
/*
 * adns_unix_calls.c
 * - Simple implementation of requiered UNIX system calls and
 *   library functions.
 */
/*
 *  This file is
 *    Copyright (C) 2000 Jarle (jgaa) Aase <jgaa@jgaa.com>
 *
 *  It is part of adns, which is
 *    Copyright (C) 1997-2000 Ian Jackson <ian@davenant.greenend.org.uk>
 *    Copyright (C) 1999 Tony Finch <dot@dotat.at>
 *  
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software Foundation,
 *  Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA. 
 */


#include "adns.h"

#ifdef ADNS_MAP_UNIXAPI
/*
int adns_writev (int FileDescriptor, const struct iovec * iov, int iovCount)
{
  size_t total_len = 0;
  int bytes_written = 0;
  int i = 0;
  char *buf = NULL, *p = NULL;
  
  for(; i < iovCount; i++)
    total_len += iov[i].iov_len;
  
  p = buf = (char *)alloca(total_len);
  
  for(; i < iovCount; i++)
  {
    memcpy(p, iov[i].iov_base, iov[i].iov_len);
    p += iov[i].iov_len;
  }
  
  return send(FileDescriptor, buf, total_len, 0);
}

int adns_inet_aton(const char *cp, struct in_addr *inp)
{
  inp->s_addr = inet_addr(cp);
  return inp->s_addr != INADDR_ANY;
}

int adns_getpid()
{
  return GetCurrentProcessId();
}
*/
int adns_gettimeofday(struct timeval *tv, struct timezone *tz)
{
  static __int64 Adjustment;
  __int64 Now = 0;
  
  if (!Adjustment)
  {
    SYSTEMTIME st = {1970,1,3,0,0,0,0};
    SystemTimeToFileTime(&st, (LPFILETIME)Adjustment);
  }
  
  if (tz)
  {
    errno = EINVAL;
    return -1;
  }
  
  GetSystemTimeAsFileTime((LPFILETIME)&Now);
  Now -= Adjustment;
  
  tv->tv_sec = (long)(Now / 100000000);
  tv->tv_usec = (long)((Now / 100) - (((__int64)tv->tv_sec * 1000) * 100));
  return 0;
}

#endif /* ADNS_MAP_UNIXAPI */

#ifdef HAVE_POLL
int adns_poll(struct pollfd *ufds, unsigned int nfds, int timeout)
{
  DWORD Result;
  unsigned int i = 0;
  SOCKET *Sck;
  u_long Arg;
  int ArgLen;
  BOOL bResult;
  DWORD dwTimeout = (timeout == WSA_INFINITE) ? 1 : (DWORD)timeout; /* Avoid infinitive lock */
  
  Sck = (SOCKET *)alloca(sizeof(int) *nfds);
  for(i = 0; i < nfds; i++)
  {
    Sck[i] = (SOCKET)ufds[i].fd;
    ufds[i].revents = 0;
  }
  
again:
  Result = WSAWaitForMultipleEvents((DWORD)nfds, 
    (const HANDLE *)Sck, 
    FALSE, dwTimeout, 
    FALSE);
  
  if ((Result >= WSA_WAIT_EVENT_0) 
    && (Result < (WSA_WAIT_EVENT_0 + nfds)))
  {
    Arg = 0;
    ArgLen = sizeof(Arg);
    if (!getsockopt(ufds[Result].fd, 
      SOL_SOCKET, 
      SO_ERROR, 
      (char *)&Arg, 
      &ArgLen)
      && (Arg != 0))
    {
      switch(Arg)
      {
      case WSAECONNRESET:
      case WSAECONNREFUSED:
      case WSAENETDOWN:
      case WSAECONNABORTED:
	ufds[Result].revents |= POLLHUP;
	break;
      case WSANOTINITIALISED:
      case WSA_INVALID_HANDLE:
	ufds[Result].revents |= POLLNVAL;
	break;
      }
      ufds[Result].revents |= POLLERR;
      return 1;
    }
    else
    {
      errno = WSAGetLastError();
      return -1;
    }
    if (ufds[Result].events & POLLIN)
    {
      Arg = 0;
      ioctlsocket(ufds[Result].fd, FIONREAD, &Arg);
      if (Arg > 0)
	ufds[Result].revents |= POLLIN;
    }
    if (ufds[Result].events & POLLOUT)
    {
    /* This is suspect!
    * TODO: Check if data can be sent
      */
      ufds[Result].revents |= POLLIN;
    }
    if (ufds[Result].events & POLLPRI)
    {
      bResult = FALSE;
      if (!WSAIoctl(ufds[Result].fd, SIOCATMARK, NULL, NULL, &bResult,
	sizeof(bResult), NULL, NULL, NULL)
	&& (bResult == TRUE))
      {
	ufds[Result].revents |= POLLPRI;
      }
    }
    
    return 1;
  }
  else if (Result == WSA_WAIT_TIMEOUT)
    return 0;
  else
    goto again;
  
  return -1; /* Compiler food yam yam */
}
#endif /* HAVE_POLL */

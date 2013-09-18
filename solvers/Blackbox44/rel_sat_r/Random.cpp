/////////////////
// OS Includes

//////////////
// Includes
#include "Random.h"

/////////////
// Defines
static long state1[32] = {
  3,
  0x9a319039, 0x32d9c024, 0x9b663182, 0x5da1f342,
  0x7449e56b, 0xbeb1dbb0, 0xab5c5918, 0x946554fd,
  0x8c2e680f, 0xeb3d799f, 0xb11ee0b7, 0x2d436b86,
  0xda672e2a, 0x1588ca88, 0xe369735d, 0x904f35f7,
  0xd7158fd6, 0x6fa6f051, 0x616e6b96, 0xac94efdc,
  0xde3b81e0, 0xdf0a6fb5, 0xf103bc02, 0x48f340fb,
  0x36413f93, 0xc622c298, 0xf5a42ab8, 0x8a88d77b,
  0xf5ad9d0e, 0x8999220b, 0x27fb47b9
};

///////////////////////////////////////////////////////////////////////////////
// Public Methods
void Random::vInitRandom(long lSeed_) 
{
#ifdef WIN32
  srand(lSeed_);
#else
  initstate(lSeed_,(char*)state1,128);
  setstate((char*)state1);
#endif
}

///////////////////////////////////////////////////////////////////////////////
// Protected Methods

///////////////////////////////////////////////////////////////////////////////
// Private Methods






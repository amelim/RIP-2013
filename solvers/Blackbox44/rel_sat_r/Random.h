#ifndef Random_h
#define Random_h

///////////////////////////////////////////////////////////////////////////////
// Initializes random number generation

/////////////////
// OS Includes

#include <stdlib.h>

// WIN32 doesn't include random(), only rand()
#ifdef WIN32
  #define random() rand()
  #define srandom(seed) srand(seed)
#endif

//////////////
// Includes
#include "LightweightTypes.h"

/////////////
// Defines

////////////////////////
// Class Declarations
class Random {
public:
  static void vInitRandom(long);
  static double dRandom1() {return ((double)(random())/((double)2147483648L));} // [0-1.0)
  static double dRandom2() {return ((double)(random()+1)/((double)2147483648L));}  // (0-1.0]
  static double dRandom3() {return ((double)(random())/((double)2147483647L));}  // [0-1.0]
  static double dRandom4() {return ((double)(random()+1)/((double)2147483649L));}  // (0-1.0)
  static unsigned int iRandom(unsigned int iMax_) {return ((unsigned int)random())%iMax_;}
  static unsigned long lRandom(unsigned long lMax_) {return ((unsigned long)random())%lMax_;}
  static boolean bRandom() {return (boolean)(random()%2);}
};

///////////////////////////////////////////////////////////////////////////////
// Class Definitions

///////////////////////////////////////////////////////////////////////////////
// Inlines

#endif // Random_h


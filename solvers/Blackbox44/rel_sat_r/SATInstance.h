#ifndef SATInstance_h
#define SATInstance_h

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SATInstance

/////////////////
// OS Includes

//////////////
// Includes
#include "ClauseList.h"

/////////////
// Defines

////////////////////////
// Class Declarations
// class istream;

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Class Definitions

class SATInstance : public ClauseList {
public:
  SATInstance() {}

  void vOutput();
  void vOutput(ofstream&);
  void vOutputDimacs();

  boolean bReadDimacs(char* aFileName_);
  boolean bReadDimacs(istream&);
  boolean bReadDimacs(VariableID eMaxVar, int iClauseCount, VariableID * CnfArray);


  // static data
  static SATInstance xSATInstance;
  int iVariableCount;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Inlines

#endif // SATInstance_h



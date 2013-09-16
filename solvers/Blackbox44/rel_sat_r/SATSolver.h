#ifndef SATSolver_h
#define SATSolver_h

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// SATSolver

/////////////////
// OS Includes
#include <sys/types.h>

#ifndef WIN32
#include <sys/times.h>
#else
#include <time.h>
#endif

//////////////
// Includes
#include "ClauseList.h"
#include "VariableSet.h"

using namespace std;

/////////////
// Defines

////////////////////////
// Class Declarations
class CSP;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Class Definitions
class VariableStruct {
 public:
  ClauseList xPositiveClauses; // stores list of clauses containing positive occurence of this 
  // variable.
  ClauseList xNegativeClauses; // stores list of clauses containing negative occurence of this 
  // variable.
  DomainValue eAssignment;
  Clause* pFilterClause1; // stores the clause filtering out "1" from this domain
  Clause* pFilterClause0; // stores the clause filtering out "0" from this domain
  Clause* pDeleteClause;
  ClauseList xDeleteList;
};

class SATSolver {
public:
  SATSolver();
  boolean bFindSolution(int iLearnOrder_, boolean& rFailed_,
			unsigned long lMaxTime_, unsigned long lMaxBt_,
			int iMaxToTry_, float _fFudgeA, float _fFudgeB);
  unsigned long lVariablesLabelled() {return _lVariablesLabelled;}
  unsigned long lBranchPointsExplored() {return _lBranchPoints;}
  unsigned long lElapsedTime() { return _lElapsedTime;}
  unsigned long lBacktracks() {return _lBacktracks;}

  double dAvgChoiceSize() {return ((double)_SumUnforcedChoices)/((double)_NumUnforcedChoices); }
  void vPrintSoln();
  
  void vSaveSoln(int *soln); // added for blackbox

private:

#ifndef WIN32
  struct tms buffer;
#else
  clock_t buffer;
#endif

  unsigned long _lMaxTime;
  unsigned long _lElapsedTime;
  unsigned long _lMaxBt;
  unsigned long _lBacktracks;

  // Initialization routines.
  boolean _bInitializeVariableInformation();
  inline void _vInitializeLargeClause(Clause*);
  inline void _vInitializeBinaryClause(Clause*);
  boolean _bInitializeUnaryClause(Clause*);

  VariableID _eTryAndPickBest(VariableSet& rTryVars_, boolean&);
  void _vFindBestSet(VariableSet&);
  double _iComputeScore();
  inline double _iCombineScores(double i1_, double i2_);

  boolean _bLoop(boolean&);
  boolean _bFunLoop(boolean&);

  boolean _bFastUnitPropagate();
  void _vFastBackup(VariableID);

  boolean _bUnitPropagate();
  boolean _bBackup();
  inline boolean _bFilterWithClauseList(ClauseList&);
  void _vUnfilterWithClauseList(ClauseList&);
  void _vSatisfyWithClauseList(ClauseList&);

  void _vCreateBackupClauseFromContradictions();
  inline void _vCreateNewBackupClause();
  inline void _vLearn();

  inline void _vLabelVariable(VariableID, DomainValue);
  inline void _vFastLabelVariable(VariableID, DomainValue);
  inline void _vDeleteClauses(ClauseList& rClauseList_);

  // Private data

  int _iMaxToTry;  /* 10 */
  float _fFudgeA;  /* .8 */
  float _fFudgeB;  /* .9 */

  unsigned long _SumUnforcedChoices;
  unsigned long _NumUnforcedChoices;

  unsigned long _lVariablesLabelled, _lBranchPoints;
  int _iLearnOrder;

  VariablePosition _iCurrentVariable;
  VariableID _eCurrentID;
  int _iVariableCount;
  VariableID _eContradictionID;

  VariableStruct _aVariableStruct[MAX_VARIABLES];
  VariableID _aPositionToID[MAX_VARIABLES]; // Maps the variables position to the variable ID
  double _aScore[MAX_VARIABLES];

  VariableSet _xUnitVariables0;  // Variables with unit sized domains containing 0
  VariableSet _xUnitVariables1;  // Variables with unit sized domains containing 1
  VariableSet _xBackupSet;
  VariableSet _xNegatedSet;
  VariableSet _xPermaVariables;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Inlines

inline double SATSolver::_iCombineScores(double i1_, double i2_)
{
  return (i1_ * i2_) + i1_ + i2_;
}

#endif // SATSolver_h


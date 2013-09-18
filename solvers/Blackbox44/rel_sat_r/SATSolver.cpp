/////////////////
// OS Includes
//#include <stdlib.h>
#include <fstream>


//////////////
// Includes
#include "Clause.h"
#include "Random.h"
#include "SATInstance.h"
#include "SATSolver.h"

#include "globals.h"

#include "../interface.h"

using namespace std;

/////////////////////////////
// Static Data Initialization

/////////////
// Defines
#define MAX_TO_TRY                  10

// #define RELEVANCE_BOUNDED_LEARNING  // Uncomment to use relevance bounded learning 
// in place of size-bounded learning

//#define SKIP_PURE_LITERALS   // Uncomment to use a simple pure literal rule.

//#define MAX_TIME                    90000 // 15 minutes of CPU time
#define MAX_TIME                    60000 // 10 minutes of CPU time
//#define MAX_TIME                  3600000 // 10 hours of CPU time
//#define NO_TIME_LIMIT          // Uncomment to enforce no time limit

//#define PRINT_STACK   // Uncomment to output stack traces
#define PRINT_FREQUENCY 100
// ^^ Says how many branch points should elapse between stack trace output

//#define NAIVE_SOLVER  // Uncomment to stop CBJ and learning
//#define ISAMP         // Uncomment, along with NAIVE_SOLVER,  to implement ISAMP

//#define OUTPUT_SOLUTION   // Uncomment to have the solver output a solution if one is found 
//#define FAVOR_SMALL_CLAUSES // Uncomment to have small clauses favored for filtering

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Methods
SATSolver::SATSolver()
{}

boolean SATSolver::bFindSolution(int iLearnOrder_, boolean& rFailed_,
				 unsigned long lMaxTime_, unsigned long lMaxBt_,
				 int iMaxToTry_, float fFudgeA_, float fFudgeB_)
{
  // Returns 1 if problem is soluble, returns 0 if unsoluble. rFailed_
  // is set to 1 if the problem is too hard; 
  _iMaxToTry = iMaxToTry_;
  _fFudgeA = fFudgeA_;
  _fFudgeB = fFudgeB_;
  _lMaxTime = lMaxTime_;
  _lMaxBt = lMaxBt_;
  _iLearnOrder = iLearnOrder_;
  rFailed_ = 0;
  _lVariablesLabelled = 0;
  _lBacktracks = 0;
  _lBranchPoints = 0;
  _iCurrentVariable = 0;

  _SumUnforcedChoices = 0;
  _NumUnforcedChoices = 0;


  if (!_bInitializeVariableInformation())
    return 0; // problem is UNSAT due to node consistency

  // Here we do an initial unit propagation since initialization
  // can discover unit domained variables due to unary clauses.

#ifndef  WIN32
  times(&buffer);
  _lElapsedTime = buffer.tms_utime + buffer.tms_stime;
#else
  _lElapsedTime = clock();
#endif

  if (_bUnitPropagate())
    return 0;
  boolean bReturn =  _bLoop(rFailed_);

#ifndef WIN32
  times(&buffer);
  _lElapsedTime = (buffer.tms_utime + buffer.tms_stime) - _lElapsedTime;
#else
  _lElapsedTime = clock() - _lElapsedTime;
#endif
  return bReturn;
}

void SATSolver::vPrintSoln()
{
    cout << "Begin assignment" << endl;
    for (int i=0; i<_iVariableCount; i++) {
      if (_aVariableStruct[i].eAssignment)
	cout << i+1 << ' ';
      else cout << "-" << i+1 << ' ';
      if (((i+1) % 20) == 0) cout << endl;
    }
    cout << endl;
    cout << "End assignment" << endl;
}

void SATSolver::vSaveSoln(int *soln)
{
    for (int i=0; i<_iVariableCount; i++) {
      soln[i+1] = ((_aVariableStruct[i].eAssignment) ? 1 : 0);
    }
}

boolean SATSolver::_bLoop(boolean& rFailed_)
{
  VariableSet xTryVars;
  while (_iCurrentVariable != _iVariableCount) {
    assert(_xUnitVariables0.iVariableCount() == 0);
    assert(_xUnitVariables1.iVariableCount() == 0);
    VariableID eBestID;
    _vFindBestSet(xTryVars);
    boolean bZeroFirst = 0;
    

    /* added for blackbox */
    if (bb_limitp(Relsat_Rate)) {
      rFailed_ = Timeout;	// Timeout == 2
      return 0;
    }
    
    
    if (_lMaxBt != 0 && _lBacktracks > _lMaxBt){
      rFailed_ = Failure;
      return 0;
    }

    if (_lMaxTime > 0){
#ifndef WIN32
	times(&buffer);
	if (((buffer.tms_utime + buffer.tms_stime) - _lElapsedTime) > _lMaxTime) {
#else
        if (((clock()) - _lElapsedTime) > _lMaxTime) {
#endif
	    rFailed_ = Timeout;
	    return 0;
	}
    }
    if (xTryVars.iVariableCount() == 1) {
      eBestID = xTryVars.eVariable(0);
    }
    else {
      eBestID = _eTryAndPickBest(xTryVars, bZeroFirst);
    }

#ifdef SKIP_PURE_LITERALS
    // Search for a pure literal.  This implementation of pure literal
    // rule only checks to see if the variable selected as "best"
    // appears as a pure literal. It does not check EVERY open
    // variable for pure literal status.  The implementation exploits
    // the fact that CBJ will backjump over the pure literal instead
    // of branch on it given appropriate value ordering.

    ClauseList* pClauseList = &_aVariableStruct[eBestID].xPositiveClauses;
    boolean bAllSatisfied = 1;
    for (int i=0; i < pClauseList->iClauseCount(); i++) {
      if (!pClauseList->pClause(i)->bIsSatisfied()) {
        bAllSatisfied = 0;
        break;
      }
    }
    if (bAllSatisfied) {
      bZeroFirst = 1;
      cout << "Using Pure Literal Rule." << endl;
    }
    else {
      pClauseList = &_aVariableStruct[eBestID].xNegativeClauses;
      bAllSatisfied = 1;
      for (int i=0; i < pClauseList->iClauseCount(); i++) {
        if (!pClauseList->pClause(i)->bIsSatisfied()) {
          bAllSatisfied = 0;
          break;
        }
      }
      if (bAllSatisfied) {
        bZeroFirst = 0;
	cout << "Using Pure Literal Rule." << endl;
      }
    }
#endif //SKIP_PURE_LITERALS
    if (bZeroFirst) {
      _xUnitVariables0.vAddVariableNoCheck(eBestID);
    }
    else {
      _xUnitVariables1.vAddVariableNoCheck(eBestID);
    }
    if (_bUnitPropagate()) {
      if (_bBackup()) {
	return 0;
      }
    }
  }
  return 1;
}

VariableID SATSolver::_eTryAndPickBest(VariableSet& rTryVars_, boolean& bZeroFirst)
{
    int i;
    
  // Performs a "fast" unit propagation for both labels of each variable in the set and
  // returns the variable that leads to the most binary clauses, or the first variable that leads
  // to a contradiction.
  assert(_xUnitVariables0.iVariableCount() == 0);
  assert(_xUnitVariables1.iVariableCount() == 0);
  _xBackupSet.vClear(); // danger: Reusing this variable
  double iBestScore = -1;
  double iScore;
  double iNewScore;
  for (i=0; i<rTryVars_.iVariableCount(); i++) {
    VariableID eID = rTryVars_.eVariable(i);
    assert(_aVariableStruct[eID].eAssignment == NON_VALUE);
    _xUnitVariables0.vAddVariableNoCheck(eID);
    iScore = _iComputeScore();
    if (iScore == -1) {
      bZeroFirst = 1;
      return eID;  // A dead end was hit
    }
    _xUnitVariables1.vAddVariableNoCheck(eID);
    iNewScore = _iComputeScore(); 
    if (iNewScore == -1) {
      bZeroFirst = 0;
      return eID;
    }
    double iCombinedScore = _iCombineScores(iScore, iNewScore);
    if (iCombinedScore >= iBestScore) {
      iBestScore = iCombinedScore;
      _xBackupSet.vAddVariable(eID);
      _aScore[eID] = iCombinedScore;
    }
  } // for (int i=0;...
  rTryVars_.vClear();
  double iAcceptableScore = iBestScore* _fFudgeB;
  for (i=0; i<_xBackupSet.iVariableCount(); i++) {



    if (_aScore[_xBackupSet.eVariable(i)] >= iAcceptableScore) {
      rTryVars_.vAddVariable(_xBackupSet.eVariable(i));
    }
  }
  bZeroFirst = Random::iRandom(2);

 _NumUnforcedChoices++;
 _SumUnforcedChoices += rTryVars_.iVariableCount();

  VariableID eReturn = rTryVars_.eVariable(Random::iRandom(rTryVars_.iVariableCount()));
  return eReturn;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Protected Methods

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Methods
boolean SATSolver::_bInitializeVariableInformation()
{
    int i;
    
  // Return 0 if problem is UNSAT due to unary clauses (node-consistency)
  _eCurrentID = NON_ID;
  _iVariableCount = SATInstance::xSATInstance.iVariableCount;
  for (i=0; i< _iVariableCount; i++) {
    Clause::a2ClauseCount[i*2] = 0;
    Clause::a2ClauseCount[i*2+1] = 0;
    _aVariableStruct[i].eAssignment = NON_VALUE;
    _aVariableStruct[i].pDeleteClause = 0;
    _aVariableStruct[i].pFilterClause0 = 0;
    _aVariableStruct[i].pFilterClause1 = 0;
  }

  for (i=0; i<SATInstance::xSATInstance.iClauseCount(); i++) {
    Clause* pClause = SATInstance::xSATInstance.pClause(i);
    if (pClause->iVariableCount() == 2) {
      _vInitializeBinaryClause(pClause);
    }
    else if (pClause->iVariableCount() == 1) {
      if (_bInitializeUnaryClause(pClause) == 0)
	return 0;
    }
    else {
      _vInitializeLargeClause(pClause);
    }
  }
  return 1;
}

inline void SATSolver::_vInitializeLargeClause(Clause* pClause_)
{
  for (int j=0; j<pClause_->iPermaCount(); j++) {
    if (pClause_->bIsNegated(j))
      _aVariableStruct[pClause_->eConstrainedVariable(j)].xNegativeClauses.vAddClause(pClause_);
    else
      _aVariableStruct[pClause_->eConstrainedVariable(j)].xPositiveClauses.vAddClause(pClause_);
  }
}

inline void SATSolver::_vInitializeBinaryClause(Clause* pClause_)
{
  assert(pClause_->iVariableCount() == 2);
  for (int j=0; j<2; j++) {
    if (pClause_->bIsNegated(j))
      _aVariableStruct[pClause_->eConstrainedVariable(j)].xNegativeClauses.vAddClause(pClause_);
    else
      _aVariableStruct[pClause_->eConstrainedVariable(j)].xPositiveClauses.vAddClause(pClause_);
    Clause::a2ClauseCount[pClause_->iLiteralID(j)]++;
  }
}

boolean SATSolver::_bInitializeUnaryClause(Clause* pClause_)
{
  // returns 0 if problem is determined to be UNSAT 
  assert(pClause_->iVariableCount() == 1);
  VariableID eConstrainedVariable = pClause_->eConstrainedVariable(0);
  if (pClause_->bIsNegated(0)) {
    if (_aVariableStruct[eConstrainedVariable].pFilterClause0)
      return 0; // problem is UNSAT
    if (_aVariableStruct[eConstrainedVariable].pFilterClause1 == 0) {
      _xUnitVariables0.vAddVariable(eConstrainedVariable);
      _aVariableStruct[eConstrainedVariable].pFilterClause1 = pClause_;
    }
  }
  else {
    if (_aVariableStruct[eConstrainedVariable].pFilterClause1)
      return 0; // problem is UNSAT
    if (_aVariableStruct[eConstrainedVariable].pFilterClause0 == 0) {
      _xUnitVariables1.vAddVariable(eConstrainedVariable);
      _aVariableStruct[eConstrainedVariable].pFilterClause0 = pClause_;
    }
  }
  return 1;
}

void SATSolver::_vFindBestSet(VariableSet& xTryVars)
{
  xTryVars.vClear();
#ifdef ISAMP
    // select random unlabelled variable
    VariableID eID;
    do {
      eID = Random::iRandom(_iVariableCount);
    } while (_aVariableStruct[eID].eAssignment != NON_VALUE);
    xTryVars.vAddVariable(eID);
    return;
#endif ISAMP
  double iBestScore = 1.0;
  _xBackupSet.vClear(); // danger: reusing this variable
  for (VariableID i=0; i<_iVariableCount; i++) {
    if (_aVariableStruct[i].eAssignment == NON_VALUE) {
      _aScore[i] = _iCombineScores(Clause::a2ClauseCount[i*2], Clause::a2ClauseCount[i*2+1]);
      if (_aScore[i] >= iBestScore * _fFudgeA) {
	_xBackupSet.vAddVariable(i);
	if (_aScore[i] > iBestScore) {
	  iBestScore = _aScore[i];
	}
      }
    }
  }

  if (_xBackupSet.iVariableCount()) {
    double iAcceptableScore = iBestScore * _fFudgeA;
    for (int i=0; i<_xBackupSet.iVariableCount(); i++) {
      VariableID eID = _xBackupSet.eVariable(i);
      if (_aScore[eID] >= iAcceptableScore)
	xTryVars.vAddVariable(eID);
    }
    while (xTryVars.iVariableCount() > _iMaxToTry) {
      xTryVars.vRemoveVariable(xTryVars.eVariable(Random::iRandom(xTryVars.iVariableCount())));
    }
  }
  else {
    // All the variables are worthless so select a random unlabelled variable
    //    cout << "Selecting a worthless variable\n"; 
    VariableID eID;
    do {
      eID = Random::iRandom(_iVariableCount);
    } while (_aVariableStruct[eID].eAssignment != NON_VALUE);
    xTryVars.vAddVariable(eID);
  }
  //  cout << "Best: " << iBestScore << "  Count: " << xTryVars.iVariableCount() <<  endl;
}

double SATSolver::_iComputeScore()
{
  // Before calling, ensure that there is exactly one unit variable.
  // On exit, ensures that there are no unit variables.
  // Returns the number of variables labelled by performing unit propagation, 
  // or -1 if a contradiction is derived.
  assert(_xUnitVariables0.iVariableCount() == 1 || _xUnitVariables1.iVariableCount() == 1);
  assert(_xUnitVariables0.iVariableCount() == 0 || _xUnitVariables1.iVariableCount() == 0);

  int iRememberVariableCount = _iCurrentVariable;
  VariableID eBackupID = _eCurrentID; 
  boolean bContradiction = _bFastUnitPropagate();
  if (bContradiction) {
    _vFastBackup(eBackupID);
    _xUnitVariables0.vClear();
    _xUnitVariables1.vClear();
    return -1;  
  }
  int iReturn = (_iCurrentVariable - iRememberVariableCount);
  _vFastBackup(eBackupID);
  return iReturn;
}

void SATSolver::_vFastBackup(VariableID eBackupID_)
{
  Clause** aClauseList1;
  Clause** aClauseList2;
  int iTo1, iTo2, iTo;
  register int i;
  while (1) { 
    if (_aVariableStruct[_eCurrentID].eAssignment == 1) {
      aClauseList1 = _aVariableStruct[_eCurrentID].xNegativeClauses._aClause;
      iTo1 = _aVariableStruct[_eCurrentID].xNegativeClauses.iClauseCount();
      aClauseList2 = _aVariableStruct[_eCurrentID].xPositiveClauses._aClause;
      iTo2 = _aVariableStruct[_eCurrentID].xPositiveClauses.iClauseCount();
    }
    else {
      aClauseList1 = _aVariableStruct[_eCurrentID].xPositiveClauses._aClause;
      iTo1 = _aVariableStruct[_eCurrentID].xPositiveClauses.iClauseCount();
      aClauseList2 = _aVariableStruct[_eCurrentID].xNegativeClauses._aClause;      
      iTo2 = _aVariableStruct[_eCurrentID].xNegativeClauses.iClauseCount();
    }

    if (iTo1 > iTo2) {
      for (i = 0; i < iTo2; i++) {
	aClauseList1[i]->vFastUnfilter();
	aClauseList2[i]->vFastMakeUnsatisfied();
      }
      for (; i < iTo1; i++) {
	aClauseList1[i]->vFastUnfilter();
      }
    }
    else {
      for (i = 0; i < iTo1; i++) {
	aClauseList1[i]->vFastUnfilter();
	aClauseList2[i]->vFastMakeUnsatisfied();
      }      
      for (; i < iTo2; i++) {
	aClauseList2[i]->vFastMakeUnsatisfied();
      }      
    }
    //
    _aVariableStruct[_eCurrentID].eAssignment = NON_VALUE;
    _iCurrentVariable--;
    if (_iCurrentVariable == 0) {// special code only needed for labelling first variable..
      _eCurrentID = -1;
      break;
    }
    _eCurrentID = _aPositionToID[_iCurrentVariable-1];
    if (_eCurrentID == eBackupID_)
      break;
  } //while(1);
}

boolean SATSolver::_bFastUnitPropagate()
{
  // Return 1 if unit propagation leads to a contradiction.
  // Does not back up, does not learn.

  int iTo1, iTo2, iInnerTo; 
  register int i;
  int j;
  Clause** aClauseList1;
  Clause** aClauseList2;
  Clause* pWorkClause;
  boolean bReturn;
  VariableID eID;
  while(1) {
    if (_xUnitVariables1.iVariableCount()) {
      _vFastLabelVariable(_xUnitVariables1.eVariable(0), 1);
      _xUnitVariables1.vRemoveVariable(_eCurrentID);
      aClauseList1 = _aVariableStruct[_eCurrentID].xPositiveClauses._aClause;
      iTo1 = _aVariableStruct[_eCurrentID].xPositiveClauses.iClauseCount();
      aClauseList2 = _aVariableStruct[_eCurrentID].xNegativeClauses._aClause;
      iTo2 = _aVariableStruct[_eCurrentID].xNegativeClauses.iClauseCount();
    }
    else if (_xUnitVariables0.iVariableCount()) {
      _vFastLabelVariable(_xUnitVariables0.eVariable(0), 0);
      _xUnitVariables0.vRemoveVariable(_eCurrentID);
      aClauseList1 = _aVariableStruct[_eCurrentID].xNegativeClauses._aClause;
      iTo1 = _aVariableStruct[_eCurrentID].xNegativeClauses.iClauseCount();
      aClauseList2 = _aVariableStruct[_eCurrentID].xPositiveClauses._aClause;
      iTo2 = _aVariableStruct[_eCurrentID].xPositiveClauses.iClauseCount();
    }
    else return 0;

    for (i = 0; i < iTo1; i++) {
      aClauseList1[i]->vFastMakeSatisfied();
    }

    bReturn = 0;

    for (i = 0; i < iTo2; i++) {
      pWorkClause = aClauseList2[i];
      if (pWorkClause->bFastFilter()) {
	// Find the variable it filters.
	iInnerTo = pWorkClause->iVariableCount();
	for (j = 0; j < iInnerTo; j++) {
	  eID = pWorkClause->eConstrainedVariable(j);
	  if (_aVariableStruct[eID].eAssignment == NON_VALUE) {
	    // we've found the filtering variable
	    if (pWorkClause->bIsNegated(j)) {
	      _xUnitVariables0.vAddVariable(eID);
	      if (_xUnitVariables1.bHasVariable(eID)) {
		// Can't simply return immediately because it will confuse the state undoing code
		bReturn = 1;
	      }
	    }
	    else  {
	      _xUnitVariables1.vAddVariable(eID);
	      if (_xUnitVariables0.bHasVariable(eID)) {
		// Can't simply return immediately because it will confuse the state undoing code
		bReturn = 1;
	      }
	    }
	    break;
	  }
	}
      }
    } // for i
    if (bReturn == 1) {
      return 1;
    }
  } //while(1);
}

boolean SATSolver::_bUnitPropagate()
{
  // Return 1 if unit propagation leads to a contradiction.
  // Does not back up, does not learn.
  // Simply leaves the list of contradicting variables intact.

  boolean bContradiction = 0;
  while(1) {
    if (_xUnitVariables1.iVariableCount()) {
      _vLabelVariable(_xUnitVariables1.eVariable(0), 1);
      _xUnitVariables1.vRemoveVariable(_eCurrentID);
      _vSatisfyWithClauseList(_aVariableStruct[_eCurrentID].xPositiveClauses);
      if (_bFilterWithClauseList(_aVariableStruct[_eCurrentID].xNegativeClauses)) {
	return 1;
      }
    }
    else if (_xUnitVariables0.iVariableCount()) {
      _vLabelVariable(_xUnitVariables0.eVariable(0), 0);
      _xUnitVariables0.vRemoveVariable(_eCurrentID);
      _vSatisfyWithClauseList(_aVariableStruct[_eCurrentID].xNegativeClauses);      
      if (_bFilterWithClauseList(_aVariableStruct[_eCurrentID].xPositiveClauses)) {
	return 1;
      }
    }
    else return 0;
  } // while(1);
}



void SATSolver::_vUnfilterWithClauseList(ClauseList& rClauseList_)
{
  int iTo =  rClauseList_.iClauseCount();
  for (int i = 0; i < iTo; i++) {
    rClauseList_.pClause(i)->vUnfilter();
  }
}

boolean SATSolver::_bFilterWithClauseList(ClauseList& rClauseList_)
{
  // return 1 if contradiction encountered.

  int iTo =  rClauseList_.iClauseCount();
  boolean bReturn = 0;
  Clause* pWorkClause;
  for (int i = 0; i < iTo; i++) {
    pWorkClause = rClauseList_.pClause(i);
    if (pWorkClause->bFilter()) {
      // Find the variable it filters.
      for (int j = 0; j < pWorkClause->iVariableCount(); j++) {
	VariableID eID = pWorkClause->eConstrainedVariable(j);
	if (_aVariableStruct[eID].eAssignment == NON_VALUE) {
	  // we've found the filtering variable
	  if (pWorkClause->bIsNegated(j)) {

	    if (_aVariableStruct[eID].pFilterClause1) {
#ifdef FAVOR_SMALL_CLAUSES
	      if (_aVariableStruct[eID].pFilterClause1->iVariableCount() >
		  pWorkClause->iVariableCount()) {
		_aVariableStruct[eID].pFilterClause1 = pWorkClause;
	      }
	      else if (_aVariableStruct[eID].pFilterClause1->iVariableCount() ==
		       pWorkClause->iVariableCount()) 
#endif
		{ 
		  if (Random::bRandom()) 
		    _aVariableStruct[eID].pFilterClause1 = pWorkClause;
		}
	    }
	    else {
	      _aVariableStruct[eID].pFilterClause1 = pWorkClause;
	      _xUnitVariables0.vAddVariable(eID);
	      if (_xUnitVariables1.bHasVariable(eID)) {
		// Can't simply return immediately because it will confuse the state undoing code
		_eContradictionID = eID;
		bReturn = 1;
	      }
	    }
	  }
	  else  {
	    if (_aVariableStruct[eID].pFilterClause0) {
#ifdef FAVOR_SMALL_CLAUSES
	      if (_aVariableStruct[eID].pFilterClause0->iVariableCount() >
		  pWorkClause->iVariableCount()) 
		_aVariableStruct[eID].pFilterClause0 = pWorkClause;
	      else if (_aVariableStruct[eID].pFilterClause0->iVariableCount() ==
		       pWorkClause->iVariableCount()) 
#endif
		{ 
		  if (Random::bRandom())
		    _aVariableStruct[eID].pFilterClause0 = pWorkClause;
		}
	    }
	    else {
	      _aVariableStruct[eID].pFilterClause0 = pWorkClause;
	      _xUnitVariables1.vAddVariable(eID);
	      if (_xUnitVariables0.bHasVariable(eID)) {
		// Can't simply return immediately because it will confuse the state undoing code
		_eContradictionID = eID;
		bReturn = 1;
	      }
	    }
	    break;
	  }
	}
      }
    }
  }
  return bReturn;
}

void SATSolver::_vSatisfyWithClauseList(ClauseList& rClauseList_)
{
  int iTo =  rClauseList_.iClauseCount();
  for (int i = 0; i < iTo; i++) {
    rClauseList_.pClause(i)->vMakeSatisfied();
  }
}


void SATSolver::_vCreateBackupClauseFromContradictions()
{
    int i;
    
  // Create a new clause representing the nogood derived from the
  // current contradiction on _eContradictionID.
  assert(_aVariableStruct[_eContradictionID].pFilterClause1);
  assert(_aVariableStruct[_eContradictionID].pFilterClause0);
  Clause* pFailClause1 = _aVariableStruct[_eContradictionID].pFilterClause1;
  Clause* pFailClause2 = _aVariableStruct[_eContradictionID].pFilterClause0;

  for (i=0; i<_xUnitVariables0.iVariableCount(); i++) {
    _aVariableStruct[_xUnitVariables0.eVariable(i)].pFilterClause1 = 0;
  }
  _xUnitVariables0.vClear();
  for (i=0; i<_xUnitVariables1.iVariableCount(); i++) {
    _aVariableStruct[_xUnitVariables1.eVariable(i)].pFilterClause0 = 0;
  }
  _xUnitVariables1.vClear();

  _xBackupSet.vClear();
  _xNegatedSet.vClear();
  for (i=0; i<pFailClause1->iVariableCount(); i++) {
    _xBackupSet.vAddVariableNoCheck(pFailClause1->eConstrainedVariable(i));
    if (pFailClause1->bIsNegated(i)) {
      _xNegatedSet.vAddVariableNoCheck(pFailClause1->eConstrainedVariable(i));
    }
  }
  for (i=0; i<pFailClause2->iVariableCount(); i++) {
    if (_xBackupSet.bAddVariable(pFailClause2->eConstrainedVariable(i)) && 
	pFailClause2->bIsNegated(i)) {
      _xNegatedSet.vAddVariableNoCheck(pFailClause2->eConstrainedVariable(i));
    }
  }
  _xBackupSet.vRemoveVariable(_eContradictionID);
}

inline void SATSolver::_vCreateNewBackupClause()
{
  Clause* pFailClause2;
  int iFailCount1 = _xBackupSet.iVariableCount();
  if (_aVariableStruct[_eCurrentID].pFilterClause0 == 0) {
    pFailClause2 = _aVariableStruct[_eCurrentID].pFilterClause1;
  }
  else {
    pFailClause2 = _aVariableStruct[_eCurrentID].pFilterClause0;
  }
  for (int i=0; i<pFailClause2->iVariableCount(); i++) {
    VariableID eWorkID = pFailClause2->eConstrainedVariable(i);
    if (_xBackupSet.bAddVariable(eWorkID) && pFailClause2->bIsNegated(i)) {
      _xNegatedSet.vAddVariableNoCheck(eWorkID);
    }
  }  
  _xBackupSet.vRemoveVariable(_eCurrentID);
}

inline void SATSolver::_vLearn()
{
  if (_xBackupSet.iVariableCount() <= _iLearnOrder) {
    //    cout  << "c Learning clause of length " << _xBackupSet.iVariableCount() << endl;
    if (_xBackupSet.iVariableCount()==1) {
      // Unary Clause! This implementation can't really learn them yet, but they arise
      // pretty rarely so learning them doesn't really seem to help much.
      // cout << "c Tried to learn unary clause on " << _xBackupSet.eVariable(0) 
      //   <<       " but couldn't.";
      //      if (_xNegatedSet.bHasVariable(_xBackupSet.eVariable(0))) {
      //	cout << " Var is negated.";
      //      }
      //      cout << endl;
    }
    else {
      Clause* pLearn = new Clause(_xBackupSet, _xNegatedSet);
      pLearn->vPrepareForUse();
      _vInitializeLargeClause(pLearn);

      // cout << "Permanent: ";
      if (DumpFlag) (*pLearn).vOutput(*PermanentFS);
    }  
  }
// #ifdef RELEVANCE_BOUNDED_LEARNING
  else if (RelevanceFlag) {
    // Learn a temporary clause
    _xPermaVariables.vClear();
    int i = _iCurrentVariable-1;
    int iBranches = 0;
    int iPermaCount = 0;
    VariableID eResetID;
    while (1) {
      VariableID eID = _aPositionToID[i];
      assert(_aVariableStruct[eID].eAssignment !=  NON_VALUE);
      if (_xBackupSet.bHasVariable(eID)) {
	if (iPermaCount == _iLearnOrder) {
	  eResetID = eID;
	  break;
	}
	if (_aVariableStruct[eID].pFilterClause0 == 0 && _aVariableStruct[eID].pFilterClause1 == 0) 
	  iBranches++;
	_xPermaVariables.vAddVariableNoCheck(eID);
	iPermaCount++;
      }
      i--;
      assert(i>=0);
    } // while
    assert(_xPermaVariables.iVariableCount() == _iLearnOrder);
    if (iBranches > 0) {
      Clause* pLearn = new Clause(_xBackupSet, _xNegatedSet, _xPermaVariables);
      _vInitializeLargeClause(pLearn);
      _aVariableStruct[eResetID].xDeleteList.vAddClause(pLearn);

      // cout << "Temporary: ";
      if (DumpFlag) (*pLearn).vOutput(*TemporaryFS);
    }
  } // else 
// #endif
}

inline void SATSolver::_vDeleteClauses(ClauseList& rClauseList_)
{
  // Delete these clauses from the problem 
  int iTo = rClauseList_.iClauseCount();
  for (int i=0; i< iTo; i++) {
    Clause* pDeleteMe = rClauseList_.pClause(i);
    for (int j=0; j<pDeleteMe->iPermaCount(); j++) {
      if (pDeleteMe->bIsNegated(j))
	_aVariableStruct[pDeleteMe->eConstrainedVariable(j)].xNegativeClauses.vDeleteClause(pDeleteMe);
      else _aVariableStruct[pDeleteMe->eConstrainedVariable(j)].xPositiveClauses.vDeleteClause(pDeleteMe);
      assert(_aVariableStruct[pDeleteMe->eConstrainedVariable(j)].eAssignment == NON_VALUE);
    }
    delete pDeleteMe;
  }
  rClauseList_.vClear();
}

inline void SATSolver::_vFastLabelVariable(VariableID eID_, DomainValue lWhich_)
{
  // Label a variable and make it current.
  _aVariableStruct[eID_].eAssignment = lWhich_;
  _aPositionToID[_iCurrentVariable++] = eID_;
  _eCurrentID = eID_;
}

inline void SATSolver::_vLabelVariable(VariableID eID_, DomainValue lWhich_)
{
  // Label a variable and make it current.
  _lVariablesLabelled++;
  _aVariableStruct[eID_].eAssignment = lWhich_;
  _aPositionToID[_iCurrentVariable++] = eID_;
  _eCurrentID = eID_;
}


#ifdef NAIVE_SOLVER 
boolean SATSolver::_bBackup()
{
  // Returns 1 if there are no solutions.
  _lBacktracks++;
start:
  for (int i=0; i<_xUnitVariables0.iVariableCount(); i++) {
    _aVariableStruct[_xUnitVariables0.eVariable(i)].pFilterClause1 = 0;
  }
  _xUnitVariables0.vClear();
  for (int i=0; i<_xUnitVariables1.iVariableCount(); i++) {
    _aVariableStruct[_xUnitVariables1.eVariable(i)].pFilterClause0 = 0;
  }
  _xUnitVariables1.vClear();

  Clause** aClause;
  Clause** aClause0;
  int iTo, iTo0;
  register int i;
  do { // while (1)
    if (_aVariableStruct[_eCurrentID].eAssignment == 1) {
      iTo0 = _aVariableStruct[_eCurrentID].xNegativeClauses.iClauseCount();
      aClause0 = _aVariableStruct[_eCurrentID].xNegativeClauses._aClause;
      iTo = _aVariableStruct[_eCurrentID].xPositiveClauses.iClauseCount();
      aClause = _aVariableStruct[_eCurrentID].xPositiveClauses._aClause;
    }
    else {
      iTo0 = _aVariableStruct[_eCurrentID].xPositiveClauses.iClauseCount();
      aClause0 = _aVariableStruct[_eCurrentID].xPositiveClauses._aClause;
      iTo = _aVariableStruct[_eCurrentID].xNegativeClauses.iClauseCount();
      aClause = _aVariableStruct[_eCurrentID].xNegativeClauses._aClause;
    }
    for (i = 0; i < iTo0; i++) {
      aClause0[i]->vUnfilter();
    }
    for (i = 0; i < iTo; i++) {
      aClause[i]->vMakeUnsatisfied();
    }
#ifndef ISAMP
    if (_aVariableStruct[_eCurrentID].pFilterClause0 == 0 &&
	_aVariableStruct[_eCurrentID].pFilterClause1 == 0) {
      // we have backed up to a branch
      _lBranchPoints++;
#ifdef PRINT_STACK
		if (_lBranchPoints % PRINT_FREQUENCY == 1) {
	  	  int iNoBranch = 0;
	  cout << '>';
	  for (int k=0; k<_iCurrentVariable; k++) {
	    VariableID eWorkID = _aPositionToID[k];
	    if (_aVariableStruct[eWorkID].pFilterClause0 == 0 &&
		_aVariableStruct[eWorkID].pFilterClause1 == 0) {
	      cout << iNoBranch << ' ';
	      iNoBranch = 0;
	    }
	    else {
	      iNoBranch++;
	    }
	  }
	  cout << endl;
	}
#endif PRINT_STACK
      if (_aVariableStruct[_eCurrentID].eAssignment == 0) {
	  // This code is for branch variables initially labelled with 0
	_aVariableStruct[_eCurrentID].pFilterClause0 = (Clause*) 1;
	_xUnitVariables1.vAddVariable(_eCurrentID);
      }
      else {
	_aVariableStruct[_eCurrentID].pFilterClause1 = (Clause*) 1;
	_xUnitVariables0.vAddVariable(_eCurrentID);
      }
      _iCurrentVariable--;
      if (_bUnitPropagate()) {
	goto start;
      }
      return 0;
    }
    else {
      if (_iCurrentVariable == 1)
	return 1;
    }
#endif ISAMP
    _aVariableStruct[_eCurrentID].eAssignment = NON_VALUE;
    _aVariableStruct[_eCurrentID].pFilterClause1 = 0;
    _aVariableStruct[_eCurrentID].pFilterClause0 = 0;
    _iCurrentVariable--;
    if (_iCurrentVariable == 0) {// special code only needed for labelling first variable...
      _eCurrentID = -1;
      return 0;
    }
    assert(_iCurrentVariable != 0);
    _eCurrentID = _aPositionToID[_iCurrentVariable-1];
  } while(1);
}

#endif NAIVE_SOLVER

#ifndef NAIVE_SOLVER

boolean SATSolver::_bBackup()
{
  ++_lBacktracks;
  start:
  _vCreateBackupClauseFromContradictions();
  _vLearn();

  Clause** aClause;
  Clause** aClause0;
  int iTo, iTo0;
  register int i;
  do { // while (1)
    if (_aVariableStruct[_eCurrentID].eAssignment == 1) {
      iTo0 = _aVariableStruct[_eCurrentID].xNegativeClauses.iClauseCount();
      aClause0 = _aVariableStruct[_eCurrentID].xNegativeClauses._aClause;
      iTo = _aVariableStruct[_eCurrentID].xPositiveClauses.iClauseCount();
      aClause = _aVariableStruct[_eCurrentID].xPositiveClauses._aClause;
    }
    else {
      iTo0 = _aVariableStruct[_eCurrentID].xPositiveClauses.iClauseCount();
      aClause0 = _aVariableStruct[_eCurrentID].xPositiveClauses._aClause;
      iTo = _aVariableStruct[_eCurrentID].xNegativeClauses.iClauseCount();
      aClause = _aVariableStruct[_eCurrentID].xNegativeClauses._aClause;
    }
    for (i = 0; i < iTo0; i++) {
      aClause0[i]->vUnfilter();
    }
    for (i = 0; i < iTo; i++) {
      aClause[i]->vMakeUnsatisfied();
    }
    if (_xBackupSet.bHasVariable(_eCurrentID)) {
      if (_aVariableStruct[_eCurrentID].pFilterClause0 == 0 &&
	  _aVariableStruct[_eCurrentID].pFilterClause1 == 0) {
	// we have backed up to a branch
	_vDeleteClauses(_aVariableStruct[_eCurrentID].xDeleteList);
	_lBranchPoints++;
#ifdef PRINT_STACK
	if (_lBranchPoints % PRINT_FREQUENCY == 1) {
	  int iNoBranch = 0;
	  cout << '>';
	  for (int k=0; k<_iCurrentVariable; k++) {
	    VariableID eWorkID = _aPositionToID[k];
	    if (_aVariableStruct[eWorkID].pFilterClause0 == 0 &&
		_aVariableStruct[eWorkID].pFilterClause1 == 0) {
	      cout << iNoBranch << ' ';
	      iNoBranch = 0;
	    }
	    else {
	      iNoBranch++;
	    }
	  }
	  cout << endl;
	}
#endif // PRINT_STACK
	if (_aVariableStruct[_eCurrentID].eAssignment == 0) {
	  // This code is for branch variables initially labelled with 0
	  _aVariableStruct[_eCurrentID].pFilterClause0 = new Clause(_xBackupSet, _xNegatedSet);
	  _aVariableStruct[_eCurrentID].pDeleteClause = _aVariableStruct[_eCurrentID].pFilterClause0;
	  _xUnitVariables1.vAddVariable(_eCurrentID);
	}
	else {
	  _aVariableStruct[_eCurrentID].pFilterClause1 = new Clause(_xBackupSet, _xNegatedSet);
	  _aVariableStruct[_eCurrentID].pDeleteClause = _aVariableStruct[_eCurrentID].pFilterClause1;
	  _xUnitVariables0.vAddVariable(_eCurrentID);
	}
	_iCurrentVariable--;
	if (_bUnitPropagate()) {
	  goto start;
	}
	return 0;
      }
      else {
	_vCreateNewBackupClause();
	if (_xBackupSet.iVariableCount() == 0)
	  return 1;
	_vLearn();
      }
    }
    if (_aVariableStruct[_eCurrentID].pDeleteClause != 0) {
      delete _aVariableStruct[_eCurrentID].pDeleteClause;
      _aVariableStruct[_eCurrentID].pDeleteClause = 0;
    }
    _aVariableStruct[_eCurrentID].eAssignment = NON_VALUE;
    _aVariableStruct[_eCurrentID].pFilterClause1 = 0;
    _aVariableStruct[_eCurrentID].pFilterClause0 = 0;
    _vDeleteClauses(_aVariableStruct[_eCurrentID].xDeleteList);
    _iCurrentVariable--;
    assert(_iCurrentVariable != 0);
    _eCurrentID = _aPositionToID[_iCurrentVariable-1];
  } while(1);
}

#endif

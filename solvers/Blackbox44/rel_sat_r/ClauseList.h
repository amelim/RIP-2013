#ifndef ClauseList_h
#define ClauseList_h

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ClauseList

/////////////////
// OS Includes
#include <assert.h>
#include <math.h>
#include <iostream>

//////////////
// Includes
#include "LightweightTypes.h"

/////////////
// Defines
#define INITIAL_SIZE 5

////////////////////////
// Class Declarations
class Clause;
class SATSolver;

class ClauseList {
  friend class SATSolver;
public:
  ClauseList() 
    : _iClauseCount(0), _iMaxSize(INITIAL_SIZE) { _aClause = new Clause*[_iMaxSize];}
  ClauseList(int iInitialSize_) 
    : _iClauseCount(0), _iMaxSize(iInitialSize_) {_aClause = new Clause*[_iMaxSize];}
  ~ClauseList() {delete [] _aClause;}
  inline void vAddClause(Clause*);
  inline void vDeleteClause(Clause*);
  Clause* pClause(int iWhich_) {assert(iWhich_>=0); assert(iWhich_<_iClauseCount); return _aClause[iWhich_];}
  int iClauseCount() {return _iClauseCount;}
  inline void vCountClauses(int&, int&);
  inline void vComputeRestrictions();
  void vClear() {_iClauseCount = 0;}
  void vDestroy();

protected:
  int _iClauseCount;
  int _iMaxSize;
  Clause** _aClause;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Class Definitions

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Inlines
void ClauseList::vAddClause(Clause* pAddMe_)
{
  // We assume there is no need to update iAlmostReady and iNotQuiteReady
  // because instantiated counts of the variables will either be zero or ALL
  if (_iMaxSize == _iClauseCount) {
    _iMaxSize = (int) (((double)_iMaxSize) * 1.5);
    // Expand the list
    Clause** _aNewList = new Clause*[_iMaxSize];
    for (int i=0; i<_iClauseCount; i++) {
      _aNewList[i] = _aClause[i];
    }
    delete [] _aClause;
    _aClause = _aNewList;
  }
  _aClause[_iClauseCount++] = pAddMe_;
}

void ClauseList::vDeleteClause(Clause* pDeleteMe_) 
{
  for (int i=_iClauseCount-1; i>=0; i--) {
    if (_aClause[i] == pDeleteMe_) {
      _aClause[i] = _aClause[--_iClauseCount];
      return;
    }
  }
  assert(0);
}

#endif // ClauseList_h



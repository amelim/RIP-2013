#ifndef Clause_h
#define Clause_h

///////////////////////////////////////////////////////////////////////////////
// This class implements CSP constraints

/////////////////
// OS Includes
#include <assert.h>
#include <fstream>

//////////////
// Includes
#include "LightweightTypes.h"
#include "Maximums.h"
#include "VariableSet.h"

/////////////
// Defines

////////////////////////
// Class Declarations

//////////////////////
// Class Definitions
class Literal {
public:
  VariableID eVariable;
  unsigned short int iLiteralID;
  boolean bIsNegated;
};

class Clause {
public:
  inline Clause(VariableSet& rConstrainedVariables_, VariableSet& rNegatedVariables_, int iUseless_);
  inline Clause(VariableSet& rConstrainedVariables_, VariableSet& rNegatedVariables_);
  inline Clause(VariableSet& rConstrainedVariables_, VariableSet& rNegatedVariables_, 
		VariableSet& rPermaVariables_);
  ~Clause() {delete [] _aConstrainedLiteral;}

  inline VariableID eConstrainedVariable(int iWhich_);
  inline boolean bIsNegated(int iWhich_);
  inline boolean bHasVariable(VariableID eVar_);
  int iLiteralID(int iWhich_) {return _aConstrainedLiteral[iWhich_].iLiteralID;}
  int iVariableCount() {return _iVariableCount;}
  int iPermaCount() {return _iPermaCount;}

  inline boolean bFastFilter();
  inline void vFastUnfilter();
  inline void vFastMakeSatisfied();
  inline void vFastMakeUnsatisfied();

  inline boolean bFilter();
  inline void vUnfilter();
  inline void vMakeSatisfied();
  inline void vMakeUnsatisfied();

  inline void vPrepareForUse();
  boolean bIsSatisfied() {return _iSatisfied;}
  void vOutput();
  void vOutput(std::ofstream&);

  // Static data
  static short int a2ClauseCount[MAX_VARIABLES*2];

protected:

  unsigned short int _iVariableCount;
  unsigned short int _iPermaCount;
  unsigned short int _iLabelledCount;
  unsigned short int _iSatisfied;
  Literal* _aConstrainedLiteral;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Inlines
inline Clause::Clause(VariableSet& rConstrainedVariables_, VariableSet& rNegatedVariables_, int)
: _iVariableCount(rConstrainedVariables_.iVariableCount()),
  _aConstrainedLiteral(new Literal[rConstrainedVariables_.iVariableCount()]),
  _iSatisfied(0),
  _iLabelledCount(0)
{
  _iPermaCount = _iVariableCount;
  for (int i=0; i < _iVariableCount; i++) {
    VariableID eWorkID = rConstrainedVariables_.eVariable(i);
    _aConstrainedLiteral[i].eVariable  = eWorkID;
    _aConstrainedLiteral[i].bIsNegated = (rNegatedVariables_.bHasVariable(eWorkID)) ? 1 : 0;
    _aConstrainedLiteral[i].iLiteralID  = eWorkID*2+_aConstrainedLiteral[i].bIsNegated;
  }
}

inline Clause::Clause(VariableSet& rConstrainedVariables_, VariableSet& rNegatedVariables_)
: _iVariableCount(rConstrainedVariables_.iVariableCount()),
  _aConstrainedLiteral(new Literal[rConstrainedVariables_.iVariableCount()])
{
    
  _iPermaCount = _iVariableCount;
  // This constructor is used by the learning mechanism
  for (int i=0; i<_iVariableCount; i++) {
    VariableID eWorkID = rConstrainedVariables_.eVariable(i);
    _aConstrainedLiteral[i].eVariable  = eWorkID;
    _aConstrainedLiteral[i].bIsNegated = (rNegatedVariables_.bHasVariable(eWorkID)) ? 1 : 0;
  }
  // If this clause is used to learn, then make sure to increment a2ClauseCounts, 
  // set _iLabelledCount(ivars), _iSatisfied(0), and iLiteralID's
}

inline Clause::Clause(VariableSet& rConstrainedVariables_, VariableSet& rNegatedVariables_, 
		      VariableSet& rPermaVariables_)
: _iVariableCount(rConstrainedVariables_.iVariableCount()),
  _iPermaCount(rPermaVariables_.iVariableCount()),
  _iSatisfied(0),
  _aConstrainedLiteral(new Literal[rConstrainedVariables_.iVariableCount()])
{
   int i;
  // This constructor is used by the relevance-bounded learning mechanism
  _iLabelledCount = _iVariableCount;
  for (i=0; i< _iPermaCount; i++) {
    VariableID eWorkID = rPermaVariables_.eVariable(i);
    _aConstrainedLiteral[i].eVariable  = eWorkID;
    _aConstrainedLiteral[i].bIsNegated = (rNegatedVariables_.bHasVariable(eWorkID)) ? 1 : 0;
    _aConstrainedLiteral[i].iLiteralID  = eWorkID * 2 + _aConstrainedLiteral[i].bIsNegated;
    Clause::a2ClauseCount[_aConstrainedLiteral[i].iLiteralID]++;
  }
  int iNext = _iPermaCount;
  for (i=0; i<_iVariableCount; i++) {
    VariableID eWorkID = rConstrainedVariables_.eVariable(i);
    if (rPermaVariables_.bHasVariable(eWorkID) == 0) {
      _aConstrainedLiteral[iNext].eVariable  = eWorkID;
      _aConstrainedLiteral[iNext].bIsNegated = (rNegatedVariables_.bHasVariable(eWorkID)) ? 1 : 0;
      iNext++;
    }
  }
  assert(iNext == _iVariableCount);
  
  // If this clause is used to learn, then make sure to increment a2ClauseCounts, 
  // set _iLabelledCount(ivars), _iSatisfied(0), and iLiteralID's
}

inline void Clause::vPrepareForUse()
{
  for (int i=0; i<_iVariableCount; i++) {
    _aConstrainedLiteral[i].iLiteralID = _aConstrainedLiteral[i].eVariable * 2 
      + _aConstrainedLiteral[i].bIsNegated;
    Clause::a2ClauseCount[_aConstrainedLiteral[i].iLiteralID]++;
  }
  _iLabelledCount = _iVariableCount;
  _iSatisfied = 0;
}  

inline boolean Clause::bIsNegated(int iWhich_)
{
  assert(iWhich_ < _iVariableCount);
  assert(iWhich_ >= 0); 
  return _aConstrainedLiteral[iWhich_].bIsNegated;
}

inline boolean Clause::bHasVariable(VariableID eVar_)
{
  for (int i=0; i<_iVariableCount; i++) {
    if (_aConstrainedLiteral[i].eVariable == eVar_)
      return 1;
  }
  return 0;
}

inline VariableID Clause::eConstrainedVariable(int iWhich_)
{
  assert(iWhich_ < _iVariableCount);
  assert(iWhich_ >= 0); 
  return _aConstrainedLiteral[iWhich_].eVariable;
}

inline boolean Clause::bFastFilter()
{
  _iLabelledCount++;
  if (_iSatisfied == 0) {
    if (_iLabelledCount == _iVariableCount-1) {
      return 1;
    }
  }
  return 0;
}

inline void Clause::vFastMakeSatisfied()
{
  _iLabelledCount++;
  if (_iSatisfied == 0) {
    _iSatisfied = _iLabelledCount;
  }
}

inline void Clause::vFastUnfilter()
{
  _iLabelledCount--;
}

inline void Clause::vFastMakeUnsatisfied()
{
  if (_iLabelledCount == _iSatisfied)
    _iSatisfied = 0;
  _iLabelledCount--;
}

inline boolean Clause::bFilter()
{
  _iLabelledCount++;
  if (_iSatisfied == 0) {
    if (_iLabelledCount == _iVariableCount-2) {
      for (int i=0; i<_iPermaCount;i++) {
	Clause::a2ClauseCount[_aConstrainedLiteral[i].iLiteralID]++;
      }
    }
    else if (_iLabelledCount == _iVariableCount-1) {
      return 1;
    }
  }
  return 0;
}

inline void Clause::vUnfilter()
{
  if (_iSatisfied == 0) {
    if (_iLabelledCount == _iVariableCount-2) {
      for (int i=0; i<_iPermaCount; i++) {
	Clause::a2ClauseCount[_aConstrainedLiteral[i].iLiteralID]--;
      }
    }
  }
  _iLabelledCount--;
}

inline void Clause::vMakeSatisfied()
{
  _iLabelledCount++;
  if (_iSatisfied==0) {
    _iSatisfied = _iLabelledCount;
    if (_iLabelledCount == _iVariableCount-1) {
      for (int i=0; i<_iPermaCount;i++) {
	Clause::a2ClauseCount[_aConstrainedLiteral[i].iLiteralID]--;
      }
    }
  }
}

inline void Clause::vMakeUnsatisfied()
{
  if (_iLabelledCount == _iSatisfied) {
    _iSatisfied = 0;
    if (_iLabelledCount == _iVariableCount-1) {
      for (int i=0; i<_iPermaCount;i++) {
	Clause::a2ClauseCount[_aConstrainedLiteral[i].iLiteralID]++;
      }
    }
  }
  _iLabelledCount--;
}

#endif // Clause_h

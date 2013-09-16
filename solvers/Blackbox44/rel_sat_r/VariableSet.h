#ifndef VariableSet_h
#define VariableSet_h

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This class allows us to manipulate a set of VariableID's. 

/////////////////
// OS Includes

//////////////
// Includes
#include "LightweightTypes.h"
#include "Maximums.h"
#include "ClauseList.h"

/////////////
// Defines

////////////////////////
// Class Declarations

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Class Definitions
class VariableSet {
public:
  VariableSet() : _iVariableCount(0) {_vClear();}
  inline void vClear();
  inline void vUnion(VariableSet& rSet_);
  inline void vRemoveVariable(VariableID eID_);
  inline void vRemoveVariableCheck(VariableID eID_);
  inline void vAddVariableNoCheck(VariableID eID_);
  inline void vAddVariable(VariableID eID_);
  inline boolean bAddVariable(VariableID eID_);
  boolean bHasVariable(VariableID eID_) {assert(eID_ < MAX_VARIABLES); return (_aHasVariable[eID_]!=-1);}
  int iVariableCount() {return _iVariableCount;}
  VariableID eVariable(int iWhich_) {assert(iWhich_ >= 0); assert(iWhich_ < _iVariableCount); return _aVariableList[iWhich_];}

private:
  void _vClear() {for (int i=0; i<MAX_VARIABLES; i++) _aHasVariable[i]=-1;}

  short _aHasVariable[MAX_VARIABLES];
  VariableID _aVariableList[MAX_VARIABLES];
  unsigned short int _iVariableCount;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Inlines
inline void VariableSet::vClear()
{
  for (int i=0; i < _iVariableCount; i++) {
    assert(_aHasVariable[_aVariableList[i]] != -1);
    _aHasVariable[_aVariableList[i]] = -1;
  }
  _iVariableCount = 0;
}

inline void VariableSet::vRemoveVariable(VariableID eID_)
{
  assert(eID_ >= 0);
  assert(eID_ < MAX_VARIABLES);
  assert(bHasVariable(eID_));
  _aVariableList[_aHasVariable[eID_]] = _aVariableList[--_iVariableCount];
  _aHasVariable[_aVariableList[_iVariableCount]] = _aHasVariable[eID_];
  _aHasVariable[eID_] = -1;
}

inline void VariableSet::vRemoveVariableCheck(VariableID eID_)
{
  assert(eID_ >= 0);
  assert(eID_ < MAX_VARIABLES);
  if (_aHasVariable[eID_] != -1) {
    _aVariableList[_aHasVariable[eID_]] = _aVariableList[--_iVariableCount];
    _aHasVariable[_aVariableList[_iVariableCount]] = _aHasVariable[eID_];
    _aHasVariable[eID_] = -1;
  }
}
    

inline void VariableSet::vAddVariableNoCheck(VariableID eID_)
{
  // Add a variable without checking for duplicates.
  assert(eID_ >= 0);
  assert(eID_ < MAX_VARIABLES);
  assert(_iVariableCount < MAX_VARIABLES);
  assert(_aHasVariable[eID_] == -1);
  _aHasVariable[eID_] = _iVariableCount;
  _aVariableList[_iVariableCount++] = eID_;
}

inline void VariableSet::vAddVariable(VariableID eID_)
{
  if (_aHasVariable[eID_] == -1) {
    vAddVariableNoCheck(eID_);
  }
}

inline boolean VariableSet::bAddVariable(VariableID eID_)
{
  if (_aHasVariable[eID_] == -1) {
    vAddVariableNoCheck(eID_);
    return 1;
  }
  return 0;
}

inline void VariableSet::vUnion(VariableSet& rSet_)
{
  for (int i=0; i<rSet_.iVariableCount(); i++) {
    if (!bHasVariable(rSet_.eVariable(i))) 
      vAddVariableNoCheck(rSet_.eVariable(i));
  }
}

#endif // VariableSet_h


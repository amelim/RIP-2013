/////////////////
// OS Includes
#include <fstream>

//////////////
// Includes
#include "Clause.h"
#include "Random.h"
#include "SATInstance.h"
#include "SATSolver.h"

/////////////
// Defines

/////////////////////////////
// Static data initialization 

using namespace std;

SATInstance SATInstance::xSATInstance;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Public Methods

void SATInstance::vOutput()
{
  for (int i=0; i<_iClauseCount; i++) {
    Clause* pPrintMe = _aClause[i];
    for (int j=0; j < pPrintMe->iVariableCount(); j++) {
      if (pPrintMe->bIsNegated(j))
	cout << "-";
      cout << (int) (pPrintMe->eConstrainedVariable(j)+1) << " "; 
    }
    cout << '\n';
  }
  cout << "%\n";
}

void SATInstance::vOutput(ofstream &Out)
{
  for (int i=0; i<_iClauseCount; i++) {
    Clause* pPrintMe = _aClause[i];
    for (int j=0; j < pPrintMe->iVariableCount(); j++) {
      if (pPrintMe->bIsNegated(j))
	Out << "-";
      Out << (int) (pPrintMe->eConstrainedVariable(j)+1) << " "; 
    }
    Out << '\n';
  }
  Out << "%\n";
}



void SATInstance::vOutputDimacs()
{
  cout << "p cnf " << iVariableCount << ' ' << _iClauseCount << '\n';
  for (int i=0; i<_iClauseCount; i++) {
    Clause* pPrintMe = _aClause[i];
    for (int j=0; j < pPrintMe->iVariableCount(); j++) {
      if (pPrintMe->bIsNegated(j))
	cout << "-";
      cout << (int) (pPrintMe->eConstrainedVariable(j)+1) << " "; 
    }
    cout << " 0\n";
  }
  cout << flush;
}

boolean SATInstance::bReadDimacs(char* aFileName_)
{
  ifstream xInputFile(aFileName_);
  return bReadDimacs(xInputFile);
}

boolean SATInstance::bReadDimacs(istream& xInputFile)
{
  char buffer[5000];
  VariableID eMaxVar = 0;
  int iClauseCount;
  char cCheck;

  VariableSet xVariables;
  VariableSet xNegatedVariables;
  while (1) {
    xInputFile >> cCheck;
    if (cCheck == 'c') {
      xInputFile.getline(buffer, 5000);
      continue;
    }
    else if (cCheck == 'p') {
      xInputFile >> buffer;
      xInputFile >> eMaxVar;
      xInputFile >> iClauseCount;
      if (eMaxVar > MAX_VARIABLES) {
	cout << "Error: Maximum variables allowed is " << MAX_VARIABLES << ".\n";
	return 0;
      }
      break;
    }
    else {
      cout << "Error: File not in DIMACS format.\n";
      return 0;
    }
  }
  iVariableCount = eMaxVar;
  int iWorkCount = 0;
  while (1) {
    xInputFile >> cCheck;
    if (cCheck == 'c') {
      xInputFile.getline(buffer, 5000);
      continue;
    }
    else xInputFile.putback(cCheck);

    xVariables.vClear();
    xNegatedVariables.vClear();
    do {
      VariableID eVar;
      xInputFile >> eVar;
      if (eVar == 0)
	break;
      if(eVar > eMaxVar){
	cout << "Error: some variable is numbered larger than the maximum.\n";
	return 0;
      }
      if (eVar < 0) {
	if (xVariables.bAddVariable(0-(eVar+1)) == 0) {
	  cout << "Error: Some clause contains duplicate variables.\n";
	  cout << eVar << endl;
	  return 0;
	}
	xNegatedVariables.vAddVariable(0-(eVar+1));
      }
      else {
	if (xVariables.bAddVariable(eVar-1) == 0) {
	  cout << "Error: Some clause contains duplicate variables.\n";
	  return 0;
	}
      }
    } while (1);
    if (xVariables.iVariableCount() == 0) {
      cout << "Error: encountered a 0 length clause \n"; 
      return 0;
    }

    Clause* pNewConstraint = new Clause(xVariables, xNegatedVariables, 1);
    SATInstance::xSATInstance.vAddClause(pNewConstraint);
    iWorkCount++;
    if (iWorkCount == iClauseCount)
      break;
  }
  return 1;
}


boolean SATInstance::bReadDimacs(VariableID eMaxVar, int iClauseCount, VariableID * CnfArray)
{
    char buffer[5000];

    VariableSet xVariables;
    VariableSet xNegatedVariables;

    iVariableCount = eMaxVar;
    int iWorkCount = 0;
    while (1) {

	xVariables.vClear();
	xNegatedVariables.vClear();


	do {
	    VariableID eVar;
	    eVar = *(CnfArray++);

	    if (eVar == 0)
		break;
	    if(eVar > eMaxVar){
		cout << "Error: some variable is numbered larger than the maximum.\n";
		return 0;
	    }
	    if (eVar < 0) {
		if (xVariables.bAddVariable(0-(eVar+1)) == 0) {
		    cout << "Error: Some clause contains duplicate variables.\n";
		    cout << eVar << endl;
		    return 0;
		}
		xNegatedVariables.vAddVariable(0-(eVar+1));
	    }
	    else {
		if (xVariables.bAddVariable(eVar-1) == 0) {
		    cout << "Error: Some clause contains duplicate variables.\n";
		    return 0;
		}
	    }
	} while (1);
	
	if (xVariables.iVariableCount() == 0) {
	    cout << "Error: encountered a 0 length clause \n"; 
	    return 0;
	}

	Clause* pNewConstraint = new Clause(xVariables, xNegatedVariables, 1);
	SATInstance::xSATInstance.vAddClause(pNewConstraint);
	iWorkCount++;
	if (iWorkCount == iClauseCount)
	    break;
    }
    return 1;
}





///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Protected Methods

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Private Methods

#include <stdlib.h>
#include <fstream>
#include "LightweightTypes.h"

using namespace std;

int CASize = 10000;

void LoadCnf (int *wff, VariableID nvarsptr, int nclausesptr, 
	     VariableID ** dataptr)
{
    VariableID * CnfArray;
    int filled = 0;
    CnfArray = (VariableID *)malloc((size_t)(sizeof(VariableID)*CASize));

    // ifstream xInputFile(FileName);
    
    // char buffer[5000];
    // VariableID eMaxVar;
    // int iClauseCount;
    // char cCheck;
    
    /*
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
	    break;
	}
	else {
	    cout << "Error: File not in DIMACS format.\n";
	    exit(-1);
	}
    }
    int iWorkCount = 0;
    while (1) {
	xInputFile >> cCheck;
	if (cCheck == 'c') {
	    xInputFile.getline(buffer, 5000);
	    continue;
	}
	else xInputFile.putback(cCheck);

	do {
	    if (filled >= CASize){
		CASize *= 2;
		CnfArray = (VariableID *)realloc(CnfArray, (size_t)(sizeof(VariableID)*CASize));
	    }
	    VariableID eVar;
	    xInputFile >> eVar;
	    CnfArray[filled++] = eVar;
	    if (eVar == 0)
		break;
	} while (1);
	iWorkCount++;
	if (iWorkCount == iClauseCount)
	    break;
    }
    */

    int iWorkCount = 0;
    while (1) {
      do {
	if (filled >= CASize){
	  CASize *= 2;
	  CnfArray = (VariableID *)realloc(CnfArray, (size_t)(sizeof(VariableID)*CASize));
	}
	VariableID eVar = (VariableID)wff[filled];
	CnfArray[filled++] = eVar;
	if (eVar == 0)
	  break;
      } while (1);
      iWorkCount++;
      if (iWorkCount == nclausesptr)
	break;
    }
   
    // *nvarsptr = eMaxVar;
    // *nclausesptr = iClauseCount;
    *dataptr = CnfArray;
}

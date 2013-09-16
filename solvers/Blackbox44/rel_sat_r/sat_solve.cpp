/////////////////
// OS Includes
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string.h>

////////////////
// Commented out Jan 2003 - hak
// Includes from standard C libraries...
//#ifndef WIN32
//#include <sys/times.h>
//#include <sys/time.h>
//#include <unistd.h>
//#else
//#include "../win32/adns/adns.h"
//#endif

#include <sys/times.h>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>

// Why on earth did CLK_TCK disappear from time.h with g++ version 4.0?
#ifndef CLK_TCK
#ifdef CLOCKS_PER_SEC
#define CLK_TCK CLOCKS_PER_SEC
#else
#define CLK_TCK 60
#endif
#endif



#include <sys/types.h>
//////////////
// Includes
#include "ClauseList.h"
#include "Clause.h"
#include "Random.h"
#include "SATSolver.h"
#include "SATInstance.h"

#include "LoadCnf.h"
#include "../interface.h"

using namespace std;

/////////////
// Externs
extern int bb_first_k;
extern struct timeval tv;
// extern struct timezone tzp;

/////////////
// Globals

ofstream * PermanentFS;
ofstream * TemporaryFS;
bool RelevanceFlag = TRUE;
bool DumpFlag = FALSE;

/////////////
// Defines

int bb_satsolve_relsat(int numvar, int numclause, int * wff, int * soln, 
		       int maxtime, int iArgc_, char * aArgv_[])
{
    fprintf(STDMSG, "Invoking solver rel_sat_rand\n");

    /*
    if (iArgc_ < 2) {
	cout << "Use: rel_sat_r FILE.cnf {-seed N} {-maxsec N} {-maxbt N}" << endl <<
	    "    {-trials N} {-learnorder N} {-numsol N} {-nosol}" << endl <<
	    "    {-fudge N A B} {-norelevance} {-dump}" << endl;
	exit(1);
    } */

    long lClkTck = CLK_TCK;
    unsigned long lSeed;
    gettimeofday(&tv, 0);
    lSeed = (( tv.tv_sec & 0177 ) * 1000000) + tv.tv_usec;

    int iNumTrials = 10;
    int iNumSol = 1;
    boolean bPrintSol = TRUE;
    unsigned long lMaxTime = 0;
    float fTmp;
    unsigned long lMaxBt = 1000000;
    int iLearnOrder = 3;
    int iInputFileArg = 1;
    int iMaxToTry = 10;
    float fFudgeA = 0.8;
    float fFudgeB = 0.9;
    int a=0;
    while (++a < iArgc_){
	if (strcmp(aArgv_[a],"-seed")==0)
	    sscanf(aArgv_[++a], "%ld", &lSeed);
	else if (strcmp(aArgv_[a],"-maxsec")==0){
	    sscanf(aArgv_[++a], "%f", &fTmp);
	    lMaxTime = (unsigned long)(lClkTck * fTmp);
	}
	else if (strcmp(aArgv_[a],"-maxbt")==0)
	    sscanf(aArgv_[++a], "%ld", &lMaxBt);
	else if (strcmp(aArgv_[a],"-numsol")==0)
	    sscanf(aArgv_[++a], "%i", &iNumSol);
	else if (strcmp(aArgv_[a],"-trials")==0)
	    sscanf(aArgv_[++a], "%i", &iNumTrials);
	else if (strcmp(aArgv_[a],"-fudge")==0){
	    sscanf(aArgv_[++a], "%i", &iMaxToTry);
	    sscanf(aArgv_[++a], "%f", &fFudgeA);
	    sscanf(aArgv_[++a], "%f", &fFudgeB);
	}
	else if (strcmp(aArgv_[a],"-nosol")==0)
	    bPrintSol = FALSE;
	else if (strcmp(aArgv_[a],"-norelevance")==0)
	    RelevanceFlag = TRUE;
	else if (strcmp(aArgv_[a],"-dump")==0)
	    DumpFlag = TRUE;
	else
	    iInputFileArg = 0;
    }
    
    if (iInputFileArg <= 0) { 
      cout << 
	"Options for solver rel_sat_r are:\n" <<
"    -seed N = initialize random seed to N\n" <<
"    -maxbt N = End each trial after N backtracks\n" <<
"        N=0 just means perform no backtracking. Default = 1000000\n" <<
"    -trials N =  Try to solve the formula N times\n" <<
"    -learnorder N =  The maximum length of clauses to be \"permanently\"\n" <<
"        learned during a trial.  Each learned clause corresponds to a\n" <<
"        backtrack point, and is entailed by the original wff. Default = 3\n" <<
"    -norelevance = If set, do not perform relevance-bounded learning.\n" <<
"        Otherwise, backtrack points that correspond to entailed clauses\n" <<
"        are longer than the learnorder are temporarily added to the wff,\n" <<
"        until backtracking unassigns the other variables in the clause.\n" <<
"    -fudge N A B = The fudge-factors used to \"degrade\" the variable\n" <<
"        choice heuristic.  In the first step of choosing a branch\n" <<
"        variable, every variable is scored by the number of times it\n" <<
"        appears in a binary clause.  Up to N variables that are within A\n" <<
"        times the BEST value are selected. Then, each of these N\n" <<
"        variables is re-scored by actually counting how many unit props\n" <<
"        are performed if the variable is set.  During this stage, if it\n" <<
"        is discovered that if setting a particular variable leads to an\n" <<
"        inconsistency, then it is immediately choosen.  Otherwise, the\n" <<
"        set of all variables that are re-scored within B times the BEST\n" <<
"        re-score is determined, and a variable is randomly choosen from\n" <<
"        this set. Default = 10 .8 .9\n";
	exit(1);
    } 

    cout << "rel_sat_r 1.0" << endl <<
	// "instance: " << aArgv_[iInputFileArg] << endl <<
	"seed: " << lSeed << endl <<
	"cutoff seconds: "<< ((double)lMaxTime)/lClkTck << endl <<
	"cutoff backtracks: "<< lMaxBt << endl <<
	"fudge: " << iMaxToTry << " " << fFudgeA << " " << fFudgeB << endl <<
	"trials: " << iNumTrials << endl <<
	"learning: " << iLearnOrder << endl <<
	"number solutions: " << iNumSol << endl ;

    cout << "dump flag is " << DumpFlag << endl;

    if (DumpFlag){
	char FileP[512];
	char FileT[512];
	strcpy(FileP, aArgv_[iInputFileArg]);
	if (strlen(FileP)>4 && strcmp(&FileP[strlen(FileP)-4], ".cnf")==0)
	    FileP[strlen(FileP)-4] = 0;
	strcpy(FileT, FileP);
	strcat(FileP, "-perm.f");
	strcat(FileT, "-temp.f");
	PermanentFS = new ofstream(FileP);
	TemporaryFS = new ofstream(FileT);
    }

    Random::vInitRandom(lSeed);    

    boolean bFailed;
    int iSuccessCount = 0;
    boolean FinalResult;
    boolean bSolution;

    VariableID * pCnfArray = (VariableID *) wff;
    VariableID vNvars = (VariableID)numvar;
    int iNclauses = numclause;

    // LoadCnf(wff, vNvars, iNclauses, &pCnfArray);
    cout << "number variables: " << vNvars << endl;
    cout << "number clauses: " << iNclauses << endl << endl;
    // cout << "[trial] solver file result time backtracks branches assigns avg_choices seed\n" << endl;
    cout << "[trial] solver result time backtracks branches assigns avg_choices seed\n" << endl;

    SATSolver * xSATSolverPtr;

    for (int i=1; i<=iNumTrials; i++) {
	cout << "[" << i << "] Start trial" << endl;
	SATInstance::xSATInstance.vDestroy();
	/* if (!SATInstance::xSATInstance.bReadDimacs(aArgv_[iInputFileArg]))
	    exit(3); */

	if (!SATInstance::xSATInstance.bReadDimacs(vNvars, iNclauses, pCnfArray))
	    exit(3);

	SATSolver xSATSolver;
	xSATSolverPtr = &xSATSolver;
	bSolution = xSATSolver.bFindSolution(iLearnOrder, bFailed, lMaxTime, lMaxBt, iMaxToTry, fFudgeA, fFudgeB);

	if (! bFailed) { 
	    iSuccessCount++;
	    FinalResult = bSolution;
	    cout << "[" << i << "] SOLVED - instance is " << ( bSolution ? "satisfiable" : 
							       "unsatisfiable") << endl;
	}
	cout << "[" << i << "] rel_sat_r " << /* aArgv_[iInputFileArg] << */
	    ( bFailed ? " timeout " : ( bSolution ? " SAT " : " UNSAT ")) <<
	    ((double)xSATSolver.lElapsedTime()) / lClkTck << " " <<
	    xSATSolver.lBacktracks() << " " <<
	    xSATSolver.lBranchPointsExplored()  << " " <<
	    xSATSolver.lVariablesLabelled() << " " <<
	    xSATSolver.dAvgChoiceSize() << " " <<
	    lSeed << endl;
	if (iSuccessCount > 0 || bFailed == Timeout) 
	  break;
    }
    /* delete pCnfArray; */
    if (iSuccessCount)
      if (bSolution > 0) {
	cout << "The instance is " << (FinalResult ? "satisfiable" : "unsatisfiable") << endl;
	(*xSATSolverPtr).vSaveSoln(soln);
	return Sat;
      }
      else
	return Unsat;
    else
      return Timeout;
    /* cout << endl << "Success rate: " << ((double)iSuccessCount)  / iNumTrials << endl; 
    if (bPrintSol && iSuccessCount > 0 && FinalResult){
	(* xSATSolverPtr).vPrintSoln();
    } */
}



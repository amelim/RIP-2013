# Microsoft Developer Studio Generated NMAKE File, Based on blackbox.dsp
!IF "$(CFG)" == ""
CFG=blackbox - Win32 Debug
!MESSAGE No configuration specified. Defaulting to blackbox - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "blackbox - Win32 Release" && "$(CFG)" != "blackbox - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "blackbox.mak" CFG="blackbox - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "blackbox - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "blackbox - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "blackbox - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\blackbox.exe"


CLEAN :
	-@erase "$(INTDIR)\bbio.obj"
	-@erase "$(INTDIR)\bbpddl.tab.obj"
	-@erase "$(INTDIR)\control.obj"
	-@erase "$(INTDIR)\dummy.obj"
	-@erase "$(INTDIR)\graph2wff.obj"
	-@erase "$(INTDIR)\graphplan.obj"
	-@erase "$(INTDIR)\hash.obj"
	-@erase "$(INTDIR)\justify.obj"
	-@erase "$(INTDIR)\learn.obj"
	-@erase "$(INTDIR)\lex.yy.obj"
	-@erase "$(INTDIR)\planner.obj"
	-@erase "$(INTDIR)\sat_solver.obj"
	-@erase "$(INTDIR)\tim.obj"
	-@erase "$(INTDIR)\utilities.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\verify.obj"
	-@erase "$(OUTDIR)\blackbox.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /I "C:\Program Files\adns\Include\\" /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D VERSION=4.0 /D "MSDOS" /Fp"$(INTDIR)\blackbox.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\blackbox.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:no /pdb:"$(OUTDIR)\blackbox.pdb" /machine:I386 /out:"$(OUTDIR)\blackbox.exe" 
LINK32_OBJS= \
	"$(INTDIR)\bbio.obj" \
	"$(INTDIR)\bbpddl.tab.obj" \
	"$(INTDIR)\control.obj" \
	"$(INTDIR)\dummy.obj" \
	"$(INTDIR)\graph2wff.obj" \
	"$(INTDIR)\graphplan.obj" \
	"$(INTDIR)\hash.obj" \
	"$(INTDIR)\justify.obj" \
	"$(INTDIR)\learn.obj" \
	"$(INTDIR)\lex.yy.obj" \
	"$(INTDIR)\planner.obj" \
	"$(INTDIR)\sat_solver.obj" \
	"$(INTDIR)\tim.obj" \
	"$(INTDIR)\utilities.obj" \
	"$(INTDIR)\verify.obj"

"$(OUTDIR)\blackbox.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "blackbox - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\blackbox.exe"


CLEAN :
	-@erase "$(INTDIR)\bbio.obj"
	-@erase "$(INTDIR)\bbpddl.tab.obj"
	-@erase "$(INTDIR)\control.obj"
	-@erase "$(INTDIR)\dummy.obj"
	-@erase "$(INTDIR)\graph2wff.obj"
	-@erase "$(INTDIR)\graphplan.obj"
	-@erase "$(INTDIR)\hash.obj"
	-@erase "$(INTDIR)\justify.obj"
	-@erase "$(INTDIR)\learn.obj"
	-@erase "$(INTDIR)\lex.yy.obj"
	-@erase "$(INTDIR)\planner.obj"
	-@erase "$(INTDIR)\sat_solver.obj"
	-@erase "$(INTDIR)\tim.obj"
	-@erase "$(INTDIR)\utilities.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\verify.obj"
	-@erase "$(OUTDIR)\blackbox.exe"
	-@erase "$(OUTDIR)\blackbox.ilk"
	-@erase "$(OUTDIR)\blackbox.map"
	-@erase "$(OUTDIR)\blackbox.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /I "C:\Program Files\adns\Include\\" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D VERSION=4.0 /D "MSDOS" /Fp"$(INTDIR)\blackbox.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\blackbox.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /incremental:yes /pdb:"$(OUTDIR)\blackbox.pdb" /map:"$(INTDIR)\blackbox.map" /debug /machine:I386 /out:"$(OUTDIR)\blackbox.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\bbio.obj" \
	"$(INTDIR)\bbpddl.tab.obj" \
	"$(INTDIR)\control.obj" \
	"$(INTDIR)\dummy.obj" \
	"$(INTDIR)\graph2wff.obj" \
	"$(INTDIR)\graphplan.obj" \
	"$(INTDIR)\hash.obj" \
	"$(INTDIR)\justify.obj" \
	"$(INTDIR)\learn.obj" \
	"$(INTDIR)\lex.yy.obj" \
	"$(INTDIR)\planner.obj" \
	"$(INTDIR)\sat_solver.obj" \
	"$(INTDIR)\tim.obj" \
	"$(INTDIR)\utilities.obj" \
	"$(INTDIR)\verify.obj"

"$(OUTDIR)\blackbox.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("blackbox.dep")
!INCLUDE "blackbox.dep"
!ELSE 
!MESSAGE Warning: cannot find "blackbox.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "blackbox - Win32 Release" || "$(CFG)" == "blackbox - Win32 Debug"
SOURCE=..\bbio.c

"$(INTDIR)\bbio.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\bbpddl.tab.c

"$(INTDIR)\bbpddl.tab.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\control.c

"$(INTDIR)\control.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\dummy.c

"$(INTDIR)\dummy.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\graph2wff.c

"$(INTDIR)\graph2wff.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\graphplan.c

"$(INTDIR)\graphplan.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\hash.c

"$(INTDIR)\hash.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\justify.c

"$(INTDIR)\justify.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\learn.c

"$(INTDIR)\learn.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\lex.yy.c

"$(INTDIR)\lex.yy.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\planner.c

"$(INTDIR)\planner.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\sat_solver.cpp

"$(INTDIR)\sat_solver.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\tim.c

"$(INTDIR)\tim.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\utilities.c

"$(INTDIR)\utilities.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\verify.c

"$(INTDIR)\verify.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 


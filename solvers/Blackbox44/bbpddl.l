%{
/*****************************************************************/ 
/*  Strict Strips PDDL lexical analyzer for BlackBox             */
/*****************************************************************/
#include "graphplan.h"
#include "control.h"
#include "bbpddl.tab.cpp.h"

int yylineno = 0;

%}

ID [.a-zA-Z0-9_=\-]+ 
VAR "?"{ID}
comment ;.*$

%option caseless
%option noyywrap

%%
"(" {return '(';}
")" {return ')';}
"define" { return DEFINE; }
"domain" { return DOMAIN; }
"defpredicate" { return DEFPREDICATE; }
"requirements" { return REQUIREMENTS; }
"constants" { return CONSTANTS; }
"types" { return TYPES; }
"predicates" { return PREDICATES; }
"action" { return ACTION; }
"parameters" { return PARAMETERS; }
"precondition" { return PRECONDITION; }
"effect" { return EFFECT; }
"and" { return AND; }
"not" { return NOT; }
"problem" { return PROBLEM; }
"objects" { return OBJECTS; }
"init" { return INIT; }
"goal" { return GOAL; }
"length" { return (LENGTH);}
"serial" { return (SERIAL);}
"parallel" {return (PARALLEL);}
"exists" { return EXISTS; }
"noexists" { return NOEXISTS; }
"either" { return EITHER; }
"fluent" { return FLUENT; }
"exclude" { return EXCLUDE; }
"wffctrl" { return WFFCTRL; }
"scope" { return SCOPE; }
"forall" { return FORALL; }
"next" { return NEXT; }
"body" { return BODY; }

"control" { return CONTROL; }
"-" { return '-'; }
":" { return ':'; }

{ID} { return ID; }
{VAR} {return VAR; }

[ \t]+ ;
{comment} ;
\n yylineno++;

%%


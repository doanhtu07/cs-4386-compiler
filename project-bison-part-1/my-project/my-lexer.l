%{
#include "my-parser.tab.h"
%}

blanks                                [ \t\r\n]+
identifier		                        [A-Z][A-Z0-9]*
number                                [1-9][0-9]*|0
boollit                               "false"|"true"

%%

{blanks}                              { /* ignore */ }

"("                                   return(LP);
")"                                   return(RP);
":="                                  return(ASGN);
";"                                   return(SC);
"*"|"div"|"mod"                       return(OP2);
"+"|"-"                               return(OP3);
"="|"!="|"<"|">"|"<="|">="            return(OP4);

"if"                                  return(IF);
"then"                                return(THEN);
"else"                                return(ELSE);
"begin"                               return(START);
"end"                                 return(END);
"while"                               return(WHILE);
"do"                                  return(DO);
"program"                             return(PROGRAM);
"var"                                 return(VAR);
"as"                                  return(AS);
"int"                                 return(INT);
"bool"                                return(BOOL);

"writeInt"                            return(WRITEINT);
"readInt"                             return(READINT);

{identifier}                          return(IDENTIFIER);
{number}                              return(NUMBER);
{boollit}                             return(BOOLLIT);

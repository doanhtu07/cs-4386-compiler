%{
#include <stdio.h>
int yylex(void);
void yyerror(const char *);
%}

// %debug

// Symbols.
%token LP
%token RP
%token ASGN
%token SC
%token OP2
%token OP3
%token OP4

%token IF
%token THEN
%token ELSE
%token START
%token END
%token WHILE
%token DO
%token PROGRAM
%token VAR
%token AS
%token INT
%token BOOL

%token WRITEINT
%token READINT

%token IDENTIFIER
%token NUMBER
%token BOOLLIT

%start program

%%

program:
  PROGRAM
    declarations 
  START 
    statementSequence
  END
;

declarations:
  VAR IDENTIFIER AS type SC 
  declarations
  |
  /* empty */
;

type:
  INT
  |
  BOOL
;

statementSequence:
  statement SC
  statementSequence
  |
  /* empty */
;

statement:
  assignment
  |
  ifStatement
  |
  whileStatement
  |
  writeInt
;

assignment:
  IDENTIFIER ASGN expression
  |
  IDENTIFIER ASGN READINT
;

ifStatement:
  IF expression THEN
    statementSequence
  elseClause
  END
;

elseClause:
  ELSE
    statementSequence
  |
  /* empty */
;

whileStatement:
  WHILE expression DO
    statementSequence
  END
;

writeInt:
  WRITEINT expression
;

expression: 
  simpleExpression OP4 simpleExpression
  |
  simpleExpression
;

simpleExpression: 
  term OP3 term
  |
  term
;

term: 
  factor OP2 factor
  |
  factor
;

factor: 
  LP expression RP
  |
  IDENTIFIER
  |
  NUMBER
  |
  BOOLLIT
;

%%

void yyerror(const char *s) {
  fprintf(stderr, "Error: %s\n", s);
}

int main(void) {
  // yydebug = 1;
  int result = yyparse();
  printf("FINISH\n");
  return result;
}

int yywrap() {
  return 1; /* EOF: Indicates that there is no more input */
}

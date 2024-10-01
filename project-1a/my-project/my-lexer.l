%{
int num_lines = 0, num_chars = 0;
%}

%%
[1-9][0-9]*|0   { printf("num"); printf(" "), printf(yytext), printf("\n"); }
false|true      { printf("boollit"); printf(" "), printf(yytext), printf("\n"); }
[A-Z][A-Z0-9]*  { printf("ident"); printf(" "), printf(yytext), printf("\n"); }

\(              { printf("LP"); printf(" "), printf(yytext), printf("\n"); }
\)              { printf("RP"); printf(" "), printf(yytext), printf("\n"); }
:=              { printf("ASGN"); printf(" "), printf(yytext), printf("\n"); }
;               { printf("SC"); printf(" "), printf(yytext), printf("\n"); }
\*|div|mod      { printf("OP2"); printf(" "), printf(yytext), printf("\n"); }
\+|-            { printf("OP3"); printf(" "), printf(yytext), printf("\n"); }
=|!=|<|>|<=|>=  { printf("OP4"); printf(" "), printf(yytext), printf("\n"); }

if              { printf("IF"); printf(" "), printf(yytext), printf("\n"); }
then            { printf("THEN"); printf(" "), printf(yytext), printf("\n"); }
else            { printf("ELSE"); printf(" "), printf(yytext), printf("\n"); }
begin           { printf("BEGIN"); printf(" "), printf(yytext), printf("\n"); }
end             { printf("END"); printf(" "), printf(yytext), printf("\n"); }
while           { printf("WHILE"); printf(" "), printf(yytext), printf("\n"); }
do              { printf("DO"); printf(" "), printf(yytext), printf("\n"); }
program         { printf("PROGRAM"); printf(" "), printf(yytext), printf("\n"); }
var             { printf("VAR"); printf(" "), printf(yytext), printf("\n"); }
as              { printf("AS"); printf(" "), printf(yytext), printf("\n"); }
int             { printf("INT"); printf(" "), printf(yytext), printf("\n"); }
bool            { printf("BOOL"); printf(" "), printf(yytext), printf("\n"); }

writeInt        { printf("WRITEINT"); printf(" "), printf(yytext), printf("\n"); }
readInt         { printf("READINT"); printf(" "), printf(yytext), printf("\n"); }

\n              { 
                    // printf("newline\n"); 
                }

[ \t\r]+        { 
                    // printf("whitespace\n");
                };
%%

int main ()
{
    yylex();
    return 0;
}

int yywrap(void) {
    return 1;  /* Required by Flex, indicates end of input */
}

%{
int num_lines = 0, num_chars = 0;
%}

%%
\n	++num_lines; ++num_chars;
.	++num_chars;
%%

int main ()
{
    yylex();
    printf("There were %d lines and %d characters.\n", num_lines, num_chars);
    return 0;
}

int yywrap(void) {
    return 1;  /* Required by Flex, indicates end of input */
}
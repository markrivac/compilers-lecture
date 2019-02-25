%{
#include <stdio.h>
%}
%%
f                                   printf("floatdcl");
i                                   printf("intdcl");
p                                   printf("print");
[aA-eE]|[gG-hH]|[jJ-oO]|[qQ-zZ]     printf("id");
=                                   printf("assign");
\+                                  printf("plus");
-                                   printf("minus");
([0-9]+[.][0-9]{0,5})               printf("fnum");
[0-9]+                              printf("inum");
^\/\/.*                             printf("comment");
%%
int main(int argc, char **argv) {
    FILE    *fd;

    if (argc == 2)
    {
        if (!(fd = fopen(argv[1], "r")))
        {
            perror("Error: ");
            return (-1);
        }
        yyset_in(fd);
        yylex();
        fclose(fd);
    }
    else
        printf("Usage: a.out filename\n");
    return (0);
}

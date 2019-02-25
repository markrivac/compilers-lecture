// Author: Mark Octavio Rivera Acosta
// Help from: https://docs.google.com/presentation/d/1KE89YKtU4IDtK5locxnlciRHkWltg9VG_C42ORVR7WI/edit#slide=id.g4c138bf21c_0_862
// Help from: https://cboard.cprogramming.com/c-programming/4198-reading-files-token-token.html
// Help from: https://stackoverflow.com/questions/3501338/c-read-file-line-by-line
// Help from: https://regexr.com/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <regex.h>
#define _GNU_SOURCE

int main(int argc, char *argv[])
{

    FILE *fp, *out_file;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    char *test_msg = NULL;
    char *p;
    char *delim = " ";
    //char *tokens[999999];
    const char *floatdcl = "f";
    const char *intdcl = "i";
    const char *print = "p";
    const char *id = "[a-e]|[g-h]|[j-o]|[q-z]";
    const char *assign = "=";
    const char *plus = "+";
    const char *minus = "-";
    const char *inum = "[0-9]+";
    const char *fnum = "([0-9]+[.][0-9]{0,5})";
    const char *comment = "^\\/\\/.*";
    int i = 0;

    fp = fopen(argv[1], "r");
    out_file = fopen("lex.out", "w");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    while ((read = getline(&line, &len, fp)) != -1)
    {
        test_msg = line;
        p = strtok(test_msg, delim);
        while (p)
        {
            if (match(p, comment)){
                break;
            }
            else if (match(p, floatdcl))
            {
                p = "floatdcl";
            }
            else if (match(p, intdcl))
            {
                p = "intdcl";
            }
            else if (match(p, print))
            {
                p = "print";
            }
            else if (match(p, id))
            {
                p = "id";
            }
            else if (match(p, assign))
            {
                p = "assign";
            }
            else if (match(p, plus))
            {
                p = "plus";
            }
            else if (match(p, minus))
            {
                p = "minus";
            }
            else if (match(p, fnum))
            {
                p = "fnum";
            }
            else if (match(p, inum))
            {
                p = "inum";
            }

            printf("%s ", p);
            p = strtok(NULL, delim);
            i++;
        }
        //tokens[i] = "\n";
        printf("%s","\n");
        i++;
    }
    // for (int j = 0; j < i; j++)
    // {
    //     fprintf(out_file, "%s ", tokens[j]);
    // }

    // fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}

int match(const char *string, const char *pattern)
{
    regex_t re;
    if (regcomp(&re, pattern, REG_EXTENDED | REG_NOSUB) != 0)
        return 0;
    int status = regexec(&re, string, 0, NULL, 0);
    regfree(&re);
    if (status != 0)
        return 0;
    return 1;
}
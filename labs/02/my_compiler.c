#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int lines = 0;
    int brace_counter = 0;
    int bracket_counter = 0;
    int parent_counter = 0;
    int error_line = 0;
    int error = 0;
    int is_string = 0;
    int is_char = 0;
    int last_open_brace = 0;
    int last_close_brace = 0;
    int last_open_bracket = 0;
    int last_close_bracket = 0;
    int last_open_parent = 0;
    int last_close_parent = 0;
    int last_open_squote = 0;
    int last_open_dquote = 0;

    fp = fopen(argv[1], "r");

    char lines_table[10][100];
    if (fp == NULL)
    {
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fp)) != -1)
    {
        lines = lines + 1;
        strcpy(lines_table[lines], line);
    }

    int lines_in_lines_table = sizeof(lines_table) / sizeof(lines_table[0]);

    for (size_t i = lines - 1; i < lines_in_lines_table; i++)
    {
        strcpy(lines_table[i], "");
    }

    for (size_t i = 0; i < lines_in_lines_table; i++)
    {
        for (size_t j = 0; j < strlen(lines_table[i]); j++)
        {
            if ('{' == lines_table[i][j] && !is_string && !is_char)
            {
                brace_counter++;
                last_open_brace = i;
            }
            else if ('}' == lines_table[i][j] && !is_string && !is_char)
            {
                brace_counter--;
                last_close_brace = i;
            }
            else if ('(' == lines_table[i][j] && !is_string && !is_char)
            {
                parent_counter = parent_counter + 1;
                last_open_parent = i;
            }
            else if (')' == lines_table[i][j] && !is_string && !is_char)
            {
                parent_counter = parent_counter - 1;
                last_close_parent = i;
            }
            else if ('[' == lines_table[i][j] && !is_string && !is_char)
            {
                bracket_counter++;
                last_open_bracket = i;
            }
            else if (']' == lines_table[i][j] && !is_string && !is_char)
            {
                bracket_counter--;
                last_close_bracket = i;
            }
            else if ('\'' == lines_table[i][j] && !is_string)
            {
                is_char = !is_char;
                int last_open_squote = 0;
            }
            else if ('\"' == lines_table[i][j] && !is_char)
            {
                is_string = !is_string;
                int last_open_dquote = 0;
            }
            else if ('/' == lines_table[i][j] && '/' == lines_table[i][j + 1] && !is_string && !is_char)
            {
                break;
            }
        }
    }

    if (brace_counter != 0 || bracket_counter != 0 || parent_counter != 0 || is_char || is_string)
    {
        error = 1;
    }

    if (error)
    {
        printf("%s", "there's an error in your code\n");
        if (is_string)
        {
            printf("%s%i%s", "You're missing a \" on line ", last_open_dquote, "\n");
        }
        else if (is_char)
        {
            printf("%s%i%s", "You're missing a \' on line ", last_open_squote, "\n");
        }
        else if (brace_counter > 0)
        {
            printf("%s%i%s", "You're missing a \"}\" for the one on line ", last_open_brace, "\n");
        }
        else if (brace_counter < 0)
        {
            printf("%s%i%s", "You're missing a \"{\" for the one on line ", last_close_brace, "\n");
        }
        else if (parent_counter > 0)
        {
            printf("%s%i%s", "You're missing a \")\" for the one on line ", last_open_parent, "\n");
        }
        else if (parent_counter < 0)
        {
            printf("%s%i%s", "You're missing a \"(\" for the one on line ", last_close_parent, "\n");
        }
        else if (bracket_counter > 0)
        {
            printf("%s%i%s", "You're missing a \"]\" for the one on line ", last_open_bracket, "\n");
        }
        else if (bracket_counter < 0)
        {
            printf("%s%i%s", "You're missing a \"[\" for the one on line ", last_close_bracket, "\n");
        }
    }

    // printf("%s%i", "brace counter: ", brace_counter);
    // printf("\n");
    // printf("%s%i", "bracket counter: ", bracket_counter);
    // printf("\n");
    // printf("%s%i", "parent counter: ", parent_counter);
    // printf("\n");
    // printf("%s%i", "char counter: ", is_char);
    // printf("\n");
    // printf("%s%i", "string counter: ", is_string);
    // printf("\n");

    if (line)
        free(line);
    fclose(fp);
    exit(EXIT_SUCCESS);
}
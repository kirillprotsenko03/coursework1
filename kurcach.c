/*Term paper for the first semester of programming*/


#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#define MAXLENGHT 10000


void greetings();
void get_path(char[]);
void file_treatment(char[]);
void comment_replace(FILE*, char*);
int file_lines_count(char*);
bool is_continue();


int main()
{
    bool program_working;
    char path[1000];

    greetings();
    program_working = true;
    while(program_working)  /* program will work while user has files to replace C++ comments */
    {
        get_path(path);
        file_treatment(path);
        program_working = is_continue();
    }
    return 0;
}


void greetings()  /* greet user and explain how to use this program */
{
    printf("Hello, it's a program to replace C++ comment // to C comment /* */\n");
}

void get_path(char path[])  /* get file path from cmd and return it */
{
    printf("You need to print here name of your file, file should be in the folder of that program\n");
    scanf("%s", path);
}


void file_treatment(char path[])
{

    FILE *file;
    int i;
    int lines_amount;
    char **text;
    lines_amount = file_lines_count(path);
    text = (char**)malloc(sizeof(char*)*lines_amount);
    file = fopen(path, "r");

    for(i=0; i<lines_amount; i++)
    {

        text[i] = (char*)malloc(sizeof(char)*MAXLENGHT);
        fgets(text[i], MAXLENGHT, file);
    }

    fclose(file);
    file = fopen(path, "w");
    for(i=0; i<lines_amount; i++) /* for each line of text replace comment(if exist) */
    {
        comment_replace(file, text[i]);
    }
    free(text);
    fclose(file);
}


void comment_replace(FILE *file, char *str)
{
    int i;
    bool previos;
    previos = false;
    for(i=1; i<strlen(str); i++)
    {
        if(str[i] == '/' && str[i-1] == '/' && !previos)
        {
            str[i] = '*';
            previos = true;
            printf("%s", str);
            strncat(str, "*/", 2);
        }
    }
    fputs(str, file);
}

int file_lines_count(char *path)
{
    FILE *file;
    int lines_count;
    lines_count = 0;
    file = fopen(path, "r");
    while (!feof(file))
    {
        if (fgetc(file) == '\n')
            lines_count++;
    }
    fclose(file);
    return lines_count;

}

bool is_continue()  /* ask if user have another file to replace comments */
{
    int answer;
    bool flag;

    printf("Do you want to change some files?\n");
    flag = true;
    while(flag)
    {
        printf("If yes [1]\n");
        printf("If no [0]\n");
        scanf("%d", &answer);
        if(answer == 0 || answer == 1) flag = false;
    }
    return (bool)answer;
}

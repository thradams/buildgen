#include <stdio.h>
#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#include <direct.h>
#include <sys/types.h>
#include <sys/stat.h>
#define rmdir _rmdir
#define mkdir(A, B)  _mkdir(A)
#define chdir  _chdir
#endif


//create projeto1

void write_file(const char* text, int textsize, const char* filename)
{
    FILE* f = fopen(filename, "wb");
    if (f)
    {
        fwrite(text, textsize - 1, 1, f);
        fclose(f);
    }
}

struct file {
    char* content;
    char* dest;
};

struct file files[] = {

    {
        .content = (char[]){
        #include "build.template.c.include"
        ,0}, .dest = "build.c"
    },

    {
        .content = (char[]){
        #include "build.template.h.include"
        ,0}, .dest = "build.h"
    },

    {
        .content = (char[]){
        #include "main.template.c.include"
        ,0}, .dest = "main.c"
    },

    {
        .content = (char[]){
        #include "file1.template.c.include"
        ,0}, .dest = "file1.c"
    },

    {
        .content = (char[]){
        #include "file1.template.h.include"
        ,0}, .dest = "file1.h"
    },

    {
        .content = (char[]){
        #include "readme.template.md.include"
        ,0}, .dest = "readme.md"
    },

    {
        .content = (char[]){
        #include "unit_test.template.h.include"
        ,0}, .dest = "unit_test.h"
    },


    {
        .content = (char[]){
        #include "maketest.template.c.include"
        ,0}, .dest = "./tools/maketest.c"
    },

    {
        .content = (char[]){
        #include "embed.template.c.include"
        ,0}, .dest = "./tools/embed.c"
    },

    {
        .content = (char[]){
        #include "amalgamator.template.c.include"
        ,0}, .dest = "./tools/amalgamator.c"
    },

    {
        .content = (char[]){
        #include "hoedown.template.c.include"
        ,0}, .dest = "./tools/hoedown.c"
    },
};

int main(int argc, char** argv)
{
#define STR \
"  ____          _  _      _   _____              \n"\
" |  _ \\        (_)| |    | | / ____|             \n"\
" | |_) | _   _  _ | |  __| || |  __   ___  _ __  \n"\
" |  _ < | | | || || | / _` || | |_ | / _ \\| '_ \\ \n"\
" | |_) || |_| || || || (_| || |__| ||  __/| | | |\n"\
" |____/  \\__,_||_||_| \\__,_| \\_____| \\___||_| |_|\n"\
"                                                 \n"

    printf(STR);

    if (argc < 2)
    {
        printf("Usage:\n");
        printf("  buildgen projectname\n");
        return;
    }

    printf("Generating '%s'", argv[1]);

    /*create folder name*/
    mkdir(argv[1], 0);
    chdir(argv[1]);
    mkdir("tools", 0);


    for (int i = 0; i < sizeof(files) / sizeof(files[0]); i++)
    {
        write_file(files[i].content, strlen(files[i].content), files[i].dest);
    }


    printf("Tips:\n");
    printf("Compiling on windows:\n");
    printf("cl build.c && build\n");
}

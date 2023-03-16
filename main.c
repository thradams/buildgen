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
    FILE* f = fopen(filename, "w");
    if (f)
    {
        fwrite(text, textsize - 1, 1, f);
        fclose(f);
    }
}

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
        printf("usage:\nbuildtool projectname");
        return;
    }

    printf("Generating '%s'", argv[1]);

    /*create folder name*/
    mkdir(argv[1], 0);
    chdir(argv[1]);
    mkdir("tools", 0);

    char build_c_text[] = {
    #include "build.template.c.include"
    ,0 };
    write_file(build_c_text, sizeof build_c_text, "build.c");

    char build_h_text[] = {
        #include "build.template.h.include"
        ,0 };
    write_file(build_h_text, sizeof build_h_text, "build.h");

    char main_c_text[] = {
        #include "main.template.c.include"
        ,0 };
    write_file(main_c_text, sizeof main_c_text, "main.c");


    char maketest_c_text[] = {
        #include "maketest.template.c.include"
        ,0 };
    write_file(maketest_c_text, sizeof maketest_c_text, "./tools/maketest.c");

    char embed_c_text[] = {
        #include "embed.template.c.include"
        ,0 };
    write_file(embed_c_text, sizeof embed_c_text, "./tools/embed.c");

    char amalgamator_c_text[] = {
        #include "amalgamator.template.c.include"
        ,0 };
    write_file(amalgamator_c_text, sizeof amalgamator_c_text, "./tools/amalgamator.c");


    char unit_test_h_text[] = {
    #include "unit_test.template.h.include"
    ,0 };
    write_file(unit_test_h_text, sizeof unit_test_h_text, "unit_test.h");

    char file1_c_text[] = {
        #include "file1.template.c.include"
        ,0 };
    write_file(file1_c_text, sizeof file1_c_text, "file1.c");

    char file1_h_text[] = {
        #include "file1.template.h.include"
        ,0 };
    write_file(file1_h_text, sizeof file1_h_text, "file1.h");


    printf("Tips:\n");
    printf("Compiling on windows:\n");
    printf("cl build.c && build\n");
}

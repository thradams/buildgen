
#include "build.h"
#include <stdio.h>


#define OUTPUT "hello.exe"

/*
*  List of all source files to compile
*/
#define SOURCE_FILES \
" main.c " \
" file1.c "

void compile_tools();
void compile_embed();
void generate_tests();
void compile_project();
void clearall();
void process_markdown(const char* mdfilename, const char* outfile);

int main()
{
    /*first we compile the tools we need*/
    compile_tools();

    /*we convert files to be used like #embed*/
    compile_embed();

    /*we now generate the test*/
    generate_tests();

    /*process markdown files*/
    process_markdown("readme.md", "readme.html");

    /*compile project*/
    compile_project();

#ifdef TEST
    /*
     * We run your program that has been compiled in test mode
    */

    int test_result = system(RUN OUTPUT);
    if (test_result)
    {
        printf("\n");
        printf(RED "TESTS FAILED "  OUTPUT " exit code %d\n", test_result);
        printf(RESET);
    }
#endif
    clearall();
}



void compile_tools()
{
    printf(CC_DESCRIPTION "\n");
    printf("Building tools-------------------------------------------\n");
    chdir("./tools");
    if (system(CC " -D_CRT_SECURE_NO_WARNINGS maketest.c " OUT_OPT "../maketest.exe") != 0) exit(1);
    if (system(CC " -D_CRT_SECURE_NO_WARNINGS amalgamator.c "  OUT_OPT "../amalgamator.exe") != 0) exit(1);
    if (system(CC " -D_CRT_SECURE_NO_WARNINGS embed.c " OUT_OPT "../embed.exe") != 0) exit(1);
    if (system(CC " -D_CRT_SECURE_NO_WARNINGS hoedown.c " OUT_OPT "../hoedown.exe") != 0) exit(1);
    chdir("..");
}

void compile_project()
{

#ifdef BUILD_WINDOWS_MSC
    if (system("cl "
        SOURCE_FILES
#if defined DEBUG
        " /Od /MDd /RTC1 "
        " /Dstrdup=_strdup" /*nao linka em release*/
#else //RELEASE
        " /GL /Gy /O2 /MD /Ot"
        " /DNDEBUG "
        " /Dstrdup=_strdup" /*nao linka em release*/
#endif
        " /D_CRT_NONSTDC_NO_WARNINGS "
        " /wd4996 "
        " /permissive- "
        " /GS "
        " /Zc:preprocessor- "
        " /std:c17 "
        " /utf-8 "
        " /W4 "
        " /Zi "
        " /Gm- "
        " /sdl "
        " /Zc:inline "
        //" /WX " //Treats all compiler warnings as errors.
        " /Gd "
        " /Oy- "
        " /FC "
        " /EHsc "
#ifdef TEST
        "-DTEST"
#endif
        " /D_CRT_SECURE_NO_WARNINGS "

        " /link "
        " /NODEFAULTLIB "
        " ucrt.lib vcruntime.lib msvcrt.lib "
        " Kernel32.lib User32.lib Advapi32.lib"
        " uuid.lib Ws2_32.lib Rpcrt4.lib Bcrypt.lib "
        " /out:" OUTPUT) != 0) exit(1);



#endif

#ifdef BUILD_WINDOWS_CLANG

    system("clang "
        SOURCE_FILES 
#if defined DEBUG
        " -D_DEBUG"
#else
        " -D_NDEBUG"
#endif

#ifdef TEST
        " -DTEST"
#endif
        " -Wno-switch"
        " -DWIN32"
        " -D_CRT_SECURE_NO_WARNINGS "
        " -std=c17 -Wno-multichar "
        " -D_MT "
        " -Xlinker /NODEFAULTLIB "
        " -lucrt.lib -lvcruntime.lib -lmsvcrt.lib "
        " -lKernel32.lib -lUser32.lib -lAdvapi32.lib"
        " -luuid.lib -lWs2_32.lib -lRpcrt4.lib -lBcrypt.lib "
        " -o " OUTPUT);
#endif

#ifdef BUILD_LINUX_CLANG
    system("clang "
        SOURCE_FILES 
#ifdef TEST
        "-DTEST"
#endif
        " -std=c17 "
        " -Wall "
        " -o " OUTPUT);
#endif


#if defined BUILD_LINUX_GCC || defined BUILD_WINDOWS_GCC

    //#define GCC_ANALIZER  " -fanalyzer "
    system("gcc "
        " -Wall "
        " -Wno-multichar "
        " -Wno-switch "
        " -g "
        SOURCE_FILES 

#if defined DEBUG
        " -D_DEBUG"
#else
        " -D_NDEBUG"
#endif

#ifdef TEST
        " -DTEST"
#endif
        " -o " OUTPUT
    );
#endif

}

void generate_tests()
{
    if (system(RUN "maketest.exe unit_test.c " SOURCE_FILES) != 0) exit(1);

}

void clearall()
{
    remove("maketest.exe");
    remove("embed.exe");
    remove("amalgamator.exe");
    

#ifdef BUILD_WINDOWS_MSC
    system("del *.pdb");
    system("del *.obj");
    chdir("./tools");
    system("del *.obj");
    chdir("..");
#endif

}

void compile_embed()
{
    /*
    * This is an emulation of C23 #embed
    * Here you can add in your build.
    */

    /*
    #define EMBED_SRC \
        " file1.png "

        system(RUN "embed.exe " EMBED_SRC);
    */
}


void process_markdown(const char* mdfilename, const char* outfile)
{
    const char* header =
        "<!DOCTYPE html>\n"
        "<html>\n"
        "<head>\n"
        "  \n"
        "</head>\n"
        "<body>\n";


    FILE* f2 = fopen(outfile /*"./web/index.html"*/, "w");
    if (f2)
    {
        fwrite(header, 1, strlen(header), f2);
        fclose(f2);
    }
    char cmd[200];
    snprintf(cmd, sizeof cmd, RUN "hoedown.exe --html-toc --toc-level 2 --autolink --fenced-code %s >> %s", mdfilename, outfile);
    if (system(cmd) != 0) exit(1);

    snprintf(cmd, sizeof cmd, RUN "hoedown.exe  --toc-level 2 --autolink --fenced-code %s >> %s", mdfilename, outfile);
    if (system(cmd) != 0) exit(1);

    FILE* f3 = fopen(outfile /*"./web/index.html"*/, "a");
    if (f3)
    {
        fwrite("</body></html>", 1, strlen("</body></html>"), f3);
        fclose(f3);
    }
}

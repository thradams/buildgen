# buildgen

Command line tool to generate a C project that
compiles on windows linux etc..

See 
https://github.com/thradams/build


## MSVC build instructions
Open the Developer Command Prompt of visual studio and type

```
cl build.c && build
```

This will build *buildgen.exe*


## GCC (linux) build instructions
Got directory and type:

```
gcc build.c -o build && ./build
```


# Usage

```
 buildgen name
```

This commnad will generate:

```
build.c
build.h
file1.c
file1.h
main.c
tools
  amalgamator.c
  embed.c
  maketest.c
unit_test.h
```

To compile the generated project (same of instructions to build buildgen)

```
cl build.c && build
```

To run tests

```
cl -DTEST build.c && build
```



## Tools Included

amalgamator - command line tool to merge several c files
and create the amalgamted version. (like sqlite)

embed - emulation of C23 embed feature. We convert files
into numbers and then we can use nornmal include.

maketest - the tool that colects tests and generate the call


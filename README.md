# BuildGen

What is BuildGen?

BuildGen is a command line tool that creates a directory structure with a 
multiplatform build script for C programs. 

See the idea behing it here https://github.com/thradams/build

## MSVC build instructions
Open the Developer Command Prompt of visual studio and type

```
cl build.c && build
```

This will build *buildgen.exe*


## GCC (linux) build instructions
Go to directory and type:

```
gcc build.c -o build && ./build
```


# Usage

```
 buildgen name
```

This commnad will generate:

```
name
	build.c
	build.h
	file1.c
	file1.h
	main.c
	readme.md
	unit_test.h

	tools
	  amalgamator.c
	  embed.c
	  maketest.c
	  hoedown.c	
```

To check is the generated build is working go to the name folder and type.

```
cl build.c && build
```

To run tests

```
cl -DTEST build.c && build
```

The sample generates hello.exe.


## Pré configured compilers 

 * Microsoft MSCV (any version)
 * Gcc
 * CLang
  
## Tools Included

amalgamator - command line tool to merge several c files
              and create the amalgamted version. (like sqlite)

embed - emulation of C23 embed feature.

maketest - the tool used to allow -DTEST option to work

hoedown - Markdown to html generator https://github.com/hoedown/hoedown

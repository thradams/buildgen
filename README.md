# BuildGen

What is BuildGen?

BuildGen is a command line tool that creates a directory structure with a 
multiplatform build script for C programs. 

See the idea behing it here https://github.com/thradams/build

## Building buildgen on MSVC windows
Open the Developer Command Prompt of visual studio and type

```
cl build.c && build
```

This will build *buildgen.exe*


## Building buildgen on linux GCC 
Go to directory and type:

```
gcc build.c -o build && ./build
```


# Using buildgen

```
 buildgen name
```

This commnad will generate:

```c
name
	build.c     // build "script"
	build.h     // build script utils
	file1.c     // sample file source with test
	file1.h     // sample file header
	main.c      // sample main
	readme.md   // sample readme
	unit_test.h // sample unit test assert facility

	tools
	  amalgamator.c   // creates amalgamation file
	  embed.c         // emulate C23 embed
	  maketest.c      // used to generate unit test
	  hoedown.c	      // used to convert .md to .html
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

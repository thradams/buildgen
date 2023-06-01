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
	file1.c     // sample file source with a unit test on it
	file1.h     // sample file header
	main.c      // sample main
	readme.md   // sample readme
	unit_test.h // sample unit test assert facility

	tools
	  amalgamator.c   // tool to create amalgamation file
	  embed.c         // tool to emulate C23 #embed
	  maketest.c      // tool to generate unit test automatic call
	  hoedown.c	  // tool to convert .md to .html
```

To check is the generated build is working go to the name folder and type.

```
cl build.c && build
```

To run unit tests

```
cl -DTEST build.c && build
```

The sample generates hello.exe.


## Pré configured compilers 

 * Microsoft MSCV (any version)
 * Gcc
 * CLang
 
 ## Debugging the build (msvc)
 
Add /Zi option

 ```
 cl /Zi build.c
 ```
 then
 ```
 devenv /DebugExe  build.exe
 ```
 F11
 
 
 
 
 
 
 
  
## Tools Included

amalgamator - command line tool to merge several c files
              and create the amalgamted version. (like sqlite)

embed - emulation of C23 embed feature.

maketest - the tool used to allow -DTEST option to work

hoedown - Markdown to html generator https://github.com/hoedown/hoedown

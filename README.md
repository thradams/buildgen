# BuildGen

What is BuildGen?

BuildGen is a command line tool that creates a directory structure build script for C programs. 


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
	tools
	  amalgamator.c
	  embed.c
	  maketest.c
	  hoedown.c
	unit_test.h
```

To check is build is working go to the name folder and type.

```
cl build.c && build
```

To run tests

```
cl -DTEST build.c && build
```



## Pré configured compilers 

 * Microsoft MSCV (any version)
 * Gcc
 * CLang
  
## Tools Included

amalgamator - command line tool to merge several c files
and create the amalgamted version. (like sqlite)

embed - emulation of C23 embed feature. We convert files
into numbers and then we can use nornmal include.

maketest - the tool that colects tests and generate the call

hoedown - Markdown to html generator https://github.com/hoedown/hoedown

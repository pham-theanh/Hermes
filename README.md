# HERMES

There are three steps to running this tool for checking a program for a deadlock.

1. Instrument the source code.
2. Compile and profile the instrumented code into an executable.
3. Execute the profiled code for the output.

The detailed instructions are as follows:

## 1. Instrument

To compile the clang tool, use  `cd clangTool && make clangTool`

This requires:
* clang+llvm build files which you can download from [here](http://releases.llvm.org/3.8.0/).
* a file called _compile\_commands.json_ which is a compilation database needed for clang tooling. The directory contains a sample compile_commands.json file. You just have to specify the command, fileName, and the directory. Learn how to create such files [here](https://clang.llvm.org/docs/JSONCompilationDatabase.html). 

Change the path to these directories in the Makefile of directory _clangTool_ accordingly.

To produce the instrumented code, run: `./clangTool path-to-the-source/source-file.cpp`

This will generate a file called __i\_source-file.cpp__ in the same directory where the source resides.

## 2. Compile and profile

Follow these steps:
* `cd Hermes/`
* `make`
* `sudo make install`
* `cd scheduler`

This should generate _libisp\_prof.so_ in _/usr/local/lib/_.

To generate the profiled executable, run: 

`ispcxx -o executable executable.cpp ../clangTool/GenerateAssumes.cpp ../clangTool/IfInfo.cpp ../profiler/Client.c`

## 3. Execute

Run the executable through the tool isp with this command: `./isp.exe -n no-of-processes ./executable`

You can find all the options isp provides using `./isp.exe -help`

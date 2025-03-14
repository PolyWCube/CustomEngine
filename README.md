# Custom Engine

An application engine in C++ emphasizes (or at least trying) raw customizable and performance.

**Feature**

> Current version able to create a window that could log associated events, messages,... into a file and console.

* Logging mechanism
* Abstract event and input system
* Window creation
* ...

# Build

> The repository already contains the build instruction in `*.bat` files (just run `clean-build.bat` for clean or initial build, or run `compile.bat` to keep the existing build and update application source code).

Simply go to the root folder and run `$(MAKE) all` and the executable file will located in `./build/*.exe` if build successfully, if the repository have built already, then the command will recompile the source code.

To clean the build, run `$(MAKE) clean` or manually remove the build folder, either way work.

> Replace `$(MAKE)` with corresponding makefile system.

# Requirement

> Built and tested in **Windows 11**.

**Operating system (OS)**
* **Window 8** or higher (Tested using **Window 11 compatible mode**)

**Build system**
* **Makefile** (`make.exe`/`mingw32-make.exe`/...) - GNU Make 4.4.1
* **C++ Compiler** (`g++.exe`) - GCC 14.0.2
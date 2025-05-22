# Custom Engine
![Totally official] (archive/image/official-logo.png)

An application engine in C++ emphasizes (or at least tries) raw customizable and performance.

**Feature**

> Current version is able to create a window that could log associated events, messages,... into a file and console + some simple UIs (buttons).

* Logging mechanism
* Abstract event, input system, and UI system
* Window creation
* ...

# Build

> The repository already contains the build instructions in `*.bat` files (just run `clean-build.bat` for a clean or initial build, or run `compile.bat` to keep the existing build and update the application source code).

Simply go to the root folder and run `$(MAKE) all` and the executable file will located in `./build/*.exe` if the build successfully, if the repository have built already, then the command will recompile the source code.

To clean the build, run `$(MAKE) clean` or manually remove the build folder, either way works.

> Replace `$(MAKE)` with corresponding makefile system.

# Requirement

> Built and tested in **Windows 11** and using **MSYS2**

**Operating system (OS)**
* **Window 8** or higher (Tested using **Window 11 compatible mode**)

**Build system**
* **Makefile** (`make.exe`/`mingw32-make.exe`/...) - GNU Make 4.4.1
* **C++ Compiler** (`g++.exe`) - GCC 14.0.2
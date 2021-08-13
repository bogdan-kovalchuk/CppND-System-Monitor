# CppND-System-Monitor

Implementation of System Monitor Project in the Object Oriented Programming Course of the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). This project relies on [ncurses](https://www.gnu.org/software/ncurses/) for display output.

## Make
This project uses [Make](https://www.gnu.org/software/make/). The Makefile has four targets:
* `build` compiles the source code and generates an executable
* `format` applies [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) to style the source code
* `debug` compiles the source code and generates an executable, including debugging symbols
* `clean` deletes the `build/` directory, including all of the build artifacts

## Instructions

1. Clone the project repository: `git clone https://github.com/bogdan-kovalchuk/CppND-System-Monitor.git`

2. Install ncurses in Linux environment: `sudo apt install libncurses5-dev libncursesw5-dev`

3. Build the project: `make build`

4. Run the resulting executable: `./build/monitor`
# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/name/projects/asio

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/name/projects/asio

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/name/projects/asio/CMakeFiles /home/name/projects/asio/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/name/projects/asio/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named final

# Build rule for target.
final: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 final
.PHONY : final

# fast build rule for target.
final/fast:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/build
.PHONY : final/fast

acceptor_loop.o: acceptor_loop.cpp.o

.PHONY : acceptor_loop.o

# target to build an object file
acceptor_loop.cpp.o:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/acceptor_loop.cpp.o
.PHONY : acceptor_loop.cpp.o

acceptor_loop.i: acceptor_loop.cpp.i

.PHONY : acceptor_loop.i

# target to preprocess a source file
acceptor_loop.cpp.i:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/acceptor_loop.cpp.i
.PHONY : acceptor_loop.cpp.i

acceptor_loop.s: acceptor_loop.cpp.s

.PHONY : acceptor_loop.s

# target to generate assembly for a file
acceptor_loop.cpp.s:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/acceptor_loop.cpp.s
.PHONY : acceptor_loop.cpp.s

config.o: config.cpp.o

.PHONY : config.o

# target to build an object file
config.cpp.o:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/config.cpp.o
.PHONY : config.cpp.o

config.i: config.cpp.i

.PHONY : config.i

# target to preprocess a source file
config.cpp.i:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/config.cpp.i
.PHONY : config.cpp.i

config.s: config.cpp.s

.PHONY : config.s

# target to generate assembly for a file
config.cpp.s:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/config.cpp.s
.PHONY : config.cpp.s

file_serving.o: file_serving.cpp.o

.PHONY : file_serving.o

# target to build an object file
file_serving.cpp.o:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/file_serving.cpp.o
.PHONY : file_serving.cpp.o

file_serving.i: file_serving.cpp.i

.PHONY : file_serving.i

# target to preprocess a source file
file_serving.cpp.i:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/file_serving.cpp.i
.PHONY : file_serving.cpp.i

file_serving.s: file_serving.cpp.s

.PHONY : file_serving.s

# target to generate assembly for a file
file_serving.cpp.s:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/file_serving.cpp.s
.PHONY : file_serving.cpp.s

logger.o: logger.cpp.o

.PHONY : logger.o

# target to build an object file
logger.cpp.o:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/logger.cpp.o
.PHONY : logger.cpp.o

logger.i: logger.cpp.i

.PHONY : logger.i

# target to preprocess a source file
logger.cpp.i:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/logger.cpp.i
.PHONY : logger.cpp.i

logger.s: logger.cpp.s

.PHONY : logger.s

# target to generate assembly for a file
logger.cpp.s:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/logger.cpp.s
.PHONY : logger.cpp.s

main.o: main.cpp.o

.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i

.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s

.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) -f CMakeFiles/final.dir/build.make CMakeFiles/final.dir/main.cpp.s
.PHONY : main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... final"
	@echo "... acceptor_loop.o"
	@echo "... acceptor_loop.i"
	@echo "... acceptor_loop.s"
	@echo "... config.o"
	@echo "... config.i"
	@echo "... config.s"
	@echo "... file_serving.o"
	@echo "... file_serving.i"
	@echo "... file_serving.s"
	@echo "... logger.o"
	@echo "... logger.i"
	@echo "... logger.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_SOURCE_DIR = /home/catlord/Documents/zimny_semester_2019-20/grafika/cvika/ppgso

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/catlord/Documents/zimny_semester_2019-20/grafika/cvika/ppgso

# Include any dependencies generated for this target.
include CMakeFiles/gl1_gradient.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/gl1_gradient.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gl1_gradient.dir/flags.make

CMakeFiles/gl1_gradient.dir/src/gl1_gradient/gl1_gradient.cpp.o: CMakeFiles/gl1_gradient.dir/flags.make
CMakeFiles/gl1_gradient.dir/src/gl1_gradient/gl1_gradient.cpp.o: src/gl1_gradient/gl1_gradient.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/catlord/Documents/zimny_semester_2019-20/grafika/cvika/ppgso/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/gl1_gradient.dir/src/gl1_gradient/gl1_gradient.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gl1_gradient.dir/src/gl1_gradient/gl1_gradient.cpp.o -c /home/catlord/Documents/zimny_semester_2019-20/grafika/cvika/ppgso/src/gl1_gradient/gl1_gradient.cpp

CMakeFiles/gl1_gradient.dir/src/gl1_gradient/gl1_gradient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gl1_gradient.dir/src/gl1_gradient/gl1_gradient.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/catlord/Documents/zimny_semester_2019-20/grafika/cvika/ppgso/src/gl1_gradient/gl1_gradient.cpp > CMakeFiles/gl1_gradient.dir/src/gl1_gradient/gl1_gradient.cpp.i

CMakeFiles/gl1_gradient.dir/src/gl1_gradient/gl1_gradient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gl1_gradient.dir/src/gl1_gradient/gl1_gradient.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/catlord/Documents/zimny_semester_2019-20/grafika/cvika/ppgso/src/gl1_gradient/gl1_gradient.cpp -o CMakeFiles/gl1_gradient.dir/src/gl1_gradient/gl1_gradient.cpp.s

CMakeFiles/gl1_gradient.dir/src/gl1_gradient/gl1_gradient.cpp.o.requires:

.PHONY : CMakeFiles/gl1_gradient.dir/src/gl1_gradient/gl1_gradient.cpp.o.requires

CMakeFiles/gl1_gradient.dir/src/gl1_gradient/gl1_gradient.cpp.o.provides: CMakeFiles/gl1_gradient.dir/src/gl1_gradient/gl1_gradient.cpp.o.requires
	$(MAKE) -f CMakeFiles/gl1_gradient.dir/build.make CMakeFiles/gl1_gradient.dir/src/gl1_gradient/gl1_gradient.cpp.o.provides.build
.PHONY : CMakeFiles/gl1_gradient.dir/src/gl1_gradient/gl1_gradient.cpp.o.provides

CMakeFiles/gl1_gradient.dir/src/gl1_gradient/gl1_gradient.cpp.o.provides.build: CMakeFiles/gl1_gradient.dir/src/gl1_gradient/gl1_gradient.cpp.o


# Object files for target gl1_gradient
gl1_gradient_OBJECTS = \
"CMakeFiles/gl1_gradient.dir/src/gl1_gradient/gl1_gradient.cpp.o"

# External object files for target gl1_gradient
gl1_gradient_EXTERNAL_OBJECTS =

gl1_gradient: CMakeFiles/gl1_gradient.dir/src/gl1_gradient/gl1_gradient.cpp.o
gl1_gradient: CMakeFiles/gl1_gradient.dir/build.make
gl1_gradient: libppgso.a
gl1_gradient: libshaders.a
gl1_gradient: /usr/lib/x86_64-linux-gnu/libglfw.so
gl1_gradient: /usr/lib/x86_64-linux-gnu/libGLEW.so
gl1_gradient: /usr/lib/x86_64-linux-gnu/libGL.so
gl1_gradient: /usr/lib/x86_64-linux-gnu/libGLU.so
gl1_gradient: CMakeFiles/gl1_gradient.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/catlord/Documents/zimny_semester_2019-20/grafika/cvika/ppgso/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable gl1_gradient"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gl1_gradient.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gl1_gradient.dir/build: gl1_gradient

.PHONY : CMakeFiles/gl1_gradient.dir/build

CMakeFiles/gl1_gradient.dir/requires: CMakeFiles/gl1_gradient.dir/src/gl1_gradient/gl1_gradient.cpp.o.requires

.PHONY : CMakeFiles/gl1_gradient.dir/requires

CMakeFiles/gl1_gradient.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gl1_gradient.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gl1_gradient.dir/clean

CMakeFiles/gl1_gradient.dir/depend:
	cd /home/catlord/Documents/zimny_semester_2019-20/grafika/cvika/ppgso && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/catlord/Documents/zimny_semester_2019-20/grafika/cvika/ppgso /home/catlord/Documents/zimny_semester_2019-20/grafika/cvika/ppgso /home/catlord/Documents/zimny_semester_2019-20/grafika/cvika/ppgso /home/catlord/Documents/zimny_semester_2019-20/grafika/cvika/ppgso /home/catlord/Documents/zimny_semester_2019-20/grafika/cvika/ppgso/CMakeFiles/gl1_gradient.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gl1_gradient.dir/depend

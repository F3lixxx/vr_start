# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.29

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\User\Documents\QT_Projects\Choose_Game

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\User\Documents\QT_Projects\Choose_Game\build\Desktop_Qt_6_7_1_MinGW_64_bit-Debug

# Utility rule file for Choose_Game_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/Choose_Game_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Choose_Game_autogen.dir/progress.make

CMakeFiles/Choose_Game_autogen: Choose_Game_autogen/timestamp

Choose_Game_autogen/timestamp: C:/Qt/6.7.1/mingw_64/./bin/moc.exe
Choose_Game_autogen/timestamp: C:/Qt/6.7.1/mingw_64/./bin/uic.exe
Choose_Game_autogen/timestamp: CMakeFiles/Choose_Game_autogen.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=C:\Users\User\Documents\QT_Projects\Choose_Game\build\Desktop_Qt_6_7_1_MinGW_64_bit-Debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target Choose_Game"
	"C:\Program Files\CMake\bin\cmake.exe" -E cmake_autogen C:/Users/User/Documents/QT_Projects/Choose_Game/build/Desktop_Qt_6_7_1_MinGW_64_bit-Debug/CMakeFiles/Choose_Game_autogen.dir/AutogenInfo.json Debug
	"C:\Program Files\CMake\bin\cmake.exe" -E touch C:/Users/User/Documents/QT_Projects/Choose_Game/build/Desktop_Qt_6_7_1_MinGW_64_bit-Debug/Choose_Game_autogen/timestamp

Choose_Game_autogen: CMakeFiles/Choose_Game_autogen
Choose_Game_autogen: Choose_Game_autogen/timestamp
Choose_Game_autogen: CMakeFiles/Choose_Game_autogen.dir/build.make
.PHONY : Choose_Game_autogen

# Rule to build all files generated by this target.
CMakeFiles/Choose_Game_autogen.dir/build: Choose_Game_autogen
.PHONY : CMakeFiles/Choose_Game_autogen.dir/build

CMakeFiles/Choose_Game_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Choose_Game_autogen.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Choose_Game_autogen.dir/clean

CMakeFiles/Choose_Game_autogen.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\User\Documents\QT_Projects\Choose_Game C:\Users\User\Documents\QT_Projects\Choose_Game C:\Users\User\Documents\QT_Projects\Choose_Game\build\Desktop_Qt_6_7_1_MinGW_64_bit-Debug C:\Users\User\Documents\QT_Projects\Choose_Game\build\Desktop_Qt_6_7_1_MinGW_64_bit-Debug C:\Users\User\Documents\QT_Projects\Choose_Game\build\Desktop_Qt_6_7_1_MinGW_64_bit-Debug\CMakeFiles\Choose_Game_autogen.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/Choose_Game_autogen.dir/depend

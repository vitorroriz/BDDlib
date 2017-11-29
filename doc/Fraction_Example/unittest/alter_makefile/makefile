## A generic Makefile

## References:
# http://www.linuxdevcenter.com/pub/a/linux/2002/01/31/make_intro.html
# ftp://ftp.gnu.org/old-gnu/Manuals/make-3.79.1/html_chapter/make_6.html
# http://make.mad-scientist.net/papers/advanced-auto-dependency-generation/

## General description:
# - The file has comments explaining it
# - Uses the compiler and the linker to produce the executable (target)
#   for testing purposes
# - The tests are also executed every time the project is recompiled
# - The Makefile generates automatically all dependencies

## Usage:
# - You should edit this file only on the locations where it is indicated
# - To run: on the console go to the directory where the Unit Test files are located
#   this Makefile should be located in the same directory.
#   Once there type "make" (without quotation marks)
# - the program Make will automatically locate this "Makefile" and use it as input
# - The general directory structure should look like this:
#     /CODE_DIR/:
#       /sources to be tested: *.cpp
#       /headers to be tested: *.hpp
#       /UTEST_DIR/:
#         /Makefile
#         /sources for Unit Testing *.cpp
#         /headers for Unit Testing *.hpp

## Name of the executable to be used for testing (adjust name to your convenience!)
TARGET_UTEST = test

## Source files with Unit Tests (adjust file names to your convenience!)
# Comments about Make:
# "wildcard" lists all the files in this case with ".cpp" extension in this directory
UTEST_SRCS = $(wildcard *.cpp)

## Name of directory with code to be tested (adjust directory to your convenience!)
# All source files (*.cpp) should be located in the same directory
# In this case the code to be tested is located one directory up
CODE_DIR = ../

## Source files to be tested (adjust file name to your convenience!)
# Comments about Make:
# "wildcard" lists all the files in this case with ".cpp" extension in directory up
CODE_SRCS = $(wildcard $(CODE_DIR)*.cpp)

## Join all required sources (source code and unit test)
SRCS += $(CODE_SRCS)
SRCS += $(UTEST_SRCS)

## Compiler and linker definitions (adjust definitions to your convenience!)
# -O0 : optimization level 0
# -g : adds debugging information to the executable file
# -Wall : activates most compiler warnings
# -std=c++11 : version 11 of the C++ standard
# -lcppunit : includes library of the CppUnit test framework
CXX = g++
CXXFLAGS = -O0 -Wall -g -D DEBUG -std=c++11
INCLUDES =
LDFLAGS = 
LIBS = -lcppunit

## Definition of Phony targets
# Comments about Make:
# .PHONY tells Make which targets are not files.
# This is useful when we need to execute commands from the console
# Phony targets are never up-to-date therefore the are always executed
.PHONY: clean

## Object files
# Comments about Make:
# Below we are replacing the suffix .cpp of all words in the variable "SRCS" with the .o suffix
OBJECTS = $(SRCS:.cpp=.o)

## Default rule, first creates the target and the run the tests
# Comments about Make:
# When called without a rule parameter, Make runs the first rule it encounters. 
# It is more human-readable to explicitly state your first rule. 
# all is a common name for a first rule.
all: $(TARGET_UTEST)

## Create main target
# Comments about Make:
# The automatic variable $@ means "the name of the target."
# The automatic variable $+ means "all prerequisites, space-separated."
# Automatic variables are pre-defined in Make.
$(TARGET_UTEST): $(OBJECTS)
	# All dependencies built, link command:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $+ $(LDFLAGS) $(LIBS)
	# Unit Test results:
	@./$(TARGET_UTEST)

## placement of dependency files (*.P)
# directory
DEPDIR = .deps
# macro
df = $(DEPDIR)/$(*F)

## Tell Make how to build .o files from .cpp files
# Comments about Make:
# A pattern rule tells Make how to convert the prerequisite to the target.
# The % in the pattern means "one or more characters," and refers to the same string in the 
# prerequisite and the target.
# This particular pattern tells Make how to convert a *.cpp file to a *.o file of the same name.
# The automatic variable $< means "the first prerequisites i.e. the *.cpp source file"
%.o: %.cpp
# create directory with dependency files if it doe not exist:
	@mkdir -p $(DEPDIR)
# create dependency files (compiler is used for that):
	@$(CXX) -M $(CXXFLAGS) $(INCLUDES) -o $(df).d $<; \
	  cp $(df).d $(df).P; \
	  sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
	      -e '/^$$/ d' -e 's/$$/ :/' < $(df).d >> $(df).P; \
	  rm -f $(df).d
# compile each source:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ -c $<

## Now ensure that Make rebuilds files if the included headers (*.hpp files) change
# Comments about Make: 
# These rules are included to define the prerequisites for the relevant *.o files.
-include $(SRCS:%.cpp=$(DEPDIR)/%.P)

## remove all files produced by the compiler and the linker
# Comments about Make:
# Note that this rule does not create a file (i.e. we are not creating a file called "clean")
# instead of that we are here just executing commands.
# Therefore clean is defined above as a Phony target
clean:
	@rm -f *.o
	@rm -f $(CODE_DIR)/*.o
	@rm -rf $(DEPDIR)	
	@rm -f $(TARGET_UTEST)


#
# 'make'        build executable file 'main'
# 'make clean'  removes all .o and executable files
#

# define the C++ compiler to use
CXX = g++
# define the C compiler to use
CC = gcc

# define any compile-time flags
CXXFLAGS	:= -std=c++17 -Wall -Wextra -g

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS =

# define output directory
OUTPUT	:= output

# define source directory
SRC		:= tests

# define include directory
INCLUDE	:= .

# define lib directory
LIB		:= lib

ifeq ($(OS),Windows_NT)
MAIN	:= main.exe
SOURCEDIRS	:= $(SRC)
INCLUDEDIRS	:= $(INCLUDE)
LIBDIRS		:= $(LIB)
FIXPATH = $(subst /,\,$1)
RM  := helpers/deletefile.exe
CP  := helpers/copyfile.exe
MD  := mkdir
else
MAIN	:= main
SOURCEDIRS	:= $(shell find $(SRC) -type d)
INCLUDEDIRS	:= $(shell find $(INCLUDE) -type d)
LIBDIRS		:= $(shell find $(LIB) -type d)
FIXPATH = $1
RM = rm -f
CP  := cp
MD	:= mkdir -p
endif

# define any directories containing header files other than /usr/include
INCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))

# define the C libs
LIBS		:= $(patsubst %,-L%, $(LIBDIRS:%/=%)) -lraylib
ifeq ($(OS),Windows_NT)
LIBS += -lopengl32 -lgdi32 -lwinmm
else
LIBS += -lm -lpthread -ldl -lrt
endif

# define the C source files
SOURCES		:= $(wildcard $(patsubst %,%/*.cpp, $(SOURCEDIRS)))

# define the C object files
OBJECTS		:= $(SOURCES:.cpp=.o)

# define the dependency output files
DEPS		:= $(OBJECTS:.o=.d)

#
# The following part of the makefile is generic; it can be used to
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

OUTPUTMAIN	:= $(call FIXPATH,$(OUTPUT)/$(MAIN))

all: $(OUTPUT) DataTypes DictStressTest ConfigTest
	@echo Executing 'all' complete!

$(OUTPUT):
	$(MD) $(OUTPUT)

DataTypes:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o output/DataTypes tests/DataTypes.cpp $(LFLAGS) $(LIBS)

DictStressTest:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o output/DictStressTest tests/DictStressTest.cpp $(LFLAGS) $(LIBS)

ConfigTest:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o output/ConfigTest tests/ConfigTest.cpp $(LFLAGS) $(LIBS)

# include all .d files
-include $(DEPS)

.PHONY: clean
clean:
	$(RM) $(OUTPUTMAIN)
	$(RM) $(call FIXPATH,$(OBJECTS))

run: all
	$(call FIXPATH,output/DataTypes)
	$(call FIXPATH,output/DictStressTest)
	$(call FIXPATH,output/ConfigTest)
	@echo Executing 'run: all' complete!

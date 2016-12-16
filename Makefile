SHELL=/bin/sh
#
# Edit: OBJECTS, INCS, INPUTS, COMMAND, INCLUDE DEPENDENCIES, tar(?).
#
# Comments:#   It will compile the fortran modules indicated by SRCS into the object
# modules indicated by OBJS and then produce an executable indicated by
# COMMAND.  Note that objects are not recompiled unless they are out of date
# with respect to their dependencies (sources and includes).
# If the SRCS are in different directories, the objects will
# be placed in same directory as source and includes will be referenced
# correctly.  Includes may not be referenced correctly with global;
# it not, change FFLAGS to O3FFLAGS and make with no option.
#
#   makefile represents the name of this makefile.  If it is actually named 
# makefile, then the -f makefile is unnecessary.  Edit the list of .o files
# (OBJS) below to represent your files.  The .f files (SRCS) can be listed 
# separately, but it is easier to determine them directly from the OBJS.
# The include files and dependence of OBJS on include files can be 
# determined using options findincl and showincl, and the results can be
# pasted into this file (and edited if needed).  Edit INPUTS to list other
# files needed to run COMMAND (*.dat, etc); INPUTS is only used with tar 
# option but it doesnt hurt to document the files anyway.
# Note that a line starting with a space follows every rule (called a 
# separator), and \ can be used to continue lines.
#  
#   The tar option creates the file $(COMMAND).tar containing this makefile,
# SRCS, INCS (include files), and INPUTS. (any input or other files that
# are needed to run code).  Tar preserves dates and is a good way to move
# code between systems.  You may wish to edit the shell commands for the
# tar option directly to include *.f, etc., as needed.
#
#   This makefile is a modified version of the standard makefile.
#   Options void, clean, and clobber which appear in the usual makefile 
# have been removed here.

# Compiler parameters
# CFLAGS        Flags to the C compiler [use -O1 when debugging]
#
# -O3 : optimisation for both small code size and small execution time
# -lm : link (-l) standard math mibrary (often also written "-lm")
# -g  : generate debug information to be used by GDB debugger

COMPILER=gcc
CFLAGS=-ansi -std=c99 -pedantic -Wall -g
EXTRFLAGS=-lm -O3

#
# Include files as generated with findincl option and modified as needed;
# any directory reference should be relative to make directory, not the
# directory of .f file which can be different.
# Include files assumed to end with .inc or .def.
# NO continuation (\) ON LAST LINE.
#

INCLUDE=-I ./include

# OBJECTS defined below, modify as needed.  OBJECTS are the source files (.c)
# with .c -> .o .   Directories are relative to make directory.
# WITH continuation (\) ON LAST LINE.

OBJECTS= \
Ising_action.o\
mt19937-64.o\
printlattice.o\
printtwopoint.o\
# EXE: name of the executable file produced by compilation
EXE=Ising_main

#
# Lines from here on are the actual rules that make uses to build $(COMMAND).
# Definition of command must precede include dependencies!
#
# INCLUDE DEPENDENCIES: Dependencies on include files, Edit as needed.  
# Can be generated via showincl option; the directory of include file
# must be relative to make directory (check it).  May need to break long 
# lines with \ .


all: Ising_main.c deltaction mtgenerator printlattice printtwopoint
	$(COMPILER) $(CFLAGS) $(EXTRFLAGS) $(INCLUDE) $(OBJECTS) $(EXE).c -lm -o $(EXE)

deltaction: Ising_action.c 
	$(COMPILER) $(CFLAGS) $(INCLUDE) Ising_action.c -c

mtgenerator: mt19937-64.c 
	$(COMPILER) $(CFLAGS) $(INCLUDE) mt19937-64.c -c

printtwopoint: printtwopoint.c 
	$(COMPILER) $(CFLAGS) $(INCLUDE) printtwopoint.c -c

printlattice: printlattice.c 
	$(COMPILER) $(CFLAGS) $(INCLUDE) printlattice.c -c
clean:
	rm $(OBJECTS) $(EXE) 

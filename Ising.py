#!/usr/bin/env python
"""Ising.py by Taylor Jacovich 2016-12-13
This script integrates Ising model C code and
runs it to determine various TD values with uncertainty"""


print ("Ising.py by Taylor Jacovich 2016-12-13 This script integrates Ising model C code\n and runs it to determine various TD values with uncertainty")
print("\n")
  #What to do options:
  #     1     Calculate magnetization for set external field and temp along with uncertainty
  #     2     Calculate magnetization and energy for a given T and H along with uncertainty
  #     3     Calculate susceptibility for given T and H with uncertainty
  #     4     Calculate Specific Heat at given H for T range along with uncertainty
  #     5     Calculate magnetization for set external field for a range of T along with uncertainty
  #     6     Calculate finite volume effects on magnetization
  #     7     Calculate energy for a finite volume of the phase space
what_do = 1
#Parameter definitions
dim_x = 10         #Lattice x-dimension
dim_y = 10         #Lattice y-dimension
h     =  0         #External field strength
T     =  0         #Temperature definition
file  = "test.txt" #Output file for the field configuration
No    = 10000      #Number of updates to perform on the initial field configuration

if what_do>7:
  print ("Invalid configuration options.  Please check Ising.py.")
if what_do<1:
  print ("Invalid configuration options.  Please check Ising.py.")

def magnetization( dim_x, dim_y, h, T, file, No ):
  str = 
  import os
  os.system("./Ising_main dim_x dim_y h T file No")
  return;
  
def jacknife( file1, bins, No ):
  from subprocess import call
  call(["./Jacknife", "file1", "bins", "No"])
  return;

if what_do==1:
  magnetization( dim_x, dim_y, h, T, file, No )
  print("magnetization complete.  Check file:")
  print(file)
  print("\n")

#!/usr/bin/env python
"""Ising.py by Taylor Jacovich 2016-12-13
This script integrates Ising model C code and
runs it to determine various TD values with uncertainty"""

def main():  
  #What to do options:
  #     1     Calculate magnetization for set external field and temp along with uncertainty
  #     2     Calculate magnetization and energy for a given T and H along with uncertainty
  #     3     Calculate susceptibility for given T and H with uncertainty
  #     4     Calculate Specific Heat at given H for T range along with uncertainty
  #     5     Calculate magnetization for set external field for a range of T along with uncertainty
  #     6     Calculate finite volume effects on magnetization
  #     7     Calculate energy for a finite volume of the phase space
  what_do = 1

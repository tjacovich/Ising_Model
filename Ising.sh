#!/bin/bash

printf "Ising.sh by Taylor Jacovich 2016-12-13 This script integrates Ising model C code\nand runs it to determine various TD values with uncertainty"
printf "\n"
printf "\n"
printf "\n"
  #What to do options:
  #     1     Calculate magnetization for set external field and temp along with uncertainty
  #     2     Calculate magnetization and energy for a given T and H along with uncertainty
  #     3     Calculate susceptibility for given T and H with uncertainty
  #     4     Calculate Specific Heat at given H for T range along with uncertainty
  #     5     Calculate magnetization for set external field for a range of T along with uncertainty
  #     6     Calculate finite volume effects on magnetization
  #     7     Calculate energy for a finite volume of the phase space

  what_do=5

 #Parameter definitions
 dim_x=10         #Lattice x-dimension
 dim_y=10         #Lattice y-dimension
     h=0          #External field strength
     T=0          #Temperature definition
  file="test.txt" #Output file for the field configuration
    No=10000      #Number of updates to perform on the initial field configuration
  hmax=1          #For options 4 and 5 these two variables specify max sweep value of T and H 
  Tmax=1          #For options 4 and 5 these two variables specify max sweep value of T and H
  inch=0.1
  incT=0.1
# if [  $what_do > 7 ]
# then
# echo $what_do
# printf "Invalid configuration options:\n Please check Ising.sh.\n" 
# exit
# fi

 #if [ $what_do < 1 ]
 #then
 #printf "Invalid configuration options:\n  Please check Ising.sh.\n"
 #exit
 #fi

 if [ $what_do = 1 ]
 then
 ./Ising_main $dim_x $dim_y $h $T $file $No
 ./jacknife $file $No
 fi
 
 if [ $what_do = 5 ]
 then
 for j in {$T $Tmax $incT}
 do	 
   for i in {$h $hmax $inch}  
    do
     file="file"
     file+="$i$j"
     file+=".txt"
     echo $file     
     ./Ising_main $dim_x $dim_y i j $file $No
    # ./jacknife $file $No
    done
 done
 fi

 exit

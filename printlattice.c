#include <stdlib.h>//Standard C library
#include <stdio.h>//Standard C I/O library
#include <math.h>//C math library

/*Jacovich 6/19/19*/
/*Function to print out the values of S_o, S_n and phi at a given time in the lattice function*/

void printlattice(double* phi, int dim_lat)
  {
    for(int j=0; j<dim_lat; j++)
      {
        for(int l=0; l<dim_lat; l++)
          {
            printf("%lf ", phi[l+dim_lat*j]);
          }
        printf(" \n");
      }


    printf(" \n");

  }

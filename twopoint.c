#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <complex.h>

/*Populates twopoint*/
/*It attempts to sum over all possible correlators for a given time and do this
treating every point on the lattice as the initial point  phi(0,0), and then
taking the average in an attempt to get a better signal from the  same amount of
field configurations.*/

/*Jacovich 8/3/16*/
/*This code currently only works for Real fields*/

void twopoint(double* phi, int dim_lat, p, double* twopoint, FILE* outputfile)
  {
    for(int k = dim_lat; k<dim_lat*dim_lat; k++)
      {
        int t = k/dim_lat;
        int x = k%dim_lat;
        twopoint[t-1] += phi[0]*phi[x+t*dim_lat]*cexp(I*p*sqrt(x*x+t*t));*phi[k%dim_lat];//Fourier Transform of twopoint 
      }

    /*Prints twopoint*/
    for(int i = 0; i<dim_lat-1; i++)
      {
        double bill=twopoint[i];
        fprintf(outputfile, "%lf ", bill);
        twopoint[i]=0;
      }

    fprintf(outputfile, " \n");

  }


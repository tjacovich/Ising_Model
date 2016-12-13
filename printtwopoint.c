#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

/*Jacovich 6/23/16*/
/*This function determines the average of the two point functions for a given distance from a point
for a given field configuration.  For a given field, it produces 2 files.  one for phi[i]*phi[i]and
one for phi[i]*phi[j] where j is at least one step away from i.*/


void printtwopoint(double* phi, int No, int dim_lat)
  {
    /*defines and opens a file for all stationary correlators*/
    FILE *stationary;
    stationary = fopen("stationary.txt", "a+");
    
    /*writes all stationary correlators to file*/
    for(int i = 0; i<dim_lat*dim_lat; i++)
      {
        fprintf(stationary, "%lf ",phi[i]*phi[i]);
      }

    /*seperates between write times*/
    fprintf(stationary, "\n");
    
    fclose(stationary);


    /*Defines a file for corellators of non-stationary points.*/
    FILE *motion;
    motion = fopen("motion.txt", "a+");
 /**This loop determines how far we are from the central point and computes the correlator.*/
    for(int k = 1; k<dim_lat+1; k++)
      { 
        double out = 0;
        /*This loop steps through all values of the matrix and determines the corellator with all points k steps away.*/
        for(int j = 0; j<dim_lat*dim_lat; j++)
          {
            int cnt = j;
             
            /*defines x and t in terms of the variable number*/
            int x = cnt%dim_lat;
            int t = cnt/dim_lat;
            
            /*defines the cross terms*/

            int xp = (x+k)%dim_lat; out += phi[xp+dim_lat*t]*phi[cnt];
            xp = (x-k+dim_lat)%dim_lat; out += phi[xp+dim_lat*t]*phi[cnt];
            int tp = (t+k)%dim_lat; out += phi[x+dim_lat*tp]*phi[cnt];
            tp = (t-k+dim_lat)%dim_lat; out += phi[x+dim_lat*tp]*phi[cnt];
            
          }
          
        fprintf(motion, "%lf ", out/(4*dim_lat*dim_lat));
      }
 
    fclose(motion);
  }

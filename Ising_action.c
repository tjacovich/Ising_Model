#include <stdlib.h>//Standard C library
#include <stdio.h>//Standard I/O library
#include <math.h>//C math library

/*Jacovich 6/16/2016*/
/*This generates the change in Energy due to a given field point, as well as the original action*/

void Isingaction(double* phi, double temp, double a,  double* dS_n, double* dS_o, int dim_lat, int dim_t, int dim_z, int dim_y, int cnt, double h)
  {
    int x = cnt%dim_lat;
    int y = (cnt/(dim_lat))%dim_y;

    double nei = 0;

    int xp = (x+1)%dim_lat; nei += phi[xp+y*dim_lat];  
    xp = (x-1+dim_lat)%dim_lat; nei += phi[xp+y*dim_lat]; 
   
    int yp = (y+1)%dim_y; nei += phi[x+yp*dim_lat]; 
    yp = (y-1+dim_lat)%dim_y; nei += phi[x+yp*dim_lat];
   
    *dS_n = -2*a*nei*temp+h*temp;
    temp = phi[cnt];
    *dS_o = -2*a*nei*temp+h*temp;

 }

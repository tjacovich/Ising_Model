#include <stdlib.h>//Standard C library
#include <stdio.h>//Standard I/O library
#include <math.h>//C math library

/*Jacovich 6/16/2016*/
/*This generates the change in Energy due to a given field point, as well as the original action*/

void action(double* phi, double* H, double a, int dim_lat, int dim_y, double h)
  {
    for(int cnt = 0;cnt<(dim_lat*dim_y);cnt++)
      {
    int x = cnt%dim_lat;
    int y = (cnt/(dim_lat))%dim_y;
    double temp =phi[cnt];
    double nei = 0;

    int xp = (x+1)%dim_lat; nei += phi[xp+y*dim_lat];  
    xp = (x-1+dim_lat)%dim_lat; nei += phi[xp+y*dim_lat]; 
   
    int yp = (y+1)%dim_y; nei += phi[x+yp*dim_lat]; 
    yp = (y-1+dim_lat)%dim_y; nei += phi[x+yp*dim_lat];
   
    *H += -a*nei*temp+h*temp;
      }
 }

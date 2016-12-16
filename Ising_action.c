#include <stdlib.h>//Standard C library
#include <stdio.h>//Standard I/O library
#include <math.h>//C math library

/*Jacovich 6/16/2016*/
/*This generates the change in Energy due to a given field point, as well as the original action*/

void Isingaction(double* phi, double temp, double a,  double* dS_n, double* dS_o, int dim_lat, int dim_y, int dim_z, int dim_t, int cnt, double h)
  {
    int x = cnt%dim_lat;
    int y = (cnt/(dim_lat))%dim_y;
    int z = (cnt/(dim_lat*dim_y))%dim_z;
    int t = (cnt/(dim_lat*dim_y*dim_z));

    double nei = 0;

    int xp = (x+1)%dim_lat; nei += phi[xp+y*dim_lat+z*dim_lat*dim_y+dim_lat*dim_y*dim_z*t];  
    xp = (x-1+dim_lat)%dim_lat; nei += phi[xp+y*dim_lat+z*dim_lat*dim_y+dim_lat*dim_y*dim_z*t]; 
   
    int tp = (t+1)%dim_t; nei += phi[x+y*dim_lat+z*dim_lat*dim_y+dim_lat*dim_y*dim_z*tp]; 
    tp = (t-1+dim_lat)%dim_t; nei += phi[x+y*dim_lat+z*dim_lat*dim_y+dim_lat*dim_y*dim_z*tp];
 
 if(dim_y!=1)
   {     
     int yp = (y+1)%dim_lat; nei += phi[x+yp*dim_lat+z*dim_lat*dim_y+dim_lat*dim_y*dim_z*t]; 
     yp = (y-1+dim_lat)%dim_lat; nei += phi[x+yp*dim_lat+z*dim_lat*dim_y+dim_lat*dim_y*dim_z*t]; 
   }      
   
 if(dim_z!=1)
   {
     int zp = (z+1)%dim_lat; nei += phi[x+y*dim_lat+zp*dim_lat*dim_y+dim_lat*dim_y*dim_z*t];
     zp = (z-1+dim_lat)%dim_lat; nei += phi[x+y*dim_lat+zp*dim_lat*dim_y+dim_lat*dim_y*dim_z*t];
   }  

    *dS_n = a*nei*temp+h*temp;
    temp = phi[cnt];
    *dS_o = a*nei*temp+h*temp;

 }

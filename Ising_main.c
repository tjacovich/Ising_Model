#include <stdlib.h>//Standard C Library
#include <math.h>//C math Library
#include <stdio.h>//C I/O library
#include <time.h>//Time functions library
#include "Isingaction.h"//Action function header file
#include "mt64.h"//MT64 random number generator header file
#include "printlattice.h"//function to print the contents of the arrays
#include "printtwopoint.h"//Prints out an average of the correlator for a given field congfiguration
#include <complex.h>//Complex Numbers Library
#include "action.h"//Prints the energy of the entire field
int main(int argc, char *argv[])
  { 
    /*checks to make sure the proper arguments are specified*/
    if(argc!=7)
     {
       printf("The number of arguments is invalid. \n");
       printf("usage: Ising_main dim_lat dim_y h T file_name No \n");
       return 1;
     }
     
    long arg1 = strtol(argv[1], &argv[1],10);//Converts command line arg into lattice spacing
    long arg3 = strtol(argv[2], &argv[2],10);//Converts command line arg into time spacing
    double arg2 = strtod(argv[3], &argv[3]);//Converts command line arg into symmetry breaking term 
    long arg5 = strtol(argv[6], &argv[6], 10);//Converts command line arg to number configs
    int dim_lat = arg1; /*Lattice Dimension*/
    int dim_y = 1; /*Lattice y*/
    int dim_z = 1; /*Lattice z*/
    int dim_t = arg3;/*temporal Dimension*/
    double J =1; /*defines the Nearest neighbor coupling*/
    double h = arg2; /*Symmetry breaking term*/
    int No = arg5; /*Number of field configurations to attempt*/
    int acc = 0;/*number of acccepted proposals*/
    int tot = 0;/*total number of proposals*/
    double T = strtod(argv[4], &argv[4]);/*Temperature variable*/ 
    /*seeding rand() in an attempt to further randomize*/
    init_genrand64(0); 
    
    double*  phi = calloc(dim_lat*dim_y*dim_z*dim_t,sizeof(double));/*main field array*/ 
    double* S = calloc(dim_lat*dim_y*dim_z*dim_t,sizeof(double));/*Hamilton Array*/
    /*Defines the initial configuration of the field*/
    for(int l=0; l<dim_lat*dim_y*dim_z*dim_t; l++)
      {
        double q = (2-2*genrand64_real1());
	int k = 1-2* (int) q;
        phi[l] = (double) k; 
      }
    
    FILE *outputfile = fopen(argv[5],"w+");
    /*This loop initiates a perturbation of a single field point on the lattice,
    and then implements a Metropolis style accept reject of the change in the field*/ 
    double temp;/*temporary field point*/
    double kb =1;/*Boltzmann Constant*/
    double bt = 1/(kb*T);/*Beta factor*/
    for(int i=0; i<No; i++)
      {
        for(int j = 0; j < dim_lat*dim_t; j++)
          {

         /*counts the number of iterations that occur*/ 
         tot++;
             
         /*Perturbs  the field with a pseudorandom real number between -1 and 1*/
	 double q = (2-2*genrand64_real1());
     	 int k = 1-2* (int) q;
      	 temp = k;
            
         /*Generates the action due to the new field point*/  
         double S_n, S_o;
         Isingaction(phi, temp, J, &S_n, &S_o, dim_lat, dim_y, dim_z, dim_t, j, h);
         //printlattice(phi, dim_lat);

         /*Metropolis Accept/Reject*/
         if(exp(-bt*S_n) / exp(-bt*S_o) > genrand64_real2())
           {
	     phi[j] = temp; //writes the new field point to phi array
             S[j] = S_n; //Writes Energy to S array
             acc++; //counts the number of accepted values
	   }
	 else
           { 
       	     S[j]=S_o;//Writes Energy to S array
           }
             
	  }   
           

        if(i>1)
          {
            /*prints the average value of each field configuration*/
            double avg = 0;
            double avgS=0;
            double avgsqred = 0;
            for(int w=0;w<dim_lat*dim_y*dim_z*dim_t; w++)
              {
                avg += phi[w]/(dim_lat*dim_t);
		avgsqred += phi[w]*phi[w]/(dim_lat*dim_t);
              }
	    action(phi, &avgS, J, dim_lat, dim_y, h);
            fprintf(outputfile, "%lf %lf %lf \n", avg, avgsqred, avgS);
          }
      }
    
   /*Prints the percentage of proposals accepted*/
   double bob = ((double) acc/tot);
   printf("%lf \n",bob);
   printlattice(phi,dim_lat);								
   /*Free the allocated memory on the heap*/
   free(phi);
   free(S);
   fclose(outputfile);
   return 0;
 }

#include <stdlib.h>//Standard C Library
#include <math.h>//C math Library
#include <stdio.h>//C I/O library
#include <time.h>//Time functions library
#include "Isingaction.h"//Action function header file
#include "mt64.h"//MT64 random number generator header file
#include "printlattice.h"//function to print the contents of the arrays
#include "printtwopoint.h"//Prints out an average of the correlator for a given field congfiguration
#include <complex.h>//Complex Numbers Library
/*Jacovich 10/16/16*/
/*For 1+1 Fields, step and cstep should be 0.5 for ~70% acceptance.
0.0038 for ~60% in 3+1 Complex*/
/*Jacovich 8/1/16*/
/*All issues with action and number generation fixed.  Currently working with symmetry breaking
in 1+1 dimensions.  Implementing a complex scalar field as well.*/

/*Jacovich 6/29/16*/
/*Changed the random number generator to rand() in an attempt to fix issues with convergence.  
Found convergence with specific step and srand() seed for a given lattice size.  Not sure if
that is what should be expected.*/

/*Jacovich 6/16/16*/
/*This is the main program for the lattice field in 1+1 dimensions.  Future versions
will support 3+1 dimensions.  Action files can be swapped out by use of various headers*/

int main(int argc, char *argv[])
  { 
    /*checks to make sure the proper arguments are specified*/
    if(argc!=7)
     {
       printf("The number of arguments is invalid. \n");
       printf("usage: lattice_main dim_lat dim_t h T file_name No \n");
       return 1;
     }
     
    long arg1 = strtol(argv[1], &argv[1],10);//Converts command line arg into lattice spacing
    long arg3 = strtol(argv[2], &argv[2],10);//Converts command line arg into time spacing
    double arg2 = strtod(argv[3], &argv[3]);//Converts command line arg into symmetry breaking term 
    long arg5 = strtol(argv[7], &argv[7], 10);//Converts command line arg to number configs
    int dim_lat = arg1; /*Lattice Dimension*/
    int dim_y = 1; /*Lattice y*/
    int dim_z = 1; /*Lattice z*/
    int dim_t = arg3;/*temporal Dimension*/
    double* twopoint = calloc(dim_lat, sizeof(double));/*Holds Two Point function values*/
    double J =; /*defines the Nearest neighbor coupling*/
    double h = arg2; /*Symmetry breaking term*/
    int No = arg5; /*Number of field configurations to attempt*/
    double step = 0.4;/*determines the step-size of the perturbation*/
    int acc = 0;/*number of acccepted proposals*/
    int tot = 0;/*total number of proposals*/
    double T = strtod(argv[5], &argv[5]);/*Temperature variable*/ 
    /*seeding rand() in an attempt to further randomize*/
    init_genrand64(0); 
    
    double*  phi = calloc(dim_lat*dim_y*dim_z*dim_t,sizeof(double));/*main field array*/ 
    double* S = calloc(dim_lat*dim_y*dim_z*dim_t,sizeof(double));/*Hamilton Array*/
    /*Defines the initial configuration of the field*/
    for(int l=0; l<dim_lat*dim_y*dim_z*dim_t; l++)
      {
        phi[l] = 2*drand48() - 1; 
      }
   
    FILE *outputfile = fopen(argv[6],"w+");
    /*This loop initiates a perturbation of a single field point on the lattice,
    and then implements a Metropolis style accept reject of the change in the field*/ 
    double temp;/*temporary field point*/
    double kb =1.38065e-23;/*Boltzmann Constant*/
    double bt = 1/(kb*T);/*Beta factor*/
    for(int i=0; i<No; i++)
      {
         for(int j=0; j<dim_lat*dim_y*dim_z*dim_t; j++)
           {
             /*counts the number of iterations that occur*/ 
             tot++;
             
             /*Perturbs  the field with a pseudorandom real number between -1 and 1*/
             temp = phi[j] + step*( 2*drand48() - 1 );
             tempI =  phiI[j] + cstep*(2*drand48() - 1);
            
             /*Generates the action due to the new field point*/  
             double S_n, S_o;
             Isingaction(phi, temp, J, &S_n, &S_o, dim_lat, dim_y, dim_z, dim_t, j, h);
             
             /*Metropolis Accept/Reject*/
             if(exp(-bt*S_n) / exp(-bt*S_o) > drand48())
               {
	               phi[j] = temp; //writes the new field point to phi array
                 S[j] = Sn; //Writes Energy to S array
                 acc++; //counts the number of accepted values
               }
             
           } 
           

        if(i>1000)
          {
            /*prints the average value of each field configuration*/
            double avg = 0;
            double avgS = 0;

            for(int w=0;w<dim_lat*dim_y*dim_z*dim_t; w++)
              {
                avg += phi[w]/(dim_lat*dim_y*dim_z*dim_t);
                avgS += S[w]/(dim_lat*dim_y*dim_z*dim_t); 
              }
            fprintf(outputfile, "%lf %lf\n", avg, avgS);
          }
      }
    
   /*Prints the percentage of proposals accepted*/
   double bob = ((double) acc/tot);
   printf("%lf \n",bob);
								
   /*Free the allocated memory on the heap*/
   free(phi);
   free(S);
   fclose(outputfile);
   return 0;
 }

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./get_params.h"

void get_z(int i, int j, double *coords, plot_params *the_params) {

   double llx = the_params->llx;
   double lly = the_params->lly;
   double urx = the_params->urx;
   double ury = the_params->ury;
   double pw = the_params->pw;
   double ph = the_params->ph;
   
   coords[0] = (double) (urx - llx)/pw*(i+.5) + llx;
   coords[1] = (double) (ury - lly)/ph*(j+.5) + lly;
}


int iterate_pix(double cx, double cy, plot_params *the_params) {
   //use z = x+iy to avoid calling get_z too often
   //return 1 if in set, 0 if not (bw implementation)
   
   int maxiter = the_params->maxiter;
   double x = cx;
   double y = cy;
   double tmp = 0.0;

   for(int iter=1; iter<maxiter; iter++) {
      if(x*x + y*y < 4.0) {
         tmp = x*x - y*y + cx;
         y = 2.0*x*y + cy;
         x = tmp;
      } else {
      return 0;
      }
   }
   // return true if no escape detected
   return 1;
}


int *get_escapes(plot_params *the_params) {
   
   if(!strcmp(the_params->colormode, "bw")) {
   // NOTE: strcmp returns 0 iff str1=str2, so must invert boolean
      int pixh = the_params->ph;
      int pixw = the_params->pw;
      printf("about to malloc\n");
      int *returnarray = malloc(sizeof(int)*pixh*pixw);
      printf("malloced");
      double coords[2];
      for(int j=0; j<pixh; j++) {
         for(int i=0; i<pixw; i++) {
            get_z(i, j, coords, the_params);
            //flip coords becuase i got i,j backwards #oops
            returnarray[i + j*(pixw-1)] = iterate_pix(coords[0], coords[1], the_params);
            printf("pix: val=%d (%d, %d)\n", returnarray[i*(pixh-1)+j], i, j);
         }
      }
      return returnarray;
   } else {
      printf("only bw has been implemented ya dingus!!!\n");
      return NULL;
   }
}


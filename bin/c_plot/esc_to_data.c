#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef ESC_TO_DATA_HEADER
#include "./esc_to_data.h"
#endif

#ifndef GET_STRUCTS
#include "./structs.h"
#endif

void normalizelogv( double *minandmax, pix *pixarray, plot_params *the_params) {

   double logvsum=0.0;
   double logvmin = 1000000.0;
   double logvmax = -100000.0;
   double thislogv = 0.0;
   for(int i=0; i<the_params->pw; i++) {
      for(int j=0; j<the_params->ph; j++) {
         thislogv = pixarray[i+j*the_params->pw].logv;
         if(!isnan(thislogv)) {
            logvsum += thislogv;
         }         
         if(thislogv < logvmin) {
            logvmin = thislogv;
         } else if(thislogv > logvmax) {
            logvmax = thislogv;
         }
      }
   }
   double logvmean = logvsum/(the_params->pw*the_params->ph);

   for(int i=0; i<the_params->pw; i++) {
      for(int j=0; j<the_params->ph; j++) {
         pixarray[i+j*the_params->pw].logv -= logvmean;
      }
   }

   minandmax[0] = logvmin;
   minandmax[1] = logvmax;
   printf("min, max, sum, mean are: %lf %lf %lf %lf\n", minandmax[0], minandmax[1], logvsum, logvmean);

} 

void get_color(int *out, pix *p, pix *pixarray, plot_params *the_params) {
   double rscale = the_params->rscale;
   double gscale = the_params->gscale;
   double bscale = the_params->bscale;
   double rmag = the_params->rmag;
   double gmag = the_params->gmag;
   double bmag = the_params->bmag;
   double rshift = the_params->rshift;
   double gshift = the_params->gshift;
   double bshift = the_params->bshift;
   if(p->n_esc == -1) {
      out[0] = 0;
      out[1] = 0;
      out[2] = 0;
   } else {
      double logv = p->logv;
      out[0] = (int) rmag/2*(1 - tanh(rscale*(logv+rshift)));
      out[1] = (int) gmag/2*(1 - tanh(gscale*(logv+gshift)));
      out[2] = (int) bmag/2*(1 - tanh(bscale*(logv+bshift)));
   }
}

void make_logv_array(double *logvarr, pix *pixarray, plot_params *the_params) {
   int pixh = the_params->ph;
   int pixw = the_params->pw;
   pix *thispix = NULL;

   for(int j=0; j<pixh; j++) {
      for(int i=0; i<pixw; i++) {
         thispix = &(pixarray[i+j*pixw]);
         if(!isnan(thispix->logv)) {
             logvarr[i+j*pixw] = thispix->logv;
         } else {
            logvarr[i+j*pixw] = 0.0;
         }      
      }
   } 
}

double l2_of_lap(double *logvarr, plot_params *the_params, char* stencil) {
   double sum = 0;
   double temp = 0;
   int pixh = the_params->ph;
   int pixw = the_params->pw;
   
   if(!strcmp(stencil, "3x3")) {
      for(int j=1; j<pixh-1; j++) {
         for(int i=1; i<pixw-1; i++) {
            temp +=       logvarr[(i-1) + (j-1)*pixw];
            temp +=       logvarr[ i    + (j-1)*pixw];
            temp +=       logvarr[(i+1) + (j-1)*pixw];
            temp +=       logvarr[(i-1) +  j*pixw];
            temp -= 8.0 * logvarr[ i    +  j*pixw];
            temp +=       logvarr[(i+1) +  j*pixw];
            temp +=       logvarr[(i-1) + (j+1)*pixw];
            temp +=       logvarr[ i    + (j+1)*pixw];
            temp +=       logvarr[(i+1) + (j+1)*pixw];
            sum += temp*temp;
            temp = 0;
         }
      }
      
      sum /= (pixw*pixh);
      return sum;
   }
   
   return -1.0;
}

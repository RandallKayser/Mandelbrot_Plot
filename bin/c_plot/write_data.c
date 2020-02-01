#include <stdio.h>
#include <string.h>
#include <math.h>

#ifndef GET_PARAMS_HEADER
#include "./get_params.h"
#endif

#ifndef GET_ESCAPES_HEADER
#include "./get_escapes.h"
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

/*   for(int i=0; i<the_params->pw; i++) {
      for(int j=0; j<the_params->ph; j++) {
         pixarray[i+j*the_params->pw].logv -= logvmean;
      }
   }
*/
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
   double minandmax[2] = {0,0};
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

void write_data(plot_params *the_params, pix *returnarray) {
   
   char outfile[128] = "";
   char tmp[64] = "";

   strcpy(outfile, the_params->plotdir);
   sprintf(tmp, "/%s.dat", the_params->outname);
   strcat(outfile, tmp);
   printf("the filepath is %s\n", outfile);

   char logvoutfile[128] = "";
   strcpy(logvoutfile, the_params->plotdir);
   sprintf(tmp, "/%s.logv", the_params->outname);
   strcat(logvoutfile, tmp);
   FILE *logvfp = fopen(logvoutfile, "w");
   double thislogv = 0.0;

   FILE *fp = fopen(outfile, "w");
   int pixw = the_params->pw;
   int pixh = the_params->ph;
   int color[3] = {0};
   double minmax[2] = {0,0};
   fprintf(fp, "colormode = %s, pixh = %d, pixw = %d\n", the_params->colormode, pixw, pixh);
//   normalizelogv(minmax, returnarray, the_params);
   for(int j=0; j<pixh; j++) {
      get_color(color, &(returnarray[j*pixw]), returnarray, the_params);
      fprintf(fp, "(%d %d %d)", color[0], color[1], color[2]);
      thislogv = returnarray[j*pixw].logv;
      if(!isnan(thislogv)) {
         fprintf(logvfp, "%lf", thislogv);
      }
      for(int i=1; i<pixw; i++) {     
         get_color(color, &(returnarray[i+j*pixw]), returnarray, the_params);
         fprintf(fp, ", (%d %d %d)", color[0], color[1], color[2]);

         thislogv = returnarray[i+j*pixw].logv;
         if(!isnan(thislogv)) {
            fprintf(logvfp, ", %lf", thislogv);
         }
      }
      fprintf(fp, "\n");
      fprintf(logvfp, "\n");
   }
   fclose(fp);
   fclose(logvfp);
}

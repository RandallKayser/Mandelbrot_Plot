#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "./get_params.h"
#include "./get_escapes.h"

void get_z(pix *p, plot_params *the_params) {
   
   double llx = the_params->llx;
   double lly = the_params->lly;
   double urx = the_params->urx;
   double ury = the_params->ury;
   int pw = the_params->pw;
   int ph = the_params->ph;
   
   //NEEDS OPTIMIZATION: precompute scale_x, scale_y
   p->cx = (double) (urx - llx)/pw*(p->i+.5) + llx;
   p->cy = (double) (ury - lly)/ph*(p->j+.5) + lly;
}


void iterate_pix(pix *p, plot_params *the_params) {
   //use z = x+iy to avoid calling get_z too often
   //return 1 if in set, 0 if not (bw implementation)
   
   int maxiter = the_params->maxiter;
   double cx = p->cx;
   double cy = p->cy;
 
   double x = cx;
   double y = cy;
   double tmp = 0.0;
   double mod = x*x + y*y;
 
   p->n_esc = -1;
   p->escmod = -1.0;
   p->logv = NAN;
   for(int iter=1; iter<maxiter; iter++) {
      if(mod < 1e6) {
         tmp = x*x - y*y + cx;
         y = 2.0*x*y + cy;
         x = tmp;
         mod = x*x + y*y;
      } else {
      p->n_esc = iter;
      p->escmod = mod;
      p->logv = log(log(mod)) - iter * log(2);
      break;
      }
   }
}


void *get_escapes(pix *pixarray, plot_params *the_params) {
   
   int pixh = the_params->ph;
   int pixw = the_params->pw;
   pix *thispix = NULL;
   
   for(int j=0; j<pixh; j++) {
      for(int i=0; i<pixw; i++) {
         thispix = &(pixarray[i + j*pixw]);
         thispix->i = i;
         thispix->j = j;
         get_z(thispix, the_params);
         iterate_pix(thispix, the_params);
      }
   }
}


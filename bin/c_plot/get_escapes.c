#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#ifndef WRITE_DATA_HEADER
#include "./write_data.h"
#endif

#ifndef GET_PARAMS_HEADER
#include "./get_params.h"
#endif
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
   double dx = 1.0;
   double derepsmod = the_params->dereps*the_params->dereps;
   double dy = 0.0;
   double dmod = 1.0;
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
      //rewrite  this logic block
      if(mod > 1e6) {
         p->n_esc = iter;
         p->escmod = mod;
         p->logv = log(log(mod)) - iter * log(2);
         break;
      } else if(dmod < derepsmod) {
         break;
      } else {
         tmp = 2.0*(dx*x - dy*y);
         dy = 2.0*(x*dy + dx*y);
         dx = tmp;
         tmp = x*x - y*y + cx;
         y = 2.0*x*y + cy;
         x = tmp;
         mod = x*x + y*y;
         dmod = dx*dx + dy*dy;
      }
   }
}


void get_escapes(pix *pixarray, plot_params *the_params) {
   
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


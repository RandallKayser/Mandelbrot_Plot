#include <stdio.h>
#include <string.h>
#include <math.h>

#ifndef GET_PARAMS_HEADER
#include "./get_params.h"
#endif

#ifndef GET_ESCAPES_HEADER
#include "./get_escapes.h"
#endif

#ifndef ESC_TO_DATA_HEADER
#include "./esc_to_data.h"
#endif

void write_data(plot_params *the_params, pix *returnarray) {
   
   char outfile[128] = "";
   char tmp[64] = "";

   strcpy(outfile, the_params->plotdir);
   sprintf(tmp, "%s.dat", the_params->outname);
   strcat(outfile, tmp);
   FILE *fp = fopen(outfile, "w");
   int pixw = the_params->pw;
   int pixh = the_params->ph;
   int color[3] = {0};

   fprintf(fp, "colormode = %s, pixh = %d, pixw = %d\n", the_params->colormode, pixw, pixh);

   for(int j=0; j<pixh; j++) {
      get_color(color, &(returnarray[j*pixw]), returnarray, the_params);
      fprintf(fp, "(%d %d %d)", color[0], color[1], color[2]);

      for(int i=1; i<pixw; i++) {     
         get_color(color, &(returnarray[i+j*pixw]), returnarray, the_params);
         fprintf(fp, ", (%d %d %d)", color[0], color[1], color[2]);
      }
      fprintf(fp, "\n");
   }
   fclose(fp);
}

void write_logv(plot_params *the_params, pix *returnarray) {
  
   char tmp[64] = "";
   char logvoutfile[128] = "";
   strcpy(logvoutfile, the_params->plotdir);
   sprintf(tmp, "/%s.logv", the_params->outname);
   strcat(logvoutfile, tmp);
   FILE *logvfp = fopen(logvoutfile, "w");
   double thislogv = 0.0;

   int pixw = the_params->pw;
   int pixh = the_params->ph;

   for(int j=0; j<pixh; j++) {
      thislogv = returnarray[j*pixw].logv;
      if(!isnan(thislogv)) {
         fprintf(logvfp, "%lf", thislogv);
      }
      for(int i=1; i<pixw; i++) {     
         thislogv = returnarray[i+j*pixw].logv;
         if(!isnan(thislogv)) {
            fprintf(logvfp, ", %lf", thislogv);
         }
      }
      fprintf(logvfp, "\n");
   }
   fclose(logvfp);
}

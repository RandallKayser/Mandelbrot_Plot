#include <stdio.h>
#include <string.h>
#ifndef GET_PARAMS_HEADER
#define GET_PARAMS_HEADER 1
#include "./get_params.h"
#endif
void write_data(plot_params *the_params, int *returnarray) {
   
   char outfile[128] = "";
   char tmp[64] = "";
   strcpy(outfile, the_params->plotdir);
   sprintf(tmp, "%d.dat", the_params->linenum);
   strcat(outfile, tmp);
   printf("the filepath is %s\n", outfile);
   FILE *fp = fopen(outfile, "w");
   int pixw = the_params->pw;
   int pixh = the_params->ph;
   
   fprintf(fp, "colormode = %s, pixh = %d, pixw = %d\n", the_params->colormode, pixw, pixh);
   
   // height of image is number of rows incrementing i moves down to next row, j over to next column
   if(!strcmp(the_params->colormode, "bw")) {
      for(int j=0; j<pixh; j++) {
         
         fprintf(fp, "%d", returnarray[j*(pixw-1)]);
         
         for(int i=1; i<pixw; i++) {
         
            fprintf(fp, ", %d", returnarray[i + j*(pixw-1)]);
         }
         
         fprintf(fp, "\n");
      }
   } else {
      printf("not implemented ya dingus!!!\n");

   }
   fclose(fp);
}

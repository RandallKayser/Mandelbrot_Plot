#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#ifndef GET_STRUCTS
#include "structs.h"
#endif

#ifndef GET_WRITE_DATA_HEADER
#include "./write_data.h"
#endif

#ifndef GET_PARAMS_HEADER
#include "./get_params.h"
#endif

#ifndef GET_ESCAPES_HEADER
#include "./get_escapes.h"
#endif 

#ifndef GET_ESC_TO_DATA_HEADER
#include "./esc_to_data.h"
#endif
int main(int argc, char *argv[]) {
   if(argc==1) {
      printf("USAGE:\n\n\t./mandelplot plotdirname lineranges \n\t\tplots specified by linerange(s),\n\t\teach linerange a single int, or int1-int2\n");
      printf("\t ./mandeplot plotdirname bin depth plotinname threshold \n\t\tplot via bisection up to level = depth \n\t\twith laplacian pruning images with l2(lap) < threshold\n");
      return 0;
   }
   if(!strcmp(argv[2], "bin")) {
      char *endptr;
      *endptr = "";
      int depth = strtol(argv[3], &endptr, 10);
      bisectionplot(depth, argv[1], argv[4]);
   } else {
      multiplot(argc, argv);
   }
   return 1; 
}

void multiplot(int argc, char *argv[]) {

   int *linelist = malloc(sizeof(int)*256);

   make_line_list(linelist, argc, argv);
   plot_params **plotparams_arr;
   plot_params *tmp = malloc(sizeof(plot_params)*(linelist[0]-1));
   plotparams_arr = &tmp;
   
   char relfp[258] = "../../dat/"; 
   strcat(relfp, argv[1]);
   strcat(relfp, "/");
   strcpy(plotparams_arr[0]->plotdir, relfp);
   
   char plotlist_fname[64] = "plotlist";
   fread_params(linelist, plotlist_fname, plotparams_arr);
   pix *pixarray = {0};
   double *logvarray = NULL;
   int ph = 0;
   int pw = 0;
   double lapl2 = 0.0;

   for(int i=0; i<linelist[0]-1; i++) {
      printf("plotparams_arr[i] = %i\n", plotparams_arr[i]);
      print_params(plotparams_arr[i]);
      ph = plotparams_arr[i]->ph;
      pw = plotparams_arr[i]->pw;
      pixarray = malloc(sizeof(pix)*ph*pw);
      logvarray = malloc(sizeof(double)*ph*pw);

      get_escapes(pixarray, plotparams_arr[i]);

      make_logv_array(logvarray, pixarray, plotparams_arr[i]);
      lapl2 = l2_of_lap(logvarray, plotparams_arr[i], "3x3");
      printf("lapl2 = %F\n", lapl2);

      write_data(plotparams_arr[i], pixarray);
      // TODO: split write_data into write_logv
      // Write logv laplacian kernel
      free(pixarray);
      free(logvarray);
   }
}

int bisectionplot(int level, char *plotdirfp, char *plotinname) {
   if(level==-1) {
      return 1;
   }
   printf("plotdirfp = %s  plotinname = %s\n\n", plotdirfp, plotinname);
   plot_params *tmp = malloc(sizeof(plot_params)*4);
   plot_params **the_params;
   the_params = &tmp;
   strcpy(the_params[0]->plotdir, plotdirfp);

   int *linelist = malloc(sizeof(int)*32);
   linelist[0]=5;
   linelist[1]=1;
   linelist[2]=2;
   linelist[3]=3;
   linelist[4]=4;
   //TODO: write code to modify linelist[0] if fread hits EOF early

   int plotnum = fread_params(linelist, plotinname, the_params);

   printf("plotnum = %i lines[0] = %i\n", plotnum, linelist[0]-1);
   pix *pixarray = NULL;
   double *logvarray = NULL;
   int ph = 0;
   int pw = 0;
   double lapl2[4]= {0.0};
   double thresh = 0.0;

   for(int i=0; i<linelist[0]-1; i++) {
      printf("i=%i, linelistmax = %i\n", i, linelist[0]-1);
      printf("plotdirfp = %s\n", plotdirfp);
      print_params(the_params[i]);
      ph = the_params[i]->ph;
      pw = the_params[i]->pw;
      
      printf("about to malloc\n\n");
      pixarray = malloc(sizeof(pix)*ph*pw);
      logvarray = malloc(sizeof(double)*ph*pw);
      printf("malloced structs\n\n");
      get_escapes(pixarray, the_params[i]);
      printf("got escapes \n\n");
      make_logv_array(logvarray, pixarray, the_params[i]);
      lapl2[i] = l2_of_lap(logvarray, the_params[i], "3x3");
      write_data(the_params[i], pixarray);
      printf("wrote data\n\n");
      free(pixarray);
      free(logvarray);
      printf("structs freed\n\n");
   }

   char temp[128] = ""; 

   for(int i=0; i < linelist[0]-1; i++) {
      if(lapl2[i] > thresh) {
         sprintf(temp, "%s%i", plotinname, i);
         printf("plotdirfp/plotinname = %s%s\n", plotdirfp, plotinname);
         bisect_params(the_params[i], temp, plotdirfp);
         bisectionplot(level-1, plotdirfp, temp);
      }
   }
   free(linelist);
   return 1;
}

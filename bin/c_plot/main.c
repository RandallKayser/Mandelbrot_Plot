#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
      printf("\t ./mandeplot plotdirname bin depth threshold \n\t\tplot via bisection up to level = depth \n\t\twith laplacian pruning images with l2(lap) < threshold\n");
      return 0;
   }
   if(strcmp(argv[2], "bin")) {
      multiplot(argc, argv);
   } else {
      char *endptr;
      *endptr = "";
      int depth = strtol(argv[3], &endptr, 10);
//      bisectionplot();
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
   strcpy(plotparams_arr[0]->plotdir, relfp);
   fread_params(linelist, plotparams_arr);
   pix *pixarray = {0};
   double *logvarray = NULL;
   int ph = 0;
   int pw = 0;
   double lapl2 = 0.0;
   for(int i=0; i<linelist[0]-1; i++) {
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

/* int bisectionplot(int level, char* plotlistfp) {
   if(level=-1) {
      return 1;
   }

   do_plots()
   double l2oflap1 = get_l2_of_logv_lapl();
   double l2oflap2 = get_l2_of_logv_lapl();
   double l2oflap3 = get_l2_of_logv_lapl();
   double l2oflap4 = get_l2_of_logv_lapl();
   
   if(l2oflap1 > thresh) {
      buildplotlist1();
      bisectionplot(level-1, filepath/subfolder1);
   }   
   if(l2oflap1 > thresh) {
      buildplotlist2();
      bisectionplot(level-1, filepath/subfolder2);
   }   
   if(l2oflap1 > thresh) {
      bisectionplot(level-1, filepath/subfolder3);
   }   
   if(l2oflap1 > thresh) {
      bisectionplot(level-1, filepath/subfolder4);
   } 
   return 1;
} */

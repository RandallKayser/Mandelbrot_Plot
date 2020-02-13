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

int main(int argc, char *argv[]) {
   if(argc==1) {
      printf("USAGE:\n\n\t./mandelplot plotdirname lineranges \n\t\t plots specified by linerange(s),\n\t\t\teach linerange a single int, or int1-int2\n");
      printf("\t (not yet) ./mandelplot m plotdirname all \n\t\t(m)ultiple plot that plots everything in plotdirname\n");
      return 0;
   }

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
      int ph = 0;
      int pw = 0;

      for(int i=0; i<linelist[0]-1; i++) {

         print_params(plotparams_arr[i]);
         ph = plotparams_arr[i]->ph;
         pw = plotparams_arr[i]->pw;
         pixarray = malloc(sizeof(pix)*ph*pw);

         get_escapes(pixarray, plotparams_arr[i]);
         write_data(plotparams_arr[i], pixarray);
         // TODO: split write_data into write_logv
         // Write logv laplacian kernel
         free(pixarray);
      }

   return 1; 
}

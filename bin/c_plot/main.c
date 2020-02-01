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
      printf("USAGE:\n\t./mandelplot s plotdirname linenum\n\t\t(s)imple plot of line linenum in .../dat/plotdirname\n"); 
      printf("\t./mandelplot m plotdirname lineranges \n\t\t(m)ultiple plots specified by each linerange,\n\t\t\teach linerange a single int, or int1-int2\n");
      printf("\t./mandelplot m plotdirname all \n\t\t(m)ultiple plot that plots everything in plotdirname\n");
   return 0;
   }

   if(!strcmp(argv[1], "s")) {
      char **ptr = NULL;
      int linenum = strtol(argv[3], ptr, 10);
      
      char plotdir[256] = "";
      strcpy(plotdir, "../../dat/");
      strcat(plotdir, argv[3]);
      strcat(plotdir, "/");
      run_params *runparams= malloc(sizeof(run_params));
      plot_params *plotparams = malloc(sizeof(plot_params));     
      return 1;


   } else if(!strcmp(argv[1], "m")) {


      int *linelist = malloc(sizeof(int)*256);
 
      make_line_list(linelist, argc, argv);
      plot_params **plotparams_arr;
      plot_params *tmp = malloc(sizeof(plot_params)*(linelist[0]-1));
      plotparams_arr = &tmp;
      
      char relfp[258] = "../../dat/";     
      strcat(relfp, argv[2]);
      strcpy(plotparams_arr[0]->plotdir, relfp);

      printf("about to enter fread\n");
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
         
         free(pixarray);	
      }
	return 1;
   }
}

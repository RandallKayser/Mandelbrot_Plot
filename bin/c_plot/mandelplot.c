#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "./write_data.h"

#ifndef GET_PARAMS_HEADER
#define GET_PARAMS_HEADER 1
#include "./get_params.h"
#endif

#ifndef GET_ESCAPES_HEADER
#define GET_ESCAPES_HEADER 1
#include "./get_escapes.h"
#endif

int main(int argc, char *argv[]) {
   time_t t_whole;
   time_t t_esc;
   time_t t_write_data;

   double tw = 0.0;
   double te = 0.0;
   double twd = 0.0;
   t_whole = clock();

   if(argc!=3) {
      printf("Usage: ./exec \"plot directory in .../dat\" linenum \n");
      return 0;
   }
   
   char pathtodat[128] = "../../dat/";
   plot_params *the_params = malloc(sizeof(plot_params));
   char **ptr = NULL;
   
   // strtol(char *n, char **p, int b) converts string n to base b long int.
   // if **p!=NULL, mutates *p to next character after int (which seems to be EOS, should check argv docs)
   the_params->linenum = strtol(argv[2], ptr, 10);
   
   strcat(pathtodat, argv[1]);
   strcat(pathtodat, "/");
   strcpy(the_params->plotdir, pathtodat);
   
   read_params(the_params);
   print_params(the_params);

   int pw = the_params->pw;
   int ph = the_params->ph;
   pix *returnarray = malloc(sizeof(pix)*pw*ph);
   
   t_esc = clock();
   get_escapes(returnarray, the_params);
   t_esc = clock() - t_esc;
   
   t_write_data = clock();
   write_data(the_params, returnarray);
   t_write_data = clock() - t_write_data;
  
   free(returnarray);
   t_whole = clock() - t_whole;
   
   tw = ((double) t_whole)/CLOCKS_PER_SEC;
   te= ((double) t_esc)/CLOCKS_PER_SEC;
   twd= ((double) t_write_data)/CLOCKS_PER_SEC;
   printf("\nTotal Time: %f\nGet Escapes Time:%f\nWrite Data Time: %f\n", tw, te, twd);
}

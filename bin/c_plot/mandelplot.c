#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

   if(argc!=3) {
      printf("Usage: ./exec linenum \"plot directory in .../dat\"\n");
      return 0;
   }
   char pathtodat[128] = "../../dat/";
   plot_params *the_params = malloc(sizeof(plot_params));

   char **ptr = NULL;
   // strtol(char *n, char **p, int b) converts string n to base b long int.
   // if **p!=NULL, mutates *p to next character after int (which seems to be EOS, should check argv docs)
   the_params->linenum = strtol(argv[1], ptr, 10);
   
   //pathtodat defined in get_params.h
   
   strcat(pathtodat, argv[2]);
   strcat(pathtodat, "/");
   strcpy(the_params->plotdir, pathtodat);
   printf("the_params says plotdir = %s\n", the_params->plotdir);
   read_params(the_params);
   printf("we read yall\n");
   print_params(the_params);
   
   int *returnarray = NULL;
   returnarray = get_escapes(the_params);
   write_data(the_params, returnarray);
}

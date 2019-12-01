#include <stdio.h>
#include <stdlib.h>
#include "./write_data.h"
#include "./get_params.h"
int main(int argc, char *argv[]) {

   if(argc!=3) {
      printf("Usage: ./exec linenum \"filepath to data folder\"");
   }

   plot_params *the_params = malloc(sizeof(plot_params));
   char **ptr;
   int linenum = strtol(argv[1], ptr, 10);
   printf("linenum is %d\n", linenum);   
   char *filepath = argv[2];
   read_params(filepath, linenum, the_params);
   print_params(the_params);
}

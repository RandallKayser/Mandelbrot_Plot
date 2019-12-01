#include <stdio.h>
#include <string.h>
#include "./get_params.h"

void read_params(char runfolder[256], int linenum, plot_params *paramsout) {
   // set up filepath, running main from working directory bin/c_plot, supplying _name_ of run folder
   // TODO: error handling of filepath convention?
   char filepath[512] = "../../dat/";
   strcat(filepath, runfolder);
   strcat(filepath, "/plotlist");
   printf(filepath);
   FILE* paramsfile = fopen(filepath, "r");
   if(paramsfile != NULL) {
      printf("paramsfile opened properly\n");
   }
   double allx, ally, aurx, aury;
   int apw, aph;
   
   for(int i=0; i!=linenum; i++) {
      fscanf(paramsfile, "%lf, %lf, %lf, %lf, %d, %d\n", &allx, &ally, &aurx, &aury, &apw, &aph);
      printf("%lf, %lf, %lf, %lf, %d, %d\n", allx, ally, aurx, aury, apw, aph); 
   }  
   
   paramsout->llx = allx;
   paramsout->lly = ally;
   paramsout->urx = aurx; 
   paramsout->ury = aury;
   paramsout->pw = apw;
   paramsout->ph = aph;

   
}

void print_params(plot_params *thisparams) {
   printf("These plotparams are:\n\nllx=%lf\nlly=%lf\nurx=%lf\nury=%lf\npw=%d\nph=%d\n\n", thisparams->llx, thisparams->lly, thisparams->urx, thisparams->ury, thisparams->pw, thisparams->ph);

}

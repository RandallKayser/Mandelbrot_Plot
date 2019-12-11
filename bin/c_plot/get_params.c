#include <stdio.h>
#include <string.h>
#include "./get_params.h"

void read_params(plot_params *paramsout) {
   // set up filepath, running main from working directory bin/c_plot, supplying _name_ of run folder
   // TODO: error handling of filepath convention?
   
   int linenum = paramsout->linenum;
   char filepath[512]="";
   strcat(filepath, paramsout->plotdir);
   strcat(filepath, "plotlist");
   FILE* paramsfile = fopen(filepath, "r");
   
   double allx = 0.0;
   double ally = 0.0;
   double aurx = 0.0;
   double aury = 0.0;
   int amaxiter = 0; 
   int apw = 0;
   int aph = 0;
   char acolormode[20]= "";
   
   for(int i=0; i<linenum; i++) {
      fscanf(paramsfile, "%lf, %lf, %lf, %lf, %d, %d, %d, %s\n", &allx, &ally, &aurx, &aury, &amaxiter, &apw, &aph, acolormode);
   }  

   fclose(paramsfile);   
   paramsout->llx = allx;
   paramsout->lly = ally;
   paramsout->urx = aurx; 
   paramsout->ury = aury;
   paramsout->maxiter = amaxiter;
   paramsout->pw = apw;
   paramsout->ph = aph;
   strcpy(paramsout->colormode, acolormode);
   
}

void print_params(plot_params *thisparams) {
   printf("These plotparams are:\n\nlinenum = %d\nllx=%lf\nlly=%lf\nurx=%lf\nury=%lf\nmaxiter=%d\npw=%d\nph=%d\ncolormode = %s\n\n", thisparams->linenum, thisparams->llx, thisparams->lly, thisparams->urx, thisparams->ury, thisparams->maxiter, thisparams->pw, thisparams->ph, thisparams->colormode);

}

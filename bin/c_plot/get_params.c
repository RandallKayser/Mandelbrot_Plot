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
   double adereps = 0.0;
   int apw = 0;
   int aph = 0;
   char acolormode[20]= "";
   double armag = 255.0;
   double agmag = 255.0;
   double abmag = 255.0;
   double arscale = 1.0;
   double agscale = 1.0;
   double abscale = 1.0;
   double arshift = 0.0;
   double agshift = 0.0;
   double abshift = 0.0;
   char p[512];
   for(int i=1; i<linenum; i++) {
      fgets(p, 5048, paramsfile);
   }
   
   fscanf(paramsfile, "%lf, %lf, %lf, %lf, %d, %lf, %d, %d, %[^,], %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf\n", &allx, &ally, &aurx, &aury, &amaxiter, &adereps, &apw, &aph, acolormode, &armag, &agmag, &abmag, &arscale, &agscale, &abscale, &arshift, &agshift, &abshift);

   fclose(paramsfile);   

   paramsout->llx = allx;
   paramsout->lly = ally;
   paramsout->urx = aurx; 
   paramsout->ury = aury;
   paramsout->maxiter = amaxiter;
   paramsout->dereps = adereps;
   paramsout->pw = apw;
   paramsout->ph = aph;
   strcpy(paramsout->colormode, acolormode);
   paramsout->rmag = armag;
   paramsout->gmag = agmag;
   paramsout->bmag = abmag;
   paramsout->rscale = arscale;
   paramsout->gscale = agscale;
   paramsout->bscale = abscale;
   paramsout->rshift = arshift;
   paramsout->gshift = agshift;
   paramsout->bshift = abshift;

}

void print_params(plot_params *thisparams) {
   printf("These plotparams are:\n\nlinenum=%d\nllx=%lf\nlly=%lf\nurx=%lf\nury=%lf\nmaxiter=%d\ndereps=%lf\npw=%d\nph=%d\ncolormode=%s\nlpcw=%lf\n\n", thisparams->linenum, thisparams->llx, thisparams->lly, thisparams->urx, thisparams->ury, thisparams->maxiter, thisparams->dereps, thisparams->pw, thisparams->ph, thisparams->colormode, thisparams->rshift);

}

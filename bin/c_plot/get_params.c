#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef GET_STRUCTS
#include "structs.h"
#endif
#ifndef GET_PARAMS_HEADER
#include "get_params.h"
#endif

plot_params *init_plot_params(char *plotdir, char *outname, int linenum,
      double llx, double lly, double urx,
      double ury, int maxiter, double dereps, int pw, int ph, char *colormode,
      double rmag, double gmag, double bmag, double rscale, double gscale, double bscale,
      double rshift, double gshift, double bshift) {
   
   plot_params *ret_ptr = malloc(sizeof(plot_params));
   strcpy(ret_ptr->plotdir, plotdir);
   strcpy(ret_ptr->outname, outname);
   ret_ptr->linenum = linenum;
   ret_ptr->llx = llx;
   ret_ptr->lly = lly;
   ret_ptr->urx = urx;
   ret_ptr->ury = ury; 
   ret_ptr->maxiter = maxiter; 
   ret_ptr->dereps = dereps; 
   ret_ptr->pw = pw;
   ret_ptr->ph = ph; 
   strcpy(ret_ptr->colormode, colormode);
   ret_ptr->rmag = rmag;
   ret_ptr->gmag = gmag;
   ret_ptr->bmag = bmag;
   ret_ptr->rscale = rscale;
   ret_ptr->gscale = gscale;
   ret_ptr->bscale = bscale;
   ret_ptr->rshift = rshift;
   ret_ptr->gshift = gshift;
   ret_ptr->bshift = bshift;

   return ret_ptr;
}

void make_line_list(int *linelist, int argctot, char *args[]) {
   // return linelist populated with values:
   //       linelist[0] = sum of true entries
   //       linelist[maxlineval] = PARAMS_BREAK
   
   char scratch[64] = "";
   char *scratchptr[2] = {""}; 
   char **ptr;
   int offset = 1;
   int low = 0;
   int high = 0;
   for(int i=3; i<argctot; i++) {
      strcpy(scratch, args[i]);
      scratchptr[0] = strtok(scratch, "-");
      scratchptr[1] = strtok(NULL, "-");
      if(scratchptr[1] != NULL) {
         low = strtol(scratchptr[0], ptr, 10);
         high = strtol(scratchptr[1], ptr, 10);
         for(int i=low; i<=high; i++) {
            linelist[offset] = i;
            offset++;
         }
      } else {
         low = strtol(scratchptr[0], ptr, 10);
         linelist[offset] = low;
         offset++;
      }
   }
   linelist[0] = offset;
}

void fread_params(int *lines, plot_params **paramsout) {
   //lines[0] = end of lineslist
   //lines[i] = line sourcing parameters for struct paramsout[i]
   // set up filepath, running main from working directory bin/c_plot, supplying _name_ of run folder
   // TODO: error handling of filepath convention?
   
   char filepath[512]="";
   strcpy(filepath, paramsout[0]->plotdir);
   strcat(filepath, "/plotlist");
   printf("the filepath is: %s\n", filepath);
   FILE* paramsfile = fopen(filepath, "r");
   char aoutname[64] = {"\0"};
   //bounds
   double allx = 0.0;
   double ally = 0.0;
   double aurx = 0.0;
   double aury = 0.0;
   
   int amaxiter = 0;
   double adereps = 0.0;
   int apw = 0;
   int aph = 0;
   char acolormode[8]= {"\0"};

   //overal channel strength
   double armag = 255.0;
   double agmag = 255.0;
   double abmag = 255.0;

   //scaling factor in tanh
   double arscale = 1.0;
   double agscale = 1.0;
   double abscale = 1.0;

   //shift in tanh
   double arshift = 0.0;
   double agshift = 0.0;
   double abshift = 0.0;

   //tracks index of paramsout[]
   int offset = 0;
   // holds junk lines
   char p[512];
   // which line in file are we at
   int fline=1;
   for(int i=1; i<lines[0]; i++) {
      while(fline<lines[i]) {
         //we dont want this line; give to placeholder
         fgets(p, 2048, paramsfile);
         fline++;
      }

      //now we want this line, scanf and set params
      fscanf(paramsfile, "%[^,], %lf, %lf, %lf, %lf, %d, %lf, %d, %d, %[^,], %d, %d, %d, %lf, %lf, %lf, %lf, %lf, %lf\n",
            aoutname, &allx, &ally, &aurx, &aury, &amaxiter, &adereps, &apw, &aph,
            acolormode, &armag, &agmag, &abmag, &arscale, &agscale, &abscale,
            &arshift, &agshift, &abshift);        
      paramsout[offset] = init_plot_params(paramsout[0]->plotdir, aoutname, 
            fline, allx, ally,  aurx, aury,
            amaxiter, adereps, apw, aph, acolormode,
            armag, agmag, abmag,
            arscale, agscale, abscale, 
            arshift, agshift, abshift);
      offset++;
      fline++;
   }

   fclose(paramsfile);   
}

void print_params(plot_params *thisparams) {
   printf("These plotparams are:\n\nplotdir=%s\n", thisparams->plotdir);
	printf("outname=%s\n", thisparams->outname);
	printf("linenum=%d\n", thisparams->linenum);
	printf("llx=%lf\n", thisparams->llx);
	printf("lly=%lf\n", thisparams->lly);
	printf("urx=%lf\n", thisparams->urx);
	printf("ury=%lf\n", thisparams->ury);
	printf("maxiter=%d\n", thisparams->maxiter);
	printf("dereps=%lf\n", thisparams->dereps);
	printf("pw=%d\n", thisparams->pw);
	printf("ph=%d\n", thisparams->ph);
	printf("colormode=%s\n", thisparams->colormode);
	printf("rmag=%lf\n", thisparams->rmag);
	printf("gmag=%lf\n", thisparams->gmag);
	printf("bmag=%lf\n", thisparams->bmag);
	printf("rscale=%lf\n", thisparams->rscale);
	printf("gscale=%lf\n", thisparams->gscale);
	printf("bscale=%lf\n", thisparams->bscale);
	printf("rshift=%lf\n", thisparams->rshift);
	printf("gshift=%lf\n", thisparams->gshift);
	printf("bshift=%lf \n\n", thisparams->bshift); 
}

void fprint_params(char *filename, plot_params *thisparams) {}

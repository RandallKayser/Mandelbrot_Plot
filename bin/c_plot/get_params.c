#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef GET_STRUCTS
#include "structs.h"
#endif
#ifndef GET_PARAMS_HEADER
#include "get_params.h"
#endif

plot_params *init_plot_params(char *plotdir, char *outname,
      double llx, double lly, double urx, double ury,
      int maxiter, double dereps, int pw, int ph, char *colormode,
      double rmag, double gmag, double bmag,
      double rscale, double gscale, double bscale,
      double rshift, double gshift, double bshift) {
   
   plot_params *ret_ptr = malloc(sizeof(plot_params));
   strcpy(ret_ptr->plotdir, plotdir);
   strcpy(ret_ptr->outname, outname);
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
   for(int i=2; i<argctot; i++) {
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

int fread_params(int *lines, char* plotlist_fname, plot_params **paramsout) {
   //lines[0] = end of lineslist
   //lines[i] = line sourcing parameters for struct paramsout[i]
   // set up filepath, running main from working directory bin/c_plot, supplying _name_ of run folder
   // TODO: error handling of filepath convention?
   
   char filepath[512]="";
   strcpy(filepath, paramsout[0]->plotdir);
   strcat(filepath, plotlist_fname);
   printf("fread filepath is: %s\n", filepath);
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
   int retval = 0;
   for(int i=1; i<lines[0]; i++) {
      
      printf("params_ptr[%d] = %i\n", offset, paramsout[offset]);
      while(fline<lines[i]) {
         //we dont want this line; give to placeholder
         fgets(p, 2048, paramsfile);
         fline++;
      }

      //now we want this line, scanf and set params
      retval = fscanf(paramsfile, "%[^,], %lf, %lf, %lf, %lf, %d, %lf, %d, %d, %[^,], %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf\n",
            aoutname, &allx, &ally, &aurx, &aury, &amaxiter, &adereps, &apw, &aph,
            acolormode, &armag, &agmag, &abmag, &arscale, &agscale, &abscale,
            &arshift, &agshift, &abshift);        
      (*paramsout)[offset] = *init_plot_params(paramsout[0]->plotdir, aoutname, 
            allx, ally,  aurx, aury,
            amaxiter, adereps, apw, aph, acolormode,
            armag, agmag, abmag,
            arscale, agscale, abscale, 
            arshift, agshift, abshift);
      print_params(paramsout[offset]);
      if(retval != 19) {
         printf("retval = %i\n", retval);
         lines[0] = offset+1;
         return offset;
      }
      offset++;
      fline++;
   }

   fclose(paramsfile);   
   printf("fread sucessful\n");
   return offset;
}

void print_params(plot_params *thisparams) {
   
   if(thisparams==NULL) {
      printf("NULL PARAMS POINTER FOUND! ABORTING...\n\n\n");
   } else {
      printf("~~~~~~~~   These plotparams are:   ~~~~~~~~~\n\n");

      if(thisparams->plotdir != NULL) {
         printf("plotdir=%s\n", thisparams->plotdir);
      } else {
         printf("plotdir=NULL\n");
      }

      if(thisparams->outname != NULL) {
         printf("outname=%s\n", thisparams->outname);
      } else {
         printf("outname=NULL\n");
      }

      printf("llx=%lf\n", thisparams->llx);
      printf("lly=%lf\n", thisparams->lly);
      printf("urx=%lf\n", thisparams->urx);
      printf("ury=%lf\n", thisparams->ury);
      printf("maxiter=%i\n", thisparams->maxiter);
      printf("dereps=%lf\n", thisparams->dereps);
      printf("pw=%i\n", thisparams->pw);
      printf("ph=%i\n", thisparams->ph);
      if(thisparams->outname != NULL) {
         printf("colormode=%s\n", thisparams->colormode);
      } else {
         printf("colormode=NULL\n");
      }
      printf("rmag=%lf\n", thisparams->rmag);
      printf("gmag=%lf\n", thisparams->gmag);
      printf("bmag=%lf\n", thisparams->bmag);
      printf("rscale=%lf\n", thisparams->rscale);
      printf("gscale=%lf\n", thisparams->gscale);
      printf("bscale=%lf\n", thisparams->bscale);
      printf("rshift=%lf\n", thisparams->rshift);
      printf("gshift=%lf\n", thisparams->gshift);
      printf("bshift=%lf\n\n", thisparams->bshift); 
   }
}

void fprint_params(char *filename, plot_params *thisparams) {
   FILE* paramsfile = NULL;

   if((paramsfile = fopen(filename, "a")) != NULL) {
      printf("fprint filename: %s\n", filename); 
      fprintf(paramsfile, "%s, %lf, %lf, %lf, %lf, %d, %lf, %d, %d, %s, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf, %lf\n",
         thisparams->outname,
         thisparams->llx, thisparams->lly, thisparams->urx, thisparams->ury,
         thisparams->maxiter, thisparams->dereps,
         thisparams->pw, thisparams->ph, thisparams->colormode,
         thisparams->rmag,   thisparams->gmag,   thisparams->bmag,
         thisparams->rscale, thisparams->gscale, thisparams->bscale,
         thisparams->rshift, thisparams->gshift, thisparams->bshift);
      fclose(paramsfile);
   } else {
      printf("fprint_params failed to open file\n");
   }
}

void bisect_params(plot_params *the_params, char *outfilename, char *plotdir) {
   char plotlistfp[256] = "";
   strcpy(plotlistfp, plotdir);
   strcat(plotlistfp, outfilename);
   plot_params *spp1 = NULL; 
   plot_params *spp2 = NULL; 
   plot_params *spp3 = NULL; 
   plot_params *spp4 = NULL; 
   double mpx = (the_params->urx + the_params->llx) / 2.0;
   double mpy = (the_params->ury + the_params->lly) / 2.0;
   char temp[256] = "";

   strcpy(temp, the_params->outname);
   strcat(temp, "0");
   spp1 = init_plot_params(plotdir, temp,
      mpx, mpy, the_params->urx, the_params->ury,
      the_params->maxiter, the_params->dereps, the_params->pw, the_params->ph, the_params->colormode,
      the_params->rmag, the_params->gmag, the_params->bmag,
      the_params->rscale, the_params->gscale, the_params->bscale,
      the_params->rshift, the_params->gshift, the_params->bshift);
   fprint_params(plotlistfp, spp1);

   strcpy(temp, the_params->outname);
   strcat(temp, "1");
   spp2 = init_plot_params(plotdir, temp,
      the_params->llx, mpy, mpx, the_params->ury,
      the_params->maxiter, the_params->dereps, the_params->pw, the_params->ph, the_params->colormode,
      the_params->rmag, the_params->gmag, the_params->bmag,
      the_params->rscale, the_params->gscale, the_params->bscale,
      the_params->rshift, the_params->gshift, the_params->bshift);
   fprint_params(plotlistfp, spp2);

   strcpy(temp, the_params->outname);
   strcat(temp, "2");
   spp3 = init_plot_params(plotdir, temp,
      the_params->llx, the_params->lly, mpx, mpy,
      the_params->maxiter, the_params->dereps, the_params->pw, the_params->ph, the_params->colormode,
      the_params->rmag, the_params->gmag, the_params->bmag,
      the_params->rscale, the_params->gscale, the_params->bscale,
      the_params->rshift, the_params->gshift, the_params->bshift);
   fprint_params(plotlistfp, spp3);

   strcpy(temp, the_params->outname);
   strcat(temp, "3");
   spp4 = init_plot_params(plotdir, temp,
      mpx, the_params->lly, the_params->urx, mpy,
      the_params->maxiter, the_params->dereps, the_params->pw, the_params->ph, the_params->colormode,
      the_params->rmag, the_params->gmag, the_params->bmag,
      the_params->rscale, the_params->gscale, the_params->bscale,
      the_params->rshift, the_params->gshift, the_params->bshift);
   fprint_params(plotlistfp, spp4);

}

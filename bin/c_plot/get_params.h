#define GET_PARAMS_HEADER 1

#ifndef GET_STRUCTS
#include "structs.h"
#endif

void make_line_list(int *linelist, int argctot, char *args[]);
void init_plot_params(plot_params *ret_ptr, char *plotdir, char *outname,
      double llx, double lly, double urx, double ury, 
      int maxiter, double dereps, int pw, int ph, char *colormode,
      double rmag, double gmag, double bmag,
      double rscale, double gscale, double bscale,
      double rshift, double gshift, double bshift);

int fread_params(int *lines, char* plotlist_fname, plot_params **paramsout);
void print_params(plot_params *paramsout);
void fprint_params(char *filepath, plot_params *thisparams);
void bisect_params(plot_params *thisparams, char *outfilename, char *plotdir);

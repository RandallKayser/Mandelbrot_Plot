#define GET_PARAMS_HEADER 1
#ifndef GET_STRUCTS
#include "structs.h"
#endif

void make_line_list(int *linelist, int argctot, char *args[]);
plot_params* init_plot_params(char *plotdir, char *outname, double llx, double lly, double urx,
      double ury, int maxiter, double dereps, int pw, int ph, char *colormode,
      double rmag, double gmag, double bmag, double rscale, double gscale, double bscale,
      double rshift, double gshift, double bshift);
void fread_params(int *lines, plot_params **paramsout);
void print_params(plot_params *paramsout);


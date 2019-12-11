#define GET_ESCAPES_HEADER 1

#ifndef GET_PARAMS_HEADER
#include "./get_params.h"
#endif


void get_z(int i, int j, double *coords, plot_params *the_params);
int iterate_pix(int i, int j, plot_params *the_params);
int *get_escapes(plot_params *the_params);


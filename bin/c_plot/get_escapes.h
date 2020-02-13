#define GET_ESCAPES_HEADER 1

#ifndef GET_PARAMS_HEADER
#include "./get_params.h"
#endif

void simple_plot(char *rundir, int linenum);
void get_z(pix *p, plot_params *the_params);
void iterate_pix(pix *p, plot_params *the_params);
void get_escapes(pix *pixarray, plot_params *the_params);


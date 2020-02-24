#define ESC_TO_DATA_HEADER 1

#ifndef GET_STRUCTS
#include "./structs.h"
#endif

void normalizelogv( double *minandmax, pix *pixarray, plot_params *the_params); 
void get_color(int *out, pix *p, pix *pixarray, plot_params *the_params); 
void make_logv_array(double *logvarr, pix *pixarray, plot_params *the_params);
double l2_of_lap(double *logvarr, plot_params *the_params, char* stencil);

#define GET_ESCAPES_HEADER 1

#ifndef GET_PARAMS_HEADER
#include "./get_params.h"
#endif

struct pix_data {
   //pixel coords
   int i;
   int j;
   // z coords
   double cx;
   double cy;
   // escape iteration and modulus
   int n_esc;
   double escmod;
   double logv;
};

typedef struct pix_data pix;

void get_z(pix *p, plot_params *the_params);
void iterate_pix(pix *p, plot_params *the_params);
void *get_escapes(pix *pixarray, plot_params *the_params);


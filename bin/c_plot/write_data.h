#define GET_WRITE_DATA_HEADER 1

#ifndef GET_PARAMS_HEADER
#include "./get_params.h"
#endif

#ifndef GET_ESCAPES_HEADER
#include "./get_escapes.h"
#endif

void write_data(plot_params *the_params, pix *returnarray);
void write_logv(plot_params *the_params, pix *returnarray);

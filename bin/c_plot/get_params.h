#define GET_PARAMS_HEADER 1

struct param_struct {
   // NOTE: dat/plotname/plotlist format specifies parameters in same order as struct!!!
   int linenum;
   char plotdir[100];
   double llx;
   double lly;
   double urx;
   double ury;
   int maxiter;
   
   int pw;
   int ph;
   char colormode[20];
};
typedef struct param_struct plot_params;

void read_params(plot_params *paramsout);
void print_params(plot_params *paramsout);


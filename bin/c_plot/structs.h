#define GET_STRUCTS 1

struct run_struct {
   int linelist[512];
   int logv_out_flag;
};

struct plot_struct {
   // NOTE: params required for singular plot
   char plotdir[256];
   char outname[256];
   int linenum;
   double llx;
   double lly;
   double urx;
   double ury;
   int maxiter;
   double dereps;   
   int pw;
   int ph;
   char colormode[20];
   double rmag;
   double gmag;
   double bmag;
   double rscale;
   double gscale;
   double bscale;
   double rshift;
   double gshift;
   double bshift;
};

typedef struct plot_struct plot_params;
typedef struct run_struct run_params;



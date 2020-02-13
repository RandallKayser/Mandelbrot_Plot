#define GET_STRUCTS 1

struct run_struct {
   int linelist[512];
   int logv_out_flag;
};

struct plot_struct {
   // all the params required for a singular plot
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
typedef struct plot_struct plot_params;
typedef struct run_struct run_params;



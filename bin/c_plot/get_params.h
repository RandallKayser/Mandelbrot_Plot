struct plot_params {
   double llx;
   double lly;
   double urx;
   double ury;
   int pw;
   int ph;
};
typedef struct plot_params plot_params;
void read_params(char runfolder[256], int linenum, plot_params *paramsout);
void print_params(plot_params *paramsout);


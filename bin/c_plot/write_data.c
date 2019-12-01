#include <stdio.h>
extern void float_to_hex(float x) {
   unsigned char out;
   for(int t=0; t<256; t++) {
      out = (unsigned char) t;
      printf("char=%c t=%d \n", out, t);
   }
   float scratch = x;
   if(scratch < 0) {
      scratch = -scratch;
   }
}

void write_data(float LL, float UR) {
   
}

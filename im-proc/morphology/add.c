#include <stdlib.h>
#include <stdio.h>

#include "morphology.h"

void add(pnm ims1, pnm ims2, pnm imd) {

  int w = pnm_get_width(ims1);
  int h = pnm_get_height(ims1);

  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      for (int k = 0; k < 3; k++) {

        int res = pnm_get_component(ims1, j, i, k) + pnm_get_component(ims2, j, i, k);
        if (res > 255) res = 255;
        if (res < 0) res = 0;
        pnm_set_component(imd,j,i,k,res);
      }
    }
  }

}

void
usage(char* s)
{
  fprintf(stderr,"%s <ims-1> <ims-2> <imd>\n",s);
  exit(EXIT_FAILURE);
}

#define PARAM 3
int
main(int argc, char* argv[])
{
  if(argc != PARAM+1)
    usage(argv[0]);

  char* ims1_name = argv[1];
  char* ims2_name = argv[2];
  char* imd_name = argv[3];

  pnm ims1 = pnm_load(ims1_name);
  pnm ims2 = pnm_load(ims2_name);
  pnm imd = pnm_new(pnm_get_width(ims1),pnm_get_height(ims1), PnmRawPpm);

  add(ims1, ims2, imd);

  pnm_save(imd, PnmRawPpm, imd_name);
  pnm_free(imd);
  return EXIT_SUCCESS;
}

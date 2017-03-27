#include <stdlib.h>
#include <stdio.h>

#include "morphology.h"

void binarize(int min, int max, pnm ims, pnm imd) {

  int w = pnm_get_width(ims);
  int h = pnm_get_height(ims);
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      for (int k = 0; k < 3; k++) {

        int res = pnm_get_component(ims, j, i, k);
        if(res >= min && res <= max)
          pnm_set_component(imd, j, i, k, 255);
        else
          pnm_set_component(imd, j, i, k, 0);
      }
    }
  }

}

void
usage(char* s)
{
  fprintf(stderr,"%s <min> <max> <ims> <imd>\n",s);
  exit(EXIT_FAILURE);
}

#define PARAM 4
int
main(int argc, char* argv[])
{
  if(argc != PARAM+1)
    usage(argv[0]);

  int min = atoi(argv[1]);
  int max = atoi(argv[2]);
  char* ims_name = argv[3];
  char* imd_name = argv[4];

  pnm ims = pnm_load(ims_name);
  pnm imd = pnm_new(pnm_get_width(ims),pnm_get_height(ims), PnmRawPpm);

  binarize(min, max, ims, imd);

  pnm_save(imd, PnmRawPpm, imd_name);
  pnm_free(imd);
  return EXIT_SUCCESS;
}

#include <stdlib.h>
#include <stdio.h>

#include <bcl.h>

void
process(char* ims_name, char* imd_name){


  pnm ims = pnm_load(ims_name);
  int h = pnm_get_height(ims);
  int w = pnm_get_width(ims);
  pnm imd = pnm_new(w, h, PnmRawPpm);
  short mean;

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      // get the mean
      mean = pnm_get_component(ims, i, j, 0)+ pnm_get_component(ims, i, j, 1)+pnm_get_component(ims, i, j, 2);
      mean = mean/3;
      // set it to imd
      for (int k = 0; k < 3; k++) {
        pnm_set_component(imd, i, j, k, mean);
      }
    }
  }

  pnm_save(imd, PnmRawPpm, imd_name);
  pnm_free(imd);
}

void
usage (char *s){
  fprintf(stderr, "Usage: %s <ims> <imd>\n", s);
  exit(EXIT_FAILURE);
}

#define PARAM 2
int
main(int argc, char *argv[]){
  if (argc != PARAM+1) usage(argv[0]);
  char* ims_name = argv[1];
  char* imd_name = argv[2];
  process(ims_name, imd_name);
  return EXIT_SUCCESS;
}

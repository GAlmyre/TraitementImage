#include <stdlib.h>
#include <stdio.h>

#include <bcl.h>

void
process(short min, short max, char* ims_name, char* imd_name){

  short minImg = 0;
  short maxImg = pnm_maxval;
  float res;

  pnm ims = pnm_load(ims_name);
  int h = pnm_get_height(ims);
  int w = pnm_get_width(ims);
  pnm imd = pnm_new(w, h, PnmRawPpm);

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      for (int k = 0; k < 3; k++) {
        res = (((max-min)*1.0))/(((maxImg-minImg)*1.0))*pnm_get_component(ims, i, j, k)+((min*maxImg-max*minImg)/(maxImg-minImg));
        pnm_set_component(imd, i, j, k, res);
      }
    }
  }

  pnm_save(imd, PnmRawPpm, imd_name);
  pnm_free(imd);
}

void
usage (char *s){
  fprintf(stderr, "Usage: %s <min> <max> <ims> <imd>\n", s);
  exit(EXIT_FAILURE);
}

#define PARAM 4
int
main(int argc, char *argv[]){
  if (argc != PARAM+1) usage(argv[0]);
  short min = atoi(argv[1]);
  short max = atoi(argv[2]);
  char* ims_name = argv[3];
  char* imd_name = argv[4];
  process(min, max, ims_name, imd_name);
  return EXIT_SUCCESS;
}

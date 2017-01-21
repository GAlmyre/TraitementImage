#include <stdlib.h>
#include <stdio.h>

#include <bcl.h>

void
process(char* ims0_name, char* ims1_name, char* ims2_name, char* imd_name){

  pnm imr = pnm_load(ims0_name);
  pnm img = pnm_load(ims1_name);
  pnm imb = pnm_load(ims2_name);

  pnm imd = pnm_new(pnm_get_width(imr), pnm_get_height(imr), PnmRawPpm);

  pnm_set_channel(imd, pnm_get_channel(imr, NULL, 0), 0);
  pnm_set_channel(imd, pnm_get_channel(img, NULL, 1), 1);
  pnm_set_channel(imd, pnm_get_channel(imb, NULL, 2), 2);

  pnm_save(imd, PnmRawPpm, imd_name);
  pnm_free(imd);
}

void
usage (char *s){
  fprintf(stderr, "Usage: %s <ims0> <ims1> <ims2> <imd>\n", s);
  exit(EXIT_FAILURE);
}

#define PARAM 4
int
main(int argc, char *argv[]){
  if (argc != PARAM+1) usage(argv[0]);
  char* ims0_name = argv[1];
  char* ims1_name = argv[2];
  char* ims2_name = argv[3];
  char* imd_name = argv[4];
  process(ims0_name, ims1_name, ims2_name, imd_name);
  return EXIT_SUCCESS;
}

#include <stdlib.h>
#include <stdio.h>

#include "morphology.h"

void erosion(int shape, int hs, pnm ims, pnm imd) {
  process(shape, hs, ims, imd, lesser);
}

void
usage(char* s)
{
  fprintf(stderr,"%s <shape> <hs> <ims> <imd>\n",s);
  exit(EXIT_FAILURE);
}

#define PARAM 4
int
main(int argc, char* argv[])
{
  if(argc != PARAM+1)
    usage(argv[0]);

  int   shape    = atoi(argv[1]);
  int   hs       = atoi(argv[2]);
  char* ims_name = argv[3];
  char* imd_name = argv[4];

  pnm ims = pnm_load(ims_name);
  pnm imd = pnm_new(pnm_get_width(ims),pnm_get_height(ims), PnmRawPpm);

  erosion(shape, hs, ims, imd);

  pnm_save(imd, PnmRawPpm, imd_name);
  pnm_free(imd);
  return EXIT_SUCCESS;
}

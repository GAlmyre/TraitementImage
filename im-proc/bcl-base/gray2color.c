/**
 * @file test1.c
 * @author Vinh-Thong Ta <ta@labri.fr>
 * @brief ???
 */

#include <stdlib.h>
#include <stdio.h>

#include <bcl.h>

void
process(char* ims0_name, char* ims1_name, char* ims2_name, char* imd_name){

  pnm ims = pnm_load(ims_name);
  pnm imd = pnm_new(pnm_get_width(ims), pnm_get_height(ims), PnmRawPpm);

  unsigned short *chan = pnm_get_channel(ims, NULL, num);

  pnm_set_channel(imd, chan, 0);
  pnm_set_channel(imd, chan, 1);
  pnm_set_channel(imd, chan, 2);

  pnm_save(imd, PnmRawPpm, imd_name);
  pnm_free(imd);
}

void
usage (char *s){
  fprintf(stderr, "Usage: %s <ims0> <ims1> <ims2> <imd>\n", s);
  exit(EXIT_FAILURE);
}

#define PARAM 3
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

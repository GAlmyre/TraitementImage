/**
 * @file test1.c
 * @author Vinh-Thong Ta <ta@labri.fr>
 * @brief ???
 */

#include <stdlib.h>
#include <stdio.h>

#include <bcl.h>

void
process(int i, int j, int rows, int cols, char* ims_name, char* imd_name){

  pnm imd = pnm_new(cols, rows, PnmRawPpm);

  pnm ims = pnm_load(ims_name);

  unsigned short *src = pnm_get_image(ims);
  unsigned short *dest = pnm_get_image(imd);

  for (int i_it = i; i_it < rows+i; i_it++) {
    for (int j_it = j; j_it < cols+j; j_it++) {
      for (int k = 0; k < 3; k++) {
        *dest++ = *(src + pnm_offset(ims, i_it, j_it) +k);
      }
    }
  }

  pnm_save(imd, PnmRawPpm, imd_name);
  pnm_free(imd);
}

void
usage (char *s){
  fprintf(stderr, "Usage: %s <i> <j> <rows> <cols> <ims> <imd>\n", s);
  exit(EXIT_FAILURE);
}

#define PARAM 6
int
main(int argc, char *argv[]){
  if (argc != PARAM+1) usage(argv[0]);
  int i = atoi(argv[1]);
  int j = atoi(argv[2]);
  int rows = atoi(argv[3]);
  int cols = atoi(argv[4]);
  char* ims_name = argv[5];
  char* imd_name = argv[6];
  process(i, j, rows, cols, ims_name, imd_name);
  return EXIT_SUCCESS;
}

#include <float.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

#include <bcl.h>
#include "fft.h"

char *gnu_basename(char *path)
{
    char *base = strrchr(path, '/');
    return base ? base+1 : path;
}

void zoom(int factor, pnm ims, char* imd_name) {

  int h = pnm_get_height(ims)*factor;
  int w = pnm_get_width(ims)*factor;

  pnm imd = pnm_new(w, h, PnmRawPpm);

  for (int i = 0; i < h/factor; i++) {
    for (int j = 0; j < w/factor; j++) {

      int p = pnm_get_component(ims, i, j, 0);

      for (int m = 0; m < factor; m++) {
        for (int n = 0; n < factor; n++) {
          for (int k = 0; k < 3; k++) {
            pnm_set_component(imd, i*factor+m, j*factor+n,k, p);
          }
        }
      }
    }
  }

  pnm_save(imd, PnmRawPpm, imd_name);
  pnm_free(imd);
}

void
usage (char *s)
{
  fprintf(stderr, "Usage: %s <factor> <ims> <imd>\n", s);
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
  if (argc != 4)
    usage(argv[0]);

  int factor = atoi(argv[1]);
  pnm ims = pnm_load(argv[2]);
  char* imd = gnu_basename(argv[3]);

  zoom(factor, ims, imd);

  return EXIT_SUCCESS;
}

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

  int w = pnm_get_width(ims);
  int h = pnm_get_height(ims);

  unsigned short* grayImg = pnm_get_channel(ims, NULL, 0);
  fftw_complex* c_img = forward(h, w, grayImg);

  fftw_complex* c_res = malloc(h*factor*w*factor*sizeof(fftw_complex));

  for (int i = 0; i < h*factor; i++) {
    for (int j = 0; j < w*factor; j++) {
      c_res[i*h*factor+j] = 0;
    }
  }
  int k = 0;
  for (int i = (h*factor)/2-h/2; i < (h*factor)/2+h/2; i++) {
    for (int j = (w*factor)/2-h/2; j < (w*factor)/2+w/2; j++) {
      c_res[i*h*factor+j] = c_img[k]*factor*factor;
      k++;
    }
  }

  unsigned short* res_img = backward(h*factor, w*factor, c_res);

  pnm imd = pnm_new(w*factor, h*factor, PnmRawPpm);

  pnm_set_channel(imd, res_img, 0);
  pnm_set_channel(imd, res_img, 1);
  pnm_set_channel(imd, res_img, 2);

  pnm_save(imd, PnmRawPpm, imd_name);

  free(grayImg);
  free(c_img);
  free(c_res);
  free(res_img);
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

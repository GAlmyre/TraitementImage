#include <stdlib.h>
#include <stdio.h>


#include <bcl.h>

static void
process(int n, char* ims_name, char* imd_name)
{
  float t = 0.25;
  pnm ims = pnm_load(ims_name);
  int w = pnm_get_width(ims);
  int h = pnm_get_height(ims);
  pnm imd = pnm_new(w, h, PnmRawPpm);

  float* diff = malloc(w*h*sizeof(float));
  float* tmpImg = malloc(w*h*sizeof(float));

  for (int i = 0; i < w*h; i++) {
    tmpImg[i] = pnm_get_component(ims,i%w,i/w,0);
  }

  for (int i = 1; i < n; i++) {

    for (int row = 0; row < h; row++) {
      for (int col = 0; col < w; col++) {

        float laplacien;
        unsigned short ui_pos, ui_neg, uj_pos, uj_neg;
        unsigned short uij = tmpImg[row*w+col];

        // calcul du laplacien
        if (row == 0)
          ui_neg = uij;
        else
          ui_neg = tmpImg[row*w+col-w];
        if (col == 0)
          uj_neg = uij;
        else
          uj_neg = tmpImg[row*w+col-1];
        if (col == w-1)
          uj_pos = uij;
        else
          uj_pos = tmpImg[row*w+col+1];
        if (row == h-1)
          ui_pos = uij;
        else
          ui_pos = tmpImg[row*w+col+w];

        laplacien = ui_pos+ui_neg+uj_pos+uj_neg-4*uij;
        diff[row*w+col] = laplacien;
      }
    }

    for (int row = 0; row < h; row++) {
      for (int col = 0; col < w; col++) {
        tmpImg[row*w+col]+= t*diff[row*w+col];
      }
    }
  }

  for (int row = 0; row < h; row++) {
    for (int col = 0; col < w; col++) {

      if (tmpImg[row*w+col] > 255) {
        tmpImg[row*w+col] = 255;
      }

      if (tmpImg[row*w+col] < 0) {
        tmpImg[row*w+col] = 0;
      }

      pnm_set_component(imd, col, row, 0, tmpImg[row*w+col]);
      pnm_set_component(imd, col, row, 1, tmpImg[row*w+col]);
      pnm_set_component(imd, col, row, 2, tmpImg[row*w+col]);
    }
  }

  pnm_save(imd, PnmRawPpm, imd_name);
}

void usage (char *s){

  fprintf(stderr, "Usage: %s <n> <ims> <imd>\n", s);
  exit(EXIT_FAILURE);
}

#define PARAM 3
int main(int argc, char *argv[]){
  if (argc != PARAM+1)
    usage(argv[0]);

  int   idx     = 1;
  int   n       = atoi(argv[idx++]);
  char* ims     = argv[idx++];
  char* imd     = argv[idx++];

  process(n, ims, imd);

  return EXIT_SUCCESS;
}

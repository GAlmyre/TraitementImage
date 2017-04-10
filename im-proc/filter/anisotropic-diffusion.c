#include <stdlib.h>
#include <stdio.h>


#include <bcl.h>

float function(int f, float s, int lambda) {
  float ret;

  switch (f) {
    case 0:
      ret = 1;
    break;
    case 1:
      ret = 1./(1+(s/lambda)*(s/lambda));
    break;
    case 2:
      ret = exp(-(s/lambda)*(s/lambda));
    break;
  }

  return ret;
}

float norm(float d1, float d2) {

  return sqrt((d1*d1)+(d2*d2));
}

void gradient(float** grad, float* img, int w, int h) {
  float d1, d2;

  for (int row = 0; row < h; row++) {
    for (int col = 0; col < w; col++) {

      if (row == h-1)
        d1 = 0;
      else
        d1 = img[row*w+col+1]-img[row*w+col];

      if (col == w-1)
        d2 = 0;
      else
        d2 = img[row*w+col+w]-img[row*w+col];

      grad[row*w+col][0] = d1;
      grad[row*w+col][1] = d2;
    }
  }
}

float* divergeance(float** tab, int w, int h) {

  float* res = malloc(w*h*sizeof(float));
  float d1, d2;
  for (int row = 0; row < h; row++) {
    for (int col = 0; col < w; col++) {
      if (row == h-1)
        d1 = 0;
      else
        d1 = tab[row*w+col+1][0]-tab[row*w+col][1];

      if (col == w-1)
        d2 = 0;
      else
        d2 = tab[row*w+col+w][0]-tab[row*w+col][1];

      res[row*w+col] = d1-d2;
    }
  }
  return res;
}

static void
process(int n, int lambda, int function, char* ims_name, char* imd_name)
{
  float t = 0.25;
  pnm ims = pnm_load(ims_name);
  int w = pnm_get_width(ims);
  int h = pnm_get_height(ims);
  pnm imd = pnm_new(w, h, PnmRawPpm);

  float** gradient = malloc(w*h*sizeof(float*));
  float* tmpImg = malloc(w*h*sizeof(float));

  for (int i = 0; i < w*h; i++) {
    tmpImg[i] = pnm_get_component(ims,i%w,i/w,0);

    gradient[i] = malloc(2*sizeof(float));
  }



  for (int row = 0; row < h; row++) {
    for (int col = 0; col < w; col++) {

      pnm_set_component(imd, col, row, 0, tmpImg[row*w+col]);
      pnm_set_component(imd, col, row, 1, tmpImg[row*w+col]);
      pnm_set_component(imd, col, row, 2, tmpImg[row*w+col]);
    }
  }

  pnm_save(imd, PnmRawPpm, imd_name);
}

void usage (char *s){

  fprintf(stderr, "Usage: %s <n> <lambda> <function> <ims> <imd>\n", s);
  exit(EXIT_FAILURE);
}

#define PARAM 3
int main(int argc, char *argv[]){
  if (argc != PARAM+1)
    usage(argv[0]);

  int   idx     = 1;
  int   n       = atoi(argv[idx++]);
  int   lambda  = atoi(argv[idx++]);
  int   function= atoi(argv[idx++]);
  char* ims     = argv[idx++];
  char* imd     = argv[idx++];

  process(n, lambda, function, ims, imd);

  return EXIT_SUCCESS;
}

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <bcl.h>

#define N 256
#define THRESHOLD 0.1

int min(int a, int b) {
  if (a < b) {
    return a;
  }
  return b;
}

int max(int a, int b) {
  if (a > b) {
    return a;
  }
  return b;
}

float Gauss(int i, int s) {
  return exp((float)(-(i*i))/(float)(2*s*s));
}

void fillTables(float* lookUpTableGs, float* lookUpTableGg, int sigma_s, int sigma_g) {

  for (int i = 0; i < N; i++) {
    lookUpTableGs[i] = Gauss(i,sigma_s);
    lookUpTableGg[i] = Gauss(i,sigma_g);
  }
}

int manhattan(int pRow, int pCol, int qRow, int qCol) {

  return abs(pRow-pCol)+abs(qRow-qCol);
}

int neighborhood(int s) {

  int res = 0;
  float gauss = Gauss(res, s);

  while (gauss > THRESHOLD) {
    res++;
    gauss = Gauss(res, s);
  }
  return res;
}

static void
process(int sigma_s, int sigma_g, char* ims_name, char* imd_name)
{
  pnm ims = pnm_load(ims_name);
  int w = pnm_get_width(ims);
  int h = pnm_get_height(ims);
  pnm imd = pnm_new(w, h, PnmRawPpm);

  float* lookUpTableGg = malloc(N*sizeof(float));
  float* lookUpTableGs = malloc(N*sizeof(float));
  unsigned short* tmpImg = malloc(w*h*sizeof(unsigned short));

  int hs = neighborhood(sigma_s);
  fillTables(lookUpTableGs, lookUpTableGg, sigma_s, sigma_g);

  for (int row = 0; row < h; row++) {
    for (int col = 0; col < w; col++) {
      unsigned short currentPixel = pnm_get_component(ims, row, col, 0);
      float sum_num = 0;
      float sum_den = 0;

      for (int row_win = -1*min(row,hs); row_win < min(h-row, hs+1); row_win++) {
        for (int col_win = -1*min(col,hs); col_win < min(w-col, hs+1); col_win++) {

          unsigned short tmp = pnm_get_component(ims,row_win+row,col_win+col,0);
          if (manhattan(row, col, row_win+row, col_win+col) < hs) {
            sum_num += lookUpTableGs[manhattan(row, col, row_win+row, col_win+col)]*lookUpTableGg[abs(currentPixel-tmp)]*tmp;
            sum_den += lookUpTableGs[manhattan(row, col, row_win+row, col_win+col)]*lookUpTableGg[abs(currentPixel-tmp)];
          }
        }
      }
      tmpImg[row*w+col] = sum_num/sum_den;
      printf("%f %f\n",sum_num,sum_den );
    }
  }

  for (int row = 0; row < h; row++) {
    for (int col = 0; col < w; col++) {

      if (tmpImg[row*w+col] > 255) {
        tmpImg[row*w+col] = 255;
      }

      pnm_set_component(imd, col, row, 0, tmpImg[row*w+col]);
      pnm_set_component(imd, col, row, 1, tmpImg[row*w+col]);
      pnm_set_component(imd, col, row, 2, tmpImg[row*w+col]);
    }
  }

  pnm_save(imd, PnmRawPpm, imd_name);
}

void usage (char *s){

  fprintf(stderr, "Usage: %s <sigma_s> <sigma_g> <ims> <imd>\n", s);
  exit(EXIT_FAILURE);
}

#define PARAM 4
int main(int argc, char *argv[]){
  if (argc != PARAM+1)
    usage(argv[0]);

  int   idx     = 1;
  int   sigma_s       = atoi(argv[idx++]);
  int   sigma_g       = atoi(argv[idx++]);
  char* ims     = argv[idx++];
  char* imd     = argv[idx++];

  process(sigma_s, sigma_g, ims, imd);

  return EXIT_SUCCESS;
}

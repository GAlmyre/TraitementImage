#include <float.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

#include <bcl.h>
#include "fft.h"

typedef double (*filter_ptr)(float);

char *gnu_basename(char *path)
{
    char *base = strrchr(path, '/');
    return base ? base+1 : path;
}

double box(float x){
  return (x>=(-0.5) && x<=0.5)? 1 : 0;
}

double tent(float x){
  return (x>=-1 && x<=1)? 1-fabs(x) : 0;
}

double bell(float x){
   if (fabs(x) <= 0.5) {
     return (-(x*x)+(3./4));
   }
   else if (fabs(x)>0.5 && fabs(x)<=(3./2)) {
     return 0.5*((fabs(x)-(3./2))*(fabs(x)-(3./2)));
   }
   else
    return 0;
}

double mitch(float x){
  if (x>=-1 && x<=1) {
    return (7./6)*(fabs(x)*fabs(x)*fabs(x))-2*(x*x)+8./9;
  }
  else if ((x>=-2 && x<=-1) || (x>=1 && x<=2)) {
    return (-7./18)*(fabs(x)*fabs(x)*fabs(x))+2*(x*x)-(10./3)*fabs(x)+16./9;
  }
  else
    return 0;
}

void filter_image(int factor, unsigned short* ims, unsigned short* imd, float WF, int w, int h, filter_ptr filter) {

  float left, right, j, S;
  for (int i = 0; i < h; i++) {
    for (int jp = 0; jp < w*factor; jp++) {
      j = 1.*jp/factor;
      left = j-WF;
      right = j+WF;
      S = 0;
      for (int k = floor(left); k <= ceil(right); k++) {
        S += ims[i*w+k]*(*filter)(k-j);
      }
      imd[i*w*factor+jp] = S;
    }
  }
}

void flip(unsigned short* ims, int w, int h) {

  unsigned short* flipped = malloc(sizeof(unsigned short)*w*h);
  for (int i = 0; i < w*h; i++) {
    flipped[i] = ims[i];
  }

  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      ims[j*h+i] = flipped[i*w+j];
    }
  }

  free(flipped);
}

void zoom(int factor, filter_ptr filter, pnm ims, char* imd_name, float WF) {

  int w = pnm_get_width(ims);
  int h = pnm_get_height(ims);

  unsigned short* grayImg = pnm_get_channel(ims, NULL, 0);
  pnm imd = pnm_new(w*factor, h*factor, PnmRawPpm);
  unsigned short* imd_short_w = malloc(sizeof(unsigned short)*w*factor*h);

  filter_image(factor, grayImg, imd_short_w, WF, w, h, filter);
  flip(imd_short_w, w*factor, h);
  unsigned short* imd_short_wh = malloc(sizeof(unsigned short)*(w*factor)*(h*factor));
  filter_image(factor, imd_short_w, imd_short_wh, WF, h, w*factor, filter);
  flip(imd_short_wh, h*factor, w*factor);

  pnm_set_channel(imd, imd_short_wh, 0);
  pnm_set_channel(imd, imd_short_wh, 1);
  pnm_set_channel(imd, imd_short_wh, 2);

  pnm_save(imd, PnmRawPpm, imd_name);

  free(imd_short_w);
  free(imd_short_wh);
  free(grayImg);
  pnm_free(imd);
}

filter_ptr get_filter(char* arg, float *WF) {
  if (strcmp(arg, "box") == 0) {
    *WF = 0.5;
    return &box;
  }
  else if (strcmp(arg, "tent") == 0) {
    *WF = 1;
    return &tent;
  }
  else if (strcmp(arg, "bell") == 0) {
    *WF = 1;
    return &bell;
  }
  else if (strcmp(arg, "mitch") == 0) {
    *WF = 2;
    return &mitch;
  }
  else
    return NULL;
}

void
usage (char *s)
{
  fprintf(stderr, "Usage: %s <factor> <filter-name> <ims> <imd>\n", s);
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
  if (argc != 5)
    usage(argv[0]);

  int factor = atoi(argv[1]);
  char* filter_name = argv[2];
  pnm ims = pnm_load(argv[3]);
  char* imd = gnu_basename(argv[4]);
  float WF = 0;
  filter_ptr ptr = get_filter(filter_name, &WF);


  zoom(factor, *ptr, ims, imd, WF);

  return EXIT_SUCCESS;
}

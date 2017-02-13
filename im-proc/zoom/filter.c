#include <float.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

#include <bcl.h>
#include "fft.h"

typedef double (*filter_ptr)(double);

char *gnu_basename(char *path)
{
    char *base = strrchr(path, '/');
    return base ? base+1 : path;
}

double box(double x){
  return (x>=(-0.5) && x<=0.5)? 1 : 0;
}

double tent(double x){
  return (x>=-1 && x<=1)? 1-abs(x) : 0;
}

double bell(double x){
   if (abs(x) <= 0.5) {
     return (-x*x+(3/4));
   }
   else if (abs(x)>=0.5 && abs(x)<=(3/2)) {
     return 0.5*(abs(x)-3/2)*(abs(x)-3/2);
   }
   else
    return 0;
}

double mitch(double x){
  if (x>=-1 && x<=1) {
    return (7/6)*(abs(x)*abs(x)*abs(x))-2*(x*x)+8/9;
  }
  else if ((x>=-2 && x<=-1) || (x>=1 && x<=2)) {
    return (-7/6)*(abs(x)*abs(x)*abs(x))+2*(x*x)-(10/3)*abs(x)+16/9;
  }
  else
    return 0;
}

void zoom(int factor, filter_ptr filter, pnm ims, char* imd_name) {

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

void get_filter(char* arg, filter_ptr ptr) {
  if (strcmp(arg, "box") == 0) {
    ptr = &box;
  }
  else if (strcmp(arg, "tent") == 0) {
    ptr = &tent;
  }
  else if (strcmp(arg, "bell") == 0) {
    ptr = &bell;
  }
  else if (strcmp(arg, "mitch") == 0) {
    ptr = &mitch;
  }
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

  filter_ptr ptr = NULL;
  get_filter(filter_name, ptr);

  zoom(factor, ims, imd);

  return EXIT_SUCCESS;
}

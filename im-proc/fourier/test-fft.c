/**
 * @file test-fft.c
 * @brief test the behaviors of functions in fft module
 *
 */
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "fft.h"
#define M_PI           3.14159265358979323846
/**
 * @brief test the forward and backward functions
 * @param pnm ims, the source image
 * @param char* name, the image file name
 */
static void
test_for_backward(pnm ims, char* name)
{
  fprintf(stderr, "test_for_backward: ");

  int w = pnm_get_width(ims);
  int h = pnm_get_height(ims);
  unsigned short* grayImg = pnm_get_channel(ims, NULL, 0);
  fftw_complex* c_img = forward(h, w, grayImg);
  unsigned short* res_img = backward(h, w, c_img);

  pnm res = pnm_new(w, h, PnmRawPpm);
  pnm_set_channel(res, res_img, 0);
  pnm_set_channel(res, res_img, 1);
  pnm_set_channel(res, res_img, 2);

  char* new_name = malloc((strlen(name)+3)*sizeof(char));
  sprintf(new_name, "FB-%s", name);
  pnm_save(res, PnmRawPpm, new_name);

  free(res);
  free(c_img);
  free(grayImg);
  free(new_name);

  fprintf(stderr, "OK\n");
}


/**
 * @brief test image reconstruction from of amplitude and phase spectrum
 * @param pnm ims: the source image
 * @param char *name: the image file name
 */
static void
test_reconstruction(pnm ims, char* name)
{
  fprintf(stderr, "test_reconstruction: ");
  int w = pnm_get_width(ims);
  int h = pnm_get_height(ims);
  unsigned short* grayImg = pnm_get_channel(ims, NULL, 0);
  fftw_complex* c_img = forward(h, w, grayImg);

  float* as = malloc(h*w*sizeof(float));
  float* ps = malloc(h*w*sizeof(float));

  freq2spectra(h, w, c_img, as, ps);

  unsigned short* res_img = backward(h, w, c_img);

  spectra2freq(h, w, as, ps, c_img);

  pnm res = pnm_new(w, h, PnmRawPpm);
  pnm_set_channel(res, res_img, 0);
  pnm_set_channel(res, res_img, 1);
  pnm_set_channel(res, res_img, 2);

  char* new_name = malloc((strlen(name)+8)*sizeof(char));
  sprintf(new_name, "FB-ASPS-%s", name);
  pnm_save(res, PnmRawPpm, new_name);

  free(res);
  free(c_img);
  free(grayImg);
  free(new_name);
  free(as);
  free(ps);

  fprintf(stderr, "OK\n");
}


/**
 * @brief test construction of amplitude and phase images in ppm files
 * @param pnm ims, the source image
 * @param char* name, the image file name
 */
static void
test_display(pnm ims, char* name)
{
  fprintf(stderr, "test_display: ");
  int w = pnm_get_width(ims);
  int h = pnm_get_height(ims);
  pnm res_as = pnm_new(w, h, PnmRawPpm);
  pnm res_ps = pnm_new(w, h, PnmRawPpm);

  unsigned short* grayImg = pnm_get_channel(ims, NULL, 0);
  fftw_complex* c_img = forward(h, w, grayImg);

  float* as_float = malloc(h*w*sizeof(float));
  float* ps_float = malloc(h*w*sizeof(float));

  unsigned short* as_short = malloc(h*w*sizeof(unsigned short));
  unsigned short* ps_short = malloc(h*w*sizeof(unsigned short));

  freq2spectra(h, w, c_img, as_float, ps_float);

  // find a_max & p_max
  float a_max = 0;
  float p_max = 0;
  for (int i = 0; i < h*w; i++) {
    if (as_float[i] > a_max) {
      a_max = as_float[i];
    }
    if (ps_float[i] > p_max) {
      p_max = ps_float[i];
    }
  }
  // shrinks the values between 0 and 255
  for (int i = 0; i < h*w; i++) {
    as_short[i] = (pow(((as_float[i])/(a_max)),0.15)*255);
    if (ps_float[i] < 0 ) {
      ps_short[i] = 0;
    }
    else
      ps_short[i] = ((ps_float[i])/(p_max))*255;

  }

  pnm_set_channel(res_as, as_short, 0);
  pnm_set_channel(res_as, as_short, 1);
  pnm_set_channel(res_as, as_short, 2);

  char* new_name = malloc((strlen(name)+3)*sizeof(char));
  sprintf(new_name, "AS-%s", name);
  pnm_save(res_as, PnmRawPpm, new_name);

  pnm_set_channel(res_ps, ps_short, 0);
  pnm_set_channel(res_ps, ps_short, 1);
  pnm_set_channel(res_ps, ps_short, 2);

  sprintf(new_name, "PS-%s", name);
  pnm_save(res_ps, PnmRawPpm, new_name);

  free(c_img);
  free(as_float);
  free(as_short);
  free(ps_float);
  free(ps_short);
  free(new_name);
  free(res_as);
  free(res_ps);

  fprintf(stderr, "OK\n");
}

/**
 * @brief test the modification of amplitude and phase spectrum and
 *        construct output images
 * @param pnm ims, the source image
 * @param char* name, the image file name
 */
static void
test_modification(pnm ims, char* name)
{
  fprintf(stderr, "test_modification: ");

  int h = pnm_get_height(ims);
  int w = pnm_get_width(ims);
  pnm res = pnm_new(w, h, PnmRawPpm);
  unsigned short* grayImg = pnm_get_channel(ims, NULL, 0);
  fftw_complex* c_img = forward(h, w, grayImg);
  float* as = malloc(h*w*sizeof(double));
  float* ps = malloc(h*w*sizeof(double));

  freq2spectra(h, w, c_img, as, ps);

  float a_max = 0;
  for (int i = 0; i < h*w; i++) {
    if (as[i] > a_max) {
      a_max = as[i];
    }
  }

  for (int i = 0; i < h*w; i++) {
    for (int j = 0; j < w; j++) {
      as[i*w+j]+= (0.25*a_max)*sin(2*M_PI*i*8);
      //as[i*w+j]*= (0.25*a_max)*sin(2*M_PI*j*8);
    }
  }

  spectra2freq(h, w, as, ps, c_img);


  unsigned short* res_img = backward(h, w, c_img);

  pnm_set_channel(res, res_img, 0);
  pnm_set_channel(res, res_img, 1);
  pnm_set_channel(res, res_img, 2);

  char* new_name = malloc((strlen(name)+4)*sizeof(char));
  sprintf(new_name, "FREQ-%s", name);
  pnm_save(res, PnmRawPpm, new_name);

  free(c_img);
  free(new_name);
  free(as);
  free(ps);
  free(res);

  fprintf(stderr, "OK\n");
}


static void
run(pnm ims, char* name)
{
  test_for_backward(ims, name);
  test_reconstruction(ims, name);
  test_display(ims, name);
  test_modification(ims, name);
}


void
usage (char *s)
{
  fprintf(stderr, "Usage: %s <ims> \n", s);
  exit(EXIT_FAILURE);
}

int
main(int argc, char *argv[])
{
  if (argc != 2)
    usage(argv[0]);
  pnm ims = pnm_load(argv[1]);
  run(ims, argv[1]);

  return EXIT_SUCCESS;
}

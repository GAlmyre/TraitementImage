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
#include <libgen.h>

#include "fft.h"
#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif


float max_tab(float* tab, int size) {
  int res = 0;
  for (int i = 0; i < size; i++) {
    if (tab[i] > res) {
      res = tab[i];
    }
  }
  return res;
}

char *gnu_basename(char *path)
{
    char *base = strrchr(path, '/');
    return base ? base+1 : path;
}

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
  pnm res = pnm_new(w, h, PnmRawPpm);

  for (int color = 0; color < 3; color++) {

    unsigned short* grayImg = pnm_get_channel(ims, NULL, color);
    fftw_complex* c_img = forward(h, w, grayImg);
    unsigned short* res_img = backward(h, w, c_img);

    pnm_set_channel(res, res_img, color);
    free(res_img);
    free(c_img);
    free(grayImg);
  }

  char* new_name = malloc((strlen(gnu_basename(name))+3)*sizeof(char));
  sprintf(new_name, "FB-%s", gnu_basename(name));
  pnm_save(res, PnmRawPpm, new_name);

  free(res);
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
  pnm res = pnm_new(w, h, PnmRawPpm);

  for (int color = 0; color < 3; color++) {
    unsigned short* grayImg = pnm_get_channel(ims, NULL, color);

    fftw_complex* c_img = forward(h, w, grayImg);

    float* as = malloc(h*w*sizeof(float));
    float* ps = malloc(h*w*sizeof(float));

    freq2spectra(h, w, c_img, as, ps);

    unsigned short* res_img = backward(h, w, c_img);

    spectra2freq(h, w, as, ps, c_img);

    pnm_set_channel(res, res_img, color);

    free(grayImg);
    free(as);
    free(ps);
    free(c_img);
  }

  char* new_name = malloc((strlen(gnu_basename(name))+8)*sizeof(char));
  sprintf(new_name, "FB-ASPS-%s", gnu_basename(name));
  pnm_save(res, PnmRawPpm, new_name);

  free(res);
  free(new_name);
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

  for (int color = 0; color < 3; color++) {
    pnm res_as = pnm_new(w, h, PnmRawPpm);
    pnm res_ps = pnm_new(w, h, PnmRawPpm);

    unsigned short* grayImg = pnm_get_channel(ims, NULL, color);
    fftw_complex* c_img = forward(h, w, grayImg);

    float* as_float = malloc(h*w*sizeof(float));
    float* ps_float = malloc(h*w*sizeof(float));

    unsigned short* as_short = malloc(h*w*sizeof(unsigned short));
    unsigned short* ps_short = malloc(h*w*sizeof(unsigned short));

    freq2spectra(h, w, c_img, as_float, ps_float);

    // find a_max & p_max
    float a_max = max_tab(as_float, h*w);
    float p_max = max_tab(ps_float, h*w);

    // shrinks the values between 0 and 255
    for (int i = 0; i < h*w; i++) {
      as_short[i] = (pow(((as_float[i])/(a_max)),0.15)*255);

      ps_short[i] = ((ps_float[i])/(p_max))*255;
    }

    pnm_set_channel(res_as, as_short, 0);
    pnm_set_channel(res_as, as_short, 1);
    pnm_set_channel(res_as, as_short, 2);

    char* new_name = malloc((strlen(name)+4)*sizeof(char));
    sprintf(new_name, "AS%d-%s", color, gnu_basename(name));
    pnm_save(res_as, PnmRawPpm, new_name);

    pnm_set_channel(res_ps, ps_short, 0);
    pnm_set_channel(res_ps, ps_short, 1);
    pnm_set_channel(res_ps, ps_short, 2);

    sprintf(new_name, "PS%d-%s", color, gnu_basename(name));
    pnm_save(res_ps, PnmRawPpm, new_name);

    free(c_img);
    free(as_float);
    free(as_short);
    free(ps_float);
    free(ps_short);
    free(new_name);
    pnm_free(res_as);
    pnm_free(res_ps);
  }

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

  for (int color = 0; color < 3; color++) {
    pnm res_as = pnm_new(w, h, PnmRawPpm);

    float* as = malloc(h*w*sizeof(float));
    float* ps = malloc(h*w*sizeof(float));
    unsigned short* as_short = malloc(h*w*sizeof(short));

    unsigned short* grayImg = pnm_get_channel(ims, NULL, color);
    fftw_complex* c_img = forward(h, w, grayImg);

    freq2spectra(h, w, c_img, as, ps);

    float a_max = max_tab(as, h*w);

    int center = w*(h/2)+w/2;

    // add the frequencies
    as[center+8] = 0.25*a_max;
    as[center-8] = 0.25*a_max;
    as[center+8*w] = 0.25*a_max;
    as[center-8*w] = 0.25*a_max;

    for (int i = 0; i < h*w; i++) {
      as_short[i] = (pow(((as[i])/(a_max)),0.15)*255);
    }

    pnm_set_channel(res_as, as_short, 0);
    pnm_set_channel(res_as, as_short, 1);
    pnm_set_channel(res_as, as_short, 2);

    spectra2freq(h, w, as, ps, c_img);

    unsigned short* res_img = backward(h, w, c_img);

    pnm_set_channel(res, res_img, color);

    char* new_as_name = malloc((strlen(gnu_basename(name))+4)*sizeof(char));
    sprintf(new_as_name, "FAS%d-%s", color, gnu_basename(name));
    pnm_save(res_as, PnmRawPpm, new_as_name);

    free(c_img);
    free(new_as_name);
    free(as);
    free(as_short);
    free(ps);
    pnm_free(res_as);
  }

  char* new_name = malloc((strlen(gnu_basename(name))+4)*sizeof(char));
  sprintf(new_name, "FREQ-%s", gnu_basename(name));
  pnm_save(res, PnmRawPpm, new_name);

  free(new_name);
  pnm_free(res);
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

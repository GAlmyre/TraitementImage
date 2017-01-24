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
  (void)ims;
  (void)name;

  
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
  (void)ims;
  (void)name;
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

#include <float.h>
#include <stdlib.h>
#include <math.h>

#include "fft.h"

fftw_complex
*forward(int rows, int cols, unsigned short* g_img)
{
  fftw_complex* c_img = malloc(rows*cols*sizeof(fftw_complex));

  // Build a complex image
  for (int i = 0; i < rows*cols; i++) {
    c_img[i] = 3*g_img[i];
  }

  // apply fftw from c_img to res
  fftw_complex* res = malloc(rows*cols*sizeof(fftw_complex));
  fftw_plan plan = fftw_plan_dft_2d(rows, cols, c_img, res, FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(plan);

  // free memory
  fftw_destroy_plan(plan);
  free(c_img);

  return res;
}


unsigned short
*backward(int rows, int cols, fftw_complex* freq_repr)
{
  // fourier backward
  fftw_complex* res = malloc(rows*cols*sizeof(fftw_complex));
  fftw_plan plan = fftw_plan_dft_2d(rows, cols, freq_repr, res, FFTW_BACKWARD, FFTW_ESTIMATE);
  fftw_execute(plan);

  //free memory
  fftw_destroy_plan(plan);
  return NULL;
}

void
freq2spectra(int rows, int cols, fftw_complex* freq_repr, float* as, float* ps)
{
  (void)rows;
  (void)cols;
  (void)freq_repr;
  (void)as;
  (void)ps;
}


void
spectra2freq(int rows, int cols, float* as, float* ps, fftw_complex* freq_repr)
{
  (void)rows;
  (void)cols;
  (void)freq_repr;
  (void)as;
  (void)ps;
}

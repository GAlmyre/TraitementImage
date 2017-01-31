#include <float.h>
#include <stdlib.h>
#include <math.h>

#include "fft.h"

void center(fftw_complex* tab, int h, int w) {

  for (int i = 0; i < h; i++)
    for (int j = 0; j < w; j++) {
      if ((j+i)%2 != 0) {
        tab[i*h+j]=tab[i*h+j]*(-1);
      }
    }
}

fftw_complex
*forward(int rows, int cols, unsigned short* g_img)
{
  fftw_complex* c_img = malloc(rows*cols*sizeof(fftw_complex));

  // Build a complex image
  for (int i = 0; i < rows*cols; i++) {
    c_img[i] = g_img[i];
  }

  center(c_img, rows, cols);

  // apply fftw from c_img to res
  fftw_complex* res = malloc(rows*cols*sizeof(fftw_complex));
  fftw_plan plan = fftw_plan_dft_2d(rows, cols, c_img, res, FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(plan); // CONVERSION UNSIGNED SHORT

  // free memory
  fftw_destroy_plan(plan);
  free(c_img);

  return res;
}

unsigned short
*backward(int rows, int cols, fftw_complex* freq_repr)
{
  // fourier backward
  unsigned short* res = malloc(rows*cols*sizeof(unsigned short));
  fftw_complex* tmp = malloc(rows*cols*sizeof(fftw_complex));

  fftw_plan plan = fftw_plan_dft_2d(rows, cols, freq_repr, tmp, FFTW_BACKWARD, FFTW_ESTIMATE);
  fftw_execute(plan);

  center(tmp, rows, cols);

  for (int i = 0; i < rows*cols; i++) {
    if (creal(tmp[i])<0) {
      res[i] = 0;
    }
    else
      res[i] = (unsigned short)(creal(tmp[i])/(rows*cols));
  }

  //free memory
  fftw_destroy_plan(plan);
  free(tmp);
  return res;
}

void
freq2spectra(int rows, int cols, fftw_complex* freq_repr, float* as, float* ps)
{
  for (int i = 0; i < rows*cols; i++) {
    as[i] = cabs(freq_repr[i]);
    ps[i] = carg(freq_repr[i]);
  }
}


void
spectra2freq(int rows, int cols, float* as, float* ps, fftw_complex* freq_repr)
{
  for (int i = 0; i < rows*cols; i++) {
    freq_repr[i] = as[i]*cos(ps[i]) + I * as[i]*sin(ps[i]);
  }
}

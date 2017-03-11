/**
 * @file color-transfert
 * @brief transfert color from source image to target image.
 *        Method from Reinhard et al. :
 *        Erik Reinhard, Michael Ashikhmin, Bruce Gooch and Peter Shirley,
 *        'Color Transfer between Images', IEEE CGA special issue on
 *        Applied Perception, Vol 21, No 5, pp 34-41, September - October 2001
 */

#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <bcl.h>

#define D 3

static float RGB2LMS[D][D] = {
  {0.3811, 0.5783, 0.0402},
  {0.1967, 0.7244, 0.0782},
  {0.0241, 0.1288, 0.8444}
};

static float LMS2LAlphaBeta[D][D] = {
  {0.57735, 0.57735, 0.57735},
  {0.408248, 0.408248, -0.816497},
  {0.707107, -0.707107, 0}
};

static float LAlphaBetaB2LMS[D][D] = {
  {0.57735, 0.408248, 0.707107},
  {0.57735, 0.408248, -0.707107},
  {0.57735, -0.816497, 0}
};

static float LMS2RGB[D][D] = {
  {4.4679, -3.5873, 0.1193},
  {-1.2186, 2.3809, -0.1624},
  {0.0497, -0.2439, 1.2045}
};

float* vectorMatrix(float* vector, float matrix[D][D]) {

  float* ret = malloc(D*sizeof(float));

  for (int i = 0; i < D; i++) {
    ret[i] = 0;
    for (int j = 0; j < D; j++) {
      ret[i]+= matrix[i][j]*vector[j];
    }
  }

  return ret;
}

float ** pnmToLab(pnm img, int w, int h) {

  unsigned short* ims_short_R = pnm_get_channel(img, NULL, 0);
  unsigned short* ims_short_G = pnm_get_channel(img, NULL, 1);
  unsigned short* ims_short_B = pnm_get_channel(img, NULL, 2);

  float* L = malloc(w*h*sizeof(float));
  float* M = malloc(w*h*sizeof(float));
  float* S = malloc(w*h*sizeof(float));

  float** lab = malloc(3*sizeof(float*));

  for (int i = 0; i < 3; i++) {
    lab[i] = malloc(h*w*sizeof(float));
  }

  float* l = malloc(w*h*sizeof(float));
  float* a = malloc(w*h*sizeof(float));
  float* b = malloc(w*h*sizeof(float));

  // RGB to LAB
  for (int i = 0; i < w*h; i++) {
    // go to LMS space
    float rgb[D] = {ims_short_R[i], ims_short_G[i], ims_short_B[i]};

    //printf("pnmToLab :\nrgb : %f %f %f\n", rgb[0], rgb[1], rgb[2]);
    float* LMSvec = vectorMatrix(rgb, RGB2LMS);

    //printf("lms : %f %f %f \n", LMSvec[0],LMSvec[1],LMSvec[2]);

    for (int i = 0; i < D; i++) {
      if (LMSvec[i] < 1) {
        LMSvec[i] = 0;
      }
      else {
        LMSvec[i] = log10(LMSvec[i]);
        //printf("OK\n" );
      }
    }
    //printf("lms_afterLog : %f %f %f \n", LMSvec[0],LMSvec[1],LMSvec[2]);
    L[i] = LMSvec[0];
    M[i] = LMSvec[1];
    S[i] = LMSvec[2];

    // go to lab space
    float lms[D] = {L[i], M[i], S[i]};
    float* LABvec = vectorMatrix(lms, LMS2LAlphaBeta);
  //  printf("lab : %f %f %f \n", LABvec[0],LABvec[1],LABvec[2]);
    l[i] = LABvec[0];
    a[i] = LABvec[1];
    b[i] = LABvec[2];
  }

  for (int i = 0; i < h*w; i++) {
    lab[0][i] = l[i];
    lab[1][i] = a[i];
    lab[2][i] = b[i];

    //printf("lab : %f %f %f\n", lab[0][i], lab[1][i], lab[2][i]);
  }

  return lab;
}

unsigned short ** LabtoRGB(float** lab, int w, int h) {

  unsigned short** rgb = malloc(3*sizeof(unsigned short*));

  float* L = malloc(w*h*sizeof(float));
  float* M = malloc(w*h*sizeof(float));
  float* S = malloc(w*h*sizeof(float));

  for (int i = 0; i < 3; i++) {
    rgb[i] = malloc(h*w*sizeof(unsigned short));
  }

  for (int i = 0; i < w*h; i++) {
    // go to LMS space
    float labTmp[D] = {lab[0][i], lab[1][i], lab[2][i]};
    float* LMSvec = vectorMatrix(labTmp, LAlphaBetaB2LMS);
    L[i] = pow(10,LMSvec[0]);
    M[i] = pow(10,LMSvec[1]);
    S[i] = pow(10,LMSvec[2]);

    // go to RGB space
    float rgbTmp[D] = {L[i], M[i], S[i]};
    float* RGBvec = vectorMatrix(rgbTmp, LMS2RGB);

    rgb[0][i] = fmin(RGBvec[0], 255);
    rgb[1][i] = fmin(RGBvec[1], 255);
    rgb[2][i] = fmin(RGBvec[2], 255);

    //printf("rgb : %d %d %d\n", rgb[0][i], rgb[1][i], rgb[2][i]);
  }

  return rgb;
}

void computeLab(float** tab, int size, float* means, float* dev) {

  for (int i = 0; i < D; i++) {
    means[i] = 0;
    dev[i] = 0;
  }

  // compute means
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < D; j++) {
      means[j] += tab[j][i];
    }
  }
  for (int i = 0; i < D; i++) {
    means[i] /= size;
    printf("%f\n", means[i]);
  }

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < D; j++) {
      dev[j] += (tab[j][i]-means[j])*(tab[j][i]-means[j]);
    }
  }

  for (int i = 0; i < D; i++) {
    dev[i] = sqrt(dev[i]/size);
  }
}

static void process(char *ims, char *imt, char* imd){

  pnm ims_pnm = pnm_load(ims);
  pnm imt_pnm = pnm_load(imt);

  int w_ims = pnm_get_width(ims_pnm);
  int h_ims = pnm_get_height(ims_pnm);
  int w_imt = pnm_get_width(imt_pnm);
  int h_imt = pnm_get_height(imt_pnm);

  pnm imd_pnm = pnm_new(w_imt, h_imt, PnmRawPpm);

  float** imd_lab = malloc(3*sizeof(float*));

  for (int i = 0; i < 3; i++) {
    imd_lab[i] = malloc(h_imt*w_imt*sizeof(float));
  }

  float** ims_lab = pnmToLab(ims_pnm, w_ims, h_ims);
  float** imt_lab = pnmToLab(imt_pnm, w_imt, h_imt);

  float ims_means[3];
  float ims_dev[3];
  float imt_means[3];
  float imt_dev[3];

  computeLab(ims_lab, w_ims*h_ims,  ims_means, ims_dev);
  computeLab(imt_lab, w_imt*h_imt,  imt_means, imt_dev);

  for (int i = 0; i < h_imt*w_imt; i++) {
    for (int j = 0; j < D; j++) {
      imt_lab[j][i] -= imt_means[j];
      imd_lab[j][i] = (ims_dev[j]/imt_dev[j])*imt_lab[j][i]+ims_means[j];
    }
    //printf("lab : %f %f %f\n", imt_lab[0][i], imt_lab[1][i], imt_lab[2][i]);
  }

  unsigned short** rgb = LabtoRGB(imd_lab, w_imt, h_imt);

  pnm_set_channel(imd_pnm, rgb[0], 0);
  pnm_set_channel(imd_pnm, rgb[1], 1);
  pnm_set_channel(imd_pnm, rgb[2], 2);

  pnm_save(imd_pnm, PnmRawPpm, imd);
}

void usage (char *s){
  fprintf(stderr, "Usage: %s <ims> <imt> <imd> \n", s);
  exit(EXIT_FAILURE);
}

#define param 3
int main(int argc, char *argv[]){
  if (argc != param+1)
    usage(argv[0]);
  process(argv[1], argv[2], argv[3]);
  return EXIT_SUCCESS;
}

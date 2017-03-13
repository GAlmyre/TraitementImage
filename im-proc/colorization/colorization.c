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
#include <time.h>

#define D 3
#define NEIGHBORHOOD 5

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

    float* LMSvec = vectorMatrix(rgb, RGB2LMS);

    for (int i = 0; i < D; i++) {
      if (LMSvec[i] < 1) {
        LMSvec[i] = 0;
      }
      else {
        LMSvec[i] = log10(LMSvec[i]);
      }
    }
    L[i] = LMSvec[0];
    M[i] = LMSvec[1];
    S[i] = LMSvec[2];

    // go to lab space
    float lms[D] = {L[i], M[i], S[i]};
    float* LABvec = vectorMatrix(lms, LMS2LAlphaBeta);
    l[i] = LABvec[0];
    a[i] = LABvec[1];
    b[i] = LABvec[2];
  }

  for (int i = 0; i < h*w; i++) {
    lab[0][i] = l[i];
    lab[1][i] = a[i];
    lab[2][i] = b[i];
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

    rgb[0][i] = RGBvec[0];
    rgb[1][i] = RGBvec[1];
    rgb[2][i] = RGBvec[2];

  }
  // normalize
  short min = 0;
  short max = 255;
  for (int i = 0; i < D; i++) {
    int maxImg = 0;
    int minImg = 0;
    // get the min and max
    for (int j = 0; j < w*h; j++) {
      if (rgb[i][j] > maxImg) {
        maxImg = rgb[i][j];
      }
      if (rgb[i][j] < minImg) {
        minImg = rgb[i][j];
      }
    }
    // compute normalization
    for (int j = 0; j < w*h; j++) {
      rgb[i][j] = (((max-min)*1.0))/(((maxImg-minImg)*1.0))*rgb[i][j]+(1.0*(min*maxImg-max*minImg)/1.0*(maxImg-minImg));
      if (rgb[i][j]>255) {
      }
    }
  }

  return rgb;
}

void computeLab(float** tab, int size, float* means, float* var) {

  for (int i = 0; i < D; i++) {
    means[i] = 0;
    var[i] = 0;
  }

  // compute means
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < D; j++) {
      means[j] += tab[j][i];
    }
  }
  for (int i = 0; i < D; i++) {
    means[i] /= size;
  }

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < D; j++) {
      var[j] += (tab[j][i]-means[j])*(tab[j][i]-means[j]);
    }
  }

  for (int i = 0; i < D; i++) {
    var[i] = var[i]/size;
  }
}

float deviation(int n, float* tab) {

  float dev = 0;
  float mean = 0;
  // means
  for (int i = 0; i < n; i++) {
    mean += tab[i];
  }
  mean/=n+1;

  for (int i = 0; i < n; i++) {
    dev += (tab[i]-mean)*(tab[i]-mean);
  }
  return dev = sqrt(dev/(n+1));
}

float** jittered_sampling(int nb_samples, int w, int h, float** img) {

  float** samples = malloc(3*sizeof(float*));
  for (int i = 0; i < 3; i++) {
    samples[i] = malloc(nb_samples*sizeof(float));
  }
  int n = w/sqrt(nb_samples);
  int m = h/sqrt(nb_samples);
  int start[2] = {0,0};
  srand(time(NULL));

  for (int i = 0; i < nb_samples; i++) {
    // select a random pixel
    samples[0][i] = 0;
    int x = (int) (rand() / (double)RAND_MAX * (n - 1));
    int y = (int) (rand() / (double)RAND_MAX * (m - 1));

    x = start[0]+x;
    y = start[1]+y;

    // convert to 1d space
    samples[0][i]=w*y+x;


    int nb_pix = 0;
    float pix[25];
    // compute neighborhood
    for (int row = y-NEIGHBORHOOD/2; row < y+NEIGHBORHOOD/2; row++) {
      for (int col = x-NEIGHBORHOOD/2; col < x+NEIGHBORHOOD/2; col++) {
        if ((y>0 && y<h) && (x>0 && x<w)) {
          pix[nb_pix] = img[0][w*col+row];
          nb_pix++;
        }
      }
    }

    // compute standard deviation
    samples[0][i] = (deviation(nb_pix, pix)+img[0][w*y+x])/2;
    samples[1][i] = img[1][w*y+x];
    samples[2][i] = img[2][w*y+x];

    start[0]+=n;
    if (start[0]>w) {
      start[0]=0;
      start[1]+=m;
    }
  }

  return samples;
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

  // convert each image to lab space
  float** ims_lab = pnmToLab(ims_pnm, w_ims, h_ims);
  float** imt_lab = pnmToLab(imt_pnm, w_imt, h_imt);

  // luminance remapping
  float ims_means[3];
  float ims_var[3];
  float imt_means[3];
  float imt_var[3];

  computeLab(ims_lab, w_ims*h_ims,  ims_means, ims_var);
  computeLab(imt_lab, w_imt*h_imt,  imt_means, imt_var);

  for (int i = 0; i < w_ims*h_ims; i++) {
    ims_lab[0][i] = (imt_var[0]/ims_var[0])*(ims_lab[0][i]-ims_means[0])+imt_means[0];
  }

  // jittered sampling
  float** samples = jittered_sampling(200, w_ims, h_ims, ims_lab);

  // Select the best sample item and transfer his a and b to target
  for (int i = 0; i < w_imt*h_imt; i++) {
    int nb_pix = 0;
    float pix[25];
    int x =i%w_imt;
    int y =i/w_imt;
    // compute neighborhood
    for (int row = y-NEIGHBORHOOD/2; row < y+NEIGHBORHOOD/2; row++) {
      for (int col = x-NEIGHBORHOOD/2; col < x+NEIGHBORHOOD/2; col++) {
        if ((y>0 && y<h_imt) && (x>0 && x<w_imt)) {
          pix[nb_pix] = imt_lab[0][w_imt*col+row];
          nb_pix++;
        }
      }
    }
    // compute standard deviation
    float dev = deviation(nb_pix, pix);
    // compute a mean of dev and l
    float weight = (dev+imt_lab[0][i])/2;

    int res = 0;
    for (int k = 1; k < 200; k++) {
      if (fabs(weight - samples[0][k]) < fabs(weight - samples[0][res])) {
        res = k;
      }
    }
    imt_lab[1][i] = samples[1][res];
    imt_lab[2][i] = samples[2][res];
  }

  // come back to rgb space
  unsigned short** rgb = LabtoRGB(imt_lab, w_imt, h_imt);

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

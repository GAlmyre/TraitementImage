#include <stdlib.h>
#include <stdio.h>


#include <bcl.h>

unsigned short median(int n, unsigned short x[]) {
  unsigned short temp;
  int i, j;

  for(i=0; i<n-1; i++) {
    for(j=i+1; j<n; j++) {
      if(x[j] < x[i]) {

        temp = x[i];
        x[i] = x[j];
        x[j] = temp;
      }
    }
  }

  if(n%2==0) {
    // if there is an even number of elements, return mean of the two elements in the middle
    return((x[n/2] + x[n/2 - 1]) / 2.0);
  }
  else {
    // else return the element in the middle
    return x[n/2];
  }
}

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

static void
process(int hs, char* ims_name, char* imd_name)
{
  pnm ims = pnm_load(ims_name);
  int w = pnm_get_width(ims);
  int h = pnm_get_height(ims);
  pnm imd = pnm_new(w, h, PnmRawPpm);
  int size = (hs*2+1)*(hs*2+1);

  unsigned short* window = malloc(size*sizeof(unsigned short));
  unsigned short* imd_short = malloc(h*w*sizeof(unsigned short));

  for (int row = 0; row < h; row++) {
    for (int col = 0; col < w; col++) {
      int n = 0;
    //  for (int row = -1*min(j,hs); row < min(h-j, hs+1); row++) {
      //  for (int col = -1*min(i,hs); col < min(w-i, hs+1); col++) {
      for (int i = 0; i < size; i++) {
        window[i]=0;
      }

      for (int row_win = -1*min(row,hs); row_win < min(h-row, hs+1); row_win++) {
        for (int col_win = -1*min(col,hs); col_win < min(w-col, hs+1); col_win++) {
          window[n] = pnm_get_component(ims,row_win+row,col_win+col,0);
          n++;
        }
      }

      imd_short[row*w+col] = median(n, window);
    }
  }

  for (int row = 0; row < h; row++) {
    for (int col = 0; col < w; col++) {

      pnm_set_component(imd, row, col, 0, imd_short[row*w+col]);
      pnm_set_component(imd, row, col, 1, imd_short[row*w+col]);
      pnm_set_component(imd, row, col, 2, imd_short[row*w+col]);
    }
  }

  pnm_save(imd, PnmRawPpm, imd_name);
}

void usage (char *s){

  fprintf(stderr, "Usage: %s <halfsize> <ims> <imd>\n", s);
  exit(EXIT_FAILURE);
}

#define PARAM 3
int main(int argc, char *argv[]){
  if (argc != PARAM+1)
    usage(argv[0]);

  int   idx     = 1;
  int   hs      = atoi(argv[idx++]);
  char* ims     = argv[idx++];
  char* imd     = argv[idx++];

  process(hs, ims, imd);

  return EXIT_SUCCESS;
}

#include <math.h>

#include "morphology.h"

enum {SQUARE, DIAMOND, DISK, LINE_V, DIAG_R, LINE_H, DIAG_L, CROSS, PLUS};

pnm
se(int s, int hs){

  int size = hs*2+1;
  int x,c_x,c_y;
  c_x = hs;
  c_y = hs;
  pnm res = pnm_new(size, size, PnmRawPpm);

  switch (s) {
    case SQUARE:
      for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
          for (int k = 0; k < 3; k++) {
            pnm_set_component(res, i, j, k, 255);
          }
        }
      }
      return res;
    break;
    case DIAMOND:
      for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
          if (abs(c_x-i)+abs(c_y-j) <= hs) {
            for (int k = 0; k < 3; k++) {
              pnm_set_component(res, i, j, k, 255);
            }
          }
        }
      }
      return res;
    break;
    case DISK:
      x = hs*hs;
      for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
          if (abs((c_x-i)*(c_x-i)+(c_y-j)*(c_y-j)) <= x) {
            for (int k = 0; k < 3; k++) {
              pnm_set_component(res, i, j, k, 255);
            }
          }
        }
      }
      return res;
    break;
    case LINE_V:
    for (int i = 0; i < size; i++) {
      for (int k = 0; k < 3; k++) {
        pnm_set_component(res, i, hs+1, k, 255);
      }
    }
      return res;
    break;
    case DIAG_R:
      x = size-1;
      for (int row = 0; row < size; row++) {
        for (int k = 0; k < 3; k++) {
          pnm_set_component(res, row, x, k, 255);
        }
        x--;
      }
      return res;
    break;
    case LINE_H:
      for (int i = 0; i < size; i++) {
        for (int k = 0; k < 3; k++) {
          pnm_set_component(res, hs+1, i, k, 255);
        }
      }
      return res;
    break;
    case DIAG_L:
      x = 0;
      for (int row = 0; row < size; row++) {
        for (int k = 0; k < 3; k++) {
          pnm_set_component(res, row, x, k, 255);
        }
        x++;
      }
      return res;
    break;
    case CROSS:
      x = 0;
      for (int row = 0; row < size; row++) {
        for (int k = 0; k < 3; k++) {
          pnm_set_component(res, row, x, k, 255);
        }
        x++;
      }
      x = size-1;
      for (int row = 0; row < size; row++) {
        for (int k = 0; k < 3; k++) {
          pnm_set_component(res, row, x, k, 255);
        }
        x--;
      }
      return res;
    break;
    case PLUS:
      for (int i = 0; i < size; i++) {
        for (int k = 0; k < 3; k++) {
          pnm_set_component(res, i, hs+1, k, 255);
        }
      }
      for (int i = 0; i < size; i++) {
        for (int k = 0; k < 3; k++) {
          pnm_set_component(res, hs+1, i, k, 255);
        }
      }
      return res;
    break;
    default:
      return NULL;
    break;
  }
}

void
lesser(unsigned short val, unsigned short* min){
  if (val < *min) {
    *min = val;
  }
}

void
greater(unsigned short val, unsigned short* max){
  if (val > *max) {
    *max = val;
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

void process(int s, int hs, pnm ims, pnm imd, void (*pf)(unsigned short, unsigned short*))
{
  pnm shape = se(s, hs);
  int w = pnm_get_width(ims);
  int h = pnm_get_height(ims);
  unsigned short val;
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      for (int k = 0; k < 3; k++) {
        val = pnm_get_component(ims,j,i,k);
        for (int row = -1*min(j,hs); row < min(h-j, hs+1); row++) {
          for (int col = -1*min(i,hs); col < min(w-i, hs+1); col++) {
            if (pnm_get_component(shape, row+hs, col+hs,  k) == 255) {
              (*pf)(pnm_get_component(ims,j+row, i+col, k), &val);
            }
          }
          pnm_set_component(imd,j,i,k,val);
        }
      }
    }
  }
}

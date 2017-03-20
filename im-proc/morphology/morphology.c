#include <math.h>

#include "morphology.h"

enum {SQUARE, DIAMOND, DISK, LINE_V, DIAG_R, LINE_H, DIAG_L, CROSS, PLUS};

pnm
se(int s, int hs){

  int size = hs*2+1;
  int x,y,d,c_x,c_y,r;
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
      // top diamond
      for (int row = 0; row < hs+1; row++) {
        for (int col = 0; col < size; col++) {
          if (col >= hs-row && col <= hs+row) {
            for (int k = 0; k < 3; k++) {
              pnm_set_component(res, row, col, k, 255);
            }
          }
        }
      }
      // bottom diamond
      for (int row = 0; row < hs; row++) {
        for (int col = 0; col < size; col++) {
          if (col >= hs-row && col <= hs+row) {
            for (int k = 0; k < 3; k++) {
              pnm_set_component(res, size-row-1, col, k, 255);
            }
          }
        }
      }
      return res;
    break;
    case DISK:
      r = hs;
      c_x = hs;
      c_y = hs;
      while (r >= 0) {
        x = 0;
        y = r;
        d = r-1;
        while (y>=x) {
          for (int k = 0; k < 3; k++) {
            pnm_set_component(res, c_x+x, c_y+y, k, 255);
            pnm_set_component(res, c_x+y, c_y+x, k, 255);
            pnm_set_component(res, c_x-x, c_y+y, k, 255);
            pnm_set_component(res, c_x-y, c_y+x, k, 255);
            pnm_set_component(res, c_x+x, c_y-y, k, 255);
            pnm_set_component(res, c_x+y, c_y-x, k, 255);
            pnm_set_component(res, c_x-x, c_y-y, k, 255);
            pnm_set_component(res, c_x-y, c_y-x, k, 255);
          }
          if (d >= 2*x) {
            d = d-2*x-1;
            x++;
          }
          else if (d < 2*(r-y)) {
            d = d+2*y-1;
            y--;
          }
          else {
            d = d+2*(y-x-1);
            y--;
            x++;
          }
        }
        r--;
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
  (void) val;
  (void) min;
}

void
greater(unsigned short val, unsigned short* max){
  (void) val;
  (void) max;
}

void
process(int s,
	int hs,
	pnm ims,
	pnm imd,
	void (*pf)(unsigned short, unsigned short*))
{
  (void) s;
  (void) hs;
  (void) ims;
  (void) imd;
  (void) pf;
}

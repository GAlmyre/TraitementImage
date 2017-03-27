/**
 * @file  labeling.c
 * @brief count connected components in pnm binary image
*/


#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pnm.h>
#include <memory.h>

int _find(int p, int* roots)
{
  while(roots[p]!=p) p=roots[p];
  return p;
}

int _union(int r0, int r1, int* roots)
{
  if(r0 == r1) return r0;
  if(r0 == -1) return r1;
  if(r1 == -1) return r0;
  if(r0 <  r1){
    roots[r1] = r0;
    return r0;
  }else{
    roots[r0]=r1;
    return r1;
  }
}

int _add(int p, int r, int* roots)
{
  if(r==-1)
    roots[p]=p;
  else
    roots[p]=r;
  return roots[p];
}

void
process(pnm ims, pnm imd){
  int             w     = pnm_get_width(ims);
  int             h     = pnm_get_height(ims);
  unsigned short *ps    = pnm_get_channel(ims, NULL, PnmRed);
  int             p     = 0;
  int             r     = -1;
  int            *roots = memory_alloc(w*h*sizeof(int));

  for(int i=0; i<h; i++){
    for(int j=0; j<w; j++){
      r = -1;
      if( j>0 && (*(ps-1)==(*ps)) )
	       r = _union(_find(p-1, roots), r, roots);
      if( (i>0 && j>0) && (*(ps-1-w)==(*ps)) )
	       r = _union(_find(p-1-w, roots), r, roots);
      if( i>0 && (*(ps-w) == (*ps)) )
	       r = _union(_find(p-w, roots), r, roots);
      if( (j<(w-1) && i>0) && (*(ps+1-w)==(*ps)) )
	       r = _union(_find(p+1-w, roots), r, roots);
      r = _add(p, r, roots);
      p++;
      ps++;
    }
  }
  for(p=0; p<w*h; p++)
    roots[p] = _find(p, roots);
  int l=0;
  for(p=0; p<w*h; p++){
    if(roots[p]==p)
      roots[p] = l++;
    else
      roots[p] = roots[roots[p]];
  }

  int colors[l][4];
  srand(time(NULL));
  for (int i = 0; i < l; i++) {
    colors[i][0]=i;
    for (int j = 0; j < 3; j++) {
      colors[i][j+1]= (int) (rand() / (double)RAND_MAX * (254));
    }
  }

  fprintf(stderr, "labeling: %d components found\n", l);

  // trouver le fond
  for (int i = 0; i < l; i++) {
    colors[i][0]=0;
  }
  int back = 0;
  for (int i = 0; i < w*h; i++) {
    colors[roots[i]][0]++;
  }

  for (int i = 0; i < l; i++) {
    if (colors[i][0]>colors[back][0]) {
      back = i;
    }
  }
  printf("back : %d\n", back);
  for (int i = 0; i < w*h; i++) {
    for (int j = 0; j < l; j++) {
      if (roots[i] == j && j!=back) {
        for (int k = 0; k < 3; k++) {
          pnm_set_component(imd, i/w, i%w, k, colors[j][k+1]);
        }
      }
    }
  }

  memory_free(roots);
}

void
usage(char* s)
{
  fprintf(stderr,"%s <ims> <imd>\n",s);
  exit(EXIT_FAILURE);
}

#define PARAM 2
int
main(int argc, char* argv[])
{
  if(argc != PARAM+1)
    usage(argv[0]);
  pnm pnm_ims = pnm_load(argv[1]);
  char* imd_name = argv[2];
  pnm imd = pnm_new(pnm_get_width(pnm_ims), pnm_get_height(pnm_ims), PnmRawPpm);
  process(pnm_ims, imd);
  pnm_save(imd, PnmRawPpm, imd_name);
  pnm_free(pnm_ims);

  return EXIT_SUCCESS;
}

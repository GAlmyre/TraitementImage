/**
 * @file print-ppm.c
 * @brief print to standard output a color ppm file
 */

#include <stdlib.h>
#include <stdio.h>

static void
process(int r, int g, int b, int rows, int cols){

  printf("P3\n%d %d 255\n",cols, rows);

  for (int i = 0; i < cols; i++) {
    for (int j = 0; j < rows; j++) {
      printf("%d %d %d\n", r, g, b);
    }
  }
}

void
usage (char *s)
{
  fprintf(stderr,
	  "Usage: %s <r={0,255}> <g={0,255}> <b={0,255}> <rows> <cols>\n"
	  ,s);
  exit(EXIT_FAILURE);
}

#define PARAMS 5
int
main(int argc, char *argv[])
{
  if (argc != PARAMS+1){
    usage(argv[0]);
  }
  // get the inputs and process
  int r=atoi(argv[1]), g=atoi(argv[2]), b=atoi(argv[3]), rows=atoi(argv[4]), cols=atoi(argv[5]);
  process(r, g, b, rows, cols);
  return EXIT_SUCCESS;
}

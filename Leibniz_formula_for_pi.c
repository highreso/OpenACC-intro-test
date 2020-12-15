#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1600000000L

int main(int argc, char *argv[])
{
  double pi, piq = 1.0;
  long int li, upto = N;
  clock_t begin, end;

  if (argc > 1) upto = atol(argv[1]);

  begin = clock();

#pragma acc kernels
  for (li = 1; li < upto; li++) 
  {
    if (li % 2 == 0) piq += 1.0 / (2.0 * li + 1.0);
    else             piq -= 1.0 / (2.0 * li + 1.0);
  }

  pi = 4.0 * piq;

  end = clock();

  fprintf(stdout, "pi = %.12f (%.2f s)\n",
          pi, (double)(end - begin) / CLOCKS_PER_SEC);
  return EXIT_SUCCESS;
}
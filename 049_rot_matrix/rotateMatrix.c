#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "The comman line argument is not correct.");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "The input file is empty.");
    return EXIT_FAILURE;
  }
  char input[10][10];
  int c;
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 11; j++) {
      c = fgetc(f);
      if (j < 10 && c == '\n') {
        fprintf(stderr, "The number of chars in row less than 10.\n");
        return EXIT_FAILURE;
      }
      if (j < 10 && c != '\n') {
        input[i][j] = c;
      }
      if (j == 10 && c != '\n') {
        fprintf(stderr, "The number of chars in row more than 10.\n");
        return EXIT_FAILURE;
      }
      if (c == EOF) {
        fprintf(stderr, "The input matrix end too early.\n");
        printf("after one round of j,c=%d\n", c);
      }
      if (c == EOF) {
        fprintf(stderr, "The input matrix has less than 10 rows.");
        return EXIT_FAILURE;
      }
    }
  }
  c = fgetc(f);
  if (c != EOF) {
    fprintf(stderr, "The input matrix has more than 10 rows.");
    return EXIT_FAILURE;
  }

  for (int i = 0; i < 10; i++) {
    for (int j = 9; j >= 0; j--) {
      fprintf(stdout, "%c", input[j][i]);
    }
    fprintf(stdout, "\n");
  }
  return EXIT_SUCCESS;
}

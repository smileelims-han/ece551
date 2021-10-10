#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int find_max(int * alpha, int size) {
  int max = 0;
  for (int i = 0; i < size; i++) {
    if (alpha[max] < alpha[i]) {
      max = i;
    }
  }
  return max;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "The input is wrong\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "There is no content in .txt file.\n");
    return EXIT_FAILURE;
  }
  int c;
  int alpha[26] = {0};
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c -= 'a';
      alpha[c]++;
    }
  }
  int max = find_max(alpha, 26);
  max += 'a';
  if (max >= 'e') {
    printf("%d\n", max - 'e');
  }
  if (max < 'e') {
    printf("%d\n", max - 'e' + 26);
  }
  return EXIT_SUCCESS;
}

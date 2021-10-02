#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

int main(void) {
  int array_1[1] = {-1};
  int array_2[1] = {0};
  int array_3[3] = {1, 2, 3};
  int array_4[3] = {3, 2, 1};
  int array_5[3] = {1, 1, 1};
  int array_6[11] = {1, 2, 3, 4, 3, 2, 3, 4, 5, 6, 7};
  int array_7[3] = {-10, -5, -1};
  int array_8[4] = {-10, -5, 0, 9};
  int array_9[1] = {1};
  if (maxSeq(array_9, 0) != 0) {
    return EXIT_FAILURE;
  }
  if (maxSeq(array_1, 1) != 1) {
    printf("array_1 got %ld\n", maxSeq(array_1, 1));
    return EXIT_FAILURE;
  }
  if (maxSeq(array_2, 1) != 1) {
    printf("array_2 got %ld\n", maxSeq(array_2, 1));
    return EXIT_FAILURE;
  }
  if (maxSeq(array_3, 3) != 3) {
    printf("array_3 got %ld\n", maxSeq(array_3, 3));
    return EXIT_FAILURE;
  }
  if (maxSeq(array_4, 3) != 1) {
    printf("array_4 got %ld\n", maxSeq(array_4, 3));
    return EXIT_FAILURE;
  }
  if (maxSeq(array_5, 3) != 1) {
    printf("array_5 got %ld\n", maxSeq(array_5, 3));
    return EXIT_FAILURE;
  }
  if (maxSeq(array_6, 11) != 6) {
    printf("array_6 got %ld\n", maxSeq(array_6, 11));
    return EXIT_FAILURE;
  }
  if (maxSeq(array_7, 3) != 3) {
    printf("array_7 got %ld\n", maxSeq(array_7, 3));
    return EXIT_FAILURE;
  }
  if (maxSeq(array_8, 4) != 4) {
    printf("array_8 got %ld\n", maxSeq(array_8, 4));
    return EXIT_FAILURE;
  }
  //if (maxSeq(array_9, 9) != 6) {
  // printf("array_8 got %ld\n", maxSeq(array_9, 9));
  // return EXIT_FAILURE;
  //}

  return EXIT_SUCCESS;
}

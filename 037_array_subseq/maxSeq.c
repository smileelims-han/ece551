#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if (n == 0) {
    return 0;
  }
  size_t maxs = 1;
  size_t nowmax = 1;
  int current = array[0];
  for (size_t i = 1; i < n; i++) {
    if (array[i] > current) {
      maxs++;
      if (maxs > nowmax) {
        nowmax = maxs;
      }
    }
    if (array[i] <= current) {
      maxs = 1;
    }
    current = array[i];
  }
  return nowmax;
}

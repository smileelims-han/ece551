#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

int run_check(unsigned x, unsigned y, unsigned expected_ans) {
  if (power(x, y) != expected_ans) {
    exit(EXIT_FAILURE);
  }
  else {
    return EXIT_SUCCESS;
  }
}

int main(void) {
  //  if (run_check(0, 0, 1) || run_check(0, 1, 0) || run_check(1, 0, 1) ||
  //  run_check(2, 2, 4) || run_check(2, 5, 32) || run_check(3, 10, 59049)||
  //    run_check(80,0,1) || run_check() {
  //  return EXIT_FAILURE;
  //}
  for (unsigned x = 0; x <= 100; x++) {
    for (unsigned y = 0; y <= 100; y++) {
      if (x == 0) {
        run_check(x, y, 1);
      }
      run_check(x, y, x ^ y);
    }
  }
  return EXIT_SUCCESS;
}

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
unsigned power(unsigned x, unsigned y);

int run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned ans = power(x, y);
  if (ans != expected_ans) {
    printf("wrong!! x=%u y=%u ans=%u expected=%u \n", x, y, ans, expected_ans);
    exit(EXIT_FAILURE);
  }
  else {
    return EXIT_SUCCESS;
  }
}

int main(void) {
  if (run_check(0, 0, 1) || run_check(0, 1, 0) || run_check(1, 0, 1) ||
      run_check(2, 2, 4) || run_check(2, 5, 32) || run_check(3, 10, 59049) ||
      run_check(80, 0, 1) || run_check(63240, 2, 3999297600)) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

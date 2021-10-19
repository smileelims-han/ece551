#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 4) {
    fprintf(stderr, "The input file number is incorrect.\n");
    return EXIT_FAILURE;
  }

  catarray_t * cat = read_list(argv[2]);
  char * temp = read_temp(argv[3]);
  char * parsed_temp = parse_temp(temp, cat, 1);

  printWords(cat);
  free(temp);
  free(parsed_temp);
  free_cat(cat);
  return EXIT_SUCCESS;
}

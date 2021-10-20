#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 4) {
    fprintf(stderr, "The input file number is incorrect.\n");
    return EXIT_FAILURE;
  }
  FILE * f_list = open_file(argv[2]);
  catarray_t * cat = read_list(f_list);
  FILE * f_temp = open_file(argv[3]);
  char * temp = read_temp(f_temp);
  char * parsed_temp = parse_temp(temp, cat, 1);

  printWords(cat);
  free(temp);
  free(parsed_temp);
  free_cat(cat);
  return EXIT_SUCCESS;
}

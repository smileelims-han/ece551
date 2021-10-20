

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "The input file number is incorrect.\n");
    return EXIT_FAILURE;
  }
  FILE * f_list = open_file(argv[1]);
  FILE * f_temp = open_file(argv[2]);
  char * temp = read_temp(f_temp);
  catarray_t * cat = read_list(f_list);
  char * parsed_temp = parse_temp(temp, cat, 0);
  printf("%s\n", parsed_temp);
  printWords(cat);

  free(temp);
  free(parsed_temp);
  free_cat(cat);
  return EXIT_SUCCESS;
}

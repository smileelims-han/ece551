#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "The input file for step1 has to be one template.\n");
    return EXIT_FAILURE;
  }
  FILE * f = open_file(argv[1]);
  char * temp_file = read_temp(f);
  catarray_t * cats = NULL;
  char * parsed_temp = parse_temp(temp_file, cats, 0);

  printf("%s", parsed_temp);

  free(temp_file);
  free(parsed_temp);

  return EXIT_SUCCESS;
}

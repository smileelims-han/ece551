#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
  FILE * f_list = NULL;
  FILE * f_temp = NULL;
  int flag = 0;
  if (argc < 3) {
    fprintf(stderr, "The input file number is incorrect.\n");
    return EXIT_FAILURE;
  }
  if (argc == 3) {
    f_list = open_file(argv[1]);
    f_temp = open_file(argv[2]);
    flag = 0;
  }
  if (argc == 4) {
    f_list = open_file(argv[2]);
    f_temp = open_file(argv[3]);
    flag = 1;
  }

  char * temp = read_temp(f_temp);
  catarray_t * cat = read_list(f_list);
  char * parsed_temp = parse_temp(temp, cat, flag);
  printf("%s\n", parsed_temp);

  free_cat(cat);
  free(temp);
  free(parsed_temp);

  return EXIT_SUCCESS;
}

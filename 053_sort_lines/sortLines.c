#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void read_sort_print(void * file) {
  size_t sz;
  size_t count = 0;
  char ** arr_string = NULL;
  char * lines = NULL;
  while (getline(&lines, &sz, file) >= 0) {
    arr_string = realloc(arr_string, (count + 1) * sizeof(*arr_string));
    arr_string[count] = lines;
    lines = NULL;
    count++;
  }
  free(lines);
  sortData(arr_string, count);
  for (size_t i = 0; i < count; i++) {
    printf("%s", arr_string[i]);
    free(arr_string[i]);
  }
  free(arr_string);
}

void read_file(int argc, char ** argv) {
  for (int i = 1; i < argc - 1; i++) {
    FILE * f = fopen(argv[i], "r");
    if (f == NULL) {
      fprintf(stderr, "The input file is empty.\n");
      exit(EXIT_FAILURE);
    }
    read_sort_print(f);
    if (fclose(f) != 0) {
      fprintf(stderr, "The file cannot close.\n");
      exit(EXIT_FAILURE);
    }
  }
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  FILE * f;
  if (argc == 1) {
    f = stdin;
    if (f == NULL) {
      fprintf(stderr, "The input stdin is empty.\n");
      return EXIT_FAILURE;
    }
    read_sort_print(f);
  }
  if (argc > 1) {
    read_file(argc, argv);
  }
  return EXIT_SUCCESS;
}

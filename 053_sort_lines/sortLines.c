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

void sort_print(void * f) {
  size_t sz;
  size_t count = 0;
  char ** array = NULL;
  char * lines = NULL;
  while (getline(&lines, &sz, f) >= 0) {
    array = realloc(array, (count + 1) * sizeof(*array));
    array[count] = lines;
    lines = NULL;
    count++;
  }
  free(lines);
  sortData(array, count);
  for (size_t i = 0; i < count; i++) {
    printf("%s", array[i]);
    free(array[i]);
  }
  free(array);
}

void read_file(int argc, char ** argv) {
  for (int i = 0; i < argc - 1; i++) {
    FILE * f = fopen(argv[1 + i], "r");
    if (f == NULL) {
      fprintf(stderr, "The input of a file is empty\n");
      exit(EXIT_FAILURE);
    }
    sort_print(f);
    if (fclose(f) != 0) {
      fprintf(stderr, "Cannot close the file.\n");
      exit(EXIT_FAILURE);
    }
  }
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  FILE * f;
  if (argc <= 1) {
    f = stdin;
    sort_print(f);
  }
  if (argc > 1) {
    read_file(argc, argv);
  }
  return EXIT_SUCCESS;
}

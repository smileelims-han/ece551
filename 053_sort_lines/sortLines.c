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

size_t read_sort(FILE * file, char ** array) {
  char * lines = NULL;
  size_t siz = 0;
  size_t count = 0;
  while (getline(&lines, &siz, file)) {
    array = realloc(array, (count + 1) * sizeof(*array));
    array[count] = lines;
    count++;
  }
  free(lines);
  sortData(array, count);
  return count;
}

void pr_result(char ** sorted, size_t n_element) {
  for (size_t i = 0; i < n_element; i++) {
    printf("%s", sorted[i]);
    free(sorted[i]);
  }
  free(sorted);
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  size_t sz = 0;
  char ** arr_str = NULL;
  FILE * f;
  if (argc <= 1) {
    f = stdin;
    if (f == NULL) {
      fprintf(stderr, "There is no input in stdin.\n");
      return EXIT_FAILURE;
    }
    sz = read_sort(f, arr_str);
    pr_result(arr_str, sz);
    if (fclose(f) != 0) {
      fprintf(stderr, "The file cannot close.\n");
      return EXIT_FAILURE;
    }
  }
  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      sz = 0;
      f = fopen(argv[i], "r");
      if (f == NULL) {
        fprintf(stderr, "This is no input in the input files.\n");
        return EXIT_FAILURE;
      }
      sz = read_sort(f, arr_str);
      pr_result(arr_str, sz);
      if (fclose(f) != 0) {
        fprintf(stderr, "The file cannot close.\n");
        return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}

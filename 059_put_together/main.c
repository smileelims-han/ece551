
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  counts_t * c = createCounts();
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "the input file is empty.\n");
    exit(EXIT_FAILURE);
  }

  ssize_t len = 0;
  size_t sz;
  char * line = NULL;

  while ((len = getline(&line, &sz, f)) >= 0) {
    char * e = strchr(line, '\n');
    size_t len_key = e - line;
    char * key = malloc((len_key + 1) * sizeof(*key));
    strncpy(key, line, len_key);
    key[len_key] = '\0';
    addCount(c, lookupValue(kvPairs, key));
    free(key);
  }
  free(line);
  if (fclose(f) != 0) {
    fprintf(stderr, "The file cannot close.\n");
    exit(EXIT_FAILURE);
  }
  return c;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  if (argc < 3) {
    fprintf(stderr, "This program needs at least two input file.\n");
    return EXIT_FAILURE;
  }
  kvarray_t * kv = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    if (fclose(f) != 0) {
      fprintf(stderr, "The outfile cannot close.\n");
      return EXIT_FAILURE;
    }
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
    //free the memory for kv
    freeKVs(kv);
    return EXIT_SUCCESS;
  }
}

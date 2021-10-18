#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvpair_t * key_value(char * line) {
  kvpair_t * pair = malloc(sizeof(*pair));
  char * k = line;
  char * s = strchr(line, '=');
  char * e = strchr(line, '\n');

  if ((s == NULL) || (e == NULL)) {
    fprintf(stderr, "There is no '=' in the line\n");
    exit(EXIT_FAILURE);
  }

  size_t len_key = s - k + 1;
  size_t len_value = e - s;
  pair->key = malloc(len_key * sizeof(*pair->key));
  pair->value = malloc(len_value * sizeof(*pair->value));
  strncpy(pair->key, line, len_key - 1);
  pair->key[len_key - 1] = '\0';
  strncpy(pair->value, s + 1, len_value - 1);
  pair->value[len_value - 1] = '\0';
  return pair;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "The input file is empty.\n");
    exit(EXIT_FAILURE);
  }

  size_t sz = 0;
  ssize_t len = 0;
  char * line = NULL;

  kvarray_t * array_pairs = malloc(sizeof(*array_pairs));
  array_pairs->num_pairs = 0;
  array_pairs->pairs = NULL;

  while ((len = getline(&line, &sz, f)) >= 0) {
    kvpair_t * pair = key_value(line);
    array_pairs->pairs =
        realloc(array_pairs->pairs, (array_pairs->num_pairs + 1) * sizeof(*array_pairs));
    array_pairs->pairs[array_pairs->num_pairs] = pair;
    array_pairs->num_pairs++;
    pair = NULL;
  }
  free(line);
  if (fclose(f) != 0) {
    fprintf(stderr, "The file cannot close.\n");
    exit(EXIT_FAILURE);
  }
  return array_pairs;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  size_t n = pairs->num_pairs;
  for (size_t i = 0; i < n; i++) {
    free(pairs->pairs[i]->key);
    free(pairs->pairs[i]->value);
    free(pairs->pairs[i]);
  }
  free(pairs->pairs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->num_pairs; i++) {
    printf("key = '%s' value = '%s'\n", pairs->pairs[i]->key, pairs->pairs[i]->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (size_t i = 0; i < pairs->num_pairs; i++) {
    if (strcmp(pairs->pairs[i]->key, key) == 0) {
      return pairs->pairs[i]->value;
    }
  }
  return NULL;
}

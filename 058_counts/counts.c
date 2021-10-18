#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

counts_t * createCounts(void) {
  //WRITE ME
  counts_t * counts = malloc(sizeof(*counts));
  counts->counts = NULL;
  counts->num_counts = 0;
  counts->num_unknown = 0;
  return counts;
}

void add_value(counts_t * c, const char * name) {
  c->num_counts++;
  c->counts = realloc(c->counts, c->num_counts * sizeof(*c->counts));
  c->counts[c->num_counts - 1] = malloc(sizeof(*c->counts[c->num_counts - 1]));
  c->counts[c->num_counts - 1]->num_value = 1;
  c->counts[c->num_counts - 1]->value = strdup(name);
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
  if (name == NULL) {
    c->num_unknown++;
  }
  if (name != NULL) {
    int name_saw = 0;
    for (size_t i = 0; i < c->num_counts; i++) {
      if (strcmp(c->counts[i]->value, name) == 0) {
        c->counts[i]->num_value++;
        name_saw++;
        break;
      }
    }
    if (name_saw == 0) {
      add_value(c, name);
    }
  }
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (size_t i = 0; i < c->num_counts; i++) {
    fprintf(outFile, "%s: %lu\n", c->counts[i]->value, c->counts[i]->num_value);
  }
  if (c->num_unknown != 0) {
    fprintf(outFile, "<unknown>: %lu\n", c->num_unknown);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (size_t i = 0; i < c->num_counts; i++) {
    free(c->counts[i]);
  }
  free(c->counts);
  free(c);
}

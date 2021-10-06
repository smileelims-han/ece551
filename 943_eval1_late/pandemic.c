#include "pandemic.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

country_t parseLine(char * line) {
  if (line == NULL) {
    fprintf(stderr, "Input is empty.");
    exit(EXIT_FAILURE);
  }
  /* check if *line is empty string */
  /* if not empty string,find the first comma */

  country_t ans;
  char *calc,
      *ref; /* set up two pointer, one for calculation the length, one for reference the start. */
  size_t name_length;
  calc = line;
  ref = line;

  /* check the location of comma, at the same time check if there has incorrect null terminal inside name */
  for (int i = 0; *calc != ','; i++) {
    if (*calc == '\0') {
      fprintf(stderr, "There is incorrect type in country's name.");
      exit(EXIT_FAILURE);
    }
    else {
      calc++;
    }
  }
  name_length = calc - ref;

  /* copy the chars in line before comma into ans.name */
  strncpy(ans.name, line, name_length);
  ans.name[name_length] = '\0';

  /* Then check the chars after comma, are they all numbers */
  calc++;
  ref = calc;
  ans.population = 0ULL;
  size_t pop_length;
  for (int j = 0; *calc != '\0'; j++) {
    calc++;
  }
  pop_length = calc - ref;
  char * pop[pop_length];

  for (int k = 0; *ref != *calc; k++) {
    pop[k] = ref;
    ref++;
  }

  ans.population = atoi(*pop);
  if (ans.population == 0) {
    fprintf(stderr, "The input format is incorrect.\n");
    exit(EXIT_FAILURE);
  }
  if (ans.population < 0) {
    ans.population = (uint64_t)ans.population;
  }
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  if (data == NULL) {
    fprintf(stderr, "There is an emtpy input.\n");
    exit(EXIT_FAILURE);
  }
  if (n_days < 7) {
    fprintf(stderr, "There is not enough days as input.\n");
    exit(EXIT_FAILURE);
  }
  size_t avg_length = n_days - 6;
  unsigned * ptr = data;
  unsigned * ref = data;
  for (size_t i = 0; i < avg_length; i++) {
    double sum = 0;
    for (size_t j = 0; j < 7; j++) {
      sum = sum + *ptr;
      ptr++;
    }
    avg[i] = sum / 7.0;
    ptr = ref + i + 1;
  }
}

/*void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
  }*/

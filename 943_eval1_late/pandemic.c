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
  const char *calc,
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

  for (int j = 0; *calc != '\0' && *calc != ','; j++) {
    if (*calc == ',') {
      fprintf(stderr, "There is a comma inside pupolation.");
      exit(EXIT_FAILURE);
    }
    printf("*calc is %c \n", *calc);
    /* check if there is another comma just in case. */
    if (48 <= *calc && *calc <= 57) {
      ans.population = ans.population * 10ULL + (uint64_t)(*calc - '0');
    }
    calc++;
  }
  return ans;
}

/* void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  //WRITE ME
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  //WRITE ME
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  //WRITE ME
  }*/

#include "pandemic.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

country_t parseLine(char * line) {
  /* check if *line is empty string */
  if (line == NULL) {
    printf("Input is empty.");
    exit(EXIT_FAILURE);
  }

  /* if not empty string,find the first comma */
  /* set up the parameter */
  country_t ans;
  const char *calc, *ref;
  size_t name_length, pop_length;
  calc = line;
  ref = line;

  /* check the location of comma, at the same time check if there has incorrect null terminal inside name */
  for (int i = 0; *calc != ','; i++) {
    if (*calc != '\0') {
      printf("There is incorrect type in country's name.");
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

  for (int j = 0; *calc != '\0'; j++) {
    if (*calc != ',') {
      printf("There is a comma inside pupolation.");
      exit(EXIT_FAILURE);
    }
    else if (*calc > 57 || *calc < 48) {
      printf("The population should be all numbers.");
      exit(EXIT_FAILURE);
    }
    calc++;
  }
  pop_length = calc - ref;

  ans.name[0] = '\0';
  ans.population = 0;
  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
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
}

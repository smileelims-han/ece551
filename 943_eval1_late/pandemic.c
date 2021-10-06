#include "pandemic.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

country_t parseLine(char * line) {
  /* check if is empty string */
  if (line == NULL) {
    fprintf(stderr, "Input is empty.");
    exit(EXIT_FAILURE);
  }

  /* find the first comma */
  country_t ans;
  size_t name_length;
  char *calc, *ref;
  calc = line;
  ref = line;
  /* set up two pointers, one will move
  in the array to check the desired symbol;
  one will set at the begining for reference.
  The difference between the two pointers is
  the length of name or population.*/

  /* Get the location of comma */
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

  /* copy the chars in sting before comma into ans.name */
  strncpy(ans.name, line, name_length);
  ans.name[name_length] = '\0';

  /* Then start work for then population */
  /* move the pointers to the first chars after comma */
  calc++;
  ref = calc;
  ans.population = 0ul;
  size_t pop_length;

  /* moving the pointer to the end of numbers and
  calculate the length of numbers */
  for (int j = 0; *calc != '\0'; j++) {
    calc++;
  }
  pop_length = calc - ref;

  /* copy the parts after comma into a new string */
  char * pop[pop_length];
  for (int k = 0; *ref != *calc; k++) {
    pop[k] = ref;
    ref++;
  }

  /* using atoi to transfer the chars into numbers */
  ans.population = atoi(*pop);
  if (ans.population == 0) {
    fprintf(stderr, "The input format is incorrect.\n");
    exit(EXIT_FAILURE);
  }
  /* return FAILURE when the first symbol
     (excluded space) is not number */
  if (ans.population < 0) {
    ans.population = (uint64_t)ans.population;
  }
  /* incase there is negative number, transfer
     it into uint64_t */

  return ans;
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  /* return error if the input data is empty
     or the inputs days less than 7 days (so we cannot calculate)*/
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

  /* calculate the sum of 7 days(from the start date),
     then divided into 7*/
  for (size_t i = 0; i < avg_length; i++) {
    double sum = 0;
    for (size_t j = 0; j < 7; j++) {
      sum = sum + *ptr;
      ptr++;
    }
    avg[i] = sum / 7.0;
    ptr = ref + i + 1; /*every time after calculate 7 days,
	          	the pointer goes back to the one next to index i*/
  }
}

void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  /* check if the input data is empty*/
  if (data == NULL) {
    fprintf(stderr, "There is an empty input.\n");
    exit(EXIT_FAILURE);
  }

  unsigned sum = 0;
  for (size_t i = 0; i < n_days; i++) {
    sum += *(data + i);
    *(cum + i) = (sum * 1.0 / pop) * 100000;
  }
}

/* function findMax for step 4 */
size_t findMax(unsigned * data, size_t n_days) {
  size_t maxnum_loc = 0;
  unsigned maxnum;
  maxnum = *data;

  /* compare the max with each number and
  update the max, stored the index of maxnumber 
  in the giving string */
  for (size_t i = 0; i < n_days; i++) {
    if (maxnum < *(data + i)) {
      maxnum = *(data + i);
      maxnum_loc = i;
    }
  }
  return maxnum_loc;
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  /*check if the inputs data are empty */
  if (countries == NULL || data == NULL) {
    fprintf(stderr, "There is an emtpy input.\n");
    exit(EXIT_FAILURE);
  }

  /*first, find the maxnumber of each country in
  given days, stored it into a new array which ordered
  based on the country sequence in the giving array*/
  unsigned maxPer_con[n_countries];
  for (size_t i = 0; i < n_countries; i++) {
    size_t max_loc = findMax(*(data + i), n_days);
    maxPer_con[i] = *(data[i] + max_loc);
  }

  /*Then, find the maxnumber of all countries */
  size_t max_country = findMax(maxPer_con, n_countries);
  printf("%s has the most daily cases with %u\n",
         (countries + max_country)->name,
         *(maxPer_con + max_country));
}

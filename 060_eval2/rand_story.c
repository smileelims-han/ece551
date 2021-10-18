#include "rand_story.h"

//read the template file and return a char*
char * read_temp(const char * file_name) {
  FILE * f = fopen(file_name, "r");
  if (f == NULL) {
    fprintf(stderr, "The input template file is empty.\n");
    exit(EXIT_FAILURE);
  }

  //creat a string with content of template file.
  char * temp;
  size_t num_temp = 0;
  int c;
  while ((c = fgetc(f)) != EOF) {
    temp = realloc(temp, (num_temp + 1) * sizeof(*temp));
    temp[num_temp] = c;
    num_temp++;
  }
  temp = realloc(temp, (num_temp + 1) * sizeof(*temp));
  temp[num_temp] = '\0';

  if (fclose(f) != 0) {
    fprintf(stderr, "The input template file cannot close.\n");
    exit(EXIT_FAILURE);
  }
  return temp;
}

/*check if the template file following the rule of each
  '_' have a matching '_' on the same line; */
int check_underscore(char * p) {
  char * symbol = strchr(p, '_');
  char * next_line = strchr(p, '\n');
  if (symbol == NULL) {
    return 0;
  }
  else if (next_line - symbol < 0) {
    return 0;
  }
  return 1;
}

char * replace_blank(char * p_temp, size_t n_temp, char * start, catarray_t * cats) {
  if (check_underscore(start) == 0) {
    fprintf(stderr, "The blank format does not meet the requirement.");
    exit(EXIT_FAILURE);
  }

  char * end = strchr(start, '_');
  size_t len_blank = end - start;
  char cate_name[len_blank];
  strncpy(cate_name, start, len_blank - 1);
  cate_name[len_blank] = '\0';
  printf("cate_nume = %s\n", cate_name);

  const char * replace_word = chooseWord(cate_name, cats);

  size_t len_replace = strlen(replace_word);
  n_temp = n_temp + len_replace;
  p_temp = realloc(p_temp, (n_temp - 1) * sizeof(*p_temp));
  strcat(p_temp, replace_word);
  start = end;
  return p_temp;
}

char * parse_temp(char * temp, catarray_t * cats) {
  char * ptr = temp;
  char * parsed_temp = NULL;
  size_t num_temp = 0;
  while (*ptr != '\0') {
    if (*ptr != '_') {
      parsed_temp = realloc(parsed_temp, (num_temp + 1) * sizeof(*parsed_temp));
      parsed_temp[num_temp] = *ptr;
      num_temp++;
      ptr++;
    }
    if (*ptr == '_') {
      parsed_temp = replace_blank(parsed_temp, num_temp, ptr, cats);
      num_temp = strlen(parsed_temp);
      ptr++;
    }
  }
  parsed_temp[num_temp] = '\0';
  return parsed_temp;
}

#include "rand_story.h"

//read the template file and return a char*
FILE * open_file(const char * file_name) {
  FILE * f = fopen(file_name, "r");
  if (f == NULL) {
    fprintf(stderr, "The input template file is empty.\n");
    exit(EXIT_FAILURE);
  }
  else {
    return f;
  }
}

char * read_temp(const char * file_name) {
  FILE * f = open_file(file_name);

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
  printf("In read_temp, the temp is %s\n", temp);
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

//check if the name is integer
int check_int(char * name) {
  char * p = name;
  while (*p != '\0') {
    if (*p > 48 && *p <= 57) {
      return 1;
    }
    if (*p == 48) {
      fprintf(stderr, "The number on blank should not be zero.\n");
      return EXIT_FAILURE;
    }
    p++;
  }
  return 0;
}

char * get_used(category_t * used, int n_back) {
  if (used->n_words == 0) {
    fprintf(stderr, "There is no used work.\n");
    exit(EXIT_FAILURE);
  }

  size_t len_w = strlen(used->words[(used->n_words) - n_back]);
  char * replace_w = malloc(len_w * sizeof(*replace_w));
  strcpy(replace_w, used->words[(used->n_words) - n_back]);
  return replace_w;
}

void add_to_used(category_t * used, char * word) {
  used->n_words++;
  size_t len_w = strlen(word);
  used->words = realloc(used->words, used->n_words * sizeof(*used->words));
  used->words[used->n_words - 1] =
      malloc((len_w + 1) * sizeof(*used->words[used->n_words - 1]));
  strcpy(used->words[used->n_words - 1], word);
}

//check if the name in the c.
void check_name_cats(char * name, catarray_t * c) {
  if (check_int(name) == 0) {
    for (size_t i = 0; i < c->n; i++) {
      if (strcmp(name, c->arr[i].name) == 0) {
        return;
      }
    }
    fprintf(stderr, "There is an invalet name.\n");
    exit(EXIT_FAILURE);
  }
  return;
}
void no_reused_cat(catarray_t * cat, char * word) {
  if (cat->n == 0) {
    fprintf(stderr, "There is no more category avaliable.\n");
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < cat->n; i++) {
    for (size_t j = 0; j < cat->arr[i].n_words; j++) {
      if (strcmp(word, cat->arr[i].words[j]) == 0) {
        free(cat->arr[i].words[j]);
        cat->arr[i].n_words--;
        return;
      }
    }
  }
}

char * replace_blank(char * p_temp,
                     size_t n_temp,
                     char * start,
                     catarray_t * cats,
                     category_t * used_word,
                     int flag) {
  if (check_underscore(start) == 0) {
    fprintf(stderr, "The blank format does not meet the requirement.");
    exit(EXIT_FAILURE);
  }

  //parse the name
  char * end = strchr(start, '_');
  size_t len_blank = end - start - 1;
  char * cate_name = malloc((len_blank + 1) * sizeof(*cate_name));
  strncpy(cate_name, start + 1, len_blank);
  cate_name[len_blank] = '\0';
  printf("cate_name = %s\n", cate_name);

  //if name is in catarray
  check_name_cats(cate_name, cats);

  //if name is number - use used word
  char * replace_word = NULL;
  if (check_int(cate_name) == 1) {
    int back = atoi(cate_name);
    replace_word = get_used(used_word, back);
  }

  //if name if not number - use chooseWord
  if (check_int(cate_name) == 0) {
    replace_word = (char *)chooseWord(cate_name, cats);
    if (flag == 1) {
      no_reused_cat(cats, replace_word);
    }
  }

  //replace the word in the string
  size_t len_replace = strlen(replace_word);
  n_temp = n_temp + len_replace;
  p_temp = realloc(p_temp, n_temp * sizeof(*p_temp));
  strcat(p_temp, replace_word);
  start = end;

  //add the replace word to the used_word
  add_to_used(used_word, replace_word);
  free(replace_word);

  return p_temp;
}

char * parse_temp(char * temp, catarray_t * cats, int flag) {
  char * ptr = temp;
  char * parsed_t = NULL;
  size_t num_temp = 0;

  //define the a category_t to record the used words
  category_t * used_word = malloc(sizeof(*used_word));
  used_word->name = NULL;
  used_word->words = NULL;
  used_word->n_words = 0;

  while (*ptr != '\0') {
    if (*ptr != '_') {
      parsed_t = realloc(parsed_t, (num_temp + 1) * sizeof(*parsed_t));
      parsed_t[num_temp] = *ptr;
      num_temp++;
      ptr++;
    }
    if (*ptr == '_') {
      parsed_t = replace_blank(parsed_t, num_temp, ptr, cats, used_word, flag);
      num_temp = strlen(parsed_t);
      ptr++;
    }
  }

  ptr = NULL;
  parsed_t = realloc(parsed_t, (num_temp + 1) * sizeof(*parsed_t));
  parsed_t[num_temp] = '\0';
  return parsed_t;
}

int check_name(char * name, catarray_t * cat) {
  if (cat->n == 0) {
    return 0;
  }
  else {
    for (size_t i = 0; i < cat->n; i++) {
      if (strcmp(cat->arr[i].name, name) == 0) {
        return 1;
      }
    }
    return 0;
  }
}

void add_name(char * name, char * word, catarray_t * cat) {
  cat->arr = realloc(cat->arr, (cat->n + 1) * sizeof(*cat->arr));
  cat->arr[cat->n].name = name;
  cat->arr[cat->n].n_words = 1;
  cat->arr[cat->n].words =
      realloc(cat->arr[cat->n].words,
              cat->arr[cat->n].n_words * sizeof(*(cat->arr[cat->n].words)));
  cat->arr[cat->n].words[cat->arr[cat->n].n_words - 1] = word;
  cat->n++;
}

void add_word(char * name, char * word, catarray_t * cat) {
  for (size_t i = 0; i < cat->n; i++) {
    if (strcmp(name, cat->arr[i].name) == 0) {
      for (size_t j = 0; j < cat->arr[i].n_words; j++) {
        if (strcmp(word, cat->arr[i].words[j]) == 0) {
          free(word);
          return;
        }
      }
      cat->arr[i].n_words++;
      cat->arr[i].words =
          realloc(cat->arr[i].words, cat->arr[i].n_words * sizeof(*cat->arr[i].words));
      cat->arr[i].words[cat->arr[i].n_words - 1] = word;
    }
  }
}

//for each line in file,add the information to the catarray * cat.
void add_cat(const char * line, catarray_t * cat) {
  //find the name and word in given line
  char * s = strchr(line, ':');
  char * newline = strchr(line, '\n');
  if (s == NULL || newline == NULL) {
    fprintf(stderr, "The format of input list file is wrong.\n");
    exit(EXIT_FAILURE);
  }

  size_t len_name = s - line;
  size_t len_word = newline - s - 1;

  char * name = malloc((len_name + 1) * sizeof(*name));
  char * word = malloc((len_word + 1) * sizeof(*word));

  strncpy(name, line, len_name);
  strncpy(word, s + 1, len_word);
  name[len_name] = '\0';
  name[len_word] = '\0';

  if (check_name(name, cat) == 0) {
    add_name(name, word, cat);
  }
  if (check_name(name, cat) == 1) {
    add_word(name, word, cat);
  }
  s = NULL;
  newline = NULL;
  name = NULL;
  word = NULL;
}

//read the list of name and word, return a catarray type.
catarray_t * read_list(char * file_name) {
  FILE * f = open_file(file_name);

  ssize_t len = 0;
  size_t sz;
  char * line;
  catarray_t * array_cat = malloc(sizeof(*array_cat));
  array_cat->n = 0;
  array_cat->arr = NULL;

  while ((len = getline(&line, &sz, f) >= 0)) {
    add_cat(line, array_cat);
    line = NULL;
  }
  free(line);

  if (fclose(f) != 0) {
    fprintf(stderr, "The input list file cannot close.\n");
    exit(EXIT_FAILURE);
  }
  return array_cat;
}

void free_cat(catarray_t * cat) {
  for (size_t i = 0; i < cat->n; i++) {
    for (size_t j = 0; j < cat->arr[i].n_words; j++) {
      free(cat->arr[i].words[j]);
    }
    free(cat->arr);
  }
  free(cat);
}

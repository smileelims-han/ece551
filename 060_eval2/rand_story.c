#include "rand_story.h"

//read the template file and return a char*
FILE * open_file(const char * file_name) {
  FILE * f = fopen(file_name, "r");
  if (f == NULL) {
    fprintf(stderr, "The input template file is empty.\n");
    exit(EXIT_FAILURE);
  }
  return f;
}

//read the template file
char * read_temp(FILE * f) {
  char * temp = NULL;
  int num_temp = 0;
  int c = 0;

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
  char * symbol = strchr(p + 1, '_');
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
    if (*p < 48 && *p > 57) {
      return 0;
    }
    if (*p == 48) {
      fprintf(stderr, "The number on blank should not be zero.\n");
      return EXIT_FAILURE;
    }
    p++;
  }
  return atoi(name);
}

//get the used words depends on the integer
char * get_used(category_t * used, int n_back) {
  if (used->n_words == 0) {
    fprintf(stderr, "There is no used work.\n");
    exit(EXIT_FAILURE);
  }

  char * replace_w = used->words[(used->n_words) - n_back];
  return replace_w;
}

//add the used word to category used
void add_to_used(category_t * used, char * word) {
  used->n_words++;
  size_t len_w = strlen(word);
  used->words = realloc(used->words, used->n_words * sizeof(*used->words));
  used->words[used->n_words - 1] =
      malloc((len_w + 1) * sizeof(*used->words[used->n_words - 1]));
  strcpy(used->words[used->n_words - 1], word);
}

//if not allowed reuse,takeoff the used word from cat
void * no_reused_cat(catarray_t * cat, char * name, char * word) {
  if (cat->n == 0) {
    fprintf(stderr, "There is no more category avaliable.\n");
    exit(EXIT_FAILURE);
  }
  catarray_t * new_cat = malloc(sizeof(*new_cat));
  new_cat->n = cat->n;
  new_cat->arr = malloc(new_cat->n * sizeof *(new_cat->arr));

  for (size_t i = 0; i < new_cat->n; i++) {
    new_cat->arr[i].name = strdup(cat->arr[i].name);
    new_cat->arr[i].n_words = 0;
    new_cat->arr[i].words = NULL;

    size_t new_count = 0;
    for (size_t j = 0; j < cat->arr[i].n_words; j++) {
      if (strcmp(cat->arr[i].name, name) == 0 &&
          strcmp(cat->arr[i].words[j], word) == 0) {
        continue;
      }
      else {
        new_cat->arr[i].words = realloc(
            new_cat->arr[i].words, (new_count + 1) * sizeof *(new_cat->arr[i].words));
        new_cat->arr[i].words[new_count] = strdup(cat->arr[i].words[j]);
        new_count++;
      }
    }
    new_cat->arr[i].n_words = new_count;
  }

  free_cat(cat);
  return new_cat;
}

//parsed the name from line
char * parse_name(char * start) {
  char * end = strchr(start + 1, '_');
  size_t len_blank = end - start - 1;
  char * cate_name = malloc((len_blank + 1) * sizeof(*cate_name));
  strncpy(cate_name, start + 1, len_blank);
  cate_name[len_blank] = '\0';
  return cate_name;
}

//check if the name in temp is in cata
int check_exist(char * name, catarray_t * cat) {
  for (size_t i = 0; i < cat->n; i++) {
    if (strcmp(name, cat->arr[i].name) == 0) {
      return 1;
    }
  }
  fprintf(stderr, "The name intemplate is not a name in list.\n");
  return (EXIT_FAILURE);
}

//find the replace words of the blank
char * find_replace(char * name, catarray_t * cat, category_t * used) {
  const char * replace_word = NULL;

  //if cat is null
  if (cat == NULL) {
    replace_word = chooseWord(name, cat);
    return (char *)replace_word;
  }

  //if name is an integer
  size_t i = check_int(name);
  if (i != 0) {
    if (i <= used->n_words) {
      replace_word = used->words[used->n_words - i];
      return (char *)replace_word;
    }
    else {
      fprintf(stderr, "There is no enough used words for use.\n");
      exit(EXIT_FAILURE);
    }
  }

  //if name is char,find a replace_word in cat, then if flag = 1, took off the word after
  if (i == 0 && check_exist(name, cat) == 1) {
    replace_word = chooseWord(name, cat);
    return ((char *)replace_word);
  }
  return NULL;
}

//find the replace word and put it into blank
void add_used(char * replace_word, category_t * used_word) {
  used_word->n_words++;
  used_word->words =
      realloc(used_word->words, (used_word->n_words) * sizeof(*used_word->words));
  used_word->words[used_word->n_words - 1] = strdup(replace_word);
}

//parse the readen template, return the parsed result
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
      parsed_t = realloc(parsed_t, (num_temp + 2) * sizeof(*parsed_t));
      parsed_t[num_temp] = *ptr;
      parsed_t[num_temp + 1] = '\0';
      num_temp++;
    }
    if (*ptr == '_') {
      if (check_underscore(ptr) == 0) {
        fprintf(stderr, "The blank format does not meet the requirement.");
        exit(EXIT_FAILURE);
      }

      char * list_name = parse_name(ptr);
      char * replace_word = find_replace(list_name, cats, used_word);
      add_used(replace_word, used_word);

      //replace the word in the string
      num_temp = num_temp + strlen(used_word->words[used_word->n_words - 1]);
      parsed_t = realloc(parsed_t, (num_temp + 1) * sizeof(*parsed_t));
      strcat(parsed_t, used_word->words[used_word->n_words - 1]);
      parsed_t[num_temp] = '\0';

      ptr = strchr(ptr + 1, '_');

      if (flag == 1 && cats != NULL) {
        cats = no_reused_cat(cats, list_name, replace_word);
      }
      free(list_name);
    }
    ptr++;
  }
  ptr = NULL;

  //free used_word category
  for (size_t i = 0; i < used_word->n_words; i++) {
    free(used_word->words[i]);
  }
  free(used_word->words);
  free(used_word);

  return parsed_t;
}

//check if the name exist in the cat
int check_name(char * name, catarray_t * cat) {
  if (cat->n == 0) {
    return 0;  //there is no category of this name add yet
  }
  else {
    for (size_t i = 0; i < cat->n; i++) {
      if (strcmp(cat->arr[i].name, name) == 0) {
        return 1;  //there is already the category of this name
      }
    }
  }
  return 0;
}

//add the name if not in the cat
void add_name(char * name, char * word, catarray_t * cat) {
  cat->arr = realloc(cat->arr, (cat->n + 1) * sizeof(*cat->arr));
  cat->arr[cat->n].name = name;
  cat->arr[cat->n].n_words = 1;
  cat->arr[cat->n].words = NULL;
  cat->arr[cat->n].words =
      realloc(cat->arr[cat->n].words,
              cat->arr[cat->n].n_words * sizeof(*(cat->arr[cat->n].words)));
  cat->arr[cat->n].words[cat->arr[cat->n].n_words - 1] = word;
  cat->n++;
}

//add the word to the category
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

//find the name before : in the line
char * find_name(char * line) {
  char * col = strchr(line, ':');
  if (col == NULL) {
    fprintf(stderr, "The format of list file is incorrect.\n");
    exit(EXIT_FAILURE);
  }
  int len_n = col - line;
  char * name = malloc((len_n + 1) * sizeof(*name));
  strncpy(name, line, len_n);
  name[len_n] = '\0';
  return name;
}

//find the word after : in the line
char * find_word(char * line) {
  char * col = strchr(line, ':');
  col++;
  char * newline = strchr(line, '\n');
  int len_w = newline - col;
  char * word = malloc((len_w + 1) * sizeof(*word));
  strncpy(word, col, len_w);
  word[len_w] = '\0';
  return word;
}

//read the list of name and word, return a catarray type.
catarray_t * read_list(FILE * f) {
  size_t sz = 0;
  char * line = NULL;
  catarray_t * array_cat = malloc(sizeof(*array_cat));
  array_cat->n = 0;
  array_cat->arr = NULL;

  while (getline(&line, &sz, f) >= 0) {
    char * name = find_name(line);
    char * word = find_word(line);
    int name_exist = check_name(name, array_cat);

    //if the name is not exist in category
    if (name_exist == 0) {
      add_name(name, word, array_cat);
    }
    if (name_exist == 1) {
      add_word(name, word, array_cat);
      free(name);
    }
    free(line);
    line = NULL;
    word = NULL;
  }
  free(line);

  if (fclose(f) != 0) {
    fprintf(stderr, "The input list file cannot close.\n");
    exit(EXIT_FAILURE);
  }
  return array_cat;
}

//free the catarray_t
void free_cat(catarray_t * cat) {
  if (cat != NULL) {
    for (size_t i = 0; i < cat->n; i++) {
      for (size_t j = 0; j < cat->arr[i].n_words; j++) {
        free(cat->arr[i].words[j]);
      }
      free(cat->arr[i].words);
      free(cat->arr[i].name);
    }
    free(cat->arr);
    free(cat);
  }
}

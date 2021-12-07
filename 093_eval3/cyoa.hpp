#include <cstdlib>
#include <exception>
#include <iostream>
#include <vector>

using namespace std;

class page {
 private:
  bool win;
  bool lose;
  vector<page> * choice;
  int num_choice;
  string context;

 public:
  page() : win(false), lose(false), choice(NULL), num_choice(0), context(""){};
  void parse_page(char * file_name) {
    FILE * f = fopen(file_name, "r");
    if (f == NULL) {
      cerr << "The page is empty.\n";
      exit(EXIT_FAILURE);
    }
  };

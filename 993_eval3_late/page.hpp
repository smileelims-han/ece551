#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class page {
 private:
  string context;

 public:
  bool win;
  bool lose;
  int page_num;

  class choice_info {
   public:
    int next_pnum;
    string choice_context;
    choice_info() : next_pnum(0){};
    choice_info(int num) : next_pnum(num){};
    ~choice_info(){};
  };

  vector<choice_info> choice;
  int num_choice;

  page() : win(false), lose(false), page_num(0), num_choice(0){};
  ~page(){};
  void parse_page(char * file_name);
  void add_page(vector<string> line_vec);
  void print_page();
};

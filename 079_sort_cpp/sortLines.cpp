#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void sort_input(std::istream & input) {
  std::vector<std::string> v;
  std::string s;

  while (getline(input, s)) {
    v.push_back(s);
  }

  if (!input.eof() && !input) {
    std::cerr << "can not read the file" << std::endl;
  }

  std::sort(v.begin(), v.end());

  std::vector<std::string>::iterator it = v.begin();
  while (it != v.end()) {
    std::cout << *it << std::endl;
    ++it;
  }
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    sort_input(std::cin);
  }
  if (argc >= 2) {
    for (int i = 1; i < argc; i++) {
      std::ifstream input_file(argv[i]);
      if (!input_file.is_open()) {
        std::cerr << "read fail." << std::endl;
        return EXIT_FAILURE;
      }
      sort_input(input_file);
    }
  }
  return EXIT_SUCCESS;
}

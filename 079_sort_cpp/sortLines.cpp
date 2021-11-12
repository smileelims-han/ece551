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
  if (!input.eof() && !input) {
    std::cout << "can not read the file" << std::endl;
  }

  while (getline(input, s)) {
    v.push_back(s);
  }
  sort(v.begin(), v.end());

  for (size_t i = 0; i < v.size(); i++) {
    std::cout << v[i] << std::endl;
  }
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    sort_input(std::cin);
  }
  if (argc >= 2) {
    for (int i = 0; i < argc; i++) {
      std::ifstream input_file;
      input_file.open(argv[i], std::ifstream::in);
      if (!input_file.is_open()) {
        std::cout << "read fail." << std::endl;
        return EXIT_FAILURE;
      }
      sort_input(input_file);
    }
  }
  return EXIT_SUCCESS;
}

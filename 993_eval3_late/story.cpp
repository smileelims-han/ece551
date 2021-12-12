#include "story.hpp"

#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <istream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void story::read_story(char * dirname) {
  //check if page1 exist
  string p1 = +dirname;
  p1.append("/page1.txt");
  char * p1_name = &p1[0];
  ifstream page1(p1_name);
  if (!page1) {
    cerr << "Cannot open the directory.\n";
    exit(EXIT_FAILURE);
  }

  //check all valid file in the directory
  string dir_name = +dirname;
  dir_name.append("/page");
  int i = 1;
  while (true) {
    ostringstream stream;
    stream << i;
    string is = stream.str();
    string file_name = dir_name + is + ".txt";
    char * file_name_char = &file_name[0];
    ifstream file(file_name_char);
    if (!file) {
      break;
    }
    else {
      page new_page;
      num_pages++;
      char * file_name_char = &file_name[0];
      new_page.parse_page(file_name_char);
      pages.push_back(new_page);
    }
    i++;
    if (i == INT_MAX) {
      cerr << "The num of pages exceed the INT_MAX in this computer.\n";
      exit(EXIT_FAILURE);
    }
  }

  win_lose();

  story_group();
  story_valid();
}

void story::win_lose() {
  int w = 0;
  int l = 0;
  for (size_t i = 0; i < num_pages; i++) {
    if (pages[i].win == true) {
      w++;
    }
    if (pages[i].lose == true) {
      l++;
    }
  }
  if (w == 0 || l == 0) {
    cerr << "A valid story should has at least one WIN and one LOSE.\n";
    exit(EXIT_FAILURE);
  }
}

bool story::find_1D(int f, vector<int> v) {
  for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
    if ((*it) == f) {
      return 1;
    }
  }
  return 0;
}

bool story::find_2D(int f, vector<vector<int> > s) {
  for (vector<vector<int> >::iterator it1 = s.begin(); it1 != s.end(); ++it1) {
    for (vector<int>::iterator it2 = (*it1).begin(); it2 != (*it1).end(); ++it2) {
      if ((*it2) == f) {
        return 1;
      }
    }
  }
  return 0;
}

void story::story_group() {
  while (visited.size() != num_pages) {
    for (size_t i = 1; i <= num_pages; i++) {
      if (find_1D(i, visited) == 0) {
        group.push_back(story_structure(i));
        num_groups++;
      }
    }
  }
}

story::structure story::story_structure(int n) {
  //adding first unvisited page num into a queue following the choice sequence
  queue<int> q;
  q.push(n);
  visited.push_back(n);
  structure cur_s;

  while (!q.empty()) {
    int cur_level = q.size();
    cur_s.s.push_back(vector<int>());
    cur_s.num_lev++;
    for (int i = 0; i < cur_level; i++) {
      int p = q.front();
      q.pop();
      cur_s.s.back().push_back(p);
      //iterate from the choice
      if (pages[p - 1].num_choice != 0) {
        for (size_t j = 0; j < pages[p - 1].num_choice; j++) {
          if (find_1D(pages[p - 1].choice[j].next_pnum, visited) == 0) {
            if (pages[p - 1].choice[j].next_pnum > num_pages) {
              cerr << "A choice point to an unkown page.\n";
              exit(EXIT_FAILURE);
            }
            q.push(pages[p - 1].choice[j].next_pnum);
            visited.push_back(pages[p - 1].choice[j].next_pnum);
          }
        }
      }
    }
  }
  return cur_s;
}

void story::story_valid() {
  int find = 0;
  for (size_t i = 1; i <= num_pages; i++) {
    //search in each group, if find the element,reset flag find
    //then go to find next page.
    for (size_t j = 0; j < num_groups; j++) {
      find += find_2D(i, group[j].s);
    }
    if (find == 0) {
      cerr << "There are certain pages do not have parent.\n";
      exit(EXIT_FAILURE);
    }
    find = 0;
  }
}

void story::play_story() {
  pages[0].print_page();
  size_t i = 0;
  while (true) {
    size_t user;
    cin >> user;
    if (user > pages[i].num_choice || user < 1) {
      cerr << "Please enter the valid choice number.\n";
      exit(EXIT_FAILURE);
    };
    size_t next_page = pages[i].choice[user - 1].next_pnum;
    pages[next_page - 1].print_page();
    if (pages[next_page - 1].win == true || pages[next_page - 1].lose == true) {
      exit(EXIT_SUCCESS);
    }
    i = next_page - 1;
  }
}
int story::find_depth(int n) {
  if (find_2D(n, group[0].s) == 0) {
    return -1;
  }

  int total_depth = group[0].num_lev;
  int depth;
  for (depth = 0; depth < total_depth; depth++) {
    if (find_1D(n, group[0].s[depth]) == 1) {
      return depth;
    }
  }
  return -1;
}

void story::depth_pages() {
  for (size_t i = 0; i < num_pages; i++) {
    int depth = find_depth(i + 1);
    if (depth != -1) {
      cout << "Page " << i + 1 << ":" << depth << endl;
    }
    if (depth == -1) {
      cout << "Page " << i + 1 << " is not reachable\n" << endl;
    }
  }
}

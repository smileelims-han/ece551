#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "il.hpp"

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList il;
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    // WRITE ME
    IntList il;
    assert(il.head == NULL && il.tail == NULL && il.getSize() == 0);
    // 3
    il.addFront(3);
    assert(il.find(3) == 0);
    assert(il.getSize() == 1 && il[0] == 3 && il.head->data == 3 && il.tail->data == 3 &&
           il.head != NULL && il.tail != NULL && il.head == il.tail &&
           il.head->next == NULL && il.head->prev == NULL && il.tail->next == NULL &&
           il.tail->prev == NULL);
    // 5 3
    il.addFront(5);
    assert(il.find(5) == 0 && il.find(3) == 1);
    assert(il.getSize() == 2 && il[0] == 5 && il[1] == 3 && il.head->prev == NULL &&
           il.head->next == il.tail && il.head->data == 5 && il.head->next->data == 3 &&
           il.tail->data == 3 && il.tail->next == NULL && il.tail->prev == il.head &&
           il.head->next->next == NULL && il.tail->prev->data == 5 &&
           il.tail->prev->prev == NULL && il.head->next->prev == il.head);
    // 7 5 3
    il.addFront(7);
    assert(il.find(7) == 0);
    assert(il.getSize() == 3 && il[0] == 7 && il[1] == 5 && il[2] == 3 &&
           il.head->data == 7 && il.head->prev == NULL &&
           il.head->next->next == il.tail && il.head->next->prev == il.head &&
           il.head->next->data == 5 && il.head->next->next->data == 3 &&
           il.tail->data == 3 && il.tail->prev == il.head->next &&
           il.tail->next == NULL && il.head->next->next->next == NULL &&
           il.tail->prev->data == 5 && il.tail->prev->prev->data == 7 &&
           il.tail->prev->prev->prev == NULL);
    il.addFront(9);
    il.addFront(11);
    il.addFront(13);
    // 13 11 9 7 5 3
    assert(il.getSize() == 6 && il[0] == 13 && il[1] == 11 && il[2] == 9 && il[3] == 7 &&
           il[4] == 5 && il[5] == 3);
  }
  // many more tester methods
  void testAddBack() {
    IntList il;
    assert(il.head == NULL && il.tail == NULL && il.getSize() == 0);
    il.addBack(7);
    //7
    assert(il[0] == 7 && il.getSize() == 1 && il.head->next == NULL &&
           il.head->prev == NULL && il.tail == il.head && il.tail != NULL &&
           il.head->data == 7 && il.tail->data == 7 && il.tail->prev == NULL &&
           il.tail->next == NULL && il.find(7) == 0);
    // 7 5
    il.addBack(5);
    assert(il.getSize() == 2 && il[0] == 7 && il[1] == 5 && il.head->prev == NULL &&
           il.head->next == il.tail && il.head->data == 7 && il.head->next->data == 5 &&
           il.tail->data == 5 && il.tail->next == NULL && il.tail->prev == il.head &&
           il.head->next->next == NULL && il.tail->prev->data == 7 &&
           il.tail->prev->prev == NULL);
    // 7 5 3
    il.addBack(3);
    assert(il.getSize() == 3 && il[0] == 7 && il[1] == 5 && il[2] == 3 &&
           il.head->data == 7 && il.head->prev == NULL &&
           il.head->next->next == il.tail && il.head->next->prev == il.head &&
           il.head->next->data == 5 && il.head->next->next->data == 3 &&
           il.tail->data == 3 && il.tail->prev == il.head->next &&
           il.tail->next == NULL && il.head->next->next->next == NULL &&
           il.tail->prev->data == 5 && il.tail->prev->prev->data == 7 &&
           il.tail->prev->prev->prev == NULL && il.tail->prev->prev == il.head &&
           il.head->next->prev == il.head);
  }
  void testRemove() {
    IntList il;
    il.remove(4);
    assert(il.head == NULL && il.tail == NULL && il.head == il.tail && il.getSize() == 0);
  }
};

int main(void) {
  Tester t;
  t.testDefCtor();
  t.testAddFront();
  // write calls to your other test methods here
  return EXIT_SUCCESS;
}

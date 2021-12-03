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
  void testall() {
    IntList il;
    assert(il.head == NULL && il.tail == NULL && il.getSize() == 0);
    /////////////////////////addBack
    il.addBack(7);
    //7
    assert(il.find(7) == 0);
    assert(il.getSize() == 1 && il[0] == 7 && il.head->data == 7 && il.tail->data == 7 &&
           il.head != NULL && il.tail != NULL && il.head == il.tail &&
           il.head->next == NULL && il.head->prev == NULL && il.tail->next == NULL &&
           il.tail->prev == NULL);
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

    il.addFront(9);
    il.addFront(11);
    // 11 9 7 5 3

    /////////////////////test remove
    il.remove(5);  // remove from mid
    // 11 9 7 3
    assert(il.remove(4) == 0);
    assert(il.getSize() == 4 && il.head->data == 11 && il.head->next->data == 9 &&
           il.head->next->next->data == 7 && il.head->next->next->next->data == 3 &&
           il.head->next->next->next->next == NULL && il.tail->data == 3 &&
           il.tail->prev->data == 7 && il.tail->prev->prev->data == 9 &&
           il.tail->prev->prev->prev->data == 11 &&
           il.tail->prev->prev->prev->prev == NULL && il.head->prev == NULL &&
           il.tail->next == NULL);
    assert(il.find(3) == 3);
    assert(il.find(11) == 0);

    il.remove(3);  //remove from end
                   // 11 9 7
    assert(il.getSize() == 3 && il[0] == 11 && il[1] == 9 && il[2] == 7 &&
           il.head->data == 11 && il.head->prev == NULL &&
           il.head->next->next == il.tail && il.head->next->prev == il.head &&
           il.head->next->data == 9 && il.head->next->next->data == 7 &&
           il.tail->data == 7 && il.tail->prev == il.head->next &&
           il.tail->next == NULL && il.head->next->next->next == NULL &&
           il.tail->prev->data == 9 && il.tail->prev->prev->data == 11 &&
           il.tail->prev->prev->prev == NULL && il.tail->prev->prev == il.head &&
           il.head->next->prev == il.head);
    assert(il.find(11) == 0 && il.find(9) == 1 && il.find(7) == 2);

    il.remove(11);  //remove from begin
                    // 9 7
    assert(il.getSize() == 2 && il[0] == 9 && il[1] == 7 && il.head->prev == NULL &&
           il.head->next == il.tail && il.head->data == 9 && il.head->next->data == 7 &&
           il.tail->data == 7 && il.tail->next == NULL && il.tail->prev == il.head &&
           il.head->next->next == NULL && il.tail->prev->data == 9 &&
           il.tail->prev->prev == NULL);
    assert(il.find(9) == 0 && il.find(7) == 1);

    //check addFront after remove
    il.remove(9);
    il.addFront(9);
    assert(il.getSize() == 2 && il[0] == 9 && il[1] == 7 && il.head->prev == NULL &&
           il.head->next == il.tail && il.head->data == 9 && il.head->next->data == 7 &&
           il.tail->data == 7 && il.tail->next == NULL && il.tail->prev == il.head &&
           il.head->next->next == NULL && il.tail->prev->data == 9 &&
           il.tail->prev->prev == NULL);
    assert(il.find(9) == 0 && il.find(7) == 1);
    //check addBack after remove
    il.remove(7);
    il.addBack(7);
    assert(il.getSize() == 2 && il[0] == 9 && il[1] == 7 && il.head->prev == NULL &&
           il.head->next == il.tail && il.head->data == 9 && il.head->next->data == 7 &&
           il.tail->data == 7 && il.tail->next == NULL && il.tail->prev == il.head &&
           il.head->next->next == NULL && il.tail->prev->data == 9 &&
           il.tail->prev->prev == NULL);
    assert(il.find(9) == 0 && il.find(7) == 1);

    //remove item is not in the list
    il.remove(4);
    assert(il.getSize() == 2 && il[0] == 9 && il[1] == 7 && il.head->prev == NULL &&
           il.head->next == il.tail && il.head->data == 9 && il.head->next->data == 7 &&
           il.tail->data == 7 && il.tail->next == NULL && il.tail->prev == il.head &&
           il.head->next->next == NULL && il.tail->prev->data == 9 &&
           il.tail->prev->prev == NULL);
    assert(il.find(9) == 0 && il.find(7) == 1);

    //remove to empty
    il.remove(9);
    il.remove(7);
    assert(il.head == NULL);
    assert(il.tail == NULL);
    assert(il.getSize() == 0);
    assert(il.head == il.tail);

    il.addFront(9);
    il.addBack(7);
    il.addFront(11);
    // addFront and addBack after remove
    assert(il.getSize() == 3 && il[0] == 11 && il[1] == 9 && il[2] == 7 &&
           il.head->data == 11 && il.head->prev == NULL &&
           il.head->next->next == il.tail && il.head->next->prev == il.head &&
           il.head->next->data == 9 && il.head->next->next->data == 7 &&
           il.tail->data == 7 && il.tail->prev == il.head->next &&
           il.tail->next == NULL && il.head->next->next->next == NULL &&
           il.tail->prev->data == 9 && il.tail->prev->prev->data == 11 &&
           il.tail->prev->prev->prev == NULL && il.tail->prev->prev == il.head &&
           il.head->next->prev == il.head);
    assert(il.find(11) == 0 && il.find(9) == 1 && il.find(7) == 2);

    ////////////////// copy and assign for testcase 10-16

    // il: 11 9 7
    // check copy , assign
    IntList il_copy1(il);
    assert(il_copy1.getSize() == 3 && il_copy1[0] == 11 && il_copy1[1] == 9 &&
           il_copy1[2] == 7 && il_copy1.head->data == 11 && il_copy1.head->prev == NULL &&
           il_copy1.head->next->next == il_copy1.tail &&
           il_copy1.head->next->prev == il_copy1.head && il_copy1.head->next->data == 9 &&
           il_copy1.head->next->next->data == 7 && il_copy1.tail->data == 7 &&
           il_copy1.tail->prev == il_copy1.head->next && il_copy1.tail->next == NULL &&
           il_copy1.head->next->next->next == NULL && il_copy1.tail->prev->data == 9 &&
           il_copy1.tail->prev->prev->data == 11 &&
           il_copy1.tail->prev->prev->prev == NULL &&
           il_copy1.tail->prev->prev == il_copy1.head &&
           il_copy1.head->next->prev == il_copy1.head);
    // check if it is a deep copy
    assert(il_copy1.head != il.head && il_copy1.tail != il.tail &&
           il_copy1.head->next != il.head->next &&
           il_copy1.head->next->next != il.head->next->next &&
           il_copy1.tail->prev != il.tail->prev);
    //check addFront / back / remove after copy
    il_copy1.remove(9);
    il_copy1.addBack(5);
    il_copy1.addFront(13);
    il_copy1.remove(11);
    //il_copy1 13 7 5
    assert(il_copy1.getSize() == 3 && il_copy1[0] == 13 && il_copy1[1] == 7 &&
           il_copy1[2] == 5 && il_copy1.head->data == 13 && il_copy1.head->prev == NULL &&
           il_copy1.head->next->next == il_copy1.tail &&
           il_copy1.head->next->prev == il_copy1.head && il_copy1.head->next->data == 7 &&
           il_copy1.head->next->next->data == 5 && il_copy1.tail->data == 5 &&
           il_copy1.tail->prev == il_copy1.head->next && il_copy1.tail->next == NULL &&
           il_copy1.head->next->next->next == NULL && il_copy1.tail->prev->data == 7 &&
           il_copy1.tail->prev->prev->data == 13 &&
           il_copy1.tail->prev->prev->prev == NULL &&
           il_copy1.tail->prev->prev == il_copy1.head &&
           il_copy1.head->next->prev == il_copy1.head);

    // check assign1
    IntList il_assign1 = il;
    assert(il_assign1.getSize() == 3 && il_assign1[0] == 11 && il_assign1[1] == 9 &&
           il_assign1[2] == 7 && il_assign1.head->data == 11 &&
           il_assign1.head->prev == NULL &&
           il_assign1.head->next->next == il_assign1.tail &&
           il_assign1.head->next->prev == il_assign1.head &&
           il_assign1.head->next->data == 9 && il_assign1.head->next->next->data == 7 &&
           il_assign1.tail->data == 7 && il_assign1.tail->prev == il_assign1.head->next &&
           il_assign1.tail->next == NULL && il_assign1.head->next->next->next == NULL &&
           il_assign1.tail->prev->data == 9 && il_assign1.tail->prev->prev->data == 11 &&
           il_assign1.tail->prev->prev->prev == NULL &&
           il_assign1.tail->prev->prev == il_assign1.head &&
           il_assign1.head->next->prev == il_assign1.head);
    //check if it is a deep assign?
    assert(il_assign1.head != il.head && il_assign1.tail != il.tail &&
           il_assign1.head->next != il.head->next &&
           il_assign1.head->next->next != il.head->next->next &&
           il_assign1.tail->prev != il.tail->prev);
    //il_assign1 11 9 7
    il_assign1.addFront(13);
    il_assign1.addBack(5);
    // 13 11 9 7 5
    il_assign1.remove(7);
    il_assign1.remove(11);
    // 13 9 5
    // check add front/back/remove after assign
    assert(il_assign1.getSize() == 3 && il_assign1[0] == 13 && il_assign1[1] == 9 &&
           il_assign1[2] == 5 && il_assign1.head->data == 13 &&
           il_assign1.head->prev == NULL &&
           il_assign1.head->next->next == il_assign1.tail &&
           il_assign1.head->next->prev == il_assign1.head &&
           il_assign1.head->next->data == 9 && il_assign1.head->next->next->data == 5 &&
           il_assign1.tail->data == 5 && il_assign1.tail->prev == il_assign1.head->next &&
           il_assign1.tail->next == NULL && il_assign1.head->next->next->next == NULL &&
           il_assign1.tail->prev->data == 9 && il_assign1.tail->prev->prev->data == 13 &&
           il_assign1.tail->prev->prev->prev == NULL &&
           il_assign1.tail->prev->prev == il_assign1.head &&
           il_assign1.head->next->prev == il_assign1.head);
    il_assign1 = il;
    assert(il_assign1.getSize() == 3 && il_assign1[0] == 11 && il_assign1[1] == 9 &&
           il_assign1[2] == 7 && il_assign1.head->data == 11 &&
           il_assign1.head->prev == NULL &&
           il_assign1.head->next->next == il_assign1.tail &&
           il_assign1.head->next->prev == il_assign1.head &&
           il_assign1.head->next->data == 9 && il_assign1.head->next->next->data == 7 &&
           il_assign1.tail->data == 7 && il_assign1.tail->prev == il_assign1.head->next &&
           il_assign1.tail->next == NULL && il_assign1.head->next->next->next == NULL &&
           il_assign1.tail->prev->data == 9 && il_assign1.tail->prev->prev->data == 11 &&
           il_assign1.tail->prev->prev->prev == NULL &&
           il_assign1.tail->prev->prev == il_assign1.head &&
           il_assign1.head->next->prev == il_assign1.head);
    //check if it is a deep assign?
    assert(il_assign1.head != il.head && il_assign1.tail != il.tail &&
           il_assign1.head->next != il.head->next &&
           il_assign1.head->next->next != il.head->next->next &&
           il_assign1.tail->prev != il.tail->prev);

    //check copy empty list
    IntList il_emp;
    IntList il_copy2(il_emp);
    assert(il_copy2.head == NULL);
    assert(il_copy2.tail == NULL);
    assert(il_copy2.getSize() == 0);
    assert(il_copy2.head == il_copy2.tail);

    //check assign emtpy list
    IntList il_assign2 = il_emp;
    assert(il_assign2.head == NULL);
    assert(il_assign2.tail == NULL);
    assert(il_assign2.getSize() == 0);
    assert(il_assign2.head == il_assign2.tail);

    //assign one item
    il_assign1[1] = 100;
    assert(il_assign1[1] = 100);
    assert(il_assign1.head->next->data =
               100 && il_assign1.getSize() == 3 && il_assign1.head->prev == NULL);

    //check deconstructor
    IntList * test_1 = new IntList();
    test_1->addFront(3);
    test_1->addBack(5);
    delete test_1;

    //empty list
    IntList * test_2 = new IntList();
    delete test_2;

    // copy-assign-delete
    IntList * test_3 = new IntList();
    IntList * test_4 = new IntList();

    test_3->addBack(3);
    test_3->addBack(5);
    // 3 5
    IntList * test_5 = new IntList(*test_3);
    *test_4 = *test_3;
    //check assign
    assert(test_4->getSize() == 2 && (*test_4)[0] == 3 && (*test_4)[1] == 5 &&
           test_4->head->prev == NULL && test_4->head->next == test_4->tail &&
           test_4->head->data == 3 && test_4->head->next->data == 5 &&
           test_4->tail->data == 5 && test_4->tail->next == NULL &&
           test_4->tail->prev == test_4->head && test_4->head->next->next == NULL &&
           test_4->tail->prev->data == 3 && test_4->tail->prev->prev == NULL);
    //check deep copy
    assert(test_4->head != test_3->head && test_4->tail != test_3->tail &&
           test_4->head->next != test_3->head->next &&
           test_4->tail->prev != test_3->tail->prev);
    //addFront/remove after assign
    test_4->remove(5);
    test_4->addFront(5);
    assert(test_4->getSize() == 2 && (*test_4)[0] == 5 && (*test_4)[1] == 3 &&
           test_4->head->prev == NULL && test_4->head->next == test_4->tail &&
           test_4->head->data == 5 && test_4->head->next->data == 3 &&
           test_4->tail->data == 3 && test_4->tail->next == NULL &&
           test_4->tail->prev == test_4->head && test_4->head->next->next == NULL &&
           test_4->tail->prev->data == 5 && test_4->tail->prev->prev == NULL);
    //check copy correcteness
    assert(test_5->getSize() == 2 && (*test_5)[0] == 3 && (*test_5)[1] == 5 &&
           test_5->head->prev == NULL && test_5->head->next == test_5->tail &&
           test_5->head->data == 3 && test_5->head->next->data == 5 &&
           test_5->tail->data == 5 && test_5->tail->next == NULL &&
           test_5->tail->prev == test_5->head && test_5->head->next->next == NULL &&
           test_5->tail->prev->data == 3 && test_5->tail->prev->prev == NULL);
    //check copy if deep copy
    assert(test_5->head != test_3->head && test_5->tail != test_3->tail &&
           test_5->head->next != test_3->head->next &&
           test_5->tail->prev != test_3->tail->prev);

    test_5->remove(5);
    test_5->addFront(5);
    assert(test_5->getSize() == 2 && (*test_5)[0] == 5 && (*test_5)[1] == 3 &&
           test_5->head->prev == NULL && test_5->head->next == test_5->tail &&
           test_5->head->data == 5 && test_5->head->next->data == 3 &&
           test_5->tail->data == 3 && test_5->tail->next == NULL &&
           test_5->tail->prev == test_5->head && test_5->head->next->next == NULL &&
           test_5->tail->prev->data == 5 && test_5->tail->prev->prev == NULL);

    delete test_3;
    delete test_4;
    delete test_5;

    /*il.remove(11);
    // 9 7
    //check addFront after copy
    IntList il_cy(il);
    il_cy.addFront(11);
    // il_cy : 11 9 7
    assert(il_cy.getSize() == 3 && il_cy[0] == 11 && il_cy[1] == 9 && il_cy[2] == 7 &&
           il_cy.head->data == 11 && il_cy.head->prev == NULL &&
           il_cy.head->next->next == il_cy.tail && il_cy.head->next->prev == il_cy.head &&
           il_cy.head->next->data == 9 && il_cy.head->next->next->data == 7 &&
           il_cy.tail->data == 7 && il_cy.tail->prev == il_cy.head->next &&
           il_cy.tail->next == NULL && il_cy.head->next->next->next == NULL &&
           il_cy.tail->prev->data == 9 && il_cy.tail->prev->prev->data == 11 &&
           il_cy.tail->prev->prev->prev == NULL && il_cy.tail->prev->prev == il_cy.head &&
           il_cy.head->next->prev == il_cy.head);

    IntList il_new;
    il_new.addBack(5);
    IntList il_cy_b(il_new);
    il_cy_b.addFront(7);
    il_cy_b.addBack(3);
    // il_cy_b :  7 5 3
    //check addBack after copy
    assert(il_cy_b.getSize() == 3 && il_cy_b[0] == 7 && il_cy_b[1] == 5 &&
           il_cy_b[2] == 3 && il_cy_b.head->data == 7 && il_cy_b.head->prev == NULL &&
           il_cy_b.head->next->next == il_cy_b.tail);
    assert(il_cy_b.head->next->prev == il_cy_b.head && il_cy_b.head->next->data == 5 &&
           il_cy_b.head->next->next->data == 3 && il_cy_b.tail->data == 3);
    assert(il_cy_b.tail->prev == il_cy_b.head->next && il_cy_b.tail->next == NULL &&
           il_cy_b.head->next->next->next == NULL && il_cy_b.tail->prev->data == 5 &&
           il_cy_b.tail->prev->prev->data == 7 &&
           il_cy_b.tail->prev->prev->prev == NULL &&
           il_cy_b.tail->prev->prev == il_cy_b.head &&
           il_cy_b.head->next->prev == il_cy_b.head);

    //check addFront after assign

    IntList il_ai;
    il_ai = il_new;
    il_ai.addFront(7);
    il_ai.addBack(3);
    assert(il_ai.getSize() == 3 && il_ai[0] == 7 && il_ai[1] == 5 && il_ai[2] == 3 &&
           il_ai.head->data == 7 && il_ai.head->prev == NULL &&
           il_ai.head->next->next == il_ai.tail && il_ai.head->next->prev == il_ai.head &&
           il_ai.head->next->data == 5 && il_ai.head->next->next->data == 3 &&
           il_ai.tail->data == 3 && il_ai.tail->prev == il_ai.head->next &&
           il_ai.tail->next == NULL && il_ai.head->next->next->next == NULL &&
           il_ai.tail->prev->data == 5 && il_ai.tail->prev->prev->data == 7 &&
           il_ai.tail->prev->prev->prev == NULL && il_ai.tail->prev->prev == il_ai.head &&
           il_ai.head->next->prev == il_ai.head);
    assert(il_ai.find(3) == 2 && il_ai.find(5) == 1 && il_ai.find(7) == 0);
    // test destructor
    // empty
    IntList test_de0;
    test_de0.~IntList();
    // test 1
    IntList test_de1;
    test_de1.addFront(1);
    test_de1.~IntList();
    //test 1 3 5 7
    IntList test_de2;
    test_de2.addFront(7);
    test_de2.addFront(5);
    test_de2.addFront(3);
    test_de2.addFront(1);
    test_de2.~IntList();
    */

    //test destructor
    //non-empty
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
  t.testall();

  return EXIT_SUCCESS;
}

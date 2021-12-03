#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>
#include <iostream>
//YOUR CODE GOES HERE
using namespace std;

class Error : public exception {
 public:
  virtual const char * what() const throw() { return "The input index is incorrect\n"; }
};

template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node() : next(NULL), prev(NULL){};
    Node(const T & a, Node * b, Node * c) : data(a), next(b), prev(c){};
  };

  Node * head;
  Node * tail;
  int size;

 public:
  //addFront
  void addFront(const T & data) {
    head = new Node(data, head, NULL);
    if (tail == NULL) {
      tail = head;
    }
    else {
      head->next->prev = head;
    }
    size++;
  }
  //addBack
  void addBack(const T & data) {
    tail = new Node(data, NULL, tail);
    if (head == NULL) {
      head = tail;
    }
    else {
      tail->prev->next = tail;
    }
    size++;
  }

  //bool remove
  bool remove(const T & data) {
    if (head == NULL) {
      return false;
    }
    Node * current = head;
    while (current != NULL) {
      if (current->data != data) {
        current = current->next;
      }
      else {
        if (head == tail) {
          delete current;
          head = NULL;
          tail = NULL;
          size = 0;
          return true;
        }
        if (current == head) {
          head = current->next;
          current->next->prev = NULL;
          delete current;
          size--;
          return true;
        }
        if (current == tail) {
          tail = current->prev;
          current->prev->next = NULL;
          delete current;
          size--;
          return true;
        }
        else {
          current->prev->next = current->next;
          current->next->prev = current->prev;
          delete current;
          size--;
          return true;
        }
      }
    }
    return false;
  }

  //index []
  T & operator[](int index) {
    Node * current = head;
    if (index < 0 || index > size) {
      throw Error();
    }
    for (int i = 0; i < index; i++) {
      current = current->next;
    }
    return current->data;
  }

  //index [] const
  const T & operator[](int index) const {
    Node * current = head;
    if (index < 0 || index > size) {
      throw Error();
    }
    for (int i = 0; i < index; i++) {
      current = current->next;
    }
    return current->data;
  }

  //find
  int find(const T & item) {
    if (head == NULL) {
      return -1;
    }
    Node * current = head;
    int index = 0;
    while (current != NULL) {
      if (current->data == item) {
        return index;
      }
      current = current->next;
      index++;
    }
    return -1;
  }

  //destructor
  ~LinkedList() {
    while (head != NULL) {
      Node * current = head->next;
      delete head;
      head = current;
    }
    head = NULL;
    tail = NULL;
    size = 0;
  }

  //assign
  LinkedList & operator=(const LinkedList & rhs) {
    if (this != &rhs) {
      LinkedList<T> temp(rhs);
      Node * current_head = head;
      Node * current_tail = tail;
      head = temp.head;
      tail = temp.tail;
      temp.head = current_head;
      temp.tail = current_tail;
      size = temp.size;
    }
    return *this;
  }

  //copy
  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(rhs.size) {
    Node * current = rhs.head;
    while (current != NULL) {
      addBack(current->data);
      current = current->next;
    }
  }

  //getSize
  int getSize() const { return size; }

  LinkedList() : head(NULL), tail(NULL), size(0){};
};
#endif

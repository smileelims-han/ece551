#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>
#include <iostream>
//YOUR CODE GOES HERE
using namespace std;

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
  bool remove(const T & data) {
    if (head == NULL) {
      return false;
    }
    Node * current = head;

    while (current != NULL && current->data != data) {
      current = current->next;
    }
    if (current == NULL) {
      return false;
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
  T & operator[](int index) {
    try {
      if (index > size || index < 0) {
        throw exception();
      }
      Node * current = head;
      for (int i = 0; i < index; i++) {
        current = current->next;
      }
      return current->data;
    }
    catch (exception & e) {
      cout << " the input index is incorret " << e.what() << "\n";
      exit(EXIT_FAILURE);
    }
  }
  T & operator[](int index) const {
    try {
      if (index > size || index < 0) {
        throw exception();
      }
      Node * current = head;
      for (int i = 0; i < index; i++) {
        current = current->next;
      }
      return current->data;
    }
    catch (exception & e) {
      cout << " the input index is incorret " << e.what() << "\n";
      exit(EXIT_FAILURE);
    }
  }
  int find(const T & item) {
    Node * current = head;
    int index = 0;
    while (current != NULL && current->data != item) {
      current = current->next;
      index++;
    }
    if (current != NULL) {
      return index;
    }
    return -1;
  }
  ~LinkedList() {
    Node * current = head;
    while (head != NULL) {
      current = current->next;
      delete head;
      head = current;
    }
    tail = NULL;
    size = 0;
  }
  T & operator=(const LinkedList & rhs) {
    if (this != rhs) {
      LinkedList<T> temp(rhs);
      while (head != NULL) {
        Node * current = head->next;
        delete head;
        head = temp;
      }
      head = temp.head;
      tail = temp.tail;
      size = temp.size;
      temp.head = NULL;
      temp.tail = NULL;
      temp.size = 0;
    }
    return *this;
  }
  LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL), size(rhs.getSize()) {
    Node * current = rhs.head;
    while (current != NULL) {
      addBack(current->data);
      current = current->next;
    }
  }

  int getSize() const { return size; }

  LinkedList() : head(NULL), tail(NULL), size(0){};
};
#endif

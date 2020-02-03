/*
 * Name: Ben Joye
 * Date Submitted: 9.7.18
 * Lab Section: 3
 * Assignment Name: Lab 02
 */

#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <string>
#include "Node.h"
using namespace std;

//This class represents a linked list of node objects
//that are sorted in descending order.
//Do not modify anything in the class interface
template <class T>
class List{

 private:
  Node<T> * start; //pointer to the first node in this list
  Node<T> * end;   //pointer to the last node in this list
  int mySize;  //size (or length) of this list

 public:
  List();
  ~List();
  int size();
  bool empty();
  void insert(T);
  bool contains(T);
  //Print the name and this list's size and values to stdout
  //This function is already implemented (no need to change it)
  void print(string name){
    cout << name << ": ";
    cout << "size = " << size();
    cout << ", values = ";
    Node<T> * iterator = start;
    while(iterator != NULL){
      cout << iterator->value << ' ';
      iterator = iterator->next;
    }
    cout << endl;
  }

}; //end of class interface (you may modify the code below)

//Implement all of the functions below

//Construct an empty list by initializig this list's instance variables
template <class T>
List<T>::List(){
  mySize = 0;
  start = NULL;
  end = NULL;
}

//Destroy all nodes in this list to prevent memory leaks
template <class T>
List<T>::~List(){
  Node<T> * iterator;
  while (start != NULL) {
    iterator = start;
    start = iterator->next;
    delete iterator;
  }
}

//Return the size of this list
template <class T>
int List<T>::size(){
  return mySize;
}

//Return true if this list is empty
//Otherwise, return false
template <class T>
bool List<T>::empty() {
  if (mySize == 0) {
    return true;
  } else {
    return false;
  }
}

//Create a new node with value, and insert that new node
//into this list in its correct position such that
//the values of the nodes in this list are sorted in descending order
template <class T>
void List<T>::insert(T value){

  // allocate memory for the new node
  Node<T> * newNode = new Node<T>(value);

  // if the list is not empty
  if (start != NULL) {

    // start the iterator at the beginning of the list
    Node<T> * current = start;

    // if the value being added is larger than the first value, then just add it to the beginning of the list
    if (newNode->value > current->value) {
      newNode->next = start;
      start = newNode;
    } else {
      // index keeps track of where in the linked list you are
      int index = 0;
      // this loop moves the current pointer to the spot in front of where the new node is being added
      while ((current->next != NULL) && (newNode->value < current->next->value)) {
        current = current->next;
        index++;
      }

      // if there is one node in the list, add it this way
      if (start == end && index == 0) {
        newNode->next = current->next;
        current->next = newNode;
        end = newNode;
      // else, if the node is being added to the end of the list
      } else if (current->next == NULL) {
        current->next = newNode;
        end = newNode;
        end = end->next;
      // if the node is being added somewhere in the middle of the list
      } else {
        newNode->next = current->next;
        current->next = newNode;
      }
    }
  // if the list is empty, add the node
  } else {
      start = newNode;
      end = newNode;
      newNode->next = NULL;
  }
  //increment the size of the list
  mySize++;
}


//Return true if this list contains a node whose value is equal to the key
//Otherwise, return false
template <class T>
bool List<T>::contains(T key){

  Node<T> * current = start;
  while (current != NULL) {
    if (key == current->value) {
      return true;
    }
    current = current->next;
  }
  return false;
}

#endif

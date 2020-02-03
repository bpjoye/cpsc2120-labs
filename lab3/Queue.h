/*
 * Name: Ben Joye
 * Date Submitted: 9/10/18
 * Lab Section: 3
 * Assignment Name: Lab 3
 */

#pragma once

#include <list>
using namespace std;

//This class represents a queue of objects
//Do not modify anything in the class interface
template <class T>
class Queue{

private:
    list<T> data; //stores all of the objects that were added to the queue

public:
    explicit Queue();
    ~Queue();
    bool empty() const;
    const int size() const;
    const T& front() const;
    void push(T value);
    void pop();
    void enqueue(T value);
    void dequeue();
    void print() const;
}; //end of class interface (you may modify the code below)

//Implement all of the functions below

//construct an empty queue
template <class T>
Queue<T>::Queue(){
  // call to the list constructor
  data = list<T>();
}

//deallocate memory properly to prevent memory leaks
template <class T>
Queue<T>::~Queue(){
  // clear the memory in the list
  data.clear();
}

//return true if the queue is empty; otherwise, return false
template <class T>
bool Queue<T>::empty() const{
  // list.empty() returns if the list is empty
  if (data.empty()) {
    return true;
  }
  return false;
}

//return the size of the queue
template <class T>
const int Queue<T>::size() const{
  // gets the size of the data list
  return data.size();
}

//return a reference to the element at the front of the queue
//(note: this function will only be called when the queue is not empty)
template <class T>
const T& Queue<T>::front() const{
  // returns the address of the front of the list
  return data.front();
}

//add the value to the back of the queue
template <class T>
void Queue<T>::push(T value){
  // push_back adds the value to the list
  data.push_back(value);
}

//remove the element at the front of the queue
//(note: this function will only be called when the queue is not empty)
template <class T>
void Queue<T>::pop(){
  // pop_front removes the first value
  data.pop_front();
}

//same functionality as push
//(note: in many algorithm textbooks, enqueue and push are synonymous operations for queues)
template <class T>
void Queue<T>::enqueue(T value){
  // same as push()
  data.push_back(value);
}

//same functionality as pop
//(note: in many algorithm textbooks, dequeue and pop are synonymous operations for queues)
template <class T>
void Queue<T>::dequeue(){
  // same as pop
  data.pop_front();
}

//print out the queue
//do not edit this function
template <class T>
void Queue<T>::print() const{
    Queue<T> queue = *this;
    cout << "(front) ";
    while(!queue.empty()){
        cout << queue.front() << " ";
        queue.pop();
    }
    cout << "(back)" << endl;
}

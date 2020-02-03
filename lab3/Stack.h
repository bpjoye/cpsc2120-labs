/*
 * Name: Ben Joye
 * Date Submitted: 9/10/18
 * Lab Section: 3
 * Assignment Name: Lab 3
 */


#pragma once

#include <vector>
using namespace std;

//This class represents a stack of objects
//Do not modify anything in the class interface
template <class T>
class Stack{

private:
    vector<T> data; //stores all of the objects that were added to the stack

public:
    explicit Stack();
    ~Stack();
    bool empty() const;
    const int size() const;
    const T& top() const;
    void push(T value);
    void pop();
    void print() const;
}; //end of class interface (you may modify the code below)

//Implement all of the functions below

//construct an empty stack
template <class T>
Stack<T>::Stack(){
  // calls the vector constructor
  data = vector<T>();
}

//deallocate memory properly to prevent memory leaks
template <class T>
Stack<T>::~Stack(){
  // clears the memory of the vector
  data.clear();
}


//Return true if this list is empty
//Otherwise, return false
template <class T>
bool Stack<T>::empty() const{
  // checks if the vector is empty
  if (data.empty()) {
    return true;
  }
  return false;
}

//return a reference to the element at the top of the stack
//(note: this function will only be called when this stack is not empty)
template <class T>
const T& Stack<T>::top() const{
  // returns the address of the last value
  return data.back();
}

//add the value to the top of the stack
template <class T>
void Stack<T>::push(T value){
  // adds value to the top
  data.push_back(value);
}

//remove the element at the top of the stack
//(note: this function will only be called when the stack is not empty)
template <class T>
void Stack<T>::pop(){
  // removes the last value
  data.pop_back();
}

//return the size of this stack
template <class T>
const int Stack<T>::size() const{
  // gets the current size of the vector
  return data.size();
}

//print out the stack
//do not edit this function
template <class T>
void Stack<T>::print() const{
    Stack<T> stack = *this;
    cout << "(top) ";
    while(!stack.empty()){
        cout << stack.top() << " ";
        stack.pop();
    }
    cout << "(bottom)" << endl;
}

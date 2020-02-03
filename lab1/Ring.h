/*
 * Name: Ben Joye
 * Date Submitted: 8/28/19
 * Lab Section: 3
 * Assignment Name: Lab 01
 *
 */

#ifndef RING_H
#define RING_H

#include <iostream>
using namespace std;

/*
 * This class represents a ring (circular) data structure.
 * Do not modify anything in the Ring class definition (its interface).
 * You will implement the functions after the class definition.
 */
template <class T>
class Ring{

 private:
  // Size of this ring
  int mySize;
  // Index to use for the add function
  int addIndex;
  // A pointer to the data (an array of T objects) stored by this ring
  T * data;

 public:
  /*
   * Constructor that initializes mySize to initialSize,
   * addIndex to 0, and data to a new T array.  The
   * size of data should be equal to mySize.
   * The default of initialSize is 0.
   */
  explicit Ring(int initialSize = 0);

  /*
   * Destructor that uses the deallocates memory properly to ensure
   * that a memory leak will not occur with this object.
   */
  ~Ring();

  /*
   * Return the T object at the specified index mod mySize in this ring.
   * Assume index >= 0.  This function should always works when index >= 0.
   */
  const T & operator[](int index);

  /*
   * Places obj in the addIndex of data (adds obj to the ring),
   * and updates addIndex appropriately.  addIndex should be incremented
   * by one each time an obj is added to this ring.
   * When addIndex exceeds the last index of data, then addIndex
   * should be set to 0.
   */
  void add(T obj);

  /*
   *  Return the size of this ring.
   */
  int size();

  /*
   * Print to standard output, the contents
   * of this ring.
   */
  void print();

};// end of Ring class definition (it's interface)

//You can modify the code below to implement the functions in this class




// Implement the constructor below
// You must use the new operator in your implementation
template <class T>
Ring<T>::Ring(int initialSize) {

  // initialize class variables
  mySize = initialSize;
  addIndex = 0;
  // dynamically allocate a array of T with size mySize, assign data pointer to this array
  data = new T[mySize];
}

// Implement the destructor below so there will be no
// memory leaks associated with this Ring object
template <class T>
Ring<T>::~Ring() {
  // delete the dynamically allocated memory in the data pointer
  delete [] data;
}

// Implement the function below
template <class T>
const T & Ring<T>::operator[](int index) {
  //mod index by mySize incase it is greater than the size of the array, return the object at that spot
  return data[index % mySize];
}

// Implement the function below
template <class T>
void Ring<T>::add(T obj) {
//check if the index is past the bounds, if so, set it back to zero
  if (addIndex >= mySize) {
    addIndex = 0;
  }
//add the object passed to the function to data at the current index
  data[addIndex] = obj;
  //increment addIndex so next data item will go after this one
  addIndex++;
}

// Implement the function below
template <class T>
int Ring<T>::size() {
  // get mySize and return it
  return this->mySize;
}

//This function is already implemented (do not modify)
template <class T>
void Ring<T>::print() {
  for(int i = 0; i < mySize; i++) {
    cout << data[i] << endl;
  }
}

#endif

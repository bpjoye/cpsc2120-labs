/*
 * Name: Ben Joye
 * Date Submitted: 8/28/19
 * Lab Section: 3
 * Assignment Name: Lab 01
 *
 */

#include <iostream>
#include "Ring.h"
using namespace std;

//Tests the Ring class
int main(void){
  cout << "Test 1 - An empty ring of doubles\n";
  Ring<double> r1;
  cout << "r1's size is " << r1.size() << endl << endl;

  cout << "Test 2 - A ring that can hold 5 integers\n";
  Ring<int> r2(5);
  cout << "Adding 0,1,2,3,4 to the ring\n";
  for(int i = 0; i < 5; i++){
    r2.add(i);
  }
  r2.print();
  cout << "Add 6 and 7 to the ring,\n";
  cout << "and they will replace the first two elements of the ring.\n";
  cout << "Also, the ring still contains the last three items\n";
  r2.add(6);
  r2.add(7);
  r2.print();
  cout << endl;

  cout << "Test 3 - A ring that can hold a playlist of 3 songs (as strings) \n";
  Ring<string> r3(3);
  cout << "Adding 3 songs to the ring\n";
  r3.add("Roar");
  r3.add("Happy");
  r3.add("Eye of the Tiger");
  r3.print();
  cout << "Playlist is full, and two new songs are added\n";
  r3.add("Lucy in the sky with diamonds");
  r3.add("Hello");
  r3.print();
  cout << "r3[13] = " << r3[13] << endl;
  cout << endl;

  cout << "Test 4 - A ring that can hold 6 integers \n";
  Ring<int> * r4 = new Ring<int>(6);
  cout << "Adding 0,1,2,...,15 to the ring\n";
  for(int i = 0; i <= 15; i++) {
    r4->add(i);
  }
  r4->print();

  delete r4;  //Why should we delete r4, but not r1, r2, or r3?

  cout << endl << "custom test cases:" << endl << endl;

  Ring<char> r5(4);
  cout << "Adding 4 characters to the ring" << endl;
  r5.add('t');
  r5.add('e');
  r5.add('s');
  r5.add('t');
  r5.print();
  cout << "ring is full, adding 'b' 'e' and 'a'" << endl;
  r5.add('b');
  r5.add('e');
  r5.add('a');
  r5.print();

  cout << endl;

  Ring<string> r6(3);
  cout << "Adding 3 to do items to the ring" << endl;
  r6.add("Do the dishes");
  r6.add("Do the laundry");
  r6.add("Walk the dog");
  r6.print();
  cout << "adding two new tasks" << endl;
  r6.add("Go to the grocery store");
  r6.print();

  cout << endl;

  Ring<int> r7(4);
  cout << "adding temperatures for the past 4 days" << endl;
  r7.add(80);
  r7.add(75);
  r7.add(76);
  r7.add(78);
  r7.print();
  cout << "adding the temperatures of the past 2 days, 82 and 81" << endl;
  r7.add(82);
  r7.add(81);
  r7.print();
  cout << endl;


  return 0;
}

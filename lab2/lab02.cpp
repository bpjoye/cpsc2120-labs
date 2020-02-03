/*
 * Name: Ben Joye
 * Date Submitted: 9.7.18
 * Lab Section: 3
 * Assignment Name: Lab 02
 */

#include <iostream>
#include <string>
#include "List.h"
#include "Node.h"
using namespace std;

//Tests the functions in List.h
int main(){

  List<int> list1;
  list1.print("list1");
  for(int i = 1, j = 1; i <= 10; i++){
    j = -2 * j;
    list1.insert(j);
    list1.print("list1");
  }

  cout << endl;

  List<string> list2;
  string s[] = {"Sisko", "Janeway", "Picard", "Kirk", "Zoey", "Frodo"};
  for(int i = 0; i < 6; i++) {
    list2.insert(s[i]);
    list2.print("list2");
  }
  if(!list2.contains("Worf")){
    cout << "Worf is not in list2 :(" << endl;
  }

  cout << endl;

  List<char> list3;
  char c[] = {'z', 'p', 'r', 'p', 'd', 'a', 'h', 'q', 'o'};
  for(int i = 0; i < 9; i++){
    list3.insert(c[i]);
    list3.print("list3");
  }
  if(list3.contains('r')){
    cout << "r is in list3" << endl;
  }

  List<int> list4;
  int intArray[] = {1,2,3,4,5,6,7,8,9,10};
  for (int i = 0; i < 10; i++) {
    list4.insert(intArray[i]);
    list4.print("list4");
  }

  List<string> list5;
  string stringArray[] = {"Jake", "Jack", "Jake","Adam", "Ashley"};
  for (int i = 0; i < 5; i++) {
    list5.insert(stringArray[i]);
    list5.print("list5");
  }
  if(list5.contains("Jake")){
    cout << "Jake is in list5" << endl;
  }

  List<char> list6;
  char c2[] = {'b','e','n','j','a','m','i','n'};
  for(int i = 0; i < 8; i++){
    list6.insert(c2[i]);
    list6.print("list6");
  }
  if(list6.contains('b')){
    cout << "b is in list6" << endl;
  }

  return 0;
}

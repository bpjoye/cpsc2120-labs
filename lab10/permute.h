/*
 * Name: Ben Joye
 * Date Submitted: 11/9/18
 * Lab Section: 3
 * Assignment Name: Lab 10
 */

#pragma once

#include <string>
#include <algorithm>
#include <random>
#include <cstdlib>
#include <ctime>

using namespace std;

// function to print the vector passed to it
void print(vector<string> v) {
  int s = v.size();
  for (int i = 0; i < s; i++) {
    cout << v[i] << " ";
  }
  cout << endl;
}

class permute {
private:
  vector<string> data;
  // vectors to hold the different random orders
  vector<string> p1;
  vector<string> p2;
  vector<string> p3;
  int n;

public:
  permute(vector<string> data);
  void print_permutation();
  void randomize();
};

permute::permute(vector<string> d) {
  data = d;
  n = 1;
  p1 = data;
  p2 = data;
  p3 = data;
  randomize();
}

void permute::randomize() {

  // generate random seed
  srand(time(NULL));

  // get random number from 1 to 50
  int r = (rand()%50) + 1;
  // get the next permutation of the vector that amount of times
  for (int i = 0; i < r; i++) {
    next_permutation(p1.begin(),p1.end());
  }

  // random shuffle function in algorithms library
  random_shuffle(p2.begin(),p2.end());

  int s3 = p3.size();
  // loop through each element of the vector
  for (int i = 0; i < s3; i++) {
    r = (rand()%s3);
    // swap it with random element
    iter_swap(p3.begin()+i, p3.begin()+r);
  }
}

// prints all the different vectors 
void permute::print_permutation() {
  if (n == 1)
    print(p1);
  if (n == 2)
    print(p2);
  if (n == 3)
    print(p3);
  n++;
}

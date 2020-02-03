/*
 * Name: Ben Joye
 * Date Submitted: 10/9/18
 * Lab Section: 003
 * Assignment Name: Lab 7
 */
#pragma once

using namespace std;

class memoization {
private:
    int run_recursion_version(int number);
    int run_memoization_version(int number);
public:
    int calculate_fibonacci_value(int number);
};

int memoization::calculate_fibonacci_value(int number) {
    int recursionAnswer = run_recursion_version(number);
    int memoizationAnswer = run_memoization_version(number);
    if(recursionAnswer == memoizationAnswer)
        return recursionAnswer;

    return -1;
}

int memoization::run_recursion_version(int number) {

  // base case
  if (number <= 1)
    return number;
  // call itself on the previous two numbers
  return run_recursion_version(number-1) + run_recursion_version(number-2);
}

int memoization::run_memoization_version(int number) {

  // array to store the previous two values
  int values[2] = {0,1};
  int total = 0;
  if (number == 1)
    return 1;

    // loop from 1 to the number
  for (int i = 1; i < number; i++) {
    // sum the two values in the array
    total = values[0] + values[1];
    // move the second element to the first spot
    values[0] = values[1];
    // set the second element to the total that was just calculated
    values[1] = total;
  }
  // return the total
  return total;
}

/*
 * Name: Ben Joye
 * Date Submitted: 10/9/18
 * Lab Section: 003
 * Assignment Name: Lab 7
 */
#pragma once
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

class integration{
private:
    vector<pair<double, double>> eq;
public:
    integration(vector<pair<double,double>>& equation);
    double perform_integration(double lowerBound, double upperBound);
    double yOf(double x);
};

integration::integration(vector<pair<double,double>>& equation) {
  eq = equation;
}

double integration::perform_integration(double lowerBound, double upperBound) {

  // initial step size is the distance between the lower and upper bound
  double stepSize = upperBound - lowerBound;
  // mid point is the average of lower and upper bounds
  double midPoint = (upperBound+lowerBound)/2;
  // integration formula
  double integration = stepSize * yOf(midPoint);
  // placeholder value to get while loop through at least one loop
  double prev = integration + 1;
  bool found = false;

  while (!found) {

    // half the step size each loop
    stepSize = stepSize / 2;
    // reset the integration value each loop
    integration = 0.0;

    // loop through each section of size stepSize in the bounds
    for (double i = lowerBound; i < upperBound; i = i+stepSize) {
      // calculate the midpoint for each segment
      midPoint = (i+(i+stepSize))/2;
      // integrate at each midpoint
      integration += stepSize * yOf(midPoint);
    }
    // if the difference between the previous integration and current integration is less than 0.0001, end the loop
    if (abs(integration-prev) < 0.0001) {
      found = true;
    }
    // set prev to the integration
    prev = integration;
  }

  // round the value to 4 decimal places
  double value = (int)(integration * 10000 + 0.5);
  return (double)value / 10000;
}

// function to calculate the y value of any x for the function given
double integration::yOf(double x) {
  int size = eq.size();
  double value = 0;
  for (int i = 0; i < size; i++) {
    value += eq[i].first * pow(x,eq[i].second);
  }
  return value;
}

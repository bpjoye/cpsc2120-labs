/*
 * Name: Ben Joye
 * Date Submitted: 10/16/18
 * Lab Section: 003
 * Assignment Name: Lab 8
 */

#pragma once

#include <functional>
#include <cfloat>
#include <random>
#include <ctime>
#include <chrono>
#include <cmath>

using namespace std;

class optimizers{
public:
    struct minimum_value{
        double value;
        double x;
        double y;
        minimum_value(double value, double x, double y):
            value(value), x(x), y(y){}
    };

    optimizers(function<double(double,double)> func,double xMin, double xMax, double yMin, double yMax);
    minimum_value greedy();
    minimum_value greedy_annealing(minimum_value);
    minimum_value simulated_annealing();
private:
    function<double(double,double)> func;
    double xMin, xMax, yMin, yMax;
    double round_number(double number);
    double random_double(double min, double max);
    double get_temperature(double time);
};

optimizers::optimizers(function<double(double,double)> func, double xMin, double xMax, double yMin, double yMax):
    func(func),xMin(xMin),xMax(xMax),yMin(yMin),yMax(yMax)
{

}

//find the lowest point in a graph using a greedy algorithm
optimizers::minimum_value optimizers::greedy(){

  // run a max of 1000 times
  int maxLoopCount = 1000;
  // set the globalMinimum to a very high value at the start
  minimum_value globalMinimum(DBL_MAX,DBL_MAX,DBL_MAX);
  double stepSize = 0.5;
  double calculatedValue;

  // loop 1000 times
  for (int i = 0; i < maxLoopCount; i++) {

    // generate random x and y values to start at
    double xI = random_double(xMin,xMax);
    double yI = random_double(yMin,yMax);
    minimum_value localMinimum = globalMinimum;
    minimum_value currentValue = globalMinimum;

    while (true) {

      // two loops to check all neighboring values
      for (int x = xI - stepSize; x <= xI + stepSize; x += 2*stepSize) {
        for (int y = yI - stepSize; y <= yI + stepSize; y += 2*stepSize) {
          // check if the neighbor is in bounds
          if (x < xMax && x > xMin && y < yMax && y > yMin) {
            // calculate the z value at the neighbor
            calculatedValue = func(x,y);
            // if that value is smaller than the initial value
            if (calculatedValue < currentValue.value) {
              // set the initial value to the new value
              currentValue.value = calculatedValue;
              currentValue.x = x;
              currentValue.y = y;
            }
          }
        }
      }
      // if the smallest neighbor is smaller than the local minimum, change the local min
      if (currentValue.value < localMinimum.value) {
        localMinimum = currentValue;
      }
      // if the local min is equal to the current min, end the loop
      if (localMinimum.value == currentValue.value) {
        break;
      }
    }
    // if the local min is smaller than the global min, change the global min
    if (localMinimum.value < globalMinimum.value) {
      globalMinimum = localMinimum;
    }
  }

  // round all the values
  globalMinimum.x = round_number(globalMinimum.x);
  globalMinimum.y = round_number(globalMinimum.y);
  globalMinimum.value = round_number(globalMinimum.value);
  return globalMinimum;
}

//find the lowest point in a graph using a simulated annealing algorithm
optimizers::minimum_value optimizers::simulated_annealing(){

  // generate random x and y inital values
  double xI = random_double(xMin,xMax);
  double yI = random_double(yMin,yMax);
  double newX, newY;
  // calculate the value at this point
  minimum_value currentLocation(func(xI,yI),xI,yI);
  minimum_value bestValue = currentLocation;
  minimum_value calculatedValue = currentLocation;
  double t = 0.0;
  // loop while temperature is > 0
  while (get_temperature(t) > 0) {
    // generate a random neighbor
    newX = currentLocation.x + random_double(-2,2);
    newY = currentLocation.y + random_double(-2,2);
    // check if the neighbor is in bounds
    if (newX < xMax && newX > xMin && newY < yMax && newY > yMin) {
      // store the neighbors values
      calculatedValue.x = newX;
      calculatedValue.y = newY;
      calculatedValue.value = func(newX,newY);
      // if it is smaller than the best value, change best value
      if (calculatedValue.value < bestValue.value) {
        bestValue = calculatedValue;
      }
      // generate P
      double P = pow(2.718,(currentLocation.value-calculatedValue.value)/t);
      // sometimes executes, depending on p
      if (P > random_double(0,1)) {
        // move the current location to the best value
        currentLocation = bestValue;
      }
      t += 0.01;
    }

  }

  // run greedy algorithm on the value in case it isn't all the way at the min yet
  return greedy_annealing(bestValue);

}

optimizers::minimum_value optimizers::greedy_annealing(minimum_value min) {

  // exact same as greedy(), just can take in a minimum value to start
  int maxLoopCount = 1000;
  minimum_value globalMinimum = min;
  double stepSize = 0.5;
  double calculatedValue;

  for (int i = 0; i < maxLoopCount; i++) {

    double xI = random_double(xMin,xMax);
    double yI = random_double(yMin,yMax);
    minimum_value localMinimum = globalMinimum;
    minimum_value currentValue = globalMinimum;

    while (true) {

      for (int x = xI - stepSize; x <= xI + stepSize; x += 2*stepSize) {
        for (int y = yI - stepSize; y <= yI + stepSize; y += 2*stepSize) {
          if (x < xMax && x > xMin && y < yMax && y > yMin) {
            calculatedValue = func(x,y);
            if (calculatedValue < currentValue.value) {
              currentValue.value = calculatedValue;
              currentValue.x = x;
              currentValue.y = y;
            }
          }
        }
      }

      if (currentValue.value < localMinimum.value) {
        localMinimum = currentValue;
      }
      if (localMinimum.value == currentValue.value) {
        break;
      }
    }

    if (localMinimum.value < globalMinimum.value) {
      globalMinimum = localMinimum;
    }
  }

  globalMinimum.x = round_number(globalMinimum.x);
  globalMinimum.y = round_number(globalMinimum.y);
  globalMinimum.value = round_number(globalMinimum.value);
  return globalMinimum;

}



//this is a function that returns a temperature based on how much time has gone by,
//the temperature gradually approches 0 over time
double optimizers::get_temperature(double time){
    static double initialTemp = 100;
    static double airTemp = 0;
    static double rate = 0.025;
    static double constValue = initialTemp - airTemp;
    double s = constValue * exp(-1*time*rate);
    double temperature = s + airTemp;
    return temperature;
}

//rounds a number to two decimal places
double optimizers::round_number(double number){
    static double scale = 0.01;
    return floor(number/scale + 0.5) * scale;
}

//returns a random double between the two values (inclusive)
double optimizers::random_double(double min, double max){
    static unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    static default_random_engine generator(seed);
    uniform_real_distribution<double> distribution(min,max);
    return round_number(distribution(generator));
}

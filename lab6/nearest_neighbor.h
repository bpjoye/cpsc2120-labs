// Ben Joye
// CPSC 2120
// Lab Section 003
// 10/5/18

#include <vector>
#include <algorithm>
#include <iostream>
#include <math.h>

#pragma once

using namespace std;

class Point {
private:
    double x,y,z;
public:
  Point(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
  Point();
  int getX() const;
  int getY() const;
  int getZ() const;
};

Point::Point() {}

int Point::getX() const {
  return this->x;
}
int Point::getY() const {
  return this->y;
}
int Point::getZ() const {
  return this->z;
}

class nearest_neighbor {
private:
  vector<Point> points;
  Point neighbor1, neighbor2;
public:
    void add_point(double x, double y, double z);
    void find_closest_points();
    static bool compare(const Point& lhs, const Point& rhs);
    double distance(Point a, Point b);
    double closest(int min, int max);
    double bruteForce(int min, int max);
    double stripClosest(Point strip[], int size, float d);
};

bool nearest_neighbor::compare(const Point& lhs, const Point& rhs) {

  if (lhs.getX() > rhs.getX()) {
    return false;
  } else if (lhs.getX() < lhs.getX()) {
    return true;
  } else {
    if (lhs.getY() > rhs.getY()) {
      return false;
    } else if (lhs.getY() < lhs.getY()) {
      return true;
    } else {
      if (lhs.getZ() > rhs.getZ()) {
        return false;
      } else {
        return true;
      }
    }
  }

  return false; //default
}

//insert a new point
void nearest_neighbor::add_point(double x, double y, double z) {
  Point p(x,y,z);
  points.push_back(p);
}

double nearest_neighbor::bruteForce(int min, int max) {

  double minDist = distance(points[min], points[min+1]);
  // checks all possible distances and returns it
  if (max-min == 1) {
    // nothing
  } else if (max-min == 2) {

    if (distance(points[min], points[max]) < minDist) {
      minDist = distance(points[min], points[max]);
    }
    if (distance(points[max-1], points[max]) < minDist) {
      minDist = distance(points[max-1], points[max]);
    }
  }

  return minDist;
}

double nearest_neighbor::stripClosest(Point strip[], int size, float d) {
    double min = d;

    // go down the split line and see if any are smaller
    for (int i = 0; i < size; i++)
        for (int j = i+1; j < size && (strip[j].getY() - strip[i].getY()) < min; j++)
          if (distance(strip[i],strip[j]) < min) {
            min = distance(strip[i], strip[j]);
            neighbor1 = strip[i];
            neighbor2 = strip[j];
          }

    return min;
}

double nearest_neighbor::closest(int min, int max) {

  vector<int> p;
  double smallest;

  // base case
  if (max-min < 3) {
    return bruteForce(min,max);
  }

  // get the middle point
  int mid = min + ((max-min)/2);
  Point midPoint = points[mid];

  // call itself on the left and right sides
  double l = closest(min,mid);
  double r = closest(mid,max);

  // get which one is smaller
  if (l < r) {
    smallest = l;
  } else {
    smallest = r;
  }


  // look at the points that go across the split
  Point strip[max-min];
  int j = 0;
  for (int i = min; i < max; i++) {
    if (abs(points[i].getX() - midPoint.getX()) < smallest) {
      strip[j] = points[i];
      j++;
    }
  }

  // see if it is smaller than the other minimum value
  double minDist2 = stripClosest(strip, j, smallest);
  if (minDist2 < smallest) {
    return minDist2;
  }
  return smallest;
}

// calculates distance between two points
double nearest_neighbor::distance(Point a, Point b) {

  double s = pow(b.getX()-a.getX(),2) + pow(b.getY()-a.getY(),2) + pow(b.getZ()-a.getZ(),2);
  return sqrt(s);
}

void nearest_neighbor::find_closest_points() {

  // sort the vector by x, then y, then z
  sort(points.begin(), points.end(), compare);

  // call the recursive function
  double min = closest(1,points.size());
  // print formatting
  cout << "Nearest neighbors: ";
  cout << "(" << neighbor1.getX() << "," << neighbor1.getY() << "," << neighbor1.getZ() << ")";
  cout << " and ";
  cout << "(" << neighbor2.getX() << "," << neighbor2.getY() << "," << neighbor2.getZ() << ")";
  cout << endl;
  cout << "Distance: " << min << endl;
}

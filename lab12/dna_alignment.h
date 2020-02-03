// Ben Joye
// December 7, 2018
// CPSC 2120

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <ctype.h>
#include <algorithm>

using namespace std;

int min(int a, int b) {
  if (a < b)
    return a;
  else
    return b;
}

// algorithm from lab 11
int levenstein_distance(string query, string text) {

  int tracker, temp;
  int rowCount = text.length()+1;
  int colCount = query.length()+1;

  // dynamically allocate 2D array because it is large
  int** d = new int*[rowCount];
  for(int i = 0; i < rowCount; ++i) {
    d[i] = new int[colCount];
  }

  int qL = query.length();
  int tL = text.length();

  for (int i = 0; i <= qL; i++) {
    d[0][i] = i;
  }

  for (int j = 0; j <= tL; j++) {
    d[j][0] = j;
  }

  for (int j = 1; j < qL; j++) {
    for (int i = 1; i < tL; i++) {
      if (query[i-1] == text[j-1]) {
        tracker = 0;
      } else {
        tracker = 1;
      }
      temp = min(d[i-1][j] + 1, d[i][j-1] + 1);
      d[i][j] = min(temp, d[i-1][j-1] + tracker);
    }
  }
  int ret = d[tL-1][qL-1];
  delete[] d;
  return ret;
}

void process() {

  ifstream file("dna-samples.txt");
  vector<string> dna;
  vector<string> names;
  string dnaString = "";
  string name = "";
  string str = "";
  map<string, string> animalDna;

  if (!file.is_open()) {
    cerr << "Failed to open file!\n";
  }

  // read every line of the file
  while (getline(file, str)) {
    str.erase(remove(str.begin(), str.end(), '\n'), str.end());
    // if its name, add it to names
    if (str[0] == '-') {
      if (!names.empty()) {
        // add all the previous DNA to the dna vector
        dna.push_back(dnaString);
        dnaString = "";
      }
      str.erase(remove(str.begin(), str.end(), '-'), str.end());
      str.pop_back();
      names.push_back(str);
    } else {
      // add the dna to the whole string
      dnaString += str;
    }
  }
  dnaString.erase(remove(dnaString.begin(), dnaString.end(), '\n'), dnaString.end());
  dna.push_back(dnaString);

  // add each name as a key and dna sequence as a value to the map
  for (int i = 0; i < (int)dna.size(); i++) {
    cout << names.at(i) << endl;
    animalDna[names.at(i)] = dna.at(i);
  }

  cout << endl;

  // get the animal from the user
  string animal;
  cout << "enter the animal to compare..." << endl;
  getline(cin,animal);

  cout << endl;

  int distance;
  map<int, string> distanceTable;
  vector<int> distances;

  // loop through each animal
  for (int i = 0; i < (int)names.size(); i++) {
    distance = 0;
    // if the animal is different from the query, calculate the distance
    if (names.at(i) != animal) {
      distance = levenstein_distance(animalDna[names.at(i)], animalDna[animal]);
      // store the distance in a vector and in a map
      distances.push_back(distance);
      distanceTable[distance] = names.at(i);
    }
  }

  string s;
  // sort all the distances
  sort(distances.begin(), distances.end());
  // loop through the sorted distances and display the names associated with them
  for (int i = 0; i < (int)names.size()-1; i++) {
    s = animal + "-" + distanceTable[distances[i]];
    cout << s << ": " << distances[i] << endl;
  }
}

// Ben Joye
// CPSC 2120 - 003
// 11/30/18
// Lab 11

#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>
#include <vector>
#include <cerrno>
#include <algorithm>
#include <functional>

using namespace std;

string get_file_contents(const char *filename) {
  string file = "content/";
  file.append(filename);
  ifstream in(file, ios::in | ios::binary);
  if (in) {
    string contents;
    in.seekg(0, ios::end);
    contents.resize(in.tellg());
    in.seekg(0, ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return(contents);
  }
  throw(errno);
}

int min(int a, int b) {
  if (a < b)
    return a;
  else
    return b;
}

int levenstein_distance(string query, string text) {

  int tracker, temp;
  int d[50][50];
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

  return d[tL-1][qL-1];
}

int search() {

  string query;
  cout << "Enter to query to find: " << endl;
  getline(cin,query);
  cout << endl;

  vector<string> files;
  vector<string> text;

  // Reads in all file names
  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir ("content")) != NULL) {
    /* print all the files and directories within directory */
    while ((ent = readdir (dir)) != NULL) {
      files.push_back(ent->d_name);
    }
    closedir (dir);
  } else {
    /* could not open directory */
    perror ("");
    return EXIT_FAILURE;
  }

  string textString;
  for (int i = 2; i < (int)files.size(); i++) {
    text.push_back(get_file_contents(files[i].c_str()));
  }


  bool found;
  bool run = true;

  while (run) {

    found = false;

    // STEP 1: searches file names for exact match
    for (int i = 0; i < (int)files.size(); i++) {
      auto it = search(files[i].begin(), files[i].end(), query.begin(), query.end());
      if (it != files[i].end()) {
        cout << "The string " << query << " found in " << files[i] << " at offset " << it - files[i].begin() << '\n';
        found = true;
        break;
      } else if (i == (int)files.size()-1) {
        cout << "Exact match for " << query << " was not found in file names\n";
      }
    }

    // STEP 2: Finds an exact match if there is one
    if (!found) {
      for (int i = 0; i < (int)text.size(); i++) {
        auto it = search(text[i].begin(), text[i].end(), query.begin(), query.end());
        if(it != text[i].end()) {
          cout << "The string " << query << " found in " << files[i+2] << " at offset " << it - text[i].begin() << '\n';
          found = true;
          break;
        } else if (i == (int)text.size()-1) {
          cout << "Exact match for " << query << " was not found\n";
        }
      }
    }

    // STEP 3: find closest string
    if (!found) {
      int totalLength, minScore, tempScore;
      string minString, str;
      int qL = query.length();
      minScore = 2147483647;

      for (int i = 0; i < (int)text.size(); i++) {

        totalLength = text[i].size();

        for (int ch = 0; ch < totalLength - qL - 1; ch++) {

          str = text[i];
          tempScore = levenstein_distance(query, str.substr(ch,qL));

          if (tempScore < minScore) {
            minScore = tempScore;
            minString = str.substr(ch,qL);
          }
        }
      }
      cout << "Closest string: " << minString << endl;
    }
    cout << endl;
    cout << "Would you like to enter another query? (y/n)" << endl;
    string r;
    getline(cin,r);
    cout << endl;
    if (!r.compare("y")) {
      cout << "Enter to query to find: " << endl;
      getline(cin,query);
      cout << endl;
    } else {
      run = false;
    }
  }
  return 0;
}

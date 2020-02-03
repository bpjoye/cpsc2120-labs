#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <utility>
#include <regex>
#include "memoization.h"
#include "integration.h"


//please add tests to lab07_int.txt and lab07_memo.txt
//there is no need to edit anything in this file
using namespace std;

const string regexMatchPattern = "(?=\\S)([\\-\\+]?\\d*\\.?\\d*)?(x)?(\\^\\-?\\d*\\.?\\d*)?";

void run_integration_program();
void run_memoization_program();

vector<pair<double,double> > create_equation_vector(string& equation);
pair<int,int> calculate_fibonacci_value(ifstream& infile, memoization& memo);

string trim_string(string value);
bool is_white_space(char value);

int main(){
    run_integration_program();
    run_memoization_program();
    return 0;
}

void run_integration_program(){
    ifstream infile("lab07_int.txt");
    string line;
    while(getline(infile, line)){
        line = trim_string(line);
        cout << line << endl;
        stringstream stream(line);
        string equation;
        double lowerBound, upperBound;
        stream >> equation >> lowerBound >> upperBound;

        vector<pair<double,double> > equationVector = create_equation_vector(equation);
        integration inte(equationVector);
        cout << inte.perform_integration(lowerBound, upperBound) << endl << endl;
    }
}

void run_memoization_program(){
    ifstream infile("lab07_memo.txt");
    while(infile.is_open()){
        memoization memo;
        pair<int,int> value = calculate_fibonacci_value(infile, memo);
        if(value.first != -1){
            cout << "fib(" << value.first << ")" << endl;
            cout << value.second << endl << endl;
        }
    }
}

vector<pair<double,double> > create_equation_vector(string& equation){
    vector<pair<double,double> > equationVector;
    smatch matchingValue;
    regex expression(regexMatchPattern);

    while(regex_search(equation,matchingValue,expression)){
        string number = *(matchingValue.begin()+1);
        string exponent = *(matchingValue.begin()+3);
        if(number == "-" || number == "+" || number == "")
            number += "1";
        if(exponent == "")
            exponent = "^0";
        exponent = string(exponent.begin()+1,exponent.end());
        equationVector.push_back(make_pair(stod(number),stod(exponent)));
        equation = matchingValue.suffix().str();
    }

    return equationVector;
}

pair<int,int> calculate_fibonacci_value(ifstream& infile, memoization& memo){
    string line;
    if(!getline(infile, line)){
        infile.close();
        return make_pair(-1,-1);
    }

    line = trim_string(line);
    int number = stoi(line);
    return make_pair(number,memo.calculate_fibonacci_value(number));
}

//gets rid of any trailing and/or leading white space when lines from file are read in
string trim_string(string value){
    auto start = value.begin();
    auto end = value.rbegin();
    int length = value.length();
    while(is_white_space(*start)) start++;
    while(is_white_space(*end)) {end++; length--;}
    return string(start,start+length);
}

bool is_white_space(char value){
    return value == '\t' || value == '\n' || value == '\r' || value == '\f' || value == ' ';
}

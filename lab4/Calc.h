// Ben Joye
// CPSC 2121-003
// 9.18.18

#pragma once

#include <stack>
#include <string>
#include <regex>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

class Calc {
  private:
    stack<double> numbers;
    stack<char> operators;

    string regex_match_pattern();
    vector<string> parse_equation(string equation);
  public:
    double solve_equation(string equation);
    double calculate(char, double, double);
};

//returns a string of a regex pattern used to split a formula
string Calc::regex_match_pattern() {
    string leftParentheses = "[(]";
    string rightParentheses = "[)]";
    string operators = "[\\-\\/+*^%]";
    string doubles = "(?:\\d+[.]\\d*|\\d*[.]\\d+|\\d+)";
    return leftParentheses + "|" + rightParentheses + "|" + operators  + "|" + doubles;
}

//takes in an equation in the form of a string, splits it, and returns it in a vector
vector<string> Calc::parse_equation(string equation) {
    vector<string> parsedEquation;
    smatch matchingValue;
    regex expression(regex_match_pattern());

    while(regex_search(equation,matchingValue,expression)){
        for(auto match: matchingValue)
            parsedEquation.push_back(match);
        equation = matchingValue.suffix().str();
    }

    return parsedEquation;
}

//takes in an equation, solves it, and returns the answer
double Calc::solve_equation(string equation){

  double answer = 0;
  string tS;
  double tN;
  vector<string> s = parse_equation(equation);
  // size of the equation
  int size = static_cast<int>(s.size());
  // loop through every character in the equation
  for (int x = 0; x < size; x++) {
    // if the character is ")"
    if (s.at(x) == ")") {
      // loop backwards through the calculation in the parentheses, and calculate it
      while (operators.top() != '(') {
        double n2 = numbers.top();
        numbers.pop();
        double n1 = numbers.top();
        numbers.pop();
        char o = operators.top();
        operators.pop();
        double ans = calculate(o, n1, n2);
        numbers.push(ans);
      }
      // remove the open parentheses
      operators.pop();

    // if the character is "(", add it to the operators stack
    } else if (s.at(x) == "(") {
      tS = s[x];
      operators.push(tS[0]);
    // if the character is "+", add it to the operators stack
    } else if (s.at(x) == "+") {
      tS = s[x];
      operators.push(tS[0]);
    // if the character is "-", add it to the operators stack
    } else if (s.at(x) == "-") {
      tS = s[x];
      operators.push(tS[0]);
    // if the character is "%", add it to the operators stack
    } else if (s.at(x) == "%") {
      tS = s[x];
      operators.push(tS[0]);
    // if the character is "*", add it to the operators stack
    } else if (s.at(x) == "*") {
      tS = s[x];
      operators.push(tS[0]);
    // if the character is "/", add it to the operators stack
    } else if (s.at(x) == "/") {
      tS = s[x];
      operators.push(tS[0]);
    // if the character is "^", add it to the operators stack
    } else if (s.at(x) == "^") {
      tS = s[x];
      operators.push(tS[0]);
    // if the character is a number, add it to the numbers stack
    } else {
      tN = stod(s[x]);
      numbers.push(tN);
      // if there are no parentheses, then just do the calculation normally
      if (numbers.size() == 2 && operators.size() == 1) {
        double n2 = numbers.top();
        numbers.pop();
        double n1 = numbers.top();
        numbers.pop();
        char o = operators.top();
        operators.pop();
        double ans = calculate(o,n1,n2);
        numbers.push(ans);
      }
    }

  }
  // if there are two numbers and an operation left at the end, do the calculation
  if (numbers.size() == 2 && operators.size() == 1) {
    double n2 = numbers.top();
    numbers.pop();
    double n1 = numbers.top();
    numbers.pop();
    char o = operators.top();
    operators.pop();
    double ans = calculate(o,n1,n2);
    numbers.push(ans);
  }

  // the answer is the last number in the stack at the end of all calculations
  answer = numbers.top();
  numbers = stack<double>();
  operators = stack<char>();
  return answer;
}

// function to handle all calculations
double Calc::calculate(char o, double n1, double n2) {
  double answer = 0;
  if (o == '+')
    answer = n1 + n2;
  if (o == '-')
    answer = n1 - n2;
  if (o == '*')
    answer = n1 * n2;
  if (o == '/')
    answer = n1 / n2;
  if (o == '^')
    answer = pow(n1,n2);
  if (o == '%')
    answer = fmod(n1,n2);
  return answer;
}

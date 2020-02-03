/*
 * Name: Ben Joye
 * Date Submitted: 9/10/18
 * Lab Section: 3
 * Assignment Name: Lab 3
 */

#include <iostream>
#include <string>
#include "Stack.h"
#include "Queue.h"
#include <string>
using namespace std;

//Test the Stack class in Stack.h
void stack_test();

//Test the Queue class in Queue.h
void queue_test();

int main()
{
    stack_test();
    queue_test();

    return 0;
}

void stack_test()
{
    Stack<int> s1;
    for (int i = 1; i < 30; i++)
    {
        s1.push(i);
        if (i % 3 == 0)
        {
            s1.pop();
            s1.pop();
        }
    }
    cout << "s1: size = " << s1.size() << ", stack = ";
    s1.print();

    Stack<char> s2;
    int i = 1;
    for (char c = 'a'; c <= 'z'; c++, i++)
    {
        if (i % 4 == 0)
        {
            s2.push('#');
        }
        else
        {
            s2.push(c);
        }
        if (i % 6 == 0)
        {
            s2.pop();
            s2.pop();
        }
    }
    cout << "s2: size = " << s2.size() << ", stack = ";
    s2.print();

    Stack<double> s3;
    for (double k = 1; k <= 1000000; k++)
    {
        double value = 0.5 * k;
        s3.push(value);
    }
    for (double k = 1; k <= 1000000 - 6; k++)
    {
        s3.pop();
    }
    cout << "s3: size = " << s3.size() << ", stack = ";
    s3.print();

    Stack<int> s4;
    for (int x = 1; x < 10; x++) {
      s4.push(100/x);
      if (x%2 == 0)
        s4.pop();
    }
    cout << "s4: size = " << s4.size() << ". stack = ";
    s4.print();


    Stack<char> s5;
    for (int x = 0; x < 20; x+=2) {
      s5.push('z' - x);
    }
    s5.pop();
    s5.pop();
    cout << "s5: size = " << s5.size() << ". stack = ";
    s5.print();
}

void queue_test()
{
    Queue<int> q1;
    for (int i = 1; i < 30; i++)
    {
        q1.push(i);
        if (i % 3 == 0)
        {
            q1.pop();
            q1.pop();
        }
    }
    cout << "q1: size = " << q1.size() << ", queue = ";
    q1.print();

    Queue<char> q2;
    int i = 1;
    for (char c = 'a'; c <= 'z'; c++, i++)
    {
        if (i % 3 == 0)
        {
            char d = (char)(c - 32);
            q2.enqueue(d);
        }
        else
        {
            q2.enqueue(c);
        }
        if (i % 6 == 0)
        {
            q2.dequeue();
            q2.dequeue();
        }
    }
    cout << "q2: size = " << q2.size() << ", queue = ";
    q2.print();

    Queue<double> q3;
    for (double k = 1; k <= 1000000; k++)
    {
        q3.push(k);
    }
    for (double k = 1; k <= 1000000 - 6; k++)
    {
        q3.pop();
    }
    cout << "q3: size = " << q3.size() << ", queue = ";
    q3.print();

    Queue<string> q4;
    q4.push("John");
    q4.push("Blake");
    q4.push("Thomas");
    q4.pop();
    q4.push("Sam");
    q4.pop();
    q4.push("Austin");
    q4.push("Thomas");
    q4.pop();
    cout << "q4: size = " << q4.size() << ", queue = ";
    q4.print();

}

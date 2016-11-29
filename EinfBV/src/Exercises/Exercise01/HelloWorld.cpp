/** @file   HelloWorld.cpp
    @brief  Simple program to get started with C++ programming (exercise 1).
    @author esquivel
*/

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
  // Read parameters
  string name = argc > 1 ? argv[1] : "";

  // Print stuff
  cout << "Hello world!" << endl;

  // Get input from user or from parameter
  if (name == "") {
    cout << "What is your name?" << endl;
    cin >> name;
  }
  cout << "Hello " << name << ", nice to meet you!" << endl;

  return 0;
}

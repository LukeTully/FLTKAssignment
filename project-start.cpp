/*
    Assignment 8 - Question 3 - project-start.cpp
    Student Number: 3020946
    Name: Lucas Martin-Tully
    Purpose: Create the custom window required for question 3
*/

#include "libraries/GUI.h"
#include "libraries/Graph.h"
#include "libraries/Window.h"
#include "libraries/line_window.h"
#include <exception>

int main() {
  
  try {
    using namespace Graph_lib;
    Lines_window win{Point{100, 100}, 600, 400, "lines"};
    return gui_main();
  } catch (std::exception& e) {
    cerr << "exception: " << e.what() << '\n';
    return 1;

  } catch (...) {
    cerr << "Some exception\n";
    return 2;
  }

  return 0;
}
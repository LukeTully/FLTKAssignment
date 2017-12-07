#include <iostream>
#include "Windims.h"
#include "Project_window.h"

using std::cerr;
using std::endl;
using namespace Graph_lib;

/* project.cpp
 * Program for project
 *
 * Author: Blair Jamieson (Jan 2017)
 *
 */


int main()
  try {


    Project_window project{ Point{100,100}, Windims::xmax, Windims::ymax, "Project"}; 

    project.play();
    return 0;
  } 
  catch (exception& e) {
    cerr << "exception: " << e.what() << endl;
    keep_window_open();
    return 1;
  }
  catch (...) {
    cerr << "exception\n";
    keep_window_open();
    return 2;
  }
  


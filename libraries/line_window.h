#include "GUI.h"
#include "Graph.h"
#include "Window.h"

#ifndef LINE_WINDOW_H
#define LINE_WINDOW_H

struct Lines_window : Graph_lib::Window {
  Lines_window(Graph_lib::Point xy, int w, int h, const string& title);

 private:
  // data:
  Graph_lib::Open_polyline lines;

  // widgets:
  Graph_lib::Button next_button;  // add (next_x,next_y) to lines
  Graph_lib::Button quit_button;  // end program
  Graph_lib::In_box next_x;
  Graph_lib::In_box next_y;
  Graph_lib::Out_box xy_out;

  void next();
  void quit();
};

#endif
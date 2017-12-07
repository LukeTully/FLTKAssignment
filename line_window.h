#include "libraries/GUI.h"
#include "libraries/Graph.h"
#include "libraries/Window.h"

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
  Graph_lib::Menu color_menu;
  Graph_lib::Button menu_button;

  void change(Graph_lib::Color c) { lines.set_color(c); }

  void hide_menu() {
    color_menu.hide();
    menu_button.show();
  }

  // actions invoked by callbacks:
  void red_pressed() {
    change(Graph_lib::Color::red);
    hide_menu();
  }
  void blue_pressed() {
    change(Graph_lib::Color::blue);
    hide_menu();
  }
  void black_pressed() {
    change(Graph_lib::Color::black);
    hide_menu();
  }
  void menu_pressed() {
    menu_button.hide();
    color_menu.show();
  }
  void next();
  void quit();

  // callback functions:
  static void cb_red(Graph_lib::Address, Graph_lib::Address);
  static void cb_blue(Graph_lib::Address, Graph_lib::Address);
  static void cb_black(Graph_lib::Address, Graph_lib::Address);
  static void cb_menu(Graph_lib::Address, Graph_lib::Address);
  static void cb_next(Graph_lib::Address, Graph_lib::Address);
  static void cb_quit(Graph_lib::Address, Graph_lib::Address);
};

#endif
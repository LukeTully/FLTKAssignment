/*
 * fltkTest.cpp
 * Author: Blair Jamieson (Oct. 2016)
 *
 * A short program to print "Hello world" in an fltk window
 *
 */

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>

int main(){
  Fl_Window window( 200, 200, "My Fltk Window" );
  Fl_Box box(0, 0, 200, 200, "Hello World and Hello Fltk");
  window.show();
  return Fl::run();
}

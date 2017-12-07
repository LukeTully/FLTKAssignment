#ifndef _Project_window_h_
#define _Project_window_h_

#include <memory>
#include "Window.h"
#include "Windims.h"
#include "Graph.h"
#include "GUI.h"

/*
 * Project_window
 * 
 * Class to make a Graph_lib::Window that implements a project.
 *
 * Author: Blair Jamieson (2017)
 */

class Project_window : public Graph_lib::Window {
 public:
  Project_window( Graph_lib::Point xy, int w, int h, const string& title );

  // only public method to "play chess"
  void play();

 private:  
  Graph_lib::Button quit_button;  // button to exit program
  Graph_lib::Button start_button; // button to do something when "start" is pressed

  void quit();    // function to quit program
  void start();   // function to start new game
  
  static void cb_quit(Graph_lib::Address, Graph_lib::Address);
  static void cb_start(Graph_lib::Address, Graph_lib::Address);

  // Author label
  Graph_lib::Text author_out;
  
  // state of game
  bool quit_pressed{false};
  
  // strings to hold screen outputs
  std::string sauthor{"Blair Jamieson (2017)"};

};


#endif

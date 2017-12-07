//#include <cctype>
#include "Windims.h"
#include "Project_window.h"

//using std::ostringstream;
using namespace Graph_lib;
using namespace Windims;

//===========================================================================================================
Project_window :: Project_window( Point xy, int w, int h, const string& title ) :
  Window{ xy, w, h, title},
  quit_button{ Point{x_max()-70,0},70,20,"Quit", cb_quit },
  start_button{ Point{x_max()-70,20},70,20,"Start", cb_start },
  author_out{ Point{0,ymax-20}, "Blair Jamieson (2017)" }
{
  attach( quit_button );
  attach( start_button );
  attach( author_out );
  
  return;
}

//===========================================================================================================
void Project_window::play() {
  show();
  
  while (!quit_pressed){
    Fl::wait(1);
  }
  Fl::redraw();

  return;
}

//===========================================================================================================
void Project_window::quit(){
  quit_pressed = true;
  hide();
}

//===========================================================================================================
void Project_window::start(){
  // do something here...

  Fl::redraw();
}


//===========================================================================================================
void Project_window::cb_quit(Address, Address pw){
  reference_to<Project_window>(pw).quit();
}

//===========================================================================================================
void Project_window::cb_start(Address, Address pw){
  reference_to<Project_window>(pw).start();
}




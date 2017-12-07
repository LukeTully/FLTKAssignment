#ifndef _Windims_h_
#define _Windims_h_
#include <string>
#include "Graph.h"

/*
 *  Windims.h
 *  Constants for window size and chess board square size.
 *
 *  Author: Blair Jamieson (Jan. 2017)
 */

namespace Windims {
  const int xmax{ 800 };    // window size 
  const int ymax{ 800 }; 
  const int xoffset{ 50 }; // distance from left hand side of window to board
  const int yoffset{ 100 };  // distance from topof window to board
  //  const int xspace{150 };   // space beyond axis 
  //  const int yspace{ 60 };  
  //const int xlength{ xmax-xoffset-xspace };    // length of axes 
  //const int ylength{ymax-yoffset-yspace};
  const int piecesize{80}; // size of chess piece image
 
  
} 

#endif

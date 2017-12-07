/*
 * testGraph.cpp
 * Simple example to plot sin(x) from 0 to 2pi and
 * thus test the SC::Graph class
 *
 * Author: Blair Jamieson
 * Date:   Oct. 12, 2016
 *
 */

#include <cmath>
#include <vector>
#include "SCGraph.h"

using namespace SC;

int main(){
  const int npts = 20;
  std::vector<double> xx, yy, ee;
  double dx = 2.*std::acos(-1)/npts;
  for ( int i = 0; i< npts; i++){
    xx.push_back( dx * i );
    yy.push_back( std::sin( dx * i ) );
    ee.push_back( std::fabs(0.05*std::sin( dx*i )) + 0.05 );
  }   
  Graph g1( "sin(x) vs x", "x", "sin(x)", xx, yy, ee );
  g1.Print();

  std::vector< std::string > ascreen;
  GraphScreenClear( ascreen, 80, 30 );
  g1.Draw( ascreen );

  // Test user input graph
  Graph g2( "User input data", "x data", "y data" ); 
  g2.DataCin();
  g2.Print();
  GraphScreenClear( ascreen, 100, 40 );
  g2.Draw( ascreen );

  return 0;
}


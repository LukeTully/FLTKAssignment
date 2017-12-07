/*
 * SCGraph.h
 *
 * Author: Blair Jamieson
 * Date:   Oct. 12, 2016
 *
 ************************************************************************
 *
 * Overview
 * --------
 * Simple graph class in the SC (Scientific computing) namespace.
 * A first example of making a class.
 *
 * Also makes a typedef std::vector<double> VD and typedef std::string
 * SS to shorten notation when declaring and using vectors.
 *
 * SC::Graph holds data for making a graph.  We will assume that we
 * need to make a copy of the data to hold in our class (since the
 * reference will go away).  
 *
 *************************************************************************
 *
 * Initializing a SC::Graph
 * -----------------------
 * It can be initialized in one of the following ways, where title
 * xlabel and ylabel are std::string holding the graph title,
 * xaxis label and yaxis label respectively.
 *
 * SC::Graph gr1( title, xlabel, ylabel );  // empty graph
 *
 * // below vecx, vecy and vecdy are of SCvd type.
 * SC::Graph gr2( title, xlabel, ylabel, 
 *                vecx, vecy, vecdy );
 * 
 * // below arrx, arry and arrdy are arrays of double
 * // of length n, ie
 * const int n = 100; // number of data points
 * double arrx[n], arry[n], arrdy[n];
 * SC::Graph gr3( title, xlabel, ylabel, 
 *                n, arrx, arry, arrdy );
 *
 **************************************************************************
 *
 * Operations that can be performed on a SC::Graph
 * -----------------------------------------------
 * Methods for adding data to a graph:
 * ..................................
 * void DataCin() // ask for input by Cin
 * void SetData( vecx, vecy, vecdy ); // set data with SDvd types
 * void SetData( n, arrx, arry, arrdy ); // set data with arrays
 *
 * Methods for manually getting and setting axis (use another user defined type):
 * ..............................................................................
 * SC::Axis xax, yax;
 * void SetAxes( xax, yax);
 * void SetXAxis( xax );
 * void SetYAxis( yax );
 * void GetAxes( xax, yax );
 *
 * Methods for drawing options:
 * ............................
 * void SetMarker( cm ); // cm is a char to use for marker
 *
 * Method for drawing the graph:
 * ..............................
 * Draw graph into vector of strings to hold contents of
 * screen when drawing "text" plot.
 * Number of entries in vector should be number
 * of lines on terminal.  Length of each vector
 * should be width of screen
 *
 * void Draw( std::vector< SS > &aScreen );
 *
 * Method to print data to screen
 * ..............................
 * void PrintData();
 *
 */

#ifndef SCGraph_h_
#define SCGraph_h_

#include <vector>
#include <string>
#include "SCAxis.h"

namespace SC {
  typedef std::vector<double> VD;
  typedef std::string SS;
  void GraphScreenClear( std::vector< std::string> & aScreen, 
			 const unsigned ax=80, 
			 const unsigned ay=30 ); 
  
  // Graph class to represent a set of data
  // with N points of form (x, y+-dy )
  class Graph {
  public:  // public part of class is meant to hold interface to the object

    Graph();
    Graph( const SS & atitle, const SS & axlabel, const SS & aylabel ); 
    Graph( const SS & atitle, const SS & axlabel, const SS & aylabel,   
	   const VD &ax, const VD &ay, const VD &ady ); 
    Graph(  const SS & atitle, const SS & axlabel, const SS & aylabel,   
	    const unsigned an, const double ax[], const double ay[], const double ady[] ); 
    void DataCin();
    void SetData( const VD &ax, const VD &ay, const VD &ady );
    void SetData( const unsigned an, const double ax[], const double ay[], const double ady[] );
    void SetAxes( const Axis & axx, const Axis & axy );
    void SetXaxis( const Axis & axx );
    void SetYaxis( const Axis & axy );
    void GetAxes( Axis & xax, Axis & yax );
    void SetMarker( const char amk );
    void Draw( std::vector< SS > &aScreen );
    void Print();

  private:
    // private part of class is meant to hold implementation details
    // not accessible from outside of the class
    // keep copy of data
    SS fTitle;
    VD fX;
    VD fY;
    VD fdY;
    Axis fXax;
    Axis fYax;
    char fMarker;

    void ResetAxisRanges();
  };
}


#endif

/*
 * SCAxis.h
 *
 * Author: Blair Jamieson
 * Date:   Oct. 12, 2016
 *
 ************************************************************************
 *
 * Overview
 * --------
 * Simple axis class in the SC (Scientific computing) namespace.
 * A first example of making a class.
 *
 * SC::Axis holds axis range, number of ticks, and orientiation.
 * Ie. we will draw the axis differently if it is vertical or horizontal.
 *
 *************************************************************************
 *
 * Initializing a SC::Axis
 * -----------------------
 * It can be initialized in one of the following ways, where 
 * alabel is std::string holding axis label, ishorizontal is a boolean
 * that is true if it is a horizontal (x-axis)
 *
 * SC::Axis ax1( alabel, axmin, axmax, ishorizontal );
 *
 **************************************************************************
 *
 * Operations that can be performed on an SC::Axis
 * -----------------------------------------------
 *
 * Methods for getting and setting axis
 * ....................................
 * void SetRange( axmin, axmax );
 * void SetLabel( alabel );
 * void SetNDivs( an ); // number of axis ticks
 * void SetHorizontal(); // make axis horizontal x-axis
 * void SetVertical(); // make axis vertical y-axis
 * void GetRange( axmin, axmax );
 * void GetLabel( alabel );
 * int GetNDivs();
 *
 * Handy methods for getting location on screen of 
 * a value along axis
 * unsigned GetLoc( std::vector< SS >& aScreen, const double aval );
 *
 * Method for drawing the axis
 * ..............................
 * // takes std::vector< std::screen > to draw into
 * void Draw( screen ); 
 *
 */
#ifndef SCAxis_h_
#define SCAxis_h_

#include <string>
#include <vector>

namespace SC {
  const unsigned   kMinAxisLen = 20; // minimum axis length in characters

  // Axis class to represent axis of a plot
  class Axis {
  public:
    Axis();
    Axis( const std::string &alabel, const double axmin, const double axmax, 
	  const bool ishorizontal );
    void     SetRange( const double & axmin, const double & axmax );
    void     SetLabel( const std::string & alabel ) { fLabel = alabel; }
    void     SetNDivs( const unsigned an ){ fNDivs = an; }
    void     SetHorizontal() { fIsX = true; }
    void     SetVertical() { fIsX = false; } 
    void     GetRange( double &axmin, double &axmax ) const;
    void     GetLabel( std::string &alabel ) const;
    unsigned GetNDivs() const;
    unsigned GetLoc( std::vector< std::string >& aScreen, const double aval ) const;
    void     Draw( std::vector< std::string > & aScreen ) const; 

  private:
    std::string fLabel;
    double      fMin;
    double      fMax;
    unsigned    fNDivs;
    bool        fIsX;
    // Helper methods for drawing X or Y axis
    void     DrawX( std::vector< std::string > & aScreen ) const;
    void     DrawY( std::vector< std::string > & aScreen ) const;
  };
}


#endif

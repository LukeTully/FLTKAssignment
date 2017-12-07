#include <iostream>
#include <iomanip>
#include <sstream>
#include "SCAxis.h"

using std::cout;
using std::cerr;
using std::endl;
using std::scientific;
using std::setprecision;
using std::setw;
using std::stringstream;
using namespace SC;


//////////////////////////////////////////////////////////////////////////////////////////////
Axis::Axis( ){
  fNDivs = 5;
  return;
} 


//////////////////////////////////////////////////////////////////////////////////////////////
Axis::Axis( const std::string & alabel, const double axmin, const double axmax, 
	    const bool ishorizontal ) : fLabel(alabel), fMin( axmin ), fMax( axmax ), fIsX( ishorizontal ) {
  // Set initial value for number of divisions
  fNDivs = 5;
  // sanity check:
  if ( fMax < fMin ) {
    double tmp = fMax;
    fMax = fMin;
    fMin = tmp;
  }
  return;
}

//////////////////////////////////////////////////////////////////////////////////////////////
void Axis::SetRange( const double & axmin, const double & axmax ){
  if ( axmin == axmax ){
    #ifndef NDEBUG
    cerr << __func__ << " axmax == axmax = " << axmin << endl;
    #endif
    return;
  } 

  if ( axmin < axmax ) {
    fMin = axmin;
    fMax = axmax; 
  } else {
    fMax = axmin;
    fMin = axmax;
  }
  
  return;
}


//////////////////////////////////////////////////////////////////////////////////////////////
void Axis::GetRange( double &axmin, double &axmax ) const {
  axmin = fMin;
  axmax = fMax;
  return;
}


//////////////////////////////////////////////////////////////////////////////////////////////
void Axis::GetLabel( std::string &alabel ) const {
  alabel =fLabel;
  return;
}

//////////////////////////////////////////////////////////////////////////////////////////////
unsigned Axis::GetNDivs() const {
  return fNDivs;
}

//////////////////////////////////////////////////////////////////////////////////////////////
unsigned Axis::GetLoc( std::vector< std::string >& aScreen, const double aval ) const {
  unsigned retval = 0;
  // get length of screen
  auto hh = aScreen.size();
  if ( hh == 0 ){
#ifndef NDEBUG
    cerr << __func__ << " screen height zero! " << endl;
#endif
    return 0;
  }
  auto ww = aScreen[0].size();
  // Answer depends on whether this is an x-axis or a y-axis
  if ( fIsX == true ){
    // 1) For horizontal axis: 
    //    first 10 char of screen are for y-axis numbers
    if ( ww < kMinAxisLen ){
#ifndef NDEBUG
      cerr << __func__ << " ww = "<<ww<< " < "
	   << kMinAxisLen << " screen too small! " << endl;
#endif
      return retval;
    }
    auto len = ww - 10;
    if ( aval <= fMin ) return 10;
    if ( aval >= fMax ) return ww-1;
    retval = (aval-fMin) / (fMax - fMin ) * len ;
    retval += 10;
    if (retval >= ww) retval = ww-1; //sanity check

  } else {
    // 2) For vertical axis: 
    //      first 2 char are for title and y-axis label, and
    //      last three are for x-axis 
    if ( hh < kMinAxisLen ){
#ifndef NDEBUG
      cerr << __func__ << " hh = "<<hh<< " < "
	   << kMinAxisLen << " screen too small! " << endl;
#endif
      return 0;
    }
    auto len = hh - 5;
    if ( aval <= fMin ) return len+2;
    if ( aval >= fMax ) return 3;
    retval = (aval-fMin) / (fMax - fMin ) * len;
    retval = len + 2 - retval;

    if ( retval >  hh-1 ) retval = hh-1; // sanity check
  }
  
  return retval;
}

//////////////////////////////////////////////////////////////////////////////////////////////
void Axis::Draw( std::vector< std::string > & aScreen ) const {
  if (  fIsX == true ){
    DrawX( aScreen );
  } else {
    DrawY( aScreen );
  }
  return;
}

//////////////////////////////////////////////////////////////////////////////////////////////
void Axis::DrawX( std::vector< std::string > & aScreen ) const{
  auto imin = GetLoc( aScreen, fMin );
  auto imax = GetLoc( aScreen, fMax );
  auto hh = aScreen.size();
  if ( hh < kMinAxisLen ){
    #ifndef NDEBUG
    cerr << __func__ << " hh = "<<hh<< " < "
	 << kMinAxisLen << " screen too small! " << endl;
    #endif
    return;
  }
  auto ww = aScreen[0].size();
  auto ytix = hh - 3; // screen line with axis line
  auto ynum = hh - 2; // screen line with axis numbers
  auto ylab = hh - 1; // screen line with axis label
  auto di = imax - imin;
  auto ditix = di / fNDivs;
  double dx = ditix / double( di ) * ( fMax - fMin );
  std::string & sstix = aScreen[ ytix ];
  std::string & ssnum = aScreen[ ynum ];
  std::string & sslab = aScreen[ ylab ];

  // fill in the axis line
  for ( decltype( sstix.size() ) i = imin ; i != ww ; ++i ){
    if ( i == imin ) {
      sstix[i] = '+';
    } else if ( i == ww-1 ) {
      sstix[i] = '>';
    } else if ( (i-imin)%ditix == 0 ) {
      sstix[i] = '|';
    } else {
      sstix[i] = '-';
    }
  }

  // fill in the line of numbers for each tick mark
  // make each number 9 characters wide +X.XXe+YY
  // length of just numbers is 9 * fNDivs = 45 (for 5 divisions)
  if ( di < 10 * fNDivs ){
    // not enough space to put all numbers for divisions
    // just put min and max
    for (int i=0; i<2; i++ ){
      double aval = fMin + dx*fNDivs*i;
      stringstream iss;
      iss << scientific;
      iss << setprecision(2);
      iss << setw(9) << aval;
      unsigned xoffs = imin - 5 + i*imax;
      std::string ss = iss.str();
      for ( decltype( ss.size() ) j=0; j != ss.size(); ++j ){
	unsigned xcur = xoffs + j ;
	if ( xcur < ww ) ssnum[ xcur ] = ss[j];	
      }
    }
  } else {
    // numbers should all fit for number of divisions
    for ( unsigned i=0 ; i <= fNDivs ; ++i ){
      double aval = fMin + dx*i;
      stringstream iss;
      iss << scientific;
      iss << setprecision(2);
      iss << setw(9) << aval;
      unsigned xoffs = imin - 5 + i*ditix;
      std::string ss = iss.str();
      for ( decltype( ss.size() ) j=0; j != ss.size(); ++j ){
	unsigned xcur = xoffs + j ;
	if ( xcur < ww ) ssnum[ xcur ] = ss[j];	
      }
    }
  }

  // Now draw the axis label
  auto lenlab = fLabel.size();
  if (lenlab > ww) lenlab=ww;
  unsigned ilabmin = ww-lenlab;
  unsigned ilabmax = ww;
  for ( unsigned i = ilabmin ; i != ilabmax ; ++i ) {
    sslab[ i ] = fLabel[ i-ilabmin ];
  }

  return;
}


//////////////////////////////////////////////////////////////////////////////////////////////
void Axis::DrawY( std::vector< std::string > & aScreen ) const{

  // index into screen increases going down, so swap fMin and fMax
  auto imin = GetLoc( aScreen, fMax ); 
  auto imax = GetLoc( aScreen, fMin );
  auto hh = aScreen.size();
  if ( hh < kMinAxisLen ){
    #ifndef NDEBUG
    cerr << __func__ << " hh = "<<hh<< " < "
	 << kMinAxisLen << " screen too small! " << endl;
    #endif
    return;
  }
  auto ww = aScreen[0].size();
  auto di = imax - imin;
  auto ditix = di / fNDivs;
  double dx = ditix / double( di ) * ( fMax - fMin );  

  // print the axis label on line [1]
  auto lablen = fLabel.size();
  if ( lablen > ww ) lablen = ww;
  for ( unsigned i = 0; i != lablen; ++i ){
    aScreen[1][i] = fLabel[i];
  }

  // print the axis and ticks
  unsigned ixax = 10;
  for ( unsigned i = 3 ; i != hh-1 ; ++i ) {
    if ( i == imin ){
      aScreen[hh-i][ixax] = '+';
    } else if ( i == hh-2 ) {
      aScreen[hh-i][ixax] = '^';
    } else if ( (i-imin)%ditix == 0 ) {
      aScreen[hh-i][ixax] = '-';
    } else {
      aScreen[hh-i][ixax] = '|';
    }
  }

  // print numbers on axis marks
  for ( unsigned i=0 ; i <= fNDivs+1 ; ++i  ) {    
    double aval = fMin + dx*i;
    stringstream iss;
    iss << scientific;
    iss << setprecision(2);
    iss << setw(9) << aval;
    unsigned yoffs = hh - 3 - ditix*i;
    if ( yoffs > 1 ){
      std::string ss = iss.str();
      for ( decltype( ss.size() ) j=0; j != ss.size(); ++j ){
	aScreen[ yoffs ][ j ] = ss[j];
      }
    }
  }
 
  return;
}

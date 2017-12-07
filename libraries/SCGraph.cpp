
#include <iostream>
#include <iomanip>
#include <algorithm>
#include "SCGraph.h"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::min_element;
using std::max_element;
using std::scientific;
using std::setw;
using std::setprecision;
using namespace SC;

//////////////////////////////////////////////////////////////////////////////////////////////
void SC::GraphScreenClear( std::vector< std::string >  & aScreen, 
		       const unsigned ax, const unsigned ay ){
  //std::string spaces( ax, ' ' );
  aScreen.clear();
  for ( std::vector<double>::size_type i = 0 ; i != ay; ++i ){
    aScreen.push_back( std::string( ax, ' ')  );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////
Graph::Graph(){
  fMarker = '*';
  return;
}

//////////////////////////////////////////////////////////////////////////////////////////////
Graph::Graph( const SS & atitle, const SS & axlabel, const SS & aylabel ) :
  fTitle ( atitle ) {
  fMarker = '*';
  fXax.SetLabel( axlabel );
  fXax.SetHorizontal();
  fYax.SetLabel( aylabel );
  fYax.SetVertical();
  return;
}

//////////////////////////////////////////////////////////////////////////////////////////////
Graph::Graph( const SS & atitle, const SS & axlabel, const SS & aylabel,   
	      const VD &ax, const VD &ay, const VD &ady ) : 
  fTitle( atitle ), fX( ax ), fY( ay ), fdY( ady ) {
  fMarker = '*';
  fXax.SetLabel( axlabel );
  fXax.SetHorizontal();
  fYax.SetLabel( aylabel );
  fYax.SetVertical();
  ResetAxisRanges();
  return;
}

//////////////////////////////////////////////////////////////////////////////////////////////
Graph::Graph( const SS & atitle, const SS & axlabel, const SS & aylabel,   
	      const unsigned an, const double ax[], const double ay[], const double ady[] ) : fTitle( atitle ) {
  fMarker = '*';
  for ( unsigned i = 0; i != an; ++i ){
    fX.push_back( ax[ i ] );
    fY.push_back( ay[ i ] );
    fdY.push_back( ady[ i ] );
  }
  fXax.SetLabel( axlabel );
  fXax.SetHorizontal();
  fYax.SetLabel( aylabel );
  fYax.SetHorizontal();
  ResetAxisRanges();
  return;
}

//////////////////////////////////////////////////////////////////////////////////////////////
void Graph::ResetAxisRanges(){
  fXax.SetRange( *min_element( fX.begin(), fX.end() ),
		 *max_element( fX.begin(), fX.end() ) );
  double errmax = *max_element( fdY.begin(), fdY.end() ) ; 
  fYax.SetRange( *min_element( fY.begin(), fY.end() )-errmax,
		 *max_element( fY.begin(), fY.end() )+errmax );
  return;
}

//////////////////////////////////////////////////////////////////////////////////////////////
void Graph::DataCin(){
  fX.clear();
  fY.clear();
  fdY.clear();
  double x,y,dy=-1.;
  do {
    if ( dy >= 0. ){
      fX.push_back( x );
      fY.push_back( y );
      fdY.push_back( dy );
    }
    if ( dy < 0. ||  cin.peek() == '\n' ){
      cout << "Input values for x y dy (dy=-ve to end):" << endl;
    }
  } while ( cin >> x >> y >> dy && dy >= 0.0 );
  ResetAxisRanges();
  return;
}


//////////////////////////////////////////////////////////////////////////////////////////////
void Graph::SetData( const VD &ax, const VD &ay, const VD &ady ) {
  fX = ax ;
  fY = ay ;
  fdY = ady ;
  ResetAxisRanges();
  return;
}


//////////////////////////////////////////////////////////////////////////////////////////////
void Graph::SetData( const unsigned an, const double ax[], const double ay[], const double ady[] ){
  fX.clear();
  fY.clear();
  fdY.clear();
  for ( unsigned i = 0 ; i < an ; ++i ){
    fX.push_back( ax[ i ] );
    fY.push_back( ay[ i ] );
    fdY.push_back( ady[ i ] );
  }
  ResetAxisRanges();
  return;
}


//////////////////////////////////////////////////////////////////////////////////////////////
void Graph::SetAxes( const Axis & axx, const Axis & axy ) { 
  fXax = axx ;
  fYax = axy ; 
  return;
}


//////////////////////////////////////////////////////////////////////////////////////////////
void Graph::SetXaxis( const Axis & axx ) {
  fXax = axx ;
  return;
}

//////////////////////////////////////////////////////////////////////////////////////////////
void Graph::SetYaxis( const Axis & axy ) {
  fYax = axy ;
  return;
}

//////////////////////////////////////////////////////////////////////////////////////////////
void Graph::GetAxes( Axis & xax, Axis & yax ){
  xax = fXax;
  yax = fYax;
  return;
}

//////////////////////////////////////////////////////////////////////////////////////////////
void Graph::SetMarker( const char amk ) {
  fMarker = amk;
  return;
}


//////////////////////////////////////////////////////////////////////////////////////////////
void Graph::Draw( std::vector< SS > &aScreen ){
  auto hh = aScreen.size();
  if ( hh < kMinAxisLen ) {
    #ifndef NDEBUG
    cerr << __func__ << " hh = " << hh << " < "
	 << kMinAxisLen << " screen too small! " << endl;
    #endif
    return;
  }
  auto ww = aScreen[0].size();
  if ( ww < kMinAxisLen ) {
    #ifndef NDEBUG
    cerr << __func__ << " ww = " << ww << " < "
	 << kMinAxisLen << " screen too small! " << endl;
    #endif
    return;
  }
  // Draw the title
  auto titlen = fTitle.size();
  unsigned itmin = 0;
  auto itmax=titlen;
  if ( titlen > ww ){
    itmax = ww;
  } else {
    itmin = (ww-titlen)/2;
    itmax = itmin + titlen;
  }
  for ( unsigned i=itmin ; i !=itmax; ++i ){
    aScreen[0][i] = fTitle[i-itmin];
  }

  // Draw the axes
  fXax.Draw( aScreen );
  fYax.Draw( aScreen );
  
  // Draw the data points
  unsigned ix = 0, iy = 0, iymin = 0, iymax = 0;
  for ( decltype( fX.size() ) i=0; i != fX.size(); ++i ){
    ix = fXax.GetLoc( aScreen, fX[i] );
    iy = fYax.GetLoc( aScreen, fY[i] );
    iymin = fYax.GetLoc( aScreen, fY[i] - fdY[i] );
    iymax = fYax.GetLoc( aScreen, fY[i] + fdY[i] );
    if ( ix < ww && iy < hh ){
      aScreen[ iy ][ ix ] = fMarker;
      if ( iymin < hh-3 && iymin != iy ) aScreen[ iymin ][ ix ] = '-';
      if ( iymax < hh-3 && iymax != iy ) aScreen[ iymax ][ ix ] = '-';
    }
  }
  
  // Flush the screen
  for ( auto line : aScreen ){
    cout << line << endl;
  }
  return;
}

//////////////////////////////////////////////////////////////////////////////////////////////
void Graph::Print(){
  cout << scientific;
  cout << setprecision(2);
  cout << "    x          y      +-     dy " <<endl;
  for ( decltype( fX.size() ) i=0; i != fX.size(); ++i ){
    cout << setw(9) << fX[i] << "  "
	 << setw(9) << fY[i] << " +- "
	 << setw(9) << fdY[i] <<endl;
  }
  return;
}

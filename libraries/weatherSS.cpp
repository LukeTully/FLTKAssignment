
/*
 * weatherSS.cpp
 * Example using istringstream and ostringstream
 * for processing a line from a file
 *
 * Author: Blair Jamieson
 * Date:   Oct. 16, 2016
 *
 */

#include <cmath>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// structure to hold all weather
// information read from file
struct WeatherInfo{
  string station;
  float  Tmean;
  float  Tmax;
  float  Tmin;
  float  Precip_mm;
  float  Precip_days;
};

// readWeather takes istream object to read from
// and reads in one weather record into w
istream & readWeather( istream& is, WeatherInfo &w ){
  is >> w.station >> w.Tmean >> w.Tmax >> w.Tmin
     >> w.Precip_mm >> w.Precip_days;
  return is;
}

// print a weather record w to output stream os
ostream & printWeather( ostream& os, const WeatherInfo & w ){
  // Note first use of formatted output to line up output. std::setw
  // from <iomanip> is used to set the minimum width of the next
  // value printed out
  os   << "station: " << setw(20) << w.station
       << " Tmean=" << setw(4) << w.Tmean
       << " Tmax=" << setw(4) << w.Tmax
       << " Tmin=" << setw(4) << w.Tmin
       << " Precipitation=" << setw(6) << w.Precip_mm << " mm"
       << " over " << w.Precip_days << " days" 
       << endl;
  return os;
}

// check weather record in w and print formatted string to 
// output stream good if it is a good reading, or to bad if it 
// is a bad reading
void checkRecord( ostream & good, ostream & bad, const WeatherInfo &w ){
  if ( w.Tmean < -50.0 || w.Tmean > 50.0 ||
       w.Tmin  < -50.0 || w.Tmin  > 50.0 ||
       w.Tmax  < -50.0 || w.Tmax  > 50.0 ||
       w.Precip_mm < 0.0 || w.Precip_mm > 20000.0 ||
       w.Precip_days < 0 || w.Precip_days > 31 ) {
    //  bad reading
    printWeather( bad, w );
  } else {
    printWeather( good, w );
  }
  return;
}


int main(){
  // open input file with the weather readings
  ifstream fin("weather.txt");
  string line; // line to read into from file
  // make a vector to hold weather records
  vector< WeatherInfo > weather;
  // read input one line at a time until fin reaches
  // end of file
  while ( getline( fin, line ) ){
    WeatherInfo wi; // object to hold current record
    istringstream iss ( line ); // bind iss to line read
    if ( readWeather( iss, wi ) ) // process string
      weather.push_back( wi ); // if process succeeds push into vector
  } 

  // loop over records and print to screen
  // to check that all records are okay
  for ( auto record : weather ) {
    printWeather( cout, record );
  }

  fin.close();
  // now test file with bad readings...
  fin.open("weather_werrors.txt");
  if ( !fin ){
    cerr<<"Error opening weather_werrors.txt"<<endl;
  }
  ostringstream formatted, badNums;
  while ( getline( fin, line ) ){
    cout << "got line: "<< line << endl;
    WeatherInfo wi; // object to hold current record
    istringstream iss ( line ); // bind iss to line read
    if ( readWeather( iss, wi ) ) {
      // print formatted weather info 
      // into ostringstream of good or bad values
      checkRecord( formatted, badNums, wi );
    }
  }

  // write formatted output to file
  ofstream fgood("good.txt");
  ofstream fbad("bad.txt");
  if ( fgood ) fgood << formatted.str() << flush;
  if ( fbad ) fbad << badNums.str() << flush;


  cout << "default: " << 100 * acos(-1) << endl;
  cout << "scientific: " << scientific << 100 * acos(-1) << endl;
  cout << "fixed: " << fixed << 100 * acos(-1) << endl;
  // hexfloat not supported
  //cout << "hex: " << hexfloat << 100 * acos(-1) << endl;
  // defaultfloat not supported
  //cout << "back to default " << defaultfloat << 100 * acos(-1) << endl; 
  cout.unsetf(std::ios_base::floatfield);
  cout << "back to default " << 100 * acos(-1) << endl;
  return 0;
}


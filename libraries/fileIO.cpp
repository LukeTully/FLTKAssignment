/*
 * fileIO.cpp
 * Simple example using iostream objects.
 * Read and write some dates from file
 *
 * Author: Blair Jamieson
 * Date:   Oct. 16, 2016
 *
 */

// include files so we can use the Date class again
#include "std_lib_facilities.h"
#include "Chrono.h"

using namespace Chrono;

// askDate prints message asking for date
ostream & askDate( ostream &os ){
  os << "Enter a date YYYY/MM/DD: ";
  return os;
}

// readDate takes input stream and reads in a date
istream &readDate( istream &is, Date &d ){
  int ad, am, ay;
  char c;
  if ( is >> ay >> c >> am >> c >> ad ){
    d = Date{ ay, Date::Month(am), ad };
  }
  return is;
}

// writeDate takes output stream and writes a date
ostream &writeDate( ostream &os, const Date &d ){
  os << d.year() << '/' << d.month() << '/' << d.day() << ' ';
  return os;
}


int main(){

  // file-stream to read from:
  ifstream fin("indates.txt");
						
  // file-stream to write to:
  ofstream fout("outdates.txt");
  
  // string-stream to read from:
  istringstream adate{"2012/11/04"};

  Date dfromfile, dfromstring;
  
  // put string to file
  fout << adate.str() << ' ' << endl;
  cout << "Date string is " << adate.str() << endl;
  // copy string into Date object
  if ( readDate( adate, dfromstring ) ){
    writeDate( fout, dfromstring );
    cout << "Date read from string is ";
    writeDate( cout, dfromstring );
    cout << endl;
  }

  // Read file of input dates
  while ( readDate( fin, dfromfile ) ){
    // write following date to file
    writeDate( fout, ++dfromfile );
    // also write same date to screen
    cout << "Date put to file ";
    writeDate( cout, dfromfile );
    cout << endl;
  }

  // Read date from user and add to output file
  stringstream datesread; // input or output string stream
  vector<Date> dates;
  Date aindate; // variable to read date into
  cout << "Enter default date ";
  writeDate( cout, aindate );
  cout << " to end date entries " << endl;
  do {
    if ( aindate != default_date () ){
      writeDate( fout, aindate );
      cout << "You entered ";
      writeDate( cout, aindate );
      cout << endl;
      // add date to string (write)
      writeDate( datesread, aindate );
    }
    askDate(cout);
  }  while (  readDate( cin, aindate ) && aindate != default_date() ); 


  cout<<"Dates entered, recalled method 1:"<<endl;
  cout << datesread.str() <<endl;

  cout<<"Dates entered add one day to each, recalled method 2:"<<endl;
  // below we read from string stream
  while ( readDate( datesread, aindate ) ){
    writeDate( cout, ++aindate );
  }
  cout << endl;

  // close output file
  fout.close();
  // open the output file to check / read its contents
  ifstream incheck;
  incheck.open( "outdates.txt" );
  if ( !incheck.is_open() ){
    cout << "Failed to open outdates.txt" << endl;
  }
  while ( readDate( incheck, aindate ) ){
    cout << "read date: ";
    writeDate( cout, aindate );
    cout <<endl;
  }
  // test state of incheck stream:
  if ( incheck.fail() )
    cout << "Fail on reading date from outdates.txt" << endl;
  if ( incheck.bad() )
    cout << "Bad reading from outdates.txt" << endl;
  if ( incheck.eof() )
    cout << "Reached end of file outdates.txt" << endl;

  return 0;
}

  










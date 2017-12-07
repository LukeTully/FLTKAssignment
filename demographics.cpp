#include "demographics.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>

using namespace std;

/* Operator overload implementations */

// Streaming in to Demographic
istream& operator>>(istream& is, Demographic& demo) {
  is >> demo.yr;
  parseSpecialInt(is, demo.births);
  parseSpecialInt(is, demo.deaths);
  parseSpecialInt(is, demo.emmigrants);
  parseSpecialInt(is, demo.immigrants);
  parseSpecialInt(is, demo.popGrowth);
  parseSpecialInt(is, demo.population);
  return is;
}

// Streaming out from a demographic
ostream& operator<<(ostream& os, Demographic& demo) {
  os << demo.yr.end << " " << demo.births << " " << demo.deaths << " "
     << demo.emmigrants << " "
     << "\n";
  return os;
}

// Streaming in to a YearRange
istream& operator>>(istream& is, YearRange& yr) {
  char ch;
  const char delimiter = '-';
  const char* yearContainer;

  int yearStart = 0;
  int yearEnd = 0;

  // Get the current year
  time_t t = time(NULL);
  tm* timePtr = localtime(&t);
  int maxYear = timePtr->tm_year + 1900;
  int minYear = 1700;

  while (is >> ch) {
    if (ch == delimiter) {
      continue;  // Found the deliminator, carry on
    }

    // Might be a year
    is.unget();
    if (yearStart > minYear) {
      is >> yearEnd;
      break;
    } else {
      is >> yearStart;
    }
  }
  if (!is) return is;
  if (yearStart >= minYear && yearEnd <= maxYear) {
    yr.start = yearStart;
    yr.end = yearEnd;
  } else {
    is.clear(ios_base::failbit);
  }

  // Find the relevant information
  return is;
}

// Streaming out from a YearRange
ostream& operator<<(ostream& os, YearRange& yr) {
  // Hyphenate the year range
  os << yr.start << '-' << yr.end;
  return os;
}

// Parse a year that has comma delimited thousands digits in string form
istream& parseSpecialInt(istream& is, int& numeric) {
  char ch;

  // Where should we stop parsing the stream?
  const char delimiter = ',';
  const char terminator = '"';
  int termCount = 0;
  int maxTermCount = 2;
  int result = 0;
  string strResult("");
  while (is >> ch && termCount < maxTermCount) {
    switch (ch) {
      case terminator:
        termCount++;
      case delimiter:
        if (termCount == 1) {
          result *= 1000;
        }
        continue;
      default:
        // Determine if the current char is a number
        is.unget();
        int temp;
        is >> temp;
        result += temp;
    }
    if (termCount == 0) {
      break;
    }
  }
  numeric = result;

  if (!is && !is.eof()) {
    is.clear(ios_base::badbit);  // totally invalid way to handle
  }
}

#ifndef DEMO_H
#define DEMO_H

#include <istream>
#include <ostream>

using namespace std;

struct YearRange {
  int start;
  int end;
};

struct Demographic {
  YearRange yr;
  int population;
  int popGrowth;
  int births;
  int deaths;
  int immigrants;
  int emmigrants;
  Demographic() {}
  Demographic(YearRange yr, int population, int popGrowth, int births,
              int deaths, int immigrants, int emmigrants)
      : yr(yr),
        population(population),
        popGrowth(popGrowth),
        births(births),
        deaths(deaths),
        immigrants(immigrants),
        emmigrants(emmigrants) {}
};

// Wrote my Scale class based on the textbook
class Scale {
  int cbase;
  int vbase;
  double scale;

 public:
  Scale(int b, int vb, double s) : cbase{b}, vbase{vb}, scale{s} {}
  int operator()(int v) const { return cbase + (v - vbase) * scale; }
};

// Operator overloads
istream& operator>>(istream& is, Demographic& demo);
ostream& operator<<(ostream& is, Demographic& demo);
istream& operator>>(istream& is, YearRange& yr);
ostream& operator<<(ostream& os, YearRange& yr);
istream& parseSpecialInt(istream& is, int& numeric);

// Utilty function for getting a subtring between two characters
void parseDelimitedSubstr(string& str, const char terminator);

#endif
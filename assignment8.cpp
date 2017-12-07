/*
    Assignment 8 - Question 1,2 - assignment8.cpp
    Student Number: 3020946
    Name: Lucas Martin-Tully
    Purpose: Read data from csv and plot it on a graph
*/

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <cmath>
#include <fstream>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>
#include "./libraries/Graph.h"
#include "./libraries/Point.h"
#include "Simple_window.h"
#include "demographics.h"

double slope(double x) { return x / 2; }
double sloping_cos(double x) { return cos(x) + slope(x); }
using namespace std;
int main() {
  // Set the csv filename
  const string filename = "sample.csv";

  // Open up a readstream to the csv file
  ifstream ist{filename};

  // Store each line as a Demographic
  vector<Demographic> demos;

  // Create a demographic object for each line in the csv file
  for (string line; getline(ist, line);) {
    // Turn the line string back into a stream
    istringstream iss(line);
    Demographic demo;

    // Stream into this demographic
    iss >> demo;

    // Store the demographic
    demos.push_back(demo);
  }

  // Close the filestream
  ist.close();

  // Construct a graph
  try {
    using namespace Graph_lib;

    // Ceiling and floor years that occur in the dataset
    constexpr int base_year = 1860;
    constexpr int end_year = 2000;

    constexpr int xmax = 600;  // window size
    constexpr int ymax = 400;

    constexpr int xoffset =
        100;  // distance from left-hand side of window to y axis
    constexpr int yoffset = 60;  // distance from bottom of window to x axis

    constexpr int xspace = 40;  // space beyond axis
    constexpr int yspace = 40;

    constexpr int ymaxval = 32000; // Largest number in the set

    constexpr int xlength = xmax - xoffset - xspace;  // length of axes
    constexpr int ylength = ymax - yoffset - yspace;

    constexpr double xscale = double(xlength) / (end_year - base_year);
    constexpr double yscale = double(ylength) / ymaxval;


    // Create x and y scales
    Scale xs{xoffset, base_year, xscale};
    Scale ys{ymax - yoffset, 0, -yscale};

    // Define a new Simple_window
    Simple_window win{Point{100, 100}, xmax, ymax, "Japanese Demographics"};

    // Create some axis
    Axis x{Axis::x,  // Orientation constant
           Point{xoffset, ymax - yoffset}, xlength, (end_year - base_year) / 20,
           "1860         1880        1900         1920         1940         "
           "1960        1980         2000"};
    Axis y{Axis::y, Point{xoffset, ymax - yoffset}, ylength, 10,
           "Population (\%)"};

    // Correct the positioning of the x axis label
    x.label.move(-70, 0);
    y.label.move(20, -10);

    Text t1(Point{xlength / 2, ymax - 10}, "Year Range (end)");
    win.attach(t1);

    // Draw some y axis labels
    for (size_t i = 0; i < 11; i++) {
      Text* ystep =
          new Text(Point(xoffset-55, ymax - yoffset - ((ylength/10) * i) + 4), std::to_string(i * (ymaxval/10)));
      win.attach(*ystep);
    }

    // Define open polylines for each dimension
    Open_polyline population;
    Open_polyline popGrowth;
    Open_polyline births;
    Open_polyline deaths;
    Open_polyline immigrants;
    Open_polyline emmigrants;

    // Give each dimension a different colour
    population.set_color(Color::dark_blue);
    popGrowth.set_color(Color::dark_red);
    births.set_color(Color::green);
    deaths.set_color(Color::red);
    immigrants.set_color(Color::dark_green);
    emmigrants.set_color(Color::dark_magenta);

    for (Demographic demo : demos) {
      // Get the x coord for the year of the current demographic
      const int x = xs(demo.yr.end);

      // Add points to each dimension's polyline according to the associated
      // year
      births.add(Point{x, ys(demo.births)});
      population.add(Point{x, ys(demo.population)});
      popGrowth.add(Point{x, ys(demo.popGrowth)});
      births.add(Point{x, ys(demo.births)});
      deaths.add(Point{x, ys(demo.deaths)});
      immigrants.add(Point{x, ys(demo.immigrants)});
      emmigrants.add(Point{x, ys(demo.emmigrants)});
    }

    // Attach all Open_polylines to the window
    win.attach(population);
    win.attach(popGrowth);
    win.attach(births);
    win.attach(deaths);
    win.attach(immigrants);
    win.attach(emmigrants);

    // Attach all Axis to the window
    win.attach(x);
    win.attach(y);

    win.wait_for_button();
  } catch (exception& e) {
    cerr << "exception: " << e.what() << endl;
    keep_window_open();
  } catch (...) {
    cerr << "exception\n";
    keep_window_open();
  }

  return 0;
}

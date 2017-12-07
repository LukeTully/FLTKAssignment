// Chapter 12, drill

#include <cmath>
#include <iostream>
#include "Graph.h"
#include "Simple_window.h"

#define _USE_MATH_DEFINES ;

void drawEnclosedPolygon(int sides, double radius, int centerX, int centerY,
                         Closed_polyline &poly_rect) {
  // Draw polygon with colours
  constexpr float magic = 8.7000366625;

  float distance = radius / magic / std::cos(M_PI / sides);
  float x;
  float y;
  for (int i = 0; i < sides; i++) {
    x = distance * std::cos((2 * M_PI * i) / sides) + centerX;
    y = distance * std::sin((2 * M_PI * i) / sides) + centerY;
    poly_rect.add(Point(x, y));
  }
  poly_rect.set_style(Line_style(Line_style::solid, 1));
}

int main(int argc, char *argv[], char *envp[]) {
  try {
    using namespace Graph_lib;

    {
      Point tl(150, 150);
      Simple_window win(tl, 600, 400, "My simple window");

      constexpr float magic = 8.7000366625;

      int radius = 200;
      int sides = 5;  // Arbitrary outer starting point
      int minSides = 3;
      int centerX = 300;
      int centerY = 200;
      Closed_polyline *p1 = new Closed_polyline();

      drawEnclosedPolygon(minSides, radius, centerX, centerY, *p1);
      radius /= std::cos(M_PI / minSides);
      win.attach(*p1);
      minSides++;

      for (int i = minSides; i <= sides; i++) {
        Closed_polyline *p1 = new Closed_polyline();

        drawEnclosedPolygon(i, radius, centerX, centerY, *p1);
        Circle *d = new Circle(Point(centerX, centerY), radius / magic);
        radius /= std::cos(M_PI / i);

        win.attach(*d);
        win.attach(*p1);
      }
      Circle *d = new Circle(Point(centerX, centerY), radius / magic);
      win.attach(*d);
      win.wait_for_button();
    }
  } catch (exception &e) {
    cerr << "exception: " << e.what() << endl;
    keep_window_open();
  } catch (...) {
    cerr << "exception\n";
    keep_window_open();
  }

  return 0;
}

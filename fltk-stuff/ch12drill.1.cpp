// Chapter 12, drill
	
#include "Simple_window.h"
#include "Graph.h"
	
int main() {
  try {
    using namespace Graph_lib;
	
    
    Point tl(150,150);
    {
      Simple_window w(tl,600,400,"Empty window");
      w.wait_for_button();
    }

    {
      Simple_window win(tl,600,400,"My simple window");
      Graph_lib::Polygon tri;
      tri.add( Point{300,200} );
      tri.add( Point{350,100} );
      tri.add( Point{400,200} );
      tri.set_color( Color::red );
      win.attach( tri );
      win.wait_for_button();
    }

    {
      Simple_window win(tl,600,400,"My simple window");
      Axis xa(Axis::x,Point(20,330),300,10,"x-axis");
      win.attach(xa);
      win.set_label("Window with x-axis");
      win.wait_for_button();
    }

    {
      Simple_window win(tl,600,400,"My simple window");
      Axis xa(Axis::x,Point(20,330),300,10,"x-axis");
      Axis ya(Axis::y,Point(20,330),280,30,"y-axis");
      ya.set_color(Color::dark_yellow);
      ya.label.set_color(Color::dark_magenta);
      win.set_label("Window with axes");
      win.attach(xa);
      win.attach(ya);
      win.wait_for_button();
    }

    {	
      Simple_window win(tl,600,400,"My simple window");
      Axis xa(Axis::x,Point(20,330),300,10,"x-axis");
      Axis ya(Axis::y,Point(20,330),280,30,"y-axis");
      ya.set_color(Color::dark_yellow);
      ya.label.set_color(Color::dark_magenta);
      win.attach(xa);
      win.attach(ya);

      Function f(sin,0,100,Point(20,300),1000,50,50);
      win.attach(f);
      win.set_label("Window with axes and function");
      f.set_color(Color::blue);
      win.wait_for_button();	

    }
    
    {
      Simple_window win(tl,600,400,"My simple window");
      Axis xa(Axis::x,Point(20,330),300,10,"x-axis");
      Axis ya(Axis::y,Point(20,330),280,30,"y-axis");
      ya.set_color(Color::dark_yellow);
      ya.label.set_color(Color::dark_magenta);
      win.attach(xa);
      win.attach(ya);

      Function f(sin,0,100,Point(20,300),1000,50,50);
      win.attach(f);
      win.set_label("Window with axes and function");
      f.set_color(Color::blue);

      Graph_lib::Polygon poly;
      poly.add(Point(300,200));
      poly.add(Point(275,175));
      poly.add(Point(350,100));
      poly.add(Point(425,175));
      poly.add(Point(400,200));
	
      poly.set_color(Color::dark_blue);
      poly.set_style(Line_style::dot);
      win.attach(poly);
	
      Graph_lib::Rectangle r(Point(200,200),100,30);
      win.attach(r);
      win.set_label("Added closed polygon rectangle");
      
      Closed_polyline poly_rect;
      poly_rect.add(Point(100,50));
      poly_rect.add(Point(200,50));
      poly_rect.add(Point(200,120));
      poly_rect.add(Point(100,100));
      win.attach(poly_rect);
	
      poly_rect.add(Point(125,75));

      r.set_fill_color(Color::yellow);
      poly_rect.set_style(Line_style(Line_style::dashdotdot,2));
      poly_rect.set_style(Line_style(Line_style::dashdot,4));
      poly_rect.set_fill_color(Color::green);
      Text t(Point(150,150),"Hello, customised world!");
      win.attach(t);
      t.set_font(Graph_lib::Font::helvetica_italic);
      t.set_font_size(50);
      


      Image ii(Point(100,50),"LiGlassPhoto.jpg");
      win.attach(ii);
      ii.move(250,150);

      Circle c(Point(100,200),50);
      Graph_lib::Ellipse e(Point(100,200),75,25);
      e.set_color(Color::dark_red);
      Mark m(Point(100,200),'X');
	
      ostringstream oss;
      oss << "screen size: " << x_max() << "*" << y_max()
	  << "; window size: " << win.x_max() << "*" << win.y_max();
      Text sizes(Point(100,20),oss.str());
	
      Image cal(Point(415,25),"hyperklogo.jpg");
      cal.set_mask(Point(40,40),200,150);
	
      win.attach(c);
      win.attach(m);
      win.attach(e);
      win.attach(sizes);
      win.attach(cal);
      win.set_label("A very busy window!");
     
      win.wait_for_button();
    }
    
  }
  catch (exception& e) {
    cerr << "exception: " << e.what() << endl;
    keep_window_open();
  }
  catch (...) {
    cerr << "exception\n";
    keep_window_open();
  }
  
  return 0;
}

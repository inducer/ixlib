// ----------------------------------------------------------------------------
//  Description      : Generic drawing functions
// ----------------------------------------------------------------------------
//  (c) Copyright 2000 by iXiONmedia, all rights reserved.
// ----------------------------------------------------------------------------




#ifndef IXLIB_DRAWING_FUNCTIONS
#define IXLIB_DRAWING_FUNCTIONS




#include <ixlib_polygon.hpp>




namespace ixion {
  /**
  A namespace containing functions that implement drawing primitives on
  a "Target" object that must have the following methods:
  <ul>
    <li> setPixel(x,y)
    <li> drawHLine(x1,y,x2) draws [x1,x2)
    <li> drawVLine(x,y1,y2) draws [y1,y2)
    </ul>
    
  Further, the Target interface must be stateful with respect to drawing modes
  and colors (i.e. these cannot be passed through these functions).
  */
  namespace drawing_functions {
    /**
    Draws a line from [(x1,y1),(x2,y2)), i.e. leaves out the last pixel.
    Set manually if needed.
    
    This is done to allow faciliating the drawing of multiple lines
    in-a-row.
    */
    template<class Target>
    void drawLine(Target &target,int x1,int y1,int x2,int y2);
    
    template<class Target>
    void drawBox(Target &target,int x1,int y1,int x2,int y2);
    template<class Target>
    void fillBox(Target &target,int x1,int y1,int x2,int y2);
    
    template<class Target>
    void drawCircle(Target &target,int x,int y,int r);
    template<class Target>
    void fillCircle(Target &target,int x,int y,int r);

    template<class Target>
    void drawEllipse(Target &target,int x,int y,int r_x,int r_y);
    template<class Target>
    void fillEllipse(Target &target,int x,int y,int r_x,int r_y);
    
    template<class Target,class T>
    void drawPolygon(Target &target,polygon<T> const &poly);
    template<class Target,class T>
    void fillPolygon(Target &target,polygon<T> const &poly);
    }
  }





template<class Target>
void ixion::drawing_functions::drawLine(Target &target,int x1,int y1,int x2,int y2) {
  int dx = abs(x2-x1);
  int dy = abs(y2-y1);
  int npixel;
  int dinc1;
  int dinc2;
  int xinc1;
  int xinc2;
  int yinc1;
  int yinc2;
  int x;
  int y;
  int d;

  if (dx >= dy) {
    npixel = dx;
    d = (2*dy)-dx;
    dinc1 = dy << 1;
    dinc2 = (dy-dx) << 1;
    xinc1 = 1;
    xinc2 = 1;
    yinc1 = 0;
    yinc2 = 1;
    }
  else {
    npixel = dy;
    d = (2*dx)-dy;
    dinc1 = dx << 1;
    dinc2 = (dx-dy) << 1;
    xinc1 = 0;
    xinc2 = 1;
    yinc1 = 1;
    yinc2 = 1;
    }

  if (x1>x2) {
    xinc1 = -xinc1;
    xinc2 = -xinc2;
    }
  if (y1>y2) {
    yinc1 = -yinc1;
    yinc2 = -yinc2;
    }

  x = x1;
  y = y1;
  for (int i=0; i < npixel; i++) { 
    target.setPixel(x,y);
    if (d<0) {
      d += dinc1;
      x += xinc1;
      y += yinc1;
      }
    else {
      d += dinc2;
      x += xinc2;
      y += yinc2;
      }
    }
  }




template<class Target>
void ixion::drawing_functions::drawBox(Target &target,int x1,int y1,int x2,int y2) {
  // * *** *
  // *     *
  // * *** *
  target.drawVLine( x1, y1, y2 + 1 ); // left
  target.drawVLine( x2, y1, y2 + 1 ); // right
  target.drawHLine( x1+1, y1, x2 ); // top
  target.drawHLine( x1+1, y2, x2 ); // bottom
  }




template<class Target>
void ixion::drawing_functions::fillBox(Target &target,int x1,int y1,int x2,int y2) {
  for (int y = y1;y < y2;y++)
    target.drawHLine(x1,y,x2);
  }




// The following notation is used throughout the circle drawing code:
//  81
// 7  2
// 6  3
//  54
    



template<class Target>
void ixion::drawing_functions::drawCircle(Target &target,int x,int y,int r) {
  int counter = r;
  int xcount = 0;
  int ycount = r;

  target.setPixel(x + xcount,y - ycount); // 1
  target.setPixel(x - xcount,y + ycount); // 5
  target.setPixel(x - ycount,y - xcount); // 7
  target.setPixel(x + ycount,y + xcount); // 3
  
  counter -= xcount + xcount + 1;
  xcount++;

  while(xcount < ycount) {
    if (counter < 0) {
      ycount--;
      counter += ycount + ycount;
      }
    
    target.setPixel(x + xcount,y - ycount); // 1
    target.setPixel(x - xcount,y - ycount); // 8
    target.setPixel(x + xcount,y + ycount); // 4
    target.setPixel(x - xcount,y + ycount); // 5
    target.setPixel(x + ycount,y - xcount); // 2
    target.setPixel(x - ycount,y - xcount); // 7
    target.setPixel(x + ycount,y + xcount); // 3
    target.setPixel(x - ycount,y + xcount); // 6

    counter -= xcount + xcount + 1;
    xcount++;
    }
  }




template<class Target>
void ixion::drawing_functions::fillCircle(Target &target,int x,int y,int r) {
  int counter = r;
  int xcount = 0;
  int ycount = r;
  bool ycount_changed = true;

  target.drawHLine(x - ycount,y - xcount,x + ycount); // 7 --> 2
  counter -= xcount + xcount + 1;
  xcount++;

  while(xcount < ycount) {
    if (counter < 0) {
      ycount--;
      ycount_changed = true;
      
      counter += ycount + ycount;
      }

    if (ycount_changed) {
      target.drawHLine(x - xcount,y - ycount,x + xcount); // 8 --> 1
      target.drawHLine(x - xcount,y + ycount,x + xcount); // 5 --> 4
      ycount_changed = false;
      }
    target.drawHLine(x - ycount,y - xcount,x + ycount); // 7 --> 2
    target.drawHLine(x - ycount,y + xcount,x + ycount); // 6 --> 3
    counter -= xcount + xcount + 1;
    xcount++;
    }
  }




template<class Target>
void ixion::drawing_functions::drawEllipse(Target &target,int x,int y,int r_x,int r_y) {
  int const fix_digits = 10;

  if (r_x > r_y) {
    int counter = r_x;
    int xcount = 0;
    int ycount = r_x;
    int factor = (r_y << fix_digits) / r_x;
  
    target.setPixel(x + r_x,y); // S
    target.setPixel(x - r_x,y); // N
    target.setPixel(x,y - r_y); // W
    target.setPixel(x,y + r_y); // E
    
    int lastline_ycount = ycount;
    int last_xcount_scaled = (xcount * factor) >> fix_digits;
    counter -= xcount + xcount + 1;
    xcount++;
    
    while(xcount < ycount) {
      if (counter < 0) {
        ycount--;
        counter += ycount + ycount;
        }
      
      int ycount_scaled = (ycount * factor) >> fix_digits;
      
      target.setPixel(x + xcount,y - ycount_scaled); // 1
      target.setPixel(x - xcount,y - ycount_scaled); // 8
      target.setPixel(x + xcount,y + ycount_scaled); // 4
      target.setPixel(x - xcount,y + ycount_scaled); // 5

      int xcount_scaled = (xcount * factor) >> fix_digits;
      
      if (xcount_scaled != last_xcount_scaled) {
        if (lastline_ycount == ycount) {
          target.setPixel(x + ycount,y + xcount_scaled);
          target.setPixel(x - ycount,y + xcount_scaled);
          target.setPixel(x + ycount,y - xcount_scaled);
          target.setPixel(x - ycount,y - xcount_scaled);
	  }
        else {
          target.drawHLine(x + ycount,y + xcount_scaled,x + lastline_ycount);
          target.drawHLine(x - lastline_ycount + 1,y + xcount_scaled,x - ycount + 1); 
          target.drawHLine(x + ycount,y - xcount_scaled,x + lastline_ycount);
          target.drawHLine(x - lastline_ycount + 1,y - xcount_scaled,x - ycount + 1); 
	  }

        last_xcount_scaled = xcount_scaled;
        lastline_ycount = ycount;
        }
      
      counter -= xcount + xcount + 1;
      xcount++;
      }
    }
  else {
    int counter = r_y;
    int xcount = 0;
    int ycount = r_y;
    int factor = (r_x << fix_digits) / r_y;
  
    target.setPixel(x + r_x,y); // S
    target.setPixel(x - r_x,y); // N
    target.setPixel(x,y - r_y); // W
    target.setPixel(x,y + r_y); // E
    
    int lastline_ycount = ycount;
    int last_xcount_scaled = (xcount * factor) >> fix_digits;
    counter -= xcount + xcount + 1;
    xcount++;
    
    while(xcount < ycount) {
      if (counter < 0) {
        ycount--;
        counter += ycount + ycount;
        }
      
      int ycount_scaled = (ycount * factor) >> fix_digits;
      
      target.setPixel(x + ycount_scaled,y - xcount);
      target.setPixel(x - ycount_scaled,y - xcount);
      target.setPixel(x + ycount_scaled,y + xcount);
      target.setPixel(x - ycount_scaled,y + xcount);

      int xcount_scaled = (xcount * factor) >> fix_digits;
      
      if (xcount_scaled != last_xcount_scaled) {
        if (lastline_ycount == ycount) {
	  target.setPixel(x + xcount_scaled,y + ycount);
	  target.setPixel(x + xcount_scaled,y - ycount);
	  target.setPixel(x - xcount_scaled,y + ycount);
	  target.setPixel(x - xcount_scaled,y - ycount);
	  }
        else {
	  target.drawVLine(x + xcount_scaled,y + ycount,y + lastline_ycount);
	  target.drawVLine(x + xcount_scaled,y - lastline_ycount + 1,y - ycount + 1);
	  target.drawVLine(x - xcount_scaled,y + ycount,y + lastline_ycount);
	  target.drawVLine(x - xcount_scaled,y - lastline_ycount + 1,y - ycount + 1);
	  }

        last_xcount_scaled = xcount_scaled;
        lastline_ycount = ycount;
        }
      
      counter -= xcount + xcount + 1;
      xcount++;
      }
    }
  }




template<class Target>
void ixion::drawing_functions::fillEllipse(Target &target,int x,int y,int r_x,int r_y) {
  int const fix_digits = 10;
  if (r_x > r_y) {
    int counter = r_x;
    int xcount = 0;
    int ycount = r_x;
    int factor = (r_y << fix_digits) / r_x;
    
    int last_scaled_xcount = (xcount * factor) >> fix_digits;
    int last_scaled_ycount = (ycount * factor) >> fix_digits;
  
    target.drawHLine(x - r_x,y,x + r_x + 1);
    
    counter -= xcount + xcount + 1;
    xcount ++;
    
    while(xcount < ycount) {
      if (counter < 0) {
        ycount --;
        counter += ycount + ycount;
        }
  
      int scaled_xcount = (xcount * factor) >> fix_digits;
      int scaled_ycount = (ycount * factor) >> fix_digits;

      if (scaled_xcount != scaled_ycount && last_scaled_ycount != scaled_ycount) {
        target.drawHLine(x - xcount,y - scaled_ycount,x + xcount+1); // 8 --> 1
        target.drawHLine(x - xcount,y + scaled_ycount,x + xcount+1); // 5 --> 4
	last_scaled_ycount = scaled_ycount;
	}
      if (last_scaled_xcount != scaled_xcount) {
        target.drawHLine(x - ycount,y - scaled_xcount,x + ycount+1); // 7 --> 2
        target.drawHLine(x - ycount,y + scaled_xcount,x + ycount+1); // 6 --> 3
	last_scaled_xcount = scaled_xcount;
	}
  
      counter -= xcount + xcount + 1;
      xcount ++;
      }
    }
  else {
    int counter = r_y;
    int xcount = 0;
    int ycount = r_y;
    int factor = (r_x << fix_digits) / r_y;
    
    int last_scaled_xcount = (xcount * factor) >> fix_digits;
    int last_scaled_ycount = (ycount * factor) >> fix_digits;
  
    target.drawVLine(x,y - r_y,y + r_y + 1);
    
    counter -= xcount + xcount + 1;
    xcount ++;
    
    while(xcount < ycount) {
      if (counter < 0) {
        ycount --;
        counter += ycount + ycount;
        }
  
      int scaled_xcount = (xcount * factor) >> fix_digits;
      int scaled_ycount = (ycount * factor) >> fix_digits;

      if (scaled_xcount != scaled_ycount && last_scaled_ycount != scaled_ycount) {
	target.drawVLine(x + scaled_ycount,y - xcount,y + xcount + 1); // 2 --> 3
	target.drawVLine(x - scaled_ycount,y - xcount,y + xcount + 1); // 7 --> 6
	last_scaled_ycount = scaled_ycount;
	}
      if (last_scaled_xcount != scaled_xcount) {
	target.drawVLine(x + scaled_xcount,y - ycount,y + ycount + 1); // 1 --> 4
	target.drawVLine(x - scaled_xcount,y - ycount,y + ycount + 1); // 8 --> 5
	last_scaled_xcount = scaled_xcount;
	}
  
      counter -= xcount + xcount + 1;
      xcount ++;
      }
    }
  }




template<class Target,class T>
void ixion::drawing_functions::drawPolygon(Target &target,polygon<T> const &poly) {
  FOREACH_CONST(first_seg,poly,polygon<T>) {
    if ((*first_seg)->size() <= 1) continue;
    if ((*first_seg)->size() == 2) {
      drawLine(target,(*first_seg)->front()[0],(*first_seg)->front()[1],
        (*first_seg)->back()[0],(*first_seg)->back()[1]);
      target.setPixel((*first_seg)->back()[0],(*first_seg)->back()[1]);
      }

    // at least a triangle
    polygon_segment<T>::const_iterator 
      next = (*first_seg)->begin(),
      last = (*first_seg)->end(),
      previous = last-1;
    while (next != last) {
      drawLine(target,(*previous)[0],(*previous)[1],
        (*next)[0],(*next)[1]);
      previous = next;
      next++;
      }
    }
  }




namespace {
  template<class Target>
  class hline_routine {
      Target &Tgt;
    public:
      hline_routine(Target &tgt)
        : Tgt(tgt) {
	}
      void operator()(int x1,int y,int x2) const {
        Tgt.drawHLine(x1,y,x2);
        }
    };
  }
  



template<class Target,class T>
void ixion::drawing_functions::fillPolygon(Target &target,polygon<T> const &poly) {
  hline_routine<Target> hlr(target);
  poly.drawScanlines(hlr);
  }




#endif

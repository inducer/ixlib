// ----------------------------------------------------------------------------
//  Description      : Polygon handling
// ----------------------------------------------------------------------------
//  (c) Copyright 2000 by iXiONmedia, all rights reserved.
// ----------------------------------------------------------------------------




#ifndef IXLIB_POLYGON
#define IXLIB_POLYGON




#include <vector>
#include <ixlib_geometry.hpp>




namespace ixion {
  template<class T>
  class polygon_segment : public std::vector<coord_vector<T,2> > {
      // vertices are enumerated in counter-clockwise 
      // (mathematically positive) order
      // boolean operations depend on this
    public:
      typedef coord_vector<T,2>      vertex_2d;

    private:
      typedef std::vector<vertex_2d>      super;

    public:
      polygon_segment() {
        }
      polygon_segment(rectangle<T> const &src);
      polygon_segment(polygon_segment const &src) 
        : super(src) {
        }
  
      void push_back_c(T x,T y);
      void insert_c(typename super::iterator it,T x,T y);

      bool isPointInside(T x,T y);
      
      void removeCrossings();
      void makeConvexHull(polygon_segment &dest) const;
      void smooth(polygon_segment &dest) const;
      void subdivide(polygon_segment &dest) const;
      void translate(T x,T y);
  
      rectangle<T> getBoundingBox() const;
      vertex_2d getCenter() const;
      vertex_2d getWeightedCenter() const;
      vertex_2d getPointOnOutside() const;
    };




  template<class T>
  class polygon : public std::vector<polygon_segment<T> *> {
      typedef std::vector<polygon_segment<T> *>      super;
      
    public:
      typedef typename polygon_segment<T>::vertex_2d	vertex_2d;

    public:
      polygon() {
        }
      polygon(polygon const &src);
      polygon &operator=(polygon const &src);
      ~polygon();
  
      void clear();
      
      bool isPointInside(T x,T y);

      void smooth();
      void subdivide();
      void translate(T x,T y);
  
      void unite(polygon &dest,polygon const &src) const;
      void intersect(polygon &dest,polygon const &src) const;
      void subtract(polygon &dest,polygon const &subtrahend) const;
  
      rectangle<T> getBoundingBox() const;
      vertex_2d getCenter() const;
      vertex_2d getWeightedCenter() const;
  
      template<class HLineRoutine>
      void drawScanlines(HLineRoutine const &hlr,T step = 1) const;
      
    private:
      void freeSegments();
    };
  }




#endif

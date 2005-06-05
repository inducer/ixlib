// ----------------------------------------------------------------------------
//  Description      : Rectangular geometry
// ----------------------------------------------------------------------------
//  (c) Copyright 1997 by iXiONmedia, all rights reserved.
// ----------------------------------------------------------------------------




#include <ixlib_geometry.hpp>
#include <ixlib_numeric.hpp>




// rectangle -----------------------------------------------------------------
template <class T>
void ixion::rectangle<T>::unite(rectangle const &rect) {
  A[0] = NUM_MIN(A[0],rect.A[0]);
  A[1] = NUM_MIN(A[1],rect.A[1]);
  B[0] = NUM_MAX(B[0],rect.B[0]);
  B[1] = NUM_MAX(B[1],rect.B[1]);
  }




template <class T>
void ixion::rectangle<T>::intersect(rectangle<T> const &rect) {
  A[0] = NUM_MAX(A[0],rect.A[0]);
  A[1] = NUM_MAX(A[1],rect.A[1]);
  B[0] = NUM_MIN(B[0],rect.B[0]);
  B[1] = NUM_MIN(B[1],rect.B[1]);

  if (isEmpty()) clear();
  }




// region --------------------------------------------------------------------
template <class T>
void ixion::region<T>::add(rectangle<T> const &rect) {
  subtract(rect);
  Rects.push_back(rect);
  }




template <class T>
void ixion::region<T>::intersect(rectangle<T> const &rect) {
  iterator first = begin(),last = end();
  
  while (first != last) 
    first++->intersect(rect);
    
  deleteEmptyRectangles();
  }




template <class T>
void ixion::region<T>::subtract(rectangle<T> const &rect) {
  iterator first = begin(),last = end();

  std::vector< rectangle<T> > newrects;
  while (first != last) {
    if (rect.doesIntersect(*first)) {
      rectangle<T> upper(rect.A[0],first->A[1],rect.B[0],rect.A[1]);
      rectangle<T> lower(rect.A[0],rect.B[1],rect.B[0],first->B[1]);
      rectangle<T> left(first->A[0],first->A[1],rect.A[0],first->B[1]);
      rectangle<T> right(rect.B[0],first->A[1],first->B[0],first->B[1]);

      if (!upper.isEmpty()) newrects.push_back(upper);
      if (!lower.isEmpty()) newrects.push_back(lower);
      if (!left.isEmpty()) newrects.push_back(left);
      if (!right.isEmpty()) newrects.push_back(right);
      
      first++;
      }
    else 
      newrects.push_back(*first++);
    }
  Rects.swap(newrects);
  } 




template <class T>
void ixion::region<T>::deleteEmptyRectangles() {
  iterator first = begin(),last = end();

  std::vector< rectangle<T> > newrects;
  while (first != last) {
    if (!first->isEmpty()) newrects.push_back(*first);
    first++;
    }
  Rects.swap(newrects);
  }




template <class T>
bool ixion::region<T>::contains(coord_vector<T> const &point) const {
  const_iterator first = begin(),last = end();
  while (first != last) {
    if (first->doesContain(point)) return true;
    first++;
    }
  return false;
  }




template <class T>
bool ixion::region<T>::intersects(rectangle<T> const &rect) const {
  const_iterator first = begin(),last = end();
  while (first != last) {
    if (first->doesIntersect(rect)) return true;
    first++;
    }
  return false;
  }

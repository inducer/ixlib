// ----------------------------------------------------------------------------
//  Description      : Rectangular geometry.
// ----------------------------------------------------------------------------
//  (c) Copyright 1997 by iXiONmedia, all rights reserved.
// ----------------------------------------------------------------------------




#ifndef IXLIB_GEOMETRY
#define IXLIB_GEOMETRY




#include <cmath>
#include <vector>
#include <ixlib_base.hpp>
#include <ixlib_exgen.hpp>
#include <ixlib_numeric.hpp>




// coord_vector --------------------------------------------------------------------
namespace ixion {
  template <class T, int DIM = 2>
  class coord_vector {
    protected:
      T Data[DIM];
  
    public:
      coord_vector()
        { }
  
  /*    template <class InputIterator>
      coord_vector(InputIterator first,InputIterator last) { 
        for (int i=0; i<DIM; i++,first++) Data[i] = *first; 
        if (last != first) EX_THROW(Generic,EC_INDEX)
        }*/
  
      template <class TP>
      coord_vector(coord_vector<TP,DIM> const &src) {
        for (int i=0; i<DIM; i++) Data[i] = src[i]; 
        }
      
      coord_vector(T const x,T const y = 0,T const z = 0) { 
        Data[0] = x;
        if (DIM>=2) Data[1] = y;
        if (DIM>=3) Data[2] = z;
        }
  
      T &operator[](int const index)
        { return Data[index]; }
  
      T const &operator[](int const index) const 
        { return Data[index]; }
  
      int getDimension() const
        { return DIM;}
  
      template <class TP>
      bool operator==(coord_vector<TP, DIM> const &vec) const {
        for (int i=0; i<DIM; i++) {
          if (Data[i] != vec[i]) return false;
          }
        return true;
        }

      template <class TP>
      bool operator!=(coord_vector<TP, DIM> const &vec) const {
        for (int i=0; i<DIM; i++) {
          if (Data[i] != vec[i]) return true;
          }
        return false;
        }

      template <class TP>
      coord_vector &operator=(TP data[]) { 
        for (int i=0; i<DIM; i++) Data[i] = data[i]; 
        return *this;
        }
  
      template <class TP>
      coord_vector &operator=(coord_vector<TP, DIM> const &vec) { 
        for (int i=0; i<DIM; i++) Data[i] = vec[i]; 
        return *this;
        }
  
      coord_vector operator-() const {
        coord_vector result;
        for (int i=0; i<DIM; i++) result[i] = -Data[i];
        return result;
        }
  
      template <class TP>
      coord_vector &operator+=(coord_vector<TP> const &vec) { 
        for (int i=0; i<DIM; i++) Data[i] += vec[i]; 
        return *this;
        }
      template <class TP>
      coord_vector operator+(coord_vector<TP, DIM> const &vec) const {
        coord_vector result;
        for (int i=0; i<DIM; i++) result[i] = Data[i] + vec[i];
        return result;
        }
  
  
      template <class TP>
      coord_vector &operator-=(coord_vector<TP, DIM> const &vec) { 
        for (int i=0; i<DIM; i++) Data[i] -= vec[i]; 
        return *this;
        }
      template <class TP>
      coord_vector operator-(coord_vector<TP, DIM> const &vec) const {
        coord_vector result;
        for (int i=0; i<DIM; i++) result[i] = Data[i] - vec[i];
        return result;
        }
  
      coord_vector &operator*=(T scalar) { 
        for (int i=0; i<DIM; i++) Data[i] *= scalar; 
        return *this;
        }
      coord_vector operator*(T scalar) const {
        coord_vector result;
        for (int i=0; i<DIM; i++) result[i] = Data[i] * scalar;
        return result;
        }
  
      coord_vector &operator/=(T scalar) { 
        for (int i=0; i<DIM; i++) Data[i] /= scalar;
        return *this;
        }
      coord_vector operator/(T scalar) const {
        coord_vector result;
        for (int i=0; i<DIM; i++) result[i] = Data[i] / scalar;
        return result;
        }
  
      template <class TP>
      T operator*(coord_vector<TP, DIM> const &vec) const {
        T result = Data[0] * vec.Data[0];
        for (int i=1; i<DIM; i++) result += Data[i] * vec[i];
        return result;
        }
  
      void set(T const x,T const y = 0,T const z = 0) {
        Data[0] = x;
        if (DIM>=2) Data[1] = y;
        if (DIM>=3) Data[2] = z;
        }
        
      void move(T const x,T const y = 0,T const z = 0) {
        Data[0] += x;
        if (DIM>=2) Data[1] += y;
        if (DIM>=3) Data[2] += z;
        }
    };




  template <class T, int DIM>
  inline coord_vector<T,DIM> operator*(T scalar,coord_vector<T,DIM> const &vec) {
    return vec*scalar;
    }




  template<class T,int Dim>
  inline double getAngle(coord_vector<T,Dim> const &vec1,coord_vector<T,Dim> const &vec2) {
    double ip = vec1*vec2/(sqrt(vec1*vec1)*sqrt(vec2*vec2));
    return acos(ip);
    }
  
  
  
  
  template<class T>
  inline double getAngle(coord_vector<T,2> const &vec) {
    return atan2(double(vec[1]),double(vec[0]));
    }
  
  
  
  
// rectangle -----------------------------------------------------------------
  template <class T>
  struct rectangle {
    coord_vector<T> A,B;
  
    rectangle()
      { }
    rectangle(T ax, T ay, T bx, T by)
      : A(ax,ay),B(bx,by)
      { }
    rectangle(coord_vector<T> const &a,coord_vector<T> const &b)
      : A(a),B(b)
      { }
    template <class TP>
    rectangle(rectangle<TP> const &src)
      : A(src.A),B(src.B) {
      }
  
    template <class TP>
    rectangle &operator=(rectangle<TP> const &src) {
      A = src.A;
      B = src.B;
      return *this;
      }
  
    T width() const { 
      return B[0]-A[0]; 
      }
    T height() const { 
      return B[1]-A[1]; 
      }
    T area() const { 
      return width()*height(); 
      }
    bool contains(T x, T y) const { 
      return (A[0] <= x) && (x < B[0]) && (A[1] <= y) && (y < B[1]); 
      }
    bool contains(coord_vector<T> const &point) const { 
      return (A[0] <= point[0]) && (point[0] < B[0]) &&
          (A[1] <= point[1]) && (point[1] < B[1]); 
      }
    bool intersects(rectangle<T> const &rect) const { 
      return NUM_OVERLAP(A[0],B[0],rect.A[0],rect.B[0]) && 
          NUM_OVERLAP(A[1],B[1],rect.A[1],rect.B[1]); 
      }
    bool empty() const { 
      return (B[0] <= A[0]) || (B[1] <= A[1]); 
      }
  
    void clear() { 
      B = A; 
      }
  
    void set(T ax, T ay, T bx, T by) { 
      A.set(ax,ay); 
      B.set(bx,by); 
      }
    template <class TP>
    void set(coord_vector<TP> const &a,coord_vector<TP> const &b) { 
      A = a; B = b; 
      }
  
    void setSize(T sizex,T sizey) { 
      B = A + coord_vector<T>(sizex,sizey); 
      }
    template <class TP>
    void setSize(coord_vector<TP> const &p) {
      B = A+p;
      }
  
    void resize(T dx,T dy) { 
      B.move(dx,dy); 
      }
    template <class TP>
    void resize(coord_vector<TP> const &p) {
      B += p;
      }
  
    void move(T dx,T dy) {
      coord_vector<T> p(dx,dy);
      A += p; B += p;
      }
    template <class TP>
    void move(coord_vector<TP> const &p) {
      A += p; B += p;
      }
  
    void unite(rectangle const &rect);
    void intersect(rectangle const &rect);
  
    template <class TP>
    rectangle &operator+=(coord_vector<TP> const &p) {
      move(p);
      return *this;
      }
    template <class TP>
    rectangle operator+(coord_vector<TP> const &p) {
      rectangle copy(*this);
      copy.move(p);
      return copy;
      }
    template <class TP>
    rectangle &operator-=(coord_vector<TP> const &p) {
      move(p*(-1));
      return *this;
      }
    template <class TP>
    rectangle operator-(coord_vector<TP> const &p) {
      rectangle copy(*this);
      copy.move(p*(-1));
      return copy;
      }

    /// \deprecated use width() instead.
    T getSizeX() const { 
      return width(); 
      }
    /// \deprecated use height() instead.
    T getSizeY() const { 
      return height(); 
      }
    /// \deprecated use width() instead.
    T getWidth() const { 
      return width(); 
      }
    /// \deprecated use height() instead.
    T getHeight() const { 
      return height(); 
      }
    /// \deprecated use area() instead.
    T getArea() const { 
      return area(); 
      }
    /// \deprecated use contains() instead.
    bool doesContain(T x, T y) const { 
      return contains(x,y); 
      }
    /// \deprecated use contains() instead.
    bool doesContain(coord_vector<T> const &point) const { 
      return contains(point); 
      }
    /// \deprecated use intersects() instead.
    bool doesIntersect(rectangle<T> const &rect) const { 
      return intersects(rect); 
      }
    /// \deprecated use empty() instead.
    bool isEmpty() const { 
      return empty(); 
      }
    };




// region --------------------------------------------------------------------
  template <class T>
  class region {
    protected:
      std::vector< rectangle<T> > Rects;
  
    public:
      typedef typename std::vector< rectangle<T> >::iterator iterator;
      typedef typename std::vector< rectangle<T> >::const_iterator const_iterator;
      
      TSize size() const {
        return Rects.size();
        }
      iterator begin() { 
        return Rects.begin(); 
        }
      const_iterator begin() const { 
        return Rects.begin(); 
        }
      iterator end() { 
        return Rects.end(); 
        }
      const_iterator end() const { 
        return Rects.end(); 
        }
      
      void add(rectangle<T> const &rect);
      void intersect(rectangle<T> const &rect);
      void subtract(rectangle<T> const &rect);
      void operator+=(rectangle<T> const &rect) { 
        add(rect); 
        }
      void operator*=(rectangle<T> const &rect) { 
        intersect(rect); 
        }
      void operator-=(rectangle<T> const &rect) { 
        subtract(rect); 
        }
        
      bool contains(T x, T y) const { 
        return contains(coord_vector<T>(x,y)); 
        }
      bool contains(coord_vector<T> const &point) const;
      bool intersects(rectangle<T> const &rect) const;
      bool empty() const { 
        return Rects.empty(); 
        }
    
      void clear() { 
        Rects.clear(); 
        }
    
      /// \deprecated use contains() instead.
      bool doesContain(T x, T y) const { 
        return contains(coord_vector<T>(x,y)); 
        }
      /// \deprecated use contains() instead.
      bool doesContain(coord_vector<T> const &point) const {
        return contains(point);
	}
      /// \deprecated use intersects() instead.
      bool doesIntersect(rectangle<T> const &rect) const {
        return intersects(rect);
	}
      /// \deprecated use empty() instead.
      bool isEmpty() const { 
        return empty(); 
        }

    protected:
      void deleteEmptyRectangles();
    };
  }




#endif

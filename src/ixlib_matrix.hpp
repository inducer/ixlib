// ----------------------------------------------------------------------------
//  Description      : Matrix handling
// ----------------------------------------------------------------------------
//  (c) Copyright 2000 by iXiONmedia, all rights reserved.
// ----------------------------------------------------------------------------




#ifndef IXLIB_MATRIX
#define IXLIB_MATRIX



#include <cmath>
#include <iostream>
#include <ixlib_exgen.hpp>
#include <ixlib_array.hpp>
#include <ixlib_numeric.hpp>



 
namespace ixion {
  template <class T>
  struct number_traits {
    typedef T   number_type;
    typedef T   scalar_type;
    
    static const number_type zero = 0;
    
    static scalar_type norm(number_type value) {
      return NUM_ABS(value);
      }
    static number_type sqrt(number_type value) {
      return ::sqrt(value);
      }
    
    static void isRing();
    static void isField();
    static void isVectorSpace();
    };
  
  
  
  
  
  template <class T,class Traits = number_traits<T> >
  class matrix {
    protected:
      TSize                     Height,Width;
      auto_array<T>             Data;
    
    public:
      typedef Traits                            traits_type;
      typedef typename traits_type::number_type entry_type;
      typedef typename traits_type::scalar_type scalar_type;
      typedef T                                 *iterator;
      typedef T const                           *const_iterator;
    
      matrix(TSize height = 0,TSize width = 0);
      template<class InputIterator>
      inline matrix(TSize height,TSize width,InputIterator first);
      matrix(matrix const &src);
      
      matrix &operator=(matrix const &src);
      
      matrix &operator+=(matrix const &op2);
      matrix &operator-=(matrix const &op2);
      matrix &operator*=(matrix const &op2) {
        return operator=(operator*(op2));
        }
  
      matrix &operator*=(scalar_type scalar);
  
      matrix operator-() const {
        matrix copy(*this);
        copy *= -1;
        return copy;
        }
      matrix operator+(matrix const &op2) const {
        matrix copy(*this);
        copy += op2;
        return copy;
        }
      matrix operator-(matrix const &op2) const {
        matrix copy(*this);
        copy -= op2;
        return copy;
        }
      matrix operator*(matrix const &op2) const;
      
      matrix operator()(TIndex row) const {
        return extractRow(row);
        }
      entry_type &operator()(TIndex row,TIndex col) {
        return Data[getIndex(row,col)];
        }
      entry_type operator()(TIndex row,TIndex col) const {
        return Data[getIndex(row,col)];
        }
    
      iterator begin() {
        return Data.get();
        }
      const_iterator begin() const {
        return Data.get();
        }
      iterator end() {
        return Data.get()+getSize();
        }
      const_iterator end() const {
        return Data.get()+getSize();
        }
      
      TSize width() const {
        return Width;
        }
      TSize height() const {
        return Height;
        }
      
      matrix extract(TIndex row,TIndex col,TSize height,TSize width) const;
      matrix extractRow(TIndex row) const {
        return extract(row,0,1,Width);
        }
      matrix extractColumn(TIndex col) const {
        return extract(0,col,Height,1);
        }
      
      matrix &set(TIndex row,TIndex col,matrix const &src);
      matrix &setRow(TIndex row,matrix const &src) {
        return set(row,0,src);
        }
      matrix &setColumn(TIndex col,matrix const &src) {
        return set(0,col,src);
        }
      
      matrix &add(TIndex row,TIndex col,matrix const &src,entry_type factor = 1);
      matrix &addRow(TIndex row,matrix &src,entry_type factor = 1) {
        return add(row,0,src,factor);
        }
      matrix &addColumn(TIndex col,matrix &src,entry_type factor = 1) {
        return add(0,col,src,factor);
        }
  
      matrix &addRowSelf(TIndex to,TIndex from,entry_type factor = 1,TIndex startcol = 0);
      matrix &addColumnSelf(TIndex to,TIndex from,entry_type factor = 1,TIndex startrow = 0);
      matrix &multiplyRowSelf(TIndex row,entry_type factor,TIndex startcol = 0);
      matrix &multiplyColumnSelf(TIndex column,entry_type factor,TIndex startrow = 0);
      matrix &swapRowSelf(TIndex row1,TIndex row2);
      matrix &swapColumnSelf(TIndex col1,TIndex col2);
  
      enum TMatrixNorm {
        NORM_TOTAL,       // = n max( a(i,j) )
	NORM_ROW_SUM,     // natural for the maximum norm
	NORM_COLUMN_SUM,  // natural for the absolute value sum norm
	NORM_SCHUR,	  // = sqrt(sum(a(i,j)^2))
	};
	
      entry_type norm(TMatrixNorm norm = NORM_SCHUR) const;
      entry_type det() const;
      entry_type trace() const;
      entry_type diagonalProduct() const;
      matrix transposed() const;
      matrix inverted() const;
      matrix gauss(scalar_type pivot_threshold = 0,TSize *swapcount = NULL) const;
      matrix gaussJordan(scalar_type pivot_threshold = 0,TSize *swapcount = NULL) const;
      matrix linearSolve(matrix const &vec,scalar_type pivot_threshold = 0) const;
      matrix cholesky() const;
      void decomposeLR(matrix &l,matrix &r) const;
      
      // operations for triangular matrices
      matrix &normalize();
      matrix upperTriangleSolve(matrix const &vec) const;
      matrix lowerTriangleSolve(matrix const &vec) const;
      
      void wipe(entry_type value = traits_type::zero);
      void setDimension(TSize height,TSize width);
      
      void outMatrix(std::ostream &ostr,void (*item_formatter)(std::ostream &os,bool first,bool last) = NULL) const;
    
      /// \deprecated use width() instead.
      TSize getWidth() const {
        return Width;
        }
      /// \deprecated use height() instead.
      TSize getHeight() const {
        return Height;
        }
      /// \deprecated use transpose() instead.
      matrix getTransposed() const {
        return transposed();
	}
      /// \deprecated use invert() instead.
      matrix getInverted() const {
        return inverted();
	}
      /// \deprecated use gauss() instead.
      matrix getGaussElim(scalar_type pivot_threshold = 0,TSize *swapcount = NULL) const {
        return gauss(pivot_threshold,swapcount);
	}
      /// \deprecated use gaussJordan() instead.
      matrix getGaussJordan(scalar_type pivot_threshold = 0,TSize *swapcount = NULL) const {
        return gaussJordan(pivot_threshold,swapcount);
	}
      /// \deprecated use cholesky() instead.
      matrix getCholesky() const {
        return cholesky();
	}
      /// \deprecated use decomposeLR() instead.
      void getLR(matrix &l,matrix &r) const {
        decomposeLR(l,r);
	}
      
    protected:
      void setup(TSize height,TSize width);
      TSize getSize() const {
        return Width*Height;
        }
      TIndex getIndex(TIndex row,TIndex col) const {
        return Width*row+col;
        }
    };
  }




// matrix operators -----------------------------------------------------------
template <class T,class Traits>
inline ixion::matrix<T,Traits> operator*(T scalar,ixion::matrix<T,Traits> const &mat);
template <class T,class Traits>
inline ixion::matrix<T,Traits> operator*(ixion::matrix<T,Traits> const &mat,T scalar);
template <class T,class Traits>
inline std::istream &operator>>(std::istream &istr,ixion::matrix<T,Traits> &mat);
template <class T,class Traits>
inline std::ostream &operator<<(std::ostream &ostr,ixion::matrix<T,Traits> const &mat);




// inline operations ----------------------------------------------------------
template<class T,class Traits>
template<class InputIterator>
inline ixion::matrix<T,Traits>::matrix(TSize width,TSize height,InputIterator first) {
  setup(width,height);
  TSize size = getSize();
  iterator it = begin();
  
  while (size--) 
    *it++ = *first++;
  }




// matrix operators -----------------------------------------------------------
template <class T,class Traits>
inline ixion::matrix<T,Traits> operator*(typename ixion::matrix<T,Traits>::scalar_type scalar,
                                         typename ixion::matrix<T,Traits> const &mat) {
  ixion::matrix<T,Traits> copy(mat);
  copy *= scalar;
  return copy;
  }




template <class T,class Traits>
inline ixion::matrix<T,Traits> operator*(ixion::matrix<T,Traits> const &mat,
                                         typename ixion::matrix<T,Traits>::scalar_type scalar) {
  ixion::matrix<T,Traits> copy(mat);
  copy *= scalar;
  return copy;
  }




template <class T,class Traits>
inline std::istream &operator>>(std::istream &istr,
                                ixion::matrix<T,Traits> &mat) {
  ixion::TSize height,width;
  char c;
  istr >> height >> c >> width;
  mat.setDimension(height,width); 
  for (ixion::TIndex y = 0;y < height;y++)
    for (ixion::TIndex x = 0;x < width;x++)
      istr >> mat(y,x);
  return istr;
  }




template <class T,class Traits>
inline std::ostream &operator<<(std::ostream &ostr,
                                ixion::matrix<T,Traits> const &mat) {
  mat.outMatrix(ostr);
  return ostr;
  }




#endif

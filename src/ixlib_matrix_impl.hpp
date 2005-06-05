// ----------------------------------------------------------------------------
//  Description      : Matrix handling
// ----------------------------------------------------------------------------
//  (c) Copyright 2000 by iXiONmedia, all rights reserved.
// ----------------------------------------------------------------------------




#include <cmath>
#include <ixlib_numeric.hpp>
#include <ixlib_exgen.hpp>
#include <ixlib_matrix.hpp>




#define EX_DIMEN \
  EXGEN_THROW(EC_DIMENSIONMISMATCH)




template <class T,class Traits>
ixion::matrix<T,Traits>::matrix(TSize height,TSize width) {
  setup(height,width);
  }




template <class T,class Traits>
ixion::matrix<T,Traits>::matrix(matrix const &src) {
  setup(src.Height,src.Width);
  TSize size = getSize();
  iterator srcit = src.Data.get();
  iterator destit = Data.get();
  
  while (size--)
    *destit++ = *srcit++;
  }




template <class T,class Traits>
ixion::matrix<T,Traits> &ixion::matrix<T,Traits>::operator=(matrix const &src) {
  setup(src.Height,src.Width);
  TSize size = getSize();
  const_iterator srcit = src.begin();
  iterator destit = begin();
  
  while (size--)
    *destit++ = *srcit++;
    
  return *this;
  }




template <class T,class Traits>
ixion::matrix<T,Traits> &ixion::matrix<T,Traits>::operator+=(matrix const &op2) {
  if (op2.Width != Width || op2.Height != Height)
    EX_DIMEN
  
  TSize size = getSize();
  const_iterator src = op2.begin();
  iterator dest = begin();
  
  while (size--)
    *dest++ += *src++;

  return *this;
  }




template <class T,class Traits>
ixion::matrix<T,Traits> &ixion::matrix<T,Traits>::operator-=(matrix const &op2) {
  if (op2.Width != Width || op2.Height != Height)
    EX_DIMEN
  
  TSize size = getSize();
  const_iterator src = op2.begin();
  iterator dest = begin();
  
  while (size--)
    *dest++ -= *src++;

  return *this;
  }




template <class T,class Traits>
ixion::matrix<T,Traits> &ixion::matrix<T,Traits>::operator*=(scalar_type scalar) {
  TSize size = getSize();
  iterator dest = begin();
  
  while (size--)
    *dest++ *= scalar;

  return *this;
  }




template <class T,class Traits>
ixion::matrix<T,Traits> ixion::matrix<T,Traits>::operator*(matrix const &op2) const {
  if (Width != op2.Height) 
    EX_DIMEN
  matrix target(Height,op2.Width);
  for (TIndex x = 0;x < op2.Width;x++)
    for (TIndex y = 0;y < Height;y++) {
      entry_type value = traits_type::zero;
      for (TIndex i = 0;i < Width;i++)
        value += operator()(y,i)*op2(i,x);
      target(y,x) = value;
      }
  return target;
  }




template <class T,class Traits>
ixion::matrix<T,Traits> ixion::matrix<T,Traits>::extract(TIndex row,TIndex col,TSize height,TSize width) const {
  matrix target(height,width);
  for (TIndex x = 0;x < width;x++)
    for (TIndex y = 0;y < height;y++) 
      target(y,x) = operator()(y+row,x+col);
  return target;
  }




template <class T,class Traits>
ixion::matrix<T,Traits> &ixion::matrix<T,Traits>::set(TIndex row,TIndex col,matrix const &src) {
  for (TIndex x = 0;x < src.Width;x++)
    for (TIndex y = 0;y < src.Height;y++) 
      operator()(y+row,x+col) = src(y,x);
  return *this;
  }




template <class T,class Traits>
ixion::matrix<T,Traits> &ixion::matrix<T,Traits>::add(TIndex row,TIndex col,matrix const &src,entry_type factor) {
  for (TIndex x = 0;x < src.Width;x++)
    for (TIndex y = 0;y < src.Height;y++) 
      operator()(y+row,x+col) += src(y,x)*factor;
  return *this;
  }




template <class T,class Traits>
ixion::matrix<T,Traits> &ixion::matrix<T,Traits>::addRowSelf(TIndex to,TIndex from,entry_type factor,TIndex startcol) {
  for (TIndex x = startcol;x < Width;x++)
    operator()(to,x) += operator()(from,x)*factor;
  return *this;
  }




template <class T,class Traits>
ixion::matrix<T,Traits> &ixion::matrix<T,Traits>::addColumnSelf(TIndex to,TIndex from,entry_type factor,TIndex startrow) {
  for (TIndex y = startrow;y < Height;y++)
    operator()(y,to) += operator()(y,from)*factor;
  return *this;
  }




template <class T,class Traits>
ixion::matrix<T,Traits> &ixion::matrix<T,Traits>::multiplyRowSelf(TIndex row,entry_type factor,TIndex startcol) {
  for (TIndex x = startcol;x < Width;x++)
    operator()(row,x) *= factor;
  return *this;
  }




template <class T,class Traits>
ixion::matrix<T,Traits> &ixion::matrix<T,Traits>::multiplyColumnSelf(TIndex column,entry_type factor,TIndex startrow) {
  for (TIndex y = startrow;y < Height;y++)
    operator()(y,column) *= factor;
  return *this;
  }




template <class T,class Traits>
ixion::matrix<T,Traits> &ixion::matrix<T,Traits>::swapRowSelf(TIndex row1,TIndex row2) {
  for (TIndex x = 0;x < Width;x++) {
    entry_type temp = operator()(row1,x);
    operator()(row1,x) = operator()(row2,x);
    operator()(row2,x) = temp;
    }
  return *this;
  }




template <class T,class Traits>
ixion::matrix<T,Traits> &ixion::matrix<T,Traits>::swapColumnSelf(TIndex col1,TIndex col2) {
  for (TIndex y = 0;y < Height;y++) {
    entry_type temp = operator()(y,col1);
    operator()(y,col1) = operator()(y,col2);
    operator()(y,col2) = temp;
    }
  return *this;
  }




template <class T,class Traits>
typename ixion::matrix<T,Traits>::entry_type 
ixion::matrix<T,Traits>::det() const {
  if (Width != Height) EX_DIMEN
  try {
    TSize swaps;
    matrix temp = getGaussElim(0,&swaps);
    entry_type factor = 1;
    if (swaps % 2) factor = -1;
    return factor*temp.diagonalProduct();
    }
  catch (...) {
    return 0;
    }
  }




template <class T,class Traits>
typename ixion::matrix<T,Traits>::entry_type 
ixion::matrix<T,Traits>::norm(TMatrixNorm norm) const {
  entry_type result,sum,entry;
  switch (norm) {
    case NORM_TOTAL:
      // the total norm can only be applied to symmetrical matrices
      if (Width != Height) EX_DIMEN
      
      result = 0;
      for (TIndex i = 0;i < Height;i++)
        for (TIndex j = 0;j < Width;j++)
	  result = NUM_MAX(result,traits_type::norm(operator()(i,j)));
      return Width*result;
    case NORM_ROW_SUM:
      result = 0;
      for (TIndex i = 0;i < Height;i++) {
        sum = 0;
        for (TIndex j = 0;j < Width;j++)
	  sum += traits_type::norm(operator()(i,j));
	result = NUM_MAX(result,sum);
	}
      return result;
    case NORM_COLUMN_SUM:
      result = 0;
      for (TIndex i = 0;i < Height;i++) {
        sum = 0;
        for (TIndex j = 0;j < Width;j++)
	  sum += traits_type::norm(operator()(j,i));
	result = NUM_MAX(result,sum);
	}
      return result;
    case NORM_SCHUR:
      result = 0;
      for (TIndex i = 0;i < Height;i++)
        for (TIndex j = 0;j < Width;j++) {
	  entry = traits_type::norm(operator()(j,i));
	  result += entry*entry;
	  }
      return traits_type::sqrt(result);
    default:
      EXGEN_NYI
    }
  }




template <class T,class Traits>
typename ixion::matrix<T,Traits>::entry_type 
ixion::matrix<T,Traits>::trace() const {
  if (Width != Height) EX_DIMEN
  entry_type result = 0;
  for (TIndex i = 0;i<Width;i++)
    result += operator()(i,i);
  return result;
  }




template <class T,class Traits>
typename ixion::matrix<T,Traits>::entry_type 
ixion::matrix<T,Traits>::diagonalProduct() const {
  if (Width != Height) EX_DIMEN
  entry_type result = 1;
  for (TIndex i = 0;i<Width;i++)
    result *= operator()(i,i);
  return result;
  }




template <class T,class Traits>
ixion::matrix<T,Traits> ixion::matrix<T,Traits>::transposed() const {
  matrix target(Width,Height);
  for (TIndex x = 0;x<Width;x++)
    for (TIndex y = 0;y<Height;y++)
      target(x,y) = operator()(y,x);
  return target;
  }




template <class T,class Traits>
ixion::matrix<T,Traits> ixion::matrix<T,Traits>::inverted() const {
  if (Width != Height) EX_DIMEN
  matrix temp(Height,Width*2);
  temp.set(0,0,*this);
  for (TIndex x = 0;x<Width;x++)
    for (TIndex y = 0;y<Width;y++)
      temp(y,x+Width) = x == y ? 1 : 0;
  return temp.getGaussJordan().normalize().extract(0,Width,Height,Width);
  }




template <class T,class Traits>
ixion::matrix<T,Traits> ixion::matrix<T,Traits>::gauss(scalar_type pivot_threshold,TSize *swapcount) const {
  matrix target(*this);
  if (swapcount) *swapcount = 0;
  
  TSize steps = NUM_MIN(Width,Height);
  
  for (TIndex step = 0;step < steps;step++) {
    // column pivot search
    TIndex pivot = step;
    scalar_type pmax = traits_type::norm(target(step,step));
    for (TIndex row = step+1;row<Height;row++) 
      if (traits_type::norm(target(row,step)) > pmax) {
        pivot = row;
	pmax = traits_type::norm(target(row,step));
        }
    
    if (pmax < pivot_threshold) EXGEN_THROW(EC_CANCELLED)
    if (pivot != step) {
      target.swapRowSelf(pivot,step);
      if (swapcount) (*swapcount)++;
      }
    
    entry_type diag = target(step,step);
    
    // zero out trailing rows
    for (TIndex row = step+1;row<Height;row++) {
      target.addRowSelf(row,step,-target(row,step)/diag,step+1);
      target(row,step) = traits_type::zero;
      }
    }
  return target;
  }




template <class T,class Traits>
ixion::matrix<T,Traits> ixion::matrix<T,Traits>::gaussJordan(scalar_type pivot_threshold,TSize *swapcount) const {
  matrix target(*this);
  if (swapcount) *swapcount = 0;
  
  TSize steps = NUM_MIN(Width,Height);
  
  for (TIndex step = 0;step < steps;step++) {
    // column pivot search
    TIndex pivot = step;
    scalar_type pmax = traits_type::norm(target(step,step));
    for (TIndex row = step+1;row<Height;row++) 
      if (Traits::norm(target(row,step)) > pmax) {
        pivot = row;
	pmax = traits_type::norm(target(row,step));
        }
    
    if (pmax < pivot_threshold) EXGEN_THROW(EC_CANCELLED)
    if (pivot != step) {
      target.swapRowSelf(pivot,step);
      if (swapcount) (*swapcount)++;
      }
    
    entry_type diag = target(step,step);
    
    // zero out preceding rows
    for (TIndex row = 0;row<step;row++) {
      target.addRowSelf(row,step,-target(row,step)/diag,step+1);
      target(row,step) = traits_type::zero;
      }
    // zero out trailing rows
    for (TIndex row = step+1;row<Height;row++) {
      target.addRowSelf(row,step,-target(row,step)/diag,step+1);
      target(row,step) = traits_type::zero;
      }
    }
  return target;
  }




template <class T,class Traits>
ixion::matrix<T,Traits> ixion::matrix<T,Traits>::linearSolve(matrix const &vec,scalar_type pivot_threshold) const {
  if (vec.Width != 1 || Height != vec.Height || Width != Height) EX_DIMEN
  matrix backpack(Height,Width+1);
  backpack.set(0,0,*this);
  backpack.set(0,Width,vec);
  matrix gaussed = backpack.getGaussJordan(pivot_threshold).normalize();
  return gaussed.extract(0,0,Height,Width).upperTriangleSolve(gaussed.extract(0,Width,Height,1));
  }




template <class T,class Traits>
ixion::matrix<T,Traits> ixion::matrix<T,Traits>::cholesky() const {
  if (Width != Height) EX_DIMEN
  matrix result(Height,Width);
  result.wipe();
  
  for (TIndex x = 0;x<Width;x++) {
    // determine diagonal element
    entry_type sum = operator()(x,x);
    for (TIndex y = 0;y<x;y++) {
      entry_type value = result(x,y);
      sum -= value*value;
      }
    result(x,x) = traits_type::sqrt(sum);

    // determine off-diagonal elements
    for (TIndex y = x+1;y<Height;y++) {
      sum = operator()(y,x);
      for (TIndex i = 0;i < x;i++) 
        sum -= result(y,i)*result(x,i);
      result(y,x) = sum/result(x,x);
      }
    }
  return result;
  }




template <class T,class Traits>
void ixion::matrix<T,Traits>::decomposeLR(matrix &l,matrix &r) const {
  if (Width != Height) EX_DIMEN
  l.setDimension(Height,Height);
  r.setDimension(Height,Width);
  l.wipe();
  r.wipe();
  
  for (TIndex x = 0;x<Width;x++) {
    entry_type sum;
    // elements above diagonal --> r
    for (TIndex y = 0;y < x;y++) {
      sum = traits_type::zero;
      for (TIndex i = 0;i < y;i++) 
        sum += l(y,i)*r(i,x);
      // the corresponding l element is 1 anyway
      r(y,x) = operator()(y,x)-sum;
      }
    
    // elements on diagonal
    sum = traits_type::zero;
    for (TIndex i = 0;i<x;i++) 
      sum += l(x,i)*r(i,x);
    
    l(x,x) = 1;
    r(x,x) = operator()(x,x)-sum;
    
    //elements under diagonal --> l
    for (TIndex y = x+1;y < Height;y++) {
      sum = traits_type::zero;
      for (TIndex i = 0;i < x;i++) 
        sum += l(y,i)*r(i,x);
      l(y,x) = (operator()(y,x)-sum)/r(x,x);
      }
    }
  }




template <class T,class Traits>
ixion::matrix<T,Traits> &ixion::matrix<T,Traits>::normalize() {
  for (TIndex i = 0;i<Height;i++)
    multiplyRowSelf(i,1/operator()(i,i),i);
  return *this;
  }




template <class T,class Traits>
ixion::matrix<T,Traits> ixion::matrix<T,Traits>::upperTriangleSolve(matrix const &vec) const {
  if (vec.Width != 1 || Height != vec.Height || Width != Height) EX_DIMEN
  matrix result(Width,1);
  if (Width == 0) return result;
  
  bool exit = false;
  for (TIndex i = Width-1;!exit;i--) {
    entry_type value = vec(i,0);
    for (TIndex x = i+1;x<Width;x++) 
      value -= result(x,0)*operator()(i,x);
    result(i,0) = value/operator()(i,i);
    exit = i == 0;
    }
  return result;
  }




template <class T,class Traits>
ixion::matrix<T,Traits> ixion::matrix<T,Traits>::lowerTriangleSolve(matrix const &vec) const {
  if (vec.Width != 1 || Height != vec.Height || Width != Height) EX_DIMEN
  matrix result(Width,1);
  if (Width == 0) return result;
  
  for (TIndex i = 0;i<Width;i++) {
    entry_type value = vec(i,0);
    for (TIndex x = 0;x<i;x++) {
      value -= result(x,0)*operator()(i,x);
      }
    result(i,0) = value/operator()(i,i);
    }
  return result;
  }




template <class T,class Traits>
void ixion::matrix<T,Traits>::wipe(entry_type value) {
  TSize size = getSize();
  iterator dest = begin();
  
  while (size--)
    *dest++ = value;
  }




template <class T,class Traits>
void ixion::matrix<T,Traits>::setDimension(TSize height,TSize width) {
  setup(height,width);
  }




template <class T,class Traits>
void ixion::matrix<T,Traits>::outMatrix(std::ostream &ostr,void (*item_formatter)(std::ostream &os,bool first,bool last)) const {
  ostr << Height << 'x' << Width << endl;
  for (TIndex y = 0;y < Height;y++) {
    for (TIndex x = 0;x < Width;x++) {
      if (item_formatter) item_formatter(ostr,x == 0,x<Width-1);
      ostr << operator()(y,x);
      if (!item_formatter) ostr << ' ';
      }
    ostr << endl;
    }
  }




template <class T,class Traits>
void ixion::matrix<T,Traits>::setup(TSize height,TSize width) {
  Data.allocate(width*height);
  Width = width;
  Height = height;
  }




#undef EX_DIMEN

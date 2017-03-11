#ifndef _BANDMATRIX_H_
#define _BANDMATRIX_H_

//-*-c++-*-
#include "matrix.h"
#include "extra.h"

// Implements a band storage structure for matrices
// Matrix is assumed square with equal number of above and below diagonal bands

template <class Element>
class BMatrix : public TMatrix<Element> {
 public: 
  // constructor 
  BMatrix(const int n, const int b) : TMatrix<Element>(n,2*b+1) 
  { _bandwidth = b; }

  // virtual destructor
  virtual ~BMatrix() {};

  // _ncols in the base class is incorrect
  inline int ncols() const {return(this->_nrows);}

  // Assignment not atomatically inherited?
  void operator=(const Element &val) { TMatrix<Element>::operator=(val); }


 private:
  // Belt and Braces
  // private (undefined) default and copy constructors, and assignment
  BMatrix(); 
  BMatrix(const BMatrix &); 
  void operator=(const BMatrix &); 

  // band width
  int _bandwidth;

 protected:
  // Local function to take care of indexing
  // Overloads the base class
  virtual int index(const int i,const int j) const {
    int a = min(i,j), b = _bandwidth+1+j-i;
    return(TMatrix<Element>::index(a,b));
  }

};

// shorthand for double and int
typedef BMatrix<double> BandMatrix;
typedef BMatrix<int> BandIMatrix;

#endif

#ifndef _MATRIX_H_
#define _MATRIX_H_

//-*-c++-*-
// Template class library useful for storing vector and matrix data, 
// both integer and double precision (consider float?)

// Base matrix template
template <class Element>
class TMatrix {
 public: 
  // constructor 
  TMatrix(const int, const int); 

  // virtual destructor
  virtual ~TMatrix(); 

  // construct from C vector of data
  TMatrix(Element *, const int, const int); 

  // assign single value to entire matrix
  void operator=(const Element &); 

  // reference to a matrix entry. There are two. 
  // First allows the entry to be modified 
  // Second returns only a const reference ie. not modify-able
  inline Element &operator()(const int i, const int j) {
     return( data[index(i,j)] );
  }
  inline const Element &operator()(const int i, const int j) const {
     return( data[index(i,j)] );
  }


  // A bunch of inquiry functions
  inline int nrows() const {return(_nrows);}
  inline int ncols() const {return(_ncols);}
  inline int length() const {return(_length);}


 private:
  // private (undefined) default constructor
  TMatrix(); 
  // private (undefined) copy constructor
  TMatrix(const TMatrix &); 
  // private (undefined) assignment op
  void operator=(const TMatrix &); 

  // pointer to the data
  Element *data; 
  // flag do I own the data pointer? 
  int _mypointer; 
  // total length of data
  int _length; 
 protected:
  // dimensions
  int _nrows, _ncols;

  // Local function to take care of indexing
  virtual int index(const int i,const int j) const {return((j-1)*_nrows+(i-1)) ;}
  //virtual int index(const int i,const int j) const {
  //if(j<1 || j>_ncols) throw 20;
  //if(i<1 || i>_nrows) throw 21;
  //return((j-1)*_nrows+(i-1)) ;}
};

// shorthand for double and int
typedef TMatrix<double> Matrix;
typedef TMatrix<int> IMatrix;

// base vector template, inherits from matrix
template <class Element>
class TVector : public TMatrix<Element> {
 public:
  // vector constructor, (explicit prevents use for conversion
  explicit TVector(const int nrow) : TMatrix<Element>(nrow, 1) {}
  // construct from a vector of data
  TVector(Element *x, const int nrow) : TMatrix<Element>(x,nrow, 1) {}

  // Assignment not atomatically inherited?
  void operator=(const Element &val) { TMatrix<Element>::operator=(val); }
  
  // references to vector entries (see TMatrix)
  Element &operator()(const int i) {return(TMatrix<Element>::operator()(i,1));}

  const Element &operator()(const int i) const 
  { return(TMatrix<Element>::operator()(i,1));}
 
private:
  // private (undefined) default and copy constructors, and assignment
  TVector();
  TVector(const TVector &);
  void operator=(const TVector &);

};

// shorthand for double and int
typedef TVector<double> Vector;
typedef TVector<int> IVector;

#endif


//#include "matrix.h"
#include "bandmatrix.h"

//  R CMD SHLIB *.cc -o dtw.so

void signalMatchABand(const Vector &s1, 
		      const Vector &s2, 
		      IVector &path,
		      const Vector &lambdaH, 
		      const int maxshift=50);

extern "C" {
  void signalMatchWrapABand(double *Rs1, 
			    double *Rs2, 
			    int *Rnr,
			    int *Rnq,
			    int *Rpath,
			    double *RlH, 
			    int *Rmaxs)
  {
    int nr = *Rnr;
    int nq = *Rnq;
    
    // Change on June 1st 2007 - vectors of lambdaH 
    Vector s1(Rs1,nr), s2(Rs2,nq), lambdaH(RlH,nr);
    IVector path(Rpath,nr);
    
    signalMatchABand(s1, s2, path, lambdaH, *Rmaxs);
  }
}


#include <stdio.h>
#include "bandmatrix.h"
#include <float.h>

using namespace std;

static double Delta(double x, double y) { return(abs(x-y));}

void signalMatchABand(const Vector &master, 
		      const Vector &signal, 
		      IVector &path,
		      const Vector &lambda, 
		      const int maxshift=50)

{
  
  //  Performs nonlinear monotone transformation of the time
  //  axis to align two signals
  //  master and signal are assumed to be two signals of comparable length

  //  Uses implementation of the dynamic programming algorithm to find
  //  the shortest path through a banded matrix from top left to
  //  bottom right (path length is sum of the elements) 
  
  //  NOTE: This is the asymmetric algorithm aligning signal to master
  //  Allowable steps are (0,1), (1,1) (2,1)
  
  //  signal is ALIGNED to master 
  //  lambda is a non-diagonal step penalty (for moves (0,1) and (2,1))
  
  //  Note the maximum size of the shift is restricted to max.shift moves
  //  Such restriction allows a banded data storage structure which is used here

  // a banded matrix of dimenions n by b has n by 2b+1 terms in it.

  int nm = master.length();
  int ns = signal.length();
  int i, j, jbest, ibest;
  int jmin, jmax;
  int imin, imax;

  double h0, h1, h2, ymin;

  BandIMatrix best(nm,maxshift);
  BandMatrix y(nm,maxshift);

  y=0; // initiate all values of y
  best=0;
  
  y(1,1) = Delta(master(1),signal(1));
  best(1,1) = 0;
  
  // we use code 0 for the vertical, 1 for the diagonal,
  // and 2 for the super-diagonal step.

  // initiate cost along both edges of Sakoe-Chiba band
  //printf("Initiating cost\n");

  // i=1 
  i=1;
  jmin = max(i-maxshift,2);
  jmax = min(i+maxshift,ns);
  
  for(j=jmin; j<=jmax; j++) {
    y(i,j) = Delta(master(i),signal(j));
    best(i,j) = -1; // Not strictly required
  }

  // At this point y(i,k) is the cost of aligning the first query
  // point to the kth reference point with no penalty for shifting
  // left or right at the start

  //printf("Continuing with initiating cost\n");

  j = 1;
  imin = max(j-maxshift,2);
  imax = min(j+maxshift,nm);

  for(i=imin; i<=imax; i++) {
    y(i,j) = Delta(master(i),signal(j));
    best(i,j) = -1;
  }
   
  // Now do dtw proper as we move away from leading edges of Sakoe-Chiba band
  //printf("Starting dtw process\n");
  j=2;
  imin = max(j-maxshift,1);
  imax = min(j+maxshift,nm);
  for(i=imin; i<=imax; i++) {
    h0 = y(i-1,j) + lambda(i);
    h1 = y(i-1,j-1);
    if(h0<h1) {
      y(i,j) = h0+Delta(master(i),signal(j));
      best(i,j) = 0;
    } else {
      y(i,j) = h1+Delta(master(i),signal(j));
      best(i,j) = 1;
    }
  }
  //printf("Starting full asymmetric dtw process\n");
  for(j=3; j<=ns; j++) {
    imin = max(j-maxshift,1);
    imax = min(j+maxshift,nm);
    for(i=imin; i<=imax; i++) {
      h0 = h1 = h2 = DBL_MAX;
      // Vertical step
      if(abs(j-(i-1))<=maxshift) h0 = y(i-1,j) + lambda(i);
      // Diagonal step
      if(abs((j-1)-(i-1))<=maxshift) h1 = y(i-1,j-1); // always possible
      // Super-diagonal step
      // Modified to add additional penalty for skipping over a point? Not in current version

      // version 1
      //if(abs((j-2)-(i-1)) <= maxshift) h2 = y(i-1,j-2) + lambda(i) + Delta(master(i),signal(j-1));  

      // more like linear interpolation as we are aligning s(j-1) to average of master_i-1 and master_i
      //if(abs((j-2)-(i-1)) <= maxshift) h2 = y(i-1,j-2) + lambda(i) + 0.5*Delta(0.5*(master(i-1)+master(i)),signal(j-1)); 

      //Double penalty for dropping a term as a compromise of the above
      if(abs((j-2)-(i-1)) <= maxshift) h2 = y(i-1,j-2) + lambda(i) * 2; 
      
      if(h0<h1 && h0<h2) {
	y(i,j) = Delta(master(i),signal(j)) + h0;
	best(i,j) = 0;
      } else if (h1<h0 && h1<h2) {
	y(i,j) = Delta(master(i),signal(j)) + h1;
	best(i,j) = 1;
      } else {
	y(i,j) = Delta(master(i),signal(j)) + h2;
	best(i,j) = 2;
      }
    }
  }
  //printf("Done with dtw process\n");

  // Backward pass
  // Reconstruct the path from either edge of Sakoe-Chiba band
  
  //printf("Starting backward pass along one edge\n");
  i = nm;
  jmin = max(i-maxshift,1);
  jmax = min(i+maxshift,ns);
  ymin = y(i,jmin);
  ibest = i;
  jbest = jmin;
  for(j=jmin; j<=jmax; j++) {
    if(y(i,j) < ymin) {
      ymin = y(i,j);
      jbest = j;
    }
  }
  
  //printf("Starting backward pass along other edge\n");
  j = ns;
  imin = max(j-maxshift,1);
  imax = min(j+maxshift,nm);
  for(i=imin; i<=imax; i++) {
    if(y(i,j) < ymin) {
      ymin = y(i,j);
      ibest = i;
      jbest = j;
    }
  }
  //printf("Backward pass starting point found\n");
  //printf("ymin = %5.3f\n",ymin);
  path(ibest) = jbest; // issue here about how long path is going to be
  
  
  //printf("\n\n");

  for(i=ibest-1; i>=1; i--) {
    j = path(i+1);
    //printf("%d %d %d\n",i+1,j,best(i+1,j));
    if(best(i+1,j)==(-1)) break;
    path(i) = j-best(i+1,j);
  }
  //printf("finished\n");
}


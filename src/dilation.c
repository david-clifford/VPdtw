void dilation(double *y, 
	      int *nym, 
	      int *sp,
	      double *ey)
{
  int i,j,n=*nym,span=*sp,pos;
  double max;
  
  // dilate y by a window of length span - ie push a line of width span
  // done on the curve y as far as possible (the max value over the
  // window)

  // Initialize max
  max = y[0];
  pos = 0;
  for(i=0;i<span;i++) {
    if(y[i]>max) {
      max=y[i];
      pos=i;
    }
  }
  
  // Initialize ey
  for(i=0;i<span;i++) ey[i]=max;
  
  // Move along y
  for(i=span;i<n;i++) {
    
    // recompute max
    if(y[i]>max) {
      max = y[i];
      pos = i;
    }

    // if current max position is off the map recompute max
    if(pos<(i-span+1)) {
      max = y[i-span+1];
      pos = i-span+1;
      for(j=i-span+1;j<=i;j++) {
	if(y[j]>max) {
	  max=y[j];
	  pos=j;
	}
      }
    }
    
    // set next value of ey
    ey[i] = max;
  }
}

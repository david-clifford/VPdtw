#ifndef _EXTRA_H_
#define _EXTRA_H_

//-*-c++-*-
// This file contains a few useful things
 
// A function to quickly compute the square of something
static inline double sqr(const double x) {return(x*x);}

// A function to quickly compute the absolute value of something
static inline int abs(const int x) {return((x<0)?(-x):x);}
static inline double abs(const double x) {return((x<0)?(-x):x);}

// A function to find the maximum of two inputs
static inline int max(const int x, const int y) {return((x<y)?y:x);}
static inline double max(const double x, const double y) {return((x<y)?y:x);}
static inline int min(const int x, const int y) {return((x<y)?x:y);}
static inline double min(const double x, const double y) {return((x<y)?x:y);}

#endif

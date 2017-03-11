\name{dilation}
\alias{dilation}

\title{ Compute a morphological dilation of a signal }
\description{
  A dilation is a moving local maximum over a window of specific fixed
  width specified by span. This dilation is computed first in one
  direction and then in the other. 
}
\usage{
dilation(y, span)
}

\arguments{
  \item{y}{signal, a numeric vector}
  \item{span}{ the width of the moving window, integer }
}

\details{

A dilation is a method often used in mathematical morphology and image
analysis (Soille 1999). This function is for vectors not matrices or
images though applying it to rows and columns of a matrix will give
the corresponding results. 

An erosion of a vector or image can also be computed easily from this
by computing the dilation of -1 times the vector and transforming
back.

We recommend using a dilation to form a \code{penalty} for use in
\code{VPdtw}.

}

\value{
  \item{res}{Dilation of y with width span}
}

\references{ Soille, P. Morphological Image Analysis: Principles and
  Applications; Springer: New York, 1999. }

\author{ David Clifford }

\examples{

## Example 1 - dilation of a signal
data(reference)
dref <- dilation(reference,150)
plot(reference,log="y",type="l")
lines(dref,col=2)

## Example 2 - dilation of an image
BIN <- (volcano>177)
dBIN <- t(apply(BIN,1,dilation,span=5))
dBIN <- apply(dBIN,2,dilation,span=5)
par(mfrow=c(2,2))
image(volcano)
image(BIN)
image(dBIN)
}

\keyword{methods}
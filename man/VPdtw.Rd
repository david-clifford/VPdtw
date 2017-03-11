\name{VPdtw}
\alias{VPdtw}
\alias{print.VPdtw}
\alias{plot.VPdtw}

\title{Variable Penalty Dynamic Time Warping function}
\description{
  Use variable penalty dynamic time warping to align one (or many)
query signal(s) to a master signal. Penalties are incurred whenever a
non-diagonal move is taken. 
}
\usage{
VPdtw(reference, query, penalty = 0, maxshift = 50, 
      Reference.type = c("random","median","mean","trimmed"))
}

\arguments{
  \item{reference}{ Reference signal, NULL or a vector, see details.}
  \item{query}{ Query signal, a vector or matrix, see details }
  \item{penalty}{ Penalty term, a vector of same length as reference
    (not checked) or a matrix. See details. Default is 0 repeated to the
  length of reference}
  \item{maxshift}{ Maximum allowable shift, an integer}
  \item{Reference.type}{Choices for \code{reference} if NULL is input}
}

\details{
  Performs variable penalty dynamic time warping of \code{query} to
  \code{reference}. Sakoe Chiba dtw used with width \code{maxshift}.

  The basic operation aligns a \code{query} vector to a
  \code{reference} vector.
  
  If \code{reference} is not specified and \code{query} is a matrix
  then the \code{reference} is created based on the value of
  \code{Reference.type}. The four choices are \code{random},
  \code{median}, \code{mean} and \code{trimmed}. These choose a column
  of \code{query} at random as a reference, or the piecewise median,
  mean or trimmed mean (with trim=0.1) with missing values removed.

  If \code{query} is a matrix and \code{penalty} is a vector then the
  same penalty is used to align each column of \code{query} to the
  \code{reference}. Different alignment paths are chosen for each
  column of the \code{query} matrix.

  If \code{query} is a vector and \code{penalty} is a matrix then the
  \code{query} is aligned to the \code{reference} several times, using
  each column of the \code{penalty} matrix in turn as the penalty for
  the alignment.

  If \code{query} and \code{penalty} are matrices then nothing
  happens. If you wish to align many query vectors and test many
  penalty vectors at the same time then do the appropriate looping (over
  queries, or penalties) outside of \code{VPdtw}.
  
}

\value{
  \item{xVals}{For plotting everything to correct index}
  \item{reference}{reference vector used by VPdtw expanded by NAs for plotting}
  \item{query}{query passed to VPdtw}
  \item{penalty}{penalty passed to VPdtw}
  \item{warpedQuery}{result of alignment, same class as query}
  \item{shift}{shifts required to achieve alignment}
  \item{summary}{Summary information about the alignment. Used for \code{print.VPdtw}}
  \item{information}{Information about the alignment. Used for \code{print.VPdtw}}
}

\references{ Alignment Using Variable Penalty Dynamic Time Warping by CLIFFORD, 
D; STONE, G; MONTOLIU, I; et al. ANALYTICAL CHEMISTRY Volume: 81 Issue: 3 Pages:
 1000-1007 Published: 2009}

\author{David Clifford, Glenn Stone}

\seealso{Also check out the \link[dtw]{dtw} package by 
         Toni Giorgino which covers many variations of dynamic time warping.}

\examples{
  ## Citation
  citation("VPdtw")

  ## Basic Examples of zero-penalty DTW

  ## Example of exact fit in the middle
  query <- c(1,5,4,3,9,8,5,2,6,5,4)
  reference <- c(rnorm(5),query,rnorm(5))
  lambda <- rep(0,length(reference))
  maxshift <- 11
  res <- VPdtw(reference,query,lambda,maxshift)
  plot(res)
  res

  ## Example of exact fit on one side
  reference <- c(1,5,4,3,9,8,5,2,6,5,4)
  query <- c(rnorm(5),reference)
  reference <- c(reference,rnorm(5))
  lambda <- rep(0,length(reference))
  maxshift <- 6
  res <- VPdtw(reference,query,lambda,maxshift)
  plot(res)
  res

  ## Example of exact fit on the other side
  reference <- c(1,5,4,3,9,8,5,2,6,5,4)
  query <- c(reference,rnorm(5))
  reference <- c(rnorm(5),reference)
  lambda <- rep(0,length(reference))
  maxshift <- 6
  res <- VPdtw(reference,query,lambda,maxshift)
  plot(res)
  res

  ## Example of exact fit except where one query gets dropped and its all on one side
  reference <- c(1,5,4,3,9,8,5,2,6,5,4)
  query <- c(reference[1:5],20,reference[6:11])
  reference <- c(rnorm(5),reference)
  query <- c(query,rnorm(5))
  lambda <- rep(0,length(reference))
  maxshift <- 6
  res <- VPdtw(reference,query,lambda,maxshift)
  plot(res)
  res
  
## Examples that use penalty term. Examples with long signals

data(reference)
data(query)
## Do alignment on log scale
reference <- log(reference)
query <- log(query)

## VPdtw
result <- VPdtw(reference=reference[1:2500],query=query[1:2500],
                penalty=dilation(reference[1:2500],150)/4,maxshift=150)
plot(result)
result

## Zero penalty DTW
result2 <- VPdtw(reference=reference[1:2500],query=query[1:2500],
                 penalty=rep(0,length(reference)),maxshift=150)
plot(result2)

## Try both penalties at the same time
penalty <- dilation(reference,350)/5
penalty <- cbind(penalty,rep(0,length(penalty)))

result <- VPdtw(reference,query,penalty=penalty,maxshift=350)
plot(result,"After")
plot(result,"Shift")
result

## All three plots at once
plot(result)

}

\keyword{methods}

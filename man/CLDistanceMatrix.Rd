\name{CLDistanceMatrix}
\alias{CLDistanceMatrix}
\title{Distance Matrix Calculation via OpenCL}
\description{
    Given a tabular data set X calculates its distance matrix D, i.e.
    D[i,j] = ||X[i,] - X[j,]||
    via an OpenCL backend in C++.
}
\usage{
CLDistanceMatrix(mat)
}
\arguments{
    \item{mat}{A tabular dataset as a matrix}
}
\value{
  \item{D}{Distance Matrix of X.}
}
\author{Julian Märte}

\keyword{ distance, opencl }

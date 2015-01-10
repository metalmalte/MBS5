/** \file GaussianKernel.cpp
 *
 * Module:    CS3303
 *            Medizinische Bild- und Signalverarbeitung
 *            Medizinische Bildverarbeitung
 *
 * Authors:   Jan Ehrhardt
 *
 * Copyright (c) 2014 Institute of Medical Informatics,
 *            University of Luebeck
 ********************************************************/
#include <iostream>
#include <math.h>
#include "GaussianKernel.h"

/* Constructor creates a Gaussian kernel of size 2m+1 x 2m+1
 * with m=2.5*sigma (rounded down).
 * Calls the constructor of the base class with the computed halfsize as arguments.
 * We use static_cast<unsigned int>() to cast from double to unsigned integer as needed
 * by the constructor of ConvolutionKernel. */
GaussianKernel::GaussianKernel( double sigma ) :
    ConvolutionKernel( static_cast<unsigned int>( 2.5*sigma), static_cast<unsigned int>( 2.5*sigma) )
{
  // precompute the denominator of the exponent (faster)
  const double denominator= 1.0/(2*sigma*sigma);

  //
  // Iterate over all mask pixel coordinates and compute the
  // value of the Gaussian function
  // to set the coefficient for all mask values.

  double sumValues=0; // needed for normalization
  for( int j = -GetHalfSizeY(); j <= GetHalfSizeY(); j++ )
  {
    for( int i = -GetHalfSizeX(); i <= GetHalfSizeX(); i++ )
    {
      // evaluate the Gaussian function for the mask indizes
      // we can omit the constant factor because of the normalization
      double value = exp(-(i*i+j*j)*denominator);
      SetCoefficient( i, j, value );
      // compute sum of all mask values
      sumValues += value;
    }
  }
  // compute normalization factor from the sum of all mask values
  const double normalizationFactor=1.0/sumValues;

  //
  // Iterate over all mask pixels to normalize the sum of the
  // mask values to 1.
  for( int j = -GetHalfSizeY(); j <= GetHalfSizeY(); j++ )
  {
    for( int i = -GetHalfSizeX(); i <= GetHalfSizeX(); i++ )
    {
      const double value = normalizationFactor * GetCoefficient( i, j);
      SetCoefficient( i, j, value );
    }
  }

}

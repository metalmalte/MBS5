/** \file MeanFilter.cpp
 *
 * Module:    CS3303
 *            Medizinische Bild- und Signalverarbeitung
 *            Medizinische Bildverarbeitung
 *
 * Authors:   Jan Ehrhardt, Alexander Schmidt-Richberg
 *
 * Copyright (c) 2010 Institute of Medical Informatics,
 *            University of Luebeck
 ********************************************************/
#include <iostream>
#include "MeanKernel.h"

/* Constructor creates an 2*hX+1 x 2*hY+1 mean kernel
 *
 * Call the constructor of the base class with arguments.*/
MeanKernel::MeanKernel( unsigned int hX, unsigned int hY ) :
    ConvolutionKernel( hX, hY )
{
  // Compute the correct coefficient of the mask (is the same for all entries).
  // Here we convert GetSizeX()*GetSizeY() to double to avoid integer division.
  const double meanKernelWeight = 1.0 / static_cast<double>( GetSizeX() * GetSizeY() );

  // Iterate over all mask pixel coordinates to
  // set the coefficient for all mask values.
  for( int j = -GetHalfSizeY(); j <= GetHalfSizeY(); j++ )
  {
    for( int i = -GetHalfSizeX(); i <= GetHalfSizeX(); i++ )
    {
      SetCoefficient( i, j, meanKernelWeight );
    }
  }
}

/* Destructor (does nothing). */
MeanKernel::~MeanKernel()
{
}

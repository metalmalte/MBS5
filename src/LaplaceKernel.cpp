/** \file LaplaceKernel.cpp
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
#include "LaplaceKernel.h"

/* Constructor creates an 3x3 Laplace kernel. */
LaplaceKernel::LaplaceKernel() :
    ConvolutionKernel( 1, 1 )
{
  /* The 3x3 Laplace kernel (filter mask) is
   *
   *      |  0  1  0 |
   *      |  1 -4  1 |
   *      |  0  1  0 |
   */

  // Coefficients are initialized with zero.
  // Here, we only have to set the non-zero values.
  SetCoefficient( 0, -1, 1.0 );
  SetCoefficient( -1, 0, 1.0 );
  SetCoefficient( 0, 0, -4.0 );
  SetCoefficient( 1, 0, 1.0 );
  SetCoefficient( 0, 1, 1.0 );
}


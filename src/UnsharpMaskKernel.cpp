/** \file UnsharpMaskKernel.cpp
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
#include "UnsharpMaskKernel.h"

/* Constructor creates an 2*hX+1 x 2*hY+1 unsharp mask kernel. */
UnsharpMaskKernel::UnsharpMaskKernel( unsigned int hX, unsigned int hY ) :
    ConvolutionKernel( hX, hY )
{
  /*
   * This implements the filter mask of the unsharp mask filter for an arbitrary size.
   *
   * The unsharp mask filter is given as
   *
   *  I_out(x,y) = 2 * I(x,y) - \bar(I(x,y))
   *
   * with \bar(I(x,y)) being a smoothed version of the input image.
   * he properties of the folding operation (here: distributivity) are used
   * to implement the unsharp mask filtering by a folding with the mask of size
   * (2*hX+1)x(2*hY+1). As smoothing filter, a mean
   * filter of size (2*hX+1)x(2*hY+1) is used.
   *
   * To determine the filter mask of a 3x3 unsharp mask filter.
   *
   * First, the mask for the calculation of
   *
   *  I_out = A # I <=>  I_out(x,y) = 2 * I(x,y)  (# is a folding, * a scalar multiplication)
   *
   * is given by
   *
   *      | 0    0    0 |
   *  A = | 0    2    0 | .
   *      | 0    0    0 |
   *
   * Due to the properties of the folding, ther is a mask G with:
   *
   *  I_out = A # I  - M # I = G # I
   *
   * The mask G is given by:
   *
   *  G = A - M
   *
   * The mask of the 3x3 filter is then:
   *
   *      | 1/9    1/9     1/9 |
   *      | 1/9   2-1/9    1/9 |
   *      | 1/9    1/9     1/9 |
   *
   */

  // Set the values of the kernel mask:
  //
  // I_out(x,y) = 2 * I(x,y) - \bar(I(x,y))
//  const double numValues = GetSizeX() * GetSizeY();
  const double numValues = hX * hY;

  for( unsigned int i = 0; i < numValues; i++ )
  {
    m_Coefficients[i] = -1.0 / numValues;
  }

  SetCoefficient( 0, 0, 2.0 - 1.0 / numValues );

}

/* Destructor (does nothing). */
UnsharpMaskKernel::~UnsharpMaskKernel()
{
}

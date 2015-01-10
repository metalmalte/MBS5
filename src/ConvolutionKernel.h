/** \file ConvolutionFilter.h
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
#ifndef ConvolutionKernel_h_
#define ConvolutionKernel_h_

#include <iostream>

/* Base class for all convolution kernels.
 *
 * A convolution kernel (or filter mask) is a 2D array
 * of size 2*hX+1 x 2*hY+1 used for convolution filtering.
 * In contrast to an image, the kernel(mask) is indexed from
 * -hX..hX to -hY...hY, with (0,0) the center of the mask.
 *
 * (-hX,-hY)... (-1,-hY)(0,-hY)(1,-hY)...(hX,-hY)
 *     :           :      :      :          :
 * (-hX,-1) ... (-1,-1) (0,-1) (1,-1) ... (hX,-1)
 * (-hX, 0) ... (-1, 0) (0, 0) (1, 0) ... (hX, 0)
 * (-hX, 1) ... (-1, 1) (0, 1) (1, 1) ... (hX, 1)
 *     :           :      :      :          :
 * (-hX,hY) ... (-1,hY) (0,hY) (1,hY) ... (hX,hY)
 *
 * The coefficients in the mask are accessed by GetCoefficient(k,m);
 * For example GetCoefficient(0,0) returns the center coefficient or
 * GetCoefficient(-1,0) the left neighbor of the center.
 */
class ConvolutionKernel
{
public:
  /* Constructor creates an 2*hX+1 x 2*hY+1 kernel with zero coefficients.
   * GetHalfSizeX() and GetHalfSizeY() will return hX, hY.
   * GetSizeX() and GetSizeY() will return 2*hX+1 and 2*hY+1. */
  ConvolutionKernel( const unsigned int hX = 1, const unsigned int hY = 1 );

  /* Destructor to delete the kernel array with coefficients. */
  virtual ~ConvolutionKernel();

  /* Get the kernel half-size for easy iteration over the mask. */
  int GetHalfSizeX() const;
  /* Get the kernel half-size for easy iteration over the mask. */
  int GetHalfSizeY() const;

  /* Compute and get the kernel size. */
  unsigned int GetSizeX() const;
  /* Compute and get the kernel size. */
  unsigned int GetSizeY() const;

  /* Get the kernel coefficient at mask position (i,j).
   * Kernel positions are indexed by -halfsize ... +halfsize. */
  double GetCoefficient( int i, int j ) const;

  /* Set the kernel coefficient at mask position (i,j).
   * Kernel positions are indexed by -halfsize ... +halfsize. */
  void SetCoefficient( int i, int j, double value );

protected:
  /* Member variable for the half-size of the kernel. */
  unsigned int m_HalfSizeX;
  /* Member variable for the half-size of the kernel. */
  unsigned int m_HalfSizeY;

  /* The array with kernel coefficients. */
  double *m_Coefficients;

private:
  /* Copy constructor is not implemented to avoid memory leaks */
  ConvolutionKernel( const ConvolutionKernel &other ); // Not implemented.
  /* Operator = (assignment) is not implemented to avoid memory leaks */
  void operator=( const ConvolutionKernel &other ); // Not implemented.
};

#endif /* ConvolutionKernel_h_ */

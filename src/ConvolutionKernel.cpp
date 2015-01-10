/** \file ConvolutionKernel.cpp
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
#include "ConvolutionKernel.h"

/* Constructor creates an 2*hX+1 x 2*hY+1 kernel with zero coefficients.
 * GetHalfSizeX() and GetHalfSizeY() will return hX, hY.
 * GetSizeX() and GetSizeY() will return 2*hX+1 and 2*hY+1. */
ConvolutionKernel::ConvolutionKernel( const unsigned int hX, const unsigned int hY )
{
  // Set half of height and width as member variables
  m_HalfSizeX = hX;
  m_HalfSizeY = hY;

  // compute size of the coefficient array
  unsigned int sizeX = m_HalfSizeX*2 +1;
  unsigned int sizeY = m_HalfSizeY*2 +1;
  unsigned int arraySize = sizeX * sizeY;

  // Allocate coefficients array
  m_Coefficients = new double[arraySize];

  // Fill coefficients array with 0
  for(unsigned int i = 0; i < arraySize; i++ )
  {
    m_Coefficients[i] = 0;
  }
}

/* Destructor to delete the kernel array with coefficients. */
ConvolutionKernel::~ConvolutionKernel()
{
  delete[] m_Coefficients;
}

/* Get the kernel half-size for easy iteration over the mask. */
int ConvolutionKernel::GetHalfSizeX() const
{
  return m_HalfSizeX;
}

/* Get the kernel half-size for easy iteration over the mask. */
int ConvolutionKernel::GetHalfSizeY() const
{
  return m_HalfSizeY;
}

/* Get the kernel size. */
unsigned int ConvolutionKernel::GetSizeX() const
{
  // Compute the size of the kernel and return this value
  return 2*m_HalfSizeX + 1;
}

/* Get the kernel size. */
unsigned int ConvolutionKernel::GetSizeY() const
{
  // Compute the size of the kernel and return this value
  return 2*m_HalfSizeY + 1;
}

/* Get the kernel coefficient at mask position (i,j).
 * Kernel positions are indexed by -halfsize ... +halfsize. */
double ConvolutionKernel::GetCoefficient( int i, int j ) const
{
  // Compute the correct position in the coefficient array
  int index = i + GetHalfSizeX() + (j + GetHalfSizeY()) * GetSizeX();

  // Check if you are outside the mask
  if( index < 0 || index >= static_cast<int>(GetSizeX() * GetSizeY()) )
  {
    std::cout << "Warning in ConvolutionKernel::GetCoefficient(): index outside kernel mask!";
    return 0;
  }

  // Return the coefficient
  return m_Coefficients[index];
}

/* Set the kernel coefficient at mask position (k,m).
 * Kernel positions are indexed by -halfsize ... +halfsize. */
void ConvolutionKernel::SetCoefficient( int i, int j, double value )
{
  // Compute the correct position in the coefficient array
  int index = i + GetHalfSizeX() + (j + GetHalfSizeY()) * GetSizeX();

  // Check if you are outside the mask
  if( index < 0 || index >= static_cast<int>(GetSizeX() * GetSizeY()) )
  {
    std::cout << "Warning in ConvolutionKernel::SetCoefficient(): index outside kernel mask!";
    return;
  }
  // Set the mask value
  m_Coefficients[index]=value;
}

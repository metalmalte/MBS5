/** \file ConvolutionFilter.cpp
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
#include "ConvolutionFilter.h"

/* Constructor. Creates a filter with the given kernel(mask) */
ConvolutionFilter::ConvolutionFilter()
{
  // Set kernel pointer to NULL.
  m_Kernel = NULL;
  // Set default boundary condition
  m_BoundaryCondition = REFLECT_BC;
}

/* Destructor */
ConvolutionFilter::~ConvolutionFilter()
{
  // nothing to do here
}

/* Execute the convolution filter. */
bool ConvolutionFilter::Execute()
{
  // First, create a valid output image.
  // This fails, if no valid input image is available.
  if( !CreateOutputImage() )
  {
    return false;
  }

  // Check if convolution kernel is set.
  if( m_Kernel == NULL )
  {
    std::cout << "Error: No convolution kernel set!" << std::endl;
    return false;
  }

  // A few constants required for the filtering.
  const int kernelHalfSizeX = m_Kernel->GetHalfSizeX();
  const int kernelHalfSizeY = m_Kernel->GetHalfSizeY();
  const int imageSizeX = static_cast<int>( m_InputImage->GetSizeX() );
  const int imageSizeY = static_cast<int>( m_InputImage->GetSizeY() );

  /*
   * The following code implements a folding with the kernel m_Kernel. The result is
   * written to m_OutputImage.
   *
   * The folding is given as:
   *
   *  f_out(x,y)=sum from{m=-hY} to{hY} sum from{k=-hX} to{hX} f(x+k,y+m) * g(k,m)
   *
   */

  if( GetBoundaryCondition() == ZERO_BC )
  {
    /*
     * The following code implements 0 boundary conditions, i.e. if (x+k,y+m) is outside of the image,
     * f(x+k,y+m) * g(i,j) = 0 is assumed.
     */

    // Iterate over all pixel coordinates.
    for( int y = 0; y < imageSizeY; y++ )
    {
      for( int x = 0; x < imageSizeX; x++ )
      {
        // variable to accumulate weighted gray-values
        double sumValue = 0;

        // iterate over all neighborhood pixel coordinates
        for( int m = -kernelHalfSizeY; m <= kernelHalfSizeY; m++ )
        {
          // Compute the pixel y coordinate for this kernel row
          int j = y + m;

          for( int k = -kernelHalfSizeX; k <= kernelHalfSizeX; k++ )
          {
            // Compute the pixel x coordinate for this kernel column
            int i = x + k;

            // Check boundary conditions
            if( j >= 0 && j < imageSizeY && i >= 0 && i < imageSizeX )
            {
              // Compute sum of weighted gray-values under the kernel mask
              sumValue += m_InputImage->GetPixel( i, j ) * m_Kernel->GetCoefficient( k, m );
            }
          }
        }
        m_OutputImage->SetPixel( x, y, static_cast<Image::PixelType>( sumValue ) );
      }
    }
  }
  else if( GetBoundaryCondition() == REFLECT_BC )
  {

    /*
     * The following code implements reflecting boundary conditions.
     */
    // Iterate over all pixel coordinates.
    for( int y = 0; y < imageSizeY; y++ )
    {
      for( int x = 0; x < imageSizeX; x++ )
      {
        // variable to accumulate weighted gray-values
        double sumValue = 0;

        // iterate over all neighborhood pixel coordinates
        for( int m = -kernelHalfSizeY; m <= kernelHalfSizeY; m++ )
        {
          // Compute the pixel y coordinate for this kernel row
          int j = y + m;
          // Apply boundary conditions if coordinate is outside the image
          if( j < 0 )
            j = -j - 1;
          else if( j >= imageSizeY )
            j = 2 * imageSizeY - j - 1;

          for( int k = -kernelHalfSizeX; k <= kernelHalfSizeX; k++ )
          {
            // Compute the pixel x coordinate for this kernel column
            int i = x + k;
            // Apply boundary conditions if coordinate is outside the image
            if( i < 0 )
              i = -i - 1;
            else if( i >= imageSizeX )
              i = 2 * imageSizeX - i - 1;

            // Compute sum of weighted gray-values under the kernel mask
            sumValue += m_InputImage->GetPixel( i, j ) * m_Kernel->GetCoefficient( k, m );
          }
        }
        m_OutputImage->SetPixel( x, y, static_cast<Image::PixelType>( sumValue ) );
      }
    }
  }
  else
  {
    std::cout << "ERROR in ConvolutionFilter::Execute(): Unknown boundary condition!\n";
    return false;
  }

  return true;
}

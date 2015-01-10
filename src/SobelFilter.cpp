/** \file SobelFilter.cpp
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
#include <math.h>
#include "SobelFilter.h"

/* Constructor creates an 3x3 sobel kernel  in X-direction
 *
 * Call the constructor of the bas class ConvolutionKernel
 * with correct size.
 * */
SobelKernelX::SobelKernelX() :
    ConvolutionKernel( 1, 1 )
{
  /* The Sobel mask is given by:
   *
   *      | -1  0  1 |
   * 1/8  | -2  0  2 |
   *      | -1  0  1 |
   */

  // coefficients are initialized with zero
  // set all non-zero values
  SetCoefficient( -1, -1, -1.0 / 8.0 );
  SetCoefficient( -1, 0, -2.0 / 8.0 );
  SetCoefficient( -1, 1, -1.0 / 8.0 );

  SetCoefficient( 1, -1, 1.0 / 8.0 );
  SetCoefficient( 1, 0, 2.0 / 8.0 );
  SetCoefficient( 1, 1, 1.0 / 8.0 );

}

SobelKernelY::SobelKernelY() :
    ConvolutionKernel( 1, 1 )
{
  /* The Sobel mask is given by:
   *
   *      | -1 -2 -1 |
   * 1/8  |  0  0  0 |
   *      |  1  2  1 |
   */

  // coefficients are initialized with zero
  // set all non-zero values
  SetCoefficient( -1, -1, -1.0 / 8.0 );
  SetCoefficient( 0, -1, -2.0 / 8.0 );
  SetCoefficient( 1, -1, -1.0 / 8.0 );

  SetCoefficient( -1, 1, 1.0 / 8.0 );
  SetCoefficient( 0, 1, 2.0 / 8.0 );
  SetCoefficient( 1, 1, 1.0 / 8.0 );
}

/* Constructor creates an Sobel filter */
SobelFilter::SobelFilter()
{
  // nothing to do here
}

/* Destructor (does nothing) */
SobelFilter::~SobelFilter()
{
}

/* Execute the Sobel filter. */
bool SobelFilter::Execute()
{
  // First, create a valid output image.
  // This fails, if no valid input image is available.
  if( !CreateOutputImage() )
    return false;

  /* The sobel edge detection is implemented as follows:
   *
   * (1) Folding with the sobel operator in x direction.
   * (2) Folding with the sobel operator in y direction.
   * (3) Calculation of the gradient |grad(I(x,y))| = sqrt(I_x(x,y)^2 + I_y(x,y)^2).
   *
   * Here, I_x and I_y are the results of the sobel operator.
   *
   * For the steps (1) and (2) the class convolution filter is used. The kernels
   * are used in the constructor to define the operation (see MIPExercise3.cpp).
   * The function sqrt() is used to calculate the square root. The result of
   * I_x(x,y)^2 + I_y(x,y)^2 first has to be converted to double to supress
   * error messages.
   */

  // create the sobel filter masks in X- and Y- direction
  SobelKernelX* kernelX = new SobelKernelX;
  SobelKernelY* kernelY = new SobelKernelY;

  // Convolve the image with the sobel X kernel.
  ConvolutionFilter* sobelXFilter = new ConvolutionFilter();
  sobelXFilter->SetKernel( kernelX );
  sobelXFilter->SetInputImage( m_InputImage );
  sobelXFilter->Execute();

  Image* sobelXImage = sobelXFilter->GetOutputImage();

  // Convolve the image with the sobel Y kernel.
  ConvolutionFilter* sobelYFilter = new ConvolutionFilter();
  sobelYFilter->SetKernel( kernelY );
  sobelYFilter->SetInputImage( m_InputImage );
  sobelYFilter->Execute();

  Image* sobelYImage = sobelYFilter->GetOutputImage();

  // Iterate over all image pixels and compute the magnitude.
  Image::PixelType gradMag;
  for( unsigned int y = 0; y < m_InputImage->GetSizeY(); y++ )
  {
    for( unsigned int x = 0; x < m_InputImage->GetSizeX(); x++ )
    {
      // Get the gradient values in x- and y- direction.
      Image::PixelType sobelXValue = sobelXImage->GetPixel( x, y );
      Image::PixelType sobelYValue = sobelYImage->GetPixel( x, y );

      // Compute sqrt( S_x^2 + S_y^2 ).
      // Do the cast to double, to avoid some compiler errors/warnings,
      // then cast the double-result back to the correct pixel type.
      gradMag = static_cast<Image::PixelType>( sqrt( static_cast<double>(
          sobelXValue * sobelXValue + sobelYValue * sobelYValue) ) );

      // Set the computed magnitude in the output image.
      m_OutputImage->SetPixel( x, y, gradMag );
    }
  }

  // Delete filter to free space.
  delete sobelXFilter;
  delete sobelYFilter;
  delete kernelX;
  delete kernelY;

  return true;
}


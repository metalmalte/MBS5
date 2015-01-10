/** \file ContrastStretchingFilter.cpp
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
#include "ContrastStretchingFilter.h"

/* Default constructor */
ContrastStretchingFilter::ContrastStretchingFilter()
{
}

/* Destructor */
ContrastStretchingFilter::~ContrastStretchingFilter()
{
}

/* Execute the window-level filter */
bool ContrastStretchingFilter::Execute()
{
  // First, create a valid output image by calling CreateOutputImage()
  // of the base class ImageFilter.
  // The resulting output image has the same size and spacing as the input
  // image and is accessible by the member variable m_OutputImage.

  // This returns false, if no valid input image is available
  // or an other error occurs.
  if( !CreateOutputImage() )
    return false;

  // Compute number of pixels.
  const unsigned int size = m_InputImage->GetSizeX() * m_InputImage->GetSizeY();

  // Find input min/max values.
  Image::PixelType inputMin = m_InputImage->GetPixel( 0 );
  Image::PixelType inputMax = m_InputImage->GetPixel( 0 );
  for( unsigned int i = 1; i < size; i++ )
  {
    const Image::PixelType value = m_InputImage->GetPixel( i );
    if( value < inputMin )
    {
      inputMin = value;
    }
    else if( value > inputMax )
    {
      inputMax = value;
    }
  }

  // Pre-compute scaling factor (out_max - out_min) / (in_max - in_min).
  const double scalingFactor = 255.0 / static_cast<double>( inputMax - inputMin );

  // Compute stretched greyvalues.
  for( unsigned int i = 0; i < size; i++ )
  {
    double value = scalingFactor * ( m_InputImage->GetPixel( i ) - inputMin );

    m_OutputImage->SetPixel( i, static_cast<Image::PixelType>( value ) );
  }

  return true;
}

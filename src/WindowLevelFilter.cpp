/** \file WindowLevelFilter.cpp
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
#include "WindowLevelFilter.h"

 /* Default constructor */
WindowLevelFilter::WindowLevelFilter()
{
  m_Window = 1;
  m_Level = 0;
}

/* Constructor for a given  window and level. */
WindowLevelFilter::WindowLevelFilter( const double window, const double level )
{
  m_Window = window;
  m_Level = level;
}

/* Destructor is empty*/
WindowLevelFilter::~WindowLevelFilter()
{
}

bool WindowLevelFilter::Execute()
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

  // Compute min, max from the given window and level.
  const double min = m_Level - 0.5 * m_Window;
  const double max = m_Level + 0.5 * m_Window;

  // Compute the scaling parameter for the linear scaling.
  const double scale = 255 / (max - min);

  double newValue;
  for( unsigned int i = 0; i < size; i++ )
  {
    double grayValue = static_cast<double> ( m_InputImage->GetPixel( i ) );

    // Check if gray-value is inside the window-level and compute new output value.
    if( grayValue < min )
      newValue = 0;
    else if( grayValue > max )
      newValue = 255;
    else
      newValue = (grayValue - min) * scale;

    m_OutputImage->SetPixel( i, static_cast<Image::PixelType> ( newValue ) );
  }

  return true;
}

/** \file BinaryThresholdFilter.cpp
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
#include "BinaryThresholdFilter.h"

 /* Default constructor */
BinaryThresholdFilter::BinaryThresholdFilter()
{
  m_LowerThreshold = 0;
  m_UpperThreshold = 4096;
}

/* Constructor for a given upper and lower threshold. */
BinaryThresholdFilter::BinaryThresholdFilter( const Image::PixelType lower, const Image::PixelType upper )
{
  m_LowerThreshold = lower;
  m_UpperThreshold = upper;
}

/* Destructor is empty*/
BinaryThresholdFilter::~BinaryThresholdFilter()
{
}

bool BinaryThresholdFilter::Execute()
{
  // First, create a valid output image by calling CreateOutputImage()
  // of the base class ImageFilter.
  // The resulting output image has the same size and spacing as the input
  // image and is accessible by the member variable m_OutputImage.

  // This returns false, if no valid input image is available
  // or an other error occurs.
  if( !CreateOutputImage() )
    return false;

  // Compute number of pixels
  const unsigned int size = m_InputImage->GetSizeX() * m_InputImage->GetSizeY();

  // Threshold the Image.
  for( unsigned int i = 0; i < size; i++ )
  {
    if( IsInside( m_InputImage->GetPixel( i ) ) )
    {
      m_OutputImage->SetPixel( i, 255 );
    }
    else
    {
      m_OutputImage->SetPixel( i, 0 );
    }
  }

  return true;
}

bool BinaryThresholdFilter::IsInside( Image::PixelType value )
{
  /*
   * Task 3: Implement the function, so that returns true, if
   * the value is between m_InsideValue and m_OutsideValue, and false
   * otherwise.
   */
  return ( value >= m_LowerThreshold && value <= m_UpperThreshold );

}

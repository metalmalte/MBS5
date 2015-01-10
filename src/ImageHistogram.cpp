/** \file ImageHistogram.cpp
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
#include <fstream>
#include "ImageHistogram.h"

/* Constructor. */
ImageHistogram::ImageHistogram()
{
  // Initialize variables.
  m_NumberOfHistogramValues = 0;
  m_HistogramValues = NULL;
  m_InputImage = NULL;

  m_MinValue = 0;
  m_MaxValue = 0;
}

/* Destructor. */
ImageHistogram::~ImageHistogram()
{
  // Delete array of histogram values.
  if( m_HistogramValues != NULL )
  {
    delete[] m_HistogramValues;
  }
}

/* Set the input image for histogram computation.
 * You have to set the input image before calling ComputeHistogram(). */
void ImageHistogram::SetInputImage( Image* inputImage )
{
  m_InputImage = inputImage;
}

/* Compute the absolute Histogram of the input image.
 * Returns true if successful.  */
bool ImageHistogram::ComputeHistogram()
{
  // Check if a valid input image is set.
  if( m_InputImage == NULL )
  {
    std::cout << "Error: Empty input image!";
    return false;
  }

  // Compute minimum maximum grey value.
  if( ! ComputeMinMaxValue( m_InputImage, m_MinValue, m_MaxValue ) )
  {
    return false;
  }

  // Allocate space for the histogram-values in the array m_HistogramValues.
  if( ! AllocateHistogramValues( m_MinValue, m_MaxValue ) )
  {
    return false;
  }

  // Compute absolute histogram values.
  for( unsigned int y = 0; y < m_InputImage->GetSizeY(); y++ )
  {
    for( unsigned int x = 0; x < m_InputImage->GetSizeX(); x++ )
    {
      Image::PixelType grayValue = m_InputImage->GetPixel( x, y );

      unsigned int histogramIndex = static_cast<unsigned int> ( grayValue - m_MinValue );

      m_HistogramValues[histogramIndex]++;
    }
  }


  return true;
}

/* Get the histogram-Value for a specific gray-value.
 * Call this after ComputeHistogram().
 * Return -1 if no histogram is computed.*/
double ImageHistogram::GetHistogramValue( Image::PixelType grayValue )
{
  if( m_HistogramValues == NULL )
  {
    return -1;
  }

  if( grayValue < m_MinValue || grayValue > m_MaxValue )
  {
    return 0;
  }

  unsigned int histogramIndex = static_cast<unsigned int> ( grayValue - m_MinValue );

  return m_HistogramValues[histogramIndex];
}

/* Save the computed histogram in a text-file. You can plot this histogram using
 * gnuplot or Excel etc. Call this after ComputeHistogram(). */
bool ImageHistogram::SaveHistogram( const char *fileName )
{
  return SaveHistogram( m_MinValue, m_MaxValue, fileName );
}

/* Save the computed histogram in a text-file. You can plot this histogram using
 * gnuplot or Excel etc. Call this after ComputeHistogram(). */
bool ImageHistogram::SaveHistogram(
    Image::PixelType fromValue, Image::PixelType toValue, const char *fileName )
{
  // Define an output stream.
  std::ofstream destination;

  // Open the file.
  destination.open( fileName, std::ios::out );
  if( !destination )
  {
    std::cout << "ERROR: Can not save histogram. Can not open file " << fileName << "!\n";
    return false;
  }

  // Write <greyvalue> TAB <histo-value>
  for( int greyValue = fromValue; greyValue <= toValue; greyValue++ )
  {
    destination << greyValue << "\t" << GetHistogramValue( greyValue ) << "\n";
  }

  // Close the file
  destination.close();

  return true;

}

/* Compute the minimum and maximum greyvalue in the image. */
bool ImageHistogram::ComputeMinMaxValue(
    const Image* inputImage, Image::PixelType &minValue, Image::PixelType &maxValue )
{
  if( inputImage == NULL )
  {
    std::cout << "Error: Can not compute Min/Max values: Empty input image!";
    return false;
  }

  // Compute minimum, maximum image value.
  minValue = inputImage->GetPixel( 0, 0 );
  maxValue = inputImage->GetPixel( 0, 0 );
  for( unsigned int y = 0; y < inputImage->GetSizeY(); y++ )
  {
    for( unsigned int x = 0; x < inputImage->GetSizeX(); x++ )
    {
      Image::PixelType value = inputImage->GetPixel( x, y );

      if( value < minValue )
        minValue = value;
      if( value > maxValue )
        maxValue = value;
    }
  }

  return true;
}

/* Allocate memory for the histogram for maxValue-minValue+1 histogram-values. */
bool ImageHistogram::AllocateHistogramValues(
    Image::PixelType minValue, Image::PixelType maxValue )
{
  if( maxValue < minValue )
  {
    std::cout << "Error: Can not allocate histogram values: Wrong minimum and maximum values !";
    return false;
  }

  // Compute size of histogram array.
  m_NumberOfHistogramValues = maxValue - minValue + 1;

  // Delete old array of histogram values.
  if( m_HistogramValues != NULL )
  {
    delete[] m_HistogramValues;
  }
  // Allocate array for histogram values.
  m_HistogramValues = new unsigned int[m_NumberOfHistogramValues];

  // Initialize histogram with zero values.
  for( unsigned int i = 0; i < m_NumberOfHistogramValues; i++ )
    m_HistogramValues[i] = 0;

  return true;
}

/** \file ImageHistogram.h
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
#ifndef ImageHistogram_h_
#define ImageHistogram_h_

#include "Image.h"

/* A simple class to calculate the absolute histogram of an image.
 *
 * This class is NOT a filter, because no output image is produced!
 *
 * You can use this class by:
 *
 *   ImageHistogram* histo = new ImageHistogram();
 *
 *   histo->SetInputImage( myInputImage );
 *   histo->ComputeHistogram();
 *
 *   // Ask for specific gray-value, e.g. 128.
 *   double histoValue = histo->GetHistogramValue( 128 );
 *
 *   // Save histogram to text file.
 *   histo->SaveHistogram( "histo.txt" ); */
class ImageHistogram
{
public:
  /* Constructor */
  ImageHistogram();
  /* Destructor */
  virtual ~ImageHistogram();

  /* Set the input image for histogram computation
   * You have to set the input image before calling ComputeHistogram(). */
  void SetInputImage( Image* inputImage );

  /* Compute the absolute Histogram of the input image.
   * Returns true if successful.  */
  bool ComputeHistogram();

  /* Get the histogram-Value for a specific gray-value
   * Call this after ComputeHistogram().
   * Return -1 if no histogram is computed. */
  double GetHistogramValue( Image::PixelType grayValue );

  /* Get the minimum gray value in the image. Call this after ComputeHistogram(). */
  Image::PixelType GetMinValue(){ return m_MinValue; }

  /* Get the maximum gray value in the image. Call this after ComputeHistogram(). */
  Image::PixelType GetMaxValue(){ return m_MaxValue; }

  /* Save the computed histogram in a text-file. You can plot this histogram
   * for example using gnuplot or Excel etc.
   * Call this after ComputeHistogram(). */
  bool SaveHistogram( const char *fileName );

  /* Save the computed histogram for a range of gray-values in a text-file.
   * You can plot this histogram using gnuplot or Excel etc.
   * Call this after ComputeHistogram(). */
 bool SaveHistogram(
     Image::PixelType fromValue,
     Image::PixelType toValue,
     const char *fileName );

protected:
  /* Compute the minimum and maximum gray value in the image. */
  bool ComputeMinMaxValue(
      const Image* inputImage,
      Image::PixelType &minValue,
      Image::PixelType &maxValue );

  /* Allocate memory for the histogram for maxValue-minValue+1 histogram-values. */
  bool AllocateHistogramValues(
      Image::PixelType minValue,
      Image::PixelType maxValue );

private:
  // The input image.
  Image* m_InputImage;

  // The number of values in the histogram.
  unsigned int m_NumberOfHistogramValues;
  // The array for the histogram.
  unsigned int *m_HistogramValues;

  // Minimum greyvalue in the image.
  Image::PixelType m_MinValue;
  // Maximum greyvalue in the image.
  Image::PixelType m_MaxValue;
};

#endif /* ImageHistogram_h_ */

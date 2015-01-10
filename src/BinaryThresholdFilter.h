/** \file BinaryThresholdFilter.h
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
#ifndef BinaryThresholdFilter_h_
#define BinaryThresholdFilter_h_

#include "ImageFilter.h"

/* A filter to perform a binary thresholding on an image. The output is
 * 255, if m_LowerThreshold <= g <= m_UpperThreshold and
 * 0  , elsewhere. */
class BinaryThresholdFilter: public ImageFilter
{
public:
  /* Default constructor */
  BinaryThresholdFilter();

  /* Constructor for a given  window and level. */
  BinaryThresholdFilter( const Image::PixelType lower, const Image::PixelType upper );

  /* Destructor */
  virtual ~BinaryThresholdFilter();

  /* Get/set the lower threshold. */
  Image::PixelType GetLowerThreshold() const { return m_LowerThreshold; }
  void SetLowerThreshold( const Image::PixelType thresh ) { m_LowerThreshold = thresh; }

  /* Get/set the upper threshold. */
  Image::PixelType GetUpperThreshold() const { return m_UpperThreshold; }
  void SetUpperThreshold( const Image::PixelType thresh ) { m_UpperThreshold = thresh; }

  /* Execute the binary threshold filter. */
  virtual bool Execute();

protected:

  /* Executes the thresholding for a pixel with a given grey value. Returns
   * true,  if m_LowerThreshold <= g <= m_UpperThreshold and
   * false, otherwise. */
  bool IsInside( Image::PixelType value );

  Image::PixelType m_LowerThreshold;
  Image::PixelType m_UpperThreshold;
};

#endif /* BinaryThresholdFilter_h_ */

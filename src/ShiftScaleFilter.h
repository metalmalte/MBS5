/** \file ShiftScaleFilter.h
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
#ifndef ShiftScaleFilter_h_
#define ShiftScaleFilter_h_

#include "ImageFilter.h"

/* This filter performs a linear transformation of the gray values in the image:
 *     S(g)= (g + shift) * scale.
 * To use this filter apply, e.g.:
 *
 *   Image* inputImage = new Image();
 *   ImageIO::Read( filename, inputImage );
 *
 *   ShiftScaleFilter* filter = new ShiftScaleFilter( shiftvalue, scalevalue );
 *   filter->SetInputImage( inputImage );
 *   filter->Execute();
 *   Image* outputImage = filter->GetOutputImage();
 *
 *   delete filter;
 *   delete inputImage;
 *
 * The default values are shift=0 and scale=1. The filter does NOT testing
 * for overflow! */
class ShiftScaleFilter: public ImageFilter
{
public:
  /* Constructor for a given shift and scale parameter. */
  ShiftScaleFilter( const double shift = 0.0, const double scale = 1.0 );
  /* Destructor */
  virtual ~ShiftScaleFilter();

  /* Execute the shift-scale filter. */
  virtual bool Execute();

protected:
  double m_Shift;
  double m_Scale;
};

#endif /* ShiftScaleFilter_h_ */

/** \file ContrastStretchingFilter.h
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
#ifndef ContrastStretchingFilter_h_
#define ContrastStretchingFilter_h_

#include "ImageFilter.h"

/* This filter performs a contrast stretching operation on the input image
 * (german: Histogramm-Spreizung). In low-contrast images, many greyvalues are
 * not used. The idea behind contrast stretching is to increase the dynamic
 * range of the gray levels in low-contrast images. In this filter, a linear
 * function is used to map the minimum (maximum) greyvalue g_min (g_max) in
 * the input image to minimum (maximum) value in the output image. For the
 * default output gray value range 0-255, the transformation is then given by:
 * S(g)= 255 * (g - g_min)/(g_max - g_min)
 * */
class ContrastStretchingFilter: public ImageFilter
{
public:
  /* Constructor for a given min/max of the output image. */
  ContrastStretchingFilter();
  /* Destructor. */
  virtual ~ContrastStretchingFilter();

  /* Execute the window-level filter. */
  virtual bool Execute();
};

#endif /* ContrastStretchingFilter_h_ */

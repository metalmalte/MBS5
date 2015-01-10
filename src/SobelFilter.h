/** \file SobelFilter.h
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
#ifndef SobelFilter_h_
#define SobelFilter_h_

#include "ImageFilter.h"
#include "ConvolutionKernel.h"
#include "ConvolutionFilter.h"

/* This class implements the kernel for sobel filtering
 * in X direction.
 * The Sobel mask is given by:
 *
 *      | -1  0  1 |
 * 1/8  | -2  0  2 |
 *      | -1  0  1 |
 */
class SobelKernelX: public ConvolutionKernel
{
public:
  /* Constructor creates an 3x3 sobel kernel  in X-direction*/
  SobelKernelX();
  /* Destructor (does nothing) */
  virtual ~SobelKernelX() {};
};

/* This class implements the kernel for sobel filtering
 * in Y direction.
 * The Sobel mask is given by:
 *
 *      | -1 -2 -1 |
 * 1/8  |  0  0  0 |
 *      |  1  2  1 |
 */
class SobelKernelY: public ConvolutionKernel
{
public:
  /* Constructor creates an 3x3 sobel kernel in Y-direction*/
  SobelKernelY();
  /* Destructor (does nothing) */
  virtual ~SobelKernelY() {};
};

/* This class implements the SobelFilter.
 *
 * SobelFiltering approximates the gradient magnitude in the image
 * and is defined by
 *
 * I_out(x,y)= sqrt( I_x(x,y)^2 + I_y(x,y)^2)
 *
 * where I_x and I_y are the results of convolution the input image
 * with the Sobel-Filter Masks in x- and y- direction.
 *
 * SobelFilter is derived from ImageFilter, because it is not a convolution.
 * Although, the computation of I_x and I_y is done by convolution.
 *
 * The SobelFilter is applied by
 *      SobelFilter myFilter;
 *
 *      myFilter.SetInputImage(image);
 *      myFilter.Execute();
 *      Image outImage = myFilter.GetOutputImage();
 *
 * The methods SetInputImage(..) and GetOutputImage()
 * are implemented in ImageFilter, the method Execute()
 * is implemented here. */
class SobelFilter: public ImageFilter
{
public:
  /* Constructor creates an Sobel filter */
  SobelFilter();
  /* Destructor (does nothing) */
  virtual ~SobelFilter();

  /* Execute the Sobel filter. */
  virtual bool Execute();
};

#endif /* SobelFilter_h_ */

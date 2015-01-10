/** \file GaussianKernel.h
 *
 * Module:    CS3303
 *            Medizinische Bild- und Signalverarbeitung
 *            Medizinische Bildverarbeitung
 *
 * Authors:   Jan Ehrhardt
 *
 * Copyright (c) 2014 Institute of Medical Informatics,
 *            University of Luebeck
 ********************************************************/
#ifndef GaussianKernel_h_
#define GaussianKernel_h_

#include "ConvolutionKernel.h"

/* This class implements the kernel for Gaussian filtering.
 * Gaussian filtering is done by convolution, use the class
 * ConvolutionFilter to perform filtering.
 *
 * The GaussianKernel (Gaussian filter mask) is a 2D array
 * with size  (width x height) and entries depending on the
 * standard deviation sigma.
 * The entries of the filtermask are computed according to the
 * Gaussion function:
 *
 * G(x,y) = 1/(2*PI*sigma^2)* exp(-(x*x + y*y)/(2*sigma*sigma))
 *
 * For example, Gaussian kernel with sigma=1.5 is constructed with
 *      GaussianKernel *myKernel = new GaussianKernel(1.5);
 * */
class GaussianKernel: public ConvolutionKernel
{
public:
  /* Constructor creates an Gaussian kernel for the given std. deviation. */
  GaussianKernel( double sigma );

  /* Destructor (does nothing). */
  virtual ~GaussianKernel() {};
};

#endif /* GaussianKernel_h_ */

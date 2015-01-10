/** \file LaplaceKernel.h
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
#ifndef LaplaceKernel_h_
#define LaplaceKernel_h_

#include "ConvolutionKernel.h"

/* This class implements a 3x3 kernel for Laplace filtering.
 * Laplace-filtering is done by convolution, use ConvolutionFilter
 * with this mask.
 * The 3x3 Laplace kernel (filter mask) is
 *
 *      |  0  1  0 |
 *      |  1 -4  1 |
 *      |  0  1  0 |
 *
 * This class is very simple because only 3x3 masks are
 * supported. Therefore no parameters (width and height)
 * are needed. */
class LaplaceKernel: public ConvolutionKernel
{
public:
  /* Constructor creates an 3x3 Laplace kernel */
  LaplaceKernel();

  /* Destructor (does nothing) */
  virtual ~LaplaceKernel() {};
};

#endif /* LaplaceKernel_h_° */

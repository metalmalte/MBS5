/** \file BinomialKernel.h
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
#ifndef BinomialKernel_h_
#define BinomialKernel_h_

#include "ConvolutionKernel.h"

/* This class implements a 3x3 kernel for binomial filtering.
 * Binomial-filtering is done by convolution, use ConvolutionFilter
 * with this mask.
 * The 3x3 binomial kernel (filter mask) is
 *
 *      | 1  2  1 |
 * 1/16 | 2  4  2 |
 *      | 1  2  1 |
 *
 * This class is very simple because only 3x3 masks are
 * supported. Therefore no parameters (width and height)
 * are needed. */
class BinomialKernel: public ConvolutionKernel
{
public:
  /* Constructor creates an 3x3 binomial kernel */
  BinomialKernel();

  /* Destructor (does nothing) */
  virtual ~BinomialKernel() {}
};

#endif /* BinomialKernel_h_ */

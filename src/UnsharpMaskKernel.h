/** \file UnsharpMaskKernel.h
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
#ifndef UnsharpMaskKernel_h_
#define UnsharpMaskKernel_h_

#include "ConvolutionKernel.h"

/* This class implements the kernel for unsharp mask filtering.
 * Unsharp mask filtering is done by convolution and is given by
 *
 * I_out(x,y) = 2 * I_in(x,y) - \bar(I_in(x,y)),
 *
 * were \bar(I_in(x,y)) is a smoothed version of the input image.
 * Smoothing is done using a mean filter of size (2*hX+1)x(2*hY+1).
 *
 * In the constructor the half-sizes hX and hY of the
 * unsharp mask kernel are needed as argument to create a
 * (2*hX+1)x(2*hY+1) filter kernel. */
class UnsharpMaskKernel: public ConvolutionKernel
{
public:
  /* Constructor, creates an 2*hX+1 x 2*hY+1 unsharp mask kernel */
  UnsharpMaskKernel(unsigned int hX=1, unsigned int hY=1);

  /* Destructor (does nothing). */
  virtual ~UnsharpMaskKernel();
};

#endif /* UnsharpMaskKernel_h_ */

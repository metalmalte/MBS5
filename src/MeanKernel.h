/** \file MeanKernel.h
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
#ifndef MeanKernel_h_
#define MeanKernel_h_

#include "ConvolutionKernel.h"

/* This class implements the kernel for mean filtering.
 * Mean-filtering is done by convolution, use the class
 * ConvolutionFilter to perform filtering.
 *
 * The MeanKernel (mean filter mask) is a 2D array
 * of size  width x height with all entries having the same
 * coefficient value of 1/(width*height) 
 * and width = 2*hX+1, height = 2*hY+1.
 * For example, the 3x3 mean kernel is constructed with
 *      MeanKernel *myKernel = new MeanKernel(1,1);
 *
 * and has coefficients:
 *  1/9 1/9 1/9
 *  1/9 1/9 1/9
 *  1/9 1/9 1/9
 *
 * For example, the 3x3 mean filter is applied by
 *
 *   ConvolutionFilter* myFilter = new ConvolutionFilter();
 *   MeanKernel* meanKernel = new MeanKernel(1,1);
 *
 *   myFilter->SetInputImage( image );
 *   myFilter->SetKernel( meanKernel );
 *   myFilter->Execute() )
 *   Image *outImage = myFilter->GetOutputImage(); */
class MeanKernel: public ConvolutionKernel
{
public:
  /* Constructor creates an 2*hX+1 x 2*hY+1 mean kernel. */
  MeanKernel( unsigned int hX = 1, unsigned int hY = 1 );

  /* Destructor (does nothing). */
  virtual ~MeanKernel();
};

#endif /* MeanKernel_h_ */

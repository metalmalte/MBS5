/** \file ConvolutionFilter.h
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

#ifndef ConvolutionFilter_h_
#define ConvolutionFilter_h_

#include "ImageFilter.h"
#include "ConvolutionKernel.h"

/* Defines an base class for all convolution filter operations.
 *
 * For this class a filter kernel (filter mask) has to be provided
 * with SetKernel(..). Executing this filter convolves the image
 * with this kernel.
 *
 * The filters can be used in the following way:
 *
 *   //create a kernel object (see ConvolutionKernel and derived classes)
 *
 *   ConvolutionFilter* myFilter = new ConvolutionFilter();
 *
 *   myFilter->SetInputImage( myInputImage );
 *   myFilter->SetKernel( kernel );
 *   if( ! myFilter->Execute())
 *   {
 *     // Error handling.
 *   }
 *   Image *outImage = myFilter->GetOutputImage();
*/
class ConvolutionFilter : public ImageFilter
{
public:
  /* Constructor. */
  ConvolutionFilter();

  /* Destructor. */
  virtual ~ConvolutionFilter();

  typedef enum {ZERO_BC=0, REFLECT_BC=1} BoundaryConditionType;

  /* Return the convolution kernel. */
  ConvolutionKernel* GetKernel() const { return m_Kernel; }

  void SetKernel( ConvolutionKernel* kernel ) { m_Kernel = kernel; }

  void SetBoundaryCondition(BoundaryConditionType boundaryCond) { m_BoundaryCondition=boundaryCond;};
  BoundaryConditionType GetBoundaryCondition() const { return m_BoundaryCondition;};
  
  /* Execute the convolution filter. */
  virtual bool Execute();

protected:
  /* The convolution kernel used for filtering. */
  ConvolutionKernel* m_Kernel;
  BoundaryConditionType m_BoundaryCondition;
};

#endif /* ConvolutionFilter_h_ */

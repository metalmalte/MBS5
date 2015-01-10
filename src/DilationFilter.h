/** \file DilationFilter.h
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

#ifndef DilationFilter_h_
#define DilationFilter_h_

#include "ImageFilter.h"
#include "StructureElement.h"

/* Defines the morphological Dilation filter.
 *
 * For this class a StructureElement has to be provided
 * in the constructor. Executing this filter performs a Dilation of the image
 * with this StructureElement.
 *
 * The filters can be used in the following way:
 *
 *   DilationFilter filter = new DilationFilter();
 *   filter->SetStructureElement( structureKernel );
 *   filter->SetInputImage( inputImage );
 *   if( !filter->Execute() )
 *   {
 *     // Error handling.
 *   }
 *   Image* outputImage = filter->GetOutputImage();
 */
class DilationFilter: public ImageFilter
{
public:
  /* Constructor. */
  DilationFilter();

  /* Destructor. */
  virtual ~DilationFilter();

  /* Set the structure element for the filter. */
  void SetStructureElement( StructureElement* structureElement );

  /* Execute the Dilation filter.*/
  virtual bool Execute();

protected:
  /* The structure element used for filtering. */
  StructureElement* m_StructureElement;
};

#endif /* DilationFilter_h_ */

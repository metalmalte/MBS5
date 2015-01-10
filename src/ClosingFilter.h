/** \file ClosingFilter.h
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

#ifndef ClosingFilter_h_
#define ClosingFilter_h_

#include "ImageFilter.h"
#include "StructureElement.h"

/* Defines the morphological Closing filter.
 *
 * For this class a StructureElement has to be provided
 * in the constructor. Executing this filter performs a Closing of the image
 * with this StructureElement.
 *
 * The filters can be used in the following way:
 *
 *   //create a StructureElement object (see StructureElement and derived classes)
 *
 *   ClosingFilter filter = new ClosingFilter();
 *   filter->SetStructureElement( structureKernel );
 *   filter->SetInputImage( inputImage );
 *   if( !filter.Execute() )
 *   {
 *     // Error handling.
 *   }
 *   Image* outputImage = filter->GetOutputImage();
 *
 */
class ClosingFilter: public ImageFilter
{
public:
  /* Constructor. */
  ClosingFilter();

  /* Destructor */
  virtual ~ClosingFilter();

  /* Set the structure element for the filter. */
  void SetStructureElement( StructureElement* structureElement );

  /* Execute the Closing filter. */
  virtual bool Execute();

protected:
  /* The structure element used for filtering. */
  StructureElement* m_StructureElement;
};

#endif /* ClosingFilter_h_ */

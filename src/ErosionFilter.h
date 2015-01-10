/** \file ErosionFilter.h
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

#ifndef ErosionFilter_h_
#define ErosionFilter_h_

#include "ImageFilter.h"
#include "StructureElement.h"

/* Defines the morphological erosion filter.
 *
 * For this class a StructureElement has to be provided
 * in the constructor. Executing this filter performs an erosion of the image
 * with this StructureElement.
 *
 * The filters can be used in the following way:
 *
 *   ErosionFilter* filter = new ErosionFilter();
 *   filter->SetStructureElement( structureKernel );
 *   filter->SetInputImage( inputImage );
 *   if( !filter.Execute() )
 *   {
 *     // Error handling.
 *   }
 *   Image* outputImage = filter->GetOutputImage();
 */
class ErosionFilter: public ImageFilter
{
public:
  /* Constructor. */
  ErosionFilter();

  /* Destructor. */
  virtual ~ErosionFilter();

  /* Set the structure element for the filter. */
  void SetStructureElement( StructureElement* structureElement );

  /* Execute the erosion filter. */
  virtual bool Execute();

protected:
  /* The structure element used for filtering. */
  StructureElement* m_StructureElement;
};

#endif /* ErosionFilter_h_ */

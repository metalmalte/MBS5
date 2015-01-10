/** \file OpeningFilter.h
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

#ifndef OpeningFilter_h_
#define OpeningFilter_h_

#include "ImageFilter.h"
#include "StructureElement.h"

/* Defines the morphological Opening filter.
 *
 * For this class a StructureElement has to be provided
 * in the constructor. Executing this filter performs a Opening of the image
 * with this StructureElement.
 *
 * The filters can be used in the following way:
 *
 *   OpeningFilter* filter = new OpeningFilter();
 *   filter->SetStructureElement( structureKernel );
 *   filter->SetInputImage( inputImage );
 *   if( !filter.Execute() )
 *   {
 *     // Error handling.
 *   }
 *   Image* outputImage = filter->GetOutputImage();
 */
class OpeningFilter: public ImageFilter
{
public:
  /* Constructor. */
  OpeningFilter();

  /* Destructor. */
  virtual ~OpeningFilter();

  /* Set the structure element for the filter. */
  void SetStructureElement( StructureElement* structureElement );

  /* Execute the Opening filter. */
  virtual bool Execute();

protected:
  /* The structure element used for filtering. */
  StructureElement* m_StructureElement;
};

#endif /* OpeningFilter_h_ */

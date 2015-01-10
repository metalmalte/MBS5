/** \file OpeningFilter.cpp
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
#include <iostream>
#include <limits>
#include "OpeningFilter.h"
#include "DilationFilter.h"
#include "ErosionFilter.h"

/* Constructor.*/
OpeningFilter::OpeningFilter()
{
  // Set structure element to NULL.
  m_StructureElement = NULL;
}

/* Destructor. */
OpeningFilter::~OpeningFilter()
{
  // Nothing to do here.
}

/* Set the structure element for the filter. */
void OpeningFilter::SetStructureElement(  StructureElement* structureElement )
{
  m_StructureElement = structureElement;
}

/* Execute the Opening filter.*/
bool OpeningFilter::Execute()
{
  // Check if structure element is set.
  if( m_StructureElement == NULL )
  {
    std::cout << "Error: No structure element set!" << std::endl;
    return false;
  }

  // First, create a valid output image.
  // This fails, if no valid input image is available.
  if( !CreateOutputImage() )
  {
    return false;
  }

  // The morphological opening is implemented as follows:
  //
  // (1) Apply an erosion with structure element E on the input image
  // (2) Apply a dilation with the same structure element E on the result of the erosion
  // (3) Output image is the result of the dilation

  //
  // Perform Erosion.
  ErosionFilter* erosionFilter = new ErosionFilter();
  erosionFilter->SetStructureElement( m_StructureElement );
  erosionFilter->SetInputImage( m_InputImage );
  if( !erosionFilter->Execute() )
  {
    std::cout << "Error: Erosion failed!" << std::endl;
    return false;
  }

  //
  // Perform Dilation.
  DilationFilter* dilationFilter = new DilationFilter();
  dilationFilter->SetStructureElement( m_StructureElement );
  dilationFilter->SetInputImage( erosionFilter->GetOutputImage() );
  if( !dilationFilter->Execute() )
  {
    std::cout << "Error: Dilation failed!" << std::endl;
    return false;
  }

  // Set the output of this filter to the result of the two operations.
  m_OutputImage->CloneImage( dilationFilter->GetOutputImage() );

  // Delete filter.
  delete dilationFilter;
  delete erosionFilter;

  return true;
}

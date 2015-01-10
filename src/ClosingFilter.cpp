/** \file ClosingFilter.cpp
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
#include "ClosingFilter.h"
#include "DilationFilter.h"
#include "ErosionFilter.h"

/* Constructor. */
ClosingFilter::ClosingFilter()
{
  // Set structure element to NULL.
  m_StructureElement = NULL;
}

/* Destructor */
ClosingFilter::~ClosingFilter()
{
  // Nothing to do here.
}

/* Set the structure element for the filter. */
void ClosingFilter::SetStructureElement(  StructureElement* structureElement )
{
  m_StructureElement = structureElement;
}

/* Execute the Closing filter.*/
bool ClosingFilter::Execute()
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

  // The morphological closing is implemented as follows:
  //
  // (1) Apply a dilation with structure element E on the input image
  // (2) Apply an erosion with the same structure element E on the result of the Dilation
  // (3) Output image is the result of the erosion

  //
  // Perform dilation:
  DilationFilter* dilationFilter = new DilationFilter();
  dilationFilter->SetStructureElement( m_StructureElement );
  dilationFilter->SetInputImage( m_InputImage );
  if( !dilationFilter->Execute() )
  {
    std::cout << "Error: Dilation failed!" << std::endl;
    return false;
  }

  //
  // Perform erosion:
  ErosionFilter* erosionFilter = new ErosionFilter();
  erosionFilter->SetStructureElement( m_StructureElement );
  erosionFilter->SetInputImage( dilationFilter->GetOutputImage() );
  if( !erosionFilter->Execute() )
  {
    std::cout << "Error: Erosion failed!" << std::endl;
    return false;
  }

  // Set the output of this filter to the result of the two operations.
  m_OutputImage->CloneImage( erosionFilter->GetOutputImage() );

  // Delete filter.
  delete erosionFilter;
  delete dilationFilter;

  return true;
}

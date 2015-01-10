/** \file DilationFilter.cpp
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
#include "DilationFilter.h"

/* Constructor. */
DilationFilter::DilationFilter()
{
  // Set structure element to NULL.
  m_StructureElement = NULL;
}

/* Destructor. */
DilationFilter::~DilationFilter()
{
  // Nothing to do here.
}

/* Set the structure element for the filter. */
void DilationFilter::SetStructureElement(  StructureElement* structureElement )
{
  m_StructureElement = structureElement;
}

/* Execute the Dilation filter. */
bool DilationFilter::Execute()
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

  // We define few constants required for the filtering. It is more efficient to
  // use constants instead of calling the member functions in each iteration.
  const int kernelHalfSizeX = m_StructureElement->GetHalfSizeX();
  const int kernelHalfSizeY = m_StructureElement->GetHalfSizeY();

  // We cast the size to int to avoid signed/unsigned warnings in the boundary checking.
  const int imageSizeX = static_cast<int> ( m_InputImage->GetSizeX() );
  const int imageSizeY = static_cast<int> ( m_InputImage->GetSizeY() );

  // Iterate over all pixel coordinates.
  for( int y = 0; y < imageSizeY; y++ )
  {
    for( int x = 0; x < imageSizeX; x++ )
    {
      // Variable to compute the minimum of the binary/gray values
      // We have to initialize this variable with the minimum possible value
      // The C++ standard function std::numeric_limits<type>::min() will return
      // the minimum for all standard types (char,int, unsigned int, short, float etc.)
      // Because Image::PixelType is one of the standard types, this will work here.
      Image::PixelType maximumValue = std::numeric_limits<Image::PixelType>::min();

      // Iterate over all neighborhood pixel coordinates.
      for( int m = -kernelHalfSizeY; m <= kernelHalfSizeY; m++ )
      {
        // Compute the pixel y coordinate for this kernel row.
        int j = y + m;

        // Apply reflected boundary conditions if coordinate is outside the image.
        if( j < 0 )
        {
          j = -j - 1;
        }
        else if( j >= imageSizeY )
        {
          j = 2 * imageSizeY - j - 1;
        }

        for( int k = -kernelHalfSizeX; k <= kernelHalfSizeX; k++ )
        {
          // Compute the pixel x coordinate for this kernel column.
          int i = x + k;

          // Apply reflected boundary conditions if coordinate is outside the image.
          if( i < 0 )
          {
            i = -i - 1;
          }
          else if( i >= imageSizeX )
          {
            i = 2 * imageSizeX - i - 1;
          }

          // Check if we are this kernel location is inside the Structure element.
          if( m_StructureElement->IsInside( k, m ) )
          {
            // Update the maximum value.
            if( maximumValue < m_InputImage->GetPixel( i, j ) )
            {
              maximumValue = m_InputImage->GetPixel( i, j );
            }
          }
        }
      }
      // Set the maximum value at the current position in the output image.
      m_OutputImage->SetPixel( x, y, maximumValue );
    }
  }

  return true;
}

/** \file RegionGrowingFilter.cpp
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
#include "RegionGrowingFilter.h"

 /* Default constructor */
RegionGrowingFilter::RegionGrowingFilter()
{
}

/* Constructor for a given upper and lower threshold. */
RegionGrowingFilter::RegionGrowingFilter( const Image::PixelType lower, const Image::PixelType upper ) :
    BinaryThresholdFilter( lower, upper )
{
}

/* Destructor (does nothing). */
RegionGrowingFilter::~RegionGrowingFilter()
{
}

/* Add coordinates of a seed point to the stack. */
void RegionGrowingFilter::AddSeedPoint( const unsigned int seedX, const unsigned int seedY )
{
  Point seed;
  seed.x = seedX;
  seed.y = seedY;
  m_SeedPoints.push( seed );
}

/* Clear all seed points in the stack. */
void RegionGrowingFilter::ClearSeedPoints()
{
  while( !m_SeedPoints.empty() )
  {
    m_SeedPoints.pop();
  }
}

bool RegionGrowingFilter::Execute()
{
  // First, create a valid output image by calling CreateOutputImage()
  // of the base class ImageFilter.
  // The resulting output image has the same size and spacing as the input
  // image and is accessible by the member variable m_OutputImage.

  // This returns false, if no valid input image is available
  // or an other error occurs.
  if( !CreateOutputImage() )
    return false;

  // Set each pixel of the output to -1 to indicate that the point is unchecked.
  const unsigned int size = m_InputImage->GetSizeX() * m_InputImage->GetSizeY();
  for( unsigned int i = 0; i < size; ++i )
  {
    m_OutputImage->SetPixel( i, -1 );
  }

  // Add each seed point to the set of border points.
  while( !m_SeedPoints.empty() )
  {
    Point point = m_SeedPoints.top();
    m_SeedPoints.pop();
    CheckAndAddPoint( point.x, point.y );
  }

  // For each border point, add each neighbor to the set of border points if
  // it is unchecked and inside the interval. This is done by the method
  // CheckAndAddPoint().
  while( !m_BorderPoints.empty() )
  {
    // Get the last point of the stack.
    Point point = m_BorderPoints.top();
    m_BorderPoints.pop();

    // Add each neighbor point to the stack.
    CheckAndAddPoint( point.x + 1, point.y );
    CheckAndAddPoint( point.x - 1, point.y );
    CheckAndAddPoint( point.x, point.y + 1 );
    CheckAndAddPoint( point.x, point.y - 1 );
  }

  // Set each unchecked pixel of the output image to outside value.
  for( unsigned int i = 0; i < size; ++i )
  {
    if( m_OutputImage->GetPixel( i ) == -1 )
    {
      m_OutputImage->SetPixel( i, 0 );
    }
  }

  return true;
}

/* Add a point to the stack, if it is unchecked and inside the region. */
void RegionGrowingFilter::CheckAndAddPoint( const unsigned int x, const unsigned int y )
{
  // Check if point is out of the image boundaries.
  if( x < 0 || x >= m_InputImage->GetSizeX() ||
      y < 0 || y >= m_InputImage->GetSizeY() )
  {
    return;
  }

  // Check if the point is currently unchecked.
  if( m_OutputImage->GetPixel( x, y ) == -1 )
  {
    // Check is point is inside the interval.
    if( IsInside( m_InputImage->GetPixel( x, y ) ) )
    {
      // Set pixel to the inside value.
      m_OutputImage->SetPixel( x, y, 255 );

      // Add point to the stack of border points.
      Point point;
      point.x = x;
      point.y = y;
      m_BorderPoints.push( point );
    }
    else
    {
      // Set pixel to the outside value.
      m_OutputImage->SetPixel( x, y, 0 );
    }
  }
}

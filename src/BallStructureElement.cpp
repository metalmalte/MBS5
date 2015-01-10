/** \file BallStructureElement.cpp
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
#include "BallStructureElement.h"

/* Constructor creates a ball structure element of size
 * (2*radius+1) x (2*radius+1).
 * GetHalfSizeX() and GetHalfSizeY() will return radius.
 * GetSizeX() and GetSizeY() will return 2*radius+1. */
BallStructureElement::BallStructureElement( const unsigned int radius ) :
    StructureElement( radius, radius )
{
  // The constructor of the base class is called to create a structure
  // element with the correct size.

  // Compute the squared radius to avoid sqrt().
  double squareRadius = radius * radius;

  // Go over all elements and set to TRUE, if the distance is smaller or
  // equal to the radius. Set to FALSE otherwise.
  for( int i = -GetHalfSizeX(); i <= GetHalfSizeX(); i++ )
    for( int j = -GetHalfSizeY(); j <= GetHalfSizeY(); j++ )
    {
      // Compute the squared distance to the center of the structure element.
      double squareDist = i * i + j * j;
      // Compare squared distance to the squared radius and set to TRUE/FALSE.
      if( squareDist <= squareRadius )
      {
        SetInside( i, j, true );
      }
      else
      {
        SetInside( i, j, false );
      }
    }
}

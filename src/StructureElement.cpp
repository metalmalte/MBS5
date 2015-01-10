/** \file StructureElement.cpp
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
#include "StructureElement.h"

/* Constructor creates an 2*hX+1 x 2*hY+1 StructureElement with all elements
 * set to false except the center.
 * GetHalfSizeX() and GetHalfSizeY() will return hX, hY.
 * GetSizeX() and GetSizeY() will return 2*hX+1 and 2*hY+1. */
StructureElement::StructureElement( unsigned int hX, unsigned int hY )
{
  // Set half of height and width as member variables.
  m_HalfSizeX = hX;
  m_HalfSizeY = hY;

  // Compute size of the coefficient array.
  unsigned int sizeX = m_HalfSizeX * 2 + 1;
  unsigned int sizeY = m_HalfSizeY * 2 + 1;
  unsigned int arraySize = sizeX * sizeY;

  // Allocate elements bool array.
  m_Elements = new bool[arraySize];

  // Fill array with false.
  for( unsigned int i = 0; i < arraySize; i++ )
  {
    m_Elements[i] = false;
  }
  // Set center to true.
  SetInside( 0, 0, true );
}

/* Destructor to delete the array with coefficients. */
StructureElement::~StructureElement()
{
  delete[] m_Elements;
}

/* Get the StructureElement half-size for easy iteration over the mask. */
int StructureElement::GetHalfSizeX() const
{
  return m_HalfSizeX;
}

/* Get the StructureElement half-size for easy iteration over the mask. */
int StructureElement::GetHalfSizeY() const
{
  return m_HalfSizeY;
}

/* Compute and get the StructureElement size. */
unsigned int StructureElement::GetSizeX() const
{
  return 2 * m_HalfSizeX + 1;
}

/* Compute and get the StructureElement size. */
unsigned int StructureElement::GetSizeY() const
{
  return 2 * m_HalfSizeY + 1;
}

/* Returns true if the position (i,j) is part of the StructureElement,
 * else returns false.
 * StructureElement positions are indexed by -halfsize ... +halfsize */
bool StructureElement::IsInside( int i, int j ) const
{
  // Compute the correct position in the array.
  int index = i + GetHalfSizeX() + (j + GetHalfSizeY()) * GetSizeX();

  // Check if you are outside the mask.
  if( index < 0 || index >= static_cast<int> ( GetSizeX() * GetSizeY() ) )
  {
    std::cout << "Warning in StructureElement::IsInside(): index outside kernel mask!";
    return 0;
  }

  // Return the element value.
  return m_Elements[index];
}

/* Set the value of the StructureElement at position (i,j).
 * StructureElement positions are indexed by -halfsize ... +halfsize */
void StructureElement::SetInside( int i, int j, bool value )
{
  // Compute the correct position in the array.
  int index = i + GetHalfSizeX() + (j + GetHalfSizeY()) * GetSizeX();

  // Check if you are outside the mask.
  if( index < 0 || index >= static_cast<int> ( GetSizeX() * GetSizeY() ) )
  {
    std::cout << "Warning in StructureElement::SetCoefficient(): index outside kernel mask!";
    return;
  }
  // Set the element value.
  m_Elements[index] = value;
}

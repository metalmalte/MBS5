/** \file StructureElement.h
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
#ifndef StructureElement_h_
#define StructureElement_h_

#include <iostream>

/* Base class for all morphological structure elements.
 *
 * A structure element is a 2D array
 * of size 2*hX+1 x 2*hY+1 used for morphological filtering.
 * In contrast to an image, the StructureElement is indexed from
 * -hX..hX to -hY...hY, with (0,0) the center of the StructureElement.
 *
 * (-hX,-hY)... (-1,-hY)(0,-hY)(1,-hY)...(hX,-hY)
 *     :           :      :      :          :
 * (-hX,-1) ... (-1,-1) (0,-1) (1,-1) ... (hX,-1)
 * (-hX, 0) ... (-1, 0) (0, 0) (1, 0) ... (hX, 0)
 * (-hX, 1) ... (-1, 1) (0, 1) (1, 1) ... (hX, 1)
 *     :           :      :      :          :
 * (-hX,hY) ... (-1,hY) (0,hY) (1,hY) ... (hX,hY)
 *
 * A StructureElement is very similar to a ConvolutionKernel, but
 * there are only boolean coefficients (true/false) indicating if this
 * position is inside or not inside the StructureElement.
 * For example, a cross-shaped 3x3 StructureElement will look like
 *  0 1 0
 *  1 1 1   0/1 - indicates false/true
 *  0 1 0
 *  and a 3x3 square element will look like
 *  1 1 1
 *  1 1 1   0/1 - indicates false/true
 *  1 1 1
 *
 * You can test, if a position is inside the  StructureElement by the
 * member function IsInside(i,j).
 * For example IsInside(0,0) returns the center value or
 * IsInside(-1,0) the left neighbor of the center.
 *
 * Similar to the ConvolutionKernel, no reference counting is used and
 * the array with coefficients are copied in memory in the copy-constructor
 * and in the operator=.
 */
class StructureElement
{
public:
  /* Constructor creates an (2 * hX + 1) x (2 * hY + 1) StructureElement with
   * all elements set to false except the center.
   * GetHalfSizeX() and GetHalfSizeY() will return hX, hY.
   * GetSizeX() and GetSizeY() will return 2 * hX + 1 and 2 * hY + 1.*/
  StructureElement( unsigned int hX = 1, unsigned int hY = 1 );

  /* Destructor to delete the structure element array with coefficients. */
  virtual ~StructureElement();

  /* Get the StructureElement half-size for easy iteration over the mask. */
  int GetHalfSizeX() const;
  /* Get the StructureElement half-size for easy iteration over the mask. */
  int GetHalfSizeY() const;

  /* Compute and get the StructureElement size. */
  unsigned int GetSizeX() const;
  /* Compute and get the StructureElement size. */
  unsigned int GetSizeY() const;

  /* Returns true if the position (i,j) is part of the StructureElement,
   * else returns false.
   * StructureElement positions are indexed by -halfsize ... +halfsize */
  bool IsInside( int i, int j ) const;

protected:

  /* Set the value of the StructureElement at position (i,j).
   * StructureElement positions are indexed by -halfsize ... +halfsize */
  void SetInside( int i, int j, bool value );

  // Member variable for the half-size of the kernel.
  unsigned int m_HalfSizeX;
  // Member variable for the half-size of the kernel.
  unsigned int m_HalfSizeY;

  // The array with StructureElement coefficients.
  bool *m_Elements;
};

#endif /* StructureElement_h_ */

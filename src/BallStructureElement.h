/** \file BallStructureElement.h
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
#ifndef BallStructureElement_h_
#define BallStructureElement_h_

#include "StructureElement.h"

/* This class implements a Ball structure elements for
 * morphological operations. This class is derived from
 * StructureElement and you can use the member function IsInside(i,j),
 * GetHalfSizeX/Y() and so on.
 * For example a 5x5 Ball element (radius=2) will look like
 *  0 0 1 0 0
 *  0 1 1 1 0
 *  1 1 1 1 1   0/1 - indicates false/true
 *  0 1 1 1 0
 *  0 0 1 0 0 */
class BallStructureElement: public StructureElement
{
public:
  /* Constructor creates a ball structure element of size
   * (2*radius+1) x (2*radius+1), per default a 3x3 element
   * is created.*/
  BallStructureElement( const unsigned int radius = 1 );

  /* Destructor (does nothing) */
  virtual ~BallStructureElement() {}
};

#endif /* BallStructureElement_h_ */

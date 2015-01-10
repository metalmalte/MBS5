/** \file RegionGrowingFilter.h
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
#ifndef RegionGrowingFilter_h_
#define RegionGrowingFilter_h_

#include "BinaryThresholdFilter.h"
#include <stack>

/* A filter to perform a region growing. */
class RegionGrowingFilter: public BinaryThresholdFilter
{
public:
  /* Default constructor. */
  RegionGrowingFilter();

  /* Constructor for a given  window and level. */
  RegionGrowingFilter( const Image::PixelType lower, const Image::PixelType upper );

  /* Destructor (does nothing). */
  virtual ~RegionGrowingFilter();

  /* Add coordinates of a seed point to the stack. */
  void AddSeedPoint( const unsigned int seedX, const unsigned int seedY );

  /* Clear all seed points. */
  void ClearSeedPoints();

  /* Execute the region growing filter. */
  virtual bool Execute();

protected:
  /* Add a point to the stack, if it is unchecked and inside the region. */
  void CheckAndAddPoint( const unsigned int x, const unsigned int y );

  /* A struct to represent the x and y coordinates of a point. */
  struct Point {
    unsigned int x; // X coordinate of the point.
    unsigned int y; // Y coordinate of the point.
  };

  /* A stack to hold the seed points. */
  std::stack<Point> m_SeedPoints;

  /* A stack to hold the border points of the current region. */
  std::stack<Point> m_BorderPoints;
};

#endif /* RegionGrowingFilter_h_ */

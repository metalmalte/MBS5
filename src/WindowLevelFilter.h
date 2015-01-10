/** \file WindowLevelFilter.h
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
#ifndef WindowLevelFilter_h_
#define WindowLevelFilter_h_

#include "ImageFilter.h"

/* A filter to perform the window-leveling operation on an image. */
class WindowLevelFilter: public ImageFilter
{
public:
  /* Default constructor */
  WindowLevelFilter();

  /* Constructor for a given  window and level. */
  WindowLevelFilter( const double window, const double level );

  /* Destructor */
  virtual ~WindowLevelFilter();

  /* Get the window. (inline function) */
  double GetWindow() { return m_Window; }

  /* Get the level. (inline function) */
  double GetLevel() { return m_Level; }

  /* Execute the window-level filter. */
  virtual bool Execute();

protected:
  double m_Window;
  double m_Level;
};

#endif /* WindowLevelFilter_h_ */

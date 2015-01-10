/** \file ImageIO.h
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
#ifndef ImageIO_h_
#define ImageIO_h_

#include <string>
#include "Image.h"

/* A class to read and write image files.
 *
 * Currently PGM and MetaImage formats are supported.
 * The specific format is automatically determined by
 * the ending of the file name.
 *
 * All methods of this if ImageIO are static, that means
 * no instance of the class is required. To read/write
 * an image use
 *
 *   ImageIO::Read( filename, image );
 *
 * or
 *
 *   ImageIO::Write( filename, image ); */
class ImageIO
{
public:
  /* Read an image with a given filename. */
  static bool Read( const char* filename, Image* image );

  /* Write an image with to a file. */
  static bool Write( const char* filename, const Image* image );

protected:
  /* Read a PRM image with a given filename. */
  static bool ReadPGMImage( const char* filename, Image* image );

  /* Read a meta image with a given filename. */
  static bool ReadMetaImage( const char* filename,Image* image );

  /* Write a PRM image with to a file. */
  static bool WritePGMImage( const char* filename, const Image* image );

  /* Write a meta image with to a file. */
  static bool WriteMetaImage( const char* filename, const Image* image );

  /* Check, if a filename is valid and has a given extension. */
  static bool CheckFilename( const char* filename, const char* extension );

private:
  /* Private constructor and destructor. */
  ImageIO();
  virtual ~ImageIO();

  static bool GetFilePath( const std::string fileName, std::string &path );
};

#endif /* ImageIO_h_ */

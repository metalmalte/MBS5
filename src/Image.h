/** \file Image.h
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
#ifndef Image_h_
#define Image_h_

#include <stdlib.h>

/* A class containing an image.
 *
 * Example:
 *   Image::PixelType grayValue;

 *   Image *im1 = new Image(); // create a zero-size image
 *
 *   ImageIO::Read( filename, im1 ); // load image 1
 *   im1->SetPixel(4,2,42); // set grayvalue 42 at pixel (4,2)
 *   grayValue = im->GetPixel(4,2); // get, grayValue is now 42
 *
 * To create a copy of an image use:
 *   Image *im2 = new Image();
 *   im2->CloneImage(im1); // create a copy of image 1
 * */
class Image
{
public:
  /* Defines the pixel type of the image.
   *
   * Using a typedef allows us to simply change the pixel type without changing
   * the code at multiple places.
   *
   * We use short values to encode medical image data with 2^12bit=4096 gray values
   * which are possible negative (e.g. in case of Hounsfield units).
   * (but in fact, we can encode 2^16bit) */
  typedef short PixelType;

  /* Constructor of an image. Creates an image of zero size without
   * allocating the image buffer.*/
  Image();

  /* Constructor of an image. Using this constructor an image of
   * the given size filled with zero-values is created. */
  Image( const unsigned int x, const unsigned int y);

  /* Destructor of an image. */
  virtual ~Image();

  /* Get the value of the pixel at coordinate (x, y). The coordinates will be
   * converted into an linearized index internally. */
  PixelType GetPixel( const unsigned int x, const unsigned int y ) const;

  /* Get the value of the pixel at index i. */
  PixelType GetPixel( const unsigned int i ) const;

  /* Set the value of the pixel at coordinate (x, y). The coordinates will be
   * converted into an linearized index internally.
   *
   * Returns success of the operation. */
  bool SetPixel( const unsigned int x, const unsigned int y, const PixelType value );

  /* Set the value of the pixel at index i.
   *
   * Returns success of the operation. */
  bool SetPixel( const unsigned int i, const PixelType value );

  /* Calculate a linearized index from the pixel coordinate (x, y). */
  unsigned int GetIndexFromCoordinate( const unsigned int x, const unsigned int y ) const;

  /* Set the spacing of the image. */
  void SetSpacing( const double sx, const double sy );

  /* Get the size of the image in x direction. */
  unsigned int GetSizeX() const { return m_SizeX; }

  /* Get the size of the image in y direction. */
  unsigned int GetSizeY() const { return m_SizeY; }

  /* Get the spacing of the image in x direction. */
  double GetSpacingX() const { return m_SpacingX; }

  /* Get the spacing of the image in y direction. */
  double GetSpacingY() const { return m_SpacingY; }

  /* Print information about the image to the screen. */
  void Print();

  /* Create this as an empty image of the given size */
  bool Allocate( const unsigned int x, const unsigned int y );

  /* Returns true, if image has a valid image buffer */
  bool IsAllocated() const { return( m_ImageBuffer != NULL ); }

  /* Makes this a copy of the other image, the image buffer is copied in  memory. */
  bool CloneImage( const Image* other );

private:
  /* Copy constructor is not implemented to avoid memory leaks */
  Image( const Image &other ); // Not implemented.
  /* Operator = (assignment) is not implemented to avoid memory leaks */
  void operator=( const Image &other ); // Not implemented.

  /* This method release the data of the image buffer (free memory) */
  void ReleaseData();

  // A pointer to the image buffer.
  PixelType* m_ImageBuffer;

  /* Size of the image in x direction. */
  unsigned int m_SizeX;
  /* Size of the image in y direction. */
  unsigned int m_SizeY;

  /* Pixel spacing of the image in x direction. */
  double m_SpacingX;
  /* Pixel spacing of the image in y direction. */
  double m_SpacingY;

};

#endif /* Image_h_ */

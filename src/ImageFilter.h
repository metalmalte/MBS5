/** \file ImageFilter.h
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
#ifndef ImageFilter_h_
#define ImageFilter_h_

#include "Image.h"

/* Defines an abstract base class for image filter operations.
 *
 * All filters can be used in the following way:
 *
 *   DerivedImageFilterType *filter = new DerivedImageFilterType();
 *
 *   filter->SetInputImage(myInputImage);
 *   if( ! filter->Execute())
 *   {
 *     // Error handling.
 *   }
 *   Image *myOutputImage = filter->GetOutputImage();
 *
 * You can check the validity of the output image by:
 *   if( ! myOutputImage )
 *   {
 *     // Error handling.
 *   }
 */
class ImageFilter
{
public:
  /* Constructor of an filter. */
  ImageFilter();
  /* virtual Destructor */
  virtual ~ImageFilter();

  /* Set the input image to filter.
   * You have to set an input image before calling Execute(). */
  virtual void SetInputImage( Image* inputImage );

  /* Execute the filter.
   * This method has to be implemented in each child class */
  virtual bool Execute() = 0;

  /* Get the filtered image.
   * You have to call this function after calling Execute(). */
  virtual Image* GetOutputImage();

protected:
  Image* m_InputImage;
  Image* m_OutputImage;

  /* Creates the output image with same size as the input image. Usually this
   * function is called from Execute(), before performing the filtering. */
  virtual bool CreateOutputImage();

  /* Returns true, if both images have the same size. */
  bool CheckImageDimensions( const Image* image1, const Image* image2 );
  /* Returns true, if both images have the same spacing. */
  bool CheckImageSpacing( const Image* image1, const Image* image2 );
};

#endif /* ImageFilter_h_ */

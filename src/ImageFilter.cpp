/** \file ImageFilter.cpp
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
#include <math.h>
#include <iostream>

#include "ImageFilter.h"

/* Constructor of an filter. */
ImageFilter::ImageFilter()
{
  // Set image pointer to null.
  m_InputImage = NULL;
  m_OutputImage = NULL;
}

ImageFilter::~ImageFilter()
{
  // Delete output image.
  if( m_OutputImage != NULL )
  {
    delete m_OutputImage;
  }
}

/* Set the input image to filter.
 * You have to set an input image before calling Execute(). */
void ImageFilter::SetInputImage( Image* inputImage )
{
  // set the input image
  m_InputImage = inputImage;
}

/* Get the filtered image.
 * You have to call this function after calling Execute(). */
Image* ImageFilter::GetOutputImage()
{
  // return the output image
  return m_OutputImage;
}

/* Creates the output image with same size as the input image. Usually this
 * function is called from Execute() before performing the filtering. */
bool ImageFilter::CreateOutputImage()
{
  // Check if a valid input image is set.
  if( m_InputImage == NULL )
  {
    std::cout << "Error: Cannot create output image! First set input image.";
    return false;
  }

  // Check, if output image is instantiated.
  if( m_OutputImage == NULL )
  {
    m_OutputImage = new Image();
  }

  // Avoid reallocation if output image is already created
  // and has the same size as the input image.
  if( ! (m_OutputImage->IsAllocated() && this->CheckImageDimensions( m_OutputImage, m_InputImage )) )
  {
    m_OutputImage->Allocate( m_InputImage->GetSizeX(), m_InputImage->GetSizeY() );
  }

  // Set image spacing.
  if( !this->CheckImageSpacing( m_OutputImage, m_InputImage ) )
  {
    m_OutputImage->SetSpacing( m_InputImage->GetSpacingX(), m_InputImage->GetSpacingY() );
  }

  return true;
}

/* Returns true, if both images have the same size. */
bool ImageFilter::CheckImageDimensions( const Image* image1, const Image* image2 )
{
  return (image1->GetSizeX() == image2->GetSizeX()
      && image1->GetSizeY() == image2->GetSizeY());
}

/* Returns true, if both images have the same spacing. */
bool ImageFilter::CheckImageSpacing( const Image* image1, const Image* image2 )
{
  // Spacing are float values -> define an epsilon to check if equal.
  const double epsilon = 0.000001;

  return (fabs( image1->GetSpacingX() - image2->GetSpacingX() ) < epsilon
      && fabs( image1->GetSpacingY() - image2->GetSpacingY() ) < epsilon);
}

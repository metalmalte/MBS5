/** \file ShiftScaleFilter.cpp
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
#include "ShiftScaleFilter.h"

/* Default constructor. */
ShiftScaleFilter::ShiftScaleFilter( const double shift, const double scale )
{
  m_Shift = shift;
  m_Scale = scale;
}

/* Destructor is empty. */
ShiftScaleFilter::~ShiftScaleFilter()
{
}

/* Execute the window-level filter. */
bool ShiftScaleFilter::Execute()
{
  // First, create a valid output image by calling CreateOutputImage()
  // of the base class ImageFilter.
  // The resulting output image has the same size and spacing as the input
  // image and is accessible by the member variable m_OutputImage.

  // This returns false, if no valid input image is available
  // or an other error occurs.
  if( !CreateOutputImage() )
    return false;

  //
  // Now, we compute transformed greyvalues S(g)=(g + shift) * scale
  // for each pixel value and set it in the output image m_OutputImage.
  for( unsigned int y = 0; y < m_InputImage->GetSizeY(); y++ )
  {
    for( unsigned int x = 0; x < m_InputImage->GetSizeX(); x++ )
    {
      // m_Shift and m_Scale are double values, therefore the output of this
      // computation is double. We have to convert the double value back to the
      // PixelType. This done with the C++ operator static_cast<T>, where T is
      // the type we wish to convert into.
      const Image::PixelType outValue =
          static_cast<Image::PixelType>( (m_InputImage->GetPixel( x, y ) + m_Shift) * m_Scale );

      // Access the output image by m_OutputImage and set the output pixel values.
      m_OutputImage->SetPixel( x, y, outValue );
    }
  }

  return true;
}

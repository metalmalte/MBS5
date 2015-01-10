/** \file ImageIO.cpp
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
#include "ImageIO.h"   // Include the header file.
#include <iostream>    // Include for printing text to the screen.
#include <fstream>     // Include for reading and writing files.
ImageIO::ImageIO()
{
}

ImageIO::~ImageIO()
{
}

//
// Read()
//
bool ImageIO::Read( const char* filename, Image* image )
{
  if( CheckFilename( filename, "pgm" ) )
  {
    return ReadPGMImage( filename, image );
  }
  else if( CheckFilename( filename, "mha" ) || CheckFilename( filename, "mhd" ) )
  {
    return ReadMetaImage( filename, image );
  }
  else
  {
    std::cout << "ERROR: file extension unknown!\n";
    return false;
  }
}

//
// Write()
//
bool ImageIO::Write( const char* filename, const Image* image )
{
  if( !image )
  {
    std::cout << "ERROR: can not save empty image !\n";
    return false;
  }

  if( CheckFilename( filename, ".pgm" ) )
  {
    return WritePGMImage( filename, image );
  }
  else if( CheckFilename( filename, ".mha" ) || CheckFilename( filename, ".mhd" ) )
  {
    return WriteMetaImage( filename, image );
  }
  else
  {
    std::cout << "ERROR: file extension unknown!\n";
    return false;
  }
}

//
// CheckFilename()
//
bool ImageIO::CheckFilename( const char* filename, const char* extension )
{
  // String for making a few checks.
  std::string fnString = filename;

  // Return error if file name is empty.
  if( fnString == "" )
  {
    std::cout << "Error: Filename is empty!" << std::endl;
    return false;
  }

  // Test if the last 3 characters are the extension.
  std::string::size_type position = fnString.rfind( extension );
  if( position == std::string::npos && position != fnString.length() - 4 )
  {
    return false;
  }

  return true;
}

//
// ReadPGMImage()
//
bool ImageIO::ReadPGMImage( const char* filename, Image* image )
{
  // Variables for image size and gray value range
  unsigned int width;
  unsigned int height;
  unsigned int maxValue;

  // Variable to read header Note: it does not Stores it
  char header[100] = { '\n' };
  char *ptr = NULL; // help variable

  // The input file stream
  std::ifstream source;

  // Open and Checks i.e Fail to open file
  source.open( filename, std::ios::in | std::ios::binary );

  // Check if the file exists
  if( !source.is_open() )
  {
    std::cout << "Can't read image: " << filename << std::endl;
    return false;
  }

  // Check if the file is a valid PGM file (magic number)
  source.getline( header, 100, '\n' );

  if( header[0] != 'P' && header[1] != '5' )
  {
    std::cout << "Error! Invalid PGM File";
    return false;
  }

  // Ignoring comments
  source.getline( header, 100, '\n' );
  while( header[0] == '#' )
  {
    source.getline( header, 100, '\n' );
  }

  // Extracting image size
  width = strtol( header, &ptr, 0 );
  height = atoi( ptr );

  // Reading Gray value range
  source.getline( header, 100, '\n' );
  maxValue = strtol( header, &ptr, 0 );

  // Create image of given size
  if( !image->Allocate( width, height ) )
  {
    std::cout << "Error: can not create image of size [" << width << "x" << height << "] !\n";
    return false;
  }

  // Reading grayvalues in file
  for( unsigned int y = 0; y < height; y++ )
  {
    for( unsigned int x = 0; x < width; x++ )
    {
      Image::PixelType pixelValue;

      // check if 8 or 16 bit values are used
      if( maxValue > 255 )
      {
        unsigned char value16Bit[2];
        source.read( (char*) &value16Bit[0], 2 * sizeof(char) );

        pixelValue = static_cast<Image::PixelType> ( (value16Bit[0] & 255) << 8 ) + static_cast<Image::PixelType> ( value16Bit[1] & 255 );
      }
      else
      {
        unsigned char value8Bit;
        source.read( (char*) &value8Bit, sizeof(char) );

        pixelValue = static_cast<Image::PixelType> ( value8Bit );
      }

      image->SetPixel( x, y, pixelValue );
    }
  }

  return true;
}

// A MetaImage consists of a header file (-mha or .mhd) and a RAW file (.raw).
//
// The minimal structure of the MetaImage header is the following:
//
// ObjectType = Image
// NDims = 2
// DimSize = 181 217
// ElementType = MET_UCHAR
// ElementSpacing = 1.0 1.0
// ElementByteOrderMSB = False
// ElementDataFile = image.raw
//
// * ObjectType indicates that the file contains an image.
// * NDims indicate that this is a 2D image.
// * DimSize indicates the size of the volume in pixels along each
//   direction.
// * ElementType indicate the primitive type used for pixels. In this case
//   is "unsigned char", implying that the data is digitized in 8 bits /
//   pixel.
// * ElementSpacing indicates the physical separation between the center of
//   one pixel and the center of the next pixel along each direction in space.
//   The units used are millimeters.
// * ElementByteOrderMSB indicates is the data is encoded in little or big
//   endian order.
// * ElementDataFile is the name of the file containing the raw binary data
//   of the image. This file must be in the same directory as the header.
bool ImageIO::ReadMetaImage( const char* filename, Image* image )
{
  // Image parameters to read from header.
  enum PixelType
  {
    CHAR, UCHAR, SHORT, USHORT
  };

  PixelType pixelType = CHAR;
  bool byteOrderMSB = true;
  unsigned int width = 0;
  unsigned int height = 0;
  double sx = 1.0;
  double sy = 1.0;
  std::string rawFilename = "";

  //
  // Read header file
  //

  // The file stream.
  std::ifstream headerFileStream( filename, std::ios::in );

  // A string to store each text line in.
  std::string textline = "";

  while( getline( headerFileStream, textline ) )
  {
    if( textline.find( "ObjectType" ) == 0 )
    {
      if( textline.find( "Image" ) == std::string::npos )
      {
        std::cout << "Error: File does not contain an image!" << std::endl;
        return false;
      }
    }
    else if( textline.find( "NDims" ) == 0 )
    {
      std::string::size_type equalPos = textline.find( "=" );

      std::string::size_type startPos = textline.find_first_not_of( " ", equalPos + 1 );
      std::string::size_type endPos = textline.find( " ", startPos + 1 );

      int dimension = atoi( textline.substr( startPos, endPos ).c_str() );

      if( dimension != 2 )
      {
        std::cout << "Error: Only images of dimension 2 are supported!" << std::endl;
        return false;
      }
    }
    else if( textline.find( "DimSize" ) == 0 )
    {
      std::string::size_type equalPos = textline.find( "=" );

      std::string::size_type startPos = textline.find_first_not_of( " ", equalPos + 1 );
      std::string::size_type endPos = textline.find( " ", startPos + 1 );
      width = atoi( textline.substr( startPos, endPos ).c_str() );

      startPos = textline.find_first_not_of( " ", endPos + 1 );
      endPos = textline.find( " ", startPos + 1 );
      height = atoi( textline.substr( startPos, endPos ).c_str() );
    }
    else if( textline.find( "ElementType" ) == 0 )
    {
      if( textline.find( "MET_CHAR" ) != std::string::npos )
      {
        pixelType = CHAR;
      }
      else if( textline.find( "MET_UCHAR" ) != std::string::npos )
      {
        pixelType = UCHAR;
      }
      else if( textline.find( "MET_SHORT" ) != std::string::npos )
      {
        pixelType = SHORT;
      }
      else if( textline.find( "MET_USHORT" ) != std::string::npos )
      {
        pixelType = USHORT;
      }
      else
      {
        std::cout << textline << "Error: Only images of type char, unsigned char, short and unsigned short are supported!" << std::endl;
        return false;
      }
    }
    else if( textline.find( "ElementSpacing" ) == 0 || textline.find( "ElementSize" ) == 0 )
    {
      std::string::size_type equalPos = textline.find( "=" );

      std::string::size_type startPos = textline.find_first_not_of( " ", equalPos + 1 );
      std::string::size_type endPos = textline.find( " ", startPos + 1 );
      sx = atof( textline.substr( startPos, endPos ).c_str() );

      startPos = textline.find_first_not_of( " ", endPos + 1 );
      endPos = textline.find( " ", startPos + 1 );
      sy = atof( textline.substr( startPos, endPos ).c_str() );
    }
    else if( textline.find( "ElementByteOrderMSB" ) == 0 )
    {
      if( textline.find( "True" ) != std::string::npos )
      {
        byteOrderMSB = true;
      }
      else if( textline.find( "False" ) != std::string::npos )
      {
        byteOrderMSB = false;
      }
      else
      {
        std::cout << textline << "Error: ElementByteOrderMSB must be 'True' or 'False'!" << std::endl;
        return false;
      }
    }
    else if( textline.find( "ElementDataFile" ) == 0 )
    {
      std::string::size_type equalPos = textline.find( "=" );
      std::string::size_type startPos = textline.find_first_not_of( " ", equalPos + 1 );
      rawFilename = textline.substr( startPos, textline.size() ).c_str();
    }
  }

  headerFileStream.close();

  // Create image with the given parameters.
  if( !image->Allocate( width, height ) )
  {
    std::cout << "Error: can not create image of size [" << width << "x" << height << "] !\n";
    return false;
  }
  image->SetSpacing( sx, sy );

  //
  // Read RAW file
  //
  // get path of the header file
  std::string pathName;
  if( GetFilePath( std::string( filename ), pathName ) )
  {
    rawFilename = pathName + rawFilename;
  }

  std::ifstream rawFileStream( rawFilename.c_str(), std::ios::in | std::ios::binary );
  if( !rawFileStream )
  {
    std::cout << "Error: Can not read raw file: " << rawFilename << std::endl;
    return false;
  }

  // Read grayvalues from RAW file.
  for( unsigned int y = 0; y < height; y++ )
  {
    for( unsigned int x = 0; x < width; x++ )
    {
      Image::PixelType pixelValue;

      // check if 8 or 16 bit values are used
      if( pixelType == SHORT || pixelType == USHORT )
      {
        unsigned char value16Bit[2];
        rawFileStream.read( (char*) &value16Bit[0], 2 * sizeof(char) );

        if( byteOrderMSB )
        {
          pixelValue = static_cast<Image::PixelType> ( (value16Bit[0] & 255) << 8 ) + static_cast<Image::PixelType> ( value16Bit[1] & 255 );
        }
        else
        {
          pixelValue = static_cast<Image::PixelType> ( (value16Bit[1] & 255) << 8 ) + static_cast<Image::PixelType> ( value16Bit[0] & 255 );
        }
      }
      else
      {
        unsigned char value8Bit;
        rawFileStream.read( (char*) &value8Bit, sizeof(char) );

        pixelValue = static_cast<Image::PixelType> ( value8Bit );
      }

      image->SetPixel( x, y, pixelValue );
    }
  }

  rawFileStream.close();

  // return the image
  return image;
}

//
// WritePGMImage()
//
bool ImageIO::WritePGMImage( const char* filename, const Image* image )
{
  std::ofstream destination;

  destination.open( filename, std::ios::binary | std::ios::out );
  if( !destination )
  {
    std::cout << "ERROR: can not open file " << filename << "!\n";
    return false;
  }

  // compute minimum, maximum image value
  Image::PixelType minValue = image->GetPixel( 0, 0 );
  Image::PixelType maxValue = image->GetPixel( 0, 0 );
  const unsigned int size = image->GetSizeX() * image->GetSizeY();

  for( unsigned int index = 0; index < size; index++ )
  {
    const Image::PixelType value = image->GetPixel( index );

    if( value < minValue )
      minValue = value;
    if( value > maxValue )
      maxValue = value;
  }

  if( minValue < 0 )
  {
    std::cout << "Warning: Negative gray values are not supported in PGM format and will be set to 0!\n";
  }

  // maxvalue of 0 not supported by most readers
  if(maxValue == 0) maxValue=1;

  // writes header into the Destination
  destination << "P5" << std::endl;
  destination << "# Created By IMI Luebeck" << std::endl;
  destination << image->GetSizeX() << " " << image->GetSizeY() << std::endl;
  destination << (int)maxValue << std::endl;

  for( unsigned int index = 0; index < size; index++ )
  {
    Image::PixelType value = image->GetPixel( index );

    if( value < 0 ) value = 0;

    // check for 8bit or 16bit storage
    if( maxValue > 255 )
    {
      char buffer[2];
      buffer[0] = static_cast<char> ( (value >> 8) & 255 );
      buffer[1] = static_cast<char> ( value & 255 );
      destination.write( buffer, 2 * sizeof(char) );
    }
    else
    {
      char buffer;
      buffer = static_cast<char> ( value );
      destination.write( &buffer, sizeof(char) );
    }
  }

  destination.close();

  return true;
}

//
// WriteMetaImage()
//
bool ImageIO::WriteMetaImage( const char* filename, const Image* image )
{
  // Byte order to write file (true = Big Endian, false = Little Endian).
  bool byteOrderMSB = false;

  // Get string filename.
  std::string fileNameString = filename;

  // Get full filename of the raw file (required to open file stream).
  std::string rawFileNameString = fileNameString.substr( 0, fileNameString.length() - 3 ).append( "raw" );

  // Get base filename of the raw file (required to write in the header file).
  std::string::size_type baseStartPos = rawFileNameString.find_last_of( "/" ) + 1;
  std::string rawFileNameBase = rawFileNameString.substr( baseStartPos, rawFileNameString.length() - baseStartPos );

  //
  // Write header file
  //
  // Open header file for writing.
  std::ofstream headerFileStream;
  headerFileStream.open( filename, std::ios::out );

  // Write data in header file.
  if( headerFileStream.is_open() )
  {
    headerFileStream << "ObjectType = Image" << std::endl;
    headerFileStream << "NDims = 2" << std::endl;
    headerFileStream << "DimSize = " << image->GetSizeX() << " " << image->GetSizeY() << std::endl;
    headerFileStream << "ElementType = MET_SHORT" << std::endl;
    headerFileStream << "ElementSpacing = " << image->GetSpacingX() << " " << image->GetSpacingY() << std::endl;
    if( byteOrderMSB )
    {
      headerFileStream << "ElementByteOrderMSB = True" << std::endl;
    }
    else
    {
      headerFileStream << "ElementByteOrderMSB = False" << std::endl;
    }
    headerFileStream << "ElementDataFile = " << rawFileNameBase << std::endl;
  }
  else
  {
    std::cout << "Error: Failed to open output header!" << std::endl;
    return false;
  }

  // Close header file.
  headerFileStream.close();

  //
  // Write RAW file
  //
  std::ofstream rawFileStream( rawFileNameString.c_str(), std::ios::binary | std::ios::out );
  if( !rawFileStream )
  {
    std::cout << "ERROR: can not open file " << filename << "!\n";
    return false;
  }

  for( unsigned int y = 0; y < image->GetSizeY(); y++ )
  {
    for( unsigned int x = 0; x < image->GetSizeX(); x++ )
    {
      Image::PixelType pixelValue = image->GetPixel( x, y );

      char buffer[2];

      if( byteOrderMSB )
      {
        buffer[0] = static_cast<char> ( (pixelValue >> 8) & 255 );
        buffer[1] = static_cast<char> ( pixelValue & 255 );
      }
      else
      {
        buffer[1] = static_cast<char> ( (pixelValue >> 8) & 255 );
        buffer[0] = static_cast<char> ( pixelValue & 255 );
      }
      rawFileStream.write( buffer, 2 * sizeof(char) );
    }
  }

  rawFileStream.close();

  return true;
}

//
// GetFilePath()
//
bool ImageIO::GetFilePath( const std::string fileName, std::string &path )
{
  size_t found;
  found = fileName.find_last_of( "\\/" );
  if( found != std::string::npos )
  {
    path = fileName.substr( 0, found + 1 );
  }
  else
  {
    path = "";
    return false;
  }
  return true;
}

/** \file MIPVentricleSegmentation.cpp
 *
 * Module:    CS3310
 *            Medizinische Bild- und Signalverarbeitung
 *            Medizinische Bildverarbeitung
 *
 * Authors:   Jan Ehrhardt, Alexander Schmidt-Richberg
 *
 * Student:   Malte Fentross, David Conrad
 *
 * Matr.-No.: 614409, 607115
 *
 * Copyright (c) 2010 Institute of Medical Informatics,
 *            University of Luebeck
 ********************************************************/
#include <iostream>

// All implemented filters are included here for your convenience

// include basis image classes
#include "Image.h"
#include "ImageIO.h"

// Include histogram and greyvalue transformations
#include "ImageHistogram.h"
#include "ShiftScaleFilter.h"
#include "ContrastStretchingFilter.h"
#include "WindowLevelFilter.h"
// Include the linear filters
#include "MeanKernel.h"
#include "LaplaceKernel.h"
#include "BinomialKernel.h"
#include "GaussianKernel.h"
#include "UnsharpMaskKernel.h"
#include "ConvolutionFilter.h"
// Include the non-linear filters
#include "SobelFilter.h"
// Include the segmentation filters
#include "BinaryThresholdFilter.h"
#include "RegionGrowingFilter.h"
// Include the morphological operations
#include "ErosionFilter.h"
#include "DilationFilter.h"
#include "ClosingFilter.h"
#include "OpeningFilter.h"
#include "BallStructureElement.h"

using namespace std;

int main( int argc, char *argv[] )
{
  std::cout << "==========================" << std::endl;
  std::cout << " MIPVentricleSegmentation   " << std::endl;
  std::cout << "==========================" << std::endl;

  // Check if program is called correctly.
  if( argc != 3 )
  {
    std::cout << "MIPVentricleSegmentation: Called incorrectly!" << std::endl;
    std::cout << "MIPVentricleSegmentation: MIPVentricleSegmentation inimage.mha outimage.mha" << std::endl;
    return -1;
  }

  // Declare an image.
  Image* image = new Image();

  // Read image using ImageIO.
  std::cout << "Reading image " << argv[1] << "..." << std::endl;
  if( !ImageIO::Read( argv[1], image ) )
  {
    std::cout << "Error: Reading image failed!" << std::endl;
    return -1;
  }

  /* TODO Aufgabe 4a: Konzeption einer BV-Pipeline zur Segmentierung der Hirnventrikel (6 Pkt)
   * Ueberlegen Sie sich eine sinnvolle Pipeline für die Segmentierung der Ventrikel
   * und implementieren sie diese hier. Filter können einfach verkettet werden,
   * indem man die Ausgabe des einen Filters als Eingabe an den nächsten Filter
   * Übergibt:
   *
   *   FilterClassA* fitlerA = new FilterClassA();
   *   filterA->SetInputImage( image );
   *   // Set parameter for filterA...
   *   filterA->Execute();
   *   FilterClassB* fitlerB = new FilterClassB();
   *   filterB->SetInputImage( filterA->GetOutputImage() );
   *   // Set parameter for filterB...
   *   filterB->Execute();
   *   ...
   *
   * Denken Sie unbedingt daran, sämtliche verwendete Filter im Kopf der Datei
   * einzubinden, z.B.: (ist hier schon geschehen)
   *
   *   #include "SobelFilter.h"
   *
   */


  //
  // Pre-processing.
  //
  // Unsharp masking to increase contrast
    ConvolutionFilter *convFilter = new ConvolutionFilter();
    convFilter->SetKernel(new UnsharpMaskKernel(3, 3));
    convFilter->SetInputImage(image);
    convFilter->Execute();

    // Use threshold filter for creating binary for erosion filter
   unsigned int lowerBound = 0;
   unsigned int upperBound = 65;
   BinaryThresholdFilter *thresholdFilter = new BinaryThresholdFilter(lowerBound, upperBound);
   thresholdFilter->SetInputImage(convFilter->GetOutputImage());
   thresholdFilter->Execute();
  // ImageIO::Write("/home/conradd/Downloads/MIPExercise5/images/test_tresh.pgm", thresholdFilter->GetOutputImage());

   // Use erosion filter to find seed points
   ErosionFilter *erosionFilter = new ErosionFilter();
   erosionFilter->SetStructureElement(new BallStructureElement(5));
   erosionFilter->SetInputImage(thresholdFilter->GetOutputImage());
   erosionFilter->Execute();

   // Get erosion image
   Image *erosionImage = erosionFilter->GetOutputImage();
   //ImageIO::Write("/Users/dc/Documents/Workspace/MIPExercise5/images/test_eros.pgm", erosionImage);


   // Allocate seed points
   // Initially lower right corner
   unsigned int leftSeedX = image->GetSizeX()-1;
   unsigned int leftSeedY = image->GetSizeY()-1;

   // Initially upper left corner
   unsigned int rightSeedX = 0;
   unsigned int rightSeedY = 0;

   // Find furtherest left and right seeds next to center of image
   // 1/10 of the picture arounf the center
   BallStructureElement *centerBall = new BallStructureElement(image->GetSizeX()/10);

   for(unsigned int m = (image->GetSizeX()/2)-centerBall->GetHalfSizeX();m < ((image->GetSizeX()/2)+centerBall->GetHalfSizeX()); m++)
   {
     for(unsigned int n = (image->GetSizeY()/2)-centerBall->GetHalfSizeY();n < ((image->GetSizeY()/2)+centerBall->GetHalfSizeY()); n++)
     {
       Image::PixelType pixel = erosionImage->GetPixel(m,n);

       // Update seed positions
       if(pixel==0){

         // Left seed
         if(m<leftSeedX)
         {
           leftSeedX=m;
           leftSeedY=n;
         }

         // Right seed
         if(m>rightSeedX)
         {
           rightSeedX=m;
           rightSeedY=n;
         }
       }
     }
   }

   //std::cout << "Left seed: " << leftSeedX << ", " << leftSeedY << std::endl;
   //std::cout << "Right seed: " << rightSeedX << ", " << rightSeedY << std::endl;

   // Debug Info for Seeds
//   Image *seedImage = new Image(image->GetSizeX(),image->GetSizeY());
//   seedImage->SetPixel(leftSeedX, leftSeedY, 255);
//   seedImage->SetPixel(rightSeedX, rightSeedY, 255);

  //ImageIO::Write("/Users/dc/Documents/Workspace/MIPExercise5/images/test_seed.pgm", seedImage);

  // Segmentation.

     // Region growing
     RegionGrowingFilter * rGF = new RegionGrowingFilter(lowerBound, upperBound);
     //Add seed points
     rGF->AddSeedPoint(leftSeedX, leftSeedY);
     rGF->AddSeedPoint(rightSeedX, rightSeedY);
     rGF->SetInputImage(image);
     rGF->Execute();

//       ImageIO::Write("/home/conradd/Downloads/MIPExercise5/images/test_Region.pgm", rGF->GetOutputImage());


  //
  // Post-processing.
  //

       //Opening
       OpeningFilter *oF = new OpeningFilter();
       oF->SetStructureElement(new BallStructureElement(2));
       oF->SetInputImage(rGF->GetOutputImage());
       oF->Execute();

       //Closing
//       ClosingFilter *cF = new ClosingFilter();
//       cF->SetStructureElement(new BallStructureElement(1));
//       cF->SetInputImage(rGF->GetOutputImage());
//       cF->Execute();


  // Get final segmentation as output image from the pipeline.
  Image* finalSegmentation = oF->GetOutputImage(); // = lastFilter->GetOutputImage();


  // Calculate ventricle volume (area).
  /* TODO Aufgabe 4b: Berechnung des Volumens der Ventrikel (1 Pkt)
   * Benutzen Sie ihre erstellte Segmentierung, um das Volumen der Ventrikel zu
   * berechnen (In 2D-Bilddaten kann natürlich nicht von einem Volumen
   * gesprochen werden! Da die verwendeten Methoden aber in Volumendaten ebenso
   * funktionieren, ignorieren wir dieses kleine Detail einmal...).
   *
   * Hinweise: Um das Volumen richtig berechnen zu können, müssen auf jeden Fall
   * die Dateien im Meta-Format eingelesen werden. Überlegen Sie warum und
   * berücksichtigen Sie dies in der Implementierung! Zum Schreiben des
   * Segmentierungsergebnisses können Sie jedoch auch das PGM-Format nutzen,
   * da die Ergebnisse so meist komfortabler Überprüft werden können. */




  double ventricleArea = 0.0;
  std::cout << "Ventricle area: " << ventricleArea << " mm^2" << std::endl;

  // Write image using ImageIO.
  std::cout << "Writing image " << argv[2] << std::endl;
  if( !ImageIO::Write( argv[2], finalSegmentation ) )
  {
    std::cout << "Error: Writing image failed!" << std::endl;
    return -1;
  }

  // TODO Delete all allocated filters and images.
  delete image;

  std::cout << "==========================" << std::endl;
  return 0;
}

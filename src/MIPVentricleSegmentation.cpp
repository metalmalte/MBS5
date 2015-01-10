/** \file MIPVentricleSegmentation.cpp
 *
 * Module:    CS3310
 *            Medizinische Bild- und Signalverarbeitung
 *            Medizinische Bildverarbeitung
 *
 * Authors:   Jan Ehrhardt, Alexander Schmidt-Richberg
 *
 * Student:   TODO Fill in your name(s) here
 *
 * Matr.-No.: TODO Fill in your matriculation number(s) here
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
   * übergibt:
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
  /* TODO Überlegen Sie sich eine geeignete Vorverarbeitung der Bilddaten. */


  //
  // Segmentation.
  //
  /* TODO wenden Sie ein geeignetes Segmentierungs-Verfahren an. Überlegen Sie
   * sich bei Verwendung des Region-Growing-Verfahrens weiterhin, wie Sie
   * automatisch geeigente Parameter wie z.B. Saatpunkte detektieren können. */


  //
  // Post-processing.
  //
  /* TODO Überlegen Sie sich eine geeignete Nachbearbeitung der Segmentierungen. */


  // Get final segmentation as output image from the pipeline.
  Image* finalSegmentation = new Image(1,1); // = lastFilter->GetOutputImage();


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
   * da die Ergebnisse so meist komfortabler überprüft werden können. */

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

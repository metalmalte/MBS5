/** \file MIPSegmentationEvaluation.cpp
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

#include "Image.h"
#include "ImageIO.h"

using namespace std;

int main( int argc, char *argv[] )
{
  std::cout << "===========================" << std::endl;
  std::cout << " MIPSegmentationEvaluation " << std::endl;
  std::cout << "===========================" << std::endl;

  // Check if program is called correctly.
  if( argc != 3 )
  {
    std::cout << "MIPSegmentationEvaluation: Called incorrectly!" << std::endl;
    std::cout << "MIPSegmentationEvaluation: MIPSegmentationEvaluation segmentation.pgm reference.pgm" << std::endl;
    return -1;
  }

  // Declare an image.
  Image* segmentation = new Image();
  Image* reference = new Image();

  // Read segmentations using ImageIO.
  std::cout << "Reading automatic segmentation " << argv[1] << "..." << std::endl;
  if( !ImageIO::Read( argv[1], segmentation ) )
  {
    std::cout << "Error: Reading automatic segmentation failed!" << std::endl;
    return -1;
  }

  std::cout << "Reading reference segmentation " << argv[2] << "..." << std::endl;
  if( !ImageIO::Read( argv[2], reference ) )
  {
    std::cout << "Error: Reading automatic reference failed!" << std::endl;
    return -1;
  }

  // Check segmentations for same size.
  if( segmentation->GetSizeX() != reference->GetSizeX() ||
      segmentation->GetSizeY() != reference->GetSizeY() )
  {
    std::cout << "Error: Segmentations are not of the same size!" << std::endl;
    return -1;
  }


  /* TODO Aufgabe 3: Berechnung des Jaccard-Koeffizienten.
   *
   * Um zu evaluieren, wie gut das entwickelte Verfahren zur Segmentierung
   * funktioniert, wird die erstellte Segmentierung mit einer Referenz-
   * segmentierung verglichen, dem sogenannten Goldstandard. Ein oft
   * herangezogenes Maß zur Quantifizierung der Ähnlichkeit zwischen erstellter
   * und Referenzsegmentierung ist der Jaccard-Koeffizient:
   *
   *   J(R,S) := |R \cap S| / |R \cup S|
   *
   * wobei R und S die Mengen der Pixel von automatischer bzw. Referenzsegmentierung
   * bezeichnen. Ein Wert von 1 (d.h. Schnittmenge und Vereinigung sind gleich)
   * bedeutet eine perfekte Übereinstimmung, während J = 0 disjunkte Mengen
   * impliziert. */

  double jaccard = 0.0;


  unsigned int sizeUnion = 0;
  unsigned int sizeIntersection = 0;

  unsigned int imageLength = segmentation->GetSizeY() * segmentation->GetSizeX();

  for (int i = 0; i < imageLength; i++) {
    Image::PixelType s_pixel = segmentation->GetPixel(i);
    Image::PixelType r_pixel = reference->GetPixel(i);

    if(s_pixel == r_pixel && s_pixel == 255) {
      sizeIntersection++;
    }

    if(s_pixel != r_pixel) {
      sizeUnion++;
    }

  }


  // add intersection here -> less cpu expensive
  sizeUnion += sizeIntersection;

  jaccard = (double) sizeIntersection / (double) sizeUnion;

  std::cout << "Jaccard coefficient: " << jaccard << std::endl;


  // Delete images.
  delete segmentation;
  delete reference;

  std::cout << "===========================" << std::endl;
  return 0;
}

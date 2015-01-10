/** \file BinomialKernel.cpp
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
#include "BinomialKernel.h"

/* Constructor creates an 3x3 binomial kernel */
BinomialKernel::BinomialKernel() :
    ConvolutionKernel( 1, 1 )
{
  /*
   * Set the coefficients of the binomial filter:
   *
   *      | 1  2  1 |
   * 1/16 | 2  4  2 |
   *      | 1  2  1 |
   *
   * Benutzen Sie die Methode SetCoefficient(i,j, value); um die Werte der
   * Maske zu setzen. Beachten Sie die Kommentare in der Klasse ConvolutionKernel.
   *
   * Hinweis: Achten Sie auf den korrekten Datentyp für die Koeffizienten der Maske.
   *          Die Variable a hat den Wert 0 nach folgendem Code:
   *          double a = 1/5;  // korrekt ist: double a = 1.0/5.0;
   * Hinweis: Betrachten Sie die Implementierung der Klasse LaplaceKernel.
   */

  // Set coefficients
  SetCoefficient( -1, -1, 1.0 / 16 );
  SetCoefficient( 0, -1, 2.0 / 16 );
  SetCoefficient( 1, -1, 1.0 / 16 );
  SetCoefficient( -1, 0, 2.0 / 16 );
  SetCoefficient( 0, 0, 4.0 / 16 );
  SetCoefficient( 1, 0, 2.0 / 16 );
  SetCoefficient( -1, 1, 1.0 / 16 );
  SetCoefficient( 0, 1, 2.0 / 16 );
  SetCoefficient( 1, 1, 1.0 / 16 );
}

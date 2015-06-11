// Solar Power Atmospheric Effects Routines
//
// Routines for computing air density and atmospheric path loss.
// 
/***************************************************************************
 *   Copyright (C) 2007 by Ken Sarkies                                     *
 *   ksarkies@trinity.asn.au                                               *
 *                                                                         *
 *   This file is part of SolarPower.                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   The program is distributed in the hope that it will be useful,        *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You may obtain a copy of the GNU General Public License by writing to *
 *   the Free Software Foundation, Inc.,                                   *
 *   51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA.             *
 ***************************************************************************/

#ifndef SPATMOSPHERICS_H_
#define SPATMOSPHERICS_H_

//---------------------------------------------------------------------------
// Compute the density of air from a suitable model
//
// Input: height above sea level in metres
// Output: Modelled air density in kg/metre^3

double airDensity(const double height);
//----------------------------------------------------------------------------
// Numerical integration of density over a sloping path.
//
// The angle of the path to the vertical is phi. To integrate density rho(h)
// as a function of height, over the path, we compute the slope of the
// path with respect to the height from ground level to get:
//
//      integral from 0 to infinity rho(h) (da/dh) dh
//
// Input: angle of path to vertical phi in degrees
// Output: path loss integral

double pathLoss(const double phi);
//----------------------------------------------------------------------------
// Global constants
//----------------------------------------------------------------------------
// Return the amount of solar power W/m^2 incident on the Earth's upper
// atmosphere.

double getSolarConstant();
//----------------------------------------------------------------------------
// A constant used to determine the rate of loss of solar power through the
// atmosphere.

double getLossConstant();

#endif /*SPATMOSPHERICS_H_*/

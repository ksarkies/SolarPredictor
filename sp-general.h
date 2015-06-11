//          Solar energy predictor
//
/***************************************************************************
 *   Copyright (C) 2007 by Ken Sarkies                                     *
 *   ksarkies@trinity.asn.au                                               *
 *                                                                         *
 *   This file is part of SolarPower.                                      *
 *                                                                         *
 *   SolarPower is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   SolarPower is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with SolarPower if not, write to the                            *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA.             *
 ***************************************************************************/

#ifndef SOLARPOWER_H_
#define SOLARPOWER_H_

//----------------------------------------------------------------------------
// Length of day in hours for given latitude and solar declination
//
double dayLength(const double latitude, const double declination);
//----------------------------------------------------------------------------
// Declination of the Sun for a given day of Year
// Input: Day of year counting from 0 at January 1
// Output: Declination in degrees
//
double sunDeclination(const double dayYear);
//----------------------------------------------------------------------------
// Standard incident solar power W/m^2 used to specify solar modules. This
// represents the nominal power incident on the Earth's surface after traversing
// the atmosphere when the Sun is vertically overhead.

double getSolarStandard();

#endif /*SOLARPOWER_H_*/

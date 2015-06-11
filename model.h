// A range of model parameters.
//
// These will be integrated into a configuration file in due course.
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

#ifndef MODEL_H_
#define MODEL_H_
#include "sp-module-model.h"

// Model and Site specific constants
    const double maxDeclination = 23.45;        // Northern tropic
    const double latitude = -34.929;            // Adelaide
//    const double latitude = maxDeclination;     // Sun overhead
    const double declination = maxDeclination;  // Worst case Winter
    const double batteryVoltage = 12;
// Only used in full power (upper bound) model
    const double modulePower = 125;
// Cloud cover model
    const double oktaFactor[12] = {0.61,0.62,0.58,0.52,0.43,0.40,0.42,0.45,0.45,0.48,0.50,0.53};
    const int daysPerMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

#endif /*MODEL_H_*/

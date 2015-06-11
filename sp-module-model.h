// Models for the PV Module

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

#ifndef SPMODULEMODEL_H_
#define SPMODULEMODEL_H_

//----------------------------------------------------------------------------
// Model for solar module BP3125
// This model, fitted to parameters from the datasheet, provides a current
// output for a give module voltage (usually constrained by the battery voltage
// and the solarEnergy impinging on it. The parameters are relevant to a
// reference solar energy of 100 units to 1000W/m^2

double moduleCurrent(const double solarEnergy, const double voltage);
//----------------------------------------------------------------------------
// Model for solar module BP3125 with a maximum power point tracker.
//
// solarEnergy is the percentage standard incident solar radiation used to
// define the module characteristics (ie 1000 W/m2).
//
// This uses a simple hill-climbing search for maximum power starting at the
// open-circuit voltage and stepping back to the peak.

double OptimalModulePower(const double solarEnergy);

//----------------------------------------------------------------------------
// Standard incident solar power W/m^2 used to specify solar modules. This
// represents the nominal power incident on the Earth's surface after traversing
// the atmosphere when the Sun is vertically overhead.

double getSolarStandard();

#endif /*SPMODULEMODEL_H_*/

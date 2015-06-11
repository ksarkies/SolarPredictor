// Solar Power Computational Routines
//
// A variety of routines producing high level results.
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

#ifndef SPCOMPUTATIONS_H_
#define SPCOMPUTATIONS_H_

//----------------------------------------------------------------------------
// Computation of annual return for a module system costg an MPP tracking
// regulator, with offset and feed-in tarrifs provided for usage offset and
// excess.
// Input: Latitude in degrees, positive north of equator
//        Angle of the module to the vertical in degrees
//        Angle offset of module from North towards East in degrees
//        Value of offset of usage power $/kWH
//        Value of feedin tariff $/kWH
//        Average power usage in kW during the daylight hours
//
// The model includes cloud cover estimates from the BOM.

double computeAnnualReturnFixedMPP(const double latitude,
                        const double moduleAngle,
                        const double moduleOffset,
                        const double cost,
                        const double feedIn,
                        const double usage);

//----------------------------------------------------------------------------
// Computation of daily financial return.
// The regulator will use Maximum power Point tracking with high efficiency.
// The module is fixed at a preset angle to the sun.
// Integration is done by a simple sum over small elements.
// Input: Latitude in degrees, positive north of equator
//        Declination of the sun in degrees
//        Angle of the module to the vertical in degrees
//        Angle offset of module from North towards East in degrees
//        Cost of offset of usage power $/kWH
//        Cost of feedin tariff $/kWH
//        Average power usage in kW during the daylight hours
// Output: Monetary return
// Dependencies: pathLoss(cosangle) integral of air density over a slant path

double computeDailyFixedMPPReturn(const double latitude,
                           const double declination,
                           const double moduleAngle,
                           const double moduleOffset,
                           const double cost,
                           const double feedIn,
                           const double usage);
//----------------------------------------------------------------------------
// Computation of daily charge for a Sun following module.
// Varieties of models:
// 1. module delivering full power to the battery.
// 2. module output voltage held to battery voltage.
// 3. module following Maximum power Point.
// Represents a module following the sun during the day.
// Integration is done by a simple sum over small elements given in minute
// increments and over half a day. The result is converted to WH by dividing
// by 60 and multiplying by 2 for the second half of the day.
// Input: Latitude in degrees, positive north of equator
//        Declination of the sun in degrees
// Output: Total charge delivered to the battery over the day in AH.
// Dependencies: pathLoss(cosangle) integral of air density over a slant path

double solarFollowingCharge(const double latitude,
                            const double declination,
                            const int model);
//----------------------------------------------------------------------------
// Computation of daily charge for a fixed module.
// Varieties of models:
// 1. module delivering full power to the battery.
// 2. module output voltage held to battery voltage.
// 3. module following Maximum power Point.
// Integration is done by a simple sum over small elements.
// Represents a fixed module facing the sun at noon.
// Input: Latitude in degrees, positive north of equator
//        Declination of the sun in degrees
//        Angle of the module to the vertical in degrees
//        Angle offset of module from North towards East in degrees
// Output: Total energy per square metre over a day arriving at earth's surface
// Dependencies: pathLoss(cosangle) integral of air density over a slant path
double solarFixedCharge(const double latitude,
                        const double declination,
                        const double moduleAngle,
                        const double moduleOffset,
                        int model);
//---------------------------------------------------------------------------
// Integration of the solar power kWH/m^2 for a day at given latitude
//
// Integration is done by a simple sum over small elements
// Input: Latitude in degrees, positive north of equator
//        Declination of the sun in degrees
// Output: Total energy per square metre over a day arriving at earth's surface
// Dependencies: pathLoss(cosangle) integral of air density over a slant path

double dailySolarEnergyFollowing(const double latitude,
                                 const double declination);
//----------------------------------------------------------------------------
// Integration of the solar power kWH/m^2 for a day at given latitude
//
// Integration is done by a simple sum over small elements.
// Represents a fixed module facing the sun at noon.
// Input: Latitude in degrees, positive north of equator
//        Declination of the sun in degrees
//        Angle of the module to the vertical
//        Angle offset of module from North towards East in degrees
// Output: Total energy per square metre over a day arriving at earth's surface
// Dependencies: pathLoss(cosangle) integral of air density over a slant path

double dailySolarEnergyFixed(const double latitude,
                             const double declination,
                             const double moduleAngle,
                             const double moduleOffset);

#endif /*SPCOMPUTATIONS_H_*/

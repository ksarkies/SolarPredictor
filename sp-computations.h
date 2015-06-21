/* Solar Power Computational Routines

A variety of routines producing high level results.
*/
 
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

double computeAnnualReturnFixedMPP(const double latitude,
                        const double moduleAngle,
                        const double moduleOffset,
                        const double cost,
                        const double feedIn,
                        const double usage);

double computeDailyFixedMPPReturn(const double latitude,
                           const double declination,
                           const double moduleAngle,
                           const double moduleOffset,
                           const double cost,
                           const double feedIn,
                           const double usage);
double solarFollowingCharge(const double latitude,
                            const double declination,
                            const int model);
double solarFixedCharge(const double latitude,
                        const double declination,
                        const double moduleAngle,
                        const double moduleOffset,
                        int model);
double dailySolarEnergyFollowing(const double latitude,
                                 const double declination);
double dailySolarEnergyFixed(const double latitude,
                             const double declination,
                             const double moduleAngle,
                             const double moduleOffset);

#endif /*SPCOMPUTATIONS_H_*/

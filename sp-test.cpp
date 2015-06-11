// A set of test routines for the Solar Power Models.
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

#include "sp-test.h"
#include "sp-atmospherics.h"
#include "sp-module-model.h"
#include "sp-computations.h"
#include "sp-general.h"
#include "model.h"
#include <iostream>                                 // Base stream classes
#include <cmath>

//----------------------------------------------------------------------------
// Printout of air density

void printAirDensity()
{
    for (double h=0;h<30000;h+=1000)
    {
       std::cout << h << " " << airDensity(h) << std::endl;
    }
}

// Solar power variation sun directly overhead at noon

void printSolarPowerNoon()
{
    const double lossConstant = getLossConstant();
    const double angleConversion = 3.1415927/180.0;
    const double solarConstant = getSolarConstant();
    double cosangle = 1;
    double hour = 12;
    while (cosangle > 0)
    {
        double solarEnergy =
              solarConstant*exp(-lossConstant*pathLoss(cosangle));
        std::cout << hour << "," << solarEnergy << std::endl;
        hour += 0.1;
        cosangle = cos(angleConversion*15*(hour-12));
    }
}

//----------------------------------------------------------------------------
// Total daily energy from modules over latitudes

void printDailyEnergyLatitudes()
{
    double declination = maxDeclination;
    for (float n = -60; n < 60; n++)                 //Range over latitudes
    {
        double latitude = n;
        std::cout << latitude << ","
                  << dayLength(latitude,maxDeclination) << ","
                  << dailySolarEnergyFollowing(latitude,declination) << ","
                  << dailySolarEnergyFixed(latitude,declination,declination,0)
                  << ","
                  << dailySolarEnergyFixed(latitude,declination,latitude,0)
                  << std::endl;
    }
}

//----------------------------------------------------------------------------
// Daily Global Solar Radiation at Armidale
// FIxed panel flat on the ground, module angle zero.

void printSolarRadiationArmidale()
{
    double latitude = -30.5;
    for (int month = 0; month < 12; month++)
    {
        double declination = maxDeclination*sin(2*3.1415927*(month-2.25)/12);
        std::cout << dailySolarEnergyFixed(latitude,declination,0,0)
                  << std::endl;
    }
    for (unsigned int v = 0; v < 230; v++) std::cout << (double)v/10 << ","
         << moduleCurrent(100,(double)v/10) << std::endl;
}

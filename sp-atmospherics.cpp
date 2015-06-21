/* Solar Power Atmospheric Effects Routines

Routines for computing air density and atmospheric path loss.
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

#include <cmath>

/*----------------------------------------------------------------------------*/
/** @brief Compute the density of air from a suitable model

Glenn Research Centre http://www.grc.nasa.gov/WWW/K-12/airplane/atmos.html
The units of the model are given in imperial, so we convert to metric last

@param[in]: height in metres
@returns: air density in kg/m^3
*/
double airDensity(const double height)
{
    double Ta;                               // Absolute temperature
    double pressure;                         // pressure lbs/ft^2
    if (height < 11019)
    {
        Ta = 288.2 - 0.00649 * height;
        pressure = 10331 * pow(0.003471*Ta,5.256);
    }
    else if (height < 25099)
    {
        Ta = 216.5;
        pressure = 2309.9 * exp(1.73-0.00015748*height);
    }
    else
    {
        Ta = 141.5 + 0.00299 * height;
        pressure = 253.39 * pow(0.0046*Ta,-11.388);
    }
    return pressure*0.0341636/Ta;           // density in kg/m^3
}
/*----------------------------------------------------------------------------*/
/** @brief Numerical integration of air density over a sloping solar ray path.

The angle of the path to the vertical is phi. To integrate density rho(h)
as a function of height, over the path length a, we compute the slope of the
path with respect to the height from ground level to get:

     integral from 0 to infinity rho(h) (da/dh) dh

@param[in]: cosine of angle of path to vertical phi in degrees
@returns: Path loss. Units are arbitrary as this appears only in ratios.
*/
double pathLoss(const double cosPhi)
{
    const double R = 6335437;                   // earth radius in metres
    double hIncr = 10;                          // Integration increment m
    double h = hIncr;                           // height above sea level
/* Because of numerical problems near h=0, cosPhi=0 (tangential incidence)
we integrate over the first height step using constant density equal
to the average of the step (trapezoidal approximation) */
    double loss = 0.5*hIncr*(airDensity(h) + airDensity(0))
                * (2*R + h)*h/(R*cosPhi+sqrt(R*R*cosPhi*cosPhi+2*h*R + h*h));
/* This starts off the trapezoidal approximation (see notes)
99.999% of air mass is below 100km, so we stop iteration there.
As density contribution falls away with height, increase increment to
speed up things. */
    loss += 0.5*hIncr*airDensity(h)*(R + h)/
                sqrt(R*R*cosPhi*cosPhi+2*h*R + h*h);
    while (h < 100000)
    {
        if (h > 6000) hIncr = 20;
        else if (h > 10000) hIncr = 50;
        else if (h > 16000) hIncr = 100;
        h += hIncr;
        loss += hIncr*airDensity(h)*(R + h)/
                    sqrt(R*R*cosPhi*cosPhi+2*h*R + h*h);
    }
    return loss;
}
/*----------------------------------------------------------------------------*/
/** @brief Return the amount of solar power W/m^2 incident on the Earth's upper
atmosphere.

@returns: solar constant W/m^2
*/

double getSolarConstant()
{
    return 1366;
}
/*----------------------------------------------------------------------------*/
/** @brief A constant used to determine the rate of loss of solar power through
the atmosphere.

@returns: loss constant
*/

double getLossConstant()
{
    return 0.253617853024622586/pathLoss(1);
}

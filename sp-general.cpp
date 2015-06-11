/* Solar Power General Functions
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
/* Length of day in hours for given latitude and solar declination
There is 15 degrees per hour movement of the sun.
Input: Latitude in degrees, positive north of equator
       Declination of the sun in degrees
Output: length of day sunrise to sunset in hours. */

double dayLength(const double latitude, const double declination)
{
    const double angleConversion = 3.1415927/180.0;
    double rLatitude = latitude*angleConversion;
    const double rDeclination = declination*angleConversion;
    return 2*acos(-tan(rLatitude)*tan(rDeclination))/(15*angleConversion);
}
/*----------------------------------------------------------------------------*/
/* Declination of the Sun for a given day of Year
Input: Day of year counting from 0 at January 1
Output: Declination in degrees
This heuristic is taken from Wikipedia referencing
Spencer, J.W. 1971: Fourier series representation of the position of the Sun.
  Search, 2(5), 172 */

double sunDeclination(const double dayYear)
{
    const double angleConversion = 3.1415927/180.0;
    double gamma = angleConversion*360/365*dayYear;
    return (0.006918 - 0.399912 * cos(gamma) + 0.070257 * sin(gamma)
            - 0.006758 * cos(2*gamma) + 0.000907 * sin(2*gamma)
            - 0.002697 * cos(3*gamma) + 0.00148 * sin(3*gamma))/angleConversion;
}
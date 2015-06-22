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

#include "sp-computations.h"
#include "model.h"
#include "sp-module-model.h"
#include "sp-atmospherics.h"
#include "sp-general.h"
#include <cmath>
#include <QDebug>

/*----------------------------------------------------------------------------*/
/** @brief Annual return for a fixed module system, MPP tracking regulator,

Offset and feed-in tariffs provided for usage offset and excess.

The model includes average cloud cover estimates from the BOM. These are
quite rough measures for this purpose and produce much lower returns than
a more suitable model would give.

This provides for computations of accumulated income over a block of days.

@param[in]: Latitude in degrees, positive north of equator
@param[in]: Angle of the module to the vertical
@param[in]: Angle offset of module from North towards East
@param[in]: cost is the tariff ($/kwH) paid by the user for power taken from the
            grid
@param[in]: feedIn is the tariff ($/kwH) paid to the user for power returned to
            the grid
@param[in]: usage is the average power in kW taken by the user during the day
            (note that this is a fixed amount for daylight hours only, and
            excludes additional power used at night which is not offset by
            solar generated power).
@param[in]: dayYear is the numerical integer day of the year, 0 being Jan 1.
@results:   Monetary return for the day in $.
*/

double computeAnnualFixedMPPReturn(const double latitude,
                             const double moduleAngle,
                             const double moduleOffset,
                             const double cost,
                             const double feedIn,
                             const double usage,
                             const int dayYear,
                             const bool useOkta)
{
    double declination = sunDeclination(dayYear);
    double dayIncome = computeDailyFixedMPPReturn(latitude,
                           declination,
                           moduleAngle, moduleOffset,
                           cost,feedIn,usage);
    if (useOkta) dayIncome *= oktaFactor[month(dayYear)];
    return dayIncome;
}

/*----------------------------------------------------------------------------*/
/** @brief Daily return for a fixed module system, MPP tracking regulator,

The regulator will use Maximum power Point (MPP) tracking for efficiency.
The module is fixed at a preset angle to the sun.
Incident radiation is integrated over time by a simple sum over small elements
taking into account the angle of the suns rays to the module and atmospheric
absorption.

Financial return is the payment for excess power, if any, plus the savings on
cost of power taken from the system rather than the grid.

@param[in]: Latitude in degrees, positive north of equator
@param[in]: Declination of the sun in degrees
@param[in]: Angle of the module to the vertical
@param[in]: Angle offset of module from North towards East
@param[in]: cost is the tariff ($/kwH) paid by the user for power taken from the
            grid
@param[in]: feedIn is the tariff ($/kwH) paid to the user for power returned to
            the grid
@param[in]: usage is the average power in kW taken by the user during the day
            (note that this is a fixed amount for daylight hours only, and
            excludes additional power used at night which is not offset by
            solar generated power).
@results:   Monetary return for the day in $.

Dependencies: pathLoss(cosangle) integral of air density over a slant path */

double computeDailyFixedMPPReturn(const double latitude,
                                const double declination,
                                const double moduleAngle,
                                const double moduleOffset,
                                const double cost,
                                const double feedIn,
                                const double usage)
{
    const double angleConversion = 3.1415927/180.0;
    const double rDeclination = declination*angleConversion;
    const double cosDeclination = cos(rDeclination);
    const double sinDeclination = sin(rDeclination);
    const double rLatitude = latitude*angleConversion;
    const double cosLatitude = cos(rLatitude);
    const double sinLatitude = sin(rLatitude);
    const double rModuleAngle = moduleAngle*angleConversion;
    const double cosModuleAngle = cos(rModuleAngle+rLatitude);
    const double sinModuleAngle = sin(rModuleAngle+rLatitude);
    const double solarConstant = getSolarConstant();
    const double lossConstant = getLossConstant();
    const double solarStandard = getSolarStandard();
    
    int minuteIncr = 1;                     // time integration step size
    double solarEnergyFixed = 0;
    double financialReturn = 0;             // Power from solar module at MPP
    double income = 0;
/* Compute the power incident on the module during the time interval
Start at midday and work forwards then backwards.
Each time check for the sun to be both above the horizon and incident
on the panel */
    int finished = false;
    while (! finished)
    {
        int minute = 0;
        double cosAngle = 1;
        double cosIncidence = 1;
        while ((cosAngle > 0) && (cosIncidence > 0))
        {
/* Longitudinal angle associated with the movement of the Earth at the time,
relative to a longitudinal axis at noon.
Note: 0.25 degrees per minute movement. */
            double cosHourAngle = cos(0.25*minute*angleConversion);
/* Angle associated with the movement of the Earth, but with respect to the
directional offset of the module from North. */
            double cosOffsetHourAngle = 
                        cos((0.25*minute+moduleOffset)*angleConversion);
/* Angle of the sun to the vertical axis at the site and at the time.
Needed to determine the atmospheric loss */
            cosAngle = cosLatitude*cosDeclination*cosHourAngle
                        + sinLatitude*sinDeclination;
/* Angle of the sun to the module orthogonal axis.
Needed to determine proportion of solar energy incident on the module. */
            cosIncidence = cosModuleAngle*cosDeclination*cosOffsetHourAngle
                            + sinModuleAngle*sinDeclination;
/* Solar energy received (W/m2) by a fixed module facing the sun at noon */
            if (cosIncidence > 0)
                solarEnergyFixed = solarConstant*cosIncidence*
                           exp(-lossConstant*pathLoss(cosAngle));
            else
                solarEnergyFixed = 0;
/* Percentage of solar energy received relative to the standard */
            double solarEnergyRatioFixed = solarEnergyFixed*100/solarStandard;
/* Power generated at the Maximum Power Point (MPP) of the module in kW */
            double power = OptimalModulePower(solarEnergyRatioFixed)/1000;
/* Integration of financial return. Costs per kWH over each hour. */
            if (power > usage) income = feedIn*(power - usage) + cost*usage;
            else income = cost*power;
            financialReturn += income/60;
            minute += minuteIncr;
        }
        finished = (minuteIncr < 0);
        minuteIncr = -1;
    }
    return financialReturn;
}

/*----------------------------------------------------------------------------*/
/** @brief Computation of daily charge for a module that following sun's motion.

Varieties of models:
1. module delivering full power to the battery.
2. module output voltage held to battery voltage.
3. module following Maximum power Point.
Represents a module always facing the sun in both elevation and azimuth.
Integration is done by a simple sum over small elements given in minute
increments and over half a day. The result is converted to WH by dividing
by 60 and multiplying by 2 for the second half of the day.

@param[in]: Latitude in degrees, positive north of equator
@param[in]: Declination of the sun in degrees
@param[in]: Model number
@results:   Total charge in AH delivered to the battery over the day.

Dependencies: pathLoss(cosangle) integral of air density over a slant path */

double solarFollowingCharge(const double latitude,
                            const double declination,
                            const int model,
                            const double modulePower)
{
    const double angleConversion = 3.1415927/180.0;
    const double rDeclination = declination*angleConversion;
    const double cosDeclination = cos(rDeclination);
    const double sinDeclination = sin(rDeclination);
    const double rLatitude = latitude*angleConversion;
    const double cosLatitude = cos(rLatitude);
    const double sinLatitude = sin(rLatitude);
    const double solarConstant = getSolarConstant();
    const double lossConstant = getLossConstant();
    const double solarStandard = getSolarStandard();
    const double energyCharge = modulePower/getSolarStandard()/batteryVoltage;
    int minuteIncr = 1;                // time integration step size
    int minute = 0;
    double cosAngle = 1;
    double solarEnergyFollowing = 0;
    double solarEnergyFollowingCharge = 0;
/* Compute the power incident on the module during the time interval */
    while (cosAngle > 0)
    {
/* Longitudinal angle associated with the movement of the earth at the time,
relative to a longitudinal axis at noon. */
        double cosHourAngle = cos(0.25*minute*angleConversion);
/* Angle of the sun to the vertical axis at the site and at the time */
        cosAngle = cosLatitude*cosDeclination*cosHourAngle
                 + sinLatitude*sinDeclination;
/* Solar energy (W/m2) incident on the module for a following module */
        solarEnergyFollowing = solarConstant*
                       exp(-lossConstant*pathLoss(cosAngle));
/* Percentage of solar energy received relative to the standard */
        double solarEnergyRatioFollowing =
                                  solarEnergyFollowing*100/solarStandard;
/* Charge delivered to the module as a result of the incident energy. */
        switch (model)
        {
        case 1:
/* Full power into system */
            solarEnergyFollowingCharge += solarEnergyFollowing*energyCharge;
            break;
        case 2:
/* Current into battery if the module is held at the battery voltage */
            solarEnergyFollowingCharge +=
                    moduleCurrent(solarEnergyRatioFollowing,batteryVoltage);
            break;
        case 3:
            solarEnergyFollowingCharge +=
                    OptimalModulePower(solarEnergyRatioFollowing)/batteryVoltage;
            break;
        }
        minute += minuteIncr;
    }
    return solarEnergyFollowingCharge/30;
}

/*----------------------------------------------------------------------------*/
/** @brief Computation of daily charge for a fixed module.

Simplistic model with module giving full power.
Integration is done by a simple sum over small elements.
Represents a fixed module facing the sun at noon.

@param[in]: double Latitude in degrees, positive north of equator
@param[in]: Declination of the sun in degrees
@param[in]: Angle of the module to the vertical
@param[in]: Offset of the module in degrees from the North to the East
@param[in]: Model number
@results:   Total charge in AH delivered to the battery over the day.

Dependencies: pathLoss(cosangle) integral of air density over a slant path */

double solarFixedCharge(const double latitude,
                        const double declination,
                        const double moduleAngle,
                        const double moduleOffset,
                        int model,
                        const double modulePower)
{
    const double angleConversion = 3.1415927/180.0;
    const double rDeclination = declination*angleConversion;
    const double cosDeclination = cos(rDeclination);
    const double sinDeclination = sin(rDeclination);
    const double rLatitude = latitude*angleConversion;
    const double cosLatitude = cos(rLatitude);
    const double sinLatitude = sin(rLatitude);
    const double rModuleAngle = moduleAngle*angleConversion;
    const double cosModuleAngle = cos(rModuleAngle+rLatitude);
    const double sinModuleAngle = sin(rModuleAngle+rLatitude);
    const double solarConstant = getSolarConstant();
    const double lossConstant = getLossConstant();
    const double solarStandard = getSolarStandard();
    const double energyCharge = modulePower/getSolarStandard()/batteryVoltage;
    int minuteIncr = 1;                // time integration step size
    double solarEnergyFixed = 0;
    double solarEnergyFixedCharge = 0;
/* Compute the power incident on the module during the time interval
Start at midday and work forwards then backwards.
Each time check for the sun to be both above the horizon and incident
on the panel */
    int finished = false;
    while (! finished)
    {
        int minute = 0;
        double cosAngle = 1;
        double cosIncidence = 1;
        while ((cosAngle > 0) && (cosIncidence > 0))
        {
/* Longitudinal angle associated with the movement of the Earth at the time,
relative to a longitudinal axis at noon.
Note: 0.25 degrees per minute movement. */
            double cosHourAngle = cos(0.25*minute*angleConversion);
/* Angle associated with the movement of the Earth, but with respect to the
directional offset of the module from North. */
            double cosOffsetHourAngle = 
                        cos((0.25*minute+moduleOffset)*angleConversion);
/* Angle of the sun to the vertical axis at the site and at the time.
Needed to determine the atmospheric loss */
            cosAngle = cosLatitude*cosDeclination*cosHourAngle
                 + sinLatitude*sinDeclination;
/* Angle of the sun to the module orthogonal axis.
Needed to determine proportion of solar energy incident on the module. */
            cosIncidence = cosModuleAngle*cosDeclination*cosOffsetHourAngle
                            + sinModuleAngle*sinDeclination;
/* Solar energy received (W/m2) by a fixed module facing the sun at noon */
            if (cosIncidence > 0)
                solarEnergyFixed = solarConstant*cosIncidence*
                           exp(-lossConstant*pathLoss(cosAngle));
            else
                solarEnergyFixed = 0;
/* Percentage of solar energy received relative to the standard */
            double solarEnergyRatioFixed = solarEnergyFixed*100/solarStandard;
/* Charge delivered to the module as a result of the incident energy. */
            switch (model)
            {
            case 1:
/* Full power into system */
                solarEnergyFixedCharge += solarEnergyFixed*energyCharge;
                break;
            case 2:
/* Current into battery if the module is held at the battery voltage */
                solarEnergyFixedCharge +=
                    moduleCurrent(solarEnergyRatioFixed,batteryVoltage);
                break;
            case 3:
                solarEnergyFixedCharge +=
                    OptimalModulePower(solarEnergyRatioFixed)/batteryVoltage;
                break;
            }
            minute += minuteIncr;
        }
        finished = (minuteIncr < 0);
        minuteIncr = -1;
    }
    return solarEnergyFixedCharge/60;
}

/*----------------------------------------------------------------------------*/
/** @brief Integration of solar energy for following module.

Integration of the solar energy (W/m^2) to give total generated energy (kWH/m^2)
over a day at a given latitude for a module that follows the motion of the sun.

Integration is done by a simple sum over small elements given in minute
increments and over half a day. The result is converted to kWH by dividing
by 60,000 and multiplying by 2 for the second half of the day.
Represents a module always facing the sun in both elevation and azimuth.

@param[in]: Latitude in degrees, positive north of equator
@param[in]: Declination of the sun in degrees
@results:   Total energy per square metre over a day arriving at the module
            surface

Dependencies: pathLoss(cosangle) integral of air density over a slant path */

double dailySolarEnergyFollowing(const double latitude,
                                 const double declination)
{
    const double angleConversion = 3.1415927/180.0;
    const double rDeclination = declination*angleConversion;
    const double cosDeclination = cos(rDeclination);
    const double sinDeclination = sin(rDeclination);
    const double rLatitude = latitude*angleConversion;
    const double cosLatitude = cos(rLatitude);
    const double sinLatitude = sin(rLatitude);
    const double lossConstant = getLossConstant();
    const double solarConstant = getSolarConstant();  // W/m^2 outer atmosphere
    int minuteIncr = 1;                            // integration step size
    int minute = 0;
    double cosAngle = 1;
    double solarEnergy = 0;
    while (cosAngle > 0)
    {
        double cosHourAngle = cos(0.25*minute*angleConversion);
        cosAngle = cosLatitude*cosDeclination*cosHourAngle
                    + sinLatitude*sinDeclination;
        solarEnergy += solarConstant*exp(-lossConstant*pathLoss(cosAngle));
        minute += minuteIncr;
    }
    return solarEnergy/30000;
}

/*----------------------------------------------------------------------------*/
/** @brief Integration of solar energy for fixed module.

Integration of the solar energy (W/m^2) to give total generated energy (kWH/m^2)
for a day at given latitude and fixed panels.

Integration is done by a simple sum over small elements given in minute
increments and over half a day. The result is converted to kWH by dividing
by 60,000 and multiplying by 2 for the second half of the day.
Represents a fixed module facing the sun at noon.
@param[in]: Latitude in degrees, positive north of equator
@param[in]: Declination of the sun in degrees
@param[in]: Angle of the module to the equatorial plane
@param[in]: Offset of the module  in degrees from the North to the East
@results:   Total energy per square metre over a day arriving at earth's surface.

Dependencies: pathLoss(cosangle) integral of air density over a slant path. */

double dailySolarEnergyFixed(const double latitude,
                             const double declination,
                             const double moduleAngle,
                             const double moduleOffset)
{
    const double angleConversion = 3.1415927/180.0;
    const double rDeclination = declination*angleConversion;
    const double cosDeclination = cos(rDeclination);
    const double sinDeclination = sin(rDeclination);
    const double rLatitude = latitude*angleConversion;
    const double cosLatitude = cos(rLatitude);
    const double sinLatitude = sin(rLatitude);
    const double rModuleAngle = moduleAngle*angleConversion;
    const double cosModuleAngle = cos(rModuleAngle+rLatitude);
    const double sinModuleAngle = sin(rModuleAngle+rLatitude);
    const double solarConstant = getSolarConstant();
    const double lossConstant = getLossConstant();
    int minuteIncr = 1;                          // integration step size
    double solarEnergy = 0;
/* Start at midday and work forwards then backwards.
Each time check for the sun to be both above the horizon and incident
on the panel */
    int finished = false;
    while (! finished)
    {
        int minute = 0;
        double cosAngle = 1;
        double cosIncidence = 1;
        while ((cosAngle > 0) && (cosIncidence > 0))
        {
            double cosHourAngle = cos(0.25*minute*angleConversion);
            cosAngle = cosLatitude*cosDeclination*cosHourAngle
                     + sinLatitude*sinDeclination;
/* Angle associated with the movement of the Earth, but with respect to the
directional offset of the module from North. */
            double cosOffsetHourAngle = 
                        cos((0.25*minute+moduleOffset)*angleConversion);
/* Angle of the sun to the module orthogonal axis.
Needed to determine proportion of solar energy incident on the module. */
            cosIncidence = cosModuleAngle*cosDeclination*cosOffsetHourAngle
                            + sinModuleAngle*sinDeclination;
            if (cosIncidence > 0)
                solarEnergy += solarConstant*cosIncidence*
                               exp(-lossConstant*pathLoss(cosAngle));
            minute += minuteIncr;
        }
    finished = (minuteIncr < 0);
    minuteIncr = -1;
    }
    return solarEnergy/60000;
}

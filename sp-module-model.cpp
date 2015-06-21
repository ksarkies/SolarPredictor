/* Models for the PV Module

This model is a basic single diode three parameter model. This is not
particularly accurate but uses parameters that are (sometimes) easily obtained
from user datasheets.

A call to setModelParameters or deriveSimpleModel must be made first to set the
module parameters, otherwise arithmetic exceptions may occur. No explicit
error checking is done.
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
#include "sp-module-model.h"

static moduleModelParameters parms;

/*----------------------------------------------------------------------------*/
/** @brief Model for solar module

Solar current generated is proportional to the short circuit current
portion only, the second term is the diode loss term.

@param[in]: const double solarEnergy. The percentage of the standard incident
            solar radiation used to define the module characteristics (ie
            typically 1000 W/m2).
@param[in]: const double voltage. That which is forced on the module by the
            system (that is, battery or MPP regulator voltage.
@returns: double. Module generated current in Amperes.
*/

double moduleCurrent(const double solarEnergy, const double voltage)
{
    double b = parms.Isc*solarEnergy*0.01/parms.I0+1;
    double current = parms.I0*(b-exp(voltage/parms.Vk));
    if (current < 0) current = 0;
    return current;
}
/*----------------------------------------------------------------------------*/
/** @brief Model for solar module BP3125 with a maximum power point tracker.

This uses a simple hill-climbing search for maximum power starting at the
open-circuit voltage and stepping back to the peak.

@param[in]: const double solarEnergy. The percentage of the standard incident
            solar radiation used to define the module characteristics
            (ie typically 1000 W/m2).
@returns: double. Module generated power (Watt)
*/

double OptimalModulePower(const double solarEnergy)
{
    if (solarEnergy == 0) return 0;
    double b = parms.Isc*solarEnergy*0.01/parms.I0+1;
    double Voc = parms.Vk*log(b);       // Open Circuit voltage
    double Vinc = Voc/10;               // Initial increment
    double V = Voc;                     // Stepping back from here
    double powerLast = 0;               // previous power computation
    double power;
    for (int j = 0; j < 4; j++)
    {
        bool finished = false;
        while (! finished)
        {
            V -= Vinc;
            power = V*parms.I0*(b-exp(V/parms.Vk));
            if (power <= powerLast) finished = true;
            powerLast = power;
         }
        V += Vinc;
        Vinc /= 10;
    }
/* Buck regulator only
   if (V < 12) V = 12;          // MPP is below battery voltage
   if (Voc < 12) V = 0;         // Highest voltage is below battery */
    return power*parms.NM*parms.eff;
}
/*----------------------------------------------------------------------------*/
/** @brief Model for solar module BP3125 with a maximum power point tracker.

Sets the local parameters structure for use with the model.

@param[in] const int NM                 // Number of Modules
@param[in] const double Isc             // Short Circuit Current (A)
@param[in] const double I0              // Diode dark current (A)
@param[in] const double Vk              // Model parameter voltage (V)
@param[in] const double eff             // Fractional efficiency of regulator
@param[in] const double Rs              // Diode series resistance
@param[in] const int Ns                 // Number of cells in series
*/

void setModelParameters(const int NM, const double Isc, const double I0,
                        const double Vk, const double eff, const double Rs,
                        const int Ns)
{
    parms.NM = NM;
    parms.Isc = Isc;
    parms.I0 = I0;
    parms.Vk = Vk;
    parms.eff = eff;
    parms.Rs = Rs;
    parms.Ns = Ns;
}

/*----------------------------------------------------------------------------*/
/** @brief Compute model parameters for simple diode model of solar cell.

Match three common current/voltage points normally quoted in datasheets to
obtain the characteristic parameters of the model pn junction. Model is correct
only at these points (short-circuit, open-circuit and maximum power).
Sets the model datastructure values from these common curve points.

This makes the assumption, usually good, that I0 is a very small value
compared to other currents flowing.

@param[in] const int NM                 // Number of Modules
@param[in] const double Isc             // Short Circuit Current (A)
@param[in] const double Voc             // Module open circuit voltage (V)
@param[in] const double Vm              // Module maximum power voltage (V)
@param[in] const double Im              // Module maximum power current (A)
@param[in] const double eff             // Fractional efficiency of regulator
@param[in] const int Ns                 // Number of cells in series
@*/

void deriveSimpleModel(const int NM, const double Isc, const double Voc,
                       const double Vm, const double Im, const double eff,
                       const int Ns)
{
    parms.NM = NM;
    parms.Isc = Isc;
    parms.Vk = (Vm - Voc)/(Ns*log(1-Im/Isc));
    parms.I0 = Isc*exp(-Voc/(Ns*parms.Vk));
    parms.eff = eff;
    parms.Ns = Ns;
}

/*----------------------------------------------------------------------------*/
/** @brief Return standard value of incident solar power.

This represents the nominal power incident on the Earth's surface after
traversing the atmosphere when the Sun is vertically overhead.

@returns: Standard incident solar power W/m^2 used to specify solar modules.
*/

double getSolarStandard()
{
    return 1000;
}
/*----------------------------------------------------------------------------*/
/** @brief Return diode parameter Vk.

@returns: Vk
*/

double getVk()
{
    return parms.Vk;
}
/*----------------------------------------------------------------------------*/
/** @brief Return diode parameter I0.

@returns: I0.
*/

double getI0()
{
    return parms.I0;
}

/* Models for the PV Module
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

/* BP3125 polycrystalline 120W
   const double Isc = 8.02;      // Short Circuit Current (A)
   const double I0 = 0.000185;   // Diode dark current (A)
   const double Vk = 2.071;      // Model parameter voltage (V)
Kaneka GEB 60W set of 24 (1.4KW system) */
    const double NM = 24;           // Number of Modules
    const double Isc = 1.19*NM;     // Short Circuit Current (A)
    const double I0 = 0.00643*NM;   // Diode dark current (A)
    const double Vk = 17.6;         // Model parameter voltage (V)
    const double eff = 0.93;        // Efficiency of regulator

/*----------------------------------------------------------------------------*/
/* Model for solar module

Match three current/voltage points to obtain the characteristic parameters
of the model pn junction. Model is correct only at these points
(short-circuit, open-circuit and maximum power).
Solar current generated is proportional to the short circuit current
portion only, the second term is the diode loss term.

Input: solarEnergy is the percentage of the standard incident solar radiation
         used to define the module characteristics (ie typically 1000 W/m2).
       Voltage is that which is forced on the module by the system (that is,
         battery or MPP regulator voltage.
Output: Module generated current in Amperes. */

double moduleCurrent(const double solarEnergy, const double voltage)
{
    double b = Isc*solarEnergy*0.01/I0+1;
    double current = I0*(b-exp(voltage/Vk));
    if (current < 0) current = 0;
    return current;
}
/*----------------------------------------------------------------------------*/
/* Model for solar module BP3125 with a maximum power point tracker.

This uses a simple hill-climbing search for maximum power starting at the
open-circuit voltage and stepping back to the peak.

Input: solarEnergy is the percentage of the standard incident solar radiation
         used to define the module characteristics (ie typically 1000 W/m2).
Output: Module generated power (Watt) */

double OptimalModulePower(const double solarEnergy)
{
    if (solarEnergy == 0) return 0;
    double b = Isc*solarEnergy*0.01/I0+1;
    double Voc = Vk*log(b);       // Open Circuit voltage
    double Vinc = Voc/10;         // Initial increment
    double V = Voc;               // Stepping back from here
    double powerLast = 0;         // previous power computation
    double power;
    for (int j = 0; j < 4; j++)
    {
        bool finished = false;
        while (! finished)
        {
            V -= Vinc;
            power = V*I0*(b-exp(V/Vk));
            if (power <= powerLast) finished = true;
            powerLast = power;
         }
        V += Vinc;
        Vinc /= 10;
    }
/* Buck regulator only
   if (V < 12) V = 12;       // MPP is below battery voltage
   if (Voc < 12) V = 0;      // Highest voltage is below battery */
    return power*eff;
}
/*----------------------------------------------------------------------------*/
/* Standard incident solar power W/m^2 used to specify solar modules. This
represents the nominal power incident on the Earth's surface after traversing
the atmosphere when the Sun is vertically overhead. */

double getSolarStandard()
{
    return 1000;
}

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

/*  BP3125 polycrystalline 120W
    double Isc = 8.02;              // Short Circuit Current (A)
    double I0 = 0.000185;           // Diode dark current (A)
    double Vk = 2.071;              // Model parameter voltage (V)
    int Ns = 36;                    // Number of cells in series
*/
/* Kaneka GEB 60W set of 24 (1.4KW system)
    int NM = 24;                    // Number of Modules
    double Isc = 1.19*NM;           // Short Circuit Current (A)
    double I0 = 0.00643*NM;         // Diode dark current (A)
    double Vk = 17.6;               // Model parameter voltage (V)
    double eff = 0.93;              // Fractional efficiency of regulator
*/
struct moduleModelParameters
{
    int NM;                         // Number of Modules in parallel
    double Isc;                     // Short Circuit Current (A)
    double I0;                      // Diode dark current (A)
    double Vk;                      // Model parameter voltage (V)
    double eff;                     // Fractional efficiency of regulator
    double Rs;                      // Diode series resistance (ohm)
    double Ns;                      // Number of cells in series
};

/*----------------------------------------------------------------------------*/
double moduleCurrent(const double solarEnergy, const double voltage);
double OptimalModulePower(const double solarEnergy);
void setModelParameters(const int NM,const double Isc,const double I0,
                        const double Vk,const double eff, const double Rs,
                        const int Ns);
void deriveSimpleModel(const int NM, const double Isc, const double Voc,
                       const double Vm, const double Im, const double eff,
                       const int Ns);
double getSolarStandard();
double getVk();
double getI0();

#endif /*SPMODULEMODEL_H_*/

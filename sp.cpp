/** Solar Energy Predictor

This program executes a model of the solar energy (kWH/m^2) arriving at a
solar module that is set at an arbitrary angle, and on an arbitrary day of
the year. It works by first proposing a Glenn Research Centre model of the
atmospheric absorption as a function of height, based on a model of air
density. From the known absorption for sunlight arriving when the sun is
vertically overhead, a model of the absorption of slant rays is developed.

ISOLATED BATTERY BACKED SYSTEMS
Using an electrical model of a solar module feeding a battery, it is
possible to predict the total amount of charge passed into the battery and
hence the effectiveness of the system. Because the solar module is not
necessarily working at its maximum power point (MPP), there is an additional
drop in efficiency that can be demonstrated. Also the behaviour of the
battery regulator which protects the batteries from overcharge can be taken
into account.

The aim is to predict the amount of energy obtained during the shortest
clear day for the purposes of understanding the performance of a solar
module in a battery charging system, and dimensioning a solar power system.

GRID-CONNECT SYSTEMS
The models are also used to compute financial returns on different grid-
connect scenarios to assist in decision making. The regulator is considered
to be an MPP tracker, and no battery backing is provided.

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

#include "sp.h"
#include "sp-computations.h"
#include "sp-general.h"
#include "model.h"
#include <QApplication>
#include <QString>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
#include <QTextEdit>
#include <QCloseEvent>
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QDebug>
#include <cstdlib>
#include <unistd.h>
#include <iostream>                                 // Base stream classes
#include <cmath>
using namespace std;

//-----------------------------------------------------------------------------
/** Solar Power Simulator Main Window Constructor

@param[in] parent Parent widget.
*/

SolarPowerGui::SolarPowerGui(QWidget* parent) : QDialog(parent)
{
// Build the User Interface display from the Ui class in ui_mainwindowform.h
    SolarPowerUi.setupUi(this);
    SolarPowerUi.computationComboBox->clear();
    SolarPowerUi.computationComboBox->insertItem(0,"Annual, Fixed module, MPP");
    SolarPowerUi.computationComboBox->insertItem(0,"Daily, Fixed module, MPP");
}

SolarPowerGui::~SolarPowerGui()
{
}
//-----------------------------------------------------------------------------
/** Compute

Read the combo box for computation type and edit boxes for parameters and
execute the computation.

*/

void SolarPowerGui::on_goPushButton_clicked()
{
    bool ok = true;
    double latitude;
    double declination;
    double moduleAngle;
    double moduleOffset;
    double cost;
    double feedIn;
    double usage;
    int numberModules = 1;
    double efficiency = 1;
    double scCurrent;
    double ocVoltage;
    double maxPCurrent;
    double maxPVoltage;
    int numberCells = 1;
    latitude = SolarPowerUi.latitudeLineEdit->text().toDouble(&ok);
    if (ok) declination = SolarPowerUi.declinationLineEdit->text().toDouble(&ok);
    if (ok) moduleAngle = SolarPowerUi.moduleAngleLineEdit->text().toDouble(&ok);
    if (ok) moduleOffset = SolarPowerUi.moduleOffsetLineEdit->text().toDouble(&ok);
    if (ok) cost = SolarPowerUi.costLineEdit->text().toDouble(&ok);
    if (ok) feedIn = SolarPowerUi.feedInLineEdit->text().toDouble(&ok);
    if (ok) usage = SolarPowerUi.usageLineEdit->text().toDouble(&ok);
    if (ok) numberModules = SolarPowerUi.numberModulesLineEdit->text().toInt(&ok);
    if (ok) efficiency = SolarPowerUi.efficiencyLineEdit->text().toDouble(&ok);
    if (ok) scCurrent = SolarPowerUi.scCurrentLineEdit->text().toDouble(&ok);
    if (ok) ocVoltage = SolarPowerUi.ocVoltageLineEdit->text().toDouble(&ok);
    if (ok) maxPCurrent = SolarPowerUi.maxPCurrentLineEdit->text().toDouble(&ok);
    if (ok) maxPVoltage = SolarPowerUi.maxPVoltageLineEdit->text().toDouble(&ok);
    if (ok) numberCells = SolarPowerUi.numberCellsLineEdit->text().toInt(&ok);
    if (ok)
    {
        deriveSimpleModel(numberModules,scCurrent,ocVoltage,
                          maxPVoltage,maxPCurrent,efficiency,numberCells);
        if (SolarPowerUi.computationComboBox->currentIndex() == 0)
        {
// Daily
            SolarPowerUi.result->setText(QString("%1").arg(
                    computeDailyFixedMPPReturn(latitude,declination,
                    moduleAngle,moduleOffset,cost,feedIn,usage),2));
        }
        if (SolarPowerUi.computationComboBox->currentIndex() == 1)
        {
// Annual
            SolarPowerUi.computationProgressBar->reset();
            SolarPowerUi.computationProgressBar->setMinimum(0);
            SolarPowerUi.computationProgressBar->setMaximum(365);
            double totalIncome = 0;
            for (int dayYear = 0; dayYear < 365; dayYear++)
            {
                qApp->processEvents();
                totalIncome += computeAnnualFixedMPPReturn(latitude,
                    moduleAngle,moduleOffset,cost,feedIn,usage,dayYear);
                SolarPowerUi.computationProgressBar->setValue(dayYear);
            }
            SolarPowerUi.result->setText(QString("%1").arg(totalIncome,2));
            SolarPowerUi.computationProgressBar->setValue(100);
        }
    }
}
//-----------------------------------------------------------------------------
/* Computation of the full annual return for solar modules oriented at 45 degrees
to the vertical (representing different roof angles).
This example has a 0 degree offset to the north, a tariff of $0.18,
feed in tariff of $0.50 and an average daily power usage of 0.33kW. */
/*    std::cout << "Computation of the full annual return for solar"
              << " modules oriented at 22 degrees"
              << std::endl;
    std::cout << "Vertical Angle " << 22 << " Total Annual Income "
              << computeAnnualReturnFixedMPP(latitude,22,45,0.18,0.50,0)
              << std::endl;
*/

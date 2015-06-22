/* Header for the main GUI code.
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

#ifndef SP_H_
#define SP_H_

#include "ui_sp.h"
#include <QDialog>

//-----------------------------------------------------------------------------
/** @brief Power Management Main Window.

*/

class SolarPowerGui : public QDialog
{
    Q_OBJECT
public:
    SolarPowerGui(QWidget* parent = 0);
    ~SolarPowerGui();
protected:
private slots:
    void on_goPushButton_clicked();
private:
// User Interface object instance
    Ui::SolarPowerDialog SolarPowerUi;
};

#endif /*SP_H_*/

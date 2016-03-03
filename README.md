Solar Power System Simulator
----------------------------

This project aims to provide a tool for modelling a grid connected solar power
system with fixed or following modules and with or without maximum power point
tracker. It accounts for solar declination and atmospheric absorption and
provides for a primitive model of cloud cover.

The result is the savings resulting from power usage offset and feed in of
excess power to the grid.

DEPENDENCIES
The QT 4.8 framework is the only dependency. This was installed on a Ubuntu
Linux distro. Port to Windows has not been done.

More information is available on [Jiggerjuice](http://www.jiggerjuice.info/electronics/solar/solar.html).

K. Sarkies
22 June 2015

TODO
* add file saving and loading of parameters.
* incorporate battery storage for non-grid connected systems to aid in
  deciding the size and number of modules and batteries.
* add in average solar irradiance measurements rather than chunky cloud cover.


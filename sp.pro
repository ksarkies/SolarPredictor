PROJECT =       Solar Power Simulator GUI
TEMPLATE =      app
TARGET          += 
DEPENDPATH      += .
QT              += widgets

OBJECTS_DIR     = obj
MOC_DIR         = moc
UI_DIR          = ui
LANGUAGE        = C++
CONFIG          += qt warn_on release

# Input
FORMS           += sp.ui
HEADERS         += sp.h
SOURCES         += sp.cpp sp-general.cpp sp-module-model.cpp
SOURCES         += sp-main.cpp sp-atmospherics.cpp sp-computations.cpp


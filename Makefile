#############################################################################
# Makefile for building: sp
# Generated by qmake (2.01a) (Qt 4.8.6) on: Mon Jun 22 16:19:23 2015
# Project:  sp.pro
# Template: app
# Command: /usr/bin/qmake-qt4 -o Makefile sp.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++-64 -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -Imoc -Iui
LINK          = g++
LFLAGS        = -m64 -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib/x86_64-linux-gnu -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake-qt4
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = obj/

####### Files

SOURCES       = sp.cpp \
		sp-general.cpp \
		sp-module-model.cpp \
		sp-main.cpp \
		sp-atmospherics.cpp \
		sp-computations.cpp moc/moc_sp.cpp
OBJECTS       = obj/sp.o \
		obj/sp-general.o \
		obj/sp-module-model.o \
		obj/sp-main.o \
		obj/sp-atmospherics.o \
		obj/sp-computations.o \
		obj/moc_sp.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		sp.pro
QMAKE_TARGET  = sp
DESTDIR       = 
TARGET        = sp

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui/ui_sp.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: sp.pro  /usr/share/qt4/mkspecs/linux-g++-64/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/x86_64-linux-gnu/libQtGui.prl \
		/usr/lib/x86_64-linux-gnu/libQtCore.prl
	$(QMAKE) -o Makefile sp.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/shared.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/x86_64-linux-gnu/libQtGui.prl:
/usr/lib/x86_64-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile sp.pro

dist: 
	@$(CHK_DIR_EXISTS) obj/sp1.0.0 || $(MKDIR) obj/sp1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) obj/sp1.0.0/ && $(COPY_FILE) --parents sp.h obj/sp1.0.0/ && $(COPY_FILE) --parents sp.cpp sp-general.cpp sp-module-model.cpp sp-main.cpp sp-atmospherics.cpp sp-computations.cpp obj/sp1.0.0/ && $(COPY_FILE) --parents sp.ui obj/sp1.0.0/ && (cd `dirname obj/sp1.0.0` && $(TAR) sp1.0.0.tar sp1.0.0 && $(COMPRESS) sp1.0.0.tar) && $(MOVE) `dirname obj/sp1.0.0`/sp1.0.0.tar.gz . && $(DEL_FILE) -r obj/sp1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc/moc_sp.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc/moc_sp.cpp
moc/moc_sp.cpp: ui/ui_sp.h \
		sp.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) sp.h -o moc/moc_sp.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui/ui_sp.h
compiler_uic_clean:
	-$(DEL_FILE) ui/ui_sp.h
ui/ui_sp.h: sp.ui
	/usr/lib/x86_64-linux-gnu/qt4/bin/uic sp.ui -o ui/ui_sp.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

obj/sp.o: sp.cpp sp.h \
		ui/ui_sp.h \
		sp-computations.h \
		sp-general.h \
		model.h \
		sp-module-model.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/sp.o sp.cpp

obj/sp-general.o: sp-general.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/sp-general.o sp-general.cpp

obj/sp-module-model.o: sp-module-model.cpp sp-module-model.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/sp-module-model.o sp-module-model.cpp

obj/sp-main.o: sp-main.cpp sp.h \
		ui/ui_sp.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/sp-main.o sp-main.cpp

obj/sp-atmospherics.o: sp-atmospherics.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/sp-atmospherics.o sp-atmospherics.cpp

obj/sp-computations.o: sp-computations.cpp sp-computations.h \
		model.h \
		sp-module-model.h \
		sp-atmospherics.h \
		sp-general.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/sp-computations.o sp-computations.cpp

obj/moc_sp.o: moc/moc_sp.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o obj/moc_sp.o moc/moc_sp.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:


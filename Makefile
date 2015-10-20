#############################################################################
# Makefile for building: SMSAM
# Generated by qmake (2.01a) (Qt 4.8.2) on: Mon Oct 19 16:15:24 2015
# Project:  SMSAM.pro
# Template: app
# Command: /usr/bin/qmake-qt4 -spec /usr/share/qt4/mkspecs/linux-g++ -o Makefile SMSAM.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_WEBKIT -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -w -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -O2 -w -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -IEigen -I. -I.
LINK          = g++
LFLAGS        = -Wl,-O1
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

OBJECTS_DIR   = ./

####### Files

SOURCES       = mainwindow.C \
		main.C \
		formloadmatrix.C \
		formviewmatrix.C \
		stackwidget.C \
		accountwidget.C \
		formvariablesexogenas.cpp \
		stackvariablesexogenas.cpp \
		variableexogenawidget.cpp \
		formexportmatrix.cpp \
		formencadenamientos.cpp \
		stackencadenamientos.cpp \
		encadenamientoswidget.cpp \
		formcompararresultados.cpp \
		formcompararmnc.cpp \
		formincidenciai.cpp \
		formpreciosnohomogeneos.cpp \
		stackpreciosnohomogeneos.cpp \
		variablepnh.cpp moc_mainwindow.cpp \
		moc_formloadmatrix.cpp \
		moc_formviewmatrix.cpp \
		moc_stackwidget.cpp \
		moc_accountwidget.cpp \
		moc_formvariablesexogenas.cpp \
		moc_stackvariablesexogenas.cpp \
		moc_variableexogenawidget.cpp \
		moc_formexportmatrix.cpp \
		moc_formencadenamientos.cpp \
		moc_stackencadenamientos.cpp \
		moc_encadenamientoswidget.cpp \
		moc_formcompararresultados.cpp \
		moc_formcompararmnc.cpp \
		moc_formincidenciai.cpp \
		moc_formpreciosnohomogeneos.cpp \
		moc_stackpreciosnohomogeneos.cpp \
		moc_variablepnh.cpp \
		qrc_img.cpp
OBJECTS       = mainwindow.o \
		main.o \
		formloadmatrix.o \
		formviewmatrix.o \
		stackwidget.o \
		accountwidget.o \
		formvariablesexogenas.o \
		stackvariablesexogenas.o \
		variableexogenawidget.o \
		formexportmatrix.o \
		formencadenamientos.o \
		stackencadenamientos.o \
		encadenamientoswidget.o \
		formcompararresultados.o \
		formcompararmnc.o \
		formincidenciai.o \
		formpreciosnohomogeneos.o \
		stackpreciosnohomogeneos.o \
		variablepnh.o \
		moc_mainwindow.o \
		moc_formloadmatrix.o \
		moc_formviewmatrix.o \
		moc_stackwidget.o \
		moc_accountwidget.o \
		moc_formvariablesexogenas.o \
		moc_stackvariablesexogenas.o \
		moc_variableexogenawidget.o \
		moc_formexportmatrix.o \
		moc_formencadenamientos.o \
		moc_stackencadenamientos.o \
		moc_encadenamientoswidget.o \
		moc_formcompararresultados.o \
		moc_formcompararmnc.o \
		moc_formincidenciai.o \
		moc_formpreciosnohomogeneos.o \
		moc_stackpreciosnohomogeneos.o \
		moc_variablepnh.o \
		qrc_img.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_off.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		SMSAM.pro
QMAKE_TARGET  = SMSAM
DESTDIR       = 
TARGET        = SMSAM

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

$(TARGET): ui_formLoadMatrix.h ui_formMatrixView.h ui_formvariablesexogenas.h ui_formexportmatrix.h ui_formencadenamientos.h ui_formcompararresultados.h ui_formcompararmnc.h ui_formincidenciai.h ui_formpreciosnohomogeneos.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: SMSAM.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_off.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/x86_64-linux-gnu/libQtGui.prl \
		/usr/lib/x86_64-linux-gnu/libQtCore.prl
	$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ -o Makefile SMSAM.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/warn_off.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/x86_64-linux-gnu/libQtGui.prl:
/usr/lib/x86_64-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ -o Makefile SMSAM.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/SMSAM1.0.0 || $(MKDIR) .tmp/SMSAM1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/SMSAM1.0.0/ && $(COPY_FILE) --parents mainwindow.H formloadmatrix.H formviewmatrix.H stackwidget.H accountwidget.H formvariablesexogenas.h stackvariablesexogenas.h variableexogenawidget.h formexportmatrix.h formencadenamientos.h stackencadenamientos.h encadenamientoswidget.h formcompararresultados.h formcompararmnc.h formincidenciai.h formpreciosnohomogeneos.h stackpreciosnohomogeneos.h variablepnh.h .tmp/SMSAM1.0.0/ && $(COPY_FILE) --parents img/img.qrc .tmp/SMSAM1.0.0/ && $(COPY_FILE) --parents mainwindow.C main.C formloadmatrix.C formviewmatrix.C stackwidget.C accountwidget.C formvariablesexogenas.cpp stackvariablesexogenas.cpp variableexogenawidget.cpp formexportmatrix.cpp formencadenamientos.cpp stackencadenamientos.cpp encadenamientoswidget.cpp formcompararresultados.cpp formcompararmnc.cpp formincidenciai.cpp formpreciosnohomogeneos.cpp stackpreciosnohomogeneos.cpp variablepnh.cpp .tmp/SMSAM1.0.0/ && $(COPY_FILE) --parents formLoadMatrix.ui formMatrixView.ui formvariablesexogenas.ui formexportmatrix.ui formencadenamientos.ui formcompararresultados.ui formcompararmnc.ui formincidenciai.ui formpreciosnohomogeneos.ui .tmp/SMSAM1.0.0/ && (cd `dirname .tmp/SMSAM1.0.0` && $(TAR) SMSAM1.0.0.tar SMSAM1.0.0 && $(COMPRESS) SMSAM1.0.0.tar) && $(MOVE) `dirname .tmp/SMSAM1.0.0`/SMSAM1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/SMSAM1.0.0


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

compiler_moc_header_make_all: moc_mainwindow.cpp moc_formloadmatrix.cpp moc_formviewmatrix.cpp moc_stackwidget.cpp moc_accountwidget.cpp moc_formvariablesexogenas.cpp moc_stackvariablesexogenas.cpp moc_variableexogenawidget.cpp moc_formexportmatrix.cpp moc_formencadenamientos.cpp moc_stackencadenamientos.cpp moc_encadenamientoswidget.cpp moc_formcompararresultados.cpp moc_formcompararmnc.cpp moc_formincidenciai.cpp moc_formpreciosnohomogeneos.cpp moc_stackpreciosnohomogeneos.cpp moc_variablepnh.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mainwindow.cpp moc_formloadmatrix.cpp moc_formviewmatrix.cpp moc_stackwidget.cpp moc_accountwidget.cpp moc_formvariablesexogenas.cpp moc_stackvariablesexogenas.cpp moc_variableexogenawidget.cpp moc_formexportmatrix.cpp moc_formencadenamientos.cpp moc_stackencadenamientos.cpp moc_encadenamientoswidget.cpp moc_formcompararresultados.cpp moc_formcompararmnc.cpp moc_formincidenciai.cpp moc_formpreciosnohomogeneos.cpp moc_stackpreciosnohomogeneos.cpp moc_variablepnh.cpp
moc_mainwindow.cpp: formloadmatrix.H \
		ui_formLoadMatrix.h \
		formviewmatrix.H \
		ui_formMatrixView.h \
		formvariablesexogenas.h \
		formexportmatrix.h \
		formencadenamientos.h \
		ui_formcompararresultados.h \
		formcompararresultados.h \
		ui_formcompararmnc.h \
		formcompararmnc.h \
		ui_formincidenciai.h \
		formincidenciai.h \
		formpreciosnohomogeneos.h \
		stackwidget.H \
		accountwidget.H \
		stackvariablesexogenas.h \
		variableexogenawidget.h \
		stackencadenamientos.h \
		encadenamientoswidget.h \
		stackpreciosnohomogeneos.h \
		variablepnh.h \
		mainwindow.H
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) mainwindow.H -o moc_mainwindow.cpp

moc_formloadmatrix.cpp: ui_formLoadMatrix.h \
		formloadmatrix.H
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) formloadmatrix.H -o moc_formloadmatrix.cpp

moc_formviewmatrix.cpp: ui_formMatrixView.h \
		formviewmatrix.H
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) formviewmatrix.H -o moc_formviewmatrix.cpp

moc_stackwidget.cpp: accountwidget.H \
		stackwidget.H
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) stackwidget.H -o moc_stackwidget.cpp

moc_accountwidget.cpp: accountwidget.H
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) accountwidget.H -o moc_accountwidget.cpp

moc_formvariablesexogenas.cpp: formvariablesexogenas.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) formvariablesexogenas.h -o moc_formvariablesexogenas.cpp

moc_stackvariablesexogenas.cpp: variableexogenawidget.h \
		stackvariablesexogenas.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) stackvariablesexogenas.h -o moc_stackvariablesexogenas.cpp

moc_variableexogenawidget.cpp: variableexogenawidget.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) variableexogenawidget.h -o moc_variableexogenawidget.cpp

moc_formexportmatrix.cpp: formexportmatrix.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) formexportmatrix.h -o moc_formexportmatrix.cpp

moc_formencadenamientos.cpp: formencadenamientos.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) formencadenamientos.h -o moc_formencadenamientos.cpp

moc_stackencadenamientos.cpp: encadenamientoswidget.h \
		stackencadenamientos.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) stackencadenamientos.h -o moc_stackencadenamientos.cpp

moc_encadenamientoswidget.cpp: encadenamientoswidget.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) encadenamientoswidget.h -o moc_encadenamientoswidget.cpp

moc_formcompararresultados.cpp: formcompararresultados.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) formcompararresultados.h -o moc_formcompararresultados.cpp

moc_formcompararmnc.cpp: formcompararmnc.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) formcompararmnc.h -o moc_formcompararmnc.cpp

moc_formincidenciai.cpp: formincidenciai.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) formincidenciai.h -o moc_formincidenciai.cpp

moc_formpreciosnohomogeneos.cpp: formpreciosnohomogeneos.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) formpreciosnohomogeneos.h -o moc_formpreciosnohomogeneos.cpp

moc_stackpreciosnohomogeneos.cpp: variablepnh.h \
		stackpreciosnohomogeneos.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) stackpreciosnohomogeneos.h -o moc_stackpreciosnohomogeneos.cpp

moc_variablepnh.cpp: variablepnh.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) variablepnh.h -o moc_variablepnh.cpp

compiler_rcc_make_all: qrc_img.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_img.cpp
qrc_img.cpp: img/img.qrc \
		img/estructura_matriz.jpg \
		img/logo_cenditel.jpg \
		img/img.qrc \
		img/undo-habilitado.png \
		img/edit-habilitado.png \
		img/Imagen-matriz.png \
		img/folder_blue.png \
		img/edit-deshabilitado.png
	/usr/bin/rcc -name img img/img.qrc -o qrc_img.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_formLoadMatrix.h ui_formMatrixView.h ui_formvariablesexogenas.h ui_formexportmatrix.h ui_formencadenamientos.h ui_formcompararresultados.h ui_formcompararmnc.h ui_formincidenciai.h ui_formpreciosnohomogeneos.h
compiler_uic_clean:
	-$(DEL_FILE) ui_formLoadMatrix.h ui_formMatrixView.h ui_formvariablesexogenas.h ui_formexportmatrix.h ui_formencadenamientos.h ui_formcompararresultados.h ui_formcompararmnc.h ui_formincidenciai.h ui_formpreciosnohomogeneos.h
ui_formLoadMatrix.h: formLoadMatrix.ui
	/usr/bin/uic-qt4 formLoadMatrix.ui -o ui_formLoadMatrix.h

ui_formMatrixView.h: formMatrixView.ui
	/usr/bin/uic-qt4 formMatrixView.ui -o ui_formMatrixView.h

ui_formvariablesexogenas.h: formvariablesexogenas.ui
	/usr/bin/uic-qt4 formvariablesexogenas.ui -o ui_formvariablesexogenas.h

ui_formexportmatrix.h: formexportmatrix.ui
	/usr/bin/uic-qt4 formexportmatrix.ui -o ui_formexportmatrix.h

ui_formencadenamientos.h: formencadenamientos.ui
	/usr/bin/uic-qt4 formencadenamientos.ui -o ui_formencadenamientos.h

ui_formcompararresultados.h: formcompararresultados.ui
	/usr/bin/uic-qt4 formcompararresultados.ui -o ui_formcompararresultados.h

ui_formcompararmnc.h: formcompararmnc.ui
	/usr/bin/uic-qt4 formcompararmnc.ui -o ui_formcompararmnc.h

ui_formincidenciai.h: formincidenciai.ui
	/usr/bin/uic-qt4 formincidenciai.ui -o ui_formincidenciai.h

ui_formpreciosnohomogeneos.h: formpreciosnohomogeneos.ui
	/usr/bin/uic-qt4 formpreciosnohomogeneos.ui -o ui_formpreciosnohomogeneos.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean compiler_uic_clean 

####### Compile

mainwindow.o: mainwindow.C mainwindow.H \
		formloadmatrix.H \
		ui_formLoadMatrix.h \
		formviewmatrix.H \
		ui_formMatrixView.h \
		formvariablesexogenas.h \
		formexportmatrix.h \
		formencadenamientos.h \
		ui_formcompararresultados.h \
		formcompararresultados.h \
		ui_formcompararmnc.h \
		formcompararmnc.h \
		ui_formincidenciai.h \
		formincidenciai.h \
		formpreciosnohomogeneos.h \
		stackwidget.H \
		accountwidget.H \
		stackvariablesexogenas.h \
		variableexogenawidget.h \
		stackencadenamientos.h \
		encadenamientoswidget.h \
		stackpreciosnohomogeneos.h \
		variablepnh.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o mainwindow.C

main.o: main.C mainwindow.H \
		formloadmatrix.H \
		ui_formLoadMatrix.h \
		formviewmatrix.H \
		ui_formMatrixView.h \
		formvariablesexogenas.h \
		formexportmatrix.h \
		formencadenamientos.h \
		ui_formcompararresultados.h \
		formcompararresultados.h \
		ui_formcompararmnc.h \
		formcompararmnc.h \
		ui_formincidenciai.h \
		formincidenciai.h \
		formpreciosnohomogeneos.h \
		stackwidget.H \
		accountwidget.H \
		stackvariablesexogenas.h \
		variableexogenawidget.h \
		stackencadenamientos.h \
		encadenamientoswidget.h \
		stackpreciosnohomogeneos.h \
		variablepnh.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.C

formloadmatrix.o: formloadmatrix.C formloadmatrix.H \
		ui_formLoadMatrix.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o formloadmatrix.o formloadmatrix.C

formviewmatrix.o: formviewmatrix.C formviewmatrix.H \
		ui_formMatrixView.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o formviewmatrix.o formviewmatrix.C

stackwidget.o: stackwidget.C stackwidget.H \
		accountwidget.H
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o stackwidget.o stackwidget.C

accountwidget.o: accountwidget.C accountwidget.H
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o accountwidget.o accountwidget.C

formvariablesexogenas.o: formvariablesexogenas.cpp formvariablesexogenas.h \
		ui_formvariablesexogenas.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o formvariablesexogenas.o formvariablesexogenas.cpp

stackvariablesexogenas.o: stackvariablesexogenas.cpp stackvariablesexogenas.h \
		variableexogenawidget.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o stackvariablesexogenas.o stackvariablesexogenas.cpp

variableexogenawidget.o: variableexogenawidget.cpp variableexogenawidget.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o variableexogenawidget.o variableexogenawidget.cpp

formexportmatrix.o: formexportmatrix.cpp formexportmatrix.h \
		ui_formexportmatrix.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o formexportmatrix.o formexportmatrix.cpp

formencadenamientos.o: formencadenamientos.cpp formencadenamientos.h \
		ui_formencadenamientos.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o formencadenamientos.o formencadenamientos.cpp

stackencadenamientos.o: stackencadenamientos.cpp stackencadenamientos.h \
		encadenamientoswidget.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o stackencadenamientos.o stackencadenamientos.cpp

encadenamientoswidget.o: encadenamientoswidget.cpp encadenamientoswidget.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o encadenamientoswidget.o encadenamientoswidget.cpp

formcompararresultados.o: formcompararresultados.cpp formcompararresultados.h \
		ui_formcompararresultados.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o formcompararresultados.o formcompararresultados.cpp

formcompararmnc.o: formcompararmnc.cpp formcompararmnc.h \
		ui_formcompararmnc.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o formcompararmnc.o formcompararmnc.cpp

formincidenciai.o: formincidenciai.cpp formincidenciai.h \
		ui_formincidenciai.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o formincidenciai.o formincidenciai.cpp

formpreciosnohomogeneos.o: formpreciosnohomogeneos.cpp formpreciosnohomogeneos.h \
		ui_formpreciosnohomogeneos.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o formpreciosnohomogeneos.o formpreciosnohomogeneos.cpp

stackpreciosnohomogeneos.o: stackpreciosnohomogeneos.cpp stackpreciosnohomogeneos.h \
		variablepnh.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o stackpreciosnohomogeneos.o stackpreciosnohomogeneos.cpp

variablepnh.o: variablepnh.cpp variablepnh.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o variablepnh.o variablepnh.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

moc_formloadmatrix.o: moc_formloadmatrix.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_formloadmatrix.o moc_formloadmatrix.cpp

moc_formviewmatrix.o: moc_formviewmatrix.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_formviewmatrix.o moc_formviewmatrix.cpp

moc_stackwidget.o: moc_stackwidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_stackwidget.o moc_stackwidget.cpp

moc_accountwidget.o: moc_accountwidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_accountwidget.o moc_accountwidget.cpp

moc_formvariablesexogenas.o: moc_formvariablesexogenas.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_formvariablesexogenas.o moc_formvariablesexogenas.cpp

moc_stackvariablesexogenas.o: moc_stackvariablesexogenas.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_stackvariablesexogenas.o moc_stackvariablesexogenas.cpp

moc_variableexogenawidget.o: moc_variableexogenawidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_variableexogenawidget.o moc_variableexogenawidget.cpp

moc_formexportmatrix.o: moc_formexportmatrix.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_formexportmatrix.o moc_formexportmatrix.cpp

moc_formencadenamientos.o: moc_formencadenamientos.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_formencadenamientos.o moc_formencadenamientos.cpp

moc_stackencadenamientos.o: moc_stackencadenamientos.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_stackencadenamientos.o moc_stackencadenamientos.cpp

moc_encadenamientoswidget.o: moc_encadenamientoswidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_encadenamientoswidget.o moc_encadenamientoswidget.cpp

moc_formcompararresultados.o: moc_formcompararresultados.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_formcompararresultados.o moc_formcompararresultados.cpp

moc_formcompararmnc.o: moc_formcompararmnc.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_formcompararmnc.o moc_formcompararmnc.cpp

moc_formincidenciai.o: moc_formincidenciai.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_formincidenciai.o moc_formincidenciai.cpp

moc_formpreciosnohomogeneos.o: moc_formpreciosnohomogeneos.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_formpreciosnohomogeneos.o moc_formpreciosnohomogeneos.cpp

moc_stackpreciosnohomogeneos.o: moc_stackpreciosnohomogeneos.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_stackpreciosnohomogeneos.o moc_stackpreciosnohomogeneos.cpp

moc_variablepnh.o: moc_variablepnh.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_variablepnh.o moc_variablepnh.cpp

qrc_img.o: qrc_img.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_img.o qrc_img.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:


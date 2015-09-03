HEADERS += mainwindow.H \
    formloadmatrix.H \
    formviewmatrix.H \
    stackwidget.H \
    accountwidget.H \
    formvariablesexogenas.h \
    stackvariablesexogenas.h \
    variableexogenawidget.h \
    formexportmatrix.h \
    formencadenamientos.h \
    stackencadenamientos.h \
    encadenamientoswidget.h \
    formcompararresultados.h

SOURCES += mainwindow.C \
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
    formcompararresultados.cpp
FORMS += formLoadMatrix.ui \
    formMatrixView.ui \
    formvariablesexogenas.ui \
    formexportmatrix.ui \
    formencadenamientos.ui \
    formcompararresultados.ui

INCLUDEPATH += $$PWD/Eigen


CONFIG += warn_off

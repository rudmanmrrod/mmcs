HEADERS += mainwindow.H \
    formloadmatrix.H \
    formviewmatrix.H \
    stackwidget.H \
    accountwidget.H \
    formvariablesexogenas.h \
    stackvariablesexogenas.h \
    variableexogenawidget.h \
    formexportmatrix.h

SOURCES += mainwindow.C \
    main.C \
    formloadmatrix.C \
    formviewmatrix.C \
    stackwidget.C \
    accountwidget.C \
    formvariablesexogenas.cpp \
    stackvariablesexogenas.cpp \
    variableexogenawidget.cpp \
    formexportmatrix.cpp
FORMS += formLoadMatrix.ui \
    formMatrixView.ui \
    formvariablesexogenas.ui \
    formexportmatrix.ui

INCLUDEPATH += $$PWD/armadillo_bits

LIBS += -L -larmadillo \
        -llapack

CONFIG += warn_off

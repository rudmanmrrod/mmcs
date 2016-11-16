QT += widgets \
    printsupport

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
    formcompararresultados.h \
    formcompararmnc.h \
    formincidenciai.h \
    formpreciosnohomogeneos.h \
    stackpreciosnohomogeneos.h \
    variablepnh.h \
    genericFunctions.h \
    formexportreport.h \
    qcustomplot.h \
    formdescomposicion.h \
    formcargando.h \
    formcortoplazo.h

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
    formcompararresultados.cpp \
    formcompararmnc.cpp \
    formincidenciai.cpp \
    formpreciosnohomogeneos.cpp \
    stackpreciosnohomogeneos.cpp \
    variablepnh.cpp \
    genericFunctions.cpp \
    formexportreport.cpp \
    qcustomplot.cpp \
    formdescomposicion.cpp \
    formcargando.cpp \
    formcortoplazo.cpp
FORMS += formLoadMatrix.ui \
    formvariablesexogenas.ui \
    formexportmatrix.ui \
    formencadenamientos.ui \
    formcompararresultados.ui \
    formcompararmnc.ui \
    formincidenciai.ui \
    formpreciosnohomogeneos.ui \
    formexportreport.ui \
    formViewMatrix.ui \
    formdescomposicion.ui \
    formcargando.ui \
    formcortoplazo.ui

INCLUDEPATH += $$PWD/Eigen


CONFIG += warn_off

RESOURCES += \
    img/images.qrc

OTHER_FILES +=

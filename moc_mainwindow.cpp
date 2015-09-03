/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.H'
**
** Created: Thu Sep 3 14:39:54 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.H"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.H' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      29,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      29,   11,   11,   11, 0x08,
      51,   48,   11,   11, 0x08,
      96,   11,   11,   11, 0x08,
     123,   11,   11,   11, 0x08,
     139,   11,   11,   11, 0x08,
     157,   11,   11,   11, 0x08,
     176,   11,   11,   11, 0x08,
     194,   11,   11,   11, 0x08,
     222,   11,   11,   11, 0x08,
     248,   11,   11,   11, 0x08,
     270,   11,   11,   11, 0x08,
     289,   11,   11,   11, 0x08,
     310,   11,   11,   11, 0x08,
     333,   11,   11,   11, 0x08,
     355,   11,   11,   11, 0x08,
     373,   11,   11,   11, 0x08,
     382,   11,   11,   11, 0x08,
     404,   11,   11,   11, 0x08,
     430,   11,   11,   11, 0x08,
     458,   11,   11,   11, 0x08,
     482,   11,   11,   11, 0x08,
     500,   11,   11,   11, 0x08,
     517,   11,   11,   11, 0x08,
     536,   11,   11,   11, 0x08,
     556,   11,   11,   11, 0x08,
     576,   11,   11,   11, 0x08,
     597,   11,   11,   11, 0x08,
     622,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0slotLoadMatrix()\0"
    "slotExportMatrix()\0,,\0"
    "slotFormLoadMatrixAccepted(QString,int,char)\0"
    "slotFormLoadMatrixClosed()\0AgregarCuenta()\0"
    "RestaurarCeldas()\0FinalizarCuentas()\0"
    "ModificarCuenta()\0slotCoeficienteHorizontal()\0"
    "slotCoeficienteVertical()\0"
    "slotVariableExogena()\0slotCloseExogena()\0"
    "slotAgregarExogena()\0slotFinalizarExogena()\0"
    "slotDeshacerExogena()\0slotCTVEndogena()\0"
    "slotMa()\0slotEncadenamientos()\0"
    "slotCloseEncadenamiento()\0"
    "slotAgregarEncadenamiento()\0"
    "slotVerEncadenamiento()\0slotCloseExport()\0"
    "slotSaveExport()\0slotSearchExport()\0"
    "slotModeloClasico()\0calcularEscenario()\0"
    "finalizarEscenario()\0slotCompararResultados()\0"
    "slotVerResultado()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->slotLoadMatrix(); break;
        case 1: _t->slotExportMatrix(); break;
        case 2: _t->slotFormLoadMatrixAccepted((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< char(*)>(_a[3]))); break;
        case 3: _t->slotFormLoadMatrixClosed(); break;
        case 4: _t->AgregarCuenta(); break;
        case 5: _t->RestaurarCeldas(); break;
        case 6: _t->FinalizarCuentas(); break;
        case 7: _t->ModificarCuenta(); break;
        case 8: _t->slotCoeficienteHorizontal(); break;
        case 9: _t->slotCoeficienteVertical(); break;
        case 10: _t->slotVariableExogena(); break;
        case 11: _t->slotCloseExogena(); break;
        case 12: _t->slotAgregarExogena(); break;
        case 13: _t->slotFinalizarExogena(); break;
        case 14: _t->slotDeshacerExogena(); break;
        case 15: _t->slotCTVEndogena(); break;
        case 16: _t->slotMa(); break;
        case 17: _t->slotEncadenamientos(); break;
        case 18: _t->slotCloseEncadenamiento(); break;
        case 19: _t->slotAgregarEncadenamiento(); break;
        case 20: _t->slotVerEncadenamiento(); break;
        case 21: _t->slotCloseExport(); break;
        case 22: _t->slotSaveExport(); break;
        case 23: _t->slotSearchExport(); break;
        case 24: _t->slotModeloClasico(); break;
        case 25: _t->calcularEscenario(); break;
        case 26: _t->finalizarEscenario(); break;
        case 27: _t->slotCompararResultados(); break;
        case 28: _t->slotVerResultado(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 29)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 29;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

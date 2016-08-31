/****************************************************************************
** Meta object code from reading C++ file 'formloadmatrix.H'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "formloadmatrix.H"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'formloadmatrix.H' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FormLoadMatrix_t {
    QByteArrayData data[6];
    char stringdata[83];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FormLoadMatrix_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FormLoadMatrix_t qt_meta_stringdata_FormLoadMatrix = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 12),
QT_MOC_LITERAL(2, 28, 0),
QT_MOC_LITERAL(3, 29, 10),
QT_MOC_LITERAL(4, 40, 18),
QT_MOC_LITERAL(5, 59, 23)
    },
    "FormLoadMatrix\0formAccepted\0\0formClosed\0"
    "slotLoadMatrixFile\0slotButtonAcceptClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FormLoadMatrix[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   34,    2, 0x06 /* Public */,
       3,    0,   41,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   42,    2, 0x0a /* Public */,
       5,    0,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Int,    2,    2,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void FormLoadMatrix::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FormLoadMatrix *_t = static_cast<FormLoadMatrix *>(_o);
        switch (_id) {
        case 0: _t->formAccepted((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->formClosed(); break;
        case 2: _t->slotLoadMatrixFile(); break;
        case 3: _t->slotButtonAcceptClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FormLoadMatrix::*_t)(const QString & , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FormLoadMatrix::formAccepted)) {
                *result = 0;
            }
        }
        {
            typedef void (FormLoadMatrix::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FormLoadMatrix::formClosed)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject FormLoadMatrix::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_FormLoadMatrix.data,
      qt_meta_data_FormLoadMatrix,  qt_static_metacall, 0, 0}
};


const QMetaObject *FormLoadMatrix::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FormLoadMatrix::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FormLoadMatrix.stringdata))
        return static_cast<void*>(const_cast< FormLoadMatrix*>(this));
    return QWidget::qt_metacast(_clname);
}

int FormLoadMatrix::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void FormLoadMatrix::formAccepted(const QString & _t1, int _t2, int _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FormLoadMatrix::formClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE

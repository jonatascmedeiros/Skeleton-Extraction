/****************************************************************************
** Meta object code from reading C++ file 'TriangleWidget.h'
**
** Created: Sat Oct 30 19:18:48 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../TriangleWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TriangleWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TriangleWidget[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      25,   16,   15,   15, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_TriangleWidget[] = {
    "TriangleWidget\0\0w1,w2,w3\0"
    "setBarycentricCoords(float,float,float)\0"
};

const QMetaObject TriangleWidget::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_TriangleWidget,
      qt_meta_data_TriangleWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TriangleWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TriangleWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TriangleWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TriangleWidget))
        return static_cast<void*>(const_cast< TriangleWidget*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int TriangleWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setBarycentricCoords((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void TriangleWidget::setBarycentricCoords(float _t1, float _t2, float _t3)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE

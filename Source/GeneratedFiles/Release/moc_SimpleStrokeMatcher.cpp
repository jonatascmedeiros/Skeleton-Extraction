/****************************************************************************
** Meta object code from reading C++ file 'SimpleStrokeMatcher.h'
**
** Created: Tue Oct 19 18:45:53 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SimpleStrokeMatcher.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SimpleStrokeMatcher.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SimpleStrokeMatcher[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   20,   20,   20, 0x09,
      32,   20,   20,   20, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_SimpleStrokeMatcher[] = {
    "SimpleStrokeMatcher\0\0textMode()\0"
    "patternMode()\0"
};

const QMetaObject SimpleStrokeMatcher::staticMetaObject = {
    { &Renderer::staticMetaObject, qt_meta_stringdata_SimpleStrokeMatcher,
      qt_meta_data_SimpleStrokeMatcher, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SimpleStrokeMatcher::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SimpleStrokeMatcher::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SimpleStrokeMatcher::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SimpleStrokeMatcher))
        return static_cast<void*>(const_cast< SimpleStrokeMatcher*>(this));
    return Renderer::qt_metacast(_clname);
}

int SimpleStrokeMatcher::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Renderer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: textMode(); break;
        case 1: patternMode(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

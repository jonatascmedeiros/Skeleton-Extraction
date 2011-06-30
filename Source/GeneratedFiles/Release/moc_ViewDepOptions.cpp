/****************************************************************************
** Meta object code from reading C++ file 'ViewDepOptions.h'
**
** Created: Mon Nov 1 17:36:53 2010
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ViewDepOptions.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ViewDepOptions.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ViewDepDialog[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   15,   14,   14, 0x08,
      52,   15,   14,   14, 0x08,
      87,   15,   14,   14, 0x08,
     118,   15,   14,   14, 0x08,
     153,   14,   14,   14, 0x08,
     169,   15,   14,   14, 0x08,
     201,   14,   14,   14, 0x08,
     217,   15,   14,   14, 0x08,
     248,   15,   14,   14, 0x08,
     283,   14,   14,   14, 0x08,
     299,   15,   14,   14, 0x08,
     330,   15,   14,   14, 0x08,
     365,   14,   14,   14, 0x08,
     381,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ViewDepDialog[] = {
    "ViewDepDialog\0\0value\0"
    "silOpsThetaPSliderChanged(int)\0"
    "silOpsThetaPSpinBoxChanged(double)\0"
    "silOpsThetaNSliderChanged(int)\0"
    "silOpsThetaNSpinBoxChanged(double)\0"
    "defaultSilOps()\0hndOpsBalanceSliderChanged(int)\0"
    "defaultHndOps()\0roiOpsScalerSliderChanged(int)\0"
    "roiOpsScalerSpinBoxChanged(double)\0"
    "defaultROIOps()\0lseOpsHandleSliderChanged(int)\0"
    "lseOpsHandleSpinBoxChanged(double)\0"
    "defaultLSEOps()\0redo()\0"
};

const QMetaObject ViewDepDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ViewDepDialog,
      qt_meta_data_ViewDepDialog, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ViewDepDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ViewDepDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ViewDepDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ViewDepDialog))
        return static_cast<void*>(const_cast< ViewDepDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ViewDepDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: silOpsThetaPSliderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: silOpsThetaPSpinBoxChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: silOpsThetaNSliderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: silOpsThetaNSpinBoxChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 4: defaultSilOps(); break;
        case 5: hndOpsBalanceSliderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: defaultHndOps(); break;
        case 7: roiOpsScalerSliderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: roiOpsScalerSpinBoxChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: defaultROIOps(); break;
        case 10: lseOpsHandleSliderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: lseOpsHandleSpinBoxChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: defaultLSEOps(); break;
        case 13: redo(); break;
        default: ;
        }
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

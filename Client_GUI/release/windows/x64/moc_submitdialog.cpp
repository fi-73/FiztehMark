/****************************************************************************
** Meta object code from reading C++ file 'submitdialog.h'
**
** Created: Mon 2. Apr 00:33:41 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../FiztehMark/submitdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'submitdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SubmitDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x05,
      25,   13,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      37,   13,   13,   13, 0x08,
      69,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_SubmitDialog[] = {
    "SubmitDialog\0\0canceled()\0confirmed()\0"
    "on_cancelSubmitButton_clicked()\0"
    "on_confirmSubmitButton_clicked()\0"
};

void SubmitDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SubmitDialog *_t = static_cast<SubmitDialog *>(_o);
        switch (_id) {
        case 0: _t->canceled(); break;
        case 1: _t->confirmed(); break;
        case 2: _t->on_cancelSubmitButton_clicked(); break;
        case 3: _t->on_confirmSubmitButton_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData SubmitDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SubmitDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SubmitDialog,
      qt_meta_data_SubmitDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SubmitDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SubmitDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SubmitDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SubmitDialog))
        return static_cast<void*>(const_cast< SubmitDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int SubmitDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void SubmitDialog::canceled()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void SubmitDialog::confirmed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE

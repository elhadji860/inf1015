/****************************************************************************
** Meta object code from reading C++ file 'Caisse.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Caisse.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Caisse.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Caisse_t {
    QByteArrayData data[10];
    char stringdata0[106];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Caisse_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Caisse_t qt_meta_stringdata_Caisse = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Caisse"
QT_MOC_LITERAL(1, 7, 13), // "articleAjoute"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 13), // "articleRetire"
QT_MOC_LITERAL(4, 36, 14), // "ajouterArticle"
QT_MOC_LITERAL(5, 51, 7), // "Article"
QT_MOC_LITERAL(6, 59, 7), // "article"
QT_MOC_LITERAL(7, 67, 14), // "retirerArticle"
QT_MOC_LITERAL(8, 82, 11), // "std::string"
QT_MOC_LITERAL(9, 94, 11) // "description"

    },
    "Caisse\0articleAjoute\0\0articleRetire\0"
    "ajouterArticle\0Article\0article\0"
    "retirerArticle\0std::string\0description"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Caisse[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   36,    2, 0x0a /* Public */,
       7,    1,   39,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 8,    9,

       0        // eod
};

void Caisse::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Caisse *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->articleAjoute(); break;
        case 1: _t->articleRetire(); break;
        case 2: _t->ajouterArticle((*reinterpret_cast< Article(*)>(_a[1]))); break;
        case 3: _t->retirerArticle((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Caisse::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Caisse::articleAjoute)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Caisse::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Caisse::articleRetire)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Caisse::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_Caisse.data,
    qt_meta_data_Caisse,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Caisse::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Caisse::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Caisse.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Caisse::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void Caisse::articleAjoute()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Caisse::articleRetire()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

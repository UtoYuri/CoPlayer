/****************************************************************************
** Meta object code from reading C++ file 'videowidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../player/videowidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'videowidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_VideoWidget_t {
    QByteArrayData data[22];
    char stringdata0[225];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VideoWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VideoWidget_t qt_meta_stringdata_VideoWidget = {
    {
QT_MOC_LITERAL(0, 0, 11), // "VideoWidget"
QT_MOC_LITERAL(1, 12, 4), // "play"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 17), // "fullScreenToggled"
QT_MOC_LITERAL(4, 36, 10), // "fullScreen"
QT_MOC_LITERAL(5, 47, 11), // "fastForward"
QT_MOC_LITERAL(6, 59, 6), // "rewind"
QT_MOC_LITERAL(7, 66, 15), // "positionChanged"
QT_MOC_LITERAL(8, 82, 3), // "pos"
QT_MOC_LITERAL(9, 86, 13), // "volumeChanged"
QT_MOC_LITERAL(10, 100, 9), // "increment"
QT_MOC_LITERAL(11, 110, 12), // "playNewMedia"
QT_MOC_LITERAL(12, 123, 5), // "files"
QT_MOC_LITERAL(13, 129, 8), // "openFile"
QT_MOC_LITERAL(14, 138, 10), // "showButton"
QT_MOC_LITERAL(15, 149, 10), // "hideButton"
QT_MOC_LITERAL(16, 160, 11), // "removeMedia"
QT_MOC_LITERAL(17, 172, 8), // "addMedia"
QT_MOC_LITERAL(18, 181, 8), // "fileName"
QT_MOC_LITERAL(19, 190, 16), // "toggleListWidget"
QT_MOC_LITERAL(20, 207, 4), // "show"
QT_MOC_LITERAL(21, 212, 12) // "adjustWidget"

    },
    "VideoWidget\0play\0\0fullScreenToggled\0"
    "fullScreen\0fastForward\0rewind\0"
    "positionChanged\0pos\0volumeChanged\0"
    "increment\0playNewMedia\0files\0openFile\0"
    "showButton\0hideButton\0removeMedia\0"
    "addMedia\0fileName\0toggleListWidget\0"
    "show\0adjustWidget"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VideoWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x06 /* Public */,
       3,    1,   85,    2, 0x06 /* Public */,
       5,    0,   88,    2, 0x06 /* Public */,
       6,    0,   89,    2, 0x06 /* Public */,
       7,    1,   90,    2, 0x06 /* Public */,
       9,    1,   93,    2, 0x06 /* Public */,
      11,    1,   96,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    0,   99,    2, 0x0a /* Public */,
      14,    0,  100,    2, 0x0a /* Public */,
      15,    0,  101,    2, 0x0a /* Public */,
      16,    0,  102,    2, 0x0a /* Public */,
      17,    1,  103,    2, 0x0a /* Public */,
      19,    1,  106,    2, 0x0a /* Public */,
      21,    0,  109,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong,    8,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::QStringList,   12,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::Void, QMetaType::Bool,   20,
    QMetaType::Void,

       0        // eod
};

void VideoWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VideoWidget *_t = static_cast<VideoWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->play(); break;
        case 1: _t->fullScreenToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->fastForward(); break;
        case 3: _t->rewind(); break;
        case 4: _t->positionChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 5: _t->volumeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->playNewMedia((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 7: _t->openFile(); break;
        case 8: _t->showButton(); break;
        case 9: _t->hideButton(); break;
        case 10: _t->removeMedia(); break;
        case 11: _t->addMedia((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->toggleListWidget((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->adjustWidget(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (VideoWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VideoWidget::play)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (VideoWidget::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VideoWidget::fullScreenToggled)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (VideoWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VideoWidget::fastForward)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (VideoWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VideoWidget::rewind)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (VideoWidget::*_t)(qint64 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VideoWidget::positionChanged)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (VideoWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VideoWidget::volumeChanged)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (VideoWidget::*_t)(QStringList );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VideoWidget::playNewMedia)) {
                *result = 6;
                return;
            }
        }
    }
}

const QMetaObject VideoWidget::staticMetaObject = {
    { &QVideoWidget::staticMetaObject, qt_meta_stringdata_VideoWidget.data,
      qt_meta_data_VideoWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *VideoWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VideoWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_VideoWidget.stringdata0))
        return static_cast<void*>(const_cast< VideoWidget*>(this));
    return QVideoWidget::qt_metacast(_clname);
}

int VideoWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QVideoWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void VideoWidget::play()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void VideoWidget::fullScreenToggled(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void VideoWidget::fastForward()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void VideoWidget::rewind()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void VideoWidget::positionChanged(qint64 _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void VideoWidget::volumeChanged(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void VideoWidget::playNewMedia(QStringList _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE

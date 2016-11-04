/****************************************************************************
** Meta object code from reading C++ file 'videocontroller.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../player/videocontroller.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'videocontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_VideoController_t {
    QByteArrayData data[19];
    char stringdata0[208];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VideoController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VideoController_t qt_meta_stringdata_VideoController = {
    {
QT_MOC_LITERAL(0, 0, 15), // "VideoController"
QT_MOC_LITERAL(1, 16, 4), // "play"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 11), // "muteChanged"
QT_MOC_LITERAL(4, 34, 5), // "muted"
QT_MOC_LITERAL(5, 40, 13), // "volumeChanged"
QT_MOC_LITERAL(6, 54, 6), // "volume"
QT_MOC_LITERAL(7, 61, 17), // "fullScreenToggled"
QT_MOC_LITERAL(8, 79, 10), // "fullScreen"
QT_MOC_LITERAL(9, 90, 15), // "positionChanged"
QT_MOC_LITERAL(10, 106, 7), // "percent"
QT_MOC_LITERAL(11, 114, 17), // "listWidgetToggled"
QT_MOC_LITERAL(12, 132, 4), // "show"
QT_MOC_LITERAL(13, 137, 15), // "setIsFullScreen"
QT_MOC_LITERAL(14, 153, 12), // "isFullScreen"
QT_MOC_LITERAL(15, 166, 12), // "setIsPlaying"
QT_MOC_LITERAL(16, 179, 9), // "isPlaying"
QT_MOC_LITERAL(17, 189, 10), // "setIsMuted"
QT_MOC_LITERAL(18, 200, 7) // "isMuted"

    },
    "VideoController\0play\0\0muteChanged\0"
    "muted\0volumeChanged\0volume\0fullScreenToggled\0"
    "fullScreen\0positionChanged\0percent\0"
    "listWidgetToggled\0show\0setIsFullScreen\0"
    "isFullScreen\0setIsPlaying\0isPlaying\0"
    "setIsMuted\0isMuted"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VideoController[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       3,    1,   62,    2, 0x06 /* Public */,
       5,    1,   65,    2, 0x06 /* Public */,
       7,    1,   68,    2, 0x06 /* Public */,
       9,    1,   71,    2, 0x06 /* Public */,
      11,    1,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    1,   77,    2, 0x0a /* Public */,
      15,    1,   80,    2, 0x0a /* Public */,
      17,    1,   83,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    1,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Float,   10,
    QMetaType::Void, QMetaType::Bool,   12,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void, QMetaType::Bool,   16,
    QMetaType::Void, QMetaType::Bool,   18,

       0        // eod
};

void VideoController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VideoController *_t = static_cast<VideoController *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->play((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->muteChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->volumeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->fullScreenToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->positionChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 5: _t->listWidgetToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->setIsFullScreen((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->setIsPlaying((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->setIsMuted((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (VideoController::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VideoController::play)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (VideoController::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VideoController::muteChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (VideoController::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VideoController::volumeChanged)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (VideoController::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VideoController::fullScreenToggled)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (VideoController::*_t)(float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VideoController::positionChanged)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (VideoController::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VideoController::listWidgetToggled)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject VideoController::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_VideoController.data,
      qt_meta_data_VideoController,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *VideoController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VideoController::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_VideoController.stringdata0))
        return static_cast<void*>(const_cast< VideoController*>(this));
    return QWidget::qt_metacast(_clname);
}

int VideoController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void VideoController::play(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VideoController::muteChanged(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void VideoController::volumeChanged(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void VideoController::fullScreenToggled(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void VideoController::positionChanged(float _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void VideoController::listWidgetToggled(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE

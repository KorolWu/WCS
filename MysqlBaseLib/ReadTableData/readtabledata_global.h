#ifndef READTABLEDATA_GLOBAL_H
#define READTABLEDATA_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(READTABLEDATA_LIBRARY)
#  define READTABLEDATASHARED_EXPORT Q_DECL_EXPORT
#else
#  define READTABLEDATASHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // READTABLEDATA_GLOBAL_H

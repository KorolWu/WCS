#ifndef CRUDBASEOPERATION_GLOBAL_H
#define CRUDBASEOPERATION_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CRUDBASEOPERATION_LIBRARY)
#  define CRUDBASEOPERATIONSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CRUDBASEOPERATIONSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CRUDBASEOPERATION_GLOBAL_H
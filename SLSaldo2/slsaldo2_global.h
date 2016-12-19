#ifndef SLSALDO2_GLOBAL_H
#define SLSALDO2_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SLSALDO2_LIBRARY)
#  define SLSALDO2SHARED_EXPORT Q_DECL_EXPORT
#else
#  define SLSALDO2SHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SLSALDO2_GLOBAL_H
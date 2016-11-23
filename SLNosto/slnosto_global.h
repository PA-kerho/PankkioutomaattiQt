#ifndef SLNOSTO_GLOBAL_H
#define SLNOSTO_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SLNOSTO_LIBRARY)
#  define SLNOSTOSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SLNOSTOSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SLNOSTO_GLOBAL_H

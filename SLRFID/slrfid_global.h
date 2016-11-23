#ifndef SLRFID_GLOBAL_H
#define SLRFID_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SLRFID_LIBRARY)
#  define SLRFIDSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SLRFIDSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SLRFID_GLOBAL_H

#ifndef SLSQL_GLOBAL_H
#define SLSQL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SLSQL_LIBRARY)
#  define SLSQLSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SLSQLSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SLSQL_GLOBAL_H

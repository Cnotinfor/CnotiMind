#ifndef CNOTIMIND_GLOBAL_H
#define CNOTIMIND_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef CNOTIMIND_LIB
# define CNOTIMIND_EXPORT Q_DECL_EXPORT
#else
# define CNOTIMIND_EXPORT Q_DECL_IMPORT
#endif

#endif // CNOTIMIND_GLOBAL_H

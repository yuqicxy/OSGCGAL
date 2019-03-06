#pragma once
#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(NODEOBJECTINSPECTOR_LIB)
#  define NODEOBJECTINSPECTOR_EXPORT Q_DECL_EXPORT
# else
#  define NODEOBJECTINSPECTOR_EXPORT Q_DECL_IMPORT
# endif
#else
# define NODEOBJECTINSPECTOR_EXPORT
#endif

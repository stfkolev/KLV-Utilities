#ifndef KLV_CONFIG__
#define KLV_CONFIG__

#ifdef __GNUC__
#   define KLV_GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#endif

#ifdef __clang_major__
#   define KLV_CLANG_VERSION (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
#endif

#if defined __GNUC__
#   if defined __clang_major__
#       if KLV_CLANG_VERSION < 30400
#           error KLV++ requires clang compiler of version 3.4.0 or above.
#       endif
#   else
#       if KLV_GCC_VERSION < 40801
#           error KLV++ requires gcc of version 4.8.1 or above.
#       endif
#   endif
#endif

#endif

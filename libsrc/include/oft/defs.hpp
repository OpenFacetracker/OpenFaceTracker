
#ifndef OFT_EXPORT_H
#define OFT_EXPORT_H

#ifdef OFT_STATIC_DEFINE
#  define OFT_EXPORT
#  define OFT_NO_EXPORT
#else
#  ifndef OFT_EXPORT
#    ifdef oft_EXPORTS
        /* We are building this library */
#      define OFT_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define OFT_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef OFT_NO_EXPORT
#    define OFT_NO_EXPORT 
#  endif
#endif

#ifndef OFT_DEPRECATED
#  define OFT_DEPRECATED 
#endif

#ifndef OFT_DEPRECATED_EXPORT
#  define OFT_DEPRECATED_EXPORT OFT_EXPORT OFT_DEPRECATED
#endif

#ifndef OFT_DEPRECATED_NO_EXPORT
#  define OFT_DEPRECATED_NO_EXPORT OFT_NO_EXPORT OFT_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef OFT_NO_DEPRECATED
#    define OFT_NO_DEPRECATED
#  endif
#endif

#endif /* OFT_EXPORT_H */

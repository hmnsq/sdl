#अगर_अघोषित __khrplatform_h_
#घोषणा __khrplatform_h_

/*
** Copyright (c) 2008-2018 The Khronos Group Inc.
**
** Permission is hereby granted, free of charge, to any person obtaining a
** copy of this software and/or associated documentation files (the
** "Materials"), to deal in the Materials without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Materials, and to
** permit persons to whom the Materials are furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be included
** in all copies or substantial portions of the Materials.
**
** THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
** CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
** TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
** MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
*/

/* Khronos platform-specific types and definitions.
 *
 * The master copy of khrplatform.h is maintained in the Khronos EGL
 * Registry repository at https://github.com/KhronosGroup/EGL-Registry
 * The last semantic modification to khrplatform.h was at commit ID:
 *      67a3e0864c2d75ea5287b9f3d2eb74a745936692
 *
 * Adopters may modify this file to suit their platform. Adopters are
 * encouraged to submit platform specific modifications to the Khronos
 * group so that they can be included in future versions of this file.
 * Please submit changes by filing pull requests or issues on
 * the EGL Registry repository linked above.
 *
 *
 * See the Implementer's Guidelines for information about where this file
 * should be located on your system and for more details of its use:
 *    http://www.khronos.org/registry/implementers_guide.pdf
 *
 * This file should be included as
 *        #include <KHR/khrplatform.h>
 * by Khronos client API header files that use its types and defines.
 *
 * The types in khrplatform.h should only be used to define API-specific types.
 *
 * Types defined in khrplatform.h:
 *    khronos_int8_t              signed   8  bit
 *    khronos_uint8_t             unsigned 8  bit
 *    khronos_int16_t             signed   16 bit
 *    khronos_uint16_t            unsigned 16 bit
 *    khronos_int32_t             signed   32 bit
 *    khronos_uint32_t            unsigned 32 bit
 *    khronos_int64_t             signed   64 bit
 *    khronos_uint64_t            unsigned 64 bit
 *    khronos_intptr_t            signed   same number of bits as a pointer
 *    khronos_uintptr_t           unsigned same number of bits as a pointer
 *    khronos_ssize_t             signed   size
 *    khronos_usize_t             unsigned size
 *    khronos_float_t             signed   32 bit floating point
 *    khronos_time_ns_t           unsigned 64 bit time in nanoseconds
 *    khronos_utime_nanoseconds_t unsigned time interval or absolute time in
 *                                         nanoseconds
 *    khronos_stime_nanoseconds_t signed time interval in nanoseconds
 *    khronos_boolean_enum_t      enumerated boolean type. This should
 *      only be used as a base type when a client API's boolean type is
 *      an enum. Client APIs which use an integer or other type for
 *      booleans cannot use this as the base type for their boolean.
 *
 * Tokens defined in khrplatform.h:
 *
 *    KHRONOS_FALSE, KHRONOS_TRUE Enumerated boolean false/true values.
 *
 *    KHRONOS_SUPPORT_INT64 is 1 if 64 bit integers are supported; otherwise 0.
 *    KHRONOS_SUPPORT_FLOAT is 1 if floats are supported; otherwise 0.
 *
 * Calling convention macros defined in this file:
 *    KHRONOS_APICALL
 *    KHRONOS_APIENTRY
 *    KHRONOS_APIATTRIBUTES
 *
 * These may be used in function prototypes as:
 *
 *      KHRONOS_APICALL void KHRONOS_APIENTRY funcname(
 *                                  int arg1,
 *                                  int arg2) KHRONOS_APIATTRIBUTES;
 */

#अगर defined(__SCITECH_SNAP__) && !defined(KHRONOS_STATIC)
#   define KHRONOS_STATIC 1
#पूर्ण_अगर

/*-------------------------------------------------------------------------
 * Definition of KHRONOS_APICALL
 *-------------------------------------------------------------------------
 * This precedes the return type of the function in the function prototype.
 */
#अगर defined(KHRONOS_STATIC)
    /* If the preprocessor constant KHRONOS_STATIC is defined, make the
     * header compatible with static linking. */
#   define KHRONOS_APICALL
#या_अगर defined(_WIN32)
#   define KHRONOS_APICALL __declspec(dllimport)
#या_अगर defined (__SYMBIAN32__)
#   define KHRONOS_APICALL IMPORT_C
#या_अगर defined(__ANDROID__)
#   define KHRONOS_APICALL __attribute__((visibility("default")))
#अन्यथा
#   define KHRONOS_APICALL
#पूर्ण_अगर

/*-------------------------------------------------------------------------
 * Definition of KHRONOS_APIENTRY
 *-------------------------------------------------------------------------
 * This follows the return type of the function  and precedes the function
 * name in the function prototype.
 */
#अगर defined(_WIN32) && !defined(_WIN32_WCE) && !defined(__SCITECH_SNAP__)
    /* Win32 but not WinCE */
#   define KHRONOS_APIENTRY __stdcall
#या_अगर defined(__CYGWIN__) /* __CYGWIN__ added by SDL */
#   define KHRONOS_APIENTRY __stdcall
#अन्यथा
#   define KHRONOS_APIENTRY
#पूर्ण_अगर

/*-------------------------------------------------------------------------
 * Definition of KHRONOS_APIATTRIBUTES
 *-------------------------------------------------------------------------
 * This follows the closing parenthesis of the function prototype arguments.
 */
#अगर defined (__ARMCC_2__)
#घोषणा KHRONOS_APIATTRIBUTES __softfp
#अन्यथा
#घोषणा KHRONOS_APIATTRIBUTES
#पूर्ण_अगर

/*-------------------------------------------------------------------------
 * basic type definitions
 *-----------------------------------------------------------------------*/
#अगर (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || defined(__GNUC__) || defined(__SCO__) || defined(__USLC__)


/*
 * Using <stdint.h>
 */
#समावेश <stdint.h>
प्रकार int32_t                 khronos_int32_t;
प्रकार uint32_t                khronos_uint32_t;
प्रकार int64_t                 khronos_int64_t;
प्रकार uint64_t                khronos_uint64_t;
#घोषणा KHRONOS_SUPPORT_INT64   1
#घोषणा KHRONOS_SUPPORT_FLOAT   1
/*
 * To support platform where unsigned long cannot be used interchangeably with
 * inptr_t (e.g. CHERI-extended ISAs), we can use the stdint.h intptr_t.
 * Ideally, we could just use (u)intptr_t everywhere, but this could result in
 * ABI breakage if khronos_uintptr_t is changed from unsigned long to
 * unsigned long long or similar (this results in different C++ name mangling).
 * To avoid changes for existing platforms, we restrict usage of intptr_t to
 * platforms where the size of a pointer is larger than the size of long.
 */
#अगर defined(__SIZEOF_LONG__) && defined(__SIZEOF_POINTER__)
#अगर __SIZEOF_POINTER__ > __SIZEOF_LONG__
#घोषणा KHRONOS_USE_INTPTR_T
#पूर्ण_अगर
#पूर्ण_अगर

#या_अगर defined(__VMS ) || defined(__sgi)

/*
 * Using <inttypes.h>
 */
#समावेश <inttypes.h>
प्रकार int32_t                 khronos_int32_t;
प्रकार uint32_t                khronos_uint32_t;
प्रकार int64_t                 khronos_int64_t;
प्रकार uint64_t                khronos_uint64_t;
#घोषणा KHRONOS_SUPPORT_INT64   1
#घोषणा KHRONOS_SUPPORT_FLOAT   1

#या_अगर defined(_WIN32) && !defined(__SCITECH_SNAP__)

/*
 * Win32
 */
प्रकार __int32                 khronos_int32_t;
प्रकार अचिन्हित __int32        khronos_uint32_t;
प्रकार __int64                 khronos_int64_t;
प्रकार अचिन्हित __int64        khronos_uint64_t;
#घोषणा KHRONOS_SUPPORT_INT64   1
#घोषणा KHRONOS_SUPPORT_FLOAT   1

#या_अगर defined(__sun__) || defined(__digital__)

/*
 * Sun or Digital
 */
प्रकार पूर्णांक                     khronos_int32_t;
प्रकार अचिन्हित पूर्णांक            khronos_uint32_t;
#अगर defined(__arch64__) || defined(_LP64)
प्रकार दीर्घ पूर्णांक                khronos_int64_t;
प्रकार अचिन्हित दीर्घ पूर्णांक       khronos_uint64_t;
#अन्यथा
प्रकार दीर्घ दीर्घ पूर्णांक           khronos_int64_t;
प्रकार अचिन्हित दीर्घ दीर्घ पूर्णांक  khronos_uint64_t;
#पूर्ण_अगर /* __arch64__ */
#घोषणा KHRONOS_SUPPORT_INT64   1
#घोषणा KHRONOS_SUPPORT_FLOAT   1

#या_अगर 0

/*
 * Hypothetical platform with no float or int64 support
 */
प्रकार पूर्णांक                     khronos_int32_t;
प्रकार अचिन्हित पूर्णांक            khronos_uint32_t;
#घोषणा KHRONOS_SUPPORT_INT64   0
#घोषणा KHRONOS_SUPPORT_FLOAT   0

#अन्यथा

/*
 * Generic fallback
 */
#समावेश <stdint.h>
प्रकार int32_t                 khronos_int32_t;
प्रकार uint32_t                khronos_uint32_t;
प्रकार int64_t                 khronos_int64_t;
प्रकार uint64_t                khronos_uint64_t;
#घोषणा KHRONOS_SUPPORT_INT64   1
#घोषणा KHRONOS_SUPPORT_FLOAT   1

#पूर्ण_अगर


/*
 * Types that are (so far) the same on all platforms
 */
प्रकार चिन्हित   अक्षर          khronos_int8_t;
प्रकार अचिन्हित अक्षर          khronos_uint8_t;
प्रकार चिन्हित   लघु पूर्णांक     khronos_int16_t;
प्रकार अचिन्हित लघु पूर्णांक     khronos_uint16_t;

/*
 * Types that differ between LLP64 and LP64 architectures - in LLP64,
 * pointers are 64 bits, but 'long' is still 32 bits. Win64 appears
 * to be the only LLP64 architecture in current use.
 */
#अगर_घोषित KHRONOS_USE_INTPTR_T
प्रकार intptr_t               khronos_intptr_t;
प्रकार uintptr_t              khronos_uintptr_t;
#या_अगर defined(_WIN64)
प्रकार चिन्हित   दीर्घ दीर्घ पूर्णांक khronos_intptr_t;
प्रकार अचिन्हित दीर्घ दीर्घ पूर्णांक khronos_uintptr_t;
#अन्यथा
प्रकार चिन्हित   दीर्घ  पूर्णांक     khronos_intptr_t;
प्रकार अचिन्हित दीर्घ  पूर्णांक     khronos_uintptr_t;
#पूर्ण_अगर

#अगर defined(_WIN64)
प्रकार चिन्हित   दीर्घ दीर्घ पूर्णांक khronos_ssize_t;
प्रकार अचिन्हित दीर्घ दीर्घ पूर्णांक khronos_usize_t;
#अन्यथा
प्रकार चिन्हित   दीर्घ  पूर्णांक     khronos_ssize_t;
प्रकार अचिन्हित दीर्घ  पूर्णांक     khronos_usize_t;
#पूर्ण_अगर

#अगर KHRONOS_SUPPORT_FLOAT
/*
 * Float type
 */
प्रकार          भग्न         khronos_float_t;
#पूर्ण_अगर

#अगर KHRONOS_SUPPORT_INT64
/* Time types
 *
 * These types can be used to represent a time interval in nanoseconds or
 * an absolute Unadjusted System Time.  Unadjusted System Time is the number
 * of nanoseconds since some arbitrary system event (e.g. since the last
 * time the system booted).  The Unadjusted System Time is an unsigned
 * 64 bit value that wraps back to 0 every 584 years.  Time intervals
 * may be either signed or unsigned.
 */
प्रकार khronos_uint64_t       khronos_utime_nanoseconds_t;
प्रकार khronos_int64_t        khronos_stime_nanoseconds_t;
#पूर्ण_अगर

/*
 * Dummy value used to pad enum types to 32 bits.
 */
#अगर_अघोषित KHRONOS_MAX_ENUM
#घोषणा KHRONOS_MAX_ENUM 0x7FFFFFFF
#पूर्ण_अगर

/*
 * Enumerated boolean type
 *
 * Values other than zero should be considered to be true.  Therefore
 * comparisons should not be made against KHRONOS_TRUE.
 */
प्रकार क्रमागत {
    KHRONOS_FALSE = 0,
    KHRONOS_TRUE  = 1,
    KHRONOS_BOOLEAN_ENUM_FORCE_आकार = KHRONOS_MAX_ENUM
} khronos_boolean_enum_t;

#पूर्ण_अगर /* __khrplatform_h_ */

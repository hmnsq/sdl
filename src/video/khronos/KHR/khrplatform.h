#ifndef __khrplatform_h_
#define __khrplatform_h_

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

#যদি defined(__SCITECH_SNAP__) && !defined(KHRONOS_STATIC)
#   define KHRONOS_STATIC 1
#endif

/*-------------------------------------------------------------------------
 * Definition of KHRONOS_APICALL
 *-------------------------------------------------------------------------
 * This precedes the return type of the function in the function prototype.
 */
#যদি defined(KHRONOS_STATIC)
    /* If the preprocessor constant KHRONOS_STATIC is defined, make the
     * header compatible with static linking. */
#   define KHRONOS_APICALL
#নোচেদ্যদি defined(_WIN32)
#   define KHRONOS_APICALL __declspec(dllimport)
#নোচেদ্যদি defined (__SYMBIAN32__)
#   define KHRONOS_APICALL IMPORT_C
#নোচেদ্যদি defined(__ANDROID__)
#   define KHRONOS_APICALL __attribute__((visibility("default")))
#অন্যথা
#   define KHRONOS_APICALL
#endif

/*-------------------------------------------------------------------------
 * Definition of KHRONOS_APIENTRY
 *-------------------------------------------------------------------------
 * This follows the return type of the function  and precedes the function
 * name in the function prototype.
 */
#যদি defined(_WIN32) && !defined(_WIN32_WCE) && !defined(__SCITECH_SNAP__)
    /* Win32 but not WinCE */
#   define KHRONOS_APIENTRY __stdcall
#নোচেদ্যদি defined(__CYGWIN__) /* __CYGWIN__ added by SDL */
#   define KHRONOS_APIENTRY __stdcall
#অন্যথা
#   define KHRONOS_APIENTRY
#endif

/*-------------------------------------------------------------------------
 * Definition of KHRONOS_APIATTRIBUTES
 *-------------------------------------------------------------------------
 * This follows the closing parenthesis of the function prototype arguments.
 */
#যদি defined (__ARMCC_2__)
#define KHRONOS_APIATTRIBUTES __softfp
#অন্যথা
#define KHRONOS_APIATTRIBUTES
#endif

/*-------------------------------------------------------------------------
 * basic type definitions
 *-----------------------------------------------------------------------*/
#যদি (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || defined(__GNUC__) || defined(__SCO__) || defined(__USLC__)


/*
 * Using <stdint.h>
 */
#অন্তর্ভাব <stdint.h>
প্রকারনির্দেশ int32_t                 khronos_int32_t;
প্রকারনির্দেশ uint32_t                khronos_uint32_t;
প্রকারনির্দেশ int64_t                 khronos_int64_t;
প্রকারনির্দেশ uint64_t                khronos_uint64_t;
#define KHRONOS_SUPPORT_INT64   1
#define KHRONOS_SUPPORT_FLOAT   1
/*
 * To support platform where unsigned long cannot be used interchangeably with
 * inptr_t (e.g. CHERI-extended ISAs), we can use the stdint.h intptr_t.
 * Ideally, we could just use (u)intptr_t everywhere, but this could result in
 * ABI breakage if khronos_uintptr_t is changed from unsigned long to
 * unsigned long long or similar (this results in different C++ name mangling).
 * To avoid changes for existing platforms, we restrict usage of intptr_t to
 * platforms where the size of a pointer is larger than the size of long.
 */
#যদি defined(__SIZEOF_LONG__) && defined(__SIZEOF_POINTER__)
#যদি __SIZEOF_POINTER__ > __SIZEOF_LONG__
#define KHRONOS_USE_INTPTR_T
#endif
#endif

#নোচেদ্যদি defined(__VMS ) || defined(__sgi)

/*
 * Using <inttypes.h>
 */
#অন্তর্ভাব <inttypes.h>
প্রকারনির্দেশ int32_t                 khronos_int32_t;
প্রকারনির্দেশ uint32_t                khronos_uint32_t;
প্রকারনির্দেশ int64_t                 khronos_int64_t;
প্রকারনির্দেশ uint64_t                khronos_uint64_t;
#define KHRONOS_SUPPORT_INT64   1
#define KHRONOS_SUPPORT_FLOAT   1

#নোচেদ্যদি defined(_WIN32) && !defined(__SCITECH_SNAP__)

/*
 * Win32
 */
প্রকারনির্দেশ __int32                 khronos_int32_t;
প্রকারনির্দেশ unsigned __int32        khronos_uint32_t;
প্রকারনির্দেশ __int64                 khronos_int64_t;
প্রকারনির্দেশ unsigned __int64        khronos_uint64_t;
#define KHRONOS_SUPPORT_INT64   1
#define KHRONOS_SUPPORT_FLOAT   1

#নোচেদ্যদি defined(__sun__) || defined(__digital__)

/*
 * Sun or Digital
 */
প্রকারনির্দেশ পূর্ণাঙ্ক                     khronos_int32_t;
প্রকারনির্দেশ unsigned পূর্ণাঙ্ক            khronos_uint32_t;
#যদি defined(__arch64__) || defined(_LP64)
প্রকারনির্দেশ long পূর্ণাঙ্ক                khronos_int64_t;
প্রকারনির্দেশ unsigned long পূর্ণাঙ্ক       khronos_uint64_t;
#অন্যথা
প্রকারনির্দেশ long long পূর্ণাঙ্ক           khronos_int64_t;
প্রকারনির্দেশ unsigned long long পূর্ণাঙ্ক  khronos_uint64_t;
#endif /* __arch64__ */
#define KHRONOS_SUPPORT_INT64   1
#define KHRONOS_SUPPORT_FLOAT   1

#নোচেদ্যদি 0

/*
 * Hypothetical platform with no float or int64 support
 */
প্রকারনির্দেশ পূর্ণাঙ্ক                     khronos_int32_t;
প্রকারনির্দেশ unsigned পূর্ণাঙ্ক            khronos_uint32_t;
#define KHRONOS_SUPPORT_INT64   0
#define KHRONOS_SUPPORT_FLOAT   0

#অন্যথা

/*
 * Generic fallback
 */
#অন্তর্ভাব <stdint.h>
প্রকারনির্দেশ int32_t                 khronos_int32_t;
প্রকারনির্দেশ uint32_t                khronos_uint32_t;
প্রকারনির্দেশ int64_t                 khronos_int64_t;
প্রকারনির্দেশ uint64_t                khronos_uint64_t;
#define KHRONOS_SUPPORT_INT64   1
#define KHRONOS_SUPPORT_FLOAT   1

#endif


/*
 * Types that are (so far) the same on all platforms
 */
প্রকারনির্দেশ signed   বর্ণ          khronos_int8_t;
প্রকারনির্দেশ unsigned বর্ণ          khronos_uint8_t;
প্রকারনির্দেশ signed   short পূর্ণাঙ্ক     khronos_int16_t;
প্রকারনির্দেশ unsigned short পূর্ণাঙ্ক     khronos_uint16_t;

/*
 * Types that differ between LLP64 and LP64 architectures - in LLP64,
 * pointers are 64 bits, but 'long' is still 32 bits. Win64 appears
 * to be the only LLP64 architecture in current use.
 */
#ifdef KHRONOS_USE_INTPTR_T
প্রকারনির্দেশ intptr_t               khronos_intptr_t;
প্রকারনির্দেশ uintptr_t              khronos_uintptr_t;
#নোচেদ্যদি defined(_WIN64)
প্রকারনির্দেশ signed   long long পূর্ণাঙ্ক khronos_intptr_t;
প্রকারনির্দেশ unsigned long long পূর্ণাঙ্ক khronos_uintptr_t;
#অন্যথা
প্রকারনির্দেশ signed   long  পূর্ণাঙ্ক     khronos_intptr_t;
প্রকারনির্দেশ unsigned long  পূর্ণাঙ্ক     khronos_uintptr_t;
#endif

#যদি defined(_WIN64)
প্রকারনির্দেশ signed   long long পূর্ণাঙ্ক khronos_ssize_t;
প্রকারনির্দেশ unsigned long long পূর্ণাঙ্ক khronos_usize_t;
#অন্যথা
প্রকারনির্দেশ signed   long  পূর্ণাঙ্ক     khronos_ssize_t;
প্রকারনির্দেশ unsigned long  পূর্ণাঙ্ক     khronos_usize_t;
#endif

#যদি KHRONOS_SUPPORT_FLOAT
/*
 * Float type
 */
প্রকারনির্দেশ          ভিন্ন         khronos_float_t;
#endif

#যদি KHRONOS_SUPPORT_INT64
/* Time types
 *
 * These types can be used to represent a time interval in nanoseconds or
 * an absolute Unadjusted System Time.  Unadjusted System Time is the number
 * of nanoseconds since some arbitrary system event (e.g. since the last
 * time the system booted).  The Unadjusted System Time is an unsigned
 * 64 bit value that wraps back to 0 every 584 years.  Time intervals
 * may be either signed or unsigned.
 */
প্রকারনির্দেশ khronos_uint64_t       khronos_utime_nanoseconds_t;
প্রকারনির্দেশ khronos_int64_t        khronos_stime_nanoseconds_t;
#endif

/*
 * Dummy value used to pad enum types to 32 bits.
 */
#ifndef KHRONOS_MAX_ENUM
#define KHRONOS_MAX_ENUM 0x7FFFFFFF
#endif

/*
 * Enumerated boolean type
 *
 * Values other than zero should be considered to be true.  Therefore
 * comparisons should not be made against KHRONOS_TRUE.
 */
প্রকারনির্দেশ গণনা {
    KHRONOS_FALSE = 0,
    KHRONOS_TRUE  = 1,
    KHRONOS_BOOLEAN_ENUM_FORCE_SIZE = KHRONOS_MAX_ENUM
} khronos_boolean_enum_t;

#endif /* __khrplatform_h_ */

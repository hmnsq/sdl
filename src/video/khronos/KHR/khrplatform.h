#నిర్వచితం_కాకపోతే __khrplatform_h_
#నిర్వచించు __khrplatform_h_

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

#ఒకవేళ defined(__SCITECH_SNAP__) && !defined(KHRONOS_STATIC)
#   define KHRONOS_STATIC 1
#అయితే_ముగింపు

/*-------------------------------------------------------------------------
 * Definition of KHRONOS_APICALL
 *-------------------------------------------------------------------------
 * This precedes the return type of the function in the function prototype.
 */
#ఒకవేళ defined(KHRONOS_STATIC)
    /* If the preprocessor constant KHRONOS_STATIC is defined, make the
     * header compatible with static linking. */
#   define KHRONOS_APICALL
#లేదావేళ defined(_WIN32)
#   define KHRONOS_APICALL __declspec(dllimport)
#లేదావేళ defined (__SYMBIAN32__)
#   define KHRONOS_APICALL IMPORT_C
#లేదావేళ defined(__ANDROID__)
#   define KHRONOS_APICALL __attribute__((visibility("default")))
#లేకపోతే
#   define KHRONOS_APICALL
#అయితే_ముగింపు

/*-------------------------------------------------------------------------
 * Definition of KHRONOS_APIENTRY
 *-------------------------------------------------------------------------
 * This follows the return type of the function  and precedes the function
 * name in the function prototype.
 */
#ఒకవేళ defined(_WIN32) && !defined(_WIN32_WCE) && !defined(__SCITECH_SNAP__)
    /* Win32 but not WinCE */
#   define KHRONOS_APIENTRY __stdcall
#లేదావేళ defined(__CYGWIN__) /* __CYGWIN__ added by SDL */
#   define KHRONOS_APIENTRY __stdcall
#లేకపోతే
#   define KHRONOS_APIENTRY
#అయితే_ముగింపు

/*-------------------------------------------------------------------------
 * Definition of KHRONOS_APIATTRIBUTES
 *-------------------------------------------------------------------------
 * This follows the closing parenthesis of the function prototype arguments.
 */
#ఒకవేళ defined (__ARMCC_2__)
#నిర్వచించు KHRONOS_APIATTRIBUTES __softfp
#లేకపోతే
#నిర్వచించు KHRONOS_APIATTRIBUTES
#అయితే_ముగింపు

/*-------------------------------------------------------------------------
 * basic type definitions
 *-----------------------------------------------------------------------*/
#ఒకవేళ (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || defined(__GNUC__) || defined(__SCO__) || defined(__USLC__)


/*
 * Using <stdint.h>
 */
#అన్తర్భావ <stdint.h>
రకనిర్వచనం int32_t                 khronos_int32_t;
రకనిర్వచనం uint32_t                khronos_uint32_t;
రకనిర్వచనం int64_t                 khronos_int64_t;
రకనిర్వచనం uint64_t                khronos_uint64_t;
#నిర్వచించు KHRONOS_SUPPORT_INT64   1
#నిర్వచించు KHRONOS_SUPPORT_FLOAT   1
/*
 * To support platform where unsigned long cannot be used interchangeably with
 * inptr_t (e.g. CHERI-extended ISAs), we can use the stdint.h intptr_t.
 * Ideally, we could just use (u)intptr_t everywhere, but this could result in
 * ABI breakage if khronos_uintptr_t is changed from unsigned long to
 * unsigned long long or similar (this results in different C++ name mangling).
 * To avoid changes for existing platforms, we restrict usage of intptr_t to
 * platforms where the size of a pointer is larger than the size of long.
 */
#ఒకవేళ defined(__SIZEOF_LONG__) && defined(__SIZEOF_POINTER__)
#ఒకవేళ __SIZEOF_POINTER__ > __SIZEOF_LONG__
#నిర్వచించు KHRONOS_USE_INTPTR_T
#అయితే_ముగింపు
#అయితే_ముగింపు

#లేదావేళ defined(__VMS ) || defined(__sgi)

/*
 * Using <inttypes.h>
 */
#అన్తర్భావ <inttypes.h>
రకనిర్వచనం int32_t                 khronos_int32_t;
రకనిర్వచనం uint32_t                khronos_uint32_t;
రకనిర్వచనం int64_t                 khronos_int64_t;
రకనిర్వచనం uint64_t                khronos_uint64_t;
#నిర్వచించు KHRONOS_SUPPORT_INT64   1
#నిర్వచించు KHRONOS_SUPPORT_FLOAT   1

#లేదావేళ defined(_WIN32) && !defined(__SCITECH_SNAP__)

/*
 * Win32
 */
రకనిర్వచనం __int32                 khronos_int32_t;
రకనిర్వచనం గుర్తులేని __int32        khronos_uint32_t;
రకనిర్వచనం __int64                 khronos_int64_t;
రకనిర్వచనం గుర్తులేని __int64        khronos_uint64_t;
#నిర్వచించు KHRONOS_SUPPORT_INT64   1
#నిర్వచించు KHRONOS_SUPPORT_FLOAT   1

#లేదావేళ defined(__sun__) || defined(__digital__)

/*
 * Sun or Digital
 */
రకనిర్వచనం పూర్ణాంకం                     khronos_int32_t;
రకనిర్వచనం గుర్తులేని పూర్ణాంకం            khronos_uint32_t;
#ఒకవేళ defined(__arch64__) || defined(_LP64)
రకనిర్వచనం దీర్ఘ పూర్ణాంకం                khronos_int64_t;
రకనిర్వచనం గుర్తులేని దీర్ఘ పూర్ణాంకం       khronos_uint64_t;
#లేకపోతే
రకనిర్వచనం దీర్ఘ దీర్ఘ పూర్ణాంకం           khronos_int64_t;
రకనిర్వచనం గుర్తులేని దీర్ఘ దీర్ఘ పూర్ణాంకం  khronos_uint64_t;
#అయితే_ముగింపు /* __arch64__ */
#నిర్వచించు KHRONOS_SUPPORT_INT64   1
#నిర్వచించు KHRONOS_SUPPORT_FLOAT   1

#లేదావేళ 0

/*
 * Hypothetical platform with no float or int64 support
 */
రకనిర్వచనం పూర్ణాంకం                     khronos_int32_t;
రకనిర్వచనం గుర్తులేని పూర్ణాంకం            khronos_uint32_t;
#నిర్వచించు KHRONOS_SUPPORT_INT64   0
#నిర్వచించు KHRONOS_SUPPORT_FLOAT   0

#లేకపోతే

/*
 * Generic fallback
 */
#అన్తర్భావ <stdint.h>
రకనిర్వచనం int32_t                 khronos_int32_t;
రకనిర్వచనం uint32_t                khronos_uint32_t;
రకనిర్వచనం int64_t                 khronos_int64_t;
రకనిర్వచనం uint64_t                khronos_uint64_t;
#నిర్వచించు KHRONOS_SUPPORT_INT64   1
#నిర్వచించు KHRONOS_SUPPORT_FLOAT   1

#అయితే_ముగింపు


/*
 * Types that are (so far) the same on all platforms
 */
రకనిర్వచనం గుర్తుగల   అక్షరం          khronos_int8_t;
రకనిర్వచనం గుర్తులేని అక్షరం          khronos_uint8_t;
రకనిర్వచనం గుర్తుగల   పొట్టి పూర్ణాంకం     khronos_int16_t;
రకనిర్వచనం గుర్తులేని పొట్టి పూర్ణాంకం     khronos_uint16_t;

/*
 * Types that differ between LLP64 and LP64 architectures - in LLP64,
 * pointers are 64 bits, but 'long' is still 32 bits. Win64 appears
 * to be the only LLP64 architecture in current use.
 */
#నిర్వచితమైతే KHRONOS_USE_INTPTR_T
రకనిర్వచనం intptr_t               khronos_intptr_t;
రకనిర్వచనం uintptr_t              khronos_uintptr_t;
#లేదావేళ defined(_WIN64)
రకనిర్వచనం గుర్తుగల   దీర్ఘ దీర్ఘ పూర్ణాంకం khronos_intptr_t;
రకనిర్వచనం గుర్తులేని దీర్ఘ దీర్ఘ పూర్ణాంకం khronos_uintptr_t;
#లేకపోతే
రకనిర్వచనం గుర్తుగల   దీర్ఘ  పూర్ణాంకం     khronos_intptr_t;
రకనిర్వచనం గుర్తులేని దీర్ఘ  పూర్ణాంకం     khronos_uintptr_t;
#అయితే_ముగింపు

#ఒకవేళ defined(_WIN64)
రకనిర్వచనం గుర్తుగల   దీర్ఘ దీర్ఘ పూర్ణాంకం khronos_ssize_t;
రకనిర్వచనం గుర్తులేని దీర్ఘ దీర్ఘ పూర్ణాంకం khronos_usize_t;
#లేకపోతే
రకనిర్వచనం గుర్తుగల   దీర్ఘ  పూర్ణాంకం     khronos_ssize_t;
రకనిర్వచనం గుర్తులేని దీర్ఘ  పూర్ణాంకం     khronos_usize_t;
#అయితే_ముగింపు

#ఒకవేళ KHRONOS_SUPPORT_FLOAT
/*
 * Float type
 */
రకనిర్వచనం          దశాంశం         khronos_float_t;
#అయితే_ముగింపు

#ఒకవేళ KHRONOS_SUPPORT_INT64
/* Time types
 *
 * These types can be used to represent a time interval in nanoseconds or
 * an absolute Unadjusted System Time.  Unadjusted System Time is the number
 * of nanoseconds since some arbitrary system event (e.g. since the last
 * time the system booted).  The Unadjusted System Time is an unsigned
 * 64 bit value that wraps back to 0 every 584 years.  Time intervals
 * may be either signed or unsigned.
 */
రకనిర్వచనం khronos_uint64_t       khronos_utime_nanoseconds_t;
రకనిర్వచనం khronos_int64_t        khronos_stime_nanoseconds_t;
#అయితే_ముగింపు

/*
 * Dummy value used to pad enum types to 32 bits.
 */
#నిర్వచితం_కాకపోతే KHRONOS_MAX_ENUM
#నిర్వచించు KHRONOS_MAX_ENUM 0x7FFFFFFF
#అయితే_ముగింపు

/*
 * Enumerated boolean type
 *
 * Values other than zero should be considered to be true.  Therefore
 * comparisons should not be made against KHRONOS_TRUE.
 */
రకనిర్వచనం గణన {
    KHRONOS_FALSE = 0,
    KHRONOS_TRUE  = 1,
    KHRONOS_BOOLEAN_ENUM_FORCE_కొలత = KHRONOS_MAX_ENUM
} khronos_boolean_enum_t;

#అయితే_ముగింపు /* __khrplatform_h_ */

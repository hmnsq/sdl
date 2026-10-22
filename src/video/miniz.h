/* miniz.c v1.15 - public domain deflate/inflate, zlib-subset, ZIP reading/writing/appending, PNG writing
   See "unlicense" statement at the end of this file.
   Rich Geldreich <richgel99@gmail.com>, last updated Oct. 13, 2013
   Implements RFC 1950: http://www.ietf.org/rfc/rfc1950.txt and RFC 1951: http://www.ietf.org/rfc/rfc1951.txt

   Most API's defined in miniz.c are optional. For example, to disable the archive related functions just define
   MINIZ_NO_ARCHIVE_APIS, or to get rid of all stdio usage define MINIZ_NO_STDIO (see the list below for more macros).

   * Change History
     10/13/13 v1.15 r4 - Interim bugfix release while I work on the next major release with Zip64 support (almost there!):
       - Critical fix for the MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY bug (thanks kahmyong.moon@hp.com) which could cause locate files to not find files. This bug
        would only have occured in earlier versions if you explicitly used this flag, OR if you used mz_zip_extract_archive_file_to_heap() or mz_zip_add_mem_to_archive_file_in_place()
        (which used this flag). If you can't switch to v1.15 but want to fix this bug, just remove the uses of this flag from both helper funcs (and of course don't use the flag).
       - Bugfix in mz_zip_reader_extract_to_mem_no_alloc() from kymoon when pUser_read_buf is not NULL and compressed size is > uncompressed size
       - Fixing mz_zip_reader_extract_*() funcs so they don't try to extract compressed data from directory entries, to account for weird zipfiles which contain zero-size compressed data on dir entries.
         Hopefully this fix won't cause any issues on weird zip archives, because it assumes the low 16-bits of zip external attributes are DOS attributes (which I believe they always are in practice).
       - Fixing mz_zip_reader_is_file_a_directory() so it doesn't check the internal attributes, just the filename and external attributes
       - mz_zip_reader_init_file() - missing MZ_FCLOSE() call if the seek failed
       - Added cmake support for Linux builds which builds all the examples, tested with clang v3.3 and gcc v4.6.
       - Clang fix for tdefl_write_image_to_png_file_in_memory() from toffaletti
       - Merged MZ_FORCEINLINE fix from hdeanclark
       - Fix <time.h> include before config #ifdef, thanks emil.brink
       - Added tdefl_write_image_to_png_file_in_memory_ex(): supports Y flipping (super useful for OpenGL apps), and explicit control over the compression level (so you can
        set it to 1 for real-time compression).
       - Merged in some compiler fixes from paulharris's github repro.
       - Retested this build under Windows (VS 2010, including static analysis), tcc  0.9.26, gcc v4.6 and clang v3.3.
       - Added example6.c, which dumps an image of the mandelbrot set to a PNG file.
       - Modified example2 to help test the MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY flag more.
       - In r3: Bugfix to mz_zip_writer_add_file() found during merge: Fix possible src file fclose() leak if alignment bytes+local header file write faiiled
       - In r4: Minor bugfix to mz_zip_writer_add_from_zip_reader(): Was pushing the wrong central dir header offset, appears harmless in this release, but it became a problem in the zip64 branch
     5/20/12 v1.14 - MinGW32/64 GCC 4.6.1 compiler fixes: added MZ_FORCEINLINE, #include <time.h> (thanks fermtect).
     5/19/12 v1.13 - From jason@cornsyrup.org and kelwert@mtu.edu - Fix mz_crc32() so it doesn't compute the wrong CRC-32's when mz_ulong is 64-bit.
       - Temporarily/locally slammed in "typedef unsigned long mz_ulong" and re-ran a randomized regression test on ~500k files.
       - Eliminated a bunch of warnings when compiling with GCC 32-bit/64.
       - Ran all examples, miniz.c, and tinfl.c through MSVC 2008's /analyze (static analysis) option and fixed all warnings (except for the silly
        "Use of the comma-operator in a tested expression.." analysis warning, which I purposely use to work around a MSVC compiler warning).
       - Created 32-bit and 64-bit Codeblocks projects/workspace. Built and tested Linux executables. The codeblocks workspace is compatible with Linux+Win32/x64.
       - Added miniz_tester solution/project, which is a useful little app derived from LZHAM's tester app that I use as part of the regression test.
       - Ran miniz.c and tinfl.c through another series of regression testing on ~500,000 files and archives.
       - Modified example5.c so it purposely disables a bunch of high-level functionality (MINIZ_NO_STDIO, etc.). (Thanks to corysama for the MINIZ_NO_STDIO bug report.)
       - Fix ftell() usage in examples so they exit with an error on files which are too large (a limitation of the examples, not miniz itself).
     4/12/12 v1.12 - More comments, added low-level example5.c, fixed a couple minor level_and_flags issues in the archive API's.
      level_and_flags can now be set to MZ_DEFAULT_COMPRESSION. Thanks to Bruce Dawson <bruced@valvesoftware.com> for the feedback/bug report.
     5/28/11 v1.11 - Added statement from unlicense.org
     5/27/11 v1.10 - Substantial compressor optimizations:
      - Level 1 is now ~4x faster than before. The L1 compressor's throughput now varies between 70-110MB/sec. on a
      - Core i7 (actual throughput varies depending on the type of data, and x64 vs. x86).
      - Improved baseline L2-L9 compression perf. Also, greatly improved compression perf. issues on some file types.
      - Refactored the compression code for better readability and maintainability.
      - Added level 10 compression level (L10 has slightly better ratio than level 9, but could have a potentially large
       drop in throughput on some files).
     5/15/11 v1.09 - Initial stable release.

   * Low-level Deflate/Inflate implementation notes:

     Compression: Use the "tdefl" API's. The compressor supports raw, static, and dynamic blocks, lazy or
     greedy parsing, match length filtering, RLE-only, and Huffman-only streams. It performs and compresses
     approximately as well as zlib.

     Decompression: Use the "tinfl" API's. The entire decompressor is implemented as a single function
     coroutine: see tinfl_decompress(). It supports decompression into a 32KB (or larger power of 2) wrapping buffer, or into a memory
     block large enough to hold the entire file.

     The low-level tdefl/tinfl API's do not make any use of dynamic memory allocation.

   * zlib-style API notes:

     miniz.c implements a fairly large subset of zlib. There's enough functionality present for it to be a drop-in
     zlib replacement in many apps:
        The z_stream struct, optional memory allocation callbacks
        deflateInit/deflateInit2/deflate/deflateReset/deflateEnd/deflateBound
        inflateInit/inflateInit2/inflate/inflateEnd
        compress, compress2, compressBound, uncompress
        CRC-32, Adler-32 - Using modern, minimal code size, CPU cache friendly routines.
        Supports raw deflate streams or standard zlib streams with adler-32 checking.

     Limitations:
      The callback API's are not implemented yet. No support for gzip headers or zlib static dictionaries.
      I've tried to closely emulate zlib's various flavors of stream flushing and return status codes, but
      there are no guarantees that miniz.c pulls this off perfectly.

   * PNG writing: See the tdefl_write_image_to_png_file_in_memory() function, originally written by
     Alex Evans. Supports 1-4 bytes/pixel images.

   * ZIP archive API notes:

     The ZIP archive API's where designed with simplicity and efficiency in mind, with just enough abstraction to
     get the job done with minimal fuss. There are simple API's to retrieve file information, read files from
     existing archives, create new archives, append new files to existing archives, or clone archive data from
     one archive to another. It supports archives located in memory or the heap, on disk (using stdio.h),
     or you can specify custom file read/write callbacks.

     - Archive reading: Just call this function to read a single file from a disk archive:

      void *mz_zip_extract_archive_file_to_heap(const char *pZip_filename, const char *pArchive_name,
        size_t *pSize, mz_uint zip_flags);

     For more complex cases, use the "mz_zip_reader" functions. Upon opening an archive, the entire central
     directory is located and read as-is into memory, and subsequent file access only occurs when reading individual files.

     - Archives file scanning: The simple way is to use this function to scan a loaded archive for a specific file:

     int mz_zip_reader_locate_file(mz_zip_archive *pZip, const char *pName, const char *pComment, mz_uint flags);

     The locate operation can optionally check file comments too, which (as one example) can be used to identify
     multiple versions of the same file in an archive. This function uses a simple linear search through the central
     directory, so it's not very fast.

     Alternately, you can iterate through all the files in an archive (using mz_zip_reader_get_num_files()) and
     retrieve detailed info on each file by calling mz_zip_reader_file_stat().

     - Archive creation: Use the "mz_zip_writer" functions. The ZIP writer immediately writes compressed file data
     to disk and builds an exact image of the central directory in memory. The central directory image is written
     all at once at the end of the archive file when the archive is finalized.

     The archive writer can optionally align each file's local header and file data to any power of 2 alignment,
     which can be useful when the archive will be read from optical media. Also, the writer supports placing
     arbitrary data blobs at the very beginning of ZIP archives. Archives written using either feature are still
     readable by any ZIP tool.

     - Archive appending: The simple way to add a single file to an archive is to call this function:

      mz_bool mz_zip_add_mem_to_archive_file_in_place(const char *pZip_filename, const char *pArchive_name,
        const void *pBuf, size_t buf_size, const void *pComment, mz_uint16 comment_size, mz_uint level_and_flags);

     The archive will be created if it doesn't already exist, otherwise it'll be appended to.
     Note the appending is done in-place and is not an atomic operation, so if something goes wrong
     during the operation it's possible the archive could be left without a central directory (although the local
     file headers and file data will be fine, so the archive will be recoverable).

     For more complex archive modification scenarios:
     1. The safest way is to use a mz_zip_reader to read the existing archive, cloning only those bits you want to
     preserve into a new archive using using the mz_zip_writer_add_from_zip_reader() function (which compiles the
     compressed file data as-is). When you're done, delete the old archive and rename the newly written archive, and
     you're done. This is safe but requires a bunch of temporary disk space or heap memory.

     2. Or, you can convert an mz_zip_reader in-place to an mz_zip_writer using mz_zip_writer_init_from_reader(),
     append new files as needed, then finalize the archive which will write an updated central directory to the
     original archive. (This is basically what mz_zip_add_mem_to_archive_file_in_place() does.) There's a
     possibility that the archive's central directory could be lost with this method if anything goes wrong, though.

     - ZIP archive support limitations:
     No zip64 or spanning support. Extraction functions can only handle unencrypted, stored or deflated files.
     Requires streams capable of seeking.

   * This is a header file library, like stb_image.c. To get only a header file, either cut and paste the
     below header, or create miniz.h, #define MINIZ_HEADER_FILE_ONLY, and then include miniz.c from it.

   * Important: For best perf. be sure to customize the below macros for your target platform:
     #define MINIZ_USE_UNALIGNED_LOADS_AND_STORES 1
     #define MINIZ_LITTLE_ENDIAN 1
     #define MINIZ_HAS_64BIT_REGISTERS 1

   * On platforms using glibc, Be sure to "#define _LARGEFILE64_SOURCE 1" before including miniz.c to ensure miniz
     uses the 64-bit variants: fopen64(), stat64(), etc. Otherwise you won't be able to process large files
     (i.e. 32-bit stat() fails for me on files > 0x7FFFFFFF bytes).
*/

#اگر_غیر_تعریف_شدہ MINIZ_سرخی_INCLUDED
#تعریف_کرو MINIZ_سرخی_INCLUDED

/*#include <stdlib.h>*/

// Defines to completely disable specific portions of miniz.c:
// If all macros here are defined the only functionality remaining will be CRC-32, adler-32, tinfl, and tdefl.

// Define MINIZ_NO_STDIO to disable all usage and any functions which rely on stdio for file I/O.
#تعریف_کرو MINIZ_NO_STDIO

// If MINIZ_NO_TIME is specified then the ZIP archive functions will not be able to get the current time, or
// get/set file times, and the C run-time funcs that get/set times won't be called.
// The current downside is the times written to your archives will be from 1979.
#تعریف_کرو MINIZ_NO_وقت

// Define MINIZ_NO_DEFLATE_APIS to disable all compression API's.
//#define MINIZ_NO_DEFLATE_APIS

// Define MINIZ_NO_INFLATE_APIS to disable all decompression API's.
#تعریف_کرو MINIZ_NO_INFLATE_APIS

// Define MINIZ_NO_ARCHIVE_APIS to disable all ZIP archive API's.
#تعریف_کرو MINIZ_NO_ARCHIVE_APIS

// Define MINIZ_NO_ARCHIVE_APIS to disable all writing related ZIP archive API's.
#تعریف_کرو MINIZ_NO_ARCHIVE_WRITING_APIS

// Define MINIZ_NO_ZLIB_APIS to remove all ZLIB-style compression/decompression API's.
#تعریف_کرو MINIZ_NO_ZLIB_APIS

// Define MINIZ_NO_ZLIB_COMPATIBLE_NAME to disable zlib names, to prevent conflicts against stock zlib.
#تعریف_کرو MINIZ_NO_ZLIB_COMPATIBLE_نام

// Define MINIZ_NO_MALLOC to disable all calls to malloc, free, and realloc.
// Note if MINIZ_NO_MALLOC is defined then the user must always provide custom user alloc/free/realloc
// callbacks to the zlib and archive API's, and a few stand-alone helper API's which don't provide custom user
// functions (such as tdefl_compress_mem_to_heap() and tinfl_decompress_mem_to_heap()) won't work.
//#define MINIZ_NO_MALLOC
#تعریف_کرو MINIZ_SDL_MALLOC

#اگر_تعریف_شدہ MINIZ_NO_INFLATE_APIS
#تعریف_کرو MINIZ_NO_ARCHIVE_APIS
#اگر_ختم

#اگر_تعریف_شدہ MINIZ_NO_DEFLATE_APIS
#تعریف_کرو MINIZ_NO_ARCHIVE_WRITING_APIS
#اگر_ختم

// Define MINIZ_STATIC_FUNCTIONS to make all functions static. You probably
// want this if you're using miniz in a library
#تعریف_کرو MINIZ_STATIC_FUNCTIONS

#اگر defined(__TINYC__) && (defined(__linux) || defined(__linux__))
  // TODO: Work around "error: include file 'sys\utime.h' when compiling with tcc on Linux
  #تعریف_کرو MINIZ_NO_وقت
#اگر_ختم

#اگر !defined(MINIZ_NO_وقت) && !defined(MINIZ_NO_ARCHIVE_APIS)
  #شامل <time.h>
#اگر_ختم

#اگر defined(_M_IX86) || defined(_M_X64) || defined(__i386__) || defined(__i386) || defined(__i486__) || defined(__i486) || defined(i386) || defined(__ia64__) || defined(__x86_64__)
// MINIZ_X86_OR_X64_CPU is only used to help set the below macros.
#تعریف_کرو MINIZ_X86_OR_X64_CPU 1
#اگر_ختم

#اگر_غیر_تعریف_شدہ MINIZ_LITTLE_ENDIAN /* if not defined by SDL */
#اگر (__BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__) || MINIZ_X86_OR_X64_CPU
// Set MINIZ_LITTLE_ENDIAN to 1 if the processor is little endian.
#تعریف_کرو MINIZ_LITTLE_ENDIAN 1
#اگر_ختم
#اگر_ختم // MINIZ_LITTLE_ENDIAN /* if not defined by SDL */

#اگر_غیر_تعریف_شدہ MINIZ_USE_UNALIGNED_LOADS_AND_STORES
#اگر MINIZ_X86_OR_X64_CPU
// Set MINIZ_USE_UNALIGNED_LOADS_AND_STORES to 1 on CPU's that permit efficient integer loads and stores from unaligned addresses.
#تعریف_کرو MINIZ_USE_UNALIGNED_LOADS_AND_STORES 1
#اگر_ختم
#اگر_ختم // MINIZ_USE_UNALIGNED_LOADS_AND_STORES

#اگر defined(_M_X64) || defined(_WIN64) || defined(__MINGW64__) || defined(_LP64) || defined(__LP64__) || defined(__ia64__) || defined(__x86_64__)
// Set MINIZ_HAS_64BIT_REGISTERS to 1 if operations on 64-bit integers are reasonably fast (and don't involve compiler generated calls to helper functions).
#تعریف_کرو MINIZ_HAS_64_ثنائی_ہندسہ_REGISTERS 1
#اگر_ختم

#اگر_تعریف_شدہ MINIZ_STATIC_FUNCTIONS
#تعریف_کرو MINIZ_STATIC ساکن
#ورنہ
#تعریف_کرو MINIZ_STATIC
#اگر_ختم

#اگر_تعریف_شدہ __cplusplus
خارجی "C" {
#اگر_ختم

// ------------------- zlib-style API Definitions.

// For more compatibility with zlib, miniz.c uses unsigned long for some parameters/struct members. Beware: mz_ulong can be either 32 or 64-bits!
قسمتعریف غیرعلامتی طویل mz_ulong;

// mz_free() internally uses the MZ_FREE() macro (which by default calls free() unless you've modified the MZ_MALLOC macro) to release a block allocated from the heap.
MINIZ_STATIC خالی mz_free(خالی *p);

#تعریف_کرو MZ_ADLER32_INIT (1)
// mz_adler32() returns the initial adler-32 value to use when called with ptr==NULL.
MINIZ_STATIC mz_ulong mz_adler32(mz_ulong adler, ثابت غیرعلامتی حرف *ptr, size_t buf_len);

#تعریف_کرو MZ_چکری_جانچ_32_INIT (0)
// mz_crc32() returns the initial CRC-32 value to use when called with ptr==NULL.
MINIZ_STATIC mz_ulong mz_چکری_جانچ_32(mz_ulong چکری_جانچ, ثابت غیرعلامتی حرف *ptr, size_t buf_len);

// Compression strategies.
شمار { MZ_DEFAULT_STRATEGY = 0, MZ_FILTERED = 1, MZ_HUFFMAN_ONLY = 2, MZ_RLE = 3, MZ_FIXED = 4 };

//طریقہ
#تعریف_کرو MZ_DEFLATED 8

#اگر_غیر_تعریف_شدہ MINIZ_NO_ZLIB_APIS

// Heap allocation callbacks.
// Note that mz_alloc_func parameter types purpsosely differ from zlib's: items/size is size_t, not unsigned long.
قسمتعریف خالی *(*mz_alloc_func)(خالی *opaque, size_t اشیاء, size_t سائز);
قسمتعریف خالی (*mz_free_func)(خالی *opaque, خالی *پتہ);
قسمتعریف خالی *(*mz_realloc_func)(خالی *opaque, خالی *پتہ, size_t اشیاء, size_t سائز);

#تعریف_کرو MZ_نسخہ          "9.1.15"
#تعریف_کرو MZ_VERNUM           0x91F0
#تعریف_کرو MZ_VER_MAJOR        9
#تعریف_کرو MZ_VER_MINOR        1
#تعریف_کرو MZ_VER_REVISION     15
#تعریف_کرو MZ_VER_SUBREVISION  0

// Flush values. For typical usage you only need MZ_NO_FLUSH and MZ_FINISH. The other values are for advanced use (refer to the zlib docs).
شمار { MZ_NO_FLUSH = 0, MZ_PARTIAL_FLUSH = 1, MZ_SYNC_FLUSH = 2, MZ_بھرا_FLUSH = 3, MZ_اختتام = 4, MZ_بلاک = 5 };

// Return status codes. MZ_PARAM_ERROR is non-standard.
شمار { MZ_OK = 0, MZ_دھارا_انتہا = 1, MZ_NEED_DICT = 2, MZ_ERRNO = -1, MZ_دھارا_ERROR = -2, MZ_ڈیٹا_ERROR = -3, MZ_MEM_ERROR = -4, MZ_BUF_ERROR = -5, MZ_نسخہ_ERROR = -6, MZ_PARAM_ERROR = -10000 };

// Compression levels: 0-9 are the standard zlib-style levels, 10 is best possible compression (not zlib compatible, and may be very slow), MZ_DEFAULT_COMPRESSION=MZ_DEFAULT_LEVEL.
شمار { MZ_NO_COMPRESSION = 0, MZ_بہترین_رفتار = 1, MZ_بہترین_COMPRESSION = 9, MZ_UBER_COMPRESSION = 10, MZ_DEFAULT_LEVEL = 6, MZ_DEFAULT_COMPRESSION = -1 };

// Window bits
#تعریف_کرو MZ_DEFAULT_کھڑکی_بٹ 15

ساخت mz_اندرونی_state;

// Compression/decompression stream struct.
قسمتعریف ساخت mz_دھارا_s
{
  ثابت غیرعلامتی حرف *اگلا_اندر;     // pointer to next byte to read
  غیرعلامتی صحیح avail_اندر;            // number of bytes available at next_in
  mz_ulong کل_اندر;                // total number of bytes consumed so far

  غیرعلامتی حرف *اگلا_برآمد;          // pointer to next byte to write
  غیرعلامتی صحیح avail_برآمد;           // number of bytes that can be written to next_out
  mz_ulong کل_برآمد;               // total number of bytes produced so far

  حرف *پیغام_2;                        // error msg (unused)
  ساخت mz_اندرونی_state *state;  // internal state, allocated by zalloc/zfree

  mz_alloc_func zalloc;             // optional heap allocation function (defaults to malloc)
  mz_free_func zfree;               // optional heap free function (defaults to free)
  خالی *opaque;                     // heap alloc function user pointer

  صحیح ڈیٹا_type;                    // data_type (unused)
  mz_ulong adler;                   // adler32 of the source or uncompressed data
  mz_ulong reserved;                // not used
} mz_دھارا;

قسمتعریف mz_دھارا *mz_streamp;

// Returns the version string of miniz.c.
MINIZ_STATIC ثابت حرف *mz_نسخہ(خالی);

#اگر_غیر_تعریف_شدہ MINIZ_NO_DEFLATE_APIS

// mz_deflateInit() initializes a compressor with default options:
// Parameters:
//  pStream must point to an initialized mz_stream struct.
//  level must be between [MZ_NO_COMPRESSION, MZ_BEST_COMPRESSION].
//  level 1 enables a specially optimized compression function that's been optimized purely for performance, not ratio.
//  (This special func. is currently only enabled when MINIZ_USE_UNALIGNED_LOADS_AND_STORES and MINIZ_LITTLE_ENDIAN are defined.)
// Return values:
//  MZ_OK on success.
//  MZ_STREAM_ERROR if the stream is bogus.
//  MZ_PARAM_ERROR if the input parameters are bogus.
//  MZ_MEM_ERROR on out of memory.
MINIZ_STATIC صحیح mz_deflateInit(mz_streamp p_دھارا, صحیح level);

// mz_deflateInit2() is like mz_deflate(), except with more control:
// Additional parameters:
//   method must be MZ_DEFLATED
//   window_bits must be MZ_DEFAULT_WINDOW_BITS (to wrap the deflate stream with zlib header/adler-32 footer) or -MZ_DEFAULT_WINDOW_BITS (raw deflate/no header or footer)
//   mem_level must be between [1, 9] (it's checked but ignored by miniz.c)
MINIZ_STATIC صحیح mz_deflateInit2(mz_streamp p_دھارا, صحیح level, صحیح طریقہ, صحیح کھڑکی_بٹ, صحیح mem_level, صحیح strategy);

// Quickly resets a compressor without having to reallocate anything. Same as calling mz_deflateEnd() followed by mz_deflateInit()/mz_deflateInit2().
MINIZ_STATIC صحیح mz_deflateReset(mz_streamp p_دھارا);

// mz_deflate() compresses the input to output, consuming as much of the input and producing as much output as possible.
// Parameters:
//   pStream is the stream to read from and write to. You must initialize/update the next_in, avail_in, next_out, and avail_out members.
//   flush may be MZ_NO_FLUSH, MZ_PARTIAL_FLUSH/MZ_SYNC_FLUSH, MZ_FULL_FLUSH, or MZ_FINISH.
// Return values:
//   MZ_OK on success (when flushing, or if more input is needed but not available, and/or there's more output to be written but the output buffer is full).
//   MZ_STREAM_END if all input has been consumed and all output bytes have been written. Don't call mz_deflate() on the stream anymore.
//   MZ_STREAM_ERROR if the stream is bogus.
//   MZ_PARAM_ERROR if one of the parameters is invalid.
//   MZ_BUF_ERROR if no forward progress is possible because the input and/or output buffers are empty. (Fill up the input buffer or free up some output space and try again.)
MINIZ_STATIC صحیح mz_deflate(mz_streamp p_دھارا, صحیح flush);

// mz_deflateEnd() deinitializes a compressor:
// Return values:
//  MZ_OK on success.
//  MZ_STREAM_ERROR if the stream is bogus.
MINIZ_STATIC صحیح mz_deflate_انتہا(mz_streamp p_دھارا);

// mz_deflateBound() returns a (very) conservative upper bound on the amount of data that could be generated by deflate(), assuming flush is set to only MZ_NO_FLUSH or MZ_FINISH.
MINIZ_STATIC mz_ulong mz_deflateBound(mz_streamp p_دھارا, mz_ulong ماخذ_len);

// Single-call compression functions mz_compress() and mz_compress2():
// Returns MZ_OK on success, or one of the error codes from mz_deflate() on failure.
MINIZ_STATIC صحیح mz_compress(غیرعلامتی حرف *pDest, mz_ulong *pDest_len, ثابت غیرعلامتی حرف *p_ماخذ, mz_ulong ماخذ_len);
MINIZ_STATIC صحیح mz_compress2(غیرعلامتی حرف *pDest, mz_ulong *pDest_len, ثابت غیرعلامتی حرف *p_ماخذ, mz_ulong ماخذ_len, صحیح level);

// mz_compressBound() returns a (very) conservative upper bound on the amount of data that could be generated by calling mz_compress().
MINIZ_STATIC mz_ulong mz_compressBound(mz_ulong ماخذ_len);

#اگر_ختم /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#اگر_غیر_تعریف_شدہ MINIZ_NO_INFLATE_APIS

// Initializes a decompressor.
MINIZ_STATIC صحیح mz_inflateInit(mz_streamp p_دھارا);

// mz_inflateInit2() is like mz_inflateInit() with an additional option that controls the window size and whether or not the stream has been wrapped with a zlib header/footer:
// window_bits must be MZ_DEFAULT_WINDOW_BITS (to parse zlib header/footer) or -MZ_DEFAULT_WINDOW_BITS (raw deflate).
MINIZ_STATIC صحیح mz_inflateInit2(mz_streamp p_دھارا, صحیح کھڑکی_بٹ);

// Decompresses the input stream to the output, consuming only as much of the input as needed, and writing as much to the output as possible.
// Parameters:
//   pStream is the stream to read from and write to. You must initialize/update the next_in, avail_in, next_out, and avail_out members.
//   flush may be MZ_NO_FLUSH, MZ_SYNC_FLUSH, or MZ_FINISH.
//   On the first call, if flush is MZ_FINISH it's assumed the input and output buffers are both sized large enough to decompress the entire stream in a single call (this is slightly faster).
//   MZ_FINISH implies that there are no more source bytes available beside what's already in the input buffer, and that the output buffer is large enough to hold the rest of the decompressed data.
// Return values:
//   MZ_OK on success. Either more input is needed but not available, and/or there's more output to be written but the output buffer is full.
//   MZ_STREAM_END if all needed input has been consumed and all output bytes have been written. For zlib streams, the adler-32 of the decompressed data has also been verified.
//   MZ_STREAM_ERROR if the stream is bogus.
//   MZ_DATA_ERROR if the deflate stream is invalid.
//   MZ_PARAM_ERROR if one of the parameters is invalid.
//   MZ_BUF_ERROR if no forward progress is possible because the input buffer is empty but the inflater needs more input to continue, or if the output buffer is not large enough. Call mz_inflate() again
//   with more input data, or with more room in the output buffer (except when using single call decompression, described above).
MINIZ_STATIC صحیح mz_inflate(mz_streamp p_دھارا, صحیح flush);

// Deinitializes a decompressor.
MINIZ_STATIC صحیح mz_inflate_انتہا(mz_streamp p_دھارا);

// Single-call decompression.
// Returns MZ_OK on success, or one of the error codes from mz_inflate() on failure.
MINIZ_STATIC صحیح mz_uncompress(غیرعلامتی حرف *pDest, mz_ulong *pDest_len, ثابت غیرعلامتی حرف *p_ماخذ, mz_ulong ماخذ_len);
#اگر_ختم /*#ifndef MINIZ_NO_INFLATE_APIS*/

// Returns a string description of the specified error code, or NULL if the error code is invalid.
MINIZ_STATIC ثابت حرف *mz_error(صحیح err);

// Redefine zlib-compatible names to miniz equivalents, so miniz.c can be used as a drop-in replacement for the subset of zlib that miniz.c supports.
// Define MINIZ_NO_ZLIB_COMPATIBLE_NAMES to disable zlib-compatibility if you use zlib in the same project.
#اگر_غیر_تعریف_شدہ MINIZ_NO_ZLIB_COMPATIBLE_نام
  قسمتعریف غیرعلامتی حرف Byte;
  قسمتعریف غیرعلامتی صحیح uInt;
  قسمتعریف mz_ulong uLong;
  قسمتعریف Byte Bytef;
  قسمتعریف uInt uIntf;
  قسمتعریف حرف charf;
  قسمتعریف صحیح intf;
  قسمتعریف خالی *voidpf;
  قسمتعریف uLong uLongf;
  قسمتعریف خالی *voidp;
  قسمتعریف خالی *ثابت voidpc;
  #تعریف_کرو Z_NULL                0
  #تعریف_کرو Z_NO_FLUSH            MZ_NO_FLUSH
  #تعریف_کرو Z_PARTIAL_FLUSH       MZ_PARTIAL_FLUSH
  #تعریف_کرو Z_SYNC_FLUSH          MZ_SYNC_FLUSH
  #تعریف_کرو Z_بھرا_FLUSH          MZ_بھرا_FLUSH
  #تعریف_کرو Z_اختتام              MZ_اختتام
  #تعریف_کرو Z_بلاک               MZ_بلاک
  #تعریف_کرو Z_OK                  MZ_OK
  #تعریف_کرو Z_دھارا_انتہا          MZ_دھارا_انتہا
  #تعریف_کرو Z_NEED_DICT           MZ_NEED_DICT
  #تعریف_کرو Z_ERRNO               MZ_ERRNO
  #تعریف_کرو Z_دھارا_ERROR        MZ_دھارا_ERROR
  #تعریف_کرو Z_ڈیٹا_ERROR          MZ_ڈیٹا_ERROR
  #تعریف_کرو Z_MEM_ERROR           MZ_MEM_ERROR
  #تعریف_کرو Z_BUF_ERROR           MZ_BUF_ERROR
  #تعریف_کرو Z_نسخہ_ERROR       MZ_نسخہ_ERROR
  #تعریف_کرو Z_PARAM_ERROR         MZ_PARAM_ERROR
  #تعریف_کرو Z_NO_COMPRESSION      MZ_NO_COMPRESSION
  #تعریف_کرو Z_بہترین_رفتار          MZ_بہترین_رفتار
  #تعریف_کرو Z_بہترین_COMPRESSION    MZ_بہترین_COMPRESSION
  #تعریف_کرو Z_DEFAULT_COMPRESSION MZ_DEFAULT_COMPRESSION
  #تعریف_کرو Z_DEFAULT_STRATEGY    MZ_DEFAULT_STRATEGY
  #تعریف_کرو Z_FILTERED            MZ_FILTERED
  #تعریف_کرو Z_HUFFMAN_ONLY        MZ_HUFFMAN_ONLY
  #تعریف_کرو Z_RLE                 MZ_RLE
  #تعریف_کرو Z_FIXED               MZ_FIXED
  #تعریف_کرو Z_DEFLATED            MZ_DEFLATED
  #تعریف_کرو Z_DEFAULT_کھڑکی_بٹ MZ_DEFAULT_کھڑکی_بٹ
  #تعریف_کرو alloc_func            mz_alloc_func
  #تعریف_کرو free_func             mz_free_func
  #تعریف_کرو اندرونی_state        mz_اندرونی_state
  #تعریف_کرو z_دھارا              mz_دھارا
#اگر_غیر_تعریف_شدہ MINIZ_NO_DEFLATE_APIS
  #تعریف_کرو deflateInit           mz_deflateInit
  #تعریف_کرو deflateInit2          mz_deflateInit2
  #تعریف_کرو deflateReset          mz_deflateReset
  #تعریف_کرو deflate               mz_deflate
  #تعریف_کرو deflate_انتہا            mz_deflate_انتہا
  #تعریف_کرو deflateBound          mz_deflateBound
  #تعریف_کرو compress              mz_compress
  #تعریف_کرو compress2             mz_compress2
  #تعریف_کرو compressBound         mz_compressBound
#اگر_ختم /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#اگر_غیر_تعریف_شدہ MINIZ_NO_INFLATE_APIS
  #تعریف_کرو inflateInit           mz_inflateInit
  #تعریف_کرو inflateInit2          mz_inflateInit2
  #تعریف_کرو inflate               mz_inflate
  #تعریف_کرو inflate_انتہا            mz_inflate_انتہا
  #تعریف_کرو uncompress            mz_uncompress
#اگر_ختم /*#ifndef MINIZ_NO_INFLATE_APIS*/
  #تعریف_کرو چکری_جانچ_32                 mz_چکری_جانچ_32
  #تعریف_کرو adler32               mz_adler32
  #تعریف_کرو MAX_WBITS             15
  #تعریف_کرو MAX_MEM_LEVEL         9
  #تعریف_کرو zError                mz_error
  #تعریف_کرو ZLIB_نسخہ          MZ_نسخہ
  #تعریف_کرو ZLIB_VERNUM           MZ_VERNUM
  #تعریف_کرو ZLIB_VER_MAJOR        MZ_VER_MAJOR
  #تعریف_کرو ZLIB_VER_MINOR        MZ_VER_MINOR
  #تعریف_کرو ZLIB_VER_REVISION     MZ_VER_REVISION
  #تعریف_کرو ZLIB_VER_SUBREVISION  MZ_VER_SUBREVISION
  #تعریف_کرو zlib_نسخہ           mz_نسخہ
  #تعریف_کرو zlib_نسخہ_2          mz_نسخہ()
#اگر_ختم // #ifndef MINIZ_NO_ZLIB_COMPATIBLE_NAMES

#اگر_ختم // MINIZ_NO_ZLIB_APIS

// ------------------- Types and macros

قسمتعریف غیرعلامتی حرف mz_uint8;
قسمتعریف علامتی مختصر mz_int16;
قسمتعریف غیرعلامتی مختصر mz_uint16;
قسمتعریف غیرعلامتی صحیح mz_uint32;
قسمتعریف غیرعلامتی صحیح mz_uint;
قسمتعریف طویل طویل mz_int64;
قسمتعریف غیرعلامتی طویل طویل mz_uint64;
قسمتعریف صحیح mz_bool;

#تعریف_کرو MZ_FALSE (0)
#تعریف_کرو MZ_TRUE (1)

// An attempt to work around MSVC's spammy "warning C4127: conditional expression is constant" message.
#اگر_تعریف_شدہ _MSC_VER
   #تعریف_کرو MZ_MACRO_انتہا جب (0, 0)
#ورنہ
   #تعریف_کرو MZ_MACRO_انتہا جب (0)
#اگر_ختم

// ------------------- ZIP archive reading/writing

#اگر_غیر_تعریف_شدہ MINIZ_NO_ARCHIVE_APIS

شمار
{
  MZ_ZIP_MAX_IO_BUF_سائز = 64*1024,
  MZ_ZIP_MAX_ARCHIVE_FILENAME_سائز = 260,
  MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_سائز = 256
};

قسمتعریف ساخت
{
  mz_uint32 m_file_اشاریہ;
  mz_uint32 m_central_dir_ofs;
  mz_uint16 m_نسخہ_made_by;
  mz_uint16 m_نسخہ_needed;
  mz_uint16 m_ثنائی_ہندسہ_flag;
  mz_uint16 m_طریقہ;
#اگر_غیر_تعریف_شدہ MINIZ_NO_وقت
  وقت_t m_وقت;
#اگر_ختم
  mz_uint32 m_چکری_جانچ_32;
  mz_uint64 m_comp_سائز;
  mz_uint64 m_uncomp_سائز;
  mz_uint16 m_اندرونی_attr;
  mz_uint32 m_external_attr;
  mz_uint64 m_local_سرخی_ofs;
  mz_uint32 m_comment_سائز;
  حرف m_filename[MZ_ZIP_MAX_ARCHIVE_FILENAME_سائز];
  حرف m_comment[MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_سائز];
} mz_zip_archive_file_stat;

قسمتعریف size_t (*mz_file_read_func)(خالی *pOpaque, mz_uint64 file_ofs, خالی *pBuf, size_t n);
قسمتعریف size_t (*mz_file_write_func)(خالی *pOpaque, mz_uint64 file_ofs, ثابت خالی *pBuf, size_t n);

ساخت mz_zip_اندرونی_state_لیبل;
قسمتعریف ساخت mz_zip_اندرونی_state_لیبل mz_zip_اندرونی_state;

قسمتعریف شمار
{
  MZ_ZIP_منوال_INVALID = 0,
  MZ_ZIP_منوال_READING = 1,
  MZ_ZIP_منوال_WRITING = 2,
  MZ_ZIP_منوال_WRITING_HAS_BEEN_FINALIZED = 3
} mz_zip_منوال;

قسمتعریف ساخت mz_zip_archive_لیبل
{
  mz_uint64 m_archive_سائز;
  mz_uint64 m_central_directory_file_ofs;
  mz_uint m_کل_files;
  mz_zip_منوال m_zip_منوال;

  mz_uint m_file_انحراف_alignment;

  mz_alloc_func m_pAlloc;
  mz_free_func m_pFree;
  mz_realloc_func m_pRealloc;
  خالی *m_pAlloc_opaque;

  mz_file_read_func m_pRead;
  mz_file_write_func m_pWrite;
  خالی *m_pIO_opaque;

  mz_zip_اندرونی_state *m_pState;

} mz_zip_archive;

قسمتعریف شمار
{
  MZ_ZIP_FLAG_CASE_SENSITIVE                = 0x0100,
  MZ_ZIP_FLAG_IGNORE_راستہ                   = 0x0200,
  MZ_ZIP_FLAG_COMPRESSED_ڈیٹا               = 0x0400,
  MZ_ZIP_FLAG_DO_NOT_ترتیب_دو_CENTRAL_DIRECTORY = 0x0800
} mz_zip_flags;

// ZIP archive reading

// Inits a ZIP archive reader.
// These functions read and validate the archive's central directory.
MINIZ_STATIC mz_bool mz_zip_reader_init(mz_zip_archive *pZip, mz_uint64 سائز, mz_uint32 flags);
MINIZ_STATIC mz_bool mz_zip_reader_init_mem(mz_zip_archive *pZip, ثابت خالی *pMem, size_t سائز, mz_uint32 flags);

#اگر_غیر_تعریف_شدہ MINIZ_NO_STDIO
MINIZ_STATIC mz_bool mz_zip_reader_init_file(mz_zip_archive *pZip, ثابت حرف *pFilename, mz_uint32 flags);
#اگر_ختم

// Returns the total number of files in the archive.
MINIZ_STATIC mz_uint mz_zip_reader_get_عدد_files(mz_zip_archive *pZip);

// Returns detailed information about an archive file entry.
MINIZ_STATIC mz_bool mz_zip_reader_file_stat(mz_zip_archive *pZip, mz_uint file_اشاریہ, mz_zip_archive_file_stat *pStat);

// Determines if an archive file entry is a directory entry.
MINIZ_STATIC mz_bool mz_zip_reader_is_file_a_directory(mz_zip_archive *pZip, mz_uint file_اشاریہ);
MINIZ_STATIC mz_bool mz_zip_reader_is_file_encrypted(mz_zip_archive *pZip, mz_uint file_اشاریہ);

// Retrieves the filename of an archive file entry.
// Returns the number of bytes written to pFilename, or if filename_buf_size is 0 this function returns the number of bytes needed to fully store the filename.
MINIZ_STATIC mz_uint mz_zip_reader_get_filename(mz_zip_archive *pZip, mz_uint file_اشاریہ, حرف *pFilename, mz_uint filename_buf_سائز);

// Attempts to locates a file in the archive's central directory.
// Valid flags: MZ_ZIP_FLAG_CASE_SENSITIVE, MZ_ZIP_FLAG_IGNORE_PATH
// Returns -1 if the file cannot be found.
MINIZ_STATIC صحیح mz_zip_reader_locate_file(mz_zip_archive *pZip, ثابت حرف *pName, ثابت حرف *pComment, mz_uint flags);

// Extracts a archive file to a memory buffer using no memory allocation.
MINIZ_STATIC mz_bool mz_zip_reader_نکالو_مقصد_mem_no_alloc(mz_zip_archive *pZip, mz_uint file_اشاریہ, خالی *pBuf, size_t buf_سائز_2, mz_uint flags, خالی *pUser_read_buf, size_t user_read_buf_سائز);
MINIZ_STATIC mz_bool mz_zip_reader_نکالو_file_مقصد_mem_no_alloc(mz_zip_archive *pZip, ثابت حرف *pFilename, خالی *pBuf, size_t buf_سائز_2, mz_uint flags, خالی *pUser_read_buf, size_t user_read_buf_سائز);

// Extracts a archive file to a memory buffer.
MINIZ_STATIC mz_bool mz_zip_reader_نکالو_مقصد_mem(mz_zip_archive *pZip, mz_uint file_اشاریہ, خالی *pBuf, size_t buf_سائز_2, mz_uint flags);
MINIZ_STATIC mz_bool mz_zip_reader_نکالو_file_مقصد_mem(mz_zip_archive *pZip, ثابت حرف *pFilename, خالی *pBuf, size_t buf_سائز_2, mz_uint flags);

// Extracts a archive file to a dynamically allocated heap buffer.
MINIZ_STATIC خالی *mz_zip_reader_نکالو_مقصد_ڈھیر(mz_zip_archive *pZip, mz_uint file_اشاریہ, size_t *p_سائز, mz_uint flags);
MINIZ_STATIC خالی *mz_zip_reader_نکالو_file_مقصد_ڈھیر(mz_zip_archive *pZip, ثابت حرف *pFilename, size_t *p_سائز, mz_uint flags);

// Extracts a archive file using a callback function to output the file's data.
MINIZ_STATIC mz_bool mz_zip_reader_نکالو_مقصد_callback(mz_zip_archive *pZip, mz_uint file_اشاریہ, mz_file_write_func pCallback, خالی *pOpaque, mz_uint flags);
MINIZ_STATIC mz_bool mz_zip_reader_نکالو_file_مقصد_callback(mz_zip_archive *pZip, ثابت حرف *pFilename, mz_file_write_func pCallback, خالی *pOpaque, mz_uint flags);

#اگر_غیر_تعریف_شدہ MINIZ_NO_STDIO
// Extracts a archive file to a disk file and sets its last accessed and modified times.
// This function only extracts files, not archive directory records.
MINIZ_STATIC mz_bool mz_zip_reader_نکالو_مقصد_file(mz_zip_archive *pZip, mz_uint file_اشاریہ, ثابت حرف *pDst_filename, mz_uint flags);
MINIZ_STATIC mz_bool mz_zip_reader_نکالو_file_مقصد_file(mz_zip_archive *pZip, ثابت حرف *pArchive_filename, ثابت حرف *pDst_filename, mz_uint flags);
#اگر_ختم

// Ends archive reading, freeing all allocations, and closing the input archive file if mz_zip_reader_init_file() was used.
MINIZ_STATIC mz_bool mz_zip_reader_انتہا(mz_zip_archive *pZip);

// ZIP archive writing

#اگر_غیر_تعریف_شدہ MINIZ_NO_ARCHIVE_WRITING_APIS

// Inits a ZIP archive writer.
MINIZ_STATIC mz_bool mz_zip_writer_init(mz_zip_archive *pZip, mz_uint64 existing_سائز);
MINIZ_STATIC mz_bool mz_zip_writer_init_ڈھیر(mz_zip_archive *pZip, size_t سائز_مقصد_reserve_at_beginning, size_t initial_تخصیص_سائز);

#اگر_غیر_تعریف_شدہ MINIZ_NO_STDIO
MINIZ_STATIC mz_bool mz_zip_writer_init_file(mz_zip_archive *pZip, ثابت حرف *pFilename, mz_uint64 سائز_مقصد_reserve_at_beginning);
#اگر_ختم

// Converts a ZIP archive reader object into a writer object, to allow efficient in-place file appends to occur on an existing archive.
// For archives opened using mz_zip_reader_init_file, pFilename must be the archive's filename so it can be reopened for writing. If the file can't be reopened, mz_zip_reader_end() will be called.
// For archives opened using mz_zip_reader_init_mem, the memory block must be growable using the realloc callback (which defaults to realloc unless you've overridden it).
// Finally, for archives opened using mz_zip_reader_init, the mz_zip_archive's user provided m_pWrite function cannot be NULL.
// Note: In-place archive modification is not recommended unless you know what you're doing, because if execution stops or something goes wrong before
// the archive is finalized the file's central directory will be hosed.
MINIZ_STATIC mz_bool mz_zip_writer_init_from_reader(mz_zip_archive *pZip, ثابت حرف *pFilename);

// Adds the contents of a memory buffer to an archive. These functions record the current local time into the archive.
// To add a directory entry, call this method with an archive name ending in a forwardslash with empty buffer.
// level_and_flags - compression level (0-10, see MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or just set to MZ_DEFAULT_COMPRESSION.
MINIZ_STATIC mz_bool mz_zip_writer_جوڑو_mem(mz_zip_archive *pZip, ثابت حرف *pArchive_name, ثابت خالی *pBuf, size_t buf_سائز_2, mz_uint level_and_flags);
MINIZ_STATIC mz_bool mz_zip_writer_جوڑو_mem_ex(mz_zip_archive *pZip, ثابت حرف *pArchive_name, ثابت خالی *pBuf, size_t buf_سائز_2, ثابت خالی *pComment, mz_uint16 comment_سائز, mz_uint level_and_flags, mz_uint64 uncomp_سائز, mz_uint32 uncomp_چکری_جانچ_32);

#اگر_غیر_تعریف_شدہ MINIZ_NO_STDIO
// Adds the contents of a disk file to an archive. This function also records the disk file's modified time into the archive.
// level_and_flags - compression level (0-10, see MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or just set to MZ_DEFAULT_COMPRESSION.
MINIZ_STATIC mz_bool mz_zip_writer_جوڑو_file(mz_zip_archive *pZip, ثابت حرف *pArchive_name, ثابت حرف *pSrc_filename, ثابت خالی *pComment, mz_uint16 comment_سائز, mz_uint level_and_flags);
#اگر_ختم

// Adds a file to an archive by fully cloning the data from another archive.
// This function fully clones the source file's compressed data (no recompression), along with its full filename, extra data, and comment fields.
MINIZ_STATIC mz_bool mz_zip_writer_جوڑو_from_zip_reader(mz_zip_archive *pZip, mz_zip_archive *p_ماخذ_zip, mz_uint file_اشاریہ);

// Finalizes the archive by writing the central directory records followed by the end of central directory record.
// After an archive is finalized, the only valid call on the mz_zip_archive struct is mz_zip_writer_end().
// An archive must be manually finalized by calling this function for it to be valid.
MINIZ_STATIC mz_bool mz_zip_writer_finalize_archive(mz_zip_archive *pZip);
MINIZ_STATIC mz_bool mz_zip_writer_finalize_ڈھیر_archive(mz_zip_archive *pZip, خالی **pBuf, size_t *p_سائز);

// Ends archive writing, freeing all allocations, and closing the output file if mz_zip_writer_init_file() was used.
// Note for the archive to be valid, it must have been finalized before ending.
MINIZ_STATIC mz_bool mz_zip_writer_انتہا(mz_zip_archive *pZip);

// Misc. high-level helper functions:

// mz_zip_add_mem_to_archive_file_in_place() efficiently (but not atomically) appends a memory blob to a ZIP archive.
// level_and_flags - compression level (0-10, see MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or just set to MZ_DEFAULT_COMPRESSION.
MINIZ_STATIC mz_bool mz_zip_جوڑو_mem_مقصد_archive_file_اندر_رکھو(ثابت حرف *pZip_filename, ثابت حرف *pArchive_name, ثابت خالی *pBuf, size_t buf_سائز_2, ثابت خالی *pComment, mz_uint16 comment_سائز, mz_uint level_and_flags);

// Reads a single file from an archive into a heap block.
// Returns NULL on failure.
MINIZ_STATIC خالی *mz_zip_نکالو_archive_file_مقصد_ڈھیر(ثابت حرف *pZip_filename, ثابت حرف *pArchive_name, size_t *p_سائز, mz_uint zip_flags);

#اگر_ختم // #ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

#اگر_ختم // #ifndef MINIZ_NO_ARCHIVE_APIS

// ------------------- Low-level Decompression API Definitions
#اگر_غیر_تعریف_شدہ MINIZ_NO_INFLATE_APIS

// Decompression flags used by tinfl_decompress().
// TINFL_FLAG_PARSE_ZLIB_HEADER: If set, the input has a valid zlib header and ends with an adler32 checksum (it's a valid zlib stream). Otherwise, the input is a raw deflate stream.
// TINFL_FLAG_HAS_MORE_INPUT: If set, there are more input bytes available beyond the end of the supplied input buffer. If clear, the input buffer contains all remaining input.
// TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF: If set, the output buffer is large enough to hold the entire decompressed stream. If clear, the output buffer is at least the size of the dictionary (typically 32KB).
// TINFL_FLAG_COMPUTE_ADLER32: Force adler-32 checksum computation of the decompressed bytes.
شمار
{
  TINFL_FLAG_PARSE_ZLIB_سرخی = 1,
  TINFL_FLAG_HAS_مزید_داخلہ = 2,
  TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF = 4,
  TINFL_FLAG_COMPUTE_ADLER32 = 8
};

// High level decompression functions:
// tinfl_decompress_mem_to_heap() decompresses a block in memory to a heap block allocated via malloc().
// On entry:
//  pSrc_buf, src_buf_len: Pointer and size of the Deflate or zlib source data to decompress.
// On return:
//  Function returns a pointer to the decompressed data, or NULL on failure.
//  *pOut_len will be set to the decompressed data's size, which could be larger than src_buf_len on uncompressible data.
//  The caller must call mz_free() on the returned block when it's no longer needed.
MINIZ_STATIC خالی *tinfl_decompress_mem_مقصد_ڈھیر(ثابت خالی *pSrc_buf, size_t src_buf_len, size_t *p_برآمد_len, صحیح flags);

// tinfl_decompress_mem_to_mem() decompresses a block in memory to another block in memory.
// Returns TINFL_DECOMPRESS_MEM_TO_MEM_FAILED on failure, or the number of bytes written on success.
#تعریف_کرو TINFL_DECOMPRESS_MEM_مقصد_MEM_FAILED ((size_t)(-1))
MINIZ_STATIC size_t tinfl_decompress_mem_مقصد_mem(خالی *p_برآمد_buf, size_t برآمد_buf_len, ثابت خالی *pSrc_buf, size_t src_buf_len, صحیح flags);

// tinfl_decompress_mem_to_callback() decompresses a block in memory to an internal 32KB buffer, and a user provided callback function will be called to flush the buffer.
// Returns 1 on success or 0 on failure.
قسمتعریف صحیح (*tinfl_put_buf_func_ptr)(ثابت خالی* pBuf, صحیح len, خالی *pUser);
MINIZ_STATIC صحیح tinfl_decompress_mem_مقصد_callback(ثابت خالی *p_اندر_buf, size_t *p_اندر_buf_سائز, tinfl_put_buf_func_ptr pPut_buf_func, خالی *pPut_buf_user, صحیح flags);

ساخت tinfl_decompressor_لیبل; قسمتعریف ساخت tinfl_decompressor_لیبل tinfl_decompressor;

// Max size of LZ dictionary.
#تعریف_کرو TINFL_LZ_DICT_سائز 32768

// Return status.
قسمتعریف شمار
{
  TINFL_حالت_BAD_PARAM = -3,
  TINFL_حالت_ADLER32_MISMATCH = -2,
  TINFL_حالت_FAILED = -1,
  TINFL_حالت_مکمل = 0,
  TINFL_حالت_NEEDS_مزید_داخلہ = 1,
  TINFL_حالت_HAS_مزید_OUTPUT = 2
} tinfl_حالت;

// Initializes the decompressor to its initial state.
#تعریف_کرو tinfl_init(r) کرو { (r)->m_state = 0; } MZ_MACRO_انتہا
#تعریف_کرو tinfl_get_adler32(r) (r)->m_check_adler32

// Main low-level decompressor coroutine function. This is the only function actually needed for decompression. All the other functions are just high-level helpers for improved usability.
// This is a universal API, i.e. it can be used as a building block to build any desired higher level decompression API. In the limit case, it can be called once per every byte input or output.
MINIZ_STATIC tinfl_حالت tinfl_decompress(tinfl_decompressor *r, ثابت mz_uint8 *p_اندر_buf_اگلا, size_t *p_اندر_buf_سائز, mz_uint8 *p_برآمد_buf_آغاز, mz_uint8 *p_برآمد_buf_اگلا, size_t *p_برآمد_buf_سائز, ثابت mz_uint32 decomp_flags);

// Internal/private bits follow.
شمار
{
  TINFL_MAX_HUFF_TABLES = 3, TINFL_MAX_HUFF_SYMBOLS_0 = 288, TINFL_MAX_HUFF_SYMBOLS_1 = 32, TINFL_MAX_HUFF_SYMBOLS_2 = 19,
  TINFL_FAST_LOOKUP_بٹ = 10, TINFL_FAST_LOOKUP_سائز = 1 << TINFL_FAST_LOOKUP_بٹ
};

قسمتعریف ساخت
{
  mz_uint8 m_رمز_سائز[TINFL_MAX_HUFF_SYMBOLS_0];
  mz_int16 m_look_اوپر[TINFL_FAST_LOOKUP_سائز], m_درخت[TINFL_MAX_HUFF_SYMBOLS_0 * 2];
} tinfl_huff_جدول;

#اگر MINIZ_HAS_64_ثنائی_ہندسہ_REGISTERS
  #تعریف_کرو TINFL_USE_64_ثنائی_ہندسہ_BITBUF 1
#اگر_ختم

#اگر TINFL_USE_64_ثنائی_ہندسہ_BITBUF
  قسمتعریف mz_uint64 tinfl_ثنائی_ہندسہ_buf_t;
  #تعریف_کرو TINFL_BITBUF_سائز (64)
#ورنہ
  قسمتعریف mz_uint32 tinfl_ثنائی_ہندسہ_buf_t;
  #تعریف_کرو TINFL_BITBUF_سائز (32)
#اگر_ختم

ساخت tinfl_decompressor_لیبل
{
  mz_uint32 m_state, m_عدد_بٹ, m_zhdr0, m_zhdr1, m_z_adler32, m_final, m_type, m_check_adler32, m_dist, m_شمار, m_عدد_extra, m_جدول_sizes[TINFL_MAX_HUFF_TABLES];
  tinfl_ثنائی_ہندسہ_buf_t m_ثنائی_ہندسہ_buf;
  size_t m_dist_from_برآمد_buf_آغاز;
  tinfl_huff_جدول m_tables[TINFL_MAX_HUFF_TABLES];
  mz_uint8 m_raw_سرخی[4], m_len_codes[TINFL_MAX_HUFF_SYMBOLS_0 + TINFL_MAX_HUFF_SYMBOLS_1 + 137];
};
#اگر_ختم /*#ifndef MINIZ_NO_INFLATE_APIS*/

// ------------------- Low-level Compression API Definitions
#اگر_غیر_تعریف_شدہ MINIZ_NO_DEFLATE_APIS

// Set TDEFL_LESS_MEMORY to 1 to use less memory (compression will be slightly slower, and raw/dynamic blocks will be output more frequently).
#تعریف_کرو TDEFL_LESS_حافظہ 0

// tdefl_init() compression flags logically OR'd together (low 12 bits contain the max. number of probes per dictionary search):
// TDEFL_DEFAULT_MAX_PROBES: The compressor defaults to 128 dictionary probes per dictionary search. 0=Huffman only, 1=Huffman+LZ (fastest/crap compression), 4095=Huffman+LZ (slowest/best compression).
شمار
{
  TDEFL_HUFFMAN_ONLY = 0, TDEFL_DEFAULT_MAX_PROBES = 128, TDEFL_MAX_PROBES_نقاب = 0xFFF
};

// TDEFL_WRITE_ZLIB_HEADER: If set, the compressor outputs a zlib header before the deflate data, and the Adler-32 of the source data at the end. Otherwise, you'll get raw deflate data.
// TDEFL_COMPUTE_ADLER32: Always compute the adler-32 of the input data (even when not writing zlib headers).
// TDEFL_GREEDY_PARSING_FLAG: Set to use faster greedy parsing, instead of more efficient lazy parsing.
// TDEFL_NONDETERMINISTIC_PARSING_FLAG: Enable to decrease the compressor's initialization time to the minimum, but the output may vary from run to run given the same input (depending on the contents of memory).
// TDEFL_RLE_MATCHES: Only look for RLE matches (matches with a distance of 1)
// TDEFL_FILTER_MATCHES: Discards matches <= 5 chars if enabled.
// TDEFL_FORCE_ALL_STATIC_BLOCKS: Disable usage of optimized Huffman tables.
// TDEFL_FORCE_ALL_RAW_BLOCKS: Only use raw (uncompressed) deflate blocks.
// The low 12 bits are reserved to control the max # of hash probes per dictionary lookup (see TDEFL_MAX_PROBES_MASK).
شمار
{
  TDEFL_WRITE_ZLIB_سرخی             = 0x01000,
  TDEFL_COMPUTE_ADLER32               = 0x02000,
  TDEFL_GREEDY_PARSING_FLAG           = 0x04000,
  TDEFL_NONDETERMINISTIC_PARSING_FLAG = 0x08000,
  TDEFL_RLE_MATCHES                   = 0x10000,
  TDEFL_FILTER_MATCHES                = 0x20000,
  TDEFL_FORCE_ALL_STATIC_بلاکیں       = 0x40000,
  TDEFL_FORCE_ALL_RAW_بلاکیں          = 0x80000
};

#اگر_غیر_تعریف_شدہ MINIZ_SDL_NOUNUSED
// High level compression functions:
// tdefl_compress_mem_to_heap() compresses a block in memory to a heap block allocated via malloc().
// On entry:
//  pSrc_buf, src_buf_len: Pointer and size of source block to compress.
//  flags: The max match finder probes (default is 128) logically OR'd against the above flags. Higher probes are slower but improve compression.
// On return:
//  Function returns a pointer to the compressed data, or NULL on failure.
//  *pOut_len will be set to the compressed data's size, which could be larger than src_buf_len on uncompressible data.
//  The caller must free() the returned block when it's no longer needed.
MINIZ_STATIC خالی *tdefl_compress_mem_مقصد_ڈھیر(ثابت خالی *pSrc_buf, size_t src_buf_len, size_t *p_برآمد_len, صحیح flags);

// tdefl_compress_mem_to_mem() compresses a block in memory to another block in memory.
// Returns 0 on failure.
MINIZ_STATIC size_t tdefl_compress_mem_مقصد_mem(خالی *p_برآمد_buf, size_t برآمد_buf_len, ثابت خالی *pSrc_buf, size_t src_buf_len, صحیح flags);
#اگر_ختم /* MINIZ_SDL_NOUNUSED */

// Compresses an image to a compressed PNG file in memory.
// On entry:
//  pImage, w, h, and num_chans describe the image to compress. num_chans may be 1, 2, 3, or 4.
//  The image pitch in bytes per scanline will be w*num_chans. The leftmost pixel on the top scanline is stored first in memory.
//  level may range from [0,10], use MZ_NO_COMPRESSION, MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc. or a decent default is MZ_DEFAULT_LEVEL
//  If flip is true, the image will be flipped on the Y axis (useful for OpenGL apps).
// On return:
//  Function returns a pointer to the compressed data, or NULL on failure.
//  *pLen_out will be set to the size of the PNG image file.
//  The caller must mz_free() the returned heap block (which will typically be larger than *pLen_out) when it's no longer needed.
MINIZ_STATIC خالی *tdefl_write_image_مقصد_png_file_اندر_حافظہ_ex(ثابت خالی *pImage, صحیح w, صحیح h, صحیح عدد_chans, صحیح bpl, size_t *p_Len_برآمد, mz_uint level, mz_bool flip, mz_uint8 *plte, صحیح plte_سائز, mz_uint8 *trns, صحیح trns_سائز);
#اگر_غیر_تعریف_شدہ MINIZ_SDL_NOUNUSED
MINIZ_STATIC خالی *tdefl_write_image_مقصد_png_file_اندر_حافظہ(ثابت خالی *pImage, صحیح w, صحیح h, صحیح عدد_chans, صحیح bpl, size_t *p_Len_برآمد);
#اگر_ختم

// Output stream interface. The compressor uses this interface to write compressed data. It'll typically be called TDEFL_OUT_BUF_SIZE at a time.
قسمتعریف mz_bool (*tdefl_put_buf_func_ptr)(ثابت خالی* pBuf, صحیح len, خالی *pUser);

#اگر_غیر_تعریف_شدہ MINIZ_SDL_NOUNUSED
// tdefl_compress_mem_to_output() compresses a block to an output stream. The above helpers use this function internally.
MINIZ_STATIC mz_bool tdefl_compress_mem_مقصد_output(ثابت خالی *pBuf, size_t buf_len, tdefl_put_buf_func_ptr pPut_buf_func, خالی *pPut_buf_user, صحیح flags);
#اگر_ختم

//enum { TDEFL_MAX_HUFF_TABLES = 3, TDEFL_MAX_HUFF_SYMBOLS_0 = 288, TDEFL_MAX_HUFF_SYMBOLS_1 = 32, TDEFL_MAX_HUFF_SYMBOLS_2 = 19, TDEFL_LZ_DICT_SIZE = 32768, TDEFL_LZ_DICT_SIZE_MASK = TDEFL_LZ_DICT_SIZE - 1, TDEFL_MIN_MATCH_LEN = 3, TDEFL_MAX_MATCH_LEN = 258 };
#تعریف_کرو TDEFL_MAX_HUFF_TABLES	3
#تعریف_کرو TDEFL_MAX_HUFF_SYMBOLS_0 288
#تعریف_کرو TDEFL_MAX_HUFF_SYMBOLS_1 32
#تعریف_کرو TDEFL_MAX_HUFF_SYMBOLS_2 19
#تعریف_کرو TDEFL_LZ_DICT_سائز 32768
#تعریف_کرو TDEFL_LZ_DICT_سائز_نقاب	( TDEFL_LZ_DICT_سائز - 1 )
#تعریف_کرو TDEFL_MIN_مطابقت_LEN	3
#تعریف_کرو TDEFL_MAX_مطابقت_LEN 258

// TDEFL_OUT_BUF_SIZE MUST be large enough to hold a single entire compressed output block (using static/fixed Huffman codes).
#اگر TDEFL_LESS_حافظہ
شمار { TDEFL_LZ_رمز_BUF_سائز = 24 * 1024, TDEFL_برآمد_BUF_سائز = (TDEFL_LZ_رمز_BUF_سائز * 13 ) / 10, TDEFL_MAX_HUFF_SYMBOLS = 288, TDEFL_LZ_HASH_بٹ = 12, TDEFL_LEVEL1_HASH_سائز_نقاب = 4095, TDEFL_LZ_HASH_سرکاؤ = (TDEFL_LZ_HASH_بٹ + 2) / 3, TDEFL_LZ_HASH_سائز = 1 << TDEFL_LZ_HASH_بٹ };
#ورنہ
شمار { TDEFL_LZ_رمز_BUF_سائز = 64 * 1024, TDEFL_برآمد_BUF_سائز = (TDEFL_LZ_رمز_BUF_سائز * 13 ) / 10, TDEFL_MAX_HUFF_SYMBOLS = 288, TDEFL_LZ_HASH_بٹ = 15, TDEFL_LEVEL1_HASH_سائز_نقاب = 4095, TDEFL_LZ_HASH_سرکاؤ = (TDEFL_LZ_HASH_بٹ + 2) / 3, TDEFL_LZ_HASH_سائز = 1 << TDEFL_LZ_HASH_بٹ };
#اگر_ختم

// The low-level tdefl functions below may be used directly if the above helper functions aren't flexible enough. The low-level functions don't make any heap allocations, unlike the above helper functions.
قسمتعریف شمار
{
  TDEFL_حالت_BAD_PARAM = -2,
  TDEFL_حالت_PUT_BUF_FAILED = -1,
  TDEFL_حالت_OKAY = 0,
  TDEFL_حالت_مکمل = 1,
} tdefl_حالت;

// Must map to MZ_NO_FLUSH, MZ_SYNC_FLUSH, etc. enums
قسمتعریف شمار
{
  TDEFL_NO_FLUSH = 0,
  TDEFL_SYNC_FLUSH = 2,
  TDEFL_بھرا_FLUSH = 3,
  TDEFL_اختتام = 4
} tdefl_flush;

// tdefl's compression state structure.
قسمتعریف ساخت
{
  tdefl_put_buf_func_ptr m_pPut_buf_func;
  خالی *m_pPut_buf_user;
  mz_uint m_flags, m_max_probes[2];
  صحیح m_greedy_parsing;
  mz_uint m_adler32, m_lookahead_pos, m_lookahead_سائز, m_dict_سائز;
  mz_uint8 *m_p_LZ_رمز_buf, *m_pLZ_flags, *m_pOutput_buf, *m_p_Output_buf_انتہا;
  mz_uint m_عدد_flags_بایاں, m_کل_lz_بائٹیں, m_lz_رمز_buf_dict_pos, m_بٹ_اندر, m_ثنائی_ہندسہ_بفر;
  mz_uint m_saved_مطابقت_dist, m_saved_مطابقت_len, m_saved_lit, m_output_flush_ofs, m_output_flush_بقایا, m_ختم_شدہ, m_بلاک_اشاریہ, m_چاہتا_مقصد_اختتام;
  tdefl_حالت m_پچھلا_return_حالت;
  ثابت خالی *m_p_اندر_buf;
  خالی *m_p_برآمد_buf;
  size_t *m_p_اندر_buf_سائز, *m_p_برآمد_buf_سائز;
  tdefl_flush m_flush;
  ثابت mz_uint8 *m_pSrc;
  size_t m_src_buf_بایاں, m_برآمد_buf_ofs;
  mz_uint8 m_dict[TDEFL_LZ_DICT_سائز + TDEFL_MAX_مطابقت_LEN - 1];
  mz_uint16 m_huff_گنتی[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint16 m_huff_codes[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint8 m_huff_رمز_sizes[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint8 m_lz_رمز_buf[TDEFL_LZ_رمز_BUF_سائز];
  mz_uint16 m_اگلا[TDEFL_LZ_DICT_سائز];
  mz_uint16 m_hash[TDEFL_LZ_HASH_سائز];
  mz_uint8 m_output_buf[TDEFL_برآمد_BUF_سائز];
} tdefl_compressor;

// Initializes the compressor.
// There is no corresponding deinit() function because the tdefl API's do not dynamically allocate memory.
// pBut_buf_func: If NULL, output data will be supplied to the specified callback. In this case, the user should call the tdefl_compress_buffer() API for compression.
// If pBut_buf_func is NULL the user should always call the tdefl_compress() API.
// flags: See the above enums (TDEFL_HUFFMAN_ONLY, TDEFL_WRITE_ZLIB_HEADER, etc.)
MINIZ_STATIC tdefl_حالت tdefl_init(tdefl_compressor *d, tdefl_put_buf_func_ptr pPut_buf_func, خالی *pPut_buf_user, صحیح flags);

// Compresses a block of data, consuming as much of the specified input buffer as possible, and writing as much compressed data to the specified output buffer as possible.
MINIZ_STATIC tdefl_حالت tdefl_compress(tdefl_compressor *d, ثابت خالی *p_اندر_buf, size_t *p_اندر_buf_سائز, خالی *p_برآمد_buf, size_t *p_برآمد_buf_سائز, tdefl_flush flush);

// tdefl_compress_buffer() is only usable when the tdefl_init() is called with a non-NULL tdefl_put_buf_func_ptr.
// tdefl_compress_buffer() always consumes the entire input buffer.
MINIZ_STATIC tdefl_حالت tdefl_compress_بفر(tdefl_compressor *d, ثابت خالی *p_اندر_buf, size_t اندر_buf_سائز, tdefl_flush flush);

#اگر_غیر_تعریف_شدہ MINIZ_SDL_NOUNUSED
MINIZ_STATIC tdefl_حالت tdefl_get_پچھلا_return_حالت(tdefl_compressor *d);
MINIZ_STATIC mz_uint32 tdefl_get_adler32(tdefl_compressor *d);
#اگر_ختم

// Can't use tdefl_create_comp_flags_from_zip_params if MINIZ_NO_ZLIB_APIS isn't defined, because it uses some of its macros.
#اگر_غیر_تعریف_شدہ MINIZ_NO_ZLIB_APIS
// Create tdefl_compress() flags given zlib-style compression parameters.
// level may range from [0,10] (where 10 is absolute max compression, but may be much slower on some files)
// window_bits may be -15 (raw deflate) or 15 (zlib)
// strategy may be either MZ_DEFAULT_STRATEGY, MZ_FILTERED, MZ_HUFFMAN_ONLY, MZ_RLE, or MZ_FIXED
MINIZ_STATIC mz_uint tdefl_create_comp_flags_from_zip_params(صحیح level, صحیح کھڑکی_بٹ, صحیح strategy);
#اگر_ختم // #ifndef MINIZ_NO_ZLIB_APIS

#اگر_ختم /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_ختم // MINIZ_HEADER_INCLUDED

// ------------------- End of Header: Implementation follows. (If you only want the header, define MINIZ_HEADER_FILE_ONLY.)

#اگر_غیر_تعریف_شدہ MINIZ_سرخی_FILE_ONLY

#اگر_تعریف_شدہ _MSC_VER
#ہدایت warning (ڈالو)
#ہدایت warning (disable:4505) // unreferenced local function has been removed
#اگر_ختم

قسمتعریف غیرعلامتی حرف mz_validate_uint16[حجم(mz_uint16)==2 ? 1 : -1];
قسمتعریف غیرعلامتی حرف mz_validate_uint32[حجم(mz_uint32)==4 ? 1 : -1];
قسمتعریف غیرعلامتی حرف mz_validate_uint64[حجم(mz_uint64)==8 ? 1 : -1];

/*#include <string.h>*/

#اگر_غیر_تعریف_شدہ MZ_ASSERT
#شامل <assert.h>
#تعریف_کرو MZ_ASSERT(x) أكد(x)
#اگر_ختم

#اگر_تعریف_شدہ MINIZ_NO_MALLOC
  #تعریف_کرو MZ_MALLOC(x) تہی
  #تعریف_کرو MZ_FREE(x) (خالی)x, ((خالی)0)
  #تعریف_کرو MZ_REALLOC(p, x) تہی
#وگرنہ_اگر defined(MINIZ_SDL_MALLOC)
  #تعریف_کرو MZ_MALLOC(x) SDL_malloc(x)
  #تعریف_کرو MZ_FREE(x) SDL_free(x)
  #تعریف_کرو MZ_REALLOC(p, x) SDL_realloc(p, x)
#ورنہ
  #تعریف_کرو MZ_MALLOC(x) حافظہ_دو(x)
  #تعریف_کرو MZ_FREE(x) آزاد(x)
  #تعریف_کرو MZ_REALLOC(p, x) realloc(p, x)
#اگر_ختم

#تعریف_کرو MZ_MAX(a,b) (((a)>(b))?(a):(b))
#تعریف_کرو MZ_MIN(a,b) (((a)<(b))?(a):(b))
#تعریف_کرو MZ_CLEAR_OBJ(obj) memset(&(obj), 0, حجم(obj))
#تعریف_کرو MZ_CLEAR_ARR(obj) memset((obj), 0, حجم(obj))
#تعریف_کرو MZ_CLEAR_PTR(obj) memset((obj), 0, حجم(*obj))

#اگر MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  #تعریف_کرو MZ_READ_LE16(p) *((ثابت mz_uint16 *)(p))
  #تعریف_کرو MZ_READ_LE32(p) *((ثابت mz_uint32 *)(p))
#ورنہ
  #تعریف_کرو MZ_READ_LE16(p) ((mz_uint32)(((ثابت mz_uint8 *)(p))[0]) | ((mz_uint32)(((ثابت mz_uint8 *)(p))[1]) << 8U))
  #تعریف_کرو MZ_READ_LE32(p) ((mz_uint32)(((ثابت mz_uint8 *)(p))[0]) | ((mz_uint32)(((ثابت mz_uint8 *)(p))[1]) << 8U) | ((mz_uint32)(((ثابت mz_uint8 *)(p))[2]) << 16U) | ((mz_uint32)(((ثابت mz_uint8 *)(p))[3]) << 24U))
#اگر_ختم

#اگر_تعریف_شدہ _MSC_VER
  #تعریف_کرو MZ_FORCEINLINE __forceinline
#وگرنہ_اگر defined(__GNUC__)
  #تعریف_کرو MZ_FORCEINLINE اندرونی __attribute__((__always_inline__))
#ورنہ
  #تعریف_کرو MZ_FORCEINLINE اندرونی
#اگر_ختم

#اگر_تعریف_شدہ __cplusplus
  خارجی "C" {
#اگر_ختم

// ------------------- zlib-style API's

mz_ulong mz_adler32(mz_ulong adler, ثابت غیرعلامتی حرف *ptr, size_t buf_len)
{
  mz_uint32 i, s1 = (mz_uint32)(adler & 0xffff), s2 = (mz_uint32)(adler >> 16); size_t بلاک_len = buf_len % 5552;
  اگر (!ptr) واپس MZ_ADLER32_INIT;
  جب (buf_len) {
    برائے (i = 0; i + 7 < بلاک_len; i += 8, ptr += 8) {
      s1 += ptr[0]; s2 += s1; s1 += ptr[1]; s2 += s1; s1 += ptr[2]; s2 += s1; s1 += ptr[3]; s2 += s1;
      s1 += ptr[4]; s2 += s1; s1 += ptr[5]; s2 += s1; s1 += ptr[6]; s2 += s1; s1 += ptr[7]; s2 += s1;
    }
    برائے ( ; i < بلاک_len; ++i) { s1 += *ptr++; s2 += s1; }
    s1 %= 65521U; s2 %= 65521U; buf_len -= بلاک_len; بلاک_len = 5552;
  }
  واپس (s2 << 16) + s1;
}

// Karl Malbrain's compact CRC-32. See "A compact CCITT crc16 and crc32 C implementation that balances processor cache usage against speed": http://www.geocities.com/malbrain/
mz_ulong mz_چکری_جانچ_32(mz_ulong چکری_جانچ, ثابت mz_uint8 *ptr, size_t buf_len)
{
  ساکن ثابت mz_uint32 s_چکری_جانچ_32[16] = { 0, 0x1db71064, 0x3b6e20c8, 0x26d930ac, 0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
    0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c, 0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c };
  mz_uint32 crcu32 = (mz_uint32)چکری_جانچ;
  اگر (!ptr) واپس MZ_چکری_جانچ_32_INIT;
  crcu32 = ~crcu32; جب (buf_len--) { mz_uint8 b = *ptr++; crcu32 = (crcu32 >> 4) ^ s_چکری_جانچ_32[(crcu32 & 0xF) ^ (b & 0xF)]; crcu32 = (crcu32 >> 4) ^ s_چکری_جانچ_32[(crcu32 & 0xF) ^ (b >> 4)]; }
  واپس ~crcu32;
}

MINIZ_STATIC خالی mz_free(خالی *p)
{
  MZ_FREE(p);
}

#اگر_غیر_تعریف_شدہ MINIZ_NO_ZLIB_APIS

ساکن خالی *def_alloc_func(خالی *opaque, size_t اشیاء, size_t سائز) { (خالی)opaque, (خالی)اشیاء, (خالی)سائز; واپس MZ_MALLOC(اشیاء * سائز); }
ساکن خالی def_free_func(خالی *opaque, خالی *پتہ) { (خالی)opaque, (خالی)پتہ; MZ_FREE(پتہ); }
ساکن خالی *def_realloc_func(خالی *opaque, خالی *پتہ, size_t اشیاء, size_t سائز) { (خالی)opaque, (خالی)پتہ, (خالی)اشیاء, (خالی)سائز; واپس MZ_REALLOC(پتہ, اشیاء * سائز); }

ثابت حرف *mz_نسخہ(خالی)
{
  واپس MZ_نسخہ;
}

#اگر_غیر_تعریف_شدہ MINIZ_NO_DEFLATE_APIS

صحیح mz_deflateInit(mz_streamp p_دھارا, صحیح level)
{
  واپس mz_deflateInit2(p_دھارا, level, MZ_DEFLATED, MZ_DEFAULT_کھڑکی_بٹ, 9, MZ_DEFAULT_STRATEGY);
}

صحیح mz_deflateInit2(mz_streamp p_دھارا, صحیح level, صحیح طریقہ, صحیح کھڑکی_بٹ, صحیح mem_level, صحیح strategy)
{
  tdefl_compressor *pComp;
  mz_uint comp_flags = TDEFL_COMPUTE_ADLER32 | tdefl_create_comp_flags_from_zip_params(level, کھڑکی_بٹ, strategy);

  اگر (!p_دھارا) واپس MZ_دھارا_ERROR;
  اگر ((طریقہ != MZ_DEFLATED) || ((mem_level < 1) || (mem_level > 9)) || ((کھڑکی_بٹ != MZ_DEFAULT_کھڑکی_بٹ) && (-کھڑکی_بٹ != MZ_DEFAULT_کھڑکی_بٹ))) واپس MZ_PARAM_ERROR;

  p_دھارا->ڈیٹا_type = 0;
  p_دھارا->adler = MZ_ADLER32_INIT;
  p_دھارا->پیغام_2 = تہی;
  p_دھارا->reserved = 0;
  p_دھارا->کل_اندر = 0;
  p_دھارا->کل_برآمد = 0;
  اگر (!p_دھارا->zalloc) p_دھارا->zalloc = def_alloc_func;
  اگر (!p_دھارا->zfree) p_دھارا->zfree = def_free_func;

  pComp = (tdefl_compressor *)p_دھارا->zalloc(p_دھارا->opaque, 1, حجم(tdefl_compressor));
  اگر (!pComp)
    واپس MZ_MEM_ERROR;

  p_دھارا->state = (ساخت mz_اندرونی_state *)pComp;

  اگر (tdefl_init(pComp, تہی, تہی, comp_flags) != TDEFL_حالت_OKAY)
  {
    mz_deflate_انتہا(p_دھارا);
    واپس MZ_PARAM_ERROR;
  }

  واپس MZ_OK;
}

صحیح mz_deflateReset(mz_streamp p_دھارا)
{
  اگر ((!p_دھارا) || (!p_دھارا->state) || (!p_دھارا->zalloc) || (!p_دھارا->zfree)) واپس MZ_دھارا_ERROR;
  p_دھارا->کل_اندر = p_دھارا->کل_برآمد = 0;
  tdefl_init((tdefl_compressor*)p_دھارا->state, تہی, تہی, ((tdefl_compressor*)p_دھارا->state)->m_flags);
  واپس MZ_OK;
}

صحیح mz_deflate(mz_streamp p_دھارا, صحیح flush)
{
  size_t اندر_بائٹیں, برآمد_بائٹیں;
  mz_ulong orig_کل_اندر, orig_کل_برآمد;
  صحیح mz_حالت = MZ_OK;

  اگر ((!p_دھارا) || (!p_دھارا->state) || (flush < 0) || (flush > MZ_اختتام) || (!p_دھارا->اگلا_برآمد)) واپس MZ_دھارا_ERROR;
  اگر (!p_دھارا->avail_برآمد) واپس MZ_BUF_ERROR;

  اگر (flush == MZ_PARTIAL_FLUSH) flush = MZ_SYNC_FLUSH;

  اگر (((tdefl_compressor*)p_دھارا->state)->m_پچھلا_return_حالت == TDEFL_حالت_مکمل)
    واپس (flush == MZ_اختتام) ? MZ_دھارا_انتہا : MZ_BUF_ERROR;

  orig_کل_اندر = p_دھارا->کل_اندر; orig_کل_برآمد = p_دھارا->کل_برآمد;
  برائے ( ; ; )
  {
    tdefl_حالت defl_حالت;
    اندر_بائٹیں = p_دھارا->avail_اندر; برآمد_بائٹیں = p_دھارا->avail_برآمد;

    defl_حالت = tdefl_compress((tdefl_compressor*)p_دھارا->state, p_دھارا->اگلا_اندر, &اندر_بائٹیں, p_دھارا->اگلا_برآمد, &برآمد_بائٹیں, (tdefl_flush)flush);
    p_دھارا->اگلا_اندر += (mz_uint)اندر_بائٹیں; p_دھارا->avail_اندر -= (mz_uint)اندر_بائٹیں;
    p_دھارا->کل_اندر += (mz_uint)اندر_بائٹیں; p_دھارا->adler = tdefl_get_adler32((tdefl_compressor*)p_دھارا->state);

    p_دھارا->اگلا_برآمد += (mz_uint)برآمد_بائٹیں; p_دھارا->avail_برآمد -= (mz_uint)برآمد_بائٹیں;
    p_دھارا->کل_برآمد += (mz_uint)برآمد_بائٹیں;

    اگر (defl_حالت < 0)
    {
      mz_حالت = MZ_دھارا_ERROR;
      توڑو;
    }
    ورنہ اگر (defl_حالت == TDEFL_حالت_مکمل)
    {
      mz_حالت = MZ_دھارا_انتہا;
      توڑو;
    }
    ورنہ اگر (!p_دھارا->avail_برآمد)
      توڑو;
    ورنہ اگر ((!p_دھارا->avail_اندر) && (flush != MZ_اختتام))
    {
      اگر ((flush) || (p_دھارا->کل_اندر != orig_کل_اندر) || (p_دھارا->کل_برآمد != orig_کل_برآمد))
        توڑو;
      واپس MZ_BUF_ERROR; // Can't make forward progress without some input.
    }
  }
  واپس mz_حالت;
}

صحیح mz_deflate_انتہا(mz_streamp p_دھارا)
{
  اگر (!p_دھارا) واپس MZ_دھارا_ERROR;
  اگر (p_دھارا->state)
  {
    p_دھارا->zfree(p_دھارا->opaque, p_دھارا->state);
    p_دھارا->state = تہی;
  }
  واپس MZ_OK;
}

mz_ulong mz_deflateBound(mz_streamp p_دھارا, mz_ulong ماخذ_len)
{
  (خالی)p_دھارا;
  // This is really over conservative. (And lame, but it's actually pretty tricky to compute a true upper bound given the way tdefl's blocking works.)
  واپس MZ_MAX(128 + (ماخذ_len * 110) / 100, 128 + ماخذ_len + ((ماخذ_len / (31 * 1024)) + 1) * 5);
}

صحیح mz_compress2(غیرعلامتی حرف *pDest, mz_ulong *pDest_len, ثابت غیرعلامتی حرف *p_ماخذ, mz_ulong ماخذ_len, صحیح level)
{
  صحیح حالت_2;
  mz_دھارا دھارا;
  memset(&دھارا, 0, حجم(دھارا));

  // In case mz_ulong is 64-bits (argh I hate longs).
  اگر ((ماخذ_len | *pDest_len) > 0xFFFFFFFFU) واپس MZ_PARAM_ERROR;

  دھارا.اگلا_اندر = p_ماخذ;
  دھارا.avail_اندر = (mz_uint32)ماخذ_len;
  دھارا.اگلا_برآمد = pDest;
  دھارا.avail_برآمد = (mz_uint32)*pDest_len;

  حالت_2 = mz_deflateInit(&دھارا, level);
  اگر (حالت_2 != MZ_OK) واپس حالت_2;

  حالت_2 = mz_deflate(&دھارا, MZ_اختتام);
  اگر (حالت_2 != MZ_دھارا_انتہا)
  {
    mz_deflate_انتہا(&دھارا);
    واپس (حالت_2 == MZ_OK) ? MZ_BUF_ERROR : حالت_2;
  }

  *pDest_len = دھارا.کل_برآمد;
  واپس mz_deflate_انتہا(&دھارا);
}

صحیح mz_compress(غیرعلامتی حرف *pDest, mz_ulong *pDest_len, ثابت غیرعلامتی حرف *p_ماخذ, mz_ulong ماخذ_len)
{
  واپس mz_compress2(pDest, pDest_len, p_ماخذ, ماخذ_len, MZ_DEFAULT_COMPRESSION);
}

mz_ulong mz_compressBound(mz_ulong ماخذ_len)
{
  واپس mz_deflateBound(تہی, ماخذ_len);
}

#اگر_ختم /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#اگر_غیر_تعریف_شدہ MINIZ_NO_INFLATE_APIS

قسمتعریف ساخت
{
  tinfl_decompressor m_decomp;
  mz_uint m_dict_ofs, m_dict_avail, m_پہلا_call, m_has_flushed; صحیح m_کھڑکی_بٹ;
  mz_uint8 m_dict[TINFL_LZ_DICT_سائز];
  tinfl_حالت m_آخری_حالت;
} inflate_state;

صحیح mz_inflateInit2(mz_streamp p_دھارا, صحیح کھڑکی_بٹ)
{
  inflate_state *pDecomp;
  اگر (!p_دھارا) واپس MZ_دھارا_ERROR;
  اگر ((کھڑکی_بٹ != MZ_DEFAULT_کھڑکی_بٹ) && (-کھڑکی_بٹ != MZ_DEFAULT_کھڑکی_بٹ)) واپس MZ_PARAM_ERROR;

  p_دھارا->ڈیٹا_type = 0;
  p_دھارا->adler = 0;
  p_دھارا->پیغام_2 = تہی;
  p_دھارا->کل_اندر = 0;
  p_دھارا->کل_برآمد = 0;
  p_دھارا->reserved = 0;
  اگر (!p_دھارا->zalloc) p_دھارا->zalloc = def_alloc_func;
  اگر (!p_دھارا->zfree) p_دھارا->zfree = def_free_func;

  pDecomp = (inflate_state*)p_دھارا->zalloc(p_دھارا->opaque, 1, حجم(inflate_state));
  اگر (!pDecomp) واپس MZ_MEM_ERROR;

  p_دھارا->state = (ساخت mz_اندرونی_state *)pDecomp;

  tinfl_init(&pDecomp->m_decomp);
  pDecomp->m_dict_ofs = 0;
  pDecomp->m_dict_avail = 0;
  pDecomp->m_آخری_حالت = TINFL_حالت_NEEDS_مزید_داخلہ;
  pDecomp->m_پہلا_call = 1;
  pDecomp->m_has_flushed = 0;
  pDecomp->m_کھڑکی_بٹ = کھڑکی_بٹ;

  واپس MZ_OK;
}

صحیح mz_inflateInit(mz_streamp p_دھارا)
{
   واپس mz_inflateInit2(p_دھارا, MZ_DEFAULT_کھڑکی_بٹ);
}

صحیح mz_inflate(mz_streamp p_دھارا, صحیح flush)
{
  inflate_state* pState;
  mz_uint n, پہلا_call, decomp_flags = TINFL_FLAG_COMPUTE_ADLER32;
  size_t اندر_بائٹیں, برآمد_بائٹیں, orig_avail_اندر;
  tinfl_حالت حالت_2;

  اگر ((!p_دھارا) || (!p_دھارا->state)) واپس MZ_دھارا_ERROR;
  اگر (flush == MZ_PARTIAL_FLUSH) flush = MZ_SYNC_FLUSH;
  اگر ((flush) && (flush != MZ_SYNC_FLUSH) && (flush != MZ_اختتام)) واپس MZ_دھارا_ERROR;

  pState = (inflate_state*)p_دھارا->state;
  اگر (pState->m_کھڑکی_بٹ > 0) decomp_flags |= TINFL_FLAG_PARSE_ZLIB_سرخی;
  orig_avail_اندر = p_دھارا->avail_اندر;

  پہلا_call = pState->m_پہلا_call; pState->m_پہلا_call = 0;
  اگر (pState->m_آخری_حالت < 0) واپس MZ_ڈیٹا_ERROR;

  اگر (pState->m_has_flushed && (flush != MZ_اختتام)) واپس MZ_دھارا_ERROR;
  pState->m_has_flushed |= (flush == MZ_اختتام);

  اگر ((flush == MZ_اختتام) && (پہلا_call))
  {
    // MZ_FINISH on the first call implies that the input and output buffers are large enough to hold the entire compressed/decompressed file.
    decomp_flags |= TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF;
    اندر_بائٹیں = p_دھارا->avail_اندر; برآمد_بائٹیں = p_دھارا->avail_برآمد;
    حالت_2 = tinfl_decompress(&pState->m_decomp, p_دھارا->اگلا_اندر, &اندر_بائٹیں, p_دھارا->اگلا_برآمد, p_دھارا->اگلا_برآمد, &برآمد_بائٹیں, decomp_flags);
    pState->m_آخری_حالت = حالت_2;
    p_دھارا->اگلا_اندر += (mz_uint)اندر_بائٹیں; p_دھارا->avail_اندر -= (mz_uint)اندر_بائٹیں; p_دھارا->کل_اندر += (mz_uint)اندر_بائٹیں;
    p_دھارا->adler = tinfl_get_adler32(&pState->m_decomp);
    p_دھارا->اگلا_برآمد += (mz_uint)برآمد_بائٹیں; p_دھارا->avail_برآمد -= (mz_uint)برآمد_بائٹیں; p_دھارا->کل_برآمد += (mz_uint)برآمد_بائٹیں;

    اگر (حالت_2 < 0)
      واپس MZ_ڈیٹا_ERROR;
    ورنہ اگر (حالت_2 != TINFL_حالت_مکمل)
    {
      pState->m_آخری_حالت = TINFL_حالت_FAILED;
      واپس MZ_BUF_ERROR;
    }
    واپس MZ_دھارا_انتہا;
  }
  // flush != MZ_FINISH then we must assume there's more input.
  اگر (flush != MZ_اختتام) decomp_flags |= TINFL_FLAG_HAS_مزید_داخلہ;

  اگر (pState->m_dict_avail)
  {
    n = MZ_MIN(pState->m_dict_avail, p_دھارا->avail_برآمد);
    حافظہ_نقل(p_دھارا->اگلا_برآمد, pState->m_dict + pState->m_dict_ofs, n);
    p_دھارا->اگلا_برآمد += n; p_دھارا->avail_برآمد -= n; p_دھارا->کل_برآمد += n;
    pState->m_dict_avail -= n; pState->m_dict_ofs = (pState->m_dict_ofs + n) & (TINFL_LZ_DICT_سائز - 1);
    واپس ((pState->m_آخری_حالت == TINFL_حالت_مکمل) && (!pState->m_dict_avail)) ? MZ_دھارا_انتہا : MZ_OK;
  }

  برائے ( ; ; )
  {
    اندر_بائٹیں = p_دھارا->avail_اندر;
    برآمد_بائٹیں = TINFL_LZ_DICT_سائز - pState->m_dict_ofs;

    حالت_2 = tinfl_decompress(&pState->m_decomp, p_دھارا->اگلا_اندر, &اندر_بائٹیں, pState->m_dict, pState->m_dict + pState->m_dict_ofs, &برآمد_بائٹیں, decomp_flags);
    pState->m_آخری_حالت = حالت_2;

    p_دھارا->اگلا_اندر += (mz_uint)اندر_بائٹیں; p_دھارا->avail_اندر -= (mz_uint)اندر_بائٹیں;
    p_دھارا->کل_اندر += (mz_uint)اندر_بائٹیں; p_دھارا->adler = tinfl_get_adler32(&pState->m_decomp);

    pState->m_dict_avail = (mz_uint)برآمد_بائٹیں;

    n = MZ_MIN(pState->m_dict_avail, p_دھارا->avail_برآمد);
    حافظہ_نقل(p_دھارا->اگلا_برآمد, pState->m_dict + pState->m_dict_ofs, n);
    p_دھارا->اگلا_برآمد += n; p_دھارا->avail_برآمد -= n; p_دھارا->کل_برآمد += n;
    pState->m_dict_avail -= n; pState->m_dict_ofs = (pState->m_dict_ofs + n) & (TINFL_LZ_DICT_سائز - 1);

    اگر (حالت_2 < 0)
       واپس MZ_ڈیٹا_ERROR; // Stream is corrupted (there could be some uncompressed data left in the output dictionary - oh well).
    ورنہ اگر ((حالت_2 == TINFL_حالت_NEEDS_مزید_داخلہ) && (!orig_avail_اندر))
      واپس MZ_BUF_ERROR; // Signal caller that we can't make forward progress without supplying more input or by setting flush to MZ_FINISH.
    ورنہ اگر (flush == MZ_اختتام)
    {
       // The output buffer MUST be large to hold the remaining uncompressed data when flush==MZ_FINISH.
       اگر (حالت_2 == TINFL_حالت_مکمل)
          واپس pState->m_dict_avail ? MZ_BUF_ERROR : MZ_دھارا_انتہا;
       // status here must be TINFL_STATUS_HAS_MORE_OUTPUT, which means there's at least 1 more byte on the way. If there's no more room left in the output buffer then something is wrong.
       ورنہ اگر (!p_دھارا->avail_برآمد)
          واپس MZ_BUF_ERROR;
    }
    ورنہ اگر ((حالت_2 == TINFL_حالت_مکمل) || (!p_دھارا->avail_اندر) || (!p_دھارا->avail_برآمد) || (pState->m_dict_avail))
      توڑو;
  }

  واپس ((حالت_2 == TINFL_حالت_مکمل) && (!pState->m_dict_avail)) ? MZ_دھارا_انتہا : MZ_OK;
}

صحیح mz_inflate_انتہا(mz_streamp p_دھارا)
{
  اگر (!p_دھارا)
    واپس MZ_دھارا_ERROR;
  اگر (p_دھارا->state)
  {
    p_دھارا->zfree(p_دھارا->opaque, p_دھارا->state);
    p_دھارا->state = تہی;
  }
  واپس MZ_OK;
}

صحیح mz_uncompress(غیرعلامتی حرف *pDest, mz_ulong *pDest_len, ثابت غیرعلامتی حرف *p_ماخذ, mz_ulong ماخذ_len)
{
  mz_دھارا دھارا;
  صحیح حالت_2;
  memset(&دھارا, 0, حجم(دھارا));

  // In case mz_ulong is 64-bits (argh I hate longs).
  اگر ((ماخذ_len | *pDest_len) > 0xFFFFFFFFU) واپس MZ_PARAM_ERROR;

  دھارا.اگلا_اندر = p_ماخذ;
  دھارا.avail_اندر = (mz_uint32)ماخذ_len;
  دھارا.اگلا_برآمد = pDest;
  دھارا.avail_برآمد = (mz_uint32)*pDest_len;

  حالت_2 = mz_inflateInit(&دھارا);
  اگر (حالت_2 != MZ_OK)
    واپس حالت_2;

  حالت_2 = mz_inflate(&دھارا, MZ_اختتام);
  اگر (حالت_2 != MZ_دھارا_انتہا)
  {
    mz_inflate_انتہا(&دھارا);
    واپس ((حالت_2 == MZ_BUF_ERROR) && (!دھارا.avail_اندر)) ? MZ_ڈیٹا_ERROR : حالت_2;
  }
  *pDest_len = دھارا.کل_برآمد;

  واپس mz_inflate_انتہا(&دھارا);
}

#اگر_ختم /*#ifndef MINIZ_NO_INFLATE_APIS*/

ثابت حرف *mz_error(صحیح err)
{
  ساکن ساخت { صحیح m_err; ثابت حرف *m_pDesc; } s_error_descs[] =
  {
    { MZ_OK, "" }, { MZ_دھارا_انتہا, "stream end" }, { MZ_NEED_DICT, "need dictionary" }, { MZ_ERRNO, "file error" }, { MZ_دھارا_ERROR, "stream error" },
    { MZ_ڈیٹا_ERROR, "data error" }, { MZ_MEM_ERROR, "out of memory" }, { MZ_BUF_ERROR, "buf error" }, { MZ_نسخہ_ERROR, "version error" }, { MZ_PARAM_ERROR, "parameter error" }
  };
  mz_uint i; برائے (i = 0; i < حجم(s_error_descs) / حجم(s_error_descs[0]); ++i) اگر (s_error_descs[i].m_err == err) واپس s_error_descs[i].m_pDesc;
  واپس تہی;
}

#اگر_ختم //MINIZ_NO_ZLIB_APIS

// ------------------- Low-level Decompression (completely independent from all compression API's)
#اگر_غیر_تعریف_شدہ MINIZ_NO_INFLATE_APIS

#تعریف_کرو TINFL_MEMCPY(d, s, l) حافظہ_نقل(d, s, l)
#تعریف_کرو TINFL_MEMSET(p, c, l) memset(p, c, l)

#تعریف_کرو TINFL_CR_BEGIN انتخاب(r->m_state) { حالت 0:
#تعریف_کرو TINFL_CR_RETURN(state_اشاریہ, نتیجہ) کرو { حالت_2 = نتیجہ; r->m_state = state_اشاریہ; جاؤ common_exit; حالت state_اشاریہ:; } MZ_MACRO_انتہا
#تعریف_کرو TINFL_CR_RETURN_FOREVER(state_اشاریہ, نتیجہ) کرو { برائے ( ; ; ) { TINFL_CR_RETURN(state_اشاریہ, نتیجہ); } } MZ_MACRO_انتہا
#تعریف_کرو TINFL_CR_اختتام }

// TODO: If the caller has indicated that there's no more input, and we attempt to read beyond the input buf, then something is wrong with the input because the inflator never
// reads ahead more than it needs to. Currently TINFL_GET_BYTE() pads the end of the stream with 0's in this scenario.
#تعریف_کرو TINFL_GET_BYTE(state_اشاریہ, c) کرو { \
  اگر (p_اندر_buf_cur >= p_اندر_buf_انتہا) { \
    برائے ( ; ; ) { \
      اگر (decomp_flags & TINFL_FLAG_HAS_مزید_داخلہ) { \
        TINFL_CR_RETURN(state_اشاریہ, TINFL_حالت_NEEDS_مزید_داخلہ); \
        اگر (p_اندر_buf_cur < p_اندر_buf_انتہا) { \
          c = *p_اندر_buf_cur++; \
          توڑو; \
        } \
      } ورنہ { \
        c = 0; \
        توڑو; \
      } \
    } \
  } ورنہ c = *p_اندر_buf_cur++; } MZ_MACRO_انتہا

#تعریف_کرو TINFL_NEED_بٹ(state_اشاریہ, n) کرو { mz_uint c; TINFL_GET_BYTE(state_اشاریہ, c); ثنائی_ہندسہ_buf |= (((tinfl_ثنائی_ہندسہ_buf_t)c) << عدد_بٹ); عدد_بٹ += 8; } جب (عدد_بٹ < (mz_uint)(n))
#تعریف_کرو TINFL_SKIP_بٹ(state_اشاریہ, n) کرو { اگر (عدد_بٹ < (mz_uint)(n)) { TINFL_NEED_بٹ(state_اشاریہ, n); } ثنائی_ہندسہ_buf >>= (n); عدد_بٹ -= (n); } MZ_MACRO_انتہا
#تعریف_کرو TINFL_GET_بٹ(state_اشاریہ, b, n) کرو { اگر (عدد_بٹ < (mz_uint)(n)) { TINFL_NEED_بٹ(state_اشاریہ, n); } b = ثنائی_ہندسہ_buf & ((1 << (n)) - 1); ثنائی_ہندسہ_buf >>= (n); عدد_بٹ -= (n); } MZ_MACRO_انتہا

// TINFL_HUFF_BITBUF_FILL() is only used rarely, when the number of bytes remaining in the input buffer falls below 2.
// It reads just enough bytes from the input stream that are needed to decode the next Huffman code (and absolutely no more). It works by trying to fully decode a
// Huffman code by using whatever bits are currently present in the bit buffer. If this fails, it reads another byte, and tries again until it succeeds or until the
// bit buffer contains >=15 bits (deflate's max. Huffman code size).
#تعریف_کرو TINFL_HUFF_BITBUF_FILL(state_اشاریہ, pHuff) \
  کرو { \
    عارضی = (pHuff)->m_look_اوپر[ثنائی_ہندسہ_buf & (TINFL_FAST_LOOKUP_سائز - 1)]; \
    اگر (عارضی >= 0) { \
      رمز_len = عارضی >> 9; \
      اگر ((رمز_len) && (عدد_بٹ >= رمز_len)) \
          توڑو; \
    } ورنہ اگر (عدد_بٹ > TINFL_FAST_LOOKUP_بٹ) { \
       رمز_len = TINFL_FAST_LOOKUP_بٹ; \
       کرو { \
          عارضی = (pHuff)->m_درخت[~عارضی + ((ثنائی_ہندسہ_buf >> رمز_len++) & 1)]; \
       } جب ((عارضی < 0) && (عدد_بٹ >= (رمز_len + 1))); \
       اگر (عارضی >= 0) توڑو; \
    } \
    TINFL_GET_BYTE(state_اشاریہ, c); \
    ثنائی_ہندسہ_buf |= (((tinfl_ثنائی_ہندسہ_buf_t)c) << عدد_بٹ); \
    عدد_بٹ += 8; \
  } جب (عدد_بٹ < 15);

// TINFL_HUFF_DECODE() decodes the next Huffman coded symbol. It's more complex than you would initially expect because the zlib API expects the decompressor to never read
// beyond the final byte of the deflate stream. (In other words, when this macro wants to read another byte from the input, it REALLY needs another byte in order to fully
// decode the next Huffman code.) Handling this properly is particularly important on raw deflate (non-zlib) streams, which aren't followed by a byte aligned adler-32.
// The slow path is only executed at the very end of the input buffer.
#تعریف_کرو TINFL_HUFF_DECODE(state_اشاریہ, sym, pHuff) کرو { \
  صحیح عارضی; mz_uint رمز_len, c; \
  اگر (عدد_بٹ < 15) { \
    اگر ((p_اندر_buf_انتہا - p_اندر_buf_cur) < 2) { \
       TINFL_HUFF_BITBUF_FILL(state_اشاریہ, pHuff); \
    } ورنہ { \
       ثنائی_ہندسہ_buf |= (((tinfl_ثنائی_ہندسہ_buf_t)p_اندر_buf_cur[0]) << عدد_بٹ) | (((tinfl_ثنائی_ہندسہ_buf_t)p_اندر_buf_cur[1]) << (عدد_بٹ + 8)); p_اندر_buf_cur += 2; عدد_بٹ += 16; \
    } \
  } \
  اگر ((عارضی = (pHuff)->m_look_اوپر[ثنائی_ہندسہ_buf & (TINFL_FAST_LOOKUP_سائز - 1)]) >= 0) \
    رمز_len = عارضی >> 9, عارضی &= 511; \
  ورنہ { \
    رمز_len = TINFL_FAST_LOOKUP_بٹ; کرو { عارضی = (pHuff)->m_درخت[~عارضی + ((ثنائی_ہندسہ_buf >> رمز_len++) & 1)]; } جب (عارضی < 0); \
  } sym = عارضی; ثنائی_ہندسہ_buf >>= رمز_len; عدد_بٹ -= رمز_len; } MZ_MACRO_انتہا

tinfl_حالت tinfl_decompress(tinfl_decompressor *r, ثابت mz_uint8 *p_اندر_buf_اگلا, size_t *p_اندر_buf_سائز, mz_uint8 *p_برآمد_buf_آغاز, mz_uint8 *p_برآمد_buf_اگلا, size_t *p_برآمد_buf_سائز, ثابت mz_uint32 decomp_flags)
{
  ساکن ثابت صحیح s_لمبائی_بنیاد[31] = { 3,4,5,6,7,8,9,10,11,13, 15,17,19,23,27,31,35,43,51,59, 67,83,99,115,131,163,195,227,258,0,0 };
  ساکن ثابت صحیح s_لمبائی_extra[31]= { 0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,0,0,0 };
  ساکن ثابت صحیح s_dist_بنیاد[32] = { 1,2,3,4,5,7,9,13,17,25,33,49,65,97,129,193, 257,385,513,769,1025,1537,2049,3073,4097,6145,8193,12289,16385,24577,0,0};
  ساکن ثابت صحیح s_dist_extra[32] = { 0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13};
  ساکن ثابت mz_uint8 s_لمبائی_dezigzag[19] = { 16,17,18,0,8,7,9,6,10,5,11,4,12,3,13,2,14,1,15 };
  ساکن ثابت صحیح s_min_جدول_sizes[3] = { 257, 1, 4 };

  tinfl_حالت حالت_2 = TINFL_حالت_FAILED; mz_uint32 عدد_بٹ, dist, شمار_2, عدد_extra; tinfl_ثنائی_ہندسہ_buf_t ثنائی_ہندسہ_buf;
  ثابت mz_uint8 *p_اندر_buf_cur = p_اندر_buf_اگلا, *ثابت p_اندر_buf_انتہا = p_اندر_buf_اگلا + *p_اندر_buf_سائز;
  mz_uint8 *p_برآمد_buf_cur = p_برآمد_buf_اگلا, *ثابت p_برآمد_buf_انتہا = p_برآمد_buf_اگلا + *p_برآمد_buf_سائز;
  size_t برآمد_buf_سائز_نقاب = (decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF) ? (size_t)-1 : ((p_برآمد_buf_اگلا - p_برآمد_buf_آغاز) + *p_برآمد_buf_سائز) - 1, dist_from_برآمد_buf_آغاز;

  // Ensure the output buffer's size is a power of 2, unless the output buffer is large enough to hold the entire output file (in which case it doesn't matter).
  اگر (((برآمد_buf_سائز_نقاب + 1) & برآمد_buf_سائز_نقاب) || (p_برآمد_buf_اگلا < p_برآمد_buf_آغاز)) { *p_اندر_buf_سائز = *p_برآمد_buf_سائز = 0; واپس TINFL_حالت_BAD_PARAM; }

  عدد_بٹ = r->m_عدد_بٹ; ثنائی_ہندسہ_buf = r->m_ثنائی_ہندسہ_buf; dist = r->m_dist; شمار_2 = r->m_شمار; عدد_extra = r->m_عدد_extra; dist_from_برآمد_buf_آغاز = r->m_dist_from_برآمد_buf_آغاز;
  TINFL_CR_BEGIN

  ثنائی_ہندسہ_buf = عدد_بٹ = dist = شمار_2 = عدد_extra = r->m_zhdr0 = r->m_zhdr1 = 0; r->m_z_adler32 = r->m_check_adler32 = 1;
  اگر (decomp_flags & TINFL_FLAG_PARSE_ZLIB_سرخی)
  {
    TINFL_GET_BYTE(1, r->m_zhdr0); TINFL_GET_BYTE(2, r->m_zhdr1);
    شمار_2 = (((r->m_zhdr0 * 256 + r->m_zhdr1) % 31 != 0) || (r->m_zhdr1 & 32) || ((r->m_zhdr0 & 15) != 8));
    اگر (!(decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF)) شمار_2 |= (((1U << (8U + (r->m_zhdr0 >> 4))) > 32768U) || ((برآمد_buf_سائز_نقاب + 1) < (size_t)(1U << (8U + (r->m_zhdr0 >> 4)))));
    اگر (شمار_2) { TINFL_CR_RETURN_FOREVER(36, TINFL_حالت_FAILED); }
  }

  کرو
  {
    TINFL_GET_بٹ(3, r->m_final, 3); r->m_type = r->m_final >> 1;
    اگر (r->m_type == 0)
    {
      TINFL_SKIP_بٹ(5, عدد_بٹ & 7);
      برائے (شمار_2 = 0; شمار_2 < 4; ++شمار_2) { اگر (عدد_بٹ) TINFL_GET_بٹ(6, r->m_raw_سرخی[شمار_2], 8); ورنہ TINFL_GET_BYTE(7, r->m_raw_سرخی[شمار_2]); }
      اگر ((شمار_2 = (r->m_raw_سرخی[0] | (r->m_raw_سرخی[1] << 8))) != (mz_uint)(0xFFFF ^ (r->m_raw_سرخی[2] | (r->m_raw_سرخی[3] << 8)))) { TINFL_CR_RETURN_FOREVER(39, TINFL_حالت_FAILED); }
      جب ((شمار_2) && (عدد_بٹ))
      {
        TINFL_GET_بٹ(51, dist, 8);
        جب (p_برآمد_buf_cur >= p_برآمد_buf_انتہا) { TINFL_CR_RETURN(52, TINFL_حالت_HAS_مزید_OUTPUT); }
        *p_برآمد_buf_cur++ = (mz_uint8)dist;
        شمار_2--;
      }
      جب (شمار_2)
      {
        size_t n; جب (p_برآمد_buf_cur >= p_برآمد_buf_انتہا) { TINFL_CR_RETURN(9, TINFL_حالت_HAS_مزید_OUTPUT); }
        جب (p_اندر_buf_cur >= p_اندر_buf_انتہا)
        {
          اگر (decomp_flags & TINFL_FLAG_HAS_مزید_داخلہ)
          {
            TINFL_CR_RETURN(38, TINFL_حالت_NEEDS_مزید_داخلہ);
          }
          ورنہ
          {
            TINFL_CR_RETURN_FOREVER(40, TINFL_حالت_FAILED);
          }
        }
        n = MZ_MIN(MZ_MIN((size_t)(p_برآمد_buf_انتہا - p_برآمد_buf_cur), (size_t)(p_اندر_buf_انتہا - p_اندر_buf_cur)), شمار_2);
        TINFL_MEMCPY(p_برآمد_buf_cur, p_اندر_buf_cur, n); p_اندر_buf_cur += n; p_برآمد_buf_cur += n; شمار_2 -= (mz_uint)n;
      }
    }
    ورنہ اگر (r->m_type == 3)
    {
      TINFL_CR_RETURN_FOREVER(10, TINFL_حالت_FAILED);
    }
    ورنہ
    {
      اگر (r->m_type == 1)
      {
        mz_uint8 *p = r->m_tables[0].m_رمز_سائز; mz_uint i;
        r->m_جدول_sizes[0] = 288; r->m_جدول_sizes[1] = 32; TINFL_MEMSET(r->m_tables[1].m_رمز_سائز, 5, 32);
        برائے ( i = 0; i <= 143; ++i) *p++ = 8;
        برائے ( ; i <= 255; ++i) *p++ = 9;
        برائے ( ; i <= 279; ++i) *p++ = 7;
        برائے ( ; i <= 287; ++i) *p++ = 8;
      }
      ورنہ
      {
        برائے (شمار_2 = 0; شمار_2 < 3; شمار_2++) { TINFL_GET_بٹ(11, r->m_جدول_sizes[شمار_2], "\05\05\04"[شمار_2]); r->m_جدول_sizes[شمار_2] += s_min_جدول_sizes[شمار_2]; }
        MZ_CLEAR_ARR(r->m_tables[2].m_رمز_سائز); برائے (شمار_2 = 0; شمار_2 < r->m_جدول_sizes[2]; شمار_2++) { mz_uint s; TINFL_GET_بٹ(14, s, 3); r->m_tables[2].m_رمز_سائز[s_لمبائی_dezigzag[شمار_2]] = (mz_uint8)s; }
        r->m_جدول_sizes[2] = 19;
      }
      برائے ( ; (صحیح)r->m_type >= 0; r->m_type--)
      {
        صحیح درخت_اگلا, درخت_cur; tinfl_huff_جدول *p_جدول;
        mz_uint i, j, مستعمل_syms, کل, sym_اشاریہ, اگلا_رمز[17], کل_syms[16]; p_جدول = &r->m_tables[r->m_type]; MZ_CLEAR_ARR(کل_syms); MZ_CLEAR_ARR(p_جدول->m_look_اوپر); MZ_CLEAR_ARR(p_جدول->m_درخت);
        برائے (i = 0; i < r->m_جدول_sizes[r->m_type]; ++i) کل_syms[p_جدول->m_رمز_سائز[i]]++;
        مستعمل_syms = 0, کل = 0; اگلا_رمز[0] = اگلا_رمز[1] = 0;
        برائے (i = 1; i <= 15; ++i) { مستعمل_syms += کل_syms[i]; اگلا_رمز[i + 1] = (کل = ((کل + کل_syms[i]) << 1)); }
        اگر ((65536 != کل) && (مستعمل_syms > 1))
        {
          TINFL_CR_RETURN_FOREVER(35, TINFL_حالت_FAILED);
        }
        برائے (درخت_اگلا = -1, sym_اشاریہ = 0; sym_اشاریہ < r->m_جدول_sizes[r->m_type]; ++sym_اشاریہ)
        {
          mz_uint rev_رمز = 0, l, cur_رمز, رمز_سائز_2 = p_جدول->m_رمز_سائز[sym_اشاریہ]; اگر (!رمز_سائز_2) جاری;
          cur_رمز = اگلا_رمز[رمز_سائز_2]++; برائے (l = رمز_سائز_2; l > 0; l--, cur_رمز >>= 1) rev_رمز = (rev_رمز << 1) | (cur_رمز & 1);
          اگر (رمز_سائز_2 <= TINFL_FAST_LOOKUP_بٹ) { mz_int16 k = (mz_int16)((رمز_سائز_2 << 9) | sym_اشاریہ); جب (rev_رمز < TINFL_FAST_LOOKUP_سائز) { p_جدول->m_look_اوپر[rev_رمز] = k; rev_رمز += (1 << رمز_سائز_2); } جاری; }
          اگر (0 == (درخت_cur = p_جدول->m_look_اوپر[rev_رمز & (TINFL_FAST_LOOKUP_سائز - 1)])) { p_جدول->m_look_اوپر[rev_رمز & (TINFL_FAST_LOOKUP_سائز - 1)] = (mz_int16)درخت_اگلا; درخت_cur = درخت_اگلا; درخت_اگلا -= 2; }
          rev_رمز >>= (TINFL_FAST_LOOKUP_بٹ - 1);
          برائے (j = رمز_سائز_2; j > (TINFL_FAST_LOOKUP_بٹ + 1); j--)
          {
            درخت_cur -= ((rev_رمز >>= 1) & 1);
            اگر (!p_جدول->m_درخت[-درخت_cur - 1]) { p_جدول->m_درخت[-درخت_cur - 1] = (mz_int16)درخت_اگلا; درخت_cur = درخت_اگلا; درخت_اگلا -= 2; } ورنہ درخت_cur = p_جدول->m_درخت[-درخت_cur - 1];
          }
          درخت_cur -= ((rev_رمز >>= 1) & 1); p_جدول->m_درخت[-درخت_cur - 1] = (mz_int16)sym_اشاریہ;
        }
        اگر (r->m_type == 2)
        {
          برائے (شمار_2 = 0; شمار_2 < (r->m_جدول_sizes[0] + r->m_جدول_sizes[1]); )
          {
            mz_uint s; TINFL_HUFF_DECODE(16, dist, &r->m_tables[2]); اگر (dist < 16) { r->m_len_codes[شمار_2++] = (mz_uint8)dist; جاری; }
            اگر ((dist == 16) && (!شمار_2))
            {
              TINFL_CR_RETURN_FOREVER(17, TINFL_حالت_FAILED);
            }
            عدد_extra = "\02\03\07"[dist - 16]; TINFL_GET_بٹ(18, s, عدد_extra); s += "\03\03\013"[dist - 16];
            TINFL_MEMSET(r->m_len_codes + شمار_2, (dist == 16) ? r->m_len_codes[شمار_2 - 1] : 0, s); شمار_2 += s;
          }
          اگر ((r->m_جدول_sizes[0] + r->m_جدول_sizes[1]) != شمار_2)
          {
            TINFL_CR_RETURN_FOREVER(21, TINFL_حالت_FAILED);
          }
          TINFL_MEMCPY(r->m_tables[0].m_رمز_سائز, r->m_len_codes, r->m_جدول_sizes[0]); TINFL_MEMCPY(r->m_tables[1].m_رمز_سائز, r->m_len_codes + r->m_جدول_sizes[0], r->m_جدول_sizes[1]);
        }
      }
      برائے ( ; ; )
      {
        mz_uint8 *pSrc;
        برائے ( ; ; )
        {
          اگر (((p_اندر_buf_انتہا - p_اندر_buf_cur) < 4) || ((p_برآمد_buf_انتہا - p_برآمد_buf_cur) < 2))
          {
            TINFL_HUFF_DECODE(23, شمار_2, &r->m_tables[0]);
            اگر (شمار_2 >= 256)
              توڑو;
            جب (p_برآمد_buf_cur >= p_برآمد_buf_انتہا) { TINFL_CR_RETURN(24, TINFL_حالت_HAS_مزید_OUTPUT); }
            *p_برآمد_buf_cur++ = (mz_uint8)شمار_2;
          }
          ورنہ
          {
            صحیح sym2; mz_uint رمز_len;
#اگر TINFL_USE_64_ثنائی_ہندسہ_BITBUF
            اگر (عدد_بٹ < 30) { ثنائی_ہندسہ_buf |= (((tinfl_ثنائی_ہندسہ_buf_t)MZ_READ_LE32(p_اندر_buf_cur)) << عدد_بٹ); p_اندر_buf_cur += 4; عدد_بٹ += 32; }
#ورنہ
            اگر (عدد_بٹ < 15) { ثنائی_ہندسہ_buf |= (((tinfl_ثنائی_ہندسہ_buf_t)MZ_READ_LE16(p_اندر_buf_cur)) << عدد_بٹ); p_اندر_buf_cur += 2; عدد_بٹ += 16; }
#اگر_ختم
            اگر ((sym2 = r->m_tables[0].m_look_اوپر[ثنائی_ہندسہ_buf & (TINFL_FAST_LOOKUP_سائز - 1)]) >= 0)
              رمز_len = sym2 >> 9;
            ورنہ
            {
              رمز_len = TINFL_FAST_LOOKUP_بٹ; کرو { sym2 = r->m_tables[0].m_درخت[~sym2 + ((ثنائی_ہندسہ_buf >> رمز_len++) & 1)]; } جب (sym2 < 0);
            }
            شمار_2 = sym2; ثنائی_ہندسہ_buf >>= رمز_len; عدد_بٹ -= رمز_len;
            اگر (شمار_2 & 256)
              توڑو;

#اگر !TINFL_USE_64_ثنائی_ہندسہ_BITBUF
            اگر (عدد_بٹ < 15) { ثنائی_ہندسہ_buf |= (((tinfl_ثنائی_ہندسہ_buf_t)MZ_READ_LE16(p_اندر_buf_cur)) << عدد_بٹ); p_اندر_buf_cur += 2; عدد_بٹ += 16; }
#اگر_ختم
            اگر ((sym2 = r->m_tables[0].m_look_اوپر[ثنائی_ہندسہ_buf & (TINFL_FAST_LOOKUP_سائز - 1)]) >= 0)
              رمز_len = sym2 >> 9;
            ورنہ
            {
              رمز_len = TINFL_FAST_LOOKUP_بٹ; کرو { sym2 = r->m_tables[0].m_درخت[~sym2 + ((ثنائی_ہندسہ_buf >> رمز_len++) & 1)]; } جب (sym2 < 0);
            }
            ثنائی_ہندسہ_buf >>= رمز_len; عدد_بٹ -= رمز_len;

            p_برآمد_buf_cur[0] = (mz_uint8)شمار_2;
            اگر (sym2 & 256)
            {
              p_برآمد_buf_cur++;
              شمار_2 = sym2;
              توڑو;
            }
            p_برآمد_buf_cur[1] = (mz_uint8)sym2;
            p_برآمد_buf_cur += 2;
          }
        }
        اگر ((شمار_2 &= 511) == 256) توڑو;

        عدد_extra = s_لمبائی_extra[شمار_2 - 257]; شمار_2 = s_لمبائی_بنیاد[شمار_2 - 257];
        اگر (عدد_extra) { mz_uint extra_بٹ; TINFL_GET_بٹ(25, extra_بٹ, عدد_extra); شمار_2 += extra_بٹ; }

        TINFL_HUFF_DECODE(26, dist, &r->m_tables[1]);
        عدد_extra = s_dist_extra[dist]; dist = s_dist_بنیاد[dist];
        اگر (عدد_extra) { mz_uint extra_بٹ; TINFL_GET_بٹ(27, extra_بٹ, عدد_extra); dist += extra_بٹ; }

        dist_from_برآمد_buf_آغاز = p_برآمد_buf_cur - p_برآمد_buf_آغاز;
        اگر ((dist > dist_from_برآمد_buf_آغاز) && (decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF))
        {
          TINFL_CR_RETURN_FOREVER(37, TINFL_حالت_FAILED);
        }

        pSrc = p_برآمد_buf_آغاز + ((dist_from_برآمد_buf_آغاز - dist) & برآمد_buf_سائز_نقاب);

        اگر ((MZ_MAX(p_برآمد_buf_cur, pSrc) + شمار_2) > p_برآمد_buf_انتہا)
        {
          جب (شمار_2--)
          {
            جب (p_برآمد_buf_cur >= p_برآمد_buf_انتہا) { TINFL_CR_RETURN(53, TINFL_حالت_HAS_مزید_OUTPUT); }
            *p_برآمد_buf_cur++ = p_برآمد_buf_آغاز[(dist_from_برآمد_buf_آغاز++ - dist) & برآمد_buf_سائز_نقاب];
          }
          جاری;
        }
#اگر MINIZ_USE_UNALIGNED_LOADS_AND_STORES
        ورنہ اگر ((شمار_2 >= 9) && (شمار_2 <= dist))
        {
          ثابت mz_uint8 *p_Src_انتہا = pSrc + (شمار_2 & ~7);
          کرو
          {
            ((mz_uint32 *)p_برآمد_buf_cur)[0] = ((ثابت mz_uint32 *)pSrc)[0];
            ((mz_uint32 *)p_برآمد_buf_cur)[1] = ((ثابت mz_uint32 *)pSrc)[1];
            p_برآمد_buf_cur += 8;
          } جب ((pSrc += 8) < p_Src_انتہا);
          اگر ((شمار_2 &= 7) < 3)
          {
            اگر (شمار_2)
            {
              p_برآمد_buf_cur[0] = pSrc[0];
              اگر (شمار_2 > 1)
                p_برآمد_buf_cur[1] = pSrc[1];
              p_برآمد_buf_cur += شمار_2;
            }
            جاری;
          }
        }
#اگر_ختم
        کرو
        {
          p_برآمد_buf_cur[0] = pSrc[0];
          p_برآمد_buf_cur[1] = pSrc[1];
          p_برآمد_buf_cur[2] = pSrc[2];
          p_برآمد_buf_cur += 3; pSrc += 3;
        } جب ((صحیح)(شمار_2 -= 3) > 2);
        اگر ((صحیح)شمار_2 > 0)
        {
          p_برآمد_buf_cur[0] = pSrc[0];
          اگر ((صحیح)شمار_2 > 1)
            p_برآمد_buf_cur[1] = pSrc[1];
          p_برآمد_buf_cur += شمار_2;
        }
      }
    }
  } جب (!(r->m_final & 1));
  اگر (decomp_flags & TINFL_FLAG_PARSE_ZLIB_سرخی)
  {
    TINFL_SKIP_بٹ(32, عدد_بٹ & 7); برائے (شمار_2 = 0; شمار_2 < 4; ++شمار_2) { mz_uint s; اگر (عدد_بٹ) TINFL_GET_بٹ(41, s, 8); ورنہ TINFL_GET_BYTE(42, s); r->m_z_adler32 = (r->m_z_adler32 << 8) | s; }
  }
  TINFL_CR_RETURN_FOREVER(34, TINFL_حالت_مکمل);
  TINFL_CR_اختتام

common_exit:
  r->m_عدد_بٹ = عدد_بٹ; r->m_ثنائی_ہندسہ_buf = ثنائی_ہندسہ_buf; r->m_dist = dist; r->m_شمار = شمار_2; r->m_عدد_extra = عدد_extra; r->m_dist_from_برآمد_buf_آغاز = dist_from_برآمد_buf_آغاز;
  *p_اندر_buf_سائز = p_اندر_buf_cur - p_اندر_buf_اگلا; *p_برآمد_buf_سائز = p_برآمد_buf_cur - p_برآمد_buf_اگلا;
  اگر ((decomp_flags & (TINFL_FLAG_PARSE_ZLIB_سرخی | TINFL_FLAG_COMPUTE_ADLER32)) && (حالت_2 >= 0))
  {
    ثابت mz_uint8 *ptr = p_برآمد_buf_اگلا; size_t buf_len = *p_برآمد_buf_سائز;
    mz_uint32 i, s1 = r->m_check_adler32 & 0xffff, s2 = r->m_check_adler32 >> 16; size_t بلاک_len = buf_len % 5552;
    جب (buf_len)
    {
      برائے (i = 0; i + 7 < بلاک_len; i += 8, ptr += 8)
      {
        s1 += ptr[0], s2 += s1; s1 += ptr[1], s2 += s1; s1 += ptr[2], s2 += s1; s1 += ptr[3], s2 += s1;
        s1 += ptr[4], s2 += s1; s1 += ptr[5], s2 += s1; s1 += ptr[6], s2 += s1; s1 += ptr[7], s2 += s1;
      }
      برائے ( ; i < بلاک_len; ++i) s1 += *ptr++, s2 += s1;
      s1 %= 65521U, s2 %= 65521U; buf_len -= بلاک_len; بلاک_len = 5552;
    }
    r->m_check_adler32 = (s2 << 16) + s1; اگر ((حالت_2 == TINFL_حالت_مکمل) && (decomp_flags & TINFL_FLAG_PARSE_ZLIB_سرخی) && (r->m_check_adler32 != r->m_z_adler32)) حالت_2 = TINFL_حالت_ADLER32_MISMATCH;
  }
  واپس حالت_2;
}

// Higher level helper functions.
خالی *tinfl_decompress_mem_مقصد_ڈھیر(ثابت خالی *pSrc_buf, size_t src_buf_len, size_t *p_برآمد_len, صحیح flags)
{
  tinfl_decompressor decomp; خالی *pBuf = تہی, *pNew_buf; size_t src_buf_ofs = 0, برآمد_buf_استعداد = 0;
  *p_برآمد_len = 0;
  tinfl_init(&decomp);
  برائے ( ; ; )
  {
    size_t src_buf_سائز = src_buf_len - src_buf_ofs, dst_buf_سائز = برآمد_buf_استعداد - *p_برآمد_len, new_برآمد_buf_استعداد;
    tinfl_حالت حالت_2 = tinfl_decompress(&decomp, (ثابت mz_uint8*)pSrc_buf + src_buf_ofs, &src_buf_سائز, (mz_uint8*)pBuf, pBuf ? (mz_uint8*)pBuf + *p_برآمد_len : تہی, &dst_buf_سائز,
      (flags & ~TINFL_FLAG_HAS_مزید_داخلہ) | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF);
    اگر ((حالت_2 < 0) || (حالت_2 == TINFL_حالت_NEEDS_مزید_داخلہ))
    {
      MZ_FREE(pBuf); *p_برآمد_len = 0; واپس تہی;
    }
    src_buf_ofs += src_buf_سائز;
    *p_برآمد_len += dst_buf_سائز;
    اگر (حالت_2 == TINFL_حالت_مکمل) توڑو;
    new_برآمد_buf_استعداد = برآمد_buf_استعداد * 2; اگر (new_برآمد_buf_استعداد < 128) new_برآمد_buf_استعداد = 128;
    pNew_buf = MZ_REALLOC(pBuf, new_برآمد_buf_استعداد);
    اگر (!pNew_buf)
    {
      MZ_FREE(pBuf); *p_برآمد_len = 0; واپس تہی;
    }
    pBuf = pNew_buf; برآمد_buf_استعداد = new_برآمد_buf_استعداد;
  }
  واپس pBuf;
}

size_t tinfl_decompress_mem_مقصد_mem(خالی *p_برآمد_buf, size_t برآمد_buf_len, ثابت خالی *pSrc_buf, size_t src_buf_len, صحیح flags)
{
  tinfl_decompressor decomp; tinfl_حالت حالت_2; tinfl_init(&decomp);
  حالت_2 = tinfl_decompress(&decomp, (ثابت mz_uint8*)pSrc_buf, &src_buf_len, (mz_uint8*)p_برآمد_buf, (mz_uint8*)p_برآمد_buf, &برآمد_buf_len, (flags & ~TINFL_FLAG_HAS_مزید_داخلہ) | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF);
  واپس (حالت_2 != TINFL_حالت_مکمل) ? TINFL_DECOMPRESS_MEM_مقصد_MEM_FAILED : برآمد_buf_len;
}

صحیح tinfl_decompress_mem_مقصد_callback(ثابت خالی *p_اندر_buf, size_t *p_اندر_buf_سائز, tinfl_put_buf_func_ptr pPut_buf_func, خالی *pPut_buf_user, صحیح flags)
{
  صحیح نتیجہ = 0;
  tinfl_decompressor decomp;
  mz_uint8 *pDict = (mz_uint8*)MZ_MALLOC(TINFL_LZ_DICT_سائز); size_t اندر_buf_ofs = 0, dict_ofs = 0;
  اگر (!pDict)
    واپس TINFL_حالت_FAILED;
  memset(pDict,0,TINFL_LZ_DICT_سائز);
  tinfl_init(&decomp);
  برائے ( ; ; )
  {
    size_t اندر_buf_سائز = *p_اندر_buf_سائز - اندر_buf_ofs, dst_buf_سائز = TINFL_LZ_DICT_سائز - dict_ofs;
    tinfl_حالت حالت_2 = tinfl_decompress(&decomp, (ثابت mz_uint8*)p_اندر_buf + اندر_buf_ofs, &اندر_buf_سائز, pDict, pDict + dict_ofs, &dst_buf_سائز,
      (flags & ~(TINFL_FLAG_HAS_مزید_داخلہ | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF)));
    اندر_buf_ofs += اندر_buf_سائز;
    اگر ((dst_buf_سائز) && (!(*pPut_buf_func)(pDict + dict_ofs, (صحیح)dst_buf_سائز, pPut_buf_user)))
      توڑو;
    اگر (حالت_2 != TINFL_حالت_HAS_مزید_OUTPUT)
    {
      نتیجہ = (حالت_2 == TINFL_حالت_مکمل);
      توڑو;
    }
    dict_ofs = (dict_ofs + dst_buf_سائز) & (TINFL_LZ_DICT_سائز - 1);
  }
  MZ_FREE(pDict);
  *p_اندر_buf_سائز = اندر_buf_ofs;
  واپس نتیجہ;
}
#اگر_ختم /*#ifndef MINIZ_NO_INFLATE_APIS*/

// ------------------- Low-level Compression (independent from all decompression API's)
#اگر_غیر_تعریف_شدہ MINIZ_NO_DEFLATE_APIS

// Purposely making these tables static for faster init and thread safety.
ساکن ثابت mz_uint16 s_tdefl_len_sym[256] = {
  257,258,259,260,261,262,263,264,265,265,266,266,267,267,268,268,269,269,269,269,270,270,270,270,271,271,271,271,272,272,272,272,
  273,273,273,273,273,273,273,273,274,274,274,274,274,274,274,274,275,275,275,275,275,275,275,275,276,276,276,276,276,276,276,276,
  277,277,277,277,277,277,277,277,277,277,277,277,277,277,277,277,278,278,278,278,278,278,278,278,278,278,278,278,278,278,278,278,
  279,279,279,279,279,279,279,279,279,279,279,279,279,279,279,279,280,280,280,280,280,280,280,280,280,280,280,280,280,280,280,280,
  281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,
  282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,
  283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,
  284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,285 };

ساکن ثابت mz_uint8 s_tdefl_len_extra[256] = {
  0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0 };

ساکن ثابت mz_uint8 s_tdefl_small_dist_sym[512] = {
  0,1,2,3,4,4,5,5,6,6,6,6,7,7,7,7,8,8,8,8,8,8,8,8,9,9,9,9,9,9,9,9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,11,11,11,11,11,11,
  11,11,11,11,11,11,11,11,11,11,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,13,
  13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,14,14,14,14,14,14,14,14,14,14,14,14,
  14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,
  14,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
  15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,16,16,16,16,16,16,16,16,16,16,16,16,16,
  16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,
  16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,
  16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,
  17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17,17 };

ساکن ثابت mz_uint8 s_tdefl_small_dist_extra[512] = {
  0,0,0,0,1,1,1,1,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
  6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
  6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7 };

ساکن ثابت mz_uint8 s_tdefl_large_dist_sym[128] = {
  0,0,18,19,20,20,21,21,22,22,22,22,23,23,23,23,24,24,24,24,24,24,24,24,25,25,25,25,25,25,25,25,26,26,26,26,26,26,26,26,26,26,26,26,
  26,26,26,26,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,
  28,28,28,28,28,28,28,28,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29 };

ساکن ثابت mz_uint8 s_tdefl_large_dist_extra[128] = {
  0,0,8,8,9,9,9,9,10,10,10,10,10,10,10,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,
  12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
  13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13 };

// Radix sorts tdefl_sym_freq[] array by 16-bit key m_key. Returns ptr to sorted values.
قسمتعریف ساخت { mz_uint16 m_کلید, m_sym_اشاریہ; } tdefl_sym_freq;
ساکن tdefl_sym_freq* tdefl_radix_ترتیب_دو_syms(mz_uint عدد_syms, tdefl_sym_freq* pSyms0, tdefl_sym_freq* pSyms1)
{
  mz_uint32 کل_passes = 2, pass_سرکاؤ, pass, i, hist[256 * 2]; tdefl_sym_freq* pCur_syms = pSyms0, *pNew_syms = pSyms1; MZ_CLEAR_ARR(hist);
  برائے (i = 0; i < عدد_syms; i++) { mz_uint freq = pSyms0[i].m_کلید; hist[freq & 0xFF]++; hist[256 + ((freq >> 8) & 0xFF)]++; }
  جب ((کل_passes > 1) && (عدد_syms == hist[(کل_passes - 1) * 256])) کل_passes--;
  برائے (pass_سرکاؤ = 0, pass = 0; pass < کل_passes; pass++, pass_سرکاؤ += 8)
  {
    ثابت mz_uint32* pHist = &hist[pass << 8];
    mz_uint offsets[256], cur_ofs = 0;
    برائے (i = 0; i < 256; i++) { offsets[i] = cur_ofs; cur_ofs += pHist[i]; }
    برائے (i = 0; i < عدد_syms; i++) pNew_syms[offsets[(pCur_syms[i].m_کلید >> pass_سرکاؤ) & 0xFF]++] = pCur_syms[i];
    { tdefl_sym_freq* t = pCur_syms; pCur_syms = pNew_syms; pNew_syms = t; }
  }
  واپس pCur_syms;
}

// tdefl_calculate_minimum_redundancy() originally written by: Alistair Moffat, alistair@cs.mu.oz.au, Jyrki Katajainen, jyrki@diku.dk, November 1996.
ساکن خالی tdefl_calculate_minimum_redundancy(tdefl_sym_freq *A, صحیح n)
{
  صحیح جڑ, برگ, اگلا, avbl, مستعمل, dpth;
  اگر (n==0) واپس; ورنہ اگر (n==1) { A[0].m_کلید = 1; واپس; }
  A[0].m_کلید += A[1].m_کلید; جڑ = 0; برگ = 2;
  برائے (اگلا=1; اگلا < n-1; اگلا++)
  {
    اگر (برگ>=n || A[جڑ].m_کلید<A[برگ].m_کلید) { A[اگلا].m_کلید = A[جڑ].m_کلید; A[جڑ++].m_کلید = (mz_uint16)اگلا; } ورنہ A[اگلا].m_کلید = A[برگ++].m_کلید;
    اگر (برگ>=n || (جڑ<اگلا && A[جڑ].m_کلید<A[برگ].m_کلید)) { A[اگلا].m_کلید = (mz_uint16)(A[اگلا].m_کلید + A[جڑ].m_کلید); A[جڑ++].m_کلید = (mz_uint16)اگلا; } ورنہ A[اگلا].m_کلید = (mz_uint16)(A[اگلا].m_کلید + A[برگ++].m_کلید);
  }
  A[n-2].m_کلید = 0; برائے (اگلا=n-3; اگلا>=0; اگلا--) A[اگلا].m_کلید = A[A[اگلا].m_کلید].m_کلید+1;
  avbl = 1; مستعمل = dpth = 0; جڑ = n-2; اگلا = n-1;
  جب (avbl>0)
  {
    جب (جڑ>=0 && (صحیح)A[جڑ].m_کلید==dpth) { مستعمل++; جڑ--; }
    جب (avbl>مستعمل) { A[اگلا--].m_کلید = (mz_uint16)(dpth); avbl--; }
    avbl = 2*مستعمل; dpth++; مستعمل = 0;
  }
}

// Limits canonical Huffman code table's max code size.
شمار { TDEFL_MAX_SUPPORTED_HUFF_CODESIZE = 32 };
ساکن خالی tdefl_huffman_enforce_max_رمز_سائز(صحیح *p_عدد_codes, صحیح رمز_list_len, صحیح max_رمز_سائز)
{
  صحیح i; mz_uint32 کل = 0; اگر (رمز_list_len <= 1) واپس;
  برائے (i = max_رمز_سائز + 1; i <= TDEFL_MAX_SUPPORTED_HUFF_CODESIZE; i++) p_عدد_codes[max_رمز_سائز] += p_عدد_codes[i];
  برائے (i = max_رمز_سائز; i > 0; i--) کل += (((mz_uint32)p_عدد_codes[i]) << (max_رمز_سائز - i));
  جب (کل != (1UL << max_رمز_سائز))
  {
    p_عدد_codes[max_رمز_سائز]--;
    برائے (i = max_رمز_سائز - 1; i > 0; i--) اگر (p_عدد_codes[i]) { p_عدد_codes[i]--; p_عدد_codes[i + 1] += 2; توڑو; }
    کل--;
  }
}

ساکن خالی tdefl_optimize_huffman_جدول(tdefl_compressor *d, صحیح جدول_عدد, صحیح جدول_len, صحیح رمز_سائز_حد_بندی, صحیح static_جدول)
{
  صحیح i, j, l, عدد_codes[1 + TDEFL_MAX_SUPPORTED_HUFF_CODESIZE]; mz_uint اگلا_رمز[TDEFL_MAX_SUPPORTED_HUFF_CODESIZE + 1]; MZ_CLEAR_ARR(عدد_codes);
  اگر (static_جدول)
  {
    برائے (i = 0; i < جدول_len; i++) عدد_codes[d->m_huff_رمز_sizes[جدول_عدد][i]]++;
  }
  ورنہ
  {
    tdefl_sym_freq syms0[TDEFL_MAX_HUFF_SYMBOLS], syms1[TDEFL_MAX_HUFF_SYMBOLS], *pSyms;
    صحیح عدد_مستعمل_syms = 0;
    ثابت mz_uint16 *p_Sym_گنتی = &d->m_huff_گنتی[جدول_عدد][0];
    برائے (i = 0; i < جدول_len; i++) اگر (p_Sym_گنتی[i]) { syms0[عدد_مستعمل_syms].m_کلید = (mz_uint16)p_Sym_گنتی[i]; syms0[عدد_مستعمل_syms++].m_sym_اشاریہ = (mz_uint16)i; }

    pSyms = tdefl_radix_ترتیب_دو_syms(عدد_مستعمل_syms, syms0, syms1); tdefl_calculate_minimum_redundancy(pSyms, عدد_مستعمل_syms);

    برائے (i = 0; i < عدد_مستعمل_syms; i++) عدد_codes[pSyms[i].m_کلید]++;

    tdefl_huffman_enforce_max_رمز_سائز(عدد_codes, عدد_مستعمل_syms, رمز_سائز_حد_بندی);

    MZ_CLEAR_ARR(d->m_huff_رمز_sizes[جدول_عدد]); MZ_CLEAR_ARR(d->m_huff_codes[جدول_عدد]);
    برائے (i = 1, j = عدد_مستعمل_syms; i <= رمز_سائز_حد_بندی; i++)
      برائے (l = عدد_codes[i]; l > 0; l--) d->m_huff_رمز_sizes[جدول_عدد][pSyms[--j].m_sym_اشاریہ] = (mz_uint8)(i);
  }

  اگلا_رمز[1] = 0; برائے (j = 0, i = 2; i <= رمز_سائز_حد_بندی; i++) اگلا_رمز[i] = j = ((j + عدد_codes[i - 1]) << 1);

  برائے (i = 0; i < جدول_len; i++)
  {
    mz_uint rev_رمز = 0, رمز, رمز_سائز_2; اگر ((رمز_سائز_2 = d->m_huff_رمز_sizes[جدول_عدد][i]) == 0) جاری;
    رمز = اگلا_رمز[رمز_سائز_2]++; برائے (l = رمز_سائز_2; l > 0; l--, رمز >>= 1) rev_رمز = (rev_رمز << 1) | (رمز & 1);
    d->m_huff_codes[جدول_عدد][i] = (mz_uint16)rev_رمز;
  }
}

#تعریف_کرو TDEFL_PUT_بٹ(b, l) کرو { \
  mz_uint بٹ = b; mz_uint len = l; MZ_ASSERT(بٹ <= ((1U << len) - 1U)); \
  d->m_ثنائی_ہندسہ_بفر |= (بٹ << d->m_بٹ_اندر); d->m_بٹ_اندر += len; \
  جب (d->m_بٹ_اندر >= 8) { \
    اگر (d->m_pOutput_buf < d->m_p_Output_buf_انتہا) \
      *d->m_pOutput_buf++ = (mz_uint8)(d->m_ثنائی_ہندسہ_بفر); \
    d->m_ثنائی_ہندسہ_بفر >>= 8; \
    d->m_بٹ_اندر -= 8; \
  } \
} MZ_MACRO_انتہا

#تعریف_کرو TDEFL_RLE_پچھلا_رمز_سائز() کرو { \
  اگر (rle_repeat_گنتی) { \
    اگر (rle_repeat_گنتی < 3) { \
      d->m_huff_گنتی[2][پچھلا_رمز_سائز] = (mz_uint16)(d->m_huff_گنتی[2][پچھلا_رمز_سائز] + rle_repeat_گنتی); \
      جب (rle_repeat_گنتی--) packed_رمز_sizes[عدد_packed_رمز_sizes++] = پچھلا_رمز_سائز; \
    } ورنہ { \
      d->m_huff_گنتی[2][16] = (mz_uint16)(d->m_huff_گنتی[2][16] + 1); packed_رمز_sizes[عدد_packed_رمز_sizes++] = 16; packed_رمز_sizes[عدد_packed_رمز_sizes++] = (mz_uint8)(rle_repeat_گنتی - 3); \
  } rle_repeat_گنتی = 0; } \
} MZ_MACRO_انتہا

#تعریف_کرو TDEFL_RLE_ZERO_رمز_سائز() کرو { \
  اگر (rle_z_گنتی) { \
    اگر (rle_z_گنتی < 3) { \
      d->m_huff_گنتی[2][0] = (mz_uint16)(d->m_huff_گنتی[2][0] + rle_z_گنتی); جب (rle_z_گنتی--) packed_رمز_sizes[عدد_packed_رمز_sizes++] = 0; \
    } ورنہ اگر (rle_z_گنتی <= 10) { \
      d->m_huff_گنتی[2][17] = (mz_uint16)(d->m_huff_گنتی[2][17] + 1); packed_رمز_sizes[عدد_packed_رمز_sizes++] = 17; packed_رمز_sizes[عدد_packed_رمز_sizes++] = (mz_uint8)(rle_z_گنتی - 3); \
    } ورنہ { \
      d->m_huff_گنتی[2][18] = (mz_uint16)(d->m_huff_گنتی[2][18] + 1); packed_رمز_sizes[عدد_packed_رمز_sizes++] = 18; packed_رمز_sizes[عدد_packed_رمز_sizes++] = (mz_uint8)(rle_z_گنتی - 11); \
  } rle_z_گنتی = 0; } \
} MZ_MACRO_انتہا

ساکن mz_uint8 s_tdefl_packed_رمز_سائز_syms_swizzle[] = { 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 };

ساکن خالی tdefl_آغاز_dynamic_بلاک(tdefl_compressor *d)
{
  صحیح عدد_lit_codes, عدد_dist_codes, عدد_ثنائی_ہندسہ_lengths; mz_uint i, کل_رمز_sizes_مقصد_pack, عدد_packed_رمز_sizes, rle_z_گنتی, rle_repeat_گنتی, packed_رمز_sizes_اشاریہ;
  mz_uint8 رمز_sizes_مقصد_pack[TDEFL_MAX_HUFF_SYMBOLS_0 + TDEFL_MAX_HUFF_SYMBOLS_1], packed_رمز_sizes[TDEFL_MAX_HUFF_SYMBOLS_0 + TDEFL_MAX_HUFF_SYMBOLS_1], پچھلا_رمز_سائز = 0xFF;

  d->m_huff_گنتی[0][256] = 1;

  tdefl_optimize_huffman_جدول(d, 0, TDEFL_MAX_HUFF_SYMBOLS_0, 15, MZ_FALSE);
  tdefl_optimize_huffman_جدول(d, 1, TDEFL_MAX_HUFF_SYMBOLS_1, 15, MZ_FALSE);

  برائے (عدد_lit_codes = 286; عدد_lit_codes > 257; عدد_lit_codes--) اگر (d->m_huff_رمز_sizes[0][عدد_lit_codes - 1]) توڑو;
  برائے (عدد_dist_codes = 30; عدد_dist_codes > 1; عدد_dist_codes--) اگر (d->m_huff_رمز_sizes[1][عدد_dist_codes - 1]) توڑو;

  حافظہ_نقل(رمز_sizes_مقصد_pack, &d->m_huff_رمز_sizes[0][0], عدد_lit_codes);
  حافظہ_نقل(رمز_sizes_مقصد_pack + عدد_lit_codes, &d->m_huff_رمز_sizes[1][0], عدد_dist_codes);
  کل_رمز_sizes_مقصد_pack = عدد_lit_codes + عدد_dist_codes; عدد_packed_رمز_sizes = 0; rle_z_گنتی = 0; rle_repeat_گنتی = 0;

  memset(&d->m_huff_گنتی[2][0], 0, حجم(d->m_huff_گنتی[2][0]) * TDEFL_MAX_HUFF_SYMBOLS_2);
  برائے (i = 0; i < کل_رمز_sizes_مقصد_pack; i++)
  {
    mz_uint8 رمز_سائز_2 = رمز_sizes_مقصد_pack[i];
    اگر (!رمز_سائز_2)
    {
      TDEFL_RLE_پچھلا_رمز_سائز();
      اگر (++rle_z_گنتی == 138) { TDEFL_RLE_ZERO_رمز_سائز(); }
    }
    ورنہ
    {
      TDEFL_RLE_ZERO_رمز_سائز();
      اگر (رمز_سائز_2 != پچھلا_رمز_سائز)
      {
        TDEFL_RLE_پچھلا_رمز_سائز();
        d->m_huff_گنتی[2][رمز_سائز_2] = (mz_uint16)(d->m_huff_گنتی[2][رمز_سائز_2] + 1); packed_رمز_sizes[عدد_packed_رمز_sizes++] = رمز_سائز_2;
      }
      ورنہ اگر (++rle_repeat_گنتی == 6)
      {
        TDEFL_RLE_پچھلا_رمز_سائز();
      }
    }
    پچھلا_رمز_سائز = رمز_سائز_2;
  }
  اگر (rle_repeat_گنتی) { TDEFL_RLE_پچھلا_رمز_سائز(); } ورنہ { TDEFL_RLE_ZERO_رمز_سائز(); }

  tdefl_optimize_huffman_جدول(d, 2, TDEFL_MAX_HUFF_SYMBOLS_2, 7, MZ_FALSE);

  TDEFL_PUT_بٹ(2, 2);

  TDEFL_PUT_بٹ(عدد_lit_codes - 257, 5);
  TDEFL_PUT_بٹ(عدد_dist_codes - 1, 5);

  برائے (عدد_ثنائی_ہندسہ_lengths = 18; عدد_ثنائی_ہندسہ_lengths >= 0; عدد_ثنائی_ہندسہ_lengths--) اگر (d->m_huff_رمز_sizes[2][s_tdefl_packed_رمز_سائز_syms_swizzle[عدد_ثنائی_ہندسہ_lengths]]) توڑو;
  عدد_ثنائی_ہندسہ_lengths = MZ_MAX(4, (عدد_ثنائی_ہندسہ_lengths + 1)); TDEFL_PUT_بٹ(عدد_ثنائی_ہندسہ_lengths - 4, 4);
  برائے (i = 0; (صحیح)i < عدد_ثنائی_ہندسہ_lengths; i++) TDEFL_PUT_بٹ(d->m_huff_رمز_sizes[2][s_tdefl_packed_رمز_سائز_syms_swizzle[i]], 3);

  برائے (packed_رمز_sizes_اشاریہ = 0; packed_رمز_sizes_اشاریہ < عدد_packed_رمز_sizes; )
  {
    mz_uint رمز = packed_رمز_sizes[packed_رمز_sizes_اشاریہ++]; MZ_ASSERT(رمز < TDEFL_MAX_HUFF_SYMBOLS_2);
    TDEFL_PUT_بٹ(d->m_huff_codes[2][رمز], d->m_huff_رمز_sizes[2][رمز]);
    اگر (رمز >= 16) TDEFL_PUT_بٹ(packed_رمز_sizes[packed_رمز_sizes_اشاریہ++], "\02\03\07"[رمز - 16]);
  }
}

ساکن خالی tdefl_آغاز_static_بلاک(tdefl_compressor *d)
{
  mz_uint i;
  mz_uint8 *p = &d->m_huff_رمز_sizes[0][0];

  برائے (i = 0; i <= 143; ++i) *p++ = 8;
  برائے ( ; i <= 255; ++i) *p++ = 9;
  برائے ( ; i <= 279; ++i) *p++ = 7;
  برائے ( ; i <= 287; ++i) *p++ = 8;

  memset(d->m_huff_رمز_sizes[1], 5, 32);

  tdefl_optimize_huffman_جدول(d, 0, 288, 15, MZ_TRUE);
  tdefl_optimize_huffman_جدول(d, 1, 32, 15, MZ_TRUE);

  TDEFL_PUT_بٹ(1, 2);
}

ساکن ثابت mz_uint mz_bitmasks[17] = { 0x0000, 0x0001, 0x0003, 0x0007, 0x000F, 0x001F, 0x003F, 0x007F, 0x00FF, 0x01FF, 0x03FF, 0x07FF, 0x0FFF, 0x1FFF, 0x3FFF, 0x7FFF, 0xFFFF };

#اگر MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN && MINIZ_HAS_64_ثنائی_ہندسہ_REGISTERS
ساکن mz_bool tdefl_compress_lz_codes(tdefl_compressor *d)
{
  mz_uint flags;
  mz_uint8 *pLZ_codes;
  mz_uint8 *pOutput_buf = d->m_pOutput_buf;
  mz_uint8 *p_LZ_رمز_buf_انتہا = d->m_p_LZ_رمز_buf;
  mz_uint64 ثنائی_ہندسہ_بفر = d->m_ثنائی_ہندسہ_بفر;
  mz_uint بٹ_اندر = d->m_بٹ_اندر;

#تعریف_کرو TDEFL_PUT_بٹ_FAST(b, l) { ثنائی_ہندسہ_بفر |= (((mz_uint64)(b)) << بٹ_اندر); بٹ_اندر += (l); }

  flags = 1;
  برائے (pLZ_codes = d->m_lz_رمز_buf; pLZ_codes < p_LZ_رمز_buf_انتہا; flags >>= 1)
  {
    اگر (flags == 1)
      flags = *pLZ_codes++ | 0x100;

    اگر (flags & 1)
    {
      mz_uint s0, s1, n0, n1, sym, عدد_extra_بٹ;
      mz_uint مطابقت_len = pLZ_codes[0], مطابقت_dist = *(ثابت mz_uint16 *)(pLZ_codes + 1); pLZ_codes += 3;

      MZ_ASSERT(d->m_huff_رمز_sizes[0][s_tdefl_len_sym[مطابقت_len]]);
      TDEFL_PUT_بٹ_FAST(d->m_huff_codes[0][s_tdefl_len_sym[مطابقت_len]], d->m_huff_رمز_sizes[0][s_tdefl_len_sym[مطابقت_len]]);
      TDEFL_PUT_بٹ_FAST(مطابقت_len & mz_bitmasks[s_tdefl_len_extra[مطابقت_len]], s_tdefl_len_extra[مطابقت_len]);

      // This sequence coaxes MSVC into using cmov's vs. jmp's.
      s0 = s_tdefl_small_dist_sym[مطابقت_dist & 511];
      n0 = s_tdefl_small_dist_extra[مطابقت_dist & 511];
      s1 = s_tdefl_large_dist_sym[مطابقت_dist >> 8];
      n1 = s_tdefl_large_dist_extra[مطابقت_dist >> 8];
      sym = (مطابقت_dist < 512) ? s0 : s1;
      عدد_extra_بٹ = (مطابقت_dist < 512) ? n0 : n1;

      MZ_ASSERT(d->m_huff_رمز_sizes[1][sym]);
      TDEFL_PUT_بٹ_FAST(d->m_huff_codes[1][sym], d->m_huff_رمز_sizes[1][sym]);
      TDEFL_PUT_بٹ_FAST(مطابقت_dist & mz_bitmasks[عدد_extra_بٹ], عدد_extra_بٹ);
    }
    ورنہ
    {
      mz_uint lit = *pLZ_codes++;
      MZ_ASSERT(d->m_huff_رمز_sizes[0][lit]);
      TDEFL_PUT_بٹ_FAST(d->m_huff_codes[0][lit], d->m_huff_رمز_sizes[0][lit]);

      اگر (((flags & 2) == 0) && (pLZ_codes < p_LZ_رمز_buf_انتہا))
      {
        flags >>= 1;
        lit = *pLZ_codes++;
        MZ_ASSERT(d->m_huff_رمز_sizes[0][lit]);
        TDEFL_PUT_بٹ_FAST(d->m_huff_codes[0][lit], d->m_huff_رمز_sizes[0][lit]);

        اگر (((flags & 2) == 0) && (pLZ_codes < p_LZ_رمز_buf_انتہا))
        {
          flags >>= 1;
          lit = *pLZ_codes++;
          MZ_ASSERT(d->m_huff_رمز_sizes[0][lit]);
          TDEFL_PUT_بٹ_FAST(d->m_huff_codes[0][lit], d->m_huff_رمز_sizes[0][lit]);
        }
      }
    }

    اگر (pOutput_buf >= d->m_p_Output_buf_انتہا)
      واپس MZ_FALSE;

    *(mz_uint64*)pOutput_buf = ثنائی_ہندسہ_بفر;
    pOutput_buf += (بٹ_اندر >> 3);
    ثنائی_ہندسہ_بفر >>= (بٹ_اندر & ~7);
    بٹ_اندر &= 7;
  }

#تعریف_منسوخ TDEFL_PUT_بٹ_FAST

  d->m_pOutput_buf = pOutput_buf;
  d->m_بٹ_اندر = 0;
  d->m_ثنائی_ہندسہ_بفر = 0;

  جب (بٹ_اندر)
  {
    mz_uint32 n = MZ_MIN(بٹ_اندر, 16);
    TDEFL_PUT_بٹ((mz_uint)ثنائی_ہندسہ_بفر & mz_bitmasks[n], n);
    ثنائی_ہندسہ_بفر >>= n;
    بٹ_اندر -= n;
  }

  TDEFL_PUT_بٹ(d->m_huff_codes[0][256], d->m_huff_رمز_sizes[0][256]);

  واپس (d->m_pOutput_buf < d->m_p_Output_buf_انتہا);
}
#ورنہ
ساکن mz_bool tdefl_compress_lz_codes(tdefl_compressor *d)
{
  mz_uint flags;
  mz_uint8 *pLZ_codes;

  flags = 1;
  برائے (pLZ_codes = d->m_lz_رمز_buf; pLZ_codes < d->m_p_LZ_رمز_buf; flags >>= 1)
  {
    اگر (flags == 1)
      flags = *pLZ_codes++ | 0x100;
    اگر (flags & 1)
    {
      mz_uint sym, عدد_extra_بٹ;
      mz_uint مطابقت_len = pLZ_codes[0], مطابقت_dist = (pLZ_codes[1] | (pLZ_codes[2] << 8)); pLZ_codes += 3;

      MZ_ASSERT(d->m_huff_رمز_sizes[0][s_tdefl_len_sym[مطابقت_len]]);
      TDEFL_PUT_بٹ(d->m_huff_codes[0][s_tdefl_len_sym[مطابقت_len]], d->m_huff_رمز_sizes[0][s_tdefl_len_sym[مطابقت_len]]);
      TDEFL_PUT_بٹ(مطابقت_len & mz_bitmasks[s_tdefl_len_extra[مطابقت_len]], s_tdefl_len_extra[مطابقت_len]);

      اگر (مطابقت_dist < 512)
      {
        sym = s_tdefl_small_dist_sym[مطابقت_dist]; عدد_extra_بٹ = s_tdefl_small_dist_extra[مطابقت_dist];
      }
      ورنہ
      {
        sym = s_tdefl_large_dist_sym[مطابقت_dist >> 8]; عدد_extra_بٹ = s_tdefl_large_dist_extra[مطابقت_dist >> 8];
      }
      MZ_ASSERT(d->m_huff_رمز_sizes[1][sym]);
      TDEFL_PUT_بٹ(d->m_huff_codes[1][sym], d->m_huff_رمز_sizes[1][sym]);
      TDEFL_PUT_بٹ(مطابقت_dist & mz_bitmasks[عدد_extra_بٹ], عدد_extra_بٹ);
    }
    ورنہ
    {
      mz_uint lit = *pLZ_codes++;
      MZ_ASSERT(d->m_huff_رمز_sizes[0][lit]);
      TDEFL_PUT_بٹ(d->m_huff_codes[0][lit], d->m_huff_رمز_sizes[0][lit]);
    }
  }

  TDEFL_PUT_بٹ(d->m_huff_codes[0][256], d->m_huff_رمز_sizes[0][256]);

  واپس (d->m_pOutput_buf < d->m_p_Output_buf_انتہا);
}
#اگر_ختم // MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN && MINIZ_HAS_64BIT_REGISTERS

ساکن mz_bool tdefl_compress_بلاک(tdefl_compressor *d, mz_bool static_بلاک)
{
  اگر (static_بلاک)
    tdefl_آغاز_static_بلاک(d);
  ورنہ
    tdefl_آغاز_dynamic_بلاک(d);
  واپس tdefl_compress_lz_codes(d);
}

ساکن صحیح tdefl_flush_بلاک(tdefl_compressor *d, صحیح flush)
{
  mz_uint saved_ثنائی_ہندسہ_buf, saved_بٹ_اندر;
  mz_uint8 *pSaved_output_buf;
  mz_bool comp_بلاک_succeeded = MZ_FALSE;
  صحیح n, use_raw_بلاک = ((d->m_flags & TDEFL_FORCE_ALL_RAW_بلاکیں) != 0) && (d->m_lookahead_pos - d->m_lz_رمز_buf_dict_pos) <= d->m_dict_سائز;
  mz_uint8 *p_Output_buf_آغاز = ((d->m_pPut_buf_func == تہی) && ((*d->m_p_برآمد_buf_سائز - d->m_برآمد_buf_ofs) >= TDEFL_برآمد_BUF_سائز)) ? ((mz_uint8 *)d->m_p_برآمد_buf + d->m_برآمد_buf_ofs) : d->m_output_buf;

  d->m_pOutput_buf = p_Output_buf_آغاز;
  d->m_p_Output_buf_انتہا = d->m_pOutput_buf + TDEFL_برآمد_BUF_سائز - 16;

  MZ_ASSERT(!d->m_output_flush_بقایا);
  d->m_output_flush_ofs = 0;
  d->m_output_flush_بقایا = 0;

  *d->m_pLZ_flags = (mz_uint8)(*d->m_pLZ_flags >> d->m_عدد_flags_بایاں);
  d->m_p_LZ_رمز_buf -= (d->m_عدد_flags_بایاں == 8);

  اگر ((d->m_flags & TDEFL_WRITE_ZLIB_سرخی) && (!d->m_بلاک_اشاریہ))
  {
    TDEFL_PUT_بٹ(0x78, 8); TDEFL_PUT_بٹ(0x01, 8);
  }

  TDEFL_PUT_بٹ(flush == TDEFL_اختتام, 1);

  pSaved_output_buf = d->m_pOutput_buf; saved_ثنائی_ہندسہ_buf = d->m_ثنائی_ہندسہ_بفر; saved_بٹ_اندر = d->m_بٹ_اندر;

  اگر (!use_raw_بلاک)
    comp_بلاک_succeeded = tdefl_compress_بلاک(d, (d->m_flags & TDEFL_FORCE_ALL_STATIC_بلاکیں) || (d->m_کل_lz_بائٹیں < 48));

  // If the block gets expanded, forget the current contents of the output buffer and send a raw block instead.
  اگر ( ((use_raw_بلاک) || ((d->m_کل_lz_بائٹیں) && ((d->m_pOutput_buf - pSaved_output_buf + 1U) >= d->m_کل_lz_بائٹیں))) &&
       ((d->m_lookahead_pos - d->m_lz_رمز_buf_dict_pos) <= d->m_dict_سائز) )
  {
    mz_uint i; d->m_pOutput_buf = pSaved_output_buf; d->m_ثنائی_ہندسہ_بفر = saved_ثنائی_ہندسہ_buf; d->m_بٹ_اندر = saved_بٹ_اندر;
    TDEFL_PUT_بٹ(0, 2);
    اگر (d->m_بٹ_اندر) { TDEFL_PUT_بٹ(0, 8 - d->m_بٹ_اندر); }
    برائے (i = 2; i; --i, d->m_کل_lz_بائٹیں ^= 0xFFFF)
    {
      TDEFL_PUT_بٹ(d->m_کل_lz_بائٹیں & 0xFFFF, 16);
    }
    برائے (i = 0; i < d->m_کل_lz_بائٹیں; ++i)
    {
      TDEFL_PUT_بٹ(d->m_dict[(d->m_lz_رمز_buf_dict_pos + i) & TDEFL_LZ_DICT_سائز_نقاب], 8);
    }
  }
  // Check for the extremely unlikely (if not impossible) case of the compressed block not fitting into the output buffer when using dynamic codes.
  ورنہ اگر (!comp_بلاک_succeeded)
  {
    d->m_pOutput_buf = pSaved_output_buf; d->m_ثنائی_ہندسہ_بفر = saved_ثنائی_ہندسہ_buf; d->m_بٹ_اندر = saved_بٹ_اندر;
    tdefl_compress_بلاک(d, MZ_TRUE);
  }

  اگر (flush)
  {
    اگر (flush == TDEFL_اختتام)
    {
      اگر (d->m_بٹ_اندر) { TDEFL_PUT_بٹ(0, 8 - d->m_بٹ_اندر); }
      اگر (d->m_flags & TDEFL_WRITE_ZLIB_سرخی) { mz_uint i, a = d->m_adler32; برائے (i = 0; i < 4; i++) { TDEFL_PUT_بٹ((a >> 24) & 0xFF, 8); a <<= 8; } }
    }
    ورنہ
    {
      mz_uint i, z = 0; TDEFL_PUT_بٹ(0, 3); اگر (d->m_بٹ_اندر) { TDEFL_PUT_بٹ(0, 8 - d->m_بٹ_اندر); } برائے (i = 2; i; --i, z ^= 0xFFFF) { TDEFL_PUT_بٹ(z & 0xFFFF, 16); }
    }
  }

  MZ_ASSERT(d->m_pOutput_buf < d->m_p_Output_buf_انتہا);

  memset(&d->m_huff_گنتی[0][0], 0, حجم(d->m_huff_گنتی[0][0]) * TDEFL_MAX_HUFF_SYMBOLS_0);
  memset(&d->m_huff_گنتی[1][0], 0, حجم(d->m_huff_گنتی[1][0]) * TDEFL_MAX_HUFF_SYMBOLS_1);

  d->m_p_LZ_رمز_buf = d->m_lz_رمز_buf + 1; d->m_pLZ_flags = d->m_lz_رمز_buf; d->m_عدد_flags_بایاں = 8; d->m_lz_رمز_buf_dict_pos += d->m_کل_lz_بائٹیں; d->m_کل_lz_بائٹیں = 0; d->m_بلاک_اشاریہ++;

  اگر ((n = (صحیح)(d->m_pOutput_buf - p_Output_buf_آغاز)) != 0)
  {
    اگر (d->m_pPut_buf_func)
    {
      *d->m_p_اندر_buf_سائز = d->m_pSrc - (ثابت mz_uint8 *)d->m_p_اندر_buf;
      اگر (!(*d->m_pPut_buf_func)(d->m_output_buf, n, d->m_pPut_buf_user))
        واپس (d->m_پچھلا_return_حالت = TDEFL_حالت_PUT_BUF_FAILED);
    }
    ورنہ اگر (p_Output_buf_آغاز == d->m_output_buf)
    {
      صحیح بائٹیں_مقصد_copy = (صحیح)MZ_MIN((size_t)n, (size_t)(*d->m_p_برآمد_buf_سائز - d->m_برآمد_buf_ofs));
      حافظہ_نقل((mz_uint8 *)d->m_p_برآمد_buf + d->m_برآمد_buf_ofs, d->m_output_buf, بائٹیں_مقصد_copy);
      d->m_برآمد_buf_ofs += بائٹیں_مقصد_copy;
      اگر ((n -= بائٹیں_مقصد_copy) != 0)
      {
        d->m_output_flush_ofs = بائٹیں_مقصد_copy;
        d->m_output_flush_بقایا = n;
      }
    }
    ورنہ
    {
      d->m_برآمد_buf_ofs += n;
    }
  }

  واپس d->m_output_flush_بقایا;
}

#اگر MINIZ_USE_UNALIGNED_LOADS_AND_STORES
#تعریف_کرو TDEFL_READ_UNALIGNED_لفظ(p) *(ثابت mz_uint16*)(p)
ساکن MZ_FORCEINLINE خالی tdefl_ڈھونڈو_مطابقت(tdefl_compressor *d, mz_uint lookahead_pos, mz_uint max_dist, mz_uint max_مطابقت_len, mz_uint *p_مطابقت_dist, mz_uint *p_مطابقت_len)
{
  mz_uint dist, pos = lookahead_pos & TDEFL_LZ_DICT_سائز_نقاب, مطابقت_len = *p_مطابقت_len, probe_pos = pos, اگلا_probe_pos, probe_len;
  mz_uint عدد_probes_بایاں = d->m_max_probes[مطابقت_len >= 32];
  ثابت mz_uint16 *s = (ثابت mz_uint16*)(d->m_dict + pos), *p, *q;
  mz_uint16 c01 = TDEFL_READ_UNALIGNED_لفظ(&d->m_dict[pos + مطابقت_len - 1]), s01 = TDEFL_READ_UNALIGNED_لفظ(s);
  MZ_ASSERT(max_مطابقت_len <= TDEFL_MAX_مطابقت_LEN); اگر (max_مطابقت_len <= مطابقت_len) واپس;
  برائے ( ; ; )
  {
    برائے ( ; ; )
    {
      اگر (--عدد_probes_بایاں == 0) واپس;
      #تعریف_کرو TDEFL_PROBE \
        اگلا_probe_pos = d->m_اگلا[probe_pos]; \
        اگر ((!اگلا_probe_pos) || ((dist = (mz_uint16)(lookahead_pos - اگلا_probe_pos)) > max_dist)) واپس; \
        probe_pos = اگلا_probe_pos & TDEFL_LZ_DICT_سائز_نقاب; \
        اگر (TDEFL_READ_UNALIGNED_لفظ(&d->m_dict[probe_pos + مطابقت_len - 1]) == c01) توڑو;
      TDEFL_PROBE
      TDEFL_PROBE
      TDEFL_PROBE
    }
    اگر (!dist) توڑو;
    q = (ثابت mz_uint16*)(d->m_dict + probe_pos);
    اگر (TDEFL_READ_UNALIGNED_لفظ(q) != s01) جاری;
    p = s; probe_len = 32;
    کرو { } جب ( (TDEFL_READ_UNALIGNED_لفظ(++p) == TDEFL_READ_UNALIGNED_لفظ(++q)) && (TDEFL_READ_UNALIGNED_لفظ(++p) == TDEFL_READ_UNALIGNED_لفظ(++q)) &&
                   (TDEFL_READ_UNALIGNED_لفظ(++p) == TDEFL_READ_UNALIGNED_لفظ(++q)) && (TDEFL_READ_UNALIGNED_لفظ(++p) == TDEFL_READ_UNALIGNED_لفظ(++q)) && (--probe_len > 0) );
    اگر (!probe_len)
    {
      *p_مطابقت_dist = dist; *p_مطابقت_len = MZ_MIN(max_مطابقت_len, TDEFL_MAX_مطابقت_LEN); توڑو;
    }
    ورنہ اگر ((probe_len = ((mz_uint)(p - s) * 2) + (mz_uint)(*(ثابت mz_uint8*)p == *(ثابت mz_uint8*)q)) > مطابقت_len)
    {
      *p_مطابقت_dist = dist; اگر ((*p_مطابقت_len = مطابقت_len = MZ_MIN(max_مطابقت_len, probe_len)) == max_مطابقت_len) توڑو;
      c01 = TDEFL_READ_UNALIGNED_لفظ(&d->m_dict[pos + مطابقت_len - 1]);
    }
  }
}
#ورنہ
ساکن MZ_FORCEINLINE خالی tdefl_ڈھونڈو_مطابقت(tdefl_compressor *d, mz_uint lookahead_pos, mz_uint max_dist, mz_uint max_مطابقت_len, mz_uint *p_مطابقت_dist, mz_uint *p_مطابقت_len)
{
  mz_uint dist, pos = lookahead_pos & TDEFL_LZ_DICT_سائز_نقاب, مطابقت_len = *p_مطابقت_len, probe_pos = pos, اگلا_probe_pos, probe_len;
  mz_uint عدد_probes_بایاں = d->m_max_probes[مطابقت_len >= 32];
  ثابت mz_uint8 *s = d->m_dict + pos, *p, *q;
  mz_uint8 c0 = d->m_dict[pos + مطابقت_len], c1 = d->m_dict[pos + مطابقت_len - 1];
  MZ_ASSERT(max_مطابقت_len <= TDEFL_MAX_مطابقت_LEN); اگر (max_مطابقت_len <= مطابقت_len) واپس;
  برائے ( ; ; )
  {
    برائے ( ; ; )
    {
      اگر (--عدد_probes_بایاں == 0) واپس;
      #تعریف_کرو TDEFL_PROBE \
        اگلا_probe_pos = d->m_اگلا[probe_pos]; \
        اگر ((!اگلا_probe_pos) || ((dist = (mz_uint16)(lookahead_pos - اگلا_probe_pos)) > max_dist)) واپس; \
        probe_pos = اگلا_probe_pos & TDEFL_LZ_DICT_سائز_نقاب; \
        اگر ((d->m_dict[probe_pos + مطابقت_len] == c0) && (d->m_dict[probe_pos + مطابقت_len - 1] == c1)) توڑو;
      TDEFL_PROBE
      TDEFL_PROBE
      TDEFL_PROBE
    }
    اگر (!dist) توڑو;
    p = s; q = d->m_dict + probe_pos;
    برائے (probe_len = 0; probe_len < max_مطابقت_len; probe_len++) {
        اگر (*p++ != *q++) توڑو;
    }
    اگر (probe_len > مطابقت_len)
    {
      *p_مطابقت_dist = dist;
      اگر ((*p_مطابقت_len = مطابقت_len = probe_len) == max_مطابقت_len) واپس;
      c0 = d->m_dict[pos + مطابقت_len]; c1 = d->m_dict[pos + مطابقت_len - 1];
    }
  }
}
#اگر_ختم // #if MINIZ_USE_UNALIGNED_LOADS_AND_STORES

#اگر MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
ساکن mz_bool tdefl_compress_fast(tdefl_compressor *d)
{
  // Faster, minimally featured LZRW1-style match+parse loop with better register utilization. Intended for applications where raw throughput is valued more highly than ratio.
  mz_uint lookahead_pos = d->m_lookahead_pos, lookahead_سائز = d->m_lookahead_سائز, dict_سائز = d->m_dict_سائز, کل_lz_بائٹیں = d->m_کل_lz_بائٹیں, عدد_flags_بایاں = d->m_عدد_flags_بایاں;
  mz_uint8 *p_LZ_رمز_buf = d->m_p_LZ_رمز_buf, *pLZ_flags = d->m_pLZ_flags;
  mz_uint cur_pos = lookahead_pos & TDEFL_LZ_DICT_سائز_نقاب;

  جب ((d->m_src_buf_بایاں) || ((d->m_flush) && (lookahead_سائز)))
  {
    ثابت mz_uint TDEFL_COMP_FAST_LOOKAHEAD_سائز = 4096;
    mz_uint dst_pos = (lookahead_pos + lookahead_سائز) & TDEFL_LZ_DICT_سائز_نقاب;
    mz_uint عدد_بائٹیں_مقصد_process = (mz_uint)MZ_MIN(d->m_src_buf_بایاں, TDEFL_COMP_FAST_LOOKAHEAD_سائز - lookahead_سائز);
    d->m_src_buf_بایاں -= عدد_بائٹیں_مقصد_process;
    lookahead_سائز += عدد_بائٹیں_مقصد_process;

    جب (عدد_بائٹیں_مقصد_process)
    {
      mz_uint32 n = MZ_MIN(TDEFL_LZ_DICT_سائز - dst_pos, عدد_بائٹیں_مقصد_process);
      حافظہ_نقل(d->m_dict + dst_pos, d->m_pSrc, n);
      اگر (dst_pos < (TDEFL_MAX_مطابقت_LEN - 1))
        حافظہ_نقل(d->m_dict + TDEFL_LZ_DICT_سائز + dst_pos, d->m_pSrc, MZ_MIN(n, (TDEFL_MAX_مطابقت_LEN - 1) - dst_pos));
      d->m_pSrc += n;
      dst_pos = (dst_pos + n) & TDEFL_LZ_DICT_سائز_نقاب;
      عدد_بائٹیں_مقصد_process -= n;
    }

    dict_سائز = MZ_MIN(TDEFL_LZ_DICT_سائز - lookahead_سائز, dict_سائز);
    اگر ((!d->m_flush) && (lookahead_سائز < TDEFL_COMP_FAST_LOOKAHEAD_سائز)) توڑو;

    جب (lookahead_سائز >= 4)
    {
      mz_uint cur_مطابقت_dist, cur_مطابقت_len = 1;
      mz_uint8 *pCur_dict = d->m_dict + cur_pos;
      mz_uint پہلا_trigram = (*(ثابت mz_uint32 *)pCur_dict) & 0xFFFFFF;
      mz_uint hash = (پہلا_trigram ^ (پہلا_trigram >> (24 - (TDEFL_LZ_HASH_بٹ - 8)))) & TDEFL_LEVEL1_HASH_سائز_نقاب;
      mz_uint probe_pos = d->m_hash[hash];
      d->m_hash[hash] = (mz_uint16)lookahead_pos;

      اگر (((cur_مطابقت_dist = (mz_uint16)(lookahead_pos - probe_pos)) <= dict_سائز) && ((*(ثابت mz_uint32 *)(d->m_dict + (probe_pos &= TDEFL_LZ_DICT_سائز_نقاب)) & 0xFFFFFF) == پہلا_trigram))
      {
        ثابت mz_uint16 *p = (ثابت mz_uint16 *)pCur_dict;
        ثابت mz_uint16 *q = (ثابت mz_uint16 *)(d->m_dict + probe_pos);
        mz_uint32 probe_len = 32;
        کرو { } جب ( (TDEFL_READ_UNALIGNED_لفظ(++p) == TDEFL_READ_UNALIGNED_لفظ(++q)) && (TDEFL_READ_UNALIGNED_لفظ(++p) == TDEFL_READ_UNALIGNED_لفظ(++q)) &&
          (TDEFL_READ_UNALIGNED_لفظ(++p) == TDEFL_READ_UNALIGNED_لفظ(++q)) && (TDEFL_READ_UNALIGNED_لفظ(++p) == TDEFL_READ_UNALIGNED_لفظ(++q)) && (--probe_len > 0) );
        cur_مطابقت_len = ((mz_uint)(p - (ثابت mz_uint16 *)pCur_dict) * 2) + (mz_uint)(*(ثابت mz_uint8 *)p == *(ثابت mz_uint8 *)q);
        اگر (!probe_len)
          cur_مطابقت_len = cur_مطابقت_dist ? TDEFL_MAX_مطابقت_LEN : 0;

        اگر ((cur_مطابقت_len < TDEFL_MIN_مطابقت_LEN) || ((cur_مطابقت_len == TDEFL_MIN_مطابقت_LEN) && (cur_مطابقت_dist >= 8U*1024U)))
        {
          cur_مطابقت_len = 1;
          *p_LZ_رمز_buf++ = (mz_uint8)پہلا_trigram;
          *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
          d->m_huff_گنتی[0][(mz_uint8)پہلا_trigram]++;
        }
        ورنہ
        {
          mz_uint32 s0, s1;
          cur_مطابقت_len = MZ_MIN(cur_مطابقت_len, lookahead_سائز);

          MZ_ASSERT((cur_مطابقت_len >= TDEFL_MIN_مطابقت_LEN) && (cur_مطابقت_dist >= 1) && (cur_مطابقت_dist <= TDEFL_LZ_DICT_سائز));

          cur_مطابقت_dist--;

          p_LZ_رمز_buf[0] = (mz_uint8)(cur_مطابقت_len - TDEFL_MIN_مطابقت_LEN);
          *(mz_uint16 *)(&p_LZ_رمز_buf[1]) = (mz_uint16)cur_مطابقت_dist;
          p_LZ_رمز_buf += 3;
          *pLZ_flags = (mz_uint8)((*pLZ_flags >> 1) | 0x80);

          s0 = s_tdefl_small_dist_sym[cur_مطابقت_dist & 511];
          s1 = s_tdefl_large_dist_sym[cur_مطابقت_dist >> 8];
          d->m_huff_گنتی[1][(cur_مطابقت_dist < 512) ? s0 : s1]++;

          d->m_huff_گنتی[0][s_tdefl_len_sym[cur_مطابقت_len - TDEFL_MIN_مطابقت_LEN]]++;
        }
      }
      ورنہ
      {
        *p_LZ_رمز_buf++ = (mz_uint8)پہلا_trigram;
        *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
        d->m_huff_گنتی[0][(mz_uint8)پہلا_trigram]++;
      }

      اگر (--عدد_flags_بایاں == 0) { عدد_flags_بایاں = 8; pLZ_flags = p_LZ_رمز_buf++; }

      کل_lz_بائٹیں += cur_مطابقت_len;
      lookahead_pos += cur_مطابقت_len;
      dict_سائز = MZ_MIN(dict_سائز + cur_مطابقت_len, TDEFL_LZ_DICT_سائز);
      cur_pos = (cur_pos + cur_مطابقت_len) & TDEFL_LZ_DICT_سائز_نقاب;
      MZ_ASSERT(lookahead_سائز >= cur_مطابقت_len);
      lookahead_سائز -= cur_مطابقت_len;

      اگر (p_LZ_رمز_buf > &d->m_lz_رمز_buf[TDEFL_LZ_رمز_BUF_سائز - 8])
      {
        صحیح n;
        d->m_lookahead_pos = lookahead_pos; d->m_lookahead_سائز = lookahead_سائز; d->m_dict_سائز = dict_سائز;
        d->m_کل_lz_بائٹیں = کل_lz_بائٹیں; d->m_p_LZ_رمز_buf = p_LZ_رمز_buf; d->m_pLZ_flags = pLZ_flags; d->m_عدد_flags_بایاں = عدد_flags_بایاں;
        اگر ((n = tdefl_flush_بلاک(d, 0)) != 0)
          واپس (n < 0) ? MZ_FALSE : MZ_TRUE;
        کل_lz_بائٹیں = d->m_کل_lz_بائٹیں; p_LZ_رمز_buf = d->m_p_LZ_رمز_buf; pLZ_flags = d->m_pLZ_flags; عدد_flags_بایاں = d->m_عدد_flags_بایاں;
      }
    }

    جب (lookahead_سائز)
    {
      mz_uint8 lit = d->m_dict[cur_pos];

      کل_lz_بائٹیں++;
      *p_LZ_رمز_buf++ = lit;
      *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
      اگر (--عدد_flags_بایاں == 0) { عدد_flags_بایاں = 8; pLZ_flags = p_LZ_رمز_buf++; }

      d->m_huff_گنتی[0][lit]++;

      lookahead_pos++;
      dict_سائز = MZ_MIN(dict_سائز + 1, TDEFL_LZ_DICT_سائز);
      cur_pos = (cur_pos + 1) & TDEFL_LZ_DICT_سائز_نقاب;
      lookahead_سائز--;

      اگر (p_LZ_رمز_buf > &d->m_lz_رمز_buf[TDEFL_LZ_رمز_BUF_سائز - 8])
      {
        صحیح n;
        d->m_lookahead_pos = lookahead_pos; d->m_lookahead_سائز = lookahead_سائز; d->m_dict_سائز = dict_سائز;
        d->m_کل_lz_بائٹیں = کل_lz_بائٹیں; d->m_p_LZ_رمز_buf = p_LZ_رمز_buf; d->m_pLZ_flags = pLZ_flags; d->m_عدد_flags_بایاں = عدد_flags_بایاں;
        اگر ((n = tdefl_flush_بلاک(d, 0)) != 0)
          واپس (n < 0) ? MZ_FALSE : MZ_TRUE;
        کل_lz_بائٹیں = d->m_کل_lz_بائٹیں; p_LZ_رمز_buf = d->m_p_LZ_رمز_buf; pLZ_flags = d->m_pLZ_flags; عدد_flags_بایاں = d->m_عدد_flags_بایاں;
      }
    }
  }

  d->m_lookahead_pos = lookahead_pos; d->m_lookahead_سائز = lookahead_سائز; d->m_dict_سائز = dict_سائز;
  d->m_کل_lz_بائٹیں = کل_lz_بائٹیں; d->m_p_LZ_رمز_buf = p_LZ_رمز_buf; d->m_pLZ_flags = pLZ_flags; d->m_عدد_flags_بایاں = عدد_flags_بایاں;
  واپس MZ_TRUE;
}
#اگر_ختم // MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN

ساکن MZ_FORCEINLINE خالی tdefl_ریکارڈ_literal(tdefl_compressor *d, mz_uint8 lit)
{
  d->m_کل_lz_بائٹیں++;
  *d->m_p_LZ_رمز_buf++ = lit;
  *d->m_pLZ_flags = (mz_uint8)(*d->m_pLZ_flags >> 1); اگر (--d->m_عدد_flags_بایاں == 0) { d->m_عدد_flags_بایاں = 8; d->m_pLZ_flags = d->m_p_LZ_رمز_buf++; }
  d->m_huff_گنتی[0][lit]++;
}

ساکن MZ_FORCEINLINE خالی tdefl_ریکارڈ_مطابقت(tdefl_compressor *d, mz_uint مطابقت_len, mz_uint مطابقت_dist)
{
  mz_uint32 s0, s1;

  MZ_ASSERT((مطابقت_len >= TDEFL_MIN_مطابقت_LEN) && (مطابقت_dist >= 1) && (مطابقت_dist <= TDEFL_LZ_DICT_سائز));

  d->m_کل_lz_بائٹیں += مطابقت_len;

  d->m_p_LZ_رمز_buf[0] = (mz_uint8)(مطابقت_len - TDEFL_MIN_مطابقت_LEN);

  مطابقت_dist -= 1;
  d->m_p_LZ_رمز_buf[1] = (mz_uint8)(مطابقت_dist & 0xFF);
  d->m_p_LZ_رمز_buf[2] = (mz_uint8)(مطابقت_dist >> 8); d->m_p_LZ_رمز_buf += 3;

  *d->m_pLZ_flags = (mz_uint8)((*d->m_pLZ_flags >> 1) | 0x80); اگر (--d->m_عدد_flags_بایاں == 0) { d->m_عدد_flags_بایاں = 8; d->m_pLZ_flags = d->m_p_LZ_رمز_buf++; }

  s0 = s_tdefl_small_dist_sym[مطابقت_dist & 511]; s1 = s_tdefl_large_dist_sym[(مطابقت_dist >> 8) & 127];
  d->m_huff_گنتی[1][(مطابقت_dist < 512) ? s0 : s1]++;

  اگر (مطابقت_len >= TDEFL_MIN_مطابقت_LEN) d->m_huff_گنتی[0][s_tdefl_len_sym[مطابقت_len - TDEFL_MIN_مطابقت_LEN]]++;
}

ساکن mz_bool tdefl_compress_معمول(tdefl_compressor *d)
{
  ثابت mz_uint8 *pSrc = d->m_pSrc; size_t src_buf_بایاں = d->m_src_buf_بایاں;
  tdefl_flush flush = d->m_flush;

  جب ((src_buf_بایاں) || ((flush) && (d->m_lookahead_سائز)))
  {
    mz_uint len_مقصد_move, cur_مطابقت_dist, cur_مطابقت_len, cur_pos;
    // Update dictionary and hash chains. Keeps the lookahead size equal to TDEFL_MAX_MATCH_LEN.
    اگر ((d->m_lookahead_سائز + d->m_dict_سائز) >= (TDEFL_MIN_مطابقت_LEN - 1))
    {
      mz_uint dst_pos = (d->m_lookahead_pos + d->m_lookahead_سائز) & TDEFL_LZ_DICT_سائز_نقاب, ins_pos = d->m_lookahead_pos + d->m_lookahead_سائز - 2;
      mz_uint hash = (d->m_dict[ins_pos & TDEFL_LZ_DICT_سائز_نقاب] << TDEFL_LZ_HASH_سرکاؤ) ^ d->m_dict[(ins_pos + 1) & TDEFL_LZ_DICT_سائز_نقاب];
      mz_uint عدد_بائٹیں_مقصد_process = (mz_uint)MZ_MIN(src_buf_بایاں, TDEFL_MAX_مطابقت_LEN - d->m_lookahead_سائز);
      ثابت mz_uint8 *p_Src_انتہا = pSrc ? pSrc + عدد_بائٹیں_مقصد_process : تہی;
      src_buf_بایاں -= عدد_بائٹیں_مقصد_process;
      d->m_lookahead_سائز += عدد_بائٹیں_مقصد_process;
      جب (pSrc != p_Src_انتہا)
      {
        mz_uint8 c = *pSrc++; d->m_dict[dst_pos] = c; اگر (dst_pos < (TDEFL_MAX_مطابقت_LEN - 1)) d->m_dict[TDEFL_LZ_DICT_سائز + dst_pos] = c;
        hash = ((hash << TDEFL_LZ_HASH_سرکاؤ) ^ c) & (TDEFL_LZ_HASH_سائز - 1);
        d->m_اگلا[ins_pos & TDEFL_LZ_DICT_سائز_نقاب] = d->m_hash[hash]; d->m_hash[hash] = (mz_uint16)(ins_pos);
        dst_pos = (dst_pos + 1) & TDEFL_LZ_DICT_سائز_نقاب; ins_pos++;
      }
    }
    ورنہ
    {
      جب ((src_buf_بایاں) && (d->m_lookahead_سائز < TDEFL_MAX_مطابقت_LEN))
      {
        mz_uint8 c = *pSrc++;
        mz_uint dst_pos = (d->m_lookahead_pos + d->m_lookahead_سائز) & TDEFL_LZ_DICT_سائز_نقاب;
        src_buf_بایاں--;
        d->m_dict[dst_pos] = c;
        اگر (dst_pos < (TDEFL_MAX_مطابقت_LEN - 1))
          d->m_dict[TDEFL_LZ_DICT_سائز + dst_pos] = c;
        اگر ((++d->m_lookahead_سائز + d->m_dict_سائز) >= TDEFL_MIN_مطابقت_LEN)
        {
          mz_uint ins_pos = d->m_lookahead_pos + (d->m_lookahead_سائز - 1) - 2;
          mz_uint hash = ((d->m_dict[ins_pos & TDEFL_LZ_DICT_سائز_نقاب] << (TDEFL_LZ_HASH_سرکاؤ * 2)) ^ (d->m_dict[(ins_pos + 1) & TDEFL_LZ_DICT_سائز_نقاب] << TDEFL_LZ_HASH_سرکاؤ) ^ c) & (TDEFL_LZ_HASH_سائز - 1);
          d->m_اگلا[ins_pos & TDEFL_LZ_DICT_سائز_نقاب] = d->m_hash[hash]; d->m_hash[hash] = (mz_uint16)(ins_pos);
        }
      }
    }
    d->m_dict_سائز = MZ_MIN(TDEFL_LZ_DICT_سائز - d->m_lookahead_سائز, d->m_dict_سائز);
    اگر ((!flush) && (d->m_lookahead_سائز < TDEFL_MAX_مطابقت_LEN))
      توڑو;

    // Simple lazy/greedy parsing state machine.
    len_مقصد_move = 1; cur_مطابقت_dist = 0; cur_مطابقت_len = d->m_saved_مطابقت_len ? d->m_saved_مطابقت_len : (TDEFL_MIN_مطابقت_LEN - 1); cur_pos = d->m_lookahead_pos & TDEFL_LZ_DICT_سائز_نقاب;
    اگر (d->m_flags & (TDEFL_RLE_MATCHES | TDEFL_FORCE_ALL_RAW_بلاکیں))
    {
      اگر ((d->m_dict_سائز) && (!(d->m_flags & TDEFL_FORCE_ALL_RAW_بلاکیں)))
      {
        mz_uint8 c = d->m_dict[(cur_pos - 1) & TDEFL_LZ_DICT_سائز_نقاب];
        cur_مطابقت_len = 0; جب (cur_مطابقت_len < d->m_lookahead_سائز) { اگر (d->m_dict[cur_pos + cur_مطابقت_len] != c) توڑو; cur_مطابقت_len++; }
        اگر (cur_مطابقت_len < TDEFL_MIN_مطابقت_LEN) cur_مطابقت_len = 0; ورنہ cur_مطابقت_dist = 1;
      }
    }
    ورنہ
    {
      tdefl_ڈھونڈو_مطابقت(d, d->m_lookahead_pos, d->m_dict_سائز, d->m_lookahead_سائز, &cur_مطابقت_dist, &cur_مطابقت_len);
    }
    اگر (((cur_مطابقت_len == TDEFL_MIN_مطابقت_LEN) && (cur_مطابقت_dist >= 8U*1024U)) || (cur_pos == cur_مطابقت_dist) || ((d->m_flags & TDEFL_FILTER_MATCHES) && (cur_مطابقت_len <= 5)))
    {
      cur_مطابقت_dist = cur_مطابقت_len = 0;
    }
    اگر (d->m_saved_مطابقت_len)
    {
      اگر (cur_مطابقت_len > d->m_saved_مطابقت_len)
      {
        tdefl_ریکارڈ_literal(d, (mz_uint8)d->m_saved_lit);
        اگر (cur_مطابقت_len >= 128)
        {
          tdefl_ریکارڈ_مطابقت(d, cur_مطابقت_len, cur_مطابقت_dist);
          d->m_saved_مطابقت_len = 0; len_مقصد_move = cur_مطابقت_len;
        }
        ورنہ
        {
          d->m_saved_lit = d->m_dict[cur_pos]; d->m_saved_مطابقت_dist = cur_مطابقت_dist; d->m_saved_مطابقت_len = cur_مطابقت_len;
        }
      }
      ورنہ
      {
        tdefl_ریکارڈ_مطابقت(d, d->m_saved_مطابقت_len, d->m_saved_مطابقت_dist);
        len_مقصد_move = d->m_saved_مطابقت_len - 1; d->m_saved_مطابقت_len = 0;
      }
    }
    ورنہ اگر (!cur_مطابقت_dist)
      tdefl_ریکارڈ_literal(d, d->m_dict[MZ_MIN(cur_pos, حجم(d->m_dict) - 1)]);
    ورنہ اگر ((d->m_greedy_parsing) || (d->m_flags & TDEFL_RLE_MATCHES) || (cur_مطابقت_len >= 128))
    {
      tdefl_ریکارڈ_مطابقت(d, cur_مطابقت_len, cur_مطابقت_dist);
      len_مقصد_move = cur_مطابقت_len;
    }
    ورنہ
    {
      d->m_saved_lit = d->m_dict[MZ_MIN(cur_pos, حجم(d->m_dict) - 1)]; d->m_saved_مطابقت_dist = cur_مطابقت_dist; d->m_saved_مطابقت_len = cur_مطابقت_len;
    }
    // Move the lookahead forward by len_to_move bytes.
    d->m_lookahead_pos += len_مقصد_move;
    MZ_ASSERT(d->m_lookahead_سائز >= len_مقصد_move);
    d->m_lookahead_سائز -= len_مقصد_move;
    d->m_dict_سائز = MZ_MIN(d->m_dict_سائز + len_مقصد_move, TDEFL_LZ_DICT_سائز);
    // Check if it's time to flush the current LZ codes to the internal output buffer.
    اگر ( (d->m_p_LZ_رمز_buf > &d->m_lz_رمز_buf[TDEFL_LZ_رمز_BUF_سائز - 8]) ||
         ( (d->m_کل_lz_بائٹیں > 31*1024) && (((((mz_uint)(d->m_p_LZ_رمز_buf - d->m_lz_رمز_buf) * 115) >> 7) >= d->m_کل_lz_بائٹیں) || (d->m_flags & TDEFL_FORCE_ALL_RAW_بلاکیں))) )
    {
      صحیح n;
      d->m_pSrc = pSrc; d->m_src_buf_بایاں = src_buf_بایاں;
      اگر ((n = tdefl_flush_بلاک(d, 0)) != 0)
        واپس (n < 0) ? MZ_FALSE : MZ_TRUE;
    }
  }

  d->m_pSrc = pSrc; d->m_src_buf_بایاں = src_buf_بایاں;
  واپس MZ_TRUE;
}

ساکن tdefl_حالت tdefl_flush_output_بفر(tdefl_compressor *d)
{
  اگر (d->m_p_اندر_buf_سائز)
  {
    *d->m_p_اندر_buf_سائز = d->m_pSrc - (ثابت mz_uint8 *)d->m_p_اندر_buf;
  }

  اگر (d->m_p_برآمد_buf_سائز)
  {
    size_t n = MZ_MIN(*d->m_p_برآمد_buf_سائز - d->m_برآمد_buf_ofs, d->m_output_flush_بقایا);
    حافظہ_نقل((mz_uint8 *)d->m_p_برآمد_buf + d->m_برآمد_buf_ofs, d->m_output_buf + d->m_output_flush_ofs, n);
    d->m_output_flush_ofs += (mz_uint)n;
    d->m_output_flush_بقایا -= (mz_uint)n;
    d->m_برآمد_buf_ofs += n;

    *d->m_p_برآمد_buf_سائز = d->m_برآمد_buf_ofs;
  }

  واپس (d->m_ختم_شدہ && !d->m_output_flush_بقایا) ? TDEFL_حالت_مکمل : TDEFL_حالت_OKAY;
}

tdefl_حالت tdefl_compress(tdefl_compressor *d, ثابت خالی *p_اندر_buf, size_t *p_اندر_buf_سائز, خالی *p_برآمد_buf, size_t *p_برآمد_buf_سائز, tdefl_flush flush)
{
  اگر (!d)
  {
    اگر (p_اندر_buf_سائز) *p_اندر_buf_سائز = 0;
    اگر (p_برآمد_buf_سائز) *p_برآمد_buf_سائز = 0;
    واپس TDEFL_حالت_BAD_PARAM;
  }

  d->m_p_اندر_buf = p_اندر_buf; d->m_p_اندر_buf_سائز = p_اندر_buf_سائز;
  d->m_p_برآمد_buf = p_برآمد_buf; d->m_p_برآمد_buf_سائز = p_برآمد_buf_سائز;
  d->m_pSrc = (ثابت mz_uint8 *)(p_اندر_buf); d->m_src_buf_بایاں = p_اندر_buf_سائز ? *p_اندر_buf_سائز : 0;
  d->m_برآمد_buf_ofs = 0;
  d->m_flush = flush;

  اگر ( ((d->m_pPut_buf_func != تہی) == ((p_برآمد_buf != تہی) || (p_برآمد_buf_سائز != تہی))) || (d->m_پچھلا_return_حالت != TDEFL_حالت_OKAY) ||
        (d->m_چاہتا_مقصد_اختتام && (flush != TDEFL_اختتام)) || (p_اندر_buf_سائز && *p_اندر_buf_سائز && !p_اندر_buf) || (p_برآمد_buf_سائز && *p_برآمد_buf_سائز && !p_برآمد_buf) )
  {
    اگر (p_اندر_buf_سائز) *p_اندر_buf_سائز = 0;
    اگر (p_برآمد_buf_سائز) *p_برآمد_buf_سائز = 0;
    واپس (d->m_پچھلا_return_حالت = TDEFL_حالت_BAD_PARAM);
  }
  d->m_چاہتا_مقصد_اختتام |= (flush == TDEFL_اختتام);

  اگر ((d->m_output_flush_بقایا) || (d->m_ختم_شدہ))
    واپس (d->m_پچھلا_return_حالت = tdefl_flush_output_بفر(d));

#اگر MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  اگر (((d->m_flags & TDEFL_MAX_PROBES_نقاب) == 1) &&
      ((d->m_flags & TDEFL_GREEDY_PARSING_FLAG) != 0) &&
      ((d->m_flags & (TDEFL_FILTER_MATCHES | TDEFL_FORCE_ALL_RAW_بلاکیں | TDEFL_RLE_MATCHES)) == 0))
  {
    اگر (!tdefl_compress_fast(d))
      واپس d->m_پچھلا_return_حالت;
  }
  ورنہ
#اگر_ختم // #if MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  {
    اگر (!tdefl_compress_معمول(d))
      واپس d->m_پچھلا_return_حالت;
  }

  اگر ((d->m_flags & (TDEFL_WRITE_ZLIB_سرخی | TDEFL_COMPUTE_ADLER32)) && (p_اندر_buf))
    d->m_adler32 = (mz_uint32)mz_adler32(d->m_adler32, (ثابت mz_uint8 *)p_اندر_buf, d->m_pSrc - (ثابت mz_uint8 *)p_اندر_buf);

  اگر ((flush) && (!d->m_lookahead_سائز) && (!d->m_src_buf_بایاں) && (!d->m_output_flush_بقایا))
  {
    اگر (tdefl_flush_بلاک(d, flush) < 0)
      واپس d->m_پچھلا_return_حالت;
    d->m_ختم_شدہ = (flush == TDEFL_اختتام);
    اگر (flush == TDEFL_بھرا_FLUSH) { MZ_CLEAR_ARR(d->m_hash); MZ_CLEAR_ARR(d->m_اگلا); d->m_dict_سائز = 0; }
  }

  واپس (d->m_پچھلا_return_حالت = tdefl_flush_output_بفر(d));
}

tdefl_حالت tdefl_compress_بفر(tdefl_compressor *d, ثابت خالی *p_اندر_buf, size_t اندر_buf_سائز, tdefl_flush flush)
{
  MZ_ASSERT(d->m_pPut_buf_func); واپس tdefl_compress(d, p_اندر_buf, &اندر_buf_سائز, تہی, تہی, flush);
}

tdefl_حالت tdefl_init(tdefl_compressor *d, tdefl_put_buf_func_ptr pPut_buf_func, خالی *pPut_buf_user, صحیح flags)
{
  d->m_pPut_buf_func = pPut_buf_func; d->m_pPut_buf_user = pPut_buf_user;
  d->m_flags = (mz_uint)(flags); d->m_max_probes[0] = 1 + ((flags & 0xFFF) + 2) / 3; d->m_greedy_parsing = (flags & TDEFL_GREEDY_PARSING_FLAG) != 0;
  d->m_max_probes[1] = 1 + (((flags & 0xFFF) >> 2) + 2) / 3;
  اگر (!(flags & TDEFL_NONDETERMINISTIC_PARSING_FLAG)) MZ_CLEAR_ARR(d->m_hash);
  d->m_lookahead_pos = d->m_lookahead_سائز = d->m_dict_سائز = d->m_کل_lz_بائٹیں = d->m_lz_رمز_buf_dict_pos = d->m_بٹ_اندر = 0;
  d->m_output_flush_ofs = d->m_output_flush_بقایا = d->m_ختم_شدہ = d->m_بلاک_اشاریہ = d->m_ثنائی_ہندسہ_بفر = d->m_چاہتا_مقصد_اختتام = 0;
  d->m_p_LZ_رمز_buf = d->m_lz_رمز_buf + 1; d->m_pLZ_flags = d->m_lz_رمز_buf; d->m_عدد_flags_بایاں = 8;
  d->m_pOutput_buf = d->m_output_buf; d->m_p_Output_buf_انتہا = d->m_output_buf; d->m_پچھلا_return_حالت = TDEFL_حالت_OKAY;
  d->m_saved_مطابقت_dist = d->m_saved_مطابقت_len = d->m_saved_lit = 0; d->m_adler32 = 1;
  d->m_p_اندر_buf = تہی; d->m_p_برآمد_buf = تہی;
  d->m_p_اندر_buf_سائز = تہی; d->m_p_برآمد_buf_سائز = تہی;
  d->m_flush = TDEFL_NO_FLUSH; d->m_pSrc = تہی; d->m_src_buf_بایاں = 0; d->m_برآمد_buf_ofs = 0;
  memset(&d->m_huff_گنتی[0][0], 0, حجم(d->m_huff_گنتی[0][0]) * TDEFL_MAX_HUFF_SYMBOLS_0);
  memset(&d->m_huff_گنتی[1][0], 0, حجم(d->m_huff_گنتی[1][0]) * TDEFL_MAX_HUFF_SYMBOLS_1);
  واپس TDEFL_حالت_OKAY;
}

#اگر_غیر_تعریف_شدہ MINIZ_SDL_NOUNUSED
tdefl_حالت tdefl_get_پچھلا_return_حالت(tdefl_compressor *d)
{
  واپس d->m_پچھلا_return_حالت;
}

mz_uint32 tdefl_get_adler32(tdefl_compressor *d)
{
  واپس d->m_adler32;
}

mz_bool tdefl_compress_mem_مقصد_output(ثابت خالی *pBuf, size_t buf_len, tdefl_put_buf_func_ptr pPut_buf_func, خالی *pPut_buf_user, صحیح flags)
{
  tdefl_compressor *pComp; mz_bool succeeded; اگر (((buf_len) && (!pBuf)) || (!pPut_buf_func)) واپس MZ_FALSE;
  pComp = (tdefl_compressor*)MZ_MALLOC(حجم(tdefl_compressor)); اگر (!pComp) واپس MZ_FALSE;
  succeeded = (tdefl_init(pComp, pPut_buf_func, pPut_buf_user, flags) == TDEFL_حالت_OKAY);
  succeeded = succeeded && (tdefl_compress_بفر(pComp, pBuf, buf_len, TDEFL_اختتام) == TDEFL_حالت_مکمل);
  MZ_FREE(pComp); واپس succeeded;
}
#اگر_ختم /* MINIZ_SDL_NOUNUSED */

قسمتعریف ساخت
{
  size_t m_سائز, m_استعداد;
  mz_uint8 *m_pBuf;
  mz_bool m_expandable;
} tdefl_output_بفر;

ساکن mz_bool tdefl_output_بفر_putter(ثابت خالی *pBuf, صحیح len, خالی *pUser)
{
  tdefl_output_بفر *p = (tdefl_output_بفر *)pUser;
  size_t new_سائز = p->m_سائز + len;
  اگر (new_سائز > p->m_استعداد)
  {
    size_t new_استعداد = p->m_استعداد; mz_uint8 *pNew_buf; اگر (!p->m_expandable) واپس MZ_FALSE;
    کرو { new_استعداد = MZ_MAX(128U, new_استعداد << 1U); } جب (new_سائز > new_استعداد);
    pNew_buf = (mz_uint8*)MZ_REALLOC(p->m_pBuf, new_استعداد); اگر (!pNew_buf) واپس MZ_FALSE;
    p->m_pBuf = pNew_buf; p->m_استعداد = new_استعداد;
  }
  حافظہ_نقل((mz_uint8*)p->m_pBuf + p->m_سائز, pBuf, len); p->m_سائز = new_سائز;
  واپس MZ_TRUE;
}

#اگر_غیر_تعریف_شدہ MINIZ_SDL_NOUNUSED
خالی *tdefl_compress_mem_مقصد_ڈھیر(ثابت خالی *pSrc_buf, size_t src_buf_len, size_t *p_برآمد_len, صحیح flags)
{
  tdefl_output_بفر برآمد_buf; MZ_CLEAR_OBJ(برآمد_buf);
  اگر (!p_برآمد_len) واپس MZ_FALSE; ورنہ *p_برآمد_len = 0;
  برآمد_buf.m_expandable = MZ_TRUE;
  اگر (!tdefl_compress_mem_مقصد_output(pSrc_buf, src_buf_len, tdefl_output_بفر_putter, &برآمد_buf, flags)) واپس تہی;
  *p_برآمد_len = برآمد_buf.m_سائز; واپس برآمد_buf.m_pBuf;
}

size_t tdefl_compress_mem_مقصد_mem(خالی *p_برآمد_buf, size_t برآمد_buf_len, ثابت خالی *pSrc_buf, size_t src_buf_len, صحیح flags)
{
  tdefl_output_بفر برآمد_buf; MZ_CLEAR_OBJ(برآمد_buf);
  اگر (!p_برآمد_buf) واپس 0;
  برآمد_buf.m_pBuf = (mz_uint8*)p_برآمد_buf; برآمد_buf.m_استعداد = برآمد_buf_len;
  اگر (!tdefl_compress_mem_مقصد_output(pSrc_buf, src_buf_len, tdefl_output_بفر_putter, &برآمد_buf, flags)) واپس 0;
  واپس برآمد_buf.m_سائز;
}
#اگر_ختم /* MINIZ_SDL_NOUNUSED */

#اگر_غیر_تعریف_شدہ MINIZ_NO_ZLIB_APIS
ساکن ثابت mz_uint s_tdefl_عدد_probes[11] = { 0, 1, 6, 32,  16, 32, 128, 256,  512, 768, 1500 };

// level may actually range from [0,10] (10 is a "hidden" max level, where we want a bit more compression and it's fine if throughput to fall off a cliff on some files).
mz_uint tdefl_create_comp_flags_from_zip_params(صحیح level, صحیح کھڑکی_بٹ, صحیح strategy)
{
  mz_uint comp_flags = s_tdefl_عدد_probes[(level >= 0) ? MZ_MIN(10, level) : MZ_DEFAULT_LEVEL] | ((level <= 3) ? TDEFL_GREEDY_PARSING_FLAG : 0);
  اگر (کھڑکی_بٹ > 0) comp_flags |= TDEFL_WRITE_ZLIB_سرخی;

  اگر (!level) comp_flags |= TDEFL_FORCE_ALL_RAW_بلاکیں;
  ورنہ اگر (strategy == MZ_FILTERED) comp_flags |= TDEFL_FILTER_MATCHES;
  ورنہ اگر (strategy == MZ_HUFFMAN_ONLY) comp_flags &= ~TDEFL_MAX_PROBES_نقاب;
  ورنہ اگر (strategy == MZ_FIXED) comp_flags |= TDEFL_FORCE_ALL_STATIC_بلاکیں;
  ورنہ اگر (strategy == MZ_RLE) comp_flags |= TDEFL_RLE_MATCHES;

  واپس comp_flags;
}
#اگر_ختم //MINIZ_NO_ZLIB_APIS

#اگر_تعریف_شدہ _MSC_VER
#ہدایت warning (ڈالو)
#ہدایت warning (disable:4204) // nonstandard extension used : non-constant aggregate initializer (also supported by GNU C and C99, so no big deal)
#اگر_ختم

// Simple PNG writer function by Alex Evans, 2011. Released into the public domain: https://gist.github.com/908299, more context at
// http://altdevblogaday.org/2011/04/06/a-smaller-jpg-encoder/.
// This is actually a modification of Alex's original code so PNG files generated by this function pass pngcheck.
MINIZ_STATIC خالی *tdefl_write_image_مقصد_png_file_اندر_حافظہ_ex(ثابت خالی *pImage, صحیح w, صحیح h, صحیح عدد_chans, صحیح bpl, size_t *p_Len_برآمد, mz_uint level, mz_bool flip, mz_uint8 *plte, صحیح plte_سائز, mz_uint8 *trns, صحیح trns_سائز)
{
  // Using a local copy of this array here in case MINIZ_NO_ZLIB_APIS was defined.
  ساکن ثابت mz_uint s_tdefl_png_عدد_probes[11] = { 0, 1, 6, 32,  16, 32, 128, 256,  512, 768, 1500 };
  tdefl_compressor *pComp = (tdefl_compressor *)MZ_MALLOC(حجم(tdefl_compressor)); tdefl_output_بفر برآمد_buf; صحیح i, y, z = 0; mz_uint32 c; *p_Len_برآمد = 0; size_t ڈیٹا_آغاز, ڈیٹا_سائز_3;
  اگر (!pComp) واپس تہی;
  MZ_CLEAR_OBJ(برآمد_buf); برآمد_buf.m_expandable = MZ_TRUE;
  برآمد_buf.m_استعداد = 57+MZ_MAX(64, (1+w*عدد_chans)*h);
  اگر (plte_سائز > 0)
    برآمد_buf.m_استعداد += 12+plte_سائز;
  اگر (trns_سائز > 0)
    برآمد_buf.m_استعداد += 12+trns_سائز;
  اگر (تہی == (برآمد_buf.m_pBuf = (mz_uint8*)MZ_MALLOC(برآمد_buf.m_استعداد))) { MZ_FREE(pComp); واپس تہی; }
  // write header
  {
    ساکن ثابت mz_uint8 chans[] = {0x00, 0x00, 0x04, 0x02, 0x06};

    mz_uint8 pnghdr[33]={ 0x89,0x50,0x4e,0x47,0x0d,0x0a,0x1a,0x0a,
                          0x00,0x00,0x00,0x0d,0x49,0x48,0x44,0x52,
                          0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                          0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

    pnghdr[18] = (mz_uint8)(w>>8);
    pnghdr[19] = (mz_uint8)(w>>0);

    pnghdr[22] = (mz_uint8)(h>>8);
    pnghdr[23] = (mz_uint8)(h>>0);

    اگر (عدد_chans == 1 && plte_سائز > 0)
      pnghdr[25] = 3;
    ورنہ
      pnghdr[25] = (chans[عدد_chans]);

    c = (mz_uint32)mz_چکری_جانچ_32(MZ_چکری_جانچ_32_INIT,pnghdr+12,17);
    برائے (i=0; i<4; ++i, c<<=8) ((mz_uint8*)(pnghdr+29))[i] = (mz_uint8)(c>>24);
    اگر (!tdefl_output_بفر_putter(pnghdr, حجم(pnghdr), &برآمد_buf)) { *p_Len_برآمد = 0; MZ_FREE(pComp); MZ_FREE(برآمد_buf.m_pBuf); واپس تہی; }
  }
  // write PLTE chunk
  اگر (plte_سائز > 0)
  {
    mz_uint8 hdr[8]={0x00,0x00,0x00,0x00,0x50,0x4c,0x54,0x45};

    hdr[0] = (mz_uint8)(plte_سائز>>24);
    hdr[1] = (mz_uint8)(plte_سائز>>16);
    hdr[2] = (mz_uint8)(plte_سائز>> 8);
    hdr[3] = (mz_uint8)(plte_سائز>> 0);
    اگر (!tdefl_output_بفر_putter(hdr, حجم(hdr), &برآمد_buf)) { *p_Len_برآمد = 0; MZ_FREE(pComp); MZ_FREE(برآمد_buf.m_pBuf); واپس تہی; }
    ڈیٹا_آغاز = برآمد_buf.m_سائز;
    اگر (!tdefl_output_بفر_putter(plte, plte_سائز, &برآمد_buf)) { *p_Len_برآمد = 0; MZ_FREE(pComp); MZ_FREE(برآمد_buf.m_pBuf); واپس تہی; }
    اگر (!tdefl_output_بفر_putter("\0\0\0\0", 4, &برآمد_buf)) { *p_Len_برآمد = 0; MZ_FREE(pComp); MZ_FREE(برآمد_buf.m_pBuf); واپس تہی; }
    c = (mz_uint32)mz_چکری_جانچ_32(MZ_چکری_جانچ_32_INIT,برآمد_buf.m_pBuf+ڈیٹا_آغاز-4, plte_سائز+4);
    برائے (i=0; i<4; ++i, c<<=8) (برآمد_buf.m_pBuf+برآمد_buf.m_سائز-4)[i] = (mz_uint8)(c >> 24);
  }
  // write tRNS chunk
  اگر (trns_سائز > 0)
  {
    mz_uint8 hdr[8]={0x00,0x00,0x00,0x00,0x74,0x52,0x4E,0x53};

    hdr[0] = (mz_uint8)(trns_سائز>>24);
    hdr[1] = (mz_uint8)(trns_سائز>>16);
    hdr[2] = (mz_uint8)(trns_سائز>> 8);
    hdr[3] = (mz_uint8)(trns_سائز>> 0);
    اگر (!tdefl_output_بفر_putter(hdr, حجم(hdr), &برآمد_buf)) { *p_Len_برآمد = 0; MZ_FREE(pComp); MZ_FREE(برآمد_buf.m_pBuf); واپس تہی; }
    ڈیٹا_آغاز = برآمد_buf.m_سائز;
    اگر (!tdefl_output_بفر_putter(trns, trns_سائز, &برآمد_buf)) { *p_Len_برآمد = 0; MZ_FREE(pComp); MZ_FREE(برآمد_buf.m_pBuf); واپس تہی; }
    اگر (!tdefl_output_بفر_putter("\0\0\0\0", 4, &برآمد_buf)) { *p_Len_برآمد = 0; MZ_FREE(pComp); MZ_FREE(برآمد_buf.m_pBuf); واپس تہی; }
    c = (mz_uint32)mz_چکری_جانچ_32(MZ_چکری_جانچ_32_INIT,برآمد_buf.m_pBuf+ڈیٹا_آغاز-4, trns_سائز+4);
    برائے (i=0; i<4; ++i, c<<=8) (برآمد_buf.m_pBuf+برآمد_buf.m_سائز-4)[i] = (mz_uint8)(c >> 24);
  }
  // write IDAT chunk
  اگر (!tdefl_output_بفر_putter("\0\0\0\0\x49\x44\x41\x54", 8, &برآمد_buf)) { *p_Len_برآمد = 0; MZ_FREE(pComp); MZ_FREE(برآمد_buf.m_pBuf); واپس تہی; }
  ڈیٹا_آغاز = برآمد_buf.m_سائز;
  // compress image data
  tdefl_init(pComp, tdefl_output_بفر_putter, &برآمد_buf, s_tdefl_png_عدد_probes[MZ_MIN(10, level)] | TDEFL_WRITE_ZLIB_سرخی);
  برائے (y = 0; y < h; ++y) { tdefl_compress_بفر(pComp, &z, 1, TDEFL_NO_FLUSH); tdefl_compress_بفر(pComp, (mz_uint8*)pImage + (flip ? (h - 1 - y) : y) * bpl, w * عدد_chans, TDEFL_NO_FLUSH); }
  اگر (tdefl_compress_بفر(pComp, تہی, 0, TDEFL_اختتام) != TDEFL_حالت_مکمل) { MZ_FREE(pComp); MZ_FREE(برآمد_buf.m_pBuf); واپس تہی; }
  // write IDAT size
  ڈیٹا_سائز_3 = برآمد_buf.m_سائز-ڈیٹا_آغاز;
  (برآمد_buf.m_pBuf+ڈیٹا_آغاز-8)[0] = (mz_uint8)(ڈیٹا_سائز_3>>24);
  (برآمد_buf.m_pBuf+ڈیٹا_آغاز-8)[1] = (mz_uint8)(ڈیٹا_سائز_3>>16);
  (برآمد_buf.m_pBuf+ڈیٹا_آغاز-8)[2] = (mz_uint8)(ڈیٹا_سائز_3>> 8);
  (برآمد_buf.m_pBuf+ڈیٹا_آغاز-8)[3] = (mz_uint8)(ڈیٹا_سائز_3>> 0);
  // write footer (IDAT CRC-32, followed by IEND chunk)
  اگر (!tdefl_output_بفر_putter("\0\0\0\0\0\0\0\0\x49\x45\x4e\x44\xae\x42\x60\x82", 16, &برآمد_buf)) { *p_Len_برآمد = 0; MZ_FREE(pComp); MZ_FREE(برآمد_buf.m_pBuf); واپس تہی; }
  c = (mz_uint32)mz_چکری_جانچ_32(MZ_چکری_جانچ_32_INIT,برآمد_buf.m_pBuf+ڈیٹا_آغاز-4, ڈیٹا_سائز_3+4);
  برائے (i=0; i<4; ++i, c<<=8) (برآمد_buf.m_pBuf+برآمد_buf.m_سائز-16)[i] = (mz_uint8)(c >> 24);
  // compute final size of file, grab compressed data buffer and return
  *p_Len_برآمد = برآمد_buf.m_سائز;
  MZ_FREE(pComp);
  واپس برآمد_buf.m_pBuf;
}
#اگر_غیر_تعریف_شدہ MINIZ_SDL_NOUNUSED
MINIZ_STATIC خالی *tdefl_write_image_مقصد_png_file_اندر_حافظہ(ثابت خالی *pImage, صحیح w, صحیح h, صحیح عدد_chans, صحیح bpl, size_t *p_Len_برآمد)
{
  // Level 6 corresponds to TDEFL_DEFAULT_MAX_PROBES or MZ_DEFAULT_LEVEL (but we can't depend on MZ_DEFAULT_LEVEL being available in case the zlib API's where #defined out)
  واپس tdefl_write_image_مقصد_png_file_اندر_حافظہ_ex(pImage, w, h, عدد_chans, bpl, p_Len_برآمد, 6, MZ_FALSE, تہی, 0, تہی, 0);
}
#اگر_ختم

#اگر_تعریف_شدہ _MSC_VER
#ہدایت warning (نکالو)
#اگر_ختم
#اگر_ختم /*#ifndef MINIZ_NO_DEFLATE_APIS*/

// ------------------- .ZIP archive reading

#اگر_غیر_تعریف_شدہ MINIZ_NO_ARCHIVE_APIS

#اگر_تعریف_شدہ MINIZ_NO_STDIO
  #تعریف_کرو MZ_FILE خالی *
#ورنہ
  #شامل <stdio.h>
  #شامل <sys/stat.h>

  #اگر defined(_MSC_VER) || defined(__MINGW64__)
    ساکن FILE *mz_fopen(ثابت حرف *pFilename, ثابت حرف *p_منوال)
    {
      FILE* pFile = تہی;
      fopen_s(&pFile, pFilename, p_منوال);
      واپس pFile;
    }
    ساکن FILE *mz_freopen(ثابت حرف *p_راستہ, ثابت حرف *p_منوال, FILE *p_دھارا)
    {
      FILE* pFile = تہی;
      اگر (freopen_s(&pFile, p_راستہ, p_منوال, p_دھارا))
        واپس تہی;
      واپس pFile;
    }
    #اگر_غیر_تعریف_شدہ MINIZ_NO_وقت
      #شامل <sys/utime.h>
    #اگر_ختم
    #تعریف_کرو MZ_FILE FILE
    #تعریف_کرو MZ_FOPEN mz_fopen
    #تعریف_کرو MZ_FCLOSE fclose
    #تعریف_کرو MZ_FREAD fread
    #تعریف_کرو MZ_FWRITE fwrite
    #تعریف_کرو MZ_FTELL64 _ftelli64
    #تعریف_کرو MZ_FSEEK64 _fseeki64
    #تعریف_کرو MZ_FILE_STAT_STRUCT _stat
    #تعریف_کرو MZ_FILE_STAT _stat
    #تعریف_کرو MZ_FFLUSH fflush
    #تعریف_کرو MZ_FREOPEN mz_freopen
    #تعریف_کرو MZ_DELETE_FILE remove
  #وگرنہ_اگر defined(__MINGW32__)
    #اگر_غیر_تعریف_شدہ MINIZ_NO_وقت
      #شامل <sys/utime.h>
    #اگر_ختم
    #تعریف_کرو MZ_FILE FILE
    #تعریف_کرو MZ_FOPEN(f, m) fopen(f, m)
    #تعریف_کرو MZ_FCLOSE fclose
    #تعریف_کرو MZ_FREAD fread
    #تعریف_کرو MZ_FWRITE fwrite
    #تعریف_کرو MZ_FTELL64 ftello64
    #تعریف_کرو MZ_FSEEK64 fseeko64
    #تعریف_کرو MZ_FILE_STAT_STRUCT _stat
    #تعریف_کرو MZ_FILE_STAT _stat
    #تعریف_کرو MZ_FFLUSH fflush
    #تعریف_کرو MZ_FREOPEN(f, m, s) freopen(f, m, s)
    #تعریف_کرو MZ_DELETE_FILE remove
  #وگرنہ_اگر defined(__TINYC__)
    #اگر_غیر_تعریف_شدہ MINIZ_NO_وقت
      #شامل <sys/utime.h>
    #اگر_ختم
    #تعریف_کرو MZ_FILE FILE
    #تعریف_کرو MZ_FOPEN(f, m) fopen(f, m)
    #تعریف_کرو MZ_FCLOSE fclose
    #تعریف_کرو MZ_FREAD fread
    #تعریف_کرو MZ_FWRITE fwrite
    #تعریف_کرو MZ_FTELL64 ftell
    #تعریف_کرو MZ_FSEEK64 fseek
    #تعریف_کرو MZ_FILE_STAT_STRUCT stat
    #تعریف_کرو MZ_FILE_STAT stat
    #تعریف_کرو MZ_FFLUSH fflush
    #تعریف_کرو MZ_FREOPEN(f, m, s) freopen(f, m, s)
    #تعریف_کرو MZ_DELETE_FILE remove
  #وگرنہ_اگر defined(__GNUC__) && LARGEFILE64_ماخذ
    #اگر_غیر_تعریف_شدہ MINIZ_NO_وقت
      #شامل <utime.h>
    #اگر_ختم
    #تعریف_کرو MZ_FILE FILE
    #تعریف_کرو MZ_FOPEN(f, m) fopen64(f, m)
    #تعریف_کرو MZ_FCLOSE fclose
    #تعریف_کرو MZ_FREAD fread
    #تعریف_کرو MZ_FWRITE fwrite
    #تعریف_کرو MZ_FTELL64 ftello64
    #تعریف_کرو MZ_FSEEK64 fseeko64
    #تعریف_کرو MZ_FILE_STAT_STRUCT stat64
    #تعریف_کرو MZ_FILE_STAT stat64
    #تعریف_کرو MZ_FFLUSH fflush
    #تعریف_کرو MZ_FREOPEN(p, m, s) freopen64(p, m, s)
    #تعریف_کرو MZ_DELETE_FILE remove
  #ورنہ
    #اگر_غیر_تعریف_شدہ MINIZ_NO_وقت
      #شامل <utime.h>
    #اگر_ختم
    #تعریف_کرو MZ_FILE FILE
    #تعریف_کرو MZ_FOPEN(f, m) fopen(f, m)
    #تعریف_کرو MZ_FCLOSE fclose
    #تعریف_کرو MZ_FREAD fread
    #تعریف_کرو MZ_FWRITE fwrite
    #تعریف_کرو MZ_FTELL64 ftello
    #تعریف_کرو MZ_FSEEK64 fseeko
    #تعریف_کرو MZ_FILE_STAT_STRUCT stat
    #تعریف_کرو MZ_FILE_STAT stat
    #تعریف_کرو MZ_FFLUSH fflush
    #تعریف_کرو MZ_FREOPEN(f, m, s) freopen(f, m, s)
    #تعریف_کرو MZ_DELETE_FILE remove
  #اگر_ختم // #ifdef _MSC_VER
#اگر_ختم // #ifdef MINIZ_NO_STDIO

#تعریف_کرو MZ_TOLOWER(c) ((((c) >= 'A') && ((c) <= 'Z')) ? ((c) - 'A' + 'a') : (c))

// Various ZIP archive enums. To completely avoid cross platform compiler alignment and platform endian issues, miniz.c doesn't use structs for any of this stuff.
شمار
{
  // ZIP archive identifiers and record sizes
  MZ_ZIP_انتہا_کا_CENTRAL_DIR_سرخی_SIG = 0x06054b50, MZ_ZIP_CENTRAL_DIR_سرخی_SIG = 0x02014b50, MZ_ZIP_LOCAL_DIR_سرخی_SIG = 0x04034b50,
  MZ_ZIP_LOCAL_DIR_سرخی_سائز = 30, MZ_ZIP_CENTRAL_DIR_سرخی_سائز = 46, MZ_ZIP_انتہا_کا_CENTRAL_DIR_سرخی_سائز = 22,
  // Central directory header record offsets
  MZ_ZIP_CDH_SIG_OFS = 0, MZ_ZIP_CDH_نسخہ_MADE_BY_OFS = 4, MZ_ZIP_CDH_نسخہ_NEEDED_OFS = 6, MZ_ZIP_CDH_ثنائی_ہندسہ_FLAG_OFS = 8,
  MZ_ZIP_CDH_طریقہ_OFS = 10, MZ_ZIP_CDH_FILE_وقت_OFS = 12, MZ_ZIP_CDH_FILE_DATE_OFS = 14, MZ_ZIP_CDH_چکری_جانچ_32_OFS = 16,
  MZ_ZIP_CDH_COMPRESSED_سائز_OFS = 20, MZ_ZIP_CDH_DECOMPRESSED_سائز_OFS = 24, MZ_ZIP_CDH_FILENAME_LEN_OFS = 28, MZ_ZIP_CDH_EXTRA_LEN_OFS = 30,
  MZ_ZIP_CDH_COMMENT_LEN_OFS = 32, MZ_ZIP_CDH_DISK_آغاز_OFS = 34, MZ_ZIP_CDH_اندرونی_ATTR_OFS = 36, MZ_ZIP_CDH_EXTERNAL_ATTR_OFS = 38, MZ_ZIP_CDH_LOCAL_سرخی_OFS = 42,
  // Local directory header offsets
  MZ_ZIP_LDH_SIG_OFS = 0, MZ_ZIP_LDH_نسخہ_NEEDED_OFS = 4, MZ_ZIP_LDH_ثنائی_ہندسہ_FLAG_OFS = 6, MZ_ZIP_LDH_طریقہ_OFS = 8, MZ_ZIP_LDH_FILE_وقت_OFS = 10,
  MZ_ZIP_LDH_FILE_DATE_OFS = 12, MZ_ZIP_LDH_چکری_جانچ_32_OFS = 14, MZ_ZIP_LDH_COMPRESSED_سائز_OFS = 18, MZ_ZIP_LDH_DECOMPRESSED_سائز_OFS = 22,
  MZ_ZIP_LDH_FILENAME_LEN_OFS = 26, MZ_ZIP_LDH_EXTRA_LEN_OFS = 28,
  // End of central directory offsets
  MZ_ZIP_ECDH_SIG_OFS = 0, MZ_ZIP_ECDH_عدد_THIS_DISK_OFS = 4, MZ_ZIP_ECDH_عدد_DISK_CDIR_OFS = 6, MZ_ZIP_ECDH_CDIR_عدد_ENTRIES_ON_DISK_OFS = 8,
  MZ_ZIP_ECDH_CDIR_کل_ENTRIES_OFS = 10, MZ_ZIP_ECDH_CDIR_سائز_OFS = 12, MZ_ZIP_ECDH_CDIR_OFS_OFS = 16, MZ_ZIP_ECDH_COMMENT_سائز_OFS = 20,
};

قسمتعریف ساخت
{
  خالی *m_p;
  size_t m_سائز, m_استعداد;
  mz_uint m_element_سائز;
} mz_zip_array;

ساخت mz_zip_اندرونی_state_لیبل
{
  mz_zip_array m_central_dir;
  mz_zip_array m_central_dir_offsets;
  mz_zip_array m_sorted_central_dir_offsets;
  MZ_FILE *m_pFile;
  خالی *m_pMem;
  size_t m_mem_سائز;
  size_t m_mem_استعداد;
};

#تعریف_کرو MZ_ZIP_ARRAY_سیٹ_ELEMENT_سائز(array_ptr, element_سائز) (array_ptr)->m_element_سائز = element_سائز
#تعریف_کرو MZ_ZIP_ARRAY_ELEMENT(array_ptr, element_type, اشاریہ) ((element_type *)((array_ptr)->m_p))[اشاریہ]

ساکن MZ_FORCEINLINE خالی mz_zip_array_clear(mz_zip_archive *pZip, mz_zip_array *pArray)
{
  pZip->m_pFree(pZip->m_pAlloc_opaque, pArray->m_p);
  memset(pArray, 0, حجم(mz_zip_array));
}

ساکن mz_bool mz_zip_array_ensure_استعداد(mz_zip_archive *pZip, mz_zip_array *pArray, size_t min_new_استعداد, mz_uint growing)
{
  خالی *pNew_p; size_t new_استعداد = min_new_استعداد; MZ_ASSERT(pArray->m_element_سائز); اگر (pArray->m_استعداد >= min_new_استعداد) واپس MZ_TRUE;
  اگر (growing) { new_استعداد = MZ_MAX(1, pArray->m_استعداد); جب (new_استعداد < min_new_استعداد) new_استعداد *= 2; }
  اگر (تہی == (pNew_p = pZip->m_pRealloc(pZip->m_pAlloc_opaque, pArray->m_p, pArray->m_element_سائز, new_استعداد))) واپس MZ_FALSE;
  pArray->m_p = pNew_p; pArray->m_استعداد = new_استعداد;
  واپس MZ_TRUE;
}

ساکن MZ_FORCEINLINE mz_bool mz_zip_array_reserve(mz_zip_archive *pZip, mz_zip_array *pArray, size_t new_استعداد, mz_uint growing)
{
  اگر (new_استعداد > pArray->m_استعداد) { اگر (!mz_zip_array_ensure_استعداد(pZip, pArray, new_استعداد, growing)) واپس MZ_FALSE; }
  واپس MZ_TRUE;
}

ساکن MZ_FORCEINLINE mz_bool mz_zip_array_resize(mz_zip_archive *pZip, mz_zip_array *pArray, size_t new_سائز, mz_uint growing)
{
  اگر (new_سائز > pArray->m_استعداد) { اگر (!mz_zip_array_ensure_استعداد(pZip, pArray, new_سائز, growing)) واپس MZ_FALSE; }
  pArray->m_سائز = new_سائز;
  واپس MZ_TRUE;
}

ساکن MZ_FORCEINLINE mz_bool mz_zip_array_ensure_گنجائش(mz_zip_archive *pZip, mz_zip_array *pArray, size_t n)
{
  واپس mz_zip_array_reserve(pZip, pArray, pArray->m_سائز + n, MZ_TRUE);
}

ساکن MZ_FORCEINLINE mz_bool mz_zip_array_ڈالو_عقب(mz_zip_archive *pZip, mz_zip_array *pArray, ثابت خالی *pElements, size_t n)
{
  size_t orig_سائز = pArray->m_سائز; اگر (!mz_zip_array_resize(pZip, pArray, orig_سائز + n, MZ_TRUE)) واپس MZ_FALSE;
  حافظہ_نقل((mz_uint8*)pArray->m_p + orig_سائز * pArray->m_element_سائز, pElements, n * pArray->m_element_سائز);
  واپس MZ_TRUE;
}

#اگر_غیر_تعریف_شدہ MINIZ_NO_وقت
ساکن وقت_t mz_zip_dos_مقصد_وقت_t(صحیح dos_وقت, صحیح dos_date)
{
  ساخت tm tm;
  memset(&tm, 0, حجم(tm)); tm.tm_isdst = -1;
  tm.tm_year = ((dos_date >> 9) & 127) + 1980 - 1900; tm.tm_mon = ((dos_date >> 5) & 15) - 1; tm.tm_mday = dos_date & 31;
  tm.tm_hour = (dos_وقت >> 11) & 31; tm.tm_min = (dos_وقت >> 5) & 63; tm.tm_sec = (dos_وقت << 1) & 62;
  واپس mktime(&tm);
}

ساکن خالی mz_zip_وقت_مقصد_dos_وقت(وقت_t وقت, mz_uint16 *p_DOS_وقت, mz_uint16 *pDOS_date)
{
#اگر_تعریف_شدہ _MSC_VER
  ساخت tm tm_struct;
  ساخت tm *tm = &tm_struct;
  errno_t err = localtime_s(tm, &وقت);
  اگر (err)
  {
    *pDOS_date = 0; *p_DOS_وقت = 0;
    واپس;
  }
#ورنہ
  ساخت tm *tm = localtime(&وقت);
#اگر_ختم
  *p_DOS_وقت = (mz_uint16)(((tm->tm_hour) << 11) + ((tm->tm_min) << 5) + ((tm->tm_sec) >> 1));
  *pDOS_date = (mz_uint16)(((tm->tm_year + 1900 - 1980) << 9) + ((tm->tm_mon + 1) << 5) + tm->tm_mday);
}
#اگر_ختم

#اگر_غیر_تعریف_شدہ MINIZ_NO_STDIO
ساکن mz_bool mz_zip_get_file_modified_وقت(ثابت حرف *pFilename, mz_uint16 *p_DOS_وقت, mz_uint16 *pDOS_date)
{
#اگر_تعریف_شدہ MINIZ_NO_وقت
  (خالی)pFilename; *pDOS_date = *p_DOS_وقت = 0;
#ورنہ
  ساخت MZ_FILE_STAT_STRUCT file_stat;
  // On Linux with x86 glibc, this call will fail on large files (>= 0x80000000 bytes) unless you compiled with _LARGEFILE64_SOURCE. Argh.
  اگر (MZ_FILE_STAT(pFilename, &file_stat) != 0)
    واپس MZ_FALSE;
  mz_zip_وقت_مقصد_dos_وقت(file_stat.st_mtime, p_DOS_وقت, pDOS_date);
#اگر_ختم // #ifdef MINIZ_NO_TIME
  واپس MZ_TRUE;
}

#اگر_غیر_تعریف_شدہ MINIZ_NO_وقت
ساکن mz_bool mz_zip_سیٹ_file_times(ثابت حرف *pFilename, وقت_t access_وقت, وقت_t modified_وقت)
{
  ساخت utimbuf t; t.actime = access_وقت; t.modtime = modified_وقت;
  واپس !utime(pFilename, &t);
}
#اگر_ختم // #ifndef MINIZ_NO_TIME
#اگر_ختم // #ifndef MINIZ_NO_STDIO

ساکن mz_bool mz_zip_reader_init_اندرونی(mz_zip_archive *pZip, mz_uint32 flags)
{
  (خالی)flags;
  اگر ((!pZip) || (pZip->m_pState) || (pZip->m_zip_منوال != MZ_ZIP_منوال_INVALID))
    واپس MZ_FALSE;

  اگر (!pZip->m_pAlloc) pZip->m_pAlloc = def_alloc_func;
  اگر (!pZip->m_pFree) pZip->m_pFree = def_free_func;
  اگر (!pZip->m_pRealloc) pZip->m_pRealloc = def_realloc_func;

  pZip->m_zip_منوال = MZ_ZIP_منوال_READING;
  pZip->m_archive_سائز = 0;
  pZip->m_central_directory_file_ofs = 0;
  pZip->m_کل_files = 0;

  اگر (تہی == (pZip->m_pState = (mz_zip_اندرونی_state *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, حجم(mz_zip_اندرونی_state))))
    واپس MZ_FALSE;
  memset(pZip->m_pState, 0, حجم(mz_zip_اندرونی_state));
  MZ_ZIP_ARRAY_سیٹ_ELEMENT_سائز(&pZip->m_pState->m_central_dir, حجم(mz_uint8));
  MZ_ZIP_ARRAY_سیٹ_ELEMENT_سائز(&pZip->m_pState->m_central_dir_offsets, حجم(mz_uint32));
  MZ_ZIP_ARRAY_سیٹ_ELEMENT_سائز(&pZip->m_pState->m_sorted_central_dir_offsets, حجم(mz_uint32));
  واپس MZ_TRUE;
}

ساکن MZ_FORCEINLINE mz_bool mz_zip_reader_filename_less(ثابت mz_zip_array *pCentral_dir_array, ثابت mz_zip_array *pCentral_dir_offsets, mz_uint l_اشاریہ, mz_uint r_اشاریہ)
{
  ثابت mz_uint8 *pL = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, l_اشاریہ)), *pE;
  ثابت mz_uint8 *pR = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, r_اشاریہ));
  mz_uint l_len = MZ_READ_LE16(pL + MZ_ZIP_CDH_FILENAME_LEN_OFS), r_len = MZ_READ_LE16(pR + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  mz_uint8 l = 0, r = 0;
  pL += MZ_ZIP_CENTRAL_DIR_سرخی_سائز; pR += MZ_ZIP_CENTRAL_DIR_سرخی_سائز;
  pE = pL + MZ_MIN(l_len, r_len);
  جب (pL < pE)
  {
    اگر ((l = MZ_TOLOWER(*pL)) != (r = MZ_TOLOWER(*pR)))
      توڑو;
    pL++; pR++;
  }
  واپس (pL == pE) ? (l_len < r_len) : (l < r);
}

#تعریف_کرو MZ_تبادلہ_UINT32(a, b) کرو { mz_uint32 t = a; a = b; b = t; } MZ_MACRO_انتہا

// Heap sort of lowercased filenames, used to help accelerate plain central directory searches by mz_zip_reader_locate_file(). (Could also use qsort(), but it could allocate memory.)
ساکن خالی mz_zip_reader_ترتیب_دو_central_dir_offsets_by_filename(mz_zip_archive *pZip)
{
  mz_zip_اندرونی_state *pState = pZip->m_pState;
  ثابت mz_zip_array *pCentral_dir_offsets = &pState->m_central_dir_offsets;
  ثابت mz_zip_array *pCentral_dir = &pState->m_central_dir;
  mz_uint32 *pIndices = &MZ_ZIP_ARRAY_ELEMENT(&pState->m_sorted_central_dir_offsets, mz_uint32, 0);
  ثابت صحیح سائز = pZip->m_کل_files;
  صحیح آغاز = (سائز - 2) >> 1, انتہا;
  جب (آغاز >= 0)
  {
    صحیح بچہ, جڑ = آغاز;
    برائے ( ; ; )
    {
      اگر ((بچہ = (جڑ << 1) + 1) >= سائز)
        توڑو;
      بچہ += (((بچہ + 1) < سائز) && (mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[بچہ], pIndices[بچہ + 1])));
      اگر (!mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[جڑ], pIndices[بچہ]))
        توڑو;
      MZ_تبادلہ_UINT32(pIndices[جڑ], pIndices[بچہ]); جڑ = بچہ;
    }
    آغاز--;
  }

  انتہا = سائز - 1;
  جب (انتہا > 0)
  {
    صحیح بچہ, جڑ = 0;
    MZ_تبادلہ_UINT32(pIndices[انتہا], pIndices[0]);
    برائے ( ; ; )
    {
      اگر ((بچہ = (جڑ << 1) + 1) >= انتہا)
        توڑو;
      بچہ += (((بچہ + 1) < انتہا) && mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[بچہ], pIndices[بچہ + 1]));
      اگر (!mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[جڑ], pIndices[بچہ]))
        توڑو;
      MZ_تبادلہ_UINT32(pIndices[جڑ], pIndices[بچہ]); جڑ = بچہ;
    }
    انتہا--;
  }
}

ساکن mz_bool mz_zip_reader_read_central_dir(mz_zip_archive *pZip, mz_uint32 flags)
{
  mz_uint cdir_سائز, عدد_this_disk, cdir_disk_اشاریہ;
  mz_uint64 cdir_ofs;
  mz_int64 cur_file_ofs;
  ثابت mz_uint8 *p;
  mz_uint32 buf_u32[4096 / حجم(mz_uint32)]; mz_uint8 *pBuf = (mz_uint8 *)buf_u32;
  mz_bool ترتیب_دو_central_dir = ((flags & MZ_ZIP_FLAG_DO_NOT_ترتیب_دو_CENTRAL_DIRECTORY) == 0);
  // Basic sanity checks - reject files which are too small, and check the first 4 bytes of the file to make sure a local header is there.
  اگر (pZip->m_archive_سائز < MZ_ZIP_انتہا_کا_CENTRAL_DIR_سرخی_سائز)
    واپس MZ_FALSE;
  // Find the end of central directory record by scanning the file from the end towards the beginning.
  cur_file_ofs = MZ_MAX((mz_int64)pZip->m_archive_سائز - (mz_int64)حجم(buf_u32), 0);
  برائے ( ; ; )
  {
    صحیح i, n = (صحیح)MZ_MIN(حجم(buf_u32), pZip->m_archive_سائز - cur_file_ofs);
    اگر (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, n) != (mz_uint)n)
      واپس MZ_FALSE;
    برائے (i = n - 4; i >= 0; --i)
      اگر (MZ_READ_LE32(pBuf + i) == MZ_ZIP_انتہا_کا_CENTRAL_DIR_سرخی_SIG)
        توڑو;
    اگر (i >= 0)
    {
      cur_file_ofs += i;
      توڑو;
    }
    اگر ((!cur_file_ofs) || ((pZip->m_archive_سائز - cur_file_ofs) >= (0xFFFF + MZ_ZIP_انتہا_کا_CENTRAL_DIR_سرخی_سائز)))
      واپس MZ_FALSE;
    cur_file_ofs = MZ_MAX(cur_file_ofs - (حجم(buf_u32) - 3), 0);
  }
  // Read and verify the end of central directory record.
  اگر (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, MZ_ZIP_انتہا_کا_CENTRAL_DIR_سرخی_سائز) != MZ_ZIP_انتہا_کا_CENTRAL_DIR_سرخی_سائز)
    واپس MZ_FALSE;
  اگر ((MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_SIG_OFS) != MZ_ZIP_انتہا_کا_CENTRAL_DIR_سرخی_SIG) ||
      ((pZip->m_کل_files = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_CDIR_کل_ENTRIES_OFS)) != MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_CDIR_عدد_ENTRIES_ON_DISK_OFS)))
    واپس MZ_FALSE;

  عدد_this_disk = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_عدد_THIS_DISK_OFS);
  cdir_disk_اشاریہ = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_عدد_DISK_CDIR_OFS);
  اگر (((عدد_this_disk | cdir_disk_اشاریہ) != 0) && ((عدد_this_disk != 1) || (cdir_disk_اشاریہ != 1)))
    واپس MZ_FALSE;

  اگر ((cdir_سائز = MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_CDIR_سائز_OFS)) < pZip->m_کل_files * MZ_ZIP_CENTRAL_DIR_سرخی_سائز)
    واپس MZ_FALSE;

  cdir_ofs = MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_CDIR_OFS_OFS);
  اگر ((cdir_ofs + (mz_uint64)cdir_سائز) > pZip->m_archive_سائز)
    واپس MZ_FALSE;

  pZip->m_central_directory_file_ofs = cdir_ofs;

  اگر (pZip->m_کل_files)
  {
     mz_uint i, n;

    // Read the entire central directory into a heap block, and allocate another heap block to hold the unsorted central dir file record offsets, and another to hold the sorted indices.
    اگر ((!mz_zip_array_resize(pZip, &pZip->m_pState->m_central_dir, cdir_سائز, MZ_FALSE)) ||
        (!mz_zip_array_resize(pZip, &pZip->m_pState->m_central_dir_offsets, pZip->m_کل_files, MZ_FALSE)))
      واپس MZ_FALSE;

    اگر (ترتیب_دو_central_dir)
    {
      اگر (!mz_zip_array_resize(pZip, &pZip->m_pState->m_sorted_central_dir_offsets, pZip->m_کل_files, MZ_FALSE))
        واپس MZ_FALSE;
    }

    اگر (pZip->m_pRead(pZip->m_pIO_opaque, cdir_ofs, pZip->m_pState->m_central_dir.m_p, cdir_سائز) != cdir_سائز)
      واپس MZ_FALSE;

    // Now create an index into the central directory file records, do some basic sanity checking on each record, and check for zip64 entries (which are not yet supported).
    p = (ثابت mz_uint8 *)pZip->m_pState->m_central_dir.m_p;
    برائے (n = cdir_سائز, i = 0; i < pZip->m_کل_files; ++i)
    {
      mz_uint کل_سرخی_سائز, comp_سائز, decomp_سائز, disk_اشاریہ;
      اگر ((n < MZ_ZIP_CENTRAL_DIR_سرخی_سائز) || (MZ_READ_LE32(p) != MZ_ZIP_CENTRAL_DIR_سرخی_SIG))
        واپس MZ_FALSE;
      MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, i) = (mz_uint32)(p - (ثابت mz_uint8 *)pZip->m_pState->m_central_dir.m_p);
      اگر (ترتیب_دو_central_dir)
        MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_sorted_central_dir_offsets, mz_uint32, i) = i;
      comp_سائز = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_سائز_OFS);
      decomp_سائز = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_سائز_OFS);
      اگر (((!MZ_READ_LE32(p + MZ_ZIP_CDH_طریقہ_OFS)) && (decomp_سائز != comp_سائز)) || (decomp_سائز && !comp_سائز) || (decomp_سائز == 0xFFFFFFFF) || (comp_سائز == 0xFFFFFFFF))
        واپس MZ_FALSE;
      disk_اشاریہ = MZ_READ_LE16(p + MZ_ZIP_CDH_DISK_آغاز_OFS);
      اگر ((disk_اشاریہ != عدد_this_disk) && (disk_اشاریہ != 1))
        واپس MZ_FALSE;
      اگر (((mz_uint64)MZ_READ_LE32(p + MZ_ZIP_CDH_LOCAL_سرخی_OFS) + MZ_ZIP_LOCAL_DIR_سرخی_سائز + comp_سائز) > pZip->m_archive_سائز)
        واپس MZ_FALSE;
      اگر ((کل_سرخی_سائز = MZ_ZIP_CENTRAL_DIR_سرخی_سائز + MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_EXTRA_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_COMMENT_LEN_OFS)) > n)
        واپس MZ_FALSE;
      n -= کل_سرخی_سائز; p += کل_سرخی_سائز;
    }
  }

  اگر (ترتیب_دو_central_dir)
    mz_zip_reader_ترتیب_دو_central_dir_offsets_by_filename(pZip);

  واپس MZ_TRUE;
}

mz_bool mz_zip_reader_init(mz_zip_archive *pZip, mz_uint64 سائز, mz_uint32 flags)
{
  اگر ((!pZip) || (!pZip->m_pRead))
    واپس MZ_FALSE;
  اگر (!mz_zip_reader_init_اندرونی(pZip, flags))
    واپس MZ_FALSE;
  pZip->m_archive_سائز = سائز;
  اگر (!mz_zip_reader_read_central_dir(pZip, flags))
  {
    mz_zip_reader_انتہا(pZip);
    واپس MZ_FALSE;
  }
  واپس MZ_TRUE;
}

ساکن size_t mz_zip_mem_read_func(خالی *pOpaque, mz_uint64 file_ofs, خالی *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  size_t s = (file_ofs >= pZip->m_archive_سائز) ? 0 : (size_t)MZ_MIN(pZip->m_archive_سائز - file_ofs, n);
  حافظہ_نقل(pBuf, (ثابت mz_uint8 *)pZip->m_pState->m_pMem + file_ofs, s);
  واپس s;
}

mz_bool mz_zip_reader_init_mem(mz_zip_archive *pZip, ثابت خالی *pMem, size_t سائز, mz_uint32 flags)
{
  اگر (!mz_zip_reader_init_اندرونی(pZip, flags))
    واپس MZ_FALSE;
  pZip->m_archive_سائز = سائز;
  pZip->m_pRead = mz_zip_mem_read_func;
  pZip->m_pIO_opaque = pZip;
#اگر_تعریف_شدہ __cplusplus
  pZip->m_pState->m_pMem = const_cast<خالی *>(pMem);
#ورنہ
  pZip->m_pState->m_pMem = (خالی *)pMem;
#اگر_ختم
  pZip->m_pState->m_mem_سائز = سائز;
  اگر (!mz_zip_reader_read_central_dir(pZip, flags))
  {
    mz_zip_reader_انتہا(pZip);
    واپس MZ_FALSE;
  }
  واپس MZ_TRUE;
}

#اگر_غیر_تعریف_شدہ MINIZ_NO_STDIO
ساکن size_t mz_zip_file_read_func(خالی *pOpaque, mz_uint64 file_ofs, خالی *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_int64 cur_ofs = MZ_FTELL64(pZip->m_pState->m_pFile);
  اگر (((mz_int64)file_ofs < 0) || (((cur_ofs != (mz_int64)file_ofs)) && (MZ_FSEEK64(pZip->m_pState->m_pFile, (mz_int64)file_ofs, SEEK_SET))))
    واپس 0;
  واپس MZ_FREAD(pBuf, 1, n, pZip->m_pState->m_pFile);
}

mz_bool mz_zip_reader_init_file(mz_zip_archive *pZip, ثابت حرف *pFilename, mz_uint32 flags)
{
  mz_uint64 file_سائز;
  MZ_FILE *pFile = MZ_FOPEN(pFilename, "rb");
  اگر (!pFile)
    واپس MZ_FALSE;
  اگر (MZ_FSEEK64(pFile, 0, SEEK_END))
  {
    MZ_FCLOSE(pFile);
    واپس MZ_FALSE;
  }
  file_سائز = MZ_FTELL64(pFile);
  اگر (!mz_zip_reader_init_اندرونی(pZip, flags))
  {
    MZ_FCLOSE(pFile);
    واپس MZ_FALSE;
  }
  pZip->m_pRead = mz_zip_file_read_func;
  pZip->m_pIO_opaque = pZip;
  pZip->m_pState->m_pFile = pFile;
  pZip->m_archive_سائز = file_سائز;
  اگر (!mz_zip_reader_read_central_dir(pZip, flags))
  {
    mz_zip_reader_انتہا(pZip);
    واپس MZ_FALSE;
  }
  واپس MZ_TRUE;
}
#اگر_ختم // #ifndef MINIZ_NO_STDIO

mz_uint mz_zip_reader_get_عدد_files(mz_zip_archive *pZip)
{
  واپس pZip ? pZip->m_کل_files : 0;
}

ساکن MZ_FORCEINLINE ثابت mz_uint8 *mz_zip_reader_get_cdh(mz_zip_archive *pZip, mz_uint file_اشاریہ)
{
  اگر ((!pZip) || (!pZip->m_pState) || (file_اشاریہ >= pZip->m_کل_files) || (pZip->m_zip_منوال != MZ_ZIP_منوال_READING))
    واپس تہی;
  واپس &MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_اشاریہ));
}

mz_bool mz_zip_reader_is_file_encrypted(mz_zip_archive *pZip, mz_uint file_اشاریہ)
{
  mz_uint m_ثنائی_ہندسہ_flag;
  ثابت mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_اشاریہ);
  اگر (!p)
    واپس MZ_FALSE;
  m_ثنائی_ہندسہ_flag = MZ_READ_LE16(p + MZ_ZIP_CDH_ثنائی_ہندسہ_FLAG_OFS);
  واپس (m_ثنائی_ہندسہ_flag & 1);
}

mz_bool mz_zip_reader_is_file_a_directory(mz_zip_archive *pZip, mz_uint file_اشاریہ)
{
  mz_uint filename_len, external_attr;
  ثابت mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_اشاریہ);
  اگر (!p)
    واپس MZ_FALSE;

  // First see if the filename ends with a '/' character.
  filename_len = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  اگر (filename_len)
  {
    اگر (*(p + MZ_ZIP_CENTRAL_DIR_سرخی_سائز + filename_len - 1) == '/')
      واپس MZ_TRUE;
  }

  // Bugfix: This code was also checking if the internal attribute was non-zero, which wasn't correct.
  // Most/all zip writers (hopefully) set DOS file/directory attributes in the low 16-bits, so check for the DOS directory flag and ignore the source OS ID in the created by field.
  // FIXME: Remove this check? Is it necessary - we already check the filename.
  external_attr = MZ_READ_LE32(p + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS);
  اگر ((external_attr & 0x10) != 0)
    واپس MZ_TRUE;

  واپس MZ_FALSE;
}

mz_bool mz_zip_reader_file_stat(mz_zip_archive *pZip, mz_uint file_اشاریہ, mz_zip_archive_file_stat *pStat)
{
  mz_uint n;
  ثابت mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_اشاریہ);
  اگر ((!p) || (!pStat))
    واپس MZ_FALSE;

  // Unpack the central directory record.
  pStat->m_file_اشاریہ = file_اشاریہ;
  pStat->m_central_dir_ofs = MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_اشاریہ);
  pStat->m_نسخہ_made_by = MZ_READ_LE16(p + MZ_ZIP_CDH_نسخہ_MADE_BY_OFS);
  pStat->m_نسخہ_needed = MZ_READ_LE16(p + MZ_ZIP_CDH_نسخہ_NEEDED_OFS);
  pStat->m_ثنائی_ہندسہ_flag = MZ_READ_LE16(p + MZ_ZIP_CDH_ثنائی_ہندسہ_FLAG_OFS);
  pStat->m_طریقہ = MZ_READ_LE16(p + MZ_ZIP_CDH_طریقہ_OFS);
#اگر_غیر_تعریف_شدہ MINIZ_NO_وقت
  pStat->m_وقت = mz_zip_dos_مقصد_وقت_t(MZ_READ_LE16(p + MZ_ZIP_CDH_FILE_وقت_OFS), MZ_READ_LE16(p + MZ_ZIP_CDH_FILE_DATE_OFS));
#اگر_ختم
  pStat->m_چکری_جانچ_32 = MZ_READ_LE32(p + MZ_ZIP_CDH_چکری_جانچ_32_OFS);
  pStat->m_comp_سائز = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_سائز_OFS);
  pStat->m_uncomp_سائز = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_سائز_OFS);
  pStat->m_اندرونی_attr = MZ_READ_LE16(p + MZ_ZIP_CDH_اندرونی_ATTR_OFS);
  pStat->m_external_attr = MZ_READ_LE32(p + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS);
  pStat->m_local_سرخی_ofs = MZ_READ_LE32(p + MZ_ZIP_CDH_LOCAL_سرخی_OFS);

  // Copy as much of the filename and comment as possible.
  n = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS); n = MZ_MIN(n, MZ_ZIP_MAX_ARCHIVE_FILENAME_سائز - 1);
  حافظہ_نقل(pStat->m_filename, p + MZ_ZIP_CENTRAL_DIR_سرخی_سائز, n); pStat->m_filename[n] = '\0';

  n = MZ_READ_LE16(p + MZ_ZIP_CDH_COMMENT_LEN_OFS); n = MZ_MIN(n, MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_سائز - 1);
  pStat->m_comment_سائز = n;
  حافظہ_نقل(pStat->m_comment, p + MZ_ZIP_CENTRAL_DIR_سرخی_سائز + MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_EXTRA_LEN_OFS), n); pStat->m_comment[n] = '\0';

  واپس MZ_TRUE;
}

mz_uint mz_zip_reader_get_filename(mz_zip_archive *pZip, mz_uint file_اشاریہ, حرف *pFilename, mz_uint filename_buf_سائز)
{
  mz_uint n;
  ثابت mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_اشاریہ);
  اگر (!p) { اگر (filename_buf_سائز) pFilename[0] = '\0'; واپس 0; }
  n = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  اگر (filename_buf_سائز)
  {
    n = MZ_MIN(n, filename_buf_سائز - 1);
    حافظہ_نقل(pFilename, p + MZ_ZIP_CENTRAL_DIR_سرخی_سائز, n);
    pFilename[n] = '\0';
  }
  واپس n + 1;
}

ساکن MZ_FORCEINLINE mz_bool mz_zip_reader_string_equal(ثابت حرف *pA, ثابت حرف *pB, mz_uint len, mz_uint flags)
{
  mz_uint i;
  اگر (flags & MZ_ZIP_FLAG_CASE_SENSITIVE)
    واپس 0 == memcmp(pA, pB, len);
  برائے (i = 0; i < len; ++i)
    اگر (MZ_TOLOWER(pA[i]) != MZ_TOLOWER(pB[i]))
      واپس MZ_FALSE;
  واپس MZ_TRUE;
}

ساکن MZ_FORCEINLINE صحیح mz_zip_reader_filename_compare(ثابت mz_zip_array *pCentral_dir_array, ثابت mz_zip_array *pCentral_dir_offsets, mz_uint l_اشاریہ, ثابت حرف *pR, mz_uint r_len)
{
  ثابت mz_uint8 *pL = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, l_اشاریہ)), *pE;
  mz_uint l_len = MZ_READ_LE16(pL + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  mz_uint8 l = 0, r = 0;
  pL += MZ_ZIP_CENTRAL_DIR_سرخی_سائز;
  pE = pL + MZ_MIN(l_len, r_len);
  جب (pL < pE)
  {
    اگر ((l = MZ_TOLOWER(*pL)) != (r = MZ_TOLOWER(*pR)))
      توڑو;
    pL++; pR++;
  }
  واپس (pL == pE) ? (صحیح)(l_len - r_len) : (l - r);
}

ساکن صحیح mz_zip_reader_locate_file_ثنائی_تلاش(mz_zip_archive *pZip, ثابت حرف *pFilename)
{
  mz_zip_اندرونی_state *pState = pZip->m_pState;
  ثابت mz_zip_array *pCentral_dir_offsets = &pState->m_central_dir_offsets;
  ثابت mz_zip_array *pCentral_dir = &pState->m_central_dir;
  mz_uint32 *pIndices = &MZ_ZIP_ARRAY_ELEMENT(&pState->m_sorted_central_dir_offsets, mz_uint32, 0);
  ثابت صحیح سائز = pZip->m_کل_files;
  ثابت mz_uint filename_len = (mz_uint)لڑی_لمبائی(pFilename);
  صحیح l = 0, h = سائز - 1;
  جب (l <= h)
  {
    صحیح m = (l + h) >> 1, file_اشاریہ = pIndices[m], comp = mz_zip_reader_filename_compare(pCentral_dir, pCentral_dir_offsets, file_اشاریہ, pFilename, filename_len);
    اگر (!comp)
      واپس file_اشاریہ;
    ورنہ اگر (comp < 0)
      l = m + 1;
    ورنہ
      h = m - 1;
  }
  واپس -1;
}

صحیح mz_zip_reader_locate_file(mz_zip_archive *pZip, ثابت حرف *pName, ثابت حرف *pComment, mz_uint flags)
{
  mz_uint file_اشاریہ; size_t name_len, comment_len;
  اگر ((!pZip) || (!pZip->m_pState) || (!pName) || (pZip->m_zip_منوال != MZ_ZIP_منوال_READING))
    واپس -1;
  اگر (((flags & (MZ_ZIP_FLAG_IGNORE_راستہ | MZ_ZIP_FLAG_CASE_SENSITIVE)) == 0) && (!pComment) && (pZip->m_pState->m_sorted_central_dir_offsets.m_سائز))
    واپس mz_zip_reader_locate_file_ثنائی_تلاش(pZip, pName);
  name_len = لڑی_لمبائی(pName); اگر (name_len > 0xFFFF) واپس -1;
  comment_len = pComment ? لڑی_لمبائی(pComment) : 0; اگر (comment_len > 0xFFFF) واپس -1;
  برائے (file_اشاریہ = 0; file_اشاریہ < pZip->m_کل_files; file_اشاریہ++)
  {
    ثابت mz_uint8 *p_سرخی = &MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_اشاریہ));
    mz_uint filename_len = MZ_READ_LE16(p_سرخی + MZ_ZIP_CDH_FILENAME_LEN_OFS);
    ثابت حرف *pFilename = (ثابت حرف *)p_سرخی + MZ_ZIP_CENTRAL_DIR_سرخی_سائز;
    اگر (filename_len < name_len)
      جاری;
    اگر (comment_len)
    {
      mz_uint file_extra_len = MZ_READ_LE16(p_سرخی + MZ_ZIP_CDH_EXTRA_LEN_OFS), file_comment_len = MZ_READ_LE16(p_سرخی + MZ_ZIP_CDH_COMMENT_LEN_OFS);
      ثابت حرف *pFile_comment = pFilename + filename_len + file_extra_len;
      اگر ((file_comment_len != comment_len) || (!mz_zip_reader_string_equal(pComment, pFile_comment, file_comment_len, flags)))
        جاری;
    }
    اگر ((flags & MZ_ZIP_FLAG_IGNORE_راستہ) && (filename_len))
    {
      صحیح ofs = filename_len - 1;
      کرو
      {
        اگر ((pFilename[ofs] == '/') || (pFilename[ofs] == '\\') || (pFilename[ofs] == ':'))
          توڑو;
      } جب (--ofs >= 0);
      ofs++;
      pFilename += ofs; filename_len -= ofs;
    }
    اگر ((filename_len == name_len) && (mz_zip_reader_string_equal(pName, pFilename, filename_len, flags)))
      واپس file_اشاریہ;
  }
  واپس -1;
}

mz_bool mz_zip_reader_نکالو_مقصد_mem_no_alloc(mz_zip_archive *pZip, mz_uint file_اشاریہ, خالی *pBuf, size_t buf_سائز_2, mz_uint flags, خالی *pUser_read_buf, size_t user_read_buf_سائز)
{
  صحیح حالت_2 = TINFL_حالت_مکمل;
  mz_uint64 needed_سائز, cur_file_ofs, comp_بقایا, برآمد_buf_ofs = 0, read_buf_سائز, read_buf_ofs = 0, read_buf_avail;
  mz_zip_archive_file_stat file_stat;
  خالی *pRead_buf;
  mz_uint32 local_سرخی_u32[(MZ_ZIP_LOCAL_DIR_سرخی_سائز + حجم(mz_uint32) - 1) / حجم(mz_uint32)]; mz_uint8 *p_Local_سرخی = (mz_uint8 *)local_سرخی_u32;
  tinfl_decompressor inflator;

  اگر ((buf_سائز_2) && (!pBuf))
    واپس MZ_FALSE;

  اگر (!mz_zip_reader_file_stat(pZip, file_اشاریہ, &file_stat))
    واپس MZ_FALSE;

  // Empty file, or a directory (but not always a directory - I've seen odd zips with directories that have compressed data which inflates to 0 bytes)
  اگر (!file_stat.m_comp_سائز)
    واپس MZ_TRUE;

  // Entry is a subdirectory (I've seen old zips with dir entries which have compressed deflate data which inflates to 0 bytes, but these entries claim to uncompress to 512 bytes in the headers).
  // I'm torn how to handle this case - should it fail instead?
  اگر (mz_zip_reader_is_file_a_directory(pZip, file_اشاریہ))
    واپس MZ_TRUE;

  // Encryption and patch files are not supported.
  اگر (file_stat.m_ثنائی_ہندسہ_flag & (1 | 32))
    واپس MZ_FALSE;

  // This function only supports stored and deflate.
  اگر ((!(flags & MZ_ZIP_FLAG_COMPRESSED_ڈیٹا)) && (file_stat.m_طریقہ != 0) && (file_stat.m_طریقہ != MZ_DEFLATED))
    واپس MZ_FALSE;

  // Ensure supplied output buffer is large enough.
  needed_سائز = (flags & MZ_ZIP_FLAG_COMPRESSED_ڈیٹا) ? file_stat.m_comp_سائز : file_stat.m_uncomp_سائز;
  اگر (buf_سائز_2 < needed_سائز)
    واپس MZ_FALSE;

  // Read and parse the local directory entry.
  cur_file_ofs = file_stat.m_local_سرخی_ofs;
  اگر (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, p_Local_سرخی, MZ_ZIP_LOCAL_DIR_سرخی_سائز) != MZ_ZIP_LOCAL_DIR_سرخی_سائز)
    واپس MZ_FALSE;
  اگر (MZ_READ_LE32(p_Local_سرخی) != MZ_ZIP_LOCAL_DIR_سرخی_SIG)
    واپس MZ_FALSE;

  cur_file_ofs += MZ_ZIP_LOCAL_DIR_سرخی_سائز + MZ_READ_LE16(p_Local_سرخی + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p_Local_سرخی + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  اگر ((cur_file_ofs + file_stat.m_comp_سائز) > pZip->m_archive_سائز)
    واپس MZ_FALSE;

  اگر ((flags & MZ_ZIP_FLAG_COMPRESSED_ڈیٹا) || (!file_stat.m_طریقہ))
  {
    // The file is stored or the caller has requested the compressed data.
    اگر (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, (size_t)needed_سائز) != needed_سائز)
      واپس MZ_FALSE;
    واپس ((flags & MZ_ZIP_FLAG_COMPRESSED_ڈیٹا) != 0) || (mz_چکری_جانچ_32(MZ_چکری_جانچ_32_INIT, (ثابت mz_uint8 *)pBuf, (size_t)file_stat.m_uncomp_سائز) == file_stat.m_چکری_جانچ_32);
  }

  // Decompress the file either directly from memory or from a file input buffer.
  tinfl_init(&inflator);

  اگر (pZip->m_pState->m_pMem)
  {
    // Read directly from the archive in memory.
    pRead_buf = (mz_uint8 *)pZip->m_pState->m_pMem + cur_file_ofs;
    read_buf_سائز = read_buf_avail = file_stat.m_comp_سائز;
    comp_بقایا = 0;
  }
  ورنہ اگر (pUser_read_buf)
  {
    // Use a user provided read buffer.
    اگر (!user_read_buf_سائز)
      واپس MZ_FALSE;
    pRead_buf = (mz_uint8 *)pUser_read_buf;
    read_buf_سائز = user_read_buf_سائز;
    read_buf_avail = 0;
    comp_بقایا = file_stat.m_comp_سائز;
  }
  ورنہ
  {
    // Temporarily allocate a read buffer.
    read_buf_سائز = MZ_MIN(file_stat.m_comp_سائز, MZ_ZIP_MAX_IO_BUF_سائز);
#اگر_تعریف_شدہ _MSC_VER
    اگر (((0, حجم(size_t) == حجم(mz_uint32))) && (read_buf_سائز > 0x7FFFFFFF))
#ورنہ
    اگر (((حجم(size_t) == حجم(mz_uint32))) && (read_buf_سائز > 0x7FFFFFFF))
#اگر_ختم
      واپس MZ_FALSE;
    اگر (تہی == (pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)read_buf_سائز)))
      واپس MZ_FALSE;
    read_buf_avail = 0;
    comp_بقایا = file_stat.m_comp_سائز;
  }

  کرو
  {
    size_t اندر_buf_سائز, برآمد_buf_سائز = (size_t)(file_stat.m_uncomp_سائز - برآمد_buf_ofs);
    اگر ((!read_buf_avail) && (!pZip->m_pState->m_pMem))
    {
      read_buf_avail = MZ_MIN(read_buf_سائز, comp_بقایا);
      اگر (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
      {
        حالت_2 = TINFL_حالت_FAILED;
        توڑو;
      }
      cur_file_ofs += read_buf_avail;
      comp_بقایا -= read_buf_avail;
      read_buf_ofs = 0;
    }
    اندر_buf_سائز = (size_t)read_buf_avail;
    حالت_2 = tinfl_decompress(&inflator, (mz_uint8 *)pRead_buf + read_buf_ofs, &اندر_buf_سائز, (mz_uint8 *)pBuf, (mz_uint8 *)pBuf + برآمد_buf_ofs, &برآمد_buf_سائز, TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF | (comp_بقایا ? TINFL_FLAG_HAS_مزید_داخلہ : 0));
    read_buf_avail -= اندر_buf_سائز;
    read_buf_ofs += اندر_buf_سائز;
    برآمد_buf_ofs += برآمد_buf_سائز;
  } جب (حالت_2 == TINFL_حالت_NEEDS_مزید_داخلہ);

  اگر (حالت_2 == TINFL_حالت_مکمل)
  {
    // Make sure the entire file was decompressed, and check its CRC.
    اگر ((برآمد_buf_ofs != file_stat.m_uncomp_سائز) || (mz_چکری_جانچ_32(MZ_چکری_جانچ_32_INIT, (ثابت mz_uint8 *)pBuf, (size_t)file_stat.m_uncomp_سائز) != file_stat.m_چکری_جانچ_32))
      حالت_2 = TINFL_حالت_FAILED;
  }

  اگر ((!pZip->m_pState->m_pMem) && (!pUser_read_buf))
    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);

  واپس حالت_2 == TINFL_حالت_مکمل;
}

mz_bool mz_zip_reader_نکالو_file_مقصد_mem_no_alloc(mz_zip_archive *pZip, ثابت حرف *pFilename, خالی *pBuf, size_t buf_سائز_2, mz_uint flags, خالی *pUser_read_buf, size_t user_read_buf_سائز)
{
  صحیح file_اشاریہ = mz_zip_reader_locate_file(pZip, pFilename, تہی, flags);
  اگر (file_اشاریہ < 0)
    واپس MZ_FALSE;
  واپس mz_zip_reader_نکالو_مقصد_mem_no_alloc(pZip, file_اشاریہ, pBuf, buf_سائز_2, flags, pUser_read_buf, user_read_buf_سائز);
}

mz_bool mz_zip_reader_نکالو_مقصد_mem(mz_zip_archive *pZip, mz_uint file_اشاریہ, خالی *pBuf, size_t buf_سائز_2, mz_uint flags)
{
  واپس mz_zip_reader_نکالو_مقصد_mem_no_alloc(pZip, file_اشاریہ, pBuf, buf_سائز_2, flags, تہی, 0);
}

mz_bool mz_zip_reader_نکالو_file_مقصد_mem(mz_zip_archive *pZip, ثابت حرف *pFilename, خالی *pBuf, size_t buf_سائز_2, mz_uint flags)
{
  واپس mz_zip_reader_نکالو_file_مقصد_mem_no_alloc(pZip, pFilename, pBuf, buf_سائز_2, flags, تہی, 0);
}

خالی *mz_zip_reader_نکالو_مقصد_ڈھیر(mz_zip_archive *pZip, mz_uint file_اشاریہ, size_t *p_سائز, mz_uint flags)
{
  mz_uint64 comp_سائز, uncomp_سائز, alloc_سائز_2;
  ثابت mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_اشاریہ);
  خالی *pBuf;

  اگر (p_سائز)
    *p_سائز = 0;
  اگر (!p)
    واپس تہی;

  comp_سائز = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_سائز_OFS);
  uncomp_سائز = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_سائز_OFS);

  alloc_سائز_2 = (flags & MZ_ZIP_FLAG_COMPRESSED_ڈیٹا) ? comp_سائز : uncomp_سائز;
#اگر_تعریف_شدہ _MSC_VER
  اگر (((0, حجم(size_t) == حجم(mz_uint32))) && (alloc_سائز_2 > 0x7FFFFFFF))
#ورنہ
  اگر (((حجم(size_t) == حجم(mz_uint32))) && (alloc_سائز_2 > 0x7FFFFFFF))
#اگر_ختم
    واپس تہی;
  اگر (تہی == (pBuf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)alloc_سائز_2)))
    واپس تہی;

  اگر (!mz_zip_reader_نکالو_مقصد_mem(pZip, file_اشاریہ, pBuf, (size_t)alloc_سائز_2, flags))
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
    واپس تہی;
  }

  اگر (p_سائز) *p_سائز = (size_t)alloc_سائز_2;
  واپس pBuf;
}

خالی *mz_zip_reader_نکالو_file_مقصد_ڈھیر(mz_zip_archive *pZip, ثابت حرف *pFilename, size_t *p_سائز, mz_uint flags)
{
  صحیح file_اشاریہ = mz_zip_reader_locate_file(pZip, pFilename, تہی, flags);
  اگر (file_اشاریہ < 0)
  {
    اگر (p_سائز) *p_سائز = 0;
    واپس MZ_FALSE;
  }
  واپس mz_zip_reader_نکالو_مقصد_ڈھیر(pZip, file_اشاریہ, p_سائز, flags);
}

mz_bool mz_zip_reader_نکالو_مقصد_callback(mz_zip_archive *pZip, mz_uint file_اشاریہ, mz_file_write_func pCallback, خالی *pOpaque, mz_uint flags)
{
  صحیح حالت_2 = TINFL_حالت_مکمل; mz_uint file_چکری_جانچ_32 = MZ_چکری_جانچ_32_INIT;
  mz_uint64 read_buf_سائز, read_buf_ofs = 0, read_buf_avail, comp_بقایا, برآمد_buf_ofs = 0, cur_file_ofs;
  mz_zip_archive_file_stat file_stat;
  خالی *pRead_buf = تہی; خالی *pWrite_buf = تہی;
  mz_uint32 local_سرخی_u32[(MZ_ZIP_LOCAL_DIR_سرخی_سائز + حجم(mz_uint32) - 1) / حجم(mz_uint32)]; mz_uint8 *p_Local_سرخی = (mz_uint8 *)local_سرخی_u32;

  اگر (!mz_zip_reader_file_stat(pZip, file_اشاریہ, &file_stat))
    واپس MZ_FALSE;

  // Empty file, or a directory (but not always a directory - I've seen odd zips with directories that have compressed data which inflates to 0 bytes)
  اگر (!file_stat.m_comp_سائز)
    واپس MZ_TRUE;

  // Entry is a subdirectory (I've seen old zips with dir entries which have compressed deflate data which inflates to 0 bytes, but these entries claim to uncompress to 512 bytes in the headers).
  // I'm torn how to handle this case - should it fail instead?
  اگر (mz_zip_reader_is_file_a_directory(pZip, file_اشاریہ))
    واپس MZ_TRUE;

  // Encryption and patch files are not supported.
  اگر (file_stat.m_ثنائی_ہندسہ_flag & (1 | 32))
    واپس MZ_FALSE;

  // This function only supports stored and deflate.
  اگر ((!(flags & MZ_ZIP_FLAG_COMPRESSED_ڈیٹا)) && (file_stat.m_طریقہ != 0) && (file_stat.m_طریقہ != MZ_DEFLATED))
    واپس MZ_FALSE;

  // Read and parse the local directory entry.
  cur_file_ofs = file_stat.m_local_سرخی_ofs;
  اگر (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, p_Local_سرخی, MZ_ZIP_LOCAL_DIR_سرخی_سائز) != MZ_ZIP_LOCAL_DIR_سرخی_سائز)
    واپس MZ_FALSE;
  اگر (MZ_READ_LE32(p_Local_سرخی) != MZ_ZIP_LOCAL_DIR_سرخی_SIG)
    واپس MZ_FALSE;

  cur_file_ofs += MZ_ZIP_LOCAL_DIR_سرخی_سائز + MZ_READ_LE16(p_Local_سرخی + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p_Local_سرخی + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  اگر ((cur_file_ofs + file_stat.m_comp_سائز) > pZip->m_archive_سائز)
    واپس MZ_FALSE;

  // Decompress the file either directly from memory or from a file input buffer.
  اگر (pZip->m_pState->m_pMem)
  {
    pRead_buf = (mz_uint8 *)pZip->m_pState->m_pMem + cur_file_ofs;
    read_buf_سائز = read_buf_avail = file_stat.m_comp_سائز;
    comp_بقایا = 0;
  }
  ورنہ
  {
    read_buf_سائز = MZ_MIN(file_stat.m_comp_سائز, MZ_ZIP_MAX_IO_BUF_سائز);
    اگر (تہی == (pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)read_buf_سائز)))
      واپس MZ_FALSE;
    read_buf_avail = 0;
    comp_بقایا = file_stat.m_comp_سائز;
  }

  اگر ((flags & MZ_ZIP_FLAG_COMPRESSED_ڈیٹا) || (!file_stat.m_طریقہ))
  {
    // The file is stored or the caller has requested the compressed data.
    اگر (pZip->m_pState->m_pMem)
    {
#اگر_تعریف_شدہ _MSC_VER
      اگر (((0, حجم(size_t) == حجم(mz_uint32))) && (file_stat.m_comp_سائز > 0xFFFFFFFF))
#ورنہ
      اگر (((حجم(size_t) == حجم(mz_uint32))) && (file_stat.m_comp_سائز > 0xFFFFFFFF))
#اگر_ختم
        واپس MZ_FALSE;
      اگر (pCallback(pOpaque, برآمد_buf_ofs, pRead_buf, (size_t)file_stat.m_comp_سائز) != file_stat.m_comp_سائز)
        حالت_2 = TINFL_حالت_FAILED;
      ورنہ اگر (!(flags & MZ_ZIP_FLAG_COMPRESSED_ڈیٹا))
        file_چکری_جانچ_32 = (mz_uint32)mz_چکری_جانچ_32(file_چکری_جانچ_32, (ثابت mz_uint8 *)pRead_buf, (size_t)file_stat.m_comp_سائز);
      cur_file_ofs += file_stat.m_comp_سائز;
      برآمد_buf_ofs += file_stat.m_comp_سائز;
      comp_بقایا = 0;
    }
    ورنہ
    {
      جب (comp_بقایا)
      {
        read_buf_avail = MZ_MIN(read_buf_سائز, comp_بقایا);
        اگر (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
        {
          حالت_2 = TINFL_حالت_FAILED;
          توڑو;
        }

        اگر (!(flags & MZ_ZIP_FLAG_COMPRESSED_ڈیٹا))
          file_چکری_جانچ_32 = (mz_uint32)mz_چکری_جانچ_32(file_چکری_جانچ_32, (ثابت mz_uint8 *)pRead_buf, (size_t)read_buf_avail);

        اگر (pCallback(pOpaque, برآمد_buf_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
        {
          حالت_2 = TINFL_حالت_FAILED;
          توڑو;
        }
        cur_file_ofs += read_buf_avail;
        برآمد_buf_ofs += read_buf_avail;
        comp_بقایا -= read_buf_avail;
      }
    }
  }
  ورنہ
  {
    tinfl_decompressor inflator;
    tinfl_init(&inflator);

    اگر (تہی == (pWrite_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, TINFL_LZ_DICT_سائز)))
      حالت_2 = TINFL_حالت_FAILED;
    ورنہ
    {
      کرو
      {
        mz_uint8 *pWrite_buf_cur = (mz_uint8 *)pWrite_buf + (برآمد_buf_ofs & (TINFL_LZ_DICT_سائز - 1));
        size_t اندر_buf_سائز, برآمد_buf_سائز = TINFL_LZ_DICT_سائز - (برآمد_buf_ofs & (TINFL_LZ_DICT_سائز - 1));
        اگر ((!read_buf_avail) && (!pZip->m_pState->m_pMem))
        {
          read_buf_avail = MZ_MIN(read_buf_سائز, comp_بقایا);
          اگر (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
          {
            حالت_2 = TINFL_حالت_FAILED;
            توڑو;
          }
          cur_file_ofs += read_buf_avail;
          comp_بقایا -= read_buf_avail;
          read_buf_ofs = 0;
        }

        اندر_buf_سائز = (size_t)read_buf_avail;
        حالت_2 = tinfl_decompress(&inflator, (ثابت mz_uint8 *)pRead_buf + read_buf_ofs, &اندر_buf_سائز, (mz_uint8 *)pWrite_buf, pWrite_buf_cur, &برآمد_buf_سائز, comp_بقایا ? TINFL_FLAG_HAS_مزید_داخلہ : 0);
        read_buf_avail -= اندر_buf_سائز;
        read_buf_ofs += اندر_buf_سائز;

        اگر (برآمد_buf_سائز)
        {
          اگر (pCallback(pOpaque, برآمد_buf_ofs, pWrite_buf_cur, برآمد_buf_سائز) != برآمد_buf_سائز)
          {
            حالت_2 = TINFL_حالت_FAILED;
            توڑو;
          }
          file_چکری_جانچ_32 = (mz_uint32)mz_چکری_جانچ_32(file_چکری_جانچ_32, pWrite_buf_cur, برآمد_buf_سائز);
          اگر ((برآمد_buf_ofs += برآمد_buf_سائز) > file_stat.m_uncomp_سائز)
          {
            حالت_2 = TINFL_حالت_FAILED;
            توڑو;
          }
        }
      } جب ((حالت_2 == TINFL_حالت_NEEDS_مزید_داخلہ) || (حالت_2 == TINFL_حالت_HAS_مزید_OUTPUT));
    }
  }

  اگر ((حالت_2 == TINFL_حالت_مکمل) && (!(flags & MZ_ZIP_FLAG_COMPRESSED_ڈیٹا)))
  {
    // Make sure the entire file was decompressed, and check its CRC.
    اگر ((برآمد_buf_ofs != file_stat.m_uncomp_سائز) || (file_چکری_جانچ_32 != file_stat.m_چکری_جانچ_32))
      حالت_2 = TINFL_حالت_FAILED;
  }

  اگر (!pZip->m_pState->m_pMem)
    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
  اگر (pWrite_buf)
    pZip->m_pFree(pZip->m_pAlloc_opaque, pWrite_buf);

  واپس حالت_2 == TINFL_حالت_مکمل;
}

mz_bool mz_zip_reader_نکالو_file_مقصد_callback(mz_zip_archive *pZip, ثابت حرف *pFilename, mz_file_write_func pCallback, خالی *pOpaque, mz_uint flags)
{
  صحیح file_اشاریہ = mz_zip_reader_locate_file(pZip, pFilename, تہی, flags);
  اگر (file_اشاریہ < 0)
    واپس MZ_FALSE;
  واپس mz_zip_reader_نکالو_مقصد_callback(pZip, file_اشاریہ, pCallback, pOpaque, flags);
}

#اگر_غیر_تعریف_شدہ MINIZ_NO_STDIO
ساکن size_t mz_zip_file_write_callback(خالی *pOpaque, mz_uint64 ofs, ثابت خالی *pBuf, size_t n)
{
  (خالی)ofs; واپس MZ_FWRITE(pBuf, 1, n, (MZ_FILE*)pOpaque);
}

mz_bool mz_zip_reader_نکالو_مقصد_file(mz_zip_archive *pZip, mz_uint file_اشاریہ, ثابت حرف *pDst_filename, mz_uint flags)
{
  mz_bool حالت_2;
  mz_zip_archive_file_stat file_stat;
  MZ_FILE *pFile;
  اگر (!mz_zip_reader_file_stat(pZip, file_اشاریہ, &file_stat))
    واپس MZ_FALSE;
  pFile = MZ_FOPEN(pDst_filename, "wb");
  اگر (!pFile)
    واپس MZ_FALSE;
  حالت_2 = mz_zip_reader_نکالو_مقصد_callback(pZip, file_اشاریہ, mz_zip_file_write_callback, pFile, flags);
  اگر (MZ_FCLOSE(pFile) == EOF)
    واپس MZ_FALSE;
#اگر_غیر_تعریف_شدہ MINIZ_NO_وقت
  اگر (حالت_2)
    mz_zip_سیٹ_file_times(pDst_filename, file_stat.m_وقت, file_stat.m_وقت);
#اگر_ختم
  واپس حالت_2;
}
#اگر_ختم // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_reader_انتہا(mz_zip_archive *pZip)
{
  اگر ((!pZip) || (!pZip->m_pState) || (!pZip->m_pAlloc) || (!pZip->m_pFree) || (pZip->m_zip_منوال != MZ_ZIP_منوال_READING))
    واپس MZ_FALSE;

  اگر (pZip->m_pState)
  {
    mz_zip_اندرونی_state *pState = pZip->m_pState; pZip->m_pState = تہی;
    mz_zip_array_clear(pZip, &pState->m_central_dir);
    mz_zip_array_clear(pZip, &pState->m_central_dir_offsets);
    mz_zip_array_clear(pZip, &pState->m_sorted_central_dir_offsets);

#اگر_غیر_تعریف_شدہ MINIZ_NO_STDIO
    اگر (pState->m_pFile)
    {
      MZ_FCLOSE(pState->m_pFile);
      pState->m_pFile = تہی;
    }
#اگر_ختم // #ifndef MINIZ_NO_STDIO

    pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
  }
  pZip->m_zip_منوال = MZ_ZIP_منوال_INVALID;

  واپس MZ_TRUE;
}

#اگر_غیر_تعریف_شدہ MINIZ_NO_STDIO
mz_bool mz_zip_reader_نکالو_file_مقصد_file(mz_zip_archive *pZip, ثابت حرف *pArchive_filename, ثابت حرف *pDst_filename, mz_uint flags)
{
  صحیح file_اشاریہ = mz_zip_reader_locate_file(pZip, pArchive_filename, تہی, flags);
  اگر (file_اشاریہ < 0)
    واپس MZ_FALSE;
  واپس mz_zip_reader_نکالو_مقصد_file(pZip, file_اشاریہ, pDst_filename, flags);
}
#اگر_ختم

// ------------------- .ZIP archive writing

#اگر_غیر_تعریف_شدہ MINIZ_NO_ARCHIVE_WRITING_APIS

ساکن خالی mz_write_le16(mz_uint8 *p, mz_uint16 v) { p[0] = (mz_uint8)v; p[1] = (mz_uint8)(v >> 8); }
ساکن خالی mz_write_le32(mz_uint8 *p, mz_uint32 v) { p[0] = (mz_uint8)v; p[1] = (mz_uint8)(v >> 8); p[2] = (mz_uint8)(v >> 16); p[3] = (mz_uint8)(v >> 24); }
#تعریف_کرو MZ_WRITE_LE16(p, v) mz_write_le16((mz_uint8 *)(p), (mz_uint16)(v))
#تعریف_کرو MZ_WRITE_LE32(p, v) mz_write_le32((mz_uint8 *)(p), (mz_uint32)(v))

mz_bool mz_zip_writer_init(mz_zip_archive *pZip, mz_uint64 existing_سائز)
{
  اگر ((!pZip) || (pZip->m_pState) || (!pZip->m_pWrite) || (pZip->m_zip_منوال != MZ_ZIP_منوال_INVALID))
    واپس MZ_FALSE;

  اگر (pZip->m_file_انحراف_alignment)
  {
    // Ensure user specified file offset alignment is a power of 2.
    اگر (pZip->m_file_انحراف_alignment & (pZip->m_file_انحراف_alignment - 1))
      واپس MZ_FALSE;
  }

  اگر (!pZip->m_pAlloc) pZip->m_pAlloc = def_alloc_func;
  اگر (!pZip->m_pFree) pZip->m_pFree = def_free_func;
  اگر (!pZip->m_pRealloc) pZip->m_pRealloc = def_realloc_func;

  pZip->m_zip_منوال = MZ_ZIP_منوال_WRITING;
  pZip->m_archive_سائز = existing_سائز;
  pZip->m_central_directory_file_ofs = 0;
  pZip->m_کل_files = 0;

  اگر (تہی == (pZip->m_pState = (mz_zip_اندرونی_state *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, حجم(mz_zip_اندرونی_state))))
    واپس MZ_FALSE;
  memset(pZip->m_pState, 0, حجم(mz_zip_اندرونی_state));
  MZ_ZIP_ARRAY_سیٹ_ELEMENT_سائز(&pZip->m_pState->m_central_dir, حجم(mz_uint8));
  MZ_ZIP_ARRAY_سیٹ_ELEMENT_سائز(&pZip->m_pState->m_central_dir_offsets, حجم(mz_uint32));
  MZ_ZIP_ARRAY_سیٹ_ELEMENT_سائز(&pZip->m_pState->m_sorted_central_dir_offsets, حجم(mz_uint32));
  واپس MZ_TRUE;
}

ساکن size_t mz_zip_ڈھیر_write_func(خالی *pOpaque, mz_uint64 file_ofs, ثابت خالی *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_zip_اندرونی_state *pState = pZip->m_pState;
  mz_uint64 new_سائز = MZ_MAX(file_ofs + n, pState->m_mem_سائز);
#اگر_تعریف_شدہ _MSC_VER
  اگر ((!n) || ((0, حجم(size_t) == حجم(mz_uint32)) && (new_سائز > 0x7FFFFFFF)))
#ورنہ
  اگر ((!n) || ((حجم(size_t) == حجم(mz_uint32)) && (new_سائز > 0x7FFFFFFF)))
#اگر_ختم
    واپس 0;
  اگر (new_سائز > pState->m_mem_استعداد)
  {
    خالی *p_New_بلاک;
    size_t new_استعداد = MZ_MAX(64, pState->m_mem_استعداد); جب (new_استعداد < new_سائز) new_استعداد *= 2;
    اگر (تہی == (p_New_بلاک = pZip->m_pRealloc(pZip->m_pAlloc_opaque, pState->m_pMem, 1, new_استعداد)))
      واپس 0;
    pState->m_pMem = p_New_بلاک; pState->m_mem_استعداد = new_استعداد;
  }
  حافظہ_نقل((mz_uint8 *)pState->m_pMem + file_ofs, pBuf, n);
  pState->m_mem_سائز = (size_t)new_سائز;
  واپس n;
}

mz_bool mz_zip_writer_init_ڈھیر(mz_zip_archive *pZip, size_t سائز_مقصد_reserve_at_beginning, size_t initial_تخصیص_سائز)
{
  pZip->m_pWrite = mz_zip_ڈھیر_write_func;
  pZip->m_pIO_opaque = pZip;
  اگر (!mz_zip_writer_init(pZip, سائز_مقصد_reserve_at_beginning))
    واپس MZ_FALSE;
  اگر (0 != (initial_تخصیص_سائز = MZ_MAX(initial_تخصیص_سائز, سائز_مقصد_reserve_at_beginning)))
  {
    اگر (تہی == (pZip->m_pState->m_pMem = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, initial_تخصیص_سائز)))
    {
      mz_zip_writer_انتہا(pZip);
      واپس MZ_FALSE;
    }
    pZip->m_pState->m_mem_استعداد = initial_تخصیص_سائز;
  }
  واپس MZ_TRUE;
}

#اگر_غیر_تعریف_شدہ MINIZ_NO_STDIO
ساکن size_t mz_zip_file_write_func(خالی *pOpaque, mz_uint64 file_ofs, ثابت خالی *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_int64 cur_ofs = MZ_FTELL64(pZip->m_pState->m_pFile);
  اگر (((mz_int64)file_ofs < 0) || (((cur_ofs != (mz_int64)file_ofs)) && (MZ_FSEEK64(pZip->m_pState->m_pFile, (mz_int64)file_ofs, SEEK_SET))))
    واپس 0;
  واپس MZ_FWRITE(pBuf, 1, n, pZip->m_pState->m_pFile);
}

mz_bool mz_zip_writer_init_file(mz_zip_archive *pZip, ثابت حرف *pFilename, mz_uint64 سائز_مقصد_reserve_at_beginning)
{
  MZ_FILE *pFile;
  pZip->m_pWrite = mz_zip_file_write_func;
  pZip->m_pIO_opaque = pZip;
  اگر (!mz_zip_writer_init(pZip, سائز_مقصد_reserve_at_beginning))
    واپس MZ_FALSE;
  اگر (تہی == (pFile = MZ_FOPEN(pFilename, "wb")))
  {
    mz_zip_writer_انتہا(pZip);
    واپس MZ_FALSE;
  }
  pZip->m_pState->m_pFile = pFile;
  اگر (سائز_مقصد_reserve_at_beginning)
  {
    mz_uint64 cur_ofs = 0; حرف buf[4096]; MZ_CLEAR_ARR(buf);
    کرو
    {
      size_t n = (size_t)MZ_MIN(حجم(buf), سائز_مقصد_reserve_at_beginning);
      اگر (pZip->m_pWrite(pZip->m_pIO_opaque, cur_ofs, buf, n) != n)
      {
        mz_zip_writer_انتہا(pZip);
        واپس MZ_FALSE;
      }
      cur_ofs += n; سائز_مقصد_reserve_at_beginning -= n;
    } جب (سائز_مقصد_reserve_at_beginning);
  }
  واپس MZ_TRUE;
}
#اگر_ختم // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_writer_init_from_reader(mz_zip_archive *pZip, ثابت حرف *pFilename)
{
  mz_zip_اندرونی_state *pState;
  اگر ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_منوال != MZ_ZIP_منوال_READING))
    واپس MZ_FALSE;
  // No sense in trying to write to an archive that's already at the support max size
  اگر ((pZip->m_کل_files == 0xFFFF) || ((pZip->m_archive_سائز + MZ_ZIP_CENTRAL_DIR_سرخی_سائز + MZ_ZIP_LOCAL_DIR_سرخی_سائز) > 0xFFFFFFFF))
    واپس MZ_FALSE;

  pState = pZip->m_pState;

  اگر (pState->m_pFile)
  {
#اگر_تعریف_شدہ MINIZ_NO_STDIO
    pFilename; واپس MZ_FALSE;
#ورنہ
    // Archive is being read from stdio - try to reopen as writable.
    اگر (pZip->m_pIO_opaque != pZip)
      واپس MZ_FALSE;
    اگر (!pFilename)
      واپس MZ_FALSE;
    pZip->m_pWrite = mz_zip_file_write_func;
    اگر (تہی == (pState->m_pFile = MZ_FREOPEN(pFilename, "r+b", pState->m_pFile)))
    {
      // The mz_zip_archive is now in a bogus state because pState->m_pFile is NULL, so just close it.
      mz_zip_reader_انتہا(pZip);
      واپس MZ_FALSE;
    }
#اگر_ختم // #ifdef MINIZ_NO_STDIO
  }
  ورنہ اگر (pState->m_pMem)
  {
    // Archive lives in a memory block. Assume it's from the heap that we can resize using the realloc callback.
    اگر (pZip->m_pIO_opaque != pZip)
      واپس MZ_FALSE;
    pState->m_mem_استعداد = pState->m_mem_سائز;
    pZip->m_pWrite = mz_zip_ڈھیر_write_func;
  }
  // Archive is being read via a user provided read function - make sure the user has specified a write function too.
  ورنہ اگر (!pZip->m_pWrite)
    واپس MZ_FALSE;

  // Start writing new files at the archive's current central directory location.
  pZip->m_archive_سائز = pZip->m_central_directory_file_ofs;
  pZip->m_zip_منوال = MZ_ZIP_منوال_WRITING;
  pZip->m_central_directory_file_ofs = 0;

  واپس MZ_TRUE;
}

mz_bool mz_zip_writer_جوڑو_mem(mz_zip_archive *pZip, ثابت حرف *pArchive_name, ثابت خالی *pBuf, size_t buf_سائز_2, mz_uint level_and_flags)
{
  واپس mz_zip_writer_جوڑو_mem_ex(pZip, pArchive_name, pBuf, buf_سائز_2, تہی, 0, level_and_flags, 0, 0);
}

قسمتعریف ساخت
{
  mz_zip_archive *m_pZip;
  mz_uint64 m_cur_archive_file_ofs;
  mz_uint64 m_comp_سائز;
} mz_zip_writer_جوڑو_state;

ساکن mz_bool mz_zip_writer_جوڑو_put_buf_callback(ثابت خالی* pBuf, صحیح len, خالی *pUser)
{
  mz_zip_writer_جوڑو_state *pState = (mz_zip_writer_جوڑو_state *)pUser;
  اگر ((صحیح)pState->m_pZip->m_pWrite(pState->m_pZip->m_pIO_opaque, pState->m_cur_archive_file_ofs, pBuf, len) != len)
    واپس MZ_FALSE;
  pState->m_cur_archive_file_ofs += len;
  pState->m_comp_سائز += len;
  واپس MZ_TRUE;
}

ساکن mz_bool mz_zip_writer_create_local_dir_سرخی(mz_zip_archive *pZip, mz_uint8 *pDst, mz_uint16 filename_سائز, mz_uint16 extra_سائز, mz_uint64 uncomp_سائز, mz_uint64 comp_سائز, mz_uint32 uncomp_چکری_جانچ_32, mz_uint16 طریقہ, mz_uint16 ثنائی_ہندسہ_flags, mz_uint16 dos_وقت, mz_uint16 dos_date)
{
  (خالی)pZip;
  memset(pDst, 0, MZ_ZIP_LOCAL_DIR_سرخی_سائز);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_SIG_OFS, MZ_ZIP_LOCAL_DIR_سرخی_SIG);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_نسخہ_NEEDED_OFS, طریقہ ? 20 : 0);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_ثنائی_ہندسہ_FLAG_OFS, ثنائی_ہندسہ_flags);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_طریقہ_OFS, طریقہ);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILE_وقت_OFS, dos_وقت);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILE_DATE_OFS, dos_date);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_چکری_جانچ_32_OFS, uncomp_چکری_جانچ_32);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_COMPRESSED_سائز_OFS, comp_سائز);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_DECOMPRESSED_سائز_OFS, uncomp_سائز);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILENAME_LEN_OFS, filename_سائز);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_EXTRA_LEN_OFS, extra_سائز);
  واپس MZ_TRUE;
}

ساکن mz_bool mz_zip_writer_create_central_dir_سرخی(mz_zip_archive *pZip, mz_uint8 *pDst, mz_uint16 filename_سائز, mz_uint16 extra_سائز, mz_uint16 comment_سائز, mz_uint64 uncomp_سائز, mz_uint64 comp_سائز, mz_uint32 uncomp_چکری_جانچ_32, mz_uint16 طریقہ, mz_uint16 ثنائی_ہندسہ_flags, mz_uint16 dos_وقت, mz_uint16 dos_date, mz_uint64 local_سرخی_ofs, mz_uint32 ext_اوصاف)
{
  (خالی)pZip;
  memset(pDst, 0, MZ_ZIP_CENTRAL_DIR_سرخی_سائز);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_SIG_OFS, MZ_ZIP_CENTRAL_DIR_سرخی_SIG);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_نسخہ_NEEDED_OFS, طریقہ ? 20 : 0);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_ثنائی_ہندسہ_FLAG_OFS, ثنائی_ہندسہ_flags);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_طریقہ_OFS, طریقہ);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILE_وقت_OFS, dos_وقت);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILE_DATE_OFS, dos_date);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_چکری_جانچ_32_OFS, uncomp_چکری_جانچ_32);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_COMPRESSED_سائز_OFS, comp_سائز);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_DECOMPRESSED_سائز_OFS, uncomp_سائز);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILENAME_LEN_OFS, filename_سائز);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_EXTRA_LEN_OFS, extra_سائز);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_COMMENT_LEN_OFS, comment_سائز);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS, ext_اوصاف);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_LOCAL_سرخی_OFS, local_سرخی_ofs);
  واپس MZ_TRUE;
}

ساکن mz_bool mz_zip_writer_جوڑو_مقصد_central_dir(mz_zip_archive *pZip, ثابت حرف *pFilename, mz_uint16 filename_سائز, ثابت خالی *pExtra, mz_uint16 extra_سائز, ثابت خالی *pComment, mz_uint16 comment_سائز, mz_uint64 uncomp_سائز, mz_uint64 comp_سائز, mz_uint32 uncomp_چکری_جانچ_32, mz_uint16 طریقہ, mz_uint16 ثنائی_ہندسہ_flags, mz_uint16 dos_وقت, mz_uint16 dos_date, mz_uint64 local_سرخی_ofs, mz_uint32 ext_اوصاف)
{
  mz_zip_اندرونی_state *pState = pZip->m_pState;
  mz_uint32 central_dir_ofs = (mz_uint32)pState->m_central_dir.m_سائز;
  size_t orig_central_dir_سائز = pState->m_central_dir.m_سائز;
  mz_uint8 central_dir_سرخی[MZ_ZIP_CENTRAL_DIR_سرخی_سائز];

  // No zip64 support yet
  اگر ((local_سرخی_ofs > 0xFFFFFFFF) || (((mz_uint64)pState->m_central_dir.m_سائز + MZ_ZIP_CENTRAL_DIR_سرخی_سائز + filename_سائز + extra_سائز + comment_سائز) > 0xFFFFFFFF))
    واپس MZ_FALSE;

  اگر (!mz_zip_writer_create_central_dir_سرخی(pZip, central_dir_سرخی, filename_سائز, extra_سائز, comment_سائز, uncomp_سائز, comp_سائز, uncomp_چکری_جانچ_32, طریقہ, ثنائی_ہندسہ_flags, dos_وقت, dos_date, local_سرخی_ofs, ext_اوصاف))
    واپس MZ_FALSE;

  اگر ((!mz_zip_array_ڈالو_عقب(pZip, &pState->m_central_dir, central_dir_سرخی, MZ_ZIP_CENTRAL_DIR_سرخی_سائز)) ||
      (!mz_zip_array_ڈالو_عقب(pZip, &pState->m_central_dir, pFilename, filename_سائز)) ||
      (!mz_zip_array_ڈالو_عقب(pZip, &pState->m_central_dir, pExtra, extra_سائز)) ||
      (!mz_zip_array_ڈالو_عقب(pZip, &pState->m_central_dir, pComment, comment_سائز)) ||
      (!mz_zip_array_ڈالو_عقب(pZip, &pState->m_central_dir_offsets, &central_dir_ofs, 1)))
  {
    // Try to push the central directory array back into its original state.
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_سائز, MZ_FALSE);
    واپس MZ_FALSE;
  }

  واپس MZ_TRUE;
}

ساکن mz_bool mz_zip_writer_validate_archive_name(ثابت حرف *pArchive_name)
{
  // Basic ZIP archive filename validity checks: Valid filenames cannot start with a forward slash, cannot contain a drive letter, and cannot use DOS-style backward slashes.
  اگر (*pArchive_name == '/')
    واپس MZ_FALSE;
  جب (*pArchive_name)
  {
    اگر ((*pArchive_name == '\\') || (*pArchive_name == ':'))
      واپس MZ_FALSE;
    pArchive_name++;
  }
  واپس MZ_TRUE;
}

ساکن mz_uint mz_zip_writer_compute_padding_needed_for_file_alignment(mz_zip_archive *pZip)
{
  mz_uint32 n;
  اگر (!pZip->m_file_انحراف_alignment)
    واپس 0;
  n = (mz_uint32)(pZip->m_archive_سائز & (pZip->m_file_انحراف_alignment - 1));
  واپس (pZip->m_file_انحراف_alignment - n) & (pZip->m_file_انحراف_alignment - 1);
}

ساکن mz_bool mz_zip_writer_write_zeros(mz_zip_archive *pZip, mz_uint64 cur_file_ofs, mz_uint32 n)
{
  حرف buf[4096];
  memset(buf, 0, MZ_MIN(حجم(buf), n));
  جب (n)
  {
    mz_uint32 s = MZ_MIN(حجم(buf), n);
    اگر (pZip->m_pWrite(pZip->m_pIO_opaque, cur_file_ofs, buf, s) != s)
      واپس MZ_FALSE;
    cur_file_ofs += s; n -= s;
  }
  واپس MZ_TRUE;
}

mz_bool mz_zip_writer_جوڑو_mem_ex(mz_zip_archive *pZip, ثابت حرف *pArchive_name, ثابت خالی *pBuf, size_t buf_سائز_2, ثابت خالی *pComment, mz_uint16 comment_سائز, mz_uint level_and_flags, mz_uint64 uncomp_سائز, mz_uint32 uncomp_چکری_جانچ_32)
{
  mz_uint16 طریقہ = 0, dos_وقت = 0, dos_date = 0;
  mz_uint level, ext_اوصاف = 0, عدد_alignment_padding_بائٹیں;
  mz_uint64 local_dir_سرخی_ofs = pZip->m_archive_سائز, cur_archive_file_ofs = pZip->m_archive_سائز, comp_سائز = 0;
  size_t archive_name_سائز;
  mz_uint8 local_dir_سرخی[MZ_ZIP_LOCAL_DIR_سرخی_سائز];
  tdefl_compressor *pComp = تہی;
  mz_bool store_ڈیٹا_uncompressed;
  mz_zip_اندرونی_state *pState;

  اگر ((صحیح)level_and_flags < 0)
    level_and_flags = MZ_DEFAULT_LEVEL;
  level = level_and_flags & 0xF;
  store_ڈیٹا_uncompressed = ((!level) || (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_ڈیٹا));

  اگر ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_منوال != MZ_ZIP_منوال_WRITING) || ((buf_سائز_2) && (!pBuf)) || (!pArchive_name) || ((comment_سائز) && (!pComment)) || (pZip->m_کل_files == 0xFFFF) || (level > MZ_UBER_COMPRESSION))
    واپس MZ_FALSE;

  pState = pZip->m_pState;

  اگر ((!(level_and_flags & MZ_ZIP_FLAG_COMPRESSED_ڈیٹا)) && (uncomp_سائز))
    واپس MZ_FALSE;
  // No zip64 support yet
  اگر ((buf_سائز_2 > 0xFFFFFFFF) || (uncomp_سائز > 0xFFFFFFFF))
    واپس MZ_FALSE;
  اگر (!mz_zip_writer_validate_archive_name(pArchive_name))
    واپس MZ_FALSE;

#اگر_غیر_تعریف_شدہ MINIZ_NO_وقت
  {
    وقت_t cur_وقت; وقت(&cur_وقت);
    mz_zip_وقت_مقصد_dos_وقت(cur_وقت, &dos_وقت, &dos_date);
  }
#اگر_ختم // #ifndef MINIZ_NO_TIME

  archive_name_سائز = لڑی_لمبائی(pArchive_name);
  اگر (archive_name_سائز > 0xFFFF)
    واپس MZ_FALSE;

  عدد_alignment_padding_بائٹیں = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  اگر ((pZip->m_کل_files == 0xFFFF) || ((pZip->m_archive_سائز + عدد_alignment_padding_بائٹیں + MZ_ZIP_LOCAL_DIR_سرخی_سائز + MZ_ZIP_CENTRAL_DIR_سرخی_سائز + comment_سائز + archive_name_سائز) > 0xFFFFFFFF))
    واپس MZ_FALSE;

  اگر ((archive_name_سائز) && (pArchive_name[archive_name_سائز - 1] == '/'))
  {
    // Set DOS Subdirectory attribute bit.
    ext_اوصاف |= 0x10;
    // Subdirectories cannot contain data.
    اگر ((buf_سائز_2) || (uncomp_سائز))
      واپس MZ_FALSE;
  }

  // Try to do any allocations before writing to the archive, so if an allocation fails the file remains unmodified. (A good idea if we're doing an in-place modification.)
  اگر ((!mz_zip_array_ensure_گنجائش(pZip, &pState->m_central_dir, MZ_ZIP_CENTRAL_DIR_سرخی_سائز + archive_name_سائز + comment_سائز)) || (!mz_zip_array_ensure_گنجائش(pZip, &pState->m_central_dir_offsets, 1)))
    واپس MZ_FALSE;

  اگر ((!store_ڈیٹا_uncompressed) && (buf_سائز_2))
  {
    اگر (تہی == (pComp = (tdefl_compressor *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, حجم(tdefl_compressor))))
      واپس MZ_FALSE;
  }

  اگر (!mz_zip_writer_write_zeros(pZip, cur_archive_file_ofs, عدد_alignment_padding_بائٹیں + حجم(local_dir_سرخی)))
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
    واپس MZ_FALSE;
  }
  local_dir_سرخی_ofs += عدد_alignment_padding_بائٹیں;
  اگر (pZip->m_file_انحراف_alignment) { MZ_ASSERT((local_dir_سرخی_ofs & (pZip->m_file_انحراف_alignment - 1)) == 0); }
  cur_archive_file_ofs += عدد_alignment_padding_بائٹیں + حجم(local_dir_سرخی);

  MZ_CLEAR_ARR(local_dir_سرخی);
  اگر (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pArchive_name, archive_name_سائز) != archive_name_سائز)
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
    واپس MZ_FALSE;
  }
  cur_archive_file_ofs += archive_name_سائز;

  اگر (!(level_and_flags & MZ_ZIP_FLAG_COMPRESSED_ڈیٹا))
  {
    uncomp_چکری_جانچ_32 = (mz_uint32)mz_چکری_جانچ_32(MZ_چکری_جانچ_32_INIT, (ثابت mz_uint8*)pBuf, buf_سائز_2);
    uncomp_سائز = buf_سائز_2;
    اگر (uncomp_سائز <= 3)
    {
      level = 0;
      store_ڈیٹا_uncompressed = MZ_TRUE;
    }
  }

  اگر (store_ڈیٹا_uncompressed)
  {
    اگر (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pBuf, buf_سائز_2) != buf_سائز_2)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
      واپس MZ_FALSE;
    }

    cur_archive_file_ofs += buf_سائز_2;
    comp_سائز = buf_سائز_2;

    اگر (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_ڈیٹا)
      طریقہ = MZ_DEFLATED;
  }
  ورنہ اگر (buf_سائز_2)
  {
    mz_zip_writer_جوڑو_state state;

    state.m_pZip = pZip;
    state.m_cur_archive_file_ofs = cur_archive_file_ofs;
    state.m_comp_سائز = 0;

    اگر ((tdefl_init(pComp, mz_zip_writer_جوڑو_put_buf_callback, &state, tdefl_create_comp_flags_from_zip_params(level, -15, MZ_DEFAULT_STRATEGY)) != TDEFL_حالت_OKAY) ||
        (tdefl_compress_بفر(pComp, pBuf, buf_سائز_2, TDEFL_اختتام) != TDEFL_حالت_مکمل))
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
      واپس MZ_FALSE;
    }

    comp_سائز = state.m_comp_سائز;
    cur_archive_file_ofs = state.m_cur_archive_file_ofs;

    طریقہ = MZ_DEFLATED;
  }

  pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
  pComp = تہی;

  // no zip64 support yet
  اگر ((comp_سائز > 0xFFFFFFFF) || (cur_archive_file_ofs > 0xFFFFFFFF))
    واپس MZ_FALSE;

  اگر (!mz_zip_writer_create_local_dir_سرخی(pZip, local_dir_سرخی, (mz_uint16)archive_name_سائز, 0, uncomp_سائز, comp_سائز, uncomp_چکری_جانچ_32, طریقہ, 0, dos_وقت, dos_date))
    واپس MZ_FALSE;

  اگر (pZip->m_pWrite(pZip->m_pIO_opaque, local_dir_سرخی_ofs, local_dir_سرخی, حجم(local_dir_سرخی)) != حجم(local_dir_سرخی))
    واپس MZ_FALSE;

  اگر (!mz_zip_writer_جوڑو_مقصد_central_dir(pZip, pArchive_name, (mz_uint16)archive_name_سائز, تہی, 0, pComment, comment_سائز, uncomp_سائز, comp_سائز, uncomp_چکری_جانچ_32, طریقہ, 0, dos_وقت, dos_date, local_dir_سرخی_ofs, ext_اوصاف))
    واپس MZ_FALSE;

  pZip->m_کل_files++;
  pZip->m_archive_سائز = cur_archive_file_ofs;

  واپس MZ_TRUE;
}

#اگر_غیر_تعریف_شدہ MINIZ_NO_STDIO
mz_bool mz_zip_writer_جوڑو_file(mz_zip_archive *pZip, ثابت حرف *pArchive_name, ثابت حرف *pSrc_filename, ثابت خالی *pComment, mz_uint16 comment_سائز, mz_uint level_and_flags)
{
  mz_uint uncomp_چکری_جانچ_32 = MZ_چکری_جانچ_32_INIT, level, عدد_alignment_padding_بائٹیں;
  mz_uint16 طریقہ = 0, dos_وقت = 0, dos_date = 0, ext_اوصاف = 0;
  mz_uint64 local_dir_سرخی_ofs = pZip->m_archive_سائز, cur_archive_file_ofs = pZip->m_archive_سائز, uncomp_سائز = 0, comp_سائز = 0;
  size_t archive_name_سائز;
  mz_uint8 local_dir_سرخی[MZ_ZIP_LOCAL_DIR_سرخی_سائز];
  MZ_FILE *pSrc_file = تہی;

  اگر ((صحیح)level_and_flags < 0)
    level_and_flags = MZ_DEFAULT_LEVEL;
  level = level_and_flags & 0xF;

  اگر ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_منوال != MZ_ZIP_منوال_WRITING) || (!pArchive_name) || ((comment_سائز) && (!pComment)) || (level > MZ_UBER_COMPRESSION))
    واپس MZ_FALSE;
  اگر (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_ڈیٹا)
    واپس MZ_FALSE;
  اگر (!mz_zip_writer_validate_archive_name(pArchive_name))
    واپس MZ_FALSE;

  archive_name_سائز = لڑی_لمبائی(pArchive_name);
  اگر (archive_name_سائز > 0xFFFF)
    واپس MZ_FALSE;

  عدد_alignment_padding_بائٹیں = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  اگر ((pZip->m_کل_files == 0xFFFF) || ((pZip->m_archive_سائز + عدد_alignment_padding_بائٹیں + MZ_ZIP_LOCAL_DIR_سرخی_سائز + MZ_ZIP_CENTRAL_DIR_سرخی_سائز + comment_سائز + archive_name_سائز) > 0xFFFFFFFF))
    واپس MZ_FALSE;

  اگر (!mz_zip_get_file_modified_وقت(pSrc_filename, &dos_وقت, &dos_date))
    واپس MZ_FALSE;

  pSrc_file = MZ_FOPEN(pSrc_filename, "rb");
  اگر (!pSrc_file)
    واپس MZ_FALSE;
  MZ_FSEEK64(pSrc_file, 0, SEEK_END);
  uncomp_سائز = MZ_FTELL64(pSrc_file);
  MZ_FSEEK64(pSrc_file, 0, SEEK_SET);

  اگر (uncomp_سائز > 0xFFFFFFFF)
  {
    // No zip64 support yet
    MZ_FCLOSE(pSrc_file);
    واپس MZ_FALSE;
  }
  اگر (uncomp_سائز <= 3)
    level = 0;

  اگر (!mz_zip_writer_write_zeros(pZip, cur_archive_file_ofs, عدد_alignment_padding_بائٹیں + حجم(local_dir_سرخی)))
  {
    MZ_FCLOSE(pSrc_file);
    واپس MZ_FALSE;
  }
  local_dir_سرخی_ofs += عدد_alignment_padding_بائٹیں;
  اگر (pZip->m_file_انحراف_alignment) { MZ_ASSERT((local_dir_سرخی_ofs & (pZip->m_file_انحراف_alignment - 1)) == 0); }
  cur_archive_file_ofs += عدد_alignment_padding_بائٹیں + حجم(local_dir_سرخی);

  MZ_CLEAR_ARR(local_dir_سرخی);
  اگر (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pArchive_name, archive_name_سائز) != archive_name_سائز)
  {
    MZ_FCLOSE(pSrc_file);
    واپس MZ_FALSE;
  }
  cur_archive_file_ofs += archive_name_سائز;

  اگر (uncomp_سائز)
  {
    mz_uint64 uncomp_بقایا = uncomp_سائز;
    خالی *pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, MZ_ZIP_MAX_IO_BUF_سائز);
    اگر (!pRead_buf)
    {
      MZ_FCLOSE(pSrc_file);
      واپس MZ_FALSE;
    }

    اگر (!level)
    {
      جب (uncomp_بقایا)
      {
        mz_uint n = (mz_uint)MZ_MIN(MZ_ZIP_MAX_IO_BUF_سائز, uncomp_بقایا);
        اگر ((MZ_FREAD(pRead_buf, 1, n, pSrc_file) != n) || (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pRead_buf, n) != n))
        {
          pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
          MZ_FCLOSE(pSrc_file);
          واپس MZ_FALSE;
        }
        uncomp_چکری_جانچ_32 = (mz_uint32)mz_چکری_جانچ_32(uncomp_چکری_جانچ_32, (ثابت mz_uint8 *)pRead_buf, n);
        uncomp_بقایا -= n;
        cur_archive_file_ofs += n;
      }
      comp_سائز = uncomp_سائز;
    }
    ورنہ
    {
      mz_bool نتیجہ = MZ_FALSE;
      mz_zip_writer_جوڑو_state state;
      tdefl_compressor *pComp = (tdefl_compressor *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, حجم(tdefl_compressor));
      اگر (!pComp)
      {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        واپس MZ_FALSE;
      }

      state.m_pZip = pZip;
      state.m_cur_archive_file_ofs = cur_archive_file_ofs;
      state.m_comp_سائز = 0;

      اگر (tdefl_init(pComp, mz_zip_writer_جوڑو_put_buf_callback, &state, tdefl_create_comp_flags_from_zip_params(level, -15, MZ_DEFAULT_STRATEGY)) != TDEFL_حالت_OKAY)
      {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        واپس MZ_FALSE;
      }

      برائے ( ; ; )
      {
        size_t اندر_buf_سائز = (mz_uint32)MZ_MIN(uncomp_بقایا, MZ_ZIP_MAX_IO_BUF_سائز);
        tdefl_حالت حالت_2;

        اگر (MZ_FREAD(pRead_buf, 1, اندر_buf_سائز, pSrc_file) != اندر_buf_سائز)
          توڑو;

        uncomp_چکری_جانچ_32 = (mz_uint32)mz_چکری_جانچ_32(uncomp_چکری_جانچ_32, (ثابت mz_uint8 *)pRead_buf, اندر_buf_سائز);
        uncomp_بقایا -= اندر_buf_سائز;

        حالت_2 = tdefl_compress_بفر(pComp, pRead_buf, اندر_buf_سائز, uncomp_بقایا ? TDEFL_NO_FLUSH : TDEFL_اختتام);
        اگر (حالت_2 == TDEFL_حالت_مکمل)
        {
          نتیجہ = MZ_TRUE;
          توڑو;
        }
        ورنہ اگر (حالت_2 != TDEFL_حالت_OKAY)
          توڑو;
      }

      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);

      اگر (!نتیجہ)
      {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        واپس MZ_FALSE;
      }

      comp_سائز = state.m_comp_سائز;
      cur_archive_file_ofs = state.m_cur_archive_file_ofs;

      طریقہ = MZ_DEFLATED;
    }

    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
  }

  MZ_FCLOSE(pSrc_file); pSrc_file = تہی;

  // no zip64 support yet
  اگر ((comp_سائز > 0xFFFFFFFF) || (cur_archive_file_ofs > 0xFFFFFFFF))
    واپس MZ_FALSE;

  اگر (!mz_zip_writer_create_local_dir_سرخی(pZip, local_dir_سرخی, (mz_uint16)archive_name_سائز, 0, uncomp_سائز, comp_سائز, uncomp_چکری_جانچ_32, طریقہ, 0, dos_وقت, dos_date))
    واپس MZ_FALSE;

  اگر (pZip->m_pWrite(pZip->m_pIO_opaque, local_dir_سرخی_ofs, local_dir_سرخی, حجم(local_dir_سرخی)) != حجم(local_dir_سرخی))
    واپس MZ_FALSE;

  اگر (!mz_zip_writer_جوڑو_مقصد_central_dir(pZip, pArchive_name, (mz_uint16)archive_name_سائز, تہی, 0, pComment, comment_سائز, uncomp_سائز, comp_سائز, uncomp_چکری_جانچ_32, طریقہ, 0, dos_وقت, dos_date, local_dir_سرخی_ofs, ext_اوصاف))
    واپس MZ_FALSE;

  pZip->m_کل_files++;
  pZip->m_archive_سائز = cur_archive_file_ofs;

  واپس MZ_TRUE;
}
#اگر_ختم // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_writer_جوڑو_from_zip_reader(mz_zip_archive *pZip, mz_zip_archive *p_ماخذ_zip, mz_uint file_اشاریہ)
{
  mz_uint n, ثنائی_ہندسہ_flags, عدد_alignment_padding_بائٹیں;
  mz_uint64 comp_بائٹیں_بقایا, local_dir_سرخی_ofs;
  mz_uint64 cur_src_file_ofs, cur_dst_file_ofs;
  mz_uint32 local_سرخی_u32[(MZ_ZIP_LOCAL_DIR_سرخی_سائز + حجم(mz_uint32) - 1) / حجم(mz_uint32)]; mz_uint8 *p_Local_سرخی = (mz_uint8 *)local_سرخی_u32;
  mz_uint8 central_سرخی[MZ_ZIP_CENTRAL_DIR_سرخی_سائز];
  size_t orig_central_dir_سائز;
  mz_zip_اندرونی_state *pState;
  خالی *pBuf; ثابت mz_uint8 *p_Src_central_سرخی;

  اگر ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_منوال != MZ_ZIP_منوال_WRITING))
    واپس MZ_FALSE;
  اگر (تہی == (p_Src_central_سرخی = mz_zip_reader_get_cdh(p_ماخذ_zip, file_اشاریہ)))
    واپس MZ_FALSE;
  pState = pZip->m_pState;

  عدد_alignment_padding_بائٹیں = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  اگر ((pZip->m_کل_files == 0xFFFF) || ((pZip->m_archive_سائز + عدد_alignment_padding_بائٹیں + MZ_ZIP_LOCAL_DIR_سرخی_سائز + MZ_ZIP_CENTRAL_DIR_سرخی_سائز) > 0xFFFFFFFF))
    واپس MZ_FALSE;

  cur_src_file_ofs = MZ_READ_LE32(p_Src_central_سرخی + MZ_ZIP_CDH_LOCAL_سرخی_OFS);
  cur_dst_file_ofs = pZip->m_archive_سائز;

  اگر (p_ماخذ_zip->m_pRead(p_ماخذ_zip->m_pIO_opaque, cur_src_file_ofs, p_Local_سرخی, MZ_ZIP_LOCAL_DIR_سرخی_سائز) != MZ_ZIP_LOCAL_DIR_سرخی_سائز)
    واپس MZ_FALSE;
  اگر (MZ_READ_LE32(p_Local_سرخی) != MZ_ZIP_LOCAL_DIR_سرخی_SIG)
    واپس MZ_FALSE;
  cur_src_file_ofs += MZ_ZIP_LOCAL_DIR_سرخی_سائز;

  اگر (!mz_zip_writer_write_zeros(pZip, cur_dst_file_ofs, عدد_alignment_padding_بائٹیں))
    واپس MZ_FALSE;
  cur_dst_file_ofs += عدد_alignment_padding_بائٹیں;
  local_dir_سرخی_ofs = cur_dst_file_ofs;
  اگر (pZip->m_file_انحراف_alignment) { MZ_ASSERT((local_dir_سرخی_ofs & (pZip->m_file_انحراف_alignment - 1)) == 0); }

  اگر (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, p_Local_سرخی, MZ_ZIP_LOCAL_DIR_سرخی_سائز) != MZ_ZIP_LOCAL_DIR_سرخی_سائز)
    واپس MZ_FALSE;
  cur_dst_file_ofs += MZ_ZIP_LOCAL_DIR_سرخی_سائز;

  n = MZ_READ_LE16(p_Local_سرخی + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p_Local_سرخی + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  comp_بائٹیں_بقایا = n + MZ_READ_LE32(p_Src_central_سرخی + MZ_ZIP_CDH_COMPRESSED_سائز_OFS);

  اگر (تہی == (pBuf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)MZ_MAX(حجم(mz_uint32) * 4, MZ_MIN(MZ_ZIP_MAX_IO_BUF_سائز, comp_بائٹیں_بقایا)))))
    واپس MZ_FALSE;

  جب (comp_بائٹیں_بقایا)
  {
    n = (mz_uint)MZ_MIN(MZ_ZIP_MAX_IO_BUF_سائز, comp_بائٹیں_بقایا);
    اگر (p_ماخذ_zip->m_pRead(p_ماخذ_zip->m_pIO_opaque, cur_src_file_ofs, pBuf, n) != n)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      واپس MZ_FALSE;
    }
    cur_src_file_ofs += n;

    اگر (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, pBuf, n) != n)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      واپس MZ_FALSE;
    }
    cur_dst_file_ofs += n;

    comp_بائٹیں_بقایا -= n;
  }

  ثنائی_ہندسہ_flags = MZ_READ_LE16(p_Local_سرخی + MZ_ZIP_LDH_ثنائی_ہندسہ_FLAG_OFS);
  اگر (ثنائی_ہندسہ_flags & 8)
  {
    // Copy data descriptor
    اگر (p_ماخذ_zip->m_pRead(p_ماخذ_zip->m_pIO_opaque, cur_src_file_ofs, pBuf, حجم(mz_uint32) * 4) != حجم(mz_uint32) * 4)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      واپس MZ_FALSE;
    }

    n = حجم(mz_uint32) * ((MZ_READ_LE32(pBuf) == 0x08074b50) ? 4 : 3);
    اگر (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, pBuf, n) != n)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      واپس MZ_FALSE;
    }

    cur_src_file_ofs += n;
    cur_dst_file_ofs += n;
  }
  pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);

  // no zip64 support yet
  اگر (cur_dst_file_ofs > 0xFFFFFFFF)
    واپس MZ_FALSE;

  orig_central_dir_سائز = pState->m_central_dir.m_سائز;

  حافظہ_نقل(central_سرخی, p_Src_central_سرخی, MZ_ZIP_CENTRAL_DIR_سرخی_سائز);
  MZ_WRITE_LE32(central_سرخی + MZ_ZIP_CDH_LOCAL_سرخی_OFS, local_dir_سرخی_ofs);
  اگر (!mz_zip_array_ڈالو_عقب(pZip, &pState->m_central_dir, central_سرخی, MZ_ZIP_CENTRAL_DIR_سرخی_سائز))
    واپس MZ_FALSE;

  n = MZ_READ_LE16(p_Src_central_سرخی + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p_Src_central_سرخی + MZ_ZIP_CDH_EXTRA_LEN_OFS) + MZ_READ_LE16(p_Src_central_سرخی + MZ_ZIP_CDH_COMMENT_LEN_OFS);
  اگر (!mz_zip_array_ڈالو_عقب(pZip, &pState->m_central_dir, p_Src_central_سرخی + MZ_ZIP_CENTRAL_DIR_سرخی_سائز, n))
  {
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_سائز, MZ_FALSE);
    واپس MZ_FALSE;
  }

  اگر (pState->m_central_dir.m_سائز > 0xFFFFFFFF)
    واپس MZ_FALSE;
  n = (mz_uint32)orig_central_dir_سائز;
  اگر (!mz_zip_array_ڈالو_عقب(pZip, &pState->m_central_dir_offsets, &n, 1))
  {
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_سائز, MZ_FALSE);
    واپس MZ_FALSE;
  }

  pZip->m_کل_files++;
  pZip->m_archive_سائز = cur_dst_file_ofs;

  واپس MZ_TRUE;
}

mz_bool mz_zip_writer_finalize_archive(mz_zip_archive *pZip)
{
  mz_zip_اندرونی_state *pState;
  mz_uint64 central_dir_ofs, central_dir_سائز;
  mz_uint8 hdr[MZ_ZIP_انتہا_کا_CENTRAL_DIR_سرخی_سائز];

  اگر ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_منوال != MZ_ZIP_منوال_WRITING))
    واپس MZ_FALSE;

  pState = pZip->m_pState;

  // no zip64 support yet
  اگر ((pZip->m_کل_files > 0xFFFF) || ((pZip->m_archive_سائز + pState->m_central_dir.m_سائز + MZ_ZIP_انتہا_کا_CENTRAL_DIR_سرخی_سائز) > 0xFFFFFFFF))
    واپس MZ_FALSE;

  central_dir_ofs = 0;
  central_dir_سائز = 0;
  اگر (pZip->m_کل_files)
  {
    // Write central directory
    central_dir_ofs = pZip->m_archive_سائز;
    central_dir_سائز = pState->m_central_dir.m_سائز;
    pZip->m_central_directory_file_ofs = central_dir_ofs;
    اگر (pZip->m_pWrite(pZip->m_pIO_opaque, central_dir_ofs, pState->m_central_dir.m_p, (size_t)central_dir_سائز) != central_dir_سائز)
      واپس MZ_FALSE;
    pZip->m_archive_سائز += central_dir_سائز;
  }

  // Write end of central directory record
  MZ_CLEAR_ARR(hdr);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_SIG_OFS, MZ_ZIP_انتہا_کا_CENTRAL_DIR_سرخی_SIG);
  MZ_WRITE_LE16(hdr + MZ_ZIP_ECDH_CDIR_عدد_ENTRIES_ON_DISK_OFS, pZip->m_کل_files);
  MZ_WRITE_LE16(hdr + MZ_ZIP_ECDH_CDIR_کل_ENTRIES_OFS, pZip->m_کل_files);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_CDIR_سائز_OFS, central_dir_سائز);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_CDIR_OFS_OFS, central_dir_ofs);

  اگر (pZip->m_pWrite(pZip->m_pIO_opaque, pZip->m_archive_سائز, hdr, حجم(hdr)) != حجم(hdr))
    واپس MZ_FALSE;
#اگر_غیر_تعریف_شدہ MINIZ_NO_STDIO
  اگر ((pState->m_pFile) && (MZ_FFLUSH(pState->m_pFile) == EOF))
    واپس MZ_FALSE;
#اگر_ختم // #ifndef MINIZ_NO_STDIO

  pZip->m_archive_سائز += حجم(hdr);

  pZip->m_zip_منوال = MZ_ZIP_منوال_WRITING_HAS_BEEN_FINALIZED;
  واپس MZ_TRUE;
}

mz_bool mz_zip_writer_finalize_ڈھیر_archive(mz_zip_archive *pZip, خالی **pBuf, size_t *p_سائز)
{
  اگر ((!pZip) || (!pZip->m_pState) || (!pBuf) || (!p_سائز))
    واپس MZ_FALSE;
  اگر (pZip->m_pWrite != mz_zip_ڈھیر_write_func)
    واپس MZ_FALSE;
  اگر (!mz_zip_writer_finalize_archive(pZip))
    واپس MZ_FALSE;

  *pBuf = pZip->m_pState->m_pMem;
  *p_سائز = pZip->m_pState->m_mem_سائز;
  pZip->m_pState->m_pMem = تہی;
  pZip->m_pState->m_mem_سائز = pZip->m_pState->m_mem_استعداد = 0;
  واپس MZ_TRUE;
}

mz_bool mz_zip_writer_انتہا(mz_zip_archive *pZip)
{
  mz_zip_اندرونی_state *pState;
  mz_bool حالت_2 = MZ_TRUE;
  اگر ((!pZip) || (!pZip->m_pState) || (!pZip->m_pAlloc) || (!pZip->m_pFree) || ((pZip->m_zip_منوال != MZ_ZIP_منوال_WRITING) && (pZip->m_zip_منوال != MZ_ZIP_منوال_WRITING_HAS_BEEN_FINALIZED)))
    واپس MZ_FALSE;

  pState = pZip->m_pState;
  pZip->m_pState = تہی;
  mz_zip_array_clear(pZip, &pState->m_central_dir);
  mz_zip_array_clear(pZip, &pState->m_central_dir_offsets);
  mz_zip_array_clear(pZip, &pState->m_sorted_central_dir_offsets);

#اگر_غیر_تعریف_شدہ MINIZ_NO_STDIO
  اگر (pState->m_pFile)
  {
    MZ_FCLOSE(pState->m_pFile);
    pState->m_pFile = تہی;
  }
#اگر_ختم // #ifndef MINIZ_NO_STDIO

  اگر ((pZip->m_pWrite == mz_zip_ڈھیر_write_func) && (pState->m_pMem))
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pState->m_pMem);
    pState->m_pMem = تہی;
  }

  pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
  pZip->m_zip_منوال = MZ_ZIP_منوال_INVALID;
  واپس حالت_2;
}

#اگر_غیر_تعریف_شدہ MINIZ_NO_STDIO
mz_bool mz_zip_جوڑو_mem_مقصد_archive_file_اندر_رکھو(ثابت حرف *pZip_filename, ثابت حرف *pArchive_name, ثابت خالی *pBuf, size_t buf_سائز_2, ثابت خالی *pComment, mz_uint16 comment_سائز, mz_uint level_and_flags)
{
  mz_bool حالت_2, created_new_archive = MZ_FALSE;
  mz_zip_archive zip_archive;
  ساخت MZ_FILE_STAT_STRUCT file_stat;
  MZ_CLEAR_OBJ(zip_archive);
  اگر ((صحیح)level_and_flags < 0)
     level_and_flags = MZ_DEFAULT_LEVEL;
  اگر ((!pZip_filename) || (!pArchive_name) || ((buf_سائز_2) && (!pBuf)) || ((comment_سائز) && (!pComment)) || ((level_and_flags & 0xF) > MZ_UBER_COMPRESSION))
    واپس MZ_FALSE;
  اگر (!mz_zip_writer_validate_archive_name(pArchive_name))
    واپس MZ_FALSE;
  اگر (MZ_FILE_STAT(pZip_filename, &file_stat) != 0)
  {
    // Create a new archive.
    اگر (!mz_zip_writer_init_file(&zip_archive, pZip_filename, 0))
      واپس MZ_FALSE;
    created_new_archive = MZ_TRUE;
  }
  ورنہ
  {
    // Append to an existing archive.
    اگر (!mz_zip_reader_init_file(&zip_archive, pZip_filename, level_and_flags | MZ_ZIP_FLAG_DO_NOT_ترتیب_دو_CENTRAL_DIRECTORY))
      واپس MZ_FALSE;
    اگر (!mz_zip_writer_init_from_reader(&zip_archive, pZip_filename))
    {
      mz_zip_reader_انتہا(&zip_archive);
      واپس MZ_FALSE;
    }
  }
  حالت_2 = mz_zip_writer_جوڑو_mem_ex(&zip_archive, pArchive_name, pBuf, buf_سائز_2, pComment, comment_سائز, level_and_flags, 0, 0);
  // Always finalize, even if adding failed for some reason, so we have a valid central directory. (This may not always succeed, but we can try.)
  اگر (!mz_zip_writer_finalize_archive(&zip_archive))
    حالت_2 = MZ_FALSE;
  اگر (!mz_zip_writer_انتہا(&zip_archive))
    حالت_2 = MZ_FALSE;
  اگر ((!حالت_2) && (created_new_archive))
  {
    // It's a new archive and something went wrong, so just delete it.
    صحیح ignored_حالت = MZ_DELETE_FILE(pZip_filename);
    (خالی)ignored_حالت;
  }
  واپس حالت_2;
}

خالی *mz_zip_نکالو_archive_file_مقصد_ڈھیر(ثابت حرف *pZip_filename, ثابت حرف *pArchive_name, size_t *p_سائز, mz_uint flags)
{
  صحیح file_اشاریہ;
  mz_zip_archive zip_archive;
  خالی *p = تہی;

  اگر (p_سائز)
    *p_سائز = 0;

  اگر ((!pZip_filename) || (!pArchive_name))
    واپس تہی;

  MZ_CLEAR_OBJ(zip_archive);
  اگر (!mz_zip_reader_init_file(&zip_archive, pZip_filename, flags | MZ_ZIP_FLAG_DO_NOT_ترتیب_دو_CENTRAL_DIRECTORY))
    واپس تہی;

  اگر ((file_اشاریہ = mz_zip_reader_locate_file(&zip_archive, pArchive_name, تہی, flags)) >= 0)
    p = mz_zip_reader_نکالو_مقصد_ڈھیر(&zip_archive, file_اشاریہ, p_سائز, flags);

  mz_zip_reader_انتہا(&zip_archive);
  واپس p;
}

#اگر_ختم // #ifndef MINIZ_NO_STDIO

#اگر_ختم // #ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

#اگر_ختم // #ifndef MINIZ_NO_ARCHIVE_APIS

#اگر_تعریف_شدہ __cplusplus
}
#اگر_ختم

#اگر_تعریف_شدہ _MSC_VER
#ہدایت warning (نکالو)
#اگر_ختم

#اگر_ختم // MINIZ_HEADER_FILE_ONLY

/*
  This is free and unencumbered software released into the public domain.

  Anyone is free to copy, modify, publish, use, compile, sell, or
  distribute this software, either in source code form or as a compiled
  binary, for any purpose, commercial or non-commercial, and by any
  means.

  In jurisdictions that recognize copyright laws, the author or authors
  of this software dedicate any and all copyright interest in the
  software to the public domain. We make this dedication for the benefit
  of the public at large and to the detriment of our heirs and
  successors. We intend this dedication to be an overt act of
  relinquishment in perpetuity of all present and future rights to this
  software under copyright law.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
  OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
  OTHER DEALINGS IN THE SOFTWARE.

  For more information, please refer to <http://unlicense.org/>
*/

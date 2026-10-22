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

#جے_بنا_تعریف MINIZ_سرخی_INCLUDED
#تعریف_کرو MINIZ_سرخی_INCLUDED

/*#include <stdlib.h>*/

// Defines to completely disable specific portions of miniz.c:
// If all macros here are defined the only functionality remaining will be CRC-32, adler-32, tinfl, and tdefl.

// Define MINIZ_NO_STDIO to disable all usage and any functions which rely on stdio for file I/O.
#تعریف_کرو MINIZ_NO_STDIO

// If MINIZ_NO_TIME is specified then the ZIP archive functions will not be able to get the current time, or
// get/set file times, and the C run-time funcs that get/set times won't be called.
// The current downside is the times written to your archives will be from 1979.
#تعریف_کرو MINIZ_NO_ویلا

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
#تعریف_کرو MINIZ_NO_ZLIB_COMPATIBLE_ناں

// Define MINIZ_NO_MALLOC to disable all calls to malloc, free, and realloc.
// Note if MINIZ_NO_MALLOC is defined then the user must always provide custom user alloc/free/realloc
// callbacks to the zlib and archive API's, and a few stand-alone helper API's which don't provide custom user
// functions (such as tdefl_compress_mem_to_heap() and tinfl_decompress_mem_to_heap()) won't work.
//#define MINIZ_NO_MALLOC
#تعریف_کرو MINIZ_SDL_MALLOC

#جے_تعریف_شدہ MINIZ_NO_INFLATE_APIS
#تعریف_کرو MINIZ_NO_ARCHIVE_APIS
#جے_انت

#جے_تعریف_شدہ MINIZ_NO_DEFLATE_APIS
#تعریف_کرو MINIZ_NO_ARCHIVE_WRITING_APIS
#جے_انت

// Define MINIZ_STATIC_FUNCTIONS to make all functions static. You probably
// want this if you're using miniz in a library
#تعریف_کرو MINIZ_STATIC_FUNCTIONS

#إذا defined(__TINYC__) && (defined(__linux) || defined(__linux__))
  // TODO: Work around "error: include file 'sys\utime.h' when compiling with tcc on Linux
  #تعریف_کرو MINIZ_NO_ویلا
#جے_انت

#إذا !defined(MINIZ_NO_ویلا) && !defined(MINIZ_NO_ARCHIVE_APIS)
  #ضمن <time.h>
#جے_انت

#إذا defined(_M_IX86) || defined(_M_X64) || defined(__i386__) || defined(__i386) || defined(__i486__) || defined(__i486) || defined(i386) || defined(__ia64__) || defined(__x86_64__)
// MINIZ_X86_OR_X64_CPU is only used to help set the below macros.
#تعریف_کرو MINIZ_X86_OR_X64_CPU 1
#جے_انت

#جے_بنا_تعریف MINIZ_LITTLE_ENDIAN /* if not defined by SDL */
#إذا (__BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__) || MINIZ_X86_OR_X64_CPU
// Set MINIZ_LITTLE_ENDIAN to 1 if the processor is little endian.
#تعریف_کرو MINIZ_LITTLE_ENDIAN 1
#جے_انت
#جے_انت // MINIZ_LITTLE_ENDIAN /* if not defined by SDL */

#جے_بنا_تعریف MINIZ_USE_UNALIGNED_LOADS_AND_STORES
#إذا MINIZ_X86_OR_X64_CPU
// Set MINIZ_USE_UNALIGNED_LOADS_AND_STORES to 1 on CPU's that permit efficient integer loads and stores from unaligned addresses.
#تعریف_کرو MINIZ_USE_UNALIGNED_LOADS_AND_STORES 1
#جے_انت
#جے_انت // MINIZ_USE_UNALIGNED_LOADS_AND_STORES

#إذا defined(_M_X64) || defined(_WIN64) || defined(__MINGW64__) || defined(_LP64) || defined(__LP64__) || defined(__ia64__) || defined(__x86_64__)
// Set MINIZ_HAS_64BIT_REGISTERS to 1 if operations on 64-bit integers are reasonably fast (and don't involve compiler generated calls to helper functions).
#تعریف_کرو MINIZ_HAS_64_ثنائی_ہندسہ_REGISTERS 1
#جے_انت

#جے_تعریف_شدہ MINIZ_STATIC_FUNCTIONS
#تعریف_کرو MINIZ_STATIC ساكن
#وإلا
#تعریف_کرو MINIZ_STATIC
#جے_انت

#جے_تعریف_شدہ __cplusplus
خارجي "C" {
#جے_انت

// ------------------- zlib-style API Definitions.

// For more compatibility with zlib, miniz.c uses unsigned long for some parameters/struct members. Beware: mz_ulong can be either 32 or 64-bits!
تعريفنوع بنانشانی لما mz_ulong;

// mz_free() internally uses the MZ_FREE() macro (which by default calls free() unless you've modified the MZ_MALLOC macro) to release a block allocated from the heap.
MINIZ_STATIC فراغ mz_free(فراغ *p);

#تعریف_کرو MZ_ADLER32_INIT (1)
// mz_adler32() returns the initial adler-32 value to use when called with ptr==NULL.
MINIZ_STATIC mz_ulong mz_adler32(mz_ulong adler, ثابت بنانشانی حرف *ptr, size_t buf_len);

#تعریف_کرو MZ_چکری_جانچ_32_INIT (0)
// mz_crc32() returns the initial CRC-32 value to use when called with ptr==NULL.
MINIZ_STATIC mz_ulong mz_چکری_جانچ_32(mz_ulong چکری_جانچ, ثابت بنانشانی حرف *ptr, size_t buf_len);

// Compression strategies.
تعداد { MZ_DEFAULT_STRATEGY = 0, MZ_FILTERED = 1, MZ_HUFFMAN_ONLY = 2, MZ_RLE = 3, MZ_FIXED = 4 };

//طریقہ
#تعریف_کرو MZ_DEFLATED 8

#جے_بنا_تعریف MINIZ_NO_ZLIB_APIS

// Heap allocation callbacks.
// Note that mz_alloc_func parameter types purpsosely differ from zlib's: items/size is size_t, not unsigned long.
تعريفنوع فراغ *(*mz_alloc_func)(فراغ *opaque, size_t اشیاء, size_t ناپ);
تعريفنوع فراغ (*mz_free_func)(فراغ *opaque, فراغ *پتہ);
تعريفنوع فراغ *(*mz_realloc_func)(فراغ *opaque, فراغ *پتہ, size_t اشیاء, size_t ناپ);

#تعریف_کرو MZ_نسخہ          "9.1.15"
#تعریف_کرو MZ_VERNUM           0x91F0
#تعریف_کرو MZ_VER_MAJOR        9
#تعریف_کرو MZ_VER_MINOR        1
#تعریف_کرو MZ_VER_REVISION     15
#تعریف_کرو MZ_VER_SUBREVISION  0

// Flush values. For typical usage you only need MZ_NO_FLUSH and MZ_FINISH. The other values are for advanced use (refer to the zlib docs).
تعداد { MZ_NO_FLUSH = 0, MZ_PARTIAL_FLUSH = 1, MZ_SYNC_FLUSH = 2, MZ_بھریا_FLUSH = 3, MZ_انت = 4, MZ_بلاک = 5 };

// Return status codes. MZ_PARAM_ERROR is non-standard.
تعداد { MZ_OK = 0, MZ_دھارا_سرا = 1, MZ_NEED_DICT = 2, MZ_ERRNO = -1, MZ_دھارا_ERROR = -2, MZ_انکڑے_ERROR = -3, MZ_MEM_ERROR = -4, MZ_BUF_ERROR = -5, MZ_نسخہ_ERROR = -6, MZ_PARAM_ERROR = -10000 };

// Compression levels: 0-9 are the standard zlib-style levels, 10 is best possible compression (not zlib compatible, and may be very slow), MZ_DEFAULT_COMPRESSION=MZ_DEFAULT_LEVEL.
تعداد { MZ_NO_COMPRESSION = 0, MZ_بہترین_رفتار = 1, MZ_بہترین_COMPRESSION = 9, MZ_UBER_COMPRESSION = 10, MZ_DEFAULT_LEVEL = 6, MZ_DEFAULT_COMPRESSION = -1 };

// Window bits
#تعریف_کرو MZ_DEFAULT_کھڑکی_بٹ 15

بنية mz_اندرونی_state;

// Compression/decompression stream struct.
تعريفنوع بنية mz_دھارا_s
{
  ثابت بنانشانی حرف *اگلا_وچ;     // pointer to next byte to read
  بنانشانی صحيح avail_وچ;            // number of bytes available at next_in
  mz_ulong کل_وچ;                // total number of bytes consumed so far

  بنانشانی حرف *اگلا_باہرلا;          // pointer to next byte to write
  بنانشانی صحيح avail_باہرلا;           // number of bytes that can be written to next_out
  mz_ulong کل_باہرلا;               // total number of bytes produced so far

  حرف *پیغام;                        // error msg (unused)
  بنية mz_اندرونی_state *state;  // internal state, allocated by zalloc/zfree

  mz_alloc_func zalloc;             // optional heap allocation function (defaults to malloc)
  mz_free_func zfree;               // optional heap free function (defaults to free)
  فراغ *opaque;                     // heap alloc function user pointer

  صحيح انکڑے_type;                    // data_type (unused)
  mz_ulong adler;                   // adler32 of the source or uncompressed data
  mz_ulong reserved;                // not used
} mz_دھارا;

تعريفنوع mz_دھارا *mz_streamp;

// Returns the version string of miniz.c.
MINIZ_STATIC ثابت حرف *mz_نسخہ(فراغ);

#جے_بنا_تعریف MINIZ_NO_DEFLATE_APIS

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
MINIZ_STATIC صحيح mz_deflateInit(mz_streamp p_دھارا, صحيح level);

// mz_deflateInit2() is like mz_deflate(), except with more control:
// Additional parameters:
//   method must be MZ_DEFLATED
//   window_bits must be MZ_DEFAULT_WINDOW_BITS (to wrap the deflate stream with zlib header/adler-32 footer) or -MZ_DEFAULT_WINDOW_BITS (raw deflate/no header or footer)
//   mem_level must be between [1, 9] (it's checked but ignored by miniz.c)
MINIZ_STATIC صحيح mz_deflateInit2(mz_streamp p_دھارا, صحيح level, صحيح طریقہ, صحيح کھڑکی_بٹ, صحيح mem_level, صحيح strategy);

// Quickly resets a compressor without having to reallocate anything. Same as calling mz_deflateEnd() followed by mz_deflateInit()/mz_deflateInit2().
MINIZ_STATIC صحيح mz_deflateReset(mz_streamp p_دھارا);

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
MINIZ_STATIC صحيح mz_deflate(mz_streamp p_دھارا, صحيح flush);

// mz_deflateEnd() deinitializes a compressor:
// Return values:
//  MZ_OK on success.
//  MZ_STREAM_ERROR if the stream is bogus.
MINIZ_STATIC صحيح mz_deflate_سرا(mz_streamp p_دھارا);

// mz_deflateBound() returns a (very) conservative upper bound on the amount of data that could be generated by deflate(), assuming flush is set to only MZ_NO_FLUSH or MZ_FINISH.
MINIZ_STATIC mz_ulong mz_deflateBound(mz_streamp p_دھارا, mz_ulong سروت_len);

// Single-call compression functions mz_compress() and mz_compress2():
// Returns MZ_OK on success, or one of the error codes from mz_deflate() on failure.
MINIZ_STATIC صحيح mz_compress(بنانشانی حرف *pDest, mz_ulong *pDest_len, ثابت بنانشانی حرف *p_سروت, mz_ulong سروت_len);
MINIZ_STATIC صحيح mz_compress2(بنانشانی حرف *pDest, mz_ulong *pDest_len, ثابت بنانشانی حرف *p_سروت, mz_ulong سروت_len, صحيح level);

// mz_compressBound() returns a (very) conservative upper bound on the amount of data that could be generated by calling mz_compress().
MINIZ_STATIC mz_ulong mz_compressBound(mz_ulong سروت_len);

#جے_انت /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#جے_بنا_تعریف MINIZ_NO_INFLATE_APIS

// Initializes a decompressor.
MINIZ_STATIC صحيح mz_inflateInit(mz_streamp p_دھارا);

// mz_inflateInit2() is like mz_inflateInit() with an additional option that controls the window size and whether or not the stream has been wrapped with a zlib header/footer:
// window_bits must be MZ_DEFAULT_WINDOW_BITS (to parse zlib header/footer) or -MZ_DEFAULT_WINDOW_BITS (raw deflate).
MINIZ_STATIC صحيح mz_inflateInit2(mz_streamp p_دھارا, صحيح کھڑکی_بٹ);

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
MINIZ_STATIC صحيح mz_inflate(mz_streamp p_دھارا, صحيح flush);

// Deinitializes a decompressor.
MINIZ_STATIC صحيح mz_inflate_سرا(mz_streamp p_دھارا);

// Single-call decompression.
// Returns MZ_OK on success, or one of the error codes from mz_inflate() on failure.
MINIZ_STATIC صحيح mz_uncompress(بنانشانی حرف *pDest, mz_ulong *pDest_len, ثابت بنانشانی حرف *p_سروت, mz_ulong سروت_len);
#جے_انت /*#ifndef MINIZ_NO_INFLATE_APIS*/

// Returns a string description of the specified error code, or NULL if the error code is invalid.
MINIZ_STATIC ثابت حرف *mz_error(صحيح err);

// Redefine zlib-compatible names to miniz equivalents, so miniz.c can be used as a drop-in replacement for the subset of zlib that miniz.c supports.
// Define MINIZ_NO_ZLIB_COMPATIBLE_NAMES to disable zlib-compatibility if you use zlib in the same project.
#جے_بنا_تعریف MINIZ_NO_ZLIB_COMPATIBLE_ناں
  تعريفنوع بنانشانی حرف Byte;
  تعريفنوع بنانشانی صحيح uInt;
  تعريفنوع mz_ulong uLong;
  تعريفنوع Byte Bytef;
  تعريفنوع uInt uIntf;
  تعريفنوع حرف charf;
  تعريفنوع صحيح intf;
  تعريفنوع فراغ *voidpf;
  تعريفنوع uLong uLongf;
  تعريفنوع فراغ *voidp;
  تعريفنوع فراغ *ثابت voidpc;
  #تعریف_کرو Z_NULL                0
  #تعریف_کرو Z_NO_FLUSH            MZ_NO_FLUSH
  #تعریف_کرو Z_PARTIAL_FLUSH       MZ_PARTIAL_FLUSH
  #تعریف_کرو Z_SYNC_FLUSH          MZ_SYNC_FLUSH
  #تعریف_کرو Z_بھریا_FLUSH          MZ_بھریا_FLUSH
  #تعریف_کرو Z_انت              MZ_انت
  #تعریف_کرو Z_بلاک               MZ_بلاک
  #تعریف_کرو Z_OK                  MZ_OK
  #تعریف_کرو Z_دھارا_سرا          MZ_دھارا_سرا
  #تعریف_کرو Z_NEED_DICT           MZ_NEED_DICT
  #تعریف_کرو Z_ERRNO               MZ_ERRNO
  #تعریف_کرو Z_دھارا_ERROR        MZ_دھارا_ERROR
  #تعریف_کرو Z_انکڑے_ERROR          MZ_انکڑے_ERROR
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
#جے_بنا_تعریف MINIZ_NO_DEFLATE_APIS
  #تعریف_کرو deflateInit           mz_deflateInit
  #تعریف_کرو deflateInit2          mz_deflateInit2
  #تعریف_کرو deflateReset          mz_deflateReset
  #تعریف_کرو deflate               mz_deflate
  #تعریف_کرو deflate_سرا            mz_deflate_سرا
  #تعریف_کرو deflateBound          mz_deflateBound
  #تعریف_کرو compress              mz_compress
  #تعریف_کرو compress2             mz_compress2
  #تعریف_کرو compressBound         mz_compressBound
#جے_انت /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#جے_بنا_تعریف MINIZ_NO_INFLATE_APIS
  #تعریف_کرو inflateInit           mz_inflateInit
  #تعریف_کرو inflateInit2          mz_inflateInit2
  #تعریف_کرو inflate               mz_inflate
  #تعریف_کرو inflate_سرا            mz_inflate_سرا
  #تعریف_کرو uncompress            mz_uncompress
#جے_انت /*#ifndef MINIZ_NO_INFLATE_APIS*/
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
#جے_انت // #ifndef MINIZ_NO_ZLIB_COMPATIBLE_NAMES

#جے_انت // MINIZ_NO_ZLIB_APIS

// ------------------- Types and macros

تعريفنوع بنانشانی حرف mz_uint8;
تعريفنوع نشانیوالا چھوٹا mz_int16;
تعريفنوع بنانشانی چھوٹا mz_uint16;
تعريفنوع بنانشانی صحيح mz_uint32;
تعريفنوع بنانشانی صحيح mz_uint;
تعريفنوع لما لما mz_int64;
تعريفنوع بنانشانی لما لما mz_uint64;
تعريفنوع صحيح mz_bool;

#تعریف_کرو MZ_FALSE (0)
#تعریف_کرو MZ_TRUE (1)

// An attempt to work around MSVC's spammy "warning C4127: conditional expression is constant" message.
#جے_تعریف_شدہ _MSC_VER
   #تعریف_کرو MZ_MACRO_سرا طالما (0, 0)
#وإلا
   #تعریف_کرو MZ_MACRO_سرا طالما (0)
#جے_انت

// ------------------- ZIP archive reading/writing

#جے_بنا_تعریف MINIZ_NO_ARCHIVE_APIS

تعداد
{
  MZ_ZIP_MAX_IO_BUF_ناپ = 64*1024,
  MZ_ZIP_MAX_ARCHIVE_FILENAME_ناپ = 260,
  MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_ناپ = 256
};

تعريفنوع بنية
{
  mz_uint32 m_file_اشاریہ;
  mz_uint32 m_central_dir_ofs;
  mz_uint16 m_نسخہ_made_by;
  mz_uint16 m_نسخہ_needed;
  mz_uint16 m_ثنائی_ہندسہ_flag;
  mz_uint16 m_طریقہ;
#جے_بنا_تعریف MINIZ_NO_ویلا
  ویلا_t m_ویلا;
#جے_انت
  mz_uint32 m_چکری_جانچ_32;
  mz_uint64 m_comp_ناپ;
  mz_uint64 m_uncomp_ناپ;
  mz_uint16 m_اندرونی_attr;
  mz_uint32 m_external_attr;
  mz_uint64 m_local_سرخی_ofs;
  mz_uint32 m_comment_ناپ;
  حرف m_filename[MZ_ZIP_MAX_ARCHIVE_FILENAME_ناپ];
  حرف m_comment[MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_ناپ];
} mz_zip_archive_file_stat;

تعريفنوع size_t (*mz_file_read_func)(فراغ *pOpaque, mz_uint64 file_ofs, فراغ *pBuf, size_t n);
تعريفنوع size_t (*mz_file_write_func)(فراغ *pOpaque, mz_uint64 file_ofs, ثابت فراغ *pBuf, size_t n);

بنية mz_zip_اندرونی_state_ٹیگ;
تعريفنوع بنية mz_zip_اندرونی_state_ٹیگ mz_zip_اندرونی_state;

تعريفنوع تعداد
{
  MZ_ZIP_منوال_INVALID = 0,
  MZ_ZIP_منوال_READING = 1,
  MZ_ZIP_منوال_WRITING = 2,
  MZ_ZIP_منوال_WRITING_HAS_BEEN_FINALIZED = 3
} mz_zip_منوال;

تعريفنوع بنية mz_zip_archive_ٹیگ
{
  mz_uint64 m_archive_ناپ;
  mz_uint64 m_central_directory_file_ofs;
  mz_uint m_کل_files;
  mz_zip_منوال m_zip_منوال;

  mz_uint m_file_وتھ_alignment;

  mz_alloc_func m_pAlloc;
  mz_free_func m_pFree;
  mz_realloc_func m_pRealloc;
  فراغ *m_pAlloc_opaque;

  mz_file_read_func m_pRead;
  mz_file_write_func m_pWrite;
  فراغ *m_pIO_opaque;

  mz_zip_اندرونی_state *m_pState;

} mz_zip_archive;

تعريفنوع تعداد
{
  MZ_ZIP_FLAG_CASE_SENSITIVE                = 0x0100,
  MZ_ZIP_FLAG_IGNORE_رستہ                   = 0x0200,
  MZ_ZIP_FLAG_COMPRESSED_انکڑے               = 0x0400,
  MZ_ZIP_FLAG_DO_NOT_ترتیب_دیو_CENTRAL_DIRECTORY = 0x0800
} mz_zip_flags;

// ZIP archive reading

// Inits a ZIP archive reader.
// These functions read and validate the archive's central directory.
MINIZ_STATIC mz_bool mz_zip_reader_init(mz_zip_archive *pZip, mz_uint64 ناپ, mz_uint32 flags);
MINIZ_STATIC mz_bool mz_zip_reader_init_mem(mz_zip_archive *pZip, ثابت فراغ *pMem, size_t ناپ, mz_uint32 flags);

#جے_بنا_تعریف MINIZ_NO_STDIO
MINIZ_STATIC mz_bool mz_zip_reader_init_file(mz_zip_archive *pZip, ثابت حرف *pFilename, mz_uint32 flags);
#جے_انت

// Returns the total number of files in the archive.
MINIZ_STATIC mz_uint mz_zip_reader_get_عدد_files(mz_zip_archive *pZip);

// Returns detailed information about an archive file entry.
MINIZ_STATIC mz_bool mz_zip_reader_file_stat(mz_zip_archive *pZip, mz_uint file_اشاریہ, mz_zip_archive_file_stat *pStat);

// Determines if an archive file entry is a directory entry.
MINIZ_STATIC mz_bool mz_zip_reader_is_file_a_directory(mz_zip_archive *pZip, mz_uint file_اشاریہ);
MINIZ_STATIC mz_bool mz_zip_reader_is_file_encrypted(mz_zip_archive *pZip, mz_uint file_اشاریہ);

// Retrieves the filename of an archive file entry.
// Returns the number of bytes written to pFilename, or if filename_buf_size is 0 this function returns the number of bytes needed to fully store the filename.
MINIZ_STATIC mz_uint mz_zip_reader_get_filename(mz_zip_archive *pZip, mz_uint file_اشاریہ, حرف *pFilename, mz_uint filename_buf_ناپ);

// Attempts to locates a file in the archive's central directory.
// Valid flags: MZ_ZIP_FLAG_CASE_SENSITIVE, MZ_ZIP_FLAG_IGNORE_PATH
// Returns -1 if the file cannot be found.
MINIZ_STATIC صحيح mz_zip_reader_locate_file(mz_zip_archive *pZip, ثابت حرف *pName, ثابت حرف *pComment, mz_uint flags);

// Extracts a archive file to a memory buffer using no memory allocation.
MINIZ_STATIC mz_bool mz_zip_reader_کڈھو_منزل_mem_no_alloc(mz_zip_archive *pZip, mz_uint file_اشاریہ, فراغ *pBuf, size_t buf_ناپ_2, mz_uint flags, فراغ *pUser_read_buf, size_t user_read_buf_ناپ);
MINIZ_STATIC mz_bool mz_zip_reader_کڈھو_file_منزل_mem_no_alloc(mz_zip_archive *pZip, ثابت حرف *pFilename, فراغ *pBuf, size_t buf_ناپ_2, mz_uint flags, فراغ *pUser_read_buf, size_t user_read_buf_ناپ);

// Extracts a archive file to a memory buffer.
MINIZ_STATIC mz_bool mz_zip_reader_کڈھو_منزل_mem(mz_zip_archive *pZip, mz_uint file_اشاریہ, فراغ *pBuf, size_t buf_ناپ_2, mz_uint flags);
MINIZ_STATIC mz_bool mz_zip_reader_کڈھو_file_منزل_mem(mz_zip_archive *pZip, ثابت حرف *pFilename, فراغ *pBuf, size_t buf_ناپ_2, mz_uint flags);

// Extracts a archive file to a dynamically allocated heap buffer.
MINIZ_STATIC فراغ *mz_zip_reader_کڈھو_منزل_ڈھیر(mz_zip_archive *pZip, mz_uint file_اشاریہ, size_t *p_ناپ, mz_uint flags);
MINIZ_STATIC فراغ *mz_zip_reader_کڈھو_file_منزل_ڈھیر(mz_zip_archive *pZip, ثابت حرف *pFilename, size_t *p_ناپ, mz_uint flags);

// Extracts a archive file using a callback function to output the file's data.
MINIZ_STATIC mz_bool mz_zip_reader_کڈھو_منزل_callback(mz_zip_archive *pZip, mz_uint file_اشاریہ, mz_file_write_func pCallback, فراغ *pOpaque, mz_uint flags);
MINIZ_STATIC mz_bool mz_zip_reader_کڈھو_file_منزل_callback(mz_zip_archive *pZip, ثابت حرف *pFilename, mz_file_write_func pCallback, فراغ *pOpaque, mz_uint flags);

#جے_بنا_تعریف MINIZ_NO_STDIO
// Extracts a archive file to a disk file and sets its last accessed and modified times.
// This function only extracts files, not archive directory records.
MINIZ_STATIC mz_bool mz_zip_reader_کڈھو_منزل_file(mz_zip_archive *pZip, mz_uint file_اشاریہ, ثابت حرف *pDst_filename, mz_uint flags);
MINIZ_STATIC mz_bool mz_zip_reader_کڈھو_file_منزل_file(mz_zip_archive *pZip, ثابت حرف *pArchive_filename, ثابت حرف *pDst_filename, mz_uint flags);
#جے_انت

// Ends archive reading, freeing all allocations, and closing the input archive file if mz_zip_reader_init_file() was used.
MINIZ_STATIC mz_bool mz_zip_reader_سرا(mz_zip_archive *pZip);

// ZIP archive writing

#جے_بنا_تعریف MINIZ_NO_ARCHIVE_WRITING_APIS

// Inits a ZIP archive writer.
MINIZ_STATIC mz_bool mz_zip_writer_init(mz_zip_archive *pZip, mz_uint64 existing_ناپ);
MINIZ_STATIC mz_bool mz_zip_writer_init_ڈھیر(mz_zip_archive *pZip, size_t ناپ_منزل_reserve_at_beginning, size_t initial_ونڈ_ناپ);

#جے_بنا_تعریف MINIZ_NO_STDIO
MINIZ_STATIC mz_bool mz_zip_writer_init_file(mz_zip_archive *pZip, ثابت حرف *pFilename, mz_uint64 ناپ_منزل_reserve_at_beginning);
#جے_انت

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
MINIZ_STATIC mz_bool mz_zip_writer_جوڑو_mem(mz_zip_archive *pZip, ثابت حرف *pArchive_name, ثابت فراغ *pBuf, size_t buf_ناپ_2, mz_uint level_and_flags);
MINIZ_STATIC mz_bool mz_zip_writer_جوڑو_mem_ex(mz_zip_archive *pZip, ثابت حرف *pArchive_name, ثابت فراغ *pBuf, size_t buf_ناپ_2, ثابت فراغ *pComment, mz_uint16 comment_ناپ, mz_uint level_and_flags, mz_uint64 uncomp_ناپ, mz_uint32 uncomp_چکری_جانچ_32);

#جے_بنا_تعریف MINIZ_NO_STDIO
// Adds the contents of a disk file to an archive. This function also records the disk file's modified time into the archive.
// level_and_flags - compression level (0-10, see MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or just set to MZ_DEFAULT_COMPRESSION.
MINIZ_STATIC mz_bool mz_zip_writer_جوڑو_file(mz_zip_archive *pZip, ثابت حرف *pArchive_name, ثابت حرف *pSrc_filename, ثابت فراغ *pComment, mz_uint16 comment_ناپ, mz_uint level_and_flags);
#جے_انت

// Adds a file to an archive by fully cloning the data from another archive.
// This function fully clones the source file's compressed data (no recompression), along with its full filename, extra data, and comment fields.
MINIZ_STATIC mz_bool mz_zip_writer_جوڑو_from_zip_reader(mz_zip_archive *pZip, mz_zip_archive *p_سروت_zip, mz_uint file_اشاریہ);

// Finalizes the archive by writing the central directory records followed by the end of central directory record.
// After an archive is finalized, the only valid call on the mz_zip_archive struct is mz_zip_writer_end().
// An archive must be manually finalized by calling this function for it to be valid.
MINIZ_STATIC mz_bool mz_zip_writer_finalize_archive(mz_zip_archive *pZip);
MINIZ_STATIC mz_bool mz_zip_writer_finalize_ڈھیر_archive(mz_zip_archive *pZip, فراغ **pBuf, size_t *p_ناپ);

// Ends archive writing, freeing all allocations, and closing the output file if mz_zip_writer_init_file() was used.
// Note for the archive to be valid, it must have been finalized before ending.
MINIZ_STATIC mz_bool mz_zip_writer_سرا(mz_zip_archive *pZip);

// Misc. high-level helper functions:

// mz_zip_add_mem_to_archive_file_in_place() efficiently (but not atomically) appends a memory blob to a ZIP archive.
// level_and_flags - compression level (0-10, see MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or just set to MZ_DEFAULT_COMPRESSION.
MINIZ_STATIC mz_bool mz_zip_جوڑو_mem_منزل_archive_file_وچ_رکھو(ثابت حرف *pZip_filename, ثابت حرف *pArchive_name, ثابت فراغ *pBuf, size_t buf_ناپ_2, ثابت فراغ *pComment, mz_uint16 comment_ناپ, mz_uint level_and_flags);

// Reads a single file from an archive into a heap block.
// Returns NULL on failure.
MINIZ_STATIC فراغ *mz_zip_کڈھو_archive_file_منزل_ڈھیر(ثابت حرف *pZip_filename, ثابت حرف *pArchive_name, size_t *p_ناپ, mz_uint zip_flags);

#جے_انت // #ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

#جے_انت // #ifndef MINIZ_NO_ARCHIVE_APIS

// ------------------- Low-level Decompression API Definitions
#جے_بنا_تعریف MINIZ_NO_INFLATE_APIS

// Decompression flags used by tinfl_decompress().
// TINFL_FLAG_PARSE_ZLIB_HEADER: If set, the input has a valid zlib header and ends with an adler32 checksum (it's a valid zlib stream). Otherwise, the input is a raw deflate stream.
// TINFL_FLAG_HAS_MORE_INPUT: If set, there are more input bytes available beyond the end of the supplied input buffer. If clear, the input buffer contains all remaining input.
// TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF: If set, the output buffer is large enough to hold the entire decompressed stream. If clear, the output buffer is at least the size of the dictionary (typically 32KB).
// TINFL_FLAG_COMPUTE_ADLER32: Force adler-32 checksum computation of the decompressed bytes.
تعداد
{
  TINFL_FLAG_PARSE_ZLIB_سرخی = 1,
  TINFL_FLAG_HAS_ہور_داخلہ = 2,
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
MINIZ_STATIC فراغ *tinfl_decompress_mem_منزل_ڈھیر(ثابت فراغ *pSrc_buf, size_t src_buf_len, size_t *p_باہرلا_len, صحيح flags);

// tinfl_decompress_mem_to_mem() decompresses a block in memory to another block in memory.
// Returns TINFL_DECOMPRESS_MEM_TO_MEM_FAILED on failure, or the number of bytes written on success.
#تعریف_کرو TINFL_DECOMPRESS_MEM_منزل_MEM_FAILED ((size_t)(-1))
MINIZ_STATIC size_t tinfl_decompress_mem_منزل_mem(فراغ *p_باہرلا_buf, size_t باہرلا_buf_len, ثابت فراغ *pSrc_buf, size_t src_buf_len, صحيح flags);

// tinfl_decompress_mem_to_callback() decompresses a block in memory to an internal 32KB buffer, and a user provided callback function will be called to flush the buffer.
// Returns 1 on success or 0 on failure.
تعريفنوع صحيح (*tinfl_put_buf_func_ptr)(ثابت فراغ* pBuf, صحيح len, فراغ *pUser);
MINIZ_STATIC صحيح tinfl_decompress_mem_منزل_callback(ثابت فراغ *p_وچ_buf, size_t *p_وچ_buf_ناپ, tinfl_put_buf_func_ptr pPut_buf_func, فراغ *pPut_buf_user, صحيح flags);

بنية tinfl_decompressor_ٹیگ; تعريفنوع بنية tinfl_decompressor_ٹیگ tinfl_decompressor;

// Max size of LZ dictionary.
#تعریف_کرو TINFL_LZ_DICT_ناپ 32768

// Return status.
تعريفنوع تعداد
{
  TINFL_حالت_BAD_PARAM = -3,
  TINFL_حالت_ADLER32_MISMATCH = -2,
  TINFL_حالت_FAILED = -1,
  TINFL_حالت_پورا = 0,
  TINFL_حالت_NEEDS_ہور_داخلہ = 1,
  TINFL_حالت_HAS_ہور_OUTPUT = 2
} tinfl_حالت;

// Initializes the decompressor to its initial state.
#تعریف_کرو tinfl_init(r) افعل { (r)->m_state = 0; } MZ_MACRO_سرا
#تعریف_کرو tinfl_get_adler32(r) (r)->m_check_adler32

// Main low-level decompressor coroutine function. This is the only function actually needed for decompression. All the other functions are just high-level helpers for improved usability.
// This is a universal API, i.e. it can be used as a building block to build any desired higher level decompression API. In the limit case, it can be called once per every byte input or output.
MINIZ_STATIC tinfl_حالت tinfl_decompress(tinfl_decompressor *r, ثابت mz_uint8 *p_وچ_buf_اگلا, size_t *p_وچ_buf_ناپ, mz_uint8 *p_باہرلا_buf_شروع, mz_uint8 *p_باہرلا_buf_اگلا, size_t *p_باہرلا_buf_ناپ, ثابت mz_uint32 decomp_flags);

// Internal/private bits follow.
تعداد
{
  TINFL_MAX_HUFF_TABLES = 3, TINFL_MAX_HUFF_SYMBOLS_0 = 288, TINFL_MAX_HUFF_SYMBOLS_1 = 32, TINFL_MAX_HUFF_SYMBOLS_2 = 19,
  TINFL_FAST_LOOKUP_بٹ = 10, TINFL_FAST_LOOKUP_ناپ = 1 << TINFL_FAST_LOOKUP_بٹ
};

تعريفنوع بنية
{
  mz_uint8 m_کوڈ_ناپ[TINFL_MAX_HUFF_SYMBOLS_0];
  mz_int16 m_look_اتے[TINFL_FAST_LOOKUP_ناپ], m_درخت[TINFL_MAX_HUFF_SYMBOLS_0 * 2];
} tinfl_huff_جدول;

#إذا MINIZ_HAS_64_ثنائی_ہندسہ_REGISTERS
  #تعریف_کرو TINFL_USE_64_ثنائی_ہندسہ_BITBUF 1
#جے_انت

#إذا TINFL_USE_64_ثنائی_ہندسہ_BITBUF
  تعريفنوع mz_uint64 tinfl_ثنائی_ہندسہ_buf_t;
  #تعریف_کرو TINFL_BITBUF_ناپ (64)
#وإلا
  تعريفنوع mz_uint32 tinfl_ثنائی_ہندسہ_buf_t;
  #تعریف_کرو TINFL_BITBUF_ناپ (32)
#جے_انت

بنية tinfl_decompressor_ٹیگ
{
  mz_uint32 m_state, m_عدد_بٹ, m_zhdr0, m_zhdr1, m_z_adler32, m_final, m_type, m_check_adler32, m_dist, m_counter, m_عدد_extra, m_جدول_sizes[TINFL_MAX_HUFF_TABLES];
  tinfl_ثنائی_ہندسہ_buf_t m_ثنائی_ہندسہ_buf;
  size_t m_dist_from_باہرلا_buf_شروع;
  tinfl_huff_جدول m_tables[TINFL_MAX_HUFF_TABLES];
  mz_uint8 m_raw_سرخی[4], m_len_codes[TINFL_MAX_HUFF_SYMBOLS_0 + TINFL_MAX_HUFF_SYMBOLS_1 + 137];
};
#جے_انت /*#ifndef MINIZ_NO_INFLATE_APIS*/

// ------------------- Low-level Compression API Definitions
#جے_بنا_تعریف MINIZ_NO_DEFLATE_APIS

// Set TDEFL_LESS_MEMORY to 1 to use less memory (compression will be slightly slower, and raw/dynamic blocks will be output more frequently).
#تعریف_کرو TDEFL_LESS_حافظہ 0

// tdefl_init() compression flags logically OR'd together (low 12 bits contain the max. number of probes per dictionary search):
// TDEFL_DEFAULT_MAX_PROBES: The compressor defaults to 128 dictionary probes per dictionary search. 0=Huffman only, 1=Huffman+LZ (fastest/crap compression), 4095=Huffman+LZ (slowest/best compression).
تعداد
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
تعداد
{
  TDEFL_WRITE_ZLIB_سرخی             = 0x01000,
  TDEFL_COMPUTE_ADLER32               = 0x02000,
  TDEFL_GREEDY_PARSING_FLAG           = 0x04000,
  TDEFL_NONDETERMINISTIC_PARSING_FLAG = 0x08000,
  TDEFL_RLE_MATCHES                   = 0x10000,
  TDEFL_FILTER_MATCHES                = 0x20000,
  TDEFL_FORCE_ALL_STATIC_بلاکاں       = 0x40000,
  TDEFL_FORCE_ALL_RAW_بلاکاں          = 0x80000
};

#جے_بنا_تعریف MINIZ_SDL_NOUNUSED
// High level compression functions:
// tdefl_compress_mem_to_heap() compresses a block in memory to a heap block allocated via malloc().
// On entry:
//  pSrc_buf, src_buf_len: Pointer and size of source block to compress.
//  flags: The max match finder probes (default is 128) logically OR'd against the above flags. Higher probes are slower but improve compression.
// On return:
//  Function returns a pointer to the compressed data, or NULL on failure.
//  *pOut_len will be set to the compressed data's size, which could be larger than src_buf_len on uncompressible data.
//  The caller must free() the returned block when it's no longer needed.
MINIZ_STATIC فراغ *tdefl_compress_mem_منزل_ڈھیر(ثابت فراغ *pSrc_buf, size_t src_buf_len, size_t *p_باہرلا_len, صحيح flags);

// tdefl_compress_mem_to_mem() compresses a block in memory to another block in memory.
// Returns 0 on failure.
MINIZ_STATIC size_t tdefl_compress_mem_منزل_mem(فراغ *p_باہرلا_buf, size_t باہرلا_buf_len, ثابت فراغ *pSrc_buf, size_t src_buf_len, صحيح flags);
#جے_انت /* MINIZ_SDL_NOUNUSED */

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
MINIZ_STATIC فراغ *tdefl_write_image_منزل_png_file_وچ_حافظہ_ex(ثابت فراغ *pImage, صحيح w, صحيح h, صحيح عدد_chans, صحيح bpl, size_t *p_Len_باہرلا, mz_uint level, mz_bool flip, mz_uint8 *plte, صحيح plte_ناپ, mz_uint8 *trns, صحيح trns_ناپ);
#جے_بنا_تعریف MINIZ_SDL_NOUNUSED
MINIZ_STATIC فراغ *tdefl_write_image_منزل_png_file_وچ_حافظہ(ثابت فراغ *pImage, صحيح w, صحيح h, صحيح عدد_chans, صحيح bpl, size_t *p_Len_باہرلا);
#جے_انت

// Output stream interface. The compressor uses this interface to write compressed data. It'll typically be called TDEFL_OUT_BUF_SIZE at a time.
تعريفنوع mz_bool (*tdefl_put_buf_func_ptr)(ثابت فراغ* pBuf, صحيح len, فراغ *pUser);

#جے_بنا_تعریف MINIZ_SDL_NOUNUSED
// tdefl_compress_mem_to_output() compresses a block to an output stream. The above helpers use this function internally.
MINIZ_STATIC mz_bool tdefl_compress_mem_منزل_output(ثابت فراغ *pBuf, size_t buf_len, tdefl_put_buf_func_ptr pPut_buf_func, فراغ *pPut_buf_user, صحيح flags);
#جے_انت

//enum { TDEFL_MAX_HUFF_TABLES = 3, TDEFL_MAX_HUFF_SYMBOLS_0 = 288, TDEFL_MAX_HUFF_SYMBOLS_1 = 32, TDEFL_MAX_HUFF_SYMBOLS_2 = 19, TDEFL_LZ_DICT_SIZE = 32768, TDEFL_LZ_DICT_SIZE_MASK = TDEFL_LZ_DICT_SIZE - 1, TDEFL_MIN_MATCH_LEN = 3, TDEFL_MAX_MATCH_LEN = 258 };
#تعریف_کرو TDEFL_MAX_HUFF_TABLES	3
#تعریف_کرو TDEFL_MAX_HUFF_SYMBOLS_0 288
#تعریف_کرو TDEFL_MAX_HUFF_SYMBOLS_1 32
#تعریف_کرو TDEFL_MAX_HUFF_SYMBOLS_2 19
#تعریف_کرو TDEFL_LZ_DICT_ناپ 32768
#تعریف_کرو TDEFL_LZ_DICT_ناپ_نقاب	( TDEFL_LZ_DICT_ناپ - 1 )
#تعریف_کرو TDEFL_MIN_میل_LEN	3
#تعریف_کرو TDEFL_MAX_میل_LEN 258

// TDEFL_OUT_BUF_SIZE MUST be large enough to hold a single entire compressed output block (using static/fixed Huffman codes).
#إذا TDEFL_LESS_حافظہ
تعداد { TDEFL_LZ_کوڈ_BUF_ناپ = 24 * 1024, TDEFL_باہرلا_BUF_ناپ = (TDEFL_LZ_کوڈ_BUF_ناپ * 13 ) / 10, TDEFL_MAX_HUFF_SYMBOLS = 288, TDEFL_LZ_HASH_بٹ = 12, TDEFL_LEVEL1_HASH_ناپ_نقاب = 4095, TDEFL_LZ_HASH_کھسکاؤ = (TDEFL_LZ_HASH_بٹ + 2) / 3, TDEFL_LZ_HASH_ناپ = 1 << TDEFL_LZ_HASH_بٹ };
#وإلا
تعداد { TDEFL_LZ_کوڈ_BUF_ناپ = 64 * 1024, TDEFL_باہرلا_BUF_ناپ = (TDEFL_LZ_کوڈ_BUF_ناپ * 13 ) / 10, TDEFL_MAX_HUFF_SYMBOLS = 288, TDEFL_LZ_HASH_بٹ = 15, TDEFL_LEVEL1_HASH_ناپ_نقاب = 4095, TDEFL_LZ_HASH_کھسکاؤ = (TDEFL_LZ_HASH_بٹ + 2) / 3, TDEFL_LZ_HASH_ناپ = 1 << TDEFL_LZ_HASH_بٹ };
#جے_انت

// The low-level tdefl functions below may be used directly if the above helper functions aren't flexible enough. The low-level functions don't make any heap allocations, unlike the above helper functions.
تعريفنوع تعداد
{
  TDEFL_حالت_BAD_PARAM = -2,
  TDEFL_حالت_PUT_BUF_FAILED = -1,
  TDEFL_حالت_OKAY = 0,
  TDEFL_حالت_پورا = 1,
} tdefl_حالت;

// Must map to MZ_NO_FLUSH, MZ_SYNC_FLUSH, etc. enums
تعريفنوع تعداد
{
  TDEFL_NO_FLUSH = 0,
  TDEFL_SYNC_FLUSH = 2,
  TDEFL_بھریا_FLUSH = 3,
  TDEFL_انت = 4
} tdefl_flush;

// tdefl's compression state structure.
تعريفنوع بنية
{
  tdefl_put_buf_func_ptr m_pPut_buf_func;
  فراغ *m_pPut_buf_user;
  mz_uint m_flags, m_max_probes[2];
  صحيح m_greedy_parsing;
  mz_uint m_adler32, m_lookahead_pos, m_lookahead_ناپ, m_dict_ناپ;
  mz_uint8 *m_p_LZ_کوڈ_buf, *m_pLZ_flags, *m_pOutput_buf, *m_p_Output_buf_سرا;
  mz_uint m_عدد_flags_بایاں, m_کل_lz_بائٹاں, m_lz_کوڈ_buf_dict_pos, m_بٹ_وچ, m_ثنائی_ہندسہ_بفر;
  mz_uint m_saved_میل_dist, m_saved_میل_len, m_saved_lit, m_output_flush_ofs, m_output_flush_بچیا, m_مکمل, m_بلاک_اشاریہ, m_چاہندا_منزل_انت;
  tdefl_حالت m_prev_return_حالت;
  ثابت فراغ *m_p_وچ_buf;
  فراغ *m_p_باہرلا_buf;
  size_t *m_p_وچ_buf_ناپ, *m_p_باہرلا_buf_ناپ;
  tdefl_flush m_flush;
  ثابت mz_uint8 *m_pSrc;
  size_t m_src_buf_بایاں, m_باہرلا_buf_ofs;
  mz_uint8 m_dict[TDEFL_LZ_DICT_ناپ + TDEFL_MAX_میل_LEN - 1];
  mz_uint16 m_huff_گنتی[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint16 m_huff_codes[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint8 m_huff_کوڈ_sizes[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint8 m_lz_کوڈ_buf[TDEFL_LZ_کوڈ_BUF_ناپ];
  mz_uint16 m_اگلا[TDEFL_LZ_DICT_ناپ];
  mz_uint16 m_hash[TDEFL_LZ_HASH_ناپ];
  mz_uint8 m_output_buf[TDEFL_باہرلا_BUF_ناپ];
} tdefl_compressor;

// Initializes the compressor.
// There is no corresponding deinit() function because the tdefl API's do not dynamically allocate memory.
// pBut_buf_func: If NULL, output data will be supplied to the specified callback. In this case, the user should call the tdefl_compress_buffer() API for compression.
// If pBut_buf_func is NULL the user should always call the tdefl_compress() API.
// flags: See the above enums (TDEFL_HUFFMAN_ONLY, TDEFL_WRITE_ZLIB_HEADER, etc.)
MINIZ_STATIC tdefl_حالت tdefl_init(tdefl_compressor *d, tdefl_put_buf_func_ptr pPut_buf_func, فراغ *pPut_buf_user, صحيح flags);

// Compresses a block of data, consuming as much of the specified input buffer as possible, and writing as much compressed data to the specified output buffer as possible.
MINIZ_STATIC tdefl_حالت tdefl_compress(tdefl_compressor *d, ثابت فراغ *p_وچ_buf, size_t *p_وچ_buf_ناپ, فراغ *p_باہرلا_buf, size_t *p_باہرلا_buf_ناپ, tdefl_flush flush);

// tdefl_compress_buffer() is only usable when the tdefl_init() is called with a non-NULL tdefl_put_buf_func_ptr.
// tdefl_compress_buffer() always consumes the entire input buffer.
MINIZ_STATIC tdefl_حالت tdefl_compress_بفر(tdefl_compressor *d, ثابت فراغ *p_وچ_buf, size_t وچ_buf_ناپ, tdefl_flush flush);

#جے_بنا_تعریف MINIZ_SDL_NOUNUSED
MINIZ_STATIC tdefl_حالت tdefl_get_prev_return_حالت(tdefl_compressor *d);
MINIZ_STATIC mz_uint32 tdefl_get_adler32(tdefl_compressor *d);
#جے_انت

// Can't use tdefl_create_comp_flags_from_zip_params if MINIZ_NO_ZLIB_APIS isn't defined, because it uses some of its macros.
#جے_بنا_تعریف MINIZ_NO_ZLIB_APIS
// Create tdefl_compress() flags given zlib-style compression parameters.
// level may range from [0,10] (where 10 is absolute max compression, but may be much slower on some files)
// window_bits may be -15 (raw deflate) or 15 (zlib)
// strategy may be either MZ_DEFAULT_STRATEGY, MZ_FILTERED, MZ_HUFFMAN_ONLY, MZ_RLE, or MZ_FIXED
MINIZ_STATIC mz_uint tdefl_create_comp_flags_from_zip_params(صحيح level, صحيح کھڑکی_بٹ, صحيح strategy);
#جے_انت // #ifndef MINIZ_NO_ZLIB_APIS

#جے_انت /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#جے_انت // MINIZ_HEADER_INCLUDED

// ------------------- End of Header: Implementation follows. (If you only want the header, define MINIZ_HEADER_FILE_ONLY.)

#جے_بنا_تعریف MINIZ_سرخی_FILE_ONLY

#جے_تعریف_شدہ _MSC_VER
#ہدایت warning (ڈالو)
#ہدایت warning (disable:4505) // unreferenced local function has been removed
#جے_انت

تعريفنوع بنانشانی حرف mz_validate_uint16[حجم(mz_uint16)==2 ? 1 : -1];
تعريفنوع بنانشانی حرف mz_validate_uint32[حجم(mz_uint32)==4 ? 1 : -1];
تعريفنوع بنانشانی حرف mz_validate_uint64[حجم(mz_uint64)==8 ? 1 : -1];

/*#include <string.h>*/

#جے_بنا_تعریف MZ_ASSERT
#ضمن <assert.h>
#تعریف_کرو MZ_ASSERT(x) أكد(x)
#جے_انت

#جے_تعریف_شدہ MINIZ_NO_MALLOC
  #تعریف_کرو MZ_MALLOC(x) عدم
  #تعریف_کرو MZ_FREE(x) (فراغ)x, ((فراغ)0)
  #تعریف_کرو MZ_REALLOC(p, x) عدم
#وإلاإذا defined(MINIZ_SDL_MALLOC)
  #تعریف_کرو MZ_MALLOC(x) SDL_malloc(x)
  #تعریف_کرو MZ_FREE(x) SDL_free(x)
  #تعریف_کرو MZ_REALLOC(p, x) SDL_realloc(p, x)
#وإلا
  #تعریف_کرو MZ_MALLOC(x) حافظہ_دیو(x)
  #تعریف_کرو MZ_FREE(x) حرر(x)
  #تعریف_کرو MZ_REALLOC(p, x) realloc(p, x)
#جے_انت

#تعریف_کرو MZ_MAX(a,b) (((a)>(b))?(a):(b))
#تعریف_کرو MZ_MIN(a,b) (((a)<(b))?(a):(b))
#تعریف_کرو MZ_CLEAR_OBJ(obj) memset(&(obj), 0, حجم(obj))
#تعریف_کرو MZ_CLEAR_ARR(obj) memset((obj), 0, حجم(obj))
#تعریف_کرو MZ_CLEAR_PTR(obj) memset((obj), 0, حجم(*obj))

#إذا MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  #تعریف_کرو MZ_READ_LE16(p) *((ثابت mz_uint16 *)(p))
  #تعریف_کرو MZ_READ_LE32(p) *((ثابت mz_uint32 *)(p))
#وإلا
  #تعریف_کرو MZ_READ_LE16(p) ((mz_uint32)(((ثابت mz_uint8 *)(p))[0]) | ((mz_uint32)(((ثابت mz_uint8 *)(p))[1]) << 8U))
  #تعریف_کرو MZ_READ_LE32(p) ((mz_uint32)(((ثابت mz_uint8 *)(p))[0]) | ((mz_uint32)(((ثابت mz_uint8 *)(p))[1]) << 8U) | ((mz_uint32)(((ثابت mz_uint8 *)(p))[2]) << 16U) | ((mz_uint32)(((ثابت mz_uint8 *)(p))[3]) << 24U))
#جے_انت

#جے_تعریف_شدہ _MSC_VER
  #تعریف_کرو MZ_FORCEINLINE __forceinline
#وإلاإذا defined(__GNUC__)
  #تعریف_کرو MZ_FORCEINLINE مضمن __attribute__((__always_inline__))
#وإلا
  #تعریف_کرو MZ_FORCEINLINE مضمن
#جے_انت

#جے_تعریف_شدہ __cplusplus
  خارجي "C" {
#جے_انت

// ------------------- zlib-style API's

mz_ulong mz_adler32(mz_ulong adler, ثابت بنانشانی حرف *ptr, size_t buf_len)
{
  mz_uint32 i, s1 = (mz_uint32)(adler & 0xffff), s2 = (mz_uint32)(adler >> 16); size_t بلاک_len = buf_len % 5552;
  إذا (!ptr) أرجع MZ_ADLER32_INIT;
  طالما (buf_len) {
    لكل (i = 0; i + 7 < بلاک_len; i += 8, ptr += 8) {
      s1 += ptr[0]; s2 += s1; s1 += ptr[1]; s2 += s1; s1 += ptr[2]; s2 += s1; s1 += ptr[3]; s2 += s1;
      s1 += ptr[4]; s2 += s1; s1 += ptr[5]; s2 += s1; s1 += ptr[6]; s2 += s1; s1 += ptr[7]; s2 += s1;
    }
    لكل ( ; i < بلاک_len; ++i) { s1 += *ptr++; s2 += s1; }
    s1 %= 65521U; s2 %= 65521U; buf_len -= بلاک_len; بلاک_len = 5552;
  }
  أرجع (s2 << 16) + s1;
}

// Karl Malbrain's compact CRC-32. See "A compact CCITT crc16 and crc32 C implementation that balances processor cache usage against speed": http://www.geocities.com/malbrain/
mz_ulong mz_چکری_جانچ_32(mz_ulong چکری_جانچ, ثابت mz_uint8 *ptr, size_t buf_len)
{
  ساكن ثابت mz_uint32 s_چکری_جانچ_32[16] = { 0, 0x1db71064, 0x3b6e20c8, 0x26d930ac, 0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
    0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c, 0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c };
  mz_uint32 crcu32 = (mz_uint32)چکری_جانچ;
  إذا (!ptr) أرجع MZ_چکری_جانچ_32_INIT;
  crcu32 = ~crcu32; طالما (buf_len--) { mz_uint8 b = *ptr++; crcu32 = (crcu32 >> 4) ^ s_چکری_جانچ_32[(crcu32 & 0xF) ^ (b & 0xF)]; crcu32 = (crcu32 >> 4) ^ s_چکری_جانچ_32[(crcu32 & 0xF) ^ (b >> 4)]; }
  أرجع ~crcu32;
}

MINIZ_STATIC فراغ mz_free(فراغ *p)
{
  MZ_FREE(p);
}

#جے_بنا_تعریف MINIZ_NO_ZLIB_APIS

ساكن فراغ *def_alloc_func(فراغ *opaque, size_t اشیاء, size_t ناپ) { (فراغ)opaque, (فراغ)اشیاء, (فراغ)ناپ; أرجع MZ_MALLOC(اشیاء * ناپ); }
ساكن فراغ def_free_func(فراغ *opaque, فراغ *پتہ) { (فراغ)opaque, (فراغ)پتہ; MZ_FREE(پتہ); }
ساكن فراغ *def_realloc_func(فراغ *opaque, فراغ *پتہ, size_t اشیاء, size_t ناپ) { (فراغ)opaque, (فراغ)پتہ, (فراغ)اشیاء, (فراغ)ناپ; أرجع MZ_REALLOC(پتہ, اشیاء * ناپ); }

ثابت حرف *mz_نسخہ(فراغ)
{
  أرجع MZ_نسخہ;
}

#جے_بنا_تعریف MINIZ_NO_DEFLATE_APIS

صحيح mz_deflateInit(mz_streamp p_دھارا, صحيح level)
{
  أرجع mz_deflateInit2(p_دھارا, level, MZ_DEFLATED, MZ_DEFAULT_کھڑکی_بٹ, 9, MZ_DEFAULT_STRATEGY);
}

صحيح mz_deflateInit2(mz_streamp p_دھارا, صحيح level, صحيح طریقہ, صحيح کھڑکی_بٹ, صحيح mem_level, صحيح strategy)
{
  tdefl_compressor *pComp;
  mz_uint comp_flags = TDEFL_COMPUTE_ADLER32 | tdefl_create_comp_flags_from_zip_params(level, کھڑکی_بٹ, strategy);

  إذا (!p_دھارا) أرجع MZ_دھارا_ERROR;
  إذا ((طریقہ != MZ_DEFLATED) || ((mem_level < 1) || (mem_level > 9)) || ((کھڑکی_بٹ != MZ_DEFAULT_کھڑکی_بٹ) && (-کھڑکی_بٹ != MZ_DEFAULT_کھڑکی_بٹ))) أرجع MZ_PARAM_ERROR;

  p_دھارا->انکڑے_type = 0;
  p_دھارا->adler = MZ_ADLER32_INIT;
  p_دھارا->پیغام = عدم;
  p_دھارا->reserved = 0;
  p_دھارا->کل_وچ = 0;
  p_دھارا->کل_باہرلا = 0;
  إذا (!p_دھارا->zalloc) p_دھارا->zalloc = def_alloc_func;
  إذا (!p_دھارا->zfree) p_دھارا->zfree = def_free_func;

  pComp = (tdefl_compressor *)p_دھارا->zalloc(p_دھارا->opaque, 1, حجم(tdefl_compressor));
  إذا (!pComp)
    أرجع MZ_MEM_ERROR;

  p_دھارا->state = (بنية mz_اندرونی_state *)pComp;

  إذا (tdefl_init(pComp, عدم, عدم, comp_flags) != TDEFL_حالت_OKAY)
  {
    mz_deflate_سرا(p_دھارا);
    أرجع MZ_PARAM_ERROR;
  }

  أرجع MZ_OK;
}

صحيح mz_deflateReset(mz_streamp p_دھارا)
{
  إذا ((!p_دھارا) || (!p_دھارا->state) || (!p_دھارا->zalloc) || (!p_دھارا->zfree)) أرجع MZ_دھارا_ERROR;
  p_دھارا->کل_وچ = p_دھارا->کل_باہرلا = 0;
  tdefl_init((tdefl_compressor*)p_دھارا->state, عدم, عدم, ((tdefl_compressor*)p_دھارا->state)->m_flags);
  أرجع MZ_OK;
}

صحيح mz_deflate(mz_streamp p_دھارا, صحيح flush)
{
  size_t وچ_بائٹاں, باہرلا_بائٹاں;
  mz_ulong orig_کل_وچ, orig_کل_باہرلا;
  صحيح mz_حالت = MZ_OK;

  إذا ((!p_دھارا) || (!p_دھارا->state) || (flush < 0) || (flush > MZ_انت) || (!p_دھارا->اگلا_باہرلا)) أرجع MZ_دھارا_ERROR;
  إذا (!p_دھارا->avail_باہرلا) أرجع MZ_BUF_ERROR;

  إذا (flush == MZ_PARTIAL_FLUSH) flush = MZ_SYNC_FLUSH;

  إذا (((tdefl_compressor*)p_دھارا->state)->m_prev_return_حالت == TDEFL_حالت_پورا)
    أرجع (flush == MZ_انت) ? MZ_دھارا_سرا : MZ_BUF_ERROR;

  orig_کل_وچ = p_دھارا->کل_وچ; orig_کل_باہرلا = p_دھارا->کل_باہرلا;
  لكل ( ; ; )
  {
    tdefl_حالت defl_حالت;
    وچ_بائٹاں = p_دھارا->avail_وچ; باہرلا_بائٹاں = p_دھارا->avail_باہرلا;

    defl_حالت = tdefl_compress((tdefl_compressor*)p_دھارا->state, p_دھارا->اگلا_وچ, &وچ_بائٹاں, p_دھارا->اگلا_باہرلا, &باہرلا_بائٹاں, (tdefl_flush)flush);
    p_دھارا->اگلا_وچ += (mz_uint)وچ_بائٹاں; p_دھارا->avail_وچ -= (mz_uint)وچ_بائٹاں;
    p_دھارا->کل_وچ += (mz_uint)وچ_بائٹاں; p_دھارا->adler = tdefl_get_adler32((tdefl_compressor*)p_دھارا->state);

    p_دھارا->اگلا_باہرلا += (mz_uint)باہرلا_بائٹاں; p_دھارا->avail_باہرلا -= (mz_uint)باہرلا_بائٹاں;
    p_دھارا->کل_باہرلا += (mz_uint)باہرلا_بائٹاں;

    إذا (defl_حالت < 0)
    {
      mz_حالت = MZ_دھارا_ERROR;
      اكسر;
    }
    وإلا إذا (defl_حالت == TDEFL_حالت_پورا)
    {
      mz_حالت = MZ_دھارا_سرا;
      اكسر;
    }
    وإلا إذا (!p_دھارا->avail_باہرلا)
      اكسر;
    وإلا إذا ((!p_دھارا->avail_وچ) && (flush != MZ_انت))
    {
      إذا ((flush) || (p_دھارا->کل_وچ != orig_کل_وچ) || (p_دھارا->کل_باہرلا != orig_کل_باہرلا))
        اكسر;
      أرجع MZ_BUF_ERROR; // Can't make forward progress without some input.
    }
  }
  أرجع mz_حالت;
}

صحيح mz_deflate_سرا(mz_streamp p_دھارا)
{
  إذا (!p_دھارا) أرجع MZ_دھارا_ERROR;
  إذا (p_دھارا->state)
  {
    p_دھارا->zfree(p_دھارا->opaque, p_دھارا->state);
    p_دھارا->state = عدم;
  }
  أرجع MZ_OK;
}

mz_ulong mz_deflateBound(mz_streamp p_دھارا, mz_ulong سروت_len)
{
  (فراغ)p_دھارا;
  // This is really over conservative. (And lame, but it's actually pretty tricky to compute a true upper bound given the way tdefl's blocking works.)
  أرجع MZ_MAX(128 + (سروت_len * 110) / 100, 128 + سروت_len + ((سروت_len / (31 * 1024)) + 1) * 5);
}

صحيح mz_compress2(بنانشانی حرف *pDest, mz_ulong *pDest_len, ثابت بنانشانی حرف *p_سروت, mz_ulong سروت_len, صحيح level)
{
  صحيح حالت;
  mz_دھارا دھارا;
  memset(&دھارا, 0, حجم(دھارا));

  // In case mz_ulong is 64-bits (argh I hate longs).
  إذا ((سروت_len | *pDest_len) > 0xFFFFFFFFU) أرجع MZ_PARAM_ERROR;

  دھارا.اگلا_وچ = p_سروت;
  دھارا.avail_وچ = (mz_uint32)سروت_len;
  دھارا.اگلا_باہرلا = pDest;
  دھارا.avail_باہرلا = (mz_uint32)*pDest_len;

  حالت = mz_deflateInit(&دھارا, level);
  إذا (حالت != MZ_OK) أرجع حالت;

  حالت = mz_deflate(&دھارا, MZ_انت);
  إذا (حالت != MZ_دھارا_سرا)
  {
    mz_deflate_سرا(&دھارا);
    أرجع (حالت == MZ_OK) ? MZ_BUF_ERROR : حالت;
  }

  *pDest_len = دھارا.کل_باہرلا;
  أرجع mz_deflate_سرا(&دھارا);
}

صحيح mz_compress(بنانشانی حرف *pDest, mz_ulong *pDest_len, ثابت بنانشانی حرف *p_سروت, mz_ulong سروت_len)
{
  أرجع mz_compress2(pDest, pDest_len, p_سروت, سروت_len, MZ_DEFAULT_COMPRESSION);
}

mz_ulong mz_compressBound(mz_ulong سروت_len)
{
  أرجع mz_deflateBound(عدم, سروت_len);
}

#جے_انت /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#جے_بنا_تعریف MINIZ_NO_INFLATE_APIS

تعريفنوع بنية
{
  tinfl_decompressor m_decomp;
  mz_uint m_dict_ofs, m_dict_avail, m_پہلا_call, m_has_flushed; صحيح m_کھڑکی_بٹ;
  mz_uint8 m_dict[TINFL_LZ_DICT_ناپ];
  tinfl_حالت m_آخری_حالت;
} inflate_state;

صحيح mz_inflateInit2(mz_streamp p_دھارا, صحيح کھڑکی_بٹ)
{
  inflate_state *pDecomp;
  إذا (!p_دھارا) أرجع MZ_دھارا_ERROR;
  إذا ((کھڑکی_بٹ != MZ_DEFAULT_کھڑکی_بٹ) && (-کھڑکی_بٹ != MZ_DEFAULT_کھڑکی_بٹ)) أرجع MZ_PARAM_ERROR;

  p_دھارا->انکڑے_type = 0;
  p_دھارا->adler = 0;
  p_دھارا->پیغام = عدم;
  p_دھارا->کل_وچ = 0;
  p_دھارا->کل_باہرلا = 0;
  p_دھارا->reserved = 0;
  إذا (!p_دھارا->zalloc) p_دھارا->zalloc = def_alloc_func;
  إذا (!p_دھارا->zfree) p_دھارا->zfree = def_free_func;

  pDecomp = (inflate_state*)p_دھارا->zalloc(p_دھارا->opaque, 1, حجم(inflate_state));
  إذا (!pDecomp) أرجع MZ_MEM_ERROR;

  p_دھارا->state = (بنية mz_اندرونی_state *)pDecomp;

  tinfl_init(&pDecomp->m_decomp);
  pDecomp->m_dict_ofs = 0;
  pDecomp->m_dict_avail = 0;
  pDecomp->m_آخری_حالت = TINFL_حالت_NEEDS_ہور_داخلہ;
  pDecomp->m_پہلا_call = 1;
  pDecomp->m_has_flushed = 0;
  pDecomp->m_کھڑکی_بٹ = کھڑکی_بٹ;

  أرجع MZ_OK;
}

صحيح mz_inflateInit(mz_streamp p_دھارا)
{
   أرجع mz_inflateInit2(p_دھارا, MZ_DEFAULT_کھڑکی_بٹ);
}

صحيح mz_inflate(mz_streamp p_دھارا, صحيح flush)
{
  inflate_state* pState;
  mz_uint n, پہلا_call, decomp_flags = TINFL_FLAG_COMPUTE_ADLER32;
  size_t وچ_بائٹاں, باہرلا_بائٹاں, orig_avail_وچ;
  tinfl_حالت حالت;

  إذا ((!p_دھارا) || (!p_دھارا->state)) أرجع MZ_دھارا_ERROR;
  إذا (flush == MZ_PARTIAL_FLUSH) flush = MZ_SYNC_FLUSH;
  إذا ((flush) && (flush != MZ_SYNC_FLUSH) && (flush != MZ_انت)) أرجع MZ_دھارا_ERROR;

  pState = (inflate_state*)p_دھارا->state;
  إذا (pState->m_کھڑکی_بٹ > 0) decomp_flags |= TINFL_FLAG_PARSE_ZLIB_سرخی;
  orig_avail_وچ = p_دھارا->avail_وچ;

  پہلا_call = pState->m_پہلا_call; pState->m_پہلا_call = 0;
  إذا (pState->m_آخری_حالت < 0) أرجع MZ_انکڑے_ERROR;

  إذا (pState->m_has_flushed && (flush != MZ_انت)) أرجع MZ_دھارا_ERROR;
  pState->m_has_flushed |= (flush == MZ_انت);

  إذا ((flush == MZ_انت) && (پہلا_call))
  {
    // MZ_FINISH on the first call implies that the input and output buffers are large enough to hold the entire compressed/decompressed file.
    decomp_flags |= TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF;
    وچ_بائٹاں = p_دھارا->avail_وچ; باہرلا_بائٹاں = p_دھارا->avail_باہرلا;
    حالت = tinfl_decompress(&pState->m_decomp, p_دھارا->اگلا_وچ, &وچ_بائٹاں, p_دھارا->اگلا_باہرلا, p_دھارا->اگلا_باہرلا, &باہرلا_بائٹاں, decomp_flags);
    pState->m_آخری_حالت = حالت;
    p_دھارا->اگلا_وچ += (mz_uint)وچ_بائٹاں; p_دھارا->avail_وچ -= (mz_uint)وچ_بائٹاں; p_دھارا->کل_وچ += (mz_uint)وچ_بائٹاں;
    p_دھارا->adler = tinfl_get_adler32(&pState->m_decomp);
    p_دھارا->اگلا_باہرلا += (mz_uint)باہرلا_بائٹاں; p_دھارا->avail_باہرلا -= (mz_uint)باہرلا_بائٹاں; p_دھارا->کل_باہرلا += (mz_uint)باہرلا_بائٹاں;

    إذا (حالت < 0)
      أرجع MZ_انکڑے_ERROR;
    وإلا إذا (حالت != TINFL_حالت_پورا)
    {
      pState->m_آخری_حالت = TINFL_حالت_FAILED;
      أرجع MZ_BUF_ERROR;
    }
    أرجع MZ_دھارا_سرا;
  }
  // flush != MZ_FINISH then we must assume there's more input.
  إذا (flush != MZ_انت) decomp_flags |= TINFL_FLAG_HAS_ہور_داخلہ;

  إذا (pState->m_dict_avail)
  {
    n = MZ_MIN(pState->m_dict_avail, p_دھارا->avail_باہرلا);
    حافظہ_نقل(p_دھارا->اگلا_باہرلا, pState->m_dict + pState->m_dict_ofs, n);
    p_دھارا->اگلا_باہرلا += n; p_دھارا->avail_باہرلا -= n; p_دھارا->کل_باہرلا += n;
    pState->m_dict_avail -= n; pState->m_dict_ofs = (pState->m_dict_ofs + n) & (TINFL_LZ_DICT_ناپ - 1);
    أرجع ((pState->m_آخری_حالت == TINFL_حالت_پورا) && (!pState->m_dict_avail)) ? MZ_دھارا_سرا : MZ_OK;
  }

  لكل ( ; ; )
  {
    وچ_بائٹاں = p_دھارا->avail_وچ;
    باہرلا_بائٹاں = TINFL_LZ_DICT_ناپ - pState->m_dict_ofs;

    حالت = tinfl_decompress(&pState->m_decomp, p_دھارا->اگلا_وچ, &وچ_بائٹاں, pState->m_dict, pState->m_dict + pState->m_dict_ofs, &باہرلا_بائٹاں, decomp_flags);
    pState->m_آخری_حالت = حالت;

    p_دھارا->اگلا_وچ += (mz_uint)وچ_بائٹاں; p_دھارا->avail_وچ -= (mz_uint)وچ_بائٹاں;
    p_دھارا->کل_وچ += (mz_uint)وچ_بائٹاں; p_دھارا->adler = tinfl_get_adler32(&pState->m_decomp);

    pState->m_dict_avail = (mz_uint)باہرلا_بائٹاں;

    n = MZ_MIN(pState->m_dict_avail, p_دھارا->avail_باہرلا);
    حافظہ_نقل(p_دھارا->اگلا_باہرلا, pState->m_dict + pState->m_dict_ofs, n);
    p_دھارا->اگلا_باہرلا += n; p_دھارا->avail_باہرلا -= n; p_دھارا->کل_باہرلا += n;
    pState->m_dict_avail -= n; pState->m_dict_ofs = (pState->m_dict_ofs + n) & (TINFL_LZ_DICT_ناپ - 1);

    إذا (حالت < 0)
       أرجع MZ_انکڑے_ERROR; // Stream is corrupted (there could be some uncompressed data left in the output dictionary - oh well).
    وإلا إذا ((حالت == TINFL_حالت_NEEDS_ہور_داخلہ) && (!orig_avail_وچ))
      أرجع MZ_BUF_ERROR; // Signal caller that we can't make forward progress without supplying more input or by setting flush to MZ_FINISH.
    وإلا إذا (flush == MZ_انت)
    {
       // The output buffer MUST be large to hold the remaining uncompressed data when flush==MZ_FINISH.
       إذا (حالت == TINFL_حالت_پورا)
          أرجع pState->m_dict_avail ? MZ_BUF_ERROR : MZ_دھارا_سرا;
       // status here must be TINFL_STATUS_HAS_MORE_OUTPUT, which means there's at least 1 more byte on the way. If there's no more room left in the output buffer then something is wrong.
       وإلا إذا (!p_دھارا->avail_باہرلا)
          أرجع MZ_BUF_ERROR;
    }
    وإلا إذا ((حالت == TINFL_حالت_پورا) || (!p_دھارا->avail_وچ) || (!p_دھارا->avail_باہرلا) || (pState->m_dict_avail))
      اكسر;
  }

  أرجع ((حالت == TINFL_حالت_پورا) && (!pState->m_dict_avail)) ? MZ_دھارا_سرا : MZ_OK;
}

صحيح mz_inflate_سرا(mz_streamp p_دھارا)
{
  إذا (!p_دھارا)
    أرجع MZ_دھارا_ERROR;
  إذا (p_دھارا->state)
  {
    p_دھارا->zfree(p_دھارا->opaque, p_دھارا->state);
    p_دھارا->state = عدم;
  }
  أرجع MZ_OK;
}

صحيح mz_uncompress(بنانشانی حرف *pDest, mz_ulong *pDest_len, ثابت بنانشانی حرف *p_سروت, mz_ulong سروت_len)
{
  mz_دھارا دھارا;
  صحيح حالت;
  memset(&دھارا, 0, حجم(دھارا));

  // In case mz_ulong is 64-bits (argh I hate longs).
  إذا ((سروت_len | *pDest_len) > 0xFFFFFFFFU) أرجع MZ_PARAM_ERROR;

  دھارا.اگلا_وچ = p_سروت;
  دھارا.avail_وچ = (mz_uint32)سروت_len;
  دھارا.اگلا_باہرلا = pDest;
  دھارا.avail_باہرلا = (mz_uint32)*pDest_len;

  حالت = mz_inflateInit(&دھارا);
  إذا (حالت != MZ_OK)
    أرجع حالت;

  حالت = mz_inflate(&دھارا, MZ_انت);
  إذا (حالت != MZ_دھارا_سرا)
  {
    mz_inflate_سرا(&دھارا);
    أرجع ((حالت == MZ_BUF_ERROR) && (!دھارا.avail_وچ)) ? MZ_انکڑے_ERROR : حالت;
  }
  *pDest_len = دھارا.کل_باہرلا;

  أرجع mz_inflate_سرا(&دھارا);
}

#جے_انت /*#ifndef MINIZ_NO_INFLATE_APIS*/

ثابت حرف *mz_error(صحيح err)
{
  ساكن بنية { صحيح m_err; ثابت حرف *m_pDesc; } s_error_descs[] =
  {
    { MZ_OK, "" }, { MZ_دھارا_سرا, "stream end" }, { MZ_NEED_DICT, "need dictionary" }, { MZ_ERRNO, "file error" }, { MZ_دھارا_ERROR, "stream error" },
    { MZ_انکڑے_ERROR, "data error" }, { MZ_MEM_ERROR, "out of memory" }, { MZ_BUF_ERROR, "buf error" }, { MZ_نسخہ_ERROR, "version error" }, { MZ_PARAM_ERROR, "parameter error" }
  };
  mz_uint i; لكل (i = 0; i < حجم(s_error_descs) / حجم(s_error_descs[0]); ++i) إذا (s_error_descs[i].m_err == err) أرجع s_error_descs[i].m_pDesc;
  أرجع عدم;
}

#جے_انت //MINIZ_NO_ZLIB_APIS

// ------------------- Low-level Decompression (completely independent from all compression API's)
#جے_بنا_تعریف MINIZ_NO_INFLATE_APIS

#تعریف_کرو TINFL_MEMCPY(d, s, l) حافظہ_نقل(d, s, l)
#تعریف_کرو TINFL_MEMSET(p, c, l) memset(p, c, l)

#تعریف_کرو TINFL_CR_BEGIN بدل(r->m_state) { حالة 0:
#تعریف_کرو TINFL_CR_RETURN(state_اشاریہ, نتیجہ) افعل { حالت = نتیجہ; r->m_state = state_اشاریہ; اذهب common_exit; حالة state_اشاریہ:; } MZ_MACRO_سرا
#تعریف_کرو TINFL_CR_RETURN_FOREVER(state_اشاریہ, نتیجہ) افعل { لكل ( ; ; ) { TINFL_CR_RETURN(state_اشاریہ, نتیجہ); } } MZ_MACRO_سرا
#تعریف_کرو TINFL_CR_انت }

// TODO: If the caller has indicated that there's no more input, and we attempt to read beyond the input buf, then something is wrong with the input because the inflator never
// reads ahead more than it needs to. Currently TINFL_GET_BYTE() pads the end of the stream with 0's in this scenario.
#تعریف_کرو TINFL_GET_BYTE(state_اشاریہ, c) افعل { \
  إذا (p_وچ_buf_cur >= p_وچ_buf_سرا) { \
    لكل ( ; ; ) { \
      إذا (decomp_flags & TINFL_FLAG_HAS_ہور_داخلہ) { \
        TINFL_CR_RETURN(state_اشاریہ, TINFL_حالت_NEEDS_ہور_داخلہ); \
        إذا (p_وچ_buf_cur < p_وچ_buf_سرا) { \
          c = *p_وچ_buf_cur++; \
          اكسر; \
        } \
      } وإلا { \
        c = 0; \
        اكسر; \
      } \
    } \
  } وإلا c = *p_وچ_buf_cur++; } MZ_MACRO_سرا

#تعریف_کرو TINFL_NEED_بٹ(state_اشاریہ, n) افعل { mz_uint c; TINFL_GET_BYTE(state_اشاریہ, c); ثنائی_ہندسہ_buf |= (((tinfl_ثنائی_ہندسہ_buf_t)c) << عدد_بٹ); عدد_بٹ += 8; } طالما (عدد_بٹ < (mz_uint)(n))
#تعریف_کرو TINFL_SKIP_بٹ(state_اشاریہ, n) افعل { إذا (عدد_بٹ < (mz_uint)(n)) { TINFL_NEED_بٹ(state_اشاریہ, n); } ثنائی_ہندسہ_buf >>= (n); عدد_بٹ -= (n); } MZ_MACRO_سرا
#تعریف_کرو TINFL_GET_بٹ(state_اشاریہ, b, n) افعل { إذا (عدد_بٹ < (mz_uint)(n)) { TINFL_NEED_بٹ(state_اشاریہ, n); } b = ثنائی_ہندسہ_buf & ((1 << (n)) - 1); ثنائی_ہندسہ_buf >>= (n); عدد_بٹ -= (n); } MZ_MACRO_سرا

// TINFL_HUFF_BITBUF_FILL() is only used rarely, when the number of bytes remaining in the input buffer falls below 2.
// It reads just enough bytes from the input stream that are needed to decode the next Huffman code (and absolutely no more). It works by trying to fully decode a
// Huffman code by using whatever bits are currently present in the bit buffer. If this fails, it reads another byte, and tries again until it succeeds or until the
// bit buffer contains >=15 bits (deflate's max. Huffman code size).
#تعریف_کرو TINFL_HUFF_BITBUF_FILL(state_اشاریہ, pHuff) \
  افعل { \
    عارضی = (pHuff)->m_look_اتے[ثنائی_ہندسہ_buf & (TINFL_FAST_LOOKUP_ناپ - 1)]; \
    إذا (عارضی >= 0) { \
      کوڈ_len = عارضی >> 9; \
      إذا ((کوڈ_len) && (عدد_بٹ >= کوڈ_len)) \
          اكسر; \
    } وإلا إذا (عدد_بٹ > TINFL_FAST_LOOKUP_بٹ) { \
       کوڈ_len = TINFL_FAST_LOOKUP_بٹ; \
       افعل { \
          عارضی = (pHuff)->m_درخت[~عارضی + ((ثنائی_ہندسہ_buf >> کوڈ_len++) & 1)]; \
       } طالما ((عارضی < 0) && (عدد_بٹ >= (کوڈ_len + 1))); \
       إذا (عارضی >= 0) اكسر; \
    } \
    TINFL_GET_BYTE(state_اشاریہ, c); \
    ثنائی_ہندسہ_buf |= (((tinfl_ثنائی_ہندسہ_buf_t)c) << عدد_بٹ); \
    عدد_بٹ += 8; \
  } طالما (عدد_بٹ < 15);

// TINFL_HUFF_DECODE() decodes the next Huffman coded symbol. It's more complex than you would initially expect because the zlib API expects the decompressor to never read
// beyond the final byte of the deflate stream. (In other words, when this macro wants to read another byte from the input, it REALLY needs another byte in order to fully
// decode the next Huffman code.) Handling this properly is particularly important on raw deflate (non-zlib) streams, which aren't followed by a byte aligned adler-32.
// The slow path is only executed at the very end of the input buffer.
#تعریف_کرو TINFL_HUFF_DECODE(state_اشاریہ, sym, pHuff) افعل { \
  صحيح عارضی; mz_uint کوڈ_len, c; \
  إذا (عدد_بٹ < 15) { \
    إذا ((p_وچ_buf_سرا - p_وچ_buf_cur) < 2) { \
       TINFL_HUFF_BITBUF_FILL(state_اشاریہ, pHuff); \
    } وإلا { \
       ثنائی_ہندسہ_buf |= (((tinfl_ثنائی_ہندسہ_buf_t)p_وچ_buf_cur[0]) << عدد_بٹ) | (((tinfl_ثنائی_ہندسہ_buf_t)p_وچ_buf_cur[1]) << (عدد_بٹ + 8)); p_وچ_buf_cur += 2; عدد_بٹ += 16; \
    } \
  } \
  إذا ((عارضی = (pHuff)->m_look_اتے[ثنائی_ہندسہ_buf & (TINFL_FAST_LOOKUP_ناپ - 1)]) >= 0) \
    کوڈ_len = عارضی >> 9, عارضی &= 511; \
  وإلا { \
    کوڈ_len = TINFL_FAST_LOOKUP_بٹ; افعل { عارضی = (pHuff)->m_درخت[~عارضی + ((ثنائی_ہندسہ_buf >> کوڈ_len++) & 1)]; } طالما (عارضی < 0); \
  } sym = عارضی; ثنائی_ہندسہ_buf >>= کوڈ_len; عدد_بٹ -= کوڈ_len; } MZ_MACRO_سرا

tinfl_حالت tinfl_decompress(tinfl_decompressor *r, ثابت mz_uint8 *p_وچ_buf_اگلا, size_t *p_وچ_buf_ناپ, mz_uint8 *p_باہرلا_buf_شروع, mz_uint8 *p_باہرلا_buf_اگلا, size_t *p_باہرلا_buf_ناپ, ثابت mz_uint32 decomp_flags)
{
  ساكن ثابت صحيح s_لمائی_ادھار[31] = { 3,4,5,6,7,8,9,10,11,13, 15,17,19,23,27,31,35,43,51,59, 67,83,99,115,131,163,195,227,258,0,0 };
  ساكن ثابت صحيح s_لمائی_extra[31]= { 0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,0,0,0 };
  ساكن ثابت صحيح s_dist_ادھار[32] = { 1,2,3,4,5,7,9,13,17,25,33,49,65,97,129,193, 257,385,513,769,1025,1537,2049,3073,4097,6145,8193,12289,16385,24577,0,0};
  ساكن ثابت صحيح s_dist_extra[32] = { 0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13};
  ساكن ثابت mz_uint8 s_لمائی_dezigzag[19] = { 16,17,18,0,8,7,9,6,10,5,11,4,12,3,13,2,14,1,15 };
  ساكن ثابت صحيح s_min_جدول_sizes[3] = { 257, 1, 4 };

  tinfl_حالت حالت = TINFL_حالت_FAILED; mz_uint32 عدد_بٹ, dist, counter, عدد_extra; tinfl_ثنائی_ہندسہ_buf_t ثنائی_ہندسہ_buf;
  ثابت mz_uint8 *p_وچ_buf_cur = p_وچ_buf_اگلا, *ثابت p_وچ_buf_سرا = p_وچ_buf_اگلا + *p_وچ_buf_ناپ;
  mz_uint8 *p_باہرلا_buf_cur = p_باہرلا_buf_اگلا, *ثابت p_باہرلا_buf_سرا = p_باہرلا_buf_اگلا + *p_باہرلا_buf_ناپ;
  size_t باہرلا_buf_ناپ_نقاب = (decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF) ? (size_t)-1 : ((p_باہرلا_buf_اگلا - p_باہرلا_buf_شروع) + *p_باہرلا_buf_ناپ) - 1, dist_from_باہرلا_buf_شروع;

  // Ensure the output buffer's size is a power of 2, unless the output buffer is large enough to hold the entire output file (in which case it doesn't matter).
  إذا (((باہرلا_buf_ناپ_نقاب + 1) & باہرلا_buf_ناپ_نقاب) || (p_باہرلا_buf_اگلا < p_باہرلا_buf_شروع)) { *p_وچ_buf_ناپ = *p_باہرلا_buf_ناپ = 0; أرجع TINFL_حالت_BAD_PARAM; }

  عدد_بٹ = r->m_عدد_بٹ; ثنائی_ہندسہ_buf = r->m_ثنائی_ہندسہ_buf; dist = r->m_dist; counter = r->m_counter; عدد_extra = r->m_عدد_extra; dist_from_باہرلا_buf_شروع = r->m_dist_from_باہرلا_buf_شروع;
  TINFL_CR_BEGIN

  ثنائی_ہندسہ_buf = عدد_بٹ = dist = counter = عدد_extra = r->m_zhdr0 = r->m_zhdr1 = 0; r->m_z_adler32 = r->m_check_adler32 = 1;
  إذا (decomp_flags & TINFL_FLAG_PARSE_ZLIB_سرخی)
  {
    TINFL_GET_BYTE(1, r->m_zhdr0); TINFL_GET_BYTE(2, r->m_zhdr1);
    counter = (((r->m_zhdr0 * 256 + r->m_zhdr1) % 31 != 0) || (r->m_zhdr1 & 32) || ((r->m_zhdr0 & 15) != 8));
    إذا (!(decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF)) counter |= (((1U << (8U + (r->m_zhdr0 >> 4))) > 32768U) || ((باہرلا_buf_ناپ_نقاب + 1) < (size_t)(1U << (8U + (r->m_zhdr0 >> 4)))));
    إذا (counter) { TINFL_CR_RETURN_FOREVER(36, TINFL_حالت_FAILED); }
  }

  افعل
  {
    TINFL_GET_بٹ(3, r->m_final, 3); r->m_type = r->m_final >> 1;
    إذا (r->m_type == 0)
    {
      TINFL_SKIP_بٹ(5, عدد_بٹ & 7);
      لكل (counter = 0; counter < 4; ++counter) { إذا (عدد_بٹ) TINFL_GET_بٹ(6, r->m_raw_سرخی[counter], 8); وإلا TINFL_GET_BYTE(7, r->m_raw_سرخی[counter]); }
      إذا ((counter = (r->m_raw_سرخی[0] | (r->m_raw_سرخی[1] << 8))) != (mz_uint)(0xFFFF ^ (r->m_raw_سرخی[2] | (r->m_raw_سرخی[3] << 8)))) { TINFL_CR_RETURN_FOREVER(39, TINFL_حالت_FAILED); }
      طالما ((counter) && (عدد_بٹ))
      {
        TINFL_GET_بٹ(51, dist, 8);
        طالما (p_باہرلا_buf_cur >= p_باہرلا_buf_سرا) { TINFL_CR_RETURN(52, TINFL_حالت_HAS_ہور_OUTPUT); }
        *p_باہرلا_buf_cur++ = (mz_uint8)dist;
        counter--;
      }
      طالما (counter)
      {
        size_t n; طالما (p_باہرلا_buf_cur >= p_باہرلا_buf_سرا) { TINFL_CR_RETURN(9, TINFL_حالت_HAS_ہور_OUTPUT); }
        طالما (p_وچ_buf_cur >= p_وچ_buf_سرا)
        {
          إذا (decomp_flags & TINFL_FLAG_HAS_ہور_داخلہ)
          {
            TINFL_CR_RETURN(38, TINFL_حالت_NEEDS_ہور_داخلہ);
          }
          وإلا
          {
            TINFL_CR_RETURN_FOREVER(40, TINFL_حالت_FAILED);
          }
        }
        n = MZ_MIN(MZ_MIN((size_t)(p_باہرلا_buf_سرا - p_باہرلا_buf_cur), (size_t)(p_وچ_buf_سرا - p_وچ_buf_cur)), counter);
        TINFL_MEMCPY(p_باہرلا_buf_cur, p_وچ_buf_cur, n); p_وچ_buf_cur += n; p_باہرلا_buf_cur += n; counter -= (mz_uint)n;
      }
    }
    وإلا إذا (r->m_type == 3)
    {
      TINFL_CR_RETURN_FOREVER(10, TINFL_حالت_FAILED);
    }
    وإلا
    {
      إذا (r->m_type == 1)
      {
        mz_uint8 *p = r->m_tables[0].m_کوڈ_ناپ; mz_uint i;
        r->m_جدول_sizes[0] = 288; r->m_جدول_sizes[1] = 32; TINFL_MEMSET(r->m_tables[1].m_کوڈ_ناپ, 5, 32);
        لكل ( i = 0; i <= 143; ++i) *p++ = 8;
        لكل ( ; i <= 255; ++i) *p++ = 9;
        لكل ( ; i <= 279; ++i) *p++ = 7;
        لكل ( ; i <= 287; ++i) *p++ = 8;
      }
      وإلا
      {
        لكل (counter = 0; counter < 3; counter++) { TINFL_GET_بٹ(11, r->m_جدول_sizes[counter], "\05\05\04"[counter]); r->m_جدول_sizes[counter] += s_min_جدول_sizes[counter]; }
        MZ_CLEAR_ARR(r->m_tables[2].m_کوڈ_ناپ); لكل (counter = 0; counter < r->m_جدول_sizes[2]; counter++) { mz_uint s; TINFL_GET_بٹ(14, s, 3); r->m_tables[2].m_کوڈ_ناپ[s_لمائی_dezigzag[counter]] = (mz_uint8)s; }
        r->m_جدول_sizes[2] = 19;
      }
      لكل ( ; (صحيح)r->m_type >= 0; r->m_type--)
      {
        صحيح درخت_اگلا, درخت_cur; tinfl_huff_جدول *p_جدول;
        mz_uint i, j, ورتیا_syms, کل, sym_اشاریہ, اگلا_کوڈ[17], کل_syms[16]; p_جدول = &r->m_tables[r->m_type]; MZ_CLEAR_ARR(کل_syms); MZ_CLEAR_ARR(p_جدول->m_look_اتے); MZ_CLEAR_ARR(p_جدول->m_درخت);
        لكل (i = 0; i < r->m_جدول_sizes[r->m_type]; ++i) کل_syms[p_جدول->m_کوڈ_ناپ[i]]++;
        ورتیا_syms = 0, کل = 0; اگلا_کوڈ[0] = اگلا_کوڈ[1] = 0;
        لكل (i = 1; i <= 15; ++i) { ورتیا_syms += کل_syms[i]; اگلا_کوڈ[i + 1] = (کل = ((کل + کل_syms[i]) << 1)); }
        إذا ((65536 != کل) && (ورتیا_syms > 1))
        {
          TINFL_CR_RETURN_FOREVER(35, TINFL_حالت_FAILED);
        }
        لكل (درخت_اگلا = -1, sym_اشاریہ = 0; sym_اشاریہ < r->m_جدول_sizes[r->m_type]; ++sym_اشاریہ)
        {
          mz_uint rev_کوڈ = 0, l, cur_کوڈ, کوڈ_ناپ_2 = p_جدول->m_کوڈ_ناپ[sym_اشاریہ]; إذا (!کوڈ_ناپ_2) استمر;
          cur_کوڈ = اگلا_کوڈ[کوڈ_ناپ_2]++; لكل (l = کوڈ_ناپ_2; l > 0; l--, cur_کوڈ >>= 1) rev_کوڈ = (rev_کوڈ << 1) | (cur_کوڈ & 1);
          إذا (کوڈ_ناپ_2 <= TINFL_FAST_LOOKUP_بٹ) { mz_int16 k = (mz_int16)((کوڈ_ناپ_2 << 9) | sym_اشاریہ); طالما (rev_کوڈ < TINFL_FAST_LOOKUP_ناپ) { p_جدول->m_look_اتے[rev_کوڈ] = k; rev_کوڈ += (1 << کوڈ_ناپ_2); } استمر; }
          إذا (0 == (درخت_cur = p_جدول->m_look_اتے[rev_کوڈ & (TINFL_FAST_LOOKUP_ناپ - 1)])) { p_جدول->m_look_اتے[rev_کوڈ & (TINFL_FAST_LOOKUP_ناپ - 1)] = (mz_int16)درخت_اگلا; درخت_cur = درخت_اگلا; درخت_اگلا -= 2; }
          rev_کوڈ >>= (TINFL_FAST_LOOKUP_بٹ - 1);
          لكل (j = کوڈ_ناپ_2; j > (TINFL_FAST_LOOKUP_بٹ + 1); j--)
          {
            درخت_cur -= ((rev_کوڈ >>= 1) & 1);
            إذا (!p_جدول->m_درخت[-درخت_cur - 1]) { p_جدول->m_درخت[-درخت_cur - 1] = (mz_int16)درخت_اگلا; درخت_cur = درخت_اگلا; درخت_اگلا -= 2; } وإلا درخت_cur = p_جدول->m_درخت[-درخت_cur - 1];
          }
          درخت_cur -= ((rev_کوڈ >>= 1) & 1); p_جدول->m_درخت[-درخت_cur - 1] = (mz_int16)sym_اشاریہ;
        }
        إذا (r->m_type == 2)
        {
          لكل (counter = 0; counter < (r->m_جدول_sizes[0] + r->m_جدول_sizes[1]); )
          {
            mz_uint s; TINFL_HUFF_DECODE(16, dist, &r->m_tables[2]); إذا (dist < 16) { r->m_len_codes[counter++] = (mz_uint8)dist; استمر; }
            إذا ((dist == 16) && (!counter))
            {
              TINFL_CR_RETURN_FOREVER(17, TINFL_حالت_FAILED);
            }
            عدد_extra = "\02\03\07"[dist - 16]; TINFL_GET_بٹ(18, s, عدد_extra); s += "\03\03\013"[dist - 16];
            TINFL_MEMSET(r->m_len_codes + counter, (dist == 16) ? r->m_len_codes[counter - 1] : 0, s); counter += s;
          }
          إذا ((r->m_جدول_sizes[0] + r->m_جدول_sizes[1]) != counter)
          {
            TINFL_CR_RETURN_FOREVER(21, TINFL_حالت_FAILED);
          }
          TINFL_MEMCPY(r->m_tables[0].m_کوڈ_ناپ, r->m_len_codes, r->m_جدول_sizes[0]); TINFL_MEMCPY(r->m_tables[1].m_کوڈ_ناپ, r->m_len_codes + r->m_جدول_sizes[0], r->m_جدول_sizes[1]);
        }
      }
      لكل ( ; ; )
      {
        mz_uint8 *pSrc;
        لكل ( ; ; )
        {
          إذا (((p_وچ_buf_سرا - p_وچ_buf_cur) < 4) || ((p_باہرلا_buf_سرا - p_باہرلا_buf_cur) < 2))
          {
            TINFL_HUFF_DECODE(23, counter, &r->m_tables[0]);
            إذا (counter >= 256)
              اكسر;
            طالما (p_باہرلا_buf_cur >= p_باہرلا_buf_سرا) { TINFL_CR_RETURN(24, TINFL_حالت_HAS_ہور_OUTPUT); }
            *p_باہرلا_buf_cur++ = (mz_uint8)counter;
          }
          وإلا
          {
            صحيح sym2; mz_uint کوڈ_len;
#إذا TINFL_USE_64_ثنائی_ہندسہ_BITBUF
            إذا (عدد_بٹ < 30) { ثنائی_ہندسہ_buf |= (((tinfl_ثنائی_ہندسہ_buf_t)MZ_READ_LE32(p_وچ_buf_cur)) << عدد_بٹ); p_وچ_buf_cur += 4; عدد_بٹ += 32; }
#وإلا
            إذا (عدد_بٹ < 15) { ثنائی_ہندسہ_buf |= (((tinfl_ثنائی_ہندسہ_buf_t)MZ_READ_LE16(p_وچ_buf_cur)) << عدد_بٹ); p_وچ_buf_cur += 2; عدد_بٹ += 16; }
#جے_انت
            إذا ((sym2 = r->m_tables[0].m_look_اتے[ثنائی_ہندسہ_buf & (TINFL_FAST_LOOKUP_ناپ - 1)]) >= 0)
              کوڈ_len = sym2 >> 9;
            وإلا
            {
              کوڈ_len = TINFL_FAST_LOOKUP_بٹ; افعل { sym2 = r->m_tables[0].m_درخت[~sym2 + ((ثنائی_ہندسہ_buf >> کوڈ_len++) & 1)]; } طالما (sym2 < 0);
            }
            counter = sym2; ثنائی_ہندسہ_buf >>= کوڈ_len; عدد_بٹ -= کوڈ_len;
            إذا (counter & 256)
              اكسر;

#إذا !TINFL_USE_64_ثنائی_ہندسہ_BITBUF
            إذا (عدد_بٹ < 15) { ثنائی_ہندسہ_buf |= (((tinfl_ثنائی_ہندسہ_buf_t)MZ_READ_LE16(p_وچ_buf_cur)) << عدد_بٹ); p_وچ_buf_cur += 2; عدد_بٹ += 16; }
#جے_انت
            إذا ((sym2 = r->m_tables[0].m_look_اتے[ثنائی_ہندسہ_buf & (TINFL_FAST_LOOKUP_ناپ - 1)]) >= 0)
              کوڈ_len = sym2 >> 9;
            وإلا
            {
              کوڈ_len = TINFL_FAST_LOOKUP_بٹ; افعل { sym2 = r->m_tables[0].m_درخت[~sym2 + ((ثنائی_ہندسہ_buf >> کوڈ_len++) & 1)]; } طالما (sym2 < 0);
            }
            ثنائی_ہندسہ_buf >>= کوڈ_len; عدد_بٹ -= کوڈ_len;

            p_باہرلا_buf_cur[0] = (mz_uint8)counter;
            إذا (sym2 & 256)
            {
              p_باہرلا_buf_cur++;
              counter = sym2;
              اكسر;
            }
            p_باہرلا_buf_cur[1] = (mz_uint8)sym2;
            p_باہرلا_buf_cur += 2;
          }
        }
        إذا ((counter &= 511) == 256) اكسر;

        عدد_extra = s_لمائی_extra[counter - 257]; counter = s_لمائی_ادھار[counter - 257];
        إذا (عدد_extra) { mz_uint extra_بٹ; TINFL_GET_بٹ(25, extra_بٹ, عدد_extra); counter += extra_بٹ; }

        TINFL_HUFF_DECODE(26, dist, &r->m_tables[1]);
        عدد_extra = s_dist_extra[dist]; dist = s_dist_ادھار[dist];
        إذا (عدد_extra) { mz_uint extra_بٹ; TINFL_GET_بٹ(27, extra_بٹ, عدد_extra); dist += extra_بٹ; }

        dist_from_باہرلا_buf_شروع = p_باہرلا_buf_cur - p_باہرلا_buf_شروع;
        إذا ((dist > dist_from_باہرلا_buf_شروع) && (decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF))
        {
          TINFL_CR_RETURN_FOREVER(37, TINFL_حالت_FAILED);
        }

        pSrc = p_باہرلا_buf_شروع + ((dist_from_باہرلا_buf_شروع - dist) & باہرلا_buf_ناپ_نقاب);

        إذا ((MZ_MAX(p_باہرلا_buf_cur, pSrc) + counter) > p_باہرلا_buf_سرا)
        {
          طالما (counter--)
          {
            طالما (p_باہرلا_buf_cur >= p_باہرلا_buf_سرا) { TINFL_CR_RETURN(53, TINFL_حالت_HAS_ہور_OUTPUT); }
            *p_باہرلا_buf_cur++ = p_باہرلا_buf_شروع[(dist_from_باہرلا_buf_شروع++ - dist) & باہرلا_buf_ناپ_نقاب];
          }
          استمر;
        }
#إذا MINIZ_USE_UNALIGNED_LOADS_AND_STORES
        وإلا إذا ((counter >= 9) && (counter <= dist))
        {
          ثابت mz_uint8 *p_Src_سرا = pSrc + (counter & ~7);
          افعل
          {
            ((mz_uint32 *)p_باہرلا_buf_cur)[0] = ((ثابت mz_uint32 *)pSrc)[0];
            ((mz_uint32 *)p_باہرلا_buf_cur)[1] = ((ثابت mz_uint32 *)pSrc)[1];
            p_باہرلا_buf_cur += 8;
          } طالما ((pSrc += 8) < p_Src_سرا);
          إذا ((counter &= 7) < 3)
          {
            إذا (counter)
            {
              p_باہرلا_buf_cur[0] = pSrc[0];
              إذا (counter > 1)
                p_باہرلا_buf_cur[1] = pSrc[1];
              p_باہرلا_buf_cur += counter;
            }
            استمر;
          }
        }
#جے_انت
        افعل
        {
          p_باہرلا_buf_cur[0] = pSrc[0];
          p_باہرلا_buf_cur[1] = pSrc[1];
          p_باہرلا_buf_cur[2] = pSrc[2];
          p_باہرلا_buf_cur += 3; pSrc += 3;
        } طالما ((صحيح)(counter -= 3) > 2);
        إذا ((صحيح)counter > 0)
        {
          p_باہرلا_buf_cur[0] = pSrc[0];
          إذا ((صحيح)counter > 1)
            p_باہرلا_buf_cur[1] = pSrc[1];
          p_باہرلا_buf_cur += counter;
        }
      }
    }
  } طالما (!(r->m_final & 1));
  إذا (decomp_flags & TINFL_FLAG_PARSE_ZLIB_سرخی)
  {
    TINFL_SKIP_بٹ(32, عدد_بٹ & 7); لكل (counter = 0; counter < 4; ++counter) { mz_uint s; إذا (عدد_بٹ) TINFL_GET_بٹ(41, s, 8); وإلا TINFL_GET_BYTE(42, s); r->m_z_adler32 = (r->m_z_adler32 << 8) | s; }
  }
  TINFL_CR_RETURN_FOREVER(34, TINFL_حالت_پورا);
  TINFL_CR_انت

common_exit:
  r->m_عدد_بٹ = عدد_بٹ; r->m_ثنائی_ہندسہ_buf = ثنائی_ہندسہ_buf; r->m_dist = dist; r->m_counter = counter; r->m_عدد_extra = عدد_extra; r->m_dist_from_باہرلا_buf_شروع = dist_from_باہرلا_buf_شروع;
  *p_وچ_buf_ناپ = p_وچ_buf_cur - p_وچ_buf_اگلا; *p_باہرلا_buf_ناپ = p_باہرلا_buf_cur - p_باہرلا_buf_اگلا;
  إذا ((decomp_flags & (TINFL_FLAG_PARSE_ZLIB_سرخی | TINFL_FLAG_COMPUTE_ADLER32)) && (حالت >= 0))
  {
    ثابت mz_uint8 *ptr = p_باہرلا_buf_اگلا; size_t buf_len = *p_باہرلا_buf_ناپ;
    mz_uint32 i, s1 = r->m_check_adler32 & 0xffff, s2 = r->m_check_adler32 >> 16; size_t بلاک_len = buf_len % 5552;
    طالما (buf_len)
    {
      لكل (i = 0; i + 7 < بلاک_len; i += 8, ptr += 8)
      {
        s1 += ptr[0], s2 += s1; s1 += ptr[1], s2 += s1; s1 += ptr[2], s2 += s1; s1 += ptr[3], s2 += s1;
        s1 += ptr[4], s2 += s1; s1 += ptr[5], s2 += s1; s1 += ptr[6], s2 += s1; s1 += ptr[7], s2 += s1;
      }
      لكل ( ; i < بلاک_len; ++i) s1 += *ptr++, s2 += s1;
      s1 %= 65521U, s2 %= 65521U; buf_len -= بلاک_len; بلاک_len = 5552;
    }
    r->m_check_adler32 = (s2 << 16) + s1; إذا ((حالت == TINFL_حالت_پورا) && (decomp_flags & TINFL_FLAG_PARSE_ZLIB_سرخی) && (r->m_check_adler32 != r->m_z_adler32)) حالت = TINFL_حالت_ADLER32_MISMATCH;
  }
  أرجع حالت;
}

// Higher level helper functions.
فراغ *tinfl_decompress_mem_منزل_ڈھیر(ثابت فراغ *pSrc_buf, size_t src_buf_len, size_t *p_باہرلا_len, صحيح flags)
{
  tinfl_decompressor decomp; فراغ *pBuf = عدم, *pNew_buf; size_t src_buf_ofs = 0, باہرلا_buf_سمرتھا = 0;
  *p_باہرلا_len = 0;
  tinfl_init(&decomp);
  لكل ( ; ; )
  {
    size_t src_buf_ناپ = src_buf_len - src_buf_ofs, dst_buf_ناپ = باہرلا_buf_سمرتھا - *p_باہرلا_len, new_باہرلا_buf_سمرتھا;
    tinfl_حالت حالت = tinfl_decompress(&decomp, (ثابت mz_uint8*)pSrc_buf + src_buf_ofs, &src_buf_ناپ, (mz_uint8*)pBuf, pBuf ? (mz_uint8*)pBuf + *p_باہرلا_len : عدم, &dst_buf_ناپ,
      (flags & ~TINFL_FLAG_HAS_ہور_داخلہ) | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF);
    إذا ((حالت < 0) || (حالت == TINFL_حالت_NEEDS_ہور_داخلہ))
    {
      MZ_FREE(pBuf); *p_باہرلا_len = 0; أرجع عدم;
    }
    src_buf_ofs += src_buf_ناپ;
    *p_باہرلا_len += dst_buf_ناپ;
    إذا (حالت == TINFL_حالت_پورا) اكسر;
    new_باہرلا_buf_سمرتھا = باہرلا_buf_سمرتھا * 2; إذا (new_باہرلا_buf_سمرتھا < 128) new_باہرلا_buf_سمرتھا = 128;
    pNew_buf = MZ_REALLOC(pBuf, new_باہرلا_buf_سمرتھا);
    إذا (!pNew_buf)
    {
      MZ_FREE(pBuf); *p_باہرلا_len = 0; أرجع عدم;
    }
    pBuf = pNew_buf; باہرلا_buf_سمرتھا = new_باہرلا_buf_سمرتھا;
  }
  أرجع pBuf;
}

size_t tinfl_decompress_mem_منزل_mem(فراغ *p_باہرلا_buf, size_t باہرلا_buf_len, ثابت فراغ *pSrc_buf, size_t src_buf_len, صحيح flags)
{
  tinfl_decompressor decomp; tinfl_حالت حالت; tinfl_init(&decomp);
  حالت = tinfl_decompress(&decomp, (ثابت mz_uint8*)pSrc_buf, &src_buf_len, (mz_uint8*)p_باہرلا_buf, (mz_uint8*)p_باہرلا_buf, &باہرلا_buf_len, (flags & ~TINFL_FLAG_HAS_ہور_داخلہ) | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF);
  أرجع (حالت != TINFL_حالت_پورا) ? TINFL_DECOMPRESS_MEM_منزل_MEM_FAILED : باہرلا_buf_len;
}

صحيح tinfl_decompress_mem_منزل_callback(ثابت فراغ *p_وچ_buf, size_t *p_وچ_buf_ناپ, tinfl_put_buf_func_ptr pPut_buf_func, فراغ *pPut_buf_user, صحيح flags)
{
  صحيح نتیجہ = 0;
  tinfl_decompressor decomp;
  mz_uint8 *pDict = (mz_uint8*)MZ_MALLOC(TINFL_LZ_DICT_ناپ); size_t وچ_buf_ofs = 0, dict_ofs = 0;
  إذا (!pDict)
    أرجع TINFL_حالت_FAILED;
  memset(pDict,0,TINFL_LZ_DICT_ناپ);
  tinfl_init(&decomp);
  لكل ( ; ; )
  {
    size_t وچ_buf_ناپ = *p_وچ_buf_ناپ - وچ_buf_ofs, dst_buf_ناپ = TINFL_LZ_DICT_ناپ - dict_ofs;
    tinfl_حالت حالت = tinfl_decompress(&decomp, (ثابت mz_uint8*)p_وچ_buf + وچ_buf_ofs, &وچ_buf_ناپ, pDict, pDict + dict_ofs, &dst_buf_ناپ,
      (flags & ~(TINFL_FLAG_HAS_ہور_داخلہ | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF)));
    وچ_buf_ofs += وچ_buf_ناپ;
    إذا ((dst_buf_ناپ) && (!(*pPut_buf_func)(pDict + dict_ofs, (صحيح)dst_buf_ناپ, pPut_buf_user)))
      اكسر;
    إذا (حالت != TINFL_حالت_HAS_ہور_OUTPUT)
    {
      نتیجہ = (حالت == TINFL_حالت_پورا);
      اكسر;
    }
    dict_ofs = (dict_ofs + dst_buf_ناپ) & (TINFL_LZ_DICT_ناپ - 1);
  }
  MZ_FREE(pDict);
  *p_وچ_buf_ناپ = وچ_buf_ofs;
  أرجع نتیجہ;
}
#جے_انت /*#ifndef MINIZ_NO_INFLATE_APIS*/

// ------------------- Low-level Compression (independent from all decompression API's)
#جے_بنا_تعریف MINIZ_NO_DEFLATE_APIS

// Purposely making these tables static for faster init and thread safety.
ساكن ثابت mz_uint16 s_tdefl_len_sym[256] = {
  257,258,259,260,261,262,263,264,265,265,266,266,267,267,268,268,269,269,269,269,270,270,270,270,271,271,271,271,272,272,272,272,
  273,273,273,273,273,273,273,273,274,274,274,274,274,274,274,274,275,275,275,275,275,275,275,275,276,276,276,276,276,276,276,276,
  277,277,277,277,277,277,277,277,277,277,277,277,277,277,277,277,278,278,278,278,278,278,278,278,278,278,278,278,278,278,278,278,
  279,279,279,279,279,279,279,279,279,279,279,279,279,279,279,279,280,280,280,280,280,280,280,280,280,280,280,280,280,280,280,280,
  281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,
  282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,
  283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,
  284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,285 };

ساكن ثابت mz_uint8 s_tdefl_len_extra[256] = {
  0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0 };

ساكن ثابت mz_uint8 s_tdefl_small_dist_sym[512] = {
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

ساكن ثابت mz_uint8 s_tdefl_small_dist_extra[512] = {
  0,0,0,0,1,1,1,1,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
  6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
  6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7 };

ساكن ثابت mz_uint8 s_tdefl_large_dist_sym[128] = {
  0,0,18,19,20,20,21,21,22,22,22,22,23,23,23,23,24,24,24,24,24,24,24,24,25,25,25,25,25,25,25,25,26,26,26,26,26,26,26,26,26,26,26,26,
  26,26,26,26,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,
  28,28,28,28,28,28,28,28,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29 };

ساكن ثابت mz_uint8 s_tdefl_large_dist_extra[128] = {
  0,0,8,8,9,9,9,9,10,10,10,10,10,10,10,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,
  12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
  13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13 };

// Radix sorts tdefl_sym_freq[] array by 16-bit key m_key. Returns ptr to sorted values.
تعريفنوع بنية { mz_uint16 m_کلید, m_sym_اشاریہ; } tdefl_sym_freq;
ساكن tdefl_sym_freq* tdefl_radix_ترتیب_دیو_syms(mz_uint عدد_syms, tdefl_sym_freq* pSyms0, tdefl_sym_freq* pSyms1)
{
  mz_uint32 کل_passes = 2, pass_کھسکاؤ, pass, i, hist[256 * 2]; tdefl_sym_freq* pCur_syms = pSyms0, *pNew_syms = pSyms1; MZ_CLEAR_ARR(hist);
  لكل (i = 0; i < عدد_syms; i++) { mz_uint freq = pSyms0[i].m_کلید; hist[freq & 0xFF]++; hist[256 + ((freq >> 8) & 0xFF)]++; }
  طالما ((کل_passes > 1) && (عدد_syms == hist[(کل_passes - 1) * 256])) کل_passes--;
  لكل (pass_کھسکاؤ = 0, pass = 0; pass < کل_passes; pass++, pass_کھسکاؤ += 8)
  {
    ثابت mz_uint32* pHist = &hist[pass << 8];
    mz_uint offsets[256], cur_ofs = 0;
    لكل (i = 0; i < 256; i++) { offsets[i] = cur_ofs; cur_ofs += pHist[i]; }
    لكل (i = 0; i < عدد_syms; i++) pNew_syms[offsets[(pCur_syms[i].m_کلید >> pass_کھسکاؤ) & 0xFF]++] = pCur_syms[i];
    { tdefl_sym_freq* t = pCur_syms; pCur_syms = pNew_syms; pNew_syms = t; }
  }
  أرجع pCur_syms;
}

// tdefl_calculate_minimum_redundancy() originally written by: Alistair Moffat, alistair@cs.mu.oz.au, Jyrki Katajainen, jyrki@diku.dk, November 1996.
ساكن فراغ tdefl_calculate_minimum_redundancy(tdefl_sym_freq *A, صحيح n)
{
  صحيح جڑ, پتی, اگلا, avbl, ورتیا, dpth;
  إذا (n==0) أرجع; وإلا إذا (n==1) { A[0].m_کلید = 1; أرجع; }
  A[0].m_کلید += A[1].m_کلید; جڑ = 0; پتی = 2;
  لكل (اگلا=1; اگلا < n-1; اگلا++)
  {
    إذا (پتی>=n || A[جڑ].m_کلید<A[پتی].m_کلید) { A[اگلا].m_کلید = A[جڑ].m_کلید; A[جڑ++].m_کلید = (mz_uint16)اگلا; } وإلا A[اگلا].m_کلید = A[پتی++].m_کلید;
    إذا (پتی>=n || (جڑ<اگلا && A[جڑ].m_کلید<A[پتی].m_کلید)) { A[اگلا].m_کلید = (mz_uint16)(A[اگلا].m_کلید + A[جڑ].m_کلید); A[جڑ++].m_کلید = (mz_uint16)اگلا; } وإلا A[اگلا].m_کلید = (mz_uint16)(A[اگلا].m_کلید + A[پتی++].m_کلید);
  }
  A[n-2].m_کلید = 0; لكل (اگلا=n-3; اگلا>=0; اگلا--) A[اگلا].m_کلید = A[A[اگلا].m_کلید].m_کلید+1;
  avbl = 1; ورتیا = dpth = 0; جڑ = n-2; اگلا = n-1;
  طالما (avbl>0)
  {
    طالما (جڑ>=0 && (صحيح)A[جڑ].m_کلید==dpth) { ورتیا++; جڑ--; }
    طالما (avbl>ورتیا) { A[اگلا--].m_کلید = (mz_uint16)(dpth); avbl--; }
    avbl = 2*ورتیا; dpth++; ورتیا = 0;
  }
}

// Limits canonical Huffman code table's max code size.
تعداد { TDEFL_MAX_SUPPORTED_HUFF_CODESIZE = 32 };
ساكن فراغ tdefl_huffman_enforce_max_کوڈ_ناپ(صحيح *p_عدد_codes, صحيح کوڈ_list_len, صحيح max_کوڈ_ناپ)
{
  صحيح i; mz_uint32 کل = 0; إذا (کوڈ_list_len <= 1) أرجع;
  لكل (i = max_کوڈ_ناپ + 1; i <= TDEFL_MAX_SUPPORTED_HUFF_CODESIZE; i++) p_عدد_codes[max_کوڈ_ناپ] += p_عدد_codes[i];
  لكل (i = max_کوڈ_ناپ; i > 0; i--) کل += (((mz_uint32)p_عدد_codes[i]) << (max_کوڈ_ناپ - i));
  طالما (کل != (1UL << max_کوڈ_ناپ))
  {
    p_عدد_codes[max_کوڈ_ناپ]--;
    لكل (i = max_کوڈ_ناپ - 1; i > 0; i--) إذا (p_عدد_codes[i]) { p_عدد_codes[i]--; p_عدد_codes[i + 1] += 2; اكسر; }
    کل--;
  }
}

ساكن فراغ tdefl_optimize_huffman_جدول(tdefl_compressor *d, صحيح جدول_عدد, صحيح جدول_len, صحيح کوڈ_ناپ_حد_بندی, صحيح static_جدول)
{
  صحيح i, j, l, عدد_codes[1 + TDEFL_MAX_SUPPORTED_HUFF_CODESIZE]; mz_uint اگلا_کوڈ[TDEFL_MAX_SUPPORTED_HUFF_CODESIZE + 1]; MZ_CLEAR_ARR(عدد_codes);
  إذا (static_جدول)
  {
    لكل (i = 0; i < جدول_len; i++) عدد_codes[d->m_huff_کوڈ_sizes[جدول_عدد][i]]++;
  }
  وإلا
  {
    tdefl_sym_freq syms0[TDEFL_MAX_HUFF_SYMBOLS], syms1[TDEFL_MAX_HUFF_SYMBOLS], *pSyms;
    صحيح عدد_ورتیا_syms = 0;
    ثابت mz_uint16 *p_Sym_گنتی = &d->m_huff_گنتی[جدول_عدد][0];
    لكل (i = 0; i < جدول_len; i++) إذا (p_Sym_گنتی[i]) { syms0[عدد_ورتیا_syms].m_کلید = (mz_uint16)p_Sym_گنتی[i]; syms0[عدد_ورتیا_syms++].m_sym_اشاریہ = (mz_uint16)i; }

    pSyms = tdefl_radix_ترتیب_دیو_syms(عدد_ورتیا_syms, syms0, syms1); tdefl_calculate_minimum_redundancy(pSyms, عدد_ورتیا_syms);

    لكل (i = 0; i < عدد_ورتیا_syms; i++) عدد_codes[pSyms[i].m_کلید]++;

    tdefl_huffman_enforce_max_کوڈ_ناپ(عدد_codes, عدد_ورتیا_syms, کوڈ_ناپ_حد_بندی);

    MZ_CLEAR_ARR(d->m_huff_کوڈ_sizes[جدول_عدد]); MZ_CLEAR_ARR(d->m_huff_codes[جدول_عدد]);
    لكل (i = 1, j = عدد_ورتیا_syms; i <= کوڈ_ناپ_حد_بندی; i++)
      لكل (l = عدد_codes[i]; l > 0; l--) d->m_huff_کوڈ_sizes[جدول_عدد][pSyms[--j].m_sym_اشاریہ] = (mz_uint8)(i);
  }

  اگلا_کوڈ[1] = 0; لكل (j = 0, i = 2; i <= کوڈ_ناپ_حد_بندی; i++) اگلا_کوڈ[i] = j = ((j + عدد_codes[i - 1]) << 1);

  لكل (i = 0; i < جدول_len; i++)
  {
    mz_uint rev_کوڈ = 0, کوڈ, کوڈ_ناپ_2; إذا ((کوڈ_ناپ_2 = d->m_huff_کوڈ_sizes[جدول_عدد][i]) == 0) استمر;
    کوڈ = اگلا_کوڈ[کوڈ_ناپ_2]++; لكل (l = کوڈ_ناپ_2; l > 0; l--, کوڈ >>= 1) rev_کوڈ = (rev_کوڈ << 1) | (کوڈ & 1);
    d->m_huff_codes[جدول_عدد][i] = (mz_uint16)rev_کوڈ;
  }
}

#تعریف_کرو TDEFL_PUT_بٹ(b, l) افعل { \
  mz_uint بٹ = b; mz_uint len = l; MZ_ASSERT(بٹ <= ((1U << len) - 1U)); \
  d->m_ثنائی_ہندسہ_بفر |= (بٹ << d->m_بٹ_وچ); d->m_بٹ_وچ += len; \
  طالما (d->m_بٹ_وچ >= 8) { \
    إذا (d->m_pOutput_buf < d->m_p_Output_buf_سرا) \
      *d->m_pOutput_buf++ = (mz_uint8)(d->m_ثنائی_ہندسہ_بفر); \
    d->m_ثنائی_ہندسہ_بفر >>= 8; \
    d->m_بٹ_وچ -= 8; \
  } \
} MZ_MACRO_سرا

#تعریف_کرو TDEFL_RLE_PREV_کوڈ_ناپ() افعل { \
  إذا (rle_repeat_گنتی) { \
    إذا (rle_repeat_گنتی < 3) { \
      d->m_huff_گنتی[2][prev_کوڈ_ناپ] = (mz_uint16)(d->m_huff_گنتی[2][prev_کوڈ_ناپ] + rle_repeat_گنتی); \
      طالما (rle_repeat_گنتی--) packed_کوڈ_sizes[عدد_packed_کوڈ_sizes++] = prev_کوڈ_ناپ; \
    } وإلا { \
      d->m_huff_گنتی[2][16] = (mz_uint16)(d->m_huff_گنتی[2][16] + 1); packed_کوڈ_sizes[عدد_packed_کوڈ_sizes++] = 16; packed_کوڈ_sizes[عدد_packed_کوڈ_sizes++] = (mz_uint8)(rle_repeat_گنتی - 3); \
  } rle_repeat_گنتی = 0; } \
} MZ_MACRO_سرا

#تعریف_کرو TDEFL_RLE_ZERO_کوڈ_ناپ() افعل { \
  إذا (rle_z_گنتی) { \
    إذا (rle_z_گنتی < 3) { \
      d->m_huff_گنتی[2][0] = (mz_uint16)(d->m_huff_گنتی[2][0] + rle_z_گنتی); طالما (rle_z_گنتی--) packed_کوڈ_sizes[عدد_packed_کوڈ_sizes++] = 0; \
    } وإلا إذا (rle_z_گنتی <= 10) { \
      d->m_huff_گنتی[2][17] = (mz_uint16)(d->m_huff_گنتی[2][17] + 1); packed_کوڈ_sizes[عدد_packed_کوڈ_sizes++] = 17; packed_کوڈ_sizes[عدد_packed_کوڈ_sizes++] = (mz_uint8)(rle_z_گنتی - 3); \
    } وإلا { \
      d->m_huff_گنتی[2][18] = (mz_uint16)(d->m_huff_گنتی[2][18] + 1); packed_کوڈ_sizes[عدد_packed_کوڈ_sizes++] = 18; packed_کوڈ_sizes[عدد_packed_کوڈ_sizes++] = (mz_uint8)(rle_z_گنتی - 11); \
  } rle_z_گنتی = 0; } \
} MZ_MACRO_سرا

ساكن mz_uint8 s_tdefl_packed_کوڈ_ناپ_syms_swizzle[] = { 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 };

ساكن فراغ tdefl_شروع_dynamic_بلاک(tdefl_compressor *d)
{
  صحيح عدد_lit_codes, عدد_dist_codes, عدد_ثنائی_ہندسہ_lengths; mz_uint i, کل_کوڈ_sizes_منزل_pack, عدد_packed_کوڈ_sizes, rle_z_گنتی, rle_repeat_گنتی, packed_کوڈ_sizes_اشاریہ;
  mz_uint8 کوڈ_sizes_منزل_pack[TDEFL_MAX_HUFF_SYMBOLS_0 + TDEFL_MAX_HUFF_SYMBOLS_1], packed_کوڈ_sizes[TDEFL_MAX_HUFF_SYMBOLS_0 + TDEFL_MAX_HUFF_SYMBOLS_1], prev_کوڈ_ناپ = 0xFF;

  d->m_huff_گنتی[0][256] = 1;

  tdefl_optimize_huffman_جدول(d, 0, TDEFL_MAX_HUFF_SYMBOLS_0, 15, MZ_FALSE);
  tdefl_optimize_huffman_جدول(d, 1, TDEFL_MAX_HUFF_SYMBOLS_1, 15, MZ_FALSE);

  لكل (عدد_lit_codes = 286; عدد_lit_codes > 257; عدد_lit_codes--) إذا (d->m_huff_کوڈ_sizes[0][عدد_lit_codes - 1]) اكسر;
  لكل (عدد_dist_codes = 30; عدد_dist_codes > 1; عدد_dist_codes--) إذا (d->m_huff_کوڈ_sizes[1][عدد_dist_codes - 1]) اكسر;

  حافظہ_نقل(کوڈ_sizes_منزل_pack, &d->m_huff_کوڈ_sizes[0][0], عدد_lit_codes);
  حافظہ_نقل(کوڈ_sizes_منزل_pack + عدد_lit_codes, &d->m_huff_کوڈ_sizes[1][0], عدد_dist_codes);
  کل_کوڈ_sizes_منزل_pack = عدد_lit_codes + عدد_dist_codes; عدد_packed_کوڈ_sizes = 0; rle_z_گنتی = 0; rle_repeat_گنتی = 0;

  memset(&d->m_huff_گنتی[2][0], 0, حجم(d->m_huff_گنتی[2][0]) * TDEFL_MAX_HUFF_SYMBOLS_2);
  لكل (i = 0; i < کل_کوڈ_sizes_منزل_pack; i++)
  {
    mz_uint8 کوڈ_ناپ_2 = کوڈ_sizes_منزل_pack[i];
    إذا (!کوڈ_ناپ_2)
    {
      TDEFL_RLE_PREV_کوڈ_ناپ();
      إذا (++rle_z_گنتی == 138) { TDEFL_RLE_ZERO_کوڈ_ناپ(); }
    }
    وإلا
    {
      TDEFL_RLE_ZERO_کوڈ_ناپ();
      إذا (کوڈ_ناپ_2 != prev_کوڈ_ناپ)
      {
        TDEFL_RLE_PREV_کوڈ_ناپ();
        d->m_huff_گنتی[2][کوڈ_ناپ_2] = (mz_uint16)(d->m_huff_گنتی[2][کوڈ_ناپ_2] + 1); packed_کوڈ_sizes[عدد_packed_کوڈ_sizes++] = کوڈ_ناپ_2;
      }
      وإلا إذا (++rle_repeat_گنتی == 6)
      {
        TDEFL_RLE_PREV_کوڈ_ناپ();
      }
    }
    prev_کوڈ_ناپ = کوڈ_ناپ_2;
  }
  إذا (rle_repeat_گنتی) { TDEFL_RLE_PREV_کوڈ_ناپ(); } وإلا { TDEFL_RLE_ZERO_کوڈ_ناپ(); }

  tdefl_optimize_huffman_جدول(d, 2, TDEFL_MAX_HUFF_SYMBOLS_2, 7, MZ_FALSE);

  TDEFL_PUT_بٹ(2, 2);

  TDEFL_PUT_بٹ(عدد_lit_codes - 257, 5);
  TDEFL_PUT_بٹ(عدد_dist_codes - 1, 5);

  لكل (عدد_ثنائی_ہندسہ_lengths = 18; عدد_ثنائی_ہندسہ_lengths >= 0; عدد_ثنائی_ہندسہ_lengths--) إذا (d->m_huff_کوڈ_sizes[2][s_tdefl_packed_کوڈ_ناپ_syms_swizzle[عدد_ثنائی_ہندسہ_lengths]]) اكسر;
  عدد_ثنائی_ہندسہ_lengths = MZ_MAX(4, (عدد_ثنائی_ہندسہ_lengths + 1)); TDEFL_PUT_بٹ(عدد_ثنائی_ہندسہ_lengths - 4, 4);
  لكل (i = 0; (صحيح)i < عدد_ثنائی_ہندسہ_lengths; i++) TDEFL_PUT_بٹ(d->m_huff_کوڈ_sizes[2][s_tdefl_packed_کوڈ_ناپ_syms_swizzle[i]], 3);

  لكل (packed_کوڈ_sizes_اشاریہ = 0; packed_کوڈ_sizes_اشاریہ < عدد_packed_کوڈ_sizes; )
  {
    mz_uint کوڈ = packed_کوڈ_sizes[packed_کوڈ_sizes_اشاریہ++]; MZ_ASSERT(کوڈ < TDEFL_MAX_HUFF_SYMBOLS_2);
    TDEFL_PUT_بٹ(d->m_huff_codes[2][کوڈ], d->m_huff_کوڈ_sizes[2][کوڈ]);
    إذا (کوڈ >= 16) TDEFL_PUT_بٹ(packed_کوڈ_sizes[packed_کوڈ_sizes_اشاریہ++], "\02\03\07"[کوڈ - 16]);
  }
}

ساكن فراغ tdefl_شروع_static_بلاک(tdefl_compressor *d)
{
  mz_uint i;
  mz_uint8 *p = &d->m_huff_کوڈ_sizes[0][0];

  لكل (i = 0; i <= 143; ++i) *p++ = 8;
  لكل ( ; i <= 255; ++i) *p++ = 9;
  لكل ( ; i <= 279; ++i) *p++ = 7;
  لكل ( ; i <= 287; ++i) *p++ = 8;

  memset(d->m_huff_کوڈ_sizes[1], 5, 32);

  tdefl_optimize_huffman_جدول(d, 0, 288, 15, MZ_TRUE);
  tdefl_optimize_huffman_جدول(d, 1, 32, 15, MZ_TRUE);

  TDEFL_PUT_بٹ(1, 2);
}

ساكن ثابت mz_uint mz_bitmasks[17] = { 0x0000, 0x0001, 0x0003, 0x0007, 0x000F, 0x001F, 0x003F, 0x007F, 0x00FF, 0x01FF, 0x03FF, 0x07FF, 0x0FFF, 0x1FFF, 0x3FFF, 0x7FFF, 0xFFFF };

#إذا MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN && MINIZ_HAS_64_ثنائی_ہندسہ_REGISTERS
ساكن mz_bool tdefl_compress_lz_codes(tdefl_compressor *d)
{
  mz_uint flags;
  mz_uint8 *pLZ_codes;
  mz_uint8 *pOutput_buf = d->m_pOutput_buf;
  mz_uint8 *p_LZ_کوڈ_buf_سرا = d->m_p_LZ_کوڈ_buf;
  mz_uint64 ثنائی_ہندسہ_بفر = d->m_ثنائی_ہندسہ_بفر;
  mz_uint بٹ_وچ = d->m_بٹ_وچ;

#تعریف_کرو TDEFL_PUT_بٹ_FAST(b, l) { ثنائی_ہندسہ_بفر |= (((mz_uint64)(b)) << بٹ_وچ); بٹ_وچ += (l); }

  flags = 1;
  لكل (pLZ_codes = d->m_lz_کوڈ_buf; pLZ_codes < p_LZ_کوڈ_buf_سرا; flags >>= 1)
  {
    إذا (flags == 1)
      flags = *pLZ_codes++ | 0x100;

    إذا (flags & 1)
    {
      mz_uint s0, s1, n0, n1, sym, عدد_extra_بٹ;
      mz_uint میل_len = pLZ_codes[0], میل_dist = *(ثابت mz_uint16 *)(pLZ_codes + 1); pLZ_codes += 3;

      MZ_ASSERT(d->m_huff_کوڈ_sizes[0][s_tdefl_len_sym[میل_len]]);
      TDEFL_PUT_بٹ_FAST(d->m_huff_codes[0][s_tdefl_len_sym[میل_len]], d->m_huff_کوڈ_sizes[0][s_tdefl_len_sym[میل_len]]);
      TDEFL_PUT_بٹ_FAST(میل_len & mz_bitmasks[s_tdefl_len_extra[میل_len]], s_tdefl_len_extra[میل_len]);

      // This sequence coaxes MSVC into using cmov's vs. jmp's.
      s0 = s_tdefl_small_dist_sym[میل_dist & 511];
      n0 = s_tdefl_small_dist_extra[میل_dist & 511];
      s1 = s_tdefl_large_dist_sym[میل_dist >> 8];
      n1 = s_tdefl_large_dist_extra[میل_dist >> 8];
      sym = (میل_dist < 512) ? s0 : s1;
      عدد_extra_بٹ = (میل_dist < 512) ? n0 : n1;

      MZ_ASSERT(d->m_huff_کوڈ_sizes[1][sym]);
      TDEFL_PUT_بٹ_FAST(d->m_huff_codes[1][sym], d->m_huff_کوڈ_sizes[1][sym]);
      TDEFL_PUT_بٹ_FAST(میل_dist & mz_bitmasks[عدد_extra_بٹ], عدد_extra_بٹ);
    }
    وإلا
    {
      mz_uint lit = *pLZ_codes++;
      MZ_ASSERT(d->m_huff_کوڈ_sizes[0][lit]);
      TDEFL_PUT_بٹ_FAST(d->m_huff_codes[0][lit], d->m_huff_کوڈ_sizes[0][lit]);

      إذا (((flags & 2) == 0) && (pLZ_codes < p_LZ_کوڈ_buf_سرا))
      {
        flags >>= 1;
        lit = *pLZ_codes++;
        MZ_ASSERT(d->m_huff_کوڈ_sizes[0][lit]);
        TDEFL_PUT_بٹ_FAST(d->m_huff_codes[0][lit], d->m_huff_کوڈ_sizes[0][lit]);

        إذا (((flags & 2) == 0) && (pLZ_codes < p_LZ_کوڈ_buf_سرا))
        {
          flags >>= 1;
          lit = *pLZ_codes++;
          MZ_ASSERT(d->m_huff_کوڈ_sizes[0][lit]);
          TDEFL_PUT_بٹ_FAST(d->m_huff_codes[0][lit], d->m_huff_کوڈ_sizes[0][lit]);
        }
      }
    }

    إذا (pOutput_buf >= d->m_p_Output_buf_سرا)
      أرجع MZ_FALSE;

    *(mz_uint64*)pOutput_buf = ثنائی_ہندسہ_بفر;
    pOutput_buf += (بٹ_وچ >> 3);
    ثنائی_ہندسہ_بفر >>= (بٹ_وچ & ~7);
    بٹ_وچ &= 7;
  }

#تعریف_رد TDEFL_PUT_بٹ_FAST

  d->m_pOutput_buf = pOutput_buf;
  d->m_بٹ_وچ = 0;
  d->m_ثنائی_ہندسہ_بفر = 0;

  طالما (بٹ_وچ)
  {
    mz_uint32 n = MZ_MIN(بٹ_وچ, 16);
    TDEFL_PUT_بٹ((mz_uint)ثنائی_ہندسہ_بفر & mz_bitmasks[n], n);
    ثنائی_ہندسہ_بفر >>= n;
    بٹ_وچ -= n;
  }

  TDEFL_PUT_بٹ(d->m_huff_codes[0][256], d->m_huff_کوڈ_sizes[0][256]);

  أرجع (d->m_pOutput_buf < d->m_p_Output_buf_سرا);
}
#وإلا
ساكن mz_bool tdefl_compress_lz_codes(tdefl_compressor *d)
{
  mz_uint flags;
  mz_uint8 *pLZ_codes;

  flags = 1;
  لكل (pLZ_codes = d->m_lz_کوڈ_buf; pLZ_codes < d->m_p_LZ_کوڈ_buf; flags >>= 1)
  {
    إذا (flags == 1)
      flags = *pLZ_codes++ | 0x100;
    إذا (flags & 1)
    {
      mz_uint sym, عدد_extra_بٹ;
      mz_uint میل_len = pLZ_codes[0], میل_dist = (pLZ_codes[1] | (pLZ_codes[2] << 8)); pLZ_codes += 3;

      MZ_ASSERT(d->m_huff_کوڈ_sizes[0][s_tdefl_len_sym[میل_len]]);
      TDEFL_PUT_بٹ(d->m_huff_codes[0][s_tdefl_len_sym[میل_len]], d->m_huff_کوڈ_sizes[0][s_tdefl_len_sym[میل_len]]);
      TDEFL_PUT_بٹ(میل_len & mz_bitmasks[s_tdefl_len_extra[میل_len]], s_tdefl_len_extra[میل_len]);

      إذا (میل_dist < 512)
      {
        sym = s_tdefl_small_dist_sym[میل_dist]; عدد_extra_بٹ = s_tdefl_small_dist_extra[میل_dist];
      }
      وإلا
      {
        sym = s_tdefl_large_dist_sym[میل_dist >> 8]; عدد_extra_بٹ = s_tdefl_large_dist_extra[میل_dist >> 8];
      }
      MZ_ASSERT(d->m_huff_کوڈ_sizes[1][sym]);
      TDEFL_PUT_بٹ(d->m_huff_codes[1][sym], d->m_huff_کوڈ_sizes[1][sym]);
      TDEFL_PUT_بٹ(میل_dist & mz_bitmasks[عدد_extra_بٹ], عدد_extra_بٹ);
    }
    وإلا
    {
      mz_uint lit = *pLZ_codes++;
      MZ_ASSERT(d->m_huff_کوڈ_sizes[0][lit]);
      TDEFL_PUT_بٹ(d->m_huff_codes[0][lit], d->m_huff_کوڈ_sizes[0][lit]);
    }
  }

  TDEFL_PUT_بٹ(d->m_huff_codes[0][256], d->m_huff_کوڈ_sizes[0][256]);

  أرجع (d->m_pOutput_buf < d->m_p_Output_buf_سرا);
}
#جے_انت // MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN && MINIZ_HAS_64BIT_REGISTERS

ساكن mz_bool tdefl_compress_بلاک(tdefl_compressor *d, mz_bool static_بلاک)
{
  إذا (static_بلاک)
    tdefl_شروع_static_بلاک(d);
  وإلا
    tdefl_شروع_dynamic_بلاک(d);
  أرجع tdefl_compress_lz_codes(d);
}

ساكن صحيح tdefl_flush_بلاک(tdefl_compressor *d, صحيح flush)
{
  mz_uint saved_ثنائی_ہندسہ_buf, saved_بٹ_وچ;
  mz_uint8 *pSaved_output_buf;
  mz_bool comp_بلاک_succeeded = MZ_FALSE;
  صحيح n, use_raw_بلاک = ((d->m_flags & TDEFL_FORCE_ALL_RAW_بلاکاں) != 0) && (d->m_lookahead_pos - d->m_lz_کوڈ_buf_dict_pos) <= d->m_dict_ناپ;
  mz_uint8 *p_Output_buf_شروع = ((d->m_pPut_buf_func == عدم) && ((*d->m_p_باہرلا_buf_ناپ - d->m_باہرلا_buf_ofs) >= TDEFL_باہرلا_BUF_ناپ)) ? ((mz_uint8 *)d->m_p_باہرلا_buf + d->m_باہرلا_buf_ofs) : d->m_output_buf;

  d->m_pOutput_buf = p_Output_buf_شروع;
  d->m_p_Output_buf_سرا = d->m_pOutput_buf + TDEFL_باہرلا_BUF_ناپ - 16;

  MZ_ASSERT(!d->m_output_flush_بچیا);
  d->m_output_flush_ofs = 0;
  d->m_output_flush_بچیا = 0;

  *d->m_pLZ_flags = (mz_uint8)(*d->m_pLZ_flags >> d->m_عدد_flags_بایاں);
  d->m_p_LZ_کوڈ_buf -= (d->m_عدد_flags_بایاں == 8);

  إذا ((d->m_flags & TDEFL_WRITE_ZLIB_سرخی) && (!d->m_بلاک_اشاریہ))
  {
    TDEFL_PUT_بٹ(0x78, 8); TDEFL_PUT_بٹ(0x01, 8);
  }

  TDEFL_PUT_بٹ(flush == TDEFL_انت, 1);

  pSaved_output_buf = d->m_pOutput_buf; saved_ثنائی_ہندسہ_buf = d->m_ثنائی_ہندسہ_بفر; saved_بٹ_وچ = d->m_بٹ_وچ;

  إذا (!use_raw_بلاک)
    comp_بلاک_succeeded = tdefl_compress_بلاک(d, (d->m_flags & TDEFL_FORCE_ALL_STATIC_بلاکاں) || (d->m_کل_lz_بائٹاں < 48));

  // If the block gets expanded, forget the current contents of the output buffer and send a raw block instead.
  إذا ( ((use_raw_بلاک) || ((d->m_کل_lz_بائٹاں) && ((d->m_pOutput_buf - pSaved_output_buf + 1U) >= d->m_کل_lz_بائٹاں))) &&
       ((d->m_lookahead_pos - d->m_lz_کوڈ_buf_dict_pos) <= d->m_dict_ناپ) )
  {
    mz_uint i; d->m_pOutput_buf = pSaved_output_buf; d->m_ثنائی_ہندسہ_بفر = saved_ثنائی_ہندسہ_buf; d->m_بٹ_وچ = saved_بٹ_وچ;
    TDEFL_PUT_بٹ(0, 2);
    إذا (d->m_بٹ_وچ) { TDEFL_PUT_بٹ(0, 8 - d->m_بٹ_وچ); }
    لكل (i = 2; i; --i, d->m_کل_lz_بائٹاں ^= 0xFFFF)
    {
      TDEFL_PUT_بٹ(d->m_کل_lz_بائٹاں & 0xFFFF, 16);
    }
    لكل (i = 0; i < d->m_کل_lz_بائٹاں; ++i)
    {
      TDEFL_PUT_بٹ(d->m_dict[(d->m_lz_کوڈ_buf_dict_pos + i) & TDEFL_LZ_DICT_ناپ_نقاب], 8);
    }
  }
  // Check for the extremely unlikely (if not impossible) case of the compressed block not fitting into the output buffer when using dynamic codes.
  وإلا إذا (!comp_بلاک_succeeded)
  {
    d->m_pOutput_buf = pSaved_output_buf; d->m_ثنائی_ہندسہ_بفر = saved_ثنائی_ہندسہ_buf; d->m_بٹ_وچ = saved_بٹ_وچ;
    tdefl_compress_بلاک(d, MZ_TRUE);
  }

  إذا (flush)
  {
    إذا (flush == TDEFL_انت)
    {
      إذا (d->m_بٹ_وچ) { TDEFL_PUT_بٹ(0, 8 - d->m_بٹ_وچ); }
      إذا (d->m_flags & TDEFL_WRITE_ZLIB_سرخی) { mz_uint i, a = d->m_adler32; لكل (i = 0; i < 4; i++) { TDEFL_PUT_بٹ((a >> 24) & 0xFF, 8); a <<= 8; } }
    }
    وإلا
    {
      mz_uint i, z = 0; TDEFL_PUT_بٹ(0, 3); إذا (d->m_بٹ_وچ) { TDEFL_PUT_بٹ(0, 8 - d->m_بٹ_وچ); } لكل (i = 2; i; --i, z ^= 0xFFFF) { TDEFL_PUT_بٹ(z & 0xFFFF, 16); }
    }
  }

  MZ_ASSERT(d->m_pOutput_buf < d->m_p_Output_buf_سرا);

  memset(&d->m_huff_گنتی[0][0], 0, حجم(d->m_huff_گنتی[0][0]) * TDEFL_MAX_HUFF_SYMBOLS_0);
  memset(&d->m_huff_گنتی[1][0], 0, حجم(d->m_huff_گنتی[1][0]) * TDEFL_MAX_HUFF_SYMBOLS_1);

  d->m_p_LZ_کوڈ_buf = d->m_lz_کوڈ_buf + 1; d->m_pLZ_flags = d->m_lz_کوڈ_buf; d->m_عدد_flags_بایاں = 8; d->m_lz_کوڈ_buf_dict_pos += d->m_کل_lz_بائٹاں; d->m_کل_lz_بائٹاں = 0; d->m_بلاک_اشاریہ++;

  إذا ((n = (صحيح)(d->m_pOutput_buf - p_Output_buf_شروع)) != 0)
  {
    إذا (d->m_pPut_buf_func)
    {
      *d->m_p_وچ_buf_ناپ = d->m_pSrc - (ثابت mz_uint8 *)d->m_p_وچ_buf;
      إذا (!(*d->m_pPut_buf_func)(d->m_output_buf, n, d->m_pPut_buf_user))
        أرجع (d->m_prev_return_حالت = TDEFL_حالت_PUT_BUF_FAILED);
    }
    وإلا إذا (p_Output_buf_شروع == d->m_output_buf)
    {
      صحيح بائٹاں_منزل_copy = (صحيح)MZ_MIN((size_t)n, (size_t)(*d->m_p_باہرلا_buf_ناپ - d->m_باہرلا_buf_ofs));
      حافظہ_نقل((mz_uint8 *)d->m_p_باہرلا_buf + d->m_باہرلا_buf_ofs, d->m_output_buf, بائٹاں_منزل_copy);
      d->m_باہرلا_buf_ofs += بائٹاں_منزل_copy;
      إذا ((n -= بائٹاں_منزل_copy) != 0)
      {
        d->m_output_flush_ofs = بائٹاں_منزل_copy;
        d->m_output_flush_بچیا = n;
      }
    }
    وإلا
    {
      d->m_باہرلا_buf_ofs += n;
    }
  }

  أرجع d->m_output_flush_بچیا;
}

#إذا MINIZ_USE_UNALIGNED_LOADS_AND_STORES
#تعریف_کرو TDEFL_READ_UNALIGNED_لفظ(p) *(ثابت mz_uint16*)(p)
ساكن MZ_FORCEINLINE فراغ tdefl_لبھو_میل(tdefl_compressor *d, mz_uint lookahead_pos, mz_uint max_dist, mz_uint max_میل_len, mz_uint *p_میل_dist, mz_uint *p_میل_len)
{
  mz_uint dist, pos = lookahead_pos & TDEFL_LZ_DICT_ناپ_نقاب, میل_len = *p_میل_len, probe_pos = pos, اگلا_probe_pos, probe_len;
  mz_uint عدد_probes_بایاں = d->m_max_probes[میل_len >= 32];
  ثابت mz_uint16 *s = (ثابت mz_uint16*)(d->m_dict + pos), *p, *q;
  mz_uint16 c01 = TDEFL_READ_UNALIGNED_لفظ(&d->m_dict[pos + میل_len - 1]), s01 = TDEFL_READ_UNALIGNED_لفظ(s);
  MZ_ASSERT(max_میل_len <= TDEFL_MAX_میل_LEN); إذا (max_میل_len <= میل_len) أرجع;
  لكل ( ; ; )
  {
    لكل ( ; ; )
    {
      إذا (--عدد_probes_بایاں == 0) أرجع;
      #تعریف_کرو TDEFL_PROBE \
        اگلا_probe_pos = d->m_اگلا[probe_pos]; \
        إذا ((!اگلا_probe_pos) || ((dist = (mz_uint16)(lookahead_pos - اگلا_probe_pos)) > max_dist)) أرجع; \
        probe_pos = اگلا_probe_pos & TDEFL_LZ_DICT_ناپ_نقاب; \
        إذا (TDEFL_READ_UNALIGNED_لفظ(&d->m_dict[probe_pos + میل_len - 1]) == c01) اكسر;
      TDEFL_PROBE
      TDEFL_PROBE
      TDEFL_PROBE
    }
    إذا (!dist) اكسر;
    q = (ثابت mz_uint16*)(d->m_dict + probe_pos);
    إذا (TDEFL_READ_UNALIGNED_لفظ(q) != s01) استمر;
    p = s; probe_len = 32;
    افعل { } طالما ( (TDEFL_READ_UNALIGNED_لفظ(++p) == TDEFL_READ_UNALIGNED_لفظ(++q)) && (TDEFL_READ_UNALIGNED_لفظ(++p) == TDEFL_READ_UNALIGNED_لفظ(++q)) &&
                   (TDEFL_READ_UNALIGNED_لفظ(++p) == TDEFL_READ_UNALIGNED_لفظ(++q)) && (TDEFL_READ_UNALIGNED_لفظ(++p) == TDEFL_READ_UNALIGNED_لفظ(++q)) && (--probe_len > 0) );
    إذا (!probe_len)
    {
      *p_میل_dist = dist; *p_میل_len = MZ_MIN(max_میل_len, TDEFL_MAX_میل_LEN); اكسر;
    }
    وإلا إذا ((probe_len = ((mz_uint)(p - s) * 2) + (mz_uint)(*(ثابت mz_uint8*)p == *(ثابت mz_uint8*)q)) > میل_len)
    {
      *p_میل_dist = dist; إذا ((*p_میل_len = میل_len = MZ_MIN(max_میل_len, probe_len)) == max_میل_len) اكسر;
      c01 = TDEFL_READ_UNALIGNED_لفظ(&d->m_dict[pos + میل_len - 1]);
    }
  }
}
#وإلا
ساكن MZ_FORCEINLINE فراغ tdefl_لبھو_میل(tdefl_compressor *d, mz_uint lookahead_pos, mz_uint max_dist, mz_uint max_میل_len, mz_uint *p_میل_dist, mz_uint *p_میل_len)
{
  mz_uint dist, pos = lookahead_pos & TDEFL_LZ_DICT_ناپ_نقاب, میل_len = *p_میل_len, probe_pos = pos, اگلا_probe_pos, probe_len;
  mz_uint عدد_probes_بایاں = d->m_max_probes[میل_len >= 32];
  ثابت mz_uint8 *s = d->m_dict + pos, *p, *q;
  mz_uint8 c0 = d->m_dict[pos + میل_len], c1 = d->m_dict[pos + میل_len - 1];
  MZ_ASSERT(max_میل_len <= TDEFL_MAX_میل_LEN); إذا (max_میل_len <= میل_len) أرجع;
  لكل ( ; ; )
  {
    لكل ( ; ; )
    {
      إذا (--عدد_probes_بایاں == 0) أرجع;
      #تعریف_کرو TDEFL_PROBE \
        اگلا_probe_pos = d->m_اگلا[probe_pos]; \
        إذا ((!اگلا_probe_pos) || ((dist = (mz_uint16)(lookahead_pos - اگلا_probe_pos)) > max_dist)) أرجع; \
        probe_pos = اگلا_probe_pos & TDEFL_LZ_DICT_ناپ_نقاب; \
        إذا ((d->m_dict[probe_pos + میل_len] == c0) && (d->m_dict[probe_pos + میل_len - 1] == c1)) اكسر;
      TDEFL_PROBE
      TDEFL_PROBE
      TDEFL_PROBE
    }
    إذا (!dist) اكسر;
    p = s; q = d->m_dict + probe_pos;
    لكل (probe_len = 0; probe_len < max_میل_len; probe_len++) {
        إذا (*p++ != *q++) اكسر;
    }
    إذا (probe_len > میل_len)
    {
      *p_میل_dist = dist;
      إذا ((*p_میل_len = میل_len = probe_len) == max_میل_len) أرجع;
      c0 = d->m_dict[pos + میل_len]; c1 = d->m_dict[pos + میل_len - 1];
    }
  }
}
#جے_انت // #if MINIZ_USE_UNALIGNED_LOADS_AND_STORES

#إذا MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
ساكن mz_bool tdefl_compress_fast(tdefl_compressor *d)
{
  // Faster, minimally featured LZRW1-style match+parse loop with better register utilization. Intended for applications where raw throughput is valued more highly than ratio.
  mz_uint lookahead_pos = d->m_lookahead_pos, lookahead_ناپ = d->m_lookahead_ناپ, dict_ناپ = d->m_dict_ناپ, کل_lz_بائٹاں = d->m_کل_lz_بائٹاں, عدد_flags_بایاں = d->m_عدد_flags_بایاں;
  mz_uint8 *p_LZ_کوڈ_buf = d->m_p_LZ_کوڈ_buf, *pLZ_flags = d->m_pLZ_flags;
  mz_uint cur_pos = lookahead_pos & TDEFL_LZ_DICT_ناپ_نقاب;

  طالما ((d->m_src_buf_بایاں) || ((d->m_flush) && (lookahead_ناپ)))
  {
    ثابت mz_uint TDEFL_COMP_FAST_LOOKAHEAD_ناپ = 4096;
    mz_uint dst_pos = (lookahead_pos + lookahead_ناپ) & TDEFL_LZ_DICT_ناپ_نقاب;
    mz_uint عدد_بائٹاں_منزل_process = (mz_uint)MZ_MIN(d->m_src_buf_بایاں, TDEFL_COMP_FAST_LOOKAHEAD_ناپ - lookahead_ناپ);
    d->m_src_buf_بایاں -= عدد_بائٹاں_منزل_process;
    lookahead_ناپ += عدد_بائٹاں_منزل_process;

    طالما (عدد_بائٹاں_منزل_process)
    {
      mz_uint32 n = MZ_MIN(TDEFL_LZ_DICT_ناپ - dst_pos, عدد_بائٹاں_منزل_process);
      حافظہ_نقل(d->m_dict + dst_pos, d->m_pSrc, n);
      إذا (dst_pos < (TDEFL_MAX_میل_LEN - 1))
        حافظہ_نقل(d->m_dict + TDEFL_LZ_DICT_ناپ + dst_pos, d->m_pSrc, MZ_MIN(n, (TDEFL_MAX_میل_LEN - 1) - dst_pos));
      d->m_pSrc += n;
      dst_pos = (dst_pos + n) & TDEFL_LZ_DICT_ناپ_نقاب;
      عدد_بائٹاں_منزل_process -= n;
    }

    dict_ناپ = MZ_MIN(TDEFL_LZ_DICT_ناپ - lookahead_ناپ, dict_ناپ);
    إذا ((!d->m_flush) && (lookahead_ناپ < TDEFL_COMP_FAST_LOOKAHEAD_ناپ)) اكسر;

    طالما (lookahead_ناپ >= 4)
    {
      mz_uint cur_میل_dist, cur_میل_len = 1;
      mz_uint8 *pCur_dict = d->m_dict + cur_pos;
      mz_uint پہلا_trigram = (*(ثابت mz_uint32 *)pCur_dict) & 0xFFFFFF;
      mz_uint hash = (پہلا_trigram ^ (پہلا_trigram >> (24 - (TDEFL_LZ_HASH_بٹ - 8)))) & TDEFL_LEVEL1_HASH_ناپ_نقاب;
      mz_uint probe_pos = d->m_hash[hash];
      d->m_hash[hash] = (mz_uint16)lookahead_pos;

      إذا (((cur_میل_dist = (mz_uint16)(lookahead_pos - probe_pos)) <= dict_ناپ) && ((*(ثابت mz_uint32 *)(d->m_dict + (probe_pos &= TDEFL_LZ_DICT_ناپ_نقاب)) & 0xFFFFFF) == پہلا_trigram))
      {
        ثابت mz_uint16 *p = (ثابت mz_uint16 *)pCur_dict;
        ثابت mz_uint16 *q = (ثابت mz_uint16 *)(d->m_dict + probe_pos);
        mz_uint32 probe_len = 32;
        افعل { } طالما ( (TDEFL_READ_UNALIGNED_لفظ(++p) == TDEFL_READ_UNALIGNED_لفظ(++q)) && (TDEFL_READ_UNALIGNED_لفظ(++p) == TDEFL_READ_UNALIGNED_لفظ(++q)) &&
          (TDEFL_READ_UNALIGNED_لفظ(++p) == TDEFL_READ_UNALIGNED_لفظ(++q)) && (TDEFL_READ_UNALIGNED_لفظ(++p) == TDEFL_READ_UNALIGNED_لفظ(++q)) && (--probe_len > 0) );
        cur_میل_len = ((mz_uint)(p - (ثابت mz_uint16 *)pCur_dict) * 2) + (mz_uint)(*(ثابت mz_uint8 *)p == *(ثابت mz_uint8 *)q);
        إذا (!probe_len)
          cur_میل_len = cur_میل_dist ? TDEFL_MAX_میل_LEN : 0;

        إذا ((cur_میل_len < TDEFL_MIN_میل_LEN) || ((cur_میل_len == TDEFL_MIN_میل_LEN) && (cur_میل_dist >= 8U*1024U)))
        {
          cur_میل_len = 1;
          *p_LZ_کوڈ_buf++ = (mz_uint8)پہلا_trigram;
          *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
          d->m_huff_گنتی[0][(mz_uint8)پہلا_trigram]++;
        }
        وإلا
        {
          mz_uint32 s0, s1;
          cur_میل_len = MZ_MIN(cur_میل_len, lookahead_ناپ);

          MZ_ASSERT((cur_میل_len >= TDEFL_MIN_میل_LEN) && (cur_میل_dist >= 1) && (cur_میل_dist <= TDEFL_LZ_DICT_ناپ));

          cur_میل_dist--;

          p_LZ_کوڈ_buf[0] = (mz_uint8)(cur_میل_len - TDEFL_MIN_میل_LEN);
          *(mz_uint16 *)(&p_LZ_کوڈ_buf[1]) = (mz_uint16)cur_میل_dist;
          p_LZ_کوڈ_buf += 3;
          *pLZ_flags = (mz_uint8)((*pLZ_flags >> 1) | 0x80);

          s0 = s_tdefl_small_dist_sym[cur_میل_dist & 511];
          s1 = s_tdefl_large_dist_sym[cur_میل_dist >> 8];
          d->m_huff_گنتی[1][(cur_میل_dist < 512) ? s0 : s1]++;

          d->m_huff_گنتی[0][s_tdefl_len_sym[cur_میل_len - TDEFL_MIN_میل_LEN]]++;
        }
      }
      وإلا
      {
        *p_LZ_کوڈ_buf++ = (mz_uint8)پہلا_trigram;
        *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
        d->m_huff_گنتی[0][(mz_uint8)پہلا_trigram]++;
      }

      إذا (--عدد_flags_بایاں == 0) { عدد_flags_بایاں = 8; pLZ_flags = p_LZ_کوڈ_buf++; }

      کل_lz_بائٹاں += cur_میل_len;
      lookahead_pos += cur_میل_len;
      dict_ناپ = MZ_MIN(dict_ناپ + cur_میل_len, TDEFL_LZ_DICT_ناپ);
      cur_pos = (cur_pos + cur_میل_len) & TDEFL_LZ_DICT_ناپ_نقاب;
      MZ_ASSERT(lookahead_ناپ >= cur_میل_len);
      lookahead_ناپ -= cur_میل_len;

      إذا (p_LZ_کوڈ_buf > &d->m_lz_کوڈ_buf[TDEFL_LZ_کوڈ_BUF_ناپ - 8])
      {
        صحيح n;
        d->m_lookahead_pos = lookahead_pos; d->m_lookahead_ناپ = lookahead_ناپ; d->m_dict_ناپ = dict_ناپ;
        d->m_کل_lz_بائٹاں = کل_lz_بائٹاں; d->m_p_LZ_کوڈ_buf = p_LZ_کوڈ_buf; d->m_pLZ_flags = pLZ_flags; d->m_عدد_flags_بایاں = عدد_flags_بایاں;
        إذا ((n = tdefl_flush_بلاک(d, 0)) != 0)
          أرجع (n < 0) ? MZ_FALSE : MZ_TRUE;
        کل_lz_بائٹاں = d->m_کل_lz_بائٹاں; p_LZ_کوڈ_buf = d->m_p_LZ_کوڈ_buf; pLZ_flags = d->m_pLZ_flags; عدد_flags_بایاں = d->m_عدد_flags_بایاں;
      }
    }

    طالما (lookahead_ناپ)
    {
      mz_uint8 lit = d->m_dict[cur_pos];

      کل_lz_بائٹاں++;
      *p_LZ_کوڈ_buf++ = lit;
      *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
      إذا (--عدد_flags_بایاں == 0) { عدد_flags_بایاں = 8; pLZ_flags = p_LZ_کوڈ_buf++; }

      d->m_huff_گنتی[0][lit]++;

      lookahead_pos++;
      dict_ناپ = MZ_MIN(dict_ناپ + 1, TDEFL_LZ_DICT_ناپ);
      cur_pos = (cur_pos + 1) & TDEFL_LZ_DICT_ناپ_نقاب;
      lookahead_ناپ--;

      إذا (p_LZ_کوڈ_buf > &d->m_lz_کوڈ_buf[TDEFL_LZ_کوڈ_BUF_ناپ - 8])
      {
        صحيح n;
        d->m_lookahead_pos = lookahead_pos; d->m_lookahead_ناپ = lookahead_ناپ; d->m_dict_ناپ = dict_ناپ;
        d->m_کل_lz_بائٹاں = کل_lz_بائٹاں; d->m_p_LZ_کوڈ_buf = p_LZ_کوڈ_buf; d->m_pLZ_flags = pLZ_flags; d->m_عدد_flags_بایاں = عدد_flags_بایاں;
        إذا ((n = tdefl_flush_بلاک(d, 0)) != 0)
          أرجع (n < 0) ? MZ_FALSE : MZ_TRUE;
        کل_lz_بائٹاں = d->m_کل_lz_بائٹاں; p_LZ_کوڈ_buf = d->m_p_LZ_کوڈ_buf; pLZ_flags = d->m_pLZ_flags; عدد_flags_بایاں = d->m_عدد_flags_بایاں;
      }
    }
  }

  d->m_lookahead_pos = lookahead_pos; d->m_lookahead_ناپ = lookahead_ناپ; d->m_dict_ناپ = dict_ناپ;
  d->m_کل_lz_بائٹاں = کل_lz_بائٹاں; d->m_p_LZ_کوڈ_buf = p_LZ_کوڈ_buf; d->m_pLZ_flags = pLZ_flags; d->m_عدد_flags_بایاں = عدد_flags_بایاں;
  أرجع MZ_TRUE;
}
#جے_انت // MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN

ساكن MZ_FORCEINLINE فراغ tdefl_ریکارڈ_literal(tdefl_compressor *d, mz_uint8 lit)
{
  d->m_کل_lz_بائٹاں++;
  *d->m_p_LZ_کوڈ_buf++ = lit;
  *d->m_pLZ_flags = (mz_uint8)(*d->m_pLZ_flags >> 1); إذا (--d->m_عدد_flags_بایاں == 0) { d->m_عدد_flags_بایاں = 8; d->m_pLZ_flags = d->m_p_LZ_کوڈ_buf++; }
  d->m_huff_گنتی[0][lit]++;
}

ساكن MZ_FORCEINLINE فراغ tdefl_ریکارڈ_میل(tdefl_compressor *d, mz_uint میل_len, mz_uint میل_dist)
{
  mz_uint32 s0, s1;

  MZ_ASSERT((میل_len >= TDEFL_MIN_میل_LEN) && (میل_dist >= 1) && (میل_dist <= TDEFL_LZ_DICT_ناپ));

  d->m_کل_lz_بائٹاں += میل_len;

  d->m_p_LZ_کوڈ_buf[0] = (mz_uint8)(میل_len - TDEFL_MIN_میل_LEN);

  میل_dist -= 1;
  d->m_p_LZ_کوڈ_buf[1] = (mz_uint8)(میل_dist & 0xFF);
  d->m_p_LZ_کوڈ_buf[2] = (mz_uint8)(میل_dist >> 8); d->m_p_LZ_کوڈ_buf += 3;

  *d->m_pLZ_flags = (mz_uint8)((*d->m_pLZ_flags >> 1) | 0x80); إذا (--d->m_عدد_flags_بایاں == 0) { d->m_عدد_flags_بایاں = 8; d->m_pLZ_flags = d->m_p_LZ_کوڈ_buf++; }

  s0 = s_tdefl_small_dist_sym[میل_dist & 511]; s1 = s_tdefl_large_dist_sym[(میل_dist >> 8) & 127];
  d->m_huff_گنتی[1][(میل_dist < 512) ? s0 : s1]++;

  إذا (میل_len >= TDEFL_MIN_میل_LEN) d->m_huff_گنتی[0][s_tdefl_len_sym[میل_len - TDEFL_MIN_میل_LEN]]++;
}

ساكن mz_bool tdefl_compress_عام(tdefl_compressor *d)
{
  ثابت mz_uint8 *pSrc = d->m_pSrc; size_t src_buf_بایاں = d->m_src_buf_بایاں;
  tdefl_flush flush = d->m_flush;

  طالما ((src_buf_بایاں) || ((flush) && (d->m_lookahead_ناپ)))
  {
    mz_uint len_منزل_move, cur_میل_dist, cur_میل_len, cur_pos;
    // Update dictionary and hash chains. Keeps the lookahead size equal to TDEFL_MAX_MATCH_LEN.
    إذا ((d->m_lookahead_ناپ + d->m_dict_ناپ) >= (TDEFL_MIN_میل_LEN - 1))
    {
      mz_uint dst_pos = (d->m_lookahead_pos + d->m_lookahead_ناپ) & TDEFL_LZ_DICT_ناپ_نقاب, ins_pos = d->m_lookahead_pos + d->m_lookahead_ناپ - 2;
      mz_uint hash = (d->m_dict[ins_pos & TDEFL_LZ_DICT_ناپ_نقاب] << TDEFL_LZ_HASH_کھسکاؤ) ^ d->m_dict[(ins_pos + 1) & TDEFL_LZ_DICT_ناپ_نقاب];
      mz_uint عدد_بائٹاں_منزل_process = (mz_uint)MZ_MIN(src_buf_بایاں, TDEFL_MAX_میل_LEN - d->m_lookahead_ناپ);
      ثابت mz_uint8 *p_Src_سرا = pSrc ? pSrc + عدد_بائٹاں_منزل_process : عدم;
      src_buf_بایاں -= عدد_بائٹاں_منزل_process;
      d->m_lookahead_ناپ += عدد_بائٹاں_منزل_process;
      طالما (pSrc != p_Src_سرا)
      {
        mz_uint8 c = *pSrc++; d->m_dict[dst_pos] = c; إذا (dst_pos < (TDEFL_MAX_میل_LEN - 1)) d->m_dict[TDEFL_LZ_DICT_ناپ + dst_pos] = c;
        hash = ((hash << TDEFL_LZ_HASH_کھسکاؤ) ^ c) & (TDEFL_LZ_HASH_ناپ - 1);
        d->m_اگلا[ins_pos & TDEFL_LZ_DICT_ناپ_نقاب] = d->m_hash[hash]; d->m_hash[hash] = (mz_uint16)(ins_pos);
        dst_pos = (dst_pos + 1) & TDEFL_LZ_DICT_ناپ_نقاب; ins_pos++;
      }
    }
    وإلا
    {
      طالما ((src_buf_بایاں) && (d->m_lookahead_ناپ < TDEFL_MAX_میل_LEN))
      {
        mz_uint8 c = *pSrc++;
        mz_uint dst_pos = (d->m_lookahead_pos + d->m_lookahead_ناپ) & TDEFL_LZ_DICT_ناپ_نقاب;
        src_buf_بایاں--;
        d->m_dict[dst_pos] = c;
        إذا (dst_pos < (TDEFL_MAX_میل_LEN - 1))
          d->m_dict[TDEFL_LZ_DICT_ناپ + dst_pos] = c;
        إذا ((++d->m_lookahead_ناپ + d->m_dict_ناپ) >= TDEFL_MIN_میل_LEN)
        {
          mz_uint ins_pos = d->m_lookahead_pos + (d->m_lookahead_ناپ - 1) - 2;
          mz_uint hash = ((d->m_dict[ins_pos & TDEFL_LZ_DICT_ناپ_نقاب] << (TDEFL_LZ_HASH_کھسکاؤ * 2)) ^ (d->m_dict[(ins_pos + 1) & TDEFL_LZ_DICT_ناپ_نقاب] << TDEFL_LZ_HASH_کھسکاؤ) ^ c) & (TDEFL_LZ_HASH_ناپ - 1);
          d->m_اگلا[ins_pos & TDEFL_LZ_DICT_ناپ_نقاب] = d->m_hash[hash]; d->m_hash[hash] = (mz_uint16)(ins_pos);
        }
      }
    }
    d->m_dict_ناپ = MZ_MIN(TDEFL_LZ_DICT_ناپ - d->m_lookahead_ناپ, d->m_dict_ناپ);
    إذا ((!flush) && (d->m_lookahead_ناپ < TDEFL_MAX_میل_LEN))
      اكسر;

    // Simple lazy/greedy parsing state machine.
    len_منزل_move = 1; cur_میل_dist = 0; cur_میل_len = d->m_saved_میل_len ? d->m_saved_میل_len : (TDEFL_MIN_میل_LEN - 1); cur_pos = d->m_lookahead_pos & TDEFL_LZ_DICT_ناپ_نقاب;
    إذا (d->m_flags & (TDEFL_RLE_MATCHES | TDEFL_FORCE_ALL_RAW_بلاکاں))
    {
      إذا ((d->m_dict_ناپ) && (!(d->m_flags & TDEFL_FORCE_ALL_RAW_بلاکاں)))
      {
        mz_uint8 c = d->m_dict[(cur_pos - 1) & TDEFL_LZ_DICT_ناپ_نقاب];
        cur_میل_len = 0; طالما (cur_میل_len < d->m_lookahead_ناپ) { إذا (d->m_dict[cur_pos + cur_میل_len] != c) اكسر; cur_میل_len++; }
        إذا (cur_میل_len < TDEFL_MIN_میل_LEN) cur_میل_len = 0; وإلا cur_میل_dist = 1;
      }
    }
    وإلا
    {
      tdefl_لبھو_میل(d, d->m_lookahead_pos, d->m_dict_ناپ, d->m_lookahead_ناپ, &cur_میل_dist, &cur_میل_len);
    }
    إذا (((cur_میل_len == TDEFL_MIN_میل_LEN) && (cur_میل_dist >= 8U*1024U)) || (cur_pos == cur_میل_dist) || ((d->m_flags & TDEFL_FILTER_MATCHES) && (cur_میل_len <= 5)))
    {
      cur_میل_dist = cur_میل_len = 0;
    }
    إذا (d->m_saved_میل_len)
    {
      إذا (cur_میل_len > d->m_saved_میل_len)
      {
        tdefl_ریکارڈ_literal(d, (mz_uint8)d->m_saved_lit);
        إذا (cur_میل_len >= 128)
        {
          tdefl_ریکارڈ_میل(d, cur_میل_len, cur_میل_dist);
          d->m_saved_میل_len = 0; len_منزل_move = cur_میل_len;
        }
        وإلا
        {
          d->m_saved_lit = d->m_dict[cur_pos]; d->m_saved_میل_dist = cur_میل_dist; d->m_saved_میل_len = cur_میل_len;
        }
      }
      وإلا
      {
        tdefl_ریکارڈ_میل(d, d->m_saved_میل_len, d->m_saved_میل_dist);
        len_منزل_move = d->m_saved_میل_len - 1; d->m_saved_میل_len = 0;
      }
    }
    وإلا إذا (!cur_میل_dist)
      tdefl_ریکارڈ_literal(d, d->m_dict[MZ_MIN(cur_pos, حجم(d->m_dict) - 1)]);
    وإلا إذا ((d->m_greedy_parsing) || (d->m_flags & TDEFL_RLE_MATCHES) || (cur_میل_len >= 128))
    {
      tdefl_ریکارڈ_میل(d, cur_میل_len, cur_میل_dist);
      len_منزل_move = cur_میل_len;
    }
    وإلا
    {
      d->m_saved_lit = d->m_dict[MZ_MIN(cur_pos, حجم(d->m_dict) - 1)]; d->m_saved_میل_dist = cur_میل_dist; d->m_saved_میل_len = cur_میل_len;
    }
    // Move the lookahead forward by len_to_move bytes.
    d->m_lookahead_pos += len_منزل_move;
    MZ_ASSERT(d->m_lookahead_ناپ >= len_منزل_move);
    d->m_lookahead_ناپ -= len_منزل_move;
    d->m_dict_ناپ = MZ_MIN(d->m_dict_ناپ + len_منزل_move, TDEFL_LZ_DICT_ناپ);
    // Check if it's time to flush the current LZ codes to the internal output buffer.
    إذا ( (d->m_p_LZ_کوڈ_buf > &d->m_lz_کوڈ_buf[TDEFL_LZ_کوڈ_BUF_ناپ - 8]) ||
         ( (d->m_کل_lz_بائٹاں > 31*1024) && (((((mz_uint)(d->m_p_LZ_کوڈ_buf - d->m_lz_کوڈ_buf) * 115) >> 7) >= d->m_کل_lz_بائٹاں) || (d->m_flags & TDEFL_FORCE_ALL_RAW_بلاکاں))) )
    {
      صحيح n;
      d->m_pSrc = pSrc; d->m_src_buf_بایاں = src_buf_بایاں;
      إذا ((n = tdefl_flush_بلاک(d, 0)) != 0)
        أرجع (n < 0) ? MZ_FALSE : MZ_TRUE;
    }
  }

  d->m_pSrc = pSrc; d->m_src_buf_بایاں = src_buf_بایاں;
  أرجع MZ_TRUE;
}

ساكن tdefl_حالت tdefl_flush_output_بفر(tdefl_compressor *d)
{
  إذا (d->m_p_وچ_buf_ناپ)
  {
    *d->m_p_وچ_buf_ناپ = d->m_pSrc - (ثابت mz_uint8 *)d->m_p_وچ_buf;
  }

  إذا (d->m_p_باہرلا_buf_ناپ)
  {
    size_t n = MZ_MIN(*d->m_p_باہرلا_buf_ناپ - d->m_باہرلا_buf_ofs, d->m_output_flush_بچیا);
    حافظہ_نقل((mz_uint8 *)d->m_p_باہرلا_buf + d->m_باہرلا_buf_ofs, d->m_output_buf + d->m_output_flush_ofs, n);
    d->m_output_flush_ofs += (mz_uint)n;
    d->m_output_flush_بچیا -= (mz_uint)n;
    d->m_باہرلا_buf_ofs += n;

    *d->m_p_باہرلا_buf_ناپ = d->m_باہرلا_buf_ofs;
  }

  أرجع (d->m_مکمل && !d->m_output_flush_بچیا) ? TDEFL_حالت_پورا : TDEFL_حالت_OKAY;
}

tdefl_حالت tdefl_compress(tdefl_compressor *d, ثابت فراغ *p_وچ_buf, size_t *p_وچ_buf_ناپ, فراغ *p_باہرلا_buf, size_t *p_باہرلا_buf_ناپ, tdefl_flush flush)
{
  إذا (!d)
  {
    إذا (p_وچ_buf_ناپ) *p_وچ_buf_ناپ = 0;
    إذا (p_باہرلا_buf_ناپ) *p_باہرلا_buf_ناپ = 0;
    أرجع TDEFL_حالت_BAD_PARAM;
  }

  d->m_p_وچ_buf = p_وچ_buf; d->m_p_وچ_buf_ناپ = p_وچ_buf_ناپ;
  d->m_p_باہرلا_buf = p_باہرلا_buf; d->m_p_باہرلا_buf_ناپ = p_باہرلا_buf_ناپ;
  d->m_pSrc = (ثابت mz_uint8 *)(p_وچ_buf); d->m_src_buf_بایاں = p_وچ_buf_ناپ ? *p_وچ_buf_ناپ : 0;
  d->m_باہرلا_buf_ofs = 0;
  d->m_flush = flush;

  إذا ( ((d->m_pPut_buf_func != عدم) == ((p_باہرلا_buf != عدم) || (p_باہرلا_buf_ناپ != عدم))) || (d->m_prev_return_حالت != TDEFL_حالت_OKAY) ||
        (d->m_چاہندا_منزل_انت && (flush != TDEFL_انت)) || (p_وچ_buf_ناپ && *p_وچ_buf_ناپ && !p_وچ_buf) || (p_باہرلا_buf_ناپ && *p_باہرلا_buf_ناپ && !p_باہرلا_buf) )
  {
    إذا (p_وچ_buf_ناپ) *p_وچ_buf_ناپ = 0;
    إذا (p_باہرلا_buf_ناپ) *p_باہرلا_buf_ناپ = 0;
    أرجع (d->m_prev_return_حالت = TDEFL_حالت_BAD_PARAM);
  }
  d->m_چاہندا_منزل_انت |= (flush == TDEFL_انت);

  إذا ((d->m_output_flush_بچیا) || (d->m_مکمل))
    أرجع (d->m_prev_return_حالت = tdefl_flush_output_بفر(d));

#إذا MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  إذا (((d->m_flags & TDEFL_MAX_PROBES_نقاب) == 1) &&
      ((d->m_flags & TDEFL_GREEDY_PARSING_FLAG) != 0) &&
      ((d->m_flags & (TDEFL_FILTER_MATCHES | TDEFL_FORCE_ALL_RAW_بلاکاں | TDEFL_RLE_MATCHES)) == 0))
  {
    إذا (!tdefl_compress_fast(d))
      أرجع d->m_prev_return_حالت;
  }
  وإلا
#جے_انت // #if MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  {
    إذا (!tdefl_compress_عام(d))
      أرجع d->m_prev_return_حالت;
  }

  إذا ((d->m_flags & (TDEFL_WRITE_ZLIB_سرخی | TDEFL_COMPUTE_ADLER32)) && (p_وچ_buf))
    d->m_adler32 = (mz_uint32)mz_adler32(d->m_adler32, (ثابت mz_uint8 *)p_وچ_buf, d->m_pSrc - (ثابت mz_uint8 *)p_وچ_buf);

  إذا ((flush) && (!d->m_lookahead_ناپ) && (!d->m_src_buf_بایاں) && (!d->m_output_flush_بچیا))
  {
    إذا (tdefl_flush_بلاک(d, flush) < 0)
      أرجع d->m_prev_return_حالت;
    d->m_مکمل = (flush == TDEFL_انت);
    إذا (flush == TDEFL_بھریا_FLUSH) { MZ_CLEAR_ARR(d->m_hash); MZ_CLEAR_ARR(d->m_اگلا); d->m_dict_ناپ = 0; }
  }

  أرجع (d->m_prev_return_حالت = tdefl_flush_output_بفر(d));
}

tdefl_حالت tdefl_compress_بفر(tdefl_compressor *d, ثابت فراغ *p_وچ_buf, size_t وچ_buf_ناپ, tdefl_flush flush)
{
  MZ_ASSERT(d->m_pPut_buf_func); أرجع tdefl_compress(d, p_وچ_buf, &وچ_buf_ناپ, عدم, عدم, flush);
}

tdefl_حالت tdefl_init(tdefl_compressor *d, tdefl_put_buf_func_ptr pPut_buf_func, فراغ *pPut_buf_user, صحيح flags)
{
  d->m_pPut_buf_func = pPut_buf_func; d->m_pPut_buf_user = pPut_buf_user;
  d->m_flags = (mz_uint)(flags); d->m_max_probes[0] = 1 + ((flags & 0xFFF) + 2) / 3; d->m_greedy_parsing = (flags & TDEFL_GREEDY_PARSING_FLAG) != 0;
  d->m_max_probes[1] = 1 + (((flags & 0xFFF) >> 2) + 2) / 3;
  إذا (!(flags & TDEFL_NONDETERMINISTIC_PARSING_FLAG)) MZ_CLEAR_ARR(d->m_hash);
  d->m_lookahead_pos = d->m_lookahead_ناپ = d->m_dict_ناپ = d->m_کل_lz_بائٹاں = d->m_lz_کوڈ_buf_dict_pos = d->m_بٹ_وچ = 0;
  d->m_output_flush_ofs = d->m_output_flush_بچیا = d->m_مکمل = d->m_بلاک_اشاریہ = d->m_ثنائی_ہندسہ_بفر = d->m_چاہندا_منزل_انت = 0;
  d->m_p_LZ_کوڈ_buf = d->m_lz_کوڈ_buf + 1; d->m_pLZ_flags = d->m_lz_کوڈ_buf; d->m_عدد_flags_بایاں = 8;
  d->m_pOutput_buf = d->m_output_buf; d->m_p_Output_buf_سرا = d->m_output_buf; d->m_prev_return_حالت = TDEFL_حالت_OKAY;
  d->m_saved_میل_dist = d->m_saved_میل_len = d->m_saved_lit = 0; d->m_adler32 = 1;
  d->m_p_وچ_buf = عدم; d->m_p_باہرلا_buf = عدم;
  d->m_p_وچ_buf_ناپ = عدم; d->m_p_باہرلا_buf_ناپ = عدم;
  d->m_flush = TDEFL_NO_FLUSH; d->m_pSrc = عدم; d->m_src_buf_بایاں = 0; d->m_باہرلا_buf_ofs = 0;
  memset(&d->m_huff_گنتی[0][0], 0, حجم(d->m_huff_گنتی[0][0]) * TDEFL_MAX_HUFF_SYMBOLS_0);
  memset(&d->m_huff_گنتی[1][0], 0, حجم(d->m_huff_گنتی[1][0]) * TDEFL_MAX_HUFF_SYMBOLS_1);
  أرجع TDEFL_حالت_OKAY;
}

#جے_بنا_تعریف MINIZ_SDL_NOUNUSED
tdefl_حالت tdefl_get_prev_return_حالت(tdefl_compressor *d)
{
  أرجع d->m_prev_return_حالت;
}

mz_uint32 tdefl_get_adler32(tdefl_compressor *d)
{
  أرجع d->m_adler32;
}

mz_bool tdefl_compress_mem_منزل_output(ثابت فراغ *pBuf, size_t buf_len, tdefl_put_buf_func_ptr pPut_buf_func, فراغ *pPut_buf_user, صحيح flags)
{
  tdefl_compressor *pComp; mz_bool succeeded; إذا (((buf_len) && (!pBuf)) || (!pPut_buf_func)) أرجع MZ_FALSE;
  pComp = (tdefl_compressor*)MZ_MALLOC(حجم(tdefl_compressor)); إذا (!pComp) أرجع MZ_FALSE;
  succeeded = (tdefl_init(pComp, pPut_buf_func, pPut_buf_user, flags) == TDEFL_حالت_OKAY);
  succeeded = succeeded && (tdefl_compress_بفر(pComp, pBuf, buf_len, TDEFL_انت) == TDEFL_حالت_پورا);
  MZ_FREE(pComp); أرجع succeeded;
}
#جے_انت /* MINIZ_SDL_NOUNUSED */

تعريفنوع بنية
{
  size_t m_ناپ, m_سمرتھا;
  mz_uint8 *m_pBuf;
  mz_bool m_expandable;
} tdefl_output_بفر;

ساكن mz_bool tdefl_output_بفر_putter(ثابت فراغ *pBuf, صحيح len, فراغ *pUser)
{
  tdefl_output_بفر *p = (tdefl_output_بفر *)pUser;
  size_t new_ناپ = p->m_ناپ + len;
  إذا (new_ناپ > p->m_سمرتھا)
  {
    size_t new_سمرتھا = p->m_سمرتھا; mz_uint8 *pNew_buf; إذا (!p->m_expandable) أرجع MZ_FALSE;
    افعل { new_سمرتھا = MZ_MAX(128U, new_سمرتھا << 1U); } طالما (new_ناپ > new_سمرتھا);
    pNew_buf = (mz_uint8*)MZ_REALLOC(p->m_pBuf, new_سمرتھا); إذا (!pNew_buf) أرجع MZ_FALSE;
    p->m_pBuf = pNew_buf; p->m_سمرتھا = new_سمرتھا;
  }
  حافظہ_نقل((mz_uint8*)p->m_pBuf + p->m_ناپ, pBuf, len); p->m_ناپ = new_ناپ;
  أرجع MZ_TRUE;
}

#جے_بنا_تعریف MINIZ_SDL_NOUNUSED
فراغ *tdefl_compress_mem_منزل_ڈھیر(ثابت فراغ *pSrc_buf, size_t src_buf_len, size_t *p_باہرلا_len, صحيح flags)
{
  tdefl_output_بفر باہرلا_buf; MZ_CLEAR_OBJ(باہرلا_buf);
  إذا (!p_باہرلا_len) أرجع MZ_FALSE; وإلا *p_باہرلا_len = 0;
  باہرلا_buf.m_expandable = MZ_TRUE;
  إذا (!tdefl_compress_mem_منزل_output(pSrc_buf, src_buf_len, tdefl_output_بفر_putter, &باہرلا_buf, flags)) أرجع عدم;
  *p_باہرلا_len = باہرلا_buf.m_ناپ; أرجع باہرلا_buf.m_pBuf;
}

size_t tdefl_compress_mem_منزل_mem(فراغ *p_باہرلا_buf, size_t باہرلا_buf_len, ثابت فراغ *pSrc_buf, size_t src_buf_len, صحيح flags)
{
  tdefl_output_بفر باہرلا_buf; MZ_CLEAR_OBJ(باہرلا_buf);
  إذا (!p_باہرلا_buf) أرجع 0;
  باہرلا_buf.m_pBuf = (mz_uint8*)p_باہرلا_buf; باہرلا_buf.m_سمرتھا = باہرلا_buf_len;
  إذا (!tdefl_compress_mem_منزل_output(pSrc_buf, src_buf_len, tdefl_output_بفر_putter, &باہرلا_buf, flags)) أرجع 0;
  أرجع باہرلا_buf.m_ناپ;
}
#جے_انت /* MINIZ_SDL_NOUNUSED */

#جے_بنا_تعریف MINIZ_NO_ZLIB_APIS
ساكن ثابت mz_uint s_tdefl_عدد_probes[11] = { 0, 1, 6, 32,  16, 32, 128, 256,  512, 768, 1500 };

// level may actually range from [0,10] (10 is a "hidden" max level, where we want a bit more compression and it's fine if throughput to fall off a cliff on some files).
mz_uint tdefl_create_comp_flags_from_zip_params(صحيح level, صحيح کھڑکی_بٹ, صحيح strategy)
{
  mz_uint comp_flags = s_tdefl_عدد_probes[(level >= 0) ? MZ_MIN(10, level) : MZ_DEFAULT_LEVEL] | ((level <= 3) ? TDEFL_GREEDY_PARSING_FLAG : 0);
  إذا (کھڑکی_بٹ > 0) comp_flags |= TDEFL_WRITE_ZLIB_سرخی;

  إذا (!level) comp_flags |= TDEFL_FORCE_ALL_RAW_بلاکاں;
  وإلا إذا (strategy == MZ_FILTERED) comp_flags |= TDEFL_FILTER_MATCHES;
  وإلا إذا (strategy == MZ_HUFFMAN_ONLY) comp_flags &= ~TDEFL_MAX_PROBES_نقاب;
  وإلا إذا (strategy == MZ_FIXED) comp_flags |= TDEFL_FORCE_ALL_STATIC_بلاکاں;
  وإلا إذا (strategy == MZ_RLE) comp_flags |= TDEFL_RLE_MATCHES;

  أرجع comp_flags;
}
#جے_انت //MINIZ_NO_ZLIB_APIS

#جے_تعریف_شدہ _MSC_VER
#ہدایت warning (ڈالو)
#ہدایت warning (disable:4204) // nonstandard extension used : non-constant aggregate initializer (also supported by GNU C and C99, so no big deal)
#جے_انت

// Simple PNG writer function by Alex Evans, 2011. Released into the public domain: https://gist.github.com/908299, more context at
// http://altdevblogaday.org/2011/04/06/a-smaller-jpg-encoder/.
// This is actually a modification of Alex's original code so PNG files generated by this function pass pngcheck.
MINIZ_STATIC فراغ *tdefl_write_image_منزل_png_file_وچ_حافظہ_ex(ثابت فراغ *pImage, صحيح w, صحيح h, صحيح عدد_chans, صحيح bpl, size_t *p_Len_باہرلا, mz_uint level, mz_bool flip, mz_uint8 *plte, صحيح plte_ناپ, mz_uint8 *trns, صحيح trns_ناپ)
{
  // Using a local copy of this array here in case MINIZ_NO_ZLIB_APIS was defined.
  ساكن ثابت mz_uint s_tdefl_png_عدد_probes[11] = { 0, 1, 6, 32,  16, 32, 128, 256,  512, 768, 1500 };
  tdefl_compressor *pComp = (tdefl_compressor *)MZ_MALLOC(حجم(tdefl_compressor)); tdefl_output_بفر باہرلا_buf; صحيح i, y, z = 0; mz_uint32 c; *p_Len_باہرلا = 0; size_t انکڑے_شروع, انکڑے_ناپ_3;
  إذا (!pComp) أرجع عدم;
  MZ_CLEAR_OBJ(باہرلا_buf); باہرلا_buf.m_expandable = MZ_TRUE;
  باہرلا_buf.m_سمرتھا = 57+MZ_MAX(64, (1+w*عدد_chans)*h);
  إذا (plte_ناپ > 0)
    باہرلا_buf.m_سمرتھا += 12+plte_ناپ;
  إذا (trns_ناپ > 0)
    باہرلا_buf.m_سمرتھا += 12+trns_ناپ;
  إذا (عدم == (باہرلا_buf.m_pBuf = (mz_uint8*)MZ_MALLOC(باہرلا_buf.m_سمرتھا))) { MZ_FREE(pComp); أرجع عدم; }
  // write header
  {
    ساكن ثابت mz_uint8 chans[] = {0x00, 0x00, 0x04, 0x02, 0x06};

    mz_uint8 pnghdr[33]={ 0x89,0x50,0x4e,0x47,0x0d,0x0a,0x1a,0x0a,
                          0x00,0x00,0x00,0x0d,0x49,0x48,0x44,0x52,
                          0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                          0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

    pnghdr[18] = (mz_uint8)(w>>8);
    pnghdr[19] = (mz_uint8)(w>>0);

    pnghdr[22] = (mz_uint8)(h>>8);
    pnghdr[23] = (mz_uint8)(h>>0);

    إذا (عدد_chans == 1 && plte_ناپ > 0)
      pnghdr[25] = 3;
    وإلا
      pnghdr[25] = (chans[عدد_chans]);

    c = (mz_uint32)mz_چکری_جانچ_32(MZ_چکری_جانچ_32_INIT,pnghdr+12,17);
    لكل (i=0; i<4; ++i, c<<=8) ((mz_uint8*)(pnghdr+29))[i] = (mz_uint8)(c>>24);
    إذا (!tdefl_output_بفر_putter(pnghdr, حجم(pnghdr), &باہرلا_buf)) { *p_Len_باہرلا = 0; MZ_FREE(pComp); MZ_FREE(باہرلا_buf.m_pBuf); أرجع عدم; }
  }
  // write PLTE chunk
  إذا (plte_ناپ > 0)
  {
    mz_uint8 hdr[8]={0x00,0x00,0x00,0x00,0x50,0x4c,0x54,0x45};

    hdr[0] = (mz_uint8)(plte_ناپ>>24);
    hdr[1] = (mz_uint8)(plte_ناپ>>16);
    hdr[2] = (mz_uint8)(plte_ناپ>> 8);
    hdr[3] = (mz_uint8)(plte_ناپ>> 0);
    إذا (!tdefl_output_بفر_putter(hdr, حجم(hdr), &باہرلا_buf)) { *p_Len_باہرلا = 0; MZ_FREE(pComp); MZ_FREE(باہرلا_buf.m_pBuf); أرجع عدم; }
    انکڑے_شروع = باہرلا_buf.m_ناپ;
    إذا (!tdefl_output_بفر_putter(plte, plte_ناپ, &باہرلا_buf)) { *p_Len_باہرلا = 0; MZ_FREE(pComp); MZ_FREE(باہرلا_buf.m_pBuf); أرجع عدم; }
    إذا (!tdefl_output_بفر_putter("\0\0\0\0", 4, &باہرلا_buf)) { *p_Len_باہرلا = 0; MZ_FREE(pComp); MZ_FREE(باہرلا_buf.m_pBuf); أرجع عدم; }
    c = (mz_uint32)mz_چکری_جانچ_32(MZ_چکری_جانچ_32_INIT,باہرلا_buf.m_pBuf+انکڑے_شروع-4, plte_ناپ+4);
    لكل (i=0; i<4; ++i, c<<=8) (باہرلا_buf.m_pBuf+باہرلا_buf.m_ناپ-4)[i] = (mz_uint8)(c >> 24);
  }
  // write tRNS chunk
  إذا (trns_ناپ > 0)
  {
    mz_uint8 hdr[8]={0x00,0x00,0x00,0x00,0x74,0x52,0x4E,0x53};

    hdr[0] = (mz_uint8)(trns_ناپ>>24);
    hdr[1] = (mz_uint8)(trns_ناپ>>16);
    hdr[2] = (mz_uint8)(trns_ناپ>> 8);
    hdr[3] = (mz_uint8)(trns_ناپ>> 0);
    إذا (!tdefl_output_بفر_putter(hdr, حجم(hdr), &باہرلا_buf)) { *p_Len_باہرلا = 0; MZ_FREE(pComp); MZ_FREE(باہرلا_buf.m_pBuf); أرجع عدم; }
    انکڑے_شروع = باہرلا_buf.m_ناپ;
    إذا (!tdefl_output_بفر_putter(trns, trns_ناپ, &باہرلا_buf)) { *p_Len_باہرلا = 0; MZ_FREE(pComp); MZ_FREE(باہرلا_buf.m_pBuf); أرجع عدم; }
    إذا (!tdefl_output_بفر_putter("\0\0\0\0", 4, &باہرلا_buf)) { *p_Len_باہرلا = 0; MZ_FREE(pComp); MZ_FREE(باہرلا_buf.m_pBuf); أرجع عدم; }
    c = (mz_uint32)mz_چکری_جانچ_32(MZ_چکری_جانچ_32_INIT,باہرلا_buf.m_pBuf+انکڑے_شروع-4, trns_ناپ+4);
    لكل (i=0; i<4; ++i, c<<=8) (باہرلا_buf.m_pBuf+باہرلا_buf.m_ناپ-4)[i] = (mz_uint8)(c >> 24);
  }
  // write IDAT chunk
  إذا (!tdefl_output_بفر_putter("\0\0\0\0\x49\x44\x41\x54", 8, &باہرلا_buf)) { *p_Len_باہرلا = 0; MZ_FREE(pComp); MZ_FREE(باہرلا_buf.m_pBuf); أرجع عدم; }
  انکڑے_شروع = باہرلا_buf.m_ناپ;
  // compress image data
  tdefl_init(pComp, tdefl_output_بفر_putter, &باہرلا_buf, s_tdefl_png_عدد_probes[MZ_MIN(10, level)] | TDEFL_WRITE_ZLIB_سرخی);
  لكل (y = 0; y < h; ++y) { tdefl_compress_بفر(pComp, &z, 1, TDEFL_NO_FLUSH); tdefl_compress_بفر(pComp, (mz_uint8*)pImage + (flip ? (h - 1 - y) : y) * bpl, w * عدد_chans, TDEFL_NO_FLUSH); }
  إذا (tdefl_compress_بفر(pComp, عدم, 0, TDEFL_انت) != TDEFL_حالت_پورا) { MZ_FREE(pComp); MZ_FREE(باہرلا_buf.m_pBuf); أرجع عدم; }
  // write IDAT size
  انکڑے_ناپ_3 = باہرلا_buf.m_ناپ-انکڑے_شروع;
  (باہرلا_buf.m_pBuf+انکڑے_شروع-8)[0] = (mz_uint8)(انکڑے_ناپ_3>>24);
  (باہرلا_buf.m_pBuf+انکڑے_شروع-8)[1] = (mz_uint8)(انکڑے_ناپ_3>>16);
  (باہرلا_buf.m_pBuf+انکڑے_شروع-8)[2] = (mz_uint8)(انکڑے_ناپ_3>> 8);
  (باہرلا_buf.m_pBuf+انکڑے_شروع-8)[3] = (mz_uint8)(انکڑے_ناپ_3>> 0);
  // write footer (IDAT CRC-32, followed by IEND chunk)
  إذا (!tdefl_output_بفر_putter("\0\0\0\0\0\0\0\0\x49\x45\x4e\x44\xae\x42\x60\x82", 16, &باہرلا_buf)) { *p_Len_باہرلا = 0; MZ_FREE(pComp); MZ_FREE(باہرلا_buf.m_pBuf); أرجع عدم; }
  c = (mz_uint32)mz_چکری_جانچ_32(MZ_چکری_جانچ_32_INIT,باہرلا_buf.m_pBuf+انکڑے_شروع-4, انکڑے_ناپ_3+4);
  لكل (i=0; i<4; ++i, c<<=8) (باہرلا_buf.m_pBuf+باہرلا_buf.m_ناپ-16)[i] = (mz_uint8)(c >> 24);
  // compute final size of file, grab compressed data buffer and return
  *p_Len_باہرلا = باہرلا_buf.m_ناپ;
  MZ_FREE(pComp);
  أرجع باہرلا_buf.m_pBuf;
}
#جے_بنا_تعریف MINIZ_SDL_NOUNUSED
MINIZ_STATIC فراغ *tdefl_write_image_منزل_png_file_وچ_حافظہ(ثابت فراغ *pImage, صحيح w, صحيح h, صحيح عدد_chans, صحيح bpl, size_t *p_Len_باہرلا)
{
  // Level 6 corresponds to TDEFL_DEFAULT_MAX_PROBES or MZ_DEFAULT_LEVEL (but we can't depend on MZ_DEFAULT_LEVEL being available in case the zlib API's where #defined out)
  أرجع tdefl_write_image_منزل_png_file_وچ_حافظہ_ex(pImage, w, h, عدد_chans, bpl, p_Len_باہرلا, 6, MZ_FALSE, عدم, 0, عدم, 0);
}
#جے_انت

#جے_تعریف_شدہ _MSC_VER
#ہدایت warning (نکالو)
#جے_انت
#جے_انت /*#ifndef MINIZ_NO_DEFLATE_APIS*/

// ------------------- .ZIP archive reading

#جے_بنا_تعریف MINIZ_NO_ARCHIVE_APIS

#جے_تعریف_شدہ MINIZ_NO_STDIO
  #تعریف_کرو MZ_FILE فراغ *
#وإلا
  #ضمن <stdio.h>
  #ضمن <sys/stat.h>

  #إذا defined(_MSC_VER) || defined(__MINGW64__)
    ساكن FILE *mz_fopen(ثابت حرف *pFilename, ثابت حرف *p_منوال)
    {
      FILE* pFile = عدم;
      fopen_s(&pFile, pFilename, p_منوال);
      أرجع pFile;
    }
    ساكن FILE *mz_freopen(ثابت حرف *p_رستہ, ثابت حرف *p_منوال, FILE *p_دھارا)
    {
      FILE* pFile = عدم;
      إذا (freopen_s(&pFile, p_رستہ, p_منوال, p_دھارا))
        أرجع عدم;
      أرجع pFile;
    }
    #جے_بنا_تعریف MINIZ_NO_ویلا
      #ضمن <sys/utime.h>
    #جے_انت
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
  #وإلاإذا defined(__MINGW32__)
    #جے_بنا_تعریف MINIZ_NO_ویلا
      #ضمن <sys/utime.h>
    #جے_انت
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
  #وإلاإذا defined(__TINYC__)
    #جے_بنا_تعریف MINIZ_NO_ویلا
      #ضمن <sys/utime.h>
    #جے_انت
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
  #وإلاإذا defined(__GNUC__) && LARGEFILE64_سروت
    #جے_بنا_تعریف MINIZ_NO_ویلا
      #ضمن <utime.h>
    #جے_انت
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
  #وإلا
    #جے_بنا_تعریف MINIZ_NO_ویلا
      #ضمن <utime.h>
    #جے_انت
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
  #جے_انت // #ifdef _MSC_VER
#جے_انت // #ifdef MINIZ_NO_STDIO

#تعریف_کرو MZ_TOLOWER(c) ((((c) >= 'A') && ((c) <= 'Z')) ? ((c) - 'A' + 'a') : (c))

// Various ZIP archive enums. To completely avoid cross platform compiler alignment and platform endian issues, miniz.c doesn't use structs for any of this stuff.
تعداد
{
  // ZIP archive identifiers and record sizes
  MZ_ZIP_سرا_دا_CENTRAL_DIR_سرخی_SIG = 0x06054b50, MZ_ZIP_CENTRAL_DIR_سرخی_SIG = 0x02014b50, MZ_ZIP_LOCAL_DIR_سرخی_SIG = 0x04034b50,
  MZ_ZIP_LOCAL_DIR_سرخی_ناپ = 30, MZ_ZIP_CENTRAL_DIR_سرخی_ناپ = 46, MZ_ZIP_سرا_دا_CENTRAL_DIR_سرخی_ناپ = 22,
  // Central directory header record offsets
  MZ_ZIP_CDH_SIG_OFS = 0, MZ_ZIP_CDH_نسخہ_MADE_BY_OFS = 4, MZ_ZIP_CDH_نسخہ_NEEDED_OFS = 6, MZ_ZIP_CDH_ثنائی_ہندسہ_FLAG_OFS = 8,
  MZ_ZIP_CDH_طریقہ_OFS = 10, MZ_ZIP_CDH_FILE_ویلا_OFS = 12, MZ_ZIP_CDH_FILE_DATE_OFS = 14, MZ_ZIP_CDH_چکری_جانچ_32_OFS = 16,
  MZ_ZIP_CDH_COMPRESSED_ناپ_OFS = 20, MZ_ZIP_CDH_DECOMPRESSED_ناپ_OFS = 24, MZ_ZIP_CDH_FILENAME_LEN_OFS = 28, MZ_ZIP_CDH_EXTRA_LEN_OFS = 30,
  MZ_ZIP_CDH_COMMENT_LEN_OFS = 32, MZ_ZIP_CDH_DISK_شروع_OFS = 34, MZ_ZIP_CDH_اندرونی_ATTR_OFS = 36, MZ_ZIP_CDH_EXTERNAL_ATTR_OFS = 38, MZ_ZIP_CDH_LOCAL_سرخی_OFS = 42,
  // Local directory header offsets
  MZ_ZIP_LDH_SIG_OFS = 0, MZ_ZIP_LDH_نسخہ_NEEDED_OFS = 4, MZ_ZIP_LDH_ثنائی_ہندسہ_FLAG_OFS = 6, MZ_ZIP_LDH_طریقہ_OFS = 8, MZ_ZIP_LDH_FILE_ویلا_OFS = 10,
  MZ_ZIP_LDH_FILE_DATE_OFS = 12, MZ_ZIP_LDH_چکری_جانچ_32_OFS = 14, MZ_ZIP_LDH_COMPRESSED_ناپ_OFS = 18, MZ_ZIP_LDH_DECOMPRESSED_ناپ_OFS = 22,
  MZ_ZIP_LDH_FILENAME_LEN_OFS = 26, MZ_ZIP_LDH_EXTRA_LEN_OFS = 28,
  // End of central directory offsets
  MZ_ZIP_ECDH_SIG_OFS = 0, MZ_ZIP_ECDH_عدد_THIS_DISK_OFS = 4, MZ_ZIP_ECDH_عدد_DISK_CDIR_OFS = 6, MZ_ZIP_ECDH_CDIR_عدد_ENTRIES_ON_DISK_OFS = 8,
  MZ_ZIP_ECDH_CDIR_کل_ENTRIES_OFS = 10, MZ_ZIP_ECDH_CDIR_ناپ_OFS = 12, MZ_ZIP_ECDH_CDIR_OFS_OFS = 16, MZ_ZIP_ECDH_COMMENT_ناپ_OFS = 20,
};

تعريفنوع بنية
{
  فراغ *m_p;
  size_t m_ناپ, m_سمرتھا;
  mz_uint m_element_ناپ;
} mz_zip_array;

بنية mz_zip_اندرونی_state_ٹیگ
{
  mz_zip_array m_central_dir;
  mz_zip_array m_central_dir_offsets;
  mz_zip_array m_sorted_central_dir_offsets;
  MZ_FILE *m_pFile;
  فراغ *m_pMem;
  size_t m_mem_ناپ;
  size_t m_mem_سمرتھا;
};

#تعریف_کرو MZ_ZIP_ARRAY_سیٹ_ELEMENT_ناپ(array_ptr, element_ناپ) (array_ptr)->m_element_ناپ = element_ناپ
#تعریف_کرو MZ_ZIP_ARRAY_ELEMENT(array_ptr, element_type, اشاریہ) ((element_type *)((array_ptr)->m_p))[اشاریہ]

ساكن MZ_FORCEINLINE فراغ mz_zip_array_clear(mz_zip_archive *pZip, mz_zip_array *pArray)
{
  pZip->m_pFree(pZip->m_pAlloc_opaque, pArray->m_p);
  memset(pArray, 0, حجم(mz_zip_array));
}

ساكن mz_bool mz_zip_array_ensure_سمرتھا(mz_zip_archive *pZip, mz_zip_array *pArray, size_t min_new_سمرتھا, mz_uint growing)
{
  فراغ *pNew_p; size_t new_سمرتھا = min_new_سمرتھا; MZ_ASSERT(pArray->m_element_ناپ); إذا (pArray->m_سمرتھا >= min_new_سمرتھا) أرجع MZ_TRUE;
  إذا (growing) { new_سمرتھا = MZ_MAX(1, pArray->m_سمرتھا); طالما (new_سمرتھا < min_new_سمرتھا) new_سمرتھا *= 2; }
  إذا (عدم == (pNew_p = pZip->m_pRealloc(pZip->m_pAlloc_opaque, pArray->m_p, pArray->m_element_ناپ, new_سمرتھا))) أرجع MZ_FALSE;
  pArray->m_p = pNew_p; pArray->m_سمرتھا = new_سمرتھا;
  أرجع MZ_TRUE;
}

ساكن MZ_FORCEINLINE mz_bool mz_zip_array_reserve(mz_zip_archive *pZip, mz_zip_array *pArray, size_t new_سمرتھا, mz_uint growing)
{
  إذا (new_سمرتھا > pArray->m_سمرتھا) { إذا (!mz_zip_array_ensure_سمرتھا(pZip, pArray, new_سمرتھا, growing)) أرجع MZ_FALSE; }
  أرجع MZ_TRUE;
}

ساكن MZ_FORCEINLINE mz_bool mz_zip_array_resize(mz_zip_archive *pZip, mz_zip_array *pArray, size_t new_ناپ, mz_uint growing)
{
  إذا (new_ناپ > pArray->m_سمرتھا) { إذا (!mz_zip_array_ensure_سمرتھا(pZip, pArray, new_ناپ, growing)) أرجع MZ_FALSE; }
  pArray->m_ناپ = new_ناپ;
  أرجع MZ_TRUE;
}

ساكن MZ_FORCEINLINE mz_bool mz_zip_array_ensure_گنجائش(mz_zip_archive *pZip, mz_zip_array *pArray, size_t n)
{
  أرجع mz_zip_array_reserve(pZip, pArray, pArray->m_ناپ + n, MZ_TRUE);
}

ساكن MZ_FORCEINLINE mz_bool mz_zip_array_ڈالو_پٹھ(mz_zip_archive *pZip, mz_zip_array *pArray, ثابت فراغ *pElements, size_t n)
{
  size_t orig_ناپ = pArray->m_ناپ; إذا (!mz_zip_array_resize(pZip, pArray, orig_ناپ + n, MZ_TRUE)) أرجع MZ_FALSE;
  حافظہ_نقل((mz_uint8*)pArray->m_p + orig_ناپ * pArray->m_element_ناپ, pElements, n * pArray->m_element_ناپ);
  أرجع MZ_TRUE;
}

#جے_بنا_تعریف MINIZ_NO_ویلا
ساكن ویلا_t mz_zip_dos_منزل_ویلا_t(صحيح dos_ویلا, صحيح dos_date)
{
  بنية tm tm;
  memset(&tm, 0, حجم(tm)); tm.tm_isdst = -1;
  tm.tm_year = ((dos_date >> 9) & 127) + 1980 - 1900; tm.tm_mon = ((dos_date >> 5) & 15) - 1; tm.tm_mday = dos_date & 31;
  tm.tm_hour = (dos_ویلا >> 11) & 31; tm.tm_min = (dos_ویلا >> 5) & 63; tm.tm_sec = (dos_ویلا << 1) & 62;
  أرجع mktime(&tm);
}

ساكن فراغ mz_zip_ویلا_منزل_dos_ویلا(ویلا_t ویلا, mz_uint16 *p_DOS_ویلا, mz_uint16 *pDOS_date)
{
#جے_تعریف_شدہ _MSC_VER
  بنية tm tm_struct;
  بنية tm *tm = &tm_struct;
  errno_t err = localtime_s(tm, &ویلا);
  إذا (err)
  {
    *pDOS_date = 0; *p_DOS_ویلا = 0;
    أرجع;
  }
#وإلا
  بنية tm *tm = localtime(&ویلا);
#جے_انت
  *p_DOS_ویلا = (mz_uint16)(((tm->tm_hour) << 11) + ((tm->tm_min) << 5) + ((tm->tm_sec) >> 1));
  *pDOS_date = (mz_uint16)(((tm->tm_year + 1900 - 1980) << 9) + ((tm->tm_mon + 1) << 5) + tm->tm_mday);
}
#جے_انت

#جے_بنا_تعریف MINIZ_NO_STDIO
ساكن mz_bool mz_zip_get_file_modified_ویلا(ثابت حرف *pFilename, mz_uint16 *p_DOS_ویلا, mz_uint16 *pDOS_date)
{
#جے_تعریف_شدہ MINIZ_NO_ویلا
  (فراغ)pFilename; *pDOS_date = *p_DOS_ویلا = 0;
#وإلا
  بنية MZ_FILE_STAT_STRUCT file_stat;
  // On Linux with x86 glibc, this call will fail on large files (>= 0x80000000 bytes) unless you compiled with _LARGEFILE64_SOURCE. Argh.
  إذا (MZ_FILE_STAT(pFilename, &file_stat) != 0)
    أرجع MZ_FALSE;
  mz_zip_ویلا_منزل_dos_ویلا(file_stat.st_mtime, p_DOS_ویلا, pDOS_date);
#جے_انت // #ifdef MINIZ_NO_TIME
  أرجع MZ_TRUE;
}

#جے_بنا_تعریف MINIZ_NO_ویلا
ساكن mz_bool mz_zip_سیٹ_file_times(ثابت حرف *pFilename, ویلا_t access_ویلا, ویلا_t modified_ویلا)
{
  بنية utimbuf t; t.actime = access_ویلا; t.modtime = modified_ویلا;
  أرجع !utime(pFilename, &t);
}
#جے_انت // #ifndef MINIZ_NO_TIME
#جے_انت // #ifndef MINIZ_NO_STDIO

ساكن mz_bool mz_zip_reader_init_اندرونی(mz_zip_archive *pZip, mz_uint32 flags)
{
  (فراغ)flags;
  إذا ((!pZip) || (pZip->m_pState) || (pZip->m_zip_منوال != MZ_ZIP_منوال_INVALID))
    أرجع MZ_FALSE;

  إذا (!pZip->m_pAlloc) pZip->m_pAlloc = def_alloc_func;
  إذا (!pZip->m_pFree) pZip->m_pFree = def_free_func;
  إذا (!pZip->m_pRealloc) pZip->m_pRealloc = def_realloc_func;

  pZip->m_zip_منوال = MZ_ZIP_منوال_READING;
  pZip->m_archive_ناپ = 0;
  pZip->m_central_directory_file_ofs = 0;
  pZip->m_کل_files = 0;

  إذا (عدم == (pZip->m_pState = (mz_zip_اندرونی_state *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, حجم(mz_zip_اندرونی_state))))
    أرجع MZ_FALSE;
  memset(pZip->m_pState, 0, حجم(mz_zip_اندرونی_state));
  MZ_ZIP_ARRAY_سیٹ_ELEMENT_ناپ(&pZip->m_pState->m_central_dir, حجم(mz_uint8));
  MZ_ZIP_ARRAY_سیٹ_ELEMENT_ناپ(&pZip->m_pState->m_central_dir_offsets, حجم(mz_uint32));
  MZ_ZIP_ARRAY_سیٹ_ELEMENT_ناپ(&pZip->m_pState->m_sorted_central_dir_offsets, حجم(mz_uint32));
  أرجع MZ_TRUE;
}

ساكن MZ_FORCEINLINE mz_bool mz_zip_reader_filename_less(ثابت mz_zip_array *pCentral_dir_array, ثابت mz_zip_array *pCentral_dir_offsets, mz_uint l_اشاریہ, mz_uint r_اشاریہ)
{
  ثابت mz_uint8 *pL = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, l_اشاریہ)), *pE;
  ثابت mz_uint8 *pR = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, r_اشاریہ));
  mz_uint l_len = MZ_READ_LE16(pL + MZ_ZIP_CDH_FILENAME_LEN_OFS), r_len = MZ_READ_LE16(pR + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  mz_uint8 l = 0, r = 0;
  pL += MZ_ZIP_CENTRAL_DIR_سرخی_ناپ; pR += MZ_ZIP_CENTRAL_DIR_سرخی_ناپ;
  pE = pL + MZ_MIN(l_len, r_len);
  طالما (pL < pE)
  {
    إذا ((l = MZ_TOLOWER(*pL)) != (r = MZ_TOLOWER(*pR)))
      اكسر;
    pL++; pR++;
  }
  أرجع (pL == pE) ? (l_len < r_len) : (l < r);
}

#تعریف_کرو MZ_وٹاندرا_UINT32(a, b) افعل { mz_uint32 t = a; a = b; b = t; } MZ_MACRO_سرا

// Heap sort of lowercased filenames, used to help accelerate plain central directory searches by mz_zip_reader_locate_file(). (Could also use qsort(), but it could allocate memory.)
ساكن فراغ mz_zip_reader_ترتیب_دیو_central_dir_offsets_by_filename(mz_zip_archive *pZip)
{
  mz_zip_اندرونی_state *pState = pZip->m_pState;
  ثابت mz_zip_array *pCentral_dir_offsets = &pState->m_central_dir_offsets;
  ثابت mz_zip_array *pCentral_dir = &pState->m_central_dir;
  mz_uint32 *pIndices = &MZ_ZIP_ARRAY_ELEMENT(&pState->m_sorted_central_dir_offsets, mz_uint32, 0);
  ثابت صحيح ناپ = pZip->m_کل_files;
  صحيح شروع = (ناپ - 2) >> 1, سرا;
  طالما (شروع >= 0)
  {
    صحيح بچہ, جڑ = شروع;
    لكل ( ; ; )
    {
      إذا ((بچہ = (جڑ << 1) + 1) >= ناپ)
        اكسر;
      بچہ += (((بچہ + 1) < ناپ) && (mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[بچہ], pIndices[بچہ + 1])));
      إذا (!mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[جڑ], pIndices[بچہ]))
        اكسر;
      MZ_وٹاندرا_UINT32(pIndices[جڑ], pIndices[بچہ]); جڑ = بچہ;
    }
    شروع--;
  }

  سرا = ناپ - 1;
  طالما (سرا > 0)
  {
    صحيح بچہ, جڑ = 0;
    MZ_وٹاندرا_UINT32(pIndices[سرا], pIndices[0]);
    لكل ( ; ; )
    {
      إذا ((بچہ = (جڑ << 1) + 1) >= سرا)
        اكسر;
      بچہ += (((بچہ + 1) < سرا) && mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[بچہ], pIndices[بچہ + 1]));
      إذا (!mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[جڑ], pIndices[بچہ]))
        اكسر;
      MZ_وٹاندرا_UINT32(pIndices[جڑ], pIndices[بچہ]); جڑ = بچہ;
    }
    سرا--;
  }
}

ساكن mz_bool mz_zip_reader_read_central_dir(mz_zip_archive *pZip, mz_uint32 flags)
{
  mz_uint cdir_ناپ, عدد_this_disk, cdir_disk_اشاریہ;
  mz_uint64 cdir_ofs;
  mz_int64 cur_file_ofs;
  ثابت mz_uint8 *p;
  mz_uint32 buf_u32[4096 / حجم(mz_uint32)]; mz_uint8 *pBuf = (mz_uint8 *)buf_u32;
  mz_bool ترتیب_دیو_central_dir = ((flags & MZ_ZIP_FLAG_DO_NOT_ترتیب_دیو_CENTRAL_DIRECTORY) == 0);
  // Basic sanity checks - reject files which are too small, and check the first 4 bytes of the file to make sure a local header is there.
  إذا (pZip->m_archive_ناپ < MZ_ZIP_سرا_دا_CENTRAL_DIR_سرخی_ناپ)
    أرجع MZ_FALSE;
  // Find the end of central directory record by scanning the file from the end towards the beginning.
  cur_file_ofs = MZ_MAX((mz_int64)pZip->m_archive_ناپ - (mz_int64)حجم(buf_u32), 0);
  لكل ( ; ; )
  {
    صحيح i, n = (صحيح)MZ_MIN(حجم(buf_u32), pZip->m_archive_ناپ - cur_file_ofs);
    إذا (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, n) != (mz_uint)n)
      أرجع MZ_FALSE;
    لكل (i = n - 4; i >= 0; --i)
      إذا (MZ_READ_LE32(pBuf + i) == MZ_ZIP_سرا_دا_CENTRAL_DIR_سرخی_SIG)
        اكسر;
    إذا (i >= 0)
    {
      cur_file_ofs += i;
      اكسر;
    }
    إذا ((!cur_file_ofs) || ((pZip->m_archive_ناپ - cur_file_ofs) >= (0xFFFF + MZ_ZIP_سرا_دا_CENTRAL_DIR_سرخی_ناپ)))
      أرجع MZ_FALSE;
    cur_file_ofs = MZ_MAX(cur_file_ofs - (حجم(buf_u32) - 3), 0);
  }
  // Read and verify the end of central directory record.
  إذا (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, MZ_ZIP_سرا_دا_CENTRAL_DIR_سرخی_ناپ) != MZ_ZIP_سرا_دا_CENTRAL_DIR_سرخی_ناپ)
    أرجع MZ_FALSE;
  إذا ((MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_SIG_OFS) != MZ_ZIP_سرا_دا_CENTRAL_DIR_سرخی_SIG) ||
      ((pZip->m_کل_files = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_CDIR_کل_ENTRIES_OFS)) != MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_CDIR_عدد_ENTRIES_ON_DISK_OFS)))
    أرجع MZ_FALSE;

  عدد_this_disk = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_عدد_THIS_DISK_OFS);
  cdir_disk_اشاریہ = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_عدد_DISK_CDIR_OFS);
  إذا (((عدد_this_disk | cdir_disk_اشاریہ) != 0) && ((عدد_this_disk != 1) || (cdir_disk_اشاریہ != 1)))
    أرجع MZ_FALSE;

  إذا ((cdir_ناپ = MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_CDIR_ناپ_OFS)) < pZip->m_کل_files * MZ_ZIP_CENTRAL_DIR_سرخی_ناپ)
    أرجع MZ_FALSE;

  cdir_ofs = MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_CDIR_OFS_OFS);
  إذا ((cdir_ofs + (mz_uint64)cdir_ناپ) > pZip->m_archive_ناپ)
    أرجع MZ_FALSE;

  pZip->m_central_directory_file_ofs = cdir_ofs;

  إذا (pZip->m_کل_files)
  {
     mz_uint i, n;

    // Read the entire central directory into a heap block, and allocate another heap block to hold the unsorted central dir file record offsets, and another to hold the sorted indices.
    إذا ((!mz_zip_array_resize(pZip, &pZip->m_pState->m_central_dir, cdir_ناپ, MZ_FALSE)) ||
        (!mz_zip_array_resize(pZip, &pZip->m_pState->m_central_dir_offsets, pZip->m_کل_files, MZ_FALSE)))
      أرجع MZ_FALSE;

    إذا (ترتیب_دیو_central_dir)
    {
      إذا (!mz_zip_array_resize(pZip, &pZip->m_pState->m_sorted_central_dir_offsets, pZip->m_کل_files, MZ_FALSE))
        أرجع MZ_FALSE;
    }

    إذا (pZip->m_pRead(pZip->m_pIO_opaque, cdir_ofs, pZip->m_pState->m_central_dir.m_p, cdir_ناپ) != cdir_ناپ)
      أرجع MZ_FALSE;

    // Now create an index into the central directory file records, do some basic sanity checking on each record, and check for zip64 entries (which are not yet supported).
    p = (ثابت mz_uint8 *)pZip->m_pState->m_central_dir.m_p;
    لكل (n = cdir_ناپ, i = 0; i < pZip->m_کل_files; ++i)
    {
      mz_uint کل_سرخی_ناپ, comp_ناپ, decomp_ناپ, disk_اشاریہ;
      إذا ((n < MZ_ZIP_CENTRAL_DIR_سرخی_ناپ) || (MZ_READ_LE32(p) != MZ_ZIP_CENTRAL_DIR_سرخی_SIG))
        أرجع MZ_FALSE;
      MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, i) = (mz_uint32)(p - (ثابت mz_uint8 *)pZip->m_pState->m_central_dir.m_p);
      إذا (ترتیب_دیو_central_dir)
        MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_sorted_central_dir_offsets, mz_uint32, i) = i;
      comp_ناپ = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_ناپ_OFS);
      decomp_ناپ = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_ناپ_OFS);
      إذا (((!MZ_READ_LE32(p + MZ_ZIP_CDH_طریقہ_OFS)) && (decomp_ناپ != comp_ناپ)) || (decomp_ناپ && !comp_ناپ) || (decomp_ناپ == 0xFFFFFFFF) || (comp_ناپ == 0xFFFFFFFF))
        أرجع MZ_FALSE;
      disk_اشاریہ = MZ_READ_LE16(p + MZ_ZIP_CDH_DISK_شروع_OFS);
      إذا ((disk_اشاریہ != عدد_this_disk) && (disk_اشاریہ != 1))
        أرجع MZ_FALSE;
      إذا (((mz_uint64)MZ_READ_LE32(p + MZ_ZIP_CDH_LOCAL_سرخی_OFS) + MZ_ZIP_LOCAL_DIR_سرخی_ناپ + comp_ناپ) > pZip->m_archive_ناپ)
        أرجع MZ_FALSE;
      إذا ((کل_سرخی_ناپ = MZ_ZIP_CENTRAL_DIR_سرخی_ناپ + MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_EXTRA_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_COMMENT_LEN_OFS)) > n)
        أرجع MZ_FALSE;
      n -= کل_سرخی_ناپ; p += کل_سرخی_ناپ;
    }
  }

  إذا (ترتیب_دیو_central_dir)
    mz_zip_reader_ترتیب_دیو_central_dir_offsets_by_filename(pZip);

  أرجع MZ_TRUE;
}

mz_bool mz_zip_reader_init(mz_zip_archive *pZip, mz_uint64 ناپ, mz_uint32 flags)
{
  إذا ((!pZip) || (!pZip->m_pRead))
    أرجع MZ_FALSE;
  إذا (!mz_zip_reader_init_اندرونی(pZip, flags))
    أرجع MZ_FALSE;
  pZip->m_archive_ناپ = ناپ;
  إذا (!mz_zip_reader_read_central_dir(pZip, flags))
  {
    mz_zip_reader_سرا(pZip);
    أرجع MZ_FALSE;
  }
  أرجع MZ_TRUE;
}

ساكن size_t mz_zip_mem_read_func(فراغ *pOpaque, mz_uint64 file_ofs, فراغ *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  size_t s = (file_ofs >= pZip->m_archive_ناپ) ? 0 : (size_t)MZ_MIN(pZip->m_archive_ناپ - file_ofs, n);
  حافظہ_نقل(pBuf, (ثابت mz_uint8 *)pZip->m_pState->m_pMem + file_ofs, s);
  أرجع s;
}

mz_bool mz_zip_reader_init_mem(mz_zip_archive *pZip, ثابت فراغ *pMem, size_t ناپ, mz_uint32 flags)
{
  إذا (!mz_zip_reader_init_اندرونی(pZip, flags))
    أرجع MZ_FALSE;
  pZip->m_archive_ناپ = ناپ;
  pZip->m_pRead = mz_zip_mem_read_func;
  pZip->m_pIO_opaque = pZip;
#جے_تعریف_شدہ __cplusplus
  pZip->m_pState->m_pMem = const_cast<فراغ *>(pMem);
#وإلا
  pZip->m_pState->m_pMem = (فراغ *)pMem;
#جے_انت
  pZip->m_pState->m_mem_ناپ = ناپ;
  إذا (!mz_zip_reader_read_central_dir(pZip, flags))
  {
    mz_zip_reader_سرا(pZip);
    أرجع MZ_FALSE;
  }
  أرجع MZ_TRUE;
}

#جے_بنا_تعریف MINIZ_NO_STDIO
ساكن size_t mz_zip_file_read_func(فراغ *pOpaque, mz_uint64 file_ofs, فراغ *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_int64 cur_ofs = MZ_FTELL64(pZip->m_pState->m_pFile);
  إذا (((mz_int64)file_ofs < 0) || (((cur_ofs != (mz_int64)file_ofs)) && (MZ_FSEEK64(pZip->m_pState->m_pFile, (mz_int64)file_ofs, SEEK_SET))))
    أرجع 0;
  أرجع MZ_FREAD(pBuf, 1, n, pZip->m_pState->m_pFile);
}

mz_bool mz_zip_reader_init_file(mz_zip_archive *pZip, ثابت حرف *pFilename, mz_uint32 flags)
{
  mz_uint64 file_ناپ;
  MZ_FILE *pFile = MZ_FOPEN(pFilename, "rb");
  إذا (!pFile)
    أرجع MZ_FALSE;
  إذا (MZ_FSEEK64(pFile, 0, SEEK_END))
  {
    MZ_FCLOSE(pFile);
    أرجع MZ_FALSE;
  }
  file_ناپ = MZ_FTELL64(pFile);
  إذا (!mz_zip_reader_init_اندرونی(pZip, flags))
  {
    MZ_FCLOSE(pFile);
    أرجع MZ_FALSE;
  }
  pZip->m_pRead = mz_zip_file_read_func;
  pZip->m_pIO_opaque = pZip;
  pZip->m_pState->m_pFile = pFile;
  pZip->m_archive_ناپ = file_ناپ;
  إذا (!mz_zip_reader_read_central_dir(pZip, flags))
  {
    mz_zip_reader_سرا(pZip);
    أرجع MZ_FALSE;
  }
  أرجع MZ_TRUE;
}
#جے_انت // #ifndef MINIZ_NO_STDIO

mz_uint mz_zip_reader_get_عدد_files(mz_zip_archive *pZip)
{
  أرجع pZip ? pZip->m_کل_files : 0;
}

ساكن MZ_FORCEINLINE ثابت mz_uint8 *mz_zip_reader_get_cdh(mz_zip_archive *pZip, mz_uint file_اشاریہ)
{
  إذا ((!pZip) || (!pZip->m_pState) || (file_اشاریہ >= pZip->m_کل_files) || (pZip->m_zip_منوال != MZ_ZIP_منوال_READING))
    أرجع عدم;
  أرجع &MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_اشاریہ));
}

mz_bool mz_zip_reader_is_file_encrypted(mz_zip_archive *pZip, mz_uint file_اشاریہ)
{
  mz_uint m_ثنائی_ہندسہ_flag;
  ثابت mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_اشاریہ);
  إذا (!p)
    أرجع MZ_FALSE;
  m_ثنائی_ہندسہ_flag = MZ_READ_LE16(p + MZ_ZIP_CDH_ثنائی_ہندسہ_FLAG_OFS);
  أرجع (m_ثنائی_ہندسہ_flag & 1);
}

mz_bool mz_zip_reader_is_file_a_directory(mz_zip_archive *pZip, mz_uint file_اشاریہ)
{
  mz_uint filename_len, external_attr;
  ثابت mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_اشاریہ);
  إذا (!p)
    أرجع MZ_FALSE;

  // First see if the filename ends with a '/' character.
  filename_len = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  إذا (filename_len)
  {
    إذا (*(p + MZ_ZIP_CENTRAL_DIR_سرخی_ناپ + filename_len - 1) == '/')
      أرجع MZ_TRUE;
  }

  // Bugfix: This code was also checking if the internal attribute was non-zero, which wasn't correct.
  // Most/all zip writers (hopefully) set DOS file/directory attributes in the low 16-bits, so check for the DOS directory flag and ignore the source OS ID in the created by field.
  // FIXME: Remove this check? Is it necessary - we already check the filename.
  external_attr = MZ_READ_LE32(p + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS);
  إذا ((external_attr & 0x10) != 0)
    أرجع MZ_TRUE;

  أرجع MZ_FALSE;
}

mz_bool mz_zip_reader_file_stat(mz_zip_archive *pZip, mz_uint file_اشاریہ, mz_zip_archive_file_stat *pStat)
{
  mz_uint n;
  ثابت mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_اشاریہ);
  إذا ((!p) || (!pStat))
    أرجع MZ_FALSE;

  // Unpack the central directory record.
  pStat->m_file_اشاریہ = file_اشاریہ;
  pStat->m_central_dir_ofs = MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_اشاریہ);
  pStat->m_نسخہ_made_by = MZ_READ_LE16(p + MZ_ZIP_CDH_نسخہ_MADE_BY_OFS);
  pStat->m_نسخہ_needed = MZ_READ_LE16(p + MZ_ZIP_CDH_نسخہ_NEEDED_OFS);
  pStat->m_ثنائی_ہندسہ_flag = MZ_READ_LE16(p + MZ_ZIP_CDH_ثنائی_ہندسہ_FLAG_OFS);
  pStat->m_طریقہ = MZ_READ_LE16(p + MZ_ZIP_CDH_طریقہ_OFS);
#جے_بنا_تعریف MINIZ_NO_ویلا
  pStat->m_ویلا = mz_zip_dos_منزل_ویلا_t(MZ_READ_LE16(p + MZ_ZIP_CDH_FILE_ویلا_OFS), MZ_READ_LE16(p + MZ_ZIP_CDH_FILE_DATE_OFS));
#جے_انت
  pStat->m_چکری_جانچ_32 = MZ_READ_LE32(p + MZ_ZIP_CDH_چکری_جانچ_32_OFS);
  pStat->m_comp_ناپ = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_ناپ_OFS);
  pStat->m_uncomp_ناپ = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_ناپ_OFS);
  pStat->m_اندرونی_attr = MZ_READ_LE16(p + MZ_ZIP_CDH_اندرونی_ATTR_OFS);
  pStat->m_external_attr = MZ_READ_LE32(p + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS);
  pStat->m_local_سرخی_ofs = MZ_READ_LE32(p + MZ_ZIP_CDH_LOCAL_سرخی_OFS);

  // Copy as much of the filename and comment as possible.
  n = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS); n = MZ_MIN(n, MZ_ZIP_MAX_ARCHIVE_FILENAME_ناپ - 1);
  حافظہ_نقل(pStat->m_filename, p + MZ_ZIP_CENTRAL_DIR_سرخی_ناپ, n); pStat->m_filename[n] = '\0';

  n = MZ_READ_LE16(p + MZ_ZIP_CDH_COMMENT_LEN_OFS); n = MZ_MIN(n, MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_ناپ - 1);
  pStat->m_comment_ناپ = n;
  حافظہ_نقل(pStat->m_comment, p + MZ_ZIP_CENTRAL_DIR_سرخی_ناپ + MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_EXTRA_LEN_OFS), n); pStat->m_comment[n] = '\0';

  أرجع MZ_TRUE;
}

mz_uint mz_zip_reader_get_filename(mz_zip_archive *pZip, mz_uint file_اشاریہ, حرف *pFilename, mz_uint filename_buf_ناپ)
{
  mz_uint n;
  ثابت mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_اشاریہ);
  إذا (!p) { إذا (filename_buf_ناپ) pFilename[0] = '\0'; أرجع 0; }
  n = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  إذا (filename_buf_ناپ)
  {
    n = MZ_MIN(n, filename_buf_ناپ - 1);
    حافظہ_نقل(pFilename, p + MZ_ZIP_CENTRAL_DIR_سرخی_ناپ, n);
    pFilename[n] = '\0';
  }
  أرجع n + 1;
}

ساكن MZ_FORCEINLINE mz_bool mz_zip_reader_string_equal(ثابت حرف *pA, ثابت حرف *pB, mz_uint len, mz_uint flags)
{
  mz_uint i;
  إذا (flags & MZ_ZIP_FLAG_CASE_SENSITIVE)
    أرجع 0 == memcmp(pA, pB, len);
  لكل (i = 0; i < len; ++i)
    إذا (MZ_TOLOWER(pA[i]) != MZ_TOLOWER(pB[i]))
      أرجع MZ_FALSE;
  أرجع MZ_TRUE;
}

ساكن MZ_FORCEINLINE صحيح mz_zip_reader_filename_compare(ثابت mz_zip_array *pCentral_dir_array, ثابت mz_zip_array *pCentral_dir_offsets, mz_uint l_اشاریہ, ثابت حرف *pR, mz_uint r_len)
{
  ثابت mz_uint8 *pL = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, l_اشاریہ)), *pE;
  mz_uint l_len = MZ_READ_LE16(pL + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  mz_uint8 l = 0, r = 0;
  pL += MZ_ZIP_CENTRAL_DIR_سرخی_ناپ;
  pE = pL + MZ_MIN(l_len, r_len);
  طالما (pL < pE)
  {
    إذا ((l = MZ_TOLOWER(*pL)) != (r = MZ_TOLOWER(*pR)))
      اكسر;
    pL++; pR++;
  }
  أرجع (pL == pE) ? (صحيح)(l_len - r_len) : (l - r);
}

ساكن صحيح mz_zip_reader_locate_file_ثنائی_تلاش(mz_zip_archive *pZip, ثابت حرف *pFilename)
{
  mz_zip_اندرونی_state *pState = pZip->m_pState;
  ثابت mz_zip_array *pCentral_dir_offsets = &pState->m_central_dir_offsets;
  ثابت mz_zip_array *pCentral_dir = &pState->m_central_dir;
  mz_uint32 *pIndices = &MZ_ZIP_ARRAY_ELEMENT(&pState->m_sorted_central_dir_offsets, mz_uint32, 0);
  ثابت صحيح ناپ = pZip->m_کل_files;
  ثابت mz_uint filename_len = (mz_uint)لڑی_لمبائی(pFilename);
  صحيح l = 0, h = ناپ - 1;
  طالما (l <= h)
  {
    صحيح m = (l + h) >> 1, file_اشاریہ = pIndices[m], comp = mz_zip_reader_filename_compare(pCentral_dir, pCentral_dir_offsets, file_اشاریہ, pFilename, filename_len);
    إذا (!comp)
      أرجع file_اشاریہ;
    وإلا إذا (comp < 0)
      l = m + 1;
    وإلا
      h = m - 1;
  }
  أرجع -1;
}

صحيح mz_zip_reader_locate_file(mz_zip_archive *pZip, ثابت حرف *pName, ثابت حرف *pComment, mz_uint flags)
{
  mz_uint file_اشاریہ; size_t name_len, comment_len;
  إذا ((!pZip) || (!pZip->m_pState) || (!pName) || (pZip->m_zip_منوال != MZ_ZIP_منوال_READING))
    أرجع -1;
  إذا (((flags & (MZ_ZIP_FLAG_IGNORE_رستہ | MZ_ZIP_FLAG_CASE_SENSITIVE)) == 0) && (!pComment) && (pZip->m_pState->m_sorted_central_dir_offsets.m_ناپ))
    أرجع mz_zip_reader_locate_file_ثنائی_تلاش(pZip, pName);
  name_len = لڑی_لمبائی(pName); إذا (name_len > 0xFFFF) أرجع -1;
  comment_len = pComment ? لڑی_لمبائی(pComment) : 0; إذا (comment_len > 0xFFFF) أرجع -1;
  لكل (file_اشاریہ = 0; file_اشاریہ < pZip->m_کل_files; file_اشاریہ++)
  {
    ثابت mz_uint8 *p_سرخی = &MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_اشاریہ));
    mz_uint filename_len = MZ_READ_LE16(p_سرخی + MZ_ZIP_CDH_FILENAME_LEN_OFS);
    ثابت حرف *pFilename = (ثابت حرف *)p_سرخی + MZ_ZIP_CENTRAL_DIR_سرخی_ناپ;
    إذا (filename_len < name_len)
      استمر;
    إذا (comment_len)
    {
      mz_uint file_extra_len = MZ_READ_LE16(p_سرخی + MZ_ZIP_CDH_EXTRA_LEN_OFS), file_comment_len = MZ_READ_LE16(p_سرخی + MZ_ZIP_CDH_COMMENT_LEN_OFS);
      ثابت حرف *pFile_comment = pFilename + filename_len + file_extra_len;
      إذا ((file_comment_len != comment_len) || (!mz_zip_reader_string_equal(pComment, pFile_comment, file_comment_len, flags)))
        استمر;
    }
    إذا ((flags & MZ_ZIP_FLAG_IGNORE_رستہ) && (filename_len))
    {
      صحيح ofs = filename_len - 1;
      افعل
      {
        إذا ((pFilename[ofs] == '/') || (pFilename[ofs] == '\\') || (pFilename[ofs] == ':'))
          اكسر;
      } طالما (--ofs >= 0);
      ofs++;
      pFilename += ofs; filename_len -= ofs;
    }
    إذا ((filename_len == name_len) && (mz_zip_reader_string_equal(pName, pFilename, filename_len, flags)))
      أرجع file_اشاریہ;
  }
  أرجع -1;
}

mz_bool mz_zip_reader_کڈھو_منزل_mem_no_alloc(mz_zip_archive *pZip, mz_uint file_اشاریہ, فراغ *pBuf, size_t buf_ناپ_2, mz_uint flags, فراغ *pUser_read_buf, size_t user_read_buf_ناپ)
{
  صحيح حالت = TINFL_حالت_پورا;
  mz_uint64 needed_ناپ, cur_file_ofs, comp_بچیا, باہرلا_buf_ofs = 0, read_buf_ناپ, read_buf_ofs = 0, read_buf_avail;
  mz_zip_archive_file_stat file_stat;
  فراغ *pRead_buf;
  mz_uint32 local_سرخی_u32[(MZ_ZIP_LOCAL_DIR_سرخی_ناپ + حجم(mz_uint32) - 1) / حجم(mz_uint32)]; mz_uint8 *p_Local_سرخی = (mz_uint8 *)local_سرخی_u32;
  tinfl_decompressor inflator;

  إذا ((buf_ناپ_2) && (!pBuf))
    أرجع MZ_FALSE;

  إذا (!mz_zip_reader_file_stat(pZip, file_اشاریہ, &file_stat))
    أرجع MZ_FALSE;

  // Empty file, or a directory (but not always a directory - I've seen odd zips with directories that have compressed data which inflates to 0 bytes)
  إذا (!file_stat.m_comp_ناپ)
    أرجع MZ_TRUE;

  // Entry is a subdirectory (I've seen old zips with dir entries which have compressed deflate data which inflates to 0 bytes, but these entries claim to uncompress to 512 bytes in the headers).
  // I'm torn how to handle this case - should it fail instead?
  إذا (mz_zip_reader_is_file_a_directory(pZip, file_اشاریہ))
    أرجع MZ_TRUE;

  // Encryption and patch files are not supported.
  إذا (file_stat.m_ثنائی_ہندسہ_flag & (1 | 32))
    أرجع MZ_FALSE;

  // This function only supports stored and deflate.
  إذا ((!(flags & MZ_ZIP_FLAG_COMPRESSED_انکڑے)) && (file_stat.m_طریقہ != 0) && (file_stat.m_طریقہ != MZ_DEFLATED))
    أرجع MZ_FALSE;

  // Ensure supplied output buffer is large enough.
  needed_ناپ = (flags & MZ_ZIP_FLAG_COMPRESSED_انکڑے) ? file_stat.m_comp_ناپ : file_stat.m_uncomp_ناپ;
  إذا (buf_ناپ_2 < needed_ناپ)
    أرجع MZ_FALSE;

  // Read and parse the local directory entry.
  cur_file_ofs = file_stat.m_local_سرخی_ofs;
  إذا (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, p_Local_سرخی, MZ_ZIP_LOCAL_DIR_سرخی_ناپ) != MZ_ZIP_LOCAL_DIR_سرخی_ناپ)
    أرجع MZ_FALSE;
  إذا (MZ_READ_LE32(p_Local_سرخی) != MZ_ZIP_LOCAL_DIR_سرخی_SIG)
    أرجع MZ_FALSE;

  cur_file_ofs += MZ_ZIP_LOCAL_DIR_سرخی_ناپ + MZ_READ_LE16(p_Local_سرخی + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p_Local_سرخی + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  إذا ((cur_file_ofs + file_stat.m_comp_ناپ) > pZip->m_archive_ناپ)
    أرجع MZ_FALSE;

  إذا ((flags & MZ_ZIP_FLAG_COMPRESSED_انکڑے) || (!file_stat.m_طریقہ))
  {
    // The file is stored or the caller has requested the compressed data.
    إذا (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, (size_t)needed_ناپ) != needed_ناپ)
      أرجع MZ_FALSE;
    أرجع ((flags & MZ_ZIP_FLAG_COMPRESSED_انکڑے) != 0) || (mz_چکری_جانچ_32(MZ_چکری_جانچ_32_INIT, (ثابت mz_uint8 *)pBuf, (size_t)file_stat.m_uncomp_ناپ) == file_stat.m_چکری_جانچ_32);
  }

  // Decompress the file either directly from memory or from a file input buffer.
  tinfl_init(&inflator);

  إذا (pZip->m_pState->m_pMem)
  {
    // Read directly from the archive in memory.
    pRead_buf = (mz_uint8 *)pZip->m_pState->m_pMem + cur_file_ofs;
    read_buf_ناپ = read_buf_avail = file_stat.m_comp_ناپ;
    comp_بچیا = 0;
  }
  وإلا إذا (pUser_read_buf)
  {
    // Use a user provided read buffer.
    إذا (!user_read_buf_ناپ)
      أرجع MZ_FALSE;
    pRead_buf = (mz_uint8 *)pUser_read_buf;
    read_buf_ناپ = user_read_buf_ناپ;
    read_buf_avail = 0;
    comp_بچیا = file_stat.m_comp_ناپ;
  }
  وإلا
  {
    // Temporarily allocate a read buffer.
    read_buf_ناپ = MZ_MIN(file_stat.m_comp_ناپ, MZ_ZIP_MAX_IO_BUF_ناپ);
#جے_تعریف_شدہ _MSC_VER
    إذا (((0, حجم(size_t) == حجم(mz_uint32))) && (read_buf_ناپ > 0x7FFFFFFF))
#وإلا
    إذا (((حجم(size_t) == حجم(mz_uint32))) && (read_buf_ناپ > 0x7FFFFFFF))
#جے_انت
      أرجع MZ_FALSE;
    إذا (عدم == (pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)read_buf_ناپ)))
      أرجع MZ_FALSE;
    read_buf_avail = 0;
    comp_بچیا = file_stat.m_comp_ناپ;
  }

  افعل
  {
    size_t وچ_buf_ناپ, باہرلا_buf_ناپ = (size_t)(file_stat.m_uncomp_ناپ - باہرلا_buf_ofs);
    إذا ((!read_buf_avail) && (!pZip->m_pState->m_pMem))
    {
      read_buf_avail = MZ_MIN(read_buf_ناپ, comp_بچیا);
      إذا (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
      {
        حالت = TINFL_حالت_FAILED;
        اكسر;
      }
      cur_file_ofs += read_buf_avail;
      comp_بچیا -= read_buf_avail;
      read_buf_ofs = 0;
    }
    وچ_buf_ناپ = (size_t)read_buf_avail;
    حالت = tinfl_decompress(&inflator, (mz_uint8 *)pRead_buf + read_buf_ofs, &وچ_buf_ناپ, (mz_uint8 *)pBuf, (mz_uint8 *)pBuf + باہرلا_buf_ofs, &باہرلا_buf_ناپ, TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF | (comp_بچیا ? TINFL_FLAG_HAS_ہور_داخلہ : 0));
    read_buf_avail -= وچ_buf_ناپ;
    read_buf_ofs += وچ_buf_ناپ;
    باہرلا_buf_ofs += باہرلا_buf_ناپ;
  } طالما (حالت == TINFL_حالت_NEEDS_ہور_داخلہ);

  إذا (حالت == TINFL_حالت_پورا)
  {
    // Make sure the entire file was decompressed, and check its CRC.
    إذا ((باہرلا_buf_ofs != file_stat.m_uncomp_ناپ) || (mz_چکری_جانچ_32(MZ_چکری_جانچ_32_INIT, (ثابت mz_uint8 *)pBuf, (size_t)file_stat.m_uncomp_ناپ) != file_stat.m_چکری_جانچ_32))
      حالت = TINFL_حالت_FAILED;
  }

  إذا ((!pZip->m_pState->m_pMem) && (!pUser_read_buf))
    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);

  أرجع حالت == TINFL_حالت_پورا;
}

mz_bool mz_zip_reader_کڈھو_file_منزل_mem_no_alloc(mz_zip_archive *pZip, ثابت حرف *pFilename, فراغ *pBuf, size_t buf_ناپ_2, mz_uint flags, فراغ *pUser_read_buf, size_t user_read_buf_ناپ)
{
  صحيح file_اشاریہ = mz_zip_reader_locate_file(pZip, pFilename, عدم, flags);
  إذا (file_اشاریہ < 0)
    أرجع MZ_FALSE;
  أرجع mz_zip_reader_کڈھو_منزل_mem_no_alloc(pZip, file_اشاریہ, pBuf, buf_ناپ_2, flags, pUser_read_buf, user_read_buf_ناپ);
}

mz_bool mz_zip_reader_کڈھو_منزل_mem(mz_zip_archive *pZip, mz_uint file_اشاریہ, فراغ *pBuf, size_t buf_ناپ_2, mz_uint flags)
{
  أرجع mz_zip_reader_کڈھو_منزل_mem_no_alloc(pZip, file_اشاریہ, pBuf, buf_ناپ_2, flags, عدم, 0);
}

mz_bool mz_zip_reader_کڈھو_file_منزل_mem(mz_zip_archive *pZip, ثابت حرف *pFilename, فراغ *pBuf, size_t buf_ناپ_2, mz_uint flags)
{
  أرجع mz_zip_reader_کڈھو_file_منزل_mem_no_alloc(pZip, pFilename, pBuf, buf_ناپ_2, flags, عدم, 0);
}

فراغ *mz_zip_reader_کڈھو_منزل_ڈھیر(mz_zip_archive *pZip, mz_uint file_اشاریہ, size_t *p_ناپ, mz_uint flags)
{
  mz_uint64 comp_ناپ, uncomp_ناپ, alloc_ناپ_2;
  ثابت mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_اشاریہ);
  فراغ *pBuf;

  إذا (p_ناپ)
    *p_ناپ = 0;
  إذا (!p)
    أرجع عدم;

  comp_ناپ = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_ناپ_OFS);
  uncomp_ناپ = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_ناپ_OFS);

  alloc_ناپ_2 = (flags & MZ_ZIP_FLAG_COMPRESSED_انکڑے) ? comp_ناپ : uncomp_ناپ;
#جے_تعریف_شدہ _MSC_VER
  إذا (((0, حجم(size_t) == حجم(mz_uint32))) && (alloc_ناپ_2 > 0x7FFFFFFF))
#وإلا
  إذا (((حجم(size_t) == حجم(mz_uint32))) && (alloc_ناپ_2 > 0x7FFFFFFF))
#جے_انت
    أرجع عدم;
  إذا (عدم == (pBuf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)alloc_ناپ_2)))
    أرجع عدم;

  إذا (!mz_zip_reader_کڈھو_منزل_mem(pZip, file_اشاریہ, pBuf, (size_t)alloc_ناپ_2, flags))
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
    أرجع عدم;
  }

  إذا (p_ناپ) *p_ناپ = (size_t)alloc_ناپ_2;
  أرجع pBuf;
}

فراغ *mz_zip_reader_کڈھو_file_منزل_ڈھیر(mz_zip_archive *pZip, ثابت حرف *pFilename, size_t *p_ناپ, mz_uint flags)
{
  صحيح file_اشاریہ = mz_zip_reader_locate_file(pZip, pFilename, عدم, flags);
  إذا (file_اشاریہ < 0)
  {
    إذا (p_ناپ) *p_ناپ = 0;
    أرجع MZ_FALSE;
  }
  أرجع mz_zip_reader_کڈھو_منزل_ڈھیر(pZip, file_اشاریہ, p_ناپ, flags);
}

mz_bool mz_zip_reader_کڈھو_منزل_callback(mz_zip_archive *pZip, mz_uint file_اشاریہ, mz_file_write_func pCallback, فراغ *pOpaque, mz_uint flags)
{
  صحيح حالت = TINFL_حالت_پورا; mz_uint file_چکری_جانچ_32 = MZ_چکری_جانچ_32_INIT;
  mz_uint64 read_buf_ناپ, read_buf_ofs = 0, read_buf_avail, comp_بچیا, باہرلا_buf_ofs = 0, cur_file_ofs;
  mz_zip_archive_file_stat file_stat;
  فراغ *pRead_buf = عدم; فراغ *pWrite_buf = عدم;
  mz_uint32 local_سرخی_u32[(MZ_ZIP_LOCAL_DIR_سرخی_ناپ + حجم(mz_uint32) - 1) / حجم(mz_uint32)]; mz_uint8 *p_Local_سرخی = (mz_uint8 *)local_سرخی_u32;

  إذا (!mz_zip_reader_file_stat(pZip, file_اشاریہ, &file_stat))
    أرجع MZ_FALSE;

  // Empty file, or a directory (but not always a directory - I've seen odd zips with directories that have compressed data which inflates to 0 bytes)
  إذا (!file_stat.m_comp_ناپ)
    أرجع MZ_TRUE;

  // Entry is a subdirectory (I've seen old zips with dir entries which have compressed deflate data which inflates to 0 bytes, but these entries claim to uncompress to 512 bytes in the headers).
  // I'm torn how to handle this case - should it fail instead?
  إذا (mz_zip_reader_is_file_a_directory(pZip, file_اشاریہ))
    أرجع MZ_TRUE;

  // Encryption and patch files are not supported.
  إذا (file_stat.m_ثنائی_ہندسہ_flag & (1 | 32))
    أرجع MZ_FALSE;

  // This function only supports stored and deflate.
  إذا ((!(flags & MZ_ZIP_FLAG_COMPRESSED_انکڑے)) && (file_stat.m_طریقہ != 0) && (file_stat.m_طریقہ != MZ_DEFLATED))
    أرجع MZ_FALSE;

  // Read and parse the local directory entry.
  cur_file_ofs = file_stat.m_local_سرخی_ofs;
  إذا (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, p_Local_سرخی, MZ_ZIP_LOCAL_DIR_سرخی_ناپ) != MZ_ZIP_LOCAL_DIR_سرخی_ناپ)
    أرجع MZ_FALSE;
  إذا (MZ_READ_LE32(p_Local_سرخی) != MZ_ZIP_LOCAL_DIR_سرخی_SIG)
    أرجع MZ_FALSE;

  cur_file_ofs += MZ_ZIP_LOCAL_DIR_سرخی_ناپ + MZ_READ_LE16(p_Local_سرخی + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p_Local_سرخی + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  إذا ((cur_file_ofs + file_stat.m_comp_ناپ) > pZip->m_archive_ناپ)
    أرجع MZ_FALSE;

  // Decompress the file either directly from memory or from a file input buffer.
  إذا (pZip->m_pState->m_pMem)
  {
    pRead_buf = (mz_uint8 *)pZip->m_pState->m_pMem + cur_file_ofs;
    read_buf_ناپ = read_buf_avail = file_stat.m_comp_ناپ;
    comp_بچیا = 0;
  }
  وإلا
  {
    read_buf_ناپ = MZ_MIN(file_stat.m_comp_ناپ, MZ_ZIP_MAX_IO_BUF_ناپ);
    إذا (عدم == (pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)read_buf_ناپ)))
      أرجع MZ_FALSE;
    read_buf_avail = 0;
    comp_بچیا = file_stat.m_comp_ناپ;
  }

  إذا ((flags & MZ_ZIP_FLAG_COMPRESSED_انکڑے) || (!file_stat.m_طریقہ))
  {
    // The file is stored or the caller has requested the compressed data.
    إذا (pZip->m_pState->m_pMem)
    {
#جے_تعریف_شدہ _MSC_VER
      إذا (((0, حجم(size_t) == حجم(mz_uint32))) && (file_stat.m_comp_ناپ > 0xFFFFFFFF))
#وإلا
      إذا (((حجم(size_t) == حجم(mz_uint32))) && (file_stat.m_comp_ناپ > 0xFFFFFFFF))
#جے_انت
        أرجع MZ_FALSE;
      إذا (pCallback(pOpaque, باہرلا_buf_ofs, pRead_buf, (size_t)file_stat.m_comp_ناپ) != file_stat.m_comp_ناپ)
        حالت = TINFL_حالت_FAILED;
      وإلا إذا (!(flags & MZ_ZIP_FLAG_COMPRESSED_انکڑے))
        file_چکری_جانچ_32 = (mz_uint32)mz_چکری_جانچ_32(file_چکری_جانچ_32, (ثابت mz_uint8 *)pRead_buf, (size_t)file_stat.m_comp_ناپ);
      cur_file_ofs += file_stat.m_comp_ناپ;
      باہرلا_buf_ofs += file_stat.m_comp_ناپ;
      comp_بچیا = 0;
    }
    وإلا
    {
      طالما (comp_بچیا)
      {
        read_buf_avail = MZ_MIN(read_buf_ناپ, comp_بچیا);
        إذا (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
        {
          حالت = TINFL_حالت_FAILED;
          اكسر;
        }

        إذا (!(flags & MZ_ZIP_FLAG_COMPRESSED_انکڑے))
          file_چکری_جانچ_32 = (mz_uint32)mz_چکری_جانچ_32(file_چکری_جانچ_32, (ثابت mz_uint8 *)pRead_buf, (size_t)read_buf_avail);

        إذا (pCallback(pOpaque, باہرلا_buf_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
        {
          حالت = TINFL_حالت_FAILED;
          اكسر;
        }
        cur_file_ofs += read_buf_avail;
        باہرلا_buf_ofs += read_buf_avail;
        comp_بچیا -= read_buf_avail;
      }
    }
  }
  وإلا
  {
    tinfl_decompressor inflator;
    tinfl_init(&inflator);

    إذا (عدم == (pWrite_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, TINFL_LZ_DICT_ناپ)))
      حالت = TINFL_حالت_FAILED;
    وإلا
    {
      افعل
      {
        mz_uint8 *pWrite_buf_cur = (mz_uint8 *)pWrite_buf + (باہرلا_buf_ofs & (TINFL_LZ_DICT_ناپ - 1));
        size_t وچ_buf_ناپ, باہرلا_buf_ناپ = TINFL_LZ_DICT_ناپ - (باہرلا_buf_ofs & (TINFL_LZ_DICT_ناپ - 1));
        إذا ((!read_buf_avail) && (!pZip->m_pState->m_pMem))
        {
          read_buf_avail = MZ_MIN(read_buf_ناپ, comp_بچیا);
          إذا (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
          {
            حالت = TINFL_حالت_FAILED;
            اكسر;
          }
          cur_file_ofs += read_buf_avail;
          comp_بچیا -= read_buf_avail;
          read_buf_ofs = 0;
        }

        وچ_buf_ناپ = (size_t)read_buf_avail;
        حالت = tinfl_decompress(&inflator, (ثابت mz_uint8 *)pRead_buf + read_buf_ofs, &وچ_buf_ناپ, (mz_uint8 *)pWrite_buf, pWrite_buf_cur, &باہرلا_buf_ناپ, comp_بچیا ? TINFL_FLAG_HAS_ہور_داخلہ : 0);
        read_buf_avail -= وچ_buf_ناپ;
        read_buf_ofs += وچ_buf_ناپ;

        إذا (باہرلا_buf_ناپ)
        {
          إذا (pCallback(pOpaque, باہرلا_buf_ofs, pWrite_buf_cur, باہرلا_buf_ناپ) != باہرلا_buf_ناپ)
          {
            حالت = TINFL_حالت_FAILED;
            اكسر;
          }
          file_چکری_جانچ_32 = (mz_uint32)mz_چکری_جانچ_32(file_چکری_جانچ_32, pWrite_buf_cur, باہرلا_buf_ناپ);
          إذا ((باہرلا_buf_ofs += باہرلا_buf_ناپ) > file_stat.m_uncomp_ناپ)
          {
            حالت = TINFL_حالت_FAILED;
            اكسر;
          }
        }
      } طالما ((حالت == TINFL_حالت_NEEDS_ہور_داخلہ) || (حالت == TINFL_حالت_HAS_ہور_OUTPUT));
    }
  }

  إذا ((حالت == TINFL_حالت_پورا) && (!(flags & MZ_ZIP_FLAG_COMPRESSED_انکڑے)))
  {
    // Make sure the entire file was decompressed, and check its CRC.
    إذا ((باہرلا_buf_ofs != file_stat.m_uncomp_ناپ) || (file_چکری_جانچ_32 != file_stat.m_چکری_جانچ_32))
      حالت = TINFL_حالت_FAILED;
  }

  إذا (!pZip->m_pState->m_pMem)
    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
  إذا (pWrite_buf)
    pZip->m_pFree(pZip->m_pAlloc_opaque, pWrite_buf);

  أرجع حالت == TINFL_حالت_پورا;
}

mz_bool mz_zip_reader_کڈھو_file_منزل_callback(mz_zip_archive *pZip, ثابت حرف *pFilename, mz_file_write_func pCallback, فراغ *pOpaque, mz_uint flags)
{
  صحيح file_اشاریہ = mz_zip_reader_locate_file(pZip, pFilename, عدم, flags);
  إذا (file_اشاریہ < 0)
    أرجع MZ_FALSE;
  أرجع mz_zip_reader_کڈھو_منزل_callback(pZip, file_اشاریہ, pCallback, pOpaque, flags);
}

#جے_بنا_تعریف MINIZ_NO_STDIO
ساكن size_t mz_zip_file_write_callback(فراغ *pOpaque, mz_uint64 ofs, ثابت فراغ *pBuf, size_t n)
{
  (فراغ)ofs; أرجع MZ_FWRITE(pBuf, 1, n, (MZ_FILE*)pOpaque);
}

mz_bool mz_zip_reader_کڈھو_منزل_file(mz_zip_archive *pZip, mz_uint file_اشاریہ, ثابت حرف *pDst_filename, mz_uint flags)
{
  mz_bool حالت;
  mz_zip_archive_file_stat file_stat;
  MZ_FILE *pFile;
  إذا (!mz_zip_reader_file_stat(pZip, file_اشاریہ, &file_stat))
    أرجع MZ_FALSE;
  pFile = MZ_FOPEN(pDst_filename, "wb");
  إذا (!pFile)
    أرجع MZ_FALSE;
  حالت = mz_zip_reader_کڈھو_منزل_callback(pZip, file_اشاریہ, mz_zip_file_write_callback, pFile, flags);
  إذا (MZ_FCLOSE(pFile) == EOF)
    أرجع MZ_FALSE;
#جے_بنا_تعریف MINIZ_NO_ویلا
  إذا (حالت)
    mz_zip_سیٹ_file_times(pDst_filename, file_stat.m_ویلا, file_stat.m_ویلا);
#جے_انت
  أرجع حالت;
}
#جے_انت // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_reader_سرا(mz_zip_archive *pZip)
{
  إذا ((!pZip) || (!pZip->m_pState) || (!pZip->m_pAlloc) || (!pZip->m_pFree) || (pZip->m_zip_منوال != MZ_ZIP_منوال_READING))
    أرجع MZ_FALSE;

  إذا (pZip->m_pState)
  {
    mz_zip_اندرونی_state *pState = pZip->m_pState; pZip->m_pState = عدم;
    mz_zip_array_clear(pZip, &pState->m_central_dir);
    mz_zip_array_clear(pZip, &pState->m_central_dir_offsets);
    mz_zip_array_clear(pZip, &pState->m_sorted_central_dir_offsets);

#جے_بنا_تعریف MINIZ_NO_STDIO
    إذا (pState->m_pFile)
    {
      MZ_FCLOSE(pState->m_pFile);
      pState->m_pFile = عدم;
    }
#جے_انت // #ifndef MINIZ_NO_STDIO

    pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
  }
  pZip->m_zip_منوال = MZ_ZIP_منوال_INVALID;

  أرجع MZ_TRUE;
}

#جے_بنا_تعریف MINIZ_NO_STDIO
mz_bool mz_zip_reader_کڈھو_file_منزل_file(mz_zip_archive *pZip, ثابت حرف *pArchive_filename, ثابت حرف *pDst_filename, mz_uint flags)
{
  صحيح file_اشاریہ = mz_zip_reader_locate_file(pZip, pArchive_filename, عدم, flags);
  إذا (file_اشاریہ < 0)
    أرجع MZ_FALSE;
  أرجع mz_zip_reader_کڈھو_منزل_file(pZip, file_اشاریہ, pDst_filename, flags);
}
#جے_انت

// ------------------- .ZIP archive writing

#جے_بنا_تعریف MINIZ_NO_ARCHIVE_WRITING_APIS

ساكن فراغ mz_write_le16(mz_uint8 *p, mz_uint16 v) { p[0] = (mz_uint8)v; p[1] = (mz_uint8)(v >> 8); }
ساكن فراغ mz_write_le32(mz_uint8 *p, mz_uint32 v) { p[0] = (mz_uint8)v; p[1] = (mz_uint8)(v >> 8); p[2] = (mz_uint8)(v >> 16); p[3] = (mz_uint8)(v >> 24); }
#تعریف_کرو MZ_WRITE_LE16(p, v) mz_write_le16((mz_uint8 *)(p), (mz_uint16)(v))
#تعریف_کرو MZ_WRITE_LE32(p, v) mz_write_le32((mz_uint8 *)(p), (mz_uint32)(v))

mz_bool mz_zip_writer_init(mz_zip_archive *pZip, mz_uint64 existing_ناپ)
{
  إذا ((!pZip) || (pZip->m_pState) || (!pZip->m_pWrite) || (pZip->m_zip_منوال != MZ_ZIP_منوال_INVALID))
    أرجع MZ_FALSE;

  إذا (pZip->m_file_وتھ_alignment)
  {
    // Ensure user specified file offset alignment is a power of 2.
    إذا (pZip->m_file_وتھ_alignment & (pZip->m_file_وتھ_alignment - 1))
      أرجع MZ_FALSE;
  }

  إذا (!pZip->m_pAlloc) pZip->m_pAlloc = def_alloc_func;
  إذا (!pZip->m_pFree) pZip->m_pFree = def_free_func;
  إذا (!pZip->m_pRealloc) pZip->m_pRealloc = def_realloc_func;

  pZip->m_zip_منوال = MZ_ZIP_منوال_WRITING;
  pZip->m_archive_ناپ = existing_ناپ;
  pZip->m_central_directory_file_ofs = 0;
  pZip->m_کل_files = 0;

  إذا (عدم == (pZip->m_pState = (mz_zip_اندرونی_state *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, حجم(mz_zip_اندرونی_state))))
    أرجع MZ_FALSE;
  memset(pZip->m_pState, 0, حجم(mz_zip_اندرونی_state));
  MZ_ZIP_ARRAY_سیٹ_ELEMENT_ناپ(&pZip->m_pState->m_central_dir, حجم(mz_uint8));
  MZ_ZIP_ARRAY_سیٹ_ELEMENT_ناپ(&pZip->m_pState->m_central_dir_offsets, حجم(mz_uint32));
  MZ_ZIP_ARRAY_سیٹ_ELEMENT_ناپ(&pZip->m_pState->m_sorted_central_dir_offsets, حجم(mz_uint32));
  أرجع MZ_TRUE;
}

ساكن size_t mz_zip_ڈھیر_write_func(فراغ *pOpaque, mz_uint64 file_ofs, ثابت فراغ *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_zip_اندرونی_state *pState = pZip->m_pState;
  mz_uint64 new_ناپ = MZ_MAX(file_ofs + n, pState->m_mem_ناپ);
#جے_تعریف_شدہ _MSC_VER
  إذا ((!n) || ((0, حجم(size_t) == حجم(mz_uint32)) && (new_ناپ > 0x7FFFFFFF)))
#وإلا
  إذا ((!n) || ((حجم(size_t) == حجم(mz_uint32)) && (new_ناپ > 0x7FFFFFFF)))
#جے_انت
    أرجع 0;
  إذا (new_ناپ > pState->m_mem_سمرتھا)
  {
    فراغ *p_New_بلاک;
    size_t new_سمرتھا = MZ_MAX(64, pState->m_mem_سمرتھا); طالما (new_سمرتھا < new_ناپ) new_سمرتھا *= 2;
    إذا (عدم == (p_New_بلاک = pZip->m_pRealloc(pZip->m_pAlloc_opaque, pState->m_pMem, 1, new_سمرتھا)))
      أرجع 0;
    pState->m_pMem = p_New_بلاک; pState->m_mem_سمرتھا = new_سمرتھا;
  }
  حافظہ_نقل((mz_uint8 *)pState->m_pMem + file_ofs, pBuf, n);
  pState->m_mem_ناپ = (size_t)new_ناپ;
  أرجع n;
}

mz_bool mz_zip_writer_init_ڈھیر(mz_zip_archive *pZip, size_t ناپ_منزل_reserve_at_beginning, size_t initial_ونڈ_ناپ)
{
  pZip->m_pWrite = mz_zip_ڈھیر_write_func;
  pZip->m_pIO_opaque = pZip;
  إذا (!mz_zip_writer_init(pZip, ناپ_منزل_reserve_at_beginning))
    أرجع MZ_FALSE;
  إذا (0 != (initial_ونڈ_ناپ = MZ_MAX(initial_ونڈ_ناپ, ناپ_منزل_reserve_at_beginning)))
  {
    إذا (عدم == (pZip->m_pState->m_pMem = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, initial_ونڈ_ناپ)))
    {
      mz_zip_writer_سرا(pZip);
      أرجع MZ_FALSE;
    }
    pZip->m_pState->m_mem_سمرتھا = initial_ونڈ_ناپ;
  }
  أرجع MZ_TRUE;
}

#جے_بنا_تعریف MINIZ_NO_STDIO
ساكن size_t mz_zip_file_write_func(فراغ *pOpaque, mz_uint64 file_ofs, ثابت فراغ *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_int64 cur_ofs = MZ_FTELL64(pZip->m_pState->m_pFile);
  إذا (((mz_int64)file_ofs < 0) || (((cur_ofs != (mz_int64)file_ofs)) && (MZ_FSEEK64(pZip->m_pState->m_pFile, (mz_int64)file_ofs, SEEK_SET))))
    أرجع 0;
  أرجع MZ_FWRITE(pBuf, 1, n, pZip->m_pState->m_pFile);
}

mz_bool mz_zip_writer_init_file(mz_zip_archive *pZip, ثابت حرف *pFilename, mz_uint64 ناپ_منزل_reserve_at_beginning)
{
  MZ_FILE *pFile;
  pZip->m_pWrite = mz_zip_file_write_func;
  pZip->m_pIO_opaque = pZip;
  إذا (!mz_zip_writer_init(pZip, ناپ_منزل_reserve_at_beginning))
    أرجع MZ_FALSE;
  إذا (عدم == (pFile = MZ_FOPEN(pFilename, "wb")))
  {
    mz_zip_writer_سرا(pZip);
    أرجع MZ_FALSE;
  }
  pZip->m_pState->m_pFile = pFile;
  إذا (ناپ_منزل_reserve_at_beginning)
  {
    mz_uint64 cur_ofs = 0; حرف buf[4096]; MZ_CLEAR_ARR(buf);
    افعل
    {
      size_t n = (size_t)MZ_MIN(حجم(buf), ناپ_منزل_reserve_at_beginning);
      إذا (pZip->m_pWrite(pZip->m_pIO_opaque, cur_ofs, buf, n) != n)
      {
        mz_zip_writer_سرا(pZip);
        أرجع MZ_FALSE;
      }
      cur_ofs += n; ناپ_منزل_reserve_at_beginning -= n;
    } طالما (ناپ_منزل_reserve_at_beginning);
  }
  أرجع MZ_TRUE;
}
#جے_انت // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_writer_init_from_reader(mz_zip_archive *pZip, ثابت حرف *pFilename)
{
  mz_zip_اندرونی_state *pState;
  إذا ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_منوال != MZ_ZIP_منوال_READING))
    أرجع MZ_FALSE;
  // No sense in trying to write to an archive that's already at the support max size
  إذا ((pZip->m_کل_files == 0xFFFF) || ((pZip->m_archive_ناپ + MZ_ZIP_CENTRAL_DIR_سرخی_ناپ + MZ_ZIP_LOCAL_DIR_سرخی_ناپ) > 0xFFFFFFFF))
    أرجع MZ_FALSE;

  pState = pZip->m_pState;

  إذا (pState->m_pFile)
  {
#جے_تعریف_شدہ MINIZ_NO_STDIO
    pFilename; أرجع MZ_FALSE;
#وإلا
    // Archive is being read from stdio - try to reopen as writable.
    إذا (pZip->m_pIO_opaque != pZip)
      أرجع MZ_FALSE;
    إذا (!pFilename)
      أرجع MZ_FALSE;
    pZip->m_pWrite = mz_zip_file_write_func;
    إذا (عدم == (pState->m_pFile = MZ_FREOPEN(pFilename, "r+b", pState->m_pFile)))
    {
      // The mz_zip_archive is now in a bogus state because pState->m_pFile is NULL, so just close it.
      mz_zip_reader_سرا(pZip);
      أرجع MZ_FALSE;
    }
#جے_انت // #ifdef MINIZ_NO_STDIO
  }
  وإلا إذا (pState->m_pMem)
  {
    // Archive lives in a memory block. Assume it's from the heap that we can resize using the realloc callback.
    إذا (pZip->m_pIO_opaque != pZip)
      أرجع MZ_FALSE;
    pState->m_mem_سمرتھا = pState->m_mem_ناپ;
    pZip->m_pWrite = mz_zip_ڈھیر_write_func;
  }
  // Archive is being read via a user provided read function - make sure the user has specified a write function too.
  وإلا إذا (!pZip->m_pWrite)
    أرجع MZ_FALSE;

  // Start writing new files at the archive's current central directory location.
  pZip->m_archive_ناپ = pZip->m_central_directory_file_ofs;
  pZip->m_zip_منوال = MZ_ZIP_منوال_WRITING;
  pZip->m_central_directory_file_ofs = 0;

  أرجع MZ_TRUE;
}

mz_bool mz_zip_writer_جوڑو_mem(mz_zip_archive *pZip, ثابت حرف *pArchive_name, ثابت فراغ *pBuf, size_t buf_ناپ_2, mz_uint level_and_flags)
{
  أرجع mz_zip_writer_جوڑو_mem_ex(pZip, pArchive_name, pBuf, buf_ناپ_2, عدم, 0, level_and_flags, 0, 0);
}

تعريفنوع بنية
{
  mz_zip_archive *m_pZip;
  mz_uint64 m_cur_archive_file_ofs;
  mz_uint64 m_comp_ناپ;
} mz_zip_writer_جوڑو_state;

ساكن mz_bool mz_zip_writer_جوڑو_put_buf_callback(ثابت فراغ* pBuf, صحيح len, فراغ *pUser)
{
  mz_zip_writer_جوڑو_state *pState = (mz_zip_writer_جوڑو_state *)pUser;
  إذا ((صحيح)pState->m_pZip->m_pWrite(pState->m_pZip->m_pIO_opaque, pState->m_cur_archive_file_ofs, pBuf, len) != len)
    أرجع MZ_FALSE;
  pState->m_cur_archive_file_ofs += len;
  pState->m_comp_ناپ += len;
  أرجع MZ_TRUE;
}

ساكن mz_bool mz_zip_writer_create_local_dir_سرخی(mz_zip_archive *pZip, mz_uint8 *pDst, mz_uint16 filename_ناپ, mz_uint16 extra_ناپ, mz_uint64 uncomp_ناپ, mz_uint64 comp_ناپ, mz_uint32 uncomp_چکری_جانچ_32, mz_uint16 طریقہ, mz_uint16 ثنائی_ہندسہ_flags, mz_uint16 dos_ویلا, mz_uint16 dos_date)
{
  (فراغ)pZip;
  memset(pDst, 0, MZ_ZIP_LOCAL_DIR_سرخی_ناپ);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_SIG_OFS, MZ_ZIP_LOCAL_DIR_سرخی_SIG);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_نسخہ_NEEDED_OFS, طریقہ ? 20 : 0);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_ثنائی_ہندسہ_FLAG_OFS, ثنائی_ہندسہ_flags);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_طریقہ_OFS, طریقہ);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILE_ویلا_OFS, dos_ویلا);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILE_DATE_OFS, dos_date);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_چکری_جانچ_32_OFS, uncomp_چکری_جانچ_32);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_COMPRESSED_ناپ_OFS, comp_ناپ);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_DECOMPRESSED_ناپ_OFS, uncomp_ناپ);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILENAME_LEN_OFS, filename_ناپ);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_EXTRA_LEN_OFS, extra_ناپ);
  أرجع MZ_TRUE;
}

ساكن mz_bool mz_zip_writer_create_central_dir_سرخی(mz_zip_archive *pZip, mz_uint8 *pDst, mz_uint16 filename_ناپ, mz_uint16 extra_ناپ, mz_uint16 comment_ناپ, mz_uint64 uncomp_ناپ, mz_uint64 comp_ناپ, mz_uint32 uncomp_چکری_جانچ_32, mz_uint16 طریقہ, mz_uint16 ثنائی_ہندسہ_flags, mz_uint16 dos_ویلا, mz_uint16 dos_date, mz_uint64 local_سرخی_ofs, mz_uint32 ext_گن)
{
  (فراغ)pZip;
  memset(pDst, 0, MZ_ZIP_CENTRAL_DIR_سرخی_ناپ);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_SIG_OFS, MZ_ZIP_CENTRAL_DIR_سرخی_SIG);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_نسخہ_NEEDED_OFS, طریقہ ? 20 : 0);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_ثنائی_ہندسہ_FLAG_OFS, ثنائی_ہندسہ_flags);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_طریقہ_OFS, طریقہ);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILE_ویلا_OFS, dos_ویلا);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILE_DATE_OFS, dos_date);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_چکری_جانچ_32_OFS, uncomp_چکری_جانچ_32);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_COMPRESSED_ناپ_OFS, comp_ناپ);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_DECOMPRESSED_ناپ_OFS, uncomp_ناپ);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILENAME_LEN_OFS, filename_ناپ);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_EXTRA_LEN_OFS, extra_ناپ);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_COMMENT_LEN_OFS, comment_ناپ);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS, ext_گن);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_LOCAL_سرخی_OFS, local_سرخی_ofs);
  أرجع MZ_TRUE;
}

ساكن mz_bool mz_zip_writer_جوڑو_منزل_central_dir(mz_zip_archive *pZip, ثابت حرف *pFilename, mz_uint16 filename_ناپ, ثابت فراغ *pExtra, mz_uint16 extra_ناپ, ثابت فراغ *pComment, mz_uint16 comment_ناپ, mz_uint64 uncomp_ناپ, mz_uint64 comp_ناپ, mz_uint32 uncomp_چکری_جانچ_32, mz_uint16 طریقہ, mz_uint16 ثنائی_ہندسہ_flags, mz_uint16 dos_ویلا, mz_uint16 dos_date, mz_uint64 local_سرخی_ofs, mz_uint32 ext_گن)
{
  mz_zip_اندرونی_state *pState = pZip->m_pState;
  mz_uint32 central_dir_ofs = (mz_uint32)pState->m_central_dir.m_ناپ;
  size_t orig_central_dir_ناپ = pState->m_central_dir.m_ناپ;
  mz_uint8 central_dir_سرخی[MZ_ZIP_CENTRAL_DIR_سرخی_ناپ];

  // No zip64 support yet
  إذا ((local_سرخی_ofs > 0xFFFFFFFF) || (((mz_uint64)pState->m_central_dir.m_ناپ + MZ_ZIP_CENTRAL_DIR_سرخی_ناپ + filename_ناپ + extra_ناپ + comment_ناپ) > 0xFFFFFFFF))
    أرجع MZ_FALSE;

  إذا (!mz_zip_writer_create_central_dir_سرخی(pZip, central_dir_سرخی, filename_ناپ, extra_ناپ, comment_ناپ, uncomp_ناپ, comp_ناپ, uncomp_چکری_جانچ_32, طریقہ, ثنائی_ہندسہ_flags, dos_ویلا, dos_date, local_سرخی_ofs, ext_گن))
    أرجع MZ_FALSE;

  إذا ((!mz_zip_array_ڈالو_پٹھ(pZip, &pState->m_central_dir, central_dir_سرخی, MZ_ZIP_CENTRAL_DIR_سرخی_ناپ)) ||
      (!mz_zip_array_ڈالو_پٹھ(pZip, &pState->m_central_dir, pFilename, filename_ناپ)) ||
      (!mz_zip_array_ڈالو_پٹھ(pZip, &pState->m_central_dir, pExtra, extra_ناپ)) ||
      (!mz_zip_array_ڈالو_پٹھ(pZip, &pState->m_central_dir, pComment, comment_ناپ)) ||
      (!mz_zip_array_ڈالو_پٹھ(pZip, &pState->m_central_dir_offsets, &central_dir_ofs, 1)))
  {
    // Try to push the central directory array back into its original state.
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_ناپ, MZ_FALSE);
    أرجع MZ_FALSE;
  }

  أرجع MZ_TRUE;
}

ساكن mz_bool mz_zip_writer_validate_archive_name(ثابت حرف *pArchive_name)
{
  // Basic ZIP archive filename validity checks: Valid filenames cannot start with a forward slash, cannot contain a drive letter, and cannot use DOS-style backward slashes.
  إذا (*pArchive_name == '/')
    أرجع MZ_FALSE;
  طالما (*pArchive_name)
  {
    إذا ((*pArchive_name == '\\') || (*pArchive_name == ':'))
      أرجع MZ_FALSE;
    pArchive_name++;
  }
  أرجع MZ_TRUE;
}

ساكن mz_uint mz_zip_writer_compute_padding_needed_for_file_alignment(mz_zip_archive *pZip)
{
  mz_uint32 n;
  إذا (!pZip->m_file_وتھ_alignment)
    أرجع 0;
  n = (mz_uint32)(pZip->m_archive_ناپ & (pZip->m_file_وتھ_alignment - 1));
  أرجع (pZip->m_file_وتھ_alignment - n) & (pZip->m_file_وتھ_alignment - 1);
}

ساكن mz_bool mz_zip_writer_write_zeros(mz_zip_archive *pZip, mz_uint64 cur_file_ofs, mz_uint32 n)
{
  حرف buf[4096];
  memset(buf, 0, MZ_MIN(حجم(buf), n));
  طالما (n)
  {
    mz_uint32 s = MZ_MIN(حجم(buf), n);
    إذا (pZip->m_pWrite(pZip->m_pIO_opaque, cur_file_ofs, buf, s) != s)
      أرجع MZ_FALSE;
    cur_file_ofs += s; n -= s;
  }
  أرجع MZ_TRUE;
}

mz_bool mz_zip_writer_جوڑو_mem_ex(mz_zip_archive *pZip, ثابت حرف *pArchive_name, ثابت فراغ *pBuf, size_t buf_ناپ_2, ثابت فراغ *pComment, mz_uint16 comment_ناپ, mz_uint level_and_flags, mz_uint64 uncomp_ناپ, mz_uint32 uncomp_چکری_جانچ_32)
{
  mz_uint16 طریقہ = 0, dos_ویلا = 0, dos_date = 0;
  mz_uint level, ext_گن = 0, عدد_alignment_padding_بائٹاں;
  mz_uint64 local_dir_سرخی_ofs = pZip->m_archive_ناپ, cur_archive_file_ofs = pZip->m_archive_ناپ, comp_ناپ = 0;
  size_t archive_name_ناپ;
  mz_uint8 local_dir_سرخی[MZ_ZIP_LOCAL_DIR_سرخی_ناپ];
  tdefl_compressor *pComp = عدم;
  mz_bool store_انکڑے_uncompressed;
  mz_zip_اندرونی_state *pState;

  إذا ((صحيح)level_and_flags < 0)
    level_and_flags = MZ_DEFAULT_LEVEL;
  level = level_and_flags & 0xF;
  store_انکڑے_uncompressed = ((!level) || (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_انکڑے));

  إذا ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_منوال != MZ_ZIP_منوال_WRITING) || ((buf_ناپ_2) && (!pBuf)) || (!pArchive_name) || ((comment_ناپ) && (!pComment)) || (pZip->m_کل_files == 0xFFFF) || (level > MZ_UBER_COMPRESSION))
    أرجع MZ_FALSE;

  pState = pZip->m_pState;

  إذا ((!(level_and_flags & MZ_ZIP_FLAG_COMPRESSED_انکڑے)) && (uncomp_ناپ))
    أرجع MZ_FALSE;
  // No zip64 support yet
  إذا ((buf_ناپ_2 > 0xFFFFFFFF) || (uncomp_ناپ > 0xFFFFFFFF))
    أرجع MZ_FALSE;
  إذا (!mz_zip_writer_validate_archive_name(pArchive_name))
    أرجع MZ_FALSE;

#جے_بنا_تعریف MINIZ_NO_ویلا
  {
    ویلا_t cur_ویلا; ویلا(&cur_ویلا);
    mz_zip_ویلا_منزل_dos_ویلا(cur_ویلا, &dos_ویلا, &dos_date);
  }
#جے_انت // #ifndef MINIZ_NO_TIME

  archive_name_ناپ = لڑی_لمبائی(pArchive_name);
  إذا (archive_name_ناپ > 0xFFFF)
    أرجع MZ_FALSE;

  عدد_alignment_padding_بائٹاں = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  إذا ((pZip->m_کل_files == 0xFFFF) || ((pZip->m_archive_ناپ + عدد_alignment_padding_بائٹاں + MZ_ZIP_LOCAL_DIR_سرخی_ناپ + MZ_ZIP_CENTRAL_DIR_سرخی_ناپ + comment_ناپ + archive_name_ناپ) > 0xFFFFFFFF))
    أرجع MZ_FALSE;

  إذا ((archive_name_ناپ) && (pArchive_name[archive_name_ناپ - 1] == '/'))
  {
    // Set DOS Subdirectory attribute bit.
    ext_گن |= 0x10;
    // Subdirectories cannot contain data.
    إذا ((buf_ناپ_2) || (uncomp_ناپ))
      أرجع MZ_FALSE;
  }

  // Try to do any allocations before writing to the archive, so if an allocation fails the file remains unmodified. (A good idea if we're doing an in-place modification.)
  إذا ((!mz_zip_array_ensure_گنجائش(pZip, &pState->m_central_dir, MZ_ZIP_CENTRAL_DIR_سرخی_ناپ + archive_name_ناپ + comment_ناپ)) || (!mz_zip_array_ensure_گنجائش(pZip, &pState->m_central_dir_offsets, 1)))
    أرجع MZ_FALSE;

  إذا ((!store_انکڑے_uncompressed) && (buf_ناپ_2))
  {
    إذا (عدم == (pComp = (tdefl_compressor *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, حجم(tdefl_compressor))))
      أرجع MZ_FALSE;
  }

  إذا (!mz_zip_writer_write_zeros(pZip, cur_archive_file_ofs, عدد_alignment_padding_بائٹاں + حجم(local_dir_سرخی)))
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
    أرجع MZ_FALSE;
  }
  local_dir_سرخی_ofs += عدد_alignment_padding_بائٹاں;
  إذا (pZip->m_file_وتھ_alignment) { MZ_ASSERT((local_dir_سرخی_ofs & (pZip->m_file_وتھ_alignment - 1)) == 0); }
  cur_archive_file_ofs += عدد_alignment_padding_بائٹاں + حجم(local_dir_سرخی);

  MZ_CLEAR_ARR(local_dir_سرخی);
  إذا (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pArchive_name, archive_name_ناپ) != archive_name_ناپ)
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
    أرجع MZ_FALSE;
  }
  cur_archive_file_ofs += archive_name_ناپ;

  إذا (!(level_and_flags & MZ_ZIP_FLAG_COMPRESSED_انکڑے))
  {
    uncomp_چکری_جانچ_32 = (mz_uint32)mz_چکری_جانچ_32(MZ_چکری_جانچ_32_INIT, (ثابت mz_uint8*)pBuf, buf_ناپ_2);
    uncomp_ناپ = buf_ناپ_2;
    إذا (uncomp_ناپ <= 3)
    {
      level = 0;
      store_انکڑے_uncompressed = MZ_TRUE;
    }
  }

  إذا (store_انکڑے_uncompressed)
  {
    إذا (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pBuf, buf_ناپ_2) != buf_ناپ_2)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
      أرجع MZ_FALSE;
    }

    cur_archive_file_ofs += buf_ناپ_2;
    comp_ناپ = buf_ناپ_2;

    إذا (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_انکڑے)
      طریقہ = MZ_DEFLATED;
  }
  وإلا إذا (buf_ناپ_2)
  {
    mz_zip_writer_جوڑو_state state;

    state.m_pZip = pZip;
    state.m_cur_archive_file_ofs = cur_archive_file_ofs;
    state.m_comp_ناپ = 0;

    إذا ((tdefl_init(pComp, mz_zip_writer_جوڑو_put_buf_callback, &state, tdefl_create_comp_flags_from_zip_params(level, -15, MZ_DEFAULT_STRATEGY)) != TDEFL_حالت_OKAY) ||
        (tdefl_compress_بفر(pComp, pBuf, buf_ناپ_2, TDEFL_انت) != TDEFL_حالت_پورا))
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
      أرجع MZ_FALSE;
    }

    comp_ناپ = state.m_comp_ناپ;
    cur_archive_file_ofs = state.m_cur_archive_file_ofs;

    طریقہ = MZ_DEFLATED;
  }

  pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
  pComp = عدم;

  // no zip64 support yet
  إذا ((comp_ناپ > 0xFFFFFFFF) || (cur_archive_file_ofs > 0xFFFFFFFF))
    أرجع MZ_FALSE;

  إذا (!mz_zip_writer_create_local_dir_سرخی(pZip, local_dir_سرخی, (mz_uint16)archive_name_ناپ, 0, uncomp_ناپ, comp_ناپ, uncomp_چکری_جانچ_32, طریقہ, 0, dos_ویلا, dos_date))
    أرجع MZ_FALSE;

  إذا (pZip->m_pWrite(pZip->m_pIO_opaque, local_dir_سرخی_ofs, local_dir_سرخی, حجم(local_dir_سرخی)) != حجم(local_dir_سرخی))
    أرجع MZ_FALSE;

  إذا (!mz_zip_writer_جوڑو_منزل_central_dir(pZip, pArchive_name, (mz_uint16)archive_name_ناپ, عدم, 0, pComment, comment_ناپ, uncomp_ناپ, comp_ناپ, uncomp_چکری_جانچ_32, طریقہ, 0, dos_ویلا, dos_date, local_dir_سرخی_ofs, ext_گن))
    أرجع MZ_FALSE;

  pZip->m_کل_files++;
  pZip->m_archive_ناپ = cur_archive_file_ofs;

  أرجع MZ_TRUE;
}

#جے_بنا_تعریف MINIZ_NO_STDIO
mz_bool mz_zip_writer_جوڑو_file(mz_zip_archive *pZip, ثابت حرف *pArchive_name, ثابت حرف *pSrc_filename, ثابت فراغ *pComment, mz_uint16 comment_ناپ, mz_uint level_and_flags)
{
  mz_uint uncomp_چکری_جانچ_32 = MZ_چکری_جانچ_32_INIT, level, عدد_alignment_padding_بائٹاں;
  mz_uint16 طریقہ = 0, dos_ویلا = 0, dos_date = 0, ext_گن = 0;
  mz_uint64 local_dir_سرخی_ofs = pZip->m_archive_ناپ, cur_archive_file_ofs = pZip->m_archive_ناپ, uncomp_ناپ = 0, comp_ناپ = 0;
  size_t archive_name_ناپ;
  mz_uint8 local_dir_سرخی[MZ_ZIP_LOCAL_DIR_سرخی_ناپ];
  MZ_FILE *pSrc_file = عدم;

  إذا ((صحيح)level_and_flags < 0)
    level_and_flags = MZ_DEFAULT_LEVEL;
  level = level_and_flags & 0xF;

  إذا ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_منوال != MZ_ZIP_منوال_WRITING) || (!pArchive_name) || ((comment_ناپ) && (!pComment)) || (level > MZ_UBER_COMPRESSION))
    أرجع MZ_FALSE;
  إذا (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_انکڑے)
    أرجع MZ_FALSE;
  إذا (!mz_zip_writer_validate_archive_name(pArchive_name))
    أرجع MZ_FALSE;

  archive_name_ناپ = لڑی_لمبائی(pArchive_name);
  إذا (archive_name_ناپ > 0xFFFF)
    أرجع MZ_FALSE;

  عدد_alignment_padding_بائٹاں = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  إذا ((pZip->m_کل_files == 0xFFFF) || ((pZip->m_archive_ناپ + عدد_alignment_padding_بائٹاں + MZ_ZIP_LOCAL_DIR_سرخی_ناپ + MZ_ZIP_CENTRAL_DIR_سرخی_ناپ + comment_ناپ + archive_name_ناپ) > 0xFFFFFFFF))
    أرجع MZ_FALSE;

  إذا (!mz_zip_get_file_modified_ویلا(pSrc_filename, &dos_ویلا, &dos_date))
    أرجع MZ_FALSE;

  pSrc_file = MZ_FOPEN(pSrc_filename, "rb");
  إذا (!pSrc_file)
    أرجع MZ_FALSE;
  MZ_FSEEK64(pSrc_file, 0, SEEK_END);
  uncomp_ناپ = MZ_FTELL64(pSrc_file);
  MZ_FSEEK64(pSrc_file, 0, SEEK_SET);

  إذا (uncomp_ناپ > 0xFFFFFFFF)
  {
    // No zip64 support yet
    MZ_FCLOSE(pSrc_file);
    أرجع MZ_FALSE;
  }
  إذا (uncomp_ناپ <= 3)
    level = 0;

  إذا (!mz_zip_writer_write_zeros(pZip, cur_archive_file_ofs, عدد_alignment_padding_بائٹاں + حجم(local_dir_سرخی)))
  {
    MZ_FCLOSE(pSrc_file);
    أرجع MZ_FALSE;
  }
  local_dir_سرخی_ofs += عدد_alignment_padding_بائٹاں;
  إذا (pZip->m_file_وتھ_alignment) { MZ_ASSERT((local_dir_سرخی_ofs & (pZip->m_file_وتھ_alignment - 1)) == 0); }
  cur_archive_file_ofs += عدد_alignment_padding_بائٹاں + حجم(local_dir_سرخی);

  MZ_CLEAR_ARR(local_dir_سرخی);
  إذا (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pArchive_name, archive_name_ناپ) != archive_name_ناپ)
  {
    MZ_FCLOSE(pSrc_file);
    أرجع MZ_FALSE;
  }
  cur_archive_file_ofs += archive_name_ناپ;

  إذا (uncomp_ناپ)
  {
    mz_uint64 uncomp_بچیا = uncomp_ناپ;
    فراغ *pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, MZ_ZIP_MAX_IO_BUF_ناپ);
    إذا (!pRead_buf)
    {
      MZ_FCLOSE(pSrc_file);
      أرجع MZ_FALSE;
    }

    إذا (!level)
    {
      طالما (uncomp_بچیا)
      {
        mz_uint n = (mz_uint)MZ_MIN(MZ_ZIP_MAX_IO_BUF_ناپ, uncomp_بچیا);
        إذا ((MZ_FREAD(pRead_buf, 1, n, pSrc_file) != n) || (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pRead_buf, n) != n))
        {
          pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
          MZ_FCLOSE(pSrc_file);
          أرجع MZ_FALSE;
        }
        uncomp_چکری_جانچ_32 = (mz_uint32)mz_چکری_جانچ_32(uncomp_چکری_جانچ_32, (ثابت mz_uint8 *)pRead_buf, n);
        uncomp_بچیا -= n;
        cur_archive_file_ofs += n;
      }
      comp_ناپ = uncomp_ناپ;
    }
    وإلا
    {
      mz_bool نتیجہ = MZ_FALSE;
      mz_zip_writer_جوڑو_state state;
      tdefl_compressor *pComp = (tdefl_compressor *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, حجم(tdefl_compressor));
      إذا (!pComp)
      {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        أرجع MZ_FALSE;
      }

      state.m_pZip = pZip;
      state.m_cur_archive_file_ofs = cur_archive_file_ofs;
      state.m_comp_ناپ = 0;

      إذا (tdefl_init(pComp, mz_zip_writer_جوڑو_put_buf_callback, &state, tdefl_create_comp_flags_from_zip_params(level, -15, MZ_DEFAULT_STRATEGY)) != TDEFL_حالت_OKAY)
      {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        أرجع MZ_FALSE;
      }

      لكل ( ; ; )
      {
        size_t وچ_buf_ناپ = (mz_uint32)MZ_MIN(uncomp_بچیا, MZ_ZIP_MAX_IO_BUF_ناپ);
        tdefl_حالت حالت;

        إذا (MZ_FREAD(pRead_buf, 1, وچ_buf_ناپ, pSrc_file) != وچ_buf_ناپ)
          اكسر;

        uncomp_چکری_جانچ_32 = (mz_uint32)mz_چکری_جانچ_32(uncomp_چکری_جانچ_32, (ثابت mz_uint8 *)pRead_buf, وچ_buf_ناپ);
        uncomp_بچیا -= وچ_buf_ناپ;

        حالت = tdefl_compress_بفر(pComp, pRead_buf, وچ_buf_ناپ, uncomp_بچیا ? TDEFL_NO_FLUSH : TDEFL_انت);
        إذا (حالت == TDEFL_حالت_پورا)
        {
          نتیجہ = MZ_TRUE;
          اكسر;
        }
        وإلا إذا (حالت != TDEFL_حالت_OKAY)
          اكسر;
      }

      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);

      إذا (!نتیجہ)
      {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        أرجع MZ_FALSE;
      }

      comp_ناپ = state.m_comp_ناپ;
      cur_archive_file_ofs = state.m_cur_archive_file_ofs;

      طریقہ = MZ_DEFLATED;
    }

    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
  }

  MZ_FCLOSE(pSrc_file); pSrc_file = عدم;

  // no zip64 support yet
  إذا ((comp_ناپ > 0xFFFFFFFF) || (cur_archive_file_ofs > 0xFFFFFFFF))
    أرجع MZ_FALSE;

  إذا (!mz_zip_writer_create_local_dir_سرخی(pZip, local_dir_سرخی, (mz_uint16)archive_name_ناپ, 0, uncomp_ناپ, comp_ناپ, uncomp_چکری_جانچ_32, طریقہ, 0, dos_ویلا, dos_date))
    أرجع MZ_FALSE;

  إذا (pZip->m_pWrite(pZip->m_pIO_opaque, local_dir_سرخی_ofs, local_dir_سرخی, حجم(local_dir_سرخی)) != حجم(local_dir_سرخی))
    أرجع MZ_FALSE;

  إذا (!mz_zip_writer_جوڑو_منزل_central_dir(pZip, pArchive_name, (mz_uint16)archive_name_ناپ, عدم, 0, pComment, comment_ناپ, uncomp_ناپ, comp_ناپ, uncomp_چکری_جانچ_32, طریقہ, 0, dos_ویلا, dos_date, local_dir_سرخی_ofs, ext_گن))
    أرجع MZ_FALSE;

  pZip->m_کل_files++;
  pZip->m_archive_ناپ = cur_archive_file_ofs;

  أرجع MZ_TRUE;
}
#جے_انت // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_writer_جوڑو_from_zip_reader(mz_zip_archive *pZip, mz_zip_archive *p_سروت_zip, mz_uint file_اشاریہ)
{
  mz_uint n, ثنائی_ہندسہ_flags, عدد_alignment_padding_بائٹاں;
  mz_uint64 comp_بائٹاں_بچیا, local_dir_سرخی_ofs;
  mz_uint64 cur_src_file_ofs, cur_dst_file_ofs;
  mz_uint32 local_سرخی_u32[(MZ_ZIP_LOCAL_DIR_سرخی_ناپ + حجم(mz_uint32) - 1) / حجم(mz_uint32)]; mz_uint8 *p_Local_سرخی = (mz_uint8 *)local_سرخی_u32;
  mz_uint8 central_سرخی[MZ_ZIP_CENTRAL_DIR_سرخی_ناپ];
  size_t orig_central_dir_ناپ;
  mz_zip_اندرونی_state *pState;
  فراغ *pBuf; ثابت mz_uint8 *p_Src_central_سرخی;

  إذا ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_منوال != MZ_ZIP_منوال_WRITING))
    أرجع MZ_FALSE;
  إذا (عدم == (p_Src_central_سرخی = mz_zip_reader_get_cdh(p_سروت_zip, file_اشاریہ)))
    أرجع MZ_FALSE;
  pState = pZip->m_pState;

  عدد_alignment_padding_بائٹاں = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  إذا ((pZip->m_کل_files == 0xFFFF) || ((pZip->m_archive_ناپ + عدد_alignment_padding_بائٹاں + MZ_ZIP_LOCAL_DIR_سرخی_ناپ + MZ_ZIP_CENTRAL_DIR_سرخی_ناپ) > 0xFFFFFFFF))
    أرجع MZ_FALSE;

  cur_src_file_ofs = MZ_READ_LE32(p_Src_central_سرخی + MZ_ZIP_CDH_LOCAL_سرخی_OFS);
  cur_dst_file_ofs = pZip->m_archive_ناپ;

  إذا (p_سروت_zip->m_pRead(p_سروت_zip->m_pIO_opaque, cur_src_file_ofs, p_Local_سرخی, MZ_ZIP_LOCAL_DIR_سرخی_ناپ) != MZ_ZIP_LOCAL_DIR_سرخی_ناپ)
    أرجع MZ_FALSE;
  إذا (MZ_READ_LE32(p_Local_سرخی) != MZ_ZIP_LOCAL_DIR_سرخی_SIG)
    أرجع MZ_FALSE;
  cur_src_file_ofs += MZ_ZIP_LOCAL_DIR_سرخی_ناپ;

  إذا (!mz_zip_writer_write_zeros(pZip, cur_dst_file_ofs, عدد_alignment_padding_بائٹاں))
    أرجع MZ_FALSE;
  cur_dst_file_ofs += عدد_alignment_padding_بائٹاں;
  local_dir_سرخی_ofs = cur_dst_file_ofs;
  إذا (pZip->m_file_وتھ_alignment) { MZ_ASSERT((local_dir_سرخی_ofs & (pZip->m_file_وتھ_alignment - 1)) == 0); }

  إذا (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, p_Local_سرخی, MZ_ZIP_LOCAL_DIR_سرخی_ناپ) != MZ_ZIP_LOCAL_DIR_سرخی_ناپ)
    أرجع MZ_FALSE;
  cur_dst_file_ofs += MZ_ZIP_LOCAL_DIR_سرخی_ناپ;

  n = MZ_READ_LE16(p_Local_سرخی + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p_Local_سرخی + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  comp_بائٹاں_بچیا = n + MZ_READ_LE32(p_Src_central_سرخی + MZ_ZIP_CDH_COMPRESSED_ناپ_OFS);

  إذا (عدم == (pBuf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)MZ_MAX(حجم(mz_uint32) * 4, MZ_MIN(MZ_ZIP_MAX_IO_BUF_ناپ, comp_بائٹاں_بچیا)))))
    أرجع MZ_FALSE;

  طالما (comp_بائٹاں_بچیا)
  {
    n = (mz_uint)MZ_MIN(MZ_ZIP_MAX_IO_BUF_ناپ, comp_بائٹاں_بچیا);
    إذا (p_سروت_zip->m_pRead(p_سروت_zip->m_pIO_opaque, cur_src_file_ofs, pBuf, n) != n)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      أرجع MZ_FALSE;
    }
    cur_src_file_ofs += n;

    إذا (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, pBuf, n) != n)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      أرجع MZ_FALSE;
    }
    cur_dst_file_ofs += n;

    comp_بائٹاں_بچیا -= n;
  }

  ثنائی_ہندسہ_flags = MZ_READ_LE16(p_Local_سرخی + MZ_ZIP_LDH_ثنائی_ہندسہ_FLAG_OFS);
  إذا (ثنائی_ہندسہ_flags & 8)
  {
    // Copy data descriptor
    إذا (p_سروت_zip->m_pRead(p_سروت_zip->m_pIO_opaque, cur_src_file_ofs, pBuf, حجم(mz_uint32) * 4) != حجم(mz_uint32) * 4)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      أرجع MZ_FALSE;
    }

    n = حجم(mz_uint32) * ((MZ_READ_LE32(pBuf) == 0x08074b50) ? 4 : 3);
    إذا (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, pBuf, n) != n)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      أرجع MZ_FALSE;
    }

    cur_src_file_ofs += n;
    cur_dst_file_ofs += n;
  }
  pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);

  // no zip64 support yet
  إذا (cur_dst_file_ofs > 0xFFFFFFFF)
    أرجع MZ_FALSE;

  orig_central_dir_ناپ = pState->m_central_dir.m_ناپ;

  حافظہ_نقل(central_سرخی, p_Src_central_سرخی, MZ_ZIP_CENTRAL_DIR_سرخی_ناپ);
  MZ_WRITE_LE32(central_سرخی + MZ_ZIP_CDH_LOCAL_سرخی_OFS, local_dir_سرخی_ofs);
  إذا (!mz_zip_array_ڈالو_پٹھ(pZip, &pState->m_central_dir, central_سرخی, MZ_ZIP_CENTRAL_DIR_سرخی_ناپ))
    أرجع MZ_FALSE;

  n = MZ_READ_LE16(p_Src_central_سرخی + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p_Src_central_سرخی + MZ_ZIP_CDH_EXTRA_LEN_OFS) + MZ_READ_LE16(p_Src_central_سرخی + MZ_ZIP_CDH_COMMENT_LEN_OFS);
  إذا (!mz_zip_array_ڈالو_پٹھ(pZip, &pState->m_central_dir, p_Src_central_سرخی + MZ_ZIP_CENTRAL_DIR_سرخی_ناپ, n))
  {
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_ناپ, MZ_FALSE);
    أرجع MZ_FALSE;
  }

  إذا (pState->m_central_dir.m_ناپ > 0xFFFFFFFF)
    أرجع MZ_FALSE;
  n = (mz_uint32)orig_central_dir_ناپ;
  إذا (!mz_zip_array_ڈالو_پٹھ(pZip, &pState->m_central_dir_offsets, &n, 1))
  {
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_ناپ, MZ_FALSE);
    أرجع MZ_FALSE;
  }

  pZip->m_کل_files++;
  pZip->m_archive_ناپ = cur_dst_file_ofs;

  أرجع MZ_TRUE;
}

mz_bool mz_zip_writer_finalize_archive(mz_zip_archive *pZip)
{
  mz_zip_اندرونی_state *pState;
  mz_uint64 central_dir_ofs, central_dir_ناپ;
  mz_uint8 hdr[MZ_ZIP_سرا_دا_CENTRAL_DIR_سرخی_ناپ];

  إذا ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_منوال != MZ_ZIP_منوال_WRITING))
    أرجع MZ_FALSE;

  pState = pZip->m_pState;

  // no zip64 support yet
  إذا ((pZip->m_کل_files > 0xFFFF) || ((pZip->m_archive_ناپ + pState->m_central_dir.m_ناپ + MZ_ZIP_سرا_دا_CENTRAL_DIR_سرخی_ناپ) > 0xFFFFFFFF))
    أرجع MZ_FALSE;

  central_dir_ofs = 0;
  central_dir_ناپ = 0;
  إذا (pZip->m_کل_files)
  {
    // Write central directory
    central_dir_ofs = pZip->m_archive_ناپ;
    central_dir_ناپ = pState->m_central_dir.m_ناپ;
    pZip->m_central_directory_file_ofs = central_dir_ofs;
    إذا (pZip->m_pWrite(pZip->m_pIO_opaque, central_dir_ofs, pState->m_central_dir.m_p, (size_t)central_dir_ناپ) != central_dir_ناپ)
      أرجع MZ_FALSE;
    pZip->m_archive_ناپ += central_dir_ناپ;
  }

  // Write end of central directory record
  MZ_CLEAR_ARR(hdr);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_SIG_OFS, MZ_ZIP_سرا_دا_CENTRAL_DIR_سرخی_SIG);
  MZ_WRITE_LE16(hdr + MZ_ZIP_ECDH_CDIR_عدد_ENTRIES_ON_DISK_OFS, pZip->m_کل_files);
  MZ_WRITE_LE16(hdr + MZ_ZIP_ECDH_CDIR_کل_ENTRIES_OFS, pZip->m_کل_files);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_CDIR_ناپ_OFS, central_dir_ناپ);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_CDIR_OFS_OFS, central_dir_ofs);

  إذا (pZip->m_pWrite(pZip->m_pIO_opaque, pZip->m_archive_ناپ, hdr, حجم(hdr)) != حجم(hdr))
    أرجع MZ_FALSE;
#جے_بنا_تعریف MINIZ_NO_STDIO
  إذا ((pState->m_pFile) && (MZ_FFLUSH(pState->m_pFile) == EOF))
    أرجع MZ_FALSE;
#جے_انت // #ifndef MINIZ_NO_STDIO

  pZip->m_archive_ناپ += حجم(hdr);

  pZip->m_zip_منوال = MZ_ZIP_منوال_WRITING_HAS_BEEN_FINALIZED;
  أرجع MZ_TRUE;
}

mz_bool mz_zip_writer_finalize_ڈھیر_archive(mz_zip_archive *pZip, فراغ **pBuf, size_t *p_ناپ)
{
  إذا ((!pZip) || (!pZip->m_pState) || (!pBuf) || (!p_ناپ))
    أرجع MZ_FALSE;
  إذا (pZip->m_pWrite != mz_zip_ڈھیر_write_func)
    أرجع MZ_FALSE;
  إذا (!mz_zip_writer_finalize_archive(pZip))
    أرجع MZ_FALSE;

  *pBuf = pZip->m_pState->m_pMem;
  *p_ناپ = pZip->m_pState->m_mem_ناپ;
  pZip->m_pState->m_pMem = عدم;
  pZip->m_pState->m_mem_ناپ = pZip->m_pState->m_mem_سمرتھا = 0;
  أرجع MZ_TRUE;
}

mz_bool mz_zip_writer_سرا(mz_zip_archive *pZip)
{
  mz_zip_اندرونی_state *pState;
  mz_bool حالت = MZ_TRUE;
  إذا ((!pZip) || (!pZip->m_pState) || (!pZip->m_pAlloc) || (!pZip->m_pFree) || ((pZip->m_zip_منوال != MZ_ZIP_منوال_WRITING) && (pZip->m_zip_منوال != MZ_ZIP_منوال_WRITING_HAS_BEEN_FINALIZED)))
    أرجع MZ_FALSE;

  pState = pZip->m_pState;
  pZip->m_pState = عدم;
  mz_zip_array_clear(pZip, &pState->m_central_dir);
  mz_zip_array_clear(pZip, &pState->m_central_dir_offsets);
  mz_zip_array_clear(pZip, &pState->m_sorted_central_dir_offsets);

#جے_بنا_تعریف MINIZ_NO_STDIO
  إذا (pState->m_pFile)
  {
    MZ_FCLOSE(pState->m_pFile);
    pState->m_pFile = عدم;
  }
#جے_انت // #ifndef MINIZ_NO_STDIO

  إذا ((pZip->m_pWrite == mz_zip_ڈھیر_write_func) && (pState->m_pMem))
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pState->m_pMem);
    pState->m_pMem = عدم;
  }

  pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
  pZip->m_zip_منوال = MZ_ZIP_منوال_INVALID;
  أرجع حالت;
}

#جے_بنا_تعریف MINIZ_NO_STDIO
mz_bool mz_zip_جوڑو_mem_منزل_archive_file_وچ_رکھو(ثابت حرف *pZip_filename, ثابت حرف *pArchive_name, ثابت فراغ *pBuf, size_t buf_ناپ_2, ثابت فراغ *pComment, mz_uint16 comment_ناپ, mz_uint level_and_flags)
{
  mz_bool حالت, created_new_archive = MZ_FALSE;
  mz_zip_archive zip_archive;
  بنية MZ_FILE_STAT_STRUCT file_stat;
  MZ_CLEAR_OBJ(zip_archive);
  إذا ((صحيح)level_and_flags < 0)
     level_and_flags = MZ_DEFAULT_LEVEL;
  إذا ((!pZip_filename) || (!pArchive_name) || ((buf_ناپ_2) && (!pBuf)) || ((comment_ناپ) && (!pComment)) || ((level_and_flags & 0xF) > MZ_UBER_COMPRESSION))
    أرجع MZ_FALSE;
  إذا (!mz_zip_writer_validate_archive_name(pArchive_name))
    أرجع MZ_FALSE;
  إذا (MZ_FILE_STAT(pZip_filename, &file_stat) != 0)
  {
    // Create a new archive.
    إذا (!mz_zip_writer_init_file(&zip_archive, pZip_filename, 0))
      أرجع MZ_FALSE;
    created_new_archive = MZ_TRUE;
  }
  وإلا
  {
    // Append to an existing archive.
    إذا (!mz_zip_reader_init_file(&zip_archive, pZip_filename, level_and_flags | MZ_ZIP_FLAG_DO_NOT_ترتیب_دیو_CENTRAL_DIRECTORY))
      أرجع MZ_FALSE;
    إذا (!mz_zip_writer_init_from_reader(&zip_archive, pZip_filename))
    {
      mz_zip_reader_سرا(&zip_archive);
      أرجع MZ_FALSE;
    }
  }
  حالت = mz_zip_writer_جوڑو_mem_ex(&zip_archive, pArchive_name, pBuf, buf_ناپ_2, pComment, comment_ناپ, level_and_flags, 0, 0);
  // Always finalize, even if adding failed for some reason, so we have a valid central directory. (This may not always succeed, but we can try.)
  إذا (!mz_zip_writer_finalize_archive(&zip_archive))
    حالت = MZ_FALSE;
  إذا (!mz_zip_writer_سرا(&zip_archive))
    حالت = MZ_FALSE;
  إذا ((!حالت) && (created_new_archive))
  {
    // It's a new archive and something went wrong, so just delete it.
    صحيح ignored_حالت = MZ_DELETE_FILE(pZip_filename);
    (فراغ)ignored_حالت;
  }
  أرجع حالت;
}

فراغ *mz_zip_کڈھو_archive_file_منزل_ڈھیر(ثابت حرف *pZip_filename, ثابت حرف *pArchive_name, size_t *p_ناپ, mz_uint flags)
{
  صحيح file_اشاریہ;
  mz_zip_archive zip_archive;
  فراغ *p = عدم;

  إذا (p_ناپ)
    *p_ناپ = 0;

  إذا ((!pZip_filename) || (!pArchive_name))
    أرجع عدم;

  MZ_CLEAR_OBJ(zip_archive);
  إذا (!mz_zip_reader_init_file(&zip_archive, pZip_filename, flags | MZ_ZIP_FLAG_DO_NOT_ترتیب_دیو_CENTRAL_DIRECTORY))
    أرجع عدم;

  إذا ((file_اشاریہ = mz_zip_reader_locate_file(&zip_archive, pArchive_name, عدم, flags)) >= 0)
    p = mz_zip_reader_کڈھو_منزل_ڈھیر(&zip_archive, file_اشاریہ, p_ناپ, flags);

  mz_zip_reader_سرا(&zip_archive);
  أرجع p;
}

#جے_انت // #ifndef MINIZ_NO_STDIO

#جے_انت // #ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

#جے_انت // #ifndef MINIZ_NO_ARCHIVE_APIS

#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#جے_تعریف_شدہ _MSC_VER
#ہدایت warning (نکالو)
#جے_انت

#جے_انت // MINIZ_HEADER_FILE_ONLY

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

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

#اگر_تعریف_نشده MINIZ_سرآیند_INCLUDED
#تعریف_کن MINIZ_سرآیند_INCLUDED

/*#include <stdlib.h>*/

// Defines to completely disable specific portions of miniz.c:
// If all macros here are defined the only functionality remaining will be CRC-32, adler-32, tinfl, and tdefl.

// Define MINIZ_NO_STDIO to disable all usage and any functions which rely on stdio for file I/O.
#تعریف_کن MINIZ_NO_STDIO

// If MINIZ_NO_TIME is specified then the ZIP archive functions will not be able to get the current time, or
// get/set file times, and the C run-time funcs that get/set times won't be called.
// The current downside is the times written to your archives will be from 1979.
#تعریف_کن MINIZ_NO_زمان

// Define MINIZ_NO_DEFLATE_APIS to disable all compression API's.
//#define MINIZ_NO_DEFLATE_APIS

// Define MINIZ_NO_INFLATE_APIS to disable all decompression API's.
#تعریف_کن MINIZ_NO_INFLATE_APIS

// Define MINIZ_NO_ARCHIVE_APIS to disable all ZIP archive API's.
#تعریف_کن MINIZ_NO_ARCHIVE_APIS

// Define MINIZ_NO_ARCHIVE_APIS to disable all writing related ZIP archive API's.
#تعریف_کن MINIZ_NO_ARCHIVE_WRITING_APIS

// Define MINIZ_NO_ZLIB_APIS to remove all ZLIB-style compression/decompression API's.
#تعریف_کن MINIZ_NO_ZLIB_APIS

// Define MINIZ_NO_ZLIB_COMPATIBLE_NAME to disable zlib names, to prevent conflicts against stock zlib.
#تعریف_کن MINIZ_NO_ZLIB_COMPATIBLE_نامها

// Define MINIZ_NO_MALLOC to disable all calls to malloc, free, and realloc.
// Note if MINIZ_NO_MALLOC is defined then the user must always provide custom user alloc/free/realloc
// callbacks to the zlib and archive API's, and a few stand-alone helper API's which don't provide custom user
// functions (such as tdefl_compress_mem_to_heap() and tinfl_decompress_mem_to_heap()) won't work.
//#define MINIZ_NO_MALLOC
#تعریف_کن MINIZ_SDL_MALLOC

#اگر_تعریف_شده MINIZ_NO_INFLATE_APIS
#تعریف_کن MINIZ_NO_ARCHIVE_APIS
#پایان_اگر

#اگر_تعریف_شده MINIZ_NO_DEFLATE_APIS
#تعریف_کن MINIZ_NO_ARCHIVE_WRITING_APIS
#پایان_اگر

// Define MINIZ_STATIC_FUNCTIONS to make all functions static. You probably
// want this if you're using miniz in a library
#تعریف_کن MINIZ_STATIC_FUNCTIONS

#إذا defined(__TINYC__) && (defined(__linux) || defined(__linux__))
  // TODO: Work around "error: include file 'sys\utime.h' when compiling with tcc on Linux
  #تعریف_کن MINIZ_NO_زمان
#پایان_اگر

#إذا !defined(MINIZ_NO_زمان) && !defined(MINIZ_NO_ARCHIVE_APIS)
  #ضمن <time.h>
#پایان_اگر

#إذا defined(_M_IX86) || defined(_M_X64) || defined(__i386__) || defined(__i386) || defined(__i486__) || defined(__i486) || defined(i386) || defined(__ia64__) || defined(__x86_64__)
// MINIZ_X86_OR_X64_CPU is only used to help set the below macros.
#تعریف_کن MINIZ_X86_OR_X64_CPU 1
#پایان_اگر

#اگر_تعریف_نشده MINIZ_LITTLE_ENDIAN /* if not defined by SDL */
#إذا (__BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__) || MINIZ_X86_OR_X64_CPU
// Set MINIZ_LITTLE_ENDIAN to 1 if the processor is little endian.
#تعریف_کن MINIZ_LITTLE_ENDIAN 1
#پایان_اگر
#پایان_اگر // MINIZ_LITTLE_ENDIAN /* if not defined by SDL */

#اگر_تعریف_نشده MINIZ_USE_UNALIGNED_LOADS_AND_STORES
#إذا MINIZ_X86_OR_X64_CPU
// Set MINIZ_USE_UNALIGNED_LOADS_AND_STORES to 1 on CPU's that permit efficient integer loads and stores from unaligned addresses.
#تعریف_کن MINIZ_USE_UNALIGNED_LOADS_AND_STORES 1
#پایان_اگر
#پایان_اگر // MINIZ_USE_UNALIGNED_LOADS_AND_STORES

#إذا defined(_M_X64) || defined(_WIN64) || defined(__MINGW64__) || defined(_LP64) || defined(__LP64__) || defined(__ia64__) || defined(__x86_64__)
// Set MINIZ_HAS_64BIT_REGISTERS to 1 if operations on 64-bit integers are reasonably fast (and don't involve compiler generated calls to helper functions).
#تعریف_کن MINIZ_HAS_64_بیت_REGISTERS 1
#پایان_اگر

#اگر_تعریف_شده MINIZ_STATIC_FUNCTIONS
#تعریف_کن MINIZ_STATIC ساكن
#وإلا
#تعریف_کن MINIZ_STATIC
#پایان_اگر

#اگر_تعریف_شده __cplusplus
خارجي "C" {
#پایان_اگر

// ------------------- zlib-style API Definitions.

// For more compatibility with zlib, miniz.c uses unsigned long for some parameters/struct members. Beware: mz_ulong can be either 32 or 64-bits!
تعريفنوع بیعلامت دراز mz_ulong;

// mz_free() internally uses the MZ_FREE() macro (which by default calls free() unless you've modified the MZ_MALLOC macro) to release a block allocated from the heap.
MINIZ_STATIC فراغ mz_free(فراغ *p);

#تعریف_کن MZ_ADLER32_INIT (1)
// mz_adler32() returns the initial adler-32 value to use when called with ptr==NULL.
MINIZ_STATIC mz_ulong mz_adler32(mz_ulong adler, ثابت بیعلامت حرف *ptr, size_t buf_len);

#تعریف_کن MZ_بررسی_چرخهای_32_INIT (0)
// mz_crc32() returns the initial CRC-32 value to use when called with ptr==NULL.
MINIZ_STATIC mz_ulong mz_بررسی_چرخهای_32(mz_ulong بررسی_چرخهای, ثابت بیعلامت حرف *ptr, size_t buf_len);

// Compression strategies.
تعداد { MZ_DEFAULT_STRATEGY = 0, MZ_FILTERED = 1, MZ_HUFFMAN_ONLY = 2, MZ_RLE = 3, MZ_FIXED = 4 };

//روش
#تعریف_کن MZ_DEFLATED 8

#اگر_تعریف_نشده MINIZ_NO_ZLIB_APIS

// Heap allocation callbacks.
// Note that mz_alloc_func parameter types purpsosely differ from zlib's: items/size is size_t, not unsigned long.
تعريفنوع فراغ *(*mz_alloc_func)(فراغ *opaque, size_t اقلام, size_t اندازه);
تعريفنوع فراغ (*mz_free_func)(فراغ *opaque, فراغ *آدرس);
تعريفنوع فراغ *(*mz_realloc_func)(فراغ *opaque, فراغ *آدرس, size_t اقلام, size_t اندازه);

#تعریف_کن MZ_نسخه          "9.1.15"
#تعریف_کن MZ_VERNUM           0x91F0
#تعریف_کن MZ_VER_MAJOR        9
#تعریف_کن MZ_VER_MINOR        1
#تعریف_کن MZ_VER_REVISION     15
#تعریف_کن MZ_VER_SUBREVISION  0

// Flush values. For typical usage you only need MZ_NO_FLUSH and MZ_FINISH. The other values are for advanced use (refer to the zlib docs).
تعداد { MZ_NO_FLUSH = 0, MZ_PARTIAL_FLUSH = 1, MZ_SYNC_FLUSH = 2, MZ_پر_FLUSH = 3, MZ_پایان = 4, MZ_بلوک = 5 };

// Return status codes. MZ_PARAM_ERROR is non-standard.
تعداد { MZ_OK = 0, MZ_جریان_انتها = 1, MZ_NEED_DICT = 2, MZ_ERRNO = -1, MZ_جریان_ERROR = -2, MZ_داده_ERROR = -3, MZ_MEM_ERROR = -4, MZ_BUF_ERROR = -5, MZ_نسخه_ERROR = -6, MZ_PARAM_ERROR = -10000 };

// Compression levels: 0-9 are the standard zlib-style levels, 10 is best possible compression (not zlib compatible, and may be very slow), MZ_DEFAULT_COMPRESSION=MZ_DEFAULT_LEVEL.
تعداد { MZ_NO_COMPRESSION = 0, MZ_بهترین_سرعت = 1, MZ_بهترین_COMPRESSION = 9, MZ_UBER_COMPRESSION = 10, MZ_DEFAULT_LEVEL = 6, MZ_DEFAULT_COMPRESSION = -1 };

// Window bits
#تعریف_کن MZ_DEFAULT_پنجره_بیتها 15

بنية mz_داخلی_state;

// Compression/decompression stream struct.
تعريفنوع بنية mz_جریان_s
{
  ثابت بیعلامت حرف *بعدی_درون;     // pointer to next byte to read
  بیعلامت صحيح avail_درون;            // number of bytes available at next_in
  mz_ulong مجموع_درون;                // total number of bytes consumed so far

  بیعلامت حرف *بعدی_بیرون;          // pointer to next byte to write
  بیعلامت صحيح avail_بیرون;           // number of bytes that can be written to next_out
  mz_ulong مجموع_بیرون;               // total number of bytes produced so far

  حرف *پیام_2;                        // error msg (unused)
  بنية mz_داخلی_state *state;  // internal state, allocated by zalloc/zfree

  mz_alloc_func zalloc;             // optional heap allocation function (defaults to malloc)
  mz_free_func zfree;               // optional heap free function (defaults to free)
  فراغ *opaque;                     // heap alloc function user pointer

  صحيح داده_type;                    // data_type (unused)
  mz_ulong adler;                   // adler32 of the source or uncompressed data
  mz_ulong reserved;                // not used
} mz_جریان;

تعريفنوع mz_جریان *mz_streamp;

// Returns the version string of miniz.c.
MINIZ_STATIC ثابت حرف *mz_نسخه(فراغ);

#اگر_تعریف_نشده MINIZ_NO_DEFLATE_APIS

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
MINIZ_STATIC صحيح mz_deflateInit(mz_streamp p_جریان, صحيح level);

// mz_deflateInit2() is like mz_deflate(), except with more control:
// Additional parameters:
//   method must be MZ_DEFLATED
//   window_bits must be MZ_DEFAULT_WINDOW_BITS (to wrap the deflate stream with zlib header/adler-32 footer) or -MZ_DEFAULT_WINDOW_BITS (raw deflate/no header or footer)
//   mem_level must be between [1, 9] (it's checked but ignored by miniz.c)
MINIZ_STATIC صحيح mz_deflateInit2(mz_streamp p_جریان, صحيح level, صحيح روش, صحيح پنجره_بیتها, صحيح mem_level, صحيح strategy);

// Quickly resets a compressor without having to reallocate anything. Same as calling mz_deflateEnd() followed by mz_deflateInit()/mz_deflateInit2().
MINIZ_STATIC صحيح mz_deflateReset(mz_streamp p_جریان);

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
MINIZ_STATIC صحيح mz_deflate(mz_streamp p_جریان, صحيح flush);

// mz_deflateEnd() deinitializes a compressor:
// Return values:
//  MZ_OK on success.
//  MZ_STREAM_ERROR if the stream is bogus.
MINIZ_STATIC صحيح mz_deflate_انتها(mz_streamp p_جریان);

// mz_deflateBound() returns a (very) conservative upper bound on the amount of data that could be generated by deflate(), assuming flush is set to only MZ_NO_FLUSH or MZ_FINISH.
MINIZ_STATIC mz_ulong mz_deflateBound(mz_streamp p_جریان, mz_ulong منبع_len);

// Single-call compression functions mz_compress() and mz_compress2():
// Returns MZ_OK on success, or one of the error codes from mz_deflate() on failure.
MINIZ_STATIC صحيح mz_compress(بیعلامت حرف *pDest, mz_ulong *pDest_len, ثابت بیعلامت حرف *p_منبع, mz_ulong منبع_len);
MINIZ_STATIC صحيح mz_compress2(بیعلامت حرف *pDest, mz_ulong *pDest_len, ثابت بیعلامت حرف *p_منبع, mz_ulong منبع_len, صحيح level);

// mz_compressBound() returns a (very) conservative upper bound on the amount of data that could be generated by calling mz_compress().
MINIZ_STATIC mz_ulong mz_compressBound(mz_ulong منبع_len);

#پایان_اگر /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#اگر_تعریف_نشده MINIZ_NO_INFLATE_APIS

// Initializes a decompressor.
MINIZ_STATIC صحيح mz_inflateInit(mz_streamp p_جریان);

// mz_inflateInit2() is like mz_inflateInit() with an additional option that controls the window size and whether or not the stream has been wrapped with a zlib header/footer:
// window_bits must be MZ_DEFAULT_WINDOW_BITS (to parse zlib header/footer) or -MZ_DEFAULT_WINDOW_BITS (raw deflate).
MINIZ_STATIC صحيح mz_inflateInit2(mz_streamp p_جریان, صحيح پنجره_بیتها);

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
MINIZ_STATIC صحيح mz_inflate(mz_streamp p_جریان, صحيح flush);

// Deinitializes a decompressor.
MINIZ_STATIC صحيح mz_inflate_انتها(mz_streamp p_جریان);

// Single-call decompression.
// Returns MZ_OK on success, or one of the error codes from mz_inflate() on failure.
MINIZ_STATIC صحيح mz_uncompress(بیعلامت حرف *pDest, mz_ulong *pDest_len, ثابت بیعلامت حرف *p_منبع, mz_ulong منبع_len);
#پایان_اگر /*#ifndef MINIZ_NO_INFLATE_APIS*/

// Returns a string description of the specified error code, or NULL if the error code is invalid.
MINIZ_STATIC ثابت حرف *mz_error(صحيح err);

// Redefine zlib-compatible names to miniz equivalents, so miniz.c can be used as a drop-in replacement for the subset of zlib that miniz.c supports.
// Define MINIZ_NO_ZLIB_COMPATIBLE_NAMES to disable zlib-compatibility if you use zlib in the same project.
#اگر_تعریف_نشده MINIZ_NO_ZLIB_COMPATIBLE_نامها
  تعريفنوع بیعلامت حرف Byte;
  تعريفنوع بیعلامت صحيح uInt;
  تعريفنوع mz_ulong uLong;
  تعريفنوع Byte Bytef;
  تعريفنوع uInt uIntf;
  تعريفنوع حرف charf;
  تعريفنوع صحيح intf;
  تعريفنوع فراغ *voidpf;
  تعريفنوع uLong uLongf;
  تعريفنوع فراغ *voidp;
  تعريفنوع فراغ *ثابت voidpc;
  #تعریف_کن Z_NULL                0
  #تعریف_کن Z_NO_FLUSH            MZ_NO_FLUSH
  #تعریف_کن Z_PARTIAL_FLUSH       MZ_PARTIAL_FLUSH
  #تعریف_کن Z_SYNC_FLUSH          MZ_SYNC_FLUSH
  #تعریف_کن Z_پر_FLUSH          MZ_پر_FLUSH
  #تعریف_کن Z_پایان              MZ_پایان
  #تعریف_کن Z_بلوک               MZ_بلوک
  #تعریف_کن Z_OK                  MZ_OK
  #تعریف_کن Z_جریان_انتها          MZ_جریان_انتها
  #تعریف_کن Z_NEED_DICT           MZ_NEED_DICT
  #تعریف_کن Z_ERRNO               MZ_ERRNO
  #تعریف_کن Z_جریان_ERROR        MZ_جریان_ERROR
  #تعریف_کن Z_داده_ERROR          MZ_داده_ERROR
  #تعریف_کن Z_MEM_ERROR           MZ_MEM_ERROR
  #تعریف_کن Z_BUF_ERROR           MZ_BUF_ERROR
  #تعریف_کن Z_نسخه_ERROR       MZ_نسخه_ERROR
  #تعریف_کن Z_PARAM_ERROR         MZ_PARAM_ERROR
  #تعریف_کن Z_NO_COMPRESSION      MZ_NO_COMPRESSION
  #تعریف_کن Z_بهترین_سرعت          MZ_بهترین_سرعت
  #تعریف_کن Z_بهترین_COMPRESSION    MZ_بهترین_COMPRESSION
  #تعریف_کن Z_DEFAULT_COMPRESSION MZ_DEFAULT_COMPRESSION
  #تعریف_کن Z_DEFAULT_STRATEGY    MZ_DEFAULT_STRATEGY
  #تعریف_کن Z_FILTERED            MZ_FILTERED
  #تعریف_کن Z_HUFFMAN_ONLY        MZ_HUFFMAN_ONLY
  #تعریف_کن Z_RLE                 MZ_RLE
  #تعریف_کن Z_FIXED               MZ_FIXED
  #تعریف_کن Z_DEFLATED            MZ_DEFLATED
  #تعریف_کن Z_DEFAULT_پنجره_بیتها MZ_DEFAULT_پنجره_بیتها
  #تعریف_کن alloc_func            mz_alloc_func
  #تعریف_کن free_func             mz_free_func
  #تعریف_کن داخلی_state        mz_داخلی_state
  #تعریف_کن z_جریان              mz_جریان
#اگر_تعریف_نشده MINIZ_NO_DEFLATE_APIS
  #تعریف_کن deflateInit           mz_deflateInit
  #تعریف_کن deflateInit2          mz_deflateInit2
  #تعریف_کن deflateReset          mz_deflateReset
  #تعریف_کن deflate               mz_deflate
  #تعریف_کن deflate_انتها            mz_deflate_انتها
  #تعریف_کن deflateBound          mz_deflateBound
  #تعریف_کن compress              mz_compress
  #تعریف_کن compress2             mz_compress2
  #تعریف_کن compressBound         mz_compressBound
#پایان_اگر /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#اگر_تعریف_نشده MINIZ_NO_INFLATE_APIS
  #تعریف_کن inflateInit           mz_inflateInit
  #تعریف_کن inflateInit2          mz_inflateInit2
  #تعریف_کن inflate               mz_inflate
  #تعریف_کن inflate_انتها            mz_inflate_انتها
  #تعریف_کن uncompress            mz_uncompress
#پایان_اگر /*#ifndef MINIZ_NO_INFLATE_APIS*/
  #تعریف_کن بررسی_چرخهای_32                 mz_بررسی_چرخهای_32
  #تعریف_کن adler32               mz_adler32
  #تعریف_کن MAX_WBITS             15
  #تعریف_کن MAX_MEM_LEVEL         9
  #تعریف_کن zError                mz_error
  #تعریف_کن ZLIB_نسخه          MZ_نسخه
  #تعریف_کن ZLIB_VERNUM           MZ_VERNUM
  #تعریف_کن ZLIB_VER_MAJOR        MZ_VER_MAJOR
  #تعریف_کن ZLIB_VER_MINOR        MZ_VER_MINOR
  #تعریف_کن ZLIB_VER_REVISION     MZ_VER_REVISION
  #تعریف_کن ZLIB_VER_SUBREVISION  MZ_VER_SUBREVISION
  #تعریف_کن zlib_نسخه           mz_نسخه
  #تعریف_کن zlib_نسخه_2          mz_نسخه()
#پایان_اگر // #ifndef MINIZ_NO_ZLIB_COMPATIBLE_NAMES

#پایان_اگر // MINIZ_NO_ZLIB_APIS

// ------------------- Types and macros

تعريفنوع بیعلامت حرف mz_uint8;
تعريفنوع علامتدار کوتاه mz_int16;
تعريفنوع بیعلامت کوتاه mz_uint16;
تعريفنوع بیعلامت صحيح mz_uint32;
تعريفنوع بیعلامت صحيح mz_uint;
تعريفنوع دراز دراز mz_int64;
تعريفنوع بیعلامت دراز دراز mz_uint64;
تعريفنوع صحيح mz_bool;

#تعریف_کن MZ_FALSE (0)
#تعریف_کن MZ_TRUE (1)

// An attempt to work around MSVC's spammy "warning C4127: conditional expression is constant" message.
#اگر_تعریف_شده _MSC_VER
   #تعریف_کن MZ_MACRO_انتها طالما (0, 0)
#وإلا
   #تعریف_کن MZ_MACRO_انتها طالما (0)
#پایان_اگر

// ------------------- ZIP archive reading/writing

#اگر_تعریف_نشده MINIZ_NO_ARCHIVE_APIS

تعداد
{
  MZ_ZIP_MAX_IO_BUF_اندازه = 64*1024,
  MZ_ZIP_MAX_ARCHIVE_FILENAME_اندازه = 260,
  MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_اندازه = 256
};

تعريفنوع بنية
{
  mz_uint32 m_file_شاخص;
  mz_uint32 m_central_dir_ofs;
  mz_uint16 m_نسخه_made_by;
  mz_uint16 m_نسخه_needed;
  mz_uint16 m_بیت_flag;
  mz_uint16 m_روش;
#اگر_تعریف_نشده MINIZ_NO_زمان
  زمان_t m_زمان;
#پایان_اگر
  mz_uint32 m_بررسی_چرخهای_32;
  mz_uint64 m_comp_اندازه;
  mz_uint64 m_uncomp_اندازه;
  mz_uint16 m_داخلی_attr;
  mz_uint32 m_external_attr;
  mz_uint64 m_local_سرآیند_ofs;
  mz_uint32 m_comment_اندازه;
  حرف m_filename[MZ_ZIP_MAX_ARCHIVE_FILENAME_اندازه];
  حرف m_comment[MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_اندازه];
} mz_zip_archive_file_stat;

تعريفنوع size_t (*mz_file_read_func)(فراغ *pOpaque, mz_uint64 file_ofs, فراغ *pBuf, size_t n);
تعريفنوع size_t (*mz_file_write_func)(فراغ *pOpaque, mz_uint64 file_ofs, ثابت فراغ *pBuf, size_t n);

بنية mz_zip_داخلی_state_برچسب;
تعريفنوع بنية mz_zip_داخلی_state_برچسب mz_zip_داخلی_state;

تعريفنوع تعداد
{
  MZ_ZIP_نما_INVALID = 0,
  MZ_ZIP_نما_READING = 1,
  MZ_ZIP_نما_WRITING = 2,
  MZ_ZIP_نما_WRITING_HAS_BEEN_FINALIZED = 3
} mz_zip_نما;

تعريفنوع بنية mz_zip_archive_برچسب
{
  mz_uint64 m_archive_اندازه;
  mz_uint64 m_central_directory_file_ofs;
  mz_uint m_مجموع_files;
  mz_zip_نما m_zip_نما;

  mz_uint m_file_جابه_جایی_alignment;

  mz_alloc_func m_pAlloc;
  mz_free_func m_pFree;
  mz_realloc_func m_pRealloc;
  فراغ *m_pAlloc_opaque;

  mz_file_read_func m_pRead;
  mz_file_write_func m_pWrite;
  فراغ *m_pIO_opaque;

  mz_zip_داخلی_state *m_pState;

} mz_zip_archive;

تعريفنوع تعداد
{
  MZ_ZIP_FLAG_CASE_SENSITIVE                = 0x0100,
  MZ_ZIP_FLAG_IGNORE_مسیر                   = 0x0200,
  MZ_ZIP_FLAG_COMPRESSED_داده               = 0x0400,
  MZ_ZIP_FLAG_DO_NOT_مرتب_سازی_CENTRAL_DIRECTORY = 0x0800
} mz_zip_flags;

// ZIP archive reading

// Inits a ZIP archive reader.
// These functions read and validate the archive's central directory.
MINIZ_STATIC mz_bool mz_zip_reader_init(mz_zip_archive *pZip, mz_uint64 اندازه, mz_uint32 flags);
MINIZ_STATIC mz_bool mz_zip_reader_init_mem(mz_zip_archive *pZip, ثابت فراغ *pMem, size_t اندازه, mz_uint32 flags);

#اگر_تعریف_نشده MINIZ_NO_STDIO
MINIZ_STATIC mz_bool mz_zip_reader_init_file(mz_zip_archive *pZip, ثابت حرف *pFilename, mz_uint32 flags);
#پایان_اگر

// Returns the total number of files in the archive.
MINIZ_STATIC mz_uint mz_zip_reader_get_رقم_files(mz_zip_archive *pZip);

// Returns detailed information about an archive file entry.
MINIZ_STATIC mz_bool mz_zip_reader_file_stat(mz_zip_archive *pZip, mz_uint file_شاخص, mz_zip_archive_file_stat *pStat);

// Determines if an archive file entry is a directory entry.
MINIZ_STATIC mz_bool mz_zip_reader_is_file_a_directory(mz_zip_archive *pZip, mz_uint file_شاخص);
MINIZ_STATIC mz_bool mz_zip_reader_is_file_encrypted(mz_zip_archive *pZip, mz_uint file_شاخص);

// Retrieves the filename of an archive file entry.
// Returns the number of bytes written to pFilename, or if filename_buf_size is 0 this function returns the number of bytes needed to fully store the filename.
MINIZ_STATIC mz_uint mz_zip_reader_get_filename(mz_zip_archive *pZip, mz_uint file_شاخص, حرف *pFilename, mz_uint filename_buf_اندازه);

// Attempts to locates a file in the archive's central directory.
// Valid flags: MZ_ZIP_FLAG_CASE_SENSITIVE, MZ_ZIP_FLAG_IGNORE_PATH
// Returns -1 if the file cannot be found.
MINIZ_STATIC صحيح mz_zip_reader_locate_file(mz_zip_archive *pZip, ثابت حرف *pName, ثابت حرف *pComment, mz_uint flags);

// Extracts a archive file to a memory buffer using no memory allocation.
MINIZ_STATIC mz_bool mz_zip_reader_استخراج_مقصد_mem_no_alloc(mz_zip_archive *pZip, mz_uint file_شاخص, فراغ *pBuf, size_t buf_اندازه_2, mz_uint flags, فراغ *pUser_read_buf, size_t user_read_buf_اندازه);
MINIZ_STATIC mz_bool mz_zip_reader_استخراج_file_مقصد_mem_no_alloc(mz_zip_archive *pZip, ثابت حرف *pFilename, فراغ *pBuf, size_t buf_اندازه_2, mz_uint flags, فراغ *pUser_read_buf, size_t user_read_buf_اندازه);

// Extracts a archive file to a memory buffer.
MINIZ_STATIC mz_bool mz_zip_reader_استخراج_مقصد_mem(mz_zip_archive *pZip, mz_uint file_شاخص, فراغ *pBuf, size_t buf_اندازه_2, mz_uint flags);
MINIZ_STATIC mz_bool mz_zip_reader_استخراج_file_مقصد_mem(mz_zip_archive *pZip, ثابت حرف *pFilename, فراغ *pBuf, size_t buf_اندازه_2, mz_uint flags);

// Extracts a archive file to a dynamically allocated heap buffer.
MINIZ_STATIC فراغ *mz_zip_reader_استخراج_مقصد_انباشته(mz_zip_archive *pZip, mz_uint file_شاخص, size_t *p_اندازه, mz_uint flags);
MINIZ_STATIC فراغ *mz_zip_reader_استخراج_file_مقصد_انباشته(mz_zip_archive *pZip, ثابت حرف *pFilename, size_t *p_اندازه, mz_uint flags);

// Extracts a archive file using a callback function to output the file's data.
MINIZ_STATIC mz_bool mz_zip_reader_استخراج_مقصد_callback(mz_zip_archive *pZip, mz_uint file_شاخص, mz_file_write_func pCallback, فراغ *pOpaque, mz_uint flags);
MINIZ_STATIC mz_bool mz_zip_reader_استخراج_file_مقصد_callback(mz_zip_archive *pZip, ثابت حرف *pFilename, mz_file_write_func pCallback, فراغ *pOpaque, mz_uint flags);

#اگر_تعریف_نشده MINIZ_NO_STDIO
// Extracts a archive file to a disk file and sets its last accessed and modified times.
// This function only extracts files, not archive directory records.
MINIZ_STATIC mz_bool mz_zip_reader_استخراج_مقصد_file(mz_zip_archive *pZip, mz_uint file_شاخص, ثابت حرف *pDst_filename, mz_uint flags);
MINIZ_STATIC mz_bool mz_zip_reader_استخراج_file_مقصد_file(mz_zip_archive *pZip, ثابت حرف *pArchive_filename, ثابت حرف *pDst_filename, mz_uint flags);
#پایان_اگر

// Ends archive reading, freeing all allocations, and closing the input archive file if mz_zip_reader_init_file() was used.
MINIZ_STATIC mz_bool mz_zip_reader_انتها(mz_zip_archive *pZip);

// ZIP archive writing

#اگر_تعریف_نشده MINIZ_NO_ARCHIVE_WRITING_APIS

// Inits a ZIP archive writer.
MINIZ_STATIC mz_bool mz_zip_writer_init(mz_zip_archive *pZip, mz_uint64 existing_اندازه);
MINIZ_STATIC mz_bool mz_zip_writer_init_انباشته(mz_zip_archive *pZip, size_t اندازه_مقصد_reserve_at_beginning, size_t initial_تخصیص_اندازه);

#اگر_تعریف_نشده MINIZ_NO_STDIO
MINIZ_STATIC mz_bool mz_zip_writer_init_file(mz_zip_archive *pZip, ثابت حرف *pFilename, mz_uint64 اندازه_مقصد_reserve_at_beginning);
#پایان_اگر

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
MINIZ_STATIC mz_bool mz_zip_writer_جمع_کن_mem(mz_zip_archive *pZip, ثابت حرف *pArchive_name, ثابت فراغ *pBuf, size_t buf_اندازه_2, mz_uint level_and_flags);
MINIZ_STATIC mz_bool mz_zip_writer_جمع_کن_mem_ex(mz_zip_archive *pZip, ثابت حرف *pArchive_name, ثابت فراغ *pBuf, size_t buf_اندازه_2, ثابت فراغ *pComment, mz_uint16 comment_اندازه, mz_uint level_and_flags, mz_uint64 uncomp_اندازه, mz_uint32 uncomp_بررسی_چرخهای_32);

#اگر_تعریف_نشده MINIZ_NO_STDIO
// Adds the contents of a disk file to an archive. This function also records the disk file's modified time into the archive.
// level_and_flags - compression level (0-10, see MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or just set to MZ_DEFAULT_COMPRESSION.
MINIZ_STATIC mz_bool mz_zip_writer_جمع_کن_file(mz_zip_archive *pZip, ثابت حرف *pArchive_name, ثابت حرف *pSrc_filename, ثابت فراغ *pComment, mz_uint16 comment_اندازه, mz_uint level_and_flags);
#پایان_اگر

// Adds a file to an archive by fully cloning the data from another archive.
// This function fully clones the source file's compressed data (no recompression), along with its full filename, extra data, and comment fields.
MINIZ_STATIC mz_bool mz_zip_writer_جمع_کن_from_zip_reader(mz_zip_archive *pZip, mz_zip_archive *p_منبع_zip, mz_uint file_شاخص);

// Finalizes the archive by writing the central directory records followed by the end of central directory record.
// After an archive is finalized, the only valid call on the mz_zip_archive struct is mz_zip_writer_end().
// An archive must be manually finalized by calling this function for it to be valid.
MINIZ_STATIC mz_bool mz_zip_writer_finalize_archive(mz_zip_archive *pZip);
MINIZ_STATIC mz_bool mz_zip_writer_finalize_انباشته_archive(mz_zip_archive *pZip, فراغ **pBuf, size_t *p_اندازه);

// Ends archive writing, freeing all allocations, and closing the output file if mz_zip_writer_init_file() was used.
// Note for the archive to be valid, it must have been finalized before ending.
MINIZ_STATIC mz_bool mz_zip_writer_انتها(mz_zip_archive *pZip);

// Misc. high-level helper functions:

// mz_zip_add_mem_to_archive_file_in_place() efficiently (but not atomically) appends a memory blob to a ZIP archive.
// level_and_flags - compression level (0-10, see MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or just set to MZ_DEFAULT_COMPRESSION.
MINIZ_STATIC mz_bool mz_zip_جمع_کن_mem_مقصد_archive_file_درون_قراربده(ثابت حرف *pZip_filename, ثابت حرف *pArchive_name, ثابت فراغ *pBuf, size_t buf_اندازه_2, ثابت فراغ *pComment, mz_uint16 comment_اندازه, mz_uint level_and_flags);

// Reads a single file from an archive into a heap block.
// Returns NULL on failure.
MINIZ_STATIC فراغ *mz_zip_استخراج_archive_file_مقصد_انباشته(ثابت حرف *pZip_filename, ثابت حرف *pArchive_name, size_t *p_اندازه, mz_uint zip_flags);

#پایان_اگر // #ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

#پایان_اگر // #ifndef MINIZ_NO_ARCHIVE_APIS

// ------------------- Low-level Decompression API Definitions
#اگر_تعریف_نشده MINIZ_NO_INFLATE_APIS

// Decompression flags used by tinfl_decompress().
// TINFL_FLAG_PARSE_ZLIB_HEADER: If set, the input has a valid zlib header and ends with an adler32 checksum (it's a valid zlib stream). Otherwise, the input is a raw deflate stream.
// TINFL_FLAG_HAS_MORE_INPUT: If set, there are more input bytes available beyond the end of the supplied input buffer. If clear, the input buffer contains all remaining input.
// TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF: If set, the output buffer is large enough to hold the entire decompressed stream. If clear, the output buffer is at least the size of the dictionary (typically 32KB).
// TINFL_FLAG_COMPUTE_ADLER32: Force adler-32 checksum computation of the decompressed bytes.
تعداد
{
  TINFL_FLAG_PARSE_ZLIB_سرآیند = 1,
  TINFL_FLAG_HAS_بیشتر_درون_داد = 2,
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
MINIZ_STATIC فراغ *tinfl_decompress_mem_مقصد_انباشته(ثابت فراغ *pSrc_buf, size_t src_buf_len, size_t *p_بیرون_len, صحيح flags);

// tinfl_decompress_mem_to_mem() decompresses a block in memory to another block in memory.
// Returns TINFL_DECOMPRESS_MEM_TO_MEM_FAILED on failure, or the number of bytes written on success.
#تعریف_کن TINFL_DECOMPRESS_MEM_مقصد_MEM_FAILED ((size_t)(-1))
MINIZ_STATIC size_t tinfl_decompress_mem_مقصد_mem(فراغ *p_بیرون_buf, size_t بیرون_buf_len, ثابت فراغ *pSrc_buf, size_t src_buf_len, صحيح flags);

// tinfl_decompress_mem_to_callback() decompresses a block in memory to an internal 32KB buffer, and a user provided callback function will be called to flush the buffer.
// Returns 1 on success or 0 on failure.
تعريفنوع صحيح (*tinfl_put_buf_func_ptr)(ثابت فراغ* pBuf, صحيح len, فراغ *pUser);
MINIZ_STATIC صحيح tinfl_decompress_mem_مقصد_callback(ثابت فراغ *p_درون_buf, size_t *p_درون_buf_اندازه, tinfl_put_buf_func_ptr pPut_buf_func, فراغ *pPut_buf_user, صحيح flags);

بنية tinfl_decompressor_برچسب; تعريفنوع بنية tinfl_decompressor_برچسب tinfl_decompressor;

// Max size of LZ dictionary.
#تعریف_کن TINFL_LZ_DICT_اندازه 32768

// Return status.
تعريفنوع تعداد
{
  TINFL_وضعیت_BAD_PARAM = -3,
  TINFL_وضعیت_ADLER32_MISMATCH = -2,
  TINFL_وضعیت_FAILED = -1,
  TINFL_وضعیت_انجامشده = 0,
  TINFL_وضعیت_NEEDS_بیشتر_درون_داد = 1,
  TINFL_وضعیت_HAS_بیشتر_OUTPUT = 2
} tinfl_وضعیت;

// Initializes the decompressor to its initial state.
#تعریف_کن tinfl_init(r) افعل { (r)->m_state = 0; } MZ_MACRO_انتها
#تعریف_کن tinfl_get_adler32(r) (r)->m_check_adler32

// Main low-level decompressor coroutine function. This is the only function actually needed for decompression. All the other functions are just high-level helpers for improved usability.
// This is a universal API, i.e. it can be used as a building block to build any desired higher level decompression API. In the limit case, it can be called once per every byte input or output.
MINIZ_STATIC tinfl_وضعیت tinfl_decompress(tinfl_decompressor *r, ثابت mz_uint8 *p_درون_buf_بعدی, size_t *p_درون_buf_اندازه, mz_uint8 *p_بیرون_buf_شروع, mz_uint8 *p_بیرون_buf_بعدی, size_t *p_بیرون_buf_اندازه, ثابت mz_uint32 decomp_flags);

// Internal/private bits follow.
تعداد
{
  TINFL_MAX_HUFF_TABLES = 3, TINFL_MAX_HUFF_SYMBOLS_0 = 288, TINFL_MAX_HUFF_SYMBOLS_1 = 32, TINFL_MAX_HUFF_SYMBOLS_2 = 19,
  TINFL_FAST_LOOKUP_بیتها = 10, TINFL_FAST_LOOKUP_اندازه = 1 << TINFL_FAST_LOOKUP_بیتها
};

تعريفنوع بنية
{
  mz_uint8 m_کد_اندازه[TINFL_MAX_HUFF_SYMBOLS_0];
  mz_int16 m_look_به_بالا[TINFL_FAST_LOOKUP_اندازه], m_درخت[TINFL_MAX_HUFF_SYMBOLS_0 * 2];
} tinfl_huff_جدول;

#إذا MINIZ_HAS_64_بیت_REGISTERS
  #تعریف_کن TINFL_USE_64_بیت_BITBUF 1
#پایان_اگر

#إذا TINFL_USE_64_بیت_BITBUF
  تعريفنوع mz_uint64 tinfl_بیت_buf_t;
  #تعریف_کن TINFL_BITBUF_اندازه (64)
#وإلا
  تعريفنوع mz_uint32 tinfl_بیت_buf_t;
  #تعریف_کن TINFL_BITBUF_اندازه (32)
#پایان_اگر

بنية tinfl_decompressor_برچسب
{
  mz_uint32 m_state, m_رقم_بیتها, m_zhdr0, m_zhdr1, m_z_adler32, m_final, m_type, m_check_adler32, m_dist, m_counter, m_رقم_extra, m_جدول_sizes[TINFL_MAX_HUFF_TABLES];
  tinfl_بیت_buf_t m_بیت_buf;
  size_t m_dist_from_بیرون_buf_شروع;
  tinfl_huff_جدول m_tables[TINFL_MAX_HUFF_TABLES];
  mz_uint8 m_raw_سرآیند[4], m_len_codes[TINFL_MAX_HUFF_SYMBOLS_0 + TINFL_MAX_HUFF_SYMBOLS_1 + 137];
};
#پایان_اگر /*#ifndef MINIZ_NO_INFLATE_APIS*/

// ------------------- Low-level Compression API Definitions
#اگر_تعریف_نشده MINIZ_NO_DEFLATE_APIS

// Set TDEFL_LESS_MEMORY to 1 to use less memory (compression will be slightly slower, and raw/dynamic blocks will be output more frequently).
#تعریف_کن TDEFL_LESS_حافظه 0

// tdefl_init() compression flags logically OR'd together (low 12 bits contain the max. number of probes per dictionary search):
// TDEFL_DEFAULT_MAX_PROBES: The compressor defaults to 128 dictionary probes per dictionary search. 0=Huffman only, 1=Huffman+LZ (fastest/crap compression), 4095=Huffman+LZ (slowest/best compression).
تعداد
{
  TDEFL_HUFFMAN_ONLY = 0, TDEFL_DEFAULT_MAX_PROBES = 128, TDEFL_MAX_PROBES_ماسک = 0xFFF
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
  TDEFL_WRITE_ZLIB_سرآیند             = 0x01000,
  TDEFL_COMPUTE_ADLER32               = 0x02000,
  TDEFL_GREEDY_PARSING_FLAG           = 0x04000,
  TDEFL_NONDETERMINISTIC_PARSING_FLAG = 0x08000,
  TDEFL_RLE_MATCHES                   = 0x10000,
  TDEFL_FILTER_MATCHES                = 0x20000,
  TDEFL_FORCE_ALL_STATIC_بلوکها       = 0x40000,
  TDEFL_FORCE_ALL_RAW_بلوکها          = 0x80000
};

#اگر_تعریف_نشده MINIZ_SDL_NOUNUSED
// High level compression functions:
// tdefl_compress_mem_to_heap() compresses a block in memory to a heap block allocated via malloc().
// On entry:
//  pSrc_buf, src_buf_len: Pointer and size of source block to compress.
//  flags: The max match finder probes (default is 128) logically OR'd against the above flags. Higher probes are slower but improve compression.
// On return:
//  Function returns a pointer to the compressed data, or NULL on failure.
//  *pOut_len will be set to the compressed data's size, which could be larger than src_buf_len on uncompressible data.
//  The caller must free() the returned block when it's no longer needed.
MINIZ_STATIC فراغ *tdefl_compress_mem_مقصد_انباشته(ثابت فراغ *pSrc_buf, size_t src_buf_len, size_t *p_بیرون_len, صحيح flags);

// tdefl_compress_mem_to_mem() compresses a block in memory to another block in memory.
// Returns 0 on failure.
MINIZ_STATIC size_t tdefl_compress_mem_مقصد_mem(فراغ *p_بیرون_buf, size_t بیرون_buf_len, ثابت فراغ *pSrc_buf, size_t src_buf_len, صحيح flags);
#پایان_اگر /* MINIZ_SDL_NOUNUSED */

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
MINIZ_STATIC فراغ *tdefl_write_image_مقصد_png_file_درون_حافظه_ex(ثابت فراغ *pImage, صحيح w, صحيح h, صحيح رقم_chans, صحيح bpl, size_t *p_Len_بیرون, mz_uint level, mz_bool flip, mz_uint8 *plte, صحيح plte_اندازه, mz_uint8 *trns, صحيح trns_اندازه);
#اگر_تعریف_نشده MINIZ_SDL_NOUNUSED
MINIZ_STATIC فراغ *tdefl_write_image_مقصد_png_file_درون_حافظه(ثابت فراغ *pImage, صحيح w, صحيح h, صحيح رقم_chans, صحيح bpl, size_t *p_Len_بیرون);
#پایان_اگر

// Output stream interface. The compressor uses this interface to write compressed data. It'll typically be called TDEFL_OUT_BUF_SIZE at a time.
تعريفنوع mz_bool (*tdefl_put_buf_func_ptr)(ثابت فراغ* pBuf, صحيح len, فراغ *pUser);

#اگر_تعریف_نشده MINIZ_SDL_NOUNUSED
// tdefl_compress_mem_to_output() compresses a block to an output stream. The above helpers use this function internally.
MINIZ_STATIC mz_bool tdefl_compress_mem_مقصد_output(ثابت فراغ *pBuf, size_t buf_len, tdefl_put_buf_func_ptr pPut_buf_func, فراغ *pPut_buf_user, صحيح flags);
#پایان_اگر

//enum { TDEFL_MAX_HUFF_TABLES = 3, TDEFL_MAX_HUFF_SYMBOLS_0 = 288, TDEFL_MAX_HUFF_SYMBOLS_1 = 32, TDEFL_MAX_HUFF_SYMBOLS_2 = 19, TDEFL_LZ_DICT_SIZE = 32768, TDEFL_LZ_DICT_SIZE_MASK = TDEFL_LZ_DICT_SIZE - 1, TDEFL_MIN_MATCH_LEN = 3, TDEFL_MAX_MATCH_LEN = 258 };
#تعریف_کن TDEFL_MAX_HUFF_TABLES	3
#تعریف_کن TDEFL_MAX_HUFF_SYMBOLS_0 288
#تعریف_کن TDEFL_MAX_HUFF_SYMBOLS_1 32
#تعریف_کن TDEFL_MAX_HUFF_SYMBOLS_2 19
#تعریف_کن TDEFL_LZ_DICT_اندازه 32768
#تعریف_کن TDEFL_LZ_DICT_اندازه_ماسک	( TDEFL_LZ_DICT_اندازه - 1 )
#تعریف_کن TDEFL_MIN_تطابق_LEN	3
#تعریف_کن TDEFL_MAX_تطابق_LEN 258

// TDEFL_OUT_BUF_SIZE MUST be large enough to hold a single entire compressed output block (using static/fixed Huffman codes).
#إذا TDEFL_LESS_حافظه
تعداد { TDEFL_LZ_کد_BUF_اندازه = 24 * 1024, TDEFL_بیرون_BUF_اندازه = (TDEFL_LZ_کد_BUF_اندازه * 13 ) / 10, TDEFL_MAX_HUFF_SYMBOLS = 288, TDEFL_LZ_HASH_بیتها = 12, TDEFL_LEVEL1_HASH_اندازه_ماسک = 4095, TDEFL_LZ_HASH_لغزش = (TDEFL_LZ_HASH_بیتها + 2) / 3, TDEFL_LZ_HASH_اندازه = 1 << TDEFL_LZ_HASH_بیتها };
#وإلا
تعداد { TDEFL_LZ_کد_BUF_اندازه = 64 * 1024, TDEFL_بیرون_BUF_اندازه = (TDEFL_LZ_کد_BUF_اندازه * 13 ) / 10, TDEFL_MAX_HUFF_SYMBOLS = 288, TDEFL_LZ_HASH_بیتها = 15, TDEFL_LEVEL1_HASH_اندازه_ماسک = 4095, TDEFL_LZ_HASH_لغزش = (TDEFL_LZ_HASH_بیتها + 2) / 3, TDEFL_LZ_HASH_اندازه = 1 << TDEFL_LZ_HASH_بیتها };
#پایان_اگر

// The low-level tdefl functions below may be used directly if the above helper functions aren't flexible enough. The low-level functions don't make any heap allocations, unlike the above helper functions.
تعريفنوع تعداد
{
  TDEFL_وضعیت_BAD_PARAM = -2,
  TDEFL_وضعیت_PUT_BUF_FAILED = -1,
  TDEFL_وضعیت_OKAY = 0,
  TDEFL_وضعیت_انجامشده = 1,
} tdefl_وضعیت;

// Must map to MZ_NO_FLUSH, MZ_SYNC_FLUSH, etc. enums
تعريفنوع تعداد
{
  TDEFL_NO_FLUSH = 0,
  TDEFL_SYNC_FLUSH = 2,
  TDEFL_پر_FLUSH = 3,
  TDEFL_پایان = 4
} tdefl_flush;

// tdefl's compression state structure.
تعريفنوع بنية
{
  tdefl_put_buf_func_ptr m_pPut_buf_func;
  فراغ *m_pPut_buf_user;
  mz_uint m_flags, m_max_probes[2];
  صحيح m_greedy_parsing;
  mz_uint m_adler32, m_lookahead_pos, m_lookahead_اندازه, m_dict_اندازه;
  mz_uint8 *m_p_LZ_کد_buf, *m_pLZ_flags, *m_pOutput_buf, *m_p_Output_buf_انتها;
  mz_uint m_رقم_flags_چپ, m_مجموع_lz_بایتها, m_lz_کد_buf_dict_pos, m_بیتها_درون, m_بیت_میانگیر;
  mz_uint m_saved_تطابق_dist, m_saved_تطابق_len, m_saved_lit, m_output_flush_ofs, m_output_flush_مانده, m_پایانیافته, m_بلوک_شاخص, m_میخواهد_مقصد_پایان;
  tdefl_وضعیت m_prev_return_وضعیت;
  ثابت فراغ *m_p_درون_buf;
  فراغ *m_p_بیرون_buf;
  size_t *m_p_درون_buf_اندازه, *m_p_بیرون_buf_اندازه;
  tdefl_flush m_flush;
  ثابت mz_uint8 *m_pSrc;
  size_t m_src_buf_چپ, m_بیرون_buf_ofs;
  mz_uint8 m_dict[TDEFL_LZ_DICT_اندازه + TDEFL_MAX_تطابق_LEN - 1];
  mz_uint16 m_huff_شمار[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint16 m_huff_codes[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint8 m_huff_کد_sizes[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint8 m_lz_کد_buf[TDEFL_LZ_کد_BUF_اندازه];
  mz_uint16 m_بعدی[TDEFL_LZ_DICT_اندازه];
  mz_uint16 m_hash[TDEFL_LZ_HASH_اندازه];
  mz_uint8 m_output_buf[TDEFL_بیرون_BUF_اندازه];
} tdefl_compressor;

// Initializes the compressor.
// There is no corresponding deinit() function because the tdefl API's do not dynamically allocate memory.
// pBut_buf_func: If NULL, output data will be supplied to the specified callback. In this case, the user should call the tdefl_compress_buffer() API for compression.
// If pBut_buf_func is NULL the user should always call the tdefl_compress() API.
// flags: See the above enums (TDEFL_HUFFMAN_ONLY, TDEFL_WRITE_ZLIB_HEADER, etc.)
MINIZ_STATIC tdefl_وضعیت tdefl_init(tdefl_compressor *d, tdefl_put_buf_func_ptr pPut_buf_func, فراغ *pPut_buf_user, صحيح flags);

// Compresses a block of data, consuming as much of the specified input buffer as possible, and writing as much compressed data to the specified output buffer as possible.
MINIZ_STATIC tdefl_وضعیت tdefl_compress(tdefl_compressor *d, ثابت فراغ *p_درون_buf, size_t *p_درون_buf_اندازه, فراغ *p_بیرون_buf, size_t *p_بیرون_buf_اندازه, tdefl_flush flush);

// tdefl_compress_buffer() is only usable when the tdefl_init() is called with a non-NULL tdefl_put_buf_func_ptr.
// tdefl_compress_buffer() always consumes the entire input buffer.
MINIZ_STATIC tdefl_وضعیت tdefl_compress_میانگیر(tdefl_compressor *d, ثابت فراغ *p_درون_buf, size_t درون_buf_اندازه, tdefl_flush flush);

#اگر_تعریف_نشده MINIZ_SDL_NOUNUSED
MINIZ_STATIC tdefl_وضعیت tdefl_get_prev_return_وضعیت(tdefl_compressor *d);
MINIZ_STATIC mz_uint32 tdefl_get_adler32(tdefl_compressor *d);
#پایان_اگر

// Can't use tdefl_create_comp_flags_from_zip_params if MINIZ_NO_ZLIB_APIS isn't defined, because it uses some of its macros.
#اگر_تعریف_نشده MINIZ_NO_ZLIB_APIS
// Create tdefl_compress() flags given zlib-style compression parameters.
// level may range from [0,10] (where 10 is absolute max compression, but may be much slower on some files)
// window_bits may be -15 (raw deflate) or 15 (zlib)
// strategy may be either MZ_DEFAULT_STRATEGY, MZ_FILTERED, MZ_HUFFMAN_ONLY, MZ_RLE, or MZ_FIXED
MINIZ_STATIC mz_uint tdefl_create_comp_flags_from_zip_params(صحيح level, صحيح پنجره_بیتها, صحيح strategy);
#پایان_اگر // #ifndef MINIZ_NO_ZLIB_APIS

#پایان_اگر /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#پایان_اگر // MINIZ_HEADER_INCLUDED

// ------------------- End of Header: Implementation follows. (If you only want the header, define MINIZ_HEADER_FILE_ONLY.)

#اگر_تعریف_نشده MINIZ_سرآیند_FILE_ONLY

#اگر_تعریف_شده _MSC_VER
#رهنمود warning (افزودن)
#رهنمود warning (disable:4505) // unreferenced local function has been removed
#پایان_اگر

تعريفنوع بیعلامت حرف mz_validate_uint16[حجم(mz_uint16)==2 ? 1 : -1];
تعريفنوع بیعلامت حرف mz_validate_uint32[حجم(mz_uint32)==4 ? 1 : -1];
تعريفنوع بیعلامت حرف mz_validate_uint64[حجم(mz_uint64)==8 ? 1 : -1];

/*#include <string.h>*/

#اگر_تعریف_نشده MZ_ASSERT
#ضمن <assert.h>
#تعریف_کن MZ_ASSERT(x) أكد(x)
#پایان_اگر

#اگر_تعریف_شده MINIZ_NO_MALLOC
  #تعریف_کن MZ_MALLOC(x) عدم
  #تعریف_کن MZ_FREE(x) (فراغ)x, ((فراغ)0)
  #تعریف_کن MZ_REALLOC(p, x) عدم
#وإلاإذا defined(MINIZ_SDL_MALLOC)
  #تعریف_کن MZ_MALLOC(x) SDL_malloc(x)
  #تعریف_کن MZ_FREE(x) SDL_free(x)
  #تعریف_کن MZ_REALLOC(p, x) SDL_realloc(p, x)
#وإلا
  #تعریف_کن MZ_MALLOC(x) حافظه_بده(x)
  #تعریف_کن MZ_FREE(x) حرر(x)
  #تعریف_کن MZ_REALLOC(p, x) realloc(p, x)
#پایان_اگر

#تعریف_کن MZ_MAX(a,b) (((a)>(b))?(a):(b))
#تعریف_کن MZ_MIN(a,b) (((a)<(b))?(a):(b))
#تعریف_کن MZ_CLEAR_OBJ(obj) memset(&(obj), 0, حجم(obj))
#تعریف_کن MZ_CLEAR_ARR(obj) memset((obj), 0, حجم(obj))
#تعریف_کن MZ_CLEAR_PTR(obj) memset((obj), 0, حجم(*obj))

#إذا MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  #تعریف_کن MZ_READ_LE16(p) *((ثابت mz_uint16 *)(p))
  #تعریف_کن MZ_READ_LE32(p) *((ثابت mz_uint32 *)(p))
#وإلا
  #تعریف_کن MZ_READ_LE16(p) ((mz_uint32)(((ثابت mz_uint8 *)(p))[0]) | ((mz_uint32)(((ثابت mz_uint8 *)(p))[1]) << 8U))
  #تعریف_کن MZ_READ_LE32(p) ((mz_uint32)(((ثابت mz_uint8 *)(p))[0]) | ((mz_uint32)(((ثابت mz_uint8 *)(p))[1]) << 8U) | ((mz_uint32)(((ثابت mz_uint8 *)(p))[2]) << 16U) | ((mz_uint32)(((ثابت mz_uint8 *)(p))[3]) << 24U))
#پایان_اگر

#اگر_تعریف_شده _MSC_VER
  #تعریف_کن MZ_FORCEINLINE __forceinline
#وإلاإذا defined(__GNUC__)
  #تعریف_کن MZ_FORCEINLINE مضمن __attribute__((__always_inline__))
#وإلا
  #تعریف_کن MZ_FORCEINLINE مضمن
#پایان_اگر

#اگر_تعریف_شده __cplusplus
  خارجي "C" {
#پایان_اگر

// ------------------- zlib-style API's

mz_ulong mz_adler32(mz_ulong adler, ثابت بیعلامت حرف *ptr, size_t buf_len)
{
  mz_uint32 i, s1 = (mz_uint32)(adler & 0xffff), s2 = (mz_uint32)(adler >> 16); size_t بلوک_len = buf_len % 5552;
  إذا (!ptr) أرجع MZ_ADLER32_INIT;
  طالما (buf_len) {
    لكل (i = 0; i + 7 < بلوک_len; i += 8, ptr += 8) {
      s1 += ptr[0]; s2 += s1; s1 += ptr[1]; s2 += s1; s1 += ptr[2]; s2 += s1; s1 += ptr[3]; s2 += s1;
      s1 += ptr[4]; s2 += s1; s1 += ptr[5]; s2 += s1; s1 += ptr[6]; s2 += s1; s1 += ptr[7]; s2 += s1;
    }
    لكل ( ; i < بلوک_len; ++i) { s1 += *ptr++; s2 += s1; }
    s1 %= 65521U; s2 %= 65521U; buf_len -= بلوک_len; بلوک_len = 5552;
  }
  أرجع (s2 << 16) + s1;
}

// Karl Malbrain's compact CRC-32. See "A compact CCITT crc16 and crc32 C implementation that balances processor cache usage against speed": http://www.geocities.com/malbrain/
mz_ulong mz_بررسی_چرخهای_32(mz_ulong بررسی_چرخهای, ثابت mz_uint8 *ptr, size_t buf_len)
{
  ساكن ثابت mz_uint32 s_بررسی_چرخهای_32[16] = { 0, 0x1db71064, 0x3b6e20c8, 0x26d930ac, 0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
    0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c, 0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c };
  mz_uint32 crcu32 = (mz_uint32)بررسی_چرخهای;
  إذا (!ptr) أرجع MZ_بررسی_چرخهای_32_INIT;
  crcu32 = ~crcu32; طالما (buf_len--) { mz_uint8 b = *ptr++; crcu32 = (crcu32 >> 4) ^ s_بررسی_چرخهای_32[(crcu32 & 0xF) ^ (b & 0xF)]; crcu32 = (crcu32 >> 4) ^ s_بررسی_چرخهای_32[(crcu32 & 0xF) ^ (b >> 4)]; }
  أرجع ~crcu32;
}

MINIZ_STATIC فراغ mz_free(فراغ *p)
{
  MZ_FREE(p);
}

#اگر_تعریف_نشده MINIZ_NO_ZLIB_APIS

ساكن فراغ *def_alloc_func(فراغ *opaque, size_t اقلام, size_t اندازه) { (فراغ)opaque, (فراغ)اقلام, (فراغ)اندازه; أرجع MZ_MALLOC(اقلام * اندازه); }
ساكن فراغ def_free_func(فراغ *opaque, فراغ *آدرس) { (فراغ)opaque, (فراغ)آدرس; MZ_FREE(آدرس); }
ساكن فراغ *def_realloc_func(فراغ *opaque, فراغ *آدرس, size_t اقلام, size_t اندازه) { (فراغ)opaque, (فراغ)آدرس, (فراغ)اقلام, (فراغ)اندازه; أرجع MZ_REALLOC(آدرس, اقلام * اندازه); }

ثابت حرف *mz_نسخه(فراغ)
{
  أرجع MZ_نسخه;
}

#اگر_تعریف_نشده MINIZ_NO_DEFLATE_APIS

صحيح mz_deflateInit(mz_streamp p_جریان, صحيح level)
{
  أرجع mz_deflateInit2(p_جریان, level, MZ_DEFLATED, MZ_DEFAULT_پنجره_بیتها, 9, MZ_DEFAULT_STRATEGY);
}

صحيح mz_deflateInit2(mz_streamp p_جریان, صحيح level, صحيح روش, صحيح پنجره_بیتها, صحيح mem_level, صحيح strategy)
{
  tdefl_compressor *pComp;
  mz_uint comp_flags = TDEFL_COMPUTE_ADLER32 | tdefl_create_comp_flags_from_zip_params(level, پنجره_بیتها, strategy);

  إذا (!p_جریان) أرجع MZ_جریان_ERROR;
  إذا ((روش != MZ_DEFLATED) || ((mem_level < 1) || (mem_level > 9)) || ((پنجره_بیتها != MZ_DEFAULT_پنجره_بیتها) && (-پنجره_بیتها != MZ_DEFAULT_پنجره_بیتها))) أرجع MZ_PARAM_ERROR;

  p_جریان->داده_type = 0;
  p_جریان->adler = MZ_ADLER32_INIT;
  p_جریان->پیام_2 = عدم;
  p_جریان->reserved = 0;
  p_جریان->مجموع_درون = 0;
  p_جریان->مجموع_بیرون = 0;
  إذا (!p_جریان->zalloc) p_جریان->zalloc = def_alloc_func;
  إذا (!p_جریان->zfree) p_جریان->zfree = def_free_func;

  pComp = (tdefl_compressor *)p_جریان->zalloc(p_جریان->opaque, 1, حجم(tdefl_compressor));
  إذا (!pComp)
    أرجع MZ_MEM_ERROR;

  p_جریان->state = (بنية mz_داخلی_state *)pComp;

  إذا (tdefl_init(pComp, عدم, عدم, comp_flags) != TDEFL_وضعیت_OKAY)
  {
    mz_deflate_انتها(p_جریان);
    أرجع MZ_PARAM_ERROR;
  }

  أرجع MZ_OK;
}

صحيح mz_deflateReset(mz_streamp p_جریان)
{
  إذا ((!p_جریان) || (!p_جریان->state) || (!p_جریان->zalloc) || (!p_جریان->zfree)) أرجع MZ_جریان_ERROR;
  p_جریان->مجموع_درون = p_جریان->مجموع_بیرون = 0;
  tdefl_init((tdefl_compressor*)p_جریان->state, عدم, عدم, ((tdefl_compressor*)p_جریان->state)->m_flags);
  أرجع MZ_OK;
}

صحيح mz_deflate(mz_streamp p_جریان, صحيح flush)
{
  size_t درون_بایتها, بیرون_بایتها;
  mz_ulong orig_مجموع_درون, orig_مجموع_بیرون;
  صحيح mz_وضعیت = MZ_OK;

  إذا ((!p_جریان) || (!p_جریان->state) || (flush < 0) || (flush > MZ_پایان) || (!p_جریان->بعدی_بیرون)) أرجع MZ_جریان_ERROR;
  إذا (!p_جریان->avail_بیرون) أرجع MZ_BUF_ERROR;

  إذا (flush == MZ_PARTIAL_FLUSH) flush = MZ_SYNC_FLUSH;

  إذا (((tdefl_compressor*)p_جریان->state)->m_prev_return_وضعیت == TDEFL_وضعیت_انجامشده)
    أرجع (flush == MZ_پایان) ? MZ_جریان_انتها : MZ_BUF_ERROR;

  orig_مجموع_درون = p_جریان->مجموع_درون; orig_مجموع_بیرون = p_جریان->مجموع_بیرون;
  لكل ( ; ; )
  {
    tdefl_وضعیت defl_وضعیت;
    درون_بایتها = p_جریان->avail_درون; بیرون_بایتها = p_جریان->avail_بیرون;

    defl_وضعیت = tdefl_compress((tdefl_compressor*)p_جریان->state, p_جریان->بعدی_درون, &درون_بایتها, p_جریان->بعدی_بیرون, &بیرون_بایتها, (tdefl_flush)flush);
    p_جریان->بعدی_درون += (mz_uint)درون_بایتها; p_جریان->avail_درون -= (mz_uint)درون_بایتها;
    p_جریان->مجموع_درون += (mz_uint)درون_بایتها; p_جریان->adler = tdefl_get_adler32((tdefl_compressor*)p_جریان->state);

    p_جریان->بعدی_بیرون += (mz_uint)بیرون_بایتها; p_جریان->avail_بیرون -= (mz_uint)بیرون_بایتها;
    p_جریان->مجموع_بیرون += (mz_uint)بیرون_بایتها;

    إذا (defl_وضعیت < 0)
    {
      mz_وضعیت = MZ_جریان_ERROR;
      اكسر;
    }
    وإلا إذا (defl_وضعیت == TDEFL_وضعیت_انجامشده)
    {
      mz_وضعیت = MZ_جریان_انتها;
      اكسر;
    }
    وإلا إذا (!p_جریان->avail_بیرون)
      اكسر;
    وإلا إذا ((!p_جریان->avail_درون) && (flush != MZ_پایان))
    {
      إذا ((flush) || (p_جریان->مجموع_درون != orig_مجموع_درون) || (p_جریان->مجموع_بیرون != orig_مجموع_بیرون))
        اكسر;
      أرجع MZ_BUF_ERROR; // Can't make forward progress without some input.
    }
  }
  أرجع mz_وضعیت;
}

صحيح mz_deflate_انتها(mz_streamp p_جریان)
{
  إذا (!p_جریان) أرجع MZ_جریان_ERROR;
  إذا (p_جریان->state)
  {
    p_جریان->zfree(p_جریان->opaque, p_جریان->state);
    p_جریان->state = عدم;
  }
  أرجع MZ_OK;
}

mz_ulong mz_deflateBound(mz_streamp p_جریان, mz_ulong منبع_len)
{
  (فراغ)p_جریان;
  // This is really over conservative. (And lame, but it's actually pretty tricky to compute a true upper bound given the way tdefl's blocking works.)
  أرجع MZ_MAX(128 + (منبع_len * 110) / 100, 128 + منبع_len + ((منبع_len / (31 * 1024)) + 1) * 5);
}

صحيح mz_compress2(بیعلامت حرف *pDest, mz_ulong *pDest_len, ثابت بیعلامت حرف *p_منبع, mz_ulong منبع_len, صحيح level)
{
  صحيح وضعیت;
  mz_جریان جریان;
  memset(&جریان, 0, حجم(جریان));

  // In case mz_ulong is 64-bits (argh I hate longs).
  إذا ((منبع_len | *pDest_len) > 0xFFFFFFFFU) أرجع MZ_PARAM_ERROR;

  جریان.بعدی_درون = p_منبع;
  جریان.avail_درون = (mz_uint32)منبع_len;
  جریان.بعدی_بیرون = pDest;
  جریان.avail_بیرون = (mz_uint32)*pDest_len;

  وضعیت = mz_deflateInit(&جریان, level);
  إذا (وضعیت != MZ_OK) أرجع وضعیت;

  وضعیت = mz_deflate(&جریان, MZ_پایان);
  إذا (وضعیت != MZ_جریان_انتها)
  {
    mz_deflate_انتها(&جریان);
    أرجع (وضعیت == MZ_OK) ? MZ_BUF_ERROR : وضعیت;
  }

  *pDest_len = جریان.مجموع_بیرون;
  أرجع mz_deflate_انتها(&جریان);
}

صحيح mz_compress(بیعلامت حرف *pDest, mz_ulong *pDest_len, ثابت بیعلامت حرف *p_منبع, mz_ulong منبع_len)
{
  أرجع mz_compress2(pDest, pDest_len, p_منبع, منبع_len, MZ_DEFAULT_COMPRESSION);
}

mz_ulong mz_compressBound(mz_ulong منبع_len)
{
  أرجع mz_deflateBound(عدم, منبع_len);
}

#پایان_اگر /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#اگر_تعریف_نشده MINIZ_NO_INFLATE_APIS

تعريفنوع بنية
{
  tinfl_decompressor m_decomp;
  mz_uint m_dict_ofs, m_dict_avail, m_اولی_call, m_has_flushed; صحيح m_پنجره_بیتها;
  mz_uint8 m_dict[TINFL_LZ_DICT_اندازه];
  tinfl_وضعیت m_آخرین_وضعیت;
} inflate_state;

صحيح mz_inflateInit2(mz_streamp p_جریان, صحيح پنجره_بیتها)
{
  inflate_state *pDecomp;
  إذا (!p_جریان) أرجع MZ_جریان_ERROR;
  إذا ((پنجره_بیتها != MZ_DEFAULT_پنجره_بیتها) && (-پنجره_بیتها != MZ_DEFAULT_پنجره_بیتها)) أرجع MZ_PARAM_ERROR;

  p_جریان->داده_type = 0;
  p_جریان->adler = 0;
  p_جریان->پیام_2 = عدم;
  p_جریان->مجموع_درون = 0;
  p_جریان->مجموع_بیرون = 0;
  p_جریان->reserved = 0;
  إذا (!p_جریان->zalloc) p_جریان->zalloc = def_alloc_func;
  إذا (!p_جریان->zfree) p_جریان->zfree = def_free_func;

  pDecomp = (inflate_state*)p_جریان->zalloc(p_جریان->opaque, 1, حجم(inflate_state));
  إذا (!pDecomp) أرجع MZ_MEM_ERROR;

  p_جریان->state = (بنية mz_داخلی_state *)pDecomp;

  tinfl_init(&pDecomp->m_decomp);
  pDecomp->m_dict_ofs = 0;
  pDecomp->m_dict_avail = 0;
  pDecomp->m_آخرین_وضعیت = TINFL_وضعیت_NEEDS_بیشتر_درون_داد;
  pDecomp->m_اولی_call = 1;
  pDecomp->m_has_flushed = 0;
  pDecomp->m_پنجره_بیتها = پنجره_بیتها;

  أرجع MZ_OK;
}

صحيح mz_inflateInit(mz_streamp p_جریان)
{
   أرجع mz_inflateInit2(p_جریان, MZ_DEFAULT_پنجره_بیتها);
}

صحيح mz_inflate(mz_streamp p_جریان, صحيح flush)
{
  inflate_state* pState;
  mz_uint n, اولی_call, decomp_flags = TINFL_FLAG_COMPUTE_ADLER32;
  size_t درون_بایتها, بیرون_بایتها, orig_avail_درون;
  tinfl_وضعیت وضعیت;

  إذا ((!p_جریان) || (!p_جریان->state)) أرجع MZ_جریان_ERROR;
  إذا (flush == MZ_PARTIAL_FLUSH) flush = MZ_SYNC_FLUSH;
  إذا ((flush) && (flush != MZ_SYNC_FLUSH) && (flush != MZ_پایان)) أرجع MZ_جریان_ERROR;

  pState = (inflate_state*)p_جریان->state;
  إذا (pState->m_پنجره_بیتها > 0) decomp_flags |= TINFL_FLAG_PARSE_ZLIB_سرآیند;
  orig_avail_درون = p_جریان->avail_درون;

  اولی_call = pState->m_اولی_call; pState->m_اولی_call = 0;
  إذا (pState->m_آخرین_وضعیت < 0) أرجع MZ_داده_ERROR;

  إذا (pState->m_has_flushed && (flush != MZ_پایان)) أرجع MZ_جریان_ERROR;
  pState->m_has_flushed |= (flush == MZ_پایان);

  إذا ((flush == MZ_پایان) && (اولی_call))
  {
    // MZ_FINISH on the first call implies that the input and output buffers are large enough to hold the entire compressed/decompressed file.
    decomp_flags |= TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF;
    درون_بایتها = p_جریان->avail_درون; بیرون_بایتها = p_جریان->avail_بیرون;
    وضعیت = tinfl_decompress(&pState->m_decomp, p_جریان->بعدی_درون, &درون_بایتها, p_جریان->بعدی_بیرون, p_جریان->بعدی_بیرون, &بیرون_بایتها, decomp_flags);
    pState->m_آخرین_وضعیت = وضعیت;
    p_جریان->بعدی_درون += (mz_uint)درون_بایتها; p_جریان->avail_درون -= (mz_uint)درون_بایتها; p_جریان->مجموع_درون += (mz_uint)درون_بایتها;
    p_جریان->adler = tinfl_get_adler32(&pState->m_decomp);
    p_جریان->بعدی_بیرون += (mz_uint)بیرون_بایتها; p_جریان->avail_بیرون -= (mz_uint)بیرون_بایتها; p_جریان->مجموع_بیرون += (mz_uint)بیرون_بایتها;

    إذا (وضعیت < 0)
      أرجع MZ_داده_ERROR;
    وإلا إذا (وضعیت != TINFL_وضعیت_انجامشده)
    {
      pState->m_آخرین_وضعیت = TINFL_وضعیت_FAILED;
      أرجع MZ_BUF_ERROR;
    }
    أرجع MZ_جریان_انتها;
  }
  // flush != MZ_FINISH then we must assume there's more input.
  إذا (flush != MZ_پایان) decomp_flags |= TINFL_FLAG_HAS_بیشتر_درون_داد;

  إذا (pState->m_dict_avail)
  {
    n = MZ_MIN(pState->m_dict_avail, p_جریان->avail_بیرون);
    کپی_حافظه(p_جریان->بعدی_بیرون, pState->m_dict + pState->m_dict_ofs, n);
    p_جریان->بعدی_بیرون += n; p_جریان->avail_بیرون -= n; p_جریان->مجموع_بیرون += n;
    pState->m_dict_avail -= n; pState->m_dict_ofs = (pState->m_dict_ofs + n) & (TINFL_LZ_DICT_اندازه - 1);
    أرجع ((pState->m_آخرین_وضعیت == TINFL_وضعیت_انجامشده) && (!pState->m_dict_avail)) ? MZ_جریان_انتها : MZ_OK;
  }

  لكل ( ; ; )
  {
    درون_بایتها = p_جریان->avail_درون;
    بیرون_بایتها = TINFL_LZ_DICT_اندازه - pState->m_dict_ofs;

    وضعیت = tinfl_decompress(&pState->m_decomp, p_جریان->بعدی_درون, &درون_بایتها, pState->m_dict, pState->m_dict + pState->m_dict_ofs, &بیرون_بایتها, decomp_flags);
    pState->m_آخرین_وضعیت = وضعیت;

    p_جریان->بعدی_درون += (mz_uint)درون_بایتها; p_جریان->avail_درون -= (mz_uint)درون_بایتها;
    p_جریان->مجموع_درون += (mz_uint)درون_بایتها; p_جریان->adler = tinfl_get_adler32(&pState->m_decomp);

    pState->m_dict_avail = (mz_uint)بیرون_بایتها;

    n = MZ_MIN(pState->m_dict_avail, p_جریان->avail_بیرون);
    کپی_حافظه(p_جریان->بعدی_بیرون, pState->m_dict + pState->m_dict_ofs, n);
    p_جریان->بعدی_بیرون += n; p_جریان->avail_بیرون -= n; p_جریان->مجموع_بیرون += n;
    pState->m_dict_avail -= n; pState->m_dict_ofs = (pState->m_dict_ofs + n) & (TINFL_LZ_DICT_اندازه - 1);

    إذا (وضعیت < 0)
       أرجع MZ_داده_ERROR; // Stream is corrupted (there could be some uncompressed data left in the output dictionary - oh well).
    وإلا إذا ((وضعیت == TINFL_وضعیت_NEEDS_بیشتر_درون_داد) && (!orig_avail_درون))
      أرجع MZ_BUF_ERROR; // Signal caller that we can't make forward progress without supplying more input or by setting flush to MZ_FINISH.
    وإلا إذا (flush == MZ_پایان)
    {
       // The output buffer MUST be large to hold the remaining uncompressed data when flush==MZ_FINISH.
       إذا (وضعیت == TINFL_وضعیت_انجامشده)
          أرجع pState->m_dict_avail ? MZ_BUF_ERROR : MZ_جریان_انتها;
       // status here must be TINFL_STATUS_HAS_MORE_OUTPUT, which means there's at least 1 more byte on the way. If there's no more room left in the output buffer then something is wrong.
       وإلا إذا (!p_جریان->avail_بیرون)
          أرجع MZ_BUF_ERROR;
    }
    وإلا إذا ((وضعیت == TINFL_وضعیت_انجامشده) || (!p_جریان->avail_درون) || (!p_جریان->avail_بیرون) || (pState->m_dict_avail))
      اكسر;
  }

  أرجع ((وضعیت == TINFL_وضعیت_انجامشده) && (!pState->m_dict_avail)) ? MZ_جریان_انتها : MZ_OK;
}

صحيح mz_inflate_انتها(mz_streamp p_جریان)
{
  إذا (!p_جریان)
    أرجع MZ_جریان_ERROR;
  إذا (p_جریان->state)
  {
    p_جریان->zfree(p_جریان->opaque, p_جریان->state);
    p_جریان->state = عدم;
  }
  أرجع MZ_OK;
}

صحيح mz_uncompress(بیعلامت حرف *pDest, mz_ulong *pDest_len, ثابت بیعلامت حرف *p_منبع, mz_ulong منبع_len)
{
  mz_جریان جریان;
  صحيح وضعیت;
  memset(&جریان, 0, حجم(جریان));

  // In case mz_ulong is 64-bits (argh I hate longs).
  إذا ((منبع_len | *pDest_len) > 0xFFFFFFFFU) أرجع MZ_PARAM_ERROR;

  جریان.بعدی_درون = p_منبع;
  جریان.avail_درون = (mz_uint32)منبع_len;
  جریان.بعدی_بیرون = pDest;
  جریان.avail_بیرون = (mz_uint32)*pDest_len;

  وضعیت = mz_inflateInit(&جریان);
  إذا (وضعیت != MZ_OK)
    أرجع وضعیت;

  وضعیت = mz_inflate(&جریان, MZ_پایان);
  إذا (وضعیت != MZ_جریان_انتها)
  {
    mz_inflate_انتها(&جریان);
    أرجع ((وضعیت == MZ_BUF_ERROR) && (!جریان.avail_درون)) ? MZ_داده_ERROR : وضعیت;
  }
  *pDest_len = جریان.مجموع_بیرون;

  أرجع mz_inflate_انتها(&جریان);
}

#پایان_اگر /*#ifndef MINIZ_NO_INFLATE_APIS*/

ثابت حرف *mz_error(صحيح err)
{
  ساكن بنية { صحيح m_err; ثابت حرف *m_pDesc; } s_error_descs[] =
  {
    { MZ_OK, "" }, { MZ_جریان_انتها, "stream end" }, { MZ_NEED_DICT, "need dictionary" }, { MZ_ERRNO, "file error" }, { MZ_جریان_ERROR, "stream error" },
    { MZ_داده_ERROR, "data error" }, { MZ_MEM_ERROR, "out of memory" }, { MZ_BUF_ERROR, "buf error" }, { MZ_نسخه_ERROR, "version error" }, { MZ_PARAM_ERROR, "parameter error" }
  };
  mz_uint i; لكل (i = 0; i < حجم(s_error_descs) / حجم(s_error_descs[0]); ++i) إذا (s_error_descs[i].m_err == err) أرجع s_error_descs[i].m_pDesc;
  أرجع عدم;
}

#پایان_اگر //MINIZ_NO_ZLIB_APIS

// ------------------- Low-level Decompression (completely independent from all compression API's)
#اگر_تعریف_نشده MINIZ_NO_INFLATE_APIS

#تعریف_کن TINFL_MEMCPY(d, s, l) کپی_حافظه(d, s, l)
#تعریف_کن TINFL_MEMSET(p, c, l) memset(p, c, l)

#تعریف_کن TINFL_CR_BEGIN بدل(r->m_state) { حالة 0:
#تعریف_کن TINFL_CR_RETURN(state_شاخص, نتیجه) افعل { وضعیت = نتیجه; r->m_state = state_شاخص; اذهب common_exit; حالة state_شاخص:; } MZ_MACRO_انتها
#تعریف_کن TINFL_CR_RETURN_FOREVER(state_شاخص, نتیجه) افعل { لكل ( ; ; ) { TINFL_CR_RETURN(state_شاخص, نتیجه); } } MZ_MACRO_انتها
#تعریف_کن TINFL_CR_پایان }

// TODO: If the caller has indicated that there's no more input, and we attempt to read beyond the input buf, then something is wrong with the input because the inflator never
// reads ahead more than it needs to. Currently TINFL_GET_BYTE() pads the end of the stream with 0's in this scenario.
#تعریف_کن TINFL_GET_BYTE(state_شاخص, c) افعل { \
  إذا (p_درون_buf_cur >= p_درون_buf_انتها) { \
    لكل ( ; ; ) { \
      إذا (decomp_flags & TINFL_FLAG_HAS_بیشتر_درون_داد) { \
        TINFL_CR_RETURN(state_شاخص, TINFL_وضعیت_NEEDS_بیشتر_درون_داد); \
        إذا (p_درون_buf_cur < p_درون_buf_انتها) { \
          c = *p_درون_buf_cur++; \
          اكسر; \
        } \
      } وإلا { \
        c = 0; \
        اكسر; \
      } \
    } \
  } وإلا c = *p_درون_buf_cur++; } MZ_MACRO_انتها

#تعریف_کن TINFL_NEED_بیتها(state_شاخص, n) افعل { mz_uint c; TINFL_GET_BYTE(state_شاخص, c); بیت_buf |= (((tinfl_بیت_buf_t)c) << رقم_بیتها); رقم_بیتها += 8; } طالما (رقم_بیتها < (mz_uint)(n))
#تعریف_کن TINFL_SKIP_بیتها(state_شاخص, n) افعل { إذا (رقم_بیتها < (mz_uint)(n)) { TINFL_NEED_بیتها(state_شاخص, n); } بیت_buf >>= (n); رقم_بیتها -= (n); } MZ_MACRO_انتها
#تعریف_کن TINFL_GET_بیتها(state_شاخص, b, n) افعل { إذا (رقم_بیتها < (mz_uint)(n)) { TINFL_NEED_بیتها(state_شاخص, n); } b = بیت_buf & ((1 << (n)) - 1); بیت_buf >>= (n); رقم_بیتها -= (n); } MZ_MACRO_انتها

// TINFL_HUFF_BITBUF_FILL() is only used rarely, when the number of bytes remaining in the input buffer falls below 2.
// It reads just enough bytes from the input stream that are needed to decode the next Huffman code (and absolutely no more). It works by trying to fully decode a
// Huffman code by using whatever bits are currently present in the bit buffer. If this fails, it reads another byte, and tries again until it succeeds or until the
// bit buffer contains >=15 bits (deflate's max. Huffman code size).
#تعریف_کن TINFL_HUFF_BITBUF_FILL(state_شاخص, pHuff) \
  افعل { \
    موقت = (pHuff)->m_look_به_بالا[بیت_buf & (TINFL_FAST_LOOKUP_اندازه - 1)]; \
    إذا (موقت >= 0) { \
      کد_len = موقت >> 9; \
      إذا ((کد_len) && (رقم_بیتها >= کد_len)) \
          اكسر; \
    } وإلا إذا (رقم_بیتها > TINFL_FAST_LOOKUP_بیتها) { \
       کد_len = TINFL_FAST_LOOKUP_بیتها; \
       افعل { \
          موقت = (pHuff)->m_درخت[~موقت + ((بیت_buf >> کد_len++) & 1)]; \
       } طالما ((موقت < 0) && (رقم_بیتها >= (کد_len + 1))); \
       إذا (موقت >= 0) اكسر; \
    } \
    TINFL_GET_BYTE(state_شاخص, c); \
    بیت_buf |= (((tinfl_بیت_buf_t)c) << رقم_بیتها); \
    رقم_بیتها += 8; \
  } طالما (رقم_بیتها < 15);

// TINFL_HUFF_DECODE() decodes the next Huffman coded symbol. It's more complex than you would initially expect because the zlib API expects the decompressor to never read
// beyond the final byte of the deflate stream. (In other words, when this macro wants to read another byte from the input, it REALLY needs another byte in order to fully
// decode the next Huffman code.) Handling this properly is particularly important on raw deflate (non-zlib) streams, which aren't followed by a byte aligned adler-32.
// The slow path is only executed at the very end of the input buffer.
#تعریف_کن TINFL_HUFF_DECODE(state_شاخص, sym, pHuff) افعل { \
  صحيح موقت; mz_uint کد_len, c; \
  إذا (رقم_بیتها < 15) { \
    إذا ((p_درون_buf_انتها - p_درون_buf_cur) < 2) { \
       TINFL_HUFF_BITBUF_FILL(state_شاخص, pHuff); \
    } وإلا { \
       بیت_buf |= (((tinfl_بیت_buf_t)p_درون_buf_cur[0]) << رقم_بیتها) | (((tinfl_بیت_buf_t)p_درون_buf_cur[1]) << (رقم_بیتها + 8)); p_درون_buf_cur += 2; رقم_بیتها += 16; \
    } \
  } \
  إذا ((موقت = (pHuff)->m_look_به_بالا[بیت_buf & (TINFL_FAST_LOOKUP_اندازه - 1)]) >= 0) \
    کد_len = موقت >> 9, موقت &= 511; \
  وإلا { \
    کد_len = TINFL_FAST_LOOKUP_بیتها; افعل { موقت = (pHuff)->m_درخت[~موقت + ((بیت_buf >> کد_len++) & 1)]; } طالما (موقت < 0); \
  } sym = موقت; بیت_buf >>= کد_len; رقم_بیتها -= کد_len; } MZ_MACRO_انتها

tinfl_وضعیت tinfl_decompress(tinfl_decompressor *r, ثابت mz_uint8 *p_درون_buf_بعدی, size_t *p_درون_buf_اندازه, mz_uint8 *p_بیرون_buf_شروع, mz_uint8 *p_بیرون_buf_بعدی, size_t *p_بیرون_buf_اندازه, ثابت mz_uint32 decomp_flags)
{
  ساكن ثابت صحيح s_درازی_پایه[31] = { 3,4,5,6,7,8,9,10,11,13, 15,17,19,23,27,31,35,43,51,59, 67,83,99,115,131,163,195,227,258,0,0 };
  ساكن ثابت صحيح s_درازی_extra[31]= { 0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,0,0,0 };
  ساكن ثابت صحيح s_dist_پایه[32] = { 1,2,3,4,5,7,9,13,17,25,33,49,65,97,129,193, 257,385,513,769,1025,1537,2049,3073,4097,6145,8193,12289,16385,24577,0,0};
  ساكن ثابت صحيح s_dist_extra[32] = { 0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13};
  ساكن ثابت mz_uint8 s_درازی_dezigzag[19] = { 16,17,18,0,8,7,9,6,10,5,11,4,12,3,13,2,14,1,15 };
  ساكن ثابت صحيح s_min_جدول_sizes[3] = { 257, 1, 4 };

  tinfl_وضعیت وضعیت = TINFL_وضعیت_FAILED; mz_uint32 رقم_بیتها, dist, counter, رقم_extra; tinfl_بیت_buf_t بیت_buf;
  ثابت mz_uint8 *p_درون_buf_cur = p_درون_buf_بعدی, *ثابت p_درون_buf_انتها = p_درون_buf_بعدی + *p_درون_buf_اندازه;
  mz_uint8 *p_بیرون_buf_cur = p_بیرون_buf_بعدی, *ثابت p_بیرون_buf_انتها = p_بیرون_buf_بعدی + *p_بیرون_buf_اندازه;
  size_t بیرون_buf_اندازه_ماسک = (decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF) ? (size_t)-1 : ((p_بیرون_buf_بعدی - p_بیرون_buf_شروع) + *p_بیرون_buf_اندازه) - 1, dist_from_بیرون_buf_شروع;

  // Ensure the output buffer's size is a power of 2, unless the output buffer is large enough to hold the entire output file (in which case it doesn't matter).
  إذا (((بیرون_buf_اندازه_ماسک + 1) & بیرون_buf_اندازه_ماسک) || (p_بیرون_buf_بعدی < p_بیرون_buf_شروع)) { *p_درون_buf_اندازه = *p_بیرون_buf_اندازه = 0; أرجع TINFL_وضعیت_BAD_PARAM; }

  رقم_بیتها = r->m_رقم_بیتها; بیت_buf = r->m_بیت_buf; dist = r->m_dist; counter = r->m_counter; رقم_extra = r->m_رقم_extra; dist_from_بیرون_buf_شروع = r->m_dist_from_بیرون_buf_شروع;
  TINFL_CR_BEGIN

  بیت_buf = رقم_بیتها = dist = counter = رقم_extra = r->m_zhdr0 = r->m_zhdr1 = 0; r->m_z_adler32 = r->m_check_adler32 = 1;
  إذا (decomp_flags & TINFL_FLAG_PARSE_ZLIB_سرآیند)
  {
    TINFL_GET_BYTE(1, r->m_zhdr0); TINFL_GET_BYTE(2, r->m_zhdr1);
    counter = (((r->m_zhdr0 * 256 + r->m_zhdr1) % 31 != 0) || (r->m_zhdr1 & 32) || ((r->m_zhdr0 & 15) != 8));
    إذا (!(decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF)) counter |= (((1U << (8U + (r->m_zhdr0 >> 4))) > 32768U) || ((بیرون_buf_اندازه_ماسک + 1) < (size_t)(1U << (8U + (r->m_zhdr0 >> 4)))));
    إذا (counter) { TINFL_CR_RETURN_FOREVER(36, TINFL_وضعیت_FAILED); }
  }

  افعل
  {
    TINFL_GET_بیتها(3, r->m_final, 3); r->m_type = r->m_final >> 1;
    إذا (r->m_type == 0)
    {
      TINFL_SKIP_بیتها(5, رقم_بیتها & 7);
      لكل (counter = 0; counter < 4; ++counter) { إذا (رقم_بیتها) TINFL_GET_بیتها(6, r->m_raw_سرآیند[counter], 8); وإلا TINFL_GET_BYTE(7, r->m_raw_سرآیند[counter]); }
      إذا ((counter = (r->m_raw_سرآیند[0] | (r->m_raw_سرآیند[1] << 8))) != (mz_uint)(0xFFFF ^ (r->m_raw_سرآیند[2] | (r->m_raw_سرآیند[3] << 8)))) { TINFL_CR_RETURN_FOREVER(39, TINFL_وضعیت_FAILED); }
      طالما ((counter) && (رقم_بیتها))
      {
        TINFL_GET_بیتها(51, dist, 8);
        طالما (p_بیرون_buf_cur >= p_بیرون_buf_انتها) { TINFL_CR_RETURN(52, TINFL_وضعیت_HAS_بیشتر_OUTPUT); }
        *p_بیرون_buf_cur++ = (mz_uint8)dist;
        counter--;
      }
      طالما (counter)
      {
        size_t n; طالما (p_بیرون_buf_cur >= p_بیرون_buf_انتها) { TINFL_CR_RETURN(9, TINFL_وضعیت_HAS_بیشتر_OUTPUT); }
        طالما (p_درون_buf_cur >= p_درون_buf_انتها)
        {
          إذا (decomp_flags & TINFL_FLAG_HAS_بیشتر_درون_داد)
          {
            TINFL_CR_RETURN(38, TINFL_وضعیت_NEEDS_بیشتر_درون_داد);
          }
          وإلا
          {
            TINFL_CR_RETURN_FOREVER(40, TINFL_وضعیت_FAILED);
          }
        }
        n = MZ_MIN(MZ_MIN((size_t)(p_بیرون_buf_انتها - p_بیرون_buf_cur), (size_t)(p_درون_buf_انتها - p_درون_buf_cur)), counter);
        TINFL_MEMCPY(p_بیرون_buf_cur, p_درون_buf_cur, n); p_درون_buf_cur += n; p_بیرون_buf_cur += n; counter -= (mz_uint)n;
      }
    }
    وإلا إذا (r->m_type == 3)
    {
      TINFL_CR_RETURN_FOREVER(10, TINFL_وضعیت_FAILED);
    }
    وإلا
    {
      إذا (r->m_type == 1)
      {
        mz_uint8 *p = r->m_tables[0].m_کد_اندازه; mz_uint i;
        r->m_جدول_sizes[0] = 288; r->m_جدول_sizes[1] = 32; TINFL_MEMSET(r->m_tables[1].m_کد_اندازه, 5, 32);
        لكل ( i = 0; i <= 143; ++i) *p++ = 8;
        لكل ( ; i <= 255; ++i) *p++ = 9;
        لكل ( ; i <= 279; ++i) *p++ = 7;
        لكل ( ; i <= 287; ++i) *p++ = 8;
      }
      وإلا
      {
        لكل (counter = 0; counter < 3; counter++) { TINFL_GET_بیتها(11, r->m_جدول_sizes[counter], "\05\05\04"[counter]); r->m_جدول_sizes[counter] += s_min_جدول_sizes[counter]; }
        MZ_CLEAR_ARR(r->m_tables[2].m_کد_اندازه); لكل (counter = 0; counter < r->m_جدول_sizes[2]; counter++) { mz_uint s; TINFL_GET_بیتها(14, s, 3); r->m_tables[2].m_کد_اندازه[s_درازی_dezigzag[counter]] = (mz_uint8)s; }
        r->m_جدول_sizes[2] = 19;
      }
      لكل ( ; (صحيح)r->m_type >= 0; r->m_type--)
      {
        صحيح درخت_بعدی, درخت_cur; tinfl_huff_جدول *p_جدول;
        mz_uint i, j, استفاده_شده_syms, مجموع, sym_شاخص, بعدی_کد[17], مجموع_syms[16]; p_جدول = &r->m_tables[r->m_type]; MZ_CLEAR_ARR(مجموع_syms); MZ_CLEAR_ARR(p_جدول->m_look_به_بالا); MZ_CLEAR_ARR(p_جدول->m_درخت);
        لكل (i = 0; i < r->m_جدول_sizes[r->m_type]; ++i) مجموع_syms[p_جدول->m_کد_اندازه[i]]++;
        استفاده_شده_syms = 0, مجموع = 0; بعدی_کد[0] = بعدی_کد[1] = 0;
        لكل (i = 1; i <= 15; ++i) { استفاده_شده_syms += مجموع_syms[i]; بعدی_کد[i + 1] = (مجموع = ((مجموع + مجموع_syms[i]) << 1)); }
        إذا ((65536 != مجموع) && (استفاده_شده_syms > 1))
        {
          TINFL_CR_RETURN_FOREVER(35, TINFL_وضعیت_FAILED);
        }
        لكل (درخت_بعدی = -1, sym_شاخص = 0; sym_شاخص < r->m_جدول_sizes[r->m_type]; ++sym_شاخص)
        {
          mz_uint rev_کد = 0, l, cur_کد, کد_اندازه_2 = p_جدول->m_کد_اندازه[sym_شاخص]; إذا (!کد_اندازه_2) استمر;
          cur_کد = بعدی_کد[کد_اندازه_2]++; لكل (l = کد_اندازه_2; l > 0; l--, cur_کد >>= 1) rev_کد = (rev_کد << 1) | (cur_کد & 1);
          إذا (کد_اندازه_2 <= TINFL_FAST_LOOKUP_بیتها) { mz_int16 k = (mz_int16)((کد_اندازه_2 << 9) | sym_شاخص); طالما (rev_کد < TINFL_FAST_LOOKUP_اندازه) { p_جدول->m_look_به_بالا[rev_کد] = k; rev_کد += (1 << کد_اندازه_2); } استمر; }
          إذا (0 == (درخت_cur = p_جدول->m_look_به_بالا[rev_کد & (TINFL_FAST_LOOKUP_اندازه - 1)])) { p_جدول->m_look_به_بالا[rev_کد & (TINFL_FAST_LOOKUP_اندازه - 1)] = (mz_int16)درخت_بعدی; درخت_cur = درخت_بعدی; درخت_بعدی -= 2; }
          rev_کد >>= (TINFL_FAST_LOOKUP_بیتها - 1);
          لكل (j = کد_اندازه_2; j > (TINFL_FAST_LOOKUP_بیتها + 1); j--)
          {
            درخت_cur -= ((rev_کد >>= 1) & 1);
            إذا (!p_جدول->m_درخت[-درخت_cur - 1]) { p_جدول->m_درخت[-درخت_cur - 1] = (mz_int16)درخت_بعدی; درخت_cur = درخت_بعدی; درخت_بعدی -= 2; } وإلا درخت_cur = p_جدول->m_درخت[-درخت_cur - 1];
          }
          درخت_cur -= ((rev_کد >>= 1) & 1); p_جدول->m_درخت[-درخت_cur - 1] = (mz_int16)sym_شاخص;
        }
        إذا (r->m_type == 2)
        {
          لكل (counter = 0; counter < (r->m_جدول_sizes[0] + r->m_جدول_sizes[1]); )
          {
            mz_uint s; TINFL_HUFF_DECODE(16, dist, &r->m_tables[2]); إذا (dist < 16) { r->m_len_codes[counter++] = (mz_uint8)dist; استمر; }
            إذا ((dist == 16) && (!counter))
            {
              TINFL_CR_RETURN_FOREVER(17, TINFL_وضعیت_FAILED);
            }
            رقم_extra = "\02\03\07"[dist - 16]; TINFL_GET_بیتها(18, s, رقم_extra); s += "\03\03\013"[dist - 16];
            TINFL_MEMSET(r->m_len_codes + counter, (dist == 16) ? r->m_len_codes[counter - 1] : 0, s); counter += s;
          }
          إذا ((r->m_جدول_sizes[0] + r->m_جدول_sizes[1]) != counter)
          {
            TINFL_CR_RETURN_FOREVER(21, TINFL_وضعیت_FAILED);
          }
          TINFL_MEMCPY(r->m_tables[0].m_کد_اندازه, r->m_len_codes, r->m_جدول_sizes[0]); TINFL_MEMCPY(r->m_tables[1].m_کد_اندازه, r->m_len_codes + r->m_جدول_sizes[0], r->m_جدول_sizes[1]);
        }
      }
      لكل ( ; ; )
      {
        mz_uint8 *pSrc;
        لكل ( ; ; )
        {
          إذا (((p_درون_buf_انتها - p_درون_buf_cur) < 4) || ((p_بیرون_buf_انتها - p_بیرون_buf_cur) < 2))
          {
            TINFL_HUFF_DECODE(23, counter, &r->m_tables[0]);
            إذا (counter >= 256)
              اكسر;
            طالما (p_بیرون_buf_cur >= p_بیرون_buf_انتها) { TINFL_CR_RETURN(24, TINFL_وضعیت_HAS_بیشتر_OUTPUT); }
            *p_بیرون_buf_cur++ = (mz_uint8)counter;
          }
          وإلا
          {
            صحيح sym2; mz_uint کد_len;
#إذا TINFL_USE_64_بیت_BITBUF
            إذا (رقم_بیتها < 30) { بیت_buf |= (((tinfl_بیت_buf_t)MZ_READ_LE32(p_درون_buf_cur)) << رقم_بیتها); p_درون_buf_cur += 4; رقم_بیتها += 32; }
#وإلا
            إذا (رقم_بیتها < 15) { بیت_buf |= (((tinfl_بیت_buf_t)MZ_READ_LE16(p_درون_buf_cur)) << رقم_بیتها); p_درون_buf_cur += 2; رقم_بیتها += 16; }
#پایان_اگر
            إذا ((sym2 = r->m_tables[0].m_look_به_بالا[بیت_buf & (TINFL_FAST_LOOKUP_اندازه - 1)]) >= 0)
              کد_len = sym2 >> 9;
            وإلا
            {
              کد_len = TINFL_FAST_LOOKUP_بیتها; افعل { sym2 = r->m_tables[0].m_درخت[~sym2 + ((بیت_buf >> کد_len++) & 1)]; } طالما (sym2 < 0);
            }
            counter = sym2; بیت_buf >>= کد_len; رقم_بیتها -= کد_len;
            إذا (counter & 256)
              اكسر;

#إذا !TINFL_USE_64_بیت_BITBUF
            إذا (رقم_بیتها < 15) { بیت_buf |= (((tinfl_بیت_buf_t)MZ_READ_LE16(p_درون_buf_cur)) << رقم_بیتها); p_درون_buf_cur += 2; رقم_بیتها += 16; }
#پایان_اگر
            إذا ((sym2 = r->m_tables[0].m_look_به_بالا[بیت_buf & (TINFL_FAST_LOOKUP_اندازه - 1)]) >= 0)
              کد_len = sym2 >> 9;
            وإلا
            {
              کد_len = TINFL_FAST_LOOKUP_بیتها; افعل { sym2 = r->m_tables[0].m_درخت[~sym2 + ((بیت_buf >> کد_len++) & 1)]; } طالما (sym2 < 0);
            }
            بیت_buf >>= کد_len; رقم_بیتها -= کد_len;

            p_بیرون_buf_cur[0] = (mz_uint8)counter;
            إذا (sym2 & 256)
            {
              p_بیرون_buf_cur++;
              counter = sym2;
              اكسر;
            }
            p_بیرون_buf_cur[1] = (mz_uint8)sym2;
            p_بیرون_buf_cur += 2;
          }
        }
        إذا ((counter &= 511) == 256) اكسر;

        رقم_extra = s_درازی_extra[counter - 257]; counter = s_درازی_پایه[counter - 257];
        إذا (رقم_extra) { mz_uint extra_بیتها; TINFL_GET_بیتها(25, extra_بیتها, رقم_extra); counter += extra_بیتها; }

        TINFL_HUFF_DECODE(26, dist, &r->m_tables[1]);
        رقم_extra = s_dist_extra[dist]; dist = s_dist_پایه[dist];
        إذا (رقم_extra) { mz_uint extra_بیتها; TINFL_GET_بیتها(27, extra_بیتها, رقم_extra); dist += extra_بیتها; }

        dist_from_بیرون_buf_شروع = p_بیرون_buf_cur - p_بیرون_buf_شروع;
        إذا ((dist > dist_from_بیرون_buf_شروع) && (decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF))
        {
          TINFL_CR_RETURN_FOREVER(37, TINFL_وضعیت_FAILED);
        }

        pSrc = p_بیرون_buf_شروع + ((dist_from_بیرون_buf_شروع - dist) & بیرون_buf_اندازه_ماسک);

        إذا ((MZ_MAX(p_بیرون_buf_cur, pSrc) + counter) > p_بیرون_buf_انتها)
        {
          طالما (counter--)
          {
            طالما (p_بیرون_buf_cur >= p_بیرون_buf_انتها) { TINFL_CR_RETURN(53, TINFL_وضعیت_HAS_بیشتر_OUTPUT); }
            *p_بیرون_buf_cur++ = p_بیرون_buf_شروع[(dist_from_بیرون_buf_شروع++ - dist) & بیرون_buf_اندازه_ماسک];
          }
          استمر;
        }
#إذا MINIZ_USE_UNALIGNED_LOADS_AND_STORES
        وإلا إذا ((counter >= 9) && (counter <= dist))
        {
          ثابت mz_uint8 *p_Src_انتها = pSrc + (counter & ~7);
          افعل
          {
            ((mz_uint32 *)p_بیرون_buf_cur)[0] = ((ثابت mz_uint32 *)pSrc)[0];
            ((mz_uint32 *)p_بیرون_buf_cur)[1] = ((ثابت mz_uint32 *)pSrc)[1];
            p_بیرون_buf_cur += 8;
          } طالما ((pSrc += 8) < p_Src_انتها);
          إذا ((counter &= 7) < 3)
          {
            إذا (counter)
            {
              p_بیرون_buf_cur[0] = pSrc[0];
              إذا (counter > 1)
                p_بیرون_buf_cur[1] = pSrc[1];
              p_بیرون_buf_cur += counter;
            }
            استمر;
          }
        }
#پایان_اگر
        افعل
        {
          p_بیرون_buf_cur[0] = pSrc[0];
          p_بیرون_buf_cur[1] = pSrc[1];
          p_بیرون_buf_cur[2] = pSrc[2];
          p_بیرون_buf_cur += 3; pSrc += 3;
        } طالما ((صحيح)(counter -= 3) > 2);
        إذا ((صحيح)counter > 0)
        {
          p_بیرون_buf_cur[0] = pSrc[0];
          إذا ((صحيح)counter > 1)
            p_بیرون_buf_cur[1] = pSrc[1];
          p_بیرون_buf_cur += counter;
        }
      }
    }
  } طالما (!(r->m_final & 1));
  إذا (decomp_flags & TINFL_FLAG_PARSE_ZLIB_سرآیند)
  {
    TINFL_SKIP_بیتها(32, رقم_بیتها & 7); لكل (counter = 0; counter < 4; ++counter) { mz_uint s; إذا (رقم_بیتها) TINFL_GET_بیتها(41, s, 8); وإلا TINFL_GET_BYTE(42, s); r->m_z_adler32 = (r->m_z_adler32 << 8) | s; }
  }
  TINFL_CR_RETURN_FOREVER(34, TINFL_وضعیت_انجامشده);
  TINFL_CR_پایان

common_exit:
  r->m_رقم_بیتها = رقم_بیتها; r->m_بیت_buf = بیت_buf; r->m_dist = dist; r->m_counter = counter; r->m_رقم_extra = رقم_extra; r->m_dist_from_بیرون_buf_شروع = dist_from_بیرون_buf_شروع;
  *p_درون_buf_اندازه = p_درون_buf_cur - p_درون_buf_بعدی; *p_بیرون_buf_اندازه = p_بیرون_buf_cur - p_بیرون_buf_بعدی;
  إذا ((decomp_flags & (TINFL_FLAG_PARSE_ZLIB_سرآیند | TINFL_FLAG_COMPUTE_ADLER32)) && (وضعیت >= 0))
  {
    ثابت mz_uint8 *ptr = p_بیرون_buf_بعدی; size_t buf_len = *p_بیرون_buf_اندازه;
    mz_uint32 i, s1 = r->m_check_adler32 & 0xffff, s2 = r->m_check_adler32 >> 16; size_t بلوک_len = buf_len % 5552;
    طالما (buf_len)
    {
      لكل (i = 0; i + 7 < بلوک_len; i += 8, ptr += 8)
      {
        s1 += ptr[0], s2 += s1; s1 += ptr[1], s2 += s1; s1 += ptr[2], s2 += s1; s1 += ptr[3], s2 += s1;
        s1 += ptr[4], s2 += s1; s1 += ptr[5], s2 += s1; s1 += ptr[6], s2 += s1; s1 += ptr[7], s2 += s1;
      }
      لكل ( ; i < بلوک_len; ++i) s1 += *ptr++, s2 += s1;
      s1 %= 65521U, s2 %= 65521U; buf_len -= بلوک_len; بلوک_len = 5552;
    }
    r->m_check_adler32 = (s2 << 16) + s1; إذا ((وضعیت == TINFL_وضعیت_انجامشده) && (decomp_flags & TINFL_FLAG_PARSE_ZLIB_سرآیند) && (r->m_check_adler32 != r->m_z_adler32)) وضعیت = TINFL_وضعیت_ADLER32_MISMATCH;
  }
  أرجع وضعیت;
}

// Higher level helper functions.
فراغ *tinfl_decompress_mem_مقصد_انباشته(ثابت فراغ *pSrc_buf, size_t src_buf_len, size_t *p_بیرون_len, صحيح flags)
{
  tinfl_decompressor decomp; فراغ *pBuf = عدم, *pNew_buf; size_t src_buf_ofs = 0, بیرون_buf_ظرفیت = 0;
  *p_بیرون_len = 0;
  tinfl_init(&decomp);
  لكل ( ; ; )
  {
    size_t src_buf_اندازه = src_buf_len - src_buf_ofs, dst_buf_اندازه = بیرون_buf_ظرفیت - *p_بیرون_len, new_بیرون_buf_ظرفیت;
    tinfl_وضعیت وضعیت = tinfl_decompress(&decomp, (ثابت mz_uint8*)pSrc_buf + src_buf_ofs, &src_buf_اندازه, (mz_uint8*)pBuf, pBuf ? (mz_uint8*)pBuf + *p_بیرون_len : عدم, &dst_buf_اندازه,
      (flags & ~TINFL_FLAG_HAS_بیشتر_درون_داد) | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF);
    إذا ((وضعیت < 0) || (وضعیت == TINFL_وضعیت_NEEDS_بیشتر_درون_داد))
    {
      MZ_FREE(pBuf); *p_بیرون_len = 0; أرجع عدم;
    }
    src_buf_ofs += src_buf_اندازه;
    *p_بیرون_len += dst_buf_اندازه;
    إذا (وضعیت == TINFL_وضعیت_انجامشده) اكسر;
    new_بیرون_buf_ظرفیت = بیرون_buf_ظرفیت * 2; إذا (new_بیرون_buf_ظرفیت < 128) new_بیرون_buf_ظرفیت = 128;
    pNew_buf = MZ_REALLOC(pBuf, new_بیرون_buf_ظرفیت);
    إذا (!pNew_buf)
    {
      MZ_FREE(pBuf); *p_بیرون_len = 0; أرجع عدم;
    }
    pBuf = pNew_buf; بیرون_buf_ظرفیت = new_بیرون_buf_ظرفیت;
  }
  أرجع pBuf;
}

size_t tinfl_decompress_mem_مقصد_mem(فراغ *p_بیرون_buf, size_t بیرون_buf_len, ثابت فراغ *pSrc_buf, size_t src_buf_len, صحيح flags)
{
  tinfl_decompressor decomp; tinfl_وضعیت وضعیت; tinfl_init(&decomp);
  وضعیت = tinfl_decompress(&decomp, (ثابت mz_uint8*)pSrc_buf, &src_buf_len, (mz_uint8*)p_بیرون_buf, (mz_uint8*)p_بیرون_buf, &بیرون_buf_len, (flags & ~TINFL_FLAG_HAS_بیشتر_درون_داد) | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF);
  أرجع (وضعیت != TINFL_وضعیت_انجامشده) ? TINFL_DECOMPRESS_MEM_مقصد_MEM_FAILED : بیرون_buf_len;
}

صحيح tinfl_decompress_mem_مقصد_callback(ثابت فراغ *p_درون_buf, size_t *p_درون_buf_اندازه, tinfl_put_buf_func_ptr pPut_buf_func, فراغ *pPut_buf_user, صحيح flags)
{
  صحيح نتیجه = 0;
  tinfl_decompressor decomp;
  mz_uint8 *pDict = (mz_uint8*)MZ_MALLOC(TINFL_LZ_DICT_اندازه); size_t درون_buf_ofs = 0, dict_ofs = 0;
  إذا (!pDict)
    أرجع TINFL_وضعیت_FAILED;
  memset(pDict,0,TINFL_LZ_DICT_اندازه);
  tinfl_init(&decomp);
  لكل ( ; ; )
  {
    size_t درون_buf_اندازه = *p_درون_buf_اندازه - درون_buf_ofs, dst_buf_اندازه = TINFL_LZ_DICT_اندازه - dict_ofs;
    tinfl_وضعیت وضعیت = tinfl_decompress(&decomp, (ثابت mz_uint8*)p_درون_buf + درون_buf_ofs, &درون_buf_اندازه, pDict, pDict + dict_ofs, &dst_buf_اندازه,
      (flags & ~(TINFL_FLAG_HAS_بیشتر_درون_داد | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF)));
    درون_buf_ofs += درون_buf_اندازه;
    إذا ((dst_buf_اندازه) && (!(*pPut_buf_func)(pDict + dict_ofs, (صحيح)dst_buf_اندازه, pPut_buf_user)))
      اكسر;
    إذا (وضعیت != TINFL_وضعیت_HAS_بیشتر_OUTPUT)
    {
      نتیجه = (وضعیت == TINFL_وضعیت_انجامشده);
      اكسر;
    }
    dict_ofs = (dict_ofs + dst_buf_اندازه) & (TINFL_LZ_DICT_اندازه - 1);
  }
  MZ_FREE(pDict);
  *p_درون_buf_اندازه = درون_buf_ofs;
  أرجع نتیجه;
}
#پایان_اگر /*#ifndef MINIZ_NO_INFLATE_APIS*/

// ------------------- Low-level Compression (independent from all decompression API's)
#اگر_تعریف_نشده MINIZ_NO_DEFLATE_APIS

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
تعريفنوع بنية { mz_uint16 m_کلید, m_sym_شاخص; } tdefl_sym_freq;
ساكن tdefl_sym_freq* tdefl_radix_مرتب_سازی_syms(mz_uint رقم_syms, tdefl_sym_freq* pSyms0, tdefl_sym_freq* pSyms1)
{
  mz_uint32 مجموع_passes = 2, pass_لغزش, pass, i, hist[256 * 2]; tdefl_sym_freq* pCur_syms = pSyms0, *pNew_syms = pSyms1; MZ_CLEAR_ARR(hist);
  لكل (i = 0; i < رقم_syms; i++) { mz_uint freq = pSyms0[i].m_کلید; hist[freq & 0xFF]++; hist[256 + ((freq >> 8) & 0xFF)]++; }
  طالما ((مجموع_passes > 1) && (رقم_syms == hist[(مجموع_passes - 1) * 256])) مجموع_passes--;
  لكل (pass_لغزش = 0, pass = 0; pass < مجموع_passes; pass++, pass_لغزش += 8)
  {
    ثابت mz_uint32* pHist = &hist[pass << 8];
    mz_uint offsets[256], cur_ofs = 0;
    لكل (i = 0; i < 256; i++) { offsets[i] = cur_ofs; cur_ofs += pHist[i]; }
    لكل (i = 0; i < رقم_syms; i++) pNew_syms[offsets[(pCur_syms[i].m_کلید >> pass_لغزش) & 0xFF]++] = pCur_syms[i];
    { tdefl_sym_freq* t = pCur_syms; pCur_syms = pNew_syms; pNew_syms = t; }
  }
  أرجع pCur_syms;
}

// tdefl_calculate_minimum_redundancy() originally written by: Alistair Moffat, alistair@cs.mu.oz.au, Jyrki Katajainen, jyrki@diku.dk, November 1996.
ساكن فراغ tdefl_calculate_minimum_redundancy(tdefl_sym_freq *A, صحيح n)
{
  صحيح ریشه, برگ, بعدی, avbl, استفاده_شده, dpth;
  إذا (n==0) أرجع; وإلا إذا (n==1) { A[0].m_کلید = 1; أرجع; }
  A[0].m_کلید += A[1].m_کلید; ریشه = 0; برگ = 2;
  لكل (بعدی=1; بعدی < n-1; بعدی++)
  {
    إذا (برگ>=n || A[ریشه].m_کلید<A[برگ].m_کلید) { A[بعدی].m_کلید = A[ریشه].m_کلید; A[ریشه++].m_کلید = (mz_uint16)بعدی; } وإلا A[بعدی].m_کلید = A[برگ++].m_کلید;
    إذا (برگ>=n || (ریشه<بعدی && A[ریشه].m_کلید<A[برگ].m_کلید)) { A[بعدی].m_کلید = (mz_uint16)(A[بعدی].m_کلید + A[ریشه].m_کلید); A[ریشه++].m_کلید = (mz_uint16)بعدی; } وإلا A[بعدی].m_کلید = (mz_uint16)(A[بعدی].m_کلید + A[برگ++].m_کلید);
  }
  A[n-2].m_کلید = 0; لكل (بعدی=n-3; بعدی>=0; بعدی--) A[بعدی].m_کلید = A[A[بعدی].m_کلید].m_کلید+1;
  avbl = 1; استفاده_شده = dpth = 0; ریشه = n-2; بعدی = n-1;
  طالما (avbl>0)
  {
    طالما (ریشه>=0 && (صحيح)A[ریشه].m_کلید==dpth) { استفاده_شده++; ریشه--; }
    طالما (avbl>استفاده_شده) { A[بعدی--].m_کلید = (mz_uint16)(dpth); avbl--; }
    avbl = 2*استفاده_شده; dpth++; استفاده_شده = 0;
  }
}

// Limits canonical Huffman code table's max code size.
تعداد { TDEFL_MAX_SUPPORTED_HUFF_CODESIZE = 32 };
ساكن فراغ tdefl_huffman_enforce_max_کد_اندازه(صحيح *p_رقم_codes, صحيح کد_list_len, صحيح max_کد_اندازه)
{
  صحيح i; mz_uint32 مجموع = 0; إذا (کد_list_len <= 1) أرجع;
  لكل (i = max_کد_اندازه + 1; i <= TDEFL_MAX_SUPPORTED_HUFF_CODESIZE; i++) p_رقم_codes[max_کد_اندازه] += p_رقم_codes[i];
  لكل (i = max_کد_اندازه; i > 0; i--) مجموع += (((mz_uint32)p_رقم_codes[i]) << (max_کد_اندازه - i));
  طالما (مجموع != (1UL << max_کد_اندازه))
  {
    p_رقم_codes[max_کد_اندازه]--;
    لكل (i = max_کد_اندازه - 1; i > 0; i--) إذا (p_رقم_codes[i]) { p_رقم_codes[i]--; p_رقم_codes[i + 1] += 2; اكسر; }
    مجموع--;
  }
}

ساكن فراغ tdefl_optimize_huffman_جدول(tdefl_compressor *d, صحيح جدول_رقم, صحيح جدول_len, صحيح کد_اندازه_حد, صحيح static_جدول)
{
  صحيح i, j, l, رقم_codes[1 + TDEFL_MAX_SUPPORTED_HUFF_CODESIZE]; mz_uint بعدی_کد[TDEFL_MAX_SUPPORTED_HUFF_CODESIZE + 1]; MZ_CLEAR_ARR(رقم_codes);
  إذا (static_جدول)
  {
    لكل (i = 0; i < جدول_len; i++) رقم_codes[d->m_huff_کد_sizes[جدول_رقم][i]]++;
  }
  وإلا
  {
    tdefl_sym_freq syms0[TDEFL_MAX_HUFF_SYMBOLS], syms1[TDEFL_MAX_HUFF_SYMBOLS], *pSyms;
    صحيح رقم_استفاده_شده_syms = 0;
    ثابت mz_uint16 *p_Sym_شمار = &d->m_huff_شمار[جدول_رقم][0];
    لكل (i = 0; i < جدول_len; i++) إذا (p_Sym_شمار[i]) { syms0[رقم_استفاده_شده_syms].m_کلید = (mz_uint16)p_Sym_شمار[i]; syms0[رقم_استفاده_شده_syms++].m_sym_شاخص = (mz_uint16)i; }

    pSyms = tdefl_radix_مرتب_سازی_syms(رقم_استفاده_شده_syms, syms0, syms1); tdefl_calculate_minimum_redundancy(pSyms, رقم_استفاده_شده_syms);

    لكل (i = 0; i < رقم_استفاده_شده_syms; i++) رقم_codes[pSyms[i].m_کلید]++;

    tdefl_huffman_enforce_max_کد_اندازه(رقم_codes, رقم_استفاده_شده_syms, کد_اندازه_حد);

    MZ_CLEAR_ARR(d->m_huff_کد_sizes[جدول_رقم]); MZ_CLEAR_ARR(d->m_huff_codes[جدول_رقم]);
    لكل (i = 1, j = رقم_استفاده_شده_syms; i <= کد_اندازه_حد; i++)
      لكل (l = رقم_codes[i]; l > 0; l--) d->m_huff_کد_sizes[جدول_رقم][pSyms[--j].m_sym_شاخص] = (mz_uint8)(i);
  }

  بعدی_کد[1] = 0; لكل (j = 0, i = 2; i <= کد_اندازه_حد; i++) بعدی_کد[i] = j = ((j + رقم_codes[i - 1]) << 1);

  لكل (i = 0; i < جدول_len; i++)
  {
    mz_uint rev_کد = 0, کد, کد_اندازه_2; إذا ((کد_اندازه_2 = d->m_huff_کد_sizes[جدول_رقم][i]) == 0) استمر;
    کد = بعدی_کد[کد_اندازه_2]++; لكل (l = کد_اندازه_2; l > 0; l--, کد >>= 1) rev_کد = (rev_کد << 1) | (کد & 1);
    d->m_huff_codes[جدول_رقم][i] = (mz_uint16)rev_کد;
  }
}

#تعریف_کن TDEFL_PUT_بیتها(b, l) افعل { \
  mz_uint بیتها = b; mz_uint len = l; MZ_ASSERT(بیتها <= ((1U << len) - 1U)); \
  d->m_بیت_میانگیر |= (بیتها << d->m_بیتها_درون); d->m_بیتها_درون += len; \
  طالما (d->m_بیتها_درون >= 8) { \
    إذا (d->m_pOutput_buf < d->m_p_Output_buf_انتها) \
      *d->m_pOutput_buf++ = (mz_uint8)(d->m_بیت_میانگیر); \
    d->m_بیت_میانگیر >>= 8; \
    d->m_بیتها_درون -= 8; \
  } \
} MZ_MACRO_انتها

#تعریف_کن TDEFL_RLE_PREV_کد_اندازه() افعل { \
  إذا (rle_repeat_شمار) { \
    إذا (rle_repeat_شمار < 3) { \
      d->m_huff_شمار[2][prev_کد_اندازه] = (mz_uint16)(d->m_huff_شمار[2][prev_کد_اندازه] + rle_repeat_شمار); \
      طالما (rle_repeat_شمار--) packed_کد_sizes[رقم_packed_کد_sizes++] = prev_کد_اندازه; \
    } وإلا { \
      d->m_huff_شمار[2][16] = (mz_uint16)(d->m_huff_شمار[2][16] + 1); packed_کد_sizes[رقم_packed_کد_sizes++] = 16; packed_کد_sizes[رقم_packed_کد_sizes++] = (mz_uint8)(rle_repeat_شمار - 3); \
  } rle_repeat_شمار = 0; } \
} MZ_MACRO_انتها

#تعریف_کن TDEFL_RLE_ZERO_کد_اندازه() افعل { \
  إذا (rle_z_شمار) { \
    إذا (rle_z_شمار < 3) { \
      d->m_huff_شمار[2][0] = (mz_uint16)(d->m_huff_شمار[2][0] + rle_z_شمار); طالما (rle_z_شمار--) packed_کد_sizes[رقم_packed_کد_sizes++] = 0; \
    } وإلا إذا (rle_z_شمار <= 10) { \
      d->m_huff_شمار[2][17] = (mz_uint16)(d->m_huff_شمار[2][17] + 1); packed_کد_sizes[رقم_packed_کد_sizes++] = 17; packed_کد_sizes[رقم_packed_کد_sizes++] = (mz_uint8)(rle_z_شمار - 3); \
    } وإلا { \
      d->m_huff_شمار[2][18] = (mz_uint16)(d->m_huff_شمار[2][18] + 1); packed_کد_sizes[رقم_packed_کد_sizes++] = 18; packed_کد_sizes[رقم_packed_کد_sizes++] = (mz_uint8)(rle_z_شمار - 11); \
  } rle_z_شمار = 0; } \
} MZ_MACRO_انتها

ساكن mz_uint8 s_tdefl_packed_کد_اندازه_syms_swizzle[] = { 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 };

ساكن فراغ tdefl_شروع_dynamic_بلوک(tdefl_compressor *d)
{
  صحيح رقم_lit_codes, رقم_dist_codes, رقم_بیت_lengths; mz_uint i, مجموع_کد_sizes_مقصد_pack, رقم_packed_کد_sizes, rle_z_شمار, rle_repeat_شمار, packed_کد_sizes_شاخص;
  mz_uint8 کد_sizes_مقصد_pack[TDEFL_MAX_HUFF_SYMBOLS_0 + TDEFL_MAX_HUFF_SYMBOLS_1], packed_کد_sizes[TDEFL_MAX_HUFF_SYMBOLS_0 + TDEFL_MAX_HUFF_SYMBOLS_1], prev_کد_اندازه = 0xFF;

  d->m_huff_شمار[0][256] = 1;

  tdefl_optimize_huffman_جدول(d, 0, TDEFL_MAX_HUFF_SYMBOLS_0, 15, MZ_FALSE);
  tdefl_optimize_huffman_جدول(d, 1, TDEFL_MAX_HUFF_SYMBOLS_1, 15, MZ_FALSE);

  لكل (رقم_lit_codes = 286; رقم_lit_codes > 257; رقم_lit_codes--) إذا (d->m_huff_کد_sizes[0][رقم_lit_codes - 1]) اكسر;
  لكل (رقم_dist_codes = 30; رقم_dist_codes > 1; رقم_dist_codes--) إذا (d->m_huff_کد_sizes[1][رقم_dist_codes - 1]) اكسر;

  کپی_حافظه(کد_sizes_مقصد_pack, &d->m_huff_کد_sizes[0][0], رقم_lit_codes);
  کپی_حافظه(کد_sizes_مقصد_pack + رقم_lit_codes, &d->m_huff_کد_sizes[1][0], رقم_dist_codes);
  مجموع_کد_sizes_مقصد_pack = رقم_lit_codes + رقم_dist_codes; رقم_packed_کد_sizes = 0; rle_z_شمار = 0; rle_repeat_شمار = 0;

  memset(&d->m_huff_شمار[2][0], 0, حجم(d->m_huff_شمار[2][0]) * TDEFL_MAX_HUFF_SYMBOLS_2);
  لكل (i = 0; i < مجموع_کد_sizes_مقصد_pack; i++)
  {
    mz_uint8 کد_اندازه_2 = کد_sizes_مقصد_pack[i];
    إذا (!کد_اندازه_2)
    {
      TDEFL_RLE_PREV_کد_اندازه();
      إذا (++rle_z_شمار == 138) { TDEFL_RLE_ZERO_کد_اندازه(); }
    }
    وإلا
    {
      TDEFL_RLE_ZERO_کد_اندازه();
      إذا (کد_اندازه_2 != prev_کد_اندازه)
      {
        TDEFL_RLE_PREV_کد_اندازه();
        d->m_huff_شمار[2][کد_اندازه_2] = (mz_uint16)(d->m_huff_شمار[2][کد_اندازه_2] + 1); packed_کد_sizes[رقم_packed_کد_sizes++] = کد_اندازه_2;
      }
      وإلا إذا (++rle_repeat_شمار == 6)
      {
        TDEFL_RLE_PREV_کد_اندازه();
      }
    }
    prev_کد_اندازه = کد_اندازه_2;
  }
  إذا (rle_repeat_شمار) { TDEFL_RLE_PREV_کد_اندازه(); } وإلا { TDEFL_RLE_ZERO_کد_اندازه(); }

  tdefl_optimize_huffman_جدول(d, 2, TDEFL_MAX_HUFF_SYMBOLS_2, 7, MZ_FALSE);

  TDEFL_PUT_بیتها(2, 2);

  TDEFL_PUT_بیتها(رقم_lit_codes - 257, 5);
  TDEFL_PUT_بیتها(رقم_dist_codes - 1, 5);

  لكل (رقم_بیت_lengths = 18; رقم_بیت_lengths >= 0; رقم_بیت_lengths--) إذا (d->m_huff_کد_sizes[2][s_tdefl_packed_کد_اندازه_syms_swizzle[رقم_بیت_lengths]]) اكسر;
  رقم_بیت_lengths = MZ_MAX(4, (رقم_بیت_lengths + 1)); TDEFL_PUT_بیتها(رقم_بیت_lengths - 4, 4);
  لكل (i = 0; (صحيح)i < رقم_بیت_lengths; i++) TDEFL_PUT_بیتها(d->m_huff_کد_sizes[2][s_tdefl_packed_کد_اندازه_syms_swizzle[i]], 3);

  لكل (packed_کد_sizes_شاخص = 0; packed_کد_sizes_شاخص < رقم_packed_کد_sizes; )
  {
    mz_uint کد = packed_کد_sizes[packed_کد_sizes_شاخص++]; MZ_ASSERT(کد < TDEFL_MAX_HUFF_SYMBOLS_2);
    TDEFL_PUT_بیتها(d->m_huff_codes[2][کد], d->m_huff_کد_sizes[2][کد]);
    إذا (کد >= 16) TDEFL_PUT_بیتها(packed_کد_sizes[packed_کد_sizes_شاخص++], "\02\03\07"[کد - 16]);
  }
}

ساكن فراغ tdefl_شروع_static_بلوک(tdefl_compressor *d)
{
  mz_uint i;
  mz_uint8 *p = &d->m_huff_کد_sizes[0][0];

  لكل (i = 0; i <= 143; ++i) *p++ = 8;
  لكل ( ; i <= 255; ++i) *p++ = 9;
  لكل ( ; i <= 279; ++i) *p++ = 7;
  لكل ( ; i <= 287; ++i) *p++ = 8;

  memset(d->m_huff_کد_sizes[1], 5, 32);

  tdefl_optimize_huffman_جدول(d, 0, 288, 15, MZ_TRUE);
  tdefl_optimize_huffman_جدول(d, 1, 32, 15, MZ_TRUE);

  TDEFL_PUT_بیتها(1, 2);
}

ساكن ثابت mz_uint mz_bitmasks[17] = { 0x0000, 0x0001, 0x0003, 0x0007, 0x000F, 0x001F, 0x003F, 0x007F, 0x00FF, 0x01FF, 0x03FF, 0x07FF, 0x0FFF, 0x1FFF, 0x3FFF, 0x7FFF, 0xFFFF };

#إذا MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN && MINIZ_HAS_64_بیت_REGISTERS
ساكن mz_bool tdefl_compress_lz_codes(tdefl_compressor *d)
{
  mz_uint flags;
  mz_uint8 *pLZ_codes;
  mz_uint8 *pOutput_buf = d->m_pOutput_buf;
  mz_uint8 *p_LZ_کد_buf_انتها = d->m_p_LZ_کد_buf;
  mz_uint64 بیت_میانگیر = d->m_بیت_میانگیر;
  mz_uint بیتها_درون = d->m_بیتها_درون;

#تعریف_کن TDEFL_PUT_بیتها_FAST(b, l) { بیت_میانگیر |= (((mz_uint64)(b)) << بیتها_درون); بیتها_درون += (l); }

  flags = 1;
  لكل (pLZ_codes = d->m_lz_کد_buf; pLZ_codes < p_LZ_کد_buf_انتها; flags >>= 1)
  {
    إذا (flags == 1)
      flags = *pLZ_codes++ | 0x100;

    إذا (flags & 1)
    {
      mz_uint s0, s1, n0, n1, sym, رقم_extra_بیتها;
      mz_uint تطابق_len = pLZ_codes[0], تطابق_dist = *(ثابت mz_uint16 *)(pLZ_codes + 1); pLZ_codes += 3;

      MZ_ASSERT(d->m_huff_کد_sizes[0][s_tdefl_len_sym[تطابق_len]]);
      TDEFL_PUT_بیتها_FAST(d->m_huff_codes[0][s_tdefl_len_sym[تطابق_len]], d->m_huff_کد_sizes[0][s_tdefl_len_sym[تطابق_len]]);
      TDEFL_PUT_بیتها_FAST(تطابق_len & mz_bitmasks[s_tdefl_len_extra[تطابق_len]], s_tdefl_len_extra[تطابق_len]);

      // This sequence coaxes MSVC into using cmov's vs. jmp's.
      s0 = s_tdefl_small_dist_sym[تطابق_dist & 511];
      n0 = s_tdefl_small_dist_extra[تطابق_dist & 511];
      s1 = s_tdefl_large_dist_sym[تطابق_dist >> 8];
      n1 = s_tdefl_large_dist_extra[تطابق_dist >> 8];
      sym = (تطابق_dist < 512) ? s0 : s1;
      رقم_extra_بیتها = (تطابق_dist < 512) ? n0 : n1;

      MZ_ASSERT(d->m_huff_کد_sizes[1][sym]);
      TDEFL_PUT_بیتها_FAST(d->m_huff_codes[1][sym], d->m_huff_کد_sizes[1][sym]);
      TDEFL_PUT_بیتها_FAST(تطابق_dist & mz_bitmasks[رقم_extra_بیتها], رقم_extra_بیتها);
    }
    وإلا
    {
      mz_uint lit = *pLZ_codes++;
      MZ_ASSERT(d->m_huff_کد_sizes[0][lit]);
      TDEFL_PUT_بیتها_FAST(d->m_huff_codes[0][lit], d->m_huff_کد_sizes[0][lit]);

      إذا (((flags & 2) == 0) && (pLZ_codes < p_LZ_کد_buf_انتها))
      {
        flags >>= 1;
        lit = *pLZ_codes++;
        MZ_ASSERT(d->m_huff_کد_sizes[0][lit]);
        TDEFL_PUT_بیتها_FAST(d->m_huff_codes[0][lit], d->m_huff_کد_sizes[0][lit]);

        إذا (((flags & 2) == 0) && (pLZ_codes < p_LZ_کد_buf_انتها))
        {
          flags >>= 1;
          lit = *pLZ_codes++;
          MZ_ASSERT(d->m_huff_کد_sizes[0][lit]);
          TDEFL_PUT_بیتها_FAST(d->m_huff_codes[0][lit], d->m_huff_کد_sizes[0][lit]);
        }
      }
    }

    إذا (pOutput_buf >= d->m_p_Output_buf_انتها)
      أرجع MZ_FALSE;

    *(mz_uint64*)pOutput_buf = بیت_میانگیر;
    pOutput_buf += (بیتها_درون >> 3);
    بیت_میانگیر >>= (بیتها_درون & ~7);
    بیتها_درون &= 7;
  }

#لغو_تعریف TDEFL_PUT_بیتها_FAST

  d->m_pOutput_buf = pOutput_buf;
  d->m_بیتها_درون = 0;
  d->m_بیت_میانگیر = 0;

  طالما (بیتها_درون)
  {
    mz_uint32 n = MZ_MIN(بیتها_درون, 16);
    TDEFL_PUT_بیتها((mz_uint)بیت_میانگیر & mz_bitmasks[n], n);
    بیت_میانگیر >>= n;
    بیتها_درون -= n;
  }

  TDEFL_PUT_بیتها(d->m_huff_codes[0][256], d->m_huff_کد_sizes[0][256]);

  أرجع (d->m_pOutput_buf < d->m_p_Output_buf_انتها);
}
#وإلا
ساكن mz_bool tdefl_compress_lz_codes(tdefl_compressor *d)
{
  mz_uint flags;
  mz_uint8 *pLZ_codes;

  flags = 1;
  لكل (pLZ_codes = d->m_lz_کد_buf; pLZ_codes < d->m_p_LZ_کد_buf; flags >>= 1)
  {
    إذا (flags == 1)
      flags = *pLZ_codes++ | 0x100;
    إذا (flags & 1)
    {
      mz_uint sym, رقم_extra_بیتها;
      mz_uint تطابق_len = pLZ_codes[0], تطابق_dist = (pLZ_codes[1] | (pLZ_codes[2] << 8)); pLZ_codes += 3;

      MZ_ASSERT(d->m_huff_کد_sizes[0][s_tdefl_len_sym[تطابق_len]]);
      TDEFL_PUT_بیتها(d->m_huff_codes[0][s_tdefl_len_sym[تطابق_len]], d->m_huff_کد_sizes[0][s_tdefl_len_sym[تطابق_len]]);
      TDEFL_PUT_بیتها(تطابق_len & mz_bitmasks[s_tdefl_len_extra[تطابق_len]], s_tdefl_len_extra[تطابق_len]);

      إذا (تطابق_dist < 512)
      {
        sym = s_tdefl_small_dist_sym[تطابق_dist]; رقم_extra_بیتها = s_tdefl_small_dist_extra[تطابق_dist];
      }
      وإلا
      {
        sym = s_tdefl_large_dist_sym[تطابق_dist >> 8]; رقم_extra_بیتها = s_tdefl_large_dist_extra[تطابق_dist >> 8];
      }
      MZ_ASSERT(d->m_huff_کد_sizes[1][sym]);
      TDEFL_PUT_بیتها(d->m_huff_codes[1][sym], d->m_huff_کد_sizes[1][sym]);
      TDEFL_PUT_بیتها(تطابق_dist & mz_bitmasks[رقم_extra_بیتها], رقم_extra_بیتها);
    }
    وإلا
    {
      mz_uint lit = *pLZ_codes++;
      MZ_ASSERT(d->m_huff_کد_sizes[0][lit]);
      TDEFL_PUT_بیتها(d->m_huff_codes[0][lit], d->m_huff_کد_sizes[0][lit]);
    }
  }

  TDEFL_PUT_بیتها(d->m_huff_codes[0][256], d->m_huff_کد_sizes[0][256]);

  أرجع (d->m_pOutput_buf < d->m_p_Output_buf_انتها);
}
#پایان_اگر // MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN && MINIZ_HAS_64BIT_REGISTERS

ساكن mz_bool tdefl_compress_بلوک(tdefl_compressor *d, mz_bool static_بلوک)
{
  إذا (static_بلوک)
    tdefl_شروع_static_بلوک(d);
  وإلا
    tdefl_شروع_dynamic_بلوک(d);
  أرجع tdefl_compress_lz_codes(d);
}

ساكن صحيح tdefl_flush_بلوک(tdefl_compressor *d, صحيح flush)
{
  mz_uint saved_بیت_buf, saved_بیتها_درون;
  mz_uint8 *pSaved_output_buf;
  mz_bool comp_بلوک_succeeded = MZ_FALSE;
  صحيح n, use_raw_بلوک = ((d->m_flags & TDEFL_FORCE_ALL_RAW_بلوکها) != 0) && (d->m_lookahead_pos - d->m_lz_کد_buf_dict_pos) <= d->m_dict_اندازه;
  mz_uint8 *p_Output_buf_شروع = ((d->m_pPut_buf_func == عدم) && ((*d->m_p_بیرون_buf_اندازه - d->m_بیرون_buf_ofs) >= TDEFL_بیرون_BUF_اندازه)) ? ((mz_uint8 *)d->m_p_بیرون_buf + d->m_بیرون_buf_ofs) : d->m_output_buf;

  d->m_pOutput_buf = p_Output_buf_شروع;
  d->m_p_Output_buf_انتها = d->m_pOutput_buf + TDEFL_بیرون_BUF_اندازه - 16;

  MZ_ASSERT(!d->m_output_flush_مانده);
  d->m_output_flush_ofs = 0;
  d->m_output_flush_مانده = 0;

  *d->m_pLZ_flags = (mz_uint8)(*d->m_pLZ_flags >> d->m_رقم_flags_چپ);
  d->m_p_LZ_کد_buf -= (d->m_رقم_flags_چپ == 8);

  إذا ((d->m_flags & TDEFL_WRITE_ZLIB_سرآیند) && (!d->m_بلوک_شاخص))
  {
    TDEFL_PUT_بیتها(0x78, 8); TDEFL_PUT_بیتها(0x01, 8);
  }

  TDEFL_PUT_بیتها(flush == TDEFL_پایان, 1);

  pSaved_output_buf = d->m_pOutput_buf; saved_بیت_buf = d->m_بیت_میانگیر; saved_بیتها_درون = d->m_بیتها_درون;

  إذا (!use_raw_بلوک)
    comp_بلوک_succeeded = tdefl_compress_بلوک(d, (d->m_flags & TDEFL_FORCE_ALL_STATIC_بلوکها) || (d->m_مجموع_lz_بایتها < 48));

  // If the block gets expanded, forget the current contents of the output buffer and send a raw block instead.
  إذا ( ((use_raw_بلوک) || ((d->m_مجموع_lz_بایتها) && ((d->m_pOutput_buf - pSaved_output_buf + 1U) >= d->m_مجموع_lz_بایتها))) &&
       ((d->m_lookahead_pos - d->m_lz_کد_buf_dict_pos) <= d->m_dict_اندازه) )
  {
    mz_uint i; d->m_pOutput_buf = pSaved_output_buf; d->m_بیت_میانگیر = saved_بیت_buf; d->m_بیتها_درون = saved_بیتها_درون;
    TDEFL_PUT_بیتها(0, 2);
    إذا (d->m_بیتها_درون) { TDEFL_PUT_بیتها(0, 8 - d->m_بیتها_درون); }
    لكل (i = 2; i; --i, d->m_مجموع_lz_بایتها ^= 0xFFFF)
    {
      TDEFL_PUT_بیتها(d->m_مجموع_lz_بایتها & 0xFFFF, 16);
    }
    لكل (i = 0; i < d->m_مجموع_lz_بایتها; ++i)
    {
      TDEFL_PUT_بیتها(d->m_dict[(d->m_lz_کد_buf_dict_pos + i) & TDEFL_LZ_DICT_اندازه_ماسک], 8);
    }
  }
  // Check for the extremely unlikely (if not impossible) case of the compressed block not fitting into the output buffer when using dynamic codes.
  وإلا إذا (!comp_بلوک_succeeded)
  {
    d->m_pOutput_buf = pSaved_output_buf; d->m_بیت_میانگیر = saved_بیت_buf; d->m_بیتها_درون = saved_بیتها_درون;
    tdefl_compress_بلوک(d, MZ_TRUE);
  }

  إذا (flush)
  {
    إذا (flush == TDEFL_پایان)
    {
      إذا (d->m_بیتها_درون) { TDEFL_PUT_بیتها(0, 8 - d->m_بیتها_درون); }
      إذا (d->m_flags & TDEFL_WRITE_ZLIB_سرآیند) { mz_uint i, a = d->m_adler32; لكل (i = 0; i < 4; i++) { TDEFL_PUT_بیتها((a >> 24) & 0xFF, 8); a <<= 8; } }
    }
    وإلا
    {
      mz_uint i, z = 0; TDEFL_PUT_بیتها(0, 3); إذا (d->m_بیتها_درون) { TDEFL_PUT_بیتها(0, 8 - d->m_بیتها_درون); } لكل (i = 2; i; --i, z ^= 0xFFFF) { TDEFL_PUT_بیتها(z & 0xFFFF, 16); }
    }
  }

  MZ_ASSERT(d->m_pOutput_buf < d->m_p_Output_buf_انتها);

  memset(&d->m_huff_شمار[0][0], 0, حجم(d->m_huff_شمار[0][0]) * TDEFL_MAX_HUFF_SYMBOLS_0);
  memset(&d->m_huff_شمار[1][0], 0, حجم(d->m_huff_شمار[1][0]) * TDEFL_MAX_HUFF_SYMBOLS_1);

  d->m_p_LZ_کد_buf = d->m_lz_کد_buf + 1; d->m_pLZ_flags = d->m_lz_کد_buf; d->m_رقم_flags_چپ = 8; d->m_lz_کد_buf_dict_pos += d->m_مجموع_lz_بایتها; d->m_مجموع_lz_بایتها = 0; d->m_بلوک_شاخص++;

  إذا ((n = (صحيح)(d->m_pOutput_buf - p_Output_buf_شروع)) != 0)
  {
    إذا (d->m_pPut_buf_func)
    {
      *d->m_p_درون_buf_اندازه = d->m_pSrc - (ثابت mz_uint8 *)d->m_p_درون_buf;
      إذا (!(*d->m_pPut_buf_func)(d->m_output_buf, n, d->m_pPut_buf_user))
        أرجع (d->m_prev_return_وضعیت = TDEFL_وضعیت_PUT_BUF_FAILED);
    }
    وإلا إذا (p_Output_buf_شروع == d->m_output_buf)
    {
      صحيح بایتها_مقصد_copy = (صحيح)MZ_MIN((size_t)n, (size_t)(*d->m_p_بیرون_buf_اندازه - d->m_بیرون_buf_ofs));
      کپی_حافظه((mz_uint8 *)d->m_p_بیرون_buf + d->m_بیرون_buf_ofs, d->m_output_buf, بایتها_مقصد_copy);
      d->m_بیرون_buf_ofs += بایتها_مقصد_copy;
      إذا ((n -= بایتها_مقصد_copy) != 0)
      {
        d->m_output_flush_ofs = بایتها_مقصد_copy;
        d->m_output_flush_مانده = n;
      }
    }
    وإلا
    {
      d->m_بیرون_buf_ofs += n;
    }
  }

  أرجع d->m_output_flush_مانده;
}

#إذا MINIZ_USE_UNALIGNED_LOADS_AND_STORES
#تعریف_کن TDEFL_READ_UNALIGNED_کلمه(p) *(ثابت mz_uint16*)(p)
ساكن MZ_FORCEINLINE فراغ tdefl_پیدا_کن_تطابق(tdefl_compressor *d, mz_uint lookahead_pos, mz_uint max_dist, mz_uint max_تطابق_len, mz_uint *p_تطابق_dist, mz_uint *p_تطابق_len)
{
  mz_uint dist, pos = lookahead_pos & TDEFL_LZ_DICT_اندازه_ماسک, تطابق_len = *p_تطابق_len, probe_pos = pos, بعدی_probe_pos, probe_len;
  mz_uint رقم_probes_چپ = d->m_max_probes[تطابق_len >= 32];
  ثابت mz_uint16 *s = (ثابت mz_uint16*)(d->m_dict + pos), *p, *q;
  mz_uint16 c01 = TDEFL_READ_UNALIGNED_کلمه(&d->m_dict[pos + تطابق_len - 1]), s01 = TDEFL_READ_UNALIGNED_کلمه(s);
  MZ_ASSERT(max_تطابق_len <= TDEFL_MAX_تطابق_LEN); إذا (max_تطابق_len <= تطابق_len) أرجع;
  لكل ( ; ; )
  {
    لكل ( ; ; )
    {
      إذا (--رقم_probes_چپ == 0) أرجع;
      #تعریف_کن TDEFL_PROBE \
        بعدی_probe_pos = d->m_بعدی[probe_pos]; \
        إذا ((!بعدی_probe_pos) || ((dist = (mz_uint16)(lookahead_pos - بعدی_probe_pos)) > max_dist)) أرجع; \
        probe_pos = بعدی_probe_pos & TDEFL_LZ_DICT_اندازه_ماسک; \
        إذا (TDEFL_READ_UNALIGNED_کلمه(&d->m_dict[probe_pos + تطابق_len - 1]) == c01) اكسر;
      TDEFL_PROBE
      TDEFL_PROBE
      TDEFL_PROBE
    }
    إذا (!dist) اكسر;
    q = (ثابت mz_uint16*)(d->m_dict + probe_pos);
    إذا (TDEFL_READ_UNALIGNED_کلمه(q) != s01) استمر;
    p = s; probe_len = 32;
    افعل { } طالما ( (TDEFL_READ_UNALIGNED_کلمه(++p) == TDEFL_READ_UNALIGNED_کلمه(++q)) && (TDEFL_READ_UNALIGNED_کلمه(++p) == TDEFL_READ_UNALIGNED_کلمه(++q)) &&
                   (TDEFL_READ_UNALIGNED_کلمه(++p) == TDEFL_READ_UNALIGNED_کلمه(++q)) && (TDEFL_READ_UNALIGNED_کلمه(++p) == TDEFL_READ_UNALIGNED_کلمه(++q)) && (--probe_len > 0) );
    إذا (!probe_len)
    {
      *p_تطابق_dist = dist; *p_تطابق_len = MZ_MIN(max_تطابق_len, TDEFL_MAX_تطابق_LEN); اكسر;
    }
    وإلا إذا ((probe_len = ((mz_uint)(p - s) * 2) + (mz_uint)(*(ثابت mz_uint8*)p == *(ثابت mz_uint8*)q)) > تطابق_len)
    {
      *p_تطابق_dist = dist; إذا ((*p_تطابق_len = تطابق_len = MZ_MIN(max_تطابق_len, probe_len)) == max_تطابق_len) اكسر;
      c01 = TDEFL_READ_UNALIGNED_کلمه(&d->m_dict[pos + تطابق_len - 1]);
    }
  }
}
#وإلا
ساكن MZ_FORCEINLINE فراغ tdefl_پیدا_کن_تطابق(tdefl_compressor *d, mz_uint lookahead_pos, mz_uint max_dist, mz_uint max_تطابق_len, mz_uint *p_تطابق_dist, mz_uint *p_تطابق_len)
{
  mz_uint dist, pos = lookahead_pos & TDEFL_LZ_DICT_اندازه_ماسک, تطابق_len = *p_تطابق_len, probe_pos = pos, بعدی_probe_pos, probe_len;
  mz_uint رقم_probes_چپ = d->m_max_probes[تطابق_len >= 32];
  ثابت mz_uint8 *s = d->m_dict + pos, *p, *q;
  mz_uint8 c0 = d->m_dict[pos + تطابق_len], c1 = d->m_dict[pos + تطابق_len - 1];
  MZ_ASSERT(max_تطابق_len <= TDEFL_MAX_تطابق_LEN); إذا (max_تطابق_len <= تطابق_len) أرجع;
  لكل ( ; ; )
  {
    لكل ( ; ; )
    {
      إذا (--رقم_probes_چپ == 0) أرجع;
      #تعریف_کن TDEFL_PROBE \
        بعدی_probe_pos = d->m_بعدی[probe_pos]; \
        إذا ((!بعدی_probe_pos) || ((dist = (mz_uint16)(lookahead_pos - بعدی_probe_pos)) > max_dist)) أرجع; \
        probe_pos = بعدی_probe_pos & TDEFL_LZ_DICT_اندازه_ماسک; \
        إذا ((d->m_dict[probe_pos + تطابق_len] == c0) && (d->m_dict[probe_pos + تطابق_len - 1] == c1)) اكسر;
      TDEFL_PROBE
      TDEFL_PROBE
      TDEFL_PROBE
    }
    إذا (!dist) اكسر;
    p = s; q = d->m_dict + probe_pos;
    لكل (probe_len = 0; probe_len < max_تطابق_len; probe_len++) {
        إذا (*p++ != *q++) اكسر;
    }
    إذا (probe_len > تطابق_len)
    {
      *p_تطابق_dist = dist;
      إذا ((*p_تطابق_len = تطابق_len = probe_len) == max_تطابق_len) أرجع;
      c0 = d->m_dict[pos + تطابق_len]; c1 = d->m_dict[pos + تطابق_len - 1];
    }
  }
}
#پایان_اگر // #if MINIZ_USE_UNALIGNED_LOADS_AND_STORES

#إذا MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
ساكن mz_bool tdefl_compress_fast(tdefl_compressor *d)
{
  // Faster, minimally featured LZRW1-style match+parse loop with better register utilization. Intended for applications where raw throughput is valued more highly than ratio.
  mz_uint lookahead_pos = d->m_lookahead_pos, lookahead_اندازه = d->m_lookahead_اندازه, dict_اندازه = d->m_dict_اندازه, مجموع_lz_بایتها = d->m_مجموع_lz_بایتها, رقم_flags_چپ = d->m_رقم_flags_چپ;
  mz_uint8 *p_LZ_کد_buf = d->m_p_LZ_کد_buf, *pLZ_flags = d->m_pLZ_flags;
  mz_uint cur_pos = lookahead_pos & TDEFL_LZ_DICT_اندازه_ماسک;

  طالما ((d->m_src_buf_چپ) || ((d->m_flush) && (lookahead_اندازه)))
  {
    ثابت mz_uint TDEFL_COMP_FAST_LOOKAHEAD_اندازه = 4096;
    mz_uint dst_pos = (lookahead_pos + lookahead_اندازه) & TDEFL_LZ_DICT_اندازه_ماسک;
    mz_uint رقم_بایتها_مقصد_process = (mz_uint)MZ_MIN(d->m_src_buf_چپ, TDEFL_COMP_FAST_LOOKAHEAD_اندازه - lookahead_اندازه);
    d->m_src_buf_چپ -= رقم_بایتها_مقصد_process;
    lookahead_اندازه += رقم_بایتها_مقصد_process;

    طالما (رقم_بایتها_مقصد_process)
    {
      mz_uint32 n = MZ_MIN(TDEFL_LZ_DICT_اندازه - dst_pos, رقم_بایتها_مقصد_process);
      کپی_حافظه(d->m_dict + dst_pos, d->m_pSrc, n);
      إذا (dst_pos < (TDEFL_MAX_تطابق_LEN - 1))
        کپی_حافظه(d->m_dict + TDEFL_LZ_DICT_اندازه + dst_pos, d->m_pSrc, MZ_MIN(n, (TDEFL_MAX_تطابق_LEN - 1) - dst_pos));
      d->m_pSrc += n;
      dst_pos = (dst_pos + n) & TDEFL_LZ_DICT_اندازه_ماسک;
      رقم_بایتها_مقصد_process -= n;
    }

    dict_اندازه = MZ_MIN(TDEFL_LZ_DICT_اندازه - lookahead_اندازه, dict_اندازه);
    إذا ((!d->m_flush) && (lookahead_اندازه < TDEFL_COMP_FAST_LOOKAHEAD_اندازه)) اكسر;

    طالما (lookahead_اندازه >= 4)
    {
      mz_uint cur_تطابق_dist, cur_تطابق_len = 1;
      mz_uint8 *pCur_dict = d->m_dict + cur_pos;
      mz_uint اولی_trigram = (*(ثابت mz_uint32 *)pCur_dict) & 0xFFFFFF;
      mz_uint hash = (اولی_trigram ^ (اولی_trigram >> (24 - (TDEFL_LZ_HASH_بیتها - 8)))) & TDEFL_LEVEL1_HASH_اندازه_ماسک;
      mz_uint probe_pos = d->m_hash[hash];
      d->m_hash[hash] = (mz_uint16)lookahead_pos;

      إذا (((cur_تطابق_dist = (mz_uint16)(lookahead_pos - probe_pos)) <= dict_اندازه) && ((*(ثابت mz_uint32 *)(d->m_dict + (probe_pos &= TDEFL_LZ_DICT_اندازه_ماسک)) & 0xFFFFFF) == اولی_trigram))
      {
        ثابت mz_uint16 *p = (ثابت mz_uint16 *)pCur_dict;
        ثابت mz_uint16 *q = (ثابت mz_uint16 *)(d->m_dict + probe_pos);
        mz_uint32 probe_len = 32;
        افعل { } طالما ( (TDEFL_READ_UNALIGNED_کلمه(++p) == TDEFL_READ_UNALIGNED_کلمه(++q)) && (TDEFL_READ_UNALIGNED_کلمه(++p) == TDEFL_READ_UNALIGNED_کلمه(++q)) &&
          (TDEFL_READ_UNALIGNED_کلمه(++p) == TDEFL_READ_UNALIGNED_کلمه(++q)) && (TDEFL_READ_UNALIGNED_کلمه(++p) == TDEFL_READ_UNALIGNED_کلمه(++q)) && (--probe_len > 0) );
        cur_تطابق_len = ((mz_uint)(p - (ثابت mz_uint16 *)pCur_dict) * 2) + (mz_uint)(*(ثابت mz_uint8 *)p == *(ثابت mz_uint8 *)q);
        إذا (!probe_len)
          cur_تطابق_len = cur_تطابق_dist ? TDEFL_MAX_تطابق_LEN : 0;

        إذا ((cur_تطابق_len < TDEFL_MIN_تطابق_LEN) || ((cur_تطابق_len == TDEFL_MIN_تطابق_LEN) && (cur_تطابق_dist >= 8U*1024U)))
        {
          cur_تطابق_len = 1;
          *p_LZ_کد_buf++ = (mz_uint8)اولی_trigram;
          *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
          d->m_huff_شمار[0][(mz_uint8)اولی_trigram]++;
        }
        وإلا
        {
          mz_uint32 s0, s1;
          cur_تطابق_len = MZ_MIN(cur_تطابق_len, lookahead_اندازه);

          MZ_ASSERT((cur_تطابق_len >= TDEFL_MIN_تطابق_LEN) && (cur_تطابق_dist >= 1) && (cur_تطابق_dist <= TDEFL_LZ_DICT_اندازه));

          cur_تطابق_dist--;

          p_LZ_کد_buf[0] = (mz_uint8)(cur_تطابق_len - TDEFL_MIN_تطابق_LEN);
          *(mz_uint16 *)(&p_LZ_کد_buf[1]) = (mz_uint16)cur_تطابق_dist;
          p_LZ_کد_buf += 3;
          *pLZ_flags = (mz_uint8)((*pLZ_flags >> 1) | 0x80);

          s0 = s_tdefl_small_dist_sym[cur_تطابق_dist & 511];
          s1 = s_tdefl_large_dist_sym[cur_تطابق_dist >> 8];
          d->m_huff_شمار[1][(cur_تطابق_dist < 512) ? s0 : s1]++;

          d->m_huff_شمار[0][s_tdefl_len_sym[cur_تطابق_len - TDEFL_MIN_تطابق_LEN]]++;
        }
      }
      وإلا
      {
        *p_LZ_کد_buf++ = (mz_uint8)اولی_trigram;
        *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
        d->m_huff_شمار[0][(mz_uint8)اولی_trigram]++;
      }

      إذا (--رقم_flags_چپ == 0) { رقم_flags_چپ = 8; pLZ_flags = p_LZ_کد_buf++; }

      مجموع_lz_بایتها += cur_تطابق_len;
      lookahead_pos += cur_تطابق_len;
      dict_اندازه = MZ_MIN(dict_اندازه + cur_تطابق_len, TDEFL_LZ_DICT_اندازه);
      cur_pos = (cur_pos + cur_تطابق_len) & TDEFL_LZ_DICT_اندازه_ماسک;
      MZ_ASSERT(lookahead_اندازه >= cur_تطابق_len);
      lookahead_اندازه -= cur_تطابق_len;

      إذا (p_LZ_کد_buf > &d->m_lz_کد_buf[TDEFL_LZ_کد_BUF_اندازه - 8])
      {
        صحيح n;
        d->m_lookahead_pos = lookahead_pos; d->m_lookahead_اندازه = lookahead_اندازه; d->m_dict_اندازه = dict_اندازه;
        d->m_مجموع_lz_بایتها = مجموع_lz_بایتها; d->m_p_LZ_کد_buf = p_LZ_کد_buf; d->m_pLZ_flags = pLZ_flags; d->m_رقم_flags_چپ = رقم_flags_چپ;
        إذا ((n = tdefl_flush_بلوک(d, 0)) != 0)
          أرجع (n < 0) ? MZ_FALSE : MZ_TRUE;
        مجموع_lz_بایتها = d->m_مجموع_lz_بایتها; p_LZ_کد_buf = d->m_p_LZ_کد_buf; pLZ_flags = d->m_pLZ_flags; رقم_flags_چپ = d->m_رقم_flags_چپ;
      }
    }

    طالما (lookahead_اندازه)
    {
      mz_uint8 lit = d->m_dict[cur_pos];

      مجموع_lz_بایتها++;
      *p_LZ_کد_buf++ = lit;
      *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
      إذا (--رقم_flags_چپ == 0) { رقم_flags_چپ = 8; pLZ_flags = p_LZ_کد_buf++; }

      d->m_huff_شمار[0][lit]++;

      lookahead_pos++;
      dict_اندازه = MZ_MIN(dict_اندازه + 1, TDEFL_LZ_DICT_اندازه);
      cur_pos = (cur_pos + 1) & TDEFL_LZ_DICT_اندازه_ماسک;
      lookahead_اندازه--;

      إذا (p_LZ_کد_buf > &d->m_lz_کد_buf[TDEFL_LZ_کد_BUF_اندازه - 8])
      {
        صحيح n;
        d->m_lookahead_pos = lookahead_pos; d->m_lookahead_اندازه = lookahead_اندازه; d->m_dict_اندازه = dict_اندازه;
        d->m_مجموع_lz_بایتها = مجموع_lz_بایتها; d->m_p_LZ_کد_buf = p_LZ_کد_buf; d->m_pLZ_flags = pLZ_flags; d->m_رقم_flags_چپ = رقم_flags_چپ;
        إذا ((n = tdefl_flush_بلوک(d, 0)) != 0)
          أرجع (n < 0) ? MZ_FALSE : MZ_TRUE;
        مجموع_lz_بایتها = d->m_مجموع_lz_بایتها; p_LZ_کد_buf = d->m_p_LZ_کد_buf; pLZ_flags = d->m_pLZ_flags; رقم_flags_چپ = d->m_رقم_flags_چپ;
      }
    }
  }

  d->m_lookahead_pos = lookahead_pos; d->m_lookahead_اندازه = lookahead_اندازه; d->m_dict_اندازه = dict_اندازه;
  d->m_مجموع_lz_بایتها = مجموع_lz_بایتها; d->m_p_LZ_کد_buf = p_LZ_کد_buf; d->m_pLZ_flags = pLZ_flags; d->m_رقم_flags_چپ = رقم_flags_چپ;
  أرجع MZ_TRUE;
}
#پایان_اگر // MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN

ساكن MZ_FORCEINLINE فراغ tdefl_رکورد_literal(tdefl_compressor *d, mz_uint8 lit)
{
  d->m_مجموع_lz_بایتها++;
  *d->m_p_LZ_کد_buf++ = lit;
  *d->m_pLZ_flags = (mz_uint8)(*d->m_pLZ_flags >> 1); إذا (--d->m_رقم_flags_چپ == 0) { d->m_رقم_flags_چپ = 8; d->m_pLZ_flags = d->m_p_LZ_کد_buf++; }
  d->m_huff_شمار[0][lit]++;
}

ساكن MZ_FORCEINLINE فراغ tdefl_رکورد_تطابق(tdefl_compressor *d, mz_uint تطابق_len, mz_uint تطابق_dist)
{
  mz_uint32 s0, s1;

  MZ_ASSERT((تطابق_len >= TDEFL_MIN_تطابق_LEN) && (تطابق_dist >= 1) && (تطابق_dist <= TDEFL_LZ_DICT_اندازه));

  d->m_مجموع_lz_بایتها += تطابق_len;

  d->m_p_LZ_کد_buf[0] = (mz_uint8)(تطابق_len - TDEFL_MIN_تطابق_LEN);

  تطابق_dist -= 1;
  d->m_p_LZ_کد_buf[1] = (mz_uint8)(تطابق_dist & 0xFF);
  d->m_p_LZ_کد_buf[2] = (mz_uint8)(تطابق_dist >> 8); d->m_p_LZ_کد_buf += 3;

  *d->m_pLZ_flags = (mz_uint8)((*d->m_pLZ_flags >> 1) | 0x80); إذا (--d->m_رقم_flags_چپ == 0) { d->m_رقم_flags_چپ = 8; d->m_pLZ_flags = d->m_p_LZ_کد_buf++; }

  s0 = s_tdefl_small_dist_sym[تطابق_dist & 511]; s1 = s_tdefl_large_dist_sym[(تطابق_dist >> 8) & 127];
  d->m_huff_شمار[1][(تطابق_dist < 512) ? s0 : s1]++;

  إذا (تطابق_len >= TDEFL_MIN_تطابق_LEN) d->m_huff_شمار[0][s_tdefl_len_sym[تطابق_len - TDEFL_MIN_تطابق_LEN]]++;
}

ساكن mz_bool tdefl_compress_نرمال(tdefl_compressor *d)
{
  ثابت mz_uint8 *pSrc = d->m_pSrc; size_t src_buf_چپ = d->m_src_buf_چپ;
  tdefl_flush flush = d->m_flush;

  طالما ((src_buf_چپ) || ((flush) && (d->m_lookahead_اندازه)))
  {
    mz_uint len_مقصد_move, cur_تطابق_dist, cur_تطابق_len, cur_pos;
    // Update dictionary and hash chains. Keeps the lookahead size equal to TDEFL_MAX_MATCH_LEN.
    إذا ((d->m_lookahead_اندازه + d->m_dict_اندازه) >= (TDEFL_MIN_تطابق_LEN - 1))
    {
      mz_uint dst_pos = (d->m_lookahead_pos + d->m_lookahead_اندازه) & TDEFL_LZ_DICT_اندازه_ماسک, ins_pos = d->m_lookahead_pos + d->m_lookahead_اندازه - 2;
      mz_uint hash = (d->m_dict[ins_pos & TDEFL_LZ_DICT_اندازه_ماسک] << TDEFL_LZ_HASH_لغزش) ^ d->m_dict[(ins_pos + 1) & TDEFL_LZ_DICT_اندازه_ماسک];
      mz_uint رقم_بایتها_مقصد_process = (mz_uint)MZ_MIN(src_buf_چپ, TDEFL_MAX_تطابق_LEN - d->m_lookahead_اندازه);
      ثابت mz_uint8 *p_Src_انتها = pSrc ? pSrc + رقم_بایتها_مقصد_process : عدم;
      src_buf_چپ -= رقم_بایتها_مقصد_process;
      d->m_lookahead_اندازه += رقم_بایتها_مقصد_process;
      طالما (pSrc != p_Src_انتها)
      {
        mz_uint8 c = *pSrc++; d->m_dict[dst_pos] = c; إذا (dst_pos < (TDEFL_MAX_تطابق_LEN - 1)) d->m_dict[TDEFL_LZ_DICT_اندازه + dst_pos] = c;
        hash = ((hash << TDEFL_LZ_HASH_لغزش) ^ c) & (TDEFL_LZ_HASH_اندازه - 1);
        d->m_بعدی[ins_pos & TDEFL_LZ_DICT_اندازه_ماسک] = d->m_hash[hash]; d->m_hash[hash] = (mz_uint16)(ins_pos);
        dst_pos = (dst_pos + 1) & TDEFL_LZ_DICT_اندازه_ماسک; ins_pos++;
      }
    }
    وإلا
    {
      طالما ((src_buf_چپ) && (d->m_lookahead_اندازه < TDEFL_MAX_تطابق_LEN))
      {
        mz_uint8 c = *pSrc++;
        mz_uint dst_pos = (d->m_lookahead_pos + d->m_lookahead_اندازه) & TDEFL_LZ_DICT_اندازه_ماسک;
        src_buf_چپ--;
        d->m_dict[dst_pos] = c;
        إذا (dst_pos < (TDEFL_MAX_تطابق_LEN - 1))
          d->m_dict[TDEFL_LZ_DICT_اندازه + dst_pos] = c;
        إذا ((++d->m_lookahead_اندازه + d->m_dict_اندازه) >= TDEFL_MIN_تطابق_LEN)
        {
          mz_uint ins_pos = d->m_lookahead_pos + (d->m_lookahead_اندازه - 1) - 2;
          mz_uint hash = ((d->m_dict[ins_pos & TDEFL_LZ_DICT_اندازه_ماسک] << (TDEFL_LZ_HASH_لغزش * 2)) ^ (d->m_dict[(ins_pos + 1) & TDEFL_LZ_DICT_اندازه_ماسک] << TDEFL_LZ_HASH_لغزش) ^ c) & (TDEFL_LZ_HASH_اندازه - 1);
          d->m_بعدی[ins_pos & TDEFL_LZ_DICT_اندازه_ماسک] = d->m_hash[hash]; d->m_hash[hash] = (mz_uint16)(ins_pos);
        }
      }
    }
    d->m_dict_اندازه = MZ_MIN(TDEFL_LZ_DICT_اندازه - d->m_lookahead_اندازه, d->m_dict_اندازه);
    إذا ((!flush) && (d->m_lookahead_اندازه < TDEFL_MAX_تطابق_LEN))
      اكسر;

    // Simple lazy/greedy parsing state machine.
    len_مقصد_move = 1; cur_تطابق_dist = 0; cur_تطابق_len = d->m_saved_تطابق_len ? d->m_saved_تطابق_len : (TDEFL_MIN_تطابق_LEN - 1); cur_pos = d->m_lookahead_pos & TDEFL_LZ_DICT_اندازه_ماسک;
    إذا (d->m_flags & (TDEFL_RLE_MATCHES | TDEFL_FORCE_ALL_RAW_بلوکها))
    {
      إذا ((d->m_dict_اندازه) && (!(d->m_flags & TDEFL_FORCE_ALL_RAW_بلوکها)))
      {
        mz_uint8 c = d->m_dict[(cur_pos - 1) & TDEFL_LZ_DICT_اندازه_ماسک];
        cur_تطابق_len = 0; طالما (cur_تطابق_len < d->m_lookahead_اندازه) { إذا (d->m_dict[cur_pos + cur_تطابق_len] != c) اكسر; cur_تطابق_len++; }
        إذا (cur_تطابق_len < TDEFL_MIN_تطابق_LEN) cur_تطابق_len = 0; وإلا cur_تطابق_dist = 1;
      }
    }
    وإلا
    {
      tdefl_پیدا_کن_تطابق(d, d->m_lookahead_pos, d->m_dict_اندازه, d->m_lookahead_اندازه, &cur_تطابق_dist, &cur_تطابق_len);
    }
    إذا (((cur_تطابق_len == TDEFL_MIN_تطابق_LEN) && (cur_تطابق_dist >= 8U*1024U)) || (cur_pos == cur_تطابق_dist) || ((d->m_flags & TDEFL_FILTER_MATCHES) && (cur_تطابق_len <= 5)))
    {
      cur_تطابق_dist = cur_تطابق_len = 0;
    }
    إذا (d->m_saved_تطابق_len)
    {
      إذا (cur_تطابق_len > d->m_saved_تطابق_len)
      {
        tdefl_رکورد_literal(d, (mz_uint8)d->m_saved_lit);
        إذا (cur_تطابق_len >= 128)
        {
          tdefl_رکورد_تطابق(d, cur_تطابق_len, cur_تطابق_dist);
          d->m_saved_تطابق_len = 0; len_مقصد_move = cur_تطابق_len;
        }
        وإلا
        {
          d->m_saved_lit = d->m_dict[cur_pos]; d->m_saved_تطابق_dist = cur_تطابق_dist; d->m_saved_تطابق_len = cur_تطابق_len;
        }
      }
      وإلا
      {
        tdefl_رکورد_تطابق(d, d->m_saved_تطابق_len, d->m_saved_تطابق_dist);
        len_مقصد_move = d->m_saved_تطابق_len - 1; d->m_saved_تطابق_len = 0;
      }
    }
    وإلا إذا (!cur_تطابق_dist)
      tdefl_رکورد_literal(d, d->m_dict[MZ_MIN(cur_pos, حجم(d->m_dict) - 1)]);
    وإلا إذا ((d->m_greedy_parsing) || (d->m_flags & TDEFL_RLE_MATCHES) || (cur_تطابق_len >= 128))
    {
      tdefl_رکورد_تطابق(d, cur_تطابق_len, cur_تطابق_dist);
      len_مقصد_move = cur_تطابق_len;
    }
    وإلا
    {
      d->m_saved_lit = d->m_dict[MZ_MIN(cur_pos, حجم(d->m_dict) - 1)]; d->m_saved_تطابق_dist = cur_تطابق_dist; d->m_saved_تطابق_len = cur_تطابق_len;
    }
    // Move the lookahead forward by len_to_move bytes.
    d->m_lookahead_pos += len_مقصد_move;
    MZ_ASSERT(d->m_lookahead_اندازه >= len_مقصد_move);
    d->m_lookahead_اندازه -= len_مقصد_move;
    d->m_dict_اندازه = MZ_MIN(d->m_dict_اندازه + len_مقصد_move, TDEFL_LZ_DICT_اندازه);
    // Check if it's time to flush the current LZ codes to the internal output buffer.
    إذا ( (d->m_p_LZ_کد_buf > &d->m_lz_کد_buf[TDEFL_LZ_کد_BUF_اندازه - 8]) ||
         ( (d->m_مجموع_lz_بایتها > 31*1024) && (((((mz_uint)(d->m_p_LZ_کد_buf - d->m_lz_کد_buf) * 115) >> 7) >= d->m_مجموع_lz_بایتها) || (d->m_flags & TDEFL_FORCE_ALL_RAW_بلوکها))) )
    {
      صحيح n;
      d->m_pSrc = pSrc; d->m_src_buf_چپ = src_buf_چپ;
      إذا ((n = tdefl_flush_بلوک(d, 0)) != 0)
        أرجع (n < 0) ? MZ_FALSE : MZ_TRUE;
    }
  }

  d->m_pSrc = pSrc; d->m_src_buf_چپ = src_buf_چپ;
  أرجع MZ_TRUE;
}

ساكن tdefl_وضعیت tdefl_flush_output_میانگیر(tdefl_compressor *d)
{
  إذا (d->m_p_درون_buf_اندازه)
  {
    *d->m_p_درون_buf_اندازه = d->m_pSrc - (ثابت mz_uint8 *)d->m_p_درون_buf;
  }

  إذا (d->m_p_بیرون_buf_اندازه)
  {
    size_t n = MZ_MIN(*d->m_p_بیرون_buf_اندازه - d->m_بیرون_buf_ofs, d->m_output_flush_مانده);
    کپی_حافظه((mz_uint8 *)d->m_p_بیرون_buf + d->m_بیرون_buf_ofs, d->m_output_buf + d->m_output_flush_ofs, n);
    d->m_output_flush_ofs += (mz_uint)n;
    d->m_output_flush_مانده -= (mz_uint)n;
    d->m_بیرون_buf_ofs += n;

    *d->m_p_بیرون_buf_اندازه = d->m_بیرون_buf_ofs;
  }

  أرجع (d->m_پایانیافته && !d->m_output_flush_مانده) ? TDEFL_وضعیت_انجامشده : TDEFL_وضعیت_OKAY;
}

tdefl_وضعیت tdefl_compress(tdefl_compressor *d, ثابت فراغ *p_درون_buf, size_t *p_درون_buf_اندازه, فراغ *p_بیرون_buf, size_t *p_بیرون_buf_اندازه, tdefl_flush flush)
{
  إذا (!d)
  {
    إذا (p_درون_buf_اندازه) *p_درون_buf_اندازه = 0;
    إذا (p_بیرون_buf_اندازه) *p_بیرون_buf_اندازه = 0;
    أرجع TDEFL_وضعیت_BAD_PARAM;
  }

  d->m_p_درون_buf = p_درون_buf; d->m_p_درون_buf_اندازه = p_درون_buf_اندازه;
  d->m_p_بیرون_buf = p_بیرون_buf; d->m_p_بیرون_buf_اندازه = p_بیرون_buf_اندازه;
  d->m_pSrc = (ثابت mz_uint8 *)(p_درون_buf); d->m_src_buf_چپ = p_درون_buf_اندازه ? *p_درون_buf_اندازه : 0;
  d->m_بیرون_buf_ofs = 0;
  d->m_flush = flush;

  إذا ( ((d->m_pPut_buf_func != عدم) == ((p_بیرون_buf != عدم) || (p_بیرون_buf_اندازه != عدم))) || (d->m_prev_return_وضعیت != TDEFL_وضعیت_OKAY) ||
        (d->m_میخواهد_مقصد_پایان && (flush != TDEFL_پایان)) || (p_درون_buf_اندازه && *p_درون_buf_اندازه && !p_درون_buf) || (p_بیرون_buf_اندازه && *p_بیرون_buf_اندازه && !p_بیرون_buf) )
  {
    إذا (p_درون_buf_اندازه) *p_درون_buf_اندازه = 0;
    إذا (p_بیرون_buf_اندازه) *p_بیرون_buf_اندازه = 0;
    أرجع (d->m_prev_return_وضعیت = TDEFL_وضعیت_BAD_PARAM);
  }
  d->m_میخواهد_مقصد_پایان |= (flush == TDEFL_پایان);

  إذا ((d->m_output_flush_مانده) || (d->m_پایانیافته))
    أرجع (d->m_prev_return_وضعیت = tdefl_flush_output_میانگیر(d));

#إذا MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  إذا (((d->m_flags & TDEFL_MAX_PROBES_ماسک) == 1) &&
      ((d->m_flags & TDEFL_GREEDY_PARSING_FLAG) != 0) &&
      ((d->m_flags & (TDEFL_FILTER_MATCHES | TDEFL_FORCE_ALL_RAW_بلوکها | TDEFL_RLE_MATCHES)) == 0))
  {
    إذا (!tdefl_compress_fast(d))
      أرجع d->m_prev_return_وضعیت;
  }
  وإلا
#پایان_اگر // #if MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  {
    إذا (!tdefl_compress_نرمال(d))
      أرجع d->m_prev_return_وضعیت;
  }

  إذا ((d->m_flags & (TDEFL_WRITE_ZLIB_سرآیند | TDEFL_COMPUTE_ADLER32)) && (p_درون_buf))
    d->m_adler32 = (mz_uint32)mz_adler32(d->m_adler32, (ثابت mz_uint8 *)p_درون_buf, d->m_pSrc - (ثابت mz_uint8 *)p_درون_buf);

  إذا ((flush) && (!d->m_lookahead_اندازه) && (!d->m_src_buf_چپ) && (!d->m_output_flush_مانده))
  {
    إذا (tdefl_flush_بلوک(d, flush) < 0)
      أرجع d->m_prev_return_وضعیت;
    d->m_پایانیافته = (flush == TDEFL_پایان);
    إذا (flush == TDEFL_پر_FLUSH) { MZ_CLEAR_ARR(d->m_hash); MZ_CLEAR_ARR(d->m_بعدی); d->m_dict_اندازه = 0; }
  }

  أرجع (d->m_prev_return_وضعیت = tdefl_flush_output_میانگیر(d));
}

tdefl_وضعیت tdefl_compress_میانگیر(tdefl_compressor *d, ثابت فراغ *p_درون_buf, size_t درون_buf_اندازه, tdefl_flush flush)
{
  MZ_ASSERT(d->m_pPut_buf_func); أرجع tdefl_compress(d, p_درون_buf, &درون_buf_اندازه, عدم, عدم, flush);
}

tdefl_وضعیت tdefl_init(tdefl_compressor *d, tdefl_put_buf_func_ptr pPut_buf_func, فراغ *pPut_buf_user, صحيح flags)
{
  d->m_pPut_buf_func = pPut_buf_func; d->m_pPut_buf_user = pPut_buf_user;
  d->m_flags = (mz_uint)(flags); d->m_max_probes[0] = 1 + ((flags & 0xFFF) + 2) / 3; d->m_greedy_parsing = (flags & TDEFL_GREEDY_PARSING_FLAG) != 0;
  d->m_max_probes[1] = 1 + (((flags & 0xFFF) >> 2) + 2) / 3;
  إذا (!(flags & TDEFL_NONDETERMINISTIC_PARSING_FLAG)) MZ_CLEAR_ARR(d->m_hash);
  d->m_lookahead_pos = d->m_lookahead_اندازه = d->m_dict_اندازه = d->m_مجموع_lz_بایتها = d->m_lz_کد_buf_dict_pos = d->m_بیتها_درون = 0;
  d->m_output_flush_ofs = d->m_output_flush_مانده = d->m_پایانیافته = d->m_بلوک_شاخص = d->m_بیت_میانگیر = d->m_میخواهد_مقصد_پایان = 0;
  d->m_p_LZ_کد_buf = d->m_lz_کد_buf + 1; d->m_pLZ_flags = d->m_lz_کد_buf; d->m_رقم_flags_چپ = 8;
  d->m_pOutput_buf = d->m_output_buf; d->m_p_Output_buf_انتها = d->m_output_buf; d->m_prev_return_وضعیت = TDEFL_وضعیت_OKAY;
  d->m_saved_تطابق_dist = d->m_saved_تطابق_len = d->m_saved_lit = 0; d->m_adler32 = 1;
  d->m_p_درون_buf = عدم; d->m_p_بیرون_buf = عدم;
  d->m_p_درون_buf_اندازه = عدم; d->m_p_بیرون_buf_اندازه = عدم;
  d->m_flush = TDEFL_NO_FLUSH; d->m_pSrc = عدم; d->m_src_buf_چپ = 0; d->m_بیرون_buf_ofs = 0;
  memset(&d->m_huff_شمار[0][0], 0, حجم(d->m_huff_شمار[0][0]) * TDEFL_MAX_HUFF_SYMBOLS_0);
  memset(&d->m_huff_شمار[1][0], 0, حجم(d->m_huff_شمار[1][0]) * TDEFL_MAX_HUFF_SYMBOLS_1);
  أرجع TDEFL_وضعیت_OKAY;
}

#اگر_تعریف_نشده MINIZ_SDL_NOUNUSED
tdefl_وضعیت tdefl_get_prev_return_وضعیت(tdefl_compressor *d)
{
  أرجع d->m_prev_return_وضعیت;
}

mz_uint32 tdefl_get_adler32(tdefl_compressor *d)
{
  أرجع d->m_adler32;
}

mz_bool tdefl_compress_mem_مقصد_output(ثابت فراغ *pBuf, size_t buf_len, tdefl_put_buf_func_ptr pPut_buf_func, فراغ *pPut_buf_user, صحيح flags)
{
  tdefl_compressor *pComp; mz_bool succeeded; إذا (((buf_len) && (!pBuf)) || (!pPut_buf_func)) أرجع MZ_FALSE;
  pComp = (tdefl_compressor*)MZ_MALLOC(حجم(tdefl_compressor)); إذا (!pComp) أرجع MZ_FALSE;
  succeeded = (tdefl_init(pComp, pPut_buf_func, pPut_buf_user, flags) == TDEFL_وضعیت_OKAY);
  succeeded = succeeded && (tdefl_compress_میانگیر(pComp, pBuf, buf_len, TDEFL_پایان) == TDEFL_وضعیت_انجامشده);
  MZ_FREE(pComp); أرجع succeeded;
}
#پایان_اگر /* MINIZ_SDL_NOUNUSED */

تعريفنوع بنية
{
  size_t m_اندازه, m_ظرفیت;
  mz_uint8 *m_pBuf;
  mz_bool m_expandable;
} tdefl_output_میانگیر;

ساكن mz_bool tdefl_output_میانگیر_putter(ثابت فراغ *pBuf, صحيح len, فراغ *pUser)
{
  tdefl_output_میانگیر *p = (tdefl_output_میانگیر *)pUser;
  size_t new_اندازه = p->m_اندازه + len;
  إذا (new_اندازه > p->m_ظرفیت)
  {
    size_t new_ظرفیت = p->m_ظرفیت; mz_uint8 *pNew_buf; إذا (!p->m_expandable) أرجع MZ_FALSE;
    افعل { new_ظرفیت = MZ_MAX(128U, new_ظرفیت << 1U); } طالما (new_اندازه > new_ظرفیت);
    pNew_buf = (mz_uint8*)MZ_REALLOC(p->m_pBuf, new_ظرفیت); إذا (!pNew_buf) أرجع MZ_FALSE;
    p->m_pBuf = pNew_buf; p->m_ظرفیت = new_ظرفیت;
  }
  کپی_حافظه((mz_uint8*)p->m_pBuf + p->m_اندازه, pBuf, len); p->m_اندازه = new_اندازه;
  أرجع MZ_TRUE;
}

#اگر_تعریف_نشده MINIZ_SDL_NOUNUSED
فراغ *tdefl_compress_mem_مقصد_انباشته(ثابت فراغ *pSrc_buf, size_t src_buf_len, size_t *p_بیرون_len, صحيح flags)
{
  tdefl_output_میانگیر بیرون_buf; MZ_CLEAR_OBJ(بیرون_buf);
  إذا (!p_بیرون_len) أرجع MZ_FALSE; وإلا *p_بیرون_len = 0;
  بیرون_buf.m_expandable = MZ_TRUE;
  إذا (!tdefl_compress_mem_مقصد_output(pSrc_buf, src_buf_len, tdefl_output_میانگیر_putter, &بیرون_buf, flags)) أرجع عدم;
  *p_بیرون_len = بیرون_buf.m_اندازه; أرجع بیرون_buf.m_pBuf;
}

size_t tdefl_compress_mem_مقصد_mem(فراغ *p_بیرون_buf, size_t بیرون_buf_len, ثابت فراغ *pSrc_buf, size_t src_buf_len, صحيح flags)
{
  tdefl_output_میانگیر بیرون_buf; MZ_CLEAR_OBJ(بیرون_buf);
  إذا (!p_بیرون_buf) أرجع 0;
  بیرون_buf.m_pBuf = (mz_uint8*)p_بیرون_buf; بیرون_buf.m_ظرفیت = بیرون_buf_len;
  إذا (!tdefl_compress_mem_مقصد_output(pSrc_buf, src_buf_len, tdefl_output_میانگیر_putter, &بیرون_buf, flags)) أرجع 0;
  أرجع بیرون_buf.m_اندازه;
}
#پایان_اگر /* MINIZ_SDL_NOUNUSED */

#اگر_تعریف_نشده MINIZ_NO_ZLIB_APIS
ساكن ثابت mz_uint s_tdefl_رقم_probes[11] = { 0, 1, 6, 32,  16, 32, 128, 256,  512, 768, 1500 };

// level may actually range from [0,10] (10 is a "hidden" max level, where we want a bit more compression and it's fine if throughput to fall off a cliff on some files).
mz_uint tdefl_create_comp_flags_from_zip_params(صحيح level, صحيح پنجره_بیتها, صحيح strategy)
{
  mz_uint comp_flags = s_tdefl_رقم_probes[(level >= 0) ? MZ_MIN(10, level) : MZ_DEFAULT_LEVEL] | ((level <= 3) ? TDEFL_GREEDY_PARSING_FLAG : 0);
  إذا (پنجره_بیتها > 0) comp_flags |= TDEFL_WRITE_ZLIB_سرآیند;

  إذا (!level) comp_flags |= TDEFL_FORCE_ALL_RAW_بلوکها;
  وإلا إذا (strategy == MZ_FILTERED) comp_flags |= TDEFL_FILTER_MATCHES;
  وإلا إذا (strategy == MZ_HUFFMAN_ONLY) comp_flags &= ~TDEFL_MAX_PROBES_ماسک;
  وإلا إذا (strategy == MZ_FIXED) comp_flags |= TDEFL_FORCE_ALL_STATIC_بلوکها;
  وإلا إذا (strategy == MZ_RLE) comp_flags |= TDEFL_RLE_MATCHES;

  أرجع comp_flags;
}
#پایان_اگر //MINIZ_NO_ZLIB_APIS

#اگر_تعریف_شده _MSC_VER
#رهنمود warning (افزودن)
#رهنمود warning (disable:4204) // nonstandard extension used : non-constant aggregate initializer (also supported by GNU C and C99, so no big deal)
#پایان_اگر

// Simple PNG writer function by Alex Evans, 2011. Released into the public domain: https://gist.github.com/908299, more context at
// http://altdevblogaday.org/2011/04/06/a-smaller-jpg-encoder/.
// This is actually a modification of Alex's original code so PNG files generated by this function pass pngcheck.
MINIZ_STATIC فراغ *tdefl_write_image_مقصد_png_file_درون_حافظه_ex(ثابت فراغ *pImage, صحيح w, صحيح h, صحيح رقم_chans, صحيح bpl, size_t *p_Len_بیرون, mz_uint level, mz_bool flip, mz_uint8 *plte, صحيح plte_اندازه, mz_uint8 *trns, صحيح trns_اندازه)
{
  // Using a local copy of this array here in case MINIZ_NO_ZLIB_APIS was defined.
  ساكن ثابت mz_uint s_tdefl_png_رقم_probes[11] = { 0, 1, 6, 32,  16, 32, 128, 256,  512, 768, 1500 };
  tdefl_compressor *pComp = (tdefl_compressor *)MZ_MALLOC(حجم(tdefl_compressor)); tdefl_output_میانگیر بیرون_buf; صحيح i, y, z = 0; mz_uint32 c; *p_Len_بیرون = 0; size_t داده_شروع, داده_اندازه_3;
  إذا (!pComp) أرجع عدم;
  MZ_CLEAR_OBJ(بیرون_buf); بیرون_buf.m_expandable = MZ_TRUE;
  بیرون_buf.m_ظرفیت = 57+MZ_MAX(64, (1+w*رقم_chans)*h);
  إذا (plte_اندازه > 0)
    بیرون_buf.m_ظرفیت += 12+plte_اندازه;
  إذا (trns_اندازه > 0)
    بیرون_buf.m_ظرفیت += 12+trns_اندازه;
  إذا (عدم == (بیرون_buf.m_pBuf = (mz_uint8*)MZ_MALLOC(بیرون_buf.m_ظرفیت))) { MZ_FREE(pComp); أرجع عدم; }
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

    إذا (رقم_chans == 1 && plte_اندازه > 0)
      pnghdr[25] = 3;
    وإلا
      pnghdr[25] = (chans[رقم_chans]);

    c = (mz_uint32)mz_بررسی_چرخهای_32(MZ_بررسی_چرخهای_32_INIT,pnghdr+12,17);
    لكل (i=0; i<4; ++i, c<<=8) ((mz_uint8*)(pnghdr+29))[i] = (mz_uint8)(c>>24);
    إذا (!tdefl_output_میانگیر_putter(pnghdr, حجم(pnghdr), &بیرون_buf)) { *p_Len_بیرون = 0; MZ_FREE(pComp); MZ_FREE(بیرون_buf.m_pBuf); أرجع عدم; }
  }
  // write PLTE chunk
  إذا (plte_اندازه > 0)
  {
    mz_uint8 hdr[8]={0x00,0x00,0x00,0x00,0x50,0x4c,0x54,0x45};

    hdr[0] = (mz_uint8)(plte_اندازه>>24);
    hdr[1] = (mz_uint8)(plte_اندازه>>16);
    hdr[2] = (mz_uint8)(plte_اندازه>> 8);
    hdr[3] = (mz_uint8)(plte_اندازه>> 0);
    إذا (!tdefl_output_میانگیر_putter(hdr, حجم(hdr), &بیرون_buf)) { *p_Len_بیرون = 0; MZ_FREE(pComp); MZ_FREE(بیرون_buf.m_pBuf); أرجع عدم; }
    داده_شروع = بیرون_buf.m_اندازه;
    إذا (!tdefl_output_میانگیر_putter(plte, plte_اندازه, &بیرون_buf)) { *p_Len_بیرون = 0; MZ_FREE(pComp); MZ_FREE(بیرون_buf.m_pBuf); أرجع عدم; }
    إذا (!tdefl_output_میانگیر_putter("\0\0\0\0", 4, &بیرون_buf)) { *p_Len_بیرون = 0; MZ_FREE(pComp); MZ_FREE(بیرون_buf.m_pBuf); أرجع عدم; }
    c = (mz_uint32)mz_بررسی_چرخهای_32(MZ_بررسی_چرخهای_32_INIT,بیرون_buf.m_pBuf+داده_شروع-4, plte_اندازه+4);
    لكل (i=0; i<4; ++i, c<<=8) (بیرون_buf.m_pBuf+بیرون_buf.m_اندازه-4)[i] = (mz_uint8)(c >> 24);
  }
  // write tRNS chunk
  إذا (trns_اندازه > 0)
  {
    mz_uint8 hdr[8]={0x00,0x00,0x00,0x00,0x74,0x52,0x4E,0x53};

    hdr[0] = (mz_uint8)(trns_اندازه>>24);
    hdr[1] = (mz_uint8)(trns_اندازه>>16);
    hdr[2] = (mz_uint8)(trns_اندازه>> 8);
    hdr[3] = (mz_uint8)(trns_اندازه>> 0);
    إذا (!tdefl_output_میانگیر_putter(hdr, حجم(hdr), &بیرون_buf)) { *p_Len_بیرون = 0; MZ_FREE(pComp); MZ_FREE(بیرون_buf.m_pBuf); أرجع عدم; }
    داده_شروع = بیرون_buf.m_اندازه;
    إذا (!tdefl_output_میانگیر_putter(trns, trns_اندازه, &بیرون_buf)) { *p_Len_بیرون = 0; MZ_FREE(pComp); MZ_FREE(بیرون_buf.m_pBuf); أرجع عدم; }
    إذا (!tdefl_output_میانگیر_putter("\0\0\0\0", 4, &بیرون_buf)) { *p_Len_بیرون = 0; MZ_FREE(pComp); MZ_FREE(بیرون_buf.m_pBuf); أرجع عدم; }
    c = (mz_uint32)mz_بررسی_چرخهای_32(MZ_بررسی_چرخهای_32_INIT,بیرون_buf.m_pBuf+داده_شروع-4, trns_اندازه+4);
    لكل (i=0; i<4; ++i, c<<=8) (بیرون_buf.m_pBuf+بیرون_buf.m_اندازه-4)[i] = (mz_uint8)(c >> 24);
  }
  // write IDAT chunk
  إذا (!tdefl_output_میانگیر_putter("\0\0\0\0\x49\x44\x41\x54", 8, &بیرون_buf)) { *p_Len_بیرون = 0; MZ_FREE(pComp); MZ_FREE(بیرون_buf.m_pBuf); أرجع عدم; }
  داده_شروع = بیرون_buf.m_اندازه;
  // compress image data
  tdefl_init(pComp, tdefl_output_میانگیر_putter, &بیرون_buf, s_tdefl_png_رقم_probes[MZ_MIN(10, level)] | TDEFL_WRITE_ZLIB_سرآیند);
  لكل (y = 0; y < h; ++y) { tdefl_compress_میانگیر(pComp, &z, 1, TDEFL_NO_FLUSH); tdefl_compress_میانگیر(pComp, (mz_uint8*)pImage + (flip ? (h - 1 - y) : y) * bpl, w * رقم_chans, TDEFL_NO_FLUSH); }
  إذا (tdefl_compress_میانگیر(pComp, عدم, 0, TDEFL_پایان) != TDEFL_وضعیت_انجامشده) { MZ_FREE(pComp); MZ_FREE(بیرون_buf.m_pBuf); أرجع عدم; }
  // write IDAT size
  داده_اندازه_3 = بیرون_buf.m_اندازه-داده_شروع;
  (بیرون_buf.m_pBuf+داده_شروع-8)[0] = (mz_uint8)(داده_اندازه_3>>24);
  (بیرون_buf.m_pBuf+داده_شروع-8)[1] = (mz_uint8)(داده_اندازه_3>>16);
  (بیرون_buf.m_pBuf+داده_شروع-8)[2] = (mz_uint8)(داده_اندازه_3>> 8);
  (بیرون_buf.m_pBuf+داده_شروع-8)[3] = (mz_uint8)(داده_اندازه_3>> 0);
  // write footer (IDAT CRC-32, followed by IEND chunk)
  إذا (!tdefl_output_میانگیر_putter("\0\0\0\0\0\0\0\0\x49\x45\x4e\x44\xae\x42\x60\x82", 16, &بیرون_buf)) { *p_Len_بیرون = 0; MZ_FREE(pComp); MZ_FREE(بیرون_buf.m_pBuf); أرجع عدم; }
  c = (mz_uint32)mz_بررسی_چرخهای_32(MZ_بررسی_چرخهای_32_INIT,بیرون_buf.m_pBuf+داده_شروع-4, داده_اندازه_3+4);
  لكل (i=0; i<4; ++i, c<<=8) (بیرون_buf.m_pBuf+بیرون_buf.m_اندازه-16)[i] = (mz_uint8)(c >> 24);
  // compute final size of file, grab compressed data buffer and return
  *p_Len_بیرون = بیرون_buf.m_اندازه;
  MZ_FREE(pComp);
  أرجع بیرون_buf.m_pBuf;
}
#اگر_تعریف_نشده MINIZ_SDL_NOUNUSED
MINIZ_STATIC فراغ *tdefl_write_image_مقصد_png_file_درون_حافظه(ثابت فراغ *pImage, صحيح w, صحيح h, صحيح رقم_chans, صحيح bpl, size_t *p_Len_بیرون)
{
  // Level 6 corresponds to TDEFL_DEFAULT_MAX_PROBES or MZ_DEFAULT_LEVEL (but we can't depend on MZ_DEFAULT_LEVEL being available in case the zlib API's where #defined out)
  أرجع tdefl_write_image_مقصد_png_file_درون_حافظه_ex(pImage, w, h, رقم_chans, bpl, p_Len_بیرون, 6, MZ_FALSE, عدم, 0, عدم, 0);
}
#پایان_اگر

#اگر_تعریف_شده _MSC_VER
#رهنمود warning (برداشت)
#پایان_اگر
#پایان_اگر /*#ifndef MINIZ_NO_DEFLATE_APIS*/

// ------------------- .ZIP archive reading

#اگر_تعریف_نشده MINIZ_NO_ARCHIVE_APIS

#اگر_تعریف_شده MINIZ_NO_STDIO
  #تعریف_کن MZ_FILE فراغ *
#وإلا
  #ضمن <stdio.h>
  #ضمن <sys/stat.h>

  #إذا defined(_MSC_VER) || defined(__MINGW64__)
    ساكن FILE *mz_fopen(ثابت حرف *pFilename, ثابت حرف *p_نما)
    {
      FILE* pFile = عدم;
      fopen_s(&pFile, pFilename, p_نما);
      أرجع pFile;
    }
    ساكن FILE *mz_freopen(ثابت حرف *p_مسیر, ثابت حرف *p_نما, FILE *p_جریان)
    {
      FILE* pFile = عدم;
      إذا (freopen_s(&pFile, p_مسیر, p_نما, p_جریان))
        أرجع عدم;
      أرجع pFile;
    }
    #اگر_تعریف_نشده MINIZ_NO_زمان
      #ضمن <sys/utime.h>
    #پایان_اگر
    #تعریف_کن MZ_FILE FILE
    #تعریف_کن MZ_FOPEN mz_fopen
    #تعریف_کن MZ_FCLOSE fclose
    #تعریف_کن MZ_FREAD fread
    #تعریف_کن MZ_FWRITE fwrite
    #تعریف_کن MZ_FTELL64 _ftelli64
    #تعریف_کن MZ_FSEEK64 _fseeki64
    #تعریف_کن MZ_FILE_STAT_STRUCT _stat
    #تعریف_کن MZ_FILE_STAT _stat
    #تعریف_کن MZ_FFLUSH fflush
    #تعریف_کن MZ_FREOPEN mz_freopen
    #تعریف_کن MZ_DELETE_FILE remove
  #وإلاإذا defined(__MINGW32__)
    #اگر_تعریف_نشده MINIZ_NO_زمان
      #ضمن <sys/utime.h>
    #پایان_اگر
    #تعریف_کن MZ_FILE FILE
    #تعریف_کن MZ_FOPEN(f, m) fopen(f, m)
    #تعریف_کن MZ_FCLOSE fclose
    #تعریف_کن MZ_FREAD fread
    #تعریف_کن MZ_FWRITE fwrite
    #تعریف_کن MZ_FTELL64 ftello64
    #تعریف_کن MZ_FSEEK64 fseeko64
    #تعریف_کن MZ_FILE_STAT_STRUCT _stat
    #تعریف_کن MZ_FILE_STAT _stat
    #تعریف_کن MZ_FFLUSH fflush
    #تعریف_کن MZ_FREOPEN(f, m, s) freopen(f, m, s)
    #تعریف_کن MZ_DELETE_FILE remove
  #وإلاإذا defined(__TINYC__)
    #اگر_تعریف_نشده MINIZ_NO_زمان
      #ضمن <sys/utime.h>
    #پایان_اگر
    #تعریف_کن MZ_FILE FILE
    #تعریف_کن MZ_FOPEN(f, m) fopen(f, m)
    #تعریف_کن MZ_FCLOSE fclose
    #تعریف_کن MZ_FREAD fread
    #تعریف_کن MZ_FWRITE fwrite
    #تعریف_کن MZ_FTELL64 ftell
    #تعریف_کن MZ_FSEEK64 fseek
    #تعریف_کن MZ_FILE_STAT_STRUCT stat
    #تعریف_کن MZ_FILE_STAT stat
    #تعریف_کن MZ_FFLUSH fflush
    #تعریف_کن MZ_FREOPEN(f, m, s) freopen(f, m, s)
    #تعریف_کن MZ_DELETE_FILE remove
  #وإلاإذا defined(__GNUC__) && LARGEFILE64_منبع
    #اگر_تعریف_نشده MINIZ_NO_زمان
      #ضمن <utime.h>
    #پایان_اگر
    #تعریف_کن MZ_FILE FILE
    #تعریف_کن MZ_FOPEN(f, m) fopen64(f, m)
    #تعریف_کن MZ_FCLOSE fclose
    #تعریف_کن MZ_FREAD fread
    #تعریف_کن MZ_FWRITE fwrite
    #تعریف_کن MZ_FTELL64 ftello64
    #تعریف_کن MZ_FSEEK64 fseeko64
    #تعریف_کن MZ_FILE_STAT_STRUCT stat64
    #تعریف_کن MZ_FILE_STAT stat64
    #تعریف_کن MZ_FFLUSH fflush
    #تعریف_کن MZ_FREOPEN(p, m, s) freopen64(p, m, s)
    #تعریف_کن MZ_DELETE_FILE remove
  #وإلا
    #اگر_تعریف_نشده MINIZ_NO_زمان
      #ضمن <utime.h>
    #پایان_اگر
    #تعریف_کن MZ_FILE FILE
    #تعریف_کن MZ_FOPEN(f, m) fopen(f, m)
    #تعریف_کن MZ_FCLOSE fclose
    #تعریف_کن MZ_FREAD fread
    #تعریف_کن MZ_FWRITE fwrite
    #تعریف_کن MZ_FTELL64 ftello
    #تعریف_کن MZ_FSEEK64 fseeko
    #تعریف_کن MZ_FILE_STAT_STRUCT stat
    #تعریف_کن MZ_FILE_STAT stat
    #تعریف_کن MZ_FFLUSH fflush
    #تعریف_کن MZ_FREOPEN(f, m, s) freopen(f, m, s)
    #تعریف_کن MZ_DELETE_FILE remove
  #پایان_اگر // #ifdef _MSC_VER
#پایان_اگر // #ifdef MINIZ_NO_STDIO

#تعریف_کن MZ_TOLOWER(c) ((((c) >= 'A') && ((c) <= 'Z')) ? ((c) - 'A' + 'a') : (c))

// Various ZIP archive enums. To completely avoid cross platform compiler alignment and platform endian issues, miniz.c doesn't use structs for any of this stuff.
تعداد
{
  // ZIP archive identifiers and record sizes
  MZ_ZIP_انتها_از_CENTRAL_DIR_سرآیند_SIG = 0x06054b50, MZ_ZIP_CENTRAL_DIR_سرآیند_SIG = 0x02014b50, MZ_ZIP_LOCAL_DIR_سرآیند_SIG = 0x04034b50,
  MZ_ZIP_LOCAL_DIR_سرآیند_اندازه = 30, MZ_ZIP_CENTRAL_DIR_سرآیند_اندازه = 46, MZ_ZIP_انتها_از_CENTRAL_DIR_سرآیند_اندازه = 22,
  // Central directory header record offsets
  MZ_ZIP_CDH_SIG_OFS = 0, MZ_ZIP_CDH_نسخه_MADE_BY_OFS = 4, MZ_ZIP_CDH_نسخه_NEEDED_OFS = 6, MZ_ZIP_CDH_بیت_FLAG_OFS = 8,
  MZ_ZIP_CDH_روش_OFS = 10, MZ_ZIP_CDH_FILE_زمان_OFS = 12, MZ_ZIP_CDH_FILE_DATE_OFS = 14, MZ_ZIP_CDH_بررسی_چرخهای_32_OFS = 16,
  MZ_ZIP_CDH_COMPRESSED_اندازه_OFS = 20, MZ_ZIP_CDH_DECOMPRESSED_اندازه_OFS = 24, MZ_ZIP_CDH_FILENAME_LEN_OFS = 28, MZ_ZIP_CDH_EXTRA_LEN_OFS = 30,
  MZ_ZIP_CDH_COMMENT_LEN_OFS = 32, MZ_ZIP_CDH_DISK_شروع_OFS = 34, MZ_ZIP_CDH_داخلی_ATTR_OFS = 36, MZ_ZIP_CDH_EXTERNAL_ATTR_OFS = 38, MZ_ZIP_CDH_LOCAL_سرآیند_OFS = 42,
  // Local directory header offsets
  MZ_ZIP_LDH_SIG_OFS = 0, MZ_ZIP_LDH_نسخه_NEEDED_OFS = 4, MZ_ZIP_LDH_بیت_FLAG_OFS = 6, MZ_ZIP_LDH_روش_OFS = 8, MZ_ZIP_LDH_FILE_زمان_OFS = 10,
  MZ_ZIP_LDH_FILE_DATE_OFS = 12, MZ_ZIP_LDH_بررسی_چرخهای_32_OFS = 14, MZ_ZIP_LDH_COMPRESSED_اندازه_OFS = 18, MZ_ZIP_LDH_DECOMPRESSED_اندازه_OFS = 22,
  MZ_ZIP_LDH_FILENAME_LEN_OFS = 26, MZ_ZIP_LDH_EXTRA_LEN_OFS = 28,
  // End of central directory offsets
  MZ_ZIP_ECDH_SIG_OFS = 0, MZ_ZIP_ECDH_رقم_THIS_DISK_OFS = 4, MZ_ZIP_ECDH_رقم_DISK_CDIR_OFS = 6, MZ_ZIP_ECDH_CDIR_رقم_ENTRIES_ON_DISK_OFS = 8,
  MZ_ZIP_ECDH_CDIR_مجموع_ENTRIES_OFS = 10, MZ_ZIP_ECDH_CDIR_اندازه_OFS = 12, MZ_ZIP_ECDH_CDIR_OFS_OFS = 16, MZ_ZIP_ECDH_COMMENT_اندازه_OFS = 20,
};

تعريفنوع بنية
{
  فراغ *m_p;
  size_t m_اندازه, m_ظرفیت;
  mz_uint m_element_اندازه;
} mz_zip_array;

بنية mz_zip_داخلی_state_برچسب
{
  mz_zip_array m_central_dir;
  mz_zip_array m_central_dir_offsets;
  mz_zip_array m_sorted_central_dir_offsets;
  MZ_FILE *m_pFile;
  فراغ *m_pMem;
  size_t m_mem_اندازه;
  size_t m_mem_ظرفیت;
};

#تعریف_کن MZ_ZIP_ARRAY_مجموعه_ELEMENT_اندازه(array_ptr, element_اندازه) (array_ptr)->m_element_اندازه = element_اندازه
#تعریف_کن MZ_ZIP_ARRAY_ELEMENT(array_ptr, element_type, شاخص) ((element_type *)((array_ptr)->m_p))[شاخص]

ساكن MZ_FORCEINLINE فراغ mz_zip_array_clear(mz_zip_archive *pZip, mz_zip_array *pArray)
{
  pZip->m_pFree(pZip->m_pAlloc_opaque, pArray->m_p);
  memset(pArray, 0, حجم(mz_zip_array));
}

ساكن mz_bool mz_zip_array_ensure_ظرفیت(mz_zip_archive *pZip, mz_zip_array *pArray, size_t min_new_ظرفیت, mz_uint growing)
{
  فراغ *pNew_p; size_t new_ظرفیت = min_new_ظرفیت; MZ_ASSERT(pArray->m_element_اندازه); إذا (pArray->m_ظرفیت >= min_new_ظرفیت) أرجع MZ_TRUE;
  إذا (growing) { new_ظرفیت = MZ_MAX(1, pArray->m_ظرفیت); طالما (new_ظرفیت < min_new_ظرفیت) new_ظرفیت *= 2; }
  إذا (عدم == (pNew_p = pZip->m_pRealloc(pZip->m_pAlloc_opaque, pArray->m_p, pArray->m_element_اندازه, new_ظرفیت))) أرجع MZ_FALSE;
  pArray->m_p = pNew_p; pArray->m_ظرفیت = new_ظرفیت;
  أرجع MZ_TRUE;
}

ساكن MZ_FORCEINLINE mz_bool mz_zip_array_reserve(mz_zip_archive *pZip, mz_zip_array *pArray, size_t new_ظرفیت, mz_uint growing)
{
  إذا (new_ظرفیت > pArray->m_ظرفیت) { إذا (!mz_zip_array_ensure_ظرفیت(pZip, pArray, new_ظرفیت, growing)) أرجع MZ_FALSE; }
  أرجع MZ_TRUE;
}

ساكن MZ_FORCEINLINE mz_bool mz_zip_array_resize(mz_zip_archive *pZip, mz_zip_array *pArray, size_t new_اندازه, mz_uint growing)
{
  إذا (new_اندازه > pArray->m_ظرفیت) { إذا (!mz_zip_array_ensure_ظرفیت(pZip, pArray, new_اندازه, growing)) أرجع MZ_FALSE; }
  pArray->m_اندازه = new_اندازه;
  أرجع MZ_TRUE;
}

ساكن MZ_FORCEINLINE mz_bool mz_zip_array_ensure_جا(mz_zip_archive *pZip, mz_zip_array *pArray, size_t n)
{
  أرجع mz_zip_array_reserve(pZip, pArray, pArray->m_اندازه + n, MZ_TRUE);
}

ساكن MZ_FORCEINLINE mz_bool mz_zip_array_افزودن_پشت(mz_zip_archive *pZip, mz_zip_array *pArray, ثابت فراغ *pElements, size_t n)
{
  size_t orig_اندازه = pArray->m_اندازه; إذا (!mz_zip_array_resize(pZip, pArray, orig_اندازه + n, MZ_TRUE)) أرجع MZ_FALSE;
  کپی_حافظه((mz_uint8*)pArray->m_p + orig_اندازه * pArray->m_element_اندازه, pElements, n * pArray->m_element_اندازه);
  أرجع MZ_TRUE;
}

#اگر_تعریف_نشده MINIZ_NO_زمان
ساكن زمان_t mz_zip_dos_مقصد_زمان_t(صحيح dos_زمان, صحيح dos_date)
{
  بنية tm tm;
  memset(&tm, 0, حجم(tm)); tm.tm_isdst = -1;
  tm.tm_year = ((dos_date >> 9) & 127) + 1980 - 1900; tm.tm_mon = ((dos_date >> 5) & 15) - 1; tm.tm_mday = dos_date & 31;
  tm.tm_hour = (dos_زمان >> 11) & 31; tm.tm_min = (dos_زمان >> 5) & 63; tm.tm_sec = (dos_زمان << 1) & 62;
  أرجع mktime(&tm);
}

ساكن فراغ mz_zip_زمان_مقصد_dos_زمان(زمان_t زمان, mz_uint16 *p_DOS_زمان, mz_uint16 *pDOS_date)
{
#اگر_تعریف_شده _MSC_VER
  بنية tm tm_struct;
  بنية tm *tm = &tm_struct;
  errno_t err = localtime_s(tm, &زمان);
  إذا (err)
  {
    *pDOS_date = 0; *p_DOS_زمان = 0;
    أرجع;
  }
#وإلا
  بنية tm *tm = localtime(&زمان);
#پایان_اگر
  *p_DOS_زمان = (mz_uint16)(((tm->tm_hour) << 11) + ((tm->tm_min) << 5) + ((tm->tm_sec) >> 1));
  *pDOS_date = (mz_uint16)(((tm->tm_year + 1900 - 1980) << 9) + ((tm->tm_mon + 1) << 5) + tm->tm_mday);
}
#پایان_اگر

#اگر_تعریف_نشده MINIZ_NO_STDIO
ساكن mz_bool mz_zip_get_file_modified_زمان(ثابت حرف *pFilename, mz_uint16 *p_DOS_زمان, mz_uint16 *pDOS_date)
{
#اگر_تعریف_شده MINIZ_NO_زمان
  (فراغ)pFilename; *pDOS_date = *p_DOS_زمان = 0;
#وإلا
  بنية MZ_FILE_STAT_STRUCT file_stat;
  // On Linux with x86 glibc, this call will fail on large files (>= 0x80000000 bytes) unless you compiled with _LARGEFILE64_SOURCE. Argh.
  إذا (MZ_FILE_STAT(pFilename, &file_stat) != 0)
    أرجع MZ_FALSE;
  mz_zip_زمان_مقصد_dos_زمان(file_stat.st_mtime, p_DOS_زمان, pDOS_date);
#پایان_اگر // #ifdef MINIZ_NO_TIME
  أرجع MZ_TRUE;
}

#اگر_تعریف_نشده MINIZ_NO_زمان
ساكن mz_bool mz_zip_مجموعه_file_times(ثابت حرف *pFilename, زمان_t access_زمان, زمان_t modified_زمان)
{
  بنية utimbuf t; t.actime = access_زمان; t.modtime = modified_زمان;
  أرجع !utime(pFilename, &t);
}
#پایان_اگر // #ifndef MINIZ_NO_TIME
#پایان_اگر // #ifndef MINIZ_NO_STDIO

ساكن mz_bool mz_zip_reader_init_داخلی(mz_zip_archive *pZip, mz_uint32 flags)
{
  (فراغ)flags;
  إذا ((!pZip) || (pZip->m_pState) || (pZip->m_zip_نما != MZ_ZIP_نما_INVALID))
    أرجع MZ_FALSE;

  إذا (!pZip->m_pAlloc) pZip->m_pAlloc = def_alloc_func;
  إذا (!pZip->m_pFree) pZip->m_pFree = def_free_func;
  إذا (!pZip->m_pRealloc) pZip->m_pRealloc = def_realloc_func;

  pZip->m_zip_نما = MZ_ZIP_نما_READING;
  pZip->m_archive_اندازه = 0;
  pZip->m_central_directory_file_ofs = 0;
  pZip->m_مجموع_files = 0;

  إذا (عدم == (pZip->m_pState = (mz_zip_داخلی_state *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, حجم(mz_zip_داخلی_state))))
    أرجع MZ_FALSE;
  memset(pZip->m_pState, 0, حجم(mz_zip_داخلی_state));
  MZ_ZIP_ARRAY_مجموعه_ELEMENT_اندازه(&pZip->m_pState->m_central_dir, حجم(mz_uint8));
  MZ_ZIP_ARRAY_مجموعه_ELEMENT_اندازه(&pZip->m_pState->m_central_dir_offsets, حجم(mz_uint32));
  MZ_ZIP_ARRAY_مجموعه_ELEMENT_اندازه(&pZip->m_pState->m_sorted_central_dir_offsets, حجم(mz_uint32));
  أرجع MZ_TRUE;
}

ساكن MZ_FORCEINLINE mz_bool mz_zip_reader_filename_less(ثابت mz_zip_array *pCentral_dir_array, ثابت mz_zip_array *pCentral_dir_offsets, mz_uint l_شاخص, mz_uint r_شاخص)
{
  ثابت mz_uint8 *pL = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, l_شاخص)), *pE;
  ثابت mz_uint8 *pR = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, r_شاخص));
  mz_uint l_len = MZ_READ_LE16(pL + MZ_ZIP_CDH_FILENAME_LEN_OFS), r_len = MZ_READ_LE16(pR + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  mz_uint8 l = 0, r = 0;
  pL += MZ_ZIP_CENTRAL_DIR_سرآیند_اندازه; pR += MZ_ZIP_CENTRAL_DIR_سرآیند_اندازه;
  pE = pL + MZ_MIN(l_len, r_len);
  طالما (pL < pE)
  {
    إذا ((l = MZ_TOLOWER(*pL)) != (r = MZ_TOLOWER(*pR)))
      اكسر;
    pL++; pR++;
  }
  أرجع (pL == pE) ? (l_len < r_len) : (l < r);
}

#تعریف_کن MZ_جابجا_UINT32(a, b) افعل { mz_uint32 t = a; a = b; b = t; } MZ_MACRO_انتها

// Heap sort of lowercased filenames, used to help accelerate plain central directory searches by mz_zip_reader_locate_file(). (Could also use qsort(), but it could allocate memory.)
ساكن فراغ mz_zip_reader_مرتب_سازی_central_dir_offsets_by_filename(mz_zip_archive *pZip)
{
  mz_zip_داخلی_state *pState = pZip->m_pState;
  ثابت mz_zip_array *pCentral_dir_offsets = &pState->m_central_dir_offsets;
  ثابت mz_zip_array *pCentral_dir = &pState->m_central_dir;
  mz_uint32 *pIndices = &MZ_ZIP_ARRAY_ELEMENT(&pState->m_sorted_central_dir_offsets, mz_uint32, 0);
  ثابت صحيح اندازه = pZip->m_مجموع_files;
  صحيح شروع = (اندازه - 2) >> 1, انتها;
  طالما (شروع >= 0)
  {
    صحيح فرزند, ریشه = شروع;
    لكل ( ; ; )
    {
      إذا ((فرزند = (ریشه << 1) + 1) >= اندازه)
        اكسر;
      فرزند += (((فرزند + 1) < اندازه) && (mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[فرزند], pIndices[فرزند + 1])));
      إذا (!mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[ریشه], pIndices[فرزند]))
        اكسر;
      MZ_جابجا_UINT32(pIndices[ریشه], pIndices[فرزند]); ریشه = فرزند;
    }
    شروع--;
  }

  انتها = اندازه - 1;
  طالما (انتها > 0)
  {
    صحيح فرزند, ریشه = 0;
    MZ_جابجا_UINT32(pIndices[انتها], pIndices[0]);
    لكل ( ; ; )
    {
      إذا ((فرزند = (ریشه << 1) + 1) >= انتها)
        اكسر;
      فرزند += (((فرزند + 1) < انتها) && mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[فرزند], pIndices[فرزند + 1]));
      إذا (!mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[ریشه], pIndices[فرزند]))
        اكسر;
      MZ_جابجا_UINT32(pIndices[ریشه], pIndices[فرزند]); ریشه = فرزند;
    }
    انتها--;
  }
}

ساكن mz_bool mz_zip_reader_read_central_dir(mz_zip_archive *pZip, mz_uint32 flags)
{
  mz_uint cdir_اندازه, رقم_this_disk, cdir_disk_شاخص;
  mz_uint64 cdir_ofs;
  mz_int64 cur_file_ofs;
  ثابت mz_uint8 *p;
  mz_uint32 buf_u32[4096 / حجم(mz_uint32)]; mz_uint8 *pBuf = (mz_uint8 *)buf_u32;
  mz_bool مرتب_سازی_central_dir = ((flags & MZ_ZIP_FLAG_DO_NOT_مرتب_سازی_CENTRAL_DIRECTORY) == 0);
  // Basic sanity checks - reject files which are too small, and check the first 4 bytes of the file to make sure a local header is there.
  إذا (pZip->m_archive_اندازه < MZ_ZIP_انتها_از_CENTRAL_DIR_سرآیند_اندازه)
    أرجع MZ_FALSE;
  // Find the end of central directory record by scanning the file from the end towards the beginning.
  cur_file_ofs = MZ_MAX((mz_int64)pZip->m_archive_اندازه - (mz_int64)حجم(buf_u32), 0);
  لكل ( ; ; )
  {
    صحيح i, n = (صحيح)MZ_MIN(حجم(buf_u32), pZip->m_archive_اندازه - cur_file_ofs);
    إذا (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, n) != (mz_uint)n)
      أرجع MZ_FALSE;
    لكل (i = n - 4; i >= 0; --i)
      إذا (MZ_READ_LE32(pBuf + i) == MZ_ZIP_انتها_از_CENTRAL_DIR_سرآیند_SIG)
        اكسر;
    إذا (i >= 0)
    {
      cur_file_ofs += i;
      اكسر;
    }
    إذا ((!cur_file_ofs) || ((pZip->m_archive_اندازه - cur_file_ofs) >= (0xFFFF + MZ_ZIP_انتها_از_CENTRAL_DIR_سرآیند_اندازه)))
      أرجع MZ_FALSE;
    cur_file_ofs = MZ_MAX(cur_file_ofs - (حجم(buf_u32) - 3), 0);
  }
  // Read and verify the end of central directory record.
  إذا (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, MZ_ZIP_انتها_از_CENTRAL_DIR_سرآیند_اندازه) != MZ_ZIP_انتها_از_CENTRAL_DIR_سرآیند_اندازه)
    أرجع MZ_FALSE;
  إذا ((MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_SIG_OFS) != MZ_ZIP_انتها_از_CENTRAL_DIR_سرآیند_SIG) ||
      ((pZip->m_مجموع_files = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_CDIR_مجموع_ENTRIES_OFS)) != MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_CDIR_رقم_ENTRIES_ON_DISK_OFS)))
    أرجع MZ_FALSE;

  رقم_this_disk = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_رقم_THIS_DISK_OFS);
  cdir_disk_شاخص = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_رقم_DISK_CDIR_OFS);
  إذا (((رقم_this_disk | cdir_disk_شاخص) != 0) && ((رقم_this_disk != 1) || (cdir_disk_شاخص != 1)))
    أرجع MZ_FALSE;

  إذا ((cdir_اندازه = MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_CDIR_اندازه_OFS)) < pZip->m_مجموع_files * MZ_ZIP_CENTRAL_DIR_سرآیند_اندازه)
    أرجع MZ_FALSE;

  cdir_ofs = MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_CDIR_OFS_OFS);
  إذا ((cdir_ofs + (mz_uint64)cdir_اندازه) > pZip->m_archive_اندازه)
    أرجع MZ_FALSE;

  pZip->m_central_directory_file_ofs = cdir_ofs;

  إذا (pZip->m_مجموع_files)
  {
     mz_uint i, n;

    // Read the entire central directory into a heap block, and allocate another heap block to hold the unsorted central dir file record offsets, and another to hold the sorted indices.
    إذا ((!mz_zip_array_resize(pZip, &pZip->m_pState->m_central_dir, cdir_اندازه, MZ_FALSE)) ||
        (!mz_zip_array_resize(pZip, &pZip->m_pState->m_central_dir_offsets, pZip->m_مجموع_files, MZ_FALSE)))
      أرجع MZ_FALSE;

    إذا (مرتب_سازی_central_dir)
    {
      إذا (!mz_zip_array_resize(pZip, &pZip->m_pState->m_sorted_central_dir_offsets, pZip->m_مجموع_files, MZ_FALSE))
        أرجع MZ_FALSE;
    }

    إذا (pZip->m_pRead(pZip->m_pIO_opaque, cdir_ofs, pZip->m_pState->m_central_dir.m_p, cdir_اندازه) != cdir_اندازه)
      أرجع MZ_FALSE;

    // Now create an index into the central directory file records, do some basic sanity checking on each record, and check for zip64 entries (which are not yet supported).
    p = (ثابت mz_uint8 *)pZip->m_pState->m_central_dir.m_p;
    لكل (n = cdir_اندازه, i = 0; i < pZip->m_مجموع_files; ++i)
    {
      mz_uint مجموع_سرآیند_اندازه, comp_اندازه, decomp_اندازه, disk_شاخص;
      إذا ((n < MZ_ZIP_CENTRAL_DIR_سرآیند_اندازه) || (MZ_READ_LE32(p) != MZ_ZIP_CENTRAL_DIR_سرآیند_SIG))
        أرجع MZ_FALSE;
      MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, i) = (mz_uint32)(p - (ثابت mz_uint8 *)pZip->m_pState->m_central_dir.m_p);
      إذا (مرتب_سازی_central_dir)
        MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_sorted_central_dir_offsets, mz_uint32, i) = i;
      comp_اندازه = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_اندازه_OFS);
      decomp_اندازه = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_اندازه_OFS);
      إذا (((!MZ_READ_LE32(p + MZ_ZIP_CDH_روش_OFS)) && (decomp_اندازه != comp_اندازه)) || (decomp_اندازه && !comp_اندازه) || (decomp_اندازه == 0xFFFFFFFF) || (comp_اندازه == 0xFFFFFFFF))
        أرجع MZ_FALSE;
      disk_شاخص = MZ_READ_LE16(p + MZ_ZIP_CDH_DISK_شروع_OFS);
      إذا ((disk_شاخص != رقم_this_disk) && (disk_شاخص != 1))
        أرجع MZ_FALSE;
      إذا (((mz_uint64)MZ_READ_LE32(p + MZ_ZIP_CDH_LOCAL_سرآیند_OFS) + MZ_ZIP_LOCAL_DIR_سرآیند_اندازه + comp_اندازه) > pZip->m_archive_اندازه)
        أرجع MZ_FALSE;
      إذا ((مجموع_سرآیند_اندازه = MZ_ZIP_CENTRAL_DIR_سرآیند_اندازه + MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_EXTRA_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_COMMENT_LEN_OFS)) > n)
        أرجع MZ_FALSE;
      n -= مجموع_سرآیند_اندازه; p += مجموع_سرآیند_اندازه;
    }
  }

  إذا (مرتب_سازی_central_dir)
    mz_zip_reader_مرتب_سازی_central_dir_offsets_by_filename(pZip);

  أرجع MZ_TRUE;
}

mz_bool mz_zip_reader_init(mz_zip_archive *pZip, mz_uint64 اندازه, mz_uint32 flags)
{
  إذا ((!pZip) || (!pZip->m_pRead))
    أرجع MZ_FALSE;
  إذا (!mz_zip_reader_init_داخلی(pZip, flags))
    أرجع MZ_FALSE;
  pZip->m_archive_اندازه = اندازه;
  إذا (!mz_zip_reader_read_central_dir(pZip, flags))
  {
    mz_zip_reader_انتها(pZip);
    أرجع MZ_FALSE;
  }
  أرجع MZ_TRUE;
}

ساكن size_t mz_zip_mem_read_func(فراغ *pOpaque, mz_uint64 file_ofs, فراغ *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  size_t s = (file_ofs >= pZip->m_archive_اندازه) ? 0 : (size_t)MZ_MIN(pZip->m_archive_اندازه - file_ofs, n);
  کپی_حافظه(pBuf, (ثابت mz_uint8 *)pZip->m_pState->m_pMem + file_ofs, s);
  أرجع s;
}

mz_bool mz_zip_reader_init_mem(mz_zip_archive *pZip, ثابت فراغ *pMem, size_t اندازه, mz_uint32 flags)
{
  إذا (!mz_zip_reader_init_داخلی(pZip, flags))
    أرجع MZ_FALSE;
  pZip->m_archive_اندازه = اندازه;
  pZip->m_pRead = mz_zip_mem_read_func;
  pZip->m_pIO_opaque = pZip;
#اگر_تعریف_شده __cplusplus
  pZip->m_pState->m_pMem = const_cast<فراغ *>(pMem);
#وإلا
  pZip->m_pState->m_pMem = (فراغ *)pMem;
#پایان_اگر
  pZip->m_pState->m_mem_اندازه = اندازه;
  إذا (!mz_zip_reader_read_central_dir(pZip, flags))
  {
    mz_zip_reader_انتها(pZip);
    أرجع MZ_FALSE;
  }
  أرجع MZ_TRUE;
}

#اگر_تعریف_نشده MINIZ_NO_STDIO
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
  mz_uint64 file_اندازه;
  MZ_FILE *pFile = MZ_FOPEN(pFilename, "rb");
  إذا (!pFile)
    أرجع MZ_FALSE;
  إذا (MZ_FSEEK64(pFile, 0, SEEK_END))
  {
    MZ_FCLOSE(pFile);
    أرجع MZ_FALSE;
  }
  file_اندازه = MZ_FTELL64(pFile);
  إذا (!mz_zip_reader_init_داخلی(pZip, flags))
  {
    MZ_FCLOSE(pFile);
    أرجع MZ_FALSE;
  }
  pZip->m_pRead = mz_zip_file_read_func;
  pZip->m_pIO_opaque = pZip;
  pZip->m_pState->m_pFile = pFile;
  pZip->m_archive_اندازه = file_اندازه;
  إذا (!mz_zip_reader_read_central_dir(pZip, flags))
  {
    mz_zip_reader_انتها(pZip);
    أرجع MZ_FALSE;
  }
  أرجع MZ_TRUE;
}
#پایان_اگر // #ifndef MINIZ_NO_STDIO

mz_uint mz_zip_reader_get_رقم_files(mz_zip_archive *pZip)
{
  أرجع pZip ? pZip->m_مجموع_files : 0;
}

ساكن MZ_FORCEINLINE ثابت mz_uint8 *mz_zip_reader_get_cdh(mz_zip_archive *pZip, mz_uint file_شاخص)
{
  إذا ((!pZip) || (!pZip->m_pState) || (file_شاخص >= pZip->m_مجموع_files) || (pZip->m_zip_نما != MZ_ZIP_نما_READING))
    أرجع عدم;
  أرجع &MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_شاخص));
}

mz_bool mz_zip_reader_is_file_encrypted(mz_zip_archive *pZip, mz_uint file_شاخص)
{
  mz_uint m_بیت_flag;
  ثابت mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_شاخص);
  إذا (!p)
    أرجع MZ_FALSE;
  m_بیت_flag = MZ_READ_LE16(p + MZ_ZIP_CDH_بیت_FLAG_OFS);
  أرجع (m_بیت_flag & 1);
}

mz_bool mz_zip_reader_is_file_a_directory(mz_zip_archive *pZip, mz_uint file_شاخص)
{
  mz_uint filename_len, external_attr;
  ثابت mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_شاخص);
  إذا (!p)
    أرجع MZ_FALSE;

  // First see if the filename ends with a '/' character.
  filename_len = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  إذا (filename_len)
  {
    إذا (*(p + MZ_ZIP_CENTRAL_DIR_سرآیند_اندازه + filename_len - 1) == '/')
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

mz_bool mz_zip_reader_file_stat(mz_zip_archive *pZip, mz_uint file_شاخص, mz_zip_archive_file_stat *pStat)
{
  mz_uint n;
  ثابت mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_شاخص);
  إذا ((!p) || (!pStat))
    أرجع MZ_FALSE;

  // Unpack the central directory record.
  pStat->m_file_شاخص = file_شاخص;
  pStat->m_central_dir_ofs = MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_شاخص);
  pStat->m_نسخه_made_by = MZ_READ_LE16(p + MZ_ZIP_CDH_نسخه_MADE_BY_OFS);
  pStat->m_نسخه_needed = MZ_READ_LE16(p + MZ_ZIP_CDH_نسخه_NEEDED_OFS);
  pStat->m_بیت_flag = MZ_READ_LE16(p + MZ_ZIP_CDH_بیت_FLAG_OFS);
  pStat->m_روش = MZ_READ_LE16(p + MZ_ZIP_CDH_روش_OFS);
#اگر_تعریف_نشده MINIZ_NO_زمان
  pStat->m_زمان = mz_zip_dos_مقصد_زمان_t(MZ_READ_LE16(p + MZ_ZIP_CDH_FILE_زمان_OFS), MZ_READ_LE16(p + MZ_ZIP_CDH_FILE_DATE_OFS));
#پایان_اگر
  pStat->m_بررسی_چرخهای_32 = MZ_READ_LE32(p + MZ_ZIP_CDH_بررسی_چرخهای_32_OFS);
  pStat->m_comp_اندازه = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_اندازه_OFS);
  pStat->m_uncomp_اندازه = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_اندازه_OFS);
  pStat->m_داخلی_attr = MZ_READ_LE16(p + MZ_ZIP_CDH_داخلی_ATTR_OFS);
  pStat->m_external_attr = MZ_READ_LE32(p + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS);
  pStat->m_local_سرآیند_ofs = MZ_READ_LE32(p + MZ_ZIP_CDH_LOCAL_سرآیند_OFS);

  // Copy as much of the filename and comment as possible.
  n = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS); n = MZ_MIN(n, MZ_ZIP_MAX_ARCHIVE_FILENAME_اندازه - 1);
  کپی_حافظه(pStat->m_filename, p + MZ_ZIP_CENTRAL_DIR_سرآیند_اندازه, n); pStat->m_filename[n] = '\0';

  n = MZ_READ_LE16(p + MZ_ZIP_CDH_COMMENT_LEN_OFS); n = MZ_MIN(n, MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_اندازه - 1);
  pStat->m_comment_اندازه = n;
  کپی_حافظه(pStat->m_comment, p + MZ_ZIP_CENTRAL_DIR_سرآیند_اندازه + MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_EXTRA_LEN_OFS), n); pStat->m_comment[n] = '\0';

  أرجع MZ_TRUE;
}

mz_uint mz_zip_reader_get_filename(mz_zip_archive *pZip, mz_uint file_شاخص, حرف *pFilename, mz_uint filename_buf_اندازه)
{
  mz_uint n;
  ثابت mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_شاخص);
  إذا (!p) { إذا (filename_buf_اندازه) pFilename[0] = '\0'; أرجع 0; }
  n = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  إذا (filename_buf_اندازه)
  {
    n = MZ_MIN(n, filename_buf_اندازه - 1);
    کپی_حافظه(pFilename, p + MZ_ZIP_CENTRAL_DIR_سرآیند_اندازه, n);
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

ساكن MZ_FORCEINLINE صحيح mz_zip_reader_filename_compare(ثابت mz_zip_array *pCentral_dir_array, ثابت mz_zip_array *pCentral_dir_offsets, mz_uint l_شاخص, ثابت حرف *pR, mz_uint r_len)
{
  ثابت mz_uint8 *pL = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, l_شاخص)), *pE;
  mz_uint l_len = MZ_READ_LE16(pL + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  mz_uint8 l = 0, r = 0;
  pL += MZ_ZIP_CENTRAL_DIR_سرآیند_اندازه;
  pE = pL + MZ_MIN(l_len, r_len);
  طالما (pL < pE)
  {
    إذا ((l = MZ_TOLOWER(*pL)) != (r = MZ_TOLOWER(*pR)))
      اكسر;
    pL++; pR++;
  }
  أرجع (pL == pE) ? (صحيح)(l_len - r_len) : (l - r);
}

ساكن صحيح mz_zip_reader_locate_file_دودویی_جستجو(mz_zip_archive *pZip, ثابت حرف *pFilename)
{
  mz_zip_داخلی_state *pState = pZip->m_pState;
  ثابت mz_zip_array *pCentral_dir_offsets = &pState->m_central_dir_offsets;
  ثابت mz_zip_array *pCentral_dir = &pState->m_central_dir;
  mz_uint32 *pIndices = &MZ_ZIP_ARRAY_ELEMENT(&pState->m_sorted_central_dir_offsets, mz_uint32, 0);
  ثابت صحيح اندازه = pZip->m_مجموع_files;
  ثابت mz_uint filename_len = (mz_uint)طول_رشته(pFilename);
  صحيح l = 0, h = اندازه - 1;
  طالما (l <= h)
  {
    صحيح m = (l + h) >> 1, file_شاخص = pIndices[m], comp = mz_zip_reader_filename_compare(pCentral_dir, pCentral_dir_offsets, file_شاخص, pFilename, filename_len);
    إذا (!comp)
      أرجع file_شاخص;
    وإلا إذا (comp < 0)
      l = m + 1;
    وإلا
      h = m - 1;
  }
  أرجع -1;
}

صحيح mz_zip_reader_locate_file(mz_zip_archive *pZip, ثابت حرف *pName, ثابت حرف *pComment, mz_uint flags)
{
  mz_uint file_شاخص; size_t name_len, comment_len;
  إذا ((!pZip) || (!pZip->m_pState) || (!pName) || (pZip->m_zip_نما != MZ_ZIP_نما_READING))
    أرجع -1;
  إذا (((flags & (MZ_ZIP_FLAG_IGNORE_مسیر | MZ_ZIP_FLAG_CASE_SENSITIVE)) == 0) && (!pComment) && (pZip->m_pState->m_sorted_central_dir_offsets.m_اندازه))
    أرجع mz_zip_reader_locate_file_دودویی_جستجو(pZip, pName);
  name_len = طول_رشته(pName); إذا (name_len > 0xFFFF) أرجع -1;
  comment_len = pComment ? طول_رشته(pComment) : 0; إذا (comment_len > 0xFFFF) أرجع -1;
  لكل (file_شاخص = 0; file_شاخص < pZip->m_مجموع_files; file_شاخص++)
  {
    ثابت mz_uint8 *p_سرآیند = &MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_شاخص));
    mz_uint filename_len = MZ_READ_LE16(p_سرآیند + MZ_ZIP_CDH_FILENAME_LEN_OFS);
    ثابت حرف *pFilename = (ثابت حرف *)p_سرآیند + MZ_ZIP_CENTRAL_DIR_سرآیند_اندازه;
    إذا (filename_len < name_len)
      استمر;
    إذا (comment_len)
    {
      mz_uint file_extra_len = MZ_READ_LE16(p_سرآیند + MZ_ZIP_CDH_EXTRA_LEN_OFS), file_comment_len = MZ_READ_LE16(p_سرآیند + MZ_ZIP_CDH_COMMENT_LEN_OFS);
      ثابت حرف *pFile_comment = pFilename + filename_len + file_extra_len;
      إذا ((file_comment_len != comment_len) || (!mz_zip_reader_string_equal(pComment, pFile_comment, file_comment_len, flags)))
        استمر;
    }
    إذا ((flags & MZ_ZIP_FLAG_IGNORE_مسیر) && (filename_len))
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
      أرجع file_شاخص;
  }
  أرجع -1;
}

mz_bool mz_zip_reader_استخراج_مقصد_mem_no_alloc(mz_zip_archive *pZip, mz_uint file_شاخص, فراغ *pBuf, size_t buf_اندازه_2, mz_uint flags, فراغ *pUser_read_buf, size_t user_read_buf_اندازه)
{
  صحيح وضعیت = TINFL_وضعیت_انجامشده;
  mz_uint64 needed_اندازه, cur_file_ofs, comp_مانده, بیرون_buf_ofs = 0, read_buf_اندازه, read_buf_ofs = 0, read_buf_avail;
  mz_zip_archive_file_stat file_stat;
  فراغ *pRead_buf;
  mz_uint32 local_سرآیند_u32[(MZ_ZIP_LOCAL_DIR_سرآیند_اندازه + حجم(mz_uint32) - 1) / حجم(mz_uint32)]; mz_uint8 *p_Local_سرآیند = (mz_uint8 *)local_سرآیند_u32;
  tinfl_decompressor inflator;

  إذا ((buf_اندازه_2) && (!pBuf))
    أرجع MZ_FALSE;

  إذا (!mz_zip_reader_file_stat(pZip, file_شاخص, &file_stat))
    أرجع MZ_FALSE;

  // Empty file, or a directory (but not always a directory - I've seen odd zips with directories that have compressed data which inflates to 0 bytes)
  إذا (!file_stat.m_comp_اندازه)
    أرجع MZ_TRUE;

  // Entry is a subdirectory (I've seen old zips with dir entries which have compressed deflate data which inflates to 0 bytes, but these entries claim to uncompress to 512 bytes in the headers).
  // I'm torn how to handle this case - should it fail instead?
  إذا (mz_zip_reader_is_file_a_directory(pZip, file_شاخص))
    أرجع MZ_TRUE;

  // Encryption and patch files are not supported.
  إذا (file_stat.m_بیت_flag & (1 | 32))
    أرجع MZ_FALSE;

  // This function only supports stored and deflate.
  إذا ((!(flags & MZ_ZIP_FLAG_COMPRESSED_داده)) && (file_stat.m_روش != 0) && (file_stat.m_روش != MZ_DEFLATED))
    أرجع MZ_FALSE;

  // Ensure supplied output buffer is large enough.
  needed_اندازه = (flags & MZ_ZIP_FLAG_COMPRESSED_داده) ? file_stat.m_comp_اندازه : file_stat.m_uncomp_اندازه;
  إذا (buf_اندازه_2 < needed_اندازه)
    أرجع MZ_FALSE;

  // Read and parse the local directory entry.
  cur_file_ofs = file_stat.m_local_سرآیند_ofs;
  إذا (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, p_Local_سرآیند, MZ_ZIP_LOCAL_DIR_سرآیند_اندازه) != MZ_ZIP_LOCAL_DIR_سرآیند_اندازه)
    أرجع MZ_FALSE;
  إذا (MZ_READ_LE32(p_Local_سرآیند) != MZ_ZIP_LOCAL_DIR_سرآیند_SIG)
    أرجع MZ_FALSE;

  cur_file_ofs += MZ_ZIP_LOCAL_DIR_سرآیند_اندازه + MZ_READ_LE16(p_Local_سرآیند + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p_Local_سرآیند + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  إذا ((cur_file_ofs + file_stat.m_comp_اندازه) > pZip->m_archive_اندازه)
    أرجع MZ_FALSE;

  إذا ((flags & MZ_ZIP_FLAG_COMPRESSED_داده) || (!file_stat.m_روش))
  {
    // The file is stored or the caller has requested the compressed data.
    إذا (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, (size_t)needed_اندازه) != needed_اندازه)
      أرجع MZ_FALSE;
    أرجع ((flags & MZ_ZIP_FLAG_COMPRESSED_داده) != 0) || (mz_بررسی_چرخهای_32(MZ_بررسی_چرخهای_32_INIT, (ثابت mz_uint8 *)pBuf, (size_t)file_stat.m_uncomp_اندازه) == file_stat.m_بررسی_چرخهای_32);
  }

  // Decompress the file either directly from memory or from a file input buffer.
  tinfl_init(&inflator);

  إذا (pZip->m_pState->m_pMem)
  {
    // Read directly from the archive in memory.
    pRead_buf = (mz_uint8 *)pZip->m_pState->m_pMem + cur_file_ofs;
    read_buf_اندازه = read_buf_avail = file_stat.m_comp_اندازه;
    comp_مانده = 0;
  }
  وإلا إذا (pUser_read_buf)
  {
    // Use a user provided read buffer.
    إذا (!user_read_buf_اندازه)
      أرجع MZ_FALSE;
    pRead_buf = (mz_uint8 *)pUser_read_buf;
    read_buf_اندازه = user_read_buf_اندازه;
    read_buf_avail = 0;
    comp_مانده = file_stat.m_comp_اندازه;
  }
  وإلا
  {
    // Temporarily allocate a read buffer.
    read_buf_اندازه = MZ_MIN(file_stat.m_comp_اندازه, MZ_ZIP_MAX_IO_BUF_اندازه);
#اگر_تعریف_شده _MSC_VER
    إذا (((0, حجم(size_t) == حجم(mz_uint32))) && (read_buf_اندازه > 0x7FFFFFFF))
#وإلا
    إذا (((حجم(size_t) == حجم(mz_uint32))) && (read_buf_اندازه > 0x7FFFFFFF))
#پایان_اگر
      أرجع MZ_FALSE;
    إذا (عدم == (pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)read_buf_اندازه)))
      أرجع MZ_FALSE;
    read_buf_avail = 0;
    comp_مانده = file_stat.m_comp_اندازه;
  }

  افعل
  {
    size_t درون_buf_اندازه, بیرون_buf_اندازه = (size_t)(file_stat.m_uncomp_اندازه - بیرون_buf_ofs);
    إذا ((!read_buf_avail) && (!pZip->m_pState->m_pMem))
    {
      read_buf_avail = MZ_MIN(read_buf_اندازه, comp_مانده);
      إذا (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
      {
        وضعیت = TINFL_وضعیت_FAILED;
        اكسر;
      }
      cur_file_ofs += read_buf_avail;
      comp_مانده -= read_buf_avail;
      read_buf_ofs = 0;
    }
    درون_buf_اندازه = (size_t)read_buf_avail;
    وضعیت = tinfl_decompress(&inflator, (mz_uint8 *)pRead_buf + read_buf_ofs, &درون_buf_اندازه, (mz_uint8 *)pBuf, (mz_uint8 *)pBuf + بیرون_buf_ofs, &بیرون_buf_اندازه, TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF | (comp_مانده ? TINFL_FLAG_HAS_بیشتر_درون_داد : 0));
    read_buf_avail -= درون_buf_اندازه;
    read_buf_ofs += درون_buf_اندازه;
    بیرون_buf_ofs += بیرون_buf_اندازه;
  } طالما (وضعیت == TINFL_وضعیت_NEEDS_بیشتر_درون_داد);

  إذا (وضعیت == TINFL_وضعیت_انجامشده)
  {
    // Make sure the entire file was decompressed, and check its CRC.
    إذا ((بیرون_buf_ofs != file_stat.m_uncomp_اندازه) || (mz_بررسی_چرخهای_32(MZ_بررسی_چرخهای_32_INIT, (ثابت mz_uint8 *)pBuf, (size_t)file_stat.m_uncomp_اندازه) != file_stat.m_بررسی_چرخهای_32))
      وضعیت = TINFL_وضعیت_FAILED;
  }

  إذا ((!pZip->m_pState->m_pMem) && (!pUser_read_buf))
    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);

  أرجع وضعیت == TINFL_وضعیت_انجامشده;
}

mz_bool mz_zip_reader_استخراج_file_مقصد_mem_no_alloc(mz_zip_archive *pZip, ثابت حرف *pFilename, فراغ *pBuf, size_t buf_اندازه_2, mz_uint flags, فراغ *pUser_read_buf, size_t user_read_buf_اندازه)
{
  صحيح file_شاخص = mz_zip_reader_locate_file(pZip, pFilename, عدم, flags);
  إذا (file_شاخص < 0)
    أرجع MZ_FALSE;
  أرجع mz_zip_reader_استخراج_مقصد_mem_no_alloc(pZip, file_شاخص, pBuf, buf_اندازه_2, flags, pUser_read_buf, user_read_buf_اندازه);
}

mz_bool mz_zip_reader_استخراج_مقصد_mem(mz_zip_archive *pZip, mz_uint file_شاخص, فراغ *pBuf, size_t buf_اندازه_2, mz_uint flags)
{
  أرجع mz_zip_reader_استخراج_مقصد_mem_no_alloc(pZip, file_شاخص, pBuf, buf_اندازه_2, flags, عدم, 0);
}

mz_bool mz_zip_reader_استخراج_file_مقصد_mem(mz_zip_archive *pZip, ثابت حرف *pFilename, فراغ *pBuf, size_t buf_اندازه_2, mz_uint flags)
{
  أرجع mz_zip_reader_استخراج_file_مقصد_mem_no_alloc(pZip, pFilename, pBuf, buf_اندازه_2, flags, عدم, 0);
}

فراغ *mz_zip_reader_استخراج_مقصد_انباشته(mz_zip_archive *pZip, mz_uint file_شاخص, size_t *p_اندازه, mz_uint flags)
{
  mz_uint64 comp_اندازه, uncomp_اندازه, alloc_اندازه_2;
  ثابت mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_شاخص);
  فراغ *pBuf;

  إذا (p_اندازه)
    *p_اندازه = 0;
  إذا (!p)
    أرجع عدم;

  comp_اندازه = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_اندازه_OFS);
  uncomp_اندازه = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_اندازه_OFS);

  alloc_اندازه_2 = (flags & MZ_ZIP_FLAG_COMPRESSED_داده) ? comp_اندازه : uncomp_اندازه;
#اگر_تعریف_شده _MSC_VER
  إذا (((0, حجم(size_t) == حجم(mz_uint32))) && (alloc_اندازه_2 > 0x7FFFFFFF))
#وإلا
  إذا (((حجم(size_t) == حجم(mz_uint32))) && (alloc_اندازه_2 > 0x7FFFFFFF))
#پایان_اگر
    أرجع عدم;
  إذا (عدم == (pBuf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)alloc_اندازه_2)))
    أرجع عدم;

  إذا (!mz_zip_reader_استخراج_مقصد_mem(pZip, file_شاخص, pBuf, (size_t)alloc_اندازه_2, flags))
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
    أرجع عدم;
  }

  إذا (p_اندازه) *p_اندازه = (size_t)alloc_اندازه_2;
  أرجع pBuf;
}

فراغ *mz_zip_reader_استخراج_file_مقصد_انباشته(mz_zip_archive *pZip, ثابت حرف *pFilename, size_t *p_اندازه, mz_uint flags)
{
  صحيح file_شاخص = mz_zip_reader_locate_file(pZip, pFilename, عدم, flags);
  إذا (file_شاخص < 0)
  {
    إذا (p_اندازه) *p_اندازه = 0;
    أرجع MZ_FALSE;
  }
  أرجع mz_zip_reader_استخراج_مقصد_انباشته(pZip, file_شاخص, p_اندازه, flags);
}

mz_bool mz_zip_reader_استخراج_مقصد_callback(mz_zip_archive *pZip, mz_uint file_شاخص, mz_file_write_func pCallback, فراغ *pOpaque, mz_uint flags)
{
  صحيح وضعیت = TINFL_وضعیت_انجامشده; mz_uint file_بررسی_چرخهای_32 = MZ_بررسی_چرخهای_32_INIT;
  mz_uint64 read_buf_اندازه, read_buf_ofs = 0, read_buf_avail, comp_مانده, بیرون_buf_ofs = 0, cur_file_ofs;
  mz_zip_archive_file_stat file_stat;
  فراغ *pRead_buf = عدم; فراغ *pWrite_buf = عدم;
  mz_uint32 local_سرآیند_u32[(MZ_ZIP_LOCAL_DIR_سرآیند_اندازه + حجم(mz_uint32) - 1) / حجم(mz_uint32)]; mz_uint8 *p_Local_سرآیند = (mz_uint8 *)local_سرآیند_u32;

  إذا (!mz_zip_reader_file_stat(pZip, file_شاخص, &file_stat))
    أرجع MZ_FALSE;

  // Empty file, or a directory (but not always a directory - I've seen odd zips with directories that have compressed data which inflates to 0 bytes)
  إذا (!file_stat.m_comp_اندازه)
    أرجع MZ_TRUE;

  // Entry is a subdirectory (I've seen old zips with dir entries which have compressed deflate data which inflates to 0 bytes, but these entries claim to uncompress to 512 bytes in the headers).
  // I'm torn how to handle this case - should it fail instead?
  إذا (mz_zip_reader_is_file_a_directory(pZip, file_شاخص))
    أرجع MZ_TRUE;

  // Encryption and patch files are not supported.
  إذا (file_stat.m_بیت_flag & (1 | 32))
    أرجع MZ_FALSE;

  // This function only supports stored and deflate.
  إذا ((!(flags & MZ_ZIP_FLAG_COMPRESSED_داده)) && (file_stat.m_روش != 0) && (file_stat.m_روش != MZ_DEFLATED))
    أرجع MZ_FALSE;

  // Read and parse the local directory entry.
  cur_file_ofs = file_stat.m_local_سرآیند_ofs;
  إذا (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, p_Local_سرآیند, MZ_ZIP_LOCAL_DIR_سرآیند_اندازه) != MZ_ZIP_LOCAL_DIR_سرآیند_اندازه)
    أرجع MZ_FALSE;
  إذا (MZ_READ_LE32(p_Local_سرآیند) != MZ_ZIP_LOCAL_DIR_سرآیند_SIG)
    أرجع MZ_FALSE;

  cur_file_ofs += MZ_ZIP_LOCAL_DIR_سرآیند_اندازه + MZ_READ_LE16(p_Local_سرآیند + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p_Local_سرآیند + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  إذا ((cur_file_ofs + file_stat.m_comp_اندازه) > pZip->m_archive_اندازه)
    أرجع MZ_FALSE;

  // Decompress the file either directly from memory or from a file input buffer.
  إذا (pZip->m_pState->m_pMem)
  {
    pRead_buf = (mz_uint8 *)pZip->m_pState->m_pMem + cur_file_ofs;
    read_buf_اندازه = read_buf_avail = file_stat.m_comp_اندازه;
    comp_مانده = 0;
  }
  وإلا
  {
    read_buf_اندازه = MZ_MIN(file_stat.m_comp_اندازه, MZ_ZIP_MAX_IO_BUF_اندازه);
    إذا (عدم == (pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)read_buf_اندازه)))
      أرجع MZ_FALSE;
    read_buf_avail = 0;
    comp_مانده = file_stat.m_comp_اندازه;
  }

  إذا ((flags & MZ_ZIP_FLAG_COMPRESSED_داده) || (!file_stat.m_روش))
  {
    // The file is stored or the caller has requested the compressed data.
    إذا (pZip->m_pState->m_pMem)
    {
#اگر_تعریف_شده _MSC_VER
      إذا (((0, حجم(size_t) == حجم(mz_uint32))) && (file_stat.m_comp_اندازه > 0xFFFFFFFF))
#وإلا
      إذا (((حجم(size_t) == حجم(mz_uint32))) && (file_stat.m_comp_اندازه > 0xFFFFFFFF))
#پایان_اگر
        أرجع MZ_FALSE;
      إذا (pCallback(pOpaque, بیرون_buf_ofs, pRead_buf, (size_t)file_stat.m_comp_اندازه) != file_stat.m_comp_اندازه)
        وضعیت = TINFL_وضعیت_FAILED;
      وإلا إذا (!(flags & MZ_ZIP_FLAG_COMPRESSED_داده))
        file_بررسی_چرخهای_32 = (mz_uint32)mz_بررسی_چرخهای_32(file_بررسی_چرخهای_32, (ثابت mz_uint8 *)pRead_buf, (size_t)file_stat.m_comp_اندازه);
      cur_file_ofs += file_stat.m_comp_اندازه;
      بیرون_buf_ofs += file_stat.m_comp_اندازه;
      comp_مانده = 0;
    }
    وإلا
    {
      طالما (comp_مانده)
      {
        read_buf_avail = MZ_MIN(read_buf_اندازه, comp_مانده);
        إذا (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
        {
          وضعیت = TINFL_وضعیت_FAILED;
          اكسر;
        }

        إذا (!(flags & MZ_ZIP_FLAG_COMPRESSED_داده))
          file_بررسی_چرخهای_32 = (mz_uint32)mz_بررسی_چرخهای_32(file_بررسی_چرخهای_32, (ثابت mz_uint8 *)pRead_buf, (size_t)read_buf_avail);

        إذا (pCallback(pOpaque, بیرون_buf_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
        {
          وضعیت = TINFL_وضعیت_FAILED;
          اكسر;
        }
        cur_file_ofs += read_buf_avail;
        بیرون_buf_ofs += read_buf_avail;
        comp_مانده -= read_buf_avail;
      }
    }
  }
  وإلا
  {
    tinfl_decompressor inflator;
    tinfl_init(&inflator);

    إذا (عدم == (pWrite_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, TINFL_LZ_DICT_اندازه)))
      وضعیت = TINFL_وضعیت_FAILED;
    وإلا
    {
      افعل
      {
        mz_uint8 *pWrite_buf_cur = (mz_uint8 *)pWrite_buf + (بیرون_buf_ofs & (TINFL_LZ_DICT_اندازه - 1));
        size_t درون_buf_اندازه, بیرون_buf_اندازه = TINFL_LZ_DICT_اندازه - (بیرون_buf_ofs & (TINFL_LZ_DICT_اندازه - 1));
        إذا ((!read_buf_avail) && (!pZip->m_pState->m_pMem))
        {
          read_buf_avail = MZ_MIN(read_buf_اندازه, comp_مانده);
          إذا (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
          {
            وضعیت = TINFL_وضعیت_FAILED;
            اكسر;
          }
          cur_file_ofs += read_buf_avail;
          comp_مانده -= read_buf_avail;
          read_buf_ofs = 0;
        }

        درون_buf_اندازه = (size_t)read_buf_avail;
        وضعیت = tinfl_decompress(&inflator, (ثابت mz_uint8 *)pRead_buf + read_buf_ofs, &درون_buf_اندازه, (mz_uint8 *)pWrite_buf, pWrite_buf_cur, &بیرون_buf_اندازه, comp_مانده ? TINFL_FLAG_HAS_بیشتر_درون_داد : 0);
        read_buf_avail -= درون_buf_اندازه;
        read_buf_ofs += درون_buf_اندازه;

        إذا (بیرون_buf_اندازه)
        {
          إذا (pCallback(pOpaque, بیرون_buf_ofs, pWrite_buf_cur, بیرون_buf_اندازه) != بیرون_buf_اندازه)
          {
            وضعیت = TINFL_وضعیت_FAILED;
            اكسر;
          }
          file_بررسی_چرخهای_32 = (mz_uint32)mz_بررسی_چرخهای_32(file_بررسی_چرخهای_32, pWrite_buf_cur, بیرون_buf_اندازه);
          إذا ((بیرون_buf_ofs += بیرون_buf_اندازه) > file_stat.m_uncomp_اندازه)
          {
            وضعیت = TINFL_وضعیت_FAILED;
            اكسر;
          }
        }
      } طالما ((وضعیت == TINFL_وضعیت_NEEDS_بیشتر_درون_داد) || (وضعیت == TINFL_وضعیت_HAS_بیشتر_OUTPUT));
    }
  }

  إذا ((وضعیت == TINFL_وضعیت_انجامشده) && (!(flags & MZ_ZIP_FLAG_COMPRESSED_داده)))
  {
    // Make sure the entire file was decompressed, and check its CRC.
    إذا ((بیرون_buf_ofs != file_stat.m_uncomp_اندازه) || (file_بررسی_چرخهای_32 != file_stat.m_بررسی_چرخهای_32))
      وضعیت = TINFL_وضعیت_FAILED;
  }

  إذا (!pZip->m_pState->m_pMem)
    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
  إذا (pWrite_buf)
    pZip->m_pFree(pZip->m_pAlloc_opaque, pWrite_buf);

  أرجع وضعیت == TINFL_وضعیت_انجامشده;
}

mz_bool mz_zip_reader_استخراج_file_مقصد_callback(mz_zip_archive *pZip, ثابت حرف *pFilename, mz_file_write_func pCallback, فراغ *pOpaque, mz_uint flags)
{
  صحيح file_شاخص = mz_zip_reader_locate_file(pZip, pFilename, عدم, flags);
  إذا (file_شاخص < 0)
    أرجع MZ_FALSE;
  أرجع mz_zip_reader_استخراج_مقصد_callback(pZip, file_شاخص, pCallback, pOpaque, flags);
}

#اگر_تعریف_نشده MINIZ_NO_STDIO
ساكن size_t mz_zip_file_write_callback(فراغ *pOpaque, mz_uint64 ofs, ثابت فراغ *pBuf, size_t n)
{
  (فراغ)ofs; أرجع MZ_FWRITE(pBuf, 1, n, (MZ_FILE*)pOpaque);
}

mz_bool mz_zip_reader_استخراج_مقصد_file(mz_zip_archive *pZip, mz_uint file_شاخص, ثابت حرف *pDst_filename, mz_uint flags)
{
  mz_bool وضعیت;
  mz_zip_archive_file_stat file_stat;
  MZ_FILE *pFile;
  إذا (!mz_zip_reader_file_stat(pZip, file_شاخص, &file_stat))
    أرجع MZ_FALSE;
  pFile = MZ_FOPEN(pDst_filename, "wb");
  إذا (!pFile)
    أرجع MZ_FALSE;
  وضعیت = mz_zip_reader_استخراج_مقصد_callback(pZip, file_شاخص, mz_zip_file_write_callback, pFile, flags);
  إذا (MZ_FCLOSE(pFile) == EOF)
    أرجع MZ_FALSE;
#اگر_تعریف_نشده MINIZ_NO_زمان
  إذا (وضعیت)
    mz_zip_مجموعه_file_times(pDst_filename, file_stat.m_زمان, file_stat.m_زمان);
#پایان_اگر
  أرجع وضعیت;
}
#پایان_اگر // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_reader_انتها(mz_zip_archive *pZip)
{
  إذا ((!pZip) || (!pZip->m_pState) || (!pZip->m_pAlloc) || (!pZip->m_pFree) || (pZip->m_zip_نما != MZ_ZIP_نما_READING))
    أرجع MZ_FALSE;

  إذا (pZip->m_pState)
  {
    mz_zip_داخلی_state *pState = pZip->m_pState; pZip->m_pState = عدم;
    mz_zip_array_clear(pZip, &pState->m_central_dir);
    mz_zip_array_clear(pZip, &pState->m_central_dir_offsets);
    mz_zip_array_clear(pZip, &pState->m_sorted_central_dir_offsets);

#اگر_تعریف_نشده MINIZ_NO_STDIO
    إذا (pState->m_pFile)
    {
      MZ_FCLOSE(pState->m_pFile);
      pState->m_pFile = عدم;
    }
#پایان_اگر // #ifndef MINIZ_NO_STDIO

    pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
  }
  pZip->m_zip_نما = MZ_ZIP_نما_INVALID;

  أرجع MZ_TRUE;
}

#اگر_تعریف_نشده MINIZ_NO_STDIO
mz_bool mz_zip_reader_استخراج_file_مقصد_file(mz_zip_archive *pZip, ثابت حرف *pArchive_filename, ثابت حرف *pDst_filename, mz_uint flags)
{
  صحيح file_شاخص = mz_zip_reader_locate_file(pZip, pArchive_filename, عدم, flags);
  إذا (file_شاخص < 0)
    أرجع MZ_FALSE;
  أرجع mz_zip_reader_استخراج_مقصد_file(pZip, file_شاخص, pDst_filename, flags);
}
#پایان_اگر

// ------------------- .ZIP archive writing

#اگر_تعریف_نشده MINIZ_NO_ARCHIVE_WRITING_APIS

ساكن فراغ mz_write_le16(mz_uint8 *p, mz_uint16 v) { p[0] = (mz_uint8)v; p[1] = (mz_uint8)(v >> 8); }
ساكن فراغ mz_write_le32(mz_uint8 *p, mz_uint32 v) { p[0] = (mz_uint8)v; p[1] = (mz_uint8)(v >> 8); p[2] = (mz_uint8)(v >> 16); p[3] = (mz_uint8)(v >> 24); }
#تعریف_کن MZ_WRITE_LE16(p, v) mz_write_le16((mz_uint8 *)(p), (mz_uint16)(v))
#تعریف_کن MZ_WRITE_LE32(p, v) mz_write_le32((mz_uint8 *)(p), (mz_uint32)(v))

mz_bool mz_zip_writer_init(mz_zip_archive *pZip, mz_uint64 existing_اندازه)
{
  إذا ((!pZip) || (pZip->m_pState) || (!pZip->m_pWrite) || (pZip->m_zip_نما != MZ_ZIP_نما_INVALID))
    أرجع MZ_FALSE;

  إذا (pZip->m_file_جابه_جایی_alignment)
  {
    // Ensure user specified file offset alignment is a power of 2.
    إذا (pZip->m_file_جابه_جایی_alignment & (pZip->m_file_جابه_جایی_alignment - 1))
      أرجع MZ_FALSE;
  }

  إذا (!pZip->m_pAlloc) pZip->m_pAlloc = def_alloc_func;
  إذا (!pZip->m_pFree) pZip->m_pFree = def_free_func;
  إذا (!pZip->m_pRealloc) pZip->m_pRealloc = def_realloc_func;

  pZip->m_zip_نما = MZ_ZIP_نما_WRITING;
  pZip->m_archive_اندازه = existing_اندازه;
  pZip->m_central_directory_file_ofs = 0;
  pZip->m_مجموع_files = 0;

  إذا (عدم == (pZip->m_pState = (mz_zip_داخلی_state *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, حجم(mz_zip_داخلی_state))))
    أرجع MZ_FALSE;
  memset(pZip->m_pState, 0, حجم(mz_zip_داخلی_state));
  MZ_ZIP_ARRAY_مجموعه_ELEMENT_اندازه(&pZip->m_pState->m_central_dir, حجم(mz_uint8));
  MZ_ZIP_ARRAY_مجموعه_ELEMENT_اندازه(&pZip->m_pState->m_central_dir_offsets, حجم(mz_uint32));
  MZ_ZIP_ARRAY_مجموعه_ELEMENT_اندازه(&pZip->m_pState->m_sorted_central_dir_offsets, حجم(mz_uint32));
  أرجع MZ_TRUE;
}

ساكن size_t mz_zip_انباشته_write_func(فراغ *pOpaque, mz_uint64 file_ofs, ثابت فراغ *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_zip_داخلی_state *pState = pZip->m_pState;
  mz_uint64 new_اندازه = MZ_MAX(file_ofs + n, pState->m_mem_اندازه);
#اگر_تعریف_شده _MSC_VER
  إذا ((!n) || ((0, حجم(size_t) == حجم(mz_uint32)) && (new_اندازه > 0x7FFFFFFF)))
#وإلا
  إذا ((!n) || ((حجم(size_t) == حجم(mz_uint32)) && (new_اندازه > 0x7FFFFFFF)))
#پایان_اگر
    أرجع 0;
  إذا (new_اندازه > pState->m_mem_ظرفیت)
  {
    فراغ *p_New_بلوک;
    size_t new_ظرفیت = MZ_MAX(64, pState->m_mem_ظرفیت); طالما (new_ظرفیت < new_اندازه) new_ظرفیت *= 2;
    إذا (عدم == (p_New_بلوک = pZip->m_pRealloc(pZip->m_pAlloc_opaque, pState->m_pMem, 1, new_ظرفیت)))
      أرجع 0;
    pState->m_pMem = p_New_بلوک; pState->m_mem_ظرفیت = new_ظرفیت;
  }
  کپی_حافظه((mz_uint8 *)pState->m_pMem + file_ofs, pBuf, n);
  pState->m_mem_اندازه = (size_t)new_اندازه;
  أرجع n;
}

mz_bool mz_zip_writer_init_انباشته(mz_zip_archive *pZip, size_t اندازه_مقصد_reserve_at_beginning, size_t initial_تخصیص_اندازه)
{
  pZip->m_pWrite = mz_zip_انباشته_write_func;
  pZip->m_pIO_opaque = pZip;
  إذا (!mz_zip_writer_init(pZip, اندازه_مقصد_reserve_at_beginning))
    أرجع MZ_FALSE;
  إذا (0 != (initial_تخصیص_اندازه = MZ_MAX(initial_تخصیص_اندازه, اندازه_مقصد_reserve_at_beginning)))
  {
    إذا (عدم == (pZip->m_pState->m_pMem = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, initial_تخصیص_اندازه)))
    {
      mz_zip_writer_انتها(pZip);
      أرجع MZ_FALSE;
    }
    pZip->m_pState->m_mem_ظرفیت = initial_تخصیص_اندازه;
  }
  أرجع MZ_TRUE;
}

#اگر_تعریف_نشده MINIZ_NO_STDIO
ساكن size_t mz_zip_file_write_func(فراغ *pOpaque, mz_uint64 file_ofs, ثابت فراغ *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_int64 cur_ofs = MZ_FTELL64(pZip->m_pState->m_pFile);
  إذا (((mz_int64)file_ofs < 0) || (((cur_ofs != (mz_int64)file_ofs)) && (MZ_FSEEK64(pZip->m_pState->m_pFile, (mz_int64)file_ofs, SEEK_SET))))
    أرجع 0;
  أرجع MZ_FWRITE(pBuf, 1, n, pZip->m_pState->m_pFile);
}

mz_bool mz_zip_writer_init_file(mz_zip_archive *pZip, ثابت حرف *pFilename, mz_uint64 اندازه_مقصد_reserve_at_beginning)
{
  MZ_FILE *pFile;
  pZip->m_pWrite = mz_zip_file_write_func;
  pZip->m_pIO_opaque = pZip;
  إذا (!mz_zip_writer_init(pZip, اندازه_مقصد_reserve_at_beginning))
    أرجع MZ_FALSE;
  إذا (عدم == (pFile = MZ_FOPEN(pFilename, "wb")))
  {
    mz_zip_writer_انتها(pZip);
    أرجع MZ_FALSE;
  }
  pZip->m_pState->m_pFile = pFile;
  إذا (اندازه_مقصد_reserve_at_beginning)
  {
    mz_uint64 cur_ofs = 0; حرف buf[4096]; MZ_CLEAR_ARR(buf);
    افعل
    {
      size_t n = (size_t)MZ_MIN(حجم(buf), اندازه_مقصد_reserve_at_beginning);
      إذا (pZip->m_pWrite(pZip->m_pIO_opaque, cur_ofs, buf, n) != n)
      {
        mz_zip_writer_انتها(pZip);
        أرجع MZ_FALSE;
      }
      cur_ofs += n; اندازه_مقصد_reserve_at_beginning -= n;
    } طالما (اندازه_مقصد_reserve_at_beginning);
  }
  أرجع MZ_TRUE;
}
#پایان_اگر // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_writer_init_from_reader(mz_zip_archive *pZip, ثابت حرف *pFilename)
{
  mz_zip_داخلی_state *pState;
  إذا ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_نما != MZ_ZIP_نما_READING))
    أرجع MZ_FALSE;
  // No sense in trying to write to an archive that's already at the support max size
  إذا ((pZip->m_مجموع_files == 0xFFFF) || ((pZip->m_archive_اندازه + MZ_ZIP_CENTRAL_DIR_سرآیند_اندازه + MZ_ZIP_LOCAL_DIR_سرآیند_اندازه) > 0xFFFFFFFF))
    أرجع MZ_FALSE;

  pState = pZip->m_pState;

  إذا (pState->m_pFile)
  {
#اگر_تعریف_شده MINIZ_NO_STDIO
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
      mz_zip_reader_انتها(pZip);
      أرجع MZ_FALSE;
    }
#پایان_اگر // #ifdef MINIZ_NO_STDIO
  }
  وإلا إذا (pState->m_pMem)
  {
    // Archive lives in a memory block. Assume it's from the heap that we can resize using the realloc callback.
    إذا (pZip->m_pIO_opaque != pZip)
      أرجع MZ_FALSE;
    pState->m_mem_ظرفیت = pState->m_mem_اندازه;
    pZip->m_pWrite = mz_zip_انباشته_write_func;
  }
  // Archive is being read via a user provided read function - make sure the user has specified a write function too.
  وإلا إذا (!pZip->m_pWrite)
    أرجع MZ_FALSE;

  // Start writing new files at the archive's current central directory location.
  pZip->m_archive_اندازه = pZip->m_central_directory_file_ofs;
  pZip->m_zip_نما = MZ_ZIP_نما_WRITING;
  pZip->m_central_directory_file_ofs = 0;

  أرجع MZ_TRUE;
}

mz_bool mz_zip_writer_جمع_کن_mem(mz_zip_archive *pZip, ثابت حرف *pArchive_name, ثابت فراغ *pBuf, size_t buf_اندازه_2, mz_uint level_and_flags)
{
  أرجع mz_zip_writer_جمع_کن_mem_ex(pZip, pArchive_name, pBuf, buf_اندازه_2, عدم, 0, level_and_flags, 0, 0);
}

تعريفنوع بنية
{
  mz_zip_archive *m_pZip;
  mz_uint64 m_cur_archive_file_ofs;
  mz_uint64 m_comp_اندازه;
} mz_zip_writer_جمع_کن_state;

ساكن mz_bool mz_zip_writer_جمع_کن_put_buf_callback(ثابت فراغ* pBuf, صحيح len, فراغ *pUser)
{
  mz_zip_writer_جمع_کن_state *pState = (mz_zip_writer_جمع_کن_state *)pUser;
  إذا ((صحيح)pState->m_pZip->m_pWrite(pState->m_pZip->m_pIO_opaque, pState->m_cur_archive_file_ofs, pBuf, len) != len)
    أرجع MZ_FALSE;
  pState->m_cur_archive_file_ofs += len;
  pState->m_comp_اندازه += len;
  أرجع MZ_TRUE;
}

ساكن mz_bool mz_zip_writer_create_local_dir_سرآیند(mz_zip_archive *pZip, mz_uint8 *pDst, mz_uint16 filename_اندازه, mz_uint16 extra_اندازه, mz_uint64 uncomp_اندازه, mz_uint64 comp_اندازه, mz_uint32 uncomp_بررسی_چرخهای_32, mz_uint16 روش, mz_uint16 بیت_flags, mz_uint16 dos_زمان, mz_uint16 dos_date)
{
  (فراغ)pZip;
  memset(pDst, 0, MZ_ZIP_LOCAL_DIR_سرآیند_اندازه);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_SIG_OFS, MZ_ZIP_LOCAL_DIR_سرآیند_SIG);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_نسخه_NEEDED_OFS, روش ? 20 : 0);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_بیت_FLAG_OFS, بیت_flags);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_روش_OFS, روش);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILE_زمان_OFS, dos_زمان);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILE_DATE_OFS, dos_date);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_بررسی_چرخهای_32_OFS, uncomp_بررسی_چرخهای_32);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_COMPRESSED_اندازه_OFS, comp_اندازه);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_DECOMPRESSED_اندازه_OFS, uncomp_اندازه);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILENAME_LEN_OFS, filename_اندازه);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_EXTRA_LEN_OFS, extra_اندازه);
  أرجع MZ_TRUE;
}

ساكن mz_bool mz_zip_writer_create_central_dir_سرآیند(mz_zip_archive *pZip, mz_uint8 *pDst, mz_uint16 filename_اندازه, mz_uint16 extra_اندازه, mz_uint16 comment_اندازه, mz_uint64 uncomp_اندازه, mz_uint64 comp_اندازه, mz_uint32 uncomp_بررسی_چرخهای_32, mz_uint16 روش, mz_uint16 بیت_flags, mz_uint16 dos_زمان, mz_uint16 dos_date, mz_uint64 local_سرآیند_ofs, mz_uint32 ext_صفات)
{
  (فراغ)pZip;
  memset(pDst, 0, MZ_ZIP_CENTRAL_DIR_سرآیند_اندازه);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_SIG_OFS, MZ_ZIP_CENTRAL_DIR_سرآیند_SIG);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_نسخه_NEEDED_OFS, روش ? 20 : 0);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_بیت_FLAG_OFS, بیت_flags);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_روش_OFS, روش);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILE_زمان_OFS, dos_زمان);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILE_DATE_OFS, dos_date);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_بررسی_چرخهای_32_OFS, uncomp_بررسی_چرخهای_32);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_COMPRESSED_اندازه_OFS, comp_اندازه);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_DECOMPRESSED_اندازه_OFS, uncomp_اندازه);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILENAME_LEN_OFS, filename_اندازه);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_EXTRA_LEN_OFS, extra_اندازه);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_COMMENT_LEN_OFS, comment_اندازه);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS, ext_صفات);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_LOCAL_سرآیند_OFS, local_سرآیند_ofs);
  أرجع MZ_TRUE;
}

ساكن mz_bool mz_zip_writer_جمع_کن_مقصد_central_dir(mz_zip_archive *pZip, ثابت حرف *pFilename, mz_uint16 filename_اندازه, ثابت فراغ *pExtra, mz_uint16 extra_اندازه, ثابت فراغ *pComment, mz_uint16 comment_اندازه, mz_uint64 uncomp_اندازه, mz_uint64 comp_اندازه, mz_uint32 uncomp_بررسی_چرخهای_32, mz_uint16 روش, mz_uint16 بیت_flags, mz_uint16 dos_زمان, mz_uint16 dos_date, mz_uint64 local_سرآیند_ofs, mz_uint32 ext_صفات)
{
  mz_zip_داخلی_state *pState = pZip->m_pState;
  mz_uint32 central_dir_ofs = (mz_uint32)pState->m_central_dir.m_اندازه;
  size_t orig_central_dir_اندازه = pState->m_central_dir.m_اندازه;
  mz_uint8 central_dir_سرآیند[MZ_ZIP_CENTRAL_DIR_سرآیند_اندازه];

  // No zip64 support yet
  إذا ((local_سرآیند_ofs > 0xFFFFFFFF) || (((mz_uint64)pState->m_central_dir.m_اندازه + MZ_ZIP_CENTRAL_DIR_سرآیند_اندازه + filename_اندازه + extra_اندازه + comment_اندازه) > 0xFFFFFFFF))
    أرجع MZ_FALSE;

  إذا (!mz_zip_writer_create_central_dir_سرآیند(pZip, central_dir_سرآیند, filename_اندازه, extra_اندازه, comment_اندازه, uncomp_اندازه, comp_اندازه, uncomp_بررسی_چرخهای_32, روش, بیت_flags, dos_زمان, dos_date, local_سرآیند_ofs, ext_صفات))
    أرجع MZ_FALSE;

  إذا ((!mz_zip_array_افزودن_پشت(pZip, &pState->m_central_dir, central_dir_سرآیند, MZ_ZIP_CENTRAL_DIR_سرآیند_اندازه)) ||
      (!mz_zip_array_افزودن_پشت(pZip, &pState->m_central_dir, pFilename, filename_اندازه)) ||
      (!mz_zip_array_افزودن_پشت(pZip, &pState->m_central_dir, pExtra, extra_اندازه)) ||
      (!mz_zip_array_افزودن_پشت(pZip, &pState->m_central_dir, pComment, comment_اندازه)) ||
      (!mz_zip_array_افزودن_پشت(pZip, &pState->m_central_dir_offsets, &central_dir_ofs, 1)))
  {
    // Try to push the central directory array back into its original state.
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_اندازه, MZ_FALSE);
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
  إذا (!pZip->m_file_جابه_جایی_alignment)
    أرجع 0;
  n = (mz_uint32)(pZip->m_archive_اندازه & (pZip->m_file_جابه_جایی_alignment - 1));
  أرجع (pZip->m_file_جابه_جایی_alignment - n) & (pZip->m_file_جابه_جایی_alignment - 1);
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

mz_bool mz_zip_writer_جمع_کن_mem_ex(mz_zip_archive *pZip, ثابت حرف *pArchive_name, ثابت فراغ *pBuf, size_t buf_اندازه_2, ثابت فراغ *pComment, mz_uint16 comment_اندازه, mz_uint level_and_flags, mz_uint64 uncomp_اندازه, mz_uint32 uncomp_بررسی_چرخهای_32)
{
  mz_uint16 روش = 0, dos_زمان = 0, dos_date = 0;
  mz_uint level, ext_صفات = 0, رقم_alignment_padding_بایتها;
  mz_uint64 local_dir_سرآیند_ofs = pZip->m_archive_اندازه, cur_archive_file_ofs = pZip->m_archive_اندازه, comp_اندازه = 0;
  size_t archive_name_اندازه;
  mz_uint8 local_dir_سرآیند[MZ_ZIP_LOCAL_DIR_سرآیند_اندازه];
  tdefl_compressor *pComp = عدم;
  mz_bool store_داده_uncompressed;
  mz_zip_داخلی_state *pState;

  إذا ((صحيح)level_and_flags < 0)
    level_and_flags = MZ_DEFAULT_LEVEL;
  level = level_and_flags & 0xF;
  store_داده_uncompressed = ((!level) || (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_داده));

  إذا ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_نما != MZ_ZIP_نما_WRITING) || ((buf_اندازه_2) && (!pBuf)) || (!pArchive_name) || ((comment_اندازه) && (!pComment)) || (pZip->m_مجموع_files == 0xFFFF) || (level > MZ_UBER_COMPRESSION))
    أرجع MZ_FALSE;

  pState = pZip->m_pState;

  إذا ((!(level_and_flags & MZ_ZIP_FLAG_COMPRESSED_داده)) && (uncomp_اندازه))
    أرجع MZ_FALSE;
  // No zip64 support yet
  إذا ((buf_اندازه_2 > 0xFFFFFFFF) || (uncomp_اندازه > 0xFFFFFFFF))
    أرجع MZ_FALSE;
  إذا (!mz_zip_writer_validate_archive_name(pArchive_name))
    أرجع MZ_FALSE;

#اگر_تعریف_نشده MINIZ_NO_زمان
  {
    زمان_t cur_زمان; زمان(&cur_زمان);
    mz_zip_زمان_مقصد_dos_زمان(cur_زمان, &dos_زمان, &dos_date);
  }
#پایان_اگر // #ifndef MINIZ_NO_TIME

  archive_name_اندازه = طول_رشته(pArchive_name);
  إذا (archive_name_اندازه > 0xFFFF)
    أرجع MZ_FALSE;

  رقم_alignment_padding_بایتها = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  إذا ((pZip->m_مجموع_files == 0xFFFF) || ((pZip->m_archive_اندازه + رقم_alignment_padding_بایتها + MZ_ZIP_LOCAL_DIR_سرآیند_اندازه + MZ_ZIP_CENTRAL_DIR_سرآیند_اندازه + comment_اندازه + archive_name_اندازه) > 0xFFFFFFFF))
    أرجع MZ_FALSE;

  إذا ((archive_name_اندازه) && (pArchive_name[archive_name_اندازه - 1] == '/'))
  {
    // Set DOS Subdirectory attribute bit.
    ext_صفات |= 0x10;
    // Subdirectories cannot contain data.
    إذا ((buf_اندازه_2) || (uncomp_اندازه))
      أرجع MZ_FALSE;
  }

  // Try to do any allocations before writing to the archive, so if an allocation fails the file remains unmodified. (A good idea if we're doing an in-place modification.)
  إذا ((!mz_zip_array_ensure_جا(pZip, &pState->m_central_dir, MZ_ZIP_CENTRAL_DIR_سرآیند_اندازه + archive_name_اندازه + comment_اندازه)) || (!mz_zip_array_ensure_جا(pZip, &pState->m_central_dir_offsets, 1)))
    أرجع MZ_FALSE;

  إذا ((!store_داده_uncompressed) && (buf_اندازه_2))
  {
    إذا (عدم == (pComp = (tdefl_compressor *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, حجم(tdefl_compressor))))
      أرجع MZ_FALSE;
  }

  إذا (!mz_zip_writer_write_zeros(pZip, cur_archive_file_ofs, رقم_alignment_padding_بایتها + حجم(local_dir_سرآیند)))
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
    أرجع MZ_FALSE;
  }
  local_dir_سرآیند_ofs += رقم_alignment_padding_بایتها;
  إذا (pZip->m_file_جابه_جایی_alignment) { MZ_ASSERT((local_dir_سرآیند_ofs & (pZip->m_file_جابه_جایی_alignment - 1)) == 0); }
  cur_archive_file_ofs += رقم_alignment_padding_بایتها + حجم(local_dir_سرآیند);

  MZ_CLEAR_ARR(local_dir_سرآیند);
  إذا (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pArchive_name, archive_name_اندازه) != archive_name_اندازه)
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
    أرجع MZ_FALSE;
  }
  cur_archive_file_ofs += archive_name_اندازه;

  إذا (!(level_and_flags & MZ_ZIP_FLAG_COMPRESSED_داده))
  {
    uncomp_بررسی_چرخهای_32 = (mz_uint32)mz_بررسی_چرخهای_32(MZ_بررسی_چرخهای_32_INIT, (ثابت mz_uint8*)pBuf, buf_اندازه_2);
    uncomp_اندازه = buf_اندازه_2;
    إذا (uncomp_اندازه <= 3)
    {
      level = 0;
      store_داده_uncompressed = MZ_TRUE;
    }
  }

  إذا (store_داده_uncompressed)
  {
    إذا (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pBuf, buf_اندازه_2) != buf_اندازه_2)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
      أرجع MZ_FALSE;
    }

    cur_archive_file_ofs += buf_اندازه_2;
    comp_اندازه = buf_اندازه_2;

    إذا (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_داده)
      روش = MZ_DEFLATED;
  }
  وإلا إذا (buf_اندازه_2)
  {
    mz_zip_writer_جمع_کن_state state;

    state.m_pZip = pZip;
    state.m_cur_archive_file_ofs = cur_archive_file_ofs;
    state.m_comp_اندازه = 0;

    إذا ((tdefl_init(pComp, mz_zip_writer_جمع_کن_put_buf_callback, &state, tdefl_create_comp_flags_from_zip_params(level, -15, MZ_DEFAULT_STRATEGY)) != TDEFL_وضعیت_OKAY) ||
        (tdefl_compress_میانگیر(pComp, pBuf, buf_اندازه_2, TDEFL_پایان) != TDEFL_وضعیت_انجامشده))
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
      أرجع MZ_FALSE;
    }

    comp_اندازه = state.m_comp_اندازه;
    cur_archive_file_ofs = state.m_cur_archive_file_ofs;

    روش = MZ_DEFLATED;
  }

  pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
  pComp = عدم;

  // no zip64 support yet
  إذا ((comp_اندازه > 0xFFFFFFFF) || (cur_archive_file_ofs > 0xFFFFFFFF))
    أرجع MZ_FALSE;

  إذا (!mz_zip_writer_create_local_dir_سرآیند(pZip, local_dir_سرآیند, (mz_uint16)archive_name_اندازه, 0, uncomp_اندازه, comp_اندازه, uncomp_بررسی_چرخهای_32, روش, 0, dos_زمان, dos_date))
    أرجع MZ_FALSE;

  إذا (pZip->m_pWrite(pZip->m_pIO_opaque, local_dir_سرآیند_ofs, local_dir_سرآیند, حجم(local_dir_سرآیند)) != حجم(local_dir_سرآیند))
    أرجع MZ_FALSE;

  إذا (!mz_zip_writer_جمع_کن_مقصد_central_dir(pZip, pArchive_name, (mz_uint16)archive_name_اندازه, عدم, 0, pComment, comment_اندازه, uncomp_اندازه, comp_اندازه, uncomp_بررسی_چرخهای_32, روش, 0, dos_زمان, dos_date, local_dir_سرآیند_ofs, ext_صفات))
    أرجع MZ_FALSE;

  pZip->m_مجموع_files++;
  pZip->m_archive_اندازه = cur_archive_file_ofs;

  أرجع MZ_TRUE;
}

#اگر_تعریف_نشده MINIZ_NO_STDIO
mz_bool mz_zip_writer_جمع_کن_file(mz_zip_archive *pZip, ثابت حرف *pArchive_name, ثابت حرف *pSrc_filename, ثابت فراغ *pComment, mz_uint16 comment_اندازه, mz_uint level_and_flags)
{
  mz_uint uncomp_بررسی_چرخهای_32 = MZ_بررسی_چرخهای_32_INIT, level, رقم_alignment_padding_بایتها;
  mz_uint16 روش = 0, dos_زمان = 0, dos_date = 0, ext_صفات = 0;
  mz_uint64 local_dir_سرآیند_ofs = pZip->m_archive_اندازه, cur_archive_file_ofs = pZip->m_archive_اندازه, uncomp_اندازه = 0, comp_اندازه = 0;
  size_t archive_name_اندازه;
  mz_uint8 local_dir_سرآیند[MZ_ZIP_LOCAL_DIR_سرآیند_اندازه];
  MZ_FILE *pSrc_file = عدم;

  إذا ((صحيح)level_and_flags < 0)
    level_and_flags = MZ_DEFAULT_LEVEL;
  level = level_and_flags & 0xF;

  إذا ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_نما != MZ_ZIP_نما_WRITING) || (!pArchive_name) || ((comment_اندازه) && (!pComment)) || (level > MZ_UBER_COMPRESSION))
    أرجع MZ_FALSE;
  إذا (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_داده)
    أرجع MZ_FALSE;
  إذا (!mz_zip_writer_validate_archive_name(pArchive_name))
    أرجع MZ_FALSE;

  archive_name_اندازه = طول_رشته(pArchive_name);
  إذا (archive_name_اندازه > 0xFFFF)
    أرجع MZ_FALSE;

  رقم_alignment_padding_بایتها = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  إذا ((pZip->m_مجموع_files == 0xFFFF) || ((pZip->m_archive_اندازه + رقم_alignment_padding_بایتها + MZ_ZIP_LOCAL_DIR_سرآیند_اندازه + MZ_ZIP_CENTRAL_DIR_سرآیند_اندازه + comment_اندازه + archive_name_اندازه) > 0xFFFFFFFF))
    أرجع MZ_FALSE;

  إذا (!mz_zip_get_file_modified_زمان(pSrc_filename, &dos_زمان, &dos_date))
    أرجع MZ_FALSE;

  pSrc_file = MZ_FOPEN(pSrc_filename, "rb");
  إذا (!pSrc_file)
    أرجع MZ_FALSE;
  MZ_FSEEK64(pSrc_file, 0, SEEK_END);
  uncomp_اندازه = MZ_FTELL64(pSrc_file);
  MZ_FSEEK64(pSrc_file, 0, SEEK_SET);

  إذا (uncomp_اندازه > 0xFFFFFFFF)
  {
    // No zip64 support yet
    MZ_FCLOSE(pSrc_file);
    أرجع MZ_FALSE;
  }
  إذا (uncomp_اندازه <= 3)
    level = 0;

  إذا (!mz_zip_writer_write_zeros(pZip, cur_archive_file_ofs, رقم_alignment_padding_بایتها + حجم(local_dir_سرآیند)))
  {
    MZ_FCLOSE(pSrc_file);
    أرجع MZ_FALSE;
  }
  local_dir_سرآیند_ofs += رقم_alignment_padding_بایتها;
  إذا (pZip->m_file_جابه_جایی_alignment) { MZ_ASSERT((local_dir_سرآیند_ofs & (pZip->m_file_جابه_جایی_alignment - 1)) == 0); }
  cur_archive_file_ofs += رقم_alignment_padding_بایتها + حجم(local_dir_سرآیند);

  MZ_CLEAR_ARR(local_dir_سرآیند);
  إذا (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pArchive_name, archive_name_اندازه) != archive_name_اندازه)
  {
    MZ_FCLOSE(pSrc_file);
    أرجع MZ_FALSE;
  }
  cur_archive_file_ofs += archive_name_اندازه;

  إذا (uncomp_اندازه)
  {
    mz_uint64 uncomp_مانده = uncomp_اندازه;
    فراغ *pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, MZ_ZIP_MAX_IO_BUF_اندازه);
    إذا (!pRead_buf)
    {
      MZ_FCLOSE(pSrc_file);
      أرجع MZ_FALSE;
    }

    إذا (!level)
    {
      طالما (uncomp_مانده)
      {
        mz_uint n = (mz_uint)MZ_MIN(MZ_ZIP_MAX_IO_BUF_اندازه, uncomp_مانده);
        إذا ((MZ_FREAD(pRead_buf, 1, n, pSrc_file) != n) || (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pRead_buf, n) != n))
        {
          pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
          MZ_FCLOSE(pSrc_file);
          أرجع MZ_FALSE;
        }
        uncomp_بررسی_چرخهای_32 = (mz_uint32)mz_بررسی_چرخهای_32(uncomp_بررسی_چرخهای_32, (ثابت mz_uint8 *)pRead_buf, n);
        uncomp_مانده -= n;
        cur_archive_file_ofs += n;
      }
      comp_اندازه = uncomp_اندازه;
    }
    وإلا
    {
      mz_bool نتیجه = MZ_FALSE;
      mz_zip_writer_جمع_کن_state state;
      tdefl_compressor *pComp = (tdefl_compressor *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, حجم(tdefl_compressor));
      إذا (!pComp)
      {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        أرجع MZ_FALSE;
      }

      state.m_pZip = pZip;
      state.m_cur_archive_file_ofs = cur_archive_file_ofs;
      state.m_comp_اندازه = 0;

      إذا (tdefl_init(pComp, mz_zip_writer_جمع_کن_put_buf_callback, &state, tdefl_create_comp_flags_from_zip_params(level, -15, MZ_DEFAULT_STRATEGY)) != TDEFL_وضعیت_OKAY)
      {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        أرجع MZ_FALSE;
      }

      لكل ( ; ; )
      {
        size_t درون_buf_اندازه = (mz_uint32)MZ_MIN(uncomp_مانده, MZ_ZIP_MAX_IO_BUF_اندازه);
        tdefl_وضعیت وضعیت;

        إذا (MZ_FREAD(pRead_buf, 1, درون_buf_اندازه, pSrc_file) != درون_buf_اندازه)
          اكسر;

        uncomp_بررسی_چرخهای_32 = (mz_uint32)mz_بررسی_چرخهای_32(uncomp_بررسی_چرخهای_32, (ثابت mz_uint8 *)pRead_buf, درون_buf_اندازه);
        uncomp_مانده -= درون_buf_اندازه;

        وضعیت = tdefl_compress_میانگیر(pComp, pRead_buf, درون_buf_اندازه, uncomp_مانده ? TDEFL_NO_FLUSH : TDEFL_پایان);
        إذا (وضعیت == TDEFL_وضعیت_انجامشده)
        {
          نتیجه = MZ_TRUE;
          اكسر;
        }
        وإلا إذا (وضعیت != TDEFL_وضعیت_OKAY)
          اكسر;
      }

      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);

      إذا (!نتیجه)
      {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        أرجع MZ_FALSE;
      }

      comp_اندازه = state.m_comp_اندازه;
      cur_archive_file_ofs = state.m_cur_archive_file_ofs;

      روش = MZ_DEFLATED;
    }

    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
  }

  MZ_FCLOSE(pSrc_file); pSrc_file = عدم;

  // no zip64 support yet
  إذا ((comp_اندازه > 0xFFFFFFFF) || (cur_archive_file_ofs > 0xFFFFFFFF))
    أرجع MZ_FALSE;

  إذا (!mz_zip_writer_create_local_dir_سرآیند(pZip, local_dir_سرآیند, (mz_uint16)archive_name_اندازه, 0, uncomp_اندازه, comp_اندازه, uncomp_بررسی_چرخهای_32, روش, 0, dos_زمان, dos_date))
    أرجع MZ_FALSE;

  إذا (pZip->m_pWrite(pZip->m_pIO_opaque, local_dir_سرآیند_ofs, local_dir_سرآیند, حجم(local_dir_سرآیند)) != حجم(local_dir_سرآیند))
    أرجع MZ_FALSE;

  إذا (!mz_zip_writer_جمع_کن_مقصد_central_dir(pZip, pArchive_name, (mz_uint16)archive_name_اندازه, عدم, 0, pComment, comment_اندازه, uncomp_اندازه, comp_اندازه, uncomp_بررسی_چرخهای_32, روش, 0, dos_زمان, dos_date, local_dir_سرآیند_ofs, ext_صفات))
    أرجع MZ_FALSE;

  pZip->m_مجموع_files++;
  pZip->m_archive_اندازه = cur_archive_file_ofs;

  أرجع MZ_TRUE;
}
#پایان_اگر // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_writer_جمع_کن_from_zip_reader(mz_zip_archive *pZip, mz_zip_archive *p_منبع_zip, mz_uint file_شاخص)
{
  mz_uint n, بیت_flags, رقم_alignment_padding_بایتها;
  mz_uint64 comp_بایتها_مانده, local_dir_سرآیند_ofs;
  mz_uint64 cur_src_file_ofs, cur_dst_file_ofs;
  mz_uint32 local_سرآیند_u32[(MZ_ZIP_LOCAL_DIR_سرآیند_اندازه + حجم(mz_uint32) - 1) / حجم(mz_uint32)]; mz_uint8 *p_Local_سرآیند = (mz_uint8 *)local_سرآیند_u32;
  mz_uint8 central_سرآیند[MZ_ZIP_CENTRAL_DIR_سرآیند_اندازه];
  size_t orig_central_dir_اندازه;
  mz_zip_داخلی_state *pState;
  فراغ *pBuf; ثابت mz_uint8 *p_Src_central_سرآیند;

  إذا ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_نما != MZ_ZIP_نما_WRITING))
    أرجع MZ_FALSE;
  إذا (عدم == (p_Src_central_سرآیند = mz_zip_reader_get_cdh(p_منبع_zip, file_شاخص)))
    أرجع MZ_FALSE;
  pState = pZip->m_pState;

  رقم_alignment_padding_بایتها = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  إذا ((pZip->m_مجموع_files == 0xFFFF) || ((pZip->m_archive_اندازه + رقم_alignment_padding_بایتها + MZ_ZIP_LOCAL_DIR_سرآیند_اندازه + MZ_ZIP_CENTRAL_DIR_سرآیند_اندازه) > 0xFFFFFFFF))
    أرجع MZ_FALSE;

  cur_src_file_ofs = MZ_READ_LE32(p_Src_central_سرآیند + MZ_ZIP_CDH_LOCAL_سرآیند_OFS);
  cur_dst_file_ofs = pZip->m_archive_اندازه;

  إذا (p_منبع_zip->m_pRead(p_منبع_zip->m_pIO_opaque, cur_src_file_ofs, p_Local_سرآیند, MZ_ZIP_LOCAL_DIR_سرآیند_اندازه) != MZ_ZIP_LOCAL_DIR_سرآیند_اندازه)
    أرجع MZ_FALSE;
  إذا (MZ_READ_LE32(p_Local_سرآیند) != MZ_ZIP_LOCAL_DIR_سرآیند_SIG)
    أرجع MZ_FALSE;
  cur_src_file_ofs += MZ_ZIP_LOCAL_DIR_سرآیند_اندازه;

  إذا (!mz_zip_writer_write_zeros(pZip, cur_dst_file_ofs, رقم_alignment_padding_بایتها))
    أرجع MZ_FALSE;
  cur_dst_file_ofs += رقم_alignment_padding_بایتها;
  local_dir_سرآیند_ofs = cur_dst_file_ofs;
  إذا (pZip->m_file_جابه_جایی_alignment) { MZ_ASSERT((local_dir_سرآیند_ofs & (pZip->m_file_جابه_جایی_alignment - 1)) == 0); }

  إذا (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, p_Local_سرآیند, MZ_ZIP_LOCAL_DIR_سرآیند_اندازه) != MZ_ZIP_LOCAL_DIR_سرآیند_اندازه)
    أرجع MZ_FALSE;
  cur_dst_file_ofs += MZ_ZIP_LOCAL_DIR_سرآیند_اندازه;

  n = MZ_READ_LE16(p_Local_سرآیند + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p_Local_سرآیند + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  comp_بایتها_مانده = n + MZ_READ_LE32(p_Src_central_سرآیند + MZ_ZIP_CDH_COMPRESSED_اندازه_OFS);

  إذا (عدم == (pBuf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)MZ_MAX(حجم(mz_uint32) * 4, MZ_MIN(MZ_ZIP_MAX_IO_BUF_اندازه, comp_بایتها_مانده)))))
    أرجع MZ_FALSE;

  طالما (comp_بایتها_مانده)
  {
    n = (mz_uint)MZ_MIN(MZ_ZIP_MAX_IO_BUF_اندازه, comp_بایتها_مانده);
    إذا (p_منبع_zip->m_pRead(p_منبع_zip->m_pIO_opaque, cur_src_file_ofs, pBuf, n) != n)
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

    comp_بایتها_مانده -= n;
  }

  بیت_flags = MZ_READ_LE16(p_Local_سرآیند + MZ_ZIP_LDH_بیت_FLAG_OFS);
  إذا (بیت_flags & 8)
  {
    // Copy data descriptor
    إذا (p_منبع_zip->m_pRead(p_منبع_zip->m_pIO_opaque, cur_src_file_ofs, pBuf, حجم(mz_uint32) * 4) != حجم(mz_uint32) * 4)
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

  orig_central_dir_اندازه = pState->m_central_dir.m_اندازه;

  کپی_حافظه(central_سرآیند, p_Src_central_سرآیند, MZ_ZIP_CENTRAL_DIR_سرآیند_اندازه);
  MZ_WRITE_LE32(central_سرآیند + MZ_ZIP_CDH_LOCAL_سرآیند_OFS, local_dir_سرآیند_ofs);
  إذا (!mz_zip_array_افزودن_پشت(pZip, &pState->m_central_dir, central_سرآیند, MZ_ZIP_CENTRAL_DIR_سرآیند_اندازه))
    أرجع MZ_FALSE;

  n = MZ_READ_LE16(p_Src_central_سرآیند + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p_Src_central_سرآیند + MZ_ZIP_CDH_EXTRA_LEN_OFS) + MZ_READ_LE16(p_Src_central_سرآیند + MZ_ZIP_CDH_COMMENT_LEN_OFS);
  إذا (!mz_zip_array_افزودن_پشت(pZip, &pState->m_central_dir, p_Src_central_سرآیند + MZ_ZIP_CENTRAL_DIR_سرآیند_اندازه, n))
  {
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_اندازه, MZ_FALSE);
    أرجع MZ_FALSE;
  }

  إذا (pState->m_central_dir.m_اندازه > 0xFFFFFFFF)
    أرجع MZ_FALSE;
  n = (mz_uint32)orig_central_dir_اندازه;
  إذا (!mz_zip_array_افزودن_پشت(pZip, &pState->m_central_dir_offsets, &n, 1))
  {
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_اندازه, MZ_FALSE);
    أرجع MZ_FALSE;
  }

  pZip->m_مجموع_files++;
  pZip->m_archive_اندازه = cur_dst_file_ofs;

  أرجع MZ_TRUE;
}

mz_bool mz_zip_writer_finalize_archive(mz_zip_archive *pZip)
{
  mz_zip_داخلی_state *pState;
  mz_uint64 central_dir_ofs, central_dir_اندازه;
  mz_uint8 hdr[MZ_ZIP_انتها_از_CENTRAL_DIR_سرآیند_اندازه];

  إذا ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_نما != MZ_ZIP_نما_WRITING))
    أرجع MZ_FALSE;

  pState = pZip->m_pState;

  // no zip64 support yet
  إذا ((pZip->m_مجموع_files > 0xFFFF) || ((pZip->m_archive_اندازه + pState->m_central_dir.m_اندازه + MZ_ZIP_انتها_از_CENTRAL_DIR_سرآیند_اندازه) > 0xFFFFFFFF))
    أرجع MZ_FALSE;

  central_dir_ofs = 0;
  central_dir_اندازه = 0;
  إذا (pZip->m_مجموع_files)
  {
    // Write central directory
    central_dir_ofs = pZip->m_archive_اندازه;
    central_dir_اندازه = pState->m_central_dir.m_اندازه;
    pZip->m_central_directory_file_ofs = central_dir_ofs;
    إذا (pZip->m_pWrite(pZip->m_pIO_opaque, central_dir_ofs, pState->m_central_dir.m_p, (size_t)central_dir_اندازه) != central_dir_اندازه)
      أرجع MZ_FALSE;
    pZip->m_archive_اندازه += central_dir_اندازه;
  }

  // Write end of central directory record
  MZ_CLEAR_ARR(hdr);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_SIG_OFS, MZ_ZIP_انتها_از_CENTRAL_DIR_سرآیند_SIG);
  MZ_WRITE_LE16(hdr + MZ_ZIP_ECDH_CDIR_رقم_ENTRIES_ON_DISK_OFS, pZip->m_مجموع_files);
  MZ_WRITE_LE16(hdr + MZ_ZIP_ECDH_CDIR_مجموع_ENTRIES_OFS, pZip->m_مجموع_files);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_CDIR_اندازه_OFS, central_dir_اندازه);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_CDIR_OFS_OFS, central_dir_ofs);

  إذا (pZip->m_pWrite(pZip->m_pIO_opaque, pZip->m_archive_اندازه, hdr, حجم(hdr)) != حجم(hdr))
    أرجع MZ_FALSE;
#اگر_تعریف_نشده MINIZ_NO_STDIO
  إذا ((pState->m_pFile) && (MZ_FFLUSH(pState->m_pFile) == EOF))
    أرجع MZ_FALSE;
#پایان_اگر // #ifndef MINIZ_NO_STDIO

  pZip->m_archive_اندازه += حجم(hdr);

  pZip->m_zip_نما = MZ_ZIP_نما_WRITING_HAS_BEEN_FINALIZED;
  أرجع MZ_TRUE;
}

mz_bool mz_zip_writer_finalize_انباشته_archive(mz_zip_archive *pZip, فراغ **pBuf, size_t *p_اندازه)
{
  إذا ((!pZip) || (!pZip->m_pState) || (!pBuf) || (!p_اندازه))
    أرجع MZ_FALSE;
  إذا (pZip->m_pWrite != mz_zip_انباشته_write_func)
    أرجع MZ_FALSE;
  إذا (!mz_zip_writer_finalize_archive(pZip))
    أرجع MZ_FALSE;

  *pBuf = pZip->m_pState->m_pMem;
  *p_اندازه = pZip->m_pState->m_mem_اندازه;
  pZip->m_pState->m_pMem = عدم;
  pZip->m_pState->m_mem_اندازه = pZip->m_pState->m_mem_ظرفیت = 0;
  أرجع MZ_TRUE;
}

mz_bool mz_zip_writer_انتها(mz_zip_archive *pZip)
{
  mz_zip_داخلی_state *pState;
  mz_bool وضعیت = MZ_TRUE;
  إذا ((!pZip) || (!pZip->m_pState) || (!pZip->m_pAlloc) || (!pZip->m_pFree) || ((pZip->m_zip_نما != MZ_ZIP_نما_WRITING) && (pZip->m_zip_نما != MZ_ZIP_نما_WRITING_HAS_BEEN_FINALIZED)))
    أرجع MZ_FALSE;

  pState = pZip->m_pState;
  pZip->m_pState = عدم;
  mz_zip_array_clear(pZip, &pState->m_central_dir);
  mz_zip_array_clear(pZip, &pState->m_central_dir_offsets);
  mz_zip_array_clear(pZip, &pState->m_sorted_central_dir_offsets);

#اگر_تعریف_نشده MINIZ_NO_STDIO
  إذا (pState->m_pFile)
  {
    MZ_FCLOSE(pState->m_pFile);
    pState->m_pFile = عدم;
  }
#پایان_اگر // #ifndef MINIZ_NO_STDIO

  إذا ((pZip->m_pWrite == mz_zip_انباشته_write_func) && (pState->m_pMem))
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pState->m_pMem);
    pState->m_pMem = عدم;
  }

  pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
  pZip->m_zip_نما = MZ_ZIP_نما_INVALID;
  أرجع وضعیت;
}

#اگر_تعریف_نشده MINIZ_NO_STDIO
mz_bool mz_zip_جمع_کن_mem_مقصد_archive_file_درون_قراربده(ثابت حرف *pZip_filename, ثابت حرف *pArchive_name, ثابت فراغ *pBuf, size_t buf_اندازه_2, ثابت فراغ *pComment, mz_uint16 comment_اندازه, mz_uint level_and_flags)
{
  mz_bool وضعیت, created_new_archive = MZ_FALSE;
  mz_zip_archive zip_archive;
  بنية MZ_FILE_STAT_STRUCT file_stat;
  MZ_CLEAR_OBJ(zip_archive);
  إذا ((صحيح)level_and_flags < 0)
     level_and_flags = MZ_DEFAULT_LEVEL;
  إذا ((!pZip_filename) || (!pArchive_name) || ((buf_اندازه_2) && (!pBuf)) || ((comment_اندازه) && (!pComment)) || ((level_and_flags & 0xF) > MZ_UBER_COMPRESSION))
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
    إذا (!mz_zip_reader_init_file(&zip_archive, pZip_filename, level_and_flags | MZ_ZIP_FLAG_DO_NOT_مرتب_سازی_CENTRAL_DIRECTORY))
      أرجع MZ_FALSE;
    إذا (!mz_zip_writer_init_from_reader(&zip_archive, pZip_filename))
    {
      mz_zip_reader_انتها(&zip_archive);
      أرجع MZ_FALSE;
    }
  }
  وضعیت = mz_zip_writer_جمع_کن_mem_ex(&zip_archive, pArchive_name, pBuf, buf_اندازه_2, pComment, comment_اندازه, level_and_flags, 0, 0);
  // Always finalize, even if adding failed for some reason, so we have a valid central directory. (This may not always succeed, but we can try.)
  إذا (!mz_zip_writer_finalize_archive(&zip_archive))
    وضعیت = MZ_FALSE;
  إذا (!mz_zip_writer_انتها(&zip_archive))
    وضعیت = MZ_FALSE;
  إذا ((!وضعیت) && (created_new_archive))
  {
    // It's a new archive and something went wrong, so just delete it.
    صحيح ignored_وضعیت = MZ_DELETE_FILE(pZip_filename);
    (فراغ)ignored_وضعیت;
  }
  أرجع وضعیت;
}

فراغ *mz_zip_استخراج_archive_file_مقصد_انباشته(ثابت حرف *pZip_filename, ثابت حرف *pArchive_name, size_t *p_اندازه, mz_uint flags)
{
  صحيح file_شاخص;
  mz_zip_archive zip_archive;
  فراغ *p = عدم;

  إذا (p_اندازه)
    *p_اندازه = 0;

  إذا ((!pZip_filename) || (!pArchive_name))
    أرجع عدم;

  MZ_CLEAR_OBJ(zip_archive);
  إذا (!mz_zip_reader_init_file(&zip_archive, pZip_filename, flags | MZ_ZIP_FLAG_DO_NOT_مرتب_سازی_CENTRAL_DIRECTORY))
    أرجع عدم;

  إذا ((file_شاخص = mz_zip_reader_locate_file(&zip_archive, pArchive_name, عدم, flags)) >= 0)
    p = mz_zip_reader_استخراج_مقصد_انباشته(&zip_archive, file_شاخص, p_اندازه, flags);

  mz_zip_reader_انتها(&zip_archive);
  أرجع p;
}

#پایان_اگر // #ifndef MINIZ_NO_STDIO

#پایان_اگر // #ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

#پایان_اگر // #ifndef MINIZ_NO_ARCHIVE_APIS

#اگر_تعریف_شده __cplusplus
}
#پایان_اگر

#اگر_تعریف_شده _MSC_VER
#رهنمود warning (برداشت)
#پایان_اگر

#پایان_اگر // MINIZ_HEADER_FILE_ONLY

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

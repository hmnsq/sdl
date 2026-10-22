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

#که_نه_تعریف_شوی MINIZ_سرلیک_INCLUDED
#تعریف_کړه MINIZ_سرلیک_INCLUDED

/*#include <stdlib.h>*/

// Defines to completely disable specific portions of miniz.c:
// If all macros here are defined the only functionality remaining will be CRC-32, adler-32, tinfl, and tdefl.

// Define MINIZ_NO_STDIO to disable all usage and any functions which rely on stdio for file I/O.
#تعریف_کړه MINIZ_NO_STDIO

// If MINIZ_NO_TIME is specified then the ZIP archive functions will not be able to get the current time, or
// get/set file times, and the C run-time funcs that get/set times won't be called.
// The current downside is the times written to your archives will be from 1979.
#تعریف_کړه MINIZ_NO_وخت

// Define MINIZ_NO_DEFLATE_APIS to disable all compression API's.
//#define MINIZ_NO_DEFLATE_APIS

// Define MINIZ_NO_INFLATE_APIS to disable all decompression API's.
#تعریف_کړه MINIZ_NO_INFLATE_APIS

// Define MINIZ_NO_ARCHIVE_APIS to disable all ZIP archive API's.
#تعریف_کړه MINIZ_NO_ARCHIVE_APIS

// Define MINIZ_NO_ARCHIVE_APIS to disable all writing related ZIP archive API's.
#تعریف_کړه MINIZ_NO_ARCHIVE_WRITING_APIS

// Define MINIZ_NO_ZLIB_APIS to remove all ZLIB-style compression/decompression API's.
#تعریف_کړه MINIZ_NO_ZLIB_APIS

// Define MINIZ_NO_ZLIB_COMPATIBLE_NAME to disable zlib names, to prevent conflicts against stock zlib.
#تعریف_کړه MINIZ_NO_ZLIB_COMPATIBLE_نومونه

// Define MINIZ_NO_MALLOC to disable all calls to malloc, free, and realloc.
// Note if MINIZ_NO_MALLOC is defined then the user must always provide custom user alloc/free/realloc
// callbacks to the zlib and archive API's, and a few stand-alone helper API's which don't provide custom user
// functions (such as tdefl_compress_mem_to_heap() and tinfl_decompress_mem_to_heap()) won't work.
//#define MINIZ_NO_MALLOC
#تعریف_کړه MINIZ_SDL_MALLOC

#که_تعریف_شوی MINIZ_NO_INFLATE_APIS
#تعریف_کړه MINIZ_NO_ARCHIVE_APIS
#د_که_پای

#که_تعریف_شوی MINIZ_NO_DEFLATE_APIS
#تعریف_کړه MINIZ_NO_ARCHIVE_WRITING_APIS
#د_که_پای

// Define MINIZ_STATIC_FUNCTIONS to make all functions static. You probably
// want this if you're using miniz in a library
#تعریف_کړه MINIZ_STATIC_FUNCTIONS

#إذا defined(__TINYC__) && (defined(__linux) || defined(__linux__))
  // TODO: Work around "error: include file 'sys\utime.h' when compiling with tcc on Linux
  #تعریف_کړه MINIZ_NO_وخت
#د_که_پای

#إذا !defined(MINIZ_NO_وخت) && !defined(MINIZ_NO_ARCHIVE_APIS)
  #ضمن <time.h>
#د_که_پای

#إذا defined(_M_IX86) || defined(_M_X64) || defined(__i386__) || defined(__i386) || defined(__i486__) || defined(__i486) || defined(i386) || defined(__ia64__) || defined(__x86_64__)
// MINIZ_X86_OR_X64_CPU is only used to help set the below macros.
#تعریف_کړه MINIZ_X86_OR_X64_CPU 1
#د_که_پای

#که_نه_تعریف_شوی MINIZ_LITTLE_ENDIAN /* if not defined by SDL */
#إذا (__BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__) || MINIZ_X86_OR_X64_CPU
// Set MINIZ_LITTLE_ENDIAN to 1 if the processor is little endian.
#تعریف_کړه MINIZ_LITTLE_ENDIAN 1
#د_که_پای
#د_که_پای // MINIZ_LITTLE_ENDIAN /* if not defined by SDL */

#که_نه_تعریف_شوی MINIZ_USE_UNALIGNED_LOADS_AND_STORES
#إذا MINIZ_X86_OR_X64_CPU
// Set MINIZ_USE_UNALIGNED_LOADS_AND_STORES to 1 on CPU's that permit efficient integer loads and stores from unaligned addresses.
#تعریف_کړه MINIZ_USE_UNALIGNED_LOADS_AND_STORES 1
#د_که_پای
#د_که_پای // MINIZ_USE_UNALIGNED_LOADS_AND_STORES

#إذا defined(_M_X64) || defined(_WIN64) || defined(__MINGW64__) || defined(_LP64) || defined(__LP64__) || defined(__ia64__) || defined(__x86_64__)
// Set MINIZ_HAS_64BIT_REGISTERS to 1 if operations on 64-bit integers are reasonably fast (and don't involve compiler generated calls to helper functions).
#تعریف_کړه MINIZ_HAS_64_بټ_REGISTERS 1
#د_که_پای

#که_تعریف_شوی MINIZ_STATIC_FUNCTIONS
#تعریف_کړه MINIZ_STATIC ساكن
#وإلا
#تعریف_کړه MINIZ_STATIC
#د_که_پای

#که_تعریف_شوی __cplusplus
خارجي "C" {
#د_که_پای

// ------------------- zlib-style API Definitions.

// For more compatibility with zlib, miniz.c uses unsigned long for some parameters/struct members. Beware: mz_ulong can be either 32 or 64-bits!
تعريفنوع بینښه اوږد mz_ulong;

// mz_free() internally uses the MZ_FREE() macro (which by default calls free() unless you've modified the MZ_MALLOC macro) to release a block allocated from the heap.
MINIZ_STATIC فراغ mz_free(فراغ *p);

#تعریف_کړه MZ_ADLER32_INIT (1)
// mz_adler32() returns the initial adler-32 value to use when called with ptr==NULL.
MINIZ_STATIC mz_ulong mz_adler32(mz_ulong adler, ثابت بینښه حرف *ptr, size_t buf_len);

#تعریف_کړه MZ_دوراني_ازموینه_32_INIT (0)
// mz_crc32() returns the initial CRC-32 value to use when called with ptr==NULL.
MINIZ_STATIC mz_ulong mz_دوراني_ازموینه_32(mz_ulong دوراني_ازموینه, ثابت بینښه حرف *ptr, size_t buf_len);

// Compression strategies.
تعداد { MZ_DEFAULT_STRATEGY = 0, MZ_FILTERED = 1, MZ_HUFFMAN_ONLY = 2, MZ_RLE = 3, MZ_FIXED = 4 };

//لاره
#تعریف_کړه MZ_DEFLATED 8

#که_نه_تعریف_شوی MINIZ_NO_ZLIB_APIS

// Heap allocation callbacks.
// Note that mz_alloc_func parameter types purpsosely differ from zlib's: items/size is size_t, not unsigned long.
تعريفنوع فراغ *(*mz_alloc_func)(فراغ *opaque, size_t توکي, size_t اندازه);
تعريفنوع فراغ (*mz_free_func)(فراغ *opaque, فراغ *پته);
تعريفنوع فراغ *(*mz_realloc_func)(فراغ *opaque, فراغ *پته, size_t توکي, size_t اندازه);

#تعریف_کړه MZ_نسخه          "9.1.15"
#تعریف_کړه MZ_VERNUM           0x91F0
#تعریف_کړه MZ_VER_MAJOR        9
#تعریف_کړه MZ_VER_MINOR        1
#تعریف_کړه MZ_VER_REVISION     15
#تعریف_کړه MZ_VER_SUBREVISION  0

// Flush values. For typical usage you only need MZ_NO_FLUSH and MZ_FINISH. The other values are for advanced use (refer to the zlib docs).
تعداد { MZ_NO_FLUSH = 0, MZ_PARTIAL_FLUSH = 1, MZ_SYNC_FLUSH = 2, MZ_ډک_FLUSH = 3, MZ_پای = 4, MZ_بلاک = 5 };

// Return status codes. MZ_PARAM_ERROR is non-standard.
تعداد { MZ_OK = 0, MZ_بهیر_پای_ټکی = 1, MZ_NEED_DICT = 2, MZ_ERRNO = -1, MZ_بهیر_ERROR = -2, MZ_معلومات_ERROR = -3, MZ_MEM_ERROR = -4, MZ_BUF_ERROR = -5, MZ_نسخه_ERROR = -6, MZ_PARAM_ERROR = -10000 };

// Compression levels: 0-9 are the standard zlib-style levels, 10 is best possible compression (not zlib compatible, and may be very slow), MZ_DEFAULT_COMPRESSION=MZ_DEFAULT_LEVEL.
تعداد { MZ_NO_COMPRESSION = 0, MZ_غوره_چټکتیا = 1, MZ_غوره_COMPRESSION = 9, MZ_UBER_COMPRESSION = 10, MZ_DEFAULT_LEVEL = 6, MZ_DEFAULT_COMPRESSION = -1 };

// Window bits
#تعریف_کړه MZ_DEFAULT_کړکۍ_بټونه 15

بنية mz_دننی_state;

// Compression/decompression stream struct.
تعريفنوع بنية mz_بهیر_s
{
  ثابت بینښه حرف *بل_دننه;     // pointer to next byte to read
  بینښه صحيح avail_دننه;            // number of bytes available at next_in
  mz_ulong ټول_دننه;                // total number of bytes consumed so far

  بینښه حرف *بل_بهر;          // pointer to next byte to write
  بینښه صحيح avail_بهر;           // number of bytes that can be written to next_out
  mz_ulong ټول_بهر;               // total number of bytes produced so far

  حرف *پیغام_2;                        // error msg (unused)
  بنية mz_دننی_state *state;  // internal state, allocated by zalloc/zfree

  mz_alloc_func zalloc;             // optional heap allocation function (defaults to malloc)
  mz_free_func zfree;               // optional heap free function (defaults to free)
  فراغ *opaque;                     // heap alloc function user pointer

  صحيح معلومات_type;                    // data_type (unused)
  mz_ulong adler;                   // adler32 of the source or uncompressed data
  mz_ulong reserved;                // not used
} mz_بهیر;

تعريفنوع mz_بهیر *mz_streamp;

// Returns the version string of miniz.c.
MINIZ_STATIC ثابت حرف *mz_نسخه(فراغ);

#که_نه_تعریف_شوی MINIZ_NO_DEFLATE_APIS

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
MINIZ_STATIC صحيح mz_deflateInit(mz_streamp p_بهیر, صحيح level);

// mz_deflateInit2() is like mz_deflate(), except with more control:
// Additional parameters:
//   method must be MZ_DEFLATED
//   window_bits must be MZ_DEFAULT_WINDOW_BITS (to wrap the deflate stream with zlib header/adler-32 footer) or -MZ_DEFAULT_WINDOW_BITS (raw deflate/no header or footer)
//   mem_level must be between [1, 9] (it's checked but ignored by miniz.c)
MINIZ_STATIC صحيح mz_deflateInit2(mz_streamp p_بهیر, صحيح level, صحيح لاره, صحيح کړکۍ_بټونه, صحيح mem_level, صحيح strategy);

// Quickly resets a compressor without having to reallocate anything. Same as calling mz_deflateEnd() followed by mz_deflateInit()/mz_deflateInit2().
MINIZ_STATIC صحيح mz_deflateReset(mz_streamp p_بهیر);

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
MINIZ_STATIC صحيح mz_deflate(mz_streamp p_بهیر, صحيح flush);

// mz_deflateEnd() deinitializes a compressor:
// Return values:
//  MZ_OK on success.
//  MZ_STREAM_ERROR if the stream is bogus.
MINIZ_STATIC صحيح mz_deflate_پای_ټکی(mz_streamp p_بهیر);

// mz_deflateBound() returns a (very) conservative upper bound on the amount of data that could be generated by deflate(), assuming flush is set to only MZ_NO_FLUSH or MZ_FINISH.
MINIZ_STATIC mz_ulong mz_deflateBound(mz_streamp p_بهیر, mz_ulong سرچینه_len);

// Single-call compression functions mz_compress() and mz_compress2():
// Returns MZ_OK on success, or one of the error codes from mz_deflate() on failure.
MINIZ_STATIC صحيح mz_compress(بینښه حرف *pDest, mz_ulong *pDest_len, ثابت بینښه حرف *p_سرچینه, mz_ulong سرچینه_len);
MINIZ_STATIC صحيح mz_compress2(بینښه حرف *pDest, mz_ulong *pDest_len, ثابت بینښه حرف *p_سرچینه, mz_ulong سرچینه_len, صحيح level);

// mz_compressBound() returns a (very) conservative upper bound on the amount of data that could be generated by calling mz_compress().
MINIZ_STATIC mz_ulong mz_compressBound(mz_ulong سرچینه_len);

#د_که_پای /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#که_نه_تعریف_شوی MINIZ_NO_INFLATE_APIS

// Initializes a decompressor.
MINIZ_STATIC صحيح mz_inflateInit(mz_streamp p_بهیر);

// mz_inflateInit2() is like mz_inflateInit() with an additional option that controls the window size and whether or not the stream has been wrapped with a zlib header/footer:
// window_bits must be MZ_DEFAULT_WINDOW_BITS (to parse zlib header/footer) or -MZ_DEFAULT_WINDOW_BITS (raw deflate).
MINIZ_STATIC صحيح mz_inflateInit2(mz_streamp p_بهیر, صحيح کړکۍ_بټونه);

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
MINIZ_STATIC صحيح mz_inflate(mz_streamp p_بهیر, صحيح flush);

// Deinitializes a decompressor.
MINIZ_STATIC صحيح mz_inflate_پای_ټکی(mz_streamp p_بهیر);

// Single-call decompression.
// Returns MZ_OK on success, or one of the error codes from mz_inflate() on failure.
MINIZ_STATIC صحيح mz_uncompress(بینښه حرف *pDest, mz_ulong *pDest_len, ثابت بینښه حرف *p_سرچینه, mz_ulong سرچینه_len);
#د_که_پای /*#ifndef MINIZ_NO_INFLATE_APIS*/

// Returns a string description of the specified error code, or NULL if the error code is invalid.
MINIZ_STATIC ثابت حرف *mz_error(صحيح err);

// Redefine zlib-compatible names to miniz equivalents, so miniz.c can be used as a drop-in replacement for the subset of zlib that miniz.c supports.
// Define MINIZ_NO_ZLIB_COMPATIBLE_NAMES to disable zlib-compatibility if you use zlib in the same project.
#که_نه_تعریف_شوی MINIZ_NO_ZLIB_COMPATIBLE_نومونه
  تعريفنوع بینښه حرف Byte;
  تعريفنوع بینښه صحيح uInt;
  تعريفنوع mz_ulong uLong;
  تعريفنوع Byte Bytef;
  تعريفنوع uInt uIntf;
  تعريفنوع حرف charf;
  تعريفنوع صحيح intf;
  تعريفنوع فراغ *voidpf;
  تعريفنوع uLong uLongf;
  تعريفنوع فراغ *voidp;
  تعريفنوع فراغ *ثابت voidpc;
  #تعریف_کړه Z_NULL                0
  #تعریف_کړه Z_NO_FLUSH            MZ_NO_FLUSH
  #تعریف_کړه Z_PARTIAL_FLUSH       MZ_PARTIAL_FLUSH
  #تعریف_کړه Z_SYNC_FLUSH          MZ_SYNC_FLUSH
  #تعریف_کړه Z_ډک_FLUSH          MZ_ډک_FLUSH
  #تعریف_کړه Z_پای              MZ_پای
  #تعریف_کړه Z_بلاک               MZ_بلاک
  #تعریف_کړه Z_OK                  MZ_OK
  #تعریف_کړه Z_بهیر_پای_ټکی          MZ_بهیر_پای_ټکی
  #تعریف_کړه Z_NEED_DICT           MZ_NEED_DICT
  #تعریف_کړه Z_ERRNO               MZ_ERRNO
  #تعریف_کړه Z_بهیر_ERROR        MZ_بهیر_ERROR
  #تعریف_کړه Z_معلومات_ERROR          MZ_معلومات_ERROR
  #تعریف_کړه Z_MEM_ERROR           MZ_MEM_ERROR
  #تعریف_کړه Z_BUF_ERROR           MZ_BUF_ERROR
  #تعریف_کړه Z_نسخه_ERROR       MZ_نسخه_ERROR
  #تعریف_کړه Z_PARAM_ERROR         MZ_PARAM_ERROR
  #تعریف_کړه Z_NO_COMPRESSION      MZ_NO_COMPRESSION
  #تعریف_کړه Z_غوره_چټکتیا          MZ_غوره_چټکتیا
  #تعریف_کړه Z_غوره_COMPRESSION    MZ_غوره_COMPRESSION
  #تعریف_کړه Z_DEFAULT_COMPRESSION MZ_DEFAULT_COMPRESSION
  #تعریف_کړه Z_DEFAULT_STRATEGY    MZ_DEFAULT_STRATEGY
  #تعریف_کړه Z_FILTERED            MZ_FILTERED
  #تعریف_کړه Z_HUFFMAN_ONLY        MZ_HUFFMAN_ONLY
  #تعریف_کړه Z_RLE                 MZ_RLE
  #تعریف_کړه Z_FIXED               MZ_FIXED
  #تعریف_کړه Z_DEFLATED            MZ_DEFLATED
  #تعریف_کړه Z_DEFAULT_کړکۍ_بټونه MZ_DEFAULT_کړکۍ_بټونه
  #تعریف_کړه alloc_func            mz_alloc_func
  #تعریف_کړه free_func             mz_free_func
  #تعریف_کړه دننی_state        mz_دننی_state
  #تعریف_کړه z_بهیر              mz_بهیر
#که_نه_تعریف_شوی MINIZ_NO_DEFLATE_APIS
  #تعریف_کړه deflateInit           mz_deflateInit
  #تعریف_کړه deflateInit2          mz_deflateInit2
  #تعریف_کړه deflateReset          mz_deflateReset
  #تعریف_کړه deflate               mz_deflate
  #تعریف_کړه deflate_پای_ټکی            mz_deflate_پای_ټکی
  #تعریف_کړه deflateBound          mz_deflateBound
  #تعریف_کړه compress              mz_compress
  #تعریف_کړه compress2             mz_compress2
  #تعریف_کړه compressBound         mz_compressBound
#د_که_پای /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#که_نه_تعریف_شوی MINIZ_NO_INFLATE_APIS
  #تعریف_کړه inflateInit           mz_inflateInit
  #تعریف_کړه inflateInit2          mz_inflateInit2
  #تعریف_کړه inflate               mz_inflate
  #تعریف_کړه inflate_پای_ټکی            mz_inflate_پای_ټکی
  #تعریف_کړه uncompress            mz_uncompress
#د_که_پای /*#ifndef MINIZ_NO_INFLATE_APIS*/
  #تعریف_کړه دوراني_ازموینه_32                 mz_دوراني_ازموینه_32
  #تعریف_کړه adler32               mz_adler32
  #تعریف_کړه MAX_WBITS             15
  #تعریف_کړه MAX_MEM_LEVEL         9
  #تعریف_کړه zError                mz_error
  #تعریف_کړه ZLIB_نسخه          MZ_نسخه
  #تعریف_کړه ZLIB_VERNUM           MZ_VERNUM
  #تعریف_کړه ZLIB_VER_MAJOR        MZ_VER_MAJOR
  #تعریف_کړه ZLIB_VER_MINOR        MZ_VER_MINOR
  #تعریف_کړه ZLIB_VER_REVISION     MZ_VER_REVISION
  #تعریف_کړه ZLIB_VER_SUBREVISION  MZ_VER_SUBREVISION
  #تعریف_کړه zlib_نسخه           mz_نسخه
  #تعریف_کړه zlib_نسخه_2          mz_نسخه()
#د_که_پای // #ifndef MINIZ_NO_ZLIB_COMPATIBLE_NAMES

#د_که_پای // MINIZ_NO_ZLIB_APIS

// ------------------- Types and macros

تعريفنوع بینښه حرف mz_uint8;
تعريفنوع نښهدار لنډ mz_int16;
تعريفنوع بینښه لنډ mz_uint16;
تعريفنوع بینښه صحيح mz_uint32;
تعريفنوع بینښه صحيح mz_uint;
تعريفنوع اوږد اوږد mz_int64;
تعريفنوع بینښه اوږد اوږد mz_uint64;
تعريفنوع صحيح mz_bool;

#تعریف_کړه MZ_FALSE (0)
#تعریف_کړه MZ_TRUE (1)

// An attempt to work around MSVC's spammy "warning C4127: conditional expression is constant" message.
#که_تعریف_شوی _MSC_VER
   #تعریف_کړه MZ_MACRO_پای_ټکی طالما (0, 0)
#وإلا
   #تعریف_کړه MZ_MACRO_پای_ټکی طالما (0)
#د_که_پای

// ------------------- ZIP archive reading/writing

#که_نه_تعریف_شوی MINIZ_NO_ARCHIVE_APIS

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
  mz_uint16 m_بټ_flag;
  mz_uint16 m_لاره;
#که_نه_تعریف_شوی MINIZ_NO_وخت
  وخت_t m_وخت;
#د_که_پای
  mz_uint32 m_دوراني_ازموینه_32;
  mz_uint64 m_comp_اندازه;
  mz_uint64 m_uncomp_اندازه;
  mz_uint16 m_دننی_attr;
  mz_uint32 m_external_attr;
  mz_uint64 m_local_سرلیک_ofs;
  mz_uint32 m_comment_اندازه;
  حرف m_filename[MZ_ZIP_MAX_ARCHIVE_FILENAME_اندازه];
  حرف m_comment[MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_اندازه];
} mz_zip_archive_file_stat;

تعريفنوع size_t (*mz_file_read_func)(فراغ *pOpaque, mz_uint64 file_ofs, فراغ *pBuf, size_t n);
تعريفنوع size_t (*mz_file_write_func)(فراغ *pOpaque, mz_uint64 file_ofs, ثابت فراغ *pBuf, size_t n);

بنية mz_zip_دننی_state_نښان;
تعريفنوع بنية mz_zip_دننی_state_نښان mz_zip_دننی_state;

تعريفنوع تعداد
{
  MZ_ZIP_ډېرپېښ_INVALID = 0,
  MZ_ZIP_ډېرپېښ_READING = 1,
  MZ_ZIP_ډېرپېښ_WRITING = 2,
  MZ_ZIP_ډېرپېښ_WRITING_HAS_BEEN_FINALIZED = 3
} mz_zip_ډېرپېښ;

تعريفنوع بنية mz_zip_archive_نښان
{
  mz_uint64 m_archive_اندازه;
  mz_uint64 m_central_directory_file_ofs;
  mz_uint m_ټول_files;
  mz_zip_ډېرپېښ m_zip_ډېرپېښ;

  mz_uint m_file_دننه_واټن_alignment;

  mz_alloc_func m_pAlloc;
  mz_free_func m_pFree;
  mz_realloc_func m_pRealloc;
  فراغ *m_pAlloc_opaque;

  mz_file_read_func m_pRead;
  mz_file_write_func m_pWrite;
  فراغ *m_pIO_opaque;

  mz_zip_دننی_state *m_pState;

} mz_zip_archive;

تعريفنوع تعداد
{
  MZ_ZIP_FLAG_CASE_SENSITIVE                = 0x0100,
  MZ_ZIP_FLAG_IGNORE_لار                   = 0x0200,
  MZ_ZIP_FLAG_COMPRESSED_معلومات               = 0x0400,
  MZ_ZIP_FLAG_DO_NOT_ترتیبول_CENTRAL_DIRECTORY = 0x0800
} mz_zip_flags;

// ZIP archive reading

// Inits a ZIP archive reader.
// These functions read and validate the archive's central directory.
MINIZ_STATIC mz_bool mz_zip_reader_init(mz_zip_archive *pZip, mz_uint64 اندازه, mz_uint32 flags);
MINIZ_STATIC mz_bool mz_zip_reader_init_mem(mz_zip_archive *pZip, ثابت فراغ *pMem, size_t اندازه, mz_uint32 flags);

#که_نه_تعریف_شوی MINIZ_NO_STDIO
MINIZ_STATIC mz_bool mz_zip_reader_init_file(mz_zip_archive *pZip, ثابت حرف *pFilename, mz_uint32 flags);
#د_که_پای

// Returns the total number of files in the archive.
MINIZ_STATIC mz_uint mz_zip_reader_get_عدد_files(mz_zip_archive *pZip);

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
MINIZ_STATIC mz_bool mz_zip_reader_ایستل_منزل_mem_no_alloc(mz_zip_archive *pZip, mz_uint file_شاخص, فراغ *pBuf, size_t buf_اندازه_2, mz_uint flags, فراغ *pUser_read_buf, size_t user_read_buf_اندازه);
MINIZ_STATIC mz_bool mz_zip_reader_ایستل_file_منزل_mem_no_alloc(mz_zip_archive *pZip, ثابت حرف *pFilename, فراغ *pBuf, size_t buf_اندازه_2, mz_uint flags, فراغ *pUser_read_buf, size_t user_read_buf_اندازه);

// Extracts a archive file to a memory buffer.
MINIZ_STATIC mz_bool mz_zip_reader_ایستل_منزل_mem(mz_zip_archive *pZip, mz_uint file_شاخص, فراغ *pBuf, size_t buf_اندازه_2, mz_uint flags);
MINIZ_STATIC mz_bool mz_zip_reader_ایستل_file_منزل_mem(mz_zip_archive *pZip, ثابت حرف *pFilename, فراغ *pBuf, size_t buf_اندازه_2, mz_uint flags);

// Extracts a archive file to a dynamically allocated heap buffer.
MINIZ_STATIC فراغ *mz_zip_reader_ایستل_منزل_ډېرۍ(mz_zip_archive *pZip, mz_uint file_شاخص, size_t *p_اندازه, mz_uint flags);
MINIZ_STATIC فراغ *mz_zip_reader_ایستل_file_منزل_ډېرۍ(mz_zip_archive *pZip, ثابت حرف *pFilename, size_t *p_اندازه, mz_uint flags);

// Extracts a archive file using a callback function to output the file's data.
MINIZ_STATIC mz_bool mz_zip_reader_ایستل_منزل_callback(mz_zip_archive *pZip, mz_uint file_شاخص, mz_file_write_func pCallback, فراغ *pOpaque, mz_uint flags);
MINIZ_STATIC mz_bool mz_zip_reader_ایستل_file_منزل_callback(mz_zip_archive *pZip, ثابت حرف *pFilename, mz_file_write_func pCallback, فراغ *pOpaque, mz_uint flags);

#که_نه_تعریف_شوی MINIZ_NO_STDIO
// Extracts a archive file to a disk file and sets its last accessed and modified times.
// This function only extracts files, not archive directory records.
MINIZ_STATIC mz_bool mz_zip_reader_ایستل_منزل_file(mz_zip_archive *pZip, mz_uint file_شاخص, ثابت حرف *pDst_filename, mz_uint flags);
MINIZ_STATIC mz_bool mz_zip_reader_ایستل_file_منزل_file(mz_zip_archive *pZip, ثابت حرف *pArchive_filename, ثابت حرف *pDst_filename, mz_uint flags);
#د_که_پای

// Ends archive reading, freeing all allocations, and closing the input archive file if mz_zip_reader_init_file() was used.
MINIZ_STATIC mz_bool mz_zip_reader_پای_ټکی(mz_zip_archive *pZip);

// ZIP archive writing

#که_نه_تعریف_شوی MINIZ_NO_ARCHIVE_WRITING_APIS

// Inits a ZIP archive writer.
MINIZ_STATIC mz_bool mz_zip_writer_init(mz_zip_archive *pZip, mz_uint64 existing_اندازه);
MINIZ_STATIC mz_bool mz_zip_writer_init_ډېرۍ(mz_zip_archive *pZip, size_t اندازه_منزل_reserve_at_beginning, size_t initial_ویش_اندازه);

#که_نه_تعریف_شوی MINIZ_NO_STDIO
MINIZ_STATIC mz_bool mz_zip_writer_init_file(mz_zip_archive *pZip, ثابت حرف *pFilename, mz_uint64 اندازه_منزل_reserve_at_beginning);
#د_که_پای

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
MINIZ_STATIC mz_bool mz_zip_writer_جمع_کړه_mem(mz_zip_archive *pZip, ثابت حرف *pArchive_name, ثابت فراغ *pBuf, size_t buf_اندازه_2, mz_uint level_and_flags);
MINIZ_STATIC mz_bool mz_zip_writer_جمع_کړه_mem_ex(mz_zip_archive *pZip, ثابت حرف *pArchive_name, ثابت فراغ *pBuf, size_t buf_اندازه_2, ثابت فراغ *pComment, mz_uint16 comment_اندازه, mz_uint level_and_flags, mz_uint64 uncomp_اندازه, mz_uint32 uncomp_دوراني_ازموینه_32);

#که_نه_تعریف_شوی MINIZ_NO_STDIO
// Adds the contents of a disk file to an archive. This function also records the disk file's modified time into the archive.
// level_and_flags - compression level (0-10, see MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or just set to MZ_DEFAULT_COMPRESSION.
MINIZ_STATIC mz_bool mz_zip_writer_جمع_کړه_file(mz_zip_archive *pZip, ثابت حرف *pArchive_name, ثابت حرف *pSrc_filename, ثابت فراغ *pComment, mz_uint16 comment_اندازه, mz_uint level_and_flags);
#د_که_پای

// Adds a file to an archive by fully cloning the data from another archive.
// This function fully clones the source file's compressed data (no recompression), along with its full filename, extra data, and comment fields.
MINIZ_STATIC mz_bool mz_zip_writer_جمع_کړه_from_zip_reader(mz_zip_archive *pZip, mz_zip_archive *p_سرچینه_zip, mz_uint file_شاخص);

// Finalizes the archive by writing the central directory records followed by the end of central directory record.
// After an archive is finalized, the only valid call on the mz_zip_archive struct is mz_zip_writer_end().
// An archive must be manually finalized by calling this function for it to be valid.
MINIZ_STATIC mz_bool mz_zip_writer_finalize_archive(mz_zip_archive *pZip);
MINIZ_STATIC mz_bool mz_zip_writer_finalize_ډېرۍ_archive(mz_zip_archive *pZip, فراغ **pBuf, size_t *p_اندازه);

// Ends archive writing, freeing all allocations, and closing the output file if mz_zip_writer_init_file() was used.
// Note for the archive to be valid, it must have been finalized before ending.
MINIZ_STATIC mz_bool mz_zip_writer_پای_ټکی(mz_zip_archive *pZip);

// Misc. high-level helper functions:

// mz_zip_add_mem_to_archive_file_in_place() efficiently (but not atomically) appends a memory blob to a ZIP archive.
// level_and_flags - compression level (0-10, see MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or just set to MZ_DEFAULT_COMPRESSION.
MINIZ_STATIC mz_bool mz_zip_جمع_کړه_mem_منزل_archive_file_دننه_ځای_پرځای_کړه(ثابت حرف *pZip_filename, ثابت حرف *pArchive_name, ثابت فراغ *pBuf, size_t buf_اندازه_2, ثابت فراغ *pComment, mz_uint16 comment_اندازه, mz_uint level_and_flags);

// Reads a single file from an archive into a heap block.
// Returns NULL on failure.
MINIZ_STATIC فراغ *mz_zip_ایستل_archive_file_منزل_ډېرۍ(ثابت حرف *pZip_filename, ثابت حرف *pArchive_name, size_t *p_اندازه, mz_uint zip_flags);

#د_که_پای // #ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

#د_که_پای // #ifndef MINIZ_NO_ARCHIVE_APIS

// ------------------- Low-level Decompression API Definitions
#که_نه_تعریف_شوی MINIZ_NO_INFLATE_APIS

// Decompression flags used by tinfl_decompress().
// TINFL_FLAG_PARSE_ZLIB_HEADER: If set, the input has a valid zlib header and ends with an adler32 checksum (it's a valid zlib stream). Otherwise, the input is a raw deflate stream.
// TINFL_FLAG_HAS_MORE_INPUT: If set, there are more input bytes available beyond the end of the supplied input buffer. If clear, the input buffer contains all remaining input.
// TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF: If set, the output buffer is large enough to hold the entire decompressed stream. If clear, the output buffer is at least the size of the dictionary (typically 32KB).
// TINFL_FLAG_COMPUTE_ADLER32: Force adler-32 checksum computation of the decompressed bytes.
تعداد
{
  TINFL_FLAG_PARSE_ZLIB_سرلیک = 1,
  TINFL_FLAG_HAS_نور_ننوت = 2,
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
MINIZ_STATIC فراغ *tinfl_decompress_mem_منزل_ډېرۍ(ثابت فراغ *pSrc_buf, size_t src_buf_len, size_t *p_بهر_len, صحيح flags);

// tinfl_decompress_mem_to_mem() decompresses a block in memory to another block in memory.
// Returns TINFL_DECOMPRESS_MEM_TO_MEM_FAILED on failure, or the number of bytes written on success.
#تعریف_کړه TINFL_DECOMPRESS_MEM_منزل_MEM_FAILED ((size_t)(-1))
MINIZ_STATIC size_t tinfl_decompress_mem_منزل_mem(فراغ *p_بهر_buf, size_t بهر_buf_len, ثابت فراغ *pSrc_buf, size_t src_buf_len, صحيح flags);

// tinfl_decompress_mem_to_callback() decompresses a block in memory to an internal 32KB buffer, and a user provided callback function will be called to flush the buffer.
// Returns 1 on success or 0 on failure.
تعريفنوع صحيح (*tinfl_put_buf_func_ptr)(ثابت فراغ* pBuf, صحيح len, فراغ *pUser);
MINIZ_STATIC صحيح tinfl_decompress_mem_منزل_callback(ثابت فراغ *p_دننه_buf, size_t *p_دننه_buf_اندازه, tinfl_put_buf_func_ptr pPut_buf_func, فراغ *pPut_buf_user, صحيح flags);

بنية tinfl_decompressor_نښان; تعريفنوع بنية tinfl_decompressor_نښان tinfl_decompressor;

// Max size of LZ dictionary.
#تعریف_کړه TINFL_LZ_DICT_اندازه 32768

// Return status.
تعريفنوع تعداد
{
  TINFL_حالت_BAD_PARAM = -3,
  TINFL_حالت_ADLER32_MISMATCH = -2,
  TINFL_حالت_FAILED = -1,
  TINFL_حالت_بشپړ = 0,
  TINFL_حالت_NEEDS_نور_ننوت = 1,
  TINFL_حالت_HAS_نور_OUTPUT = 2
} tinfl_حالت;

// Initializes the decompressor to its initial state.
#تعریف_کړه tinfl_init(r) افعل { (r)->m_state = 0; } MZ_MACRO_پای_ټکی
#تعریف_کړه tinfl_get_adler32(r) (r)->m_check_adler32

// Main low-level decompressor coroutine function. This is the only function actually needed for decompression. All the other functions are just high-level helpers for improved usability.
// This is a universal API, i.e. it can be used as a building block to build any desired higher level decompression API. In the limit case, it can be called once per every byte input or output.
MINIZ_STATIC tinfl_حالت tinfl_decompress(tinfl_decompressor *r, ثابت mz_uint8 *p_دننه_buf_بل, size_t *p_دننه_buf_اندازه, mz_uint8 *p_بهر_buf_پیل, mz_uint8 *p_بهر_buf_بل, size_t *p_بهر_buf_اندازه, ثابت mz_uint32 decomp_flags);

// Internal/private bits follow.
تعداد
{
  TINFL_MAX_HUFF_TABLES = 3, TINFL_MAX_HUFF_SYMBOLS_0 = 288, TINFL_MAX_HUFF_SYMBOLS_1 = 32, TINFL_MAX_HUFF_SYMBOLS_2 = 19,
  TINFL_FAST_LOOKUP_بټونه = 10, TINFL_FAST_LOOKUP_اندازه = 1 << TINFL_FAST_LOOKUP_بټونه
};

تعريفنوع بنية
{
  mz_uint8 m_کوډ_اندازه[TINFL_MAX_HUFF_SYMBOLS_0];
  mz_int16 m_look_پورته[TINFL_FAST_LOOKUP_اندازه], m_ونه[TINFL_MAX_HUFF_SYMBOLS_0 * 2];
} tinfl_huff_جدول;

#إذا MINIZ_HAS_64_بټ_REGISTERS
  #تعریف_کړه TINFL_USE_64_بټ_BITBUF 1
#د_که_پای

#إذا TINFL_USE_64_بټ_BITBUF
  تعريفنوع mz_uint64 tinfl_بټ_buf_t;
  #تعریف_کړه TINFL_BITBUF_اندازه (64)
#وإلا
  تعريفنوع mz_uint32 tinfl_بټ_buf_t;
  #تعریف_کړه TINFL_BITBUF_اندازه (32)
#د_که_پای

بنية tinfl_decompressor_نښان
{
  mz_uint32 m_state, m_عدد_بټونه, m_zhdr0, m_zhdr1, m_z_adler32, m_final, m_type, m_check_adler32, m_dist, m_counter, m_عدد_extra, m_جدول_sizes[TINFL_MAX_HUFF_TABLES];
  tinfl_بټ_buf_t m_بټ_buf;
  size_t m_dist_from_بهر_buf_پیل;
  tinfl_huff_جدول m_tables[TINFL_MAX_HUFF_TABLES];
  mz_uint8 m_raw_سرلیک[4], m_len_codes[TINFL_MAX_HUFF_SYMBOLS_0 + TINFL_MAX_HUFF_SYMBOLS_1 + 137];
};
#د_که_پای /*#ifndef MINIZ_NO_INFLATE_APIS*/

// ------------------- Low-level Compression API Definitions
#که_نه_تعریف_شوی MINIZ_NO_DEFLATE_APIS

// Set TDEFL_LESS_MEMORY to 1 to use less memory (compression will be slightly slower, and raw/dynamic blocks will be output more frequently).
#تعریف_کړه TDEFL_LESS_حافظه 0

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
  TDEFL_WRITE_ZLIB_سرلیک             = 0x01000,
  TDEFL_COMPUTE_ADLER32               = 0x02000,
  TDEFL_GREEDY_PARSING_FLAG           = 0x04000,
  TDEFL_NONDETERMINISTIC_PARSING_FLAG = 0x08000,
  TDEFL_RLE_MATCHES                   = 0x10000,
  TDEFL_FILTER_MATCHES                = 0x20000,
  TDEFL_FORCE_ALL_STATIC_بلاکونه       = 0x40000,
  TDEFL_FORCE_ALL_RAW_بلاکونه          = 0x80000
};

#که_نه_تعریف_شوی MINIZ_SDL_NOUNUSED
// High level compression functions:
// tdefl_compress_mem_to_heap() compresses a block in memory to a heap block allocated via malloc().
// On entry:
//  pSrc_buf, src_buf_len: Pointer and size of source block to compress.
//  flags: The max match finder probes (default is 128) logically OR'd against the above flags. Higher probes are slower but improve compression.
// On return:
//  Function returns a pointer to the compressed data, or NULL on failure.
//  *pOut_len will be set to the compressed data's size, which could be larger than src_buf_len on uncompressible data.
//  The caller must free() the returned block when it's no longer needed.
MINIZ_STATIC فراغ *tdefl_compress_mem_منزل_ډېرۍ(ثابت فراغ *pSrc_buf, size_t src_buf_len, size_t *p_بهر_len, صحيح flags);

// tdefl_compress_mem_to_mem() compresses a block in memory to another block in memory.
// Returns 0 on failure.
MINIZ_STATIC size_t tdefl_compress_mem_منزل_mem(فراغ *p_بهر_buf, size_t بهر_buf_len, ثابت فراغ *pSrc_buf, size_t src_buf_len, صحيح flags);
#د_که_پای /* MINIZ_SDL_NOUNUSED */

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
MINIZ_STATIC فراغ *tdefl_write_image_منزل_png_file_دننه_حافظه_ex(ثابت فراغ *pImage, صحيح w, صحيح h, صحيح عدد_chans, صحيح bpl, size_t *p_Len_بهر, mz_uint level, mz_bool flip, mz_uint8 *plte, صحيح plte_اندازه, mz_uint8 *trns, صحيح trns_اندازه);
#که_نه_تعریف_شوی MINIZ_SDL_NOUNUSED
MINIZ_STATIC فراغ *tdefl_write_image_منزل_png_file_دننه_حافظه(ثابت فراغ *pImage, صحيح w, صحيح h, صحيح عدد_chans, صحيح bpl, size_t *p_Len_بهر);
#د_که_پای

// Output stream interface. The compressor uses this interface to write compressed data. It'll typically be called TDEFL_OUT_BUF_SIZE at a time.
تعريفنوع mz_bool (*tdefl_put_buf_func_ptr)(ثابت فراغ* pBuf, صحيح len, فراغ *pUser);

#که_نه_تعریف_شوی MINIZ_SDL_NOUNUSED
// tdefl_compress_mem_to_output() compresses a block to an output stream. The above helpers use this function internally.
MINIZ_STATIC mz_bool tdefl_compress_mem_منزل_output(ثابت فراغ *pBuf, size_t buf_len, tdefl_put_buf_func_ptr pPut_buf_func, فراغ *pPut_buf_user, صحيح flags);
#د_که_پای

//enum { TDEFL_MAX_HUFF_TABLES = 3, TDEFL_MAX_HUFF_SYMBOLS_0 = 288, TDEFL_MAX_HUFF_SYMBOLS_1 = 32, TDEFL_MAX_HUFF_SYMBOLS_2 = 19, TDEFL_LZ_DICT_SIZE = 32768, TDEFL_LZ_DICT_SIZE_MASK = TDEFL_LZ_DICT_SIZE - 1, TDEFL_MIN_MATCH_LEN = 3, TDEFL_MAX_MATCH_LEN = 258 };
#تعریف_کړه TDEFL_MAX_HUFF_TABLES	3
#تعریف_کړه TDEFL_MAX_HUFF_SYMBOLS_0 288
#تعریف_کړه TDEFL_MAX_HUFF_SYMBOLS_1 32
#تعریف_کړه TDEFL_MAX_HUFF_SYMBOLS_2 19
#تعریف_کړه TDEFL_LZ_DICT_اندازه 32768
#تعریف_کړه TDEFL_LZ_DICT_اندازه_ماسک	( TDEFL_LZ_DICT_اندازه - 1 )
#تعریف_کړه TDEFL_MIN_سمون_LEN	3
#تعریف_کړه TDEFL_MAX_سمون_LEN 258

// TDEFL_OUT_BUF_SIZE MUST be large enough to hold a single entire compressed output block (using static/fixed Huffman codes).
#إذا TDEFL_LESS_حافظه
تعداد { TDEFL_LZ_کوډ_BUF_اندازه = 24 * 1024, TDEFL_بهر_BUF_اندازه = (TDEFL_LZ_کوډ_BUF_اندازه * 13 ) / 10, TDEFL_MAX_HUFF_SYMBOLS = 288, TDEFL_LZ_HASH_بټونه = 12, TDEFL_LEVEL1_HASH_اندازه_ماسک = 4095, TDEFL_LZ_HASH_ښويدنه = (TDEFL_LZ_HASH_بټونه + 2) / 3, TDEFL_LZ_HASH_اندازه = 1 << TDEFL_LZ_HASH_بټونه };
#وإلا
تعداد { TDEFL_LZ_کوډ_BUF_اندازه = 64 * 1024, TDEFL_بهر_BUF_اندازه = (TDEFL_LZ_کوډ_BUF_اندازه * 13 ) / 10, TDEFL_MAX_HUFF_SYMBOLS = 288, TDEFL_LZ_HASH_بټونه = 15, TDEFL_LEVEL1_HASH_اندازه_ماسک = 4095, TDEFL_LZ_HASH_ښويدنه = (TDEFL_LZ_HASH_بټونه + 2) / 3, TDEFL_LZ_HASH_اندازه = 1 << TDEFL_LZ_HASH_بټونه };
#د_که_پای

// The low-level tdefl functions below may be used directly if the above helper functions aren't flexible enough. The low-level functions don't make any heap allocations, unlike the above helper functions.
تعريفنوع تعداد
{
  TDEFL_حالت_BAD_PARAM = -2,
  TDEFL_حالت_PUT_BUF_FAILED = -1,
  TDEFL_حالت_OKAY = 0,
  TDEFL_حالت_بشپړ = 1,
} tdefl_حالت;

// Must map to MZ_NO_FLUSH, MZ_SYNC_FLUSH, etc. enums
تعريفنوع تعداد
{
  TDEFL_NO_FLUSH = 0,
  TDEFL_SYNC_FLUSH = 2,
  TDEFL_ډک_FLUSH = 3,
  TDEFL_پای = 4
} tdefl_flush;

// tdefl's compression state structure.
تعريفنوع بنية
{
  tdefl_put_buf_func_ptr m_pPut_buf_func;
  فراغ *m_pPut_buf_user;
  mz_uint m_flags, m_max_probes[2];
  صحيح m_greedy_parsing;
  mz_uint m_adler32, m_lookahead_pos, m_lookahead_اندازه, m_dict_اندازه;
  mz_uint8 *m_p_LZ_کوډ_buf, *m_pLZ_flags, *m_pOutput_buf, *m_p_Output_buf_پای_ټکی;
  mz_uint m_عدد_flags_کیڼ, m_ټول_lz_بایټونه, m_lz_کوډ_buf_dict_pos, m_بټونه_دننه, m_بټ_بفر;
  mz_uint m_saved_سمون_dist, m_saved_سمون_len, m_saved_lit, m_output_flush_ofs, m_output_flush_پاتې_شوی, m_پای_ته_رسېدلی, m_بلاک_شاخص, m_غواړي_منزل_پای;
  tdefl_حالت m_prev_return_حالت;
  ثابت فراغ *m_p_دننه_buf;
  فراغ *m_p_بهر_buf;
  size_t *m_p_دننه_buf_اندازه, *m_p_بهر_buf_اندازه;
  tdefl_flush m_flush;
  ثابت mz_uint8 *m_pSrc;
  size_t m_src_buf_کیڼ, m_بهر_buf_ofs;
  mz_uint8 m_dict[TDEFL_LZ_DICT_اندازه + TDEFL_MAX_سمون_LEN - 1];
  mz_uint16 m_huff_شمېر[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint16 m_huff_codes[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint8 m_huff_کوډ_sizes[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint8 m_lz_کوډ_buf[TDEFL_LZ_کوډ_BUF_اندازه];
  mz_uint16 m_بل[TDEFL_LZ_DICT_اندازه];
  mz_uint16 m_hash[TDEFL_LZ_HASH_اندازه];
  mz_uint8 m_output_buf[TDEFL_بهر_BUF_اندازه];
} tdefl_compressor;

// Initializes the compressor.
// There is no corresponding deinit() function because the tdefl API's do not dynamically allocate memory.
// pBut_buf_func: If NULL, output data will be supplied to the specified callback. In this case, the user should call the tdefl_compress_buffer() API for compression.
// If pBut_buf_func is NULL the user should always call the tdefl_compress() API.
// flags: See the above enums (TDEFL_HUFFMAN_ONLY, TDEFL_WRITE_ZLIB_HEADER, etc.)
MINIZ_STATIC tdefl_حالت tdefl_init(tdefl_compressor *d, tdefl_put_buf_func_ptr pPut_buf_func, فراغ *pPut_buf_user, صحيح flags);

// Compresses a block of data, consuming as much of the specified input buffer as possible, and writing as much compressed data to the specified output buffer as possible.
MINIZ_STATIC tdefl_حالت tdefl_compress(tdefl_compressor *d, ثابت فراغ *p_دننه_buf, size_t *p_دننه_buf_اندازه, فراغ *p_بهر_buf, size_t *p_بهر_buf_اندازه, tdefl_flush flush);

// tdefl_compress_buffer() is only usable when the tdefl_init() is called with a non-NULL tdefl_put_buf_func_ptr.
// tdefl_compress_buffer() always consumes the entire input buffer.
MINIZ_STATIC tdefl_حالت tdefl_compress_بفر(tdefl_compressor *d, ثابت فراغ *p_دننه_buf, size_t دننه_buf_اندازه, tdefl_flush flush);

#که_نه_تعریف_شوی MINIZ_SDL_NOUNUSED
MINIZ_STATIC tdefl_حالت tdefl_get_prev_return_حالت(tdefl_compressor *d);
MINIZ_STATIC mz_uint32 tdefl_get_adler32(tdefl_compressor *d);
#د_که_پای

// Can't use tdefl_create_comp_flags_from_zip_params if MINIZ_NO_ZLIB_APIS isn't defined, because it uses some of its macros.
#که_نه_تعریف_شوی MINIZ_NO_ZLIB_APIS
// Create tdefl_compress() flags given zlib-style compression parameters.
// level may range from [0,10] (where 10 is absolute max compression, but may be much slower on some files)
// window_bits may be -15 (raw deflate) or 15 (zlib)
// strategy may be either MZ_DEFAULT_STRATEGY, MZ_FILTERED, MZ_HUFFMAN_ONLY, MZ_RLE, or MZ_FIXED
MINIZ_STATIC mz_uint tdefl_create_comp_flags_from_zip_params(صحيح level, صحيح کړکۍ_بټونه, صحيح strategy);
#د_که_پای // #ifndef MINIZ_NO_ZLIB_APIS

#د_که_پای /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای // MINIZ_HEADER_INCLUDED

// ------------------- End of Header: Implementation follows. (If you only want the header, define MINIZ_HEADER_FILE_ONLY.)

#که_نه_تعریف_شوی MINIZ_سرلیک_FILE_ONLY

#که_تعریف_شوی _MSC_VER
#لارښوونه warning (ټېل)
#لارښوونه warning (disable:4505) // unreferenced local function has been removed
#د_که_پای

تعريفنوع بینښه حرف mz_validate_uint16[حجم(mz_uint16)==2 ? 1 : -1];
تعريفنوع بینښه حرف mz_validate_uint32[حجم(mz_uint32)==4 ? 1 : -1];
تعريفنوع بینښه حرف mz_validate_uint64[حجم(mz_uint64)==8 ? 1 : -1];

/*#include <string.h>*/

#که_نه_تعریف_شوی MZ_ASSERT
#ضمن <assert.h>
#تعریف_کړه MZ_ASSERT(x) أكد(x)
#د_که_پای

#که_تعریف_شوی MINIZ_NO_MALLOC
  #تعریف_کړه MZ_MALLOC(x) عدم
  #تعریف_کړه MZ_FREE(x) (فراغ)x, ((فراغ)0)
  #تعریف_کړه MZ_REALLOC(p, x) عدم
#وإلاإذا defined(MINIZ_SDL_MALLOC)
  #تعریف_کړه MZ_MALLOC(x) SDL_malloc(x)
  #تعریف_کړه MZ_FREE(x) SDL_free(x)
  #تعریف_کړه MZ_REALLOC(p, x) SDL_realloc(p, x)
#وإلا
  #تعریف_کړه MZ_MALLOC(x) حافظه_ورکړه(x)
  #تعریف_کړه MZ_FREE(x) حرر(x)
  #تعریف_کړه MZ_REALLOC(p, x) realloc(p, x)
#د_که_پای

#تعریف_کړه MZ_MAX(a,b) (((a)>(b))?(a):(b))
#تعریف_کړه MZ_MIN(a,b) (((a)<(b))?(a):(b))
#تعریف_کړه MZ_CLEAR_OBJ(obj) memset(&(obj), 0, حجم(obj))
#تعریف_کړه MZ_CLEAR_ARR(obj) memset((obj), 0, حجم(obj))
#تعریف_کړه MZ_CLEAR_PTR(obj) memset((obj), 0, حجم(*obj))

#إذا MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  #تعریف_کړه MZ_READ_LE16(p) *((ثابت mz_uint16 *)(p))
  #تعریف_کړه MZ_READ_LE32(p) *((ثابت mz_uint32 *)(p))
#وإلا
  #تعریف_کړه MZ_READ_LE16(p) ((mz_uint32)(((ثابت mz_uint8 *)(p))[0]) | ((mz_uint32)(((ثابت mz_uint8 *)(p))[1]) << 8U))
  #تعریف_کړه MZ_READ_LE32(p) ((mz_uint32)(((ثابت mz_uint8 *)(p))[0]) | ((mz_uint32)(((ثابت mz_uint8 *)(p))[1]) << 8U) | ((mz_uint32)(((ثابت mz_uint8 *)(p))[2]) << 16U) | ((mz_uint32)(((ثابت mz_uint8 *)(p))[3]) << 24U))
#د_که_پای

#که_تعریف_شوی _MSC_VER
  #تعریف_کړه MZ_FORCEINLINE __forceinline
#وإلاإذا defined(__GNUC__)
  #تعریف_کړه MZ_FORCEINLINE مضمن __attribute__((__always_inline__))
#وإلا
  #تعریف_کړه MZ_FORCEINLINE مضمن
#د_که_پای

#که_تعریف_شوی __cplusplus
  خارجي "C" {
#د_که_پای

// ------------------- zlib-style API's

mz_ulong mz_adler32(mz_ulong adler, ثابت بینښه حرف *ptr, size_t buf_len)
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
mz_ulong mz_دوراني_ازموینه_32(mz_ulong دوراني_ازموینه, ثابت mz_uint8 *ptr, size_t buf_len)
{
  ساكن ثابت mz_uint32 s_دوراني_ازموینه_32[16] = { 0, 0x1db71064, 0x3b6e20c8, 0x26d930ac, 0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
    0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c, 0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c };
  mz_uint32 crcu32 = (mz_uint32)دوراني_ازموینه;
  إذا (!ptr) أرجع MZ_دوراني_ازموینه_32_INIT;
  crcu32 = ~crcu32; طالما (buf_len--) { mz_uint8 b = *ptr++; crcu32 = (crcu32 >> 4) ^ s_دوراني_ازموینه_32[(crcu32 & 0xF) ^ (b & 0xF)]; crcu32 = (crcu32 >> 4) ^ s_دوراني_ازموینه_32[(crcu32 & 0xF) ^ (b >> 4)]; }
  أرجع ~crcu32;
}

MINIZ_STATIC فراغ mz_free(فراغ *p)
{
  MZ_FREE(p);
}

#که_نه_تعریف_شوی MINIZ_NO_ZLIB_APIS

ساكن فراغ *def_alloc_func(فراغ *opaque, size_t توکي, size_t اندازه) { (فراغ)opaque, (فراغ)توکي, (فراغ)اندازه; أرجع MZ_MALLOC(توکي * اندازه); }
ساكن فراغ def_free_func(فراغ *opaque, فراغ *پته) { (فراغ)opaque, (فراغ)پته; MZ_FREE(پته); }
ساكن فراغ *def_realloc_func(فراغ *opaque, فراغ *پته, size_t توکي, size_t اندازه) { (فراغ)opaque, (فراغ)پته, (فراغ)توکي, (فراغ)اندازه; أرجع MZ_REALLOC(پته, توکي * اندازه); }

ثابت حرف *mz_نسخه(فراغ)
{
  أرجع MZ_نسخه;
}

#که_نه_تعریف_شوی MINIZ_NO_DEFLATE_APIS

صحيح mz_deflateInit(mz_streamp p_بهیر, صحيح level)
{
  أرجع mz_deflateInit2(p_بهیر, level, MZ_DEFLATED, MZ_DEFAULT_کړکۍ_بټونه, 9, MZ_DEFAULT_STRATEGY);
}

صحيح mz_deflateInit2(mz_streamp p_بهیر, صحيح level, صحيح لاره, صحيح کړکۍ_بټونه, صحيح mem_level, صحيح strategy)
{
  tdefl_compressor *pComp;
  mz_uint comp_flags = TDEFL_COMPUTE_ADLER32 | tdefl_create_comp_flags_from_zip_params(level, کړکۍ_بټونه, strategy);

  إذا (!p_بهیر) أرجع MZ_بهیر_ERROR;
  إذا ((لاره != MZ_DEFLATED) || ((mem_level < 1) || (mem_level > 9)) || ((کړکۍ_بټونه != MZ_DEFAULT_کړکۍ_بټونه) && (-کړکۍ_بټونه != MZ_DEFAULT_کړکۍ_بټونه))) أرجع MZ_PARAM_ERROR;

  p_بهیر->معلومات_type = 0;
  p_بهیر->adler = MZ_ADLER32_INIT;
  p_بهیر->پیغام_2 = عدم;
  p_بهیر->reserved = 0;
  p_بهیر->ټول_دننه = 0;
  p_بهیر->ټول_بهر = 0;
  إذا (!p_بهیر->zalloc) p_بهیر->zalloc = def_alloc_func;
  إذا (!p_بهیر->zfree) p_بهیر->zfree = def_free_func;

  pComp = (tdefl_compressor *)p_بهیر->zalloc(p_بهیر->opaque, 1, حجم(tdefl_compressor));
  إذا (!pComp)
    أرجع MZ_MEM_ERROR;

  p_بهیر->state = (بنية mz_دننی_state *)pComp;

  إذا (tdefl_init(pComp, عدم, عدم, comp_flags) != TDEFL_حالت_OKAY)
  {
    mz_deflate_پای_ټکی(p_بهیر);
    أرجع MZ_PARAM_ERROR;
  }

  أرجع MZ_OK;
}

صحيح mz_deflateReset(mz_streamp p_بهیر)
{
  إذا ((!p_بهیر) || (!p_بهیر->state) || (!p_بهیر->zalloc) || (!p_بهیر->zfree)) أرجع MZ_بهیر_ERROR;
  p_بهیر->ټول_دننه = p_بهیر->ټول_بهر = 0;
  tdefl_init((tdefl_compressor*)p_بهیر->state, عدم, عدم, ((tdefl_compressor*)p_بهیر->state)->m_flags);
  أرجع MZ_OK;
}

صحيح mz_deflate(mz_streamp p_بهیر, صحيح flush)
{
  size_t دننه_بایټونه, بهر_بایټونه;
  mz_ulong orig_ټول_دننه, orig_ټول_بهر;
  صحيح mz_حالت = MZ_OK;

  إذا ((!p_بهیر) || (!p_بهیر->state) || (flush < 0) || (flush > MZ_پای) || (!p_بهیر->بل_بهر)) أرجع MZ_بهیر_ERROR;
  إذا (!p_بهیر->avail_بهر) أرجع MZ_BUF_ERROR;

  إذا (flush == MZ_PARTIAL_FLUSH) flush = MZ_SYNC_FLUSH;

  إذا (((tdefl_compressor*)p_بهیر->state)->m_prev_return_حالت == TDEFL_حالت_بشپړ)
    أرجع (flush == MZ_پای) ? MZ_بهیر_پای_ټکی : MZ_BUF_ERROR;

  orig_ټول_دننه = p_بهیر->ټول_دننه; orig_ټول_بهر = p_بهیر->ټول_بهر;
  لكل ( ; ; )
  {
    tdefl_حالت defl_حالت;
    دننه_بایټونه = p_بهیر->avail_دننه; بهر_بایټونه = p_بهیر->avail_بهر;

    defl_حالت = tdefl_compress((tdefl_compressor*)p_بهیر->state, p_بهیر->بل_دننه, &دننه_بایټونه, p_بهیر->بل_بهر, &بهر_بایټونه, (tdefl_flush)flush);
    p_بهیر->بل_دننه += (mz_uint)دننه_بایټونه; p_بهیر->avail_دننه -= (mz_uint)دننه_بایټونه;
    p_بهیر->ټول_دننه += (mz_uint)دننه_بایټونه; p_بهیر->adler = tdefl_get_adler32((tdefl_compressor*)p_بهیر->state);

    p_بهیر->بل_بهر += (mz_uint)بهر_بایټونه; p_بهیر->avail_بهر -= (mz_uint)بهر_بایټونه;
    p_بهیر->ټول_بهر += (mz_uint)بهر_بایټونه;

    إذا (defl_حالت < 0)
    {
      mz_حالت = MZ_بهیر_ERROR;
      اكسر;
    }
    وإلا إذا (defl_حالت == TDEFL_حالت_بشپړ)
    {
      mz_حالت = MZ_بهیر_پای_ټکی;
      اكسر;
    }
    وإلا إذا (!p_بهیر->avail_بهر)
      اكسر;
    وإلا إذا ((!p_بهیر->avail_دننه) && (flush != MZ_پای))
    {
      إذا ((flush) || (p_بهیر->ټول_دننه != orig_ټول_دننه) || (p_بهیر->ټول_بهر != orig_ټول_بهر))
        اكسر;
      أرجع MZ_BUF_ERROR; // Can't make forward progress without some input.
    }
  }
  أرجع mz_حالت;
}

صحيح mz_deflate_پای_ټکی(mz_streamp p_بهیر)
{
  إذا (!p_بهیر) أرجع MZ_بهیر_ERROR;
  إذا (p_بهیر->state)
  {
    p_بهیر->zfree(p_بهیر->opaque, p_بهیر->state);
    p_بهیر->state = عدم;
  }
  أرجع MZ_OK;
}

mz_ulong mz_deflateBound(mz_streamp p_بهیر, mz_ulong سرچینه_len)
{
  (فراغ)p_بهیر;
  // This is really over conservative. (And lame, but it's actually pretty tricky to compute a true upper bound given the way tdefl's blocking works.)
  أرجع MZ_MAX(128 + (سرچینه_len * 110) / 100, 128 + سرچینه_len + ((سرچینه_len / (31 * 1024)) + 1) * 5);
}

صحيح mz_compress2(بینښه حرف *pDest, mz_ulong *pDest_len, ثابت بینښه حرف *p_سرچینه, mz_ulong سرچینه_len, صحيح level)
{
  صحيح حالت;
  mz_بهیر بهیر;
  memset(&بهیر, 0, حجم(بهیر));

  // In case mz_ulong is 64-bits (argh I hate longs).
  إذا ((سرچینه_len | *pDest_len) > 0xFFFFFFFFU) أرجع MZ_PARAM_ERROR;

  بهیر.بل_دننه = p_سرچینه;
  بهیر.avail_دننه = (mz_uint32)سرچینه_len;
  بهیر.بل_بهر = pDest;
  بهیر.avail_بهر = (mz_uint32)*pDest_len;

  حالت = mz_deflateInit(&بهیر, level);
  إذا (حالت != MZ_OK) أرجع حالت;

  حالت = mz_deflate(&بهیر, MZ_پای);
  إذا (حالت != MZ_بهیر_پای_ټکی)
  {
    mz_deflate_پای_ټکی(&بهیر);
    أرجع (حالت == MZ_OK) ? MZ_BUF_ERROR : حالت;
  }

  *pDest_len = بهیر.ټول_بهر;
  أرجع mz_deflate_پای_ټکی(&بهیر);
}

صحيح mz_compress(بینښه حرف *pDest, mz_ulong *pDest_len, ثابت بینښه حرف *p_سرچینه, mz_ulong سرچینه_len)
{
  أرجع mz_compress2(pDest, pDest_len, p_سرچینه, سرچینه_len, MZ_DEFAULT_COMPRESSION);
}

mz_ulong mz_compressBound(mz_ulong سرچینه_len)
{
  أرجع mz_deflateBound(عدم, سرچینه_len);
}

#د_که_پای /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#که_نه_تعریف_شوی MINIZ_NO_INFLATE_APIS

تعريفنوع بنية
{
  tinfl_decompressor m_decomp;
  mz_uint m_dict_ofs, m_dict_avail, m_لومړی_call, m_has_flushed; صحيح m_کړکۍ_بټونه;
  mz_uint8 m_dict[TINFL_LZ_DICT_اندازه];
  tinfl_حالت m_وروستی_حالت;
} inflate_state;

صحيح mz_inflateInit2(mz_streamp p_بهیر, صحيح کړکۍ_بټونه)
{
  inflate_state *pDecomp;
  إذا (!p_بهیر) أرجع MZ_بهیر_ERROR;
  إذا ((کړکۍ_بټونه != MZ_DEFAULT_کړکۍ_بټونه) && (-کړکۍ_بټونه != MZ_DEFAULT_کړکۍ_بټونه)) أرجع MZ_PARAM_ERROR;

  p_بهیر->معلومات_type = 0;
  p_بهیر->adler = 0;
  p_بهیر->پیغام_2 = عدم;
  p_بهیر->ټول_دننه = 0;
  p_بهیر->ټول_بهر = 0;
  p_بهیر->reserved = 0;
  إذا (!p_بهیر->zalloc) p_بهیر->zalloc = def_alloc_func;
  إذا (!p_بهیر->zfree) p_بهیر->zfree = def_free_func;

  pDecomp = (inflate_state*)p_بهیر->zalloc(p_بهیر->opaque, 1, حجم(inflate_state));
  إذا (!pDecomp) أرجع MZ_MEM_ERROR;

  p_بهیر->state = (بنية mz_دننی_state *)pDecomp;

  tinfl_init(&pDecomp->m_decomp);
  pDecomp->m_dict_ofs = 0;
  pDecomp->m_dict_avail = 0;
  pDecomp->m_وروستی_حالت = TINFL_حالت_NEEDS_نور_ننوت;
  pDecomp->m_لومړی_call = 1;
  pDecomp->m_has_flushed = 0;
  pDecomp->m_کړکۍ_بټونه = کړکۍ_بټونه;

  أرجع MZ_OK;
}

صحيح mz_inflateInit(mz_streamp p_بهیر)
{
   أرجع mz_inflateInit2(p_بهیر, MZ_DEFAULT_کړکۍ_بټونه);
}

صحيح mz_inflate(mz_streamp p_بهیر, صحيح flush)
{
  inflate_state* pState;
  mz_uint n, لومړی_call, decomp_flags = TINFL_FLAG_COMPUTE_ADLER32;
  size_t دننه_بایټونه, بهر_بایټونه, orig_avail_دننه;
  tinfl_حالت حالت;

  إذا ((!p_بهیر) || (!p_بهیر->state)) أرجع MZ_بهیر_ERROR;
  إذا (flush == MZ_PARTIAL_FLUSH) flush = MZ_SYNC_FLUSH;
  إذا ((flush) && (flush != MZ_SYNC_FLUSH) && (flush != MZ_پای)) أرجع MZ_بهیر_ERROR;

  pState = (inflate_state*)p_بهیر->state;
  إذا (pState->m_کړکۍ_بټونه > 0) decomp_flags |= TINFL_FLAG_PARSE_ZLIB_سرلیک;
  orig_avail_دننه = p_بهیر->avail_دننه;

  لومړی_call = pState->m_لومړی_call; pState->m_لومړی_call = 0;
  إذا (pState->m_وروستی_حالت < 0) أرجع MZ_معلومات_ERROR;

  إذا (pState->m_has_flushed && (flush != MZ_پای)) أرجع MZ_بهیر_ERROR;
  pState->m_has_flushed |= (flush == MZ_پای);

  إذا ((flush == MZ_پای) && (لومړی_call))
  {
    // MZ_FINISH on the first call implies that the input and output buffers are large enough to hold the entire compressed/decompressed file.
    decomp_flags |= TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF;
    دننه_بایټونه = p_بهیر->avail_دننه; بهر_بایټونه = p_بهیر->avail_بهر;
    حالت = tinfl_decompress(&pState->m_decomp, p_بهیر->بل_دننه, &دننه_بایټونه, p_بهیر->بل_بهر, p_بهیر->بل_بهر, &بهر_بایټونه, decomp_flags);
    pState->m_وروستی_حالت = حالت;
    p_بهیر->بل_دننه += (mz_uint)دننه_بایټونه; p_بهیر->avail_دننه -= (mz_uint)دننه_بایټونه; p_بهیر->ټول_دننه += (mz_uint)دننه_بایټونه;
    p_بهیر->adler = tinfl_get_adler32(&pState->m_decomp);
    p_بهیر->بل_بهر += (mz_uint)بهر_بایټونه; p_بهیر->avail_بهر -= (mz_uint)بهر_بایټونه; p_بهیر->ټول_بهر += (mz_uint)بهر_بایټونه;

    إذا (حالت < 0)
      أرجع MZ_معلومات_ERROR;
    وإلا إذا (حالت != TINFL_حالت_بشپړ)
    {
      pState->m_وروستی_حالت = TINFL_حالت_FAILED;
      أرجع MZ_BUF_ERROR;
    }
    أرجع MZ_بهیر_پای_ټکی;
  }
  // flush != MZ_FINISH then we must assume there's more input.
  إذا (flush != MZ_پای) decomp_flags |= TINFL_FLAG_HAS_نور_ننوت;

  إذا (pState->m_dict_avail)
  {
    n = MZ_MIN(pState->m_dict_avail, p_بهیر->avail_بهر);
    حافظه_نقل(p_بهیر->بل_بهر, pState->m_dict + pState->m_dict_ofs, n);
    p_بهیر->بل_بهر += n; p_بهیر->avail_بهر -= n; p_بهیر->ټول_بهر += n;
    pState->m_dict_avail -= n; pState->m_dict_ofs = (pState->m_dict_ofs + n) & (TINFL_LZ_DICT_اندازه - 1);
    أرجع ((pState->m_وروستی_حالت == TINFL_حالت_بشپړ) && (!pState->m_dict_avail)) ? MZ_بهیر_پای_ټکی : MZ_OK;
  }

  لكل ( ; ; )
  {
    دننه_بایټونه = p_بهیر->avail_دننه;
    بهر_بایټونه = TINFL_LZ_DICT_اندازه - pState->m_dict_ofs;

    حالت = tinfl_decompress(&pState->m_decomp, p_بهیر->بل_دننه, &دننه_بایټونه, pState->m_dict, pState->m_dict + pState->m_dict_ofs, &بهر_بایټونه, decomp_flags);
    pState->m_وروستی_حالت = حالت;

    p_بهیر->بل_دننه += (mz_uint)دننه_بایټونه; p_بهیر->avail_دننه -= (mz_uint)دننه_بایټونه;
    p_بهیر->ټول_دننه += (mz_uint)دننه_بایټونه; p_بهیر->adler = tinfl_get_adler32(&pState->m_decomp);

    pState->m_dict_avail = (mz_uint)بهر_بایټونه;

    n = MZ_MIN(pState->m_dict_avail, p_بهیر->avail_بهر);
    حافظه_نقل(p_بهیر->بل_بهر, pState->m_dict + pState->m_dict_ofs, n);
    p_بهیر->بل_بهر += n; p_بهیر->avail_بهر -= n; p_بهیر->ټول_بهر += n;
    pState->m_dict_avail -= n; pState->m_dict_ofs = (pState->m_dict_ofs + n) & (TINFL_LZ_DICT_اندازه - 1);

    إذا (حالت < 0)
       أرجع MZ_معلومات_ERROR; // Stream is corrupted (there could be some uncompressed data left in the output dictionary - oh well).
    وإلا إذا ((حالت == TINFL_حالت_NEEDS_نور_ننوت) && (!orig_avail_دننه))
      أرجع MZ_BUF_ERROR; // Signal caller that we can't make forward progress without supplying more input or by setting flush to MZ_FINISH.
    وإلا إذا (flush == MZ_پای)
    {
       // The output buffer MUST be large to hold the remaining uncompressed data when flush==MZ_FINISH.
       إذا (حالت == TINFL_حالت_بشپړ)
          أرجع pState->m_dict_avail ? MZ_BUF_ERROR : MZ_بهیر_پای_ټکی;
       // status here must be TINFL_STATUS_HAS_MORE_OUTPUT, which means there's at least 1 more byte on the way. If there's no more room left in the output buffer then something is wrong.
       وإلا إذا (!p_بهیر->avail_بهر)
          أرجع MZ_BUF_ERROR;
    }
    وإلا إذا ((حالت == TINFL_حالت_بشپړ) || (!p_بهیر->avail_دننه) || (!p_بهیر->avail_بهر) || (pState->m_dict_avail))
      اكسر;
  }

  أرجع ((حالت == TINFL_حالت_بشپړ) && (!pState->m_dict_avail)) ? MZ_بهیر_پای_ټکی : MZ_OK;
}

صحيح mz_inflate_پای_ټکی(mz_streamp p_بهیر)
{
  إذا (!p_بهیر)
    أرجع MZ_بهیر_ERROR;
  إذا (p_بهیر->state)
  {
    p_بهیر->zfree(p_بهیر->opaque, p_بهیر->state);
    p_بهیر->state = عدم;
  }
  أرجع MZ_OK;
}

صحيح mz_uncompress(بینښه حرف *pDest, mz_ulong *pDest_len, ثابت بینښه حرف *p_سرچینه, mz_ulong سرچینه_len)
{
  mz_بهیر بهیر;
  صحيح حالت;
  memset(&بهیر, 0, حجم(بهیر));

  // In case mz_ulong is 64-bits (argh I hate longs).
  إذا ((سرچینه_len | *pDest_len) > 0xFFFFFFFFU) أرجع MZ_PARAM_ERROR;

  بهیر.بل_دننه = p_سرچینه;
  بهیر.avail_دننه = (mz_uint32)سرچینه_len;
  بهیر.بل_بهر = pDest;
  بهیر.avail_بهر = (mz_uint32)*pDest_len;

  حالت = mz_inflateInit(&بهیر);
  إذا (حالت != MZ_OK)
    أرجع حالت;

  حالت = mz_inflate(&بهیر, MZ_پای);
  إذا (حالت != MZ_بهیر_پای_ټکی)
  {
    mz_inflate_پای_ټکی(&بهیر);
    أرجع ((حالت == MZ_BUF_ERROR) && (!بهیر.avail_دننه)) ? MZ_معلومات_ERROR : حالت;
  }
  *pDest_len = بهیر.ټول_بهر;

  أرجع mz_inflate_پای_ټکی(&بهیر);
}

#د_که_پای /*#ifndef MINIZ_NO_INFLATE_APIS*/

ثابت حرف *mz_error(صحيح err)
{
  ساكن بنية { صحيح m_err; ثابت حرف *m_pDesc; } s_error_descs[] =
  {
    { MZ_OK, "" }, { MZ_بهیر_پای_ټکی, "stream end" }, { MZ_NEED_DICT, "need dictionary" }, { MZ_ERRNO, "file error" }, { MZ_بهیر_ERROR, "stream error" },
    { MZ_معلومات_ERROR, "data error" }, { MZ_MEM_ERROR, "out of memory" }, { MZ_BUF_ERROR, "buf error" }, { MZ_نسخه_ERROR, "version error" }, { MZ_PARAM_ERROR, "parameter error" }
  };
  mz_uint i; لكل (i = 0; i < حجم(s_error_descs) / حجم(s_error_descs[0]); ++i) إذا (s_error_descs[i].m_err == err) أرجع s_error_descs[i].m_pDesc;
  أرجع عدم;
}

#د_که_پای //MINIZ_NO_ZLIB_APIS

// ------------------- Low-level Decompression (completely independent from all compression API's)
#که_نه_تعریف_شوی MINIZ_NO_INFLATE_APIS

#تعریف_کړه TINFL_MEMCPY(d, s, l) حافظه_نقل(d, s, l)
#تعریف_کړه TINFL_MEMSET(p, c, l) memset(p, c, l)

#تعریف_کړه TINFL_CR_BEGIN بدل(r->m_state) { حالة 0:
#تعریف_کړه TINFL_CR_RETURN(state_شاخص, پایله) افعل { حالت = پایله; r->m_state = state_شاخص; اذهب common_exit; حالة state_شاخص:; } MZ_MACRO_پای_ټکی
#تعریف_کړه TINFL_CR_RETURN_FOREVER(state_شاخص, پایله) افعل { لكل ( ; ; ) { TINFL_CR_RETURN(state_شاخص, پایله); } } MZ_MACRO_پای_ټکی
#تعریف_کړه TINFL_CR_پای }

// TODO: If the caller has indicated that there's no more input, and we attempt to read beyond the input buf, then something is wrong with the input because the inflator never
// reads ahead more than it needs to. Currently TINFL_GET_BYTE() pads the end of the stream with 0's in this scenario.
#تعریف_کړه TINFL_GET_BYTE(state_شاخص, c) افعل { \
  إذا (p_دننه_buf_cur >= p_دننه_buf_پای_ټکی) { \
    لكل ( ; ; ) { \
      إذا (decomp_flags & TINFL_FLAG_HAS_نور_ننوت) { \
        TINFL_CR_RETURN(state_شاخص, TINFL_حالت_NEEDS_نور_ننوت); \
        إذا (p_دننه_buf_cur < p_دننه_buf_پای_ټکی) { \
          c = *p_دننه_buf_cur++; \
          اكسر; \
        } \
      } وإلا { \
        c = 0; \
        اكسر; \
      } \
    } \
  } وإلا c = *p_دننه_buf_cur++; } MZ_MACRO_پای_ټکی

#تعریف_کړه TINFL_NEED_بټونه(state_شاخص, n) افعل { mz_uint c; TINFL_GET_BYTE(state_شاخص, c); بټ_buf |= (((tinfl_بټ_buf_t)c) << عدد_بټونه); عدد_بټونه += 8; } طالما (عدد_بټونه < (mz_uint)(n))
#تعریف_کړه TINFL_SKIP_بټونه(state_شاخص, n) افعل { إذا (عدد_بټونه < (mz_uint)(n)) { TINFL_NEED_بټونه(state_شاخص, n); } بټ_buf >>= (n); عدد_بټونه -= (n); } MZ_MACRO_پای_ټکی
#تعریف_کړه TINFL_GET_بټونه(state_شاخص, b, n) افعل { إذا (عدد_بټونه < (mz_uint)(n)) { TINFL_NEED_بټونه(state_شاخص, n); } b = بټ_buf & ((1 << (n)) - 1); بټ_buf >>= (n); عدد_بټونه -= (n); } MZ_MACRO_پای_ټکی

// TINFL_HUFF_BITBUF_FILL() is only used rarely, when the number of bytes remaining in the input buffer falls below 2.
// It reads just enough bytes from the input stream that are needed to decode the next Huffman code (and absolutely no more). It works by trying to fully decode a
// Huffman code by using whatever bits are currently present in the bit buffer. If this fails, it reads another byte, and tries again until it succeeds or until the
// bit buffer contains >=15 bits (deflate's max. Huffman code size).
#تعریف_کړه TINFL_HUFF_BITBUF_FILL(state_شاخص, pHuff) \
  افعل { \
    لنډمهاله = (pHuff)->m_look_پورته[بټ_buf & (TINFL_FAST_LOOKUP_اندازه - 1)]; \
    إذا (لنډمهاله >= 0) { \
      کوډ_len = لنډمهاله >> 9; \
      إذا ((کوډ_len) && (عدد_بټونه >= کوډ_len)) \
          اكسر; \
    } وإلا إذا (عدد_بټونه > TINFL_FAST_LOOKUP_بټونه) { \
       کوډ_len = TINFL_FAST_LOOKUP_بټونه; \
       افعل { \
          لنډمهاله = (pHuff)->m_ونه[~لنډمهاله + ((بټ_buf >> کوډ_len++) & 1)]; \
       } طالما ((لنډمهاله < 0) && (عدد_بټونه >= (کوډ_len + 1))); \
       إذا (لنډمهاله >= 0) اكسر; \
    } \
    TINFL_GET_BYTE(state_شاخص, c); \
    بټ_buf |= (((tinfl_بټ_buf_t)c) << عدد_بټونه); \
    عدد_بټونه += 8; \
  } طالما (عدد_بټونه < 15);

// TINFL_HUFF_DECODE() decodes the next Huffman coded symbol. It's more complex than you would initially expect because the zlib API expects the decompressor to never read
// beyond the final byte of the deflate stream. (In other words, when this macro wants to read another byte from the input, it REALLY needs another byte in order to fully
// decode the next Huffman code.) Handling this properly is particularly important on raw deflate (non-zlib) streams, which aren't followed by a byte aligned adler-32.
// The slow path is only executed at the very end of the input buffer.
#تعریف_کړه TINFL_HUFF_DECODE(state_شاخص, sym, pHuff) افعل { \
  صحيح لنډمهاله; mz_uint کوډ_len, c; \
  إذا (عدد_بټونه < 15) { \
    إذا ((p_دننه_buf_پای_ټکی - p_دننه_buf_cur) < 2) { \
       TINFL_HUFF_BITBUF_FILL(state_شاخص, pHuff); \
    } وإلا { \
       بټ_buf |= (((tinfl_بټ_buf_t)p_دننه_buf_cur[0]) << عدد_بټونه) | (((tinfl_بټ_buf_t)p_دننه_buf_cur[1]) << (عدد_بټونه + 8)); p_دننه_buf_cur += 2; عدد_بټونه += 16; \
    } \
  } \
  إذا ((لنډمهاله = (pHuff)->m_look_پورته[بټ_buf & (TINFL_FAST_LOOKUP_اندازه - 1)]) >= 0) \
    کوډ_len = لنډمهاله >> 9, لنډمهاله &= 511; \
  وإلا { \
    کوډ_len = TINFL_FAST_LOOKUP_بټونه; افعل { لنډمهاله = (pHuff)->m_ونه[~لنډمهاله + ((بټ_buf >> کوډ_len++) & 1)]; } طالما (لنډمهاله < 0); \
  } sym = لنډمهاله; بټ_buf >>= کوډ_len; عدد_بټونه -= کوډ_len; } MZ_MACRO_پای_ټکی

tinfl_حالت tinfl_decompress(tinfl_decompressor *r, ثابت mz_uint8 *p_دننه_buf_بل, size_t *p_دننه_buf_اندازه, mz_uint8 *p_بهر_buf_پیل, mz_uint8 *p_بهر_buf_بل, size_t *p_بهر_buf_اندازه, ثابت mz_uint32 decomp_flags)
{
  ساكن ثابت صحيح s_اوږدتیا_بنسټ[31] = { 3,4,5,6,7,8,9,10,11,13, 15,17,19,23,27,31,35,43,51,59, 67,83,99,115,131,163,195,227,258,0,0 };
  ساكن ثابت صحيح s_اوږدتیا_extra[31]= { 0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,0,0,0 };
  ساكن ثابت صحيح s_dist_بنسټ[32] = { 1,2,3,4,5,7,9,13,17,25,33,49,65,97,129,193, 257,385,513,769,1025,1537,2049,3073,4097,6145,8193,12289,16385,24577,0,0};
  ساكن ثابت صحيح s_dist_extra[32] = { 0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13};
  ساكن ثابت mz_uint8 s_اوږدتیا_dezigzag[19] = { 16,17,18,0,8,7,9,6,10,5,11,4,12,3,13,2,14,1,15 };
  ساكن ثابت صحيح s_min_جدول_sizes[3] = { 257, 1, 4 };

  tinfl_حالت حالت = TINFL_حالت_FAILED; mz_uint32 عدد_بټونه, dist, counter, عدد_extra; tinfl_بټ_buf_t بټ_buf;
  ثابت mz_uint8 *p_دننه_buf_cur = p_دننه_buf_بل, *ثابت p_دننه_buf_پای_ټکی = p_دننه_buf_بل + *p_دننه_buf_اندازه;
  mz_uint8 *p_بهر_buf_cur = p_بهر_buf_بل, *ثابت p_بهر_buf_پای_ټکی = p_بهر_buf_بل + *p_بهر_buf_اندازه;
  size_t بهر_buf_اندازه_ماسک = (decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF) ? (size_t)-1 : ((p_بهر_buf_بل - p_بهر_buf_پیل) + *p_بهر_buf_اندازه) - 1, dist_from_بهر_buf_پیل;

  // Ensure the output buffer's size is a power of 2, unless the output buffer is large enough to hold the entire output file (in which case it doesn't matter).
  إذا (((بهر_buf_اندازه_ماسک + 1) & بهر_buf_اندازه_ماسک) || (p_بهر_buf_بل < p_بهر_buf_پیل)) { *p_دننه_buf_اندازه = *p_بهر_buf_اندازه = 0; أرجع TINFL_حالت_BAD_PARAM; }

  عدد_بټونه = r->m_عدد_بټونه; بټ_buf = r->m_بټ_buf; dist = r->m_dist; counter = r->m_counter; عدد_extra = r->m_عدد_extra; dist_from_بهر_buf_پیل = r->m_dist_from_بهر_buf_پیل;
  TINFL_CR_BEGIN

  بټ_buf = عدد_بټونه = dist = counter = عدد_extra = r->m_zhdr0 = r->m_zhdr1 = 0; r->m_z_adler32 = r->m_check_adler32 = 1;
  إذا (decomp_flags & TINFL_FLAG_PARSE_ZLIB_سرلیک)
  {
    TINFL_GET_BYTE(1, r->m_zhdr0); TINFL_GET_BYTE(2, r->m_zhdr1);
    counter = (((r->m_zhdr0 * 256 + r->m_zhdr1) % 31 != 0) || (r->m_zhdr1 & 32) || ((r->m_zhdr0 & 15) != 8));
    إذا (!(decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF)) counter |= (((1U << (8U + (r->m_zhdr0 >> 4))) > 32768U) || ((بهر_buf_اندازه_ماسک + 1) < (size_t)(1U << (8U + (r->m_zhdr0 >> 4)))));
    إذا (counter) { TINFL_CR_RETURN_FOREVER(36, TINFL_حالت_FAILED); }
  }

  افعل
  {
    TINFL_GET_بټونه(3, r->m_final, 3); r->m_type = r->m_final >> 1;
    إذا (r->m_type == 0)
    {
      TINFL_SKIP_بټونه(5, عدد_بټونه & 7);
      لكل (counter = 0; counter < 4; ++counter) { إذا (عدد_بټونه) TINFL_GET_بټونه(6, r->m_raw_سرلیک[counter], 8); وإلا TINFL_GET_BYTE(7, r->m_raw_سرلیک[counter]); }
      إذا ((counter = (r->m_raw_سرلیک[0] | (r->m_raw_سرلیک[1] << 8))) != (mz_uint)(0xFFFF ^ (r->m_raw_سرلیک[2] | (r->m_raw_سرلیک[3] << 8)))) { TINFL_CR_RETURN_FOREVER(39, TINFL_حالت_FAILED); }
      طالما ((counter) && (عدد_بټونه))
      {
        TINFL_GET_بټونه(51, dist, 8);
        طالما (p_بهر_buf_cur >= p_بهر_buf_پای_ټکی) { TINFL_CR_RETURN(52, TINFL_حالت_HAS_نور_OUTPUT); }
        *p_بهر_buf_cur++ = (mz_uint8)dist;
        counter--;
      }
      طالما (counter)
      {
        size_t n; طالما (p_بهر_buf_cur >= p_بهر_buf_پای_ټکی) { TINFL_CR_RETURN(9, TINFL_حالت_HAS_نور_OUTPUT); }
        طالما (p_دننه_buf_cur >= p_دننه_buf_پای_ټکی)
        {
          إذا (decomp_flags & TINFL_FLAG_HAS_نور_ننوت)
          {
            TINFL_CR_RETURN(38, TINFL_حالت_NEEDS_نور_ننوت);
          }
          وإلا
          {
            TINFL_CR_RETURN_FOREVER(40, TINFL_حالت_FAILED);
          }
        }
        n = MZ_MIN(MZ_MIN((size_t)(p_بهر_buf_پای_ټکی - p_بهر_buf_cur), (size_t)(p_دننه_buf_پای_ټکی - p_دننه_buf_cur)), counter);
        TINFL_MEMCPY(p_بهر_buf_cur, p_دننه_buf_cur, n); p_دننه_buf_cur += n; p_بهر_buf_cur += n; counter -= (mz_uint)n;
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
        mz_uint8 *p = r->m_tables[0].m_کوډ_اندازه; mz_uint i;
        r->m_جدول_sizes[0] = 288; r->m_جدول_sizes[1] = 32; TINFL_MEMSET(r->m_tables[1].m_کوډ_اندازه, 5, 32);
        لكل ( i = 0; i <= 143; ++i) *p++ = 8;
        لكل ( ; i <= 255; ++i) *p++ = 9;
        لكل ( ; i <= 279; ++i) *p++ = 7;
        لكل ( ; i <= 287; ++i) *p++ = 8;
      }
      وإلا
      {
        لكل (counter = 0; counter < 3; counter++) { TINFL_GET_بټونه(11, r->m_جدول_sizes[counter], "\05\05\04"[counter]); r->m_جدول_sizes[counter] += s_min_جدول_sizes[counter]; }
        MZ_CLEAR_ARR(r->m_tables[2].m_کوډ_اندازه); لكل (counter = 0; counter < r->m_جدول_sizes[2]; counter++) { mz_uint s; TINFL_GET_بټونه(14, s, 3); r->m_tables[2].m_کوډ_اندازه[s_اوږدتیا_dezigzag[counter]] = (mz_uint8)s; }
        r->m_جدول_sizes[2] = 19;
      }
      لكل ( ; (صحيح)r->m_type >= 0; r->m_type--)
      {
        صحيح ونه_بل, ونه_cur; tinfl_huff_جدول *p_جدول;
        mz_uint i, j, کارول_شوی_syms, ټول, sym_شاخص, بل_کوډ[17], ټول_syms[16]; p_جدول = &r->m_tables[r->m_type]; MZ_CLEAR_ARR(ټول_syms); MZ_CLEAR_ARR(p_جدول->m_look_پورته); MZ_CLEAR_ARR(p_جدول->m_ونه);
        لكل (i = 0; i < r->m_جدول_sizes[r->m_type]; ++i) ټول_syms[p_جدول->m_کوډ_اندازه[i]]++;
        کارول_شوی_syms = 0, ټول = 0; بل_کوډ[0] = بل_کوډ[1] = 0;
        لكل (i = 1; i <= 15; ++i) { کارول_شوی_syms += ټول_syms[i]; بل_کوډ[i + 1] = (ټول = ((ټول + ټول_syms[i]) << 1)); }
        إذا ((65536 != ټول) && (کارول_شوی_syms > 1))
        {
          TINFL_CR_RETURN_FOREVER(35, TINFL_حالت_FAILED);
        }
        لكل (ونه_بل = -1, sym_شاخص = 0; sym_شاخص < r->m_جدول_sizes[r->m_type]; ++sym_شاخص)
        {
          mz_uint rev_کوډ = 0, l, cur_کوډ, کوډ_اندازه_2 = p_جدول->m_کوډ_اندازه[sym_شاخص]; إذا (!کوډ_اندازه_2) استمر;
          cur_کوډ = بل_کوډ[کوډ_اندازه_2]++; لكل (l = کوډ_اندازه_2; l > 0; l--, cur_کوډ >>= 1) rev_کوډ = (rev_کوډ << 1) | (cur_کوډ & 1);
          إذا (کوډ_اندازه_2 <= TINFL_FAST_LOOKUP_بټونه) { mz_int16 k = (mz_int16)((کوډ_اندازه_2 << 9) | sym_شاخص); طالما (rev_کوډ < TINFL_FAST_LOOKUP_اندازه) { p_جدول->m_look_پورته[rev_کوډ] = k; rev_کوډ += (1 << کوډ_اندازه_2); } استمر; }
          إذا (0 == (ونه_cur = p_جدول->m_look_پورته[rev_کوډ & (TINFL_FAST_LOOKUP_اندازه - 1)])) { p_جدول->m_look_پورته[rev_کوډ & (TINFL_FAST_LOOKUP_اندازه - 1)] = (mz_int16)ونه_بل; ونه_cur = ونه_بل; ونه_بل -= 2; }
          rev_کوډ >>= (TINFL_FAST_LOOKUP_بټونه - 1);
          لكل (j = کوډ_اندازه_2; j > (TINFL_FAST_LOOKUP_بټونه + 1); j--)
          {
            ونه_cur -= ((rev_کوډ >>= 1) & 1);
            إذا (!p_جدول->m_ونه[-ونه_cur - 1]) { p_جدول->m_ونه[-ونه_cur - 1] = (mz_int16)ونه_بل; ونه_cur = ونه_بل; ونه_بل -= 2; } وإلا ونه_cur = p_جدول->m_ونه[-ونه_cur - 1];
          }
          ونه_cur -= ((rev_کوډ >>= 1) & 1); p_جدول->m_ونه[-ونه_cur - 1] = (mz_int16)sym_شاخص;
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
            عدد_extra = "\02\03\07"[dist - 16]; TINFL_GET_بټونه(18, s, عدد_extra); s += "\03\03\013"[dist - 16];
            TINFL_MEMSET(r->m_len_codes + counter, (dist == 16) ? r->m_len_codes[counter - 1] : 0, s); counter += s;
          }
          إذا ((r->m_جدول_sizes[0] + r->m_جدول_sizes[1]) != counter)
          {
            TINFL_CR_RETURN_FOREVER(21, TINFL_حالت_FAILED);
          }
          TINFL_MEMCPY(r->m_tables[0].m_کوډ_اندازه, r->m_len_codes, r->m_جدول_sizes[0]); TINFL_MEMCPY(r->m_tables[1].m_کوډ_اندازه, r->m_len_codes + r->m_جدول_sizes[0], r->m_جدول_sizes[1]);
        }
      }
      لكل ( ; ; )
      {
        mz_uint8 *pSrc;
        لكل ( ; ; )
        {
          إذا (((p_دننه_buf_پای_ټکی - p_دننه_buf_cur) < 4) || ((p_بهر_buf_پای_ټکی - p_بهر_buf_cur) < 2))
          {
            TINFL_HUFF_DECODE(23, counter, &r->m_tables[0]);
            إذا (counter >= 256)
              اكسر;
            طالما (p_بهر_buf_cur >= p_بهر_buf_پای_ټکی) { TINFL_CR_RETURN(24, TINFL_حالت_HAS_نور_OUTPUT); }
            *p_بهر_buf_cur++ = (mz_uint8)counter;
          }
          وإلا
          {
            صحيح sym2; mz_uint کوډ_len;
#إذا TINFL_USE_64_بټ_BITBUF
            إذا (عدد_بټونه < 30) { بټ_buf |= (((tinfl_بټ_buf_t)MZ_READ_LE32(p_دننه_buf_cur)) << عدد_بټونه); p_دننه_buf_cur += 4; عدد_بټونه += 32; }
#وإلا
            إذا (عدد_بټونه < 15) { بټ_buf |= (((tinfl_بټ_buf_t)MZ_READ_LE16(p_دننه_buf_cur)) << عدد_بټونه); p_دننه_buf_cur += 2; عدد_بټونه += 16; }
#د_که_پای
            إذا ((sym2 = r->m_tables[0].m_look_پورته[بټ_buf & (TINFL_FAST_LOOKUP_اندازه - 1)]) >= 0)
              کوډ_len = sym2 >> 9;
            وإلا
            {
              کوډ_len = TINFL_FAST_LOOKUP_بټونه; افعل { sym2 = r->m_tables[0].m_ونه[~sym2 + ((بټ_buf >> کوډ_len++) & 1)]; } طالما (sym2 < 0);
            }
            counter = sym2; بټ_buf >>= کوډ_len; عدد_بټونه -= کوډ_len;
            إذا (counter & 256)
              اكسر;

#إذا !TINFL_USE_64_بټ_BITBUF
            إذا (عدد_بټونه < 15) { بټ_buf |= (((tinfl_بټ_buf_t)MZ_READ_LE16(p_دننه_buf_cur)) << عدد_بټونه); p_دننه_buf_cur += 2; عدد_بټونه += 16; }
#د_که_پای
            إذا ((sym2 = r->m_tables[0].m_look_پورته[بټ_buf & (TINFL_FAST_LOOKUP_اندازه - 1)]) >= 0)
              کوډ_len = sym2 >> 9;
            وإلا
            {
              کوډ_len = TINFL_FAST_LOOKUP_بټونه; افعل { sym2 = r->m_tables[0].m_ونه[~sym2 + ((بټ_buf >> کوډ_len++) & 1)]; } طالما (sym2 < 0);
            }
            بټ_buf >>= کوډ_len; عدد_بټونه -= کوډ_len;

            p_بهر_buf_cur[0] = (mz_uint8)counter;
            إذا (sym2 & 256)
            {
              p_بهر_buf_cur++;
              counter = sym2;
              اكسر;
            }
            p_بهر_buf_cur[1] = (mz_uint8)sym2;
            p_بهر_buf_cur += 2;
          }
        }
        إذا ((counter &= 511) == 256) اكسر;

        عدد_extra = s_اوږدتیا_extra[counter - 257]; counter = s_اوږدتیا_بنسټ[counter - 257];
        إذا (عدد_extra) { mz_uint extra_بټونه; TINFL_GET_بټونه(25, extra_بټونه, عدد_extra); counter += extra_بټونه; }

        TINFL_HUFF_DECODE(26, dist, &r->m_tables[1]);
        عدد_extra = s_dist_extra[dist]; dist = s_dist_بنسټ[dist];
        إذا (عدد_extra) { mz_uint extra_بټونه; TINFL_GET_بټونه(27, extra_بټونه, عدد_extra); dist += extra_بټونه; }

        dist_from_بهر_buf_پیل = p_بهر_buf_cur - p_بهر_buf_پیل;
        إذا ((dist > dist_from_بهر_buf_پیل) && (decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF))
        {
          TINFL_CR_RETURN_FOREVER(37, TINFL_حالت_FAILED);
        }

        pSrc = p_بهر_buf_پیل + ((dist_from_بهر_buf_پیل - dist) & بهر_buf_اندازه_ماسک);

        إذا ((MZ_MAX(p_بهر_buf_cur, pSrc) + counter) > p_بهر_buf_پای_ټکی)
        {
          طالما (counter--)
          {
            طالما (p_بهر_buf_cur >= p_بهر_buf_پای_ټکی) { TINFL_CR_RETURN(53, TINFL_حالت_HAS_نور_OUTPUT); }
            *p_بهر_buf_cur++ = p_بهر_buf_پیل[(dist_from_بهر_buf_پیل++ - dist) & بهر_buf_اندازه_ماسک];
          }
          استمر;
        }
#إذا MINIZ_USE_UNALIGNED_LOADS_AND_STORES
        وإلا إذا ((counter >= 9) && (counter <= dist))
        {
          ثابت mz_uint8 *p_Src_پای_ټکی = pSrc + (counter & ~7);
          افعل
          {
            ((mz_uint32 *)p_بهر_buf_cur)[0] = ((ثابت mz_uint32 *)pSrc)[0];
            ((mz_uint32 *)p_بهر_buf_cur)[1] = ((ثابت mz_uint32 *)pSrc)[1];
            p_بهر_buf_cur += 8;
          } طالما ((pSrc += 8) < p_Src_پای_ټکی);
          إذا ((counter &= 7) < 3)
          {
            إذا (counter)
            {
              p_بهر_buf_cur[0] = pSrc[0];
              إذا (counter > 1)
                p_بهر_buf_cur[1] = pSrc[1];
              p_بهر_buf_cur += counter;
            }
            استمر;
          }
        }
#د_که_پای
        افعل
        {
          p_بهر_buf_cur[0] = pSrc[0];
          p_بهر_buf_cur[1] = pSrc[1];
          p_بهر_buf_cur[2] = pSrc[2];
          p_بهر_buf_cur += 3; pSrc += 3;
        } طالما ((صحيح)(counter -= 3) > 2);
        إذا ((صحيح)counter > 0)
        {
          p_بهر_buf_cur[0] = pSrc[0];
          إذا ((صحيح)counter > 1)
            p_بهر_buf_cur[1] = pSrc[1];
          p_بهر_buf_cur += counter;
        }
      }
    }
  } طالما (!(r->m_final & 1));
  إذا (decomp_flags & TINFL_FLAG_PARSE_ZLIB_سرلیک)
  {
    TINFL_SKIP_بټونه(32, عدد_بټونه & 7); لكل (counter = 0; counter < 4; ++counter) { mz_uint s; إذا (عدد_بټونه) TINFL_GET_بټونه(41, s, 8); وإلا TINFL_GET_BYTE(42, s); r->m_z_adler32 = (r->m_z_adler32 << 8) | s; }
  }
  TINFL_CR_RETURN_FOREVER(34, TINFL_حالت_بشپړ);
  TINFL_CR_پای

common_exit:
  r->m_عدد_بټونه = عدد_بټونه; r->m_بټ_buf = بټ_buf; r->m_dist = dist; r->m_counter = counter; r->m_عدد_extra = عدد_extra; r->m_dist_from_بهر_buf_پیل = dist_from_بهر_buf_پیل;
  *p_دننه_buf_اندازه = p_دننه_buf_cur - p_دننه_buf_بل; *p_بهر_buf_اندازه = p_بهر_buf_cur - p_بهر_buf_بل;
  إذا ((decomp_flags & (TINFL_FLAG_PARSE_ZLIB_سرلیک | TINFL_FLAG_COMPUTE_ADLER32)) && (حالت >= 0))
  {
    ثابت mz_uint8 *ptr = p_بهر_buf_بل; size_t buf_len = *p_بهر_buf_اندازه;
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
    r->m_check_adler32 = (s2 << 16) + s1; إذا ((حالت == TINFL_حالت_بشپړ) && (decomp_flags & TINFL_FLAG_PARSE_ZLIB_سرلیک) && (r->m_check_adler32 != r->m_z_adler32)) حالت = TINFL_حالت_ADLER32_MISMATCH;
  }
  أرجع حالت;
}

// Higher level helper functions.
فراغ *tinfl_decompress_mem_منزل_ډېرۍ(ثابت فراغ *pSrc_buf, size_t src_buf_len, size_t *p_بهر_len, صحيح flags)
{
  tinfl_decompressor decomp; فراغ *pBuf = عدم, *pNew_buf; size_t src_buf_ofs = 0, بهر_buf_ظرفیت = 0;
  *p_بهر_len = 0;
  tinfl_init(&decomp);
  لكل ( ; ; )
  {
    size_t src_buf_اندازه = src_buf_len - src_buf_ofs, dst_buf_اندازه = بهر_buf_ظرفیت - *p_بهر_len, new_بهر_buf_ظرفیت;
    tinfl_حالت حالت = tinfl_decompress(&decomp, (ثابت mz_uint8*)pSrc_buf + src_buf_ofs, &src_buf_اندازه, (mz_uint8*)pBuf, pBuf ? (mz_uint8*)pBuf + *p_بهر_len : عدم, &dst_buf_اندازه,
      (flags & ~TINFL_FLAG_HAS_نور_ننوت) | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF);
    إذا ((حالت < 0) || (حالت == TINFL_حالت_NEEDS_نور_ننوت))
    {
      MZ_FREE(pBuf); *p_بهر_len = 0; أرجع عدم;
    }
    src_buf_ofs += src_buf_اندازه;
    *p_بهر_len += dst_buf_اندازه;
    إذا (حالت == TINFL_حالت_بشپړ) اكسر;
    new_بهر_buf_ظرفیت = بهر_buf_ظرفیت * 2; إذا (new_بهر_buf_ظرفیت < 128) new_بهر_buf_ظرفیت = 128;
    pNew_buf = MZ_REALLOC(pBuf, new_بهر_buf_ظرفیت);
    إذا (!pNew_buf)
    {
      MZ_FREE(pBuf); *p_بهر_len = 0; أرجع عدم;
    }
    pBuf = pNew_buf; بهر_buf_ظرفیت = new_بهر_buf_ظرفیت;
  }
  أرجع pBuf;
}

size_t tinfl_decompress_mem_منزل_mem(فراغ *p_بهر_buf, size_t بهر_buf_len, ثابت فراغ *pSrc_buf, size_t src_buf_len, صحيح flags)
{
  tinfl_decompressor decomp; tinfl_حالت حالت; tinfl_init(&decomp);
  حالت = tinfl_decompress(&decomp, (ثابت mz_uint8*)pSrc_buf, &src_buf_len, (mz_uint8*)p_بهر_buf, (mz_uint8*)p_بهر_buf, &بهر_buf_len, (flags & ~TINFL_FLAG_HAS_نور_ننوت) | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF);
  أرجع (حالت != TINFL_حالت_بشپړ) ? TINFL_DECOMPRESS_MEM_منزل_MEM_FAILED : بهر_buf_len;
}

صحيح tinfl_decompress_mem_منزل_callback(ثابت فراغ *p_دننه_buf, size_t *p_دننه_buf_اندازه, tinfl_put_buf_func_ptr pPut_buf_func, فراغ *pPut_buf_user, صحيح flags)
{
  صحيح پایله = 0;
  tinfl_decompressor decomp;
  mz_uint8 *pDict = (mz_uint8*)MZ_MALLOC(TINFL_LZ_DICT_اندازه); size_t دننه_buf_ofs = 0, dict_ofs = 0;
  إذا (!pDict)
    أرجع TINFL_حالت_FAILED;
  memset(pDict,0,TINFL_LZ_DICT_اندازه);
  tinfl_init(&decomp);
  لكل ( ; ; )
  {
    size_t دننه_buf_اندازه = *p_دننه_buf_اندازه - دننه_buf_ofs, dst_buf_اندازه = TINFL_LZ_DICT_اندازه - dict_ofs;
    tinfl_حالت حالت = tinfl_decompress(&decomp, (ثابت mz_uint8*)p_دننه_buf + دننه_buf_ofs, &دننه_buf_اندازه, pDict, pDict + dict_ofs, &dst_buf_اندازه,
      (flags & ~(TINFL_FLAG_HAS_نور_ننوت | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF)));
    دننه_buf_ofs += دننه_buf_اندازه;
    إذا ((dst_buf_اندازه) && (!(*pPut_buf_func)(pDict + dict_ofs, (صحيح)dst_buf_اندازه, pPut_buf_user)))
      اكسر;
    إذا (حالت != TINFL_حالت_HAS_نور_OUTPUT)
    {
      پایله = (حالت == TINFL_حالت_بشپړ);
      اكسر;
    }
    dict_ofs = (dict_ofs + dst_buf_اندازه) & (TINFL_LZ_DICT_اندازه - 1);
  }
  MZ_FREE(pDict);
  *p_دننه_buf_اندازه = دننه_buf_ofs;
  أرجع پایله;
}
#د_که_پای /*#ifndef MINIZ_NO_INFLATE_APIS*/

// ------------------- Low-level Compression (independent from all decompression API's)
#که_نه_تعریف_شوی MINIZ_NO_DEFLATE_APIS

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
تعريفنوع بنية { mz_uint16 m_کلی, m_sym_شاخص; } tdefl_sym_freq;
ساكن tdefl_sym_freq* tdefl_radix_ترتیبول_syms(mz_uint عدد_syms, tdefl_sym_freq* pSyms0, tdefl_sym_freq* pSyms1)
{
  mz_uint32 ټول_passes = 2, pass_ښويدنه, pass, i, hist[256 * 2]; tdefl_sym_freq* pCur_syms = pSyms0, *pNew_syms = pSyms1; MZ_CLEAR_ARR(hist);
  لكل (i = 0; i < عدد_syms; i++) { mz_uint freq = pSyms0[i].m_کلی; hist[freq & 0xFF]++; hist[256 + ((freq >> 8) & 0xFF)]++; }
  طالما ((ټول_passes > 1) && (عدد_syms == hist[(ټول_passes - 1) * 256])) ټول_passes--;
  لكل (pass_ښويدنه = 0, pass = 0; pass < ټول_passes; pass++, pass_ښويدنه += 8)
  {
    ثابت mz_uint32* pHist = &hist[pass << 8];
    mz_uint offsets[256], cur_ofs = 0;
    لكل (i = 0; i < 256; i++) { offsets[i] = cur_ofs; cur_ofs += pHist[i]; }
    لكل (i = 0; i < عدد_syms; i++) pNew_syms[offsets[(pCur_syms[i].m_کلی >> pass_ښويدنه) & 0xFF]++] = pCur_syms[i];
    { tdefl_sym_freq* t = pCur_syms; pCur_syms = pNew_syms; pNew_syms = t; }
  }
  أرجع pCur_syms;
}

// tdefl_calculate_minimum_redundancy() originally written by: Alistair Moffat, alistair@cs.mu.oz.au, Jyrki Katajainen, jyrki@diku.dk, November 1996.
ساكن فراغ tdefl_calculate_minimum_redundancy(tdefl_sym_freq *A, صحيح n)
{
  صحيح ریښه, ونې_پاڼه, بل, avbl, کارول_شوی, dpth;
  إذا (n==0) أرجع; وإلا إذا (n==1) { A[0].m_کلی = 1; أرجع; }
  A[0].m_کلی += A[1].m_کلی; ریښه = 0; ونې_پاڼه = 2;
  لكل (بل=1; بل < n-1; بل++)
  {
    إذا (ونې_پاڼه>=n || A[ریښه].m_کلی<A[ونې_پاڼه].m_کلی) { A[بل].m_کلی = A[ریښه].m_کلی; A[ریښه++].m_کلی = (mz_uint16)بل; } وإلا A[بل].m_کلی = A[ونې_پاڼه++].m_کلی;
    إذا (ونې_پاڼه>=n || (ریښه<بل && A[ریښه].m_کلی<A[ونې_پاڼه].m_کلی)) { A[بل].m_کلی = (mz_uint16)(A[بل].m_کلی + A[ریښه].m_کلی); A[ریښه++].m_کلی = (mz_uint16)بل; } وإلا A[بل].m_کلی = (mz_uint16)(A[بل].m_کلی + A[ونې_پاڼه++].m_کلی);
  }
  A[n-2].m_کلی = 0; لكل (بل=n-3; بل>=0; بل--) A[بل].m_کلی = A[A[بل].m_کلی].m_کلی+1;
  avbl = 1; کارول_شوی = dpth = 0; ریښه = n-2; بل = n-1;
  طالما (avbl>0)
  {
    طالما (ریښه>=0 && (صحيح)A[ریښه].m_کلی==dpth) { کارول_شوی++; ریښه--; }
    طالما (avbl>کارول_شوی) { A[بل--].m_کلی = (mz_uint16)(dpth); avbl--; }
    avbl = 2*کارول_شوی; dpth++; کارول_شوی = 0;
  }
}

// Limits canonical Huffman code table's max code size.
تعداد { TDEFL_MAX_SUPPORTED_HUFF_CODESIZE = 32 };
ساكن فراغ tdefl_huffman_enforce_max_کوډ_اندازه(صحيح *p_عدد_codes, صحيح کوډ_list_len, صحيح max_کوډ_اندازه)
{
  صحيح i; mz_uint32 ټول = 0; إذا (کوډ_list_len <= 1) أرجع;
  لكل (i = max_کوډ_اندازه + 1; i <= TDEFL_MAX_SUPPORTED_HUFF_CODESIZE; i++) p_عدد_codes[max_کوډ_اندازه] += p_عدد_codes[i];
  لكل (i = max_کوډ_اندازه; i > 0; i--) ټول += (((mz_uint32)p_عدد_codes[i]) << (max_کوډ_اندازه - i));
  طالما (ټول != (1UL << max_کوډ_اندازه))
  {
    p_عدد_codes[max_کوډ_اندازه]--;
    لكل (i = max_کوډ_اندازه - 1; i > 0; i--) إذا (p_عدد_codes[i]) { p_عدد_codes[i]--; p_عدد_codes[i + 1] += 2; اكسر; }
    ټول--;
  }
}

ساكن فراغ tdefl_optimize_huffman_جدول(tdefl_compressor *d, صحيح جدول_عدد, صحيح جدول_len, صحيح کوډ_اندازه_حد, صحيح static_جدول)
{
  صحيح i, j, l, عدد_codes[1 + TDEFL_MAX_SUPPORTED_HUFF_CODESIZE]; mz_uint بل_کوډ[TDEFL_MAX_SUPPORTED_HUFF_CODESIZE + 1]; MZ_CLEAR_ARR(عدد_codes);
  إذا (static_جدول)
  {
    لكل (i = 0; i < جدول_len; i++) عدد_codes[d->m_huff_کوډ_sizes[جدول_عدد][i]]++;
  }
  وإلا
  {
    tdefl_sym_freq syms0[TDEFL_MAX_HUFF_SYMBOLS], syms1[TDEFL_MAX_HUFF_SYMBOLS], *pSyms;
    صحيح عدد_کارول_شوی_syms = 0;
    ثابت mz_uint16 *p_Sym_شمېر = &d->m_huff_شمېر[جدول_عدد][0];
    لكل (i = 0; i < جدول_len; i++) إذا (p_Sym_شمېر[i]) { syms0[عدد_کارول_شوی_syms].m_کلی = (mz_uint16)p_Sym_شمېر[i]; syms0[عدد_کارول_شوی_syms++].m_sym_شاخص = (mz_uint16)i; }

    pSyms = tdefl_radix_ترتیبول_syms(عدد_کارول_شوی_syms, syms0, syms1); tdefl_calculate_minimum_redundancy(pSyms, عدد_کارول_شوی_syms);

    لكل (i = 0; i < عدد_کارول_شوی_syms; i++) عدد_codes[pSyms[i].m_کلی]++;

    tdefl_huffman_enforce_max_کوډ_اندازه(عدد_codes, عدد_کارول_شوی_syms, کوډ_اندازه_حد);

    MZ_CLEAR_ARR(d->m_huff_کوډ_sizes[جدول_عدد]); MZ_CLEAR_ARR(d->m_huff_codes[جدول_عدد]);
    لكل (i = 1, j = عدد_کارول_شوی_syms; i <= کوډ_اندازه_حد; i++)
      لكل (l = عدد_codes[i]; l > 0; l--) d->m_huff_کوډ_sizes[جدول_عدد][pSyms[--j].m_sym_شاخص] = (mz_uint8)(i);
  }

  بل_کوډ[1] = 0; لكل (j = 0, i = 2; i <= کوډ_اندازه_حد; i++) بل_کوډ[i] = j = ((j + عدد_codes[i - 1]) << 1);

  لكل (i = 0; i < جدول_len; i++)
  {
    mz_uint rev_کوډ = 0, کوډ, کوډ_اندازه_2; إذا ((کوډ_اندازه_2 = d->m_huff_کوډ_sizes[جدول_عدد][i]) == 0) استمر;
    کوډ = بل_کوډ[کوډ_اندازه_2]++; لكل (l = کوډ_اندازه_2; l > 0; l--, کوډ >>= 1) rev_کوډ = (rev_کوډ << 1) | (کوډ & 1);
    d->m_huff_codes[جدول_عدد][i] = (mz_uint16)rev_کوډ;
  }
}

#تعریف_کړه TDEFL_PUT_بټونه(b, l) افعل { \
  mz_uint بټونه = b; mz_uint len = l; MZ_ASSERT(بټونه <= ((1U << len) - 1U)); \
  d->m_بټ_بفر |= (بټونه << d->m_بټونه_دننه); d->m_بټونه_دننه += len; \
  طالما (d->m_بټونه_دننه >= 8) { \
    إذا (d->m_pOutput_buf < d->m_p_Output_buf_پای_ټکی) \
      *d->m_pOutput_buf++ = (mz_uint8)(d->m_بټ_بفر); \
    d->m_بټ_بفر >>= 8; \
    d->m_بټونه_دننه -= 8; \
  } \
} MZ_MACRO_پای_ټکی

#تعریف_کړه TDEFL_RLE_PREV_کوډ_اندازه() افعل { \
  إذا (rle_repeat_شمېر) { \
    إذا (rle_repeat_شمېر < 3) { \
      d->m_huff_شمېر[2][prev_کوډ_اندازه] = (mz_uint16)(d->m_huff_شمېر[2][prev_کوډ_اندازه] + rle_repeat_شمېر); \
      طالما (rle_repeat_شمېر--) packed_کوډ_sizes[عدد_packed_کوډ_sizes++] = prev_کوډ_اندازه; \
    } وإلا { \
      d->m_huff_شمېر[2][16] = (mz_uint16)(d->m_huff_شمېر[2][16] + 1); packed_کوډ_sizes[عدد_packed_کوډ_sizes++] = 16; packed_کوډ_sizes[عدد_packed_کوډ_sizes++] = (mz_uint8)(rle_repeat_شمېر - 3); \
  } rle_repeat_شمېر = 0; } \
} MZ_MACRO_پای_ټکی

#تعریف_کړه TDEFL_RLE_ZERO_کوډ_اندازه() افعل { \
  إذا (rle_z_شمېر) { \
    إذا (rle_z_شمېر < 3) { \
      d->m_huff_شمېر[2][0] = (mz_uint16)(d->m_huff_شمېر[2][0] + rle_z_شمېر); طالما (rle_z_شمېر--) packed_کوډ_sizes[عدد_packed_کوډ_sizes++] = 0; \
    } وإلا إذا (rle_z_شمېر <= 10) { \
      d->m_huff_شمېر[2][17] = (mz_uint16)(d->m_huff_شمېر[2][17] + 1); packed_کوډ_sizes[عدد_packed_کوډ_sizes++] = 17; packed_کوډ_sizes[عدد_packed_کوډ_sizes++] = (mz_uint8)(rle_z_شمېر - 3); \
    } وإلا { \
      d->m_huff_شمېر[2][18] = (mz_uint16)(d->m_huff_شمېر[2][18] + 1); packed_کوډ_sizes[عدد_packed_کوډ_sizes++] = 18; packed_کوډ_sizes[عدد_packed_کوډ_sizes++] = (mz_uint8)(rle_z_شمېر - 11); \
  } rle_z_شمېر = 0; } \
} MZ_MACRO_پای_ټکی

ساكن mz_uint8 s_tdefl_packed_کوډ_اندازه_syms_swizzle[] = { 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 };

ساكن فراغ tdefl_پیل_dynamic_بلاک(tdefl_compressor *d)
{
  صحيح عدد_lit_codes, عدد_dist_codes, عدد_بټ_lengths; mz_uint i, ټول_کوډ_sizes_منزل_pack, عدد_packed_کوډ_sizes, rle_z_شمېر, rle_repeat_شمېر, packed_کوډ_sizes_شاخص;
  mz_uint8 کوډ_sizes_منزل_pack[TDEFL_MAX_HUFF_SYMBOLS_0 + TDEFL_MAX_HUFF_SYMBOLS_1], packed_کوډ_sizes[TDEFL_MAX_HUFF_SYMBOLS_0 + TDEFL_MAX_HUFF_SYMBOLS_1], prev_کوډ_اندازه = 0xFF;

  d->m_huff_شمېر[0][256] = 1;

  tdefl_optimize_huffman_جدول(d, 0, TDEFL_MAX_HUFF_SYMBOLS_0, 15, MZ_FALSE);
  tdefl_optimize_huffman_جدول(d, 1, TDEFL_MAX_HUFF_SYMBOLS_1, 15, MZ_FALSE);

  لكل (عدد_lit_codes = 286; عدد_lit_codes > 257; عدد_lit_codes--) إذا (d->m_huff_کوډ_sizes[0][عدد_lit_codes - 1]) اكسر;
  لكل (عدد_dist_codes = 30; عدد_dist_codes > 1; عدد_dist_codes--) إذا (d->m_huff_کوډ_sizes[1][عدد_dist_codes - 1]) اكسر;

  حافظه_نقل(کوډ_sizes_منزل_pack, &d->m_huff_کوډ_sizes[0][0], عدد_lit_codes);
  حافظه_نقل(کوډ_sizes_منزل_pack + عدد_lit_codes, &d->m_huff_کوډ_sizes[1][0], عدد_dist_codes);
  ټول_کوډ_sizes_منزل_pack = عدد_lit_codes + عدد_dist_codes; عدد_packed_کوډ_sizes = 0; rle_z_شمېر = 0; rle_repeat_شمېر = 0;

  memset(&d->m_huff_شمېر[2][0], 0, حجم(d->m_huff_شمېر[2][0]) * TDEFL_MAX_HUFF_SYMBOLS_2);
  لكل (i = 0; i < ټول_کوډ_sizes_منزل_pack; i++)
  {
    mz_uint8 کوډ_اندازه_2 = کوډ_sizes_منزل_pack[i];
    إذا (!کوډ_اندازه_2)
    {
      TDEFL_RLE_PREV_کوډ_اندازه();
      إذا (++rle_z_شمېر == 138) { TDEFL_RLE_ZERO_کوډ_اندازه(); }
    }
    وإلا
    {
      TDEFL_RLE_ZERO_کوډ_اندازه();
      إذا (کوډ_اندازه_2 != prev_کوډ_اندازه)
      {
        TDEFL_RLE_PREV_کوډ_اندازه();
        d->m_huff_شمېر[2][کوډ_اندازه_2] = (mz_uint16)(d->m_huff_شمېر[2][کوډ_اندازه_2] + 1); packed_کوډ_sizes[عدد_packed_کوډ_sizes++] = کوډ_اندازه_2;
      }
      وإلا إذا (++rle_repeat_شمېر == 6)
      {
        TDEFL_RLE_PREV_کوډ_اندازه();
      }
    }
    prev_کوډ_اندازه = کوډ_اندازه_2;
  }
  إذا (rle_repeat_شمېر) { TDEFL_RLE_PREV_کوډ_اندازه(); } وإلا { TDEFL_RLE_ZERO_کوډ_اندازه(); }

  tdefl_optimize_huffman_جدول(d, 2, TDEFL_MAX_HUFF_SYMBOLS_2, 7, MZ_FALSE);

  TDEFL_PUT_بټونه(2, 2);

  TDEFL_PUT_بټونه(عدد_lit_codes - 257, 5);
  TDEFL_PUT_بټونه(عدد_dist_codes - 1, 5);

  لكل (عدد_بټ_lengths = 18; عدد_بټ_lengths >= 0; عدد_بټ_lengths--) إذا (d->m_huff_کوډ_sizes[2][s_tdefl_packed_کوډ_اندازه_syms_swizzle[عدد_بټ_lengths]]) اكسر;
  عدد_بټ_lengths = MZ_MAX(4, (عدد_بټ_lengths + 1)); TDEFL_PUT_بټونه(عدد_بټ_lengths - 4, 4);
  لكل (i = 0; (صحيح)i < عدد_بټ_lengths; i++) TDEFL_PUT_بټونه(d->m_huff_کوډ_sizes[2][s_tdefl_packed_کوډ_اندازه_syms_swizzle[i]], 3);

  لكل (packed_کوډ_sizes_شاخص = 0; packed_کوډ_sizes_شاخص < عدد_packed_کوډ_sizes; )
  {
    mz_uint کوډ = packed_کوډ_sizes[packed_کوډ_sizes_شاخص++]; MZ_ASSERT(کوډ < TDEFL_MAX_HUFF_SYMBOLS_2);
    TDEFL_PUT_بټونه(d->m_huff_codes[2][کوډ], d->m_huff_کوډ_sizes[2][کوډ]);
    إذا (کوډ >= 16) TDEFL_PUT_بټونه(packed_کوډ_sizes[packed_کوډ_sizes_شاخص++], "\02\03\07"[کوډ - 16]);
  }
}

ساكن فراغ tdefl_پیل_static_بلاک(tdefl_compressor *d)
{
  mz_uint i;
  mz_uint8 *p = &d->m_huff_کوډ_sizes[0][0];

  لكل (i = 0; i <= 143; ++i) *p++ = 8;
  لكل ( ; i <= 255; ++i) *p++ = 9;
  لكل ( ; i <= 279; ++i) *p++ = 7;
  لكل ( ; i <= 287; ++i) *p++ = 8;

  memset(d->m_huff_کوډ_sizes[1], 5, 32);

  tdefl_optimize_huffman_جدول(d, 0, 288, 15, MZ_TRUE);
  tdefl_optimize_huffman_جدول(d, 1, 32, 15, MZ_TRUE);

  TDEFL_PUT_بټونه(1, 2);
}

ساكن ثابت mz_uint mz_bitmasks[17] = { 0x0000, 0x0001, 0x0003, 0x0007, 0x000F, 0x001F, 0x003F, 0x007F, 0x00FF, 0x01FF, 0x03FF, 0x07FF, 0x0FFF, 0x1FFF, 0x3FFF, 0x7FFF, 0xFFFF };

#إذا MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN && MINIZ_HAS_64_بټ_REGISTERS
ساكن mz_bool tdefl_compress_lz_codes(tdefl_compressor *d)
{
  mz_uint flags;
  mz_uint8 *pLZ_codes;
  mz_uint8 *pOutput_buf = d->m_pOutput_buf;
  mz_uint8 *p_LZ_کوډ_buf_پای_ټکی = d->m_p_LZ_کوډ_buf;
  mz_uint64 بټ_بفر = d->m_بټ_بفر;
  mz_uint بټونه_دننه = d->m_بټونه_دننه;

#تعریف_کړه TDEFL_PUT_بټونه_FAST(b, l) { بټ_بفر |= (((mz_uint64)(b)) << بټونه_دننه); بټونه_دننه += (l); }

  flags = 1;
  لكل (pLZ_codes = d->m_lz_کوډ_buf; pLZ_codes < p_LZ_کوډ_buf_پای_ټکی; flags >>= 1)
  {
    إذا (flags == 1)
      flags = *pLZ_codes++ | 0x100;

    إذا (flags & 1)
    {
      mz_uint s0, s1, n0, n1, sym, عدد_extra_بټونه;
      mz_uint سمون_len = pLZ_codes[0], سمون_dist = *(ثابت mz_uint16 *)(pLZ_codes + 1); pLZ_codes += 3;

      MZ_ASSERT(d->m_huff_کوډ_sizes[0][s_tdefl_len_sym[سمون_len]]);
      TDEFL_PUT_بټونه_FAST(d->m_huff_codes[0][s_tdefl_len_sym[سمون_len]], d->m_huff_کوډ_sizes[0][s_tdefl_len_sym[سمون_len]]);
      TDEFL_PUT_بټونه_FAST(سمون_len & mz_bitmasks[s_tdefl_len_extra[سمون_len]], s_tdefl_len_extra[سمون_len]);

      // This sequence coaxes MSVC into using cmov's vs. jmp's.
      s0 = s_tdefl_small_dist_sym[سمون_dist & 511];
      n0 = s_tdefl_small_dist_extra[سمون_dist & 511];
      s1 = s_tdefl_large_dist_sym[سمون_dist >> 8];
      n1 = s_tdefl_large_dist_extra[سمون_dist >> 8];
      sym = (سمون_dist < 512) ? s0 : s1;
      عدد_extra_بټونه = (سمون_dist < 512) ? n0 : n1;

      MZ_ASSERT(d->m_huff_کوډ_sizes[1][sym]);
      TDEFL_PUT_بټونه_FAST(d->m_huff_codes[1][sym], d->m_huff_کوډ_sizes[1][sym]);
      TDEFL_PUT_بټونه_FAST(سمون_dist & mz_bitmasks[عدد_extra_بټونه], عدد_extra_بټونه);
    }
    وإلا
    {
      mz_uint lit = *pLZ_codes++;
      MZ_ASSERT(d->m_huff_کوډ_sizes[0][lit]);
      TDEFL_PUT_بټونه_FAST(d->m_huff_codes[0][lit], d->m_huff_کوډ_sizes[0][lit]);

      إذا (((flags & 2) == 0) && (pLZ_codes < p_LZ_کوډ_buf_پای_ټکی))
      {
        flags >>= 1;
        lit = *pLZ_codes++;
        MZ_ASSERT(d->m_huff_کوډ_sizes[0][lit]);
        TDEFL_PUT_بټونه_FAST(d->m_huff_codes[0][lit], d->m_huff_کوډ_sizes[0][lit]);

        إذا (((flags & 2) == 0) && (pLZ_codes < p_LZ_کوډ_buf_پای_ټکی))
        {
          flags >>= 1;
          lit = *pLZ_codes++;
          MZ_ASSERT(d->m_huff_کوډ_sizes[0][lit]);
          TDEFL_PUT_بټونه_FAST(d->m_huff_codes[0][lit], d->m_huff_کوډ_sizes[0][lit]);
        }
      }
    }

    إذا (pOutput_buf >= d->m_p_Output_buf_پای_ټکی)
      أرجع MZ_FALSE;

    *(mz_uint64*)pOutput_buf = بټ_بفر;
    pOutput_buf += (بټونه_دننه >> 3);
    بټ_بفر >>= (بټونه_دننه & ~7);
    بټونه_دننه &= 7;
  }

#تعریف_لغوه TDEFL_PUT_بټونه_FAST

  d->m_pOutput_buf = pOutput_buf;
  d->m_بټونه_دننه = 0;
  d->m_بټ_بفر = 0;

  طالما (بټونه_دننه)
  {
    mz_uint32 n = MZ_MIN(بټونه_دننه, 16);
    TDEFL_PUT_بټونه((mz_uint)بټ_بفر & mz_bitmasks[n], n);
    بټ_بفر >>= n;
    بټونه_دننه -= n;
  }

  TDEFL_PUT_بټونه(d->m_huff_codes[0][256], d->m_huff_کوډ_sizes[0][256]);

  أرجع (d->m_pOutput_buf < d->m_p_Output_buf_پای_ټکی);
}
#وإلا
ساكن mz_bool tdefl_compress_lz_codes(tdefl_compressor *d)
{
  mz_uint flags;
  mz_uint8 *pLZ_codes;

  flags = 1;
  لكل (pLZ_codes = d->m_lz_کوډ_buf; pLZ_codes < d->m_p_LZ_کوډ_buf; flags >>= 1)
  {
    إذا (flags == 1)
      flags = *pLZ_codes++ | 0x100;
    إذا (flags & 1)
    {
      mz_uint sym, عدد_extra_بټونه;
      mz_uint سمون_len = pLZ_codes[0], سمون_dist = (pLZ_codes[1] | (pLZ_codes[2] << 8)); pLZ_codes += 3;

      MZ_ASSERT(d->m_huff_کوډ_sizes[0][s_tdefl_len_sym[سمون_len]]);
      TDEFL_PUT_بټونه(d->m_huff_codes[0][s_tdefl_len_sym[سمون_len]], d->m_huff_کوډ_sizes[0][s_tdefl_len_sym[سمون_len]]);
      TDEFL_PUT_بټونه(سمون_len & mz_bitmasks[s_tdefl_len_extra[سمون_len]], s_tdefl_len_extra[سمون_len]);

      إذا (سمون_dist < 512)
      {
        sym = s_tdefl_small_dist_sym[سمون_dist]; عدد_extra_بټونه = s_tdefl_small_dist_extra[سمون_dist];
      }
      وإلا
      {
        sym = s_tdefl_large_dist_sym[سمون_dist >> 8]; عدد_extra_بټونه = s_tdefl_large_dist_extra[سمون_dist >> 8];
      }
      MZ_ASSERT(d->m_huff_کوډ_sizes[1][sym]);
      TDEFL_PUT_بټونه(d->m_huff_codes[1][sym], d->m_huff_کوډ_sizes[1][sym]);
      TDEFL_PUT_بټونه(سمون_dist & mz_bitmasks[عدد_extra_بټونه], عدد_extra_بټونه);
    }
    وإلا
    {
      mz_uint lit = *pLZ_codes++;
      MZ_ASSERT(d->m_huff_کوډ_sizes[0][lit]);
      TDEFL_PUT_بټونه(d->m_huff_codes[0][lit], d->m_huff_کوډ_sizes[0][lit]);
    }
  }

  TDEFL_PUT_بټونه(d->m_huff_codes[0][256], d->m_huff_کوډ_sizes[0][256]);

  أرجع (d->m_pOutput_buf < d->m_p_Output_buf_پای_ټکی);
}
#د_که_پای // MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN && MINIZ_HAS_64BIT_REGISTERS

ساكن mz_bool tdefl_compress_بلاک(tdefl_compressor *d, mz_bool static_بلاک)
{
  إذا (static_بلاک)
    tdefl_پیل_static_بلاک(d);
  وإلا
    tdefl_پیل_dynamic_بلاک(d);
  أرجع tdefl_compress_lz_codes(d);
}

ساكن صحيح tdefl_flush_بلاک(tdefl_compressor *d, صحيح flush)
{
  mz_uint saved_بټ_buf, saved_بټونه_دننه;
  mz_uint8 *pSaved_output_buf;
  mz_bool comp_بلاک_succeeded = MZ_FALSE;
  صحيح n, use_raw_بلاک = ((d->m_flags & TDEFL_FORCE_ALL_RAW_بلاکونه) != 0) && (d->m_lookahead_pos - d->m_lz_کوډ_buf_dict_pos) <= d->m_dict_اندازه;
  mz_uint8 *p_Output_buf_پیل = ((d->m_pPut_buf_func == عدم) && ((*d->m_p_بهر_buf_اندازه - d->m_بهر_buf_ofs) >= TDEFL_بهر_BUF_اندازه)) ? ((mz_uint8 *)d->m_p_بهر_buf + d->m_بهر_buf_ofs) : d->m_output_buf;

  d->m_pOutput_buf = p_Output_buf_پیل;
  d->m_p_Output_buf_پای_ټکی = d->m_pOutput_buf + TDEFL_بهر_BUF_اندازه - 16;

  MZ_ASSERT(!d->m_output_flush_پاتې_شوی);
  d->m_output_flush_ofs = 0;
  d->m_output_flush_پاتې_شوی = 0;

  *d->m_pLZ_flags = (mz_uint8)(*d->m_pLZ_flags >> d->m_عدد_flags_کیڼ);
  d->m_p_LZ_کوډ_buf -= (d->m_عدد_flags_کیڼ == 8);

  إذا ((d->m_flags & TDEFL_WRITE_ZLIB_سرلیک) && (!d->m_بلاک_شاخص))
  {
    TDEFL_PUT_بټونه(0x78, 8); TDEFL_PUT_بټونه(0x01, 8);
  }

  TDEFL_PUT_بټونه(flush == TDEFL_پای, 1);

  pSaved_output_buf = d->m_pOutput_buf; saved_بټ_buf = d->m_بټ_بفر; saved_بټونه_دننه = d->m_بټونه_دننه;

  إذا (!use_raw_بلاک)
    comp_بلاک_succeeded = tdefl_compress_بلاک(d, (d->m_flags & TDEFL_FORCE_ALL_STATIC_بلاکونه) || (d->m_ټول_lz_بایټونه < 48));

  // If the block gets expanded, forget the current contents of the output buffer and send a raw block instead.
  إذا ( ((use_raw_بلاک) || ((d->m_ټول_lz_بایټونه) && ((d->m_pOutput_buf - pSaved_output_buf + 1U) >= d->m_ټول_lz_بایټونه))) &&
       ((d->m_lookahead_pos - d->m_lz_کوډ_buf_dict_pos) <= d->m_dict_اندازه) )
  {
    mz_uint i; d->m_pOutput_buf = pSaved_output_buf; d->m_بټ_بفر = saved_بټ_buf; d->m_بټونه_دننه = saved_بټونه_دننه;
    TDEFL_PUT_بټونه(0, 2);
    إذا (d->m_بټونه_دننه) { TDEFL_PUT_بټونه(0, 8 - d->m_بټونه_دننه); }
    لكل (i = 2; i; --i, d->m_ټول_lz_بایټونه ^= 0xFFFF)
    {
      TDEFL_PUT_بټونه(d->m_ټول_lz_بایټونه & 0xFFFF, 16);
    }
    لكل (i = 0; i < d->m_ټول_lz_بایټونه; ++i)
    {
      TDEFL_PUT_بټونه(d->m_dict[(d->m_lz_کوډ_buf_dict_pos + i) & TDEFL_LZ_DICT_اندازه_ماسک], 8);
    }
  }
  // Check for the extremely unlikely (if not impossible) case of the compressed block not fitting into the output buffer when using dynamic codes.
  وإلا إذا (!comp_بلاک_succeeded)
  {
    d->m_pOutput_buf = pSaved_output_buf; d->m_بټ_بفر = saved_بټ_buf; d->m_بټونه_دننه = saved_بټونه_دننه;
    tdefl_compress_بلاک(d, MZ_TRUE);
  }

  إذا (flush)
  {
    إذا (flush == TDEFL_پای)
    {
      إذا (d->m_بټونه_دننه) { TDEFL_PUT_بټونه(0, 8 - d->m_بټونه_دننه); }
      إذا (d->m_flags & TDEFL_WRITE_ZLIB_سرلیک) { mz_uint i, a = d->m_adler32; لكل (i = 0; i < 4; i++) { TDEFL_PUT_بټونه((a >> 24) & 0xFF, 8); a <<= 8; } }
    }
    وإلا
    {
      mz_uint i, z = 0; TDEFL_PUT_بټونه(0, 3); إذا (d->m_بټونه_دننه) { TDEFL_PUT_بټونه(0, 8 - d->m_بټونه_دننه); } لكل (i = 2; i; --i, z ^= 0xFFFF) { TDEFL_PUT_بټونه(z & 0xFFFF, 16); }
    }
  }

  MZ_ASSERT(d->m_pOutput_buf < d->m_p_Output_buf_پای_ټکی);

  memset(&d->m_huff_شمېر[0][0], 0, حجم(d->m_huff_شمېر[0][0]) * TDEFL_MAX_HUFF_SYMBOLS_0);
  memset(&d->m_huff_شمېر[1][0], 0, حجم(d->m_huff_شمېر[1][0]) * TDEFL_MAX_HUFF_SYMBOLS_1);

  d->m_p_LZ_کوډ_buf = d->m_lz_کوډ_buf + 1; d->m_pLZ_flags = d->m_lz_کوډ_buf; d->m_عدد_flags_کیڼ = 8; d->m_lz_کوډ_buf_dict_pos += d->m_ټول_lz_بایټونه; d->m_ټول_lz_بایټونه = 0; d->m_بلاک_شاخص++;

  إذا ((n = (صحيح)(d->m_pOutput_buf - p_Output_buf_پیل)) != 0)
  {
    إذا (d->m_pPut_buf_func)
    {
      *d->m_p_دننه_buf_اندازه = d->m_pSrc - (ثابت mz_uint8 *)d->m_p_دننه_buf;
      إذا (!(*d->m_pPut_buf_func)(d->m_output_buf, n, d->m_pPut_buf_user))
        أرجع (d->m_prev_return_حالت = TDEFL_حالت_PUT_BUF_FAILED);
    }
    وإلا إذا (p_Output_buf_پیل == d->m_output_buf)
    {
      صحيح بایټونه_منزل_copy = (صحيح)MZ_MIN((size_t)n, (size_t)(*d->m_p_بهر_buf_اندازه - d->m_بهر_buf_ofs));
      حافظه_نقل((mz_uint8 *)d->m_p_بهر_buf + d->m_بهر_buf_ofs, d->m_output_buf, بایټونه_منزل_copy);
      d->m_بهر_buf_ofs += بایټونه_منزل_copy;
      إذا ((n -= بایټونه_منزل_copy) != 0)
      {
        d->m_output_flush_ofs = بایټونه_منزل_copy;
        d->m_output_flush_پاتې_شوی = n;
      }
    }
    وإلا
    {
      d->m_بهر_buf_ofs += n;
    }
  }

  أرجع d->m_output_flush_پاتې_شوی;
}

#إذا MINIZ_USE_UNALIGNED_LOADS_AND_STORES
#تعریف_کړه TDEFL_READ_UNALIGNED_کلمه(p) *(ثابت mz_uint16*)(p)
ساكن MZ_FORCEINLINE فراغ tdefl_پیدا_کړه_سمون(tdefl_compressor *d, mz_uint lookahead_pos, mz_uint max_dist, mz_uint max_سمون_len, mz_uint *p_سمون_dist, mz_uint *p_سمون_len)
{
  mz_uint dist, pos = lookahead_pos & TDEFL_LZ_DICT_اندازه_ماسک, سمون_len = *p_سمون_len, probe_pos = pos, بل_probe_pos, probe_len;
  mz_uint عدد_probes_کیڼ = d->m_max_probes[سمون_len >= 32];
  ثابت mz_uint16 *s = (ثابت mz_uint16*)(d->m_dict + pos), *p, *q;
  mz_uint16 c01 = TDEFL_READ_UNALIGNED_کلمه(&d->m_dict[pos + سمون_len - 1]), s01 = TDEFL_READ_UNALIGNED_کلمه(s);
  MZ_ASSERT(max_سمون_len <= TDEFL_MAX_سمون_LEN); إذا (max_سمون_len <= سمون_len) أرجع;
  لكل ( ; ; )
  {
    لكل ( ; ; )
    {
      إذا (--عدد_probes_کیڼ == 0) أرجع;
      #تعریف_کړه TDEFL_PROBE \
        بل_probe_pos = d->m_بل[probe_pos]; \
        إذا ((!بل_probe_pos) || ((dist = (mz_uint16)(lookahead_pos - بل_probe_pos)) > max_dist)) أرجع; \
        probe_pos = بل_probe_pos & TDEFL_LZ_DICT_اندازه_ماسک; \
        إذا (TDEFL_READ_UNALIGNED_کلمه(&d->m_dict[probe_pos + سمون_len - 1]) == c01) اكسر;
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
      *p_سمون_dist = dist; *p_سمون_len = MZ_MIN(max_سمون_len, TDEFL_MAX_سمون_LEN); اكسر;
    }
    وإلا إذا ((probe_len = ((mz_uint)(p - s) * 2) + (mz_uint)(*(ثابت mz_uint8*)p == *(ثابت mz_uint8*)q)) > سمون_len)
    {
      *p_سمون_dist = dist; إذا ((*p_سمون_len = سمون_len = MZ_MIN(max_سمون_len, probe_len)) == max_سمون_len) اكسر;
      c01 = TDEFL_READ_UNALIGNED_کلمه(&d->m_dict[pos + سمون_len - 1]);
    }
  }
}
#وإلا
ساكن MZ_FORCEINLINE فراغ tdefl_پیدا_کړه_سمون(tdefl_compressor *d, mz_uint lookahead_pos, mz_uint max_dist, mz_uint max_سمون_len, mz_uint *p_سمون_dist, mz_uint *p_سمون_len)
{
  mz_uint dist, pos = lookahead_pos & TDEFL_LZ_DICT_اندازه_ماسک, سمون_len = *p_سمون_len, probe_pos = pos, بل_probe_pos, probe_len;
  mz_uint عدد_probes_کیڼ = d->m_max_probes[سمون_len >= 32];
  ثابت mz_uint8 *s = d->m_dict + pos, *p, *q;
  mz_uint8 c0 = d->m_dict[pos + سمون_len], c1 = d->m_dict[pos + سمون_len - 1];
  MZ_ASSERT(max_سمون_len <= TDEFL_MAX_سمون_LEN); إذا (max_سمون_len <= سمون_len) أرجع;
  لكل ( ; ; )
  {
    لكل ( ; ; )
    {
      إذا (--عدد_probes_کیڼ == 0) أرجع;
      #تعریف_کړه TDEFL_PROBE \
        بل_probe_pos = d->m_بل[probe_pos]; \
        إذا ((!بل_probe_pos) || ((dist = (mz_uint16)(lookahead_pos - بل_probe_pos)) > max_dist)) أرجع; \
        probe_pos = بل_probe_pos & TDEFL_LZ_DICT_اندازه_ماسک; \
        إذا ((d->m_dict[probe_pos + سمون_len] == c0) && (d->m_dict[probe_pos + سمون_len - 1] == c1)) اكسر;
      TDEFL_PROBE
      TDEFL_PROBE
      TDEFL_PROBE
    }
    إذا (!dist) اكسر;
    p = s; q = d->m_dict + probe_pos;
    لكل (probe_len = 0; probe_len < max_سمون_len; probe_len++) {
        إذا (*p++ != *q++) اكسر;
    }
    إذا (probe_len > سمون_len)
    {
      *p_سمون_dist = dist;
      إذا ((*p_سمون_len = سمون_len = probe_len) == max_سمون_len) أرجع;
      c0 = d->m_dict[pos + سمون_len]; c1 = d->m_dict[pos + سمون_len - 1];
    }
  }
}
#د_که_پای // #if MINIZ_USE_UNALIGNED_LOADS_AND_STORES

#إذا MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
ساكن mz_bool tdefl_compress_fast(tdefl_compressor *d)
{
  // Faster, minimally featured LZRW1-style match+parse loop with better register utilization. Intended for applications where raw throughput is valued more highly than ratio.
  mz_uint lookahead_pos = d->m_lookahead_pos, lookahead_اندازه = d->m_lookahead_اندازه, dict_اندازه = d->m_dict_اندازه, ټول_lz_بایټونه = d->m_ټول_lz_بایټونه, عدد_flags_کیڼ = d->m_عدد_flags_کیڼ;
  mz_uint8 *p_LZ_کوډ_buf = d->m_p_LZ_کوډ_buf, *pLZ_flags = d->m_pLZ_flags;
  mz_uint cur_pos = lookahead_pos & TDEFL_LZ_DICT_اندازه_ماسک;

  طالما ((d->m_src_buf_کیڼ) || ((d->m_flush) && (lookahead_اندازه)))
  {
    ثابت mz_uint TDEFL_COMP_FAST_LOOKAHEAD_اندازه = 4096;
    mz_uint dst_pos = (lookahead_pos + lookahead_اندازه) & TDEFL_LZ_DICT_اندازه_ماسک;
    mz_uint عدد_بایټونه_منزل_process = (mz_uint)MZ_MIN(d->m_src_buf_کیڼ, TDEFL_COMP_FAST_LOOKAHEAD_اندازه - lookahead_اندازه);
    d->m_src_buf_کیڼ -= عدد_بایټونه_منزل_process;
    lookahead_اندازه += عدد_بایټونه_منزل_process;

    طالما (عدد_بایټونه_منزل_process)
    {
      mz_uint32 n = MZ_MIN(TDEFL_LZ_DICT_اندازه - dst_pos, عدد_بایټونه_منزل_process);
      حافظه_نقل(d->m_dict + dst_pos, d->m_pSrc, n);
      إذا (dst_pos < (TDEFL_MAX_سمون_LEN - 1))
        حافظه_نقل(d->m_dict + TDEFL_LZ_DICT_اندازه + dst_pos, d->m_pSrc, MZ_MIN(n, (TDEFL_MAX_سمون_LEN - 1) - dst_pos));
      d->m_pSrc += n;
      dst_pos = (dst_pos + n) & TDEFL_LZ_DICT_اندازه_ماسک;
      عدد_بایټونه_منزل_process -= n;
    }

    dict_اندازه = MZ_MIN(TDEFL_LZ_DICT_اندازه - lookahead_اندازه, dict_اندازه);
    إذا ((!d->m_flush) && (lookahead_اندازه < TDEFL_COMP_FAST_LOOKAHEAD_اندازه)) اكسر;

    طالما (lookahead_اندازه >= 4)
    {
      mz_uint cur_سمون_dist, cur_سمون_len = 1;
      mz_uint8 *pCur_dict = d->m_dict + cur_pos;
      mz_uint لومړی_trigram = (*(ثابت mz_uint32 *)pCur_dict) & 0xFFFFFF;
      mz_uint hash = (لومړی_trigram ^ (لومړی_trigram >> (24 - (TDEFL_LZ_HASH_بټونه - 8)))) & TDEFL_LEVEL1_HASH_اندازه_ماسک;
      mz_uint probe_pos = d->m_hash[hash];
      d->m_hash[hash] = (mz_uint16)lookahead_pos;

      إذا (((cur_سمون_dist = (mz_uint16)(lookahead_pos - probe_pos)) <= dict_اندازه) && ((*(ثابت mz_uint32 *)(d->m_dict + (probe_pos &= TDEFL_LZ_DICT_اندازه_ماسک)) & 0xFFFFFF) == لومړی_trigram))
      {
        ثابت mz_uint16 *p = (ثابت mz_uint16 *)pCur_dict;
        ثابت mz_uint16 *q = (ثابت mz_uint16 *)(d->m_dict + probe_pos);
        mz_uint32 probe_len = 32;
        افعل { } طالما ( (TDEFL_READ_UNALIGNED_کلمه(++p) == TDEFL_READ_UNALIGNED_کلمه(++q)) && (TDEFL_READ_UNALIGNED_کلمه(++p) == TDEFL_READ_UNALIGNED_کلمه(++q)) &&
          (TDEFL_READ_UNALIGNED_کلمه(++p) == TDEFL_READ_UNALIGNED_کلمه(++q)) && (TDEFL_READ_UNALIGNED_کلمه(++p) == TDEFL_READ_UNALIGNED_کلمه(++q)) && (--probe_len > 0) );
        cur_سمون_len = ((mz_uint)(p - (ثابت mz_uint16 *)pCur_dict) * 2) + (mz_uint)(*(ثابت mz_uint8 *)p == *(ثابت mz_uint8 *)q);
        إذا (!probe_len)
          cur_سمون_len = cur_سمون_dist ? TDEFL_MAX_سمون_LEN : 0;

        إذا ((cur_سمون_len < TDEFL_MIN_سمون_LEN) || ((cur_سمون_len == TDEFL_MIN_سمون_LEN) && (cur_سمون_dist >= 8U*1024U)))
        {
          cur_سمون_len = 1;
          *p_LZ_کوډ_buf++ = (mz_uint8)لومړی_trigram;
          *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
          d->m_huff_شمېر[0][(mz_uint8)لومړی_trigram]++;
        }
        وإلا
        {
          mz_uint32 s0, s1;
          cur_سمون_len = MZ_MIN(cur_سمون_len, lookahead_اندازه);

          MZ_ASSERT((cur_سمون_len >= TDEFL_MIN_سمون_LEN) && (cur_سمون_dist >= 1) && (cur_سمون_dist <= TDEFL_LZ_DICT_اندازه));

          cur_سمون_dist--;

          p_LZ_کوډ_buf[0] = (mz_uint8)(cur_سمون_len - TDEFL_MIN_سمون_LEN);
          *(mz_uint16 *)(&p_LZ_کوډ_buf[1]) = (mz_uint16)cur_سمون_dist;
          p_LZ_کوډ_buf += 3;
          *pLZ_flags = (mz_uint8)((*pLZ_flags >> 1) | 0x80);

          s0 = s_tdefl_small_dist_sym[cur_سمون_dist & 511];
          s1 = s_tdefl_large_dist_sym[cur_سمون_dist >> 8];
          d->m_huff_شمېر[1][(cur_سمون_dist < 512) ? s0 : s1]++;

          d->m_huff_شمېر[0][s_tdefl_len_sym[cur_سمون_len - TDEFL_MIN_سمون_LEN]]++;
        }
      }
      وإلا
      {
        *p_LZ_کوډ_buf++ = (mz_uint8)لومړی_trigram;
        *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
        d->m_huff_شمېر[0][(mz_uint8)لومړی_trigram]++;
      }

      إذا (--عدد_flags_کیڼ == 0) { عدد_flags_کیڼ = 8; pLZ_flags = p_LZ_کوډ_buf++; }

      ټول_lz_بایټونه += cur_سمون_len;
      lookahead_pos += cur_سمون_len;
      dict_اندازه = MZ_MIN(dict_اندازه + cur_سمون_len, TDEFL_LZ_DICT_اندازه);
      cur_pos = (cur_pos + cur_سمون_len) & TDEFL_LZ_DICT_اندازه_ماسک;
      MZ_ASSERT(lookahead_اندازه >= cur_سمون_len);
      lookahead_اندازه -= cur_سمون_len;

      إذا (p_LZ_کوډ_buf > &d->m_lz_کوډ_buf[TDEFL_LZ_کوډ_BUF_اندازه - 8])
      {
        صحيح n;
        d->m_lookahead_pos = lookahead_pos; d->m_lookahead_اندازه = lookahead_اندازه; d->m_dict_اندازه = dict_اندازه;
        d->m_ټول_lz_بایټونه = ټول_lz_بایټونه; d->m_p_LZ_کوډ_buf = p_LZ_کوډ_buf; d->m_pLZ_flags = pLZ_flags; d->m_عدد_flags_کیڼ = عدد_flags_کیڼ;
        إذا ((n = tdefl_flush_بلاک(d, 0)) != 0)
          أرجع (n < 0) ? MZ_FALSE : MZ_TRUE;
        ټول_lz_بایټونه = d->m_ټول_lz_بایټونه; p_LZ_کوډ_buf = d->m_p_LZ_کوډ_buf; pLZ_flags = d->m_pLZ_flags; عدد_flags_کیڼ = d->m_عدد_flags_کیڼ;
      }
    }

    طالما (lookahead_اندازه)
    {
      mz_uint8 lit = d->m_dict[cur_pos];

      ټول_lz_بایټونه++;
      *p_LZ_کوډ_buf++ = lit;
      *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
      إذا (--عدد_flags_کیڼ == 0) { عدد_flags_کیڼ = 8; pLZ_flags = p_LZ_کوډ_buf++; }

      d->m_huff_شمېر[0][lit]++;

      lookahead_pos++;
      dict_اندازه = MZ_MIN(dict_اندازه + 1, TDEFL_LZ_DICT_اندازه);
      cur_pos = (cur_pos + 1) & TDEFL_LZ_DICT_اندازه_ماسک;
      lookahead_اندازه--;

      إذا (p_LZ_کوډ_buf > &d->m_lz_کوډ_buf[TDEFL_LZ_کوډ_BUF_اندازه - 8])
      {
        صحيح n;
        d->m_lookahead_pos = lookahead_pos; d->m_lookahead_اندازه = lookahead_اندازه; d->m_dict_اندازه = dict_اندازه;
        d->m_ټول_lz_بایټونه = ټول_lz_بایټونه; d->m_p_LZ_کوډ_buf = p_LZ_کوډ_buf; d->m_pLZ_flags = pLZ_flags; d->m_عدد_flags_کیڼ = عدد_flags_کیڼ;
        إذا ((n = tdefl_flush_بلاک(d, 0)) != 0)
          أرجع (n < 0) ? MZ_FALSE : MZ_TRUE;
        ټول_lz_بایټونه = d->m_ټول_lz_بایټونه; p_LZ_کوډ_buf = d->m_p_LZ_کوډ_buf; pLZ_flags = d->m_pLZ_flags; عدد_flags_کیڼ = d->m_عدد_flags_کیڼ;
      }
    }
  }

  d->m_lookahead_pos = lookahead_pos; d->m_lookahead_اندازه = lookahead_اندازه; d->m_dict_اندازه = dict_اندازه;
  d->m_ټول_lz_بایټونه = ټول_lz_بایټونه; d->m_p_LZ_کوډ_buf = p_LZ_کوډ_buf; d->m_pLZ_flags = pLZ_flags; d->m_عدد_flags_کیڼ = عدد_flags_کیڼ;
  أرجع MZ_TRUE;
}
#د_که_پای // MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN

ساكن MZ_FORCEINLINE فراغ tdefl_ریکارډ_literal(tdefl_compressor *d, mz_uint8 lit)
{
  d->m_ټول_lz_بایټونه++;
  *d->m_p_LZ_کوډ_buf++ = lit;
  *d->m_pLZ_flags = (mz_uint8)(*d->m_pLZ_flags >> 1); إذا (--d->m_عدد_flags_کیڼ == 0) { d->m_عدد_flags_کیڼ = 8; d->m_pLZ_flags = d->m_p_LZ_کوډ_buf++; }
  d->m_huff_شمېر[0][lit]++;
}

ساكن MZ_FORCEINLINE فراغ tdefl_ریکارډ_سمون(tdefl_compressor *d, mz_uint سمون_len, mz_uint سمون_dist)
{
  mz_uint32 s0, s1;

  MZ_ASSERT((سمون_len >= TDEFL_MIN_سمون_LEN) && (سمون_dist >= 1) && (سمون_dist <= TDEFL_LZ_DICT_اندازه));

  d->m_ټول_lz_بایټونه += سمون_len;

  d->m_p_LZ_کوډ_buf[0] = (mz_uint8)(سمون_len - TDEFL_MIN_سمون_LEN);

  سمون_dist -= 1;
  d->m_p_LZ_کوډ_buf[1] = (mz_uint8)(سمون_dist & 0xFF);
  d->m_p_LZ_کوډ_buf[2] = (mz_uint8)(سمون_dist >> 8); d->m_p_LZ_کوډ_buf += 3;

  *d->m_pLZ_flags = (mz_uint8)((*d->m_pLZ_flags >> 1) | 0x80); إذا (--d->m_عدد_flags_کیڼ == 0) { d->m_عدد_flags_کیڼ = 8; d->m_pLZ_flags = d->m_p_LZ_کوډ_buf++; }

  s0 = s_tdefl_small_dist_sym[سمون_dist & 511]; s1 = s_tdefl_large_dist_sym[(سمون_dist >> 8) & 127];
  d->m_huff_شمېر[1][(سمون_dist < 512) ? s0 : s1]++;

  إذا (سمون_len >= TDEFL_MIN_سمون_LEN) d->m_huff_شمېر[0][s_tdefl_len_sym[سمون_len - TDEFL_MIN_سمون_LEN]]++;
}

ساكن mz_bool tdefl_compress_نورمال(tdefl_compressor *d)
{
  ثابت mz_uint8 *pSrc = d->m_pSrc; size_t src_buf_کیڼ = d->m_src_buf_کیڼ;
  tdefl_flush flush = d->m_flush;

  طالما ((src_buf_کیڼ) || ((flush) && (d->m_lookahead_اندازه)))
  {
    mz_uint len_منزل_move, cur_سمون_dist, cur_سمون_len, cur_pos;
    // Update dictionary and hash chains. Keeps the lookahead size equal to TDEFL_MAX_MATCH_LEN.
    إذا ((d->m_lookahead_اندازه + d->m_dict_اندازه) >= (TDEFL_MIN_سمون_LEN - 1))
    {
      mz_uint dst_pos = (d->m_lookahead_pos + d->m_lookahead_اندازه) & TDEFL_LZ_DICT_اندازه_ماسک, ins_pos = d->m_lookahead_pos + d->m_lookahead_اندازه - 2;
      mz_uint hash = (d->m_dict[ins_pos & TDEFL_LZ_DICT_اندازه_ماسک] << TDEFL_LZ_HASH_ښويدنه) ^ d->m_dict[(ins_pos + 1) & TDEFL_LZ_DICT_اندازه_ماسک];
      mz_uint عدد_بایټونه_منزل_process = (mz_uint)MZ_MIN(src_buf_کیڼ, TDEFL_MAX_سمون_LEN - d->m_lookahead_اندازه);
      ثابت mz_uint8 *p_Src_پای_ټکی = pSrc ? pSrc + عدد_بایټونه_منزل_process : عدم;
      src_buf_کیڼ -= عدد_بایټونه_منزل_process;
      d->m_lookahead_اندازه += عدد_بایټونه_منزل_process;
      طالما (pSrc != p_Src_پای_ټکی)
      {
        mz_uint8 c = *pSrc++; d->m_dict[dst_pos] = c; إذا (dst_pos < (TDEFL_MAX_سمون_LEN - 1)) d->m_dict[TDEFL_LZ_DICT_اندازه + dst_pos] = c;
        hash = ((hash << TDEFL_LZ_HASH_ښويدنه) ^ c) & (TDEFL_LZ_HASH_اندازه - 1);
        d->m_بل[ins_pos & TDEFL_LZ_DICT_اندازه_ماسک] = d->m_hash[hash]; d->m_hash[hash] = (mz_uint16)(ins_pos);
        dst_pos = (dst_pos + 1) & TDEFL_LZ_DICT_اندازه_ماسک; ins_pos++;
      }
    }
    وإلا
    {
      طالما ((src_buf_کیڼ) && (d->m_lookahead_اندازه < TDEFL_MAX_سمون_LEN))
      {
        mz_uint8 c = *pSrc++;
        mz_uint dst_pos = (d->m_lookahead_pos + d->m_lookahead_اندازه) & TDEFL_LZ_DICT_اندازه_ماسک;
        src_buf_کیڼ--;
        d->m_dict[dst_pos] = c;
        إذا (dst_pos < (TDEFL_MAX_سمون_LEN - 1))
          d->m_dict[TDEFL_LZ_DICT_اندازه + dst_pos] = c;
        إذا ((++d->m_lookahead_اندازه + d->m_dict_اندازه) >= TDEFL_MIN_سمون_LEN)
        {
          mz_uint ins_pos = d->m_lookahead_pos + (d->m_lookahead_اندازه - 1) - 2;
          mz_uint hash = ((d->m_dict[ins_pos & TDEFL_LZ_DICT_اندازه_ماسک] << (TDEFL_LZ_HASH_ښويدنه * 2)) ^ (d->m_dict[(ins_pos + 1) & TDEFL_LZ_DICT_اندازه_ماسک] << TDEFL_LZ_HASH_ښويدنه) ^ c) & (TDEFL_LZ_HASH_اندازه - 1);
          d->m_بل[ins_pos & TDEFL_LZ_DICT_اندازه_ماسک] = d->m_hash[hash]; d->m_hash[hash] = (mz_uint16)(ins_pos);
        }
      }
    }
    d->m_dict_اندازه = MZ_MIN(TDEFL_LZ_DICT_اندازه - d->m_lookahead_اندازه, d->m_dict_اندازه);
    إذا ((!flush) && (d->m_lookahead_اندازه < TDEFL_MAX_سمون_LEN))
      اكسر;

    // Simple lazy/greedy parsing state machine.
    len_منزل_move = 1; cur_سمون_dist = 0; cur_سمون_len = d->m_saved_سمون_len ? d->m_saved_سمون_len : (TDEFL_MIN_سمون_LEN - 1); cur_pos = d->m_lookahead_pos & TDEFL_LZ_DICT_اندازه_ماسک;
    إذا (d->m_flags & (TDEFL_RLE_MATCHES | TDEFL_FORCE_ALL_RAW_بلاکونه))
    {
      إذا ((d->m_dict_اندازه) && (!(d->m_flags & TDEFL_FORCE_ALL_RAW_بلاکونه)))
      {
        mz_uint8 c = d->m_dict[(cur_pos - 1) & TDEFL_LZ_DICT_اندازه_ماسک];
        cur_سمون_len = 0; طالما (cur_سمون_len < d->m_lookahead_اندازه) { إذا (d->m_dict[cur_pos + cur_سمون_len] != c) اكسر; cur_سمون_len++; }
        إذا (cur_سمون_len < TDEFL_MIN_سمون_LEN) cur_سمون_len = 0; وإلا cur_سمون_dist = 1;
      }
    }
    وإلا
    {
      tdefl_پیدا_کړه_سمون(d, d->m_lookahead_pos, d->m_dict_اندازه, d->m_lookahead_اندازه, &cur_سمون_dist, &cur_سمون_len);
    }
    إذا (((cur_سمون_len == TDEFL_MIN_سمون_LEN) && (cur_سمون_dist >= 8U*1024U)) || (cur_pos == cur_سمون_dist) || ((d->m_flags & TDEFL_FILTER_MATCHES) && (cur_سمون_len <= 5)))
    {
      cur_سمون_dist = cur_سمون_len = 0;
    }
    إذا (d->m_saved_سمون_len)
    {
      إذا (cur_سمون_len > d->m_saved_سمون_len)
      {
        tdefl_ریکارډ_literal(d, (mz_uint8)d->m_saved_lit);
        إذا (cur_سمون_len >= 128)
        {
          tdefl_ریکارډ_سمون(d, cur_سمون_len, cur_سمون_dist);
          d->m_saved_سمون_len = 0; len_منزل_move = cur_سمون_len;
        }
        وإلا
        {
          d->m_saved_lit = d->m_dict[cur_pos]; d->m_saved_سمون_dist = cur_سمون_dist; d->m_saved_سمون_len = cur_سمون_len;
        }
      }
      وإلا
      {
        tdefl_ریکارډ_سمون(d, d->m_saved_سمون_len, d->m_saved_سمون_dist);
        len_منزل_move = d->m_saved_سمون_len - 1; d->m_saved_سمون_len = 0;
      }
    }
    وإلا إذا (!cur_سمون_dist)
      tdefl_ریکارډ_literal(d, d->m_dict[MZ_MIN(cur_pos, حجم(d->m_dict) - 1)]);
    وإلا إذا ((d->m_greedy_parsing) || (d->m_flags & TDEFL_RLE_MATCHES) || (cur_سمون_len >= 128))
    {
      tdefl_ریکارډ_سمون(d, cur_سمون_len, cur_سمون_dist);
      len_منزل_move = cur_سمون_len;
    }
    وإلا
    {
      d->m_saved_lit = d->m_dict[MZ_MIN(cur_pos, حجم(d->m_dict) - 1)]; d->m_saved_سمون_dist = cur_سمون_dist; d->m_saved_سمون_len = cur_سمون_len;
    }
    // Move the lookahead forward by len_to_move bytes.
    d->m_lookahead_pos += len_منزل_move;
    MZ_ASSERT(d->m_lookahead_اندازه >= len_منزل_move);
    d->m_lookahead_اندازه -= len_منزل_move;
    d->m_dict_اندازه = MZ_MIN(d->m_dict_اندازه + len_منزل_move, TDEFL_LZ_DICT_اندازه);
    // Check if it's time to flush the current LZ codes to the internal output buffer.
    إذا ( (d->m_p_LZ_کوډ_buf > &d->m_lz_کوډ_buf[TDEFL_LZ_کوډ_BUF_اندازه - 8]) ||
         ( (d->m_ټول_lz_بایټونه > 31*1024) && (((((mz_uint)(d->m_p_LZ_کوډ_buf - d->m_lz_کوډ_buf) * 115) >> 7) >= d->m_ټول_lz_بایټونه) || (d->m_flags & TDEFL_FORCE_ALL_RAW_بلاکونه))) )
    {
      صحيح n;
      d->m_pSrc = pSrc; d->m_src_buf_کیڼ = src_buf_کیڼ;
      إذا ((n = tdefl_flush_بلاک(d, 0)) != 0)
        أرجع (n < 0) ? MZ_FALSE : MZ_TRUE;
    }
  }

  d->m_pSrc = pSrc; d->m_src_buf_کیڼ = src_buf_کیڼ;
  أرجع MZ_TRUE;
}

ساكن tdefl_حالت tdefl_flush_output_بفر(tdefl_compressor *d)
{
  إذا (d->m_p_دننه_buf_اندازه)
  {
    *d->m_p_دننه_buf_اندازه = d->m_pSrc - (ثابت mz_uint8 *)d->m_p_دننه_buf;
  }

  إذا (d->m_p_بهر_buf_اندازه)
  {
    size_t n = MZ_MIN(*d->m_p_بهر_buf_اندازه - d->m_بهر_buf_ofs, d->m_output_flush_پاتې_شوی);
    حافظه_نقل((mz_uint8 *)d->m_p_بهر_buf + d->m_بهر_buf_ofs, d->m_output_buf + d->m_output_flush_ofs, n);
    d->m_output_flush_ofs += (mz_uint)n;
    d->m_output_flush_پاتې_شوی -= (mz_uint)n;
    d->m_بهر_buf_ofs += n;

    *d->m_p_بهر_buf_اندازه = d->m_بهر_buf_ofs;
  }

  أرجع (d->m_پای_ته_رسېدلی && !d->m_output_flush_پاتې_شوی) ? TDEFL_حالت_بشپړ : TDEFL_حالت_OKAY;
}

tdefl_حالت tdefl_compress(tdefl_compressor *d, ثابت فراغ *p_دننه_buf, size_t *p_دننه_buf_اندازه, فراغ *p_بهر_buf, size_t *p_بهر_buf_اندازه, tdefl_flush flush)
{
  إذا (!d)
  {
    إذا (p_دننه_buf_اندازه) *p_دننه_buf_اندازه = 0;
    إذا (p_بهر_buf_اندازه) *p_بهر_buf_اندازه = 0;
    أرجع TDEFL_حالت_BAD_PARAM;
  }

  d->m_p_دننه_buf = p_دننه_buf; d->m_p_دننه_buf_اندازه = p_دننه_buf_اندازه;
  d->m_p_بهر_buf = p_بهر_buf; d->m_p_بهر_buf_اندازه = p_بهر_buf_اندازه;
  d->m_pSrc = (ثابت mz_uint8 *)(p_دننه_buf); d->m_src_buf_کیڼ = p_دننه_buf_اندازه ? *p_دننه_buf_اندازه : 0;
  d->m_بهر_buf_ofs = 0;
  d->m_flush = flush;

  إذا ( ((d->m_pPut_buf_func != عدم) == ((p_بهر_buf != عدم) || (p_بهر_buf_اندازه != عدم))) || (d->m_prev_return_حالت != TDEFL_حالت_OKAY) ||
        (d->m_غواړي_منزل_پای && (flush != TDEFL_پای)) || (p_دننه_buf_اندازه && *p_دننه_buf_اندازه && !p_دننه_buf) || (p_بهر_buf_اندازه && *p_بهر_buf_اندازه && !p_بهر_buf) )
  {
    إذا (p_دننه_buf_اندازه) *p_دننه_buf_اندازه = 0;
    إذا (p_بهر_buf_اندازه) *p_بهر_buf_اندازه = 0;
    أرجع (d->m_prev_return_حالت = TDEFL_حالت_BAD_PARAM);
  }
  d->m_غواړي_منزل_پای |= (flush == TDEFL_پای);

  إذا ((d->m_output_flush_پاتې_شوی) || (d->m_پای_ته_رسېدلی))
    أرجع (d->m_prev_return_حالت = tdefl_flush_output_بفر(d));

#إذا MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  إذا (((d->m_flags & TDEFL_MAX_PROBES_ماسک) == 1) &&
      ((d->m_flags & TDEFL_GREEDY_PARSING_FLAG) != 0) &&
      ((d->m_flags & (TDEFL_FILTER_MATCHES | TDEFL_FORCE_ALL_RAW_بلاکونه | TDEFL_RLE_MATCHES)) == 0))
  {
    إذا (!tdefl_compress_fast(d))
      أرجع d->m_prev_return_حالت;
  }
  وإلا
#د_که_پای // #if MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  {
    إذا (!tdefl_compress_نورمال(d))
      أرجع d->m_prev_return_حالت;
  }

  إذا ((d->m_flags & (TDEFL_WRITE_ZLIB_سرلیک | TDEFL_COMPUTE_ADLER32)) && (p_دننه_buf))
    d->m_adler32 = (mz_uint32)mz_adler32(d->m_adler32, (ثابت mz_uint8 *)p_دننه_buf, d->m_pSrc - (ثابت mz_uint8 *)p_دننه_buf);

  إذا ((flush) && (!d->m_lookahead_اندازه) && (!d->m_src_buf_کیڼ) && (!d->m_output_flush_پاتې_شوی))
  {
    إذا (tdefl_flush_بلاک(d, flush) < 0)
      أرجع d->m_prev_return_حالت;
    d->m_پای_ته_رسېدلی = (flush == TDEFL_پای);
    إذا (flush == TDEFL_ډک_FLUSH) { MZ_CLEAR_ARR(d->m_hash); MZ_CLEAR_ARR(d->m_بل); d->m_dict_اندازه = 0; }
  }

  أرجع (d->m_prev_return_حالت = tdefl_flush_output_بفر(d));
}

tdefl_حالت tdefl_compress_بفر(tdefl_compressor *d, ثابت فراغ *p_دننه_buf, size_t دننه_buf_اندازه, tdefl_flush flush)
{
  MZ_ASSERT(d->m_pPut_buf_func); أرجع tdefl_compress(d, p_دننه_buf, &دننه_buf_اندازه, عدم, عدم, flush);
}

tdefl_حالت tdefl_init(tdefl_compressor *d, tdefl_put_buf_func_ptr pPut_buf_func, فراغ *pPut_buf_user, صحيح flags)
{
  d->m_pPut_buf_func = pPut_buf_func; d->m_pPut_buf_user = pPut_buf_user;
  d->m_flags = (mz_uint)(flags); d->m_max_probes[0] = 1 + ((flags & 0xFFF) + 2) / 3; d->m_greedy_parsing = (flags & TDEFL_GREEDY_PARSING_FLAG) != 0;
  d->m_max_probes[1] = 1 + (((flags & 0xFFF) >> 2) + 2) / 3;
  إذا (!(flags & TDEFL_NONDETERMINISTIC_PARSING_FLAG)) MZ_CLEAR_ARR(d->m_hash);
  d->m_lookahead_pos = d->m_lookahead_اندازه = d->m_dict_اندازه = d->m_ټول_lz_بایټونه = d->m_lz_کوډ_buf_dict_pos = d->m_بټونه_دننه = 0;
  d->m_output_flush_ofs = d->m_output_flush_پاتې_شوی = d->m_پای_ته_رسېدلی = d->m_بلاک_شاخص = d->m_بټ_بفر = d->m_غواړي_منزل_پای = 0;
  d->m_p_LZ_کوډ_buf = d->m_lz_کوډ_buf + 1; d->m_pLZ_flags = d->m_lz_کوډ_buf; d->m_عدد_flags_کیڼ = 8;
  d->m_pOutput_buf = d->m_output_buf; d->m_p_Output_buf_پای_ټکی = d->m_output_buf; d->m_prev_return_حالت = TDEFL_حالت_OKAY;
  d->m_saved_سمون_dist = d->m_saved_سمون_len = d->m_saved_lit = 0; d->m_adler32 = 1;
  d->m_p_دننه_buf = عدم; d->m_p_بهر_buf = عدم;
  d->m_p_دننه_buf_اندازه = عدم; d->m_p_بهر_buf_اندازه = عدم;
  d->m_flush = TDEFL_NO_FLUSH; d->m_pSrc = عدم; d->m_src_buf_کیڼ = 0; d->m_بهر_buf_ofs = 0;
  memset(&d->m_huff_شمېر[0][0], 0, حجم(d->m_huff_شمېر[0][0]) * TDEFL_MAX_HUFF_SYMBOLS_0);
  memset(&d->m_huff_شمېر[1][0], 0, حجم(d->m_huff_شمېر[1][0]) * TDEFL_MAX_HUFF_SYMBOLS_1);
  أرجع TDEFL_حالت_OKAY;
}

#که_نه_تعریف_شوی MINIZ_SDL_NOUNUSED
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
  succeeded = succeeded && (tdefl_compress_بفر(pComp, pBuf, buf_len, TDEFL_پای) == TDEFL_حالت_بشپړ);
  MZ_FREE(pComp); أرجع succeeded;
}
#د_که_پای /* MINIZ_SDL_NOUNUSED */

تعريفنوع بنية
{
  size_t m_اندازه, m_ظرفیت;
  mz_uint8 *m_pBuf;
  mz_bool m_expandable;
} tdefl_output_بفر;

ساكن mz_bool tdefl_output_بفر_putter(ثابت فراغ *pBuf, صحيح len, فراغ *pUser)
{
  tdefl_output_بفر *p = (tdefl_output_بفر *)pUser;
  size_t new_اندازه = p->m_اندازه + len;
  إذا (new_اندازه > p->m_ظرفیت)
  {
    size_t new_ظرفیت = p->m_ظرفیت; mz_uint8 *pNew_buf; إذا (!p->m_expandable) أرجع MZ_FALSE;
    افعل { new_ظرفیت = MZ_MAX(128U, new_ظرفیت << 1U); } طالما (new_اندازه > new_ظرفیت);
    pNew_buf = (mz_uint8*)MZ_REALLOC(p->m_pBuf, new_ظرفیت); إذا (!pNew_buf) أرجع MZ_FALSE;
    p->m_pBuf = pNew_buf; p->m_ظرفیت = new_ظرفیت;
  }
  حافظه_نقل((mz_uint8*)p->m_pBuf + p->m_اندازه, pBuf, len); p->m_اندازه = new_اندازه;
  أرجع MZ_TRUE;
}

#که_نه_تعریف_شوی MINIZ_SDL_NOUNUSED
فراغ *tdefl_compress_mem_منزل_ډېرۍ(ثابت فراغ *pSrc_buf, size_t src_buf_len, size_t *p_بهر_len, صحيح flags)
{
  tdefl_output_بفر بهر_buf; MZ_CLEAR_OBJ(بهر_buf);
  إذا (!p_بهر_len) أرجع MZ_FALSE; وإلا *p_بهر_len = 0;
  بهر_buf.m_expandable = MZ_TRUE;
  إذا (!tdefl_compress_mem_منزل_output(pSrc_buf, src_buf_len, tdefl_output_بفر_putter, &بهر_buf, flags)) أرجع عدم;
  *p_بهر_len = بهر_buf.m_اندازه; أرجع بهر_buf.m_pBuf;
}

size_t tdefl_compress_mem_منزل_mem(فراغ *p_بهر_buf, size_t بهر_buf_len, ثابت فراغ *pSrc_buf, size_t src_buf_len, صحيح flags)
{
  tdefl_output_بفر بهر_buf; MZ_CLEAR_OBJ(بهر_buf);
  إذا (!p_بهر_buf) أرجع 0;
  بهر_buf.m_pBuf = (mz_uint8*)p_بهر_buf; بهر_buf.m_ظرفیت = بهر_buf_len;
  إذا (!tdefl_compress_mem_منزل_output(pSrc_buf, src_buf_len, tdefl_output_بفر_putter, &بهر_buf, flags)) أرجع 0;
  أرجع بهر_buf.m_اندازه;
}
#د_که_پای /* MINIZ_SDL_NOUNUSED */

#که_نه_تعریف_شوی MINIZ_NO_ZLIB_APIS
ساكن ثابت mz_uint s_tdefl_عدد_probes[11] = { 0, 1, 6, 32,  16, 32, 128, 256,  512, 768, 1500 };

// level may actually range from [0,10] (10 is a "hidden" max level, where we want a bit more compression and it's fine if throughput to fall off a cliff on some files).
mz_uint tdefl_create_comp_flags_from_zip_params(صحيح level, صحيح کړکۍ_بټونه, صحيح strategy)
{
  mz_uint comp_flags = s_tdefl_عدد_probes[(level >= 0) ? MZ_MIN(10, level) : MZ_DEFAULT_LEVEL] | ((level <= 3) ? TDEFL_GREEDY_PARSING_FLAG : 0);
  إذا (کړکۍ_بټونه > 0) comp_flags |= TDEFL_WRITE_ZLIB_سرلیک;

  إذا (!level) comp_flags |= TDEFL_FORCE_ALL_RAW_بلاکونه;
  وإلا إذا (strategy == MZ_FILTERED) comp_flags |= TDEFL_FILTER_MATCHES;
  وإلا إذا (strategy == MZ_HUFFMAN_ONLY) comp_flags &= ~TDEFL_MAX_PROBES_ماسک;
  وإلا إذا (strategy == MZ_FIXED) comp_flags |= TDEFL_FORCE_ALL_STATIC_بلاکونه;
  وإلا إذا (strategy == MZ_RLE) comp_flags |= TDEFL_RLE_MATCHES;

  أرجع comp_flags;
}
#د_که_پای //MINIZ_NO_ZLIB_APIS

#که_تعریف_شوی _MSC_VER
#لارښوونه warning (ټېل)
#لارښوونه warning (disable:4204) // nonstandard extension used : non-constant aggregate initializer (also supported by GNU C and C99, so no big deal)
#د_که_پای

// Simple PNG writer function by Alex Evans, 2011. Released into the public domain: https://gist.github.com/908299, more context at
// http://altdevblogaday.org/2011/04/06/a-smaller-jpg-encoder/.
// This is actually a modification of Alex's original code so PNG files generated by this function pass pngcheck.
MINIZ_STATIC فراغ *tdefl_write_image_منزل_png_file_دننه_حافظه_ex(ثابت فراغ *pImage, صحيح w, صحيح h, صحيح عدد_chans, صحيح bpl, size_t *p_Len_بهر, mz_uint level, mz_bool flip, mz_uint8 *plte, صحيح plte_اندازه, mz_uint8 *trns, صحيح trns_اندازه)
{
  // Using a local copy of this array here in case MINIZ_NO_ZLIB_APIS was defined.
  ساكن ثابت mz_uint s_tdefl_png_عدد_probes[11] = { 0, 1, 6, 32,  16, 32, 128, 256,  512, 768, 1500 };
  tdefl_compressor *pComp = (tdefl_compressor *)MZ_MALLOC(حجم(tdefl_compressor)); tdefl_output_بفر بهر_buf; صحيح i, y, z = 0; mz_uint32 c; *p_Len_بهر = 0; size_t معلومات_پیل, معلومات_اندازه_3;
  إذا (!pComp) أرجع عدم;
  MZ_CLEAR_OBJ(بهر_buf); بهر_buf.m_expandable = MZ_TRUE;
  بهر_buf.m_ظرفیت = 57+MZ_MAX(64, (1+w*عدد_chans)*h);
  إذا (plte_اندازه > 0)
    بهر_buf.m_ظرفیت += 12+plte_اندازه;
  إذا (trns_اندازه > 0)
    بهر_buf.m_ظرفیت += 12+trns_اندازه;
  إذا (عدم == (بهر_buf.m_pBuf = (mz_uint8*)MZ_MALLOC(بهر_buf.m_ظرفیت))) { MZ_FREE(pComp); أرجع عدم; }
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

    إذا (عدد_chans == 1 && plte_اندازه > 0)
      pnghdr[25] = 3;
    وإلا
      pnghdr[25] = (chans[عدد_chans]);

    c = (mz_uint32)mz_دوراني_ازموینه_32(MZ_دوراني_ازموینه_32_INIT,pnghdr+12,17);
    لكل (i=0; i<4; ++i, c<<=8) ((mz_uint8*)(pnghdr+29))[i] = (mz_uint8)(c>>24);
    إذا (!tdefl_output_بفر_putter(pnghdr, حجم(pnghdr), &بهر_buf)) { *p_Len_بهر = 0; MZ_FREE(pComp); MZ_FREE(بهر_buf.m_pBuf); أرجع عدم; }
  }
  // write PLTE chunk
  إذا (plte_اندازه > 0)
  {
    mz_uint8 hdr[8]={0x00,0x00,0x00,0x00,0x50,0x4c,0x54,0x45};

    hdr[0] = (mz_uint8)(plte_اندازه>>24);
    hdr[1] = (mz_uint8)(plte_اندازه>>16);
    hdr[2] = (mz_uint8)(plte_اندازه>> 8);
    hdr[3] = (mz_uint8)(plte_اندازه>> 0);
    إذا (!tdefl_output_بفر_putter(hdr, حجم(hdr), &بهر_buf)) { *p_Len_بهر = 0; MZ_FREE(pComp); MZ_FREE(بهر_buf.m_pBuf); أرجع عدم; }
    معلومات_پیل = بهر_buf.m_اندازه;
    إذا (!tdefl_output_بفر_putter(plte, plte_اندازه, &بهر_buf)) { *p_Len_بهر = 0; MZ_FREE(pComp); MZ_FREE(بهر_buf.m_pBuf); أرجع عدم; }
    إذا (!tdefl_output_بفر_putter("\0\0\0\0", 4, &بهر_buf)) { *p_Len_بهر = 0; MZ_FREE(pComp); MZ_FREE(بهر_buf.m_pBuf); أرجع عدم; }
    c = (mz_uint32)mz_دوراني_ازموینه_32(MZ_دوراني_ازموینه_32_INIT,بهر_buf.m_pBuf+معلومات_پیل-4, plte_اندازه+4);
    لكل (i=0; i<4; ++i, c<<=8) (بهر_buf.m_pBuf+بهر_buf.m_اندازه-4)[i] = (mz_uint8)(c >> 24);
  }
  // write tRNS chunk
  إذا (trns_اندازه > 0)
  {
    mz_uint8 hdr[8]={0x00,0x00,0x00,0x00,0x74,0x52,0x4E,0x53};

    hdr[0] = (mz_uint8)(trns_اندازه>>24);
    hdr[1] = (mz_uint8)(trns_اندازه>>16);
    hdr[2] = (mz_uint8)(trns_اندازه>> 8);
    hdr[3] = (mz_uint8)(trns_اندازه>> 0);
    إذا (!tdefl_output_بفر_putter(hdr, حجم(hdr), &بهر_buf)) { *p_Len_بهر = 0; MZ_FREE(pComp); MZ_FREE(بهر_buf.m_pBuf); أرجع عدم; }
    معلومات_پیل = بهر_buf.m_اندازه;
    إذا (!tdefl_output_بفر_putter(trns, trns_اندازه, &بهر_buf)) { *p_Len_بهر = 0; MZ_FREE(pComp); MZ_FREE(بهر_buf.m_pBuf); أرجع عدم; }
    إذا (!tdefl_output_بفر_putter("\0\0\0\0", 4, &بهر_buf)) { *p_Len_بهر = 0; MZ_FREE(pComp); MZ_FREE(بهر_buf.m_pBuf); أرجع عدم; }
    c = (mz_uint32)mz_دوراني_ازموینه_32(MZ_دوراني_ازموینه_32_INIT,بهر_buf.m_pBuf+معلومات_پیل-4, trns_اندازه+4);
    لكل (i=0; i<4; ++i, c<<=8) (بهر_buf.m_pBuf+بهر_buf.m_اندازه-4)[i] = (mz_uint8)(c >> 24);
  }
  // write IDAT chunk
  إذا (!tdefl_output_بفر_putter("\0\0\0\0\x49\x44\x41\x54", 8, &بهر_buf)) { *p_Len_بهر = 0; MZ_FREE(pComp); MZ_FREE(بهر_buf.m_pBuf); أرجع عدم; }
  معلومات_پیل = بهر_buf.m_اندازه;
  // compress image data
  tdefl_init(pComp, tdefl_output_بفر_putter, &بهر_buf, s_tdefl_png_عدد_probes[MZ_MIN(10, level)] | TDEFL_WRITE_ZLIB_سرلیک);
  لكل (y = 0; y < h; ++y) { tdefl_compress_بفر(pComp, &z, 1, TDEFL_NO_FLUSH); tdefl_compress_بفر(pComp, (mz_uint8*)pImage + (flip ? (h - 1 - y) : y) * bpl, w * عدد_chans, TDEFL_NO_FLUSH); }
  إذا (tdefl_compress_بفر(pComp, عدم, 0, TDEFL_پای) != TDEFL_حالت_بشپړ) { MZ_FREE(pComp); MZ_FREE(بهر_buf.m_pBuf); أرجع عدم; }
  // write IDAT size
  معلومات_اندازه_3 = بهر_buf.m_اندازه-معلومات_پیل;
  (بهر_buf.m_pBuf+معلومات_پیل-8)[0] = (mz_uint8)(معلومات_اندازه_3>>24);
  (بهر_buf.m_pBuf+معلومات_پیل-8)[1] = (mz_uint8)(معلومات_اندازه_3>>16);
  (بهر_buf.m_pBuf+معلومات_پیل-8)[2] = (mz_uint8)(معلومات_اندازه_3>> 8);
  (بهر_buf.m_pBuf+معلومات_پیل-8)[3] = (mz_uint8)(معلومات_اندازه_3>> 0);
  // write footer (IDAT CRC-32, followed by IEND chunk)
  إذا (!tdefl_output_بفر_putter("\0\0\0\0\0\0\0\0\x49\x45\x4e\x44\xae\x42\x60\x82", 16, &بهر_buf)) { *p_Len_بهر = 0; MZ_FREE(pComp); MZ_FREE(بهر_buf.m_pBuf); أرجع عدم; }
  c = (mz_uint32)mz_دوراني_ازموینه_32(MZ_دوراني_ازموینه_32_INIT,بهر_buf.m_pBuf+معلومات_پیل-4, معلومات_اندازه_3+4);
  لكل (i=0; i<4; ++i, c<<=8) (بهر_buf.m_pBuf+بهر_buf.m_اندازه-16)[i] = (mz_uint8)(c >> 24);
  // compute final size of file, grab compressed data buffer and return
  *p_Len_بهر = بهر_buf.m_اندازه;
  MZ_FREE(pComp);
  أرجع بهر_buf.m_pBuf;
}
#که_نه_تعریف_شوی MINIZ_SDL_NOUNUSED
MINIZ_STATIC فراغ *tdefl_write_image_منزل_png_file_دننه_حافظه(ثابت فراغ *pImage, صحيح w, صحيح h, صحيح عدد_chans, صحيح bpl, size_t *p_Len_بهر)
{
  // Level 6 corresponds to TDEFL_DEFAULT_MAX_PROBES or MZ_DEFAULT_LEVEL (but we can't depend on MZ_DEFAULT_LEVEL being available in case the zlib API's where #defined out)
  أرجع tdefl_write_image_منزل_png_file_دننه_حافظه_ex(pImage, w, h, عدد_chans, bpl, p_Len_بهر, 6, MZ_FALSE, عدم, 0, عدم, 0);
}
#د_که_پای

#که_تعریف_شوی _MSC_VER
#لارښوونه warning (راوباسه)
#د_که_پای
#د_که_پای /*#ifndef MINIZ_NO_DEFLATE_APIS*/

// ------------------- .ZIP archive reading

#که_نه_تعریف_شوی MINIZ_NO_ARCHIVE_APIS

#که_تعریف_شوی MINIZ_NO_STDIO
  #تعریف_کړه MZ_FILE فراغ *
#وإلا
  #ضمن <stdio.h>
  #ضمن <sys/stat.h>

  #إذا defined(_MSC_VER) || defined(__MINGW64__)
    ساكن FILE *mz_fopen(ثابت حرف *pFilename, ثابت حرف *p_ډېرپېښ)
    {
      FILE* pFile = عدم;
      fopen_s(&pFile, pFilename, p_ډېرپېښ);
      أرجع pFile;
    }
    ساكن FILE *mz_freopen(ثابت حرف *p_لار, ثابت حرف *p_ډېرپېښ, FILE *p_بهیر)
    {
      FILE* pFile = عدم;
      إذا (freopen_s(&pFile, p_لار, p_ډېرپېښ, p_بهیر))
        أرجع عدم;
      أرجع pFile;
    }
    #که_نه_تعریف_شوی MINIZ_NO_وخت
      #ضمن <sys/utime.h>
    #د_که_پای
    #تعریف_کړه MZ_FILE FILE
    #تعریف_کړه MZ_FOPEN mz_fopen
    #تعریف_کړه MZ_FCLOSE fclose
    #تعریف_کړه MZ_FREAD fread
    #تعریف_کړه MZ_FWRITE fwrite
    #تعریف_کړه MZ_FTELL64 _ftelli64
    #تعریف_کړه MZ_FSEEK64 _fseeki64
    #تعریف_کړه MZ_FILE_STAT_STRUCT _stat
    #تعریف_کړه MZ_FILE_STAT _stat
    #تعریف_کړه MZ_FFLUSH fflush
    #تعریف_کړه MZ_FREOPEN mz_freopen
    #تعریف_کړه MZ_DELETE_FILE remove
  #وإلاإذا defined(__MINGW32__)
    #که_نه_تعریف_شوی MINIZ_NO_وخت
      #ضمن <sys/utime.h>
    #د_که_پای
    #تعریف_کړه MZ_FILE FILE
    #تعریف_کړه MZ_FOPEN(f, m) fopen(f, m)
    #تعریف_کړه MZ_FCLOSE fclose
    #تعریف_کړه MZ_FREAD fread
    #تعریف_کړه MZ_FWRITE fwrite
    #تعریف_کړه MZ_FTELL64 ftello64
    #تعریف_کړه MZ_FSEEK64 fseeko64
    #تعریف_کړه MZ_FILE_STAT_STRUCT _stat
    #تعریف_کړه MZ_FILE_STAT _stat
    #تعریف_کړه MZ_FFLUSH fflush
    #تعریف_کړه MZ_FREOPEN(f, m, s) freopen(f, m, s)
    #تعریف_کړه MZ_DELETE_FILE remove
  #وإلاإذا defined(__TINYC__)
    #که_نه_تعریف_شوی MINIZ_NO_وخت
      #ضمن <sys/utime.h>
    #د_که_پای
    #تعریف_کړه MZ_FILE FILE
    #تعریف_کړه MZ_FOPEN(f, m) fopen(f, m)
    #تعریف_کړه MZ_FCLOSE fclose
    #تعریف_کړه MZ_FREAD fread
    #تعریف_کړه MZ_FWRITE fwrite
    #تعریف_کړه MZ_FTELL64 ftell
    #تعریف_کړه MZ_FSEEK64 fseek
    #تعریف_کړه MZ_FILE_STAT_STRUCT stat
    #تعریف_کړه MZ_FILE_STAT stat
    #تعریف_کړه MZ_FFLUSH fflush
    #تعریف_کړه MZ_FREOPEN(f, m, s) freopen(f, m, s)
    #تعریف_کړه MZ_DELETE_FILE remove
  #وإلاإذا defined(__GNUC__) && LARGEFILE64_سرچینه
    #که_نه_تعریف_شوی MINIZ_NO_وخت
      #ضمن <utime.h>
    #د_که_پای
    #تعریف_کړه MZ_FILE FILE
    #تعریف_کړه MZ_FOPEN(f, m) fopen64(f, m)
    #تعریف_کړه MZ_FCLOSE fclose
    #تعریف_کړه MZ_FREAD fread
    #تعریف_کړه MZ_FWRITE fwrite
    #تعریف_کړه MZ_FTELL64 ftello64
    #تعریف_کړه MZ_FSEEK64 fseeko64
    #تعریف_کړه MZ_FILE_STAT_STRUCT stat64
    #تعریف_کړه MZ_FILE_STAT stat64
    #تعریف_کړه MZ_FFLUSH fflush
    #تعریف_کړه MZ_FREOPEN(p, m, s) freopen64(p, m, s)
    #تعریف_کړه MZ_DELETE_FILE remove
  #وإلا
    #که_نه_تعریف_شوی MINIZ_NO_وخت
      #ضمن <utime.h>
    #د_که_پای
    #تعریف_کړه MZ_FILE FILE
    #تعریف_کړه MZ_FOPEN(f, m) fopen(f, m)
    #تعریف_کړه MZ_FCLOSE fclose
    #تعریف_کړه MZ_FREAD fread
    #تعریف_کړه MZ_FWRITE fwrite
    #تعریف_کړه MZ_FTELL64 ftello
    #تعریف_کړه MZ_FSEEK64 fseeko
    #تعریف_کړه MZ_FILE_STAT_STRUCT stat
    #تعریف_کړه MZ_FILE_STAT stat
    #تعریف_کړه MZ_FFLUSH fflush
    #تعریف_کړه MZ_FREOPEN(f, m, s) freopen(f, m, s)
    #تعریف_کړه MZ_DELETE_FILE remove
  #د_که_پای // #ifdef _MSC_VER
#د_که_پای // #ifdef MINIZ_NO_STDIO

#تعریف_کړه MZ_TOLOWER(c) ((((c) >= 'A') && ((c) <= 'Z')) ? ((c) - 'A' + 'a') : (c))

// Various ZIP archive enums. To completely avoid cross platform compiler alignment and platform endian issues, miniz.c doesn't use structs for any of this stuff.
تعداد
{
  // ZIP archive identifiers and record sizes
  MZ_ZIP_پای_ټکی_د_CENTRAL_DIR_سرلیک_SIG = 0x06054b50, MZ_ZIP_CENTRAL_DIR_سرلیک_SIG = 0x02014b50, MZ_ZIP_LOCAL_DIR_سرلیک_SIG = 0x04034b50,
  MZ_ZIP_LOCAL_DIR_سرلیک_اندازه = 30, MZ_ZIP_CENTRAL_DIR_سرلیک_اندازه = 46, MZ_ZIP_پای_ټکی_د_CENTRAL_DIR_سرلیک_اندازه = 22,
  // Central directory header record offsets
  MZ_ZIP_CDH_SIG_OFS = 0, MZ_ZIP_CDH_نسخه_MADE_BY_OFS = 4, MZ_ZIP_CDH_نسخه_NEEDED_OFS = 6, MZ_ZIP_CDH_بټ_FLAG_OFS = 8,
  MZ_ZIP_CDH_لاره_OFS = 10, MZ_ZIP_CDH_FILE_وخت_OFS = 12, MZ_ZIP_CDH_FILE_DATE_OFS = 14, MZ_ZIP_CDH_دوراني_ازموینه_32_OFS = 16,
  MZ_ZIP_CDH_COMPRESSED_اندازه_OFS = 20, MZ_ZIP_CDH_DECOMPRESSED_اندازه_OFS = 24, MZ_ZIP_CDH_FILENAME_LEN_OFS = 28, MZ_ZIP_CDH_EXTRA_LEN_OFS = 30,
  MZ_ZIP_CDH_COMMENT_LEN_OFS = 32, MZ_ZIP_CDH_DISK_پیل_OFS = 34, MZ_ZIP_CDH_دننی_ATTR_OFS = 36, MZ_ZIP_CDH_EXTERNAL_ATTR_OFS = 38, MZ_ZIP_CDH_LOCAL_سرلیک_OFS = 42,
  // Local directory header offsets
  MZ_ZIP_LDH_SIG_OFS = 0, MZ_ZIP_LDH_نسخه_NEEDED_OFS = 4, MZ_ZIP_LDH_بټ_FLAG_OFS = 6, MZ_ZIP_LDH_لاره_OFS = 8, MZ_ZIP_LDH_FILE_وخت_OFS = 10,
  MZ_ZIP_LDH_FILE_DATE_OFS = 12, MZ_ZIP_LDH_دوراني_ازموینه_32_OFS = 14, MZ_ZIP_LDH_COMPRESSED_اندازه_OFS = 18, MZ_ZIP_LDH_DECOMPRESSED_اندازه_OFS = 22,
  MZ_ZIP_LDH_FILENAME_LEN_OFS = 26, MZ_ZIP_LDH_EXTRA_LEN_OFS = 28,
  // End of central directory offsets
  MZ_ZIP_ECDH_SIG_OFS = 0, MZ_ZIP_ECDH_عدد_THIS_DISK_OFS = 4, MZ_ZIP_ECDH_عدد_DISK_CDIR_OFS = 6, MZ_ZIP_ECDH_CDIR_عدد_ENTRIES_ON_DISK_OFS = 8,
  MZ_ZIP_ECDH_CDIR_ټول_ENTRIES_OFS = 10, MZ_ZIP_ECDH_CDIR_اندازه_OFS = 12, MZ_ZIP_ECDH_CDIR_OFS_OFS = 16, MZ_ZIP_ECDH_COMMENT_اندازه_OFS = 20,
};

تعريفنوع بنية
{
  فراغ *m_p;
  size_t m_اندازه, m_ظرفیت;
  mz_uint m_element_اندازه;
} mz_zip_array;

بنية mz_zip_دننی_state_نښان
{
  mz_zip_array m_central_dir;
  mz_zip_array m_central_dir_offsets;
  mz_zip_array m_sorted_central_dir_offsets;
  MZ_FILE *m_pFile;
  فراغ *m_pMem;
  size_t m_mem_اندازه;
  size_t m_mem_ظرفیت;
};

#تعریف_کړه MZ_ZIP_ARRAY_سېټ_ELEMENT_اندازه(array_ptr, element_اندازه) (array_ptr)->m_element_اندازه = element_اندازه
#تعریف_کړه MZ_ZIP_ARRAY_ELEMENT(array_ptr, element_type, شاخص) ((element_type *)((array_ptr)->m_p))[شاخص]

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

ساكن MZ_FORCEINLINE mz_bool mz_zip_array_ensure_ځای(mz_zip_archive *pZip, mz_zip_array *pArray, size_t n)
{
  أرجع mz_zip_array_reserve(pZip, pArray, pArray->m_اندازه + n, MZ_TRUE);
}

ساكن MZ_FORCEINLINE mz_bool mz_zip_array_ټېل_شا(mz_zip_archive *pZip, mz_zip_array *pArray, ثابت فراغ *pElements, size_t n)
{
  size_t orig_اندازه = pArray->m_اندازه; إذا (!mz_zip_array_resize(pZip, pArray, orig_اندازه + n, MZ_TRUE)) أرجع MZ_FALSE;
  حافظه_نقل((mz_uint8*)pArray->m_p + orig_اندازه * pArray->m_element_اندازه, pElements, n * pArray->m_element_اندازه);
  أرجع MZ_TRUE;
}

#که_نه_تعریف_شوی MINIZ_NO_وخت
ساكن وخت_t mz_zip_dos_منزل_وخت_t(صحيح dos_وخت, صحيح dos_date)
{
  بنية tm tm;
  memset(&tm, 0, حجم(tm)); tm.tm_isdst = -1;
  tm.tm_year = ((dos_date >> 9) & 127) + 1980 - 1900; tm.tm_mon = ((dos_date >> 5) & 15) - 1; tm.tm_mday = dos_date & 31;
  tm.tm_hour = (dos_وخت >> 11) & 31; tm.tm_min = (dos_وخت >> 5) & 63; tm.tm_sec = (dos_وخت << 1) & 62;
  أرجع mktime(&tm);
}

ساكن فراغ mz_zip_وخت_منزل_dos_وخت(وخت_t وخت, mz_uint16 *p_DOS_وخت, mz_uint16 *pDOS_date)
{
#که_تعریف_شوی _MSC_VER
  بنية tm tm_struct;
  بنية tm *tm = &tm_struct;
  errno_t err = localtime_s(tm, &وخت);
  إذا (err)
  {
    *pDOS_date = 0; *p_DOS_وخت = 0;
    أرجع;
  }
#وإلا
  بنية tm *tm = localtime(&وخت);
#د_که_پای
  *p_DOS_وخت = (mz_uint16)(((tm->tm_hour) << 11) + ((tm->tm_min) << 5) + ((tm->tm_sec) >> 1));
  *pDOS_date = (mz_uint16)(((tm->tm_year + 1900 - 1980) << 9) + ((tm->tm_mon + 1) << 5) + tm->tm_mday);
}
#د_که_پای

#که_نه_تعریف_شوی MINIZ_NO_STDIO
ساكن mz_bool mz_zip_get_file_modified_وخت(ثابت حرف *pFilename, mz_uint16 *p_DOS_وخت, mz_uint16 *pDOS_date)
{
#که_تعریف_شوی MINIZ_NO_وخت
  (فراغ)pFilename; *pDOS_date = *p_DOS_وخت = 0;
#وإلا
  بنية MZ_FILE_STAT_STRUCT file_stat;
  // On Linux with x86 glibc, this call will fail on large files (>= 0x80000000 bytes) unless you compiled with _LARGEFILE64_SOURCE. Argh.
  إذا (MZ_FILE_STAT(pFilename, &file_stat) != 0)
    أرجع MZ_FALSE;
  mz_zip_وخت_منزل_dos_وخت(file_stat.st_mtime, p_DOS_وخت, pDOS_date);
#د_که_پای // #ifdef MINIZ_NO_TIME
  أرجع MZ_TRUE;
}

#که_نه_تعریف_شوی MINIZ_NO_وخت
ساكن mz_bool mz_zip_سېټ_file_times(ثابت حرف *pFilename, وخت_t access_وخت, وخت_t modified_وخت)
{
  بنية utimbuf t; t.actime = access_وخت; t.modtime = modified_وخت;
  أرجع !utime(pFilename, &t);
}
#د_که_پای // #ifndef MINIZ_NO_TIME
#د_که_پای // #ifndef MINIZ_NO_STDIO

ساكن mz_bool mz_zip_reader_init_دننی(mz_zip_archive *pZip, mz_uint32 flags)
{
  (فراغ)flags;
  إذا ((!pZip) || (pZip->m_pState) || (pZip->m_zip_ډېرپېښ != MZ_ZIP_ډېرپېښ_INVALID))
    أرجع MZ_FALSE;

  إذا (!pZip->m_pAlloc) pZip->m_pAlloc = def_alloc_func;
  إذا (!pZip->m_pFree) pZip->m_pFree = def_free_func;
  إذا (!pZip->m_pRealloc) pZip->m_pRealloc = def_realloc_func;

  pZip->m_zip_ډېرپېښ = MZ_ZIP_ډېرپېښ_READING;
  pZip->m_archive_اندازه = 0;
  pZip->m_central_directory_file_ofs = 0;
  pZip->m_ټول_files = 0;

  إذا (عدم == (pZip->m_pState = (mz_zip_دننی_state *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, حجم(mz_zip_دننی_state))))
    أرجع MZ_FALSE;
  memset(pZip->m_pState, 0, حجم(mz_zip_دننی_state));
  MZ_ZIP_ARRAY_سېټ_ELEMENT_اندازه(&pZip->m_pState->m_central_dir, حجم(mz_uint8));
  MZ_ZIP_ARRAY_سېټ_ELEMENT_اندازه(&pZip->m_pState->m_central_dir_offsets, حجم(mz_uint32));
  MZ_ZIP_ARRAY_سېټ_ELEMENT_اندازه(&pZip->m_pState->m_sorted_central_dir_offsets, حجم(mz_uint32));
  أرجع MZ_TRUE;
}

ساكن MZ_FORCEINLINE mz_bool mz_zip_reader_filename_less(ثابت mz_zip_array *pCentral_dir_array, ثابت mz_zip_array *pCentral_dir_offsets, mz_uint l_شاخص, mz_uint r_شاخص)
{
  ثابت mz_uint8 *pL = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, l_شاخص)), *pE;
  ثابت mz_uint8 *pR = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, r_شاخص));
  mz_uint l_len = MZ_READ_LE16(pL + MZ_ZIP_CDH_FILENAME_LEN_OFS), r_len = MZ_READ_LE16(pR + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  mz_uint8 l = 0, r = 0;
  pL += MZ_ZIP_CENTRAL_DIR_سرلیک_اندازه; pR += MZ_ZIP_CENTRAL_DIR_سرلیک_اندازه;
  pE = pL + MZ_MIN(l_len, r_len);
  طالما (pL < pE)
  {
    إذا ((l = MZ_TOLOWER(*pL)) != (r = MZ_TOLOWER(*pR)))
      اكسر;
    pL++; pR++;
  }
  أرجع (pL == pE) ? (l_len < r_len) : (l < r);
}

#تعریف_کړه MZ_بدلون_UINT32(a, b) افعل { mz_uint32 t = a; a = b; b = t; } MZ_MACRO_پای_ټکی

// Heap sort of lowercased filenames, used to help accelerate plain central directory searches by mz_zip_reader_locate_file(). (Could also use qsort(), but it could allocate memory.)
ساكن فراغ mz_zip_reader_ترتیبول_central_dir_offsets_by_filename(mz_zip_archive *pZip)
{
  mz_zip_دننی_state *pState = pZip->m_pState;
  ثابت mz_zip_array *pCentral_dir_offsets = &pState->m_central_dir_offsets;
  ثابت mz_zip_array *pCentral_dir = &pState->m_central_dir;
  mz_uint32 *pIndices = &MZ_ZIP_ARRAY_ELEMENT(&pState->m_sorted_central_dir_offsets, mz_uint32, 0);
  ثابت صحيح اندازه = pZip->m_ټول_files;
  صحيح پیل = (اندازه - 2) >> 1, پای_ټکی;
  طالما (پیل >= 0)
  {
    صحيح ماشوم, ریښه = پیل;
    لكل ( ; ; )
    {
      إذا ((ماشوم = (ریښه << 1) + 1) >= اندازه)
        اكسر;
      ماشوم += (((ماشوم + 1) < اندازه) && (mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[ماشوم], pIndices[ماشوم + 1])));
      إذا (!mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[ریښه], pIndices[ماشوم]))
        اكسر;
      MZ_بدلون_UINT32(pIndices[ریښه], pIndices[ماشوم]); ریښه = ماشوم;
    }
    پیل--;
  }

  پای_ټکی = اندازه - 1;
  طالما (پای_ټکی > 0)
  {
    صحيح ماشوم, ریښه = 0;
    MZ_بدلون_UINT32(pIndices[پای_ټکی], pIndices[0]);
    لكل ( ; ; )
    {
      إذا ((ماشوم = (ریښه << 1) + 1) >= پای_ټکی)
        اكسر;
      ماشوم += (((ماشوم + 1) < پای_ټکی) && mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[ماشوم], pIndices[ماشوم + 1]));
      إذا (!mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[ریښه], pIndices[ماشوم]))
        اكسر;
      MZ_بدلون_UINT32(pIndices[ریښه], pIndices[ماشوم]); ریښه = ماشوم;
    }
    پای_ټکی--;
  }
}

ساكن mz_bool mz_zip_reader_read_central_dir(mz_zip_archive *pZip, mz_uint32 flags)
{
  mz_uint cdir_اندازه, عدد_this_disk, cdir_disk_شاخص;
  mz_uint64 cdir_ofs;
  mz_int64 cur_file_ofs;
  ثابت mz_uint8 *p;
  mz_uint32 buf_u32[4096 / حجم(mz_uint32)]; mz_uint8 *pBuf = (mz_uint8 *)buf_u32;
  mz_bool ترتیبول_central_dir = ((flags & MZ_ZIP_FLAG_DO_NOT_ترتیبول_CENTRAL_DIRECTORY) == 0);
  // Basic sanity checks - reject files which are too small, and check the first 4 bytes of the file to make sure a local header is there.
  إذا (pZip->m_archive_اندازه < MZ_ZIP_پای_ټکی_د_CENTRAL_DIR_سرلیک_اندازه)
    أرجع MZ_FALSE;
  // Find the end of central directory record by scanning the file from the end towards the beginning.
  cur_file_ofs = MZ_MAX((mz_int64)pZip->m_archive_اندازه - (mz_int64)حجم(buf_u32), 0);
  لكل ( ; ; )
  {
    صحيح i, n = (صحيح)MZ_MIN(حجم(buf_u32), pZip->m_archive_اندازه - cur_file_ofs);
    إذا (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, n) != (mz_uint)n)
      أرجع MZ_FALSE;
    لكل (i = n - 4; i >= 0; --i)
      إذا (MZ_READ_LE32(pBuf + i) == MZ_ZIP_پای_ټکی_د_CENTRAL_DIR_سرلیک_SIG)
        اكسر;
    إذا (i >= 0)
    {
      cur_file_ofs += i;
      اكسر;
    }
    إذا ((!cur_file_ofs) || ((pZip->m_archive_اندازه - cur_file_ofs) >= (0xFFFF + MZ_ZIP_پای_ټکی_د_CENTRAL_DIR_سرلیک_اندازه)))
      أرجع MZ_FALSE;
    cur_file_ofs = MZ_MAX(cur_file_ofs - (حجم(buf_u32) - 3), 0);
  }
  // Read and verify the end of central directory record.
  إذا (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, MZ_ZIP_پای_ټکی_د_CENTRAL_DIR_سرلیک_اندازه) != MZ_ZIP_پای_ټکی_د_CENTRAL_DIR_سرلیک_اندازه)
    أرجع MZ_FALSE;
  إذا ((MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_SIG_OFS) != MZ_ZIP_پای_ټکی_د_CENTRAL_DIR_سرلیک_SIG) ||
      ((pZip->m_ټول_files = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_CDIR_ټول_ENTRIES_OFS)) != MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_CDIR_عدد_ENTRIES_ON_DISK_OFS)))
    أرجع MZ_FALSE;

  عدد_this_disk = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_عدد_THIS_DISK_OFS);
  cdir_disk_شاخص = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_عدد_DISK_CDIR_OFS);
  إذا (((عدد_this_disk | cdir_disk_شاخص) != 0) && ((عدد_this_disk != 1) || (cdir_disk_شاخص != 1)))
    أرجع MZ_FALSE;

  إذا ((cdir_اندازه = MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_CDIR_اندازه_OFS)) < pZip->m_ټول_files * MZ_ZIP_CENTRAL_DIR_سرلیک_اندازه)
    أرجع MZ_FALSE;

  cdir_ofs = MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_CDIR_OFS_OFS);
  إذا ((cdir_ofs + (mz_uint64)cdir_اندازه) > pZip->m_archive_اندازه)
    أرجع MZ_FALSE;

  pZip->m_central_directory_file_ofs = cdir_ofs;

  إذا (pZip->m_ټول_files)
  {
     mz_uint i, n;

    // Read the entire central directory into a heap block, and allocate another heap block to hold the unsorted central dir file record offsets, and another to hold the sorted indices.
    إذا ((!mz_zip_array_resize(pZip, &pZip->m_pState->m_central_dir, cdir_اندازه, MZ_FALSE)) ||
        (!mz_zip_array_resize(pZip, &pZip->m_pState->m_central_dir_offsets, pZip->m_ټول_files, MZ_FALSE)))
      أرجع MZ_FALSE;

    إذا (ترتیبول_central_dir)
    {
      إذا (!mz_zip_array_resize(pZip, &pZip->m_pState->m_sorted_central_dir_offsets, pZip->m_ټول_files, MZ_FALSE))
        أرجع MZ_FALSE;
    }

    إذا (pZip->m_pRead(pZip->m_pIO_opaque, cdir_ofs, pZip->m_pState->m_central_dir.m_p, cdir_اندازه) != cdir_اندازه)
      أرجع MZ_FALSE;

    // Now create an index into the central directory file records, do some basic sanity checking on each record, and check for zip64 entries (which are not yet supported).
    p = (ثابت mz_uint8 *)pZip->m_pState->m_central_dir.m_p;
    لكل (n = cdir_اندازه, i = 0; i < pZip->m_ټول_files; ++i)
    {
      mz_uint ټول_سرلیک_اندازه, comp_اندازه, decomp_اندازه, disk_شاخص;
      إذا ((n < MZ_ZIP_CENTRAL_DIR_سرلیک_اندازه) || (MZ_READ_LE32(p) != MZ_ZIP_CENTRAL_DIR_سرلیک_SIG))
        أرجع MZ_FALSE;
      MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, i) = (mz_uint32)(p - (ثابت mz_uint8 *)pZip->m_pState->m_central_dir.m_p);
      إذا (ترتیبول_central_dir)
        MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_sorted_central_dir_offsets, mz_uint32, i) = i;
      comp_اندازه = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_اندازه_OFS);
      decomp_اندازه = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_اندازه_OFS);
      إذا (((!MZ_READ_LE32(p + MZ_ZIP_CDH_لاره_OFS)) && (decomp_اندازه != comp_اندازه)) || (decomp_اندازه && !comp_اندازه) || (decomp_اندازه == 0xFFFFFFFF) || (comp_اندازه == 0xFFFFFFFF))
        أرجع MZ_FALSE;
      disk_شاخص = MZ_READ_LE16(p + MZ_ZIP_CDH_DISK_پیل_OFS);
      إذا ((disk_شاخص != عدد_this_disk) && (disk_شاخص != 1))
        أرجع MZ_FALSE;
      إذا (((mz_uint64)MZ_READ_LE32(p + MZ_ZIP_CDH_LOCAL_سرلیک_OFS) + MZ_ZIP_LOCAL_DIR_سرلیک_اندازه + comp_اندازه) > pZip->m_archive_اندازه)
        أرجع MZ_FALSE;
      إذا ((ټول_سرلیک_اندازه = MZ_ZIP_CENTRAL_DIR_سرلیک_اندازه + MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_EXTRA_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_COMMENT_LEN_OFS)) > n)
        أرجع MZ_FALSE;
      n -= ټول_سرلیک_اندازه; p += ټول_سرلیک_اندازه;
    }
  }

  إذا (ترتیبول_central_dir)
    mz_zip_reader_ترتیبول_central_dir_offsets_by_filename(pZip);

  أرجع MZ_TRUE;
}

mz_bool mz_zip_reader_init(mz_zip_archive *pZip, mz_uint64 اندازه, mz_uint32 flags)
{
  إذا ((!pZip) || (!pZip->m_pRead))
    أرجع MZ_FALSE;
  إذا (!mz_zip_reader_init_دننی(pZip, flags))
    أرجع MZ_FALSE;
  pZip->m_archive_اندازه = اندازه;
  إذا (!mz_zip_reader_read_central_dir(pZip, flags))
  {
    mz_zip_reader_پای_ټکی(pZip);
    أرجع MZ_FALSE;
  }
  أرجع MZ_TRUE;
}

ساكن size_t mz_zip_mem_read_func(فراغ *pOpaque, mz_uint64 file_ofs, فراغ *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  size_t s = (file_ofs >= pZip->m_archive_اندازه) ? 0 : (size_t)MZ_MIN(pZip->m_archive_اندازه - file_ofs, n);
  حافظه_نقل(pBuf, (ثابت mz_uint8 *)pZip->m_pState->m_pMem + file_ofs, s);
  أرجع s;
}

mz_bool mz_zip_reader_init_mem(mz_zip_archive *pZip, ثابت فراغ *pMem, size_t اندازه, mz_uint32 flags)
{
  إذا (!mz_zip_reader_init_دننی(pZip, flags))
    أرجع MZ_FALSE;
  pZip->m_archive_اندازه = اندازه;
  pZip->m_pRead = mz_zip_mem_read_func;
  pZip->m_pIO_opaque = pZip;
#که_تعریف_شوی __cplusplus
  pZip->m_pState->m_pMem = const_cast<فراغ *>(pMem);
#وإلا
  pZip->m_pState->m_pMem = (فراغ *)pMem;
#د_که_پای
  pZip->m_pState->m_mem_اندازه = اندازه;
  إذا (!mz_zip_reader_read_central_dir(pZip, flags))
  {
    mz_zip_reader_پای_ټکی(pZip);
    أرجع MZ_FALSE;
  }
  أرجع MZ_TRUE;
}

#که_نه_تعریف_شوی MINIZ_NO_STDIO
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
  إذا (!mz_zip_reader_init_دننی(pZip, flags))
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
    mz_zip_reader_پای_ټکی(pZip);
    أرجع MZ_FALSE;
  }
  أرجع MZ_TRUE;
}
#د_که_پای // #ifndef MINIZ_NO_STDIO

mz_uint mz_zip_reader_get_عدد_files(mz_zip_archive *pZip)
{
  أرجع pZip ? pZip->m_ټول_files : 0;
}

ساكن MZ_FORCEINLINE ثابت mz_uint8 *mz_zip_reader_get_cdh(mz_zip_archive *pZip, mz_uint file_شاخص)
{
  إذا ((!pZip) || (!pZip->m_pState) || (file_شاخص >= pZip->m_ټول_files) || (pZip->m_zip_ډېرپېښ != MZ_ZIP_ډېرپېښ_READING))
    أرجع عدم;
  أرجع &MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_شاخص));
}

mz_bool mz_zip_reader_is_file_encrypted(mz_zip_archive *pZip, mz_uint file_شاخص)
{
  mz_uint m_بټ_flag;
  ثابت mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_شاخص);
  إذا (!p)
    أرجع MZ_FALSE;
  m_بټ_flag = MZ_READ_LE16(p + MZ_ZIP_CDH_بټ_FLAG_OFS);
  أرجع (m_بټ_flag & 1);
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
    إذا (*(p + MZ_ZIP_CENTRAL_DIR_سرلیک_اندازه + filename_len - 1) == '/')
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
  pStat->m_بټ_flag = MZ_READ_LE16(p + MZ_ZIP_CDH_بټ_FLAG_OFS);
  pStat->m_لاره = MZ_READ_LE16(p + MZ_ZIP_CDH_لاره_OFS);
#که_نه_تعریف_شوی MINIZ_NO_وخت
  pStat->m_وخت = mz_zip_dos_منزل_وخت_t(MZ_READ_LE16(p + MZ_ZIP_CDH_FILE_وخت_OFS), MZ_READ_LE16(p + MZ_ZIP_CDH_FILE_DATE_OFS));
#د_که_پای
  pStat->m_دوراني_ازموینه_32 = MZ_READ_LE32(p + MZ_ZIP_CDH_دوراني_ازموینه_32_OFS);
  pStat->m_comp_اندازه = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_اندازه_OFS);
  pStat->m_uncomp_اندازه = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_اندازه_OFS);
  pStat->m_دننی_attr = MZ_READ_LE16(p + MZ_ZIP_CDH_دننی_ATTR_OFS);
  pStat->m_external_attr = MZ_READ_LE32(p + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS);
  pStat->m_local_سرلیک_ofs = MZ_READ_LE32(p + MZ_ZIP_CDH_LOCAL_سرلیک_OFS);

  // Copy as much of the filename and comment as possible.
  n = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS); n = MZ_MIN(n, MZ_ZIP_MAX_ARCHIVE_FILENAME_اندازه - 1);
  حافظه_نقل(pStat->m_filename, p + MZ_ZIP_CENTRAL_DIR_سرلیک_اندازه, n); pStat->m_filename[n] = '\0';

  n = MZ_READ_LE16(p + MZ_ZIP_CDH_COMMENT_LEN_OFS); n = MZ_MIN(n, MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_اندازه - 1);
  pStat->m_comment_اندازه = n;
  حافظه_نقل(pStat->m_comment, p + MZ_ZIP_CENTRAL_DIR_سرلیک_اندازه + MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_EXTRA_LEN_OFS), n); pStat->m_comment[n] = '\0';

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
    حافظه_نقل(pFilename, p + MZ_ZIP_CENTRAL_DIR_سرلیک_اندازه, n);
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
  pL += MZ_ZIP_CENTRAL_DIR_سرلیک_اندازه;
  pE = pL + MZ_MIN(l_len, r_len);
  طالما (pL < pE)
  {
    إذا ((l = MZ_TOLOWER(*pL)) != (r = MZ_TOLOWER(*pR)))
      اكسر;
    pL++; pR++;
  }
  أرجع (pL == pE) ? (صحيح)(l_len - r_len) : (l - r);
}

ساكن صحيح mz_zip_reader_locate_file_دوګونی_پلټنه(mz_zip_archive *pZip, ثابت حرف *pFilename)
{
  mz_zip_دننی_state *pState = pZip->m_pState;
  ثابت mz_zip_array *pCentral_dir_offsets = &pState->m_central_dir_offsets;
  ثابت mz_zip_array *pCentral_dir = &pState->m_central_dir;
  mz_uint32 *pIndices = &MZ_ZIP_ARRAY_ELEMENT(&pState->m_sorted_central_dir_offsets, mz_uint32, 0);
  ثابت صحيح اندازه = pZip->m_ټول_files;
  ثابت mz_uint filename_len = (mz_uint)مزي_اوږدوالی(pFilename);
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
  إذا ((!pZip) || (!pZip->m_pState) || (!pName) || (pZip->m_zip_ډېرپېښ != MZ_ZIP_ډېرپېښ_READING))
    أرجع -1;
  إذا (((flags & (MZ_ZIP_FLAG_IGNORE_لار | MZ_ZIP_FLAG_CASE_SENSITIVE)) == 0) && (!pComment) && (pZip->m_pState->m_sorted_central_dir_offsets.m_اندازه))
    أرجع mz_zip_reader_locate_file_دوګونی_پلټنه(pZip, pName);
  name_len = مزي_اوږدوالی(pName); إذا (name_len > 0xFFFF) أرجع -1;
  comment_len = pComment ? مزي_اوږدوالی(pComment) : 0; إذا (comment_len > 0xFFFF) أرجع -1;
  لكل (file_شاخص = 0; file_شاخص < pZip->m_ټول_files; file_شاخص++)
  {
    ثابت mz_uint8 *p_سرلیک = &MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_شاخص));
    mz_uint filename_len = MZ_READ_LE16(p_سرلیک + MZ_ZIP_CDH_FILENAME_LEN_OFS);
    ثابت حرف *pFilename = (ثابت حرف *)p_سرلیک + MZ_ZIP_CENTRAL_DIR_سرلیک_اندازه;
    إذا (filename_len < name_len)
      استمر;
    إذا (comment_len)
    {
      mz_uint file_extra_len = MZ_READ_LE16(p_سرلیک + MZ_ZIP_CDH_EXTRA_LEN_OFS), file_comment_len = MZ_READ_LE16(p_سرلیک + MZ_ZIP_CDH_COMMENT_LEN_OFS);
      ثابت حرف *pFile_comment = pFilename + filename_len + file_extra_len;
      إذا ((file_comment_len != comment_len) || (!mz_zip_reader_string_equal(pComment, pFile_comment, file_comment_len, flags)))
        استمر;
    }
    إذا ((flags & MZ_ZIP_FLAG_IGNORE_لار) && (filename_len))
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

mz_bool mz_zip_reader_ایستل_منزل_mem_no_alloc(mz_zip_archive *pZip, mz_uint file_شاخص, فراغ *pBuf, size_t buf_اندازه_2, mz_uint flags, فراغ *pUser_read_buf, size_t user_read_buf_اندازه)
{
  صحيح حالت = TINFL_حالت_بشپړ;
  mz_uint64 needed_اندازه, cur_file_ofs, comp_پاتې_شوی, بهر_buf_ofs = 0, read_buf_اندازه, read_buf_ofs = 0, read_buf_avail;
  mz_zip_archive_file_stat file_stat;
  فراغ *pRead_buf;
  mz_uint32 local_سرلیک_u32[(MZ_ZIP_LOCAL_DIR_سرلیک_اندازه + حجم(mz_uint32) - 1) / حجم(mz_uint32)]; mz_uint8 *p_Local_سرلیک = (mz_uint8 *)local_سرلیک_u32;
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
  إذا (file_stat.m_بټ_flag & (1 | 32))
    أرجع MZ_FALSE;

  // This function only supports stored and deflate.
  إذا ((!(flags & MZ_ZIP_FLAG_COMPRESSED_معلومات)) && (file_stat.m_لاره != 0) && (file_stat.m_لاره != MZ_DEFLATED))
    أرجع MZ_FALSE;

  // Ensure supplied output buffer is large enough.
  needed_اندازه = (flags & MZ_ZIP_FLAG_COMPRESSED_معلومات) ? file_stat.m_comp_اندازه : file_stat.m_uncomp_اندازه;
  إذا (buf_اندازه_2 < needed_اندازه)
    أرجع MZ_FALSE;

  // Read and parse the local directory entry.
  cur_file_ofs = file_stat.m_local_سرلیک_ofs;
  إذا (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, p_Local_سرلیک, MZ_ZIP_LOCAL_DIR_سرلیک_اندازه) != MZ_ZIP_LOCAL_DIR_سرلیک_اندازه)
    أرجع MZ_FALSE;
  إذا (MZ_READ_LE32(p_Local_سرلیک) != MZ_ZIP_LOCAL_DIR_سرلیک_SIG)
    أرجع MZ_FALSE;

  cur_file_ofs += MZ_ZIP_LOCAL_DIR_سرلیک_اندازه + MZ_READ_LE16(p_Local_سرلیک + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p_Local_سرلیک + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  إذا ((cur_file_ofs + file_stat.m_comp_اندازه) > pZip->m_archive_اندازه)
    أرجع MZ_FALSE;

  إذا ((flags & MZ_ZIP_FLAG_COMPRESSED_معلومات) || (!file_stat.m_لاره))
  {
    // The file is stored or the caller has requested the compressed data.
    إذا (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, (size_t)needed_اندازه) != needed_اندازه)
      أرجع MZ_FALSE;
    أرجع ((flags & MZ_ZIP_FLAG_COMPRESSED_معلومات) != 0) || (mz_دوراني_ازموینه_32(MZ_دوراني_ازموینه_32_INIT, (ثابت mz_uint8 *)pBuf, (size_t)file_stat.m_uncomp_اندازه) == file_stat.m_دوراني_ازموینه_32);
  }

  // Decompress the file either directly from memory or from a file input buffer.
  tinfl_init(&inflator);

  إذا (pZip->m_pState->m_pMem)
  {
    // Read directly from the archive in memory.
    pRead_buf = (mz_uint8 *)pZip->m_pState->m_pMem + cur_file_ofs;
    read_buf_اندازه = read_buf_avail = file_stat.m_comp_اندازه;
    comp_پاتې_شوی = 0;
  }
  وإلا إذا (pUser_read_buf)
  {
    // Use a user provided read buffer.
    إذا (!user_read_buf_اندازه)
      أرجع MZ_FALSE;
    pRead_buf = (mz_uint8 *)pUser_read_buf;
    read_buf_اندازه = user_read_buf_اندازه;
    read_buf_avail = 0;
    comp_پاتې_شوی = file_stat.m_comp_اندازه;
  }
  وإلا
  {
    // Temporarily allocate a read buffer.
    read_buf_اندازه = MZ_MIN(file_stat.m_comp_اندازه, MZ_ZIP_MAX_IO_BUF_اندازه);
#که_تعریف_شوی _MSC_VER
    إذا (((0, حجم(size_t) == حجم(mz_uint32))) && (read_buf_اندازه > 0x7FFFFFFF))
#وإلا
    إذا (((حجم(size_t) == حجم(mz_uint32))) && (read_buf_اندازه > 0x7FFFFFFF))
#د_که_پای
      أرجع MZ_FALSE;
    إذا (عدم == (pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)read_buf_اندازه)))
      أرجع MZ_FALSE;
    read_buf_avail = 0;
    comp_پاتې_شوی = file_stat.m_comp_اندازه;
  }

  افعل
  {
    size_t دننه_buf_اندازه, بهر_buf_اندازه = (size_t)(file_stat.m_uncomp_اندازه - بهر_buf_ofs);
    إذا ((!read_buf_avail) && (!pZip->m_pState->m_pMem))
    {
      read_buf_avail = MZ_MIN(read_buf_اندازه, comp_پاتې_شوی);
      إذا (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
      {
        حالت = TINFL_حالت_FAILED;
        اكسر;
      }
      cur_file_ofs += read_buf_avail;
      comp_پاتې_شوی -= read_buf_avail;
      read_buf_ofs = 0;
    }
    دننه_buf_اندازه = (size_t)read_buf_avail;
    حالت = tinfl_decompress(&inflator, (mz_uint8 *)pRead_buf + read_buf_ofs, &دننه_buf_اندازه, (mz_uint8 *)pBuf, (mz_uint8 *)pBuf + بهر_buf_ofs, &بهر_buf_اندازه, TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF | (comp_پاتې_شوی ? TINFL_FLAG_HAS_نور_ننوت : 0));
    read_buf_avail -= دننه_buf_اندازه;
    read_buf_ofs += دننه_buf_اندازه;
    بهر_buf_ofs += بهر_buf_اندازه;
  } طالما (حالت == TINFL_حالت_NEEDS_نور_ننوت);

  إذا (حالت == TINFL_حالت_بشپړ)
  {
    // Make sure the entire file was decompressed, and check its CRC.
    إذا ((بهر_buf_ofs != file_stat.m_uncomp_اندازه) || (mz_دوراني_ازموینه_32(MZ_دوراني_ازموینه_32_INIT, (ثابت mz_uint8 *)pBuf, (size_t)file_stat.m_uncomp_اندازه) != file_stat.m_دوراني_ازموینه_32))
      حالت = TINFL_حالت_FAILED;
  }

  إذا ((!pZip->m_pState->m_pMem) && (!pUser_read_buf))
    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);

  أرجع حالت == TINFL_حالت_بشپړ;
}

mz_bool mz_zip_reader_ایستل_file_منزل_mem_no_alloc(mz_zip_archive *pZip, ثابت حرف *pFilename, فراغ *pBuf, size_t buf_اندازه_2, mz_uint flags, فراغ *pUser_read_buf, size_t user_read_buf_اندازه)
{
  صحيح file_شاخص = mz_zip_reader_locate_file(pZip, pFilename, عدم, flags);
  إذا (file_شاخص < 0)
    أرجع MZ_FALSE;
  أرجع mz_zip_reader_ایستل_منزل_mem_no_alloc(pZip, file_شاخص, pBuf, buf_اندازه_2, flags, pUser_read_buf, user_read_buf_اندازه);
}

mz_bool mz_zip_reader_ایستل_منزل_mem(mz_zip_archive *pZip, mz_uint file_شاخص, فراغ *pBuf, size_t buf_اندازه_2, mz_uint flags)
{
  أرجع mz_zip_reader_ایستل_منزل_mem_no_alloc(pZip, file_شاخص, pBuf, buf_اندازه_2, flags, عدم, 0);
}

mz_bool mz_zip_reader_ایستل_file_منزل_mem(mz_zip_archive *pZip, ثابت حرف *pFilename, فراغ *pBuf, size_t buf_اندازه_2, mz_uint flags)
{
  أرجع mz_zip_reader_ایستل_file_منزل_mem_no_alloc(pZip, pFilename, pBuf, buf_اندازه_2, flags, عدم, 0);
}

فراغ *mz_zip_reader_ایستل_منزل_ډېرۍ(mz_zip_archive *pZip, mz_uint file_شاخص, size_t *p_اندازه, mz_uint flags)
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

  alloc_اندازه_2 = (flags & MZ_ZIP_FLAG_COMPRESSED_معلومات) ? comp_اندازه : uncomp_اندازه;
#که_تعریف_شوی _MSC_VER
  إذا (((0, حجم(size_t) == حجم(mz_uint32))) && (alloc_اندازه_2 > 0x7FFFFFFF))
#وإلا
  إذا (((حجم(size_t) == حجم(mz_uint32))) && (alloc_اندازه_2 > 0x7FFFFFFF))
#د_که_پای
    أرجع عدم;
  إذا (عدم == (pBuf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)alloc_اندازه_2)))
    أرجع عدم;

  إذا (!mz_zip_reader_ایستل_منزل_mem(pZip, file_شاخص, pBuf, (size_t)alloc_اندازه_2, flags))
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
    أرجع عدم;
  }

  إذا (p_اندازه) *p_اندازه = (size_t)alloc_اندازه_2;
  أرجع pBuf;
}

فراغ *mz_zip_reader_ایستل_file_منزل_ډېرۍ(mz_zip_archive *pZip, ثابت حرف *pFilename, size_t *p_اندازه, mz_uint flags)
{
  صحيح file_شاخص = mz_zip_reader_locate_file(pZip, pFilename, عدم, flags);
  إذا (file_شاخص < 0)
  {
    إذا (p_اندازه) *p_اندازه = 0;
    أرجع MZ_FALSE;
  }
  أرجع mz_zip_reader_ایستل_منزل_ډېرۍ(pZip, file_شاخص, p_اندازه, flags);
}

mz_bool mz_zip_reader_ایستل_منزل_callback(mz_zip_archive *pZip, mz_uint file_شاخص, mz_file_write_func pCallback, فراغ *pOpaque, mz_uint flags)
{
  صحيح حالت = TINFL_حالت_بشپړ; mz_uint file_دوراني_ازموینه_32 = MZ_دوراني_ازموینه_32_INIT;
  mz_uint64 read_buf_اندازه, read_buf_ofs = 0, read_buf_avail, comp_پاتې_شوی, بهر_buf_ofs = 0, cur_file_ofs;
  mz_zip_archive_file_stat file_stat;
  فراغ *pRead_buf = عدم; فراغ *pWrite_buf = عدم;
  mz_uint32 local_سرلیک_u32[(MZ_ZIP_LOCAL_DIR_سرلیک_اندازه + حجم(mz_uint32) - 1) / حجم(mz_uint32)]; mz_uint8 *p_Local_سرلیک = (mz_uint8 *)local_سرلیک_u32;

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
  إذا (file_stat.m_بټ_flag & (1 | 32))
    أرجع MZ_FALSE;

  // This function only supports stored and deflate.
  إذا ((!(flags & MZ_ZIP_FLAG_COMPRESSED_معلومات)) && (file_stat.m_لاره != 0) && (file_stat.m_لاره != MZ_DEFLATED))
    أرجع MZ_FALSE;

  // Read and parse the local directory entry.
  cur_file_ofs = file_stat.m_local_سرلیک_ofs;
  إذا (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, p_Local_سرلیک, MZ_ZIP_LOCAL_DIR_سرلیک_اندازه) != MZ_ZIP_LOCAL_DIR_سرلیک_اندازه)
    أرجع MZ_FALSE;
  إذا (MZ_READ_LE32(p_Local_سرلیک) != MZ_ZIP_LOCAL_DIR_سرلیک_SIG)
    أرجع MZ_FALSE;

  cur_file_ofs += MZ_ZIP_LOCAL_DIR_سرلیک_اندازه + MZ_READ_LE16(p_Local_سرلیک + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p_Local_سرلیک + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  إذا ((cur_file_ofs + file_stat.m_comp_اندازه) > pZip->m_archive_اندازه)
    أرجع MZ_FALSE;

  // Decompress the file either directly from memory or from a file input buffer.
  إذا (pZip->m_pState->m_pMem)
  {
    pRead_buf = (mz_uint8 *)pZip->m_pState->m_pMem + cur_file_ofs;
    read_buf_اندازه = read_buf_avail = file_stat.m_comp_اندازه;
    comp_پاتې_شوی = 0;
  }
  وإلا
  {
    read_buf_اندازه = MZ_MIN(file_stat.m_comp_اندازه, MZ_ZIP_MAX_IO_BUF_اندازه);
    إذا (عدم == (pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)read_buf_اندازه)))
      أرجع MZ_FALSE;
    read_buf_avail = 0;
    comp_پاتې_شوی = file_stat.m_comp_اندازه;
  }

  إذا ((flags & MZ_ZIP_FLAG_COMPRESSED_معلومات) || (!file_stat.m_لاره))
  {
    // The file is stored or the caller has requested the compressed data.
    إذا (pZip->m_pState->m_pMem)
    {
#که_تعریف_شوی _MSC_VER
      إذا (((0, حجم(size_t) == حجم(mz_uint32))) && (file_stat.m_comp_اندازه > 0xFFFFFFFF))
#وإلا
      إذا (((حجم(size_t) == حجم(mz_uint32))) && (file_stat.m_comp_اندازه > 0xFFFFFFFF))
#د_که_پای
        أرجع MZ_FALSE;
      إذا (pCallback(pOpaque, بهر_buf_ofs, pRead_buf, (size_t)file_stat.m_comp_اندازه) != file_stat.m_comp_اندازه)
        حالت = TINFL_حالت_FAILED;
      وإلا إذا (!(flags & MZ_ZIP_FLAG_COMPRESSED_معلومات))
        file_دوراني_ازموینه_32 = (mz_uint32)mz_دوراني_ازموینه_32(file_دوراني_ازموینه_32, (ثابت mz_uint8 *)pRead_buf, (size_t)file_stat.m_comp_اندازه);
      cur_file_ofs += file_stat.m_comp_اندازه;
      بهر_buf_ofs += file_stat.m_comp_اندازه;
      comp_پاتې_شوی = 0;
    }
    وإلا
    {
      طالما (comp_پاتې_شوی)
      {
        read_buf_avail = MZ_MIN(read_buf_اندازه, comp_پاتې_شوی);
        إذا (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
        {
          حالت = TINFL_حالت_FAILED;
          اكسر;
        }

        إذا (!(flags & MZ_ZIP_FLAG_COMPRESSED_معلومات))
          file_دوراني_ازموینه_32 = (mz_uint32)mz_دوراني_ازموینه_32(file_دوراني_ازموینه_32, (ثابت mz_uint8 *)pRead_buf, (size_t)read_buf_avail);

        إذا (pCallback(pOpaque, بهر_buf_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
        {
          حالت = TINFL_حالت_FAILED;
          اكسر;
        }
        cur_file_ofs += read_buf_avail;
        بهر_buf_ofs += read_buf_avail;
        comp_پاتې_شوی -= read_buf_avail;
      }
    }
  }
  وإلا
  {
    tinfl_decompressor inflator;
    tinfl_init(&inflator);

    إذا (عدم == (pWrite_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, TINFL_LZ_DICT_اندازه)))
      حالت = TINFL_حالت_FAILED;
    وإلا
    {
      افعل
      {
        mz_uint8 *pWrite_buf_cur = (mz_uint8 *)pWrite_buf + (بهر_buf_ofs & (TINFL_LZ_DICT_اندازه - 1));
        size_t دننه_buf_اندازه, بهر_buf_اندازه = TINFL_LZ_DICT_اندازه - (بهر_buf_ofs & (TINFL_LZ_DICT_اندازه - 1));
        إذا ((!read_buf_avail) && (!pZip->m_pState->m_pMem))
        {
          read_buf_avail = MZ_MIN(read_buf_اندازه, comp_پاتې_شوی);
          إذا (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
          {
            حالت = TINFL_حالت_FAILED;
            اكسر;
          }
          cur_file_ofs += read_buf_avail;
          comp_پاتې_شوی -= read_buf_avail;
          read_buf_ofs = 0;
        }

        دننه_buf_اندازه = (size_t)read_buf_avail;
        حالت = tinfl_decompress(&inflator, (ثابت mz_uint8 *)pRead_buf + read_buf_ofs, &دننه_buf_اندازه, (mz_uint8 *)pWrite_buf, pWrite_buf_cur, &بهر_buf_اندازه, comp_پاتې_شوی ? TINFL_FLAG_HAS_نور_ننوت : 0);
        read_buf_avail -= دننه_buf_اندازه;
        read_buf_ofs += دننه_buf_اندازه;

        إذا (بهر_buf_اندازه)
        {
          إذا (pCallback(pOpaque, بهر_buf_ofs, pWrite_buf_cur, بهر_buf_اندازه) != بهر_buf_اندازه)
          {
            حالت = TINFL_حالت_FAILED;
            اكسر;
          }
          file_دوراني_ازموینه_32 = (mz_uint32)mz_دوراني_ازموینه_32(file_دوراني_ازموینه_32, pWrite_buf_cur, بهر_buf_اندازه);
          إذا ((بهر_buf_ofs += بهر_buf_اندازه) > file_stat.m_uncomp_اندازه)
          {
            حالت = TINFL_حالت_FAILED;
            اكسر;
          }
        }
      } طالما ((حالت == TINFL_حالت_NEEDS_نور_ننوت) || (حالت == TINFL_حالت_HAS_نور_OUTPUT));
    }
  }

  إذا ((حالت == TINFL_حالت_بشپړ) && (!(flags & MZ_ZIP_FLAG_COMPRESSED_معلومات)))
  {
    // Make sure the entire file was decompressed, and check its CRC.
    إذا ((بهر_buf_ofs != file_stat.m_uncomp_اندازه) || (file_دوراني_ازموینه_32 != file_stat.m_دوراني_ازموینه_32))
      حالت = TINFL_حالت_FAILED;
  }

  إذا (!pZip->m_pState->m_pMem)
    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
  إذا (pWrite_buf)
    pZip->m_pFree(pZip->m_pAlloc_opaque, pWrite_buf);

  أرجع حالت == TINFL_حالت_بشپړ;
}

mz_bool mz_zip_reader_ایستل_file_منزل_callback(mz_zip_archive *pZip, ثابت حرف *pFilename, mz_file_write_func pCallback, فراغ *pOpaque, mz_uint flags)
{
  صحيح file_شاخص = mz_zip_reader_locate_file(pZip, pFilename, عدم, flags);
  إذا (file_شاخص < 0)
    أرجع MZ_FALSE;
  أرجع mz_zip_reader_ایستل_منزل_callback(pZip, file_شاخص, pCallback, pOpaque, flags);
}

#که_نه_تعریف_شوی MINIZ_NO_STDIO
ساكن size_t mz_zip_file_write_callback(فراغ *pOpaque, mz_uint64 ofs, ثابت فراغ *pBuf, size_t n)
{
  (فراغ)ofs; أرجع MZ_FWRITE(pBuf, 1, n, (MZ_FILE*)pOpaque);
}

mz_bool mz_zip_reader_ایستل_منزل_file(mz_zip_archive *pZip, mz_uint file_شاخص, ثابت حرف *pDst_filename, mz_uint flags)
{
  mz_bool حالت;
  mz_zip_archive_file_stat file_stat;
  MZ_FILE *pFile;
  إذا (!mz_zip_reader_file_stat(pZip, file_شاخص, &file_stat))
    أرجع MZ_FALSE;
  pFile = MZ_FOPEN(pDst_filename, "wb");
  إذا (!pFile)
    أرجع MZ_FALSE;
  حالت = mz_zip_reader_ایستل_منزل_callback(pZip, file_شاخص, mz_zip_file_write_callback, pFile, flags);
  إذا (MZ_FCLOSE(pFile) == EOF)
    أرجع MZ_FALSE;
#که_نه_تعریف_شوی MINIZ_NO_وخت
  إذا (حالت)
    mz_zip_سېټ_file_times(pDst_filename, file_stat.m_وخت, file_stat.m_وخت);
#د_که_پای
  أرجع حالت;
}
#د_که_پای // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_reader_پای_ټکی(mz_zip_archive *pZip)
{
  إذا ((!pZip) || (!pZip->m_pState) || (!pZip->m_pAlloc) || (!pZip->m_pFree) || (pZip->m_zip_ډېرپېښ != MZ_ZIP_ډېرپېښ_READING))
    أرجع MZ_FALSE;

  إذا (pZip->m_pState)
  {
    mz_zip_دننی_state *pState = pZip->m_pState; pZip->m_pState = عدم;
    mz_zip_array_clear(pZip, &pState->m_central_dir);
    mz_zip_array_clear(pZip, &pState->m_central_dir_offsets);
    mz_zip_array_clear(pZip, &pState->m_sorted_central_dir_offsets);

#که_نه_تعریف_شوی MINIZ_NO_STDIO
    إذا (pState->m_pFile)
    {
      MZ_FCLOSE(pState->m_pFile);
      pState->m_pFile = عدم;
    }
#د_که_پای // #ifndef MINIZ_NO_STDIO

    pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
  }
  pZip->m_zip_ډېرپېښ = MZ_ZIP_ډېرپېښ_INVALID;

  أرجع MZ_TRUE;
}

#که_نه_تعریف_شوی MINIZ_NO_STDIO
mz_bool mz_zip_reader_ایستل_file_منزل_file(mz_zip_archive *pZip, ثابت حرف *pArchive_filename, ثابت حرف *pDst_filename, mz_uint flags)
{
  صحيح file_شاخص = mz_zip_reader_locate_file(pZip, pArchive_filename, عدم, flags);
  إذا (file_شاخص < 0)
    أرجع MZ_FALSE;
  أرجع mz_zip_reader_ایستل_منزل_file(pZip, file_شاخص, pDst_filename, flags);
}
#د_که_پای

// ------------------- .ZIP archive writing

#که_نه_تعریف_شوی MINIZ_NO_ARCHIVE_WRITING_APIS

ساكن فراغ mz_write_le16(mz_uint8 *p, mz_uint16 v) { p[0] = (mz_uint8)v; p[1] = (mz_uint8)(v >> 8); }
ساكن فراغ mz_write_le32(mz_uint8 *p, mz_uint32 v) { p[0] = (mz_uint8)v; p[1] = (mz_uint8)(v >> 8); p[2] = (mz_uint8)(v >> 16); p[3] = (mz_uint8)(v >> 24); }
#تعریف_کړه MZ_WRITE_LE16(p, v) mz_write_le16((mz_uint8 *)(p), (mz_uint16)(v))
#تعریف_کړه MZ_WRITE_LE32(p, v) mz_write_le32((mz_uint8 *)(p), (mz_uint32)(v))

mz_bool mz_zip_writer_init(mz_zip_archive *pZip, mz_uint64 existing_اندازه)
{
  إذا ((!pZip) || (pZip->m_pState) || (!pZip->m_pWrite) || (pZip->m_zip_ډېرپېښ != MZ_ZIP_ډېرپېښ_INVALID))
    أرجع MZ_FALSE;

  إذا (pZip->m_file_دننه_واټن_alignment)
  {
    // Ensure user specified file offset alignment is a power of 2.
    إذا (pZip->m_file_دننه_واټن_alignment & (pZip->m_file_دننه_واټن_alignment - 1))
      أرجع MZ_FALSE;
  }

  إذا (!pZip->m_pAlloc) pZip->m_pAlloc = def_alloc_func;
  إذا (!pZip->m_pFree) pZip->m_pFree = def_free_func;
  إذا (!pZip->m_pRealloc) pZip->m_pRealloc = def_realloc_func;

  pZip->m_zip_ډېرپېښ = MZ_ZIP_ډېرپېښ_WRITING;
  pZip->m_archive_اندازه = existing_اندازه;
  pZip->m_central_directory_file_ofs = 0;
  pZip->m_ټول_files = 0;

  إذا (عدم == (pZip->m_pState = (mz_zip_دننی_state *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, حجم(mz_zip_دننی_state))))
    أرجع MZ_FALSE;
  memset(pZip->m_pState, 0, حجم(mz_zip_دننی_state));
  MZ_ZIP_ARRAY_سېټ_ELEMENT_اندازه(&pZip->m_pState->m_central_dir, حجم(mz_uint8));
  MZ_ZIP_ARRAY_سېټ_ELEMENT_اندازه(&pZip->m_pState->m_central_dir_offsets, حجم(mz_uint32));
  MZ_ZIP_ARRAY_سېټ_ELEMENT_اندازه(&pZip->m_pState->m_sorted_central_dir_offsets, حجم(mz_uint32));
  أرجع MZ_TRUE;
}

ساكن size_t mz_zip_ډېرۍ_write_func(فراغ *pOpaque, mz_uint64 file_ofs, ثابت فراغ *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_zip_دننی_state *pState = pZip->m_pState;
  mz_uint64 new_اندازه = MZ_MAX(file_ofs + n, pState->m_mem_اندازه);
#که_تعریف_شوی _MSC_VER
  إذا ((!n) || ((0, حجم(size_t) == حجم(mz_uint32)) && (new_اندازه > 0x7FFFFFFF)))
#وإلا
  إذا ((!n) || ((حجم(size_t) == حجم(mz_uint32)) && (new_اندازه > 0x7FFFFFFF)))
#د_که_پای
    أرجع 0;
  إذا (new_اندازه > pState->m_mem_ظرفیت)
  {
    فراغ *p_New_بلاک;
    size_t new_ظرفیت = MZ_MAX(64, pState->m_mem_ظرفیت); طالما (new_ظرفیت < new_اندازه) new_ظرفیت *= 2;
    إذا (عدم == (p_New_بلاک = pZip->m_pRealloc(pZip->m_pAlloc_opaque, pState->m_pMem, 1, new_ظرفیت)))
      أرجع 0;
    pState->m_pMem = p_New_بلاک; pState->m_mem_ظرفیت = new_ظرفیت;
  }
  حافظه_نقل((mz_uint8 *)pState->m_pMem + file_ofs, pBuf, n);
  pState->m_mem_اندازه = (size_t)new_اندازه;
  أرجع n;
}

mz_bool mz_zip_writer_init_ډېرۍ(mz_zip_archive *pZip, size_t اندازه_منزل_reserve_at_beginning, size_t initial_ویش_اندازه)
{
  pZip->m_pWrite = mz_zip_ډېرۍ_write_func;
  pZip->m_pIO_opaque = pZip;
  إذا (!mz_zip_writer_init(pZip, اندازه_منزل_reserve_at_beginning))
    أرجع MZ_FALSE;
  إذا (0 != (initial_ویش_اندازه = MZ_MAX(initial_ویش_اندازه, اندازه_منزل_reserve_at_beginning)))
  {
    إذا (عدم == (pZip->m_pState->m_pMem = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, initial_ویش_اندازه)))
    {
      mz_zip_writer_پای_ټکی(pZip);
      أرجع MZ_FALSE;
    }
    pZip->m_pState->m_mem_ظرفیت = initial_ویش_اندازه;
  }
  أرجع MZ_TRUE;
}

#که_نه_تعریف_شوی MINIZ_NO_STDIO
ساكن size_t mz_zip_file_write_func(فراغ *pOpaque, mz_uint64 file_ofs, ثابت فراغ *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_int64 cur_ofs = MZ_FTELL64(pZip->m_pState->m_pFile);
  إذا (((mz_int64)file_ofs < 0) || (((cur_ofs != (mz_int64)file_ofs)) && (MZ_FSEEK64(pZip->m_pState->m_pFile, (mz_int64)file_ofs, SEEK_SET))))
    أرجع 0;
  أرجع MZ_FWRITE(pBuf, 1, n, pZip->m_pState->m_pFile);
}

mz_bool mz_zip_writer_init_file(mz_zip_archive *pZip, ثابت حرف *pFilename, mz_uint64 اندازه_منزل_reserve_at_beginning)
{
  MZ_FILE *pFile;
  pZip->m_pWrite = mz_zip_file_write_func;
  pZip->m_pIO_opaque = pZip;
  إذا (!mz_zip_writer_init(pZip, اندازه_منزل_reserve_at_beginning))
    أرجع MZ_FALSE;
  إذا (عدم == (pFile = MZ_FOPEN(pFilename, "wb")))
  {
    mz_zip_writer_پای_ټکی(pZip);
    أرجع MZ_FALSE;
  }
  pZip->m_pState->m_pFile = pFile;
  إذا (اندازه_منزل_reserve_at_beginning)
  {
    mz_uint64 cur_ofs = 0; حرف buf[4096]; MZ_CLEAR_ARR(buf);
    افعل
    {
      size_t n = (size_t)MZ_MIN(حجم(buf), اندازه_منزل_reserve_at_beginning);
      إذا (pZip->m_pWrite(pZip->m_pIO_opaque, cur_ofs, buf, n) != n)
      {
        mz_zip_writer_پای_ټکی(pZip);
        أرجع MZ_FALSE;
      }
      cur_ofs += n; اندازه_منزل_reserve_at_beginning -= n;
    } طالما (اندازه_منزل_reserve_at_beginning);
  }
  أرجع MZ_TRUE;
}
#د_که_پای // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_writer_init_from_reader(mz_zip_archive *pZip, ثابت حرف *pFilename)
{
  mz_zip_دننی_state *pState;
  إذا ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_ډېرپېښ != MZ_ZIP_ډېرپېښ_READING))
    أرجع MZ_FALSE;
  // No sense in trying to write to an archive that's already at the support max size
  إذا ((pZip->m_ټول_files == 0xFFFF) || ((pZip->m_archive_اندازه + MZ_ZIP_CENTRAL_DIR_سرلیک_اندازه + MZ_ZIP_LOCAL_DIR_سرلیک_اندازه) > 0xFFFFFFFF))
    أرجع MZ_FALSE;

  pState = pZip->m_pState;

  إذا (pState->m_pFile)
  {
#که_تعریف_شوی MINIZ_NO_STDIO
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
      mz_zip_reader_پای_ټکی(pZip);
      أرجع MZ_FALSE;
    }
#د_که_پای // #ifdef MINIZ_NO_STDIO
  }
  وإلا إذا (pState->m_pMem)
  {
    // Archive lives in a memory block. Assume it's from the heap that we can resize using the realloc callback.
    إذا (pZip->m_pIO_opaque != pZip)
      أرجع MZ_FALSE;
    pState->m_mem_ظرفیت = pState->m_mem_اندازه;
    pZip->m_pWrite = mz_zip_ډېرۍ_write_func;
  }
  // Archive is being read via a user provided read function - make sure the user has specified a write function too.
  وإلا إذا (!pZip->m_pWrite)
    أرجع MZ_FALSE;

  // Start writing new files at the archive's current central directory location.
  pZip->m_archive_اندازه = pZip->m_central_directory_file_ofs;
  pZip->m_zip_ډېرپېښ = MZ_ZIP_ډېرپېښ_WRITING;
  pZip->m_central_directory_file_ofs = 0;

  أرجع MZ_TRUE;
}

mz_bool mz_zip_writer_جمع_کړه_mem(mz_zip_archive *pZip, ثابت حرف *pArchive_name, ثابت فراغ *pBuf, size_t buf_اندازه_2, mz_uint level_and_flags)
{
  أرجع mz_zip_writer_جمع_کړه_mem_ex(pZip, pArchive_name, pBuf, buf_اندازه_2, عدم, 0, level_and_flags, 0, 0);
}

تعريفنوع بنية
{
  mz_zip_archive *m_pZip;
  mz_uint64 m_cur_archive_file_ofs;
  mz_uint64 m_comp_اندازه;
} mz_zip_writer_جمع_کړه_state;

ساكن mz_bool mz_zip_writer_جمع_کړه_put_buf_callback(ثابت فراغ* pBuf, صحيح len, فراغ *pUser)
{
  mz_zip_writer_جمع_کړه_state *pState = (mz_zip_writer_جمع_کړه_state *)pUser;
  إذا ((صحيح)pState->m_pZip->m_pWrite(pState->m_pZip->m_pIO_opaque, pState->m_cur_archive_file_ofs, pBuf, len) != len)
    أرجع MZ_FALSE;
  pState->m_cur_archive_file_ofs += len;
  pState->m_comp_اندازه += len;
  أرجع MZ_TRUE;
}

ساكن mz_bool mz_zip_writer_create_local_dir_سرلیک(mz_zip_archive *pZip, mz_uint8 *pDst, mz_uint16 filename_اندازه, mz_uint16 extra_اندازه, mz_uint64 uncomp_اندازه, mz_uint64 comp_اندازه, mz_uint32 uncomp_دوراني_ازموینه_32, mz_uint16 لاره, mz_uint16 بټ_flags, mz_uint16 dos_وخت, mz_uint16 dos_date)
{
  (فراغ)pZip;
  memset(pDst, 0, MZ_ZIP_LOCAL_DIR_سرلیک_اندازه);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_SIG_OFS, MZ_ZIP_LOCAL_DIR_سرلیک_SIG);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_نسخه_NEEDED_OFS, لاره ? 20 : 0);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_بټ_FLAG_OFS, بټ_flags);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_لاره_OFS, لاره);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILE_وخت_OFS, dos_وخت);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILE_DATE_OFS, dos_date);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_دوراني_ازموینه_32_OFS, uncomp_دوراني_ازموینه_32);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_COMPRESSED_اندازه_OFS, comp_اندازه);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_DECOMPRESSED_اندازه_OFS, uncomp_اندازه);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILENAME_LEN_OFS, filename_اندازه);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_EXTRA_LEN_OFS, extra_اندازه);
  أرجع MZ_TRUE;
}

ساكن mz_bool mz_zip_writer_create_central_dir_سرلیک(mz_zip_archive *pZip, mz_uint8 *pDst, mz_uint16 filename_اندازه, mz_uint16 extra_اندازه, mz_uint16 comment_اندازه, mz_uint64 uncomp_اندازه, mz_uint64 comp_اندازه, mz_uint32 uncomp_دوراني_ازموینه_32, mz_uint16 لاره, mz_uint16 بټ_flags, mz_uint16 dos_وخت, mz_uint16 dos_date, mz_uint64 local_سرلیک_ofs, mz_uint32 ext_ځانګړتیاوې)
{
  (فراغ)pZip;
  memset(pDst, 0, MZ_ZIP_CENTRAL_DIR_سرلیک_اندازه);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_SIG_OFS, MZ_ZIP_CENTRAL_DIR_سرلیک_SIG);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_نسخه_NEEDED_OFS, لاره ? 20 : 0);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_بټ_FLAG_OFS, بټ_flags);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_لاره_OFS, لاره);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILE_وخت_OFS, dos_وخت);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILE_DATE_OFS, dos_date);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_دوراني_ازموینه_32_OFS, uncomp_دوراني_ازموینه_32);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_COMPRESSED_اندازه_OFS, comp_اندازه);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_DECOMPRESSED_اندازه_OFS, uncomp_اندازه);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILENAME_LEN_OFS, filename_اندازه);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_EXTRA_LEN_OFS, extra_اندازه);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_COMMENT_LEN_OFS, comment_اندازه);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS, ext_ځانګړتیاوې);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_LOCAL_سرلیک_OFS, local_سرلیک_ofs);
  أرجع MZ_TRUE;
}

ساكن mz_bool mz_zip_writer_جمع_کړه_منزل_central_dir(mz_zip_archive *pZip, ثابت حرف *pFilename, mz_uint16 filename_اندازه, ثابت فراغ *pExtra, mz_uint16 extra_اندازه, ثابت فراغ *pComment, mz_uint16 comment_اندازه, mz_uint64 uncomp_اندازه, mz_uint64 comp_اندازه, mz_uint32 uncomp_دوراني_ازموینه_32, mz_uint16 لاره, mz_uint16 بټ_flags, mz_uint16 dos_وخت, mz_uint16 dos_date, mz_uint64 local_سرلیک_ofs, mz_uint32 ext_ځانګړتیاوې)
{
  mz_zip_دننی_state *pState = pZip->m_pState;
  mz_uint32 central_dir_ofs = (mz_uint32)pState->m_central_dir.m_اندازه;
  size_t orig_central_dir_اندازه = pState->m_central_dir.m_اندازه;
  mz_uint8 central_dir_سرلیک[MZ_ZIP_CENTRAL_DIR_سرلیک_اندازه];

  // No zip64 support yet
  إذا ((local_سرلیک_ofs > 0xFFFFFFFF) || (((mz_uint64)pState->m_central_dir.m_اندازه + MZ_ZIP_CENTRAL_DIR_سرلیک_اندازه + filename_اندازه + extra_اندازه + comment_اندازه) > 0xFFFFFFFF))
    أرجع MZ_FALSE;

  إذا (!mz_zip_writer_create_central_dir_سرلیک(pZip, central_dir_سرلیک, filename_اندازه, extra_اندازه, comment_اندازه, uncomp_اندازه, comp_اندازه, uncomp_دوراني_ازموینه_32, لاره, بټ_flags, dos_وخت, dos_date, local_سرلیک_ofs, ext_ځانګړتیاوې))
    أرجع MZ_FALSE;

  إذا ((!mz_zip_array_ټېل_شا(pZip, &pState->m_central_dir, central_dir_سرلیک, MZ_ZIP_CENTRAL_DIR_سرلیک_اندازه)) ||
      (!mz_zip_array_ټېل_شا(pZip, &pState->m_central_dir, pFilename, filename_اندازه)) ||
      (!mz_zip_array_ټېل_شا(pZip, &pState->m_central_dir, pExtra, extra_اندازه)) ||
      (!mz_zip_array_ټېل_شا(pZip, &pState->m_central_dir, pComment, comment_اندازه)) ||
      (!mz_zip_array_ټېل_شا(pZip, &pState->m_central_dir_offsets, &central_dir_ofs, 1)))
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
  إذا (!pZip->m_file_دننه_واټن_alignment)
    أرجع 0;
  n = (mz_uint32)(pZip->m_archive_اندازه & (pZip->m_file_دننه_واټن_alignment - 1));
  أرجع (pZip->m_file_دننه_واټن_alignment - n) & (pZip->m_file_دننه_واټن_alignment - 1);
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

mz_bool mz_zip_writer_جمع_کړه_mem_ex(mz_zip_archive *pZip, ثابت حرف *pArchive_name, ثابت فراغ *pBuf, size_t buf_اندازه_2, ثابت فراغ *pComment, mz_uint16 comment_اندازه, mz_uint level_and_flags, mz_uint64 uncomp_اندازه, mz_uint32 uncomp_دوراني_ازموینه_32)
{
  mz_uint16 لاره = 0, dos_وخت = 0, dos_date = 0;
  mz_uint level, ext_ځانګړتیاوې = 0, عدد_alignment_padding_بایټونه;
  mz_uint64 local_dir_سرلیک_ofs = pZip->m_archive_اندازه, cur_archive_file_ofs = pZip->m_archive_اندازه, comp_اندازه = 0;
  size_t archive_name_اندازه;
  mz_uint8 local_dir_سرلیک[MZ_ZIP_LOCAL_DIR_سرلیک_اندازه];
  tdefl_compressor *pComp = عدم;
  mz_bool store_معلومات_uncompressed;
  mz_zip_دننی_state *pState;

  إذا ((صحيح)level_and_flags < 0)
    level_and_flags = MZ_DEFAULT_LEVEL;
  level = level_and_flags & 0xF;
  store_معلومات_uncompressed = ((!level) || (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_معلومات));

  إذا ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_ډېرپېښ != MZ_ZIP_ډېرپېښ_WRITING) || ((buf_اندازه_2) && (!pBuf)) || (!pArchive_name) || ((comment_اندازه) && (!pComment)) || (pZip->m_ټول_files == 0xFFFF) || (level > MZ_UBER_COMPRESSION))
    أرجع MZ_FALSE;

  pState = pZip->m_pState;

  إذا ((!(level_and_flags & MZ_ZIP_FLAG_COMPRESSED_معلومات)) && (uncomp_اندازه))
    أرجع MZ_FALSE;
  // No zip64 support yet
  إذا ((buf_اندازه_2 > 0xFFFFFFFF) || (uncomp_اندازه > 0xFFFFFFFF))
    أرجع MZ_FALSE;
  إذا (!mz_zip_writer_validate_archive_name(pArchive_name))
    أرجع MZ_FALSE;

#که_نه_تعریف_شوی MINIZ_NO_وخت
  {
    وخت_t cur_وخت; وخت(&cur_وخت);
    mz_zip_وخت_منزل_dos_وخت(cur_وخت, &dos_وخت, &dos_date);
  }
#د_که_پای // #ifndef MINIZ_NO_TIME

  archive_name_اندازه = مزي_اوږدوالی(pArchive_name);
  إذا (archive_name_اندازه > 0xFFFF)
    أرجع MZ_FALSE;

  عدد_alignment_padding_بایټونه = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  إذا ((pZip->m_ټول_files == 0xFFFF) || ((pZip->m_archive_اندازه + عدد_alignment_padding_بایټونه + MZ_ZIP_LOCAL_DIR_سرلیک_اندازه + MZ_ZIP_CENTRAL_DIR_سرلیک_اندازه + comment_اندازه + archive_name_اندازه) > 0xFFFFFFFF))
    أرجع MZ_FALSE;

  إذا ((archive_name_اندازه) && (pArchive_name[archive_name_اندازه - 1] == '/'))
  {
    // Set DOS Subdirectory attribute bit.
    ext_ځانګړتیاوې |= 0x10;
    // Subdirectories cannot contain data.
    إذا ((buf_اندازه_2) || (uncomp_اندازه))
      أرجع MZ_FALSE;
  }

  // Try to do any allocations before writing to the archive, so if an allocation fails the file remains unmodified. (A good idea if we're doing an in-place modification.)
  إذا ((!mz_zip_array_ensure_ځای(pZip, &pState->m_central_dir, MZ_ZIP_CENTRAL_DIR_سرلیک_اندازه + archive_name_اندازه + comment_اندازه)) || (!mz_zip_array_ensure_ځای(pZip, &pState->m_central_dir_offsets, 1)))
    أرجع MZ_FALSE;

  إذا ((!store_معلومات_uncompressed) && (buf_اندازه_2))
  {
    إذا (عدم == (pComp = (tdefl_compressor *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, حجم(tdefl_compressor))))
      أرجع MZ_FALSE;
  }

  إذا (!mz_zip_writer_write_zeros(pZip, cur_archive_file_ofs, عدد_alignment_padding_بایټونه + حجم(local_dir_سرلیک)))
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
    أرجع MZ_FALSE;
  }
  local_dir_سرلیک_ofs += عدد_alignment_padding_بایټونه;
  إذا (pZip->m_file_دننه_واټن_alignment) { MZ_ASSERT((local_dir_سرلیک_ofs & (pZip->m_file_دننه_واټن_alignment - 1)) == 0); }
  cur_archive_file_ofs += عدد_alignment_padding_بایټونه + حجم(local_dir_سرلیک);

  MZ_CLEAR_ARR(local_dir_سرلیک);
  إذا (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pArchive_name, archive_name_اندازه) != archive_name_اندازه)
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
    أرجع MZ_FALSE;
  }
  cur_archive_file_ofs += archive_name_اندازه;

  إذا (!(level_and_flags & MZ_ZIP_FLAG_COMPRESSED_معلومات))
  {
    uncomp_دوراني_ازموینه_32 = (mz_uint32)mz_دوراني_ازموینه_32(MZ_دوراني_ازموینه_32_INIT, (ثابت mz_uint8*)pBuf, buf_اندازه_2);
    uncomp_اندازه = buf_اندازه_2;
    إذا (uncomp_اندازه <= 3)
    {
      level = 0;
      store_معلومات_uncompressed = MZ_TRUE;
    }
  }

  إذا (store_معلومات_uncompressed)
  {
    إذا (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pBuf, buf_اندازه_2) != buf_اندازه_2)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
      أرجع MZ_FALSE;
    }

    cur_archive_file_ofs += buf_اندازه_2;
    comp_اندازه = buf_اندازه_2;

    إذا (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_معلومات)
      لاره = MZ_DEFLATED;
  }
  وإلا إذا (buf_اندازه_2)
  {
    mz_zip_writer_جمع_کړه_state state;

    state.m_pZip = pZip;
    state.m_cur_archive_file_ofs = cur_archive_file_ofs;
    state.m_comp_اندازه = 0;

    إذا ((tdefl_init(pComp, mz_zip_writer_جمع_کړه_put_buf_callback, &state, tdefl_create_comp_flags_from_zip_params(level, -15, MZ_DEFAULT_STRATEGY)) != TDEFL_حالت_OKAY) ||
        (tdefl_compress_بفر(pComp, pBuf, buf_اندازه_2, TDEFL_پای) != TDEFL_حالت_بشپړ))
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
      أرجع MZ_FALSE;
    }

    comp_اندازه = state.m_comp_اندازه;
    cur_archive_file_ofs = state.m_cur_archive_file_ofs;

    لاره = MZ_DEFLATED;
  }

  pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
  pComp = عدم;

  // no zip64 support yet
  إذا ((comp_اندازه > 0xFFFFFFFF) || (cur_archive_file_ofs > 0xFFFFFFFF))
    أرجع MZ_FALSE;

  إذا (!mz_zip_writer_create_local_dir_سرلیک(pZip, local_dir_سرلیک, (mz_uint16)archive_name_اندازه, 0, uncomp_اندازه, comp_اندازه, uncomp_دوراني_ازموینه_32, لاره, 0, dos_وخت, dos_date))
    أرجع MZ_FALSE;

  إذا (pZip->m_pWrite(pZip->m_pIO_opaque, local_dir_سرلیک_ofs, local_dir_سرلیک, حجم(local_dir_سرلیک)) != حجم(local_dir_سرلیک))
    أرجع MZ_FALSE;

  إذا (!mz_zip_writer_جمع_کړه_منزل_central_dir(pZip, pArchive_name, (mz_uint16)archive_name_اندازه, عدم, 0, pComment, comment_اندازه, uncomp_اندازه, comp_اندازه, uncomp_دوراني_ازموینه_32, لاره, 0, dos_وخت, dos_date, local_dir_سرلیک_ofs, ext_ځانګړتیاوې))
    أرجع MZ_FALSE;

  pZip->m_ټول_files++;
  pZip->m_archive_اندازه = cur_archive_file_ofs;

  أرجع MZ_TRUE;
}

#که_نه_تعریف_شوی MINIZ_NO_STDIO
mz_bool mz_zip_writer_جمع_کړه_file(mz_zip_archive *pZip, ثابت حرف *pArchive_name, ثابت حرف *pSrc_filename, ثابت فراغ *pComment, mz_uint16 comment_اندازه, mz_uint level_and_flags)
{
  mz_uint uncomp_دوراني_ازموینه_32 = MZ_دوراني_ازموینه_32_INIT, level, عدد_alignment_padding_بایټونه;
  mz_uint16 لاره = 0, dos_وخت = 0, dos_date = 0, ext_ځانګړتیاوې = 0;
  mz_uint64 local_dir_سرلیک_ofs = pZip->m_archive_اندازه, cur_archive_file_ofs = pZip->m_archive_اندازه, uncomp_اندازه = 0, comp_اندازه = 0;
  size_t archive_name_اندازه;
  mz_uint8 local_dir_سرلیک[MZ_ZIP_LOCAL_DIR_سرلیک_اندازه];
  MZ_FILE *pSrc_file = عدم;

  إذا ((صحيح)level_and_flags < 0)
    level_and_flags = MZ_DEFAULT_LEVEL;
  level = level_and_flags & 0xF;

  إذا ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_ډېرپېښ != MZ_ZIP_ډېرپېښ_WRITING) || (!pArchive_name) || ((comment_اندازه) && (!pComment)) || (level > MZ_UBER_COMPRESSION))
    أرجع MZ_FALSE;
  إذا (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_معلومات)
    أرجع MZ_FALSE;
  إذا (!mz_zip_writer_validate_archive_name(pArchive_name))
    أرجع MZ_FALSE;

  archive_name_اندازه = مزي_اوږدوالی(pArchive_name);
  إذا (archive_name_اندازه > 0xFFFF)
    أرجع MZ_FALSE;

  عدد_alignment_padding_بایټونه = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  إذا ((pZip->m_ټول_files == 0xFFFF) || ((pZip->m_archive_اندازه + عدد_alignment_padding_بایټونه + MZ_ZIP_LOCAL_DIR_سرلیک_اندازه + MZ_ZIP_CENTRAL_DIR_سرلیک_اندازه + comment_اندازه + archive_name_اندازه) > 0xFFFFFFFF))
    أرجع MZ_FALSE;

  إذا (!mz_zip_get_file_modified_وخت(pSrc_filename, &dos_وخت, &dos_date))
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

  إذا (!mz_zip_writer_write_zeros(pZip, cur_archive_file_ofs, عدد_alignment_padding_بایټونه + حجم(local_dir_سرلیک)))
  {
    MZ_FCLOSE(pSrc_file);
    أرجع MZ_FALSE;
  }
  local_dir_سرلیک_ofs += عدد_alignment_padding_بایټونه;
  إذا (pZip->m_file_دننه_واټن_alignment) { MZ_ASSERT((local_dir_سرلیک_ofs & (pZip->m_file_دننه_واټن_alignment - 1)) == 0); }
  cur_archive_file_ofs += عدد_alignment_padding_بایټونه + حجم(local_dir_سرلیک);

  MZ_CLEAR_ARR(local_dir_سرلیک);
  إذا (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pArchive_name, archive_name_اندازه) != archive_name_اندازه)
  {
    MZ_FCLOSE(pSrc_file);
    أرجع MZ_FALSE;
  }
  cur_archive_file_ofs += archive_name_اندازه;

  إذا (uncomp_اندازه)
  {
    mz_uint64 uncomp_پاتې_شوی = uncomp_اندازه;
    فراغ *pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, MZ_ZIP_MAX_IO_BUF_اندازه);
    إذا (!pRead_buf)
    {
      MZ_FCLOSE(pSrc_file);
      أرجع MZ_FALSE;
    }

    إذا (!level)
    {
      طالما (uncomp_پاتې_شوی)
      {
        mz_uint n = (mz_uint)MZ_MIN(MZ_ZIP_MAX_IO_BUF_اندازه, uncomp_پاتې_شوی);
        إذا ((MZ_FREAD(pRead_buf, 1, n, pSrc_file) != n) || (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pRead_buf, n) != n))
        {
          pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
          MZ_FCLOSE(pSrc_file);
          أرجع MZ_FALSE;
        }
        uncomp_دوراني_ازموینه_32 = (mz_uint32)mz_دوراني_ازموینه_32(uncomp_دوراني_ازموینه_32, (ثابت mz_uint8 *)pRead_buf, n);
        uncomp_پاتې_شوی -= n;
        cur_archive_file_ofs += n;
      }
      comp_اندازه = uncomp_اندازه;
    }
    وإلا
    {
      mz_bool پایله = MZ_FALSE;
      mz_zip_writer_جمع_کړه_state state;
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

      إذا (tdefl_init(pComp, mz_zip_writer_جمع_کړه_put_buf_callback, &state, tdefl_create_comp_flags_from_zip_params(level, -15, MZ_DEFAULT_STRATEGY)) != TDEFL_حالت_OKAY)
      {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        أرجع MZ_FALSE;
      }

      لكل ( ; ; )
      {
        size_t دننه_buf_اندازه = (mz_uint32)MZ_MIN(uncomp_پاتې_شوی, MZ_ZIP_MAX_IO_BUF_اندازه);
        tdefl_حالت حالت;

        إذا (MZ_FREAD(pRead_buf, 1, دننه_buf_اندازه, pSrc_file) != دننه_buf_اندازه)
          اكسر;

        uncomp_دوراني_ازموینه_32 = (mz_uint32)mz_دوراني_ازموینه_32(uncomp_دوراني_ازموینه_32, (ثابت mz_uint8 *)pRead_buf, دننه_buf_اندازه);
        uncomp_پاتې_شوی -= دننه_buf_اندازه;

        حالت = tdefl_compress_بفر(pComp, pRead_buf, دننه_buf_اندازه, uncomp_پاتې_شوی ? TDEFL_NO_FLUSH : TDEFL_پای);
        إذا (حالت == TDEFL_حالت_بشپړ)
        {
          پایله = MZ_TRUE;
          اكسر;
        }
        وإلا إذا (حالت != TDEFL_حالت_OKAY)
          اكسر;
      }

      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);

      إذا (!پایله)
      {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        أرجع MZ_FALSE;
      }

      comp_اندازه = state.m_comp_اندازه;
      cur_archive_file_ofs = state.m_cur_archive_file_ofs;

      لاره = MZ_DEFLATED;
    }

    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
  }

  MZ_FCLOSE(pSrc_file); pSrc_file = عدم;

  // no zip64 support yet
  إذا ((comp_اندازه > 0xFFFFFFFF) || (cur_archive_file_ofs > 0xFFFFFFFF))
    أرجع MZ_FALSE;

  إذا (!mz_zip_writer_create_local_dir_سرلیک(pZip, local_dir_سرلیک, (mz_uint16)archive_name_اندازه, 0, uncomp_اندازه, comp_اندازه, uncomp_دوراني_ازموینه_32, لاره, 0, dos_وخت, dos_date))
    أرجع MZ_FALSE;

  إذا (pZip->m_pWrite(pZip->m_pIO_opaque, local_dir_سرلیک_ofs, local_dir_سرلیک, حجم(local_dir_سرلیک)) != حجم(local_dir_سرلیک))
    أرجع MZ_FALSE;

  إذا (!mz_zip_writer_جمع_کړه_منزل_central_dir(pZip, pArchive_name, (mz_uint16)archive_name_اندازه, عدم, 0, pComment, comment_اندازه, uncomp_اندازه, comp_اندازه, uncomp_دوراني_ازموینه_32, لاره, 0, dos_وخت, dos_date, local_dir_سرلیک_ofs, ext_ځانګړتیاوې))
    أرجع MZ_FALSE;

  pZip->m_ټول_files++;
  pZip->m_archive_اندازه = cur_archive_file_ofs;

  أرجع MZ_TRUE;
}
#د_که_پای // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_writer_جمع_کړه_from_zip_reader(mz_zip_archive *pZip, mz_zip_archive *p_سرچینه_zip, mz_uint file_شاخص)
{
  mz_uint n, بټ_flags, عدد_alignment_padding_بایټونه;
  mz_uint64 comp_بایټونه_پاتې_شوی, local_dir_سرلیک_ofs;
  mz_uint64 cur_src_file_ofs, cur_dst_file_ofs;
  mz_uint32 local_سرلیک_u32[(MZ_ZIP_LOCAL_DIR_سرلیک_اندازه + حجم(mz_uint32) - 1) / حجم(mz_uint32)]; mz_uint8 *p_Local_سرلیک = (mz_uint8 *)local_سرلیک_u32;
  mz_uint8 central_سرلیک[MZ_ZIP_CENTRAL_DIR_سرلیک_اندازه];
  size_t orig_central_dir_اندازه;
  mz_zip_دننی_state *pState;
  فراغ *pBuf; ثابت mz_uint8 *p_Src_central_سرلیک;

  إذا ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_ډېرپېښ != MZ_ZIP_ډېرپېښ_WRITING))
    أرجع MZ_FALSE;
  إذا (عدم == (p_Src_central_سرلیک = mz_zip_reader_get_cdh(p_سرچینه_zip, file_شاخص)))
    أرجع MZ_FALSE;
  pState = pZip->m_pState;

  عدد_alignment_padding_بایټونه = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  إذا ((pZip->m_ټول_files == 0xFFFF) || ((pZip->m_archive_اندازه + عدد_alignment_padding_بایټونه + MZ_ZIP_LOCAL_DIR_سرلیک_اندازه + MZ_ZIP_CENTRAL_DIR_سرلیک_اندازه) > 0xFFFFFFFF))
    أرجع MZ_FALSE;

  cur_src_file_ofs = MZ_READ_LE32(p_Src_central_سرلیک + MZ_ZIP_CDH_LOCAL_سرلیک_OFS);
  cur_dst_file_ofs = pZip->m_archive_اندازه;

  إذا (p_سرچینه_zip->m_pRead(p_سرچینه_zip->m_pIO_opaque, cur_src_file_ofs, p_Local_سرلیک, MZ_ZIP_LOCAL_DIR_سرلیک_اندازه) != MZ_ZIP_LOCAL_DIR_سرلیک_اندازه)
    أرجع MZ_FALSE;
  إذا (MZ_READ_LE32(p_Local_سرلیک) != MZ_ZIP_LOCAL_DIR_سرلیک_SIG)
    أرجع MZ_FALSE;
  cur_src_file_ofs += MZ_ZIP_LOCAL_DIR_سرلیک_اندازه;

  إذا (!mz_zip_writer_write_zeros(pZip, cur_dst_file_ofs, عدد_alignment_padding_بایټونه))
    أرجع MZ_FALSE;
  cur_dst_file_ofs += عدد_alignment_padding_بایټونه;
  local_dir_سرلیک_ofs = cur_dst_file_ofs;
  إذا (pZip->m_file_دننه_واټن_alignment) { MZ_ASSERT((local_dir_سرلیک_ofs & (pZip->m_file_دننه_واټن_alignment - 1)) == 0); }

  إذا (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, p_Local_سرلیک, MZ_ZIP_LOCAL_DIR_سرلیک_اندازه) != MZ_ZIP_LOCAL_DIR_سرلیک_اندازه)
    أرجع MZ_FALSE;
  cur_dst_file_ofs += MZ_ZIP_LOCAL_DIR_سرلیک_اندازه;

  n = MZ_READ_LE16(p_Local_سرلیک + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p_Local_سرلیک + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  comp_بایټونه_پاتې_شوی = n + MZ_READ_LE32(p_Src_central_سرلیک + MZ_ZIP_CDH_COMPRESSED_اندازه_OFS);

  إذا (عدم == (pBuf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)MZ_MAX(حجم(mz_uint32) * 4, MZ_MIN(MZ_ZIP_MAX_IO_BUF_اندازه, comp_بایټونه_پاتې_شوی)))))
    أرجع MZ_FALSE;

  طالما (comp_بایټونه_پاتې_شوی)
  {
    n = (mz_uint)MZ_MIN(MZ_ZIP_MAX_IO_BUF_اندازه, comp_بایټونه_پاتې_شوی);
    إذا (p_سرچینه_zip->m_pRead(p_سرچینه_zip->m_pIO_opaque, cur_src_file_ofs, pBuf, n) != n)
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

    comp_بایټونه_پاتې_شوی -= n;
  }

  بټ_flags = MZ_READ_LE16(p_Local_سرلیک + MZ_ZIP_LDH_بټ_FLAG_OFS);
  إذا (بټ_flags & 8)
  {
    // Copy data descriptor
    إذا (p_سرچینه_zip->m_pRead(p_سرچینه_zip->m_pIO_opaque, cur_src_file_ofs, pBuf, حجم(mz_uint32) * 4) != حجم(mz_uint32) * 4)
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

  حافظه_نقل(central_سرلیک, p_Src_central_سرلیک, MZ_ZIP_CENTRAL_DIR_سرلیک_اندازه);
  MZ_WRITE_LE32(central_سرلیک + MZ_ZIP_CDH_LOCAL_سرلیک_OFS, local_dir_سرلیک_ofs);
  إذا (!mz_zip_array_ټېل_شا(pZip, &pState->m_central_dir, central_سرلیک, MZ_ZIP_CENTRAL_DIR_سرلیک_اندازه))
    أرجع MZ_FALSE;

  n = MZ_READ_LE16(p_Src_central_سرلیک + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p_Src_central_سرلیک + MZ_ZIP_CDH_EXTRA_LEN_OFS) + MZ_READ_LE16(p_Src_central_سرلیک + MZ_ZIP_CDH_COMMENT_LEN_OFS);
  إذا (!mz_zip_array_ټېل_شا(pZip, &pState->m_central_dir, p_Src_central_سرلیک + MZ_ZIP_CENTRAL_DIR_سرلیک_اندازه, n))
  {
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_اندازه, MZ_FALSE);
    أرجع MZ_FALSE;
  }

  إذا (pState->m_central_dir.m_اندازه > 0xFFFFFFFF)
    أرجع MZ_FALSE;
  n = (mz_uint32)orig_central_dir_اندازه;
  إذا (!mz_zip_array_ټېل_شا(pZip, &pState->m_central_dir_offsets, &n, 1))
  {
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_اندازه, MZ_FALSE);
    أرجع MZ_FALSE;
  }

  pZip->m_ټول_files++;
  pZip->m_archive_اندازه = cur_dst_file_ofs;

  أرجع MZ_TRUE;
}

mz_bool mz_zip_writer_finalize_archive(mz_zip_archive *pZip)
{
  mz_zip_دننی_state *pState;
  mz_uint64 central_dir_ofs, central_dir_اندازه;
  mz_uint8 hdr[MZ_ZIP_پای_ټکی_د_CENTRAL_DIR_سرلیک_اندازه];

  إذا ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_ډېرپېښ != MZ_ZIP_ډېرپېښ_WRITING))
    أرجع MZ_FALSE;

  pState = pZip->m_pState;

  // no zip64 support yet
  إذا ((pZip->m_ټول_files > 0xFFFF) || ((pZip->m_archive_اندازه + pState->m_central_dir.m_اندازه + MZ_ZIP_پای_ټکی_د_CENTRAL_DIR_سرلیک_اندازه) > 0xFFFFFFFF))
    أرجع MZ_FALSE;

  central_dir_ofs = 0;
  central_dir_اندازه = 0;
  إذا (pZip->m_ټول_files)
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
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_SIG_OFS, MZ_ZIP_پای_ټکی_د_CENTRAL_DIR_سرلیک_SIG);
  MZ_WRITE_LE16(hdr + MZ_ZIP_ECDH_CDIR_عدد_ENTRIES_ON_DISK_OFS, pZip->m_ټول_files);
  MZ_WRITE_LE16(hdr + MZ_ZIP_ECDH_CDIR_ټول_ENTRIES_OFS, pZip->m_ټول_files);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_CDIR_اندازه_OFS, central_dir_اندازه);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_CDIR_OFS_OFS, central_dir_ofs);

  إذا (pZip->m_pWrite(pZip->m_pIO_opaque, pZip->m_archive_اندازه, hdr, حجم(hdr)) != حجم(hdr))
    أرجع MZ_FALSE;
#که_نه_تعریف_شوی MINIZ_NO_STDIO
  إذا ((pState->m_pFile) && (MZ_FFLUSH(pState->m_pFile) == EOF))
    أرجع MZ_FALSE;
#د_که_پای // #ifndef MINIZ_NO_STDIO

  pZip->m_archive_اندازه += حجم(hdr);

  pZip->m_zip_ډېرپېښ = MZ_ZIP_ډېرپېښ_WRITING_HAS_BEEN_FINALIZED;
  أرجع MZ_TRUE;
}

mz_bool mz_zip_writer_finalize_ډېرۍ_archive(mz_zip_archive *pZip, فراغ **pBuf, size_t *p_اندازه)
{
  إذا ((!pZip) || (!pZip->m_pState) || (!pBuf) || (!p_اندازه))
    أرجع MZ_FALSE;
  إذا (pZip->m_pWrite != mz_zip_ډېرۍ_write_func)
    أرجع MZ_FALSE;
  إذا (!mz_zip_writer_finalize_archive(pZip))
    أرجع MZ_FALSE;

  *pBuf = pZip->m_pState->m_pMem;
  *p_اندازه = pZip->m_pState->m_mem_اندازه;
  pZip->m_pState->m_pMem = عدم;
  pZip->m_pState->m_mem_اندازه = pZip->m_pState->m_mem_ظرفیت = 0;
  أرجع MZ_TRUE;
}

mz_bool mz_zip_writer_پای_ټکی(mz_zip_archive *pZip)
{
  mz_zip_دننی_state *pState;
  mz_bool حالت = MZ_TRUE;
  إذا ((!pZip) || (!pZip->m_pState) || (!pZip->m_pAlloc) || (!pZip->m_pFree) || ((pZip->m_zip_ډېرپېښ != MZ_ZIP_ډېرپېښ_WRITING) && (pZip->m_zip_ډېرپېښ != MZ_ZIP_ډېرپېښ_WRITING_HAS_BEEN_FINALIZED)))
    أرجع MZ_FALSE;

  pState = pZip->m_pState;
  pZip->m_pState = عدم;
  mz_zip_array_clear(pZip, &pState->m_central_dir);
  mz_zip_array_clear(pZip, &pState->m_central_dir_offsets);
  mz_zip_array_clear(pZip, &pState->m_sorted_central_dir_offsets);

#که_نه_تعریف_شوی MINIZ_NO_STDIO
  إذا (pState->m_pFile)
  {
    MZ_FCLOSE(pState->m_pFile);
    pState->m_pFile = عدم;
  }
#د_که_پای // #ifndef MINIZ_NO_STDIO

  إذا ((pZip->m_pWrite == mz_zip_ډېرۍ_write_func) && (pState->m_pMem))
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pState->m_pMem);
    pState->m_pMem = عدم;
  }

  pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
  pZip->m_zip_ډېرپېښ = MZ_ZIP_ډېرپېښ_INVALID;
  أرجع حالت;
}

#که_نه_تعریف_شوی MINIZ_NO_STDIO
mz_bool mz_zip_جمع_کړه_mem_منزل_archive_file_دننه_ځای_پرځای_کړه(ثابت حرف *pZip_filename, ثابت حرف *pArchive_name, ثابت فراغ *pBuf, size_t buf_اندازه_2, ثابت فراغ *pComment, mz_uint16 comment_اندازه, mz_uint level_and_flags)
{
  mz_bool حالت, created_new_archive = MZ_FALSE;
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
    إذا (!mz_zip_reader_init_file(&zip_archive, pZip_filename, level_and_flags | MZ_ZIP_FLAG_DO_NOT_ترتیبول_CENTRAL_DIRECTORY))
      أرجع MZ_FALSE;
    إذا (!mz_zip_writer_init_from_reader(&zip_archive, pZip_filename))
    {
      mz_zip_reader_پای_ټکی(&zip_archive);
      أرجع MZ_FALSE;
    }
  }
  حالت = mz_zip_writer_جمع_کړه_mem_ex(&zip_archive, pArchive_name, pBuf, buf_اندازه_2, pComment, comment_اندازه, level_and_flags, 0, 0);
  // Always finalize, even if adding failed for some reason, so we have a valid central directory. (This may not always succeed, but we can try.)
  إذا (!mz_zip_writer_finalize_archive(&zip_archive))
    حالت = MZ_FALSE;
  إذا (!mz_zip_writer_پای_ټکی(&zip_archive))
    حالت = MZ_FALSE;
  إذا ((!حالت) && (created_new_archive))
  {
    // It's a new archive and something went wrong, so just delete it.
    صحيح ignored_حالت = MZ_DELETE_FILE(pZip_filename);
    (فراغ)ignored_حالت;
  }
  أرجع حالت;
}

فراغ *mz_zip_ایستل_archive_file_منزل_ډېرۍ(ثابت حرف *pZip_filename, ثابت حرف *pArchive_name, size_t *p_اندازه, mz_uint flags)
{
  صحيح file_شاخص;
  mz_zip_archive zip_archive;
  فراغ *p = عدم;

  إذا (p_اندازه)
    *p_اندازه = 0;

  إذا ((!pZip_filename) || (!pArchive_name))
    أرجع عدم;

  MZ_CLEAR_OBJ(zip_archive);
  إذا (!mz_zip_reader_init_file(&zip_archive, pZip_filename, flags | MZ_ZIP_FLAG_DO_NOT_ترتیبول_CENTRAL_DIRECTORY))
    أرجع عدم;

  إذا ((file_شاخص = mz_zip_reader_locate_file(&zip_archive, pArchive_name, عدم, flags)) >= 0)
    p = mz_zip_reader_ایستل_منزل_ډېرۍ(&zip_archive, file_شاخص, p_اندازه, flags);

  mz_zip_reader_پای_ټکی(&zip_archive);
  أرجع p;
}

#د_که_پای // #ifndef MINIZ_NO_STDIO

#د_که_پای // #ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

#د_که_پای // #ifndef MINIZ_NO_ARCHIVE_APIS

#که_تعریف_شوی __cplusplus
}
#د_که_پای

#که_تعریف_شوی _MSC_VER
#لارښوونه warning (راوباسه)
#د_که_پای

#د_که_پای // MINIZ_HEADER_FILE_ONLY

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

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

#ifndef MINIZ_HEADER_INCLUDED
#define MINIZ_HEADER_INCLUDED

/*#include <stdlib.h>*/

// Defines to completely disable specific portions of miniz.c:
// If all macros here are defined the only functionality remaining will be CRC-32, adler-32, tinfl, and tdefl.

// Define MINIZ_NO_STDIO to disable all usage and any functions which rely on stdio for file I/O.
#define MINIZ_NO_STDIO

// If MINIZ_NO_TIME is specified then the ZIP archive functions will not be able to get the current time, or
// get/set file times, and the C run-time funcs that get/set times won't be called.
// The current downside is the times written to your archives will be from 1979.
#define MINIZ_NO_TIME

// Define MINIZ_NO_DEFLATE_APIS to disable all compression API's.
//#define MINIZ_NO_DEFLATE_APIS

// Define MINIZ_NO_INFLATE_APIS to disable all decompression API's.
#define MINIZ_NO_INFLATE_APIS

// Define MINIZ_NO_ARCHIVE_APIS to disable all ZIP archive API's.
#define MINIZ_NO_ARCHIVE_APIS

// Define MINIZ_NO_ARCHIVE_APIS to disable all writing related ZIP archive API's.
#define MINIZ_NO_ARCHIVE_WRITING_APIS

// Define MINIZ_NO_ZLIB_APIS to remove all ZLIB-style compression/decompression API's.
#define MINIZ_NO_ZLIB_APIS

// Define MINIZ_NO_ZLIB_COMPATIBLE_NAME to disable zlib names, to prevent conflicts against stock zlib.
#define MINIZ_NO_ZLIB_COMPATIBLE_NAMES

// Define MINIZ_NO_MALLOC to disable all calls to malloc, free, and realloc.
// Note if MINIZ_NO_MALLOC is defined then the user must always provide custom user alloc/free/realloc
// callbacks to the zlib and archive API's, and a few stand-alone helper API's which don't provide custom user
// functions (such as tdefl_compress_mem_to_heap() and tinfl_decompress_mem_to_heap()) won't work.
//#define MINIZ_NO_MALLOC
#define MINIZ_SDL_MALLOC

#ifdef MINIZ_NO_INFLATE_APIS
#define MINIZ_NO_ARCHIVE_APIS
#endif

#ifdef MINIZ_NO_DEFLATE_APIS
#define MINIZ_NO_ARCHIVE_WRITING_APIS
#endif

// Define MINIZ_STATIC_FUNCTIONS to make all functions static. You probably
// want this if you're using miniz in a library
#define MINIZ_STATIC_FUNCTIONS

#എങ്കിൽ defined(__TINYC__) && (defined(__linux) || defined(__linux__))
  // TODO: Work around "error: include file 'sys\utime.h' when compiling with tcc on Linux
  #define MINIZ_NO_TIME
#endif

#എങ്കിൽ !defined(MINIZ_NO_TIME) && !defined(MINIZ_NO_ARCHIVE_APIS)
  #അന്തര്ഭാവ <time.h>
#endif

#എങ്കിൽ defined(_M_IX86) || defined(_M_X64) || defined(__i386__) || defined(__i386) || defined(__i486__) || defined(__i486) || defined(i386) || defined(__ia64__) || defined(__x86_64__)
// MINIZ_X86_OR_X64_CPU is only used to help set the below macros.
#define MINIZ_X86_OR_X64_CPU 1
#endif

#ifndef MINIZ_LITTLE_ENDIAN /* if not defined by SDL */
#എങ്കിൽ (__BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__) || MINIZ_X86_OR_X64_CPU
// Set MINIZ_LITTLE_ENDIAN to 1 if the processor is little endian.
#define MINIZ_LITTLE_ENDIAN 1
#endif
#endif // MINIZ_LITTLE_ENDIAN /* if not defined by SDL */

#ifndef MINIZ_USE_UNALIGNED_LOADS_AND_STORES
#എങ്കിൽ MINIZ_X86_OR_X64_CPU
// Set MINIZ_USE_UNALIGNED_LOADS_AND_STORES to 1 on CPU's that permit efficient integer loads and stores from unaligned addresses.
#define MINIZ_USE_UNALIGNED_LOADS_AND_STORES 1
#endif
#endif // MINIZ_USE_UNALIGNED_LOADS_AND_STORES

#എങ്കിൽ defined(_M_X64) || defined(_WIN64) || defined(__MINGW64__) || defined(_LP64) || defined(__LP64__) || defined(__ia64__) || defined(__x86_64__)
// Set MINIZ_HAS_64BIT_REGISTERS to 1 if operations on 64-bit integers are reasonably fast (and don't involve compiler generated calls to helper functions).
#define MINIZ_HAS_64BIT_REGISTERS 1
#endif

#ifdef MINIZ_STATIC_FUNCTIONS
#define MINIZ_STATIC സ്ഥിതം
#അല്ലെങ്കിൽ
#define MINIZ_STATIC
#endif

#ifdef __cplusplus
ബാഹ്യ "C" {
#endif

// ------------------- zlib-style API Definitions.

// For more compatibility with zlib, miniz.c uses unsigned long for some parameters/struct members. Beware: mz_ulong can be either 32 or 64-bits!
തരനിർവചനം unsigned long mz_ulong;

// mz_free() internally uses the MZ_FREE() macro (which by default calls free() unless you've modified the MZ_MALLOC macro) to release a block allocated from the heap.
MINIZ_STATIC ശൂന്യം mz_free(ശൂന്യം *p);

#define MZ_ADLER32_INIT (1)
// mz_adler32() returns the initial adler-32 value to use when called with ptr==NULL.
MINIZ_STATIC mz_ulong mz_adler32(mz_ulong adler, സ്ഥിരം unsigned അക്ഷരം *ptr, size_t buf_len);

#define MZ_CRC32_INIT (0)
// mz_crc32() returns the initial CRC-32 value to use when called with ptr==NULL.
MINIZ_STATIC mz_ulong mz_crc32(mz_ulong crc, സ്ഥിരം unsigned അക്ഷരം *ptr, size_t buf_len);

// Compression strategies.
എണ്ണൽ { MZ_DEFAULT_STRATEGY = 0, MZ_FILTERED = 1, MZ_HUFFMAN_ONLY = 2, MZ_RLE = 3, MZ_FIXED = 4 };

// Method
#define MZ_DEFLATED 8

#ifndef MINIZ_NO_ZLIB_APIS

// Heap allocation callbacks.
// Note that mz_alloc_func parameter types purpsosely differ from zlib's: items/size is size_t, not unsigned long.
തരനിർവചനം ശൂന്യം *(*mz_alloc_func)(ശൂന്യം *opaque, size_t ഇനങ്ങൾ, size_t size);
തരനിർവചനം ശൂന്യം (*mz_free_func)(ശൂന്യം *opaque, ശൂന്യം *address);
തരനിർവചനം ശൂന്യം *(*mz_realloc_func)(ശൂന്യം *opaque, ശൂന്യം *address, size_t ഇനങ്ങൾ, size_t size);

#define MZ_VERSION          "9.1.15"
#define MZ_VERNUM           0x91F0
#define MZ_VER_MAJOR        9
#define MZ_VER_MINOR        1
#define MZ_VER_REVISION     15
#define MZ_VER_SUBREVISION  0

// Flush values. For typical usage you only need MZ_NO_FLUSH and MZ_FINISH. The other values are for advanced use (refer to the zlib docs).
എണ്ണൽ { MZ_NO_FLUSH = 0, MZ_PARTIAL_FLUSH = 1, MZ_SYNC_FLUSH = 2, MZ_FULL_FLUSH = 3, MZ_FINISH = 4, MZ_BLOCK = 5 };

// Return status codes. MZ_PARAM_ERROR is non-standard.
എണ്ണൽ { MZ_OK = 0, MZ_STREAM_END = 1, MZ_NEED_DICT = 2, MZ_ERRNO = -1, MZ_STREAM_ERROR = -2, MZ_DATA_ERROR = -3, MZ_MEM_ERROR = -4, MZ_BUF_ERROR = -5, MZ_VERSION_ERROR = -6, MZ_PARAM_ERROR = -10000 };

// Compression levels: 0-9 are the standard zlib-style levels, 10 is best possible compression (not zlib compatible, and may be very slow), MZ_DEFAULT_COMPRESSION=MZ_DEFAULT_LEVEL.
എണ്ണൽ { MZ_NO_COMPRESSION = 0, MZ_BEST_SPEED = 1, MZ_BEST_COMPRESSION = 9, MZ_UBER_COMPRESSION = 10, MZ_DEFAULT_LEVEL = 6, MZ_DEFAULT_COMPRESSION = -1 };

// Window bits
#define MZ_DEFAULT_WINDOW_BITS 15

ഘടന mz_internal_state;

// Compression/decompression stream struct.
തരനിർവചനം ഘടന mz_stream_s
{
  സ്ഥിരം unsigned അക്ഷരം *next_in;     // pointer to next byte to read
  unsigned പൂർണ്ണസംഖ്യ avail_in;            // number of bytes available at next_in
  mz_ulong total_in;                // total number of bytes consumed so far

  unsigned അക്ഷരം *next_out;          // pointer to next byte to write
  unsigned പൂർണ്ണസംഖ്യ avail_out;           // number of bytes that can be written to next_out
  mz_ulong total_out;               // total number of bytes produced so far

  അക്ഷരം *സന്ദേശം;                        // error msg (unused)
  ഘടന mz_internal_state *state;  // internal state, allocated by zalloc/zfree

  mz_alloc_func zalloc;             // optional heap allocation function (defaults to malloc)
  mz_free_func zfree;               // optional heap free function (defaults to free)
  ശൂന്യം *opaque;                     // heap alloc function user pointer

  പൂർണ്ണസംഖ്യ data_type;                    // data_type (unused)
  mz_ulong adler;                   // adler32 of the source or uncompressed data
  mz_ulong reserved;                // not used
} mz_stream;

തരനിർവചനം mz_stream *mz_streamp;

// Returns the version string of miniz.c.
MINIZ_STATIC സ്ഥിരം അക്ഷരം *mz_version(ശൂന്യം);

#ifndef MINIZ_NO_DEFLATE_APIS

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
MINIZ_STATIC പൂർണ്ണസംഖ്യ mz_deflateInit(mz_streamp pStream, പൂർണ്ണസംഖ്യ level);

// mz_deflateInit2() is like mz_deflate(), except with more control:
// Additional parameters:
//   method must be MZ_DEFLATED
//   window_bits must be MZ_DEFAULT_WINDOW_BITS (to wrap the deflate stream with zlib header/adler-32 footer) or -MZ_DEFAULT_WINDOW_BITS (raw deflate/no header or footer)
//   mem_level must be between [1, 9] (it's checked but ignored by miniz.c)
MINIZ_STATIC പൂർണ്ണസംഖ്യ mz_deflateInit2(mz_streamp pStream, പൂർണ്ണസംഖ്യ level, പൂർണ്ണസംഖ്യ method, പൂർണ്ണസംഖ്യ window_bits, പൂർണ്ണസംഖ്യ mem_level, പൂർണ്ണസംഖ്യ strategy);

// Quickly resets a compressor without having to reallocate anything. Same as calling mz_deflateEnd() followed by mz_deflateInit()/mz_deflateInit2().
MINIZ_STATIC പൂർണ്ണസംഖ്യ mz_deflateReset(mz_streamp pStream);

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
MINIZ_STATIC പൂർണ്ണസംഖ്യ mz_deflate(mz_streamp pStream, പൂർണ്ണസംഖ്യ flush);

// mz_deflateEnd() deinitializes a compressor:
// Return values:
//  MZ_OK on success.
//  MZ_STREAM_ERROR if the stream is bogus.
MINIZ_STATIC പൂർണ്ണസംഖ്യ mz_deflateEnd(mz_streamp pStream);

// mz_deflateBound() returns a (very) conservative upper bound on the amount of data that could be generated by deflate(), assuming flush is set to only MZ_NO_FLUSH or MZ_FINISH.
MINIZ_STATIC mz_ulong mz_deflateBound(mz_streamp pStream, mz_ulong source_len);

// Single-call compression functions mz_compress() and mz_compress2():
// Returns MZ_OK on success, or one of the error codes from mz_deflate() on failure.
MINIZ_STATIC പൂർണ്ണസംഖ്യ mz_compress(unsigned അക്ഷരം *pDest, mz_ulong *pDest_len, സ്ഥിരം unsigned അക്ഷരം *pSource, mz_ulong source_len);
MINIZ_STATIC പൂർണ്ണസംഖ്യ mz_compress2(unsigned അക്ഷരം *pDest, mz_ulong *pDest_len, സ്ഥിരം unsigned അക്ഷരം *pSource, mz_ulong source_len, പൂർണ്ണസംഖ്യ level);

// mz_compressBound() returns a (very) conservative upper bound on the amount of data that could be generated by calling mz_compress().
MINIZ_STATIC mz_ulong mz_compressBound(mz_ulong source_len);

#endif /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#ifndef MINIZ_NO_INFLATE_APIS

// Initializes a decompressor.
MINIZ_STATIC പൂർണ്ണസംഖ്യ mz_inflateInit(mz_streamp pStream);

// mz_inflateInit2() is like mz_inflateInit() with an additional option that controls the window size and whether or not the stream has been wrapped with a zlib header/footer:
// window_bits must be MZ_DEFAULT_WINDOW_BITS (to parse zlib header/footer) or -MZ_DEFAULT_WINDOW_BITS (raw deflate).
MINIZ_STATIC പൂർണ്ണസംഖ്യ mz_inflateInit2(mz_streamp pStream, പൂർണ്ണസംഖ്യ window_bits);

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
MINIZ_STATIC പൂർണ്ണസംഖ്യ mz_inflate(mz_streamp pStream, പൂർണ്ണസംഖ്യ flush);

// Deinitializes a decompressor.
MINIZ_STATIC പൂർണ്ണസംഖ്യ mz_inflateEnd(mz_streamp pStream);

// Single-call decompression.
// Returns MZ_OK on success, or one of the error codes from mz_inflate() on failure.
MINIZ_STATIC പൂർണ്ണസംഖ്യ mz_uncompress(unsigned അക്ഷരം *pDest, mz_ulong *pDest_len, സ്ഥിരം unsigned അക്ഷരം *pSource, mz_ulong source_len);
#endif /*#ifndef MINIZ_NO_INFLATE_APIS*/

// Returns a string description of the specified error code, or NULL if the error code is invalid.
MINIZ_STATIC സ്ഥിരം അക്ഷരം *mz_error(പൂർണ്ണസംഖ്യ err);

// Redefine zlib-compatible names to miniz equivalents, so miniz.c can be used as a drop-in replacement for the subset of zlib that miniz.c supports.
// Define MINIZ_NO_ZLIB_COMPATIBLE_NAMES to disable zlib-compatibility if you use zlib in the same project.
#ifndef MINIZ_NO_ZLIB_COMPATIBLE_NAMES
  തരനിർവചനം unsigned അക്ഷരം Byte;
  തരനിർവചനം unsigned പൂർണ്ണസംഖ്യ uInt;
  തരനിർവചനം mz_ulong uLong;
  തരനിർവചനം Byte Bytef;
  തരനിർവചനം uInt uIntf;
  തരനിർവചനം അക്ഷരം charf;
  തരനിർവചനം പൂർണ്ണസംഖ്യ intf;
  തരനിർവചനം ശൂന്യം *voidpf;
  തരനിർവചനം uLong uLongf;
  തരനിർവചനം ശൂന്യം *voidp;
  തരനിർവചനം ശൂന്യം *സ്ഥിരം voidpc;
  #define Z_NULL                0
  #define Z_NO_FLUSH            MZ_NO_FLUSH
  #define Z_PARTIAL_FLUSH       MZ_PARTIAL_FLUSH
  #define Z_SYNC_FLUSH          MZ_SYNC_FLUSH
  #define Z_FULL_FLUSH          MZ_FULL_FLUSH
  #define Z_FINISH              MZ_FINISH
  #define Z_BLOCK               MZ_BLOCK
  #define Z_OK                  MZ_OK
  #define Z_STREAM_END          MZ_STREAM_END
  #define Z_NEED_DICT           MZ_NEED_DICT
  #define Z_ERRNO               MZ_ERRNO
  #define Z_STREAM_ERROR        MZ_STREAM_ERROR
  #define Z_DATA_ERROR          MZ_DATA_ERROR
  #define Z_MEM_ERROR           MZ_MEM_ERROR
  #define Z_BUF_ERROR           MZ_BUF_ERROR
  #define Z_VERSION_ERROR       MZ_VERSION_ERROR
  #define Z_PARAM_ERROR         MZ_PARAM_ERROR
  #define Z_NO_COMPRESSION      MZ_NO_COMPRESSION
  #define Z_BEST_SPEED          MZ_BEST_SPEED
  #define Z_BEST_COMPRESSION    MZ_BEST_COMPRESSION
  #define Z_DEFAULT_COMPRESSION MZ_DEFAULT_COMPRESSION
  #define Z_DEFAULT_STRATEGY    MZ_DEFAULT_STRATEGY
  #define Z_FILTERED            MZ_FILTERED
  #define Z_HUFFMAN_ONLY        MZ_HUFFMAN_ONLY
  #define Z_RLE                 MZ_RLE
  #define Z_FIXED               MZ_FIXED
  #define Z_DEFLATED            MZ_DEFLATED
  #define Z_DEFAULT_WINDOW_BITS MZ_DEFAULT_WINDOW_BITS
  #define alloc_func            mz_alloc_func
  #define free_func             mz_free_func
  #define internal_state        mz_internal_state
  #define z_stream              mz_stream
#ifndef MINIZ_NO_DEFLATE_APIS
  #define deflateInit           mz_deflateInit
  #define deflateInit2          mz_deflateInit2
  #define deflateReset          mz_deflateReset
  #define deflate               mz_deflate
  #define deflateEnd            mz_deflateEnd
  #define deflateBound          mz_deflateBound
  #define compress              mz_compress
  #define compress2             mz_compress2
  #define compressBound         mz_compressBound
#endif /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#ifndef MINIZ_NO_INFLATE_APIS
  #define inflateInit           mz_inflateInit
  #define inflateInit2          mz_inflateInit2
  #define inflate               mz_inflate
  #define inflateEnd            mz_inflateEnd
  #define uncompress            mz_uncompress
#endif /*#ifndef MINIZ_NO_INFLATE_APIS*/
  #define crc32                 mz_crc32
  #define adler32               mz_adler32
  #define MAX_WBITS             15
  #define MAX_MEM_LEVEL         9
  #define zError                mz_error
  #define ZLIB_VERSION          MZ_VERSION
  #define ZLIB_VERNUM           MZ_VERNUM
  #define ZLIB_VER_MAJOR        MZ_VER_MAJOR
  #define ZLIB_VER_MINOR        MZ_VER_MINOR
  #define ZLIB_VER_REVISION     MZ_VER_REVISION
  #define ZLIB_VER_SUBREVISION  MZ_VER_SUBREVISION
  #define zlibVersion           mz_version
  #define zlib_version          mz_version()
#endif // #ifndef MINIZ_NO_ZLIB_COMPATIBLE_NAMES

#endif // MINIZ_NO_ZLIB_APIS

// ------------------- Types and macros

തരനിർവചനം unsigned അക്ഷരം mz_uint8;
തരനിർവചനം signed short mz_int16;
തരനിർവചനം unsigned short mz_uint16;
തരനിർവചനം unsigned പൂർണ്ണസംഖ്യ mz_uint32;
തരനിർവചനം unsigned പൂർണ്ണസംഖ്യ mz_uint;
തരനിർവചനം long long mz_int64;
തരനിർവചനം unsigned long long mz_uint64;
തരനിർവചനം പൂർണ്ണസംഖ്യ mz_bool;

#define MZ_FALSE (0)
#define MZ_TRUE (1)

// An attempt to work around MSVC's spammy "warning C4127: conditional expression is constant" message.
#ifdef _MSC_VER
   #define MZ_MACRO_END ആകുമ്പോൾ (0, 0)
#അല്ലെങ്കിൽ
   #define MZ_MACRO_END ആകുമ്പോൾ (0)
#endif

// ------------------- ZIP archive reading/writing

#ifndef MINIZ_NO_ARCHIVE_APIS

എണ്ണൽ
{
  MZ_ZIP_MAX_IO_BUF_SIZE = 64*1024,
  MZ_ZIP_MAX_ARCHIVE_FILENAME_SIZE = 260,
  MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_SIZE = 256
};

തരനിർവചനം ഘടന
{
  mz_uint32 m_file_index;
  mz_uint32 m_central_dir_ofs;
  mz_uint16 m_version_made_by;
  mz_uint16 m_version_needed;
  mz_uint16 m_bit_flag;
  mz_uint16 m_method;
#ifndef MINIZ_NO_TIME
  time_t m_time;
#endif
  mz_uint32 m_crc32;
  mz_uint64 m_comp_size;
  mz_uint64 m_uncomp_size;
  mz_uint16 m_internal_attr;
  mz_uint32 m_external_attr;
  mz_uint64 m_local_header_ofs;
  mz_uint32 m_comment_size;
  അക്ഷരം m_filename[MZ_ZIP_MAX_ARCHIVE_FILENAME_SIZE];
  അക്ഷരം m_comment[MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_SIZE];
} mz_zip_archive_file_stat;

തരനിർവചനം size_t (*mz_file_read_func)(ശൂന്യം *pOpaque, mz_uint64 file_ofs, ശൂന്യം *pBuf, size_t n);
തരനിർവചനം size_t (*mz_file_write_func)(ശൂന്യം *pOpaque, mz_uint64 file_ofs, സ്ഥിരം ശൂന്യം *pBuf, size_t n);

ഘടന mz_zip_internal_state_tag;
തരനിർവചനം ഘടന mz_zip_internal_state_tag mz_zip_internal_state;

തരനിർവചനം എണ്ണൽ
{
  MZ_ZIP_MODE_INVALID = 0,
  MZ_ZIP_MODE_READING = 1,
  MZ_ZIP_MODE_WRITING = 2,
  MZ_ZIP_MODE_WRITING_HAS_BEEN_FINALIZED = 3
} mz_zip_mode;

തരനിർവചനം ഘടന mz_zip_archive_tag
{
  mz_uint64 m_archive_size;
  mz_uint64 m_central_directory_file_ofs;
  mz_uint m_total_files;
  mz_zip_mode m_zip_mode;

  mz_uint m_file_offset_alignment;

  mz_alloc_func m_pAlloc;
  mz_free_func m_pFree;
  mz_realloc_func m_pRealloc;
  ശൂന്യം *m_pAlloc_opaque;

  mz_file_read_func m_pRead;
  mz_file_write_func m_pWrite;
  ശൂന്യം *m_pIO_opaque;

  mz_zip_internal_state *m_pState;

} mz_zip_archive;

തരനിർവചനം എണ്ണൽ
{
  MZ_ZIP_FLAG_CASE_SENSITIVE                = 0x0100,
  MZ_ZIP_FLAG_IGNORE_PATH                   = 0x0200,
  MZ_ZIP_FLAG_COMPRESSED_DATA               = 0x0400,
  MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY = 0x0800
} mz_zip_flags;

// ZIP archive reading

// Inits a ZIP archive reader.
// These functions read and validate the archive's central directory.
MINIZ_STATIC mz_bool mz_zip_reader_init(mz_zip_archive *pZip, mz_uint64 size, mz_uint32 flags);
MINIZ_STATIC mz_bool mz_zip_reader_init_mem(mz_zip_archive *pZip, സ്ഥിരം ശൂന്യം *pMem, size_t size, mz_uint32 flags);

#ifndef MINIZ_NO_STDIO
MINIZ_STATIC mz_bool mz_zip_reader_init_file(mz_zip_archive *pZip, സ്ഥിരം അക്ഷരം *pFilename, mz_uint32 flags);
#endif

// Returns the total number of files in the archive.
MINIZ_STATIC mz_uint mz_zip_reader_get_അക്കം_files(mz_zip_archive *pZip);

// Returns detailed information about an archive file entry.
MINIZ_STATIC mz_bool mz_zip_reader_file_stat(mz_zip_archive *pZip, mz_uint file_index, mz_zip_archive_file_stat *pStat);

// Determines if an archive file entry is a directory entry.
MINIZ_STATIC mz_bool mz_zip_reader_is_file_a_directory(mz_zip_archive *pZip, mz_uint file_index);
MINIZ_STATIC mz_bool mz_zip_reader_is_file_encrypted(mz_zip_archive *pZip, mz_uint file_index);

// Retrieves the filename of an archive file entry.
// Returns the number of bytes written to pFilename, or if filename_buf_size is 0 this function returns the number of bytes needed to fully store the filename.
MINIZ_STATIC mz_uint mz_zip_reader_get_filename(mz_zip_archive *pZip, mz_uint file_index, അക്ഷരം *pFilename, mz_uint filename_buf_size);

// Attempts to locates a file in the archive's central directory.
// Valid flags: MZ_ZIP_FLAG_CASE_SENSITIVE, MZ_ZIP_FLAG_IGNORE_PATH
// Returns -1 if the file cannot be found.
MINIZ_STATIC പൂർണ്ണസംഖ്യ mz_zip_reader_locate_file(mz_zip_archive *pZip, സ്ഥിരം അക്ഷരം *pName, സ്ഥിരം അക്ഷരം *pComment, mz_uint flags);

// Extracts a archive file to a memory buffer using no memory allocation.
MINIZ_STATIC mz_bool mz_zip_reader_extract_to_mem_no_alloc(mz_zip_archive *pZip, mz_uint file_index, ശൂന്യം *pBuf, size_t buf_size, mz_uint flags, ശൂന്യം *pUser_read_buf, size_t user_read_buf_size);
MINIZ_STATIC mz_bool mz_zip_reader_extract_file_to_mem_no_alloc(mz_zip_archive *pZip, സ്ഥിരം അക്ഷരം *pFilename, ശൂന്യം *pBuf, size_t buf_size, mz_uint flags, ശൂന്യം *pUser_read_buf, size_t user_read_buf_size);

// Extracts a archive file to a memory buffer.
MINIZ_STATIC mz_bool mz_zip_reader_extract_to_mem(mz_zip_archive *pZip, mz_uint file_index, ശൂന്യം *pBuf, size_t buf_size, mz_uint flags);
MINIZ_STATIC mz_bool mz_zip_reader_extract_file_to_mem(mz_zip_archive *pZip, സ്ഥിരം അക്ഷരം *pFilename, ശൂന്യം *pBuf, size_t buf_size, mz_uint flags);

// Extracts a archive file to a dynamically allocated heap buffer.
MINIZ_STATIC ശൂന്യം *mz_zip_reader_extract_to_heap(mz_zip_archive *pZip, mz_uint file_index, size_t *pSize, mz_uint flags);
MINIZ_STATIC ശൂന്യം *mz_zip_reader_extract_file_to_heap(mz_zip_archive *pZip, സ്ഥിരം അക്ഷരം *pFilename, size_t *pSize, mz_uint flags);

// Extracts a archive file using a callback function to output the file's data.
MINIZ_STATIC mz_bool mz_zip_reader_extract_to_callback(mz_zip_archive *pZip, mz_uint file_index, mz_file_write_func pCallback, ശൂന്യം *pOpaque, mz_uint flags);
MINIZ_STATIC mz_bool mz_zip_reader_extract_file_to_callback(mz_zip_archive *pZip, സ്ഥിരം അക്ഷരം *pFilename, mz_file_write_func pCallback, ശൂന്യം *pOpaque, mz_uint flags);

#ifndef MINIZ_NO_STDIO
// Extracts a archive file to a disk file and sets its last accessed and modified times.
// This function only extracts files, not archive directory records.
MINIZ_STATIC mz_bool mz_zip_reader_extract_to_file(mz_zip_archive *pZip, mz_uint file_index, സ്ഥിരം അക്ഷരം *pDst_filename, mz_uint flags);
MINIZ_STATIC mz_bool mz_zip_reader_extract_file_to_file(mz_zip_archive *pZip, സ്ഥിരം അക്ഷരം *pArchive_filename, സ്ഥിരം അക്ഷരം *pDst_filename, mz_uint flags);
#endif

// Ends archive reading, freeing all allocations, and closing the input archive file if mz_zip_reader_init_file() was used.
MINIZ_STATIC mz_bool mz_zip_reader_end(mz_zip_archive *pZip);

// ZIP archive writing

#ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

// Inits a ZIP archive writer.
MINIZ_STATIC mz_bool mz_zip_writer_init(mz_zip_archive *pZip, mz_uint64 existing_size);
MINIZ_STATIC mz_bool mz_zip_writer_init_heap(mz_zip_archive *pZip, size_t size_to_reserve_at_beginning, size_t initial_allocation_size);

#ifndef MINIZ_NO_STDIO
MINIZ_STATIC mz_bool mz_zip_writer_init_file(mz_zip_archive *pZip, സ്ഥിരം അക്ഷരം *pFilename, mz_uint64 size_to_reserve_at_beginning);
#endif

// Converts a ZIP archive reader object into a writer object, to allow efficient in-place file appends to occur on an existing archive.
// For archives opened using mz_zip_reader_init_file, pFilename must be the archive's filename so it can be reopened for writing. If the file can't be reopened, mz_zip_reader_end() will be called.
// For archives opened using mz_zip_reader_init_mem, the memory block must be growable using the realloc callback (which defaults to realloc unless you've overridden it).
// Finally, for archives opened using mz_zip_reader_init, the mz_zip_archive's user provided m_pWrite function cannot be NULL.
// Note: In-place archive modification is not recommended unless you know what you're doing, because if execution stops or something goes wrong before
// the archive is finalized the file's central directory will be hosed.
MINIZ_STATIC mz_bool mz_zip_writer_init_from_reader(mz_zip_archive *pZip, സ്ഥിരം അക്ഷരം *pFilename);

// Adds the contents of a memory buffer to an archive. These functions record the current local time into the archive.
// To add a directory entry, call this method with an archive name ending in a forwardslash with empty buffer.
// level_and_flags - compression level (0-10, see MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or just set to MZ_DEFAULT_COMPRESSION.
MINIZ_STATIC mz_bool mz_zip_writer_add_mem(mz_zip_archive *pZip, സ്ഥിരം അക്ഷരം *pArchive_name, സ്ഥിരം ശൂന്യം *pBuf, size_t buf_size, mz_uint level_and_flags);
MINIZ_STATIC mz_bool mz_zip_writer_add_mem_ex(mz_zip_archive *pZip, സ്ഥിരം അക്ഷരം *pArchive_name, സ്ഥിരം ശൂന്യം *pBuf, size_t buf_size, സ്ഥിരം ശൂന്യം *pComment, mz_uint16 comment_size, mz_uint level_and_flags, mz_uint64 uncomp_size, mz_uint32 uncomp_crc32);

#ifndef MINIZ_NO_STDIO
// Adds the contents of a disk file to an archive. This function also records the disk file's modified time into the archive.
// level_and_flags - compression level (0-10, see MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or just set to MZ_DEFAULT_COMPRESSION.
MINIZ_STATIC mz_bool mz_zip_writer_add_file(mz_zip_archive *pZip, സ്ഥിരം അക്ഷരം *pArchive_name, സ്ഥിരം അക്ഷരം *pSrc_filename, സ്ഥിരം ശൂന്യം *pComment, mz_uint16 comment_size, mz_uint level_and_flags);
#endif

// Adds a file to an archive by fully cloning the data from another archive.
// This function fully clones the source file's compressed data (no recompression), along with its full filename, extra data, and comment fields.
MINIZ_STATIC mz_bool mz_zip_writer_add_from_zip_reader(mz_zip_archive *pZip, mz_zip_archive *pSource_zip, mz_uint file_index);

// Finalizes the archive by writing the central directory records followed by the end of central directory record.
// After an archive is finalized, the only valid call on the mz_zip_archive struct is mz_zip_writer_end().
// An archive must be manually finalized by calling this function for it to be valid.
MINIZ_STATIC mz_bool mz_zip_writer_finalize_archive(mz_zip_archive *pZip);
MINIZ_STATIC mz_bool mz_zip_writer_finalize_heap_archive(mz_zip_archive *pZip, ശൂന്യം **pBuf, size_t *pSize);

// Ends archive writing, freeing all allocations, and closing the output file if mz_zip_writer_init_file() was used.
// Note for the archive to be valid, it must have been finalized before ending.
MINIZ_STATIC mz_bool mz_zip_writer_end(mz_zip_archive *pZip);

// Misc. high-level helper functions:

// mz_zip_add_mem_to_archive_file_in_place() efficiently (but not atomically) appends a memory blob to a ZIP archive.
// level_and_flags - compression level (0-10, see MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or just set to MZ_DEFAULT_COMPRESSION.
MINIZ_STATIC mz_bool mz_zip_add_mem_to_archive_file_in_place(സ്ഥിരം അക്ഷരം *pZip_filename, സ്ഥിരം അക്ഷരം *pArchive_name, സ്ഥിരം ശൂന്യം *pBuf, size_t buf_size, സ്ഥിരം ശൂന്യം *pComment, mz_uint16 comment_size, mz_uint level_and_flags);

// Reads a single file from an archive into a heap block.
// Returns NULL on failure.
MINIZ_STATIC ശൂന്യം *mz_zip_extract_archive_file_to_heap(സ്ഥിരം അക്ഷരം *pZip_filename, സ്ഥിരം അക്ഷരം *pArchive_name, size_t *pSize, mz_uint zip_flags);

#endif // #ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

#endif // #ifndef MINIZ_NO_ARCHIVE_APIS

// ------------------- Low-level Decompression API Definitions
#ifndef MINIZ_NO_INFLATE_APIS

// Decompression flags used by tinfl_decompress().
// TINFL_FLAG_PARSE_ZLIB_HEADER: If set, the input has a valid zlib header and ends with an adler32 checksum (it's a valid zlib stream). Otherwise, the input is a raw deflate stream.
// TINFL_FLAG_HAS_MORE_INPUT: If set, there are more input bytes available beyond the end of the supplied input buffer. If clear, the input buffer contains all remaining input.
// TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF: If set, the output buffer is large enough to hold the entire decompressed stream. If clear, the output buffer is at least the size of the dictionary (typically 32KB).
// TINFL_FLAG_COMPUTE_ADLER32: Force adler-32 checksum computation of the decompressed bytes.
എണ്ണൽ
{
  TINFL_FLAG_PARSE_ZLIB_HEADER = 1,
  TINFL_FLAG_HAS_MORE_നിവേശം = 2,
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
MINIZ_STATIC ശൂന്യം *tinfl_decompress_mem_to_heap(സ്ഥിരം ശൂന്യം *pSrc_buf, size_t src_buf_len, size_t *pOut_len, പൂർണ്ണസംഖ്യ flags);

// tinfl_decompress_mem_to_mem() decompresses a block in memory to another block in memory.
// Returns TINFL_DECOMPRESS_MEM_TO_MEM_FAILED on failure, or the number of bytes written on success.
#define TINFL_DECOMPRESS_MEM_TO_MEM_FAILED ((size_t)(-1))
MINIZ_STATIC size_t tinfl_decompress_mem_to_mem(ശൂന്യം *pOut_buf, size_t out_buf_len, സ്ഥിരം ശൂന്യം *pSrc_buf, size_t src_buf_len, പൂർണ്ണസംഖ്യ flags);

// tinfl_decompress_mem_to_callback() decompresses a block in memory to an internal 32KB buffer, and a user provided callback function will be called to flush the buffer.
// Returns 1 on success or 0 on failure.
തരനിർവചനം പൂർണ്ണസംഖ്യ (*tinfl_put_buf_func_ptr)(സ്ഥിരം ശൂന്യം* pBuf, പൂർണ്ണസംഖ്യ len, ശൂന്യം *pUser);
MINIZ_STATIC പൂർണ്ണസംഖ്യ tinfl_decompress_mem_to_callback(സ്ഥിരം ശൂന്യം *pIn_buf, size_t *pIn_buf_size, tinfl_put_buf_func_ptr pPut_buf_func, ശൂന്യം *pPut_buf_user, പൂർണ്ണസംഖ്യ flags);

ഘടന tinfl_decompressor_tag; തരനിർവചനം ഘടന tinfl_decompressor_tag tinfl_decompressor;

// Max size of LZ dictionary.
#define TINFL_LZ_DICT_SIZE 32768

// Return status.
തരനിർവചനം എണ്ണൽ
{
  TINFL_STATUS_BAD_PARAM = -3,
  TINFL_STATUS_ADLER32_MISMATCH = -2,
  TINFL_STATUS_FAILED = -1,
  TINFL_STATUS_DONE = 0,
  TINFL_STATUS_NEEDS_MORE_നിവേശം = 1,
  TINFL_STATUS_HAS_MORE_OUTPUT = 2
} tinfl_status;

// Initializes the decompressor to its initial state.
#define tinfl_init(r) ചെയ്യുക { (r)->m_state = 0; } MZ_MACRO_END
#define tinfl_get_adler32(r) (r)->m_check_adler32

// Main low-level decompressor coroutine function. This is the only function actually needed for decompression. All the other functions are just high-level helpers for improved usability.
// This is a universal API, i.e. it can be used as a building block to build any desired higher level decompression API. In the limit case, it can be called once per every byte input or output.
MINIZ_STATIC tinfl_status tinfl_decompress(tinfl_decompressor *r, സ്ഥിരം mz_uint8 *pIn_buf_next, size_t *pIn_buf_size, mz_uint8 *pOut_buf_start, mz_uint8 *pOut_buf_next, size_t *pOut_buf_size, സ്ഥിരം mz_uint32 decomp_flags);

// Internal/private bits follow.
എണ്ണൽ
{
  TINFL_MAX_HUFF_TABLES = 3, TINFL_MAX_HUFF_SYMBOLS_0 = 288, TINFL_MAX_HUFF_SYMBOLS_1 = 32, TINFL_MAX_HUFF_SYMBOLS_2 = 19,
  TINFL_FAST_LOOKUP_BITS = 10, TINFL_FAST_LOOKUP_SIZE = 1 << TINFL_FAST_LOOKUP_BITS
};

തരനിർവചനം ഘടന
{
  mz_uint8 m_code_size[TINFL_MAX_HUFF_SYMBOLS_0];
  mz_int16 m_look_up[TINFL_FAST_LOOKUP_SIZE], m_വൃക്ഷം[TINFL_MAX_HUFF_SYMBOLS_0 * 2];
} tinfl_huff_table;

#എങ്കിൽ MINIZ_HAS_64BIT_REGISTERS
  #define TINFL_USE_64BIT_BITBUF 1
#endif

#എങ്കിൽ TINFL_USE_64BIT_BITBUF
  തരനിർവചനം mz_uint64 tinfl_bit_buf_t;
  #define TINFL_BITBUF_SIZE (64)
#അല്ലെങ്കിൽ
  തരനിർവചനം mz_uint32 tinfl_bit_buf_t;
  #define TINFL_BITBUF_SIZE (32)
#endif

ഘടന tinfl_decompressor_tag
{
  mz_uint32 m_state, m_അക്കം_bits, m_zhdr0, m_zhdr1, m_z_adler32, m_final, m_type, m_check_adler32, m_dist, m_counter, m_അക്കം_extra, m_table_sizes[TINFL_MAX_HUFF_TABLES];
  tinfl_bit_buf_t m_bit_buf;
  size_t m_dist_from_out_buf_start;
  tinfl_huff_table m_tables[TINFL_MAX_HUFF_TABLES];
  mz_uint8 m_raw_header[4], m_len_codes[TINFL_MAX_HUFF_SYMBOLS_0 + TINFL_MAX_HUFF_SYMBOLS_1 + 137];
};
#endif /*#ifndef MINIZ_NO_INFLATE_APIS*/

// ------------------- Low-level Compression API Definitions
#ifndef MINIZ_NO_DEFLATE_APIS

// Set TDEFL_LESS_MEMORY to 1 to use less memory (compression will be slightly slower, and raw/dynamic blocks will be output more frequently).
#define TDEFL_LESS_MEMORY 0

// tdefl_init() compression flags logically OR'd together (low 12 bits contain the max. number of probes per dictionary search):
// TDEFL_DEFAULT_MAX_PROBES: The compressor defaults to 128 dictionary probes per dictionary search. 0=Huffman only, 1=Huffman+LZ (fastest/crap compression), 4095=Huffman+LZ (slowest/best compression).
എണ്ണൽ
{
  TDEFL_HUFFMAN_ONLY = 0, TDEFL_DEFAULT_MAX_PROBES = 128, TDEFL_MAX_PROBES_MASK = 0xFFF
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
എണ്ണൽ
{
  TDEFL_WRITE_ZLIB_HEADER             = 0x01000,
  TDEFL_COMPUTE_ADLER32               = 0x02000,
  TDEFL_GREEDY_PARSING_FLAG           = 0x04000,
  TDEFL_NONDETERMINISTIC_PARSING_FLAG = 0x08000,
  TDEFL_RLE_MATCHES                   = 0x10000,
  TDEFL_FILTER_MATCHES                = 0x20000,
  TDEFL_FORCE_ALL_STATIC_BLOCKS       = 0x40000,
  TDEFL_FORCE_ALL_RAW_BLOCKS          = 0x80000
};

#ifndef MINIZ_SDL_NOUNUSED
// High level compression functions:
// tdefl_compress_mem_to_heap() compresses a block in memory to a heap block allocated via malloc().
// On entry:
//  pSrc_buf, src_buf_len: Pointer and size of source block to compress.
//  flags: The max match finder probes (default is 128) logically OR'd against the above flags. Higher probes are slower but improve compression.
// On return:
//  Function returns a pointer to the compressed data, or NULL on failure.
//  *pOut_len will be set to the compressed data's size, which could be larger than src_buf_len on uncompressible data.
//  The caller must free() the returned block when it's no longer needed.
MINIZ_STATIC ശൂന്യം *tdefl_compress_mem_to_heap(സ്ഥിരം ശൂന്യം *pSrc_buf, size_t src_buf_len, size_t *pOut_len, പൂർണ്ണസംഖ്യ flags);

// tdefl_compress_mem_to_mem() compresses a block in memory to another block in memory.
// Returns 0 on failure.
MINIZ_STATIC size_t tdefl_compress_mem_to_mem(ശൂന്യം *pOut_buf, size_t out_buf_len, സ്ഥിരം ശൂന്യം *pSrc_buf, size_t src_buf_len, പൂർണ്ണസംഖ്യ flags);
#endif /* MINIZ_SDL_NOUNUSED */

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
MINIZ_STATIC ശൂന്യം *tdefl_write_image_to_png_file_in_memory_ex(സ്ഥിരം ശൂന്യം *pImage, പൂർണ്ണസംഖ്യ w, പൂർണ്ണസംഖ്യ h, പൂർണ്ണസംഖ്യ അക്കം_chans, പൂർണ്ണസംഖ്യ bpl, size_t *pLen_out, mz_uint level, mz_bool flip, mz_uint8 *plte, പൂർണ്ണസംഖ്യ plte_size, mz_uint8 *trns, പൂർണ്ണസംഖ്യ trns_size);
#ifndef MINIZ_SDL_NOUNUSED
MINIZ_STATIC ശൂന്യം *tdefl_write_image_to_png_file_in_memory(സ്ഥിരം ശൂന്യം *pImage, പൂർണ്ണസംഖ്യ w, പൂർണ്ണസംഖ്യ h, പൂർണ്ണസംഖ്യ അക്കം_chans, പൂർണ്ണസംഖ്യ bpl, size_t *pLen_out);
#endif

// Output stream interface. The compressor uses this interface to write compressed data. It'll typically be called TDEFL_OUT_BUF_SIZE at a time.
തരനിർവചനം mz_bool (*tdefl_put_buf_func_ptr)(സ്ഥിരം ശൂന്യം* pBuf, പൂർണ്ണസംഖ്യ len, ശൂന്യം *pUser);

#ifndef MINIZ_SDL_NOUNUSED
// tdefl_compress_mem_to_output() compresses a block to an output stream. The above helpers use this function internally.
MINIZ_STATIC mz_bool tdefl_compress_mem_to_output(സ്ഥിരം ശൂന്യം *pBuf, size_t buf_len, tdefl_put_buf_func_ptr pPut_buf_func, ശൂന്യം *pPut_buf_user, പൂർണ്ണസംഖ്യ flags);
#endif

//enum { TDEFL_MAX_HUFF_TABLES = 3, TDEFL_MAX_HUFF_SYMBOLS_0 = 288, TDEFL_MAX_HUFF_SYMBOLS_1 = 32, TDEFL_MAX_HUFF_SYMBOLS_2 = 19, TDEFL_LZ_DICT_SIZE = 32768, TDEFL_LZ_DICT_SIZE_MASK = TDEFL_LZ_DICT_SIZE - 1, TDEFL_MIN_MATCH_LEN = 3, TDEFL_MAX_MATCH_LEN = 258 };
#define TDEFL_MAX_HUFF_TABLES	3
#define TDEFL_MAX_HUFF_SYMBOLS_0 288
#define TDEFL_MAX_HUFF_SYMBOLS_1 32
#define TDEFL_MAX_HUFF_SYMBOLS_2 19
#define TDEFL_LZ_DICT_SIZE 32768
#define TDEFL_LZ_DICT_SIZE_MASK	( TDEFL_LZ_DICT_SIZE - 1 )
#define TDEFL_MIN_MATCH_LEN	3
#define TDEFL_MAX_MATCH_LEN 258

// TDEFL_OUT_BUF_SIZE MUST be large enough to hold a single entire compressed output block (using static/fixed Huffman codes).
#എങ്കിൽ TDEFL_LESS_MEMORY
എണ്ണൽ { TDEFL_LZ_CODE_BUF_SIZE = 24 * 1024, TDEFL_OUT_BUF_SIZE = (TDEFL_LZ_CODE_BUF_SIZE * 13 ) / 10, TDEFL_MAX_HUFF_SYMBOLS = 288, TDEFL_LZ_HASH_BITS = 12, TDEFL_LEVEL1_HASH_SIZE_MASK = 4095, TDEFL_LZ_HASH_SHIFT = (TDEFL_LZ_HASH_BITS + 2) / 3, TDEFL_LZ_HASH_SIZE = 1 << TDEFL_LZ_HASH_BITS };
#അല്ലെങ്കിൽ
എണ്ണൽ { TDEFL_LZ_CODE_BUF_SIZE = 64 * 1024, TDEFL_OUT_BUF_SIZE = (TDEFL_LZ_CODE_BUF_SIZE * 13 ) / 10, TDEFL_MAX_HUFF_SYMBOLS = 288, TDEFL_LZ_HASH_BITS = 15, TDEFL_LEVEL1_HASH_SIZE_MASK = 4095, TDEFL_LZ_HASH_SHIFT = (TDEFL_LZ_HASH_BITS + 2) / 3, TDEFL_LZ_HASH_SIZE = 1 << TDEFL_LZ_HASH_BITS };
#endif

// The low-level tdefl functions below may be used directly if the above helper functions aren't flexible enough. The low-level functions don't make any heap allocations, unlike the above helper functions.
തരനിർവചനം എണ്ണൽ
{
  TDEFL_STATUS_BAD_PARAM = -2,
  TDEFL_STATUS_PUT_BUF_FAILED = -1,
  TDEFL_STATUS_OKAY = 0,
  TDEFL_STATUS_DONE = 1,
} tdefl_status;

// Must map to MZ_NO_FLUSH, MZ_SYNC_FLUSH, etc. enums
തരനിർവചനം എണ്ണൽ
{
  TDEFL_NO_FLUSH = 0,
  TDEFL_SYNC_FLUSH = 2,
  TDEFL_FULL_FLUSH = 3,
  TDEFL_FINISH = 4
} tdefl_flush;

// tdefl's compression state structure.
തരനിർവചനം ഘടന
{
  tdefl_put_buf_func_ptr m_pPut_buf_func;
  ശൂന്യം *m_pPut_buf_user;
  mz_uint m_flags, m_max_probes[2];
  പൂർണ്ണസംഖ്യ m_greedy_parsing;
  mz_uint m_adler32, m_lookahead_pos, m_lookahead_size, m_dict_size;
  mz_uint8 *m_pLZ_code_buf, *m_pLZ_flags, *m_pOutput_buf, *m_pOutput_buf_end;
  mz_uint m_അക്കം_flags_ഇടത്, m_total_lz_bytes, m_lz_code_buf_dict_pos, m_bits_in, m_bit_buffer;
  mz_uint m_saved_match_dist, m_saved_match_len, m_saved_lit, m_output_flush_ofs, m_output_flush_remaining, m_finished, m_block_index, m_wants_to_finish;
  tdefl_status m_prev_return_status;
  സ്ഥിരം ശൂന്യം *m_pIn_buf;
  ശൂന്യം *m_pOut_buf;
  size_t *m_pIn_buf_size, *m_pOut_buf_size;
  tdefl_flush m_flush;
  സ്ഥിരം mz_uint8 *m_pSrc;
  size_t m_src_buf_ഇടത്, m_out_buf_ofs;
  mz_uint8 m_dict[TDEFL_LZ_DICT_SIZE + TDEFL_MAX_MATCH_LEN - 1];
  mz_uint16 m_huff_എണ്ണം[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint16 m_huff_codes[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint8 m_huff_code_sizes[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint8 m_lz_code_buf[TDEFL_LZ_CODE_BUF_SIZE];
  mz_uint16 m_next[TDEFL_LZ_DICT_SIZE];
  mz_uint16 m_hash[TDEFL_LZ_HASH_SIZE];
  mz_uint8 m_output_buf[TDEFL_OUT_BUF_SIZE];
} tdefl_compressor;

// Initializes the compressor.
// There is no corresponding deinit() function because the tdefl API's do not dynamically allocate memory.
// pBut_buf_func: If NULL, output data will be supplied to the specified callback. In this case, the user should call the tdefl_compress_buffer() API for compression.
// If pBut_buf_func is NULL the user should always call the tdefl_compress() API.
// flags: See the above enums (TDEFL_HUFFMAN_ONLY, TDEFL_WRITE_ZLIB_HEADER, etc.)
MINIZ_STATIC tdefl_status tdefl_init(tdefl_compressor *d, tdefl_put_buf_func_ptr pPut_buf_func, ശൂന്യം *pPut_buf_user, പൂർണ്ണസംഖ്യ flags);

// Compresses a block of data, consuming as much of the specified input buffer as possible, and writing as much compressed data to the specified output buffer as possible.
MINIZ_STATIC tdefl_status tdefl_compress(tdefl_compressor *d, സ്ഥിരം ശൂന്യം *pIn_buf, size_t *pIn_buf_size, ശൂന്യം *pOut_buf, size_t *pOut_buf_size, tdefl_flush flush);

// tdefl_compress_buffer() is only usable when the tdefl_init() is called with a non-NULL tdefl_put_buf_func_ptr.
// tdefl_compress_buffer() always consumes the entire input buffer.
MINIZ_STATIC tdefl_status tdefl_compress_buffer(tdefl_compressor *d, സ്ഥിരം ശൂന്യം *pIn_buf, size_t in_buf_size, tdefl_flush flush);

#ifndef MINIZ_SDL_NOUNUSED
MINIZ_STATIC tdefl_status tdefl_get_prev_return_status(tdefl_compressor *d);
MINIZ_STATIC mz_uint32 tdefl_get_adler32(tdefl_compressor *d);
#endif

// Can't use tdefl_create_comp_flags_from_zip_params if MINIZ_NO_ZLIB_APIS isn't defined, because it uses some of its macros.
#ifndef MINIZ_NO_ZLIB_APIS
// Create tdefl_compress() flags given zlib-style compression parameters.
// level may range from [0,10] (where 10 is absolute max compression, but may be much slower on some files)
// window_bits may be -15 (raw deflate) or 15 (zlib)
// strategy may be either MZ_DEFAULT_STRATEGY, MZ_FILTERED, MZ_HUFFMAN_ONLY, MZ_RLE, or MZ_FIXED
MINIZ_STATIC mz_uint tdefl_create_comp_flags_from_zip_params(പൂർണ്ണസംഖ്യ level, പൂർണ്ണസംഖ്യ window_bits, പൂർണ്ണസംഖ്യ strategy);
#endif // #ifndef MINIZ_NO_ZLIB_APIS

#endif /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#ifdef __cplusplus
}
#endif

#endif // MINIZ_HEADER_INCLUDED

// ------------------- End of Header: Implementation follows. (If you only want the header, define MINIZ_HEADER_FILE_ONLY.)

#ifndef MINIZ_HEADER_FILE_ONLY

#ifdef _MSC_VER
#pragma warning (തള്ളുക)
#pragma warning (disable:4505) // unreferenced local function has been removed
#endif

തരനിർവചനം unsigned അക്ഷരം mz_validate_uint16[വലുപ്പം(mz_uint16)==2 ? 1 : -1];
തരനിർവചനം unsigned അക്ഷരം mz_validate_uint32[വലുപ്പം(mz_uint32)==4 ? 1 : -1];
തരനിർവചനം unsigned അക്ഷരം mz_validate_uint64[വലുപ്പം(mz_uint64)==8 ? 1 : -1];

/*#include <string.h>*/

#ifndef MZ_ASSERT
#അന്തര്ഭാവ <assert.h>
#define MZ_ASSERT(x) പ്രതിജ്ഞാ(x)
#endif

#ifdef MINIZ_NO_MALLOC
  #define MZ_MALLOC(x) ശൂന്യ
  #define MZ_FREE(x) (ശൂന്യം)x, ((ശൂന്യം)0)
  #define MZ_REALLOC(p, x) ശൂന്യ
#അല്ലെങ്കിലെങ്കിൽ defined(MINIZ_SDL_MALLOC)
  #define MZ_MALLOC(x) SDL_malloc(x)
  #define MZ_FREE(x) SDL_free(x)
  #define MZ_REALLOC(p, x) SDL_realloc(p, x)
#അല്ലെങ്കിൽ
  #define MZ_MALLOC(x) malloc(x)
  #define MZ_FREE(x) സ്വതന്ത്രം(x)
  #define MZ_REALLOC(p, x) realloc(p, x)
#endif

#define MZ_MAX(a,b) (((a)>(b))?(a):(b))
#define MZ_MIN(a,b) (((a)<(b))?(a):(b))
#define MZ_CLEAR_OBJ(obj) memset(&(obj), 0, വലുപ്പം(obj))
#define MZ_CLEAR_ARR(obj) memset((obj), 0, വലുപ്പം(obj))
#define MZ_CLEAR_PTR(obj) memset((obj), 0, വലുപ്പം(*obj))

#എങ്കിൽ MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  #define MZ_READ_LE16(p) *((സ്ഥിരം mz_uint16 *)(p))
  #define MZ_READ_LE32(p) *((സ്ഥിരം mz_uint32 *)(p))
#അല്ലെങ്കിൽ
  #define MZ_READ_LE16(p) ((mz_uint32)(((സ്ഥിരം mz_uint8 *)(p))[0]) | ((mz_uint32)(((സ്ഥിരം mz_uint8 *)(p))[1]) << 8U))
  #define MZ_READ_LE32(p) ((mz_uint32)(((സ്ഥിരം mz_uint8 *)(p))[0]) | ((mz_uint32)(((സ്ഥിരം mz_uint8 *)(p))[1]) << 8U) | ((mz_uint32)(((സ്ഥിരം mz_uint8 *)(p))[2]) << 16U) | ((mz_uint32)(((സ്ഥിരം mz_uint8 *)(p))[3]) << 24U))
#endif

#ifdef _MSC_VER
  #define MZ_FORCEINLINE __forceinline
#അല്ലെങ്കിലെങ്കിൽ defined(__GNUC__)
  #define MZ_FORCEINLINE വരിയിൽ __attribute__((__always_inline__))
#അല്ലെങ്കിൽ
  #define MZ_FORCEINLINE വരിയിൽ
#endif

#ifdef __cplusplus
  ബാഹ്യ "C" {
#endif

// ------------------- zlib-style API's

mz_ulong mz_adler32(mz_ulong adler, സ്ഥിരം unsigned അക്ഷരം *ptr, size_t buf_len)
{
  mz_uint32 i, s1 = (mz_uint32)(adler & 0xffff), s2 = (mz_uint32)(adler >> 16); size_t block_len = buf_len % 5552;
  എങ്കിൽ (!ptr) തിരികെ MZ_ADLER32_INIT;
  ആകുമ്പോൾ (buf_len) {
    വേണ്ടി (i = 0; i + 7 < block_len; i += 8, ptr += 8) {
      s1 += ptr[0]; s2 += s1; s1 += ptr[1]; s2 += s1; s1 += ptr[2]; s2 += s1; s1 += ptr[3]; s2 += s1;
      s1 += ptr[4]; s2 += s1; s1 += ptr[5]; s2 += s1; s1 += ptr[6]; s2 += s1; s1 += ptr[7]; s2 += s1;
    }
    വേണ്ടി ( ; i < block_len; ++i) { s1 += *ptr++; s2 += s1; }
    s1 %= 65521U; s2 %= 65521U; buf_len -= block_len; block_len = 5552;
  }
  തിരികെ (s2 << 16) + s1;
}

// Karl Malbrain's compact CRC-32. See "A compact CCITT crc16 and crc32 C implementation that balances processor cache usage against speed": http://www.geocities.com/malbrain/
mz_ulong mz_crc32(mz_ulong crc, സ്ഥിരം mz_uint8 *ptr, size_t buf_len)
{
  സ്ഥിതം സ്ഥിരം mz_uint32 s_crc32[16] = { 0, 0x1db71064, 0x3b6e20c8, 0x26d930ac, 0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
    0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c, 0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c };
  mz_uint32 crcu32 = (mz_uint32)crc;
  എങ്കിൽ (!ptr) തിരികെ MZ_CRC32_INIT;
  crcu32 = ~crcu32; ആകുമ്പോൾ (buf_len--) { mz_uint8 b = *ptr++; crcu32 = (crcu32 >> 4) ^ s_crc32[(crcu32 & 0xF) ^ (b & 0xF)]; crcu32 = (crcu32 >> 4) ^ s_crc32[(crcu32 & 0xF) ^ (b >> 4)]; }
  തിരികെ ~crcu32;
}

MINIZ_STATIC ശൂന്യം mz_free(ശൂന്യം *p)
{
  MZ_FREE(p);
}

#ifndef MINIZ_NO_ZLIB_APIS

സ്ഥിതം ശൂന്യം *def_alloc_func(ശൂന്യം *opaque, size_t ഇനങ്ങൾ, size_t size) { (ശൂന്യം)opaque, (ശൂന്യം)ഇനങ്ങൾ, (ശൂന്യം)size; തിരികെ MZ_MALLOC(ഇനങ്ങൾ * size); }
സ്ഥിതം ശൂന്യം def_free_func(ശൂന്യം *opaque, ശൂന്യം *address) { (ശൂന്യം)opaque, (ശൂന്യം)address; MZ_FREE(address); }
സ്ഥിതം ശൂന്യം *def_realloc_func(ശൂന്യം *opaque, ശൂന്യം *address, size_t ഇനങ്ങൾ, size_t size) { (ശൂന്യം)opaque, (ശൂന്യം)address, (ശൂന്യം)ഇനങ്ങൾ, (ശൂന്യം)size; തിരികെ MZ_REALLOC(address, ഇനങ്ങൾ * size); }

സ്ഥിരം അക്ഷരം *mz_version(ശൂന്യം)
{
  തിരികെ MZ_VERSION;
}

#ifndef MINIZ_NO_DEFLATE_APIS

പൂർണ്ണസംഖ്യ mz_deflateInit(mz_streamp pStream, പൂർണ്ണസംഖ്യ level)
{
  തിരികെ mz_deflateInit2(pStream, level, MZ_DEFLATED, MZ_DEFAULT_WINDOW_BITS, 9, MZ_DEFAULT_STRATEGY);
}

പൂർണ്ണസംഖ്യ mz_deflateInit2(mz_streamp pStream, പൂർണ്ണസംഖ്യ level, പൂർണ്ണസംഖ്യ method, പൂർണ്ണസംഖ്യ window_bits, പൂർണ്ണസംഖ്യ mem_level, പൂർണ്ണസംഖ്യ strategy)
{
  tdefl_compressor *pComp;
  mz_uint comp_flags = TDEFL_COMPUTE_ADLER32 | tdefl_create_comp_flags_from_zip_params(level, window_bits, strategy);

  എങ്കിൽ (!pStream) തിരികെ MZ_STREAM_ERROR;
  എങ്കിൽ ((method != MZ_DEFLATED) || ((mem_level < 1) || (mem_level > 9)) || ((window_bits != MZ_DEFAULT_WINDOW_BITS) && (-window_bits != MZ_DEFAULT_WINDOW_BITS))) തിരികെ MZ_PARAM_ERROR;

  pStream->data_type = 0;
  pStream->adler = MZ_ADLER32_INIT;
  pStream->സന്ദേശം = ശൂന്യ;
  pStream->reserved = 0;
  pStream->total_in = 0;
  pStream->total_out = 0;
  എങ്കിൽ (!pStream->zalloc) pStream->zalloc = def_alloc_func;
  എങ്കിൽ (!pStream->zfree) pStream->zfree = def_free_func;

  pComp = (tdefl_compressor *)pStream->zalloc(pStream->opaque, 1, വലുപ്പം(tdefl_compressor));
  എങ്കിൽ (!pComp)
    തിരികെ MZ_MEM_ERROR;

  pStream->state = (ഘടന mz_internal_state *)pComp;

  എങ്കിൽ (tdefl_init(pComp, ശൂന്യ, ശൂന്യ, comp_flags) != TDEFL_STATUS_OKAY)
  {
    mz_deflateEnd(pStream);
    തിരികെ MZ_PARAM_ERROR;
  }

  തിരികെ MZ_OK;
}

പൂർണ്ണസംഖ്യ mz_deflateReset(mz_streamp pStream)
{
  എങ്കിൽ ((!pStream) || (!pStream->state) || (!pStream->zalloc) || (!pStream->zfree)) തിരികെ MZ_STREAM_ERROR;
  pStream->total_in = pStream->total_out = 0;
  tdefl_init((tdefl_compressor*)pStream->state, ശൂന്യ, ശൂന്യ, ((tdefl_compressor*)pStream->state)->m_flags);
  തിരികെ MZ_OK;
}

പൂർണ്ണസംഖ്യ mz_deflate(mz_streamp pStream, പൂർണ്ണസംഖ്യ flush)
{
  size_t in_bytes, out_bytes;
  mz_ulong orig_total_in, orig_total_out;
  പൂർണ്ണസംഖ്യ mz_status = MZ_OK;

  എങ്കിൽ ((!pStream) || (!pStream->state) || (flush < 0) || (flush > MZ_FINISH) || (!pStream->next_out)) തിരികെ MZ_STREAM_ERROR;
  എങ്കിൽ (!pStream->avail_out) തിരികെ MZ_BUF_ERROR;

  എങ്കിൽ (flush == MZ_PARTIAL_FLUSH) flush = MZ_SYNC_FLUSH;

  എങ്കിൽ (((tdefl_compressor*)pStream->state)->m_prev_return_status == TDEFL_STATUS_DONE)
    തിരികെ (flush == MZ_FINISH) ? MZ_STREAM_END : MZ_BUF_ERROR;

  orig_total_in = pStream->total_in; orig_total_out = pStream->total_out;
  വേണ്ടി ( ; ; )
  {
    tdefl_status defl_status;
    in_bytes = pStream->avail_in; out_bytes = pStream->avail_out;

    defl_status = tdefl_compress((tdefl_compressor*)pStream->state, pStream->next_in, &in_bytes, pStream->next_out, &out_bytes, (tdefl_flush)flush);
    pStream->next_in += (mz_uint)in_bytes; pStream->avail_in -= (mz_uint)in_bytes;
    pStream->total_in += (mz_uint)in_bytes; pStream->adler = tdefl_get_adler32((tdefl_compressor*)pStream->state);

    pStream->next_out += (mz_uint)out_bytes; pStream->avail_out -= (mz_uint)out_bytes;
    pStream->total_out += (mz_uint)out_bytes;

    എങ്കിൽ (defl_status < 0)
    {
      mz_status = MZ_STREAM_ERROR;
      നിർത്തുക;
    }
    അല്ലെങ്കിൽ എങ്കിൽ (defl_status == TDEFL_STATUS_DONE)
    {
      mz_status = MZ_STREAM_END;
      നിർത്തുക;
    }
    അല്ലെങ്കിൽ എങ്കിൽ (!pStream->avail_out)
      നിർത്തുക;
    അല്ലെങ്കിൽ എങ്കിൽ ((!pStream->avail_in) && (flush != MZ_FINISH))
    {
      എങ്കിൽ ((flush) || (pStream->total_in != orig_total_in) || (pStream->total_out != orig_total_out))
        നിർത്തുക;
      തിരികെ MZ_BUF_ERROR; // Can't make forward progress without some input.
    }
  }
  തിരികെ mz_status;
}

പൂർണ്ണസംഖ്യ mz_deflateEnd(mz_streamp pStream)
{
  എങ്കിൽ (!pStream) തിരികെ MZ_STREAM_ERROR;
  എങ്കിൽ (pStream->state)
  {
    pStream->zfree(pStream->opaque, pStream->state);
    pStream->state = ശൂന്യ;
  }
  തിരികെ MZ_OK;
}

mz_ulong mz_deflateBound(mz_streamp pStream, mz_ulong source_len)
{
  (ശൂന്യം)pStream;
  // This is really over conservative. (And lame, but it's actually pretty tricky to compute a true upper bound given the way tdefl's blocking works.)
  തിരികെ MZ_MAX(128 + (source_len * 110) / 100, 128 + source_len + ((source_len / (31 * 1024)) + 1) * 5);
}

പൂർണ്ണസംഖ്യ mz_compress2(unsigned അക്ഷരം *pDest, mz_ulong *pDest_len, സ്ഥിരം unsigned അക്ഷരം *pSource, mz_ulong source_len, പൂർണ്ണസംഖ്യ level)
{
  പൂർണ്ണസംഖ്യ status;
  mz_stream stream;
  memset(&stream, 0, വലുപ്പം(stream));

  // In case mz_ulong is 64-bits (argh I hate longs).
  എങ്കിൽ ((source_len | *pDest_len) > 0xFFFFFFFFU) തിരികെ MZ_PARAM_ERROR;

  stream.next_in = pSource;
  stream.avail_in = (mz_uint32)source_len;
  stream.next_out = pDest;
  stream.avail_out = (mz_uint32)*pDest_len;

  status = mz_deflateInit(&stream, level);
  എങ്കിൽ (status != MZ_OK) തിരികെ status;

  status = mz_deflate(&stream, MZ_FINISH);
  എങ്കിൽ (status != MZ_STREAM_END)
  {
    mz_deflateEnd(&stream);
    തിരികെ (status == MZ_OK) ? MZ_BUF_ERROR : status;
  }

  *pDest_len = stream.total_out;
  തിരികെ mz_deflateEnd(&stream);
}

പൂർണ്ണസംഖ്യ mz_compress(unsigned അക്ഷരം *pDest, mz_ulong *pDest_len, സ്ഥിരം unsigned അക്ഷരം *pSource, mz_ulong source_len)
{
  തിരികെ mz_compress2(pDest, pDest_len, pSource, source_len, MZ_DEFAULT_COMPRESSION);
}

mz_ulong mz_compressBound(mz_ulong source_len)
{
  തിരികെ mz_deflateBound(ശൂന്യ, source_len);
}

#endif /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#ifndef MINIZ_NO_INFLATE_APIS

തരനിർവചനം ഘടന
{
  tinfl_decompressor m_decomp;
  mz_uint m_dict_ofs, m_dict_avail, m_first_call, m_has_flushed; പൂർണ്ണസംഖ്യ m_window_bits;
  mz_uint8 m_dict[TINFL_LZ_DICT_SIZE];
  tinfl_status m_last_status;
} inflate_state;

പൂർണ്ണസംഖ്യ mz_inflateInit2(mz_streamp pStream, പൂർണ്ണസംഖ്യ window_bits)
{
  inflate_state *pDecomp;
  എങ്കിൽ (!pStream) തിരികെ MZ_STREAM_ERROR;
  എങ്കിൽ ((window_bits != MZ_DEFAULT_WINDOW_BITS) && (-window_bits != MZ_DEFAULT_WINDOW_BITS)) തിരികെ MZ_PARAM_ERROR;

  pStream->data_type = 0;
  pStream->adler = 0;
  pStream->സന്ദേശം = ശൂന്യ;
  pStream->total_in = 0;
  pStream->total_out = 0;
  pStream->reserved = 0;
  എങ്കിൽ (!pStream->zalloc) pStream->zalloc = def_alloc_func;
  എങ്കിൽ (!pStream->zfree) pStream->zfree = def_free_func;

  pDecomp = (inflate_state*)pStream->zalloc(pStream->opaque, 1, വലുപ്പം(inflate_state));
  എങ്കിൽ (!pDecomp) തിരികെ MZ_MEM_ERROR;

  pStream->state = (ഘടന mz_internal_state *)pDecomp;

  tinfl_init(&pDecomp->m_decomp);
  pDecomp->m_dict_ofs = 0;
  pDecomp->m_dict_avail = 0;
  pDecomp->m_last_status = TINFL_STATUS_NEEDS_MORE_നിവേശം;
  pDecomp->m_first_call = 1;
  pDecomp->m_has_flushed = 0;
  pDecomp->m_window_bits = window_bits;

  തിരികെ MZ_OK;
}

പൂർണ്ണസംഖ്യ mz_inflateInit(mz_streamp pStream)
{
   തിരികെ mz_inflateInit2(pStream, MZ_DEFAULT_WINDOW_BITS);
}

പൂർണ്ണസംഖ്യ mz_inflate(mz_streamp pStream, പൂർണ്ണസംഖ്യ flush)
{
  inflate_state* pState;
  mz_uint n, first_call, decomp_flags = TINFL_FLAG_COMPUTE_ADLER32;
  size_t in_bytes, out_bytes, orig_avail_in;
  tinfl_status status;

  എങ്കിൽ ((!pStream) || (!pStream->state)) തിരികെ MZ_STREAM_ERROR;
  എങ്കിൽ (flush == MZ_PARTIAL_FLUSH) flush = MZ_SYNC_FLUSH;
  എങ്കിൽ ((flush) && (flush != MZ_SYNC_FLUSH) && (flush != MZ_FINISH)) തിരികെ MZ_STREAM_ERROR;

  pState = (inflate_state*)pStream->state;
  എങ്കിൽ (pState->m_window_bits > 0) decomp_flags |= TINFL_FLAG_PARSE_ZLIB_HEADER;
  orig_avail_in = pStream->avail_in;

  first_call = pState->m_first_call; pState->m_first_call = 0;
  എങ്കിൽ (pState->m_last_status < 0) തിരികെ MZ_DATA_ERROR;

  എങ്കിൽ (pState->m_has_flushed && (flush != MZ_FINISH)) തിരികെ MZ_STREAM_ERROR;
  pState->m_has_flushed |= (flush == MZ_FINISH);

  എങ്കിൽ ((flush == MZ_FINISH) && (first_call))
  {
    // MZ_FINISH on the first call implies that the input and output buffers are large enough to hold the entire compressed/decompressed file.
    decomp_flags |= TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF;
    in_bytes = pStream->avail_in; out_bytes = pStream->avail_out;
    status = tinfl_decompress(&pState->m_decomp, pStream->next_in, &in_bytes, pStream->next_out, pStream->next_out, &out_bytes, decomp_flags);
    pState->m_last_status = status;
    pStream->next_in += (mz_uint)in_bytes; pStream->avail_in -= (mz_uint)in_bytes; pStream->total_in += (mz_uint)in_bytes;
    pStream->adler = tinfl_get_adler32(&pState->m_decomp);
    pStream->next_out += (mz_uint)out_bytes; pStream->avail_out -= (mz_uint)out_bytes; pStream->total_out += (mz_uint)out_bytes;

    എങ്കിൽ (status < 0)
      തിരികെ MZ_DATA_ERROR;
    അല്ലെങ്കിൽ എങ്കിൽ (status != TINFL_STATUS_DONE)
    {
      pState->m_last_status = TINFL_STATUS_FAILED;
      തിരികെ MZ_BUF_ERROR;
    }
    തിരികെ MZ_STREAM_END;
  }
  // flush != MZ_FINISH then we must assume there's more input.
  എങ്കിൽ (flush != MZ_FINISH) decomp_flags |= TINFL_FLAG_HAS_MORE_നിവേശം;

  എങ്കിൽ (pState->m_dict_avail)
  {
    n = MZ_MIN(pState->m_dict_avail, pStream->avail_out);
    memcpy(pStream->next_out, pState->m_dict + pState->m_dict_ofs, n);
    pStream->next_out += n; pStream->avail_out -= n; pStream->total_out += n;
    pState->m_dict_avail -= n; pState->m_dict_ofs = (pState->m_dict_ofs + n) & (TINFL_LZ_DICT_SIZE - 1);
    തിരികെ ((pState->m_last_status == TINFL_STATUS_DONE) && (!pState->m_dict_avail)) ? MZ_STREAM_END : MZ_OK;
  }

  വേണ്ടി ( ; ; )
  {
    in_bytes = pStream->avail_in;
    out_bytes = TINFL_LZ_DICT_SIZE - pState->m_dict_ofs;

    status = tinfl_decompress(&pState->m_decomp, pStream->next_in, &in_bytes, pState->m_dict, pState->m_dict + pState->m_dict_ofs, &out_bytes, decomp_flags);
    pState->m_last_status = status;

    pStream->next_in += (mz_uint)in_bytes; pStream->avail_in -= (mz_uint)in_bytes;
    pStream->total_in += (mz_uint)in_bytes; pStream->adler = tinfl_get_adler32(&pState->m_decomp);

    pState->m_dict_avail = (mz_uint)out_bytes;

    n = MZ_MIN(pState->m_dict_avail, pStream->avail_out);
    memcpy(pStream->next_out, pState->m_dict + pState->m_dict_ofs, n);
    pStream->next_out += n; pStream->avail_out -= n; pStream->total_out += n;
    pState->m_dict_avail -= n; pState->m_dict_ofs = (pState->m_dict_ofs + n) & (TINFL_LZ_DICT_SIZE - 1);

    എങ്കിൽ (status < 0)
       തിരികെ MZ_DATA_ERROR; // Stream is corrupted (there could be some uncompressed data left in the output dictionary - oh well).
    അല്ലെങ്കിൽ എങ്കിൽ ((status == TINFL_STATUS_NEEDS_MORE_നിവേശം) && (!orig_avail_in))
      തിരികെ MZ_BUF_ERROR; // Signal caller that we can't make forward progress without supplying more input or by setting flush to MZ_FINISH.
    അല്ലെങ്കിൽ എങ്കിൽ (flush == MZ_FINISH)
    {
       // The output buffer MUST be large to hold the remaining uncompressed data when flush==MZ_FINISH.
       എങ്കിൽ (status == TINFL_STATUS_DONE)
          തിരികെ pState->m_dict_avail ? MZ_BUF_ERROR : MZ_STREAM_END;
       // status here must be TINFL_STATUS_HAS_MORE_OUTPUT, which means there's at least 1 more byte on the way. If there's no more room left in the output buffer then something is wrong.
       അല്ലെങ്കിൽ എങ്കിൽ (!pStream->avail_out)
          തിരികെ MZ_BUF_ERROR;
    }
    അല്ലെങ്കിൽ എങ്കിൽ ((status == TINFL_STATUS_DONE) || (!pStream->avail_in) || (!pStream->avail_out) || (pState->m_dict_avail))
      നിർത്തുക;
  }

  തിരികെ ((status == TINFL_STATUS_DONE) && (!pState->m_dict_avail)) ? MZ_STREAM_END : MZ_OK;
}

പൂർണ്ണസംഖ്യ mz_inflateEnd(mz_streamp pStream)
{
  എങ്കിൽ (!pStream)
    തിരികെ MZ_STREAM_ERROR;
  എങ്കിൽ (pStream->state)
  {
    pStream->zfree(pStream->opaque, pStream->state);
    pStream->state = ശൂന്യ;
  }
  തിരികെ MZ_OK;
}

പൂർണ്ണസംഖ്യ mz_uncompress(unsigned അക്ഷരം *pDest, mz_ulong *pDest_len, സ്ഥിരം unsigned അക്ഷരം *pSource, mz_ulong source_len)
{
  mz_stream stream;
  പൂർണ്ണസംഖ്യ status;
  memset(&stream, 0, വലുപ്പം(stream));

  // In case mz_ulong is 64-bits (argh I hate longs).
  എങ്കിൽ ((source_len | *pDest_len) > 0xFFFFFFFFU) തിരികെ MZ_PARAM_ERROR;

  stream.next_in = pSource;
  stream.avail_in = (mz_uint32)source_len;
  stream.next_out = pDest;
  stream.avail_out = (mz_uint32)*pDest_len;

  status = mz_inflateInit(&stream);
  എങ്കിൽ (status != MZ_OK)
    തിരികെ status;

  status = mz_inflate(&stream, MZ_FINISH);
  എങ്കിൽ (status != MZ_STREAM_END)
  {
    mz_inflateEnd(&stream);
    തിരികെ ((status == MZ_BUF_ERROR) && (!stream.avail_in)) ? MZ_DATA_ERROR : status;
  }
  *pDest_len = stream.total_out;

  തിരികെ mz_inflateEnd(&stream);
}

#endif /*#ifndef MINIZ_NO_INFLATE_APIS*/

സ്ഥിരം അക്ഷരം *mz_error(പൂർണ്ണസംഖ്യ err)
{
  സ്ഥിതം ഘടന { പൂർണ്ണസംഖ്യ m_err; സ്ഥിരം അക്ഷരം *m_pDesc; } s_error_descs[] =
  {
    { MZ_OK, "" }, { MZ_STREAM_END, "stream end" }, { MZ_NEED_DICT, "need dictionary" }, { MZ_ERRNO, "file error" }, { MZ_STREAM_ERROR, "stream error" },
    { MZ_DATA_ERROR, "data error" }, { MZ_MEM_ERROR, "out of memory" }, { MZ_BUF_ERROR, "buf error" }, { MZ_VERSION_ERROR, "version error" }, { MZ_PARAM_ERROR, "parameter error" }
  };
  mz_uint i; വേണ്ടി (i = 0; i < വലുപ്പം(s_error_descs) / വലുപ്പം(s_error_descs[0]); ++i) എങ്കിൽ (s_error_descs[i].m_err == err) തിരികെ s_error_descs[i].m_pDesc;
  തിരികെ ശൂന്യ;
}

#endif //MINIZ_NO_ZLIB_APIS

// ------------------- Low-level Decompression (completely independent from all compression API's)
#ifndef MINIZ_NO_INFLATE_APIS

#define TINFL_MEMCPY(d, s, l) memcpy(d, s, l)
#define TINFL_MEMSET(p, c, l) memset(p, c, l)

#define TINFL_CR_BEGIN തിരഞ്ഞെടുപ്പ്(r->m_state) { അവസ്ഥ 0:
#define TINFL_CR_RETURN(state_index, result) ചെയ്യുക { status = result; r->m_state = state_index; പോകുക common_exit; അവസ്ഥ state_index:; } MZ_MACRO_END
#define TINFL_CR_RETURN_FOREVER(state_index, result) ചെയ്യുക { വേണ്ടി ( ; ; ) { TINFL_CR_RETURN(state_index, result); } } MZ_MACRO_END
#define TINFL_CR_FINISH }

// TODO: If the caller has indicated that there's no more input, and we attempt to read beyond the input buf, then something is wrong with the input because the inflator never
// reads ahead more than it needs to. Currently TINFL_GET_BYTE() pads the end of the stream with 0's in this scenario.
#define TINFL_GET_BYTE(state_index, c) ചെയ്യുക { \
  എങ്കിൽ (pIn_buf_cur >= pIn_buf_end) { \
    വേണ്ടി ( ; ; ) { \
      എങ്കിൽ (decomp_flags & TINFL_FLAG_HAS_MORE_നിവേശം) { \
        TINFL_CR_RETURN(state_index, TINFL_STATUS_NEEDS_MORE_നിവേശം); \
        എങ്കിൽ (pIn_buf_cur < pIn_buf_end) { \
          c = *pIn_buf_cur++; \
          നിർത്തുക; \
        } \
      } അല്ലെങ്കിൽ { \
        c = 0; \
        നിർത്തുക; \
      } \
    } \
  } അല്ലെങ്കിൽ c = *pIn_buf_cur++; } MZ_MACRO_END

#define TINFL_NEED_BITS(state_index, n) ചെയ്യുക { mz_uint c; TINFL_GET_BYTE(state_index, c); bit_buf |= (((tinfl_bit_buf_t)c) << അക്കം_bits); അക്കം_bits += 8; } ആകുമ്പോൾ (അക്കം_bits < (mz_uint)(n))
#define TINFL_SKIP_BITS(state_index, n) ചെയ്യുക { എങ്കിൽ (അക്കം_bits < (mz_uint)(n)) { TINFL_NEED_BITS(state_index, n); } bit_buf >>= (n); അക്കം_bits -= (n); } MZ_MACRO_END
#define TINFL_GET_BITS(state_index, b, n) ചെയ്യുക { എങ്കിൽ (അക്കം_bits < (mz_uint)(n)) { TINFL_NEED_BITS(state_index, n); } b = bit_buf & ((1 << (n)) - 1); bit_buf >>= (n); അക്കം_bits -= (n); } MZ_MACRO_END

// TINFL_HUFF_BITBUF_FILL() is only used rarely, when the number of bytes remaining in the input buffer falls below 2.
// It reads just enough bytes from the input stream that are needed to decode the next Huffman code (and absolutely no more). It works by trying to fully decode a
// Huffman code by using whatever bits are currently present in the bit buffer. If this fails, it reads another byte, and tries again until it succeeds or until the
// bit buffer contains >=15 bits (deflate's max. Huffman code size).
#define TINFL_HUFF_BITBUF_FILL(state_index, pHuff) \
  ചെയ്യുക { \
    temp = (pHuff)->m_look_up[bit_buf & (TINFL_FAST_LOOKUP_SIZE - 1)]; \
    എങ്കിൽ (temp >= 0) { \
      code_len = temp >> 9; \
      എങ്കിൽ ((code_len) && (അക്കം_bits >= code_len)) \
          നിർത്തുക; \
    } അല്ലെങ്കിൽ എങ്കിൽ (അക്കം_bits > TINFL_FAST_LOOKUP_BITS) { \
       code_len = TINFL_FAST_LOOKUP_BITS; \
       ചെയ്യുക { \
          temp = (pHuff)->m_വൃക്ഷം[~temp + ((bit_buf >> code_len++) & 1)]; \
       } ആകുമ്പോൾ ((temp < 0) && (അക്കം_bits >= (code_len + 1))); \
       എങ്കിൽ (temp >= 0) നിർത്തുക; \
    } \
    TINFL_GET_BYTE(state_index, c); \
    bit_buf |= (((tinfl_bit_buf_t)c) << അക്കം_bits); \
    അക്കം_bits += 8; \
  } ആകുമ്പോൾ (അക്കം_bits < 15);

// TINFL_HUFF_DECODE() decodes the next Huffman coded symbol. It's more complex than you would initially expect because the zlib API expects the decompressor to never read
// beyond the final byte of the deflate stream. (In other words, when this macro wants to read another byte from the input, it REALLY needs another byte in order to fully
// decode the next Huffman code.) Handling this properly is particularly important on raw deflate (non-zlib) streams, which aren't followed by a byte aligned adler-32.
// The slow path is only executed at the very end of the input buffer.
#define TINFL_HUFF_DECODE(state_index, sym, pHuff) ചെയ്യുക { \
  പൂർണ്ണസംഖ്യ temp; mz_uint code_len, c; \
  എങ്കിൽ (അക്കം_bits < 15) { \
    എങ്കിൽ ((pIn_buf_end - pIn_buf_cur) < 2) { \
       TINFL_HUFF_BITBUF_FILL(state_index, pHuff); \
    } അല്ലെങ്കിൽ { \
       bit_buf |= (((tinfl_bit_buf_t)pIn_buf_cur[0]) << അക്കം_bits) | (((tinfl_bit_buf_t)pIn_buf_cur[1]) << (അക്കം_bits + 8)); pIn_buf_cur += 2; അക്കം_bits += 16; \
    } \
  } \
  എങ്കിൽ ((temp = (pHuff)->m_look_up[bit_buf & (TINFL_FAST_LOOKUP_SIZE - 1)]) >= 0) \
    code_len = temp >> 9, temp &= 511; \
  അല്ലെങ്കിൽ { \
    code_len = TINFL_FAST_LOOKUP_BITS; ചെയ്യുക { temp = (pHuff)->m_വൃക്ഷം[~temp + ((bit_buf >> code_len++) & 1)]; } ആകുമ്പോൾ (temp < 0); \
  } sym = temp; bit_buf >>= code_len; അക്കം_bits -= code_len; } MZ_MACRO_END

tinfl_status tinfl_decompress(tinfl_decompressor *r, സ്ഥിരം mz_uint8 *pIn_buf_next, size_t *pIn_buf_size, mz_uint8 *pOut_buf_start, mz_uint8 *pOut_buf_next, size_t *pOut_buf_size, സ്ഥിരം mz_uint32 decomp_flags)
{
  സ്ഥിതം സ്ഥിരം പൂർണ്ണസംഖ്യ s_length_base[31] = { 3,4,5,6,7,8,9,10,11,13, 15,17,19,23,27,31,35,43,51,59, 67,83,99,115,131,163,195,227,258,0,0 };
  സ്ഥിതം സ്ഥിരം പൂർണ്ണസംഖ്യ s_length_extra[31]= { 0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,0,0,0 };
  സ്ഥിതം സ്ഥിരം പൂർണ്ണസംഖ്യ s_dist_base[32] = { 1,2,3,4,5,7,9,13,17,25,33,49,65,97,129,193, 257,385,513,769,1025,1537,2049,3073,4097,6145,8193,12289,16385,24577,0,0};
  സ്ഥിതം സ്ഥിരം പൂർണ്ണസംഖ്യ s_dist_extra[32] = { 0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13};
  സ്ഥിതം സ്ഥിരം mz_uint8 s_length_dezigzag[19] = { 16,17,18,0,8,7,9,6,10,5,11,4,12,3,13,2,14,1,15 };
  സ്ഥിതം സ്ഥിരം പൂർണ്ണസംഖ്യ s_min_table_sizes[3] = { 257, 1, 4 };

  tinfl_status status = TINFL_STATUS_FAILED; mz_uint32 അക്കം_bits, dist, counter, അക്കം_extra; tinfl_bit_buf_t bit_buf;
  സ്ഥിരം mz_uint8 *pIn_buf_cur = pIn_buf_next, *സ്ഥിരം pIn_buf_end = pIn_buf_next + *pIn_buf_size;
  mz_uint8 *pOut_buf_cur = pOut_buf_next, *സ്ഥിരം pOut_buf_end = pOut_buf_next + *pOut_buf_size;
  size_t out_buf_size_mask = (decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF) ? (size_t)-1 : ((pOut_buf_next - pOut_buf_start) + *pOut_buf_size) - 1, dist_from_out_buf_start;

  // Ensure the output buffer's size is a power of 2, unless the output buffer is large enough to hold the entire output file (in which case it doesn't matter).
  എങ്കിൽ (((out_buf_size_mask + 1) & out_buf_size_mask) || (pOut_buf_next < pOut_buf_start)) { *pIn_buf_size = *pOut_buf_size = 0; തിരികെ TINFL_STATUS_BAD_PARAM; }

  അക്കം_bits = r->m_അക്കം_bits; bit_buf = r->m_bit_buf; dist = r->m_dist; counter = r->m_counter; അക്കം_extra = r->m_അക്കം_extra; dist_from_out_buf_start = r->m_dist_from_out_buf_start;
  TINFL_CR_BEGIN

  bit_buf = അക്കം_bits = dist = counter = അക്കം_extra = r->m_zhdr0 = r->m_zhdr1 = 0; r->m_z_adler32 = r->m_check_adler32 = 1;
  എങ്കിൽ (decomp_flags & TINFL_FLAG_PARSE_ZLIB_HEADER)
  {
    TINFL_GET_BYTE(1, r->m_zhdr0); TINFL_GET_BYTE(2, r->m_zhdr1);
    counter = (((r->m_zhdr0 * 256 + r->m_zhdr1) % 31 != 0) || (r->m_zhdr1 & 32) || ((r->m_zhdr0 & 15) != 8));
    എങ്കിൽ (!(decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF)) counter |= (((1U << (8U + (r->m_zhdr0 >> 4))) > 32768U) || ((out_buf_size_mask + 1) < (size_t)(1U << (8U + (r->m_zhdr0 >> 4)))));
    എങ്കിൽ (counter) { TINFL_CR_RETURN_FOREVER(36, TINFL_STATUS_FAILED); }
  }

  ചെയ്യുക
  {
    TINFL_GET_BITS(3, r->m_final, 3); r->m_type = r->m_final >> 1;
    എങ്കിൽ (r->m_type == 0)
    {
      TINFL_SKIP_BITS(5, അക്കം_bits & 7);
      വേണ്ടി (counter = 0; counter < 4; ++counter) { എങ്കിൽ (അക്കം_bits) TINFL_GET_BITS(6, r->m_raw_header[counter], 8); അല്ലെങ്കിൽ TINFL_GET_BYTE(7, r->m_raw_header[counter]); }
      എങ്കിൽ ((counter = (r->m_raw_header[0] | (r->m_raw_header[1] << 8))) != (mz_uint)(0xFFFF ^ (r->m_raw_header[2] | (r->m_raw_header[3] << 8)))) { TINFL_CR_RETURN_FOREVER(39, TINFL_STATUS_FAILED); }
      ആകുമ്പോൾ ((counter) && (അക്കം_bits))
      {
        TINFL_GET_BITS(51, dist, 8);
        ആകുമ്പോൾ (pOut_buf_cur >= pOut_buf_end) { TINFL_CR_RETURN(52, TINFL_STATUS_HAS_MORE_OUTPUT); }
        *pOut_buf_cur++ = (mz_uint8)dist;
        counter--;
      }
      ആകുമ്പോൾ (counter)
      {
        size_t n; ആകുമ്പോൾ (pOut_buf_cur >= pOut_buf_end) { TINFL_CR_RETURN(9, TINFL_STATUS_HAS_MORE_OUTPUT); }
        ആകുമ്പോൾ (pIn_buf_cur >= pIn_buf_end)
        {
          എങ്കിൽ (decomp_flags & TINFL_FLAG_HAS_MORE_നിവേശം)
          {
            TINFL_CR_RETURN(38, TINFL_STATUS_NEEDS_MORE_നിവേശം);
          }
          അല്ലെങ്കിൽ
          {
            TINFL_CR_RETURN_FOREVER(40, TINFL_STATUS_FAILED);
          }
        }
        n = MZ_MIN(MZ_MIN((size_t)(pOut_buf_end - pOut_buf_cur), (size_t)(pIn_buf_end - pIn_buf_cur)), counter);
        TINFL_MEMCPY(pOut_buf_cur, pIn_buf_cur, n); pIn_buf_cur += n; pOut_buf_cur += n; counter -= (mz_uint)n;
      }
    }
    അല്ലെങ്കിൽ എങ്കിൽ (r->m_type == 3)
    {
      TINFL_CR_RETURN_FOREVER(10, TINFL_STATUS_FAILED);
    }
    അല്ലെങ്കിൽ
    {
      എങ്കിൽ (r->m_type == 1)
      {
        mz_uint8 *p = r->m_tables[0].m_code_size; mz_uint i;
        r->m_table_sizes[0] = 288; r->m_table_sizes[1] = 32; TINFL_MEMSET(r->m_tables[1].m_code_size, 5, 32);
        വേണ്ടി ( i = 0; i <= 143; ++i) *p++ = 8;
        വേണ്ടി ( ; i <= 255; ++i) *p++ = 9;
        വേണ്ടി ( ; i <= 279; ++i) *p++ = 7;
        വേണ്ടി ( ; i <= 287; ++i) *p++ = 8;
      }
      അല്ലെങ്കിൽ
      {
        വേണ്ടി (counter = 0; counter < 3; counter++) { TINFL_GET_BITS(11, r->m_table_sizes[counter], "\05\05\04"[counter]); r->m_table_sizes[counter] += s_min_table_sizes[counter]; }
        MZ_CLEAR_ARR(r->m_tables[2].m_code_size); വേണ്ടി (counter = 0; counter < r->m_table_sizes[2]; counter++) { mz_uint s; TINFL_GET_BITS(14, s, 3); r->m_tables[2].m_code_size[s_length_dezigzag[counter]] = (mz_uint8)s; }
        r->m_table_sizes[2] = 19;
      }
      വേണ്ടി ( ; (പൂർണ്ണസംഖ്യ)r->m_type >= 0; r->m_type--)
      {
        പൂർണ്ണസംഖ്യ വൃക്ഷം_next, വൃക്ഷം_cur; tinfl_huff_table *pTable;
        mz_uint i, j, used_syms, total, sym_index, next_code[17], total_syms[16]; pTable = &r->m_tables[r->m_type]; MZ_CLEAR_ARR(total_syms); MZ_CLEAR_ARR(pTable->m_look_up); MZ_CLEAR_ARR(pTable->m_വൃക്ഷം);
        വേണ്ടി (i = 0; i < r->m_table_sizes[r->m_type]; ++i) total_syms[pTable->m_code_size[i]]++;
        used_syms = 0, total = 0; next_code[0] = next_code[1] = 0;
        വേണ്ടി (i = 1; i <= 15; ++i) { used_syms += total_syms[i]; next_code[i + 1] = (total = ((total + total_syms[i]) << 1)); }
        എങ്കിൽ ((65536 != total) && (used_syms > 1))
        {
          TINFL_CR_RETURN_FOREVER(35, TINFL_STATUS_FAILED);
        }
        വേണ്ടി (വൃക്ഷം_next = -1, sym_index = 0; sym_index < r->m_table_sizes[r->m_type]; ++sym_index)
        {
          mz_uint rev_code = 0, l, cur_code, code_size = pTable->m_code_size[sym_index]; എങ്കിൽ (!code_size) തുടരുക;
          cur_code = next_code[code_size]++; വേണ്ടി (l = code_size; l > 0; l--, cur_code >>= 1) rev_code = (rev_code << 1) | (cur_code & 1);
          എങ്കിൽ (code_size <= TINFL_FAST_LOOKUP_BITS) { mz_int16 k = (mz_int16)((code_size << 9) | sym_index); ആകുമ്പോൾ (rev_code < TINFL_FAST_LOOKUP_SIZE) { pTable->m_look_up[rev_code] = k; rev_code += (1 << code_size); } തുടരുക; }
          എങ്കിൽ (0 == (വൃക്ഷം_cur = pTable->m_look_up[rev_code & (TINFL_FAST_LOOKUP_SIZE - 1)])) { pTable->m_look_up[rev_code & (TINFL_FAST_LOOKUP_SIZE - 1)] = (mz_int16)വൃക്ഷം_next; വൃക്ഷം_cur = വൃക്ഷം_next; വൃക്ഷം_next -= 2; }
          rev_code >>= (TINFL_FAST_LOOKUP_BITS - 1);
          വേണ്ടി (j = code_size; j > (TINFL_FAST_LOOKUP_BITS + 1); j--)
          {
            വൃക്ഷം_cur -= ((rev_code >>= 1) & 1);
            എങ്കിൽ (!pTable->m_വൃക്ഷം[-വൃക്ഷം_cur - 1]) { pTable->m_വൃക്ഷം[-വൃക്ഷം_cur - 1] = (mz_int16)വൃക്ഷം_next; വൃക്ഷം_cur = വൃക്ഷം_next; വൃക്ഷം_next -= 2; } അല്ലെങ്കിൽ വൃക്ഷം_cur = pTable->m_വൃക്ഷം[-വൃക്ഷം_cur - 1];
          }
          വൃക്ഷം_cur -= ((rev_code >>= 1) & 1); pTable->m_വൃക്ഷം[-വൃക്ഷം_cur - 1] = (mz_int16)sym_index;
        }
        എങ്കിൽ (r->m_type == 2)
        {
          വേണ്ടി (counter = 0; counter < (r->m_table_sizes[0] + r->m_table_sizes[1]); )
          {
            mz_uint s; TINFL_HUFF_DECODE(16, dist, &r->m_tables[2]); എങ്കിൽ (dist < 16) { r->m_len_codes[counter++] = (mz_uint8)dist; തുടരുക; }
            എങ്കിൽ ((dist == 16) && (!counter))
            {
              TINFL_CR_RETURN_FOREVER(17, TINFL_STATUS_FAILED);
            }
            അക്കം_extra = "\02\03\07"[dist - 16]; TINFL_GET_BITS(18, s, അക്കം_extra); s += "\03\03\013"[dist - 16];
            TINFL_MEMSET(r->m_len_codes + counter, (dist == 16) ? r->m_len_codes[counter - 1] : 0, s); counter += s;
          }
          എങ്കിൽ ((r->m_table_sizes[0] + r->m_table_sizes[1]) != counter)
          {
            TINFL_CR_RETURN_FOREVER(21, TINFL_STATUS_FAILED);
          }
          TINFL_MEMCPY(r->m_tables[0].m_code_size, r->m_len_codes, r->m_table_sizes[0]); TINFL_MEMCPY(r->m_tables[1].m_code_size, r->m_len_codes + r->m_table_sizes[0], r->m_table_sizes[1]);
        }
      }
      വേണ്ടി ( ; ; )
      {
        mz_uint8 *pSrc;
        വേണ്ടി ( ; ; )
        {
          എങ്കിൽ (((pIn_buf_end - pIn_buf_cur) < 4) || ((pOut_buf_end - pOut_buf_cur) < 2))
          {
            TINFL_HUFF_DECODE(23, counter, &r->m_tables[0]);
            എങ്കിൽ (counter >= 256)
              നിർത്തുക;
            ആകുമ്പോൾ (pOut_buf_cur >= pOut_buf_end) { TINFL_CR_RETURN(24, TINFL_STATUS_HAS_MORE_OUTPUT); }
            *pOut_buf_cur++ = (mz_uint8)counter;
          }
          അല്ലെങ്കിൽ
          {
            പൂർണ്ണസംഖ്യ sym2; mz_uint code_len;
#എങ്കിൽ TINFL_USE_64BIT_BITBUF
            എങ്കിൽ (അക്കം_bits < 30) { bit_buf |= (((tinfl_bit_buf_t)MZ_READ_LE32(pIn_buf_cur)) << അക്കം_bits); pIn_buf_cur += 4; അക്കം_bits += 32; }
#അല്ലെങ്കിൽ
            എങ്കിൽ (അക്കം_bits < 15) { bit_buf |= (((tinfl_bit_buf_t)MZ_READ_LE16(pIn_buf_cur)) << അക്കം_bits); pIn_buf_cur += 2; അക്കം_bits += 16; }
#endif
            എങ്കിൽ ((sym2 = r->m_tables[0].m_look_up[bit_buf & (TINFL_FAST_LOOKUP_SIZE - 1)]) >= 0)
              code_len = sym2 >> 9;
            അല്ലെങ്കിൽ
            {
              code_len = TINFL_FAST_LOOKUP_BITS; ചെയ്യുക { sym2 = r->m_tables[0].m_വൃക്ഷം[~sym2 + ((bit_buf >> code_len++) & 1)]; } ആകുമ്പോൾ (sym2 < 0);
            }
            counter = sym2; bit_buf >>= code_len; അക്കം_bits -= code_len;
            എങ്കിൽ (counter & 256)
              നിർത്തുക;

#എങ്കിൽ !TINFL_USE_64BIT_BITBUF
            എങ്കിൽ (അക്കം_bits < 15) { bit_buf |= (((tinfl_bit_buf_t)MZ_READ_LE16(pIn_buf_cur)) << അക്കം_bits); pIn_buf_cur += 2; അക്കം_bits += 16; }
#endif
            എങ്കിൽ ((sym2 = r->m_tables[0].m_look_up[bit_buf & (TINFL_FAST_LOOKUP_SIZE - 1)]) >= 0)
              code_len = sym2 >> 9;
            അല്ലെങ്കിൽ
            {
              code_len = TINFL_FAST_LOOKUP_BITS; ചെയ്യുക { sym2 = r->m_tables[0].m_വൃക്ഷം[~sym2 + ((bit_buf >> code_len++) & 1)]; } ആകുമ്പോൾ (sym2 < 0);
            }
            bit_buf >>= code_len; അക്കം_bits -= code_len;

            pOut_buf_cur[0] = (mz_uint8)counter;
            എങ്കിൽ (sym2 & 256)
            {
              pOut_buf_cur++;
              counter = sym2;
              നിർത്തുക;
            }
            pOut_buf_cur[1] = (mz_uint8)sym2;
            pOut_buf_cur += 2;
          }
        }
        എങ്കിൽ ((counter &= 511) == 256) നിർത്തുക;

        അക്കം_extra = s_length_extra[counter - 257]; counter = s_length_base[counter - 257];
        എങ്കിൽ (അക്കം_extra) { mz_uint extra_bits; TINFL_GET_BITS(25, extra_bits, അക്കം_extra); counter += extra_bits; }

        TINFL_HUFF_DECODE(26, dist, &r->m_tables[1]);
        അക്കം_extra = s_dist_extra[dist]; dist = s_dist_base[dist];
        എങ്കിൽ (അക്കം_extra) { mz_uint extra_bits; TINFL_GET_BITS(27, extra_bits, അക്കം_extra); dist += extra_bits; }

        dist_from_out_buf_start = pOut_buf_cur - pOut_buf_start;
        എങ്കിൽ ((dist > dist_from_out_buf_start) && (decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF))
        {
          TINFL_CR_RETURN_FOREVER(37, TINFL_STATUS_FAILED);
        }

        pSrc = pOut_buf_start + ((dist_from_out_buf_start - dist) & out_buf_size_mask);

        എങ്കിൽ ((MZ_MAX(pOut_buf_cur, pSrc) + counter) > pOut_buf_end)
        {
          ആകുമ്പോൾ (counter--)
          {
            ആകുമ്പോൾ (pOut_buf_cur >= pOut_buf_end) { TINFL_CR_RETURN(53, TINFL_STATUS_HAS_MORE_OUTPUT); }
            *pOut_buf_cur++ = pOut_buf_start[(dist_from_out_buf_start++ - dist) & out_buf_size_mask];
          }
          തുടരുക;
        }
#എങ്കിൽ MINIZ_USE_UNALIGNED_LOADS_AND_STORES
        അല്ലെങ്കിൽ എങ്കിൽ ((counter >= 9) && (counter <= dist))
        {
          സ്ഥിരം mz_uint8 *pSrc_end = pSrc + (counter & ~7);
          ചെയ്യുക
          {
            ((mz_uint32 *)pOut_buf_cur)[0] = ((സ്ഥിരം mz_uint32 *)pSrc)[0];
            ((mz_uint32 *)pOut_buf_cur)[1] = ((സ്ഥിരം mz_uint32 *)pSrc)[1];
            pOut_buf_cur += 8;
          } ആകുമ്പോൾ ((pSrc += 8) < pSrc_end);
          എങ്കിൽ ((counter &= 7) < 3)
          {
            എങ്കിൽ (counter)
            {
              pOut_buf_cur[0] = pSrc[0];
              എങ്കിൽ (counter > 1)
                pOut_buf_cur[1] = pSrc[1];
              pOut_buf_cur += counter;
            }
            തുടരുക;
          }
        }
#endif
        ചെയ്യുക
        {
          pOut_buf_cur[0] = pSrc[0];
          pOut_buf_cur[1] = pSrc[1];
          pOut_buf_cur[2] = pSrc[2];
          pOut_buf_cur += 3; pSrc += 3;
        } ആകുമ്പോൾ ((പൂർണ്ണസംഖ്യ)(counter -= 3) > 2);
        എങ്കിൽ ((പൂർണ്ണസംഖ്യ)counter > 0)
        {
          pOut_buf_cur[0] = pSrc[0];
          എങ്കിൽ ((പൂർണ്ണസംഖ്യ)counter > 1)
            pOut_buf_cur[1] = pSrc[1];
          pOut_buf_cur += counter;
        }
      }
    }
  } ആകുമ്പോൾ (!(r->m_final & 1));
  എങ്കിൽ (decomp_flags & TINFL_FLAG_PARSE_ZLIB_HEADER)
  {
    TINFL_SKIP_BITS(32, അക്കം_bits & 7); വേണ്ടി (counter = 0; counter < 4; ++counter) { mz_uint s; എങ്കിൽ (അക്കം_bits) TINFL_GET_BITS(41, s, 8); അല്ലെങ്കിൽ TINFL_GET_BYTE(42, s); r->m_z_adler32 = (r->m_z_adler32 << 8) | s; }
  }
  TINFL_CR_RETURN_FOREVER(34, TINFL_STATUS_DONE);
  TINFL_CR_FINISH

common_exit:
  r->m_അക്കം_bits = അക്കം_bits; r->m_bit_buf = bit_buf; r->m_dist = dist; r->m_counter = counter; r->m_അക്കം_extra = അക്കം_extra; r->m_dist_from_out_buf_start = dist_from_out_buf_start;
  *pIn_buf_size = pIn_buf_cur - pIn_buf_next; *pOut_buf_size = pOut_buf_cur - pOut_buf_next;
  എങ്കിൽ ((decomp_flags & (TINFL_FLAG_PARSE_ZLIB_HEADER | TINFL_FLAG_COMPUTE_ADLER32)) && (status >= 0))
  {
    സ്ഥിരം mz_uint8 *ptr = pOut_buf_next; size_t buf_len = *pOut_buf_size;
    mz_uint32 i, s1 = r->m_check_adler32 & 0xffff, s2 = r->m_check_adler32 >> 16; size_t block_len = buf_len % 5552;
    ആകുമ്പോൾ (buf_len)
    {
      വേണ്ടി (i = 0; i + 7 < block_len; i += 8, ptr += 8)
      {
        s1 += ptr[0], s2 += s1; s1 += ptr[1], s2 += s1; s1 += ptr[2], s2 += s1; s1 += ptr[3], s2 += s1;
        s1 += ptr[4], s2 += s1; s1 += ptr[5], s2 += s1; s1 += ptr[6], s2 += s1; s1 += ptr[7], s2 += s1;
      }
      വേണ്ടി ( ; i < block_len; ++i) s1 += *ptr++, s2 += s1;
      s1 %= 65521U, s2 %= 65521U; buf_len -= block_len; block_len = 5552;
    }
    r->m_check_adler32 = (s2 << 16) + s1; എങ്കിൽ ((status == TINFL_STATUS_DONE) && (decomp_flags & TINFL_FLAG_PARSE_ZLIB_HEADER) && (r->m_check_adler32 != r->m_z_adler32)) status = TINFL_STATUS_ADLER32_MISMATCH;
  }
  തിരികെ status;
}

// Higher level helper functions.
ശൂന്യം *tinfl_decompress_mem_to_heap(സ്ഥിരം ശൂന്യം *pSrc_buf, size_t src_buf_len, size_t *pOut_len, പൂർണ്ണസംഖ്യ flags)
{
  tinfl_decompressor decomp; ശൂന്യം *pBuf = ശൂന്യ, *pNew_buf; size_t src_buf_ofs = 0, out_buf_capacity = 0;
  *pOut_len = 0;
  tinfl_init(&decomp);
  വേണ്ടി ( ; ; )
  {
    size_t src_buf_size = src_buf_len - src_buf_ofs, dst_buf_size = out_buf_capacity - *pOut_len, new_out_buf_capacity;
    tinfl_status status = tinfl_decompress(&decomp, (സ്ഥിരം mz_uint8*)pSrc_buf + src_buf_ofs, &src_buf_size, (mz_uint8*)pBuf, pBuf ? (mz_uint8*)pBuf + *pOut_len : ശൂന്യ, &dst_buf_size,
      (flags & ~TINFL_FLAG_HAS_MORE_നിവേശം) | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF);
    എങ്കിൽ ((status < 0) || (status == TINFL_STATUS_NEEDS_MORE_നിവേശം))
    {
      MZ_FREE(pBuf); *pOut_len = 0; തിരികെ ശൂന്യ;
    }
    src_buf_ofs += src_buf_size;
    *pOut_len += dst_buf_size;
    എങ്കിൽ (status == TINFL_STATUS_DONE) നിർത്തുക;
    new_out_buf_capacity = out_buf_capacity * 2; എങ്കിൽ (new_out_buf_capacity < 128) new_out_buf_capacity = 128;
    pNew_buf = MZ_REALLOC(pBuf, new_out_buf_capacity);
    എങ്കിൽ (!pNew_buf)
    {
      MZ_FREE(pBuf); *pOut_len = 0; തിരികെ ശൂന്യ;
    }
    pBuf = pNew_buf; out_buf_capacity = new_out_buf_capacity;
  }
  തിരികെ pBuf;
}

size_t tinfl_decompress_mem_to_mem(ശൂന്യം *pOut_buf, size_t out_buf_len, സ്ഥിരം ശൂന്യം *pSrc_buf, size_t src_buf_len, പൂർണ്ണസംഖ്യ flags)
{
  tinfl_decompressor decomp; tinfl_status status; tinfl_init(&decomp);
  status = tinfl_decompress(&decomp, (സ്ഥിരം mz_uint8*)pSrc_buf, &src_buf_len, (mz_uint8*)pOut_buf, (mz_uint8*)pOut_buf, &out_buf_len, (flags & ~TINFL_FLAG_HAS_MORE_നിവേശം) | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF);
  തിരികെ (status != TINFL_STATUS_DONE) ? TINFL_DECOMPRESS_MEM_TO_MEM_FAILED : out_buf_len;
}

പൂർണ്ണസംഖ്യ tinfl_decompress_mem_to_callback(സ്ഥിരം ശൂന്യം *pIn_buf, size_t *pIn_buf_size, tinfl_put_buf_func_ptr pPut_buf_func, ശൂന്യം *pPut_buf_user, പൂർണ്ണസംഖ്യ flags)
{
  പൂർണ്ണസംഖ്യ result = 0;
  tinfl_decompressor decomp;
  mz_uint8 *pDict = (mz_uint8*)MZ_MALLOC(TINFL_LZ_DICT_SIZE); size_t in_buf_ofs = 0, dict_ofs = 0;
  എങ്കിൽ (!pDict)
    തിരികെ TINFL_STATUS_FAILED;
  memset(pDict,0,TINFL_LZ_DICT_SIZE);
  tinfl_init(&decomp);
  വേണ്ടി ( ; ; )
  {
    size_t in_buf_size = *pIn_buf_size - in_buf_ofs, dst_buf_size = TINFL_LZ_DICT_SIZE - dict_ofs;
    tinfl_status status = tinfl_decompress(&decomp, (സ്ഥിരം mz_uint8*)pIn_buf + in_buf_ofs, &in_buf_size, pDict, pDict + dict_ofs, &dst_buf_size,
      (flags & ~(TINFL_FLAG_HAS_MORE_നിവേശം | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF)));
    in_buf_ofs += in_buf_size;
    എങ്കിൽ ((dst_buf_size) && (!(*pPut_buf_func)(pDict + dict_ofs, (പൂർണ്ണസംഖ്യ)dst_buf_size, pPut_buf_user)))
      നിർത്തുക;
    എങ്കിൽ (status != TINFL_STATUS_HAS_MORE_OUTPUT)
    {
      result = (status == TINFL_STATUS_DONE);
      നിർത്തുക;
    }
    dict_ofs = (dict_ofs + dst_buf_size) & (TINFL_LZ_DICT_SIZE - 1);
  }
  MZ_FREE(pDict);
  *pIn_buf_size = in_buf_ofs;
  തിരികെ result;
}
#endif /*#ifndef MINIZ_NO_INFLATE_APIS*/

// ------------------- Low-level Compression (independent from all decompression API's)
#ifndef MINIZ_NO_DEFLATE_APIS

// Purposely making these tables static for faster init and thread safety.
സ്ഥിതം സ്ഥിരം mz_uint16 s_tdefl_len_sym[256] = {
  257,258,259,260,261,262,263,264,265,265,266,266,267,267,268,268,269,269,269,269,270,270,270,270,271,271,271,271,272,272,272,272,
  273,273,273,273,273,273,273,273,274,274,274,274,274,274,274,274,275,275,275,275,275,275,275,275,276,276,276,276,276,276,276,276,
  277,277,277,277,277,277,277,277,277,277,277,277,277,277,277,277,278,278,278,278,278,278,278,278,278,278,278,278,278,278,278,278,
  279,279,279,279,279,279,279,279,279,279,279,279,279,279,279,279,280,280,280,280,280,280,280,280,280,280,280,280,280,280,280,280,
  281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,
  282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,
  283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,
  284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,285 };

സ്ഥിതം സ്ഥിരം mz_uint8 s_tdefl_len_extra[256] = {
  0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0 };

സ്ഥിതം സ്ഥിരം mz_uint8 s_tdefl_small_dist_sym[512] = {
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

സ്ഥിതം സ്ഥിരം mz_uint8 s_tdefl_small_dist_extra[512] = {
  0,0,0,0,1,1,1,1,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
  6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
  6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7 };

സ്ഥിതം സ്ഥിരം mz_uint8 s_tdefl_large_dist_sym[128] = {
  0,0,18,19,20,20,21,21,22,22,22,22,23,23,23,23,24,24,24,24,24,24,24,24,25,25,25,25,25,25,25,25,26,26,26,26,26,26,26,26,26,26,26,26,
  26,26,26,26,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,
  28,28,28,28,28,28,28,28,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29 };

സ്ഥിതം സ്ഥിരം mz_uint8 s_tdefl_large_dist_extra[128] = {
  0,0,8,8,9,9,9,9,10,10,10,10,10,10,10,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,
  12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
  13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13 };

// Radix sorts tdefl_sym_freq[] array by 16-bit key m_key. Returns ptr to sorted values.
തരനിർവചനം ഘടന { mz_uint16 m_താക്കോൽ, m_sym_index; } tdefl_sym_freq;
സ്ഥിതം tdefl_sym_freq* tdefl_radix_sort_syms(mz_uint അക്കം_syms, tdefl_sym_freq* pSyms0, tdefl_sym_freq* pSyms1)
{
  mz_uint32 total_passes = 2, pass_shift, pass, i, hist[256 * 2]; tdefl_sym_freq* pCur_syms = pSyms0, *pNew_syms = pSyms1; MZ_CLEAR_ARR(hist);
  വേണ്ടി (i = 0; i < അക്കം_syms; i++) { mz_uint freq = pSyms0[i].m_താക്കോൽ; hist[freq & 0xFF]++; hist[256 + ((freq >> 8) & 0xFF)]++; }
  ആകുമ്പോൾ ((total_passes > 1) && (അക്കം_syms == hist[(total_passes - 1) * 256])) total_passes--;
  വേണ്ടി (pass_shift = 0, pass = 0; pass < total_passes; pass++, pass_shift += 8)
  {
    സ്ഥിരം mz_uint32* pHist = &hist[pass << 8];
    mz_uint offsets[256], cur_ofs = 0;
    വേണ്ടി (i = 0; i < 256; i++) { offsets[i] = cur_ofs; cur_ofs += pHist[i]; }
    വേണ്ടി (i = 0; i < അക്കം_syms; i++) pNew_syms[offsets[(pCur_syms[i].m_താക്കോൽ >> pass_shift) & 0xFF]++] = pCur_syms[i];
    { tdefl_sym_freq* t = pCur_syms; pCur_syms = pNew_syms; pNew_syms = t; }
  }
  തിരികെ pCur_syms;
}

// tdefl_calculate_minimum_redundancy() originally written by: Alistair Moffat, alistair@cs.mu.oz.au, Jyrki Katajainen, jyrki@diku.dk, November 1996.
സ്ഥിതം ശൂന്യം tdefl_calculate_minimum_redundancy(tdefl_sym_freq *A, പൂർണ്ണസംഖ്യ n)
{
  പൂർണ്ണസംഖ്യ വേര്, leaf, next, avbl, used, dpth;
  എങ്കിൽ (n==0) തിരികെ; അല്ലെങ്കിൽ എങ്കിൽ (n==1) { A[0].m_താക്കോൽ = 1; തിരികെ; }
  A[0].m_താക്കോൽ += A[1].m_താക്കോൽ; വേര് = 0; leaf = 2;
  വേണ്ടി (next=1; next < n-1; next++)
  {
    എങ്കിൽ (leaf>=n || A[വേര്].m_താക്കോൽ<A[leaf].m_താക്കോൽ) { A[next].m_താക്കോൽ = A[വേര്].m_താക്കോൽ; A[വേര്++].m_താക്കോൽ = (mz_uint16)next; } അല്ലെങ്കിൽ A[next].m_താക്കോൽ = A[leaf++].m_താക്കോൽ;
    എങ്കിൽ (leaf>=n || (വേര്<next && A[വേര്].m_താക്കോൽ<A[leaf].m_താക്കോൽ)) { A[next].m_താക്കോൽ = (mz_uint16)(A[next].m_താക്കോൽ + A[വേര്].m_താക്കോൽ); A[വേര്++].m_താക്കോൽ = (mz_uint16)next; } അല്ലെങ്കിൽ A[next].m_താക്കോൽ = (mz_uint16)(A[next].m_താക്കോൽ + A[leaf++].m_താക്കോൽ);
  }
  A[n-2].m_താക്കോൽ = 0; വേണ്ടി (next=n-3; next>=0; next--) A[next].m_താക്കോൽ = A[A[next].m_താക്കോൽ].m_താക്കോൽ+1;
  avbl = 1; used = dpth = 0; വേര് = n-2; next = n-1;
  ആകുമ്പോൾ (avbl>0)
  {
    ആകുമ്പോൾ (വേര്>=0 && (പൂർണ്ണസംഖ്യ)A[വേര്].m_താക്കോൽ==dpth) { used++; വേര്--; }
    ആകുമ്പോൾ (avbl>used) { A[next--].m_താക്കോൽ = (mz_uint16)(dpth); avbl--; }
    avbl = 2*used; dpth++; used = 0;
  }
}

// Limits canonical Huffman code table's max code size.
എണ്ണൽ { TDEFL_MAX_SUPPORTED_HUFF_CODESIZE = 32 };
സ്ഥിതം ശൂന്യം tdefl_huffman_enforce_max_code_size(പൂർണ്ണസംഖ്യ *p_അക്കം_codes, പൂർണ്ണസംഖ്യ code_list_len, പൂർണ്ണസംഖ്യ max_code_size)
{
  പൂർണ്ണസംഖ്യ i; mz_uint32 total = 0; എങ്കിൽ (code_list_len <= 1) തിരികെ;
  വേണ്ടി (i = max_code_size + 1; i <= TDEFL_MAX_SUPPORTED_HUFF_CODESIZE; i++) p_അക്കം_codes[max_code_size] += p_അക്കം_codes[i];
  വേണ്ടി (i = max_code_size; i > 0; i--) total += (((mz_uint32)p_അക്കം_codes[i]) << (max_code_size - i));
  ആകുമ്പോൾ (total != (1UL << max_code_size))
  {
    p_അക്കം_codes[max_code_size]--;
    വേണ്ടി (i = max_code_size - 1; i > 0; i--) എങ്കിൽ (p_അക്കം_codes[i]) { p_അക്കം_codes[i]--; p_അക്കം_codes[i + 1] += 2; നിർത്തുക; }
    total--;
  }
}

സ്ഥിതം ശൂന്യം tdefl_optimize_huffman_table(tdefl_compressor *d, പൂർണ്ണസംഖ്യ table_അക്കം, പൂർണ്ണസംഖ്യ table_len, പൂർണ്ണസംഖ്യ code_size_limit, പൂർണ്ണസംഖ്യ static_table)
{
  പൂർണ്ണസംഖ്യ i, j, l, അക്കം_codes[1 + TDEFL_MAX_SUPPORTED_HUFF_CODESIZE]; mz_uint next_code[TDEFL_MAX_SUPPORTED_HUFF_CODESIZE + 1]; MZ_CLEAR_ARR(അക്കം_codes);
  എങ്കിൽ (static_table)
  {
    വേണ്ടി (i = 0; i < table_len; i++) അക്കം_codes[d->m_huff_code_sizes[table_അക്കം][i]]++;
  }
  അല്ലെങ്കിൽ
  {
    tdefl_sym_freq syms0[TDEFL_MAX_HUFF_SYMBOLS], syms1[TDEFL_MAX_HUFF_SYMBOLS], *pSyms;
    പൂർണ്ണസംഖ്യ അക്കം_used_syms = 0;
    സ്ഥിരം mz_uint16 *p_Sym_എണ്ണം = &d->m_huff_എണ്ണം[table_അക്കം][0];
    വേണ്ടി (i = 0; i < table_len; i++) എങ്കിൽ (p_Sym_എണ്ണം[i]) { syms0[അക്കം_used_syms].m_താക്കോൽ = (mz_uint16)p_Sym_എണ്ണം[i]; syms0[അക്കം_used_syms++].m_sym_index = (mz_uint16)i; }

    pSyms = tdefl_radix_sort_syms(അക്കം_used_syms, syms0, syms1); tdefl_calculate_minimum_redundancy(pSyms, അക്കം_used_syms);

    വേണ്ടി (i = 0; i < അക്കം_used_syms; i++) അക്കം_codes[pSyms[i].m_താക്കോൽ]++;

    tdefl_huffman_enforce_max_code_size(അക്കം_codes, അക്കം_used_syms, code_size_limit);

    MZ_CLEAR_ARR(d->m_huff_code_sizes[table_അക്കം]); MZ_CLEAR_ARR(d->m_huff_codes[table_അക്കം]);
    വേണ്ടി (i = 1, j = അക്കം_used_syms; i <= code_size_limit; i++)
      വേണ്ടി (l = അക്കം_codes[i]; l > 0; l--) d->m_huff_code_sizes[table_അക്കം][pSyms[--j].m_sym_index] = (mz_uint8)(i);
  }

  next_code[1] = 0; വേണ്ടി (j = 0, i = 2; i <= code_size_limit; i++) next_code[i] = j = ((j + അക്കം_codes[i - 1]) << 1);

  വേണ്ടി (i = 0; i < table_len; i++)
  {
    mz_uint rev_code = 0, code, code_size; എങ്കിൽ ((code_size = d->m_huff_code_sizes[table_അക്കം][i]) == 0) തുടരുക;
    code = next_code[code_size]++; വേണ്ടി (l = code_size; l > 0; l--, code >>= 1) rev_code = (rev_code << 1) | (code & 1);
    d->m_huff_codes[table_അക്കം][i] = (mz_uint16)rev_code;
  }
}

#define TDEFL_PUT_BITS(b, l) ചെയ്യുക { \
  mz_uint bits = b; mz_uint len = l; MZ_ASSERT(bits <= ((1U << len) - 1U)); \
  d->m_bit_buffer |= (bits << d->m_bits_in); d->m_bits_in += len; \
  ആകുമ്പോൾ (d->m_bits_in >= 8) { \
    എങ്കിൽ (d->m_pOutput_buf < d->m_pOutput_buf_end) \
      *d->m_pOutput_buf++ = (mz_uint8)(d->m_bit_buffer); \
    d->m_bit_buffer >>= 8; \
    d->m_bits_in -= 8; \
  } \
} MZ_MACRO_END

#define TDEFL_RLE_PREV_CODE_SIZE() ചെയ്യുക { \
  എങ്കിൽ (rle_repeat_എണ്ണം) { \
    എങ്കിൽ (rle_repeat_എണ്ണം < 3) { \
      d->m_huff_എണ്ണം[2][prev_code_size] = (mz_uint16)(d->m_huff_എണ്ണം[2][prev_code_size] + rle_repeat_എണ്ണം); \
      ആകുമ്പോൾ (rle_repeat_എണ്ണം--) packed_code_sizes[അക്കം_packed_code_sizes++] = prev_code_size; \
    } അല്ലെങ്കിൽ { \
      d->m_huff_എണ്ണം[2][16] = (mz_uint16)(d->m_huff_എണ്ണം[2][16] + 1); packed_code_sizes[അക്കം_packed_code_sizes++] = 16; packed_code_sizes[അക്കം_packed_code_sizes++] = (mz_uint8)(rle_repeat_എണ്ണം - 3); \
  } rle_repeat_എണ്ണം = 0; } \
} MZ_MACRO_END

#define TDEFL_RLE_ZERO_CODE_SIZE() ചെയ്യുക { \
  എങ്കിൽ (rle_z_എണ്ണം) { \
    എങ്കിൽ (rle_z_എണ്ണം < 3) { \
      d->m_huff_എണ്ണം[2][0] = (mz_uint16)(d->m_huff_എണ്ണം[2][0] + rle_z_എണ്ണം); ആകുമ്പോൾ (rle_z_എണ്ണം--) packed_code_sizes[അക്കം_packed_code_sizes++] = 0; \
    } അല്ലെങ്കിൽ എങ്കിൽ (rle_z_എണ്ണം <= 10) { \
      d->m_huff_എണ്ണം[2][17] = (mz_uint16)(d->m_huff_എണ്ണം[2][17] + 1); packed_code_sizes[അക്കം_packed_code_sizes++] = 17; packed_code_sizes[അക്കം_packed_code_sizes++] = (mz_uint8)(rle_z_എണ്ണം - 3); \
    } അല്ലെങ്കിൽ { \
      d->m_huff_എണ്ണം[2][18] = (mz_uint16)(d->m_huff_എണ്ണം[2][18] + 1); packed_code_sizes[അക്കം_packed_code_sizes++] = 18; packed_code_sizes[അക്കം_packed_code_sizes++] = (mz_uint8)(rle_z_എണ്ണം - 11); \
  } rle_z_എണ്ണം = 0; } \
} MZ_MACRO_END

സ്ഥിതം mz_uint8 s_tdefl_packed_code_size_syms_swizzle[] = { 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 };

സ്ഥിതം ശൂന്യം tdefl_start_dynamic_block(tdefl_compressor *d)
{
  പൂർണ്ണസംഖ്യ അക്കം_lit_codes, അക്കം_dist_codes, അക്കം_bit_lengths; mz_uint i, total_code_sizes_to_pack, അക്കം_packed_code_sizes, rle_z_എണ്ണം, rle_repeat_എണ്ണം, packed_code_sizes_index;
  mz_uint8 code_sizes_to_pack[TDEFL_MAX_HUFF_SYMBOLS_0 + TDEFL_MAX_HUFF_SYMBOLS_1], packed_code_sizes[TDEFL_MAX_HUFF_SYMBOLS_0 + TDEFL_MAX_HUFF_SYMBOLS_1], prev_code_size = 0xFF;

  d->m_huff_എണ്ണം[0][256] = 1;

  tdefl_optimize_huffman_table(d, 0, TDEFL_MAX_HUFF_SYMBOLS_0, 15, MZ_FALSE);
  tdefl_optimize_huffman_table(d, 1, TDEFL_MAX_HUFF_SYMBOLS_1, 15, MZ_FALSE);

  വേണ്ടി (അക്കം_lit_codes = 286; അക്കം_lit_codes > 257; അക്കം_lit_codes--) എങ്കിൽ (d->m_huff_code_sizes[0][അക്കം_lit_codes - 1]) നിർത്തുക;
  വേണ്ടി (അക്കം_dist_codes = 30; അക്കം_dist_codes > 1; അക്കം_dist_codes--) എങ്കിൽ (d->m_huff_code_sizes[1][അക്കം_dist_codes - 1]) നിർത്തുക;

  memcpy(code_sizes_to_pack, &d->m_huff_code_sizes[0][0], അക്കം_lit_codes);
  memcpy(code_sizes_to_pack + അക്കം_lit_codes, &d->m_huff_code_sizes[1][0], അക്കം_dist_codes);
  total_code_sizes_to_pack = അക്കം_lit_codes + അക്കം_dist_codes; അക്കം_packed_code_sizes = 0; rle_z_എണ്ണം = 0; rle_repeat_എണ്ണം = 0;

  memset(&d->m_huff_എണ്ണം[2][0], 0, വലുപ്പം(d->m_huff_എണ്ണം[2][0]) * TDEFL_MAX_HUFF_SYMBOLS_2);
  വേണ്ടി (i = 0; i < total_code_sizes_to_pack; i++)
  {
    mz_uint8 code_size = code_sizes_to_pack[i];
    എങ്കിൽ (!code_size)
    {
      TDEFL_RLE_PREV_CODE_SIZE();
      എങ്കിൽ (++rle_z_എണ്ണം == 138) { TDEFL_RLE_ZERO_CODE_SIZE(); }
    }
    അല്ലെങ്കിൽ
    {
      TDEFL_RLE_ZERO_CODE_SIZE();
      എങ്കിൽ (code_size != prev_code_size)
      {
        TDEFL_RLE_PREV_CODE_SIZE();
        d->m_huff_എണ്ണം[2][code_size] = (mz_uint16)(d->m_huff_എണ്ണം[2][code_size] + 1); packed_code_sizes[അക്കം_packed_code_sizes++] = code_size;
      }
      അല്ലെങ്കിൽ എങ്കിൽ (++rle_repeat_എണ്ണം == 6)
      {
        TDEFL_RLE_PREV_CODE_SIZE();
      }
    }
    prev_code_size = code_size;
  }
  എങ്കിൽ (rle_repeat_എണ്ണം) { TDEFL_RLE_PREV_CODE_SIZE(); } അല്ലെങ്കിൽ { TDEFL_RLE_ZERO_CODE_SIZE(); }

  tdefl_optimize_huffman_table(d, 2, TDEFL_MAX_HUFF_SYMBOLS_2, 7, MZ_FALSE);

  TDEFL_PUT_BITS(2, 2);

  TDEFL_PUT_BITS(അക്കം_lit_codes - 257, 5);
  TDEFL_PUT_BITS(അക്കം_dist_codes - 1, 5);

  വേണ്ടി (അക്കം_bit_lengths = 18; അക്കം_bit_lengths >= 0; അക്കം_bit_lengths--) എങ്കിൽ (d->m_huff_code_sizes[2][s_tdefl_packed_code_size_syms_swizzle[അക്കം_bit_lengths]]) നിർത്തുക;
  അക്കം_bit_lengths = MZ_MAX(4, (അക്കം_bit_lengths + 1)); TDEFL_PUT_BITS(അക്കം_bit_lengths - 4, 4);
  വേണ്ടി (i = 0; (പൂർണ്ണസംഖ്യ)i < അക്കം_bit_lengths; i++) TDEFL_PUT_BITS(d->m_huff_code_sizes[2][s_tdefl_packed_code_size_syms_swizzle[i]], 3);

  വേണ്ടി (packed_code_sizes_index = 0; packed_code_sizes_index < അക്കം_packed_code_sizes; )
  {
    mz_uint code = packed_code_sizes[packed_code_sizes_index++]; MZ_ASSERT(code < TDEFL_MAX_HUFF_SYMBOLS_2);
    TDEFL_PUT_BITS(d->m_huff_codes[2][code], d->m_huff_code_sizes[2][code]);
    എങ്കിൽ (code >= 16) TDEFL_PUT_BITS(packed_code_sizes[packed_code_sizes_index++], "\02\03\07"[code - 16]);
  }
}

സ്ഥിതം ശൂന്യം tdefl_start_static_block(tdefl_compressor *d)
{
  mz_uint i;
  mz_uint8 *p = &d->m_huff_code_sizes[0][0];

  വേണ്ടി (i = 0; i <= 143; ++i) *p++ = 8;
  വേണ്ടി ( ; i <= 255; ++i) *p++ = 9;
  വേണ്ടി ( ; i <= 279; ++i) *p++ = 7;
  വേണ്ടി ( ; i <= 287; ++i) *p++ = 8;

  memset(d->m_huff_code_sizes[1], 5, 32);

  tdefl_optimize_huffman_table(d, 0, 288, 15, MZ_TRUE);
  tdefl_optimize_huffman_table(d, 1, 32, 15, MZ_TRUE);

  TDEFL_PUT_BITS(1, 2);
}

സ്ഥിതം സ്ഥിരം mz_uint mz_bitmasks[17] = { 0x0000, 0x0001, 0x0003, 0x0007, 0x000F, 0x001F, 0x003F, 0x007F, 0x00FF, 0x01FF, 0x03FF, 0x07FF, 0x0FFF, 0x1FFF, 0x3FFF, 0x7FFF, 0xFFFF };

#എങ്കിൽ MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN && MINIZ_HAS_64BIT_REGISTERS
സ്ഥിതം mz_bool tdefl_compress_lz_codes(tdefl_compressor *d)
{
  mz_uint flags;
  mz_uint8 *pLZ_codes;
  mz_uint8 *pOutput_buf = d->m_pOutput_buf;
  mz_uint8 *pLZ_code_buf_end = d->m_pLZ_code_buf;
  mz_uint64 bit_buffer = d->m_bit_buffer;
  mz_uint bits_in = d->m_bits_in;

#define TDEFL_PUT_BITS_FAST(b, l) { bit_buffer |= (((mz_uint64)(b)) << bits_in); bits_in += (l); }

  flags = 1;
  വേണ്ടി (pLZ_codes = d->m_lz_code_buf; pLZ_codes < pLZ_code_buf_end; flags >>= 1)
  {
    എങ്കിൽ (flags == 1)
      flags = *pLZ_codes++ | 0x100;

    എങ്കിൽ (flags & 1)
    {
      mz_uint s0, s1, n0, n1, sym, അക്കം_extra_bits;
      mz_uint match_len = pLZ_codes[0], match_dist = *(സ്ഥിരം mz_uint16 *)(pLZ_codes + 1); pLZ_codes += 3;

      MZ_ASSERT(d->m_huff_code_sizes[0][s_tdefl_len_sym[match_len]]);
      TDEFL_PUT_BITS_FAST(d->m_huff_codes[0][s_tdefl_len_sym[match_len]], d->m_huff_code_sizes[0][s_tdefl_len_sym[match_len]]);
      TDEFL_PUT_BITS_FAST(match_len & mz_bitmasks[s_tdefl_len_extra[match_len]], s_tdefl_len_extra[match_len]);

      // This sequence coaxes MSVC into using cmov's vs. jmp's.
      s0 = s_tdefl_small_dist_sym[match_dist & 511];
      n0 = s_tdefl_small_dist_extra[match_dist & 511];
      s1 = s_tdefl_large_dist_sym[match_dist >> 8];
      n1 = s_tdefl_large_dist_extra[match_dist >> 8];
      sym = (match_dist < 512) ? s0 : s1;
      അക്കം_extra_bits = (match_dist < 512) ? n0 : n1;

      MZ_ASSERT(d->m_huff_code_sizes[1][sym]);
      TDEFL_PUT_BITS_FAST(d->m_huff_codes[1][sym], d->m_huff_code_sizes[1][sym]);
      TDEFL_PUT_BITS_FAST(match_dist & mz_bitmasks[അക്കം_extra_bits], അക്കം_extra_bits);
    }
    അല്ലെങ്കിൽ
    {
      mz_uint lit = *pLZ_codes++;
      MZ_ASSERT(d->m_huff_code_sizes[0][lit]);
      TDEFL_PUT_BITS_FAST(d->m_huff_codes[0][lit], d->m_huff_code_sizes[0][lit]);

      എങ്കിൽ (((flags & 2) == 0) && (pLZ_codes < pLZ_code_buf_end))
      {
        flags >>= 1;
        lit = *pLZ_codes++;
        MZ_ASSERT(d->m_huff_code_sizes[0][lit]);
        TDEFL_PUT_BITS_FAST(d->m_huff_codes[0][lit], d->m_huff_code_sizes[0][lit]);

        എങ്കിൽ (((flags & 2) == 0) && (pLZ_codes < pLZ_code_buf_end))
        {
          flags >>= 1;
          lit = *pLZ_codes++;
          MZ_ASSERT(d->m_huff_code_sizes[0][lit]);
          TDEFL_PUT_BITS_FAST(d->m_huff_codes[0][lit], d->m_huff_code_sizes[0][lit]);
        }
      }
    }

    എങ്കിൽ (pOutput_buf >= d->m_pOutput_buf_end)
      തിരികെ MZ_FALSE;

    *(mz_uint64*)pOutput_buf = bit_buffer;
    pOutput_buf += (bits_in >> 3);
    bit_buffer >>= (bits_in & ~7);
    bits_in &= 7;
  }

#undef TDEFL_PUT_BITS_FAST

  d->m_pOutput_buf = pOutput_buf;
  d->m_bits_in = 0;
  d->m_bit_buffer = 0;

  ആകുമ്പോൾ (bits_in)
  {
    mz_uint32 n = MZ_MIN(bits_in, 16);
    TDEFL_PUT_BITS((mz_uint)bit_buffer & mz_bitmasks[n], n);
    bit_buffer >>= n;
    bits_in -= n;
  }

  TDEFL_PUT_BITS(d->m_huff_codes[0][256], d->m_huff_code_sizes[0][256]);

  തിരികെ (d->m_pOutput_buf < d->m_pOutput_buf_end);
}
#അല്ലെങ്കിൽ
സ്ഥിതം mz_bool tdefl_compress_lz_codes(tdefl_compressor *d)
{
  mz_uint flags;
  mz_uint8 *pLZ_codes;

  flags = 1;
  വേണ്ടി (pLZ_codes = d->m_lz_code_buf; pLZ_codes < d->m_pLZ_code_buf; flags >>= 1)
  {
    എങ്കിൽ (flags == 1)
      flags = *pLZ_codes++ | 0x100;
    എങ്കിൽ (flags & 1)
    {
      mz_uint sym, അക്കം_extra_bits;
      mz_uint match_len = pLZ_codes[0], match_dist = (pLZ_codes[1] | (pLZ_codes[2] << 8)); pLZ_codes += 3;

      MZ_ASSERT(d->m_huff_code_sizes[0][s_tdefl_len_sym[match_len]]);
      TDEFL_PUT_BITS(d->m_huff_codes[0][s_tdefl_len_sym[match_len]], d->m_huff_code_sizes[0][s_tdefl_len_sym[match_len]]);
      TDEFL_PUT_BITS(match_len & mz_bitmasks[s_tdefl_len_extra[match_len]], s_tdefl_len_extra[match_len]);

      എങ്കിൽ (match_dist < 512)
      {
        sym = s_tdefl_small_dist_sym[match_dist]; അക്കം_extra_bits = s_tdefl_small_dist_extra[match_dist];
      }
      അല്ലെങ്കിൽ
      {
        sym = s_tdefl_large_dist_sym[match_dist >> 8]; അക്കം_extra_bits = s_tdefl_large_dist_extra[match_dist >> 8];
      }
      MZ_ASSERT(d->m_huff_code_sizes[1][sym]);
      TDEFL_PUT_BITS(d->m_huff_codes[1][sym], d->m_huff_code_sizes[1][sym]);
      TDEFL_PUT_BITS(match_dist & mz_bitmasks[അക്കം_extra_bits], അക്കം_extra_bits);
    }
    അല്ലെങ്കിൽ
    {
      mz_uint lit = *pLZ_codes++;
      MZ_ASSERT(d->m_huff_code_sizes[0][lit]);
      TDEFL_PUT_BITS(d->m_huff_codes[0][lit], d->m_huff_code_sizes[0][lit]);
    }
  }

  TDEFL_PUT_BITS(d->m_huff_codes[0][256], d->m_huff_code_sizes[0][256]);

  തിരികെ (d->m_pOutput_buf < d->m_pOutput_buf_end);
}
#endif // MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN && MINIZ_HAS_64BIT_REGISTERS

സ്ഥിതം mz_bool tdefl_compress_block(tdefl_compressor *d, mz_bool static_block)
{
  എങ്കിൽ (static_block)
    tdefl_start_static_block(d);
  അല്ലെങ്കിൽ
    tdefl_start_dynamic_block(d);
  തിരികെ tdefl_compress_lz_codes(d);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ tdefl_flush_block(tdefl_compressor *d, പൂർണ്ണസംഖ്യ flush)
{
  mz_uint saved_bit_buf, saved_bits_in;
  mz_uint8 *pSaved_output_buf;
  mz_bool comp_block_succeeded = MZ_FALSE;
  പൂർണ്ണസംഖ്യ n, use_raw_block = ((d->m_flags & TDEFL_FORCE_ALL_RAW_BLOCKS) != 0) && (d->m_lookahead_pos - d->m_lz_code_buf_dict_pos) <= d->m_dict_size;
  mz_uint8 *pOutput_buf_start = ((d->m_pPut_buf_func == ശൂന്യ) && ((*d->m_pOut_buf_size - d->m_out_buf_ofs) >= TDEFL_OUT_BUF_SIZE)) ? ((mz_uint8 *)d->m_pOut_buf + d->m_out_buf_ofs) : d->m_output_buf;

  d->m_pOutput_buf = pOutput_buf_start;
  d->m_pOutput_buf_end = d->m_pOutput_buf + TDEFL_OUT_BUF_SIZE - 16;

  MZ_ASSERT(!d->m_output_flush_remaining);
  d->m_output_flush_ofs = 0;
  d->m_output_flush_remaining = 0;

  *d->m_pLZ_flags = (mz_uint8)(*d->m_pLZ_flags >> d->m_അക്കം_flags_ഇടത്);
  d->m_pLZ_code_buf -= (d->m_അക്കം_flags_ഇടത് == 8);

  എങ്കിൽ ((d->m_flags & TDEFL_WRITE_ZLIB_HEADER) && (!d->m_block_index))
  {
    TDEFL_PUT_BITS(0x78, 8); TDEFL_PUT_BITS(0x01, 8);
  }

  TDEFL_PUT_BITS(flush == TDEFL_FINISH, 1);

  pSaved_output_buf = d->m_pOutput_buf; saved_bit_buf = d->m_bit_buffer; saved_bits_in = d->m_bits_in;

  എങ്കിൽ (!use_raw_block)
    comp_block_succeeded = tdefl_compress_block(d, (d->m_flags & TDEFL_FORCE_ALL_STATIC_BLOCKS) || (d->m_total_lz_bytes < 48));

  // If the block gets expanded, forget the current contents of the output buffer and send a raw block instead.
  എങ്കിൽ ( ((use_raw_block) || ((d->m_total_lz_bytes) && ((d->m_pOutput_buf - pSaved_output_buf + 1U) >= d->m_total_lz_bytes))) &&
       ((d->m_lookahead_pos - d->m_lz_code_buf_dict_pos) <= d->m_dict_size) )
  {
    mz_uint i; d->m_pOutput_buf = pSaved_output_buf; d->m_bit_buffer = saved_bit_buf; d->m_bits_in = saved_bits_in;
    TDEFL_PUT_BITS(0, 2);
    എങ്കിൽ (d->m_bits_in) { TDEFL_PUT_BITS(0, 8 - d->m_bits_in); }
    വേണ്ടി (i = 2; i; --i, d->m_total_lz_bytes ^= 0xFFFF)
    {
      TDEFL_PUT_BITS(d->m_total_lz_bytes & 0xFFFF, 16);
    }
    വേണ്ടി (i = 0; i < d->m_total_lz_bytes; ++i)
    {
      TDEFL_PUT_BITS(d->m_dict[(d->m_lz_code_buf_dict_pos + i) & TDEFL_LZ_DICT_SIZE_MASK], 8);
    }
  }
  // Check for the extremely unlikely (if not impossible) case of the compressed block not fitting into the output buffer when using dynamic codes.
  അല്ലെങ്കിൽ എങ്കിൽ (!comp_block_succeeded)
  {
    d->m_pOutput_buf = pSaved_output_buf; d->m_bit_buffer = saved_bit_buf; d->m_bits_in = saved_bits_in;
    tdefl_compress_block(d, MZ_TRUE);
  }

  എങ്കിൽ (flush)
  {
    എങ്കിൽ (flush == TDEFL_FINISH)
    {
      എങ്കിൽ (d->m_bits_in) { TDEFL_PUT_BITS(0, 8 - d->m_bits_in); }
      എങ്കിൽ (d->m_flags & TDEFL_WRITE_ZLIB_HEADER) { mz_uint i, a = d->m_adler32; വേണ്ടി (i = 0; i < 4; i++) { TDEFL_PUT_BITS((a >> 24) & 0xFF, 8); a <<= 8; } }
    }
    അല്ലെങ്കിൽ
    {
      mz_uint i, z = 0; TDEFL_PUT_BITS(0, 3); എങ്കിൽ (d->m_bits_in) { TDEFL_PUT_BITS(0, 8 - d->m_bits_in); } വേണ്ടി (i = 2; i; --i, z ^= 0xFFFF) { TDEFL_PUT_BITS(z & 0xFFFF, 16); }
    }
  }

  MZ_ASSERT(d->m_pOutput_buf < d->m_pOutput_buf_end);

  memset(&d->m_huff_എണ്ണം[0][0], 0, വലുപ്പം(d->m_huff_എണ്ണം[0][0]) * TDEFL_MAX_HUFF_SYMBOLS_0);
  memset(&d->m_huff_എണ്ണം[1][0], 0, വലുപ്പം(d->m_huff_എണ്ണം[1][0]) * TDEFL_MAX_HUFF_SYMBOLS_1);

  d->m_pLZ_code_buf = d->m_lz_code_buf + 1; d->m_pLZ_flags = d->m_lz_code_buf; d->m_അക്കം_flags_ഇടത് = 8; d->m_lz_code_buf_dict_pos += d->m_total_lz_bytes; d->m_total_lz_bytes = 0; d->m_block_index++;

  എങ്കിൽ ((n = (പൂർണ്ണസംഖ്യ)(d->m_pOutput_buf - pOutput_buf_start)) != 0)
  {
    എങ്കിൽ (d->m_pPut_buf_func)
    {
      *d->m_pIn_buf_size = d->m_pSrc - (സ്ഥിരം mz_uint8 *)d->m_pIn_buf;
      എങ്കിൽ (!(*d->m_pPut_buf_func)(d->m_output_buf, n, d->m_pPut_buf_user))
        തിരികെ (d->m_prev_return_status = TDEFL_STATUS_PUT_BUF_FAILED);
    }
    അല്ലെങ്കിൽ എങ്കിൽ (pOutput_buf_start == d->m_output_buf)
    {
      പൂർണ്ണസംഖ്യ bytes_to_copy = (പൂർണ്ണസംഖ്യ)MZ_MIN((size_t)n, (size_t)(*d->m_pOut_buf_size - d->m_out_buf_ofs));
      memcpy((mz_uint8 *)d->m_pOut_buf + d->m_out_buf_ofs, d->m_output_buf, bytes_to_copy);
      d->m_out_buf_ofs += bytes_to_copy;
      എങ്കിൽ ((n -= bytes_to_copy) != 0)
      {
        d->m_output_flush_ofs = bytes_to_copy;
        d->m_output_flush_remaining = n;
      }
    }
    അല്ലെങ്കിൽ
    {
      d->m_out_buf_ofs += n;
    }
  }

  തിരികെ d->m_output_flush_remaining;
}

#എങ്കിൽ MINIZ_USE_UNALIGNED_LOADS_AND_STORES
#define TDEFL_READ_UNALIGNED_WORD(p) *(സ്ഥിരം mz_uint16*)(p)
സ്ഥിതം MZ_FORCEINLINE ശൂന്യം tdefl_find_match(tdefl_compressor *d, mz_uint lookahead_pos, mz_uint max_dist, mz_uint max_match_len, mz_uint *pMatch_dist, mz_uint *pMatch_len)
{
  mz_uint dist, pos = lookahead_pos & TDEFL_LZ_DICT_SIZE_MASK, match_len = *pMatch_len, probe_pos = pos, next_probe_pos, probe_len;
  mz_uint അക്കം_probes_ഇടത് = d->m_max_probes[match_len >= 32];
  സ്ഥിരം mz_uint16 *s = (സ്ഥിരം mz_uint16*)(d->m_dict + pos), *p, *q;
  mz_uint16 c01 = TDEFL_READ_UNALIGNED_WORD(&d->m_dict[pos + match_len - 1]), s01 = TDEFL_READ_UNALIGNED_WORD(s);
  MZ_ASSERT(max_match_len <= TDEFL_MAX_MATCH_LEN); എങ്കിൽ (max_match_len <= match_len) തിരികെ;
  വേണ്ടി ( ; ; )
  {
    വേണ്ടി ( ; ; )
    {
      എങ്കിൽ (--അക്കം_probes_ഇടത് == 0) തിരികെ;
      #define TDEFL_PROBE \
        next_probe_pos = d->m_next[probe_pos]; \
        എങ്കിൽ ((!next_probe_pos) || ((dist = (mz_uint16)(lookahead_pos - next_probe_pos)) > max_dist)) തിരികെ; \
        probe_pos = next_probe_pos & TDEFL_LZ_DICT_SIZE_MASK; \
        എങ്കിൽ (TDEFL_READ_UNALIGNED_WORD(&d->m_dict[probe_pos + match_len - 1]) == c01) നിർത്തുക;
      TDEFL_PROBE
      TDEFL_PROBE
      TDEFL_PROBE
    }
    എങ്കിൽ (!dist) നിർത്തുക;
    q = (സ്ഥിരം mz_uint16*)(d->m_dict + probe_pos);
    എങ്കിൽ (TDEFL_READ_UNALIGNED_WORD(q) != s01) തുടരുക;
    p = s; probe_len = 32;
    ചെയ്യുക { } ആകുമ്പോൾ ( (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) && (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) &&
                   (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) && (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) && (--probe_len > 0) );
    എങ്കിൽ (!probe_len)
    {
      *pMatch_dist = dist; *pMatch_len = MZ_MIN(max_match_len, TDEFL_MAX_MATCH_LEN); നിർത്തുക;
    }
    അല്ലെങ്കിൽ എങ്കിൽ ((probe_len = ((mz_uint)(p - s) * 2) + (mz_uint)(*(സ്ഥിരം mz_uint8*)p == *(സ്ഥിരം mz_uint8*)q)) > match_len)
    {
      *pMatch_dist = dist; എങ്കിൽ ((*pMatch_len = match_len = MZ_MIN(max_match_len, probe_len)) == max_match_len) നിർത്തുക;
      c01 = TDEFL_READ_UNALIGNED_WORD(&d->m_dict[pos + match_len - 1]);
    }
  }
}
#അല്ലെങ്കിൽ
സ്ഥിതം MZ_FORCEINLINE ശൂന്യം tdefl_find_match(tdefl_compressor *d, mz_uint lookahead_pos, mz_uint max_dist, mz_uint max_match_len, mz_uint *pMatch_dist, mz_uint *pMatch_len)
{
  mz_uint dist, pos = lookahead_pos & TDEFL_LZ_DICT_SIZE_MASK, match_len = *pMatch_len, probe_pos = pos, next_probe_pos, probe_len;
  mz_uint അക്കം_probes_ഇടത് = d->m_max_probes[match_len >= 32];
  സ്ഥിരം mz_uint8 *s = d->m_dict + pos, *p, *q;
  mz_uint8 c0 = d->m_dict[pos + match_len], c1 = d->m_dict[pos + match_len - 1];
  MZ_ASSERT(max_match_len <= TDEFL_MAX_MATCH_LEN); എങ്കിൽ (max_match_len <= match_len) തിരികെ;
  വേണ്ടി ( ; ; )
  {
    വേണ്ടി ( ; ; )
    {
      എങ്കിൽ (--അക്കം_probes_ഇടത് == 0) തിരികെ;
      #define TDEFL_PROBE \
        next_probe_pos = d->m_next[probe_pos]; \
        എങ്കിൽ ((!next_probe_pos) || ((dist = (mz_uint16)(lookahead_pos - next_probe_pos)) > max_dist)) തിരികെ; \
        probe_pos = next_probe_pos & TDEFL_LZ_DICT_SIZE_MASK; \
        എങ്കിൽ ((d->m_dict[probe_pos + match_len] == c0) && (d->m_dict[probe_pos + match_len - 1] == c1)) നിർത്തുക;
      TDEFL_PROBE
      TDEFL_PROBE
      TDEFL_PROBE
    }
    എങ്കിൽ (!dist) നിർത്തുക;
    p = s; q = d->m_dict + probe_pos;
    വേണ്ടി (probe_len = 0; probe_len < max_match_len; probe_len++) {
        എങ്കിൽ (*p++ != *q++) നിർത്തുക;
    }
    എങ്കിൽ (probe_len > match_len)
    {
      *pMatch_dist = dist;
      എങ്കിൽ ((*pMatch_len = match_len = probe_len) == max_match_len) തിരികെ;
      c0 = d->m_dict[pos + match_len]; c1 = d->m_dict[pos + match_len - 1];
    }
  }
}
#endif // #if MINIZ_USE_UNALIGNED_LOADS_AND_STORES

#എങ്കിൽ MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
സ്ഥിതം mz_bool tdefl_compress_fast(tdefl_compressor *d)
{
  // Faster, minimally featured LZRW1-style match+parse loop with better register utilization. Intended for applications where raw throughput is valued more highly than ratio.
  mz_uint lookahead_pos = d->m_lookahead_pos, lookahead_size = d->m_lookahead_size, dict_size = d->m_dict_size, total_lz_bytes = d->m_total_lz_bytes, അക്കം_flags_ഇടത് = d->m_അക്കം_flags_ഇടത്;
  mz_uint8 *pLZ_code_buf = d->m_pLZ_code_buf, *pLZ_flags = d->m_pLZ_flags;
  mz_uint cur_pos = lookahead_pos & TDEFL_LZ_DICT_SIZE_MASK;

  ആകുമ്പോൾ ((d->m_src_buf_ഇടത്) || ((d->m_flush) && (lookahead_size)))
  {
    സ്ഥിരം mz_uint TDEFL_COMP_FAST_LOOKAHEAD_SIZE = 4096;
    mz_uint dst_pos = (lookahead_pos + lookahead_size) & TDEFL_LZ_DICT_SIZE_MASK;
    mz_uint അക്കം_bytes_to_process = (mz_uint)MZ_MIN(d->m_src_buf_ഇടത്, TDEFL_COMP_FAST_LOOKAHEAD_SIZE - lookahead_size);
    d->m_src_buf_ഇടത് -= അക്കം_bytes_to_process;
    lookahead_size += അക്കം_bytes_to_process;

    ആകുമ്പോൾ (അക്കം_bytes_to_process)
    {
      mz_uint32 n = MZ_MIN(TDEFL_LZ_DICT_SIZE - dst_pos, അക്കം_bytes_to_process);
      memcpy(d->m_dict + dst_pos, d->m_pSrc, n);
      എങ്കിൽ (dst_pos < (TDEFL_MAX_MATCH_LEN - 1))
        memcpy(d->m_dict + TDEFL_LZ_DICT_SIZE + dst_pos, d->m_pSrc, MZ_MIN(n, (TDEFL_MAX_MATCH_LEN - 1) - dst_pos));
      d->m_pSrc += n;
      dst_pos = (dst_pos + n) & TDEFL_LZ_DICT_SIZE_MASK;
      അക്കം_bytes_to_process -= n;
    }

    dict_size = MZ_MIN(TDEFL_LZ_DICT_SIZE - lookahead_size, dict_size);
    എങ്കിൽ ((!d->m_flush) && (lookahead_size < TDEFL_COMP_FAST_LOOKAHEAD_SIZE)) നിർത്തുക;

    ആകുമ്പോൾ (lookahead_size >= 4)
    {
      mz_uint cur_match_dist, cur_match_len = 1;
      mz_uint8 *pCur_dict = d->m_dict + cur_pos;
      mz_uint first_trigram = (*(സ്ഥിരം mz_uint32 *)pCur_dict) & 0xFFFFFF;
      mz_uint hash = (first_trigram ^ (first_trigram >> (24 - (TDEFL_LZ_HASH_BITS - 8)))) & TDEFL_LEVEL1_HASH_SIZE_MASK;
      mz_uint probe_pos = d->m_hash[hash];
      d->m_hash[hash] = (mz_uint16)lookahead_pos;

      എങ്കിൽ (((cur_match_dist = (mz_uint16)(lookahead_pos - probe_pos)) <= dict_size) && ((*(സ്ഥിരം mz_uint32 *)(d->m_dict + (probe_pos &= TDEFL_LZ_DICT_SIZE_MASK)) & 0xFFFFFF) == first_trigram))
      {
        സ്ഥിരം mz_uint16 *p = (സ്ഥിരം mz_uint16 *)pCur_dict;
        സ്ഥിരം mz_uint16 *q = (സ്ഥിരം mz_uint16 *)(d->m_dict + probe_pos);
        mz_uint32 probe_len = 32;
        ചെയ്യുക { } ആകുമ്പോൾ ( (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) && (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) &&
          (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) && (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) && (--probe_len > 0) );
        cur_match_len = ((mz_uint)(p - (സ്ഥിരം mz_uint16 *)pCur_dict) * 2) + (mz_uint)(*(സ്ഥിരം mz_uint8 *)p == *(സ്ഥിരം mz_uint8 *)q);
        എങ്കിൽ (!probe_len)
          cur_match_len = cur_match_dist ? TDEFL_MAX_MATCH_LEN : 0;

        എങ്കിൽ ((cur_match_len < TDEFL_MIN_MATCH_LEN) || ((cur_match_len == TDEFL_MIN_MATCH_LEN) && (cur_match_dist >= 8U*1024U)))
        {
          cur_match_len = 1;
          *pLZ_code_buf++ = (mz_uint8)first_trigram;
          *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
          d->m_huff_എണ്ണം[0][(mz_uint8)first_trigram]++;
        }
        അല്ലെങ്കിൽ
        {
          mz_uint32 s0, s1;
          cur_match_len = MZ_MIN(cur_match_len, lookahead_size);

          MZ_ASSERT((cur_match_len >= TDEFL_MIN_MATCH_LEN) && (cur_match_dist >= 1) && (cur_match_dist <= TDEFL_LZ_DICT_SIZE));

          cur_match_dist--;

          pLZ_code_buf[0] = (mz_uint8)(cur_match_len - TDEFL_MIN_MATCH_LEN);
          *(mz_uint16 *)(&pLZ_code_buf[1]) = (mz_uint16)cur_match_dist;
          pLZ_code_buf += 3;
          *pLZ_flags = (mz_uint8)((*pLZ_flags >> 1) | 0x80);

          s0 = s_tdefl_small_dist_sym[cur_match_dist & 511];
          s1 = s_tdefl_large_dist_sym[cur_match_dist >> 8];
          d->m_huff_എണ്ണം[1][(cur_match_dist < 512) ? s0 : s1]++;

          d->m_huff_എണ്ണം[0][s_tdefl_len_sym[cur_match_len - TDEFL_MIN_MATCH_LEN]]++;
        }
      }
      അല്ലെങ്കിൽ
      {
        *pLZ_code_buf++ = (mz_uint8)first_trigram;
        *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
        d->m_huff_എണ്ണം[0][(mz_uint8)first_trigram]++;
      }

      എങ്കിൽ (--അക്കം_flags_ഇടത് == 0) { അക്കം_flags_ഇടത് = 8; pLZ_flags = pLZ_code_buf++; }

      total_lz_bytes += cur_match_len;
      lookahead_pos += cur_match_len;
      dict_size = MZ_MIN(dict_size + cur_match_len, TDEFL_LZ_DICT_SIZE);
      cur_pos = (cur_pos + cur_match_len) & TDEFL_LZ_DICT_SIZE_MASK;
      MZ_ASSERT(lookahead_size >= cur_match_len);
      lookahead_size -= cur_match_len;

      എങ്കിൽ (pLZ_code_buf > &d->m_lz_code_buf[TDEFL_LZ_CODE_BUF_SIZE - 8])
      {
        പൂർണ്ണസംഖ്യ n;
        d->m_lookahead_pos = lookahead_pos; d->m_lookahead_size = lookahead_size; d->m_dict_size = dict_size;
        d->m_total_lz_bytes = total_lz_bytes; d->m_pLZ_code_buf = pLZ_code_buf; d->m_pLZ_flags = pLZ_flags; d->m_അക്കം_flags_ഇടത് = അക്കം_flags_ഇടത്;
        എങ്കിൽ ((n = tdefl_flush_block(d, 0)) != 0)
          തിരികെ (n < 0) ? MZ_FALSE : MZ_TRUE;
        total_lz_bytes = d->m_total_lz_bytes; pLZ_code_buf = d->m_pLZ_code_buf; pLZ_flags = d->m_pLZ_flags; അക്കം_flags_ഇടത് = d->m_അക്കം_flags_ഇടത്;
      }
    }

    ആകുമ്പോൾ (lookahead_size)
    {
      mz_uint8 lit = d->m_dict[cur_pos];

      total_lz_bytes++;
      *pLZ_code_buf++ = lit;
      *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
      എങ്കിൽ (--അക്കം_flags_ഇടത് == 0) { അക്കം_flags_ഇടത് = 8; pLZ_flags = pLZ_code_buf++; }

      d->m_huff_എണ്ണം[0][lit]++;

      lookahead_pos++;
      dict_size = MZ_MIN(dict_size + 1, TDEFL_LZ_DICT_SIZE);
      cur_pos = (cur_pos + 1) & TDEFL_LZ_DICT_SIZE_MASK;
      lookahead_size--;

      എങ്കിൽ (pLZ_code_buf > &d->m_lz_code_buf[TDEFL_LZ_CODE_BUF_SIZE - 8])
      {
        പൂർണ്ണസംഖ്യ n;
        d->m_lookahead_pos = lookahead_pos; d->m_lookahead_size = lookahead_size; d->m_dict_size = dict_size;
        d->m_total_lz_bytes = total_lz_bytes; d->m_pLZ_code_buf = pLZ_code_buf; d->m_pLZ_flags = pLZ_flags; d->m_അക്കം_flags_ഇടത് = അക്കം_flags_ഇടത്;
        എങ്കിൽ ((n = tdefl_flush_block(d, 0)) != 0)
          തിരികെ (n < 0) ? MZ_FALSE : MZ_TRUE;
        total_lz_bytes = d->m_total_lz_bytes; pLZ_code_buf = d->m_pLZ_code_buf; pLZ_flags = d->m_pLZ_flags; അക്കം_flags_ഇടത് = d->m_അക്കം_flags_ഇടത്;
      }
    }
  }

  d->m_lookahead_pos = lookahead_pos; d->m_lookahead_size = lookahead_size; d->m_dict_size = dict_size;
  d->m_total_lz_bytes = total_lz_bytes; d->m_pLZ_code_buf = pLZ_code_buf; d->m_pLZ_flags = pLZ_flags; d->m_അക്കം_flags_ഇടത് = അക്കം_flags_ഇടത്;
  തിരികെ MZ_TRUE;
}
#endif // MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN

സ്ഥിതം MZ_FORCEINLINE ശൂന്യം tdefl_record_literal(tdefl_compressor *d, mz_uint8 lit)
{
  d->m_total_lz_bytes++;
  *d->m_pLZ_code_buf++ = lit;
  *d->m_pLZ_flags = (mz_uint8)(*d->m_pLZ_flags >> 1); എങ്കിൽ (--d->m_അക്കം_flags_ഇടത് == 0) { d->m_അക്കം_flags_ഇടത് = 8; d->m_pLZ_flags = d->m_pLZ_code_buf++; }
  d->m_huff_എണ്ണം[0][lit]++;
}

സ്ഥിതം MZ_FORCEINLINE ശൂന്യം tdefl_record_match(tdefl_compressor *d, mz_uint match_len, mz_uint match_dist)
{
  mz_uint32 s0, s1;

  MZ_ASSERT((match_len >= TDEFL_MIN_MATCH_LEN) && (match_dist >= 1) && (match_dist <= TDEFL_LZ_DICT_SIZE));

  d->m_total_lz_bytes += match_len;

  d->m_pLZ_code_buf[0] = (mz_uint8)(match_len - TDEFL_MIN_MATCH_LEN);

  match_dist -= 1;
  d->m_pLZ_code_buf[1] = (mz_uint8)(match_dist & 0xFF);
  d->m_pLZ_code_buf[2] = (mz_uint8)(match_dist >> 8); d->m_pLZ_code_buf += 3;

  *d->m_pLZ_flags = (mz_uint8)((*d->m_pLZ_flags >> 1) | 0x80); എങ്കിൽ (--d->m_അക്കം_flags_ഇടത് == 0) { d->m_അക്കം_flags_ഇടത് = 8; d->m_pLZ_flags = d->m_pLZ_code_buf++; }

  s0 = s_tdefl_small_dist_sym[match_dist & 511]; s1 = s_tdefl_large_dist_sym[(match_dist >> 8) & 127];
  d->m_huff_എണ്ണം[1][(match_dist < 512) ? s0 : s1]++;

  എങ്കിൽ (match_len >= TDEFL_MIN_MATCH_LEN) d->m_huff_എണ്ണം[0][s_tdefl_len_sym[match_len - TDEFL_MIN_MATCH_LEN]]++;
}

സ്ഥിതം mz_bool tdefl_compress_normal(tdefl_compressor *d)
{
  സ്ഥിരം mz_uint8 *pSrc = d->m_pSrc; size_t src_buf_ഇടത് = d->m_src_buf_ഇടത്;
  tdefl_flush flush = d->m_flush;

  ആകുമ്പോൾ ((src_buf_ഇടത്) || ((flush) && (d->m_lookahead_size)))
  {
    mz_uint len_to_move, cur_match_dist, cur_match_len, cur_pos;
    // Update dictionary and hash chains. Keeps the lookahead size equal to TDEFL_MAX_MATCH_LEN.
    എങ്കിൽ ((d->m_lookahead_size + d->m_dict_size) >= (TDEFL_MIN_MATCH_LEN - 1))
    {
      mz_uint dst_pos = (d->m_lookahead_pos + d->m_lookahead_size) & TDEFL_LZ_DICT_SIZE_MASK, ins_pos = d->m_lookahead_pos + d->m_lookahead_size - 2;
      mz_uint hash = (d->m_dict[ins_pos & TDEFL_LZ_DICT_SIZE_MASK] << TDEFL_LZ_HASH_SHIFT) ^ d->m_dict[(ins_pos + 1) & TDEFL_LZ_DICT_SIZE_MASK];
      mz_uint അക്കം_bytes_to_process = (mz_uint)MZ_MIN(src_buf_ഇടത്, TDEFL_MAX_MATCH_LEN - d->m_lookahead_size);
      സ്ഥിരം mz_uint8 *pSrc_end = pSrc ? pSrc + അക്കം_bytes_to_process : ശൂന്യ;
      src_buf_ഇടത് -= അക്കം_bytes_to_process;
      d->m_lookahead_size += അക്കം_bytes_to_process;
      ആകുമ്പോൾ (pSrc != pSrc_end)
      {
        mz_uint8 c = *pSrc++; d->m_dict[dst_pos] = c; എങ്കിൽ (dst_pos < (TDEFL_MAX_MATCH_LEN - 1)) d->m_dict[TDEFL_LZ_DICT_SIZE + dst_pos] = c;
        hash = ((hash << TDEFL_LZ_HASH_SHIFT) ^ c) & (TDEFL_LZ_HASH_SIZE - 1);
        d->m_next[ins_pos & TDEFL_LZ_DICT_SIZE_MASK] = d->m_hash[hash]; d->m_hash[hash] = (mz_uint16)(ins_pos);
        dst_pos = (dst_pos + 1) & TDEFL_LZ_DICT_SIZE_MASK; ins_pos++;
      }
    }
    അല്ലെങ്കിൽ
    {
      ആകുമ്പോൾ ((src_buf_ഇടത്) && (d->m_lookahead_size < TDEFL_MAX_MATCH_LEN))
      {
        mz_uint8 c = *pSrc++;
        mz_uint dst_pos = (d->m_lookahead_pos + d->m_lookahead_size) & TDEFL_LZ_DICT_SIZE_MASK;
        src_buf_ഇടത്--;
        d->m_dict[dst_pos] = c;
        എങ്കിൽ (dst_pos < (TDEFL_MAX_MATCH_LEN - 1))
          d->m_dict[TDEFL_LZ_DICT_SIZE + dst_pos] = c;
        എങ്കിൽ ((++d->m_lookahead_size + d->m_dict_size) >= TDEFL_MIN_MATCH_LEN)
        {
          mz_uint ins_pos = d->m_lookahead_pos + (d->m_lookahead_size - 1) - 2;
          mz_uint hash = ((d->m_dict[ins_pos & TDEFL_LZ_DICT_SIZE_MASK] << (TDEFL_LZ_HASH_SHIFT * 2)) ^ (d->m_dict[(ins_pos + 1) & TDEFL_LZ_DICT_SIZE_MASK] << TDEFL_LZ_HASH_SHIFT) ^ c) & (TDEFL_LZ_HASH_SIZE - 1);
          d->m_next[ins_pos & TDEFL_LZ_DICT_SIZE_MASK] = d->m_hash[hash]; d->m_hash[hash] = (mz_uint16)(ins_pos);
        }
      }
    }
    d->m_dict_size = MZ_MIN(TDEFL_LZ_DICT_SIZE - d->m_lookahead_size, d->m_dict_size);
    എങ്കിൽ ((!flush) && (d->m_lookahead_size < TDEFL_MAX_MATCH_LEN))
      നിർത്തുക;

    // Simple lazy/greedy parsing state machine.
    len_to_move = 1; cur_match_dist = 0; cur_match_len = d->m_saved_match_len ? d->m_saved_match_len : (TDEFL_MIN_MATCH_LEN - 1); cur_pos = d->m_lookahead_pos & TDEFL_LZ_DICT_SIZE_MASK;
    എങ്കിൽ (d->m_flags & (TDEFL_RLE_MATCHES | TDEFL_FORCE_ALL_RAW_BLOCKS))
    {
      എങ്കിൽ ((d->m_dict_size) && (!(d->m_flags & TDEFL_FORCE_ALL_RAW_BLOCKS)))
      {
        mz_uint8 c = d->m_dict[(cur_pos - 1) & TDEFL_LZ_DICT_SIZE_MASK];
        cur_match_len = 0; ആകുമ്പോൾ (cur_match_len < d->m_lookahead_size) { എങ്കിൽ (d->m_dict[cur_pos + cur_match_len] != c) നിർത്തുക; cur_match_len++; }
        എങ്കിൽ (cur_match_len < TDEFL_MIN_MATCH_LEN) cur_match_len = 0; അല്ലെങ്കിൽ cur_match_dist = 1;
      }
    }
    അല്ലെങ്കിൽ
    {
      tdefl_find_match(d, d->m_lookahead_pos, d->m_dict_size, d->m_lookahead_size, &cur_match_dist, &cur_match_len);
    }
    എങ്കിൽ (((cur_match_len == TDEFL_MIN_MATCH_LEN) && (cur_match_dist >= 8U*1024U)) || (cur_pos == cur_match_dist) || ((d->m_flags & TDEFL_FILTER_MATCHES) && (cur_match_len <= 5)))
    {
      cur_match_dist = cur_match_len = 0;
    }
    എങ്കിൽ (d->m_saved_match_len)
    {
      എങ്കിൽ (cur_match_len > d->m_saved_match_len)
      {
        tdefl_record_literal(d, (mz_uint8)d->m_saved_lit);
        എങ്കിൽ (cur_match_len >= 128)
        {
          tdefl_record_match(d, cur_match_len, cur_match_dist);
          d->m_saved_match_len = 0; len_to_move = cur_match_len;
        }
        അല്ലെങ്കിൽ
        {
          d->m_saved_lit = d->m_dict[cur_pos]; d->m_saved_match_dist = cur_match_dist; d->m_saved_match_len = cur_match_len;
        }
      }
      അല്ലെങ്കിൽ
      {
        tdefl_record_match(d, d->m_saved_match_len, d->m_saved_match_dist);
        len_to_move = d->m_saved_match_len - 1; d->m_saved_match_len = 0;
      }
    }
    അല്ലെങ്കിൽ എങ്കിൽ (!cur_match_dist)
      tdefl_record_literal(d, d->m_dict[MZ_MIN(cur_pos, വലുപ്പം(d->m_dict) - 1)]);
    അല്ലെങ്കിൽ എങ്കിൽ ((d->m_greedy_parsing) || (d->m_flags & TDEFL_RLE_MATCHES) || (cur_match_len >= 128))
    {
      tdefl_record_match(d, cur_match_len, cur_match_dist);
      len_to_move = cur_match_len;
    }
    അല്ലെങ്കിൽ
    {
      d->m_saved_lit = d->m_dict[MZ_MIN(cur_pos, വലുപ്പം(d->m_dict) - 1)]; d->m_saved_match_dist = cur_match_dist; d->m_saved_match_len = cur_match_len;
    }
    // Move the lookahead forward by len_to_move bytes.
    d->m_lookahead_pos += len_to_move;
    MZ_ASSERT(d->m_lookahead_size >= len_to_move);
    d->m_lookahead_size -= len_to_move;
    d->m_dict_size = MZ_MIN(d->m_dict_size + len_to_move, TDEFL_LZ_DICT_SIZE);
    // Check if it's time to flush the current LZ codes to the internal output buffer.
    എങ്കിൽ ( (d->m_pLZ_code_buf > &d->m_lz_code_buf[TDEFL_LZ_CODE_BUF_SIZE - 8]) ||
         ( (d->m_total_lz_bytes > 31*1024) && (((((mz_uint)(d->m_pLZ_code_buf - d->m_lz_code_buf) * 115) >> 7) >= d->m_total_lz_bytes) || (d->m_flags & TDEFL_FORCE_ALL_RAW_BLOCKS))) )
    {
      പൂർണ്ണസംഖ്യ n;
      d->m_pSrc = pSrc; d->m_src_buf_ഇടത് = src_buf_ഇടത്;
      എങ്കിൽ ((n = tdefl_flush_block(d, 0)) != 0)
        തിരികെ (n < 0) ? MZ_FALSE : MZ_TRUE;
    }
  }

  d->m_pSrc = pSrc; d->m_src_buf_ഇടത് = src_buf_ഇടത്;
  തിരികെ MZ_TRUE;
}

സ്ഥിതം tdefl_status tdefl_flush_output_buffer(tdefl_compressor *d)
{
  എങ്കിൽ (d->m_pIn_buf_size)
  {
    *d->m_pIn_buf_size = d->m_pSrc - (സ്ഥിരം mz_uint8 *)d->m_pIn_buf;
  }

  എങ്കിൽ (d->m_pOut_buf_size)
  {
    size_t n = MZ_MIN(*d->m_pOut_buf_size - d->m_out_buf_ofs, d->m_output_flush_remaining);
    memcpy((mz_uint8 *)d->m_pOut_buf + d->m_out_buf_ofs, d->m_output_buf + d->m_output_flush_ofs, n);
    d->m_output_flush_ofs += (mz_uint)n;
    d->m_output_flush_remaining -= (mz_uint)n;
    d->m_out_buf_ofs += n;

    *d->m_pOut_buf_size = d->m_out_buf_ofs;
  }

  തിരികെ (d->m_finished && !d->m_output_flush_remaining) ? TDEFL_STATUS_DONE : TDEFL_STATUS_OKAY;
}

tdefl_status tdefl_compress(tdefl_compressor *d, സ്ഥിരം ശൂന്യം *pIn_buf, size_t *pIn_buf_size, ശൂന്യം *pOut_buf, size_t *pOut_buf_size, tdefl_flush flush)
{
  എങ്കിൽ (!d)
  {
    എങ്കിൽ (pIn_buf_size) *pIn_buf_size = 0;
    എങ്കിൽ (pOut_buf_size) *pOut_buf_size = 0;
    തിരികെ TDEFL_STATUS_BAD_PARAM;
  }

  d->m_pIn_buf = pIn_buf; d->m_pIn_buf_size = pIn_buf_size;
  d->m_pOut_buf = pOut_buf; d->m_pOut_buf_size = pOut_buf_size;
  d->m_pSrc = (സ്ഥിരം mz_uint8 *)(pIn_buf); d->m_src_buf_ഇടത് = pIn_buf_size ? *pIn_buf_size : 0;
  d->m_out_buf_ofs = 0;
  d->m_flush = flush;

  എങ്കിൽ ( ((d->m_pPut_buf_func != ശൂന്യ) == ((pOut_buf != ശൂന്യ) || (pOut_buf_size != ശൂന്യ))) || (d->m_prev_return_status != TDEFL_STATUS_OKAY) ||
        (d->m_wants_to_finish && (flush != TDEFL_FINISH)) || (pIn_buf_size && *pIn_buf_size && !pIn_buf) || (pOut_buf_size && *pOut_buf_size && !pOut_buf) )
  {
    എങ്കിൽ (pIn_buf_size) *pIn_buf_size = 0;
    എങ്കിൽ (pOut_buf_size) *pOut_buf_size = 0;
    തിരികെ (d->m_prev_return_status = TDEFL_STATUS_BAD_PARAM);
  }
  d->m_wants_to_finish |= (flush == TDEFL_FINISH);

  എങ്കിൽ ((d->m_output_flush_remaining) || (d->m_finished))
    തിരികെ (d->m_prev_return_status = tdefl_flush_output_buffer(d));

#എങ്കിൽ MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  എങ്കിൽ (((d->m_flags & TDEFL_MAX_PROBES_MASK) == 1) &&
      ((d->m_flags & TDEFL_GREEDY_PARSING_FLAG) != 0) &&
      ((d->m_flags & (TDEFL_FILTER_MATCHES | TDEFL_FORCE_ALL_RAW_BLOCKS | TDEFL_RLE_MATCHES)) == 0))
  {
    എങ്കിൽ (!tdefl_compress_fast(d))
      തിരികെ d->m_prev_return_status;
  }
  അല്ലെങ്കിൽ
#endif // #if MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  {
    എങ്കിൽ (!tdefl_compress_normal(d))
      തിരികെ d->m_prev_return_status;
  }

  എങ്കിൽ ((d->m_flags & (TDEFL_WRITE_ZLIB_HEADER | TDEFL_COMPUTE_ADLER32)) && (pIn_buf))
    d->m_adler32 = (mz_uint32)mz_adler32(d->m_adler32, (സ്ഥിരം mz_uint8 *)pIn_buf, d->m_pSrc - (സ്ഥിരം mz_uint8 *)pIn_buf);

  എങ്കിൽ ((flush) && (!d->m_lookahead_size) && (!d->m_src_buf_ഇടത്) && (!d->m_output_flush_remaining))
  {
    എങ്കിൽ (tdefl_flush_block(d, flush) < 0)
      തിരികെ d->m_prev_return_status;
    d->m_finished = (flush == TDEFL_FINISH);
    എങ്കിൽ (flush == TDEFL_FULL_FLUSH) { MZ_CLEAR_ARR(d->m_hash); MZ_CLEAR_ARR(d->m_next); d->m_dict_size = 0; }
  }

  തിരികെ (d->m_prev_return_status = tdefl_flush_output_buffer(d));
}

tdefl_status tdefl_compress_buffer(tdefl_compressor *d, സ്ഥിരം ശൂന്യം *pIn_buf, size_t in_buf_size, tdefl_flush flush)
{
  MZ_ASSERT(d->m_pPut_buf_func); തിരികെ tdefl_compress(d, pIn_buf, &in_buf_size, ശൂന്യ, ശൂന്യ, flush);
}

tdefl_status tdefl_init(tdefl_compressor *d, tdefl_put_buf_func_ptr pPut_buf_func, ശൂന്യം *pPut_buf_user, പൂർണ്ണസംഖ്യ flags)
{
  d->m_pPut_buf_func = pPut_buf_func; d->m_pPut_buf_user = pPut_buf_user;
  d->m_flags = (mz_uint)(flags); d->m_max_probes[0] = 1 + ((flags & 0xFFF) + 2) / 3; d->m_greedy_parsing = (flags & TDEFL_GREEDY_PARSING_FLAG) != 0;
  d->m_max_probes[1] = 1 + (((flags & 0xFFF) >> 2) + 2) / 3;
  എങ്കിൽ (!(flags & TDEFL_NONDETERMINISTIC_PARSING_FLAG)) MZ_CLEAR_ARR(d->m_hash);
  d->m_lookahead_pos = d->m_lookahead_size = d->m_dict_size = d->m_total_lz_bytes = d->m_lz_code_buf_dict_pos = d->m_bits_in = 0;
  d->m_output_flush_ofs = d->m_output_flush_remaining = d->m_finished = d->m_block_index = d->m_bit_buffer = d->m_wants_to_finish = 0;
  d->m_pLZ_code_buf = d->m_lz_code_buf + 1; d->m_pLZ_flags = d->m_lz_code_buf; d->m_അക്കം_flags_ഇടത് = 8;
  d->m_pOutput_buf = d->m_output_buf; d->m_pOutput_buf_end = d->m_output_buf; d->m_prev_return_status = TDEFL_STATUS_OKAY;
  d->m_saved_match_dist = d->m_saved_match_len = d->m_saved_lit = 0; d->m_adler32 = 1;
  d->m_pIn_buf = ശൂന്യ; d->m_pOut_buf = ശൂന്യ;
  d->m_pIn_buf_size = ശൂന്യ; d->m_pOut_buf_size = ശൂന്യ;
  d->m_flush = TDEFL_NO_FLUSH; d->m_pSrc = ശൂന്യ; d->m_src_buf_ഇടത് = 0; d->m_out_buf_ofs = 0;
  memset(&d->m_huff_എണ്ണം[0][0], 0, വലുപ്പം(d->m_huff_എണ്ണം[0][0]) * TDEFL_MAX_HUFF_SYMBOLS_0);
  memset(&d->m_huff_എണ്ണം[1][0], 0, വലുപ്പം(d->m_huff_എണ്ണം[1][0]) * TDEFL_MAX_HUFF_SYMBOLS_1);
  തിരികെ TDEFL_STATUS_OKAY;
}

#ifndef MINIZ_SDL_NOUNUSED
tdefl_status tdefl_get_prev_return_status(tdefl_compressor *d)
{
  തിരികെ d->m_prev_return_status;
}

mz_uint32 tdefl_get_adler32(tdefl_compressor *d)
{
  തിരികെ d->m_adler32;
}

mz_bool tdefl_compress_mem_to_output(സ്ഥിരം ശൂന്യം *pBuf, size_t buf_len, tdefl_put_buf_func_ptr pPut_buf_func, ശൂന്യം *pPut_buf_user, പൂർണ്ണസംഖ്യ flags)
{
  tdefl_compressor *pComp; mz_bool succeeded; എങ്കിൽ (((buf_len) && (!pBuf)) || (!pPut_buf_func)) തിരികെ MZ_FALSE;
  pComp = (tdefl_compressor*)MZ_MALLOC(വലുപ്പം(tdefl_compressor)); എങ്കിൽ (!pComp) തിരികെ MZ_FALSE;
  succeeded = (tdefl_init(pComp, pPut_buf_func, pPut_buf_user, flags) == TDEFL_STATUS_OKAY);
  succeeded = succeeded && (tdefl_compress_buffer(pComp, pBuf, buf_len, TDEFL_FINISH) == TDEFL_STATUS_DONE);
  MZ_FREE(pComp); തിരികെ succeeded;
}
#endif /* MINIZ_SDL_NOUNUSED */

തരനിർവചനം ഘടന
{
  size_t m_size, m_capacity;
  mz_uint8 *m_pBuf;
  mz_bool m_expandable;
} tdefl_output_buffer;

സ്ഥിതം mz_bool tdefl_output_buffer_putter(സ്ഥിരം ശൂന്യം *pBuf, പൂർണ്ണസംഖ്യ len, ശൂന്യം *pUser)
{
  tdefl_output_buffer *p = (tdefl_output_buffer *)pUser;
  size_t new_size = p->m_size + len;
  എങ്കിൽ (new_size > p->m_capacity)
  {
    size_t new_capacity = p->m_capacity; mz_uint8 *pNew_buf; എങ്കിൽ (!p->m_expandable) തിരികെ MZ_FALSE;
    ചെയ്യുക { new_capacity = MZ_MAX(128U, new_capacity << 1U); } ആകുമ്പോൾ (new_size > new_capacity);
    pNew_buf = (mz_uint8*)MZ_REALLOC(p->m_pBuf, new_capacity); എങ്കിൽ (!pNew_buf) തിരികെ MZ_FALSE;
    p->m_pBuf = pNew_buf; p->m_capacity = new_capacity;
  }
  memcpy((mz_uint8*)p->m_pBuf + p->m_size, pBuf, len); p->m_size = new_size;
  തിരികെ MZ_TRUE;
}

#ifndef MINIZ_SDL_NOUNUSED
ശൂന്യം *tdefl_compress_mem_to_heap(സ്ഥിരം ശൂന്യം *pSrc_buf, size_t src_buf_len, size_t *pOut_len, പൂർണ്ണസംഖ്യ flags)
{
  tdefl_output_buffer out_buf; MZ_CLEAR_OBJ(out_buf);
  എങ്കിൽ (!pOut_len) തിരികെ MZ_FALSE; അല്ലെങ്കിൽ *pOut_len = 0;
  out_buf.m_expandable = MZ_TRUE;
  എങ്കിൽ (!tdefl_compress_mem_to_output(pSrc_buf, src_buf_len, tdefl_output_buffer_putter, &out_buf, flags)) തിരികെ ശൂന്യ;
  *pOut_len = out_buf.m_size; തിരികെ out_buf.m_pBuf;
}

size_t tdefl_compress_mem_to_mem(ശൂന്യം *pOut_buf, size_t out_buf_len, സ്ഥിരം ശൂന്യം *pSrc_buf, size_t src_buf_len, പൂർണ്ണസംഖ്യ flags)
{
  tdefl_output_buffer out_buf; MZ_CLEAR_OBJ(out_buf);
  എങ്കിൽ (!pOut_buf) തിരികെ 0;
  out_buf.m_pBuf = (mz_uint8*)pOut_buf; out_buf.m_capacity = out_buf_len;
  എങ്കിൽ (!tdefl_compress_mem_to_output(pSrc_buf, src_buf_len, tdefl_output_buffer_putter, &out_buf, flags)) തിരികെ 0;
  തിരികെ out_buf.m_size;
}
#endif /* MINIZ_SDL_NOUNUSED */

#ifndef MINIZ_NO_ZLIB_APIS
സ്ഥിതം സ്ഥിരം mz_uint s_tdefl_അക്കം_probes[11] = { 0, 1, 6, 32,  16, 32, 128, 256,  512, 768, 1500 };

// level may actually range from [0,10] (10 is a "hidden" max level, where we want a bit more compression and it's fine if throughput to fall off a cliff on some files).
mz_uint tdefl_create_comp_flags_from_zip_params(പൂർണ്ണസംഖ്യ level, പൂർണ്ണസംഖ്യ window_bits, പൂർണ്ണസംഖ്യ strategy)
{
  mz_uint comp_flags = s_tdefl_അക്കം_probes[(level >= 0) ? MZ_MIN(10, level) : MZ_DEFAULT_LEVEL] | ((level <= 3) ? TDEFL_GREEDY_PARSING_FLAG : 0);
  എങ്കിൽ (window_bits > 0) comp_flags |= TDEFL_WRITE_ZLIB_HEADER;

  എങ്കിൽ (!level) comp_flags |= TDEFL_FORCE_ALL_RAW_BLOCKS;
  അല്ലെങ്കിൽ എങ്കിൽ (strategy == MZ_FILTERED) comp_flags |= TDEFL_FILTER_MATCHES;
  അല്ലെങ്കിൽ എങ്കിൽ (strategy == MZ_HUFFMAN_ONLY) comp_flags &= ~TDEFL_MAX_PROBES_MASK;
  അല്ലെങ്കിൽ എങ്കിൽ (strategy == MZ_FIXED) comp_flags |= TDEFL_FORCE_ALL_STATIC_BLOCKS;
  അല്ലെങ്കിൽ എങ്കിൽ (strategy == MZ_RLE) comp_flags |= TDEFL_RLE_MATCHES;

  തിരികെ comp_flags;
}
#endif //MINIZ_NO_ZLIB_APIS

#ifdef _MSC_VER
#pragma warning (തള്ളുക)
#pragma warning (disable:4204) // nonstandard extension used : non-constant aggregate initializer (also supported by GNU C and C99, so no big deal)
#endif

// Simple PNG writer function by Alex Evans, 2011. Released into the public domain: https://gist.github.com/908299, more context at
// http://altdevblogaday.org/2011/04/06/a-smaller-jpg-encoder/.
// This is actually a modification of Alex's original code so PNG files generated by this function pass pngcheck.
MINIZ_STATIC ശൂന്യം *tdefl_write_image_to_png_file_in_memory_ex(സ്ഥിരം ശൂന്യം *pImage, പൂർണ്ണസംഖ്യ w, പൂർണ്ണസംഖ്യ h, പൂർണ്ണസംഖ്യ അക്കം_chans, പൂർണ്ണസംഖ്യ bpl, size_t *pLen_out, mz_uint level, mz_bool flip, mz_uint8 *plte, പൂർണ്ണസംഖ്യ plte_size, mz_uint8 *trns, പൂർണ്ണസംഖ്യ trns_size)
{
  // Using a local copy of this array here in case MINIZ_NO_ZLIB_APIS was defined.
  സ്ഥിതം സ്ഥിരം mz_uint s_tdefl_png_അക്കം_probes[11] = { 0, 1, 6, 32,  16, 32, 128, 256,  512, 768, 1500 };
  tdefl_compressor *pComp = (tdefl_compressor *)MZ_MALLOC(വലുപ്പം(tdefl_compressor)); tdefl_output_buffer out_buf; പൂർണ്ണസംഖ്യ i, y, z = 0; mz_uint32 c; *pLen_out = 0; size_t data_start, data_size;
  എങ്കിൽ (!pComp) തിരികെ ശൂന്യ;
  MZ_CLEAR_OBJ(out_buf); out_buf.m_expandable = MZ_TRUE;
  out_buf.m_capacity = 57+MZ_MAX(64, (1+w*അക്കം_chans)*h);
  എങ്കിൽ (plte_size > 0)
    out_buf.m_capacity += 12+plte_size;
  എങ്കിൽ (trns_size > 0)
    out_buf.m_capacity += 12+trns_size;
  എങ്കിൽ (ശൂന്യ == (out_buf.m_pBuf = (mz_uint8*)MZ_MALLOC(out_buf.m_capacity))) { MZ_FREE(pComp); തിരികെ ശൂന്യ; }
  // write header
  {
    സ്ഥിതം സ്ഥിരം mz_uint8 chans[] = {0x00, 0x00, 0x04, 0x02, 0x06};

    mz_uint8 pnghdr[33]={ 0x89,0x50,0x4e,0x47,0x0d,0x0a,0x1a,0x0a,
                          0x00,0x00,0x00,0x0d,0x49,0x48,0x44,0x52,
                          0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                          0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

    pnghdr[18] = (mz_uint8)(w>>8);
    pnghdr[19] = (mz_uint8)(w>>0);

    pnghdr[22] = (mz_uint8)(h>>8);
    pnghdr[23] = (mz_uint8)(h>>0);

    എങ്കിൽ (അക്കം_chans == 1 && plte_size > 0)
      pnghdr[25] = 3;
    അല്ലെങ്കിൽ
      pnghdr[25] = (chans[അക്കം_chans]);

    c = (mz_uint32)mz_crc32(MZ_CRC32_INIT,pnghdr+12,17);
    വേണ്ടി (i=0; i<4; ++i, c<<=8) ((mz_uint8*)(pnghdr+29))[i] = (mz_uint8)(c>>24);
    എങ്കിൽ (!tdefl_output_buffer_putter(pnghdr, വലുപ്പം(pnghdr), &out_buf)) { *pLen_out = 0; MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); തിരികെ ശൂന്യ; }
  }
  // write PLTE chunk
  എങ്കിൽ (plte_size > 0)
  {
    mz_uint8 hdr[8]={0x00,0x00,0x00,0x00,0x50,0x4c,0x54,0x45};

    hdr[0] = (mz_uint8)(plte_size>>24);
    hdr[1] = (mz_uint8)(plte_size>>16);
    hdr[2] = (mz_uint8)(plte_size>> 8);
    hdr[3] = (mz_uint8)(plte_size>> 0);
    എങ്കിൽ (!tdefl_output_buffer_putter(hdr, വലുപ്പം(hdr), &out_buf)) { *pLen_out = 0; MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); തിരികെ ശൂന്യ; }
    data_start = out_buf.m_size;
    എങ്കിൽ (!tdefl_output_buffer_putter(plte, plte_size, &out_buf)) { *pLen_out = 0; MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); തിരികെ ശൂന്യ; }
    എങ്കിൽ (!tdefl_output_buffer_putter("\0\0\0\0", 4, &out_buf)) { *pLen_out = 0; MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); തിരികെ ശൂന്യ; }
    c = (mz_uint32)mz_crc32(MZ_CRC32_INIT,out_buf.m_pBuf+data_start-4, plte_size+4);
    വേണ്ടി (i=0; i<4; ++i, c<<=8) (out_buf.m_pBuf+out_buf.m_size-4)[i] = (mz_uint8)(c >> 24);
  }
  // write tRNS chunk
  എങ്കിൽ (trns_size > 0)
  {
    mz_uint8 hdr[8]={0x00,0x00,0x00,0x00,0x74,0x52,0x4E,0x53};

    hdr[0] = (mz_uint8)(trns_size>>24);
    hdr[1] = (mz_uint8)(trns_size>>16);
    hdr[2] = (mz_uint8)(trns_size>> 8);
    hdr[3] = (mz_uint8)(trns_size>> 0);
    എങ്കിൽ (!tdefl_output_buffer_putter(hdr, വലുപ്പം(hdr), &out_buf)) { *pLen_out = 0; MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); തിരികെ ശൂന്യ; }
    data_start = out_buf.m_size;
    എങ്കിൽ (!tdefl_output_buffer_putter(trns, trns_size, &out_buf)) { *pLen_out = 0; MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); തിരികെ ശൂന്യ; }
    എങ്കിൽ (!tdefl_output_buffer_putter("\0\0\0\0", 4, &out_buf)) { *pLen_out = 0; MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); തിരികെ ശൂന്യ; }
    c = (mz_uint32)mz_crc32(MZ_CRC32_INIT,out_buf.m_pBuf+data_start-4, trns_size+4);
    വേണ്ടി (i=0; i<4; ++i, c<<=8) (out_buf.m_pBuf+out_buf.m_size-4)[i] = (mz_uint8)(c >> 24);
  }
  // write IDAT chunk
  എങ്കിൽ (!tdefl_output_buffer_putter("\0\0\0\0\x49\x44\x41\x54", 8, &out_buf)) { *pLen_out = 0; MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); തിരികെ ശൂന്യ; }
  data_start = out_buf.m_size;
  // compress image data
  tdefl_init(pComp, tdefl_output_buffer_putter, &out_buf, s_tdefl_png_അക്കം_probes[MZ_MIN(10, level)] | TDEFL_WRITE_ZLIB_HEADER);
  വേണ്ടി (y = 0; y < h; ++y) { tdefl_compress_buffer(pComp, &z, 1, TDEFL_NO_FLUSH); tdefl_compress_buffer(pComp, (mz_uint8*)pImage + (flip ? (h - 1 - y) : y) * bpl, w * അക്കം_chans, TDEFL_NO_FLUSH); }
  എങ്കിൽ (tdefl_compress_buffer(pComp, ശൂന്യ, 0, TDEFL_FINISH) != TDEFL_STATUS_DONE) { MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); തിരികെ ശൂന്യ; }
  // write IDAT size
  data_size = out_buf.m_size-data_start;
  (out_buf.m_pBuf+data_start-8)[0] = (mz_uint8)(data_size>>24);
  (out_buf.m_pBuf+data_start-8)[1] = (mz_uint8)(data_size>>16);
  (out_buf.m_pBuf+data_start-8)[2] = (mz_uint8)(data_size>> 8);
  (out_buf.m_pBuf+data_start-8)[3] = (mz_uint8)(data_size>> 0);
  // write footer (IDAT CRC-32, followed by IEND chunk)
  എങ്കിൽ (!tdefl_output_buffer_putter("\0\0\0\0\0\0\0\0\x49\x45\x4e\x44\xae\x42\x60\x82", 16, &out_buf)) { *pLen_out = 0; MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); തിരികെ ശൂന്യ; }
  c = (mz_uint32)mz_crc32(MZ_CRC32_INIT,out_buf.m_pBuf+data_start-4, data_size+4);
  വേണ്ടി (i=0; i<4; ++i, c<<=8) (out_buf.m_pBuf+out_buf.m_size-16)[i] = (mz_uint8)(c >> 24);
  // compute final size of file, grab compressed data buffer and return
  *pLen_out = out_buf.m_size;
  MZ_FREE(pComp);
  തിരികെ out_buf.m_pBuf;
}
#ifndef MINIZ_SDL_NOUNUSED
MINIZ_STATIC ശൂന്യം *tdefl_write_image_to_png_file_in_memory(സ്ഥിരം ശൂന്യം *pImage, പൂർണ്ണസംഖ്യ w, പൂർണ്ണസംഖ്യ h, പൂർണ്ണസംഖ്യ അക്കം_chans, പൂർണ്ണസംഖ്യ bpl, size_t *pLen_out)
{
  // Level 6 corresponds to TDEFL_DEFAULT_MAX_PROBES or MZ_DEFAULT_LEVEL (but we can't depend on MZ_DEFAULT_LEVEL being available in case the zlib API's where #defined out)
  തിരികെ tdefl_write_image_to_png_file_in_memory_ex(pImage, w, h, അക്കം_chans, bpl, pLen_out, 6, MZ_FALSE, ശൂന്യ, 0, ശൂന്യ, 0);
}
#endif

#ifdef _MSC_VER
#pragma warning (എടുക്കുക)
#endif
#endif /*#ifndef MINIZ_NO_DEFLATE_APIS*/

// ------------------- .ZIP archive reading

#ifndef MINIZ_NO_ARCHIVE_APIS

#ifdef MINIZ_NO_STDIO
  #define MZ_FILE ശൂന്യം *
#അല്ലെങ്കിൽ
  #അന്തര്ഭാവ <stdio.h>
  #അന്തര്ഭാവ <sys/stat.h>

  #എങ്കിൽ defined(_MSC_VER) || defined(__MINGW64__)
    സ്ഥിതം FILE *mz_fopen(സ്ഥിരം അക്ഷരം *pFilename, സ്ഥിരം അക്ഷരം *pMode)
    {
      FILE* pFile = ശൂന്യ;
      fopen_s(&pFile, pFilename, pMode);
      തിരികെ pFile;
    }
    സ്ഥിതം FILE *mz_freopen(സ്ഥിരം അക്ഷരം *pPath, സ്ഥിരം അക്ഷരം *pMode, FILE *pStream)
    {
      FILE* pFile = ശൂന്യ;
      എങ്കിൽ (freopen_s(&pFile, pPath, pMode, pStream))
        തിരികെ ശൂന്യ;
      തിരികെ pFile;
    }
    #ifndef MINIZ_NO_TIME
      #അന്തര്ഭാവ <sys/utime.h>
    #endif
    #define MZ_FILE FILE
    #define MZ_FOPEN mz_fopen
    #define MZ_FCLOSE fclose
    #define MZ_FREAD fread
    #define MZ_FWRITE fwrite
    #define MZ_FTELL64 _ftelli64
    #define MZ_FSEEK64 _fseeki64
    #define MZ_FILE_STAT_STRUCT _stat
    #define MZ_FILE_STAT _stat
    #define MZ_FFLUSH fflush
    #define MZ_FREOPEN mz_freopen
    #define MZ_DELETE_FILE remove
  #അല്ലെങ്കിലെങ്കിൽ defined(__MINGW32__)
    #ifndef MINIZ_NO_TIME
      #അന്തര്ഭാവ <sys/utime.h>
    #endif
    #define MZ_FILE FILE
    #define MZ_FOPEN(f, m) fopen(f, m)
    #define MZ_FCLOSE fclose
    #define MZ_FREAD fread
    #define MZ_FWRITE fwrite
    #define MZ_FTELL64 ftello64
    #define MZ_FSEEK64 fseeko64
    #define MZ_FILE_STAT_STRUCT _stat
    #define MZ_FILE_STAT _stat
    #define MZ_FFLUSH fflush
    #define MZ_FREOPEN(f, m, s) freopen(f, m, s)
    #define MZ_DELETE_FILE remove
  #അല്ലെങ്കിലെങ്കിൽ defined(__TINYC__)
    #ifndef MINIZ_NO_TIME
      #അന്തര്ഭാവ <sys/utime.h>
    #endif
    #define MZ_FILE FILE
    #define MZ_FOPEN(f, m) fopen(f, m)
    #define MZ_FCLOSE fclose
    #define MZ_FREAD fread
    #define MZ_FWRITE fwrite
    #define MZ_FTELL64 ftell
    #define MZ_FSEEK64 fseek
    #define MZ_FILE_STAT_STRUCT stat
    #define MZ_FILE_STAT stat
    #define MZ_FFLUSH fflush
    #define MZ_FREOPEN(f, m, s) freopen(f, m, s)
    #define MZ_DELETE_FILE remove
  #അല്ലെങ്കിലെങ്കിൽ defined(__GNUC__) && _LARGEFILE64_SOURCE
    #ifndef MINIZ_NO_TIME
      #അന്തര്ഭാവ <utime.h>
    #endif
    #define MZ_FILE FILE
    #define MZ_FOPEN(f, m) fopen64(f, m)
    #define MZ_FCLOSE fclose
    #define MZ_FREAD fread
    #define MZ_FWRITE fwrite
    #define MZ_FTELL64 ftello64
    #define MZ_FSEEK64 fseeko64
    #define MZ_FILE_STAT_STRUCT stat64
    #define MZ_FILE_STAT stat64
    #define MZ_FFLUSH fflush
    #define MZ_FREOPEN(p, m, s) freopen64(p, m, s)
    #define MZ_DELETE_FILE remove
  #അല്ലെങ്കിൽ
    #ifndef MINIZ_NO_TIME
      #അന്തര്ഭാവ <utime.h>
    #endif
    #define MZ_FILE FILE
    #define MZ_FOPEN(f, m) fopen(f, m)
    #define MZ_FCLOSE fclose
    #define MZ_FREAD fread
    #define MZ_FWRITE fwrite
    #define MZ_FTELL64 ftello
    #define MZ_FSEEK64 fseeko
    #define MZ_FILE_STAT_STRUCT stat
    #define MZ_FILE_STAT stat
    #define MZ_FFLUSH fflush
    #define MZ_FREOPEN(f, m, s) freopen(f, m, s)
    #define MZ_DELETE_FILE remove
  #endif // #ifdef _MSC_VER
#endif // #ifdef MINIZ_NO_STDIO

#define MZ_TOLOWER(c) ((((c) >= 'A') && ((c) <= 'Z')) ? ((c) - 'A' + 'a') : (c))

// Various ZIP archive enums. To completely avoid cross platform compiler alignment and platform endian issues, miniz.c doesn't use structs for any of this stuff.
എണ്ണൽ
{
  // ZIP archive identifiers and record sizes
  MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIG = 0x06054b50, MZ_ZIP_CENTRAL_DIR_HEADER_SIG = 0x02014b50, MZ_ZIP_LOCAL_DIR_HEADER_SIG = 0x04034b50,
  MZ_ZIP_LOCAL_DIR_HEADER_SIZE = 30, MZ_ZIP_CENTRAL_DIR_HEADER_SIZE = 46, MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE = 22,
  // Central directory header record offsets
  MZ_ZIP_CDH_SIG_OFS = 0, MZ_ZIP_CDH_VERSION_MADE_BY_OFS = 4, MZ_ZIP_CDH_VERSION_NEEDED_OFS = 6, MZ_ZIP_CDH_BIT_FLAG_OFS = 8,
  MZ_ZIP_CDH_METHOD_OFS = 10, MZ_ZIP_CDH_FILE_TIME_OFS = 12, MZ_ZIP_CDH_FILE_DATE_OFS = 14, MZ_ZIP_CDH_CRC32_OFS = 16,
  MZ_ZIP_CDH_COMPRESSED_SIZE_OFS = 20, MZ_ZIP_CDH_DECOMPRESSED_SIZE_OFS = 24, MZ_ZIP_CDH_FILENAME_LEN_OFS = 28, MZ_ZIP_CDH_EXTRA_LEN_OFS = 30,
  MZ_ZIP_CDH_COMMENT_LEN_OFS = 32, MZ_ZIP_CDH_DISK_START_OFS = 34, MZ_ZIP_CDH_INTERNAL_ATTR_OFS = 36, MZ_ZIP_CDH_EXTERNAL_ATTR_OFS = 38, MZ_ZIP_CDH_LOCAL_HEADER_OFS = 42,
  // Local directory header offsets
  MZ_ZIP_LDH_SIG_OFS = 0, MZ_ZIP_LDH_VERSION_NEEDED_OFS = 4, MZ_ZIP_LDH_BIT_FLAG_OFS = 6, MZ_ZIP_LDH_METHOD_OFS = 8, MZ_ZIP_LDH_FILE_TIME_OFS = 10,
  MZ_ZIP_LDH_FILE_DATE_OFS = 12, MZ_ZIP_LDH_CRC32_OFS = 14, MZ_ZIP_LDH_COMPRESSED_SIZE_OFS = 18, MZ_ZIP_LDH_DECOMPRESSED_SIZE_OFS = 22,
  MZ_ZIP_LDH_FILENAME_LEN_OFS = 26, MZ_ZIP_LDH_EXTRA_LEN_OFS = 28,
  // End of central directory offsets
  MZ_ZIP_ECDH_SIG_OFS = 0, MZ_ZIP_ECDH_അക്കം_THIS_DISK_OFS = 4, MZ_ZIP_ECDH_അക്കം_DISK_CDIR_OFS = 6, MZ_ZIP_ECDH_CDIR_അക്കം_ENTRIES_ON_DISK_OFS = 8,
  MZ_ZIP_ECDH_CDIR_TOTAL_ENTRIES_OFS = 10, MZ_ZIP_ECDH_CDIR_SIZE_OFS = 12, MZ_ZIP_ECDH_CDIR_OFS_OFS = 16, MZ_ZIP_ECDH_COMMENT_SIZE_OFS = 20,
};

തരനിർവചനം ഘടന
{
  ശൂന്യം *m_p;
  size_t m_size, m_capacity;
  mz_uint m_element_size;
} mz_zip_array;

ഘടന mz_zip_internal_state_tag
{
  mz_zip_array m_central_dir;
  mz_zip_array m_central_dir_offsets;
  mz_zip_array m_sorted_central_dir_offsets;
  MZ_FILE *m_pFile;
  ശൂന്യം *m_pMem;
  size_t m_mem_size;
  size_t m_mem_capacity;
};

#define MZ_ZIP_ARRAY_SET_ELEMENT_SIZE(array_ptr, element_size) (array_ptr)->m_element_size = element_size
#define MZ_ZIP_ARRAY_ELEMENT(array_ptr, element_type, index) ((element_type *)((array_ptr)->m_p))[index]

സ്ഥിതം MZ_FORCEINLINE ശൂന്യം mz_zip_array_clear(mz_zip_archive *pZip, mz_zip_array *pArray)
{
  pZip->m_pFree(pZip->m_pAlloc_opaque, pArray->m_p);
  memset(pArray, 0, വലുപ്പം(mz_zip_array));
}

സ്ഥിതം mz_bool mz_zip_array_ensure_capacity(mz_zip_archive *pZip, mz_zip_array *pArray, size_t min_new_capacity, mz_uint growing)
{
  ശൂന്യം *pNew_p; size_t new_capacity = min_new_capacity; MZ_ASSERT(pArray->m_element_size); എങ്കിൽ (pArray->m_capacity >= min_new_capacity) തിരികെ MZ_TRUE;
  എങ്കിൽ (growing) { new_capacity = MZ_MAX(1, pArray->m_capacity); ആകുമ്പോൾ (new_capacity < min_new_capacity) new_capacity *= 2; }
  എങ്കിൽ (ശൂന്യ == (pNew_p = pZip->m_pRealloc(pZip->m_pAlloc_opaque, pArray->m_p, pArray->m_element_size, new_capacity))) തിരികെ MZ_FALSE;
  pArray->m_p = pNew_p; pArray->m_capacity = new_capacity;
  തിരികെ MZ_TRUE;
}

സ്ഥിതം MZ_FORCEINLINE mz_bool mz_zip_array_reserve(mz_zip_archive *pZip, mz_zip_array *pArray, size_t new_capacity, mz_uint growing)
{
  എങ്കിൽ (new_capacity > pArray->m_capacity) { എങ്കിൽ (!mz_zip_array_ensure_capacity(pZip, pArray, new_capacity, growing)) തിരികെ MZ_FALSE; }
  തിരികെ MZ_TRUE;
}

സ്ഥിതം MZ_FORCEINLINE mz_bool mz_zip_array_resize(mz_zip_archive *pZip, mz_zip_array *pArray, size_t new_size, mz_uint growing)
{
  എങ്കിൽ (new_size > pArray->m_capacity) { എങ്കിൽ (!mz_zip_array_ensure_capacity(pZip, pArray, new_size, growing)) തിരികെ MZ_FALSE; }
  pArray->m_size = new_size;
  തിരികെ MZ_TRUE;
}

സ്ഥിതം MZ_FORCEINLINE mz_bool mz_zip_array_ensure_room(mz_zip_archive *pZip, mz_zip_array *pArray, size_t n)
{
  തിരികെ mz_zip_array_reserve(pZip, pArray, pArray->m_size + n, MZ_TRUE);
}

സ്ഥിതം MZ_FORCEINLINE mz_bool mz_zip_array_തള്ളുക_back(mz_zip_archive *pZip, mz_zip_array *pArray, സ്ഥിരം ശൂന്യം *pElements, size_t n)
{
  size_t orig_size = pArray->m_size; എങ്കിൽ (!mz_zip_array_resize(pZip, pArray, orig_size + n, MZ_TRUE)) തിരികെ MZ_FALSE;
  memcpy((mz_uint8*)pArray->m_p + orig_size * pArray->m_element_size, pElements, n * pArray->m_element_size);
  തിരികെ MZ_TRUE;
}

#ifndef MINIZ_NO_TIME
സ്ഥിതം time_t mz_zip_dos_to_time_t(പൂർണ്ണസംഖ്യ dos_time, പൂർണ്ണസംഖ്യ dos_date)
{
  ഘടന tm tm;
  memset(&tm, 0, വലുപ്പം(tm)); tm.tm_isdst = -1;
  tm.tm_year = ((dos_date >> 9) & 127) + 1980 - 1900; tm.tm_mon = ((dos_date >> 5) & 15) - 1; tm.tm_mday = dos_date & 31;
  tm.tm_hour = (dos_time >> 11) & 31; tm.tm_min = (dos_time >> 5) & 63; tm.tm_sec = (dos_time << 1) & 62;
  തിരികെ mktime(&tm);
}

സ്ഥിതം ശൂന്യം mz_zip_time_to_dos_time(time_t time, mz_uint16 *pDOS_time, mz_uint16 *pDOS_date)
{
#ifdef _MSC_VER
  ഘടന tm tm_struct;
  ഘടന tm *tm = &tm_struct;
  errno_t err = localtime_s(tm, &time);
  എങ്കിൽ (err)
  {
    *pDOS_date = 0; *pDOS_time = 0;
    തിരികെ;
  }
#അല്ലെങ്കിൽ
  ഘടന tm *tm = localtime(&time);
#endif
  *pDOS_time = (mz_uint16)(((tm->tm_hour) << 11) + ((tm->tm_min) << 5) + ((tm->tm_sec) >> 1));
  *pDOS_date = (mz_uint16)(((tm->tm_year + 1900 - 1980) << 9) + ((tm->tm_mon + 1) << 5) + tm->tm_mday);
}
#endif

#ifndef MINIZ_NO_STDIO
സ്ഥിതം mz_bool mz_zip_get_file_modified_time(സ്ഥിരം അക്ഷരം *pFilename, mz_uint16 *pDOS_time, mz_uint16 *pDOS_date)
{
#ifdef MINIZ_NO_TIME
  (ശൂന്യം)pFilename; *pDOS_date = *pDOS_time = 0;
#അല്ലെങ്കിൽ
  ഘടന MZ_FILE_STAT_STRUCT file_stat;
  // On Linux with x86 glibc, this call will fail on large files (>= 0x80000000 bytes) unless you compiled with _LARGEFILE64_SOURCE. Argh.
  എങ്കിൽ (MZ_FILE_STAT(pFilename, &file_stat) != 0)
    തിരികെ MZ_FALSE;
  mz_zip_time_to_dos_time(file_stat.st_mtime, pDOS_time, pDOS_date);
#endif // #ifdef MINIZ_NO_TIME
  തിരികെ MZ_TRUE;
}

#ifndef MINIZ_NO_TIME
സ്ഥിതം mz_bool mz_zip_set_file_times(സ്ഥിരം അക്ഷരം *pFilename, time_t access_time, time_t modified_time)
{
  ഘടന utimbuf t; t.actime = access_time; t.modtime = modified_time;
  തിരികെ !utime(pFilename, &t);
}
#endif // #ifndef MINIZ_NO_TIME
#endif // #ifndef MINIZ_NO_STDIO

സ്ഥിതം mz_bool mz_zip_reader_init_internal(mz_zip_archive *pZip, mz_uint32 flags)
{
  (ശൂന്യം)flags;
  എങ്കിൽ ((!pZip) || (pZip->m_pState) || (pZip->m_zip_mode != MZ_ZIP_MODE_INVALID))
    തിരികെ MZ_FALSE;

  എങ്കിൽ (!pZip->m_pAlloc) pZip->m_pAlloc = def_alloc_func;
  എങ്കിൽ (!pZip->m_pFree) pZip->m_pFree = def_free_func;
  എങ്കിൽ (!pZip->m_pRealloc) pZip->m_pRealloc = def_realloc_func;

  pZip->m_zip_mode = MZ_ZIP_MODE_READING;
  pZip->m_archive_size = 0;
  pZip->m_central_directory_file_ofs = 0;
  pZip->m_total_files = 0;

  എങ്കിൽ (ശൂന്യ == (pZip->m_pState = (mz_zip_internal_state *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, വലുപ്പം(mz_zip_internal_state))))
    തിരികെ MZ_FALSE;
  memset(pZip->m_pState, 0, വലുപ്പം(mz_zip_internal_state));
  MZ_ZIP_ARRAY_SET_ELEMENT_SIZE(&pZip->m_pState->m_central_dir, വലുപ്പം(mz_uint8));
  MZ_ZIP_ARRAY_SET_ELEMENT_SIZE(&pZip->m_pState->m_central_dir_offsets, വലുപ്പം(mz_uint32));
  MZ_ZIP_ARRAY_SET_ELEMENT_SIZE(&pZip->m_pState->m_sorted_central_dir_offsets, വലുപ്പം(mz_uint32));
  തിരികെ MZ_TRUE;
}

സ്ഥിതം MZ_FORCEINLINE mz_bool mz_zip_reader_filename_less(സ്ഥിരം mz_zip_array *pCentral_dir_array, സ്ഥിരം mz_zip_array *pCentral_dir_offsets, mz_uint l_index, mz_uint r_index)
{
  സ്ഥിരം mz_uint8 *pL = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, l_index)), *pE;
  സ്ഥിരം mz_uint8 *pR = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, r_index));
  mz_uint l_len = MZ_READ_LE16(pL + MZ_ZIP_CDH_FILENAME_LEN_OFS), r_len = MZ_READ_LE16(pR + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  mz_uint8 l = 0, r = 0;
  pL += MZ_ZIP_CENTRAL_DIR_HEADER_SIZE; pR += MZ_ZIP_CENTRAL_DIR_HEADER_SIZE;
  pE = pL + MZ_MIN(l_len, r_len);
  ആകുമ്പോൾ (pL < pE)
  {
    എങ്കിൽ ((l = MZ_TOLOWER(*pL)) != (r = MZ_TOLOWER(*pR)))
      നിർത്തുക;
    pL++; pR++;
  }
  തിരികെ (pL == pE) ? (l_len < r_len) : (l < r);
}

#define MZ_SWAP_UINT32(a, b) ചെയ്യുക { mz_uint32 t = a; a = b; b = t; } MZ_MACRO_END

// Heap sort of lowercased filenames, used to help accelerate plain central directory searches by mz_zip_reader_locate_file(). (Could also use qsort(), but it could allocate memory.)
സ്ഥിതം ശൂന്യം mz_zip_reader_sort_central_dir_offsets_by_filename(mz_zip_archive *pZip)
{
  mz_zip_internal_state *pState = pZip->m_pState;
  സ്ഥിരം mz_zip_array *pCentral_dir_offsets = &pState->m_central_dir_offsets;
  സ്ഥിരം mz_zip_array *pCentral_dir = &pState->m_central_dir;
  mz_uint32 *pIndices = &MZ_ZIP_ARRAY_ELEMENT(&pState->m_sorted_central_dir_offsets, mz_uint32, 0);
  സ്ഥിരം പൂർണ്ണസംഖ്യ size = pZip->m_total_files;
  പൂർണ്ണസംഖ്യ start = (size - 2) >> 1, end;
  ആകുമ്പോൾ (start >= 0)
  {
    പൂർണ്ണസംഖ്യ child, വേര് = start;
    വേണ്ടി ( ; ; )
    {
      എങ്കിൽ ((child = (വേര് << 1) + 1) >= size)
        നിർത്തുക;
      child += (((child + 1) < size) && (mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[child], pIndices[child + 1])));
      എങ്കിൽ (!mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[വേര്], pIndices[child]))
        നിർത്തുക;
      MZ_SWAP_UINT32(pIndices[വേര്], pIndices[child]); വേര് = child;
    }
    start--;
  }

  end = size - 1;
  ആകുമ്പോൾ (end > 0)
  {
    പൂർണ്ണസംഖ്യ child, വേര് = 0;
    MZ_SWAP_UINT32(pIndices[end], pIndices[0]);
    വേണ്ടി ( ; ; )
    {
      എങ്കിൽ ((child = (വേര് << 1) + 1) >= end)
        നിർത്തുക;
      child += (((child + 1) < end) && mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[child], pIndices[child + 1]));
      എങ്കിൽ (!mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[വേര്], pIndices[child]))
        നിർത്തുക;
      MZ_SWAP_UINT32(pIndices[വേര്], pIndices[child]); വേര് = child;
    }
    end--;
  }
}

സ്ഥിതം mz_bool mz_zip_reader_read_central_dir(mz_zip_archive *pZip, mz_uint32 flags)
{
  mz_uint cdir_size, അക്കം_this_disk, cdir_disk_index;
  mz_uint64 cdir_ofs;
  mz_int64 cur_file_ofs;
  സ്ഥിരം mz_uint8 *p;
  mz_uint32 buf_u32[4096 / വലുപ്പം(mz_uint32)]; mz_uint8 *pBuf = (mz_uint8 *)buf_u32;
  mz_bool sort_central_dir = ((flags & MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY) == 0);
  // Basic sanity checks - reject files which are too small, and check the first 4 bytes of the file to make sure a local header is there.
  എങ്കിൽ (pZip->m_archive_size < MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE)
    തിരികെ MZ_FALSE;
  // Find the end of central directory record by scanning the file from the end towards the beginning.
  cur_file_ofs = MZ_MAX((mz_int64)pZip->m_archive_size - (mz_int64)വലുപ്പം(buf_u32), 0);
  വേണ്ടി ( ; ; )
  {
    പൂർണ്ണസംഖ്യ i, n = (പൂർണ്ണസംഖ്യ)MZ_MIN(വലുപ്പം(buf_u32), pZip->m_archive_size - cur_file_ofs);
    എങ്കിൽ (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, n) != (mz_uint)n)
      തിരികെ MZ_FALSE;
    വേണ്ടി (i = n - 4; i >= 0; --i)
      എങ്കിൽ (MZ_READ_LE32(pBuf + i) == MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIG)
        നിർത്തുക;
    എങ്കിൽ (i >= 0)
    {
      cur_file_ofs += i;
      നിർത്തുക;
    }
    എങ്കിൽ ((!cur_file_ofs) || ((pZip->m_archive_size - cur_file_ofs) >= (0xFFFF + MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE)))
      തിരികെ MZ_FALSE;
    cur_file_ofs = MZ_MAX(cur_file_ofs - (വലുപ്പം(buf_u32) - 3), 0);
  }
  // Read and verify the end of central directory record.
  എങ്കിൽ (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE) != MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE)
    തിരികെ MZ_FALSE;
  എങ്കിൽ ((MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_SIG_OFS) != MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIG) ||
      ((pZip->m_total_files = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_CDIR_TOTAL_ENTRIES_OFS)) != MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_CDIR_അക്കം_ENTRIES_ON_DISK_OFS)))
    തിരികെ MZ_FALSE;

  അക്കം_this_disk = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_അക്കം_THIS_DISK_OFS);
  cdir_disk_index = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_അക്കം_DISK_CDIR_OFS);
  എങ്കിൽ (((അക്കം_this_disk | cdir_disk_index) != 0) && ((അക്കം_this_disk != 1) || (cdir_disk_index != 1)))
    തിരികെ MZ_FALSE;

  എങ്കിൽ ((cdir_size = MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_CDIR_SIZE_OFS)) < pZip->m_total_files * MZ_ZIP_CENTRAL_DIR_HEADER_SIZE)
    തിരികെ MZ_FALSE;

  cdir_ofs = MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_CDIR_OFS_OFS);
  എങ്കിൽ ((cdir_ofs + (mz_uint64)cdir_size) > pZip->m_archive_size)
    തിരികെ MZ_FALSE;

  pZip->m_central_directory_file_ofs = cdir_ofs;

  എങ്കിൽ (pZip->m_total_files)
  {
     mz_uint i, n;

    // Read the entire central directory into a heap block, and allocate another heap block to hold the unsorted central dir file record offsets, and another to hold the sorted indices.
    എങ്കിൽ ((!mz_zip_array_resize(pZip, &pZip->m_pState->m_central_dir, cdir_size, MZ_FALSE)) ||
        (!mz_zip_array_resize(pZip, &pZip->m_pState->m_central_dir_offsets, pZip->m_total_files, MZ_FALSE)))
      തിരികെ MZ_FALSE;

    എങ്കിൽ (sort_central_dir)
    {
      എങ്കിൽ (!mz_zip_array_resize(pZip, &pZip->m_pState->m_sorted_central_dir_offsets, pZip->m_total_files, MZ_FALSE))
        തിരികെ MZ_FALSE;
    }

    എങ്കിൽ (pZip->m_pRead(pZip->m_pIO_opaque, cdir_ofs, pZip->m_pState->m_central_dir.m_p, cdir_size) != cdir_size)
      തിരികെ MZ_FALSE;

    // Now create an index into the central directory file records, do some basic sanity checking on each record, and check for zip64 entries (which are not yet supported).
    p = (സ്ഥിരം mz_uint8 *)pZip->m_pState->m_central_dir.m_p;
    വേണ്ടി (n = cdir_size, i = 0; i < pZip->m_total_files; ++i)
    {
      mz_uint total_header_size, comp_size, decomp_size, disk_index;
      എങ്കിൽ ((n < MZ_ZIP_CENTRAL_DIR_HEADER_SIZE) || (MZ_READ_LE32(p) != MZ_ZIP_CENTRAL_DIR_HEADER_SIG))
        തിരികെ MZ_FALSE;
      MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, i) = (mz_uint32)(p - (സ്ഥിരം mz_uint8 *)pZip->m_pState->m_central_dir.m_p);
      എങ്കിൽ (sort_central_dir)
        MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_sorted_central_dir_offsets, mz_uint32, i) = i;
      comp_size = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_SIZE_OFS);
      decomp_size = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_SIZE_OFS);
      എങ്കിൽ (((!MZ_READ_LE32(p + MZ_ZIP_CDH_METHOD_OFS)) && (decomp_size != comp_size)) || (decomp_size && !comp_size) || (decomp_size == 0xFFFFFFFF) || (comp_size == 0xFFFFFFFF))
        തിരികെ MZ_FALSE;
      disk_index = MZ_READ_LE16(p + MZ_ZIP_CDH_DISK_START_OFS);
      എങ്കിൽ ((disk_index != അക്കം_this_disk) && (disk_index != 1))
        തിരികെ MZ_FALSE;
      എങ്കിൽ (((mz_uint64)MZ_READ_LE32(p + MZ_ZIP_CDH_LOCAL_HEADER_OFS) + MZ_ZIP_LOCAL_DIR_HEADER_SIZE + comp_size) > pZip->m_archive_size)
        തിരികെ MZ_FALSE;
      എങ്കിൽ ((total_header_size = MZ_ZIP_CENTRAL_DIR_HEADER_SIZE + MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_EXTRA_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_COMMENT_LEN_OFS)) > n)
        തിരികെ MZ_FALSE;
      n -= total_header_size; p += total_header_size;
    }
  }

  എങ്കിൽ (sort_central_dir)
    mz_zip_reader_sort_central_dir_offsets_by_filename(pZip);

  തിരികെ MZ_TRUE;
}

mz_bool mz_zip_reader_init(mz_zip_archive *pZip, mz_uint64 size, mz_uint32 flags)
{
  എങ്കിൽ ((!pZip) || (!pZip->m_pRead))
    തിരികെ MZ_FALSE;
  എങ്കിൽ (!mz_zip_reader_init_internal(pZip, flags))
    തിരികെ MZ_FALSE;
  pZip->m_archive_size = size;
  എങ്കിൽ (!mz_zip_reader_read_central_dir(pZip, flags))
  {
    mz_zip_reader_end(pZip);
    തിരികെ MZ_FALSE;
  }
  തിരികെ MZ_TRUE;
}

സ്ഥിതം size_t mz_zip_mem_read_func(ശൂന്യം *pOpaque, mz_uint64 file_ofs, ശൂന്യം *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  size_t s = (file_ofs >= pZip->m_archive_size) ? 0 : (size_t)MZ_MIN(pZip->m_archive_size - file_ofs, n);
  memcpy(pBuf, (സ്ഥിരം mz_uint8 *)pZip->m_pState->m_pMem + file_ofs, s);
  തിരികെ s;
}

mz_bool mz_zip_reader_init_mem(mz_zip_archive *pZip, സ്ഥിരം ശൂന്യം *pMem, size_t size, mz_uint32 flags)
{
  എങ്കിൽ (!mz_zip_reader_init_internal(pZip, flags))
    തിരികെ MZ_FALSE;
  pZip->m_archive_size = size;
  pZip->m_pRead = mz_zip_mem_read_func;
  pZip->m_pIO_opaque = pZip;
#ifdef __cplusplus
  pZip->m_pState->m_pMem = const_cast<ശൂന്യം *>(pMem);
#അല്ലെങ്കിൽ
  pZip->m_pState->m_pMem = (ശൂന്യം *)pMem;
#endif
  pZip->m_pState->m_mem_size = size;
  എങ്കിൽ (!mz_zip_reader_read_central_dir(pZip, flags))
  {
    mz_zip_reader_end(pZip);
    തിരികെ MZ_FALSE;
  }
  തിരികെ MZ_TRUE;
}

#ifndef MINIZ_NO_STDIO
സ്ഥിതം size_t mz_zip_file_read_func(ശൂന്യം *pOpaque, mz_uint64 file_ofs, ശൂന്യം *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_int64 cur_ofs = MZ_FTELL64(pZip->m_pState->m_pFile);
  എങ്കിൽ (((mz_int64)file_ofs < 0) || (((cur_ofs != (mz_int64)file_ofs)) && (MZ_FSEEK64(pZip->m_pState->m_pFile, (mz_int64)file_ofs, SEEK_SET))))
    തിരികെ 0;
  തിരികെ MZ_FREAD(pBuf, 1, n, pZip->m_pState->m_pFile);
}

mz_bool mz_zip_reader_init_file(mz_zip_archive *pZip, സ്ഥിരം അക്ഷരം *pFilename, mz_uint32 flags)
{
  mz_uint64 file_size;
  MZ_FILE *pFile = MZ_FOPEN(pFilename, "rb");
  എങ്കിൽ (!pFile)
    തിരികെ MZ_FALSE;
  എങ്കിൽ (MZ_FSEEK64(pFile, 0, SEEK_END))
  {
    MZ_FCLOSE(pFile);
    തിരികെ MZ_FALSE;
  }
  file_size = MZ_FTELL64(pFile);
  എങ്കിൽ (!mz_zip_reader_init_internal(pZip, flags))
  {
    MZ_FCLOSE(pFile);
    തിരികെ MZ_FALSE;
  }
  pZip->m_pRead = mz_zip_file_read_func;
  pZip->m_pIO_opaque = pZip;
  pZip->m_pState->m_pFile = pFile;
  pZip->m_archive_size = file_size;
  എങ്കിൽ (!mz_zip_reader_read_central_dir(pZip, flags))
  {
    mz_zip_reader_end(pZip);
    തിരികെ MZ_FALSE;
  }
  തിരികെ MZ_TRUE;
}
#endif // #ifndef MINIZ_NO_STDIO

mz_uint mz_zip_reader_get_അക്കം_files(mz_zip_archive *pZip)
{
  തിരികെ pZip ? pZip->m_total_files : 0;
}

സ്ഥിതം MZ_FORCEINLINE സ്ഥിരം mz_uint8 *mz_zip_reader_get_cdh(mz_zip_archive *pZip, mz_uint file_index)
{
  എങ്കിൽ ((!pZip) || (!pZip->m_pState) || (file_index >= pZip->m_total_files) || (pZip->m_zip_mode != MZ_ZIP_MODE_READING))
    തിരികെ ശൂന്യ;
  തിരികെ &MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_index));
}

mz_bool mz_zip_reader_is_file_encrypted(mz_zip_archive *pZip, mz_uint file_index)
{
  mz_uint m_bit_flag;
  സ്ഥിരം mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_index);
  എങ്കിൽ (!p)
    തിരികെ MZ_FALSE;
  m_bit_flag = MZ_READ_LE16(p + MZ_ZIP_CDH_BIT_FLAG_OFS);
  തിരികെ (m_bit_flag & 1);
}

mz_bool mz_zip_reader_is_file_a_directory(mz_zip_archive *pZip, mz_uint file_index)
{
  mz_uint filename_len, external_attr;
  സ്ഥിരം mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_index);
  എങ്കിൽ (!p)
    തിരികെ MZ_FALSE;

  // First see if the filename ends with a '/' character.
  filename_len = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  എങ്കിൽ (filename_len)
  {
    എങ്കിൽ (*(p + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE + filename_len - 1) == '/')
      തിരികെ MZ_TRUE;
  }

  // Bugfix: This code was also checking if the internal attribute was non-zero, which wasn't correct.
  // Most/all zip writers (hopefully) set DOS file/directory attributes in the low 16-bits, so check for the DOS directory flag and ignore the source OS ID in the created by field.
  // FIXME: Remove this check? Is it necessary - we already check the filename.
  external_attr = MZ_READ_LE32(p + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS);
  എങ്കിൽ ((external_attr & 0x10) != 0)
    തിരികെ MZ_TRUE;

  തിരികെ MZ_FALSE;
}

mz_bool mz_zip_reader_file_stat(mz_zip_archive *pZip, mz_uint file_index, mz_zip_archive_file_stat *pStat)
{
  mz_uint n;
  സ്ഥിരം mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_index);
  എങ്കിൽ ((!p) || (!pStat))
    തിരികെ MZ_FALSE;

  // Unpack the central directory record.
  pStat->m_file_index = file_index;
  pStat->m_central_dir_ofs = MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_index);
  pStat->m_version_made_by = MZ_READ_LE16(p + MZ_ZIP_CDH_VERSION_MADE_BY_OFS);
  pStat->m_version_needed = MZ_READ_LE16(p + MZ_ZIP_CDH_VERSION_NEEDED_OFS);
  pStat->m_bit_flag = MZ_READ_LE16(p + MZ_ZIP_CDH_BIT_FLAG_OFS);
  pStat->m_method = MZ_READ_LE16(p + MZ_ZIP_CDH_METHOD_OFS);
#ifndef MINIZ_NO_TIME
  pStat->m_time = mz_zip_dos_to_time_t(MZ_READ_LE16(p + MZ_ZIP_CDH_FILE_TIME_OFS), MZ_READ_LE16(p + MZ_ZIP_CDH_FILE_DATE_OFS));
#endif
  pStat->m_crc32 = MZ_READ_LE32(p + MZ_ZIP_CDH_CRC32_OFS);
  pStat->m_comp_size = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_SIZE_OFS);
  pStat->m_uncomp_size = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_SIZE_OFS);
  pStat->m_internal_attr = MZ_READ_LE16(p + MZ_ZIP_CDH_INTERNAL_ATTR_OFS);
  pStat->m_external_attr = MZ_READ_LE32(p + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS);
  pStat->m_local_header_ofs = MZ_READ_LE32(p + MZ_ZIP_CDH_LOCAL_HEADER_OFS);

  // Copy as much of the filename and comment as possible.
  n = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS); n = MZ_MIN(n, MZ_ZIP_MAX_ARCHIVE_FILENAME_SIZE - 1);
  memcpy(pStat->m_filename, p + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE, n); pStat->m_filename[n] = '\0';

  n = MZ_READ_LE16(p + MZ_ZIP_CDH_COMMENT_LEN_OFS); n = MZ_MIN(n, MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_SIZE - 1);
  pStat->m_comment_size = n;
  memcpy(pStat->m_comment, p + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE + MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_EXTRA_LEN_OFS), n); pStat->m_comment[n] = '\0';

  തിരികെ MZ_TRUE;
}

mz_uint mz_zip_reader_get_filename(mz_zip_archive *pZip, mz_uint file_index, അക്ഷരം *pFilename, mz_uint filename_buf_size)
{
  mz_uint n;
  സ്ഥിരം mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_index);
  എങ്കിൽ (!p) { എങ്കിൽ (filename_buf_size) pFilename[0] = '\0'; തിരികെ 0; }
  n = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  എങ്കിൽ (filename_buf_size)
  {
    n = MZ_MIN(n, filename_buf_size - 1);
    memcpy(pFilename, p + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE, n);
    pFilename[n] = '\0';
  }
  തിരികെ n + 1;
}

സ്ഥിതം MZ_FORCEINLINE mz_bool mz_zip_reader_string_equal(സ്ഥിരം അക്ഷരം *pA, സ്ഥിരം അക്ഷരം *pB, mz_uint len, mz_uint flags)
{
  mz_uint i;
  എങ്കിൽ (flags & MZ_ZIP_FLAG_CASE_SENSITIVE)
    തിരികെ 0 == memcmp(pA, pB, len);
  വേണ്ടി (i = 0; i < len; ++i)
    എങ്കിൽ (MZ_TOLOWER(pA[i]) != MZ_TOLOWER(pB[i]))
      തിരികെ MZ_FALSE;
  തിരികെ MZ_TRUE;
}

സ്ഥിതം MZ_FORCEINLINE പൂർണ്ണസംഖ്യ mz_zip_reader_filename_compare(സ്ഥിരം mz_zip_array *pCentral_dir_array, സ്ഥിരം mz_zip_array *pCentral_dir_offsets, mz_uint l_index, സ്ഥിരം അക്ഷരം *pR, mz_uint r_len)
{
  സ്ഥിരം mz_uint8 *pL = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, l_index)), *pE;
  mz_uint l_len = MZ_READ_LE16(pL + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  mz_uint8 l = 0, r = 0;
  pL += MZ_ZIP_CENTRAL_DIR_HEADER_SIZE;
  pE = pL + MZ_MIN(l_len, r_len);
  ആകുമ്പോൾ (pL < pE)
  {
    എങ്കിൽ ((l = MZ_TOLOWER(*pL)) != (r = MZ_TOLOWER(*pR)))
      നിർത്തുക;
    pL++; pR++;
  }
  തിരികെ (pL == pE) ? (പൂർണ്ണസംഖ്യ)(l_len - r_len) : (l - r);
}

സ്ഥിതം പൂർണ്ണസംഖ്യ mz_zip_reader_locate_file_ദ്വിമാന_തിരയൽ(mz_zip_archive *pZip, സ്ഥിരം അക്ഷരം *pFilename)
{
  mz_zip_internal_state *pState = pZip->m_pState;
  സ്ഥിരം mz_zip_array *pCentral_dir_offsets = &pState->m_central_dir_offsets;
  സ്ഥിരം mz_zip_array *pCentral_dir = &pState->m_central_dir;
  mz_uint32 *pIndices = &MZ_ZIP_ARRAY_ELEMENT(&pState->m_sorted_central_dir_offsets, mz_uint32, 0);
  സ്ഥിരം പൂർണ്ണസംഖ്യ size = pZip->m_total_files;
  സ്ഥിരം mz_uint filename_len = (mz_uint)strlen(pFilename);
  പൂർണ്ണസംഖ്യ l = 0, h = size - 1;
  ആകുമ്പോൾ (l <= h)
  {
    പൂർണ്ണസംഖ്യ m = (l + h) >> 1, file_index = pIndices[m], comp = mz_zip_reader_filename_compare(pCentral_dir, pCentral_dir_offsets, file_index, pFilename, filename_len);
    എങ്കിൽ (!comp)
      തിരികെ file_index;
    അല്ലെങ്കിൽ എങ്കിൽ (comp < 0)
      l = m + 1;
    അല്ലെങ്കിൽ
      h = m - 1;
  }
  തിരികെ -1;
}

പൂർണ്ണസംഖ്യ mz_zip_reader_locate_file(mz_zip_archive *pZip, സ്ഥിരം അക്ഷരം *pName, സ്ഥിരം അക്ഷരം *pComment, mz_uint flags)
{
  mz_uint file_index; size_t name_len, comment_len;
  എങ്കിൽ ((!pZip) || (!pZip->m_pState) || (!pName) || (pZip->m_zip_mode != MZ_ZIP_MODE_READING))
    തിരികെ -1;
  എങ്കിൽ (((flags & (MZ_ZIP_FLAG_IGNORE_PATH | MZ_ZIP_FLAG_CASE_SENSITIVE)) == 0) && (!pComment) && (pZip->m_pState->m_sorted_central_dir_offsets.m_size))
    തിരികെ mz_zip_reader_locate_file_ദ്വിമാന_തിരയൽ(pZip, pName);
  name_len = strlen(pName); എങ്കിൽ (name_len > 0xFFFF) തിരികെ -1;
  comment_len = pComment ? strlen(pComment) : 0; എങ്കിൽ (comment_len > 0xFFFF) തിരികെ -1;
  വേണ്ടി (file_index = 0; file_index < pZip->m_total_files; file_index++)
  {
    സ്ഥിരം mz_uint8 *pHeader = &MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_index));
    mz_uint filename_len = MZ_READ_LE16(pHeader + MZ_ZIP_CDH_FILENAME_LEN_OFS);
    സ്ഥിരം അക്ഷരം *pFilename = (സ്ഥിരം അക്ഷരം *)pHeader + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE;
    എങ്കിൽ (filename_len < name_len)
      തുടരുക;
    എങ്കിൽ (comment_len)
    {
      mz_uint file_extra_len = MZ_READ_LE16(pHeader + MZ_ZIP_CDH_EXTRA_LEN_OFS), file_comment_len = MZ_READ_LE16(pHeader + MZ_ZIP_CDH_COMMENT_LEN_OFS);
      സ്ഥിരം അക്ഷരം *pFile_comment = pFilename + filename_len + file_extra_len;
      എങ്കിൽ ((file_comment_len != comment_len) || (!mz_zip_reader_string_equal(pComment, pFile_comment, file_comment_len, flags)))
        തുടരുക;
    }
    എങ്കിൽ ((flags & MZ_ZIP_FLAG_IGNORE_PATH) && (filename_len))
    {
      പൂർണ്ണസംഖ്യ ofs = filename_len - 1;
      ചെയ്യുക
      {
        എങ്കിൽ ((pFilename[ofs] == '/') || (pFilename[ofs] == '\\') || (pFilename[ofs] == ':'))
          നിർത്തുക;
      } ആകുമ്പോൾ (--ofs >= 0);
      ofs++;
      pFilename += ofs; filename_len -= ofs;
    }
    എങ്കിൽ ((filename_len == name_len) && (mz_zip_reader_string_equal(pName, pFilename, filename_len, flags)))
      തിരികെ file_index;
  }
  തിരികെ -1;
}

mz_bool mz_zip_reader_extract_to_mem_no_alloc(mz_zip_archive *pZip, mz_uint file_index, ശൂന്യം *pBuf, size_t buf_size, mz_uint flags, ശൂന്യം *pUser_read_buf, size_t user_read_buf_size)
{
  പൂർണ്ണസംഖ്യ status = TINFL_STATUS_DONE;
  mz_uint64 needed_size, cur_file_ofs, comp_remaining, out_buf_ofs = 0, read_buf_size, read_buf_ofs = 0, read_buf_avail;
  mz_zip_archive_file_stat file_stat;
  ശൂന്യം *pRead_buf;
  mz_uint32 local_header_u32[(MZ_ZIP_LOCAL_DIR_HEADER_SIZE + വലുപ്പം(mz_uint32) - 1) / വലുപ്പം(mz_uint32)]; mz_uint8 *pLocal_header = (mz_uint8 *)local_header_u32;
  tinfl_decompressor inflator;

  എങ്കിൽ ((buf_size) && (!pBuf))
    തിരികെ MZ_FALSE;

  എങ്കിൽ (!mz_zip_reader_file_stat(pZip, file_index, &file_stat))
    തിരികെ MZ_FALSE;

  // Empty file, or a directory (but not always a directory - I've seen odd zips with directories that have compressed data which inflates to 0 bytes)
  എങ്കിൽ (!file_stat.m_comp_size)
    തിരികെ MZ_TRUE;

  // Entry is a subdirectory (I've seen old zips with dir entries which have compressed deflate data which inflates to 0 bytes, but these entries claim to uncompress to 512 bytes in the headers).
  // I'm torn how to handle this case - should it fail instead?
  എങ്കിൽ (mz_zip_reader_is_file_a_directory(pZip, file_index))
    തിരികെ MZ_TRUE;

  // Encryption and patch files are not supported.
  എങ്കിൽ (file_stat.m_bit_flag & (1 | 32))
    തിരികെ MZ_FALSE;

  // This function only supports stored and deflate.
  എങ്കിൽ ((!(flags & MZ_ZIP_FLAG_COMPRESSED_DATA)) && (file_stat.m_method != 0) && (file_stat.m_method != MZ_DEFLATED))
    തിരികെ MZ_FALSE;

  // Ensure supplied output buffer is large enough.
  needed_size = (flags & MZ_ZIP_FLAG_COMPRESSED_DATA) ? file_stat.m_comp_size : file_stat.m_uncomp_size;
  എങ്കിൽ (buf_size < needed_size)
    തിരികെ MZ_FALSE;

  // Read and parse the local directory entry.
  cur_file_ofs = file_stat.m_local_header_ofs;
  എങ്കിൽ (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pLocal_header, MZ_ZIP_LOCAL_DIR_HEADER_SIZE) != MZ_ZIP_LOCAL_DIR_HEADER_SIZE)
    തിരികെ MZ_FALSE;
  എങ്കിൽ (MZ_READ_LE32(pLocal_header) != MZ_ZIP_LOCAL_DIR_HEADER_SIG)
    തിരികെ MZ_FALSE;

  cur_file_ofs += MZ_ZIP_LOCAL_DIR_HEADER_SIZE + MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  എങ്കിൽ ((cur_file_ofs + file_stat.m_comp_size) > pZip->m_archive_size)
    തിരികെ MZ_FALSE;

  എങ്കിൽ ((flags & MZ_ZIP_FLAG_COMPRESSED_DATA) || (!file_stat.m_method))
  {
    // The file is stored or the caller has requested the compressed data.
    എങ്കിൽ (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, (size_t)needed_size) != needed_size)
      തിരികെ MZ_FALSE;
    തിരികെ ((flags & MZ_ZIP_FLAG_COMPRESSED_DATA) != 0) || (mz_crc32(MZ_CRC32_INIT, (സ്ഥിരം mz_uint8 *)pBuf, (size_t)file_stat.m_uncomp_size) == file_stat.m_crc32);
  }

  // Decompress the file either directly from memory or from a file input buffer.
  tinfl_init(&inflator);

  എങ്കിൽ (pZip->m_pState->m_pMem)
  {
    // Read directly from the archive in memory.
    pRead_buf = (mz_uint8 *)pZip->m_pState->m_pMem + cur_file_ofs;
    read_buf_size = read_buf_avail = file_stat.m_comp_size;
    comp_remaining = 0;
  }
  അല്ലെങ്കിൽ എങ്കിൽ (pUser_read_buf)
  {
    // Use a user provided read buffer.
    എങ്കിൽ (!user_read_buf_size)
      തിരികെ MZ_FALSE;
    pRead_buf = (mz_uint8 *)pUser_read_buf;
    read_buf_size = user_read_buf_size;
    read_buf_avail = 0;
    comp_remaining = file_stat.m_comp_size;
  }
  അല്ലെങ്കിൽ
  {
    // Temporarily allocate a read buffer.
    read_buf_size = MZ_MIN(file_stat.m_comp_size, MZ_ZIP_MAX_IO_BUF_SIZE);
#ifdef _MSC_VER
    എങ്കിൽ (((0, വലുപ്പം(size_t) == വലുപ്പം(mz_uint32))) && (read_buf_size > 0x7FFFFFFF))
#അല്ലെങ്കിൽ
    എങ്കിൽ (((വലുപ്പം(size_t) == വലുപ്പം(mz_uint32))) && (read_buf_size > 0x7FFFFFFF))
#endif
      തിരികെ MZ_FALSE;
    എങ്കിൽ (ശൂന്യ == (pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)read_buf_size)))
      തിരികെ MZ_FALSE;
    read_buf_avail = 0;
    comp_remaining = file_stat.m_comp_size;
  }

  ചെയ്യുക
  {
    size_t in_buf_size, out_buf_size = (size_t)(file_stat.m_uncomp_size - out_buf_ofs);
    എങ്കിൽ ((!read_buf_avail) && (!pZip->m_pState->m_pMem))
    {
      read_buf_avail = MZ_MIN(read_buf_size, comp_remaining);
      എങ്കിൽ (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
      {
        status = TINFL_STATUS_FAILED;
        നിർത്തുക;
      }
      cur_file_ofs += read_buf_avail;
      comp_remaining -= read_buf_avail;
      read_buf_ofs = 0;
    }
    in_buf_size = (size_t)read_buf_avail;
    status = tinfl_decompress(&inflator, (mz_uint8 *)pRead_buf + read_buf_ofs, &in_buf_size, (mz_uint8 *)pBuf, (mz_uint8 *)pBuf + out_buf_ofs, &out_buf_size, TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF | (comp_remaining ? TINFL_FLAG_HAS_MORE_നിവേശം : 0));
    read_buf_avail -= in_buf_size;
    read_buf_ofs += in_buf_size;
    out_buf_ofs += out_buf_size;
  } ആകുമ്പോൾ (status == TINFL_STATUS_NEEDS_MORE_നിവേശം);

  എങ്കിൽ (status == TINFL_STATUS_DONE)
  {
    // Make sure the entire file was decompressed, and check its CRC.
    എങ്കിൽ ((out_buf_ofs != file_stat.m_uncomp_size) || (mz_crc32(MZ_CRC32_INIT, (സ്ഥിരം mz_uint8 *)pBuf, (size_t)file_stat.m_uncomp_size) != file_stat.m_crc32))
      status = TINFL_STATUS_FAILED;
  }

  എങ്കിൽ ((!pZip->m_pState->m_pMem) && (!pUser_read_buf))
    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);

  തിരികെ status == TINFL_STATUS_DONE;
}

mz_bool mz_zip_reader_extract_file_to_mem_no_alloc(mz_zip_archive *pZip, സ്ഥിരം അക്ഷരം *pFilename, ശൂന്യം *pBuf, size_t buf_size, mz_uint flags, ശൂന്യം *pUser_read_buf, size_t user_read_buf_size)
{
  പൂർണ്ണസംഖ്യ file_index = mz_zip_reader_locate_file(pZip, pFilename, ശൂന്യ, flags);
  എങ്കിൽ (file_index < 0)
    തിരികെ MZ_FALSE;
  തിരികെ mz_zip_reader_extract_to_mem_no_alloc(pZip, file_index, pBuf, buf_size, flags, pUser_read_buf, user_read_buf_size);
}

mz_bool mz_zip_reader_extract_to_mem(mz_zip_archive *pZip, mz_uint file_index, ശൂന്യം *pBuf, size_t buf_size, mz_uint flags)
{
  തിരികെ mz_zip_reader_extract_to_mem_no_alloc(pZip, file_index, pBuf, buf_size, flags, ശൂന്യ, 0);
}

mz_bool mz_zip_reader_extract_file_to_mem(mz_zip_archive *pZip, സ്ഥിരം അക്ഷരം *pFilename, ശൂന്യം *pBuf, size_t buf_size, mz_uint flags)
{
  തിരികെ mz_zip_reader_extract_file_to_mem_no_alloc(pZip, pFilename, pBuf, buf_size, flags, ശൂന്യ, 0);
}

ശൂന്യം *mz_zip_reader_extract_to_heap(mz_zip_archive *pZip, mz_uint file_index, size_t *pSize, mz_uint flags)
{
  mz_uint64 comp_size, uncomp_size, alloc_size;
  സ്ഥിരം mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_index);
  ശൂന്യം *pBuf;

  എങ്കിൽ (pSize)
    *pSize = 0;
  എങ്കിൽ (!p)
    തിരികെ ശൂന്യ;

  comp_size = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_SIZE_OFS);
  uncomp_size = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_SIZE_OFS);

  alloc_size = (flags & MZ_ZIP_FLAG_COMPRESSED_DATA) ? comp_size : uncomp_size;
#ifdef _MSC_VER
  എങ്കിൽ (((0, വലുപ്പം(size_t) == വലുപ്പം(mz_uint32))) && (alloc_size > 0x7FFFFFFF))
#അല്ലെങ്കിൽ
  എങ്കിൽ (((വലുപ്പം(size_t) == വലുപ്പം(mz_uint32))) && (alloc_size > 0x7FFFFFFF))
#endif
    തിരികെ ശൂന്യ;
  എങ്കിൽ (ശൂന്യ == (pBuf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)alloc_size)))
    തിരികെ ശൂന്യ;

  എങ്കിൽ (!mz_zip_reader_extract_to_mem(pZip, file_index, pBuf, (size_t)alloc_size, flags))
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
    തിരികെ ശൂന്യ;
  }

  എങ്കിൽ (pSize) *pSize = (size_t)alloc_size;
  തിരികെ pBuf;
}

ശൂന്യം *mz_zip_reader_extract_file_to_heap(mz_zip_archive *pZip, സ്ഥിരം അക്ഷരം *pFilename, size_t *pSize, mz_uint flags)
{
  പൂർണ്ണസംഖ്യ file_index = mz_zip_reader_locate_file(pZip, pFilename, ശൂന്യ, flags);
  എങ്കിൽ (file_index < 0)
  {
    എങ്കിൽ (pSize) *pSize = 0;
    തിരികെ MZ_FALSE;
  }
  തിരികെ mz_zip_reader_extract_to_heap(pZip, file_index, pSize, flags);
}

mz_bool mz_zip_reader_extract_to_callback(mz_zip_archive *pZip, mz_uint file_index, mz_file_write_func pCallback, ശൂന്യം *pOpaque, mz_uint flags)
{
  പൂർണ്ണസംഖ്യ status = TINFL_STATUS_DONE; mz_uint file_crc32 = MZ_CRC32_INIT;
  mz_uint64 read_buf_size, read_buf_ofs = 0, read_buf_avail, comp_remaining, out_buf_ofs = 0, cur_file_ofs;
  mz_zip_archive_file_stat file_stat;
  ശൂന്യം *pRead_buf = ശൂന്യ; ശൂന്യം *pWrite_buf = ശൂന്യ;
  mz_uint32 local_header_u32[(MZ_ZIP_LOCAL_DIR_HEADER_SIZE + വലുപ്പം(mz_uint32) - 1) / വലുപ്പം(mz_uint32)]; mz_uint8 *pLocal_header = (mz_uint8 *)local_header_u32;

  എങ്കിൽ (!mz_zip_reader_file_stat(pZip, file_index, &file_stat))
    തിരികെ MZ_FALSE;

  // Empty file, or a directory (but not always a directory - I've seen odd zips with directories that have compressed data which inflates to 0 bytes)
  എങ്കിൽ (!file_stat.m_comp_size)
    തിരികെ MZ_TRUE;

  // Entry is a subdirectory (I've seen old zips with dir entries which have compressed deflate data which inflates to 0 bytes, but these entries claim to uncompress to 512 bytes in the headers).
  // I'm torn how to handle this case - should it fail instead?
  എങ്കിൽ (mz_zip_reader_is_file_a_directory(pZip, file_index))
    തിരികെ MZ_TRUE;

  // Encryption and patch files are not supported.
  എങ്കിൽ (file_stat.m_bit_flag & (1 | 32))
    തിരികെ MZ_FALSE;

  // This function only supports stored and deflate.
  എങ്കിൽ ((!(flags & MZ_ZIP_FLAG_COMPRESSED_DATA)) && (file_stat.m_method != 0) && (file_stat.m_method != MZ_DEFLATED))
    തിരികെ MZ_FALSE;

  // Read and parse the local directory entry.
  cur_file_ofs = file_stat.m_local_header_ofs;
  എങ്കിൽ (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pLocal_header, MZ_ZIP_LOCAL_DIR_HEADER_SIZE) != MZ_ZIP_LOCAL_DIR_HEADER_SIZE)
    തിരികെ MZ_FALSE;
  എങ്കിൽ (MZ_READ_LE32(pLocal_header) != MZ_ZIP_LOCAL_DIR_HEADER_SIG)
    തിരികെ MZ_FALSE;

  cur_file_ofs += MZ_ZIP_LOCAL_DIR_HEADER_SIZE + MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  എങ്കിൽ ((cur_file_ofs + file_stat.m_comp_size) > pZip->m_archive_size)
    തിരികെ MZ_FALSE;

  // Decompress the file either directly from memory or from a file input buffer.
  എങ്കിൽ (pZip->m_pState->m_pMem)
  {
    pRead_buf = (mz_uint8 *)pZip->m_pState->m_pMem + cur_file_ofs;
    read_buf_size = read_buf_avail = file_stat.m_comp_size;
    comp_remaining = 0;
  }
  അല്ലെങ്കിൽ
  {
    read_buf_size = MZ_MIN(file_stat.m_comp_size, MZ_ZIP_MAX_IO_BUF_SIZE);
    എങ്കിൽ (ശൂന്യ == (pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)read_buf_size)))
      തിരികെ MZ_FALSE;
    read_buf_avail = 0;
    comp_remaining = file_stat.m_comp_size;
  }

  എങ്കിൽ ((flags & MZ_ZIP_FLAG_COMPRESSED_DATA) || (!file_stat.m_method))
  {
    // The file is stored or the caller has requested the compressed data.
    എങ്കിൽ (pZip->m_pState->m_pMem)
    {
#ifdef _MSC_VER
      എങ്കിൽ (((0, വലുപ്പം(size_t) == വലുപ്പം(mz_uint32))) && (file_stat.m_comp_size > 0xFFFFFFFF))
#അല്ലെങ്കിൽ
      എങ്കിൽ (((വലുപ്പം(size_t) == വലുപ്പം(mz_uint32))) && (file_stat.m_comp_size > 0xFFFFFFFF))
#endif
        തിരികെ MZ_FALSE;
      എങ്കിൽ (pCallback(pOpaque, out_buf_ofs, pRead_buf, (size_t)file_stat.m_comp_size) != file_stat.m_comp_size)
        status = TINFL_STATUS_FAILED;
      അല്ലെങ്കിൽ എങ്കിൽ (!(flags & MZ_ZIP_FLAG_COMPRESSED_DATA))
        file_crc32 = (mz_uint32)mz_crc32(file_crc32, (സ്ഥിരം mz_uint8 *)pRead_buf, (size_t)file_stat.m_comp_size);
      cur_file_ofs += file_stat.m_comp_size;
      out_buf_ofs += file_stat.m_comp_size;
      comp_remaining = 0;
    }
    അല്ലെങ്കിൽ
    {
      ആകുമ്പോൾ (comp_remaining)
      {
        read_buf_avail = MZ_MIN(read_buf_size, comp_remaining);
        എങ്കിൽ (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
        {
          status = TINFL_STATUS_FAILED;
          നിർത്തുക;
        }

        എങ്കിൽ (!(flags & MZ_ZIP_FLAG_COMPRESSED_DATA))
          file_crc32 = (mz_uint32)mz_crc32(file_crc32, (സ്ഥിരം mz_uint8 *)pRead_buf, (size_t)read_buf_avail);

        എങ്കിൽ (pCallback(pOpaque, out_buf_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
        {
          status = TINFL_STATUS_FAILED;
          നിർത്തുക;
        }
        cur_file_ofs += read_buf_avail;
        out_buf_ofs += read_buf_avail;
        comp_remaining -= read_buf_avail;
      }
    }
  }
  അല്ലെങ്കിൽ
  {
    tinfl_decompressor inflator;
    tinfl_init(&inflator);

    എങ്കിൽ (ശൂന്യ == (pWrite_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, TINFL_LZ_DICT_SIZE)))
      status = TINFL_STATUS_FAILED;
    അല്ലെങ്കിൽ
    {
      ചെയ്യുക
      {
        mz_uint8 *pWrite_buf_cur = (mz_uint8 *)pWrite_buf + (out_buf_ofs & (TINFL_LZ_DICT_SIZE - 1));
        size_t in_buf_size, out_buf_size = TINFL_LZ_DICT_SIZE - (out_buf_ofs & (TINFL_LZ_DICT_SIZE - 1));
        എങ്കിൽ ((!read_buf_avail) && (!pZip->m_pState->m_pMem))
        {
          read_buf_avail = MZ_MIN(read_buf_size, comp_remaining);
          എങ്കിൽ (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
          {
            status = TINFL_STATUS_FAILED;
            നിർത്തുക;
          }
          cur_file_ofs += read_buf_avail;
          comp_remaining -= read_buf_avail;
          read_buf_ofs = 0;
        }

        in_buf_size = (size_t)read_buf_avail;
        status = tinfl_decompress(&inflator, (സ്ഥിരം mz_uint8 *)pRead_buf + read_buf_ofs, &in_buf_size, (mz_uint8 *)pWrite_buf, pWrite_buf_cur, &out_buf_size, comp_remaining ? TINFL_FLAG_HAS_MORE_നിവേശം : 0);
        read_buf_avail -= in_buf_size;
        read_buf_ofs += in_buf_size;

        എങ്കിൽ (out_buf_size)
        {
          എങ്കിൽ (pCallback(pOpaque, out_buf_ofs, pWrite_buf_cur, out_buf_size) != out_buf_size)
          {
            status = TINFL_STATUS_FAILED;
            നിർത്തുക;
          }
          file_crc32 = (mz_uint32)mz_crc32(file_crc32, pWrite_buf_cur, out_buf_size);
          എങ്കിൽ ((out_buf_ofs += out_buf_size) > file_stat.m_uncomp_size)
          {
            status = TINFL_STATUS_FAILED;
            നിർത്തുക;
          }
        }
      } ആകുമ്പോൾ ((status == TINFL_STATUS_NEEDS_MORE_നിവേശം) || (status == TINFL_STATUS_HAS_MORE_OUTPUT));
    }
  }

  എങ്കിൽ ((status == TINFL_STATUS_DONE) && (!(flags & MZ_ZIP_FLAG_COMPRESSED_DATA)))
  {
    // Make sure the entire file was decompressed, and check its CRC.
    എങ്കിൽ ((out_buf_ofs != file_stat.m_uncomp_size) || (file_crc32 != file_stat.m_crc32))
      status = TINFL_STATUS_FAILED;
  }

  എങ്കിൽ (!pZip->m_pState->m_pMem)
    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
  എങ്കിൽ (pWrite_buf)
    pZip->m_pFree(pZip->m_pAlloc_opaque, pWrite_buf);

  തിരികെ status == TINFL_STATUS_DONE;
}

mz_bool mz_zip_reader_extract_file_to_callback(mz_zip_archive *pZip, സ്ഥിരം അക്ഷരം *pFilename, mz_file_write_func pCallback, ശൂന്യം *pOpaque, mz_uint flags)
{
  പൂർണ്ണസംഖ്യ file_index = mz_zip_reader_locate_file(pZip, pFilename, ശൂന്യ, flags);
  എങ്കിൽ (file_index < 0)
    തിരികെ MZ_FALSE;
  തിരികെ mz_zip_reader_extract_to_callback(pZip, file_index, pCallback, pOpaque, flags);
}

#ifndef MINIZ_NO_STDIO
സ്ഥിതം size_t mz_zip_file_write_callback(ശൂന്യം *pOpaque, mz_uint64 ofs, സ്ഥിരം ശൂന്യം *pBuf, size_t n)
{
  (ശൂന്യം)ofs; തിരികെ MZ_FWRITE(pBuf, 1, n, (MZ_FILE*)pOpaque);
}

mz_bool mz_zip_reader_extract_to_file(mz_zip_archive *pZip, mz_uint file_index, സ്ഥിരം അക്ഷരം *pDst_filename, mz_uint flags)
{
  mz_bool status;
  mz_zip_archive_file_stat file_stat;
  MZ_FILE *pFile;
  എങ്കിൽ (!mz_zip_reader_file_stat(pZip, file_index, &file_stat))
    തിരികെ MZ_FALSE;
  pFile = MZ_FOPEN(pDst_filename, "wb");
  എങ്കിൽ (!pFile)
    തിരികെ MZ_FALSE;
  status = mz_zip_reader_extract_to_callback(pZip, file_index, mz_zip_file_write_callback, pFile, flags);
  എങ്കിൽ (MZ_FCLOSE(pFile) == EOF)
    തിരികെ MZ_FALSE;
#ifndef MINIZ_NO_TIME
  എങ്കിൽ (status)
    mz_zip_set_file_times(pDst_filename, file_stat.m_time, file_stat.m_time);
#endif
  തിരികെ status;
}
#endif // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_reader_end(mz_zip_archive *pZip)
{
  എങ്കിൽ ((!pZip) || (!pZip->m_pState) || (!pZip->m_pAlloc) || (!pZip->m_pFree) || (pZip->m_zip_mode != MZ_ZIP_MODE_READING))
    തിരികെ MZ_FALSE;

  എങ്കിൽ (pZip->m_pState)
  {
    mz_zip_internal_state *pState = pZip->m_pState; pZip->m_pState = ശൂന്യ;
    mz_zip_array_clear(pZip, &pState->m_central_dir);
    mz_zip_array_clear(pZip, &pState->m_central_dir_offsets);
    mz_zip_array_clear(pZip, &pState->m_sorted_central_dir_offsets);

#ifndef MINIZ_NO_STDIO
    എങ്കിൽ (pState->m_pFile)
    {
      MZ_FCLOSE(pState->m_pFile);
      pState->m_pFile = ശൂന്യ;
    }
#endif // #ifndef MINIZ_NO_STDIO

    pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
  }
  pZip->m_zip_mode = MZ_ZIP_MODE_INVALID;

  തിരികെ MZ_TRUE;
}

#ifndef MINIZ_NO_STDIO
mz_bool mz_zip_reader_extract_file_to_file(mz_zip_archive *pZip, സ്ഥിരം അക്ഷരം *pArchive_filename, സ്ഥിരം അക്ഷരം *pDst_filename, mz_uint flags)
{
  പൂർണ്ണസംഖ്യ file_index = mz_zip_reader_locate_file(pZip, pArchive_filename, ശൂന്യ, flags);
  എങ്കിൽ (file_index < 0)
    തിരികെ MZ_FALSE;
  തിരികെ mz_zip_reader_extract_to_file(pZip, file_index, pDst_filename, flags);
}
#endif

// ------------------- .ZIP archive writing

#ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

സ്ഥിതം ശൂന്യം mz_write_le16(mz_uint8 *p, mz_uint16 v) { p[0] = (mz_uint8)v; p[1] = (mz_uint8)(v >> 8); }
സ്ഥിതം ശൂന്യം mz_write_le32(mz_uint8 *p, mz_uint32 v) { p[0] = (mz_uint8)v; p[1] = (mz_uint8)(v >> 8); p[2] = (mz_uint8)(v >> 16); p[3] = (mz_uint8)(v >> 24); }
#define MZ_WRITE_LE16(p, v) mz_write_le16((mz_uint8 *)(p), (mz_uint16)(v))
#define MZ_WRITE_LE32(p, v) mz_write_le32((mz_uint8 *)(p), (mz_uint32)(v))

mz_bool mz_zip_writer_init(mz_zip_archive *pZip, mz_uint64 existing_size)
{
  എങ്കിൽ ((!pZip) || (pZip->m_pState) || (!pZip->m_pWrite) || (pZip->m_zip_mode != MZ_ZIP_MODE_INVALID))
    തിരികെ MZ_FALSE;

  എങ്കിൽ (pZip->m_file_offset_alignment)
  {
    // Ensure user specified file offset alignment is a power of 2.
    എങ്കിൽ (pZip->m_file_offset_alignment & (pZip->m_file_offset_alignment - 1))
      തിരികെ MZ_FALSE;
  }

  എങ്കിൽ (!pZip->m_pAlloc) pZip->m_pAlloc = def_alloc_func;
  എങ്കിൽ (!pZip->m_pFree) pZip->m_pFree = def_free_func;
  എങ്കിൽ (!pZip->m_pRealloc) pZip->m_pRealloc = def_realloc_func;

  pZip->m_zip_mode = MZ_ZIP_MODE_WRITING;
  pZip->m_archive_size = existing_size;
  pZip->m_central_directory_file_ofs = 0;
  pZip->m_total_files = 0;

  എങ്കിൽ (ശൂന്യ == (pZip->m_pState = (mz_zip_internal_state *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, വലുപ്പം(mz_zip_internal_state))))
    തിരികെ MZ_FALSE;
  memset(pZip->m_pState, 0, വലുപ്പം(mz_zip_internal_state));
  MZ_ZIP_ARRAY_SET_ELEMENT_SIZE(&pZip->m_pState->m_central_dir, വലുപ്പം(mz_uint8));
  MZ_ZIP_ARRAY_SET_ELEMENT_SIZE(&pZip->m_pState->m_central_dir_offsets, വലുപ്പം(mz_uint32));
  MZ_ZIP_ARRAY_SET_ELEMENT_SIZE(&pZip->m_pState->m_sorted_central_dir_offsets, വലുപ്പം(mz_uint32));
  തിരികെ MZ_TRUE;
}

സ്ഥിതം size_t mz_zip_heap_write_func(ശൂന്യം *pOpaque, mz_uint64 file_ofs, സ്ഥിരം ശൂന്യം *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_zip_internal_state *pState = pZip->m_pState;
  mz_uint64 new_size = MZ_MAX(file_ofs + n, pState->m_mem_size);
#ifdef _MSC_VER
  എങ്കിൽ ((!n) || ((0, വലുപ്പം(size_t) == വലുപ്പം(mz_uint32)) && (new_size > 0x7FFFFFFF)))
#അല്ലെങ്കിൽ
  എങ്കിൽ ((!n) || ((വലുപ്പം(size_t) == വലുപ്പം(mz_uint32)) && (new_size > 0x7FFFFFFF)))
#endif
    തിരികെ 0;
  എങ്കിൽ (new_size > pState->m_mem_capacity)
  {
    ശൂന്യം *pNew_block;
    size_t new_capacity = MZ_MAX(64, pState->m_mem_capacity); ആകുമ്പോൾ (new_capacity < new_size) new_capacity *= 2;
    എങ്കിൽ (ശൂന്യ == (pNew_block = pZip->m_pRealloc(pZip->m_pAlloc_opaque, pState->m_pMem, 1, new_capacity)))
      തിരികെ 0;
    pState->m_pMem = pNew_block; pState->m_mem_capacity = new_capacity;
  }
  memcpy((mz_uint8 *)pState->m_pMem + file_ofs, pBuf, n);
  pState->m_mem_size = (size_t)new_size;
  തിരികെ n;
}

mz_bool mz_zip_writer_init_heap(mz_zip_archive *pZip, size_t size_to_reserve_at_beginning, size_t initial_allocation_size)
{
  pZip->m_pWrite = mz_zip_heap_write_func;
  pZip->m_pIO_opaque = pZip;
  എങ്കിൽ (!mz_zip_writer_init(pZip, size_to_reserve_at_beginning))
    തിരികെ MZ_FALSE;
  എങ്കിൽ (0 != (initial_allocation_size = MZ_MAX(initial_allocation_size, size_to_reserve_at_beginning)))
  {
    എങ്കിൽ (ശൂന്യ == (pZip->m_pState->m_pMem = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, initial_allocation_size)))
    {
      mz_zip_writer_end(pZip);
      തിരികെ MZ_FALSE;
    }
    pZip->m_pState->m_mem_capacity = initial_allocation_size;
  }
  തിരികെ MZ_TRUE;
}

#ifndef MINIZ_NO_STDIO
സ്ഥിതം size_t mz_zip_file_write_func(ശൂന്യം *pOpaque, mz_uint64 file_ofs, സ്ഥിരം ശൂന്യം *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_int64 cur_ofs = MZ_FTELL64(pZip->m_pState->m_pFile);
  എങ്കിൽ (((mz_int64)file_ofs < 0) || (((cur_ofs != (mz_int64)file_ofs)) && (MZ_FSEEK64(pZip->m_pState->m_pFile, (mz_int64)file_ofs, SEEK_SET))))
    തിരികെ 0;
  തിരികെ MZ_FWRITE(pBuf, 1, n, pZip->m_pState->m_pFile);
}

mz_bool mz_zip_writer_init_file(mz_zip_archive *pZip, സ്ഥിരം അക്ഷരം *pFilename, mz_uint64 size_to_reserve_at_beginning)
{
  MZ_FILE *pFile;
  pZip->m_pWrite = mz_zip_file_write_func;
  pZip->m_pIO_opaque = pZip;
  എങ്കിൽ (!mz_zip_writer_init(pZip, size_to_reserve_at_beginning))
    തിരികെ MZ_FALSE;
  എങ്കിൽ (ശൂന്യ == (pFile = MZ_FOPEN(pFilename, "wb")))
  {
    mz_zip_writer_end(pZip);
    തിരികെ MZ_FALSE;
  }
  pZip->m_pState->m_pFile = pFile;
  എങ്കിൽ (size_to_reserve_at_beginning)
  {
    mz_uint64 cur_ofs = 0; അക്ഷരം buf[4096]; MZ_CLEAR_ARR(buf);
    ചെയ്യുക
    {
      size_t n = (size_t)MZ_MIN(വലുപ്പം(buf), size_to_reserve_at_beginning);
      എങ്കിൽ (pZip->m_pWrite(pZip->m_pIO_opaque, cur_ofs, buf, n) != n)
      {
        mz_zip_writer_end(pZip);
        തിരികെ MZ_FALSE;
      }
      cur_ofs += n; size_to_reserve_at_beginning -= n;
    } ആകുമ്പോൾ (size_to_reserve_at_beginning);
  }
  തിരികെ MZ_TRUE;
}
#endif // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_writer_init_from_reader(mz_zip_archive *pZip, സ്ഥിരം അക്ഷരം *pFilename)
{
  mz_zip_internal_state *pState;
  എങ്കിൽ ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_mode != MZ_ZIP_MODE_READING))
    തിരികെ MZ_FALSE;
  // No sense in trying to write to an archive that's already at the support max size
  എങ്കിൽ ((pZip->m_total_files == 0xFFFF) || ((pZip->m_archive_size + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE + MZ_ZIP_LOCAL_DIR_HEADER_SIZE) > 0xFFFFFFFF))
    തിരികെ MZ_FALSE;

  pState = pZip->m_pState;

  എങ്കിൽ (pState->m_pFile)
  {
#ifdef MINIZ_NO_STDIO
    pFilename; തിരികെ MZ_FALSE;
#അല്ലെങ്കിൽ
    // Archive is being read from stdio - try to reopen as writable.
    എങ്കിൽ (pZip->m_pIO_opaque != pZip)
      തിരികെ MZ_FALSE;
    എങ്കിൽ (!pFilename)
      തിരികെ MZ_FALSE;
    pZip->m_pWrite = mz_zip_file_write_func;
    എങ്കിൽ (ശൂന്യ == (pState->m_pFile = MZ_FREOPEN(pFilename, "r+b", pState->m_pFile)))
    {
      // The mz_zip_archive is now in a bogus state because pState->m_pFile is NULL, so just close it.
      mz_zip_reader_end(pZip);
      തിരികെ MZ_FALSE;
    }
#endif // #ifdef MINIZ_NO_STDIO
  }
  അല്ലെങ്കിൽ എങ്കിൽ (pState->m_pMem)
  {
    // Archive lives in a memory block. Assume it's from the heap that we can resize using the realloc callback.
    എങ്കിൽ (pZip->m_pIO_opaque != pZip)
      തിരികെ MZ_FALSE;
    pState->m_mem_capacity = pState->m_mem_size;
    pZip->m_pWrite = mz_zip_heap_write_func;
  }
  // Archive is being read via a user provided read function - make sure the user has specified a write function too.
  അല്ലെങ്കിൽ എങ്കിൽ (!pZip->m_pWrite)
    തിരികെ MZ_FALSE;

  // Start writing new files at the archive's current central directory location.
  pZip->m_archive_size = pZip->m_central_directory_file_ofs;
  pZip->m_zip_mode = MZ_ZIP_MODE_WRITING;
  pZip->m_central_directory_file_ofs = 0;

  തിരികെ MZ_TRUE;
}

mz_bool mz_zip_writer_add_mem(mz_zip_archive *pZip, സ്ഥിരം അക്ഷരം *pArchive_name, സ്ഥിരം ശൂന്യം *pBuf, size_t buf_size, mz_uint level_and_flags)
{
  തിരികെ mz_zip_writer_add_mem_ex(pZip, pArchive_name, pBuf, buf_size, ശൂന്യ, 0, level_and_flags, 0, 0);
}

തരനിർവചനം ഘടന
{
  mz_zip_archive *m_pZip;
  mz_uint64 m_cur_archive_file_ofs;
  mz_uint64 m_comp_size;
} mz_zip_writer_add_state;

സ്ഥിതം mz_bool mz_zip_writer_add_put_buf_callback(സ്ഥിരം ശൂന്യം* pBuf, പൂർണ്ണസംഖ്യ len, ശൂന്യം *pUser)
{
  mz_zip_writer_add_state *pState = (mz_zip_writer_add_state *)pUser;
  എങ്കിൽ ((പൂർണ്ണസംഖ്യ)pState->m_pZip->m_pWrite(pState->m_pZip->m_pIO_opaque, pState->m_cur_archive_file_ofs, pBuf, len) != len)
    തിരികെ MZ_FALSE;
  pState->m_cur_archive_file_ofs += len;
  pState->m_comp_size += len;
  തിരികെ MZ_TRUE;
}

സ്ഥിതം mz_bool mz_zip_writer_create_local_dir_header(mz_zip_archive *pZip, mz_uint8 *pDst, mz_uint16 filename_size, mz_uint16 extra_size, mz_uint64 uncomp_size, mz_uint64 comp_size, mz_uint32 uncomp_crc32, mz_uint16 method, mz_uint16 bit_flags, mz_uint16 dos_time, mz_uint16 dos_date)
{
  (ശൂന്യം)pZip;
  memset(pDst, 0, MZ_ZIP_LOCAL_DIR_HEADER_SIZE);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_SIG_OFS, MZ_ZIP_LOCAL_DIR_HEADER_SIG);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_VERSION_NEEDED_OFS, method ? 20 : 0);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_BIT_FLAG_OFS, bit_flags);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_METHOD_OFS, method);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILE_TIME_OFS, dos_time);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILE_DATE_OFS, dos_date);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_CRC32_OFS, uncomp_crc32);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_COMPRESSED_SIZE_OFS, comp_size);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_DECOMPRESSED_SIZE_OFS, uncomp_size);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILENAME_LEN_OFS, filename_size);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_EXTRA_LEN_OFS, extra_size);
  തിരികെ MZ_TRUE;
}

സ്ഥിതം mz_bool mz_zip_writer_create_central_dir_header(mz_zip_archive *pZip, mz_uint8 *pDst, mz_uint16 filename_size, mz_uint16 extra_size, mz_uint16 comment_size, mz_uint64 uncomp_size, mz_uint64 comp_size, mz_uint32 uncomp_crc32, mz_uint16 method, mz_uint16 bit_flags, mz_uint16 dos_time, mz_uint16 dos_date, mz_uint64 local_header_ofs, mz_uint32 ext_attributes)
{
  (ശൂന്യം)pZip;
  memset(pDst, 0, MZ_ZIP_CENTRAL_DIR_HEADER_SIZE);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_SIG_OFS, MZ_ZIP_CENTRAL_DIR_HEADER_SIG);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_VERSION_NEEDED_OFS, method ? 20 : 0);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_BIT_FLAG_OFS, bit_flags);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_METHOD_OFS, method);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILE_TIME_OFS, dos_time);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILE_DATE_OFS, dos_date);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_CRC32_OFS, uncomp_crc32);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_COMPRESSED_SIZE_OFS, comp_size);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_DECOMPRESSED_SIZE_OFS, uncomp_size);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILENAME_LEN_OFS, filename_size);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_EXTRA_LEN_OFS, extra_size);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_COMMENT_LEN_OFS, comment_size);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS, ext_attributes);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_LOCAL_HEADER_OFS, local_header_ofs);
  തിരികെ MZ_TRUE;
}

സ്ഥിതം mz_bool mz_zip_writer_add_to_central_dir(mz_zip_archive *pZip, സ്ഥിരം അക്ഷരം *pFilename, mz_uint16 filename_size, സ്ഥിരം ശൂന്യം *pExtra, mz_uint16 extra_size, സ്ഥിരം ശൂന്യം *pComment, mz_uint16 comment_size, mz_uint64 uncomp_size, mz_uint64 comp_size, mz_uint32 uncomp_crc32, mz_uint16 method, mz_uint16 bit_flags, mz_uint16 dos_time, mz_uint16 dos_date, mz_uint64 local_header_ofs, mz_uint32 ext_attributes)
{
  mz_zip_internal_state *pState = pZip->m_pState;
  mz_uint32 central_dir_ofs = (mz_uint32)pState->m_central_dir.m_size;
  size_t orig_central_dir_size = pState->m_central_dir.m_size;
  mz_uint8 central_dir_header[MZ_ZIP_CENTRAL_DIR_HEADER_SIZE];

  // No zip64 support yet
  എങ്കിൽ ((local_header_ofs > 0xFFFFFFFF) || (((mz_uint64)pState->m_central_dir.m_size + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE + filename_size + extra_size + comment_size) > 0xFFFFFFFF))
    തിരികെ MZ_FALSE;

  എങ്കിൽ (!mz_zip_writer_create_central_dir_header(pZip, central_dir_header, filename_size, extra_size, comment_size, uncomp_size, comp_size, uncomp_crc32, method, bit_flags, dos_time, dos_date, local_header_ofs, ext_attributes))
    തിരികെ MZ_FALSE;

  എങ്കിൽ ((!mz_zip_array_തള്ളുക_back(pZip, &pState->m_central_dir, central_dir_header, MZ_ZIP_CENTRAL_DIR_HEADER_SIZE)) ||
      (!mz_zip_array_തള്ളുക_back(pZip, &pState->m_central_dir, pFilename, filename_size)) ||
      (!mz_zip_array_തള്ളുക_back(pZip, &pState->m_central_dir, pExtra, extra_size)) ||
      (!mz_zip_array_തള്ളുക_back(pZip, &pState->m_central_dir, pComment, comment_size)) ||
      (!mz_zip_array_തള്ളുക_back(pZip, &pState->m_central_dir_offsets, &central_dir_ofs, 1)))
  {
    // Try to push the central directory array back into its original state.
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_size, MZ_FALSE);
    തിരികെ MZ_FALSE;
  }

  തിരികെ MZ_TRUE;
}

സ്ഥിതം mz_bool mz_zip_writer_validate_archive_name(സ്ഥിരം അക്ഷരം *pArchive_name)
{
  // Basic ZIP archive filename validity checks: Valid filenames cannot start with a forward slash, cannot contain a drive letter, and cannot use DOS-style backward slashes.
  എങ്കിൽ (*pArchive_name == '/')
    തിരികെ MZ_FALSE;
  ആകുമ്പോൾ (*pArchive_name)
  {
    എങ്കിൽ ((*pArchive_name == '\\') || (*pArchive_name == ':'))
      തിരികെ MZ_FALSE;
    pArchive_name++;
  }
  തിരികെ MZ_TRUE;
}

സ്ഥിതം mz_uint mz_zip_writer_compute_padding_needed_for_file_alignment(mz_zip_archive *pZip)
{
  mz_uint32 n;
  എങ്കിൽ (!pZip->m_file_offset_alignment)
    തിരികെ 0;
  n = (mz_uint32)(pZip->m_archive_size & (pZip->m_file_offset_alignment - 1));
  തിരികെ (pZip->m_file_offset_alignment - n) & (pZip->m_file_offset_alignment - 1);
}

സ്ഥിതം mz_bool mz_zip_writer_write_zeros(mz_zip_archive *pZip, mz_uint64 cur_file_ofs, mz_uint32 n)
{
  അക്ഷരം buf[4096];
  memset(buf, 0, MZ_MIN(വലുപ്പം(buf), n));
  ആകുമ്പോൾ (n)
  {
    mz_uint32 s = MZ_MIN(വലുപ്പം(buf), n);
    എങ്കിൽ (pZip->m_pWrite(pZip->m_pIO_opaque, cur_file_ofs, buf, s) != s)
      തിരികെ MZ_FALSE;
    cur_file_ofs += s; n -= s;
  }
  തിരികെ MZ_TRUE;
}

mz_bool mz_zip_writer_add_mem_ex(mz_zip_archive *pZip, സ്ഥിരം അക്ഷരം *pArchive_name, സ്ഥിരം ശൂന്യം *pBuf, size_t buf_size, സ്ഥിരം ശൂന്യം *pComment, mz_uint16 comment_size, mz_uint level_and_flags, mz_uint64 uncomp_size, mz_uint32 uncomp_crc32)
{
  mz_uint16 method = 0, dos_time = 0, dos_date = 0;
  mz_uint level, ext_attributes = 0, അക്കം_alignment_padding_bytes;
  mz_uint64 local_dir_header_ofs = pZip->m_archive_size, cur_archive_file_ofs = pZip->m_archive_size, comp_size = 0;
  size_t archive_name_size;
  mz_uint8 local_dir_header[MZ_ZIP_LOCAL_DIR_HEADER_SIZE];
  tdefl_compressor *pComp = ശൂന്യ;
  mz_bool store_data_uncompressed;
  mz_zip_internal_state *pState;

  എങ്കിൽ ((പൂർണ്ണസംഖ്യ)level_and_flags < 0)
    level_and_flags = MZ_DEFAULT_LEVEL;
  level = level_and_flags & 0xF;
  store_data_uncompressed = ((!level) || (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_DATA));

  എങ്കിൽ ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_mode != MZ_ZIP_MODE_WRITING) || ((buf_size) && (!pBuf)) || (!pArchive_name) || ((comment_size) && (!pComment)) || (pZip->m_total_files == 0xFFFF) || (level > MZ_UBER_COMPRESSION))
    തിരികെ MZ_FALSE;

  pState = pZip->m_pState;

  എങ്കിൽ ((!(level_and_flags & MZ_ZIP_FLAG_COMPRESSED_DATA)) && (uncomp_size))
    തിരികെ MZ_FALSE;
  // No zip64 support yet
  എങ്കിൽ ((buf_size > 0xFFFFFFFF) || (uncomp_size > 0xFFFFFFFF))
    തിരികെ MZ_FALSE;
  എങ്കിൽ (!mz_zip_writer_validate_archive_name(pArchive_name))
    തിരികെ MZ_FALSE;

#ifndef MINIZ_NO_TIME
  {
    time_t cur_time; time(&cur_time);
    mz_zip_time_to_dos_time(cur_time, &dos_time, &dos_date);
  }
#endif // #ifndef MINIZ_NO_TIME

  archive_name_size = strlen(pArchive_name);
  എങ്കിൽ (archive_name_size > 0xFFFF)
    തിരികെ MZ_FALSE;

  അക്കം_alignment_padding_bytes = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  എങ്കിൽ ((pZip->m_total_files == 0xFFFF) || ((pZip->m_archive_size + അക്കം_alignment_padding_bytes + MZ_ZIP_LOCAL_DIR_HEADER_SIZE + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE + comment_size + archive_name_size) > 0xFFFFFFFF))
    തിരികെ MZ_FALSE;

  എങ്കിൽ ((archive_name_size) && (pArchive_name[archive_name_size - 1] == '/'))
  {
    // Set DOS Subdirectory attribute bit.
    ext_attributes |= 0x10;
    // Subdirectories cannot contain data.
    എങ്കിൽ ((buf_size) || (uncomp_size))
      തിരികെ MZ_FALSE;
  }

  // Try to do any allocations before writing to the archive, so if an allocation fails the file remains unmodified. (A good idea if we're doing an in-place modification.)
  എങ്കിൽ ((!mz_zip_array_ensure_room(pZip, &pState->m_central_dir, MZ_ZIP_CENTRAL_DIR_HEADER_SIZE + archive_name_size + comment_size)) || (!mz_zip_array_ensure_room(pZip, &pState->m_central_dir_offsets, 1)))
    തിരികെ MZ_FALSE;

  എങ്കിൽ ((!store_data_uncompressed) && (buf_size))
  {
    എങ്കിൽ (ശൂന്യ == (pComp = (tdefl_compressor *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, വലുപ്പം(tdefl_compressor))))
      തിരികെ MZ_FALSE;
  }

  എങ്കിൽ (!mz_zip_writer_write_zeros(pZip, cur_archive_file_ofs, അക്കം_alignment_padding_bytes + വലുപ്പം(local_dir_header)))
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
    തിരികെ MZ_FALSE;
  }
  local_dir_header_ofs += അക്കം_alignment_padding_bytes;
  എങ്കിൽ (pZip->m_file_offset_alignment) { MZ_ASSERT((local_dir_header_ofs & (pZip->m_file_offset_alignment - 1)) == 0); }
  cur_archive_file_ofs += അക്കം_alignment_padding_bytes + വലുപ്പം(local_dir_header);

  MZ_CLEAR_ARR(local_dir_header);
  എങ്കിൽ (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pArchive_name, archive_name_size) != archive_name_size)
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
    തിരികെ MZ_FALSE;
  }
  cur_archive_file_ofs += archive_name_size;

  എങ്കിൽ (!(level_and_flags & MZ_ZIP_FLAG_COMPRESSED_DATA))
  {
    uncomp_crc32 = (mz_uint32)mz_crc32(MZ_CRC32_INIT, (സ്ഥിരം mz_uint8*)pBuf, buf_size);
    uncomp_size = buf_size;
    എങ്കിൽ (uncomp_size <= 3)
    {
      level = 0;
      store_data_uncompressed = MZ_TRUE;
    }
  }

  എങ്കിൽ (store_data_uncompressed)
  {
    എങ്കിൽ (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pBuf, buf_size) != buf_size)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
      തിരികെ MZ_FALSE;
    }

    cur_archive_file_ofs += buf_size;
    comp_size = buf_size;

    എങ്കിൽ (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_DATA)
      method = MZ_DEFLATED;
  }
  അല്ലെങ്കിൽ എങ്കിൽ (buf_size)
  {
    mz_zip_writer_add_state state;

    state.m_pZip = pZip;
    state.m_cur_archive_file_ofs = cur_archive_file_ofs;
    state.m_comp_size = 0;

    എങ്കിൽ ((tdefl_init(pComp, mz_zip_writer_add_put_buf_callback, &state, tdefl_create_comp_flags_from_zip_params(level, -15, MZ_DEFAULT_STRATEGY)) != TDEFL_STATUS_OKAY) ||
        (tdefl_compress_buffer(pComp, pBuf, buf_size, TDEFL_FINISH) != TDEFL_STATUS_DONE))
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
      തിരികെ MZ_FALSE;
    }

    comp_size = state.m_comp_size;
    cur_archive_file_ofs = state.m_cur_archive_file_ofs;

    method = MZ_DEFLATED;
  }

  pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
  pComp = ശൂന്യ;

  // no zip64 support yet
  എങ്കിൽ ((comp_size > 0xFFFFFFFF) || (cur_archive_file_ofs > 0xFFFFFFFF))
    തിരികെ MZ_FALSE;

  എങ്കിൽ (!mz_zip_writer_create_local_dir_header(pZip, local_dir_header, (mz_uint16)archive_name_size, 0, uncomp_size, comp_size, uncomp_crc32, method, 0, dos_time, dos_date))
    തിരികെ MZ_FALSE;

  എങ്കിൽ (pZip->m_pWrite(pZip->m_pIO_opaque, local_dir_header_ofs, local_dir_header, വലുപ്പം(local_dir_header)) != വലുപ്പം(local_dir_header))
    തിരികെ MZ_FALSE;

  എങ്കിൽ (!mz_zip_writer_add_to_central_dir(pZip, pArchive_name, (mz_uint16)archive_name_size, ശൂന്യ, 0, pComment, comment_size, uncomp_size, comp_size, uncomp_crc32, method, 0, dos_time, dos_date, local_dir_header_ofs, ext_attributes))
    തിരികെ MZ_FALSE;

  pZip->m_total_files++;
  pZip->m_archive_size = cur_archive_file_ofs;

  തിരികെ MZ_TRUE;
}

#ifndef MINIZ_NO_STDIO
mz_bool mz_zip_writer_add_file(mz_zip_archive *pZip, സ്ഥിരം അക്ഷരം *pArchive_name, സ്ഥിരം അക്ഷരം *pSrc_filename, സ്ഥിരം ശൂന്യം *pComment, mz_uint16 comment_size, mz_uint level_and_flags)
{
  mz_uint uncomp_crc32 = MZ_CRC32_INIT, level, അക്കം_alignment_padding_bytes;
  mz_uint16 method = 0, dos_time = 0, dos_date = 0, ext_attributes = 0;
  mz_uint64 local_dir_header_ofs = pZip->m_archive_size, cur_archive_file_ofs = pZip->m_archive_size, uncomp_size = 0, comp_size = 0;
  size_t archive_name_size;
  mz_uint8 local_dir_header[MZ_ZIP_LOCAL_DIR_HEADER_SIZE];
  MZ_FILE *pSrc_file = ശൂന്യ;

  എങ്കിൽ ((പൂർണ്ണസംഖ്യ)level_and_flags < 0)
    level_and_flags = MZ_DEFAULT_LEVEL;
  level = level_and_flags & 0xF;

  എങ്കിൽ ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_mode != MZ_ZIP_MODE_WRITING) || (!pArchive_name) || ((comment_size) && (!pComment)) || (level > MZ_UBER_COMPRESSION))
    തിരികെ MZ_FALSE;
  എങ്കിൽ (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_DATA)
    തിരികെ MZ_FALSE;
  എങ്കിൽ (!mz_zip_writer_validate_archive_name(pArchive_name))
    തിരികെ MZ_FALSE;

  archive_name_size = strlen(pArchive_name);
  എങ്കിൽ (archive_name_size > 0xFFFF)
    തിരികെ MZ_FALSE;

  അക്കം_alignment_padding_bytes = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  എങ്കിൽ ((pZip->m_total_files == 0xFFFF) || ((pZip->m_archive_size + അക്കം_alignment_padding_bytes + MZ_ZIP_LOCAL_DIR_HEADER_SIZE + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE + comment_size + archive_name_size) > 0xFFFFFFFF))
    തിരികെ MZ_FALSE;

  എങ്കിൽ (!mz_zip_get_file_modified_time(pSrc_filename, &dos_time, &dos_date))
    തിരികെ MZ_FALSE;

  pSrc_file = MZ_FOPEN(pSrc_filename, "rb");
  എങ്കിൽ (!pSrc_file)
    തിരികെ MZ_FALSE;
  MZ_FSEEK64(pSrc_file, 0, SEEK_END);
  uncomp_size = MZ_FTELL64(pSrc_file);
  MZ_FSEEK64(pSrc_file, 0, SEEK_SET);

  എങ്കിൽ (uncomp_size > 0xFFFFFFFF)
  {
    // No zip64 support yet
    MZ_FCLOSE(pSrc_file);
    തിരികെ MZ_FALSE;
  }
  എങ്കിൽ (uncomp_size <= 3)
    level = 0;

  എങ്കിൽ (!mz_zip_writer_write_zeros(pZip, cur_archive_file_ofs, അക്കം_alignment_padding_bytes + വലുപ്പം(local_dir_header)))
  {
    MZ_FCLOSE(pSrc_file);
    തിരികെ MZ_FALSE;
  }
  local_dir_header_ofs += അക്കം_alignment_padding_bytes;
  എങ്കിൽ (pZip->m_file_offset_alignment) { MZ_ASSERT((local_dir_header_ofs & (pZip->m_file_offset_alignment - 1)) == 0); }
  cur_archive_file_ofs += അക്കം_alignment_padding_bytes + വലുപ്പം(local_dir_header);

  MZ_CLEAR_ARR(local_dir_header);
  എങ്കിൽ (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pArchive_name, archive_name_size) != archive_name_size)
  {
    MZ_FCLOSE(pSrc_file);
    തിരികെ MZ_FALSE;
  }
  cur_archive_file_ofs += archive_name_size;

  എങ്കിൽ (uncomp_size)
  {
    mz_uint64 uncomp_remaining = uncomp_size;
    ശൂന്യം *pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, MZ_ZIP_MAX_IO_BUF_SIZE);
    എങ്കിൽ (!pRead_buf)
    {
      MZ_FCLOSE(pSrc_file);
      തിരികെ MZ_FALSE;
    }

    എങ്കിൽ (!level)
    {
      ആകുമ്പോൾ (uncomp_remaining)
      {
        mz_uint n = (mz_uint)MZ_MIN(MZ_ZIP_MAX_IO_BUF_SIZE, uncomp_remaining);
        എങ്കിൽ ((MZ_FREAD(pRead_buf, 1, n, pSrc_file) != n) || (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pRead_buf, n) != n))
        {
          pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
          MZ_FCLOSE(pSrc_file);
          തിരികെ MZ_FALSE;
        }
        uncomp_crc32 = (mz_uint32)mz_crc32(uncomp_crc32, (സ്ഥിരം mz_uint8 *)pRead_buf, n);
        uncomp_remaining -= n;
        cur_archive_file_ofs += n;
      }
      comp_size = uncomp_size;
    }
    അല്ലെങ്കിൽ
    {
      mz_bool result = MZ_FALSE;
      mz_zip_writer_add_state state;
      tdefl_compressor *pComp = (tdefl_compressor *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, വലുപ്പം(tdefl_compressor));
      എങ്കിൽ (!pComp)
      {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        തിരികെ MZ_FALSE;
      }

      state.m_pZip = pZip;
      state.m_cur_archive_file_ofs = cur_archive_file_ofs;
      state.m_comp_size = 0;

      എങ്കിൽ (tdefl_init(pComp, mz_zip_writer_add_put_buf_callback, &state, tdefl_create_comp_flags_from_zip_params(level, -15, MZ_DEFAULT_STRATEGY)) != TDEFL_STATUS_OKAY)
      {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        തിരികെ MZ_FALSE;
      }

      വേണ്ടി ( ; ; )
      {
        size_t in_buf_size = (mz_uint32)MZ_MIN(uncomp_remaining, MZ_ZIP_MAX_IO_BUF_SIZE);
        tdefl_status status;

        എങ്കിൽ (MZ_FREAD(pRead_buf, 1, in_buf_size, pSrc_file) != in_buf_size)
          നിർത്തുക;

        uncomp_crc32 = (mz_uint32)mz_crc32(uncomp_crc32, (സ്ഥിരം mz_uint8 *)pRead_buf, in_buf_size);
        uncomp_remaining -= in_buf_size;

        status = tdefl_compress_buffer(pComp, pRead_buf, in_buf_size, uncomp_remaining ? TDEFL_NO_FLUSH : TDEFL_FINISH);
        എങ്കിൽ (status == TDEFL_STATUS_DONE)
        {
          result = MZ_TRUE;
          നിർത്തുക;
        }
        അല്ലെങ്കിൽ എങ്കിൽ (status != TDEFL_STATUS_OKAY)
          നിർത്തുക;
      }

      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);

      എങ്കിൽ (!result)
      {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        തിരികെ MZ_FALSE;
      }

      comp_size = state.m_comp_size;
      cur_archive_file_ofs = state.m_cur_archive_file_ofs;

      method = MZ_DEFLATED;
    }

    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
  }

  MZ_FCLOSE(pSrc_file); pSrc_file = ശൂന്യ;

  // no zip64 support yet
  എങ്കിൽ ((comp_size > 0xFFFFFFFF) || (cur_archive_file_ofs > 0xFFFFFFFF))
    തിരികെ MZ_FALSE;

  എങ്കിൽ (!mz_zip_writer_create_local_dir_header(pZip, local_dir_header, (mz_uint16)archive_name_size, 0, uncomp_size, comp_size, uncomp_crc32, method, 0, dos_time, dos_date))
    തിരികെ MZ_FALSE;

  എങ്കിൽ (pZip->m_pWrite(pZip->m_pIO_opaque, local_dir_header_ofs, local_dir_header, വലുപ്പം(local_dir_header)) != വലുപ്പം(local_dir_header))
    തിരികെ MZ_FALSE;

  എങ്കിൽ (!mz_zip_writer_add_to_central_dir(pZip, pArchive_name, (mz_uint16)archive_name_size, ശൂന്യ, 0, pComment, comment_size, uncomp_size, comp_size, uncomp_crc32, method, 0, dos_time, dos_date, local_dir_header_ofs, ext_attributes))
    തിരികെ MZ_FALSE;

  pZip->m_total_files++;
  pZip->m_archive_size = cur_archive_file_ofs;

  തിരികെ MZ_TRUE;
}
#endif // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_writer_add_from_zip_reader(mz_zip_archive *pZip, mz_zip_archive *pSource_zip, mz_uint file_index)
{
  mz_uint n, bit_flags, അക്കം_alignment_padding_bytes;
  mz_uint64 comp_bytes_remaining, local_dir_header_ofs;
  mz_uint64 cur_src_file_ofs, cur_dst_file_ofs;
  mz_uint32 local_header_u32[(MZ_ZIP_LOCAL_DIR_HEADER_SIZE + വലുപ്പം(mz_uint32) - 1) / വലുപ്പം(mz_uint32)]; mz_uint8 *pLocal_header = (mz_uint8 *)local_header_u32;
  mz_uint8 central_header[MZ_ZIP_CENTRAL_DIR_HEADER_SIZE];
  size_t orig_central_dir_size;
  mz_zip_internal_state *pState;
  ശൂന്യം *pBuf; സ്ഥിരം mz_uint8 *pSrc_central_header;

  എങ്കിൽ ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_mode != MZ_ZIP_MODE_WRITING))
    തിരികെ MZ_FALSE;
  എങ്കിൽ (ശൂന്യ == (pSrc_central_header = mz_zip_reader_get_cdh(pSource_zip, file_index)))
    തിരികെ MZ_FALSE;
  pState = pZip->m_pState;

  അക്കം_alignment_padding_bytes = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  എങ്കിൽ ((pZip->m_total_files == 0xFFFF) || ((pZip->m_archive_size + അക്കം_alignment_padding_bytes + MZ_ZIP_LOCAL_DIR_HEADER_SIZE + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE) > 0xFFFFFFFF))
    തിരികെ MZ_FALSE;

  cur_src_file_ofs = MZ_READ_LE32(pSrc_central_header + MZ_ZIP_CDH_LOCAL_HEADER_OFS);
  cur_dst_file_ofs = pZip->m_archive_size;

  എങ്കിൽ (pSource_zip->m_pRead(pSource_zip->m_pIO_opaque, cur_src_file_ofs, pLocal_header, MZ_ZIP_LOCAL_DIR_HEADER_SIZE) != MZ_ZIP_LOCAL_DIR_HEADER_SIZE)
    തിരികെ MZ_FALSE;
  എങ്കിൽ (MZ_READ_LE32(pLocal_header) != MZ_ZIP_LOCAL_DIR_HEADER_SIG)
    തിരികെ MZ_FALSE;
  cur_src_file_ofs += MZ_ZIP_LOCAL_DIR_HEADER_SIZE;

  എങ്കിൽ (!mz_zip_writer_write_zeros(pZip, cur_dst_file_ofs, അക്കം_alignment_padding_bytes))
    തിരികെ MZ_FALSE;
  cur_dst_file_ofs += അക്കം_alignment_padding_bytes;
  local_dir_header_ofs = cur_dst_file_ofs;
  എങ്കിൽ (pZip->m_file_offset_alignment) { MZ_ASSERT((local_dir_header_ofs & (pZip->m_file_offset_alignment - 1)) == 0); }

  എങ്കിൽ (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, pLocal_header, MZ_ZIP_LOCAL_DIR_HEADER_SIZE) != MZ_ZIP_LOCAL_DIR_HEADER_SIZE)
    തിരികെ MZ_FALSE;
  cur_dst_file_ofs += MZ_ZIP_LOCAL_DIR_HEADER_SIZE;

  n = MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  comp_bytes_remaining = n + MZ_READ_LE32(pSrc_central_header + MZ_ZIP_CDH_COMPRESSED_SIZE_OFS);

  എങ്കിൽ (ശൂന്യ == (pBuf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)MZ_MAX(വലുപ്പം(mz_uint32) * 4, MZ_MIN(MZ_ZIP_MAX_IO_BUF_SIZE, comp_bytes_remaining)))))
    തിരികെ MZ_FALSE;

  ആകുമ്പോൾ (comp_bytes_remaining)
  {
    n = (mz_uint)MZ_MIN(MZ_ZIP_MAX_IO_BUF_SIZE, comp_bytes_remaining);
    എങ്കിൽ (pSource_zip->m_pRead(pSource_zip->m_pIO_opaque, cur_src_file_ofs, pBuf, n) != n)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      തിരികെ MZ_FALSE;
    }
    cur_src_file_ofs += n;

    എങ്കിൽ (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, pBuf, n) != n)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      തിരികെ MZ_FALSE;
    }
    cur_dst_file_ofs += n;

    comp_bytes_remaining -= n;
  }

  bit_flags = MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_BIT_FLAG_OFS);
  എങ്കിൽ (bit_flags & 8)
  {
    // Copy data descriptor
    എങ്കിൽ (pSource_zip->m_pRead(pSource_zip->m_pIO_opaque, cur_src_file_ofs, pBuf, വലുപ്പം(mz_uint32) * 4) != വലുപ്പം(mz_uint32) * 4)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      തിരികെ MZ_FALSE;
    }

    n = വലുപ്പം(mz_uint32) * ((MZ_READ_LE32(pBuf) == 0x08074b50) ? 4 : 3);
    എങ്കിൽ (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, pBuf, n) != n)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      തിരികെ MZ_FALSE;
    }

    cur_src_file_ofs += n;
    cur_dst_file_ofs += n;
  }
  pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);

  // no zip64 support yet
  എങ്കിൽ (cur_dst_file_ofs > 0xFFFFFFFF)
    തിരികെ MZ_FALSE;

  orig_central_dir_size = pState->m_central_dir.m_size;

  memcpy(central_header, pSrc_central_header, MZ_ZIP_CENTRAL_DIR_HEADER_SIZE);
  MZ_WRITE_LE32(central_header + MZ_ZIP_CDH_LOCAL_HEADER_OFS, local_dir_header_ofs);
  എങ്കിൽ (!mz_zip_array_തള്ളുക_back(pZip, &pState->m_central_dir, central_header, MZ_ZIP_CENTRAL_DIR_HEADER_SIZE))
    തിരികെ MZ_FALSE;

  n = MZ_READ_LE16(pSrc_central_header + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(pSrc_central_header + MZ_ZIP_CDH_EXTRA_LEN_OFS) + MZ_READ_LE16(pSrc_central_header + MZ_ZIP_CDH_COMMENT_LEN_OFS);
  എങ്കിൽ (!mz_zip_array_തള്ളുക_back(pZip, &pState->m_central_dir, pSrc_central_header + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE, n))
  {
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_size, MZ_FALSE);
    തിരികെ MZ_FALSE;
  }

  എങ്കിൽ (pState->m_central_dir.m_size > 0xFFFFFFFF)
    തിരികെ MZ_FALSE;
  n = (mz_uint32)orig_central_dir_size;
  എങ്കിൽ (!mz_zip_array_തള്ളുക_back(pZip, &pState->m_central_dir_offsets, &n, 1))
  {
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_size, MZ_FALSE);
    തിരികെ MZ_FALSE;
  }

  pZip->m_total_files++;
  pZip->m_archive_size = cur_dst_file_ofs;

  തിരികെ MZ_TRUE;
}

mz_bool mz_zip_writer_finalize_archive(mz_zip_archive *pZip)
{
  mz_zip_internal_state *pState;
  mz_uint64 central_dir_ofs, central_dir_size;
  mz_uint8 hdr[MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE];

  എങ്കിൽ ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_mode != MZ_ZIP_MODE_WRITING))
    തിരികെ MZ_FALSE;

  pState = pZip->m_pState;

  // no zip64 support yet
  എങ്കിൽ ((pZip->m_total_files > 0xFFFF) || ((pZip->m_archive_size + pState->m_central_dir.m_size + MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE) > 0xFFFFFFFF))
    തിരികെ MZ_FALSE;

  central_dir_ofs = 0;
  central_dir_size = 0;
  എങ്കിൽ (pZip->m_total_files)
  {
    // Write central directory
    central_dir_ofs = pZip->m_archive_size;
    central_dir_size = pState->m_central_dir.m_size;
    pZip->m_central_directory_file_ofs = central_dir_ofs;
    എങ്കിൽ (pZip->m_pWrite(pZip->m_pIO_opaque, central_dir_ofs, pState->m_central_dir.m_p, (size_t)central_dir_size) != central_dir_size)
      തിരികെ MZ_FALSE;
    pZip->m_archive_size += central_dir_size;
  }

  // Write end of central directory record
  MZ_CLEAR_ARR(hdr);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_SIG_OFS, MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIG);
  MZ_WRITE_LE16(hdr + MZ_ZIP_ECDH_CDIR_അക്കം_ENTRIES_ON_DISK_OFS, pZip->m_total_files);
  MZ_WRITE_LE16(hdr + MZ_ZIP_ECDH_CDIR_TOTAL_ENTRIES_OFS, pZip->m_total_files);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_CDIR_SIZE_OFS, central_dir_size);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_CDIR_OFS_OFS, central_dir_ofs);

  എങ്കിൽ (pZip->m_pWrite(pZip->m_pIO_opaque, pZip->m_archive_size, hdr, വലുപ്പം(hdr)) != വലുപ്പം(hdr))
    തിരികെ MZ_FALSE;
#ifndef MINIZ_NO_STDIO
  എങ്കിൽ ((pState->m_pFile) && (MZ_FFLUSH(pState->m_pFile) == EOF))
    തിരികെ MZ_FALSE;
#endif // #ifndef MINIZ_NO_STDIO

  pZip->m_archive_size += വലുപ്പം(hdr);

  pZip->m_zip_mode = MZ_ZIP_MODE_WRITING_HAS_BEEN_FINALIZED;
  തിരികെ MZ_TRUE;
}

mz_bool mz_zip_writer_finalize_heap_archive(mz_zip_archive *pZip, ശൂന്യം **pBuf, size_t *pSize)
{
  എങ്കിൽ ((!pZip) || (!pZip->m_pState) || (!pBuf) || (!pSize))
    തിരികെ MZ_FALSE;
  എങ്കിൽ (pZip->m_pWrite != mz_zip_heap_write_func)
    തിരികെ MZ_FALSE;
  എങ്കിൽ (!mz_zip_writer_finalize_archive(pZip))
    തിരികെ MZ_FALSE;

  *pBuf = pZip->m_pState->m_pMem;
  *pSize = pZip->m_pState->m_mem_size;
  pZip->m_pState->m_pMem = ശൂന്യ;
  pZip->m_pState->m_mem_size = pZip->m_pState->m_mem_capacity = 0;
  തിരികെ MZ_TRUE;
}

mz_bool mz_zip_writer_end(mz_zip_archive *pZip)
{
  mz_zip_internal_state *pState;
  mz_bool status = MZ_TRUE;
  എങ്കിൽ ((!pZip) || (!pZip->m_pState) || (!pZip->m_pAlloc) || (!pZip->m_pFree) || ((pZip->m_zip_mode != MZ_ZIP_MODE_WRITING) && (pZip->m_zip_mode != MZ_ZIP_MODE_WRITING_HAS_BEEN_FINALIZED)))
    തിരികെ MZ_FALSE;

  pState = pZip->m_pState;
  pZip->m_pState = ശൂന്യ;
  mz_zip_array_clear(pZip, &pState->m_central_dir);
  mz_zip_array_clear(pZip, &pState->m_central_dir_offsets);
  mz_zip_array_clear(pZip, &pState->m_sorted_central_dir_offsets);

#ifndef MINIZ_NO_STDIO
  എങ്കിൽ (pState->m_pFile)
  {
    MZ_FCLOSE(pState->m_pFile);
    pState->m_pFile = ശൂന്യ;
  }
#endif // #ifndef MINIZ_NO_STDIO

  എങ്കിൽ ((pZip->m_pWrite == mz_zip_heap_write_func) && (pState->m_pMem))
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pState->m_pMem);
    pState->m_pMem = ശൂന്യ;
  }

  pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
  pZip->m_zip_mode = MZ_ZIP_MODE_INVALID;
  തിരികെ status;
}

#ifndef MINIZ_NO_STDIO
mz_bool mz_zip_add_mem_to_archive_file_in_place(സ്ഥിരം അക്ഷരം *pZip_filename, സ്ഥിരം അക്ഷരം *pArchive_name, സ്ഥിരം ശൂന്യം *pBuf, size_t buf_size, സ്ഥിരം ശൂന്യം *pComment, mz_uint16 comment_size, mz_uint level_and_flags)
{
  mz_bool status, created_new_archive = MZ_FALSE;
  mz_zip_archive zip_archive;
  ഘടന MZ_FILE_STAT_STRUCT file_stat;
  MZ_CLEAR_OBJ(zip_archive);
  എങ്കിൽ ((പൂർണ്ണസംഖ്യ)level_and_flags < 0)
     level_and_flags = MZ_DEFAULT_LEVEL;
  എങ്കിൽ ((!pZip_filename) || (!pArchive_name) || ((buf_size) && (!pBuf)) || ((comment_size) && (!pComment)) || ((level_and_flags & 0xF) > MZ_UBER_COMPRESSION))
    തിരികെ MZ_FALSE;
  എങ്കിൽ (!mz_zip_writer_validate_archive_name(pArchive_name))
    തിരികെ MZ_FALSE;
  എങ്കിൽ (MZ_FILE_STAT(pZip_filename, &file_stat) != 0)
  {
    // Create a new archive.
    എങ്കിൽ (!mz_zip_writer_init_file(&zip_archive, pZip_filename, 0))
      തിരികെ MZ_FALSE;
    created_new_archive = MZ_TRUE;
  }
  അല്ലെങ്കിൽ
  {
    // Append to an existing archive.
    എങ്കിൽ (!mz_zip_reader_init_file(&zip_archive, pZip_filename, level_and_flags | MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY))
      തിരികെ MZ_FALSE;
    എങ്കിൽ (!mz_zip_writer_init_from_reader(&zip_archive, pZip_filename))
    {
      mz_zip_reader_end(&zip_archive);
      തിരികെ MZ_FALSE;
    }
  }
  status = mz_zip_writer_add_mem_ex(&zip_archive, pArchive_name, pBuf, buf_size, pComment, comment_size, level_and_flags, 0, 0);
  // Always finalize, even if adding failed for some reason, so we have a valid central directory. (This may not always succeed, but we can try.)
  എങ്കിൽ (!mz_zip_writer_finalize_archive(&zip_archive))
    status = MZ_FALSE;
  എങ്കിൽ (!mz_zip_writer_end(&zip_archive))
    status = MZ_FALSE;
  എങ്കിൽ ((!status) && (created_new_archive))
  {
    // It's a new archive and something went wrong, so just delete it.
    പൂർണ്ണസംഖ്യ ignoredStatus = MZ_DELETE_FILE(pZip_filename);
    (ശൂന്യം)ignoredStatus;
  }
  തിരികെ status;
}

ശൂന്യം *mz_zip_extract_archive_file_to_heap(സ്ഥിരം അക്ഷരം *pZip_filename, സ്ഥിരം അക്ഷരം *pArchive_name, size_t *pSize, mz_uint flags)
{
  പൂർണ്ണസംഖ്യ file_index;
  mz_zip_archive zip_archive;
  ശൂന്യം *p = ശൂന്യ;

  എങ്കിൽ (pSize)
    *pSize = 0;

  എങ്കിൽ ((!pZip_filename) || (!pArchive_name))
    തിരികെ ശൂന്യ;

  MZ_CLEAR_OBJ(zip_archive);
  എങ്കിൽ (!mz_zip_reader_init_file(&zip_archive, pZip_filename, flags | MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY))
    തിരികെ ശൂന്യ;

  എങ്കിൽ ((file_index = mz_zip_reader_locate_file(&zip_archive, pArchive_name, ശൂന്യ, flags)) >= 0)
    p = mz_zip_reader_extract_to_heap(&zip_archive, file_index, pSize, flags);

  mz_zip_reader_end(&zip_archive);
  തിരികെ p;
}

#endif // #ifndef MINIZ_NO_STDIO

#endif // #ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

#endif // #ifndef MINIZ_NO_ARCHIVE_APIS

#ifdef __cplusplus
}
#endif

#ifdef _MSC_VER
#pragma warning (എടുക്കുക)
#endif

#endif // MINIZ_HEADER_FILE_ONLY

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

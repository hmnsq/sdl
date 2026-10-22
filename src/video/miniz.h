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

#যদি defined(__TINYC__) && (defined(__linux) || defined(__linux__))
  // TODO: Work around "error: include file 'sys\utime.h' when compiling with tcc on Linux
  #define MINIZ_NO_TIME
#endif

#যদি !defined(MINIZ_NO_TIME) && !defined(MINIZ_NO_ARCHIVE_APIS)
  #অন্তর্ভাব <time.h>
#endif

#যদি defined(_M_IX86) || defined(_M_X64) || defined(__i386__) || defined(__i386) || defined(__i486__) || defined(__i486) || defined(i386) || defined(__ia64__) || defined(__x86_64__)
// MINIZ_X86_OR_X64_CPU is only used to help set the below macros.
#define MINIZ_X86_OR_X64_CPU 1
#endif

#ifndef MINIZ_LITTLE_ENDIAN /* if not defined by SDL */
#যদি (__BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__) || MINIZ_X86_OR_X64_CPU
// Set MINIZ_LITTLE_ENDIAN to 1 if the processor is little endian.
#define MINIZ_LITTLE_ENDIAN 1
#endif
#endif // MINIZ_LITTLE_ENDIAN /* if not defined by SDL */

#ifndef MINIZ_USE_UNALIGNED_LOADS_AND_STORES
#যদি MINIZ_X86_OR_X64_CPU
// Set MINIZ_USE_UNALIGNED_LOADS_AND_STORES to 1 on CPU's that permit efficient integer loads and stores from unaligned addresses.
#define MINIZ_USE_UNALIGNED_LOADS_AND_STORES 1
#endif
#endif // MINIZ_USE_UNALIGNED_LOADS_AND_STORES

#যদি defined(_M_X64) || defined(_WIN64) || defined(__MINGW64__) || defined(_LP64) || defined(__LP64__) || defined(__ia64__) || defined(__x86_64__)
// Set MINIZ_HAS_64BIT_REGISTERS to 1 if operations on 64-bit integers are reasonably fast (and don't involve compiler generated calls to helper functions).
#define MINIZ_HAS_64BIT_REGISTERS 1
#endif

#ifdef MINIZ_STATIC_FUNCTIONS
#define MINIZ_STATIC স্থির
#অন্যথা
#define MINIZ_STATIC
#endif

#ifdef __cplusplus
বাহ্যিক "C" {
#endif

// ------------------- zlib-style API Definitions.

// For more compatibility with zlib, miniz.c uses unsigned long for some parameters/struct members. Beware: mz_ulong can be either 32 or 64-bits!
প্রকারলেখ unsigned long mz_ulong;

// mz_free() internally uses the MZ_FREE() macro (which by default calls free() unless you've modified the MZ_MALLOC macro) to release a block allocated from the heap.
MINIZ_STATIC শূন্য mz_free(শূন্য *p);

#define MZ_ADLER32_INIT (1)
// mz_adler32() returns the initial adler-32 value to use when called with ptr==NULL.
MINIZ_STATIC mz_ulong mz_adler32(mz_ulong adler, ধ্রুবক unsigned অক্ষর *ptr, size_t buf_len);

#define MZ_CRC32_INIT (0)
// mz_crc32() returns the initial CRC-32 value to use when called with ptr==NULL.
MINIZ_STATIC mz_ulong mz_crc32(mz_ulong crc, ধ্রুবক unsigned অক্ষর *ptr, size_t buf_len);

// Compression strategies.
গণনা { MZ_DEFAULT_STRATEGY = 0, MZ_FILTERED = 1, MZ_HUFFMAN_ONLY = 2, MZ_RLE = 3, MZ_FIXED = 4 };

// Method
#define MZ_DEFLATED 8

#ifndef MINIZ_NO_ZLIB_APIS

// Heap allocation callbacks.
// Note that mz_alloc_func parameter types purpsosely differ from zlib's: items/size is size_t, not unsigned long.
প্রকারলেখ শূন্য *(*mz_alloc_func)(শূন্য *opaque, size_t বস্তুসমূহ, size_t আকার_2);
প্রকারলেখ শূন্য (*mz_free_func)(শূন্য *opaque, শূন্য *address);
প্রকারলেখ শূন্য *(*mz_realloc_func)(শূন্য *opaque, শূন্য *address, size_t বস্তুসমূহ, size_t আকার_2);

#define MZ_VERSION          "9.1.15"
#define MZ_VERNUM           0x91F0
#define MZ_VER_MAJOR        9
#define MZ_VER_MINOR        1
#define MZ_VER_REVISION     15
#define MZ_VER_SUBREVISION  0

// Flush values. For typical usage you only need MZ_NO_FLUSH and MZ_FINISH. The other values are for advanced use (refer to the zlib docs).
গণনা { MZ_NO_FLUSH = 0, MZ_PARTIAL_FLUSH = 1, MZ_SYNC_FLUSH = 2, MZ_FULL_FLUSH = 3, MZ_FINISH = 4, MZ_BLOCK = 5 };

// Return status codes. MZ_PARAM_ERROR is non-standard.
গণনা { MZ_OK = 0, MZ_STREAM_END = 1, MZ_NEED_DICT = 2, MZ_ERRNO = -1, MZ_STREAM_ERROR = -2, MZ_তথ্য_ERROR = -3, MZ_MEM_ERROR = -4, MZ_BUF_ERROR = -5, MZ_VERSION_ERROR = -6, MZ_PARAM_ERROR = -10000 };

// Compression levels: 0-9 are the standard zlib-style levels, 10 is best possible compression (not zlib compatible, and may be very slow), MZ_DEFAULT_COMPRESSION=MZ_DEFAULT_LEVEL.
গণনা { MZ_NO_COMPRESSION = 0, MZ_BEST_SPEED = 1, MZ_BEST_COMPRESSION = 9, MZ_UBER_COMPRESSION = 10, MZ_DEFAULT_LEVEL = 6, MZ_DEFAULT_COMPRESSION = -1 };

// Window bits
#define MZ_DEFAULT_WINDOW_BITS 15

কাঠামো mz_internal_state;

// Compression/decompression stream struct.
প্রকারলেখ কাঠামো mz_stream_s
{
  ধ্রুবক unsigned অক্ষর *পরবর্তী_in;     // pointer to next byte to read
  unsigned পূর্ণসংখ্যা avail_in;            // number of bytes available at next_in
  mz_ulong যোগ_in;                // total number of bytes consumed so far

  unsigned অক্ষর *পরবর্তী_out;          // pointer to next byte to write
  unsigned পূর্ণসংখ্যা avail_out;           // number of bytes that can be written to next_out
  mz_ulong যোগ_out;               // total number of bytes produced so far

  অক্ষর *বার্তা;                        // error msg (unused)
  কাঠামো mz_internal_state *state;  // internal state, allocated by zalloc/zfree

  mz_alloc_func zalloc;             // optional heap allocation function (defaults to malloc)
  mz_free_func zfree;               // optional heap free function (defaults to free)
  শূন্য *opaque;                     // heap alloc function user pointer

  পূর্ণসংখ্যা তথ্য_type;                    // data_type (unused)
  mz_ulong adler;                   // adler32 of the source or uncompressed data
  mz_ulong reserved;                // not used
} mz_stream;

প্রকারলেখ mz_stream *mz_streamp;

// Returns the version string of miniz.c.
MINIZ_STATIC ধ্রুবক অক্ষর *mz_version(শূন্য);

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
MINIZ_STATIC পূর্ণসংখ্যা mz_deflateInit(mz_streamp pStream, পূর্ণসংখ্যা level);

// mz_deflateInit2() is like mz_deflate(), except with more control:
// Additional parameters:
//   method must be MZ_DEFLATED
//   window_bits must be MZ_DEFAULT_WINDOW_BITS (to wrap the deflate stream with zlib header/adler-32 footer) or -MZ_DEFAULT_WINDOW_BITS (raw deflate/no header or footer)
//   mem_level must be between [1, 9] (it's checked but ignored by miniz.c)
MINIZ_STATIC পূর্ণসংখ্যা mz_deflateInit2(mz_streamp pStream, পূর্ণসংখ্যা level, পূর্ণসংখ্যা method, পূর্ণসংখ্যা window_bits, পূর্ণসংখ্যা mem_level, পূর্ণসংখ্যা strategy);

// Quickly resets a compressor without having to reallocate anything. Same as calling mz_deflateEnd() followed by mz_deflateInit()/mz_deflateInit2().
MINIZ_STATIC পূর্ণসংখ্যা mz_deflateReset(mz_streamp pStream);

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
MINIZ_STATIC পূর্ণসংখ্যা mz_deflate(mz_streamp pStream, পূর্ণসংখ্যা flush);

// mz_deflateEnd() deinitializes a compressor:
// Return values:
//  MZ_OK on success.
//  MZ_STREAM_ERROR if the stream is bogus.
MINIZ_STATIC পূর্ণসংখ্যা mz_deflateEnd(mz_streamp pStream);

// mz_deflateBound() returns a (very) conservative upper bound on the amount of data that could be generated by deflate(), assuming flush is set to only MZ_NO_FLUSH or MZ_FINISH.
MINIZ_STATIC mz_ulong mz_deflateBound(mz_streamp pStream, mz_ulong source_len);

// Single-call compression functions mz_compress() and mz_compress2():
// Returns MZ_OK on success, or one of the error codes from mz_deflate() on failure.
MINIZ_STATIC পূর্ণসংখ্যা mz_compress(unsigned অক্ষর *pDest, mz_ulong *pDest_len, ধ্রুবক unsigned অক্ষর *pSource, mz_ulong source_len);
MINIZ_STATIC পূর্ণসংখ্যা mz_compress2(unsigned অক্ষর *pDest, mz_ulong *pDest_len, ধ্রুবক unsigned অক্ষর *pSource, mz_ulong source_len, পূর্ণসংখ্যা level);

// mz_compressBound() returns a (very) conservative upper bound on the amount of data that could be generated by calling mz_compress().
MINIZ_STATIC mz_ulong mz_compressBound(mz_ulong source_len);

#endif /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#ifndef MINIZ_NO_INFLATE_APIS

// Initializes a decompressor.
MINIZ_STATIC পূর্ণসংখ্যা mz_inflateInit(mz_streamp pStream);

// mz_inflateInit2() is like mz_inflateInit() with an additional option that controls the window size and whether or not the stream has been wrapped with a zlib header/footer:
// window_bits must be MZ_DEFAULT_WINDOW_BITS (to parse zlib header/footer) or -MZ_DEFAULT_WINDOW_BITS (raw deflate).
MINIZ_STATIC পূর্ণসংখ্যা mz_inflateInit2(mz_streamp pStream, পূর্ণসংখ্যা window_bits);

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
MINIZ_STATIC পূর্ণসংখ্যা mz_inflate(mz_streamp pStream, পূর্ণসংখ্যা flush);

// Deinitializes a decompressor.
MINIZ_STATIC পূর্ণসংখ্যা mz_inflateEnd(mz_streamp pStream);

// Single-call decompression.
// Returns MZ_OK on success, or one of the error codes from mz_inflate() on failure.
MINIZ_STATIC পূর্ণসংখ্যা mz_uncompress(unsigned অক্ষর *pDest, mz_ulong *pDest_len, ধ্রুবক unsigned অক্ষর *pSource, mz_ulong source_len);
#endif /*#ifndef MINIZ_NO_INFLATE_APIS*/

// Returns a string description of the specified error code, or NULL if the error code is invalid.
MINIZ_STATIC ধ্রুবক অক্ষর *mz_error(পূর্ণসংখ্যা err);

// Redefine zlib-compatible names to miniz equivalents, so miniz.c can be used as a drop-in replacement for the subset of zlib that miniz.c supports.
// Define MINIZ_NO_ZLIB_COMPATIBLE_NAMES to disable zlib-compatibility if you use zlib in the same project.
#ifndef MINIZ_NO_ZLIB_COMPATIBLE_NAMES
  প্রকারলেখ unsigned অক্ষর Byte;
  প্রকারলেখ unsigned পূর্ণসংখ্যা uInt;
  প্রকারলেখ mz_ulong uLong;
  প্রকারলেখ Byte Bytef;
  প্রকারলেখ uInt uIntf;
  প্রকারলেখ অক্ষর charf;
  প্রকারলেখ পূর্ণসংখ্যা intf;
  প্রকারলেখ শূন্য *voidpf;
  প্রকারলেখ uLong uLongf;
  প্রকারলেখ শূন্য *voidp;
  প্রকারলেখ শূন্য *ধ্রুবক voidpc;
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
  #define Z_তথ্য_ERROR          MZ_তথ্য_ERROR
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

প্রকারলেখ unsigned অক্ষর mz_uint8;
প্রকারলেখ signed short mz_int16;
প্রকারলেখ unsigned short mz_uint16;
প্রকারলেখ unsigned পূর্ণসংখ্যা mz_uint32;
প্রকারলেখ unsigned পূর্ণসংখ্যা mz_uint;
প্রকারলেখ long long mz_int64;
প্রকারলেখ unsigned long long mz_uint64;
প্রকারলেখ পূর্ণসংখ্যা mz_bool;

#define MZ_FALSE (0)
#define MZ_TRUE (1)

// An attempt to work around MSVC's spammy "warning C4127: conditional expression is constant" message.
#ifdef _MSC_VER
   #define MZ_MACRO_END যখন (0, 0)
#অন্যথা
   #define MZ_MACRO_END যখন (0)
#endif

// ------------------- ZIP archive reading/writing

#ifndef MINIZ_NO_ARCHIVE_APIS

গণনা
{
  MZ_ZIP_MAX_IO_BUF_আকার = 64*1024,
  MZ_ZIP_MAX_ARCHIVE_FILENAME_আকার = 260,
  MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_আকার = 256
};

প্রকারলেখ কাঠামো
{
  mz_uint32 m_file_সূচক;
  mz_uint32 m_central_dir_ofs;
  mz_uint16 m_version_made_by;
  mz_uint16 m_version_needed;
  mz_uint16 m_bit_flag;
  mz_uint16 m_method;
#ifndef MINIZ_NO_TIME
  time_t m_time;
#endif
  mz_uint32 m_crc32;
  mz_uint64 m_comp_আকার;
  mz_uint64 m_uncomp_আকার;
  mz_uint16 m_internal_attr;
  mz_uint32 m_external_attr;
  mz_uint64 m_local_header_ofs;
  mz_uint32 m_comment_আকার;
  অক্ষর m_filename[MZ_ZIP_MAX_ARCHIVE_FILENAME_আকার];
  অক্ষর m_comment[MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_আকার];
} mz_zip_archive_file_stat;

প্রকারলেখ size_t (*mz_file_read_func)(শূন্য *pOpaque, mz_uint64 file_ofs, শূন্য *pBuf, size_t n);
প্রকারলেখ size_t (*mz_file_write_func)(শূন্য *pOpaque, mz_uint64 file_ofs, ধ্রুবক শূন্য *pBuf, size_t n);

কাঠামো mz_zip_internal_state_tag;
প্রকারলেখ কাঠামো mz_zip_internal_state_tag mz_zip_internal_state;

প্রকারলেখ গণনা
{
  MZ_ZIP_MODE_INVALID = 0,
  MZ_ZIP_MODE_READING = 1,
  MZ_ZIP_MODE_WRITING = 2,
  MZ_ZIP_MODE_WRITING_HAS_BEEN_FINALIZED = 3
} mz_zip_mode;

প্রকারলেখ কাঠামো mz_zip_archive_tag
{
  mz_uint64 m_archive_আকার;
  mz_uint64 m_central_directory_file_ofs;
  mz_uint m_যোগ_files;
  mz_zip_mode m_zip_mode;

  mz_uint m_file_offset_alignment;

  mz_alloc_func m_pAlloc;
  mz_free_func m_pFree;
  mz_realloc_func m_pRealloc;
  শূন্য *m_pAlloc_opaque;

  mz_file_read_func m_pRead;
  mz_file_write_func m_pWrite;
  শূন্য *m_pIO_opaque;

  mz_zip_internal_state *m_pState;

} mz_zip_archive;

প্রকারলেখ গণনা
{
  MZ_ZIP_FLAG_CASE_SENSITIVE                = 0x0100,
  MZ_ZIP_FLAG_IGNORE_PATH                   = 0x0200,
  MZ_ZIP_FLAG_COMPRESSED_তথ্য               = 0x0400,
  MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY = 0x0800
} mz_zip_flags;

// ZIP archive reading

// Inits a ZIP archive reader.
// These functions read and validate the archive's central directory.
MINIZ_STATIC mz_bool mz_zip_reader_init(mz_zip_archive *pZip, mz_uint64 আকার_2, mz_uint32 flags);
MINIZ_STATIC mz_bool mz_zip_reader_init_mem(mz_zip_archive *pZip, ধ্রুবক শূন্য *pMem, size_t আকার_2, mz_uint32 flags);

#ifndef MINIZ_NO_STDIO
MINIZ_STATIC mz_bool mz_zip_reader_init_file(mz_zip_archive *pZip, ধ্রুবক অক্ষর *pFilename, mz_uint32 flags);
#endif

// Returns the total number of files in the archive.
MINIZ_STATIC mz_uint mz_zip_reader_get_অঙ্ক_files(mz_zip_archive *pZip);

// Returns detailed information about an archive file entry.
MINIZ_STATIC mz_bool mz_zip_reader_file_stat(mz_zip_archive *pZip, mz_uint file_সূচক, mz_zip_archive_file_stat *pStat);

// Determines if an archive file entry is a directory entry.
MINIZ_STATIC mz_bool mz_zip_reader_is_file_a_directory(mz_zip_archive *pZip, mz_uint file_সূচক);
MINIZ_STATIC mz_bool mz_zip_reader_is_file_encrypted(mz_zip_archive *pZip, mz_uint file_সূচক);

// Retrieves the filename of an archive file entry.
// Returns the number of bytes written to pFilename, or if filename_buf_size is 0 this function returns the number of bytes needed to fully store the filename.
MINIZ_STATIC mz_uint mz_zip_reader_get_filename(mz_zip_archive *pZip, mz_uint file_সূচক, অক্ষর *pFilename, mz_uint filename_buf_আকার);

// Attempts to locates a file in the archive's central directory.
// Valid flags: MZ_ZIP_FLAG_CASE_SENSITIVE, MZ_ZIP_FLAG_IGNORE_PATH
// Returns -1 if the file cannot be found.
MINIZ_STATIC পূর্ণসংখ্যা mz_zip_reader_locate_file(mz_zip_archive *pZip, ধ্রুবক অক্ষর *pName, ধ্রুবক অক্ষর *pComment, mz_uint flags);

// Extracts a archive file to a memory buffer using no memory allocation.
MINIZ_STATIC mz_bool mz_zip_reader_extract_to_mem_no_alloc(mz_zip_archive *pZip, mz_uint file_সূচক, শূন্য *pBuf, size_t buf_আকার_2, mz_uint flags, শূন্য *pUser_read_buf, size_t user_read_buf_আকার);
MINIZ_STATIC mz_bool mz_zip_reader_extract_file_to_mem_no_alloc(mz_zip_archive *pZip, ধ্রুবক অক্ষর *pFilename, শূন্য *pBuf, size_t buf_আকার_2, mz_uint flags, শূন্য *pUser_read_buf, size_t user_read_buf_আকার);

// Extracts a archive file to a memory buffer.
MINIZ_STATIC mz_bool mz_zip_reader_extract_to_mem(mz_zip_archive *pZip, mz_uint file_সূচক, শূন্য *pBuf, size_t buf_আকার_2, mz_uint flags);
MINIZ_STATIC mz_bool mz_zip_reader_extract_file_to_mem(mz_zip_archive *pZip, ধ্রুবক অক্ষর *pFilename, শূন্য *pBuf, size_t buf_আকার_2, mz_uint flags);

// Extracts a archive file to a dynamically allocated heap buffer.
MINIZ_STATIC শূন্য *mz_zip_reader_extract_to_heap(mz_zip_archive *pZip, mz_uint file_সূচক, size_t *p_আকার, mz_uint flags);
MINIZ_STATIC শূন্য *mz_zip_reader_extract_file_to_heap(mz_zip_archive *pZip, ধ্রুবক অক্ষর *pFilename, size_t *p_আকার, mz_uint flags);

// Extracts a archive file using a callback function to output the file's data.
MINIZ_STATIC mz_bool mz_zip_reader_extract_to_callback(mz_zip_archive *pZip, mz_uint file_সূচক, mz_file_write_func pCallback, শূন্য *pOpaque, mz_uint flags);
MINIZ_STATIC mz_bool mz_zip_reader_extract_file_to_callback(mz_zip_archive *pZip, ধ্রুবক অক্ষর *pFilename, mz_file_write_func pCallback, শূন্য *pOpaque, mz_uint flags);

#ifndef MINIZ_NO_STDIO
// Extracts a archive file to a disk file and sets its last accessed and modified times.
// This function only extracts files, not archive directory records.
MINIZ_STATIC mz_bool mz_zip_reader_extract_to_file(mz_zip_archive *pZip, mz_uint file_সূচক, ধ্রুবক অক্ষর *pDst_filename, mz_uint flags);
MINIZ_STATIC mz_bool mz_zip_reader_extract_file_to_file(mz_zip_archive *pZip, ধ্রুবক অক্ষর *pArchive_filename, ধ্রুবক অক্ষর *pDst_filename, mz_uint flags);
#endif

// Ends archive reading, freeing all allocations, and closing the input archive file if mz_zip_reader_init_file() was used.
MINIZ_STATIC mz_bool mz_zip_reader_end(mz_zip_archive *pZip);

// ZIP archive writing

#ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

// Inits a ZIP archive writer.
MINIZ_STATIC mz_bool mz_zip_writer_init(mz_zip_archive *pZip, mz_uint64 existing_আকার);
MINIZ_STATIC mz_bool mz_zip_writer_init_heap(mz_zip_archive *pZip, size_t আকার_to_reserve_at_beginning, size_t initial_allocation_আকার);

#ifndef MINIZ_NO_STDIO
MINIZ_STATIC mz_bool mz_zip_writer_init_file(mz_zip_archive *pZip, ধ্রুবক অক্ষর *pFilename, mz_uint64 আকার_to_reserve_at_beginning);
#endif

// Converts a ZIP archive reader object into a writer object, to allow efficient in-place file appends to occur on an existing archive.
// For archives opened using mz_zip_reader_init_file, pFilename must be the archive's filename so it can be reopened for writing. If the file can't be reopened, mz_zip_reader_end() will be called.
// For archives opened using mz_zip_reader_init_mem, the memory block must be growable using the realloc callback (which defaults to realloc unless you've overridden it).
// Finally, for archives opened using mz_zip_reader_init, the mz_zip_archive's user provided m_pWrite function cannot be NULL.
// Note: In-place archive modification is not recommended unless you know what you're doing, because if execution stops or something goes wrong before
// the archive is finalized the file's central directory will be hosed.
MINIZ_STATIC mz_bool mz_zip_writer_init_from_reader(mz_zip_archive *pZip, ধ্রুবক অক্ষর *pFilename);

// Adds the contents of a memory buffer to an archive. These functions record the current local time into the archive.
// To add a directory entry, call this method with an archive name ending in a forwardslash with empty buffer.
// level_and_flags - compression level (0-10, see MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or just set to MZ_DEFAULT_COMPRESSION.
MINIZ_STATIC mz_bool mz_zip_writer_add_mem(mz_zip_archive *pZip, ধ্রুবক অক্ষর *pArchive_name, ধ্রুবক শূন্য *pBuf, size_t buf_আকার_2, mz_uint level_and_flags);
MINIZ_STATIC mz_bool mz_zip_writer_add_mem_ex(mz_zip_archive *pZip, ধ্রুবক অক্ষর *pArchive_name, ধ্রুবক শূন্য *pBuf, size_t buf_আকার_2, ধ্রুবক শূন্য *pComment, mz_uint16 comment_আকার, mz_uint level_and_flags, mz_uint64 uncomp_আকার, mz_uint32 uncomp_crc32);

#ifndef MINIZ_NO_STDIO
// Adds the contents of a disk file to an archive. This function also records the disk file's modified time into the archive.
// level_and_flags - compression level (0-10, see MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or just set to MZ_DEFAULT_COMPRESSION.
MINIZ_STATIC mz_bool mz_zip_writer_add_file(mz_zip_archive *pZip, ধ্রুবক অক্ষর *pArchive_name, ধ্রুবক অক্ষর *pSrc_filename, ধ্রুবক শূন্য *pComment, mz_uint16 comment_আকার, mz_uint level_and_flags);
#endif

// Adds a file to an archive by fully cloning the data from another archive.
// This function fully clones the source file's compressed data (no recompression), along with its full filename, extra data, and comment fields.
MINIZ_STATIC mz_bool mz_zip_writer_add_from_zip_reader(mz_zip_archive *pZip, mz_zip_archive *pSource_zip, mz_uint file_সূচক);

// Finalizes the archive by writing the central directory records followed by the end of central directory record.
// After an archive is finalized, the only valid call on the mz_zip_archive struct is mz_zip_writer_end().
// An archive must be manually finalized by calling this function for it to be valid.
MINIZ_STATIC mz_bool mz_zip_writer_finalize_archive(mz_zip_archive *pZip);
MINIZ_STATIC mz_bool mz_zip_writer_finalize_heap_archive(mz_zip_archive *pZip, শূন্য **pBuf, size_t *p_আকার);

// Ends archive writing, freeing all allocations, and closing the output file if mz_zip_writer_init_file() was used.
// Note for the archive to be valid, it must have been finalized before ending.
MINIZ_STATIC mz_bool mz_zip_writer_end(mz_zip_archive *pZip);

// Misc. high-level helper functions:

// mz_zip_add_mem_to_archive_file_in_place() efficiently (but not atomically) appends a memory blob to a ZIP archive.
// level_and_flags - compression level (0-10, see MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or just set to MZ_DEFAULT_COMPRESSION.
MINIZ_STATIC mz_bool mz_zip_add_mem_to_archive_file_in_place(ধ্রুবক অক্ষর *pZip_filename, ধ্রুবক অক্ষর *pArchive_name, ধ্রুবক শূন্য *pBuf, size_t buf_আকার_2, ধ্রুবক শূন্য *pComment, mz_uint16 comment_আকার, mz_uint level_and_flags);

// Reads a single file from an archive into a heap block.
// Returns NULL on failure.
MINIZ_STATIC শূন্য *mz_zip_extract_archive_file_to_heap(ধ্রুবক অক্ষর *pZip_filename, ধ্রুবক অক্ষর *pArchive_name, size_t *p_আকার, mz_uint zip_flags);

#endif // #ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

#endif // #ifndef MINIZ_NO_ARCHIVE_APIS

// ------------------- Low-level Decompression API Definitions
#ifndef MINIZ_NO_INFLATE_APIS

// Decompression flags used by tinfl_decompress().
// TINFL_FLAG_PARSE_ZLIB_HEADER: If set, the input has a valid zlib header and ends with an adler32 checksum (it's a valid zlib stream). Otherwise, the input is a raw deflate stream.
// TINFL_FLAG_HAS_MORE_INPUT: If set, there are more input bytes available beyond the end of the supplied input buffer. If clear, the input buffer contains all remaining input.
// TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF: If set, the output buffer is large enough to hold the entire decompressed stream. If clear, the output buffer is at least the size of the dictionary (typically 32KB).
// TINFL_FLAG_COMPUTE_ADLER32: Force adler-32 checksum computation of the decompressed bytes.
গণনা
{
  TINFL_FLAG_PARSE_ZLIB_HEADER = 1,
  TINFL_FLAG_HAS_MORE_প্রবেশ = 2,
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
MINIZ_STATIC শূন্য *tinfl_decompress_mem_to_heap(ধ্রুবক শূন্য *pSrc_buf, size_t src_buf_len, size_t *pOut_len, পূর্ণসংখ্যা flags);

// tinfl_decompress_mem_to_mem() decompresses a block in memory to another block in memory.
// Returns TINFL_DECOMPRESS_MEM_TO_MEM_FAILED on failure, or the number of bytes written on success.
#define TINFL_DECOMPRESS_MEM_TO_MEM_FAILED ((size_t)(-1))
MINIZ_STATIC size_t tinfl_decompress_mem_to_mem(শূন্য *pOut_buf, size_t out_buf_len, ধ্রুবক শূন্য *pSrc_buf, size_t src_buf_len, পূর্ণসংখ্যা flags);

// tinfl_decompress_mem_to_callback() decompresses a block in memory to an internal 32KB buffer, and a user provided callback function will be called to flush the buffer.
// Returns 1 on success or 0 on failure.
প্রকারলেখ পূর্ণসংখ্যা (*tinfl_put_buf_func_ptr)(ধ্রুবক শূন্য* pBuf, পূর্ণসংখ্যা len, শূন্য *pUser);
MINIZ_STATIC পূর্ণসংখ্যা tinfl_decompress_mem_to_callback(ধ্রুবক শূন্য *pIn_buf, size_t *p_In_buf_আকার, tinfl_put_buf_func_ptr pPut_buf_func, শূন্য *pPut_buf_user, পূর্ণসংখ্যা flags);

কাঠামো tinfl_decompressor_tag; প্রকারলেখ কাঠামো tinfl_decompressor_tag tinfl_decompressor;

// Max size of LZ dictionary.
#define TINFL_LZ_DICT_আকার 32768

// Return status.
প্রকারলেখ গণনা
{
  TINFL_STATUS_BAD_PARAM = -3,
  TINFL_STATUS_ADLER32_MISMATCH = -2,
  TINFL_STATUS_FAILED = -1,
  TINFL_STATUS_DONE = 0,
  TINFL_STATUS_NEEDS_MORE_প্রবেশ = 1,
  TINFL_STATUS_HAS_MORE_OUTPUT = 2
} tinfl_status;

// Initializes the decompressor to its initial state.
#define tinfl_init(r) করো { (r)->m_state = 0; } MZ_MACRO_END
#define tinfl_get_adler32(r) (r)->m_check_adler32

// Main low-level decompressor coroutine function. This is the only function actually needed for decompression. All the other functions are just high-level helpers for improved usability.
// This is a universal API, i.e. it can be used as a building block to build any desired higher level decompression API. In the limit case, it can be called once per every byte input or output.
MINIZ_STATIC tinfl_status tinfl_decompress(tinfl_decompressor *r, ধ্রুবক mz_uint8 *p_In_buf_পরবর্তী, size_t *p_In_buf_আকার, mz_uint8 *pOut_buf_start, mz_uint8 *p_Out_buf_পরবর্তী, size_t *p_Out_buf_আকার, ধ্রুবক mz_uint32 decomp_flags);

// Internal/private bits follow.
গণনা
{
  TINFL_MAX_HUFF_TABLES = 3, TINFL_MAX_HUFF_SYMBOLS_0 = 288, TINFL_MAX_HUFF_SYMBOLS_1 = 32, TINFL_MAX_HUFF_SYMBOLS_2 = 19,
  TINFL_FAST_LOOKUP_BITS = 10, TINFL_FAST_LOOKUP_আকার = 1 << TINFL_FAST_LOOKUP_BITS
};

প্রকারলেখ কাঠামো
{
  mz_uint8 m_code_আকার[TINFL_MAX_HUFF_SYMBOLS_0];
  mz_int16 m_look_up[TINFL_FAST_LOOKUP_আকার], m_বৃক্ষ[TINFL_MAX_HUFF_SYMBOLS_0 * 2];
} tinfl_huff_table;

#যদি MINIZ_HAS_64BIT_REGISTERS
  #define TINFL_USE_64BIT_BITBUF 1
#endif

#যদি TINFL_USE_64BIT_BITBUF
  প্রকারলেখ mz_uint64 tinfl_bit_buf_t;
  #define TINFL_BITBUF_আকার (64)
#অন্যথা
  প্রকারলেখ mz_uint32 tinfl_bit_buf_t;
  #define TINFL_BITBUF_আকার (32)
#endif

কাঠামো tinfl_decompressor_tag
{
  mz_uint32 m_state, m_অঙ্ক_bits, m_zhdr0, m_zhdr1, m_z_adler32, m_final, m_type, m_check_adler32, m_dist, m_গণক, m_অঙ্ক_extra, m_table_sizes[TINFL_MAX_HUFF_TABLES];
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
গণনা
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
গণনা
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
MINIZ_STATIC শূন্য *tdefl_compress_mem_to_heap(ধ্রুবক শূন্য *pSrc_buf, size_t src_buf_len, size_t *pOut_len, পূর্ণসংখ্যা flags);

// tdefl_compress_mem_to_mem() compresses a block in memory to another block in memory.
// Returns 0 on failure.
MINIZ_STATIC size_t tdefl_compress_mem_to_mem(শূন্য *pOut_buf, size_t out_buf_len, ধ্রুবক শূন্য *pSrc_buf, size_t src_buf_len, পূর্ণসংখ্যা flags);
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
MINIZ_STATIC শূন্য *tdefl_write_image_to_png_file_in_memory_ex(ধ্রুবক শূন্য *pImage, পূর্ণসংখ্যা w, পূর্ণসংখ্যা h, পূর্ণসংখ্যা অঙ্ক_chans, পূর্ণসংখ্যা bpl, size_t *pLen_out, mz_uint level, mz_bool flip, mz_uint8 *plte, পূর্ণসংখ্যা plte_আকার, mz_uint8 *trns, পূর্ণসংখ্যা trns_আকার);
#ifndef MINIZ_SDL_NOUNUSED
MINIZ_STATIC শূন্য *tdefl_write_image_to_png_file_in_memory(ধ্রুবক শূন্য *pImage, পূর্ণসংখ্যা w, পূর্ণসংখ্যা h, পূর্ণসংখ্যা অঙ্ক_chans, পূর্ণসংখ্যা bpl, size_t *pLen_out);
#endif

// Output stream interface. The compressor uses this interface to write compressed data. It'll typically be called TDEFL_OUT_BUF_SIZE at a time.
প্রকারলেখ mz_bool (*tdefl_put_buf_func_ptr)(ধ্রুবক শূন্য* pBuf, পূর্ণসংখ্যা len, শূন্য *pUser);

#ifndef MINIZ_SDL_NOUNUSED
// tdefl_compress_mem_to_output() compresses a block to an output stream. The above helpers use this function internally.
MINIZ_STATIC mz_bool tdefl_compress_mem_to_output(ধ্রুবক শূন্য *pBuf, size_t buf_len, tdefl_put_buf_func_ptr pPut_buf_func, শূন্য *pPut_buf_user, পূর্ণসংখ্যা flags);
#endif

//enum { TDEFL_MAX_HUFF_TABLES = 3, TDEFL_MAX_HUFF_SYMBOLS_0 = 288, TDEFL_MAX_HUFF_SYMBOLS_1 = 32, TDEFL_MAX_HUFF_SYMBOLS_2 = 19, TDEFL_LZ_DICT_SIZE = 32768, TDEFL_LZ_DICT_SIZE_MASK = TDEFL_LZ_DICT_SIZE - 1, TDEFL_MIN_MATCH_LEN = 3, TDEFL_MAX_MATCH_LEN = 258 };
#define TDEFL_MAX_HUFF_TABLES	3
#define TDEFL_MAX_HUFF_SYMBOLS_0 288
#define TDEFL_MAX_HUFF_SYMBOLS_1 32
#define TDEFL_MAX_HUFF_SYMBOLS_2 19
#define TDEFL_LZ_DICT_আকার 32768
#define TDEFL_LZ_DICT_আকার_MASK	( TDEFL_LZ_DICT_আকার - 1 )
#define TDEFL_MIN_MATCH_LEN	3
#define TDEFL_MAX_MATCH_LEN 258

// TDEFL_OUT_BUF_SIZE MUST be large enough to hold a single entire compressed output block (using static/fixed Huffman codes).
#যদি TDEFL_LESS_MEMORY
গণনা { TDEFL_LZ_CODE_BUF_আকার = 24 * 1024, TDEFL_OUT_BUF_আকার = (TDEFL_LZ_CODE_BUF_আকার * 13 ) / 10, TDEFL_MAX_HUFF_SYMBOLS = 288, TDEFL_LZ_HASH_BITS = 12, TDEFL_LEVEL1_HASH_আকার_MASK = 4095, TDEFL_LZ_HASH_SHIFT = (TDEFL_LZ_HASH_BITS + 2) / 3, TDEFL_LZ_HASH_আকার = 1 << TDEFL_LZ_HASH_BITS };
#অন্যথা
গণনা { TDEFL_LZ_CODE_BUF_আকার = 64 * 1024, TDEFL_OUT_BUF_আকার = (TDEFL_LZ_CODE_BUF_আকার * 13 ) / 10, TDEFL_MAX_HUFF_SYMBOLS = 288, TDEFL_LZ_HASH_BITS = 15, TDEFL_LEVEL1_HASH_আকার_MASK = 4095, TDEFL_LZ_HASH_SHIFT = (TDEFL_LZ_HASH_BITS + 2) / 3, TDEFL_LZ_HASH_আকার = 1 << TDEFL_LZ_HASH_BITS };
#endif

// The low-level tdefl functions below may be used directly if the above helper functions aren't flexible enough. The low-level functions don't make any heap allocations, unlike the above helper functions.
প্রকারলেখ গণনা
{
  TDEFL_STATUS_BAD_PARAM = -2,
  TDEFL_STATUS_PUT_BUF_FAILED = -1,
  TDEFL_STATUS_OKAY = 0,
  TDEFL_STATUS_DONE = 1,
} tdefl_status;

// Must map to MZ_NO_FLUSH, MZ_SYNC_FLUSH, etc. enums
প্রকারলেখ গণনা
{
  TDEFL_NO_FLUSH = 0,
  TDEFL_SYNC_FLUSH = 2,
  TDEFL_FULL_FLUSH = 3,
  TDEFL_FINISH = 4
} tdefl_flush;

// tdefl's compression state structure.
প্রকারলেখ কাঠামো
{
  tdefl_put_buf_func_ptr m_pPut_buf_func;
  শূন্য *m_pPut_buf_user;
  mz_uint m_flags, m_max_probes[2];
  পূর্ণসংখ্যা m_greedy_parsing;
  mz_uint m_adler32, m_lookahead_pos, m_lookahead_আকার, m_dict_আকার;
  mz_uint8 *m_pLZ_code_buf, *m_pLZ_flags, *m_pOutput_buf, *m_pOutput_buf_end;
  mz_uint m_অঙ্ক_flags_বাম, m_যোগ_lz_bytes, m_lz_code_buf_dict_pos, m_bits_in, m_bit_বাফার;
  mz_uint m_saved_match_dist, m_saved_match_len, m_saved_lit, m_output_flush_ofs, m_output_flush_remaining, m_finished, m_block_সূচক, m_wants_to_finish;
  tdefl_status m_পূর্ব_return_status;
  ধ্রুবক শূন্য *m_pIn_buf;
  শূন্য *m_pOut_buf;
  size_t *m_p_In_buf_আকার, *m_p_Out_buf_আকার;
  tdefl_flush m_flush;
  ধ্রুবক mz_uint8 *m_pSrc;
  size_t m_src_buf_বাম, m_out_buf_ofs;
  mz_uint8 m_dict[TDEFL_LZ_DICT_আকার + TDEFL_MAX_MATCH_LEN - 1];
  mz_uint16 m_huff_গুনতি[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint16 m_huff_codes[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint8 m_huff_code_sizes[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint8 m_lz_code_buf[TDEFL_LZ_CODE_BUF_আকার];
  mz_uint16 m_পরবর্তী[TDEFL_LZ_DICT_আকার];
  mz_uint16 m_hash[TDEFL_LZ_HASH_আকার];
  mz_uint8 m_output_buf[TDEFL_OUT_BUF_আকার];
} tdefl_compressor;

// Initializes the compressor.
// There is no corresponding deinit() function because the tdefl API's do not dynamically allocate memory.
// pBut_buf_func: If NULL, output data will be supplied to the specified callback. In this case, the user should call the tdefl_compress_buffer() API for compression.
// If pBut_buf_func is NULL the user should always call the tdefl_compress() API.
// flags: See the above enums (TDEFL_HUFFMAN_ONLY, TDEFL_WRITE_ZLIB_HEADER, etc.)
MINIZ_STATIC tdefl_status tdefl_init(tdefl_compressor *d, tdefl_put_buf_func_ptr pPut_buf_func, শূন্য *pPut_buf_user, পূর্ণসংখ্যা flags);

// Compresses a block of data, consuming as much of the specified input buffer as possible, and writing as much compressed data to the specified output buffer as possible.
MINIZ_STATIC tdefl_status tdefl_compress(tdefl_compressor *d, ধ্রুবক শূন্য *pIn_buf, size_t *p_In_buf_আকার, শূন্য *pOut_buf, size_t *p_Out_buf_আকার, tdefl_flush flush);

// tdefl_compress_buffer() is only usable when the tdefl_init() is called with a non-NULL tdefl_put_buf_func_ptr.
// tdefl_compress_buffer() always consumes the entire input buffer.
MINIZ_STATIC tdefl_status tdefl_compress_বাফার(tdefl_compressor *d, ধ্রুবক শূন্য *pIn_buf, size_t in_buf_আকার, tdefl_flush flush);

#ifndef MINIZ_SDL_NOUNUSED
MINIZ_STATIC tdefl_status tdefl_get_পূর্ব_return_status(tdefl_compressor *d);
MINIZ_STATIC mz_uint32 tdefl_get_adler32(tdefl_compressor *d);
#endif

// Can't use tdefl_create_comp_flags_from_zip_params if MINIZ_NO_ZLIB_APIS isn't defined, because it uses some of its macros.
#ifndef MINIZ_NO_ZLIB_APIS
// Create tdefl_compress() flags given zlib-style compression parameters.
// level may range from [0,10] (where 10 is absolute max compression, but may be much slower on some files)
// window_bits may be -15 (raw deflate) or 15 (zlib)
// strategy may be either MZ_DEFAULT_STRATEGY, MZ_FILTERED, MZ_HUFFMAN_ONLY, MZ_RLE, or MZ_FIXED
MINIZ_STATIC mz_uint tdefl_create_comp_flags_from_zip_params(পূর্ণসংখ্যা level, পূর্ণসংখ্যা window_bits, পূর্ণসংখ্যা strategy);
#endif // #ifndef MINIZ_NO_ZLIB_APIS

#endif /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#ifdef __cplusplus
}
#endif

#endif // MINIZ_HEADER_INCLUDED

// ------------------- End of Header: Implementation follows. (If you only want the header, define MINIZ_HEADER_FILE_ONLY.)

#ifndef MINIZ_HEADER_FILE_ONLY

#ifdef _MSC_VER
#pragma warning (ঠেলো)
#pragma warning (disable:4505) // unreferenced local function has been removed
#endif

প্রকারলেখ unsigned অক্ষর mz_validate_uint16[আকার(mz_uint16)==2 ? 1 : -1];
প্রকারলেখ unsigned অক্ষর mz_validate_uint32[আকার(mz_uint32)==4 ? 1 : -1];
প্রকারলেখ unsigned অক্ষর mz_validate_uint64[আকার(mz_uint64)==8 ? 1 : -1];

/*#include <string.h>*/

#ifndef MZ_ASSERT
#অন্তর্ভাব <assert.h>
#define MZ_ASSERT(x) প্রতিজ্ঞা(x)
#endif

#ifdef MINIZ_NO_MALLOC
  #define MZ_MALLOC(x) ফাঁকা
  #define MZ_FREE(x) (শূন্য)x, ((শূন্য)0)
  #define MZ_REALLOC(p, x) ফাঁকা
#নতুবা_যদি defined(MINIZ_SDL_MALLOC)
  #define MZ_MALLOC(x) SDL_malloc(x)
  #define MZ_FREE(x) SDL_free(x)
  #define MZ_REALLOC(p, x) SDL_realloc(p, x)
#অন্যথা
  #define MZ_MALLOC(x) malloc(x)
  #define MZ_FREE(x) মুক্ত(x)
  #define MZ_REALLOC(p, x) realloc(p, x)
#endif

#define MZ_MAX(a,b) (((a)>(b))?(a):(b))
#define MZ_MIN(a,b) (((a)<(b))?(a):(b))
#define MZ_CLEAR_OBJ(obj) memset(&(obj), 0, আকার(obj))
#define MZ_CLEAR_ARR(obj) memset((obj), 0, আকার(obj))
#define MZ_CLEAR_PTR(obj) memset((obj), 0, আকার(*obj))

#যদি MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  #define MZ_READ_LE16(p) *((ধ্রুবক mz_uint16 *)(p))
  #define MZ_READ_LE32(p) *((ধ্রুবক mz_uint32 *)(p))
#অন্যথা
  #define MZ_READ_LE16(p) ((mz_uint32)(((ধ্রুবক mz_uint8 *)(p))[0]) | ((mz_uint32)(((ধ্রুবক mz_uint8 *)(p))[1]) << 8U))
  #define MZ_READ_LE32(p) ((mz_uint32)(((ধ্রুবক mz_uint8 *)(p))[0]) | ((mz_uint32)(((ধ্রুবক mz_uint8 *)(p))[1]) << 8U) | ((mz_uint32)(((ধ্রুবক mz_uint8 *)(p))[2]) << 16U) | ((mz_uint32)(((ধ্রুবক mz_uint8 *)(p))[3]) << 24U))
#endif

#ifdef _MSC_VER
  #define MZ_FORCEINLINE __forceinline
#নতুবা_যদি defined(__GNUC__)
  #define MZ_FORCEINLINE অন্তঃরেখ __attribute__((__always_inline__))
#অন্যথা
  #define MZ_FORCEINLINE অন্তঃরেখ
#endif

#ifdef __cplusplus
  বাহ্যিক "C" {
#endif

// ------------------- zlib-style API's

mz_ulong mz_adler32(mz_ulong adler, ধ্রুবক unsigned অক্ষর *ptr, size_t buf_len)
{
  mz_uint32 i, s1 = (mz_uint32)(adler & 0xffff), s2 = (mz_uint32)(adler >> 16); size_t block_len = buf_len % 5552;
  যদি (!ptr) ফেরত MZ_ADLER32_INIT;
  যখন (buf_len) {
    জন্য (i = 0; i + 7 < block_len; i += 8, ptr += 8) {
      s1 += ptr[0]; s2 += s1; s1 += ptr[1]; s2 += s1; s1 += ptr[2]; s2 += s1; s1 += ptr[3]; s2 += s1;
      s1 += ptr[4]; s2 += s1; s1 += ptr[5]; s2 += s1; s1 += ptr[6]; s2 += s1; s1 += ptr[7]; s2 += s1;
    }
    জন্য ( ; i < block_len; ++i) { s1 += *ptr++; s2 += s1; }
    s1 %= 65521U; s2 %= 65521U; buf_len -= block_len; block_len = 5552;
  }
  ফেরত (s2 << 16) + s1;
}

// Karl Malbrain's compact CRC-32. See "A compact CCITT crc16 and crc32 C implementation that balances processor cache usage against speed": http://www.geocities.com/malbrain/
mz_ulong mz_crc32(mz_ulong crc, ধ্রুবক mz_uint8 *ptr, size_t buf_len)
{
  স্থির ধ্রুবক mz_uint32 s_crc32[16] = { 0, 0x1db71064, 0x3b6e20c8, 0x26d930ac, 0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
    0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c, 0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c };
  mz_uint32 crcu32 = (mz_uint32)crc;
  যদি (!ptr) ফেরত MZ_CRC32_INIT;
  crcu32 = ~crcu32; যখন (buf_len--) { mz_uint8 b = *ptr++; crcu32 = (crcu32 >> 4) ^ s_crc32[(crcu32 & 0xF) ^ (b & 0xF)]; crcu32 = (crcu32 >> 4) ^ s_crc32[(crcu32 & 0xF) ^ (b >> 4)]; }
  ফেরত ~crcu32;
}

MINIZ_STATIC শূন্য mz_free(শূন্য *p)
{
  MZ_FREE(p);
}

#ifndef MINIZ_NO_ZLIB_APIS

স্থির শূন্য *def_alloc_func(শূন্য *opaque, size_t বস্তুসমূহ, size_t আকার_2) { (শূন্য)opaque, (শূন্য)বস্তুসমূহ, (শূন্য)আকার_2; ফেরত MZ_MALLOC(বস্তুসমূহ * আকার_2); }
স্থির শূন্য def_free_func(শূন্য *opaque, শূন্য *address) { (শূন্য)opaque, (শূন্য)address; MZ_FREE(address); }
স্থির শূন্য *def_realloc_func(শূন্য *opaque, শূন্য *address, size_t বস্তুসমূহ, size_t আকার_2) { (শূন্য)opaque, (শূন্য)address, (শূন্য)বস্তুসমূহ, (শূন্য)আকার_2; ফেরত MZ_REALLOC(address, বস্তুসমূহ * আকার_2); }

ধ্রুবক অক্ষর *mz_version(শূন্য)
{
  ফেরত MZ_VERSION;
}

#ifndef MINIZ_NO_DEFLATE_APIS

পূর্ণসংখ্যা mz_deflateInit(mz_streamp pStream, পূর্ণসংখ্যা level)
{
  ফেরত mz_deflateInit2(pStream, level, MZ_DEFLATED, MZ_DEFAULT_WINDOW_BITS, 9, MZ_DEFAULT_STRATEGY);
}

পূর্ণসংখ্যা mz_deflateInit2(mz_streamp pStream, পূর্ণসংখ্যা level, পূর্ণসংখ্যা method, পূর্ণসংখ্যা window_bits, পূর্ণসংখ্যা mem_level, পূর্ণসংখ্যা strategy)
{
  tdefl_compressor *pComp;
  mz_uint comp_flags = TDEFL_COMPUTE_ADLER32 | tdefl_create_comp_flags_from_zip_params(level, window_bits, strategy);

  যদি (!pStream) ফেরত MZ_STREAM_ERROR;
  যদি ((method != MZ_DEFLATED) || ((mem_level < 1) || (mem_level > 9)) || ((window_bits != MZ_DEFAULT_WINDOW_BITS) && (-window_bits != MZ_DEFAULT_WINDOW_BITS))) ফেরত MZ_PARAM_ERROR;

  pStream->তথ্য_type = 0;
  pStream->adler = MZ_ADLER32_INIT;
  pStream->বার্তা = ফাঁকা;
  pStream->reserved = 0;
  pStream->যোগ_in = 0;
  pStream->যোগ_out = 0;
  যদি (!pStream->zalloc) pStream->zalloc = def_alloc_func;
  যদি (!pStream->zfree) pStream->zfree = def_free_func;

  pComp = (tdefl_compressor *)pStream->zalloc(pStream->opaque, 1, আকার(tdefl_compressor));
  যদি (!pComp)
    ফেরত MZ_MEM_ERROR;

  pStream->state = (কাঠামো mz_internal_state *)pComp;

  যদি (tdefl_init(pComp, ফাঁকা, ফাঁকা, comp_flags) != TDEFL_STATUS_OKAY)
  {
    mz_deflateEnd(pStream);
    ফেরত MZ_PARAM_ERROR;
  }

  ফেরত MZ_OK;
}

পূর্ণসংখ্যা mz_deflateReset(mz_streamp pStream)
{
  যদি ((!pStream) || (!pStream->state) || (!pStream->zalloc) || (!pStream->zfree)) ফেরত MZ_STREAM_ERROR;
  pStream->যোগ_in = pStream->যোগ_out = 0;
  tdefl_init((tdefl_compressor*)pStream->state, ফাঁকা, ফাঁকা, ((tdefl_compressor*)pStream->state)->m_flags);
  ফেরত MZ_OK;
}

পূর্ণসংখ্যা mz_deflate(mz_streamp pStream, পূর্ণসংখ্যা flush)
{
  size_t in_bytes, out_bytes;
  mz_ulong orig_যোগ_in, orig_যোগ_out;
  পূর্ণসংখ্যা mz_status = MZ_OK;

  যদি ((!pStream) || (!pStream->state) || (flush < 0) || (flush > MZ_FINISH) || (!pStream->পরবর্তী_out)) ফেরত MZ_STREAM_ERROR;
  যদি (!pStream->avail_out) ফেরত MZ_BUF_ERROR;

  যদি (flush == MZ_PARTIAL_FLUSH) flush = MZ_SYNC_FLUSH;

  যদি (((tdefl_compressor*)pStream->state)->m_পূর্ব_return_status == TDEFL_STATUS_DONE)
    ফেরত (flush == MZ_FINISH) ? MZ_STREAM_END : MZ_BUF_ERROR;

  orig_যোগ_in = pStream->যোগ_in; orig_যোগ_out = pStream->যোগ_out;
  জন্য ( ; ; )
  {
    tdefl_status defl_status;
    in_bytes = pStream->avail_in; out_bytes = pStream->avail_out;

    defl_status = tdefl_compress((tdefl_compressor*)pStream->state, pStream->পরবর্তী_in, &in_bytes, pStream->পরবর্তী_out, &out_bytes, (tdefl_flush)flush);
    pStream->পরবর্তী_in += (mz_uint)in_bytes; pStream->avail_in -= (mz_uint)in_bytes;
    pStream->যোগ_in += (mz_uint)in_bytes; pStream->adler = tdefl_get_adler32((tdefl_compressor*)pStream->state);

    pStream->পরবর্তী_out += (mz_uint)out_bytes; pStream->avail_out -= (mz_uint)out_bytes;
    pStream->যোগ_out += (mz_uint)out_bytes;

    যদি (defl_status < 0)
    {
      mz_status = MZ_STREAM_ERROR;
      বিরতি;
    }
    অন্যথা যদি (defl_status == TDEFL_STATUS_DONE)
    {
      mz_status = MZ_STREAM_END;
      বিরতি;
    }
    অন্যথা যদি (!pStream->avail_out)
      বিরতি;
    অন্যথা যদি ((!pStream->avail_in) && (flush != MZ_FINISH))
    {
      যদি ((flush) || (pStream->যোগ_in != orig_যোগ_in) || (pStream->যোগ_out != orig_যোগ_out))
        বিরতি;
      ফেরত MZ_BUF_ERROR; // Can't make forward progress without some input.
    }
  }
  ফেরত mz_status;
}

পূর্ণসংখ্যা mz_deflateEnd(mz_streamp pStream)
{
  যদি (!pStream) ফেরত MZ_STREAM_ERROR;
  যদি (pStream->state)
  {
    pStream->zfree(pStream->opaque, pStream->state);
    pStream->state = ফাঁকা;
  }
  ফেরত MZ_OK;
}

mz_ulong mz_deflateBound(mz_streamp pStream, mz_ulong source_len)
{
  (শূন্য)pStream;
  // This is really over conservative. (And lame, but it's actually pretty tricky to compute a true upper bound given the way tdefl's blocking works.)
  ফেরত MZ_MAX(128 + (source_len * 110) / 100, 128 + source_len + ((source_len / (31 * 1024)) + 1) * 5);
}

পূর্ণসংখ্যা mz_compress2(unsigned অক্ষর *pDest, mz_ulong *pDest_len, ধ্রুবক unsigned অক্ষর *pSource, mz_ulong source_len, পূর্ণসংখ্যা level)
{
  পূর্ণসংখ্যা status;
  mz_stream stream;
  memset(&stream, 0, আকার(stream));

  // In case mz_ulong is 64-bits (argh I hate longs).
  যদি ((source_len | *pDest_len) > 0xFFFFFFFFU) ফেরত MZ_PARAM_ERROR;

  stream.পরবর্তী_in = pSource;
  stream.avail_in = (mz_uint32)source_len;
  stream.পরবর্তী_out = pDest;
  stream.avail_out = (mz_uint32)*pDest_len;

  status = mz_deflateInit(&stream, level);
  যদি (status != MZ_OK) ফেরত status;

  status = mz_deflate(&stream, MZ_FINISH);
  যদি (status != MZ_STREAM_END)
  {
    mz_deflateEnd(&stream);
    ফেরত (status == MZ_OK) ? MZ_BUF_ERROR : status;
  }

  *pDest_len = stream.যোগ_out;
  ফেরত mz_deflateEnd(&stream);
}

পূর্ণসংখ্যা mz_compress(unsigned অক্ষর *pDest, mz_ulong *pDest_len, ধ্রুবক unsigned অক্ষর *pSource, mz_ulong source_len)
{
  ফেরত mz_compress2(pDest, pDest_len, pSource, source_len, MZ_DEFAULT_COMPRESSION);
}

mz_ulong mz_compressBound(mz_ulong source_len)
{
  ফেরত mz_deflateBound(ফাঁকা, source_len);
}

#endif /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#ifndef MINIZ_NO_INFLATE_APIS

প্রকারলেখ কাঠামো
{
  tinfl_decompressor m_decomp;
  mz_uint m_dict_ofs, m_dict_avail, m_first_call, m_has_flushed; পূর্ণসংখ্যা m_window_bits;
  mz_uint8 m_dict[TINFL_LZ_DICT_আকার];
  tinfl_status m_last_status;
} inflate_state;

পূর্ণসংখ্যা mz_inflateInit2(mz_streamp pStream, পূর্ণসংখ্যা window_bits)
{
  inflate_state *pDecomp;
  যদি (!pStream) ফেরত MZ_STREAM_ERROR;
  যদি ((window_bits != MZ_DEFAULT_WINDOW_BITS) && (-window_bits != MZ_DEFAULT_WINDOW_BITS)) ফেরত MZ_PARAM_ERROR;

  pStream->তথ্য_type = 0;
  pStream->adler = 0;
  pStream->বার্তা = ফাঁকা;
  pStream->যোগ_in = 0;
  pStream->যোগ_out = 0;
  pStream->reserved = 0;
  যদি (!pStream->zalloc) pStream->zalloc = def_alloc_func;
  যদি (!pStream->zfree) pStream->zfree = def_free_func;

  pDecomp = (inflate_state*)pStream->zalloc(pStream->opaque, 1, আকার(inflate_state));
  যদি (!pDecomp) ফেরত MZ_MEM_ERROR;

  pStream->state = (কাঠামো mz_internal_state *)pDecomp;

  tinfl_init(&pDecomp->m_decomp);
  pDecomp->m_dict_ofs = 0;
  pDecomp->m_dict_avail = 0;
  pDecomp->m_last_status = TINFL_STATUS_NEEDS_MORE_প্রবেশ;
  pDecomp->m_first_call = 1;
  pDecomp->m_has_flushed = 0;
  pDecomp->m_window_bits = window_bits;

  ফেরত MZ_OK;
}

পূর্ণসংখ্যা mz_inflateInit(mz_streamp pStream)
{
   ফেরত mz_inflateInit2(pStream, MZ_DEFAULT_WINDOW_BITS);
}

পূর্ণসংখ্যা mz_inflate(mz_streamp pStream, পূর্ণসংখ্যা flush)
{
  inflate_state* pState;
  mz_uint n, first_call, decomp_flags = TINFL_FLAG_COMPUTE_ADLER32;
  size_t in_bytes, out_bytes, orig_avail_in;
  tinfl_status status;

  যদি ((!pStream) || (!pStream->state)) ফেরত MZ_STREAM_ERROR;
  যদি (flush == MZ_PARTIAL_FLUSH) flush = MZ_SYNC_FLUSH;
  যদি ((flush) && (flush != MZ_SYNC_FLUSH) && (flush != MZ_FINISH)) ফেরত MZ_STREAM_ERROR;

  pState = (inflate_state*)pStream->state;
  যদি (pState->m_window_bits > 0) decomp_flags |= TINFL_FLAG_PARSE_ZLIB_HEADER;
  orig_avail_in = pStream->avail_in;

  first_call = pState->m_first_call; pState->m_first_call = 0;
  যদি (pState->m_last_status < 0) ফেরত MZ_তথ্য_ERROR;

  যদি (pState->m_has_flushed && (flush != MZ_FINISH)) ফেরত MZ_STREAM_ERROR;
  pState->m_has_flushed |= (flush == MZ_FINISH);

  যদি ((flush == MZ_FINISH) && (first_call))
  {
    // MZ_FINISH on the first call implies that the input and output buffers are large enough to hold the entire compressed/decompressed file.
    decomp_flags |= TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF;
    in_bytes = pStream->avail_in; out_bytes = pStream->avail_out;
    status = tinfl_decompress(&pState->m_decomp, pStream->পরবর্তী_in, &in_bytes, pStream->পরবর্তী_out, pStream->পরবর্তী_out, &out_bytes, decomp_flags);
    pState->m_last_status = status;
    pStream->পরবর্তী_in += (mz_uint)in_bytes; pStream->avail_in -= (mz_uint)in_bytes; pStream->যোগ_in += (mz_uint)in_bytes;
    pStream->adler = tinfl_get_adler32(&pState->m_decomp);
    pStream->পরবর্তী_out += (mz_uint)out_bytes; pStream->avail_out -= (mz_uint)out_bytes; pStream->যোগ_out += (mz_uint)out_bytes;

    যদি (status < 0)
      ফেরত MZ_তথ্য_ERROR;
    অন্যথা যদি (status != TINFL_STATUS_DONE)
    {
      pState->m_last_status = TINFL_STATUS_FAILED;
      ফেরত MZ_BUF_ERROR;
    }
    ফেরত MZ_STREAM_END;
  }
  // flush != MZ_FINISH then we must assume there's more input.
  যদি (flush != MZ_FINISH) decomp_flags |= TINFL_FLAG_HAS_MORE_প্রবেশ;

  যদি (pState->m_dict_avail)
  {
    n = MZ_MIN(pState->m_dict_avail, pStream->avail_out);
    memcpy(pStream->পরবর্তী_out, pState->m_dict + pState->m_dict_ofs, n);
    pStream->পরবর্তী_out += n; pStream->avail_out -= n; pStream->যোগ_out += n;
    pState->m_dict_avail -= n; pState->m_dict_ofs = (pState->m_dict_ofs + n) & (TINFL_LZ_DICT_আকার - 1);
    ফেরত ((pState->m_last_status == TINFL_STATUS_DONE) && (!pState->m_dict_avail)) ? MZ_STREAM_END : MZ_OK;
  }

  জন্য ( ; ; )
  {
    in_bytes = pStream->avail_in;
    out_bytes = TINFL_LZ_DICT_আকার - pState->m_dict_ofs;

    status = tinfl_decompress(&pState->m_decomp, pStream->পরবর্তী_in, &in_bytes, pState->m_dict, pState->m_dict + pState->m_dict_ofs, &out_bytes, decomp_flags);
    pState->m_last_status = status;

    pStream->পরবর্তী_in += (mz_uint)in_bytes; pStream->avail_in -= (mz_uint)in_bytes;
    pStream->যোগ_in += (mz_uint)in_bytes; pStream->adler = tinfl_get_adler32(&pState->m_decomp);

    pState->m_dict_avail = (mz_uint)out_bytes;

    n = MZ_MIN(pState->m_dict_avail, pStream->avail_out);
    memcpy(pStream->পরবর্তী_out, pState->m_dict + pState->m_dict_ofs, n);
    pStream->পরবর্তী_out += n; pStream->avail_out -= n; pStream->যোগ_out += n;
    pState->m_dict_avail -= n; pState->m_dict_ofs = (pState->m_dict_ofs + n) & (TINFL_LZ_DICT_আকার - 1);

    যদি (status < 0)
       ফেরত MZ_তথ্য_ERROR; // Stream is corrupted (there could be some uncompressed data left in the output dictionary - oh well).
    অন্যথা যদি ((status == TINFL_STATUS_NEEDS_MORE_প্রবেশ) && (!orig_avail_in))
      ফেরত MZ_BUF_ERROR; // Signal caller that we can't make forward progress without supplying more input or by setting flush to MZ_FINISH.
    অন্যথা যদি (flush == MZ_FINISH)
    {
       // The output buffer MUST be large to hold the remaining uncompressed data when flush==MZ_FINISH.
       যদি (status == TINFL_STATUS_DONE)
          ফেরত pState->m_dict_avail ? MZ_BUF_ERROR : MZ_STREAM_END;
       // status here must be TINFL_STATUS_HAS_MORE_OUTPUT, which means there's at least 1 more byte on the way. If there's no more room left in the output buffer then something is wrong.
       অন্যথা যদি (!pStream->avail_out)
          ফেরত MZ_BUF_ERROR;
    }
    অন্যথা যদি ((status == TINFL_STATUS_DONE) || (!pStream->avail_in) || (!pStream->avail_out) || (pState->m_dict_avail))
      বিরতি;
  }

  ফেরত ((status == TINFL_STATUS_DONE) && (!pState->m_dict_avail)) ? MZ_STREAM_END : MZ_OK;
}

পূর্ণসংখ্যা mz_inflateEnd(mz_streamp pStream)
{
  যদি (!pStream)
    ফেরত MZ_STREAM_ERROR;
  যদি (pStream->state)
  {
    pStream->zfree(pStream->opaque, pStream->state);
    pStream->state = ফাঁকা;
  }
  ফেরত MZ_OK;
}

পূর্ণসংখ্যা mz_uncompress(unsigned অক্ষর *pDest, mz_ulong *pDest_len, ধ্রুবক unsigned অক্ষর *pSource, mz_ulong source_len)
{
  mz_stream stream;
  পূর্ণসংখ্যা status;
  memset(&stream, 0, আকার(stream));

  // In case mz_ulong is 64-bits (argh I hate longs).
  যদি ((source_len | *pDest_len) > 0xFFFFFFFFU) ফেরত MZ_PARAM_ERROR;

  stream.পরবর্তী_in = pSource;
  stream.avail_in = (mz_uint32)source_len;
  stream.পরবর্তী_out = pDest;
  stream.avail_out = (mz_uint32)*pDest_len;

  status = mz_inflateInit(&stream);
  যদি (status != MZ_OK)
    ফেরত status;

  status = mz_inflate(&stream, MZ_FINISH);
  যদি (status != MZ_STREAM_END)
  {
    mz_inflateEnd(&stream);
    ফেরত ((status == MZ_BUF_ERROR) && (!stream.avail_in)) ? MZ_তথ্য_ERROR : status;
  }
  *pDest_len = stream.যোগ_out;

  ফেরত mz_inflateEnd(&stream);
}

#endif /*#ifndef MINIZ_NO_INFLATE_APIS*/

ধ্রুবক অক্ষর *mz_error(পূর্ণসংখ্যা err)
{
  স্থির কাঠামো { পূর্ণসংখ্যা m_err; ধ্রুবক অক্ষর *m_pDesc; } s_error_descs[] =
  {
    { MZ_OK, "" }, { MZ_STREAM_END, "stream end" }, { MZ_NEED_DICT, "need dictionary" }, { MZ_ERRNO, "file error" }, { MZ_STREAM_ERROR, "stream error" },
    { MZ_তথ্য_ERROR, "data error" }, { MZ_MEM_ERROR, "out of memory" }, { MZ_BUF_ERROR, "buf error" }, { MZ_VERSION_ERROR, "version error" }, { MZ_PARAM_ERROR, "parameter error" }
  };
  mz_uint i; জন্য (i = 0; i < আকার(s_error_descs) / আকার(s_error_descs[0]); ++i) যদি (s_error_descs[i].m_err == err) ফেরত s_error_descs[i].m_pDesc;
  ফেরত ফাঁকা;
}

#endif //MINIZ_NO_ZLIB_APIS

// ------------------- Low-level Decompression (completely independent from all compression API's)
#ifndef MINIZ_NO_INFLATE_APIS

#define TINFL_MEMCPY(d, s, l) memcpy(d, s, l)
#define TINFL_MEMSET(p, c, l) memset(p, c, l)

#define TINFL_CR_BEGIN নির্বাচন(r->m_state) { ক্ষেত্র 0:
#define TINFL_CR_RETURN(state_সূচক, ফলাফল) করো { status = ফলাফল; r->m_state = state_সূচক; যাও common_exit; ক্ষেত্র state_সূচক:; } MZ_MACRO_END
#define TINFL_CR_RETURN_FOREVER(state_সূচক, ফলাফল) করো { জন্য ( ; ; ) { TINFL_CR_RETURN(state_সূচক, ফলাফল); } } MZ_MACRO_END
#define TINFL_CR_FINISH }

// TODO: If the caller has indicated that there's no more input, and we attempt to read beyond the input buf, then something is wrong with the input because the inflator never
// reads ahead more than it needs to. Currently TINFL_GET_BYTE() pads the end of the stream with 0's in this scenario.
#define TINFL_GET_BYTE(state_সূচক, c) করো { \
  যদি (pIn_buf_cur >= pIn_buf_end) { \
    জন্য ( ; ; ) { \
      যদি (decomp_flags & TINFL_FLAG_HAS_MORE_প্রবেশ) { \
        TINFL_CR_RETURN(state_সূচক, TINFL_STATUS_NEEDS_MORE_প্রবেশ); \
        যদি (pIn_buf_cur < pIn_buf_end) { \
          c = *pIn_buf_cur++; \
          বিরতি; \
        } \
      } অন্যথা { \
        c = 0; \
        বিরতি; \
      } \
    } \
  } অন্যথা c = *pIn_buf_cur++; } MZ_MACRO_END

#define TINFL_NEED_BITS(state_সূচক, n) করো { mz_uint c; TINFL_GET_BYTE(state_সূচক, c); bit_buf |= (((tinfl_bit_buf_t)c) << অঙ্ক_bits); অঙ্ক_bits += 8; } যখন (অঙ্ক_bits < (mz_uint)(n))
#define TINFL_SKIP_BITS(state_সূচক, n) করো { যদি (অঙ্ক_bits < (mz_uint)(n)) { TINFL_NEED_BITS(state_সূচক, n); } bit_buf >>= (n); অঙ্ক_bits -= (n); } MZ_MACRO_END
#define TINFL_GET_BITS(state_সূচক, b, n) করো { যদি (অঙ্ক_bits < (mz_uint)(n)) { TINFL_NEED_BITS(state_সূচক, n); } b = bit_buf & ((1 << (n)) - 1); bit_buf >>= (n); অঙ্ক_bits -= (n); } MZ_MACRO_END

// TINFL_HUFF_BITBUF_FILL() is only used rarely, when the number of bytes remaining in the input buffer falls below 2.
// It reads just enough bytes from the input stream that are needed to decode the next Huffman code (and absolutely no more). It works by trying to fully decode a
// Huffman code by using whatever bits are currently present in the bit buffer. If this fails, it reads another byte, and tries again until it succeeds or until the
// bit buffer contains >=15 bits (deflate's max. Huffman code size).
#define TINFL_HUFF_BITBUF_FILL(state_সূচক, pHuff) \
  করো { \
    অস্থায়ী = (pHuff)->m_look_up[bit_buf & (TINFL_FAST_LOOKUP_আকার - 1)]; \
    যদি (অস্থায়ী >= 0) { \
      code_len = অস্থায়ী >> 9; \
      যদি ((code_len) && (অঙ্ক_bits >= code_len)) \
          বিরতি; \
    } অন্যথা যদি (অঙ্ক_bits > TINFL_FAST_LOOKUP_BITS) { \
       code_len = TINFL_FAST_LOOKUP_BITS; \
       করো { \
          অস্থায়ী = (pHuff)->m_বৃক্ষ[~অস্থায়ী + ((bit_buf >> code_len++) & 1)]; \
       } যখন ((অস্থায়ী < 0) && (অঙ্ক_bits >= (code_len + 1))); \
       যদি (অস্থায়ী >= 0) বিরতি; \
    } \
    TINFL_GET_BYTE(state_সূচক, c); \
    bit_buf |= (((tinfl_bit_buf_t)c) << অঙ্ক_bits); \
    অঙ্ক_bits += 8; \
  } যখন (অঙ্ক_bits < 15);

// TINFL_HUFF_DECODE() decodes the next Huffman coded symbol. It's more complex than you would initially expect because the zlib API expects the decompressor to never read
// beyond the final byte of the deflate stream. (In other words, when this macro wants to read another byte from the input, it REALLY needs another byte in order to fully
// decode the next Huffman code.) Handling this properly is particularly important on raw deflate (non-zlib) streams, which aren't followed by a byte aligned adler-32.
// The slow path is only executed at the very end of the input buffer.
#define TINFL_HUFF_DECODE(state_সূচক, sym, pHuff) করো { \
  পূর্ণসংখ্যা অস্থায়ী; mz_uint code_len, c; \
  যদি (অঙ্ক_bits < 15) { \
    যদি ((pIn_buf_end - pIn_buf_cur) < 2) { \
       TINFL_HUFF_BITBUF_FILL(state_সূচক, pHuff); \
    } অন্যথা { \
       bit_buf |= (((tinfl_bit_buf_t)pIn_buf_cur[0]) << অঙ্ক_bits) | (((tinfl_bit_buf_t)pIn_buf_cur[1]) << (অঙ্ক_bits + 8)); pIn_buf_cur += 2; অঙ্ক_bits += 16; \
    } \
  } \
  যদি ((অস্থায়ী = (pHuff)->m_look_up[bit_buf & (TINFL_FAST_LOOKUP_আকার - 1)]) >= 0) \
    code_len = অস্থায়ী >> 9, অস্থায়ী &= 511; \
  অন্যথা { \
    code_len = TINFL_FAST_LOOKUP_BITS; করো { অস্থায়ী = (pHuff)->m_বৃক্ষ[~অস্থায়ী + ((bit_buf >> code_len++) & 1)]; } যখন (অস্থায়ী < 0); \
  } sym = অস্থায়ী; bit_buf >>= code_len; অঙ্ক_bits -= code_len; } MZ_MACRO_END

tinfl_status tinfl_decompress(tinfl_decompressor *r, ধ্রুবক mz_uint8 *p_In_buf_পরবর্তী, size_t *p_In_buf_আকার, mz_uint8 *pOut_buf_start, mz_uint8 *p_Out_buf_পরবর্তী, size_t *p_Out_buf_আকার, ধ্রুবক mz_uint32 decomp_flags)
{
  স্থির ধ্রুবক পূর্ণসংখ্যা s_দৈর্ঘ্য_base[31] = { 3,4,5,6,7,8,9,10,11,13, 15,17,19,23,27,31,35,43,51,59, 67,83,99,115,131,163,195,227,258,0,0 };
  স্থির ধ্রুবক পূর্ণসংখ্যা s_দৈর্ঘ্য_extra[31]= { 0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,0,0,0 };
  স্থির ধ্রুবক পূর্ণসংখ্যা s_dist_base[32] = { 1,2,3,4,5,7,9,13,17,25,33,49,65,97,129,193, 257,385,513,769,1025,1537,2049,3073,4097,6145,8193,12289,16385,24577,0,0};
  স্থির ধ্রুবক পূর্ণসংখ্যা s_dist_extra[32] = { 0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13};
  স্থির ধ্রুবক mz_uint8 s_দৈর্ঘ্য_dezigzag[19] = { 16,17,18,0,8,7,9,6,10,5,11,4,12,3,13,2,14,1,15 };
  স্থির ধ্রুবক পূর্ণসংখ্যা s_min_table_sizes[3] = { 257, 1, 4 };

  tinfl_status status = TINFL_STATUS_FAILED; mz_uint32 অঙ্ক_bits, dist, গণক, অঙ্ক_extra; tinfl_bit_buf_t bit_buf;
  ধ্রুবক mz_uint8 *pIn_buf_cur = p_In_buf_পরবর্তী, *ধ্রুবক pIn_buf_end = p_In_buf_পরবর্তী + *p_In_buf_আকার;
  mz_uint8 *pOut_buf_cur = p_Out_buf_পরবর্তী, *ধ্রুবক pOut_buf_end = p_Out_buf_পরবর্তী + *p_Out_buf_আকার;
  size_t out_buf_আকার_mask = (decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF) ? (size_t)-1 : ((p_Out_buf_পরবর্তী - pOut_buf_start) + *p_Out_buf_আকার) - 1, dist_from_out_buf_start;

  // Ensure the output buffer's size is a power of 2, unless the output buffer is large enough to hold the entire output file (in which case it doesn't matter).
  যদি (((out_buf_আকার_mask + 1) & out_buf_আকার_mask) || (p_Out_buf_পরবর্তী < pOut_buf_start)) { *p_In_buf_আকার = *p_Out_buf_আকার = 0; ফেরত TINFL_STATUS_BAD_PARAM; }

  অঙ্ক_bits = r->m_অঙ্ক_bits; bit_buf = r->m_bit_buf; dist = r->m_dist; গণক = r->m_গণক; অঙ্ক_extra = r->m_অঙ্ক_extra; dist_from_out_buf_start = r->m_dist_from_out_buf_start;
  TINFL_CR_BEGIN

  bit_buf = অঙ্ক_bits = dist = গণক = অঙ্ক_extra = r->m_zhdr0 = r->m_zhdr1 = 0; r->m_z_adler32 = r->m_check_adler32 = 1;
  যদি (decomp_flags & TINFL_FLAG_PARSE_ZLIB_HEADER)
  {
    TINFL_GET_BYTE(1, r->m_zhdr0); TINFL_GET_BYTE(2, r->m_zhdr1);
    গণক = (((r->m_zhdr0 * 256 + r->m_zhdr1) % 31 != 0) || (r->m_zhdr1 & 32) || ((r->m_zhdr0 & 15) != 8));
    যদি (!(decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF)) গণক |= (((1U << (8U + (r->m_zhdr0 >> 4))) > 32768U) || ((out_buf_আকার_mask + 1) < (size_t)(1U << (8U + (r->m_zhdr0 >> 4)))));
    যদি (গণক) { TINFL_CR_RETURN_FOREVER(36, TINFL_STATUS_FAILED); }
  }

  করো
  {
    TINFL_GET_BITS(3, r->m_final, 3); r->m_type = r->m_final >> 1;
    যদি (r->m_type == 0)
    {
      TINFL_SKIP_BITS(5, অঙ্ক_bits & 7);
      জন্য (গণক = 0; গণক < 4; ++গণক) { যদি (অঙ্ক_bits) TINFL_GET_BITS(6, r->m_raw_header[গণক], 8); অন্যথা TINFL_GET_BYTE(7, r->m_raw_header[গণক]); }
      যদি ((গণক = (r->m_raw_header[0] | (r->m_raw_header[1] << 8))) != (mz_uint)(0xFFFF ^ (r->m_raw_header[2] | (r->m_raw_header[3] << 8)))) { TINFL_CR_RETURN_FOREVER(39, TINFL_STATUS_FAILED); }
      যখন ((গণক) && (অঙ্ক_bits))
      {
        TINFL_GET_BITS(51, dist, 8);
        যখন (pOut_buf_cur >= pOut_buf_end) { TINFL_CR_RETURN(52, TINFL_STATUS_HAS_MORE_OUTPUT); }
        *pOut_buf_cur++ = (mz_uint8)dist;
        গণক--;
      }
      যখন (গণক)
      {
        size_t n; যখন (pOut_buf_cur >= pOut_buf_end) { TINFL_CR_RETURN(9, TINFL_STATUS_HAS_MORE_OUTPUT); }
        যখন (pIn_buf_cur >= pIn_buf_end)
        {
          যদি (decomp_flags & TINFL_FLAG_HAS_MORE_প্রবেশ)
          {
            TINFL_CR_RETURN(38, TINFL_STATUS_NEEDS_MORE_প্রবেশ);
          }
          অন্যথা
          {
            TINFL_CR_RETURN_FOREVER(40, TINFL_STATUS_FAILED);
          }
        }
        n = MZ_MIN(MZ_MIN((size_t)(pOut_buf_end - pOut_buf_cur), (size_t)(pIn_buf_end - pIn_buf_cur)), গণক);
        TINFL_MEMCPY(pOut_buf_cur, pIn_buf_cur, n); pIn_buf_cur += n; pOut_buf_cur += n; গণক -= (mz_uint)n;
      }
    }
    অন্যথা যদি (r->m_type == 3)
    {
      TINFL_CR_RETURN_FOREVER(10, TINFL_STATUS_FAILED);
    }
    অন্যথা
    {
      যদি (r->m_type == 1)
      {
        mz_uint8 *p = r->m_tables[0].m_code_আকার; mz_uint i;
        r->m_table_sizes[0] = 288; r->m_table_sizes[1] = 32; TINFL_MEMSET(r->m_tables[1].m_code_আকার, 5, 32);
        জন্য ( i = 0; i <= 143; ++i) *p++ = 8;
        জন্য ( ; i <= 255; ++i) *p++ = 9;
        জন্য ( ; i <= 279; ++i) *p++ = 7;
        জন্য ( ; i <= 287; ++i) *p++ = 8;
      }
      অন্যথা
      {
        জন্য (গণক = 0; গণক < 3; গণক++) { TINFL_GET_BITS(11, r->m_table_sizes[গণক], "\05\05\04"[গণক]); r->m_table_sizes[গণক] += s_min_table_sizes[গণক]; }
        MZ_CLEAR_ARR(r->m_tables[2].m_code_আকার); জন্য (গণক = 0; গণক < r->m_table_sizes[2]; গণক++) { mz_uint s; TINFL_GET_BITS(14, s, 3); r->m_tables[2].m_code_আকার[s_দৈর্ঘ্য_dezigzag[গণক]] = (mz_uint8)s; }
        r->m_table_sizes[2] = 19;
      }
      জন্য ( ; (পূর্ণসংখ্যা)r->m_type >= 0; r->m_type--)
      {
        পূর্ণসংখ্যা বৃক্ষ_পরবর্তী, বৃক্ষ_cur; tinfl_huff_table *pTable;
        mz_uint i, j, used_syms, যোগ, sym_সূচক, পরবর্তী_code[17], যোগ_syms[16]; pTable = &r->m_tables[r->m_type]; MZ_CLEAR_ARR(যোগ_syms); MZ_CLEAR_ARR(pTable->m_look_up); MZ_CLEAR_ARR(pTable->m_বৃক্ষ);
        জন্য (i = 0; i < r->m_table_sizes[r->m_type]; ++i) যোগ_syms[pTable->m_code_আকার[i]]++;
        used_syms = 0, যোগ = 0; পরবর্তী_code[0] = পরবর্তী_code[1] = 0;
        জন্য (i = 1; i <= 15; ++i) { used_syms += যোগ_syms[i]; পরবর্তী_code[i + 1] = (যোগ = ((যোগ + যোগ_syms[i]) << 1)); }
        যদি ((65536 != যোগ) && (used_syms > 1))
        {
          TINFL_CR_RETURN_FOREVER(35, TINFL_STATUS_FAILED);
        }
        জন্য (বৃক্ষ_পরবর্তী = -1, sym_সূচক = 0; sym_সূচক < r->m_table_sizes[r->m_type]; ++sym_সূচক)
        {
          mz_uint rev_code = 0, l, cur_code, code_আকার_2 = pTable->m_code_আকার[sym_সূচক]; যদি (!code_আকার_2) চালু;
          cur_code = পরবর্তী_code[code_আকার_2]++; জন্য (l = code_আকার_2; l > 0; l--, cur_code >>= 1) rev_code = (rev_code << 1) | (cur_code & 1);
          যদি (code_আকার_2 <= TINFL_FAST_LOOKUP_BITS) { mz_int16 k = (mz_int16)((code_আকার_2 << 9) | sym_সূচক); যখন (rev_code < TINFL_FAST_LOOKUP_আকার) { pTable->m_look_up[rev_code] = k; rev_code += (1 << code_আকার_2); } চালু; }
          যদি (0 == (বৃক্ষ_cur = pTable->m_look_up[rev_code & (TINFL_FAST_LOOKUP_আকার - 1)])) { pTable->m_look_up[rev_code & (TINFL_FAST_LOOKUP_আকার - 1)] = (mz_int16)বৃক্ষ_পরবর্তী; বৃক্ষ_cur = বৃক্ষ_পরবর্তী; বৃক্ষ_পরবর্তী -= 2; }
          rev_code >>= (TINFL_FAST_LOOKUP_BITS - 1);
          জন্য (j = code_আকার_2; j > (TINFL_FAST_LOOKUP_BITS + 1); j--)
          {
            বৃক্ষ_cur -= ((rev_code >>= 1) & 1);
            যদি (!pTable->m_বৃক্ষ[-বৃক্ষ_cur - 1]) { pTable->m_বৃক্ষ[-বৃক্ষ_cur - 1] = (mz_int16)বৃক্ষ_পরবর্তী; বৃক্ষ_cur = বৃক্ষ_পরবর্তী; বৃক্ষ_পরবর্তী -= 2; } অন্যথা বৃক্ষ_cur = pTable->m_বৃক্ষ[-বৃক্ষ_cur - 1];
          }
          বৃক্ষ_cur -= ((rev_code >>= 1) & 1); pTable->m_বৃক্ষ[-বৃক্ষ_cur - 1] = (mz_int16)sym_সূচক;
        }
        যদি (r->m_type == 2)
        {
          জন্য (গণক = 0; গণক < (r->m_table_sizes[0] + r->m_table_sizes[1]); )
          {
            mz_uint s; TINFL_HUFF_DECODE(16, dist, &r->m_tables[2]); যদি (dist < 16) { r->m_len_codes[গণক++] = (mz_uint8)dist; চালু; }
            যদি ((dist == 16) && (!গণক))
            {
              TINFL_CR_RETURN_FOREVER(17, TINFL_STATUS_FAILED);
            }
            অঙ্ক_extra = "\02\03\07"[dist - 16]; TINFL_GET_BITS(18, s, অঙ্ক_extra); s += "\03\03\013"[dist - 16];
            TINFL_MEMSET(r->m_len_codes + গণক, (dist == 16) ? r->m_len_codes[গণক - 1] : 0, s); গণক += s;
          }
          যদি ((r->m_table_sizes[0] + r->m_table_sizes[1]) != গণক)
          {
            TINFL_CR_RETURN_FOREVER(21, TINFL_STATUS_FAILED);
          }
          TINFL_MEMCPY(r->m_tables[0].m_code_আকার, r->m_len_codes, r->m_table_sizes[0]); TINFL_MEMCPY(r->m_tables[1].m_code_আকার, r->m_len_codes + r->m_table_sizes[0], r->m_table_sizes[1]);
        }
      }
      জন্য ( ; ; )
      {
        mz_uint8 *pSrc;
        জন্য ( ; ; )
        {
          যদি (((pIn_buf_end - pIn_buf_cur) < 4) || ((pOut_buf_end - pOut_buf_cur) < 2))
          {
            TINFL_HUFF_DECODE(23, গণক, &r->m_tables[0]);
            যদি (গণক >= 256)
              বিরতি;
            যখন (pOut_buf_cur >= pOut_buf_end) { TINFL_CR_RETURN(24, TINFL_STATUS_HAS_MORE_OUTPUT); }
            *pOut_buf_cur++ = (mz_uint8)গণক;
          }
          অন্যথা
          {
            পূর্ণসংখ্যা sym2; mz_uint code_len;
#যদি TINFL_USE_64BIT_BITBUF
            যদি (অঙ্ক_bits < 30) { bit_buf |= (((tinfl_bit_buf_t)MZ_READ_LE32(pIn_buf_cur)) << অঙ্ক_bits); pIn_buf_cur += 4; অঙ্ক_bits += 32; }
#অন্যথা
            যদি (অঙ্ক_bits < 15) { bit_buf |= (((tinfl_bit_buf_t)MZ_READ_LE16(pIn_buf_cur)) << অঙ্ক_bits); pIn_buf_cur += 2; অঙ্ক_bits += 16; }
#endif
            যদি ((sym2 = r->m_tables[0].m_look_up[bit_buf & (TINFL_FAST_LOOKUP_আকার - 1)]) >= 0)
              code_len = sym2 >> 9;
            অন্যথা
            {
              code_len = TINFL_FAST_LOOKUP_BITS; করো { sym2 = r->m_tables[0].m_বৃক্ষ[~sym2 + ((bit_buf >> code_len++) & 1)]; } যখন (sym2 < 0);
            }
            গণক = sym2; bit_buf >>= code_len; অঙ্ক_bits -= code_len;
            যদি (গণক & 256)
              বিরতি;

#যদি !TINFL_USE_64BIT_BITBUF
            যদি (অঙ্ক_bits < 15) { bit_buf |= (((tinfl_bit_buf_t)MZ_READ_LE16(pIn_buf_cur)) << অঙ্ক_bits); pIn_buf_cur += 2; অঙ্ক_bits += 16; }
#endif
            যদি ((sym2 = r->m_tables[0].m_look_up[bit_buf & (TINFL_FAST_LOOKUP_আকার - 1)]) >= 0)
              code_len = sym2 >> 9;
            অন্যথা
            {
              code_len = TINFL_FAST_LOOKUP_BITS; করো { sym2 = r->m_tables[0].m_বৃক্ষ[~sym2 + ((bit_buf >> code_len++) & 1)]; } যখন (sym2 < 0);
            }
            bit_buf >>= code_len; অঙ্ক_bits -= code_len;

            pOut_buf_cur[0] = (mz_uint8)গণক;
            যদি (sym2 & 256)
            {
              pOut_buf_cur++;
              গণক = sym2;
              বিরতি;
            }
            pOut_buf_cur[1] = (mz_uint8)sym2;
            pOut_buf_cur += 2;
          }
        }
        যদি ((গণক &= 511) == 256) বিরতি;

        অঙ্ক_extra = s_দৈর্ঘ্য_extra[গণক - 257]; গণক = s_দৈর্ঘ্য_base[গণক - 257];
        যদি (অঙ্ক_extra) { mz_uint extra_bits; TINFL_GET_BITS(25, extra_bits, অঙ্ক_extra); গণক += extra_bits; }

        TINFL_HUFF_DECODE(26, dist, &r->m_tables[1]);
        অঙ্ক_extra = s_dist_extra[dist]; dist = s_dist_base[dist];
        যদি (অঙ্ক_extra) { mz_uint extra_bits; TINFL_GET_BITS(27, extra_bits, অঙ্ক_extra); dist += extra_bits; }

        dist_from_out_buf_start = pOut_buf_cur - pOut_buf_start;
        যদি ((dist > dist_from_out_buf_start) && (decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF))
        {
          TINFL_CR_RETURN_FOREVER(37, TINFL_STATUS_FAILED);
        }

        pSrc = pOut_buf_start + ((dist_from_out_buf_start - dist) & out_buf_আকার_mask);

        যদি ((MZ_MAX(pOut_buf_cur, pSrc) + গণক) > pOut_buf_end)
        {
          যখন (গণক--)
          {
            যখন (pOut_buf_cur >= pOut_buf_end) { TINFL_CR_RETURN(53, TINFL_STATUS_HAS_MORE_OUTPUT); }
            *pOut_buf_cur++ = pOut_buf_start[(dist_from_out_buf_start++ - dist) & out_buf_আকার_mask];
          }
          চালু;
        }
#যদি MINIZ_USE_UNALIGNED_LOADS_AND_STORES
        অন্যথা যদি ((গণক >= 9) && (গণক <= dist))
        {
          ধ্রুবক mz_uint8 *pSrc_end = pSrc + (গণক & ~7);
          করো
          {
            ((mz_uint32 *)pOut_buf_cur)[0] = ((ধ্রুবক mz_uint32 *)pSrc)[0];
            ((mz_uint32 *)pOut_buf_cur)[1] = ((ধ্রুবক mz_uint32 *)pSrc)[1];
            pOut_buf_cur += 8;
          } যখন ((pSrc += 8) < pSrc_end);
          যদি ((গণক &= 7) < 3)
          {
            যদি (গণক)
            {
              pOut_buf_cur[0] = pSrc[0];
              যদি (গণক > 1)
                pOut_buf_cur[1] = pSrc[1];
              pOut_buf_cur += গণক;
            }
            চালু;
          }
        }
#endif
        করো
        {
          pOut_buf_cur[0] = pSrc[0];
          pOut_buf_cur[1] = pSrc[1];
          pOut_buf_cur[2] = pSrc[2];
          pOut_buf_cur += 3; pSrc += 3;
        } যখন ((পূর্ণসংখ্যা)(গণক -= 3) > 2);
        যদি ((পূর্ণসংখ্যা)গণক > 0)
        {
          pOut_buf_cur[0] = pSrc[0];
          যদি ((পূর্ণসংখ্যা)গণক > 1)
            pOut_buf_cur[1] = pSrc[1];
          pOut_buf_cur += গণক;
        }
      }
    }
  } যখন (!(r->m_final & 1));
  যদি (decomp_flags & TINFL_FLAG_PARSE_ZLIB_HEADER)
  {
    TINFL_SKIP_BITS(32, অঙ্ক_bits & 7); জন্য (গণক = 0; গণক < 4; ++গণক) { mz_uint s; যদি (অঙ্ক_bits) TINFL_GET_BITS(41, s, 8); অন্যথা TINFL_GET_BYTE(42, s); r->m_z_adler32 = (r->m_z_adler32 << 8) | s; }
  }
  TINFL_CR_RETURN_FOREVER(34, TINFL_STATUS_DONE);
  TINFL_CR_FINISH

common_exit:
  r->m_অঙ্ক_bits = অঙ্ক_bits; r->m_bit_buf = bit_buf; r->m_dist = dist; r->m_গণক = গণক; r->m_অঙ্ক_extra = অঙ্ক_extra; r->m_dist_from_out_buf_start = dist_from_out_buf_start;
  *p_In_buf_আকার = pIn_buf_cur - p_In_buf_পরবর্তী; *p_Out_buf_আকার = pOut_buf_cur - p_Out_buf_পরবর্তী;
  যদি ((decomp_flags & (TINFL_FLAG_PARSE_ZLIB_HEADER | TINFL_FLAG_COMPUTE_ADLER32)) && (status >= 0))
  {
    ধ্রুবক mz_uint8 *ptr = p_Out_buf_পরবর্তী; size_t buf_len = *p_Out_buf_আকার;
    mz_uint32 i, s1 = r->m_check_adler32 & 0xffff, s2 = r->m_check_adler32 >> 16; size_t block_len = buf_len % 5552;
    যখন (buf_len)
    {
      জন্য (i = 0; i + 7 < block_len; i += 8, ptr += 8)
      {
        s1 += ptr[0], s2 += s1; s1 += ptr[1], s2 += s1; s1 += ptr[2], s2 += s1; s1 += ptr[3], s2 += s1;
        s1 += ptr[4], s2 += s1; s1 += ptr[5], s2 += s1; s1 += ptr[6], s2 += s1; s1 += ptr[7], s2 += s1;
      }
      জন্য ( ; i < block_len; ++i) s1 += *ptr++, s2 += s1;
      s1 %= 65521U, s2 %= 65521U; buf_len -= block_len; block_len = 5552;
    }
    r->m_check_adler32 = (s2 << 16) + s1; যদি ((status == TINFL_STATUS_DONE) && (decomp_flags & TINFL_FLAG_PARSE_ZLIB_HEADER) && (r->m_check_adler32 != r->m_z_adler32)) status = TINFL_STATUS_ADLER32_MISMATCH;
  }
  ফেরত status;
}

// Higher level helper functions.
শূন্য *tinfl_decompress_mem_to_heap(ধ্রুবক শূন্য *pSrc_buf, size_t src_buf_len, size_t *pOut_len, পূর্ণসংখ্যা flags)
{
  tinfl_decompressor decomp; শূন্য *pBuf = ফাঁকা, *pNew_buf; size_t src_buf_ofs = 0, out_buf_capacity = 0;
  *pOut_len = 0;
  tinfl_init(&decomp);
  জন্য ( ; ; )
  {
    size_t src_buf_আকার = src_buf_len - src_buf_ofs, dst_buf_আকার = out_buf_capacity - *pOut_len, new_out_buf_capacity;
    tinfl_status status = tinfl_decompress(&decomp, (ধ্রুবক mz_uint8*)pSrc_buf + src_buf_ofs, &src_buf_আকার, (mz_uint8*)pBuf, pBuf ? (mz_uint8*)pBuf + *pOut_len : ফাঁকা, &dst_buf_আকার,
      (flags & ~TINFL_FLAG_HAS_MORE_প্রবেশ) | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF);
    যদি ((status < 0) || (status == TINFL_STATUS_NEEDS_MORE_প্রবেশ))
    {
      MZ_FREE(pBuf); *pOut_len = 0; ফেরত ফাঁকা;
    }
    src_buf_ofs += src_buf_আকার;
    *pOut_len += dst_buf_আকার;
    যদি (status == TINFL_STATUS_DONE) বিরতি;
    new_out_buf_capacity = out_buf_capacity * 2; যদি (new_out_buf_capacity < 128) new_out_buf_capacity = 128;
    pNew_buf = MZ_REALLOC(pBuf, new_out_buf_capacity);
    যদি (!pNew_buf)
    {
      MZ_FREE(pBuf); *pOut_len = 0; ফেরত ফাঁকা;
    }
    pBuf = pNew_buf; out_buf_capacity = new_out_buf_capacity;
  }
  ফেরত pBuf;
}

size_t tinfl_decompress_mem_to_mem(শূন্য *pOut_buf, size_t out_buf_len, ধ্রুবক শূন্য *pSrc_buf, size_t src_buf_len, পূর্ণসংখ্যা flags)
{
  tinfl_decompressor decomp; tinfl_status status; tinfl_init(&decomp);
  status = tinfl_decompress(&decomp, (ধ্রুবক mz_uint8*)pSrc_buf, &src_buf_len, (mz_uint8*)pOut_buf, (mz_uint8*)pOut_buf, &out_buf_len, (flags & ~TINFL_FLAG_HAS_MORE_প্রবেশ) | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF);
  ফেরত (status != TINFL_STATUS_DONE) ? TINFL_DECOMPRESS_MEM_TO_MEM_FAILED : out_buf_len;
}

পূর্ণসংখ্যা tinfl_decompress_mem_to_callback(ধ্রুবক শূন্য *pIn_buf, size_t *p_In_buf_আকার, tinfl_put_buf_func_ptr pPut_buf_func, শূন্য *pPut_buf_user, পূর্ণসংখ্যা flags)
{
  পূর্ণসংখ্যা ফলাফল = 0;
  tinfl_decompressor decomp;
  mz_uint8 *pDict = (mz_uint8*)MZ_MALLOC(TINFL_LZ_DICT_আকার); size_t in_buf_ofs = 0, dict_ofs = 0;
  যদি (!pDict)
    ফেরত TINFL_STATUS_FAILED;
  memset(pDict,0,TINFL_LZ_DICT_আকার);
  tinfl_init(&decomp);
  জন্য ( ; ; )
  {
    size_t in_buf_আকার = *p_In_buf_আকার - in_buf_ofs, dst_buf_আকার = TINFL_LZ_DICT_আকার - dict_ofs;
    tinfl_status status = tinfl_decompress(&decomp, (ধ্রুবক mz_uint8*)pIn_buf + in_buf_ofs, &in_buf_আকার, pDict, pDict + dict_ofs, &dst_buf_আকার,
      (flags & ~(TINFL_FLAG_HAS_MORE_প্রবেশ | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF)));
    in_buf_ofs += in_buf_আকার;
    যদি ((dst_buf_আকার) && (!(*pPut_buf_func)(pDict + dict_ofs, (পূর্ণসংখ্যা)dst_buf_আকার, pPut_buf_user)))
      বিরতি;
    যদি (status != TINFL_STATUS_HAS_MORE_OUTPUT)
    {
      ফলাফল = (status == TINFL_STATUS_DONE);
      বিরতি;
    }
    dict_ofs = (dict_ofs + dst_buf_আকার) & (TINFL_LZ_DICT_আকার - 1);
  }
  MZ_FREE(pDict);
  *p_In_buf_আকার = in_buf_ofs;
  ফেরত ফলাফল;
}
#endif /*#ifndef MINIZ_NO_INFLATE_APIS*/

// ------------------- Low-level Compression (independent from all decompression API's)
#ifndef MINIZ_NO_DEFLATE_APIS

// Purposely making these tables static for faster init and thread safety.
স্থির ধ্রুবক mz_uint16 s_tdefl_len_sym[256] = {
  257,258,259,260,261,262,263,264,265,265,266,266,267,267,268,268,269,269,269,269,270,270,270,270,271,271,271,271,272,272,272,272,
  273,273,273,273,273,273,273,273,274,274,274,274,274,274,274,274,275,275,275,275,275,275,275,275,276,276,276,276,276,276,276,276,
  277,277,277,277,277,277,277,277,277,277,277,277,277,277,277,277,278,278,278,278,278,278,278,278,278,278,278,278,278,278,278,278,
  279,279,279,279,279,279,279,279,279,279,279,279,279,279,279,279,280,280,280,280,280,280,280,280,280,280,280,280,280,280,280,280,
  281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,
  282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,
  283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,
  284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,285 };

স্থির ধ্রুবক mz_uint8 s_tdefl_len_extra[256] = {
  0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0 };

স্থির ধ্রুবক mz_uint8 s_tdefl_small_dist_sym[512] = {
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

স্থির ধ্রুবক mz_uint8 s_tdefl_small_dist_extra[512] = {
  0,0,0,0,1,1,1,1,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
  6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
  6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7 };

স্থির ধ্রুবক mz_uint8 s_tdefl_large_dist_sym[128] = {
  0,0,18,19,20,20,21,21,22,22,22,22,23,23,23,23,24,24,24,24,24,24,24,24,25,25,25,25,25,25,25,25,26,26,26,26,26,26,26,26,26,26,26,26,
  26,26,26,26,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,
  28,28,28,28,28,28,28,28,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29 };

স্থির ধ্রুবক mz_uint8 s_tdefl_large_dist_extra[128] = {
  0,0,8,8,9,9,9,9,10,10,10,10,10,10,10,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,
  12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
  13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13 };

// Radix sorts tdefl_sym_freq[] array by 16-bit key m_key. Returns ptr to sorted values.
প্রকারলেখ কাঠামো { mz_uint16 m_চাবি, m_sym_সূচক; } tdefl_sym_freq;
স্থির tdefl_sym_freq* tdefl_radix_sort_syms(mz_uint অঙ্ক_syms, tdefl_sym_freq* pSyms0, tdefl_sym_freq* pSyms1)
{
  mz_uint32 যোগ_passes = 2, pass_shift, pass, i, hist[256 * 2]; tdefl_sym_freq* pCur_syms = pSyms0, *pNew_syms = pSyms1; MZ_CLEAR_ARR(hist);
  জন্য (i = 0; i < অঙ্ক_syms; i++) { mz_uint freq = pSyms0[i].m_চাবি; hist[freq & 0xFF]++; hist[256 + ((freq >> 8) & 0xFF)]++; }
  যখন ((যোগ_passes > 1) && (অঙ্ক_syms == hist[(যোগ_passes - 1) * 256])) যোগ_passes--;
  জন্য (pass_shift = 0, pass = 0; pass < যোগ_passes; pass++, pass_shift += 8)
  {
    ধ্রুবক mz_uint32* pHist = &hist[pass << 8];
    mz_uint offsets[256], cur_ofs = 0;
    জন্য (i = 0; i < 256; i++) { offsets[i] = cur_ofs; cur_ofs += pHist[i]; }
    জন্য (i = 0; i < অঙ্ক_syms; i++) pNew_syms[offsets[(pCur_syms[i].m_চাবি >> pass_shift) & 0xFF]++] = pCur_syms[i];
    { tdefl_sym_freq* t = pCur_syms; pCur_syms = pNew_syms; pNew_syms = t; }
  }
  ফেরত pCur_syms;
}

// tdefl_calculate_minimum_redundancy() originally written by: Alistair Moffat, alistair@cs.mu.oz.au, Jyrki Katajainen, jyrki@diku.dk, November 1996.
স্থির শূন্য tdefl_calculate_minimum_redundancy(tdefl_sym_freq *A, পূর্ণসংখ্যা n)
{
  পূর্ণসংখ্যা মূল, leaf, পরবর্তী, avbl, used, dpth;
  যদি (n==0) ফেরত; অন্যথা যদি (n==1) { A[0].m_চাবি = 1; ফেরত; }
  A[0].m_চাবি += A[1].m_চাবি; মূল = 0; leaf = 2;
  জন্য (পরবর্তী=1; পরবর্তী < n-1; পরবর্তী++)
  {
    যদি (leaf>=n || A[মূল].m_চাবি<A[leaf].m_চাবি) { A[পরবর্তী].m_চাবি = A[মূল].m_চাবি; A[মূল++].m_চাবি = (mz_uint16)পরবর্তী; } অন্যথা A[পরবর্তী].m_চাবি = A[leaf++].m_চাবি;
    যদি (leaf>=n || (মূল<পরবর্তী && A[মূল].m_চাবি<A[leaf].m_চাবি)) { A[পরবর্তী].m_চাবি = (mz_uint16)(A[পরবর্তী].m_চাবি + A[মূল].m_চাবি); A[মূল++].m_চাবি = (mz_uint16)পরবর্তী; } অন্যথা A[পরবর্তী].m_চাবি = (mz_uint16)(A[পরবর্তী].m_চাবি + A[leaf++].m_চাবি);
  }
  A[n-2].m_চাবি = 0; জন্য (পরবর্তী=n-3; পরবর্তী>=0; পরবর্তী--) A[পরবর্তী].m_চাবি = A[A[পরবর্তী].m_চাবি].m_চাবি+1;
  avbl = 1; used = dpth = 0; মূল = n-2; পরবর্তী = n-1;
  যখন (avbl>0)
  {
    যখন (মূল>=0 && (পূর্ণসংখ্যা)A[মূল].m_চাবি==dpth) { used++; মূল--; }
    যখন (avbl>used) { A[পরবর্তী--].m_চাবি = (mz_uint16)(dpth); avbl--; }
    avbl = 2*used; dpth++; used = 0;
  }
}

// Limits canonical Huffman code table's max code size.
গণনা { TDEFL_MAX_SUPPORTED_HUFF_CODESIZE = 32 };
স্থির শূন্য tdefl_huffman_enforce_max_code_আকার(পূর্ণসংখ্যা *p_অঙ্ক_codes, পূর্ণসংখ্যা code_list_len, পূর্ণসংখ্যা max_code_আকার)
{
  পূর্ণসংখ্যা i; mz_uint32 যোগ = 0; যদি (code_list_len <= 1) ফেরত;
  জন্য (i = max_code_আকার + 1; i <= TDEFL_MAX_SUPPORTED_HUFF_CODESIZE; i++) p_অঙ্ক_codes[max_code_আকার] += p_অঙ্ক_codes[i];
  জন্য (i = max_code_আকার; i > 0; i--) যোগ += (((mz_uint32)p_অঙ্ক_codes[i]) << (max_code_আকার - i));
  যখন (যোগ != (1UL << max_code_আকার))
  {
    p_অঙ্ক_codes[max_code_আকার]--;
    জন্য (i = max_code_আকার - 1; i > 0; i--) যদি (p_অঙ্ক_codes[i]) { p_অঙ্ক_codes[i]--; p_অঙ্ক_codes[i + 1] += 2; বিরতি; }
    যোগ--;
  }
}

স্থির শূন্য tdefl_optimize_huffman_table(tdefl_compressor *d, পূর্ণসংখ্যা table_অঙ্ক, পূর্ণসংখ্যা table_len, পূর্ণসংখ্যা code_আকার_limit, পূর্ণসংখ্যা static_table)
{
  পূর্ণসংখ্যা i, j, l, অঙ্ক_codes[1 + TDEFL_MAX_SUPPORTED_HUFF_CODESIZE]; mz_uint পরবর্তী_code[TDEFL_MAX_SUPPORTED_HUFF_CODESIZE + 1]; MZ_CLEAR_ARR(অঙ্ক_codes);
  যদি (static_table)
  {
    জন্য (i = 0; i < table_len; i++) অঙ্ক_codes[d->m_huff_code_sizes[table_অঙ্ক][i]]++;
  }
  অন্যথা
  {
    tdefl_sym_freq syms0[TDEFL_MAX_HUFF_SYMBOLS], syms1[TDEFL_MAX_HUFF_SYMBOLS], *pSyms;
    পূর্ণসংখ্যা অঙ্ক_used_syms = 0;
    ধ্রুবক mz_uint16 *p_Sym_গুনতি = &d->m_huff_গুনতি[table_অঙ্ক][0];
    জন্য (i = 0; i < table_len; i++) যদি (p_Sym_গুনতি[i]) { syms0[অঙ্ক_used_syms].m_চাবি = (mz_uint16)p_Sym_গুনতি[i]; syms0[অঙ্ক_used_syms++].m_sym_সূচক = (mz_uint16)i; }

    pSyms = tdefl_radix_sort_syms(অঙ্ক_used_syms, syms0, syms1); tdefl_calculate_minimum_redundancy(pSyms, অঙ্ক_used_syms);

    জন্য (i = 0; i < অঙ্ক_used_syms; i++) অঙ্ক_codes[pSyms[i].m_চাবি]++;

    tdefl_huffman_enforce_max_code_আকার(অঙ্ক_codes, অঙ্ক_used_syms, code_আকার_limit);

    MZ_CLEAR_ARR(d->m_huff_code_sizes[table_অঙ্ক]); MZ_CLEAR_ARR(d->m_huff_codes[table_অঙ্ক]);
    জন্য (i = 1, j = অঙ্ক_used_syms; i <= code_আকার_limit; i++)
      জন্য (l = অঙ্ক_codes[i]; l > 0; l--) d->m_huff_code_sizes[table_অঙ্ক][pSyms[--j].m_sym_সূচক] = (mz_uint8)(i);
  }

  পরবর্তী_code[1] = 0; জন্য (j = 0, i = 2; i <= code_আকার_limit; i++) পরবর্তী_code[i] = j = ((j + অঙ্ক_codes[i - 1]) << 1);

  জন্য (i = 0; i < table_len; i++)
  {
    mz_uint rev_code = 0, code, code_আকার_2; যদি ((code_আকার_2 = d->m_huff_code_sizes[table_অঙ্ক][i]) == 0) চালু;
    code = পরবর্তী_code[code_আকার_2]++; জন্য (l = code_আকার_2; l > 0; l--, code >>= 1) rev_code = (rev_code << 1) | (code & 1);
    d->m_huff_codes[table_অঙ্ক][i] = (mz_uint16)rev_code;
  }
}

#define TDEFL_PUT_BITS(b, l) করো { \
  mz_uint bits = b; mz_uint len = l; MZ_ASSERT(bits <= ((1U << len) - 1U)); \
  d->m_bit_বাফার |= (bits << d->m_bits_in); d->m_bits_in += len; \
  যখন (d->m_bits_in >= 8) { \
    যদি (d->m_pOutput_buf < d->m_pOutput_buf_end) \
      *d->m_pOutput_buf++ = (mz_uint8)(d->m_bit_বাফার); \
    d->m_bit_বাফার >>= 8; \
    d->m_bits_in -= 8; \
  } \
} MZ_MACRO_END

#define TDEFL_RLE_পূর্ব_CODE_আকার() করো { \
  যদি (rle_repeat_গুনতি) { \
    যদি (rle_repeat_গুনতি < 3) { \
      d->m_huff_গুনতি[2][পূর্ব_code_আকার] = (mz_uint16)(d->m_huff_গুনতি[2][পূর্ব_code_আকার] + rle_repeat_গুনতি); \
      যখন (rle_repeat_গুনতি--) packed_code_sizes[অঙ্ক_packed_code_sizes++] = পূর্ব_code_আকার; \
    } অন্যথা { \
      d->m_huff_গুনতি[2][16] = (mz_uint16)(d->m_huff_গুনতি[2][16] + 1); packed_code_sizes[অঙ্ক_packed_code_sizes++] = 16; packed_code_sizes[অঙ্ক_packed_code_sizes++] = (mz_uint8)(rle_repeat_গুনতি - 3); \
  } rle_repeat_গুনতি = 0; } \
} MZ_MACRO_END

#define TDEFL_RLE_ZERO_CODE_আকার() করো { \
  যদি (rle_z_গুনতি) { \
    যদি (rle_z_গুনতি < 3) { \
      d->m_huff_গুনতি[2][0] = (mz_uint16)(d->m_huff_গুনতি[2][0] + rle_z_গুনতি); যখন (rle_z_গুনতি--) packed_code_sizes[অঙ্ক_packed_code_sizes++] = 0; \
    } অন্যথা যদি (rle_z_গুনতি <= 10) { \
      d->m_huff_গুনতি[2][17] = (mz_uint16)(d->m_huff_গুনতি[2][17] + 1); packed_code_sizes[অঙ্ক_packed_code_sizes++] = 17; packed_code_sizes[অঙ্ক_packed_code_sizes++] = (mz_uint8)(rle_z_গুনতি - 3); \
    } অন্যথা { \
      d->m_huff_গুনতি[2][18] = (mz_uint16)(d->m_huff_গুনতি[2][18] + 1); packed_code_sizes[অঙ্ক_packed_code_sizes++] = 18; packed_code_sizes[অঙ্ক_packed_code_sizes++] = (mz_uint8)(rle_z_গুনতি - 11); \
  } rle_z_গুনতি = 0; } \
} MZ_MACRO_END

স্থির mz_uint8 s_tdefl_packed_code_আকার_syms_swizzle[] = { 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 };

স্থির শূন্য tdefl_start_dynamic_block(tdefl_compressor *d)
{
  পূর্ণসংখ্যা অঙ্ক_lit_codes, অঙ্ক_dist_codes, অঙ্ক_bit_lengths; mz_uint i, যোগ_code_sizes_to_pack, অঙ্ক_packed_code_sizes, rle_z_গুনতি, rle_repeat_গুনতি, packed_code_sizes_সূচক;
  mz_uint8 code_sizes_to_pack[TDEFL_MAX_HUFF_SYMBOLS_0 + TDEFL_MAX_HUFF_SYMBOLS_1], packed_code_sizes[TDEFL_MAX_HUFF_SYMBOLS_0 + TDEFL_MAX_HUFF_SYMBOLS_1], পূর্ব_code_আকার = 0xFF;

  d->m_huff_গুনতি[0][256] = 1;

  tdefl_optimize_huffman_table(d, 0, TDEFL_MAX_HUFF_SYMBOLS_0, 15, MZ_FALSE);
  tdefl_optimize_huffman_table(d, 1, TDEFL_MAX_HUFF_SYMBOLS_1, 15, MZ_FALSE);

  জন্য (অঙ্ক_lit_codes = 286; অঙ্ক_lit_codes > 257; অঙ্ক_lit_codes--) যদি (d->m_huff_code_sizes[0][অঙ্ক_lit_codes - 1]) বিরতি;
  জন্য (অঙ্ক_dist_codes = 30; অঙ্ক_dist_codes > 1; অঙ্ক_dist_codes--) যদি (d->m_huff_code_sizes[1][অঙ্ক_dist_codes - 1]) বিরতি;

  memcpy(code_sizes_to_pack, &d->m_huff_code_sizes[0][0], অঙ্ক_lit_codes);
  memcpy(code_sizes_to_pack + অঙ্ক_lit_codes, &d->m_huff_code_sizes[1][0], অঙ্ক_dist_codes);
  যোগ_code_sizes_to_pack = অঙ্ক_lit_codes + অঙ্ক_dist_codes; অঙ্ক_packed_code_sizes = 0; rle_z_গুনতি = 0; rle_repeat_গুনতি = 0;

  memset(&d->m_huff_গুনতি[2][0], 0, আকার(d->m_huff_গুনতি[2][0]) * TDEFL_MAX_HUFF_SYMBOLS_2);
  জন্য (i = 0; i < যোগ_code_sizes_to_pack; i++)
  {
    mz_uint8 code_আকার_2 = code_sizes_to_pack[i];
    যদি (!code_আকার_2)
    {
      TDEFL_RLE_পূর্ব_CODE_আকার();
      যদি (++rle_z_গুনতি == 138) { TDEFL_RLE_ZERO_CODE_আকার(); }
    }
    অন্যথা
    {
      TDEFL_RLE_ZERO_CODE_আকার();
      যদি (code_আকার_2 != পূর্ব_code_আকার)
      {
        TDEFL_RLE_পূর্ব_CODE_আকার();
        d->m_huff_গুনতি[2][code_আকার_2] = (mz_uint16)(d->m_huff_গুনতি[2][code_আকার_2] + 1); packed_code_sizes[অঙ্ক_packed_code_sizes++] = code_আকার_2;
      }
      অন্যথা যদি (++rle_repeat_গুনতি == 6)
      {
        TDEFL_RLE_পূর্ব_CODE_আকার();
      }
    }
    পূর্ব_code_আকার = code_আকার_2;
  }
  যদি (rle_repeat_গুনতি) { TDEFL_RLE_পূর্ব_CODE_আকার(); } অন্যথা { TDEFL_RLE_ZERO_CODE_আকার(); }

  tdefl_optimize_huffman_table(d, 2, TDEFL_MAX_HUFF_SYMBOLS_2, 7, MZ_FALSE);

  TDEFL_PUT_BITS(2, 2);

  TDEFL_PUT_BITS(অঙ্ক_lit_codes - 257, 5);
  TDEFL_PUT_BITS(অঙ্ক_dist_codes - 1, 5);

  জন্য (অঙ্ক_bit_lengths = 18; অঙ্ক_bit_lengths >= 0; অঙ্ক_bit_lengths--) যদি (d->m_huff_code_sizes[2][s_tdefl_packed_code_আকার_syms_swizzle[অঙ্ক_bit_lengths]]) বিরতি;
  অঙ্ক_bit_lengths = MZ_MAX(4, (অঙ্ক_bit_lengths + 1)); TDEFL_PUT_BITS(অঙ্ক_bit_lengths - 4, 4);
  জন্য (i = 0; (পূর্ণসংখ্যা)i < অঙ্ক_bit_lengths; i++) TDEFL_PUT_BITS(d->m_huff_code_sizes[2][s_tdefl_packed_code_আকার_syms_swizzle[i]], 3);

  জন্য (packed_code_sizes_সূচক = 0; packed_code_sizes_সূচক < অঙ্ক_packed_code_sizes; )
  {
    mz_uint code = packed_code_sizes[packed_code_sizes_সূচক++]; MZ_ASSERT(code < TDEFL_MAX_HUFF_SYMBOLS_2);
    TDEFL_PUT_BITS(d->m_huff_codes[2][code], d->m_huff_code_sizes[2][code]);
    যদি (code >= 16) TDEFL_PUT_BITS(packed_code_sizes[packed_code_sizes_সূচক++], "\02\03\07"[code - 16]);
  }
}

স্থির শূন্য tdefl_start_static_block(tdefl_compressor *d)
{
  mz_uint i;
  mz_uint8 *p = &d->m_huff_code_sizes[0][0];

  জন্য (i = 0; i <= 143; ++i) *p++ = 8;
  জন্য ( ; i <= 255; ++i) *p++ = 9;
  জন্য ( ; i <= 279; ++i) *p++ = 7;
  জন্য ( ; i <= 287; ++i) *p++ = 8;

  memset(d->m_huff_code_sizes[1], 5, 32);

  tdefl_optimize_huffman_table(d, 0, 288, 15, MZ_TRUE);
  tdefl_optimize_huffman_table(d, 1, 32, 15, MZ_TRUE);

  TDEFL_PUT_BITS(1, 2);
}

স্থির ধ্রুবক mz_uint mz_bitmasks[17] = { 0x0000, 0x0001, 0x0003, 0x0007, 0x000F, 0x001F, 0x003F, 0x007F, 0x00FF, 0x01FF, 0x03FF, 0x07FF, 0x0FFF, 0x1FFF, 0x3FFF, 0x7FFF, 0xFFFF };

#যদি MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN && MINIZ_HAS_64BIT_REGISTERS
স্থির mz_bool tdefl_compress_lz_codes(tdefl_compressor *d)
{
  mz_uint flags;
  mz_uint8 *pLZ_codes;
  mz_uint8 *pOutput_buf = d->m_pOutput_buf;
  mz_uint8 *pLZ_code_buf_end = d->m_pLZ_code_buf;
  mz_uint64 bit_বাফার = d->m_bit_বাফার;
  mz_uint bits_in = d->m_bits_in;

#define TDEFL_PUT_BITS_FAST(b, l) { bit_বাফার |= (((mz_uint64)(b)) << bits_in); bits_in += (l); }

  flags = 1;
  জন্য (pLZ_codes = d->m_lz_code_buf; pLZ_codes < pLZ_code_buf_end; flags >>= 1)
  {
    যদি (flags == 1)
      flags = *pLZ_codes++ | 0x100;

    যদি (flags & 1)
    {
      mz_uint s0, s1, n0, n1, sym, অঙ্ক_extra_bits;
      mz_uint match_len = pLZ_codes[0], match_dist = *(ধ্রুবক mz_uint16 *)(pLZ_codes + 1); pLZ_codes += 3;

      MZ_ASSERT(d->m_huff_code_sizes[0][s_tdefl_len_sym[match_len]]);
      TDEFL_PUT_BITS_FAST(d->m_huff_codes[0][s_tdefl_len_sym[match_len]], d->m_huff_code_sizes[0][s_tdefl_len_sym[match_len]]);
      TDEFL_PUT_BITS_FAST(match_len & mz_bitmasks[s_tdefl_len_extra[match_len]], s_tdefl_len_extra[match_len]);

      // This sequence coaxes MSVC into using cmov's vs. jmp's.
      s0 = s_tdefl_small_dist_sym[match_dist & 511];
      n0 = s_tdefl_small_dist_extra[match_dist & 511];
      s1 = s_tdefl_large_dist_sym[match_dist >> 8];
      n1 = s_tdefl_large_dist_extra[match_dist >> 8];
      sym = (match_dist < 512) ? s0 : s1;
      অঙ্ক_extra_bits = (match_dist < 512) ? n0 : n1;

      MZ_ASSERT(d->m_huff_code_sizes[1][sym]);
      TDEFL_PUT_BITS_FAST(d->m_huff_codes[1][sym], d->m_huff_code_sizes[1][sym]);
      TDEFL_PUT_BITS_FAST(match_dist & mz_bitmasks[অঙ্ক_extra_bits], অঙ্ক_extra_bits);
    }
    অন্যথা
    {
      mz_uint lit = *pLZ_codes++;
      MZ_ASSERT(d->m_huff_code_sizes[0][lit]);
      TDEFL_PUT_BITS_FAST(d->m_huff_codes[0][lit], d->m_huff_code_sizes[0][lit]);

      যদি (((flags & 2) == 0) && (pLZ_codes < pLZ_code_buf_end))
      {
        flags >>= 1;
        lit = *pLZ_codes++;
        MZ_ASSERT(d->m_huff_code_sizes[0][lit]);
        TDEFL_PUT_BITS_FAST(d->m_huff_codes[0][lit], d->m_huff_code_sizes[0][lit]);

        যদি (((flags & 2) == 0) && (pLZ_codes < pLZ_code_buf_end))
        {
          flags >>= 1;
          lit = *pLZ_codes++;
          MZ_ASSERT(d->m_huff_code_sizes[0][lit]);
          TDEFL_PUT_BITS_FAST(d->m_huff_codes[0][lit], d->m_huff_code_sizes[0][lit]);
        }
      }
    }

    যদি (pOutput_buf >= d->m_pOutput_buf_end)
      ফেরত MZ_FALSE;

    *(mz_uint64*)pOutput_buf = bit_বাফার;
    pOutput_buf += (bits_in >> 3);
    bit_বাফার >>= (bits_in & ~7);
    bits_in &= 7;
  }

#undef TDEFL_PUT_BITS_FAST

  d->m_pOutput_buf = pOutput_buf;
  d->m_bits_in = 0;
  d->m_bit_বাফার = 0;

  যখন (bits_in)
  {
    mz_uint32 n = MZ_MIN(bits_in, 16);
    TDEFL_PUT_BITS((mz_uint)bit_বাফার & mz_bitmasks[n], n);
    bit_বাফার >>= n;
    bits_in -= n;
  }

  TDEFL_PUT_BITS(d->m_huff_codes[0][256], d->m_huff_code_sizes[0][256]);

  ফেরত (d->m_pOutput_buf < d->m_pOutput_buf_end);
}
#অন্যথা
স্থির mz_bool tdefl_compress_lz_codes(tdefl_compressor *d)
{
  mz_uint flags;
  mz_uint8 *pLZ_codes;

  flags = 1;
  জন্য (pLZ_codes = d->m_lz_code_buf; pLZ_codes < d->m_pLZ_code_buf; flags >>= 1)
  {
    যদি (flags == 1)
      flags = *pLZ_codes++ | 0x100;
    যদি (flags & 1)
    {
      mz_uint sym, অঙ্ক_extra_bits;
      mz_uint match_len = pLZ_codes[0], match_dist = (pLZ_codes[1] | (pLZ_codes[2] << 8)); pLZ_codes += 3;

      MZ_ASSERT(d->m_huff_code_sizes[0][s_tdefl_len_sym[match_len]]);
      TDEFL_PUT_BITS(d->m_huff_codes[0][s_tdefl_len_sym[match_len]], d->m_huff_code_sizes[0][s_tdefl_len_sym[match_len]]);
      TDEFL_PUT_BITS(match_len & mz_bitmasks[s_tdefl_len_extra[match_len]], s_tdefl_len_extra[match_len]);

      যদি (match_dist < 512)
      {
        sym = s_tdefl_small_dist_sym[match_dist]; অঙ্ক_extra_bits = s_tdefl_small_dist_extra[match_dist];
      }
      অন্যথা
      {
        sym = s_tdefl_large_dist_sym[match_dist >> 8]; অঙ্ক_extra_bits = s_tdefl_large_dist_extra[match_dist >> 8];
      }
      MZ_ASSERT(d->m_huff_code_sizes[1][sym]);
      TDEFL_PUT_BITS(d->m_huff_codes[1][sym], d->m_huff_code_sizes[1][sym]);
      TDEFL_PUT_BITS(match_dist & mz_bitmasks[অঙ্ক_extra_bits], অঙ্ক_extra_bits);
    }
    অন্যথা
    {
      mz_uint lit = *pLZ_codes++;
      MZ_ASSERT(d->m_huff_code_sizes[0][lit]);
      TDEFL_PUT_BITS(d->m_huff_codes[0][lit], d->m_huff_code_sizes[0][lit]);
    }
  }

  TDEFL_PUT_BITS(d->m_huff_codes[0][256], d->m_huff_code_sizes[0][256]);

  ফেরত (d->m_pOutput_buf < d->m_pOutput_buf_end);
}
#endif // MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN && MINIZ_HAS_64BIT_REGISTERS

স্থির mz_bool tdefl_compress_block(tdefl_compressor *d, mz_bool static_block)
{
  যদি (static_block)
    tdefl_start_static_block(d);
  অন্যথা
    tdefl_start_dynamic_block(d);
  ফেরত tdefl_compress_lz_codes(d);
}

স্থির পূর্ণসংখ্যা tdefl_flush_block(tdefl_compressor *d, পূর্ণসংখ্যা flush)
{
  mz_uint saved_bit_buf, saved_bits_in;
  mz_uint8 *pSaved_output_buf;
  mz_bool comp_block_succeeded = MZ_FALSE;
  পূর্ণসংখ্যা n, use_raw_block = ((d->m_flags & TDEFL_FORCE_ALL_RAW_BLOCKS) != 0) && (d->m_lookahead_pos - d->m_lz_code_buf_dict_pos) <= d->m_dict_আকার;
  mz_uint8 *pOutput_buf_start = ((d->m_pPut_buf_func == ফাঁকা) && ((*d->m_p_Out_buf_আকার - d->m_out_buf_ofs) >= TDEFL_OUT_BUF_আকার)) ? ((mz_uint8 *)d->m_pOut_buf + d->m_out_buf_ofs) : d->m_output_buf;

  d->m_pOutput_buf = pOutput_buf_start;
  d->m_pOutput_buf_end = d->m_pOutput_buf + TDEFL_OUT_BUF_আকার - 16;

  MZ_ASSERT(!d->m_output_flush_remaining);
  d->m_output_flush_ofs = 0;
  d->m_output_flush_remaining = 0;

  *d->m_pLZ_flags = (mz_uint8)(*d->m_pLZ_flags >> d->m_অঙ্ক_flags_বাম);
  d->m_pLZ_code_buf -= (d->m_অঙ্ক_flags_বাম == 8);

  যদি ((d->m_flags & TDEFL_WRITE_ZLIB_HEADER) && (!d->m_block_সূচক))
  {
    TDEFL_PUT_BITS(0x78, 8); TDEFL_PUT_BITS(0x01, 8);
  }

  TDEFL_PUT_BITS(flush == TDEFL_FINISH, 1);

  pSaved_output_buf = d->m_pOutput_buf; saved_bit_buf = d->m_bit_বাফার; saved_bits_in = d->m_bits_in;

  যদি (!use_raw_block)
    comp_block_succeeded = tdefl_compress_block(d, (d->m_flags & TDEFL_FORCE_ALL_STATIC_BLOCKS) || (d->m_যোগ_lz_bytes < 48));

  // If the block gets expanded, forget the current contents of the output buffer and send a raw block instead.
  যদি ( ((use_raw_block) || ((d->m_যোগ_lz_bytes) && ((d->m_pOutput_buf - pSaved_output_buf + 1U) >= d->m_যোগ_lz_bytes))) &&
       ((d->m_lookahead_pos - d->m_lz_code_buf_dict_pos) <= d->m_dict_আকার) )
  {
    mz_uint i; d->m_pOutput_buf = pSaved_output_buf; d->m_bit_বাফার = saved_bit_buf; d->m_bits_in = saved_bits_in;
    TDEFL_PUT_BITS(0, 2);
    যদি (d->m_bits_in) { TDEFL_PUT_BITS(0, 8 - d->m_bits_in); }
    জন্য (i = 2; i; --i, d->m_যোগ_lz_bytes ^= 0xFFFF)
    {
      TDEFL_PUT_BITS(d->m_যোগ_lz_bytes & 0xFFFF, 16);
    }
    জন্য (i = 0; i < d->m_যোগ_lz_bytes; ++i)
    {
      TDEFL_PUT_BITS(d->m_dict[(d->m_lz_code_buf_dict_pos + i) & TDEFL_LZ_DICT_আকার_MASK], 8);
    }
  }
  // Check for the extremely unlikely (if not impossible) case of the compressed block not fitting into the output buffer when using dynamic codes.
  অন্যথা যদি (!comp_block_succeeded)
  {
    d->m_pOutput_buf = pSaved_output_buf; d->m_bit_বাফার = saved_bit_buf; d->m_bits_in = saved_bits_in;
    tdefl_compress_block(d, MZ_TRUE);
  }

  যদি (flush)
  {
    যদি (flush == TDEFL_FINISH)
    {
      যদি (d->m_bits_in) { TDEFL_PUT_BITS(0, 8 - d->m_bits_in); }
      যদি (d->m_flags & TDEFL_WRITE_ZLIB_HEADER) { mz_uint i, a = d->m_adler32; জন্য (i = 0; i < 4; i++) { TDEFL_PUT_BITS((a >> 24) & 0xFF, 8); a <<= 8; } }
    }
    অন্যথা
    {
      mz_uint i, z = 0; TDEFL_PUT_BITS(0, 3); যদি (d->m_bits_in) { TDEFL_PUT_BITS(0, 8 - d->m_bits_in); } জন্য (i = 2; i; --i, z ^= 0xFFFF) { TDEFL_PUT_BITS(z & 0xFFFF, 16); }
    }
  }

  MZ_ASSERT(d->m_pOutput_buf < d->m_pOutput_buf_end);

  memset(&d->m_huff_গুনতি[0][0], 0, আকার(d->m_huff_গুনতি[0][0]) * TDEFL_MAX_HUFF_SYMBOLS_0);
  memset(&d->m_huff_গুনতি[1][0], 0, আকার(d->m_huff_গুনতি[1][0]) * TDEFL_MAX_HUFF_SYMBOLS_1);

  d->m_pLZ_code_buf = d->m_lz_code_buf + 1; d->m_pLZ_flags = d->m_lz_code_buf; d->m_অঙ্ক_flags_বাম = 8; d->m_lz_code_buf_dict_pos += d->m_যোগ_lz_bytes; d->m_যোগ_lz_bytes = 0; d->m_block_সূচক++;

  যদি ((n = (পূর্ণসংখ্যা)(d->m_pOutput_buf - pOutput_buf_start)) != 0)
  {
    যদি (d->m_pPut_buf_func)
    {
      *d->m_p_In_buf_আকার = d->m_pSrc - (ধ্রুবক mz_uint8 *)d->m_pIn_buf;
      যদি (!(*d->m_pPut_buf_func)(d->m_output_buf, n, d->m_pPut_buf_user))
        ফেরত (d->m_পূর্ব_return_status = TDEFL_STATUS_PUT_BUF_FAILED);
    }
    অন্যথা যদি (pOutput_buf_start == d->m_output_buf)
    {
      পূর্ণসংখ্যা bytes_to_copy = (পূর্ণসংখ্যা)MZ_MIN((size_t)n, (size_t)(*d->m_p_Out_buf_আকার - d->m_out_buf_ofs));
      memcpy((mz_uint8 *)d->m_pOut_buf + d->m_out_buf_ofs, d->m_output_buf, bytes_to_copy);
      d->m_out_buf_ofs += bytes_to_copy;
      যদি ((n -= bytes_to_copy) != 0)
      {
        d->m_output_flush_ofs = bytes_to_copy;
        d->m_output_flush_remaining = n;
      }
    }
    অন্যথা
    {
      d->m_out_buf_ofs += n;
    }
  }

  ফেরত d->m_output_flush_remaining;
}

#যদি MINIZ_USE_UNALIGNED_LOADS_AND_STORES
#define TDEFL_READ_UNALIGNED_WORD(p) *(ধ্রুবক mz_uint16*)(p)
স্থির MZ_FORCEINLINE শূন্য tdefl_find_match(tdefl_compressor *d, mz_uint lookahead_pos, mz_uint max_dist, mz_uint max_match_len, mz_uint *pMatch_dist, mz_uint *pMatch_len)
{
  mz_uint dist, pos = lookahead_pos & TDEFL_LZ_DICT_আকার_MASK, match_len = *pMatch_len, probe_pos = pos, পরবর্তী_probe_pos, probe_len;
  mz_uint অঙ্ক_probes_বাম = d->m_max_probes[match_len >= 32];
  ধ্রুবক mz_uint16 *s = (ধ্রুবক mz_uint16*)(d->m_dict + pos), *p, *q;
  mz_uint16 c01 = TDEFL_READ_UNALIGNED_WORD(&d->m_dict[pos + match_len - 1]), s01 = TDEFL_READ_UNALIGNED_WORD(s);
  MZ_ASSERT(max_match_len <= TDEFL_MAX_MATCH_LEN); যদি (max_match_len <= match_len) ফেরত;
  জন্য ( ; ; )
  {
    জন্য ( ; ; )
    {
      যদি (--অঙ্ক_probes_বাম == 0) ফেরত;
      #define TDEFL_PROBE \
        পরবর্তী_probe_pos = d->m_পরবর্তী[probe_pos]; \
        যদি ((!পরবর্তী_probe_pos) || ((dist = (mz_uint16)(lookahead_pos - পরবর্তী_probe_pos)) > max_dist)) ফেরত; \
        probe_pos = পরবর্তী_probe_pos & TDEFL_LZ_DICT_আকার_MASK; \
        যদি (TDEFL_READ_UNALIGNED_WORD(&d->m_dict[probe_pos + match_len - 1]) == c01) বিরতি;
      TDEFL_PROBE
      TDEFL_PROBE
      TDEFL_PROBE
    }
    যদি (!dist) বিরতি;
    q = (ধ্রুবক mz_uint16*)(d->m_dict + probe_pos);
    যদি (TDEFL_READ_UNALIGNED_WORD(q) != s01) চালু;
    p = s; probe_len = 32;
    করো { } যখন ( (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) && (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) &&
                   (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) && (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) && (--probe_len > 0) );
    যদি (!probe_len)
    {
      *pMatch_dist = dist; *pMatch_len = MZ_MIN(max_match_len, TDEFL_MAX_MATCH_LEN); বিরতি;
    }
    অন্যথা যদি ((probe_len = ((mz_uint)(p - s) * 2) + (mz_uint)(*(ধ্রুবক mz_uint8*)p == *(ধ্রুবক mz_uint8*)q)) > match_len)
    {
      *pMatch_dist = dist; যদি ((*pMatch_len = match_len = MZ_MIN(max_match_len, probe_len)) == max_match_len) বিরতি;
      c01 = TDEFL_READ_UNALIGNED_WORD(&d->m_dict[pos + match_len - 1]);
    }
  }
}
#অন্যথা
স্থির MZ_FORCEINLINE শূন্য tdefl_find_match(tdefl_compressor *d, mz_uint lookahead_pos, mz_uint max_dist, mz_uint max_match_len, mz_uint *pMatch_dist, mz_uint *pMatch_len)
{
  mz_uint dist, pos = lookahead_pos & TDEFL_LZ_DICT_আকার_MASK, match_len = *pMatch_len, probe_pos = pos, পরবর্তী_probe_pos, probe_len;
  mz_uint অঙ্ক_probes_বাম = d->m_max_probes[match_len >= 32];
  ধ্রুবক mz_uint8 *s = d->m_dict + pos, *p, *q;
  mz_uint8 c0 = d->m_dict[pos + match_len], c1 = d->m_dict[pos + match_len - 1];
  MZ_ASSERT(max_match_len <= TDEFL_MAX_MATCH_LEN); যদি (max_match_len <= match_len) ফেরত;
  জন্য ( ; ; )
  {
    জন্য ( ; ; )
    {
      যদি (--অঙ্ক_probes_বাম == 0) ফেরত;
      #define TDEFL_PROBE \
        পরবর্তী_probe_pos = d->m_পরবর্তী[probe_pos]; \
        যদি ((!পরবর্তী_probe_pos) || ((dist = (mz_uint16)(lookahead_pos - পরবর্তী_probe_pos)) > max_dist)) ফেরত; \
        probe_pos = পরবর্তী_probe_pos & TDEFL_LZ_DICT_আকার_MASK; \
        যদি ((d->m_dict[probe_pos + match_len] == c0) && (d->m_dict[probe_pos + match_len - 1] == c1)) বিরতি;
      TDEFL_PROBE
      TDEFL_PROBE
      TDEFL_PROBE
    }
    যদি (!dist) বিরতি;
    p = s; q = d->m_dict + probe_pos;
    জন্য (probe_len = 0; probe_len < max_match_len; probe_len++) {
        যদি (*p++ != *q++) বিরতি;
    }
    যদি (probe_len > match_len)
    {
      *pMatch_dist = dist;
      যদি ((*pMatch_len = match_len = probe_len) == max_match_len) ফেরত;
      c0 = d->m_dict[pos + match_len]; c1 = d->m_dict[pos + match_len - 1];
    }
  }
}
#endif // #if MINIZ_USE_UNALIGNED_LOADS_AND_STORES

#যদি MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
স্থির mz_bool tdefl_compress_fast(tdefl_compressor *d)
{
  // Faster, minimally featured LZRW1-style match+parse loop with better register utilization. Intended for applications where raw throughput is valued more highly than ratio.
  mz_uint lookahead_pos = d->m_lookahead_pos, lookahead_আকার = d->m_lookahead_আকার, dict_আকার = d->m_dict_আকার, যোগ_lz_bytes = d->m_যোগ_lz_bytes, অঙ্ক_flags_বাম = d->m_অঙ্ক_flags_বাম;
  mz_uint8 *pLZ_code_buf = d->m_pLZ_code_buf, *pLZ_flags = d->m_pLZ_flags;
  mz_uint cur_pos = lookahead_pos & TDEFL_LZ_DICT_আকার_MASK;

  যখন ((d->m_src_buf_বাম) || ((d->m_flush) && (lookahead_আকার)))
  {
    ধ্রুবক mz_uint TDEFL_COMP_FAST_LOOKAHEAD_আকার = 4096;
    mz_uint dst_pos = (lookahead_pos + lookahead_আকার) & TDEFL_LZ_DICT_আকার_MASK;
    mz_uint অঙ্ক_bytes_to_process = (mz_uint)MZ_MIN(d->m_src_buf_বাম, TDEFL_COMP_FAST_LOOKAHEAD_আকার - lookahead_আকার);
    d->m_src_buf_বাম -= অঙ্ক_bytes_to_process;
    lookahead_আকার += অঙ্ক_bytes_to_process;

    যখন (অঙ্ক_bytes_to_process)
    {
      mz_uint32 n = MZ_MIN(TDEFL_LZ_DICT_আকার - dst_pos, অঙ্ক_bytes_to_process);
      memcpy(d->m_dict + dst_pos, d->m_pSrc, n);
      যদি (dst_pos < (TDEFL_MAX_MATCH_LEN - 1))
        memcpy(d->m_dict + TDEFL_LZ_DICT_আকার + dst_pos, d->m_pSrc, MZ_MIN(n, (TDEFL_MAX_MATCH_LEN - 1) - dst_pos));
      d->m_pSrc += n;
      dst_pos = (dst_pos + n) & TDEFL_LZ_DICT_আকার_MASK;
      অঙ্ক_bytes_to_process -= n;
    }

    dict_আকার = MZ_MIN(TDEFL_LZ_DICT_আকার - lookahead_আকার, dict_আকার);
    যদি ((!d->m_flush) && (lookahead_আকার < TDEFL_COMP_FAST_LOOKAHEAD_আকার)) বিরতি;

    যখন (lookahead_আকার >= 4)
    {
      mz_uint cur_match_dist, cur_match_len = 1;
      mz_uint8 *pCur_dict = d->m_dict + cur_pos;
      mz_uint first_trigram = (*(ধ্রুবক mz_uint32 *)pCur_dict) & 0xFFFFFF;
      mz_uint hash = (first_trigram ^ (first_trigram >> (24 - (TDEFL_LZ_HASH_BITS - 8)))) & TDEFL_LEVEL1_HASH_আকার_MASK;
      mz_uint probe_pos = d->m_hash[hash];
      d->m_hash[hash] = (mz_uint16)lookahead_pos;

      যদি (((cur_match_dist = (mz_uint16)(lookahead_pos - probe_pos)) <= dict_আকার) && ((*(ধ্রুবক mz_uint32 *)(d->m_dict + (probe_pos &= TDEFL_LZ_DICT_আকার_MASK)) & 0xFFFFFF) == first_trigram))
      {
        ধ্রুবক mz_uint16 *p = (ধ্রুবক mz_uint16 *)pCur_dict;
        ধ্রুবক mz_uint16 *q = (ধ্রুবক mz_uint16 *)(d->m_dict + probe_pos);
        mz_uint32 probe_len = 32;
        করো { } যখন ( (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) && (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) &&
          (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) && (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) && (--probe_len > 0) );
        cur_match_len = ((mz_uint)(p - (ধ্রুবক mz_uint16 *)pCur_dict) * 2) + (mz_uint)(*(ধ্রুবক mz_uint8 *)p == *(ধ্রুবক mz_uint8 *)q);
        যদি (!probe_len)
          cur_match_len = cur_match_dist ? TDEFL_MAX_MATCH_LEN : 0;

        যদি ((cur_match_len < TDEFL_MIN_MATCH_LEN) || ((cur_match_len == TDEFL_MIN_MATCH_LEN) && (cur_match_dist >= 8U*1024U)))
        {
          cur_match_len = 1;
          *pLZ_code_buf++ = (mz_uint8)first_trigram;
          *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
          d->m_huff_গুনতি[0][(mz_uint8)first_trigram]++;
        }
        অন্যথা
        {
          mz_uint32 s0, s1;
          cur_match_len = MZ_MIN(cur_match_len, lookahead_আকার);

          MZ_ASSERT((cur_match_len >= TDEFL_MIN_MATCH_LEN) && (cur_match_dist >= 1) && (cur_match_dist <= TDEFL_LZ_DICT_আকার));

          cur_match_dist--;

          pLZ_code_buf[0] = (mz_uint8)(cur_match_len - TDEFL_MIN_MATCH_LEN);
          *(mz_uint16 *)(&pLZ_code_buf[1]) = (mz_uint16)cur_match_dist;
          pLZ_code_buf += 3;
          *pLZ_flags = (mz_uint8)((*pLZ_flags >> 1) | 0x80);

          s0 = s_tdefl_small_dist_sym[cur_match_dist & 511];
          s1 = s_tdefl_large_dist_sym[cur_match_dist >> 8];
          d->m_huff_গুনতি[1][(cur_match_dist < 512) ? s0 : s1]++;

          d->m_huff_গুনতি[0][s_tdefl_len_sym[cur_match_len - TDEFL_MIN_MATCH_LEN]]++;
        }
      }
      অন্যথা
      {
        *pLZ_code_buf++ = (mz_uint8)first_trigram;
        *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
        d->m_huff_গুনতি[0][(mz_uint8)first_trigram]++;
      }

      যদি (--অঙ্ক_flags_বাম == 0) { অঙ্ক_flags_বাম = 8; pLZ_flags = pLZ_code_buf++; }

      যোগ_lz_bytes += cur_match_len;
      lookahead_pos += cur_match_len;
      dict_আকার = MZ_MIN(dict_আকার + cur_match_len, TDEFL_LZ_DICT_আকার);
      cur_pos = (cur_pos + cur_match_len) & TDEFL_LZ_DICT_আকার_MASK;
      MZ_ASSERT(lookahead_আকার >= cur_match_len);
      lookahead_আকার -= cur_match_len;

      যদি (pLZ_code_buf > &d->m_lz_code_buf[TDEFL_LZ_CODE_BUF_আকার - 8])
      {
        পূর্ণসংখ্যা n;
        d->m_lookahead_pos = lookahead_pos; d->m_lookahead_আকার = lookahead_আকার; d->m_dict_আকার = dict_আকার;
        d->m_যোগ_lz_bytes = যোগ_lz_bytes; d->m_pLZ_code_buf = pLZ_code_buf; d->m_pLZ_flags = pLZ_flags; d->m_অঙ্ক_flags_বাম = অঙ্ক_flags_বাম;
        যদি ((n = tdefl_flush_block(d, 0)) != 0)
          ফেরত (n < 0) ? MZ_FALSE : MZ_TRUE;
        যোগ_lz_bytes = d->m_যোগ_lz_bytes; pLZ_code_buf = d->m_pLZ_code_buf; pLZ_flags = d->m_pLZ_flags; অঙ্ক_flags_বাম = d->m_অঙ্ক_flags_বাম;
      }
    }

    যখন (lookahead_আকার)
    {
      mz_uint8 lit = d->m_dict[cur_pos];

      যোগ_lz_bytes++;
      *pLZ_code_buf++ = lit;
      *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
      যদি (--অঙ্ক_flags_বাম == 0) { অঙ্ক_flags_বাম = 8; pLZ_flags = pLZ_code_buf++; }

      d->m_huff_গুনতি[0][lit]++;

      lookahead_pos++;
      dict_আকার = MZ_MIN(dict_আকার + 1, TDEFL_LZ_DICT_আকার);
      cur_pos = (cur_pos + 1) & TDEFL_LZ_DICT_আকার_MASK;
      lookahead_আকার--;

      যদি (pLZ_code_buf > &d->m_lz_code_buf[TDEFL_LZ_CODE_BUF_আকার - 8])
      {
        পূর্ণসংখ্যা n;
        d->m_lookahead_pos = lookahead_pos; d->m_lookahead_আকার = lookahead_আকার; d->m_dict_আকার = dict_আকার;
        d->m_যোগ_lz_bytes = যোগ_lz_bytes; d->m_pLZ_code_buf = pLZ_code_buf; d->m_pLZ_flags = pLZ_flags; d->m_অঙ্ক_flags_বাম = অঙ্ক_flags_বাম;
        যদি ((n = tdefl_flush_block(d, 0)) != 0)
          ফেরত (n < 0) ? MZ_FALSE : MZ_TRUE;
        যোগ_lz_bytes = d->m_যোগ_lz_bytes; pLZ_code_buf = d->m_pLZ_code_buf; pLZ_flags = d->m_pLZ_flags; অঙ্ক_flags_বাম = d->m_অঙ্ক_flags_বাম;
      }
    }
  }

  d->m_lookahead_pos = lookahead_pos; d->m_lookahead_আকার = lookahead_আকার; d->m_dict_আকার = dict_আকার;
  d->m_যোগ_lz_bytes = যোগ_lz_bytes; d->m_pLZ_code_buf = pLZ_code_buf; d->m_pLZ_flags = pLZ_flags; d->m_অঙ্ক_flags_বাম = অঙ্ক_flags_বাম;
  ফেরত MZ_TRUE;
}
#endif // MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN

স্থির MZ_FORCEINLINE শূন্য tdefl_record_literal(tdefl_compressor *d, mz_uint8 lit)
{
  d->m_যোগ_lz_bytes++;
  *d->m_pLZ_code_buf++ = lit;
  *d->m_pLZ_flags = (mz_uint8)(*d->m_pLZ_flags >> 1); যদি (--d->m_অঙ্ক_flags_বাম == 0) { d->m_অঙ্ক_flags_বাম = 8; d->m_pLZ_flags = d->m_pLZ_code_buf++; }
  d->m_huff_গুনতি[0][lit]++;
}

স্থির MZ_FORCEINLINE শূন্য tdefl_record_match(tdefl_compressor *d, mz_uint match_len, mz_uint match_dist)
{
  mz_uint32 s0, s1;

  MZ_ASSERT((match_len >= TDEFL_MIN_MATCH_LEN) && (match_dist >= 1) && (match_dist <= TDEFL_LZ_DICT_আকার));

  d->m_যোগ_lz_bytes += match_len;

  d->m_pLZ_code_buf[0] = (mz_uint8)(match_len - TDEFL_MIN_MATCH_LEN);

  match_dist -= 1;
  d->m_pLZ_code_buf[1] = (mz_uint8)(match_dist & 0xFF);
  d->m_pLZ_code_buf[2] = (mz_uint8)(match_dist >> 8); d->m_pLZ_code_buf += 3;

  *d->m_pLZ_flags = (mz_uint8)((*d->m_pLZ_flags >> 1) | 0x80); যদি (--d->m_অঙ্ক_flags_বাম == 0) { d->m_অঙ্ক_flags_বাম = 8; d->m_pLZ_flags = d->m_pLZ_code_buf++; }

  s0 = s_tdefl_small_dist_sym[match_dist & 511]; s1 = s_tdefl_large_dist_sym[(match_dist >> 8) & 127];
  d->m_huff_গুনতি[1][(match_dist < 512) ? s0 : s1]++;

  যদি (match_len >= TDEFL_MIN_MATCH_LEN) d->m_huff_গুনতি[0][s_tdefl_len_sym[match_len - TDEFL_MIN_MATCH_LEN]]++;
}

স্থির mz_bool tdefl_compress_normal(tdefl_compressor *d)
{
  ধ্রুবক mz_uint8 *pSrc = d->m_pSrc; size_t src_buf_বাম = d->m_src_buf_বাম;
  tdefl_flush flush = d->m_flush;

  যখন ((src_buf_বাম) || ((flush) && (d->m_lookahead_আকার)))
  {
    mz_uint len_to_move, cur_match_dist, cur_match_len, cur_pos;
    // Update dictionary and hash chains. Keeps the lookahead size equal to TDEFL_MAX_MATCH_LEN.
    যদি ((d->m_lookahead_আকার + d->m_dict_আকার) >= (TDEFL_MIN_MATCH_LEN - 1))
    {
      mz_uint dst_pos = (d->m_lookahead_pos + d->m_lookahead_আকার) & TDEFL_LZ_DICT_আকার_MASK, ins_pos = d->m_lookahead_pos + d->m_lookahead_আকার - 2;
      mz_uint hash = (d->m_dict[ins_pos & TDEFL_LZ_DICT_আকার_MASK] << TDEFL_LZ_HASH_SHIFT) ^ d->m_dict[(ins_pos + 1) & TDEFL_LZ_DICT_আকার_MASK];
      mz_uint অঙ্ক_bytes_to_process = (mz_uint)MZ_MIN(src_buf_বাম, TDEFL_MAX_MATCH_LEN - d->m_lookahead_আকার);
      ধ্রুবক mz_uint8 *pSrc_end = pSrc ? pSrc + অঙ্ক_bytes_to_process : ফাঁকা;
      src_buf_বাম -= অঙ্ক_bytes_to_process;
      d->m_lookahead_আকার += অঙ্ক_bytes_to_process;
      যখন (pSrc != pSrc_end)
      {
        mz_uint8 c = *pSrc++; d->m_dict[dst_pos] = c; যদি (dst_pos < (TDEFL_MAX_MATCH_LEN - 1)) d->m_dict[TDEFL_LZ_DICT_আকার + dst_pos] = c;
        hash = ((hash << TDEFL_LZ_HASH_SHIFT) ^ c) & (TDEFL_LZ_HASH_আকার - 1);
        d->m_পরবর্তী[ins_pos & TDEFL_LZ_DICT_আকার_MASK] = d->m_hash[hash]; d->m_hash[hash] = (mz_uint16)(ins_pos);
        dst_pos = (dst_pos + 1) & TDEFL_LZ_DICT_আকার_MASK; ins_pos++;
      }
    }
    অন্যথা
    {
      যখন ((src_buf_বাম) && (d->m_lookahead_আকার < TDEFL_MAX_MATCH_LEN))
      {
        mz_uint8 c = *pSrc++;
        mz_uint dst_pos = (d->m_lookahead_pos + d->m_lookahead_আকার) & TDEFL_LZ_DICT_আকার_MASK;
        src_buf_বাম--;
        d->m_dict[dst_pos] = c;
        যদি (dst_pos < (TDEFL_MAX_MATCH_LEN - 1))
          d->m_dict[TDEFL_LZ_DICT_আকার + dst_pos] = c;
        যদি ((++d->m_lookahead_আকার + d->m_dict_আকার) >= TDEFL_MIN_MATCH_LEN)
        {
          mz_uint ins_pos = d->m_lookahead_pos + (d->m_lookahead_আকার - 1) - 2;
          mz_uint hash = ((d->m_dict[ins_pos & TDEFL_LZ_DICT_আকার_MASK] << (TDEFL_LZ_HASH_SHIFT * 2)) ^ (d->m_dict[(ins_pos + 1) & TDEFL_LZ_DICT_আকার_MASK] << TDEFL_LZ_HASH_SHIFT) ^ c) & (TDEFL_LZ_HASH_আকার - 1);
          d->m_পরবর্তী[ins_pos & TDEFL_LZ_DICT_আকার_MASK] = d->m_hash[hash]; d->m_hash[hash] = (mz_uint16)(ins_pos);
        }
      }
    }
    d->m_dict_আকার = MZ_MIN(TDEFL_LZ_DICT_আকার - d->m_lookahead_আকার, d->m_dict_আকার);
    যদি ((!flush) && (d->m_lookahead_আকার < TDEFL_MAX_MATCH_LEN))
      বিরতি;

    // Simple lazy/greedy parsing state machine.
    len_to_move = 1; cur_match_dist = 0; cur_match_len = d->m_saved_match_len ? d->m_saved_match_len : (TDEFL_MIN_MATCH_LEN - 1); cur_pos = d->m_lookahead_pos & TDEFL_LZ_DICT_আকার_MASK;
    যদি (d->m_flags & (TDEFL_RLE_MATCHES | TDEFL_FORCE_ALL_RAW_BLOCKS))
    {
      যদি ((d->m_dict_আকার) && (!(d->m_flags & TDEFL_FORCE_ALL_RAW_BLOCKS)))
      {
        mz_uint8 c = d->m_dict[(cur_pos - 1) & TDEFL_LZ_DICT_আকার_MASK];
        cur_match_len = 0; যখন (cur_match_len < d->m_lookahead_আকার) { যদি (d->m_dict[cur_pos + cur_match_len] != c) বিরতি; cur_match_len++; }
        যদি (cur_match_len < TDEFL_MIN_MATCH_LEN) cur_match_len = 0; অন্যথা cur_match_dist = 1;
      }
    }
    অন্যথা
    {
      tdefl_find_match(d, d->m_lookahead_pos, d->m_dict_আকার, d->m_lookahead_আকার, &cur_match_dist, &cur_match_len);
    }
    যদি (((cur_match_len == TDEFL_MIN_MATCH_LEN) && (cur_match_dist >= 8U*1024U)) || (cur_pos == cur_match_dist) || ((d->m_flags & TDEFL_FILTER_MATCHES) && (cur_match_len <= 5)))
    {
      cur_match_dist = cur_match_len = 0;
    }
    যদি (d->m_saved_match_len)
    {
      যদি (cur_match_len > d->m_saved_match_len)
      {
        tdefl_record_literal(d, (mz_uint8)d->m_saved_lit);
        যদি (cur_match_len >= 128)
        {
          tdefl_record_match(d, cur_match_len, cur_match_dist);
          d->m_saved_match_len = 0; len_to_move = cur_match_len;
        }
        অন্যথা
        {
          d->m_saved_lit = d->m_dict[cur_pos]; d->m_saved_match_dist = cur_match_dist; d->m_saved_match_len = cur_match_len;
        }
      }
      অন্যথা
      {
        tdefl_record_match(d, d->m_saved_match_len, d->m_saved_match_dist);
        len_to_move = d->m_saved_match_len - 1; d->m_saved_match_len = 0;
      }
    }
    অন্যথা যদি (!cur_match_dist)
      tdefl_record_literal(d, d->m_dict[MZ_MIN(cur_pos, আকার(d->m_dict) - 1)]);
    অন্যথা যদি ((d->m_greedy_parsing) || (d->m_flags & TDEFL_RLE_MATCHES) || (cur_match_len >= 128))
    {
      tdefl_record_match(d, cur_match_len, cur_match_dist);
      len_to_move = cur_match_len;
    }
    অন্যথা
    {
      d->m_saved_lit = d->m_dict[MZ_MIN(cur_pos, আকার(d->m_dict) - 1)]; d->m_saved_match_dist = cur_match_dist; d->m_saved_match_len = cur_match_len;
    }
    // Move the lookahead forward by len_to_move bytes.
    d->m_lookahead_pos += len_to_move;
    MZ_ASSERT(d->m_lookahead_আকার >= len_to_move);
    d->m_lookahead_আকার -= len_to_move;
    d->m_dict_আকার = MZ_MIN(d->m_dict_আকার + len_to_move, TDEFL_LZ_DICT_আকার);
    // Check if it's time to flush the current LZ codes to the internal output buffer.
    যদি ( (d->m_pLZ_code_buf > &d->m_lz_code_buf[TDEFL_LZ_CODE_BUF_আকার - 8]) ||
         ( (d->m_যোগ_lz_bytes > 31*1024) && (((((mz_uint)(d->m_pLZ_code_buf - d->m_lz_code_buf) * 115) >> 7) >= d->m_যোগ_lz_bytes) || (d->m_flags & TDEFL_FORCE_ALL_RAW_BLOCKS))) )
    {
      পূর্ণসংখ্যা n;
      d->m_pSrc = pSrc; d->m_src_buf_বাম = src_buf_বাম;
      যদি ((n = tdefl_flush_block(d, 0)) != 0)
        ফেরত (n < 0) ? MZ_FALSE : MZ_TRUE;
    }
  }

  d->m_pSrc = pSrc; d->m_src_buf_বাম = src_buf_বাম;
  ফেরত MZ_TRUE;
}

স্থির tdefl_status tdefl_flush_output_বাফার(tdefl_compressor *d)
{
  যদি (d->m_p_In_buf_আকার)
  {
    *d->m_p_In_buf_আকার = d->m_pSrc - (ধ্রুবক mz_uint8 *)d->m_pIn_buf;
  }

  যদি (d->m_p_Out_buf_আকার)
  {
    size_t n = MZ_MIN(*d->m_p_Out_buf_আকার - d->m_out_buf_ofs, d->m_output_flush_remaining);
    memcpy((mz_uint8 *)d->m_pOut_buf + d->m_out_buf_ofs, d->m_output_buf + d->m_output_flush_ofs, n);
    d->m_output_flush_ofs += (mz_uint)n;
    d->m_output_flush_remaining -= (mz_uint)n;
    d->m_out_buf_ofs += n;

    *d->m_p_Out_buf_আকার = d->m_out_buf_ofs;
  }

  ফেরত (d->m_finished && !d->m_output_flush_remaining) ? TDEFL_STATUS_DONE : TDEFL_STATUS_OKAY;
}

tdefl_status tdefl_compress(tdefl_compressor *d, ধ্রুবক শূন্য *pIn_buf, size_t *p_In_buf_আকার, শূন্য *pOut_buf, size_t *p_Out_buf_আকার, tdefl_flush flush)
{
  যদি (!d)
  {
    যদি (p_In_buf_আকার) *p_In_buf_আকার = 0;
    যদি (p_Out_buf_আকার) *p_Out_buf_আকার = 0;
    ফেরত TDEFL_STATUS_BAD_PARAM;
  }

  d->m_pIn_buf = pIn_buf; d->m_p_In_buf_আকার = p_In_buf_আকার;
  d->m_pOut_buf = pOut_buf; d->m_p_Out_buf_আকার = p_Out_buf_আকার;
  d->m_pSrc = (ধ্রুবক mz_uint8 *)(pIn_buf); d->m_src_buf_বাম = p_In_buf_আকার ? *p_In_buf_আকার : 0;
  d->m_out_buf_ofs = 0;
  d->m_flush = flush;

  যদি ( ((d->m_pPut_buf_func != ফাঁকা) == ((pOut_buf != ফাঁকা) || (p_Out_buf_আকার != ফাঁকা))) || (d->m_পূর্ব_return_status != TDEFL_STATUS_OKAY) ||
        (d->m_wants_to_finish && (flush != TDEFL_FINISH)) || (p_In_buf_আকার && *p_In_buf_আকার && !pIn_buf) || (p_Out_buf_আকার && *p_Out_buf_আকার && !pOut_buf) )
  {
    যদি (p_In_buf_আকার) *p_In_buf_আকার = 0;
    যদি (p_Out_buf_আকার) *p_Out_buf_আকার = 0;
    ফেরত (d->m_পূর্ব_return_status = TDEFL_STATUS_BAD_PARAM);
  }
  d->m_wants_to_finish |= (flush == TDEFL_FINISH);

  যদি ((d->m_output_flush_remaining) || (d->m_finished))
    ফেরত (d->m_পূর্ব_return_status = tdefl_flush_output_বাফার(d));

#যদি MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  যদি (((d->m_flags & TDEFL_MAX_PROBES_MASK) == 1) &&
      ((d->m_flags & TDEFL_GREEDY_PARSING_FLAG) != 0) &&
      ((d->m_flags & (TDEFL_FILTER_MATCHES | TDEFL_FORCE_ALL_RAW_BLOCKS | TDEFL_RLE_MATCHES)) == 0))
  {
    যদি (!tdefl_compress_fast(d))
      ফেরত d->m_পূর্ব_return_status;
  }
  অন্যথা
#endif // #if MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  {
    যদি (!tdefl_compress_normal(d))
      ফেরত d->m_পূর্ব_return_status;
  }

  যদি ((d->m_flags & (TDEFL_WRITE_ZLIB_HEADER | TDEFL_COMPUTE_ADLER32)) && (pIn_buf))
    d->m_adler32 = (mz_uint32)mz_adler32(d->m_adler32, (ধ্রুবক mz_uint8 *)pIn_buf, d->m_pSrc - (ধ্রুবক mz_uint8 *)pIn_buf);

  যদি ((flush) && (!d->m_lookahead_আকার) && (!d->m_src_buf_বাম) && (!d->m_output_flush_remaining))
  {
    যদি (tdefl_flush_block(d, flush) < 0)
      ফেরত d->m_পূর্ব_return_status;
    d->m_finished = (flush == TDEFL_FINISH);
    যদি (flush == TDEFL_FULL_FLUSH) { MZ_CLEAR_ARR(d->m_hash); MZ_CLEAR_ARR(d->m_পরবর্তী); d->m_dict_আকার = 0; }
  }

  ফেরত (d->m_পূর্ব_return_status = tdefl_flush_output_বাফার(d));
}

tdefl_status tdefl_compress_বাফার(tdefl_compressor *d, ধ্রুবক শূন্য *pIn_buf, size_t in_buf_আকার, tdefl_flush flush)
{
  MZ_ASSERT(d->m_pPut_buf_func); ফেরত tdefl_compress(d, pIn_buf, &in_buf_আকার, ফাঁকা, ফাঁকা, flush);
}

tdefl_status tdefl_init(tdefl_compressor *d, tdefl_put_buf_func_ptr pPut_buf_func, শূন্য *pPut_buf_user, পূর্ণসংখ্যা flags)
{
  d->m_pPut_buf_func = pPut_buf_func; d->m_pPut_buf_user = pPut_buf_user;
  d->m_flags = (mz_uint)(flags); d->m_max_probes[0] = 1 + ((flags & 0xFFF) + 2) / 3; d->m_greedy_parsing = (flags & TDEFL_GREEDY_PARSING_FLAG) != 0;
  d->m_max_probes[1] = 1 + (((flags & 0xFFF) >> 2) + 2) / 3;
  যদি (!(flags & TDEFL_NONDETERMINISTIC_PARSING_FLAG)) MZ_CLEAR_ARR(d->m_hash);
  d->m_lookahead_pos = d->m_lookahead_আকার = d->m_dict_আকার = d->m_যোগ_lz_bytes = d->m_lz_code_buf_dict_pos = d->m_bits_in = 0;
  d->m_output_flush_ofs = d->m_output_flush_remaining = d->m_finished = d->m_block_সূচক = d->m_bit_বাফার = d->m_wants_to_finish = 0;
  d->m_pLZ_code_buf = d->m_lz_code_buf + 1; d->m_pLZ_flags = d->m_lz_code_buf; d->m_অঙ্ক_flags_বাম = 8;
  d->m_pOutput_buf = d->m_output_buf; d->m_pOutput_buf_end = d->m_output_buf; d->m_পূর্ব_return_status = TDEFL_STATUS_OKAY;
  d->m_saved_match_dist = d->m_saved_match_len = d->m_saved_lit = 0; d->m_adler32 = 1;
  d->m_pIn_buf = ফাঁকা; d->m_pOut_buf = ফাঁকা;
  d->m_p_In_buf_আকার = ফাঁকা; d->m_p_Out_buf_আকার = ফাঁকা;
  d->m_flush = TDEFL_NO_FLUSH; d->m_pSrc = ফাঁকা; d->m_src_buf_বাম = 0; d->m_out_buf_ofs = 0;
  memset(&d->m_huff_গুনতি[0][0], 0, আকার(d->m_huff_গুনতি[0][0]) * TDEFL_MAX_HUFF_SYMBOLS_0);
  memset(&d->m_huff_গুনতি[1][0], 0, আকার(d->m_huff_গুনতি[1][0]) * TDEFL_MAX_HUFF_SYMBOLS_1);
  ফেরত TDEFL_STATUS_OKAY;
}

#ifndef MINIZ_SDL_NOUNUSED
tdefl_status tdefl_get_পূর্ব_return_status(tdefl_compressor *d)
{
  ফেরত d->m_পূর্ব_return_status;
}

mz_uint32 tdefl_get_adler32(tdefl_compressor *d)
{
  ফেরত d->m_adler32;
}

mz_bool tdefl_compress_mem_to_output(ধ্রুবক শূন্য *pBuf, size_t buf_len, tdefl_put_buf_func_ptr pPut_buf_func, শূন্য *pPut_buf_user, পূর্ণসংখ্যা flags)
{
  tdefl_compressor *pComp; mz_bool succeeded; যদি (((buf_len) && (!pBuf)) || (!pPut_buf_func)) ফেরত MZ_FALSE;
  pComp = (tdefl_compressor*)MZ_MALLOC(আকার(tdefl_compressor)); যদি (!pComp) ফেরত MZ_FALSE;
  succeeded = (tdefl_init(pComp, pPut_buf_func, pPut_buf_user, flags) == TDEFL_STATUS_OKAY);
  succeeded = succeeded && (tdefl_compress_বাফার(pComp, pBuf, buf_len, TDEFL_FINISH) == TDEFL_STATUS_DONE);
  MZ_FREE(pComp); ফেরত succeeded;
}
#endif /* MINIZ_SDL_NOUNUSED */

প্রকারলেখ কাঠামো
{
  size_t m_আকার, m_capacity;
  mz_uint8 *m_pBuf;
  mz_bool m_expandable;
} tdefl_output_বাফার;

স্থির mz_bool tdefl_output_বাফার_putter(ধ্রুবক শূন্য *pBuf, পূর্ণসংখ্যা len, শূন্য *pUser)
{
  tdefl_output_বাফার *p = (tdefl_output_বাফার *)pUser;
  size_t new_আকার = p->m_আকার + len;
  যদি (new_আকার > p->m_capacity)
  {
    size_t new_capacity = p->m_capacity; mz_uint8 *pNew_buf; যদি (!p->m_expandable) ফেরত MZ_FALSE;
    করো { new_capacity = MZ_MAX(128U, new_capacity << 1U); } যখন (new_আকার > new_capacity);
    pNew_buf = (mz_uint8*)MZ_REALLOC(p->m_pBuf, new_capacity); যদি (!pNew_buf) ফেরত MZ_FALSE;
    p->m_pBuf = pNew_buf; p->m_capacity = new_capacity;
  }
  memcpy((mz_uint8*)p->m_pBuf + p->m_আকার, pBuf, len); p->m_আকার = new_আকার;
  ফেরত MZ_TRUE;
}

#ifndef MINIZ_SDL_NOUNUSED
শূন্য *tdefl_compress_mem_to_heap(ধ্রুবক শূন্য *pSrc_buf, size_t src_buf_len, size_t *pOut_len, পূর্ণসংখ্যা flags)
{
  tdefl_output_বাফার out_buf; MZ_CLEAR_OBJ(out_buf);
  যদি (!pOut_len) ফেরত MZ_FALSE; অন্যথা *pOut_len = 0;
  out_buf.m_expandable = MZ_TRUE;
  যদি (!tdefl_compress_mem_to_output(pSrc_buf, src_buf_len, tdefl_output_বাফার_putter, &out_buf, flags)) ফেরত ফাঁকা;
  *pOut_len = out_buf.m_আকার; ফেরত out_buf.m_pBuf;
}

size_t tdefl_compress_mem_to_mem(শূন্য *pOut_buf, size_t out_buf_len, ধ্রুবক শূন্য *pSrc_buf, size_t src_buf_len, পূর্ণসংখ্যা flags)
{
  tdefl_output_বাফার out_buf; MZ_CLEAR_OBJ(out_buf);
  যদি (!pOut_buf) ফেরত 0;
  out_buf.m_pBuf = (mz_uint8*)pOut_buf; out_buf.m_capacity = out_buf_len;
  যদি (!tdefl_compress_mem_to_output(pSrc_buf, src_buf_len, tdefl_output_বাফার_putter, &out_buf, flags)) ফেরত 0;
  ফেরত out_buf.m_আকার;
}
#endif /* MINIZ_SDL_NOUNUSED */

#ifndef MINIZ_NO_ZLIB_APIS
স্থির ধ্রুবক mz_uint s_tdefl_অঙ্ক_probes[11] = { 0, 1, 6, 32,  16, 32, 128, 256,  512, 768, 1500 };

// level may actually range from [0,10] (10 is a "hidden" max level, where we want a bit more compression and it's fine if throughput to fall off a cliff on some files).
mz_uint tdefl_create_comp_flags_from_zip_params(পূর্ণসংখ্যা level, পূর্ণসংখ্যা window_bits, পূর্ণসংখ্যা strategy)
{
  mz_uint comp_flags = s_tdefl_অঙ্ক_probes[(level >= 0) ? MZ_MIN(10, level) : MZ_DEFAULT_LEVEL] | ((level <= 3) ? TDEFL_GREEDY_PARSING_FLAG : 0);
  যদি (window_bits > 0) comp_flags |= TDEFL_WRITE_ZLIB_HEADER;

  যদি (!level) comp_flags |= TDEFL_FORCE_ALL_RAW_BLOCKS;
  অন্যথা যদি (strategy == MZ_FILTERED) comp_flags |= TDEFL_FILTER_MATCHES;
  অন্যথা যদি (strategy == MZ_HUFFMAN_ONLY) comp_flags &= ~TDEFL_MAX_PROBES_MASK;
  অন্যথা যদি (strategy == MZ_FIXED) comp_flags |= TDEFL_FORCE_ALL_STATIC_BLOCKS;
  অন্যথা যদি (strategy == MZ_RLE) comp_flags |= TDEFL_RLE_MATCHES;

  ফেরত comp_flags;
}
#endif //MINIZ_NO_ZLIB_APIS

#ifdef _MSC_VER
#pragma warning (ঠেলো)
#pragma warning (disable:4204) // nonstandard extension used : non-constant aggregate initializer (also supported by GNU C and C99, so no big deal)
#endif

// Simple PNG writer function by Alex Evans, 2011. Released into the public domain: https://gist.github.com/908299, more context at
// http://altdevblogaday.org/2011/04/06/a-smaller-jpg-encoder/.
// This is actually a modification of Alex's original code so PNG files generated by this function pass pngcheck.
MINIZ_STATIC শূন্য *tdefl_write_image_to_png_file_in_memory_ex(ধ্রুবক শূন্য *pImage, পূর্ণসংখ্যা w, পূর্ণসংখ্যা h, পূর্ণসংখ্যা অঙ্ক_chans, পূর্ণসংখ্যা bpl, size_t *pLen_out, mz_uint level, mz_bool flip, mz_uint8 *plte, পূর্ণসংখ্যা plte_আকার, mz_uint8 *trns, পূর্ণসংখ্যা trns_আকার)
{
  // Using a local copy of this array here in case MINIZ_NO_ZLIB_APIS was defined.
  স্থির ধ্রুবক mz_uint s_tdefl_png_অঙ্ক_probes[11] = { 0, 1, 6, 32,  16, 32, 128, 256,  512, 768, 1500 };
  tdefl_compressor *pComp = (tdefl_compressor *)MZ_MALLOC(আকার(tdefl_compressor)); tdefl_output_বাফার out_buf; পূর্ণসংখ্যা i, y, z = 0; mz_uint32 c; *pLen_out = 0; size_t তথ্য_start, তথ্য_আকার_3;
  যদি (!pComp) ফেরত ফাঁকা;
  MZ_CLEAR_OBJ(out_buf); out_buf.m_expandable = MZ_TRUE;
  out_buf.m_capacity = 57+MZ_MAX(64, (1+w*অঙ্ক_chans)*h);
  যদি (plte_আকার > 0)
    out_buf.m_capacity += 12+plte_আকার;
  যদি (trns_আকার > 0)
    out_buf.m_capacity += 12+trns_আকার;
  যদি (ফাঁকা == (out_buf.m_pBuf = (mz_uint8*)MZ_MALLOC(out_buf.m_capacity))) { MZ_FREE(pComp); ফেরত ফাঁকা; }
  // write header
  {
    স্থির ধ্রুবক mz_uint8 chans[] = {0x00, 0x00, 0x04, 0x02, 0x06};

    mz_uint8 pnghdr[33]={ 0x89,0x50,0x4e,0x47,0x0d,0x0a,0x1a,0x0a,
                          0x00,0x00,0x00,0x0d,0x49,0x48,0x44,0x52,
                          0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                          0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

    pnghdr[18] = (mz_uint8)(w>>8);
    pnghdr[19] = (mz_uint8)(w>>0);

    pnghdr[22] = (mz_uint8)(h>>8);
    pnghdr[23] = (mz_uint8)(h>>0);

    যদি (অঙ্ক_chans == 1 && plte_আকার > 0)
      pnghdr[25] = 3;
    অন্যথা
      pnghdr[25] = (chans[অঙ্ক_chans]);

    c = (mz_uint32)mz_crc32(MZ_CRC32_INIT,pnghdr+12,17);
    জন্য (i=0; i<4; ++i, c<<=8) ((mz_uint8*)(pnghdr+29))[i] = (mz_uint8)(c>>24);
    যদি (!tdefl_output_বাফার_putter(pnghdr, আকার(pnghdr), &out_buf)) { *pLen_out = 0; MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); ফেরত ফাঁকা; }
  }
  // write PLTE chunk
  যদি (plte_আকার > 0)
  {
    mz_uint8 hdr[8]={0x00,0x00,0x00,0x00,0x50,0x4c,0x54,0x45};

    hdr[0] = (mz_uint8)(plte_আকার>>24);
    hdr[1] = (mz_uint8)(plte_আকার>>16);
    hdr[2] = (mz_uint8)(plte_আকার>> 8);
    hdr[3] = (mz_uint8)(plte_আকার>> 0);
    যদি (!tdefl_output_বাফার_putter(hdr, আকার(hdr), &out_buf)) { *pLen_out = 0; MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); ফেরত ফাঁকা; }
    তথ্য_start = out_buf.m_আকার;
    যদি (!tdefl_output_বাফার_putter(plte, plte_আকার, &out_buf)) { *pLen_out = 0; MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); ফেরত ফাঁকা; }
    যদি (!tdefl_output_বাফার_putter("\0\0\0\0", 4, &out_buf)) { *pLen_out = 0; MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); ফেরত ফাঁকা; }
    c = (mz_uint32)mz_crc32(MZ_CRC32_INIT,out_buf.m_pBuf+তথ্য_start-4, plte_আকার+4);
    জন্য (i=0; i<4; ++i, c<<=8) (out_buf.m_pBuf+out_buf.m_আকার-4)[i] = (mz_uint8)(c >> 24);
  }
  // write tRNS chunk
  যদি (trns_আকার > 0)
  {
    mz_uint8 hdr[8]={0x00,0x00,0x00,0x00,0x74,0x52,0x4E,0x53};

    hdr[0] = (mz_uint8)(trns_আকার>>24);
    hdr[1] = (mz_uint8)(trns_আকার>>16);
    hdr[2] = (mz_uint8)(trns_আকার>> 8);
    hdr[3] = (mz_uint8)(trns_আকার>> 0);
    যদি (!tdefl_output_বাফার_putter(hdr, আকার(hdr), &out_buf)) { *pLen_out = 0; MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); ফেরত ফাঁকা; }
    তথ্য_start = out_buf.m_আকার;
    যদি (!tdefl_output_বাফার_putter(trns, trns_আকার, &out_buf)) { *pLen_out = 0; MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); ফেরত ফাঁকা; }
    যদি (!tdefl_output_বাফার_putter("\0\0\0\0", 4, &out_buf)) { *pLen_out = 0; MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); ফেরত ফাঁকা; }
    c = (mz_uint32)mz_crc32(MZ_CRC32_INIT,out_buf.m_pBuf+তথ্য_start-4, trns_আকার+4);
    জন্য (i=0; i<4; ++i, c<<=8) (out_buf.m_pBuf+out_buf.m_আকার-4)[i] = (mz_uint8)(c >> 24);
  }
  // write IDAT chunk
  যদি (!tdefl_output_বাফার_putter("\0\0\0\0\x49\x44\x41\x54", 8, &out_buf)) { *pLen_out = 0; MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); ফেরত ফাঁকা; }
  তথ্য_start = out_buf.m_আকার;
  // compress image data
  tdefl_init(pComp, tdefl_output_বাফার_putter, &out_buf, s_tdefl_png_অঙ্ক_probes[MZ_MIN(10, level)] | TDEFL_WRITE_ZLIB_HEADER);
  জন্য (y = 0; y < h; ++y) { tdefl_compress_বাফার(pComp, &z, 1, TDEFL_NO_FLUSH); tdefl_compress_বাফার(pComp, (mz_uint8*)pImage + (flip ? (h - 1 - y) : y) * bpl, w * অঙ্ক_chans, TDEFL_NO_FLUSH); }
  যদি (tdefl_compress_বাফার(pComp, ফাঁকা, 0, TDEFL_FINISH) != TDEFL_STATUS_DONE) { MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); ফেরত ফাঁকা; }
  // write IDAT size
  তথ্য_আকার_3 = out_buf.m_আকার-তথ্য_start;
  (out_buf.m_pBuf+তথ্য_start-8)[0] = (mz_uint8)(তথ্য_আকার_3>>24);
  (out_buf.m_pBuf+তথ্য_start-8)[1] = (mz_uint8)(তথ্য_আকার_3>>16);
  (out_buf.m_pBuf+তথ্য_start-8)[2] = (mz_uint8)(তথ্য_আকার_3>> 8);
  (out_buf.m_pBuf+তথ্য_start-8)[3] = (mz_uint8)(তথ্য_আকার_3>> 0);
  // write footer (IDAT CRC-32, followed by IEND chunk)
  যদি (!tdefl_output_বাফার_putter("\0\0\0\0\0\0\0\0\x49\x45\x4e\x44\xae\x42\x60\x82", 16, &out_buf)) { *pLen_out = 0; MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); ফেরত ফাঁকা; }
  c = (mz_uint32)mz_crc32(MZ_CRC32_INIT,out_buf.m_pBuf+তথ্য_start-4, তথ্য_আকার_3+4);
  জন্য (i=0; i<4; ++i, c<<=8) (out_buf.m_pBuf+out_buf.m_আকার-16)[i] = (mz_uint8)(c >> 24);
  // compute final size of file, grab compressed data buffer and return
  *pLen_out = out_buf.m_আকার;
  MZ_FREE(pComp);
  ফেরত out_buf.m_pBuf;
}
#ifndef MINIZ_SDL_NOUNUSED
MINIZ_STATIC শূন্য *tdefl_write_image_to_png_file_in_memory(ধ্রুবক শূন্য *pImage, পূর্ণসংখ্যা w, পূর্ণসংখ্যা h, পূর্ণসংখ্যা অঙ্ক_chans, পূর্ণসংখ্যা bpl, size_t *pLen_out)
{
  // Level 6 corresponds to TDEFL_DEFAULT_MAX_PROBES or MZ_DEFAULT_LEVEL (but we can't depend on MZ_DEFAULT_LEVEL being available in case the zlib API's where #defined out)
  ফেরত tdefl_write_image_to_png_file_in_memory_ex(pImage, w, h, অঙ্ক_chans, bpl, pLen_out, 6, MZ_FALSE, ফাঁকা, 0, ফাঁকা, 0);
}
#endif

#ifdef _MSC_VER
#pragma warning (বের_করো)
#endif
#endif /*#ifndef MINIZ_NO_DEFLATE_APIS*/

// ------------------- .ZIP archive reading

#ifndef MINIZ_NO_ARCHIVE_APIS

#ifdef MINIZ_NO_STDIO
  #define MZ_FILE শূন্য *
#অন্যথা
  #অন্তর্ভাব <stdio.h>
  #অন্তর্ভাব <sys/stat.h>

  #যদি defined(_MSC_VER) || defined(__MINGW64__)
    স্থির FILE *mz_fopen(ধ্রুবক অক্ষর *pFilename, ধ্রুবক অক্ষর *pMode)
    {
      FILE* pFile = ফাঁকা;
      fopen_s(&pFile, pFilename, pMode);
      ফেরত pFile;
    }
    স্থির FILE *mz_freopen(ধ্রুবক অক্ষর *pPath, ধ্রুবক অক্ষর *pMode, FILE *pStream)
    {
      FILE* pFile = ফাঁকা;
      যদি (freopen_s(&pFile, pPath, pMode, pStream))
        ফেরত ফাঁকা;
      ফেরত pFile;
    }
    #ifndef MINIZ_NO_TIME
      #অন্তর্ভাব <sys/utime.h>
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
  #নতুবা_যদি defined(__MINGW32__)
    #ifndef MINIZ_NO_TIME
      #অন্তর্ভাব <sys/utime.h>
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
  #নতুবা_যদি defined(__TINYC__)
    #ifndef MINIZ_NO_TIME
      #অন্তর্ভাব <sys/utime.h>
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
  #নতুবা_যদি defined(__GNUC__) && _LARGEFILE64_SOURCE
    #ifndef MINIZ_NO_TIME
      #অন্তর্ভাব <utime.h>
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
  #অন্যথা
    #ifndef MINIZ_NO_TIME
      #অন্তর্ভাব <utime.h>
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
গণনা
{
  // ZIP archive identifiers and record sizes
  MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIG = 0x06054b50, MZ_ZIP_CENTRAL_DIR_HEADER_SIG = 0x02014b50, MZ_ZIP_LOCAL_DIR_HEADER_SIG = 0x04034b50,
  MZ_ZIP_LOCAL_DIR_HEADER_আকার = 30, MZ_ZIP_CENTRAL_DIR_HEADER_আকার = 46, MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_আকার = 22,
  // Central directory header record offsets
  MZ_ZIP_CDH_SIG_OFS = 0, MZ_ZIP_CDH_VERSION_MADE_BY_OFS = 4, MZ_ZIP_CDH_VERSION_NEEDED_OFS = 6, MZ_ZIP_CDH_BIT_FLAG_OFS = 8,
  MZ_ZIP_CDH_METHOD_OFS = 10, MZ_ZIP_CDH_FILE_TIME_OFS = 12, MZ_ZIP_CDH_FILE_DATE_OFS = 14, MZ_ZIP_CDH_CRC32_OFS = 16,
  MZ_ZIP_CDH_COMPRESSED_আকার_OFS = 20, MZ_ZIP_CDH_DECOMPRESSED_আকার_OFS = 24, MZ_ZIP_CDH_FILENAME_LEN_OFS = 28, MZ_ZIP_CDH_EXTRA_LEN_OFS = 30,
  MZ_ZIP_CDH_COMMENT_LEN_OFS = 32, MZ_ZIP_CDH_DISK_START_OFS = 34, MZ_ZIP_CDH_INTERNAL_ATTR_OFS = 36, MZ_ZIP_CDH_EXTERNAL_ATTR_OFS = 38, MZ_ZIP_CDH_LOCAL_HEADER_OFS = 42,
  // Local directory header offsets
  MZ_ZIP_LDH_SIG_OFS = 0, MZ_ZIP_LDH_VERSION_NEEDED_OFS = 4, MZ_ZIP_LDH_BIT_FLAG_OFS = 6, MZ_ZIP_LDH_METHOD_OFS = 8, MZ_ZIP_LDH_FILE_TIME_OFS = 10,
  MZ_ZIP_LDH_FILE_DATE_OFS = 12, MZ_ZIP_LDH_CRC32_OFS = 14, MZ_ZIP_LDH_COMPRESSED_আকার_OFS = 18, MZ_ZIP_LDH_DECOMPRESSED_আকার_OFS = 22,
  MZ_ZIP_LDH_FILENAME_LEN_OFS = 26, MZ_ZIP_LDH_EXTRA_LEN_OFS = 28,
  // End of central directory offsets
  MZ_ZIP_ECDH_SIG_OFS = 0, MZ_ZIP_ECDH_অঙ্ক_THIS_DISK_OFS = 4, MZ_ZIP_ECDH_অঙ্ক_DISK_CDIR_OFS = 6, MZ_ZIP_ECDH_CDIR_অঙ্ক_ENTRIES_ON_DISK_OFS = 8,
  MZ_ZIP_ECDH_CDIR_যোগ_ENTRIES_OFS = 10, MZ_ZIP_ECDH_CDIR_আকার_OFS = 12, MZ_ZIP_ECDH_CDIR_OFS_OFS = 16, MZ_ZIP_ECDH_COMMENT_আকার_OFS = 20,
};

প্রকারলেখ কাঠামো
{
  শূন্য *m_p;
  size_t m_আকার, m_capacity;
  mz_uint m_element_আকার;
} mz_zip_array;

কাঠামো mz_zip_internal_state_tag
{
  mz_zip_array m_central_dir;
  mz_zip_array m_central_dir_offsets;
  mz_zip_array m_sorted_central_dir_offsets;
  MZ_FILE *m_pFile;
  শূন্য *m_pMem;
  size_t m_mem_আকার;
  size_t m_mem_capacity;
};

#define MZ_ZIP_ARRAY_SET_ELEMENT_আকার(array_ptr, element_আকার) (array_ptr)->m_element_আকার = element_আকার
#define MZ_ZIP_ARRAY_ELEMENT(array_ptr, element_type, সূচক) ((element_type *)((array_ptr)->m_p))[সূচক]

স্থির MZ_FORCEINLINE শূন্য mz_zip_array_clear(mz_zip_archive *pZip, mz_zip_array *pArray)
{
  pZip->m_pFree(pZip->m_pAlloc_opaque, pArray->m_p);
  memset(pArray, 0, আকার(mz_zip_array));
}

স্থির mz_bool mz_zip_array_ensure_capacity(mz_zip_archive *pZip, mz_zip_array *pArray, size_t min_new_capacity, mz_uint growing)
{
  শূন্য *pNew_p; size_t new_capacity = min_new_capacity; MZ_ASSERT(pArray->m_element_আকার); যদি (pArray->m_capacity >= min_new_capacity) ফেরত MZ_TRUE;
  যদি (growing) { new_capacity = MZ_MAX(1, pArray->m_capacity); যখন (new_capacity < min_new_capacity) new_capacity *= 2; }
  যদি (ফাঁকা == (pNew_p = pZip->m_pRealloc(pZip->m_pAlloc_opaque, pArray->m_p, pArray->m_element_আকার, new_capacity))) ফেরত MZ_FALSE;
  pArray->m_p = pNew_p; pArray->m_capacity = new_capacity;
  ফেরত MZ_TRUE;
}

স্থির MZ_FORCEINLINE mz_bool mz_zip_array_reserve(mz_zip_archive *pZip, mz_zip_array *pArray, size_t new_capacity, mz_uint growing)
{
  যদি (new_capacity > pArray->m_capacity) { যদি (!mz_zip_array_ensure_capacity(pZip, pArray, new_capacity, growing)) ফেরত MZ_FALSE; }
  ফেরত MZ_TRUE;
}

স্থির MZ_FORCEINLINE mz_bool mz_zip_array_resize(mz_zip_archive *pZip, mz_zip_array *pArray, size_t new_আকার, mz_uint growing)
{
  যদি (new_আকার > pArray->m_capacity) { যদি (!mz_zip_array_ensure_capacity(pZip, pArray, new_আকার, growing)) ফেরত MZ_FALSE; }
  pArray->m_আকার = new_আকার;
  ফেরত MZ_TRUE;
}

স্থির MZ_FORCEINLINE mz_bool mz_zip_array_ensure_room(mz_zip_archive *pZip, mz_zip_array *pArray, size_t n)
{
  ফেরত mz_zip_array_reserve(pZip, pArray, pArray->m_আকার + n, MZ_TRUE);
}

স্থির MZ_FORCEINLINE mz_bool mz_zip_array_ঠেলো_back(mz_zip_archive *pZip, mz_zip_array *pArray, ধ্রুবক শূন্য *pElements, size_t n)
{
  size_t orig_আকার = pArray->m_আকার; যদি (!mz_zip_array_resize(pZip, pArray, orig_আকার + n, MZ_TRUE)) ফেরত MZ_FALSE;
  memcpy((mz_uint8*)pArray->m_p + orig_আকার * pArray->m_element_আকার, pElements, n * pArray->m_element_আকার);
  ফেরত MZ_TRUE;
}

#ifndef MINIZ_NO_TIME
স্থির time_t mz_zip_dos_to_time_t(পূর্ণসংখ্যা dos_time, পূর্ণসংখ্যা dos_date)
{
  কাঠামো tm tm;
  memset(&tm, 0, আকার(tm)); tm.tm_isdst = -1;
  tm.tm_year = ((dos_date >> 9) & 127) + 1980 - 1900; tm.tm_mon = ((dos_date >> 5) & 15) - 1; tm.tm_mday = dos_date & 31;
  tm.tm_hour = (dos_time >> 11) & 31; tm.tm_min = (dos_time >> 5) & 63; tm.tm_sec = (dos_time << 1) & 62;
  ফেরত mktime(&tm);
}

স্থির শূন্য mz_zip_time_to_dos_time(time_t time, mz_uint16 *pDOS_time, mz_uint16 *pDOS_date)
{
#ifdef _MSC_VER
  কাঠামো tm tm_struct;
  কাঠামো tm *tm = &tm_struct;
  errno_t err = localtime_s(tm, &time);
  যদি (err)
  {
    *pDOS_date = 0; *pDOS_time = 0;
    ফেরত;
  }
#অন্যথা
  কাঠামো tm *tm = localtime(&time);
#endif
  *pDOS_time = (mz_uint16)(((tm->tm_hour) << 11) + ((tm->tm_min) << 5) + ((tm->tm_sec) >> 1));
  *pDOS_date = (mz_uint16)(((tm->tm_year + 1900 - 1980) << 9) + ((tm->tm_mon + 1) << 5) + tm->tm_mday);
}
#endif

#ifndef MINIZ_NO_STDIO
স্থির mz_bool mz_zip_get_file_modified_time(ধ্রুবক অক্ষর *pFilename, mz_uint16 *pDOS_time, mz_uint16 *pDOS_date)
{
#ifdef MINIZ_NO_TIME
  (শূন্য)pFilename; *pDOS_date = *pDOS_time = 0;
#অন্যথা
  কাঠামো MZ_FILE_STAT_STRUCT file_stat;
  // On Linux with x86 glibc, this call will fail on large files (>= 0x80000000 bytes) unless you compiled with _LARGEFILE64_SOURCE. Argh.
  যদি (MZ_FILE_STAT(pFilename, &file_stat) != 0)
    ফেরত MZ_FALSE;
  mz_zip_time_to_dos_time(file_stat.st_mtime, pDOS_time, pDOS_date);
#endif // #ifdef MINIZ_NO_TIME
  ফেরত MZ_TRUE;
}

#ifndef MINIZ_NO_TIME
স্থির mz_bool mz_zip_set_file_times(ধ্রুবক অক্ষর *pFilename, time_t access_time, time_t modified_time)
{
  কাঠামো utimbuf t; t.actime = access_time; t.modtime = modified_time;
  ফেরত !utime(pFilename, &t);
}
#endif // #ifndef MINIZ_NO_TIME
#endif // #ifndef MINIZ_NO_STDIO

স্থির mz_bool mz_zip_reader_init_internal(mz_zip_archive *pZip, mz_uint32 flags)
{
  (শূন্য)flags;
  যদি ((!pZip) || (pZip->m_pState) || (pZip->m_zip_mode != MZ_ZIP_MODE_INVALID))
    ফেরত MZ_FALSE;

  যদি (!pZip->m_pAlloc) pZip->m_pAlloc = def_alloc_func;
  যদি (!pZip->m_pFree) pZip->m_pFree = def_free_func;
  যদি (!pZip->m_pRealloc) pZip->m_pRealloc = def_realloc_func;

  pZip->m_zip_mode = MZ_ZIP_MODE_READING;
  pZip->m_archive_আকার = 0;
  pZip->m_central_directory_file_ofs = 0;
  pZip->m_যোগ_files = 0;

  যদি (ফাঁকা == (pZip->m_pState = (mz_zip_internal_state *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, আকার(mz_zip_internal_state))))
    ফেরত MZ_FALSE;
  memset(pZip->m_pState, 0, আকার(mz_zip_internal_state));
  MZ_ZIP_ARRAY_SET_ELEMENT_আকার(&pZip->m_pState->m_central_dir, আকার(mz_uint8));
  MZ_ZIP_ARRAY_SET_ELEMENT_আকার(&pZip->m_pState->m_central_dir_offsets, আকার(mz_uint32));
  MZ_ZIP_ARRAY_SET_ELEMENT_আকার(&pZip->m_pState->m_sorted_central_dir_offsets, আকার(mz_uint32));
  ফেরত MZ_TRUE;
}

স্থির MZ_FORCEINLINE mz_bool mz_zip_reader_filename_less(ধ্রুবক mz_zip_array *pCentral_dir_array, ধ্রুবক mz_zip_array *pCentral_dir_offsets, mz_uint l_সূচক, mz_uint r_সূচক)
{
  ধ্রুবক mz_uint8 *pL = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, l_সূচক)), *pE;
  ধ্রুবক mz_uint8 *pR = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, r_সূচক));
  mz_uint l_len = MZ_READ_LE16(pL + MZ_ZIP_CDH_FILENAME_LEN_OFS), r_len = MZ_READ_LE16(pR + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  mz_uint8 l = 0, r = 0;
  pL += MZ_ZIP_CENTRAL_DIR_HEADER_আকার; pR += MZ_ZIP_CENTRAL_DIR_HEADER_আকার;
  pE = pL + MZ_MIN(l_len, r_len);
  যখন (pL < pE)
  {
    যদি ((l = MZ_TOLOWER(*pL)) != (r = MZ_TOLOWER(*pR)))
      বিরতি;
    pL++; pR++;
  }
  ফেরত (pL == pE) ? (l_len < r_len) : (l < r);
}

#define MZ_SWAP_UINT32(a, b) করো { mz_uint32 t = a; a = b; b = t; } MZ_MACRO_END

// Heap sort of lowercased filenames, used to help accelerate plain central directory searches by mz_zip_reader_locate_file(). (Could also use qsort(), but it could allocate memory.)
স্থির শূন্য mz_zip_reader_sort_central_dir_offsets_by_filename(mz_zip_archive *pZip)
{
  mz_zip_internal_state *pState = pZip->m_pState;
  ধ্রুবক mz_zip_array *pCentral_dir_offsets = &pState->m_central_dir_offsets;
  ধ্রুবক mz_zip_array *pCentral_dir = &pState->m_central_dir;
  mz_uint32 *pIndices = &MZ_ZIP_ARRAY_ELEMENT(&pState->m_sorted_central_dir_offsets, mz_uint32, 0);
  ধ্রুবক পূর্ণসংখ্যা আকার_2 = pZip->m_যোগ_files;
  পূর্ণসংখ্যা start = (আকার_2 - 2) >> 1, end;
  যখন (start >= 0)
  {
    পূর্ণসংখ্যা child, মূল = start;
    জন্য ( ; ; )
    {
      যদি ((child = (মূল << 1) + 1) >= আকার_2)
        বিরতি;
      child += (((child + 1) < আকার_2) && (mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[child], pIndices[child + 1])));
      যদি (!mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[মূল], pIndices[child]))
        বিরতি;
      MZ_SWAP_UINT32(pIndices[মূল], pIndices[child]); মূল = child;
    }
    start--;
  }

  end = আকার_2 - 1;
  যখন (end > 0)
  {
    পূর্ণসংখ্যা child, মূল = 0;
    MZ_SWAP_UINT32(pIndices[end], pIndices[0]);
    জন্য ( ; ; )
    {
      যদি ((child = (মূল << 1) + 1) >= end)
        বিরতি;
      child += (((child + 1) < end) && mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[child], pIndices[child + 1]));
      যদি (!mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[মূল], pIndices[child]))
        বিরতি;
      MZ_SWAP_UINT32(pIndices[মূল], pIndices[child]); মূল = child;
    }
    end--;
  }
}

স্থির mz_bool mz_zip_reader_read_central_dir(mz_zip_archive *pZip, mz_uint32 flags)
{
  mz_uint cdir_আকার, অঙ্ক_this_disk, cdir_disk_সূচক;
  mz_uint64 cdir_ofs;
  mz_int64 cur_file_ofs;
  ধ্রুবক mz_uint8 *p;
  mz_uint32 buf_u32[4096 / আকার(mz_uint32)]; mz_uint8 *pBuf = (mz_uint8 *)buf_u32;
  mz_bool sort_central_dir = ((flags & MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY) == 0);
  // Basic sanity checks - reject files which are too small, and check the first 4 bytes of the file to make sure a local header is there.
  যদি (pZip->m_archive_আকার < MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_আকার)
    ফেরত MZ_FALSE;
  // Find the end of central directory record by scanning the file from the end towards the beginning.
  cur_file_ofs = MZ_MAX((mz_int64)pZip->m_archive_আকার - (mz_int64)আকার(buf_u32), 0);
  জন্য ( ; ; )
  {
    পূর্ণসংখ্যা i, n = (পূর্ণসংখ্যা)MZ_MIN(আকার(buf_u32), pZip->m_archive_আকার - cur_file_ofs);
    যদি (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, n) != (mz_uint)n)
      ফেরত MZ_FALSE;
    জন্য (i = n - 4; i >= 0; --i)
      যদি (MZ_READ_LE32(pBuf + i) == MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIG)
        বিরতি;
    যদি (i >= 0)
    {
      cur_file_ofs += i;
      বিরতি;
    }
    যদি ((!cur_file_ofs) || ((pZip->m_archive_আকার - cur_file_ofs) >= (0xFFFF + MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_আকার)))
      ফেরত MZ_FALSE;
    cur_file_ofs = MZ_MAX(cur_file_ofs - (আকার(buf_u32) - 3), 0);
  }
  // Read and verify the end of central directory record.
  যদি (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_আকার) != MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_আকার)
    ফেরত MZ_FALSE;
  যদি ((MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_SIG_OFS) != MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIG) ||
      ((pZip->m_যোগ_files = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_CDIR_যোগ_ENTRIES_OFS)) != MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_CDIR_অঙ্ক_ENTRIES_ON_DISK_OFS)))
    ফেরত MZ_FALSE;

  অঙ্ক_this_disk = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_অঙ্ক_THIS_DISK_OFS);
  cdir_disk_সূচক = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_অঙ্ক_DISK_CDIR_OFS);
  যদি (((অঙ্ক_this_disk | cdir_disk_সূচক) != 0) && ((অঙ্ক_this_disk != 1) || (cdir_disk_সূচক != 1)))
    ফেরত MZ_FALSE;

  যদি ((cdir_আকার = MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_CDIR_আকার_OFS)) < pZip->m_যোগ_files * MZ_ZIP_CENTRAL_DIR_HEADER_আকার)
    ফেরত MZ_FALSE;

  cdir_ofs = MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_CDIR_OFS_OFS);
  যদি ((cdir_ofs + (mz_uint64)cdir_আকার) > pZip->m_archive_আকার)
    ফেরত MZ_FALSE;

  pZip->m_central_directory_file_ofs = cdir_ofs;

  যদি (pZip->m_যোগ_files)
  {
     mz_uint i, n;

    // Read the entire central directory into a heap block, and allocate another heap block to hold the unsorted central dir file record offsets, and another to hold the sorted indices.
    যদি ((!mz_zip_array_resize(pZip, &pZip->m_pState->m_central_dir, cdir_আকার, MZ_FALSE)) ||
        (!mz_zip_array_resize(pZip, &pZip->m_pState->m_central_dir_offsets, pZip->m_যোগ_files, MZ_FALSE)))
      ফেরত MZ_FALSE;

    যদি (sort_central_dir)
    {
      যদি (!mz_zip_array_resize(pZip, &pZip->m_pState->m_sorted_central_dir_offsets, pZip->m_যোগ_files, MZ_FALSE))
        ফেরত MZ_FALSE;
    }

    যদি (pZip->m_pRead(pZip->m_pIO_opaque, cdir_ofs, pZip->m_pState->m_central_dir.m_p, cdir_আকার) != cdir_আকার)
      ফেরত MZ_FALSE;

    // Now create an index into the central directory file records, do some basic sanity checking on each record, and check for zip64 entries (which are not yet supported).
    p = (ধ্রুবক mz_uint8 *)pZip->m_pState->m_central_dir.m_p;
    জন্য (n = cdir_আকার, i = 0; i < pZip->m_যোগ_files; ++i)
    {
      mz_uint যোগ_header_আকার, comp_আকার, decomp_আকার, disk_সূচক;
      যদি ((n < MZ_ZIP_CENTRAL_DIR_HEADER_আকার) || (MZ_READ_LE32(p) != MZ_ZIP_CENTRAL_DIR_HEADER_SIG))
        ফেরত MZ_FALSE;
      MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, i) = (mz_uint32)(p - (ধ্রুবক mz_uint8 *)pZip->m_pState->m_central_dir.m_p);
      যদি (sort_central_dir)
        MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_sorted_central_dir_offsets, mz_uint32, i) = i;
      comp_আকার = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_আকার_OFS);
      decomp_আকার = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_আকার_OFS);
      যদি (((!MZ_READ_LE32(p + MZ_ZIP_CDH_METHOD_OFS)) && (decomp_আকার != comp_আকার)) || (decomp_আকার && !comp_আকার) || (decomp_আকার == 0xFFFFFFFF) || (comp_আকার == 0xFFFFFFFF))
        ফেরত MZ_FALSE;
      disk_সূচক = MZ_READ_LE16(p + MZ_ZIP_CDH_DISK_START_OFS);
      যদি ((disk_সূচক != অঙ্ক_this_disk) && (disk_সূচক != 1))
        ফেরত MZ_FALSE;
      যদি (((mz_uint64)MZ_READ_LE32(p + MZ_ZIP_CDH_LOCAL_HEADER_OFS) + MZ_ZIP_LOCAL_DIR_HEADER_আকার + comp_আকার) > pZip->m_archive_আকার)
        ফেরত MZ_FALSE;
      যদি ((যোগ_header_আকার = MZ_ZIP_CENTRAL_DIR_HEADER_আকার + MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_EXTRA_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_COMMENT_LEN_OFS)) > n)
        ফেরত MZ_FALSE;
      n -= যোগ_header_আকার; p += যোগ_header_আকার;
    }
  }

  যদি (sort_central_dir)
    mz_zip_reader_sort_central_dir_offsets_by_filename(pZip);

  ফেরত MZ_TRUE;
}

mz_bool mz_zip_reader_init(mz_zip_archive *pZip, mz_uint64 আকার_2, mz_uint32 flags)
{
  যদি ((!pZip) || (!pZip->m_pRead))
    ফেরত MZ_FALSE;
  যদি (!mz_zip_reader_init_internal(pZip, flags))
    ফেরত MZ_FALSE;
  pZip->m_archive_আকার = আকার_2;
  যদি (!mz_zip_reader_read_central_dir(pZip, flags))
  {
    mz_zip_reader_end(pZip);
    ফেরত MZ_FALSE;
  }
  ফেরত MZ_TRUE;
}

স্থির size_t mz_zip_mem_read_func(শূন্য *pOpaque, mz_uint64 file_ofs, শূন্য *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  size_t s = (file_ofs >= pZip->m_archive_আকার) ? 0 : (size_t)MZ_MIN(pZip->m_archive_আকার - file_ofs, n);
  memcpy(pBuf, (ধ্রুবক mz_uint8 *)pZip->m_pState->m_pMem + file_ofs, s);
  ফেরত s;
}

mz_bool mz_zip_reader_init_mem(mz_zip_archive *pZip, ধ্রুবক শূন্য *pMem, size_t আকার_2, mz_uint32 flags)
{
  যদি (!mz_zip_reader_init_internal(pZip, flags))
    ফেরত MZ_FALSE;
  pZip->m_archive_আকার = আকার_2;
  pZip->m_pRead = mz_zip_mem_read_func;
  pZip->m_pIO_opaque = pZip;
#ifdef __cplusplus
  pZip->m_pState->m_pMem = const_cast<শূন্য *>(pMem);
#অন্যথা
  pZip->m_pState->m_pMem = (শূন্য *)pMem;
#endif
  pZip->m_pState->m_mem_আকার = আকার_2;
  যদি (!mz_zip_reader_read_central_dir(pZip, flags))
  {
    mz_zip_reader_end(pZip);
    ফেরত MZ_FALSE;
  }
  ফেরত MZ_TRUE;
}

#ifndef MINIZ_NO_STDIO
স্থির size_t mz_zip_file_read_func(শূন্য *pOpaque, mz_uint64 file_ofs, শূন্য *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_int64 cur_ofs = MZ_FTELL64(pZip->m_pState->m_pFile);
  যদি (((mz_int64)file_ofs < 0) || (((cur_ofs != (mz_int64)file_ofs)) && (MZ_FSEEK64(pZip->m_pState->m_pFile, (mz_int64)file_ofs, SEEK_SET))))
    ফেরত 0;
  ফেরত MZ_FREAD(pBuf, 1, n, pZip->m_pState->m_pFile);
}

mz_bool mz_zip_reader_init_file(mz_zip_archive *pZip, ধ্রুবক অক্ষর *pFilename, mz_uint32 flags)
{
  mz_uint64 file_আকার;
  MZ_FILE *pFile = MZ_FOPEN(pFilename, "rb");
  যদি (!pFile)
    ফেরত MZ_FALSE;
  যদি (MZ_FSEEK64(pFile, 0, SEEK_END))
  {
    MZ_FCLOSE(pFile);
    ফেরত MZ_FALSE;
  }
  file_আকার = MZ_FTELL64(pFile);
  যদি (!mz_zip_reader_init_internal(pZip, flags))
  {
    MZ_FCLOSE(pFile);
    ফেরত MZ_FALSE;
  }
  pZip->m_pRead = mz_zip_file_read_func;
  pZip->m_pIO_opaque = pZip;
  pZip->m_pState->m_pFile = pFile;
  pZip->m_archive_আকার = file_আকার;
  যদি (!mz_zip_reader_read_central_dir(pZip, flags))
  {
    mz_zip_reader_end(pZip);
    ফেরত MZ_FALSE;
  }
  ফেরত MZ_TRUE;
}
#endif // #ifndef MINIZ_NO_STDIO

mz_uint mz_zip_reader_get_অঙ্ক_files(mz_zip_archive *pZip)
{
  ফেরত pZip ? pZip->m_যোগ_files : 0;
}

স্থির MZ_FORCEINLINE ধ্রুবক mz_uint8 *mz_zip_reader_get_cdh(mz_zip_archive *pZip, mz_uint file_সূচক)
{
  যদি ((!pZip) || (!pZip->m_pState) || (file_সূচক >= pZip->m_যোগ_files) || (pZip->m_zip_mode != MZ_ZIP_MODE_READING))
    ফেরত ফাঁকা;
  ফেরত &MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_সূচক));
}

mz_bool mz_zip_reader_is_file_encrypted(mz_zip_archive *pZip, mz_uint file_সূচক)
{
  mz_uint m_bit_flag;
  ধ্রুবক mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_সূচক);
  যদি (!p)
    ফেরত MZ_FALSE;
  m_bit_flag = MZ_READ_LE16(p + MZ_ZIP_CDH_BIT_FLAG_OFS);
  ফেরত (m_bit_flag & 1);
}

mz_bool mz_zip_reader_is_file_a_directory(mz_zip_archive *pZip, mz_uint file_সূচক)
{
  mz_uint filename_len, external_attr;
  ধ্রুবক mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_সূচক);
  যদি (!p)
    ফেরত MZ_FALSE;

  // First see if the filename ends with a '/' character.
  filename_len = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  যদি (filename_len)
  {
    যদি (*(p + MZ_ZIP_CENTRAL_DIR_HEADER_আকার + filename_len - 1) == '/')
      ফেরত MZ_TRUE;
  }

  // Bugfix: This code was also checking if the internal attribute was non-zero, which wasn't correct.
  // Most/all zip writers (hopefully) set DOS file/directory attributes in the low 16-bits, so check for the DOS directory flag and ignore the source OS ID in the created by field.
  // FIXME: Remove this check? Is it necessary - we already check the filename.
  external_attr = MZ_READ_LE32(p + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS);
  যদি ((external_attr & 0x10) != 0)
    ফেরত MZ_TRUE;

  ফেরত MZ_FALSE;
}

mz_bool mz_zip_reader_file_stat(mz_zip_archive *pZip, mz_uint file_সূচক, mz_zip_archive_file_stat *pStat)
{
  mz_uint n;
  ধ্রুবক mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_সূচক);
  যদি ((!p) || (!pStat))
    ফেরত MZ_FALSE;

  // Unpack the central directory record.
  pStat->m_file_সূচক = file_সূচক;
  pStat->m_central_dir_ofs = MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_সূচক);
  pStat->m_version_made_by = MZ_READ_LE16(p + MZ_ZIP_CDH_VERSION_MADE_BY_OFS);
  pStat->m_version_needed = MZ_READ_LE16(p + MZ_ZIP_CDH_VERSION_NEEDED_OFS);
  pStat->m_bit_flag = MZ_READ_LE16(p + MZ_ZIP_CDH_BIT_FLAG_OFS);
  pStat->m_method = MZ_READ_LE16(p + MZ_ZIP_CDH_METHOD_OFS);
#ifndef MINIZ_NO_TIME
  pStat->m_time = mz_zip_dos_to_time_t(MZ_READ_LE16(p + MZ_ZIP_CDH_FILE_TIME_OFS), MZ_READ_LE16(p + MZ_ZIP_CDH_FILE_DATE_OFS));
#endif
  pStat->m_crc32 = MZ_READ_LE32(p + MZ_ZIP_CDH_CRC32_OFS);
  pStat->m_comp_আকার = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_আকার_OFS);
  pStat->m_uncomp_আকার = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_আকার_OFS);
  pStat->m_internal_attr = MZ_READ_LE16(p + MZ_ZIP_CDH_INTERNAL_ATTR_OFS);
  pStat->m_external_attr = MZ_READ_LE32(p + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS);
  pStat->m_local_header_ofs = MZ_READ_LE32(p + MZ_ZIP_CDH_LOCAL_HEADER_OFS);

  // Copy as much of the filename and comment as possible.
  n = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS); n = MZ_MIN(n, MZ_ZIP_MAX_ARCHIVE_FILENAME_আকার - 1);
  memcpy(pStat->m_filename, p + MZ_ZIP_CENTRAL_DIR_HEADER_আকার, n); pStat->m_filename[n] = '\0';

  n = MZ_READ_LE16(p + MZ_ZIP_CDH_COMMENT_LEN_OFS); n = MZ_MIN(n, MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_আকার - 1);
  pStat->m_comment_আকার = n;
  memcpy(pStat->m_comment, p + MZ_ZIP_CENTRAL_DIR_HEADER_আকার + MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_EXTRA_LEN_OFS), n); pStat->m_comment[n] = '\0';

  ফেরত MZ_TRUE;
}

mz_uint mz_zip_reader_get_filename(mz_zip_archive *pZip, mz_uint file_সূচক, অক্ষর *pFilename, mz_uint filename_buf_আকার)
{
  mz_uint n;
  ধ্রুবক mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_সূচক);
  যদি (!p) { যদি (filename_buf_আকার) pFilename[0] = '\0'; ফেরত 0; }
  n = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  যদি (filename_buf_আকার)
  {
    n = MZ_MIN(n, filename_buf_আকার - 1);
    memcpy(pFilename, p + MZ_ZIP_CENTRAL_DIR_HEADER_আকার, n);
    pFilename[n] = '\0';
  }
  ফেরত n + 1;
}

স্থির MZ_FORCEINLINE mz_bool mz_zip_reader_string_equal(ধ্রুবক অক্ষর *pA, ধ্রুবক অক্ষর *pB, mz_uint len, mz_uint flags)
{
  mz_uint i;
  যদি (flags & MZ_ZIP_FLAG_CASE_SENSITIVE)
    ফেরত 0 == memcmp(pA, pB, len);
  জন্য (i = 0; i < len; ++i)
    যদি (MZ_TOLOWER(pA[i]) != MZ_TOLOWER(pB[i]))
      ফেরত MZ_FALSE;
  ফেরত MZ_TRUE;
}

স্থির MZ_FORCEINLINE পূর্ণসংখ্যা mz_zip_reader_filename_compare(ধ্রুবক mz_zip_array *pCentral_dir_array, ধ্রুবক mz_zip_array *pCentral_dir_offsets, mz_uint l_সূচক, ধ্রুবক অক্ষর *pR, mz_uint r_len)
{
  ধ্রুবক mz_uint8 *pL = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, l_সূচক)), *pE;
  mz_uint l_len = MZ_READ_LE16(pL + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  mz_uint8 l = 0, r = 0;
  pL += MZ_ZIP_CENTRAL_DIR_HEADER_আকার;
  pE = pL + MZ_MIN(l_len, r_len);
  যখন (pL < pE)
  {
    যদি ((l = MZ_TOLOWER(*pL)) != (r = MZ_TOLOWER(*pR)))
      বিরতি;
    pL++; pR++;
  }
  ফেরত (pL == pE) ? (পূর্ণসংখ্যা)(l_len - r_len) : (l - r);
}

স্থির পূর্ণসংখ্যা mz_zip_reader_locate_file_দ্বিমিক_অনুসন্ধান(mz_zip_archive *pZip, ধ্রুবক অক্ষর *pFilename)
{
  mz_zip_internal_state *pState = pZip->m_pState;
  ধ্রুবক mz_zip_array *pCentral_dir_offsets = &pState->m_central_dir_offsets;
  ধ্রুবক mz_zip_array *pCentral_dir = &pState->m_central_dir;
  mz_uint32 *pIndices = &MZ_ZIP_ARRAY_ELEMENT(&pState->m_sorted_central_dir_offsets, mz_uint32, 0);
  ধ্রুবক পূর্ণসংখ্যা আকার_2 = pZip->m_যোগ_files;
  ধ্রুবক mz_uint filename_len = (mz_uint)strlen(pFilename);
  পূর্ণসংখ্যা l = 0, h = আকার_2 - 1;
  যখন (l <= h)
  {
    পূর্ণসংখ্যা m = (l + h) >> 1, file_সূচক = pIndices[m], comp = mz_zip_reader_filename_compare(pCentral_dir, pCentral_dir_offsets, file_সূচক, pFilename, filename_len);
    যদি (!comp)
      ফেরত file_সূচক;
    অন্যথা যদি (comp < 0)
      l = m + 1;
    অন্যথা
      h = m - 1;
  }
  ফেরত -1;
}

পূর্ণসংখ্যা mz_zip_reader_locate_file(mz_zip_archive *pZip, ধ্রুবক অক্ষর *pName, ধ্রুবক অক্ষর *pComment, mz_uint flags)
{
  mz_uint file_সূচক; size_t name_len, comment_len;
  যদি ((!pZip) || (!pZip->m_pState) || (!pName) || (pZip->m_zip_mode != MZ_ZIP_MODE_READING))
    ফেরত -1;
  যদি (((flags & (MZ_ZIP_FLAG_IGNORE_PATH | MZ_ZIP_FLAG_CASE_SENSITIVE)) == 0) && (!pComment) && (pZip->m_pState->m_sorted_central_dir_offsets.m_আকার))
    ফেরত mz_zip_reader_locate_file_দ্বিমিক_অনুসন্ধান(pZip, pName);
  name_len = strlen(pName); যদি (name_len > 0xFFFF) ফেরত -1;
  comment_len = pComment ? strlen(pComment) : 0; যদি (comment_len > 0xFFFF) ফেরত -1;
  জন্য (file_সূচক = 0; file_সূচক < pZip->m_যোগ_files; file_সূচক++)
  {
    ধ্রুবক mz_uint8 *pHeader = &MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_সূচক));
    mz_uint filename_len = MZ_READ_LE16(pHeader + MZ_ZIP_CDH_FILENAME_LEN_OFS);
    ধ্রুবক অক্ষর *pFilename = (ধ্রুবক অক্ষর *)pHeader + MZ_ZIP_CENTRAL_DIR_HEADER_আকার;
    যদি (filename_len < name_len)
      চালু;
    যদি (comment_len)
    {
      mz_uint file_extra_len = MZ_READ_LE16(pHeader + MZ_ZIP_CDH_EXTRA_LEN_OFS), file_comment_len = MZ_READ_LE16(pHeader + MZ_ZIP_CDH_COMMENT_LEN_OFS);
      ধ্রুবক অক্ষর *pFile_comment = pFilename + filename_len + file_extra_len;
      যদি ((file_comment_len != comment_len) || (!mz_zip_reader_string_equal(pComment, pFile_comment, file_comment_len, flags)))
        চালু;
    }
    যদি ((flags & MZ_ZIP_FLAG_IGNORE_PATH) && (filename_len))
    {
      পূর্ণসংখ্যা ofs = filename_len - 1;
      করো
      {
        যদি ((pFilename[ofs] == '/') || (pFilename[ofs] == '\\') || (pFilename[ofs] == ':'))
          বিরতি;
      } যখন (--ofs >= 0);
      ofs++;
      pFilename += ofs; filename_len -= ofs;
    }
    যদি ((filename_len == name_len) && (mz_zip_reader_string_equal(pName, pFilename, filename_len, flags)))
      ফেরত file_সূচক;
  }
  ফেরত -1;
}

mz_bool mz_zip_reader_extract_to_mem_no_alloc(mz_zip_archive *pZip, mz_uint file_সূচক, শূন্য *pBuf, size_t buf_আকার_2, mz_uint flags, শূন্য *pUser_read_buf, size_t user_read_buf_আকার)
{
  পূর্ণসংখ্যা status = TINFL_STATUS_DONE;
  mz_uint64 needed_আকার, cur_file_ofs, comp_remaining, out_buf_ofs = 0, read_buf_আকার, read_buf_ofs = 0, read_buf_avail;
  mz_zip_archive_file_stat file_stat;
  শূন্য *pRead_buf;
  mz_uint32 local_header_u32[(MZ_ZIP_LOCAL_DIR_HEADER_আকার + আকার(mz_uint32) - 1) / আকার(mz_uint32)]; mz_uint8 *pLocal_header = (mz_uint8 *)local_header_u32;
  tinfl_decompressor inflator;

  যদি ((buf_আকার_2) && (!pBuf))
    ফেরত MZ_FALSE;

  যদি (!mz_zip_reader_file_stat(pZip, file_সূচক, &file_stat))
    ফেরত MZ_FALSE;

  // Empty file, or a directory (but not always a directory - I've seen odd zips with directories that have compressed data which inflates to 0 bytes)
  যদি (!file_stat.m_comp_আকার)
    ফেরত MZ_TRUE;

  // Entry is a subdirectory (I've seen old zips with dir entries which have compressed deflate data which inflates to 0 bytes, but these entries claim to uncompress to 512 bytes in the headers).
  // I'm torn how to handle this case - should it fail instead?
  যদি (mz_zip_reader_is_file_a_directory(pZip, file_সূচক))
    ফেরত MZ_TRUE;

  // Encryption and patch files are not supported.
  যদি (file_stat.m_bit_flag & (1 | 32))
    ফেরত MZ_FALSE;

  // This function only supports stored and deflate.
  যদি ((!(flags & MZ_ZIP_FLAG_COMPRESSED_তথ্য)) && (file_stat.m_method != 0) && (file_stat.m_method != MZ_DEFLATED))
    ফেরত MZ_FALSE;

  // Ensure supplied output buffer is large enough.
  needed_আকার = (flags & MZ_ZIP_FLAG_COMPRESSED_তথ্য) ? file_stat.m_comp_আকার : file_stat.m_uncomp_আকার;
  যদি (buf_আকার_2 < needed_আকার)
    ফেরত MZ_FALSE;

  // Read and parse the local directory entry.
  cur_file_ofs = file_stat.m_local_header_ofs;
  যদি (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pLocal_header, MZ_ZIP_LOCAL_DIR_HEADER_আকার) != MZ_ZIP_LOCAL_DIR_HEADER_আকার)
    ফেরত MZ_FALSE;
  যদি (MZ_READ_LE32(pLocal_header) != MZ_ZIP_LOCAL_DIR_HEADER_SIG)
    ফেরত MZ_FALSE;

  cur_file_ofs += MZ_ZIP_LOCAL_DIR_HEADER_আকার + MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  যদি ((cur_file_ofs + file_stat.m_comp_আকার) > pZip->m_archive_আকার)
    ফেরত MZ_FALSE;

  যদি ((flags & MZ_ZIP_FLAG_COMPRESSED_তথ্য) || (!file_stat.m_method))
  {
    // The file is stored or the caller has requested the compressed data.
    যদি (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, (size_t)needed_আকার) != needed_আকার)
      ফেরত MZ_FALSE;
    ফেরত ((flags & MZ_ZIP_FLAG_COMPRESSED_তথ্য) != 0) || (mz_crc32(MZ_CRC32_INIT, (ধ্রুবক mz_uint8 *)pBuf, (size_t)file_stat.m_uncomp_আকার) == file_stat.m_crc32);
  }

  // Decompress the file either directly from memory or from a file input buffer.
  tinfl_init(&inflator);

  যদি (pZip->m_pState->m_pMem)
  {
    // Read directly from the archive in memory.
    pRead_buf = (mz_uint8 *)pZip->m_pState->m_pMem + cur_file_ofs;
    read_buf_আকার = read_buf_avail = file_stat.m_comp_আকার;
    comp_remaining = 0;
  }
  অন্যথা যদি (pUser_read_buf)
  {
    // Use a user provided read buffer.
    যদি (!user_read_buf_আকার)
      ফেরত MZ_FALSE;
    pRead_buf = (mz_uint8 *)pUser_read_buf;
    read_buf_আকার = user_read_buf_আকার;
    read_buf_avail = 0;
    comp_remaining = file_stat.m_comp_আকার;
  }
  অন্যথা
  {
    // Temporarily allocate a read buffer.
    read_buf_আকার = MZ_MIN(file_stat.m_comp_আকার, MZ_ZIP_MAX_IO_BUF_আকার);
#ifdef _MSC_VER
    যদি (((0, আকার(size_t) == আকার(mz_uint32))) && (read_buf_আকার > 0x7FFFFFFF))
#অন্যথা
    যদি (((আকার(size_t) == আকার(mz_uint32))) && (read_buf_আকার > 0x7FFFFFFF))
#endif
      ফেরত MZ_FALSE;
    যদি (ফাঁকা == (pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)read_buf_আকার)))
      ফেরত MZ_FALSE;
    read_buf_avail = 0;
    comp_remaining = file_stat.m_comp_আকার;
  }

  করো
  {
    size_t in_buf_আকার, out_buf_আকার = (size_t)(file_stat.m_uncomp_আকার - out_buf_ofs);
    যদি ((!read_buf_avail) && (!pZip->m_pState->m_pMem))
    {
      read_buf_avail = MZ_MIN(read_buf_আকার, comp_remaining);
      যদি (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
      {
        status = TINFL_STATUS_FAILED;
        বিরতি;
      }
      cur_file_ofs += read_buf_avail;
      comp_remaining -= read_buf_avail;
      read_buf_ofs = 0;
    }
    in_buf_আকার = (size_t)read_buf_avail;
    status = tinfl_decompress(&inflator, (mz_uint8 *)pRead_buf + read_buf_ofs, &in_buf_আকার, (mz_uint8 *)pBuf, (mz_uint8 *)pBuf + out_buf_ofs, &out_buf_আকার, TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF | (comp_remaining ? TINFL_FLAG_HAS_MORE_প্রবেশ : 0));
    read_buf_avail -= in_buf_আকার;
    read_buf_ofs += in_buf_আকার;
    out_buf_ofs += out_buf_আকার;
  } যখন (status == TINFL_STATUS_NEEDS_MORE_প্রবেশ);

  যদি (status == TINFL_STATUS_DONE)
  {
    // Make sure the entire file was decompressed, and check its CRC.
    যদি ((out_buf_ofs != file_stat.m_uncomp_আকার) || (mz_crc32(MZ_CRC32_INIT, (ধ্রুবক mz_uint8 *)pBuf, (size_t)file_stat.m_uncomp_আকার) != file_stat.m_crc32))
      status = TINFL_STATUS_FAILED;
  }

  যদি ((!pZip->m_pState->m_pMem) && (!pUser_read_buf))
    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);

  ফেরত status == TINFL_STATUS_DONE;
}

mz_bool mz_zip_reader_extract_file_to_mem_no_alloc(mz_zip_archive *pZip, ধ্রুবক অক্ষর *pFilename, শূন্য *pBuf, size_t buf_আকার_2, mz_uint flags, শূন্য *pUser_read_buf, size_t user_read_buf_আকার)
{
  পূর্ণসংখ্যা file_সূচক = mz_zip_reader_locate_file(pZip, pFilename, ফাঁকা, flags);
  যদি (file_সূচক < 0)
    ফেরত MZ_FALSE;
  ফেরত mz_zip_reader_extract_to_mem_no_alloc(pZip, file_সূচক, pBuf, buf_আকার_2, flags, pUser_read_buf, user_read_buf_আকার);
}

mz_bool mz_zip_reader_extract_to_mem(mz_zip_archive *pZip, mz_uint file_সূচক, শূন্য *pBuf, size_t buf_আকার_2, mz_uint flags)
{
  ফেরত mz_zip_reader_extract_to_mem_no_alloc(pZip, file_সূচক, pBuf, buf_আকার_2, flags, ফাঁকা, 0);
}

mz_bool mz_zip_reader_extract_file_to_mem(mz_zip_archive *pZip, ধ্রুবক অক্ষর *pFilename, শূন্য *pBuf, size_t buf_আকার_2, mz_uint flags)
{
  ফেরত mz_zip_reader_extract_file_to_mem_no_alloc(pZip, pFilename, pBuf, buf_আকার_2, flags, ফাঁকা, 0);
}

শূন্য *mz_zip_reader_extract_to_heap(mz_zip_archive *pZip, mz_uint file_সূচক, size_t *p_আকার, mz_uint flags)
{
  mz_uint64 comp_আকার, uncomp_আকার, alloc_আকার_2;
  ধ্রুবক mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_সূচক);
  শূন্য *pBuf;

  যদি (p_আকার)
    *p_আকার = 0;
  যদি (!p)
    ফেরত ফাঁকা;

  comp_আকার = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_আকার_OFS);
  uncomp_আকার = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_আকার_OFS);

  alloc_আকার_2 = (flags & MZ_ZIP_FLAG_COMPRESSED_তথ্য) ? comp_আকার : uncomp_আকার;
#ifdef _MSC_VER
  যদি (((0, আকার(size_t) == আকার(mz_uint32))) && (alloc_আকার_2 > 0x7FFFFFFF))
#অন্যথা
  যদি (((আকার(size_t) == আকার(mz_uint32))) && (alloc_আকার_2 > 0x7FFFFFFF))
#endif
    ফেরত ফাঁকা;
  যদি (ফাঁকা == (pBuf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)alloc_আকার_2)))
    ফেরত ফাঁকা;

  যদি (!mz_zip_reader_extract_to_mem(pZip, file_সূচক, pBuf, (size_t)alloc_আকার_2, flags))
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
    ফেরত ফাঁকা;
  }

  যদি (p_আকার) *p_আকার = (size_t)alloc_আকার_2;
  ফেরত pBuf;
}

শূন্য *mz_zip_reader_extract_file_to_heap(mz_zip_archive *pZip, ধ্রুবক অক্ষর *pFilename, size_t *p_আকার, mz_uint flags)
{
  পূর্ণসংখ্যা file_সূচক = mz_zip_reader_locate_file(pZip, pFilename, ফাঁকা, flags);
  যদি (file_সূচক < 0)
  {
    যদি (p_আকার) *p_আকার = 0;
    ফেরত MZ_FALSE;
  }
  ফেরত mz_zip_reader_extract_to_heap(pZip, file_সূচক, p_আকার, flags);
}

mz_bool mz_zip_reader_extract_to_callback(mz_zip_archive *pZip, mz_uint file_সূচক, mz_file_write_func pCallback, শূন্য *pOpaque, mz_uint flags)
{
  পূর্ণসংখ্যা status = TINFL_STATUS_DONE; mz_uint file_crc32 = MZ_CRC32_INIT;
  mz_uint64 read_buf_আকার, read_buf_ofs = 0, read_buf_avail, comp_remaining, out_buf_ofs = 0, cur_file_ofs;
  mz_zip_archive_file_stat file_stat;
  শূন্য *pRead_buf = ফাঁকা; শূন্য *pWrite_buf = ফাঁকা;
  mz_uint32 local_header_u32[(MZ_ZIP_LOCAL_DIR_HEADER_আকার + আকার(mz_uint32) - 1) / আকার(mz_uint32)]; mz_uint8 *pLocal_header = (mz_uint8 *)local_header_u32;

  যদি (!mz_zip_reader_file_stat(pZip, file_সূচক, &file_stat))
    ফেরত MZ_FALSE;

  // Empty file, or a directory (but not always a directory - I've seen odd zips with directories that have compressed data which inflates to 0 bytes)
  যদি (!file_stat.m_comp_আকার)
    ফেরত MZ_TRUE;

  // Entry is a subdirectory (I've seen old zips with dir entries which have compressed deflate data which inflates to 0 bytes, but these entries claim to uncompress to 512 bytes in the headers).
  // I'm torn how to handle this case - should it fail instead?
  যদি (mz_zip_reader_is_file_a_directory(pZip, file_সূচক))
    ফেরত MZ_TRUE;

  // Encryption and patch files are not supported.
  যদি (file_stat.m_bit_flag & (1 | 32))
    ফেরত MZ_FALSE;

  // This function only supports stored and deflate.
  যদি ((!(flags & MZ_ZIP_FLAG_COMPRESSED_তথ্য)) && (file_stat.m_method != 0) && (file_stat.m_method != MZ_DEFLATED))
    ফেরত MZ_FALSE;

  // Read and parse the local directory entry.
  cur_file_ofs = file_stat.m_local_header_ofs;
  যদি (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pLocal_header, MZ_ZIP_LOCAL_DIR_HEADER_আকার) != MZ_ZIP_LOCAL_DIR_HEADER_আকার)
    ফেরত MZ_FALSE;
  যদি (MZ_READ_LE32(pLocal_header) != MZ_ZIP_LOCAL_DIR_HEADER_SIG)
    ফেরত MZ_FALSE;

  cur_file_ofs += MZ_ZIP_LOCAL_DIR_HEADER_আকার + MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  যদি ((cur_file_ofs + file_stat.m_comp_আকার) > pZip->m_archive_আকার)
    ফেরত MZ_FALSE;

  // Decompress the file either directly from memory or from a file input buffer.
  যদি (pZip->m_pState->m_pMem)
  {
    pRead_buf = (mz_uint8 *)pZip->m_pState->m_pMem + cur_file_ofs;
    read_buf_আকার = read_buf_avail = file_stat.m_comp_আকার;
    comp_remaining = 0;
  }
  অন্যথা
  {
    read_buf_আকার = MZ_MIN(file_stat.m_comp_আকার, MZ_ZIP_MAX_IO_BUF_আকার);
    যদি (ফাঁকা == (pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)read_buf_আকার)))
      ফেরত MZ_FALSE;
    read_buf_avail = 0;
    comp_remaining = file_stat.m_comp_আকার;
  }

  যদি ((flags & MZ_ZIP_FLAG_COMPRESSED_তথ্য) || (!file_stat.m_method))
  {
    // The file is stored or the caller has requested the compressed data.
    যদি (pZip->m_pState->m_pMem)
    {
#ifdef _MSC_VER
      যদি (((0, আকার(size_t) == আকার(mz_uint32))) && (file_stat.m_comp_আকার > 0xFFFFFFFF))
#অন্যথা
      যদি (((আকার(size_t) == আকার(mz_uint32))) && (file_stat.m_comp_আকার > 0xFFFFFFFF))
#endif
        ফেরত MZ_FALSE;
      যদি (pCallback(pOpaque, out_buf_ofs, pRead_buf, (size_t)file_stat.m_comp_আকার) != file_stat.m_comp_আকার)
        status = TINFL_STATUS_FAILED;
      অন্যথা যদি (!(flags & MZ_ZIP_FLAG_COMPRESSED_তথ্য))
        file_crc32 = (mz_uint32)mz_crc32(file_crc32, (ধ্রুবক mz_uint8 *)pRead_buf, (size_t)file_stat.m_comp_আকার);
      cur_file_ofs += file_stat.m_comp_আকার;
      out_buf_ofs += file_stat.m_comp_আকার;
      comp_remaining = 0;
    }
    অন্যথা
    {
      যখন (comp_remaining)
      {
        read_buf_avail = MZ_MIN(read_buf_আকার, comp_remaining);
        যদি (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
        {
          status = TINFL_STATUS_FAILED;
          বিরতি;
        }

        যদি (!(flags & MZ_ZIP_FLAG_COMPRESSED_তথ্য))
          file_crc32 = (mz_uint32)mz_crc32(file_crc32, (ধ্রুবক mz_uint8 *)pRead_buf, (size_t)read_buf_avail);

        যদি (pCallback(pOpaque, out_buf_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
        {
          status = TINFL_STATUS_FAILED;
          বিরতি;
        }
        cur_file_ofs += read_buf_avail;
        out_buf_ofs += read_buf_avail;
        comp_remaining -= read_buf_avail;
      }
    }
  }
  অন্যথা
  {
    tinfl_decompressor inflator;
    tinfl_init(&inflator);

    যদি (ফাঁকা == (pWrite_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, TINFL_LZ_DICT_আকার)))
      status = TINFL_STATUS_FAILED;
    অন্যথা
    {
      করো
      {
        mz_uint8 *pWrite_buf_cur = (mz_uint8 *)pWrite_buf + (out_buf_ofs & (TINFL_LZ_DICT_আকার - 1));
        size_t in_buf_আকার, out_buf_আকার = TINFL_LZ_DICT_আকার - (out_buf_ofs & (TINFL_LZ_DICT_আকার - 1));
        যদি ((!read_buf_avail) && (!pZip->m_pState->m_pMem))
        {
          read_buf_avail = MZ_MIN(read_buf_আকার, comp_remaining);
          যদি (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
          {
            status = TINFL_STATUS_FAILED;
            বিরতি;
          }
          cur_file_ofs += read_buf_avail;
          comp_remaining -= read_buf_avail;
          read_buf_ofs = 0;
        }

        in_buf_আকার = (size_t)read_buf_avail;
        status = tinfl_decompress(&inflator, (ধ্রুবক mz_uint8 *)pRead_buf + read_buf_ofs, &in_buf_আকার, (mz_uint8 *)pWrite_buf, pWrite_buf_cur, &out_buf_আকার, comp_remaining ? TINFL_FLAG_HAS_MORE_প্রবেশ : 0);
        read_buf_avail -= in_buf_আকার;
        read_buf_ofs += in_buf_আকার;

        যদি (out_buf_আকার)
        {
          যদি (pCallback(pOpaque, out_buf_ofs, pWrite_buf_cur, out_buf_আকার) != out_buf_আকার)
          {
            status = TINFL_STATUS_FAILED;
            বিরতি;
          }
          file_crc32 = (mz_uint32)mz_crc32(file_crc32, pWrite_buf_cur, out_buf_আকার);
          যদি ((out_buf_ofs += out_buf_আকার) > file_stat.m_uncomp_আকার)
          {
            status = TINFL_STATUS_FAILED;
            বিরতি;
          }
        }
      } যখন ((status == TINFL_STATUS_NEEDS_MORE_প্রবেশ) || (status == TINFL_STATUS_HAS_MORE_OUTPUT));
    }
  }

  যদি ((status == TINFL_STATUS_DONE) && (!(flags & MZ_ZIP_FLAG_COMPRESSED_তথ্য)))
  {
    // Make sure the entire file was decompressed, and check its CRC.
    যদি ((out_buf_ofs != file_stat.m_uncomp_আকার) || (file_crc32 != file_stat.m_crc32))
      status = TINFL_STATUS_FAILED;
  }

  যদি (!pZip->m_pState->m_pMem)
    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
  যদি (pWrite_buf)
    pZip->m_pFree(pZip->m_pAlloc_opaque, pWrite_buf);

  ফেরত status == TINFL_STATUS_DONE;
}

mz_bool mz_zip_reader_extract_file_to_callback(mz_zip_archive *pZip, ধ্রুবক অক্ষর *pFilename, mz_file_write_func pCallback, শূন্য *pOpaque, mz_uint flags)
{
  পূর্ণসংখ্যা file_সূচক = mz_zip_reader_locate_file(pZip, pFilename, ফাঁকা, flags);
  যদি (file_সূচক < 0)
    ফেরত MZ_FALSE;
  ফেরত mz_zip_reader_extract_to_callback(pZip, file_সূচক, pCallback, pOpaque, flags);
}

#ifndef MINIZ_NO_STDIO
স্থির size_t mz_zip_file_write_callback(শূন্য *pOpaque, mz_uint64 ofs, ধ্রুবক শূন্য *pBuf, size_t n)
{
  (শূন্য)ofs; ফেরত MZ_FWRITE(pBuf, 1, n, (MZ_FILE*)pOpaque);
}

mz_bool mz_zip_reader_extract_to_file(mz_zip_archive *pZip, mz_uint file_সূচক, ধ্রুবক অক্ষর *pDst_filename, mz_uint flags)
{
  mz_bool status;
  mz_zip_archive_file_stat file_stat;
  MZ_FILE *pFile;
  যদি (!mz_zip_reader_file_stat(pZip, file_সূচক, &file_stat))
    ফেরত MZ_FALSE;
  pFile = MZ_FOPEN(pDst_filename, "wb");
  যদি (!pFile)
    ফেরত MZ_FALSE;
  status = mz_zip_reader_extract_to_callback(pZip, file_সূচক, mz_zip_file_write_callback, pFile, flags);
  যদি (MZ_FCLOSE(pFile) == EOF)
    ফেরত MZ_FALSE;
#ifndef MINIZ_NO_TIME
  যদি (status)
    mz_zip_set_file_times(pDst_filename, file_stat.m_time, file_stat.m_time);
#endif
  ফেরত status;
}
#endif // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_reader_end(mz_zip_archive *pZip)
{
  যদি ((!pZip) || (!pZip->m_pState) || (!pZip->m_pAlloc) || (!pZip->m_pFree) || (pZip->m_zip_mode != MZ_ZIP_MODE_READING))
    ফেরত MZ_FALSE;

  যদি (pZip->m_pState)
  {
    mz_zip_internal_state *pState = pZip->m_pState; pZip->m_pState = ফাঁকা;
    mz_zip_array_clear(pZip, &pState->m_central_dir);
    mz_zip_array_clear(pZip, &pState->m_central_dir_offsets);
    mz_zip_array_clear(pZip, &pState->m_sorted_central_dir_offsets);

#ifndef MINIZ_NO_STDIO
    যদি (pState->m_pFile)
    {
      MZ_FCLOSE(pState->m_pFile);
      pState->m_pFile = ফাঁকা;
    }
#endif // #ifndef MINIZ_NO_STDIO

    pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
  }
  pZip->m_zip_mode = MZ_ZIP_MODE_INVALID;

  ফেরত MZ_TRUE;
}

#ifndef MINIZ_NO_STDIO
mz_bool mz_zip_reader_extract_file_to_file(mz_zip_archive *pZip, ধ্রুবক অক্ষর *pArchive_filename, ধ্রুবক অক্ষর *pDst_filename, mz_uint flags)
{
  পূর্ণসংখ্যা file_সূচক = mz_zip_reader_locate_file(pZip, pArchive_filename, ফাঁকা, flags);
  যদি (file_সূচক < 0)
    ফেরত MZ_FALSE;
  ফেরত mz_zip_reader_extract_to_file(pZip, file_সূচক, pDst_filename, flags);
}
#endif

// ------------------- .ZIP archive writing

#ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

স্থির শূন্য mz_write_le16(mz_uint8 *p, mz_uint16 v) { p[0] = (mz_uint8)v; p[1] = (mz_uint8)(v >> 8); }
স্থির শূন্য mz_write_le32(mz_uint8 *p, mz_uint32 v) { p[0] = (mz_uint8)v; p[1] = (mz_uint8)(v >> 8); p[2] = (mz_uint8)(v >> 16); p[3] = (mz_uint8)(v >> 24); }
#define MZ_WRITE_LE16(p, v) mz_write_le16((mz_uint8 *)(p), (mz_uint16)(v))
#define MZ_WRITE_LE32(p, v) mz_write_le32((mz_uint8 *)(p), (mz_uint32)(v))

mz_bool mz_zip_writer_init(mz_zip_archive *pZip, mz_uint64 existing_আকার)
{
  যদি ((!pZip) || (pZip->m_pState) || (!pZip->m_pWrite) || (pZip->m_zip_mode != MZ_ZIP_MODE_INVALID))
    ফেরত MZ_FALSE;

  যদি (pZip->m_file_offset_alignment)
  {
    // Ensure user specified file offset alignment is a power of 2.
    যদি (pZip->m_file_offset_alignment & (pZip->m_file_offset_alignment - 1))
      ফেরত MZ_FALSE;
  }

  যদি (!pZip->m_pAlloc) pZip->m_pAlloc = def_alloc_func;
  যদি (!pZip->m_pFree) pZip->m_pFree = def_free_func;
  যদি (!pZip->m_pRealloc) pZip->m_pRealloc = def_realloc_func;

  pZip->m_zip_mode = MZ_ZIP_MODE_WRITING;
  pZip->m_archive_আকার = existing_আকার;
  pZip->m_central_directory_file_ofs = 0;
  pZip->m_যোগ_files = 0;

  যদি (ফাঁকা == (pZip->m_pState = (mz_zip_internal_state *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, আকার(mz_zip_internal_state))))
    ফেরত MZ_FALSE;
  memset(pZip->m_pState, 0, আকার(mz_zip_internal_state));
  MZ_ZIP_ARRAY_SET_ELEMENT_আকার(&pZip->m_pState->m_central_dir, আকার(mz_uint8));
  MZ_ZIP_ARRAY_SET_ELEMENT_আকার(&pZip->m_pState->m_central_dir_offsets, আকার(mz_uint32));
  MZ_ZIP_ARRAY_SET_ELEMENT_আকার(&pZip->m_pState->m_sorted_central_dir_offsets, আকার(mz_uint32));
  ফেরত MZ_TRUE;
}

স্থির size_t mz_zip_heap_write_func(শূন্য *pOpaque, mz_uint64 file_ofs, ধ্রুবক শূন্য *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_zip_internal_state *pState = pZip->m_pState;
  mz_uint64 new_আকার = MZ_MAX(file_ofs + n, pState->m_mem_আকার);
#ifdef _MSC_VER
  যদি ((!n) || ((0, আকার(size_t) == আকার(mz_uint32)) && (new_আকার > 0x7FFFFFFF)))
#অন্যথা
  যদি ((!n) || ((আকার(size_t) == আকার(mz_uint32)) && (new_আকার > 0x7FFFFFFF)))
#endif
    ফেরত 0;
  যদি (new_আকার > pState->m_mem_capacity)
  {
    শূন্য *pNew_block;
    size_t new_capacity = MZ_MAX(64, pState->m_mem_capacity); যখন (new_capacity < new_আকার) new_capacity *= 2;
    যদি (ফাঁকা == (pNew_block = pZip->m_pRealloc(pZip->m_pAlloc_opaque, pState->m_pMem, 1, new_capacity)))
      ফেরত 0;
    pState->m_pMem = pNew_block; pState->m_mem_capacity = new_capacity;
  }
  memcpy((mz_uint8 *)pState->m_pMem + file_ofs, pBuf, n);
  pState->m_mem_আকার = (size_t)new_আকার;
  ফেরত n;
}

mz_bool mz_zip_writer_init_heap(mz_zip_archive *pZip, size_t আকার_to_reserve_at_beginning, size_t initial_allocation_আকার)
{
  pZip->m_pWrite = mz_zip_heap_write_func;
  pZip->m_pIO_opaque = pZip;
  যদি (!mz_zip_writer_init(pZip, আকার_to_reserve_at_beginning))
    ফেরত MZ_FALSE;
  যদি (0 != (initial_allocation_আকার = MZ_MAX(initial_allocation_আকার, আকার_to_reserve_at_beginning)))
  {
    যদি (ফাঁকা == (pZip->m_pState->m_pMem = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, initial_allocation_আকার)))
    {
      mz_zip_writer_end(pZip);
      ফেরত MZ_FALSE;
    }
    pZip->m_pState->m_mem_capacity = initial_allocation_আকার;
  }
  ফেরত MZ_TRUE;
}

#ifndef MINIZ_NO_STDIO
স্থির size_t mz_zip_file_write_func(শূন্য *pOpaque, mz_uint64 file_ofs, ধ্রুবক শূন্য *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_int64 cur_ofs = MZ_FTELL64(pZip->m_pState->m_pFile);
  যদি (((mz_int64)file_ofs < 0) || (((cur_ofs != (mz_int64)file_ofs)) && (MZ_FSEEK64(pZip->m_pState->m_pFile, (mz_int64)file_ofs, SEEK_SET))))
    ফেরত 0;
  ফেরত MZ_FWRITE(pBuf, 1, n, pZip->m_pState->m_pFile);
}

mz_bool mz_zip_writer_init_file(mz_zip_archive *pZip, ধ্রুবক অক্ষর *pFilename, mz_uint64 আকার_to_reserve_at_beginning)
{
  MZ_FILE *pFile;
  pZip->m_pWrite = mz_zip_file_write_func;
  pZip->m_pIO_opaque = pZip;
  যদি (!mz_zip_writer_init(pZip, আকার_to_reserve_at_beginning))
    ফেরত MZ_FALSE;
  যদি (ফাঁকা == (pFile = MZ_FOPEN(pFilename, "wb")))
  {
    mz_zip_writer_end(pZip);
    ফেরত MZ_FALSE;
  }
  pZip->m_pState->m_pFile = pFile;
  যদি (আকার_to_reserve_at_beginning)
  {
    mz_uint64 cur_ofs = 0; অক্ষর buf[4096]; MZ_CLEAR_ARR(buf);
    করো
    {
      size_t n = (size_t)MZ_MIN(আকার(buf), আকার_to_reserve_at_beginning);
      যদি (pZip->m_pWrite(pZip->m_pIO_opaque, cur_ofs, buf, n) != n)
      {
        mz_zip_writer_end(pZip);
        ফেরত MZ_FALSE;
      }
      cur_ofs += n; আকার_to_reserve_at_beginning -= n;
    } যখন (আকার_to_reserve_at_beginning);
  }
  ফেরত MZ_TRUE;
}
#endif // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_writer_init_from_reader(mz_zip_archive *pZip, ধ্রুবক অক্ষর *pFilename)
{
  mz_zip_internal_state *pState;
  যদি ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_mode != MZ_ZIP_MODE_READING))
    ফেরত MZ_FALSE;
  // No sense in trying to write to an archive that's already at the support max size
  যদি ((pZip->m_যোগ_files == 0xFFFF) || ((pZip->m_archive_আকার + MZ_ZIP_CENTRAL_DIR_HEADER_আকার + MZ_ZIP_LOCAL_DIR_HEADER_আকার) > 0xFFFFFFFF))
    ফেরত MZ_FALSE;

  pState = pZip->m_pState;

  যদি (pState->m_pFile)
  {
#ifdef MINIZ_NO_STDIO
    pFilename; ফেরত MZ_FALSE;
#অন্যথা
    // Archive is being read from stdio - try to reopen as writable.
    যদি (pZip->m_pIO_opaque != pZip)
      ফেরত MZ_FALSE;
    যদি (!pFilename)
      ফেরত MZ_FALSE;
    pZip->m_pWrite = mz_zip_file_write_func;
    যদি (ফাঁকা == (pState->m_pFile = MZ_FREOPEN(pFilename, "r+b", pState->m_pFile)))
    {
      // The mz_zip_archive is now in a bogus state because pState->m_pFile is NULL, so just close it.
      mz_zip_reader_end(pZip);
      ফেরত MZ_FALSE;
    }
#endif // #ifdef MINIZ_NO_STDIO
  }
  অন্যথা যদি (pState->m_pMem)
  {
    // Archive lives in a memory block. Assume it's from the heap that we can resize using the realloc callback.
    যদি (pZip->m_pIO_opaque != pZip)
      ফেরত MZ_FALSE;
    pState->m_mem_capacity = pState->m_mem_আকার;
    pZip->m_pWrite = mz_zip_heap_write_func;
  }
  // Archive is being read via a user provided read function - make sure the user has specified a write function too.
  অন্যথা যদি (!pZip->m_pWrite)
    ফেরত MZ_FALSE;

  // Start writing new files at the archive's current central directory location.
  pZip->m_archive_আকার = pZip->m_central_directory_file_ofs;
  pZip->m_zip_mode = MZ_ZIP_MODE_WRITING;
  pZip->m_central_directory_file_ofs = 0;

  ফেরত MZ_TRUE;
}

mz_bool mz_zip_writer_add_mem(mz_zip_archive *pZip, ধ্রুবক অক্ষর *pArchive_name, ধ্রুবক শূন্য *pBuf, size_t buf_আকার_2, mz_uint level_and_flags)
{
  ফেরত mz_zip_writer_add_mem_ex(pZip, pArchive_name, pBuf, buf_আকার_2, ফাঁকা, 0, level_and_flags, 0, 0);
}

প্রকারলেখ কাঠামো
{
  mz_zip_archive *m_pZip;
  mz_uint64 m_cur_archive_file_ofs;
  mz_uint64 m_comp_আকার;
} mz_zip_writer_add_state;

স্থির mz_bool mz_zip_writer_add_put_buf_callback(ধ্রুবক শূন্য* pBuf, পূর্ণসংখ্যা len, শূন্য *pUser)
{
  mz_zip_writer_add_state *pState = (mz_zip_writer_add_state *)pUser;
  যদি ((পূর্ণসংখ্যা)pState->m_pZip->m_pWrite(pState->m_pZip->m_pIO_opaque, pState->m_cur_archive_file_ofs, pBuf, len) != len)
    ফেরত MZ_FALSE;
  pState->m_cur_archive_file_ofs += len;
  pState->m_comp_আকার += len;
  ফেরত MZ_TRUE;
}

স্থির mz_bool mz_zip_writer_create_local_dir_header(mz_zip_archive *pZip, mz_uint8 *pDst, mz_uint16 filename_আকার, mz_uint16 extra_আকার, mz_uint64 uncomp_আকার, mz_uint64 comp_আকার, mz_uint32 uncomp_crc32, mz_uint16 method, mz_uint16 bit_flags, mz_uint16 dos_time, mz_uint16 dos_date)
{
  (শূন্য)pZip;
  memset(pDst, 0, MZ_ZIP_LOCAL_DIR_HEADER_আকার);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_SIG_OFS, MZ_ZIP_LOCAL_DIR_HEADER_SIG);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_VERSION_NEEDED_OFS, method ? 20 : 0);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_BIT_FLAG_OFS, bit_flags);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_METHOD_OFS, method);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILE_TIME_OFS, dos_time);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILE_DATE_OFS, dos_date);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_CRC32_OFS, uncomp_crc32);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_COMPRESSED_আকার_OFS, comp_আকার);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_DECOMPRESSED_আকার_OFS, uncomp_আকার);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILENAME_LEN_OFS, filename_আকার);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_EXTRA_LEN_OFS, extra_আকার);
  ফেরত MZ_TRUE;
}

স্থির mz_bool mz_zip_writer_create_central_dir_header(mz_zip_archive *pZip, mz_uint8 *pDst, mz_uint16 filename_আকার, mz_uint16 extra_আকার, mz_uint16 comment_আকার, mz_uint64 uncomp_আকার, mz_uint64 comp_আকার, mz_uint32 uncomp_crc32, mz_uint16 method, mz_uint16 bit_flags, mz_uint16 dos_time, mz_uint16 dos_date, mz_uint64 local_header_ofs, mz_uint32 ext_attributes)
{
  (শূন্য)pZip;
  memset(pDst, 0, MZ_ZIP_CENTRAL_DIR_HEADER_আকার);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_SIG_OFS, MZ_ZIP_CENTRAL_DIR_HEADER_SIG);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_VERSION_NEEDED_OFS, method ? 20 : 0);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_BIT_FLAG_OFS, bit_flags);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_METHOD_OFS, method);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILE_TIME_OFS, dos_time);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILE_DATE_OFS, dos_date);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_CRC32_OFS, uncomp_crc32);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_COMPRESSED_আকার_OFS, comp_আকার);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_DECOMPRESSED_আকার_OFS, uncomp_আকার);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILENAME_LEN_OFS, filename_আকার);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_EXTRA_LEN_OFS, extra_আকার);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_COMMENT_LEN_OFS, comment_আকার);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS, ext_attributes);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_LOCAL_HEADER_OFS, local_header_ofs);
  ফেরত MZ_TRUE;
}

স্থির mz_bool mz_zip_writer_add_to_central_dir(mz_zip_archive *pZip, ধ্রুবক অক্ষর *pFilename, mz_uint16 filename_আকার, ধ্রুবক শূন্য *pExtra, mz_uint16 extra_আকার, ধ্রুবক শূন্য *pComment, mz_uint16 comment_আকার, mz_uint64 uncomp_আকার, mz_uint64 comp_আকার, mz_uint32 uncomp_crc32, mz_uint16 method, mz_uint16 bit_flags, mz_uint16 dos_time, mz_uint16 dos_date, mz_uint64 local_header_ofs, mz_uint32 ext_attributes)
{
  mz_zip_internal_state *pState = pZip->m_pState;
  mz_uint32 central_dir_ofs = (mz_uint32)pState->m_central_dir.m_আকার;
  size_t orig_central_dir_আকার = pState->m_central_dir.m_আকার;
  mz_uint8 central_dir_header[MZ_ZIP_CENTRAL_DIR_HEADER_আকার];

  // No zip64 support yet
  যদি ((local_header_ofs > 0xFFFFFFFF) || (((mz_uint64)pState->m_central_dir.m_আকার + MZ_ZIP_CENTRAL_DIR_HEADER_আকার + filename_আকার + extra_আকার + comment_আকার) > 0xFFFFFFFF))
    ফেরত MZ_FALSE;

  যদি (!mz_zip_writer_create_central_dir_header(pZip, central_dir_header, filename_আকার, extra_আকার, comment_আকার, uncomp_আকার, comp_আকার, uncomp_crc32, method, bit_flags, dos_time, dos_date, local_header_ofs, ext_attributes))
    ফেরত MZ_FALSE;

  যদি ((!mz_zip_array_ঠেলো_back(pZip, &pState->m_central_dir, central_dir_header, MZ_ZIP_CENTRAL_DIR_HEADER_আকার)) ||
      (!mz_zip_array_ঠেলো_back(pZip, &pState->m_central_dir, pFilename, filename_আকার)) ||
      (!mz_zip_array_ঠেলো_back(pZip, &pState->m_central_dir, pExtra, extra_আকার)) ||
      (!mz_zip_array_ঠেলো_back(pZip, &pState->m_central_dir, pComment, comment_আকার)) ||
      (!mz_zip_array_ঠেলো_back(pZip, &pState->m_central_dir_offsets, &central_dir_ofs, 1)))
  {
    // Try to push the central directory array back into its original state.
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_আকার, MZ_FALSE);
    ফেরত MZ_FALSE;
  }

  ফেরত MZ_TRUE;
}

স্থির mz_bool mz_zip_writer_validate_archive_name(ধ্রুবক অক্ষর *pArchive_name)
{
  // Basic ZIP archive filename validity checks: Valid filenames cannot start with a forward slash, cannot contain a drive letter, and cannot use DOS-style backward slashes.
  যদি (*pArchive_name == '/')
    ফেরত MZ_FALSE;
  যখন (*pArchive_name)
  {
    যদি ((*pArchive_name == '\\') || (*pArchive_name == ':'))
      ফেরত MZ_FALSE;
    pArchive_name++;
  }
  ফেরত MZ_TRUE;
}

স্থির mz_uint mz_zip_writer_compute_padding_needed_for_file_alignment(mz_zip_archive *pZip)
{
  mz_uint32 n;
  যদি (!pZip->m_file_offset_alignment)
    ফেরত 0;
  n = (mz_uint32)(pZip->m_archive_আকার & (pZip->m_file_offset_alignment - 1));
  ফেরত (pZip->m_file_offset_alignment - n) & (pZip->m_file_offset_alignment - 1);
}

স্থির mz_bool mz_zip_writer_write_zeros(mz_zip_archive *pZip, mz_uint64 cur_file_ofs, mz_uint32 n)
{
  অক্ষর buf[4096];
  memset(buf, 0, MZ_MIN(আকার(buf), n));
  যখন (n)
  {
    mz_uint32 s = MZ_MIN(আকার(buf), n);
    যদি (pZip->m_pWrite(pZip->m_pIO_opaque, cur_file_ofs, buf, s) != s)
      ফেরত MZ_FALSE;
    cur_file_ofs += s; n -= s;
  }
  ফেরত MZ_TRUE;
}

mz_bool mz_zip_writer_add_mem_ex(mz_zip_archive *pZip, ধ্রুবক অক্ষর *pArchive_name, ধ্রুবক শূন্য *pBuf, size_t buf_আকার_2, ধ্রুবক শূন্য *pComment, mz_uint16 comment_আকার, mz_uint level_and_flags, mz_uint64 uncomp_আকার, mz_uint32 uncomp_crc32)
{
  mz_uint16 method = 0, dos_time = 0, dos_date = 0;
  mz_uint level, ext_attributes = 0, অঙ্ক_alignment_padding_bytes;
  mz_uint64 local_dir_header_ofs = pZip->m_archive_আকার, cur_archive_file_ofs = pZip->m_archive_আকার, comp_আকার = 0;
  size_t archive_name_আকার;
  mz_uint8 local_dir_header[MZ_ZIP_LOCAL_DIR_HEADER_আকার];
  tdefl_compressor *pComp = ফাঁকা;
  mz_bool store_তথ্য_uncompressed;
  mz_zip_internal_state *pState;

  যদি ((পূর্ণসংখ্যা)level_and_flags < 0)
    level_and_flags = MZ_DEFAULT_LEVEL;
  level = level_and_flags & 0xF;
  store_তথ্য_uncompressed = ((!level) || (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_তথ্য));

  যদি ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_mode != MZ_ZIP_MODE_WRITING) || ((buf_আকার_2) && (!pBuf)) || (!pArchive_name) || ((comment_আকার) && (!pComment)) || (pZip->m_যোগ_files == 0xFFFF) || (level > MZ_UBER_COMPRESSION))
    ফেরত MZ_FALSE;

  pState = pZip->m_pState;

  যদি ((!(level_and_flags & MZ_ZIP_FLAG_COMPRESSED_তথ্য)) && (uncomp_আকার))
    ফেরত MZ_FALSE;
  // No zip64 support yet
  যদি ((buf_আকার_2 > 0xFFFFFFFF) || (uncomp_আকার > 0xFFFFFFFF))
    ফেরত MZ_FALSE;
  যদি (!mz_zip_writer_validate_archive_name(pArchive_name))
    ফেরত MZ_FALSE;

#ifndef MINIZ_NO_TIME
  {
    time_t cur_time; time(&cur_time);
    mz_zip_time_to_dos_time(cur_time, &dos_time, &dos_date);
  }
#endif // #ifndef MINIZ_NO_TIME

  archive_name_আকার = strlen(pArchive_name);
  যদি (archive_name_আকার > 0xFFFF)
    ফেরত MZ_FALSE;

  অঙ্ক_alignment_padding_bytes = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  যদি ((pZip->m_যোগ_files == 0xFFFF) || ((pZip->m_archive_আকার + অঙ্ক_alignment_padding_bytes + MZ_ZIP_LOCAL_DIR_HEADER_আকার + MZ_ZIP_CENTRAL_DIR_HEADER_আকার + comment_আকার + archive_name_আকার) > 0xFFFFFFFF))
    ফেরত MZ_FALSE;

  যদি ((archive_name_আকার) && (pArchive_name[archive_name_আকার - 1] == '/'))
  {
    // Set DOS Subdirectory attribute bit.
    ext_attributes |= 0x10;
    // Subdirectories cannot contain data.
    যদি ((buf_আকার_2) || (uncomp_আকার))
      ফেরত MZ_FALSE;
  }

  // Try to do any allocations before writing to the archive, so if an allocation fails the file remains unmodified. (A good idea if we're doing an in-place modification.)
  যদি ((!mz_zip_array_ensure_room(pZip, &pState->m_central_dir, MZ_ZIP_CENTRAL_DIR_HEADER_আকার + archive_name_আকার + comment_আকার)) || (!mz_zip_array_ensure_room(pZip, &pState->m_central_dir_offsets, 1)))
    ফেরত MZ_FALSE;

  যদি ((!store_তথ্য_uncompressed) && (buf_আকার_2))
  {
    যদি (ফাঁকা == (pComp = (tdefl_compressor *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, আকার(tdefl_compressor))))
      ফেরত MZ_FALSE;
  }

  যদি (!mz_zip_writer_write_zeros(pZip, cur_archive_file_ofs, অঙ্ক_alignment_padding_bytes + আকার(local_dir_header)))
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
    ফেরত MZ_FALSE;
  }
  local_dir_header_ofs += অঙ্ক_alignment_padding_bytes;
  যদি (pZip->m_file_offset_alignment) { MZ_ASSERT((local_dir_header_ofs & (pZip->m_file_offset_alignment - 1)) == 0); }
  cur_archive_file_ofs += অঙ্ক_alignment_padding_bytes + আকার(local_dir_header);

  MZ_CLEAR_ARR(local_dir_header);
  যদি (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pArchive_name, archive_name_আকার) != archive_name_আকার)
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
    ফেরত MZ_FALSE;
  }
  cur_archive_file_ofs += archive_name_আকার;

  যদি (!(level_and_flags & MZ_ZIP_FLAG_COMPRESSED_তথ্য))
  {
    uncomp_crc32 = (mz_uint32)mz_crc32(MZ_CRC32_INIT, (ধ্রুবক mz_uint8*)pBuf, buf_আকার_2);
    uncomp_আকার = buf_আকার_2;
    যদি (uncomp_আকার <= 3)
    {
      level = 0;
      store_তথ্য_uncompressed = MZ_TRUE;
    }
  }

  যদি (store_তথ্য_uncompressed)
  {
    যদি (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pBuf, buf_আকার_2) != buf_আকার_2)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
      ফেরত MZ_FALSE;
    }

    cur_archive_file_ofs += buf_আকার_2;
    comp_আকার = buf_আকার_2;

    যদি (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_তথ্য)
      method = MZ_DEFLATED;
  }
  অন্যথা যদি (buf_আকার_2)
  {
    mz_zip_writer_add_state state;

    state.m_pZip = pZip;
    state.m_cur_archive_file_ofs = cur_archive_file_ofs;
    state.m_comp_আকার = 0;

    যদি ((tdefl_init(pComp, mz_zip_writer_add_put_buf_callback, &state, tdefl_create_comp_flags_from_zip_params(level, -15, MZ_DEFAULT_STRATEGY)) != TDEFL_STATUS_OKAY) ||
        (tdefl_compress_বাফার(pComp, pBuf, buf_আকার_2, TDEFL_FINISH) != TDEFL_STATUS_DONE))
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
      ফেরত MZ_FALSE;
    }

    comp_আকার = state.m_comp_আকার;
    cur_archive_file_ofs = state.m_cur_archive_file_ofs;

    method = MZ_DEFLATED;
  }

  pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
  pComp = ফাঁকা;

  // no zip64 support yet
  যদি ((comp_আকার > 0xFFFFFFFF) || (cur_archive_file_ofs > 0xFFFFFFFF))
    ফেরত MZ_FALSE;

  যদি (!mz_zip_writer_create_local_dir_header(pZip, local_dir_header, (mz_uint16)archive_name_আকার, 0, uncomp_আকার, comp_আকার, uncomp_crc32, method, 0, dos_time, dos_date))
    ফেরত MZ_FALSE;

  যদি (pZip->m_pWrite(pZip->m_pIO_opaque, local_dir_header_ofs, local_dir_header, আকার(local_dir_header)) != আকার(local_dir_header))
    ফেরত MZ_FALSE;

  যদি (!mz_zip_writer_add_to_central_dir(pZip, pArchive_name, (mz_uint16)archive_name_আকার, ফাঁকা, 0, pComment, comment_আকার, uncomp_আকার, comp_আকার, uncomp_crc32, method, 0, dos_time, dos_date, local_dir_header_ofs, ext_attributes))
    ফেরত MZ_FALSE;

  pZip->m_যোগ_files++;
  pZip->m_archive_আকার = cur_archive_file_ofs;

  ফেরত MZ_TRUE;
}

#ifndef MINIZ_NO_STDIO
mz_bool mz_zip_writer_add_file(mz_zip_archive *pZip, ধ্রুবক অক্ষর *pArchive_name, ধ্রুবক অক্ষর *pSrc_filename, ধ্রুবক শূন্য *pComment, mz_uint16 comment_আকার, mz_uint level_and_flags)
{
  mz_uint uncomp_crc32 = MZ_CRC32_INIT, level, অঙ্ক_alignment_padding_bytes;
  mz_uint16 method = 0, dos_time = 0, dos_date = 0, ext_attributes = 0;
  mz_uint64 local_dir_header_ofs = pZip->m_archive_আকার, cur_archive_file_ofs = pZip->m_archive_আকার, uncomp_আকার = 0, comp_আকার = 0;
  size_t archive_name_আকার;
  mz_uint8 local_dir_header[MZ_ZIP_LOCAL_DIR_HEADER_আকার];
  MZ_FILE *pSrc_file = ফাঁকা;

  যদি ((পূর্ণসংখ্যা)level_and_flags < 0)
    level_and_flags = MZ_DEFAULT_LEVEL;
  level = level_and_flags & 0xF;

  যদি ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_mode != MZ_ZIP_MODE_WRITING) || (!pArchive_name) || ((comment_আকার) && (!pComment)) || (level > MZ_UBER_COMPRESSION))
    ফেরত MZ_FALSE;
  যদি (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_তথ্য)
    ফেরত MZ_FALSE;
  যদি (!mz_zip_writer_validate_archive_name(pArchive_name))
    ফেরত MZ_FALSE;

  archive_name_আকার = strlen(pArchive_name);
  যদি (archive_name_আকার > 0xFFFF)
    ফেরত MZ_FALSE;

  অঙ্ক_alignment_padding_bytes = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  যদি ((pZip->m_যোগ_files == 0xFFFF) || ((pZip->m_archive_আকার + অঙ্ক_alignment_padding_bytes + MZ_ZIP_LOCAL_DIR_HEADER_আকার + MZ_ZIP_CENTRAL_DIR_HEADER_আকার + comment_আকার + archive_name_আকার) > 0xFFFFFFFF))
    ফেরত MZ_FALSE;

  যদি (!mz_zip_get_file_modified_time(pSrc_filename, &dos_time, &dos_date))
    ফেরত MZ_FALSE;

  pSrc_file = MZ_FOPEN(pSrc_filename, "rb");
  যদি (!pSrc_file)
    ফেরত MZ_FALSE;
  MZ_FSEEK64(pSrc_file, 0, SEEK_END);
  uncomp_আকার = MZ_FTELL64(pSrc_file);
  MZ_FSEEK64(pSrc_file, 0, SEEK_SET);

  যদি (uncomp_আকার > 0xFFFFFFFF)
  {
    // No zip64 support yet
    MZ_FCLOSE(pSrc_file);
    ফেরত MZ_FALSE;
  }
  যদি (uncomp_আকার <= 3)
    level = 0;

  যদি (!mz_zip_writer_write_zeros(pZip, cur_archive_file_ofs, অঙ্ক_alignment_padding_bytes + আকার(local_dir_header)))
  {
    MZ_FCLOSE(pSrc_file);
    ফেরত MZ_FALSE;
  }
  local_dir_header_ofs += অঙ্ক_alignment_padding_bytes;
  যদি (pZip->m_file_offset_alignment) { MZ_ASSERT((local_dir_header_ofs & (pZip->m_file_offset_alignment - 1)) == 0); }
  cur_archive_file_ofs += অঙ্ক_alignment_padding_bytes + আকার(local_dir_header);

  MZ_CLEAR_ARR(local_dir_header);
  যদি (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pArchive_name, archive_name_আকার) != archive_name_আকার)
  {
    MZ_FCLOSE(pSrc_file);
    ফেরত MZ_FALSE;
  }
  cur_archive_file_ofs += archive_name_আকার;

  যদি (uncomp_আকার)
  {
    mz_uint64 uncomp_remaining = uncomp_আকার;
    শূন্য *pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, MZ_ZIP_MAX_IO_BUF_আকার);
    যদি (!pRead_buf)
    {
      MZ_FCLOSE(pSrc_file);
      ফেরত MZ_FALSE;
    }

    যদি (!level)
    {
      যখন (uncomp_remaining)
      {
        mz_uint n = (mz_uint)MZ_MIN(MZ_ZIP_MAX_IO_BUF_আকার, uncomp_remaining);
        যদি ((MZ_FREAD(pRead_buf, 1, n, pSrc_file) != n) || (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pRead_buf, n) != n))
        {
          pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
          MZ_FCLOSE(pSrc_file);
          ফেরত MZ_FALSE;
        }
        uncomp_crc32 = (mz_uint32)mz_crc32(uncomp_crc32, (ধ্রুবক mz_uint8 *)pRead_buf, n);
        uncomp_remaining -= n;
        cur_archive_file_ofs += n;
      }
      comp_আকার = uncomp_আকার;
    }
    অন্যথা
    {
      mz_bool ফলাফল = MZ_FALSE;
      mz_zip_writer_add_state state;
      tdefl_compressor *pComp = (tdefl_compressor *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, আকার(tdefl_compressor));
      যদি (!pComp)
      {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        ফেরত MZ_FALSE;
      }

      state.m_pZip = pZip;
      state.m_cur_archive_file_ofs = cur_archive_file_ofs;
      state.m_comp_আকার = 0;

      যদি (tdefl_init(pComp, mz_zip_writer_add_put_buf_callback, &state, tdefl_create_comp_flags_from_zip_params(level, -15, MZ_DEFAULT_STRATEGY)) != TDEFL_STATUS_OKAY)
      {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        ফেরত MZ_FALSE;
      }

      জন্য ( ; ; )
      {
        size_t in_buf_আকার = (mz_uint32)MZ_MIN(uncomp_remaining, MZ_ZIP_MAX_IO_BUF_আকার);
        tdefl_status status;

        যদি (MZ_FREAD(pRead_buf, 1, in_buf_আকার, pSrc_file) != in_buf_আকার)
          বিরতি;

        uncomp_crc32 = (mz_uint32)mz_crc32(uncomp_crc32, (ধ্রুবক mz_uint8 *)pRead_buf, in_buf_আকার);
        uncomp_remaining -= in_buf_আকার;

        status = tdefl_compress_বাফার(pComp, pRead_buf, in_buf_আকার, uncomp_remaining ? TDEFL_NO_FLUSH : TDEFL_FINISH);
        যদি (status == TDEFL_STATUS_DONE)
        {
          ফলাফল = MZ_TRUE;
          বিরতি;
        }
        অন্যথা যদি (status != TDEFL_STATUS_OKAY)
          বিরতি;
      }

      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);

      যদি (!ফলাফল)
      {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        ফেরত MZ_FALSE;
      }

      comp_আকার = state.m_comp_আকার;
      cur_archive_file_ofs = state.m_cur_archive_file_ofs;

      method = MZ_DEFLATED;
    }

    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
  }

  MZ_FCLOSE(pSrc_file); pSrc_file = ফাঁকা;

  // no zip64 support yet
  যদি ((comp_আকার > 0xFFFFFFFF) || (cur_archive_file_ofs > 0xFFFFFFFF))
    ফেরত MZ_FALSE;

  যদি (!mz_zip_writer_create_local_dir_header(pZip, local_dir_header, (mz_uint16)archive_name_আকার, 0, uncomp_আকার, comp_আকার, uncomp_crc32, method, 0, dos_time, dos_date))
    ফেরত MZ_FALSE;

  যদি (pZip->m_pWrite(pZip->m_pIO_opaque, local_dir_header_ofs, local_dir_header, আকার(local_dir_header)) != আকার(local_dir_header))
    ফেরত MZ_FALSE;

  যদি (!mz_zip_writer_add_to_central_dir(pZip, pArchive_name, (mz_uint16)archive_name_আকার, ফাঁকা, 0, pComment, comment_আকার, uncomp_আকার, comp_আকার, uncomp_crc32, method, 0, dos_time, dos_date, local_dir_header_ofs, ext_attributes))
    ফেরত MZ_FALSE;

  pZip->m_যোগ_files++;
  pZip->m_archive_আকার = cur_archive_file_ofs;

  ফেরত MZ_TRUE;
}
#endif // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_writer_add_from_zip_reader(mz_zip_archive *pZip, mz_zip_archive *pSource_zip, mz_uint file_সূচক)
{
  mz_uint n, bit_flags, অঙ্ক_alignment_padding_bytes;
  mz_uint64 comp_bytes_remaining, local_dir_header_ofs;
  mz_uint64 cur_src_file_ofs, cur_dst_file_ofs;
  mz_uint32 local_header_u32[(MZ_ZIP_LOCAL_DIR_HEADER_আকার + আকার(mz_uint32) - 1) / আকার(mz_uint32)]; mz_uint8 *pLocal_header = (mz_uint8 *)local_header_u32;
  mz_uint8 central_header[MZ_ZIP_CENTRAL_DIR_HEADER_আকার];
  size_t orig_central_dir_আকার;
  mz_zip_internal_state *pState;
  শূন্য *pBuf; ধ্রুবক mz_uint8 *pSrc_central_header;

  যদি ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_mode != MZ_ZIP_MODE_WRITING))
    ফেরত MZ_FALSE;
  যদি (ফাঁকা == (pSrc_central_header = mz_zip_reader_get_cdh(pSource_zip, file_সূচক)))
    ফেরত MZ_FALSE;
  pState = pZip->m_pState;

  অঙ্ক_alignment_padding_bytes = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  যদি ((pZip->m_যোগ_files == 0xFFFF) || ((pZip->m_archive_আকার + অঙ্ক_alignment_padding_bytes + MZ_ZIP_LOCAL_DIR_HEADER_আকার + MZ_ZIP_CENTRAL_DIR_HEADER_আকার) > 0xFFFFFFFF))
    ফেরত MZ_FALSE;

  cur_src_file_ofs = MZ_READ_LE32(pSrc_central_header + MZ_ZIP_CDH_LOCAL_HEADER_OFS);
  cur_dst_file_ofs = pZip->m_archive_আকার;

  যদি (pSource_zip->m_pRead(pSource_zip->m_pIO_opaque, cur_src_file_ofs, pLocal_header, MZ_ZIP_LOCAL_DIR_HEADER_আকার) != MZ_ZIP_LOCAL_DIR_HEADER_আকার)
    ফেরত MZ_FALSE;
  যদি (MZ_READ_LE32(pLocal_header) != MZ_ZIP_LOCAL_DIR_HEADER_SIG)
    ফেরত MZ_FALSE;
  cur_src_file_ofs += MZ_ZIP_LOCAL_DIR_HEADER_আকার;

  যদি (!mz_zip_writer_write_zeros(pZip, cur_dst_file_ofs, অঙ্ক_alignment_padding_bytes))
    ফেরত MZ_FALSE;
  cur_dst_file_ofs += অঙ্ক_alignment_padding_bytes;
  local_dir_header_ofs = cur_dst_file_ofs;
  যদি (pZip->m_file_offset_alignment) { MZ_ASSERT((local_dir_header_ofs & (pZip->m_file_offset_alignment - 1)) == 0); }

  যদি (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, pLocal_header, MZ_ZIP_LOCAL_DIR_HEADER_আকার) != MZ_ZIP_LOCAL_DIR_HEADER_আকার)
    ফেরত MZ_FALSE;
  cur_dst_file_ofs += MZ_ZIP_LOCAL_DIR_HEADER_আকার;

  n = MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  comp_bytes_remaining = n + MZ_READ_LE32(pSrc_central_header + MZ_ZIP_CDH_COMPRESSED_আকার_OFS);

  যদি (ফাঁকা == (pBuf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)MZ_MAX(আকার(mz_uint32) * 4, MZ_MIN(MZ_ZIP_MAX_IO_BUF_আকার, comp_bytes_remaining)))))
    ফেরত MZ_FALSE;

  যখন (comp_bytes_remaining)
  {
    n = (mz_uint)MZ_MIN(MZ_ZIP_MAX_IO_BUF_আকার, comp_bytes_remaining);
    যদি (pSource_zip->m_pRead(pSource_zip->m_pIO_opaque, cur_src_file_ofs, pBuf, n) != n)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      ফেরত MZ_FALSE;
    }
    cur_src_file_ofs += n;

    যদি (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, pBuf, n) != n)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      ফেরত MZ_FALSE;
    }
    cur_dst_file_ofs += n;

    comp_bytes_remaining -= n;
  }

  bit_flags = MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_BIT_FLAG_OFS);
  যদি (bit_flags & 8)
  {
    // Copy data descriptor
    যদি (pSource_zip->m_pRead(pSource_zip->m_pIO_opaque, cur_src_file_ofs, pBuf, আকার(mz_uint32) * 4) != আকার(mz_uint32) * 4)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      ফেরত MZ_FALSE;
    }

    n = আকার(mz_uint32) * ((MZ_READ_LE32(pBuf) == 0x08074b50) ? 4 : 3);
    যদি (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, pBuf, n) != n)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      ফেরত MZ_FALSE;
    }

    cur_src_file_ofs += n;
    cur_dst_file_ofs += n;
  }
  pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);

  // no zip64 support yet
  যদি (cur_dst_file_ofs > 0xFFFFFFFF)
    ফেরত MZ_FALSE;

  orig_central_dir_আকার = pState->m_central_dir.m_আকার;

  memcpy(central_header, pSrc_central_header, MZ_ZIP_CENTRAL_DIR_HEADER_আকার);
  MZ_WRITE_LE32(central_header + MZ_ZIP_CDH_LOCAL_HEADER_OFS, local_dir_header_ofs);
  যদি (!mz_zip_array_ঠেলো_back(pZip, &pState->m_central_dir, central_header, MZ_ZIP_CENTRAL_DIR_HEADER_আকার))
    ফেরত MZ_FALSE;

  n = MZ_READ_LE16(pSrc_central_header + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(pSrc_central_header + MZ_ZIP_CDH_EXTRA_LEN_OFS) + MZ_READ_LE16(pSrc_central_header + MZ_ZIP_CDH_COMMENT_LEN_OFS);
  যদি (!mz_zip_array_ঠেলো_back(pZip, &pState->m_central_dir, pSrc_central_header + MZ_ZIP_CENTRAL_DIR_HEADER_আকার, n))
  {
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_আকার, MZ_FALSE);
    ফেরত MZ_FALSE;
  }

  যদি (pState->m_central_dir.m_আকার > 0xFFFFFFFF)
    ফেরত MZ_FALSE;
  n = (mz_uint32)orig_central_dir_আকার;
  যদি (!mz_zip_array_ঠেলো_back(pZip, &pState->m_central_dir_offsets, &n, 1))
  {
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_আকার, MZ_FALSE);
    ফেরত MZ_FALSE;
  }

  pZip->m_যোগ_files++;
  pZip->m_archive_আকার = cur_dst_file_ofs;

  ফেরত MZ_TRUE;
}

mz_bool mz_zip_writer_finalize_archive(mz_zip_archive *pZip)
{
  mz_zip_internal_state *pState;
  mz_uint64 central_dir_ofs, central_dir_আকার;
  mz_uint8 hdr[MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_আকার];

  যদি ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_mode != MZ_ZIP_MODE_WRITING))
    ফেরত MZ_FALSE;

  pState = pZip->m_pState;

  // no zip64 support yet
  যদি ((pZip->m_যোগ_files > 0xFFFF) || ((pZip->m_archive_আকার + pState->m_central_dir.m_আকার + MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_আকার) > 0xFFFFFFFF))
    ফেরত MZ_FALSE;

  central_dir_ofs = 0;
  central_dir_আকার = 0;
  যদি (pZip->m_যোগ_files)
  {
    // Write central directory
    central_dir_ofs = pZip->m_archive_আকার;
    central_dir_আকার = pState->m_central_dir.m_আকার;
    pZip->m_central_directory_file_ofs = central_dir_ofs;
    যদি (pZip->m_pWrite(pZip->m_pIO_opaque, central_dir_ofs, pState->m_central_dir.m_p, (size_t)central_dir_আকার) != central_dir_আকার)
      ফেরত MZ_FALSE;
    pZip->m_archive_আকার += central_dir_আকার;
  }

  // Write end of central directory record
  MZ_CLEAR_ARR(hdr);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_SIG_OFS, MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIG);
  MZ_WRITE_LE16(hdr + MZ_ZIP_ECDH_CDIR_অঙ্ক_ENTRIES_ON_DISK_OFS, pZip->m_যোগ_files);
  MZ_WRITE_LE16(hdr + MZ_ZIP_ECDH_CDIR_যোগ_ENTRIES_OFS, pZip->m_যোগ_files);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_CDIR_আকার_OFS, central_dir_আকার);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_CDIR_OFS_OFS, central_dir_ofs);

  যদি (pZip->m_pWrite(pZip->m_pIO_opaque, pZip->m_archive_আকার, hdr, আকার(hdr)) != আকার(hdr))
    ফেরত MZ_FALSE;
#ifndef MINIZ_NO_STDIO
  যদি ((pState->m_pFile) && (MZ_FFLUSH(pState->m_pFile) == EOF))
    ফেরত MZ_FALSE;
#endif // #ifndef MINIZ_NO_STDIO

  pZip->m_archive_আকার += আকার(hdr);

  pZip->m_zip_mode = MZ_ZIP_MODE_WRITING_HAS_BEEN_FINALIZED;
  ফেরত MZ_TRUE;
}

mz_bool mz_zip_writer_finalize_heap_archive(mz_zip_archive *pZip, শূন্য **pBuf, size_t *p_আকার)
{
  যদি ((!pZip) || (!pZip->m_pState) || (!pBuf) || (!p_আকার))
    ফেরত MZ_FALSE;
  যদি (pZip->m_pWrite != mz_zip_heap_write_func)
    ফেরত MZ_FALSE;
  যদি (!mz_zip_writer_finalize_archive(pZip))
    ফেরত MZ_FALSE;

  *pBuf = pZip->m_pState->m_pMem;
  *p_আকার = pZip->m_pState->m_mem_আকার;
  pZip->m_pState->m_pMem = ফাঁকা;
  pZip->m_pState->m_mem_আকার = pZip->m_pState->m_mem_capacity = 0;
  ফেরত MZ_TRUE;
}

mz_bool mz_zip_writer_end(mz_zip_archive *pZip)
{
  mz_zip_internal_state *pState;
  mz_bool status = MZ_TRUE;
  যদি ((!pZip) || (!pZip->m_pState) || (!pZip->m_pAlloc) || (!pZip->m_pFree) || ((pZip->m_zip_mode != MZ_ZIP_MODE_WRITING) && (pZip->m_zip_mode != MZ_ZIP_MODE_WRITING_HAS_BEEN_FINALIZED)))
    ফেরত MZ_FALSE;

  pState = pZip->m_pState;
  pZip->m_pState = ফাঁকা;
  mz_zip_array_clear(pZip, &pState->m_central_dir);
  mz_zip_array_clear(pZip, &pState->m_central_dir_offsets);
  mz_zip_array_clear(pZip, &pState->m_sorted_central_dir_offsets);

#ifndef MINIZ_NO_STDIO
  যদি (pState->m_pFile)
  {
    MZ_FCLOSE(pState->m_pFile);
    pState->m_pFile = ফাঁকা;
  }
#endif // #ifndef MINIZ_NO_STDIO

  যদি ((pZip->m_pWrite == mz_zip_heap_write_func) && (pState->m_pMem))
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pState->m_pMem);
    pState->m_pMem = ফাঁকা;
  }

  pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
  pZip->m_zip_mode = MZ_ZIP_MODE_INVALID;
  ফেরত status;
}

#ifndef MINIZ_NO_STDIO
mz_bool mz_zip_add_mem_to_archive_file_in_place(ধ্রুবক অক্ষর *pZip_filename, ধ্রুবক অক্ষর *pArchive_name, ধ্রুবক শূন্য *pBuf, size_t buf_আকার_2, ধ্রুবক শূন্য *pComment, mz_uint16 comment_আকার, mz_uint level_and_flags)
{
  mz_bool status, created_new_archive = MZ_FALSE;
  mz_zip_archive zip_archive;
  কাঠামো MZ_FILE_STAT_STRUCT file_stat;
  MZ_CLEAR_OBJ(zip_archive);
  যদি ((পূর্ণসংখ্যা)level_and_flags < 0)
     level_and_flags = MZ_DEFAULT_LEVEL;
  যদি ((!pZip_filename) || (!pArchive_name) || ((buf_আকার_2) && (!pBuf)) || ((comment_আকার) && (!pComment)) || ((level_and_flags & 0xF) > MZ_UBER_COMPRESSION))
    ফেরত MZ_FALSE;
  যদি (!mz_zip_writer_validate_archive_name(pArchive_name))
    ফেরত MZ_FALSE;
  যদি (MZ_FILE_STAT(pZip_filename, &file_stat) != 0)
  {
    // Create a new archive.
    যদি (!mz_zip_writer_init_file(&zip_archive, pZip_filename, 0))
      ফেরত MZ_FALSE;
    created_new_archive = MZ_TRUE;
  }
  অন্যথা
  {
    // Append to an existing archive.
    যদি (!mz_zip_reader_init_file(&zip_archive, pZip_filename, level_and_flags | MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY))
      ফেরত MZ_FALSE;
    যদি (!mz_zip_writer_init_from_reader(&zip_archive, pZip_filename))
    {
      mz_zip_reader_end(&zip_archive);
      ফেরত MZ_FALSE;
    }
  }
  status = mz_zip_writer_add_mem_ex(&zip_archive, pArchive_name, pBuf, buf_আকার_2, pComment, comment_আকার, level_and_flags, 0, 0);
  // Always finalize, even if adding failed for some reason, so we have a valid central directory. (This may not always succeed, but we can try.)
  যদি (!mz_zip_writer_finalize_archive(&zip_archive))
    status = MZ_FALSE;
  যদি (!mz_zip_writer_end(&zip_archive))
    status = MZ_FALSE;
  যদি ((!status) && (created_new_archive))
  {
    // It's a new archive and something went wrong, so just delete it.
    পূর্ণসংখ্যা ignoredStatus = MZ_DELETE_FILE(pZip_filename);
    (শূন্য)ignoredStatus;
  }
  ফেরত status;
}

শূন্য *mz_zip_extract_archive_file_to_heap(ধ্রুবক অক্ষর *pZip_filename, ধ্রুবক অক্ষর *pArchive_name, size_t *p_আকার, mz_uint flags)
{
  পূর্ণসংখ্যা file_সূচক;
  mz_zip_archive zip_archive;
  শূন্য *p = ফাঁকা;

  যদি (p_আকার)
    *p_আকার = 0;

  যদি ((!pZip_filename) || (!pArchive_name))
    ফেরত ফাঁকা;

  MZ_CLEAR_OBJ(zip_archive);
  যদি (!mz_zip_reader_init_file(&zip_archive, pZip_filename, flags | MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY))
    ফেরত ফাঁকা;

  যদি ((file_সূচক = mz_zip_reader_locate_file(&zip_archive, pArchive_name, ফাঁকা, flags)) >= 0)
    p = mz_zip_reader_extract_to_heap(&zip_archive, file_সূচক, p_আকার, flags);

  mz_zip_reader_end(&zip_archive);
  ফেরত p;
}

#endif // #ifndef MINIZ_NO_STDIO

#endif // #ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

#endif // #ifndef MINIZ_NO_ARCHIVE_APIS

#ifdef __cplusplus
}
#endif

#ifdef _MSC_VER
#pragma warning (বের_করো)
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

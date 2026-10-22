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

#જો defined(__TINYC__) && (defined(__linux) || defined(__linux__))
  // TODO: Work around "error: include file 'sys\utime.h' when compiling with tcc on Linux
  #define MINIZ_NO_TIME
#endif

#જો !defined(MINIZ_NO_TIME) && !defined(MINIZ_NO_ARCHIVE_APIS)
  #અન્તર્ભાવ <time.h>
#endif

#જો defined(_M_IX86) || defined(_M_X64) || defined(__i386__) || defined(__i386) || defined(__i486__) || defined(__i486) || defined(i386) || defined(__ia64__) || defined(__x86_64__)
// MINIZ_X86_OR_X64_CPU is only used to help set the below macros.
#define MINIZ_X86_OR_X64_CPU 1
#endif

#ifndef MINIZ_LITTLE_ENDIAN /* if not defined by SDL */
#જો (__BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__) || MINIZ_X86_OR_X64_CPU
// Set MINIZ_LITTLE_ENDIAN to 1 if the processor is little endian.
#define MINIZ_LITTLE_ENDIAN 1
#endif
#endif // MINIZ_LITTLE_ENDIAN /* if not defined by SDL */

#ifndef MINIZ_USE_UNALIGNED_LOADS_AND_STORES
#જો MINIZ_X86_OR_X64_CPU
// Set MINIZ_USE_UNALIGNED_LOADS_AND_STORES to 1 on CPU's that permit efficient integer loads and stores from unaligned addresses.
#define MINIZ_USE_UNALIGNED_LOADS_AND_STORES 1
#endif
#endif // MINIZ_USE_UNALIGNED_LOADS_AND_STORES

#જો defined(_M_X64) || defined(_WIN64) || defined(__MINGW64__) || defined(_LP64) || defined(__LP64__) || defined(__ia64__) || defined(__x86_64__)
// Set MINIZ_HAS_64BIT_REGISTERS to 1 if operations on 64-bit integers are reasonably fast (and don't involve compiler generated calls to helper functions).
#define MINIZ_HAS_64BIT_REGISTERS 1
#endif

#ifdef MINIZ_STATIC_FUNCTIONS
#define MINIZ_STATIC સ્થિર
#નહીંતર
#define MINIZ_STATIC
#endif

#ifdef __cplusplus
બાહ્ય "C" {
#endif

// ------------------- zlib-style API Definitions.

// For more compatibility with zlib, miniz.c uses unsigned long for some parameters/struct members. Beware: mz_ulong can be either 32 or 64-bits!
પ્રકારવ્યાખ્યા unsigned long mz_ulong;

// mz_free() internally uses the MZ_FREE() macro (which by default calls free() unless you've modified the MZ_MALLOC macro) to release a block allocated from the heap.
MINIZ_STATIC શૂન્ય mz_free(શૂન્ય *p);

#define MZ_ADLER32_INIT (1)
// mz_adler32() returns the initial adler-32 value to use when called with ptr==NULL.
MINIZ_STATIC mz_ulong mz_adler32(mz_ulong adler, અચલ unsigned અક્ષર *ptr, size_t buf_len);

#define MZ_CRC32_INIT (0)
// mz_crc32() returns the initial CRC-32 value to use when called with ptr==NULL.
MINIZ_STATIC mz_ulong mz_crc32(mz_ulong crc, અચલ unsigned અક્ષર *ptr, size_t buf_len);

// Compression strategies.
ગણના { MZ_DEFAULT_STRATEGY = 0, MZ_FILTERED = 1, MZ_HUFFMAN_ONLY = 2, MZ_RLE = 3, MZ_FIXED = 4 };

// Method
#define MZ_DEFLATED 8

#ifndef MINIZ_NO_ZLIB_APIS

// Heap allocation callbacks.
// Note that mz_alloc_func parameter types purpsosely differ from zlib's: items/size is size_t, not unsigned long.
પ્રકારવ્યાખ્યા શૂન્ય *(*mz_alloc_func)(શૂન્ય *opaque, size_t વસ્તુઓ, size_t size);
પ્રકારવ્યાખ્યા શૂન્ય (*mz_free_func)(શૂન્ય *opaque, શૂન્ય *address);
પ્રકારવ્યાખ્યા શૂન્ય *(*mz_realloc_func)(શૂન્ય *opaque, શૂન્ય *address, size_t વસ્તુઓ, size_t size);

#define MZ_VERSION          "9.1.15"
#define MZ_VERNUM           0x91F0
#define MZ_VER_MAJOR        9
#define MZ_VER_MINOR        1
#define MZ_VER_REVISION     15
#define MZ_VER_SUBREVISION  0

// Flush values. For typical usage you only need MZ_NO_FLUSH and MZ_FINISH. The other values are for advanced use (refer to the zlib docs).
ગણના { MZ_NO_FLUSH = 0, MZ_PARTIAL_FLUSH = 1, MZ_SYNC_FLUSH = 2, MZ_FULL_FLUSH = 3, MZ_FINISH = 4, MZ_BLOCK = 5 };

// Return status codes. MZ_PARAM_ERROR is non-standard.
ગણના { MZ_OK = 0, MZ_STREAM_END = 1, MZ_NEED_DICT = 2, MZ_ERRNO = -1, MZ_STREAM_ERROR = -2, MZ_DATA_ERROR = -3, MZ_MEM_ERROR = -4, MZ_BUF_ERROR = -5, MZ_VERSION_ERROR = -6, MZ_PARAM_ERROR = -10000 };

// Compression levels: 0-9 are the standard zlib-style levels, 10 is best possible compression (not zlib compatible, and may be very slow), MZ_DEFAULT_COMPRESSION=MZ_DEFAULT_LEVEL.
ગણના { MZ_NO_COMPRESSION = 0, MZ_BEST_SPEED = 1, MZ_BEST_COMPRESSION = 9, MZ_UBER_COMPRESSION = 10, MZ_DEFAULT_LEVEL = 6, MZ_DEFAULT_COMPRESSION = -1 };

// Window bits
#define MZ_DEFAULT_WINDOW_BITS 15

સંરચના mz_internal_state;

// Compression/decompression stream struct.
પ્રકારવ્યાખ્યા સંરચના mz_stream_s
{
  અચલ unsigned અક્ષર *next_in;     // pointer to next byte to read
  unsigned પૂર્ણાંક avail_in;            // number of bytes available at next_in
  mz_ulong total_in;                // total number of bytes consumed so far

  unsigned અક્ષર *next_out;          // pointer to next byte to write
  unsigned પૂર્ણાંક avail_out;           // number of bytes that can be written to next_out
  mz_ulong total_out;               // total number of bytes produced so far

  અક્ષર *સંદેશ;                        // error msg (unused)
  સંરચના mz_internal_state *state;  // internal state, allocated by zalloc/zfree

  mz_alloc_func zalloc;             // optional heap allocation function (defaults to malloc)
  mz_free_func zfree;               // optional heap free function (defaults to free)
  શૂન્ય *opaque;                     // heap alloc function user pointer

  પૂર્ણાંક data_type;                    // data_type (unused)
  mz_ulong adler;                   // adler32 of the source or uncompressed data
  mz_ulong reserved;                // not used
} mz_stream;

પ્રકારવ્યાખ્યા mz_stream *mz_streamp;

// Returns the version string of miniz.c.
MINIZ_STATIC અચલ અક્ષર *mz_version(શૂન્ય);

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
MINIZ_STATIC પૂર્ણાંક mz_deflateInit(mz_streamp pStream, પૂર્ણાંક level);

// mz_deflateInit2() is like mz_deflate(), except with more control:
// Additional parameters:
//   method must be MZ_DEFLATED
//   window_bits must be MZ_DEFAULT_WINDOW_BITS (to wrap the deflate stream with zlib header/adler-32 footer) or -MZ_DEFAULT_WINDOW_BITS (raw deflate/no header or footer)
//   mem_level must be between [1, 9] (it's checked but ignored by miniz.c)
MINIZ_STATIC પૂર્ણાંક mz_deflateInit2(mz_streamp pStream, પૂર્ણાંક level, પૂર્ણાંક method, પૂર્ણાંક window_bits, પૂર્ણાંક mem_level, પૂર્ણાંક strategy);

// Quickly resets a compressor without having to reallocate anything. Same as calling mz_deflateEnd() followed by mz_deflateInit()/mz_deflateInit2().
MINIZ_STATIC પૂર્ણાંક mz_deflateReset(mz_streamp pStream);

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
MINIZ_STATIC પૂર્ણાંક mz_deflate(mz_streamp pStream, પૂર્ણાંક flush);

// mz_deflateEnd() deinitializes a compressor:
// Return values:
//  MZ_OK on success.
//  MZ_STREAM_ERROR if the stream is bogus.
MINIZ_STATIC પૂર્ણાંક mz_deflateEnd(mz_streamp pStream);

// mz_deflateBound() returns a (very) conservative upper bound on the amount of data that could be generated by deflate(), assuming flush is set to only MZ_NO_FLUSH or MZ_FINISH.
MINIZ_STATIC mz_ulong mz_deflateBound(mz_streamp pStream, mz_ulong source_len);

// Single-call compression functions mz_compress() and mz_compress2():
// Returns MZ_OK on success, or one of the error codes from mz_deflate() on failure.
MINIZ_STATIC પૂર્ણાંક mz_compress(unsigned અક્ષર *pDest, mz_ulong *pDest_len, અચલ unsigned અક્ષર *pSource, mz_ulong source_len);
MINIZ_STATIC પૂર્ણાંક mz_compress2(unsigned અક્ષર *pDest, mz_ulong *pDest_len, અચલ unsigned અક્ષર *pSource, mz_ulong source_len, પૂર્ણાંક level);

// mz_compressBound() returns a (very) conservative upper bound on the amount of data that could be generated by calling mz_compress().
MINIZ_STATIC mz_ulong mz_compressBound(mz_ulong source_len);

#endif /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#ifndef MINIZ_NO_INFLATE_APIS

// Initializes a decompressor.
MINIZ_STATIC પૂર્ણાંક mz_inflateInit(mz_streamp pStream);

// mz_inflateInit2() is like mz_inflateInit() with an additional option that controls the window size and whether or not the stream has been wrapped with a zlib header/footer:
// window_bits must be MZ_DEFAULT_WINDOW_BITS (to parse zlib header/footer) or -MZ_DEFAULT_WINDOW_BITS (raw deflate).
MINIZ_STATIC પૂર્ણાંક mz_inflateInit2(mz_streamp pStream, પૂર્ણાંક window_bits);

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
MINIZ_STATIC પૂર્ણાંક mz_inflate(mz_streamp pStream, પૂર્ણાંક flush);

// Deinitializes a decompressor.
MINIZ_STATIC પૂર્ણાંક mz_inflateEnd(mz_streamp pStream);

// Single-call decompression.
// Returns MZ_OK on success, or one of the error codes from mz_inflate() on failure.
MINIZ_STATIC પૂર્ણાંક mz_uncompress(unsigned અક્ષર *pDest, mz_ulong *pDest_len, અચલ unsigned અક્ષર *pSource, mz_ulong source_len);
#endif /*#ifndef MINIZ_NO_INFLATE_APIS*/

// Returns a string description of the specified error code, or NULL if the error code is invalid.
MINIZ_STATIC અચલ અક્ષર *mz_error(પૂર્ણાંક err);

// Redefine zlib-compatible names to miniz equivalents, so miniz.c can be used as a drop-in replacement for the subset of zlib that miniz.c supports.
// Define MINIZ_NO_ZLIB_COMPATIBLE_NAMES to disable zlib-compatibility if you use zlib in the same project.
#ifndef MINIZ_NO_ZLIB_COMPATIBLE_NAMES
  પ્રકારવ્યાખ્યા unsigned અક્ષર Byte;
  પ્રકારવ્યાખ્યા unsigned પૂર્ણાંક uInt;
  પ્રકારવ્યાખ્યા mz_ulong uLong;
  પ્રકારવ્યાખ્યા Byte Bytef;
  પ્રકારવ્યાખ્યા uInt uIntf;
  પ્રકારવ્યાખ્યા અક્ષર charf;
  પ્રકારવ્યાખ્યા પૂર્ણાંક intf;
  પ્રકારવ્યાખ્યા શૂન્ય *voidpf;
  પ્રકારવ્યાખ્યા uLong uLongf;
  પ્રકારવ્યાખ્યા શૂન્ય *voidp;
  પ્રકારવ્યાખ્યા શૂન્ય *અચલ voidpc;
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

પ્રકારવ્યાખ્યા unsigned અક્ષર mz_uint8;
પ્રકારવ્યાખ્યા signed short mz_int16;
પ્રકારવ્યાખ્યા unsigned short mz_uint16;
પ્રકારવ્યાખ્યા unsigned પૂર્ણાંક mz_uint32;
પ્રકારવ્યાખ્યા unsigned પૂર્ણાંક mz_uint;
પ્રકારવ્યાખ્યા long long mz_int64;
પ્રકારવ્યાખ્યા unsigned long long mz_uint64;
પ્રકારવ્યાખ્યા પૂર્ણાંક mz_bool;

#define MZ_FALSE (0)
#define MZ_TRUE (1)

// An attempt to work around MSVC's spammy "warning C4127: conditional expression is constant" message.
#ifdef _MSC_VER
   #define MZ_MACRO_END જ્યારે (0, 0)
#નહીંતર
   #define MZ_MACRO_END જ્યારે (0)
#endif

// ------------------- ZIP archive reading/writing

#ifndef MINIZ_NO_ARCHIVE_APIS

ગણના
{
  MZ_ZIP_MAX_IO_BUF_SIZE = 64*1024,
  MZ_ZIP_MAX_ARCHIVE_FILENAME_SIZE = 260,
  MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_SIZE = 256
};

પ્રકારવ્યાખ્યા સંરચના
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
  અક્ષર m_filename[MZ_ZIP_MAX_ARCHIVE_FILENAME_SIZE];
  અક્ષર m_comment[MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_SIZE];
} mz_zip_archive_file_stat;

પ્રકારવ્યાખ્યા size_t (*mz_file_read_func)(શૂન્ય *pOpaque, mz_uint64 file_ofs, શૂન્ય *pBuf, size_t n);
પ્રકારવ્યાખ્યા size_t (*mz_file_write_func)(શૂન્ય *pOpaque, mz_uint64 file_ofs, અચલ શૂન્ય *pBuf, size_t n);

સંરચના mz_zip_internal_state_tag;
પ્રકારવ્યાખ્યા સંરચના mz_zip_internal_state_tag mz_zip_internal_state;

પ્રકારવ્યાખ્યા ગણના
{
  MZ_ZIP_MODE_INVALID = 0,
  MZ_ZIP_MODE_READING = 1,
  MZ_ZIP_MODE_WRITING = 2,
  MZ_ZIP_MODE_WRITING_HAS_BEEN_FINALIZED = 3
} mz_zip_mode;

પ્રકારવ્યાખ્યા સંરચના mz_zip_archive_tag
{
  mz_uint64 m_archive_size;
  mz_uint64 m_central_directory_file_ofs;
  mz_uint m_total_files;
  mz_zip_mode m_zip_mode;

  mz_uint m_file_offset_alignment;

  mz_alloc_func m_pAlloc;
  mz_free_func m_pFree;
  mz_realloc_func m_pRealloc;
  શૂન્ય *m_pAlloc_opaque;

  mz_file_read_func m_pRead;
  mz_file_write_func m_pWrite;
  શૂન્ય *m_pIO_opaque;

  mz_zip_internal_state *m_pState;

} mz_zip_archive;

પ્રકારવ્યાખ્યા ગણના
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
MINIZ_STATIC mz_bool mz_zip_reader_init_mem(mz_zip_archive *pZip, અચલ શૂન્ય *pMem, size_t size, mz_uint32 flags);

#ifndef MINIZ_NO_STDIO
MINIZ_STATIC mz_bool mz_zip_reader_init_file(mz_zip_archive *pZip, અચલ અક્ષર *pFilename, mz_uint32 flags);
#endif

// Returns the total number of files in the archive.
MINIZ_STATIC mz_uint mz_zip_reader_get_અંક_files(mz_zip_archive *pZip);

// Returns detailed information about an archive file entry.
MINIZ_STATIC mz_bool mz_zip_reader_file_stat(mz_zip_archive *pZip, mz_uint file_index, mz_zip_archive_file_stat *pStat);

// Determines if an archive file entry is a directory entry.
MINIZ_STATIC mz_bool mz_zip_reader_is_file_a_directory(mz_zip_archive *pZip, mz_uint file_index);
MINIZ_STATIC mz_bool mz_zip_reader_is_file_encrypted(mz_zip_archive *pZip, mz_uint file_index);

// Retrieves the filename of an archive file entry.
// Returns the number of bytes written to pFilename, or if filename_buf_size is 0 this function returns the number of bytes needed to fully store the filename.
MINIZ_STATIC mz_uint mz_zip_reader_get_filename(mz_zip_archive *pZip, mz_uint file_index, અક્ષર *pFilename, mz_uint filename_buf_size);

// Attempts to locates a file in the archive's central directory.
// Valid flags: MZ_ZIP_FLAG_CASE_SENSITIVE, MZ_ZIP_FLAG_IGNORE_PATH
// Returns -1 if the file cannot be found.
MINIZ_STATIC પૂર્ણાંક mz_zip_reader_locate_file(mz_zip_archive *pZip, અચલ અક્ષર *pName, અચલ અક્ષર *pComment, mz_uint flags);

// Extracts a archive file to a memory buffer using no memory allocation.
MINIZ_STATIC mz_bool mz_zip_reader_extract_to_mem_no_alloc(mz_zip_archive *pZip, mz_uint file_index, શૂન્ય *pBuf, size_t buf_size, mz_uint flags, શૂન્ય *pUser_read_buf, size_t user_read_buf_size);
MINIZ_STATIC mz_bool mz_zip_reader_extract_file_to_mem_no_alloc(mz_zip_archive *pZip, અચલ અક્ષર *pFilename, શૂન્ય *pBuf, size_t buf_size, mz_uint flags, શૂન્ય *pUser_read_buf, size_t user_read_buf_size);

// Extracts a archive file to a memory buffer.
MINIZ_STATIC mz_bool mz_zip_reader_extract_to_mem(mz_zip_archive *pZip, mz_uint file_index, શૂન્ય *pBuf, size_t buf_size, mz_uint flags);
MINIZ_STATIC mz_bool mz_zip_reader_extract_file_to_mem(mz_zip_archive *pZip, અચલ અક્ષર *pFilename, શૂન્ય *pBuf, size_t buf_size, mz_uint flags);

// Extracts a archive file to a dynamically allocated heap buffer.
MINIZ_STATIC શૂન્ય *mz_zip_reader_extract_to_heap(mz_zip_archive *pZip, mz_uint file_index, size_t *pSize, mz_uint flags);
MINIZ_STATIC શૂન્ય *mz_zip_reader_extract_file_to_heap(mz_zip_archive *pZip, અચલ અક્ષર *pFilename, size_t *pSize, mz_uint flags);

// Extracts a archive file using a callback function to output the file's data.
MINIZ_STATIC mz_bool mz_zip_reader_extract_to_callback(mz_zip_archive *pZip, mz_uint file_index, mz_file_write_func pCallback, શૂન્ય *pOpaque, mz_uint flags);
MINIZ_STATIC mz_bool mz_zip_reader_extract_file_to_callback(mz_zip_archive *pZip, અચલ અક્ષર *pFilename, mz_file_write_func pCallback, શૂન્ય *pOpaque, mz_uint flags);

#ifndef MINIZ_NO_STDIO
// Extracts a archive file to a disk file and sets its last accessed and modified times.
// This function only extracts files, not archive directory records.
MINIZ_STATIC mz_bool mz_zip_reader_extract_to_file(mz_zip_archive *pZip, mz_uint file_index, અચલ અક્ષર *pDst_filename, mz_uint flags);
MINIZ_STATIC mz_bool mz_zip_reader_extract_file_to_file(mz_zip_archive *pZip, અચલ અક્ષર *pArchive_filename, અચલ અક્ષર *pDst_filename, mz_uint flags);
#endif

// Ends archive reading, freeing all allocations, and closing the input archive file if mz_zip_reader_init_file() was used.
MINIZ_STATIC mz_bool mz_zip_reader_end(mz_zip_archive *pZip);

// ZIP archive writing

#ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

// Inits a ZIP archive writer.
MINIZ_STATIC mz_bool mz_zip_writer_init(mz_zip_archive *pZip, mz_uint64 existing_size);
MINIZ_STATIC mz_bool mz_zip_writer_init_heap(mz_zip_archive *pZip, size_t size_to_reserve_at_beginning, size_t initial_allocation_size);

#ifndef MINIZ_NO_STDIO
MINIZ_STATIC mz_bool mz_zip_writer_init_file(mz_zip_archive *pZip, અચલ અક્ષર *pFilename, mz_uint64 size_to_reserve_at_beginning);
#endif

// Converts a ZIP archive reader object into a writer object, to allow efficient in-place file appends to occur on an existing archive.
// For archives opened using mz_zip_reader_init_file, pFilename must be the archive's filename so it can be reopened for writing. If the file can't be reopened, mz_zip_reader_end() will be called.
// For archives opened using mz_zip_reader_init_mem, the memory block must be growable using the realloc callback (which defaults to realloc unless you've overridden it).
// Finally, for archives opened using mz_zip_reader_init, the mz_zip_archive's user provided m_pWrite function cannot be NULL.
// Note: In-place archive modification is not recommended unless you know what you're doing, because if execution stops or something goes wrong before
// the archive is finalized the file's central directory will be hosed.
MINIZ_STATIC mz_bool mz_zip_writer_init_from_reader(mz_zip_archive *pZip, અચલ અક્ષર *pFilename);

// Adds the contents of a memory buffer to an archive. These functions record the current local time into the archive.
// To add a directory entry, call this method with an archive name ending in a forwardslash with empty buffer.
// level_and_flags - compression level (0-10, see MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or just set to MZ_DEFAULT_COMPRESSION.
MINIZ_STATIC mz_bool mz_zip_writer_add_mem(mz_zip_archive *pZip, અચલ અક્ષર *pArchive_name, અચલ શૂન્ય *pBuf, size_t buf_size, mz_uint level_and_flags);
MINIZ_STATIC mz_bool mz_zip_writer_add_mem_ex(mz_zip_archive *pZip, અચલ અક્ષર *pArchive_name, અચલ શૂન્ય *pBuf, size_t buf_size, અચલ શૂન્ય *pComment, mz_uint16 comment_size, mz_uint level_and_flags, mz_uint64 uncomp_size, mz_uint32 uncomp_crc32);

#ifndef MINIZ_NO_STDIO
// Adds the contents of a disk file to an archive. This function also records the disk file's modified time into the archive.
// level_and_flags - compression level (0-10, see MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or just set to MZ_DEFAULT_COMPRESSION.
MINIZ_STATIC mz_bool mz_zip_writer_add_file(mz_zip_archive *pZip, અચલ અક્ષર *pArchive_name, અચલ અક્ષર *pSrc_filename, અચલ શૂન્ય *pComment, mz_uint16 comment_size, mz_uint level_and_flags);
#endif

// Adds a file to an archive by fully cloning the data from another archive.
// This function fully clones the source file's compressed data (no recompression), along with its full filename, extra data, and comment fields.
MINIZ_STATIC mz_bool mz_zip_writer_add_from_zip_reader(mz_zip_archive *pZip, mz_zip_archive *pSource_zip, mz_uint file_index);

// Finalizes the archive by writing the central directory records followed by the end of central directory record.
// After an archive is finalized, the only valid call on the mz_zip_archive struct is mz_zip_writer_end().
// An archive must be manually finalized by calling this function for it to be valid.
MINIZ_STATIC mz_bool mz_zip_writer_finalize_archive(mz_zip_archive *pZip);
MINIZ_STATIC mz_bool mz_zip_writer_finalize_heap_archive(mz_zip_archive *pZip, શૂન્ય **pBuf, size_t *pSize);

// Ends archive writing, freeing all allocations, and closing the output file if mz_zip_writer_init_file() was used.
// Note for the archive to be valid, it must have been finalized before ending.
MINIZ_STATIC mz_bool mz_zip_writer_end(mz_zip_archive *pZip);

// Misc. high-level helper functions:

// mz_zip_add_mem_to_archive_file_in_place() efficiently (but not atomically) appends a memory blob to a ZIP archive.
// level_and_flags - compression level (0-10, see MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or just set to MZ_DEFAULT_COMPRESSION.
MINIZ_STATIC mz_bool mz_zip_add_mem_to_archive_file_in_place(અચલ અક્ષર *pZip_filename, અચલ અક્ષર *pArchive_name, અચલ શૂન્ય *pBuf, size_t buf_size, અચલ શૂન્ય *pComment, mz_uint16 comment_size, mz_uint level_and_flags);

// Reads a single file from an archive into a heap block.
// Returns NULL on failure.
MINIZ_STATIC શૂન્ય *mz_zip_extract_archive_file_to_heap(અચલ અક્ષર *pZip_filename, અચલ અક્ષર *pArchive_name, size_t *pSize, mz_uint zip_flags);

#endif // #ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

#endif // #ifndef MINIZ_NO_ARCHIVE_APIS

// ------------------- Low-level Decompression API Definitions
#ifndef MINIZ_NO_INFLATE_APIS

// Decompression flags used by tinfl_decompress().
// TINFL_FLAG_PARSE_ZLIB_HEADER: If set, the input has a valid zlib header and ends with an adler32 checksum (it's a valid zlib stream). Otherwise, the input is a raw deflate stream.
// TINFL_FLAG_HAS_MORE_INPUT: If set, there are more input bytes available beyond the end of the supplied input buffer. If clear, the input buffer contains all remaining input.
// TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF: If set, the output buffer is large enough to hold the entire decompressed stream. If clear, the output buffer is at least the size of the dictionary (typically 32KB).
// TINFL_FLAG_COMPUTE_ADLER32: Force adler-32 checksum computation of the decompressed bytes.
ગણના
{
  TINFL_FLAG_PARSE_ZLIB_HEADER = 1,
  TINFL_FLAG_HAS_MORE_આગત = 2,
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
MINIZ_STATIC શૂન્ય *tinfl_decompress_mem_to_heap(અચલ શૂન્ય *pSrc_buf, size_t src_buf_len, size_t *pOut_len, પૂર્ણાંક flags);

// tinfl_decompress_mem_to_mem() decompresses a block in memory to another block in memory.
// Returns TINFL_DECOMPRESS_MEM_TO_MEM_FAILED on failure, or the number of bytes written on success.
#define TINFL_DECOMPRESS_MEM_TO_MEM_FAILED ((size_t)(-1))
MINIZ_STATIC size_t tinfl_decompress_mem_to_mem(શૂન્ય *pOut_buf, size_t out_buf_len, અચલ શૂન્ય *pSrc_buf, size_t src_buf_len, પૂર્ણાંક flags);

// tinfl_decompress_mem_to_callback() decompresses a block in memory to an internal 32KB buffer, and a user provided callback function will be called to flush the buffer.
// Returns 1 on success or 0 on failure.
પ્રકારવ્યાખ્યા પૂર્ણાંક (*tinfl_put_buf_func_ptr)(અચલ શૂન્ય* pBuf, પૂર્ણાંક len, શૂન્ય *pUser);
MINIZ_STATIC પૂર્ણાંક tinfl_decompress_mem_to_callback(અચલ શૂન્ય *pIn_buf, size_t *pIn_buf_size, tinfl_put_buf_func_ptr pPut_buf_func, શૂન્ય *pPut_buf_user, પૂર્ણાંક flags);

સંરચના tinfl_decompressor_tag; પ્રકારવ્યાખ્યા સંરચના tinfl_decompressor_tag tinfl_decompressor;

// Max size of LZ dictionary.
#define TINFL_LZ_DICT_SIZE 32768

// Return status.
પ્રકારવ્યાખ્યા ગણના
{
  TINFL_STATUS_BAD_PARAM = -3,
  TINFL_STATUS_ADLER32_MISMATCH = -2,
  TINFL_STATUS_FAILED = -1,
  TINFL_STATUS_DONE = 0,
  TINFL_STATUS_NEEDS_MORE_આગત = 1,
  TINFL_STATUS_HAS_MORE_OUTPUT = 2
} tinfl_status;

// Initializes the decompressor to its initial state.
#define tinfl_init(r) કરો { (r)->m_state = 0; } MZ_MACRO_END
#define tinfl_get_adler32(r) (r)->m_check_adler32

// Main low-level decompressor coroutine function. This is the only function actually needed for decompression. All the other functions are just high-level helpers for improved usability.
// This is a universal API, i.e. it can be used as a building block to build any desired higher level decompression API. In the limit case, it can be called once per every byte input or output.
MINIZ_STATIC tinfl_status tinfl_decompress(tinfl_decompressor *r, અચલ mz_uint8 *pIn_buf_next, size_t *pIn_buf_size, mz_uint8 *pOut_buf_start, mz_uint8 *pOut_buf_next, size_t *pOut_buf_size, અચલ mz_uint32 decomp_flags);

// Internal/private bits follow.
ગણના
{
  TINFL_MAX_HUFF_TABLES = 3, TINFL_MAX_HUFF_SYMBOLS_0 = 288, TINFL_MAX_HUFF_SYMBOLS_1 = 32, TINFL_MAX_HUFF_SYMBOLS_2 = 19,
  TINFL_FAST_LOOKUP_BITS = 10, TINFL_FAST_LOOKUP_SIZE = 1 << TINFL_FAST_LOOKUP_BITS
};

પ્રકારવ્યાખ્યા સંરચના
{
  mz_uint8 m_code_size[TINFL_MAX_HUFF_SYMBOLS_0];
  mz_int16 m_look_up[TINFL_FAST_LOOKUP_SIZE], m_વૃક્ષ[TINFL_MAX_HUFF_SYMBOLS_0 * 2];
} tinfl_huff_table;

#જો MINIZ_HAS_64BIT_REGISTERS
  #define TINFL_USE_64BIT_BITBUF 1
#endif

#જો TINFL_USE_64BIT_BITBUF
  પ્રકારવ્યાખ્યા mz_uint64 tinfl_bit_buf_t;
  #define TINFL_BITBUF_SIZE (64)
#નહીંતર
  પ્રકારવ્યાખ્યા mz_uint32 tinfl_bit_buf_t;
  #define TINFL_BITBUF_SIZE (32)
#endif

સંરચના tinfl_decompressor_tag
{
  mz_uint32 m_state, m_અંક_bits, m_zhdr0, m_zhdr1, m_z_adler32, m_final, m_type, m_check_adler32, m_dist, m_counter, m_અંક_extra, m_table_sizes[TINFL_MAX_HUFF_TABLES];
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
ગણના
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
ગણના
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
MINIZ_STATIC શૂન્ય *tdefl_compress_mem_to_heap(અચલ શૂન્ય *pSrc_buf, size_t src_buf_len, size_t *pOut_len, પૂર્ણાંક flags);

// tdefl_compress_mem_to_mem() compresses a block in memory to another block in memory.
// Returns 0 on failure.
MINIZ_STATIC size_t tdefl_compress_mem_to_mem(શૂન્ય *pOut_buf, size_t out_buf_len, અચલ શૂન્ય *pSrc_buf, size_t src_buf_len, પૂર્ણાંક flags);
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
MINIZ_STATIC શૂન્ય *tdefl_write_image_to_png_file_in_memory_ex(અચલ શૂન્ય *pImage, પૂર્ણાંક w, પૂર્ણાંક h, પૂર્ણાંક અંક_chans, પૂર્ણાંક bpl, size_t *pLen_out, mz_uint level, mz_bool flip, mz_uint8 *plte, પૂર્ણાંક plte_size, mz_uint8 *trns, પૂર્ણાંક trns_size);
#ifndef MINIZ_SDL_NOUNUSED
MINIZ_STATIC શૂન્ય *tdefl_write_image_to_png_file_in_memory(અચલ શૂન્ય *pImage, પૂર્ણાંક w, પૂર્ણાંક h, પૂર્ણાંક અંક_chans, પૂર્ણાંક bpl, size_t *pLen_out);
#endif

// Output stream interface. The compressor uses this interface to write compressed data. It'll typically be called TDEFL_OUT_BUF_SIZE at a time.
પ્રકારવ્યાખ્યા mz_bool (*tdefl_put_buf_func_ptr)(અચલ શૂન્ય* pBuf, પૂર્ણાંક len, શૂન્ય *pUser);

#ifndef MINIZ_SDL_NOUNUSED
// tdefl_compress_mem_to_output() compresses a block to an output stream. The above helpers use this function internally.
MINIZ_STATIC mz_bool tdefl_compress_mem_to_output(અચલ શૂન્ય *pBuf, size_t buf_len, tdefl_put_buf_func_ptr pPut_buf_func, શૂન્ય *pPut_buf_user, પૂર્ણાંક flags);
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
#જો TDEFL_LESS_MEMORY
ગણના { TDEFL_LZ_CODE_BUF_SIZE = 24 * 1024, TDEFL_OUT_BUF_SIZE = (TDEFL_LZ_CODE_BUF_SIZE * 13 ) / 10, TDEFL_MAX_HUFF_SYMBOLS = 288, TDEFL_LZ_HASH_BITS = 12, TDEFL_LEVEL1_HASH_SIZE_MASK = 4095, TDEFL_LZ_HASH_SHIFT = (TDEFL_LZ_HASH_BITS + 2) / 3, TDEFL_LZ_HASH_SIZE = 1 << TDEFL_LZ_HASH_BITS };
#નહીંતર
ગણના { TDEFL_LZ_CODE_BUF_SIZE = 64 * 1024, TDEFL_OUT_BUF_SIZE = (TDEFL_LZ_CODE_BUF_SIZE * 13 ) / 10, TDEFL_MAX_HUFF_SYMBOLS = 288, TDEFL_LZ_HASH_BITS = 15, TDEFL_LEVEL1_HASH_SIZE_MASK = 4095, TDEFL_LZ_HASH_SHIFT = (TDEFL_LZ_HASH_BITS + 2) / 3, TDEFL_LZ_HASH_SIZE = 1 << TDEFL_LZ_HASH_BITS };
#endif

// The low-level tdefl functions below may be used directly if the above helper functions aren't flexible enough. The low-level functions don't make any heap allocations, unlike the above helper functions.
પ્રકારવ્યાખ્યા ગણના
{
  TDEFL_STATUS_BAD_PARAM = -2,
  TDEFL_STATUS_PUT_BUF_FAILED = -1,
  TDEFL_STATUS_OKAY = 0,
  TDEFL_STATUS_DONE = 1,
} tdefl_status;

// Must map to MZ_NO_FLUSH, MZ_SYNC_FLUSH, etc. enums
પ્રકારવ્યાખ્યા ગણના
{
  TDEFL_NO_FLUSH = 0,
  TDEFL_SYNC_FLUSH = 2,
  TDEFL_FULL_FLUSH = 3,
  TDEFL_FINISH = 4
} tdefl_flush;

// tdefl's compression state structure.
પ્રકારવ્યાખ્યા સંરચના
{
  tdefl_put_buf_func_ptr m_pPut_buf_func;
  શૂન્ય *m_pPut_buf_user;
  mz_uint m_flags, m_max_probes[2];
  પૂર્ણાંક m_greedy_parsing;
  mz_uint m_adler32, m_lookahead_pos, m_lookahead_size, m_dict_size;
  mz_uint8 *m_pLZ_code_buf, *m_pLZ_flags, *m_pOutput_buf, *m_pOutput_buf_end;
  mz_uint m_અંક_flags_ડાબું, m_total_lz_bytes, m_lz_code_buf_dict_pos, m_bits_in, m_bit_buffer;
  mz_uint m_saved_match_dist, m_saved_match_len, m_saved_lit, m_output_flush_ofs, m_output_flush_remaining, m_finished, m_block_index, m_wants_to_finish;
  tdefl_status m_prev_return_status;
  અચલ શૂન્ય *m_pIn_buf;
  શૂન્ય *m_pOut_buf;
  size_t *m_pIn_buf_size, *m_pOut_buf_size;
  tdefl_flush m_flush;
  અચલ mz_uint8 *m_pSrc;
  size_t m_src_buf_ડાબું, m_out_buf_ofs;
  mz_uint8 m_dict[TDEFL_LZ_DICT_SIZE + TDEFL_MAX_MATCH_LEN - 1];
  mz_uint16 m_huff_ગણતરી[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
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
MINIZ_STATIC tdefl_status tdefl_init(tdefl_compressor *d, tdefl_put_buf_func_ptr pPut_buf_func, શૂન્ય *pPut_buf_user, પૂર્ણાંક flags);

// Compresses a block of data, consuming as much of the specified input buffer as possible, and writing as much compressed data to the specified output buffer as possible.
MINIZ_STATIC tdefl_status tdefl_compress(tdefl_compressor *d, અચલ શૂન્ય *pIn_buf, size_t *pIn_buf_size, શૂન્ય *pOut_buf, size_t *pOut_buf_size, tdefl_flush flush);

// tdefl_compress_buffer() is only usable when the tdefl_init() is called with a non-NULL tdefl_put_buf_func_ptr.
// tdefl_compress_buffer() always consumes the entire input buffer.
MINIZ_STATIC tdefl_status tdefl_compress_buffer(tdefl_compressor *d, અચલ શૂન્ય *pIn_buf, size_t in_buf_size, tdefl_flush flush);

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
MINIZ_STATIC mz_uint tdefl_create_comp_flags_from_zip_params(પૂર્ણાંક level, પૂર્ણાંક window_bits, પૂર્ણાંક strategy);
#endif // #ifndef MINIZ_NO_ZLIB_APIS

#endif /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#ifdef __cplusplus
}
#endif

#endif // MINIZ_HEADER_INCLUDED

// ------------------- End of Header: Implementation follows. (If you only want the header, define MINIZ_HEADER_FILE_ONLY.)

#ifndef MINIZ_HEADER_FILE_ONLY

#ifdef _MSC_VER
#pragma warning (ધકેલો)
#pragma warning (disable:4505) // unreferenced local function has been removed
#endif

પ્રકારવ્યાખ્યા unsigned અક્ષર mz_validate_uint16[કદ(mz_uint16)==2 ? 1 : -1];
પ્રકારવ્યાખ્યા unsigned અક્ષર mz_validate_uint32[કદ(mz_uint32)==4 ? 1 : -1];
પ્રકારવ્યાખ્યા unsigned અક્ષર mz_validate_uint64[કદ(mz_uint64)==8 ? 1 : -1];

/*#include <string.h>*/

#ifndef MZ_ASSERT
#અન્તર્ભાવ <assert.h>
#define MZ_ASSERT(x) પ્રતિજ્ઞા(x)
#endif

#ifdef MINIZ_NO_MALLOC
  #define MZ_MALLOC(x) ખાલી
  #define MZ_FREE(x) (શૂન્ય)x, ((શૂન્ય)0)
  #define MZ_REALLOC(p, x) ખાલી
#અથવાજો defined(MINIZ_SDL_MALLOC)
  #define MZ_MALLOC(x) SDL_malloc(x)
  #define MZ_FREE(x) SDL_free(x)
  #define MZ_REALLOC(p, x) SDL_realloc(p, x)
#નહીંતર
  #define MZ_MALLOC(x) malloc(x)
  #define MZ_FREE(x) મુક્ત(x)
  #define MZ_REALLOC(p, x) realloc(p, x)
#endif

#define MZ_MAX(a,b) (((a)>(b))?(a):(b))
#define MZ_MIN(a,b) (((a)<(b))?(a):(b))
#define MZ_CLEAR_OBJ(obj) memset(&(obj), 0, કદ(obj))
#define MZ_CLEAR_ARR(obj) memset((obj), 0, કદ(obj))
#define MZ_CLEAR_PTR(obj) memset((obj), 0, કદ(*obj))

#જો MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  #define MZ_READ_LE16(p) *((અચલ mz_uint16 *)(p))
  #define MZ_READ_LE32(p) *((અચલ mz_uint32 *)(p))
#નહીંતર
  #define MZ_READ_LE16(p) ((mz_uint32)(((અચલ mz_uint8 *)(p))[0]) | ((mz_uint32)(((અચલ mz_uint8 *)(p))[1]) << 8U))
  #define MZ_READ_LE32(p) ((mz_uint32)(((અચલ mz_uint8 *)(p))[0]) | ((mz_uint32)(((અચલ mz_uint8 *)(p))[1]) << 8U) | ((mz_uint32)(((અચલ mz_uint8 *)(p))[2]) << 16U) | ((mz_uint32)(((અચલ mz_uint8 *)(p))[3]) << 24U))
#endif

#ifdef _MSC_VER
  #define MZ_FORCEINLINE __forceinline
#અથવાજો defined(__GNUC__)
  #define MZ_FORCEINLINE અંતઃરેખ __attribute__((__always_inline__))
#નહીંતર
  #define MZ_FORCEINLINE અંતઃરેખ
#endif

#ifdef __cplusplus
  બાહ્ય "C" {
#endif

// ------------------- zlib-style API's

mz_ulong mz_adler32(mz_ulong adler, અચલ unsigned અક્ષર *ptr, size_t buf_len)
{
  mz_uint32 i, s1 = (mz_uint32)(adler & 0xffff), s2 = (mz_uint32)(adler >> 16); size_t block_len = buf_len % 5552;
  જો (!ptr) પાછા MZ_ADLER32_INIT;
  જ્યારે (buf_len) {
    માટે (i = 0; i + 7 < block_len; i += 8, ptr += 8) {
      s1 += ptr[0]; s2 += s1; s1 += ptr[1]; s2 += s1; s1 += ptr[2]; s2 += s1; s1 += ptr[3]; s2 += s1;
      s1 += ptr[4]; s2 += s1; s1 += ptr[5]; s2 += s1; s1 += ptr[6]; s2 += s1; s1 += ptr[7]; s2 += s1;
    }
    માટે ( ; i < block_len; ++i) { s1 += *ptr++; s2 += s1; }
    s1 %= 65521U; s2 %= 65521U; buf_len -= block_len; block_len = 5552;
  }
  પાછા (s2 << 16) + s1;
}

// Karl Malbrain's compact CRC-32. See "A compact CCITT crc16 and crc32 C implementation that balances processor cache usage against speed": http://www.geocities.com/malbrain/
mz_ulong mz_crc32(mz_ulong crc, અચલ mz_uint8 *ptr, size_t buf_len)
{
  સ્થિર અચલ mz_uint32 s_crc32[16] = { 0, 0x1db71064, 0x3b6e20c8, 0x26d930ac, 0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
    0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c, 0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c };
  mz_uint32 crcu32 = (mz_uint32)crc;
  જો (!ptr) પાછા MZ_CRC32_INIT;
  crcu32 = ~crcu32; જ્યારે (buf_len--) { mz_uint8 b = *ptr++; crcu32 = (crcu32 >> 4) ^ s_crc32[(crcu32 & 0xF) ^ (b & 0xF)]; crcu32 = (crcu32 >> 4) ^ s_crc32[(crcu32 & 0xF) ^ (b >> 4)]; }
  પાછા ~crcu32;
}

MINIZ_STATIC શૂન્ય mz_free(શૂન્ય *p)
{
  MZ_FREE(p);
}

#ifndef MINIZ_NO_ZLIB_APIS

સ્થિર શૂન્ય *def_alloc_func(શૂન્ય *opaque, size_t વસ્તુઓ, size_t size) { (શૂન્ય)opaque, (શૂન્ય)વસ્તુઓ, (શૂન્ય)size; પાછા MZ_MALLOC(વસ્તુઓ * size); }
સ્થિર શૂન્ય def_free_func(શૂન્ય *opaque, શૂન્ય *address) { (શૂન્ય)opaque, (શૂન્ય)address; MZ_FREE(address); }
સ્થિર શૂન્ય *def_realloc_func(શૂન્ય *opaque, શૂન્ય *address, size_t વસ્તુઓ, size_t size) { (શૂન્ય)opaque, (શૂન્ય)address, (શૂન્ય)વસ્તુઓ, (શૂન્ય)size; પાછા MZ_REALLOC(address, વસ્તુઓ * size); }

અચલ અક્ષર *mz_version(શૂન્ય)
{
  પાછા MZ_VERSION;
}

#ifndef MINIZ_NO_DEFLATE_APIS

પૂર્ણાંક mz_deflateInit(mz_streamp pStream, પૂર્ણાંક level)
{
  પાછા mz_deflateInit2(pStream, level, MZ_DEFLATED, MZ_DEFAULT_WINDOW_BITS, 9, MZ_DEFAULT_STRATEGY);
}

પૂર્ણાંક mz_deflateInit2(mz_streamp pStream, પૂર્ણાંક level, પૂર્ણાંક method, પૂર્ણાંક window_bits, પૂર્ણાંક mem_level, પૂર્ણાંક strategy)
{
  tdefl_compressor *pComp;
  mz_uint comp_flags = TDEFL_COMPUTE_ADLER32 | tdefl_create_comp_flags_from_zip_params(level, window_bits, strategy);

  જો (!pStream) પાછા MZ_STREAM_ERROR;
  જો ((method != MZ_DEFLATED) || ((mem_level < 1) || (mem_level > 9)) || ((window_bits != MZ_DEFAULT_WINDOW_BITS) && (-window_bits != MZ_DEFAULT_WINDOW_BITS))) પાછા MZ_PARAM_ERROR;

  pStream->data_type = 0;
  pStream->adler = MZ_ADLER32_INIT;
  pStream->સંદેશ = ખાલી;
  pStream->reserved = 0;
  pStream->total_in = 0;
  pStream->total_out = 0;
  જો (!pStream->zalloc) pStream->zalloc = def_alloc_func;
  જો (!pStream->zfree) pStream->zfree = def_free_func;

  pComp = (tdefl_compressor *)pStream->zalloc(pStream->opaque, 1, કદ(tdefl_compressor));
  જો (!pComp)
    પાછા MZ_MEM_ERROR;

  pStream->state = (સંરચના mz_internal_state *)pComp;

  જો (tdefl_init(pComp, ખાલી, ખાલી, comp_flags) != TDEFL_STATUS_OKAY)
  {
    mz_deflateEnd(pStream);
    પાછા MZ_PARAM_ERROR;
  }

  પાછા MZ_OK;
}

પૂર્ણાંક mz_deflateReset(mz_streamp pStream)
{
  જો ((!pStream) || (!pStream->state) || (!pStream->zalloc) || (!pStream->zfree)) પાછા MZ_STREAM_ERROR;
  pStream->total_in = pStream->total_out = 0;
  tdefl_init((tdefl_compressor*)pStream->state, ખાલી, ખાલી, ((tdefl_compressor*)pStream->state)->m_flags);
  પાછા MZ_OK;
}

પૂર્ણાંક mz_deflate(mz_streamp pStream, પૂર્ણાંક flush)
{
  size_t in_bytes, out_bytes;
  mz_ulong orig_total_in, orig_total_out;
  પૂર્ણાંક mz_status = MZ_OK;

  જો ((!pStream) || (!pStream->state) || (flush < 0) || (flush > MZ_FINISH) || (!pStream->next_out)) પાછા MZ_STREAM_ERROR;
  જો (!pStream->avail_out) પાછા MZ_BUF_ERROR;

  જો (flush == MZ_PARTIAL_FLUSH) flush = MZ_SYNC_FLUSH;

  જો (((tdefl_compressor*)pStream->state)->m_prev_return_status == TDEFL_STATUS_DONE)
    પાછા (flush == MZ_FINISH) ? MZ_STREAM_END : MZ_BUF_ERROR;

  orig_total_in = pStream->total_in; orig_total_out = pStream->total_out;
  માટે ( ; ; )
  {
    tdefl_status defl_status;
    in_bytes = pStream->avail_in; out_bytes = pStream->avail_out;

    defl_status = tdefl_compress((tdefl_compressor*)pStream->state, pStream->next_in, &in_bytes, pStream->next_out, &out_bytes, (tdefl_flush)flush);
    pStream->next_in += (mz_uint)in_bytes; pStream->avail_in -= (mz_uint)in_bytes;
    pStream->total_in += (mz_uint)in_bytes; pStream->adler = tdefl_get_adler32((tdefl_compressor*)pStream->state);

    pStream->next_out += (mz_uint)out_bytes; pStream->avail_out -= (mz_uint)out_bytes;
    pStream->total_out += (mz_uint)out_bytes;

    જો (defl_status < 0)
    {
      mz_status = MZ_STREAM_ERROR;
      તોડો;
    }
    નહીંતર જો (defl_status == TDEFL_STATUS_DONE)
    {
      mz_status = MZ_STREAM_END;
      તોડો;
    }
    નહીંતર જો (!pStream->avail_out)
      તોડો;
    નહીંતર જો ((!pStream->avail_in) && (flush != MZ_FINISH))
    {
      જો ((flush) || (pStream->total_in != orig_total_in) || (pStream->total_out != orig_total_out))
        તોડો;
      પાછા MZ_BUF_ERROR; // Can't make forward progress without some input.
    }
  }
  પાછા mz_status;
}

પૂર્ણાંક mz_deflateEnd(mz_streamp pStream)
{
  જો (!pStream) પાછા MZ_STREAM_ERROR;
  જો (pStream->state)
  {
    pStream->zfree(pStream->opaque, pStream->state);
    pStream->state = ખાલી;
  }
  પાછા MZ_OK;
}

mz_ulong mz_deflateBound(mz_streamp pStream, mz_ulong source_len)
{
  (શૂન્ય)pStream;
  // This is really over conservative. (And lame, but it's actually pretty tricky to compute a true upper bound given the way tdefl's blocking works.)
  પાછા MZ_MAX(128 + (source_len * 110) / 100, 128 + source_len + ((source_len / (31 * 1024)) + 1) * 5);
}

પૂર્ણાંક mz_compress2(unsigned અક્ષર *pDest, mz_ulong *pDest_len, અચલ unsigned અક્ષર *pSource, mz_ulong source_len, પૂર્ણાંક level)
{
  પૂર્ણાંક status;
  mz_stream stream;
  memset(&stream, 0, કદ(stream));

  // In case mz_ulong is 64-bits (argh I hate longs).
  જો ((source_len | *pDest_len) > 0xFFFFFFFFU) પાછા MZ_PARAM_ERROR;

  stream.next_in = pSource;
  stream.avail_in = (mz_uint32)source_len;
  stream.next_out = pDest;
  stream.avail_out = (mz_uint32)*pDest_len;

  status = mz_deflateInit(&stream, level);
  જો (status != MZ_OK) પાછા status;

  status = mz_deflate(&stream, MZ_FINISH);
  જો (status != MZ_STREAM_END)
  {
    mz_deflateEnd(&stream);
    પાછા (status == MZ_OK) ? MZ_BUF_ERROR : status;
  }

  *pDest_len = stream.total_out;
  પાછા mz_deflateEnd(&stream);
}

પૂર્ણાંક mz_compress(unsigned અક્ષર *pDest, mz_ulong *pDest_len, અચલ unsigned અક્ષર *pSource, mz_ulong source_len)
{
  પાછા mz_compress2(pDest, pDest_len, pSource, source_len, MZ_DEFAULT_COMPRESSION);
}

mz_ulong mz_compressBound(mz_ulong source_len)
{
  પાછા mz_deflateBound(ખાલી, source_len);
}

#endif /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#ifndef MINIZ_NO_INFLATE_APIS

પ્રકારવ્યાખ્યા સંરચના
{
  tinfl_decompressor m_decomp;
  mz_uint m_dict_ofs, m_dict_avail, m_first_call, m_has_flushed; પૂર્ણાંક m_window_bits;
  mz_uint8 m_dict[TINFL_LZ_DICT_SIZE];
  tinfl_status m_last_status;
} inflate_state;

પૂર્ણાંક mz_inflateInit2(mz_streamp pStream, પૂર્ણાંક window_bits)
{
  inflate_state *pDecomp;
  જો (!pStream) પાછા MZ_STREAM_ERROR;
  જો ((window_bits != MZ_DEFAULT_WINDOW_BITS) && (-window_bits != MZ_DEFAULT_WINDOW_BITS)) પાછા MZ_PARAM_ERROR;

  pStream->data_type = 0;
  pStream->adler = 0;
  pStream->સંદેશ = ખાલી;
  pStream->total_in = 0;
  pStream->total_out = 0;
  pStream->reserved = 0;
  જો (!pStream->zalloc) pStream->zalloc = def_alloc_func;
  જો (!pStream->zfree) pStream->zfree = def_free_func;

  pDecomp = (inflate_state*)pStream->zalloc(pStream->opaque, 1, કદ(inflate_state));
  જો (!pDecomp) પાછા MZ_MEM_ERROR;

  pStream->state = (સંરચના mz_internal_state *)pDecomp;

  tinfl_init(&pDecomp->m_decomp);
  pDecomp->m_dict_ofs = 0;
  pDecomp->m_dict_avail = 0;
  pDecomp->m_last_status = TINFL_STATUS_NEEDS_MORE_આગત;
  pDecomp->m_first_call = 1;
  pDecomp->m_has_flushed = 0;
  pDecomp->m_window_bits = window_bits;

  પાછા MZ_OK;
}

પૂર્ણાંક mz_inflateInit(mz_streamp pStream)
{
   પાછા mz_inflateInit2(pStream, MZ_DEFAULT_WINDOW_BITS);
}

પૂર્ણાંક mz_inflate(mz_streamp pStream, પૂર્ણાંક flush)
{
  inflate_state* pState;
  mz_uint n, first_call, decomp_flags = TINFL_FLAG_COMPUTE_ADLER32;
  size_t in_bytes, out_bytes, orig_avail_in;
  tinfl_status status;

  જો ((!pStream) || (!pStream->state)) પાછા MZ_STREAM_ERROR;
  જો (flush == MZ_PARTIAL_FLUSH) flush = MZ_SYNC_FLUSH;
  જો ((flush) && (flush != MZ_SYNC_FLUSH) && (flush != MZ_FINISH)) પાછા MZ_STREAM_ERROR;

  pState = (inflate_state*)pStream->state;
  જો (pState->m_window_bits > 0) decomp_flags |= TINFL_FLAG_PARSE_ZLIB_HEADER;
  orig_avail_in = pStream->avail_in;

  first_call = pState->m_first_call; pState->m_first_call = 0;
  જો (pState->m_last_status < 0) પાછા MZ_DATA_ERROR;

  જો (pState->m_has_flushed && (flush != MZ_FINISH)) પાછા MZ_STREAM_ERROR;
  pState->m_has_flushed |= (flush == MZ_FINISH);

  જો ((flush == MZ_FINISH) && (first_call))
  {
    // MZ_FINISH on the first call implies that the input and output buffers are large enough to hold the entire compressed/decompressed file.
    decomp_flags |= TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF;
    in_bytes = pStream->avail_in; out_bytes = pStream->avail_out;
    status = tinfl_decompress(&pState->m_decomp, pStream->next_in, &in_bytes, pStream->next_out, pStream->next_out, &out_bytes, decomp_flags);
    pState->m_last_status = status;
    pStream->next_in += (mz_uint)in_bytes; pStream->avail_in -= (mz_uint)in_bytes; pStream->total_in += (mz_uint)in_bytes;
    pStream->adler = tinfl_get_adler32(&pState->m_decomp);
    pStream->next_out += (mz_uint)out_bytes; pStream->avail_out -= (mz_uint)out_bytes; pStream->total_out += (mz_uint)out_bytes;

    જો (status < 0)
      પાછા MZ_DATA_ERROR;
    નહીંતર જો (status != TINFL_STATUS_DONE)
    {
      pState->m_last_status = TINFL_STATUS_FAILED;
      પાછા MZ_BUF_ERROR;
    }
    પાછા MZ_STREAM_END;
  }
  // flush != MZ_FINISH then we must assume there's more input.
  જો (flush != MZ_FINISH) decomp_flags |= TINFL_FLAG_HAS_MORE_આગત;

  જો (pState->m_dict_avail)
  {
    n = MZ_MIN(pState->m_dict_avail, pStream->avail_out);
    memcpy(pStream->next_out, pState->m_dict + pState->m_dict_ofs, n);
    pStream->next_out += n; pStream->avail_out -= n; pStream->total_out += n;
    pState->m_dict_avail -= n; pState->m_dict_ofs = (pState->m_dict_ofs + n) & (TINFL_LZ_DICT_SIZE - 1);
    પાછા ((pState->m_last_status == TINFL_STATUS_DONE) && (!pState->m_dict_avail)) ? MZ_STREAM_END : MZ_OK;
  }

  માટે ( ; ; )
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

    જો (status < 0)
       પાછા MZ_DATA_ERROR; // Stream is corrupted (there could be some uncompressed data left in the output dictionary - oh well).
    નહીંતર જો ((status == TINFL_STATUS_NEEDS_MORE_આગત) && (!orig_avail_in))
      પાછા MZ_BUF_ERROR; // Signal caller that we can't make forward progress without supplying more input or by setting flush to MZ_FINISH.
    નહીંતર જો (flush == MZ_FINISH)
    {
       // The output buffer MUST be large to hold the remaining uncompressed data when flush==MZ_FINISH.
       જો (status == TINFL_STATUS_DONE)
          પાછા pState->m_dict_avail ? MZ_BUF_ERROR : MZ_STREAM_END;
       // status here must be TINFL_STATUS_HAS_MORE_OUTPUT, which means there's at least 1 more byte on the way. If there's no more room left in the output buffer then something is wrong.
       નહીંતર જો (!pStream->avail_out)
          પાછા MZ_BUF_ERROR;
    }
    નહીંતર જો ((status == TINFL_STATUS_DONE) || (!pStream->avail_in) || (!pStream->avail_out) || (pState->m_dict_avail))
      તોડો;
  }

  પાછા ((status == TINFL_STATUS_DONE) && (!pState->m_dict_avail)) ? MZ_STREAM_END : MZ_OK;
}

પૂર્ણાંક mz_inflateEnd(mz_streamp pStream)
{
  જો (!pStream)
    પાછા MZ_STREAM_ERROR;
  જો (pStream->state)
  {
    pStream->zfree(pStream->opaque, pStream->state);
    pStream->state = ખાલી;
  }
  પાછા MZ_OK;
}

પૂર્ણાંક mz_uncompress(unsigned અક્ષર *pDest, mz_ulong *pDest_len, અચલ unsigned અક્ષર *pSource, mz_ulong source_len)
{
  mz_stream stream;
  પૂર્ણાંક status;
  memset(&stream, 0, કદ(stream));

  // In case mz_ulong is 64-bits (argh I hate longs).
  જો ((source_len | *pDest_len) > 0xFFFFFFFFU) પાછા MZ_PARAM_ERROR;

  stream.next_in = pSource;
  stream.avail_in = (mz_uint32)source_len;
  stream.next_out = pDest;
  stream.avail_out = (mz_uint32)*pDest_len;

  status = mz_inflateInit(&stream);
  જો (status != MZ_OK)
    પાછા status;

  status = mz_inflate(&stream, MZ_FINISH);
  જો (status != MZ_STREAM_END)
  {
    mz_inflateEnd(&stream);
    પાછા ((status == MZ_BUF_ERROR) && (!stream.avail_in)) ? MZ_DATA_ERROR : status;
  }
  *pDest_len = stream.total_out;

  પાછા mz_inflateEnd(&stream);
}

#endif /*#ifndef MINIZ_NO_INFLATE_APIS*/

અચલ અક્ષર *mz_error(પૂર્ણાંક err)
{
  સ્થિર સંરચના { પૂર્ણાંક m_err; અચલ અક્ષર *m_pDesc; } s_error_descs[] =
  {
    { MZ_OK, "" }, { MZ_STREAM_END, "stream end" }, { MZ_NEED_DICT, "need dictionary" }, { MZ_ERRNO, "file error" }, { MZ_STREAM_ERROR, "stream error" },
    { MZ_DATA_ERROR, "data error" }, { MZ_MEM_ERROR, "out of memory" }, { MZ_BUF_ERROR, "buf error" }, { MZ_VERSION_ERROR, "version error" }, { MZ_PARAM_ERROR, "parameter error" }
  };
  mz_uint i; માટે (i = 0; i < કદ(s_error_descs) / કદ(s_error_descs[0]); ++i) જો (s_error_descs[i].m_err == err) પાછા s_error_descs[i].m_pDesc;
  પાછા ખાલી;
}

#endif //MINIZ_NO_ZLIB_APIS

// ------------------- Low-level Decompression (completely independent from all compression API's)
#ifndef MINIZ_NO_INFLATE_APIS

#define TINFL_MEMCPY(d, s, l) memcpy(d, s, l)
#define TINFL_MEMSET(p, c, l) memset(p, c, l)

#define TINFL_CR_BEGIN પસંદગી(r->m_state) { સ્થિતિ 0:
#define TINFL_CR_RETURN(state_index, result) કરો { status = result; r->m_state = state_index; જાઓ common_exit; સ્થિતિ state_index:; } MZ_MACRO_END
#define TINFL_CR_RETURN_FOREVER(state_index, result) કરો { માટે ( ; ; ) { TINFL_CR_RETURN(state_index, result); } } MZ_MACRO_END
#define TINFL_CR_FINISH }

// TODO: If the caller has indicated that there's no more input, and we attempt to read beyond the input buf, then something is wrong with the input because the inflator never
// reads ahead more than it needs to. Currently TINFL_GET_BYTE() pads the end of the stream with 0's in this scenario.
#define TINFL_GET_BYTE(state_index, c) કરો { \
  જો (pIn_buf_cur >= pIn_buf_end) { \
    માટે ( ; ; ) { \
      જો (decomp_flags & TINFL_FLAG_HAS_MORE_આગત) { \
        TINFL_CR_RETURN(state_index, TINFL_STATUS_NEEDS_MORE_આગત); \
        જો (pIn_buf_cur < pIn_buf_end) { \
          c = *pIn_buf_cur++; \
          તોડો; \
        } \
      } નહીંતર { \
        c = 0; \
        તોડો; \
      } \
    } \
  } નહીંતર c = *pIn_buf_cur++; } MZ_MACRO_END

#define TINFL_NEED_BITS(state_index, n) કરો { mz_uint c; TINFL_GET_BYTE(state_index, c); bit_buf |= (((tinfl_bit_buf_t)c) << અંક_bits); અંક_bits += 8; } જ્યારે (અંક_bits < (mz_uint)(n))
#define TINFL_SKIP_BITS(state_index, n) કરો { જો (અંક_bits < (mz_uint)(n)) { TINFL_NEED_BITS(state_index, n); } bit_buf >>= (n); અંક_bits -= (n); } MZ_MACRO_END
#define TINFL_GET_BITS(state_index, b, n) કરો { જો (અંક_bits < (mz_uint)(n)) { TINFL_NEED_BITS(state_index, n); } b = bit_buf & ((1 << (n)) - 1); bit_buf >>= (n); અંક_bits -= (n); } MZ_MACRO_END

// TINFL_HUFF_BITBUF_FILL() is only used rarely, when the number of bytes remaining in the input buffer falls below 2.
// It reads just enough bytes from the input stream that are needed to decode the next Huffman code (and absolutely no more). It works by trying to fully decode a
// Huffman code by using whatever bits are currently present in the bit buffer. If this fails, it reads another byte, and tries again until it succeeds or until the
// bit buffer contains >=15 bits (deflate's max. Huffman code size).
#define TINFL_HUFF_BITBUF_FILL(state_index, pHuff) \
  કરો { \
    temp = (pHuff)->m_look_up[bit_buf & (TINFL_FAST_LOOKUP_SIZE - 1)]; \
    જો (temp >= 0) { \
      code_len = temp >> 9; \
      જો ((code_len) && (અંક_bits >= code_len)) \
          તોડો; \
    } નહીંતર જો (અંક_bits > TINFL_FAST_LOOKUP_BITS) { \
       code_len = TINFL_FAST_LOOKUP_BITS; \
       કરો { \
          temp = (pHuff)->m_વૃક્ષ[~temp + ((bit_buf >> code_len++) & 1)]; \
       } જ્યારે ((temp < 0) && (અંક_bits >= (code_len + 1))); \
       જો (temp >= 0) તોડો; \
    } \
    TINFL_GET_BYTE(state_index, c); \
    bit_buf |= (((tinfl_bit_buf_t)c) << અંક_bits); \
    અંક_bits += 8; \
  } જ્યારે (અંક_bits < 15);

// TINFL_HUFF_DECODE() decodes the next Huffman coded symbol. It's more complex than you would initially expect because the zlib API expects the decompressor to never read
// beyond the final byte of the deflate stream. (In other words, when this macro wants to read another byte from the input, it REALLY needs another byte in order to fully
// decode the next Huffman code.) Handling this properly is particularly important on raw deflate (non-zlib) streams, which aren't followed by a byte aligned adler-32.
// The slow path is only executed at the very end of the input buffer.
#define TINFL_HUFF_DECODE(state_index, sym, pHuff) કરો { \
  પૂર્ણાંક temp; mz_uint code_len, c; \
  જો (અંક_bits < 15) { \
    જો ((pIn_buf_end - pIn_buf_cur) < 2) { \
       TINFL_HUFF_BITBUF_FILL(state_index, pHuff); \
    } નહીંતર { \
       bit_buf |= (((tinfl_bit_buf_t)pIn_buf_cur[0]) << અંક_bits) | (((tinfl_bit_buf_t)pIn_buf_cur[1]) << (અંક_bits + 8)); pIn_buf_cur += 2; અંક_bits += 16; \
    } \
  } \
  જો ((temp = (pHuff)->m_look_up[bit_buf & (TINFL_FAST_LOOKUP_SIZE - 1)]) >= 0) \
    code_len = temp >> 9, temp &= 511; \
  નહીંતર { \
    code_len = TINFL_FAST_LOOKUP_BITS; કરો { temp = (pHuff)->m_વૃક્ષ[~temp + ((bit_buf >> code_len++) & 1)]; } જ્યારે (temp < 0); \
  } sym = temp; bit_buf >>= code_len; અંક_bits -= code_len; } MZ_MACRO_END

tinfl_status tinfl_decompress(tinfl_decompressor *r, અચલ mz_uint8 *pIn_buf_next, size_t *pIn_buf_size, mz_uint8 *pOut_buf_start, mz_uint8 *pOut_buf_next, size_t *pOut_buf_size, અચલ mz_uint32 decomp_flags)
{
  સ્થિર અચલ પૂર્ણાંક s_length_base[31] = { 3,4,5,6,7,8,9,10,11,13, 15,17,19,23,27,31,35,43,51,59, 67,83,99,115,131,163,195,227,258,0,0 };
  સ્થિર અચલ પૂર્ણાંક s_length_extra[31]= { 0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,0,0,0 };
  સ્થિર અચલ પૂર્ણાંક s_dist_base[32] = { 1,2,3,4,5,7,9,13,17,25,33,49,65,97,129,193, 257,385,513,769,1025,1537,2049,3073,4097,6145,8193,12289,16385,24577,0,0};
  સ્થિર અચલ પૂર્ણાંક s_dist_extra[32] = { 0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13};
  સ્થિર અચલ mz_uint8 s_length_dezigzag[19] = { 16,17,18,0,8,7,9,6,10,5,11,4,12,3,13,2,14,1,15 };
  સ્થિર અચલ પૂર્ણાંક s_min_table_sizes[3] = { 257, 1, 4 };

  tinfl_status status = TINFL_STATUS_FAILED; mz_uint32 અંક_bits, dist, counter, અંક_extra; tinfl_bit_buf_t bit_buf;
  અચલ mz_uint8 *pIn_buf_cur = pIn_buf_next, *અચલ pIn_buf_end = pIn_buf_next + *pIn_buf_size;
  mz_uint8 *pOut_buf_cur = pOut_buf_next, *અચલ pOut_buf_end = pOut_buf_next + *pOut_buf_size;
  size_t out_buf_size_mask = (decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF) ? (size_t)-1 : ((pOut_buf_next - pOut_buf_start) + *pOut_buf_size) - 1, dist_from_out_buf_start;

  // Ensure the output buffer's size is a power of 2, unless the output buffer is large enough to hold the entire output file (in which case it doesn't matter).
  જો (((out_buf_size_mask + 1) & out_buf_size_mask) || (pOut_buf_next < pOut_buf_start)) { *pIn_buf_size = *pOut_buf_size = 0; પાછા TINFL_STATUS_BAD_PARAM; }

  અંક_bits = r->m_અંક_bits; bit_buf = r->m_bit_buf; dist = r->m_dist; counter = r->m_counter; અંક_extra = r->m_અંક_extra; dist_from_out_buf_start = r->m_dist_from_out_buf_start;
  TINFL_CR_BEGIN

  bit_buf = અંક_bits = dist = counter = અંક_extra = r->m_zhdr0 = r->m_zhdr1 = 0; r->m_z_adler32 = r->m_check_adler32 = 1;
  જો (decomp_flags & TINFL_FLAG_PARSE_ZLIB_HEADER)
  {
    TINFL_GET_BYTE(1, r->m_zhdr0); TINFL_GET_BYTE(2, r->m_zhdr1);
    counter = (((r->m_zhdr0 * 256 + r->m_zhdr1) % 31 != 0) || (r->m_zhdr1 & 32) || ((r->m_zhdr0 & 15) != 8));
    જો (!(decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF)) counter |= (((1U << (8U + (r->m_zhdr0 >> 4))) > 32768U) || ((out_buf_size_mask + 1) < (size_t)(1U << (8U + (r->m_zhdr0 >> 4)))));
    જો (counter) { TINFL_CR_RETURN_FOREVER(36, TINFL_STATUS_FAILED); }
  }

  કરો
  {
    TINFL_GET_BITS(3, r->m_final, 3); r->m_type = r->m_final >> 1;
    જો (r->m_type == 0)
    {
      TINFL_SKIP_BITS(5, અંક_bits & 7);
      માટે (counter = 0; counter < 4; ++counter) { જો (અંક_bits) TINFL_GET_BITS(6, r->m_raw_header[counter], 8); નહીંતર TINFL_GET_BYTE(7, r->m_raw_header[counter]); }
      જો ((counter = (r->m_raw_header[0] | (r->m_raw_header[1] << 8))) != (mz_uint)(0xFFFF ^ (r->m_raw_header[2] | (r->m_raw_header[3] << 8)))) { TINFL_CR_RETURN_FOREVER(39, TINFL_STATUS_FAILED); }
      જ્યારે ((counter) && (અંક_bits))
      {
        TINFL_GET_BITS(51, dist, 8);
        જ્યારે (pOut_buf_cur >= pOut_buf_end) { TINFL_CR_RETURN(52, TINFL_STATUS_HAS_MORE_OUTPUT); }
        *pOut_buf_cur++ = (mz_uint8)dist;
        counter--;
      }
      જ્યારે (counter)
      {
        size_t n; જ્યારે (pOut_buf_cur >= pOut_buf_end) { TINFL_CR_RETURN(9, TINFL_STATUS_HAS_MORE_OUTPUT); }
        જ્યારે (pIn_buf_cur >= pIn_buf_end)
        {
          જો (decomp_flags & TINFL_FLAG_HAS_MORE_આગત)
          {
            TINFL_CR_RETURN(38, TINFL_STATUS_NEEDS_MORE_આગત);
          }
          નહીંતર
          {
            TINFL_CR_RETURN_FOREVER(40, TINFL_STATUS_FAILED);
          }
        }
        n = MZ_MIN(MZ_MIN((size_t)(pOut_buf_end - pOut_buf_cur), (size_t)(pIn_buf_end - pIn_buf_cur)), counter);
        TINFL_MEMCPY(pOut_buf_cur, pIn_buf_cur, n); pIn_buf_cur += n; pOut_buf_cur += n; counter -= (mz_uint)n;
      }
    }
    નહીંતર જો (r->m_type == 3)
    {
      TINFL_CR_RETURN_FOREVER(10, TINFL_STATUS_FAILED);
    }
    નહીંતર
    {
      જો (r->m_type == 1)
      {
        mz_uint8 *p = r->m_tables[0].m_code_size; mz_uint i;
        r->m_table_sizes[0] = 288; r->m_table_sizes[1] = 32; TINFL_MEMSET(r->m_tables[1].m_code_size, 5, 32);
        માટે ( i = 0; i <= 143; ++i) *p++ = 8;
        માટે ( ; i <= 255; ++i) *p++ = 9;
        માટે ( ; i <= 279; ++i) *p++ = 7;
        માટે ( ; i <= 287; ++i) *p++ = 8;
      }
      નહીંતર
      {
        માટે (counter = 0; counter < 3; counter++) { TINFL_GET_BITS(11, r->m_table_sizes[counter], "\05\05\04"[counter]); r->m_table_sizes[counter] += s_min_table_sizes[counter]; }
        MZ_CLEAR_ARR(r->m_tables[2].m_code_size); માટે (counter = 0; counter < r->m_table_sizes[2]; counter++) { mz_uint s; TINFL_GET_BITS(14, s, 3); r->m_tables[2].m_code_size[s_length_dezigzag[counter]] = (mz_uint8)s; }
        r->m_table_sizes[2] = 19;
      }
      માટે ( ; (પૂર્ણાંક)r->m_type >= 0; r->m_type--)
      {
        પૂર્ણાંક વૃક્ષ_next, વૃક્ષ_cur; tinfl_huff_table *pTable;
        mz_uint i, j, used_syms, total, sym_index, next_code[17], total_syms[16]; pTable = &r->m_tables[r->m_type]; MZ_CLEAR_ARR(total_syms); MZ_CLEAR_ARR(pTable->m_look_up); MZ_CLEAR_ARR(pTable->m_વૃક્ષ);
        માટે (i = 0; i < r->m_table_sizes[r->m_type]; ++i) total_syms[pTable->m_code_size[i]]++;
        used_syms = 0, total = 0; next_code[0] = next_code[1] = 0;
        માટે (i = 1; i <= 15; ++i) { used_syms += total_syms[i]; next_code[i + 1] = (total = ((total + total_syms[i]) << 1)); }
        જો ((65536 != total) && (used_syms > 1))
        {
          TINFL_CR_RETURN_FOREVER(35, TINFL_STATUS_FAILED);
        }
        માટે (વૃક્ષ_next = -1, sym_index = 0; sym_index < r->m_table_sizes[r->m_type]; ++sym_index)
        {
          mz_uint rev_code = 0, l, cur_code, code_size = pTable->m_code_size[sym_index]; જો (!code_size) ચાલુ;
          cur_code = next_code[code_size]++; માટે (l = code_size; l > 0; l--, cur_code >>= 1) rev_code = (rev_code << 1) | (cur_code & 1);
          જો (code_size <= TINFL_FAST_LOOKUP_BITS) { mz_int16 k = (mz_int16)((code_size << 9) | sym_index); જ્યારે (rev_code < TINFL_FAST_LOOKUP_SIZE) { pTable->m_look_up[rev_code] = k; rev_code += (1 << code_size); } ચાલુ; }
          જો (0 == (વૃક્ષ_cur = pTable->m_look_up[rev_code & (TINFL_FAST_LOOKUP_SIZE - 1)])) { pTable->m_look_up[rev_code & (TINFL_FAST_LOOKUP_SIZE - 1)] = (mz_int16)વૃક્ષ_next; વૃક્ષ_cur = વૃક્ષ_next; વૃક્ષ_next -= 2; }
          rev_code >>= (TINFL_FAST_LOOKUP_BITS - 1);
          માટે (j = code_size; j > (TINFL_FAST_LOOKUP_BITS + 1); j--)
          {
            વૃક્ષ_cur -= ((rev_code >>= 1) & 1);
            જો (!pTable->m_વૃક્ષ[-વૃક્ષ_cur - 1]) { pTable->m_વૃક્ષ[-વૃક્ષ_cur - 1] = (mz_int16)વૃક્ષ_next; વૃક્ષ_cur = વૃક્ષ_next; વૃક્ષ_next -= 2; } નહીંતર વૃક્ષ_cur = pTable->m_વૃક્ષ[-વૃક્ષ_cur - 1];
          }
          વૃક્ષ_cur -= ((rev_code >>= 1) & 1); pTable->m_વૃક્ષ[-વૃક્ષ_cur - 1] = (mz_int16)sym_index;
        }
        જો (r->m_type == 2)
        {
          માટે (counter = 0; counter < (r->m_table_sizes[0] + r->m_table_sizes[1]); )
          {
            mz_uint s; TINFL_HUFF_DECODE(16, dist, &r->m_tables[2]); જો (dist < 16) { r->m_len_codes[counter++] = (mz_uint8)dist; ચાલુ; }
            જો ((dist == 16) && (!counter))
            {
              TINFL_CR_RETURN_FOREVER(17, TINFL_STATUS_FAILED);
            }
            અંક_extra = "\02\03\07"[dist - 16]; TINFL_GET_BITS(18, s, અંક_extra); s += "\03\03\013"[dist - 16];
            TINFL_MEMSET(r->m_len_codes + counter, (dist == 16) ? r->m_len_codes[counter - 1] : 0, s); counter += s;
          }
          જો ((r->m_table_sizes[0] + r->m_table_sizes[1]) != counter)
          {
            TINFL_CR_RETURN_FOREVER(21, TINFL_STATUS_FAILED);
          }
          TINFL_MEMCPY(r->m_tables[0].m_code_size, r->m_len_codes, r->m_table_sizes[0]); TINFL_MEMCPY(r->m_tables[1].m_code_size, r->m_len_codes + r->m_table_sizes[0], r->m_table_sizes[1]);
        }
      }
      માટે ( ; ; )
      {
        mz_uint8 *pSrc;
        માટે ( ; ; )
        {
          જો (((pIn_buf_end - pIn_buf_cur) < 4) || ((pOut_buf_end - pOut_buf_cur) < 2))
          {
            TINFL_HUFF_DECODE(23, counter, &r->m_tables[0]);
            જો (counter >= 256)
              તોડો;
            જ્યારે (pOut_buf_cur >= pOut_buf_end) { TINFL_CR_RETURN(24, TINFL_STATUS_HAS_MORE_OUTPUT); }
            *pOut_buf_cur++ = (mz_uint8)counter;
          }
          નહીંતર
          {
            પૂર્ણાંક sym2; mz_uint code_len;
#જો TINFL_USE_64BIT_BITBUF
            જો (અંક_bits < 30) { bit_buf |= (((tinfl_bit_buf_t)MZ_READ_LE32(pIn_buf_cur)) << અંક_bits); pIn_buf_cur += 4; અંક_bits += 32; }
#નહીંતર
            જો (અંક_bits < 15) { bit_buf |= (((tinfl_bit_buf_t)MZ_READ_LE16(pIn_buf_cur)) << અંક_bits); pIn_buf_cur += 2; અંક_bits += 16; }
#endif
            જો ((sym2 = r->m_tables[0].m_look_up[bit_buf & (TINFL_FAST_LOOKUP_SIZE - 1)]) >= 0)
              code_len = sym2 >> 9;
            નહીંતર
            {
              code_len = TINFL_FAST_LOOKUP_BITS; કરો { sym2 = r->m_tables[0].m_વૃક્ષ[~sym2 + ((bit_buf >> code_len++) & 1)]; } જ્યારે (sym2 < 0);
            }
            counter = sym2; bit_buf >>= code_len; અંક_bits -= code_len;
            જો (counter & 256)
              તોડો;

#જો !TINFL_USE_64BIT_BITBUF
            જો (અંક_bits < 15) { bit_buf |= (((tinfl_bit_buf_t)MZ_READ_LE16(pIn_buf_cur)) << અંક_bits); pIn_buf_cur += 2; અંક_bits += 16; }
#endif
            જો ((sym2 = r->m_tables[0].m_look_up[bit_buf & (TINFL_FAST_LOOKUP_SIZE - 1)]) >= 0)
              code_len = sym2 >> 9;
            નહીંતર
            {
              code_len = TINFL_FAST_LOOKUP_BITS; કરો { sym2 = r->m_tables[0].m_વૃક્ષ[~sym2 + ((bit_buf >> code_len++) & 1)]; } જ્યારે (sym2 < 0);
            }
            bit_buf >>= code_len; અંક_bits -= code_len;

            pOut_buf_cur[0] = (mz_uint8)counter;
            જો (sym2 & 256)
            {
              pOut_buf_cur++;
              counter = sym2;
              તોડો;
            }
            pOut_buf_cur[1] = (mz_uint8)sym2;
            pOut_buf_cur += 2;
          }
        }
        જો ((counter &= 511) == 256) તોડો;

        અંક_extra = s_length_extra[counter - 257]; counter = s_length_base[counter - 257];
        જો (અંક_extra) { mz_uint extra_bits; TINFL_GET_BITS(25, extra_bits, અંક_extra); counter += extra_bits; }

        TINFL_HUFF_DECODE(26, dist, &r->m_tables[1]);
        અંક_extra = s_dist_extra[dist]; dist = s_dist_base[dist];
        જો (અંક_extra) { mz_uint extra_bits; TINFL_GET_BITS(27, extra_bits, અંક_extra); dist += extra_bits; }

        dist_from_out_buf_start = pOut_buf_cur - pOut_buf_start;
        જો ((dist > dist_from_out_buf_start) && (decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF))
        {
          TINFL_CR_RETURN_FOREVER(37, TINFL_STATUS_FAILED);
        }

        pSrc = pOut_buf_start + ((dist_from_out_buf_start - dist) & out_buf_size_mask);

        જો ((MZ_MAX(pOut_buf_cur, pSrc) + counter) > pOut_buf_end)
        {
          જ્યારે (counter--)
          {
            જ્યારે (pOut_buf_cur >= pOut_buf_end) { TINFL_CR_RETURN(53, TINFL_STATUS_HAS_MORE_OUTPUT); }
            *pOut_buf_cur++ = pOut_buf_start[(dist_from_out_buf_start++ - dist) & out_buf_size_mask];
          }
          ચાલુ;
        }
#જો MINIZ_USE_UNALIGNED_LOADS_AND_STORES
        નહીંતર જો ((counter >= 9) && (counter <= dist))
        {
          અચલ mz_uint8 *pSrc_end = pSrc + (counter & ~7);
          કરો
          {
            ((mz_uint32 *)pOut_buf_cur)[0] = ((અચલ mz_uint32 *)pSrc)[0];
            ((mz_uint32 *)pOut_buf_cur)[1] = ((અચલ mz_uint32 *)pSrc)[1];
            pOut_buf_cur += 8;
          } જ્યારે ((pSrc += 8) < pSrc_end);
          જો ((counter &= 7) < 3)
          {
            જો (counter)
            {
              pOut_buf_cur[0] = pSrc[0];
              જો (counter > 1)
                pOut_buf_cur[1] = pSrc[1];
              pOut_buf_cur += counter;
            }
            ચાલુ;
          }
        }
#endif
        કરો
        {
          pOut_buf_cur[0] = pSrc[0];
          pOut_buf_cur[1] = pSrc[1];
          pOut_buf_cur[2] = pSrc[2];
          pOut_buf_cur += 3; pSrc += 3;
        } જ્યારે ((પૂર્ણાંક)(counter -= 3) > 2);
        જો ((પૂર્ણાંક)counter > 0)
        {
          pOut_buf_cur[0] = pSrc[0];
          જો ((પૂર્ણાંક)counter > 1)
            pOut_buf_cur[1] = pSrc[1];
          pOut_buf_cur += counter;
        }
      }
    }
  } જ્યારે (!(r->m_final & 1));
  જો (decomp_flags & TINFL_FLAG_PARSE_ZLIB_HEADER)
  {
    TINFL_SKIP_BITS(32, અંક_bits & 7); માટે (counter = 0; counter < 4; ++counter) { mz_uint s; જો (અંક_bits) TINFL_GET_BITS(41, s, 8); નહીંતર TINFL_GET_BYTE(42, s); r->m_z_adler32 = (r->m_z_adler32 << 8) | s; }
  }
  TINFL_CR_RETURN_FOREVER(34, TINFL_STATUS_DONE);
  TINFL_CR_FINISH

common_exit:
  r->m_અંક_bits = અંક_bits; r->m_bit_buf = bit_buf; r->m_dist = dist; r->m_counter = counter; r->m_અંક_extra = અંક_extra; r->m_dist_from_out_buf_start = dist_from_out_buf_start;
  *pIn_buf_size = pIn_buf_cur - pIn_buf_next; *pOut_buf_size = pOut_buf_cur - pOut_buf_next;
  જો ((decomp_flags & (TINFL_FLAG_PARSE_ZLIB_HEADER | TINFL_FLAG_COMPUTE_ADLER32)) && (status >= 0))
  {
    અચલ mz_uint8 *ptr = pOut_buf_next; size_t buf_len = *pOut_buf_size;
    mz_uint32 i, s1 = r->m_check_adler32 & 0xffff, s2 = r->m_check_adler32 >> 16; size_t block_len = buf_len % 5552;
    જ્યારે (buf_len)
    {
      માટે (i = 0; i + 7 < block_len; i += 8, ptr += 8)
      {
        s1 += ptr[0], s2 += s1; s1 += ptr[1], s2 += s1; s1 += ptr[2], s2 += s1; s1 += ptr[3], s2 += s1;
        s1 += ptr[4], s2 += s1; s1 += ptr[5], s2 += s1; s1 += ptr[6], s2 += s1; s1 += ptr[7], s2 += s1;
      }
      માટે ( ; i < block_len; ++i) s1 += *ptr++, s2 += s1;
      s1 %= 65521U, s2 %= 65521U; buf_len -= block_len; block_len = 5552;
    }
    r->m_check_adler32 = (s2 << 16) + s1; જો ((status == TINFL_STATUS_DONE) && (decomp_flags & TINFL_FLAG_PARSE_ZLIB_HEADER) && (r->m_check_adler32 != r->m_z_adler32)) status = TINFL_STATUS_ADLER32_MISMATCH;
  }
  પાછા status;
}

// Higher level helper functions.
શૂન્ય *tinfl_decompress_mem_to_heap(અચલ શૂન્ય *pSrc_buf, size_t src_buf_len, size_t *pOut_len, પૂર્ણાંક flags)
{
  tinfl_decompressor decomp; શૂન્ય *pBuf = ખાલી, *pNew_buf; size_t src_buf_ofs = 0, out_buf_capacity = 0;
  *pOut_len = 0;
  tinfl_init(&decomp);
  માટે ( ; ; )
  {
    size_t src_buf_size = src_buf_len - src_buf_ofs, dst_buf_size = out_buf_capacity - *pOut_len, new_out_buf_capacity;
    tinfl_status status = tinfl_decompress(&decomp, (અચલ mz_uint8*)pSrc_buf + src_buf_ofs, &src_buf_size, (mz_uint8*)pBuf, pBuf ? (mz_uint8*)pBuf + *pOut_len : ખાલી, &dst_buf_size,
      (flags & ~TINFL_FLAG_HAS_MORE_આગત) | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF);
    જો ((status < 0) || (status == TINFL_STATUS_NEEDS_MORE_આગત))
    {
      MZ_FREE(pBuf); *pOut_len = 0; પાછા ખાલી;
    }
    src_buf_ofs += src_buf_size;
    *pOut_len += dst_buf_size;
    જો (status == TINFL_STATUS_DONE) તોડો;
    new_out_buf_capacity = out_buf_capacity * 2; જો (new_out_buf_capacity < 128) new_out_buf_capacity = 128;
    pNew_buf = MZ_REALLOC(pBuf, new_out_buf_capacity);
    જો (!pNew_buf)
    {
      MZ_FREE(pBuf); *pOut_len = 0; પાછા ખાલી;
    }
    pBuf = pNew_buf; out_buf_capacity = new_out_buf_capacity;
  }
  પાછા pBuf;
}

size_t tinfl_decompress_mem_to_mem(શૂન્ય *pOut_buf, size_t out_buf_len, અચલ શૂન્ય *pSrc_buf, size_t src_buf_len, પૂર્ણાંક flags)
{
  tinfl_decompressor decomp; tinfl_status status; tinfl_init(&decomp);
  status = tinfl_decompress(&decomp, (અચલ mz_uint8*)pSrc_buf, &src_buf_len, (mz_uint8*)pOut_buf, (mz_uint8*)pOut_buf, &out_buf_len, (flags & ~TINFL_FLAG_HAS_MORE_આગત) | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF);
  પાછા (status != TINFL_STATUS_DONE) ? TINFL_DECOMPRESS_MEM_TO_MEM_FAILED : out_buf_len;
}

પૂર્ણાંક tinfl_decompress_mem_to_callback(અચલ શૂન્ય *pIn_buf, size_t *pIn_buf_size, tinfl_put_buf_func_ptr pPut_buf_func, શૂન્ય *pPut_buf_user, પૂર્ણાંક flags)
{
  પૂર્ણાંક result = 0;
  tinfl_decompressor decomp;
  mz_uint8 *pDict = (mz_uint8*)MZ_MALLOC(TINFL_LZ_DICT_SIZE); size_t in_buf_ofs = 0, dict_ofs = 0;
  જો (!pDict)
    પાછા TINFL_STATUS_FAILED;
  memset(pDict,0,TINFL_LZ_DICT_SIZE);
  tinfl_init(&decomp);
  માટે ( ; ; )
  {
    size_t in_buf_size = *pIn_buf_size - in_buf_ofs, dst_buf_size = TINFL_LZ_DICT_SIZE - dict_ofs;
    tinfl_status status = tinfl_decompress(&decomp, (અચલ mz_uint8*)pIn_buf + in_buf_ofs, &in_buf_size, pDict, pDict + dict_ofs, &dst_buf_size,
      (flags & ~(TINFL_FLAG_HAS_MORE_આગત | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF)));
    in_buf_ofs += in_buf_size;
    જો ((dst_buf_size) && (!(*pPut_buf_func)(pDict + dict_ofs, (પૂર્ણાંક)dst_buf_size, pPut_buf_user)))
      તોડો;
    જો (status != TINFL_STATUS_HAS_MORE_OUTPUT)
    {
      result = (status == TINFL_STATUS_DONE);
      તોડો;
    }
    dict_ofs = (dict_ofs + dst_buf_size) & (TINFL_LZ_DICT_SIZE - 1);
  }
  MZ_FREE(pDict);
  *pIn_buf_size = in_buf_ofs;
  પાછા result;
}
#endif /*#ifndef MINIZ_NO_INFLATE_APIS*/

// ------------------- Low-level Compression (independent from all decompression API's)
#ifndef MINIZ_NO_DEFLATE_APIS

// Purposely making these tables static for faster init and thread safety.
સ્થિર અચલ mz_uint16 s_tdefl_len_sym[256] = {
  257,258,259,260,261,262,263,264,265,265,266,266,267,267,268,268,269,269,269,269,270,270,270,270,271,271,271,271,272,272,272,272,
  273,273,273,273,273,273,273,273,274,274,274,274,274,274,274,274,275,275,275,275,275,275,275,275,276,276,276,276,276,276,276,276,
  277,277,277,277,277,277,277,277,277,277,277,277,277,277,277,277,278,278,278,278,278,278,278,278,278,278,278,278,278,278,278,278,
  279,279,279,279,279,279,279,279,279,279,279,279,279,279,279,279,280,280,280,280,280,280,280,280,280,280,280,280,280,280,280,280,
  281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,
  282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,
  283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,
  284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,285 };

સ્થિર અચલ mz_uint8 s_tdefl_len_extra[256] = {
  0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0 };

સ્થિર અચલ mz_uint8 s_tdefl_small_dist_sym[512] = {
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

સ્થિર અચલ mz_uint8 s_tdefl_small_dist_extra[512] = {
  0,0,0,0,1,1,1,1,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
  6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
  6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7 };

સ્થિર અચલ mz_uint8 s_tdefl_large_dist_sym[128] = {
  0,0,18,19,20,20,21,21,22,22,22,22,23,23,23,23,24,24,24,24,24,24,24,24,25,25,25,25,25,25,25,25,26,26,26,26,26,26,26,26,26,26,26,26,
  26,26,26,26,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,
  28,28,28,28,28,28,28,28,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29 };

સ્થિર અચલ mz_uint8 s_tdefl_large_dist_extra[128] = {
  0,0,8,8,9,9,9,9,10,10,10,10,10,10,10,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,
  12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
  13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13 };

// Radix sorts tdefl_sym_freq[] array by 16-bit key m_key. Returns ptr to sorted values.
પ્રકારવ્યાખ્યા સંરચના { mz_uint16 m_ચાવી, m_sym_index; } tdefl_sym_freq;
સ્થિર tdefl_sym_freq* tdefl_radix_sort_syms(mz_uint અંક_syms, tdefl_sym_freq* pSyms0, tdefl_sym_freq* pSyms1)
{
  mz_uint32 total_passes = 2, pass_shift, pass, i, hist[256 * 2]; tdefl_sym_freq* pCur_syms = pSyms0, *pNew_syms = pSyms1; MZ_CLEAR_ARR(hist);
  માટે (i = 0; i < અંક_syms; i++) { mz_uint freq = pSyms0[i].m_ચાવી; hist[freq & 0xFF]++; hist[256 + ((freq >> 8) & 0xFF)]++; }
  જ્યારે ((total_passes > 1) && (અંક_syms == hist[(total_passes - 1) * 256])) total_passes--;
  માટે (pass_shift = 0, pass = 0; pass < total_passes; pass++, pass_shift += 8)
  {
    અચલ mz_uint32* pHist = &hist[pass << 8];
    mz_uint offsets[256], cur_ofs = 0;
    માટે (i = 0; i < 256; i++) { offsets[i] = cur_ofs; cur_ofs += pHist[i]; }
    માટે (i = 0; i < અંક_syms; i++) pNew_syms[offsets[(pCur_syms[i].m_ચાવી >> pass_shift) & 0xFF]++] = pCur_syms[i];
    { tdefl_sym_freq* t = pCur_syms; pCur_syms = pNew_syms; pNew_syms = t; }
  }
  પાછા pCur_syms;
}

// tdefl_calculate_minimum_redundancy() originally written by: Alistair Moffat, alistair@cs.mu.oz.au, Jyrki Katajainen, jyrki@diku.dk, November 1996.
સ્થિર શૂન્ય tdefl_calculate_minimum_redundancy(tdefl_sym_freq *A, પૂર્ણાંક n)
{
  પૂર્ણાંક મૂળ, leaf, next, avbl, used, dpth;
  જો (n==0) પાછા; નહીંતર જો (n==1) { A[0].m_ચાવી = 1; પાછા; }
  A[0].m_ચાવી += A[1].m_ચાવી; મૂળ = 0; leaf = 2;
  માટે (next=1; next < n-1; next++)
  {
    જો (leaf>=n || A[મૂળ].m_ચાવી<A[leaf].m_ચાવી) { A[next].m_ચાવી = A[મૂળ].m_ચાવી; A[મૂળ++].m_ચાવી = (mz_uint16)next; } નહીંતર A[next].m_ચાવી = A[leaf++].m_ચાવી;
    જો (leaf>=n || (મૂળ<next && A[મૂળ].m_ચાવી<A[leaf].m_ચાવી)) { A[next].m_ચાવી = (mz_uint16)(A[next].m_ચાવી + A[મૂળ].m_ચાવી); A[મૂળ++].m_ચાવી = (mz_uint16)next; } નહીંતર A[next].m_ચાવી = (mz_uint16)(A[next].m_ચાવી + A[leaf++].m_ચાવી);
  }
  A[n-2].m_ચાવી = 0; માટે (next=n-3; next>=0; next--) A[next].m_ચાવી = A[A[next].m_ચાવી].m_ચાવી+1;
  avbl = 1; used = dpth = 0; મૂળ = n-2; next = n-1;
  જ્યારે (avbl>0)
  {
    જ્યારે (મૂળ>=0 && (પૂર્ણાંક)A[મૂળ].m_ચાવી==dpth) { used++; મૂળ--; }
    જ્યારે (avbl>used) { A[next--].m_ચાવી = (mz_uint16)(dpth); avbl--; }
    avbl = 2*used; dpth++; used = 0;
  }
}

// Limits canonical Huffman code table's max code size.
ગણના { TDEFL_MAX_SUPPORTED_HUFF_CODESIZE = 32 };
સ્થિર શૂન્ય tdefl_huffman_enforce_max_code_size(પૂર્ણાંક *p_અંક_codes, પૂર્ણાંક code_list_len, પૂર્ણાંક max_code_size)
{
  પૂર્ણાંક i; mz_uint32 total = 0; જો (code_list_len <= 1) પાછા;
  માટે (i = max_code_size + 1; i <= TDEFL_MAX_SUPPORTED_HUFF_CODESIZE; i++) p_અંક_codes[max_code_size] += p_અંક_codes[i];
  માટે (i = max_code_size; i > 0; i--) total += (((mz_uint32)p_અંક_codes[i]) << (max_code_size - i));
  જ્યારે (total != (1UL << max_code_size))
  {
    p_અંક_codes[max_code_size]--;
    માટે (i = max_code_size - 1; i > 0; i--) જો (p_અંક_codes[i]) { p_અંક_codes[i]--; p_અંક_codes[i + 1] += 2; તોડો; }
    total--;
  }
}

સ્થિર શૂન્ય tdefl_optimize_huffman_table(tdefl_compressor *d, પૂર્ણાંક table_અંક, પૂર્ણાંક table_len, પૂર્ણાંક code_size_limit, પૂર્ણાંક static_table)
{
  પૂર્ણાંક i, j, l, અંક_codes[1 + TDEFL_MAX_SUPPORTED_HUFF_CODESIZE]; mz_uint next_code[TDEFL_MAX_SUPPORTED_HUFF_CODESIZE + 1]; MZ_CLEAR_ARR(અંક_codes);
  જો (static_table)
  {
    માટે (i = 0; i < table_len; i++) અંક_codes[d->m_huff_code_sizes[table_અંક][i]]++;
  }
  નહીંતર
  {
    tdefl_sym_freq syms0[TDEFL_MAX_HUFF_SYMBOLS], syms1[TDEFL_MAX_HUFF_SYMBOLS], *pSyms;
    પૂર્ણાંક અંક_used_syms = 0;
    અચલ mz_uint16 *p_Sym_ગણતરી = &d->m_huff_ગણતરી[table_અંક][0];
    માટે (i = 0; i < table_len; i++) જો (p_Sym_ગણતરી[i]) { syms0[અંક_used_syms].m_ચાવી = (mz_uint16)p_Sym_ગણતરી[i]; syms0[અંક_used_syms++].m_sym_index = (mz_uint16)i; }

    pSyms = tdefl_radix_sort_syms(અંક_used_syms, syms0, syms1); tdefl_calculate_minimum_redundancy(pSyms, અંક_used_syms);

    માટે (i = 0; i < અંક_used_syms; i++) અંક_codes[pSyms[i].m_ચાવી]++;

    tdefl_huffman_enforce_max_code_size(અંક_codes, અંક_used_syms, code_size_limit);

    MZ_CLEAR_ARR(d->m_huff_code_sizes[table_અંક]); MZ_CLEAR_ARR(d->m_huff_codes[table_અંક]);
    માટે (i = 1, j = અંક_used_syms; i <= code_size_limit; i++)
      માટે (l = અંક_codes[i]; l > 0; l--) d->m_huff_code_sizes[table_અંક][pSyms[--j].m_sym_index] = (mz_uint8)(i);
  }

  next_code[1] = 0; માટે (j = 0, i = 2; i <= code_size_limit; i++) next_code[i] = j = ((j + અંક_codes[i - 1]) << 1);

  માટે (i = 0; i < table_len; i++)
  {
    mz_uint rev_code = 0, code, code_size; જો ((code_size = d->m_huff_code_sizes[table_અંક][i]) == 0) ચાલુ;
    code = next_code[code_size]++; માટે (l = code_size; l > 0; l--, code >>= 1) rev_code = (rev_code << 1) | (code & 1);
    d->m_huff_codes[table_અંક][i] = (mz_uint16)rev_code;
  }
}

#define TDEFL_PUT_BITS(b, l) કરો { \
  mz_uint bits = b; mz_uint len = l; MZ_ASSERT(bits <= ((1U << len) - 1U)); \
  d->m_bit_buffer |= (bits << d->m_bits_in); d->m_bits_in += len; \
  જ્યારે (d->m_bits_in >= 8) { \
    જો (d->m_pOutput_buf < d->m_pOutput_buf_end) \
      *d->m_pOutput_buf++ = (mz_uint8)(d->m_bit_buffer); \
    d->m_bit_buffer >>= 8; \
    d->m_bits_in -= 8; \
  } \
} MZ_MACRO_END

#define TDEFL_RLE_PREV_CODE_SIZE() કરો { \
  જો (rle_repeat_ગણતરી) { \
    જો (rle_repeat_ગણતરી < 3) { \
      d->m_huff_ગણતરી[2][prev_code_size] = (mz_uint16)(d->m_huff_ગણતરી[2][prev_code_size] + rle_repeat_ગણતરી); \
      જ્યારે (rle_repeat_ગણતરી--) packed_code_sizes[અંક_packed_code_sizes++] = prev_code_size; \
    } નહીંતર { \
      d->m_huff_ગણતરી[2][16] = (mz_uint16)(d->m_huff_ગણતરી[2][16] + 1); packed_code_sizes[અંક_packed_code_sizes++] = 16; packed_code_sizes[અંક_packed_code_sizes++] = (mz_uint8)(rle_repeat_ગણતરી - 3); \
  } rle_repeat_ગણતરી = 0; } \
} MZ_MACRO_END

#define TDEFL_RLE_ZERO_CODE_SIZE() કરો { \
  જો (rle_z_ગણતરી) { \
    જો (rle_z_ગણતરી < 3) { \
      d->m_huff_ગણતરી[2][0] = (mz_uint16)(d->m_huff_ગણતરી[2][0] + rle_z_ગણતરી); જ્યારે (rle_z_ગણતરી--) packed_code_sizes[અંક_packed_code_sizes++] = 0; \
    } નહીંતર જો (rle_z_ગણતરી <= 10) { \
      d->m_huff_ગણતરી[2][17] = (mz_uint16)(d->m_huff_ગણતરી[2][17] + 1); packed_code_sizes[અંક_packed_code_sizes++] = 17; packed_code_sizes[અંક_packed_code_sizes++] = (mz_uint8)(rle_z_ગણતરી - 3); \
    } નહીંતર { \
      d->m_huff_ગણતરી[2][18] = (mz_uint16)(d->m_huff_ગણતરી[2][18] + 1); packed_code_sizes[અંક_packed_code_sizes++] = 18; packed_code_sizes[અંક_packed_code_sizes++] = (mz_uint8)(rle_z_ગણતરી - 11); \
  } rle_z_ગણતરી = 0; } \
} MZ_MACRO_END

સ્થિર mz_uint8 s_tdefl_packed_code_size_syms_swizzle[] = { 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 };

સ્થિર શૂન્ય tdefl_start_dynamic_block(tdefl_compressor *d)
{
  પૂર્ણાંક અંક_lit_codes, અંક_dist_codes, અંક_bit_lengths; mz_uint i, total_code_sizes_to_pack, અંક_packed_code_sizes, rle_z_ગણતરી, rle_repeat_ગણતરી, packed_code_sizes_index;
  mz_uint8 code_sizes_to_pack[TDEFL_MAX_HUFF_SYMBOLS_0 + TDEFL_MAX_HUFF_SYMBOLS_1], packed_code_sizes[TDEFL_MAX_HUFF_SYMBOLS_0 + TDEFL_MAX_HUFF_SYMBOLS_1], prev_code_size = 0xFF;

  d->m_huff_ગણતરી[0][256] = 1;

  tdefl_optimize_huffman_table(d, 0, TDEFL_MAX_HUFF_SYMBOLS_0, 15, MZ_FALSE);
  tdefl_optimize_huffman_table(d, 1, TDEFL_MAX_HUFF_SYMBOLS_1, 15, MZ_FALSE);

  માટે (અંક_lit_codes = 286; અંક_lit_codes > 257; અંક_lit_codes--) જો (d->m_huff_code_sizes[0][અંક_lit_codes - 1]) તોડો;
  માટે (અંક_dist_codes = 30; અંક_dist_codes > 1; અંક_dist_codes--) જો (d->m_huff_code_sizes[1][અંક_dist_codes - 1]) તોડો;

  memcpy(code_sizes_to_pack, &d->m_huff_code_sizes[0][0], અંક_lit_codes);
  memcpy(code_sizes_to_pack + અંક_lit_codes, &d->m_huff_code_sizes[1][0], અંક_dist_codes);
  total_code_sizes_to_pack = અંક_lit_codes + અંક_dist_codes; અંક_packed_code_sizes = 0; rle_z_ગણતરી = 0; rle_repeat_ગણતરી = 0;

  memset(&d->m_huff_ગણતરી[2][0], 0, કદ(d->m_huff_ગણતરી[2][0]) * TDEFL_MAX_HUFF_SYMBOLS_2);
  માટે (i = 0; i < total_code_sizes_to_pack; i++)
  {
    mz_uint8 code_size = code_sizes_to_pack[i];
    જો (!code_size)
    {
      TDEFL_RLE_PREV_CODE_SIZE();
      જો (++rle_z_ગણતરી == 138) { TDEFL_RLE_ZERO_CODE_SIZE(); }
    }
    નહીંતર
    {
      TDEFL_RLE_ZERO_CODE_SIZE();
      જો (code_size != prev_code_size)
      {
        TDEFL_RLE_PREV_CODE_SIZE();
        d->m_huff_ગણતરી[2][code_size] = (mz_uint16)(d->m_huff_ગણતરી[2][code_size] + 1); packed_code_sizes[અંક_packed_code_sizes++] = code_size;
      }
      નહીંતર જો (++rle_repeat_ગણતરી == 6)
      {
        TDEFL_RLE_PREV_CODE_SIZE();
      }
    }
    prev_code_size = code_size;
  }
  જો (rle_repeat_ગણતરી) { TDEFL_RLE_PREV_CODE_SIZE(); } નહીંતર { TDEFL_RLE_ZERO_CODE_SIZE(); }

  tdefl_optimize_huffman_table(d, 2, TDEFL_MAX_HUFF_SYMBOLS_2, 7, MZ_FALSE);

  TDEFL_PUT_BITS(2, 2);

  TDEFL_PUT_BITS(અંક_lit_codes - 257, 5);
  TDEFL_PUT_BITS(અંક_dist_codes - 1, 5);

  માટે (અંક_bit_lengths = 18; અંક_bit_lengths >= 0; અંક_bit_lengths--) જો (d->m_huff_code_sizes[2][s_tdefl_packed_code_size_syms_swizzle[અંક_bit_lengths]]) તોડો;
  અંક_bit_lengths = MZ_MAX(4, (અંક_bit_lengths + 1)); TDEFL_PUT_BITS(અંક_bit_lengths - 4, 4);
  માટે (i = 0; (પૂર્ણાંક)i < અંક_bit_lengths; i++) TDEFL_PUT_BITS(d->m_huff_code_sizes[2][s_tdefl_packed_code_size_syms_swizzle[i]], 3);

  માટે (packed_code_sizes_index = 0; packed_code_sizes_index < અંક_packed_code_sizes; )
  {
    mz_uint code = packed_code_sizes[packed_code_sizes_index++]; MZ_ASSERT(code < TDEFL_MAX_HUFF_SYMBOLS_2);
    TDEFL_PUT_BITS(d->m_huff_codes[2][code], d->m_huff_code_sizes[2][code]);
    જો (code >= 16) TDEFL_PUT_BITS(packed_code_sizes[packed_code_sizes_index++], "\02\03\07"[code - 16]);
  }
}

સ્થિર શૂન્ય tdefl_start_static_block(tdefl_compressor *d)
{
  mz_uint i;
  mz_uint8 *p = &d->m_huff_code_sizes[0][0];

  માટે (i = 0; i <= 143; ++i) *p++ = 8;
  માટે ( ; i <= 255; ++i) *p++ = 9;
  માટે ( ; i <= 279; ++i) *p++ = 7;
  માટે ( ; i <= 287; ++i) *p++ = 8;

  memset(d->m_huff_code_sizes[1], 5, 32);

  tdefl_optimize_huffman_table(d, 0, 288, 15, MZ_TRUE);
  tdefl_optimize_huffman_table(d, 1, 32, 15, MZ_TRUE);

  TDEFL_PUT_BITS(1, 2);
}

સ્થિર અચલ mz_uint mz_bitmasks[17] = { 0x0000, 0x0001, 0x0003, 0x0007, 0x000F, 0x001F, 0x003F, 0x007F, 0x00FF, 0x01FF, 0x03FF, 0x07FF, 0x0FFF, 0x1FFF, 0x3FFF, 0x7FFF, 0xFFFF };

#જો MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN && MINIZ_HAS_64BIT_REGISTERS
સ્થિર mz_bool tdefl_compress_lz_codes(tdefl_compressor *d)
{
  mz_uint flags;
  mz_uint8 *pLZ_codes;
  mz_uint8 *pOutput_buf = d->m_pOutput_buf;
  mz_uint8 *pLZ_code_buf_end = d->m_pLZ_code_buf;
  mz_uint64 bit_buffer = d->m_bit_buffer;
  mz_uint bits_in = d->m_bits_in;

#define TDEFL_PUT_BITS_FAST(b, l) { bit_buffer |= (((mz_uint64)(b)) << bits_in); bits_in += (l); }

  flags = 1;
  માટે (pLZ_codes = d->m_lz_code_buf; pLZ_codes < pLZ_code_buf_end; flags >>= 1)
  {
    જો (flags == 1)
      flags = *pLZ_codes++ | 0x100;

    જો (flags & 1)
    {
      mz_uint s0, s1, n0, n1, sym, અંક_extra_bits;
      mz_uint match_len = pLZ_codes[0], match_dist = *(અચલ mz_uint16 *)(pLZ_codes + 1); pLZ_codes += 3;

      MZ_ASSERT(d->m_huff_code_sizes[0][s_tdefl_len_sym[match_len]]);
      TDEFL_PUT_BITS_FAST(d->m_huff_codes[0][s_tdefl_len_sym[match_len]], d->m_huff_code_sizes[0][s_tdefl_len_sym[match_len]]);
      TDEFL_PUT_BITS_FAST(match_len & mz_bitmasks[s_tdefl_len_extra[match_len]], s_tdefl_len_extra[match_len]);

      // This sequence coaxes MSVC into using cmov's vs. jmp's.
      s0 = s_tdefl_small_dist_sym[match_dist & 511];
      n0 = s_tdefl_small_dist_extra[match_dist & 511];
      s1 = s_tdefl_large_dist_sym[match_dist >> 8];
      n1 = s_tdefl_large_dist_extra[match_dist >> 8];
      sym = (match_dist < 512) ? s0 : s1;
      અંક_extra_bits = (match_dist < 512) ? n0 : n1;

      MZ_ASSERT(d->m_huff_code_sizes[1][sym]);
      TDEFL_PUT_BITS_FAST(d->m_huff_codes[1][sym], d->m_huff_code_sizes[1][sym]);
      TDEFL_PUT_BITS_FAST(match_dist & mz_bitmasks[અંક_extra_bits], અંક_extra_bits);
    }
    નહીંતર
    {
      mz_uint lit = *pLZ_codes++;
      MZ_ASSERT(d->m_huff_code_sizes[0][lit]);
      TDEFL_PUT_BITS_FAST(d->m_huff_codes[0][lit], d->m_huff_code_sizes[0][lit]);

      જો (((flags & 2) == 0) && (pLZ_codes < pLZ_code_buf_end))
      {
        flags >>= 1;
        lit = *pLZ_codes++;
        MZ_ASSERT(d->m_huff_code_sizes[0][lit]);
        TDEFL_PUT_BITS_FAST(d->m_huff_codes[0][lit], d->m_huff_code_sizes[0][lit]);

        જો (((flags & 2) == 0) && (pLZ_codes < pLZ_code_buf_end))
        {
          flags >>= 1;
          lit = *pLZ_codes++;
          MZ_ASSERT(d->m_huff_code_sizes[0][lit]);
          TDEFL_PUT_BITS_FAST(d->m_huff_codes[0][lit], d->m_huff_code_sizes[0][lit]);
        }
      }
    }

    જો (pOutput_buf >= d->m_pOutput_buf_end)
      પાછા MZ_FALSE;

    *(mz_uint64*)pOutput_buf = bit_buffer;
    pOutput_buf += (bits_in >> 3);
    bit_buffer >>= (bits_in & ~7);
    bits_in &= 7;
  }

#undef TDEFL_PUT_BITS_FAST

  d->m_pOutput_buf = pOutput_buf;
  d->m_bits_in = 0;
  d->m_bit_buffer = 0;

  જ્યારે (bits_in)
  {
    mz_uint32 n = MZ_MIN(bits_in, 16);
    TDEFL_PUT_BITS((mz_uint)bit_buffer & mz_bitmasks[n], n);
    bit_buffer >>= n;
    bits_in -= n;
  }

  TDEFL_PUT_BITS(d->m_huff_codes[0][256], d->m_huff_code_sizes[0][256]);

  પાછા (d->m_pOutput_buf < d->m_pOutput_buf_end);
}
#નહીંતર
સ્થિર mz_bool tdefl_compress_lz_codes(tdefl_compressor *d)
{
  mz_uint flags;
  mz_uint8 *pLZ_codes;

  flags = 1;
  માટે (pLZ_codes = d->m_lz_code_buf; pLZ_codes < d->m_pLZ_code_buf; flags >>= 1)
  {
    જો (flags == 1)
      flags = *pLZ_codes++ | 0x100;
    જો (flags & 1)
    {
      mz_uint sym, અંક_extra_bits;
      mz_uint match_len = pLZ_codes[0], match_dist = (pLZ_codes[1] | (pLZ_codes[2] << 8)); pLZ_codes += 3;

      MZ_ASSERT(d->m_huff_code_sizes[0][s_tdefl_len_sym[match_len]]);
      TDEFL_PUT_BITS(d->m_huff_codes[0][s_tdefl_len_sym[match_len]], d->m_huff_code_sizes[0][s_tdefl_len_sym[match_len]]);
      TDEFL_PUT_BITS(match_len & mz_bitmasks[s_tdefl_len_extra[match_len]], s_tdefl_len_extra[match_len]);

      જો (match_dist < 512)
      {
        sym = s_tdefl_small_dist_sym[match_dist]; અંક_extra_bits = s_tdefl_small_dist_extra[match_dist];
      }
      નહીંતર
      {
        sym = s_tdefl_large_dist_sym[match_dist >> 8]; અંક_extra_bits = s_tdefl_large_dist_extra[match_dist >> 8];
      }
      MZ_ASSERT(d->m_huff_code_sizes[1][sym]);
      TDEFL_PUT_BITS(d->m_huff_codes[1][sym], d->m_huff_code_sizes[1][sym]);
      TDEFL_PUT_BITS(match_dist & mz_bitmasks[અંક_extra_bits], અંક_extra_bits);
    }
    નહીંતર
    {
      mz_uint lit = *pLZ_codes++;
      MZ_ASSERT(d->m_huff_code_sizes[0][lit]);
      TDEFL_PUT_BITS(d->m_huff_codes[0][lit], d->m_huff_code_sizes[0][lit]);
    }
  }

  TDEFL_PUT_BITS(d->m_huff_codes[0][256], d->m_huff_code_sizes[0][256]);

  પાછા (d->m_pOutput_buf < d->m_pOutput_buf_end);
}
#endif // MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN && MINIZ_HAS_64BIT_REGISTERS

સ્થિર mz_bool tdefl_compress_block(tdefl_compressor *d, mz_bool static_block)
{
  જો (static_block)
    tdefl_start_static_block(d);
  નહીંતર
    tdefl_start_dynamic_block(d);
  પાછા tdefl_compress_lz_codes(d);
}

સ્થિર પૂર્ણાંક tdefl_flush_block(tdefl_compressor *d, પૂર્ણાંક flush)
{
  mz_uint saved_bit_buf, saved_bits_in;
  mz_uint8 *pSaved_output_buf;
  mz_bool comp_block_succeeded = MZ_FALSE;
  પૂર્ણાંક n, use_raw_block = ((d->m_flags & TDEFL_FORCE_ALL_RAW_BLOCKS) != 0) && (d->m_lookahead_pos - d->m_lz_code_buf_dict_pos) <= d->m_dict_size;
  mz_uint8 *pOutput_buf_start = ((d->m_pPut_buf_func == ખાલી) && ((*d->m_pOut_buf_size - d->m_out_buf_ofs) >= TDEFL_OUT_BUF_SIZE)) ? ((mz_uint8 *)d->m_pOut_buf + d->m_out_buf_ofs) : d->m_output_buf;

  d->m_pOutput_buf = pOutput_buf_start;
  d->m_pOutput_buf_end = d->m_pOutput_buf + TDEFL_OUT_BUF_SIZE - 16;

  MZ_ASSERT(!d->m_output_flush_remaining);
  d->m_output_flush_ofs = 0;
  d->m_output_flush_remaining = 0;

  *d->m_pLZ_flags = (mz_uint8)(*d->m_pLZ_flags >> d->m_અંક_flags_ડાબું);
  d->m_pLZ_code_buf -= (d->m_અંક_flags_ડાબું == 8);

  જો ((d->m_flags & TDEFL_WRITE_ZLIB_HEADER) && (!d->m_block_index))
  {
    TDEFL_PUT_BITS(0x78, 8); TDEFL_PUT_BITS(0x01, 8);
  }

  TDEFL_PUT_BITS(flush == TDEFL_FINISH, 1);

  pSaved_output_buf = d->m_pOutput_buf; saved_bit_buf = d->m_bit_buffer; saved_bits_in = d->m_bits_in;

  જો (!use_raw_block)
    comp_block_succeeded = tdefl_compress_block(d, (d->m_flags & TDEFL_FORCE_ALL_STATIC_BLOCKS) || (d->m_total_lz_bytes < 48));

  // If the block gets expanded, forget the current contents of the output buffer and send a raw block instead.
  જો ( ((use_raw_block) || ((d->m_total_lz_bytes) && ((d->m_pOutput_buf - pSaved_output_buf + 1U) >= d->m_total_lz_bytes))) &&
       ((d->m_lookahead_pos - d->m_lz_code_buf_dict_pos) <= d->m_dict_size) )
  {
    mz_uint i; d->m_pOutput_buf = pSaved_output_buf; d->m_bit_buffer = saved_bit_buf; d->m_bits_in = saved_bits_in;
    TDEFL_PUT_BITS(0, 2);
    જો (d->m_bits_in) { TDEFL_PUT_BITS(0, 8 - d->m_bits_in); }
    માટે (i = 2; i; --i, d->m_total_lz_bytes ^= 0xFFFF)
    {
      TDEFL_PUT_BITS(d->m_total_lz_bytes & 0xFFFF, 16);
    }
    માટે (i = 0; i < d->m_total_lz_bytes; ++i)
    {
      TDEFL_PUT_BITS(d->m_dict[(d->m_lz_code_buf_dict_pos + i) & TDEFL_LZ_DICT_SIZE_MASK], 8);
    }
  }
  // Check for the extremely unlikely (if not impossible) case of the compressed block not fitting into the output buffer when using dynamic codes.
  નહીંતર જો (!comp_block_succeeded)
  {
    d->m_pOutput_buf = pSaved_output_buf; d->m_bit_buffer = saved_bit_buf; d->m_bits_in = saved_bits_in;
    tdefl_compress_block(d, MZ_TRUE);
  }

  જો (flush)
  {
    જો (flush == TDEFL_FINISH)
    {
      જો (d->m_bits_in) { TDEFL_PUT_BITS(0, 8 - d->m_bits_in); }
      જો (d->m_flags & TDEFL_WRITE_ZLIB_HEADER) { mz_uint i, a = d->m_adler32; માટે (i = 0; i < 4; i++) { TDEFL_PUT_BITS((a >> 24) & 0xFF, 8); a <<= 8; } }
    }
    નહીંતર
    {
      mz_uint i, z = 0; TDEFL_PUT_BITS(0, 3); જો (d->m_bits_in) { TDEFL_PUT_BITS(0, 8 - d->m_bits_in); } માટે (i = 2; i; --i, z ^= 0xFFFF) { TDEFL_PUT_BITS(z & 0xFFFF, 16); }
    }
  }

  MZ_ASSERT(d->m_pOutput_buf < d->m_pOutput_buf_end);

  memset(&d->m_huff_ગણતરી[0][0], 0, કદ(d->m_huff_ગણતરી[0][0]) * TDEFL_MAX_HUFF_SYMBOLS_0);
  memset(&d->m_huff_ગણતરી[1][0], 0, કદ(d->m_huff_ગણતરી[1][0]) * TDEFL_MAX_HUFF_SYMBOLS_1);

  d->m_pLZ_code_buf = d->m_lz_code_buf + 1; d->m_pLZ_flags = d->m_lz_code_buf; d->m_અંક_flags_ડાબું = 8; d->m_lz_code_buf_dict_pos += d->m_total_lz_bytes; d->m_total_lz_bytes = 0; d->m_block_index++;

  જો ((n = (પૂર્ણાંક)(d->m_pOutput_buf - pOutput_buf_start)) != 0)
  {
    જો (d->m_pPut_buf_func)
    {
      *d->m_pIn_buf_size = d->m_pSrc - (અચલ mz_uint8 *)d->m_pIn_buf;
      જો (!(*d->m_pPut_buf_func)(d->m_output_buf, n, d->m_pPut_buf_user))
        પાછા (d->m_prev_return_status = TDEFL_STATUS_PUT_BUF_FAILED);
    }
    નહીંતર જો (pOutput_buf_start == d->m_output_buf)
    {
      પૂર્ણાંક bytes_to_copy = (પૂર્ણાંક)MZ_MIN((size_t)n, (size_t)(*d->m_pOut_buf_size - d->m_out_buf_ofs));
      memcpy((mz_uint8 *)d->m_pOut_buf + d->m_out_buf_ofs, d->m_output_buf, bytes_to_copy);
      d->m_out_buf_ofs += bytes_to_copy;
      જો ((n -= bytes_to_copy) != 0)
      {
        d->m_output_flush_ofs = bytes_to_copy;
        d->m_output_flush_remaining = n;
      }
    }
    નહીંતર
    {
      d->m_out_buf_ofs += n;
    }
  }

  પાછા d->m_output_flush_remaining;
}

#જો MINIZ_USE_UNALIGNED_LOADS_AND_STORES
#define TDEFL_READ_UNALIGNED_WORD(p) *(અચલ mz_uint16*)(p)
સ્થિર MZ_FORCEINLINE શૂન્ય tdefl_find_match(tdefl_compressor *d, mz_uint lookahead_pos, mz_uint max_dist, mz_uint max_match_len, mz_uint *pMatch_dist, mz_uint *pMatch_len)
{
  mz_uint dist, pos = lookahead_pos & TDEFL_LZ_DICT_SIZE_MASK, match_len = *pMatch_len, probe_pos = pos, next_probe_pos, probe_len;
  mz_uint અંક_probes_ડાબું = d->m_max_probes[match_len >= 32];
  અચલ mz_uint16 *s = (અચલ mz_uint16*)(d->m_dict + pos), *p, *q;
  mz_uint16 c01 = TDEFL_READ_UNALIGNED_WORD(&d->m_dict[pos + match_len - 1]), s01 = TDEFL_READ_UNALIGNED_WORD(s);
  MZ_ASSERT(max_match_len <= TDEFL_MAX_MATCH_LEN); જો (max_match_len <= match_len) પાછા;
  માટે ( ; ; )
  {
    માટે ( ; ; )
    {
      જો (--અંક_probes_ડાબું == 0) પાછા;
      #define TDEFL_PROBE \
        next_probe_pos = d->m_next[probe_pos]; \
        જો ((!next_probe_pos) || ((dist = (mz_uint16)(lookahead_pos - next_probe_pos)) > max_dist)) પાછા; \
        probe_pos = next_probe_pos & TDEFL_LZ_DICT_SIZE_MASK; \
        જો (TDEFL_READ_UNALIGNED_WORD(&d->m_dict[probe_pos + match_len - 1]) == c01) તોડો;
      TDEFL_PROBE
      TDEFL_PROBE
      TDEFL_PROBE
    }
    જો (!dist) તોડો;
    q = (અચલ mz_uint16*)(d->m_dict + probe_pos);
    જો (TDEFL_READ_UNALIGNED_WORD(q) != s01) ચાલુ;
    p = s; probe_len = 32;
    કરો { } જ્યારે ( (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) && (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) &&
                   (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) && (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) && (--probe_len > 0) );
    જો (!probe_len)
    {
      *pMatch_dist = dist; *pMatch_len = MZ_MIN(max_match_len, TDEFL_MAX_MATCH_LEN); તોડો;
    }
    નહીંતર જો ((probe_len = ((mz_uint)(p - s) * 2) + (mz_uint)(*(અચલ mz_uint8*)p == *(અચલ mz_uint8*)q)) > match_len)
    {
      *pMatch_dist = dist; જો ((*pMatch_len = match_len = MZ_MIN(max_match_len, probe_len)) == max_match_len) તોડો;
      c01 = TDEFL_READ_UNALIGNED_WORD(&d->m_dict[pos + match_len - 1]);
    }
  }
}
#નહીંતર
સ્થિર MZ_FORCEINLINE શૂન્ય tdefl_find_match(tdefl_compressor *d, mz_uint lookahead_pos, mz_uint max_dist, mz_uint max_match_len, mz_uint *pMatch_dist, mz_uint *pMatch_len)
{
  mz_uint dist, pos = lookahead_pos & TDEFL_LZ_DICT_SIZE_MASK, match_len = *pMatch_len, probe_pos = pos, next_probe_pos, probe_len;
  mz_uint અંક_probes_ડાબું = d->m_max_probes[match_len >= 32];
  અચલ mz_uint8 *s = d->m_dict + pos, *p, *q;
  mz_uint8 c0 = d->m_dict[pos + match_len], c1 = d->m_dict[pos + match_len - 1];
  MZ_ASSERT(max_match_len <= TDEFL_MAX_MATCH_LEN); જો (max_match_len <= match_len) પાછા;
  માટે ( ; ; )
  {
    માટે ( ; ; )
    {
      જો (--અંક_probes_ડાબું == 0) પાછા;
      #define TDEFL_PROBE \
        next_probe_pos = d->m_next[probe_pos]; \
        જો ((!next_probe_pos) || ((dist = (mz_uint16)(lookahead_pos - next_probe_pos)) > max_dist)) પાછા; \
        probe_pos = next_probe_pos & TDEFL_LZ_DICT_SIZE_MASK; \
        જો ((d->m_dict[probe_pos + match_len] == c0) && (d->m_dict[probe_pos + match_len - 1] == c1)) તોડો;
      TDEFL_PROBE
      TDEFL_PROBE
      TDEFL_PROBE
    }
    જો (!dist) તોડો;
    p = s; q = d->m_dict + probe_pos;
    માટે (probe_len = 0; probe_len < max_match_len; probe_len++) {
        જો (*p++ != *q++) તોડો;
    }
    જો (probe_len > match_len)
    {
      *pMatch_dist = dist;
      જો ((*pMatch_len = match_len = probe_len) == max_match_len) પાછા;
      c0 = d->m_dict[pos + match_len]; c1 = d->m_dict[pos + match_len - 1];
    }
  }
}
#endif // #if MINIZ_USE_UNALIGNED_LOADS_AND_STORES

#જો MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
સ્થિર mz_bool tdefl_compress_fast(tdefl_compressor *d)
{
  // Faster, minimally featured LZRW1-style match+parse loop with better register utilization. Intended for applications where raw throughput is valued more highly than ratio.
  mz_uint lookahead_pos = d->m_lookahead_pos, lookahead_size = d->m_lookahead_size, dict_size = d->m_dict_size, total_lz_bytes = d->m_total_lz_bytes, અંક_flags_ડાબું = d->m_અંક_flags_ડાબું;
  mz_uint8 *pLZ_code_buf = d->m_pLZ_code_buf, *pLZ_flags = d->m_pLZ_flags;
  mz_uint cur_pos = lookahead_pos & TDEFL_LZ_DICT_SIZE_MASK;

  જ્યારે ((d->m_src_buf_ડાબું) || ((d->m_flush) && (lookahead_size)))
  {
    અચલ mz_uint TDEFL_COMP_FAST_LOOKAHEAD_SIZE = 4096;
    mz_uint dst_pos = (lookahead_pos + lookahead_size) & TDEFL_LZ_DICT_SIZE_MASK;
    mz_uint અંક_bytes_to_process = (mz_uint)MZ_MIN(d->m_src_buf_ડાબું, TDEFL_COMP_FAST_LOOKAHEAD_SIZE - lookahead_size);
    d->m_src_buf_ડાબું -= અંક_bytes_to_process;
    lookahead_size += અંક_bytes_to_process;

    જ્યારે (અંક_bytes_to_process)
    {
      mz_uint32 n = MZ_MIN(TDEFL_LZ_DICT_SIZE - dst_pos, અંક_bytes_to_process);
      memcpy(d->m_dict + dst_pos, d->m_pSrc, n);
      જો (dst_pos < (TDEFL_MAX_MATCH_LEN - 1))
        memcpy(d->m_dict + TDEFL_LZ_DICT_SIZE + dst_pos, d->m_pSrc, MZ_MIN(n, (TDEFL_MAX_MATCH_LEN - 1) - dst_pos));
      d->m_pSrc += n;
      dst_pos = (dst_pos + n) & TDEFL_LZ_DICT_SIZE_MASK;
      અંક_bytes_to_process -= n;
    }

    dict_size = MZ_MIN(TDEFL_LZ_DICT_SIZE - lookahead_size, dict_size);
    જો ((!d->m_flush) && (lookahead_size < TDEFL_COMP_FAST_LOOKAHEAD_SIZE)) તોડો;

    જ્યારે (lookahead_size >= 4)
    {
      mz_uint cur_match_dist, cur_match_len = 1;
      mz_uint8 *pCur_dict = d->m_dict + cur_pos;
      mz_uint first_trigram = (*(અચલ mz_uint32 *)pCur_dict) & 0xFFFFFF;
      mz_uint hash = (first_trigram ^ (first_trigram >> (24 - (TDEFL_LZ_HASH_BITS - 8)))) & TDEFL_LEVEL1_HASH_SIZE_MASK;
      mz_uint probe_pos = d->m_hash[hash];
      d->m_hash[hash] = (mz_uint16)lookahead_pos;

      જો (((cur_match_dist = (mz_uint16)(lookahead_pos - probe_pos)) <= dict_size) && ((*(અચલ mz_uint32 *)(d->m_dict + (probe_pos &= TDEFL_LZ_DICT_SIZE_MASK)) & 0xFFFFFF) == first_trigram))
      {
        અચલ mz_uint16 *p = (અચલ mz_uint16 *)pCur_dict;
        અચલ mz_uint16 *q = (અચલ mz_uint16 *)(d->m_dict + probe_pos);
        mz_uint32 probe_len = 32;
        કરો { } જ્યારે ( (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) && (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) &&
          (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) && (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) && (--probe_len > 0) );
        cur_match_len = ((mz_uint)(p - (અચલ mz_uint16 *)pCur_dict) * 2) + (mz_uint)(*(અચલ mz_uint8 *)p == *(અચલ mz_uint8 *)q);
        જો (!probe_len)
          cur_match_len = cur_match_dist ? TDEFL_MAX_MATCH_LEN : 0;

        જો ((cur_match_len < TDEFL_MIN_MATCH_LEN) || ((cur_match_len == TDEFL_MIN_MATCH_LEN) && (cur_match_dist >= 8U*1024U)))
        {
          cur_match_len = 1;
          *pLZ_code_buf++ = (mz_uint8)first_trigram;
          *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
          d->m_huff_ગણતરી[0][(mz_uint8)first_trigram]++;
        }
        નહીંતર
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
          d->m_huff_ગણતરી[1][(cur_match_dist < 512) ? s0 : s1]++;

          d->m_huff_ગણતરી[0][s_tdefl_len_sym[cur_match_len - TDEFL_MIN_MATCH_LEN]]++;
        }
      }
      નહીંતર
      {
        *pLZ_code_buf++ = (mz_uint8)first_trigram;
        *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
        d->m_huff_ગણતરી[0][(mz_uint8)first_trigram]++;
      }

      જો (--અંક_flags_ડાબું == 0) { અંક_flags_ડાબું = 8; pLZ_flags = pLZ_code_buf++; }

      total_lz_bytes += cur_match_len;
      lookahead_pos += cur_match_len;
      dict_size = MZ_MIN(dict_size + cur_match_len, TDEFL_LZ_DICT_SIZE);
      cur_pos = (cur_pos + cur_match_len) & TDEFL_LZ_DICT_SIZE_MASK;
      MZ_ASSERT(lookahead_size >= cur_match_len);
      lookahead_size -= cur_match_len;

      જો (pLZ_code_buf > &d->m_lz_code_buf[TDEFL_LZ_CODE_BUF_SIZE - 8])
      {
        પૂર્ણાંક n;
        d->m_lookahead_pos = lookahead_pos; d->m_lookahead_size = lookahead_size; d->m_dict_size = dict_size;
        d->m_total_lz_bytes = total_lz_bytes; d->m_pLZ_code_buf = pLZ_code_buf; d->m_pLZ_flags = pLZ_flags; d->m_અંક_flags_ડાબું = અંક_flags_ડાબું;
        જો ((n = tdefl_flush_block(d, 0)) != 0)
          પાછા (n < 0) ? MZ_FALSE : MZ_TRUE;
        total_lz_bytes = d->m_total_lz_bytes; pLZ_code_buf = d->m_pLZ_code_buf; pLZ_flags = d->m_pLZ_flags; અંક_flags_ડાબું = d->m_અંક_flags_ડાબું;
      }
    }

    જ્યારે (lookahead_size)
    {
      mz_uint8 lit = d->m_dict[cur_pos];

      total_lz_bytes++;
      *pLZ_code_buf++ = lit;
      *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
      જો (--અંક_flags_ડાબું == 0) { અંક_flags_ડાબું = 8; pLZ_flags = pLZ_code_buf++; }

      d->m_huff_ગણતરી[0][lit]++;

      lookahead_pos++;
      dict_size = MZ_MIN(dict_size + 1, TDEFL_LZ_DICT_SIZE);
      cur_pos = (cur_pos + 1) & TDEFL_LZ_DICT_SIZE_MASK;
      lookahead_size--;

      જો (pLZ_code_buf > &d->m_lz_code_buf[TDEFL_LZ_CODE_BUF_SIZE - 8])
      {
        પૂર્ણાંક n;
        d->m_lookahead_pos = lookahead_pos; d->m_lookahead_size = lookahead_size; d->m_dict_size = dict_size;
        d->m_total_lz_bytes = total_lz_bytes; d->m_pLZ_code_buf = pLZ_code_buf; d->m_pLZ_flags = pLZ_flags; d->m_અંક_flags_ડાબું = અંક_flags_ડાબું;
        જો ((n = tdefl_flush_block(d, 0)) != 0)
          પાછા (n < 0) ? MZ_FALSE : MZ_TRUE;
        total_lz_bytes = d->m_total_lz_bytes; pLZ_code_buf = d->m_pLZ_code_buf; pLZ_flags = d->m_pLZ_flags; અંક_flags_ડાબું = d->m_અંક_flags_ડાબું;
      }
    }
  }

  d->m_lookahead_pos = lookahead_pos; d->m_lookahead_size = lookahead_size; d->m_dict_size = dict_size;
  d->m_total_lz_bytes = total_lz_bytes; d->m_pLZ_code_buf = pLZ_code_buf; d->m_pLZ_flags = pLZ_flags; d->m_અંક_flags_ડાબું = અંક_flags_ડાબું;
  પાછા MZ_TRUE;
}
#endif // MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN

સ્થિર MZ_FORCEINLINE શૂન્ય tdefl_record_literal(tdefl_compressor *d, mz_uint8 lit)
{
  d->m_total_lz_bytes++;
  *d->m_pLZ_code_buf++ = lit;
  *d->m_pLZ_flags = (mz_uint8)(*d->m_pLZ_flags >> 1); જો (--d->m_અંક_flags_ડાબું == 0) { d->m_અંક_flags_ડાબું = 8; d->m_pLZ_flags = d->m_pLZ_code_buf++; }
  d->m_huff_ગણતરી[0][lit]++;
}

સ્થિર MZ_FORCEINLINE શૂન્ય tdefl_record_match(tdefl_compressor *d, mz_uint match_len, mz_uint match_dist)
{
  mz_uint32 s0, s1;

  MZ_ASSERT((match_len >= TDEFL_MIN_MATCH_LEN) && (match_dist >= 1) && (match_dist <= TDEFL_LZ_DICT_SIZE));

  d->m_total_lz_bytes += match_len;

  d->m_pLZ_code_buf[0] = (mz_uint8)(match_len - TDEFL_MIN_MATCH_LEN);

  match_dist -= 1;
  d->m_pLZ_code_buf[1] = (mz_uint8)(match_dist & 0xFF);
  d->m_pLZ_code_buf[2] = (mz_uint8)(match_dist >> 8); d->m_pLZ_code_buf += 3;

  *d->m_pLZ_flags = (mz_uint8)((*d->m_pLZ_flags >> 1) | 0x80); જો (--d->m_અંક_flags_ડાબું == 0) { d->m_અંક_flags_ડાબું = 8; d->m_pLZ_flags = d->m_pLZ_code_buf++; }

  s0 = s_tdefl_small_dist_sym[match_dist & 511]; s1 = s_tdefl_large_dist_sym[(match_dist >> 8) & 127];
  d->m_huff_ગણતરી[1][(match_dist < 512) ? s0 : s1]++;

  જો (match_len >= TDEFL_MIN_MATCH_LEN) d->m_huff_ગણતરી[0][s_tdefl_len_sym[match_len - TDEFL_MIN_MATCH_LEN]]++;
}

સ્થિર mz_bool tdefl_compress_normal(tdefl_compressor *d)
{
  અચલ mz_uint8 *pSrc = d->m_pSrc; size_t src_buf_ડાબું = d->m_src_buf_ડાબું;
  tdefl_flush flush = d->m_flush;

  જ્યારે ((src_buf_ડાબું) || ((flush) && (d->m_lookahead_size)))
  {
    mz_uint len_to_move, cur_match_dist, cur_match_len, cur_pos;
    // Update dictionary and hash chains. Keeps the lookahead size equal to TDEFL_MAX_MATCH_LEN.
    જો ((d->m_lookahead_size + d->m_dict_size) >= (TDEFL_MIN_MATCH_LEN - 1))
    {
      mz_uint dst_pos = (d->m_lookahead_pos + d->m_lookahead_size) & TDEFL_LZ_DICT_SIZE_MASK, ins_pos = d->m_lookahead_pos + d->m_lookahead_size - 2;
      mz_uint hash = (d->m_dict[ins_pos & TDEFL_LZ_DICT_SIZE_MASK] << TDEFL_LZ_HASH_SHIFT) ^ d->m_dict[(ins_pos + 1) & TDEFL_LZ_DICT_SIZE_MASK];
      mz_uint અંક_bytes_to_process = (mz_uint)MZ_MIN(src_buf_ડાબું, TDEFL_MAX_MATCH_LEN - d->m_lookahead_size);
      અચલ mz_uint8 *pSrc_end = pSrc ? pSrc + અંક_bytes_to_process : ખાલી;
      src_buf_ડાબું -= અંક_bytes_to_process;
      d->m_lookahead_size += અંક_bytes_to_process;
      જ્યારે (pSrc != pSrc_end)
      {
        mz_uint8 c = *pSrc++; d->m_dict[dst_pos] = c; જો (dst_pos < (TDEFL_MAX_MATCH_LEN - 1)) d->m_dict[TDEFL_LZ_DICT_SIZE + dst_pos] = c;
        hash = ((hash << TDEFL_LZ_HASH_SHIFT) ^ c) & (TDEFL_LZ_HASH_SIZE - 1);
        d->m_next[ins_pos & TDEFL_LZ_DICT_SIZE_MASK] = d->m_hash[hash]; d->m_hash[hash] = (mz_uint16)(ins_pos);
        dst_pos = (dst_pos + 1) & TDEFL_LZ_DICT_SIZE_MASK; ins_pos++;
      }
    }
    નહીંતર
    {
      જ્યારે ((src_buf_ડાબું) && (d->m_lookahead_size < TDEFL_MAX_MATCH_LEN))
      {
        mz_uint8 c = *pSrc++;
        mz_uint dst_pos = (d->m_lookahead_pos + d->m_lookahead_size) & TDEFL_LZ_DICT_SIZE_MASK;
        src_buf_ડાબું--;
        d->m_dict[dst_pos] = c;
        જો (dst_pos < (TDEFL_MAX_MATCH_LEN - 1))
          d->m_dict[TDEFL_LZ_DICT_SIZE + dst_pos] = c;
        જો ((++d->m_lookahead_size + d->m_dict_size) >= TDEFL_MIN_MATCH_LEN)
        {
          mz_uint ins_pos = d->m_lookahead_pos + (d->m_lookahead_size - 1) - 2;
          mz_uint hash = ((d->m_dict[ins_pos & TDEFL_LZ_DICT_SIZE_MASK] << (TDEFL_LZ_HASH_SHIFT * 2)) ^ (d->m_dict[(ins_pos + 1) & TDEFL_LZ_DICT_SIZE_MASK] << TDEFL_LZ_HASH_SHIFT) ^ c) & (TDEFL_LZ_HASH_SIZE - 1);
          d->m_next[ins_pos & TDEFL_LZ_DICT_SIZE_MASK] = d->m_hash[hash]; d->m_hash[hash] = (mz_uint16)(ins_pos);
        }
      }
    }
    d->m_dict_size = MZ_MIN(TDEFL_LZ_DICT_SIZE - d->m_lookahead_size, d->m_dict_size);
    જો ((!flush) && (d->m_lookahead_size < TDEFL_MAX_MATCH_LEN))
      તોડો;

    // Simple lazy/greedy parsing state machine.
    len_to_move = 1; cur_match_dist = 0; cur_match_len = d->m_saved_match_len ? d->m_saved_match_len : (TDEFL_MIN_MATCH_LEN - 1); cur_pos = d->m_lookahead_pos & TDEFL_LZ_DICT_SIZE_MASK;
    જો (d->m_flags & (TDEFL_RLE_MATCHES | TDEFL_FORCE_ALL_RAW_BLOCKS))
    {
      જો ((d->m_dict_size) && (!(d->m_flags & TDEFL_FORCE_ALL_RAW_BLOCKS)))
      {
        mz_uint8 c = d->m_dict[(cur_pos - 1) & TDEFL_LZ_DICT_SIZE_MASK];
        cur_match_len = 0; જ્યારે (cur_match_len < d->m_lookahead_size) { જો (d->m_dict[cur_pos + cur_match_len] != c) તોડો; cur_match_len++; }
        જો (cur_match_len < TDEFL_MIN_MATCH_LEN) cur_match_len = 0; નહીંતર cur_match_dist = 1;
      }
    }
    નહીંતર
    {
      tdefl_find_match(d, d->m_lookahead_pos, d->m_dict_size, d->m_lookahead_size, &cur_match_dist, &cur_match_len);
    }
    જો (((cur_match_len == TDEFL_MIN_MATCH_LEN) && (cur_match_dist >= 8U*1024U)) || (cur_pos == cur_match_dist) || ((d->m_flags & TDEFL_FILTER_MATCHES) && (cur_match_len <= 5)))
    {
      cur_match_dist = cur_match_len = 0;
    }
    જો (d->m_saved_match_len)
    {
      જો (cur_match_len > d->m_saved_match_len)
      {
        tdefl_record_literal(d, (mz_uint8)d->m_saved_lit);
        જો (cur_match_len >= 128)
        {
          tdefl_record_match(d, cur_match_len, cur_match_dist);
          d->m_saved_match_len = 0; len_to_move = cur_match_len;
        }
        નહીંતર
        {
          d->m_saved_lit = d->m_dict[cur_pos]; d->m_saved_match_dist = cur_match_dist; d->m_saved_match_len = cur_match_len;
        }
      }
      નહીંતર
      {
        tdefl_record_match(d, d->m_saved_match_len, d->m_saved_match_dist);
        len_to_move = d->m_saved_match_len - 1; d->m_saved_match_len = 0;
      }
    }
    નહીંતર જો (!cur_match_dist)
      tdefl_record_literal(d, d->m_dict[MZ_MIN(cur_pos, કદ(d->m_dict) - 1)]);
    નહીંતર જો ((d->m_greedy_parsing) || (d->m_flags & TDEFL_RLE_MATCHES) || (cur_match_len >= 128))
    {
      tdefl_record_match(d, cur_match_len, cur_match_dist);
      len_to_move = cur_match_len;
    }
    નહીંતર
    {
      d->m_saved_lit = d->m_dict[MZ_MIN(cur_pos, કદ(d->m_dict) - 1)]; d->m_saved_match_dist = cur_match_dist; d->m_saved_match_len = cur_match_len;
    }
    // Move the lookahead forward by len_to_move bytes.
    d->m_lookahead_pos += len_to_move;
    MZ_ASSERT(d->m_lookahead_size >= len_to_move);
    d->m_lookahead_size -= len_to_move;
    d->m_dict_size = MZ_MIN(d->m_dict_size + len_to_move, TDEFL_LZ_DICT_SIZE);
    // Check if it's time to flush the current LZ codes to the internal output buffer.
    જો ( (d->m_pLZ_code_buf > &d->m_lz_code_buf[TDEFL_LZ_CODE_BUF_SIZE - 8]) ||
         ( (d->m_total_lz_bytes > 31*1024) && (((((mz_uint)(d->m_pLZ_code_buf - d->m_lz_code_buf) * 115) >> 7) >= d->m_total_lz_bytes) || (d->m_flags & TDEFL_FORCE_ALL_RAW_BLOCKS))) )
    {
      પૂર્ણાંક n;
      d->m_pSrc = pSrc; d->m_src_buf_ડાબું = src_buf_ડાબું;
      જો ((n = tdefl_flush_block(d, 0)) != 0)
        પાછા (n < 0) ? MZ_FALSE : MZ_TRUE;
    }
  }

  d->m_pSrc = pSrc; d->m_src_buf_ડાબું = src_buf_ડાબું;
  પાછા MZ_TRUE;
}

સ્થિર tdefl_status tdefl_flush_output_buffer(tdefl_compressor *d)
{
  જો (d->m_pIn_buf_size)
  {
    *d->m_pIn_buf_size = d->m_pSrc - (અચલ mz_uint8 *)d->m_pIn_buf;
  }

  જો (d->m_pOut_buf_size)
  {
    size_t n = MZ_MIN(*d->m_pOut_buf_size - d->m_out_buf_ofs, d->m_output_flush_remaining);
    memcpy((mz_uint8 *)d->m_pOut_buf + d->m_out_buf_ofs, d->m_output_buf + d->m_output_flush_ofs, n);
    d->m_output_flush_ofs += (mz_uint)n;
    d->m_output_flush_remaining -= (mz_uint)n;
    d->m_out_buf_ofs += n;

    *d->m_pOut_buf_size = d->m_out_buf_ofs;
  }

  પાછા (d->m_finished && !d->m_output_flush_remaining) ? TDEFL_STATUS_DONE : TDEFL_STATUS_OKAY;
}

tdefl_status tdefl_compress(tdefl_compressor *d, અચલ શૂન્ય *pIn_buf, size_t *pIn_buf_size, શૂન્ય *pOut_buf, size_t *pOut_buf_size, tdefl_flush flush)
{
  જો (!d)
  {
    જો (pIn_buf_size) *pIn_buf_size = 0;
    જો (pOut_buf_size) *pOut_buf_size = 0;
    પાછા TDEFL_STATUS_BAD_PARAM;
  }

  d->m_pIn_buf = pIn_buf; d->m_pIn_buf_size = pIn_buf_size;
  d->m_pOut_buf = pOut_buf; d->m_pOut_buf_size = pOut_buf_size;
  d->m_pSrc = (અચલ mz_uint8 *)(pIn_buf); d->m_src_buf_ડાબું = pIn_buf_size ? *pIn_buf_size : 0;
  d->m_out_buf_ofs = 0;
  d->m_flush = flush;

  જો ( ((d->m_pPut_buf_func != ખાલી) == ((pOut_buf != ખાલી) || (pOut_buf_size != ખાલી))) || (d->m_prev_return_status != TDEFL_STATUS_OKAY) ||
        (d->m_wants_to_finish && (flush != TDEFL_FINISH)) || (pIn_buf_size && *pIn_buf_size && !pIn_buf) || (pOut_buf_size && *pOut_buf_size && !pOut_buf) )
  {
    જો (pIn_buf_size) *pIn_buf_size = 0;
    જો (pOut_buf_size) *pOut_buf_size = 0;
    પાછા (d->m_prev_return_status = TDEFL_STATUS_BAD_PARAM);
  }
  d->m_wants_to_finish |= (flush == TDEFL_FINISH);

  જો ((d->m_output_flush_remaining) || (d->m_finished))
    પાછા (d->m_prev_return_status = tdefl_flush_output_buffer(d));

#જો MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  જો (((d->m_flags & TDEFL_MAX_PROBES_MASK) == 1) &&
      ((d->m_flags & TDEFL_GREEDY_PARSING_FLAG) != 0) &&
      ((d->m_flags & (TDEFL_FILTER_MATCHES | TDEFL_FORCE_ALL_RAW_BLOCKS | TDEFL_RLE_MATCHES)) == 0))
  {
    જો (!tdefl_compress_fast(d))
      પાછા d->m_prev_return_status;
  }
  નહીંતર
#endif // #if MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  {
    જો (!tdefl_compress_normal(d))
      પાછા d->m_prev_return_status;
  }

  જો ((d->m_flags & (TDEFL_WRITE_ZLIB_HEADER | TDEFL_COMPUTE_ADLER32)) && (pIn_buf))
    d->m_adler32 = (mz_uint32)mz_adler32(d->m_adler32, (અચલ mz_uint8 *)pIn_buf, d->m_pSrc - (અચલ mz_uint8 *)pIn_buf);

  જો ((flush) && (!d->m_lookahead_size) && (!d->m_src_buf_ડાબું) && (!d->m_output_flush_remaining))
  {
    જો (tdefl_flush_block(d, flush) < 0)
      પાછા d->m_prev_return_status;
    d->m_finished = (flush == TDEFL_FINISH);
    જો (flush == TDEFL_FULL_FLUSH) { MZ_CLEAR_ARR(d->m_hash); MZ_CLEAR_ARR(d->m_next); d->m_dict_size = 0; }
  }

  પાછા (d->m_prev_return_status = tdefl_flush_output_buffer(d));
}

tdefl_status tdefl_compress_buffer(tdefl_compressor *d, અચલ શૂન્ય *pIn_buf, size_t in_buf_size, tdefl_flush flush)
{
  MZ_ASSERT(d->m_pPut_buf_func); પાછા tdefl_compress(d, pIn_buf, &in_buf_size, ખાલી, ખાલી, flush);
}

tdefl_status tdefl_init(tdefl_compressor *d, tdefl_put_buf_func_ptr pPut_buf_func, શૂન્ય *pPut_buf_user, પૂર્ણાંક flags)
{
  d->m_pPut_buf_func = pPut_buf_func; d->m_pPut_buf_user = pPut_buf_user;
  d->m_flags = (mz_uint)(flags); d->m_max_probes[0] = 1 + ((flags & 0xFFF) + 2) / 3; d->m_greedy_parsing = (flags & TDEFL_GREEDY_PARSING_FLAG) != 0;
  d->m_max_probes[1] = 1 + (((flags & 0xFFF) >> 2) + 2) / 3;
  જો (!(flags & TDEFL_NONDETERMINISTIC_PARSING_FLAG)) MZ_CLEAR_ARR(d->m_hash);
  d->m_lookahead_pos = d->m_lookahead_size = d->m_dict_size = d->m_total_lz_bytes = d->m_lz_code_buf_dict_pos = d->m_bits_in = 0;
  d->m_output_flush_ofs = d->m_output_flush_remaining = d->m_finished = d->m_block_index = d->m_bit_buffer = d->m_wants_to_finish = 0;
  d->m_pLZ_code_buf = d->m_lz_code_buf + 1; d->m_pLZ_flags = d->m_lz_code_buf; d->m_અંક_flags_ડાબું = 8;
  d->m_pOutput_buf = d->m_output_buf; d->m_pOutput_buf_end = d->m_output_buf; d->m_prev_return_status = TDEFL_STATUS_OKAY;
  d->m_saved_match_dist = d->m_saved_match_len = d->m_saved_lit = 0; d->m_adler32 = 1;
  d->m_pIn_buf = ખાલી; d->m_pOut_buf = ખાલી;
  d->m_pIn_buf_size = ખાલી; d->m_pOut_buf_size = ખાલી;
  d->m_flush = TDEFL_NO_FLUSH; d->m_pSrc = ખાલી; d->m_src_buf_ડાબું = 0; d->m_out_buf_ofs = 0;
  memset(&d->m_huff_ગણતરી[0][0], 0, કદ(d->m_huff_ગણતરી[0][0]) * TDEFL_MAX_HUFF_SYMBOLS_0);
  memset(&d->m_huff_ગણતરી[1][0], 0, કદ(d->m_huff_ગણતરી[1][0]) * TDEFL_MAX_HUFF_SYMBOLS_1);
  પાછા TDEFL_STATUS_OKAY;
}

#ifndef MINIZ_SDL_NOUNUSED
tdefl_status tdefl_get_prev_return_status(tdefl_compressor *d)
{
  પાછા d->m_prev_return_status;
}

mz_uint32 tdefl_get_adler32(tdefl_compressor *d)
{
  પાછા d->m_adler32;
}

mz_bool tdefl_compress_mem_to_output(અચલ શૂન્ય *pBuf, size_t buf_len, tdefl_put_buf_func_ptr pPut_buf_func, શૂન્ય *pPut_buf_user, પૂર્ણાંક flags)
{
  tdefl_compressor *pComp; mz_bool succeeded; જો (((buf_len) && (!pBuf)) || (!pPut_buf_func)) પાછા MZ_FALSE;
  pComp = (tdefl_compressor*)MZ_MALLOC(કદ(tdefl_compressor)); જો (!pComp) પાછા MZ_FALSE;
  succeeded = (tdefl_init(pComp, pPut_buf_func, pPut_buf_user, flags) == TDEFL_STATUS_OKAY);
  succeeded = succeeded && (tdefl_compress_buffer(pComp, pBuf, buf_len, TDEFL_FINISH) == TDEFL_STATUS_DONE);
  MZ_FREE(pComp); પાછા succeeded;
}
#endif /* MINIZ_SDL_NOUNUSED */

પ્રકારવ્યાખ્યા સંરચના
{
  size_t m_size, m_capacity;
  mz_uint8 *m_pBuf;
  mz_bool m_expandable;
} tdefl_output_buffer;

સ્થિર mz_bool tdefl_output_buffer_putter(અચલ શૂન્ય *pBuf, પૂર્ણાંક len, શૂન્ય *pUser)
{
  tdefl_output_buffer *p = (tdefl_output_buffer *)pUser;
  size_t new_size = p->m_size + len;
  જો (new_size > p->m_capacity)
  {
    size_t new_capacity = p->m_capacity; mz_uint8 *pNew_buf; જો (!p->m_expandable) પાછા MZ_FALSE;
    કરો { new_capacity = MZ_MAX(128U, new_capacity << 1U); } જ્યારે (new_size > new_capacity);
    pNew_buf = (mz_uint8*)MZ_REALLOC(p->m_pBuf, new_capacity); જો (!pNew_buf) પાછા MZ_FALSE;
    p->m_pBuf = pNew_buf; p->m_capacity = new_capacity;
  }
  memcpy((mz_uint8*)p->m_pBuf + p->m_size, pBuf, len); p->m_size = new_size;
  પાછા MZ_TRUE;
}

#ifndef MINIZ_SDL_NOUNUSED
શૂન્ય *tdefl_compress_mem_to_heap(અચલ શૂન્ય *pSrc_buf, size_t src_buf_len, size_t *pOut_len, પૂર્ણાંક flags)
{
  tdefl_output_buffer out_buf; MZ_CLEAR_OBJ(out_buf);
  જો (!pOut_len) પાછા MZ_FALSE; નહીંતર *pOut_len = 0;
  out_buf.m_expandable = MZ_TRUE;
  જો (!tdefl_compress_mem_to_output(pSrc_buf, src_buf_len, tdefl_output_buffer_putter, &out_buf, flags)) પાછા ખાલી;
  *pOut_len = out_buf.m_size; પાછા out_buf.m_pBuf;
}

size_t tdefl_compress_mem_to_mem(શૂન્ય *pOut_buf, size_t out_buf_len, અચલ શૂન્ય *pSrc_buf, size_t src_buf_len, પૂર્ણાંક flags)
{
  tdefl_output_buffer out_buf; MZ_CLEAR_OBJ(out_buf);
  જો (!pOut_buf) પાછા 0;
  out_buf.m_pBuf = (mz_uint8*)pOut_buf; out_buf.m_capacity = out_buf_len;
  જો (!tdefl_compress_mem_to_output(pSrc_buf, src_buf_len, tdefl_output_buffer_putter, &out_buf, flags)) પાછા 0;
  પાછા out_buf.m_size;
}
#endif /* MINIZ_SDL_NOUNUSED */

#ifndef MINIZ_NO_ZLIB_APIS
સ્થિર અચલ mz_uint s_tdefl_અંક_probes[11] = { 0, 1, 6, 32,  16, 32, 128, 256,  512, 768, 1500 };

// level may actually range from [0,10] (10 is a "hidden" max level, where we want a bit more compression and it's fine if throughput to fall off a cliff on some files).
mz_uint tdefl_create_comp_flags_from_zip_params(પૂર્ણાંક level, પૂર્ણાંક window_bits, પૂર્ણાંક strategy)
{
  mz_uint comp_flags = s_tdefl_અંક_probes[(level >= 0) ? MZ_MIN(10, level) : MZ_DEFAULT_LEVEL] | ((level <= 3) ? TDEFL_GREEDY_PARSING_FLAG : 0);
  જો (window_bits > 0) comp_flags |= TDEFL_WRITE_ZLIB_HEADER;

  જો (!level) comp_flags |= TDEFL_FORCE_ALL_RAW_BLOCKS;
  નહીંતર જો (strategy == MZ_FILTERED) comp_flags |= TDEFL_FILTER_MATCHES;
  નહીંતર જો (strategy == MZ_HUFFMAN_ONLY) comp_flags &= ~TDEFL_MAX_PROBES_MASK;
  નહીંતર જો (strategy == MZ_FIXED) comp_flags |= TDEFL_FORCE_ALL_STATIC_BLOCKS;
  નહીંતર જો (strategy == MZ_RLE) comp_flags |= TDEFL_RLE_MATCHES;

  પાછા comp_flags;
}
#endif //MINIZ_NO_ZLIB_APIS

#ifdef _MSC_VER
#pragma warning (ધકેલો)
#pragma warning (disable:4204) // nonstandard extension used : non-constant aggregate initializer (also supported by GNU C and C99, so no big deal)
#endif

// Simple PNG writer function by Alex Evans, 2011. Released into the public domain: https://gist.github.com/908299, more context at
// http://altdevblogaday.org/2011/04/06/a-smaller-jpg-encoder/.
// This is actually a modification of Alex's original code so PNG files generated by this function pass pngcheck.
MINIZ_STATIC શૂન્ય *tdefl_write_image_to_png_file_in_memory_ex(અચલ શૂન્ય *pImage, પૂર્ણાંક w, પૂર્ણાંક h, પૂર્ણાંક અંક_chans, પૂર્ણાંક bpl, size_t *pLen_out, mz_uint level, mz_bool flip, mz_uint8 *plte, પૂર્ણાંક plte_size, mz_uint8 *trns, પૂર્ણાંક trns_size)
{
  // Using a local copy of this array here in case MINIZ_NO_ZLIB_APIS was defined.
  સ્થિર અચલ mz_uint s_tdefl_png_અંક_probes[11] = { 0, 1, 6, 32,  16, 32, 128, 256,  512, 768, 1500 };
  tdefl_compressor *pComp = (tdefl_compressor *)MZ_MALLOC(કદ(tdefl_compressor)); tdefl_output_buffer out_buf; પૂર્ણાંક i, y, z = 0; mz_uint32 c; *pLen_out = 0; size_t data_start, data_size;
  જો (!pComp) પાછા ખાલી;
  MZ_CLEAR_OBJ(out_buf); out_buf.m_expandable = MZ_TRUE;
  out_buf.m_capacity = 57+MZ_MAX(64, (1+w*અંક_chans)*h);
  જો (plte_size > 0)
    out_buf.m_capacity += 12+plte_size;
  જો (trns_size > 0)
    out_buf.m_capacity += 12+trns_size;
  જો (ખાલી == (out_buf.m_pBuf = (mz_uint8*)MZ_MALLOC(out_buf.m_capacity))) { MZ_FREE(pComp); પાછા ખાલી; }
  // write header
  {
    સ્થિર અચલ mz_uint8 chans[] = {0x00, 0x00, 0x04, 0x02, 0x06};

    mz_uint8 pnghdr[33]={ 0x89,0x50,0x4e,0x47,0x0d,0x0a,0x1a,0x0a,
                          0x00,0x00,0x00,0x0d,0x49,0x48,0x44,0x52,
                          0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                          0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

    pnghdr[18] = (mz_uint8)(w>>8);
    pnghdr[19] = (mz_uint8)(w>>0);

    pnghdr[22] = (mz_uint8)(h>>8);
    pnghdr[23] = (mz_uint8)(h>>0);

    જો (અંક_chans == 1 && plte_size > 0)
      pnghdr[25] = 3;
    નહીંતર
      pnghdr[25] = (chans[અંક_chans]);

    c = (mz_uint32)mz_crc32(MZ_CRC32_INIT,pnghdr+12,17);
    માટે (i=0; i<4; ++i, c<<=8) ((mz_uint8*)(pnghdr+29))[i] = (mz_uint8)(c>>24);
    જો (!tdefl_output_buffer_putter(pnghdr, કદ(pnghdr), &out_buf)) { *pLen_out = 0; MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); પાછા ખાલી; }
  }
  // write PLTE chunk
  જો (plte_size > 0)
  {
    mz_uint8 hdr[8]={0x00,0x00,0x00,0x00,0x50,0x4c,0x54,0x45};

    hdr[0] = (mz_uint8)(plte_size>>24);
    hdr[1] = (mz_uint8)(plte_size>>16);
    hdr[2] = (mz_uint8)(plte_size>> 8);
    hdr[3] = (mz_uint8)(plte_size>> 0);
    જો (!tdefl_output_buffer_putter(hdr, કદ(hdr), &out_buf)) { *pLen_out = 0; MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); પાછા ખાલી; }
    data_start = out_buf.m_size;
    જો (!tdefl_output_buffer_putter(plte, plte_size, &out_buf)) { *pLen_out = 0; MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); પાછા ખાલી; }
    જો (!tdefl_output_buffer_putter("\0\0\0\0", 4, &out_buf)) { *pLen_out = 0; MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); પાછા ખાલી; }
    c = (mz_uint32)mz_crc32(MZ_CRC32_INIT,out_buf.m_pBuf+data_start-4, plte_size+4);
    માટે (i=0; i<4; ++i, c<<=8) (out_buf.m_pBuf+out_buf.m_size-4)[i] = (mz_uint8)(c >> 24);
  }
  // write tRNS chunk
  જો (trns_size > 0)
  {
    mz_uint8 hdr[8]={0x00,0x00,0x00,0x00,0x74,0x52,0x4E,0x53};

    hdr[0] = (mz_uint8)(trns_size>>24);
    hdr[1] = (mz_uint8)(trns_size>>16);
    hdr[2] = (mz_uint8)(trns_size>> 8);
    hdr[3] = (mz_uint8)(trns_size>> 0);
    જો (!tdefl_output_buffer_putter(hdr, કદ(hdr), &out_buf)) { *pLen_out = 0; MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); પાછા ખાલી; }
    data_start = out_buf.m_size;
    જો (!tdefl_output_buffer_putter(trns, trns_size, &out_buf)) { *pLen_out = 0; MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); પાછા ખાલી; }
    જો (!tdefl_output_buffer_putter("\0\0\0\0", 4, &out_buf)) { *pLen_out = 0; MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); પાછા ખાલી; }
    c = (mz_uint32)mz_crc32(MZ_CRC32_INIT,out_buf.m_pBuf+data_start-4, trns_size+4);
    માટે (i=0; i<4; ++i, c<<=8) (out_buf.m_pBuf+out_buf.m_size-4)[i] = (mz_uint8)(c >> 24);
  }
  // write IDAT chunk
  જો (!tdefl_output_buffer_putter("\0\0\0\0\x49\x44\x41\x54", 8, &out_buf)) { *pLen_out = 0; MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); પાછા ખાલી; }
  data_start = out_buf.m_size;
  // compress image data
  tdefl_init(pComp, tdefl_output_buffer_putter, &out_buf, s_tdefl_png_અંક_probes[MZ_MIN(10, level)] | TDEFL_WRITE_ZLIB_HEADER);
  માટે (y = 0; y < h; ++y) { tdefl_compress_buffer(pComp, &z, 1, TDEFL_NO_FLUSH); tdefl_compress_buffer(pComp, (mz_uint8*)pImage + (flip ? (h - 1 - y) : y) * bpl, w * અંક_chans, TDEFL_NO_FLUSH); }
  જો (tdefl_compress_buffer(pComp, ખાલી, 0, TDEFL_FINISH) != TDEFL_STATUS_DONE) { MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); પાછા ખાલી; }
  // write IDAT size
  data_size = out_buf.m_size-data_start;
  (out_buf.m_pBuf+data_start-8)[0] = (mz_uint8)(data_size>>24);
  (out_buf.m_pBuf+data_start-8)[1] = (mz_uint8)(data_size>>16);
  (out_buf.m_pBuf+data_start-8)[2] = (mz_uint8)(data_size>> 8);
  (out_buf.m_pBuf+data_start-8)[3] = (mz_uint8)(data_size>> 0);
  // write footer (IDAT CRC-32, followed by IEND chunk)
  જો (!tdefl_output_buffer_putter("\0\0\0\0\0\0\0\0\x49\x45\x4e\x44\xae\x42\x60\x82", 16, &out_buf)) { *pLen_out = 0; MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); પાછા ખાલી; }
  c = (mz_uint32)mz_crc32(MZ_CRC32_INIT,out_buf.m_pBuf+data_start-4, data_size+4);
  માટે (i=0; i<4; ++i, c<<=8) (out_buf.m_pBuf+out_buf.m_size-16)[i] = (mz_uint8)(c >> 24);
  // compute final size of file, grab compressed data buffer and return
  *pLen_out = out_buf.m_size;
  MZ_FREE(pComp);
  પાછા out_buf.m_pBuf;
}
#ifndef MINIZ_SDL_NOUNUSED
MINIZ_STATIC શૂન્ય *tdefl_write_image_to_png_file_in_memory(અચલ શૂન્ય *pImage, પૂર્ણાંક w, પૂર્ણાંક h, પૂર્ણાંક અંક_chans, પૂર્ણાંક bpl, size_t *pLen_out)
{
  // Level 6 corresponds to TDEFL_DEFAULT_MAX_PROBES or MZ_DEFAULT_LEVEL (but we can't depend on MZ_DEFAULT_LEVEL being available in case the zlib API's where #defined out)
  પાછા tdefl_write_image_to_png_file_in_memory_ex(pImage, w, h, અંક_chans, bpl, pLen_out, 6, MZ_FALSE, ખાલી, 0, ખાલી, 0);
}
#endif

#ifdef _MSC_VER
#pragma warning (કાઢો)
#endif
#endif /*#ifndef MINIZ_NO_DEFLATE_APIS*/

// ------------------- .ZIP archive reading

#ifndef MINIZ_NO_ARCHIVE_APIS

#ifdef MINIZ_NO_STDIO
  #define MZ_FILE શૂન્ય *
#નહીંતર
  #અન્તર્ભાવ <stdio.h>
  #અન્તર્ભાવ <sys/stat.h>

  #જો defined(_MSC_VER) || defined(__MINGW64__)
    સ્થિર FILE *mz_fopen(અચલ અક્ષર *pFilename, અચલ અક્ષર *pMode)
    {
      FILE* pFile = ખાલી;
      fopen_s(&pFile, pFilename, pMode);
      પાછા pFile;
    }
    સ્થિર FILE *mz_freopen(અચલ અક્ષર *pPath, અચલ અક્ષર *pMode, FILE *pStream)
    {
      FILE* pFile = ખાલી;
      જો (freopen_s(&pFile, pPath, pMode, pStream))
        પાછા ખાલી;
      પાછા pFile;
    }
    #ifndef MINIZ_NO_TIME
      #અન્તર્ભાવ <sys/utime.h>
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
  #અથવાજો defined(__MINGW32__)
    #ifndef MINIZ_NO_TIME
      #અન્તર્ભાવ <sys/utime.h>
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
  #અથવાજો defined(__TINYC__)
    #ifndef MINIZ_NO_TIME
      #અન્તર્ભાવ <sys/utime.h>
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
  #અથવાજો defined(__GNUC__) && _LARGEFILE64_SOURCE
    #ifndef MINIZ_NO_TIME
      #અન્તર્ભાવ <utime.h>
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
  #નહીંતર
    #ifndef MINIZ_NO_TIME
      #અન્તર્ભાવ <utime.h>
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
ગણના
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
  MZ_ZIP_ECDH_SIG_OFS = 0, MZ_ZIP_ECDH_અંક_THIS_DISK_OFS = 4, MZ_ZIP_ECDH_અંક_DISK_CDIR_OFS = 6, MZ_ZIP_ECDH_CDIR_અંક_ENTRIES_ON_DISK_OFS = 8,
  MZ_ZIP_ECDH_CDIR_TOTAL_ENTRIES_OFS = 10, MZ_ZIP_ECDH_CDIR_SIZE_OFS = 12, MZ_ZIP_ECDH_CDIR_OFS_OFS = 16, MZ_ZIP_ECDH_COMMENT_SIZE_OFS = 20,
};

પ્રકારવ્યાખ્યા સંરચના
{
  શૂન્ય *m_p;
  size_t m_size, m_capacity;
  mz_uint m_element_size;
} mz_zip_array;

સંરચના mz_zip_internal_state_tag
{
  mz_zip_array m_central_dir;
  mz_zip_array m_central_dir_offsets;
  mz_zip_array m_sorted_central_dir_offsets;
  MZ_FILE *m_pFile;
  શૂન્ય *m_pMem;
  size_t m_mem_size;
  size_t m_mem_capacity;
};

#define MZ_ZIP_ARRAY_SET_ELEMENT_SIZE(array_ptr, element_size) (array_ptr)->m_element_size = element_size
#define MZ_ZIP_ARRAY_ELEMENT(array_ptr, element_type, index) ((element_type *)((array_ptr)->m_p))[index]

સ્થિર MZ_FORCEINLINE શૂન્ય mz_zip_array_clear(mz_zip_archive *pZip, mz_zip_array *pArray)
{
  pZip->m_pFree(pZip->m_pAlloc_opaque, pArray->m_p);
  memset(pArray, 0, કદ(mz_zip_array));
}

સ્થિર mz_bool mz_zip_array_ensure_capacity(mz_zip_archive *pZip, mz_zip_array *pArray, size_t min_new_capacity, mz_uint growing)
{
  શૂન્ય *pNew_p; size_t new_capacity = min_new_capacity; MZ_ASSERT(pArray->m_element_size); જો (pArray->m_capacity >= min_new_capacity) પાછા MZ_TRUE;
  જો (growing) { new_capacity = MZ_MAX(1, pArray->m_capacity); જ્યારે (new_capacity < min_new_capacity) new_capacity *= 2; }
  જો (ખાલી == (pNew_p = pZip->m_pRealloc(pZip->m_pAlloc_opaque, pArray->m_p, pArray->m_element_size, new_capacity))) પાછા MZ_FALSE;
  pArray->m_p = pNew_p; pArray->m_capacity = new_capacity;
  પાછા MZ_TRUE;
}

સ્થિર MZ_FORCEINLINE mz_bool mz_zip_array_reserve(mz_zip_archive *pZip, mz_zip_array *pArray, size_t new_capacity, mz_uint growing)
{
  જો (new_capacity > pArray->m_capacity) { જો (!mz_zip_array_ensure_capacity(pZip, pArray, new_capacity, growing)) પાછા MZ_FALSE; }
  પાછા MZ_TRUE;
}

સ્થિર MZ_FORCEINLINE mz_bool mz_zip_array_resize(mz_zip_archive *pZip, mz_zip_array *pArray, size_t new_size, mz_uint growing)
{
  જો (new_size > pArray->m_capacity) { જો (!mz_zip_array_ensure_capacity(pZip, pArray, new_size, growing)) પાછા MZ_FALSE; }
  pArray->m_size = new_size;
  પાછા MZ_TRUE;
}

સ્થિર MZ_FORCEINLINE mz_bool mz_zip_array_ensure_room(mz_zip_archive *pZip, mz_zip_array *pArray, size_t n)
{
  પાછા mz_zip_array_reserve(pZip, pArray, pArray->m_size + n, MZ_TRUE);
}

સ્થિર MZ_FORCEINLINE mz_bool mz_zip_array_ધકેલો_back(mz_zip_archive *pZip, mz_zip_array *pArray, અચલ શૂન્ય *pElements, size_t n)
{
  size_t orig_size = pArray->m_size; જો (!mz_zip_array_resize(pZip, pArray, orig_size + n, MZ_TRUE)) પાછા MZ_FALSE;
  memcpy((mz_uint8*)pArray->m_p + orig_size * pArray->m_element_size, pElements, n * pArray->m_element_size);
  પાછા MZ_TRUE;
}

#ifndef MINIZ_NO_TIME
સ્થિર time_t mz_zip_dos_to_time_t(પૂર્ણાંક dos_time, પૂર્ણાંક dos_date)
{
  સંરચના tm tm;
  memset(&tm, 0, કદ(tm)); tm.tm_isdst = -1;
  tm.tm_year = ((dos_date >> 9) & 127) + 1980 - 1900; tm.tm_mon = ((dos_date >> 5) & 15) - 1; tm.tm_mday = dos_date & 31;
  tm.tm_hour = (dos_time >> 11) & 31; tm.tm_min = (dos_time >> 5) & 63; tm.tm_sec = (dos_time << 1) & 62;
  પાછા mktime(&tm);
}

સ્થિર શૂન્ય mz_zip_time_to_dos_time(time_t time, mz_uint16 *pDOS_time, mz_uint16 *pDOS_date)
{
#ifdef _MSC_VER
  સંરચના tm tm_struct;
  સંરચના tm *tm = &tm_struct;
  errno_t err = localtime_s(tm, &time);
  જો (err)
  {
    *pDOS_date = 0; *pDOS_time = 0;
    પાછા;
  }
#નહીંતર
  સંરચના tm *tm = localtime(&time);
#endif
  *pDOS_time = (mz_uint16)(((tm->tm_hour) << 11) + ((tm->tm_min) << 5) + ((tm->tm_sec) >> 1));
  *pDOS_date = (mz_uint16)(((tm->tm_year + 1900 - 1980) << 9) + ((tm->tm_mon + 1) << 5) + tm->tm_mday);
}
#endif

#ifndef MINIZ_NO_STDIO
સ્થિર mz_bool mz_zip_get_file_modified_time(અચલ અક્ષર *pFilename, mz_uint16 *pDOS_time, mz_uint16 *pDOS_date)
{
#ifdef MINIZ_NO_TIME
  (શૂન્ય)pFilename; *pDOS_date = *pDOS_time = 0;
#નહીંતર
  સંરચના MZ_FILE_STAT_STRUCT file_stat;
  // On Linux with x86 glibc, this call will fail on large files (>= 0x80000000 bytes) unless you compiled with _LARGEFILE64_SOURCE. Argh.
  જો (MZ_FILE_STAT(pFilename, &file_stat) != 0)
    પાછા MZ_FALSE;
  mz_zip_time_to_dos_time(file_stat.st_mtime, pDOS_time, pDOS_date);
#endif // #ifdef MINIZ_NO_TIME
  પાછા MZ_TRUE;
}

#ifndef MINIZ_NO_TIME
સ્થિર mz_bool mz_zip_set_file_times(અચલ અક્ષર *pFilename, time_t access_time, time_t modified_time)
{
  સંરચના utimbuf t; t.actime = access_time; t.modtime = modified_time;
  પાછા !utime(pFilename, &t);
}
#endif // #ifndef MINIZ_NO_TIME
#endif // #ifndef MINIZ_NO_STDIO

સ્થિર mz_bool mz_zip_reader_init_internal(mz_zip_archive *pZip, mz_uint32 flags)
{
  (શૂન્ય)flags;
  જો ((!pZip) || (pZip->m_pState) || (pZip->m_zip_mode != MZ_ZIP_MODE_INVALID))
    પાછા MZ_FALSE;

  જો (!pZip->m_pAlloc) pZip->m_pAlloc = def_alloc_func;
  જો (!pZip->m_pFree) pZip->m_pFree = def_free_func;
  જો (!pZip->m_pRealloc) pZip->m_pRealloc = def_realloc_func;

  pZip->m_zip_mode = MZ_ZIP_MODE_READING;
  pZip->m_archive_size = 0;
  pZip->m_central_directory_file_ofs = 0;
  pZip->m_total_files = 0;

  જો (ખાલી == (pZip->m_pState = (mz_zip_internal_state *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, કદ(mz_zip_internal_state))))
    પાછા MZ_FALSE;
  memset(pZip->m_pState, 0, કદ(mz_zip_internal_state));
  MZ_ZIP_ARRAY_SET_ELEMENT_SIZE(&pZip->m_pState->m_central_dir, કદ(mz_uint8));
  MZ_ZIP_ARRAY_SET_ELEMENT_SIZE(&pZip->m_pState->m_central_dir_offsets, કદ(mz_uint32));
  MZ_ZIP_ARRAY_SET_ELEMENT_SIZE(&pZip->m_pState->m_sorted_central_dir_offsets, કદ(mz_uint32));
  પાછા MZ_TRUE;
}

સ્થિર MZ_FORCEINLINE mz_bool mz_zip_reader_filename_less(અચલ mz_zip_array *pCentral_dir_array, અચલ mz_zip_array *pCentral_dir_offsets, mz_uint l_index, mz_uint r_index)
{
  અચલ mz_uint8 *pL = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, l_index)), *pE;
  અચલ mz_uint8 *pR = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, r_index));
  mz_uint l_len = MZ_READ_LE16(pL + MZ_ZIP_CDH_FILENAME_LEN_OFS), r_len = MZ_READ_LE16(pR + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  mz_uint8 l = 0, r = 0;
  pL += MZ_ZIP_CENTRAL_DIR_HEADER_SIZE; pR += MZ_ZIP_CENTRAL_DIR_HEADER_SIZE;
  pE = pL + MZ_MIN(l_len, r_len);
  જ્યારે (pL < pE)
  {
    જો ((l = MZ_TOLOWER(*pL)) != (r = MZ_TOLOWER(*pR)))
      તોડો;
    pL++; pR++;
  }
  પાછા (pL == pE) ? (l_len < r_len) : (l < r);
}

#define MZ_SWAP_UINT32(a, b) કરો { mz_uint32 t = a; a = b; b = t; } MZ_MACRO_END

// Heap sort of lowercased filenames, used to help accelerate plain central directory searches by mz_zip_reader_locate_file(). (Could also use qsort(), but it could allocate memory.)
સ્થિર શૂન્ય mz_zip_reader_sort_central_dir_offsets_by_filename(mz_zip_archive *pZip)
{
  mz_zip_internal_state *pState = pZip->m_pState;
  અચલ mz_zip_array *pCentral_dir_offsets = &pState->m_central_dir_offsets;
  અચલ mz_zip_array *pCentral_dir = &pState->m_central_dir;
  mz_uint32 *pIndices = &MZ_ZIP_ARRAY_ELEMENT(&pState->m_sorted_central_dir_offsets, mz_uint32, 0);
  અચલ પૂર્ણાંક size = pZip->m_total_files;
  પૂર્ણાંક start = (size - 2) >> 1, end;
  જ્યારે (start >= 0)
  {
    પૂર્ણાંક child, મૂળ = start;
    માટે ( ; ; )
    {
      જો ((child = (મૂળ << 1) + 1) >= size)
        તોડો;
      child += (((child + 1) < size) && (mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[child], pIndices[child + 1])));
      જો (!mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[મૂળ], pIndices[child]))
        તોડો;
      MZ_SWAP_UINT32(pIndices[મૂળ], pIndices[child]); મૂળ = child;
    }
    start--;
  }

  end = size - 1;
  જ્યારે (end > 0)
  {
    પૂર્ણાંક child, મૂળ = 0;
    MZ_SWAP_UINT32(pIndices[end], pIndices[0]);
    માટે ( ; ; )
    {
      જો ((child = (મૂળ << 1) + 1) >= end)
        તોડો;
      child += (((child + 1) < end) && mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[child], pIndices[child + 1]));
      જો (!mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[મૂળ], pIndices[child]))
        તોડો;
      MZ_SWAP_UINT32(pIndices[મૂળ], pIndices[child]); મૂળ = child;
    }
    end--;
  }
}

સ્થિર mz_bool mz_zip_reader_read_central_dir(mz_zip_archive *pZip, mz_uint32 flags)
{
  mz_uint cdir_size, અંક_this_disk, cdir_disk_index;
  mz_uint64 cdir_ofs;
  mz_int64 cur_file_ofs;
  અચલ mz_uint8 *p;
  mz_uint32 buf_u32[4096 / કદ(mz_uint32)]; mz_uint8 *pBuf = (mz_uint8 *)buf_u32;
  mz_bool sort_central_dir = ((flags & MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY) == 0);
  // Basic sanity checks - reject files which are too small, and check the first 4 bytes of the file to make sure a local header is there.
  જો (pZip->m_archive_size < MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE)
    પાછા MZ_FALSE;
  // Find the end of central directory record by scanning the file from the end towards the beginning.
  cur_file_ofs = MZ_MAX((mz_int64)pZip->m_archive_size - (mz_int64)કદ(buf_u32), 0);
  માટે ( ; ; )
  {
    પૂર્ણાંક i, n = (પૂર્ણાંક)MZ_MIN(કદ(buf_u32), pZip->m_archive_size - cur_file_ofs);
    જો (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, n) != (mz_uint)n)
      પાછા MZ_FALSE;
    માટે (i = n - 4; i >= 0; --i)
      જો (MZ_READ_LE32(pBuf + i) == MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIG)
        તોડો;
    જો (i >= 0)
    {
      cur_file_ofs += i;
      તોડો;
    }
    જો ((!cur_file_ofs) || ((pZip->m_archive_size - cur_file_ofs) >= (0xFFFF + MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE)))
      પાછા MZ_FALSE;
    cur_file_ofs = MZ_MAX(cur_file_ofs - (કદ(buf_u32) - 3), 0);
  }
  // Read and verify the end of central directory record.
  જો (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE) != MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE)
    પાછા MZ_FALSE;
  જો ((MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_SIG_OFS) != MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIG) ||
      ((pZip->m_total_files = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_CDIR_TOTAL_ENTRIES_OFS)) != MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_CDIR_અંક_ENTRIES_ON_DISK_OFS)))
    પાછા MZ_FALSE;

  અંક_this_disk = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_અંક_THIS_DISK_OFS);
  cdir_disk_index = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_અંક_DISK_CDIR_OFS);
  જો (((અંક_this_disk | cdir_disk_index) != 0) && ((અંક_this_disk != 1) || (cdir_disk_index != 1)))
    પાછા MZ_FALSE;

  જો ((cdir_size = MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_CDIR_SIZE_OFS)) < pZip->m_total_files * MZ_ZIP_CENTRAL_DIR_HEADER_SIZE)
    પાછા MZ_FALSE;

  cdir_ofs = MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_CDIR_OFS_OFS);
  જો ((cdir_ofs + (mz_uint64)cdir_size) > pZip->m_archive_size)
    પાછા MZ_FALSE;

  pZip->m_central_directory_file_ofs = cdir_ofs;

  જો (pZip->m_total_files)
  {
     mz_uint i, n;

    // Read the entire central directory into a heap block, and allocate another heap block to hold the unsorted central dir file record offsets, and another to hold the sorted indices.
    જો ((!mz_zip_array_resize(pZip, &pZip->m_pState->m_central_dir, cdir_size, MZ_FALSE)) ||
        (!mz_zip_array_resize(pZip, &pZip->m_pState->m_central_dir_offsets, pZip->m_total_files, MZ_FALSE)))
      પાછા MZ_FALSE;

    જો (sort_central_dir)
    {
      જો (!mz_zip_array_resize(pZip, &pZip->m_pState->m_sorted_central_dir_offsets, pZip->m_total_files, MZ_FALSE))
        પાછા MZ_FALSE;
    }

    જો (pZip->m_pRead(pZip->m_pIO_opaque, cdir_ofs, pZip->m_pState->m_central_dir.m_p, cdir_size) != cdir_size)
      પાછા MZ_FALSE;

    // Now create an index into the central directory file records, do some basic sanity checking on each record, and check for zip64 entries (which are not yet supported).
    p = (અચલ mz_uint8 *)pZip->m_pState->m_central_dir.m_p;
    માટે (n = cdir_size, i = 0; i < pZip->m_total_files; ++i)
    {
      mz_uint total_header_size, comp_size, decomp_size, disk_index;
      જો ((n < MZ_ZIP_CENTRAL_DIR_HEADER_SIZE) || (MZ_READ_LE32(p) != MZ_ZIP_CENTRAL_DIR_HEADER_SIG))
        પાછા MZ_FALSE;
      MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, i) = (mz_uint32)(p - (અચલ mz_uint8 *)pZip->m_pState->m_central_dir.m_p);
      જો (sort_central_dir)
        MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_sorted_central_dir_offsets, mz_uint32, i) = i;
      comp_size = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_SIZE_OFS);
      decomp_size = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_SIZE_OFS);
      જો (((!MZ_READ_LE32(p + MZ_ZIP_CDH_METHOD_OFS)) && (decomp_size != comp_size)) || (decomp_size && !comp_size) || (decomp_size == 0xFFFFFFFF) || (comp_size == 0xFFFFFFFF))
        પાછા MZ_FALSE;
      disk_index = MZ_READ_LE16(p + MZ_ZIP_CDH_DISK_START_OFS);
      જો ((disk_index != અંક_this_disk) && (disk_index != 1))
        પાછા MZ_FALSE;
      જો (((mz_uint64)MZ_READ_LE32(p + MZ_ZIP_CDH_LOCAL_HEADER_OFS) + MZ_ZIP_LOCAL_DIR_HEADER_SIZE + comp_size) > pZip->m_archive_size)
        પાછા MZ_FALSE;
      જો ((total_header_size = MZ_ZIP_CENTRAL_DIR_HEADER_SIZE + MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_EXTRA_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_COMMENT_LEN_OFS)) > n)
        પાછા MZ_FALSE;
      n -= total_header_size; p += total_header_size;
    }
  }

  જો (sort_central_dir)
    mz_zip_reader_sort_central_dir_offsets_by_filename(pZip);

  પાછા MZ_TRUE;
}

mz_bool mz_zip_reader_init(mz_zip_archive *pZip, mz_uint64 size, mz_uint32 flags)
{
  જો ((!pZip) || (!pZip->m_pRead))
    પાછા MZ_FALSE;
  જો (!mz_zip_reader_init_internal(pZip, flags))
    પાછા MZ_FALSE;
  pZip->m_archive_size = size;
  જો (!mz_zip_reader_read_central_dir(pZip, flags))
  {
    mz_zip_reader_end(pZip);
    પાછા MZ_FALSE;
  }
  પાછા MZ_TRUE;
}

સ્થિર size_t mz_zip_mem_read_func(શૂન્ય *pOpaque, mz_uint64 file_ofs, શૂન્ય *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  size_t s = (file_ofs >= pZip->m_archive_size) ? 0 : (size_t)MZ_MIN(pZip->m_archive_size - file_ofs, n);
  memcpy(pBuf, (અચલ mz_uint8 *)pZip->m_pState->m_pMem + file_ofs, s);
  પાછા s;
}

mz_bool mz_zip_reader_init_mem(mz_zip_archive *pZip, અચલ શૂન્ય *pMem, size_t size, mz_uint32 flags)
{
  જો (!mz_zip_reader_init_internal(pZip, flags))
    પાછા MZ_FALSE;
  pZip->m_archive_size = size;
  pZip->m_pRead = mz_zip_mem_read_func;
  pZip->m_pIO_opaque = pZip;
#ifdef __cplusplus
  pZip->m_pState->m_pMem = const_cast<શૂન્ય *>(pMem);
#નહીંતર
  pZip->m_pState->m_pMem = (શૂન્ય *)pMem;
#endif
  pZip->m_pState->m_mem_size = size;
  જો (!mz_zip_reader_read_central_dir(pZip, flags))
  {
    mz_zip_reader_end(pZip);
    પાછા MZ_FALSE;
  }
  પાછા MZ_TRUE;
}

#ifndef MINIZ_NO_STDIO
સ્થિર size_t mz_zip_file_read_func(શૂન્ય *pOpaque, mz_uint64 file_ofs, શૂન્ય *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_int64 cur_ofs = MZ_FTELL64(pZip->m_pState->m_pFile);
  જો (((mz_int64)file_ofs < 0) || (((cur_ofs != (mz_int64)file_ofs)) && (MZ_FSEEK64(pZip->m_pState->m_pFile, (mz_int64)file_ofs, SEEK_SET))))
    પાછા 0;
  પાછા MZ_FREAD(pBuf, 1, n, pZip->m_pState->m_pFile);
}

mz_bool mz_zip_reader_init_file(mz_zip_archive *pZip, અચલ અક્ષર *pFilename, mz_uint32 flags)
{
  mz_uint64 file_size;
  MZ_FILE *pFile = MZ_FOPEN(pFilename, "rb");
  જો (!pFile)
    પાછા MZ_FALSE;
  જો (MZ_FSEEK64(pFile, 0, SEEK_END))
  {
    MZ_FCLOSE(pFile);
    પાછા MZ_FALSE;
  }
  file_size = MZ_FTELL64(pFile);
  જો (!mz_zip_reader_init_internal(pZip, flags))
  {
    MZ_FCLOSE(pFile);
    પાછા MZ_FALSE;
  }
  pZip->m_pRead = mz_zip_file_read_func;
  pZip->m_pIO_opaque = pZip;
  pZip->m_pState->m_pFile = pFile;
  pZip->m_archive_size = file_size;
  જો (!mz_zip_reader_read_central_dir(pZip, flags))
  {
    mz_zip_reader_end(pZip);
    પાછા MZ_FALSE;
  }
  પાછા MZ_TRUE;
}
#endif // #ifndef MINIZ_NO_STDIO

mz_uint mz_zip_reader_get_અંક_files(mz_zip_archive *pZip)
{
  પાછા pZip ? pZip->m_total_files : 0;
}

સ્થિર MZ_FORCEINLINE અચલ mz_uint8 *mz_zip_reader_get_cdh(mz_zip_archive *pZip, mz_uint file_index)
{
  જો ((!pZip) || (!pZip->m_pState) || (file_index >= pZip->m_total_files) || (pZip->m_zip_mode != MZ_ZIP_MODE_READING))
    પાછા ખાલી;
  પાછા &MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_index));
}

mz_bool mz_zip_reader_is_file_encrypted(mz_zip_archive *pZip, mz_uint file_index)
{
  mz_uint m_bit_flag;
  અચલ mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_index);
  જો (!p)
    પાછા MZ_FALSE;
  m_bit_flag = MZ_READ_LE16(p + MZ_ZIP_CDH_BIT_FLAG_OFS);
  પાછા (m_bit_flag & 1);
}

mz_bool mz_zip_reader_is_file_a_directory(mz_zip_archive *pZip, mz_uint file_index)
{
  mz_uint filename_len, external_attr;
  અચલ mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_index);
  જો (!p)
    પાછા MZ_FALSE;

  // First see if the filename ends with a '/' character.
  filename_len = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  જો (filename_len)
  {
    જો (*(p + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE + filename_len - 1) == '/')
      પાછા MZ_TRUE;
  }

  // Bugfix: This code was also checking if the internal attribute was non-zero, which wasn't correct.
  // Most/all zip writers (hopefully) set DOS file/directory attributes in the low 16-bits, so check for the DOS directory flag and ignore the source OS ID in the created by field.
  // FIXME: Remove this check? Is it necessary - we already check the filename.
  external_attr = MZ_READ_LE32(p + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS);
  જો ((external_attr & 0x10) != 0)
    પાછા MZ_TRUE;

  પાછા MZ_FALSE;
}

mz_bool mz_zip_reader_file_stat(mz_zip_archive *pZip, mz_uint file_index, mz_zip_archive_file_stat *pStat)
{
  mz_uint n;
  અચલ mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_index);
  જો ((!p) || (!pStat))
    પાછા MZ_FALSE;

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

  પાછા MZ_TRUE;
}

mz_uint mz_zip_reader_get_filename(mz_zip_archive *pZip, mz_uint file_index, અક્ષર *pFilename, mz_uint filename_buf_size)
{
  mz_uint n;
  અચલ mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_index);
  જો (!p) { જો (filename_buf_size) pFilename[0] = '\0'; પાછા 0; }
  n = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  જો (filename_buf_size)
  {
    n = MZ_MIN(n, filename_buf_size - 1);
    memcpy(pFilename, p + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE, n);
    pFilename[n] = '\0';
  }
  પાછા n + 1;
}

સ્થિર MZ_FORCEINLINE mz_bool mz_zip_reader_string_equal(અચલ અક્ષર *pA, અચલ અક્ષર *pB, mz_uint len, mz_uint flags)
{
  mz_uint i;
  જો (flags & MZ_ZIP_FLAG_CASE_SENSITIVE)
    પાછા 0 == memcmp(pA, pB, len);
  માટે (i = 0; i < len; ++i)
    જો (MZ_TOLOWER(pA[i]) != MZ_TOLOWER(pB[i]))
      પાછા MZ_FALSE;
  પાછા MZ_TRUE;
}

સ્થિર MZ_FORCEINLINE પૂર્ણાંક mz_zip_reader_filename_compare(અચલ mz_zip_array *pCentral_dir_array, અચલ mz_zip_array *pCentral_dir_offsets, mz_uint l_index, અચલ અક્ષર *pR, mz_uint r_len)
{
  અચલ mz_uint8 *pL = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, l_index)), *pE;
  mz_uint l_len = MZ_READ_LE16(pL + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  mz_uint8 l = 0, r = 0;
  pL += MZ_ZIP_CENTRAL_DIR_HEADER_SIZE;
  pE = pL + MZ_MIN(l_len, r_len);
  જ્યારે (pL < pE)
  {
    જો ((l = MZ_TOLOWER(*pL)) != (r = MZ_TOLOWER(*pR)))
      તોડો;
    pL++; pR++;
  }
  પાછા (pL == pE) ? (પૂર્ણાંક)(l_len - r_len) : (l - r);
}

સ્થિર પૂર્ણાંક mz_zip_reader_locate_file_દ્વિઅંકી_શોધ(mz_zip_archive *pZip, અચલ અક્ષર *pFilename)
{
  mz_zip_internal_state *pState = pZip->m_pState;
  અચલ mz_zip_array *pCentral_dir_offsets = &pState->m_central_dir_offsets;
  અચલ mz_zip_array *pCentral_dir = &pState->m_central_dir;
  mz_uint32 *pIndices = &MZ_ZIP_ARRAY_ELEMENT(&pState->m_sorted_central_dir_offsets, mz_uint32, 0);
  અચલ પૂર્ણાંક size = pZip->m_total_files;
  અચલ mz_uint filename_len = (mz_uint)strlen(pFilename);
  પૂર્ણાંક l = 0, h = size - 1;
  જ્યારે (l <= h)
  {
    પૂર્ણાંક m = (l + h) >> 1, file_index = pIndices[m], comp = mz_zip_reader_filename_compare(pCentral_dir, pCentral_dir_offsets, file_index, pFilename, filename_len);
    જો (!comp)
      પાછા file_index;
    નહીંતર જો (comp < 0)
      l = m + 1;
    નહીંતર
      h = m - 1;
  }
  પાછા -1;
}

પૂર્ણાંક mz_zip_reader_locate_file(mz_zip_archive *pZip, અચલ અક્ષર *pName, અચલ અક્ષર *pComment, mz_uint flags)
{
  mz_uint file_index; size_t name_len, comment_len;
  જો ((!pZip) || (!pZip->m_pState) || (!pName) || (pZip->m_zip_mode != MZ_ZIP_MODE_READING))
    પાછા -1;
  જો (((flags & (MZ_ZIP_FLAG_IGNORE_PATH | MZ_ZIP_FLAG_CASE_SENSITIVE)) == 0) && (!pComment) && (pZip->m_pState->m_sorted_central_dir_offsets.m_size))
    પાછા mz_zip_reader_locate_file_દ્વિઅંકી_શોધ(pZip, pName);
  name_len = strlen(pName); જો (name_len > 0xFFFF) પાછા -1;
  comment_len = pComment ? strlen(pComment) : 0; જો (comment_len > 0xFFFF) પાછા -1;
  માટે (file_index = 0; file_index < pZip->m_total_files; file_index++)
  {
    અચલ mz_uint8 *pHeader = &MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_index));
    mz_uint filename_len = MZ_READ_LE16(pHeader + MZ_ZIP_CDH_FILENAME_LEN_OFS);
    અચલ અક્ષર *pFilename = (અચલ અક્ષર *)pHeader + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE;
    જો (filename_len < name_len)
      ચાલુ;
    જો (comment_len)
    {
      mz_uint file_extra_len = MZ_READ_LE16(pHeader + MZ_ZIP_CDH_EXTRA_LEN_OFS), file_comment_len = MZ_READ_LE16(pHeader + MZ_ZIP_CDH_COMMENT_LEN_OFS);
      અચલ અક્ષર *pFile_comment = pFilename + filename_len + file_extra_len;
      જો ((file_comment_len != comment_len) || (!mz_zip_reader_string_equal(pComment, pFile_comment, file_comment_len, flags)))
        ચાલુ;
    }
    જો ((flags & MZ_ZIP_FLAG_IGNORE_PATH) && (filename_len))
    {
      પૂર્ણાંક ofs = filename_len - 1;
      કરો
      {
        જો ((pFilename[ofs] == '/') || (pFilename[ofs] == '\\') || (pFilename[ofs] == ':'))
          તોડો;
      } જ્યારે (--ofs >= 0);
      ofs++;
      pFilename += ofs; filename_len -= ofs;
    }
    જો ((filename_len == name_len) && (mz_zip_reader_string_equal(pName, pFilename, filename_len, flags)))
      પાછા file_index;
  }
  પાછા -1;
}

mz_bool mz_zip_reader_extract_to_mem_no_alloc(mz_zip_archive *pZip, mz_uint file_index, શૂન્ય *pBuf, size_t buf_size, mz_uint flags, શૂન્ય *pUser_read_buf, size_t user_read_buf_size)
{
  પૂર્ણાંક status = TINFL_STATUS_DONE;
  mz_uint64 needed_size, cur_file_ofs, comp_remaining, out_buf_ofs = 0, read_buf_size, read_buf_ofs = 0, read_buf_avail;
  mz_zip_archive_file_stat file_stat;
  શૂન્ય *pRead_buf;
  mz_uint32 local_header_u32[(MZ_ZIP_LOCAL_DIR_HEADER_SIZE + કદ(mz_uint32) - 1) / કદ(mz_uint32)]; mz_uint8 *pLocal_header = (mz_uint8 *)local_header_u32;
  tinfl_decompressor inflator;

  જો ((buf_size) && (!pBuf))
    પાછા MZ_FALSE;

  જો (!mz_zip_reader_file_stat(pZip, file_index, &file_stat))
    પાછા MZ_FALSE;

  // Empty file, or a directory (but not always a directory - I've seen odd zips with directories that have compressed data which inflates to 0 bytes)
  જો (!file_stat.m_comp_size)
    પાછા MZ_TRUE;

  // Entry is a subdirectory (I've seen old zips with dir entries which have compressed deflate data which inflates to 0 bytes, but these entries claim to uncompress to 512 bytes in the headers).
  // I'm torn how to handle this case - should it fail instead?
  જો (mz_zip_reader_is_file_a_directory(pZip, file_index))
    પાછા MZ_TRUE;

  // Encryption and patch files are not supported.
  જો (file_stat.m_bit_flag & (1 | 32))
    પાછા MZ_FALSE;

  // This function only supports stored and deflate.
  જો ((!(flags & MZ_ZIP_FLAG_COMPRESSED_DATA)) && (file_stat.m_method != 0) && (file_stat.m_method != MZ_DEFLATED))
    પાછા MZ_FALSE;

  // Ensure supplied output buffer is large enough.
  needed_size = (flags & MZ_ZIP_FLAG_COMPRESSED_DATA) ? file_stat.m_comp_size : file_stat.m_uncomp_size;
  જો (buf_size < needed_size)
    પાછા MZ_FALSE;

  // Read and parse the local directory entry.
  cur_file_ofs = file_stat.m_local_header_ofs;
  જો (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pLocal_header, MZ_ZIP_LOCAL_DIR_HEADER_SIZE) != MZ_ZIP_LOCAL_DIR_HEADER_SIZE)
    પાછા MZ_FALSE;
  જો (MZ_READ_LE32(pLocal_header) != MZ_ZIP_LOCAL_DIR_HEADER_SIG)
    પાછા MZ_FALSE;

  cur_file_ofs += MZ_ZIP_LOCAL_DIR_HEADER_SIZE + MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  જો ((cur_file_ofs + file_stat.m_comp_size) > pZip->m_archive_size)
    પાછા MZ_FALSE;

  જો ((flags & MZ_ZIP_FLAG_COMPRESSED_DATA) || (!file_stat.m_method))
  {
    // The file is stored or the caller has requested the compressed data.
    જો (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, (size_t)needed_size) != needed_size)
      પાછા MZ_FALSE;
    પાછા ((flags & MZ_ZIP_FLAG_COMPRESSED_DATA) != 0) || (mz_crc32(MZ_CRC32_INIT, (અચલ mz_uint8 *)pBuf, (size_t)file_stat.m_uncomp_size) == file_stat.m_crc32);
  }

  // Decompress the file either directly from memory or from a file input buffer.
  tinfl_init(&inflator);

  જો (pZip->m_pState->m_pMem)
  {
    // Read directly from the archive in memory.
    pRead_buf = (mz_uint8 *)pZip->m_pState->m_pMem + cur_file_ofs;
    read_buf_size = read_buf_avail = file_stat.m_comp_size;
    comp_remaining = 0;
  }
  નહીંતર જો (pUser_read_buf)
  {
    // Use a user provided read buffer.
    જો (!user_read_buf_size)
      પાછા MZ_FALSE;
    pRead_buf = (mz_uint8 *)pUser_read_buf;
    read_buf_size = user_read_buf_size;
    read_buf_avail = 0;
    comp_remaining = file_stat.m_comp_size;
  }
  નહીંતર
  {
    // Temporarily allocate a read buffer.
    read_buf_size = MZ_MIN(file_stat.m_comp_size, MZ_ZIP_MAX_IO_BUF_SIZE);
#ifdef _MSC_VER
    જો (((0, કદ(size_t) == કદ(mz_uint32))) && (read_buf_size > 0x7FFFFFFF))
#નહીંતર
    જો (((કદ(size_t) == કદ(mz_uint32))) && (read_buf_size > 0x7FFFFFFF))
#endif
      પાછા MZ_FALSE;
    જો (ખાલી == (pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)read_buf_size)))
      પાછા MZ_FALSE;
    read_buf_avail = 0;
    comp_remaining = file_stat.m_comp_size;
  }

  કરો
  {
    size_t in_buf_size, out_buf_size = (size_t)(file_stat.m_uncomp_size - out_buf_ofs);
    જો ((!read_buf_avail) && (!pZip->m_pState->m_pMem))
    {
      read_buf_avail = MZ_MIN(read_buf_size, comp_remaining);
      જો (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
      {
        status = TINFL_STATUS_FAILED;
        તોડો;
      }
      cur_file_ofs += read_buf_avail;
      comp_remaining -= read_buf_avail;
      read_buf_ofs = 0;
    }
    in_buf_size = (size_t)read_buf_avail;
    status = tinfl_decompress(&inflator, (mz_uint8 *)pRead_buf + read_buf_ofs, &in_buf_size, (mz_uint8 *)pBuf, (mz_uint8 *)pBuf + out_buf_ofs, &out_buf_size, TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF | (comp_remaining ? TINFL_FLAG_HAS_MORE_આગત : 0));
    read_buf_avail -= in_buf_size;
    read_buf_ofs += in_buf_size;
    out_buf_ofs += out_buf_size;
  } જ્યારે (status == TINFL_STATUS_NEEDS_MORE_આગત);

  જો (status == TINFL_STATUS_DONE)
  {
    // Make sure the entire file was decompressed, and check its CRC.
    જો ((out_buf_ofs != file_stat.m_uncomp_size) || (mz_crc32(MZ_CRC32_INIT, (અચલ mz_uint8 *)pBuf, (size_t)file_stat.m_uncomp_size) != file_stat.m_crc32))
      status = TINFL_STATUS_FAILED;
  }

  જો ((!pZip->m_pState->m_pMem) && (!pUser_read_buf))
    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);

  પાછા status == TINFL_STATUS_DONE;
}

mz_bool mz_zip_reader_extract_file_to_mem_no_alloc(mz_zip_archive *pZip, અચલ અક્ષર *pFilename, શૂન્ય *pBuf, size_t buf_size, mz_uint flags, શૂન્ય *pUser_read_buf, size_t user_read_buf_size)
{
  પૂર્ણાંક file_index = mz_zip_reader_locate_file(pZip, pFilename, ખાલી, flags);
  જો (file_index < 0)
    પાછા MZ_FALSE;
  પાછા mz_zip_reader_extract_to_mem_no_alloc(pZip, file_index, pBuf, buf_size, flags, pUser_read_buf, user_read_buf_size);
}

mz_bool mz_zip_reader_extract_to_mem(mz_zip_archive *pZip, mz_uint file_index, શૂન્ય *pBuf, size_t buf_size, mz_uint flags)
{
  પાછા mz_zip_reader_extract_to_mem_no_alloc(pZip, file_index, pBuf, buf_size, flags, ખાલી, 0);
}

mz_bool mz_zip_reader_extract_file_to_mem(mz_zip_archive *pZip, અચલ અક્ષર *pFilename, શૂન્ય *pBuf, size_t buf_size, mz_uint flags)
{
  પાછા mz_zip_reader_extract_file_to_mem_no_alloc(pZip, pFilename, pBuf, buf_size, flags, ખાલી, 0);
}

શૂન્ય *mz_zip_reader_extract_to_heap(mz_zip_archive *pZip, mz_uint file_index, size_t *pSize, mz_uint flags)
{
  mz_uint64 comp_size, uncomp_size, alloc_size;
  અચલ mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_index);
  શૂન્ય *pBuf;

  જો (pSize)
    *pSize = 0;
  જો (!p)
    પાછા ખાલી;

  comp_size = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_SIZE_OFS);
  uncomp_size = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_SIZE_OFS);

  alloc_size = (flags & MZ_ZIP_FLAG_COMPRESSED_DATA) ? comp_size : uncomp_size;
#ifdef _MSC_VER
  જો (((0, કદ(size_t) == કદ(mz_uint32))) && (alloc_size > 0x7FFFFFFF))
#નહીંતર
  જો (((કદ(size_t) == કદ(mz_uint32))) && (alloc_size > 0x7FFFFFFF))
#endif
    પાછા ખાલી;
  જો (ખાલી == (pBuf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)alloc_size)))
    પાછા ખાલી;

  જો (!mz_zip_reader_extract_to_mem(pZip, file_index, pBuf, (size_t)alloc_size, flags))
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
    પાછા ખાલી;
  }

  જો (pSize) *pSize = (size_t)alloc_size;
  પાછા pBuf;
}

શૂન્ય *mz_zip_reader_extract_file_to_heap(mz_zip_archive *pZip, અચલ અક્ષર *pFilename, size_t *pSize, mz_uint flags)
{
  પૂર્ણાંક file_index = mz_zip_reader_locate_file(pZip, pFilename, ખાલી, flags);
  જો (file_index < 0)
  {
    જો (pSize) *pSize = 0;
    પાછા MZ_FALSE;
  }
  પાછા mz_zip_reader_extract_to_heap(pZip, file_index, pSize, flags);
}

mz_bool mz_zip_reader_extract_to_callback(mz_zip_archive *pZip, mz_uint file_index, mz_file_write_func pCallback, શૂન્ય *pOpaque, mz_uint flags)
{
  પૂર્ણાંક status = TINFL_STATUS_DONE; mz_uint file_crc32 = MZ_CRC32_INIT;
  mz_uint64 read_buf_size, read_buf_ofs = 0, read_buf_avail, comp_remaining, out_buf_ofs = 0, cur_file_ofs;
  mz_zip_archive_file_stat file_stat;
  શૂન્ય *pRead_buf = ખાલી; શૂન્ય *pWrite_buf = ખાલી;
  mz_uint32 local_header_u32[(MZ_ZIP_LOCAL_DIR_HEADER_SIZE + કદ(mz_uint32) - 1) / કદ(mz_uint32)]; mz_uint8 *pLocal_header = (mz_uint8 *)local_header_u32;

  જો (!mz_zip_reader_file_stat(pZip, file_index, &file_stat))
    પાછા MZ_FALSE;

  // Empty file, or a directory (but not always a directory - I've seen odd zips with directories that have compressed data which inflates to 0 bytes)
  જો (!file_stat.m_comp_size)
    પાછા MZ_TRUE;

  // Entry is a subdirectory (I've seen old zips with dir entries which have compressed deflate data which inflates to 0 bytes, but these entries claim to uncompress to 512 bytes in the headers).
  // I'm torn how to handle this case - should it fail instead?
  જો (mz_zip_reader_is_file_a_directory(pZip, file_index))
    પાછા MZ_TRUE;

  // Encryption and patch files are not supported.
  જો (file_stat.m_bit_flag & (1 | 32))
    પાછા MZ_FALSE;

  // This function only supports stored and deflate.
  જો ((!(flags & MZ_ZIP_FLAG_COMPRESSED_DATA)) && (file_stat.m_method != 0) && (file_stat.m_method != MZ_DEFLATED))
    પાછા MZ_FALSE;

  // Read and parse the local directory entry.
  cur_file_ofs = file_stat.m_local_header_ofs;
  જો (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pLocal_header, MZ_ZIP_LOCAL_DIR_HEADER_SIZE) != MZ_ZIP_LOCAL_DIR_HEADER_SIZE)
    પાછા MZ_FALSE;
  જો (MZ_READ_LE32(pLocal_header) != MZ_ZIP_LOCAL_DIR_HEADER_SIG)
    પાછા MZ_FALSE;

  cur_file_ofs += MZ_ZIP_LOCAL_DIR_HEADER_SIZE + MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  જો ((cur_file_ofs + file_stat.m_comp_size) > pZip->m_archive_size)
    પાછા MZ_FALSE;

  // Decompress the file either directly from memory or from a file input buffer.
  જો (pZip->m_pState->m_pMem)
  {
    pRead_buf = (mz_uint8 *)pZip->m_pState->m_pMem + cur_file_ofs;
    read_buf_size = read_buf_avail = file_stat.m_comp_size;
    comp_remaining = 0;
  }
  નહીંતર
  {
    read_buf_size = MZ_MIN(file_stat.m_comp_size, MZ_ZIP_MAX_IO_BUF_SIZE);
    જો (ખાલી == (pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)read_buf_size)))
      પાછા MZ_FALSE;
    read_buf_avail = 0;
    comp_remaining = file_stat.m_comp_size;
  }

  જો ((flags & MZ_ZIP_FLAG_COMPRESSED_DATA) || (!file_stat.m_method))
  {
    // The file is stored or the caller has requested the compressed data.
    જો (pZip->m_pState->m_pMem)
    {
#ifdef _MSC_VER
      જો (((0, કદ(size_t) == કદ(mz_uint32))) && (file_stat.m_comp_size > 0xFFFFFFFF))
#નહીંતર
      જો (((કદ(size_t) == કદ(mz_uint32))) && (file_stat.m_comp_size > 0xFFFFFFFF))
#endif
        પાછા MZ_FALSE;
      જો (pCallback(pOpaque, out_buf_ofs, pRead_buf, (size_t)file_stat.m_comp_size) != file_stat.m_comp_size)
        status = TINFL_STATUS_FAILED;
      નહીંતર જો (!(flags & MZ_ZIP_FLAG_COMPRESSED_DATA))
        file_crc32 = (mz_uint32)mz_crc32(file_crc32, (અચલ mz_uint8 *)pRead_buf, (size_t)file_stat.m_comp_size);
      cur_file_ofs += file_stat.m_comp_size;
      out_buf_ofs += file_stat.m_comp_size;
      comp_remaining = 0;
    }
    નહીંતર
    {
      જ્યારે (comp_remaining)
      {
        read_buf_avail = MZ_MIN(read_buf_size, comp_remaining);
        જો (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
        {
          status = TINFL_STATUS_FAILED;
          તોડો;
        }

        જો (!(flags & MZ_ZIP_FLAG_COMPRESSED_DATA))
          file_crc32 = (mz_uint32)mz_crc32(file_crc32, (અચલ mz_uint8 *)pRead_buf, (size_t)read_buf_avail);

        જો (pCallback(pOpaque, out_buf_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
        {
          status = TINFL_STATUS_FAILED;
          તોડો;
        }
        cur_file_ofs += read_buf_avail;
        out_buf_ofs += read_buf_avail;
        comp_remaining -= read_buf_avail;
      }
    }
  }
  નહીંતર
  {
    tinfl_decompressor inflator;
    tinfl_init(&inflator);

    જો (ખાલી == (pWrite_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, TINFL_LZ_DICT_SIZE)))
      status = TINFL_STATUS_FAILED;
    નહીંતર
    {
      કરો
      {
        mz_uint8 *pWrite_buf_cur = (mz_uint8 *)pWrite_buf + (out_buf_ofs & (TINFL_LZ_DICT_SIZE - 1));
        size_t in_buf_size, out_buf_size = TINFL_LZ_DICT_SIZE - (out_buf_ofs & (TINFL_LZ_DICT_SIZE - 1));
        જો ((!read_buf_avail) && (!pZip->m_pState->m_pMem))
        {
          read_buf_avail = MZ_MIN(read_buf_size, comp_remaining);
          જો (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
          {
            status = TINFL_STATUS_FAILED;
            તોડો;
          }
          cur_file_ofs += read_buf_avail;
          comp_remaining -= read_buf_avail;
          read_buf_ofs = 0;
        }

        in_buf_size = (size_t)read_buf_avail;
        status = tinfl_decompress(&inflator, (અચલ mz_uint8 *)pRead_buf + read_buf_ofs, &in_buf_size, (mz_uint8 *)pWrite_buf, pWrite_buf_cur, &out_buf_size, comp_remaining ? TINFL_FLAG_HAS_MORE_આગત : 0);
        read_buf_avail -= in_buf_size;
        read_buf_ofs += in_buf_size;

        જો (out_buf_size)
        {
          જો (pCallback(pOpaque, out_buf_ofs, pWrite_buf_cur, out_buf_size) != out_buf_size)
          {
            status = TINFL_STATUS_FAILED;
            તોડો;
          }
          file_crc32 = (mz_uint32)mz_crc32(file_crc32, pWrite_buf_cur, out_buf_size);
          જો ((out_buf_ofs += out_buf_size) > file_stat.m_uncomp_size)
          {
            status = TINFL_STATUS_FAILED;
            તોડો;
          }
        }
      } જ્યારે ((status == TINFL_STATUS_NEEDS_MORE_આગત) || (status == TINFL_STATUS_HAS_MORE_OUTPUT));
    }
  }

  જો ((status == TINFL_STATUS_DONE) && (!(flags & MZ_ZIP_FLAG_COMPRESSED_DATA)))
  {
    // Make sure the entire file was decompressed, and check its CRC.
    જો ((out_buf_ofs != file_stat.m_uncomp_size) || (file_crc32 != file_stat.m_crc32))
      status = TINFL_STATUS_FAILED;
  }

  જો (!pZip->m_pState->m_pMem)
    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
  જો (pWrite_buf)
    pZip->m_pFree(pZip->m_pAlloc_opaque, pWrite_buf);

  પાછા status == TINFL_STATUS_DONE;
}

mz_bool mz_zip_reader_extract_file_to_callback(mz_zip_archive *pZip, અચલ અક્ષર *pFilename, mz_file_write_func pCallback, શૂન્ય *pOpaque, mz_uint flags)
{
  પૂર્ણાંક file_index = mz_zip_reader_locate_file(pZip, pFilename, ખાલી, flags);
  જો (file_index < 0)
    પાછા MZ_FALSE;
  પાછા mz_zip_reader_extract_to_callback(pZip, file_index, pCallback, pOpaque, flags);
}

#ifndef MINIZ_NO_STDIO
સ્થિર size_t mz_zip_file_write_callback(શૂન્ય *pOpaque, mz_uint64 ofs, અચલ શૂન્ય *pBuf, size_t n)
{
  (શૂન્ય)ofs; પાછા MZ_FWRITE(pBuf, 1, n, (MZ_FILE*)pOpaque);
}

mz_bool mz_zip_reader_extract_to_file(mz_zip_archive *pZip, mz_uint file_index, અચલ અક્ષર *pDst_filename, mz_uint flags)
{
  mz_bool status;
  mz_zip_archive_file_stat file_stat;
  MZ_FILE *pFile;
  જો (!mz_zip_reader_file_stat(pZip, file_index, &file_stat))
    પાછા MZ_FALSE;
  pFile = MZ_FOPEN(pDst_filename, "wb");
  જો (!pFile)
    પાછા MZ_FALSE;
  status = mz_zip_reader_extract_to_callback(pZip, file_index, mz_zip_file_write_callback, pFile, flags);
  જો (MZ_FCLOSE(pFile) == EOF)
    પાછા MZ_FALSE;
#ifndef MINIZ_NO_TIME
  જો (status)
    mz_zip_set_file_times(pDst_filename, file_stat.m_time, file_stat.m_time);
#endif
  પાછા status;
}
#endif // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_reader_end(mz_zip_archive *pZip)
{
  જો ((!pZip) || (!pZip->m_pState) || (!pZip->m_pAlloc) || (!pZip->m_pFree) || (pZip->m_zip_mode != MZ_ZIP_MODE_READING))
    પાછા MZ_FALSE;

  જો (pZip->m_pState)
  {
    mz_zip_internal_state *pState = pZip->m_pState; pZip->m_pState = ખાલી;
    mz_zip_array_clear(pZip, &pState->m_central_dir);
    mz_zip_array_clear(pZip, &pState->m_central_dir_offsets);
    mz_zip_array_clear(pZip, &pState->m_sorted_central_dir_offsets);

#ifndef MINIZ_NO_STDIO
    જો (pState->m_pFile)
    {
      MZ_FCLOSE(pState->m_pFile);
      pState->m_pFile = ખાલી;
    }
#endif // #ifndef MINIZ_NO_STDIO

    pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
  }
  pZip->m_zip_mode = MZ_ZIP_MODE_INVALID;

  પાછા MZ_TRUE;
}

#ifndef MINIZ_NO_STDIO
mz_bool mz_zip_reader_extract_file_to_file(mz_zip_archive *pZip, અચલ અક્ષર *pArchive_filename, અચલ અક્ષર *pDst_filename, mz_uint flags)
{
  પૂર્ણાંક file_index = mz_zip_reader_locate_file(pZip, pArchive_filename, ખાલી, flags);
  જો (file_index < 0)
    પાછા MZ_FALSE;
  પાછા mz_zip_reader_extract_to_file(pZip, file_index, pDst_filename, flags);
}
#endif

// ------------------- .ZIP archive writing

#ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

સ્થિર શૂન્ય mz_write_le16(mz_uint8 *p, mz_uint16 v) { p[0] = (mz_uint8)v; p[1] = (mz_uint8)(v >> 8); }
સ્થિર શૂન્ય mz_write_le32(mz_uint8 *p, mz_uint32 v) { p[0] = (mz_uint8)v; p[1] = (mz_uint8)(v >> 8); p[2] = (mz_uint8)(v >> 16); p[3] = (mz_uint8)(v >> 24); }
#define MZ_WRITE_LE16(p, v) mz_write_le16((mz_uint8 *)(p), (mz_uint16)(v))
#define MZ_WRITE_LE32(p, v) mz_write_le32((mz_uint8 *)(p), (mz_uint32)(v))

mz_bool mz_zip_writer_init(mz_zip_archive *pZip, mz_uint64 existing_size)
{
  જો ((!pZip) || (pZip->m_pState) || (!pZip->m_pWrite) || (pZip->m_zip_mode != MZ_ZIP_MODE_INVALID))
    પાછા MZ_FALSE;

  જો (pZip->m_file_offset_alignment)
  {
    // Ensure user specified file offset alignment is a power of 2.
    જો (pZip->m_file_offset_alignment & (pZip->m_file_offset_alignment - 1))
      પાછા MZ_FALSE;
  }

  જો (!pZip->m_pAlloc) pZip->m_pAlloc = def_alloc_func;
  જો (!pZip->m_pFree) pZip->m_pFree = def_free_func;
  જો (!pZip->m_pRealloc) pZip->m_pRealloc = def_realloc_func;

  pZip->m_zip_mode = MZ_ZIP_MODE_WRITING;
  pZip->m_archive_size = existing_size;
  pZip->m_central_directory_file_ofs = 0;
  pZip->m_total_files = 0;

  જો (ખાલી == (pZip->m_pState = (mz_zip_internal_state *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, કદ(mz_zip_internal_state))))
    પાછા MZ_FALSE;
  memset(pZip->m_pState, 0, કદ(mz_zip_internal_state));
  MZ_ZIP_ARRAY_SET_ELEMENT_SIZE(&pZip->m_pState->m_central_dir, કદ(mz_uint8));
  MZ_ZIP_ARRAY_SET_ELEMENT_SIZE(&pZip->m_pState->m_central_dir_offsets, કદ(mz_uint32));
  MZ_ZIP_ARRAY_SET_ELEMENT_SIZE(&pZip->m_pState->m_sorted_central_dir_offsets, કદ(mz_uint32));
  પાછા MZ_TRUE;
}

સ્થિર size_t mz_zip_heap_write_func(શૂન્ય *pOpaque, mz_uint64 file_ofs, અચલ શૂન્ય *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_zip_internal_state *pState = pZip->m_pState;
  mz_uint64 new_size = MZ_MAX(file_ofs + n, pState->m_mem_size);
#ifdef _MSC_VER
  જો ((!n) || ((0, કદ(size_t) == કદ(mz_uint32)) && (new_size > 0x7FFFFFFF)))
#નહીંતર
  જો ((!n) || ((કદ(size_t) == કદ(mz_uint32)) && (new_size > 0x7FFFFFFF)))
#endif
    પાછા 0;
  જો (new_size > pState->m_mem_capacity)
  {
    શૂન્ય *pNew_block;
    size_t new_capacity = MZ_MAX(64, pState->m_mem_capacity); જ્યારે (new_capacity < new_size) new_capacity *= 2;
    જો (ખાલી == (pNew_block = pZip->m_pRealloc(pZip->m_pAlloc_opaque, pState->m_pMem, 1, new_capacity)))
      પાછા 0;
    pState->m_pMem = pNew_block; pState->m_mem_capacity = new_capacity;
  }
  memcpy((mz_uint8 *)pState->m_pMem + file_ofs, pBuf, n);
  pState->m_mem_size = (size_t)new_size;
  પાછા n;
}

mz_bool mz_zip_writer_init_heap(mz_zip_archive *pZip, size_t size_to_reserve_at_beginning, size_t initial_allocation_size)
{
  pZip->m_pWrite = mz_zip_heap_write_func;
  pZip->m_pIO_opaque = pZip;
  જો (!mz_zip_writer_init(pZip, size_to_reserve_at_beginning))
    પાછા MZ_FALSE;
  જો (0 != (initial_allocation_size = MZ_MAX(initial_allocation_size, size_to_reserve_at_beginning)))
  {
    જો (ખાલી == (pZip->m_pState->m_pMem = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, initial_allocation_size)))
    {
      mz_zip_writer_end(pZip);
      પાછા MZ_FALSE;
    }
    pZip->m_pState->m_mem_capacity = initial_allocation_size;
  }
  પાછા MZ_TRUE;
}

#ifndef MINIZ_NO_STDIO
સ્થિર size_t mz_zip_file_write_func(શૂન્ય *pOpaque, mz_uint64 file_ofs, અચલ શૂન્ય *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_int64 cur_ofs = MZ_FTELL64(pZip->m_pState->m_pFile);
  જો (((mz_int64)file_ofs < 0) || (((cur_ofs != (mz_int64)file_ofs)) && (MZ_FSEEK64(pZip->m_pState->m_pFile, (mz_int64)file_ofs, SEEK_SET))))
    પાછા 0;
  પાછા MZ_FWRITE(pBuf, 1, n, pZip->m_pState->m_pFile);
}

mz_bool mz_zip_writer_init_file(mz_zip_archive *pZip, અચલ અક્ષર *pFilename, mz_uint64 size_to_reserve_at_beginning)
{
  MZ_FILE *pFile;
  pZip->m_pWrite = mz_zip_file_write_func;
  pZip->m_pIO_opaque = pZip;
  જો (!mz_zip_writer_init(pZip, size_to_reserve_at_beginning))
    પાછા MZ_FALSE;
  જો (ખાલી == (pFile = MZ_FOPEN(pFilename, "wb")))
  {
    mz_zip_writer_end(pZip);
    પાછા MZ_FALSE;
  }
  pZip->m_pState->m_pFile = pFile;
  જો (size_to_reserve_at_beginning)
  {
    mz_uint64 cur_ofs = 0; અક્ષર buf[4096]; MZ_CLEAR_ARR(buf);
    કરો
    {
      size_t n = (size_t)MZ_MIN(કદ(buf), size_to_reserve_at_beginning);
      જો (pZip->m_pWrite(pZip->m_pIO_opaque, cur_ofs, buf, n) != n)
      {
        mz_zip_writer_end(pZip);
        પાછા MZ_FALSE;
      }
      cur_ofs += n; size_to_reserve_at_beginning -= n;
    } જ્યારે (size_to_reserve_at_beginning);
  }
  પાછા MZ_TRUE;
}
#endif // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_writer_init_from_reader(mz_zip_archive *pZip, અચલ અક્ષર *pFilename)
{
  mz_zip_internal_state *pState;
  જો ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_mode != MZ_ZIP_MODE_READING))
    પાછા MZ_FALSE;
  // No sense in trying to write to an archive that's already at the support max size
  જો ((pZip->m_total_files == 0xFFFF) || ((pZip->m_archive_size + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE + MZ_ZIP_LOCAL_DIR_HEADER_SIZE) > 0xFFFFFFFF))
    પાછા MZ_FALSE;

  pState = pZip->m_pState;

  જો (pState->m_pFile)
  {
#ifdef MINIZ_NO_STDIO
    pFilename; પાછા MZ_FALSE;
#નહીંતર
    // Archive is being read from stdio - try to reopen as writable.
    જો (pZip->m_pIO_opaque != pZip)
      પાછા MZ_FALSE;
    જો (!pFilename)
      પાછા MZ_FALSE;
    pZip->m_pWrite = mz_zip_file_write_func;
    જો (ખાલી == (pState->m_pFile = MZ_FREOPEN(pFilename, "r+b", pState->m_pFile)))
    {
      // The mz_zip_archive is now in a bogus state because pState->m_pFile is NULL, so just close it.
      mz_zip_reader_end(pZip);
      પાછા MZ_FALSE;
    }
#endif // #ifdef MINIZ_NO_STDIO
  }
  નહીંતર જો (pState->m_pMem)
  {
    // Archive lives in a memory block. Assume it's from the heap that we can resize using the realloc callback.
    જો (pZip->m_pIO_opaque != pZip)
      પાછા MZ_FALSE;
    pState->m_mem_capacity = pState->m_mem_size;
    pZip->m_pWrite = mz_zip_heap_write_func;
  }
  // Archive is being read via a user provided read function - make sure the user has specified a write function too.
  નહીંતર જો (!pZip->m_pWrite)
    પાછા MZ_FALSE;

  // Start writing new files at the archive's current central directory location.
  pZip->m_archive_size = pZip->m_central_directory_file_ofs;
  pZip->m_zip_mode = MZ_ZIP_MODE_WRITING;
  pZip->m_central_directory_file_ofs = 0;

  પાછા MZ_TRUE;
}

mz_bool mz_zip_writer_add_mem(mz_zip_archive *pZip, અચલ અક્ષર *pArchive_name, અચલ શૂન્ય *pBuf, size_t buf_size, mz_uint level_and_flags)
{
  પાછા mz_zip_writer_add_mem_ex(pZip, pArchive_name, pBuf, buf_size, ખાલી, 0, level_and_flags, 0, 0);
}

પ્રકારવ્યાખ્યા સંરચના
{
  mz_zip_archive *m_pZip;
  mz_uint64 m_cur_archive_file_ofs;
  mz_uint64 m_comp_size;
} mz_zip_writer_add_state;

સ્થિર mz_bool mz_zip_writer_add_put_buf_callback(અચલ શૂન્ય* pBuf, પૂર્ણાંક len, શૂન્ય *pUser)
{
  mz_zip_writer_add_state *pState = (mz_zip_writer_add_state *)pUser;
  જો ((પૂર્ણાંક)pState->m_pZip->m_pWrite(pState->m_pZip->m_pIO_opaque, pState->m_cur_archive_file_ofs, pBuf, len) != len)
    પાછા MZ_FALSE;
  pState->m_cur_archive_file_ofs += len;
  pState->m_comp_size += len;
  પાછા MZ_TRUE;
}

સ્થિર mz_bool mz_zip_writer_create_local_dir_header(mz_zip_archive *pZip, mz_uint8 *pDst, mz_uint16 filename_size, mz_uint16 extra_size, mz_uint64 uncomp_size, mz_uint64 comp_size, mz_uint32 uncomp_crc32, mz_uint16 method, mz_uint16 bit_flags, mz_uint16 dos_time, mz_uint16 dos_date)
{
  (શૂન્ય)pZip;
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
  પાછા MZ_TRUE;
}

સ્થિર mz_bool mz_zip_writer_create_central_dir_header(mz_zip_archive *pZip, mz_uint8 *pDst, mz_uint16 filename_size, mz_uint16 extra_size, mz_uint16 comment_size, mz_uint64 uncomp_size, mz_uint64 comp_size, mz_uint32 uncomp_crc32, mz_uint16 method, mz_uint16 bit_flags, mz_uint16 dos_time, mz_uint16 dos_date, mz_uint64 local_header_ofs, mz_uint32 ext_attributes)
{
  (શૂન્ય)pZip;
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
  પાછા MZ_TRUE;
}

સ્થિર mz_bool mz_zip_writer_add_to_central_dir(mz_zip_archive *pZip, અચલ અક્ષર *pFilename, mz_uint16 filename_size, અચલ શૂન્ય *pExtra, mz_uint16 extra_size, અચલ શૂન્ય *pComment, mz_uint16 comment_size, mz_uint64 uncomp_size, mz_uint64 comp_size, mz_uint32 uncomp_crc32, mz_uint16 method, mz_uint16 bit_flags, mz_uint16 dos_time, mz_uint16 dos_date, mz_uint64 local_header_ofs, mz_uint32 ext_attributes)
{
  mz_zip_internal_state *pState = pZip->m_pState;
  mz_uint32 central_dir_ofs = (mz_uint32)pState->m_central_dir.m_size;
  size_t orig_central_dir_size = pState->m_central_dir.m_size;
  mz_uint8 central_dir_header[MZ_ZIP_CENTRAL_DIR_HEADER_SIZE];

  // No zip64 support yet
  જો ((local_header_ofs > 0xFFFFFFFF) || (((mz_uint64)pState->m_central_dir.m_size + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE + filename_size + extra_size + comment_size) > 0xFFFFFFFF))
    પાછા MZ_FALSE;

  જો (!mz_zip_writer_create_central_dir_header(pZip, central_dir_header, filename_size, extra_size, comment_size, uncomp_size, comp_size, uncomp_crc32, method, bit_flags, dos_time, dos_date, local_header_ofs, ext_attributes))
    પાછા MZ_FALSE;

  જો ((!mz_zip_array_ધકેલો_back(pZip, &pState->m_central_dir, central_dir_header, MZ_ZIP_CENTRAL_DIR_HEADER_SIZE)) ||
      (!mz_zip_array_ધકેલો_back(pZip, &pState->m_central_dir, pFilename, filename_size)) ||
      (!mz_zip_array_ધકેલો_back(pZip, &pState->m_central_dir, pExtra, extra_size)) ||
      (!mz_zip_array_ધકેલો_back(pZip, &pState->m_central_dir, pComment, comment_size)) ||
      (!mz_zip_array_ધકેલો_back(pZip, &pState->m_central_dir_offsets, &central_dir_ofs, 1)))
  {
    // Try to push the central directory array back into its original state.
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_size, MZ_FALSE);
    પાછા MZ_FALSE;
  }

  પાછા MZ_TRUE;
}

સ્થિર mz_bool mz_zip_writer_validate_archive_name(અચલ અક્ષર *pArchive_name)
{
  // Basic ZIP archive filename validity checks: Valid filenames cannot start with a forward slash, cannot contain a drive letter, and cannot use DOS-style backward slashes.
  જો (*pArchive_name == '/')
    પાછા MZ_FALSE;
  જ્યારે (*pArchive_name)
  {
    જો ((*pArchive_name == '\\') || (*pArchive_name == ':'))
      પાછા MZ_FALSE;
    pArchive_name++;
  }
  પાછા MZ_TRUE;
}

સ્થિર mz_uint mz_zip_writer_compute_padding_needed_for_file_alignment(mz_zip_archive *pZip)
{
  mz_uint32 n;
  જો (!pZip->m_file_offset_alignment)
    પાછા 0;
  n = (mz_uint32)(pZip->m_archive_size & (pZip->m_file_offset_alignment - 1));
  પાછા (pZip->m_file_offset_alignment - n) & (pZip->m_file_offset_alignment - 1);
}

સ્થિર mz_bool mz_zip_writer_write_zeros(mz_zip_archive *pZip, mz_uint64 cur_file_ofs, mz_uint32 n)
{
  અક્ષર buf[4096];
  memset(buf, 0, MZ_MIN(કદ(buf), n));
  જ્યારે (n)
  {
    mz_uint32 s = MZ_MIN(કદ(buf), n);
    જો (pZip->m_pWrite(pZip->m_pIO_opaque, cur_file_ofs, buf, s) != s)
      પાછા MZ_FALSE;
    cur_file_ofs += s; n -= s;
  }
  પાછા MZ_TRUE;
}

mz_bool mz_zip_writer_add_mem_ex(mz_zip_archive *pZip, અચલ અક્ષર *pArchive_name, અચલ શૂન્ય *pBuf, size_t buf_size, અચલ શૂન્ય *pComment, mz_uint16 comment_size, mz_uint level_and_flags, mz_uint64 uncomp_size, mz_uint32 uncomp_crc32)
{
  mz_uint16 method = 0, dos_time = 0, dos_date = 0;
  mz_uint level, ext_attributes = 0, અંક_alignment_padding_bytes;
  mz_uint64 local_dir_header_ofs = pZip->m_archive_size, cur_archive_file_ofs = pZip->m_archive_size, comp_size = 0;
  size_t archive_name_size;
  mz_uint8 local_dir_header[MZ_ZIP_LOCAL_DIR_HEADER_SIZE];
  tdefl_compressor *pComp = ખાલી;
  mz_bool store_data_uncompressed;
  mz_zip_internal_state *pState;

  જો ((પૂર્ણાંક)level_and_flags < 0)
    level_and_flags = MZ_DEFAULT_LEVEL;
  level = level_and_flags & 0xF;
  store_data_uncompressed = ((!level) || (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_DATA));

  જો ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_mode != MZ_ZIP_MODE_WRITING) || ((buf_size) && (!pBuf)) || (!pArchive_name) || ((comment_size) && (!pComment)) || (pZip->m_total_files == 0xFFFF) || (level > MZ_UBER_COMPRESSION))
    પાછા MZ_FALSE;

  pState = pZip->m_pState;

  જો ((!(level_and_flags & MZ_ZIP_FLAG_COMPRESSED_DATA)) && (uncomp_size))
    પાછા MZ_FALSE;
  // No zip64 support yet
  જો ((buf_size > 0xFFFFFFFF) || (uncomp_size > 0xFFFFFFFF))
    પાછા MZ_FALSE;
  જો (!mz_zip_writer_validate_archive_name(pArchive_name))
    પાછા MZ_FALSE;

#ifndef MINIZ_NO_TIME
  {
    time_t cur_time; time(&cur_time);
    mz_zip_time_to_dos_time(cur_time, &dos_time, &dos_date);
  }
#endif // #ifndef MINIZ_NO_TIME

  archive_name_size = strlen(pArchive_name);
  જો (archive_name_size > 0xFFFF)
    પાછા MZ_FALSE;

  અંક_alignment_padding_bytes = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  જો ((pZip->m_total_files == 0xFFFF) || ((pZip->m_archive_size + અંક_alignment_padding_bytes + MZ_ZIP_LOCAL_DIR_HEADER_SIZE + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE + comment_size + archive_name_size) > 0xFFFFFFFF))
    પાછા MZ_FALSE;

  જો ((archive_name_size) && (pArchive_name[archive_name_size - 1] == '/'))
  {
    // Set DOS Subdirectory attribute bit.
    ext_attributes |= 0x10;
    // Subdirectories cannot contain data.
    જો ((buf_size) || (uncomp_size))
      પાછા MZ_FALSE;
  }

  // Try to do any allocations before writing to the archive, so if an allocation fails the file remains unmodified. (A good idea if we're doing an in-place modification.)
  જો ((!mz_zip_array_ensure_room(pZip, &pState->m_central_dir, MZ_ZIP_CENTRAL_DIR_HEADER_SIZE + archive_name_size + comment_size)) || (!mz_zip_array_ensure_room(pZip, &pState->m_central_dir_offsets, 1)))
    પાછા MZ_FALSE;

  જો ((!store_data_uncompressed) && (buf_size))
  {
    જો (ખાલી == (pComp = (tdefl_compressor *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, કદ(tdefl_compressor))))
      પાછા MZ_FALSE;
  }

  જો (!mz_zip_writer_write_zeros(pZip, cur_archive_file_ofs, અંક_alignment_padding_bytes + કદ(local_dir_header)))
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
    પાછા MZ_FALSE;
  }
  local_dir_header_ofs += અંક_alignment_padding_bytes;
  જો (pZip->m_file_offset_alignment) { MZ_ASSERT((local_dir_header_ofs & (pZip->m_file_offset_alignment - 1)) == 0); }
  cur_archive_file_ofs += અંક_alignment_padding_bytes + કદ(local_dir_header);

  MZ_CLEAR_ARR(local_dir_header);
  જો (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pArchive_name, archive_name_size) != archive_name_size)
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
    પાછા MZ_FALSE;
  }
  cur_archive_file_ofs += archive_name_size;

  જો (!(level_and_flags & MZ_ZIP_FLAG_COMPRESSED_DATA))
  {
    uncomp_crc32 = (mz_uint32)mz_crc32(MZ_CRC32_INIT, (અચલ mz_uint8*)pBuf, buf_size);
    uncomp_size = buf_size;
    જો (uncomp_size <= 3)
    {
      level = 0;
      store_data_uncompressed = MZ_TRUE;
    }
  }

  જો (store_data_uncompressed)
  {
    જો (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pBuf, buf_size) != buf_size)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
      પાછા MZ_FALSE;
    }

    cur_archive_file_ofs += buf_size;
    comp_size = buf_size;

    જો (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_DATA)
      method = MZ_DEFLATED;
  }
  નહીંતર જો (buf_size)
  {
    mz_zip_writer_add_state state;

    state.m_pZip = pZip;
    state.m_cur_archive_file_ofs = cur_archive_file_ofs;
    state.m_comp_size = 0;

    જો ((tdefl_init(pComp, mz_zip_writer_add_put_buf_callback, &state, tdefl_create_comp_flags_from_zip_params(level, -15, MZ_DEFAULT_STRATEGY)) != TDEFL_STATUS_OKAY) ||
        (tdefl_compress_buffer(pComp, pBuf, buf_size, TDEFL_FINISH) != TDEFL_STATUS_DONE))
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
      પાછા MZ_FALSE;
    }

    comp_size = state.m_comp_size;
    cur_archive_file_ofs = state.m_cur_archive_file_ofs;

    method = MZ_DEFLATED;
  }

  pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
  pComp = ખાલી;

  // no zip64 support yet
  જો ((comp_size > 0xFFFFFFFF) || (cur_archive_file_ofs > 0xFFFFFFFF))
    પાછા MZ_FALSE;

  જો (!mz_zip_writer_create_local_dir_header(pZip, local_dir_header, (mz_uint16)archive_name_size, 0, uncomp_size, comp_size, uncomp_crc32, method, 0, dos_time, dos_date))
    પાછા MZ_FALSE;

  જો (pZip->m_pWrite(pZip->m_pIO_opaque, local_dir_header_ofs, local_dir_header, કદ(local_dir_header)) != કદ(local_dir_header))
    પાછા MZ_FALSE;

  જો (!mz_zip_writer_add_to_central_dir(pZip, pArchive_name, (mz_uint16)archive_name_size, ખાલી, 0, pComment, comment_size, uncomp_size, comp_size, uncomp_crc32, method, 0, dos_time, dos_date, local_dir_header_ofs, ext_attributes))
    પાછા MZ_FALSE;

  pZip->m_total_files++;
  pZip->m_archive_size = cur_archive_file_ofs;

  પાછા MZ_TRUE;
}

#ifndef MINIZ_NO_STDIO
mz_bool mz_zip_writer_add_file(mz_zip_archive *pZip, અચલ અક્ષર *pArchive_name, અચલ અક્ષર *pSrc_filename, અચલ શૂન્ય *pComment, mz_uint16 comment_size, mz_uint level_and_flags)
{
  mz_uint uncomp_crc32 = MZ_CRC32_INIT, level, અંક_alignment_padding_bytes;
  mz_uint16 method = 0, dos_time = 0, dos_date = 0, ext_attributes = 0;
  mz_uint64 local_dir_header_ofs = pZip->m_archive_size, cur_archive_file_ofs = pZip->m_archive_size, uncomp_size = 0, comp_size = 0;
  size_t archive_name_size;
  mz_uint8 local_dir_header[MZ_ZIP_LOCAL_DIR_HEADER_SIZE];
  MZ_FILE *pSrc_file = ખાલી;

  જો ((પૂર્ણાંક)level_and_flags < 0)
    level_and_flags = MZ_DEFAULT_LEVEL;
  level = level_and_flags & 0xF;

  જો ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_mode != MZ_ZIP_MODE_WRITING) || (!pArchive_name) || ((comment_size) && (!pComment)) || (level > MZ_UBER_COMPRESSION))
    પાછા MZ_FALSE;
  જો (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_DATA)
    પાછા MZ_FALSE;
  જો (!mz_zip_writer_validate_archive_name(pArchive_name))
    પાછા MZ_FALSE;

  archive_name_size = strlen(pArchive_name);
  જો (archive_name_size > 0xFFFF)
    પાછા MZ_FALSE;

  અંક_alignment_padding_bytes = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  જો ((pZip->m_total_files == 0xFFFF) || ((pZip->m_archive_size + અંક_alignment_padding_bytes + MZ_ZIP_LOCAL_DIR_HEADER_SIZE + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE + comment_size + archive_name_size) > 0xFFFFFFFF))
    પાછા MZ_FALSE;

  જો (!mz_zip_get_file_modified_time(pSrc_filename, &dos_time, &dos_date))
    પાછા MZ_FALSE;

  pSrc_file = MZ_FOPEN(pSrc_filename, "rb");
  જો (!pSrc_file)
    પાછા MZ_FALSE;
  MZ_FSEEK64(pSrc_file, 0, SEEK_END);
  uncomp_size = MZ_FTELL64(pSrc_file);
  MZ_FSEEK64(pSrc_file, 0, SEEK_SET);

  જો (uncomp_size > 0xFFFFFFFF)
  {
    // No zip64 support yet
    MZ_FCLOSE(pSrc_file);
    પાછા MZ_FALSE;
  }
  જો (uncomp_size <= 3)
    level = 0;

  જો (!mz_zip_writer_write_zeros(pZip, cur_archive_file_ofs, અંક_alignment_padding_bytes + કદ(local_dir_header)))
  {
    MZ_FCLOSE(pSrc_file);
    પાછા MZ_FALSE;
  }
  local_dir_header_ofs += અંક_alignment_padding_bytes;
  જો (pZip->m_file_offset_alignment) { MZ_ASSERT((local_dir_header_ofs & (pZip->m_file_offset_alignment - 1)) == 0); }
  cur_archive_file_ofs += અંક_alignment_padding_bytes + કદ(local_dir_header);

  MZ_CLEAR_ARR(local_dir_header);
  જો (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pArchive_name, archive_name_size) != archive_name_size)
  {
    MZ_FCLOSE(pSrc_file);
    પાછા MZ_FALSE;
  }
  cur_archive_file_ofs += archive_name_size;

  જો (uncomp_size)
  {
    mz_uint64 uncomp_remaining = uncomp_size;
    શૂન્ય *pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, MZ_ZIP_MAX_IO_BUF_SIZE);
    જો (!pRead_buf)
    {
      MZ_FCLOSE(pSrc_file);
      પાછા MZ_FALSE;
    }

    જો (!level)
    {
      જ્યારે (uncomp_remaining)
      {
        mz_uint n = (mz_uint)MZ_MIN(MZ_ZIP_MAX_IO_BUF_SIZE, uncomp_remaining);
        જો ((MZ_FREAD(pRead_buf, 1, n, pSrc_file) != n) || (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pRead_buf, n) != n))
        {
          pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
          MZ_FCLOSE(pSrc_file);
          પાછા MZ_FALSE;
        }
        uncomp_crc32 = (mz_uint32)mz_crc32(uncomp_crc32, (અચલ mz_uint8 *)pRead_buf, n);
        uncomp_remaining -= n;
        cur_archive_file_ofs += n;
      }
      comp_size = uncomp_size;
    }
    નહીંતર
    {
      mz_bool result = MZ_FALSE;
      mz_zip_writer_add_state state;
      tdefl_compressor *pComp = (tdefl_compressor *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, કદ(tdefl_compressor));
      જો (!pComp)
      {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        પાછા MZ_FALSE;
      }

      state.m_pZip = pZip;
      state.m_cur_archive_file_ofs = cur_archive_file_ofs;
      state.m_comp_size = 0;

      જો (tdefl_init(pComp, mz_zip_writer_add_put_buf_callback, &state, tdefl_create_comp_flags_from_zip_params(level, -15, MZ_DEFAULT_STRATEGY)) != TDEFL_STATUS_OKAY)
      {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        પાછા MZ_FALSE;
      }

      માટે ( ; ; )
      {
        size_t in_buf_size = (mz_uint32)MZ_MIN(uncomp_remaining, MZ_ZIP_MAX_IO_BUF_SIZE);
        tdefl_status status;

        જો (MZ_FREAD(pRead_buf, 1, in_buf_size, pSrc_file) != in_buf_size)
          તોડો;

        uncomp_crc32 = (mz_uint32)mz_crc32(uncomp_crc32, (અચલ mz_uint8 *)pRead_buf, in_buf_size);
        uncomp_remaining -= in_buf_size;

        status = tdefl_compress_buffer(pComp, pRead_buf, in_buf_size, uncomp_remaining ? TDEFL_NO_FLUSH : TDEFL_FINISH);
        જો (status == TDEFL_STATUS_DONE)
        {
          result = MZ_TRUE;
          તોડો;
        }
        નહીંતર જો (status != TDEFL_STATUS_OKAY)
          તોડો;
      }

      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);

      જો (!result)
      {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        પાછા MZ_FALSE;
      }

      comp_size = state.m_comp_size;
      cur_archive_file_ofs = state.m_cur_archive_file_ofs;

      method = MZ_DEFLATED;
    }

    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
  }

  MZ_FCLOSE(pSrc_file); pSrc_file = ખાલી;

  // no zip64 support yet
  જો ((comp_size > 0xFFFFFFFF) || (cur_archive_file_ofs > 0xFFFFFFFF))
    પાછા MZ_FALSE;

  જો (!mz_zip_writer_create_local_dir_header(pZip, local_dir_header, (mz_uint16)archive_name_size, 0, uncomp_size, comp_size, uncomp_crc32, method, 0, dos_time, dos_date))
    પાછા MZ_FALSE;

  જો (pZip->m_pWrite(pZip->m_pIO_opaque, local_dir_header_ofs, local_dir_header, કદ(local_dir_header)) != કદ(local_dir_header))
    પાછા MZ_FALSE;

  જો (!mz_zip_writer_add_to_central_dir(pZip, pArchive_name, (mz_uint16)archive_name_size, ખાલી, 0, pComment, comment_size, uncomp_size, comp_size, uncomp_crc32, method, 0, dos_time, dos_date, local_dir_header_ofs, ext_attributes))
    પાછા MZ_FALSE;

  pZip->m_total_files++;
  pZip->m_archive_size = cur_archive_file_ofs;

  પાછા MZ_TRUE;
}
#endif // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_writer_add_from_zip_reader(mz_zip_archive *pZip, mz_zip_archive *pSource_zip, mz_uint file_index)
{
  mz_uint n, bit_flags, અંક_alignment_padding_bytes;
  mz_uint64 comp_bytes_remaining, local_dir_header_ofs;
  mz_uint64 cur_src_file_ofs, cur_dst_file_ofs;
  mz_uint32 local_header_u32[(MZ_ZIP_LOCAL_DIR_HEADER_SIZE + કદ(mz_uint32) - 1) / કદ(mz_uint32)]; mz_uint8 *pLocal_header = (mz_uint8 *)local_header_u32;
  mz_uint8 central_header[MZ_ZIP_CENTRAL_DIR_HEADER_SIZE];
  size_t orig_central_dir_size;
  mz_zip_internal_state *pState;
  શૂન્ય *pBuf; અચલ mz_uint8 *pSrc_central_header;

  જો ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_mode != MZ_ZIP_MODE_WRITING))
    પાછા MZ_FALSE;
  જો (ખાલી == (pSrc_central_header = mz_zip_reader_get_cdh(pSource_zip, file_index)))
    પાછા MZ_FALSE;
  pState = pZip->m_pState;

  અંક_alignment_padding_bytes = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  જો ((pZip->m_total_files == 0xFFFF) || ((pZip->m_archive_size + અંક_alignment_padding_bytes + MZ_ZIP_LOCAL_DIR_HEADER_SIZE + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE) > 0xFFFFFFFF))
    પાછા MZ_FALSE;

  cur_src_file_ofs = MZ_READ_LE32(pSrc_central_header + MZ_ZIP_CDH_LOCAL_HEADER_OFS);
  cur_dst_file_ofs = pZip->m_archive_size;

  જો (pSource_zip->m_pRead(pSource_zip->m_pIO_opaque, cur_src_file_ofs, pLocal_header, MZ_ZIP_LOCAL_DIR_HEADER_SIZE) != MZ_ZIP_LOCAL_DIR_HEADER_SIZE)
    પાછા MZ_FALSE;
  જો (MZ_READ_LE32(pLocal_header) != MZ_ZIP_LOCAL_DIR_HEADER_SIG)
    પાછા MZ_FALSE;
  cur_src_file_ofs += MZ_ZIP_LOCAL_DIR_HEADER_SIZE;

  જો (!mz_zip_writer_write_zeros(pZip, cur_dst_file_ofs, અંક_alignment_padding_bytes))
    પાછા MZ_FALSE;
  cur_dst_file_ofs += અંક_alignment_padding_bytes;
  local_dir_header_ofs = cur_dst_file_ofs;
  જો (pZip->m_file_offset_alignment) { MZ_ASSERT((local_dir_header_ofs & (pZip->m_file_offset_alignment - 1)) == 0); }

  જો (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, pLocal_header, MZ_ZIP_LOCAL_DIR_HEADER_SIZE) != MZ_ZIP_LOCAL_DIR_HEADER_SIZE)
    પાછા MZ_FALSE;
  cur_dst_file_ofs += MZ_ZIP_LOCAL_DIR_HEADER_SIZE;

  n = MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  comp_bytes_remaining = n + MZ_READ_LE32(pSrc_central_header + MZ_ZIP_CDH_COMPRESSED_SIZE_OFS);

  જો (ખાલી == (pBuf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)MZ_MAX(કદ(mz_uint32) * 4, MZ_MIN(MZ_ZIP_MAX_IO_BUF_SIZE, comp_bytes_remaining)))))
    પાછા MZ_FALSE;

  જ્યારે (comp_bytes_remaining)
  {
    n = (mz_uint)MZ_MIN(MZ_ZIP_MAX_IO_BUF_SIZE, comp_bytes_remaining);
    જો (pSource_zip->m_pRead(pSource_zip->m_pIO_opaque, cur_src_file_ofs, pBuf, n) != n)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      પાછા MZ_FALSE;
    }
    cur_src_file_ofs += n;

    જો (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, pBuf, n) != n)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      પાછા MZ_FALSE;
    }
    cur_dst_file_ofs += n;

    comp_bytes_remaining -= n;
  }

  bit_flags = MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_BIT_FLAG_OFS);
  જો (bit_flags & 8)
  {
    // Copy data descriptor
    જો (pSource_zip->m_pRead(pSource_zip->m_pIO_opaque, cur_src_file_ofs, pBuf, કદ(mz_uint32) * 4) != કદ(mz_uint32) * 4)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      પાછા MZ_FALSE;
    }

    n = કદ(mz_uint32) * ((MZ_READ_LE32(pBuf) == 0x08074b50) ? 4 : 3);
    જો (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, pBuf, n) != n)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      પાછા MZ_FALSE;
    }

    cur_src_file_ofs += n;
    cur_dst_file_ofs += n;
  }
  pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);

  // no zip64 support yet
  જો (cur_dst_file_ofs > 0xFFFFFFFF)
    પાછા MZ_FALSE;

  orig_central_dir_size = pState->m_central_dir.m_size;

  memcpy(central_header, pSrc_central_header, MZ_ZIP_CENTRAL_DIR_HEADER_SIZE);
  MZ_WRITE_LE32(central_header + MZ_ZIP_CDH_LOCAL_HEADER_OFS, local_dir_header_ofs);
  જો (!mz_zip_array_ધકેલો_back(pZip, &pState->m_central_dir, central_header, MZ_ZIP_CENTRAL_DIR_HEADER_SIZE))
    પાછા MZ_FALSE;

  n = MZ_READ_LE16(pSrc_central_header + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(pSrc_central_header + MZ_ZIP_CDH_EXTRA_LEN_OFS) + MZ_READ_LE16(pSrc_central_header + MZ_ZIP_CDH_COMMENT_LEN_OFS);
  જો (!mz_zip_array_ધકેલો_back(pZip, &pState->m_central_dir, pSrc_central_header + MZ_ZIP_CENTRAL_DIR_HEADER_SIZE, n))
  {
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_size, MZ_FALSE);
    પાછા MZ_FALSE;
  }

  જો (pState->m_central_dir.m_size > 0xFFFFFFFF)
    પાછા MZ_FALSE;
  n = (mz_uint32)orig_central_dir_size;
  જો (!mz_zip_array_ધકેલો_back(pZip, &pState->m_central_dir_offsets, &n, 1))
  {
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_size, MZ_FALSE);
    પાછા MZ_FALSE;
  }

  pZip->m_total_files++;
  pZip->m_archive_size = cur_dst_file_ofs;

  પાછા MZ_TRUE;
}

mz_bool mz_zip_writer_finalize_archive(mz_zip_archive *pZip)
{
  mz_zip_internal_state *pState;
  mz_uint64 central_dir_ofs, central_dir_size;
  mz_uint8 hdr[MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE];

  જો ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_mode != MZ_ZIP_MODE_WRITING))
    પાછા MZ_FALSE;

  pState = pZip->m_pState;

  // no zip64 support yet
  જો ((pZip->m_total_files > 0xFFFF) || ((pZip->m_archive_size + pState->m_central_dir.m_size + MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIZE) > 0xFFFFFFFF))
    પાછા MZ_FALSE;

  central_dir_ofs = 0;
  central_dir_size = 0;
  જો (pZip->m_total_files)
  {
    // Write central directory
    central_dir_ofs = pZip->m_archive_size;
    central_dir_size = pState->m_central_dir.m_size;
    pZip->m_central_directory_file_ofs = central_dir_ofs;
    જો (pZip->m_pWrite(pZip->m_pIO_opaque, central_dir_ofs, pState->m_central_dir.m_p, (size_t)central_dir_size) != central_dir_size)
      પાછા MZ_FALSE;
    pZip->m_archive_size += central_dir_size;
  }

  // Write end of central directory record
  MZ_CLEAR_ARR(hdr);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_SIG_OFS, MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIG);
  MZ_WRITE_LE16(hdr + MZ_ZIP_ECDH_CDIR_અંક_ENTRIES_ON_DISK_OFS, pZip->m_total_files);
  MZ_WRITE_LE16(hdr + MZ_ZIP_ECDH_CDIR_TOTAL_ENTRIES_OFS, pZip->m_total_files);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_CDIR_SIZE_OFS, central_dir_size);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_CDIR_OFS_OFS, central_dir_ofs);

  જો (pZip->m_pWrite(pZip->m_pIO_opaque, pZip->m_archive_size, hdr, કદ(hdr)) != કદ(hdr))
    પાછા MZ_FALSE;
#ifndef MINIZ_NO_STDIO
  જો ((pState->m_pFile) && (MZ_FFLUSH(pState->m_pFile) == EOF))
    પાછા MZ_FALSE;
#endif // #ifndef MINIZ_NO_STDIO

  pZip->m_archive_size += કદ(hdr);

  pZip->m_zip_mode = MZ_ZIP_MODE_WRITING_HAS_BEEN_FINALIZED;
  પાછા MZ_TRUE;
}

mz_bool mz_zip_writer_finalize_heap_archive(mz_zip_archive *pZip, શૂન્ય **pBuf, size_t *pSize)
{
  જો ((!pZip) || (!pZip->m_pState) || (!pBuf) || (!pSize))
    પાછા MZ_FALSE;
  જો (pZip->m_pWrite != mz_zip_heap_write_func)
    પાછા MZ_FALSE;
  જો (!mz_zip_writer_finalize_archive(pZip))
    પાછા MZ_FALSE;

  *pBuf = pZip->m_pState->m_pMem;
  *pSize = pZip->m_pState->m_mem_size;
  pZip->m_pState->m_pMem = ખાલી;
  pZip->m_pState->m_mem_size = pZip->m_pState->m_mem_capacity = 0;
  પાછા MZ_TRUE;
}

mz_bool mz_zip_writer_end(mz_zip_archive *pZip)
{
  mz_zip_internal_state *pState;
  mz_bool status = MZ_TRUE;
  જો ((!pZip) || (!pZip->m_pState) || (!pZip->m_pAlloc) || (!pZip->m_pFree) || ((pZip->m_zip_mode != MZ_ZIP_MODE_WRITING) && (pZip->m_zip_mode != MZ_ZIP_MODE_WRITING_HAS_BEEN_FINALIZED)))
    પાછા MZ_FALSE;

  pState = pZip->m_pState;
  pZip->m_pState = ખાલી;
  mz_zip_array_clear(pZip, &pState->m_central_dir);
  mz_zip_array_clear(pZip, &pState->m_central_dir_offsets);
  mz_zip_array_clear(pZip, &pState->m_sorted_central_dir_offsets);

#ifndef MINIZ_NO_STDIO
  જો (pState->m_pFile)
  {
    MZ_FCLOSE(pState->m_pFile);
    pState->m_pFile = ખાલી;
  }
#endif // #ifndef MINIZ_NO_STDIO

  જો ((pZip->m_pWrite == mz_zip_heap_write_func) && (pState->m_pMem))
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pState->m_pMem);
    pState->m_pMem = ખાલી;
  }

  pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
  pZip->m_zip_mode = MZ_ZIP_MODE_INVALID;
  પાછા status;
}

#ifndef MINIZ_NO_STDIO
mz_bool mz_zip_add_mem_to_archive_file_in_place(અચલ અક્ષર *pZip_filename, અચલ અક્ષર *pArchive_name, અચલ શૂન્ય *pBuf, size_t buf_size, અચલ શૂન્ય *pComment, mz_uint16 comment_size, mz_uint level_and_flags)
{
  mz_bool status, created_new_archive = MZ_FALSE;
  mz_zip_archive zip_archive;
  સંરચના MZ_FILE_STAT_STRUCT file_stat;
  MZ_CLEAR_OBJ(zip_archive);
  જો ((પૂર્ણાંક)level_and_flags < 0)
     level_and_flags = MZ_DEFAULT_LEVEL;
  જો ((!pZip_filename) || (!pArchive_name) || ((buf_size) && (!pBuf)) || ((comment_size) && (!pComment)) || ((level_and_flags & 0xF) > MZ_UBER_COMPRESSION))
    પાછા MZ_FALSE;
  જો (!mz_zip_writer_validate_archive_name(pArchive_name))
    પાછા MZ_FALSE;
  જો (MZ_FILE_STAT(pZip_filename, &file_stat) != 0)
  {
    // Create a new archive.
    જો (!mz_zip_writer_init_file(&zip_archive, pZip_filename, 0))
      પાછા MZ_FALSE;
    created_new_archive = MZ_TRUE;
  }
  નહીંતર
  {
    // Append to an existing archive.
    જો (!mz_zip_reader_init_file(&zip_archive, pZip_filename, level_and_flags | MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY))
      પાછા MZ_FALSE;
    જો (!mz_zip_writer_init_from_reader(&zip_archive, pZip_filename))
    {
      mz_zip_reader_end(&zip_archive);
      પાછા MZ_FALSE;
    }
  }
  status = mz_zip_writer_add_mem_ex(&zip_archive, pArchive_name, pBuf, buf_size, pComment, comment_size, level_and_flags, 0, 0);
  // Always finalize, even if adding failed for some reason, so we have a valid central directory. (This may not always succeed, but we can try.)
  જો (!mz_zip_writer_finalize_archive(&zip_archive))
    status = MZ_FALSE;
  જો (!mz_zip_writer_end(&zip_archive))
    status = MZ_FALSE;
  જો ((!status) && (created_new_archive))
  {
    // It's a new archive and something went wrong, so just delete it.
    પૂર્ણાંક ignoredStatus = MZ_DELETE_FILE(pZip_filename);
    (શૂન્ય)ignoredStatus;
  }
  પાછા status;
}

શૂન્ય *mz_zip_extract_archive_file_to_heap(અચલ અક્ષર *pZip_filename, અચલ અક્ષર *pArchive_name, size_t *pSize, mz_uint flags)
{
  પૂર્ણાંક file_index;
  mz_zip_archive zip_archive;
  શૂન્ય *p = ખાલી;

  જો (pSize)
    *pSize = 0;

  જો ((!pZip_filename) || (!pArchive_name))
    પાછા ખાલી;

  MZ_CLEAR_OBJ(zip_archive);
  જો (!mz_zip_reader_init_file(&zip_archive, pZip_filename, flags | MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY))
    પાછા ખાલી;

  જો ((file_index = mz_zip_reader_locate_file(&zip_archive, pArchive_name, ખાલી, flags)) >= 0)
    p = mz_zip_reader_extract_to_heap(&zip_archive, file_index, pSize, flags);

  mz_zip_reader_end(&zip_archive);
  પાછા p;
}

#endif // #ifndef MINIZ_NO_STDIO

#endif // #ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

#endif // #ifndef MINIZ_NO_ARCHIVE_APIS

#ifdef __cplusplus
}
#endif

#ifdef _MSC_VER
#pragma warning (કાઢો)
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

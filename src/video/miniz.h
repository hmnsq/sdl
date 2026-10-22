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

#अगर_अघोषित MINIZ_HEADER_INCLUDED
#घोषणा MINIZ_HEADER_INCLUDED

/*#include <stdlib.h>*/

// Defines to completely disable specific portions of miniz.c:
// If all macros here are defined the only functionality remaining will be CRC-32, adler-32, tinfl, and tdefl.

// Define MINIZ_NO_STDIO to disable all usage and any functions which rely on stdio for file I/O.
#घोषणा MINIZ_NO_STDIO

// If MINIZ_NO_TIME is specified then the ZIP archive functions will not be able to get the current time, or
// get/set file times, and the C run-time funcs that get/set times won't be called.
// The current downside is the times written to your archives will be from 1979.
#घोषणा MINIZ_NO_TIME

// Define MINIZ_NO_DEFLATE_APIS to disable all compression API's.
//#define MINIZ_NO_DEFLATE_APIS

// Define MINIZ_NO_INFLATE_APIS to disable all decompression API's.
#घोषणा MINIZ_NO_INFLATE_APIS

// Define MINIZ_NO_ARCHIVE_APIS to disable all ZIP archive API's.
#घोषणा MINIZ_NO_ARCHIVE_APIS

// Define MINIZ_NO_ARCHIVE_APIS to disable all writing related ZIP archive API's.
#घोषणा MINIZ_NO_ARCHIVE_WRITING_APIS

// Define MINIZ_NO_ZLIB_APIS to remove all ZLIB-style compression/decompression API's.
#घोषणा MINIZ_NO_ZLIB_APIS

// Define MINIZ_NO_ZLIB_COMPATIBLE_NAME to disable zlib names, to prevent conflicts against stock zlib.
#घोषणा MINIZ_NO_ZLIB_COMPATIBLE_NAMES

// Define MINIZ_NO_MALLOC to disable all calls to malloc, free, and realloc.
// Note if MINIZ_NO_MALLOC is defined then the user must always provide custom user alloc/free/realloc
// callbacks to the zlib and archive API's, and a few stand-alone helper API's which don't provide custom user
// functions (such as tdefl_compress_mem_to_heap() and tinfl_decompress_mem_to_heap()) won't work.
//#define MINIZ_NO_MALLOC
#घोषणा MINIZ_SDL_MALLOC

#अगर_घोषित MINIZ_NO_INFLATE_APIS
#घोषणा MINIZ_NO_ARCHIVE_APIS
#पूर्ण_अगर

#अगर_घोषित MINIZ_NO_DEFLATE_APIS
#घोषणा MINIZ_NO_ARCHIVE_WRITING_APIS
#पूर्ण_अगर

// Define MINIZ_STATIC_FUNCTIONS to make all functions static. You probably
// want this if you're using miniz in a library
#घोषणा MINIZ_STATIC_FUNCTIONS

#अगर defined(__TINYC__) && (defined(__linux) || defined(__linux__))
  // TODO: Work around "error: include file 'sys\utime.h' when compiling with tcc on Linux
  #घोषणा MINIZ_NO_TIME
#पूर्ण_अगर

#अगर !defined(MINIZ_NO_TIME) && !defined(MINIZ_NO_ARCHIVE_APIS)
  #समावेश <time.h>
#पूर्ण_अगर

#अगर defined(_M_IX86) || defined(_M_X64) || defined(__i386__) || defined(__i386) || defined(__i486__) || defined(__i486) || defined(i386) || defined(__ia64__) || defined(__x86_64__)
// MINIZ_X86_OR_X64_CPU is only used to help set the below macros.
#घोषणा MINIZ_X86_OR_X64_CPU 1
#पूर्ण_अगर

#अगर_अघोषित MINIZ_LITTLE_ENDIAN /* if not defined by SDL */
#अगर (__BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__) || MINIZ_X86_OR_X64_CPU
// Set MINIZ_LITTLE_ENDIAN to 1 if the processor is little endian.
#घोषणा MINIZ_LITTLE_ENDIAN 1
#पूर्ण_अगर
#पूर्ण_अगर // MINIZ_LITTLE_ENDIAN /* if not defined by SDL */

#अगर_अघोषित MINIZ_USE_UNALIGNED_LOADS_AND_STORES
#अगर MINIZ_X86_OR_X64_CPU
// Set MINIZ_USE_UNALIGNED_LOADS_AND_STORES to 1 on CPU's that permit efficient integer loads and stores from unaligned addresses.
#घोषणा MINIZ_USE_UNALIGNED_LOADS_AND_STORES 1
#पूर्ण_अगर
#पूर्ण_अगर // MINIZ_USE_UNALIGNED_LOADS_AND_STORES

#अगर defined(_M_X64) || defined(_WIN64) || defined(__MINGW64__) || defined(_LP64) || defined(__LP64__) || defined(__ia64__) || defined(__x86_64__)
// Set MINIZ_HAS_64BIT_REGISTERS to 1 if operations on 64-bit integers are reasonably fast (and don't involve compiler generated calls to helper functions).
#घोषणा MINIZ_HAS_64BIT_REGISTERS 1
#पूर्ण_अगर

#अगर_घोषित MINIZ_STATIC_FUNCTIONS
#घोषणा MINIZ_STATIC अटल
#अन्यथा
#घोषणा MINIZ_STATIC
#पूर्ण_अगर

#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर

// ------------------- zlib-style API Definitions.

// For more compatibility with zlib, miniz.c uses unsigned long for some parameters/struct members. Beware: mz_ulong can be either 32 or 64-bits!
प्रकार अचिन्हित दीर्घ mz_ulong;

// mz_free() internally uses the MZ_FREE() macro (which by default calls free() unless you've modified the MZ_MALLOC macro) to release a block allocated from the heap.
MINIZ_STATIC व्योम mz_free(व्योम *p);

#घोषणा MZ_ADLER32_INIT (1)
// mz_adler32() returns the initial adler-32 value to use when called with ptr==NULL.
MINIZ_STATIC mz_ulong mz_adler32(mz_ulong adler, स्थिर अचिन्हित अक्षर *ptr, माप_प्रकार buf_len);

#घोषणा MZ_CRC32_INIT (0)
// mz_crc32() returns the initial CRC-32 value to use when called with ptr==NULL.
MINIZ_STATIC mz_ulong mz_crc32(mz_ulong crc, स्थिर अचिन्हित अक्षर *ptr, माप_प्रकार buf_len);

// Compression strategies.
क्रमागत { MZ_DEFAULT_STRATEGY = 0, MZ_FILTERED = 1, MZ_HUFFMAN_ONLY = 2, MZ_RLE = 3, MZ_FIXED = 4 };

// Method
#घोषणा MZ_DEFLATED 8

#अगर_अघोषित MINIZ_NO_ZLIB_APIS

// Heap allocation callbacks.
// Note that mz_alloc_func parameter types purpsosely differ from zlib's: items/size is size_t, not unsigned long.
प्रकार व्योम *(*mz_alloc_func)(व्योम *opaque, माप_प्रकार वस्तुएँ, माप_प्रकार आकार);
प्रकार व्योम (*mz_free_func)(व्योम *opaque, व्योम *address);
प्रकार व्योम *(*mz_realloc_func)(व्योम *opaque, व्योम *address, माप_प्रकार वस्तुएँ, माप_प्रकार आकार);

#घोषणा MZ_VERSION          "9.1.15"
#घोषणा MZ_VERNUM           0x91F0
#घोषणा MZ_VER_MAJOR        9
#घोषणा MZ_VER_MINOR        1
#घोषणा MZ_VER_REVISION     15
#घोषणा MZ_VER_SUBREVISION  0

// Flush values. For typical usage you only need MZ_NO_FLUSH and MZ_FINISH. The other values are for advanced use (refer to the zlib docs).
क्रमागत { MZ_NO_FLUSH = 0, MZ_PARTIAL_FLUSH = 1, MZ_SYNC_FLUSH = 2, MZ_FULL_FLUSH = 3, MZ_FINISH = 4, MZ_BLOCK = 5 };

// Return status codes. MZ_PARAM_ERROR is non-standard.
क्रमागत { MZ_OK = 0, MZ_STREAM_END = 1, MZ_NEED_DICT = 2, MZ_ERRNO = -1, MZ_STREAM_ERROR = -2, MZ_तथ्य_ERROR = -3, MZ_MEM_ERROR = -4, MZ_BUF_ERROR = -5, MZ_VERSION_ERROR = -6, MZ_PARAM_ERROR = -10000 };

// Compression levels: 0-9 are the standard zlib-style levels, 10 is best possible compression (not zlib compatible, and may be very slow), MZ_DEFAULT_COMPRESSION=MZ_DEFAULT_LEVEL.
क्रमागत { MZ_NO_COMPRESSION = 0, MZ_BEST_SPEED = 1, MZ_BEST_COMPRESSION = 9, MZ_UBER_COMPRESSION = 10, MZ_DEFAULT_LEVEL = 6, MZ_DEFAULT_COMPRESSION = -1 };

// Window bits
#घोषणा MZ_DEFAULT_WINDOW_BITS 15

काष्ठा mz_internal_state;

// Compression/decompression stream struct.
प्रकार काष्ठा mz_stream_s
{
  स्थिर अचिन्हित अक्षर *अग्र_in;     // pointer to next byte to read
  अचिन्हित पूर्णांक avail_in;            // number of bytes available at next_in
  mz_ulong योग_in;                // total number of bytes consumed so far

  अचिन्हित अक्षर *अग्र_out;          // pointer to next byte to write
  अचिन्हित पूर्णांक avail_out;           // number of bytes that can be written to next_out
  mz_ulong योग_out;               // total number of bytes produced so far

  अक्षर *संदेश;                        // error msg (unused)
  काष्ठा mz_internal_state *state;  // internal state, allocated by zalloc/zfree

  mz_alloc_func zalloc;             // optional heap allocation function (defaults to malloc)
  mz_free_func zfree;               // optional heap free function (defaults to free)
  व्योम *opaque;                     // heap alloc function user pointer

  पूर्णांक तथ्य_type;                    // data_type (unused)
  mz_ulong adler;                   // adler32 of the source or uncompressed data
  mz_ulong reserved;                // not used
} mz_stream;

प्रकार mz_stream *mz_streamp;

// Returns the version string of miniz.c.
MINIZ_STATIC स्थिर अक्षर *mz_version(व्योम);

#अगर_अघोषित MINIZ_NO_DEFLATE_APIS

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
MINIZ_STATIC पूर्णांक mz_deflateInit(mz_streamp pStream, पूर्णांक level);

// mz_deflateInit2() is like mz_deflate(), except with more control:
// Additional parameters:
//   method must be MZ_DEFLATED
//   window_bits must be MZ_DEFAULT_WINDOW_BITS (to wrap the deflate stream with zlib header/adler-32 footer) or -MZ_DEFAULT_WINDOW_BITS (raw deflate/no header or footer)
//   mem_level must be between [1, 9] (it's checked but ignored by miniz.c)
MINIZ_STATIC पूर्णांक mz_deflateInit2(mz_streamp pStream, पूर्णांक level, पूर्णांक method, पूर्णांक window_bits, पूर्णांक mem_level, पूर्णांक strategy);

// Quickly resets a compressor without having to reallocate anything. Same as calling mz_deflateEnd() followed by mz_deflateInit()/mz_deflateInit2().
MINIZ_STATIC पूर्णांक mz_deflateReset(mz_streamp pStream);

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
MINIZ_STATIC पूर्णांक mz_deflate(mz_streamp pStream, पूर्णांक flush);

// mz_deflateEnd() deinitializes a compressor:
// Return values:
//  MZ_OK on success.
//  MZ_STREAM_ERROR if the stream is bogus.
MINIZ_STATIC पूर्णांक mz_deflateEnd(mz_streamp pStream);

// mz_deflateBound() returns a (very) conservative upper bound on the amount of data that could be generated by deflate(), assuming flush is set to only MZ_NO_FLUSH or MZ_FINISH.
MINIZ_STATIC mz_ulong mz_deflateBound(mz_streamp pStream, mz_ulong source_len);

// Single-call compression functions mz_compress() and mz_compress2():
// Returns MZ_OK on success, or one of the error codes from mz_deflate() on failure.
MINIZ_STATIC पूर्णांक mz_compress(अचिन्हित अक्षर *pDest, mz_ulong *pDest_len, स्थिर अचिन्हित अक्षर *pSource, mz_ulong source_len);
MINIZ_STATIC पूर्णांक mz_compress2(अचिन्हित अक्षर *pDest, mz_ulong *pDest_len, स्थिर अचिन्हित अक्षर *pSource, mz_ulong source_len, पूर्णांक level);

// mz_compressBound() returns a (very) conservative upper bound on the amount of data that could be generated by calling mz_compress().
MINIZ_STATIC mz_ulong mz_compressBound(mz_ulong source_len);

#पूर्ण_अगर /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#अगर_अघोषित MINIZ_NO_INFLATE_APIS

// Initializes a decompressor.
MINIZ_STATIC पूर्णांक mz_inflateInit(mz_streamp pStream);

// mz_inflateInit2() is like mz_inflateInit() with an additional option that controls the window size and whether or not the stream has been wrapped with a zlib header/footer:
// window_bits must be MZ_DEFAULT_WINDOW_BITS (to parse zlib header/footer) or -MZ_DEFAULT_WINDOW_BITS (raw deflate).
MINIZ_STATIC पूर्णांक mz_inflateInit2(mz_streamp pStream, पूर्णांक window_bits);

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
MINIZ_STATIC पूर्णांक mz_inflate(mz_streamp pStream, पूर्णांक flush);

// Deinitializes a decompressor.
MINIZ_STATIC पूर्णांक mz_inflateEnd(mz_streamp pStream);

// Single-call decompression.
// Returns MZ_OK on success, or one of the error codes from mz_inflate() on failure.
MINIZ_STATIC पूर्णांक mz_uncompress(अचिन्हित अक्षर *pDest, mz_ulong *pDest_len, स्थिर अचिन्हित अक्षर *pSource, mz_ulong source_len);
#पूर्ण_अगर /*#ifndef MINIZ_NO_INFLATE_APIS*/

// Returns a string description of the specified error code, or NULL if the error code is invalid.
MINIZ_STATIC स्थिर अक्षर *mz_error(पूर्णांक err);

// Redefine zlib-compatible names to miniz equivalents, so miniz.c can be used as a drop-in replacement for the subset of zlib that miniz.c supports.
// Define MINIZ_NO_ZLIB_COMPATIBLE_NAMES to disable zlib-compatibility if you use zlib in the same project.
#अगर_अघोषित MINIZ_NO_ZLIB_COMPATIBLE_NAMES
  प्रकार अचिन्हित अक्षर Byte;
  प्रकार अचिन्हित पूर्णांक uInt;
  प्रकार mz_ulong uLong;
  प्रकार Byte Bytef;
  प्रकार uInt uIntf;
  प्रकार अक्षर charf;
  प्रकार पूर्णांक intf;
  प्रकार व्योम *voidpf;
  प्रकार uLong uLongf;
  प्रकार व्योम *voidp;
  प्रकार व्योम *स्थिर voidpc;
  #घोषणा Z_NULL                0
  #घोषणा Z_NO_FLUSH            MZ_NO_FLUSH
  #घोषणा Z_PARTIAL_FLUSH       MZ_PARTIAL_FLUSH
  #घोषणा Z_SYNC_FLUSH          MZ_SYNC_FLUSH
  #घोषणा Z_FULL_FLUSH          MZ_FULL_FLUSH
  #घोषणा Z_FINISH              MZ_FINISH
  #घोषणा Z_BLOCK               MZ_BLOCK
  #घोषणा Z_OK                  MZ_OK
  #घोषणा Z_STREAM_END          MZ_STREAM_END
  #घोषणा Z_NEED_DICT           MZ_NEED_DICT
  #घोषणा Z_ERRNO               MZ_ERRNO
  #घोषणा Z_STREAM_ERROR        MZ_STREAM_ERROR
  #घोषणा Z_तथ्य_ERROR          MZ_तथ्य_ERROR
  #घोषणा Z_MEM_ERROR           MZ_MEM_ERROR
  #घोषणा Z_BUF_ERROR           MZ_BUF_ERROR
  #घोषणा Z_VERSION_ERROR       MZ_VERSION_ERROR
  #घोषणा Z_PARAM_ERROR         MZ_PARAM_ERROR
  #घोषणा Z_NO_COMPRESSION      MZ_NO_COMPRESSION
  #घोषणा Z_BEST_SPEED          MZ_BEST_SPEED
  #घोषणा Z_BEST_COMPRESSION    MZ_BEST_COMPRESSION
  #घोषणा Z_DEFAULT_COMPRESSION MZ_DEFAULT_COMPRESSION
  #घोषणा Z_DEFAULT_STRATEGY    MZ_DEFAULT_STRATEGY
  #घोषणा Z_FILTERED            MZ_FILTERED
  #घोषणा Z_HUFFMAN_ONLY        MZ_HUFFMAN_ONLY
  #घोषणा Z_RLE                 MZ_RLE
  #घोषणा Z_FIXED               MZ_FIXED
  #घोषणा Z_DEFLATED            MZ_DEFLATED
  #घोषणा Z_DEFAULT_WINDOW_BITS MZ_DEFAULT_WINDOW_BITS
  #घोषणा alloc_func            mz_alloc_func
  #घोषणा free_func             mz_free_func
  #घोषणा internal_state        mz_internal_state
  #घोषणा z_stream              mz_stream
#अगर_अघोषित MINIZ_NO_DEFLATE_APIS
  #घोषणा deflateInit           mz_deflateInit
  #घोषणा deflateInit2          mz_deflateInit2
  #घोषणा deflateReset          mz_deflateReset
  #घोषणा deflate               mz_deflate
  #घोषणा deflateEnd            mz_deflateEnd
  #घोषणा deflateBound          mz_deflateBound
  #घोषणा compress              mz_compress
  #घोषणा compress2             mz_compress2
  #घोषणा compressBound         mz_compressBound
#पूर्ण_अगर /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#अगर_अघोषित MINIZ_NO_INFLATE_APIS
  #घोषणा inflateInit           mz_inflateInit
  #घोषणा inflateInit2          mz_inflateInit2
  #घोषणा inflate               mz_inflate
  #घोषणा inflateEnd            mz_inflateEnd
  #घोषणा uncompress            mz_uncompress
#पूर्ण_अगर /*#ifndef MINIZ_NO_INFLATE_APIS*/
  #घोषणा crc32                 mz_crc32
  #घोषणा adler32               mz_adler32
  #घोषणा MAX_WBITS             15
  #घोषणा MAX_MEM_LEVEL         9
  #घोषणा zError                mz_error
  #घोषणा ZLIB_VERSION          MZ_VERSION
  #घोषणा ZLIB_VERNUM           MZ_VERNUM
  #घोषणा ZLIB_VER_MAJOR        MZ_VER_MAJOR
  #घोषणा ZLIB_VER_MINOR        MZ_VER_MINOR
  #घोषणा ZLIB_VER_REVISION     MZ_VER_REVISION
  #घोषणा ZLIB_VER_SUBREVISION  MZ_VER_SUBREVISION
  #घोषणा zlibVersion           mz_version
  #घोषणा zlib_version          mz_version()
#पूर्ण_अगर // #ifndef MINIZ_NO_ZLIB_COMPATIBLE_NAMES

#पूर्ण_अगर // MINIZ_NO_ZLIB_APIS

// ------------------- Types and macros

प्रकार अचिन्हित अक्षर mz_uint8;
प्रकार चिन्हित लघु mz_int16;
प्रकार अचिन्हित लघु mz_uint16;
प्रकार अचिन्हित पूर्णांक mz_uint32;
प्रकार अचिन्हित पूर्णांक mz_uint;
प्रकार दीर्घ दीर्घ mz_int64;
प्रकार अचिन्हित दीर्घ दीर्घ mz_uint64;
प्रकार पूर्णांक mz_bool;

#घोषणा MZ_FALSE (0)
#घोषणा MZ_TRUE (1)

// An attempt to work around MSVC's spammy "warning C4127: conditional expression is constant" message.
#अगर_घोषित _MSC_VER
   #घोषणा MZ_MACRO_END जबतक (0, 0)
#अन्यथा
   #घोषणा MZ_MACRO_END जबतक (0)
#पूर्ण_अगर

// ------------------- ZIP archive reading/writing

#अगर_अघोषित MINIZ_NO_ARCHIVE_APIS

क्रमागत
{
  MZ_ZIP_MAX_IO_BUF_आकार = 64*1024,
  MZ_ZIP_MAX_ARCHIVE_FILENAME_आकार = 260,
  MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_आकार = 256
};

प्रकार काष्ठा
{
  mz_uint32 m_file_सूचकांक;
  mz_uint32 m_central_dir_ofs;
  mz_uint16 m_version_made_by;
  mz_uint16 m_version_needed;
  mz_uint16 m_bit_flag;
  mz_uint16 m_method;
#अगर_अघोषित MINIZ_NO_TIME
  समय_प्रकार m_time;
#पूर्ण_अगर
  mz_uint32 m_crc32;
  mz_uint64 m_comp_आकार;
  mz_uint64 m_uncomp_आकार;
  mz_uint16 m_internal_attr;
  mz_uint32 m_external_attr;
  mz_uint64 m_local_header_ofs;
  mz_uint32 m_comment_आकार;
  अक्षर m_filename[MZ_ZIP_MAX_ARCHIVE_FILENAME_आकार];
  अक्षर m_comment[MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_आकार];
} mz_zip_archive_file_stat;

प्रकार माप_प्रकार (*mz_file_read_func)(व्योम *pOpaque, mz_uint64 file_ofs, व्योम *pBuf, माप_प्रकार n);
प्रकार माप_प्रकार (*mz_file_write_func)(व्योम *pOpaque, mz_uint64 file_ofs, स्थिर व्योम *pBuf, माप_प्रकार n);

काष्ठा mz_zip_internal_state_tag;
प्रकार काष्ठा mz_zip_internal_state_tag mz_zip_internal_state;

प्रकार क्रमागत
{
  MZ_ZIP_MODE_INVALID = 0,
  MZ_ZIP_MODE_READING = 1,
  MZ_ZIP_MODE_WRITING = 2,
  MZ_ZIP_MODE_WRITING_HAS_BEEN_FINALIZED = 3
} mz_zip_mode;

प्रकार काष्ठा mz_zip_archive_tag
{
  mz_uint64 m_archive_आकार;
  mz_uint64 m_central_directory_file_ofs;
  mz_uint m_योग_files;
  mz_zip_mode m_zip_mode;

  mz_uint m_file_offset_alignment;

  mz_alloc_func m_pAlloc;
  mz_free_func m_pFree;
  mz_realloc_func m_pRealloc;
  व्योम *m_pAlloc_opaque;

  mz_file_read_func m_pRead;
  mz_file_write_func m_pWrite;
  व्योम *m_pIO_opaque;

  mz_zip_internal_state *m_pState;

} mz_zip_archive;

प्रकार क्रमागत
{
  MZ_ZIP_FLAG_CASE_SENSITIVE                = 0x0100,
  MZ_ZIP_FLAG_IGNORE_PATH                   = 0x0200,
  MZ_ZIP_FLAG_COMPRESSED_तथ्य               = 0x0400,
  MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY = 0x0800
} mz_zip_flags;

// ZIP archive reading

// Inits a ZIP archive reader.
// These functions read and validate the archive's central directory.
MINIZ_STATIC mz_bool mz_zip_reader_init(mz_zip_archive *pZip, mz_uint64 आकार, mz_uint32 flags);
MINIZ_STATIC mz_bool mz_zip_reader_init_mem(mz_zip_archive *pZip, स्थिर व्योम *pMem, माप_प्रकार आकार, mz_uint32 flags);

#अगर_अघोषित MINIZ_NO_STDIO
MINIZ_STATIC mz_bool mz_zip_reader_init_file(mz_zip_archive *pZip, स्थिर अक्षर *pFilename, mz_uint32 flags);
#पूर्ण_अगर

// Returns the total number of files in the archive.
MINIZ_STATIC mz_uint mz_zip_reader_get_अंक_files(mz_zip_archive *pZip);

// Returns detailed information about an archive file entry.
MINIZ_STATIC mz_bool mz_zip_reader_file_stat(mz_zip_archive *pZip, mz_uint file_सूचकांक, mz_zip_archive_file_stat *pStat);

// Determines if an archive file entry is a directory entry.
MINIZ_STATIC mz_bool mz_zip_reader_is_file_a_directory(mz_zip_archive *pZip, mz_uint file_सूचकांक);
MINIZ_STATIC mz_bool mz_zip_reader_is_file_encrypted(mz_zip_archive *pZip, mz_uint file_सूचकांक);

// Retrieves the filename of an archive file entry.
// Returns the number of bytes written to pFilename, or if filename_buf_size is 0 this function returns the number of bytes needed to fully store the filename.
MINIZ_STATIC mz_uint mz_zip_reader_get_filename(mz_zip_archive *pZip, mz_uint file_सूचकांक, अक्षर *pFilename, mz_uint filename_buf_आकार);

// Attempts to locates a file in the archive's central directory.
// Valid flags: MZ_ZIP_FLAG_CASE_SENSITIVE, MZ_ZIP_FLAG_IGNORE_PATH
// Returns -1 if the file cannot be found.
MINIZ_STATIC पूर्णांक mz_zip_reader_locate_file(mz_zip_archive *pZip, स्थिर अक्षर *pName, स्थिर अक्षर *pComment, mz_uint flags);

// Extracts a archive file to a memory buffer using no memory allocation.
MINIZ_STATIC mz_bool mz_zip_reader_extract_to_mem_no_alloc(mz_zip_archive *pZip, mz_uint file_सूचकांक, व्योम *pBuf, माप_प्रकार buf_आकार_2, mz_uint flags, व्योम *pUser_read_buf, माप_प्रकार user_read_buf_आकार);
MINIZ_STATIC mz_bool mz_zip_reader_extract_file_to_mem_no_alloc(mz_zip_archive *pZip, स्थिर अक्षर *pFilename, व्योम *pBuf, माप_प्रकार buf_आकार_2, mz_uint flags, व्योम *pUser_read_buf, माप_प्रकार user_read_buf_आकार);

// Extracts a archive file to a memory buffer.
MINIZ_STATIC mz_bool mz_zip_reader_extract_to_mem(mz_zip_archive *pZip, mz_uint file_सूचकांक, व्योम *pBuf, माप_प्रकार buf_आकार_2, mz_uint flags);
MINIZ_STATIC mz_bool mz_zip_reader_extract_file_to_mem(mz_zip_archive *pZip, स्थिर अक्षर *pFilename, व्योम *pBuf, माप_प्रकार buf_आकार_2, mz_uint flags);

// Extracts a archive file to a dynamically allocated heap buffer.
MINIZ_STATIC व्योम *mz_zip_reader_extract_to_heap(mz_zip_archive *pZip, mz_uint file_सूचकांक, माप_प्रकार *p_आकार, mz_uint flags);
MINIZ_STATIC व्योम *mz_zip_reader_extract_file_to_heap(mz_zip_archive *pZip, स्थिर अक्षर *pFilename, माप_प्रकार *p_आकार, mz_uint flags);

// Extracts a archive file using a callback function to output the file's data.
MINIZ_STATIC mz_bool mz_zip_reader_extract_to_callback(mz_zip_archive *pZip, mz_uint file_सूचकांक, mz_file_write_func pCallback, व्योम *pOpaque, mz_uint flags);
MINIZ_STATIC mz_bool mz_zip_reader_extract_file_to_callback(mz_zip_archive *pZip, स्थिर अक्षर *pFilename, mz_file_write_func pCallback, व्योम *pOpaque, mz_uint flags);

#अगर_अघोषित MINIZ_NO_STDIO
// Extracts a archive file to a disk file and sets its last accessed and modified times.
// This function only extracts files, not archive directory records.
MINIZ_STATIC mz_bool mz_zip_reader_extract_to_file(mz_zip_archive *pZip, mz_uint file_सूचकांक, स्थिर अक्षर *pDst_filename, mz_uint flags);
MINIZ_STATIC mz_bool mz_zip_reader_extract_file_to_file(mz_zip_archive *pZip, स्थिर अक्षर *pArchive_filename, स्थिर अक्षर *pDst_filename, mz_uint flags);
#पूर्ण_अगर

// Ends archive reading, freeing all allocations, and closing the input archive file if mz_zip_reader_init_file() was used.
MINIZ_STATIC mz_bool mz_zip_reader_end(mz_zip_archive *pZip);

// ZIP archive writing

#अगर_अघोषित MINIZ_NO_ARCHIVE_WRITING_APIS

// Inits a ZIP archive writer.
MINIZ_STATIC mz_bool mz_zip_writer_init(mz_zip_archive *pZip, mz_uint64 existing_आकार);
MINIZ_STATIC mz_bool mz_zip_writer_init_heap(mz_zip_archive *pZip, माप_प्रकार आकार_to_reserve_at_beginning, माप_प्रकार initial_allocation_आकार);

#अगर_अघोषित MINIZ_NO_STDIO
MINIZ_STATIC mz_bool mz_zip_writer_init_file(mz_zip_archive *pZip, स्थिर अक्षर *pFilename, mz_uint64 आकार_to_reserve_at_beginning);
#पूर्ण_अगर

// Converts a ZIP archive reader object into a writer object, to allow efficient in-place file appends to occur on an existing archive.
// For archives opened using mz_zip_reader_init_file, pFilename must be the archive's filename so it can be reopened for writing. If the file can't be reopened, mz_zip_reader_end() will be called.
// For archives opened using mz_zip_reader_init_mem, the memory block must be growable using the realloc callback (which defaults to realloc unless you've overridden it).
// Finally, for archives opened using mz_zip_reader_init, the mz_zip_archive's user provided m_pWrite function cannot be NULL.
// Note: In-place archive modification is not recommended unless you know what you're doing, because if execution stops or something goes wrong before
// the archive is finalized the file's central directory will be hosed.
MINIZ_STATIC mz_bool mz_zip_writer_init_from_reader(mz_zip_archive *pZip, स्थिर अक्षर *pFilename);

// Adds the contents of a memory buffer to an archive. These functions record the current local time into the archive.
// To add a directory entry, call this method with an archive name ending in a forwardslash with empty buffer.
// level_and_flags - compression level (0-10, see MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or just set to MZ_DEFAULT_COMPRESSION.
MINIZ_STATIC mz_bool mz_zip_writer_add_mem(mz_zip_archive *pZip, स्थिर अक्षर *pArchive_name, स्थिर व्योम *pBuf, माप_प्रकार buf_आकार_2, mz_uint level_and_flags);
MINIZ_STATIC mz_bool mz_zip_writer_add_mem_ex(mz_zip_archive *pZip, स्थिर अक्षर *pArchive_name, स्थिर व्योम *pBuf, माप_प्रकार buf_आकार_2, स्थिर व्योम *pComment, mz_uint16 comment_आकार, mz_uint level_and_flags, mz_uint64 uncomp_आकार, mz_uint32 uncomp_crc32);

#अगर_अघोषित MINIZ_NO_STDIO
// Adds the contents of a disk file to an archive. This function also records the disk file's modified time into the archive.
// level_and_flags - compression level (0-10, see MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or just set to MZ_DEFAULT_COMPRESSION.
MINIZ_STATIC mz_bool mz_zip_writer_add_file(mz_zip_archive *pZip, स्थिर अक्षर *pArchive_name, स्थिर अक्षर *pSrc_filename, स्थिर व्योम *pComment, mz_uint16 comment_आकार, mz_uint level_and_flags);
#पूर्ण_अगर

// Adds a file to an archive by fully cloning the data from another archive.
// This function fully clones the source file's compressed data (no recompression), along with its full filename, extra data, and comment fields.
MINIZ_STATIC mz_bool mz_zip_writer_add_from_zip_reader(mz_zip_archive *pZip, mz_zip_archive *pSource_zip, mz_uint file_सूचकांक);

// Finalizes the archive by writing the central directory records followed by the end of central directory record.
// After an archive is finalized, the only valid call on the mz_zip_archive struct is mz_zip_writer_end().
// An archive must be manually finalized by calling this function for it to be valid.
MINIZ_STATIC mz_bool mz_zip_writer_finalize_archive(mz_zip_archive *pZip);
MINIZ_STATIC mz_bool mz_zip_writer_finalize_heap_archive(mz_zip_archive *pZip, व्योम **pBuf, माप_प्रकार *p_आकार);

// Ends archive writing, freeing all allocations, and closing the output file if mz_zip_writer_init_file() was used.
// Note for the archive to be valid, it must have been finalized before ending.
MINIZ_STATIC mz_bool mz_zip_writer_end(mz_zip_archive *pZip);

// Misc. high-level helper functions:

// mz_zip_add_mem_to_archive_file_in_place() efficiently (but not atomically) appends a memory blob to a ZIP archive.
// level_and_flags - compression level (0-10, see MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or just set to MZ_DEFAULT_COMPRESSION.
MINIZ_STATIC mz_bool mz_zip_add_mem_to_archive_file_in_place(स्थिर अक्षर *pZip_filename, स्थिर अक्षर *pArchive_name, स्थिर व्योम *pBuf, माप_प्रकार buf_आकार_2, स्थिर व्योम *pComment, mz_uint16 comment_आकार, mz_uint level_and_flags);

// Reads a single file from an archive into a heap block.
// Returns NULL on failure.
MINIZ_STATIC व्योम *mz_zip_extract_archive_file_to_heap(स्थिर अक्षर *pZip_filename, स्थिर अक्षर *pArchive_name, माप_प्रकार *p_आकार, mz_uint zip_flags);

#पूर्ण_अगर // #ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

#पूर्ण_अगर // #ifndef MINIZ_NO_ARCHIVE_APIS

// ------------------- Low-level Decompression API Definitions
#अगर_अघोषित MINIZ_NO_INFLATE_APIS

// Decompression flags used by tinfl_decompress().
// TINFL_FLAG_PARSE_ZLIB_HEADER: If set, the input has a valid zlib header and ends with an adler32 checksum (it's a valid zlib stream). Otherwise, the input is a raw deflate stream.
// TINFL_FLAG_HAS_MORE_INPUT: If set, there are more input bytes available beyond the end of the supplied input buffer. If clear, the input buffer contains all remaining input.
// TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF: If set, the output buffer is large enough to hold the entire decompressed stream. If clear, the output buffer is at least the size of the dictionary (typically 32KB).
// TINFL_FLAG_COMPUTE_ADLER32: Force adler-32 checksum computation of the decompressed bytes.
क्रमागत
{
  TINFL_FLAG_PARSE_ZLIB_HEADER = 1,
  TINFL_FLAG_HAS_MORE_निवेश = 2,
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
MINIZ_STATIC व्योम *tinfl_decompress_mem_to_heap(स्थिर व्योम *pSrc_buf, माप_प्रकार src_buf_len, माप_प्रकार *pOut_len, पूर्णांक flags);

// tinfl_decompress_mem_to_mem() decompresses a block in memory to another block in memory.
// Returns TINFL_DECOMPRESS_MEM_TO_MEM_FAILED on failure, or the number of bytes written on success.
#घोषणा TINFL_DECOMPRESS_MEM_TO_MEM_FAILED ((माप_प्रकार)(-1))
MINIZ_STATIC माप_प्रकार tinfl_decompress_mem_to_mem(व्योम *pOut_buf, माप_प्रकार out_buf_len, स्थिर व्योम *pSrc_buf, माप_प्रकार src_buf_len, पूर्णांक flags);

// tinfl_decompress_mem_to_callback() decompresses a block in memory to an internal 32KB buffer, and a user provided callback function will be called to flush the buffer.
// Returns 1 on success or 0 on failure.
प्रकार पूर्णांक (*tinfl_put_buf_func_ptr)(स्थिर व्योम* pBuf, पूर्णांक len, व्योम *pUser);
MINIZ_STATIC पूर्णांक tinfl_decompress_mem_to_callback(स्थिर व्योम *pIn_buf, माप_प्रकार *p_In_buf_आकार, tinfl_put_buf_func_ptr pPut_buf_func, व्योम *pPut_buf_user, पूर्णांक flags);

काष्ठा tinfl_decompressor_tag; प्रकार काष्ठा tinfl_decompressor_tag tinfl_decompressor;

// Max size of LZ dictionary.
#घोषणा TINFL_LZ_DICT_आकार 32768

// Return status.
प्रकार क्रमागत
{
  TINFL_STATUS_BAD_PARAM = -3,
  TINFL_STATUS_ADLER32_MISMATCH = -2,
  TINFL_STATUS_FAILED = -1,
  TINFL_STATUS_DONE = 0,
  TINFL_STATUS_NEEDS_MORE_निवेश = 1,
  TINFL_STATUS_HAS_MORE_OUTPUT = 2
} tinfl_status;

// Initializes the decompressor to its initial state.
#घोषणा tinfl_init(r) करो { (r)->m_state = 0; } MZ_MACRO_END
#घोषणा tinfl_get_adler32(r) (r)->m_check_adler32

// Main low-level decompressor coroutine function. This is the only function actually needed for decompression. All the other functions are just high-level helpers for improved usability.
// This is a universal API, i.e. it can be used as a building block to build any desired higher level decompression API. In the limit case, it can be called once per every byte input or output.
MINIZ_STATIC tinfl_status tinfl_decompress(tinfl_decompressor *r, स्थिर mz_uint8 *p_In_buf_अग्र, माप_प्रकार *p_In_buf_आकार, mz_uint8 *pOut_buf_start, mz_uint8 *p_Out_buf_अग्र, माप_प्रकार *p_Out_buf_आकार, स्थिर mz_uint32 decomp_flags);

// Internal/private bits follow.
क्रमागत
{
  TINFL_MAX_HUFF_TABLES = 3, TINFL_MAX_HUFF_SYMBOLS_0 = 288, TINFL_MAX_HUFF_SYMBOLS_1 = 32, TINFL_MAX_HUFF_SYMBOLS_2 = 19,
  TINFL_FAST_LOOKUP_BITS = 10, TINFL_FAST_LOOKUP_आकार = 1 << TINFL_FAST_LOOKUP_BITS
};

प्रकार काष्ठा
{
  mz_uint8 m_code_आकार[TINFL_MAX_HUFF_SYMBOLS_0];
  mz_int16 m_look_up[TINFL_FAST_LOOKUP_आकार], m_वृक्ष[TINFL_MAX_HUFF_SYMBOLS_0 * 2];
} tinfl_huff_table;

#अगर MINIZ_HAS_64BIT_REGISTERS
  #घोषणा TINFL_USE_64BIT_BITBUF 1
#पूर्ण_अगर

#अगर TINFL_USE_64BIT_BITBUF
  प्रकार mz_uint64 tinfl_bit_buf_t;
  #घोषणा TINFL_BITBUF_आकार (64)
#अन्यथा
  प्रकार mz_uint32 tinfl_bit_buf_t;
  #घोषणा TINFL_BITBUF_आकार (32)
#पूर्ण_अगर

काष्ठा tinfl_decompressor_tag
{
  mz_uint32 m_state, m_अंक_bits, m_zhdr0, m_zhdr1, m_z_adler32, m_final, m_type, m_check_adler32, m_dist, m_गणक, m_अंक_extra, m_table_sizes[TINFL_MAX_HUFF_TABLES];
  tinfl_bit_buf_t m_bit_buf;
  माप_प्रकार m_dist_from_out_buf_start;
  tinfl_huff_table m_tables[TINFL_MAX_HUFF_TABLES];
  mz_uint8 m_raw_header[4], m_len_codes[TINFL_MAX_HUFF_SYMBOLS_0 + TINFL_MAX_HUFF_SYMBOLS_1 + 137];
};
#पूर्ण_अगर /*#ifndef MINIZ_NO_INFLATE_APIS*/

// ------------------- Low-level Compression API Definitions
#अगर_अघोषित MINIZ_NO_DEFLATE_APIS

// Set TDEFL_LESS_MEMORY to 1 to use less memory (compression will be slightly slower, and raw/dynamic blocks will be output more frequently).
#घोषणा TDEFL_LESS_MEMORY 0

// tdefl_init() compression flags logically OR'd together (low 12 bits contain the max. number of probes per dictionary search):
// TDEFL_DEFAULT_MAX_PROBES: The compressor defaults to 128 dictionary probes per dictionary search. 0=Huffman only, 1=Huffman+LZ (fastest/crap compression), 4095=Huffman+LZ (slowest/best compression).
क्रमागत
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
क्रमागत
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

#अगर_अघोषित MINIZ_SDL_NOUNUSED
// High level compression functions:
// tdefl_compress_mem_to_heap() compresses a block in memory to a heap block allocated via malloc().
// On entry:
//  pSrc_buf, src_buf_len: Pointer and size of source block to compress.
//  flags: The max match finder probes (default is 128) logically OR'd against the above flags. Higher probes are slower but improve compression.
// On return:
//  Function returns a pointer to the compressed data, or NULL on failure.
//  *pOut_len will be set to the compressed data's size, which could be larger than src_buf_len on uncompressible data.
//  The caller must free() the returned block when it's no longer needed.
MINIZ_STATIC व्योम *tdefl_compress_mem_to_heap(स्थिर व्योम *pSrc_buf, माप_प्रकार src_buf_len, माप_प्रकार *pOut_len, पूर्णांक flags);

// tdefl_compress_mem_to_mem() compresses a block in memory to another block in memory.
// Returns 0 on failure.
MINIZ_STATIC माप_प्रकार tdefl_compress_mem_to_mem(व्योम *pOut_buf, माप_प्रकार out_buf_len, स्थिर व्योम *pSrc_buf, माप_प्रकार src_buf_len, पूर्णांक flags);
#पूर्ण_अगर /* MINIZ_SDL_NOUNUSED */

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
MINIZ_STATIC व्योम *tdefl_write_image_to_png_file_in_memory_ex(स्थिर व्योम *pImage, पूर्णांक w, पूर्णांक h, पूर्णांक अंक_chans, पूर्णांक bpl, माप_प्रकार *pLen_out, mz_uint level, mz_bool flip, mz_uint8 *plte, पूर्णांक plte_आकार, mz_uint8 *trns, पूर्णांक trns_आकार);
#अगर_अघोषित MINIZ_SDL_NOUNUSED
MINIZ_STATIC व्योम *tdefl_write_image_to_png_file_in_memory(स्थिर व्योम *pImage, पूर्णांक w, पूर्णांक h, पूर्णांक अंक_chans, पूर्णांक bpl, माप_प्रकार *pLen_out);
#पूर्ण_अगर

// Output stream interface. The compressor uses this interface to write compressed data. It'll typically be called TDEFL_OUT_BUF_SIZE at a time.
प्रकार mz_bool (*tdefl_put_buf_func_ptr)(स्थिर व्योम* pBuf, पूर्णांक len, व्योम *pUser);

#अगर_अघोषित MINIZ_SDL_NOUNUSED
// tdefl_compress_mem_to_output() compresses a block to an output stream. The above helpers use this function internally.
MINIZ_STATIC mz_bool tdefl_compress_mem_to_output(स्थिर व्योम *pBuf, माप_प्रकार buf_len, tdefl_put_buf_func_ptr pPut_buf_func, व्योम *pPut_buf_user, पूर्णांक flags);
#पूर्ण_अगर

//enum { TDEFL_MAX_HUFF_TABLES = 3, TDEFL_MAX_HUFF_SYMBOLS_0 = 288, TDEFL_MAX_HUFF_SYMBOLS_1 = 32, TDEFL_MAX_HUFF_SYMBOLS_2 = 19, TDEFL_LZ_DICT_SIZE = 32768, TDEFL_LZ_DICT_SIZE_MASK = TDEFL_LZ_DICT_SIZE - 1, TDEFL_MIN_MATCH_LEN = 3, TDEFL_MAX_MATCH_LEN = 258 };
#घोषणा TDEFL_MAX_HUFF_TABLES	3
#घोषणा TDEFL_MAX_HUFF_SYMBOLS_0 288
#घोषणा TDEFL_MAX_HUFF_SYMBOLS_1 32
#घोषणा TDEFL_MAX_HUFF_SYMBOLS_2 19
#घोषणा TDEFL_LZ_DICT_आकार 32768
#घोषणा TDEFL_LZ_DICT_आकार_MASK	( TDEFL_LZ_DICT_आकार - 1 )
#घोषणा TDEFL_MIN_MATCH_LEN	3
#घोषणा TDEFL_MAX_MATCH_LEN 258

// TDEFL_OUT_BUF_SIZE MUST be large enough to hold a single entire compressed output block (using static/fixed Huffman codes).
#अगर TDEFL_LESS_MEMORY
क्रमागत { TDEFL_LZ_CODE_BUF_आकार = 24 * 1024, TDEFL_OUT_BUF_आकार = (TDEFL_LZ_CODE_BUF_आकार * 13 ) / 10, TDEFL_MAX_HUFF_SYMBOLS = 288, TDEFL_LZ_HASH_BITS = 12, TDEFL_LEVEL1_HASH_आकार_MASK = 4095, TDEFL_LZ_HASH_SHIFT = (TDEFL_LZ_HASH_BITS + 2) / 3, TDEFL_LZ_HASH_आकार = 1 << TDEFL_LZ_HASH_BITS };
#अन्यथा
क्रमागत { TDEFL_LZ_CODE_BUF_आकार = 64 * 1024, TDEFL_OUT_BUF_आकार = (TDEFL_LZ_CODE_BUF_आकार * 13 ) / 10, TDEFL_MAX_HUFF_SYMBOLS = 288, TDEFL_LZ_HASH_BITS = 15, TDEFL_LEVEL1_HASH_आकार_MASK = 4095, TDEFL_LZ_HASH_SHIFT = (TDEFL_LZ_HASH_BITS + 2) / 3, TDEFL_LZ_HASH_आकार = 1 << TDEFL_LZ_HASH_BITS };
#पूर्ण_अगर

// The low-level tdefl functions below may be used directly if the above helper functions aren't flexible enough. The low-level functions don't make any heap allocations, unlike the above helper functions.
प्रकार क्रमागत
{
  TDEFL_STATUS_BAD_PARAM = -2,
  TDEFL_STATUS_PUT_BUF_FAILED = -1,
  TDEFL_STATUS_OKAY = 0,
  TDEFL_STATUS_DONE = 1,
} tdefl_status;

// Must map to MZ_NO_FLUSH, MZ_SYNC_FLUSH, etc. enums
प्रकार क्रमागत
{
  TDEFL_NO_FLUSH = 0,
  TDEFL_SYNC_FLUSH = 2,
  TDEFL_FULL_FLUSH = 3,
  TDEFL_FINISH = 4
} tdefl_flush;

// tdefl's compression state structure.
प्रकार काष्ठा
{
  tdefl_put_buf_func_ptr m_pPut_buf_func;
  व्योम *m_pPut_buf_user;
  mz_uint m_flags, m_max_probes[2];
  पूर्णांक m_greedy_parsing;
  mz_uint m_adler32, m_lookahead_pos, m_lookahead_आकार, m_dict_आकार;
  mz_uint8 *m_pLZ_code_buf, *m_pLZ_flags, *m_pOutput_buf, *m_pOutput_buf_end;
  mz_uint m_अंक_flags_बायाँ, m_योग_lz_bytes, m_lz_code_buf_dict_pos, m_bits_in, m_bit_बफर;
  mz_uint m_saved_match_dist, m_saved_match_len, m_saved_lit, m_output_flush_ofs, m_output_flush_remaining, m_finished, m_block_सूचकांक, m_wants_to_finish;
  tdefl_status m_पूर्व_return_status;
  स्थिर व्योम *m_pIn_buf;
  व्योम *m_pOut_buf;
  माप_प्रकार *m_p_In_buf_आकार, *m_p_Out_buf_आकार;
  tdefl_flush m_flush;
  स्थिर mz_uint8 *m_pSrc;
  माप_प्रकार m_src_buf_बायाँ, m_out_buf_ofs;
  mz_uint8 m_dict[TDEFL_LZ_DICT_आकार + TDEFL_MAX_MATCH_LEN - 1];
  mz_uint16 m_huff_गिनती[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint16 m_huff_codes[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint8 m_huff_code_sizes[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint8 m_lz_code_buf[TDEFL_LZ_CODE_BUF_आकार];
  mz_uint16 m_अग्र[TDEFL_LZ_DICT_आकार];
  mz_uint16 m_hash[TDEFL_LZ_HASH_आकार];
  mz_uint8 m_output_buf[TDEFL_OUT_BUF_आकार];
} tdefl_compressor;

// Initializes the compressor.
// There is no corresponding deinit() function because the tdefl API's do not dynamically allocate memory.
// pBut_buf_func: If NULL, output data will be supplied to the specified callback. In this case, the user should call the tdefl_compress_buffer() API for compression.
// If pBut_buf_func is NULL the user should always call the tdefl_compress() API.
// flags: See the above enums (TDEFL_HUFFMAN_ONLY, TDEFL_WRITE_ZLIB_HEADER, etc.)
MINIZ_STATIC tdefl_status tdefl_init(tdefl_compressor *d, tdefl_put_buf_func_ptr pPut_buf_func, व्योम *pPut_buf_user, पूर्णांक flags);

// Compresses a block of data, consuming as much of the specified input buffer as possible, and writing as much compressed data to the specified output buffer as possible.
MINIZ_STATIC tdefl_status tdefl_compress(tdefl_compressor *d, स्थिर व्योम *pIn_buf, माप_प्रकार *p_In_buf_आकार, व्योम *pOut_buf, माप_प्रकार *p_Out_buf_आकार, tdefl_flush flush);

// tdefl_compress_buffer() is only usable when the tdefl_init() is called with a non-NULL tdefl_put_buf_func_ptr.
// tdefl_compress_buffer() always consumes the entire input buffer.
MINIZ_STATIC tdefl_status tdefl_compress_बफर(tdefl_compressor *d, स्थिर व्योम *pIn_buf, माप_प्रकार in_buf_आकार, tdefl_flush flush);

#अगर_अघोषित MINIZ_SDL_NOUNUSED
MINIZ_STATIC tdefl_status tdefl_get_पूर्व_return_status(tdefl_compressor *d);
MINIZ_STATIC mz_uint32 tdefl_get_adler32(tdefl_compressor *d);
#पूर्ण_अगर

// Can't use tdefl_create_comp_flags_from_zip_params if MINIZ_NO_ZLIB_APIS isn't defined, because it uses some of its macros.
#अगर_अघोषित MINIZ_NO_ZLIB_APIS
// Create tdefl_compress() flags given zlib-style compression parameters.
// level may range from [0,10] (where 10 is absolute max compression, but may be much slower on some files)
// window_bits may be -15 (raw deflate) or 15 (zlib)
// strategy may be either MZ_DEFAULT_STRATEGY, MZ_FILTERED, MZ_HUFFMAN_ONLY, MZ_RLE, or MZ_FIXED
MINIZ_STATIC mz_uint tdefl_create_comp_flags_from_zip_params(पूर्णांक level, पूर्णांक window_bits, पूर्णांक strategy);
#पूर्ण_अगर // #ifndef MINIZ_NO_ZLIB_APIS

#पूर्ण_अगर /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर // MINIZ_HEADER_INCLUDED

// ------------------- End of Header: Implementation follows. (If you only want the header, define MINIZ_HEADER_FILE_ONLY.)

#अगर_अघोषित MINIZ_HEADER_FILE_ONLY

#अगर_घोषित _MSC_VER
#आशय warning (धकेलो)
#आशय warning (disable:4505) // unreferenced local function has been removed
#पूर्ण_अगर

प्रकार अचिन्हित अक्षर mz_validate_uint16[माप(mz_uint16)==2 ? 1 : -1];
प्रकार अचिन्हित अक्षर mz_validate_uint32[माप(mz_uint32)==4 ? 1 : -1];
प्रकार अचिन्हित अक्षर mz_validate_uint64[माप(mz_uint64)==8 ? 1 : -1];

/*#include <string.h>*/

#अगर_अघोषित MZ_ASSERT
#समावेश <assert.h>
#घोषणा MZ_ASSERT(x) निश्चित(x)
#पूर्ण_अगर

#अगर_घोषित MINIZ_NO_MALLOC
  #घोषणा MZ_MALLOC(x) शून्य
  #घोषणा MZ_FREE(x) (व्योम)x, ((व्योम)0)
  #घोषणा MZ_REALLOC(p, x) शून्य
#या_अगर defined(MINIZ_SDL_MALLOC)
  #घोषणा MZ_MALLOC(x) SDL_malloc(x)
  #घोषणा MZ_FREE(x) SDL_free(x)
  #घोषणा MZ_REALLOC(p, x) SDL_realloc(p, x)
#अन्यथा
  #घोषणा MZ_MALLOC(x) दो_स्मृति(x)
  #घोषणा MZ_FREE(x) मुक्त(x)
  #घोषणा MZ_REALLOC(p, x) पुनः_स्मृति(p, x)
#पूर्ण_अगर

#घोषणा MZ_MAX(a,b) (((a)>(b))?(a):(b))
#घोषणा MZ_MIN(a,b) (((a)<(b))?(a):(b))
#घोषणा MZ_CLEAR_OBJ(obj) स_रखो(&(obj), 0, माप(obj))
#घोषणा MZ_CLEAR_ARR(obj) स_रखो((obj), 0, माप(obj))
#घोषणा MZ_CLEAR_PTR(obj) स_रखो((obj), 0, माप(*obj))

#अगर MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  #घोषणा MZ_READ_LE16(p) *((स्थिर mz_uint16 *)(p))
  #घोषणा MZ_READ_LE32(p) *((स्थिर mz_uint32 *)(p))
#अन्यथा
  #घोषणा MZ_READ_LE16(p) ((mz_uint32)(((स्थिर mz_uint8 *)(p))[0]) | ((mz_uint32)(((स्थिर mz_uint8 *)(p))[1]) << 8U))
  #घोषणा MZ_READ_LE32(p) ((mz_uint32)(((स्थिर mz_uint8 *)(p))[0]) | ((mz_uint32)(((स्थिर mz_uint8 *)(p))[1]) << 8U) | ((mz_uint32)(((स्थिर mz_uint8 *)(p))[2]) << 16U) | ((mz_uint32)(((स्थिर mz_uint8 *)(p))[3]) << 24U))
#पूर्ण_अगर

#अगर_घोषित _MSC_VER
  #घोषणा MZ_FORCEINLINE __forceinline
#या_अगर defined(__GNUC__)
  #घोषणा MZ_FORCEINLINE अंतरभूत __attribute__((__always_inline__))
#अन्यथा
  #घोषणा MZ_FORCEINLINE अंतरभूत
#पूर्ण_अगर

#अगर_घोषित __cplusplus
  बाह्य "C" {
#पूर्ण_अगर

// ------------------- zlib-style API's

mz_ulong mz_adler32(mz_ulong adler, स्थिर अचिन्हित अक्षर *ptr, माप_प्रकार buf_len)
{
  mz_uint32 i, s1 = (mz_uint32)(adler & 0xffff), s2 = (mz_uint32)(adler >> 16); माप_प्रकार block_len = buf_len % 5552;
  अगर (!ptr) वापस MZ_ADLER32_INIT;
  जबतक (buf_len) {
    क्रम (i = 0; i + 7 < block_len; i += 8, ptr += 8) {
      s1 += ptr[0]; s2 += s1; s1 += ptr[1]; s2 += s1; s1 += ptr[2]; s2 += s1; s1 += ptr[3]; s2 += s1;
      s1 += ptr[4]; s2 += s1; s1 += ptr[5]; s2 += s1; s1 += ptr[6]; s2 += s1; s1 += ptr[7]; s2 += s1;
    }
    क्रम ( ; i < block_len; ++i) { s1 += *ptr++; s2 += s1; }
    s1 %= 65521U; s2 %= 65521U; buf_len -= block_len; block_len = 5552;
  }
  वापस (s2 << 16) + s1;
}

// Karl Malbrain's compact CRC-32. See "A compact CCITT crc16 and crc32 C implementation that balances processor cache usage against speed": http://www.geocities.com/malbrain/
mz_ulong mz_crc32(mz_ulong crc, स्थिर mz_uint8 *ptr, माप_प्रकार buf_len)
{
  अटल स्थिर mz_uint32 s_crc32[16] = { 0, 0x1db71064, 0x3b6e20c8, 0x26d930ac, 0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
    0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c, 0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c };
  mz_uint32 crcu32 = (mz_uint32)crc;
  अगर (!ptr) वापस MZ_CRC32_INIT;
  crcu32 = ~crcu32; जबतक (buf_len--) { mz_uint8 b = *ptr++; crcu32 = (crcu32 >> 4) ^ s_crc32[(crcu32 & 0xF) ^ (b & 0xF)]; crcu32 = (crcu32 >> 4) ^ s_crc32[(crcu32 & 0xF) ^ (b >> 4)]; }
  वापस ~crcu32;
}

MINIZ_STATIC व्योम mz_free(व्योम *p)
{
  MZ_FREE(p);
}

#अगर_अघोषित MINIZ_NO_ZLIB_APIS

अटल व्योम *def_alloc_func(व्योम *opaque, माप_प्रकार वस्तुएँ, माप_प्रकार आकार) { (व्योम)opaque, (व्योम)वस्तुएँ, (व्योम)आकार; वापस MZ_MALLOC(वस्तुएँ * आकार); }
अटल व्योम def_free_func(व्योम *opaque, व्योम *address) { (व्योम)opaque, (व्योम)address; MZ_FREE(address); }
अटल व्योम *def_realloc_func(व्योम *opaque, व्योम *address, माप_प्रकार वस्तुएँ, माप_प्रकार आकार) { (व्योम)opaque, (व्योम)address, (व्योम)वस्तुएँ, (व्योम)आकार; वापस MZ_REALLOC(address, वस्तुएँ * आकार); }

स्थिर अक्षर *mz_version(व्योम)
{
  वापस MZ_VERSION;
}

#अगर_अघोषित MINIZ_NO_DEFLATE_APIS

पूर्णांक mz_deflateInit(mz_streamp pStream, पूर्णांक level)
{
  वापस mz_deflateInit2(pStream, level, MZ_DEFLATED, MZ_DEFAULT_WINDOW_BITS, 9, MZ_DEFAULT_STRATEGY);
}

पूर्णांक mz_deflateInit2(mz_streamp pStream, पूर्णांक level, पूर्णांक method, पूर्णांक window_bits, पूर्णांक mem_level, पूर्णांक strategy)
{
  tdefl_compressor *pComp;
  mz_uint comp_flags = TDEFL_COMPUTE_ADLER32 | tdefl_create_comp_flags_from_zip_params(level, window_bits, strategy);

  अगर (!pStream) वापस MZ_STREAM_ERROR;
  अगर ((method != MZ_DEFLATED) || ((mem_level < 1) || (mem_level > 9)) || ((window_bits != MZ_DEFAULT_WINDOW_BITS) && (-window_bits != MZ_DEFAULT_WINDOW_BITS))) वापस MZ_PARAM_ERROR;

  pStream->तथ्य_type = 0;
  pStream->adler = MZ_ADLER32_INIT;
  pStream->संदेश = शून्य;
  pStream->reserved = 0;
  pStream->योग_in = 0;
  pStream->योग_out = 0;
  अगर (!pStream->zalloc) pStream->zalloc = def_alloc_func;
  अगर (!pStream->zfree) pStream->zfree = def_free_func;

  pComp = (tdefl_compressor *)pStream->zalloc(pStream->opaque, 1, माप(tdefl_compressor));
  अगर (!pComp)
    वापस MZ_MEM_ERROR;

  pStream->state = (काष्ठा mz_internal_state *)pComp;

  अगर (tdefl_init(pComp, शून्य, शून्य, comp_flags) != TDEFL_STATUS_OKAY)
  {
    mz_deflateEnd(pStream);
    वापस MZ_PARAM_ERROR;
  }

  वापस MZ_OK;
}

पूर्णांक mz_deflateReset(mz_streamp pStream)
{
  अगर ((!pStream) || (!pStream->state) || (!pStream->zalloc) || (!pStream->zfree)) वापस MZ_STREAM_ERROR;
  pStream->योग_in = pStream->योग_out = 0;
  tdefl_init((tdefl_compressor*)pStream->state, शून्य, शून्य, ((tdefl_compressor*)pStream->state)->m_flags);
  वापस MZ_OK;
}

पूर्णांक mz_deflate(mz_streamp pStream, पूर्णांक flush)
{
  माप_प्रकार in_bytes, out_bytes;
  mz_ulong orig_योग_in, orig_योग_out;
  पूर्णांक mz_status = MZ_OK;

  अगर ((!pStream) || (!pStream->state) || (flush < 0) || (flush > MZ_FINISH) || (!pStream->अग्र_out)) वापस MZ_STREAM_ERROR;
  अगर (!pStream->avail_out) वापस MZ_BUF_ERROR;

  अगर (flush == MZ_PARTIAL_FLUSH) flush = MZ_SYNC_FLUSH;

  अगर (((tdefl_compressor*)pStream->state)->m_पूर्व_return_status == TDEFL_STATUS_DONE)
    वापस (flush == MZ_FINISH) ? MZ_STREAM_END : MZ_BUF_ERROR;

  orig_योग_in = pStream->योग_in; orig_योग_out = pStream->योग_out;
  क्रम ( ; ; )
  {
    tdefl_status defl_status;
    in_bytes = pStream->avail_in; out_bytes = pStream->avail_out;

    defl_status = tdefl_compress((tdefl_compressor*)pStream->state, pStream->अग्र_in, &in_bytes, pStream->अग्र_out, &out_bytes, (tdefl_flush)flush);
    pStream->अग्र_in += (mz_uint)in_bytes; pStream->avail_in -= (mz_uint)in_bytes;
    pStream->योग_in += (mz_uint)in_bytes; pStream->adler = tdefl_get_adler32((tdefl_compressor*)pStream->state);

    pStream->अग्र_out += (mz_uint)out_bytes; pStream->avail_out -= (mz_uint)out_bytes;
    pStream->योग_out += (mz_uint)out_bytes;

    अगर (defl_status < 0)
    {
      mz_status = MZ_STREAM_ERROR;
      अवरोध;
    }
    अन्यथा अगर (defl_status == TDEFL_STATUS_DONE)
    {
      mz_status = MZ_STREAM_END;
      अवरोध;
    }
    अन्यथा अगर (!pStream->avail_out)
      अवरोध;
    अन्यथा अगर ((!pStream->avail_in) && (flush != MZ_FINISH))
    {
      अगर ((flush) || (pStream->योग_in != orig_योग_in) || (pStream->योग_out != orig_योग_out))
        अवरोध;
      वापस MZ_BUF_ERROR; // Can't make forward progress without some input.
    }
  }
  वापस mz_status;
}

पूर्णांक mz_deflateEnd(mz_streamp pStream)
{
  अगर (!pStream) वापस MZ_STREAM_ERROR;
  अगर (pStream->state)
  {
    pStream->zfree(pStream->opaque, pStream->state);
    pStream->state = शून्य;
  }
  वापस MZ_OK;
}

mz_ulong mz_deflateBound(mz_streamp pStream, mz_ulong source_len)
{
  (व्योम)pStream;
  // This is really over conservative. (And lame, but it's actually pretty tricky to compute a true upper bound given the way tdefl's blocking works.)
  वापस MZ_MAX(128 + (source_len * 110) / 100, 128 + source_len + ((source_len / (31 * 1024)) + 1) * 5);
}

पूर्णांक mz_compress2(अचिन्हित अक्षर *pDest, mz_ulong *pDest_len, स्थिर अचिन्हित अक्षर *pSource, mz_ulong source_len, पूर्णांक level)
{
  पूर्णांक status;
  mz_stream stream;
  स_रखो(&stream, 0, माप(stream));

  // In case mz_ulong is 64-bits (argh I hate longs).
  अगर ((source_len | *pDest_len) > 0xFFFFFFFFU) वापस MZ_PARAM_ERROR;

  stream.अग्र_in = pSource;
  stream.avail_in = (mz_uint32)source_len;
  stream.अग्र_out = pDest;
  stream.avail_out = (mz_uint32)*pDest_len;

  status = mz_deflateInit(&stream, level);
  अगर (status != MZ_OK) वापस status;

  status = mz_deflate(&stream, MZ_FINISH);
  अगर (status != MZ_STREAM_END)
  {
    mz_deflateEnd(&stream);
    वापस (status == MZ_OK) ? MZ_BUF_ERROR : status;
  }

  *pDest_len = stream.योग_out;
  वापस mz_deflateEnd(&stream);
}

पूर्णांक mz_compress(अचिन्हित अक्षर *pDest, mz_ulong *pDest_len, स्थिर अचिन्हित अक्षर *pSource, mz_ulong source_len)
{
  वापस mz_compress2(pDest, pDest_len, pSource, source_len, MZ_DEFAULT_COMPRESSION);
}

mz_ulong mz_compressBound(mz_ulong source_len)
{
  वापस mz_deflateBound(शून्य, source_len);
}

#पूर्ण_अगर /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#अगर_अघोषित MINIZ_NO_INFLATE_APIS

प्रकार काष्ठा
{
  tinfl_decompressor m_decomp;
  mz_uint m_dict_ofs, m_dict_avail, m_first_call, m_has_flushed; पूर्णांक m_window_bits;
  mz_uint8 m_dict[TINFL_LZ_DICT_आकार];
  tinfl_status m_last_status;
} inflate_state;

पूर्णांक mz_inflateInit2(mz_streamp pStream, पूर्णांक window_bits)
{
  inflate_state *pDecomp;
  अगर (!pStream) वापस MZ_STREAM_ERROR;
  अगर ((window_bits != MZ_DEFAULT_WINDOW_BITS) && (-window_bits != MZ_DEFAULT_WINDOW_BITS)) वापस MZ_PARAM_ERROR;

  pStream->तथ्य_type = 0;
  pStream->adler = 0;
  pStream->संदेश = शून्य;
  pStream->योग_in = 0;
  pStream->योग_out = 0;
  pStream->reserved = 0;
  अगर (!pStream->zalloc) pStream->zalloc = def_alloc_func;
  अगर (!pStream->zfree) pStream->zfree = def_free_func;

  pDecomp = (inflate_state*)pStream->zalloc(pStream->opaque, 1, माप(inflate_state));
  अगर (!pDecomp) वापस MZ_MEM_ERROR;

  pStream->state = (काष्ठा mz_internal_state *)pDecomp;

  tinfl_init(&pDecomp->m_decomp);
  pDecomp->m_dict_ofs = 0;
  pDecomp->m_dict_avail = 0;
  pDecomp->m_last_status = TINFL_STATUS_NEEDS_MORE_निवेश;
  pDecomp->m_first_call = 1;
  pDecomp->m_has_flushed = 0;
  pDecomp->m_window_bits = window_bits;

  वापस MZ_OK;
}

पूर्णांक mz_inflateInit(mz_streamp pStream)
{
   वापस mz_inflateInit2(pStream, MZ_DEFAULT_WINDOW_BITS);
}

पूर्णांक mz_inflate(mz_streamp pStream, पूर्णांक flush)
{
  inflate_state* pState;
  mz_uint n, first_call, decomp_flags = TINFL_FLAG_COMPUTE_ADLER32;
  माप_प्रकार in_bytes, out_bytes, orig_avail_in;
  tinfl_status status;

  अगर ((!pStream) || (!pStream->state)) वापस MZ_STREAM_ERROR;
  अगर (flush == MZ_PARTIAL_FLUSH) flush = MZ_SYNC_FLUSH;
  अगर ((flush) && (flush != MZ_SYNC_FLUSH) && (flush != MZ_FINISH)) वापस MZ_STREAM_ERROR;

  pState = (inflate_state*)pStream->state;
  अगर (pState->m_window_bits > 0) decomp_flags |= TINFL_FLAG_PARSE_ZLIB_HEADER;
  orig_avail_in = pStream->avail_in;

  first_call = pState->m_first_call; pState->m_first_call = 0;
  अगर (pState->m_last_status < 0) वापस MZ_तथ्य_ERROR;

  अगर (pState->m_has_flushed && (flush != MZ_FINISH)) वापस MZ_STREAM_ERROR;
  pState->m_has_flushed |= (flush == MZ_FINISH);

  अगर ((flush == MZ_FINISH) && (first_call))
  {
    // MZ_FINISH on the first call implies that the input and output buffers are large enough to hold the entire compressed/decompressed file.
    decomp_flags |= TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF;
    in_bytes = pStream->avail_in; out_bytes = pStream->avail_out;
    status = tinfl_decompress(&pState->m_decomp, pStream->अग्र_in, &in_bytes, pStream->अग्र_out, pStream->अग्र_out, &out_bytes, decomp_flags);
    pState->m_last_status = status;
    pStream->अग्र_in += (mz_uint)in_bytes; pStream->avail_in -= (mz_uint)in_bytes; pStream->योग_in += (mz_uint)in_bytes;
    pStream->adler = tinfl_get_adler32(&pState->m_decomp);
    pStream->अग्र_out += (mz_uint)out_bytes; pStream->avail_out -= (mz_uint)out_bytes; pStream->योग_out += (mz_uint)out_bytes;

    अगर (status < 0)
      वापस MZ_तथ्य_ERROR;
    अन्यथा अगर (status != TINFL_STATUS_DONE)
    {
      pState->m_last_status = TINFL_STATUS_FAILED;
      वापस MZ_BUF_ERROR;
    }
    वापस MZ_STREAM_END;
  }
  // flush != MZ_FINISH then we must assume there's more input.
  अगर (flush != MZ_FINISH) decomp_flags |= TINFL_FLAG_HAS_MORE_निवेश;

  अगर (pState->m_dict_avail)
  {
    n = MZ_MIN(pState->m_dict_avail, pStream->avail_out);
    स_नकल(pStream->अग्र_out, pState->m_dict + pState->m_dict_ofs, n);
    pStream->अग्र_out += n; pStream->avail_out -= n; pStream->योग_out += n;
    pState->m_dict_avail -= n; pState->m_dict_ofs = (pState->m_dict_ofs + n) & (TINFL_LZ_DICT_आकार - 1);
    वापस ((pState->m_last_status == TINFL_STATUS_DONE) && (!pState->m_dict_avail)) ? MZ_STREAM_END : MZ_OK;
  }

  क्रम ( ; ; )
  {
    in_bytes = pStream->avail_in;
    out_bytes = TINFL_LZ_DICT_आकार - pState->m_dict_ofs;

    status = tinfl_decompress(&pState->m_decomp, pStream->अग्र_in, &in_bytes, pState->m_dict, pState->m_dict + pState->m_dict_ofs, &out_bytes, decomp_flags);
    pState->m_last_status = status;

    pStream->अग्र_in += (mz_uint)in_bytes; pStream->avail_in -= (mz_uint)in_bytes;
    pStream->योग_in += (mz_uint)in_bytes; pStream->adler = tinfl_get_adler32(&pState->m_decomp);

    pState->m_dict_avail = (mz_uint)out_bytes;

    n = MZ_MIN(pState->m_dict_avail, pStream->avail_out);
    स_नकल(pStream->अग्र_out, pState->m_dict + pState->m_dict_ofs, n);
    pStream->अग्र_out += n; pStream->avail_out -= n; pStream->योग_out += n;
    pState->m_dict_avail -= n; pState->m_dict_ofs = (pState->m_dict_ofs + n) & (TINFL_LZ_DICT_आकार - 1);

    अगर (status < 0)
       वापस MZ_तथ्य_ERROR; // Stream is corrupted (there could be some uncompressed data left in the output dictionary - oh well).
    अन्यथा अगर ((status == TINFL_STATUS_NEEDS_MORE_निवेश) && (!orig_avail_in))
      वापस MZ_BUF_ERROR; // Signal caller that we can't make forward progress without supplying more input or by setting flush to MZ_FINISH.
    अन्यथा अगर (flush == MZ_FINISH)
    {
       // The output buffer MUST be large to hold the remaining uncompressed data when flush==MZ_FINISH.
       अगर (status == TINFL_STATUS_DONE)
          वापस pState->m_dict_avail ? MZ_BUF_ERROR : MZ_STREAM_END;
       // status here must be TINFL_STATUS_HAS_MORE_OUTPUT, which means there's at least 1 more byte on the way. If there's no more room left in the output buffer then something is wrong.
       अन्यथा अगर (!pStream->avail_out)
          वापस MZ_BUF_ERROR;
    }
    अन्यथा अगर ((status == TINFL_STATUS_DONE) || (!pStream->avail_in) || (!pStream->avail_out) || (pState->m_dict_avail))
      अवरोध;
  }

  वापस ((status == TINFL_STATUS_DONE) && (!pState->m_dict_avail)) ? MZ_STREAM_END : MZ_OK;
}

पूर्णांक mz_inflateEnd(mz_streamp pStream)
{
  अगर (!pStream)
    वापस MZ_STREAM_ERROR;
  अगर (pStream->state)
  {
    pStream->zfree(pStream->opaque, pStream->state);
    pStream->state = शून्य;
  }
  वापस MZ_OK;
}

पूर्णांक mz_uncompress(अचिन्हित अक्षर *pDest, mz_ulong *pDest_len, स्थिर अचिन्हित अक्षर *pSource, mz_ulong source_len)
{
  mz_stream stream;
  पूर्णांक status;
  स_रखो(&stream, 0, माप(stream));

  // In case mz_ulong is 64-bits (argh I hate longs).
  अगर ((source_len | *pDest_len) > 0xFFFFFFFFU) वापस MZ_PARAM_ERROR;

  stream.अग्र_in = pSource;
  stream.avail_in = (mz_uint32)source_len;
  stream.अग्र_out = pDest;
  stream.avail_out = (mz_uint32)*pDest_len;

  status = mz_inflateInit(&stream);
  अगर (status != MZ_OK)
    वापस status;

  status = mz_inflate(&stream, MZ_FINISH);
  अगर (status != MZ_STREAM_END)
  {
    mz_inflateEnd(&stream);
    वापस ((status == MZ_BUF_ERROR) && (!stream.avail_in)) ? MZ_तथ्य_ERROR : status;
  }
  *pDest_len = stream.योग_out;

  वापस mz_inflateEnd(&stream);
}

#पूर्ण_अगर /*#ifndef MINIZ_NO_INFLATE_APIS*/

स्थिर अक्षर *mz_error(पूर्णांक err)
{
  अटल काष्ठा { पूर्णांक m_err; स्थिर अक्षर *m_pDesc; } s_error_descs[] =
  {
    { MZ_OK, "" }, { MZ_STREAM_END, "stream end" }, { MZ_NEED_DICT, "need dictionary" }, { MZ_ERRNO, "file error" }, { MZ_STREAM_ERROR, "stream error" },
    { MZ_तथ्य_ERROR, "data error" }, { MZ_MEM_ERROR, "out of memory" }, { MZ_BUF_ERROR, "buf error" }, { MZ_VERSION_ERROR, "version error" }, { MZ_PARAM_ERROR, "parameter error" }
  };
  mz_uint i; क्रम (i = 0; i < माप(s_error_descs) / माप(s_error_descs[0]); ++i) अगर (s_error_descs[i].m_err == err) वापस s_error_descs[i].m_pDesc;
  वापस शून्य;
}

#पूर्ण_अगर //MINIZ_NO_ZLIB_APIS

// ------------------- Low-level Decompression (completely independent from all compression API's)
#अगर_अघोषित MINIZ_NO_INFLATE_APIS

#घोषणा TINFL_MEMCPY(d, s, l) स_नकल(d, s, l)
#घोषणा TINFL_MEMSET(p, c, l) स_रखो(p, c, l)

#घोषणा TINFL_CR_BEGIN चयन(r->m_state) { हाल 0:
#घोषणा TINFL_CR_RETURN(state_सूचकांक, परिणाम) करो { status = परिणाम; r->m_state = state_सूचकांक; जाओ common_exit; हाल state_सूचकांक:; } MZ_MACRO_END
#घोषणा TINFL_CR_RETURN_FOREVER(state_सूचकांक, परिणाम) करो { क्रम ( ; ; ) { TINFL_CR_RETURN(state_सूचकांक, परिणाम); } } MZ_MACRO_END
#घोषणा TINFL_CR_FINISH }

// TODO: If the caller has indicated that there's no more input, and we attempt to read beyond the input buf, then something is wrong with the input because the inflator never
// reads ahead more than it needs to. Currently TINFL_GET_BYTE() pads the end of the stream with 0's in this scenario.
#घोषणा TINFL_GET_BYTE(state_सूचकांक, c) करो { \
  अगर (pIn_buf_cur >= pIn_buf_end) { \
    क्रम ( ; ; ) { \
      अगर (decomp_flags & TINFL_FLAG_HAS_MORE_निवेश) { \
        TINFL_CR_RETURN(state_सूचकांक, TINFL_STATUS_NEEDS_MORE_निवेश); \
        अगर (pIn_buf_cur < pIn_buf_end) { \
          c = *pIn_buf_cur++; \
          अवरोध; \
        } \
      } अन्यथा { \
        c = 0; \
        अवरोध; \
      } \
    } \
  } अन्यथा c = *pIn_buf_cur++; } MZ_MACRO_END

#घोषणा TINFL_NEED_BITS(state_सूचकांक, n) करो { mz_uint c; TINFL_GET_BYTE(state_सूचकांक, c); bit_buf |= (((tinfl_bit_buf_t)c) << अंक_bits); अंक_bits += 8; } जबतक (अंक_bits < (mz_uint)(n))
#घोषणा TINFL_SKIP_BITS(state_सूचकांक, n) करो { अगर (अंक_bits < (mz_uint)(n)) { TINFL_NEED_BITS(state_सूचकांक, n); } bit_buf >>= (n); अंक_bits -= (n); } MZ_MACRO_END
#घोषणा TINFL_GET_BITS(state_सूचकांक, b, n) करो { अगर (अंक_bits < (mz_uint)(n)) { TINFL_NEED_BITS(state_सूचकांक, n); } b = bit_buf & ((1 << (n)) - 1); bit_buf >>= (n); अंक_bits -= (n); } MZ_MACRO_END

// TINFL_HUFF_BITBUF_FILL() is only used rarely, when the number of bytes remaining in the input buffer falls below 2.
// It reads just enough bytes from the input stream that are needed to decode the next Huffman code (and absolutely no more). It works by trying to fully decode a
// Huffman code by using whatever bits are currently present in the bit buffer. If this fails, it reads another byte, and tries again until it succeeds or until the
// bit buffer contains >=15 bits (deflate's max. Huffman code size).
#घोषणा TINFL_HUFF_BITBUF_FILL(state_सूचकांक, pHuff) \
  करो { \
    अस्थायी = (pHuff)->m_look_up[bit_buf & (TINFL_FAST_LOOKUP_आकार - 1)]; \
    अगर (अस्थायी >= 0) { \
      code_len = अस्थायी >> 9; \
      अगर ((code_len) && (अंक_bits >= code_len)) \
          अवरोध; \
    } अन्यथा अगर (अंक_bits > TINFL_FAST_LOOKUP_BITS) { \
       code_len = TINFL_FAST_LOOKUP_BITS; \
       करो { \
          अस्थायी = (pHuff)->m_वृक्ष[~अस्थायी + ((bit_buf >> code_len++) & 1)]; \
       } जबतक ((अस्थायी < 0) && (अंक_bits >= (code_len + 1))); \
       अगर (अस्थायी >= 0) अवरोध; \
    } \
    TINFL_GET_BYTE(state_सूचकांक, c); \
    bit_buf |= (((tinfl_bit_buf_t)c) << अंक_bits); \
    अंक_bits += 8; \
  } जबतक (अंक_bits < 15);

// TINFL_HUFF_DECODE() decodes the next Huffman coded symbol. It's more complex than you would initially expect because the zlib API expects the decompressor to never read
// beyond the final byte of the deflate stream. (In other words, when this macro wants to read another byte from the input, it REALLY needs another byte in order to fully
// decode the next Huffman code.) Handling this properly is particularly important on raw deflate (non-zlib) streams, which aren't followed by a byte aligned adler-32.
// The slow path is only executed at the very end of the input buffer.
#घोषणा TINFL_HUFF_DECODE(state_सूचकांक, sym, pHuff) करो { \
  पूर्णांक अस्थायी; mz_uint code_len, c; \
  अगर (अंक_bits < 15) { \
    अगर ((pIn_buf_end - pIn_buf_cur) < 2) { \
       TINFL_HUFF_BITBUF_FILL(state_सूचकांक, pHuff); \
    } अन्यथा { \
       bit_buf |= (((tinfl_bit_buf_t)pIn_buf_cur[0]) << अंक_bits) | (((tinfl_bit_buf_t)pIn_buf_cur[1]) << (अंक_bits + 8)); pIn_buf_cur += 2; अंक_bits += 16; \
    } \
  } \
  अगर ((अस्थायी = (pHuff)->m_look_up[bit_buf & (TINFL_FAST_LOOKUP_आकार - 1)]) >= 0) \
    code_len = अस्थायी >> 9, अस्थायी &= 511; \
  अन्यथा { \
    code_len = TINFL_FAST_LOOKUP_BITS; करो { अस्थायी = (pHuff)->m_वृक्ष[~अस्थायी + ((bit_buf >> code_len++) & 1)]; } जबतक (अस्थायी < 0); \
  } sym = अस्थायी; bit_buf >>= code_len; अंक_bits -= code_len; } MZ_MACRO_END

tinfl_status tinfl_decompress(tinfl_decompressor *r, स्थिर mz_uint8 *p_In_buf_अग्र, माप_प्रकार *p_In_buf_आकार, mz_uint8 *pOut_buf_start, mz_uint8 *p_Out_buf_अग्र, माप_प्रकार *p_Out_buf_आकार, स्थिर mz_uint32 decomp_flags)
{
  अटल स्थिर पूर्णांक s_लंबाई_base[31] = { 3,4,5,6,7,8,9,10,11,13, 15,17,19,23,27,31,35,43,51,59, 67,83,99,115,131,163,195,227,258,0,0 };
  अटल स्थिर पूर्णांक s_लंबाई_extra[31]= { 0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,0,0,0 };
  अटल स्थिर पूर्णांक s_dist_base[32] = { 1,2,3,4,5,7,9,13,17,25,33,49,65,97,129,193, 257,385,513,769,1025,1537,2049,3073,4097,6145,8193,12289,16385,24577,0,0};
  अटल स्थिर पूर्णांक s_dist_extra[32] = { 0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13};
  अटल स्थिर mz_uint8 s_लंबाई_dezigzag[19] = { 16,17,18,0,8,7,9,6,10,5,11,4,12,3,13,2,14,1,15 };
  अटल स्थिर पूर्णांक s_min_table_sizes[3] = { 257, 1, 4 };

  tinfl_status status = TINFL_STATUS_FAILED; mz_uint32 अंक_bits, dist, गणक, अंक_extra; tinfl_bit_buf_t bit_buf;
  स्थिर mz_uint8 *pIn_buf_cur = p_In_buf_अग्र, *स्थिर pIn_buf_end = p_In_buf_अग्र + *p_In_buf_आकार;
  mz_uint8 *pOut_buf_cur = p_Out_buf_अग्र, *स्थिर pOut_buf_end = p_Out_buf_अग्र + *p_Out_buf_आकार;
  माप_प्रकार out_buf_आकार_mask = (decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF) ? (माप_प्रकार)-1 : ((p_Out_buf_अग्र - pOut_buf_start) + *p_Out_buf_आकार) - 1, dist_from_out_buf_start;

  // Ensure the output buffer's size is a power of 2, unless the output buffer is large enough to hold the entire output file (in which case it doesn't matter).
  अगर (((out_buf_आकार_mask + 1) & out_buf_आकार_mask) || (p_Out_buf_अग्र < pOut_buf_start)) { *p_In_buf_आकार = *p_Out_buf_आकार = 0; वापस TINFL_STATUS_BAD_PARAM; }

  अंक_bits = r->m_अंक_bits; bit_buf = r->m_bit_buf; dist = r->m_dist; गणक = r->m_गणक; अंक_extra = r->m_अंक_extra; dist_from_out_buf_start = r->m_dist_from_out_buf_start;
  TINFL_CR_BEGIN

  bit_buf = अंक_bits = dist = गणक = अंक_extra = r->m_zhdr0 = r->m_zhdr1 = 0; r->m_z_adler32 = r->m_check_adler32 = 1;
  अगर (decomp_flags & TINFL_FLAG_PARSE_ZLIB_HEADER)
  {
    TINFL_GET_BYTE(1, r->m_zhdr0); TINFL_GET_BYTE(2, r->m_zhdr1);
    गणक = (((r->m_zhdr0 * 256 + r->m_zhdr1) % 31 != 0) || (r->m_zhdr1 & 32) || ((r->m_zhdr0 & 15) != 8));
    अगर (!(decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF)) गणक |= (((1U << (8U + (r->m_zhdr0 >> 4))) > 32768U) || ((out_buf_आकार_mask + 1) < (माप_प्रकार)(1U << (8U + (r->m_zhdr0 >> 4)))));
    अगर (गणक) { TINFL_CR_RETURN_FOREVER(36, TINFL_STATUS_FAILED); }
  }

  करो
  {
    TINFL_GET_BITS(3, r->m_final, 3); r->m_type = r->m_final >> 1;
    अगर (r->m_type == 0)
    {
      TINFL_SKIP_BITS(5, अंक_bits & 7);
      क्रम (गणक = 0; गणक < 4; ++गणक) { अगर (अंक_bits) TINFL_GET_BITS(6, r->m_raw_header[गणक], 8); अन्यथा TINFL_GET_BYTE(7, r->m_raw_header[गणक]); }
      अगर ((गणक = (r->m_raw_header[0] | (r->m_raw_header[1] << 8))) != (mz_uint)(0xFFFF ^ (r->m_raw_header[2] | (r->m_raw_header[3] << 8)))) { TINFL_CR_RETURN_FOREVER(39, TINFL_STATUS_FAILED); }
      जबतक ((गणक) && (अंक_bits))
      {
        TINFL_GET_BITS(51, dist, 8);
        जबतक (pOut_buf_cur >= pOut_buf_end) { TINFL_CR_RETURN(52, TINFL_STATUS_HAS_MORE_OUTPUT); }
        *pOut_buf_cur++ = (mz_uint8)dist;
        गणक--;
      }
      जबतक (गणक)
      {
        माप_प्रकार n; जबतक (pOut_buf_cur >= pOut_buf_end) { TINFL_CR_RETURN(9, TINFL_STATUS_HAS_MORE_OUTPUT); }
        जबतक (pIn_buf_cur >= pIn_buf_end)
        {
          अगर (decomp_flags & TINFL_FLAG_HAS_MORE_निवेश)
          {
            TINFL_CR_RETURN(38, TINFL_STATUS_NEEDS_MORE_निवेश);
          }
          अन्यथा
          {
            TINFL_CR_RETURN_FOREVER(40, TINFL_STATUS_FAILED);
          }
        }
        n = MZ_MIN(MZ_MIN((माप_प्रकार)(pOut_buf_end - pOut_buf_cur), (माप_प्रकार)(pIn_buf_end - pIn_buf_cur)), गणक);
        TINFL_MEMCPY(pOut_buf_cur, pIn_buf_cur, n); pIn_buf_cur += n; pOut_buf_cur += n; गणक -= (mz_uint)n;
      }
    }
    अन्यथा अगर (r->m_type == 3)
    {
      TINFL_CR_RETURN_FOREVER(10, TINFL_STATUS_FAILED);
    }
    अन्यथा
    {
      अगर (r->m_type == 1)
      {
        mz_uint8 *p = r->m_tables[0].m_code_आकार; mz_uint i;
        r->m_table_sizes[0] = 288; r->m_table_sizes[1] = 32; TINFL_MEMSET(r->m_tables[1].m_code_आकार, 5, 32);
        क्रम ( i = 0; i <= 143; ++i) *p++ = 8;
        क्रम ( ; i <= 255; ++i) *p++ = 9;
        क्रम ( ; i <= 279; ++i) *p++ = 7;
        क्रम ( ; i <= 287; ++i) *p++ = 8;
      }
      अन्यथा
      {
        क्रम (गणक = 0; गणक < 3; गणक++) { TINFL_GET_BITS(11, r->m_table_sizes[गणक], "\05\05\04"[गणक]); r->m_table_sizes[गणक] += s_min_table_sizes[गणक]; }
        MZ_CLEAR_ARR(r->m_tables[2].m_code_आकार); क्रम (गणक = 0; गणक < r->m_table_sizes[2]; गणक++) { mz_uint s; TINFL_GET_BITS(14, s, 3); r->m_tables[2].m_code_आकार[s_लंबाई_dezigzag[गणक]] = (mz_uint8)s; }
        r->m_table_sizes[2] = 19;
      }
      क्रम ( ; (पूर्णांक)r->m_type >= 0; r->m_type--)
      {
        पूर्णांक वृक्ष_अग्र, वृक्ष_cur; tinfl_huff_table *pTable;
        mz_uint i, j, used_syms, योग, sym_सूचकांक, अग्र_code[17], योग_syms[16]; pTable = &r->m_tables[r->m_type]; MZ_CLEAR_ARR(योग_syms); MZ_CLEAR_ARR(pTable->m_look_up); MZ_CLEAR_ARR(pTable->m_वृक्ष);
        क्रम (i = 0; i < r->m_table_sizes[r->m_type]; ++i) योग_syms[pTable->m_code_आकार[i]]++;
        used_syms = 0, योग = 0; अग्र_code[0] = अग्र_code[1] = 0;
        क्रम (i = 1; i <= 15; ++i) { used_syms += योग_syms[i]; अग्र_code[i + 1] = (योग = ((योग + योग_syms[i]) << 1)); }
        अगर ((65536 != योग) && (used_syms > 1))
        {
          TINFL_CR_RETURN_FOREVER(35, TINFL_STATUS_FAILED);
        }
        क्रम (वृक्ष_अग्र = -1, sym_सूचकांक = 0; sym_सूचकांक < r->m_table_sizes[r->m_type]; ++sym_सूचकांक)
        {
          mz_uint rev_code = 0, l, cur_code, code_आकार_2 = pTable->m_code_आकार[sym_सूचकांक]; अगर (!code_आकार_2) जारी;
          cur_code = अग्र_code[code_आकार_2]++; क्रम (l = code_आकार_2; l > 0; l--, cur_code >>= 1) rev_code = (rev_code << 1) | (cur_code & 1);
          अगर (code_आकार_2 <= TINFL_FAST_LOOKUP_BITS) { mz_int16 k = (mz_int16)((code_आकार_2 << 9) | sym_सूचकांक); जबतक (rev_code < TINFL_FAST_LOOKUP_आकार) { pTable->m_look_up[rev_code] = k; rev_code += (1 << code_आकार_2); } जारी; }
          अगर (0 == (वृक्ष_cur = pTable->m_look_up[rev_code & (TINFL_FAST_LOOKUP_आकार - 1)])) { pTable->m_look_up[rev_code & (TINFL_FAST_LOOKUP_आकार - 1)] = (mz_int16)वृक्ष_अग्र; वृक्ष_cur = वृक्ष_अग्र; वृक्ष_अग्र -= 2; }
          rev_code >>= (TINFL_FAST_LOOKUP_BITS - 1);
          क्रम (j = code_आकार_2; j > (TINFL_FAST_LOOKUP_BITS + 1); j--)
          {
            वृक्ष_cur -= ((rev_code >>= 1) & 1);
            अगर (!pTable->m_वृक्ष[-वृक्ष_cur - 1]) { pTable->m_वृक्ष[-वृक्ष_cur - 1] = (mz_int16)वृक्ष_अग्र; वृक्ष_cur = वृक्ष_अग्र; वृक्ष_अग्र -= 2; } अन्यथा वृक्ष_cur = pTable->m_वृक्ष[-वृक्ष_cur - 1];
          }
          वृक्ष_cur -= ((rev_code >>= 1) & 1); pTable->m_वृक्ष[-वृक्ष_cur - 1] = (mz_int16)sym_सूचकांक;
        }
        अगर (r->m_type == 2)
        {
          क्रम (गणक = 0; गणक < (r->m_table_sizes[0] + r->m_table_sizes[1]); )
          {
            mz_uint s; TINFL_HUFF_DECODE(16, dist, &r->m_tables[2]); अगर (dist < 16) { r->m_len_codes[गणक++] = (mz_uint8)dist; जारी; }
            अगर ((dist == 16) && (!गणक))
            {
              TINFL_CR_RETURN_FOREVER(17, TINFL_STATUS_FAILED);
            }
            अंक_extra = "\02\03\07"[dist - 16]; TINFL_GET_BITS(18, s, अंक_extra); s += "\03\03\013"[dist - 16];
            TINFL_MEMSET(r->m_len_codes + गणक, (dist == 16) ? r->m_len_codes[गणक - 1] : 0, s); गणक += s;
          }
          अगर ((r->m_table_sizes[0] + r->m_table_sizes[1]) != गणक)
          {
            TINFL_CR_RETURN_FOREVER(21, TINFL_STATUS_FAILED);
          }
          TINFL_MEMCPY(r->m_tables[0].m_code_आकार, r->m_len_codes, r->m_table_sizes[0]); TINFL_MEMCPY(r->m_tables[1].m_code_आकार, r->m_len_codes + r->m_table_sizes[0], r->m_table_sizes[1]);
        }
      }
      क्रम ( ; ; )
      {
        mz_uint8 *pSrc;
        क्रम ( ; ; )
        {
          अगर (((pIn_buf_end - pIn_buf_cur) < 4) || ((pOut_buf_end - pOut_buf_cur) < 2))
          {
            TINFL_HUFF_DECODE(23, गणक, &r->m_tables[0]);
            अगर (गणक >= 256)
              अवरोध;
            जबतक (pOut_buf_cur >= pOut_buf_end) { TINFL_CR_RETURN(24, TINFL_STATUS_HAS_MORE_OUTPUT); }
            *pOut_buf_cur++ = (mz_uint8)गणक;
          }
          अन्यथा
          {
            पूर्णांक sym2; mz_uint code_len;
#अगर TINFL_USE_64BIT_BITBUF
            अगर (अंक_bits < 30) { bit_buf |= (((tinfl_bit_buf_t)MZ_READ_LE32(pIn_buf_cur)) << अंक_bits); pIn_buf_cur += 4; अंक_bits += 32; }
#अन्यथा
            अगर (अंक_bits < 15) { bit_buf |= (((tinfl_bit_buf_t)MZ_READ_LE16(pIn_buf_cur)) << अंक_bits); pIn_buf_cur += 2; अंक_bits += 16; }
#पूर्ण_अगर
            अगर ((sym2 = r->m_tables[0].m_look_up[bit_buf & (TINFL_FAST_LOOKUP_आकार - 1)]) >= 0)
              code_len = sym2 >> 9;
            अन्यथा
            {
              code_len = TINFL_FAST_LOOKUP_BITS; करो { sym2 = r->m_tables[0].m_वृक्ष[~sym2 + ((bit_buf >> code_len++) & 1)]; } जबतक (sym2 < 0);
            }
            गणक = sym2; bit_buf >>= code_len; अंक_bits -= code_len;
            अगर (गणक & 256)
              अवरोध;

#अगर !TINFL_USE_64BIT_BITBUF
            अगर (अंक_bits < 15) { bit_buf |= (((tinfl_bit_buf_t)MZ_READ_LE16(pIn_buf_cur)) << अंक_bits); pIn_buf_cur += 2; अंक_bits += 16; }
#पूर्ण_अगर
            अगर ((sym2 = r->m_tables[0].m_look_up[bit_buf & (TINFL_FAST_LOOKUP_आकार - 1)]) >= 0)
              code_len = sym2 >> 9;
            अन्यथा
            {
              code_len = TINFL_FAST_LOOKUP_BITS; करो { sym2 = r->m_tables[0].m_वृक्ष[~sym2 + ((bit_buf >> code_len++) & 1)]; } जबतक (sym2 < 0);
            }
            bit_buf >>= code_len; अंक_bits -= code_len;

            pOut_buf_cur[0] = (mz_uint8)गणक;
            अगर (sym2 & 256)
            {
              pOut_buf_cur++;
              गणक = sym2;
              अवरोध;
            }
            pOut_buf_cur[1] = (mz_uint8)sym2;
            pOut_buf_cur += 2;
          }
        }
        अगर ((गणक &= 511) == 256) अवरोध;

        अंक_extra = s_लंबाई_extra[गणक - 257]; गणक = s_लंबाई_base[गणक - 257];
        अगर (अंक_extra) { mz_uint extra_bits; TINFL_GET_BITS(25, extra_bits, अंक_extra); गणक += extra_bits; }

        TINFL_HUFF_DECODE(26, dist, &r->m_tables[1]);
        अंक_extra = s_dist_extra[dist]; dist = s_dist_base[dist];
        अगर (अंक_extra) { mz_uint extra_bits; TINFL_GET_BITS(27, extra_bits, अंक_extra); dist += extra_bits; }

        dist_from_out_buf_start = pOut_buf_cur - pOut_buf_start;
        अगर ((dist > dist_from_out_buf_start) && (decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF))
        {
          TINFL_CR_RETURN_FOREVER(37, TINFL_STATUS_FAILED);
        }

        pSrc = pOut_buf_start + ((dist_from_out_buf_start - dist) & out_buf_आकार_mask);

        अगर ((MZ_MAX(pOut_buf_cur, pSrc) + गणक) > pOut_buf_end)
        {
          जबतक (गणक--)
          {
            जबतक (pOut_buf_cur >= pOut_buf_end) { TINFL_CR_RETURN(53, TINFL_STATUS_HAS_MORE_OUTPUT); }
            *pOut_buf_cur++ = pOut_buf_start[(dist_from_out_buf_start++ - dist) & out_buf_आकार_mask];
          }
          जारी;
        }
#अगर MINIZ_USE_UNALIGNED_LOADS_AND_STORES
        अन्यथा अगर ((गणक >= 9) && (गणक <= dist))
        {
          स्थिर mz_uint8 *pSrc_end = pSrc + (गणक & ~7);
          करो
          {
            ((mz_uint32 *)pOut_buf_cur)[0] = ((स्थिर mz_uint32 *)pSrc)[0];
            ((mz_uint32 *)pOut_buf_cur)[1] = ((स्थिर mz_uint32 *)pSrc)[1];
            pOut_buf_cur += 8;
          } जबतक ((pSrc += 8) < pSrc_end);
          अगर ((गणक &= 7) < 3)
          {
            अगर (गणक)
            {
              pOut_buf_cur[0] = pSrc[0];
              अगर (गणक > 1)
                pOut_buf_cur[1] = pSrc[1];
              pOut_buf_cur += गणक;
            }
            जारी;
          }
        }
#पूर्ण_अगर
        करो
        {
          pOut_buf_cur[0] = pSrc[0];
          pOut_buf_cur[1] = pSrc[1];
          pOut_buf_cur[2] = pSrc[2];
          pOut_buf_cur += 3; pSrc += 3;
        } जबतक ((पूर्णांक)(गणक -= 3) > 2);
        अगर ((पूर्णांक)गणक > 0)
        {
          pOut_buf_cur[0] = pSrc[0];
          अगर ((पूर्णांक)गणक > 1)
            pOut_buf_cur[1] = pSrc[1];
          pOut_buf_cur += गणक;
        }
      }
    }
  } जबतक (!(r->m_final & 1));
  अगर (decomp_flags & TINFL_FLAG_PARSE_ZLIB_HEADER)
  {
    TINFL_SKIP_BITS(32, अंक_bits & 7); क्रम (गणक = 0; गणक < 4; ++गणक) { mz_uint s; अगर (अंक_bits) TINFL_GET_BITS(41, s, 8); अन्यथा TINFL_GET_BYTE(42, s); r->m_z_adler32 = (r->m_z_adler32 << 8) | s; }
  }
  TINFL_CR_RETURN_FOREVER(34, TINFL_STATUS_DONE);
  TINFL_CR_FINISH

common_exit:
  r->m_अंक_bits = अंक_bits; r->m_bit_buf = bit_buf; r->m_dist = dist; r->m_गणक = गणक; r->m_अंक_extra = अंक_extra; r->m_dist_from_out_buf_start = dist_from_out_buf_start;
  *p_In_buf_आकार = pIn_buf_cur - p_In_buf_अग्र; *p_Out_buf_आकार = pOut_buf_cur - p_Out_buf_अग्र;
  अगर ((decomp_flags & (TINFL_FLAG_PARSE_ZLIB_HEADER | TINFL_FLAG_COMPUTE_ADLER32)) && (status >= 0))
  {
    स्थिर mz_uint8 *ptr = p_Out_buf_अग्र; माप_प्रकार buf_len = *p_Out_buf_आकार;
    mz_uint32 i, s1 = r->m_check_adler32 & 0xffff, s2 = r->m_check_adler32 >> 16; माप_प्रकार block_len = buf_len % 5552;
    जबतक (buf_len)
    {
      क्रम (i = 0; i + 7 < block_len; i += 8, ptr += 8)
      {
        s1 += ptr[0], s2 += s1; s1 += ptr[1], s2 += s1; s1 += ptr[2], s2 += s1; s1 += ptr[3], s2 += s1;
        s1 += ptr[4], s2 += s1; s1 += ptr[5], s2 += s1; s1 += ptr[6], s2 += s1; s1 += ptr[7], s2 += s1;
      }
      क्रम ( ; i < block_len; ++i) s1 += *ptr++, s2 += s1;
      s1 %= 65521U, s2 %= 65521U; buf_len -= block_len; block_len = 5552;
    }
    r->m_check_adler32 = (s2 << 16) + s1; अगर ((status == TINFL_STATUS_DONE) && (decomp_flags & TINFL_FLAG_PARSE_ZLIB_HEADER) && (r->m_check_adler32 != r->m_z_adler32)) status = TINFL_STATUS_ADLER32_MISMATCH;
  }
  वापस status;
}

// Higher level helper functions.
व्योम *tinfl_decompress_mem_to_heap(स्थिर व्योम *pSrc_buf, माप_प्रकार src_buf_len, माप_प्रकार *pOut_len, पूर्णांक flags)
{
  tinfl_decompressor decomp; व्योम *pBuf = शून्य, *pNew_buf; माप_प्रकार src_buf_ofs = 0, out_buf_capacity = 0;
  *pOut_len = 0;
  tinfl_init(&decomp);
  क्रम ( ; ; )
  {
    माप_प्रकार src_buf_आकार = src_buf_len - src_buf_ofs, dst_buf_आकार = out_buf_capacity - *pOut_len, new_out_buf_capacity;
    tinfl_status status = tinfl_decompress(&decomp, (स्थिर mz_uint8*)pSrc_buf + src_buf_ofs, &src_buf_आकार, (mz_uint8*)pBuf, pBuf ? (mz_uint8*)pBuf + *pOut_len : शून्य, &dst_buf_आकार,
      (flags & ~TINFL_FLAG_HAS_MORE_निवेश) | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF);
    अगर ((status < 0) || (status == TINFL_STATUS_NEEDS_MORE_निवेश))
    {
      MZ_FREE(pBuf); *pOut_len = 0; वापस शून्य;
    }
    src_buf_ofs += src_buf_आकार;
    *pOut_len += dst_buf_आकार;
    अगर (status == TINFL_STATUS_DONE) अवरोध;
    new_out_buf_capacity = out_buf_capacity * 2; अगर (new_out_buf_capacity < 128) new_out_buf_capacity = 128;
    pNew_buf = MZ_REALLOC(pBuf, new_out_buf_capacity);
    अगर (!pNew_buf)
    {
      MZ_FREE(pBuf); *pOut_len = 0; वापस शून्य;
    }
    pBuf = pNew_buf; out_buf_capacity = new_out_buf_capacity;
  }
  वापस pBuf;
}

माप_प्रकार tinfl_decompress_mem_to_mem(व्योम *pOut_buf, माप_प्रकार out_buf_len, स्थिर व्योम *pSrc_buf, माप_प्रकार src_buf_len, पूर्णांक flags)
{
  tinfl_decompressor decomp; tinfl_status status; tinfl_init(&decomp);
  status = tinfl_decompress(&decomp, (स्थिर mz_uint8*)pSrc_buf, &src_buf_len, (mz_uint8*)pOut_buf, (mz_uint8*)pOut_buf, &out_buf_len, (flags & ~TINFL_FLAG_HAS_MORE_निवेश) | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF);
  वापस (status != TINFL_STATUS_DONE) ? TINFL_DECOMPRESS_MEM_TO_MEM_FAILED : out_buf_len;
}

पूर्णांक tinfl_decompress_mem_to_callback(स्थिर व्योम *pIn_buf, माप_प्रकार *p_In_buf_आकार, tinfl_put_buf_func_ptr pPut_buf_func, व्योम *pPut_buf_user, पूर्णांक flags)
{
  पूर्णांक परिणाम = 0;
  tinfl_decompressor decomp;
  mz_uint8 *pDict = (mz_uint8*)MZ_MALLOC(TINFL_LZ_DICT_आकार); माप_प्रकार in_buf_ofs = 0, dict_ofs = 0;
  अगर (!pDict)
    वापस TINFL_STATUS_FAILED;
  स_रखो(pDict,0,TINFL_LZ_DICT_आकार);
  tinfl_init(&decomp);
  क्रम ( ; ; )
  {
    माप_प्रकार in_buf_आकार = *p_In_buf_आकार - in_buf_ofs, dst_buf_आकार = TINFL_LZ_DICT_आकार - dict_ofs;
    tinfl_status status = tinfl_decompress(&decomp, (स्थिर mz_uint8*)pIn_buf + in_buf_ofs, &in_buf_आकार, pDict, pDict + dict_ofs, &dst_buf_आकार,
      (flags & ~(TINFL_FLAG_HAS_MORE_निवेश | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF)));
    in_buf_ofs += in_buf_आकार;
    अगर ((dst_buf_आकार) && (!(*pPut_buf_func)(pDict + dict_ofs, (पूर्णांक)dst_buf_आकार, pPut_buf_user)))
      अवरोध;
    अगर (status != TINFL_STATUS_HAS_MORE_OUTPUT)
    {
      परिणाम = (status == TINFL_STATUS_DONE);
      अवरोध;
    }
    dict_ofs = (dict_ofs + dst_buf_आकार) & (TINFL_LZ_DICT_आकार - 1);
  }
  MZ_FREE(pDict);
  *p_In_buf_आकार = in_buf_ofs;
  वापस परिणाम;
}
#पूर्ण_अगर /*#ifndef MINIZ_NO_INFLATE_APIS*/

// ------------------- Low-level Compression (independent from all decompression API's)
#अगर_अघोषित MINIZ_NO_DEFLATE_APIS

// Purposely making these tables static for faster init and thread safety.
अटल स्थिर mz_uint16 s_tdefl_len_sym[256] = {
  257,258,259,260,261,262,263,264,265,265,266,266,267,267,268,268,269,269,269,269,270,270,270,270,271,271,271,271,272,272,272,272,
  273,273,273,273,273,273,273,273,274,274,274,274,274,274,274,274,275,275,275,275,275,275,275,275,276,276,276,276,276,276,276,276,
  277,277,277,277,277,277,277,277,277,277,277,277,277,277,277,277,278,278,278,278,278,278,278,278,278,278,278,278,278,278,278,278,
  279,279,279,279,279,279,279,279,279,279,279,279,279,279,279,279,280,280,280,280,280,280,280,280,280,280,280,280,280,280,280,280,
  281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,
  282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,
  283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,
  284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,285 };

अटल स्थिर mz_uint8 s_tdefl_len_extra[256] = {
  0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0 };

अटल स्थिर mz_uint8 s_tdefl_small_dist_sym[512] = {
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

अटल स्थिर mz_uint8 s_tdefl_small_dist_extra[512] = {
  0,0,0,0,1,1,1,1,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
  6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
  6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7 };

अटल स्थिर mz_uint8 s_tdefl_large_dist_sym[128] = {
  0,0,18,19,20,20,21,21,22,22,22,22,23,23,23,23,24,24,24,24,24,24,24,24,25,25,25,25,25,25,25,25,26,26,26,26,26,26,26,26,26,26,26,26,
  26,26,26,26,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,
  28,28,28,28,28,28,28,28,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29 };

अटल स्थिर mz_uint8 s_tdefl_large_dist_extra[128] = {
  0,0,8,8,9,9,9,9,10,10,10,10,10,10,10,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,
  12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
  13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13 };

// Radix sorts tdefl_sym_freq[] array by 16-bit key m_key. Returns ptr to sorted values.
प्रकार काष्ठा { mz_uint16 m_कुंजी, m_sym_सूचकांक; } tdefl_sym_freq;
अटल tdefl_sym_freq* tdefl_radix_sort_syms(mz_uint अंक_syms, tdefl_sym_freq* pSyms0, tdefl_sym_freq* pSyms1)
{
  mz_uint32 योग_passes = 2, pass_shift, pass, i, hist[256 * 2]; tdefl_sym_freq* pCur_syms = pSyms0, *pNew_syms = pSyms1; MZ_CLEAR_ARR(hist);
  क्रम (i = 0; i < अंक_syms; i++) { mz_uint freq = pSyms0[i].m_कुंजी; hist[freq & 0xFF]++; hist[256 + ((freq >> 8) & 0xFF)]++; }
  जबतक ((योग_passes > 1) && (अंक_syms == hist[(योग_passes - 1) * 256])) योग_passes--;
  क्रम (pass_shift = 0, pass = 0; pass < योग_passes; pass++, pass_shift += 8)
  {
    स्थिर mz_uint32* pHist = &hist[pass << 8];
    mz_uint offsets[256], cur_ofs = 0;
    क्रम (i = 0; i < 256; i++) { offsets[i] = cur_ofs; cur_ofs += pHist[i]; }
    क्रम (i = 0; i < अंक_syms; i++) pNew_syms[offsets[(pCur_syms[i].m_कुंजी >> pass_shift) & 0xFF]++] = pCur_syms[i];
    { tdefl_sym_freq* t = pCur_syms; pCur_syms = pNew_syms; pNew_syms = t; }
  }
  वापस pCur_syms;
}

// tdefl_calculate_minimum_redundancy() originally written by: Alistair Moffat, alistair@cs.mu.oz.au, Jyrki Katajainen, jyrki@diku.dk, November 1996.
अटल व्योम tdefl_calculate_minimum_redundancy(tdefl_sym_freq *A, पूर्णांक n)
{
  पूर्णांक मूल, leaf, अग्र, avbl, used, dpth;
  अगर (n==0) वापस; अन्यथा अगर (n==1) { A[0].m_कुंजी = 1; वापस; }
  A[0].m_कुंजी += A[1].m_कुंजी; मूल = 0; leaf = 2;
  क्रम (अग्र=1; अग्र < n-1; अग्र++)
  {
    अगर (leaf>=n || A[मूल].m_कुंजी<A[leaf].m_कुंजी) { A[अग्र].m_कुंजी = A[मूल].m_कुंजी; A[मूल++].m_कुंजी = (mz_uint16)अग्र; } अन्यथा A[अग्र].m_कुंजी = A[leaf++].m_कुंजी;
    अगर (leaf>=n || (मूल<अग्र && A[मूल].m_कुंजी<A[leaf].m_कुंजी)) { A[अग्र].m_कुंजी = (mz_uint16)(A[अग्र].m_कुंजी + A[मूल].m_कुंजी); A[मूल++].m_कुंजी = (mz_uint16)अग्र; } अन्यथा A[अग्र].m_कुंजी = (mz_uint16)(A[अग्र].m_कुंजी + A[leaf++].m_कुंजी);
  }
  A[n-2].m_कुंजी = 0; क्रम (अग्र=n-3; अग्र>=0; अग्र--) A[अग्र].m_कुंजी = A[A[अग्र].m_कुंजी].m_कुंजी+1;
  avbl = 1; used = dpth = 0; मूल = n-2; अग्र = n-1;
  जबतक (avbl>0)
  {
    जबतक (मूल>=0 && (पूर्णांक)A[मूल].m_कुंजी==dpth) { used++; मूल--; }
    जबतक (avbl>used) { A[अग्र--].m_कुंजी = (mz_uint16)(dpth); avbl--; }
    avbl = 2*used; dpth++; used = 0;
  }
}

// Limits canonical Huffman code table's max code size.
क्रमागत { TDEFL_MAX_SUPPORTED_HUFF_CODESIZE = 32 };
अटल व्योम tdefl_huffman_enforce_max_code_आकार(पूर्णांक *p_अंक_codes, पूर्णांक code_list_len, पूर्णांक max_code_आकार)
{
  पूर्णांक i; mz_uint32 योग = 0; अगर (code_list_len <= 1) वापस;
  क्रम (i = max_code_आकार + 1; i <= TDEFL_MAX_SUPPORTED_HUFF_CODESIZE; i++) p_अंक_codes[max_code_आकार] += p_अंक_codes[i];
  क्रम (i = max_code_आकार; i > 0; i--) योग += (((mz_uint32)p_अंक_codes[i]) << (max_code_आकार - i));
  जबतक (योग != (1UL << max_code_आकार))
  {
    p_अंक_codes[max_code_आकार]--;
    क्रम (i = max_code_आकार - 1; i > 0; i--) अगर (p_अंक_codes[i]) { p_अंक_codes[i]--; p_अंक_codes[i + 1] += 2; अवरोध; }
    योग--;
  }
}

अटल व्योम tdefl_optimize_huffman_table(tdefl_compressor *d, पूर्णांक table_अंक, पूर्णांक table_len, पूर्णांक code_आकार_limit, पूर्णांक static_table)
{
  पूर्णांक i, j, l, अंक_codes[1 + TDEFL_MAX_SUPPORTED_HUFF_CODESIZE]; mz_uint अग्र_code[TDEFL_MAX_SUPPORTED_HUFF_CODESIZE + 1]; MZ_CLEAR_ARR(अंक_codes);
  अगर (static_table)
  {
    क्रम (i = 0; i < table_len; i++) अंक_codes[d->m_huff_code_sizes[table_अंक][i]]++;
  }
  अन्यथा
  {
    tdefl_sym_freq syms0[TDEFL_MAX_HUFF_SYMBOLS], syms1[TDEFL_MAX_HUFF_SYMBOLS], *pSyms;
    पूर्णांक अंक_used_syms = 0;
    स्थिर mz_uint16 *p_Sym_गिनती = &d->m_huff_गिनती[table_अंक][0];
    क्रम (i = 0; i < table_len; i++) अगर (p_Sym_गिनती[i]) { syms0[अंक_used_syms].m_कुंजी = (mz_uint16)p_Sym_गिनती[i]; syms0[अंक_used_syms++].m_sym_सूचकांक = (mz_uint16)i; }

    pSyms = tdefl_radix_sort_syms(अंक_used_syms, syms0, syms1); tdefl_calculate_minimum_redundancy(pSyms, अंक_used_syms);

    क्रम (i = 0; i < अंक_used_syms; i++) अंक_codes[pSyms[i].m_कुंजी]++;

    tdefl_huffman_enforce_max_code_आकार(अंक_codes, अंक_used_syms, code_आकार_limit);

    MZ_CLEAR_ARR(d->m_huff_code_sizes[table_अंक]); MZ_CLEAR_ARR(d->m_huff_codes[table_अंक]);
    क्रम (i = 1, j = अंक_used_syms; i <= code_आकार_limit; i++)
      क्रम (l = अंक_codes[i]; l > 0; l--) d->m_huff_code_sizes[table_अंक][pSyms[--j].m_sym_सूचकांक] = (mz_uint8)(i);
  }

  अग्र_code[1] = 0; क्रम (j = 0, i = 2; i <= code_आकार_limit; i++) अग्र_code[i] = j = ((j + अंक_codes[i - 1]) << 1);

  क्रम (i = 0; i < table_len; i++)
  {
    mz_uint rev_code = 0, code, code_आकार_2; अगर ((code_आकार_2 = d->m_huff_code_sizes[table_अंक][i]) == 0) जारी;
    code = अग्र_code[code_आकार_2]++; क्रम (l = code_आकार_2; l > 0; l--, code >>= 1) rev_code = (rev_code << 1) | (code & 1);
    d->m_huff_codes[table_अंक][i] = (mz_uint16)rev_code;
  }
}

#घोषणा TDEFL_PUT_BITS(b, l) करो { \
  mz_uint bits = b; mz_uint len = l; MZ_ASSERT(bits <= ((1U << len) - 1U)); \
  d->m_bit_बफर |= (bits << d->m_bits_in); d->m_bits_in += len; \
  जबतक (d->m_bits_in >= 8) { \
    अगर (d->m_pOutput_buf < d->m_pOutput_buf_end) \
      *d->m_pOutput_buf++ = (mz_uint8)(d->m_bit_बफर); \
    d->m_bit_बफर >>= 8; \
    d->m_bits_in -= 8; \
  } \
} MZ_MACRO_END

#घोषणा TDEFL_RLE_पूर्व_CODE_आकार() करो { \
  अगर (rle_repeat_गिनती) { \
    अगर (rle_repeat_गिनती < 3) { \
      d->m_huff_गिनती[2][पूर्व_code_आकार] = (mz_uint16)(d->m_huff_गिनती[2][पूर्व_code_आकार] + rle_repeat_गिनती); \
      जबतक (rle_repeat_गिनती--) packed_code_sizes[अंक_packed_code_sizes++] = पूर्व_code_आकार; \
    } अन्यथा { \
      d->m_huff_गिनती[2][16] = (mz_uint16)(d->m_huff_गिनती[2][16] + 1); packed_code_sizes[अंक_packed_code_sizes++] = 16; packed_code_sizes[अंक_packed_code_sizes++] = (mz_uint8)(rle_repeat_गिनती - 3); \
  } rle_repeat_गिनती = 0; } \
} MZ_MACRO_END

#घोषणा TDEFL_RLE_ZERO_CODE_आकार() करो { \
  अगर (rle_z_गिनती) { \
    अगर (rle_z_गिनती < 3) { \
      d->m_huff_गिनती[2][0] = (mz_uint16)(d->m_huff_गिनती[2][0] + rle_z_गिनती); जबतक (rle_z_गिनती--) packed_code_sizes[अंक_packed_code_sizes++] = 0; \
    } अन्यथा अगर (rle_z_गिनती <= 10) { \
      d->m_huff_गिनती[2][17] = (mz_uint16)(d->m_huff_गिनती[2][17] + 1); packed_code_sizes[अंक_packed_code_sizes++] = 17; packed_code_sizes[अंक_packed_code_sizes++] = (mz_uint8)(rle_z_गिनती - 3); \
    } अन्यथा { \
      d->m_huff_गिनती[2][18] = (mz_uint16)(d->m_huff_गिनती[2][18] + 1); packed_code_sizes[अंक_packed_code_sizes++] = 18; packed_code_sizes[अंक_packed_code_sizes++] = (mz_uint8)(rle_z_गिनती - 11); \
  } rle_z_गिनती = 0; } \
} MZ_MACRO_END

अटल mz_uint8 s_tdefl_packed_code_आकार_syms_swizzle[] = { 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 };

अटल व्योम tdefl_start_dynamic_block(tdefl_compressor *d)
{
  पूर्णांक अंक_lit_codes, अंक_dist_codes, अंक_bit_lengths; mz_uint i, योग_code_sizes_to_pack, अंक_packed_code_sizes, rle_z_गिनती, rle_repeat_गिनती, packed_code_sizes_सूचकांक;
  mz_uint8 code_sizes_to_pack[TDEFL_MAX_HUFF_SYMBOLS_0 + TDEFL_MAX_HUFF_SYMBOLS_1], packed_code_sizes[TDEFL_MAX_HUFF_SYMBOLS_0 + TDEFL_MAX_HUFF_SYMBOLS_1], पूर्व_code_आकार = 0xFF;

  d->m_huff_गिनती[0][256] = 1;

  tdefl_optimize_huffman_table(d, 0, TDEFL_MAX_HUFF_SYMBOLS_0, 15, MZ_FALSE);
  tdefl_optimize_huffman_table(d, 1, TDEFL_MAX_HUFF_SYMBOLS_1, 15, MZ_FALSE);

  क्रम (अंक_lit_codes = 286; अंक_lit_codes > 257; अंक_lit_codes--) अगर (d->m_huff_code_sizes[0][अंक_lit_codes - 1]) अवरोध;
  क्रम (अंक_dist_codes = 30; अंक_dist_codes > 1; अंक_dist_codes--) अगर (d->m_huff_code_sizes[1][अंक_dist_codes - 1]) अवरोध;

  स_नकल(code_sizes_to_pack, &d->m_huff_code_sizes[0][0], अंक_lit_codes);
  स_नकल(code_sizes_to_pack + अंक_lit_codes, &d->m_huff_code_sizes[1][0], अंक_dist_codes);
  योग_code_sizes_to_pack = अंक_lit_codes + अंक_dist_codes; अंक_packed_code_sizes = 0; rle_z_गिनती = 0; rle_repeat_गिनती = 0;

  स_रखो(&d->m_huff_गिनती[2][0], 0, माप(d->m_huff_गिनती[2][0]) * TDEFL_MAX_HUFF_SYMBOLS_2);
  क्रम (i = 0; i < योग_code_sizes_to_pack; i++)
  {
    mz_uint8 code_आकार_2 = code_sizes_to_pack[i];
    अगर (!code_आकार_2)
    {
      TDEFL_RLE_पूर्व_CODE_आकार();
      अगर (++rle_z_गिनती == 138) { TDEFL_RLE_ZERO_CODE_आकार(); }
    }
    अन्यथा
    {
      TDEFL_RLE_ZERO_CODE_आकार();
      अगर (code_आकार_2 != पूर्व_code_आकार)
      {
        TDEFL_RLE_पूर्व_CODE_आकार();
        d->m_huff_गिनती[2][code_आकार_2] = (mz_uint16)(d->m_huff_गिनती[2][code_आकार_2] + 1); packed_code_sizes[अंक_packed_code_sizes++] = code_आकार_2;
      }
      अन्यथा अगर (++rle_repeat_गिनती == 6)
      {
        TDEFL_RLE_पूर्व_CODE_आकार();
      }
    }
    पूर्व_code_आकार = code_आकार_2;
  }
  अगर (rle_repeat_गिनती) { TDEFL_RLE_पूर्व_CODE_आकार(); } अन्यथा { TDEFL_RLE_ZERO_CODE_आकार(); }

  tdefl_optimize_huffman_table(d, 2, TDEFL_MAX_HUFF_SYMBOLS_2, 7, MZ_FALSE);

  TDEFL_PUT_BITS(2, 2);

  TDEFL_PUT_BITS(अंक_lit_codes - 257, 5);
  TDEFL_PUT_BITS(अंक_dist_codes - 1, 5);

  क्रम (अंक_bit_lengths = 18; अंक_bit_lengths >= 0; अंक_bit_lengths--) अगर (d->m_huff_code_sizes[2][s_tdefl_packed_code_आकार_syms_swizzle[अंक_bit_lengths]]) अवरोध;
  अंक_bit_lengths = MZ_MAX(4, (अंक_bit_lengths + 1)); TDEFL_PUT_BITS(अंक_bit_lengths - 4, 4);
  क्रम (i = 0; (पूर्णांक)i < अंक_bit_lengths; i++) TDEFL_PUT_BITS(d->m_huff_code_sizes[2][s_tdefl_packed_code_आकार_syms_swizzle[i]], 3);

  क्रम (packed_code_sizes_सूचकांक = 0; packed_code_sizes_सूचकांक < अंक_packed_code_sizes; )
  {
    mz_uint code = packed_code_sizes[packed_code_sizes_सूचकांक++]; MZ_ASSERT(code < TDEFL_MAX_HUFF_SYMBOLS_2);
    TDEFL_PUT_BITS(d->m_huff_codes[2][code], d->m_huff_code_sizes[2][code]);
    अगर (code >= 16) TDEFL_PUT_BITS(packed_code_sizes[packed_code_sizes_सूचकांक++], "\02\03\07"[code - 16]);
  }
}

अटल व्योम tdefl_start_static_block(tdefl_compressor *d)
{
  mz_uint i;
  mz_uint8 *p = &d->m_huff_code_sizes[0][0];

  क्रम (i = 0; i <= 143; ++i) *p++ = 8;
  क्रम ( ; i <= 255; ++i) *p++ = 9;
  क्रम ( ; i <= 279; ++i) *p++ = 7;
  क्रम ( ; i <= 287; ++i) *p++ = 8;

  स_रखो(d->m_huff_code_sizes[1], 5, 32);

  tdefl_optimize_huffman_table(d, 0, 288, 15, MZ_TRUE);
  tdefl_optimize_huffman_table(d, 1, 32, 15, MZ_TRUE);

  TDEFL_PUT_BITS(1, 2);
}

अटल स्थिर mz_uint mz_bitmasks[17] = { 0x0000, 0x0001, 0x0003, 0x0007, 0x000F, 0x001F, 0x003F, 0x007F, 0x00FF, 0x01FF, 0x03FF, 0x07FF, 0x0FFF, 0x1FFF, 0x3FFF, 0x7FFF, 0xFFFF };

#अगर MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN && MINIZ_HAS_64BIT_REGISTERS
अटल mz_bool tdefl_compress_lz_codes(tdefl_compressor *d)
{
  mz_uint flags;
  mz_uint8 *pLZ_codes;
  mz_uint8 *pOutput_buf = d->m_pOutput_buf;
  mz_uint8 *pLZ_code_buf_end = d->m_pLZ_code_buf;
  mz_uint64 bit_बफर = d->m_bit_बफर;
  mz_uint bits_in = d->m_bits_in;

#घोषणा TDEFL_PUT_BITS_FAST(b, l) { bit_बफर |= (((mz_uint64)(b)) << bits_in); bits_in += (l); }

  flags = 1;
  क्रम (pLZ_codes = d->m_lz_code_buf; pLZ_codes < pLZ_code_buf_end; flags >>= 1)
  {
    अगर (flags == 1)
      flags = *pLZ_codes++ | 0x100;

    अगर (flags & 1)
    {
      mz_uint s0, s1, n0, n1, sym, अंक_extra_bits;
      mz_uint match_len = pLZ_codes[0], match_dist = *(स्थिर mz_uint16 *)(pLZ_codes + 1); pLZ_codes += 3;

      MZ_ASSERT(d->m_huff_code_sizes[0][s_tdefl_len_sym[match_len]]);
      TDEFL_PUT_BITS_FAST(d->m_huff_codes[0][s_tdefl_len_sym[match_len]], d->m_huff_code_sizes[0][s_tdefl_len_sym[match_len]]);
      TDEFL_PUT_BITS_FAST(match_len & mz_bitmasks[s_tdefl_len_extra[match_len]], s_tdefl_len_extra[match_len]);

      // This sequence coaxes MSVC into using cmov's vs. jmp's.
      s0 = s_tdefl_small_dist_sym[match_dist & 511];
      n0 = s_tdefl_small_dist_extra[match_dist & 511];
      s1 = s_tdefl_large_dist_sym[match_dist >> 8];
      n1 = s_tdefl_large_dist_extra[match_dist >> 8];
      sym = (match_dist < 512) ? s0 : s1;
      अंक_extra_bits = (match_dist < 512) ? n0 : n1;

      MZ_ASSERT(d->m_huff_code_sizes[1][sym]);
      TDEFL_PUT_BITS_FAST(d->m_huff_codes[1][sym], d->m_huff_code_sizes[1][sym]);
      TDEFL_PUT_BITS_FAST(match_dist & mz_bitmasks[अंक_extra_bits], अंक_extra_bits);
    }
    अन्यथा
    {
      mz_uint lit = *pLZ_codes++;
      MZ_ASSERT(d->m_huff_code_sizes[0][lit]);
      TDEFL_PUT_BITS_FAST(d->m_huff_codes[0][lit], d->m_huff_code_sizes[0][lit]);

      अगर (((flags & 2) == 0) && (pLZ_codes < pLZ_code_buf_end))
      {
        flags >>= 1;
        lit = *pLZ_codes++;
        MZ_ASSERT(d->m_huff_code_sizes[0][lit]);
        TDEFL_PUT_BITS_FAST(d->m_huff_codes[0][lit], d->m_huff_code_sizes[0][lit]);

        अगर (((flags & 2) == 0) && (pLZ_codes < pLZ_code_buf_end))
        {
          flags >>= 1;
          lit = *pLZ_codes++;
          MZ_ASSERT(d->m_huff_code_sizes[0][lit]);
          TDEFL_PUT_BITS_FAST(d->m_huff_codes[0][lit], d->m_huff_code_sizes[0][lit]);
        }
      }
    }

    अगर (pOutput_buf >= d->m_pOutput_buf_end)
      वापस MZ_FALSE;

    *(mz_uint64*)pOutput_buf = bit_बफर;
    pOutput_buf += (bits_in >> 3);
    bit_बफर >>= (bits_in & ~7);
    bits_in &= 7;
  }

#अघोषित TDEFL_PUT_BITS_FAST

  d->m_pOutput_buf = pOutput_buf;
  d->m_bits_in = 0;
  d->m_bit_बफर = 0;

  जबतक (bits_in)
  {
    mz_uint32 n = MZ_MIN(bits_in, 16);
    TDEFL_PUT_BITS((mz_uint)bit_बफर & mz_bitmasks[n], n);
    bit_बफर >>= n;
    bits_in -= n;
  }

  TDEFL_PUT_BITS(d->m_huff_codes[0][256], d->m_huff_code_sizes[0][256]);

  वापस (d->m_pOutput_buf < d->m_pOutput_buf_end);
}
#अन्यथा
अटल mz_bool tdefl_compress_lz_codes(tdefl_compressor *d)
{
  mz_uint flags;
  mz_uint8 *pLZ_codes;

  flags = 1;
  क्रम (pLZ_codes = d->m_lz_code_buf; pLZ_codes < d->m_pLZ_code_buf; flags >>= 1)
  {
    अगर (flags == 1)
      flags = *pLZ_codes++ | 0x100;
    अगर (flags & 1)
    {
      mz_uint sym, अंक_extra_bits;
      mz_uint match_len = pLZ_codes[0], match_dist = (pLZ_codes[1] | (pLZ_codes[2] << 8)); pLZ_codes += 3;

      MZ_ASSERT(d->m_huff_code_sizes[0][s_tdefl_len_sym[match_len]]);
      TDEFL_PUT_BITS(d->m_huff_codes[0][s_tdefl_len_sym[match_len]], d->m_huff_code_sizes[0][s_tdefl_len_sym[match_len]]);
      TDEFL_PUT_BITS(match_len & mz_bitmasks[s_tdefl_len_extra[match_len]], s_tdefl_len_extra[match_len]);

      अगर (match_dist < 512)
      {
        sym = s_tdefl_small_dist_sym[match_dist]; अंक_extra_bits = s_tdefl_small_dist_extra[match_dist];
      }
      अन्यथा
      {
        sym = s_tdefl_large_dist_sym[match_dist >> 8]; अंक_extra_bits = s_tdefl_large_dist_extra[match_dist >> 8];
      }
      MZ_ASSERT(d->m_huff_code_sizes[1][sym]);
      TDEFL_PUT_BITS(d->m_huff_codes[1][sym], d->m_huff_code_sizes[1][sym]);
      TDEFL_PUT_BITS(match_dist & mz_bitmasks[अंक_extra_bits], अंक_extra_bits);
    }
    अन्यथा
    {
      mz_uint lit = *pLZ_codes++;
      MZ_ASSERT(d->m_huff_code_sizes[0][lit]);
      TDEFL_PUT_BITS(d->m_huff_codes[0][lit], d->m_huff_code_sizes[0][lit]);
    }
  }

  TDEFL_PUT_BITS(d->m_huff_codes[0][256], d->m_huff_code_sizes[0][256]);

  वापस (d->m_pOutput_buf < d->m_pOutput_buf_end);
}
#पूर्ण_अगर // MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN && MINIZ_HAS_64BIT_REGISTERS

अटल mz_bool tdefl_compress_block(tdefl_compressor *d, mz_bool static_block)
{
  अगर (static_block)
    tdefl_start_static_block(d);
  अन्यथा
    tdefl_start_dynamic_block(d);
  वापस tdefl_compress_lz_codes(d);
}

अटल पूर्णांक tdefl_flush_block(tdefl_compressor *d, पूर्णांक flush)
{
  mz_uint saved_bit_buf, saved_bits_in;
  mz_uint8 *pSaved_output_buf;
  mz_bool comp_block_succeeded = MZ_FALSE;
  पूर्णांक n, use_raw_block = ((d->m_flags & TDEFL_FORCE_ALL_RAW_BLOCKS) != 0) && (d->m_lookahead_pos - d->m_lz_code_buf_dict_pos) <= d->m_dict_आकार;
  mz_uint8 *pOutput_buf_start = ((d->m_pPut_buf_func == शून्य) && ((*d->m_p_Out_buf_आकार - d->m_out_buf_ofs) >= TDEFL_OUT_BUF_आकार)) ? ((mz_uint8 *)d->m_pOut_buf + d->m_out_buf_ofs) : d->m_output_buf;

  d->m_pOutput_buf = pOutput_buf_start;
  d->m_pOutput_buf_end = d->m_pOutput_buf + TDEFL_OUT_BUF_आकार - 16;

  MZ_ASSERT(!d->m_output_flush_remaining);
  d->m_output_flush_ofs = 0;
  d->m_output_flush_remaining = 0;

  *d->m_pLZ_flags = (mz_uint8)(*d->m_pLZ_flags >> d->m_अंक_flags_बायाँ);
  d->m_pLZ_code_buf -= (d->m_अंक_flags_बायाँ == 8);

  अगर ((d->m_flags & TDEFL_WRITE_ZLIB_HEADER) && (!d->m_block_सूचकांक))
  {
    TDEFL_PUT_BITS(0x78, 8); TDEFL_PUT_BITS(0x01, 8);
  }

  TDEFL_PUT_BITS(flush == TDEFL_FINISH, 1);

  pSaved_output_buf = d->m_pOutput_buf; saved_bit_buf = d->m_bit_बफर; saved_bits_in = d->m_bits_in;

  अगर (!use_raw_block)
    comp_block_succeeded = tdefl_compress_block(d, (d->m_flags & TDEFL_FORCE_ALL_STATIC_BLOCKS) || (d->m_योग_lz_bytes < 48));

  // If the block gets expanded, forget the current contents of the output buffer and send a raw block instead.
  अगर ( ((use_raw_block) || ((d->m_योग_lz_bytes) && ((d->m_pOutput_buf - pSaved_output_buf + 1U) >= d->m_योग_lz_bytes))) &&
       ((d->m_lookahead_pos - d->m_lz_code_buf_dict_pos) <= d->m_dict_आकार) )
  {
    mz_uint i; d->m_pOutput_buf = pSaved_output_buf; d->m_bit_बफर = saved_bit_buf; d->m_bits_in = saved_bits_in;
    TDEFL_PUT_BITS(0, 2);
    अगर (d->m_bits_in) { TDEFL_PUT_BITS(0, 8 - d->m_bits_in); }
    क्रम (i = 2; i; --i, d->m_योग_lz_bytes ^= 0xFFFF)
    {
      TDEFL_PUT_BITS(d->m_योग_lz_bytes & 0xFFFF, 16);
    }
    क्रम (i = 0; i < d->m_योग_lz_bytes; ++i)
    {
      TDEFL_PUT_BITS(d->m_dict[(d->m_lz_code_buf_dict_pos + i) & TDEFL_LZ_DICT_आकार_MASK], 8);
    }
  }
  // Check for the extremely unlikely (if not impossible) case of the compressed block not fitting into the output buffer when using dynamic codes.
  अन्यथा अगर (!comp_block_succeeded)
  {
    d->m_pOutput_buf = pSaved_output_buf; d->m_bit_बफर = saved_bit_buf; d->m_bits_in = saved_bits_in;
    tdefl_compress_block(d, MZ_TRUE);
  }

  अगर (flush)
  {
    अगर (flush == TDEFL_FINISH)
    {
      अगर (d->m_bits_in) { TDEFL_PUT_BITS(0, 8 - d->m_bits_in); }
      अगर (d->m_flags & TDEFL_WRITE_ZLIB_HEADER) { mz_uint i, a = d->m_adler32; क्रम (i = 0; i < 4; i++) { TDEFL_PUT_BITS((a >> 24) & 0xFF, 8); a <<= 8; } }
    }
    अन्यथा
    {
      mz_uint i, z = 0; TDEFL_PUT_BITS(0, 3); अगर (d->m_bits_in) { TDEFL_PUT_BITS(0, 8 - d->m_bits_in); } क्रम (i = 2; i; --i, z ^= 0xFFFF) { TDEFL_PUT_BITS(z & 0xFFFF, 16); }
    }
  }

  MZ_ASSERT(d->m_pOutput_buf < d->m_pOutput_buf_end);

  स_रखो(&d->m_huff_गिनती[0][0], 0, माप(d->m_huff_गिनती[0][0]) * TDEFL_MAX_HUFF_SYMBOLS_0);
  स_रखो(&d->m_huff_गिनती[1][0], 0, माप(d->m_huff_गिनती[1][0]) * TDEFL_MAX_HUFF_SYMBOLS_1);

  d->m_pLZ_code_buf = d->m_lz_code_buf + 1; d->m_pLZ_flags = d->m_lz_code_buf; d->m_अंक_flags_बायाँ = 8; d->m_lz_code_buf_dict_pos += d->m_योग_lz_bytes; d->m_योग_lz_bytes = 0; d->m_block_सूचकांक++;

  अगर ((n = (पूर्णांक)(d->m_pOutput_buf - pOutput_buf_start)) != 0)
  {
    अगर (d->m_pPut_buf_func)
    {
      *d->m_p_In_buf_आकार = d->m_pSrc - (स्थिर mz_uint8 *)d->m_pIn_buf;
      अगर (!(*d->m_pPut_buf_func)(d->m_output_buf, n, d->m_pPut_buf_user))
        वापस (d->m_पूर्व_return_status = TDEFL_STATUS_PUT_BUF_FAILED);
    }
    अन्यथा अगर (pOutput_buf_start == d->m_output_buf)
    {
      पूर्णांक bytes_to_copy = (पूर्णांक)MZ_MIN((माप_प्रकार)n, (माप_प्रकार)(*d->m_p_Out_buf_आकार - d->m_out_buf_ofs));
      स_नकल((mz_uint8 *)d->m_pOut_buf + d->m_out_buf_ofs, d->m_output_buf, bytes_to_copy);
      d->m_out_buf_ofs += bytes_to_copy;
      अगर ((n -= bytes_to_copy) != 0)
      {
        d->m_output_flush_ofs = bytes_to_copy;
        d->m_output_flush_remaining = n;
      }
    }
    अन्यथा
    {
      d->m_out_buf_ofs += n;
    }
  }

  वापस d->m_output_flush_remaining;
}

#अगर MINIZ_USE_UNALIGNED_LOADS_AND_STORES
#घोषणा TDEFL_READ_UNALIGNED_WORD(p) *(स्थिर mz_uint16*)(p)
अटल MZ_FORCEINLINE व्योम tdefl_find_match(tdefl_compressor *d, mz_uint lookahead_pos, mz_uint max_dist, mz_uint max_match_len, mz_uint *pMatch_dist, mz_uint *pMatch_len)
{
  mz_uint dist, pos = lookahead_pos & TDEFL_LZ_DICT_आकार_MASK, match_len = *pMatch_len, probe_pos = pos, अग्र_probe_pos, probe_len;
  mz_uint अंक_probes_बायाँ = d->m_max_probes[match_len >= 32];
  स्थिर mz_uint16 *s = (स्थिर mz_uint16*)(d->m_dict + pos), *p, *q;
  mz_uint16 c01 = TDEFL_READ_UNALIGNED_WORD(&d->m_dict[pos + match_len - 1]), s01 = TDEFL_READ_UNALIGNED_WORD(s);
  MZ_ASSERT(max_match_len <= TDEFL_MAX_MATCH_LEN); अगर (max_match_len <= match_len) वापस;
  क्रम ( ; ; )
  {
    क्रम ( ; ; )
    {
      अगर (--अंक_probes_बायाँ == 0) वापस;
      #घोषणा TDEFL_PROBE \
        अग्र_probe_pos = d->m_अग्र[probe_pos]; \
        अगर ((!अग्र_probe_pos) || ((dist = (mz_uint16)(lookahead_pos - अग्र_probe_pos)) > max_dist)) वापस; \
        probe_pos = अग्र_probe_pos & TDEFL_LZ_DICT_आकार_MASK; \
        अगर (TDEFL_READ_UNALIGNED_WORD(&d->m_dict[probe_pos + match_len - 1]) == c01) अवरोध;
      TDEFL_PROBE
      TDEFL_PROBE
      TDEFL_PROBE
    }
    अगर (!dist) अवरोध;
    q = (स्थिर mz_uint16*)(d->m_dict + probe_pos);
    अगर (TDEFL_READ_UNALIGNED_WORD(q) != s01) जारी;
    p = s; probe_len = 32;
    करो { } जबतक ( (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) && (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) &&
                   (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) && (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) && (--probe_len > 0) );
    अगर (!probe_len)
    {
      *pMatch_dist = dist; *pMatch_len = MZ_MIN(max_match_len, TDEFL_MAX_MATCH_LEN); अवरोध;
    }
    अन्यथा अगर ((probe_len = ((mz_uint)(p - s) * 2) + (mz_uint)(*(स्थिर mz_uint8*)p == *(स्थिर mz_uint8*)q)) > match_len)
    {
      *pMatch_dist = dist; अगर ((*pMatch_len = match_len = MZ_MIN(max_match_len, probe_len)) == max_match_len) अवरोध;
      c01 = TDEFL_READ_UNALIGNED_WORD(&d->m_dict[pos + match_len - 1]);
    }
  }
}
#अन्यथा
अटल MZ_FORCEINLINE व्योम tdefl_find_match(tdefl_compressor *d, mz_uint lookahead_pos, mz_uint max_dist, mz_uint max_match_len, mz_uint *pMatch_dist, mz_uint *pMatch_len)
{
  mz_uint dist, pos = lookahead_pos & TDEFL_LZ_DICT_आकार_MASK, match_len = *pMatch_len, probe_pos = pos, अग्र_probe_pos, probe_len;
  mz_uint अंक_probes_बायाँ = d->m_max_probes[match_len >= 32];
  स्थिर mz_uint8 *s = d->m_dict + pos, *p, *q;
  mz_uint8 c0 = d->m_dict[pos + match_len], c1 = d->m_dict[pos + match_len - 1];
  MZ_ASSERT(max_match_len <= TDEFL_MAX_MATCH_LEN); अगर (max_match_len <= match_len) वापस;
  क्रम ( ; ; )
  {
    क्रम ( ; ; )
    {
      अगर (--अंक_probes_बायाँ == 0) वापस;
      #घोषणा TDEFL_PROBE \
        अग्र_probe_pos = d->m_अग्र[probe_pos]; \
        अगर ((!अग्र_probe_pos) || ((dist = (mz_uint16)(lookahead_pos - अग्र_probe_pos)) > max_dist)) वापस; \
        probe_pos = अग्र_probe_pos & TDEFL_LZ_DICT_आकार_MASK; \
        अगर ((d->m_dict[probe_pos + match_len] == c0) && (d->m_dict[probe_pos + match_len - 1] == c1)) अवरोध;
      TDEFL_PROBE
      TDEFL_PROBE
      TDEFL_PROBE
    }
    अगर (!dist) अवरोध;
    p = s; q = d->m_dict + probe_pos;
    क्रम (probe_len = 0; probe_len < max_match_len; probe_len++) {
        अगर (*p++ != *q++) अवरोध;
    }
    अगर (probe_len > match_len)
    {
      *pMatch_dist = dist;
      अगर ((*pMatch_len = match_len = probe_len) == max_match_len) वापस;
      c0 = d->m_dict[pos + match_len]; c1 = d->m_dict[pos + match_len - 1];
    }
  }
}
#पूर्ण_अगर // #if MINIZ_USE_UNALIGNED_LOADS_AND_STORES

#अगर MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
अटल mz_bool tdefl_compress_fast(tdefl_compressor *d)
{
  // Faster, minimally featured LZRW1-style match+parse loop with better register utilization. Intended for applications where raw throughput is valued more highly than ratio.
  mz_uint lookahead_pos = d->m_lookahead_pos, lookahead_आकार = d->m_lookahead_आकार, dict_आकार = d->m_dict_आकार, योग_lz_bytes = d->m_योग_lz_bytes, अंक_flags_बायाँ = d->m_अंक_flags_बायाँ;
  mz_uint8 *pLZ_code_buf = d->m_pLZ_code_buf, *pLZ_flags = d->m_pLZ_flags;
  mz_uint cur_pos = lookahead_pos & TDEFL_LZ_DICT_आकार_MASK;

  जबतक ((d->m_src_buf_बायाँ) || ((d->m_flush) && (lookahead_आकार)))
  {
    स्थिर mz_uint TDEFL_COMP_FAST_LOOKAHEAD_आकार = 4096;
    mz_uint dst_pos = (lookahead_pos + lookahead_आकार) & TDEFL_LZ_DICT_आकार_MASK;
    mz_uint अंक_bytes_to_process = (mz_uint)MZ_MIN(d->m_src_buf_बायाँ, TDEFL_COMP_FAST_LOOKAHEAD_आकार - lookahead_आकार);
    d->m_src_buf_बायाँ -= अंक_bytes_to_process;
    lookahead_आकार += अंक_bytes_to_process;

    जबतक (अंक_bytes_to_process)
    {
      mz_uint32 n = MZ_MIN(TDEFL_LZ_DICT_आकार - dst_pos, अंक_bytes_to_process);
      स_नकल(d->m_dict + dst_pos, d->m_pSrc, n);
      अगर (dst_pos < (TDEFL_MAX_MATCH_LEN - 1))
        स_नकल(d->m_dict + TDEFL_LZ_DICT_आकार + dst_pos, d->m_pSrc, MZ_MIN(n, (TDEFL_MAX_MATCH_LEN - 1) - dst_pos));
      d->m_pSrc += n;
      dst_pos = (dst_pos + n) & TDEFL_LZ_DICT_आकार_MASK;
      अंक_bytes_to_process -= n;
    }

    dict_आकार = MZ_MIN(TDEFL_LZ_DICT_आकार - lookahead_आकार, dict_आकार);
    अगर ((!d->m_flush) && (lookahead_आकार < TDEFL_COMP_FAST_LOOKAHEAD_आकार)) अवरोध;

    जबतक (lookahead_आकार >= 4)
    {
      mz_uint cur_match_dist, cur_match_len = 1;
      mz_uint8 *pCur_dict = d->m_dict + cur_pos;
      mz_uint first_trigram = (*(स्थिर mz_uint32 *)pCur_dict) & 0xFFFFFF;
      mz_uint hash = (first_trigram ^ (first_trigram >> (24 - (TDEFL_LZ_HASH_BITS - 8)))) & TDEFL_LEVEL1_HASH_आकार_MASK;
      mz_uint probe_pos = d->m_hash[hash];
      d->m_hash[hash] = (mz_uint16)lookahead_pos;

      अगर (((cur_match_dist = (mz_uint16)(lookahead_pos - probe_pos)) <= dict_आकार) && ((*(स्थिर mz_uint32 *)(d->m_dict + (probe_pos &= TDEFL_LZ_DICT_आकार_MASK)) & 0xFFFFFF) == first_trigram))
      {
        स्थिर mz_uint16 *p = (स्थिर mz_uint16 *)pCur_dict;
        स्थिर mz_uint16 *q = (स्थिर mz_uint16 *)(d->m_dict + probe_pos);
        mz_uint32 probe_len = 32;
        करो { } जबतक ( (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) && (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) &&
          (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) && (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) && (--probe_len > 0) );
        cur_match_len = ((mz_uint)(p - (स्थिर mz_uint16 *)pCur_dict) * 2) + (mz_uint)(*(स्थिर mz_uint8 *)p == *(स्थिर mz_uint8 *)q);
        अगर (!probe_len)
          cur_match_len = cur_match_dist ? TDEFL_MAX_MATCH_LEN : 0;

        अगर ((cur_match_len < TDEFL_MIN_MATCH_LEN) || ((cur_match_len == TDEFL_MIN_MATCH_LEN) && (cur_match_dist >= 8U*1024U)))
        {
          cur_match_len = 1;
          *pLZ_code_buf++ = (mz_uint8)first_trigram;
          *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
          d->m_huff_गिनती[0][(mz_uint8)first_trigram]++;
        }
        अन्यथा
        {
          mz_uint32 s0, s1;
          cur_match_len = MZ_MIN(cur_match_len, lookahead_आकार);

          MZ_ASSERT((cur_match_len >= TDEFL_MIN_MATCH_LEN) && (cur_match_dist >= 1) && (cur_match_dist <= TDEFL_LZ_DICT_आकार));

          cur_match_dist--;

          pLZ_code_buf[0] = (mz_uint8)(cur_match_len - TDEFL_MIN_MATCH_LEN);
          *(mz_uint16 *)(&pLZ_code_buf[1]) = (mz_uint16)cur_match_dist;
          pLZ_code_buf += 3;
          *pLZ_flags = (mz_uint8)((*pLZ_flags >> 1) | 0x80);

          s0 = s_tdefl_small_dist_sym[cur_match_dist & 511];
          s1 = s_tdefl_large_dist_sym[cur_match_dist >> 8];
          d->m_huff_गिनती[1][(cur_match_dist < 512) ? s0 : s1]++;

          d->m_huff_गिनती[0][s_tdefl_len_sym[cur_match_len - TDEFL_MIN_MATCH_LEN]]++;
        }
      }
      अन्यथा
      {
        *pLZ_code_buf++ = (mz_uint8)first_trigram;
        *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
        d->m_huff_गिनती[0][(mz_uint8)first_trigram]++;
      }

      अगर (--अंक_flags_बायाँ == 0) { अंक_flags_बायाँ = 8; pLZ_flags = pLZ_code_buf++; }

      योग_lz_bytes += cur_match_len;
      lookahead_pos += cur_match_len;
      dict_आकार = MZ_MIN(dict_आकार + cur_match_len, TDEFL_LZ_DICT_आकार);
      cur_pos = (cur_pos + cur_match_len) & TDEFL_LZ_DICT_आकार_MASK;
      MZ_ASSERT(lookahead_आकार >= cur_match_len);
      lookahead_आकार -= cur_match_len;

      अगर (pLZ_code_buf > &d->m_lz_code_buf[TDEFL_LZ_CODE_BUF_आकार - 8])
      {
        पूर्णांक n;
        d->m_lookahead_pos = lookahead_pos; d->m_lookahead_आकार = lookahead_आकार; d->m_dict_आकार = dict_आकार;
        d->m_योग_lz_bytes = योग_lz_bytes; d->m_pLZ_code_buf = pLZ_code_buf; d->m_pLZ_flags = pLZ_flags; d->m_अंक_flags_बायाँ = अंक_flags_बायाँ;
        अगर ((n = tdefl_flush_block(d, 0)) != 0)
          वापस (n < 0) ? MZ_FALSE : MZ_TRUE;
        योग_lz_bytes = d->m_योग_lz_bytes; pLZ_code_buf = d->m_pLZ_code_buf; pLZ_flags = d->m_pLZ_flags; अंक_flags_बायाँ = d->m_अंक_flags_बायाँ;
      }
    }

    जबतक (lookahead_आकार)
    {
      mz_uint8 lit = d->m_dict[cur_pos];

      योग_lz_bytes++;
      *pLZ_code_buf++ = lit;
      *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
      अगर (--अंक_flags_बायाँ == 0) { अंक_flags_बायाँ = 8; pLZ_flags = pLZ_code_buf++; }

      d->m_huff_गिनती[0][lit]++;

      lookahead_pos++;
      dict_आकार = MZ_MIN(dict_आकार + 1, TDEFL_LZ_DICT_आकार);
      cur_pos = (cur_pos + 1) & TDEFL_LZ_DICT_आकार_MASK;
      lookahead_आकार--;

      अगर (pLZ_code_buf > &d->m_lz_code_buf[TDEFL_LZ_CODE_BUF_आकार - 8])
      {
        पूर्णांक n;
        d->m_lookahead_pos = lookahead_pos; d->m_lookahead_आकार = lookahead_आकार; d->m_dict_आकार = dict_आकार;
        d->m_योग_lz_bytes = योग_lz_bytes; d->m_pLZ_code_buf = pLZ_code_buf; d->m_pLZ_flags = pLZ_flags; d->m_अंक_flags_बायाँ = अंक_flags_बायाँ;
        अगर ((n = tdefl_flush_block(d, 0)) != 0)
          वापस (n < 0) ? MZ_FALSE : MZ_TRUE;
        योग_lz_bytes = d->m_योग_lz_bytes; pLZ_code_buf = d->m_pLZ_code_buf; pLZ_flags = d->m_pLZ_flags; अंक_flags_बायाँ = d->m_अंक_flags_बायाँ;
      }
    }
  }

  d->m_lookahead_pos = lookahead_pos; d->m_lookahead_आकार = lookahead_आकार; d->m_dict_आकार = dict_आकार;
  d->m_योग_lz_bytes = योग_lz_bytes; d->m_pLZ_code_buf = pLZ_code_buf; d->m_pLZ_flags = pLZ_flags; d->m_अंक_flags_बायाँ = अंक_flags_बायाँ;
  वापस MZ_TRUE;
}
#पूर्ण_अगर // MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN

अटल MZ_FORCEINLINE व्योम tdefl_record_literal(tdefl_compressor *d, mz_uint8 lit)
{
  d->m_योग_lz_bytes++;
  *d->m_pLZ_code_buf++ = lit;
  *d->m_pLZ_flags = (mz_uint8)(*d->m_pLZ_flags >> 1); अगर (--d->m_अंक_flags_बायाँ == 0) { d->m_अंक_flags_बायाँ = 8; d->m_pLZ_flags = d->m_pLZ_code_buf++; }
  d->m_huff_गिनती[0][lit]++;
}

अटल MZ_FORCEINLINE व्योम tdefl_record_match(tdefl_compressor *d, mz_uint match_len, mz_uint match_dist)
{
  mz_uint32 s0, s1;

  MZ_ASSERT((match_len >= TDEFL_MIN_MATCH_LEN) && (match_dist >= 1) && (match_dist <= TDEFL_LZ_DICT_आकार));

  d->m_योग_lz_bytes += match_len;

  d->m_pLZ_code_buf[0] = (mz_uint8)(match_len - TDEFL_MIN_MATCH_LEN);

  match_dist -= 1;
  d->m_pLZ_code_buf[1] = (mz_uint8)(match_dist & 0xFF);
  d->m_pLZ_code_buf[2] = (mz_uint8)(match_dist >> 8); d->m_pLZ_code_buf += 3;

  *d->m_pLZ_flags = (mz_uint8)((*d->m_pLZ_flags >> 1) | 0x80); अगर (--d->m_अंक_flags_बायाँ == 0) { d->m_अंक_flags_बायाँ = 8; d->m_pLZ_flags = d->m_pLZ_code_buf++; }

  s0 = s_tdefl_small_dist_sym[match_dist & 511]; s1 = s_tdefl_large_dist_sym[(match_dist >> 8) & 127];
  d->m_huff_गिनती[1][(match_dist < 512) ? s0 : s1]++;

  अगर (match_len >= TDEFL_MIN_MATCH_LEN) d->m_huff_गिनती[0][s_tdefl_len_sym[match_len - TDEFL_MIN_MATCH_LEN]]++;
}

अटल mz_bool tdefl_compress_normal(tdefl_compressor *d)
{
  स्थिर mz_uint8 *pSrc = d->m_pSrc; माप_प्रकार src_buf_बायाँ = d->m_src_buf_बायाँ;
  tdefl_flush flush = d->m_flush;

  जबतक ((src_buf_बायाँ) || ((flush) && (d->m_lookahead_आकार)))
  {
    mz_uint len_to_move, cur_match_dist, cur_match_len, cur_pos;
    // Update dictionary and hash chains. Keeps the lookahead size equal to TDEFL_MAX_MATCH_LEN.
    अगर ((d->m_lookahead_आकार + d->m_dict_आकार) >= (TDEFL_MIN_MATCH_LEN - 1))
    {
      mz_uint dst_pos = (d->m_lookahead_pos + d->m_lookahead_आकार) & TDEFL_LZ_DICT_आकार_MASK, ins_pos = d->m_lookahead_pos + d->m_lookahead_आकार - 2;
      mz_uint hash = (d->m_dict[ins_pos & TDEFL_LZ_DICT_आकार_MASK] << TDEFL_LZ_HASH_SHIFT) ^ d->m_dict[(ins_pos + 1) & TDEFL_LZ_DICT_आकार_MASK];
      mz_uint अंक_bytes_to_process = (mz_uint)MZ_MIN(src_buf_बायाँ, TDEFL_MAX_MATCH_LEN - d->m_lookahead_आकार);
      स्थिर mz_uint8 *pSrc_end = pSrc ? pSrc + अंक_bytes_to_process : शून्य;
      src_buf_बायाँ -= अंक_bytes_to_process;
      d->m_lookahead_आकार += अंक_bytes_to_process;
      जबतक (pSrc != pSrc_end)
      {
        mz_uint8 c = *pSrc++; d->m_dict[dst_pos] = c; अगर (dst_pos < (TDEFL_MAX_MATCH_LEN - 1)) d->m_dict[TDEFL_LZ_DICT_आकार + dst_pos] = c;
        hash = ((hash << TDEFL_LZ_HASH_SHIFT) ^ c) & (TDEFL_LZ_HASH_आकार - 1);
        d->m_अग्र[ins_pos & TDEFL_LZ_DICT_आकार_MASK] = d->m_hash[hash]; d->m_hash[hash] = (mz_uint16)(ins_pos);
        dst_pos = (dst_pos + 1) & TDEFL_LZ_DICT_आकार_MASK; ins_pos++;
      }
    }
    अन्यथा
    {
      जबतक ((src_buf_बायाँ) && (d->m_lookahead_आकार < TDEFL_MAX_MATCH_LEN))
      {
        mz_uint8 c = *pSrc++;
        mz_uint dst_pos = (d->m_lookahead_pos + d->m_lookahead_आकार) & TDEFL_LZ_DICT_आकार_MASK;
        src_buf_बायाँ--;
        d->m_dict[dst_pos] = c;
        अगर (dst_pos < (TDEFL_MAX_MATCH_LEN - 1))
          d->m_dict[TDEFL_LZ_DICT_आकार + dst_pos] = c;
        अगर ((++d->m_lookahead_आकार + d->m_dict_आकार) >= TDEFL_MIN_MATCH_LEN)
        {
          mz_uint ins_pos = d->m_lookahead_pos + (d->m_lookahead_आकार - 1) - 2;
          mz_uint hash = ((d->m_dict[ins_pos & TDEFL_LZ_DICT_आकार_MASK] << (TDEFL_LZ_HASH_SHIFT * 2)) ^ (d->m_dict[(ins_pos + 1) & TDEFL_LZ_DICT_आकार_MASK] << TDEFL_LZ_HASH_SHIFT) ^ c) & (TDEFL_LZ_HASH_आकार - 1);
          d->m_अग्र[ins_pos & TDEFL_LZ_DICT_आकार_MASK] = d->m_hash[hash]; d->m_hash[hash] = (mz_uint16)(ins_pos);
        }
      }
    }
    d->m_dict_आकार = MZ_MIN(TDEFL_LZ_DICT_आकार - d->m_lookahead_आकार, d->m_dict_आकार);
    अगर ((!flush) && (d->m_lookahead_आकार < TDEFL_MAX_MATCH_LEN))
      अवरोध;

    // Simple lazy/greedy parsing state machine.
    len_to_move = 1; cur_match_dist = 0; cur_match_len = d->m_saved_match_len ? d->m_saved_match_len : (TDEFL_MIN_MATCH_LEN - 1); cur_pos = d->m_lookahead_pos & TDEFL_LZ_DICT_आकार_MASK;
    अगर (d->m_flags & (TDEFL_RLE_MATCHES | TDEFL_FORCE_ALL_RAW_BLOCKS))
    {
      अगर ((d->m_dict_आकार) && (!(d->m_flags & TDEFL_FORCE_ALL_RAW_BLOCKS)))
      {
        mz_uint8 c = d->m_dict[(cur_pos - 1) & TDEFL_LZ_DICT_आकार_MASK];
        cur_match_len = 0; जबतक (cur_match_len < d->m_lookahead_आकार) { अगर (d->m_dict[cur_pos + cur_match_len] != c) अवरोध; cur_match_len++; }
        अगर (cur_match_len < TDEFL_MIN_MATCH_LEN) cur_match_len = 0; अन्यथा cur_match_dist = 1;
      }
    }
    अन्यथा
    {
      tdefl_find_match(d, d->m_lookahead_pos, d->m_dict_आकार, d->m_lookahead_आकार, &cur_match_dist, &cur_match_len);
    }
    अगर (((cur_match_len == TDEFL_MIN_MATCH_LEN) && (cur_match_dist >= 8U*1024U)) || (cur_pos == cur_match_dist) || ((d->m_flags & TDEFL_FILTER_MATCHES) && (cur_match_len <= 5)))
    {
      cur_match_dist = cur_match_len = 0;
    }
    अगर (d->m_saved_match_len)
    {
      अगर (cur_match_len > d->m_saved_match_len)
      {
        tdefl_record_literal(d, (mz_uint8)d->m_saved_lit);
        अगर (cur_match_len >= 128)
        {
          tdefl_record_match(d, cur_match_len, cur_match_dist);
          d->m_saved_match_len = 0; len_to_move = cur_match_len;
        }
        अन्यथा
        {
          d->m_saved_lit = d->m_dict[cur_pos]; d->m_saved_match_dist = cur_match_dist; d->m_saved_match_len = cur_match_len;
        }
      }
      अन्यथा
      {
        tdefl_record_match(d, d->m_saved_match_len, d->m_saved_match_dist);
        len_to_move = d->m_saved_match_len - 1; d->m_saved_match_len = 0;
      }
    }
    अन्यथा अगर (!cur_match_dist)
      tdefl_record_literal(d, d->m_dict[MZ_MIN(cur_pos, माप(d->m_dict) - 1)]);
    अन्यथा अगर ((d->m_greedy_parsing) || (d->m_flags & TDEFL_RLE_MATCHES) || (cur_match_len >= 128))
    {
      tdefl_record_match(d, cur_match_len, cur_match_dist);
      len_to_move = cur_match_len;
    }
    अन्यथा
    {
      d->m_saved_lit = d->m_dict[MZ_MIN(cur_pos, माप(d->m_dict) - 1)]; d->m_saved_match_dist = cur_match_dist; d->m_saved_match_len = cur_match_len;
    }
    // Move the lookahead forward by len_to_move bytes.
    d->m_lookahead_pos += len_to_move;
    MZ_ASSERT(d->m_lookahead_आकार >= len_to_move);
    d->m_lookahead_आकार -= len_to_move;
    d->m_dict_आकार = MZ_MIN(d->m_dict_आकार + len_to_move, TDEFL_LZ_DICT_आकार);
    // Check if it's time to flush the current LZ codes to the internal output buffer.
    अगर ( (d->m_pLZ_code_buf > &d->m_lz_code_buf[TDEFL_LZ_CODE_BUF_आकार - 8]) ||
         ( (d->m_योग_lz_bytes > 31*1024) && (((((mz_uint)(d->m_pLZ_code_buf - d->m_lz_code_buf) * 115) >> 7) >= d->m_योग_lz_bytes) || (d->m_flags & TDEFL_FORCE_ALL_RAW_BLOCKS))) )
    {
      पूर्णांक n;
      d->m_pSrc = pSrc; d->m_src_buf_बायाँ = src_buf_बायाँ;
      अगर ((n = tdefl_flush_block(d, 0)) != 0)
        वापस (n < 0) ? MZ_FALSE : MZ_TRUE;
    }
  }

  d->m_pSrc = pSrc; d->m_src_buf_बायाँ = src_buf_बायाँ;
  वापस MZ_TRUE;
}

अटल tdefl_status tdefl_flush_output_बफर(tdefl_compressor *d)
{
  अगर (d->m_p_In_buf_आकार)
  {
    *d->m_p_In_buf_आकार = d->m_pSrc - (स्थिर mz_uint8 *)d->m_pIn_buf;
  }

  अगर (d->m_p_Out_buf_आकार)
  {
    माप_प्रकार n = MZ_MIN(*d->m_p_Out_buf_आकार - d->m_out_buf_ofs, d->m_output_flush_remaining);
    स_नकल((mz_uint8 *)d->m_pOut_buf + d->m_out_buf_ofs, d->m_output_buf + d->m_output_flush_ofs, n);
    d->m_output_flush_ofs += (mz_uint)n;
    d->m_output_flush_remaining -= (mz_uint)n;
    d->m_out_buf_ofs += n;

    *d->m_p_Out_buf_आकार = d->m_out_buf_ofs;
  }

  वापस (d->m_finished && !d->m_output_flush_remaining) ? TDEFL_STATUS_DONE : TDEFL_STATUS_OKAY;
}

tdefl_status tdefl_compress(tdefl_compressor *d, स्थिर व्योम *pIn_buf, माप_प्रकार *p_In_buf_आकार, व्योम *pOut_buf, माप_प्रकार *p_Out_buf_आकार, tdefl_flush flush)
{
  अगर (!d)
  {
    अगर (p_In_buf_आकार) *p_In_buf_आकार = 0;
    अगर (p_Out_buf_आकार) *p_Out_buf_आकार = 0;
    वापस TDEFL_STATUS_BAD_PARAM;
  }

  d->m_pIn_buf = pIn_buf; d->m_p_In_buf_आकार = p_In_buf_आकार;
  d->m_pOut_buf = pOut_buf; d->m_p_Out_buf_आकार = p_Out_buf_आकार;
  d->m_pSrc = (स्थिर mz_uint8 *)(pIn_buf); d->m_src_buf_बायाँ = p_In_buf_आकार ? *p_In_buf_आकार : 0;
  d->m_out_buf_ofs = 0;
  d->m_flush = flush;

  अगर ( ((d->m_pPut_buf_func != शून्य) == ((pOut_buf != शून्य) || (p_Out_buf_आकार != शून्य))) || (d->m_पूर्व_return_status != TDEFL_STATUS_OKAY) ||
        (d->m_wants_to_finish && (flush != TDEFL_FINISH)) || (p_In_buf_आकार && *p_In_buf_आकार && !pIn_buf) || (p_Out_buf_आकार && *p_Out_buf_आकार && !pOut_buf) )
  {
    अगर (p_In_buf_आकार) *p_In_buf_आकार = 0;
    अगर (p_Out_buf_आकार) *p_Out_buf_आकार = 0;
    वापस (d->m_पूर्व_return_status = TDEFL_STATUS_BAD_PARAM);
  }
  d->m_wants_to_finish |= (flush == TDEFL_FINISH);

  अगर ((d->m_output_flush_remaining) || (d->m_finished))
    वापस (d->m_पूर्व_return_status = tdefl_flush_output_बफर(d));

#अगर MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  अगर (((d->m_flags & TDEFL_MAX_PROBES_MASK) == 1) &&
      ((d->m_flags & TDEFL_GREEDY_PARSING_FLAG) != 0) &&
      ((d->m_flags & (TDEFL_FILTER_MATCHES | TDEFL_FORCE_ALL_RAW_BLOCKS | TDEFL_RLE_MATCHES)) == 0))
  {
    अगर (!tdefl_compress_fast(d))
      वापस d->m_पूर्व_return_status;
  }
  अन्यथा
#पूर्ण_अगर // #if MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  {
    अगर (!tdefl_compress_normal(d))
      वापस d->m_पूर्व_return_status;
  }

  अगर ((d->m_flags & (TDEFL_WRITE_ZLIB_HEADER | TDEFL_COMPUTE_ADLER32)) && (pIn_buf))
    d->m_adler32 = (mz_uint32)mz_adler32(d->m_adler32, (स्थिर mz_uint8 *)pIn_buf, d->m_pSrc - (स्थिर mz_uint8 *)pIn_buf);

  अगर ((flush) && (!d->m_lookahead_आकार) && (!d->m_src_buf_बायाँ) && (!d->m_output_flush_remaining))
  {
    अगर (tdefl_flush_block(d, flush) < 0)
      वापस d->m_पूर्व_return_status;
    d->m_finished = (flush == TDEFL_FINISH);
    अगर (flush == TDEFL_FULL_FLUSH) { MZ_CLEAR_ARR(d->m_hash); MZ_CLEAR_ARR(d->m_अग्र); d->m_dict_आकार = 0; }
  }

  वापस (d->m_पूर्व_return_status = tdefl_flush_output_बफर(d));
}

tdefl_status tdefl_compress_बफर(tdefl_compressor *d, स्थिर व्योम *pIn_buf, माप_प्रकार in_buf_आकार, tdefl_flush flush)
{
  MZ_ASSERT(d->m_pPut_buf_func); वापस tdefl_compress(d, pIn_buf, &in_buf_आकार, शून्य, शून्य, flush);
}

tdefl_status tdefl_init(tdefl_compressor *d, tdefl_put_buf_func_ptr pPut_buf_func, व्योम *pPut_buf_user, पूर्णांक flags)
{
  d->m_pPut_buf_func = pPut_buf_func; d->m_pPut_buf_user = pPut_buf_user;
  d->m_flags = (mz_uint)(flags); d->m_max_probes[0] = 1 + ((flags & 0xFFF) + 2) / 3; d->m_greedy_parsing = (flags & TDEFL_GREEDY_PARSING_FLAG) != 0;
  d->m_max_probes[1] = 1 + (((flags & 0xFFF) >> 2) + 2) / 3;
  अगर (!(flags & TDEFL_NONDETERMINISTIC_PARSING_FLAG)) MZ_CLEAR_ARR(d->m_hash);
  d->m_lookahead_pos = d->m_lookahead_आकार = d->m_dict_आकार = d->m_योग_lz_bytes = d->m_lz_code_buf_dict_pos = d->m_bits_in = 0;
  d->m_output_flush_ofs = d->m_output_flush_remaining = d->m_finished = d->m_block_सूचकांक = d->m_bit_बफर = d->m_wants_to_finish = 0;
  d->m_pLZ_code_buf = d->m_lz_code_buf + 1; d->m_pLZ_flags = d->m_lz_code_buf; d->m_अंक_flags_बायाँ = 8;
  d->m_pOutput_buf = d->m_output_buf; d->m_pOutput_buf_end = d->m_output_buf; d->m_पूर्व_return_status = TDEFL_STATUS_OKAY;
  d->m_saved_match_dist = d->m_saved_match_len = d->m_saved_lit = 0; d->m_adler32 = 1;
  d->m_pIn_buf = शून्य; d->m_pOut_buf = शून्य;
  d->m_p_In_buf_आकार = शून्य; d->m_p_Out_buf_आकार = शून्य;
  d->m_flush = TDEFL_NO_FLUSH; d->m_pSrc = शून्य; d->m_src_buf_बायाँ = 0; d->m_out_buf_ofs = 0;
  स_रखो(&d->m_huff_गिनती[0][0], 0, माप(d->m_huff_गिनती[0][0]) * TDEFL_MAX_HUFF_SYMBOLS_0);
  स_रखो(&d->m_huff_गिनती[1][0], 0, माप(d->m_huff_गिनती[1][0]) * TDEFL_MAX_HUFF_SYMBOLS_1);
  वापस TDEFL_STATUS_OKAY;
}

#अगर_अघोषित MINIZ_SDL_NOUNUSED
tdefl_status tdefl_get_पूर्व_return_status(tdefl_compressor *d)
{
  वापस d->m_पूर्व_return_status;
}

mz_uint32 tdefl_get_adler32(tdefl_compressor *d)
{
  वापस d->m_adler32;
}

mz_bool tdefl_compress_mem_to_output(स्थिर व्योम *pBuf, माप_प्रकार buf_len, tdefl_put_buf_func_ptr pPut_buf_func, व्योम *pPut_buf_user, पूर्णांक flags)
{
  tdefl_compressor *pComp; mz_bool succeeded; अगर (((buf_len) && (!pBuf)) || (!pPut_buf_func)) वापस MZ_FALSE;
  pComp = (tdefl_compressor*)MZ_MALLOC(माप(tdefl_compressor)); अगर (!pComp) वापस MZ_FALSE;
  succeeded = (tdefl_init(pComp, pPut_buf_func, pPut_buf_user, flags) == TDEFL_STATUS_OKAY);
  succeeded = succeeded && (tdefl_compress_बफर(pComp, pBuf, buf_len, TDEFL_FINISH) == TDEFL_STATUS_DONE);
  MZ_FREE(pComp); वापस succeeded;
}
#पूर्ण_अगर /* MINIZ_SDL_NOUNUSED */

प्रकार काष्ठा
{
  माप_प्रकार m_आकार, m_capacity;
  mz_uint8 *m_pBuf;
  mz_bool m_expandable;
} tdefl_output_बफर;

अटल mz_bool tdefl_output_बफर_putter(स्थिर व्योम *pBuf, पूर्णांक len, व्योम *pUser)
{
  tdefl_output_बफर *p = (tdefl_output_बफर *)pUser;
  माप_प्रकार new_आकार = p->m_आकार + len;
  अगर (new_आकार > p->m_capacity)
  {
    माप_प्रकार new_capacity = p->m_capacity; mz_uint8 *pNew_buf; अगर (!p->m_expandable) वापस MZ_FALSE;
    करो { new_capacity = MZ_MAX(128U, new_capacity << 1U); } जबतक (new_आकार > new_capacity);
    pNew_buf = (mz_uint8*)MZ_REALLOC(p->m_pBuf, new_capacity); अगर (!pNew_buf) वापस MZ_FALSE;
    p->m_pBuf = pNew_buf; p->m_capacity = new_capacity;
  }
  स_नकल((mz_uint8*)p->m_pBuf + p->m_आकार, pBuf, len); p->m_आकार = new_आकार;
  वापस MZ_TRUE;
}

#अगर_अघोषित MINIZ_SDL_NOUNUSED
व्योम *tdefl_compress_mem_to_heap(स्थिर व्योम *pSrc_buf, माप_प्रकार src_buf_len, माप_प्रकार *pOut_len, पूर्णांक flags)
{
  tdefl_output_बफर out_buf; MZ_CLEAR_OBJ(out_buf);
  अगर (!pOut_len) वापस MZ_FALSE; अन्यथा *pOut_len = 0;
  out_buf.m_expandable = MZ_TRUE;
  अगर (!tdefl_compress_mem_to_output(pSrc_buf, src_buf_len, tdefl_output_बफर_putter, &out_buf, flags)) वापस शून्य;
  *pOut_len = out_buf.m_आकार; वापस out_buf.m_pBuf;
}

माप_प्रकार tdefl_compress_mem_to_mem(व्योम *pOut_buf, माप_प्रकार out_buf_len, स्थिर व्योम *pSrc_buf, माप_प्रकार src_buf_len, पूर्णांक flags)
{
  tdefl_output_बफर out_buf; MZ_CLEAR_OBJ(out_buf);
  अगर (!pOut_buf) वापस 0;
  out_buf.m_pBuf = (mz_uint8*)pOut_buf; out_buf.m_capacity = out_buf_len;
  अगर (!tdefl_compress_mem_to_output(pSrc_buf, src_buf_len, tdefl_output_बफर_putter, &out_buf, flags)) वापस 0;
  वापस out_buf.m_आकार;
}
#पूर्ण_अगर /* MINIZ_SDL_NOUNUSED */

#अगर_अघोषित MINIZ_NO_ZLIB_APIS
अटल स्थिर mz_uint s_tdefl_अंक_probes[11] = { 0, 1, 6, 32,  16, 32, 128, 256,  512, 768, 1500 };

// level may actually range from [0,10] (10 is a "hidden" max level, where we want a bit more compression and it's fine if throughput to fall off a cliff on some files).
mz_uint tdefl_create_comp_flags_from_zip_params(पूर्णांक level, पूर्णांक window_bits, पूर्णांक strategy)
{
  mz_uint comp_flags = s_tdefl_अंक_probes[(level >= 0) ? MZ_MIN(10, level) : MZ_DEFAULT_LEVEL] | ((level <= 3) ? TDEFL_GREEDY_PARSING_FLAG : 0);
  अगर (window_bits > 0) comp_flags |= TDEFL_WRITE_ZLIB_HEADER;

  अगर (!level) comp_flags |= TDEFL_FORCE_ALL_RAW_BLOCKS;
  अन्यथा अगर (strategy == MZ_FILTERED) comp_flags |= TDEFL_FILTER_MATCHES;
  अन्यथा अगर (strategy == MZ_HUFFMAN_ONLY) comp_flags &= ~TDEFL_MAX_PROBES_MASK;
  अन्यथा अगर (strategy == MZ_FIXED) comp_flags |= TDEFL_FORCE_ALL_STATIC_BLOCKS;
  अन्यथा अगर (strategy == MZ_RLE) comp_flags |= TDEFL_RLE_MATCHES;

  वापस comp_flags;
}
#पूर्ण_अगर //MINIZ_NO_ZLIB_APIS

#अगर_घोषित _MSC_VER
#आशय warning (धकेलो)
#आशय warning (disable:4204) // nonstandard extension used : non-constant aggregate initializer (also supported by GNU C and C99, so no big deal)
#पूर्ण_अगर

// Simple PNG writer function by Alex Evans, 2011. Released into the public domain: https://gist.github.com/908299, more context at
// http://altdevblogaday.org/2011/04/06/a-smaller-jpg-encoder/.
// This is actually a modification of Alex's original code so PNG files generated by this function pass pngcheck.
MINIZ_STATIC व्योम *tdefl_write_image_to_png_file_in_memory_ex(स्थिर व्योम *pImage, पूर्णांक w, पूर्णांक h, पूर्णांक अंक_chans, पूर्णांक bpl, माप_प्रकार *pLen_out, mz_uint level, mz_bool flip, mz_uint8 *plte, पूर्णांक plte_आकार, mz_uint8 *trns, पूर्णांक trns_आकार)
{
  // Using a local copy of this array here in case MINIZ_NO_ZLIB_APIS was defined.
  अटल स्थिर mz_uint s_tdefl_png_अंक_probes[11] = { 0, 1, 6, 32,  16, 32, 128, 256,  512, 768, 1500 };
  tdefl_compressor *pComp = (tdefl_compressor *)MZ_MALLOC(माप(tdefl_compressor)); tdefl_output_बफर out_buf; पूर्णांक i, y, z = 0; mz_uint32 c; *pLen_out = 0; माप_प्रकार तथ्य_start, तथ्य_आकार_3;
  अगर (!pComp) वापस शून्य;
  MZ_CLEAR_OBJ(out_buf); out_buf.m_expandable = MZ_TRUE;
  out_buf.m_capacity = 57+MZ_MAX(64, (1+w*अंक_chans)*h);
  अगर (plte_आकार > 0)
    out_buf.m_capacity += 12+plte_आकार;
  अगर (trns_आकार > 0)
    out_buf.m_capacity += 12+trns_आकार;
  अगर (शून्य == (out_buf.m_pBuf = (mz_uint8*)MZ_MALLOC(out_buf.m_capacity))) { MZ_FREE(pComp); वापस शून्य; }
  // write header
  {
    अटल स्थिर mz_uint8 chans[] = {0x00, 0x00, 0x04, 0x02, 0x06};

    mz_uint8 pnghdr[33]={ 0x89,0x50,0x4e,0x47,0x0d,0x0a,0x1a,0x0a,
                          0x00,0x00,0x00,0x0d,0x49,0x48,0x44,0x52,
                          0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                          0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

    pnghdr[18] = (mz_uint8)(w>>8);
    pnghdr[19] = (mz_uint8)(w>>0);

    pnghdr[22] = (mz_uint8)(h>>8);
    pnghdr[23] = (mz_uint8)(h>>0);

    अगर (अंक_chans == 1 && plte_आकार > 0)
      pnghdr[25] = 3;
    अन्यथा
      pnghdr[25] = (chans[अंक_chans]);

    c = (mz_uint32)mz_crc32(MZ_CRC32_INIT,pnghdr+12,17);
    क्रम (i=0; i<4; ++i, c<<=8) ((mz_uint8*)(pnghdr+29))[i] = (mz_uint8)(c>>24);
    अगर (!tdefl_output_बफर_putter(pnghdr, माप(pnghdr), &out_buf)) { *pLen_out = 0; MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); वापस शून्य; }
  }
  // write PLTE chunk
  अगर (plte_आकार > 0)
  {
    mz_uint8 hdr[8]={0x00,0x00,0x00,0x00,0x50,0x4c,0x54,0x45};

    hdr[0] = (mz_uint8)(plte_आकार>>24);
    hdr[1] = (mz_uint8)(plte_आकार>>16);
    hdr[2] = (mz_uint8)(plte_आकार>> 8);
    hdr[3] = (mz_uint8)(plte_आकार>> 0);
    अगर (!tdefl_output_बफर_putter(hdr, माप(hdr), &out_buf)) { *pLen_out = 0; MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); वापस शून्य; }
    तथ्य_start = out_buf.m_आकार;
    अगर (!tdefl_output_बफर_putter(plte, plte_आकार, &out_buf)) { *pLen_out = 0; MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); वापस शून्य; }
    अगर (!tdefl_output_बफर_putter("\0\0\0\0", 4, &out_buf)) { *pLen_out = 0; MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); वापस शून्य; }
    c = (mz_uint32)mz_crc32(MZ_CRC32_INIT,out_buf.m_pBuf+तथ्य_start-4, plte_आकार+4);
    क्रम (i=0; i<4; ++i, c<<=8) (out_buf.m_pBuf+out_buf.m_आकार-4)[i] = (mz_uint8)(c >> 24);
  }
  // write tRNS chunk
  अगर (trns_आकार > 0)
  {
    mz_uint8 hdr[8]={0x00,0x00,0x00,0x00,0x74,0x52,0x4E,0x53};

    hdr[0] = (mz_uint8)(trns_आकार>>24);
    hdr[1] = (mz_uint8)(trns_आकार>>16);
    hdr[2] = (mz_uint8)(trns_आकार>> 8);
    hdr[3] = (mz_uint8)(trns_आकार>> 0);
    अगर (!tdefl_output_बफर_putter(hdr, माप(hdr), &out_buf)) { *pLen_out = 0; MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); वापस शून्य; }
    तथ्य_start = out_buf.m_आकार;
    अगर (!tdefl_output_बफर_putter(trns, trns_आकार, &out_buf)) { *pLen_out = 0; MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); वापस शून्य; }
    अगर (!tdefl_output_बफर_putter("\0\0\0\0", 4, &out_buf)) { *pLen_out = 0; MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); वापस शून्य; }
    c = (mz_uint32)mz_crc32(MZ_CRC32_INIT,out_buf.m_pBuf+तथ्य_start-4, trns_आकार+4);
    क्रम (i=0; i<4; ++i, c<<=8) (out_buf.m_pBuf+out_buf.m_आकार-4)[i] = (mz_uint8)(c >> 24);
  }
  // write IDAT chunk
  अगर (!tdefl_output_बफर_putter("\0\0\0\0\x49\x44\x41\x54", 8, &out_buf)) { *pLen_out = 0; MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); वापस शून्य; }
  तथ्य_start = out_buf.m_आकार;
  // compress image data
  tdefl_init(pComp, tdefl_output_बफर_putter, &out_buf, s_tdefl_png_अंक_probes[MZ_MIN(10, level)] | TDEFL_WRITE_ZLIB_HEADER);
  क्रम (y = 0; y < h; ++y) { tdefl_compress_बफर(pComp, &z, 1, TDEFL_NO_FLUSH); tdefl_compress_बफर(pComp, (mz_uint8*)pImage + (flip ? (h - 1 - y) : y) * bpl, w * अंक_chans, TDEFL_NO_FLUSH); }
  अगर (tdefl_compress_बफर(pComp, शून्य, 0, TDEFL_FINISH) != TDEFL_STATUS_DONE) { MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); वापस शून्य; }
  // write IDAT size
  तथ्य_आकार_3 = out_buf.m_आकार-तथ्य_start;
  (out_buf.m_pBuf+तथ्य_start-8)[0] = (mz_uint8)(तथ्य_आकार_3>>24);
  (out_buf.m_pBuf+तथ्य_start-8)[1] = (mz_uint8)(तथ्य_आकार_3>>16);
  (out_buf.m_pBuf+तथ्य_start-8)[2] = (mz_uint8)(तथ्य_आकार_3>> 8);
  (out_buf.m_pBuf+तथ्य_start-8)[3] = (mz_uint8)(तथ्य_आकार_3>> 0);
  // write footer (IDAT CRC-32, followed by IEND chunk)
  अगर (!tdefl_output_बफर_putter("\0\0\0\0\0\0\0\0\x49\x45\x4e\x44\xae\x42\x60\x82", 16, &out_buf)) { *pLen_out = 0; MZ_FREE(pComp); MZ_FREE(out_buf.m_pBuf); वापस शून्य; }
  c = (mz_uint32)mz_crc32(MZ_CRC32_INIT,out_buf.m_pBuf+तथ्य_start-4, तथ्य_आकार_3+4);
  क्रम (i=0; i<4; ++i, c<<=8) (out_buf.m_pBuf+out_buf.m_आकार-16)[i] = (mz_uint8)(c >> 24);
  // compute final size of file, grab compressed data buffer and return
  *pLen_out = out_buf.m_आकार;
  MZ_FREE(pComp);
  वापस out_buf.m_pBuf;
}
#अगर_अघोषित MINIZ_SDL_NOUNUSED
MINIZ_STATIC व्योम *tdefl_write_image_to_png_file_in_memory(स्थिर व्योम *pImage, पूर्णांक w, पूर्णांक h, पूर्णांक अंक_chans, पूर्णांक bpl, माप_प्रकार *pLen_out)
{
  // Level 6 corresponds to TDEFL_DEFAULT_MAX_PROBES or MZ_DEFAULT_LEVEL (but we can't depend on MZ_DEFAULT_LEVEL being available in case the zlib API's where #defined out)
  वापस tdefl_write_image_to_png_file_in_memory_ex(pImage, w, h, अंक_chans, bpl, pLen_out, 6, MZ_FALSE, शून्य, 0, शून्य, 0);
}
#पूर्ण_अगर

#अगर_घोषित _MSC_VER
#आशय warning (निकालो)
#पूर्ण_अगर
#पूर्ण_अगर /*#ifndef MINIZ_NO_DEFLATE_APIS*/

// ------------------- .ZIP archive reading

#अगर_अघोषित MINIZ_NO_ARCHIVE_APIS

#अगर_घोषित MINIZ_NO_STDIO
  #घोषणा MZ_FILE व्योम *
#अन्यथा
  #समावेश <stdio.h>
  #समावेश <sys/stat.h>

  #अगर defined(_MSC_VER) || defined(__MINGW64__)
    अटल खाता *mz_fopen(स्थिर अक्षर *pFilename, स्थिर अक्षर *pMode)
    {
      खाता* pFile = शून्य;
      fopen_s(&pFile, pFilename, pMode);
      वापस pFile;
    }
    अटल खाता *mz_freopen(स्थिर अक्षर *pPath, स्थिर अक्षर *pMode, खाता *pStream)
    {
      खाता* pFile = शून्य;
      अगर (freopen_s(&pFile, pPath, pMode, pStream))
        वापस शून्य;
      वापस pFile;
    }
    #अगर_अघोषित MINIZ_NO_TIME
      #समावेश <sys/utime.h>
    #पूर्ण_अगर
    #घोषणा MZ_FILE खाता
    #घोषणा MZ_FOPEN mz_fopen
    #घोषणा MZ_FCLOSE ख_बंद
    #घोषणा MZ_FREAD ख_पढ़ो
    #घोषणा MZ_FWRITE ख_डालो
    #घोषणा MZ_FTELL64 _ftelli64
    #घोषणा MZ_FSEEK64 _fseeki64
    #घोषणा MZ_FILE_STAT_STRUCT _stat
    #घोषणा MZ_FILE_STAT _stat
    #घोषणा MZ_FFLUSH ख_साफ
    #घोषणा MZ_FREOPEN mz_freopen
    #घोषणा MZ_DELETE_FILE हटाओ
  #या_अगर defined(__MINGW32__)
    #अगर_अघोषित MINIZ_NO_TIME
      #समावेश <sys/utime.h>
    #पूर्ण_अगर
    #घोषणा MZ_FILE खाता
    #घोषणा MZ_FOPEN(f, m) ख_खोलो(f, m)
    #घोषणा MZ_FCLOSE ख_बंद
    #घोषणा MZ_FREAD ख_पढ़ो
    #घोषणा MZ_FWRITE ख_डालो
    #घोषणा MZ_FTELL64 ftello64
    #घोषणा MZ_FSEEK64 fseeko64
    #घोषणा MZ_FILE_STAT_STRUCT _stat
    #घोषणा MZ_FILE_STAT _stat
    #घोषणा MZ_FFLUSH ख_साफ
    #घोषणा MZ_FREOPEN(f, m, s) ख_व_खोलो(f, m, s)
    #घोषणा MZ_DELETE_FILE हटाओ
  #या_अगर defined(__TINYC__)
    #अगर_अघोषित MINIZ_NO_TIME
      #समावेश <sys/utime.h>
    #पूर्ण_अगर
    #घोषणा MZ_FILE खाता
    #घोषणा MZ_FOPEN(f, m) ख_खोलो(f, m)
    #घोषणा MZ_FCLOSE ख_बंद
    #घोषणा MZ_FREAD ख_पढ़ो
    #घोषणा MZ_FWRITE ख_डालो
    #घोषणा MZ_FTELL64 ख_बताओ
    #घोषणा MZ_FSEEK64 ख_जाओ
    #घोषणा MZ_FILE_STAT_STRUCT stat
    #घोषणा MZ_FILE_STAT stat
    #घोषणा MZ_FFLUSH ख_साफ
    #घोषणा MZ_FREOPEN(f, m, s) ख_व_खोलो(f, m, s)
    #घोषणा MZ_DELETE_FILE हटाओ
  #या_अगर defined(__GNUC__) && _LARGEFILE64_SOURCE
    #अगर_अघोषित MINIZ_NO_TIME
      #समावेश <utime.h>
    #पूर्ण_अगर
    #घोषणा MZ_FILE खाता
    #घोषणा MZ_FOPEN(f, m) fopen64(f, m)
    #घोषणा MZ_FCLOSE ख_बंद
    #घोषणा MZ_FREAD ख_पढ़ो
    #घोषणा MZ_FWRITE ख_डालो
    #घोषणा MZ_FTELL64 ftello64
    #घोषणा MZ_FSEEK64 fseeko64
    #घोषणा MZ_FILE_STAT_STRUCT stat64
    #घोषणा MZ_FILE_STAT stat64
    #घोषणा MZ_FFLUSH ख_साफ
    #घोषणा MZ_FREOPEN(p, m, s) freopen64(p, m, s)
    #घोषणा MZ_DELETE_FILE हटाओ
  #अन्यथा
    #अगर_अघोषित MINIZ_NO_TIME
      #समावेश <utime.h>
    #पूर्ण_अगर
    #घोषणा MZ_FILE खाता
    #घोषणा MZ_FOPEN(f, m) ख_खोलो(f, m)
    #घोषणा MZ_FCLOSE ख_बंद
    #घोषणा MZ_FREAD ख_पढ़ो
    #घोषणा MZ_FWRITE ख_डालो
    #घोषणा MZ_FTELL64 ftello
    #घोषणा MZ_FSEEK64 fseeko
    #घोषणा MZ_FILE_STAT_STRUCT stat
    #घोषणा MZ_FILE_STAT stat
    #घोषणा MZ_FFLUSH ख_साफ
    #घोषणा MZ_FREOPEN(f, m, s) ख_व_खोलो(f, m, s)
    #घोषणा MZ_DELETE_FILE हटाओ
  #पूर्ण_अगर // #ifdef _MSC_VER
#पूर्ण_अगर // #ifdef MINIZ_NO_STDIO

#घोषणा MZ_TOLOWER(c) ((((c) >= 'A') && ((c) <= 'Z')) ? ((c) - 'A' + 'a') : (c))

// Various ZIP archive enums. To completely avoid cross platform compiler alignment and platform endian issues, miniz.c doesn't use structs for any of this stuff.
क्रमागत
{
  // ZIP archive identifiers and record sizes
  MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIG = 0x06054b50, MZ_ZIP_CENTRAL_DIR_HEADER_SIG = 0x02014b50, MZ_ZIP_LOCAL_DIR_HEADER_SIG = 0x04034b50,
  MZ_ZIP_LOCAL_DIR_HEADER_आकार = 30, MZ_ZIP_CENTRAL_DIR_HEADER_आकार = 46, MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_आकार = 22,
  // Central directory header record offsets
  MZ_ZIP_CDH_SIG_OFS = 0, MZ_ZIP_CDH_VERSION_MADE_BY_OFS = 4, MZ_ZIP_CDH_VERSION_NEEDED_OFS = 6, MZ_ZIP_CDH_BIT_FLAG_OFS = 8,
  MZ_ZIP_CDH_METHOD_OFS = 10, MZ_ZIP_CDH_FILE_TIME_OFS = 12, MZ_ZIP_CDH_FILE_DATE_OFS = 14, MZ_ZIP_CDH_CRC32_OFS = 16,
  MZ_ZIP_CDH_COMPRESSED_आकार_OFS = 20, MZ_ZIP_CDH_DECOMPRESSED_आकार_OFS = 24, MZ_ZIP_CDH_FILENAME_LEN_OFS = 28, MZ_ZIP_CDH_EXTRA_LEN_OFS = 30,
  MZ_ZIP_CDH_COMMENT_LEN_OFS = 32, MZ_ZIP_CDH_DISK_START_OFS = 34, MZ_ZIP_CDH_INTERNAL_ATTR_OFS = 36, MZ_ZIP_CDH_EXTERNAL_ATTR_OFS = 38, MZ_ZIP_CDH_LOCAL_HEADER_OFS = 42,
  // Local directory header offsets
  MZ_ZIP_LDH_SIG_OFS = 0, MZ_ZIP_LDH_VERSION_NEEDED_OFS = 4, MZ_ZIP_LDH_BIT_FLAG_OFS = 6, MZ_ZIP_LDH_METHOD_OFS = 8, MZ_ZIP_LDH_FILE_TIME_OFS = 10,
  MZ_ZIP_LDH_FILE_DATE_OFS = 12, MZ_ZIP_LDH_CRC32_OFS = 14, MZ_ZIP_LDH_COMPRESSED_आकार_OFS = 18, MZ_ZIP_LDH_DECOMPRESSED_आकार_OFS = 22,
  MZ_ZIP_LDH_FILENAME_LEN_OFS = 26, MZ_ZIP_LDH_EXTRA_LEN_OFS = 28,
  // End of central directory offsets
  MZ_ZIP_ECDH_SIG_OFS = 0, MZ_ZIP_ECDH_अंक_THIS_DISK_OFS = 4, MZ_ZIP_ECDH_अंक_DISK_CDIR_OFS = 6, MZ_ZIP_ECDH_CDIR_अंक_ENTRIES_ON_DISK_OFS = 8,
  MZ_ZIP_ECDH_CDIR_योग_ENTRIES_OFS = 10, MZ_ZIP_ECDH_CDIR_आकार_OFS = 12, MZ_ZIP_ECDH_CDIR_OFS_OFS = 16, MZ_ZIP_ECDH_COMMENT_आकार_OFS = 20,
};

प्रकार काष्ठा
{
  व्योम *m_p;
  माप_प्रकार m_आकार, m_capacity;
  mz_uint m_element_आकार;
} mz_zip_array;

काष्ठा mz_zip_internal_state_tag
{
  mz_zip_array m_central_dir;
  mz_zip_array m_central_dir_offsets;
  mz_zip_array m_sorted_central_dir_offsets;
  MZ_FILE *m_pFile;
  व्योम *m_pMem;
  माप_प्रकार m_mem_आकार;
  माप_प्रकार m_mem_capacity;
};

#घोषणा MZ_ZIP_ARRAY_SET_ELEMENT_आकार(array_ptr, element_आकार) (array_ptr)->m_element_आकार = element_आकार
#घोषणा MZ_ZIP_ARRAY_ELEMENT(array_ptr, element_type, सूचकांक) ((element_type *)((array_ptr)->m_p))[सूचकांक]

अटल MZ_FORCEINLINE व्योम mz_zip_array_clear(mz_zip_archive *pZip, mz_zip_array *pArray)
{
  pZip->m_pFree(pZip->m_pAlloc_opaque, pArray->m_p);
  स_रखो(pArray, 0, माप(mz_zip_array));
}

अटल mz_bool mz_zip_array_ensure_capacity(mz_zip_archive *pZip, mz_zip_array *pArray, माप_प्रकार min_new_capacity, mz_uint growing)
{
  व्योम *pNew_p; माप_प्रकार new_capacity = min_new_capacity; MZ_ASSERT(pArray->m_element_आकार); अगर (pArray->m_capacity >= min_new_capacity) वापस MZ_TRUE;
  अगर (growing) { new_capacity = MZ_MAX(1, pArray->m_capacity); जबतक (new_capacity < min_new_capacity) new_capacity *= 2; }
  अगर (शून्य == (pNew_p = pZip->m_pRealloc(pZip->m_pAlloc_opaque, pArray->m_p, pArray->m_element_आकार, new_capacity))) वापस MZ_FALSE;
  pArray->m_p = pNew_p; pArray->m_capacity = new_capacity;
  वापस MZ_TRUE;
}

अटल MZ_FORCEINLINE mz_bool mz_zip_array_reserve(mz_zip_archive *pZip, mz_zip_array *pArray, माप_प्रकार new_capacity, mz_uint growing)
{
  अगर (new_capacity > pArray->m_capacity) { अगर (!mz_zip_array_ensure_capacity(pZip, pArray, new_capacity, growing)) वापस MZ_FALSE; }
  वापस MZ_TRUE;
}

अटल MZ_FORCEINLINE mz_bool mz_zip_array_resize(mz_zip_archive *pZip, mz_zip_array *pArray, माप_प्रकार new_आकार, mz_uint growing)
{
  अगर (new_आकार > pArray->m_capacity) { अगर (!mz_zip_array_ensure_capacity(pZip, pArray, new_आकार, growing)) वापस MZ_FALSE; }
  pArray->m_आकार = new_आकार;
  वापस MZ_TRUE;
}

अटल MZ_FORCEINLINE mz_bool mz_zip_array_ensure_room(mz_zip_archive *pZip, mz_zip_array *pArray, माप_प्रकार n)
{
  वापस mz_zip_array_reserve(pZip, pArray, pArray->m_आकार + n, MZ_TRUE);
}

अटल MZ_FORCEINLINE mz_bool mz_zip_array_धकेलो_back(mz_zip_archive *pZip, mz_zip_array *pArray, स्थिर व्योम *pElements, माप_प्रकार n)
{
  माप_प्रकार orig_आकार = pArray->m_आकार; अगर (!mz_zip_array_resize(pZip, pArray, orig_आकार + n, MZ_TRUE)) वापस MZ_FALSE;
  स_नकल((mz_uint8*)pArray->m_p + orig_आकार * pArray->m_element_आकार, pElements, n * pArray->m_element_आकार);
  वापस MZ_TRUE;
}

#अगर_अघोषित MINIZ_NO_TIME
अटल समय_प्रकार mz_zip_dos_to_time_t(पूर्णांक dos_time, पूर्णांक dos_date)
{
  काष्ठा पंचांग पंचांग;
  स_रखो(&पंचांग, 0, माप(पंचांग)); पंचांग.tm_isdst = -1;
  पंचांग.tm_year = ((dos_date >> 9) & 127) + 1980 - 1900; पंचांग.tm_mon = ((dos_date >> 5) & 15) - 1; पंचांग.tm_mday = dos_date & 31;
  पंचांग.tm_hour = (dos_time >> 11) & 31; पंचांग.tm_min = (dos_time >> 5) & 63; पंचांग.tm_sec = (dos_time << 1) & 62;
  वापस स_गढ़ो(&पंचांग);
}

अटल व्योम mz_zip_time_to_dos_time(समय_प्रकार समय, mz_uint16 *pDOS_time, mz_uint16 *pDOS_date)
{
#अगर_घोषित _MSC_VER
  काष्ठा पंचांग tm_struct;
  काष्ठा पंचांग *पंचांग = &tm_struct;
  errno_t err = localtime_s(पंचांग, &समय);
  अगर (err)
  {
    *pDOS_date = 0; *pDOS_time = 0;
    वापस;
  }
#अन्यथा
  काष्ठा पंचांग *पंचांग = स_स्थानीय(&समय);
#पूर्ण_अगर
  *pDOS_time = (mz_uint16)(((पंचांग->tm_hour) << 11) + ((पंचांग->tm_min) << 5) + ((पंचांग->tm_sec) >> 1));
  *pDOS_date = (mz_uint16)(((पंचांग->tm_year + 1900 - 1980) << 9) + ((पंचांग->tm_mon + 1) << 5) + पंचांग->tm_mday);
}
#पूर्ण_अगर

#अगर_अघोषित MINIZ_NO_STDIO
अटल mz_bool mz_zip_get_file_modified_time(स्थिर अक्षर *pFilename, mz_uint16 *pDOS_time, mz_uint16 *pDOS_date)
{
#अगर_घोषित MINIZ_NO_TIME
  (व्योम)pFilename; *pDOS_date = *pDOS_time = 0;
#अन्यथा
  काष्ठा MZ_FILE_STAT_STRUCT file_stat;
  // On Linux with x86 glibc, this call will fail on large files (>= 0x80000000 bytes) unless you compiled with _LARGEFILE64_SOURCE. Argh.
  अगर (MZ_FILE_STAT(pFilename, &file_stat) != 0)
    वापस MZ_FALSE;
  mz_zip_time_to_dos_time(file_stat.st_mtime, pDOS_time, pDOS_date);
#पूर्ण_अगर // #ifdef MINIZ_NO_TIME
  वापस MZ_TRUE;
}

#अगर_अघोषित MINIZ_NO_TIME
अटल mz_bool mz_zip_set_file_times(स्थिर अक्षर *pFilename, समय_प्रकार access_time, समय_प्रकार modified_time)
{
  काष्ठा utimbuf t; t.actime = access_time; t.modtime = modified_time;
  वापस !utime(pFilename, &t);
}
#पूर्ण_अगर // #ifndef MINIZ_NO_TIME
#पूर्ण_अगर // #ifndef MINIZ_NO_STDIO

अटल mz_bool mz_zip_reader_init_internal(mz_zip_archive *pZip, mz_uint32 flags)
{
  (व्योम)flags;
  अगर ((!pZip) || (pZip->m_pState) || (pZip->m_zip_mode != MZ_ZIP_MODE_INVALID))
    वापस MZ_FALSE;

  अगर (!pZip->m_pAlloc) pZip->m_pAlloc = def_alloc_func;
  अगर (!pZip->m_pFree) pZip->m_pFree = def_free_func;
  अगर (!pZip->m_pRealloc) pZip->m_pRealloc = def_realloc_func;

  pZip->m_zip_mode = MZ_ZIP_MODE_READING;
  pZip->m_archive_आकार = 0;
  pZip->m_central_directory_file_ofs = 0;
  pZip->m_योग_files = 0;

  अगर (शून्य == (pZip->m_pState = (mz_zip_internal_state *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, माप(mz_zip_internal_state))))
    वापस MZ_FALSE;
  स_रखो(pZip->m_pState, 0, माप(mz_zip_internal_state));
  MZ_ZIP_ARRAY_SET_ELEMENT_आकार(&pZip->m_pState->m_central_dir, माप(mz_uint8));
  MZ_ZIP_ARRAY_SET_ELEMENT_आकार(&pZip->m_pState->m_central_dir_offsets, माप(mz_uint32));
  MZ_ZIP_ARRAY_SET_ELEMENT_आकार(&pZip->m_pState->m_sorted_central_dir_offsets, माप(mz_uint32));
  वापस MZ_TRUE;
}

अटल MZ_FORCEINLINE mz_bool mz_zip_reader_filename_less(स्थिर mz_zip_array *pCentral_dir_array, स्थिर mz_zip_array *pCentral_dir_offsets, mz_uint l_सूचकांक, mz_uint r_सूचकांक)
{
  स्थिर mz_uint8 *pL = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, l_सूचकांक)), *pE;
  स्थिर mz_uint8 *pR = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, r_सूचकांक));
  mz_uint l_len = MZ_READ_LE16(pL + MZ_ZIP_CDH_FILENAME_LEN_OFS), r_len = MZ_READ_LE16(pR + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  mz_uint8 l = 0, r = 0;
  pL += MZ_ZIP_CENTRAL_DIR_HEADER_आकार; pR += MZ_ZIP_CENTRAL_DIR_HEADER_आकार;
  pE = pL + MZ_MIN(l_len, r_len);
  जबतक (pL < pE)
  {
    अगर ((l = MZ_TOLOWER(*pL)) != (r = MZ_TOLOWER(*pR)))
      अवरोध;
    pL++; pR++;
  }
  वापस (pL == pE) ? (l_len < r_len) : (l < r);
}

#घोषणा MZ_SWAP_UINT32(a, b) करो { mz_uint32 t = a; a = b; b = t; } MZ_MACRO_END

// Heap sort of lowercased filenames, used to help accelerate plain central directory searches by mz_zip_reader_locate_file(). (Could also use qsort(), but it could allocate memory.)
अटल व्योम mz_zip_reader_sort_central_dir_offsets_by_filename(mz_zip_archive *pZip)
{
  mz_zip_internal_state *pState = pZip->m_pState;
  स्थिर mz_zip_array *pCentral_dir_offsets = &pState->m_central_dir_offsets;
  स्थिर mz_zip_array *pCentral_dir = &pState->m_central_dir;
  mz_uint32 *pIndices = &MZ_ZIP_ARRAY_ELEMENT(&pState->m_sorted_central_dir_offsets, mz_uint32, 0);
  स्थिर पूर्णांक आकार = pZip->m_योग_files;
  पूर्णांक start = (आकार - 2) >> 1, end;
  जबतक (start >= 0)
  {
    पूर्णांक child, मूल = start;
    क्रम ( ; ; )
    {
      अगर ((child = (मूल << 1) + 1) >= आकार)
        अवरोध;
      child += (((child + 1) < आकार) && (mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[child], pIndices[child + 1])));
      अगर (!mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[मूल], pIndices[child]))
        अवरोध;
      MZ_SWAP_UINT32(pIndices[मूल], pIndices[child]); मूल = child;
    }
    start--;
  }

  end = आकार - 1;
  जबतक (end > 0)
  {
    पूर्णांक child, मूल = 0;
    MZ_SWAP_UINT32(pIndices[end], pIndices[0]);
    क्रम ( ; ; )
    {
      अगर ((child = (मूल << 1) + 1) >= end)
        अवरोध;
      child += (((child + 1) < end) && mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[child], pIndices[child + 1]));
      अगर (!mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[मूल], pIndices[child]))
        अवरोध;
      MZ_SWAP_UINT32(pIndices[मूल], pIndices[child]); मूल = child;
    }
    end--;
  }
}

अटल mz_bool mz_zip_reader_read_central_dir(mz_zip_archive *pZip, mz_uint32 flags)
{
  mz_uint cdir_आकार, अंक_this_disk, cdir_disk_सूचकांक;
  mz_uint64 cdir_ofs;
  mz_int64 cur_file_ofs;
  स्थिर mz_uint8 *p;
  mz_uint32 buf_u32[4096 / माप(mz_uint32)]; mz_uint8 *pBuf = (mz_uint8 *)buf_u32;
  mz_bool sort_central_dir = ((flags & MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY) == 0);
  // Basic sanity checks - reject files which are too small, and check the first 4 bytes of the file to make sure a local header is there.
  अगर (pZip->m_archive_आकार < MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_आकार)
    वापस MZ_FALSE;
  // Find the end of central directory record by scanning the file from the end towards the beginning.
  cur_file_ofs = MZ_MAX((mz_int64)pZip->m_archive_आकार - (mz_int64)माप(buf_u32), 0);
  क्रम ( ; ; )
  {
    पूर्णांक i, n = (पूर्णांक)MZ_MIN(माप(buf_u32), pZip->m_archive_आकार - cur_file_ofs);
    अगर (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, n) != (mz_uint)n)
      वापस MZ_FALSE;
    क्रम (i = n - 4; i >= 0; --i)
      अगर (MZ_READ_LE32(pBuf + i) == MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIG)
        अवरोध;
    अगर (i >= 0)
    {
      cur_file_ofs += i;
      अवरोध;
    }
    अगर ((!cur_file_ofs) || ((pZip->m_archive_आकार - cur_file_ofs) >= (0xFFFF + MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_आकार)))
      वापस MZ_FALSE;
    cur_file_ofs = MZ_MAX(cur_file_ofs - (माप(buf_u32) - 3), 0);
  }
  // Read and verify the end of central directory record.
  अगर (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_आकार) != MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_आकार)
    वापस MZ_FALSE;
  अगर ((MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_SIG_OFS) != MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIG) ||
      ((pZip->m_योग_files = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_CDIR_योग_ENTRIES_OFS)) != MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_CDIR_अंक_ENTRIES_ON_DISK_OFS)))
    वापस MZ_FALSE;

  अंक_this_disk = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_अंक_THIS_DISK_OFS);
  cdir_disk_सूचकांक = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_अंक_DISK_CDIR_OFS);
  अगर (((अंक_this_disk | cdir_disk_सूचकांक) != 0) && ((अंक_this_disk != 1) || (cdir_disk_सूचकांक != 1)))
    वापस MZ_FALSE;

  अगर ((cdir_आकार = MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_CDIR_आकार_OFS)) < pZip->m_योग_files * MZ_ZIP_CENTRAL_DIR_HEADER_आकार)
    वापस MZ_FALSE;

  cdir_ofs = MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_CDIR_OFS_OFS);
  अगर ((cdir_ofs + (mz_uint64)cdir_आकार) > pZip->m_archive_आकार)
    वापस MZ_FALSE;

  pZip->m_central_directory_file_ofs = cdir_ofs;

  अगर (pZip->m_योग_files)
  {
     mz_uint i, n;

    // Read the entire central directory into a heap block, and allocate another heap block to hold the unsorted central dir file record offsets, and another to hold the sorted indices.
    अगर ((!mz_zip_array_resize(pZip, &pZip->m_pState->m_central_dir, cdir_आकार, MZ_FALSE)) ||
        (!mz_zip_array_resize(pZip, &pZip->m_pState->m_central_dir_offsets, pZip->m_योग_files, MZ_FALSE)))
      वापस MZ_FALSE;

    अगर (sort_central_dir)
    {
      अगर (!mz_zip_array_resize(pZip, &pZip->m_pState->m_sorted_central_dir_offsets, pZip->m_योग_files, MZ_FALSE))
        वापस MZ_FALSE;
    }

    अगर (pZip->m_pRead(pZip->m_pIO_opaque, cdir_ofs, pZip->m_pState->m_central_dir.m_p, cdir_आकार) != cdir_आकार)
      वापस MZ_FALSE;

    // Now create an index into the central directory file records, do some basic sanity checking on each record, and check for zip64 entries (which are not yet supported).
    p = (स्थिर mz_uint8 *)pZip->m_pState->m_central_dir.m_p;
    क्रम (n = cdir_आकार, i = 0; i < pZip->m_योग_files; ++i)
    {
      mz_uint योग_header_आकार, comp_आकार, decomp_आकार, disk_सूचकांक;
      अगर ((n < MZ_ZIP_CENTRAL_DIR_HEADER_आकार) || (MZ_READ_LE32(p) != MZ_ZIP_CENTRAL_DIR_HEADER_SIG))
        वापस MZ_FALSE;
      MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, i) = (mz_uint32)(p - (स्थिर mz_uint8 *)pZip->m_pState->m_central_dir.m_p);
      अगर (sort_central_dir)
        MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_sorted_central_dir_offsets, mz_uint32, i) = i;
      comp_आकार = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_आकार_OFS);
      decomp_आकार = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_आकार_OFS);
      अगर (((!MZ_READ_LE32(p + MZ_ZIP_CDH_METHOD_OFS)) && (decomp_आकार != comp_आकार)) || (decomp_आकार && !comp_आकार) || (decomp_आकार == 0xFFFFFFFF) || (comp_आकार == 0xFFFFFFFF))
        वापस MZ_FALSE;
      disk_सूचकांक = MZ_READ_LE16(p + MZ_ZIP_CDH_DISK_START_OFS);
      अगर ((disk_सूचकांक != अंक_this_disk) && (disk_सूचकांक != 1))
        वापस MZ_FALSE;
      अगर (((mz_uint64)MZ_READ_LE32(p + MZ_ZIP_CDH_LOCAL_HEADER_OFS) + MZ_ZIP_LOCAL_DIR_HEADER_आकार + comp_आकार) > pZip->m_archive_आकार)
        वापस MZ_FALSE;
      अगर ((योग_header_आकार = MZ_ZIP_CENTRAL_DIR_HEADER_आकार + MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_EXTRA_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_COMMENT_LEN_OFS)) > n)
        वापस MZ_FALSE;
      n -= योग_header_आकार; p += योग_header_आकार;
    }
  }

  अगर (sort_central_dir)
    mz_zip_reader_sort_central_dir_offsets_by_filename(pZip);

  वापस MZ_TRUE;
}

mz_bool mz_zip_reader_init(mz_zip_archive *pZip, mz_uint64 आकार, mz_uint32 flags)
{
  अगर ((!pZip) || (!pZip->m_pRead))
    वापस MZ_FALSE;
  अगर (!mz_zip_reader_init_internal(pZip, flags))
    वापस MZ_FALSE;
  pZip->m_archive_आकार = आकार;
  अगर (!mz_zip_reader_read_central_dir(pZip, flags))
  {
    mz_zip_reader_end(pZip);
    वापस MZ_FALSE;
  }
  वापस MZ_TRUE;
}

अटल माप_प्रकार mz_zip_mem_read_func(व्योम *pOpaque, mz_uint64 file_ofs, व्योम *pBuf, माप_प्रकार n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  माप_प्रकार s = (file_ofs >= pZip->m_archive_आकार) ? 0 : (माप_प्रकार)MZ_MIN(pZip->m_archive_आकार - file_ofs, n);
  स_नकल(pBuf, (स्थिर mz_uint8 *)pZip->m_pState->m_pMem + file_ofs, s);
  वापस s;
}

mz_bool mz_zip_reader_init_mem(mz_zip_archive *pZip, स्थिर व्योम *pMem, माप_प्रकार आकार, mz_uint32 flags)
{
  अगर (!mz_zip_reader_init_internal(pZip, flags))
    वापस MZ_FALSE;
  pZip->m_archive_आकार = आकार;
  pZip->m_pRead = mz_zip_mem_read_func;
  pZip->m_pIO_opaque = pZip;
#अगर_घोषित __cplusplus
  pZip->m_pState->m_pMem = const_cast<व्योम *>(pMem);
#अन्यथा
  pZip->m_pState->m_pMem = (व्योम *)pMem;
#पूर्ण_अगर
  pZip->m_pState->m_mem_आकार = आकार;
  अगर (!mz_zip_reader_read_central_dir(pZip, flags))
  {
    mz_zip_reader_end(pZip);
    वापस MZ_FALSE;
  }
  वापस MZ_TRUE;
}

#अगर_अघोषित MINIZ_NO_STDIO
अटल माप_प्रकार mz_zip_file_read_func(व्योम *pOpaque, mz_uint64 file_ofs, व्योम *pBuf, माप_प्रकार n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_int64 cur_ofs = MZ_FTELL64(pZip->m_pState->m_pFile);
  अगर (((mz_int64)file_ofs < 0) || (((cur_ofs != (mz_int64)file_ofs)) && (MZ_FSEEK64(pZip->m_pState->m_pFile, (mz_int64)file_ofs, शुरू_से))))
    वापस 0;
  वापस MZ_FREAD(pBuf, 1, n, pZip->m_pState->m_pFile);
}

mz_bool mz_zip_reader_init_file(mz_zip_archive *pZip, स्थिर अक्षर *pFilename, mz_uint32 flags)
{
  mz_uint64 file_आकार;
  MZ_FILE *pFile = MZ_FOPEN(pFilename, "rb");
  अगर (!pFile)
    वापस MZ_FALSE;
  अगर (MZ_FSEEK64(pFile, 0, अंत_से))
  {
    MZ_FCLOSE(pFile);
    वापस MZ_FALSE;
  }
  file_आकार = MZ_FTELL64(pFile);
  अगर (!mz_zip_reader_init_internal(pZip, flags))
  {
    MZ_FCLOSE(pFile);
    वापस MZ_FALSE;
  }
  pZip->m_pRead = mz_zip_file_read_func;
  pZip->m_pIO_opaque = pZip;
  pZip->m_pState->m_pFile = pFile;
  pZip->m_archive_आकार = file_आकार;
  अगर (!mz_zip_reader_read_central_dir(pZip, flags))
  {
    mz_zip_reader_end(pZip);
    वापस MZ_FALSE;
  }
  वापस MZ_TRUE;
}
#पूर्ण_अगर // #ifndef MINIZ_NO_STDIO

mz_uint mz_zip_reader_get_अंक_files(mz_zip_archive *pZip)
{
  वापस pZip ? pZip->m_योग_files : 0;
}

अटल MZ_FORCEINLINE स्थिर mz_uint8 *mz_zip_reader_get_cdh(mz_zip_archive *pZip, mz_uint file_सूचकांक)
{
  अगर ((!pZip) || (!pZip->m_pState) || (file_सूचकांक >= pZip->m_योग_files) || (pZip->m_zip_mode != MZ_ZIP_MODE_READING))
    वापस शून्य;
  वापस &MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_सूचकांक));
}

mz_bool mz_zip_reader_is_file_encrypted(mz_zip_archive *pZip, mz_uint file_सूचकांक)
{
  mz_uint m_bit_flag;
  स्थिर mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_सूचकांक);
  अगर (!p)
    वापस MZ_FALSE;
  m_bit_flag = MZ_READ_LE16(p + MZ_ZIP_CDH_BIT_FLAG_OFS);
  वापस (m_bit_flag & 1);
}

mz_bool mz_zip_reader_is_file_a_directory(mz_zip_archive *pZip, mz_uint file_सूचकांक)
{
  mz_uint filename_len, external_attr;
  स्थिर mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_सूचकांक);
  अगर (!p)
    वापस MZ_FALSE;

  // First see if the filename ends with a '/' character.
  filename_len = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  अगर (filename_len)
  {
    अगर (*(p + MZ_ZIP_CENTRAL_DIR_HEADER_आकार + filename_len - 1) == '/')
      वापस MZ_TRUE;
  }

  // Bugfix: This code was also checking if the internal attribute was non-zero, which wasn't correct.
  // Most/all zip writers (hopefully) set DOS file/directory attributes in the low 16-bits, so check for the DOS directory flag and ignore the source OS ID in the created by field.
  // FIXME: Remove this check? Is it necessary - we already check the filename.
  external_attr = MZ_READ_LE32(p + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS);
  अगर ((external_attr & 0x10) != 0)
    वापस MZ_TRUE;

  वापस MZ_FALSE;
}

mz_bool mz_zip_reader_file_stat(mz_zip_archive *pZip, mz_uint file_सूचकांक, mz_zip_archive_file_stat *pStat)
{
  mz_uint n;
  स्थिर mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_सूचकांक);
  अगर ((!p) || (!pStat))
    वापस MZ_FALSE;

  // Unpack the central directory record.
  pStat->m_file_सूचकांक = file_सूचकांक;
  pStat->m_central_dir_ofs = MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_सूचकांक);
  pStat->m_version_made_by = MZ_READ_LE16(p + MZ_ZIP_CDH_VERSION_MADE_BY_OFS);
  pStat->m_version_needed = MZ_READ_LE16(p + MZ_ZIP_CDH_VERSION_NEEDED_OFS);
  pStat->m_bit_flag = MZ_READ_LE16(p + MZ_ZIP_CDH_BIT_FLAG_OFS);
  pStat->m_method = MZ_READ_LE16(p + MZ_ZIP_CDH_METHOD_OFS);
#अगर_अघोषित MINIZ_NO_TIME
  pStat->m_time = mz_zip_dos_to_time_t(MZ_READ_LE16(p + MZ_ZIP_CDH_FILE_TIME_OFS), MZ_READ_LE16(p + MZ_ZIP_CDH_FILE_DATE_OFS));
#पूर्ण_अगर
  pStat->m_crc32 = MZ_READ_LE32(p + MZ_ZIP_CDH_CRC32_OFS);
  pStat->m_comp_आकार = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_आकार_OFS);
  pStat->m_uncomp_आकार = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_आकार_OFS);
  pStat->m_internal_attr = MZ_READ_LE16(p + MZ_ZIP_CDH_INTERNAL_ATTR_OFS);
  pStat->m_external_attr = MZ_READ_LE32(p + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS);
  pStat->m_local_header_ofs = MZ_READ_LE32(p + MZ_ZIP_CDH_LOCAL_HEADER_OFS);

  // Copy as much of the filename and comment as possible.
  n = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS); n = MZ_MIN(n, MZ_ZIP_MAX_ARCHIVE_FILENAME_आकार - 1);
  स_नकल(pStat->m_filename, p + MZ_ZIP_CENTRAL_DIR_HEADER_आकार, n); pStat->m_filename[n] = '\0';

  n = MZ_READ_LE16(p + MZ_ZIP_CDH_COMMENT_LEN_OFS); n = MZ_MIN(n, MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_आकार - 1);
  pStat->m_comment_आकार = n;
  स_नकल(pStat->m_comment, p + MZ_ZIP_CENTRAL_DIR_HEADER_आकार + MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_EXTRA_LEN_OFS), n); pStat->m_comment[n] = '\0';

  वापस MZ_TRUE;
}

mz_uint mz_zip_reader_get_filename(mz_zip_archive *pZip, mz_uint file_सूचकांक, अक्षर *pFilename, mz_uint filename_buf_आकार)
{
  mz_uint n;
  स्थिर mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_सूचकांक);
  अगर (!p) { अगर (filename_buf_आकार) pFilename[0] = '\0'; वापस 0; }
  n = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  अगर (filename_buf_आकार)
  {
    n = MZ_MIN(n, filename_buf_आकार - 1);
    स_नकल(pFilename, p + MZ_ZIP_CENTRAL_DIR_HEADER_आकार, n);
    pFilename[n] = '\0';
  }
  वापस n + 1;
}

अटल MZ_FORCEINLINE mz_bool mz_zip_reader_string_equal(स्थिर अक्षर *pA, स्थिर अक्षर *pB, mz_uint len, mz_uint flags)
{
  mz_uint i;
  अगर (flags & MZ_ZIP_FLAG_CASE_SENSITIVE)
    वापस 0 == स_भेद(pA, pB, len);
  क्रम (i = 0; i < len; ++i)
    अगर (MZ_TOLOWER(pA[i]) != MZ_TOLOWER(pB[i]))
      वापस MZ_FALSE;
  वापस MZ_TRUE;
}

अटल MZ_FORCEINLINE पूर्णांक mz_zip_reader_filename_compare(स्थिर mz_zip_array *pCentral_dir_array, स्थिर mz_zip_array *pCentral_dir_offsets, mz_uint l_सूचकांक, स्थिर अक्षर *pR, mz_uint r_len)
{
  स्थिर mz_uint8 *pL = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, l_सूचकांक)), *pE;
  mz_uint l_len = MZ_READ_LE16(pL + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  mz_uint8 l = 0, r = 0;
  pL += MZ_ZIP_CENTRAL_DIR_HEADER_आकार;
  pE = pL + MZ_MIN(l_len, r_len);
  जबतक (pL < pE)
  {
    अगर ((l = MZ_TOLOWER(*pL)) != (r = MZ_TOLOWER(*pR)))
      अवरोध;
    pL++; pR++;
  }
  वापस (pL == pE) ? (पूर्णांक)(l_len - r_len) : (l - r);
}

अटल पूर्णांक mz_zip_reader_locate_file_द्विआधारी_खोज(mz_zip_archive *pZip, स्थिर अक्षर *pFilename)
{
  mz_zip_internal_state *pState = pZip->m_pState;
  स्थिर mz_zip_array *pCentral_dir_offsets = &pState->m_central_dir_offsets;
  स्थिर mz_zip_array *pCentral_dir = &pState->m_central_dir;
  mz_uint32 *pIndices = &MZ_ZIP_ARRAY_ELEMENT(&pState->m_sorted_central_dir_offsets, mz_uint32, 0);
  स्थिर पूर्णांक आकार = pZip->m_योग_files;
  स्थिर mz_uint filename_len = (mz_uint)म_माप(pFilename);
  पूर्णांक l = 0, h = आकार - 1;
  जबतक (l <= h)
  {
    पूर्णांक m = (l + h) >> 1, file_सूचकांक = pIndices[m], comp = mz_zip_reader_filename_compare(pCentral_dir, pCentral_dir_offsets, file_सूचकांक, pFilename, filename_len);
    अगर (!comp)
      वापस file_सूचकांक;
    अन्यथा अगर (comp < 0)
      l = m + 1;
    अन्यथा
      h = m - 1;
  }
  वापस -1;
}

पूर्णांक mz_zip_reader_locate_file(mz_zip_archive *pZip, स्थिर अक्षर *pName, स्थिर अक्षर *pComment, mz_uint flags)
{
  mz_uint file_सूचकांक; माप_प्रकार name_len, comment_len;
  अगर ((!pZip) || (!pZip->m_pState) || (!pName) || (pZip->m_zip_mode != MZ_ZIP_MODE_READING))
    वापस -1;
  अगर (((flags & (MZ_ZIP_FLAG_IGNORE_PATH | MZ_ZIP_FLAG_CASE_SENSITIVE)) == 0) && (!pComment) && (pZip->m_pState->m_sorted_central_dir_offsets.m_आकार))
    वापस mz_zip_reader_locate_file_द्विआधारी_खोज(pZip, pName);
  name_len = म_माप(pName); अगर (name_len > 0xFFFF) वापस -1;
  comment_len = pComment ? म_माप(pComment) : 0; अगर (comment_len > 0xFFFF) वापस -1;
  क्रम (file_सूचकांक = 0; file_सूचकांक < pZip->m_योग_files; file_सूचकांक++)
  {
    स्थिर mz_uint8 *pHeader = &MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_सूचकांक));
    mz_uint filename_len = MZ_READ_LE16(pHeader + MZ_ZIP_CDH_FILENAME_LEN_OFS);
    स्थिर अक्षर *pFilename = (स्थिर अक्षर *)pHeader + MZ_ZIP_CENTRAL_DIR_HEADER_आकार;
    अगर (filename_len < name_len)
      जारी;
    अगर (comment_len)
    {
      mz_uint file_extra_len = MZ_READ_LE16(pHeader + MZ_ZIP_CDH_EXTRA_LEN_OFS), file_comment_len = MZ_READ_LE16(pHeader + MZ_ZIP_CDH_COMMENT_LEN_OFS);
      स्थिर अक्षर *pFile_comment = pFilename + filename_len + file_extra_len;
      अगर ((file_comment_len != comment_len) || (!mz_zip_reader_string_equal(pComment, pFile_comment, file_comment_len, flags)))
        जारी;
    }
    अगर ((flags & MZ_ZIP_FLAG_IGNORE_PATH) && (filename_len))
    {
      पूर्णांक ofs = filename_len - 1;
      करो
      {
        अगर ((pFilename[ofs] == '/') || (pFilename[ofs] == '\\') || (pFilename[ofs] == ':'))
          अवरोध;
      } जबतक (--ofs >= 0);
      ofs++;
      pFilename += ofs; filename_len -= ofs;
    }
    अगर ((filename_len == name_len) && (mz_zip_reader_string_equal(pName, pFilename, filename_len, flags)))
      वापस file_सूचकांक;
  }
  वापस -1;
}

mz_bool mz_zip_reader_extract_to_mem_no_alloc(mz_zip_archive *pZip, mz_uint file_सूचकांक, व्योम *pBuf, माप_प्रकार buf_आकार_2, mz_uint flags, व्योम *pUser_read_buf, माप_प्रकार user_read_buf_आकार)
{
  पूर्णांक status = TINFL_STATUS_DONE;
  mz_uint64 needed_आकार, cur_file_ofs, comp_remaining, out_buf_ofs = 0, read_buf_आकार, read_buf_ofs = 0, read_buf_avail;
  mz_zip_archive_file_stat file_stat;
  व्योम *pRead_buf;
  mz_uint32 local_header_u32[(MZ_ZIP_LOCAL_DIR_HEADER_आकार + माप(mz_uint32) - 1) / माप(mz_uint32)]; mz_uint8 *pLocal_header = (mz_uint8 *)local_header_u32;
  tinfl_decompressor inflator;

  अगर ((buf_आकार_2) && (!pBuf))
    वापस MZ_FALSE;

  अगर (!mz_zip_reader_file_stat(pZip, file_सूचकांक, &file_stat))
    वापस MZ_FALSE;

  // Empty file, or a directory (but not always a directory - I've seen odd zips with directories that have compressed data which inflates to 0 bytes)
  अगर (!file_stat.m_comp_आकार)
    वापस MZ_TRUE;

  // Entry is a subdirectory (I've seen old zips with dir entries which have compressed deflate data which inflates to 0 bytes, but these entries claim to uncompress to 512 bytes in the headers).
  // I'm torn how to handle this case - should it fail instead?
  अगर (mz_zip_reader_is_file_a_directory(pZip, file_सूचकांक))
    वापस MZ_TRUE;

  // Encryption and patch files are not supported.
  अगर (file_stat.m_bit_flag & (1 | 32))
    वापस MZ_FALSE;

  // This function only supports stored and deflate.
  अगर ((!(flags & MZ_ZIP_FLAG_COMPRESSED_तथ्य)) && (file_stat.m_method != 0) && (file_stat.m_method != MZ_DEFLATED))
    वापस MZ_FALSE;

  // Ensure supplied output buffer is large enough.
  needed_आकार = (flags & MZ_ZIP_FLAG_COMPRESSED_तथ्य) ? file_stat.m_comp_आकार : file_stat.m_uncomp_आकार;
  अगर (buf_आकार_2 < needed_आकार)
    वापस MZ_FALSE;

  // Read and parse the local directory entry.
  cur_file_ofs = file_stat.m_local_header_ofs;
  अगर (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pLocal_header, MZ_ZIP_LOCAL_DIR_HEADER_आकार) != MZ_ZIP_LOCAL_DIR_HEADER_आकार)
    वापस MZ_FALSE;
  अगर (MZ_READ_LE32(pLocal_header) != MZ_ZIP_LOCAL_DIR_HEADER_SIG)
    वापस MZ_FALSE;

  cur_file_ofs += MZ_ZIP_LOCAL_DIR_HEADER_आकार + MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  अगर ((cur_file_ofs + file_stat.m_comp_आकार) > pZip->m_archive_आकार)
    वापस MZ_FALSE;

  अगर ((flags & MZ_ZIP_FLAG_COMPRESSED_तथ्य) || (!file_stat.m_method))
  {
    // The file is stored or the caller has requested the compressed data.
    अगर (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, (माप_प्रकार)needed_आकार) != needed_आकार)
      वापस MZ_FALSE;
    वापस ((flags & MZ_ZIP_FLAG_COMPRESSED_तथ्य) != 0) || (mz_crc32(MZ_CRC32_INIT, (स्थिर mz_uint8 *)pBuf, (माप_प्रकार)file_stat.m_uncomp_आकार) == file_stat.m_crc32);
  }

  // Decompress the file either directly from memory or from a file input buffer.
  tinfl_init(&inflator);

  अगर (pZip->m_pState->m_pMem)
  {
    // Read directly from the archive in memory.
    pRead_buf = (mz_uint8 *)pZip->m_pState->m_pMem + cur_file_ofs;
    read_buf_आकार = read_buf_avail = file_stat.m_comp_आकार;
    comp_remaining = 0;
  }
  अन्यथा अगर (pUser_read_buf)
  {
    // Use a user provided read buffer.
    अगर (!user_read_buf_आकार)
      वापस MZ_FALSE;
    pRead_buf = (mz_uint8 *)pUser_read_buf;
    read_buf_आकार = user_read_buf_आकार;
    read_buf_avail = 0;
    comp_remaining = file_stat.m_comp_आकार;
  }
  अन्यथा
  {
    // Temporarily allocate a read buffer.
    read_buf_आकार = MZ_MIN(file_stat.m_comp_आकार, MZ_ZIP_MAX_IO_BUF_आकार);
#अगर_घोषित _MSC_VER
    अगर (((0, माप(माप_प्रकार) == माप(mz_uint32))) && (read_buf_आकार > 0x7FFFFFFF))
#अन्यथा
    अगर (((माप(माप_प्रकार) == माप(mz_uint32))) && (read_buf_आकार > 0x7FFFFFFF))
#पूर्ण_अगर
      वापस MZ_FALSE;
    अगर (शून्य == (pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (माप_प्रकार)read_buf_आकार)))
      वापस MZ_FALSE;
    read_buf_avail = 0;
    comp_remaining = file_stat.m_comp_आकार;
  }

  करो
  {
    माप_प्रकार in_buf_आकार, out_buf_आकार = (माप_प्रकार)(file_stat.m_uncomp_आकार - out_buf_ofs);
    अगर ((!read_buf_avail) && (!pZip->m_pState->m_pMem))
    {
      read_buf_avail = MZ_MIN(read_buf_आकार, comp_remaining);
      अगर (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (माप_प्रकार)read_buf_avail) != read_buf_avail)
      {
        status = TINFL_STATUS_FAILED;
        अवरोध;
      }
      cur_file_ofs += read_buf_avail;
      comp_remaining -= read_buf_avail;
      read_buf_ofs = 0;
    }
    in_buf_आकार = (माप_प्रकार)read_buf_avail;
    status = tinfl_decompress(&inflator, (mz_uint8 *)pRead_buf + read_buf_ofs, &in_buf_आकार, (mz_uint8 *)pBuf, (mz_uint8 *)pBuf + out_buf_ofs, &out_buf_आकार, TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF | (comp_remaining ? TINFL_FLAG_HAS_MORE_निवेश : 0));
    read_buf_avail -= in_buf_आकार;
    read_buf_ofs += in_buf_आकार;
    out_buf_ofs += out_buf_आकार;
  } जबतक (status == TINFL_STATUS_NEEDS_MORE_निवेश);

  अगर (status == TINFL_STATUS_DONE)
  {
    // Make sure the entire file was decompressed, and check its CRC.
    अगर ((out_buf_ofs != file_stat.m_uncomp_आकार) || (mz_crc32(MZ_CRC32_INIT, (स्थिर mz_uint8 *)pBuf, (माप_प्रकार)file_stat.m_uncomp_आकार) != file_stat.m_crc32))
      status = TINFL_STATUS_FAILED;
  }

  अगर ((!pZip->m_pState->m_pMem) && (!pUser_read_buf))
    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);

  वापस status == TINFL_STATUS_DONE;
}

mz_bool mz_zip_reader_extract_file_to_mem_no_alloc(mz_zip_archive *pZip, स्थिर अक्षर *pFilename, व्योम *pBuf, माप_प्रकार buf_आकार_2, mz_uint flags, व्योम *pUser_read_buf, माप_प्रकार user_read_buf_आकार)
{
  पूर्णांक file_सूचकांक = mz_zip_reader_locate_file(pZip, pFilename, शून्य, flags);
  अगर (file_सूचकांक < 0)
    वापस MZ_FALSE;
  वापस mz_zip_reader_extract_to_mem_no_alloc(pZip, file_सूचकांक, pBuf, buf_आकार_2, flags, pUser_read_buf, user_read_buf_आकार);
}

mz_bool mz_zip_reader_extract_to_mem(mz_zip_archive *pZip, mz_uint file_सूचकांक, व्योम *pBuf, माप_प्रकार buf_आकार_2, mz_uint flags)
{
  वापस mz_zip_reader_extract_to_mem_no_alloc(pZip, file_सूचकांक, pBuf, buf_आकार_2, flags, शून्य, 0);
}

mz_bool mz_zip_reader_extract_file_to_mem(mz_zip_archive *pZip, स्थिर अक्षर *pFilename, व्योम *pBuf, माप_प्रकार buf_आकार_2, mz_uint flags)
{
  वापस mz_zip_reader_extract_file_to_mem_no_alloc(pZip, pFilename, pBuf, buf_आकार_2, flags, शून्य, 0);
}

व्योम *mz_zip_reader_extract_to_heap(mz_zip_archive *pZip, mz_uint file_सूचकांक, माप_प्रकार *p_आकार, mz_uint flags)
{
  mz_uint64 comp_आकार, uncomp_आकार, alloc_आकार_2;
  स्थिर mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_सूचकांक);
  व्योम *pBuf;

  अगर (p_आकार)
    *p_आकार = 0;
  अगर (!p)
    वापस शून्य;

  comp_आकार = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_आकार_OFS);
  uncomp_आकार = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_आकार_OFS);

  alloc_आकार_2 = (flags & MZ_ZIP_FLAG_COMPRESSED_तथ्य) ? comp_आकार : uncomp_आकार;
#अगर_घोषित _MSC_VER
  अगर (((0, माप(माप_प्रकार) == माप(mz_uint32))) && (alloc_आकार_2 > 0x7FFFFFFF))
#अन्यथा
  अगर (((माप(माप_प्रकार) == माप(mz_uint32))) && (alloc_आकार_2 > 0x7FFFFFFF))
#पूर्ण_अगर
    वापस शून्य;
  अगर (शून्य == (pBuf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (माप_प्रकार)alloc_आकार_2)))
    वापस शून्य;

  अगर (!mz_zip_reader_extract_to_mem(pZip, file_सूचकांक, pBuf, (माप_प्रकार)alloc_आकार_2, flags))
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
    वापस शून्य;
  }

  अगर (p_आकार) *p_आकार = (माप_प्रकार)alloc_आकार_2;
  वापस pBuf;
}

व्योम *mz_zip_reader_extract_file_to_heap(mz_zip_archive *pZip, स्थिर अक्षर *pFilename, माप_प्रकार *p_आकार, mz_uint flags)
{
  पूर्णांक file_सूचकांक = mz_zip_reader_locate_file(pZip, pFilename, शून्य, flags);
  अगर (file_सूचकांक < 0)
  {
    अगर (p_आकार) *p_आकार = 0;
    वापस MZ_FALSE;
  }
  वापस mz_zip_reader_extract_to_heap(pZip, file_सूचकांक, p_आकार, flags);
}

mz_bool mz_zip_reader_extract_to_callback(mz_zip_archive *pZip, mz_uint file_सूचकांक, mz_file_write_func pCallback, व्योम *pOpaque, mz_uint flags)
{
  पूर्णांक status = TINFL_STATUS_DONE; mz_uint file_crc32 = MZ_CRC32_INIT;
  mz_uint64 read_buf_आकार, read_buf_ofs = 0, read_buf_avail, comp_remaining, out_buf_ofs = 0, cur_file_ofs;
  mz_zip_archive_file_stat file_stat;
  व्योम *pRead_buf = शून्य; व्योम *pWrite_buf = शून्य;
  mz_uint32 local_header_u32[(MZ_ZIP_LOCAL_DIR_HEADER_आकार + माप(mz_uint32) - 1) / माप(mz_uint32)]; mz_uint8 *pLocal_header = (mz_uint8 *)local_header_u32;

  अगर (!mz_zip_reader_file_stat(pZip, file_सूचकांक, &file_stat))
    वापस MZ_FALSE;

  // Empty file, or a directory (but not always a directory - I've seen odd zips with directories that have compressed data which inflates to 0 bytes)
  अगर (!file_stat.m_comp_आकार)
    वापस MZ_TRUE;

  // Entry is a subdirectory (I've seen old zips with dir entries which have compressed deflate data which inflates to 0 bytes, but these entries claim to uncompress to 512 bytes in the headers).
  // I'm torn how to handle this case - should it fail instead?
  अगर (mz_zip_reader_is_file_a_directory(pZip, file_सूचकांक))
    वापस MZ_TRUE;

  // Encryption and patch files are not supported.
  अगर (file_stat.m_bit_flag & (1 | 32))
    वापस MZ_FALSE;

  // This function only supports stored and deflate.
  अगर ((!(flags & MZ_ZIP_FLAG_COMPRESSED_तथ्य)) && (file_stat.m_method != 0) && (file_stat.m_method != MZ_DEFLATED))
    वापस MZ_FALSE;

  // Read and parse the local directory entry.
  cur_file_ofs = file_stat.m_local_header_ofs;
  अगर (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pLocal_header, MZ_ZIP_LOCAL_DIR_HEADER_आकार) != MZ_ZIP_LOCAL_DIR_HEADER_आकार)
    वापस MZ_FALSE;
  अगर (MZ_READ_LE32(pLocal_header) != MZ_ZIP_LOCAL_DIR_HEADER_SIG)
    वापस MZ_FALSE;

  cur_file_ofs += MZ_ZIP_LOCAL_DIR_HEADER_आकार + MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  अगर ((cur_file_ofs + file_stat.m_comp_आकार) > pZip->m_archive_आकार)
    वापस MZ_FALSE;

  // Decompress the file either directly from memory or from a file input buffer.
  अगर (pZip->m_pState->m_pMem)
  {
    pRead_buf = (mz_uint8 *)pZip->m_pState->m_pMem + cur_file_ofs;
    read_buf_आकार = read_buf_avail = file_stat.m_comp_आकार;
    comp_remaining = 0;
  }
  अन्यथा
  {
    read_buf_आकार = MZ_MIN(file_stat.m_comp_आकार, MZ_ZIP_MAX_IO_BUF_आकार);
    अगर (शून्य == (pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (माप_प्रकार)read_buf_आकार)))
      वापस MZ_FALSE;
    read_buf_avail = 0;
    comp_remaining = file_stat.m_comp_आकार;
  }

  अगर ((flags & MZ_ZIP_FLAG_COMPRESSED_तथ्य) || (!file_stat.m_method))
  {
    // The file is stored or the caller has requested the compressed data.
    अगर (pZip->m_pState->m_pMem)
    {
#अगर_घोषित _MSC_VER
      अगर (((0, माप(माप_प्रकार) == माप(mz_uint32))) && (file_stat.m_comp_आकार > 0xFFFFFFFF))
#अन्यथा
      अगर (((माप(माप_प्रकार) == माप(mz_uint32))) && (file_stat.m_comp_आकार > 0xFFFFFFFF))
#पूर्ण_अगर
        वापस MZ_FALSE;
      अगर (pCallback(pOpaque, out_buf_ofs, pRead_buf, (माप_प्रकार)file_stat.m_comp_आकार) != file_stat.m_comp_आकार)
        status = TINFL_STATUS_FAILED;
      अन्यथा अगर (!(flags & MZ_ZIP_FLAG_COMPRESSED_तथ्य))
        file_crc32 = (mz_uint32)mz_crc32(file_crc32, (स्थिर mz_uint8 *)pRead_buf, (माप_प्रकार)file_stat.m_comp_आकार);
      cur_file_ofs += file_stat.m_comp_आकार;
      out_buf_ofs += file_stat.m_comp_आकार;
      comp_remaining = 0;
    }
    अन्यथा
    {
      जबतक (comp_remaining)
      {
        read_buf_avail = MZ_MIN(read_buf_आकार, comp_remaining);
        अगर (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (माप_प्रकार)read_buf_avail) != read_buf_avail)
        {
          status = TINFL_STATUS_FAILED;
          अवरोध;
        }

        अगर (!(flags & MZ_ZIP_FLAG_COMPRESSED_तथ्य))
          file_crc32 = (mz_uint32)mz_crc32(file_crc32, (स्थिर mz_uint8 *)pRead_buf, (माप_प्रकार)read_buf_avail);

        अगर (pCallback(pOpaque, out_buf_ofs, pRead_buf, (माप_प्रकार)read_buf_avail) != read_buf_avail)
        {
          status = TINFL_STATUS_FAILED;
          अवरोध;
        }
        cur_file_ofs += read_buf_avail;
        out_buf_ofs += read_buf_avail;
        comp_remaining -= read_buf_avail;
      }
    }
  }
  अन्यथा
  {
    tinfl_decompressor inflator;
    tinfl_init(&inflator);

    अगर (शून्य == (pWrite_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, TINFL_LZ_DICT_आकार)))
      status = TINFL_STATUS_FAILED;
    अन्यथा
    {
      करो
      {
        mz_uint8 *pWrite_buf_cur = (mz_uint8 *)pWrite_buf + (out_buf_ofs & (TINFL_LZ_DICT_आकार - 1));
        माप_प्रकार in_buf_आकार, out_buf_आकार = TINFL_LZ_DICT_आकार - (out_buf_ofs & (TINFL_LZ_DICT_आकार - 1));
        अगर ((!read_buf_avail) && (!pZip->m_pState->m_pMem))
        {
          read_buf_avail = MZ_MIN(read_buf_आकार, comp_remaining);
          अगर (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (माप_प्रकार)read_buf_avail) != read_buf_avail)
          {
            status = TINFL_STATUS_FAILED;
            अवरोध;
          }
          cur_file_ofs += read_buf_avail;
          comp_remaining -= read_buf_avail;
          read_buf_ofs = 0;
        }

        in_buf_आकार = (माप_प्रकार)read_buf_avail;
        status = tinfl_decompress(&inflator, (स्थिर mz_uint8 *)pRead_buf + read_buf_ofs, &in_buf_आकार, (mz_uint8 *)pWrite_buf, pWrite_buf_cur, &out_buf_आकार, comp_remaining ? TINFL_FLAG_HAS_MORE_निवेश : 0);
        read_buf_avail -= in_buf_आकार;
        read_buf_ofs += in_buf_आकार;

        अगर (out_buf_आकार)
        {
          अगर (pCallback(pOpaque, out_buf_ofs, pWrite_buf_cur, out_buf_आकार) != out_buf_आकार)
          {
            status = TINFL_STATUS_FAILED;
            अवरोध;
          }
          file_crc32 = (mz_uint32)mz_crc32(file_crc32, pWrite_buf_cur, out_buf_आकार);
          अगर ((out_buf_ofs += out_buf_आकार) > file_stat.m_uncomp_आकार)
          {
            status = TINFL_STATUS_FAILED;
            अवरोध;
          }
        }
      } जबतक ((status == TINFL_STATUS_NEEDS_MORE_निवेश) || (status == TINFL_STATUS_HAS_MORE_OUTPUT));
    }
  }

  अगर ((status == TINFL_STATUS_DONE) && (!(flags & MZ_ZIP_FLAG_COMPRESSED_तथ्य)))
  {
    // Make sure the entire file was decompressed, and check its CRC.
    अगर ((out_buf_ofs != file_stat.m_uncomp_आकार) || (file_crc32 != file_stat.m_crc32))
      status = TINFL_STATUS_FAILED;
  }

  अगर (!pZip->m_pState->m_pMem)
    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
  अगर (pWrite_buf)
    pZip->m_pFree(pZip->m_pAlloc_opaque, pWrite_buf);

  वापस status == TINFL_STATUS_DONE;
}

mz_bool mz_zip_reader_extract_file_to_callback(mz_zip_archive *pZip, स्थिर अक्षर *pFilename, mz_file_write_func pCallback, व्योम *pOpaque, mz_uint flags)
{
  पूर्णांक file_सूचकांक = mz_zip_reader_locate_file(pZip, pFilename, शून्य, flags);
  अगर (file_सूचकांक < 0)
    वापस MZ_FALSE;
  वापस mz_zip_reader_extract_to_callback(pZip, file_सूचकांक, pCallback, pOpaque, flags);
}

#अगर_अघोषित MINIZ_NO_STDIO
अटल माप_प्रकार mz_zip_file_write_callback(व्योम *pOpaque, mz_uint64 ofs, स्थिर व्योम *pBuf, माप_प्रकार n)
{
  (व्योम)ofs; वापस MZ_FWRITE(pBuf, 1, n, (MZ_FILE*)pOpaque);
}

mz_bool mz_zip_reader_extract_to_file(mz_zip_archive *pZip, mz_uint file_सूचकांक, स्थिर अक्षर *pDst_filename, mz_uint flags)
{
  mz_bool status;
  mz_zip_archive_file_stat file_stat;
  MZ_FILE *pFile;
  अगर (!mz_zip_reader_file_stat(pZip, file_सूचकांक, &file_stat))
    वापस MZ_FALSE;
  pFile = MZ_FOPEN(pDst_filename, "wb");
  अगर (!pFile)
    वापस MZ_FALSE;
  status = mz_zip_reader_extract_to_callback(pZip, file_सूचकांक, mz_zip_file_write_callback, pFile, flags);
  अगर (MZ_FCLOSE(pFile) == खातापूर्ण)
    वापस MZ_FALSE;
#अगर_अघोषित MINIZ_NO_TIME
  अगर (status)
    mz_zip_set_file_times(pDst_filename, file_stat.m_time, file_stat.m_time);
#पूर्ण_अगर
  वापस status;
}
#पूर्ण_अगर // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_reader_end(mz_zip_archive *pZip)
{
  अगर ((!pZip) || (!pZip->m_pState) || (!pZip->m_pAlloc) || (!pZip->m_pFree) || (pZip->m_zip_mode != MZ_ZIP_MODE_READING))
    वापस MZ_FALSE;

  अगर (pZip->m_pState)
  {
    mz_zip_internal_state *pState = pZip->m_pState; pZip->m_pState = शून्य;
    mz_zip_array_clear(pZip, &pState->m_central_dir);
    mz_zip_array_clear(pZip, &pState->m_central_dir_offsets);
    mz_zip_array_clear(pZip, &pState->m_sorted_central_dir_offsets);

#अगर_अघोषित MINIZ_NO_STDIO
    अगर (pState->m_pFile)
    {
      MZ_FCLOSE(pState->m_pFile);
      pState->m_pFile = शून्य;
    }
#पूर्ण_अगर // #ifndef MINIZ_NO_STDIO

    pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
  }
  pZip->m_zip_mode = MZ_ZIP_MODE_INVALID;

  वापस MZ_TRUE;
}

#अगर_अघोषित MINIZ_NO_STDIO
mz_bool mz_zip_reader_extract_file_to_file(mz_zip_archive *pZip, स्थिर अक्षर *pArchive_filename, स्थिर अक्षर *pDst_filename, mz_uint flags)
{
  पूर्णांक file_सूचकांक = mz_zip_reader_locate_file(pZip, pArchive_filename, शून्य, flags);
  अगर (file_सूचकांक < 0)
    वापस MZ_FALSE;
  वापस mz_zip_reader_extract_to_file(pZip, file_सूचकांक, pDst_filename, flags);
}
#पूर्ण_अगर

// ------------------- .ZIP archive writing

#अगर_अघोषित MINIZ_NO_ARCHIVE_WRITING_APIS

अटल व्योम mz_write_le16(mz_uint8 *p, mz_uint16 v) { p[0] = (mz_uint8)v; p[1] = (mz_uint8)(v >> 8); }
अटल व्योम mz_write_le32(mz_uint8 *p, mz_uint32 v) { p[0] = (mz_uint8)v; p[1] = (mz_uint8)(v >> 8); p[2] = (mz_uint8)(v >> 16); p[3] = (mz_uint8)(v >> 24); }
#घोषणा MZ_WRITE_LE16(p, v) mz_write_le16((mz_uint8 *)(p), (mz_uint16)(v))
#घोषणा MZ_WRITE_LE32(p, v) mz_write_le32((mz_uint8 *)(p), (mz_uint32)(v))

mz_bool mz_zip_writer_init(mz_zip_archive *pZip, mz_uint64 existing_आकार)
{
  अगर ((!pZip) || (pZip->m_pState) || (!pZip->m_pWrite) || (pZip->m_zip_mode != MZ_ZIP_MODE_INVALID))
    वापस MZ_FALSE;

  अगर (pZip->m_file_offset_alignment)
  {
    // Ensure user specified file offset alignment is a power of 2.
    अगर (pZip->m_file_offset_alignment & (pZip->m_file_offset_alignment - 1))
      वापस MZ_FALSE;
  }

  अगर (!pZip->m_pAlloc) pZip->m_pAlloc = def_alloc_func;
  अगर (!pZip->m_pFree) pZip->m_pFree = def_free_func;
  अगर (!pZip->m_pRealloc) pZip->m_pRealloc = def_realloc_func;

  pZip->m_zip_mode = MZ_ZIP_MODE_WRITING;
  pZip->m_archive_आकार = existing_आकार;
  pZip->m_central_directory_file_ofs = 0;
  pZip->m_योग_files = 0;

  अगर (शून्य == (pZip->m_pState = (mz_zip_internal_state *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, माप(mz_zip_internal_state))))
    वापस MZ_FALSE;
  स_रखो(pZip->m_pState, 0, माप(mz_zip_internal_state));
  MZ_ZIP_ARRAY_SET_ELEMENT_आकार(&pZip->m_pState->m_central_dir, माप(mz_uint8));
  MZ_ZIP_ARRAY_SET_ELEMENT_आकार(&pZip->m_pState->m_central_dir_offsets, माप(mz_uint32));
  MZ_ZIP_ARRAY_SET_ELEMENT_आकार(&pZip->m_pState->m_sorted_central_dir_offsets, माप(mz_uint32));
  वापस MZ_TRUE;
}

अटल माप_प्रकार mz_zip_heap_write_func(व्योम *pOpaque, mz_uint64 file_ofs, स्थिर व्योम *pBuf, माप_प्रकार n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_zip_internal_state *pState = pZip->m_pState;
  mz_uint64 new_आकार = MZ_MAX(file_ofs + n, pState->m_mem_आकार);
#अगर_घोषित _MSC_VER
  अगर ((!n) || ((0, माप(माप_प्रकार) == माप(mz_uint32)) && (new_आकार > 0x7FFFFFFF)))
#अन्यथा
  अगर ((!n) || ((माप(माप_प्रकार) == माप(mz_uint32)) && (new_आकार > 0x7FFFFFFF)))
#पूर्ण_अगर
    वापस 0;
  अगर (new_आकार > pState->m_mem_capacity)
  {
    व्योम *pNew_block;
    माप_प्रकार new_capacity = MZ_MAX(64, pState->m_mem_capacity); जबतक (new_capacity < new_आकार) new_capacity *= 2;
    अगर (शून्य == (pNew_block = pZip->m_pRealloc(pZip->m_pAlloc_opaque, pState->m_pMem, 1, new_capacity)))
      वापस 0;
    pState->m_pMem = pNew_block; pState->m_mem_capacity = new_capacity;
  }
  स_नकल((mz_uint8 *)pState->m_pMem + file_ofs, pBuf, n);
  pState->m_mem_आकार = (माप_प्रकार)new_आकार;
  वापस n;
}

mz_bool mz_zip_writer_init_heap(mz_zip_archive *pZip, माप_प्रकार आकार_to_reserve_at_beginning, माप_प्रकार initial_allocation_आकार)
{
  pZip->m_pWrite = mz_zip_heap_write_func;
  pZip->m_pIO_opaque = pZip;
  अगर (!mz_zip_writer_init(pZip, आकार_to_reserve_at_beginning))
    वापस MZ_FALSE;
  अगर (0 != (initial_allocation_आकार = MZ_MAX(initial_allocation_आकार, आकार_to_reserve_at_beginning)))
  {
    अगर (शून्य == (pZip->m_pState->m_pMem = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, initial_allocation_आकार)))
    {
      mz_zip_writer_end(pZip);
      वापस MZ_FALSE;
    }
    pZip->m_pState->m_mem_capacity = initial_allocation_आकार;
  }
  वापस MZ_TRUE;
}

#अगर_अघोषित MINIZ_NO_STDIO
अटल माप_प्रकार mz_zip_file_write_func(व्योम *pOpaque, mz_uint64 file_ofs, स्थिर व्योम *pBuf, माप_प्रकार n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_int64 cur_ofs = MZ_FTELL64(pZip->m_pState->m_pFile);
  अगर (((mz_int64)file_ofs < 0) || (((cur_ofs != (mz_int64)file_ofs)) && (MZ_FSEEK64(pZip->m_pState->m_pFile, (mz_int64)file_ofs, शुरू_से))))
    वापस 0;
  वापस MZ_FWRITE(pBuf, 1, n, pZip->m_pState->m_pFile);
}

mz_bool mz_zip_writer_init_file(mz_zip_archive *pZip, स्थिर अक्षर *pFilename, mz_uint64 आकार_to_reserve_at_beginning)
{
  MZ_FILE *pFile;
  pZip->m_pWrite = mz_zip_file_write_func;
  pZip->m_pIO_opaque = pZip;
  अगर (!mz_zip_writer_init(pZip, आकार_to_reserve_at_beginning))
    वापस MZ_FALSE;
  अगर (शून्य == (pFile = MZ_FOPEN(pFilename, "wb")))
  {
    mz_zip_writer_end(pZip);
    वापस MZ_FALSE;
  }
  pZip->m_pState->m_pFile = pFile;
  अगर (आकार_to_reserve_at_beginning)
  {
    mz_uint64 cur_ofs = 0; अक्षर buf[4096]; MZ_CLEAR_ARR(buf);
    करो
    {
      माप_प्रकार n = (माप_प्रकार)MZ_MIN(माप(buf), आकार_to_reserve_at_beginning);
      अगर (pZip->m_pWrite(pZip->m_pIO_opaque, cur_ofs, buf, n) != n)
      {
        mz_zip_writer_end(pZip);
        वापस MZ_FALSE;
      }
      cur_ofs += n; आकार_to_reserve_at_beginning -= n;
    } जबतक (आकार_to_reserve_at_beginning);
  }
  वापस MZ_TRUE;
}
#पूर्ण_अगर // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_writer_init_from_reader(mz_zip_archive *pZip, स्थिर अक्षर *pFilename)
{
  mz_zip_internal_state *pState;
  अगर ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_mode != MZ_ZIP_MODE_READING))
    वापस MZ_FALSE;
  // No sense in trying to write to an archive that's already at the support max size
  अगर ((pZip->m_योग_files == 0xFFFF) || ((pZip->m_archive_आकार + MZ_ZIP_CENTRAL_DIR_HEADER_आकार + MZ_ZIP_LOCAL_DIR_HEADER_आकार) > 0xFFFFFFFF))
    वापस MZ_FALSE;

  pState = pZip->m_pState;

  अगर (pState->m_pFile)
  {
#अगर_घोषित MINIZ_NO_STDIO
    pFilename; वापस MZ_FALSE;
#अन्यथा
    // Archive is being read from stdio - try to reopen as writable.
    अगर (pZip->m_pIO_opaque != pZip)
      वापस MZ_FALSE;
    अगर (!pFilename)
      वापस MZ_FALSE;
    pZip->m_pWrite = mz_zip_file_write_func;
    अगर (शून्य == (pState->m_pFile = MZ_FREOPEN(pFilename, "r+b", pState->m_pFile)))
    {
      // The mz_zip_archive is now in a bogus state because pState->m_pFile is NULL, so just close it.
      mz_zip_reader_end(pZip);
      वापस MZ_FALSE;
    }
#पूर्ण_अगर // #ifdef MINIZ_NO_STDIO
  }
  अन्यथा अगर (pState->m_pMem)
  {
    // Archive lives in a memory block. Assume it's from the heap that we can resize using the realloc callback.
    अगर (pZip->m_pIO_opaque != pZip)
      वापस MZ_FALSE;
    pState->m_mem_capacity = pState->m_mem_आकार;
    pZip->m_pWrite = mz_zip_heap_write_func;
  }
  // Archive is being read via a user provided read function - make sure the user has specified a write function too.
  अन्यथा अगर (!pZip->m_pWrite)
    वापस MZ_FALSE;

  // Start writing new files at the archive's current central directory location.
  pZip->m_archive_आकार = pZip->m_central_directory_file_ofs;
  pZip->m_zip_mode = MZ_ZIP_MODE_WRITING;
  pZip->m_central_directory_file_ofs = 0;

  वापस MZ_TRUE;
}

mz_bool mz_zip_writer_add_mem(mz_zip_archive *pZip, स्थिर अक्षर *pArchive_name, स्थिर व्योम *pBuf, माप_प्रकार buf_आकार_2, mz_uint level_and_flags)
{
  वापस mz_zip_writer_add_mem_ex(pZip, pArchive_name, pBuf, buf_आकार_2, शून्य, 0, level_and_flags, 0, 0);
}

प्रकार काष्ठा
{
  mz_zip_archive *m_pZip;
  mz_uint64 m_cur_archive_file_ofs;
  mz_uint64 m_comp_आकार;
} mz_zip_writer_add_state;

अटल mz_bool mz_zip_writer_add_put_buf_callback(स्थिर व्योम* pBuf, पूर्णांक len, व्योम *pUser)
{
  mz_zip_writer_add_state *pState = (mz_zip_writer_add_state *)pUser;
  अगर ((पूर्णांक)pState->m_pZip->m_pWrite(pState->m_pZip->m_pIO_opaque, pState->m_cur_archive_file_ofs, pBuf, len) != len)
    वापस MZ_FALSE;
  pState->m_cur_archive_file_ofs += len;
  pState->m_comp_आकार += len;
  वापस MZ_TRUE;
}

अटल mz_bool mz_zip_writer_create_local_dir_header(mz_zip_archive *pZip, mz_uint8 *pDst, mz_uint16 filename_आकार, mz_uint16 extra_आकार, mz_uint64 uncomp_आकार, mz_uint64 comp_आकार, mz_uint32 uncomp_crc32, mz_uint16 method, mz_uint16 bit_flags, mz_uint16 dos_time, mz_uint16 dos_date)
{
  (व्योम)pZip;
  स_रखो(pDst, 0, MZ_ZIP_LOCAL_DIR_HEADER_आकार);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_SIG_OFS, MZ_ZIP_LOCAL_DIR_HEADER_SIG);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_VERSION_NEEDED_OFS, method ? 20 : 0);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_BIT_FLAG_OFS, bit_flags);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_METHOD_OFS, method);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILE_TIME_OFS, dos_time);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILE_DATE_OFS, dos_date);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_CRC32_OFS, uncomp_crc32);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_COMPRESSED_आकार_OFS, comp_आकार);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_DECOMPRESSED_आकार_OFS, uncomp_आकार);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILENAME_LEN_OFS, filename_आकार);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_EXTRA_LEN_OFS, extra_आकार);
  वापस MZ_TRUE;
}

अटल mz_bool mz_zip_writer_create_central_dir_header(mz_zip_archive *pZip, mz_uint8 *pDst, mz_uint16 filename_आकार, mz_uint16 extra_आकार, mz_uint16 comment_आकार, mz_uint64 uncomp_आकार, mz_uint64 comp_आकार, mz_uint32 uncomp_crc32, mz_uint16 method, mz_uint16 bit_flags, mz_uint16 dos_time, mz_uint16 dos_date, mz_uint64 local_header_ofs, mz_uint32 ext_attributes)
{
  (व्योम)pZip;
  स_रखो(pDst, 0, MZ_ZIP_CENTRAL_DIR_HEADER_आकार);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_SIG_OFS, MZ_ZIP_CENTRAL_DIR_HEADER_SIG);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_VERSION_NEEDED_OFS, method ? 20 : 0);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_BIT_FLAG_OFS, bit_flags);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_METHOD_OFS, method);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILE_TIME_OFS, dos_time);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILE_DATE_OFS, dos_date);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_CRC32_OFS, uncomp_crc32);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_COMPRESSED_आकार_OFS, comp_आकार);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_DECOMPRESSED_आकार_OFS, uncomp_आकार);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILENAME_LEN_OFS, filename_आकार);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_EXTRA_LEN_OFS, extra_आकार);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_COMMENT_LEN_OFS, comment_आकार);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS, ext_attributes);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_LOCAL_HEADER_OFS, local_header_ofs);
  वापस MZ_TRUE;
}

अटल mz_bool mz_zip_writer_add_to_central_dir(mz_zip_archive *pZip, स्थिर अक्षर *pFilename, mz_uint16 filename_आकार, स्थिर व्योम *pExtra, mz_uint16 extra_आकार, स्थिर व्योम *pComment, mz_uint16 comment_आकार, mz_uint64 uncomp_आकार, mz_uint64 comp_आकार, mz_uint32 uncomp_crc32, mz_uint16 method, mz_uint16 bit_flags, mz_uint16 dos_time, mz_uint16 dos_date, mz_uint64 local_header_ofs, mz_uint32 ext_attributes)
{
  mz_zip_internal_state *pState = pZip->m_pState;
  mz_uint32 central_dir_ofs = (mz_uint32)pState->m_central_dir.m_आकार;
  माप_प्रकार orig_central_dir_आकार = pState->m_central_dir.m_आकार;
  mz_uint8 central_dir_header[MZ_ZIP_CENTRAL_DIR_HEADER_आकार];

  // No zip64 support yet
  अगर ((local_header_ofs > 0xFFFFFFFF) || (((mz_uint64)pState->m_central_dir.m_आकार + MZ_ZIP_CENTRAL_DIR_HEADER_आकार + filename_आकार + extra_आकार + comment_आकार) > 0xFFFFFFFF))
    वापस MZ_FALSE;

  अगर (!mz_zip_writer_create_central_dir_header(pZip, central_dir_header, filename_आकार, extra_आकार, comment_आकार, uncomp_आकार, comp_आकार, uncomp_crc32, method, bit_flags, dos_time, dos_date, local_header_ofs, ext_attributes))
    वापस MZ_FALSE;

  अगर ((!mz_zip_array_धकेलो_back(pZip, &pState->m_central_dir, central_dir_header, MZ_ZIP_CENTRAL_DIR_HEADER_आकार)) ||
      (!mz_zip_array_धकेलो_back(pZip, &pState->m_central_dir, pFilename, filename_आकार)) ||
      (!mz_zip_array_धकेलो_back(pZip, &pState->m_central_dir, pExtra, extra_आकार)) ||
      (!mz_zip_array_धकेलो_back(pZip, &pState->m_central_dir, pComment, comment_आकार)) ||
      (!mz_zip_array_धकेलो_back(pZip, &pState->m_central_dir_offsets, &central_dir_ofs, 1)))
  {
    // Try to push the central directory array back into its original state.
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_आकार, MZ_FALSE);
    वापस MZ_FALSE;
  }

  वापस MZ_TRUE;
}

अटल mz_bool mz_zip_writer_validate_archive_name(स्थिर अक्षर *pArchive_name)
{
  // Basic ZIP archive filename validity checks: Valid filenames cannot start with a forward slash, cannot contain a drive letter, and cannot use DOS-style backward slashes.
  अगर (*pArchive_name == '/')
    वापस MZ_FALSE;
  जबतक (*pArchive_name)
  {
    अगर ((*pArchive_name == '\\') || (*pArchive_name == ':'))
      वापस MZ_FALSE;
    pArchive_name++;
  }
  वापस MZ_TRUE;
}

अटल mz_uint mz_zip_writer_compute_padding_needed_for_file_alignment(mz_zip_archive *pZip)
{
  mz_uint32 n;
  अगर (!pZip->m_file_offset_alignment)
    वापस 0;
  n = (mz_uint32)(pZip->m_archive_आकार & (pZip->m_file_offset_alignment - 1));
  वापस (pZip->m_file_offset_alignment - n) & (pZip->m_file_offset_alignment - 1);
}

अटल mz_bool mz_zip_writer_write_zeros(mz_zip_archive *pZip, mz_uint64 cur_file_ofs, mz_uint32 n)
{
  अक्षर buf[4096];
  स_रखो(buf, 0, MZ_MIN(माप(buf), n));
  जबतक (n)
  {
    mz_uint32 s = MZ_MIN(माप(buf), n);
    अगर (pZip->m_pWrite(pZip->m_pIO_opaque, cur_file_ofs, buf, s) != s)
      वापस MZ_FALSE;
    cur_file_ofs += s; n -= s;
  }
  वापस MZ_TRUE;
}

mz_bool mz_zip_writer_add_mem_ex(mz_zip_archive *pZip, स्थिर अक्षर *pArchive_name, स्थिर व्योम *pBuf, माप_प्रकार buf_आकार_2, स्थिर व्योम *pComment, mz_uint16 comment_आकार, mz_uint level_and_flags, mz_uint64 uncomp_आकार, mz_uint32 uncomp_crc32)
{
  mz_uint16 method = 0, dos_time = 0, dos_date = 0;
  mz_uint level, ext_attributes = 0, अंक_alignment_padding_bytes;
  mz_uint64 local_dir_header_ofs = pZip->m_archive_आकार, cur_archive_file_ofs = pZip->m_archive_आकार, comp_आकार = 0;
  माप_प्रकार archive_name_आकार;
  mz_uint8 local_dir_header[MZ_ZIP_LOCAL_DIR_HEADER_आकार];
  tdefl_compressor *pComp = शून्य;
  mz_bool store_तथ्य_uncompressed;
  mz_zip_internal_state *pState;

  अगर ((पूर्णांक)level_and_flags < 0)
    level_and_flags = MZ_DEFAULT_LEVEL;
  level = level_and_flags & 0xF;
  store_तथ्य_uncompressed = ((!level) || (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_तथ्य));

  अगर ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_mode != MZ_ZIP_MODE_WRITING) || ((buf_आकार_2) && (!pBuf)) || (!pArchive_name) || ((comment_आकार) && (!pComment)) || (pZip->m_योग_files == 0xFFFF) || (level > MZ_UBER_COMPRESSION))
    वापस MZ_FALSE;

  pState = pZip->m_pState;

  अगर ((!(level_and_flags & MZ_ZIP_FLAG_COMPRESSED_तथ्य)) && (uncomp_आकार))
    वापस MZ_FALSE;
  // No zip64 support yet
  अगर ((buf_आकार_2 > 0xFFFFFFFF) || (uncomp_आकार > 0xFFFFFFFF))
    वापस MZ_FALSE;
  अगर (!mz_zip_writer_validate_archive_name(pArchive_name))
    वापस MZ_FALSE;

#अगर_अघोषित MINIZ_NO_TIME
  {
    समय_प्रकार cur_time; समय(&cur_time);
    mz_zip_time_to_dos_time(cur_time, &dos_time, &dos_date);
  }
#पूर्ण_अगर // #ifndef MINIZ_NO_TIME

  archive_name_आकार = म_माप(pArchive_name);
  अगर (archive_name_आकार > 0xFFFF)
    वापस MZ_FALSE;

  अंक_alignment_padding_bytes = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  अगर ((pZip->m_योग_files == 0xFFFF) || ((pZip->m_archive_आकार + अंक_alignment_padding_bytes + MZ_ZIP_LOCAL_DIR_HEADER_आकार + MZ_ZIP_CENTRAL_DIR_HEADER_आकार + comment_आकार + archive_name_आकार) > 0xFFFFFFFF))
    वापस MZ_FALSE;

  अगर ((archive_name_आकार) && (pArchive_name[archive_name_आकार - 1] == '/'))
  {
    // Set DOS Subdirectory attribute bit.
    ext_attributes |= 0x10;
    // Subdirectories cannot contain data.
    अगर ((buf_आकार_2) || (uncomp_आकार))
      वापस MZ_FALSE;
  }

  // Try to do any allocations before writing to the archive, so if an allocation fails the file remains unmodified. (A good idea if we're doing an in-place modification.)
  अगर ((!mz_zip_array_ensure_room(pZip, &pState->m_central_dir, MZ_ZIP_CENTRAL_DIR_HEADER_आकार + archive_name_आकार + comment_आकार)) || (!mz_zip_array_ensure_room(pZip, &pState->m_central_dir_offsets, 1)))
    वापस MZ_FALSE;

  अगर ((!store_तथ्य_uncompressed) && (buf_आकार_2))
  {
    अगर (शून्य == (pComp = (tdefl_compressor *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, माप(tdefl_compressor))))
      वापस MZ_FALSE;
  }

  अगर (!mz_zip_writer_write_zeros(pZip, cur_archive_file_ofs, अंक_alignment_padding_bytes + माप(local_dir_header)))
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
    वापस MZ_FALSE;
  }
  local_dir_header_ofs += अंक_alignment_padding_bytes;
  अगर (pZip->m_file_offset_alignment) { MZ_ASSERT((local_dir_header_ofs & (pZip->m_file_offset_alignment - 1)) == 0); }
  cur_archive_file_ofs += अंक_alignment_padding_bytes + माप(local_dir_header);

  MZ_CLEAR_ARR(local_dir_header);
  अगर (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pArchive_name, archive_name_आकार) != archive_name_आकार)
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
    वापस MZ_FALSE;
  }
  cur_archive_file_ofs += archive_name_आकार;

  अगर (!(level_and_flags & MZ_ZIP_FLAG_COMPRESSED_तथ्य))
  {
    uncomp_crc32 = (mz_uint32)mz_crc32(MZ_CRC32_INIT, (स्थिर mz_uint8*)pBuf, buf_आकार_2);
    uncomp_आकार = buf_आकार_2;
    अगर (uncomp_आकार <= 3)
    {
      level = 0;
      store_तथ्य_uncompressed = MZ_TRUE;
    }
  }

  अगर (store_तथ्य_uncompressed)
  {
    अगर (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pBuf, buf_आकार_2) != buf_आकार_2)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
      वापस MZ_FALSE;
    }

    cur_archive_file_ofs += buf_आकार_2;
    comp_आकार = buf_आकार_2;

    अगर (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_तथ्य)
      method = MZ_DEFLATED;
  }
  अन्यथा अगर (buf_आकार_2)
  {
    mz_zip_writer_add_state state;

    state.m_pZip = pZip;
    state.m_cur_archive_file_ofs = cur_archive_file_ofs;
    state.m_comp_आकार = 0;

    अगर ((tdefl_init(pComp, mz_zip_writer_add_put_buf_callback, &state, tdefl_create_comp_flags_from_zip_params(level, -15, MZ_DEFAULT_STRATEGY)) != TDEFL_STATUS_OKAY) ||
        (tdefl_compress_बफर(pComp, pBuf, buf_आकार_2, TDEFL_FINISH) != TDEFL_STATUS_DONE))
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
      वापस MZ_FALSE;
    }

    comp_आकार = state.m_comp_आकार;
    cur_archive_file_ofs = state.m_cur_archive_file_ofs;

    method = MZ_DEFLATED;
  }

  pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
  pComp = शून्य;

  // no zip64 support yet
  अगर ((comp_आकार > 0xFFFFFFFF) || (cur_archive_file_ofs > 0xFFFFFFFF))
    वापस MZ_FALSE;

  अगर (!mz_zip_writer_create_local_dir_header(pZip, local_dir_header, (mz_uint16)archive_name_आकार, 0, uncomp_आकार, comp_आकार, uncomp_crc32, method, 0, dos_time, dos_date))
    वापस MZ_FALSE;

  अगर (pZip->m_pWrite(pZip->m_pIO_opaque, local_dir_header_ofs, local_dir_header, माप(local_dir_header)) != माप(local_dir_header))
    वापस MZ_FALSE;

  अगर (!mz_zip_writer_add_to_central_dir(pZip, pArchive_name, (mz_uint16)archive_name_आकार, शून्य, 0, pComment, comment_आकार, uncomp_आकार, comp_आकार, uncomp_crc32, method, 0, dos_time, dos_date, local_dir_header_ofs, ext_attributes))
    वापस MZ_FALSE;

  pZip->m_योग_files++;
  pZip->m_archive_आकार = cur_archive_file_ofs;

  वापस MZ_TRUE;
}

#अगर_अघोषित MINIZ_NO_STDIO
mz_bool mz_zip_writer_add_file(mz_zip_archive *pZip, स्थिर अक्षर *pArchive_name, स्थिर अक्षर *pSrc_filename, स्थिर व्योम *pComment, mz_uint16 comment_आकार, mz_uint level_and_flags)
{
  mz_uint uncomp_crc32 = MZ_CRC32_INIT, level, अंक_alignment_padding_bytes;
  mz_uint16 method = 0, dos_time = 0, dos_date = 0, ext_attributes = 0;
  mz_uint64 local_dir_header_ofs = pZip->m_archive_आकार, cur_archive_file_ofs = pZip->m_archive_आकार, uncomp_आकार = 0, comp_आकार = 0;
  माप_प्रकार archive_name_आकार;
  mz_uint8 local_dir_header[MZ_ZIP_LOCAL_DIR_HEADER_आकार];
  MZ_FILE *pSrc_file = शून्य;

  अगर ((पूर्णांक)level_and_flags < 0)
    level_and_flags = MZ_DEFAULT_LEVEL;
  level = level_and_flags & 0xF;

  अगर ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_mode != MZ_ZIP_MODE_WRITING) || (!pArchive_name) || ((comment_आकार) && (!pComment)) || (level > MZ_UBER_COMPRESSION))
    वापस MZ_FALSE;
  अगर (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_तथ्य)
    वापस MZ_FALSE;
  अगर (!mz_zip_writer_validate_archive_name(pArchive_name))
    वापस MZ_FALSE;

  archive_name_आकार = म_माप(pArchive_name);
  अगर (archive_name_आकार > 0xFFFF)
    वापस MZ_FALSE;

  अंक_alignment_padding_bytes = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  अगर ((pZip->m_योग_files == 0xFFFF) || ((pZip->m_archive_आकार + अंक_alignment_padding_bytes + MZ_ZIP_LOCAL_DIR_HEADER_आकार + MZ_ZIP_CENTRAL_DIR_HEADER_आकार + comment_आकार + archive_name_आकार) > 0xFFFFFFFF))
    वापस MZ_FALSE;

  अगर (!mz_zip_get_file_modified_time(pSrc_filename, &dos_time, &dos_date))
    वापस MZ_FALSE;

  pSrc_file = MZ_FOPEN(pSrc_filename, "rb");
  अगर (!pSrc_file)
    वापस MZ_FALSE;
  MZ_FSEEK64(pSrc_file, 0, अंत_से);
  uncomp_आकार = MZ_FTELL64(pSrc_file);
  MZ_FSEEK64(pSrc_file, 0, शुरू_से);

  अगर (uncomp_आकार > 0xFFFFFFFF)
  {
    // No zip64 support yet
    MZ_FCLOSE(pSrc_file);
    वापस MZ_FALSE;
  }
  अगर (uncomp_आकार <= 3)
    level = 0;

  अगर (!mz_zip_writer_write_zeros(pZip, cur_archive_file_ofs, अंक_alignment_padding_bytes + माप(local_dir_header)))
  {
    MZ_FCLOSE(pSrc_file);
    वापस MZ_FALSE;
  }
  local_dir_header_ofs += अंक_alignment_padding_bytes;
  अगर (pZip->m_file_offset_alignment) { MZ_ASSERT((local_dir_header_ofs & (pZip->m_file_offset_alignment - 1)) == 0); }
  cur_archive_file_ofs += अंक_alignment_padding_bytes + माप(local_dir_header);

  MZ_CLEAR_ARR(local_dir_header);
  अगर (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pArchive_name, archive_name_आकार) != archive_name_आकार)
  {
    MZ_FCLOSE(pSrc_file);
    वापस MZ_FALSE;
  }
  cur_archive_file_ofs += archive_name_आकार;

  अगर (uncomp_आकार)
  {
    mz_uint64 uncomp_remaining = uncomp_आकार;
    व्योम *pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, MZ_ZIP_MAX_IO_BUF_आकार);
    अगर (!pRead_buf)
    {
      MZ_FCLOSE(pSrc_file);
      वापस MZ_FALSE;
    }

    अगर (!level)
    {
      जबतक (uncomp_remaining)
      {
        mz_uint n = (mz_uint)MZ_MIN(MZ_ZIP_MAX_IO_BUF_आकार, uncomp_remaining);
        अगर ((MZ_FREAD(pRead_buf, 1, n, pSrc_file) != n) || (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pRead_buf, n) != n))
        {
          pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
          MZ_FCLOSE(pSrc_file);
          वापस MZ_FALSE;
        }
        uncomp_crc32 = (mz_uint32)mz_crc32(uncomp_crc32, (स्थिर mz_uint8 *)pRead_buf, n);
        uncomp_remaining -= n;
        cur_archive_file_ofs += n;
      }
      comp_आकार = uncomp_आकार;
    }
    अन्यथा
    {
      mz_bool परिणाम = MZ_FALSE;
      mz_zip_writer_add_state state;
      tdefl_compressor *pComp = (tdefl_compressor *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, माप(tdefl_compressor));
      अगर (!pComp)
      {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        वापस MZ_FALSE;
      }

      state.m_pZip = pZip;
      state.m_cur_archive_file_ofs = cur_archive_file_ofs;
      state.m_comp_आकार = 0;

      अगर (tdefl_init(pComp, mz_zip_writer_add_put_buf_callback, &state, tdefl_create_comp_flags_from_zip_params(level, -15, MZ_DEFAULT_STRATEGY)) != TDEFL_STATUS_OKAY)
      {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        वापस MZ_FALSE;
      }

      क्रम ( ; ; )
      {
        माप_प्रकार in_buf_आकार = (mz_uint32)MZ_MIN(uncomp_remaining, MZ_ZIP_MAX_IO_BUF_आकार);
        tdefl_status status;

        अगर (MZ_FREAD(pRead_buf, 1, in_buf_आकार, pSrc_file) != in_buf_आकार)
          अवरोध;

        uncomp_crc32 = (mz_uint32)mz_crc32(uncomp_crc32, (स्थिर mz_uint8 *)pRead_buf, in_buf_आकार);
        uncomp_remaining -= in_buf_आकार;

        status = tdefl_compress_बफर(pComp, pRead_buf, in_buf_आकार, uncomp_remaining ? TDEFL_NO_FLUSH : TDEFL_FINISH);
        अगर (status == TDEFL_STATUS_DONE)
        {
          परिणाम = MZ_TRUE;
          अवरोध;
        }
        अन्यथा अगर (status != TDEFL_STATUS_OKAY)
          अवरोध;
      }

      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);

      अगर (!परिणाम)
      {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        वापस MZ_FALSE;
      }

      comp_आकार = state.m_comp_आकार;
      cur_archive_file_ofs = state.m_cur_archive_file_ofs;

      method = MZ_DEFLATED;
    }

    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
  }

  MZ_FCLOSE(pSrc_file); pSrc_file = शून्य;

  // no zip64 support yet
  अगर ((comp_आकार > 0xFFFFFFFF) || (cur_archive_file_ofs > 0xFFFFFFFF))
    वापस MZ_FALSE;

  अगर (!mz_zip_writer_create_local_dir_header(pZip, local_dir_header, (mz_uint16)archive_name_आकार, 0, uncomp_आकार, comp_आकार, uncomp_crc32, method, 0, dos_time, dos_date))
    वापस MZ_FALSE;

  अगर (pZip->m_pWrite(pZip->m_pIO_opaque, local_dir_header_ofs, local_dir_header, माप(local_dir_header)) != माप(local_dir_header))
    वापस MZ_FALSE;

  अगर (!mz_zip_writer_add_to_central_dir(pZip, pArchive_name, (mz_uint16)archive_name_आकार, शून्य, 0, pComment, comment_आकार, uncomp_आकार, comp_आकार, uncomp_crc32, method, 0, dos_time, dos_date, local_dir_header_ofs, ext_attributes))
    वापस MZ_FALSE;

  pZip->m_योग_files++;
  pZip->m_archive_आकार = cur_archive_file_ofs;

  वापस MZ_TRUE;
}
#पूर्ण_अगर // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_writer_add_from_zip_reader(mz_zip_archive *pZip, mz_zip_archive *pSource_zip, mz_uint file_सूचकांक)
{
  mz_uint n, bit_flags, अंक_alignment_padding_bytes;
  mz_uint64 comp_bytes_remaining, local_dir_header_ofs;
  mz_uint64 cur_src_file_ofs, cur_dst_file_ofs;
  mz_uint32 local_header_u32[(MZ_ZIP_LOCAL_DIR_HEADER_आकार + माप(mz_uint32) - 1) / माप(mz_uint32)]; mz_uint8 *pLocal_header = (mz_uint8 *)local_header_u32;
  mz_uint8 central_header[MZ_ZIP_CENTRAL_DIR_HEADER_आकार];
  माप_प्रकार orig_central_dir_आकार;
  mz_zip_internal_state *pState;
  व्योम *pBuf; स्थिर mz_uint8 *pSrc_central_header;

  अगर ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_mode != MZ_ZIP_MODE_WRITING))
    वापस MZ_FALSE;
  अगर (शून्य == (pSrc_central_header = mz_zip_reader_get_cdh(pSource_zip, file_सूचकांक)))
    वापस MZ_FALSE;
  pState = pZip->m_pState;

  अंक_alignment_padding_bytes = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  अगर ((pZip->m_योग_files == 0xFFFF) || ((pZip->m_archive_आकार + अंक_alignment_padding_bytes + MZ_ZIP_LOCAL_DIR_HEADER_आकार + MZ_ZIP_CENTRAL_DIR_HEADER_आकार) > 0xFFFFFFFF))
    वापस MZ_FALSE;

  cur_src_file_ofs = MZ_READ_LE32(pSrc_central_header + MZ_ZIP_CDH_LOCAL_HEADER_OFS);
  cur_dst_file_ofs = pZip->m_archive_आकार;

  अगर (pSource_zip->m_pRead(pSource_zip->m_pIO_opaque, cur_src_file_ofs, pLocal_header, MZ_ZIP_LOCAL_DIR_HEADER_आकार) != MZ_ZIP_LOCAL_DIR_HEADER_आकार)
    वापस MZ_FALSE;
  अगर (MZ_READ_LE32(pLocal_header) != MZ_ZIP_LOCAL_DIR_HEADER_SIG)
    वापस MZ_FALSE;
  cur_src_file_ofs += MZ_ZIP_LOCAL_DIR_HEADER_आकार;

  अगर (!mz_zip_writer_write_zeros(pZip, cur_dst_file_ofs, अंक_alignment_padding_bytes))
    वापस MZ_FALSE;
  cur_dst_file_ofs += अंक_alignment_padding_bytes;
  local_dir_header_ofs = cur_dst_file_ofs;
  अगर (pZip->m_file_offset_alignment) { MZ_ASSERT((local_dir_header_ofs & (pZip->m_file_offset_alignment - 1)) == 0); }

  अगर (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, pLocal_header, MZ_ZIP_LOCAL_DIR_HEADER_आकार) != MZ_ZIP_LOCAL_DIR_HEADER_आकार)
    वापस MZ_FALSE;
  cur_dst_file_ofs += MZ_ZIP_LOCAL_DIR_HEADER_आकार;

  n = MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  comp_bytes_remaining = n + MZ_READ_LE32(pSrc_central_header + MZ_ZIP_CDH_COMPRESSED_आकार_OFS);

  अगर (शून्य == (pBuf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (माप_प्रकार)MZ_MAX(माप(mz_uint32) * 4, MZ_MIN(MZ_ZIP_MAX_IO_BUF_आकार, comp_bytes_remaining)))))
    वापस MZ_FALSE;

  जबतक (comp_bytes_remaining)
  {
    n = (mz_uint)MZ_MIN(MZ_ZIP_MAX_IO_BUF_आकार, comp_bytes_remaining);
    अगर (pSource_zip->m_pRead(pSource_zip->m_pIO_opaque, cur_src_file_ofs, pBuf, n) != n)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      वापस MZ_FALSE;
    }
    cur_src_file_ofs += n;

    अगर (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, pBuf, n) != n)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      वापस MZ_FALSE;
    }
    cur_dst_file_ofs += n;

    comp_bytes_remaining -= n;
  }

  bit_flags = MZ_READ_LE16(pLocal_header + MZ_ZIP_LDH_BIT_FLAG_OFS);
  अगर (bit_flags & 8)
  {
    // Copy data descriptor
    अगर (pSource_zip->m_pRead(pSource_zip->m_pIO_opaque, cur_src_file_ofs, pBuf, माप(mz_uint32) * 4) != माप(mz_uint32) * 4)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      वापस MZ_FALSE;
    }

    n = माप(mz_uint32) * ((MZ_READ_LE32(pBuf) == 0x08074b50) ? 4 : 3);
    अगर (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, pBuf, n) != n)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      वापस MZ_FALSE;
    }

    cur_src_file_ofs += n;
    cur_dst_file_ofs += n;
  }
  pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);

  // no zip64 support yet
  अगर (cur_dst_file_ofs > 0xFFFFFFFF)
    वापस MZ_FALSE;

  orig_central_dir_आकार = pState->m_central_dir.m_आकार;

  स_नकल(central_header, pSrc_central_header, MZ_ZIP_CENTRAL_DIR_HEADER_आकार);
  MZ_WRITE_LE32(central_header + MZ_ZIP_CDH_LOCAL_HEADER_OFS, local_dir_header_ofs);
  अगर (!mz_zip_array_धकेलो_back(pZip, &pState->m_central_dir, central_header, MZ_ZIP_CENTRAL_DIR_HEADER_आकार))
    वापस MZ_FALSE;

  n = MZ_READ_LE16(pSrc_central_header + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(pSrc_central_header + MZ_ZIP_CDH_EXTRA_LEN_OFS) + MZ_READ_LE16(pSrc_central_header + MZ_ZIP_CDH_COMMENT_LEN_OFS);
  अगर (!mz_zip_array_धकेलो_back(pZip, &pState->m_central_dir, pSrc_central_header + MZ_ZIP_CENTRAL_DIR_HEADER_आकार, n))
  {
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_आकार, MZ_FALSE);
    वापस MZ_FALSE;
  }

  अगर (pState->m_central_dir.m_आकार > 0xFFFFFFFF)
    वापस MZ_FALSE;
  n = (mz_uint32)orig_central_dir_आकार;
  अगर (!mz_zip_array_धकेलो_back(pZip, &pState->m_central_dir_offsets, &n, 1))
  {
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_आकार, MZ_FALSE);
    वापस MZ_FALSE;
  }

  pZip->m_योग_files++;
  pZip->m_archive_आकार = cur_dst_file_ofs;

  वापस MZ_TRUE;
}

mz_bool mz_zip_writer_finalize_archive(mz_zip_archive *pZip)
{
  mz_zip_internal_state *pState;
  mz_uint64 central_dir_ofs, central_dir_आकार;
  mz_uint8 hdr[MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_आकार];

  अगर ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_mode != MZ_ZIP_MODE_WRITING))
    वापस MZ_FALSE;

  pState = pZip->m_pState;

  // no zip64 support yet
  अगर ((pZip->m_योग_files > 0xFFFF) || ((pZip->m_archive_आकार + pState->m_central_dir.m_आकार + MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_आकार) > 0xFFFFFFFF))
    वापस MZ_FALSE;

  central_dir_ofs = 0;
  central_dir_आकार = 0;
  अगर (pZip->m_योग_files)
  {
    // Write central directory
    central_dir_ofs = pZip->m_archive_आकार;
    central_dir_आकार = pState->m_central_dir.m_आकार;
    pZip->m_central_directory_file_ofs = central_dir_ofs;
    अगर (pZip->m_pWrite(pZip->m_pIO_opaque, central_dir_ofs, pState->m_central_dir.m_p, (माप_प्रकार)central_dir_आकार) != central_dir_आकार)
      वापस MZ_FALSE;
    pZip->m_archive_आकार += central_dir_आकार;
  }

  // Write end of central directory record
  MZ_CLEAR_ARR(hdr);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_SIG_OFS, MZ_ZIP_END_OF_CENTRAL_DIR_HEADER_SIG);
  MZ_WRITE_LE16(hdr + MZ_ZIP_ECDH_CDIR_अंक_ENTRIES_ON_DISK_OFS, pZip->m_योग_files);
  MZ_WRITE_LE16(hdr + MZ_ZIP_ECDH_CDIR_योग_ENTRIES_OFS, pZip->m_योग_files);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_CDIR_आकार_OFS, central_dir_आकार);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_CDIR_OFS_OFS, central_dir_ofs);

  अगर (pZip->m_pWrite(pZip->m_pIO_opaque, pZip->m_archive_आकार, hdr, माप(hdr)) != माप(hdr))
    वापस MZ_FALSE;
#अगर_अघोषित MINIZ_NO_STDIO
  अगर ((pState->m_pFile) && (MZ_FFLUSH(pState->m_pFile) == खातापूर्ण))
    वापस MZ_FALSE;
#पूर्ण_अगर // #ifndef MINIZ_NO_STDIO

  pZip->m_archive_आकार += माप(hdr);

  pZip->m_zip_mode = MZ_ZIP_MODE_WRITING_HAS_BEEN_FINALIZED;
  वापस MZ_TRUE;
}

mz_bool mz_zip_writer_finalize_heap_archive(mz_zip_archive *pZip, व्योम **pBuf, माप_प्रकार *p_आकार)
{
  अगर ((!pZip) || (!pZip->m_pState) || (!pBuf) || (!p_आकार))
    वापस MZ_FALSE;
  अगर (pZip->m_pWrite != mz_zip_heap_write_func)
    वापस MZ_FALSE;
  अगर (!mz_zip_writer_finalize_archive(pZip))
    वापस MZ_FALSE;

  *pBuf = pZip->m_pState->m_pMem;
  *p_आकार = pZip->m_pState->m_mem_आकार;
  pZip->m_pState->m_pMem = शून्य;
  pZip->m_pState->m_mem_आकार = pZip->m_pState->m_mem_capacity = 0;
  वापस MZ_TRUE;
}

mz_bool mz_zip_writer_end(mz_zip_archive *pZip)
{
  mz_zip_internal_state *pState;
  mz_bool status = MZ_TRUE;
  अगर ((!pZip) || (!pZip->m_pState) || (!pZip->m_pAlloc) || (!pZip->m_pFree) || ((pZip->m_zip_mode != MZ_ZIP_MODE_WRITING) && (pZip->m_zip_mode != MZ_ZIP_MODE_WRITING_HAS_BEEN_FINALIZED)))
    वापस MZ_FALSE;

  pState = pZip->m_pState;
  pZip->m_pState = शून्य;
  mz_zip_array_clear(pZip, &pState->m_central_dir);
  mz_zip_array_clear(pZip, &pState->m_central_dir_offsets);
  mz_zip_array_clear(pZip, &pState->m_sorted_central_dir_offsets);

#अगर_अघोषित MINIZ_NO_STDIO
  अगर (pState->m_pFile)
  {
    MZ_FCLOSE(pState->m_pFile);
    pState->m_pFile = शून्य;
  }
#पूर्ण_अगर // #ifndef MINIZ_NO_STDIO

  अगर ((pZip->m_pWrite == mz_zip_heap_write_func) && (pState->m_pMem))
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pState->m_pMem);
    pState->m_pMem = शून्य;
  }

  pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
  pZip->m_zip_mode = MZ_ZIP_MODE_INVALID;
  वापस status;
}

#अगर_अघोषित MINIZ_NO_STDIO
mz_bool mz_zip_add_mem_to_archive_file_in_place(स्थिर अक्षर *pZip_filename, स्थिर अक्षर *pArchive_name, स्थिर व्योम *pBuf, माप_प्रकार buf_आकार_2, स्थिर व्योम *pComment, mz_uint16 comment_आकार, mz_uint level_and_flags)
{
  mz_bool status, created_new_archive = MZ_FALSE;
  mz_zip_archive zip_archive;
  काष्ठा MZ_FILE_STAT_STRUCT file_stat;
  MZ_CLEAR_OBJ(zip_archive);
  अगर ((पूर्णांक)level_and_flags < 0)
     level_and_flags = MZ_DEFAULT_LEVEL;
  अगर ((!pZip_filename) || (!pArchive_name) || ((buf_आकार_2) && (!pBuf)) || ((comment_आकार) && (!pComment)) || ((level_and_flags & 0xF) > MZ_UBER_COMPRESSION))
    वापस MZ_FALSE;
  अगर (!mz_zip_writer_validate_archive_name(pArchive_name))
    वापस MZ_FALSE;
  अगर (MZ_FILE_STAT(pZip_filename, &file_stat) != 0)
  {
    // Create a new archive.
    अगर (!mz_zip_writer_init_file(&zip_archive, pZip_filename, 0))
      वापस MZ_FALSE;
    created_new_archive = MZ_TRUE;
  }
  अन्यथा
  {
    // Append to an existing archive.
    अगर (!mz_zip_reader_init_file(&zip_archive, pZip_filename, level_and_flags | MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY))
      वापस MZ_FALSE;
    अगर (!mz_zip_writer_init_from_reader(&zip_archive, pZip_filename))
    {
      mz_zip_reader_end(&zip_archive);
      वापस MZ_FALSE;
    }
  }
  status = mz_zip_writer_add_mem_ex(&zip_archive, pArchive_name, pBuf, buf_आकार_2, pComment, comment_आकार, level_and_flags, 0, 0);
  // Always finalize, even if adding failed for some reason, so we have a valid central directory. (This may not always succeed, but we can try.)
  अगर (!mz_zip_writer_finalize_archive(&zip_archive))
    status = MZ_FALSE;
  अगर (!mz_zip_writer_end(&zip_archive))
    status = MZ_FALSE;
  अगर ((!status) && (created_new_archive))
  {
    // It's a new archive and something went wrong, so just delete it.
    पूर्णांक ignoredStatus = MZ_DELETE_FILE(pZip_filename);
    (व्योम)ignoredStatus;
  }
  वापस status;
}

व्योम *mz_zip_extract_archive_file_to_heap(स्थिर अक्षर *pZip_filename, स्थिर अक्षर *pArchive_name, माप_प्रकार *p_आकार, mz_uint flags)
{
  पूर्णांक file_सूचकांक;
  mz_zip_archive zip_archive;
  व्योम *p = शून्य;

  अगर (p_आकार)
    *p_आकार = 0;

  अगर ((!pZip_filename) || (!pArchive_name))
    वापस शून्य;

  MZ_CLEAR_OBJ(zip_archive);
  अगर (!mz_zip_reader_init_file(&zip_archive, pZip_filename, flags | MZ_ZIP_FLAG_DO_NOT_SORT_CENTRAL_DIRECTORY))
    वापस शून्य;

  अगर ((file_सूचकांक = mz_zip_reader_locate_file(&zip_archive, pArchive_name, शून्य, flags)) >= 0)
    p = mz_zip_reader_extract_to_heap(&zip_archive, file_सूचकांक, p_आकार, flags);

  mz_zip_reader_end(&zip_archive);
  वापस p;
}

#पूर्ण_अगर // #ifndef MINIZ_NO_STDIO

#पूर्ण_अगर // #ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

#पूर्ण_अगर // #ifndef MINIZ_NO_ARCHIVE_APIS

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#अगर_घोषित _MSC_VER
#आशय warning (निकालो)
#पूर्ण_अगर

#पूर्ण_अगर // MINIZ_HEADER_FILE_ONLY

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

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

#جيڪڏهن_وصف_نه_ٿيل MINIZ_سرو_INCLUDED
#وصف_ڪريو MINIZ_سرو_INCLUDED

/*#include <stdlib.h>*/

// Defines to completely disable specific portions of miniz.c:
// If all macros here are defined the only functionality remaining will be CRC-32, adler-32, tinfl, and tdefl.

// Define MINIZ_NO_STDIO to disable all usage and any functions which rely on stdio for file I/O.
#وصف_ڪريو MINIZ_NO_STDIO

// If MINIZ_NO_TIME is specified then the ZIP archive functions will not be able to get the current time, or
// get/set file times, and the C run-time funcs that get/set times won't be called.
// The current downside is the times written to your archives will be from 1979.
#وصف_ڪريو MINIZ_NO_وقت

// Define MINIZ_NO_DEFLATE_APIS to disable all compression API's.
//#define MINIZ_NO_DEFLATE_APIS

// Define MINIZ_NO_INFLATE_APIS to disable all decompression API's.
#وصف_ڪريو MINIZ_NO_INFLATE_APIS

// Define MINIZ_NO_ARCHIVE_APIS to disable all ZIP archive API's.
#وصف_ڪريو MINIZ_NO_ARCHIVE_APIS

// Define MINIZ_NO_ARCHIVE_APIS to disable all writing related ZIP archive API's.
#وصف_ڪريو MINIZ_NO_ARCHIVE_WRITING_APIS

// Define MINIZ_NO_ZLIB_APIS to remove all ZLIB-style compression/decompression API's.
#وصف_ڪريو MINIZ_NO_ZLIB_APIS

// Define MINIZ_NO_ZLIB_COMPATIBLE_NAME to disable zlib names, to prevent conflicts against stock zlib.
#وصف_ڪريو MINIZ_NO_ZLIB_COMPATIBLE_نالا

// Define MINIZ_NO_MALLOC to disable all calls to malloc, free, and realloc.
// Note if MINIZ_NO_MALLOC is defined then the user must always provide custom user alloc/free/realloc
// callbacks to the zlib and archive API's, and a few stand-alone helper API's which don't provide custom user
// functions (such as tdefl_compress_mem_to_heap() and tinfl_decompress_mem_to_heap()) won't work.
//#define MINIZ_NO_MALLOC
#وصف_ڪريو MINIZ_SDL_MALLOC

#جيڪڏهن_وصف_ٿيل MINIZ_NO_INFLATE_APIS
#وصف_ڪريو MINIZ_NO_ARCHIVE_APIS
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل MINIZ_NO_DEFLATE_APIS
#وصف_ڪريو MINIZ_NO_ARCHIVE_WRITING_APIS
#جيڪڏهن_پورو

// Define MINIZ_STATIC_FUNCTIONS to make all functions static. You probably
// want this if you're using miniz in a library
#وصف_ڪريو MINIZ_STATIC_FUNCTIONS

#إذا defined(__TINYC__) && (defined(__linux) || defined(__linux__))
  // TODO: Work around "error: include file 'sys\utime.h' when compiling with tcc on Linux
  #وصف_ڪريو MINIZ_NO_وقت
#جيڪڏهن_پورو

#إذا !defined(MINIZ_NO_وقت) && !defined(MINIZ_NO_ARCHIVE_APIS)
  #ضمن <time.h>
#جيڪڏهن_پورو

#إذا defined(_M_IX86) || defined(_M_X64) || defined(__i386__) || defined(__i386) || defined(__i486__) || defined(__i486) || defined(i386) || defined(__ia64__) || defined(__x86_64__)
// MINIZ_X86_OR_X64_CPU is only used to help set the below macros.
#وصف_ڪريو MINIZ_X86_OR_X64_CPU 1
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل MINIZ_LITTLE_ENDIAN /* if not defined by SDL */
#إذا (__BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__) || MINIZ_X86_OR_X64_CPU
// Set MINIZ_LITTLE_ENDIAN to 1 if the processor is little endian.
#وصف_ڪريو MINIZ_LITTLE_ENDIAN 1
#جيڪڏهن_پورو
#جيڪڏهن_پورو // MINIZ_LITTLE_ENDIAN /* if not defined by SDL */

#جيڪڏهن_وصف_نه_ٿيل MINIZ_USE_UNALIGNED_LOADS_AND_STORES
#إذا MINIZ_X86_OR_X64_CPU
// Set MINIZ_USE_UNALIGNED_LOADS_AND_STORES to 1 on CPU's that permit efficient integer loads and stores from unaligned addresses.
#وصف_ڪريو MINIZ_USE_UNALIGNED_LOADS_AND_STORES 1
#جيڪڏهن_پورو
#جيڪڏهن_پورو // MINIZ_USE_UNALIGNED_LOADS_AND_STORES

#إذا defined(_M_X64) || defined(_WIN64) || defined(__MINGW64__) || defined(_LP64) || defined(__LP64__) || defined(__ia64__) || defined(__x86_64__)
// Set MINIZ_HAS_64BIT_REGISTERS to 1 if operations on 64-bit integers are reasonably fast (and don't involve compiler generated calls to helper functions).
#وصف_ڪريو MINIZ_HAS_64_ٻٽو_انگ_REGISTERS 1
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل MINIZ_STATIC_FUNCTIONS
#وصف_ڪريو MINIZ_STATIC ساكن
#وإلا
#وصف_ڪريو MINIZ_STATIC
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل __cplusplus
خارجي "C" {
#جيڪڏهن_پورو

// ------------------- zlib-style API Definitions.

// For more compatibility with zlib, miniz.c uses unsigned long for some parameters/struct members. Beware: mz_ulong can be either 32 or 64-bits!
تعريفنوع بنانشان ڊگهو mz_ulong;

// mz_free() internally uses the MZ_FREE() macro (which by default calls free() unless you've modified the MZ_MALLOC macro) to release a block allocated from the heap.
MINIZ_STATIC فراغ mz_free(فراغ *p);

#وصف_ڪريو MZ_ADLER32_INIT (1)
// mz_adler32() returns the initial adler-32 value to use when called with ptr==NULL.
MINIZ_STATIC mz_ulong mz_adler32(mz_ulong adler, ثابت بنانشان حرف *ptr, size_t buf_len);

#وصف_ڪريو MZ_چڪري_جاچ_32_INIT (0)
// mz_crc32() returns the initial CRC-32 value to use when called with ptr==NULL.
MINIZ_STATIC mz_ulong mz_چڪري_جاچ_32(mz_ulong چڪري_جاچ, ثابت بنانشان حرف *ptr, size_t buf_len);

// Compression strategies.
تعداد { MZ_DEFAULT_STRATEGY = 0, MZ_FILTERED = 1, MZ_HUFFMAN_ONLY = 2, MZ_RLE = 3, MZ_FIXED = 4 };

//طريقو
#وصف_ڪريو MZ_DEFLATED 8

#جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_ZLIB_APIS

// Heap allocation callbacks.
// Note that mz_alloc_func parameter types purpsosely differ from zlib's: items/size is size_t, not unsigned long.
تعريفنوع فراغ *(*mz_alloc_func)(فراغ *opaque, size_t شيون, size_t سائيز);
تعريفنوع فراغ (*mz_free_func)(فراغ *opaque, فراغ *پتو);
تعريفنوع فراغ *(*mz_realloc_func)(فراغ *opaque, فراغ *پتو, size_t شيون, size_t سائيز);

#وصف_ڪريو MZ_نسخو          "9.1.15"
#وصف_ڪريو MZ_VERNUM           0x91F0
#وصف_ڪريو MZ_VER_MAJOR        9
#وصف_ڪريو MZ_VER_MINOR        1
#وصف_ڪريو MZ_VER_REVISION     15
#وصف_ڪريو MZ_VER_SUBREVISION  0

// Flush values. For typical usage you only need MZ_NO_FLUSH and MZ_FINISH. The other values are for advanced use (refer to the zlib docs).
تعداد { MZ_NO_FLUSH = 0, MZ_PARTIAL_FLUSH = 1, MZ_SYNC_FLUSH = 2, MZ_ڀريل_FLUSH = 3, MZ_پڄاڻي = 4, MZ_بلاڪ = 5 };

// Return status codes. MZ_PARAM_ERROR is non-standard.
تعداد { MZ_OK = 0, MZ_وهڪرو_پڇاڙي = 1, MZ_NEED_DICT = 2, MZ_ERRNO = -1, MZ_وهڪرو_ERROR = -2, MZ_معلومات_ERROR = -3, MZ_MEM_ERROR = -4, MZ_BUF_ERROR = -5, MZ_نسخو_ERROR = -6, MZ_PARAM_ERROR = -10000 };

// Compression levels: 0-9 are the standard zlib-style levels, 10 is best possible compression (not zlib compatible, and may be very slow), MZ_DEFAULT_COMPRESSION=MZ_DEFAULT_LEVEL.
تعداد { MZ_NO_COMPRESSION = 0, MZ_بهترين_رفتار = 1, MZ_بهترين_COMPRESSION = 9, MZ_UBER_COMPRESSION = 10, MZ_DEFAULT_LEVEL = 6, MZ_DEFAULT_COMPRESSION = -1 };

// Window bits
#وصف_ڪريو MZ_DEFAULT_دري_بٽ 15

بنية mz_اندروني_state;

// Compression/decompression stream struct.
تعريفنوع بنية mz_وهڪرو_s
{
  ثابت بنانشان حرف *ايندڙ_اندريون;     // pointer to next byte to read
  بنانشان صحيح avail_اندريون;            // number of bytes available at next_in
  mz_ulong ڪل_اندريون;                // total number of bytes consumed so far

  بنانشان حرف *ايندڙ_ٻاهريون;          // pointer to next byte to write
  بنانشان صحيح avail_ٻاهريون;           // number of bytes that can be written to next_out
  mz_ulong ڪل_ٻاهريون;               // total number of bytes produced so far

  حرف *نياپو;                        // error msg (unused)
  بنية mz_اندروني_state *state;  // internal state, allocated by zalloc/zfree

  mz_alloc_func zalloc;             // optional heap allocation function (defaults to malloc)
  mz_free_func zfree;               // optional heap free function (defaults to free)
  فراغ *opaque;                     // heap alloc function user pointer

  صحيح معلومات_type;                    // data_type (unused)
  mz_ulong adler;                   // adler32 of the source or uncompressed data
  mz_ulong reserved;                // not used
} mz_وهڪرو;

تعريفنوع mz_وهڪرو *mz_streamp;

// Returns the version string of miniz.c.
MINIZ_STATIC ثابت حرف *mz_نسخو(فراغ);

#جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_DEFLATE_APIS

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
MINIZ_STATIC صحيح mz_deflateInit(mz_streamp p_وهڪرو, صحيح level);

// mz_deflateInit2() is like mz_deflate(), except with more control:
// Additional parameters:
//   method must be MZ_DEFLATED
//   window_bits must be MZ_DEFAULT_WINDOW_BITS (to wrap the deflate stream with zlib header/adler-32 footer) or -MZ_DEFAULT_WINDOW_BITS (raw deflate/no header or footer)
//   mem_level must be between [1, 9] (it's checked but ignored by miniz.c)
MINIZ_STATIC صحيح mz_deflateInit2(mz_streamp p_وهڪرو, صحيح level, صحيح طريقو, صحيح دري_بٽ, صحيح mem_level, صحيح strategy);

// Quickly resets a compressor without having to reallocate anything. Same as calling mz_deflateEnd() followed by mz_deflateInit()/mz_deflateInit2().
MINIZ_STATIC صحيح mz_deflateReset(mz_streamp p_وهڪرو);

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
MINIZ_STATIC صحيح mz_deflate(mz_streamp p_وهڪرو, صحيح flush);

// mz_deflateEnd() deinitializes a compressor:
// Return values:
//  MZ_OK on success.
//  MZ_STREAM_ERROR if the stream is bogus.
MINIZ_STATIC صحيح mz_deflate_پڇاڙي(mz_streamp p_وهڪرو);

// mz_deflateBound() returns a (very) conservative upper bound on the amount of data that could be generated by deflate(), assuming flush is set to only MZ_NO_FLUSH or MZ_FINISH.
MINIZ_STATIC mz_ulong mz_deflateBound(mz_streamp p_وهڪرو, mz_ulong ذريعو_len);

// Single-call compression functions mz_compress() and mz_compress2():
// Returns MZ_OK on success, or one of the error codes from mz_deflate() on failure.
MINIZ_STATIC صحيح mz_compress(بنانشان حرف *pDest, mz_ulong *pDest_len, ثابت بنانشان حرف *p_ذريعو, mz_ulong ذريعو_len);
MINIZ_STATIC صحيح mz_compress2(بنانشان حرف *pDest, mz_ulong *pDest_len, ثابت بنانشان حرف *p_ذريعو, mz_ulong ذريعو_len, صحيح level);

// mz_compressBound() returns a (very) conservative upper bound on the amount of data that could be generated by calling mz_compress().
MINIZ_STATIC mz_ulong mz_compressBound(mz_ulong ذريعو_len);

#جيڪڏهن_پورو /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_INFLATE_APIS

// Initializes a decompressor.
MINIZ_STATIC صحيح mz_inflateInit(mz_streamp p_وهڪرو);

// mz_inflateInit2() is like mz_inflateInit() with an additional option that controls the window size and whether or not the stream has been wrapped with a zlib header/footer:
// window_bits must be MZ_DEFAULT_WINDOW_BITS (to parse zlib header/footer) or -MZ_DEFAULT_WINDOW_BITS (raw deflate).
MINIZ_STATIC صحيح mz_inflateInit2(mz_streamp p_وهڪرو, صحيح دري_بٽ);

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
MINIZ_STATIC صحيح mz_inflate(mz_streamp p_وهڪرو, صحيح flush);

// Deinitializes a decompressor.
MINIZ_STATIC صحيح mz_inflate_پڇاڙي(mz_streamp p_وهڪرو);

// Single-call decompression.
// Returns MZ_OK on success, or one of the error codes from mz_inflate() on failure.
MINIZ_STATIC صحيح mz_uncompress(بنانشان حرف *pDest, mz_ulong *pDest_len, ثابت بنانشان حرف *p_ذريعو, mz_ulong ذريعو_len);
#جيڪڏهن_پورو /*#ifndef MINIZ_NO_INFLATE_APIS*/

// Returns a string description of the specified error code, or NULL if the error code is invalid.
MINIZ_STATIC ثابت حرف *mz_error(صحيح err);

// Redefine zlib-compatible names to miniz equivalents, so miniz.c can be used as a drop-in replacement for the subset of zlib that miniz.c supports.
// Define MINIZ_NO_ZLIB_COMPATIBLE_NAMES to disable zlib-compatibility if you use zlib in the same project.
#جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_ZLIB_COMPATIBLE_نالا
  تعريفنوع بنانشان حرف Byte;
  تعريفنوع بنانشان صحيح uInt;
  تعريفنوع mz_ulong uLong;
  تعريفنوع Byte Bytef;
  تعريفنوع uInt uIntf;
  تعريفنوع حرف charf;
  تعريفنوع صحيح intf;
  تعريفنوع فراغ *voidpf;
  تعريفنوع uLong uLongf;
  تعريفنوع فراغ *voidp;
  تعريفنوع فراغ *ثابت voidpc;
  #وصف_ڪريو Z_NULL                0
  #وصف_ڪريو Z_NO_FLUSH            MZ_NO_FLUSH
  #وصف_ڪريو Z_PARTIAL_FLUSH       MZ_PARTIAL_FLUSH
  #وصف_ڪريو Z_SYNC_FLUSH          MZ_SYNC_FLUSH
  #وصف_ڪريو Z_ڀريل_FLUSH          MZ_ڀريل_FLUSH
  #وصف_ڪريو Z_پڄاڻي              MZ_پڄاڻي
  #وصف_ڪريو Z_بلاڪ               MZ_بلاڪ
  #وصف_ڪريو Z_OK                  MZ_OK
  #وصف_ڪريو Z_وهڪرو_پڇاڙي          MZ_وهڪرو_پڇاڙي
  #وصف_ڪريو Z_NEED_DICT           MZ_NEED_DICT
  #وصف_ڪريو Z_ERRNO               MZ_ERRNO
  #وصف_ڪريو Z_وهڪرو_ERROR        MZ_وهڪرو_ERROR
  #وصف_ڪريو Z_معلومات_ERROR          MZ_معلومات_ERROR
  #وصف_ڪريو Z_MEM_ERROR           MZ_MEM_ERROR
  #وصف_ڪريو Z_BUF_ERROR           MZ_BUF_ERROR
  #وصف_ڪريو Z_نسخو_ERROR       MZ_نسخو_ERROR
  #وصف_ڪريو Z_PARAM_ERROR         MZ_PARAM_ERROR
  #وصف_ڪريو Z_NO_COMPRESSION      MZ_NO_COMPRESSION
  #وصف_ڪريو Z_بهترين_رفتار          MZ_بهترين_رفتار
  #وصف_ڪريو Z_بهترين_COMPRESSION    MZ_بهترين_COMPRESSION
  #وصف_ڪريو Z_DEFAULT_COMPRESSION MZ_DEFAULT_COMPRESSION
  #وصف_ڪريو Z_DEFAULT_STRATEGY    MZ_DEFAULT_STRATEGY
  #وصف_ڪريو Z_FILTERED            MZ_FILTERED
  #وصف_ڪريو Z_HUFFMAN_ONLY        MZ_HUFFMAN_ONLY
  #وصف_ڪريو Z_RLE                 MZ_RLE
  #وصف_ڪريو Z_FIXED               MZ_FIXED
  #وصف_ڪريو Z_DEFLATED            MZ_DEFLATED
  #وصف_ڪريو Z_DEFAULT_دري_بٽ MZ_DEFAULT_دري_بٽ
  #وصف_ڪريو alloc_func            mz_alloc_func
  #وصف_ڪريو free_func             mz_free_func
  #وصف_ڪريو اندروني_state        mz_اندروني_state
  #وصف_ڪريو z_وهڪرو              mz_وهڪرو
#جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_DEFLATE_APIS
  #وصف_ڪريو deflateInit           mz_deflateInit
  #وصف_ڪريو deflateInit2          mz_deflateInit2
  #وصف_ڪريو deflateReset          mz_deflateReset
  #وصف_ڪريو deflate               mz_deflate
  #وصف_ڪريو deflate_پڇاڙي            mz_deflate_پڇاڙي
  #وصف_ڪريو deflateBound          mz_deflateBound
  #وصف_ڪريو compress              mz_compress
  #وصف_ڪريو compress2             mz_compress2
  #وصف_ڪريو compressBound         mz_compressBound
#جيڪڏهن_پورو /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_INFLATE_APIS
  #وصف_ڪريو inflateInit           mz_inflateInit
  #وصف_ڪريو inflateInit2          mz_inflateInit2
  #وصف_ڪريو inflate               mz_inflate
  #وصف_ڪريو inflate_پڇاڙي            mz_inflate_پڇاڙي
  #وصف_ڪريو uncompress            mz_uncompress
#جيڪڏهن_پورو /*#ifndef MINIZ_NO_INFLATE_APIS*/
  #وصف_ڪريو چڪري_جاچ_32                 mz_چڪري_جاچ_32
  #وصف_ڪريو adler32               mz_adler32
  #وصف_ڪريو MAX_WBITS             15
  #وصف_ڪريو MAX_MEM_LEVEL         9
  #وصف_ڪريو zError                mz_error
  #وصف_ڪريو ZLIB_نسخو          MZ_نسخو
  #وصف_ڪريو ZLIB_VERNUM           MZ_VERNUM
  #وصف_ڪريو ZLIB_VER_MAJOR        MZ_VER_MAJOR
  #وصف_ڪريو ZLIB_VER_MINOR        MZ_VER_MINOR
  #وصف_ڪريو ZLIB_VER_REVISION     MZ_VER_REVISION
  #وصف_ڪريو ZLIB_VER_SUBREVISION  MZ_VER_SUBREVISION
  #وصف_ڪريو zlib_نسخو           mz_نسخو
  #وصف_ڪريو zlib_نسخو_2          mz_نسخو()
#جيڪڏهن_پورو // #ifndef MINIZ_NO_ZLIB_COMPATIBLE_NAMES

#جيڪڏهن_پورو // MINIZ_NO_ZLIB_APIS

// ------------------- Types and macros

تعريفنوع بنانشان حرف mz_uint8;
تعريفنوع نشانوارو ننڍو mz_int16;
تعريفنوع بنانشان ننڍو mz_uint16;
تعريفنوع بنانشان صحيح mz_uint32;
تعريفنوع بنانشان صحيح mz_uint;
تعريفنوع ڊگهو ڊگهو mz_int64;
تعريفنوع بنانشان ڊگهو ڊگهو mz_uint64;
تعريفنوع صحيح mz_bool;

#وصف_ڪريو MZ_FALSE (0)
#وصف_ڪريو MZ_TRUE (1)

// An attempt to work around MSVC's spammy "warning C4127: conditional expression is constant" message.
#جيڪڏهن_وصف_ٿيل _MSC_VER
   #وصف_ڪريو MZ_MACRO_پڇاڙي طالما (0, 0)
#وإلا
   #وصف_ڪريو MZ_MACRO_پڇاڙي طالما (0)
#جيڪڏهن_پورو

// ------------------- ZIP archive reading/writing

#جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_ARCHIVE_APIS

تعداد
{
  MZ_ZIP_MAX_IO_BUF_سائيز = 64*1024,
  MZ_ZIP_MAX_ARCHIVE_FILENAME_سائيز = 260,
  MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_سائيز = 256
};

تعريفنوع بنية
{
  mz_uint32 m_file_اشاريو;
  mz_uint32 m_central_dir_ofs;
  mz_uint16 m_نسخو_made_by;
  mz_uint16 m_نسخو_needed;
  mz_uint16 m_ٻٽو_انگ_flag;
  mz_uint16 m_طريقو;
#جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_وقت
  وقت_t m_وقت;
#جيڪڏهن_پورو
  mz_uint32 m_چڪري_جاچ_32;
  mz_uint64 m_comp_سائيز;
  mz_uint64 m_uncomp_سائيز;
  mz_uint16 m_اندروني_attr;
  mz_uint32 m_external_attr;
  mz_uint64 m_local_سرو_ofs;
  mz_uint32 m_comment_سائيز;
  حرف m_filename[MZ_ZIP_MAX_ARCHIVE_FILENAME_سائيز];
  حرف m_comment[MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_سائيز];
} mz_zip_archive_file_stat;

تعريفنوع size_t (*mz_file_read_func)(فراغ *pOpaque, mz_uint64 file_ofs, فراغ *pBuf, size_t n);
تعريفنوع size_t (*mz_file_write_func)(فراغ *pOpaque, mz_uint64 file_ofs, ثابت فراغ *pBuf, size_t n);

بنية mz_zip_اندروني_state_ٽيگ;
تعريفنوع بنية mz_zip_اندروني_state_ٽيگ mz_zip_اندروني_state;

تعريفنوع تعداد
{
  MZ_ZIP_گهڻائي_INVALID = 0,
  MZ_ZIP_گهڻائي_READING = 1,
  MZ_ZIP_گهڻائي_WRITING = 2,
  MZ_ZIP_گهڻائي_WRITING_HAS_BEEN_FINALIZED = 3
} mz_zip_گهڻائي;

تعريفنوع بنية mz_zip_archive_ٽيگ
{
  mz_uint64 m_archive_سائيز;
  mz_uint64 m_central_directory_file_ofs;
  mz_uint m_ڪل_files;
  mz_zip_گهڻائي m_zip_گهڻائي;

  mz_uint m_file_وٿي_alignment;

  mz_alloc_func m_pAlloc;
  mz_free_func m_pFree;
  mz_realloc_func m_pRealloc;
  فراغ *m_pAlloc_opaque;

  mz_file_read_func m_pRead;
  mz_file_write_func m_pWrite;
  فراغ *m_pIO_opaque;

  mz_zip_اندروني_state *m_pState;

} mz_zip_archive;

تعريفنوع تعداد
{
  MZ_ZIP_FLAG_CASE_SENSITIVE                = 0x0100,
  MZ_ZIP_FLAG_IGNORE_رستو                   = 0x0200,
  MZ_ZIP_FLAG_COMPRESSED_معلومات               = 0x0400,
  MZ_ZIP_FLAG_DO_NOT_ترتيب_ڏيو_CENTRAL_DIRECTORY = 0x0800
} mz_zip_flags;

// ZIP archive reading

// Inits a ZIP archive reader.
// These functions read and validate the archive's central directory.
MINIZ_STATIC mz_bool mz_zip_reader_init(mz_zip_archive *pZip, mz_uint64 سائيز, mz_uint32 flags);
MINIZ_STATIC mz_bool mz_zip_reader_init_mem(mz_zip_archive *pZip, ثابت فراغ *pMem, size_t سائيز, mz_uint32 flags);

#جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_STDIO
MINIZ_STATIC mz_bool mz_zip_reader_init_file(mz_zip_archive *pZip, ثابت حرف *pFilename, mz_uint32 flags);
#جيڪڏهن_پورو

// Returns the total number of files in the archive.
MINIZ_STATIC mz_uint mz_zip_reader_get_انگ_files(mz_zip_archive *pZip);

// Returns detailed information about an archive file entry.
MINIZ_STATIC mz_bool mz_zip_reader_file_stat(mz_zip_archive *pZip, mz_uint file_اشاريو, mz_zip_archive_file_stat *pStat);

// Determines if an archive file entry is a directory entry.
MINIZ_STATIC mz_bool mz_zip_reader_is_file_a_directory(mz_zip_archive *pZip, mz_uint file_اشاريو);
MINIZ_STATIC mz_bool mz_zip_reader_is_file_encrypted(mz_zip_archive *pZip, mz_uint file_اشاريو);

// Retrieves the filename of an archive file entry.
// Returns the number of bytes written to pFilename, or if filename_buf_size is 0 this function returns the number of bytes needed to fully store the filename.
MINIZ_STATIC mz_uint mz_zip_reader_get_filename(mz_zip_archive *pZip, mz_uint file_اشاريو, حرف *pFilename, mz_uint filename_buf_سائيز);

// Attempts to locates a file in the archive's central directory.
// Valid flags: MZ_ZIP_FLAG_CASE_SENSITIVE, MZ_ZIP_FLAG_IGNORE_PATH
// Returns -1 if the file cannot be found.
MINIZ_STATIC صحيح mz_zip_reader_locate_file(mz_zip_archive *pZip, ثابت حرف *pName, ثابت حرف *pComment, mz_uint flags);

// Extracts a archive file to a memory buffer using no memory allocation.
MINIZ_STATIC mz_bool mz_zip_reader_ڪڍو_منزل_mem_no_alloc(mz_zip_archive *pZip, mz_uint file_اشاريو, فراغ *pBuf, size_t buf_سائيز_2, mz_uint flags, فراغ *pUser_read_buf, size_t user_read_buf_سائيز);
MINIZ_STATIC mz_bool mz_zip_reader_ڪڍو_file_منزل_mem_no_alloc(mz_zip_archive *pZip, ثابت حرف *pFilename, فراغ *pBuf, size_t buf_سائيز_2, mz_uint flags, فراغ *pUser_read_buf, size_t user_read_buf_سائيز);

// Extracts a archive file to a memory buffer.
MINIZ_STATIC mz_bool mz_zip_reader_ڪڍو_منزل_mem(mz_zip_archive *pZip, mz_uint file_اشاريو, فراغ *pBuf, size_t buf_سائيز_2, mz_uint flags);
MINIZ_STATIC mz_bool mz_zip_reader_ڪڍو_file_منزل_mem(mz_zip_archive *pZip, ثابت حرف *pFilename, فراغ *pBuf, size_t buf_سائيز_2, mz_uint flags);

// Extracts a archive file to a dynamically allocated heap buffer.
MINIZ_STATIC فراغ *mz_zip_reader_ڪڍو_منزل_ڍير(mz_zip_archive *pZip, mz_uint file_اشاريو, size_t *p_سائيز, mz_uint flags);
MINIZ_STATIC فراغ *mz_zip_reader_ڪڍو_file_منزل_ڍير(mz_zip_archive *pZip, ثابت حرف *pFilename, size_t *p_سائيز, mz_uint flags);

// Extracts a archive file using a callback function to output the file's data.
MINIZ_STATIC mz_bool mz_zip_reader_ڪڍو_منزل_callback(mz_zip_archive *pZip, mz_uint file_اشاريو, mz_file_write_func pCallback, فراغ *pOpaque, mz_uint flags);
MINIZ_STATIC mz_bool mz_zip_reader_ڪڍو_file_منزل_callback(mz_zip_archive *pZip, ثابت حرف *pFilename, mz_file_write_func pCallback, فراغ *pOpaque, mz_uint flags);

#جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_STDIO
// Extracts a archive file to a disk file and sets its last accessed and modified times.
// This function only extracts files, not archive directory records.
MINIZ_STATIC mz_bool mz_zip_reader_ڪڍو_منزل_file(mz_zip_archive *pZip, mz_uint file_اشاريو, ثابت حرف *pDst_filename, mz_uint flags);
MINIZ_STATIC mz_bool mz_zip_reader_ڪڍو_file_منزل_file(mz_zip_archive *pZip, ثابت حرف *pArchive_filename, ثابت حرف *pDst_filename, mz_uint flags);
#جيڪڏهن_پورو

// Ends archive reading, freeing all allocations, and closing the input archive file if mz_zip_reader_init_file() was used.
MINIZ_STATIC mz_bool mz_zip_reader_پڇاڙي(mz_zip_archive *pZip);

// ZIP archive writing

#جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_ARCHIVE_WRITING_APIS

// Inits a ZIP archive writer.
MINIZ_STATIC mz_bool mz_zip_writer_init(mz_zip_archive *pZip, mz_uint64 existing_سائيز);
MINIZ_STATIC mz_bool mz_zip_writer_init_ڍير(mz_zip_archive *pZip, size_t سائيز_منزل_reserve_at_beginning, size_t initial_ورهاست_سائيز);

#جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_STDIO
MINIZ_STATIC mz_bool mz_zip_writer_init_file(mz_zip_archive *pZip, ثابت حرف *pFilename, mz_uint64 سائيز_منزل_reserve_at_beginning);
#جيڪڏهن_پورو

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
MINIZ_STATIC mz_bool mz_zip_writer_جوڙيو_mem(mz_zip_archive *pZip, ثابت حرف *pArchive_name, ثابت فراغ *pBuf, size_t buf_سائيز_2, mz_uint level_and_flags);
MINIZ_STATIC mz_bool mz_zip_writer_جوڙيو_mem_ex(mz_zip_archive *pZip, ثابت حرف *pArchive_name, ثابت فراغ *pBuf, size_t buf_سائيز_2, ثابت فراغ *pComment, mz_uint16 comment_سائيز, mz_uint level_and_flags, mz_uint64 uncomp_سائيز, mz_uint32 uncomp_چڪري_جاچ_32);

#جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_STDIO
// Adds the contents of a disk file to an archive. This function also records the disk file's modified time into the archive.
// level_and_flags - compression level (0-10, see MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or just set to MZ_DEFAULT_COMPRESSION.
MINIZ_STATIC mz_bool mz_zip_writer_جوڙيو_file(mz_zip_archive *pZip, ثابت حرف *pArchive_name, ثابت حرف *pSrc_filename, ثابت فراغ *pComment, mz_uint16 comment_سائيز, mz_uint level_and_flags);
#جيڪڏهن_پورو

// Adds a file to an archive by fully cloning the data from another archive.
// This function fully clones the source file's compressed data (no recompression), along with its full filename, extra data, and comment fields.
MINIZ_STATIC mz_bool mz_zip_writer_جوڙيو_from_zip_reader(mz_zip_archive *pZip, mz_zip_archive *p_ذريعو_zip, mz_uint file_اشاريو);

// Finalizes the archive by writing the central directory records followed by the end of central directory record.
// After an archive is finalized, the only valid call on the mz_zip_archive struct is mz_zip_writer_end().
// An archive must be manually finalized by calling this function for it to be valid.
MINIZ_STATIC mz_bool mz_zip_writer_finalize_archive(mz_zip_archive *pZip);
MINIZ_STATIC mz_bool mz_zip_writer_finalize_ڍير_archive(mz_zip_archive *pZip, فراغ **pBuf, size_t *p_سائيز);

// Ends archive writing, freeing all allocations, and closing the output file if mz_zip_writer_init_file() was used.
// Note for the archive to be valid, it must have been finalized before ending.
MINIZ_STATIC mz_bool mz_zip_writer_پڇاڙي(mz_zip_archive *pZip);

// Misc. high-level helper functions:

// mz_zip_add_mem_to_archive_file_in_place() efficiently (but not atomically) appends a memory blob to a ZIP archive.
// level_and_flags - compression level (0-10, see MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or just set to MZ_DEFAULT_COMPRESSION.
MINIZ_STATIC mz_bool mz_zip_جوڙيو_mem_منزل_archive_file_اندريون_رکو(ثابت حرف *pZip_filename, ثابت حرف *pArchive_name, ثابت فراغ *pBuf, size_t buf_سائيز_2, ثابت فراغ *pComment, mz_uint16 comment_سائيز, mz_uint level_and_flags);

// Reads a single file from an archive into a heap block.
// Returns NULL on failure.
MINIZ_STATIC فراغ *mz_zip_ڪڍو_archive_file_منزل_ڍير(ثابت حرف *pZip_filename, ثابت حرف *pArchive_name, size_t *p_سائيز, mz_uint zip_flags);

#جيڪڏهن_پورو // #ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

#جيڪڏهن_پورو // #ifndef MINIZ_NO_ARCHIVE_APIS

// ------------------- Low-level Decompression API Definitions
#جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_INFLATE_APIS

// Decompression flags used by tinfl_decompress().
// TINFL_FLAG_PARSE_ZLIB_HEADER: If set, the input has a valid zlib header and ends with an adler32 checksum (it's a valid zlib stream). Otherwise, the input is a raw deflate stream.
// TINFL_FLAG_HAS_MORE_INPUT: If set, there are more input bytes available beyond the end of the supplied input buffer. If clear, the input buffer contains all remaining input.
// TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF: If set, the output buffer is large enough to hold the entire decompressed stream. If clear, the output buffer is at least the size of the dictionary (typically 32KB).
// TINFL_FLAG_COMPUTE_ADLER32: Force adler-32 checksum computation of the decompressed bytes.
تعداد
{
  TINFL_FLAG_PARSE_ZLIB_سرو = 1,
  TINFL_FLAG_HAS_وڌيڪ_داخلا = 2,
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
MINIZ_STATIC فراغ *tinfl_decompress_mem_منزل_ڍير(ثابت فراغ *pSrc_buf, size_t src_buf_len, size_t *p_ٻاهريون_len, صحيح flags);

// tinfl_decompress_mem_to_mem() decompresses a block in memory to another block in memory.
// Returns TINFL_DECOMPRESS_MEM_TO_MEM_FAILED on failure, or the number of bytes written on success.
#وصف_ڪريو TINFL_DECOMPRESS_MEM_منزل_MEM_FAILED ((size_t)(-1))
MINIZ_STATIC size_t tinfl_decompress_mem_منزل_mem(فراغ *p_ٻاهريون_buf, size_t ٻاهريون_buf_len, ثابت فراغ *pSrc_buf, size_t src_buf_len, صحيح flags);

// tinfl_decompress_mem_to_callback() decompresses a block in memory to an internal 32KB buffer, and a user provided callback function will be called to flush the buffer.
// Returns 1 on success or 0 on failure.
تعريفنوع صحيح (*tinfl_put_buf_func_ptr)(ثابت فراغ* pBuf, صحيح len, فراغ *pUser);
MINIZ_STATIC صحيح tinfl_decompress_mem_منزل_callback(ثابت فراغ *p_اندريون_buf, size_t *p_اندريون_buf_سائيز, tinfl_put_buf_func_ptr pPut_buf_func, فراغ *pPut_buf_user, صحيح flags);

بنية tinfl_decompressor_ٽيگ; تعريفنوع بنية tinfl_decompressor_ٽيگ tinfl_decompressor;

// Max size of LZ dictionary.
#وصف_ڪريو TINFL_LZ_DICT_سائيز 32768

// Return status.
تعريفنوع تعداد
{
  TINFL_حالت_BAD_PARAM = -3,
  TINFL_حالت_ADLER32_MISMATCH = -2,
  TINFL_حالت_FAILED = -1,
  TINFL_حالت_پورو = 0,
  TINFL_حالت_NEEDS_وڌيڪ_داخلا = 1,
  TINFL_حالت_HAS_وڌيڪ_OUTPUT = 2
} tinfl_حالت;

// Initializes the decompressor to its initial state.
#وصف_ڪريو tinfl_init(r) افعل { (r)->m_state = 0; } MZ_MACRO_پڇاڙي
#وصف_ڪريو tinfl_get_adler32(r) (r)->m_check_adler32

// Main low-level decompressor coroutine function. This is the only function actually needed for decompression. All the other functions are just high-level helpers for improved usability.
// This is a universal API, i.e. it can be used as a building block to build any desired higher level decompression API. In the limit case, it can be called once per every byte input or output.
MINIZ_STATIC tinfl_حالت tinfl_decompress(tinfl_decompressor *r, ثابت mz_uint8 *p_اندريون_buf_ايندڙ, size_t *p_اندريون_buf_سائيز, mz_uint8 *p_ٻاهريون_buf_شروعات, mz_uint8 *p_ٻاهريون_buf_ايندڙ, size_t *p_ٻاهريون_buf_سائيز, ثابت mz_uint32 decomp_flags);

// Internal/private bits follow.
تعداد
{
  TINFL_MAX_HUFF_TABLES = 3, TINFL_MAX_HUFF_SYMBOLS_0 = 288, TINFL_MAX_HUFF_SYMBOLS_1 = 32, TINFL_MAX_HUFF_SYMBOLS_2 = 19,
  TINFL_FAST_LOOKUP_بٽ = 10, TINFL_FAST_LOOKUP_سائيز = 1 << TINFL_FAST_LOOKUP_بٽ
};

تعريفنوع بنية
{
  mz_uint8 m_ڪوڊ_سائيز[TINFL_MAX_HUFF_SYMBOLS_0];
  mz_int16 m_look_مٿي[TINFL_FAST_LOOKUP_سائيز], m_وڻ[TINFL_MAX_HUFF_SYMBOLS_0 * 2];
} tinfl_huff_جدول;

#إذا MINIZ_HAS_64_ٻٽو_انگ_REGISTERS
  #وصف_ڪريو TINFL_USE_64_ٻٽو_انگ_BITBUF 1
#جيڪڏهن_پورو

#إذا TINFL_USE_64_ٻٽو_انگ_BITBUF
  تعريفنوع mz_uint64 tinfl_ٻٽو_انگ_buf_t;
  #وصف_ڪريو TINFL_BITBUF_سائيز (64)
#وإلا
  تعريفنوع mz_uint32 tinfl_ٻٽو_انگ_buf_t;
  #وصف_ڪريو TINFL_BITBUF_سائيز (32)
#جيڪڏهن_پورو

بنية tinfl_decompressor_ٽيگ
{
  mz_uint32 m_state, m_انگ_بٽ, m_zhdr0, m_zhdr1, m_z_adler32, m_final, m_type, m_check_adler32, m_dist, m_counter, m_انگ_extra, m_جدول_sizes[TINFL_MAX_HUFF_TABLES];
  tinfl_ٻٽو_انگ_buf_t m_ٻٽو_انگ_buf;
  size_t m_dist_from_ٻاهريون_buf_شروعات;
  tinfl_huff_جدول m_tables[TINFL_MAX_HUFF_TABLES];
  mz_uint8 m_raw_سرو[4], m_len_codes[TINFL_MAX_HUFF_SYMBOLS_0 + TINFL_MAX_HUFF_SYMBOLS_1 + 137];
};
#جيڪڏهن_پورو /*#ifndef MINIZ_NO_INFLATE_APIS*/

// ------------------- Low-level Compression API Definitions
#جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_DEFLATE_APIS

// Set TDEFL_LESS_MEMORY to 1 to use less memory (compression will be slightly slower, and raw/dynamic blocks will be output more frequently).
#وصف_ڪريو TDEFL_LESS_يادگيري 0

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
  TDEFL_WRITE_ZLIB_سرو             = 0x01000,
  TDEFL_COMPUTE_ADLER32               = 0x02000,
  TDEFL_GREEDY_PARSING_FLAG           = 0x04000,
  TDEFL_NONDETERMINISTIC_PARSING_FLAG = 0x08000,
  TDEFL_RLE_MATCHES                   = 0x10000,
  TDEFL_FILTER_MATCHES                = 0x20000,
  TDEFL_FORCE_ALL_STATIC_بلاڪون       = 0x40000,
  TDEFL_FORCE_ALL_RAW_بلاڪون          = 0x80000
};

#جيڪڏهن_وصف_نه_ٿيل MINIZ_SDL_NOUNUSED
// High level compression functions:
// tdefl_compress_mem_to_heap() compresses a block in memory to a heap block allocated via malloc().
// On entry:
//  pSrc_buf, src_buf_len: Pointer and size of source block to compress.
//  flags: The max match finder probes (default is 128) logically OR'd against the above flags. Higher probes are slower but improve compression.
// On return:
//  Function returns a pointer to the compressed data, or NULL on failure.
//  *pOut_len will be set to the compressed data's size, which could be larger than src_buf_len on uncompressible data.
//  The caller must free() the returned block when it's no longer needed.
MINIZ_STATIC فراغ *tdefl_compress_mem_منزل_ڍير(ثابت فراغ *pSrc_buf, size_t src_buf_len, size_t *p_ٻاهريون_len, صحيح flags);

// tdefl_compress_mem_to_mem() compresses a block in memory to another block in memory.
// Returns 0 on failure.
MINIZ_STATIC size_t tdefl_compress_mem_منزل_mem(فراغ *p_ٻاهريون_buf, size_t ٻاهريون_buf_len, ثابت فراغ *pSrc_buf, size_t src_buf_len, صحيح flags);
#جيڪڏهن_پورو /* MINIZ_SDL_NOUNUSED */

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
MINIZ_STATIC فراغ *tdefl_write_image_منزل_png_file_اندريون_يادگيري_ex(ثابت فراغ *pImage, صحيح w, صحيح h, صحيح انگ_chans, صحيح bpl, size_t *p_Len_ٻاهريون, mz_uint level, mz_bool flip, mz_uint8 *plte, صحيح plte_سائيز, mz_uint8 *trns, صحيح trns_سائيز);
#جيڪڏهن_وصف_نه_ٿيل MINIZ_SDL_NOUNUSED
MINIZ_STATIC فراغ *tdefl_write_image_منزل_png_file_اندريون_يادگيري(ثابت فراغ *pImage, صحيح w, صحيح h, صحيح انگ_chans, صحيح bpl, size_t *p_Len_ٻاهريون);
#جيڪڏهن_پورو

// Output stream interface. The compressor uses this interface to write compressed data. It'll typically be called TDEFL_OUT_BUF_SIZE at a time.
تعريفنوع mz_bool (*tdefl_put_buf_func_ptr)(ثابت فراغ* pBuf, صحيح len, فراغ *pUser);

#جيڪڏهن_وصف_نه_ٿيل MINIZ_SDL_NOUNUSED
// tdefl_compress_mem_to_output() compresses a block to an output stream. The above helpers use this function internally.
MINIZ_STATIC mz_bool tdefl_compress_mem_منزل_output(ثابت فراغ *pBuf, size_t buf_len, tdefl_put_buf_func_ptr pPut_buf_func, فراغ *pPut_buf_user, صحيح flags);
#جيڪڏهن_پورو

//enum { TDEFL_MAX_HUFF_TABLES = 3, TDEFL_MAX_HUFF_SYMBOLS_0 = 288, TDEFL_MAX_HUFF_SYMBOLS_1 = 32, TDEFL_MAX_HUFF_SYMBOLS_2 = 19, TDEFL_LZ_DICT_SIZE = 32768, TDEFL_LZ_DICT_SIZE_MASK = TDEFL_LZ_DICT_SIZE - 1, TDEFL_MIN_MATCH_LEN = 3, TDEFL_MAX_MATCH_LEN = 258 };
#وصف_ڪريو TDEFL_MAX_HUFF_TABLES	3
#وصف_ڪريو TDEFL_MAX_HUFF_SYMBOLS_0 288
#وصف_ڪريو TDEFL_MAX_HUFF_SYMBOLS_1 32
#وصف_ڪريو TDEFL_MAX_HUFF_SYMBOLS_2 19
#وصف_ڪريو TDEFL_LZ_DICT_سائيز 32768
#وصف_ڪريو TDEFL_LZ_DICT_سائيز_نقاب	( TDEFL_LZ_DICT_سائيز - 1 )
#وصف_ڪريو TDEFL_MIN_ميلاپ_LEN	3
#وصف_ڪريو TDEFL_MAX_ميلاپ_LEN 258

// TDEFL_OUT_BUF_SIZE MUST be large enough to hold a single entire compressed output block (using static/fixed Huffman codes).
#إذا TDEFL_LESS_يادگيري
تعداد { TDEFL_LZ_ڪوڊ_BUF_سائيز = 24 * 1024, TDEFL_ٻاهريون_BUF_سائيز = (TDEFL_LZ_ڪوڊ_BUF_سائيز * 13 ) / 10, TDEFL_MAX_HUFF_SYMBOLS = 288, TDEFL_LZ_HASH_بٽ = 12, TDEFL_LEVEL1_HASH_سائيز_نقاب = 4095, TDEFL_LZ_HASH_سرڪايو = (TDEFL_LZ_HASH_بٽ + 2) / 3, TDEFL_LZ_HASH_سائيز = 1 << TDEFL_LZ_HASH_بٽ };
#وإلا
تعداد { TDEFL_LZ_ڪوڊ_BUF_سائيز = 64 * 1024, TDEFL_ٻاهريون_BUF_سائيز = (TDEFL_LZ_ڪوڊ_BUF_سائيز * 13 ) / 10, TDEFL_MAX_HUFF_SYMBOLS = 288, TDEFL_LZ_HASH_بٽ = 15, TDEFL_LEVEL1_HASH_سائيز_نقاب = 4095, TDEFL_LZ_HASH_سرڪايو = (TDEFL_LZ_HASH_بٽ + 2) / 3, TDEFL_LZ_HASH_سائيز = 1 << TDEFL_LZ_HASH_بٽ };
#جيڪڏهن_پورو

// The low-level tdefl functions below may be used directly if the above helper functions aren't flexible enough. The low-level functions don't make any heap allocations, unlike the above helper functions.
تعريفنوع تعداد
{
  TDEFL_حالت_BAD_PARAM = -2,
  TDEFL_حالت_PUT_BUF_FAILED = -1,
  TDEFL_حالت_OKAY = 0,
  TDEFL_حالت_پورو = 1,
} tdefl_حالت;

// Must map to MZ_NO_FLUSH, MZ_SYNC_FLUSH, etc. enums
تعريفنوع تعداد
{
  TDEFL_NO_FLUSH = 0,
  TDEFL_SYNC_FLUSH = 2,
  TDEFL_ڀريل_FLUSH = 3,
  TDEFL_پڄاڻي = 4
} tdefl_flush;

// tdefl's compression state structure.
تعريفنوع بنية
{
  tdefl_put_buf_func_ptr m_pPut_buf_func;
  فراغ *m_pPut_buf_user;
  mz_uint m_flags, m_max_probes[2];
  صحيح m_greedy_parsing;
  mz_uint m_adler32, m_lookahead_pos, m_lookahead_سائيز, m_dict_سائيز;
  mz_uint8 *m_p_LZ_ڪوڊ_buf, *m_pLZ_flags, *m_pOutput_buf, *m_p_Output_buf_پڇاڙي;
  mz_uint m_انگ_flags_کاٻو, m_ڪل_lz_بائيٽون, m_lz_ڪوڊ_buf_dict_pos, m_بٽ_اندريون, m_ٻٽو_انگ_بفر;
  mz_uint m_saved_ميلاپ_dist, m_saved_ميلاپ_len, m_saved_lit, m_output_flush_ofs, m_output_flush_بچيل, m_ختم, m_بلاڪ_اشاريو, m_چاهي_منزل_پڄاڻي;
  tdefl_حالت m_prev_return_حالت;
  ثابت فراغ *m_p_اندريون_buf;
  فراغ *m_p_ٻاهريون_buf;
  size_t *m_p_اندريون_buf_سائيز, *m_p_ٻاهريون_buf_سائيز;
  tdefl_flush m_flush;
  ثابت mz_uint8 *m_pSrc;
  size_t m_src_buf_کاٻو, m_ٻاهريون_buf_ofs;
  mz_uint8 m_dict[TDEFL_LZ_DICT_سائيز + TDEFL_MAX_ميلاپ_LEN - 1];
  mz_uint16 m_huff_ڳڻپ[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint16 m_huff_codes[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint8 m_huff_ڪوڊ_sizes[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint8 m_lz_ڪوڊ_buf[TDEFL_LZ_ڪوڊ_BUF_سائيز];
  mz_uint16 m_ايندڙ[TDEFL_LZ_DICT_سائيز];
  mz_uint16 m_hash[TDEFL_LZ_HASH_سائيز];
  mz_uint8 m_output_buf[TDEFL_ٻاهريون_BUF_سائيز];
} tdefl_compressor;

// Initializes the compressor.
// There is no corresponding deinit() function because the tdefl API's do not dynamically allocate memory.
// pBut_buf_func: If NULL, output data will be supplied to the specified callback. In this case, the user should call the tdefl_compress_buffer() API for compression.
// If pBut_buf_func is NULL the user should always call the tdefl_compress() API.
// flags: See the above enums (TDEFL_HUFFMAN_ONLY, TDEFL_WRITE_ZLIB_HEADER, etc.)
MINIZ_STATIC tdefl_حالت tdefl_init(tdefl_compressor *d, tdefl_put_buf_func_ptr pPut_buf_func, فراغ *pPut_buf_user, صحيح flags);

// Compresses a block of data, consuming as much of the specified input buffer as possible, and writing as much compressed data to the specified output buffer as possible.
MINIZ_STATIC tdefl_حالت tdefl_compress(tdefl_compressor *d, ثابت فراغ *p_اندريون_buf, size_t *p_اندريون_buf_سائيز, فراغ *p_ٻاهريون_buf, size_t *p_ٻاهريون_buf_سائيز, tdefl_flush flush);

// tdefl_compress_buffer() is only usable when the tdefl_init() is called with a non-NULL tdefl_put_buf_func_ptr.
// tdefl_compress_buffer() always consumes the entire input buffer.
MINIZ_STATIC tdefl_حالت tdefl_compress_بفر(tdefl_compressor *d, ثابت فراغ *p_اندريون_buf, size_t اندريون_buf_سائيز, tdefl_flush flush);

#جيڪڏهن_وصف_نه_ٿيل MINIZ_SDL_NOUNUSED
MINIZ_STATIC tdefl_حالت tdefl_get_prev_return_حالت(tdefl_compressor *d);
MINIZ_STATIC mz_uint32 tdefl_get_adler32(tdefl_compressor *d);
#جيڪڏهن_پورو

// Can't use tdefl_create_comp_flags_from_zip_params if MINIZ_NO_ZLIB_APIS isn't defined, because it uses some of its macros.
#جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_ZLIB_APIS
// Create tdefl_compress() flags given zlib-style compression parameters.
// level may range from [0,10] (where 10 is absolute max compression, but may be much slower on some files)
// window_bits may be -15 (raw deflate) or 15 (zlib)
// strategy may be either MZ_DEFAULT_STRATEGY, MZ_FILTERED, MZ_HUFFMAN_ONLY, MZ_RLE, or MZ_FIXED
MINIZ_STATIC mz_uint tdefl_create_comp_flags_from_zip_params(صحيح level, صحيح دري_بٽ, صحيح strategy);
#جيڪڏهن_پورو // #ifndef MINIZ_NO_ZLIB_APIS

#جيڪڏهن_پورو /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو // MINIZ_HEADER_INCLUDED

// ------------------- End of Header: Implementation follows. (If you only want the header, define MINIZ_HEADER_FILE_ONLY.)

#جيڪڏهن_وصف_نه_ٿيل MINIZ_سرو_FILE_ONLY

#جيڪڏهن_وصف_ٿيل _MSC_VER
#هدايت warning (ڌڪو)
#هدايت warning (disable:4505) // unreferenced local function has been removed
#جيڪڏهن_پورو

تعريفنوع بنانشان حرف mz_validate_uint16[حجم(mz_uint16)==2 ? 1 : -1];
تعريفنوع بنانشان حرف mz_validate_uint32[حجم(mz_uint32)==4 ? 1 : -1];
تعريفنوع بنانشان حرف mz_validate_uint64[حجم(mz_uint64)==8 ? 1 : -1];

/*#include <string.h>*/

#جيڪڏهن_وصف_نه_ٿيل MZ_ASSERT
#ضمن <assert.h>
#وصف_ڪريو MZ_ASSERT(x) أكد(x)
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل MINIZ_NO_MALLOC
  #وصف_ڪريو MZ_MALLOC(x) عدم
  #وصف_ڪريو MZ_FREE(x) (فراغ)x, ((فراغ)0)
  #وصف_ڪريو MZ_REALLOC(p, x) عدم
#وإلاإذا defined(MINIZ_SDL_MALLOC)
  #وصف_ڪريو MZ_MALLOC(x) SDL_malloc(x)
  #وصف_ڪريو MZ_FREE(x) SDL_free(x)
  #وصف_ڪريو MZ_REALLOC(p, x) SDL_realloc(p, x)
#وإلا
  #وصف_ڪريو MZ_MALLOC(x) يادگيري_ڏيو(x)
  #وصف_ڪريو MZ_FREE(x) حرر(x)
  #وصف_ڪريو MZ_REALLOC(p, x) realloc(p, x)
#جيڪڏهن_پورو

#وصف_ڪريو MZ_MAX(a,b) (((a)>(b))?(a):(b))
#وصف_ڪريو MZ_MIN(a,b) (((a)<(b))?(a):(b))
#وصف_ڪريو MZ_CLEAR_OBJ(obj) memset(&(obj), 0, حجم(obj))
#وصف_ڪريو MZ_CLEAR_ARR(obj) memset((obj), 0, حجم(obj))
#وصف_ڪريو MZ_CLEAR_PTR(obj) memset((obj), 0, حجم(*obj))

#إذا MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  #وصف_ڪريو MZ_READ_LE16(p) *((ثابت mz_uint16 *)(p))
  #وصف_ڪريو MZ_READ_LE32(p) *((ثابت mz_uint32 *)(p))
#وإلا
  #وصف_ڪريو MZ_READ_LE16(p) ((mz_uint32)(((ثابت mz_uint8 *)(p))[0]) | ((mz_uint32)(((ثابت mz_uint8 *)(p))[1]) << 8U))
  #وصف_ڪريو MZ_READ_LE32(p) ((mz_uint32)(((ثابت mz_uint8 *)(p))[0]) | ((mz_uint32)(((ثابت mz_uint8 *)(p))[1]) << 8U) | ((mz_uint32)(((ثابت mz_uint8 *)(p))[2]) << 16U) | ((mz_uint32)(((ثابت mz_uint8 *)(p))[3]) << 24U))
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل _MSC_VER
  #وصف_ڪريو MZ_FORCEINLINE __forceinline
#وإلاإذا defined(__GNUC__)
  #وصف_ڪريو MZ_FORCEINLINE مضمن __attribute__((__always_inline__))
#وإلا
  #وصف_ڪريو MZ_FORCEINLINE مضمن
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل __cplusplus
  خارجي "C" {
#جيڪڏهن_پورو

// ------------------- zlib-style API's

mz_ulong mz_adler32(mz_ulong adler, ثابت بنانشان حرف *ptr, size_t buf_len)
{
  mz_uint32 i, s1 = (mz_uint32)(adler & 0xffff), s2 = (mz_uint32)(adler >> 16); size_t بلاڪ_len = buf_len % 5552;
  إذا (!ptr) أرجع MZ_ADLER32_INIT;
  طالما (buf_len) {
    لكل (i = 0; i + 7 < بلاڪ_len; i += 8, ptr += 8) {
      s1 += ptr[0]; s2 += s1; s1 += ptr[1]; s2 += s1; s1 += ptr[2]; s2 += s1; s1 += ptr[3]; s2 += s1;
      s1 += ptr[4]; s2 += s1; s1 += ptr[5]; s2 += s1; s1 += ptr[6]; s2 += s1; s1 += ptr[7]; s2 += s1;
    }
    لكل ( ; i < بلاڪ_len; ++i) { s1 += *ptr++; s2 += s1; }
    s1 %= 65521U; s2 %= 65521U; buf_len -= بلاڪ_len; بلاڪ_len = 5552;
  }
  أرجع (s2 << 16) + s1;
}

// Karl Malbrain's compact CRC-32. See "A compact CCITT crc16 and crc32 C implementation that balances processor cache usage against speed": http://www.geocities.com/malbrain/
mz_ulong mz_چڪري_جاچ_32(mz_ulong چڪري_جاچ, ثابت mz_uint8 *ptr, size_t buf_len)
{
  ساكن ثابت mz_uint32 s_چڪري_جاچ_32[16] = { 0, 0x1db71064, 0x3b6e20c8, 0x26d930ac, 0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
    0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c, 0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c };
  mz_uint32 crcu32 = (mz_uint32)چڪري_جاچ;
  إذا (!ptr) أرجع MZ_چڪري_جاچ_32_INIT;
  crcu32 = ~crcu32; طالما (buf_len--) { mz_uint8 b = *ptr++; crcu32 = (crcu32 >> 4) ^ s_چڪري_جاچ_32[(crcu32 & 0xF) ^ (b & 0xF)]; crcu32 = (crcu32 >> 4) ^ s_چڪري_جاچ_32[(crcu32 & 0xF) ^ (b >> 4)]; }
  أرجع ~crcu32;
}

MINIZ_STATIC فراغ mz_free(فراغ *p)
{
  MZ_FREE(p);
}

#جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_ZLIB_APIS

ساكن فراغ *def_alloc_func(فراغ *opaque, size_t شيون, size_t سائيز) { (فراغ)opaque, (فراغ)شيون, (فراغ)سائيز; أرجع MZ_MALLOC(شيون * سائيز); }
ساكن فراغ def_free_func(فراغ *opaque, فراغ *پتو) { (فراغ)opaque, (فراغ)پتو; MZ_FREE(پتو); }
ساكن فراغ *def_realloc_func(فراغ *opaque, فراغ *پتو, size_t شيون, size_t سائيز) { (فراغ)opaque, (فراغ)پتو, (فراغ)شيون, (فراغ)سائيز; أرجع MZ_REALLOC(پتو, شيون * سائيز); }

ثابت حرف *mz_نسخو(فراغ)
{
  أرجع MZ_نسخو;
}

#جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_DEFLATE_APIS

صحيح mz_deflateInit(mz_streamp p_وهڪرو, صحيح level)
{
  أرجع mz_deflateInit2(p_وهڪرو, level, MZ_DEFLATED, MZ_DEFAULT_دري_بٽ, 9, MZ_DEFAULT_STRATEGY);
}

صحيح mz_deflateInit2(mz_streamp p_وهڪرو, صحيح level, صحيح طريقو, صحيح دري_بٽ, صحيح mem_level, صحيح strategy)
{
  tdefl_compressor *pComp;
  mz_uint comp_flags = TDEFL_COMPUTE_ADLER32 | tdefl_create_comp_flags_from_zip_params(level, دري_بٽ, strategy);

  إذا (!p_وهڪرو) أرجع MZ_وهڪرو_ERROR;
  إذا ((طريقو != MZ_DEFLATED) || ((mem_level < 1) || (mem_level > 9)) || ((دري_بٽ != MZ_DEFAULT_دري_بٽ) && (-دري_بٽ != MZ_DEFAULT_دري_بٽ))) أرجع MZ_PARAM_ERROR;

  p_وهڪرو->معلومات_type = 0;
  p_وهڪرو->adler = MZ_ADLER32_INIT;
  p_وهڪرو->نياپو = عدم;
  p_وهڪرو->reserved = 0;
  p_وهڪرو->ڪل_اندريون = 0;
  p_وهڪرو->ڪل_ٻاهريون = 0;
  إذا (!p_وهڪرو->zalloc) p_وهڪرو->zalloc = def_alloc_func;
  إذا (!p_وهڪرو->zfree) p_وهڪرو->zfree = def_free_func;

  pComp = (tdefl_compressor *)p_وهڪرو->zalloc(p_وهڪرو->opaque, 1, حجم(tdefl_compressor));
  إذا (!pComp)
    أرجع MZ_MEM_ERROR;

  p_وهڪرو->state = (بنية mz_اندروني_state *)pComp;

  إذا (tdefl_init(pComp, عدم, عدم, comp_flags) != TDEFL_حالت_OKAY)
  {
    mz_deflate_پڇاڙي(p_وهڪرو);
    أرجع MZ_PARAM_ERROR;
  }

  أرجع MZ_OK;
}

صحيح mz_deflateReset(mz_streamp p_وهڪرو)
{
  إذا ((!p_وهڪرو) || (!p_وهڪرو->state) || (!p_وهڪرو->zalloc) || (!p_وهڪرو->zfree)) أرجع MZ_وهڪرو_ERROR;
  p_وهڪرو->ڪل_اندريون = p_وهڪرو->ڪل_ٻاهريون = 0;
  tdefl_init((tdefl_compressor*)p_وهڪرو->state, عدم, عدم, ((tdefl_compressor*)p_وهڪرو->state)->m_flags);
  أرجع MZ_OK;
}

صحيح mz_deflate(mz_streamp p_وهڪرو, صحيح flush)
{
  size_t اندريون_بائيٽون, ٻاهريون_بائيٽون;
  mz_ulong orig_ڪل_اندريون, orig_ڪل_ٻاهريون;
  صحيح mz_حالت = MZ_OK;

  إذا ((!p_وهڪرو) || (!p_وهڪرو->state) || (flush < 0) || (flush > MZ_پڄاڻي) || (!p_وهڪرو->ايندڙ_ٻاهريون)) أرجع MZ_وهڪرو_ERROR;
  إذا (!p_وهڪرو->avail_ٻاهريون) أرجع MZ_BUF_ERROR;

  إذا (flush == MZ_PARTIAL_FLUSH) flush = MZ_SYNC_FLUSH;

  إذا (((tdefl_compressor*)p_وهڪرو->state)->m_prev_return_حالت == TDEFL_حالت_پورو)
    أرجع (flush == MZ_پڄاڻي) ? MZ_وهڪرو_پڇاڙي : MZ_BUF_ERROR;

  orig_ڪل_اندريون = p_وهڪرو->ڪل_اندريون; orig_ڪل_ٻاهريون = p_وهڪرو->ڪل_ٻاهريون;
  لكل ( ; ; )
  {
    tdefl_حالت defl_حالت;
    اندريون_بائيٽون = p_وهڪرو->avail_اندريون; ٻاهريون_بائيٽون = p_وهڪرو->avail_ٻاهريون;

    defl_حالت = tdefl_compress((tdefl_compressor*)p_وهڪرو->state, p_وهڪرو->ايندڙ_اندريون, &اندريون_بائيٽون, p_وهڪرو->ايندڙ_ٻاهريون, &ٻاهريون_بائيٽون, (tdefl_flush)flush);
    p_وهڪرو->ايندڙ_اندريون += (mz_uint)اندريون_بائيٽون; p_وهڪرو->avail_اندريون -= (mz_uint)اندريون_بائيٽون;
    p_وهڪرو->ڪل_اندريون += (mz_uint)اندريون_بائيٽون; p_وهڪرو->adler = tdefl_get_adler32((tdefl_compressor*)p_وهڪرو->state);

    p_وهڪرو->ايندڙ_ٻاهريون += (mz_uint)ٻاهريون_بائيٽون; p_وهڪرو->avail_ٻاهريون -= (mz_uint)ٻاهريون_بائيٽون;
    p_وهڪرو->ڪل_ٻاهريون += (mz_uint)ٻاهريون_بائيٽون;

    إذا (defl_حالت < 0)
    {
      mz_حالت = MZ_وهڪرو_ERROR;
      اكسر;
    }
    وإلا إذا (defl_حالت == TDEFL_حالت_پورو)
    {
      mz_حالت = MZ_وهڪرو_پڇاڙي;
      اكسر;
    }
    وإلا إذا (!p_وهڪرو->avail_ٻاهريون)
      اكسر;
    وإلا إذا ((!p_وهڪرو->avail_اندريون) && (flush != MZ_پڄاڻي))
    {
      إذا ((flush) || (p_وهڪرو->ڪل_اندريون != orig_ڪل_اندريون) || (p_وهڪرو->ڪل_ٻاهريون != orig_ڪل_ٻاهريون))
        اكسر;
      أرجع MZ_BUF_ERROR; // Can't make forward progress without some input.
    }
  }
  أرجع mz_حالت;
}

صحيح mz_deflate_پڇاڙي(mz_streamp p_وهڪرو)
{
  إذا (!p_وهڪرو) أرجع MZ_وهڪرو_ERROR;
  إذا (p_وهڪرو->state)
  {
    p_وهڪرو->zfree(p_وهڪرو->opaque, p_وهڪرو->state);
    p_وهڪرو->state = عدم;
  }
  أرجع MZ_OK;
}

mz_ulong mz_deflateBound(mz_streamp p_وهڪرو, mz_ulong ذريعو_len)
{
  (فراغ)p_وهڪرو;
  // This is really over conservative. (And lame, but it's actually pretty tricky to compute a true upper bound given the way tdefl's blocking works.)
  أرجع MZ_MAX(128 + (ذريعو_len * 110) / 100, 128 + ذريعو_len + ((ذريعو_len / (31 * 1024)) + 1) * 5);
}

صحيح mz_compress2(بنانشان حرف *pDest, mz_ulong *pDest_len, ثابت بنانشان حرف *p_ذريعو, mz_ulong ذريعو_len, صحيح level)
{
  صحيح حالت;
  mz_وهڪرو وهڪرو;
  memset(&وهڪرو, 0, حجم(وهڪرو));

  // In case mz_ulong is 64-bits (argh I hate longs).
  إذا ((ذريعو_len | *pDest_len) > 0xFFFFFFFFU) أرجع MZ_PARAM_ERROR;

  وهڪرو.ايندڙ_اندريون = p_ذريعو;
  وهڪرو.avail_اندريون = (mz_uint32)ذريعو_len;
  وهڪرو.ايندڙ_ٻاهريون = pDest;
  وهڪرو.avail_ٻاهريون = (mz_uint32)*pDest_len;

  حالت = mz_deflateInit(&وهڪرو, level);
  إذا (حالت != MZ_OK) أرجع حالت;

  حالت = mz_deflate(&وهڪرو, MZ_پڄاڻي);
  إذا (حالت != MZ_وهڪرو_پڇاڙي)
  {
    mz_deflate_پڇاڙي(&وهڪرو);
    أرجع (حالت == MZ_OK) ? MZ_BUF_ERROR : حالت;
  }

  *pDest_len = وهڪرو.ڪل_ٻاهريون;
  أرجع mz_deflate_پڇاڙي(&وهڪرو);
}

صحيح mz_compress(بنانشان حرف *pDest, mz_ulong *pDest_len, ثابت بنانشان حرف *p_ذريعو, mz_ulong ذريعو_len)
{
  أرجع mz_compress2(pDest, pDest_len, p_ذريعو, ذريعو_len, MZ_DEFAULT_COMPRESSION);
}

mz_ulong mz_compressBound(mz_ulong ذريعو_len)
{
  أرجع mz_deflateBound(عدم, ذريعو_len);
}

#جيڪڏهن_پورو /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_INFLATE_APIS

تعريفنوع بنية
{
  tinfl_decompressor m_decomp;
  mz_uint m_dict_ofs, m_dict_avail, m_پهريون_call, m_has_flushed; صحيح m_دري_بٽ;
  mz_uint8 m_dict[TINFL_LZ_DICT_سائيز];
  tinfl_حالت m_آخري_حالت;
} inflate_state;

صحيح mz_inflateInit2(mz_streamp p_وهڪرو, صحيح دري_بٽ)
{
  inflate_state *pDecomp;
  إذا (!p_وهڪرو) أرجع MZ_وهڪرو_ERROR;
  إذا ((دري_بٽ != MZ_DEFAULT_دري_بٽ) && (-دري_بٽ != MZ_DEFAULT_دري_بٽ)) أرجع MZ_PARAM_ERROR;

  p_وهڪرو->معلومات_type = 0;
  p_وهڪرو->adler = 0;
  p_وهڪرو->نياپو = عدم;
  p_وهڪرو->ڪل_اندريون = 0;
  p_وهڪرو->ڪل_ٻاهريون = 0;
  p_وهڪرو->reserved = 0;
  إذا (!p_وهڪرو->zalloc) p_وهڪرو->zalloc = def_alloc_func;
  إذا (!p_وهڪرو->zfree) p_وهڪرو->zfree = def_free_func;

  pDecomp = (inflate_state*)p_وهڪرو->zalloc(p_وهڪرو->opaque, 1, حجم(inflate_state));
  إذا (!pDecomp) أرجع MZ_MEM_ERROR;

  p_وهڪرو->state = (بنية mz_اندروني_state *)pDecomp;

  tinfl_init(&pDecomp->m_decomp);
  pDecomp->m_dict_ofs = 0;
  pDecomp->m_dict_avail = 0;
  pDecomp->m_آخري_حالت = TINFL_حالت_NEEDS_وڌيڪ_داخلا;
  pDecomp->m_پهريون_call = 1;
  pDecomp->m_has_flushed = 0;
  pDecomp->m_دري_بٽ = دري_بٽ;

  أرجع MZ_OK;
}

صحيح mz_inflateInit(mz_streamp p_وهڪرو)
{
   أرجع mz_inflateInit2(p_وهڪرو, MZ_DEFAULT_دري_بٽ);
}

صحيح mz_inflate(mz_streamp p_وهڪرو, صحيح flush)
{
  inflate_state* pState;
  mz_uint n, پهريون_call, decomp_flags = TINFL_FLAG_COMPUTE_ADLER32;
  size_t اندريون_بائيٽون, ٻاهريون_بائيٽون, orig_avail_اندريون;
  tinfl_حالت حالت;

  إذا ((!p_وهڪرو) || (!p_وهڪرو->state)) أرجع MZ_وهڪرو_ERROR;
  إذا (flush == MZ_PARTIAL_FLUSH) flush = MZ_SYNC_FLUSH;
  إذا ((flush) && (flush != MZ_SYNC_FLUSH) && (flush != MZ_پڄاڻي)) أرجع MZ_وهڪرو_ERROR;

  pState = (inflate_state*)p_وهڪرو->state;
  إذا (pState->m_دري_بٽ > 0) decomp_flags |= TINFL_FLAG_PARSE_ZLIB_سرو;
  orig_avail_اندريون = p_وهڪرو->avail_اندريون;

  پهريون_call = pState->m_پهريون_call; pState->m_پهريون_call = 0;
  إذا (pState->m_آخري_حالت < 0) أرجع MZ_معلومات_ERROR;

  إذا (pState->m_has_flushed && (flush != MZ_پڄاڻي)) أرجع MZ_وهڪرو_ERROR;
  pState->m_has_flushed |= (flush == MZ_پڄاڻي);

  إذا ((flush == MZ_پڄاڻي) && (پهريون_call))
  {
    // MZ_FINISH on the first call implies that the input and output buffers are large enough to hold the entire compressed/decompressed file.
    decomp_flags |= TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF;
    اندريون_بائيٽون = p_وهڪرو->avail_اندريون; ٻاهريون_بائيٽون = p_وهڪرو->avail_ٻاهريون;
    حالت = tinfl_decompress(&pState->m_decomp, p_وهڪرو->ايندڙ_اندريون, &اندريون_بائيٽون, p_وهڪرو->ايندڙ_ٻاهريون, p_وهڪرو->ايندڙ_ٻاهريون, &ٻاهريون_بائيٽون, decomp_flags);
    pState->m_آخري_حالت = حالت;
    p_وهڪرو->ايندڙ_اندريون += (mz_uint)اندريون_بائيٽون; p_وهڪرو->avail_اندريون -= (mz_uint)اندريون_بائيٽون; p_وهڪرو->ڪل_اندريون += (mz_uint)اندريون_بائيٽون;
    p_وهڪرو->adler = tinfl_get_adler32(&pState->m_decomp);
    p_وهڪرو->ايندڙ_ٻاهريون += (mz_uint)ٻاهريون_بائيٽون; p_وهڪرو->avail_ٻاهريون -= (mz_uint)ٻاهريون_بائيٽون; p_وهڪرو->ڪل_ٻاهريون += (mz_uint)ٻاهريون_بائيٽون;

    إذا (حالت < 0)
      أرجع MZ_معلومات_ERROR;
    وإلا إذا (حالت != TINFL_حالت_پورو)
    {
      pState->m_آخري_حالت = TINFL_حالت_FAILED;
      أرجع MZ_BUF_ERROR;
    }
    أرجع MZ_وهڪرو_پڇاڙي;
  }
  // flush != MZ_FINISH then we must assume there's more input.
  إذا (flush != MZ_پڄاڻي) decomp_flags |= TINFL_FLAG_HAS_وڌيڪ_داخلا;

  إذا (pState->m_dict_avail)
  {
    n = MZ_MIN(pState->m_dict_avail, p_وهڪرو->avail_ٻاهريون);
    يادگيري_نقل(p_وهڪرو->ايندڙ_ٻاهريون, pState->m_dict + pState->m_dict_ofs, n);
    p_وهڪرو->ايندڙ_ٻاهريون += n; p_وهڪرو->avail_ٻاهريون -= n; p_وهڪرو->ڪل_ٻاهريون += n;
    pState->m_dict_avail -= n; pState->m_dict_ofs = (pState->m_dict_ofs + n) & (TINFL_LZ_DICT_سائيز - 1);
    أرجع ((pState->m_آخري_حالت == TINFL_حالت_پورو) && (!pState->m_dict_avail)) ? MZ_وهڪرو_پڇاڙي : MZ_OK;
  }

  لكل ( ; ; )
  {
    اندريون_بائيٽون = p_وهڪرو->avail_اندريون;
    ٻاهريون_بائيٽون = TINFL_LZ_DICT_سائيز - pState->m_dict_ofs;

    حالت = tinfl_decompress(&pState->m_decomp, p_وهڪرو->ايندڙ_اندريون, &اندريون_بائيٽون, pState->m_dict, pState->m_dict + pState->m_dict_ofs, &ٻاهريون_بائيٽون, decomp_flags);
    pState->m_آخري_حالت = حالت;

    p_وهڪرو->ايندڙ_اندريون += (mz_uint)اندريون_بائيٽون; p_وهڪرو->avail_اندريون -= (mz_uint)اندريون_بائيٽون;
    p_وهڪرو->ڪل_اندريون += (mz_uint)اندريون_بائيٽون; p_وهڪرو->adler = tinfl_get_adler32(&pState->m_decomp);

    pState->m_dict_avail = (mz_uint)ٻاهريون_بائيٽون;

    n = MZ_MIN(pState->m_dict_avail, p_وهڪرو->avail_ٻاهريون);
    يادگيري_نقل(p_وهڪرو->ايندڙ_ٻاهريون, pState->m_dict + pState->m_dict_ofs, n);
    p_وهڪرو->ايندڙ_ٻاهريون += n; p_وهڪرو->avail_ٻاهريون -= n; p_وهڪرو->ڪل_ٻاهريون += n;
    pState->m_dict_avail -= n; pState->m_dict_ofs = (pState->m_dict_ofs + n) & (TINFL_LZ_DICT_سائيز - 1);

    إذا (حالت < 0)
       أرجع MZ_معلومات_ERROR; // Stream is corrupted (there could be some uncompressed data left in the output dictionary - oh well).
    وإلا إذا ((حالت == TINFL_حالت_NEEDS_وڌيڪ_داخلا) && (!orig_avail_اندريون))
      أرجع MZ_BUF_ERROR; // Signal caller that we can't make forward progress without supplying more input or by setting flush to MZ_FINISH.
    وإلا إذا (flush == MZ_پڄاڻي)
    {
       // The output buffer MUST be large to hold the remaining uncompressed data when flush==MZ_FINISH.
       إذا (حالت == TINFL_حالت_پورو)
          أرجع pState->m_dict_avail ? MZ_BUF_ERROR : MZ_وهڪرو_پڇاڙي;
       // status here must be TINFL_STATUS_HAS_MORE_OUTPUT, which means there's at least 1 more byte on the way. If there's no more room left in the output buffer then something is wrong.
       وإلا إذا (!p_وهڪرو->avail_ٻاهريون)
          أرجع MZ_BUF_ERROR;
    }
    وإلا إذا ((حالت == TINFL_حالت_پورو) || (!p_وهڪرو->avail_اندريون) || (!p_وهڪرو->avail_ٻاهريون) || (pState->m_dict_avail))
      اكسر;
  }

  أرجع ((حالت == TINFL_حالت_پورو) && (!pState->m_dict_avail)) ? MZ_وهڪرو_پڇاڙي : MZ_OK;
}

صحيح mz_inflate_پڇاڙي(mz_streamp p_وهڪرو)
{
  إذا (!p_وهڪرو)
    أرجع MZ_وهڪرو_ERROR;
  إذا (p_وهڪرو->state)
  {
    p_وهڪرو->zfree(p_وهڪرو->opaque, p_وهڪرو->state);
    p_وهڪرو->state = عدم;
  }
  أرجع MZ_OK;
}

صحيح mz_uncompress(بنانشان حرف *pDest, mz_ulong *pDest_len, ثابت بنانشان حرف *p_ذريعو, mz_ulong ذريعو_len)
{
  mz_وهڪرو وهڪرو;
  صحيح حالت;
  memset(&وهڪرو, 0, حجم(وهڪرو));

  // In case mz_ulong is 64-bits (argh I hate longs).
  إذا ((ذريعو_len | *pDest_len) > 0xFFFFFFFFU) أرجع MZ_PARAM_ERROR;

  وهڪرو.ايندڙ_اندريون = p_ذريعو;
  وهڪرو.avail_اندريون = (mz_uint32)ذريعو_len;
  وهڪرو.ايندڙ_ٻاهريون = pDest;
  وهڪرو.avail_ٻاهريون = (mz_uint32)*pDest_len;

  حالت = mz_inflateInit(&وهڪرو);
  إذا (حالت != MZ_OK)
    أرجع حالت;

  حالت = mz_inflate(&وهڪرو, MZ_پڄاڻي);
  إذا (حالت != MZ_وهڪرو_پڇاڙي)
  {
    mz_inflate_پڇاڙي(&وهڪرو);
    أرجع ((حالت == MZ_BUF_ERROR) && (!وهڪرو.avail_اندريون)) ? MZ_معلومات_ERROR : حالت;
  }
  *pDest_len = وهڪرو.ڪل_ٻاهريون;

  أرجع mz_inflate_پڇاڙي(&وهڪرو);
}

#جيڪڏهن_پورو /*#ifndef MINIZ_NO_INFLATE_APIS*/

ثابت حرف *mz_error(صحيح err)
{
  ساكن بنية { صحيح m_err; ثابت حرف *m_pDesc; } s_error_descs[] =
  {
    { MZ_OK, "" }, { MZ_وهڪرو_پڇاڙي, "stream end" }, { MZ_NEED_DICT, "need dictionary" }, { MZ_ERRNO, "file error" }, { MZ_وهڪرو_ERROR, "stream error" },
    { MZ_معلومات_ERROR, "data error" }, { MZ_MEM_ERROR, "out of memory" }, { MZ_BUF_ERROR, "buf error" }, { MZ_نسخو_ERROR, "version error" }, { MZ_PARAM_ERROR, "parameter error" }
  };
  mz_uint i; لكل (i = 0; i < حجم(s_error_descs) / حجم(s_error_descs[0]); ++i) إذا (s_error_descs[i].m_err == err) أرجع s_error_descs[i].m_pDesc;
  أرجع عدم;
}

#جيڪڏهن_پورو //MINIZ_NO_ZLIB_APIS

// ------------------- Low-level Decompression (completely independent from all compression API's)
#جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_INFLATE_APIS

#وصف_ڪريو TINFL_MEMCPY(d, s, l) يادگيري_نقل(d, s, l)
#وصف_ڪريو TINFL_MEMSET(p, c, l) memset(p, c, l)

#وصف_ڪريو TINFL_CR_BEGIN بدل(r->m_state) { حالة 0:
#وصف_ڪريو TINFL_CR_RETURN(state_اشاريو, نتيجو) افعل { حالت = نتيجو; r->m_state = state_اشاريو; اذهب common_exit; حالة state_اشاريو:; } MZ_MACRO_پڇاڙي
#وصف_ڪريو TINFL_CR_RETURN_FOREVER(state_اشاريو, نتيجو) افعل { لكل ( ; ; ) { TINFL_CR_RETURN(state_اشاريو, نتيجو); } } MZ_MACRO_پڇاڙي
#وصف_ڪريو TINFL_CR_پڄاڻي }

// TODO: If the caller has indicated that there's no more input, and we attempt to read beyond the input buf, then something is wrong with the input because the inflator never
// reads ahead more than it needs to. Currently TINFL_GET_BYTE() pads the end of the stream with 0's in this scenario.
#وصف_ڪريو TINFL_GET_BYTE(state_اشاريو, c) افعل { \
  إذا (p_اندريون_buf_cur >= p_اندريون_buf_پڇاڙي) { \
    لكل ( ; ; ) { \
      إذا (decomp_flags & TINFL_FLAG_HAS_وڌيڪ_داخلا) { \
        TINFL_CR_RETURN(state_اشاريو, TINFL_حالت_NEEDS_وڌيڪ_داخلا); \
        إذا (p_اندريون_buf_cur < p_اندريون_buf_پڇاڙي) { \
          c = *p_اندريون_buf_cur++; \
          اكسر; \
        } \
      } وإلا { \
        c = 0; \
        اكسر; \
      } \
    } \
  } وإلا c = *p_اندريون_buf_cur++; } MZ_MACRO_پڇاڙي

#وصف_ڪريو TINFL_NEED_بٽ(state_اشاريو, n) افعل { mz_uint c; TINFL_GET_BYTE(state_اشاريو, c); ٻٽو_انگ_buf |= (((tinfl_ٻٽو_انگ_buf_t)c) << انگ_بٽ); انگ_بٽ += 8; } طالما (انگ_بٽ < (mz_uint)(n))
#وصف_ڪريو TINFL_SKIP_بٽ(state_اشاريو, n) افعل { إذا (انگ_بٽ < (mz_uint)(n)) { TINFL_NEED_بٽ(state_اشاريو, n); } ٻٽو_انگ_buf >>= (n); انگ_بٽ -= (n); } MZ_MACRO_پڇاڙي
#وصف_ڪريو TINFL_GET_بٽ(state_اشاريو, b, n) افعل { إذا (انگ_بٽ < (mz_uint)(n)) { TINFL_NEED_بٽ(state_اشاريو, n); } b = ٻٽو_انگ_buf & ((1 << (n)) - 1); ٻٽو_انگ_buf >>= (n); انگ_بٽ -= (n); } MZ_MACRO_پڇاڙي

// TINFL_HUFF_BITBUF_FILL() is only used rarely, when the number of bytes remaining in the input buffer falls below 2.
// It reads just enough bytes from the input stream that are needed to decode the next Huffman code (and absolutely no more). It works by trying to fully decode a
// Huffman code by using whatever bits are currently present in the bit buffer. If this fails, it reads another byte, and tries again until it succeeds or until the
// bit buffer contains >=15 bits (deflate's max. Huffman code size).
#وصف_ڪريو TINFL_HUFF_BITBUF_FILL(state_اشاريو, pHuff) \
  افعل { \
    عارضي = (pHuff)->m_look_مٿي[ٻٽو_انگ_buf & (TINFL_FAST_LOOKUP_سائيز - 1)]; \
    إذا (عارضي >= 0) { \
      ڪوڊ_len = عارضي >> 9; \
      إذا ((ڪوڊ_len) && (انگ_بٽ >= ڪوڊ_len)) \
          اكسر; \
    } وإلا إذا (انگ_بٽ > TINFL_FAST_LOOKUP_بٽ) { \
       ڪوڊ_len = TINFL_FAST_LOOKUP_بٽ; \
       افعل { \
          عارضي = (pHuff)->m_وڻ[~عارضي + ((ٻٽو_انگ_buf >> ڪوڊ_len++) & 1)]; \
       } طالما ((عارضي < 0) && (انگ_بٽ >= (ڪوڊ_len + 1))); \
       إذا (عارضي >= 0) اكسر; \
    } \
    TINFL_GET_BYTE(state_اشاريو, c); \
    ٻٽو_انگ_buf |= (((tinfl_ٻٽو_انگ_buf_t)c) << انگ_بٽ); \
    انگ_بٽ += 8; \
  } طالما (انگ_بٽ < 15);

// TINFL_HUFF_DECODE() decodes the next Huffman coded symbol. It's more complex than you would initially expect because the zlib API expects the decompressor to never read
// beyond the final byte of the deflate stream. (In other words, when this macro wants to read another byte from the input, it REALLY needs another byte in order to fully
// decode the next Huffman code.) Handling this properly is particularly important on raw deflate (non-zlib) streams, which aren't followed by a byte aligned adler-32.
// The slow path is only executed at the very end of the input buffer.
#وصف_ڪريو TINFL_HUFF_DECODE(state_اشاريو, sym, pHuff) افعل { \
  صحيح عارضي; mz_uint ڪوڊ_len, c; \
  إذا (انگ_بٽ < 15) { \
    إذا ((p_اندريون_buf_پڇاڙي - p_اندريون_buf_cur) < 2) { \
       TINFL_HUFF_BITBUF_FILL(state_اشاريو, pHuff); \
    } وإلا { \
       ٻٽو_انگ_buf |= (((tinfl_ٻٽو_انگ_buf_t)p_اندريون_buf_cur[0]) << انگ_بٽ) | (((tinfl_ٻٽو_انگ_buf_t)p_اندريون_buf_cur[1]) << (انگ_بٽ + 8)); p_اندريون_buf_cur += 2; انگ_بٽ += 16; \
    } \
  } \
  إذا ((عارضي = (pHuff)->m_look_مٿي[ٻٽو_انگ_buf & (TINFL_FAST_LOOKUP_سائيز - 1)]) >= 0) \
    ڪوڊ_len = عارضي >> 9, عارضي &= 511; \
  وإلا { \
    ڪوڊ_len = TINFL_FAST_LOOKUP_بٽ; افعل { عارضي = (pHuff)->m_وڻ[~عارضي + ((ٻٽو_انگ_buf >> ڪوڊ_len++) & 1)]; } طالما (عارضي < 0); \
  } sym = عارضي; ٻٽو_انگ_buf >>= ڪوڊ_len; انگ_بٽ -= ڪوڊ_len; } MZ_MACRO_پڇاڙي

tinfl_حالت tinfl_decompress(tinfl_decompressor *r, ثابت mz_uint8 *p_اندريون_buf_ايندڙ, size_t *p_اندريون_buf_سائيز, mz_uint8 *p_ٻاهريون_buf_شروعات, mz_uint8 *p_ٻاهريون_buf_ايندڙ, size_t *p_ٻاهريون_buf_سائيز, ثابت mz_uint32 decomp_flags)
{
  ساكن ثابت صحيح s_ڊيگهائي_بنياد[31] = { 3,4,5,6,7,8,9,10,11,13, 15,17,19,23,27,31,35,43,51,59, 67,83,99,115,131,163,195,227,258,0,0 };
  ساكن ثابت صحيح s_ڊيگهائي_extra[31]= { 0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,0,0,0 };
  ساكن ثابت صحيح s_dist_بنياد[32] = { 1,2,3,4,5,7,9,13,17,25,33,49,65,97,129,193, 257,385,513,769,1025,1537,2049,3073,4097,6145,8193,12289,16385,24577,0,0};
  ساكن ثابت صحيح s_dist_extra[32] = { 0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13};
  ساكن ثابت mz_uint8 s_ڊيگهائي_dezigzag[19] = { 16,17,18,0,8,7,9,6,10,5,11,4,12,3,13,2,14,1,15 };
  ساكن ثابت صحيح s_min_جدول_sizes[3] = { 257, 1, 4 };

  tinfl_حالت حالت = TINFL_حالت_FAILED; mz_uint32 انگ_بٽ, dist, counter, انگ_extra; tinfl_ٻٽو_انگ_buf_t ٻٽو_انگ_buf;
  ثابت mz_uint8 *p_اندريون_buf_cur = p_اندريون_buf_ايندڙ, *ثابت p_اندريون_buf_پڇاڙي = p_اندريون_buf_ايندڙ + *p_اندريون_buf_سائيز;
  mz_uint8 *p_ٻاهريون_buf_cur = p_ٻاهريون_buf_ايندڙ, *ثابت p_ٻاهريون_buf_پڇاڙي = p_ٻاهريون_buf_ايندڙ + *p_ٻاهريون_buf_سائيز;
  size_t ٻاهريون_buf_سائيز_نقاب = (decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF) ? (size_t)-1 : ((p_ٻاهريون_buf_ايندڙ - p_ٻاهريون_buf_شروعات) + *p_ٻاهريون_buf_سائيز) - 1, dist_from_ٻاهريون_buf_شروعات;

  // Ensure the output buffer's size is a power of 2, unless the output buffer is large enough to hold the entire output file (in which case it doesn't matter).
  إذا (((ٻاهريون_buf_سائيز_نقاب + 1) & ٻاهريون_buf_سائيز_نقاب) || (p_ٻاهريون_buf_ايندڙ < p_ٻاهريون_buf_شروعات)) { *p_اندريون_buf_سائيز = *p_ٻاهريون_buf_سائيز = 0; أرجع TINFL_حالت_BAD_PARAM; }

  انگ_بٽ = r->m_انگ_بٽ; ٻٽو_انگ_buf = r->m_ٻٽو_انگ_buf; dist = r->m_dist; counter = r->m_counter; انگ_extra = r->m_انگ_extra; dist_from_ٻاهريون_buf_شروعات = r->m_dist_from_ٻاهريون_buf_شروعات;
  TINFL_CR_BEGIN

  ٻٽو_انگ_buf = انگ_بٽ = dist = counter = انگ_extra = r->m_zhdr0 = r->m_zhdr1 = 0; r->m_z_adler32 = r->m_check_adler32 = 1;
  إذا (decomp_flags & TINFL_FLAG_PARSE_ZLIB_سرو)
  {
    TINFL_GET_BYTE(1, r->m_zhdr0); TINFL_GET_BYTE(2, r->m_zhdr1);
    counter = (((r->m_zhdr0 * 256 + r->m_zhdr1) % 31 != 0) || (r->m_zhdr1 & 32) || ((r->m_zhdr0 & 15) != 8));
    إذا (!(decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF)) counter |= (((1U << (8U + (r->m_zhdr0 >> 4))) > 32768U) || ((ٻاهريون_buf_سائيز_نقاب + 1) < (size_t)(1U << (8U + (r->m_zhdr0 >> 4)))));
    إذا (counter) { TINFL_CR_RETURN_FOREVER(36, TINFL_حالت_FAILED); }
  }

  افعل
  {
    TINFL_GET_بٽ(3, r->m_final, 3); r->m_type = r->m_final >> 1;
    إذا (r->m_type == 0)
    {
      TINFL_SKIP_بٽ(5, انگ_بٽ & 7);
      لكل (counter = 0; counter < 4; ++counter) { إذا (انگ_بٽ) TINFL_GET_بٽ(6, r->m_raw_سرو[counter], 8); وإلا TINFL_GET_BYTE(7, r->m_raw_سرو[counter]); }
      إذا ((counter = (r->m_raw_سرو[0] | (r->m_raw_سرو[1] << 8))) != (mz_uint)(0xFFFF ^ (r->m_raw_سرو[2] | (r->m_raw_سرو[3] << 8)))) { TINFL_CR_RETURN_FOREVER(39, TINFL_حالت_FAILED); }
      طالما ((counter) && (انگ_بٽ))
      {
        TINFL_GET_بٽ(51, dist, 8);
        طالما (p_ٻاهريون_buf_cur >= p_ٻاهريون_buf_پڇاڙي) { TINFL_CR_RETURN(52, TINFL_حالت_HAS_وڌيڪ_OUTPUT); }
        *p_ٻاهريون_buf_cur++ = (mz_uint8)dist;
        counter--;
      }
      طالما (counter)
      {
        size_t n; طالما (p_ٻاهريون_buf_cur >= p_ٻاهريون_buf_پڇاڙي) { TINFL_CR_RETURN(9, TINFL_حالت_HAS_وڌيڪ_OUTPUT); }
        طالما (p_اندريون_buf_cur >= p_اندريون_buf_پڇاڙي)
        {
          إذا (decomp_flags & TINFL_FLAG_HAS_وڌيڪ_داخلا)
          {
            TINFL_CR_RETURN(38, TINFL_حالت_NEEDS_وڌيڪ_داخلا);
          }
          وإلا
          {
            TINFL_CR_RETURN_FOREVER(40, TINFL_حالت_FAILED);
          }
        }
        n = MZ_MIN(MZ_MIN((size_t)(p_ٻاهريون_buf_پڇاڙي - p_ٻاهريون_buf_cur), (size_t)(p_اندريون_buf_پڇاڙي - p_اندريون_buf_cur)), counter);
        TINFL_MEMCPY(p_ٻاهريون_buf_cur, p_اندريون_buf_cur, n); p_اندريون_buf_cur += n; p_ٻاهريون_buf_cur += n; counter -= (mz_uint)n;
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
        mz_uint8 *p = r->m_tables[0].m_ڪوڊ_سائيز; mz_uint i;
        r->m_جدول_sizes[0] = 288; r->m_جدول_sizes[1] = 32; TINFL_MEMSET(r->m_tables[1].m_ڪوڊ_سائيز, 5, 32);
        لكل ( i = 0; i <= 143; ++i) *p++ = 8;
        لكل ( ; i <= 255; ++i) *p++ = 9;
        لكل ( ; i <= 279; ++i) *p++ = 7;
        لكل ( ; i <= 287; ++i) *p++ = 8;
      }
      وإلا
      {
        لكل (counter = 0; counter < 3; counter++) { TINFL_GET_بٽ(11, r->m_جدول_sizes[counter], "\05\05\04"[counter]); r->m_جدول_sizes[counter] += s_min_جدول_sizes[counter]; }
        MZ_CLEAR_ARR(r->m_tables[2].m_ڪوڊ_سائيز); لكل (counter = 0; counter < r->m_جدول_sizes[2]; counter++) { mz_uint s; TINFL_GET_بٽ(14, s, 3); r->m_tables[2].m_ڪوڊ_سائيز[s_ڊيگهائي_dezigzag[counter]] = (mz_uint8)s; }
        r->m_جدول_sizes[2] = 19;
      }
      لكل ( ; (صحيح)r->m_type >= 0; r->m_type--)
      {
        صحيح وڻ_ايندڙ, وڻ_cur; tinfl_huff_جدول *p_جدول;
        mz_uint i, j, استعمال_ٿيل_syms, ڪل, sym_اشاريو, ايندڙ_ڪوڊ[17], ڪل_syms[16]; p_جدول = &r->m_tables[r->m_type]; MZ_CLEAR_ARR(ڪل_syms); MZ_CLEAR_ARR(p_جدول->m_look_مٿي); MZ_CLEAR_ARR(p_جدول->m_وڻ);
        لكل (i = 0; i < r->m_جدول_sizes[r->m_type]; ++i) ڪل_syms[p_جدول->m_ڪوڊ_سائيز[i]]++;
        استعمال_ٿيل_syms = 0, ڪل = 0; ايندڙ_ڪوڊ[0] = ايندڙ_ڪوڊ[1] = 0;
        لكل (i = 1; i <= 15; ++i) { استعمال_ٿيل_syms += ڪل_syms[i]; ايندڙ_ڪوڊ[i + 1] = (ڪل = ((ڪل + ڪل_syms[i]) << 1)); }
        إذا ((65536 != ڪل) && (استعمال_ٿيل_syms > 1))
        {
          TINFL_CR_RETURN_FOREVER(35, TINFL_حالت_FAILED);
        }
        لكل (وڻ_ايندڙ = -1, sym_اشاريو = 0; sym_اشاريو < r->m_جدول_sizes[r->m_type]; ++sym_اشاريو)
        {
          mz_uint rev_ڪوڊ = 0, l, cur_ڪوڊ, ڪوڊ_سائيز_2 = p_جدول->m_ڪوڊ_سائيز[sym_اشاريو]; إذا (!ڪوڊ_سائيز_2) استمر;
          cur_ڪوڊ = ايندڙ_ڪوڊ[ڪوڊ_سائيز_2]++; لكل (l = ڪوڊ_سائيز_2; l > 0; l--, cur_ڪوڊ >>= 1) rev_ڪوڊ = (rev_ڪوڊ << 1) | (cur_ڪوڊ & 1);
          إذا (ڪوڊ_سائيز_2 <= TINFL_FAST_LOOKUP_بٽ) { mz_int16 k = (mz_int16)((ڪوڊ_سائيز_2 << 9) | sym_اشاريو); طالما (rev_ڪوڊ < TINFL_FAST_LOOKUP_سائيز) { p_جدول->m_look_مٿي[rev_ڪوڊ] = k; rev_ڪوڊ += (1 << ڪوڊ_سائيز_2); } استمر; }
          إذا (0 == (وڻ_cur = p_جدول->m_look_مٿي[rev_ڪوڊ & (TINFL_FAST_LOOKUP_سائيز - 1)])) { p_جدول->m_look_مٿي[rev_ڪوڊ & (TINFL_FAST_LOOKUP_سائيز - 1)] = (mz_int16)وڻ_ايندڙ; وڻ_cur = وڻ_ايندڙ; وڻ_ايندڙ -= 2; }
          rev_ڪوڊ >>= (TINFL_FAST_LOOKUP_بٽ - 1);
          لكل (j = ڪوڊ_سائيز_2; j > (TINFL_FAST_LOOKUP_بٽ + 1); j--)
          {
            وڻ_cur -= ((rev_ڪوڊ >>= 1) & 1);
            إذا (!p_جدول->m_وڻ[-وڻ_cur - 1]) { p_جدول->m_وڻ[-وڻ_cur - 1] = (mz_int16)وڻ_ايندڙ; وڻ_cur = وڻ_ايندڙ; وڻ_ايندڙ -= 2; } وإلا وڻ_cur = p_جدول->m_وڻ[-وڻ_cur - 1];
          }
          وڻ_cur -= ((rev_ڪوڊ >>= 1) & 1); p_جدول->m_وڻ[-وڻ_cur - 1] = (mz_int16)sym_اشاريو;
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
            انگ_extra = "\02\03\07"[dist - 16]; TINFL_GET_بٽ(18, s, انگ_extra); s += "\03\03\013"[dist - 16];
            TINFL_MEMSET(r->m_len_codes + counter, (dist == 16) ? r->m_len_codes[counter - 1] : 0, s); counter += s;
          }
          إذا ((r->m_جدول_sizes[0] + r->m_جدول_sizes[1]) != counter)
          {
            TINFL_CR_RETURN_FOREVER(21, TINFL_حالت_FAILED);
          }
          TINFL_MEMCPY(r->m_tables[0].m_ڪوڊ_سائيز, r->m_len_codes, r->m_جدول_sizes[0]); TINFL_MEMCPY(r->m_tables[1].m_ڪوڊ_سائيز, r->m_len_codes + r->m_جدول_sizes[0], r->m_جدول_sizes[1]);
        }
      }
      لكل ( ; ; )
      {
        mz_uint8 *pSrc;
        لكل ( ; ; )
        {
          إذا (((p_اندريون_buf_پڇاڙي - p_اندريون_buf_cur) < 4) || ((p_ٻاهريون_buf_پڇاڙي - p_ٻاهريون_buf_cur) < 2))
          {
            TINFL_HUFF_DECODE(23, counter, &r->m_tables[0]);
            إذا (counter >= 256)
              اكسر;
            طالما (p_ٻاهريون_buf_cur >= p_ٻاهريون_buf_پڇاڙي) { TINFL_CR_RETURN(24, TINFL_حالت_HAS_وڌيڪ_OUTPUT); }
            *p_ٻاهريون_buf_cur++ = (mz_uint8)counter;
          }
          وإلا
          {
            صحيح sym2; mz_uint ڪوڊ_len;
#إذا TINFL_USE_64_ٻٽو_انگ_BITBUF
            إذا (انگ_بٽ < 30) { ٻٽو_انگ_buf |= (((tinfl_ٻٽو_انگ_buf_t)MZ_READ_LE32(p_اندريون_buf_cur)) << انگ_بٽ); p_اندريون_buf_cur += 4; انگ_بٽ += 32; }
#وإلا
            إذا (انگ_بٽ < 15) { ٻٽو_انگ_buf |= (((tinfl_ٻٽو_انگ_buf_t)MZ_READ_LE16(p_اندريون_buf_cur)) << انگ_بٽ); p_اندريون_buf_cur += 2; انگ_بٽ += 16; }
#جيڪڏهن_پورو
            إذا ((sym2 = r->m_tables[0].m_look_مٿي[ٻٽو_انگ_buf & (TINFL_FAST_LOOKUP_سائيز - 1)]) >= 0)
              ڪوڊ_len = sym2 >> 9;
            وإلا
            {
              ڪوڊ_len = TINFL_FAST_LOOKUP_بٽ; افعل { sym2 = r->m_tables[0].m_وڻ[~sym2 + ((ٻٽو_انگ_buf >> ڪوڊ_len++) & 1)]; } طالما (sym2 < 0);
            }
            counter = sym2; ٻٽو_انگ_buf >>= ڪوڊ_len; انگ_بٽ -= ڪوڊ_len;
            إذا (counter & 256)
              اكسر;

#إذا !TINFL_USE_64_ٻٽو_انگ_BITBUF
            إذا (انگ_بٽ < 15) { ٻٽو_انگ_buf |= (((tinfl_ٻٽو_انگ_buf_t)MZ_READ_LE16(p_اندريون_buf_cur)) << انگ_بٽ); p_اندريون_buf_cur += 2; انگ_بٽ += 16; }
#جيڪڏهن_پورو
            إذا ((sym2 = r->m_tables[0].m_look_مٿي[ٻٽو_انگ_buf & (TINFL_FAST_LOOKUP_سائيز - 1)]) >= 0)
              ڪوڊ_len = sym2 >> 9;
            وإلا
            {
              ڪوڊ_len = TINFL_FAST_LOOKUP_بٽ; افعل { sym2 = r->m_tables[0].m_وڻ[~sym2 + ((ٻٽو_انگ_buf >> ڪوڊ_len++) & 1)]; } طالما (sym2 < 0);
            }
            ٻٽو_انگ_buf >>= ڪوڊ_len; انگ_بٽ -= ڪوڊ_len;

            p_ٻاهريون_buf_cur[0] = (mz_uint8)counter;
            إذا (sym2 & 256)
            {
              p_ٻاهريون_buf_cur++;
              counter = sym2;
              اكسر;
            }
            p_ٻاهريون_buf_cur[1] = (mz_uint8)sym2;
            p_ٻاهريون_buf_cur += 2;
          }
        }
        إذا ((counter &= 511) == 256) اكسر;

        انگ_extra = s_ڊيگهائي_extra[counter - 257]; counter = s_ڊيگهائي_بنياد[counter - 257];
        إذا (انگ_extra) { mz_uint extra_بٽ; TINFL_GET_بٽ(25, extra_بٽ, انگ_extra); counter += extra_بٽ; }

        TINFL_HUFF_DECODE(26, dist, &r->m_tables[1]);
        انگ_extra = s_dist_extra[dist]; dist = s_dist_بنياد[dist];
        إذا (انگ_extra) { mz_uint extra_بٽ; TINFL_GET_بٽ(27, extra_بٽ, انگ_extra); dist += extra_بٽ; }

        dist_from_ٻاهريون_buf_شروعات = p_ٻاهريون_buf_cur - p_ٻاهريون_buf_شروعات;
        إذا ((dist > dist_from_ٻاهريون_buf_شروعات) && (decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF))
        {
          TINFL_CR_RETURN_FOREVER(37, TINFL_حالت_FAILED);
        }

        pSrc = p_ٻاهريون_buf_شروعات + ((dist_from_ٻاهريون_buf_شروعات - dist) & ٻاهريون_buf_سائيز_نقاب);

        إذا ((MZ_MAX(p_ٻاهريون_buf_cur, pSrc) + counter) > p_ٻاهريون_buf_پڇاڙي)
        {
          طالما (counter--)
          {
            طالما (p_ٻاهريون_buf_cur >= p_ٻاهريون_buf_پڇاڙي) { TINFL_CR_RETURN(53, TINFL_حالت_HAS_وڌيڪ_OUTPUT); }
            *p_ٻاهريون_buf_cur++ = p_ٻاهريون_buf_شروعات[(dist_from_ٻاهريون_buf_شروعات++ - dist) & ٻاهريون_buf_سائيز_نقاب];
          }
          استمر;
        }
#إذا MINIZ_USE_UNALIGNED_LOADS_AND_STORES
        وإلا إذا ((counter >= 9) && (counter <= dist))
        {
          ثابت mz_uint8 *p_Src_پڇاڙي = pSrc + (counter & ~7);
          افعل
          {
            ((mz_uint32 *)p_ٻاهريون_buf_cur)[0] = ((ثابت mz_uint32 *)pSrc)[0];
            ((mz_uint32 *)p_ٻاهريون_buf_cur)[1] = ((ثابت mz_uint32 *)pSrc)[1];
            p_ٻاهريون_buf_cur += 8;
          } طالما ((pSrc += 8) < p_Src_پڇاڙي);
          إذا ((counter &= 7) < 3)
          {
            إذا (counter)
            {
              p_ٻاهريون_buf_cur[0] = pSrc[0];
              إذا (counter > 1)
                p_ٻاهريون_buf_cur[1] = pSrc[1];
              p_ٻاهريون_buf_cur += counter;
            }
            استمر;
          }
        }
#جيڪڏهن_پورو
        افعل
        {
          p_ٻاهريون_buf_cur[0] = pSrc[0];
          p_ٻاهريون_buf_cur[1] = pSrc[1];
          p_ٻاهريون_buf_cur[2] = pSrc[2];
          p_ٻاهريون_buf_cur += 3; pSrc += 3;
        } طالما ((صحيح)(counter -= 3) > 2);
        إذا ((صحيح)counter > 0)
        {
          p_ٻاهريون_buf_cur[0] = pSrc[0];
          إذا ((صحيح)counter > 1)
            p_ٻاهريون_buf_cur[1] = pSrc[1];
          p_ٻاهريون_buf_cur += counter;
        }
      }
    }
  } طالما (!(r->m_final & 1));
  إذا (decomp_flags & TINFL_FLAG_PARSE_ZLIB_سرو)
  {
    TINFL_SKIP_بٽ(32, انگ_بٽ & 7); لكل (counter = 0; counter < 4; ++counter) { mz_uint s; إذا (انگ_بٽ) TINFL_GET_بٽ(41, s, 8); وإلا TINFL_GET_BYTE(42, s); r->m_z_adler32 = (r->m_z_adler32 << 8) | s; }
  }
  TINFL_CR_RETURN_FOREVER(34, TINFL_حالت_پورو);
  TINFL_CR_پڄاڻي

common_exit:
  r->m_انگ_بٽ = انگ_بٽ; r->m_ٻٽو_انگ_buf = ٻٽو_انگ_buf; r->m_dist = dist; r->m_counter = counter; r->m_انگ_extra = انگ_extra; r->m_dist_from_ٻاهريون_buf_شروعات = dist_from_ٻاهريون_buf_شروعات;
  *p_اندريون_buf_سائيز = p_اندريون_buf_cur - p_اندريون_buf_ايندڙ; *p_ٻاهريون_buf_سائيز = p_ٻاهريون_buf_cur - p_ٻاهريون_buf_ايندڙ;
  إذا ((decomp_flags & (TINFL_FLAG_PARSE_ZLIB_سرو | TINFL_FLAG_COMPUTE_ADLER32)) && (حالت >= 0))
  {
    ثابت mz_uint8 *ptr = p_ٻاهريون_buf_ايندڙ; size_t buf_len = *p_ٻاهريون_buf_سائيز;
    mz_uint32 i, s1 = r->m_check_adler32 & 0xffff, s2 = r->m_check_adler32 >> 16; size_t بلاڪ_len = buf_len % 5552;
    طالما (buf_len)
    {
      لكل (i = 0; i + 7 < بلاڪ_len; i += 8, ptr += 8)
      {
        s1 += ptr[0], s2 += s1; s1 += ptr[1], s2 += s1; s1 += ptr[2], s2 += s1; s1 += ptr[3], s2 += s1;
        s1 += ptr[4], s2 += s1; s1 += ptr[5], s2 += s1; s1 += ptr[6], s2 += s1; s1 += ptr[7], s2 += s1;
      }
      لكل ( ; i < بلاڪ_len; ++i) s1 += *ptr++, s2 += s1;
      s1 %= 65521U, s2 %= 65521U; buf_len -= بلاڪ_len; بلاڪ_len = 5552;
    }
    r->m_check_adler32 = (s2 << 16) + s1; إذا ((حالت == TINFL_حالت_پورو) && (decomp_flags & TINFL_FLAG_PARSE_ZLIB_سرو) && (r->m_check_adler32 != r->m_z_adler32)) حالت = TINFL_حالت_ADLER32_MISMATCH;
  }
  أرجع حالت;
}

// Higher level helper functions.
فراغ *tinfl_decompress_mem_منزل_ڍير(ثابت فراغ *pSrc_buf, size_t src_buf_len, size_t *p_ٻاهريون_len, صحيح flags)
{
  tinfl_decompressor decomp; فراغ *pBuf = عدم, *pNew_buf; size_t src_buf_ofs = 0, ٻاهريون_buf_صلاحيت = 0;
  *p_ٻاهريون_len = 0;
  tinfl_init(&decomp);
  لكل ( ; ; )
  {
    size_t src_buf_سائيز = src_buf_len - src_buf_ofs, dst_buf_سائيز = ٻاهريون_buf_صلاحيت - *p_ٻاهريون_len, new_ٻاهريون_buf_صلاحيت;
    tinfl_حالت حالت = tinfl_decompress(&decomp, (ثابت mz_uint8*)pSrc_buf + src_buf_ofs, &src_buf_سائيز, (mz_uint8*)pBuf, pBuf ? (mz_uint8*)pBuf + *p_ٻاهريون_len : عدم, &dst_buf_سائيز,
      (flags & ~TINFL_FLAG_HAS_وڌيڪ_داخلا) | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF);
    إذا ((حالت < 0) || (حالت == TINFL_حالت_NEEDS_وڌيڪ_داخلا))
    {
      MZ_FREE(pBuf); *p_ٻاهريون_len = 0; أرجع عدم;
    }
    src_buf_ofs += src_buf_سائيز;
    *p_ٻاهريون_len += dst_buf_سائيز;
    إذا (حالت == TINFL_حالت_پورو) اكسر;
    new_ٻاهريون_buf_صلاحيت = ٻاهريون_buf_صلاحيت * 2; إذا (new_ٻاهريون_buf_صلاحيت < 128) new_ٻاهريون_buf_صلاحيت = 128;
    pNew_buf = MZ_REALLOC(pBuf, new_ٻاهريون_buf_صلاحيت);
    إذا (!pNew_buf)
    {
      MZ_FREE(pBuf); *p_ٻاهريون_len = 0; أرجع عدم;
    }
    pBuf = pNew_buf; ٻاهريون_buf_صلاحيت = new_ٻاهريون_buf_صلاحيت;
  }
  أرجع pBuf;
}

size_t tinfl_decompress_mem_منزل_mem(فراغ *p_ٻاهريون_buf, size_t ٻاهريون_buf_len, ثابت فراغ *pSrc_buf, size_t src_buf_len, صحيح flags)
{
  tinfl_decompressor decomp; tinfl_حالت حالت; tinfl_init(&decomp);
  حالت = tinfl_decompress(&decomp, (ثابت mz_uint8*)pSrc_buf, &src_buf_len, (mz_uint8*)p_ٻاهريون_buf, (mz_uint8*)p_ٻاهريون_buf, &ٻاهريون_buf_len, (flags & ~TINFL_FLAG_HAS_وڌيڪ_داخلا) | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF);
  أرجع (حالت != TINFL_حالت_پورو) ? TINFL_DECOMPRESS_MEM_منزل_MEM_FAILED : ٻاهريون_buf_len;
}

صحيح tinfl_decompress_mem_منزل_callback(ثابت فراغ *p_اندريون_buf, size_t *p_اندريون_buf_سائيز, tinfl_put_buf_func_ptr pPut_buf_func, فراغ *pPut_buf_user, صحيح flags)
{
  صحيح نتيجو = 0;
  tinfl_decompressor decomp;
  mz_uint8 *pDict = (mz_uint8*)MZ_MALLOC(TINFL_LZ_DICT_سائيز); size_t اندريون_buf_ofs = 0, dict_ofs = 0;
  إذا (!pDict)
    أرجع TINFL_حالت_FAILED;
  memset(pDict,0,TINFL_LZ_DICT_سائيز);
  tinfl_init(&decomp);
  لكل ( ; ; )
  {
    size_t اندريون_buf_سائيز = *p_اندريون_buf_سائيز - اندريون_buf_ofs, dst_buf_سائيز = TINFL_LZ_DICT_سائيز - dict_ofs;
    tinfl_حالت حالت = tinfl_decompress(&decomp, (ثابت mz_uint8*)p_اندريون_buf + اندريون_buf_ofs, &اندريون_buf_سائيز, pDict, pDict + dict_ofs, &dst_buf_سائيز,
      (flags & ~(TINFL_FLAG_HAS_وڌيڪ_داخلا | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF)));
    اندريون_buf_ofs += اندريون_buf_سائيز;
    إذا ((dst_buf_سائيز) && (!(*pPut_buf_func)(pDict + dict_ofs, (صحيح)dst_buf_سائيز, pPut_buf_user)))
      اكسر;
    إذا (حالت != TINFL_حالت_HAS_وڌيڪ_OUTPUT)
    {
      نتيجو = (حالت == TINFL_حالت_پورو);
      اكسر;
    }
    dict_ofs = (dict_ofs + dst_buf_سائيز) & (TINFL_LZ_DICT_سائيز - 1);
  }
  MZ_FREE(pDict);
  *p_اندريون_buf_سائيز = اندريون_buf_ofs;
  أرجع نتيجو;
}
#جيڪڏهن_پورو /*#ifndef MINIZ_NO_INFLATE_APIS*/

// ------------------- Low-level Compression (independent from all decompression API's)
#جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_DEFLATE_APIS

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
تعريفنوع بنية { mz_uint16 m_ڪنجي, m_sym_اشاريو; } tdefl_sym_freq;
ساكن tdefl_sym_freq* tdefl_radix_ترتيب_ڏيو_syms(mz_uint انگ_syms, tdefl_sym_freq* pSyms0, tdefl_sym_freq* pSyms1)
{
  mz_uint32 ڪل_passes = 2, pass_سرڪايو, pass, i, hist[256 * 2]; tdefl_sym_freq* pCur_syms = pSyms0, *pNew_syms = pSyms1; MZ_CLEAR_ARR(hist);
  لكل (i = 0; i < انگ_syms; i++) { mz_uint freq = pSyms0[i].m_ڪنجي; hist[freq & 0xFF]++; hist[256 + ((freq >> 8) & 0xFF)]++; }
  طالما ((ڪل_passes > 1) && (انگ_syms == hist[(ڪل_passes - 1) * 256])) ڪل_passes--;
  لكل (pass_سرڪايو = 0, pass = 0; pass < ڪل_passes; pass++, pass_سرڪايو += 8)
  {
    ثابت mz_uint32* pHist = &hist[pass << 8];
    mz_uint offsets[256], cur_ofs = 0;
    لكل (i = 0; i < 256; i++) { offsets[i] = cur_ofs; cur_ofs += pHist[i]; }
    لكل (i = 0; i < انگ_syms; i++) pNew_syms[offsets[(pCur_syms[i].m_ڪنجي >> pass_سرڪايو) & 0xFF]++] = pCur_syms[i];
    { tdefl_sym_freq* t = pCur_syms; pCur_syms = pNew_syms; pNew_syms = t; }
  }
  أرجع pCur_syms;
}

// tdefl_calculate_minimum_redundancy() originally written by: Alistair Moffat, alistair@cs.mu.oz.au, Jyrki Katajainen, jyrki@diku.dk, November 1996.
ساكن فراغ tdefl_calculate_minimum_redundancy(tdefl_sym_freq *A, صحيح n)
{
  صحيح پاڙ, پن, ايندڙ, avbl, استعمال_ٿيل, dpth;
  إذا (n==0) أرجع; وإلا إذا (n==1) { A[0].m_ڪنجي = 1; أرجع; }
  A[0].m_ڪنجي += A[1].m_ڪنجي; پاڙ = 0; پن = 2;
  لكل (ايندڙ=1; ايندڙ < n-1; ايندڙ++)
  {
    إذا (پن>=n || A[پاڙ].m_ڪنجي<A[پن].m_ڪنجي) { A[ايندڙ].m_ڪنجي = A[پاڙ].m_ڪنجي; A[پاڙ++].m_ڪنجي = (mz_uint16)ايندڙ; } وإلا A[ايندڙ].m_ڪنجي = A[پن++].m_ڪنجي;
    إذا (پن>=n || (پاڙ<ايندڙ && A[پاڙ].m_ڪنجي<A[پن].m_ڪنجي)) { A[ايندڙ].m_ڪنجي = (mz_uint16)(A[ايندڙ].m_ڪنجي + A[پاڙ].m_ڪنجي); A[پاڙ++].m_ڪنجي = (mz_uint16)ايندڙ; } وإلا A[ايندڙ].m_ڪنجي = (mz_uint16)(A[ايندڙ].m_ڪنجي + A[پن++].m_ڪنجي);
  }
  A[n-2].m_ڪنجي = 0; لكل (ايندڙ=n-3; ايندڙ>=0; ايندڙ--) A[ايندڙ].m_ڪنجي = A[A[ايندڙ].m_ڪنجي].m_ڪنجي+1;
  avbl = 1; استعمال_ٿيل = dpth = 0; پاڙ = n-2; ايندڙ = n-1;
  طالما (avbl>0)
  {
    طالما (پاڙ>=0 && (صحيح)A[پاڙ].m_ڪنجي==dpth) { استعمال_ٿيل++; پاڙ--; }
    طالما (avbl>استعمال_ٿيل) { A[ايندڙ--].m_ڪنجي = (mz_uint16)(dpth); avbl--; }
    avbl = 2*استعمال_ٿيل; dpth++; استعمال_ٿيل = 0;
  }
}

// Limits canonical Huffman code table's max code size.
تعداد { TDEFL_MAX_SUPPORTED_HUFF_CODESIZE = 32 };
ساكن فراغ tdefl_huffman_enforce_max_ڪوڊ_سائيز(صحيح *p_انگ_codes, صحيح ڪوڊ_list_len, صحيح max_ڪوڊ_سائيز)
{
  صحيح i; mz_uint32 ڪل = 0; إذا (ڪوڊ_list_len <= 1) أرجع;
  لكل (i = max_ڪوڊ_سائيز + 1; i <= TDEFL_MAX_SUPPORTED_HUFF_CODESIZE; i++) p_انگ_codes[max_ڪوڊ_سائيز] += p_انگ_codes[i];
  لكل (i = max_ڪوڊ_سائيز; i > 0; i--) ڪل += (((mz_uint32)p_انگ_codes[i]) << (max_ڪوڊ_سائيز - i));
  طالما (ڪل != (1UL << max_ڪوڊ_سائيز))
  {
    p_انگ_codes[max_ڪوڊ_سائيز]--;
    لكل (i = max_ڪوڊ_سائيز - 1; i > 0; i--) إذا (p_انگ_codes[i]) { p_انگ_codes[i]--; p_انگ_codes[i + 1] += 2; اكسر; }
    ڪل--;
  }
}

ساكن فراغ tdefl_optimize_huffman_جدول(tdefl_compressor *d, صحيح جدول_انگ, صحيح جدول_len, صحيح ڪوڊ_سائيز_حد_بندي, صحيح static_جدول)
{
  صحيح i, j, l, انگ_codes[1 + TDEFL_MAX_SUPPORTED_HUFF_CODESIZE]; mz_uint ايندڙ_ڪوڊ[TDEFL_MAX_SUPPORTED_HUFF_CODESIZE + 1]; MZ_CLEAR_ARR(انگ_codes);
  إذا (static_جدول)
  {
    لكل (i = 0; i < جدول_len; i++) انگ_codes[d->m_huff_ڪوڊ_sizes[جدول_انگ][i]]++;
  }
  وإلا
  {
    tdefl_sym_freq syms0[TDEFL_MAX_HUFF_SYMBOLS], syms1[TDEFL_MAX_HUFF_SYMBOLS], *pSyms;
    صحيح انگ_استعمال_ٿيل_syms = 0;
    ثابت mz_uint16 *p_Sym_ڳڻپ = &d->m_huff_ڳڻپ[جدول_انگ][0];
    لكل (i = 0; i < جدول_len; i++) إذا (p_Sym_ڳڻپ[i]) { syms0[انگ_استعمال_ٿيل_syms].m_ڪنجي = (mz_uint16)p_Sym_ڳڻپ[i]; syms0[انگ_استعمال_ٿيل_syms++].m_sym_اشاريو = (mz_uint16)i; }

    pSyms = tdefl_radix_ترتيب_ڏيو_syms(انگ_استعمال_ٿيل_syms, syms0, syms1); tdefl_calculate_minimum_redundancy(pSyms, انگ_استعمال_ٿيل_syms);

    لكل (i = 0; i < انگ_استعمال_ٿيل_syms; i++) انگ_codes[pSyms[i].m_ڪنجي]++;

    tdefl_huffman_enforce_max_ڪوڊ_سائيز(انگ_codes, انگ_استعمال_ٿيل_syms, ڪوڊ_سائيز_حد_بندي);

    MZ_CLEAR_ARR(d->m_huff_ڪوڊ_sizes[جدول_انگ]); MZ_CLEAR_ARR(d->m_huff_codes[جدول_انگ]);
    لكل (i = 1, j = انگ_استعمال_ٿيل_syms; i <= ڪوڊ_سائيز_حد_بندي; i++)
      لكل (l = انگ_codes[i]; l > 0; l--) d->m_huff_ڪوڊ_sizes[جدول_انگ][pSyms[--j].m_sym_اشاريو] = (mz_uint8)(i);
  }

  ايندڙ_ڪوڊ[1] = 0; لكل (j = 0, i = 2; i <= ڪوڊ_سائيز_حد_بندي; i++) ايندڙ_ڪوڊ[i] = j = ((j + انگ_codes[i - 1]) << 1);

  لكل (i = 0; i < جدول_len; i++)
  {
    mz_uint rev_ڪوڊ = 0, ڪوڊ, ڪوڊ_سائيز_2; إذا ((ڪوڊ_سائيز_2 = d->m_huff_ڪوڊ_sizes[جدول_انگ][i]) == 0) استمر;
    ڪوڊ = ايندڙ_ڪوڊ[ڪوڊ_سائيز_2]++; لكل (l = ڪوڊ_سائيز_2; l > 0; l--, ڪوڊ >>= 1) rev_ڪوڊ = (rev_ڪوڊ << 1) | (ڪوڊ & 1);
    d->m_huff_codes[جدول_انگ][i] = (mz_uint16)rev_ڪوڊ;
  }
}

#وصف_ڪريو TDEFL_PUT_بٽ(b, l) افعل { \
  mz_uint بٽ = b; mz_uint len = l; MZ_ASSERT(بٽ <= ((1U << len) - 1U)); \
  d->m_ٻٽو_انگ_بفر |= (بٽ << d->m_بٽ_اندريون); d->m_بٽ_اندريون += len; \
  طالما (d->m_بٽ_اندريون >= 8) { \
    إذا (d->m_pOutput_buf < d->m_p_Output_buf_پڇاڙي) \
      *d->m_pOutput_buf++ = (mz_uint8)(d->m_ٻٽو_انگ_بفر); \
    d->m_ٻٽو_انگ_بفر >>= 8; \
    d->m_بٽ_اندريون -= 8; \
  } \
} MZ_MACRO_پڇاڙي

#وصف_ڪريو TDEFL_RLE_PREV_ڪوڊ_سائيز() افعل { \
  إذا (rle_repeat_ڳڻپ) { \
    إذا (rle_repeat_ڳڻپ < 3) { \
      d->m_huff_ڳڻپ[2][prev_ڪوڊ_سائيز] = (mz_uint16)(d->m_huff_ڳڻپ[2][prev_ڪوڊ_سائيز] + rle_repeat_ڳڻپ); \
      طالما (rle_repeat_ڳڻپ--) packed_ڪوڊ_sizes[انگ_packed_ڪوڊ_sizes++] = prev_ڪوڊ_سائيز; \
    } وإلا { \
      d->m_huff_ڳڻپ[2][16] = (mz_uint16)(d->m_huff_ڳڻپ[2][16] + 1); packed_ڪوڊ_sizes[انگ_packed_ڪوڊ_sizes++] = 16; packed_ڪوڊ_sizes[انگ_packed_ڪوڊ_sizes++] = (mz_uint8)(rle_repeat_ڳڻپ - 3); \
  } rle_repeat_ڳڻپ = 0; } \
} MZ_MACRO_پڇاڙي

#وصف_ڪريو TDEFL_RLE_ZERO_ڪوڊ_سائيز() افعل { \
  إذا (rle_z_ڳڻپ) { \
    إذا (rle_z_ڳڻپ < 3) { \
      d->m_huff_ڳڻپ[2][0] = (mz_uint16)(d->m_huff_ڳڻپ[2][0] + rle_z_ڳڻپ); طالما (rle_z_ڳڻپ--) packed_ڪوڊ_sizes[انگ_packed_ڪوڊ_sizes++] = 0; \
    } وإلا إذا (rle_z_ڳڻپ <= 10) { \
      d->m_huff_ڳڻپ[2][17] = (mz_uint16)(d->m_huff_ڳڻپ[2][17] + 1); packed_ڪوڊ_sizes[انگ_packed_ڪوڊ_sizes++] = 17; packed_ڪوڊ_sizes[انگ_packed_ڪوڊ_sizes++] = (mz_uint8)(rle_z_ڳڻپ - 3); \
    } وإلا { \
      d->m_huff_ڳڻپ[2][18] = (mz_uint16)(d->m_huff_ڳڻپ[2][18] + 1); packed_ڪوڊ_sizes[انگ_packed_ڪوڊ_sizes++] = 18; packed_ڪوڊ_sizes[انگ_packed_ڪوڊ_sizes++] = (mz_uint8)(rle_z_ڳڻپ - 11); \
  } rle_z_ڳڻپ = 0; } \
} MZ_MACRO_پڇاڙي

ساكن mz_uint8 s_tdefl_packed_ڪوڊ_سائيز_syms_swizzle[] = { 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 };

ساكن فراغ tdefl_شروعات_dynamic_بلاڪ(tdefl_compressor *d)
{
  صحيح انگ_lit_codes, انگ_dist_codes, انگ_ٻٽو_انگ_lengths; mz_uint i, ڪل_ڪوڊ_sizes_منزل_pack, انگ_packed_ڪوڊ_sizes, rle_z_ڳڻپ, rle_repeat_ڳڻپ, packed_ڪوڊ_sizes_اشاريو;
  mz_uint8 ڪوڊ_sizes_منزل_pack[TDEFL_MAX_HUFF_SYMBOLS_0 + TDEFL_MAX_HUFF_SYMBOLS_1], packed_ڪوڊ_sizes[TDEFL_MAX_HUFF_SYMBOLS_0 + TDEFL_MAX_HUFF_SYMBOLS_1], prev_ڪوڊ_سائيز = 0xFF;

  d->m_huff_ڳڻپ[0][256] = 1;

  tdefl_optimize_huffman_جدول(d, 0, TDEFL_MAX_HUFF_SYMBOLS_0, 15, MZ_FALSE);
  tdefl_optimize_huffman_جدول(d, 1, TDEFL_MAX_HUFF_SYMBOLS_1, 15, MZ_FALSE);

  لكل (انگ_lit_codes = 286; انگ_lit_codes > 257; انگ_lit_codes--) إذا (d->m_huff_ڪوڊ_sizes[0][انگ_lit_codes - 1]) اكسر;
  لكل (انگ_dist_codes = 30; انگ_dist_codes > 1; انگ_dist_codes--) إذا (d->m_huff_ڪوڊ_sizes[1][انگ_dist_codes - 1]) اكسر;

  يادگيري_نقل(ڪوڊ_sizes_منزل_pack, &d->m_huff_ڪوڊ_sizes[0][0], انگ_lit_codes);
  يادگيري_نقل(ڪوڊ_sizes_منزل_pack + انگ_lit_codes, &d->m_huff_ڪوڊ_sizes[1][0], انگ_dist_codes);
  ڪل_ڪوڊ_sizes_منزل_pack = انگ_lit_codes + انگ_dist_codes; انگ_packed_ڪوڊ_sizes = 0; rle_z_ڳڻپ = 0; rle_repeat_ڳڻپ = 0;

  memset(&d->m_huff_ڳڻپ[2][0], 0, حجم(d->m_huff_ڳڻپ[2][0]) * TDEFL_MAX_HUFF_SYMBOLS_2);
  لكل (i = 0; i < ڪل_ڪوڊ_sizes_منزل_pack; i++)
  {
    mz_uint8 ڪوڊ_سائيز_2 = ڪوڊ_sizes_منزل_pack[i];
    إذا (!ڪوڊ_سائيز_2)
    {
      TDEFL_RLE_PREV_ڪوڊ_سائيز();
      إذا (++rle_z_ڳڻپ == 138) { TDEFL_RLE_ZERO_ڪوڊ_سائيز(); }
    }
    وإلا
    {
      TDEFL_RLE_ZERO_ڪوڊ_سائيز();
      إذا (ڪوڊ_سائيز_2 != prev_ڪوڊ_سائيز)
      {
        TDEFL_RLE_PREV_ڪوڊ_سائيز();
        d->m_huff_ڳڻپ[2][ڪوڊ_سائيز_2] = (mz_uint16)(d->m_huff_ڳڻپ[2][ڪوڊ_سائيز_2] + 1); packed_ڪوڊ_sizes[انگ_packed_ڪوڊ_sizes++] = ڪوڊ_سائيز_2;
      }
      وإلا إذا (++rle_repeat_ڳڻپ == 6)
      {
        TDEFL_RLE_PREV_ڪوڊ_سائيز();
      }
    }
    prev_ڪوڊ_سائيز = ڪوڊ_سائيز_2;
  }
  إذا (rle_repeat_ڳڻپ) { TDEFL_RLE_PREV_ڪوڊ_سائيز(); } وإلا { TDEFL_RLE_ZERO_ڪوڊ_سائيز(); }

  tdefl_optimize_huffman_جدول(d, 2, TDEFL_MAX_HUFF_SYMBOLS_2, 7, MZ_FALSE);

  TDEFL_PUT_بٽ(2, 2);

  TDEFL_PUT_بٽ(انگ_lit_codes - 257, 5);
  TDEFL_PUT_بٽ(انگ_dist_codes - 1, 5);

  لكل (انگ_ٻٽو_انگ_lengths = 18; انگ_ٻٽو_انگ_lengths >= 0; انگ_ٻٽو_انگ_lengths--) إذا (d->m_huff_ڪوڊ_sizes[2][s_tdefl_packed_ڪوڊ_سائيز_syms_swizzle[انگ_ٻٽو_انگ_lengths]]) اكسر;
  انگ_ٻٽو_انگ_lengths = MZ_MAX(4, (انگ_ٻٽو_انگ_lengths + 1)); TDEFL_PUT_بٽ(انگ_ٻٽو_انگ_lengths - 4, 4);
  لكل (i = 0; (صحيح)i < انگ_ٻٽو_انگ_lengths; i++) TDEFL_PUT_بٽ(d->m_huff_ڪوڊ_sizes[2][s_tdefl_packed_ڪوڊ_سائيز_syms_swizzle[i]], 3);

  لكل (packed_ڪوڊ_sizes_اشاريو = 0; packed_ڪوڊ_sizes_اشاريو < انگ_packed_ڪوڊ_sizes; )
  {
    mz_uint ڪوڊ = packed_ڪوڊ_sizes[packed_ڪوڊ_sizes_اشاريو++]; MZ_ASSERT(ڪوڊ < TDEFL_MAX_HUFF_SYMBOLS_2);
    TDEFL_PUT_بٽ(d->m_huff_codes[2][ڪوڊ], d->m_huff_ڪوڊ_sizes[2][ڪوڊ]);
    إذا (ڪوڊ >= 16) TDEFL_PUT_بٽ(packed_ڪوڊ_sizes[packed_ڪوڊ_sizes_اشاريو++], "\02\03\07"[ڪوڊ - 16]);
  }
}

ساكن فراغ tdefl_شروعات_static_بلاڪ(tdefl_compressor *d)
{
  mz_uint i;
  mz_uint8 *p = &d->m_huff_ڪوڊ_sizes[0][0];

  لكل (i = 0; i <= 143; ++i) *p++ = 8;
  لكل ( ; i <= 255; ++i) *p++ = 9;
  لكل ( ; i <= 279; ++i) *p++ = 7;
  لكل ( ; i <= 287; ++i) *p++ = 8;

  memset(d->m_huff_ڪوڊ_sizes[1], 5, 32);

  tdefl_optimize_huffman_جدول(d, 0, 288, 15, MZ_TRUE);
  tdefl_optimize_huffman_جدول(d, 1, 32, 15, MZ_TRUE);

  TDEFL_PUT_بٽ(1, 2);
}

ساكن ثابت mz_uint mz_bitmasks[17] = { 0x0000, 0x0001, 0x0003, 0x0007, 0x000F, 0x001F, 0x003F, 0x007F, 0x00FF, 0x01FF, 0x03FF, 0x07FF, 0x0FFF, 0x1FFF, 0x3FFF, 0x7FFF, 0xFFFF };

#إذا MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN && MINIZ_HAS_64_ٻٽو_انگ_REGISTERS
ساكن mz_bool tdefl_compress_lz_codes(tdefl_compressor *d)
{
  mz_uint flags;
  mz_uint8 *pLZ_codes;
  mz_uint8 *pOutput_buf = d->m_pOutput_buf;
  mz_uint8 *p_LZ_ڪوڊ_buf_پڇاڙي = d->m_p_LZ_ڪوڊ_buf;
  mz_uint64 ٻٽو_انگ_بفر = d->m_ٻٽو_انگ_بفر;
  mz_uint بٽ_اندريون = d->m_بٽ_اندريون;

#وصف_ڪريو TDEFL_PUT_بٽ_FAST(b, l) { ٻٽو_انگ_بفر |= (((mz_uint64)(b)) << بٽ_اندريون); بٽ_اندريون += (l); }

  flags = 1;
  لكل (pLZ_codes = d->m_lz_ڪوڊ_buf; pLZ_codes < p_LZ_ڪوڊ_buf_پڇاڙي; flags >>= 1)
  {
    إذا (flags == 1)
      flags = *pLZ_codes++ | 0x100;

    إذا (flags & 1)
    {
      mz_uint s0, s1, n0, n1, sym, انگ_extra_بٽ;
      mz_uint ميلاپ_len = pLZ_codes[0], ميلاپ_dist = *(ثابت mz_uint16 *)(pLZ_codes + 1); pLZ_codes += 3;

      MZ_ASSERT(d->m_huff_ڪوڊ_sizes[0][s_tdefl_len_sym[ميلاپ_len]]);
      TDEFL_PUT_بٽ_FAST(d->m_huff_codes[0][s_tdefl_len_sym[ميلاپ_len]], d->m_huff_ڪوڊ_sizes[0][s_tdefl_len_sym[ميلاپ_len]]);
      TDEFL_PUT_بٽ_FAST(ميلاپ_len & mz_bitmasks[s_tdefl_len_extra[ميلاپ_len]], s_tdefl_len_extra[ميلاپ_len]);

      // This sequence coaxes MSVC into using cmov's vs. jmp's.
      s0 = s_tdefl_small_dist_sym[ميلاپ_dist & 511];
      n0 = s_tdefl_small_dist_extra[ميلاپ_dist & 511];
      s1 = s_tdefl_large_dist_sym[ميلاپ_dist >> 8];
      n1 = s_tdefl_large_dist_extra[ميلاپ_dist >> 8];
      sym = (ميلاپ_dist < 512) ? s0 : s1;
      انگ_extra_بٽ = (ميلاپ_dist < 512) ? n0 : n1;

      MZ_ASSERT(d->m_huff_ڪوڊ_sizes[1][sym]);
      TDEFL_PUT_بٽ_FAST(d->m_huff_codes[1][sym], d->m_huff_ڪوڊ_sizes[1][sym]);
      TDEFL_PUT_بٽ_FAST(ميلاپ_dist & mz_bitmasks[انگ_extra_بٽ], انگ_extra_بٽ);
    }
    وإلا
    {
      mz_uint lit = *pLZ_codes++;
      MZ_ASSERT(d->m_huff_ڪوڊ_sizes[0][lit]);
      TDEFL_PUT_بٽ_FAST(d->m_huff_codes[0][lit], d->m_huff_ڪوڊ_sizes[0][lit]);

      إذا (((flags & 2) == 0) && (pLZ_codes < p_LZ_ڪوڊ_buf_پڇاڙي))
      {
        flags >>= 1;
        lit = *pLZ_codes++;
        MZ_ASSERT(d->m_huff_ڪوڊ_sizes[0][lit]);
        TDEFL_PUT_بٽ_FAST(d->m_huff_codes[0][lit], d->m_huff_ڪوڊ_sizes[0][lit]);

        إذا (((flags & 2) == 0) && (pLZ_codes < p_LZ_ڪوڊ_buf_پڇاڙي))
        {
          flags >>= 1;
          lit = *pLZ_codes++;
          MZ_ASSERT(d->m_huff_ڪوڊ_sizes[0][lit]);
          TDEFL_PUT_بٽ_FAST(d->m_huff_codes[0][lit], d->m_huff_ڪوڊ_sizes[0][lit]);
        }
      }
    }

    إذا (pOutput_buf >= d->m_p_Output_buf_پڇاڙي)
      أرجع MZ_FALSE;

    *(mz_uint64*)pOutput_buf = ٻٽو_انگ_بفر;
    pOutput_buf += (بٽ_اندريون >> 3);
    ٻٽو_انگ_بفر >>= (بٽ_اندريون & ~7);
    بٽ_اندريون &= 7;
  }

#وصف_رد TDEFL_PUT_بٽ_FAST

  d->m_pOutput_buf = pOutput_buf;
  d->m_بٽ_اندريون = 0;
  d->m_ٻٽو_انگ_بفر = 0;

  طالما (بٽ_اندريون)
  {
    mz_uint32 n = MZ_MIN(بٽ_اندريون, 16);
    TDEFL_PUT_بٽ((mz_uint)ٻٽو_انگ_بفر & mz_bitmasks[n], n);
    ٻٽو_انگ_بفر >>= n;
    بٽ_اندريون -= n;
  }

  TDEFL_PUT_بٽ(d->m_huff_codes[0][256], d->m_huff_ڪوڊ_sizes[0][256]);

  أرجع (d->m_pOutput_buf < d->m_p_Output_buf_پڇاڙي);
}
#وإلا
ساكن mz_bool tdefl_compress_lz_codes(tdefl_compressor *d)
{
  mz_uint flags;
  mz_uint8 *pLZ_codes;

  flags = 1;
  لكل (pLZ_codes = d->m_lz_ڪوڊ_buf; pLZ_codes < d->m_p_LZ_ڪوڊ_buf; flags >>= 1)
  {
    إذا (flags == 1)
      flags = *pLZ_codes++ | 0x100;
    إذا (flags & 1)
    {
      mz_uint sym, انگ_extra_بٽ;
      mz_uint ميلاپ_len = pLZ_codes[0], ميلاپ_dist = (pLZ_codes[1] | (pLZ_codes[2] << 8)); pLZ_codes += 3;

      MZ_ASSERT(d->m_huff_ڪوڊ_sizes[0][s_tdefl_len_sym[ميلاپ_len]]);
      TDEFL_PUT_بٽ(d->m_huff_codes[0][s_tdefl_len_sym[ميلاپ_len]], d->m_huff_ڪوڊ_sizes[0][s_tdefl_len_sym[ميلاپ_len]]);
      TDEFL_PUT_بٽ(ميلاپ_len & mz_bitmasks[s_tdefl_len_extra[ميلاپ_len]], s_tdefl_len_extra[ميلاپ_len]);

      إذا (ميلاپ_dist < 512)
      {
        sym = s_tdefl_small_dist_sym[ميلاپ_dist]; انگ_extra_بٽ = s_tdefl_small_dist_extra[ميلاپ_dist];
      }
      وإلا
      {
        sym = s_tdefl_large_dist_sym[ميلاپ_dist >> 8]; انگ_extra_بٽ = s_tdefl_large_dist_extra[ميلاپ_dist >> 8];
      }
      MZ_ASSERT(d->m_huff_ڪوڊ_sizes[1][sym]);
      TDEFL_PUT_بٽ(d->m_huff_codes[1][sym], d->m_huff_ڪوڊ_sizes[1][sym]);
      TDEFL_PUT_بٽ(ميلاپ_dist & mz_bitmasks[انگ_extra_بٽ], انگ_extra_بٽ);
    }
    وإلا
    {
      mz_uint lit = *pLZ_codes++;
      MZ_ASSERT(d->m_huff_ڪوڊ_sizes[0][lit]);
      TDEFL_PUT_بٽ(d->m_huff_codes[0][lit], d->m_huff_ڪوڊ_sizes[0][lit]);
    }
  }

  TDEFL_PUT_بٽ(d->m_huff_codes[0][256], d->m_huff_ڪوڊ_sizes[0][256]);

  أرجع (d->m_pOutput_buf < d->m_p_Output_buf_پڇاڙي);
}
#جيڪڏهن_پورو // MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN && MINIZ_HAS_64BIT_REGISTERS

ساكن mz_bool tdefl_compress_بلاڪ(tdefl_compressor *d, mz_bool static_بلاڪ)
{
  إذا (static_بلاڪ)
    tdefl_شروعات_static_بلاڪ(d);
  وإلا
    tdefl_شروعات_dynamic_بلاڪ(d);
  أرجع tdefl_compress_lz_codes(d);
}

ساكن صحيح tdefl_flush_بلاڪ(tdefl_compressor *d, صحيح flush)
{
  mz_uint saved_ٻٽو_انگ_buf, saved_بٽ_اندريون;
  mz_uint8 *pSaved_output_buf;
  mz_bool comp_بلاڪ_succeeded = MZ_FALSE;
  صحيح n, use_raw_بلاڪ = ((d->m_flags & TDEFL_FORCE_ALL_RAW_بلاڪون) != 0) && (d->m_lookahead_pos - d->m_lz_ڪوڊ_buf_dict_pos) <= d->m_dict_سائيز;
  mz_uint8 *p_Output_buf_شروعات = ((d->m_pPut_buf_func == عدم) && ((*d->m_p_ٻاهريون_buf_سائيز - d->m_ٻاهريون_buf_ofs) >= TDEFL_ٻاهريون_BUF_سائيز)) ? ((mz_uint8 *)d->m_p_ٻاهريون_buf + d->m_ٻاهريون_buf_ofs) : d->m_output_buf;

  d->m_pOutput_buf = p_Output_buf_شروعات;
  d->m_p_Output_buf_پڇاڙي = d->m_pOutput_buf + TDEFL_ٻاهريون_BUF_سائيز - 16;

  MZ_ASSERT(!d->m_output_flush_بچيل);
  d->m_output_flush_ofs = 0;
  d->m_output_flush_بچيل = 0;

  *d->m_pLZ_flags = (mz_uint8)(*d->m_pLZ_flags >> d->m_انگ_flags_کاٻو);
  d->m_p_LZ_ڪوڊ_buf -= (d->m_انگ_flags_کاٻو == 8);

  إذا ((d->m_flags & TDEFL_WRITE_ZLIB_سرو) && (!d->m_بلاڪ_اشاريو))
  {
    TDEFL_PUT_بٽ(0x78, 8); TDEFL_PUT_بٽ(0x01, 8);
  }

  TDEFL_PUT_بٽ(flush == TDEFL_پڄاڻي, 1);

  pSaved_output_buf = d->m_pOutput_buf; saved_ٻٽو_انگ_buf = d->m_ٻٽو_انگ_بفر; saved_بٽ_اندريون = d->m_بٽ_اندريون;

  إذا (!use_raw_بلاڪ)
    comp_بلاڪ_succeeded = tdefl_compress_بلاڪ(d, (d->m_flags & TDEFL_FORCE_ALL_STATIC_بلاڪون) || (d->m_ڪل_lz_بائيٽون < 48));

  // If the block gets expanded, forget the current contents of the output buffer and send a raw block instead.
  إذا ( ((use_raw_بلاڪ) || ((d->m_ڪل_lz_بائيٽون) && ((d->m_pOutput_buf - pSaved_output_buf + 1U) >= d->m_ڪل_lz_بائيٽون))) &&
       ((d->m_lookahead_pos - d->m_lz_ڪوڊ_buf_dict_pos) <= d->m_dict_سائيز) )
  {
    mz_uint i; d->m_pOutput_buf = pSaved_output_buf; d->m_ٻٽو_انگ_بفر = saved_ٻٽو_انگ_buf; d->m_بٽ_اندريون = saved_بٽ_اندريون;
    TDEFL_PUT_بٽ(0, 2);
    إذا (d->m_بٽ_اندريون) { TDEFL_PUT_بٽ(0, 8 - d->m_بٽ_اندريون); }
    لكل (i = 2; i; --i, d->m_ڪل_lz_بائيٽون ^= 0xFFFF)
    {
      TDEFL_PUT_بٽ(d->m_ڪل_lz_بائيٽون & 0xFFFF, 16);
    }
    لكل (i = 0; i < d->m_ڪل_lz_بائيٽون; ++i)
    {
      TDEFL_PUT_بٽ(d->m_dict[(d->m_lz_ڪوڊ_buf_dict_pos + i) & TDEFL_LZ_DICT_سائيز_نقاب], 8);
    }
  }
  // Check for the extremely unlikely (if not impossible) case of the compressed block not fitting into the output buffer when using dynamic codes.
  وإلا إذا (!comp_بلاڪ_succeeded)
  {
    d->m_pOutput_buf = pSaved_output_buf; d->m_ٻٽو_انگ_بفر = saved_ٻٽو_انگ_buf; d->m_بٽ_اندريون = saved_بٽ_اندريون;
    tdefl_compress_بلاڪ(d, MZ_TRUE);
  }

  إذا (flush)
  {
    إذا (flush == TDEFL_پڄاڻي)
    {
      إذا (d->m_بٽ_اندريون) { TDEFL_PUT_بٽ(0, 8 - d->m_بٽ_اندريون); }
      إذا (d->m_flags & TDEFL_WRITE_ZLIB_سرو) { mz_uint i, a = d->m_adler32; لكل (i = 0; i < 4; i++) { TDEFL_PUT_بٽ((a >> 24) & 0xFF, 8); a <<= 8; } }
    }
    وإلا
    {
      mz_uint i, z = 0; TDEFL_PUT_بٽ(0, 3); إذا (d->m_بٽ_اندريون) { TDEFL_PUT_بٽ(0, 8 - d->m_بٽ_اندريون); } لكل (i = 2; i; --i, z ^= 0xFFFF) { TDEFL_PUT_بٽ(z & 0xFFFF, 16); }
    }
  }

  MZ_ASSERT(d->m_pOutput_buf < d->m_p_Output_buf_پڇاڙي);

  memset(&d->m_huff_ڳڻپ[0][0], 0, حجم(d->m_huff_ڳڻپ[0][0]) * TDEFL_MAX_HUFF_SYMBOLS_0);
  memset(&d->m_huff_ڳڻپ[1][0], 0, حجم(d->m_huff_ڳڻپ[1][0]) * TDEFL_MAX_HUFF_SYMBOLS_1);

  d->m_p_LZ_ڪوڊ_buf = d->m_lz_ڪوڊ_buf + 1; d->m_pLZ_flags = d->m_lz_ڪوڊ_buf; d->m_انگ_flags_کاٻو = 8; d->m_lz_ڪوڊ_buf_dict_pos += d->m_ڪل_lz_بائيٽون; d->m_ڪل_lz_بائيٽون = 0; d->m_بلاڪ_اشاريو++;

  إذا ((n = (صحيح)(d->m_pOutput_buf - p_Output_buf_شروعات)) != 0)
  {
    إذا (d->m_pPut_buf_func)
    {
      *d->m_p_اندريون_buf_سائيز = d->m_pSrc - (ثابت mz_uint8 *)d->m_p_اندريون_buf;
      إذا (!(*d->m_pPut_buf_func)(d->m_output_buf, n, d->m_pPut_buf_user))
        أرجع (d->m_prev_return_حالت = TDEFL_حالت_PUT_BUF_FAILED);
    }
    وإلا إذا (p_Output_buf_شروعات == d->m_output_buf)
    {
      صحيح بائيٽون_منزل_copy = (صحيح)MZ_MIN((size_t)n, (size_t)(*d->m_p_ٻاهريون_buf_سائيز - d->m_ٻاهريون_buf_ofs));
      يادگيري_نقل((mz_uint8 *)d->m_p_ٻاهريون_buf + d->m_ٻاهريون_buf_ofs, d->m_output_buf, بائيٽون_منزل_copy);
      d->m_ٻاهريون_buf_ofs += بائيٽون_منزل_copy;
      إذا ((n -= بائيٽون_منزل_copy) != 0)
      {
        d->m_output_flush_ofs = بائيٽون_منزل_copy;
        d->m_output_flush_بچيل = n;
      }
    }
    وإلا
    {
      d->m_ٻاهريون_buf_ofs += n;
    }
  }

  أرجع d->m_output_flush_بچيل;
}

#إذا MINIZ_USE_UNALIGNED_LOADS_AND_STORES
#وصف_ڪريو TDEFL_READ_UNALIGNED_لفظ(p) *(ثابت mz_uint16*)(p)
ساكن MZ_FORCEINLINE فراغ tdefl_ڳوليو_ميلاپ(tdefl_compressor *d, mz_uint lookahead_pos, mz_uint max_dist, mz_uint max_ميلاپ_len, mz_uint *p_ميلاپ_dist, mz_uint *p_ميلاپ_len)
{
  mz_uint dist, pos = lookahead_pos & TDEFL_LZ_DICT_سائيز_نقاب, ميلاپ_len = *p_ميلاپ_len, probe_pos = pos, ايندڙ_probe_pos, probe_len;
  mz_uint انگ_probes_کاٻو = d->m_max_probes[ميلاپ_len >= 32];
  ثابت mz_uint16 *s = (ثابت mz_uint16*)(d->m_dict + pos), *p, *q;
  mz_uint16 c01 = TDEFL_READ_UNALIGNED_لفظ(&d->m_dict[pos + ميلاپ_len - 1]), s01 = TDEFL_READ_UNALIGNED_لفظ(s);
  MZ_ASSERT(max_ميلاپ_len <= TDEFL_MAX_ميلاپ_LEN); إذا (max_ميلاپ_len <= ميلاپ_len) أرجع;
  لكل ( ; ; )
  {
    لكل ( ; ; )
    {
      إذا (--انگ_probes_کاٻو == 0) أرجع;
      #وصف_ڪريو TDEFL_PROBE \
        ايندڙ_probe_pos = d->m_ايندڙ[probe_pos]; \
        إذا ((!ايندڙ_probe_pos) || ((dist = (mz_uint16)(lookahead_pos - ايندڙ_probe_pos)) > max_dist)) أرجع; \
        probe_pos = ايندڙ_probe_pos & TDEFL_LZ_DICT_سائيز_نقاب; \
        إذا (TDEFL_READ_UNALIGNED_لفظ(&d->m_dict[probe_pos + ميلاپ_len - 1]) == c01) اكسر;
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
      *p_ميلاپ_dist = dist; *p_ميلاپ_len = MZ_MIN(max_ميلاپ_len, TDEFL_MAX_ميلاپ_LEN); اكسر;
    }
    وإلا إذا ((probe_len = ((mz_uint)(p - s) * 2) + (mz_uint)(*(ثابت mz_uint8*)p == *(ثابت mz_uint8*)q)) > ميلاپ_len)
    {
      *p_ميلاپ_dist = dist; إذا ((*p_ميلاپ_len = ميلاپ_len = MZ_MIN(max_ميلاپ_len, probe_len)) == max_ميلاپ_len) اكسر;
      c01 = TDEFL_READ_UNALIGNED_لفظ(&d->m_dict[pos + ميلاپ_len - 1]);
    }
  }
}
#وإلا
ساكن MZ_FORCEINLINE فراغ tdefl_ڳوليو_ميلاپ(tdefl_compressor *d, mz_uint lookahead_pos, mz_uint max_dist, mz_uint max_ميلاپ_len, mz_uint *p_ميلاپ_dist, mz_uint *p_ميلاپ_len)
{
  mz_uint dist, pos = lookahead_pos & TDEFL_LZ_DICT_سائيز_نقاب, ميلاپ_len = *p_ميلاپ_len, probe_pos = pos, ايندڙ_probe_pos, probe_len;
  mz_uint انگ_probes_کاٻو = d->m_max_probes[ميلاپ_len >= 32];
  ثابت mz_uint8 *s = d->m_dict + pos, *p, *q;
  mz_uint8 c0 = d->m_dict[pos + ميلاپ_len], c1 = d->m_dict[pos + ميلاپ_len - 1];
  MZ_ASSERT(max_ميلاپ_len <= TDEFL_MAX_ميلاپ_LEN); إذا (max_ميلاپ_len <= ميلاپ_len) أرجع;
  لكل ( ; ; )
  {
    لكل ( ; ; )
    {
      إذا (--انگ_probes_کاٻو == 0) أرجع;
      #وصف_ڪريو TDEFL_PROBE \
        ايندڙ_probe_pos = d->m_ايندڙ[probe_pos]; \
        إذا ((!ايندڙ_probe_pos) || ((dist = (mz_uint16)(lookahead_pos - ايندڙ_probe_pos)) > max_dist)) أرجع; \
        probe_pos = ايندڙ_probe_pos & TDEFL_LZ_DICT_سائيز_نقاب; \
        إذا ((d->m_dict[probe_pos + ميلاپ_len] == c0) && (d->m_dict[probe_pos + ميلاپ_len - 1] == c1)) اكسر;
      TDEFL_PROBE
      TDEFL_PROBE
      TDEFL_PROBE
    }
    إذا (!dist) اكسر;
    p = s; q = d->m_dict + probe_pos;
    لكل (probe_len = 0; probe_len < max_ميلاپ_len; probe_len++) {
        إذا (*p++ != *q++) اكسر;
    }
    إذا (probe_len > ميلاپ_len)
    {
      *p_ميلاپ_dist = dist;
      إذا ((*p_ميلاپ_len = ميلاپ_len = probe_len) == max_ميلاپ_len) أرجع;
      c0 = d->m_dict[pos + ميلاپ_len]; c1 = d->m_dict[pos + ميلاپ_len - 1];
    }
  }
}
#جيڪڏهن_پورو // #if MINIZ_USE_UNALIGNED_LOADS_AND_STORES

#إذا MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
ساكن mz_bool tdefl_compress_fast(tdefl_compressor *d)
{
  // Faster, minimally featured LZRW1-style match+parse loop with better register utilization. Intended for applications where raw throughput is valued more highly than ratio.
  mz_uint lookahead_pos = d->m_lookahead_pos, lookahead_سائيز = d->m_lookahead_سائيز, dict_سائيز = d->m_dict_سائيز, ڪل_lz_بائيٽون = d->m_ڪل_lz_بائيٽون, انگ_flags_کاٻو = d->m_انگ_flags_کاٻو;
  mz_uint8 *p_LZ_ڪوڊ_buf = d->m_p_LZ_ڪوڊ_buf, *pLZ_flags = d->m_pLZ_flags;
  mz_uint cur_pos = lookahead_pos & TDEFL_LZ_DICT_سائيز_نقاب;

  طالما ((d->m_src_buf_کاٻو) || ((d->m_flush) && (lookahead_سائيز)))
  {
    ثابت mz_uint TDEFL_COMP_FAST_LOOKAHEAD_سائيز = 4096;
    mz_uint dst_pos = (lookahead_pos + lookahead_سائيز) & TDEFL_LZ_DICT_سائيز_نقاب;
    mz_uint انگ_بائيٽون_منزل_process = (mz_uint)MZ_MIN(d->m_src_buf_کاٻو, TDEFL_COMP_FAST_LOOKAHEAD_سائيز - lookahead_سائيز);
    d->m_src_buf_کاٻو -= انگ_بائيٽون_منزل_process;
    lookahead_سائيز += انگ_بائيٽون_منزل_process;

    طالما (انگ_بائيٽون_منزل_process)
    {
      mz_uint32 n = MZ_MIN(TDEFL_LZ_DICT_سائيز - dst_pos, انگ_بائيٽون_منزل_process);
      يادگيري_نقل(d->m_dict + dst_pos, d->m_pSrc, n);
      إذا (dst_pos < (TDEFL_MAX_ميلاپ_LEN - 1))
        يادگيري_نقل(d->m_dict + TDEFL_LZ_DICT_سائيز + dst_pos, d->m_pSrc, MZ_MIN(n, (TDEFL_MAX_ميلاپ_LEN - 1) - dst_pos));
      d->m_pSrc += n;
      dst_pos = (dst_pos + n) & TDEFL_LZ_DICT_سائيز_نقاب;
      انگ_بائيٽون_منزل_process -= n;
    }

    dict_سائيز = MZ_MIN(TDEFL_LZ_DICT_سائيز - lookahead_سائيز, dict_سائيز);
    إذا ((!d->m_flush) && (lookahead_سائيز < TDEFL_COMP_FAST_LOOKAHEAD_سائيز)) اكسر;

    طالما (lookahead_سائيز >= 4)
    {
      mz_uint cur_ميلاپ_dist, cur_ميلاپ_len = 1;
      mz_uint8 *pCur_dict = d->m_dict + cur_pos;
      mz_uint پهريون_trigram = (*(ثابت mz_uint32 *)pCur_dict) & 0xFFFFFF;
      mz_uint hash = (پهريون_trigram ^ (پهريون_trigram >> (24 - (TDEFL_LZ_HASH_بٽ - 8)))) & TDEFL_LEVEL1_HASH_سائيز_نقاب;
      mz_uint probe_pos = d->m_hash[hash];
      d->m_hash[hash] = (mz_uint16)lookahead_pos;

      إذا (((cur_ميلاپ_dist = (mz_uint16)(lookahead_pos - probe_pos)) <= dict_سائيز) && ((*(ثابت mz_uint32 *)(d->m_dict + (probe_pos &= TDEFL_LZ_DICT_سائيز_نقاب)) & 0xFFFFFF) == پهريون_trigram))
      {
        ثابت mz_uint16 *p = (ثابت mz_uint16 *)pCur_dict;
        ثابت mz_uint16 *q = (ثابت mz_uint16 *)(d->m_dict + probe_pos);
        mz_uint32 probe_len = 32;
        افعل { } طالما ( (TDEFL_READ_UNALIGNED_لفظ(++p) == TDEFL_READ_UNALIGNED_لفظ(++q)) && (TDEFL_READ_UNALIGNED_لفظ(++p) == TDEFL_READ_UNALIGNED_لفظ(++q)) &&
          (TDEFL_READ_UNALIGNED_لفظ(++p) == TDEFL_READ_UNALIGNED_لفظ(++q)) && (TDEFL_READ_UNALIGNED_لفظ(++p) == TDEFL_READ_UNALIGNED_لفظ(++q)) && (--probe_len > 0) );
        cur_ميلاپ_len = ((mz_uint)(p - (ثابت mz_uint16 *)pCur_dict) * 2) + (mz_uint)(*(ثابت mz_uint8 *)p == *(ثابت mz_uint8 *)q);
        إذا (!probe_len)
          cur_ميلاپ_len = cur_ميلاپ_dist ? TDEFL_MAX_ميلاپ_LEN : 0;

        إذا ((cur_ميلاپ_len < TDEFL_MIN_ميلاپ_LEN) || ((cur_ميلاپ_len == TDEFL_MIN_ميلاپ_LEN) && (cur_ميلاپ_dist >= 8U*1024U)))
        {
          cur_ميلاپ_len = 1;
          *p_LZ_ڪوڊ_buf++ = (mz_uint8)پهريون_trigram;
          *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
          d->m_huff_ڳڻپ[0][(mz_uint8)پهريون_trigram]++;
        }
        وإلا
        {
          mz_uint32 s0, s1;
          cur_ميلاپ_len = MZ_MIN(cur_ميلاپ_len, lookahead_سائيز);

          MZ_ASSERT((cur_ميلاپ_len >= TDEFL_MIN_ميلاپ_LEN) && (cur_ميلاپ_dist >= 1) && (cur_ميلاپ_dist <= TDEFL_LZ_DICT_سائيز));

          cur_ميلاپ_dist--;

          p_LZ_ڪوڊ_buf[0] = (mz_uint8)(cur_ميلاپ_len - TDEFL_MIN_ميلاپ_LEN);
          *(mz_uint16 *)(&p_LZ_ڪوڊ_buf[1]) = (mz_uint16)cur_ميلاپ_dist;
          p_LZ_ڪوڊ_buf += 3;
          *pLZ_flags = (mz_uint8)((*pLZ_flags >> 1) | 0x80);

          s0 = s_tdefl_small_dist_sym[cur_ميلاپ_dist & 511];
          s1 = s_tdefl_large_dist_sym[cur_ميلاپ_dist >> 8];
          d->m_huff_ڳڻپ[1][(cur_ميلاپ_dist < 512) ? s0 : s1]++;

          d->m_huff_ڳڻپ[0][s_tdefl_len_sym[cur_ميلاپ_len - TDEFL_MIN_ميلاپ_LEN]]++;
        }
      }
      وإلا
      {
        *p_LZ_ڪوڊ_buf++ = (mz_uint8)پهريون_trigram;
        *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
        d->m_huff_ڳڻپ[0][(mz_uint8)پهريون_trigram]++;
      }

      إذا (--انگ_flags_کاٻو == 0) { انگ_flags_کاٻو = 8; pLZ_flags = p_LZ_ڪوڊ_buf++; }

      ڪل_lz_بائيٽون += cur_ميلاپ_len;
      lookahead_pos += cur_ميلاپ_len;
      dict_سائيز = MZ_MIN(dict_سائيز + cur_ميلاپ_len, TDEFL_LZ_DICT_سائيز);
      cur_pos = (cur_pos + cur_ميلاپ_len) & TDEFL_LZ_DICT_سائيز_نقاب;
      MZ_ASSERT(lookahead_سائيز >= cur_ميلاپ_len);
      lookahead_سائيز -= cur_ميلاپ_len;

      إذا (p_LZ_ڪوڊ_buf > &d->m_lz_ڪوڊ_buf[TDEFL_LZ_ڪوڊ_BUF_سائيز - 8])
      {
        صحيح n;
        d->m_lookahead_pos = lookahead_pos; d->m_lookahead_سائيز = lookahead_سائيز; d->m_dict_سائيز = dict_سائيز;
        d->m_ڪل_lz_بائيٽون = ڪل_lz_بائيٽون; d->m_p_LZ_ڪوڊ_buf = p_LZ_ڪوڊ_buf; d->m_pLZ_flags = pLZ_flags; d->m_انگ_flags_کاٻو = انگ_flags_کاٻو;
        إذا ((n = tdefl_flush_بلاڪ(d, 0)) != 0)
          أرجع (n < 0) ? MZ_FALSE : MZ_TRUE;
        ڪل_lz_بائيٽون = d->m_ڪل_lz_بائيٽون; p_LZ_ڪوڊ_buf = d->m_p_LZ_ڪوڊ_buf; pLZ_flags = d->m_pLZ_flags; انگ_flags_کاٻو = d->m_انگ_flags_کاٻو;
      }
    }

    طالما (lookahead_سائيز)
    {
      mz_uint8 lit = d->m_dict[cur_pos];

      ڪل_lz_بائيٽون++;
      *p_LZ_ڪوڊ_buf++ = lit;
      *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
      إذا (--انگ_flags_کاٻو == 0) { انگ_flags_کاٻو = 8; pLZ_flags = p_LZ_ڪوڊ_buf++; }

      d->m_huff_ڳڻپ[0][lit]++;

      lookahead_pos++;
      dict_سائيز = MZ_MIN(dict_سائيز + 1, TDEFL_LZ_DICT_سائيز);
      cur_pos = (cur_pos + 1) & TDEFL_LZ_DICT_سائيز_نقاب;
      lookahead_سائيز--;

      إذا (p_LZ_ڪوڊ_buf > &d->m_lz_ڪوڊ_buf[TDEFL_LZ_ڪوڊ_BUF_سائيز - 8])
      {
        صحيح n;
        d->m_lookahead_pos = lookahead_pos; d->m_lookahead_سائيز = lookahead_سائيز; d->m_dict_سائيز = dict_سائيز;
        d->m_ڪل_lz_بائيٽون = ڪل_lz_بائيٽون; d->m_p_LZ_ڪوڊ_buf = p_LZ_ڪوڊ_buf; d->m_pLZ_flags = pLZ_flags; d->m_انگ_flags_کاٻو = انگ_flags_کاٻو;
        إذا ((n = tdefl_flush_بلاڪ(d, 0)) != 0)
          أرجع (n < 0) ? MZ_FALSE : MZ_TRUE;
        ڪل_lz_بائيٽون = d->m_ڪل_lz_بائيٽون; p_LZ_ڪوڊ_buf = d->m_p_LZ_ڪوڊ_buf; pLZ_flags = d->m_pLZ_flags; انگ_flags_کاٻو = d->m_انگ_flags_کاٻو;
      }
    }
  }

  d->m_lookahead_pos = lookahead_pos; d->m_lookahead_سائيز = lookahead_سائيز; d->m_dict_سائيز = dict_سائيز;
  d->m_ڪل_lz_بائيٽون = ڪل_lz_بائيٽون; d->m_p_LZ_ڪوڊ_buf = p_LZ_ڪوڊ_buf; d->m_pLZ_flags = pLZ_flags; d->m_انگ_flags_کاٻو = انگ_flags_کاٻو;
  أرجع MZ_TRUE;
}
#جيڪڏهن_پورو // MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN

ساكن MZ_FORCEINLINE فراغ tdefl_رڪارڊ_literal(tdefl_compressor *d, mz_uint8 lit)
{
  d->m_ڪل_lz_بائيٽون++;
  *d->m_p_LZ_ڪوڊ_buf++ = lit;
  *d->m_pLZ_flags = (mz_uint8)(*d->m_pLZ_flags >> 1); إذا (--d->m_انگ_flags_کاٻو == 0) { d->m_انگ_flags_کاٻو = 8; d->m_pLZ_flags = d->m_p_LZ_ڪوڊ_buf++; }
  d->m_huff_ڳڻپ[0][lit]++;
}

ساكن MZ_FORCEINLINE فراغ tdefl_رڪارڊ_ميلاپ(tdefl_compressor *d, mz_uint ميلاپ_len, mz_uint ميلاپ_dist)
{
  mz_uint32 s0, s1;

  MZ_ASSERT((ميلاپ_len >= TDEFL_MIN_ميلاپ_LEN) && (ميلاپ_dist >= 1) && (ميلاپ_dist <= TDEFL_LZ_DICT_سائيز));

  d->m_ڪل_lz_بائيٽون += ميلاپ_len;

  d->m_p_LZ_ڪوڊ_buf[0] = (mz_uint8)(ميلاپ_len - TDEFL_MIN_ميلاپ_LEN);

  ميلاپ_dist -= 1;
  d->m_p_LZ_ڪوڊ_buf[1] = (mz_uint8)(ميلاپ_dist & 0xFF);
  d->m_p_LZ_ڪوڊ_buf[2] = (mz_uint8)(ميلاپ_dist >> 8); d->m_p_LZ_ڪوڊ_buf += 3;

  *d->m_pLZ_flags = (mz_uint8)((*d->m_pLZ_flags >> 1) | 0x80); إذا (--d->m_انگ_flags_کاٻو == 0) { d->m_انگ_flags_کاٻو = 8; d->m_pLZ_flags = d->m_p_LZ_ڪوڊ_buf++; }

  s0 = s_tdefl_small_dist_sym[ميلاپ_dist & 511]; s1 = s_tdefl_large_dist_sym[(ميلاپ_dist >> 8) & 127];
  d->m_huff_ڳڻپ[1][(ميلاپ_dist < 512) ? s0 : s1]++;

  إذا (ميلاپ_len >= TDEFL_MIN_ميلاپ_LEN) d->m_huff_ڳڻپ[0][s_tdefl_len_sym[ميلاپ_len - TDEFL_MIN_ميلاپ_LEN]]++;
}

ساكن mz_bool tdefl_compress_عام(tdefl_compressor *d)
{
  ثابت mz_uint8 *pSrc = d->m_pSrc; size_t src_buf_کاٻو = d->m_src_buf_کاٻو;
  tdefl_flush flush = d->m_flush;

  طالما ((src_buf_کاٻو) || ((flush) && (d->m_lookahead_سائيز)))
  {
    mz_uint len_منزل_move, cur_ميلاپ_dist, cur_ميلاپ_len, cur_pos;
    // Update dictionary and hash chains. Keeps the lookahead size equal to TDEFL_MAX_MATCH_LEN.
    إذا ((d->m_lookahead_سائيز + d->m_dict_سائيز) >= (TDEFL_MIN_ميلاپ_LEN - 1))
    {
      mz_uint dst_pos = (d->m_lookahead_pos + d->m_lookahead_سائيز) & TDEFL_LZ_DICT_سائيز_نقاب, ins_pos = d->m_lookahead_pos + d->m_lookahead_سائيز - 2;
      mz_uint hash = (d->m_dict[ins_pos & TDEFL_LZ_DICT_سائيز_نقاب] << TDEFL_LZ_HASH_سرڪايو) ^ d->m_dict[(ins_pos + 1) & TDEFL_LZ_DICT_سائيز_نقاب];
      mz_uint انگ_بائيٽون_منزل_process = (mz_uint)MZ_MIN(src_buf_کاٻو, TDEFL_MAX_ميلاپ_LEN - d->m_lookahead_سائيز);
      ثابت mz_uint8 *p_Src_پڇاڙي = pSrc ? pSrc + انگ_بائيٽون_منزل_process : عدم;
      src_buf_کاٻو -= انگ_بائيٽون_منزل_process;
      d->m_lookahead_سائيز += انگ_بائيٽون_منزل_process;
      طالما (pSrc != p_Src_پڇاڙي)
      {
        mz_uint8 c = *pSrc++; d->m_dict[dst_pos] = c; إذا (dst_pos < (TDEFL_MAX_ميلاپ_LEN - 1)) d->m_dict[TDEFL_LZ_DICT_سائيز + dst_pos] = c;
        hash = ((hash << TDEFL_LZ_HASH_سرڪايو) ^ c) & (TDEFL_LZ_HASH_سائيز - 1);
        d->m_ايندڙ[ins_pos & TDEFL_LZ_DICT_سائيز_نقاب] = d->m_hash[hash]; d->m_hash[hash] = (mz_uint16)(ins_pos);
        dst_pos = (dst_pos + 1) & TDEFL_LZ_DICT_سائيز_نقاب; ins_pos++;
      }
    }
    وإلا
    {
      طالما ((src_buf_کاٻو) && (d->m_lookahead_سائيز < TDEFL_MAX_ميلاپ_LEN))
      {
        mz_uint8 c = *pSrc++;
        mz_uint dst_pos = (d->m_lookahead_pos + d->m_lookahead_سائيز) & TDEFL_LZ_DICT_سائيز_نقاب;
        src_buf_کاٻو--;
        d->m_dict[dst_pos] = c;
        إذا (dst_pos < (TDEFL_MAX_ميلاپ_LEN - 1))
          d->m_dict[TDEFL_LZ_DICT_سائيز + dst_pos] = c;
        إذا ((++d->m_lookahead_سائيز + d->m_dict_سائيز) >= TDEFL_MIN_ميلاپ_LEN)
        {
          mz_uint ins_pos = d->m_lookahead_pos + (d->m_lookahead_سائيز - 1) - 2;
          mz_uint hash = ((d->m_dict[ins_pos & TDEFL_LZ_DICT_سائيز_نقاب] << (TDEFL_LZ_HASH_سرڪايو * 2)) ^ (d->m_dict[(ins_pos + 1) & TDEFL_LZ_DICT_سائيز_نقاب] << TDEFL_LZ_HASH_سرڪايو) ^ c) & (TDEFL_LZ_HASH_سائيز - 1);
          d->m_ايندڙ[ins_pos & TDEFL_LZ_DICT_سائيز_نقاب] = d->m_hash[hash]; d->m_hash[hash] = (mz_uint16)(ins_pos);
        }
      }
    }
    d->m_dict_سائيز = MZ_MIN(TDEFL_LZ_DICT_سائيز - d->m_lookahead_سائيز, d->m_dict_سائيز);
    إذا ((!flush) && (d->m_lookahead_سائيز < TDEFL_MAX_ميلاپ_LEN))
      اكسر;

    // Simple lazy/greedy parsing state machine.
    len_منزل_move = 1; cur_ميلاپ_dist = 0; cur_ميلاپ_len = d->m_saved_ميلاپ_len ? d->m_saved_ميلاپ_len : (TDEFL_MIN_ميلاپ_LEN - 1); cur_pos = d->m_lookahead_pos & TDEFL_LZ_DICT_سائيز_نقاب;
    إذا (d->m_flags & (TDEFL_RLE_MATCHES | TDEFL_FORCE_ALL_RAW_بلاڪون))
    {
      إذا ((d->m_dict_سائيز) && (!(d->m_flags & TDEFL_FORCE_ALL_RAW_بلاڪون)))
      {
        mz_uint8 c = d->m_dict[(cur_pos - 1) & TDEFL_LZ_DICT_سائيز_نقاب];
        cur_ميلاپ_len = 0; طالما (cur_ميلاپ_len < d->m_lookahead_سائيز) { إذا (d->m_dict[cur_pos + cur_ميلاپ_len] != c) اكسر; cur_ميلاپ_len++; }
        إذا (cur_ميلاپ_len < TDEFL_MIN_ميلاپ_LEN) cur_ميلاپ_len = 0; وإلا cur_ميلاپ_dist = 1;
      }
    }
    وإلا
    {
      tdefl_ڳوليو_ميلاپ(d, d->m_lookahead_pos, d->m_dict_سائيز, d->m_lookahead_سائيز, &cur_ميلاپ_dist, &cur_ميلاپ_len);
    }
    إذا (((cur_ميلاپ_len == TDEFL_MIN_ميلاپ_LEN) && (cur_ميلاپ_dist >= 8U*1024U)) || (cur_pos == cur_ميلاپ_dist) || ((d->m_flags & TDEFL_FILTER_MATCHES) && (cur_ميلاپ_len <= 5)))
    {
      cur_ميلاپ_dist = cur_ميلاپ_len = 0;
    }
    إذا (d->m_saved_ميلاپ_len)
    {
      إذا (cur_ميلاپ_len > d->m_saved_ميلاپ_len)
      {
        tdefl_رڪارڊ_literal(d, (mz_uint8)d->m_saved_lit);
        إذا (cur_ميلاپ_len >= 128)
        {
          tdefl_رڪارڊ_ميلاپ(d, cur_ميلاپ_len, cur_ميلاپ_dist);
          d->m_saved_ميلاپ_len = 0; len_منزل_move = cur_ميلاپ_len;
        }
        وإلا
        {
          d->m_saved_lit = d->m_dict[cur_pos]; d->m_saved_ميلاپ_dist = cur_ميلاپ_dist; d->m_saved_ميلاپ_len = cur_ميلاپ_len;
        }
      }
      وإلا
      {
        tdefl_رڪارڊ_ميلاپ(d, d->m_saved_ميلاپ_len, d->m_saved_ميلاپ_dist);
        len_منزل_move = d->m_saved_ميلاپ_len - 1; d->m_saved_ميلاپ_len = 0;
      }
    }
    وإلا إذا (!cur_ميلاپ_dist)
      tdefl_رڪارڊ_literal(d, d->m_dict[MZ_MIN(cur_pos, حجم(d->m_dict) - 1)]);
    وإلا إذا ((d->m_greedy_parsing) || (d->m_flags & TDEFL_RLE_MATCHES) || (cur_ميلاپ_len >= 128))
    {
      tdefl_رڪارڊ_ميلاپ(d, cur_ميلاپ_len, cur_ميلاپ_dist);
      len_منزل_move = cur_ميلاپ_len;
    }
    وإلا
    {
      d->m_saved_lit = d->m_dict[MZ_MIN(cur_pos, حجم(d->m_dict) - 1)]; d->m_saved_ميلاپ_dist = cur_ميلاپ_dist; d->m_saved_ميلاپ_len = cur_ميلاپ_len;
    }
    // Move the lookahead forward by len_to_move bytes.
    d->m_lookahead_pos += len_منزل_move;
    MZ_ASSERT(d->m_lookahead_سائيز >= len_منزل_move);
    d->m_lookahead_سائيز -= len_منزل_move;
    d->m_dict_سائيز = MZ_MIN(d->m_dict_سائيز + len_منزل_move, TDEFL_LZ_DICT_سائيز);
    // Check if it's time to flush the current LZ codes to the internal output buffer.
    إذا ( (d->m_p_LZ_ڪوڊ_buf > &d->m_lz_ڪوڊ_buf[TDEFL_LZ_ڪوڊ_BUF_سائيز - 8]) ||
         ( (d->m_ڪل_lz_بائيٽون > 31*1024) && (((((mz_uint)(d->m_p_LZ_ڪوڊ_buf - d->m_lz_ڪوڊ_buf) * 115) >> 7) >= d->m_ڪل_lz_بائيٽون) || (d->m_flags & TDEFL_FORCE_ALL_RAW_بلاڪون))) )
    {
      صحيح n;
      d->m_pSrc = pSrc; d->m_src_buf_کاٻو = src_buf_کاٻو;
      إذا ((n = tdefl_flush_بلاڪ(d, 0)) != 0)
        أرجع (n < 0) ? MZ_FALSE : MZ_TRUE;
    }
  }

  d->m_pSrc = pSrc; d->m_src_buf_کاٻو = src_buf_کاٻو;
  أرجع MZ_TRUE;
}

ساكن tdefl_حالت tdefl_flush_output_بفر(tdefl_compressor *d)
{
  إذا (d->m_p_اندريون_buf_سائيز)
  {
    *d->m_p_اندريون_buf_سائيز = d->m_pSrc - (ثابت mz_uint8 *)d->m_p_اندريون_buf;
  }

  إذا (d->m_p_ٻاهريون_buf_سائيز)
  {
    size_t n = MZ_MIN(*d->m_p_ٻاهريون_buf_سائيز - d->m_ٻاهريون_buf_ofs, d->m_output_flush_بچيل);
    يادگيري_نقل((mz_uint8 *)d->m_p_ٻاهريون_buf + d->m_ٻاهريون_buf_ofs, d->m_output_buf + d->m_output_flush_ofs, n);
    d->m_output_flush_ofs += (mz_uint)n;
    d->m_output_flush_بچيل -= (mz_uint)n;
    d->m_ٻاهريون_buf_ofs += n;

    *d->m_p_ٻاهريون_buf_سائيز = d->m_ٻاهريون_buf_ofs;
  }

  أرجع (d->m_ختم && !d->m_output_flush_بچيل) ? TDEFL_حالت_پورو : TDEFL_حالت_OKAY;
}

tdefl_حالت tdefl_compress(tdefl_compressor *d, ثابت فراغ *p_اندريون_buf, size_t *p_اندريون_buf_سائيز, فراغ *p_ٻاهريون_buf, size_t *p_ٻاهريون_buf_سائيز, tdefl_flush flush)
{
  إذا (!d)
  {
    إذا (p_اندريون_buf_سائيز) *p_اندريون_buf_سائيز = 0;
    إذا (p_ٻاهريون_buf_سائيز) *p_ٻاهريون_buf_سائيز = 0;
    أرجع TDEFL_حالت_BAD_PARAM;
  }

  d->m_p_اندريون_buf = p_اندريون_buf; d->m_p_اندريون_buf_سائيز = p_اندريون_buf_سائيز;
  d->m_p_ٻاهريون_buf = p_ٻاهريون_buf; d->m_p_ٻاهريون_buf_سائيز = p_ٻاهريون_buf_سائيز;
  d->m_pSrc = (ثابت mz_uint8 *)(p_اندريون_buf); d->m_src_buf_کاٻو = p_اندريون_buf_سائيز ? *p_اندريون_buf_سائيز : 0;
  d->m_ٻاهريون_buf_ofs = 0;
  d->m_flush = flush;

  إذا ( ((d->m_pPut_buf_func != عدم) == ((p_ٻاهريون_buf != عدم) || (p_ٻاهريون_buf_سائيز != عدم))) || (d->m_prev_return_حالت != TDEFL_حالت_OKAY) ||
        (d->m_چاهي_منزل_پڄاڻي && (flush != TDEFL_پڄاڻي)) || (p_اندريون_buf_سائيز && *p_اندريون_buf_سائيز && !p_اندريون_buf) || (p_ٻاهريون_buf_سائيز && *p_ٻاهريون_buf_سائيز && !p_ٻاهريون_buf) )
  {
    إذا (p_اندريون_buf_سائيز) *p_اندريون_buf_سائيز = 0;
    إذا (p_ٻاهريون_buf_سائيز) *p_ٻاهريون_buf_سائيز = 0;
    أرجع (d->m_prev_return_حالت = TDEFL_حالت_BAD_PARAM);
  }
  d->m_چاهي_منزل_پڄاڻي |= (flush == TDEFL_پڄاڻي);

  إذا ((d->m_output_flush_بچيل) || (d->m_ختم))
    أرجع (d->m_prev_return_حالت = tdefl_flush_output_بفر(d));

#إذا MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  إذا (((d->m_flags & TDEFL_MAX_PROBES_نقاب) == 1) &&
      ((d->m_flags & TDEFL_GREEDY_PARSING_FLAG) != 0) &&
      ((d->m_flags & (TDEFL_FILTER_MATCHES | TDEFL_FORCE_ALL_RAW_بلاڪون | TDEFL_RLE_MATCHES)) == 0))
  {
    إذا (!tdefl_compress_fast(d))
      أرجع d->m_prev_return_حالت;
  }
  وإلا
#جيڪڏهن_پورو // #if MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  {
    إذا (!tdefl_compress_عام(d))
      أرجع d->m_prev_return_حالت;
  }

  إذا ((d->m_flags & (TDEFL_WRITE_ZLIB_سرو | TDEFL_COMPUTE_ADLER32)) && (p_اندريون_buf))
    d->m_adler32 = (mz_uint32)mz_adler32(d->m_adler32, (ثابت mz_uint8 *)p_اندريون_buf, d->m_pSrc - (ثابت mz_uint8 *)p_اندريون_buf);

  إذا ((flush) && (!d->m_lookahead_سائيز) && (!d->m_src_buf_کاٻو) && (!d->m_output_flush_بچيل))
  {
    إذا (tdefl_flush_بلاڪ(d, flush) < 0)
      أرجع d->m_prev_return_حالت;
    d->m_ختم = (flush == TDEFL_پڄاڻي);
    إذا (flush == TDEFL_ڀريل_FLUSH) { MZ_CLEAR_ARR(d->m_hash); MZ_CLEAR_ARR(d->m_ايندڙ); d->m_dict_سائيز = 0; }
  }

  أرجع (d->m_prev_return_حالت = tdefl_flush_output_بفر(d));
}

tdefl_حالت tdefl_compress_بفر(tdefl_compressor *d, ثابت فراغ *p_اندريون_buf, size_t اندريون_buf_سائيز, tdefl_flush flush)
{
  MZ_ASSERT(d->m_pPut_buf_func); أرجع tdefl_compress(d, p_اندريون_buf, &اندريون_buf_سائيز, عدم, عدم, flush);
}

tdefl_حالت tdefl_init(tdefl_compressor *d, tdefl_put_buf_func_ptr pPut_buf_func, فراغ *pPut_buf_user, صحيح flags)
{
  d->m_pPut_buf_func = pPut_buf_func; d->m_pPut_buf_user = pPut_buf_user;
  d->m_flags = (mz_uint)(flags); d->m_max_probes[0] = 1 + ((flags & 0xFFF) + 2) / 3; d->m_greedy_parsing = (flags & TDEFL_GREEDY_PARSING_FLAG) != 0;
  d->m_max_probes[1] = 1 + (((flags & 0xFFF) >> 2) + 2) / 3;
  إذا (!(flags & TDEFL_NONDETERMINISTIC_PARSING_FLAG)) MZ_CLEAR_ARR(d->m_hash);
  d->m_lookahead_pos = d->m_lookahead_سائيز = d->m_dict_سائيز = d->m_ڪل_lz_بائيٽون = d->m_lz_ڪوڊ_buf_dict_pos = d->m_بٽ_اندريون = 0;
  d->m_output_flush_ofs = d->m_output_flush_بچيل = d->m_ختم = d->m_بلاڪ_اشاريو = d->m_ٻٽو_انگ_بفر = d->m_چاهي_منزل_پڄاڻي = 0;
  d->m_p_LZ_ڪوڊ_buf = d->m_lz_ڪوڊ_buf + 1; d->m_pLZ_flags = d->m_lz_ڪوڊ_buf; d->m_انگ_flags_کاٻو = 8;
  d->m_pOutput_buf = d->m_output_buf; d->m_p_Output_buf_پڇاڙي = d->m_output_buf; d->m_prev_return_حالت = TDEFL_حالت_OKAY;
  d->m_saved_ميلاپ_dist = d->m_saved_ميلاپ_len = d->m_saved_lit = 0; d->m_adler32 = 1;
  d->m_p_اندريون_buf = عدم; d->m_p_ٻاهريون_buf = عدم;
  d->m_p_اندريون_buf_سائيز = عدم; d->m_p_ٻاهريون_buf_سائيز = عدم;
  d->m_flush = TDEFL_NO_FLUSH; d->m_pSrc = عدم; d->m_src_buf_کاٻو = 0; d->m_ٻاهريون_buf_ofs = 0;
  memset(&d->m_huff_ڳڻپ[0][0], 0, حجم(d->m_huff_ڳڻپ[0][0]) * TDEFL_MAX_HUFF_SYMBOLS_0);
  memset(&d->m_huff_ڳڻپ[1][0], 0, حجم(d->m_huff_ڳڻپ[1][0]) * TDEFL_MAX_HUFF_SYMBOLS_1);
  أرجع TDEFL_حالت_OKAY;
}

#جيڪڏهن_وصف_نه_ٿيل MINIZ_SDL_NOUNUSED
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
  succeeded = succeeded && (tdefl_compress_بفر(pComp, pBuf, buf_len, TDEFL_پڄاڻي) == TDEFL_حالت_پورو);
  MZ_FREE(pComp); أرجع succeeded;
}
#جيڪڏهن_پورو /* MINIZ_SDL_NOUNUSED */

تعريفنوع بنية
{
  size_t m_سائيز, m_صلاحيت;
  mz_uint8 *m_pBuf;
  mz_bool m_expandable;
} tdefl_output_بفر;

ساكن mz_bool tdefl_output_بفر_putter(ثابت فراغ *pBuf, صحيح len, فراغ *pUser)
{
  tdefl_output_بفر *p = (tdefl_output_بفر *)pUser;
  size_t new_سائيز = p->m_سائيز + len;
  إذا (new_سائيز > p->m_صلاحيت)
  {
    size_t new_صلاحيت = p->m_صلاحيت; mz_uint8 *pNew_buf; إذا (!p->m_expandable) أرجع MZ_FALSE;
    افعل { new_صلاحيت = MZ_MAX(128U, new_صلاحيت << 1U); } طالما (new_سائيز > new_صلاحيت);
    pNew_buf = (mz_uint8*)MZ_REALLOC(p->m_pBuf, new_صلاحيت); إذا (!pNew_buf) أرجع MZ_FALSE;
    p->m_pBuf = pNew_buf; p->m_صلاحيت = new_صلاحيت;
  }
  يادگيري_نقل((mz_uint8*)p->m_pBuf + p->m_سائيز, pBuf, len); p->m_سائيز = new_سائيز;
  أرجع MZ_TRUE;
}

#جيڪڏهن_وصف_نه_ٿيل MINIZ_SDL_NOUNUSED
فراغ *tdefl_compress_mem_منزل_ڍير(ثابت فراغ *pSrc_buf, size_t src_buf_len, size_t *p_ٻاهريون_len, صحيح flags)
{
  tdefl_output_بفر ٻاهريون_buf; MZ_CLEAR_OBJ(ٻاهريون_buf);
  إذا (!p_ٻاهريون_len) أرجع MZ_FALSE; وإلا *p_ٻاهريون_len = 0;
  ٻاهريون_buf.m_expandable = MZ_TRUE;
  إذا (!tdefl_compress_mem_منزل_output(pSrc_buf, src_buf_len, tdefl_output_بفر_putter, &ٻاهريون_buf, flags)) أرجع عدم;
  *p_ٻاهريون_len = ٻاهريون_buf.m_سائيز; أرجع ٻاهريون_buf.m_pBuf;
}

size_t tdefl_compress_mem_منزل_mem(فراغ *p_ٻاهريون_buf, size_t ٻاهريون_buf_len, ثابت فراغ *pSrc_buf, size_t src_buf_len, صحيح flags)
{
  tdefl_output_بفر ٻاهريون_buf; MZ_CLEAR_OBJ(ٻاهريون_buf);
  إذا (!p_ٻاهريون_buf) أرجع 0;
  ٻاهريون_buf.m_pBuf = (mz_uint8*)p_ٻاهريون_buf; ٻاهريون_buf.m_صلاحيت = ٻاهريون_buf_len;
  إذا (!tdefl_compress_mem_منزل_output(pSrc_buf, src_buf_len, tdefl_output_بفر_putter, &ٻاهريون_buf, flags)) أرجع 0;
  أرجع ٻاهريون_buf.m_سائيز;
}
#جيڪڏهن_پورو /* MINIZ_SDL_NOUNUSED */

#جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_ZLIB_APIS
ساكن ثابت mz_uint s_tdefl_انگ_probes[11] = { 0, 1, 6, 32,  16, 32, 128, 256,  512, 768, 1500 };

// level may actually range from [0,10] (10 is a "hidden" max level, where we want a bit more compression and it's fine if throughput to fall off a cliff on some files).
mz_uint tdefl_create_comp_flags_from_zip_params(صحيح level, صحيح دري_بٽ, صحيح strategy)
{
  mz_uint comp_flags = s_tdefl_انگ_probes[(level >= 0) ? MZ_MIN(10, level) : MZ_DEFAULT_LEVEL] | ((level <= 3) ? TDEFL_GREEDY_PARSING_FLAG : 0);
  إذا (دري_بٽ > 0) comp_flags |= TDEFL_WRITE_ZLIB_سرو;

  إذا (!level) comp_flags |= TDEFL_FORCE_ALL_RAW_بلاڪون;
  وإلا إذا (strategy == MZ_FILTERED) comp_flags |= TDEFL_FILTER_MATCHES;
  وإلا إذا (strategy == MZ_HUFFMAN_ONLY) comp_flags &= ~TDEFL_MAX_PROBES_نقاب;
  وإلا إذا (strategy == MZ_FIXED) comp_flags |= TDEFL_FORCE_ALL_STATIC_بلاڪون;
  وإلا إذا (strategy == MZ_RLE) comp_flags |= TDEFL_RLE_MATCHES;

  أرجع comp_flags;
}
#جيڪڏهن_پورو //MINIZ_NO_ZLIB_APIS

#جيڪڏهن_وصف_ٿيل _MSC_VER
#هدايت warning (ڌڪو)
#هدايت warning (disable:4204) // nonstandard extension used : non-constant aggregate initializer (also supported by GNU C and C99, so no big deal)
#جيڪڏهن_پورو

// Simple PNG writer function by Alex Evans, 2011. Released into the public domain: https://gist.github.com/908299, more context at
// http://altdevblogaday.org/2011/04/06/a-smaller-jpg-encoder/.
// This is actually a modification of Alex's original code so PNG files generated by this function pass pngcheck.
MINIZ_STATIC فراغ *tdefl_write_image_منزل_png_file_اندريون_يادگيري_ex(ثابت فراغ *pImage, صحيح w, صحيح h, صحيح انگ_chans, صحيح bpl, size_t *p_Len_ٻاهريون, mz_uint level, mz_bool flip, mz_uint8 *plte, صحيح plte_سائيز, mz_uint8 *trns, صحيح trns_سائيز)
{
  // Using a local copy of this array here in case MINIZ_NO_ZLIB_APIS was defined.
  ساكن ثابت mz_uint s_tdefl_png_انگ_probes[11] = { 0, 1, 6, 32,  16, 32, 128, 256,  512, 768, 1500 };
  tdefl_compressor *pComp = (tdefl_compressor *)MZ_MALLOC(حجم(tdefl_compressor)); tdefl_output_بفر ٻاهريون_buf; صحيح i, y, z = 0; mz_uint32 c; *p_Len_ٻاهريون = 0; size_t معلومات_شروعات, معلومات_سائيز_3;
  إذا (!pComp) أرجع عدم;
  MZ_CLEAR_OBJ(ٻاهريون_buf); ٻاهريون_buf.m_expandable = MZ_TRUE;
  ٻاهريون_buf.m_صلاحيت = 57+MZ_MAX(64, (1+w*انگ_chans)*h);
  إذا (plte_سائيز > 0)
    ٻاهريون_buf.m_صلاحيت += 12+plte_سائيز;
  إذا (trns_سائيز > 0)
    ٻاهريون_buf.m_صلاحيت += 12+trns_سائيز;
  إذا (عدم == (ٻاهريون_buf.m_pBuf = (mz_uint8*)MZ_MALLOC(ٻاهريون_buf.m_صلاحيت))) { MZ_FREE(pComp); أرجع عدم; }
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

    إذا (انگ_chans == 1 && plte_سائيز > 0)
      pnghdr[25] = 3;
    وإلا
      pnghdr[25] = (chans[انگ_chans]);

    c = (mz_uint32)mz_چڪري_جاچ_32(MZ_چڪري_جاچ_32_INIT,pnghdr+12,17);
    لكل (i=0; i<4; ++i, c<<=8) ((mz_uint8*)(pnghdr+29))[i] = (mz_uint8)(c>>24);
    إذا (!tdefl_output_بفر_putter(pnghdr, حجم(pnghdr), &ٻاهريون_buf)) { *p_Len_ٻاهريون = 0; MZ_FREE(pComp); MZ_FREE(ٻاهريون_buf.m_pBuf); أرجع عدم; }
  }
  // write PLTE chunk
  إذا (plte_سائيز > 0)
  {
    mz_uint8 hdr[8]={0x00,0x00,0x00,0x00,0x50,0x4c,0x54,0x45};

    hdr[0] = (mz_uint8)(plte_سائيز>>24);
    hdr[1] = (mz_uint8)(plte_سائيز>>16);
    hdr[2] = (mz_uint8)(plte_سائيز>> 8);
    hdr[3] = (mz_uint8)(plte_سائيز>> 0);
    إذا (!tdefl_output_بفر_putter(hdr, حجم(hdr), &ٻاهريون_buf)) { *p_Len_ٻاهريون = 0; MZ_FREE(pComp); MZ_FREE(ٻاهريون_buf.m_pBuf); أرجع عدم; }
    معلومات_شروعات = ٻاهريون_buf.m_سائيز;
    إذا (!tdefl_output_بفر_putter(plte, plte_سائيز, &ٻاهريون_buf)) { *p_Len_ٻاهريون = 0; MZ_FREE(pComp); MZ_FREE(ٻاهريون_buf.m_pBuf); أرجع عدم; }
    إذا (!tdefl_output_بفر_putter("\0\0\0\0", 4, &ٻاهريون_buf)) { *p_Len_ٻاهريون = 0; MZ_FREE(pComp); MZ_FREE(ٻاهريون_buf.m_pBuf); أرجع عدم; }
    c = (mz_uint32)mz_چڪري_جاچ_32(MZ_چڪري_جاچ_32_INIT,ٻاهريون_buf.m_pBuf+معلومات_شروعات-4, plte_سائيز+4);
    لكل (i=0; i<4; ++i, c<<=8) (ٻاهريون_buf.m_pBuf+ٻاهريون_buf.m_سائيز-4)[i] = (mz_uint8)(c >> 24);
  }
  // write tRNS chunk
  إذا (trns_سائيز > 0)
  {
    mz_uint8 hdr[8]={0x00,0x00,0x00,0x00,0x74,0x52,0x4E,0x53};

    hdr[0] = (mz_uint8)(trns_سائيز>>24);
    hdr[1] = (mz_uint8)(trns_سائيز>>16);
    hdr[2] = (mz_uint8)(trns_سائيز>> 8);
    hdr[3] = (mz_uint8)(trns_سائيز>> 0);
    إذا (!tdefl_output_بفر_putter(hdr, حجم(hdr), &ٻاهريون_buf)) { *p_Len_ٻاهريون = 0; MZ_FREE(pComp); MZ_FREE(ٻاهريون_buf.m_pBuf); أرجع عدم; }
    معلومات_شروعات = ٻاهريون_buf.m_سائيز;
    إذا (!tdefl_output_بفر_putter(trns, trns_سائيز, &ٻاهريون_buf)) { *p_Len_ٻاهريون = 0; MZ_FREE(pComp); MZ_FREE(ٻاهريون_buf.m_pBuf); أرجع عدم; }
    إذا (!tdefl_output_بفر_putter("\0\0\0\0", 4, &ٻاهريون_buf)) { *p_Len_ٻاهريون = 0; MZ_FREE(pComp); MZ_FREE(ٻاهريون_buf.m_pBuf); أرجع عدم; }
    c = (mz_uint32)mz_چڪري_جاچ_32(MZ_چڪري_جاچ_32_INIT,ٻاهريون_buf.m_pBuf+معلومات_شروعات-4, trns_سائيز+4);
    لكل (i=0; i<4; ++i, c<<=8) (ٻاهريون_buf.m_pBuf+ٻاهريون_buf.m_سائيز-4)[i] = (mz_uint8)(c >> 24);
  }
  // write IDAT chunk
  إذا (!tdefl_output_بفر_putter("\0\0\0\0\x49\x44\x41\x54", 8, &ٻاهريون_buf)) { *p_Len_ٻاهريون = 0; MZ_FREE(pComp); MZ_FREE(ٻاهريون_buf.m_pBuf); أرجع عدم; }
  معلومات_شروعات = ٻاهريون_buf.m_سائيز;
  // compress image data
  tdefl_init(pComp, tdefl_output_بفر_putter, &ٻاهريون_buf, s_tdefl_png_انگ_probes[MZ_MIN(10, level)] | TDEFL_WRITE_ZLIB_سرو);
  لكل (y = 0; y < h; ++y) { tdefl_compress_بفر(pComp, &z, 1, TDEFL_NO_FLUSH); tdefl_compress_بفر(pComp, (mz_uint8*)pImage + (flip ? (h - 1 - y) : y) * bpl, w * انگ_chans, TDEFL_NO_FLUSH); }
  إذا (tdefl_compress_بفر(pComp, عدم, 0, TDEFL_پڄاڻي) != TDEFL_حالت_پورو) { MZ_FREE(pComp); MZ_FREE(ٻاهريون_buf.m_pBuf); أرجع عدم; }
  // write IDAT size
  معلومات_سائيز_3 = ٻاهريون_buf.m_سائيز-معلومات_شروعات;
  (ٻاهريون_buf.m_pBuf+معلومات_شروعات-8)[0] = (mz_uint8)(معلومات_سائيز_3>>24);
  (ٻاهريون_buf.m_pBuf+معلومات_شروعات-8)[1] = (mz_uint8)(معلومات_سائيز_3>>16);
  (ٻاهريون_buf.m_pBuf+معلومات_شروعات-8)[2] = (mz_uint8)(معلومات_سائيز_3>> 8);
  (ٻاهريون_buf.m_pBuf+معلومات_شروعات-8)[3] = (mz_uint8)(معلومات_سائيز_3>> 0);
  // write footer (IDAT CRC-32, followed by IEND chunk)
  إذا (!tdefl_output_بفر_putter("\0\0\0\0\0\0\0\0\x49\x45\x4e\x44\xae\x42\x60\x82", 16, &ٻاهريون_buf)) { *p_Len_ٻاهريون = 0; MZ_FREE(pComp); MZ_FREE(ٻاهريون_buf.m_pBuf); أرجع عدم; }
  c = (mz_uint32)mz_چڪري_جاچ_32(MZ_چڪري_جاچ_32_INIT,ٻاهريون_buf.m_pBuf+معلومات_شروعات-4, معلومات_سائيز_3+4);
  لكل (i=0; i<4; ++i, c<<=8) (ٻاهريون_buf.m_pBuf+ٻاهريون_buf.m_سائيز-16)[i] = (mz_uint8)(c >> 24);
  // compute final size of file, grab compressed data buffer and return
  *p_Len_ٻاهريون = ٻاهريون_buf.m_سائيز;
  MZ_FREE(pComp);
  أرجع ٻاهريون_buf.m_pBuf;
}
#جيڪڏهن_وصف_نه_ٿيل MINIZ_SDL_NOUNUSED
MINIZ_STATIC فراغ *tdefl_write_image_منزل_png_file_اندريون_يادگيري(ثابت فراغ *pImage, صحيح w, صحيح h, صحيح انگ_chans, صحيح bpl, size_t *p_Len_ٻاهريون)
{
  // Level 6 corresponds to TDEFL_DEFAULT_MAX_PROBES or MZ_DEFAULT_LEVEL (but we can't depend on MZ_DEFAULT_LEVEL being available in case the zlib API's where #defined out)
  أرجع tdefl_write_image_منزل_png_file_اندريون_يادگيري_ex(pImage, w, h, انگ_chans, bpl, p_Len_ٻاهريون, 6, MZ_FALSE, عدم, 0, عدم, 0);
}
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل _MSC_VER
#هدايت warning (ڪڍو)
#جيڪڏهن_پورو
#جيڪڏهن_پورو /*#ifndef MINIZ_NO_DEFLATE_APIS*/

// ------------------- .ZIP archive reading

#جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_ARCHIVE_APIS

#جيڪڏهن_وصف_ٿيل MINIZ_NO_STDIO
  #وصف_ڪريو MZ_FILE فراغ *
#وإلا
  #ضمن <stdio.h>
  #ضمن <sys/stat.h>

  #إذا defined(_MSC_VER) || defined(__MINGW64__)
    ساكن FILE *mz_fopen(ثابت حرف *pFilename, ثابت حرف *p_گهڻائي)
    {
      FILE* pFile = عدم;
      fopen_s(&pFile, pFilename, p_گهڻائي);
      أرجع pFile;
    }
    ساكن FILE *mz_freopen(ثابت حرف *p_رستو, ثابت حرف *p_گهڻائي, FILE *p_وهڪرو)
    {
      FILE* pFile = عدم;
      إذا (freopen_s(&pFile, p_رستو, p_گهڻائي, p_وهڪرو))
        أرجع عدم;
      أرجع pFile;
    }
    #جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_وقت
      #ضمن <sys/utime.h>
    #جيڪڏهن_پورو
    #وصف_ڪريو MZ_FILE FILE
    #وصف_ڪريو MZ_FOPEN mz_fopen
    #وصف_ڪريو MZ_FCLOSE fclose
    #وصف_ڪريو MZ_FREAD fread
    #وصف_ڪريو MZ_FWRITE fwrite
    #وصف_ڪريو MZ_FTELL64 _ftelli64
    #وصف_ڪريو MZ_FSEEK64 _fseeki64
    #وصف_ڪريو MZ_FILE_STAT_STRUCT _stat
    #وصف_ڪريو MZ_FILE_STAT _stat
    #وصف_ڪريو MZ_FFLUSH fflush
    #وصف_ڪريو MZ_FREOPEN mz_freopen
    #وصف_ڪريو MZ_DELETE_FILE remove
  #وإلاإذا defined(__MINGW32__)
    #جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_وقت
      #ضمن <sys/utime.h>
    #جيڪڏهن_پورو
    #وصف_ڪريو MZ_FILE FILE
    #وصف_ڪريو MZ_FOPEN(f, m) fopen(f, m)
    #وصف_ڪريو MZ_FCLOSE fclose
    #وصف_ڪريو MZ_FREAD fread
    #وصف_ڪريو MZ_FWRITE fwrite
    #وصف_ڪريو MZ_FTELL64 ftello64
    #وصف_ڪريو MZ_FSEEK64 fseeko64
    #وصف_ڪريو MZ_FILE_STAT_STRUCT _stat
    #وصف_ڪريو MZ_FILE_STAT _stat
    #وصف_ڪريو MZ_FFLUSH fflush
    #وصف_ڪريو MZ_FREOPEN(f, m, s) freopen(f, m, s)
    #وصف_ڪريو MZ_DELETE_FILE remove
  #وإلاإذا defined(__TINYC__)
    #جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_وقت
      #ضمن <sys/utime.h>
    #جيڪڏهن_پورو
    #وصف_ڪريو MZ_FILE FILE
    #وصف_ڪريو MZ_FOPEN(f, m) fopen(f, m)
    #وصف_ڪريو MZ_FCLOSE fclose
    #وصف_ڪريو MZ_FREAD fread
    #وصف_ڪريو MZ_FWRITE fwrite
    #وصف_ڪريو MZ_FTELL64 ftell
    #وصف_ڪريو MZ_FSEEK64 fseek
    #وصف_ڪريو MZ_FILE_STAT_STRUCT stat
    #وصف_ڪريو MZ_FILE_STAT stat
    #وصف_ڪريو MZ_FFLUSH fflush
    #وصف_ڪريو MZ_FREOPEN(f, m, s) freopen(f, m, s)
    #وصف_ڪريو MZ_DELETE_FILE remove
  #وإلاإذا defined(__GNUC__) && LARGEFILE64_ذريعو
    #جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_وقت
      #ضمن <utime.h>
    #جيڪڏهن_پورو
    #وصف_ڪريو MZ_FILE FILE
    #وصف_ڪريو MZ_FOPEN(f, m) fopen64(f, m)
    #وصف_ڪريو MZ_FCLOSE fclose
    #وصف_ڪريو MZ_FREAD fread
    #وصف_ڪريو MZ_FWRITE fwrite
    #وصف_ڪريو MZ_FTELL64 ftello64
    #وصف_ڪريو MZ_FSEEK64 fseeko64
    #وصف_ڪريو MZ_FILE_STAT_STRUCT stat64
    #وصف_ڪريو MZ_FILE_STAT stat64
    #وصف_ڪريو MZ_FFLUSH fflush
    #وصف_ڪريو MZ_FREOPEN(p, m, s) freopen64(p, m, s)
    #وصف_ڪريو MZ_DELETE_FILE remove
  #وإلا
    #جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_وقت
      #ضمن <utime.h>
    #جيڪڏهن_پورو
    #وصف_ڪريو MZ_FILE FILE
    #وصف_ڪريو MZ_FOPEN(f, m) fopen(f, m)
    #وصف_ڪريو MZ_FCLOSE fclose
    #وصف_ڪريو MZ_FREAD fread
    #وصف_ڪريو MZ_FWRITE fwrite
    #وصف_ڪريو MZ_FTELL64 ftello
    #وصف_ڪريو MZ_FSEEK64 fseeko
    #وصف_ڪريو MZ_FILE_STAT_STRUCT stat
    #وصف_ڪريو MZ_FILE_STAT stat
    #وصف_ڪريو MZ_FFLUSH fflush
    #وصف_ڪريو MZ_FREOPEN(f, m, s) freopen(f, m, s)
    #وصف_ڪريو MZ_DELETE_FILE remove
  #جيڪڏهن_پورو // #ifdef _MSC_VER
#جيڪڏهن_پورو // #ifdef MINIZ_NO_STDIO

#وصف_ڪريو MZ_TOLOWER(c) ((((c) >= 'A') && ((c) <= 'Z')) ? ((c) - 'A' + 'a') : (c))

// Various ZIP archive enums. To completely avoid cross platform compiler alignment and platform endian issues, miniz.c doesn't use structs for any of this stuff.
تعداد
{
  // ZIP archive identifiers and record sizes
  MZ_ZIP_پڇاڙي_جو_CENTRAL_DIR_سرو_SIG = 0x06054b50, MZ_ZIP_CENTRAL_DIR_سرو_SIG = 0x02014b50, MZ_ZIP_LOCAL_DIR_سرو_SIG = 0x04034b50,
  MZ_ZIP_LOCAL_DIR_سرو_سائيز = 30, MZ_ZIP_CENTRAL_DIR_سرو_سائيز = 46, MZ_ZIP_پڇاڙي_جو_CENTRAL_DIR_سرو_سائيز = 22,
  // Central directory header record offsets
  MZ_ZIP_CDH_SIG_OFS = 0, MZ_ZIP_CDH_نسخو_MADE_BY_OFS = 4, MZ_ZIP_CDH_نسخو_NEEDED_OFS = 6, MZ_ZIP_CDH_ٻٽو_انگ_FLAG_OFS = 8,
  MZ_ZIP_CDH_طريقو_OFS = 10, MZ_ZIP_CDH_FILE_وقت_OFS = 12, MZ_ZIP_CDH_FILE_DATE_OFS = 14, MZ_ZIP_CDH_چڪري_جاچ_32_OFS = 16,
  MZ_ZIP_CDH_COMPRESSED_سائيز_OFS = 20, MZ_ZIP_CDH_DECOMPRESSED_سائيز_OFS = 24, MZ_ZIP_CDH_FILENAME_LEN_OFS = 28, MZ_ZIP_CDH_EXTRA_LEN_OFS = 30,
  MZ_ZIP_CDH_COMMENT_LEN_OFS = 32, MZ_ZIP_CDH_DISK_شروعات_OFS = 34, MZ_ZIP_CDH_اندروني_ATTR_OFS = 36, MZ_ZIP_CDH_EXTERNAL_ATTR_OFS = 38, MZ_ZIP_CDH_LOCAL_سرو_OFS = 42,
  // Local directory header offsets
  MZ_ZIP_LDH_SIG_OFS = 0, MZ_ZIP_LDH_نسخو_NEEDED_OFS = 4, MZ_ZIP_LDH_ٻٽو_انگ_FLAG_OFS = 6, MZ_ZIP_LDH_طريقو_OFS = 8, MZ_ZIP_LDH_FILE_وقت_OFS = 10,
  MZ_ZIP_LDH_FILE_DATE_OFS = 12, MZ_ZIP_LDH_چڪري_جاچ_32_OFS = 14, MZ_ZIP_LDH_COMPRESSED_سائيز_OFS = 18, MZ_ZIP_LDH_DECOMPRESSED_سائيز_OFS = 22,
  MZ_ZIP_LDH_FILENAME_LEN_OFS = 26, MZ_ZIP_LDH_EXTRA_LEN_OFS = 28,
  // End of central directory offsets
  MZ_ZIP_ECDH_SIG_OFS = 0, MZ_ZIP_ECDH_انگ_THIS_DISK_OFS = 4, MZ_ZIP_ECDH_انگ_DISK_CDIR_OFS = 6, MZ_ZIP_ECDH_CDIR_انگ_ENTRIES_ON_DISK_OFS = 8,
  MZ_ZIP_ECDH_CDIR_ڪل_ENTRIES_OFS = 10, MZ_ZIP_ECDH_CDIR_سائيز_OFS = 12, MZ_ZIP_ECDH_CDIR_OFS_OFS = 16, MZ_ZIP_ECDH_COMMENT_سائيز_OFS = 20,
};

تعريفنوع بنية
{
  فراغ *m_p;
  size_t m_سائيز, m_صلاحيت;
  mz_uint m_element_سائيز;
} mz_zip_array;

بنية mz_zip_اندروني_state_ٽيگ
{
  mz_zip_array m_central_dir;
  mz_zip_array m_central_dir_offsets;
  mz_zip_array m_sorted_central_dir_offsets;
  MZ_FILE *m_pFile;
  فراغ *m_pMem;
  size_t m_mem_سائيز;
  size_t m_mem_صلاحيت;
};

#وصف_ڪريو MZ_ZIP_ARRAY_سيٽ_ELEMENT_سائيز(array_ptr, element_سائيز) (array_ptr)->m_element_سائيز = element_سائيز
#وصف_ڪريو MZ_ZIP_ARRAY_ELEMENT(array_ptr, element_type, اشاريو) ((element_type *)((array_ptr)->m_p))[اشاريو]

ساكن MZ_FORCEINLINE فراغ mz_zip_array_clear(mz_zip_archive *pZip, mz_zip_array *pArray)
{
  pZip->m_pFree(pZip->m_pAlloc_opaque, pArray->m_p);
  memset(pArray, 0, حجم(mz_zip_array));
}

ساكن mz_bool mz_zip_array_ensure_صلاحيت(mz_zip_archive *pZip, mz_zip_array *pArray, size_t min_new_صلاحيت, mz_uint growing)
{
  فراغ *pNew_p; size_t new_صلاحيت = min_new_صلاحيت; MZ_ASSERT(pArray->m_element_سائيز); إذا (pArray->m_صلاحيت >= min_new_صلاحيت) أرجع MZ_TRUE;
  إذا (growing) { new_صلاحيت = MZ_MAX(1, pArray->m_صلاحيت); طالما (new_صلاحيت < min_new_صلاحيت) new_صلاحيت *= 2; }
  إذا (عدم == (pNew_p = pZip->m_pRealloc(pZip->m_pAlloc_opaque, pArray->m_p, pArray->m_element_سائيز, new_صلاحيت))) أرجع MZ_FALSE;
  pArray->m_p = pNew_p; pArray->m_صلاحيت = new_صلاحيت;
  أرجع MZ_TRUE;
}

ساكن MZ_FORCEINLINE mz_bool mz_zip_array_reserve(mz_zip_archive *pZip, mz_zip_array *pArray, size_t new_صلاحيت, mz_uint growing)
{
  إذا (new_صلاحيت > pArray->m_صلاحيت) { إذا (!mz_zip_array_ensure_صلاحيت(pZip, pArray, new_صلاحيت, growing)) أرجع MZ_FALSE; }
  أرجع MZ_TRUE;
}

ساكن MZ_FORCEINLINE mz_bool mz_zip_array_resize(mz_zip_archive *pZip, mz_zip_array *pArray, size_t new_سائيز, mz_uint growing)
{
  إذا (new_سائيز > pArray->m_صلاحيت) { إذا (!mz_zip_array_ensure_صلاحيت(pZip, pArray, new_سائيز, growing)) أرجع MZ_FALSE; }
  pArray->m_سائيز = new_سائيز;
  أرجع MZ_TRUE;
}

ساكن MZ_FORCEINLINE mz_bool mz_zip_array_ensure_گنجائش(mz_zip_archive *pZip, mz_zip_array *pArray, size_t n)
{
  أرجع mz_zip_array_reserve(pZip, pArray, pArray->m_سائيز + n, MZ_TRUE);
}

ساكن MZ_FORCEINLINE mz_bool mz_zip_array_ڌڪو_پٺ(mz_zip_archive *pZip, mz_zip_array *pArray, ثابت فراغ *pElements, size_t n)
{
  size_t orig_سائيز = pArray->m_سائيز; إذا (!mz_zip_array_resize(pZip, pArray, orig_سائيز + n, MZ_TRUE)) أرجع MZ_FALSE;
  يادگيري_نقل((mz_uint8*)pArray->m_p + orig_سائيز * pArray->m_element_سائيز, pElements, n * pArray->m_element_سائيز);
  أرجع MZ_TRUE;
}

#جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_وقت
ساكن وقت_t mz_zip_dos_منزل_وقت_t(صحيح dos_وقت, صحيح dos_date)
{
  بنية tm tm;
  memset(&tm, 0, حجم(tm)); tm.tm_isdst = -1;
  tm.tm_year = ((dos_date >> 9) & 127) + 1980 - 1900; tm.tm_mon = ((dos_date >> 5) & 15) - 1; tm.tm_mday = dos_date & 31;
  tm.tm_hour = (dos_وقت >> 11) & 31; tm.tm_min = (dos_وقت >> 5) & 63; tm.tm_sec = (dos_وقت << 1) & 62;
  أرجع mktime(&tm);
}

ساكن فراغ mz_zip_وقت_منزل_dos_وقت(وقت_t وقت, mz_uint16 *p_DOS_وقت, mz_uint16 *pDOS_date)
{
#جيڪڏهن_وصف_ٿيل _MSC_VER
  بنية tm tm_struct;
  بنية tm *tm = &tm_struct;
  errno_t err = localtime_s(tm, &وقت);
  إذا (err)
  {
    *pDOS_date = 0; *p_DOS_وقت = 0;
    أرجع;
  }
#وإلا
  بنية tm *tm = localtime(&وقت);
#جيڪڏهن_پورو
  *p_DOS_وقت = (mz_uint16)(((tm->tm_hour) << 11) + ((tm->tm_min) << 5) + ((tm->tm_sec) >> 1));
  *pDOS_date = (mz_uint16)(((tm->tm_year + 1900 - 1980) << 9) + ((tm->tm_mon + 1) << 5) + tm->tm_mday);
}
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_STDIO
ساكن mz_bool mz_zip_get_file_modified_وقت(ثابت حرف *pFilename, mz_uint16 *p_DOS_وقت, mz_uint16 *pDOS_date)
{
#جيڪڏهن_وصف_ٿيل MINIZ_NO_وقت
  (فراغ)pFilename; *pDOS_date = *p_DOS_وقت = 0;
#وإلا
  بنية MZ_FILE_STAT_STRUCT file_stat;
  // On Linux with x86 glibc, this call will fail on large files (>= 0x80000000 bytes) unless you compiled with _LARGEFILE64_SOURCE. Argh.
  إذا (MZ_FILE_STAT(pFilename, &file_stat) != 0)
    أرجع MZ_FALSE;
  mz_zip_وقت_منزل_dos_وقت(file_stat.st_mtime, p_DOS_وقت, pDOS_date);
#جيڪڏهن_پورو // #ifdef MINIZ_NO_TIME
  أرجع MZ_TRUE;
}

#جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_وقت
ساكن mz_bool mz_zip_سيٽ_file_times(ثابت حرف *pFilename, وقت_t access_وقت, وقت_t modified_وقت)
{
  بنية utimbuf t; t.actime = access_وقت; t.modtime = modified_وقت;
  أرجع !utime(pFilename, &t);
}
#جيڪڏهن_پورو // #ifndef MINIZ_NO_TIME
#جيڪڏهن_پورو // #ifndef MINIZ_NO_STDIO

ساكن mz_bool mz_zip_reader_init_اندروني(mz_zip_archive *pZip, mz_uint32 flags)
{
  (فراغ)flags;
  إذا ((!pZip) || (pZip->m_pState) || (pZip->m_zip_گهڻائي != MZ_ZIP_گهڻائي_INVALID))
    أرجع MZ_FALSE;

  إذا (!pZip->m_pAlloc) pZip->m_pAlloc = def_alloc_func;
  إذا (!pZip->m_pFree) pZip->m_pFree = def_free_func;
  إذا (!pZip->m_pRealloc) pZip->m_pRealloc = def_realloc_func;

  pZip->m_zip_گهڻائي = MZ_ZIP_گهڻائي_READING;
  pZip->m_archive_سائيز = 0;
  pZip->m_central_directory_file_ofs = 0;
  pZip->m_ڪل_files = 0;

  إذا (عدم == (pZip->m_pState = (mz_zip_اندروني_state *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, حجم(mz_zip_اندروني_state))))
    أرجع MZ_FALSE;
  memset(pZip->m_pState, 0, حجم(mz_zip_اندروني_state));
  MZ_ZIP_ARRAY_سيٽ_ELEMENT_سائيز(&pZip->m_pState->m_central_dir, حجم(mz_uint8));
  MZ_ZIP_ARRAY_سيٽ_ELEMENT_سائيز(&pZip->m_pState->m_central_dir_offsets, حجم(mz_uint32));
  MZ_ZIP_ARRAY_سيٽ_ELEMENT_سائيز(&pZip->m_pState->m_sorted_central_dir_offsets, حجم(mz_uint32));
  أرجع MZ_TRUE;
}

ساكن MZ_FORCEINLINE mz_bool mz_zip_reader_filename_less(ثابت mz_zip_array *pCentral_dir_array, ثابت mz_zip_array *pCentral_dir_offsets, mz_uint l_اشاريو, mz_uint r_اشاريو)
{
  ثابت mz_uint8 *pL = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, l_اشاريو)), *pE;
  ثابت mz_uint8 *pR = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, r_اشاريو));
  mz_uint l_len = MZ_READ_LE16(pL + MZ_ZIP_CDH_FILENAME_LEN_OFS), r_len = MZ_READ_LE16(pR + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  mz_uint8 l = 0, r = 0;
  pL += MZ_ZIP_CENTRAL_DIR_سرو_سائيز; pR += MZ_ZIP_CENTRAL_DIR_سرو_سائيز;
  pE = pL + MZ_MIN(l_len, r_len);
  طالما (pL < pE)
  {
    إذا ((l = MZ_TOLOWER(*pL)) != (r = MZ_TOLOWER(*pR)))
      اكسر;
    pL++; pR++;
  }
  أرجع (pL == pE) ? (l_len < r_len) : (l < r);
}

#وصف_ڪريو MZ_مٽا_سٽا_UINT32(a, b) افعل { mz_uint32 t = a; a = b; b = t; } MZ_MACRO_پڇاڙي

// Heap sort of lowercased filenames, used to help accelerate plain central directory searches by mz_zip_reader_locate_file(). (Could also use qsort(), but it could allocate memory.)
ساكن فراغ mz_zip_reader_ترتيب_ڏيو_central_dir_offsets_by_filename(mz_zip_archive *pZip)
{
  mz_zip_اندروني_state *pState = pZip->m_pState;
  ثابت mz_zip_array *pCentral_dir_offsets = &pState->m_central_dir_offsets;
  ثابت mz_zip_array *pCentral_dir = &pState->m_central_dir;
  mz_uint32 *pIndices = &MZ_ZIP_ARRAY_ELEMENT(&pState->m_sorted_central_dir_offsets, mz_uint32, 0);
  ثابت صحيح سائيز = pZip->m_ڪل_files;
  صحيح شروعات = (سائيز - 2) >> 1, پڇاڙي;
  طالما (شروعات >= 0)
  {
    صحيح ٻار, پاڙ = شروعات;
    لكل ( ; ; )
    {
      إذا ((ٻار = (پاڙ << 1) + 1) >= سائيز)
        اكسر;
      ٻار += (((ٻار + 1) < سائيز) && (mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[ٻار], pIndices[ٻار + 1])));
      إذا (!mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[پاڙ], pIndices[ٻار]))
        اكسر;
      MZ_مٽا_سٽا_UINT32(pIndices[پاڙ], pIndices[ٻار]); پاڙ = ٻار;
    }
    شروعات--;
  }

  پڇاڙي = سائيز - 1;
  طالما (پڇاڙي > 0)
  {
    صحيح ٻار, پاڙ = 0;
    MZ_مٽا_سٽا_UINT32(pIndices[پڇاڙي], pIndices[0]);
    لكل ( ; ; )
    {
      إذا ((ٻار = (پاڙ << 1) + 1) >= پڇاڙي)
        اكسر;
      ٻار += (((ٻار + 1) < پڇاڙي) && mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[ٻار], pIndices[ٻار + 1]));
      إذا (!mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[پاڙ], pIndices[ٻار]))
        اكسر;
      MZ_مٽا_سٽا_UINT32(pIndices[پاڙ], pIndices[ٻار]); پاڙ = ٻار;
    }
    پڇاڙي--;
  }
}

ساكن mz_bool mz_zip_reader_read_central_dir(mz_zip_archive *pZip, mz_uint32 flags)
{
  mz_uint cdir_سائيز, انگ_this_disk, cdir_disk_اشاريو;
  mz_uint64 cdir_ofs;
  mz_int64 cur_file_ofs;
  ثابت mz_uint8 *p;
  mz_uint32 buf_u32[4096 / حجم(mz_uint32)]; mz_uint8 *pBuf = (mz_uint8 *)buf_u32;
  mz_bool ترتيب_ڏيو_central_dir = ((flags & MZ_ZIP_FLAG_DO_NOT_ترتيب_ڏيو_CENTRAL_DIRECTORY) == 0);
  // Basic sanity checks - reject files which are too small, and check the first 4 bytes of the file to make sure a local header is there.
  إذا (pZip->m_archive_سائيز < MZ_ZIP_پڇاڙي_جو_CENTRAL_DIR_سرو_سائيز)
    أرجع MZ_FALSE;
  // Find the end of central directory record by scanning the file from the end towards the beginning.
  cur_file_ofs = MZ_MAX((mz_int64)pZip->m_archive_سائيز - (mz_int64)حجم(buf_u32), 0);
  لكل ( ; ; )
  {
    صحيح i, n = (صحيح)MZ_MIN(حجم(buf_u32), pZip->m_archive_سائيز - cur_file_ofs);
    إذا (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, n) != (mz_uint)n)
      أرجع MZ_FALSE;
    لكل (i = n - 4; i >= 0; --i)
      إذا (MZ_READ_LE32(pBuf + i) == MZ_ZIP_پڇاڙي_جو_CENTRAL_DIR_سرو_SIG)
        اكسر;
    إذا (i >= 0)
    {
      cur_file_ofs += i;
      اكسر;
    }
    إذا ((!cur_file_ofs) || ((pZip->m_archive_سائيز - cur_file_ofs) >= (0xFFFF + MZ_ZIP_پڇاڙي_جو_CENTRAL_DIR_سرو_سائيز)))
      أرجع MZ_FALSE;
    cur_file_ofs = MZ_MAX(cur_file_ofs - (حجم(buf_u32) - 3), 0);
  }
  // Read and verify the end of central directory record.
  إذا (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, MZ_ZIP_پڇاڙي_جو_CENTRAL_DIR_سرو_سائيز) != MZ_ZIP_پڇاڙي_جو_CENTRAL_DIR_سرو_سائيز)
    أرجع MZ_FALSE;
  إذا ((MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_SIG_OFS) != MZ_ZIP_پڇاڙي_جو_CENTRAL_DIR_سرو_SIG) ||
      ((pZip->m_ڪل_files = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_CDIR_ڪل_ENTRIES_OFS)) != MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_CDIR_انگ_ENTRIES_ON_DISK_OFS)))
    أرجع MZ_FALSE;

  انگ_this_disk = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_انگ_THIS_DISK_OFS);
  cdir_disk_اشاريو = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_انگ_DISK_CDIR_OFS);
  إذا (((انگ_this_disk | cdir_disk_اشاريو) != 0) && ((انگ_this_disk != 1) || (cdir_disk_اشاريو != 1)))
    أرجع MZ_FALSE;

  إذا ((cdir_سائيز = MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_CDIR_سائيز_OFS)) < pZip->m_ڪل_files * MZ_ZIP_CENTRAL_DIR_سرو_سائيز)
    أرجع MZ_FALSE;

  cdir_ofs = MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_CDIR_OFS_OFS);
  إذا ((cdir_ofs + (mz_uint64)cdir_سائيز) > pZip->m_archive_سائيز)
    أرجع MZ_FALSE;

  pZip->m_central_directory_file_ofs = cdir_ofs;

  إذا (pZip->m_ڪل_files)
  {
     mz_uint i, n;

    // Read the entire central directory into a heap block, and allocate another heap block to hold the unsorted central dir file record offsets, and another to hold the sorted indices.
    إذا ((!mz_zip_array_resize(pZip, &pZip->m_pState->m_central_dir, cdir_سائيز, MZ_FALSE)) ||
        (!mz_zip_array_resize(pZip, &pZip->m_pState->m_central_dir_offsets, pZip->m_ڪل_files, MZ_FALSE)))
      أرجع MZ_FALSE;

    إذا (ترتيب_ڏيو_central_dir)
    {
      إذا (!mz_zip_array_resize(pZip, &pZip->m_pState->m_sorted_central_dir_offsets, pZip->m_ڪل_files, MZ_FALSE))
        أرجع MZ_FALSE;
    }

    إذا (pZip->m_pRead(pZip->m_pIO_opaque, cdir_ofs, pZip->m_pState->m_central_dir.m_p, cdir_سائيز) != cdir_سائيز)
      أرجع MZ_FALSE;

    // Now create an index into the central directory file records, do some basic sanity checking on each record, and check for zip64 entries (which are not yet supported).
    p = (ثابت mz_uint8 *)pZip->m_pState->m_central_dir.m_p;
    لكل (n = cdir_سائيز, i = 0; i < pZip->m_ڪل_files; ++i)
    {
      mz_uint ڪل_سرو_سائيز, comp_سائيز, decomp_سائيز, disk_اشاريو;
      إذا ((n < MZ_ZIP_CENTRAL_DIR_سرو_سائيز) || (MZ_READ_LE32(p) != MZ_ZIP_CENTRAL_DIR_سرو_SIG))
        أرجع MZ_FALSE;
      MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, i) = (mz_uint32)(p - (ثابت mz_uint8 *)pZip->m_pState->m_central_dir.m_p);
      إذا (ترتيب_ڏيو_central_dir)
        MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_sorted_central_dir_offsets, mz_uint32, i) = i;
      comp_سائيز = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_سائيز_OFS);
      decomp_سائيز = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_سائيز_OFS);
      إذا (((!MZ_READ_LE32(p + MZ_ZIP_CDH_طريقو_OFS)) && (decomp_سائيز != comp_سائيز)) || (decomp_سائيز && !comp_سائيز) || (decomp_سائيز == 0xFFFFFFFF) || (comp_سائيز == 0xFFFFFFFF))
        أرجع MZ_FALSE;
      disk_اشاريو = MZ_READ_LE16(p + MZ_ZIP_CDH_DISK_شروعات_OFS);
      إذا ((disk_اشاريو != انگ_this_disk) && (disk_اشاريو != 1))
        أرجع MZ_FALSE;
      إذا (((mz_uint64)MZ_READ_LE32(p + MZ_ZIP_CDH_LOCAL_سرو_OFS) + MZ_ZIP_LOCAL_DIR_سرو_سائيز + comp_سائيز) > pZip->m_archive_سائيز)
        أرجع MZ_FALSE;
      إذا ((ڪل_سرو_سائيز = MZ_ZIP_CENTRAL_DIR_سرو_سائيز + MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_EXTRA_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_COMMENT_LEN_OFS)) > n)
        أرجع MZ_FALSE;
      n -= ڪل_سرو_سائيز; p += ڪل_سرو_سائيز;
    }
  }

  إذا (ترتيب_ڏيو_central_dir)
    mz_zip_reader_ترتيب_ڏيو_central_dir_offsets_by_filename(pZip);

  أرجع MZ_TRUE;
}

mz_bool mz_zip_reader_init(mz_zip_archive *pZip, mz_uint64 سائيز, mz_uint32 flags)
{
  إذا ((!pZip) || (!pZip->m_pRead))
    أرجع MZ_FALSE;
  إذا (!mz_zip_reader_init_اندروني(pZip, flags))
    أرجع MZ_FALSE;
  pZip->m_archive_سائيز = سائيز;
  إذا (!mz_zip_reader_read_central_dir(pZip, flags))
  {
    mz_zip_reader_پڇاڙي(pZip);
    أرجع MZ_FALSE;
  }
  أرجع MZ_TRUE;
}

ساكن size_t mz_zip_mem_read_func(فراغ *pOpaque, mz_uint64 file_ofs, فراغ *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  size_t s = (file_ofs >= pZip->m_archive_سائيز) ? 0 : (size_t)MZ_MIN(pZip->m_archive_سائيز - file_ofs, n);
  يادگيري_نقل(pBuf, (ثابت mz_uint8 *)pZip->m_pState->m_pMem + file_ofs, s);
  أرجع s;
}

mz_bool mz_zip_reader_init_mem(mz_zip_archive *pZip, ثابت فراغ *pMem, size_t سائيز, mz_uint32 flags)
{
  إذا (!mz_zip_reader_init_اندروني(pZip, flags))
    أرجع MZ_FALSE;
  pZip->m_archive_سائيز = سائيز;
  pZip->m_pRead = mz_zip_mem_read_func;
  pZip->m_pIO_opaque = pZip;
#جيڪڏهن_وصف_ٿيل __cplusplus
  pZip->m_pState->m_pMem = const_cast<فراغ *>(pMem);
#وإلا
  pZip->m_pState->m_pMem = (فراغ *)pMem;
#جيڪڏهن_پورو
  pZip->m_pState->m_mem_سائيز = سائيز;
  إذا (!mz_zip_reader_read_central_dir(pZip, flags))
  {
    mz_zip_reader_پڇاڙي(pZip);
    أرجع MZ_FALSE;
  }
  أرجع MZ_TRUE;
}

#جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_STDIO
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
  mz_uint64 file_سائيز;
  MZ_FILE *pFile = MZ_FOPEN(pFilename, "rb");
  إذا (!pFile)
    أرجع MZ_FALSE;
  إذا (MZ_FSEEK64(pFile, 0, SEEK_END))
  {
    MZ_FCLOSE(pFile);
    أرجع MZ_FALSE;
  }
  file_سائيز = MZ_FTELL64(pFile);
  إذا (!mz_zip_reader_init_اندروني(pZip, flags))
  {
    MZ_FCLOSE(pFile);
    أرجع MZ_FALSE;
  }
  pZip->m_pRead = mz_zip_file_read_func;
  pZip->m_pIO_opaque = pZip;
  pZip->m_pState->m_pFile = pFile;
  pZip->m_archive_سائيز = file_سائيز;
  إذا (!mz_zip_reader_read_central_dir(pZip, flags))
  {
    mz_zip_reader_پڇاڙي(pZip);
    أرجع MZ_FALSE;
  }
  أرجع MZ_TRUE;
}
#جيڪڏهن_پورو // #ifndef MINIZ_NO_STDIO

mz_uint mz_zip_reader_get_انگ_files(mz_zip_archive *pZip)
{
  أرجع pZip ? pZip->m_ڪل_files : 0;
}

ساكن MZ_FORCEINLINE ثابت mz_uint8 *mz_zip_reader_get_cdh(mz_zip_archive *pZip, mz_uint file_اشاريو)
{
  إذا ((!pZip) || (!pZip->m_pState) || (file_اشاريو >= pZip->m_ڪل_files) || (pZip->m_zip_گهڻائي != MZ_ZIP_گهڻائي_READING))
    أرجع عدم;
  أرجع &MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_اشاريو));
}

mz_bool mz_zip_reader_is_file_encrypted(mz_zip_archive *pZip, mz_uint file_اشاريو)
{
  mz_uint m_ٻٽو_انگ_flag;
  ثابت mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_اشاريو);
  إذا (!p)
    أرجع MZ_FALSE;
  m_ٻٽو_انگ_flag = MZ_READ_LE16(p + MZ_ZIP_CDH_ٻٽو_انگ_FLAG_OFS);
  أرجع (m_ٻٽو_انگ_flag & 1);
}

mz_bool mz_zip_reader_is_file_a_directory(mz_zip_archive *pZip, mz_uint file_اشاريو)
{
  mz_uint filename_len, external_attr;
  ثابت mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_اشاريو);
  إذا (!p)
    أرجع MZ_FALSE;

  // First see if the filename ends with a '/' character.
  filename_len = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  إذا (filename_len)
  {
    إذا (*(p + MZ_ZIP_CENTRAL_DIR_سرو_سائيز + filename_len - 1) == '/')
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

mz_bool mz_zip_reader_file_stat(mz_zip_archive *pZip, mz_uint file_اشاريو, mz_zip_archive_file_stat *pStat)
{
  mz_uint n;
  ثابت mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_اشاريو);
  إذا ((!p) || (!pStat))
    أرجع MZ_FALSE;

  // Unpack the central directory record.
  pStat->m_file_اشاريو = file_اشاريو;
  pStat->m_central_dir_ofs = MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_اشاريو);
  pStat->m_نسخو_made_by = MZ_READ_LE16(p + MZ_ZIP_CDH_نسخو_MADE_BY_OFS);
  pStat->m_نسخو_needed = MZ_READ_LE16(p + MZ_ZIP_CDH_نسخو_NEEDED_OFS);
  pStat->m_ٻٽو_انگ_flag = MZ_READ_LE16(p + MZ_ZIP_CDH_ٻٽو_انگ_FLAG_OFS);
  pStat->m_طريقو = MZ_READ_LE16(p + MZ_ZIP_CDH_طريقو_OFS);
#جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_وقت
  pStat->m_وقت = mz_zip_dos_منزل_وقت_t(MZ_READ_LE16(p + MZ_ZIP_CDH_FILE_وقت_OFS), MZ_READ_LE16(p + MZ_ZIP_CDH_FILE_DATE_OFS));
#جيڪڏهن_پورو
  pStat->m_چڪري_جاچ_32 = MZ_READ_LE32(p + MZ_ZIP_CDH_چڪري_جاچ_32_OFS);
  pStat->m_comp_سائيز = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_سائيز_OFS);
  pStat->m_uncomp_سائيز = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_سائيز_OFS);
  pStat->m_اندروني_attr = MZ_READ_LE16(p + MZ_ZIP_CDH_اندروني_ATTR_OFS);
  pStat->m_external_attr = MZ_READ_LE32(p + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS);
  pStat->m_local_سرو_ofs = MZ_READ_LE32(p + MZ_ZIP_CDH_LOCAL_سرو_OFS);

  // Copy as much of the filename and comment as possible.
  n = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS); n = MZ_MIN(n, MZ_ZIP_MAX_ARCHIVE_FILENAME_سائيز - 1);
  يادگيري_نقل(pStat->m_filename, p + MZ_ZIP_CENTRAL_DIR_سرو_سائيز, n); pStat->m_filename[n] = '\0';

  n = MZ_READ_LE16(p + MZ_ZIP_CDH_COMMENT_LEN_OFS); n = MZ_MIN(n, MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_سائيز - 1);
  pStat->m_comment_سائيز = n;
  يادگيري_نقل(pStat->m_comment, p + MZ_ZIP_CENTRAL_DIR_سرو_سائيز + MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_EXTRA_LEN_OFS), n); pStat->m_comment[n] = '\0';

  أرجع MZ_TRUE;
}

mz_uint mz_zip_reader_get_filename(mz_zip_archive *pZip, mz_uint file_اشاريو, حرف *pFilename, mz_uint filename_buf_سائيز)
{
  mz_uint n;
  ثابت mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_اشاريو);
  إذا (!p) { إذا (filename_buf_سائيز) pFilename[0] = '\0'; أرجع 0; }
  n = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  إذا (filename_buf_سائيز)
  {
    n = MZ_MIN(n, filename_buf_سائيز - 1);
    يادگيري_نقل(pFilename, p + MZ_ZIP_CENTRAL_DIR_سرو_سائيز, n);
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

ساكن MZ_FORCEINLINE صحيح mz_zip_reader_filename_compare(ثابت mz_zip_array *pCentral_dir_array, ثابت mz_zip_array *pCentral_dir_offsets, mz_uint l_اشاريو, ثابت حرف *pR, mz_uint r_len)
{
  ثابت mz_uint8 *pL = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, l_اشاريو)), *pE;
  mz_uint l_len = MZ_READ_LE16(pL + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  mz_uint8 l = 0, r = 0;
  pL += MZ_ZIP_CENTRAL_DIR_سرو_سائيز;
  pE = pL + MZ_MIN(l_len, r_len);
  طالما (pL < pE)
  {
    إذا ((l = MZ_TOLOWER(*pL)) != (r = MZ_TOLOWER(*pR)))
      اكسر;
    pL++; pR++;
  }
  أرجع (pL == pE) ? (صحيح)(l_len - r_len) : (l - r);
}

ساكن صحيح mz_zip_reader_locate_file_ٻٽو_ڳولا(mz_zip_archive *pZip, ثابت حرف *pFilename)
{
  mz_zip_اندروني_state *pState = pZip->m_pState;
  ثابت mz_zip_array *pCentral_dir_offsets = &pState->m_central_dir_offsets;
  ثابت mz_zip_array *pCentral_dir = &pState->m_central_dir;
  mz_uint32 *pIndices = &MZ_ZIP_ARRAY_ELEMENT(&pState->m_sorted_central_dir_offsets, mz_uint32, 0);
  ثابت صحيح سائيز = pZip->m_ڪل_files;
  ثابت mz_uint filename_len = (mz_uint)لڙي_ڊيگهه(pFilename);
  صحيح l = 0, h = سائيز - 1;
  طالما (l <= h)
  {
    صحيح m = (l + h) >> 1, file_اشاريو = pIndices[m], comp = mz_zip_reader_filename_compare(pCentral_dir, pCentral_dir_offsets, file_اشاريو, pFilename, filename_len);
    إذا (!comp)
      أرجع file_اشاريو;
    وإلا إذا (comp < 0)
      l = m + 1;
    وإلا
      h = m - 1;
  }
  أرجع -1;
}

صحيح mz_zip_reader_locate_file(mz_zip_archive *pZip, ثابت حرف *pName, ثابت حرف *pComment, mz_uint flags)
{
  mz_uint file_اشاريو; size_t name_len, comment_len;
  إذا ((!pZip) || (!pZip->m_pState) || (!pName) || (pZip->m_zip_گهڻائي != MZ_ZIP_گهڻائي_READING))
    أرجع -1;
  إذا (((flags & (MZ_ZIP_FLAG_IGNORE_رستو | MZ_ZIP_FLAG_CASE_SENSITIVE)) == 0) && (!pComment) && (pZip->m_pState->m_sorted_central_dir_offsets.m_سائيز))
    أرجع mz_zip_reader_locate_file_ٻٽو_ڳولا(pZip, pName);
  name_len = لڙي_ڊيگهه(pName); إذا (name_len > 0xFFFF) أرجع -1;
  comment_len = pComment ? لڙي_ڊيگهه(pComment) : 0; إذا (comment_len > 0xFFFF) أرجع -1;
  لكل (file_اشاريو = 0; file_اشاريو < pZip->m_ڪل_files; file_اشاريو++)
  {
    ثابت mz_uint8 *p_سرو = &MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_اشاريو));
    mz_uint filename_len = MZ_READ_LE16(p_سرو + MZ_ZIP_CDH_FILENAME_LEN_OFS);
    ثابت حرف *pFilename = (ثابت حرف *)p_سرو + MZ_ZIP_CENTRAL_DIR_سرو_سائيز;
    إذا (filename_len < name_len)
      استمر;
    إذا (comment_len)
    {
      mz_uint file_extra_len = MZ_READ_LE16(p_سرو + MZ_ZIP_CDH_EXTRA_LEN_OFS), file_comment_len = MZ_READ_LE16(p_سرو + MZ_ZIP_CDH_COMMENT_LEN_OFS);
      ثابت حرف *pFile_comment = pFilename + filename_len + file_extra_len;
      إذا ((file_comment_len != comment_len) || (!mz_zip_reader_string_equal(pComment, pFile_comment, file_comment_len, flags)))
        استمر;
    }
    إذا ((flags & MZ_ZIP_FLAG_IGNORE_رستو) && (filename_len))
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
      أرجع file_اشاريو;
  }
  أرجع -1;
}

mz_bool mz_zip_reader_ڪڍو_منزل_mem_no_alloc(mz_zip_archive *pZip, mz_uint file_اشاريو, فراغ *pBuf, size_t buf_سائيز_2, mz_uint flags, فراغ *pUser_read_buf, size_t user_read_buf_سائيز)
{
  صحيح حالت = TINFL_حالت_پورو;
  mz_uint64 needed_سائيز, cur_file_ofs, comp_بچيل, ٻاهريون_buf_ofs = 0, read_buf_سائيز, read_buf_ofs = 0, read_buf_avail;
  mz_zip_archive_file_stat file_stat;
  فراغ *pRead_buf;
  mz_uint32 local_سرو_u32[(MZ_ZIP_LOCAL_DIR_سرو_سائيز + حجم(mz_uint32) - 1) / حجم(mz_uint32)]; mz_uint8 *p_Local_سرو = (mz_uint8 *)local_سرو_u32;
  tinfl_decompressor inflator;

  إذا ((buf_سائيز_2) && (!pBuf))
    أرجع MZ_FALSE;

  إذا (!mz_zip_reader_file_stat(pZip, file_اشاريو, &file_stat))
    أرجع MZ_FALSE;

  // Empty file, or a directory (but not always a directory - I've seen odd zips with directories that have compressed data which inflates to 0 bytes)
  إذا (!file_stat.m_comp_سائيز)
    أرجع MZ_TRUE;

  // Entry is a subdirectory (I've seen old zips with dir entries which have compressed deflate data which inflates to 0 bytes, but these entries claim to uncompress to 512 bytes in the headers).
  // I'm torn how to handle this case - should it fail instead?
  إذا (mz_zip_reader_is_file_a_directory(pZip, file_اشاريو))
    أرجع MZ_TRUE;

  // Encryption and patch files are not supported.
  إذا (file_stat.m_ٻٽو_انگ_flag & (1 | 32))
    أرجع MZ_FALSE;

  // This function only supports stored and deflate.
  إذا ((!(flags & MZ_ZIP_FLAG_COMPRESSED_معلومات)) && (file_stat.m_طريقو != 0) && (file_stat.m_طريقو != MZ_DEFLATED))
    أرجع MZ_FALSE;

  // Ensure supplied output buffer is large enough.
  needed_سائيز = (flags & MZ_ZIP_FLAG_COMPRESSED_معلومات) ? file_stat.m_comp_سائيز : file_stat.m_uncomp_سائيز;
  إذا (buf_سائيز_2 < needed_سائيز)
    أرجع MZ_FALSE;

  // Read and parse the local directory entry.
  cur_file_ofs = file_stat.m_local_سرو_ofs;
  إذا (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, p_Local_سرو, MZ_ZIP_LOCAL_DIR_سرو_سائيز) != MZ_ZIP_LOCAL_DIR_سرو_سائيز)
    أرجع MZ_FALSE;
  إذا (MZ_READ_LE32(p_Local_سرو) != MZ_ZIP_LOCAL_DIR_سرو_SIG)
    أرجع MZ_FALSE;

  cur_file_ofs += MZ_ZIP_LOCAL_DIR_سرو_سائيز + MZ_READ_LE16(p_Local_سرو + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p_Local_سرو + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  إذا ((cur_file_ofs + file_stat.m_comp_سائيز) > pZip->m_archive_سائيز)
    أرجع MZ_FALSE;

  إذا ((flags & MZ_ZIP_FLAG_COMPRESSED_معلومات) || (!file_stat.m_طريقو))
  {
    // The file is stored or the caller has requested the compressed data.
    إذا (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, (size_t)needed_سائيز) != needed_سائيز)
      أرجع MZ_FALSE;
    أرجع ((flags & MZ_ZIP_FLAG_COMPRESSED_معلومات) != 0) || (mz_چڪري_جاچ_32(MZ_چڪري_جاچ_32_INIT, (ثابت mz_uint8 *)pBuf, (size_t)file_stat.m_uncomp_سائيز) == file_stat.m_چڪري_جاچ_32);
  }

  // Decompress the file either directly from memory or from a file input buffer.
  tinfl_init(&inflator);

  إذا (pZip->m_pState->m_pMem)
  {
    // Read directly from the archive in memory.
    pRead_buf = (mz_uint8 *)pZip->m_pState->m_pMem + cur_file_ofs;
    read_buf_سائيز = read_buf_avail = file_stat.m_comp_سائيز;
    comp_بچيل = 0;
  }
  وإلا إذا (pUser_read_buf)
  {
    // Use a user provided read buffer.
    إذا (!user_read_buf_سائيز)
      أرجع MZ_FALSE;
    pRead_buf = (mz_uint8 *)pUser_read_buf;
    read_buf_سائيز = user_read_buf_سائيز;
    read_buf_avail = 0;
    comp_بچيل = file_stat.m_comp_سائيز;
  }
  وإلا
  {
    // Temporarily allocate a read buffer.
    read_buf_سائيز = MZ_MIN(file_stat.m_comp_سائيز, MZ_ZIP_MAX_IO_BUF_سائيز);
#جيڪڏهن_وصف_ٿيل _MSC_VER
    إذا (((0, حجم(size_t) == حجم(mz_uint32))) && (read_buf_سائيز > 0x7FFFFFFF))
#وإلا
    إذا (((حجم(size_t) == حجم(mz_uint32))) && (read_buf_سائيز > 0x7FFFFFFF))
#جيڪڏهن_پورو
      أرجع MZ_FALSE;
    إذا (عدم == (pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)read_buf_سائيز)))
      أرجع MZ_FALSE;
    read_buf_avail = 0;
    comp_بچيل = file_stat.m_comp_سائيز;
  }

  افعل
  {
    size_t اندريون_buf_سائيز, ٻاهريون_buf_سائيز = (size_t)(file_stat.m_uncomp_سائيز - ٻاهريون_buf_ofs);
    إذا ((!read_buf_avail) && (!pZip->m_pState->m_pMem))
    {
      read_buf_avail = MZ_MIN(read_buf_سائيز, comp_بچيل);
      إذا (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
      {
        حالت = TINFL_حالت_FAILED;
        اكسر;
      }
      cur_file_ofs += read_buf_avail;
      comp_بچيل -= read_buf_avail;
      read_buf_ofs = 0;
    }
    اندريون_buf_سائيز = (size_t)read_buf_avail;
    حالت = tinfl_decompress(&inflator, (mz_uint8 *)pRead_buf + read_buf_ofs, &اندريون_buf_سائيز, (mz_uint8 *)pBuf, (mz_uint8 *)pBuf + ٻاهريون_buf_ofs, &ٻاهريون_buf_سائيز, TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF | (comp_بچيل ? TINFL_FLAG_HAS_وڌيڪ_داخلا : 0));
    read_buf_avail -= اندريون_buf_سائيز;
    read_buf_ofs += اندريون_buf_سائيز;
    ٻاهريون_buf_ofs += ٻاهريون_buf_سائيز;
  } طالما (حالت == TINFL_حالت_NEEDS_وڌيڪ_داخلا);

  إذا (حالت == TINFL_حالت_پورو)
  {
    // Make sure the entire file was decompressed, and check its CRC.
    إذا ((ٻاهريون_buf_ofs != file_stat.m_uncomp_سائيز) || (mz_چڪري_جاچ_32(MZ_چڪري_جاچ_32_INIT, (ثابت mz_uint8 *)pBuf, (size_t)file_stat.m_uncomp_سائيز) != file_stat.m_چڪري_جاچ_32))
      حالت = TINFL_حالت_FAILED;
  }

  إذا ((!pZip->m_pState->m_pMem) && (!pUser_read_buf))
    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);

  أرجع حالت == TINFL_حالت_پورو;
}

mz_bool mz_zip_reader_ڪڍو_file_منزل_mem_no_alloc(mz_zip_archive *pZip, ثابت حرف *pFilename, فراغ *pBuf, size_t buf_سائيز_2, mz_uint flags, فراغ *pUser_read_buf, size_t user_read_buf_سائيز)
{
  صحيح file_اشاريو = mz_zip_reader_locate_file(pZip, pFilename, عدم, flags);
  إذا (file_اشاريو < 0)
    أرجع MZ_FALSE;
  أرجع mz_zip_reader_ڪڍو_منزل_mem_no_alloc(pZip, file_اشاريو, pBuf, buf_سائيز_2, flags, pUser_read_buf, user_read_buf_سائيز);
}

mz_bool mz_zip_reader_ڪڍو_منزل_mem(mz_zip_archive *pZip, mz_uint file_اشاريو, فراغ *pBuf, size_t buf_سائيز_2, mz_uint flags)
{
  أرجع mz_zip_reader_ڪڍو_منزل_mem_no_alloc(pZip, file_اشاريو, pBuf, buf_سائيز_2, flags, عدم, 0);
}

mz_bool mz_zip_reader_ڪڍو_file_منزل_mem(mz_zip_archive *pZip, ثابت حرف *pFilename, فراغ *pBuf, size_t buf_سائيز_2, mz_uint flags)
{
  أرجع mz_zip_reader_ڪڍو_file_منزل_mem_no_alloc(pZip, pFilename, pBuf, buf_سائيز_2, flags, عدم, 0);
}

فراغ *mz_zip_reader_ڪڍو_منزل_ڍير(mz_zip_archive *pZip, mz_uint file_اشاريو, size_t *p_سائيز, mz_uint flags)
{
  mz_uint64 comp_سائيز, uncomp_سائيز, alloc_سائيز_2;
  ثابت mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_اشاريو);
  فراغ *pBuf;

  إذا (p_سائيز)
    *p_سائيز = 0;
  إذا (!p)
    أرجع عدم;

  comp_سائيز = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_سائيز_OFS);
  uncomp_سائيز = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_سائيز_OFS);

  alloc_سائيز_2 = (flags & MZ_ZIP_FLAG_COMPRESSED_معلومات) ? comp_سائيز : uncomp_سائيز;
#جيڪڏهن_وصف_ٿيل _MSC_VER
  إذا (((0, حجم(size_t) == حجم(mz_uint32))) && (alloc_سائيز_2 > 0x7FFFFFFF))
#وإلا
  إذا (((حجم(size_t) == حجم(mz_uint32))) && (alloc_سائيز_2 > 0x7FFFFFFF))
#جيڪڏهن_پورو
    أرجع عدم;
  إذا (عدم == (pBuf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)alloc_سائيز_2)))
    أرجع عدم;

  إذا (!mz_zip_reader_ڪڍو_منزل_mem(pZip, file_اشاريو, pBuf, (size_t)alloc_سائيز_2, flags))
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
    أرجع عدم;
  }

  إذا (p_سائيز) *p_سائيز = (size_t)alloc_سائيز_2;
  أرجع pBuf;
}

فراغ *mz_zip_reader_ڪڍو_file_منزل_ڍير(mz_zip_archive *pZip, ثابت حرف *pFilename, size_t *p_سائيز, mz_uint flags)
{
  صحيح file_اشاريو = mz_zip_reader_locate_file(pZip, pFilename, عدم, flags);
  إذا (file_اشاريو < 0)
  {
    إذا (p_سائيز) *p_سائيز = 0;
    أرجع MZ_FALSE;
  }
  أرجع mz_zip_reader_ڪڍو_منزل_ڍير(pZip, file_اشاريو, p_سائيز, flags);
}

mz_bool mz_zip_reader_ڪڍو_منزل_callback(mz_zip_archive *pZip, mz_uint file_اشاريو, mz_file_write_func pCallback, فراغ *pOpaque, mz_uint flags)
{
  صحيح حالت = TINFL_حالت_پورو; mz_uint file_چڪري_جاچ_32 = MZ_چڪري_جاچ_32_INIT;
  mz_uint64 read_buf_سائيز, read_buf_ofs = 0, read_buf_avail, comp_بچيل, ٻاهريون_buf_ofs = 0, cur_file_ofs;
  mz_zip_archive_file_stat file_stat;
  فراغ *pRead_buf = عدم; فراغ *pWrite_buf = عدم;
  mz_uint32 local_سرو_u32[(MZ_ZIP_LOCAL_DIR_سرو_سائيز + حجم(mz_uint32) - 1) / حجم(mz_uint32)]; mz_uint8 *p_Local_سرو = (mz_uint8 *)local_سرو_u32;

  إذا (!mz_zip_reader_file_stat(pZip, file_اشاريو, &file_stat))
    أرجع MZ_FALSE;

  // Empty file, or a directory (but not always a directory - I've seen odd zips with directories that have compressed data which inflates to 0 bytes)
  إذا (!file_stat.m_comp_سائيز)
    أرجع MZ_TRUE;

  // Entry is a subdirectory (I've seen old zips with dir entries which have compressed deflate data which inflates to 0 bytes, but these entries claim to uncompress to 512 bytes in the headers).
  // I'm torn how to handle this case - should it fail instead?
  إذا (mz_zip_reader_is_file_a_directory(pZip, file_اشاريو))
    أرجع MZ_TRUE;

  // Encryption and patch files are not supported.
  إذا (file_stat.m_ٻٽو_انگ_flag & (1 | 32))
    أرجع MZ_FALSE;

  // This function only supports stored and deflate.
  إذا ((!(flags & MZ_ZIP_FLAG_COMPRESSED_معلومات)) && (file_stat.m_طريقو != 0) && (file_stat.m_طريقو != MZ_DEFLATED))
    أرجع MZ_FALSE;

  // Read and parse the local directory entry.
  cur_file_ofs = file_stat.m_local_سرو_ofs;
  إذا (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, p_Local_سرو, MZ_ZIP_LOCAL_DIR_سرو_سائيز) != MZ_ZIP_LOCAL_DIR_سرو_سائيز)
    أرجع MZ_FALSE;
  إذا (MZ_READ_LE32(p_Local_سرو) != MZ_ZIP_LOCAL_DIR_سرو_SIG)
    أرجع MZ_FALSE;

  cur_file_ofs += MZ_ZIP_LOCAL_DIR_سرو_سائيز + MZ_READ_LE16(p_Local_سرو + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p_Local_سرو + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  إذا ((cur_file_ofs + file_stat.m_comp_سائيز) > pZip->m_archive_سائيز)
    أرجع MZ_FALSE;

  // Decompress the file either directly from memory or from a file input buffer.
  إذا (pZip->m_pState->m_pMem)
  {
    pRead_buf = (mz_uint8 *)pZip->m_pState->m_pMem + cur_file_ofs;
    read_buf_سائيز = read_buf_avail = file_stat.m_comp_سائيز;
    comp_بچيل = 0;
  }
  وإلا
  {
    read_buf_سائيز = MZ_MIN(file_stat.m_comp_سائيز, MZ_ZIP_MAX_IO_BUF_سائيز);
    إذا (عدم == (pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)read_buf_سائيز)))
      أرجع MZ_FALSE;
    read_buf_avail = 0;
    comp_بچيل = file_stat.m_comp_سائيز;
  }

  إذا ((flags & MZ_ZIP_FLAG_COMPRESSED_معلومات) || (!file_stat.m_طريقو))
  {
    // The file is stored or the caller has requested the compressed data.
    إذا (pZip->m_pState->m_pMem)
    {
#جيڪڏهن_وصف_ٿيل _MSC_VER
      إذا (((0, حجم(size_t) == حجم(mz_uint32))) && (file_stat.m_comp_سائيز > 0xFFFFFFFF))
#وإلا
      إذا (((حجم(size_t) == حجم(mz_uint32))) && (file_stat.m_comp_سائيز > 0xFFFFFFFF))
#جيڪڏهن_پورو
        أرجع MZ_FALSE;
      إذا (pCallback(pOpaque, ٻاهريون_buf_ofs, pRead_buf, (size_t)file_stat.m_comp_سائيز) != file_stat.m_comp_سائيز)
        حالت = TINFL_حالت_FAILED;
      وإلا إذا (!(flags & MZ_ZIP_FLAG_COMPRESSED_معلومات))
        file_چڪري_جاچ_32 = (mz_uint32)mz_چڪري_جاچ_32(file_چڪري_جاچ_32, (ثابت mz_uint8 *)pRead_buf, (size_t)file_stat.m_comp_سائيز);
      cur_file_ofs += file_stat.m_comp_سائيز;
      ٻاهريون_buf_ofs += file_stat.m_comp_سائيز;
      comp_بچيل = 0;
    }
    وإلا
    {
      طالما (comp_بچيل)
      {
        read_buf_avail = MZ_MIN(read_buf_سائيز, comp_بچيل);
        إذا (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
        {
          حالت = TINFL_حالت_FAILED;
          اكسر;
        }

        إذا (!(flags & MZ_ZIP_FLAG_COMPRESSED_معلومات))
          file_چڪري_جاچ_32 = (mz_uint32)mz_چڪري_جاچ_32(file_چڪري_جاچ_32, (ثابت mz_uint8 *)pRead_buf, (size_t)read_buf_avail);

        إذا (pCallback(pOpaque, ٻاهريون_buf_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
        {
          حالت = TINFL_حالت_FAILED;
          اكسر;
        }
        cur_file_ofs += read_buf_avail;
        ٻاهريون_buf_ofs += read_buf_avail;
        comp_بچيل -= read_buf_avail;
      }
    }
  }
  وإلا
  {
    tinfl_decompressor inflator;
    tinfl_init(&inflator);

    إذا (عدم == (pWrite_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, TINFL_LZ_DICT_سائيز)))
      حالت = TINFL_حالت_FAILED;
    وإلا
    {
      افعل
      {
        mz_uint8 *pWrite_buf_cur = (mz_uint8 *)pWrite_buf + (ٻاهريون_buf_ofs & (TINFL_LZ_DICT_سائيز - 1));
        size_t اندريون_buf_سائيز, ٻاهريون_buf_سائيز = TINFL_LZ_DICT_سائيز - (ٻاهريون_buf_ofs & (TINFL_LZ_DICT_سائيز - 1));
        إذا ((!read_buf_avail) && (!pZip->m_pState->m_pMem))
        {
          read_buf_avail = MZ_MIN(read_buf_سائيز, comp_بچيل);
          إذا (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
          {
            حالت = TINFL_حالت_FAILED;
            اكسر;
          }
          cur_file_ofs += read_buf_avail;
          comp_بچيل -= read_buf_avail;
          read_buf_ofs = 0;
        }

        اندريون_buf_سائيز = (size_t)read_buf_avail;
        حالت = tinfl_decompress(&inflator, (ثابت mz_uint8 *)pRead_buf + read_buf_ofs, &اندريون_buf_سائيز, (mz_uint8 *)pWrite_buf, pWrite_buf_cur, &ٻاهريون_buf_سائيز, comp_بچيل ? TINFL_FLAG_HAS_وڌيڪ_داخلا : 0);
        read_buf_avail -= اندريون_buf_سائيز;
        read_buf_ofs += اندريون_buf_سائيز;

        إذا (ٻاهريون_buf_سائيز)
        {
          إذا (pCallback(pOpaque, ٻاهريون_buf_ofs, pWrite_buf_cur, ٻاهريون_buf_سائيز) != ٻاهريون_buf_سائيز)
          {
            حالت = TINFL_حالت_FAILED;
            اكسر;
          }
          file_چڪري_جاچ_32 = (mz_uint32)mz_چڪري_جاچ_32(file_چڪري_جاچ_32, pWrite_buf_cur, ٻاهريون_buf_سائيز);
          إذا ((ٻاهريون_buf_ofs += ٻاهريون_buf_سائيز) > file_stat.m_uncomp_سائيز)
          {
            حالت = TINFL_حالت_FAILED;
            اكسر;
          }
        }
      } طالما ((حالت == TINFL_حالت_NEEDS_وڌيڪ_داخلا) || (حالت == TINFL_حالت_HAS_وڌيڪ_OUTPUT));
    }
  }

  إذا ((حالت == TINFL_حالت_پورو) && (!(flags & MZ_ZIP_FLAG_COMPRESSED_معلومات)))
  {
    // Make sure the entire file was decompressed, and check its CRC.
    إذا ((ٻاهريون_buf_ofs != file_stat.m_uncomp_سائيز) || (file_چڪري_جاچ_32 != file_stat.m_چڪري_جاچ_32))
      حالت = TINFL_حالت_FAILED;
  }

  إذا (!pZip->m_pState->m_pMem)
    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
  إذا (pWrite_buf)
    pZip->m_pFree(pZip->m_pAlloc_opaque, pWrite_buf);

  أرجع حالت == TINFL_حالت_پورو;
}

mz_bool mz_zip_reader_ڪڍو_file_منزل_callback(mz_zip_archive *pZip, ثابت حرف *pFilename, mz_file_write_func pCallback, فراغ *pOpaque, mz_uint flags)
{
  صحيح file_اشاريو = mz_zip_reader_locate_file(pZip, pFilename, عدم, flags);
  إذا (file_اشاريو < 0)
    أرجع MZ_FALSE;
  أرجع mz_zip_reader_ڪڍو_منزل_callback(pZip, file_اشاريو, pCallback, pOpaque, flags);
}

#جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_STDIO
ساكن size_t mz_zip_file_write_callback(فراغ *pOpaque, mz_uint64 ofs, ثابت فراغ *pBuf, size_t n)
{
  (فراغ)ofs; أرجع MZ_FWRITE(pBuf, 1, n, (MZ_FILE*)pOpaque);
}

mz_bool mz_zip_reader_ڪڍو_منزل_file(mz_zip_archive *pZip, mz_uint file_اشاريو, ثابت حرف *pDst_filename, mz_uint flags)
{
  mz_bool حالت;
  mz_zip_archive_file_stat file_stat;
  MZ_FILE *pFile;
  إذا (!mz_zip_reader_file_stat(pZip, file_اشاريو, &file_stat))
    أرجع MZ_FALSE;
  pFile = MZ_FOPEN(pDst_filename, "wb");
  إذا (!pFile)
    أرجع MZ_FALSE;
  حالت = mz_zip_reader_ڪڍو_منزل_callback(pZip, file_اشاريو, mz_zip_file_write_callback, pFile, flags);
  إذا (MZ_FCLOSE(pFile) == EOF)
    أرجع MZ_FALSE;
#جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_وقت
  إذا (حالت)
    mz_zip_سيٽ_file_times(pDst_filename, file_stat.m_وقت, file_stat.m_وقت);
#جيڪڏهن_پورو
  أرجع حالت;
}
#جيڪڏهن_پورو // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_reader_پڇاڙي(mz_zip_archive *pZip)
{
  إذا ((!pZip) || (!pZip->m_pState) || (!pZip->m_pAlloc) || (!pZip->m_pFree) || (pZip->m_zip_گهڻائي != MZ_ZIP_گهڻائي_READING))
    أرجع MZ_FALSE;

  إذا (pZip->m_pState)
  {
    mz_zip_اندروني_state *pState = pZip->m_pState; pZip->m_pState = عدم;
    mz_zip_array_clear(pZip, &pState->m_central_dir);
    mz_zip_array_clear(pZip, &pState->m_central_dir_offsets);
    mz_zip_array_clear(pZip, &pState->m_sorted_central_dir_offsets);

#جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_STDIO
    إذا (pState->m_pFile)
    {
      MZ_FCLOSE(pState->m_pFile);
      pState->m_pFile = عدم;
    }
#جيڪڏهن_پورو // #ifndef MINIZ_NO_STDIO

    pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
  }
  pZip->m_zip_گهڻائي = MZ_ZIP_گهڻائي_INVALID;

  أرجع MZ_TRUE;
}

#جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_STDIO
mz_bool mz_zip_reader_ڪڍو_file_منزل_file(mz_zip_archive *pZip, ثابت حرف *pArchive_filename, ثابت حرف *pDst_filename, mz_uint flags)
{
  صحيح file_اشاريو = mz_zip_reader_locate_file(pZip, pArchive_filename, عدم, flags);
  إذا (file_اشاريو < 0)
    أرجع MZ_FALSE;
  أرجع mz_zip_reader_ڪڍو_منزل_file(pZip, file_اشاريو, pDst_filename, flags);
}
#جيڪڏهن_پورو

// ------------------- .ZIP archive writing

#جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_ARCHIVE_WRITING_APIS

ساكن فراغ mz_write_le16(mz_uint8 *p, mz_uint16 v) { p[0] = (mz_uint8)v; p[1] = (mz_uint8)(v >> 8); }
ساكن فراغ mz_write_le32(mz_uint8 *p, mz_uint32 v) { p[0] = (mz_uint8)v; p[1] = (mz_uint8)(v >> 8); p[2] = (mz_uint8)(v >> 16); p[3] = (mz_uint8)(v >> 24); }
#وصف_ڪريو MZ_WRITE_LE16(p, v) mz_write_le16((mz_uint8 *)(p), (mz_uint16)(v))
#وصف_ڪريو MZ_WRITE_LE32(p, v) mz_write_le32((mz_uint8 *)(p), (mz_uint32)(v))

mz_bool mz_zip_writer_init(mz_zip_archive *pZip, mz_uint64 existing_سائيز)
{
  إذا ((!pZip) || (pZip->m_pState) || (!pZip->m_pWrite) || (pZip->m_zip_گهڻائي != MZ_ZIP_گهڻائي_INVALID))
    أرجع MZ_FALSE;

  إذا (pZip->m_file_وٿي_alignment)
  {
    // Ensure user specified file offset alignment is a power of 2.
    إذا (pZip->m_file_وٿي_alignment & (pZip->m_file_وٿي_alignment - 1))
      أرجع MZ_FALSE;
  }

  إذا (!pZip->m_pAlloc) pZip->m_pAlloc = def_alloc_func;
  إذا (!pZip->m_pFree) pZip->m_pFree = def_free_func;
  إذا (!pZip->m_pRealloc) pZip->m_pRealloc = def_realloc_func;

  pZip->m_zip_گهڻائي = MZ_ZIP_گهڻائي_WRITING;
  pZip->m_archive_سائيز = existing_سائيز;
  pZip->m_central_directory_file_ofs = 0;
  pZip->m_ڪل_files = 0;

  إذا (عدم == (pZip->m_pState = (mz_zip_اندروني_state *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, حجم(mz_zip_اندروني_state))))
    أرجع MZ_FALSE;
  memset(pZip->m_pState, 0, حجم(mz_zip_اندروني_state));
  MZ_ZIP_ARRAY_سيٽ_ELEMENT_سائيز(&pZip->m_pState->m_central_dir, حجم(mz_uint8));
  MZ_ZIP_ARRAY_سيٽ_ELEMENT_سائيز(&pZip->m_pState->m_central_dir_offsets, حجم(mz_uint32));
  MZ_ZIP_ARRAY_سيٽ_ELEMENT_سائيز(&pZip->m_pState->m_sorted_central_dir_offsets, حجم(mz_uint32));
  أرجع MZ_TRUE;
}

ساكن size_t mz_zip_ڍير_write_func(فراغ *pOpaque, mz_uint64 file_ofs, ثابت فراغ *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_zip_اندروني_state *pState = pZip->m_pState;
  mz_uint64 new_سائيز = MZ_MAX(file_ofs + n, pState->m_mem_سائيز);
#جيڪڏهن_وصف_ٿيل _MSC_VER
  إذا ((!n) || ((0, حجم(size_t) == حجم(mz_uint32)) && (new_سائيز > 0x7FFFFFFF)))
#وإلا
  إذا ((!n) || ((حجم(size_t) == حجم(mz_uint32)) && (new_سائيز > 0x7FFFFFFF)))
#جيڪڏهن_پورو
    أرجع 0;
  إذا (new_سائيز > pState->m_mem_صلاحيت)
  {
    فراغ *p_New_بلاڪ;
    size_t new_صلاحيت = MZ_MAX(64, pState->m_mem_صلاحيت); طالما (new_صلاحيت < new_سائيز) new_صلاحيت *= 2;
    إذا (عدم == (p_New_بلاڪ = pZip->m_pRealloc(pZip->m_pAlloc_opaque, pState->m_pMem, 1, new_صلاحيت)))
      أرجع 0;
    pState->m_pMem = p_New_بلاڪ; pState->m_mem_صلاحيت = new_صلاحيت;
  }
  يادگيري_نقل((mz_uint8 *)pState->m_pMem + file_ofs, pBuf, n);
  pState->m_mem_سائيز = (size_t)new_سائيز;
  أرجع n;
}

mz_bool mz_zip_writer_init_ڍير(mz_zip_archive *pZip, size_t سائيز_منزل_reserve_at_beginning, size_t initial_ورهاست_سائيز)
{
  pZip->m_pWrite = mz_zip_ڍير_write_func;
  pZip->m_pIO_opaque = pZip;
  إذا (!mz_zip_writer_init(pZip, سائيز_منزل_reserve_at_beginning))
    أرجع MZ_FALSE;
  إذا (0 != (initial_ورهاست_سائيز = MZ_MAX(initial_ورهاست_سائيز, سائيز_منزل_reserve_at_beginning)))
  {
    إذا (عدم == (pZip->m_pState->m_pMem = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, initial_ورهاست_سائيز)))
    {
      mz_zip_writer_پڇاڙي(pZip);
      أرجع MZ_FALSE;
    }
    pZip->m_pState->m_mem_صلاحيت = initial_ورهاست_سائيز;
  }
  أرجع MZ_TRUE;
}

#جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_STDIO
ساكن size_t mz_zip_file_write_func(فراغ *pOpaque, mz_uint64 file_ofs, ثابت فراغ *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_int64 cur_ofs = MZ_FTELL64(pZip->m_pState->m_pFile);
  إذا (((mz_int64)file_ofs < 0) || (((cur_ofs != (mz_int64)file_ofs)) && (MZ_FSEEK64(pZip->m_pState->m_pFile, (mz_int64)file_ofs, SEEK_SET))))
    أرجع 0;
  أرجع MZ_FWRITE(pBuf, 1, n, pZip->m_pState->m_pFile);
}

mz_bool mz_zip_writer_init_file(mz_zip_archive *pZip, ثابت حرف *pFilename, mz_uint64 سائيز_منزل_reserve_at_beginning)
{
  MZ_FILE *pFile;
  pZip->m_pWrite = mz_zip_file_write_func;
  pZip->m_pIO_opaque = pZip;
  إذا (!mz_zip_writer_init(pZip, سائيز_منزل_reserve_at_beginning))
    أرجع MZ_FALSE;
  إذا (عدم == (pFile = MZ_FOPEN(pFilename, "wb")))
  {
    mz_zip_writer_پڇاڙي(pZip);
    أرجع MZ_FALSE;
  }
  pZip->m_pState->m_pFile = pFile;
  إذا (سائيز_منزل_reserve_at_beginning)
  {
    mz_uint64 cur_ofs = 0; حرف buf[4096]; MZ_CLEAR_ARR(buf);
    افعل
    {
      size_t n = (size_t)MZ_MIN(حجم(buf), سائيز_منزل_reserve_at_beginning);
      إذا (pZip->m_pWrite(pZip->m_pIO_opaque, cur_ofs, buf, n) != n)
      {
        mz_zip_writer_پڇاڙي(pZip);
        أرجع MZ_FALSE;
      }
      cur_ofs += n; سائيز_منزل_reserve_at_beginning -= n;
    } طالما (سائيز_منزل_reserve_at_beginning);
  }
  أرجع MZ_TRUE;
}
#جيڪڏهن_پورو // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_writer_init_from_reader(mz_zip_archive *pZip, ثابت حرف *pFilename)
{
  mz_zip_اندروني_state *pState;
  إذا ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_گهڻائي != MZ_ZIP_گهڻائي_READING))
    أرجع MZ_FALSE;
  // No sense in trying to write to an archive that's already at the support max size
  إذا ((pZip->m_ڪل_files == 0xFFFF) || ((pZip->m_archive_سائيز + MZ_ZIP_CENTRAL_DIR_سرو_سائيز + MZ_ZIP_LOCAL_DIR_سرو_سائيز) > 0xFFFFFFFF))
    أرجع MZ_FALSE;

  pState = pZip->m_pState;

  إذا (pState->m_pFile)
  {
#جيڪڏهن_وصف_ٿيل MINIZ_NO_STDIO
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
      mz_zip_reader_پڇاڙي(pZip);
      أرجع MZ_FALSE;
    }
#جيڪڏهن_پورو // #ifdef MINIZ_NO_STDIO
  }
  وإلا إذا (pState->m_pMem)
  {
    // Archive lives in a memory block. Assume it's from the heap that we can resize using the realloc callback.
    إذا (pZip->m_pIO_opaque != pZip)
      أرجع MZ_FALSE;
    pState->m_mem_صلاحيت = pState->m_mem_سائيز;
    pZip->m_pWrite = mz_zip_ڍير_write_func;
  }
  // Archive is being read via a user provided read function - make sure the user has specified a write function too.
  وإلا إذا (!pZip->m_pWrite)
    أرجع MZ_FALSE;

  // Start writing new files at the archive's current central directory location.
  pZip->m_archive_سائيز = pZip->m_central_directory_file_ofs;
  pZip->m_zip_گهڻائي = MZ_ZIP_گهڻائي_WRITING;
  pZip->m_central_directory_file_ofs = 0;

  أرجع MZ_TRUE;
}

mz_bool mz_zip_writer_جوڙيو_mem(mz_zip_archive *pZip, ثابت حرف *pArchive_name, ثابت فراغ *pBuf, size_t buf_سائيز_2, mz_uint level_and_flags)
{
  أرجع mz_zip_writer_جوڙيو_mem_ex(pZip, pArchive_name, pBuf, buf_سائيز_2, عدم, 0, level_and_flags, 0, 0);
}

تعريفنوع بنية
{
  mz_zip_archive *m_pZip;
  mz_uint64 m_cur_archive_file_ofs;
  mz_uint64 m_comp_سائيز;
} mz_zip_writer_جوڙيو_state;

ساكن mz_bool mz_zip_writer_جوڙيو_put_buf_callback(ثابت فراغ* pBuf, صحيح len, فراغ *pUser)
{
  mz_zip_writer_جوڙيو_state *pState = (mz_zip_writer_جوڙيو_state *)pUser;
  إذا ((صحيح)pState->m_pZip->m_pWrite(pState->m_pZip->m_pIO_opaque, pState->m_cur_archive_file_ofs, pBuf, len) != len)
    أرجع MZ_FALSE;
  pState->m_cur_archive_file_ofs += len;
  pState->m_comp_سائيز += len;
  أرجع MZ_TRUE;
}

ساكن mz_bool mz_zip_writer_create_local_dir_سرو(mz_zip_archive *pZip, mz_uint8 *pDst, mz_uint16 filename_سائيز, mz_uint16 extra_سائيز, mz_uint64 uncomp_سائيز, mz_uint64 comp_سائيز, mz_uint32 uncomp_چڪري_جاچ_32, mz_uint16 طريقو, mz_uint16 ٻٽو_انگ_flags, mz_uint16 dos_وقت, mz_uint16 dos_date)
{
  (فراغ)pZip;
  memset(pDst, 0, MZ_ZIP_LOCAL_DIR_سرو_سائيز);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_SIG_OFS, MZ_ZIP_LOCAL_DIR_سرو_SIG);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_نسخو_NEEDED_OFS, طريقو ? 20 : 0);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_ٻٽو_انگ_FLAG_OFS, ٻٽو_انگ_flags);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_طريقو_OFS, طريقو);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILE_وقت_OFS, dos_وقت);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILE_DATE_OFS, dos_date);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_چڪري_جاچ_32_OFS, uncomp_چڪري_جاچ_32);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_COMPRESSED_سائيز_OFS, comp_سائيز);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_DECOMPRESSED_سائيز_OFS, uncomp_سائيز);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILENAME_LEN_OFS, filename_سائيز);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_EXTRA_LEN_OFS, extra_سائيز);
  أرجع MZ_TRUE;
}

ساكن mz_bool mz_zip_writer_create_central_dir_سرو(mz_zip_archive *pZip, mz_uint8 *pDst, mz_uint16 filename_سائيز, mz_uint16 extra_سائيز, mz_uint16 comment_سائيز, mz_uint64 uncomp_سائيز, mz_uint64 comp_سائيز, mz_uint32 uncomp_چڪري_جاچ_32, mz_uint16 طريقو, mz_uint16 ٻٽو_انگ_flags, mz_uint16 dos_وقت, mz_uint16 dos_date, mz_uint64 local_سرو_ofs, mz_uint32 ext_خاصيتون)
{
  (فراغ)pZip;
  memset(pDst, 0, MZ_ZIP_CENTRAL_DIR_سرو_سائيز);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_SIG_OFS, MZ_ZIP_CENTRAL_DIR_سرو_SIG);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_نسخو_NEEDED_OFS, طريقو ? 20 : 0);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_ٻٽو_انگ_FLAG_OFS, ٻٽو_انگ_flags);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_طريقو_OFS, طريقو);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILE_وقت_OFS, dos_وقت);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILE_DATE_OFS, dos_date);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_چڪري_جاچ_32_OFS, uncomp_چڪري_جاچ_32);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_COMPRESSED_سائيز_OFS, comp_سائيز);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_DECOMPRESSED_سائيز_OFS, uncomp_سائيز);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILENAME_LEN_OFS, filename_سائيز);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_EXTRA_LEN_OFS, extra_سائيز);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_COMMENT_LEN_OFS, comment_سائيز);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS, ext_خاصيتون);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_LOCAL_سرو_OFS, local_سرو_ofs);
  أرجع MZ_TRUE;
}

ساكن mz_bool mz_zip_writer_جوڙيو_منزل_central_dir(mz_zip_archive *pZip, ثابت حرف *pFilename, mz_uint16 filename_سائيز, ثابت فراغ *pExtra, mz_uint16 extra_سائيز, ثابت فراغ *pComment, mz_uint16 comment_سائيز, mz_uint64 uncomp_سائيز, mz_uint64 comp_سائيز, mz_uint32 uncomp_چڪري_جاچ_32, mz_uint16 طريقو, mz_uint16 ٻٽو_انگ_flags, mz_uint16 dos_وقت, mz_uint16 dos_date, mz_uint64 local_سرو_ofs, mz_uint32 ext_خاصيتون)
{
  mz_zip_اندروني_state *pState = pZip->m_pState;
  mz_uint32 central_dir_ofs = (mz_uint32)pState->m_central_dir.m_سائيز;
  size_t orig_central_dir_سائيز = pState->m_central_dir.m_سائيز;
  mz_uint8 central_dir_سرو[MZ_ZIP_CENTRAL_DIR_سرو_سائيز];

  // No zip64 support yet
  إذا ((local_سرو_ofs > 0xFFFFFFFF) || (((mz_uint64)pState->m_central_dir.m_سائيز + MZ_ZIP_CENTRAL_DIR_سرو_سائيز + filename_سائيز + extra_سائيز + comment_سائيز) > 0xFFFFFFFF))
    أرجع MZ_FALSE;

  إذا (!mz_zip_writer_create_central_dir_سرو(pZip, central_dir_سرو, filename_سائيز, extra_سائيز, comment_سائيز, uncomp_سائيز, comp_سائيز, uncomp_چڪري_جاچ_32, طريقو, ٻٽو_انگ_flags, dos_وقت, dos_date, local_سرو_ofs, ext_خاصيتون))
    أرجع MZ_FALSE;

  إذا ((!mz_zip_array_ڌڪو_پٺ(pZip, &pState->m_central_dir, central_dir_سرو, MZ_ZIP_CENTRAL_DIR_سرو_سائيز)) ||
      (!mz_zip_array_ڌڪو_پٺ(pZip, &pState->m_central_dir, pFilename, filename_سائيز)) ||
      (!mz_zip_array_ڌڪو_پٺ(pZip, &pState->m_central_dir, pExtra, extra_سائيز)) ||
      (!mz_zip_array_ڌڪو_پٺ(pZip, &pState->m_central_dir, pComment, comment_سائيز)) ||
      (!mz_zip_array_ڌڪو_پٺ(pZip, &pState->m_central_dir_offsets, &central_dir_ofs, 1)))
  {
    // Try to push the central directory array back into its original state.
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_سائيز, MZ_FALSE);
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
  إذا (!pZip->m_file_وٿي_alignment)
    أرجع 0;
  n = (mz_uint32)(pZip->m_archive_سائيز & (pZip->m_file_وٿي_alignment - 1));
  أرجع (pZip->m_file_وٿي_alignment - n) & (pZip->m_file_وٿي_alignment - 1);
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

mz_bool mz_zip_writer_جوڙيو_mem_ex(mz_zip_archive *pZip, ثابت حرف *pArchive_name, ثابت فراغ *pBuf, size_t buf_سائيز_2, ثابت فراغ *pComment, mz_uint16 comment_سائيز, mz_uint level_and_flags, mz_uint64 uncomp_سائيز, mz_uint32 uncomp_چڪري_جاچ_32)
{
  mz_uint16 طريقو = 0, dos_وقت = 0, dos_date = 0;
  mz_uint level, ext_خاصيتون = 0, انگ_alignment_padding_بائيٽون;
  mz_uint64 local_dir_سرو_ofs = pZip->m_archive_سائيز, cur_archive_file_ofs = pZip->m_archive_سائيز, comp_سائيز = 0;
  size_t archive_name_سائيز;
  mz_uint8 local_dir_سرو[MZ_ZIP_LOCAL_DIR_سرو_سائيز];
  tdefl_compressor *pComp = عدم;
  mz_bool store_معلومات_uncompressed;
  mz_zip_اندروني_state *pState;

  إذا ((صحيح)level_and_flags < 0)
    level_and_flags = MZ_DEFAULT_LEVEL;
  level = level_and_flags & 0xF;
  store_معلومات_uncompressed = ((!level) || (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_معلومات));

  إذا ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_گهڻائي != MZ_ZIP_گهڻائي_WRITING) || ((buf_سائيز_2) && (!pBuf)) || (!pArchive_name) || ((comment_سائيز) && (!pComment)) || (pZip->m_ڪل_files == 0xFFFF) || (level > MZ_UBER_COMPRESSION))
    أرجع MZ_FALSE;

  pState = pZip->m_pState;

  إذا ((!(level_and_flags & MZ_ZIP_FLAG_COMPRESSED_معلومات)) && (uncomp_سائيز))
    أرجع MZ_FALSE;
  // No zip64 support yet
  إذا ((buf_سائيز_2 > 0xFFFFFFFF) || (uncomp_سائيز > 0xFFFFFFFF))
    أرجع MZ_FALSE;
  إذا (!mz_zip_writer_validate_archive_name(pArchive_name))
    أرجع MZ_FALSE;

#جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_وقت
  {
    وقت_t cur_وقت; وقت(&cur_وقت);
    mz_zip_وقت_منزل_dos_وقت(cur_وقت, &dos_وقت, &dos_date);
  }
#جيڪڏهن_پورو // #ifndef MINIZ_NO_TIME

  archive_name_سائيز = لڙي_ڊيگهه(pArchive_name);
  إذا (archive_name_سائيز > 0xFFFF)
    أرجع MZ_FALSE;

  انگ_alignment_padding_بائيٽون = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  إذا ((pZip->m_ڪل_files == 0xFFFF) || ((pZip->m_archive_سائيز + انگ_alignment_padding_بائيٽون + MZ_ZIP_LOCAL_DIR_سرو_سائيز + MZ_ZIP_CENTRAL_DIR_سرو_سائيز + comment_سائيز + archive_name_سائيز) > 0xFFFFFFFF))
    أرجع MZ_FALSE;

  إذا ((archive_name_سائيز) && (pArchive_name[archive_name_سائيز - 1] == '/'))
  {
    // Set DOS Subdirectory attribute bit.
    ext_خاصيتون |= 0x10;
    // Subdirectories cannot contain data.
    إذا ((buf_سائيز_2) || (uncomp_سائيز))
      أرجع MZ_FALSE;
  }

  // Try to do any allocations before writing to the archive, so if an allocation fails the file remains unmodified. (A good idea if we're doing an in-place modification.)
  إذا ((!mz_zip_array_ensure_گنجائش(pZip, &pState->m_central_dir, MZ_ZIP_CENTRAL_DIR_سرو_سائيز + archive_name_سائيز + comment_سائيز)) || (!mz_zip_array_ensure_گنجائش(pZip, &pState->m_central_dir_offsets, 1)))
    أرجع MZ_FALSE;

  إذا ((!store_معلومات_uncompressed) && (buf_سائيز_2))
  {
    إذا (عدم == (pComp = (tdefl_compressor *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, حجم(tdefl_compressor))))
      أرجع MZ_FALSE;
  }

  إذا (!mz_zip_writer_write_zeros(pZip, cur_archive_file_ofs, انگ_alignment_padding_بائيٽون + حجم(local_dir_سرو)))
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
    أرجع MZ_FALSE;
  }
  local_dir_سرو_ofs += انگ_alignment_padding_بائيٽون;
  إذا (pZip->m_file_وٿي_alignment) { MZ_ASSERT((local_dir_سرو_ofs & (pZip->m_file_وٿي_alignment - 1)) == 0); }
  cur_archive_file_ofs += انگ_alignment_padding_بائيٽون + حجم(local_dir_سرو);

  MZ_CLEAR_ARR(local_dir_سرو);
  إذا (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pArchive_name, archive_name_سائيز) != archive_name_سائيز)
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
    أرجع MZ_FALSE;
  }
  cur_archive_file_ofs += archive_name_سائيز;

  إذا (!(level_and_flags & MZ_ZIP_FLAG_COMPRESSED_معلومات))
  {
    uncomp_چڪري_جاچ_32 = (mz_uint32)mz_چڪري_جاچ_32(MZ_چڪري_جاچ_32_INIT, (ثابت mz_uint8*)pBuf, buf_سائيز_2);
    uncomp_سائيز = buf_سائيز_2;
    إذا (uncomp_سائيز <= 3)
    {
      level = 0;
      store_معلومات_uncompressed = MZ_TRUE;
    }
  }

  إذا (store_معلومات_uncompressed)
  {
    إذا (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pBuf, buf_سائيز_2) != buf_سائيز_2)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
      أرجع MZ_FALSE;
    }

    cur_archive_file_ofs += buf_سائيز_2;
    comp_سائيز = buf_سائيز_2;

    إذا (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_معلومات)
      طريقو = MZ_DEFLATED;
  }
  وإلا إذا (buf_سائيز_2)
  {
    mz_zip_writer_جوڙيو_state state;

    state.m_pZip = pZip;
    state.m_cur_archive_file_ofs = cur_archive_file_ofs;
    state.m_comp_سائيز = 0;

    إذا ((tdefl_init(pComp, mz_zip_writer_جوڙيو_put_buf_callback, &state, tdefl_create_comp_flags_from_zip_params(level, -15, MZ_DEFAULT_STRATEGY)) != TDEFL_حالت_OKAY) ||
        (tdefl_compress_بفر(pComp, pBuf, buf_سائيز_2, TDEFL_پڄاڻي) != TDEFL_حالت_پورو))
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
      أرجع MZ_FALSE;
    }

    comp_سائيز = state.m_comp_سائيز;
    cur_archive_file_ofs = state.m_cur_archive_file_ofs;

    طريقو = MZ_DEFLATED;
  }

  pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
  pComp = عدم;

  // no zip64 support yet
  إذا ((comp_سائيز > 0xFFFFFFFF) || (cur_archive_file_ofs > 0xFFFFFFFF))
    أرجع MZ_FALSE;

  إذا (!mz_zip_writer_create_local_dir_سرو(pZip, local_dir_سرو, (mz_uint16)archive_name_سائيز, 0, uncomp_سائيز, comp_سائيز, uncomp_چڪري_جاچ_32, طريقو, 0, dos_وقت, dos_date))
    أرجع MZ_FALSE;

  إذا (pZip->m_pWrite(pZip->m_pIO_opaque, local_dir_سرو_ofs, local_dir_سرو, حجم(local_dir_سرو)) != حجم(local_dir_سرو))
    أرجع MZ_FALSE;

  إذا (!mz_zip_writer_جوڙيو_منزل_central_dir(pZip, pArchive_name, (mz_uint16)archive_name_سائيز, عدم, 0, pComment, comment_سائيز, uncomp_سائيز, comp_سائيز, uncomp_چڪري_جاچ_32, طريقو, 0, dos_وقت, dos_date, local_dir_سرو_ofs, ext_خاصيتون))
    أرجع MZ_FALSE;

  pZip->m_ڪل_files++;
  pZip->m_archive_سائيز = cur_archive_file_ofs;

  أرجع MZ_TRUE;
}

#جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_STDIO
mz_bool mz_zip_writer_جوڙيو_file(mz_zip_archive *pZip, ثابت حرف *pArchive_name, ثابت حرف *pSrc_filename, ثابت فراغ *pComment, mz_uint16 comment_سائيز, mz_uint level_and_flags)
{
  mz_uint uncomp_چڪري_جاچ_32 = MZ_چڪري_جاچ_32_INIT, level, انگ_alignment_padding_بائيٽون;
  mz_uint16 طريقو = 0, dos_وقت = 0, dos_date = 0, ext_خاصيتون = 0;
  mz_uint64 local_dir_سرو_ofs = pZip->m_archive_سائيز, cur_archive_file_ofs = pZip->m_archive_سائيز, uncomp_سائيز = 0, comp_سائيز = 0;
  size_t archive_name_سائيز;
  mz_uint8 local_dir_سرو[MZ_ZIP_LOCAL_DIR_سرو_سائيز];
  MZ_FILE *pSrc_file = عدم;

  إذا ((صحيح)level_and_flags < 0)
    level_and_flags = MZ_DEFAULT_LEVEL;
  level = level_and_flags & 0xF;

  إذا ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_گهڻائي != MZ_ZIP_گهڻائي_WRITING) || (!pArchive_name) || ((comment_سائيز) && (!pComment)) || (level > MZ_UBER_COMPRESSION))
    أرجع MZ_FALSE;
  إذا (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_معلومات)
    أرجع MZ_FALSE;
  إذا (!mz_zip_writer_validate_archive_name(pArchive_name))
    أرجع MZ_FALSE;

  archive_name_سائيز = لڙي_ڊيگهه(pArchive_name);
  إذا (archive_name_سائيز > 0xFFFF)
    أرجع MZ_FALSE;

  انگ_alignment_padding_بائيٽون = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  إذا ((pZip->m_ڪل_files == 0xFFFF) || ((pZip->m_archive_سائيز + انگ_alignment_padding_بائيٽون + MZ_ZIP_LOCAL_DIR_سرو_سائيز + MZ_ZIP_CENTRAL_DIR_سرو_سائيز + comment_سائيز + archive_name_سائيز) > 0xFFFFFFFF))
    أرجع MZ_FALSE;

  إذا (!mz_zip_get_file_modified_وقت(pSrc_filename, &dos_وقت, &dos_date))
    أرجع MZ_FALSE;

  pSrc_file = MZ_FOPEN(pSrc_filename, "rb");
  إذا (!pSrc_file)
    أرجع MZ_FALSE;
  MZ_FSEEK64(pSrc_file, 0, SEEK_END);
  uncomp_سائيز = MZ_FTELL64(pSrc_file);
  MZ_FSEEK64(pSrc_file, 0, SEEK_SET);

  إذا (uncomp_سائيز > 0xFFFFFFFF)
  {
    // No zip64 support yet
    MZ_FCLOSE(pSrc_file);
    أرجع MZ_FALSE;
  }
  إذا (uncomp_سائيز <= 3)
    level = 0;

  إذا (!mz_zip_writer_write_zeros(pZip, cur_archive_file_ofs, انگ_alignment_padding_بائيٽون + حجم(local_dir_سرو)))
  {
    MZ_FCLOSE(pSrc_file);
    أرجع MZ_FALSE;
  }
  local_dir_سرو_ofs += انگ_alignment_padding_بائيٽون;
  إذا (pZip->m_file_وٿي_alignment) { MZ_ASSERT((local_dir_سرو_ofs & (pZip->m_file_وٿي_alignment - 1)) == 0); }
  cur_archive_file_ofs += انگ_alignment_padding_بائيٽون + حجم(local_dir_سرو);

  MZ_CLEAR_ARR(local_dir_سرو);
  إذا (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pArchive_name, archive_name_سائيز) != archive_name_سائيز)
  {
    MZ_FCLOSE(pSrc_file);
    أرجع MZ_FALSE;
  }
  cur_archive_file_ofs += archive_name_سائيز;

  إذا (uncomp_سائيز)
  {
    mz_uint64 uncomp_بچيل = uncomp_سائيز;
    فراغ *pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, MZ_ZIP_MAX_IO_BUF_سائيز);
    إذا (!pRead_buf)
    {
      MZ_FCLOSE(pSrc_file);
      أرجع MZ_FALSE;
    }

    إذا (!level)
    {
      طالما (uncomp_بچيل)
      {
        mz_uint n = (mz_uint)MZ_MIN(MZ_ZIP_MAX_IO_BUF_سائيز, uncomp_بچيل);
        إذا ((MZ_FREAD(pRead_buf, 1, n, pSrc_file) != n) || (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pRead_buf, n) != n))
        {
          pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
          MZ_FCLOSE(pSrc_file);
          أرجع MZ_FALSE;
        }
        uncomp_چڪري_جاچ_32 = (mz_uint32)mz_چڪري_جاچ_32(uncomp_چڪري_جاچ_32, (ثابت mz_uint8 *)pRead_buf, n);
        uncomp_بچيل -= n;
        cur_archive_file_ofs += n;
      }
      comp_سائيز = uncomp_سائيز;
    }
    وإلا
    {
      mz_bool نتيجو = MZ_FALSE;
      mz_zip_writer_جوڙيو_state state;
      tdefl_compressor *pComp = (tdefl_compressor *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, حجم(tdefl_compressor));
      إذا (!pComp)
      {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        أرجع MZ_FALSE;
      }

      state.m_pZip = pZip;
      state.m_cur_archive_file_ofs = cur_archive_file_ofs;
      state.m_comp_سائيز = 0;

      إذا (tdefl_init(pComp, mz_zip_writer_جوڙيو_put_buf_callback, &state, tdefl_create_comp_flags_from_zip_params(level, -15, MZ_DEFAULT_STRATEGY)) != TDEFL_حالت_OKAY)
      {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        أرجع MZ_FALSE;
      }

      لكل ( ; ; )
      {
        size_t اندريون_buf_سائيز = (mz_uint32)MZ_MIN(uncomp_بچيل, MZ_ZIP_MAX_IO_BUF_سائيز);
        tdefl_حالت حالت;

        إذا (MZ_FREAD(pRead_buf, 1, اندريون_buf_سائيز, pSrc_file) != اندريون_buf_سائيز)
          اكسر;

        uncomp_چڪري_جاچ_32 = (mz_uint32)mz_چڪري_جاچ_32(uncomp_چڪري_جاچ_32, (ثابت mz_uint8 *)pRead_buf, اندريون_buf_سائيز);
        uncomp_بچيل -= اندريون_buf_سائيز;

        حالت = tdefl_compress_بفر(pComp, pRead_buf, اندريون_buf_سائيز, uncomp_بچيل ? TDEFL_NO_FLUSH : TDEFL_پڄاڻي);
        إذا (حالت == TDEFL_حالت_پورو)
        {
          نتيجو = MZ_TRUE;
          اكسر;
        }
        وإلا إذا (حالت != TDEFL_حالت_OKAY)
          اكسر;
      }

      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);

      إذا (!نتيجو)
      {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        أرجع MZ_FALSE;
      }

      comp_سائيز = state.m_comp_سائيز;
      cur_archive_file_ofs = state.m_cur_archive_file_ofs;

      طريقو = MZ_DEFLATED;
    }

    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
  }

  MZ_FCLOSE(pSrc_file); pSrc_file = عدم;

  // no zip64 support yet
  إذا ((comp_سائيز > 0xFFFFFFFF) || (cur_archive_file_ofs > 0xFFFFFFFF))
    أرجع MZ_FALSE;

  إذا (!mz_zip_writer_create_local_dir_سرو(pZip, local_dir_سرو, (mz_uint16)archive_name_سائيز, 0, uncomp_سائيز, comp_سائيز, uncomp_چڪري_جاچ_32, طريقو, 0, dos_وقت, dos_date))
    أرجع MZ_FALSE;

  إذا (pZip->m_pWrite(pZip->m_pIO_opaque, local_dir_سرو_ofs, local_dir_سرو, حجم(local_dir_سرو)) != حجم(local_dir_سرو))
    أرجع MZ_FALSE;

  إذا (!mz_zip_writer_جوڙيو_منزل_central_dir(pZip, pArchive_name, (mz_uint16)archive_name_سائيز, عدم, 0, pComment, comment_سائيز, uncomp_سائيز, comp_سائيز, uncomp_چڪري_جاچ_32, طريقو, 0, dos_وقت, dos_date, local_dir_سرو_ofs, ext_خاصيتون))
    أرجع MZ_FALSE;

  pZip->m_ڪل_files++;
  pZip->m_archive_سائيز = cur_archive_file_ofs;

  أرجع MZ_TRUE;
}
#جيڪڏهن_پورو // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_writer_جوڙيو_from_zip_reader(mz_zip_archive *pZip, mz_zip_archive *p_ذريعو_zip, mz_uint file_اشاريو)
{
  mz_uint n, ٻٽو_انگ_flags, انگ_alignment_padding_بائيٽون;
  mz_uint64 comp_بائيٽون_بچيل, local_dir_سرو_ofs;
  mz_uint64 cur_src_file_ofs, cur_dst_file_ofs;
  mz_uint32 local_سرو_u32[(MZ_ZIP_LOCAL_DIR_سرو_سائيز + حجم(mz_uint32) - 1) / حجم(mz_uint32)]; mz_uint8 *p_Local_سرو = (mz_uint8 *)local_سرو_u32;
  mz_uint8 central_سرو[MZ_ZIP_CENTRAL_DIR_سرو_سائيز];
  size_t orig_central_dir_سائيز;
  mz_zip_اندروني_state *pState;
  فراغ *pBuf; ثابت mz_uint8 *p_Src_central_سرو;

  إذا ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_گهڻائي != MZ_ZIP_گهڻائي_WRITING))
    أرجع MZ_FALSE;
  إذا (عدم == (p_Src_central_سرو = mz_zip_reader_get_cdh(p_ذريعو_zip, file_اشاريو)))
    أرجع MZ_FALSE;
  pState = pZip->m_pState;

  انگ_alignment_padding_بائيٽون = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  إذا ((pZip->m_ڪل_files == 0xFFFF) || ((pZip->m_archive_سائيز + انگ_alignment_padding_بائيٽون + MZ_ZIP_LOCAL_DIR_سرو_سائيز + MZ_ZIP_CENTRAL_DIR_سرو_سائيز) > 0xFFFFFFFF))
    أرجع MZ_FALSE;

  cur_src_file_ofs = MZ_READ_LE32(p_Src_central_سرو + MZ_ZIP_CDH_LOCAL_سرو_OFS);
  cur_dst_file_ofs = pZip->m_archive_سائيز;

  إذا (p_ذريعو_zip->m_pRead(p_ذريعو_zip->m_pIO_opaque, cur_src_file_ofs, p_Local_سرو, MZ_ZIP_LOCAL_DIR_سرو_سائيز) != MZ_ZIP_LOCAL_DIR_سرو_سائيز)
    أرجع MZ_FALSE;
  إذا (MZ_READ_LE32(p_Local_سرو) != MZ_ZIP_LOCAL_DIR_سرو_SIG)
    أرجع MZ_FALSE;
  cur_src_file_ofs += MZ_ZIP_LOCAL_DIR_سرو_سائيز;

  إذا (!mz_zip_writer_write_zeros(pZip, cur_dst_file_ofs, انگ_alignment_padding_بائيٽون))
    أرجع MZ_FALSE;
  cur_dst_file_ofs += انگ_alignment_padding_بائيٽون;
  local_dir_سرو_ofs = cur_dst_file_ofs;
  إذا (pZip->m_file_وٿي_alignment) { MZ_ASSERT((local_dir_سرو_ofs & (pZip->m_file_وٿي_alignment - 1)) == 0); }

  إذا (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, p_Local_سرو, MZ_ZIP_LOCAL_DIR_سرو_سائيز) != MZ_ZIP_LOCAL_DIR_سرو_سائيز)
    أرجع MZ_FALSE;
  cur_dst_file_ofs += MZ_ZIP_LOCAL_DIR_سرو_سائيز;

  n = MZ_READ_LE16(p_Local_سرو + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p_Local_سرو + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  comp_بائيٽون_بچيل = n + MZ_READ_LE32(p_Src_central_سرو + MZ_ZIP_CDH_COMPRESSED_سائيز_OFS);

  إذا (عدم == (pBuf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)MZ_MAX(حجم(mz_uint32) * 4, MZ_MIN(MZ_ZIP_MAX_IO_BUF_سائيز, comp_بائيٽون_بچيل)))))
    أرجع MZ_FALSE;

  طالما (comp_بائيٽون_بچيل)
  {
    n = (mz_uint)MZ_MIN(MZ_ZIP_MAX_IO_BUF_سائيز, comp_بائيٽون_بچيل);
    إذا (p_ذريعو_zip->m_pRead(p_ذريعو_zip->m_pIO_opaque, cur_src_file_ofs, pBuf, n) != n)
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

    comp_بائيٽون_بچيل -= n;
  }

  ٻٽو_انگ_flags = MZ_READ_LE16(p_Local_سرو + MZ_ZIP_LDH_ٻٽو_انگ_FLAG_OFS);
  إذا (ٻٽو_انگ_flags & 8)
  {
    // Copy data descriptor
    إذا (p_ذريعو_zip->m_pRead(p_ذريعو_zip->m_pIO_opaque, cur_src_file_ofs, pBuf, حجم(mz_uint32) * 4) != حجم(mz_uint32) * 4)
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

  orig_central_dir_سائيز = pState->m_central_dir.m_سائيز;

  يادگيري_نقل(central_سرو, p_Src_central_سرو, MZ_ZIP_CENTRAL_DIR_سرو_سائيز);
  MZ_WRITE_LE32(central_سرو + MZ_ZIP_CDH_LOCAL_سرو_OFS, local_dir_سرو_ofs);
  إذا (!mz_zip_array_ڌڪو_پٺ(pZip, &pState->m_central_dir, central_سرو, MZ_ZIP_CENTRAL_DIR_سرو_سائيز))
    أرجع MZ_FALSE;

  n = MZ_READ_LE16(p_Src_central_سرو + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p_Src_central_سرو + MZ_ZIP_CDH_EXTRA_LEN_OFS) + MZ_READ_LE16(p_Src_central_سرو + MZ_ZIP_CDH_COMMENT_LEN_OFS);
  إذا (!mz_zip_array_ڌڪو_پٺ(pZip, &pState->m_central_dir, p_Src_central_سرو + MZ_ZIP_CENTRAL_DIR_سرو_سائيز, n))
  {
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_سائيز, MZ_FALSE);
    أرجع MZ_FALSE;
  }

  إذا (pState->m_central_dir.m_سائيز > 0xFFFFFFFF)
    أرجع MZ_FALSE;
  n = (mz_uint32)orig_central_dir_سائيز;
  إذا (!mz_zip_array_ڌڪو_پٺ(pZip, &pState->m_central_dir_offsets, &n, 1))
  {
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_سائيز, MZ_FALSE);
    أرجع MZ_FALSE;
  }

  pZip->m_ڪل_files++;
  pZip->m_archive_سائيز = cur_dst_file_ofs;

  أرجع MZ_TRUE;
}

mz_bool mz_zip_writer_finalize_archive(mz_zip_archive *pZip)
{
  mz_zip_اندروني_state *pState;
  mz_uint64 central_dir_ofs, central_dir_سائيز;
  mz_uint8 hdr[MZ_ZIP_پڇاڙي_جو_CENTRAL_DIR_سرو_سائيز];

  إذا ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_گهڻائي != MZ_ZIP_گهڻائي_WRITING))
    أرجع MZ_FALSE;

  pState = pZip->m_pState;

  // no zip64 support yet
  إذا ((pZip->m_ڪل_files > 0xFFFF) || ((pZip->m_archive_سائيز + pState->m_central_dir.m_سائيز + MZ_ZIP_پڇاڙي_جو_CENTRAL_DIR_سرو_سائيز) > 0xFFFFFFFF))
    أرجع MZ_FALSE;

  central_dir_ofs = 0;
  central_dir_سائيز = 0;
  إذا (pZip->m_ڪل_files)
  {
    // Write central directory
    central_dir_ofs = pZip->m_archive_سائيز;
    central_dir_سائيز = pState->m_central_dir.m_سائيز;
    pZip->m_central_directory_file_ofs = central_dir_ofs;
    إذا (pZip->m_pWrite(pZip->m_pIO_opaque, central_dir_ofs, pState->m_central_dir.m_p, (size_t)central_dir_سائيز) != central_dir_سائيز)
      أرجع MZ_FALSE;
    pZip->m_archive_سائيز += central_dir_سائيز;
  }

  // Write end of central directory record
  MZ_CLEAR_ARR(hdr);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_SIG_OFS, MZ_ZIP_پڇاڙي_جو_CENTRAL_DIR_سرو_SIG);
  MZ_WRITE_LE16(hdr + MZ_ZIP_ECDH_CDIR_انگ_ENTRIES_ON_DISK_OFS, pZip->m_ڪل_files);
  MZ_WRITE_LE16(hdr + MZ_ZIP_ECDH_CDIR_ڪل_ENTRIES_OFS, pZip->m_ڪل_files);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_CDIR_سائيز_OFS, central_dir_سائيز);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_CDIR_OFS_OFS, central_dir_ofs);

  إذا (pZip->m_pWrite(pZip->m_pIO_opaque, pZip->m_archive_سائيز, hdr, حجم(hdr)) != حجم(hdr))
    أرجع MZ_FALSE;
#جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_STDIO
  إذا ((pState->m_pFile) && (MZ_FFLUSH(pState->m_pFile) == EOF))
    أرجع MZ_FALSE;
#جيڪڏهن_پورو // #ifndef MINIZ_NO_STDIO

  pZip->m_archive_سائيز += حجم(hdr);

  pZip->m_zip_گهڻائي = MZ_ZIP_گهڻائي_WRITING_HAS_BEEN_FINALIZED;
  أرجع MZ_TRUE;
}

mz_bool mz_zip_writer_finalize_ڍير_archive(mz_zip_archive *pZip, فراغ **pBuf, size_t *p_سائيز)
{
  إذا ((!pZip) || (!pZip->m_pState) || (!pBuf) || (!p_سائيز))
    أرجع MZ_FALSE;
  إذا (pZip->m_pWrite != mz_zip_ڍير_write_func)
    أرجع MZ_FALSE;
  إذا (!mz_zip_writer_finalize_archive(pZip))
    أرجع MZ_FALSE;

  *pBuf = pZip->m_pState->m_pMem;
  *p_سائيز = pZip->m_pState->m_mem_سائيز;
  pZip->m_pState->m_pMem = عدم;
  pZip->m_pState->m_mem_سائيز = pZip->m_pState->m_mem_صلاحيت = 0;
  أرجع MZ_TRUE;
}

mz_bool mz_zip_writer_پڇاڙي(mz_zip_archive *pZip)
{
  mz_zip_اندروني_state *pState;
  mz_bool حالت = MZ_TRUE;
  إذا ((!pZip) || (!pZip->m_pState) || (!pZip->m_pAlloc) || (!pZip->m_pFree) || ((pZip->m_zip_گهڻائي != MZ_ZIP_گهڻائي_WRITING) && (pZip->m_zip_گهڻائي != MZ_ZIP_گهڻائي_WRITING_HAS_BEEN_FINALIZED)))
    أرجع MZ_FALSE;

  pState = pZip->m_pState;
  pZip->m_pState = عدم;
  mz_zip_array_clear(pZip, &pState->m_central_dir);
  mz_zip_array_clear(pZip, &pState->m_central_dir_offsets);
  mz_zip_array_clear(pZip, &pState->m_sorted_central_dir_offsets);

#جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_STDIO
  إذا (pState->m_pFile)
  {
    MZ_FCLOSE(pState->m_pFile);
    pState->m_pFile = عدم;
  }
#جيڪڏهن_پورو // #ifndef MINIZ_NO_STDIO

  إذا ((pZip->m_pWrite == mz_zip_ڍير_write_func) && (pState->m_pMem))
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pState->m_pMem);
    pState->m_pMem = عدم;
  }

  pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
  pZip->m_zip_گهڻائي = MZ_ZIP_گهڻائي_INVALID;
  أرجع حالت;
}

#جيڪڏهن_وصف_نه_ٿيل MINIZ_NO_STDIO
mz_bool mz_zip_جوڙيو_mem_منزل_archive_file_اندريون_رکو(ثابت حرف *pZip_filename, ثابت حرف *pArchive_name, ثابت فراغ *pBuf, size_t buf_سائيز_2, ثابت فراغ *pComment, mz_uint16 comment_سائيز, mz_uint level_and_flags)
{
  mz_bool حالت, created_new_archive = MZ_FALSE;
  mz_zip_archive zip_archive;
  بنية MZ_FILE_STAT_STRUCT file_stat;
  MZ_CLEAR_OBJ(zip_archive);
  إذا ((صحيح)level_and_flags < 0)
     level_and_flags = MZ_DEFAULT_LEVEL;
  إذا ((!pZip_filename) || (!pArchive_name) || ((buf_سائيز_2) && (!pBuf)) || ((comment_سائيز) && (!pComment)) || ((level_and_flags & 0xF) > MZ_UBER_COMPRESSION))
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
    إذا (!mz_zip_reader_init_file(&zip_archive, pZip_filename, level_and_flags | MZ_ZIP_FLAG_DO_NOT_ترتيب_ڏيو_CENTRAL_DIRECTORY))
      أرجع MZ_FALSE;
    إذا (!mz_zip_writer_init_from_reader(&zip_archive, pZip_filename))
    {
      mz_zip_reader_پڇاڙي(&zip_archive);
      أرجع MZ_FALSE;
    }
  }
  حالت = mz_zip_writer_جوڙيو_mem_ex(&zip_archive, pArchive_name, pBuf, buf_سائيز_2, pComment, comment_سائيز, level_and_flags, 0, 0);
  // Always finalize, even if adding failed for some reason, so we have a valid central directory. (This may not always succeed, but we can try.)
  إذا (!mz_zip_writer_finalize_archive(&zip_archive))
    حالت = MZ_FALSE;
  إذا (!mz_zip_writer_پڇاڙي(&zip_archive))
    حالت = MZ_FALSE;
  إذا ((!حالت) && (created_new_archive))
  {
    // It's a new archive and something went wrong, so just delete it.
    صحيح ignored_حالت = MZ_DELETE_FILE(pZip_filename);
    (فراغ)ignored_حالت;
  }
  أرجع حالت;
}

فراغ *mz_zip_ڪڍو_archive_file_منزل_ڍير(ثابت حرف *pZip_filename, ثابت حرف *pArchive_name, size_t *p_سائيز, mz_uint flags)
{
  صحيح file_اشاريو;
  mz_zip_archive zip_archive;
  فراغ *p = عدم;

  إذا (p_سائيز)
    *p_سائيز = 0;

  إذا ((!pZip_filename) || (!pArchive_name))
    أرجع عدم;

  MZ_CLEAR_OBJ(zip_archive);
  إذا (!mz_zip_reader_init_file(&zip_archive, pZip_filename, flags | MZ_ZIP_FLAG_DO_NOT_ترتيب_ڏيو_CENTRAL_DIRECTORY))
    أرجع عدم;

  إذا ((file_اشاريو = mz_zip_reader_locate_file(&zip_archive, pArchive_name, عدم, flags)) >= 0)
    p = mz_zip_reader_ڪڍو_منزل_ڍير(&zip_archive, file_اشاريو, p_سائيز, flags);

  mz_zip_reader_پڇاڙي(&zip_archive);
  أرجع p;
}

#جيڪڏهن_پورو // #ifndef MINIZ_NO_STDIO

#جيڪڏهن_پورو // #ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

#جيڪڏهن_پورو // #ifndef MINIZ_NO_ARCHIVE_APIS

#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل _MSC_VER
#هدايت warning (ڪڍو)
#جيڪڏهن_پورو

#جيڪڏهن_پورو // MINIZ_HEADER_FILE_ONLY

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

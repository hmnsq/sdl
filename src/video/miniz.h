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

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_ਸਿਰਲੇਖ_INCLUDED
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MINIZ_ਸਿਰਲੇਖ_INCLUDED

/*#include <stdlib.h>*/

// Defines to completely disable specific portions of miniz.c:
// If all macros here are defined the only functionality remaining will be CRC-32, adler-32, tinfl, and tdefl.

// Define MINIZ_NO_STDIO to disable all usage and any functions which rely on stdio for file I/O.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MINIZ_NO_STDIO

// If MINIZ_NO_TIME is specified then the ZIP archive functions will not be able to get the current time, or
// get/set file times, and the C run-time funcs that get/set times won't be called.
// The current downside is the times written to your archives will be from 1979.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MINIZ_NO_ਸਮਾਂ

// Define MINIZ_NO_DEFLATE_APIS to disable all compression API's.
//#define MINIZ_NO_DEFLATE_APIS

// Define MINIZ_NO_INFLATE_APIS to disable all decompression API's.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MINIZ_NO_INFLATE_APIS

// Define MINIZ_NO_ARCHIVE_APIS to disable all ZIP archive API's.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MINIZ_NO_ARCHIVE_APIS

// Define MINIZ_NO_ARCHIVE_APIS to disable all writing related ZIP archive API's.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MINIZ_NO_ARCHIVE_WRITING_APIS

// Define MINIZ_NO_ZLIB_APIS to remove all ZLIB-style compression/decompression API's.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MINIZ_NO_ZLIB_APIS

// Define MINIZ_NO_ZLIB_COMPATIBLE_NAME to disable zlib names, to prevent conflicts against stock zlib.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MINIZ_NO_ZLIB_COMPATIBLE_ਨਾਂ

// Define MINIZ_NO_MALLOC to disable all calls to malloc, free, and realloc.
// Note if MINIZ_NO_MALLOC is defined then the user must always provide custom user alloc/free/realloc
// callbacks to the zlib and archive API's, and a few stand-alone helper API's which don't provide custom user
// functions (such as tdefl_compress_mem_to_heap() and tinfl_decompress_mem_to_heap()) won't work.
//#define MINIZ_NO_MALLOC
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MINIZ_SDL_MALLOC

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_INFLATE_APIS
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MINIZ_NO_ARCHIVE_APIS
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_DEFLATE_APIS
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MINIZ_NO_ARCHIVE_WRITING_APIS
#ਜੇ_ਅੰਤ

// Define MINIZ_STATIC_FUNCTIONS to make all functions static. You probably
// want this if you're using miniz in a library
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MINIZ_STATIC_FUNCTIONS

#ਜੇ defined(__TINYC__) && (defined(__linux) || defined(__linux__))
  // TODO: Work around "error: include file 'sys\utime.h' when compiling with tcc on Linux
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MINIZ_NO_ਸਮਾਂ
#ਜੇ_ਅੰਤ

#ਜੇ !defined(MINIZ_NO_ਸਮਾਂ) && !defined(MINIZ_NO_ARCHIVE_APIS)
  #ਅਨ੍ਤਰ੍ਭਾਵ <time.h>
#ਜੇ_ਅੰਤ

#ਜੇ defined(_M_IX86) || defined(_M_X64) || defined(__i386__) || defined(__i386) || defined(__i486__) || defined(__i486) || defined(i386) || defined(__ia64__) || defined(__x86_64__)
// MINIZ_X86_OR_X64_CPU is only used to help set the below macros.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MINIZ_X86_OR_X64_CPU 1
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_LITTLE_ENDIAN /* if not defined by SDL */
#ਜੇ (__BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__) || MINIZ_X86_OR_X64_CPU
// Set MINIZ_LITTLE_ENDIAN to 1 if the processor is little endian.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MINIZ_LITTLE_ENDIAN 1
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ // MINIZ_LITTLE_ENDIAN /* if not defined by SDL */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_USE_UNALIGNED_LOADS_AND_STORES
#ਜੇ MINIZ_X86_OR_X64_CPU
// Set MINIZ_USE_UNALIGNED_LOADS_AND_STORES to 1 on CPU's that permit efficient integer loads and stores from unaligned addresses.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MINIZ_USE_UNALIGNED_LOADS_AND_STORES 1
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ // MINIZ_USE_UNALIGNED_LOADS_AND_STORES

#ਜੇ defined(_M_X64) || defined(_WIN64) || defined(__MINGW64__) || defined(_LP64) || defined(__LP64__) || defined(__ia64__) || defined(__x86_64__)
// Set MINIZ_HAS_64BIT_REGISTERS to 1 if operations on 64-bit integers are reasonably fast (and don't involve compiler generated calls to helper functions).
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MINIZ_HAS_64_ਦੋਆਧਾਰੀ_ਅੰਕ_REGISTERS 1
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ MINIZ_STATIC_FUNCTIONS
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MINIZ_STATIC ਸਥਿਰ
#ਨਹੀਂਤਾਂ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MINIZ_STATIC
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ

// ------------------- zlib-style API Definitions.

// For more compatibility with zlib, miniz.c uses unsigned long for some parameters/struct members. Beware: mz_ulong can be either 32 or 64-bits!
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ mz_ulong;

// mz_free() internally uses the MZ_FREE() macro (which by default calls free() unless you've modified the MZ_MALLOC macro) to release a block allocated from the heap.
MINIZ_STATIC ਖਾਲੀ mz_free(ਖਾਲੀ *p);

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_ADLER32_INIT (1)
// mz_adler32() returns the initial adler-32 value to use when called with ptr==NULL.
MINIZ_STATIC mz_ulong mz_adler32(mz_ulong adler, ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *ptr, size_t buf_len);

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_ਚੱਕਰੀ_ਜਾਂਚ_32_INIT (0)
// mz_crc32() returns the initial CRC-32 value to use when called with ptr==NULL.
MINIZ_STATIC mz_ulong mz_ਚੱਕਰੀ_ਜਾਂਚ_32(mz_ulong ਚੱਕਰੀ_ਜਾਂਚ, ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *ptr, size_t buf_len);

// Compression strategies.
ਗਿਣਤੀ { MZ_DEFAULT_STRATEGY = 0, MZ_FILTERED = 1, MZ_HUFFMAN_ONLY = 2, MZ_RLE = 3, MZ_FIXED = 4 };

//ਵਿਧੀ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_DEFLATED 8

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_ZLIB_APIS

// Heap allocation callbacks.
// Note that mz_alloc_func parameter types purpsosely differ from zlib's: items/size is size_t, not unsigned long.
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ *(*mz_alloc_func)(ਖਾਲੀ *opaque, size_t ਚੀਜ਼ਾਂ, size_t ਮਾਪ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (*mz_free_func)(ਖਾਲੀ *opaque, ਖਾਲੀ *ਪਤਾ);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ *(*mz_realloc_func)(ਖਾਲੀ *opaque, ਖਾਲੀ *ਪਤਾ, size_t ਚੀਜ਼ਾਂ, size_t ਮਾਪ);

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_ਸੰਸਕਰਣ          "9.1.15"
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_VERNUM           0x91F0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_VER_MAJOR        9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_VER_MINOR        1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_VER_REVISION     15
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_VER_SUBREVISION  0

// Flush values. For typical usage you only need MZ_NO_FLUSH and MZ_FINISH. The other values are for advanced use (refer to the zlib docs).
ਗਿਣਤੀ { MZ_NO_FLUSH = 0, MZ_PARTIAL_FLUSH = 1, MZ_SYNC_FLUSH = 2, MZ_ਭਰਿਆ_FLUSH = 3, MZ_ਅੰਤ = 4, MZ_ਖੰਡ = 5 };

// Return status codes. MZ_PARAM_ERROR is non-standard.
ਗਿਣਤੀ { MZ_OK = 0, MZ_ਧਾਰਾ_ਸਿਰਾ = 1, MZ_NEED_DICT = 2, MZ_ERRNO = -1, MZ_ਧਾਰਾ_ERROR = -2, MZ_ਅੰਕੜੇ_ERROR = -3, MZ_MEM_ERROR = -4, MZ_BUF_ERROR = -5, MZ_ਸੰਸਕਰਣ_ERROR = -6, MZ_PARAM_ERROR = -10000 };

// Compression levels: 0-9 are the standard zlib-style levels, 10 is best possible compression (not zlib compatible, and may be very slow), MZ_DEFAULT_COMPRESSION=MZ_DEFAULT_LEVEL.
ਗਿਣਤੀ { MZ_NO_COMPRESSION = 0, MZ_ਉੱਤਮ_ਰਫਤਾਰ = 1, MZ_ਉੱਤਮ_COMPRESSION = 9, MZ_UBER_COMPRESSION = 10, MZ_DEFAULT_LEVEL = 6, MZ_DEFAULT_COMPRESSION = -1 };

// Window bits
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_DEFAULT_ਖਿੜਕੀ_ਬਿੱਟ 15

ਬਣਤਰ mz_ਅੰਦਰੂਨੀ_state;

// Compression/decompression stream struct.
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ mz_ਧਾਰਾ_s
{
  ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *ਅਗਲਾ_ਵਿੱਚ;     // pointer to next byte to read
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ avail_ਵਿੱਚ;            // number of bytes available at next_in
  mz_ulong ਕੁੱਲ_ਵਿੱਚ;                // total number of bytes consumed so far

  ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *ਅਗਲਾ_ਬਾਹਰਲਾ;          // pointer to next byte to write
  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ avail_ਬਾਹਰਲਾ;           // number of bytes that can be written to next_out
  mz_ulong ਕੁੱਲ_ਬਾਹਰਲਾ;               // total number of bytes produced so far

  ਅੱਖਰ *ਸੁਨੇਹਾ_2;                        // error msg (unused)
  ਬਣਤਰ mz_ਅੰਦਰੂਨੀ_state *state;  // internal state, allocated by zalloc/zfree

  mz_alloc_func zalloc;             // optional heap allocation function (defaults to malloc)
  mz_free_func zfree;               // optional heap free function (defaults to free)
  ਖਾਲੀ *opaque;                     // heap alloc function user pointer

  ਪੂਰਨ ਅੰਕੜੇ_type;                    // data_type (unused)
  mz_ulong adler;                   // adler32 of the source or uncompressed data
  mz_ulong reserved;                // not used
} mz_ਧਾਰਾ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ mz_ਧਾਰਾ *mz_streamp;

// Returns the version string of miniz.c.
MINIZ_STATIC ਅਚਲ ਅੱਖਰ *mz_ਸੰਸਕਰਣ(ਖਾਲੀ);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_DEFLATE_APIS

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
MINIZ_STATIC ਪੂਰਨ mz_deflateInit(mz_streamp p_ਧਾਰਾ, ਪੂਰਨ level);

// mz_deflateInit2() is like mz_deflate(), except with more control:
// Additional parameters:
//   method must be MZ_DEFLATED
//   window_bits must be MZ_DEFAULT_WINDOW_BITS (to wrap the deflate stream with zlib header/adler-32 footer) or -MZ_DEFAULT_WINDOW_BITS (raw deflate/no header or footer)
//   mem_level must be between [1, 9] (it's checked but ignored by miniz.c)
MINIZ_STATIC ਪੂਰਨ mz_deflateInit2(mz_streamp p_ਧਾਰਾ, ਪੂਰਨ level, ਪੂਰਨ ਵਿਧੀ, ਪੂਰਨ ਖਿੜਕੀ_ਬਿੱਟ, ਪੂਰਨ mem_level, ਪੂਰਨ strategy);

// Quickly resets a compressor without having to reallocate anything. Same as calling mz_deflateEnd() followed by mz_deflateInit()/mz_deflateInit2().
MINIZ_STATIC ਪੂਰਨ mz_deflateReset(mz_streamp p_ਧਾਰਾ);

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
MINIZ_STATIC ਪੂਰਨ mz_deflate(mz_streamp p_ਧਾਰਾ, ਪੂਰਨ flush);

// mz_deflateEnd() deinitializes a compressor:
// Return values:
//  MZ_OK on success.
//  MZ_STREAM_ERROR if the stream is bogus.
MINIZ_STATIC ਪੂਰਨ mz_deflate_ਸਿਰਾ(mz_streamp p_ਧਾਰਾ);

// mz_deflateBound() returns a (very) conservative upper bound on the amount of data that could be generated by deflate(), assuming flush is set to only MZ_NO_FLUSH or MZ_FINISH.
MINIZ_STATIC mz_ulong mz_deflateBound(mz_streamp p_ਧਾਰਾ, mz_ulong ਸਰੋਤ_len);

// Single-call compression functions mz_compress() and mz_compress2():
// Returns MZ_OK on success, or one of the error codes from mz_deflate() on failure.
MINIZ_STATIC ਪੂਰਨ mz_compress(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *pDest, mz_ulong *pDest_len, ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *p_ਸਰੋਤ, mz_ulong ਸਰੋਤ_len);
MINIZ_STATIC ਪੂਰਨ mz_compress2(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *pDest, mz_ulong *pDest_len, ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *p_ਸਰੋਤ, mz_ulong ਸਰੋਤ_len, ਪੂਰਨ level);

// mz_compressBound() returns a (very) conservative upper bound on the amount of data that could be generated by calling mz_compress().
MINIZ_STATIC mz_ulong mz_compressBound(mz_ulong ਸਰੋਤ_len);

#ਜੇ_ਅੰਤ /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_INFLATE_APIS

// Initializes a decompressor.
MINIZ_STATIC ਪੂਰਨ mz_inflateInit(mz_streamp p_ਧਾਰਾ);

// mz_inflateInit2() is like mz_inflateInit() with an additional option that controls the window size and whether or not the stream has been wrapped with a zlib header/footer:
// window_bits must be MZ_DEFAULT_WINDOW_BITS (to parse zlib header/footer) or -MZ_DEFAULT_WINDOW_BITS (raw deflate).
MINIZ_STATIC ਪੂਰਨ mz_inflateInit2(mz_streamp p_ਧਾਰਾ, ਪੂਰਨ ਖਿੜਕੀ_ਬਿੱਟ);

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
MINIZ_STATIC ਪੂਰਨ mz_inflate(mz_streamp p_ਧਾਰਾ, ਪੂਰਨ flush);

// Deinitializes a decompressor.
MINIZ_STATIC ਪੂਰਨ mz_inflate_ਸਿਰਾ(mz_streamp p_ਧਾਰਾ);

// Single-call decompression.
// Returns MZ_OK on success, or one of the error codes from mz_inflate() on failure.
MINIZ_STATIC ਪੂਰਨ mz_uncompress(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *pDest, mz_ulong *pDest_len, ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *p_ਸਰੋਤ, mz_ulong ਸਰੋਤ_len);
#ਜੇ_ਅੰਤ /*#ifndef MINIZ_NO_INFLATE_APIS*/

// Returns a string description of the specified error code, or NULL if the error code is invalid.
MINIZ_STATIC ਅਚਲ ਅੱਖਰ *mz_error(ਪੂਰਨ err);

// Redefine zlib-compatible names to miniz equivalents, so miniz.c can be used as a drop-in replacement for the subset of zlib that miniz.c supports.
// Define MINIZ_NO_ZLIB_COMPATIBLE_NAMES to disable zlib-compatibility if you use zlib in the same project.
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_ZLIB_COMPATIBLE_ਨਾਂ
  ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ Byte;
  ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ uInt;
  ਕਿਸਮਪਰਿਭਾਸ਼ਾ mz_ulong uLong;
  ਕਿਸਮਪਰਿਭਾਸ਼ਾ Byte Bytef;
  ਕਿਸਮਪਰਿਭਾਸ਼ਾ uInt uIntf;
  ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਅੱਖਰ charf;
  ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੂਰਨ intf;
  ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ *voidpf;
  ਕਿਸਮਪਰਿਭਾਸ਼ਾ uLong uLongf;
  ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ *voidp;
  ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ *ਅਚਲ voidpc;
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Z_NULL                0
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Z_NO_FLUSH            MZ_NO_FLUSH
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Z_PARTIAL_FLUSH       MZ_PARTIAL_FLUSH
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Z_SYNC_FLUSH          MZ_SYNC_FLUSH
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Z_ਭਰਿਆ_FLUSH          MZ_ਭਰਿਆ_FLUSH
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Z_ਅੰਤ              MZ_ਅੰਤ
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Z_ਖੰਡ               MZ_ਖੰਡ
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Z_OK                  MZ_OK
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Z_ਧਾਰਾ_ਸਿਰਾ          MZ_ਧਾਰਾ_ਸਿਰਾ
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Z_NEED_DICT           MZ_NEED_DICT
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Z_ERRNO               MZ_ERRNO
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Z_ਧਾਰਾ_ERROR        MZ_ਧਾਰਾ_ERROR
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Z_ਅੰਕੜੇ_ERROR          MZ_ਅੰਕੜੇ_ERROR
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Z_MEM_ERROR           MZ_MEM_ERROR
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Z_BUF_ERROR           MZ_BUF_ERROR
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Z_ਸੰਸਕਰਣ_ERROR       MZ_ਸੰਸਕਰਣ_ERROR
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Z_PARAM_ERROR         MZ_PARAM_ERROR
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Z_NO_COMPRESSION      MZ_NO_COMPRESSION
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Z_ਉੱਤਮ_ਰਫਤਾਰ          MZ_ਉੱਤਮ_ਰਫਤਾਰ
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Z_ਉੱਤਮ_COMPRESSION    MZ_ਉੱਤਮ_COMPRESSION
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Z_DEFAULT_COMPRESSION MZ_DEFAULT_COMPRESSION
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Z_DEFAULT_STRATEGY    MZ_DEFAULT_STRATEGY
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Z_FILTERED            MZ_FILTERED
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Z_HUFFMAN_ONLY        MZ_HUFFMAN_ONLY
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Z_RLE                 MZ_RLE
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Z_FIXED               MZ_FIXED
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Z_DEFLATED            MZ_DEFLATED
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ Z_DEFAULT_ਖਿੜਕੀ_ਬਿੱਟ MZ_DEFAULT_ਖਿੜਕੀ_ਬਿੱਟ
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ alloc_func            mz_alloc_func
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ free_func             mz_free_func
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਅੰਦਰੂਨੀ_state        mz_ਅੰਦਰੂਨੀ_state
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ z_ਧਾਰਾ              mz_ਧਾਰਾ
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_DEFLATE_APIS
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ deflateInit           mz_deflateInit
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ deflateInit2          mz_deflateInit2
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ deflateReset          mz_deflateReset
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ deflate               mz_deflate
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ deflate_ਸਿਰਾ            mz_deflate_ਸਿਰਾ
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ deflateBound          mz_deflateBound
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ compress              mz_compress
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ compress2             mz_compress2
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ compressBound         mz_compressBound
#ਜੇ_ਅੰਤ /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_INFLATE_APIS
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ inflateInit           mz_inflateInit
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ inflateInit2          mz_inflateInit2
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ inflate               mz_inflate
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ inflate_ਸਿਰਾ            mz_inflate_ਸਿਰਾ
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ uncompress            mz_uncompress
#ਜੇ_ਅੰਤ /*#ifndef MINIZ_NO_INFLATE_APIS*/
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ਚੱਕਰੀ_ਜਾਂਚ_32                 mz_ਚੱਕਰੀ_ਜਾਂਚ_32
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ adler32               mz_adler32
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_WBITS             15
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MAX_MEM_LEVEL         9
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ zError                mz_error
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ZLIB_ਸੰਸਕਰਣ          MZ_ਸੰਸਕਰਣ
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ZLIB_VERNUM           MZ_VERNUM
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ZLIB_VER_MAJOR        MZ_VER_MAJOR
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ZLIB_VER_MINOR        MZ_VER_MINOR
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ZLIB_VER_REVISION     MZ_VER_REVISION
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ZLIB_VER_SUBREVISION  MZ_VER_SUBREVISION
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ zlib_ਸੰਸਕਰਣ           mz_ਸੰਸਕਰਣ
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ zlib_ਸੰਸਕਰਣ_2          mz_ਸੰਸਕਰਣ()
#ਜੇ_ਅੰਤ // #ifndef MINIZ_NO_ZLIB_COMPATIBLE_NAMES

#ਜੇ_ਅੰਤ // MINIZ_NO_ZLIB_APIS

// ------------------- Types and macros

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ mz_uint8;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਨਿਸ਼ਾਨੀਵਾਲਾ ਛੋਟਾ mz_int16;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ mz_uint16;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ mz_uint32;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ mz_uint;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਲੰਮਾ ਲੰਮਾ mz_int64;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਲੰਮਾ mz_uint64;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੂਰਨ mz_bool;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FALSE (0)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_TRUE (1)

// An attempt to work around MSVC's spammy "warning C4127: conditional expression is constant" message.
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _MSC_VER
   #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_MACRO_ਸਿਰਾ ਜਦੋਂ (0, 0)
#ਨਹੀਂਤਾਂ
   #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_MACRO_ਸਿਰਾ ਜਦੋਂ (0)
#ਜੇ_ਅੰਤ

// ------------------- ZIP archive reading/writing

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_ARCHIVE_APIS

ਗਿਣਤੀ
{
  MZ_ZIP_MAX_IO_BUF_ਮਾਪ = 64*1024,
  MZ_ZIP_MAX_ARCHIVE_FILENAME_ਮਾਪ = 260,
  MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_ਮਾਪ = 256
};

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
  mz_uint32 m_file_ਸੂਚਕਾਂਕ;
  mz_uint32 m_central_dir_ofs;
  mz_uint16 m_ਸੰਸਕਰਣ_made_by;
  mz_uint16 m_ਸੰਸਕਰਣ_needed;
  mz_uint16 m_ਦੋਆਧਾਰੀ_ਅੰਕ_flag;
  mz_uint16 m_ਵਿਧੀ;
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_ਸਮਾਂ
  ਸਮਾਂ_t m_ਸਮਾਂ;
#ਜੇ_ਅੰਤ
  mz_uint32 m_ਚੱਕਰੀ_ਜਾਂਚ_32;
  mz_uint64 m_comp_ਮਾਪ;
  mz_uint64 m_uncomp_ਮਾਪ;
  mz_uint16 m_ਅੰਦਰੂਨੀ_attr;
  mz_uint32 m_external_attr;
  mz_uint64 m_local_ਸਿਰਲੇਖ_ofs;
  mz_uint32 m_comment_ਮਾਪ;
  ਅੱਖਰ m_filename[MZ_ZIP_MAX_ARCHIVE_FILENAME_ਮਾਪ];
  ਅੱਖਰ m_comment[MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_ਮਾਪ];
} mz_zip_archive_file_stat;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ size_t (*mz_file_read_func)(ਖਾਲੀ *pOpaque, mz_uint64 file_ofs, ਖਾਲੀ *pBuf, size_t n);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ size_t (*mz_file_write_func)(ਖਾਲੀ *pOpaque, mz_uint64 file_ofs, ਅਚਲ ਖਾਲੀ *pBuf, size_t n);

ਬਣਤਰ mz_zip_ਅੰਦਰੂਨੀ_state_ਟੈਗ;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ mz_zip_ਅੰਦਰੂਨੀ_state_ਟੈਗ mz_zip_ਅੰਦਰੂਨੀ_state;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ
{
  MZ_ZIP_ਬਹੁਲਕ_INVALID = 0,
  MZ_ZIP_ਬਹੁਲਕ_READING = 1,
  MZ_ZIP_ਬਹੁਲਕ_WRITING = 2,
  MZ_ZIP_ਬਹੁਲਕ_WRITING_HAS_BEEN_FINALIZED = 3
} mz_zip_ਬਹੁਲਕ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ mz_zip_archive_ਟੈਗ
{
  mz_uint64 m_archive_ਮਾਪ;
  mz_uint64 m_central_directory_file_ofs;
  mz_uint m_ਕੁੱਲ_files;
  mz_zip_ਬਹੁਲਕ m_zip_ਬਹੁਲਕ;

  mz_uint m_file_ਵਿੱਥ_alignment;

  mz_alloc_func m_pAlloc;
  mz_free_func m_pFree;
  mz_realloc_func m_pRealloc;
  ਖਾਲੀ *m_pAlloc_opaque;

  mz_file_read_func m_pRead;
  mz_file_write_func m_pWrite;
  ਖਾਲੀ *m_pIO_opaque;

  mz_zip_ਅੰਦਰੂਨੀ_state *m_pState;

} mz_zip_archive;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ
{
  MZ_ZIP_FLAG_CASE_SENSITIVE                = 0x0100,
  MZ_ZIP_FLAG_IGNORE_ਰਸਤਾ                   = 0x0200,
  MZ_ZIP_FLAG_COMPRESSED_ਅੰਕੜੇ               = 0x0400,
  MZ_ZIP_FLAG_DO_NOT_ਛਾਂਟੋ_CENTRAL_DIRECTORY = 0x0800
} mz_zip_flags;

// ZIP archive reading

// Inits a ZIP archive reader.
// These functions read and validate the archive's central directory.
MINIZ_STATIC mz_bool mz_zip_reader_init(mz_zip_archive *pZip, mz_uint64 ਮਾਪ, mz_uint32 flags);
MINIZ_STATIC mz_bool mz_zip_reader_init_mem(mz_zip_archive *pZip, ਅਚਲ ਖਾਲੀ *pMem, size_t ਮਾਪ, mz_uint32 flags);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_STDIO
MINIZ_STATIC mz_bool mz_zip_reader_init_file(mz_zip_archive *pZip, ਅਚਲ ਅੱਖਰ *pFilename, mz_uint32 flags);
#ਜੇ_ਅੰਤ

// Returns the total number of files in the archive.
MINIZ_STATIC mz_uint mz_zip_reader_get_ਅੰਕ_files(mz_zip_archive *pZip);

// Returns detailed information about an archive file entry.
MINIZ_STATIC mz_bool mz_zip_reader_file_stat(mz_zip_archive *pZip, mz_uint file_ਸੂਚਕਾਂਕ, mz_zip_archive_file_stat *pStat);

// Determines if an archive file entry is a directory entry.
MINIZ_STATIC mz_bool mz_zip_reader_is_file_a_directory(mz_zip_archive *pZip, mz_uint file_ਸੂਚਕਾਂਕ);
MINIZ_STATIC mz_bool mz_zip_reader_is_file_encrypted(mz_zip_archive *pZip, mz_uint file_ਸੂਚਕਾਂਕ);

// Retrieves the filename of an archive file entry.
// Returns the number of bytes written to pFilename, or if filename_buf_size is 0 this function returns the number of bytes needed to fully store the filename.
MINIZ_STATIC mz_uint mz_zip_reader_get_filename(mz_zip_archive *pZip, mz_uint file_ਸੂਚਕਾਂਕ, ਅੱਖਰ *pFilename, mz_uint filename_buf_ਮਾਪ);

// Attempts to locates a file in the archive's central directory.
// Valid flags: MZ_ZIP_FLAG_CASE_SENSITIVE, MZ_ZIP_FLAG_IGNORE_PATH
// Returns -1 if the file cannot be found.
MINIZ_STATIC ਪੂਰਨ mz_zip_reader_locate_file(mz_zip_archive *pZip, ਅਚਲ ਅੱਖਰ *pName, ਅਚਲ ਅੱਖਰ *pComment, mz_uint flags);

// Extracts a archive file to a memory buffer using no memory allocation.
MINIZ_STATIC mz_bool mz_zip_reader_ਕੱਢੋ_ਮੰਜ਼ਿਲ_mem_no_alloc(mz_zip_archive *pZip, mz_uint file_ਸੂਚਕਾਂਕ, ਖਾਲੀ *pBuf, size_t buf_ਮਾਪ_2, mz_uint flags, ਖਾਲੀ *pUser_read_buf, size_t user_read_buf_ਮਾਪ);
MINIZ_STATIC mz_bool mz_zip_reader_ਕੱਢੋ_file_ਮੰਜ਼ਿਲ_mem_no_alloc(mz_zip_archive *pZip, ਅਚਲ ਅੱਖਰ *pFilename, ਖਾਲੀ *pBuf, size_t buf_ਮਾਪ_2, mz_uint flags, ਖਾਲੀ *pUser_read_buf, size_t user_read_buf_ਮਾਪ);

// Extracts a archive file to a memory buffer.
MINIZ_STATIC mz_bool mz_zip_reader_ਕੱਢੋ_ਮੰਜ਼ਿਲ_mem(mz_zip_archive *pZip, mz_uint file_ਸੂਚਕਾਂਕ, ਖਾਲੀ *pBuf, size_t buf_ਮਾਪ_2, mz_uint flags);
MINIZ_STATIC mz_bool mz_zip_reader_ਕੱਢੋ_file_ਮੰਜ਼ਿਲ_mem(mz_zip_archive *pZip, ਅਚਲ ਅੱਖਰ *pFilename, ਖਾਲੀ *pBuf, size_t buf_ਮਾਪ_2, mz_uint flags);

// Extracts a archive file to a dynamically allocated heap buffer.
MINIZ_STATIC ਖਾਲੀ *mz_zip_reader_ਕੱਢੋ_ਮੰਜ਼ਿਲ_ਢੇਰ(mz_zip_archive *pZip, mz_uint file_ਸੂਚਕਾਂਕ, size_t *p_ਮਾਪ, mz_uint flags);
MINIZ_STATIC ਖਾਲੀ *mz_zip_reader_ਕੱਢੋ_file_ਮੰਜ਼ਿਲ_ਢੇਰ(mz_zip_archive *pZip, ਅਚਲ ਅੱਖਰ *pFilename, size_t *p_ਮਾਪ, mz_uint flags);

// Extracts a archive file using a callback function to output the file's data.
MINIZ_STATIC mz_bool mz_zip_reader_ਕੱਢੋ_ਮੰਜ਼ਿਲ_callback(mz_zip_archive *pZip, mz_uint file_ਸੂਚਕਾਂਕ, mz_file_write_func pCallback, ਖਾਲੀ *pOpaque, mz_uint flags);
MINIZ_STATIC mz_bool mz_zip_reader_ਕੱਢੋ_file_ਮੰਜ਼ਿਲ_callback(mz_zip_archive *pZip, ਅਚਲ ਅੱਖਰ *pFilename, mz_file_write_func pCallback, ਖਾਲੀ *pOpaque, mz_uint flags);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_STDIO
// Extracts a archive file to a disk file and sets its last accessed and modified times.
// This function only extracts files, not archive directory records.
MINIZ_STATIC mz_bool mz_zip_reader_ਕੱਢੋ_ਮੰਜ਼ਿਲ_file(mz_zip_archive *pZip, mz_uint file_ਸੂਚਕਾਂਕ, ਅਚਲ ਅੱਖਰ *pDst_filename, mz_uint flags);
MINIZ_STATIC mz_bool mz_zip_reader_ਕੱਢੋ_file_ਮੰਜ਼ਿਲ_file(mz_zip_archive *pZip, ਅਚਲ ਅੱਖਰ *pArchive_filename, ਅਚਲ ਅੱਖਰ *pDst_filename, mz_uint flags);
#ਜੇ_ਅੰਤ

// Ends archive reading, freeing all allocations, and closing the input archive file if mz_zip_reader_init_file() was used.
MINIZ_STATIC mz_bool mz_zip_reader_ਸਿਰਾ(mz_zip_archive *pZip);

// ZIP archive writing

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_ARCHIVE_WRITING_APIS

// Inits a ZIP archive writer.
MINIZ_STATIC mz_bool mz_zip_writer_init(mz_zip_archive *pZip, mz_uint64 existing_ਮਾਪ);
MINIZ_STATIC mz_bool mz_zip_writer_init_ਢੇਰ(mz_zip_archive *pZip, size_t ਮਾਪ_ਮੰਜ਼ਿਲ_reserve_at_beginning, size_t initial_ਵੰਡ_ਮਾਪ);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_STDIO
MINIZ_STATIC mz_bool mz_zip_writer_init_file(mz_zip_archive *pZip, ਅਚਲ ਅੱਖਰ *pFilename, mz_uint64 ਮਾਪ_ਮੰਜ਼ਿਲ_reserve_at_beginning);
#ਜੇ_ਅੰਤ

// Converts a ZIP archive reader object into a writer object, to allow efficient in-place file appends to occur on an existing archive.
// For archives opened using mz_zip_reader_init_file, pFilename must be the archive's filename so it can be reopened for writing. If the file can't be reopened, mz_zip_reader_end() will be called.
// For archives opened using mz_zip_reader_init_mem, the memory block must be growable using the realloc callback (which defaults to realloc unless you've overridden it).
// Finally, for archives opened using mz_zip_reader_init, the mz_zip_archive's user provided m_pWrite function cannot be NULL.
// Note: In-place archive modification is not recommended unless you know what you're doing, because if execution stops or something goes wrong before
// the archive is finalized the file's central directory will be hosed.
MINIZ_STATIC mz_bool mz_zip_writer_init_from_reader(mz_zip_archive *pZip, ਅਚਲ ਅੱਖਰ *pFilename);

// Adds the contents of a memory buffer to an archive. These functions record the current local time into the archive.
// To add a directory entry, call this method with an archive name ending in a forwardslash with empty buffer.
// level_and_flags - compression level (0-10, see MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or just set to MZ_DEFAULT_COMPRESSION.
MINIZ_STATIC mz_bool mz_zip_writer_ਜੋੜੋ_mem(mz_zip_archive *pZip, ਅਚਲ ਅੱਖਰ *pArchive_name, ਅਚਲ ਖਾਲੀ *pBuf, size_t buf_ਮਾਪ_2, mz_uint level_and_flags);
MINIZ_STATIC mz_bool mz_zip_writer_ਜੋੜੋ_mem_ex(mz_zip_archive *pZip, ਅਚਲ ਅੱਖਰ *pArchive_name, ਅਚਲ ਖਾਲੀ *pBuf, size_t buf_ਮਾਪ_2, ਅਚਲ ਖਾਲੀ *pComment, mz_uint16 comment_ਮਾਪ, mz_uint level_and_flags, mz_uint64 uncomp_ਮਾਪ, mz_uint32 uncomp_ਚੱਕਰੀ_ਜਾਂਚ_32);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_STDIO
// Adds the contents of a disk file to an archive. This function also records the disk file's modified time into the archive.
// level_and_flags - compression level (0-10, see MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or just set to MZ_DEFAULT_COMPRESSION.
MINIZ_STATIC mz_bool mz_zip_writer_ਜੋੜੋ_file(mz_zip_archive *pZip, ਅਚਲ ਅੱਖਰ *pArchive_name, ਅਚਲ ਅੱਖਰ *pSrc_filename, ਅਚਲ ਖਾਲੀ *pComment, mz_uint16 comment_ਮਾਪ, mz_uint level_and_flags);
#ਜੇ_ਅੰਤ

// Adds a file to an archive by fully cloning the data from another archive.
// This function fully clones the source file's compressed data (no recompression), along with its full filename, extra data, and comment fields.
MINIZ_STATIC mz_bool mz_zip_writer_ਜੋੜੋ_from_zip_reader(mz_zip_archive *pZip, mz_zip_archive *p_ਸਰੋਤ_zip, mz_uint file_ਸੂਚਕਾਂਕ);

// Finalizes the archive by writing the central directory records followed by the end of central directory record.
// After an archive is finalized, the only valid call on the mz_zip_archive struct is mz_zip_writer_end().
// An archive must be manually finalized by calling this function for it to be valid.
MINIZ_STATIC mz_bool mz_zip_writer_finalize_archive(mz_zip_archive *pZip);
MINIZ_STATIC mz_bool mz_zip_writer_finalize_ਢੇਰ_archive(mz_zip_archive *pZip, ਖਾਲੀ **pBuf, size_t *p_ਮਾਪ);

// Ends archive writing, freeing all allocations, and closing the output file if mz_zip_writer_init_file() was used.
// Note for the archive to be valid, it must have been finalized before ending.
MINIZ_STATIC mz_bool mz_zip_writer_ਸਿਰਾ(mz_zip_archive *pZip);

// Misc. high-level helper functions:

// mz_zip_add_mem_to_archive_file_in_place() efficiently (but not atomically) appends a memory blob to a ZIP archive.
// level_and_flags - compression level (0-10, see MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or just set to MZ_DEFAULT_COMPRESSION.
MINIZ_STATIC mz_bool mz_zip_ਜੋੜੋ_mem_ਮੰਜ਼ਿਲ_archive_file_ਵਿੱਚ_ਰੱਖੋ(ਅਚਲ ਅੱਖਰ *pZip_filename, ਅਚਲ ਅੱਖਰ *pArchive_name, ਅਚਲ ਖਾਲੀ *pBuf, size_t buf_ਮਾਪ_2, ਅਚਲ ਖਾਲੀ *pComment, mz_uint16 comment_ਮਾਪ, mz_uint level_and_flags);

// Reads a single file from an archive into a heap block.
// Returns NULL on failure.
MINIZ_STATIC ਖਾਲੀ *mz_zip_ਕੱਢੋ_archive_file_ਮੰਜ਼ਿਲ_ਢੇਰ(ਅਚਲ ਅੱਖਰ *pZip_filename, ਅਚਲ ਅੱਖਰ *pArchive_name, size_t *p_ਮਾਪ, mz_uint zip_flags);

#ਜੇ_ਅੰਤ // #ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

#ਜੇ_ਅੰਤ // #ifndef MINIZ_NO_ARCHIVE_APIS

// ------------------- Low-level Decompression API Definitions
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_INFLATE_APIS

// Decompression flags used by tinfl_decompress().
// TINFL_FLAG_PARSE_ZLIB_HEADER: If set, the input has a valid zlib header and ends with an adler32 checksum (it's a valid zlib stream). Otherwise, the input is a raw deflate stream.
// TINFL_FLAG_HAS_MORE_INPUT: If set, there are more input bytes available beyond the end of the supplied input buffer. If clear, the input buffer contains all remaining input.
// TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF: If set, the output buffer is large enough to hold the entire decompressed stream. If clear, the output buffer is at least the size of the dictionary (typically 32KB).
// TINFL_FLAG_COMPUTE_ADLER32: Force adler-32 checksum computation of the decompressed bytes.
ਗਿਣਤੀ
{
  TINFL_FLAG_PARSE_ZLIB_ਸਿਰਲੇਖ = 1,
  TINFL_FLAG_HAS_ਹੋਰ_ਨਿਵੇਸ਼ = 2,
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
MINIZ_STATIC ਖਾਲੀ *tinfl_decompress_mem_ਮੰਜ਼ਿਲ_ਢੇਰ(ਅਚਲ ਖਾਲੀ *pSrc_buf, size_t src_buf_len, size_t *p_ਬਾਹਰਲਾ_len, ਪੂਰਨ flags);

// tinfl_decompress_mem_to_mem() decompresses a block in memory to another block in memory.
// Returns TINFL_DECOMPRESS_MEM_TO_MEM_FAILED on failure, or the number of bytes written on success.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TINFL_DECOMPRESS_MEM_ਮੰਜ਼ਿਲ_MEM_FAILED ((size_t)(-1))
MINIZ_STATIC size_t tinfl_decompress_mem_ਮੰਜ਼ਿਲ_mem(ਖਾਲੀ *p_ਬਾਹਰਲਾ_buf, size_t ਬਾਹਰਲਾ_buf_len, ਅਚਲ ਖਾਲੀ *pSrc_buf, size_t src_buf_len, ਪੂਰਨ flags);

// tinfl_decompress_mem_to_callback() decompresses a block in memory to an internal 32KB buffer, and a user provided callback function will be called to flush the buffer.
// Returns 1 on success or 0 on failure.
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਪੂਰਨ (*tinfl_put_buf_func_ptr)(ਅਚਲ ਖਾਲੀ* pBuf, ਪੂਰਨ len, ਖਾਲੀ *pUser);
MINIZ_STATIC ਪੂਰਨ tinfl_decompress_mem_ਮੰਜ਼ਿਲ_callback(ਅਚਲ ਖਾਲੀ *p_ਵਿੱਚ_buf, size_t *p_ਵਿੱਚ_buf_ਮਾਪ, tinfl_put_buf_func_ptr pPut_buf_func, ਖਾਲੀ *pPut_buf_user, ਪੂਰਨ flags);

ਬਣਤਰ tinfl_decompressor_ਟੈਗ; ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ tinfl_decompressor_ਟੈਗ tinfl_decompressor;

// Max size of LZ dictionary.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TINFL_LZ_DICT_ਮਾਪ 32768

// Return status.
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ
{
  TINFL_ਸਥਿਤੀ_BAD_PARAM = -3,
  TINFL_ਸਥਿਤੀ_ADLER32_MISMATCH = -2,
  TINFL_ਸਥਿਤੀ_FAILED = -1,
  TINFL_ਸਥਿਤੀ_ਪੂਰਾ = 0,
  TINFL_ਸਥਿਤੀ_NEEDS_ਹੋਰ_ਨਿਵੇਸ਼ = 1,
  TINFL_ਸਥਿਤੀ_HAS_ਹੋਰ_OUTPUT = 2
} tinfl_ਸਥਿਤੀ;

// Initializes the decompressor to its initial state.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ tinfl_init(r) ਕਰੋ { (r)->m_state = 0; } MZ_MACRO_ਸਿਰਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ tinfl_get_adler32(r) (r)->m_check_adler32

// Main low-level decompressor coroutine function. This is the only function actually needed for decompression. All the other functions are just high-level helpers for improved usability.
// This is a universal API, i.e. it can be used as a building block to build any desired higher level decompression API. In the limit case, it can be called once per every byte input or output.
MINIZ_STATIC tinfl_ਸਥਿਤੀ tinfl_decompress(tinfl_decompressor *r, ਅਚਲ mz_uint8 *p_ਵਿੱਚ_buf_ਅਗਲਾ, size_t *p_ਵਿੱਚ_buf_ਮਾਪ, mz_uint8 *p_ਬਾਹਰਲਾ_buf_ਸ਼ੁਰੂ, mz_uint8 *p_ਬਾਹਰਲਾ_buf_ਅਗਲਾ, size_t *p_ਬਾਹਰਲਾ_buf_ਮਾਪ, ਅਚਲ mz_uint32 decomp_flags);

// Internal/private bits follow.
ਗਿਣਤੀ
{
  TINFL_MAX_HUFF_TABLES = 3, TINFL_MAX_HUFF_SYMBOLS_0 = 288, TINFL_MAX_HUFF_SYMBOLS_1 = 32, TINFL_MAX_HUFF_SYMBOLS_2 = 19,
  TINFL_FAST_LOOKUP_ਬਿੱਟ = 10, TINFL_FAST_LOOKUP_ਮਾਪ = 1 << TINFL_FAST_LOOKUP_ਬਿੱਟ
};

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
  mz_uint8 m_ਕੋਡ_ਮਾਪ[TINFL_MAX_HUFF_SYMBOLS_0];
  mz_int16 m_look_ਉੱਪਰ[TINFL_FAST_LOOKUP_ਮਾਪ], m_ਰੁੱਖ[TINFL_MAX_HUFF_SYMBOLS_0 * 2];
} tinfl_huff_ਸਾਰਣੀ;

#ਜੇ MINIZ_HAS_64_ਦੋਆਧਾਰੀ_ਅੰਕ_REGISTERS
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TINFL_USE_64_ਦੋਆਧਾਰੀ_ਅੰਕ_BITBUF 1
#ਜੇ_ਅੰਤ

#ਜੇ TINFL_USE_64_ਦੋਆਧਾਰੀ_ਅੰਕ_BITBUF
  ਕਿਸਮਪਰਿਭਾਸ਼ਾ mz_uint64 tinfl_ਦੋਆਧਾਰੀ_ਅੰਕ_buf_t;
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TINFL_BITBUF_ਮਾਪ (64)
#ਨਹੀਂਤਾਂ
  ਕਿਸਮਪਰਿਭਾਸ਼ਾ mz_uint32 tinfl_ਦੋਆਧਾਰੀ_ਅੰਕ_buf_t;
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TINFL_BITBUF_ਮਾਪ (32)
#ਜੇ_ਅੰਤ

ਬਣਤਰ tinfl_decompressor_ਟੈਗ
{
  mz_uint32 m_state, m_ਅੰਕ_ਬਿੱਟ, m_zhdr0, m_zhdr1, m_z_adler32, m_final, m_type, m_check_adler32, m_dist, m_counter, m_ਅੰਕ_extra, m_ਸਾਰਣੀ_sizes[TINFL_MAX_HUFF_TABLES];
  tinfl_ਦੋਆਧਾਰੀ_ਅੰਕ_buf_t m_ਦੋਆਧਾਰੀ_ਅੰਕ_buf;
  size_t m_dist_from_ਬਾਹਰਲਾ_buf_ਸ਼ੁਰੂ;
  tinfl_huff_ਸਾਰਣੀ m_tables[TINFL_MAX_HUFF_TABLES];
  mz_uint8 m_raw_ਸਿਰਲੇਖ[4], m_len_codes[TINFL_MAX_HUFF_SYMBOLS_0 + TINFL_MAX_HUFF_SYMBOLS_1 + 137];
};
#ਜੇ_ਅੰਤ /*#ifndef MINIZ_NO_INFLATE_APIS*/

// ------------------- Low-level Compression API Definitions
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_DEFLATE_APIS

// Set TDEFL_LESS_MEMORY to 1 to use less memory (compression will be slightly slower, and raw/dynamic blocks will be output more frequently).
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TDEFL_LESS_ਸਮ੍ਰਿਤੀ 0

// tdefl_init() compression flags logically OR'd together (low 12 bits contain the max. number of probes per dictionary search):
// TDEFL_DEFAULT_MAX_PROBES: The compressor defaults to 128 dictionary probes per dictionary search. 0=Huffman only, 1=Huffman+LZ (fastest/crap compression), 4095=Huffman+LZ (slowest/best compression).
ਗਿਣਤੀ
{
  TDEFL_HUFFMAN_ONLY = 0, TDEFL_DEFAULT_MAX_PROBES = 128, TDEFL_MAX_PROBES_ਨਕਾਬ = 0xFFF
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
ਗਿਣਤੀ
{
  TDEFL_WRITE_ZLIB_ਸਿਰਲੇਖ             = 0x01000,
  TDEFL_COMPUTE_ADLER32               = 0x02000,
  TDEFL_GREEDY_PARSING_FLAG           = 0x04000,
  TDEFL_NONDETERMINISTIC_PARSING_FLAG = 0x08000,
  TDEFL_RLE_MATCHES                   = 0x10000,
  TDEFL_FILTER_MATCHES                = 0x20000,
  TDEFL_FORCE_ALL_STATIC_ਖੰਡਾਂ       = 0x40000,
  TDEFL_FORCE_ALL_RAW_ਖੰਡਾਂ          = 0x80000
};

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_SDL_NOUNUSED
// High level compression functions:
// tdefl_compress_mem_to_heap() compresses a block in memory to a heap block allocated via malloc().
// On entry:
//  pSrc_buf, src_buf_len: Pointer and size of source block to compress.
//  flags: The max match finder probes (default is 128) logically OR'd against the above flags. Higher probes are slower but improve compression.
// On return:
//  Function returns a pointer to the compressed data, or NULL on failure.
//  *pOut_len will be set to the compressed data's size, which could be larger than src_buf_len on uncompressible data.
//  The caller must free() the returned block when it's no longer needed.
MINIZ_STATIC ਖਾਲੀ *tdefl_compress_mem_ਮੰਜ਼ਿਲ_ਢੇਰ(ਅਚਲ ਖਾਲੀ *pSrc_buf, size_t src_buf_len, size_t *p_ਬਾਹਰਲਾ_len, ਪੂਰਨ flags);

// tdefl_compress_mem_to_mem() compresses a block in memory to another block in memory.
// Returns 0 on failure.
MINIZ_STATIC size_t tdefl_compress_mem_ਮੰਜ਼ਿਲ_mem(ਖਾਲੀ *p_ਬਾਹਰਲਾ_buf, size_t ਬਾਹਰਲਾ_buf_len, ਅਚਲ ਖਾਲੀ *pSrc_buf, size_t src_buf_len, ਪੂਰਨ flags);
#ਜੇ_ਅੰਤ /* MINIZ_SDL_NOUNUSED */

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
MINIZ_STATIC ਖਾਲੀ *tdefl_write_image_ਮੰਜ਼ਿਲ_png_file_ਵਿੱਚ_ਸਮ੍ਰਿਤੀ_ex(ਅਚਲ ਖਾਲੀ *pImage, ਪੂਰਨ w, ਪੂਰਨ h, ਪੂਰਨ ਅੰਕ_chans, ਪੂਰਨ bpl, size_t *p_Len_ਬਾਹਰਲਾ, mz_uint level, mz_bool flip, mz_uint8 *plte, ਪੂਰਨ plte_ਮਾਪ, mz_uint8 *trns, ਪੂਰਨ trns_ਮਾਪ);
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_SDL_NOUNUSED
MINIZ_STATIC ਖਾਲੀ *tdefl_write_image_ਮੰਜ਼ਿਲ_png_file_ਵਿੱਚ_ਸਮ੍ਰਿਤੀ(ਅਚਲ ਖਾਲੀ *pImage, ਪੂਰਨ w, ਪੂਰਨ h, ਪੂਰਨ ਅੰਕ_chans, ਪੂਰਨ bpl, size_t *p_Len_ਬਾਹਰਲਾ);
#ਜੇ_ਅੰਤ

// Output stream interface. The compressor uses this interface to write compressed data. It'll typically be called TDEFL_OUT_BUF_SIZE at a time.
ਕਿਸਮਪਰਿਭਾਸ਼ਾ mz_bool (*tdefl_put_buf_func_ptr)(ਅਚਲ ਖਾਲੀ* pBuf, ਪੂਰਨ len, ਖਾਲੀ *pUser);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_SDL_NOUNUSED
// tdefl_compress_mem_to_output() compresses a block to an output stream. The above helpers use this function internally.
MINIZ_STATIC mz_bool tdefl_compress_mem_ਮੰਜ਼ਿਲ_output(ਅਚਲ ਖਾਲੀ *pBuf, size_t buf_len, tdefl_put_buf_func_ptr pPut_buf_func, ਖਾਲੀ *pPut_buf_user, ਪੂਰਨ flags);
#ਜੇ_ਅੰਤ

//enum { TDEFL_MAX_HUFF_TABLES = 3, TDEFL_MAX_HUFF_SYMBOLS_0 = 288, TDEFL_MAX_HUFF_SYMBOLS_1 = 32, TDEFL_MAX_HUFF_SYMBOLS_2 = 19, TDEFL_LZ_DICT_SIZE = 32768, TDEFL_LZ_DICT_SIZE_MASK = TDEFL_LZ_DICT_SIZE - 1, TDEFL_MIN_MATCH_LEN = 3, TDEFL_MAX_MATCH_LEN = 258 };
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TDEFL_MAX_HUFF_TABLES	3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TDEFL_MAX_HUFF_SYMBOLS_0 288
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TDEFL_MAX_HUFF_SYMBOLS_1 32
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TDEFL_MAX_HUFF_SYMBOLS_2 19
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TDEFL_LZ_DICT_ਮਾਪ 32768
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TDEFL_LZ_DICT_ਮਾਪ_ਨਕਾਬ	( TDEFL_LZ_DICT_ਮਾਪ - 1 )
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TDEFL_MIN_ਮੇਲ_LEN	3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TDEFL_MAX_ਮੇਲ_LEN 258

// TDEFL_OUT_BUF_SIZE MUST be large enough to hold a single entire compressed output block (using static/fixed Huffman codes).
#ਜੇ TDEFL_LESS_ਸਮ੍ਰਿਤੀ
ਗਿਣਤੀ { TDEFL_LZ_ਕੋਡ_BUF_ਮਾਪ = 24 * 1024, TDEFL_ਬਾਹਰਲਾ_BUF_ਮਾਪ = (TDEFL_LZ_ਕੋਡ_BUF_ਮਾਪ * 13 ) / 10, TDEFL_MAX_HUFF_SYMBOLS = 288, TDEFL_LZ_HASH_ਬਿੱਟ = 12, TDEFL_LEVEL1_HASH_ਮਾਪ_ਨਕਾਬ = 4095, TDEFL_LZ_HASH_ਖਿਸਕਾਓ = (TDEFL_LZ_HASH_ਬਿੱਟ + 2) / 3, TDEFL_LZ_HASH_ਮਾਪ = 1 << TDEFL_LZ_HASH_ਬਿੱਟ };
#ਨਹੀਂਤਾਂ
ਗਿਣਤੀ { TDEFL_LZ_ਕੋਡ_BUF_ਮਾਪ = 64 * 1024, TDEFL_ਬਾਹਰਲਾ_BUF_ਮਾਪ = (TDEFL_LZ_ਕੋਡ_BUF_ਮਾਪ * 13 ) / 10, TDEFL_MAX_HUFF_SYMBOLS = 288, TDEFL_LZ_HASH_ਬਿੱਟ = 15, TDEFL_LEVEL1_HASH_ਮਾਪ_ਨਕਾਬ = 4095, TDEFL_LZ_HASH_ਖਿਸਕਾਓ = (TDEFL_LZ_HASH_ਬਿੱਟ + 2) / 3, TDEFL_LZ_HASH_ਮਾਪ = 1 << TDEFL_LZ_HASH_ਬਿੱਟ };
#ਜੇ_ਅੰਤ

// The low-level tdefl functions below may be used directly if the above helper functions aren't flexible enough. The low-level functions don't make any heap allocations, unlike the above helper functions.
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ
{
  TDEFL_ਸਥਿਤੀ_BAD_PARAM = -2,
  TDEFL_ਸਥਿਤੀ_PUT_BUF_FAILED = -1,
  TDEFL_ਸਥਿਤੀ_OKAY = 0,
  TDEFL_ਸਥਿਤੀ_ਪੂਰਾ = 1,
} tdefl_ਸਥਿਤੀ;

// Must map to MZ_NO_FLUSH, MZ_SYNC_FLUSH, etc. enums
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ
{
  TDEFL_NO_FLUSH = 0,
  TDEFL_SYNC_FLUSH = 2,
  TDEFL_ਭਰਿਆ_FLUSH = 3,
  TDEFL_ਅੰਤ = 4
} tdefl_flush;

// tdefl's compression state structure.
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
  tdefl_put_buf_func_ptr m_pPut_buf_func;
  ਖਾਲੀ *m_pPut_buf_user;
  mz_uint m_flags, m_max_probes[2];
  ਪੂਰਨ m_greedy_parsing;
  mz_uint m_adler32, m_lookahead_pos, m_lookahead_ਮਾਪ, m_dict_ਮਾਪ;
  mz_uint8 *m_p_LZ_ਕੋਡ_buf, *m_pLZ_flags, *m_pOutput_buf, *m_p_Output_buf_ਸਿਰਾ;
  mz_uint m_ਅੰਕ_flags_ਖੱਬਾ, m_ਕੁੱਲ_lz_ਬਾਈਟਾਂ, m_lz_ਕੋਡ_buf_dict_pos, m_ਬਿੱਟ_ਵਿੱਚ, m_ਦੋਆਧਾਰੀ_ਅੰਕ_ਬਫਰ;
  mz_uint m_saved_ਮੇਲ_dist, m_saved_ਮੇਲ_len, m_saved_lit, m_output_flush_ofs, m_output_flush_ਬਚਿਆ, m_ਮੁਕੰਮਲ, m_ਖੰਡ_ਸੂਚਕਾਂਕ, m_ਚਾਹੁੰਦਾ_ਮੰਜ਼ਿਲ_ਅੰਤ;
  tdefl_ਸਥਿਤੀ m_prev_return_ਸਥਿਤੀ;
  ਅਚਲ ਖਾਲੀ *m_p_ਵਿੱਚ_buf;
  ਖਾਲੀ *m_p_ਬਾਹਰਲਾ_buf;
  size_t *m_p_ਵਿੱਚ_buf_ਮਾਪ, *m_p_ਬਾਹਰਲਾ_buf_ਮਾਪ;
  tdefl_flush m_flush;
  ਅਚਲ mz_uint8 *m_pSrc;
  size_t m_src_buf_ਖੱਬਾ, m_ਬਾਹਰਲਾ_buf_ofs;
  mz_uint8 m_dict[TDEFL_LZ_DICT_ਮਾਪ + TDEFL_MAX_ਮੇਲ_LEN - 1];
  mz_uint16 m_huff_ਗਿਣਤੀ[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint16 m_huff_codes[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint8 m_huff_ਕੋਡ_sizes[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint8 m_lz_ਕੋਡ_buf[TDEFL_LZ_ਕੋਡ_BUF_ਮਾਪ];
  mz_uint16 m_ਅਗਲਾ[TDEFL_LZ_DICT_ਮਾਪ];
  mz_uint16 m_hash[TDEFL_LZ_HASH_ਮਾਪ];
  mz_uint8 m_output_buf[TDEFL_ਬਾਹਰਲਾ_BUF_ਮਾਪ];
} tdefl_compressor;

// Initializes the compressor.
// There is no corresponding deinit() function because the tdefl API's do not dynamically allocate memory.
// pBut_buf_func: If NULL, output data will be supplied to the specified callback. In this case, the user should call the tdefl_compress_buffer() API for compression.
// If pBut_buf_func is NULL the user should always call the tdefl_compress() API.
// flags: See the above enums (TDEFL_HUFFMAN_ONLY, TDEFL_WRITE_ZLIB_HEADER, etc.)
MINIZ_STATIC tdefl_ਸਥਿਤੀ tdefl_init(tdefl_compressor *d, tdefl_put_buf_func_ptr pPut_buf_func, ਖਾਲੀ *pPut_buf_user, ਪੂਰਨ flags);

// Compresses a block of data, consuming as much of the specified input buffer as possible, and writing as much compressed data to the specified output buffer as possible.
MINIZ_STATIC tdefl_ਸਥਿਤੀ tdefl_compress(tdefl_compressor *d, ਅਚਲ ਖਾਲੀ *p_ਵਿੱਚ_buf, size_t *p_ਵਿੱਚ_buf_ਮਾਪ, ਖਾਲੀ *p_ਬਾਹਰਲਾ_buf, size_t *p_ਬਾਹਰਲਾ_buf_ਮਾਪ, tdefl_flush flush);

// tdefl_compress_buffer() is only usable when the tdefl_init() is called with a non-NULL tdefl_put_buf_func_ptr.
// tdefl_compress_buffer() always consumes the entire input buffer.
MINIZ_STATIC tdefl_ਸਥਿਤੀ tdefl_compress_ਬਫਰ(tdefl_compressor *d, ਅਚਲ ਖਾਲੀ *p_ਵਿੱਚ_buf, size_t ਵਿੱਚ_buf_ਮਾਪ, tdefl_flush flush);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_SDL_NOUNUSED
MINIZ_STATIC tdefl_ਸਥਿਤੀ tdefl_get_prev_return_ਸਥਿਤੀ(tdefl_compressor *d);
MINIZ_STATIC mz_uint32 tdefl_get_adler32(tdefl_compressor *d);
#ਜੇ_ਅੰਤ

// Can't use tdefl_create_comp_flags_from_zip_params if MINIZ_NO_ZLIB_APIS isn't defined, because it uses some of its macros.
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_ZLIB_APIS
// Create tdefl_compress() flags given zlib-style compression parameters.
// level may range from [0,10] (where 10 is absolute max compression, but may be much slower on some files)
// window_bits may be -15 (raw deflate) or 15 (zlib)
// strategy may be either MZ_DEFAULT_STRATEGY, MZ_FILTERED, MZ_HUFFMAN_ONLY, MZ_RLE, or MZ_FIXED
MINIZ_STATIC mz_uint tdefl_create_comp_flags_from_zip_params(ਪੂਰਨ level, ਪੂਰਨ ਖਿੜਕੀ_ਬਿੱਟ, ਪੂਰਨ strategy);
#ਜੇ_ਅੰਤ // #ifndef MINIZ_NO_ZLIB_APIS

#ਜੇ_ਅੰਤ /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ // MINIZ_HEADER_INCLUDED

// ------------------- End of Header: Implementation follows. (If you only want the header, define MINIZ_HEADER_FILE_ONLY.)

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_ਸਿਰਲੇਖ_FILE_ONLY

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _MSC_VER
#ਹਦਾਇਤ warning (ਧੱਕੋ)
#ਹਦਾਇਤ warning (disable:4505) // unreferenced local function has been removed
#ਜੇ_ਅੰਤ

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ mz_validate_uint16[ਆਕਾਰ(mz_uint16)==2 ? 1 : -1];
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ mz_validate_uint32[ਆਕਾਰ(mz_uint32)==4 ? 1 : -1];
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ mz_validate_uint64[ਆਕਾਰ(mz_uint64)==8 ? 1 : -1];

/*#include <string.h>*/

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MZ_ASSERT
#ਅਨ੍ਤਰ੍ਭਾਵ <assert.h>
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_ASSERT(x) ਪ੍ਰਤਿਜ੍ਞਾ(x)
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_MALLOC
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_MALLOC(x) ਨਿਰਾ
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FREE(x) (ਖਾਲੀ)x, ((ਖਾਲੀ)0)
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_REALLOC(p, x) ਨਿਰਾ
#ਜਾਂਜੇ defined(MINIZ_SDL_MALLOC)
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_MALLOC(x) SDL_malloc(x)
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FREE(x) SDL_free(x)
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_REALLOC(p, x) SDL_realloc(p, x)
#ਨਹੀਂਤਾਂ
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_MALLOC(x) ਸਮ੍ਰਿਤੀ_ਦਿਓ(x)
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FREE(x) ਮੁਕਤ(x)
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_REALLOC(p, x) realloc(p, x)
#ਜੇ_ਅੰਤ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_MAX(a,b) (((a)>(b))?(a):(b))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_MIN(a,b) (((a)<(b))?(a):(b))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_CLEAR_OBJ(obj) memset(&(obj), 0, ਆਕਾਰ(obj))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_CLEAR_ARR(obj) memset((obj), 0, ਆਕਾਰ(obj))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_CLEAR_PTR(obj) memset((obj), 0, ਆਕਾਰ(*obj))

#ਜੇ MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_READ_LE16(p) *((ਅਚਲ mz_uint16 *)(p))
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_READ_LE32(p) *((ਅਚਲ mz_uint32 *)(p))
#ਨਹੀਂਤਾਂ
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_READ_LE16(p) ((mz_uint32)(((ਅਚਲ mz_uint8 *)(p))[0]) | ((mz_uint32)(((ਅਚਲ mz_uint8 *)(p))[1]) << 8U))
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_READ_LE32(p) ((mz_uint32)(((ਅਚਲ mz_uint8 *)(p))[0]) | ((mz_uint32)(((ਅਚਲ mz_uint8 *)(p))[1]) << 8U) | ((mz_uint32)(((ਅਚਲ mz_uint8 *)(p))[2]) << 16U) | ((mz_uint32)(((ਅਚਲ mz_uint8 *)(p))[3]) << 24U))
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _MSC_VER
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FORCEINLINE __forceinline
#ਜਾਂਜੇ defined(__GNUC__)
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FORCEINLINE ਸਤਰਅੰਦਰ __attribute__((__always_inline__))
#ਨਹੀਂਤਾਂ
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FORCEINLINE ਸਤਰਅੰਦਰ
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
  ਬਾਹਰੀ "C" {
#ਜੇ_ਅੰਤ

// ------------------- zlib-style API's

mz_ulong mz_adler32(mz_ulong adler, ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *ptr, size_t buf_len)
{
  mz_uint32 i, s1 = (mz_uint32)(adler & 0xffff), s2 = (mz_uint32)(adler >> 16); size_t ਖੰਡ_len = buf_len % 5552;
  ਜੇ (!ptr) ਵਾਪਸ MZ_ADLER32_INIT;
  ਜਦੋਂ (buf_len) {
    ਲਈ (i = 0; i + 7 < ਖੰਡ_len; i += 8, ptr += 8) {
      s1 += ptr[0]; s2 += s1; s1 += ptr[1]; s2 += s1; s1 += ptr[2]; s2 += s1; s1 += ptr[3]; s2 += s1;
      s1 += ptr[4]; s2 += s1; s1 += ptr[5]; s2 += s1; s1 += ptr[6]; s2 += s1; s1 += ptr[7]; s2 += s1;
    }
    ਲਈ ( ; i < ਖੰਡ_len; ++i) { s1 += *ptr++; s2 += s1; }
    s1 %= 65521U; s2 %= 65521U; buf_len -= ਖੰਡ_len; ਖੰਡ_len = 5552;
  }
  ਵਾਪਸ (s2 << 16) + s1;
}

// Karl Malbrain's compact CRC-32. See "A compact CCITT crc16 and crc32 C implementation that balances processor cache usage against speed": http://www.geocities.com/malbrain/
mz_ulong mz_ਚੱਕਰੀ_ਜਾਂਚ_32(mz_ulong ਚੱਕਰੀ_ਜਾਂਚ, ਅਚਲ mz_uint8 *ptr, size_t buf_len)
{
  ਸਥਿਰ ਅਚਲ mz_uint32 s_ਚੱਕਰੀ_ਜਾਂਚ_32[16] = { 0, 0x1db71064, 0x3b6e20c8, 0x26d930ac, 0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
    0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c, 0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c };
  mz_uint32 crcu32 = (mz_uint32)ਚੱਕਰੀ_ਜਾਂਚ;
  ਜੇ (!ptr) ਵਾਪਸ MZ_ਚੱਕਰੀ_ਜਾਂਚ_32_INIT;
  crcu32 = ~crcu32; ਜਦੋਂ (buf_len--) { mz_uint8 b = *ptr++; crcu32 = (crcu32 >> 4) ^ s_ਚੱਕਰੀ_ਜਾਂਚ_32[(crcu32 & 0xF) ^ (b & 0xF)]; crcu32 = (crcu32 >> 4) ^ s_ਚੱਕਰੀ_ਜਾਂਚ_32[(crcu32 & 0xF) ^ (b >> 4)]; }
  ਵਾਪਸ ~crcu32;
}

MINIZ_STATIC ਖਾਲੀ mz_free(ਖਾਲੀ *p)
{
  MZ_FREE(p);
}

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_ZLIB_APIS

ਸਥਿਰ ਖਾਲੀ *def_alloc_func(ਖਾਲੀ *opaque, size_t ਚੀਜ਼ਾਂ, size_t ਮਾਪ) { (ਖਾਲੀ)opaque, (ਖਾਲੀ)ਚੀਜ਼ਾਂ, (ਖਾਲੀ)ਮਾਪ; ਵਾਪਸ MZ_MALLOC(ਚੀਜ਼ਾਂ * ਮਾਪ); }
ਸਥਿਰ ਖਾਲੀ def_free_func(ਖਾਲੀ *opaque, ਖਾਲੀ *ਪਤਾ) { (ਖਾਲੀ)opaque, (ਖਾਲੀ)ਪਤਾ; MZ_FREE(ਪਤਾ); }
ਸਥਿਰ ਖਾਲੀ *def_realloc_func(ਖਾਲੀ *opaque, ਖਾਲੀ *ਪਤਾ, size_t ਚੀਜ਼ਾਂ, size_t ਮਾਪ) { (ਖਾਲੀ)opaque, (ਖਾਲੀ)ਪਤਾ, (ਖਾਲੀ)ਚੀਜ਼ਾਂ, (ਖਾਲੀ)ਮਾਪ; ਵਾਪਸ MZ_REALLOC(ਪਤਾ, ਚੀਜ਼ਾਂ * ਮਾਪ); }

ਅਚਲ ਅੱਖਰ *mz_ਸੰਸਕਰਣ(ਖਾਲੀ)
{
  ਵਾਪਸ MZ_ਸੰਸਕਰਣ;
}

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_DEFLATE_APIS

ਪੂਰਨ mz_deflateInit(mz_streamp p_ਧਾਰਾ, ਪੂਰਨ level)
{
  ਵਾਪਸ mz_deflateInit2(p_ਧਾਰਾ, level, MZ_DEFLATED, MZ_DEFAULT_ਖਿੜਕੀ_ਬਿੱਟ, 9, MZ_DEFAULT_STRATEGY);
}

ਪੂਰਨ mz_deflateInit2(mz_streamp p_ਧਾਰਾ, ਪੂਰਨ level, ਪੂਰਨ ਵਿਧੀ, ਪੂਰਨ ਖਿੜਕੀ_ਬਿੱਟ, ਪੂਰਨ mem_level, ਪੂਰਨ strategy)
{
  tdefl_compressor *pComp;
  mz_uint comp_flags = TDEFL_COMPUTE_ADLER32 | tdefl_create_comp_flags_from_zip_params(level, ਖਿੜਕੀ_ਬਿੱਟ, strategy);

  ਜੇ (!p_ਧਾਰਾ) ਵਾਪਸ MZ_ਧਾਰਾ_ERROR;
  ਜੇ ((ਵਿਧੀ != MZ_DEFLATED) || ((mem_level < 1) || (mem_level > 9)) || ((ਖਿੜਕੀ_ਬਿੱਟ != MZ_DEFAULT_ਖਿੜਕੀ_ਬਿੱਟ) && (-ਖਿੜਕੀ_ਬਿੱਟ != MZ_DEFAULT_ਖਿੜਕੀ_ਬਿੱਟ))) ਵਾਪਸ MZ_PARAM_ERROR;

  p_ਧਾਰਾ->ਅੰਕੜੇ_type = 0;
  p_ਧਾਰਾ->adler = MZ_ADLER32_INIT;
  p_ਧਾਰਾ->ਸੁਨੇਹਾ_2 = ਨਿਰਾ;
  p_ਧਾਰਾ->reserved = 0;
  p_ਧਾਰਾ->ਕੁੱਲ_ਵਿੱਚ = 0;
  p_ਧਾਰਾ->ਕੁੱਲ_ਬਾਹਰਲਾ = 0;
  ਜੇ (!p_ਧਾਰਾ->zalloc) p_ਧਾਰਾ->zalloc = def_alloc_func;
  ਜੇ (!p_ਧਾਰਾ->zfree) p_ਧਾਰਾ->zfree = def_free_func;

  pComp = (tdefl_compressor *)p_ਧਾਰਾ->zalloc(p_ਧਾਰਾ->opaque, 1, ਆਕਾਰ(tdefl_compressor));
  ਜੇ (!pComp)
    ਵਾਪਸ MZ_MEM_ERROR;

  p_ਧਾਰਾ->state = (ਬਣਤਰ mz_ਅੰਦਰੂਨੀ_state *)pComp;

  ਜੇ (tdefl_init(pComp, ਨਿਰਾ, ਨਿਰਾ, comp_flags) != TDEFL_ਸਥਿਤੀ_OKAY)
  {
    mz_deflate_ਸਿਰਾ(p_ਧਾਰਾ);
    ਵਾਪਸ MZ_PARAM_ERROR;
  }

  ਵਾਪਸ MZ_OK;
}

ਪੂਰਨ mz_deflateReset(mz_streamp p_ਧਾਰਾ)
{
  ਜੇ ((!p_ਧਾਰਾ) || (!p_ਧਾਰਾ->state) || (!p_ਧਾਰਾ->zalloc) || (!p_ਧਾਰਾ->zfree)) ਵਾਪਸ MZ_ਧਾਰਾ_ERROR;
  p_ਧਾਰਾ->ਕੁੱਲ_ਵਿੱਚ = p_ਧਾਰਾ->ਕੁੱਲ_ਬਾਹਰਲਾ = 0;
  tdefl_init((tdefl_compressor*)p_ਧਾਰਾ->state, ਨਿਰਾ, ਨਿਰਾ, ((tdefl_compressor*)p_ਧਾਰਾ->state)->m_flags);
  ਵਾਪਸ MZ_OK;
}

ਪੂਰਨ mz_deflate(mz_streamp p_ਧਾਰਾ, ਪੂਰਨ flush)
{
  size_t ਵਿੱਚ_ਬਾਈਟਾਂ, ਬਾਹਰਲਾ_ਬਾਈਟਾਂ;
  mz_ulong orig_ਕੁੱਲ_ਵਿੱਚ, orig_ਕੁੱਲ_ਬਾਹਰਲਾ;
  ਪੂਰਨ mz_ਸਥਿਤੀ = MZ_OK;

  ਜੇ ((!p_ਧਾਰਾ) || (!p_ਧਾਰਾ->state) || (flush < 0) || (flush > MZ_ਅੰਤ) || (!p_ਧਾਰਾ->ਅਗਲਾ_ਬਾਹਰਲਾ)) ਵਾਪਸ MZ_ਧਾਰਾ_ERROR;
  ਜੇ (!p_ਧਾਰਾ->avail_ਬਾਹਰਲਾ) ਵਾਪਸ MZ_BUF_ERROR;

  ਜੇ (flush == MZ_PARTIAL_FLUSH) flush = MZ_SYNC_FLUSH;

  ਜੇ (((tdefl_compressor*)p_ਧਾਰਾ->state)->m_prev_return_ਸਥਿਤੀ == TDEFL_ਸਥਿਤੀ_ਪੂਰਾ)
    ਵਾਪਸ (flush == MZ_ਅੰਤ) ? MZ_ਧਾਰਾ_ਸਿਰਾ : MZ_BUF_ERROR;

  orig_ਕੁੱਲ_ਵਿੱਚ = p_ਧਾਰਾ->ਕੁੱਲ_ਵਿੱਚ; orig_ਕੁੱਲ_ਬਾਹਰਲਾ = p_ਧਾਰਾ->ਕੁੱਲ_ਬਾਹਰਲਾ;
  ਲਈ ( ; ; )
  {
    tdefl_ਸਥਿਤੀ defl_ਸਥਿਤੀ;
    ਵਿੱਚ_ਬਾਈਟਾਂ = p_ਧਾਰਾ->avail_ਵਿੱਚ; ਬਾਹਰਲਾ_ਬਾਈਟਾਂ = p_ਧਾਰਾ->avail_ਬਾਹਰਲਾ;

    defl_ਸਥਿਤੀ = tdefl_compress((tdefl_compressor*)p_ਧਾਰਾ->state, p_ਧਾਰਾ->ਅਗਲਾ_ਵਿੱਚ, &ਵਿੱਚ_ਬਾਈਟਾਂ, p_ਧਾਰਾ->ਅਗਲਾ_ਬਾਹਰਲਾ, &ਬਾਹਰਲਾ_ਬਾਈਟਾਂ, (tdefl_flush)flush);
    p_ਧਾਰਾ->ਅਗਲਾ_ਵਿੱਚ += (mz_uint)ਵਿੱਚ_ਬਾਈਟਾਂ; p_ਧਾਰਾ->avail_ਵਿੱਚ -= (mz_uint)ਵਿੱਚ_ਬਾਈਟਾਂ;
    p_ਧਾਰਾ->ਕੁੱਲ_ਵਿੱਚ += (mz_uint)ਵਿੱਚ_ਬਾਈਟਾਂ; p_ਧਾਰਾ->adler = tdefl_get_adler32((tdefl_compressor*)p_ਧਾਰਾ->state);

    p_ਧਾਰਾ->ਅਗਲਾ_ਬਾਹਰਲਾ += (mz_uint)ਬਾਹਰਲਾ_ਬਾਈਟਾਂ; p_ਧਾਰਾ->avail_ਬਾਹਰਲਾ -= (mz_uint)ਬਾਹਰਲਾ_ਬਾਈਟਾਂ;
    p_ਧਾਰਾ->ਕੁੱਲ_ਬਾਹਰਲਾ += (mz_uint)ਬਾਹਰਲਾ_ਬਾਈਟਾਂ;

    ਜੇ (defl_ਸਥਿਤੀ < 0)
    {
      mz_ਸਥਿਤੀ = MZ_ਧਾਰਾ_ERROR;
      ਰੋਕੋ;
    }
    ਨਹੀਂਤਾਂ ਜੇ (defl_ਸਥਿਤੀ == TDEFL_ਸਥਿਤੀ_ਪੂਰਾ)
    {
      mz_ਸਥਿਤੀ = MZ_ਧਾਰਾ_ਸਿਰਾ;
      ਰੋਕੋ;
    }
    ਨਹੀਂਤਾਂ ਜੇ (!p_ਧਾਰਾ->avail_ਬਾਹਰਲਾ)
      ਰੋਕੋ;
    ਨਹੀਂਤਾਂ ਜੇ ((!p_ਧਾਰਾ->avail_ਵਿੱਚ) && (flush != MZ_ਅੰਤ))
    {
      ਜੇ ((flush) || (p_ਧਾਰਾ->ਕੁੱਲ_ਵਿੱਚ != orig_ਕੁੱਲ_ਵਿੱਚ) || (p_ਧਾਰਾ->ਕੁੱਲ_ਬਾਹਰਲਾ != orig_ਕੁੱਲ_ਬਾਹਰਲਾ))
        ਰੋਕੋ;
      ਵਾਪਸ MZ_BUF_ERROR; // Can't make forward progress without some input.
    }
  }
  ਵਾਪਸ mz_ਸਥਿਤੀ;
}

ਪੂਰਨ mz_deflate_ਸਿਰਾ(mz_streamp p_ਧਾਰਾ)
{
  ਜੇ (!p_ਧਾਰਾ) ਵਾਪਸ MZ_ਧਾਰਾ_ERROR;
  ਜੇ (p_ਧਾਰਾ->state)
  {
    p_ਧਾਰਾ->zfree(p_ਧਾਰਾ->opaque, p_ਧਾਰਾ->state);
    p_ਧਾਰਾ->state = ਨਿਰਾ;
  }
  ਵਾਪਸ MZ_OK;
}

mz_ulong mz_deflateBound(mz_streamp p_ਧਾਰਾ, mz_ulong ਸਰੋਤ_len)
{
  (ਖਾਲੀ)p_ਧਾਰਾ;
  // This is really over conservative. (And lame, but it's actually pretty tricky to compute a true upper bound given the way tdefl's blocking works.)
  ਵਾਪਸ MZ_MAX(128 + (ਸਰੋਤ_len * 110) / 100, 128 + ਸਰੋਤ_len + ((ਸਰੋਤ_len / (31 * 1024)) + 1) * 5);
}

ਪੂਰਨ mz_compress2(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *pDest, mz_ulong *pDest_len, ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *p_ਸਰੋਤ, mz_ulong ਸਰੋਤ_len, ਪੂਰਨ level)
{
  ਪੂਰਨ ਸਥਿਤੀ;
  mz_ਧਾਰਾ ਧਾਰਾ;
  memset(&ਧਾਰਾ, 0, ਆਕਾਰ(ਧਾਰਾ));

  // In case mz_ulong is 64-bits (argh I hate longs).
  ਜੇ ((ਸਰੋਤ_len | *pDest_len) > 0xFFFFFFFFU) ਵਾਪਸ MZ_PARAM_ERROR;

  ਧਾਰਾ.ਅਗਲਾ_ਵਿੱਚ = p_ਸਰੋਤ;
  ਧਾਰਾ.avail_ਵਿੱਚ = (mz_uint32)ਸਰੋਤ_len;
  ਧਾਰਾ.ਅਗਲਾ_ਬਾਹਰਲਾ = pDest;
  ਧਾਰਾ.avail_ਬਾਹਰਲਾ = (mz_uint32)*pDest_len;

  ਸਥਿਤੀ = mz_deflateInit(&ਧਾਰਾ, level);
  ਜੇ (ਸਥਿਤੀ != MZ_OK) ਵਾਪਸ ਸਥਿਤੀ;

  ਸਥਿਤੀ = mz_deflate(&ਧਾਰਾ, MZ_ਅੰਤ);
  ਜੇ (ਸਥਿਤੀ != MZ_ਧਾਰਾ_ਸਿਰਾ)
  {
    mz_deflate_ਸਿਰਾ(&ਧਾਰਾ);
    ਵਾਪਸ (ਸਥਿਤੀ == MZ_OK) ? MZ_BUF_ERROR : ਸਥਿਤੀ;
  }

  *pDest_len = ਧਾਰਾ.ਕੁੱਲ_ਬਾਹਰਲਾ;
  ਵਾਪਸ mz_deflate_ਸਿਰਾ(&ਧਾਰਾ);
}

ਪੂਰਨ mz_compress(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *pDest, mz_ulong *pDest_len, ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *p_ਸਰੋਤ, mz_ulong ਸਰੋਤ_len)
{
  ਵਾਪਸ mz_compress2(pDest, pDest_len, p_ਸਰੋਤ, ਸਰੋਤ_len, MZ_DEFAULT_COMPRESSION);
}

mz_ulong mz_compressBound(mz_ulong ਸਰੋਤ_len)
{
  ਵਾਪਸ mz_deflateBound(ਨਿਰਾ, ਸਰੋਤ_len);
}

#ਜੇ_ਅੰਤ /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_INFLATE_APIS

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
  tinfl_decompressor m_decomp;
  mz_uint m_dict_ofs, m_dict_avail, m_ਪਹਿਲਾ_call, m_has_flushed; ਪੂਰਨ m_ਖਿੜਕੀ_ਬਿੱਟ;
  mz_uint8 m_dict[TINFL_LZ_DICT_ਮਾਪ];
  tinfl_ਸਥਿਤੀ m_ਆਖਰੀ_ਸਥਿਤੀ;
} inflate_state;

ਪੂਰਨ mz_inflateInit2(mz_streamp p_ਧਾਰਾ, ਪੂਰਨ ਖਿੜਕੀ_ਬਿੱਟ)
{
  inflate_state *pDecomp;
  ਜੇ (!p_ਧਾਰਾ) ਵਾਪਸ MZ_ਧਾਰਾ_ERROR;
  ਜੇ ((ਖਿੜਕੀ_ਬਿੱਟ != MZ_DEFAULT_ਖਿੜਕੀ_ਬਿੱਟ) && (-ਖਿੜਕੀ_ਬਿੱਟ != MZ_DEFAULT_ਖਿੜਕੀ_ਬਿੱਟ)) ਵਾਪਸ MZ_PARAM_ERROR;

  p_ਧਾਰਾ->ਅੰਕੜੇ_type = 0;
  p_ਧਾਰਾ->adler = 0;
  p_ਧਾਰਾ->ਸੁਨੇਹਾ_2 = ਨਿਰਾ;
  p_ਧਾਰਾ->ਕੁੱਲ_ਵਿੱਚ = 0;
  p_ਧਾਰਾ->ਕੁੱਲ_ਬਾਹਰਲਾ = 0;
  p_ਧਾਰਾ->reserved = 0;
  ਜੇ (!p_ਧਾਰਾ->zalloc) p_ਧਾਰਾ->zalloc = def_alloc_func;
  ਜੇ (!p_ਧਾਰਾ->zfree) p_ਧਾਰਾ->zfree = def_free_func;

  pDecomp = (inflate_state*)p_ਧਾਰਾ->zalloc(p_ਧਾਰਾ->opaque, 1, ਆਕਾਰ(inflate_state));
  ਜੇ (!pDecomp) ਵਾਪਸ MZ_MEM_ERROR;

  p_ਧਾਰਾ->state = (ਬਣਤਰ mz_ਅੰਦਰੂਨੀ_state *)pDecomp;

  tinfl_init(&pDecomp->m_decomp);
  pDecomp->m_dict_ofs = 0;
  pDecomp->m_dict_avail = 0;
  pDecomp->m_ਆਖਰੀ_ਸਥਿਤੀ = TINFL_ਸਥਿਤੀ_NEEDS_ਹੋਰ_ਨਿਵੇਸ਼;
  pDecomp->m_ਪਹਿਲਾ_call = 1;
  pDecomp->m_has_flushed = 0;
  pDecomp->m_ਖਿੜਕੀ_ਬਿੱਟ = ਖਿੜਕੀ_ਬਿੱਟ;

  ਵਾਪਸ MZ_OK;
}

ਪੂਰਨ mz_inflateInit(mz_streamp p_ਧਾਰਾ)
{
   ਵਾਪਸ mz_inflateInit2(p_ਧਾਰਾ, MZ_DEFAULT_ਖਿੜਕੀ_ਬਿੱਟ);
}

ਪੂਰਨ mz_inflate(mz_streamp p_ਧਾਰਾ, ਪੂਰਨ flush)
{
  inflate_state* pState;
  mz_uint n, ਪਹਿਲਾ_call, decomp_flags = TINFL_FLAG_COMPUTE_ADLER32;
  size_t ਵਿੱਚ_ਬਾਈਟਾਂ, ਬਾਹਰਲਾ_ਬਾਈਟਾਂ, orig_avail_ਵਿੱਚ;
  tinfl_ਸਥਿਤੀ ਸਥਿਤੀ;

  ਜੇ ((!p_ਧਾਰਾ) || (!p_ਧਾਰਾ->state)) ਵਾਪਸ MZ_ਧਾਰਾ_ERROR;
  ਜੇ (flush == MZ_PARTIAL_FLUSH) flush = MZ_SYNC_FLUSH;
  ਜੇ ((flush) && (flush != MZ_SYNC_FLUSH) && (flush != MZ_ਅੰਤ)) ਵਾਪਸ MZ_ਧਾਰਾ_ERROR;

  pState = (inflate_state*)p_ਧਾਰਾ->state;
  ਜੇ (pState->m_ਖਿੜਕੀ_ਬਿੱਟ > 0) decomp_flags |= TINFL_FLAG_PARSE_ZLIB_ਸਿਰਲੇਖ;
  orig_avail_ਵਿੱਚ = p_ਧਾਰਾ->avail_ਵਿੱਚ;

  ਪਹਿਲਾ_call = pState->m_ਪਹਿਲਾ_call; pState->m_ਪਹਿਲਾ_call = 0;
  ਜੇ (pState->m_ਆਖਰੀ_ਸਥਿਤੀ < 0) ਵਾਪਸ MZ_ਅੰਕੜੇ_ERROR;

  ਜੇ (pState->m_has_flushed && (flush != MZ_ਅੰਤ)) ਵਾਪਸ MZ_ਧਾਰਾ_ERROR;
  pState->m_has_flushed |= (flush == MZ_ਅੰਤ);

  ਜੇ ((flush == MZ_ਅੰਤ) && (ਪਹਿਲਾ_call))
  {
    // MZ_FINISH on the first call implies that the input and output buffers are large enough to hold the entire compressed/decompressed file.
    decomp_flags |= TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF;
    ਵਿੱਚ_ਬਾਈਟਾਂ = p_ਧਾਰਾ->avail_ਵਿੱਚ; ਬਾਹਰਲਾ_ਬਾਈਟਾਂ = p_ਧਾਰਾ->avail_ਬਾਹਰਲਾ;
    ਸਥਿਤੀ = tinfl_decompress(&pState->m_decomp, p_ਧਾਰਾ->ਅਗਲਾ_ਵਿੱਚ, &ਵਿੱਚ_ਬਾਈਟਾਂ, p_ਧਾਰਾ->ਅਗਲਾ_ਬਾਹਰਲਾ, p_ਧਾਰਾ->ਅਗਲਾ_ਬਾਹਰਲਾ, &ਬਾਹਰਲਾ_ਬਾਈਟਾਂ, decomp_flags);
    pState->m_ਆਖਰੀ_ਸਥਿਤੀ = ਸਥਿਤੀ;
    p_ਧਾਰਾ->ਅਗਲਾ_ਵਿੱਚ += (mz_uint)ਵਿੱਚ_ਬਾਈਟਾਂ; p_ਧਾਰਾ->avail_ਵਿੱਚ -= (mz_uint)ਵਿੱਚ_ਬਾਈਟਾਂ; p_ਧਾਰਾ->ਕੁੱਲ_ਵਿੱਚ += (mz_uint)ਵਿੱਚ_ਬਾਈਟਾਂ;
    p_ਧਾਰਾ->adler = tinfl_get_adler32(&pState->m_decomp);
    p_ਧਾਰਾ->ਅਗਲਾ_ਬਾਹਰਲਾ += (mz_uint)ਬਾਹਰਲਾ_ਬਾਈਟਾਂ; p_ਧਾਰਾ->avail_ਬਾਹਰਲਾ -= (mz_uint)ਬਾਹਰਲਾ_ਬਾਈਟਾਂ; p_ਧਾਰਾ->ਕੁੱਲ_ਬਾਹਰਲਾ += (mz_uint)ਬਾਹਰਲਾ_ਬਾਈਟਾਂ;

    ਜੇ (ਸਥਿਤੀ < 0)
      ਵਾਪਸ MZ_ਅੰਕੜੇ_ERROR;
    ਨਹੀਂਤਾਂ ਜੇ (ਸਥਿਤੀ != TINFL_ਸਥਿਤੀ_ਪੂਰਾ)
    {
      pState->m_ਆਖਰੀ_ਸਥਿਤੀ = TINFL_ਸਥਿਤੀ_FAILED;
      ਵਾਪਸ MZ_BUF_ERROR;
    }
    ਵਾਪਸ MZ_ਧਾਰਾ_ਸਿਰਾ;
  }
  // flush != MZ_FINISH then we must assume there's more input.
  ਜੇ (flush != MZ_ਅੰਤ) decomp_flags |= TINFL_FLAG_HAS_ਹੋਰ_ਨਿਵੇਸ਼;

  ਜੇ (pState->m_dict_avail)
  {
    n = MZ_MIN(pState->m_dict_avail, p_ਧਾਰਾ->avail_ਬਾਹਰਲਾ);
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(p_ਧਾਰਾ->ਅਗਲਾ_ਬਾਹਰਲਾ, pState->m_dict + pState->m_dict_ofs, n);
    p_ਧਾਰਾ->ਅਗਲਾ_ਬਾਹਰਲਾ += n; p_ਧਾਰਾ->avail_ਬਾਹਰਲਾ -= n; p_ਧਾਰਾ->ਕੁੱਲ_ਬਾਹਰਲਾ += n;
    pState->m_dict_avail -= n; pState->m_dict_ofs = (pState->m_dict_ofs + n) & (TINFL_LZ_DICT_ਮਾਪ - 1);
    ਵਾਪਸ ((pState->m_ਆਖਰੀ_ਸਥਿਤੀ == TINFL_ਸਥਿਤੀ_ਪੂਰਾ) && (!pState->m_dict_avail)) ? MZ_ਧਾਰਾ_ਸਿਰਾ : MZ_OK;
  }

  ਲਈ ( ; ; )
  {
    ਵਿੱਚ_ਬਾਈਟਾਂ = p_ਧਾਰਾ->avail_ਵਿੱਚ;
    ਬਾਹਰਲਾ_ਬਾਈਟਾਂ = TINFL_LZ_DICT_ਮਾਪ - pState->m_dict_ofs;

    ਸਥਿਤੀ = tinfl_decompress(&pState->m_decomp, p_ਧਾਰਾ->ਅਗਲਾ_ਵਿੱਚ, &ਵਿੱਚ_ਬਾਈਟਾਂ, pState->m_dict, pState->m_dict + pState->m_dict_ofs, &ਬਾਹਰਲਾ_ਬਾਈਟਾਂ, decomp_flags);
    pState->m_ਆਖਰੀ_ਸਥਿਤੀ = ਸਥਿਤੀ;

    p_ਧਾਰਾ->ਅਗਲਾ_ਵਿੱਚ += (mz_uint)ਵਿੱਚ_ਬਾਈਟਾਂ; p_ਧਾਰਾ->avail_ਵਿੱਚ -= (mz_uint)ਵਿੱਚ_ਬਾਈਟਾਂ;
    p_ਧਾਰਾ->ਕੁੱਲ_ਵਿੱਚ += (mz_uint)ਵਿੱਚ_ਬਾਈਟਾਂ; p_ਧਾਰਾ->adler = tinfl_get_adler32(&pState->m_decomp);

    pState->m_dict_avail = (mz_uint)ਬਾਹਰਲਾ_ਬਾਈਟਾਂ;

    n = MZ_MIN(pState->m_dict_avail, p_ਧਾਰਾ->avail_ਬਾਹਰਲਾ);
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(p_ਧਾਰਾ->ਅਗਲਾ_ਬਾਹਰਲਾ, pState->m_dict + pState->m_dict_ofs, n);
    p_ਧਾਰਾ->ਅਗਲਾ_ਬਾਹਰਲਾ += n; p_ਧਾਰਾ->avail_ਬਾਹਰਲਾ -= n; p_ਧਾਰਾ->ਕੁੱਲ_ਬਾਹਰਲਾ += n;
    pState->m_dict_avail -= n; pState->m_dict_ofs = (pState->m_dict_ofs + n) & (TINFL_LZ_DICT_ਮਾਪ - 1);

    ਜੇ (ਸਥਿਤੀ < 0)
       ਵਾਪਸ MZ_ਅੰਕੜੇ_ERROR; // Stream is corrupted (there could be some uncompressed data left in the output dictionary - oh well).
    ਨਹੀਂਤਾਂ ਜੇ ((ਸਥਿਤੀ == TINFL_ਸਥਿਤੀ_NEEDS_ਹੋਰ_ਨਿਵੇਸ਼) && (!orig_avail_ਵਿੱਚ))
      ਵਾਪਸ MZ_BUF_ERROR; // Signal caller that we can't make forward progress without supplying more input or by setting flush to MZ_FINISH.
    ਨਹੀਂਤਾਂ ਜੇ (flush == MZ_ਅੰਤ)
    {
       // The output buffer MUST be large to hold the remaining uncompressed data when flush==MZ_FINISH.
       ਜੇ (ਸਥਿਤੀ == TINFL_ਸਥਿਤੀ_ਪੂਰਾ)
          ਵਾਪਸ pState->m_dict_avail ? MZ_BUF_ERROR : MZ_ਧਾਰਾ_ਸਿਰਾ;
       // status here must be TINFL_STATUS_HAS_MORE_OUTPUT, which means there's at least 1 more byte on the way. If there's no more room left in the output buffer then something is wrong.
       ਨਹੀਂਤਾਂ ਜੇ (!p_ਧਾਰਾ->avail_ਬਾਹਰਲਾ)
          ਵਾਪਸ MZ_BUF_ERROR;
    }
    ਨਹੀਂਤਾਂ ਜੇ ((ਸਥਿਤੀ == TINFL_ਸਥਿਤੀ_ਪੂਰਾ) || (!p_ਧਾਰਾ->avail_ਵਿੱਚ) || (!p_ਧਾਰਾ->avail_ਬਾਹਰਲਾ) || (pState->m_dict_avail))
      ਰੋਕੋ;
  }

  ਵਾਪਸ ((ਸਥਿਤੀ == TINFL_ਸਥਿਤੀ_ਪੂਰਾ) && (!pState->m_dict_avail)) ? MZ_ਧਾਰਾ_ਸਿਰਾ : MZ_OK;
}

ਪੂਰਨ mz_inflate_ਸਿਰਾ(mz_streamp p_ਧਾਰਾ)
{
  ਜੇ (!p_ਧਾਰਾ)
    ਵਾਪਸ MZ_ਧਾਰਾ_ERROR;
  ਜੇ (p_ਧਾਰਾ->state)
  {
    p_ਧਾਰਾ->zfree(p_ਧਾਰਾ->opaque, p_ਧਾਰਾ->state);
    p_ਧਾਰਾ->state = ਨਿਰਾ;
  }
  ਵਾਪਸ MZ_OK;
}

ਪੂਰਨ mz_uncompress(ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *pDest, mz_ulong *pDest_len, ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *p_ਸਰੋਤ, mz_ulong ਸਰੋਤ_len)
{
  mz_ਧਾਰਾ ਧਾਰਾ;
  ਪੂਰਨ ਸਥਿਤੀ;
  memset(&ਧਾਰਾ, 0, ਆਕਾਰ(ਧਾਰਾ));

  // In case mz_ulong is 64-bits (argh I hate longs).
  ਜੇ ((ਸਰੋਤ_len | *pDest_len) > 0xFFFFFFFFU) ਵਾਪਸ MZ_PARAM_ERROR;

  ਧਾਰਾ.ਅਗਲਾ_ਵਿੱਚ = p_ਸਰੋਤ;
  ਧਾਰਾ.avail_ਵਿੱਚ = (mz_uint32)ਸਰੋਤ_len;
  ਧਾਰਾ.ਅਗਲਾ_ਬਾਹਰਲਾ = pDest;
  ਧਾਰਾ.avail_ਬਾਹਰਲਾ = (mz_uint32)*pDest_len;

  ਸਥਿਤੀ = mz_inflateInit(&ਧਾਰਾ);
  ਜੇ (ਸਥਿਤੀ != MZ_OK)
    ਵਾਪਸ ਸਥਿਤੀ;

  ਸਥਿਤੀ = mz_inflate(&ਧਾਰਾ, MZ_ਅੰਤ);
  ਜੇ (ਸਥਿਤੀ != MZ_ਧਾਰਾ_ਸਿਰਾ)
  {
    mz_inflate_ਸਿਰਾ(&ਧਾਰਾ);
    ਵਾਪਸ ((ਸਥਿਤੀ == MZ_BUF_ERROR) && (!ਧਾਰਾ.avail_ਵਿੱਚ)) ? MZ_ਅੰਕੜੇ_ERROR : ਸਥਿਤੀ;
  }
  *pDest_len = ਧਾਰਾ.ਕੁੱਲ_ਬਾਹਰਲਾ;

  ਵਾਪਸ mz_inflate_ਸਿਰਾ(&ਧਾਰਾ);
}

#ਜੇ_ਅੰਤ /*#ifndef MINIZ_NO_INFLATE_APIS*/

ਅਚਲ ਅੱਖਰ *mz_error(ਪੂਰਨ err)
{
  ਸਥਿਰ ਬਣਤਰ { ਪੂਰਨ m_err; ਅਚਲ ਅੱਖਰ *m_pDesc; } s_error_descs[] =
  {
    { MZ_OK, "" }, { MZ_ਧਾਰਾ_ਸਿਰਾ, "stream end" }, { MZ_NEED_DICT, "need dictionary" }, { MZ_ERRNO, "file error" }, { MZ_ਧਾਰਾ_ERROR, "stream error" },
    { MZ_ਅੰਕੜੇ_ERROR, "data error" }, { MZ_MEM_ERROR, "out of memory" }, { MZ_BUF_ERROR, "buf error" }, { MZ_ਸੰਸਕਰਣ_ERROR, "version error" }, { MZ_PARAM_ERROR, "parameter error" }
  };
  mz_uint i; ਲਈ (i = 0; i < ਆਕਾਰ(s_error_descs) / ਆਕਾਰ(s_error_descs[0]); ++i) ਜੇ (s_error_descs[i].m_err == err) ਵਾਪਸ s_error_descs[i].m_pDesc;
  ਵਾਪਸ ਨਿਰਾ;
}

#ਜੇ_ਅੰਤ //MINIZ_NO_ZLIB_APIS

// ------------------- Low-level Decompression (completely independent from all compression API's)
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_INFLATE_APIS

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TINFL_MEMCPY(d, s, l) ਸਮ੍ਰਿਤੀ_ਨਕਲ(d, s, l)
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TINFL_MEMSET(p, c, l) memset(p, c, l)

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TINFL_CR_BEGIN ਚੋਣ(r->m_state) { ਹਾਲਤ 0:
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TINFL_CR_RETURN(state_ਸੂਚਕਾਂਕ, ਨਤੀਜਾ) ਕਰੋ { ਸਥਿਤੀ = ਨਤੀਜਾ; r->m_state = state_ਸੂਚਕਾਂਕ; ਜਾਓ common_exit; ਹਾਲਤ state_ਸੂਚਕਾਂਕ:; } MZ_MACRO_ਸਿਰਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TINFL_CR_RETURN_FOREVER(state_ਸੂਚਕਾਂਕ, ਨਤੀਜਾ) ਕਰੋ { ਲਈ ( ; ; ) { TINFL_CR_RETURN(state_ਸੂਚਕਾਂਕ, ਨਤੀਜਾ); } } MZ_MACRO_ਸਿਰਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TINFL_CR_ਅੰਤ }

// TODO: If the caller has indicated that there's no more input, and we attempt to read beyond the input buf, then something is wrong with the input because the inflator never
// reads ahead more than it needs to. Currently TINFL_GET_BYTE() pads the end of the stream with 0's in this scenario.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TINFL_GET_BYTE(state_ਸੂਚਕਾਂਕ, c) ਕਰੋ { \
  ਜੇ (p_ਵਿੱਚ_buf_cur >= p_ਵਿੱਚ_buf_ਸਿਰਾ) { \
    ਲਈ ( ; ; ) { \
      ਜੇ (decomp_flags & TINFL_FLAG_HAS_ਹੋਰ_ਨਿਵੇਸ਼) { \
        TINFL_CR_RETURN(state_ਸੂਚਕਾਂਕ, TINFL_ਸਥਿਤੀ_NEEDS_ਹੋਰ_ਨਿਵੇਸ਼); \
        ਜੇ (p_ਵਿੱਚ_buf_cur < p_ਵਿੱਚ_buf_ਸਿਰਾ) { \
          c = *p_ਵਿੱਚ_buf_cur++; \
          ਰੋਕੋ; \
        } \
      } ਨਹੀਂਤਾਂ { \
        c = 0; \
        ਰੋਕੋ; \
      } \
    } \
  } ਨਹੀਂਤਾਂ c = *p_ਵਿੱਚ_buf_cur++; } MZ_MACRO_ਸਿਰਾ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TINFL_NEED_ਬਿੱਟ(state_ਸੂਚਕਾਂਕ, n) ਕਰੋ { mz_uint c; TINFL_GET_BYTE(state_ਸੂਚਕਾਂਕ, c); ਦੋਆਧਾਰੀ_ਅੰਕ_buf |= (((tinfl_ਦੋਆਧਾਰੀ_ਅੰਕ_buf_t)c) << ਅੰਕ_ਬਿੱਟ); ਅੰਕ_ਬਿੱਟ += 8; } ਜਦੋਂ (ਅੰਕ_ਬਿੱਟ < (mz_uint)(n))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TINFL_SKIP_ਬਿੱਟ(state_ਸੂਚਕਾਂਕ, n) ਕਰੋ { ਜੇ (ਅੰਕ_ਬਿੱਟ < (mz_uint)(n)) { TINFL_NEED_ਬਿੱਟ(state_ਸੂਚਕਾਂਕ, n); } ਦੋਆਧਾਰੀ_ਅੰਕ_buf >>= (n); ਅੰਕ_ਬਿੱਟ -= (n); } MZ_MACRO_ਸਿਰਾ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TINFL_GET_ਬਿੱਟ(state_ਸੂਚਕਾਂਕ, b, n) ਕਰੋ { ਜੇ (ਅੰਕ_ਬਿੱਟ < (mz_uint)(n)) { TINFL_NEED_ਬਿੱਟ(state_ਸੂਚਕਾਂਕ, n); } b = ਦੋਆਧਾਰੀ_ਅੰਕ_buf & ((1 << (n)) - 1); ਦੋਆਧਾਰੀ_ਅੰਕ_buf >>= (n); ਅੰਕ_ਬਿੱਟ -= (n); } MZ_MACRO_ਸਿਰਾ

// TINFL_HUFF_BITBUF_FILL() is only used rarely, when the number of bytes remaining in the input buffer falls below 2.
// It reads just enough bytes from the input stream that are needed to decode the next Huffman code (and absolutely no more). It works by trying to fully decode a
// Huffman code by using whatever bits are currently present in the bit buffer. If this fails, it reads another byte, and tries again until it succeeds or until the
// bit buffer contains >=15 bits (deflate's max. Huffman code size).
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TINFL_HUFF_BITBUF_FILL(state_ਸੂਚਕਾਂਕ, pHuff) \
  ਕਰੋ { \
    ਆਰਜ਼ੀ = (pHuff)->m_look_ਉੱਪਰ[ਦੋਆਧਾਰੀ_ਅੰਕ_buf & (TINFL_FAST_LOOKUP_ਮਾਪ - 1)]; \
    ਜੇ (ਆਰਜ਼ੀ >= 0) { \
      ਕੋਡ_len = ਆਰਜ਼ੀ >> 9; \
      ਜੇ ((ਕੋਡ_len) && (ਅੰਕ_ਬਿੱਟ >= ਕੋਡ_len)) \
          ਰੋਕੋ; \
    } ਨਹੀਂਤਾਂ ਜੇ (ਅੰਕ_ਬਿੱਟ > TINFL_FAST_LOOKUP_ਬਿੱਟ) { \
       ਕੋਡ_len = TINFL_FAST_LOOKUP_ਬਿੱਟ; \
       ਕਰੋ { \
          ਆਰਜ਼ੀ = (pHuff)->m_ਰੁੱਖ[~ਆਰਜ਼ੀ + ((ਦੋਆਧਾਰੀ_ਅੰਕ_buf >> ਕੋਡ_len++) & 1)]; \
       } ਜਦੋਂ ((ਆਰਜ਼ੀ < 0) && (ਅੰਕ_ਬਿੱਟ >= (ਕੋਡ_len + 1))); \
       ਜੇ (ਆਰਜ਼ੀ >= 0) ਰੋਕੋ; \
    } \
    TINFL_GET_BYTE(state_ਸੂਚਕਾਂਕ, c); \
    ਦੋਆਧਾਰੀ_ਅੰਕ_buf |= (((tinfl_ਦੋਆਧਾਰੀ_ਅੰਕ_buf_t)c) << ਅੰਕ_ਬਿੱਟ); \
    ਅੰਕ_ਬਿੱਟ += 8; \
  } ਜਦੋਂ (ਅੰਕ_ਬਿੱਟ < 15);

// TINFL_HUFF_DECODE() decodes the next Huffman coded symbol. It's more complex than you would initially expect because the zlib API expects the decompressor to never read
// beyond the final byte of the deflate stream. (In other words, when this macro wants to read another byte from the input, it REALLY needs another byte in order to fully
// decode the next Huffman code.) Handling this properly is particularly important on raw deflate (non-zlib) streams, which aren't followed by a byte aligned adler-32.
// The slow path is only executed at the very end of the input buffer.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TINFL_HUFF_DECODE(state_ਸੂਚਕਾਂਕ, sym, pHuff) ਕਰੋ { \
  ਪੂਰਨ ਆਰਜ਼ੀ; mz_uint ਕੋਡ_len, c; \
  ਜੇ (ਅੰਕ_ਬਿੱਟ < 15) { \
    ਜੇ ((p_ਵਿੱਚ_buf_ਸਿਰਾ - p_ਵਿੱਚ_buf_cur) < 2) { \
       TINFL_HUFF_BITBUF_FILL(state_ਸੂਚਕਾਂਕ, pHuff); \
    } ਨਹੀਂਤਾਂ { \
       ਦੋਆਧਾਰੀ_ਅੰਕ_buf |= (((tinfl_ਦੋਆਧਾਰੀ_ਅੰਕ_buf_t)p_ਵਿੱਚ_buf_cur[0]) << ਅੰਕ_ਬਿੱਟ) | (((tinfl_ਦੋਆਧਾਰੀ_ਅੰਕ_buf_t)p_ਵਿੱਚ_buf_cur[1]) << (ਅੰਕ_ਬਿੱਟ + 8)); p_ਵਿੱਚ_buf_cur += 2; ਅੰਕ_ਬਿੱਟ += 16; \
    } \
  } \
  ਜੇ ((ਆਰਜ਼ੀ = (pHuff)->m_look_ਉੱਪਰ[ਦੋਆਧਾਰੀ_ਅੰਕ_buf & (TINFL_FAST_LOOKUP_ਮਾਪ - 1)]) >= 0) \
    ਕੋਡ_len = ਆਰਜ਼ੀ >> 9, ਆਰਜ਼ੀ &= 511; \
  ਨਹੀਂਤਾਂ { \
    ਕੋਡ_len = TINFL_FAST_LOOKUP_ਬਿੱਟ; ਕਰੋ { ਆਰਜ਼ੀ = (pHuff)->m_ਰੁੱਖ[~ਆਰਜ਼ੀ + ((ਦੋਆਧਾਰੀ_ਅੰਕ_buf >> ਕੋਡ_len++) & 1)]; } ਜਦੋਂ (ਆਰਜ਼ੀ < 0); \
  } sym = ਆਰਜ਼ੀ; ਦੋਆਧਾਰੀ_ਅੰਕ_buf >>= ਕੋਡ_len; ਅੰਕ_ਬਿੱਟ -= ਕੋਡ_len; } MZ_MACRO_ਸਿਰਾ

tinfl_ਸਥਿਤੀ tinfl_decompress(tinfl_decompressor *r, ਅਚਲ mz_uint8 *p_ਵਿੱਚ_buf_ਅਗਲਾ, size_t *p_ਵਿੱਚ_buf_ਮਾਪ, mz_uint8 *p_ਬਾਹਰਲਾ_buf_ਸ਼ੁਰੂ, mz_uint8 *p_ਬਾਹਰਲਾ_buf_ਅਗਲਾ, size_t *p_ਬਾਹਰਲਾ_buf_ਮਾਪ, ਅਚਲ mz_uint32 decomp_flags)
{
  ਸਥਿਰ ਅਚਲ ਪੂਰਨ s_ਲੰਮਾਈ_ਅਧਾਰ[31] = { 3,4,5,6,7,8,9,10,11,13, 15,17,19,23,27,31,35,43,51,59, 67,83,99,115,131,163,195,227,258,0,0 };
  ਸਥਿਰ ਅਚਲ ਪੂਰਨ s_ਲੰਮਾਈ_extra[31]= { 0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,0,0,0 };
  ਸਥਿਰ ਅਚਲ ਪੂਰਨ s_dist_ਅਧਾਰ[32] = { 1,2,3,4,5,7,9,13,17,25,33,49,65,97,129,193, 257,385,513,769,1025,1537,2049,3073,4097,6145,8193,12289,16385,24577,0,0};
  ਸਥਿਰ ਅਚਲ ਪੂਰਨ s_dist_extra[32] = { 0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13};
  ਸਥਿਰ ਅਚਲ mz_uint8 s_ਲੰਮਾਈ_dezigzag[19] = { 16,17,18,0,8,7,9,6,10,5,11,4,12,3,13,2,14,1,15 };
  ਸਥਿਰ ਅਚਲ ਪੂਰਨ s_min_ਸਾਰਣੀ_sizes[3] = { 257, 1, 4 };

  tinfl_ਸਥਿਤੀ ਸਥਿਤੀ = TINFL_ਸਥਿਤੀ_FAILED; mz_uint32 ਅੰਕ_ਬਿੱਟ, dist, counter, ਅੰਕ_extra; tinfl_ਦੋਆਧਾਰੀ_ਅੰਕ_buf_t ਦੋਆਧਾਰੀ_ਅੰਕ_buf;
  ਅਚਲ mz_uint8 *p_ਵਿੱਚ_buf_cur = p_ਵਿੱਚ_buf_ਅਗਲਾ, *ਅਚਲ p_ਵਿੱਚ_buf_ਸਿਰਾ = p_ਵਿੱਚ_buf_ਅਗਲਾ + *p_ਵਿੱਚ_buf_ਮਾਪ;
  mz_uint8 *p_ਬਾਹਰਲਾ_buf_cur = p_ਬਾਹਰਲਾ_buf_ਅਗਲਾ, *ਅਚਲ p_ਬਾਹਰਲਾ_buf_ਸਿਰਾ = p_ਬਾਹਰਲਾ_buf_ਅਗਲਾ + *p_ਬਾਹਰਲਾ_buf_ਮਾਪ;
  size_t ਬਾਹਰਲਾ_buf_ਮਾਪ_ਨਕਾਬ = (decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF) ? (size_t)-1 : ((p_ਬਾਹਰਲਾ_buf_ਅਗਲਾ - p_ਬਾਹਰਲਾ_buf_ਸ਼ੁਰੂ) + *p_ਬਾਹਰਲਾ_buf_ਮਾਪ) - 1, dist_from_ਬਾਹਰਲਾ_buf_ਸ਼ੁਰੂ;

  // Ensure the output buffer's size is a power of 2, unless the output buffer is large enough to hold the entire output file (in which case it doesn't matter).
  ਜੇ (((ਬਾਹਰਲਾ_buf_ਮਾਪ_ਨਕਾਬ + 1) & ਬਾਹਰਲਾ_buf_ਮਾਪ_ਨਕਾਬ) || (p_ਬਾਹਰਲਾ_buf_ਅਗਲਾ < p_ਬਾਹਰਲਾ_buf_ਸ਼ੁਰੂ)) { *p_ਵਿੱਚ_buf_ਮਾਪ = *p_ਬਾਹਰਲਾ_buf_ਮਾਪ = 0; ਵਾਪਸ TINFL_ਸਥਿਤੀ_BAD_PARAM; }

  ਅੰਕ_ਬਿੱਟ = r->m_ਅੰਕ_ਬਿੱਟ; ਦੋਆਧਾਰੀ_ਅੰਕ_buf = r->m_ਦੋਆਧਾਰੀ_ਅੰਕ_buf; dist = r->m_dist; counter = r->m_counter; ਅੰਕ_extra = r->m_ਅੰਕ_extra; dist_from_ਬਾਹਰਲਾ_buf_ਸ਼ੁਰੂ = r->m_dist_from_ਬਾਹਰਲਾ_buf_ਸ਼ੁਰੂ;
  TINFL_CR_BEGIN

  ਦੋਆਧਾਰੀ_ਅੰਕ_buf = ਅੰਕ_ਬਿੱਟ = dist = counter = ਅੰਕ_extra = r->m_zhdr0 = r->m_zhdr1 = 0; r->m_z_adler32 = r->m_check_adler32 = 1;
  ਜੇ (decomp_flags & TINFL_FLAG_PARSE_ZLIB_ਸਿਰਲੇਖ)
  {
    TINFL_GET_BYTE(1, r->m_zhdr0); TINFL_GET_BYTE(2, r->m_zhdr1);
    counter = (((r->m_zhdr0 * 256 + r->m_zhdr1) % 31 != 0) || (r->m_zhdr1 & 32) || ((r->m_zhdr0 & 15) != 8));
    ਜੇ (!(decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF)) counter |= (((1U << (8U + (r->m_zhdr0 >> 4))) > 32768U) || ((ਬਾਹਰਲਾ_buf_ਮਾਪ_ਨਕਾਬ + 1) < (size_t)(1U << (8U + (r->m_zhdr0 >> 4)))));
    ਜੇ (counter) { TINFL_CR_RETURN_FOREVER(36, TINFL_ਸਥਿਤੀ_FAILED); }
  }

  ਕਰੋ
  {
    TINFL_GET_ਬਿੱਟ(3, r->m_final, 3); r->m_type = r->m_final >> 1;
    ਜੇ (r->m_type == 0)
    {
      TINFL_SKIP_ਬਿੱਟ(5, ਅੰਕ_ਬਿੱਟ & 7);
      ਲਈ (counter = 0; counter < 4; ++counter) { ਜੇ (ਅੰਕ_ਬਿੱਟ) TINFL_GET_ਬਿੱਟ(6, r->m_raw_ਸਿਰਲੇਖ[counter], 8); ਨਹੀਂਤਾਂ TINFL_GET_BYTE(7, r->m_raw_ਸਿਰਲੇਖ[counter]); }
      ਜੇ ((counter = (r->m_raw_ਸਿਰਲੇਖ[0] | (r->m_raw_ਸਿਰਲੇਖ[1] << 8))) != (mz_uint)(0xFFFF ^ (r->m_raw_ਸਿਰਲੇਖ[2] | (r->m_raw_ਸਿਰਲੇਖ[3] << 8)))) { TINFL_CR_RETURN_FOREVER(39, TINFL_ਸਥਿਤੀ_FAILED); }
      ਜਦੋਂ ((counter) && (ਅੰਕ_ਬਿੱਟ))
      {
        TINFL_GET_ਬਿੱਟ(51, dist, 8);
        ਜਦੋਂ (p_ਬਾਹਰਲਾ_buf_cur >= p_ਬਾਹਰਲਾ_buf_ਸਿਰਾ) { TINFL_CR_RETURN(52, TINFL_ਸਥਿਤੀ_HAS_ਹੋਰ_OUTPUT); }
        *p_ਬਾਹਰਲਾ_buf_cur++ = (mz_uint8)dist;
        counter--;
      }
      ਜਦੋਂ (counter)
      {
        size_t n; ਜਦੋਂ (p_ਬਾਹਰਲਾ_buf_cur >= p_ਬਾਹਰਲਾ_buf_ਸਿਰਾ) { TINFL_CR_RETURN(9, TINFL_ਸਥਿਤੀ_HAS_ਹੋਰ_OUTPUT); }
        ਜਦੋਂ (p_ਵਿੱਚ_buf_cur >= p_ਵਿੱਚ_buf_ਸਿਰਾ)
        {
          ਜੇ (decomp_flags & TINFL_FLAG_HAS_ਹੋਰ_ਨਿਵੇਸ਼)
          {
            TINFL_CR_RETURN(38, TINFL_ਸਥਿਤੀ_NEEDS_ਹੋਰ_ਨਿਵੇਸ਼);
          }
          ਨਹੀਂਤਾਂ
          {
            TINFL_CR_RETURN_FOREVER(40, TINFL_ਸਥਿਤੀ_FAILED);
          }
        }
        n = MZ_MIN(MZ_MIN((size_t)(p_ਬਾਹਰਲਾ_buf_ਸਿਰਾ - p_ਬਾਹਰਲਾ_buf_cur), (size_t)(p_ਵਿੱਚ_buf_ਸਿਰਾ - p_ਵਿੱਚ_buf_cur)), counter);
        TINFL_MEMCPY(p_ਬਾਹਰਲਾ_buf_cur, p_ਵਿੱਚ_buf_cur, n); p_ਵਿੱਚ_buf_cur += n; p_ਬਾਹਰਲਾ_buf_cur += n; counter -= (mz_uint)n;
      }
    }
    ਨਹੀਂਤਾਂ ਜੇ (r->m_type == 3)
    {
      TINFL_CR_RETURN_FOREVER(10, TINFL_ਸਥਿਤੀ_FAILED);
    }
    ਨਹੀਂਤਾਂ
    {
      ਜੇ (r->m_type == 1)
      {
        mz_uint8 *p = r->m_tables[0].m_ਕੋਡ_ਮਾਪ; mz_uint i;
        r->m_ਸਾਰਣੀ_sizes[0] = 288; r->m_ਸਾਰਣੀ_sizes[1] = 32; TINFL_MEMSET(r->m_tables[1].m_ਕੋਡ_ਮਾਪ, 5, 32);
        ਲਈ ( i = 0; i <= 143; ++i) *p++ = 8;
        ਲਈ ( ; i <= 255; ++i) *p++ = 9;
        ਲਈ ( ; i <= 279; ++i) *p++ = 7;
        ਲਈ ( ; i <= 287; ++i) *p++ = 8;
      }
      ਨਹੀਂਤਾਂ
      {
        ਲਈ (counter = 0; counter < 3; counter++) { TINFL_GET_ਬਿੱਟ(11, r->m_ਸਾਰਣੀ_sizes[counter], "\05\05\04"[counter]); r->m_ਸਾਰਣੀ_sizes[counter] += s_min_ਸਾਰਣੀ_sizes[counter]; }
        MZ_CLEAR_ARR(r->m_tables[2].m_ਕੋਡ_ਮਾਪ); ਲਈ (counter = 0; counter < r->m_ਸਾਰਣੀ_sizes[2]; counter++) { mz_uint s; TINFL_GET_ਬਿੱਟ(14, s, 3); r->m_tables[2].m_ਕੋਡ_ਮਾਪ[s_ਲੰਮਾਈ_dezigzag[counter]] = (mz_uint8)s; }
        r->m_ਸਾਰਣੀ_sizes[2] = 19;
      }
      ਲਈ ( ; (ਪੂਰਨ)r->m_type >= 0; r->m_type--)
      {
        ਪੂਰਨ ਰੁੱਖ_ਅਗਲਾ, ਰੁੱਖ_cur; tinfl_huff_ਸਾਰਣੀ *p_ਸਾਰਣੀ;
        mz_uint i, j, ਵਰਤਿਆ_syms, ਕੁੱਲ, sym_ਸੂਚਕਾਂਕ, ਅਗਲਾ_ਕੋਡ[17], ਕੁੱਲ_syms[16]; p_ਸਾਰਣੀ = &r->m_tables[r->m_type]; MZ_CLEAR_ARR(ਕੁੱਲ_syms); MZ_CLEAR_ARR(p_ਸਾਰਣੀ->m_look_ਉੱਪਰ); MZ_CLEAR_ARR(p_ਸਾਰਣੀ->m_ਰੁੱਖ);
        ਲਈ (i = 0; i < r->m_ਸਾਰਣੀ_sizes[r->m_type]; ++i) ਕੁੱਲ_syms[p_ਸਾਰਣੀ->m_ਕੋਡ_ਮਾਪ[i]]++;
        ਵਰਤਿਆ_syms = 0, ਕੁੱਲ = 0; ਅਗਲਾ_ਕੋਡ[0] = ਅਗਲਾ_ਕੋਡ[1] = 0;
        ਲਈ (i = 1; i <= 15; ++i) { ਵਰਤਿਆ_syms += ਕੁੱਲ_syms[i]; ਅਗਲਾ_ਕੋਡ[i + 1] = (ਕੁੱਲ = ((ਕੁੱਲ + ਕੁੱਲ_syms[i]) << 1)); }
        ਜੇ ((65536 != ਕੁੱਲ) && (ਵਰਤਿਆ_syms > 1))
        {
          TINFL_CR_RETURN_FOREVER(35, TINFL_ਸਥਿਤੀ_FAILED);
        }
        ਲਈ (ਰੁੱਖ_ਅਗਲਾ = -1, sym_ਸੂਚਕਾਂਕ = 0; sym_ਸੂਚਕਾਂਕ < r->m_ਸਾਰਣੀ_sizes[r->m_type]; ++sym_ਸੂਚਕਾਂਕ)
        {
          mz_uint rev_ਕੋਡ = 0, l, cur_ਕੋਡ, ਕੋਡ_ਮਾਪ_2 = p_ਸਾਰਣੀ->m_ਕੋਡ_ਮਾਪ[sym_ਸੂਚਕਾਂਕ]; ਜੇ (!ਕੋਡ_ਮਾਪ_2) ਜਾਰੀ;
          cur_ਕੋਡ = ਅਗਲਾ_ਕੋਡ[ਕੋਡ_ਮਾਪ_2]++; ਲਈ (l = ਕੋਡ_ਮਾਪ_2; l > 0; l--, cur_ਕੋਡ >>= 1) rev_ਕੋਡ = (rev_ਕੋਡ << 1) | (cur_ਕੋਡ & 1);
          ਜੇ (ਕੋਡ_ਮਾਪ_2 <= TINFL_FAST_LOOKUP_ਬਿੱਟ) { mz_int16 k = (mz_int16)((ਕੋਡ_ਮਾਪ_2 << 9) | sym_ਸੂਚਕਾਂਕ); ਜਦੋਂ (rev_ਕੋਡ < TINFL_FAST_LOOKUP_ਮਾਪ) { p_ਸਾਰਣੀ->m_look_ਉੱਪਰ[rev_ਕੋਡ] = k; rev_ਕੋਡ += (1 << ਕੋਡ_ਮਾਪ_2); } ਜਾਰੀ; }
          ਜੇ (0 == (ਰੁੱਖ_cur = p_ਸਾਰਣੀ->m_look_ਉੱਪਰ[rev_ਕੋਡ & (TINFL_FAST_LOOKUP_ਮਾਪ - 1)])) { p_ਸਾਰਣੀ->m_look_ਉੱਪਰ[rev_ਕੋਡ & (TINFL_FAST_LOOKUP_ਮਾਪ - 1)] = (mz_int16)ਰੁੱਖ_ਅਗਲਾ; ਰੁੱਖ_cur = ਰੁੱਖ_ਅਗਲਾ; ਰੁੱਖ_ਅਗਲਾ -= 2; }
          rev_ਕੋਡ >>= (TINFL_FAST_LOOKUP_ਬਿੱਟ - 1);
          ਲਈ (j = ਕੋਡ_ਮਾਪ_2; j > (TINFL_FAST_LOOKUP_ਬਿੱਟ + 1); j--)
          {
            ਰੁੱਖ_cur -= ((rev_ਕੋਡ >>= 1) & 1);
            ਜੇ (!p_ਸਾਰਣੀ->m_ਰੁੱਖ[-ਰੁੱਖ_cur - 1]) { p_ਸਾਰਣੀ->m_ਰੁੱਖ[-ਰੁੱਖ_cur - 1] = (mz_int16)ਰੁੱਖ_ਅਗਲਾ; ਰੁੱਖ_cur = ਰੁੱਖ_ਅਗਲਾ; ਰੁੱਖ_ਅਗਲਾ -= 2; } ਨਹੀਂਤਾਂ ਰੁੱਖ_cur = p_ਸਾਰਣੀ->m_ਰੁੱਖ[-ਰੁੱਖ_cur - 1];
          }
          ਰੁੱਖ_cur -= ((rev_ਕੋਡ >>= 1) & 1); p_ਸਾਰਣੀ->m_ਰੁੱਖ[-ਰੁੱਖ_cur - 1] = (mz_int16)sym_ਸੂਚਕਾਂਕ;
        }
        ਜੇ (r->m_type == 2)
        {
          ਲਈ (counter = 0; counter < (r->m_ਸਾਰਣੀ_sizes[0] + r->m_ਸਾਰਣੀ_sizes[1]); )
          {
            mz_uint s; TINFL_HUFF_DECODE(16, dist, &r->m_tables[2]); ਜੇ (dist < 16) { r->m_len_codes[counter++] = (mz_uint8)dist; ਜਾਰੀ; }
            ਜੇ ((dist == 16) && (!counter))
            {
              TINFL_CR_RETURN_FOREVER(17, TINFL_ਸਥਿਤੀ_FAILED);
            }
            ਅੰਕ_extra = "\02\03\07"[dist - 16]; TINFL_GET_ਬਿੱਟ(18, s, ਅੰਕ_extra); s += "\03\03\013"[dist - 16];
            TINFL_MEMSET(r->m_len_codes + counter, (dist == 16) ? r->m_len_codes[counter - 1] : 0, s); counter += s;
          }
          ਜੇ ((r->m_ਸਾਰਣੀ_sizes[0] + r->m_ਸਾਰਣੀ_sizes[1]) != counter)
          {
            TINFL_CR_RETURN_FOREVER(21, TINFL_ਸਥਿਤੀ_FAILED);
          }
          TINFL_MEMCPY(r->m_tables[0].m_ਕੋਡ_ਮਾਪ, r->m_len_codes, r->m_ਸਾਰਣੀ_sizes[0]); TINFL_MEMCPY(r->m_tables[1].m_ਕੋਡ_ਮਾਪ, r->m_len_codes + r->m_ਸਾਰਣੀ_sizes[0], r->m_ਸਾਰਣੀ_sizes[1]);
        }
      }
      ਲਈ ( ; ; )
      {
        mz_uint8 *pSrc;
        ਲਈ ( ; ; )
        {
          ਜੇ (((p_ਵਿੱਚ_buf_ਸਿਰਾ - p_ਵਿੱਚ_buf_cur) < 4) || ((p_ਬਾਹਰਲਾ_buf_ਸਿਰਾ - p_ਬਾਹਰਲਾ_buf_cur) < 2))
          {
            TINFL_HUFF_DECODE(23, counter, &r->m_tables[0]);
            ਜੇ (counter >= 256)
              ਰੋਕੋ;
            ਜਦੋਂ (p_ਬਾਹਰਲਾ_buf_cur >= p_ਬਾਹਰਲਾ_buf_ਸਿਰਾ) { TINFL_CR_RETURN(24, TINFL_ਸਥਿਤੀ_HAS_ਹੋਰ_OUTPUT); }
            *p_ਬਾਹਰਲਾ_buf_cur++ = (mz_uint8)counter;
          }
          ਨਹੀਂਤਾਂ
          {
            ਪੂਰਨ sym2; mz_uint ਕੋਡ_len;
#ਜੇ TINFL_USE_64_ਦੋਆਧਾਰੀ_ਅੰਕ_BITBUF
            ਜੇ (ਅੰਕ_ਬਿੱਟ < 30) { ਦੋਆਧਾਰੀ_ਅੰਕ_buf |= (((tinfl_ਦੋਆਧਾਰੀ_ਅੰਕ_buf_t)MZ_READ_LE32(p_ਵਿੱਚ_buf_cur)) << ਅੰਕ_ਬਿੱਟ); p_ਵਿੱਚ_buf_cur += 4; ਅੰਕ_ਬਿੱਟ += 32; }
#ਨਹੀਂਤਾਂ
            ਜੇ (ਅੰਕ_ਬਿੱਟ < 15) { ਦੋਆਧਾਰੀ_ਅੰਕ_buf |= (((tinfl_ਦੋਆਧਾਰੀ_ਅੰਕ_buf_t)MZ_READ_LE16(p_ਵਿੱਚ_buf_cur)) << ਅੰਕ_ਬਿੱਟ); p_ਵਿੱਚ_buf_cur += 2; ਅੰਕ_ਬਿੱਟ += 16; }
#ਜੇ_ਅੰਤ
            ਜੇ ((sym2 = r->m_tables[0].m_look_ਉੱਪਰ[ਦੋਆਧਾਰੀ_ਅੰਕ_buf & (TINFL_FAST_LOOKUP_ਮਾਪ - 1)]) >= 0)
              ਕੋਡ_len = sym2 >> 9;
            ਨਹੀਂਤਾਂ
            {
              ਕੋਡ_len = TINFL_FAST_LOOKUP_ਬਿੱਟ; ਕਰੋ { sym2 = r->m_tables[0].m_ਰੁੱਖ[~sym2 + ((ਦੋਆਧਾਰੀ_ਅੰਕ_buf >> ਕੋਡ_len++) & 1)]; } ਜਦੋਂ (sym2 < 0);
            }
            counter = sym2; ਦੋਆਧਾਰੀ_ਅੰਕ_buf >>= ਕੋਡ_len; ਅੰਕ_ਬਿੱਟ -= ਕੋਡ_len;
            ਜੇ (counter & 256)
              ਰੋਕੋ;

#ਜੇ !TINFL_USE_64_ਦੋਆਧਾਰੀ_ਅੰਕ_BITBUF
            ਜੇ (ਅੰਕ_ਬਿੱਟ < 15) { ਦੋਆਧਾਰੀ_ਅੰਕ_buf |= (((tinfl_ਦੋਆਧਾਰੀ_ਅੰਕ_buf_t)MZ_READ_LE16(p_ਵਿੱਚ_buf_cur)) << ਅੰਕ_ਬਿੱਟ); p_ਵਿੱਚ_buf_cur += 2; ਅੰਕ_ਬਿੱਟ += 16; }
#ਜੇ_ਅੰਤ
            ਜੇ ((sym2 = r->m_tables[0].m_look_ਉੱਪਰ[ਦੋਆਧਾਰੀ_ਅੰਕ_buf & (TINFL_FAST_LOOKUP_ਮਾਪ - 1)]) >= 0)
              ਕੋਡ_len = sym2 >> 9;
            ਨਹੀਂਤਾਂ
            {
              ਕੋਡ_len = TINFL_FAST_LOOKUP_ਬਿੱਟ; ਕਰੋ { sym2 = r->m_tables[0].m_ਰੁੱਖ[~sym2 + ((ਦੋਆਧਾਰੀ_ਅੰਕ_buf >> ਕੋਡ_len++) & 1)]; } ਜਦੋਂ (sym2 < 0);
            }
            ਦੋਆਧਾਰੀ_ਅੰਕ_buf >>= ਕੋਡ_len; ਅੰਕ_ਬਿੱਟ -= ਕੋਡ_len;

            p_ਬਾਹਰਲਾ_buf_cur[0] = (mz_uint8)counter;
            ਜੇ (sym2 & 256)
            {
              p_ਬਾਹਰਲਾ_buf_cur++;
              counter = sym2;
              ਰੋਕੋ;
            }
            p_ਬਾਹਰਲਾ_buf_cur[1] = (mz_uint8)sym2;
            p_ਬਾਹਰਲਾ_buf_cur += 2;
          }
        }
        ਜੇ ((counter &= 511) == 256) ਰੋਕੋ;

        ਅੰਕ_extra = s_ਲੰਮਾਈ_extra[counter - 257]; counter = s_ਲੰਮਾਈ_ਅਧਾਰ[counter - 257];
        ਜੇ (ਅੰਕ_extra) { mz_uint extra_ਬਿੱਟ; TINFL_GET_ਬਿੱਟ(25, extra_ਬਿੱਟ, ਅੰਕ_extra); counter += extra_ਬਿੱਟ; }

        TINFL_HUFF_DECODE(26, dist, &r->m_tables[1]);
        ਅੰਕ_extra = s_dist_extra[dist]; dist = s_dist_ਅਧਾਰ[dist];
        ਜੇ (ਅੰਕ_extra) { mz_uint extra_ਬਿੱਟ; TINFL_GET_ਬਿੱਟ(27, extra_ਬਿੱਟ, ਅੰਕ_extra); dist += extra_ਬਿੱਟ; }

        dist_from_ਬਾਹਰਲਾ_buf_ਸ਼ੁਰੂ = p_ਬਾਹਰਲਾ_buf_cur - p_ਬਾਹਰਲਾ_buf_ਸ਼ੁਰੂ;
        ਜੇ ((dist > dist_from_ਬਾਹਰਲਾ_buf_ਸ਼ੁਰੂ) && (decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF))
        {
          TINFL_CR_RETURN_FOREVER(37, TINFL_ਸਥਿਤੀ_FAILED);
        }

        pSrc = p_ਬਾਹਰਲਾ_buf_ਸ਼ੁਰੂ + ((dist_from_ਬਾਹਰਲਾ_buf_ਸ਼ੁਰੂ - dist) & ਬਾਹਰਲਾ_buf_ਮਾਪ_ਨਕਾਬ);

        ਜੇ ((MZ_MAX(p_ਬਾਹਰਲਾ_buf_cur, pSrc) + counter) > p_ਬਾਹਰਲਾ_buf_ਸਿਰਾ)
        {
          ਜਦੋਂ (counter--)
          {
            ਜਦੋਂ (p_ਬਾਹਰਲਾ_buf_cur >= p_ਬਾਹਰਲਾ_buf_ਸਿਰਾ) { TINFL_CR_RETURN(53, TINFL_ਸਥਿਤੀ_HAS_ਹੋਰ_OUTPUT); }
            *p_ਬਾਹਰਲਾ_buf_cur++ = p_ਬਾਹਰਲਾ_buf_ਸ਼ੁਰੂ[(dist_from_ਬਾਹਰਲਾ_buf_ਸ਼ੁਰੂ++ - dist) & ਬਾਹਰਲਾ_buf_ਮਾਪ_ਨਕਾਬ];
          }
          ਜਾਰੀ;
        }
#ਜੇ MINIZ_USE_UNALIGNED_LOADS_AND_STORES
        ਨਹੀਂਤਾਂ ਜੇ ((counter >= 9) && (counter <= dist))
        {
          ਅਚਲ mz_uint8 *p_Src_ਸਿਰਾ = pSrc + (counter & ~7);
          ਕਰੋ
          {
            ((mz_uint32 *)p_ਬਾਹਰਲਾ_buf_cur)[0] = ((ਅਚਲ mz_uint32 *)pSrc)[0];
            ((mz_uint32 *)p_ਬਾਹਰਲਾ_buf_cur)[1] = ((ਅਚਲ mz_uint32 *)pSrc)[1];
            p_ਬਾਹਰਲਾ_buf_cur += 8;
          } ਜਦੋਂ ((pSrc += 8) < p_Src_ਸਿਰਾ);
          ਜੇ ((counter &= 7) < 3)
          {
            ਜੇ (counter)
            {
              p_ਬਾਹਰਲਾ_buf_cur[0] = pSrc[0];
              ਜੇ (counter > 1)
                p_ਬਾਹਰਲਾ_buf_cur[1] = pSrc[1];
              p_ਬਾਹਰਲਾ_buf_cur += counter;
            }
            ਜਾਰੀ;
          }
        }
#ਜੇ_ਅੰਤ
        ਕਰੋ
        {
          p_ਬਾਹਰਲਾ_buf_cur[0] = pSrc[0];
          p_ਬਾਹਰਲਾ_buf_cur[1] = pSrc[1];
          p_ਬਾਹਰਲਾ_buf_cur[2] = pSrc[2];
          p_ਬਾਹਰਲਾ_buf_cur += 3; pSrc += 3;
        } ਜਦੋਂ ((ਪੂਰਨ)(counter -= 3) > 2);
        ਜੇ ((ਪੂਰਨ)counter > 0)
        {
          p_ਬਾਹਰਲਾ_buf_cur[0] = pSrc[0];
          ਜੇ ((ਪੂਰਨ)counter > 1)
            p_ਬਾਹਰਲਾ_buf_cur[1] = pSrc[1];
          p_ਬਾਹਰਲਾ_buf_cur += counter;
        }
      }
    }
  } ਜਦੋਂ (!(r->m_final & 1));
  ਜੇ (decomp_flags & TINFL_FLAG_PARSE_ZLIB_ਸਿਰਲੇਖ)
  {
    TINFL_SKIP_ਬਿੱਟ(32, ਅੰਕ_ਬਿੱਟ & 7); ਲਈ (counter = 0; counter < 4; ++counter) { mz_uint s; ਜੇ (ਅੰਕ_ਬਿੱਟ) TINFL_GET_ਬਿੱਟ(41, s, 8); ਨਹੀਂਤਾਂ TINFL_GET_BYTE(42, s); r->m_z_adler32 = (r->m_z_adler32 << 8) | s; }
  }
  TINFL_CR_RETURN_FOREVER(34, TINFL_ਸਥਿਤੀ_ਪੂਰਾ);
  TINFL_CR_ਅੰਤ

common_exit:
  r->m_ਅੰਕ_ਬਿੱਟ = ਅੰਕ_ਬਿੱਟ; r->m_ਦੋਆਧਾਰੀ_ਅੰਕ_buf = ਦੋਆਧਾਰੀ_ਅੰਕ_buf; r->m_dist = dist; r->m_counter = counter; r->m_ਅੰਕ_extra = ਅੰਕ_extra; r->m_dist_from_ਬਾਹਰਲਾ_buf_ਸ਼ੁਰੂ = dist_from_ਬਾਹਰਲਾ_buf_ਸ਼ੁਰੂ;
  *p_ਵਿੱਚ_buf_ਮਾਪ = p_ਵਿੱਚ_buf_cur - p_ਵਿੱਚ_buf_ਅਗਲਾ; *p_ਬਾਹਰਲਾ_buf_ਮਾਪ = p_ਬਾਹਰਲਾ_buf_cur - p_ਬਾਹਰਲਾ_buf_ਅਗਲਾ;
  ਜੇ ((decomp_flags & (TINFL_FLAG_PARSE_ZLIB_ਸਿਰਲੇਖ | TINFL_FLAG_COMPUTE_ADLER32)) && (ਸਥਿਤੀ >= 0))
  {
    ਅਚਲ mz_uint8 *ptr = p_ਬਾਹਰਲਾ_buf_ਅਗਲਾ; size_t buf_len = *p_ਬਾਹਰਲਾ_buf_ਮਾਪ;
    mz_uint32 i, s1 = r->m_check_adler32 & 0xffff, s2 = r->m_check_adler32 >> 16; size_t ਖੰਡ_len = buf_len % 5552;
    ਜਦੋਂ (buf_len)
    {
      ਲਈ (i = 0; i + 7 < ਖੰਡ_len; i += 8, ptr += 8)
      {
        s1 += ptr[0], s2 += s1; s1 += ptr[1], s2 += s1; s1 += ptr[2], s2 += s1; s1 += ptr[3], s2 += s1;
        s1 += ptr[4], s2 += s1; s1 += ptr[5], s2 += s1; s1 += ptr[6], s2 += s1; s1 += ptr[7], s2 += s1;
      }
      ਲਈ ( ; i < ਖੰਡ_len; ++i) s1 += *ptr++, s2 += s1;
      s1 %= 65521U, s2 %= 65521U; buf_len -= ਖੰਡ_len; ਖੰਡ_len = 5552;
    }
    r->m_check_adler32 = (s2 << 16) + s1; ਜੇ ((ਸਥਿਤੀ == TINFL_ਸਥਿਤੀ_ਪੂਰਾ) && (decomp_flags & TINFL_FLAG_PARSE_ZLIB_ਸਿਰਲੇਖ) && (r->m_check_adler32 != r->m_z_adler32)) ਸਥਿਤੀ = TINFL_ਸਥਿਤੀ_ADLER32_MISMATCH;
  }
  ਵਾਪਸ ਸਥਿਤੀ;
}

// Higher level helper functions.
ਖਾਲੀ *tinfl_decompress_mem_ਮੰਜ਼ਿਲ_ਢੇਰ(ਅਚਲ ਖਾਲੀ *pSrc_buf, size_t src_buf_len, size_t *p_ਬਾਹਰਲਾ_len, ਪੂਰਨ flags)
{
  tinfl_decompressor decomp; ਖਾਲੀ *pBuf = ਨਿਰਾ, *pNew_buf; size_t src_buf_ofs = 0, ਬਾਹਰਲਾ_buf_ਸਮਰੱਥਾ = 0;
  *p_ਬਾਹਰਲਾ_len = 0;
  tinfl_init(&decomp);
  ਲਈ ( ; ; )
  {
    size_t src_buf_ਮਾਪ = src_buf_len - src_buf_ofs, dst_buf_ਮਾਪ = ਬਾਹਰਲਾ_buf_ਸਮਰੱਥਾ - *p_ਬਾਹਰਲਾ_len, new_ਬਾਹਰਲਾ_buf_ਸਮਰੱਥਾ;
    tinfl_ਸਥਿਤੀ ਸਥਿਤੀ = tinfl_decompress(&decomp, (ਅਚਲ mz_uint8*)pSrc_buf + src_buf_ofs, &src_buf_ਮਾਪ, (mz_uint8*)pBuf, pBuf ? (mz_uint8*)pBuf + *p_ਬਾਹਰਲਾ_len : ਨਿਰਾ, &dst_buf_ਮਾਪ,
      (flags & ~TINFL_FLAG_HAS_ਹੋਰ_ਨਿਵੇਸ਼) | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF);
    ਜੇ ((ਸਥਿਤੀ < 0) || (ਸਥਿਤੀ == TINFL_ਸਥਿਤੀ_NEEDS_ਹੋਰ_ਨਿਵੇਸ਼))
    {
      MZ_FREE(pBuf); *p_ਬਾਹਰਲਾ_len = 0; ਵਾਪਸ ਨਿਰਾ;
    }
    src_buf_ofs += src_buf_ਮਾਪ;
    *p_ਬਾਹਰਲਾ_len += dst_buf_ਮਾਪ;
    ਜੇ (ਸਥਿਤੀ == TINFL_ਸਥਿਤੀ_ਪੂਰਾ) ਰੋਕੋ;
    new_ਬਾਹਰਲਾ_buf_ਸਮਰੱਥਾ = ਬਾਹਰਲਾ_buf_ਸਮਰੱਥਾ * 2; ਜੇ (new_ਬਾਹਰਲਾ_buf_ਸਮਰੱਥਾ < 128) new_ਬਾਹਰਲਾ_buf_ਸਮਰੱਥਾ = 128;
    pNew_buf = MZ_REALLOC(pBuf, new_ਬਾਹਰਲਾ_buf_ਸਮਰੱਥਾ);
    ਜੇ (!pNew_buf)
    {
      MZ_FREE(pBuf); *p_ਬਾਹਰਲਾ_len = 0; ਵਾਪਸ ਨਿਰਾ;
    }
    pBuf = pNew_buf; ਬਾਹਰਲਾ_buf_ਸਮਰੱਥਾ = new_ਬਾਹਰਲਾ_buf_ਸਮਰੱਥਾ;
  }
  ਵਾਪਸ pBuf;
}

size_t tinfl_decompress_mem_ਮੰਜ਼ਿਲ_mem(ਖਾਲੀ *p_ਬਾਹਰਲਾ_buf, size_t ਬਾਹਰਲਾ_buf_len, ਅਚਲ ਖਾਲੀ *pSrc_buf, size_t src_buf_len, ਪੂਰਨ flags)
{
  tinfl_decompressor decomp; tinfl_ਸਥਿਤੀ ਸਥਿਤੀ; tinfl_init(&decomp);
  ਸਥਿਤੀ = tinfl_decompress(&decomp, (ਅਚਲ mz_uint8*)pSrc_buf, &src_buf_len, (mz_uint8*)p_ਬਾਹਰਲਾ_buf, (mz_uint8*)p_ਬਾਹਰਲਾ_buf, &ਬਾਹਰਲਾ_buf_len, (flags & ~TINFL_FLAG_HAS_ਹੋਰ_ਨਿਵੇਸ਼) | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF);
  ਵਾਪਸ (ਸਥਿਤੀ != TINFL_ਸਥਿਤੀ_ਪੂਰਾ) ? TINFL_DECOMPRESS_MEM_ਮੰਜ਼ਿਲ_MEM_FAILED : ਬਾਹਰਲਾ_buf_len;
}

ਪੂਰਨ tinfl_decompress_mem_ਮੰਜ਼ਿਲ_callback(ਅਚਲ ਖਾਲੀ *p_ਵਿੱਚ_buf, size_t *p_ਵਿੱਚ_buf_ਮਾਪ, tinfl_put_buf_func_ptr pPut_buf_func, ਖਾਲੀ *pPut_buf_user, ਪੂਰਨ flags)
{
  ਪੂਰਨ ਨਤੀਜਾ = 0;
  tinfl_decompressor decomp;
  mz_uint8 *pDict = (mz_uint8*)MZ_MALLOC(TINFL_LZ_DICT_ਮਾਪ); size_t ਵਿੱਚ_buf_ofs = 0, dict_ofs = 0;
  ਜੇ (!pDict)
    ਵਾਪਸ TINFL_ਸਥਿਤੀ_FAILED;
  memset(pDict,0,TINFL_LZ_DICT_ਮਾਪ);
  tinfl_init(&decomp);
  ਲਈ ( ; ; )
  {
    size_t ਵਿੱਚ_buf_ਮਾਪ = *p_ਵਿੱਚ_buf_ਮਾਪ - ਵਿੱਚ_buf_ofs, dst_buf_ਮਾਪ = TINFL_LZ_DICT_ਮਾਪ - dict_ofs;
    tinfl_ਸਥਿਤੀ ਸਥਿਤੀ = tinfl_decompress(&decomp, (ਅਚਲ mz_uint8*)p_ਵਿੱਚ_buf + ਵਿੱਚ_buf_ofs, &ਵਿੱਚ_buf_ਮਾਪ, pDict, pDict + dict_ofs, &dst_buf_ਮਾਪ,
      (flags & ~(TINFL_FLAG_HAS_ਹੋਰ_ਨਿਵੇਸ਼ | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF)));
    ਵਿੱਚ_buf_ofs += ਵਿੱਚ_buf_ਮਾਪ;
    ਜੇ ((dst_buf_ਮਾਪ) && (!(*pPut_buf_func)(pDict + dict_ofs, (ਪੂਰਨ)dst_buf_ਮਾਪ, pPut_buf_user)))
      ਰੋਕੋ;
    ਜੇ (ਸਥਿਤੀ != TINFL_ਸਥਿਤੀ_HAS_ਹੋਰ_OUTPUT)
    {
      ਨਤੀਜਾ = (ਸਥਿਤੀ == TINFL_ਸਥਿਤੀ_ਪੂਰਾ);
      ਰੋਕੋ;
    }
    dict_ofs = (dict_ofs + dst_buf_ਮਾਪ) & (TINFL_LZ_DICT_ਮਾਪ - 1);
  }
  MZ_FREE(pDict);
  *p_ਵਿੱਚ_buf_ਮਾਪ = ਵਿੱਚ_buf_ofs;
  ਵਾਪਸ ਨਤੀਜਾ;
}
#ਜੇ_ਅੰਤ /*#ifndef MINIZ_NO_INFLATE_APIS*/

// ------------------- Low-level Compression (independent from all decompression API's)
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_DEFLATE_APIS

// Purposely making these tables static for faster init and thread safety.
ਸਥਿਰ ਅਚਲ mz_uint16 s_tdefl_len_sym[256] = {
  257,258,259,260,261,262,263,264,265,265,266,266,267,267,268,268,269,269,269,269,270,270,270,270,271,271,271,271,272,272,272,272,
  273,273,273,273,273,273,273,273,274,274,274,274,274,274,274,274,275,275,275,275,275,275,275,275,276,276,276,276,276,276,276,276,
  277,277,277,277,277,277,277,277,277,277,277,277,277,277,277,277,278,278,278,278,278,278,278,278,278,278,278,278,278,278,278,278,
  279,279,279,279,279,279,279,279,279,279,279,279,279,279,279,279,280,280,280,280,280,280,280,280,280,280,280,280,280,280,280,280,
  281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,
  282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,
  283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,
  284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,285 };

ਸਥਿਰ ਅਚਲ mz_uint8 s_tdefl_len_extra[256] = {
  0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0 };

ਸਥਿਰ ਅਚਲ mz_uint8 s_tdefl_small_dist_sym[512] = {
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

ਸਥਿਰ ਅਚਲ mz_uint8 s_tdefl_small_dist_extra[512] = {
  0,0,0,0,1,1,1,1,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
  6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
  6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7 };

ਸਥਿਰ ਅਚਲ mz_uint8 s_tdefl_large_dist_sym[128] = {
  0,0,18,19,20,20,21,21,22,22,22,22,23,23,23,23,24,24,24,24,24,24,24,24,25,25,25,25,25,25,25,25,26,26,26,26,26,26,26,26,26,26,26,26,
  26,26,26,26,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,
  28,28,28,28,28,28,28,28,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29 };

ਸਥਿਰ ਅਚਲ mz_uint8 s_tdefl_large_dist_extra[128] = {
  0,0,8,8,9,9,9,9,10,10,10,10,10,10,10,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,
  12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
  13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13 };

// Radix sorts tdefl_sym_freq[] array by 16-bit key m_key. Returns ptr to sorted values.
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ { mz_uint16 m_ਕੁੰਜੀ, m_sym_ਸੂਚਕਾਂਕ; } tdefl_sym_freq;
ਸਥਿਰ tdefl_sym_freq* tdefl_radix_ਛਾਂਟੋ_syms(mz_uint ਅੰਕ_syms, tdefl_sym_freq* pSyms0, tdefl_sym_freq* pSyms1)
{
  mz_uint32 ਕੁੱਲ_passes = 2, pass_ਖਿਸਕਾਓ, pass, i, hist[256 * 2]; tdefl_sym_freq* pCur_syms = pSyms0, *pNew_syms = pSyms1; MZ_CLEAR_ARR(hist);
  ਲਈ (i = 0; i < ਅੰਕ_syms; i++) { mz_uint freq = pSyms0[i].m_ਕੁੰਜੀ; hist[freq & 0xFF]++; hist[256 + ((freq >> 8) & 0xFF)]++; }
  ਜਦੋਂ ((ਕੁੱਲ_passes > 1) && (ਅੰਕ_syms == hist[(ਕੁੱਲ_passes - 1) * 256])) ਕੁੱਲ_passes--;
  ਲਈ (pass_ਖਿਸਕਾਓ = 0, pass = 0; pass < ਕੁੱਲ_passes; pass++, pass_ਖਿਸਕਾਓ += 8)
  {
    ਅਚਲ mz_uint32* pHist = &hist[pass << 8];
    mz_uint offsets[256], cur_ofs = 0;
    ਲਈ (i = 0; i < 256; i++) { offsets[i] = cur_ofs; cur_ofs += pHist[i]; }
    ਲਈ (i = 0; i < ਅੰਕ_syms; i++) pNew_syms[offsets[(pCur_syms[i].m_ਕੁੰਜੀ >> pass_ਖਿਸਕਾਓ) & 0xFF]++] = pCur_syms[i];
    { tdefl_sym_freq* t = pCur_syms; pCur_syms = pNew_syms; pNew_syms = t; }
  }
  ਵਾਪਸ pCur_syms;
}

// tdefl_calculate_minimum_redundancy() originally written by: Alistair Moffat, alistair@cs.mu.oz.au, Jyrki Katajainen, jyrki@diku.dk, November 1996.
ਸਥਿਰ ਖਾਲੀ tdefl_calculate_minimum_redundancy(tdefl_sym_freq *A, ਪੂਰਨ n)
{
  ਪੂਰਨ ਜੜ੍ਹ, ਪੱਤੀ, ਅਗਲਾ, avbl, ਵਰਤਿਆ, dpth;
  ਜੇ (n==0) ਵਾਪਸ; ਨਹੀਂਤਾਂ ਜੇ (n==1) { A[0].m_ਕੁੰਜੀ = 1; ਵਾਪਸ; }
  A[0].m_ਕੁੰਜੀ += A[1].m_ਕੁੰਜੀ; ਜੜ੍ਹ = 0; ਪੱਤੀ = 2;
  ਲਈ (ਅਗਲਾ=1; ਅਗਲਾ < n-1; ਅਗਲਾ++)
  {
    ਜੇ (ਪੱਤੀ>=n || A[ਜੜ੍ਹ].m_ਕੁੰਜੀ<A[ਪੱਤੀ].m_ਕੁੰਜੀ) { A[ਅਗਲਾ].m_ਕੁੰਜੀ = A[ਜੜ੍ਹ].m_ਕੁੰਜੀ; A[ਜੜ੍ਹ++].m_ਕੁੰਜੀ = (mz_uint16)ਅਗਲਾ; } ਨਹੀਂਤਾਂ A[ਅਗਲਾ].m_ਕੁੰਜੀ = A[ਪੱਤੀ++].m_ਕੁੰਜੀ;
    ਜੇ (ਪੱਤੀ>=n || (ਜੜ੍ਹ<ਅਗਲਾ && A[ਜੜ੍ਹ].m_ਕੁੰਜੀ<A[ਪੱਤੀ].m_ਕੁੰਜੀ)) { A[ਅਗਲਾ].m_ਕੁੰਜੀ = (mz_uint16)(A[ਅਗਲਾ].m_ਕੁੰਜੀ + A[ਜੜ੍ਹ].m_ਕੁੰਜੀ); A[ਜੜ੍ਹ++].m_ਕੁੰਜੀ = (mz_uint16)ਅਗਲਾ; } ਨਹੀਂਤਾਂ A[ਅਗਲਾ].m_ਕੁੰਜੀ = (mz_uint16)(A[ਅਗਲਾ].m_ਕੁੰਜੀ + A[ਪੱਤੀ++].m_ਕੁੰਜੀ);
  }
  A[n-2].m_ਕੁੰਜੀ = 0; ਲਈ (ਅਗਲਾ=n-3; ਅਗਲਾ>=0; ਅਗਲਾ--) A[ਅਗਲਾ].m_ਕੁੰਜੀ = A[A[ਅਗਲਾ].m_ਕੁੰਜੀ].m_ਕੁੰਜੀ+1;
  avbl = 1; ਵਰਤਿਆ = dpth = 0; ਜੜ੍ਹ = n-2; ਅਗਲਾ = n-1;
  ਜਦੋਂ (avbl>0)
  {
    ਜਦੋਂ (ਜੜ੍ਹ>=0 && (ਪੂਰਨ)A[ਜੜ੍ਹ].m_ਕੁੰਜੀ==dpth) { ਵਰਤਿਆ++; ਜੜ੍ਹ--; }
    ਜਦੋਂ (avbl>ਵਰਤਿਆ) { A[ਅਗਲਾ--].m_ਕੁੰਜੀ = (mz_uint16)(dpth); avbl--; }
    avbl = 2*ਵਰਤਿਆ; dpth++; ਵਰਤਿਆ = 0;
  }
}

// Limits canonical Huffman code table's max code size.
ਗਿਣਤੀ { TDEFL_MAX_SUPPORTED_HUFF_CODESIZE = 32 };
ਸਥਿਰ ਖਾਲੀ tdefl_huffman_enforce_max_ਕੋਡ_ਮਾਪ(ਪੂਰਨ *p_ਅੰਕ_codes, ਪੂਰਨ ਕੋਡ_list_len, ਪੂਰਨ max_ਕੋਡ_ਮਾਪ)
{
  ਪੂਰਨ i; mz_uint32 ਕੁੱਲ = 0; ਜੇ (ਕੋਡ_list_len <= 1) ਵਾਪਸ;
  ਲਈ (i = max_ਕੋਡ_ਮਾਪ + 1; i <= TDEFL_MAX_SUPPORTED_HUFF_CODESIZE; i++) p_ਅੰਕ_codes[max_ਕੋਡ_ਮਾਪ] += p_ਅੰਕ_codes[i];
  ਲਈ (i = max_ਕੋਡ_ਮਾਪ; i > 0; i--) ਕੁੱਲ += (((mz_uint32)p_ਅੰਕ_codes[i]) << (max_ਕੋਡ_ਮਾਪ - i));
  ਜਦੋਂ (ਕੁੱਲ != (1UL << max_ਕੋਡ_ਮਾਪ))
  {
    p_ਅੰਕ_codes[max_ਕੋਡ_ਮਾਪ]--;
    ਲਈ (i = max_ਕੋਡ_ਮਾਪ - 1; i > 0; i--) ਜੇ (p_ਅੰਕ_codes[i]) { p_ਅੰਕ_codes[i]--; p_ਅੰਕ_codes[i + 1] += 2; ਰੋਕੋ; }
    ਕੁੱਲ--;
  }
}

ਸਥਿਰ ਖਾਲੀ tdefl_optimize_huffman_ਸਾਰਣੀ(tdefl_compressor *d, ਪੂਰਨ ਸਾਰਣੀ_ਅੰਕ, ਪੂਰਨ ਸਾਰਣੀ_len, ਪੂਰਨ ਕੋਡ_ਮਾਪ_ਹੱਦਬੰਦੀ, ਪੂਰਨ static_ਸਾਰਣੀ)
{
  ਪੂਰਨ i, j, l, ਅੰਕ_codes[1 + TDEFL_MAX_SUPPORTED_HUFF_CODESIZE]; mz_uint ਅਗਲਾ_ਕੋਡ[TDEFL_MAX_SUPPORTED_HUFF_CODESIZE + 1]; MZ_CLEAR_ARR(ਅੰਕ_codes);
  ਜੇ (static_ਸਾਰਣੀ)
  {
    ਲਈ (i = 0; i < ਸਾਰਣੀ_len; i++) ਅੰਕ_codes[d->m_huff_ਕੋਡ_sizes[ਸਾਰਣੀ_ਅੰਕ][i]]++;
  }
  ਨਹੀਂਤਾਂ
  {
    tdefl_sym_freq syms0[TDEFL_MAX_HUFF_SYMBOLS], syms1[TDEFL_MAX_HUFF_SYMBOLS], *pSyms;
    ਪੂਰਨ ਅੰਕ_ਵਰਤਿਆ_syms = 0;
    ਅਚਲ mz_uint16 *p_Sym_ਗਿਣਤੀ = &d->m_huff_ਗਿਣਤੀ[ਸਾਰਣੀ_ਅੰਕ][0];
    ਲਈ (i = 0; i < ਸਾਰਣੀ_len; i++) ਜੇ (p_Sym_ਗਿਣਤੀ[i]) { syms0[ਅੰਕ_ਵਰਤਿਆ_syms].m_ਕੁੰਜੀ = (mz_uint16)p_Sym_ਗਿਣਤੀ[i]; syms0[ਅੰਕ_ਵਰਤਿਆ_syms++].m_sym_ਸੂਚਕਾਂਕ = (mz_uint16)i; }

    pSyms = tdefl_radix_ਛਾਂਟੋ_syms(ਅੰਕ_ਵਰਤਿਆ_syms, syms0, syms1); tdefl_calculate_minimum_redundancy(pSyms, ਅੰਕ_ਵਰਤਿਆ_syms);

    ਲਈ (i = 0; i < ਅੰਕ_ਵਰਤਿਆ_syms; i++) ਅੰਕ_codes[pSyms[i].m_ਕੁੰਜੀ]++;

    tdefl_huffman_enforce_max_ਕੋਡ_ਮਾਪ(ਅੰਕ_codes, ਅੰਕ_ਵਰਤਿਆ_syms, ਕੋਡ_ਮਾਪ_ਹੱਦਬੰਦੀ);

    MZ_CLEAR_ARR(d->m_huff_ਕੋਡ_sizes[ਸਾਰਣੀ_ਅੰਕ]); MZ_CLEAR_ARR(d->m_huff_codes[ਸਾਰਣੀ_ਅੰਕ]);
    ਲਈ (i = 1, j = ਅੰਕ_ਵਰਤਿਆ_syms; i <= ਕੋਡ_ਮਾਪ_ਹੱਦਬੰਦੀ; i++)
      ਲਈ (l = ਅੰਕ_codes[i]; l > 0; l--) d->m_huff_ਕੋਡ_sizes[ਸਾਰਣੀ_ਅੰਕ][pSyms[--j].m_sym_ਸੂਚਕਾਂਕ] = (mz_uint8)(i);
  }

  ਅਗਲਾ_ਕੋਡ[1] = 0; ਲਈ (j = 0, i = 2; i <= ਕੋਡ_ਮਾਪ_ਹੱਦਬੰਦੀ; i++) ਅਗਲਾ_ਕੋਡ[i] = j = ((j + ਅੰਕ_codes[i - 1]) << 1);

  ਲਈ (i = 0; i < ਸਾਰਣੀ_len; i++)
  {
    mz_uint rev_ਕੋਡ = 0, ਕੋਡ, ਕੋਡ_ਮਾਪ_2; ਜੇ ((ਕੋਡ_ਮਾਪ_2 = d->m_huff_ਕੋਡ_sizes[ਸਾਰਣੀ_ਅੰਕ][i]) == 0) ਜਾਰੀ;
    ਕੋਡ = ਅਗਲਾ_ਕੋਡ[ਕੋਡ_ਮਾਪ_2]++; ਲਈ (l = ਕੋਡ_ਮਾਪ_2; l > 0; l--, ਕੋਡ >>= 1) rev_ਕੋਡ = (rev_ਕੋਡ << 1) | (ਕੋਡ & 1);
    d->m_huff_codes[ਸਾਰਣੀ_ਅੰਕ][i] = (mz_uint16)rev_ਕੋਡ;
  }
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TDEFL_PUT_ਬਿੱਟ(b, l) ਕਰੋ { \
  mz_uint ਬਿੱਟ = b; mz_uint len = l; MZ_ASSERT(ਬਿੱਟ <= ((1U << len) - 1U)); \
  d->m_ਦੋਆਧਾਰੀ_ਅੰਕ_ਬਫਰ |= (ਬਿੱਟ << d->m_ਬਿੱਟ_ਵਿੱਚ); d->m_ਬਿੱਟ_ਵਿੱਚ += len; \
  ਜਦੋਂ (d->m_ਬਿੱਟ_ਵਿੱਚ >= 8) { \
    ਜੇ (d->m_pOutput_buf < d->m_p_Output_buf_ਸਿਰਾ) \
      *d->m_pOutput_buf++ = (mz_uint8)(d->m_ਦੋਆਧਾਰੀ_ਅੰਕ_ਬਫਰ); \
    d->m_ਦੋਆਧਾਰੀ_ਅੰਕ_ਬਫਰ >>= 8; \
    d->m_ਬਿੱਟ_ਵਿੱਚ -= 8; \
  } \
} MZ_MACRO_ਸਿਰਾ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TDEFL_RLE_PREV_ਕੋਡ_ਮਾਪ() ਕਰੋ { \
  ਜੇ (rle_repeat_ਗਿਣਤੀ) { \
    ਜੇ (rle_repeat_ਗਿਣਤੀ < 3) { \
      d->m_huff_ਗਿਣਤੀ[2][prev_ਕੋਡ_ਮਾਪ] = (mz_uint16)(d->m_huff_ਗਿਣਤੀ[2][prev_ਕੋਡ_ਮਾਪ] + rle_repeat_ਗਿਣਤੀ); \
      ਜਦੋਂ (rle_repeat_ਗਿਣਤੀ--) packed_ਕੋਡ_sizes[ਅੰਕ_packed_ਕੋਡ_sizes++] = prev_ਕੋਡ_ਮਾਪ; \
    } ਨਹੀਂਤਾਂ { \
      d->m_huff_ਗਿਣਤੀ[2][16] = (mz_uint16)(d->m_huff_ਗਿਣਤੀ[2][16] + 1); packed_ਕੋਡ_sizes[ਅੰਕ_packed_ਕੋਡ_sizes++] = 16; packed_ਕੋਡ_sizes[ਅੰਕ_packed_ਕੋਡ_sizes++] = (mz_uint8)(rle_repeat_ਗਿਣਤੀ - 3); \
  } rle_repeat_ਗਿਣਤੀ = 0; } \
} MZ_MACRO_ਸਿਰਾ

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TDEFL_RLE_ZERO_ਕੋਡ_ਮਾਪ() ਕਰੋ { \
  ਜੇ (rle_z_ਗਿਣਤੀ) { \
    ਜੇ (rle_z_ਗਿਣਤੀ < 3) { \
      d->m_huff_ਗਿਣਤੀ[2][0] = (mz_uint16)(d->m_huff_ਗਿਣਤੀ[2][0] + rle_z_ਗਿਣਤੀ); ਜਦੋਂ (rle_z_ਗਿਣਤੀ--) packed_ਕੋਡ_sizes[ਅੰਕ_packed_ਕੋਡ_sizes++] = 0; \
    } ਨਹੀਂਤਾਂ ਜੇ (rle_z_ਗਿਣਤੀ <= 10) { \
      d->m_huff_ਗਿਣਤੀ[2][17] = (mz_uint16)(d->m_huff_ਗਿਣਤੀ[2][17] + 1); packed_ਕੋਡ_sizes[ਅੰਕ_packed_ਕੋਡ_sizes++] = 17; packed_ਕੋਡ_sizes[ਅੰਕ_packed_ਕੋਡ_sizes++] = (mz_uint8)(rle_z_ਗਿਣਤੀ - 3); \
    } ਨਹੀਂਤਾਂ { \
      d->m_huff_ਗਿਣਤੀ[2][18] = (mz_uint16)(d->m_huff_ਗਿਣਤੀ[2][18] + 1); packed_ਕੋਡ_sizes[ਅੰਕ_packed_ਕੋਡ_sizes++] = 18; packed_ਕੋਡ_sizes[ਅੰਕ_packed_ਕੋਡ_sizes++] = (mz_uint8)(rle_z_ਗਿਣਤੀ - 11); \
  } rle_z_ਗਿਣਤੀ = 0; } \
} MZ_MACRO_ਸਿਰਾ

ਸਥਿਰ mz_uint8 s_tdefl_packed_ਕੋਡ_ਮਾਪ_syms_swizzle[] = { 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 };

ਸਥਿਰ ਖਾਲੀ tdefl_ਸ਼ੁਰੂ_dynamic_ਖੰਡ(tdefl_compressor *d)
{
  ਪੂਰਨ ਅੰਕ_lit_codes, ਅੰਕ_dist_codes, ਅੰਕ_ਦੋਆਧਾਰੀ_ਅੰਕ_lengths; mz_uint i, ਕੁੱਲ_ਕੋਡ_sizes_ਮੰਜ਼ਿਲ_pack, ਅੰਕ_packed_ਕੋਡ_sizes, rle_z_ਗਿਣਤੀ, rle_repeat_ਗਿਣਤੀ, packed_ਕੋਡ_sizes_ਸੂਚਕਾਂਕ;
  mz_uint8 ਕੋਡ_sizes_ਮੰਜ਼ਿਲ_pack[TDEFL_MAX_HUFF_SYMBOLS_0 + TDEFL_MAX_HUFF_SYMBOLS_1], packed_ਕੋਡ_sizes[TDEFL_MAX_HUFF_SYMBOLS_0 + TDEFL_MAX_HUFF_SYMBOLS_1], prev_ਕੋਡ_ਮਾਪ = 0xFF;

  d->m_huff_ਗਿਣਤੀ[0][256] = 1;

  tdefl_optimize_huffman_ਸਾਰਣੀ(d, 0, TDEFL_MAX_HUFF_SYMBOLS_0, 15, MZ_FALSE);
  tdefl_optimize_huffman_ਸਾਰਣੀ(d, 1, TDEFL_MAX_HUFF_SYMBOLS_1, 15, MZ_FALSE);

  ਲਈ (ਅੰਕ_lit_codes = 286; ਅੰਕ_lit_codes > 257; ਅੰਕ_lit_codes--) ਜੇ (d->m_huff_ਕੋਡ_sizes[0][ਅੰਕ_lit_codes - 1]) ਰੋਕੋ;
  ਲਈ (ਅੰਕ_dist_codes = 30; ਅੰਕ_dist_codes > 1; ਅੰਕ_dist_codes--) ਜੇ (d->m_huff_ਕੋਡ_sizes[1][ਅੰਕ_dist_codes - 1]) ਰੋਕੋ;

  ਸਮ੍ਰਿਤੀ_ਨਕਲ(ਕੋਡ_sizes_ਮੰਜ਼ਿਲ_pack, &d->m_huff_ਕੋਡ_sizes[0][0], ਅੰਕ_lit_codes);
  ਸਮ੍ਰਿਤੀ_ਨਕਲ(ਕੋਡ_sizes_ਮੰਜ਼ਿਲ_pack + ਅੰਕ_lit_codes, &d->m_huff_ਕੋਡ_sizes[1][0], ਅੰਕ_dist_codes);
  ਕੁੱਲ_ਕੋਡ_sizes_ਮੰਜ਼ਿਲ_pack = ਅੰਕ_lit_codes + ਅੰਕ_dist_codes; ਅੰਕ_packed_ਕੋਡ_sizes = 0; rle_z_ਗਿਣਤੀ = 0; rle_repeat_ਗਿਣਤੀ = 0;

  memset(&d->m_huff_ਗਿਣਤੀ[2][0], 0, ਆਕਾਰ(d->m_huff_ਗਿਣਤੀ[2][0]) * TDEFL_MAX_HUFF_SYMBOLS_2);
  ਲਈ (i = 0; i < ਕੁੱਲ_ਕੋਡ_sizes_ਮੰਜ਼ਿਲ_pack; i++)
  {
    mz_uint8 ਕੋਡ_ਮਾਪ_2 = ਕੋਡ_sizes_ਮੰਜ਼ਿਲ_pack[i];
    ਜੇ (!ਕੋਡ_ਮਾਪ_2)
    {
      TDEFL_RLE_PREV_ਕੋਡ_ਮਾਪ();
      ਜੇ (++rle_z_ਗਿਣਤੀ == 138) { TDEFL_RLE_ZERO_ਕੋਡ_ਮਾਪ(); }
    }
    ਨਹੀਂਤਾਂ
    {
      TDEFL_RLE_ZERO_ਕੋਡ_ਮਾਪ();
      ਜੇ (ਕੋਡ_ਮਾਪ_2 != prev_ਕੋਡ_ਮਾਪ)
      {
        TDEFL_RLE_PREV_ਕੋਡ_ਮਾਪ();
        d->m_huff_ਗਿਣਤੀ[2][ਕੋਡ_ਮਾਪ_2] = (mz_uint16)(d->m_huff_ਗਿਣਤੀ[2][ਕੋਡ_ਮਾਪ_2] + 1); packed_ਕੋਡ_sizes[ਅੰਕ_packed_ਕੋਡ_sizes++] = ਕੋਡ_ਮਾਪ_2;
      }
      ਨਹੀਂਤਾਂ ਜੇ (++rle_repeat_ਗਿਣਤੀ == 6)
      {
        TDEFL_RLE_PREV_ਕੋਡ_ਮਾਪ();
      }
    }
    prev_ਕੋਡ_ਮਾਪ = ਕੋਡ_ਮਾਪ_2;
  }
  ਜੇ (rle_repeat_ਗਿਣਤੀ) { TDEFL_RLE_PREV_ਕੋਡ_ਮਾਪ(); } ਨਹੀਂਤਾਂ { TDEFL_RLE_ZERO_ਕੋਡ_ਮਾਪ(); }

  tdefl_optimize_huffman_ਸਾਰਣੀ(d, 2, TDEFL_MAX_HUFF_SYMBOLS_2, 7, MZ_FALSE);

  TDEFL_PUT_ਬਿੱਟ(2, 2);

  TDEFL_PUT_ਬਿੱਟ(ਅੰਕ_lit_codes - 257, 5);
  TDEFL_PUT_ਬਿੱਟ(ਅੰਕ_dist_codes - 1, 5);

  ਲਈ (ਅੰਕ_ਦੋਆਧਾਰੀ_ਅੰਕ_lengths = 18; ਅੰਕ_ਦੋਆਧਾਰੀ_ਅੰਕ_lengths >= 0; ਅੰਕ_ਦੋਆਧਾਰੀ_ਅੰਕ_lengths--) ਜੇ (d->m_huff_ਕੋਡ_sizes[2][s_tdefl_packed_ਕੋਡ_ਮਾਪ_syms_swizzle[ਅੰਕ_ਦੋਆਧਾਰੀ_ਅੰਕ_lengths]]) ਰੋਕੋ;
  ਅੰਕ_ਦੋਆਧਾਰੀ_ਅੰਕ_lengths = MZ_MAX(4, (ਅੰਕ_ਦੋਆਧਾਰੀ_ਅੰਕ_lengths + 1)); TDEFL_PUT_ਬਿੱਟ(ਅੰਕ_ਦੋਆਧਾਰੀ_ਅੰਕ_lengths - 4, 4);
  ਲਈ (i = 0; (ਪੂਰਨ)i < ਅੰਕ_ਦੋਆਧਾਰੀ_ਅੰਕ_lengths; i++) TDEFL_PUT_ਬਿੱਟ(d->m_huff_ਕੋਡ_sizes[2][s_tdefl_packed_ਕੋਡ_ਮਾਪ_syms_swizzle[i]], 3);

  ਲਈ (packed_ਕੋਡ_sizes_ਸੂਚਕਾਂਕ = 0; packed_ਕੋਡ_sizes_ਸੂਚਕਾਂਕ < ਅੰਕ_packed_ਕੋਡ_sizes; )
  {
    mz_uint ਕੋਡ = packed_ਕੋਡ_sizes[packed_ਕੋਡ_sizes_ਸੂਚਕਾਂਕ++]; MZ_ASSERT(ਕੋਡ < TDEFL_MAX_HUFF_SYMBOLS_2);
    TDEFL_PUT_ਬਿੱਟ(d->m_huff_codes[2][ਕੋਡ], d->m_huff_ਕੋਡ_sizes[2][ਕੋਡ]);
    ਜੇ (ਕੋਡ >= 16) TDEFL_PUT_ਬਿੱਟ(packed_ਕੋਡ_sizes[packed_ਕੋਡ_sizes_ਸੂਚਕਾਂਕ++], "\02\03\07"[ਕੋਡ - 16]);
  }
}

ਸਥਿਰ ਖਾਲੀ tdefl_ਸ਼ੁਰੂ_static_ਖੰਡ(tdefl_compressor *d)
{
  mz_uint i;
  mz_uint8 *p = &d->m_huff_ਕੋਡ_sizes[0][0];

  ਲਈ (i = 0; i <= 143; ++i) *p++ = 8;
  ਲਈ ( ; i <= 255; ++i) *p++ = 9;
  ਲਈ ( ; i <= 279; ++i) *p++ = 7;
  ਲਈ ( ; i <= 287; ++i) *p++ = 8;

  memset(d->m_huff_ਕੋਡ_sizes[1], 5, 32);

  tdefl_optimize_huffman_ਸਾਰਣੀ(d, 0, 288, 15, MZ_TRUE);
  tdefl_optimize_huffman_ਸਾਰਣੀ(d, 1, 32, 15, MZ_TRUE);

  TDEFL_PUT_ਬਿੱਟ(1, 2);
}

ਸਥਿਰ ਅਚਲ mz_uint mz_bitmasks[17] = { 0x0000, 0x0001, 0x0003, 0x0007, 0x000F, 0x001F, 0x003F, 0x007F, 0x00FF, 0x01FF, 0x03FF, 0x07FF, 0x0FFF, 0x1FFF, 0x3FFF, 0x7FFF, 0xFFFF };

#ਜੇ MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN && MINIZ_HAS_64_ਦੋਆਧਾਰੀ_ਅੰਕ_REGISTERS
ਸਥਿਰ mz_bool tdefl_compress_lz_codes(tdefl_compressor *d)
{
  mz_uint flags;
  mz_uint8 *pLZ_codes;
  mz_uint8 *pOutput_buf = d->m_pOutput_buf;
  mz_uint8 *p_LZ_ਕੋਡ_buf_ਸਿਰਾ = d->m_p_LZ_ਕੋਡ_buf;
  mz_uint64 ਦੋਆਧਾਰੀ_ਅੰਕ_ਬਫਰ = d->m_ਦੋਆਧਾਰੀ_ਅੰਕ_ਬਫਰ;
  mz_uint ਬਿੱਟ_ਵਿੱਚ = d->m_ਬਿੱਟ_ਵਿੱਚ;

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TDEFL_PUT_ਬਿੱਟ_FAST(b, l) { ਦੋਆਧਾਰੀ_ਅੰਕ_ਬਫਰ |= (((mz_uint64)(b)) << ਬਿੱਟ_ਵਿੱਚ); ਬਿੱਟ_ਵਿੱਚ += (l); }

  flags = 1;
  ਲਈ (pLZ_codes = d->m_lz_ਕੋਡ_buf; pLZ_codes < p_LZ_ਕੋਡ_buf_ਸਿਰਾ; flags >>= 1)
  {
    ਜੇ (flags == 1)
      flags = *pLZ_codes++ | 0x100;

    ਜੇ (flags & 1)
    {
      mz_uint s0, s1, n0, n1, sym, ਅੰਕ_extra_ਬਿੱਟ;
      mz_uint ਮੇਲ_len = pLZ_codes[0], ਮੇਲ_dist = *(ਅਚਲ mz_uint16 *)(pLZ_codes + 1); pLZ_codes += 3;

      MZ_ASSERT(d->m_huff_ਕੋਡ_sizes[0][s_tdefl_len_sym[ਮੇਲ_len]]);
      TDEFL_PUT_ਬਿੱਟ_FAST(d->m_huff_codes[0][s_tdefl_len_sym[ਮੇਲ_len]], d->m_huff_ਕੋਡ_sizes[0][s_tdefl_len_sym[ਮੇਲ_len]]);
      TDEFL_PUT_ਬਿੱਟ_FAST(ਮੇਲ_len & mz_bitmasks[s_tdefl_len_extra[ਮੇਲ_len]], s_tdefl_len_extra[ਮੇਲ_len]);

      // This sequence coaxes MSVC into using cmov's vs. jmp's.
      s0 = s_tdefl_small_dist_sym[ਮੇਲ_dist & 511];
      n0 = s_tdefl_small_dist_extra[ਮੇਲ_dist & 511];
      s1 = s_tdefl_large_dist_sym[ਮੇਲ_dist >> 8];
      n1 = s_tdefl_large_dist_extra[ਮੇਲ_dist >> 8];
      sym = (ਮੇਲ_dist < 512) ? s0 : s1;
      ਅੰਕ_extra_ਬਿੱਟ = (ਮੇਲ_dist < 512) ? n0 : n1;

      MZ_ASSERT(d->m_huff_ਕੋਡ_sizes[1][sym]);
      TDEFL_PUT_ਬਿੱਟ_FAST(d->m_huff_codes[1][sym], d->m_huff_ਕੋਡ_sizes[1][sym]);
      TDEFL_PUT_ਬਿੱਟ_FAST(ਮੇਲ_dist & mz_bitmasks[ਅੰਕ_extra_ਬਿੱਟ], ਅੰਕ_extra_ਬਿੱਟ);
    }
    ਨਹੀਂਤਾਂ
    {
      mz_uint lit = *pLZ_codes++;
      MZ_ASSERT(d->m_huff_ਕੋਡ_sizes[0][lit]);
      TDEFL_PUT_ਬਿੱਟ_FAST(d->m_huff_codes[0][lit], d->m_huff_ਕੋਡ_sizes[0][lit]);

      ਜੇ (((flags & 2) == 0) && (pLZ_codes < p_LZ_ਕੋਡ_buf_ਸਿਰਾ))
      {
        flags >>= 1;
        lit = *pLZ_codes++;
        MZ_ASSERT(d->m_huff_ਕੋਡ_sizes[0][lit]);
        TDEFL_PUT_ਬਿੱਟ_FAST(d->m_huff_codes[0][lit], d->m_huff_ਕੋਡ_sizes[0][lit]);

        ਜੇ (((flags & 2) == 0) && (pLZ_codes < p_LZ_ਕੋਡ_buf_ਸਿਰਾ))
        {
          flags >>= 1;
          lit = *pLZ_codes++;
          MZ_ASSERT(d->m_huff_ਕੋਡ_sizes[0][lit]);
          TDEFL_PUT_ਬਿੱਟ_FAST(d->m_huff_codes[0][lit], d->m_huff_ਕੋਡ_sizes[0][lit]);
        }
      }
    }

    ਜੇ (pOutput_buf >= d->m_p_Output_buf_ਸਿਰਾ)
      ਵਾਪਸ MZ_FALSE;

    *(mz_uint64*)pOutput_buf = ਦੋਆਧਾਰੀ_ਅੰਕ_ਬਫਰ;
    pOutput_buf += (ਬਿੱਟ_ਵਿੱਚ >> 3);
    ਦੋਆਧਾਰੀ_ਅੰਕ_ਬਫਰ >>= (ਬਿੱਟ_ਵਿੱਚ & ~7);
    ਬਿੱਟ_ਵਿੱਚ &= 7;
  }

#ਪਰਿਭਾਸ਼ਾ_ਰੱਦ TDEFL_PUT_ਬਿੱਟ_FAST

  d->m_pOutput_buf = pOutput_buf;
  d->m_ਬਿੱਟ_ਵਿੱਚ = 0;
  d->m_ਦੋਆਧਾਰੀ_ਅੰਕ_ਬਫਰ = 0;

  ਜਦੋਂ (ਬਿੱਟ_ਵਿੱਚ)
  {
    mz_uint32 n = MZ_MIN(ਬਿੱਟ_ਵਿੱਚ, 16);
    TDEFL_PUT_ਬਿੱਟ((mz_uint)ਦੋਆਧਾਰੀ_ਅੰਕ_ਬਫਰ & mz_bitmasks[n], n);
    ਦੋਆਧਾਰੀ_ਅੰਕ_ਬਫਰ >>= n;
    ਬਿੱਟ_ਵਿੱਚ -= n;
  }

  TDEFL_PUT_ਬਿੱਟ(d->m_huff_codes[0][256], d->m_huff_ਕੋਡ_sizes[0][256]);

  ਵਾਪਸ (d->m_pOutput_buf < d->m_p_Output_buf_ਸਿਰਾ);
}
#ਨਹੀਂਤਾਂ
ਸਥਿਰ mz_bool tdefl_compress_lz_codes(tdefl_compressor *d)
{
  mz_uint flags;
  mz_uint8 *pLZ_codes;

  flags = 1;
  ਲਈ (pLZ_codes = d->m_lz_ਕੋਡ_buf; pLZ_codes < d->m_p_LZ_ਕੋਡ_buf; flags >>= 1)
  {
    ਜੇ (flags == 1)
      flags = *pLZ_codes++ | 0x100;
    ਜੇ (flags & 1)
    {
      mz_uint sym, ਅੰਕ_extra_ਬਿੱਟ;
      mz_uint ਮੇਲ_len = pLZ_codes[0], ਮੇਲ_dist = (pLZ_codes[1] | (pLZ_codes[2] << 8)); pLZ_codes += 3;

      MZ_ASSERT(d->m_huff_ਕੋਡ_sizes[0][s_tdefl_len_sym[ਮੇਲ_len]]);
      TDEFL_PUT_ਬਿੱਟ(d->m_huff_codes[0][s_tdefl_len_sym[ਮੇਲ_len]], d->m_huff_ਕੋਡ_sizes[0][s_tdefl_len_sym[ਮੇਲ_len]]);
      TDEFL_PUT_ਬਿੱਟ(ਮੇਲ_len & mz_bitmasks[s_tdefl_len_extra[ਮੇਲ_len]], s_tdefl_len_extra[ਮੇਲ_len]);

      ਜੇ (ਮੇਲ_dist < 512)
      {
        sym = s_tdefl_small_dist_sym[ਮੇਲ_dist]; ਅੰਕ_extra_ਬਿੱਟ = s_tdefl_small_dist_extra[ਮੇਲ_dist];
      }
      ਨਹੀਂਤਾਂ
      {
        sym = s_tdefl_large_dist_sym[ਮੇਲ_dist >> 8]; ਅੰਕ_extra_ਬਿੱਟ = s_tdefl_large_dist_extra[ਮੇਲ_dist >> 8];
      }
      MZ_ASSERT(d->m_huff_ਕੋਡ_sizes[1][sym]);
      TDEFL_PUT_ਬਿੱਟ(d->m_huff_codes[1][sym], d->m_huff_ਕੋਡ_sizes[1][sym]);
      TDEFL_PUT_ਬਿੱਟ(ਮੇਲ_dist & mz_bitmasks[ਅੰਕ_extra_ਬਿੱਟ], ਅੰਕ_extra_ਬਿੱਟ);
    }
    ਨਹੀਂਤਾਂ
    {
      mz_uint lit = *pLZ_codes++;
      MZ_ASSERT(d->m_huff_ਕੋਡ_sizes[0][lit]);
      TDEFL_PUT_ਬਿੱਟ(d->m_huff_codes[0][lit], d->m_huff_ਕੋਡ_sizes[0][lit]);
    }
  }

  TDEFL_PUT_ਬਿੱਟ(d->m_huff_codes[0][256], d->m_huff_ਕੋਡ_sizes[0][256]);

  ਵਾਪਸ (d->m_pOutput_buf < d->m_p_Output_buf_ਸਿਰਾ);
}
#ਜੇ_ਅੰਤ // MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN && MINIZ_HAS_64BIT_REGISTERS

ਸਥਿਰ mz_bool tdefl_compress_ਖੰਡ(tdefl_compressor *d, mz_bool static_ਖੰਡ)
{
  ਜੇ (static_ਖੰਡ)
    tdefl_ਸ਼ੁਰੂ_static_ਖੰਡ(d);
  ਨਹੀਂਤਾਂ
    tdefl_ਸ਼ੁਰੂ_dynamic_ਖੰਡ(d);
  ਵਾਪਸ tdefl_compress_lz_codes(d);
}

ਸਥਿਰ ਪੂਰਨ tdefl_flush_ਖੰਡ(tdefl_compressor *d, ਪੂਰਨ flush)
{
  mz_uint saved_ਦੋਆਧਾਰੀ_ਅੰਕ_buf, saved_ਬਿੱਟ_ਵਿੱਚ;
  mz_uint8 *pSaved_output_buf;
  mz_bool comp_ਖੰਡ_succeeded = MZ_FALSE;
  ਪੂਰਨ n, use_raw_ਖੰਡ = ((d->m_flags & TDEFL_FORCE_ALL_RAW_ਖੰਡਾਂ) != 0) && (d->m_lookahead_pos - d->m_lz_ਕੋਡ_buf_dict_pos) <= d->m_dict_ਮਾਪ;
  mz_uint8 *p_Output_buf_ਸ਼ੁਰੂ = ((d->m_pPut_buf_func == ਨਿਰਾ) && ((*d->m_p_ਬਾਹਰਲਾ_buf_ਮਾਪ - d->m_ਬਾਹਰਲਾ_buf_ofs) >= TDEFL_ਬਾਹਰਲਾ_BUF_ਮਾਪ)) ? ((mz_uint8 *)d->m_p_ਬਾਹਰਲਾ_buf + d->m_ਬਾਹਰਲਾ_buf_ofs) : d->m_output_buf;

  d->m_pOutput_buf = p_Output_buf_ਸ਼ੁਰੂ;
  d->m_p_Output_buf_ਸਿਰਾ = d->m_pOutput_buf + TDEFL_ਬਾਹਰਲਾ_BUF_ਮਾਪ - 16;

  MZ_ASSERT(!d->m_output_flush_ਬਚਿਆ);
  d->m_output_flush_ofs = 0;
  d->m_output_flush_ਬਚਿਆ = 0;

  *d->m_pLZ_flags = (mz_uint8)(*d->m_pLZ_flags >> d->m_ਅੰਕ_flags_ਖੱਬਾ);
  d->m_p_LZ_ਕੋਡ_buf -= (d->m_ਅੰਕ_flags_ਖੱਬਾ == 8);

  ਜੇ ((d->m_flags & TDEFL_WRITE_ZLIB_ਸਿਰਲੇਖ) && (!d->m_ਖੰਡ_ਸੂਚਕਾਂਕ))
  {
    TDEFL_PUT_ਬਿੱਟ(0x78, 8); TDEFL_PUT_ਬਿੱਟ(0x01, 8);
  }

  TDEFL_PUT_ਬਿੱਟ(flush == TDEFL_ਅੰਤ, 1);

  pSaved_output_buf = d->m_pOutput_buf; saved_ਦੋਆਧਾਰੀ_ਅੰਕ_buf = d->m_ਦੋਆਧਾਰੀ_ਅੰਕ_ਬਫਰ; saved_ਬਿੱਟ_ਵਿੱਚ = d->m_ਬਿੱਟ_ਵਿੱਚ;

  ਜੇ (!use_raw_ਖੰਡ)
    comp_ਖੰਡ_succeeded = tdefl_compress_ਖੰਡ(d, (d->m_flags & TDEFL_FORCE_ALL_STATIC_ਖੰਡਾਂ) || (d->m_ਕੁੱਲ_lz_ਬਾਈਟਾਂ < 48));

  // If the block gets expanded, forget the current contents of the output buffer and send a raw block instead.
  ਜੇ ( ((use_raw_ਖੰਡ) || ((d->m_ਕੁੱਲ_lz_ਬਾਈਟਾਂ) && ((d->m_pOutput_buf - pSaved_output_buf + 1U) >= d->m_ਕੁੱਲ_lz_ਬਾਈਟਾਂ))) &&
       ((d->m_lookahead_pos - d->m_lz_ਕੋਡ_buf_dict_pos) <= d->m_dict_ਮਾਪ) )
  {
    mz_uint i; d->m_pOutput_buf = pSaved_output_buf; d->m_ਦੋਆਧਾਰੀ_ਅੰਕ_ਬਫਰ = saved_ਦੋਆਧਾਰੀ_ਅੰਕ_buf; d->m_ਬਿੱਟ_ਵਿੱਚ = saved_ਬਿੱਟ_ਵਿੱਚ;
    TDEFL_PUT_ਬਿੱਟ(0, 2);
    ਜੇ (d->m_ਬਿੱਟ_ਵਿੱਚ) { TDEFL_PUT_ਬਿੱਟ(0, 8 - d->m_ਬਿੱਟ_ਵਿੱਚ); }
    ਲਈ (i = 2; i; --i, d->m_ਕੁੱਲ_lz_ਬਾਈਟਾਂ ^= 0xFFFF)
    {
      TDEFL_PUT_ਬਿੱਟ(d->m_ਕੁੱਲ_lz_ਬਾਈਟਾਂ & 0xFFFF, 16);
    }
    ਲਈ (i = 0; i < d->m_ਕੁੱਲ_lz_ਬਾਈਟਾਂ; ++i)
    {
      TDEFL_PUT_ਬਿੱਟ(d->m_dict[(d->m_lz_ਕੋਡ_buf_dict_pos + i) & TDEFL_LZ_DICT_ਮਾਪ_ਨਕਾਬ], 8);
    }
  }
  // Check for the extremely unlikely (if not impossible) case of the compressed block not fitting into the output buffer when using dynamic codes.
  ਨਹੀਂਤਾਂ ਜੇ (!comp_ਖੰਡ_succeeded)
  {
    d->m_pOutput_buf = pSaved_output_buf; d->m_ਦੋਆਧਾਰੀ_ਅੰਕ_ਬਫਰ = saved_ਦੋਆਧਾਰੀ_ਅੰਕ_buf; d->m_ਬਿੱਟ_ਵਿੱਚ = saved_ਬਿੱਟ_ਵਿੱਚ;
    tdefl_compress_ਖੰਡ(d, MZ_TRUE);
  }

  ਜੇ (flush)
  {
    ਜੇ (flush == TDEFL_ਅੰਤ)
    {
      ਜੇ (d->m_ਬਿੱਟ_ਵਿੱਚ) { TDEFL_PUT_ਬਿੱਟ(0, 8 - d->m_ਬਿੱਟ_ਵਿੱਚ); }
      ਜੇ (d->m_flags & TDEFL_WRITE_ZLIB_ਸਿਰਲੇਖ) { mz_uint i, a = d->m_adler32; ਲਈ (i = 0; i < 4; i++) { TDEFL_PUT_ਬਿੱਟ((a >> 24) & 0xFF, 8); a <<= 8; } }
    }
    ਨਹੀਂਤਾਂ
    {
      mz_uint i, z = 0; TDEFL_PUT_ਬਿੱਟ(0, 3); ਜੇ (d->m_ਬਿੱਟ_ਵਿੱਚ) { TDEFL_PUT_ਬਿੱਟ(0, 8 - d->m_ਬਿੱਟ_ਵਿੱਚ); } ਲਈ (i = 2; i; --i, z ^= 0xFFFF) { TDEFL_PUT_ਬਿੱਟ(z & 0xFFFF, 16); }
    }
  }

  MZ_ASSERT(d->m_pOutput_buf < d->m_p_Output_buf_ਸਿਰਾ);

  memset(&d->m_huff_ਗਿਣਤੀ[0][0], 0, ਆਕਾਰ(d->m_huff_ਗਿਣਤੀ[0][0]) * TDEFL_MAX_HUFF_SYMBOLS_0);
  memset(&d->m_huff_ਗਿਣਤੀ[1][0], 0, ਆਕਾਰ(d->m_huff_ਗਿਣਤੀ[1][0]) * TDEFL_MAX_HUFF_SYMBOLS_1);

  d->m_p_LZ_ਕੋਡ_buf = d->m_lz_ਕੋਡ_buf + 1; d->m_pLZ_flags = d->m_lz_ਕੋਡ_buf; d->m_ਅੰਕ_flags_ਖੱਬਾ = 8; d->m_lz_ਕੋਡ_buf_dict_pos += d->m_ਕੁੱਲ_lz_ਬਾਈਟਾਂ; d->m_ਕੁੱਲ_lz_ਬਾਈਟਾਂ = 0; d->m_ਖੰਡ_ਸੂਚਕਾਂਕ++;

  ਜੇ ((n = (ਪੂਰਨ)(d->m_pOutput_buf - p_Output_buf_ਸ਼ੁਰੂ)) != 0)
  {
    ਜੇ (d->m_pPut_buf_func)
    {
      *d->m_p_ਵਿੱਚ_buf_ਮਾਪ = d->m_pSrc - (ਅਚਲ mz_uint8 *)d->m_p_ਵਿੱਚ_buf;
      ਜੇ (!(*d->m_pPut_buf_func)(d->m_output_buf, n, d->m_pPut_buf_user))
        ਵਾਪਸ (d->m_prev_return_ਸਥਿਤੀ = TDEFL_ਸਥਿਤੀ_PUT_BUF_FAILED);
    }
    ਨਹੀਂਤਾਂ ਜੇ (p_Output_buf_ਸ਼ੁਰੂ == d->m_output_buf)
    {
      ਪੂਰਨ ਬਾਈਟਾਂ_ਮੰਜ਼ਿਲ_copy = (ਪੂਰਨ)MZ_MIN((size_t)n, (size_t)(*d->m_p_ਬਾਹਰਲਾ_buf_ਮਾਪ - d->m_ਬਾਹਰਲਾ_buf_ofs));
      ਸਮ੍ਰਿਤੀ_ਨਕਲ((mz_uint8 *)d->m_p_ਬਾਹਰਲਾ_buf + d->m_ਬਾਹਰਲਾ_buf_ofs, d->m_output_buf, ਬਾਈਟਾਂ_ਮੰਜ਼ਿਲ_copy);
      d->m_ਬਾਹਰਲਾ_buf_ofs += ਬਾਈਟਾਂ_ਮੰਜ਼ਿਲ_copy;
      ਜੇ ((n -= ਬਾਈਟਾਂ_ਮੰਜ਼ਿਲ_copy) != 0)
      {
        d->m_output_flush_ofs = ਬਾਈਟਾਂ_ਮੰਜ਼ਿਲ_copy;
        d->m_output_flush_ਬਚਿਆ = n;
      }
    }
    ਨਹੀਂਤਾਂ
    {
      d->m_ਬਾਹਰਲਾ_buf_ofs += n;
    }
  }

  ਵਾਪਸ d->m_output_flush_ਬਚਿਆ;
}

#ਜੇ MINIZ_USE_UNALIGNED_LOADS_AND_STORES
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TDEFL_READ_UNALIGNED_ਸ਼ਬਦ(p) *(ਅਚਲ mz_uint16*)(p)
ਸਥਿਰ MZ_FORCEINLINE ਖਾਲੀ tdefl_ਲੱਭੋ_ਮੇਲ(tdefl_compressor *d, mz_uint lookahead_pos, mz_uint max_dist, mz_uint max_ਮੇਲ_len, mz_uint *p_ਮੇਲ_dist, mz_uint *p_ਮੇਲ_len)
{
  mz_uint dist, pos = lookahead_pos & TDEFL_LZ_DICT_ਮਾਪ_ਨਕਾਬ, ਮੇਲ_len = *p_ਮੇਲ_len, probe_pos = pos, ਅਗਲਾ_probe_pos, probe_len;
  mz_uint ਅੰਕ_probes_ਖੱਬਾ = d->m_max_probes[ਮੇਲ_len >= 32];
  ਅਚਲ mz_uint16 *s = (ਅਚਲ mz_uint16*)(d->m_dict + pos), *p, *q;
  mz_uint16 c01 = TDEFL_READ_UNALIGNED_ਸ਼ਬਦ(&d->m_dict[pos + ਮੇਲ_len - 1]), s01 = TDEFL_READ_UNALIGNED_ਸ਼ਬਦ(s);
  MZ_ASSERT(max_ਮੇਲ_len <= TDEFL_MAX_ਮੇਲ_LEN); ਜੇ (max_ਮੇਲ_len <= ਮੇਲ_len) ਵਾਪਸ;
  ਲਈ ( ; ; )
  {
    ਲਈ ( ; ; )
    {
      ਜੇ (--ਅੰਕ_probes_ਖੱਬਾ == 0) ਵਾਪਸ;
      #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TDEFL_PROBE \
        ਅਗਲਾ_probe_pos = d->m_ਅਗਲਾ[probe_pos]; \
        ਜੇ ((!ਅਗਲਾ_probe_pos) || ((dist = (mz_uint16)(lookahead_pos - ਅਗਲਾ_probe_pos)) > max_dist)) ਵਾਪਸ; \
        probe_pos = ਅਗਲਾ_probe_pos & TDEFL_LZ_DICT_ਮਾਪ_ਨਕਾਬ; \
        ਜੇ (TDEFL_READ_UNALIGNED_ਸ਼ਬਦ(&d->m_dict[probe_pos + ਮੇਲ_len - 1]) == c01) ਰੋਕੋ;
      TDEFL_PROBE
      TDEFL_PROBE
      TDEFL_PROBE
    }
    ਜੇ (!dist) ਰੋਕੋ;
    q = (ਅਚਲ mz_uint16*)(d->m_dict + probe_pos);
    ਜੇ (TDEFL_READ_UNALIGNED_ਸ਼ਬਦ(q) != s01) ਜਾਰੀ;
    p = s; probe_len = 32;
    ਕਰੋ { } ਜਦੋਂ ( (TDEFL_READ_UNALIGNED_ਸ਼ਬਦ(++p) == TDEFL_READ_UNALIGNED_ਸ਼ਬਦ(++q)) && (TDEFL_READ_UNALIGNED_ਸ਼ਬਦ(++p) == TDEFL_READ_UNALIGNED_ਸ਼ਬਦ(++q)) &&
                   (TDEFL_READ_UNALIGNED_ਸ਼ਬਦ(++p) == TDEFL_READ_UNALIGNED_ਸ਼ਬਦ(++q)) && (TDEFL_READ_UNALIGNED_ਸ਼ਬਦ(++p) == TDEFL_READ_UNALIGNED_ਸ਼ਬਦ(++q)) && (--probe_len > 0) );
    ਜੇ (!probe_len)
    {
      *p_ਮੇਲ_dist = dist; *p_ਮੇਲ_len = MZ_MIN(max_ਮੇਲ_len, TDEFL_MAX_ਮੇਲ_LEN); ਰੋਕੋ;
    }
    ਨਹੀਂਤਾਂ ਜੇ ((probe_len = ((mz_uint)(p - s) * 2) + (mz_uint)(*(ਅਚਲ mz_uint8*)p == *(ਅਚਲ mz_uint8*)q)) > ਮੇਲ_len)
    {
      *p_ਮੇਲ_dist = dist; ਜੇ ((*p_ਮੇਲ_len = ਮੇਲ_len = MZ_MIN(max_ਮੇਲ_len, probe_len)) == max_ਮੇਲ_len) ਰੋਕੋ;
      c01 = TDEFL_READ_UNALIGNED_ਸ਼ਬਦ(&d->m_dict[pos + ਮੇਲ_len - 1]);
    }
  }
}
#ਨਹੀਂਤਾਂ
ਸਥਿਰ MZ_FORCEINLINE ਖਾਲੀ tdefl_ਲੱਭੋ_ਮੇਲ(tdefl_compressor *d, mz_uint lookahead_pos, mz_uint max_dist, mz_uint max_ਮੇਲ_len, mz_uint *p_ਮੇਲ_dist, mz_uint *p_ਮੇਲ_len)
{
  mz_uint dist, pos = lookahead_pos & TDEFL_LZ_DICT_ਮਾਪ_ਨਕਾਬ, ਮੇਲ_len = *p_ਮੇਲ_len, probe_pos = pos, ਅਗਲਾ_probe_pos, probe_len;
  mz_uint ਅੰਕ_probes_ਖੱਬਾ = d->m_max_probes[ਮੇਲ_len >= 32];
  ਅਚਲ mz_uint8 *s = d->m_dict + pos, *p, *q;
  mz_uint8 c0 = d->m_dict[pos + ਮੇਲ_len], c1 = d->m_dict[pos + ਮੇਲ_len - 1];
  MZ_ASSERT(max_ਮੇਲ_len <= TDEFL_MAX_ਮੇਲ_LEN); ਜੇ (max_ਮੇਲ_len <= ਮੇਲ_len) ਵਾਪਸ;
  ਲਈ ( ; ; )
  {
    ਲਈ ( ; ; )
    {
      ਜੇ (--ਅੰਕ_probes_ਖੱਬਾ == 0) ਵਾਪਸ;
      #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ TDEFL_PROBE \
        ਅਗਲਾ_probe_pos = d->m_ਅਗਲਾ[probe_pos]; \
        ਜੇ ((!ਅਗਲਾ_probe_pos) || ((dist = (mz_uint16)(lookahead_pos - ਅਗਲਾ_probe_pos)) > max_dist)) ਵਾਪਸ; \
        probe_pos = ਅਗਲਾ_probe_pos & TDEFL_LZ_DICT_ਮਾਪ_ਨਕਾਬ; \
        ਜੇ ((d->m_dict[probe_pos + ਮੇਲ_len] == c0) && (d->m_dict[probe_pos + ਮੇਲ_len - 1] == c1)) ਰੋਕੋ;
      TDEFL_PROBE
      TDEFL_PROBE
      TDEFL_PROBE
    }
    ਜੇ (!dist) ਰੋਕੋ;
    p = s; q = d->m_dict + probe_pos;
    ਲਈ (probe_len = 0; probe_len < max_ਮੇਲ_len; probe_len++) {
        ਜੇ (*p++ != *q++) ਰੋਕੋ;
    }
    ਜੇ (probe_len > ਮੇਲ_len)
    {
      *p_ਮੇਲ_dist = dist;
      ਜੇ ((*p_ਮੇਲ_len = ਮੇਲ_len = probe_len) == max_ਮੇਲ_len) ਵਾਪਸ;
      c0 = d->m_dict[pos + ਮੇਲ_len]; c1 = d->m_dict[pos + ਮੇਲ_len - 1];
    }
  }
}
#ਜੇ_ਅੰਤ // #if MINIZ_USE_UNALIGNED_LOADS_AND_STORES

#ਜੇ MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
ਸਥਿਰ mz_bool tdefl_compress_fast(tdefl_compressor *d)
{
  // Faster, minimally featured LZRW1-style match+parse loop with better register utilization. Intended for applications where raw throughput is valued more highly than ratio.
  mz_uint lookahead_pos = d->m_lookahead_pos, lookahead_ਮਾਪ = d->m_lookahead_ਮਾਪ, dict_ਮਾਪ = d->m_dict_ਮਾਪ, ਕੁੱਲ_lz_ਬਾਈਟਾਂ = d->m_ਕੁੱਲ_lz_ਬਾਈਟਾਂ, ਅੰਕ_flags_ਖੱਬਾ = d->m_ਅੰਕ_flags_ਖੱਬਾ;
  mz_uint8 *p_LZ_ਕੋਡ_buf = d->m_p_LZ_ਕੋਡ_buf, *pLZ_flags = d->m_pLZ_flags;
  mz_uint cur_pos = lookahead_pos & TDEFL_LZ_DICT_ਮਾਪ_ਨਕਾਬ;

  ਜਦੋਂ ((d->m_src_buf_ਖੱਬਾ) || ((d->m_flush) && (lookahead_ਮਾਪ)))
  {
    ਅਚਲ mz_uint TDEFL_COMP_FAST_LOOKAHEAD_ਮਾਪ = 4096;
    mz_uint dst_pos = (lookahead_pos + lookahead_ਮਾਪ) & TDEFL_LZ_DICT_ਮਾਪ_ਨਕਾਬ;
    mz_uint ਅੰਕ_ਬਾਈਟਾਂ_ਮੰਜ਼ਿਲ_process = (mz_uint)MZ_MIN(d->m_src_buf_ਖੱਬਾ, TDEFL_COMP_FAST_LOOKAHEAD_ਮਾਪ - lookahead_ਮਾਪ);
    d->m_src_buf_ਖੱਬਾ -= ਅੰਕ_ਬਾਈਟਾਂ_ਮੰਜ਼ਿਲ_process;
    lookahead_ਮਾਪ += ਅੰਕ_ਬਾਈਟਾਂ_ਮੰਜ਼ਿਲ_process;

    ਜਦੋਂ (ਅੰਕ_ਬਾਈਟਾਂ_ਮੰਜ਼ਿਲ_process)
    {
      mz_uint32 n = MZ_MIN(TDEFL_LZ_DICT_ਮਾਪ - dst_pos, ਅੰਕ_ਬਾਈਟਾਂ_ਮੰਜ਼ਿਲ_process);
      ਸਮ੍ਰਿਤੀ_ਨਕਲ(d->m_dict + dst_pos, d->m_pSrc, n);
      ਜੇ (dst_pos < (TDEFL_MAX_ਮੇਲ_LEN - 1))
        ਸਮ੍ਰਿਤੀ_ਨਕਲ(d->m_dict + TDEFL_LZ_DICT_ਮਾਪ + dst_pos, d->m_pSrc, MZ_MIN(n, (TDEFL_MAX_ਮੇਲ_LEN - 1) - dst_pos));
      d->m_pSrc += n;
      dst_pos = (dst_pos + n) & TDEFL_LZ_DICT_ਮਾਪ_ਨਕਾਬ;
      ਅੰਕ_ਬਾਈਟਾਂ_ਮੰਜ਼ਿਲ_process -= n;
    }

    dict_ਮਾਪ = MZ_MIN(TDEFL_LZ_DICT_ਮਾਪ - lookahead_ਮਾਪ, dict_ਮਾਪ);
    ਜੇ ((!d->m_flush) && (lookahead_ਮਾਪ < TDEFL_COMP_FAST_LOOKAHEAD_ਮਾਪ)) ਰੋਕੋ;

    ਜਦੋਂ (lookahead_ਮਾਪ >= 4)
    {
      mz_uint cur_ਮੇਲ_dist, cur_ਮੇਲ_len = 1;
      mz_uint8 *pCur_dict = d->m_dict + cur_pos;
      mz_uint ਪਹਿਲਾ_trigram = (*(ਅਚਲ mz_uint32 *)pCur_dict) & 0xFFFFFF;
      mz_uint hash = (ਪਹਿਲਾ_trigram ^ (ਪਹਿਲਾ_trigram >> (24 - (TDEFL_LZ_HASH_ਬਿੱਟ - 8)))) & TDEFL_LEVEL1_HASH_ਮਾਪ_ਨਕਾਬ;
      mz_uint probe_pos = d->m_hash[hash];
      d->m_hash[hash] = (mz_uint16)lookahead_pos;

      ਜੇ (((cur_ਮੇਲ_dist = (mz_uint16)(lookahead_pos - probe_pos)) <= dict_ਮਾਪ) && ((*(ਅਚਲ mz_uint32 *)(d->m_dict + (probe_pos &= TDEFL_LZ_DICT_ਮਾਪ_ਨਕਾਬ)) & 0xFFFFFF) == ਪਹਿਲਾ_trigram))
      {
        ਅਚਲ mz_uint16 *p = (ਅਚਲ mz_uint16 *)pCur_dict;
        ਅਚਲ mz_uint16 *q = (ਅਚਲ mz_uint16 *)(d->m_dict + probe_pos);
        mz_uint32 probe_len = 32;
        ਕਰੋ { } ਜਦੋਂ ( (TDEFL_READ_UNALIGNED_ਸ਼ਬਦ(++p) == TDEFL_READ_UNALIGNED_ਸ਼ਬਦ(++q)) && (TDEFL_READ_UNALIGNED_ਸ਼ਬਦ(++p) == TDEFL_READ_UNALIGNED_ਸ਼ਬਦ(++q)) &&
          (TDEFL_READ_UNALIGNED_ਸ਼ਬਦ(++p) == TDEFL_READ_UNALIGNED_ਸ਼ਬਦ(++q)) && (TDEFL_READ_UNALIGNED_ਸ਼ਬਦ(++p) == TDEFL_READ_UNALIGNED_ਸ਼ਬਦ(++q)) && (--probe_len > 0) );
        cur_ਮੇਲ_len = ((mz_uint)(p - (ਅਚਲ mz_uint16 *)pCur_dict) * 2) + (mz_uint)(*(ਅਚਲ mz_uint8 *)p == *(ਅਚਲ mz_uint8 *)q);
        ਜੇ (!probe_len)
          cur_ਮੇਲ_len = cur_ਮੇਲ_dist ? TDEFL_MAX_ਮੇਲ_LEN : 0;

        ਜੇ ((cur_ਮੇਲ_len < TDEFL_MIN_ਮੇਲ_LEN) || ((cur_ਮੇਲ_len == TDEFL_MIN_ਮੇਲ_LEN) && (cur_ਮੇਲ_dist >= 8U*1024U)))
        {
          cur_ਮੇਲ_len = 1;
          *p_LZ_ਕੋਡ_buf++ = (mz_uint8)ਪਹਿਲਾ_trigram;
          *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
          d->m_huff_ਗਿਣਤੀ[0][(mz_uint8)ਪਹਿਲਾ_trigram]++;
        }
        ਨਹੀਂਤਾਂ
        {
          mz_uint32 s0, s1;
          cur_ਮੇਲ_len = MZ_MIN(cur_ਮੇਲ_len, lookahead_ਮਾਪ);

          MZ_ASSERT((cur_ਮੇਲ_len >= TDEFL_MIN_ਮੇਲ_LEN) && (cur_ਮੇਲ_dist >= 1) && (cur_ਮੇਲ_dist <= TDEFL_LZ_DICT_ਮਾਪ));

          cur_ਮੇਲ_dist--;

          p_LZ_ਕੋਡ_buf[0] = (mz_uint8)(cur_ਮੇਲ_len - TDEFL_MIN_ਮੇਲ_LEN);
          *(mz_uint16 *)(&p_LZ_ਕੋਡ_buf[1]) = (mz_uint16)cur_ਮੇਲ_dist;
          p_LZ_ਕੋਡ_buf += 3;
          *pLZ_flags = (mz_uint8)((*pLZ_flags >> 1) | 0x80);

          s0 = s_tdefl_small_dist_sym[cur_ਮੇਲ_dist & 511];
          s1 = s_tdefl_large_dist_sym[cur_ਮੇਲ_dist >> 8];
          d->m_huff_ਗਿਣਤੀ[1][(cur_ਮੇਲ_dist < 512) ? s0 : s1]++;

          d->m_huff_ਗਿਣਤੀ[0][s_tdefl_len_sym[cur_ਮੇਲ_len - TDEFL_MIN_ਮੇਲ_LEN]]++;
        }
      }
      ਨਹੀਂਤਾਂ
      {
        *p_LZ_ਕੋਡ_buf++ = (mz_uint8)ਪਹਿਲਾ_trigram;
        *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
        d->m_huff_ਗਿਣਤੀ[0][(mz_uint8)ਪਹਿਲਾ_trigram]++;
      }

      ਜੇ (--ਅੰਕ_flags_ਖੱਬਾ == 0) { ਅੰਕ_flags_ਖੱਬਾ = 8; pLZ_flags = p_LZ_ਕੋਡ_buf++; }

      ਕੁੱਲ_lz_ਬਾਈਟਾਂ += cur_ਮੇਲ_len;
      lookahead_pos += cur_ਮੇਲ_len;
      dict_ਮਾਪ = MZ_MIN(dict_ਮਾਪ + cur_ਮੇਲ_len, TDEFL_LZ_DICT_ਮਾਪ);
      cur_pos = (cur_pos + cur_ਮੇਲ_len) & TDEFL_LZ_DICT_ਮਾਪ_ਨਕਾਬ;
      MZ_ASSERT(lookahead_ਮਾਪ >= cur_ਮੇਲ_len);
      lookahead_ਮਾਪ -= cur_ਮੇਲ_len;

      ਜੇ (p_LZ_ਕੋਡ_buf > &d->m_lz_ਕੋਡ_buf[TDEFL_LZ_ਕੋਡ_BUF_ਮਾਪ - 8])
      {
        ਪੂਰਨ n;
        d->m_lookahead_pos = lookahead_pos; d->m_lookahead_ਮਾਪ = lookahead_ਮਾਪ; d->m_dict_ਮਾਪ = dict_ਮਾਪ;
        d->m_ਕੁੱਲ_lz_ਬਾਈਟਾਂ = ਕੁੱਲ_lz_ਬਾਈਟਾਂ; d->m_p_LZ_ਕੋਡ_buf = p_LZ_ਕੋਡ_buf; d->m_pLZ_flags = pLZ_flags; d->m_ਅੰਕ_flags_ਖੱਬਾ = ਅੰਕ_flags_ਖੱਬਾ;
        ਜੇ ((n = tdefl_flush_ਖੰਡ(d, 0)) != 0)
          ਵਾਪਸ (n < 0) ? MZ_FALSE : MZ_TRUE;
        ਕੁੱਲ_lz_ਬਾਈਟਾਂ = d->m_ਕੁੱਲ_lz_ਬਾਈਟਾਂ; p_LZ_ਕੋਡ_buf = d->m_p_LZ_ਕੋਡ_buf; pLZ_flags = d->m_pLZ_flags; ਅੰਕ_flags_ਖੱਬਾ = d->m_ਅੰਕ_flags_ਖੱਬਾ;
      }
    }

    ਜਦੋਂ (lookahead_ਮਾਪ)
    {
      mz_uint8 lit = d->m_dict[cur_pos];

      ਕੁੱਲ_lz_ਬਾਈਟਾਂ++;
      *p_LZ_ਕੋਡ_buf++ = lit;
      *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
      ਜੇ (--ਅੰਕ_flags_ਖੱਬਾ == 0) { ਅੰਕ_flags_ਖੱਬਾ = 8; pLZ_flags = p_LZ_ਕੋਡ_buf++; }

      d->m_huff_ਗਿਣਤੀ[0][lit]++;

      lookahead_pos++;
      dict_ਮਾਪ = MZ_MIN(dict_ਮਾਪ + 1, TDEFL_LZ_DICT_ਮਾਪ);
      cur_pos = (cur_pos + 1) & TDEFL_LZ_DICT_ਮਾਪ_ਨਕਾਬ;
      lookahead_ਮਾਪ--;

      ਜੇ (p_LZ_ਕੋਡ_buf > &d->m_lz_ਕੋਡ_buf[TDEFL_LZ_ਕੋਡ_BUF_ਮਾਪ - 8])
      {
        ਪੂਰਨ n;
        d->m_lookahead_pos = lookahead_pos; d->m_lookahead_ਮਾਪ = lookahead_ਮਾਪ; d->m_dict_ਮਾਪ = dict_ਮਾਪ;
        d->m_ਕੁੱਲ_lz_ਬਾਈਟਾਂ = ਕੁੱਲ_lz_ਬਾਈਟਾਂ; d->m_p_LZ_ਕੋਡ_buf = p_LZ_ਕੋਡ_buf; d->m_pLZ_flags = pLZ_flags; d->m_ਅੰਕ_flags_ਖੱਬਾ = ਅੰਕ_flags_ਖੱਬਾ;
        ਜੇ ((n = tdefl_flush_ਖੰਡ(d, 0)) != 0)
          ਵਾਪਸ (n < 0) ? MZ_FALSE : MZ_TRUE;
        ਕੁੱਲ_lz_ਬਾਈਟਾਂ = d->m_ਕੁੱਲ_lz_ਬਾਈਟਾਂ; p_LZ_ਕੋਡ_buf = d->m_p_LZ_ਕੋਡ_buf; pLZ_flags = d->m_pLZ_flags; ਅੰਕ_flags_ਖੱਬਾ = d->m_ਅੰਕ_flags_ਖੱਬਾ;
      }
    }
  }

  d->m_lookahead_pos = lookahead_pos; d->m_lookahead_ਮਾਪ = lookahead_ਮਾਪ; d->m_dict_ਮਾਪ = dict_ਮਾਪ;
  d->m_ਕੁੱਲ_lz_ਬਾਈਟਾਂ = ਕੁੱਲ_lz_ਬਾਈਟਾਂ; d->m_p_LZ_ਕੋਡ_buf = p_LZ_ਕੋਡ_buf; d->m_pLZ_flags = pLZ_flags; d->m_ਅੰਕ_flags_ਖੱਬਾ = ਅੰਕ_flags_ਖੱਬਾ;
  ਵਾਪਸ MZ_TRUE;
}
#ਜੇ_ਅੰਤ // MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN

ਸਥਿਰ MZ_FORCEINLINE ਖਾਲੀ tdefl_ਰਿਕਾਰਡ_literal(tdefl_compressor *d, mz_uint8 lit)
{
  d->m_ਕੁੱਲ_lz_ਬਾਈਟਾਂ++;
  *d->m_p_LZ_ਕੋਡ_buf++ = lit;
  *d->m_pLZ_flags = (mz_uint8)(*d->m_pLZ_flags >> 1); ਜੇ (--d->m_ਅੰਕ_flags_ਖੱਬਾ == 0) { d->m_ਅੰਕ_flags_ਖੱਬਾ = 8; d->m_pLZ_flags = d->m_p_LZ_ਕੋਡ_buf++; }
  d->m_huff_ਗਿਣਤੀ[0][lit]++;
}

ਸਥਿਰ MZ_FORCEINLINE ਖਾਲੀ tdefl_ਰਿਕਾਰਡ_ਮੇਲ(tdefl_compressor *d, mz_uint ਮੇਲ_len, mz_uint ਮੇਲ_dist)
{
  mz_uint32 s0, s1;

  MZ_ASSERT((ਮੇਲ_len >= TDEFL_MIN_ਮੇਲ_LEN) && (ਮੇਲ_dist >= 1) && (ਮੇਲ_dist <= TDEFL_LZ_DICT_ਮਾਪ));

  d->m_ਕੁੱਲ_lz_ਬਾਈਟਾਂ += ਮੇਲ_len;

  d->m_p_LZ_ਕੋਡ_buf[0] = (mz_uint8)(ਮੇਲ_len - TDEFL_MIN_ਮੇਲ_LEN);

  ਮੇਲ_dist -= 1;
  d->m_p_LZ_ਕੋਡ_buf[1] = (mz_uint8)(ਮੇਲ_dist & 0xFF);
  d->m_p_LZ_ਕੋਡ_buf[2] = (mz_uint8)(ਮੇਲ_dist >> 8); d->m_p_LZ_ਕੋਡ_buf += 3;

  *d->m_pLZ_flags = (mz_uint8)((*d->m_pLZ_flags >> 1) | 0x80); ਜੇ (--d->m_ਅੰਕ_flags_ਖੱਬਾ == 0) { d->m_ਅੰਕ_flags_ਖੱਬਾ = 8; d->m_pLZ_flags = d->m_p_LZ_ਕੋਡ_buf++; }

  s0 = s_tdefl_small_dist_sym[ਮੇਲ_dist & 511]; s1 = s_tdefl_large_dist_sym[(ਮੇਲ_dist >> 8) & 127];
  d->m_huff_ਗਿਣਤੀ[1][(ਮੇਲ_dist < 512) ? s0 : s1]++;

  ਜੇ (ਮੇਲ_len >= TDEFL_MIN_ਮੇਲ_LEN) d->m_huff_ਗਿਣਤੀ[0][s_tdefl_len_sym[ਮੇਲ_len - TDEFL_MIN_ਮੇਲ_LEN]]++;
}

ਸਥਿਰ mz_bool tdefl_compress_ਸਾਧਾਰਨ(tdefl_compressor *d)
{
  ਅਚਲ mz_uint8 *pSrc = d->m_pSrc; size_t src_buf_ਖੱਬਾ = d->m_src_buf_ਖੱਬਾ;
  tdefl_flush flush = d->m_flush;

  ਜਦੋਂ ((src_buf_ਖੱਬਾ) || ((flush) && (d->m_lookahead_ਮਾਪ)))
  {
    mz_uint len_ਮੰਜ਼ਿਲ_move, cur_ਮੇਲ_dist, cur_ਮੇਲ_len, cur_pos;
    // Update dictionary and hash chains. Keeps the lookahead size equal to TDEFL_MAX_MATCH_LEN.
    ਜੇ ((d->m_lookahead_ਮਾਪ + d->m_dict_ਮਾਪ) >= (TDEFL_MIN_ਮੇਲ_LEN - 1))
    {
      mz_uint dst_pos = (d->m_lookahead_pos + d->m_lookahead_ਮਾਪ) & TDEFL_LZ_DICT_ਮਾਪ_ਨਕਾਬ, ins_pos = d->m_lookahead_pos + d->m_lookahead_ਮਾਪ - 2;
      mz_uint hash = (d->m_dict[ins_pos & TDEFL_LZ_DICT_ਮਾਪ_ਨਕਾਬ] << TDEFL_LZ_HASH_ਖਿਸਕਾਓ) ^ d->m_dict[(ins_pos + 1) & TDEFL_LZ_DICT_ਮਾਪ_ਨਕਾਬ];
      mz_uint ਅੰਕ_ਬਾਈਟਾਂ_ਮੰਜ਼ਿਲ_process = (mz_uint)MZ_MIN(src_buf_ਖੱਬਾ, TDEFL_MAX_ਮੇਲ_LEN - d->m_lookahead_ਮਾਪ);
      ਅਚਲ mz_uint8 *p_Src_ਸਿਰਾ = pSrc ? pSrc + ਅੰਕ_ਬਾਈਟਾਂ_ਮੰਜ਼ਿਲ_process : ਨਿਰਾ;
      src_buf_ਖੱਬਾ -= ਅੰਕ_ਬਾਈਟਾਂ_ਮੰਜ਼ਿਲ_process;
      d->m_lookahead_ਮਾਪ += ਅੰਕ_ਬਾਈਟਾਂ_ਮੰਜ਼ਿਲ_process;
      ਜਦੋਂ (pSrc != p_Src_ਸਿਰਾ)
      {
        mz_uint8 c = *pSrc++; d->m_dict[dst_pos] = c; ਜੇ (dst_pos < (TDEFL_MAX_ਮੇਲ_LEN - 1)) d->m_dict[TDEFL_LZ_DICT_ਮਾਪ + dst_pos] = c;
        hash = ((hash << TDEFL_LZ_HASH_ਖਿਸਕਾਓ) ^ c) & (TDEFL_LZ_HASH_ਮਾਪ - 1);
        d->m_ਅਗਲਾ[ins_pos & TDEFL_LZ_DICT_ਮਾਪ_ਨਕਾਬ] = d->m_hash[hash]; d->m_hash[hash] = (mz_uint16)(ins_pos);
        dst_pos = (dst_pos + 1) & TDEFL_LZ_DICT_ਮਾਪ_ਨਕਾਬ; ins_pos++;
      }
    }
    ਨਹੀਂਤਾਂ
    {
      ਜਦੋਂ ((src_buf_ਖੱਬਾ) && (d->m_lookahead_ਮਾਪ < TDEFL_MAX_ਮੇਲ_LEN))
      {
        mz_uint8 c = *pSrc++;
        mz_uint dst_pos = (d->m_lookahead_pos + d->m_lookahead_ਮਾਪ) & TDEFL_LZ_DICT_ਮਾਪ_ਨਕਾਬ;
        src_buf_ਖੱਬਾ--;
        d->m_dict[dst_pos] = c;
        ਜੇ (dst_pos < (TDEFL_MAX_ਮੇਲ_LEN - 1))
          d->m_dict[TDEFL_LZ_DICT_ਮਾਪ + dst_pos] = c;
        ਜੇ ((++d->m_lookahead_ਮਾਪ + d->m_dict_ਮਾਪ) >= TDEFL_MIN_ਮੇਲ_LEN)
        {
          mz_uint ins_pos = d->m_lookahead_pos + (d->m_lookahead_ਮਾਪ - 1) - 2;
          mz_uint hash = ((d->m_dict[ins_pos & TDEFL_LZ_DICT_ਮਾਪ_ਨਕਾਬ] << (TDEFL_LZ_HASH_ਖਿਸਕਾਓ * 2)) ^ (d->m_dict[(ins_pos + 1) & TDEFL_LZ_DICT_ਮਾਪ_ਨਕਾਬ] << TDEFL_LZ_HASH_ਖਿਸਕਾਓ) ^ c) & (TDEFL_LZ_HASH_ਮਾਪ - 1);
          d->m_ਅਗਲਾ[ins_pos & TDEFL_LZ_DICT_ਮਾਪ_ਨਕਾਬ] = d->m_hash[hash]; d->m_hash[hash] = (mz_uint16)(ins_pos);
        }
      }
    }
    d->m_dict_ਮਾਪ = MZ_MIN(TDEFL_LZ_DICT_ਮਾਪ - d->m_lookahead_ਮਾਪ, d->m_dict_ਮਾਪ);
    ਜੇ ((!flush) && (d->m_lookahead_ਮਾਪ < TDEFL_MAX_ਮੇਲ_LEN))
      ਰੋਕੋ;

    // Simple lazy/greedy parsing state machine.
    len_ਮੰਜ਼ਿਲ_move = 1; cur_ਮੇਲ_dist = 0; cur_ਮੇਲ_len = d->m_saved_ਮੇਲ_len ? d->m_saved_ਮੇਲ_len : (TDEFL_MIN_ਮੇਲ_LEN - 1); cur_pos = d->m_lookahead_pos & TDEFL_LZ_DICT_ਮਾਪ_ਨਕਾਬ;
    ਜੇ (d->m_flags & (TDEFL_RLE_MATCHES | TDEFL_FORCE_ALL_RAW_ਖੰਡਾਂ))
    {
      ਜੇ ((d->m_dict_ਮਾਪ) && (!(d->m_flags & TDEFL_FORCE_ALL_RAW_ਖੰਡਾਂ)))
      {
        mz_uint8 c = d->m_dict[(cur_pos - 1) & TDEFL_LZ_DICT_ਮਾਪ_ਨਕਾਬ];
        cur_ਮੇਲ_len = 0; ਜਦੋਂ (cur_ਮੇਲ_len < d->m_lookahead_ਮਾਪ) { ਜੇ (d->m_dict[cur_pos + cur_ਮੇਲ_len] != c) ਰੋਕੋ; cur_ਮੇਲ_len++; }
        ਜੇ (cur_ਮੇਲ_len < TDEFL_MIN_ਮੇਲ_LEN) cur_ਮੇਲ_len = 0; ਨਹੀਂਤਾਂ cur_ਮੇਲ_dist = 1;
      }
    }
    ਨਹੀਂਤਾਂ
    {
      tdefl_ਲੱਭੋ_ਮੇਲ(d, d->m_lookahead_pos, d->m_dict_ਮਾਪ, d->m_lookahead_ਮਾਪ, &cur_ਮੇਲ_dist, &cur_ਮੇਲ_len);
    }
    ਜੇ (((cur_ਮੇਲ_len == TDEFL_MIN_ਮੇਲ_LEN) && (cur_ਮੇਲ_dist >= 8U*1024U)) || (cur_pos == cur_ਮੇਲ_dist) || ((d->m_flags & TDEFL_FILTER_MATCHES) && (cur_ਮੇਲ_len <= 5)))
    {
      cur_ਮੇਲ_dist = cur_ਮੇਲ_len = 0;
    }
    ਜੇ (d->m_saved_ਮੇਲ_len)
    {
      ਜੇ (cur_ਮੇਲ_len > d->m_saved_ਮੇਲ_len)
      {
        tdefl_ਰਿਕਾਰਡ_literal(d, (mz_uint8)d->m_saved_lit);
        ਜੇ (cur_ਮੇਲ_len >= 128)
        {
          tdefl_ਰਿਕਾਰਡ_ਮੇਲ(d, cur_ਮੇਲ_len, cur_ਮੇਲ_dist);
          d->m_saved_ਮੇਲ_len = 0; len_ਮੰਜ਼ਿਲ_move = cur_ਮੇਲ_len;
        }
        ਨਹੀਂਤਾਂ
        {
          d->m_saved_lit = d->m_dict[cur_pos]; d->m_saved_ਮੇਲ_dist = cur_ਮੇਲ_dist; d->m_saved_ਮੇਲ_len = cur_ਮੇਲ_len;
        }
      }
      ਨਹੀਂਤਾਂ
      {
        tdefl_ਰਿਕਾਰਡ_ਮੇਲ(d, d->m_saved_ਮੇਲ_len, d->m_saved_ਮੇਲ_dist);
        len_ਮੰਜ਼ਿਲ_move = d->m_saved_ਮੇਲ_len - 1; d->m_saved_ਮੇਲ_len = 0;
      }
    }
    ਨਹੀਂਤਾਂ ਜੇ (!cur_ਮੇਲ_dist)
      tdefl_ਰਿਕਾਰਡ_literal(d, d->m_dict[MZ_MIN(cur_pos, ਆਕਾਰ(d->m_dict) - 1)]);
    ਨਹੀਂਤਾਂ ਜੇ ((d->m_greedy_parsing) || (d->m_flags & TDEFL_RLE_MATCHES) || (cur_ਮੇਲ_len >= 128))
    {
      tdefl_ਰਿਕਾਰਡ_ਮੇਲ(d, cur_ਮੇਲ_len, cur_ਮੇਲ_dist);
      len_ਮੰਜ਼ਿਲ_move = cur_ਮੇਲ_len;
    }
    ਨਹੀਂਤਾਂ
    {
      d->m_saved_lit = d->m_dict[MZ_MIN(cur_pos, ਆਕਾਰ(d->m_dict) - 1)]; d->m_saved_ਮੇਲ_dist = cur_ਮੇਲ_dist; d->m_saved_ਮੇਲ_len = cur_ਮੇਲ_len;
    }
    // Move the lookahead forward by len_to_move bytes.
    d->m_lookahead_pos += len_ਮੰਜ਼ਿਲ_move;
    MZ_ASSERT(d->m_lookahead_ਮਾਪ >= len_ਮੰਜ਼ਿਲ_move);
    d->m_lookahead_ਮਾਪ -= len_ਮੰਜ਼ਿਲ_move;
    d->m_dict_ਮਾਪ = MZ_MIN(d->m_dict_ਮਾਪ + len_ਮੰਜ਼ਿਲ_move, TDEFL_LZ_DICT_ਮਾਪ);
    // Check if it's time to flush the current LZ codes to the internal output buffer.
    ਜੇ ( (d->m_p_LZ_ਕੋਡ_buf > &d->m_lz_ਕੋਡ_buf[TDEFL_LZ_ਕੋਡ_BUF_ਮਾਪ - 8]) ||
         ( (d->m_ਕੁੱਲ_lz_ਬਾਈਟਾਂ > 31*1024) && (((((mz_uint)(d->m_p_LZ_ਕੋਡ_buf - d->m_lz_ਕੋਡ_buf) * 115) >> 7) >= d->m_ਕੁੱਲ_lz_ਬਾਈਟਾਂ) || (d->m_flags & TDEFL_FORCE_ALL_RAW_ਖੰਡਾਂ))) )
    {
      ਪੂਰਨ n;
      d->m_pSrc = pSrc; d->m_src_buf_ਖੱਬਾ = src_buf_ਖੱਬਾ;
      ਜੇ ((n = tdefl_flush_ਖੰਡ(d, 0)) != 0)
        ਵਾਪਸ (n < 0) ? MZ_FALSE : MZ_TRUE;
    }
  }

  d->m_pSrc = pSrc; d->m_src_buf_ਖੱਬਾ = src_buf_ਖੱਬਾ;
  ਵਾਪਸ MZ_TRUE;
}

ਸਥਿਰ tdefl_ਸਥਿਤੀ tdefl_flush_output_ਬਫਰ(tdefl_compressor *d)
{
  ਜੇ (d->m_p_ਵਿੱਚ_buf_ਮਾਪ)
  {
    *d->m_p_ਵਿੱਚ_buf_ਮਾਪ = d->m_pSrc - (ਅਚਲ mz_uint8 *)d->m_p_ਵਿੱਚ_buf;
  }

  ਜੇ (d->m_p_ਬਾਹਰਲਾ_buf_ਮਾਪ)
  {
    size_t n = MZ_MIN(*d->m_p_ਬਾਹਰਲਾ_buf_ਮਾਪ - d->m_ਬਾਹਰਲਾ_buf_ofs, d->m_output_flush_ਬਚਿਆ);
    ਸਮ੍ਰਿਤੀ_ਨਕਲ((mz_uint8 *)d->m_p_ਬਾਹਰਲਾ_buf + d->m_ਬਾਹਰਲਾ_buf_ofs, d->m_output_buf + d->m_output_flush_ofs, n);
    d->m_output_flush_ofs += (mz_uint)n;
    d->m_output_flush_ਬਚਿਆ -= (mz_uint)n;
    d->m_ਬਾਹਰਲਾ_buf_ofs += n;

    *d->m_p_ਬਾਹਰਲਾ_buf_ਮਾਪ = d->m_ਬਾਹਰਲਾ_buf_ofs;
  }

  ਵਾਪਸ (d->m_ਮੁਕੰਮਲ && !d->m_output_flush_ਬਚਿਆ) ? TDEFL_ਸਥਿਤੀ_ਪੂਰਾ : TDEFL_ਸਥਿਤੀ_OKAY;
}

tdefl_ਸਥਿਤੀ tdefl_compress(tdefl_compressor *d, ਅਚਲ ਖਾਲੀ *p_ਵਿੱਚ_buf, size_t *p_ਵਿੱਚ_buf_ਮਾਪ, ਖਾਲੀ *p_ਬਾਹਰਲਾ_buf, size_t *p_ਬਾਹਰਲਾ_buf_ਮਾਪ, tdefl_flush flush)
{
  ਜੇ (!d)
  {
    ਜੇ (p_ਵਿੱਚ_buf_ਮਾਪ) *p_ਵਿੱਚ_buf_ਮਾਪ = 0;
    ਜੇ (p_ਬਾਹਰਲਾ_buf_ਮਾਪ) *p_ਬਾਹਰਲਾ_buf_ਮਾਪ = 0;
    ਵਾਪਸ TDEFL_ਸਥਿਤੀ_BAD_PARAM;
  }

  d->m_p_ਵਿੱਚ_buf = p_ਵਿੱਚ_buf; d->m_p_ਵਿੱਚ_buf_ਮਾਪ = p_ਵਿੱਚ_buf_ਮਾਪ;
  d->m_p_ਬਾਹਰਲਾ_buf = p_ਬਾਹਰਲਾ_buf; d->m_p_ਬਾਹਰਲਾ_buf_ਮਾਪ = p_ਬਾਹਰਲਾ_buf_ਮਾਪ;
  d->m_pSrc = (ਅਚਲ mz_uint8 *)(p_ਵਿੱਚ_buf); d->m_src_buf_ਖੱਬਾ = p_ਵਿੱਚ_buf_ਮਾਪ ? *p_ਵਿੱਚ_buf_ਮਾਪ : 0;
  d->m_ਬਾਹਰਲਾ_buf_ofs = 0;
  d->m_flush = flush;

  ਜੇ ( ((d->m_pPut_buf_func != ਨਿਰਾ) == ((p_ਬਾਹਰਲਾ_buf != ਨਿਰਾ) || (p_ਬਾਹਰਲਾ_buf_ਮਾਪ != ਨਿਰਾ))) || (d->m_prev_return_ਸਥਿਤੀ != TDEFL_ਸਥਿਤੀ_OKAY) ||
        (d->m_ਚਾਹੁੰਦਾ_ਮੰਜ਼ਿਲ_ਅੰਤ && (flush != TDEFL_ਅੰਤ)) || (p_ਵਿੱਚ_buf_ਮਾਪ && *p_ਵਿੱਚ_buf_ਮਾਪ && !p_ਵਿੱਚ_buf) || (p_ਬਾਹਰਲਾ_buf_ਮਾਪ && *p_ਬਾਹਰਲਾ_buf_ਮਾਪ && !p_ਬਾਹਰਲਾ_buf) )
  {
    ਜੇ (p_ਵਿੱਚ_buf_ਮਾਪ) *p_ਵਿੱਚ_buf_ਮਾਪ = 0;
    ਜੇ (p_ਬਾਹਰਲਾ_buf_ਮਾਪ) *p_ਬਾਹਰਲਾ_buf_ਮਾਪ = 0;
    ਵਾਪਸ (d->m_prev_return_ਸਥਿਤੀ = TDEFL_ਸਥਿਤੀ_BAD_PARAM);
  }
  d->m_ਚਾਹੁੰਦਾ_ਮੰਜ਼ਿਲ_ਅੰਤ |= (flush == TDEFL_ਅੰਤ);

  ਜੇ ((d->m_output_flush_ਬਚਿਆ) || (d->m_ਮੁਕੰਮਲ))
    ਵਾਪਸ (d->m_prev_return_ਸਥਿਤੀ = tdefl_flush_output_ਬਫਰ(d));

#ਜੇ MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  ਜੇ (((d->m_flags & TDEFL_MAX_PROBES_ਨਕਾਬ) == 1) &&
      ((d->m_flags & TDEFL_GREEDY_PARSING_FLAG) != 0) &&
      ((d->m_flags & (TDEFL_FILTER_MATCHES | TDEFL_FORCE_ALL_RAW_ਖੰਡਾਂ | TDEFL_RLE_MATCHES)) == 0))
  {
    ਜੇ (!tdefl_compress_fast(d))
      ਵਾਪਸ d->m_prev_return_ਸਥਿਤੀ;
  }
  ਨਹੀਂਤਾਂ
#ਜੇ_ਅੰਤ // #if MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  {
    ਜੇ (!tdefl_compress_ਸਾਧਾਰਨ(d))
      ਵਾਪਸ d->m_prev_return_ਸਥਿਤੀ;
  }

  ਜੇ ((d->m_flags & (TDEFL_WRITE_ZLIB_ਸਿਰਲੇਖ | TDEFL_COMPUTE_ADLER32)) && (p_ਵਿੱਚ_buf))
    d->m_adler32 = (mz_uint32)mz_adler32(d->m_adler32, (ਅਚਲ mz_uint8 *)p_ਵਿੱਚ_buf, d->m_pSrc - (ਅਚਲ mz_uint8 *)p_ਵਿੱਚ_buf);

  ਜੇ ((flush) && (!d->m_lookahead_ਮਾਪ) && (!d->m_src_buf_ਖੱਬਾ) && (!d->m_output_flush_ਬਚਿਆ))
  {
    ਜੇ (tdefl_flush_ਖੰਡ(d, flush) < 0)
      ਵਾਪਸ d->m_prev_return_ਸਥਿਤੀ;
    d->m_ਮੁਕੰਮਲ = (flush == TDEFL_ਅੰਤ);
    ਜੇ (flush == TDEFL_ਭਰਿਆ_FLUSH) { MZ_CLEAR_ARR(d->m_hash); MZ_CLEAR_ARR(d->m_ਅਗਲਾ); d->m_dict_ਮਾਪ = 0; }
  }

  ਵਾਪਸ (d->m_prev_return_ਸਥਿਤੀ = tdefl_flush_output_ਬਫਰ(d));
}

tdefl_ਸਥਿਤੀ tdefl_compress_ਬਫਰ(tdefl_compressor *d, ਅਚਲ ਖਾਲੀ *p_ਵਿੱਚ_buf, size_t ਵਿੱਚ_buf_ਮਾਪ, tdefl_flush flush)
{
  MZ_ASSERT(d->m_pPut_buf_func); ਵਾਪਸ tdefl_compress(d, p_ਵਿੱਚ_buf, &ਵਿੱਚ_buf_ਮਾਪ, ਨਿਰਾ, ਨਿਰਾ, flush);
}

tdefl_ਸਥਿਤੀ tdefl_init(tdefl_compressor *d, tdefl_put_buf_func_ptr pPut_buf_func, ਖਾਲੀ *pPut_buf_user, ਪੂਰਨ flags)
{
  d->m_pPut_buf_func = pPut_buf_func; d->m_pPut_buf_user = pPut_buf_user;
  d->m_flags = (mz_uint)(flags); d->m_max_probes[0] = 1 + ((flags & 0xFFF) + 2) / 3; d->m_greedy_parsing = (flags & TDEFL_GREEDY_PARSING_FLAG) != 0;
  d->m_max_probes[1] = 1 + (((flags & 0xFFF) >> 2) + 2) / 3;
  ਜੇ (!(flags & TDEFL_NONDETERMINISTIC_PARSING_FLAG)) MZ_CLEAR_ARR(d->m_hash);
  d->m_lookahead_pos = d->m_lookahead_ਮਾਪ = d->m_dict_ਮਾਪ = d->m_ਕੁੱਲ_lz_ਬਾਈਟਾਂ = d->m_lz_ਕੋਡ_buf_dict_pos = d->m_ਬਿੱਟ_ਵਿੱਚ = 0;
  d->m_output_flush_ofs = d->m_output_flush_ਬਚਿਆ = d->m_ਮੁਕੰਮਲ = d->m_ਖੰਡ_ਸੂਚਕਾਂਕ = d->m_ਦੋਆਧਾਰੀ_ਅੰਕ_ਬਫਰ = d->m_ਚਾਹੁੰਦਾ_ਮੰਜ਼ਿਲ_ਅੰਤ = 0;
  d->m_p_LZ_ਕੋਡ_buf = d->m_lz_ਕੋਡ_buf + 1; d->m_pLZ_flags = d->m_lz_ਕੋਡ_buf; d->m_ਅੰਕ_flags_ਖੱਬਾ = 8;
  d->m_pOutput_buf = d->m_output_buf; d->m_p_Output_buf_ਸਿਰਾ = d->m_output_buf; d->m_prev_return_ਸਥਿਤੀ = TDEFL_ਸਥਿਤੀ_OKAY;
  d->m_saved_ਮੇਲ_dist = d->m_saved_ਮੇਲ_len = d->m_saved_lit = 0; d->m_adler32 = 1;
  d->m_p_ਵਿੱਚ_buf = ਨਿਰਾ; d->m_p_ਬਾਹਰਲਾ_buf = ਨਿਰਾ;
  d->m_p_ਵਿੱਚ_buf_ਮਾਪ = ਨਿਰਾ; d->m_p_ਬਾਹਰਲਾ_buf_ਮਾਪ = ਨਿਰਾ;
  d->m_flush = TDEFL_NO_FLUSH; d->m_pSrc = ਨਿਰਾ; d->m_src_buf_ਖੱਬਾ = 0; d->m_ਬਾਹਰਲਾ_buf_ofs = 0;
  memset(&d->m_huff_ਗਿਣਤੀ[0][0], 0, ਆਕਾਰ(d->m_huff_ਗਿਣਤੀ[0][0]) * TDEFL_MAX_HUFF_SYMBOLS_0);
  memset(&d->m_huff_ਗਿਣਤੀ[1][0], 0, ਆਕਾਰ(d->m_huff_ਗਿਣਤੀ[1][0]) * TDEFL_MAX_HUFF_SYMBOLS_1);
  ਵਾਪਸ TDEFL_ਸਥਿਤੀ_OKAY;
}

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_SDL_NOUNUSED
tdefl_ਸਥਿਤੀ tdefl_get_prev_return_ਸਥਿਤੀ(tdefl_compressor *d)
{
  ਵਾਪਸ d->m_prev_return_ਸਥਿਤੀ;
}

mz_uint32 tdefl_get_adler32(tdefl_compressor *d)
{
  ਵਾਪਸ d->m_adler32;
}

mz_bool tdefl_compress_mem_ਮੰਜ਼ਿਲ_output(ਅਚਲ ਖਾਲੀ *pBuf, size_t buf_len, tdefl_put_buf_func_ptr pPut_buf_func, ਖਾਲੀ *pPut_buf_user, ਪੂਰਨ flags)
{
  tdefl_compressor *pComp; mz_bool succeeded; ਜੇ (((buf_len) && (!pBuf)) || (!pPut_buf_func)) ਵਾਪਸ MZ_FALSE;
  pComp = (tdefl_compressor*)MZ_MALLOC(ਆਕਾਰ(tdefl_compressor)); ਜੇ (!pComp) ਵਾਪਸ MZ_FALSE;
  succeeded = (tdefl_init(pComp, pPut_buf_func, pPut_buf_user, flags) == TDEFL_ਸਥਿਤੀ_OKAY);
  succeeded = succeeded && (tdefl_compress_ਬਫਰ(pComp, pBuf, buf_len, TDEFL_ਅੰਤ) == TDEFL_ਸਥਿਤੀ_ਪੂਰਾ);
  MZ_FREE(pComp); ਵਾਪਸ succeeded;
}
#ਜੇ_ਅੰਤ /* MINIZ_SDL_NOUNUSED */

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
  size_t m_ਮਾਪ, m_ਸਮਰੱਥਾ;
  mz_uint8 *m_pBuf;
  mz_bool m_expandable;
} tdefl_output_ਬਫਰ;

ਸਥਿਰ mz_bool tdefl_output_ਬਫਰ_putter(ਅਚਲ ਖਾਲੀ *pBuf, ਪੂਰਨ len, ਖਾਲੀ *pUser)
{
  tdefl_output_ਬਫਰ *p = (tdefl_output_ਬਫਰ *)pUser;
  size_t new_ਮਾਪ = p->m_ਮਾਪ + len;
  ਜੇ (new_ਮਾਪ > p->m_ਸਮਰੱਥਾ)
  {
    size_t new_ਸਮਰੱਥਾ = p->m_ਸਮਰੱਥਾ; mz_uint8 *pNew_buf; ਜੇ (!p->m_expandable) ਵਾਪਸ MZ_FALSE;
    ਕਰੋ { new_ਸਮਰੱਥਾ = MZ_MAX(128U, new_ਸਮਰੱਥਾ << 1U); } ਜਦੋਂ (new_ਮਾਪ > new_ਸਮਰੱਥਾ);
    pNew_buf = (mz_uint8*)MZ_REALLOC(p->m_pBuf, new_ਸਮਰੱਥਾ); ਜੇ (!pNew_buf) ਵਾਪਸ MZ_FALSE;
    p->m_pBuf = pNew_buf; p->m_ਸਮਰੱਥਾ = new_ਸਮਰੱਥਾ;
  }
  ਸਮ੍ਰਿਤੀ_ਨਕਲ((mz_uint8*)p->m_pBuf + p->m_ਮਾਪ, pBuf, len); p->m_ਮਾਪ = new_ਮਾਪ;
  ਵਾਪਸ MZ_TRUE;
}

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_SDL_NOUNUSED
ਖਾਲੀ *tdefl_compress_mem_ਮੰਜ਼ਿਲ_ਢੇਰ(ਅਚਲ ਖਾਲੀ *pSrc_buf, size_t src_buf_len, size_t *p_ਬਾਹਰਲਾ_len, ਪੂਰਨ flags)
{
  tdefl_output_ਬਫਰ ਬਾਹਰਲਾ_buf; MZ_CLEAR_OBJ(ਬਾਹਰਲਾ_buf);
  ਜੇ (!p_ਬਾਹਰਲਾ_len) ਵਾਪਸ MZ_FALSE; ਨਹੀਂਤਾਂ *p_ਬਾਹਰਲਾ_len = 0;
  ਬਾਹਰਲਾ_buf.m_expandable = MZ_TRUE;
  ਜੇ (!tdefl_compress_mem_ਮੰਜ਼ਿਲ_output(pSrc_buf, src_buf_len, tdefl_output_ਬਫਰ_putter, &ਬਾਹਰਲਾ_buf, flags)) ਵਾਪਸ ਨਿਰਾ;
  *p_ਬਾਹਰਲਾ_len = ਬਾਹਰਲਾ_buf.m_ਮਾਪ; ਵਾਪਸ ਬਾਹਰਲਾ_buf.m_pBuf;
}

size_t tdefl_compress_mem_ਮੰਜ਼ਿਲ_mem(ਖਾਲੀ *p_ਬਾਹਰਲਾ_buf, size_t ਬਾਹਰਲਾ_buf_len, ਅਚਲ ਖਾਲੀ *pSrc_buf, size_t src_buf_len, ਪੂਰਨ flags)
{
  tdefl_output_ਬਫਰ ਬਾਹਰਲਾ_buf; MZ_CLEAR_OBJ(ਬਾਹਰਲਾ_buf);
  ਜੇ (!p_ਬਾਹਰਲਾ_buf) ਵਾਪਸ 0;
  ਬਾਹਰਲਾ_buf.m_pBuf = (mz_uint8*)p_ਬਾਹਰਲਾ_buf; ਬਾਹਰਲਾ_buf.m_ਸਮਰੱਥਾ = ਬਾਹਰਲਾ_buf_len;
  ਜੇ (!tdefl_compress_mem_ਮੰਜ਼ਿਲ_output(pSrc_buf, src_buf_len, tdefl_output_ਬਫਰ_putter, &ਬਾਹਰਲਾ_buf, flags)) ਵਾਪਸ 0;
  ਵਾਪਸ ਬਾਹਰਲਾ_buf.m_ਮਾਪ;
}
#ਜੇ_ਅੰਤ /* MINIZ_SDL_NOUNUSED */

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_ZLIB_APIS
ਸਥਿਰ ਅਚਲ mz_uint s_tdefl_ਅੰਕ_probes[11] = { 0, 1, 6, 32,  16, 32, 128, 256,  512, 768, 1500 };

// level may actually range from [0,10] (10 is a "hidden" max level, where we want a bit more compression and it's fine if throughput to fall off a cliff on some files).
mz_uint tdefl_create_comp_flags_from_zip_params(ਪੂਰਨ level, ਪੂਰਨ ਖਿੜਕੀ_ਬਿੱਟ, ਪੂਰਨ strategy)
{
  mz_uint comp_flags = s_tdefl_ਅੰਕ_probes[(level >= 0) ? MZ_MIN(10, level) : MZ_DEFAULT_LEVEL] | ((level <= 3) ? TDEFL_GREEDY_PARSING_FLAG : 0);
  ਜੇ (ਖਿੜਕੀ_ਬਿੱਟ > 0) comp_flags |= TDEFL_WRITE_ZLIB_ਸਿਰਲੇਖ;

  ਜੇ (!level) comp_flags |= TDEFL_FORCE_ALL_RAW_ਖੰਡਾਂ;
  ਨਹੀਂਤਾਂ ਜੇ (strategy == MZ_FILTERED) comp_flags |= TDEFL_FILTER_MATCHES;
  ਨਹੀਂਤਾਂ ਜੇ (strategy == MZ_HUFFMAN_ONLY) comp_flags &= ~TDEFL_MAX_PROBES_ਨਕਾਬ;
  ਨਹੀਂਤਾਂ ਜੇ (strategy == MZ_FIXED) comp_flags |= TDEFL_FORCE_ALL_STATIC_ਖੰਡਾਂ;
  ਨਹੀਂਤਾਂ ਜੇ (strategy == MZ_RLE) comp_flags |= TDEFL_RLE_MATCHES;

  ਵਾਪਸ comp_flags;
}
#ਜੇ_ਅੰਤ //MINIZ_NO_ZLIB_APIS

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _MSC_VER
#ਹਦਾਇਤ warning (ਧੱਕੋ)
#ਹਦਾਇਤ warning (disable:4204) // nonstandard extension used : non-constant aggregate initializer (also supported by GNU C and C99, so no big deal)
#ਜੇ_ਅੰਤ

// Simple PNG writer function by Alex Evans, 2011. Released into the public domain: https://gist.github.com/908299, more context at
// http://altdevblogaday.org/2011/04/06/a-smaller-jpg-encoder/.
// This is actually a modification of Alex's original code so PNG files generated by this function pass pngcheck.
MINIZ_STATIC ਖਾਲੀ *tdefl_write_image_ਮੰਜ਼ਿਲ_png_file_ਵਿੱਚ_ਸਮ੍ਰਿਤੀ_ex(ਅਚਲ ਖਾਲੀ *pImage, ਪੂਰਨ w, ਪੂਰਨ h, ਪੂਰਨ ਅੰਕ_chans, ਪੂਰਨ bpl, size_t *p_Len_ਬਾਹਰਲਾ, mz_uint level, mz_bool flip, mz_uint8 *plte, ਪੂਰਨ plte_ਮਾਪ, mz_uint8 *trns, ਪੂਰਨ trns_ਮਾਪ)
{
  // Using a local copy of this array here in case MINIZ_NO_ZLIB_APIS was defined.
  ਸਥਿਰ ਅਚਲ mz_uint s_tdefl_png_ਅੰਕ_probes[11] = { 0, 1, 6, 32,  16, 32, 128, 256,  512, 768, 1500 };
  tdefl_compressor *pComp = (tdefl_compressor *)MZ_MALLOC(ਆਕਾਰ(tdefl_compressor)); tdefl_output_ਬਫਰ ਬਾਹਰਲਾ_buf; ਪੂਰਨ i, y, z = 0; mz_uint32 c; *p_Len_ਬਾਹਰਲਾ = 0; size_t ਅੰਕੜੇ_ਸ਼ੁਰੂ, ਅੰਕੜੇ_ਮਾਪ_3;
  ਜੇ (!pComp) ਵਾਪਸ ਨਿਰਾ;
  MZ_CLEAR_OBJ(ਬਾਹਰਲਾ_buf); ਬਾਹਰਲਾ_buf.m_expandable = MZ_TRUE;
  ਬਾਹਰਲਾ_buf.m_ਸਮਰੱਥਾ = 57+MZ_MAX(64, (1+w*ਅੰਕ_chans)*h);
  ਜੇ (plte_ਮਾਪ > 0)
    ਬਾਹਰਲਾ_buf.m_ਸਮਰੱਥਾ += 12+plte_ਮਾਪ;
  ਜੇ (trns_ਮਾਪ > 0)
    ਬਾਹਰਲਾ_buf.m_ਸਮਰੱਥਾ += 12+trns_ਮਾਪ;
  ਜੇ (ਨਿਰਾ == (ਬਾਹਰਲਾ_buf.m_pBuf = (mz_uint8*)MZ_MALLOC(ਬਾਹਰਲਾ_buf.m_ਸਮਰੱਥਾ))) { MZ_FREE(pComp); ਵਾਪਸ ਨਿਰਾ; }
  // write header
  {
    ਸਥਿਰ ਅਚਲ mz_uint8 chans[] = {0x00, 0x00, 0x04, 0x02, 0x06};

    mz_uint8 pnghdr[33]={ 0x89,0x50,0x4e,0x47,0x0d,0x0a,0x1a,0x0a,
                          0x00,0x00,0x00,0x0d,0x49,0x48,0x44,0x52,
                          0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                          0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

    pnghdr[18] = (mz_uint8)(w>>8);
    pnghdr[19] = (mz_uint8)(w>>0);

    pnghdr[22] = (mz_uint8)(h>>8);
    pnghdr[23] = (mz_uint8)(h>>0);

    ਜੇ (ਅੰਕ_chans == 1 && plte_ਮਾਪ > 0)
      pnghdr[25] = 3;
    ਨਹੀਂਤਾਂ
      pnghdr[25] = (chans[ਅੰਕ_chans]);

    c = (mz_uint32)mz_ਚੱਕਰੀ_ਜਾਂਚ_32(MZ_ਚੱਕਰੀ_ਜਾਂਚ_32_INIT,pnghdr+12,17);
    ਲਈ (i=0; i<4; ++i, c<<=8) ((mz_uint8*)(pnghdr+29))[i] = (mz_uint8)(c>>24);
    ਜੇ (!tdefl_output_ਬਫਰ_putter(pnghdr, ਆਕਾਰ(pnghdr), &ਬਾਹਰਲਾ_buf)) { *p_Len_ਬਾਹਰਲਾ = 0; MZ_FREE(pComp); MZ_FREE(ਬਾਹਰਲਾ_buf.m_pBuf); ਵਾਪਸ ਨਿਰਾ; }
  }
  // write PLTE chunk
  ਜੇ (plte_ਮਾਪ > 0)
  {
    mz_uint8 hdr[8]={0x00,0x00,0x00,0x00,0x50,0x4c,0x54,0x45};

    hdr[0] = (mz_uint8)(plte_ਮਾਪ>>24);
    hdr[1] = (mz_uint8)(plte_ਮਾਪ>>16);
    hdr[2] = (mz_uint8)(plte_ਮਾਪ>> 8);
    hdr[3] = (mz_uint8)(plte_ਮਾਪ>> 0);
    ਜੇ (!tdefl_output_ਬਫਰ_putter(hdr, ਆਕਾਰ(hdr), &ਬਾਹਰਲਾ_buf)) { *p_Len_ਬਾਹਰਲਾ = 0; MZ_FREE(pComp); MZ_FREE(ਬਾਹਰਲਾ_buf.m_pBuf); ਵਾਪਸ ਨਿਰਾ; }
    ਅੰਕੜੇ_ਸ਼ੁਰੂ = ਬਾਹਰਲਾ_buf.m_ਮਾਪ;
    ਜੇ (!tdefl_output_ਬਫਰ_putter(plte, plte_ਮਾਪ, &ਬਾਹਰਲਾ_buf)) { *p_Len_ਬਾਹਰਲਾ = 0; MZ_FREE(pComp); MZ_FREE(ਬਾਹਰਲਾ_buf.m_pBuf); ਵਾਪਸ ਨਿਰਾ; }
    ਜੇ (!tdefl_output_ਬਫਰ_putter("\0\0\0\0", 4, &ਬਾਹਰਲਾ_buf)) { *p_Len_ਬਾਹਰਲਾ = 0; MZ_FREE(pComp); MZ_FREE(ਬਾਹਰਲਾ_buf.m_pBuf); ਵਾਪਸ ਨਿਰਾ; }
    c = (mz_uint32)mz_ਚੱਕਰੀ_ਜਾਂਚ_32(MZ_ਚੱਕਰੀ_ਜਾਂਚ_32_INIT,ਬਾਹਰਲਾ_buf.m_pBuf+ਅੰਕੜੇ_ਸ਼ੁਰੂ-4, plte_ਮਾਪ+4);
    ਲਈ (i=0; i<4; ++i, c<<=8) (ਬਾਹਰਲਾ_buf.m_pBuf+ਬਾਹਰਲਾ_buf.m_ਮਾਪ-4)[i] = (mz_uint8)(c >> 24);
  }
  // write tRNS chunk
  ਜੇ (trns_ਮਾਪ > 0)
  {
    mz_uint8 hdr[8]={0x00,0x00,0x00,0x00,0x74,0x52,0x4E,0x53};

    hdr[0] = (mz_uint8)(trns_ਮਾਪ>>24);
    hdr[1] = (mz_uint8)(trns_ਮਾਪ>>16);
    hdr[2] = (mz_uint8)(trns_ਮਾਪ>> 8);
    hdr[3] = (mz_uint8)(trns_ਮਾਪ>> 0);
    ਜੇ (!tdefl_output_ਬਫਰ_putter(hdr, ਆਕਾਰ(hdr), &ਬਾਹਰਲਾ_buf)) { *p_Len_ਬਾਹਰਲਾ = 0; MZ_FREE(pComp); MZ_FREE(ਬਾਹਰਲਾ_buf.m_pBuf); ਵਾਪਸ ਨਿਰਾ; }
    ਅੰਕੜੇ_ਸ਼ੁਰੂ = ਬਾਹਰਲਾ_buf.m_ਮਾਪ;
    ਜੇ (!tdefl_output_ਬਫਰ_putter(trns, trns_ਮਾਪ, &ਬਾਹਰਲਾ_buf)) { *p_Len_ਬਾਹਰਲਾ = 0; MZ_FREE(pComp); MZ_FREE(ਬਾਹਰਲਾ_buf.m_pBuf); ਵਾਪਸ ਨਿਰਾ; }
    ਜੇ (!tdefl_output_ਬਫਰ_putter("\0\0\0\0", 4, &ਬਾਹਰਲਾ_buf)) { *p_Len_ਬਾਹਰਲਾ = 0; MZ_FREE(pComp); MZ_FREE(ਬਾਹਰਲਾ_buf.m_pBuf); ਵਾਪਸ ਨਿਰਾ; }
    c = (mz_uint32)mz_ਚੱਕਰੀ_ਜਾਂਚ_32(MZ_ਚੱਕਰੀ_ਜਾਂਚ_32_INIT,ਬਾਹਰਲਾ_buf.m_pBuf+ਅੰਕੜੇ_ਸ਼ੁਰੂ-4, trns_ਮਾਪ+4);
    ਲਈ (i=0; i<4; ++i, c<<=8) (ਬਾਹਰਲਾ_buf.m_pBuf+ਬਾਹਰਲਾ_buf.m_ਮਾਪ-4)[i] = (mz_uint8)(c >> 24);
  }
  // write IDAT chunk
  ਜੇ (!tdefl_output_ਬਫਰ_putter("\0\0\0\0\x49\x44\x41\x54", 8, &ਬਾਹਰਲਾ_buf)) { *p_Len_ਬਾਹਰਲਾ = 0; MZ_FREE(pComp); MZ_FREE(ਬਾਹਰਲਾ_buf.m_pBuf); ਵਾਪਸ ਨਿਰਾ; }
  ਅੰਕੜੇ_ਸ਼ੁਰੂ = ਬਾਹਰਲਾ_buf.m_ਮਾਪ;
  // compress image data
  tdefl_init(pComp, tdefl_output_ਬਫਰ_putter, &ਬਾਹਰਲਾ_buf, s_tdefl_png_ਅੰਕ_probes[MZ_MIN(10, level)] | TDEFL_WRITE_ZLIB_ਸਿਰਲੇਖ);
  ਲਈ (y = 0; y < h; ++y) { tdefl_compress_ਬਫਰ(pComp, &z, 1, TDEFL_NO_FLUSH); tdefl_compress_ਬਫਰ(pComp, (mz_uint8*)pImage + (flip ? (h - 1 - y) : y) * bpl, w * ਅੰਕ_chans, TDEFL_NO_FLUSH); }
  ਜੇ (tdefl_compress_ਬਫਰ(pComp, ਨਿਰਾ, 0, TDEFL_ਅੰਤ) != TDEFL_ਸਥਿਤੀ_ਪੂਰਾ) { MZ_FREE(pComp); MZ_FREE(ਬਾਹਰਲਾ_buf.m_pBuf); ਵਾਪਸ ਨਿਰਾ; }
  // write IDAT size
  ਅੰਕੜੇ_ਮਾਪ_3 = ਬਾਹਰਲਾ_buf.m_ਮਾਪ-ਅੰਕੜੇ_ਸ਼ੁਰੂ;
  (ਬਾਹਰਲਾ_buf.m_pBuf+ਅੰਕੜੇ_ਸ਼ੁਰੂ-8)[0] = (mz_uint8)(ਅੰਕੜੇ_ਮਾਪ_3>>24);
  (ਬਾਹਰਲਾ_buf.m_pBuf+ਅੰਕੜੇ_ਸ਼ੁਰੂ-8)[1] = (mz_uint8)(ਅੰਕੜੇ_ਮਾਪ_3>>16);
  (ਬਾਹਰਲਾ_buf.m_pBuf+ਅੰਕੜੇ_ਸ਼ੁਰੂ-8)[2] = (mz_uint8)(ਅੰਕੜੇ_ਮਾਪ_3>> 8);
  (ਬਾਹਰਲਾ_buf.m_pBuf+ਅੰਕੜੇ_ਸ਼ੁਰੂ-8)[3] = (mz_uint8)(ਅੰਕੜੇ_ਮਾਪ_3>> 0);
  // write footer (IDAT CRC-32, followed by IEND chunk)
  ਜੇ (!tdefl_output_ਬਫਰ_putter("\0\0\0\0\0\0\0\0\x49\x45\x4e\x44\xae\x42\x60\x82", 16, &ਬਾਹਰਲਾ_buf)) { *p_Len_ਬਾਹਰਲਾ = 0; MZ_FREE(pComp); MZ_FREE(ਬਾਹਰਲਾ_buf.m_pBuf); ਵਾਪਸ ਨਿਰਾ; }
  c = (mz_uint32)mz_ਚੱਕਰੀ_ਜਾਂਚ_32(MZ_ਚੱਕਰੀ_ਜਾਂਚ_32_INIT,ਬਾਹਰਲਾ_buf.m_pBuf+ਅੰਕੜੇ_ਸ਼ੁਰੂ-4, ਅੰਕੜੇ_ਮਾਪ_3+4);
  ਲਈ (i=0; i<4; ++i, c<<=8) (ਬਾਹਰਲਾ_buf.m_pBuf+ਬਾਹਰਲਾ_buf.m_ਮਾਪ-16)[i] = (mz_uint8)(c >> 24);
  // compute final size of file, grab compressed data buffer and return
  *p_Len_ਬਾਹਰਲਾ = ਬਾਹਰਲਾ_buf.m_ਮਾਪ;
  MZ_FREE(pComp);
  ਵਾਪਸ ਬਾਹਰਲਾ_buf.m_pBuf;
}
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_SDL_NOUNUSED
MINIZ_STATIC ਖਾਲੀ *tdefl_write_image_ਮੰਜ਼ਿਲ_png_file_ਵਿੱਚ_ਸਮ੍ਰਿਤੀ(ਅਚਲ ਖਾਲੀ *pImage, ਪੂਰਨ w, ਪੂਰਨ h, ਪੂਰਨ ਅੰਕ_chans, ਪੂਰਨ bpl, size_t *p_Len_ਬਾਹਰਲਾ)
{
  // Level 6 corresponds to TDEFL_DEFAULT_MAX_PROBES or MZ_DEFAULT_LEVEL (but we can't depend on MZ_DEFAULT_LEVEL being available in case the zlib API's where #defined out)
  ਵਾਪਸ tdefl_write_image_ਮੰਜ਼ਿਲ_png_file_ਵਿੱਚ_ਸਮ੍ਰਿਤੀ_ex(pImage, w, h, ਅੰਕ_chans, bpl, p_Len_ਬਾਹਰਲਾ, 6, MZ_FALSE, ਨਿਰਾ, 0, ਨਿਰਾ, 0);
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _MSC_VER
#ਹਦਾਇਤ warning (ਕੱਢੋ)
#ਜੇ_ਅੰਤ
#ਜੇ_ਅੰਤ /*#ifndef MINIZ_NO_DEFLATE_APIS*/

// ------------------- .ZIP archive reading

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_ARCHIVE_APIS

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_STDIO
  #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FILE ਖਾਲੀ *
#ਨਹੀਂਤਾਂ
  #ਅਨ੍ਤਰ੍ਭਾਵ <stdio.h>
  #ਅਨ੍ਤਰ੍ਭਾਵ <sys/stat.h>

  #ਜੇ defined(_MSC_VER) || defined(__MINGW64__)
    ਸਥਿਰ FILE *mz_fopen(ਅਚਲ ਅੱਖਰ *pFilename, ਅਚਲ ਅੱਖਰ *p_ਬਹੁਲਕ)
    {
      FILE* pFile = ਨਿਰਾ;
      fopen_s(&pFile, pFilename, p_ਬਹੁਲਕ);
      ਵਾਪਸ pFile;
    }
    ਸਥਿਰ FILE *mz_freopen(ਅਚਲ ਅੱਖਰ *p_ਰਸਤਾ, ਅਚਲ ਅੱਖਰ *p_ਬਹੁਲਕ, FILE *p_ਧਾਰਾ)
    {
      FILE* pFile = ਨਿਰਾ;
      ਜੇ (freopen_s(&pFile, p_ਰਸਤਾ, p_ਬਹੁਲਕ, p_ਧਾਰਾ))
        ਵਾਪਸ ਨਿਰਾ;
      ਵਾਪਸ pFile;
    }
    #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_ਸਮਾਂ
      #ਅਨ੍ਤਰ੍ਭਾਵ <sys/utime.h>
    #ਜੇ_ਅੰਤ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FILE FILE
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FOPEN mz_fopen
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FCLOSE fclose
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FREAD fread
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FWRITE fwrite
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FTELL64 _ftelli64
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FSEEK64 _fseeki64
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FILE_STAT_STRUCT _stat
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FILE_STAT _stat
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FFLUSH fflush
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FREOPEN mz_freopen
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_DELETE_FILE remove
  #ਜਾਂਜੇ defined(__MINGW32__)
    #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_ਸਮਾਂ
      #ਅਨ੍ਤਰ੍ਭਾਵ <sys/utime.h>
    #ਜੇ_ਅੰਤ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FILE FILE
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FOPEN(f, m) fopen(f, m)
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FCLOSE fclose
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FREAD fread
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FWRITE fwrite
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FTELL64 ftello64
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FSEEK64 fseeko64
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FILE_STAT_STRUCT _stat
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FILE_STAT _stat
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FFLUSH fflush
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FREOPEN(f, m, s) freopen(f, m, s)
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_DELETE_FILE remove
  #ਜਾਂਜੇ defined(__TINYC__)
    #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_ਸਮਾਂ
      #ਅਨ੍ਤਰ੍ਭਾਵ <sys/utime.h>
    #ਜੇ_ਅੰਤ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FILE FILE
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FOPEN(f, m) fopen(f, m)
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FCLOSE fclose
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FREAD fread
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FWRITE fwrite
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FTELL64 ftell
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FSEEK64 fseek
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FILE_STAT_STRUCT stat
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FILE_STAT stat
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FFLUSH fflush
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FREOPEN(f, m, s) freopen(f, m, s)
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_DELETE_FILE remove
  #ਜਾਂਜੇ defined(__GNUC__) && LARGEFILE64_ਸਰੋਤ
    #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_ਸਮਾਂ
      #ਅਨ੍ਤਰ੍ਭਾਵ <utime.h>
    #ਜੇ_ਅੰਤ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FILE FILE
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FOPEN(f, m) fopen64(f, m)
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FCLOSE fclose
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FREAD fread
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FWRITE fwrite
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FTELL64 ftello64
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FSEEK64 fseeko64
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FILE_STAT_STRUCT stat64
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FILE_STAT stat64
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FFLUSH fflush
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FREOPEN(p, m, s) freopen64(p, m, s)
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_DELETE_FILE remove
  #ਨਹੀਂਤਾਂ
    #ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_ਸਮਾਂ
      #ਅਨ੍ਤਰ੍ਭਾਵ <utime.h>
    #ਜੇ_ਅੰਤ
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FILE FILE
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FOPEN(f, m) fopen(f, m)
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FCLOSE fclose
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FREAD fread
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FWRITE fwrite
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FTELL64 ftello
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FSEEK64 fseeko
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FILE_STAT_STRUCT stat
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FILE_STAT stat
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FFLUSH fflush
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_FREOPEN(f, m, s) freopen(f, m, s)
    #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_DELETE_FILE remove
  #ਜੇ_ਅੰਤ // #ifdef _MSC_VER
#ਜੇ_ਅੰਤ // #ifdef MINIZ_NO_STDIO

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_TOLOWER(c) ((((c) >= 'A') && ((c) <= 'Z')) ? ((c) - 'A' + 'a') : (c))

// Various ZIP archive enums. To completely avoid cross platform compiler alignment and platform endian issues, miniz.c doesn't use structs for any of this stuff.
ਗਿਣਤੀ
{
  // ZIP archive identifiers and record sizes
  MZ_ZIP_ਸਿਰਾ_ਦਾ_CENTRAL_DIR_ਸਿਰਲੇਖ_SIG = 0x06054b50, MZ_ZIP_CENTRAL_DIR_ਸਿਰਲੇਖ_SIG = 0x02014b50, MZ_ZIP_LOCAL_DIR_ਸਿਰਲੇਖ_SIG = 0x04034b50,
  MZ_ZIP_LOCAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ = 30, MZ_ZIP_CENTRAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ = 46, MZ_ZIP_ਸਿਰਾ_ਦਾ_CENTRAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ = 22,
  // Central directory header record offsets
  MZ_ZIP_CDH_SIG_OFS = 0, MZ_ZIP_CDH_ਸੰਸਕਰਣ_MADE_BY_OFS = 4, MZ_ZIP_CDH_ਸੰਸਕਰਣ_NEEDED_OFS = 6, MZ_ZIP_CDH_ਦੋਆਧਾਰੀ_ਅੰਕ_FLAG_OFS = 8,
  MZ_ZIP_CDH_ਵਿਧੀ_OFS = 10, MZ_ZIP_CDH_FILE_ਸਮਾਂ_OFS = 12, MZ_ZIP_CDH_FILE_DATE_OFS = 14, MZ_ZIP_CDH_ਚੱਕਰੀ_ਜਾਂਚ_32_OFS = 16,
  MZ_ZIP_CDH_COMPRESSED_ਮਾਪ_OFS = 20, MZ_ZIP_CDH_DECOMPRESSED_ਮਾਪ_OFS = 24, MZ_ZIP_CDH_FILENAME_LEN_OFS = 28, MZ_ZIP_CDH_EXTRA_LEN_OFS = 30,
  MZ_ZIP_CDH_COMMENT_LEN_OFS = 32, MZ_ZIP_CDH_DISK_ਸ਼ੁਰੂ_OFS = 34, MZ_ZIP_CDH_ਅੰਦਰੂਨੀ_ATTR_OFS = 36, MZ_ZIP_CDH_EXTERNAL_ATTR_OFS = 38, MZ_ZIP_CDH_LOCAL_ਸਿਰਲੇਖ_OFS = 42,
  // Local directory header offsets
  MZ_ZIP_LDH_SIG_OFS = 0, MZ_ZIP_LDH_ਸੰਸਕਰਣ_NEEDED_OFS = 4, MZ_ZIP_LDH_ਦੋਆਧਾਰੀ_ਅੰਕ_FLAG_OFS = 6, MZ_ZIP_LDH_ਵਿਧੀ_OFS = 8, MZ_ZIP_LDH_FILE_ਸਮਾਂ_OFS = 10,
  MZ_ZIP_LDH_FILE_DATE_OFS = 12, MZ_ZIP_LDH_ਚੱਕਰੀ_ਜਾਂਚ_32_OFS = 14, MZ_ZIP_LDH_COMPRESSED_ਮਾਪ_OFS = 18, MZ_ZIP_LDH_DECOMPRESSED_ਮਾਪ_OFS = 22,
  MZ_ZIP_LDH_FILENAME_LEN_OFS = 26, MZ_ZIP_LDH_EXTRA_LEN_OFS = 28,
  // End of central directory offsets
  MZ_ZIP_ECDH_SIG_OFS = 0, MZ_ZIP_ECDH_ਅੰਕ_THIS_DISK_OFS = 4, MZ_ZIP_ECDH_ਅੰਕ_DISK_CDIR_OFS = 6, MZ_ZIP_ECDH_CDIR_ਅੰਕ_ENTRIES_ON_DISK_OFS = 8,
  MZ_ZIP_ECDH_CDIR_ਕੁੱਲ_ENTRIES_OFS = 10, MZ_ZIP_ECDH_CDIR_ਮਾਪ_OFS = 12, MZ_ZIP_ECDH_CDIR_OFS_OFS = 16, MZ_ZIP_ECDH_COMMENT_ਮਾਪ_OFS = 20,
};

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
  ਖਾਲੀ *m_p;
  size_t m_ਮਾਪ, m_ਸਮਰੱਥਾ;
  mz_uint m_element_ਮਾਪ;
} mz_zip_array;

ਬਣਤਰ mz_zip_ਅੰਦਰੂਨੀ_state_ਟੈਗ
{
  mz_zip_array m_central_dir;
  mz_zip_array m_central_dir_offsets;
  mz_zip_array m_sorted_central_dir_offsets;
  MZ_FILE *m_pFile;
  ਖਾਲੀ *m_pMem;
  size_t m_mem_ਮਾਪ;
  size_t m_mem_ਸਮਰੱਥਾ;
};

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_ZIP_ARRAY_ਸੈੱਟ_ELEMENT_ਮਾਪ(array_ptr, element_ਮਾਪ) (array_ptr)->m_element_ਮਾਪ = element_ਮਾਪ
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_ZIP_ARRAY_ELEMENT(array_ptr, element_type, ਸੂਚਕਾਂਕ) ((element_type *)((array_ptr)->m_p))[ਸੂਚਕਾਂਕ]

ਸਥਿਰ MZ_FORCEINLINE ਖਾਲੀ mz_zip_array_clear(mz_zip_archive *pZip, mz_zip_array *pArray)
{
  pZip->m_pFree(pZip->m_pAlloc_opaque, pArray->m_p);
  memset(pArray, 0, ਆਕਾਰ(mz_zip_array));
}

ਸਥਿਰ mz_bool mz_zip_array_ensure_ਸਮਰੱਥਾ(mz_zip_archive *pZip, mz_zip_array *pArray, size_t min_new_ਸਮਰੱਥਾ, mz_uint growing)
{
  ਖਾਲੀ *pNew_p; size_t new_ਸਮਰੱਥਾ = min_new_ਸਮਰੱਥਾ; MZ_ASSERT(pArray->m_element_ਮਾਪ); ਜੇ (pArray->m_ਸਮਰੱਥਾ >= min_new_ਸਮਰੱਥਾ) ਵਾਪਸ MZ_TRUE;
  ਜੇ (growing) { new_ਸਮਰੱਥਾ = MZ_MAX(1, pArray->m_ਸਮਰੱਥਾ); ਜਦੋਂ (new_ਸਮਰੱਥਾ < min_new_ਸਮਰੱਥਾ) new_ਸਮਰੱਥਾ *= 2; }
  ਜੇ (ਨਿਰਾ == (pNew_p = pZip->m_pRealloc(pZip->m_pAlloc_opaque, pArray->m_p, pArray->m_element_ਮਾਪ, new_ਸਮਰੱਥਾ))) ਵਾਪਸ MZ_FALSE;
  pArray->m_p = pNew_p; pArray->m_ਸਮਰੱਥਾ = new_ਸਮਰੱਥਾ;
  ਵਾਪਸ MZ_TRUE;
}

ਸਥਿਰ MZ_FORCEINLINE mz_bool mz_zip_array_reserve(mz_zip_archive *pZip, mz_zip_array *pArray, size_t new_ਸਮਰੱਥਾ, mz_uint growing)
{
  ਜੇ (new_ਸਮਰੱਥਾ > pArray->m_ਸਮਰੱਥਾ) { ਜੇ (!mz_zip_array_ensure_ਸਮਰੱਥਾ(pZip, pArray, new_ਸਮਰੱਥਾ, growing)) ਵਾਪਸ MZ_FALSE; }
  ਵਾਪਸ MZ_TRUE;
}

ਸਥਿਰ MZ_FORCEINLINE mz_bool mz_zip_array_resize(mz_zip_archive *pZip, mz_zip_array *pArray, size_t new_ਮਾਪ, mz_uint growing)
{
  ਜੇ (new_ਮਾਪ > pArray->m_ਸਮਰੱਥਾ) { ਜੇ (!mz_zip_array_ensure_ਸਮਰੱਥਾ(pZip, pArray, new_ਮਾਪ, growing)) ਵਾਪਸ MZ_FALSE; }
  pArray->m_ਮਾਪ = new_ਮਾਪ;
  ਵਾਪਸ MZ_TRUE;
}

ਸਥਿਰ MZ_FORCEINLINE mz_bool mz_zip_array_ensure_ਗੁੰਜਾਇਸ਼(mz_zip_archive *pZip, mz_zip_array *pArray, size_t n)
{
  ਵਾਪਸ mz_zip_array_reserve(pZip, pArray, pArray->m_ਮਾਪ + n, MZ_TRUE);
}

ਸਥਿਰ MZ_FORCEINLINE mz_bool mz_zip_array_ਧੱਕੋ_ਪਿੱਠ(mz_zip_archive *pZip, mz_zip_array *pArray, ਅਚਲ ਖਾਲੀ *pElements, size_t n)
{
  size_t orig_ਮਾਪ = pArray->m_ਮਾਪ; ਜੇ (!mz_zip_array_resize(pZip, pArray, orig_ਮਾਪ + n, MZ_TRUE)) ਵਾਪਸ MZ_FALSE;
  ਸਮ੍ਰਿਤੀ_ਨਕਲ((mz_uint8*)pArray->m_p + orig_ਮਾਪ * pArray->m_element_ਮਾਪ, pElements, n * pArray->m_element_ਮਾਪ);
  ਵਾਪਸ MZ_TRUE;
}

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_ਸਮਾਂ
ਸਥਿਰ ਸਮਾਂ_t mz_zip_dos_ਮੰਜ਼ਿਲ_ਸਮਾਂ_t(ਪੂਰਨ dos_ਸਮਾਂ, ਪੂਰਨ dos_date)
{
  ਬਣਤਰ tm tm;
  memset(&tm, 0, ਆਕਾਰ(tm)); tm.tm_isdst = -1;
  tm.tm_year = ((dos_date >> 9) & 127) + 1980 - 1900; tm.tm_mon = ((dos_date >> 5) & 15) - 1; tm.tm_mday = dos_date & 31;
  tm.tm_hour = (dos_ਸਮਾਂ >> 11) & 31; tm.tm_min = (dos_ਸਮਾਂ >> 5) & 63; tm.tm_sec = (dos_ਸਮਾਂ << 1) & 62;
  ਵਾਪਸ mktime(&tm);
}

ਸਥਿਰ ਖਾਲੀ mz_zip_ਸਮਾਂ_ਮੰਜ਼ਿਲ_dos_ਸਮਾਂ(ਸਮਾਂ_t ਸਮਾਂ, mz_uint16 *p_DOS_ਸਮਾਂ, mz_uint16 *pDOS_date)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _MSC_VER
  ਬਣਤਰ tm tm_struct;
  ਬਣਤਰ tm *tm = &tm_struct;
  errno_t err = localtime_s(tm, &ਸਮਾਂ);
  ਜੇ (err)
  {
    *pDOS_date = 0; *p_DOS_ਸਮਾਂ = 0;
    ਵਾਪਸ;
  }
#ਨਹੀਂਤਾਂ
  ਬਣਤਰ tm *tm = localtime(&ਸਮਾਂ);
#ਜੇ_ਅੰਤ
  *p_DOS_ਸਮਾਂ = (mz_uint16)(((tm->tm_hour) << 11) + ((tm->tm_min) << 5) + ((tm->tm_sec) >> 1));
  *pDOS_date = (mz_uint16)(((tm->tm_year + 1900 - 1980) << 9) + ((tm->tm_mon + 1) << 5) + tm->tm_mday);
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_STDIO
ਸਥਿਰ mz_bool mz_zip_get_file_modified_ਸਮਾਂ(ਅਚਲ ਅੱਖਰ *pFilename, mz_uint16 *p_DOS_ਸਮਾਂ, mz_uint16 *pDOS_date)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_ਸਮਾਂ
  (ਖਾਲੀ)pFilename; *pDOS_date = *p_DOS_ਸਮਾਂ = 0;
#ਨਹੀਂਤਾਂ
  ਬਣਤਰ MZ_FILE_STAT_STRUCT file_stat;
  // On Linux with x86 glibc, this call will fail on large files (>= 0x80000000 bytes) unless you compiled with _LARGEFILE64_SOURCE. Argh.
  ਜੇ (MZ_FILE_STAT(pFilename, &file_stat) != 0)
    ਵਾਪਸ MZ_FALSE;
  mz_zip_ਸਮਾਂ_ਮੰਜ਼ਿਲ_dos_ਸਮਾਂ(file_stat.st_mtime, p_DOS_ਸਮਾਂ, pDOS_date);
#ਜੇ_ਅੰਤ // #ifdef MINIZ_NO_TIME
  ਵਾਪਸ MZ_TRUE;
}

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_ਸਮਾਂ
ਸਥਿਰ mz_bool mz_zip_ਸੈੱਟ_file_times(ਅਚਲ ਅੱਖਰ *pFilename, ਸਮਾਂ_t access_ਸਮਾਂ, ਸਮਾਂ_t modified_ਸਮਾਂ)
{
  ਬਣਤਰ utimbuf t; t.actime = access_ਸਮਾਂ; t.modtime = modified_ਸਮਾਂ;
  ਵਾਪਸ !utime(pFilename, &t);
}
#ਜੇ_ਅੰਤ // #ifndef MINIZ_NO_TIME
#ਜੇ_ਅੰਤ // #ifndef MINIZ_NO_STDIO

ਸਥਿਰ mz_bool mz_zip_reader_init_ਅੰਦਰੂਨੀ(mz_zip_archive *pZip, mz_uint32 flags)
{
  (ਖਾਲੀ)flags;
  ਜੇ ((!pZip) || (pZip->m_pState) || (pZip->m_zip_ਬਹੁਲਕ != MZ_ZIP_ਬਹੁਲਕ_INVALID))
    ਵਾਪਸ MZ_FALSE;

  ਜੇ (!pZip->m_pAlloc) pZip->m_pAlloc = def_alloc_func;
  ਜੇ (!pZip->m_pFree) pZip->m_pFree = def_free_func;
  ਜੇ (!pZip->m_pRealloc) pZip->m_pRealloc = def_realloc_func;

  pZip->m_zip_ਬਹੁਲਕ = MZ_ZIP_ਬਹੁਲਕ_READING;
  pZip->m_archive_ਮਾਪ = 0;
  pZip->m_central_directory_file_ofs = 0;
  pZip->m_ਕੁੱਲ_files = 0;

  ਜੇ (ਨਿਰਾ == (pZip->m_pState = (mz_zip_ਅੰਦਰੂਨੀ_state *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, ਆਕਾਰ(mz_zip_ਅੰਦਰੂਨੀ_state))))
    ਵਾਪਸ MZ_FALSE;
  memset(pZip->m_pState, 0, ਆਕਾਰ(mz_zip_ਅੰਦਰੂਨੀ_state));
  MZ_ZIP_ARRAY_ਸੈੱਟ_ELEMENT_ਮਾਪ(&pZip->m_pState->m_central_dir, ਆਕਾਰ(mz_uint8));
  MZ_ZIP_ARRAY_ਸੈੱਟ_ELEMENT_ਮਾਪ(&pZip->m_pState->m_central_dir_offsets, ਆਕਾਰ(mz_uint32));
  MZ_ZIP_ARRAY_ਸੈੱਟ_ELEMENT_ਮਾਪ(&pZip->m_pState->m_sorted_central_dir_offsets, ਆਕਾਰ(mz_uint32));
  ਵਾਪਸ MZ_TRUE;
}

ਸਥਿਰ MZ_FORCEINLINE mz_bool mz_zip_reader_filename_less(ਅਚਲ mz_zip_array *pCentral_dir_array, ਅਚਲ mz_zip_array *pCentral_dir_offsets, mz_uint l_ਸੂਚਕਾਂਕ, mz_uint r_ਸੂਚਕਾਂਕ)
{
  ਅਚਲ mz_uint8 *pL = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, l_ਸੂਚਕਾਂਕ)), *pE;
  ਅਚਲ mz_uint8 *pR = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, r_ਸੂਚਕਾਂਕ));
  mz_uint l_len = MZ_READ_LE16(pL + MZ_ZIP_CDH_FILENAME_LEN_OFS), r_len = MZ_READ_LE16(pR + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  mz_uint8 l = 0, r = 0;
  pL += MZ_ZIP_CENTRAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ; pR += MZ_ZIP_CENTRAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ;
  pE = pL + MZ_MIN(l_len, r_len);
  ਜਦੋਂ (pL < pE)
  {
    ਜੇ ((l = MZ_TOLOWER(*pL)) != (r = MZ_TOLOWER(*pR)))
      ਰੋਕੋ;
    pL++; pR++;
  }
  ਵਾਪਸ (pL == pE) ? (l_len < r_len) : (l < r);
}

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_ਅਦਲਾ_ਬਦਲੀ_UINT32(a, b) ਕਰੋ { mz_uint32 t = a; a = b; b = t; } MZ_MACRO_ਸਿਰਾ

// Heap sort of lowercased filenames, used to help accelerate plain central directory searches by mz_zip_reader_locate_file(). (Could also use qsort(), but it could allocate memory.)
ਸਥਿਰ ਖਾਲੀ mz_zip_reader_ਛਾਂਟੋ_central_dir_offsets_by_filename(mz_zip_archive *pZip)
{
  mz_zip_ਅੰਦਰੂਨੀ_state *pState = pZip->m_pState;
  ਅਚਲ mz_zip_array *pCentral_dir_offsets = &pState->m_central_dir_offsets;
  ਅਚਲ mz_zip_array *pCentral_dir = &pState->m_central_dir;
  mz_uint32 *pIndices = &MZ_ZIP_ARRAY_ELEMENT(&pState->m_sorted_central_dir_offsets, mz_uint32, 0);
  ਅਚਲ ਪੂਰਨ ਮਾਪ = pZip->m_ਕੁੱਲ_files;
  ਪੂਰਨ ਸ਼ੁਰੂ = (ਮਾਪ - 2) >> 1, ਸਿਰਾ;
  ਜਦੋਂ (ਸ਼ੁਰੂ >= 0)
  {
    ਪੂਰਨ ਬੱਚਾ, ਜੜ੍ਹ = ਸ਼ੁਰੂ;
    ਲਈ ( ; ; )
    {
      ਜੇ ((ਬੱਚਾ = (ਜੜ੍ਹ << 1) + 1) >= ਮਾਪ)
        ਰੋਕੋ;
      ਬੱਚਾ += (((ਬੱਚਾ + 1) < ਮਾਪ) && (mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[ਬੱਚਾ], pIndices[ਬੱਚਾ + 1])));
      ਜੇ (!mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[ਜੜ੍ਹ], pIndices[ਬੱਚਾ]))
        ਰੋਕੋ;
      MZ_ਅਦਲਾ_ਬਦਲੀ_UINT32(pIndices[ਜੜ੍ਹ], pIndices[ਬੱਚਾ]); ਜੜ੍ਹ = ਬੱਚਾ;
    }
    ਸ਼ੁਰੂ--;
  }

  ਸਿਰਾ = ਮਾਪ - 1;
  ਜਦੋਂ (ਸਿਰਾ > 0)
  {
    ਪੂਰਨ ਬੱਚਾ, ਜੜ੍ਹ = 0;
    MZ_ਅਦਲਾ_ਬਦਲੀ_UINT32(pIndices[ਸਿਰਾ], pIndices[0]);
    ਲਈ ( ; ; )
    {
      ਜੇ ((ਬੱਚਾ = (ਜੜ੍ਹ << 1) + 1) >= ਸਿਰਾ)
        ਰੋਕੋ;
      ਬੱਚਾ += (((ਬੱਚਾ + 1) < ਸਿਰਾ) && mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[ਬੱਚਾ], pIndices[ਬੱਚਾ + 1]));
      ਜੇ (!mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[ਜੜ੍ਹ], pIndices[ਬੱਚਾ]))
        ਰੋਕੋ;
      MZ_ਅਦਲਾ_ਬਦਲੀ_UINT32(pIndices[ਜੜ੍ਹ], pIndices[ਬੱਚਾ]); ਜੜ੍ਹ = ਬੱਚਾ;
    }
    ਸਿਰਾ--;
  }
}

ਸਥਿਰ mz_bool mz_zip_reader_read_central_dir(mz_zip_archive *pZip, mz_uint32 flags)
{
  mz_uint cdir_ਮਾਪ, ਅੰਕ_this_disk, cdir_disk_ਸੂਚਕਾਂਕ;
  mz_uint64 cdir_ofs;
  mz_int64 cur_file_ofs;
  ਅਚਲ mz_uint8 *p;
  mz_uint32 buf_u32[4096 / ਆਕਾਰ(mz_uint32)]; mz_uint8 *pBuf = (mz_uint8 *)buf_u32;
  mz_bool ਛਾਂਟੋ_central_dir = ((flags & MZ_ZIP_FLAG_DO_NOT_ਛਾਂਟੋ_CENTRAL_DIRECTORY) == 0);
  // Basic sanity checks - reject files which are too small, and check the first 4 bytes of the file to make sure a local header is there.
  ਜੇ (pZip->m_archive_ਮਾਪ < MZ_ZIP_ਸਿਰਾ_ਦਾ_CENTRAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ)
    ਵਾਪਸ MZ_FALSE;
  // Find the end of central directory record by scanning the file from the end towards the beginning.
  cur_file_ofs = MZ_MAX((mz_int64)pZip->m_archive_ਮਾਪ - (mz_int64)ਆਕਾਰ(buf_u32), 0);
  ਲਈ ( ; ; )
  {
    ਪੂਰਨ i, n = (ਪੂਰਨ)MZ_MIN(ਆਕਾਰ(buf_u32), pZip->m_archive_ਮਾਪ - cur_file_ofs);
    ਜੇ (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, n) != (mz_uint)n)
      ਵਾਪਸ MZ_FALSE;
    ਲਈ (i = n - 4; i >= 0; --i)
      ਜੇ (MZ_READ_LE32(pBuf + i) == MZ_ZIP_ਸਿਰਾ_ਦਾ_CENTRAL_DIR_ਸਿਰਲੇਖ_SIG)
        ਰੋਕੋ;
    ਜੇ (i >= 0)
    {
      cur_file_ofs += i;
      ਰੋਕੋ;
    }
    ਜੇ ((!cur_file_ofs) || ((pZip->m_archive_ਮਾਪ - cur_file_ofs) >= (0xFFFF + MZ_ZIP_ਸਿਰਾ_ਦਾ_CENTRAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ)))
      ਵਾਪਸ MZ_FALSE;
    cur_file_ofs = MZ_MAX(cur_file_ofs - (ਆਕਾਰ(buf_u32) - 3), 0);
  }
  // Read and verify the end of central directory record.
  ਜੇ (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, MZ_ZIP_ਸਿਰਾ_ਦਾ_CENTRAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ) != MZ_ZIP_ਸਿਰਾ_ਦਾ_CENTRAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ)
    ਵਾਪਸ MZ_FALSE;
  ਜੇ ((MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_SIG_OFS) != MZ_ZIP_ਸਿਰਾ_ਦਾ_CENTRAL_DIR_ਸਿਰਲੇਖ_SIG) ||
      ((pZip->m_ਕੁੱਲ_files = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_CDIR_ਕੁੱਲ_ENTRIES_OFS)) != MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_CDIR_ਅੰਕ_ENTRIES_ON_DISK_OFS)))
    ਵਾਪਸ MZ_FALSE;

  ਅੰਕ_this_disk = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_ਅੰਕ_THIS_DISK_OFS);
  cdir_disk_ਸੂਚਕਾਂਕ = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_ਅੰਕ_DISK_CDIR_OFS);
  ਜੇ (((ਅੰਕ_this_disk | cdir_disk_ਸੂਚਕਾਂਕ) != 0) && ((ਅੰਕ_this_disk != 1) || (cdir_disk_ਸੂਚਕਾਂਕ != 1)))
    ਵਾਪਸ MZ_FALSE;

  ਜੇ ((cdir_ਮਾਪ = MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_CDIR_ਮਾਪ_OFS)) < pZip->m_ਕੁੱਲ_files * MZ_ZIP_CENTRAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ)
    ਵਾਪਸ MZ_FALSE;

  cdir_ofs = MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_CDIR_OFS_OFS);
  ਜੇ ((cdir_ofs + (mz_uint64)cdir_ਮਾਪ) > pZip->m_archive_ਮਾਪ)
    ਵਾਪਸ MZ_FALSE;

  pZip->m_central_directory_file_ofs = cdir_ofs;

  ਜੇ (pZip->m_ਕੁੱਲ_files)
  {
     mz_uint i, n;

    // Read the entire central directory into a heap block, and allocate another heap block to hold the unsorted central dir file record offsets, and another to hold the sorted indices.
    ਜੇ ((!mz_zip_array_resize(pZip, &pZip->m_pState->m_central_dir, cdir_ਮਾਪ, MZ_FALSE)) ||
        (!mz_zip_array_resize(pZip, &pZip->m_pState->m_central_dir_offsets, pZip->m_ਕੁੱਲ_files, MZ_FALSE)))
      ਵਾਪਸ MZ_FALSE;

    ਜੇ (ਛਾਂਟੋ_central_dir)
    {
      ਜੇ (!mz_zip_array_resize(pZip, &pZip->m_pState->m_sorted_central_dir_offsets, pZip->m_ਕੁੱਲ_files, MZ_FALSE))
        ਵਾਪਸ MZ_FALSE;
    }

    ਜੇ (pZip->m_pRead(pZip->m_pIO_opaque, cdir_ofs, pZip->m_pState->m_central_dir.m_p, cdir_ਮਾਪ) != cdir_ਮਾਪ)
      ਵਾਪਸ MZ_FALSE;

    // Now create an index into the central directory file records, do some basic sanity checking on each record, and check for zip64 entries (which are not yet supported).
    p = (ਅਚਲ mz_uint8 *)pZip->m_pState->m_central_dir.m_p;
    ਲਈ (n = cdir_ਮਾਪ, i = 0; i < pZip->m_ਕੁੱਲ_files; ++i)
    {
      mz_uint ਕੁੱਲ_ਸਿਰਲੇਖ_ਮਾਪ, comp_ਮਾਪ, decomp_ਮਾਪ, disk_ਸੂਚਕਾਂਕ;
      ਜੇ ((n < MZ_ZIP_CENTRAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ) || (MZ_READ_LE32(p) != MZ_ZIP_CENTRAL_DIR_ਸਿਰਲੇਖ_SIG))
        ਵਾਪਸ MZ_FALSE;
      MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, i) = (mz_uint32)(p - (ਅਚਲ mz_uint8 *)pZip->m_pState->m_central_dir.m_p);
      ਜੇ (ਛਾਂਟੋ_central_dir)
        MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_sorted_central_dir_offsets, mz_uint32, i) = i;
      comp_ਮਾਪ = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_ਮਾਪ_OFS);
      decomp_ਮਾਪ = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_ਮਾਪ_OFS);
      ਜੇ (((!MZ_READ_LE32(p + MZ_ZIP_CDH_ਵਿਧੀ_OFS)) && (decomp_ਮਾਪ != comp_ਮਾਪ)) || (decomp_ਮਾਪ && !comp_ਮਾਪ) || (decomp_ਮਾਪ == 0xFFFFFFFF) || (comp_ਮਾਪ == 0xFFFFFFFF))
        ਵਾਪਸ MZ_FALSE;
      disk_ਸੂਚਕਾਂਕ = MZ_READ_LE16(p + MZ_ZIP_CDH_DISK_ਸ਼ੁਰੂ_OFS);
      ਜੇ ((disk_ਸੂਚਕਾਂਕ != ਅੰਕ_this_disk) && (disk_ਸੂਚਕਾਂਕ != 1))
        ਵਾਪਸ MZ_FALSE;
      ਜੇ (((mz_uint64)MZ_READ_LE32(p + MZ_ZIP_CDH_LOCAL_ਸਿਰਲੇਖ_OFS) + MZ_ZIP_LOCAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ + comp_ਮਾਪ) > pZip->m_archive_ਮਾਪ)
        ਵਾਪਸ MZ_FALSE;
      ਜੇ ((ਕੁੱਲ_ਸਿਰਲੇਖ_ਮਾਪ = MZ_ZIP_CENTRAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ + MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_EXTRA_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_COMMENT_LEN_OFS)) > n)
        ਵਾਪਸ MZ_FALSE;
      n -= ਕੁੱਲ_ਸਿਰਲੇਖ_ਮਾਪ; p += ਕੁੱਲ_ਸਿਰਲੇਖ_ਮਾਪ;
    }
  }

  ਜੇ (ਛਾਂਟੋ_central_dir)
    mz_zip_reader_ਛਾਂਟੋ_central_dir_offsets_by_filename(pZip);

  ਵਾਪਸ MZ_TRUE;
}

mz_bool mz_zip_reader_init(mz_zip_archive *pZip, mz_uint64 ਮਾਪ, mz_uint32 flags)
{
  ਜੇ ((!pZip) || (!pZip->m_pRead))
    ਵਾਪਸ MZ_FALSE;
  ਜੇ (!mz_zip_reader_init_ਅੰਦਰੂਨੀ(pZip, flags))
    ਵਾਪਸ MZ_FALSE;
  pZip->m_archive_ਮਾਪ = ਮਾਪ;
  ਜੇ (!mz_zip_reader_read_central_dir(pZip, flags))
  {
    mz_zip_reader_ਸਿਰਾ(pZip);
    ਵਾਪਸ MZ_FALSE;
  }
  ਵਾਪਸ MZ_TRUE;
}

ਸਥਿਰ size_t mz_zip_mem_read_func(ਖਾਲੀ *pOpaque, mz_uint64 file_ofs, ਖਾਲੀ *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  size_t s = (file_ofs >= pZip->m_archive_ਮਾਪ) ? 0 : (size_t)MZ_MIN(pZip->m_archive_ਮਾਪ - file_ofs, n);
  ਸਮ੍ਰਿਤੀ_ਨਕਲ(pBuf, (ਅਚਲ mz_uint8 *)pZip->m_pState->m_pMem + file_ofs, s);
  ਵਾਪਸ s;
}

mz_bool mz_zip_reader_init_mem(mz_zip_archive *pZip, ਅਚਲ ਖਾਲੀ *pMem, size_t ਮਾਪ, mz_uint32 flags)
{
  ਜੇ (!mz_zip_reader_init_ਅੰਦਰੂਨੀ(pZip, flags))
    ਵਾਪਸ MZ_FALSE;
  pZip->m_archive_ਮਾਪ = ਮਾਪ;
  pZip->m_pRead = mz_zip_mem_read_func;
  pZip->m_pIO_opaque = pZip;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
  pZip->m_pState->m_pMem = const_cast<ਖਾਲੀ *>(pMem);
#ਨਹੀਂਤਾਂ
  pZip->m_pState->m_pMem = (ਖਾਲੀ *)pMem;
#ਜੇ_ਅੰਤ
  pZip->m_pState->m_mem_ਮਾਪ = ਮਾਪ;
  ਜੇ (!mz_zip_reader_read_central_dir(pZip, flags))
  {
    mz_zip_reader_ਸਿਰਾ(pZip);
    ਵਾਪਸ MZ_FALSE;
  }
  ਵਾਪਸ MZ_TRUE;
}

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_STDIO
ਸਥਿਰ size_t mz_zip_file_read_func(ਖਾਲੀ *pOpaque, mz_uint64 file_ofs, ਖਾਲੀ *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_int64 cur_ofs = MZ_FTELL64(pZip->m_pState->m_pFile);
  ਜੇ (((mz_int64)file_ofs < 0) || (((cur_ofs != (mz_int64)file_ofs)) && (MZ_FSEEK64(pZip->m_pState->m_pFile, (mz_int64)file_ofs, SEEK_SET))))
    ਵਾਪਸ 0;
  ਵਾਪਸ MZ_FREAD(pBuf, 1, n, pZip->m_pState->m_pFile);
}

mz_bool mz_zip_reader_init_file(mz_zip_archive *pZip, ਅਚਲ ਅੱਖਰ *pFilename, mz_uint32 flags)
{
  mz_uint64 file_ਮਾਪ;
  MZ_FILE *pFile = MZ_FOPEN(pFilename, "rb");
  ਜੇ (!pFile)
    ਵਾਪਸ MZ_FALSE;
  ਜੇ (MZ_FSEEK64(pFile, 0, SEEK_END))
  {
    MZ_FCLOSE(pFile);
    ਵਾਪਸ MZ_FALSE;
  }
  file_ਮਾਪ = MZ_FTELL64(pFile);
  ਜੇ (!mz_zip_reader_init_ਅੰਦਰੂਨੀ(pZip, flags))
  {
    MZ_FCLOSE(pFile);
    ਵਾਪਸ MZ_FALSE;
  }
  pZip->m_pRead = mz_zip_file_read_func;
  pZip->m_pIO_opaque = pZip;
  pZip->m_pState->m_pFile = pFile;
  pZip->m_archive_ਮਾਪ = file_ਮਾਪ;
  ਜੇ (!mz_zip_reader_read_central_dir(pZip, flags))
  {
    mz_zip_reader_ਸਿਰਾ(pZip);
    ਵਾਪਸ MZ_FALSE;
  }
  ਵਾਪਸ MZ_TRUE;
}
#ਜੇ_ਅੰਤ // #ifndef MINIZ_NO_STDIO

mz_uint mz_zip_reader_get_ਅੰਕ_files(mz_zip_archive *pZip)
{
  ਵਾਪਸ pZip ? pZip->m_ਕੁੱਲ_files : 0;
}

ਸਥਿਰ MZ_FORCEINLINE ਅਚਲ mz_uint8 *mz_zip_reader_get_cdh(mz_zip_archive *pZip, mz_uint file_ਸੂਚਕਾਂਕ)
{
  ਜੇ ((!pZip) || (!pZip->m_pState) || (file_ਸੂਚਕਾਂਕ >= pZip->m_ਕੁੱਲ_files) || (pZip->m_zip_ਬਹੁਲਕ != MZ_ZIP_ਬਹੁਲਕ_READING))
    ਵਾਪਸ ਨਿਰਾ;
  ਵਾਪਸ &MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_ਸੂਚਕਾਂਕ));
}

mz_bool mz_zip_reader_is_file_encrypted(mz_zip_archive *pZip, mz_uint file_ਸੂਚਕਾਂਕ)
{
  mz_uint m_ਦੋਆਧਾਰੀ_ਅੰਕ_flag;
  ਅਚਲ mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_ਸੂਚਕਾਂਕ);
  ਜੇ (!p)
    ਵਾਪਸ MZ_FALSE;
  m_ਦੋਆਧਾਰੀ_ਅੰਕ_flag = MZ_READ_LE16(p + MZ_ZIP_CDH_ਦੋਆਧਾਰੀ_ਅੰਕ_FLAG_OFS);
  ਵਾਪਸ (m_ਦੋਆਧਾਰੀ_ਅੰਕ_flag & 1);
}

mz_bool mz_zip_reader_is_file_a_directory(mz_zip_archive *pZip, mz_uint file_ਸੂਚਕਾਂਕ)
{
  mz_uint filename_len, external_attr;
  ਅਚਲ mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_ਸੂਚਕਾਂਕ);
  ਜੇ (!p)
    ਵਾਪਸ MZ_FALSE;

  // First see if the filename ends with a '/' character.
  filename_len = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  ਜੇ (filename_len)
  {
    ਜੇ (*(p + MZ_ZIP_CENTRAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ + filename_len - 1) == '/')
      ਵਾਪਸ MZ_TRUE;
  }

  // Bugfix: This code was also checking if the internal attribute was non-zero, which wasn't correct.
  // Most/all zip writers (hopefully) set DOS file/directory attributes in the low 16-bits, so check for the DOS directory flag and ignore the source OS ID in the created by field.
  // FIXME: Remove this check? Is it necessary - we already check the filename.
  external_attr = MZ_READ_LE32(p + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS);
  ਜੇ ((external_attr & 0x10) != 0)
    ਵਾਪਸ MZ_TRUE;

  ਵਾਪਸ MZ_FALSE;
}

mz_bool mz_zip_reader_file_stat(mz_zip_archive *pZip, mz_uint file_ਸੂਚਕਾਂਕ, mz_zip_archive_file_stat *pStat)
{
  mz_uint n;
  ਅਚਲ mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_ਸੂਚਕਾਂਕ);
  ਜੇ ((!p) || (!pStat))
    ਵਾਪਸ MZ_FALSE;

  // Unpack the central directory record.
  pStat->m_file_ਸੂਚਕਾਂਕ = file_ਸੂਚਕਾਂਕ;
  pStat->m_central_dir_ofs = MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_ਸੂਚਕਾਂਕ);
  pStat->m_ਸੰਸਕਰਣ_made_by = MZ_READ_LE16(p + MZ_ZIP_CDH_ਸੰਸਕਰਣ_MADE_BY_OFS);
  pStat->m_ਸੰਸਕਰਣ_needed = MZ_READ_LE16(p + MZ_ZIP_CDH_ਸੰਸਕਰਣ_NEEDED_OFS);
  pStat->m_ਦੋਆਧਾਰੀ_ਅੰਕ_flag = MZ_READ_LE16(p + MZ_ZIP_CDH_ਦੋਆਧਾਰੀ_ਅੰਕ_FLAG_OFS);
  pStat->m_ਵਿਧੀ = MZ_READ_LE16(p + MZ_ZIP_CDH_ਵਿਧੀ_OFS);
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_ਸਮਾਂ
  pStat->m_ਸਮਾਂ = mz_zip_dos_ਮੰਜ਼ਿਲ_ਸਮਾਂ_t(MZ_READ_LE16(p + MZ_ZIP_CDH_FILE_ਸਮਾਂ_OFS), MZ_READ_LE16(p + MZ_ZIP_CDH_FILE_DATE_OFS));
#ਜੇ_ਅੰਤ
  pStat->m_ਚੱਕਰੀ_ਜਾਂਚ_32 = MZ_READ_LE32(p + MZ_ZIP_CDH_ਚੱਕਰੀ_ਜਾਂਚ_32_OFS);
  pStat->m_comp_ਮਾਪ = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_ਮਾਪ_OFS);
  pStat->m_uncomp_ਮਾਪ = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_ਮਾਪ_OFS);
  pStat->m_ਅੰਦਰੂਨੀ_attr = MZ_READ_LE16(p + MZ_ZIP_CDH_ਅੰਦਰੂਨੀ_ATTR_OFS);
  pStat->m_external_attr = MZ_READ_LE32(p + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS);
  pStat->m_local_ਸਿਰਲੇਖ_ofs = MZ_READ_LE32(p + MZ_ZIP_CDH_LOCAL_ਸਿਰਲੇਖ_OFS);

  // Copy as much of the filename and comment as possible.
  n = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS); n = MZ_MIN(n, MZ_ZIP_MAX_ARCHIVE_FILENAME_ਮਾਪ - 1);
  ਸਮ੍ਰਿਤੀ_ਨਕਲ(pStat->m_filename, p + MZ_ZIP_CENTRAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ, n); pStat->m_filename[n] = '\0';

  n = MZ_READ_LE16(p + MZ_ZIP_CDH_COMMENT_LEN_OFS); n = MZ_MIN(n, MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_ਮਾਪ - 1);
  pStat->m_comment_ਮਾਪ = n;
  ਸਮ੍ਰਿਤੀ_ਨਕਲ(pStat->m_comment, p + MZ_ZIP_CENTRAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ + MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_EXTRA_LEN_OFS), n); pStat->m_comment[n] = '\0';

  ਵਾਪਸ MZ_TRUE;
}

mz_uint mz_zip_reader_get_filename(mz_zip_archive *pZip, mz_uint file_ਸੂਚਕਾਂਕ, ਅੱਖਰ *pFilename, mz_uint filename_buf_ਮਾਪ)
{
  mz_uint n;
  ਅਚਲ mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_ਸੂਚਕਾਂਕ);
  ਜੇ (!p) { ਜੇ (filename_buf_ਮਾਪ) pFilename[0] = '\0'; ਵਾਪਸ 0; }
  n = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  ਜੇ (filename_buf_ਮਾਪ)
  {
    n = MZ_MIN(n, filename_buf_ਮਾਪ - 1);
    ਸਮ੍ਰਿਤੀ_ਨਕਲ(pFilename, p + MZ_ZIP_CENTRAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ, n);
    pFilename[n] = '\0';
  }
  ਵਾਪਸ n + 1;
}

ਸਥਿਰ MZ_FORCEINLINE mz_bool mz_zip_reader_string_equal(ਅਚਲ ਅੱਖਰ *pA, ਅਚਲ ਅੱਖਰ *pB, mz_uint len, mz_uint flags)
{
  mz_uint i;
  ਜੇ (flags & MZ_ZIP_FLAG_CASE_SENSITIVE)
    ਵਾਪਸ 0 == memcmp(pA, pB, len);
  ਲਈ (i = 0; i < len; ++i)
    ਜੇ (MZ_TOLOWER(pA[i]) != MZ_TOLOWER(pB[i]))
      ਵਾਪਸ MZ_FALSE;
  ਵਾਪਸ MZ_TRUE;
}

ਸਥਿਰ MZ_FORCEINLINE ਪੂਰਨ mz_zip_reader_filename_compare(ਅਚਲ mz_zip_array *pCentral_dir_array, ਅਚਲ mz_zip_array *pCentral_dir_offsets, mz_uint l_ਸੂਚਕਾਂਕ, ਅਚਲ ਅੱਖਰ *pR, mz_uint r_len)
{
  ਅਚਲ mz_uint8 *pL = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, l_ਸੂਚਕਾਂਕ)), *pE;
  mz_uint l_len = MZ_READ_LE16(pL + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  mz_uint8 l = 0, r = 0;
  pL += MZ_ZIP_CENTRAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ;
  pE = pL + MZ_MIN(l_len, r_len);
  ਜਦੋਂ (pL < pE)
  {
    ਜੇ ((l = MZ_TOLOWER(*pL)) != (r = MZ_TOLOWER(*pR)))
      ਰੋਕੋ;
    pL++; pR++;
  }
  ਵਾਪਸ (pL == pE) ? (ਪੂਰਨ)(l_len - r_len) : (l - r);
}

ਸਥਿਰ ਪੂਰਨ mz_zip_reader_locate_file_ਦੁਆਧਾਰੀ_ਖੋਜ(mz_zip_archive *pZip, ਅਚਲ ਅੱਖਰ *pFilename)
{
  mz_zip_ਅੰਦਰੂਨੀ_state *pState = pZip->m_pState;
  ਅਚਲ mz_zip_array *pCentral_dir_offsets = &pState->m_central_dir_offsets;
  ਅਚਲ mz_zip_array *pCentral_dir = &pState->m_central_dir;
  mz_uint32 *pIndices = &MZ_ZIP_ARRAY_ELEMENT(&pState->m_sorted_central_dir_offsets, mz_uint32, 0);
  ਅਚਲ ਪੂਰਨ ਮਾਪ = pZip->m_ਕੁੱਲ_files;
  ਅਚਲ mz_uint filename_len = (mz_uint)ਲੜੀ_ਲੰਬਾਈ(pFilename);
  ਪੂਰਨ l = 0, h = ਮਾਪ - 1;
  ਜਦੋਂ (l <= h)
  {
    ਪੂਰਨ m = (l + h) >> 1, file_ਸੂਚਕਾਂਕ = pIndices[m], comp = mz_zip_reader_filename_compare(pCentral_dir, pCentral_dir_offsets, file_ਸੂਚਕਾਂਕ, pFilename, filename_len);
    ਜੇ (!comp)
      ਵਾਪਸ file_ਸੂਚਕਾਂਕ;
    ਨਹੀਂਤਾਂ ਜੇ (comp < 0)
      l = m + 1;
    ਨਹੀਂਤਾਂ
      h = m - 1;
  }
  ਵਾਪਸ -1;
}

ਪੂਰਨ mz_zip_reader_locate_file(mz_zip_archive *pZip, ਅਚਲ ਅੱਖਰ *pName, ਅਚਲ ਅੱਖਰ *pComment, mz_uint flags)
{
  mz_uint file_ਸੂਚਕਾਂਕ; size_t name_len, comment_len;
  ਜੇ ((!pZip) || (!pZip->m_pState) || (!pName) || (pZip->m_zip_ਬਹੁਲਕ != MZ_ZIP_ਬਹੁਲਕ_READING))
    ਵਾਪਸ -1;
  ਜੇ (((flags & (MZ_ZIP_FLAG_IGNORE_ਰਸਤਾ | MZ_ZIP_FLAG_CASE_SENSITIVE)) == 0) && (!pComment) && (pZip->m_pState->m_sorted_central_dir_offsets.m_ਮਾਪ))
    ਵਾਪਸ mz_zip_reader_locate_file_ਦੁਆਧਾਰੀ_ਖੋਜ(pZip, pName);
  name_len = ਲੜੀ_ਲੰਬਾਈ(pName); ਜੇ (name_len > 0xFFFF) ਵਾਪਸ -1;
  comment_len = pComment ? ਲੜੀ_ਲੰਬਾਈ(pComment) : 0; ਜੇ (comment_len > 0xFFFF) ਵਾਪਸ -1;
  ਲਈ (file_ਸੂਚਕਾਂਕ = 0; file_ਸੂਚਕਾਂਕ < pZip->m_ਕੁੱਲ_files; file_ਸੂਚਕਾਂਕ++)
  {
    ਅਚਲ mz_uint8 *p_ਸਿਰਲੇਖ = &MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_ਸੂਚਕਾਂਕ));
    mz_uint filename_len = MZ_READ_LE16(p_ਸਿਰਲੇਖ + MZ_ZIP_CDH_FILENAME_LEN_OFS);
    ਅਚਲ ਅੱਖਰ *pFilename = (ਅਚਲ ਅੱਖਰ *)p_ਸਿਰਲੇਖ + MZ_ZIP_CENTRAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ;
    ਜੇ (filename_len < name_len)
      ਜਾਰੀ;
    ਜੇ (comment_len)
    {
      mz_uint file_extra_len = MZ_READ_LE16(p_ਸਿਰਲੇਖ + MZ_ZIP_CDH_EXTRA_LEN_OFS), file_comment_len = MZ_READ_LE16(p_ਸਿਰਲੇਖ + MZ_ZIP_CDH_COMMENT_LEN_OFS);
      ਅਚਲ ਅੱਖਰ *pFile_comment = pFilename + filename_len + file_extra_len;
      ਜੇ ((file_comment_len != comment_len) || (!mz_zip_reader_string_equal(pComment, pFile_comment, file_comment_len, flags)))
        ਜਾਰੀ;
    }
    ਜੇ ((flags & MZ_ZIP_FLAG_IGNORE_ਰਸਤਾ) && (filename_len))
    {
      ਪੂਰਨ ofs = filename_len - 1;
      ਕਰੋ
      {
        ਜੇ ((pFilename[ofs] == '/') || (pFilename[ofs] == '\\') || (pFilename[ofs] == ':'))
          ਰੋਕੋ;
      } ਜਦੋਂ (--ofs >= 0);
      ofs++;
      pFilename += ofs; filename_len -= ofs;
    }
    ਜੇ ((filename_len == name_len) && (mz_zip_reader_string_equal(pName, pFilename, filename_len, flags)))
      ਵਾਪਸ file_ਸੂਚਕਾਂਕ;
  }
  ਵਾਪਸ -1;
}

mz_bool mz_zip_reader_ਕੱਢੋ_ਮੰਜ਼ਿਲ_mem_no_alloc(mz_zip_archive *pZip, mz_uint file_ਸੂਚਕਾਂਕ, ਖਾਲੀ *pBuf, size_t buf_ਮਾਪ_2, mz_uint flags, ਖਾਲੀ *pUser_read_buf, size_t user_read_buf_ਮਾਪ)
{
  ਪੂਰਨ ਸਥਿਤੀ = TINFL_ਸਥਿਤੀ_ਪੂਰਾ;
  mz_uint64 needed_ਮਾਪ, cur_file_ofs, comp_ਬਚਿਆ, ਬਾਹਰਲਾ_buf_ofs = 0, read_buf_ਮਾਪ, read_buf_ofs = 0, read_buf_avail;
  mz_zip_archive_file_stat file_stat;
  ਖਾਲੀ *pRead_buf;
  mz_uint32 local_ਸਿਰਲੇਖ_u32[(MZ_ZIP_LOCAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ + ਆਕਾਰ(mz_uint32) - 1) / ਆਕਾਰ(mz_uint32)]; mz_uint8 *p_Local_ਸਿਰਲੇਖ = (mz_uint8 *)local_ਸਿਰਲੇਖ_u32;
  tinfl_decompressor inflator;

  ਜੇ ((buf_ਮਾਪ_2) && (!pBuf))
    ਵਾਪਸ MZ_FALSE;

  ਜੇ (!mz_zip_reader_file_stat(pZip, file_ਸੂਚਕਾਂਕ, &file_stat))
    ਵਾਪਸ MZ_FALSE;

  // Empty file, or a directory (but not always a directory - I've seen odd zips with directories that have compressed data which inflates to 0 bytes)
  ਜੇ (!file_stat.m_comp_ਮਾਪ)
    ਵਾਪਸ MZ_TRUE;

  // Entry is a subdirectory (I've seen old zips with dir entries which have compressed deflate data which inflates to 0 bytes, but these entries claim to uncompress to 512 bytes in the headers).
  // I'm torn how to handle this case - should it fail instead?
  ਜੇ (mz_zip_reader_is_file_a_directory(pZip, file_ਸੂਚਕਾਂਕ))
    ਵਾਪਸ MZ_TRUE;

  // Encryption and patch files are not supported.
  ਜੇ (file_stat.m_ਦੋਆਧਾਰੀ_ਅੰਕ_flag & (1 | 32))
    ਵਾਪਸ MZ_FALSE;

  // This function only supports stored and deflate.
  ਜੇ ((!(flags & MZ_ZIP_FLAG_COMPRESSED_ਅੰਕੜੇ)) && (file_stat.m_ਵਿਧੀ != 0) && (file_stat.m_ਵਿਧੀ != MZ_DEFLATED))
    ਵਾਪਸ MZ_FALSE;

  // Ensure supplied output buffer is large enough.
  needed_ਮਾਪ = (flags & MZ_ZIP_FLAG_COMPRESSED_ਅੰਕੜੇ) ? file_stat.m_comp_ਮਾਪ : file_stat.m_uncomp_ਮਾਪ;
  ਜੇ (buf_ਮਾਪ_2 < needed_ਮਾਪ)
    ਵਾਪਸ MZ_FALSE;

  // Read and parse the local directory entry.
  cur_file_ofs = file_stat.m_local_ਸਿਰਲੇਖ_ofs;
  ਜੇ (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, p_Local_ਸਿਰਲੇਖ, MZ_ZIP_LOCAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ) != MZ_ZIP_LOCAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ)
    ਵਾਪਸ MZ_FALSE;
  ਜੇ (MZ_READ_LE32(p_Local_ਸਿਰਲੇਖ) != MZ_ZIP_LOCAL_DIR_ਸਿਰਲੇਖ_SIG)
    ਵਾਪਸ MZ_FALSE;

  cur_file_ofs += MZ_ZIP_LOCAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ + MZ_READ_LE16(p_Local_ਸਿਰਲੇਖ + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p_Local_ਸਿਰਲੇਖ + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  ਜੇ ((cur_file_ofs + file_stat.m_comp_ਮਾਪ) > pZip->m_archive_ਮਾਪ)
    ਵਾਪਸ MZ_FALSE;

  ਜੇ ((flags & MZ_ZIP_FLAG_COMPRESSED_ਅੰਕੜੇ) || (!file_stat.m_ਵਿਧੀ))
  {
    // The file is stored or the caller has requested the compressed data.
    ਜੇ (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, (size_t)needed_ਮਾਪ) != needed_ਮਾਪ)
      ਵਾਪਸ MZ_FALSE;
    ਵਾਪਸ ((flags & MZ_ZIP_FLAG_COMPRESSED_ਅੰਕੜੇ) != 0) || (mz_ਚੱਕਰੀ_ਜਾਂਚ_32(MZ_ਚੱਕਰੀ_ਜਾਂਚ_32_INIT, (ਅਚਲ mz_uint8 *)pBuf, (size_t)file_stat.m_uncomp_ਮਾਪ) == file_stat.m_ਚੱਕਰੀ_ਜਾਂਚ_32);
  }

  // Decompress the file either directly from memory or from a file input buffer.
  tinfl_init(&inflator);

  ਜੇ (pZip->m_pState->m_pMem)
  {
    // Read directly from the archive in memory.
    pRead_buf = (mz_uint8 *)pZip->m_pState->m_pMem + cur_file_ofs;
    read_buf_ਮਾਪ = read_buf_avail = file_stat.m_comp_ਮਾਪ;
    comp_ਬਚਿਆ = 0;
  }
  ਨਹੀਂਤਾਂ ਜੇ (pUser_read_buf)
  {
    // Use a user provided read buffer.
    ਜੇ (!user_read_buf_ਮਾਪ)
      ਵਾਪਸ MZ_FALSE;
    pRead_buf = (mz_uint8 *)pUser_read_buf;
    read_buf_ਮਾਪ = user_read_buf_ਮਾਪ;
    read_buf_avail = 0;
    comp_ਬਚਿਆ = file_stat.m_comp_ਮਾਪ;
  }
  ਨਹੀਂਤਾਂ
  {
    // Temporarily allocate a read buffer.
    read_buf_ਮਾਪ = MZ_MIN(file_stat.m_comp_ਮਾਪ, MZ_ZIP_MAX_IO_BUF_ਮਾਪ);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _MSC_VER
    ਜੇ (((0, ਆਕਾਰ(size_t) == ਆਕਾਰ(mz_uint32))) && (read_buf_ਮਾਪ > 0x7FFFFFFF))
#ਨਹੀਂਤਾਂ
    ਜੇ (((ਆਕਾਰ(size_t) == ਆਕਾਰ(mz_uint32))) && (read_buf_ਮਾਪ > 0x7FFFFFFF))
#ਜੇ_ਅੰਤ
      ਵਾਪਸ MZ_FALSE;
    ਜੇ (ਨਿਰਾ == (pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)read_buf_ਮਾਪ)))
      ਵਾਪਸ MZ_FALSE;
    read_buf_avail = 0;
    comp_ਬਚਿਆ = file_stat.m_comp_ਮਾਪ;
  }

  ਕਰੋ
  {
    size_t ਵਿੱਚ_buf_ਮਾਪ, ਬਾਹਰਲਾ_buf_ਮਾਪ = (size_t)(file_stat.m_uncomp_ਮਾਪ - ਬਾਹਰਲਾ_buf_ofs);
    ਜੇ ((!read_buf_avail) && (!pZip->m_pState->m_pMem))
    {
      read_buf_avail = MZ_MIN(read_buf_ਮਾਪ, comp_ਬਚਿਆ);
      ਜੇ (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
      {
        ਸਥਿਤੀ = TINFL_ਸਥਿਤੀ_FAILED;
        ਰੋਕੋ;
      }
      cur_file_ofs += read_buf_avail;
      comp_ਬਚਿਆ -= read_buf_avail;
      read_buf_ofs = 0;
    }
    ਵਿੱਚ_buf_ਮਾਪ = (size_t)read_buf_avail;
    ਸਥਿਤੀ = tinfl_decompress(&inflator, (mz_uint8 *)pRead_buf + read_buf_ofs, &ਵਿੱਚ_buf_ਮਾਪ, (mz_uint8 *)pBuf, (mz_uint8 *)pBuf + ਬਾਹਰਲਾ_buf_ofs, &ਬਾਹਰਲਾ_buf_ਮਾਪ, TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF | (comp_ਬਚਿਆ ? TINFL_FLAG_HAS_ਹੋਰ_ਨਿਵੇਸ਼ : 0));
    read_buf_avail -= ਵਿੱਚ_buf_ਮਾਪ;
    read_buf_ofs += ਵਿੱਚ_buf_ਮਾਪ;
    ਬਾਹਰਲਾ_buf_ofs += ਬਾਹਰਲਾ_buf_ਮਾਪ;
  } ਜਦੋਂ (ਸਥਿਤੀ == TINFL_ਸਥਿਤੀ_NEEDS_ਹੋਰ_ਨਿਵੇਸ਼);

  ਜੇ (ਸਥਿਤੀ == TINFL_ਸਥਿਤੀ_ਪੂਰਾ)
  {
    // Make sure the entire file was decompressed, and check its CRC.
    ਜੇ ((ਬਾਹਰਲਾ_buf_ofs != file_stat.m_uncomp_ਮਾਪ) || (mz_ਚੱਕਰੀ_ਜਾਂਚ_32(MZ_ਚੱਕਰੀ_ਜਾਂਚ_32_INIT, (ਅਚਲ mz_uint8 *)pBuf, (size_t)file_stat.m_uncomp_ਮਾਪ) != file_stat.m_ਚੱਕਰੀ_ਜਾਂਚ_32))
      ਸਥਿਤੀ = TINFL_ਸਥਿਤੀ_FAILED;
  }

  ਜੇ ((!pZip->m_pState->m_pMem) && (!pUser_read_buf))
    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);

  ਵਾਪਸ ਸਥਿਤੀ == TINFL_ਸਥਿਤੀ_ਪੂਰਾ;
}

mz_bool mz_zip_reader_ਕੱਢੋ_file_ਮੰਜ਼ਿਲ_mem_no_alloc(mz_zip_archive *pZip, ਅਚਲ ਅੱਖਰ *pFilename, ਖਾਲੀ *pBuf, size_t buf_ਮਾਪ_2, mz_uint flags, ਖਾਲੀ *pUser_read_buf, size_t user_read_buf_ਮਾਪ)
{
  ਪੂਰਨ file_ਸੂਚਕਾਂਕ = mz_zip_reader_locate_file(pZip, pFilename, ਨਿਰਾ, flags);
  ਜੇ (file_ਸੂਚਕਾਂਕ < 0)
    ਵਾਪਸ MZ_FALSE;
  ਵਾਪਸ mz_zip_reader_ਕੱਢੋ_ਮੰਜ਼ਿਲ_mem_no_alloc(pZip, file_ਸੂਚਕਾਂਕ, pBuf, buf_ਮਾਪ_2, flags, pUser_read_buf, user_read_buf_ਮਾਪ);
}

mz_bool mz_zip_reader_ਕੱਢੋ_ਮੰਜ਼ਿਲ_mem(mz_zip_archive *pZip, mz_uint file_ਸੂਚਕਾਂਕ, ਖਾਲੀ *pBuf, size_t buf_ਮਾਪ_2, mz_uint flags)
{
  ਵਾਪਸ mz_zip_reader_ਕੱਢੋ_ਮੰਜ਼ਿਲ_mem_no_alloc(pZip, file_ਸੂਚਕਾਂਕ, pBuf, buf_ਮਾਪ_2, flags, ਨਿਰਾ, 0);
}

mz_bool mz_zip_reader_ਕੱਢੋ_file_ਮੰਜ਼ਿਲ_mem(mz_zip_archive *pZip, ਅਚਲ ਅੱਖਰ *pFilename, ਖਾਲੀ *pBuf, size_t buf_ਮਾਪ_2, mz_uint flags)
{
  ਵਾਪਸ mz_zip_reader_ਕੱਢੋ_file_ਮੰਜ਼ਿਲ_mem_no_alloc(pZip, pFilename, pBuf, buf_ਮਾਪ_2, flags, ਨਿਰਾ, 0);
}

ਖਾਲੀ *mz_zip_reader_ਕੱਢੋ_ਮੰਜ਼ਿਲ_ਢੇਰ(mz_zip_archive *pZip, mz_uint file_ਸੂਚਕਾਂਕ, size_t *p_ਮਾਪ, mz_uint flags)
{
  mz_uint64 comp_ਮਾਪ, uncomp_ਮਾਪ, alloc_ਮਾਪ_2;
  ਅਚਲ mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_ਸੂਚਕਾਂਕ);
  ਖਾਲੀ *pBuf;

  ਜੇ (p_ਮਾਪ)
    *p_ਮਾਪ = 0;
  ਜੇ (!p)
    ਵਾਪਸ ਨਿਰਾ;

  comp_ਮਾਪ = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_ਮਾਪ_OFS);
  uncomp_ਮਾਪ = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_ਮਾਪ_OFS);

  alloc_ਮਾਪ_2 = (flags & MZ_ZIP_FLAG_COMPRESSED_ਅੰਕੜੇ) ? comp_ਮਾਪ : uncomp_ਮਾਪ;
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _MSC_VER
  ਜੇ (((0, ਆਕਾਰ(size_t) == ਆਕਾਰ(mz_uint32))) && (alloc_ਮਾਪ_2 > 0x7FFFFFFF))
#ਨਹੀਂਤਾਂ
  ਜੇ (((ਆਕਾਰ(size_t) == ਆਕਾਰ(mz_uint32))) && (alloc_ਮਾਪ_2 > 0x7FFFFFFF))
#ਜੇ_ਅੰਤ
    ਵਾਪਸ ਨਿਰਾ;
  ਜੇ (ਨਿਰਾ == (pBuf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)alloc_ਮਾਪ_2)))
    ਵਾਪਸ ਨਿਰਾ;

  ਜੇ (!mz_zip_reader_ਕੱਢੋ_ਮੰਜ਼ਿਲ_mem(pZip, file_ਸੂਚਕਾਂਕ, pBuf, (size_t)alloc_ਮਾਪ_2, flags))
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
    ਵਾਪਸ ਨਿਰਾ;
  }

  ਜੇ (p_ਮਾਪ) *p_ਮਾਪ = (size_t)alloc_ਮਾਪ_2;
  ਵਾਪਸ pBuf;
}

ਖਾਲੀ *mz_zip_reader_ਕੱਢੋ_file_ਮੰਜ਼ਿਲ_ਢੇਰ(mz_zip_archive *pZip, ਅਚਲ ਅੱਖਰ *pFilename, size_t *p_ਮਾਪ, mz_uint flags)
{
  ਪੂਰਨ file_ਸੂਚਕਾਂਕ = mz_zip_reader_locate_file(pZip, pFilename, ਨਿਰਾ, flags);
  ਜੇ (file_ਸੂਚਕਾਂਕ < 0)
  {
    ਜੇ (p_ਮਾਪ) *p_ਮਾਪ = 0;
    ਵਾਪਸ MZ_FALSE;
  }
  ਵਾਪਸ mz_zip_reader_ਕੱਢੋ_ਮੰਜ਼ਿਲ_ਢੇਰ(pZip, file_ਸੂਚਕਾਂਕ, p_ਮਾਪ, flags);
}

mz_bool mz_zip_reader_ਕੱਢੋ_ਮੰਜ਼ਿਲ_callback(mz_zip_archive *pZip, mz_uint file_ਸੂਚਕਾਂਕ, mz_file_write_func pCallback, ਖਾਲੀ *pOpaque, mz_uint flags)
{
  ਪੂਰਨ ਸਥਿਤੀ = TINFL_ਸਥਿਤੀ_ਪੂਰਾ; mz_uint file_ਚੱਕਰੀ_ਜਾਂਚ_32 = MZ_ਚੱਕਰੀ_ਜਾਂਚ_32_INIT;
  mz_uint64 read_buf_ਮਾਪ, read_buf_ofs = 0, read_buf_avail, comp_ਬਚਿਆ, ਬਾਹਰਲਾ_buf_ofs = 0, cur_file_ofs;
  mz_zip_archive_file_stat file_stat;
  ਖਾਲੀ *pRead_buf = ਨਿਰਾ; ਖਾਲੀ *pWrite_buf = ਨਿਰਾ;
  mz_uint32 local_ਸਿਰਲੇਖ_u32[(MZ_ZIP_LOCAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ + ਆਕਾਰ(mz_uint32) - 1) / ਆਕਾਰ(mz_uint32)]; mz_uint8 *p_Local_ਸਿਰਲੇਖ = (mz_uint8 *)local_ਸਿਰਲੇਖ_u32;

  ਜੇ (!mz_zip_reader_file_stat(pZip, file_ਸੂਚਕਾਂਕ, &file_stat))
    ਵਾਪਸ MZ_FALSE;

  // Empty file, or a directory (but not always a directory - I've seen odd zips with directories that have compressed data which inflates to 0 bytes)
  ਜੇ (!file_stat.m_comp_ਮਾਪ)
    ਵਾਪਸ MZ_TRUE;

  // Entry is a subdirectory (I've seen old zips with dir entries which have compressed deflate data which inflates to 0 bytes, but these entries claim to uncompress to 512 bytes in the headers).
  // I'm torn how to handle this case - should it fail instead?
  ਜੇ (mz_zip_reader_is_file_a_directory(pZip, file_ਸੂਚਕਾਂਕ))
    ਵਾਪਸ MZ_TRUE;

  // Encryption and patch files are not supported.
  ਜੇ (file_stat.m_ਦੋਆਧਾਰੀ_ਅੰਕ_flag & (1 | 32))
    ਵਾਪਸ MZ_FALSE;

  // This function only supports stored and deflate.
  ਜੇ ((!(flags & MZ_ZIP_FLAG_COMPRESSED_ਅੰਕੜੇ)) && (file_stat.m_ਵਿਧੀ != 0) && (file_stat.m_ਵਿਧੀ != MZ_DEFLATED))
    ਵਾਪਸ MZ_FALSE;

  // Read and parse the local directory entry.
  cur_file_ofs = file_stat.m_local_ਸਿਰਲੇਖ_ofs;
  ਜੇ (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, p_Local_ਸਿਰਲੇਖ, MZ_ZIP_LOCAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ) != MZ_ZIP_LOCAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ)
    ਵਾਪਸ MZ_FALSE;
  ਜੇ (MZ_READ_LE32(p_Local_ਸਿਰਲੇਖ) != MZ_ZIP_LOCAL_DIR_ਸਿਰਲੇਖ_SIG)
    ਵਾਪਸ MZ_FALSE;

  cur_file_ofs += MZ_ZIP_LOCAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ + MZ_READ_LE16(p_Local_ਸਿਰਲੇਖ + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p_Local_ਸਿਰਲੇਖ + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  ਜੇ ((cur_file_ofs + file_stat.m_comp_ਮਾਪ) > pZip->m_archive_ਮਾਪ)
    ਵਾਪਸ MZ_FALSE;

  // Decompress the file either directly from memory or from a file input buffer.
  ਜੇ (pZip->m_pState->m_pMem)
  {
    pRead_buf = (mz_uint8 *)pZip->m_pState->m_pMem + cur_file_ofs;
    read_buf_ਮਾਪ = read_buf_avail = file_stat.m_comp_ਮਾਪ;
    comp_ਬਚਿਆ = 0;
  }
  ਨਹੀਂਤਾਂ
  {
    read_buf_ਮਾਪ = MZ_MIN(file_stat.m_comp_ਮਾਪ, MZ_ZIP_MAX_IO_BUF_ਮਾਪ);
    ਜੇ (ਨਿਰਾ == (pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)read_buf_ਮਾਪ)))
      ਵਾਪਸ MZ_FALSE;
    read_buf_avail = 0;
    comp_ਬਚਿਆ = file_stat.m_comp_ਮਾਪ;
  }

  ਜੇ ((flags & MZ_ZIP_FLAG_COMPRESSED_ਅੰਕੜੇ) || (!file_stat.m_ਵਿਧੀ))
  {
    // The file is stored or the caller has requested the compressed data.
    ਜੇ (pZip->m_pState->m_pMem)
    {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _MSC_VER
      ਜੇ (((0, ਆਕਾਰ(size_t) == ਆਕਾਰ(mz_uint32))) && (file_stat.m_comp_ਮਾਪ > 0xFFFFFFFF))
#ਨਹੀਂਤਾਂ
      ਜੇ (((ਆਕਾਰ(size_t) == ਆਕਾਰ(mz_uint32))) && (file_stat.m_comp_ਮਾਪ > 0xFFFFFFFF))
#ਜੇ_ਅੰਤ
        ਵਾਪਸ MZ_FALSE;
      ਜੇ (pCallback(pOpaque, ਬਾਹਰਲਾ_buf_ofs, pRead_buf, (size_t)file_stat.m_comp_ਮਾਪ) != file_stat.m_comp_ਮਾਪ)
        ਸਥਿਤੀ = TINFL_ਸਥਿਤੀ_FAILED;
      ਨਹੀਂਤਾਂ ਜੇ (!(flags & MZ_ZIP_FLAG_COMPRESSED_ਅੰਕੜੇ))
        file_ਚੱਕਰੀ_ਜਾਂਚ_32 = (mz_uint32)mz_ਚੱਕਰੀ_ਜਾਂਚ_32(file_ਚੱਕਰੀ_ਜਾਂਚ_32, (ਅਚਲ mz_uint8 *)pRead_buf, (size_t)file_stat.m_comp_ਮਾਪ);
      cur_file_ofs += file_stat.m_comp_ਮਾਪ;
      ਬਾਹਰਲਾ_buf_ofs += file_stat.m_comp_ਮਾਪ;
      comp_ਬਚਿਆ = 0;
    }
    ਨਹੀਂਤਾਂ
    {
      ਜਦੋਂ (comp_ਬਚਿਆ)
      {
        read_buf_avail = MZ_MIN(read_buf_ਮਾਪ, comp_ਬਚਿਆ);
        ਜੇ (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
        {
          ਸਥਿਤੀ = TINFL_ਸਥਿਤੀ_FAILED;
          ਰੋਕੋ;
        }

        ਜੇ (!(flags & MZ_ZIP_FLAG_COMPRESSED_ਅੰਕੜੇ))
          file_ਚੱਕਰੀ_ਜਾਂਚ_32 = (mz_uint32)mz_ਚੱਕਰੀ_ਜਾਂਚ_32(file_ਚੱਕਰੀ_ਜਾਂਚ_32, (ਅਚਲ mz_uint8 *)pRead_buf, (size_t)read_buf_avail);

        ਜੇ (pCallback(pOpaque, ਬਾਹਰਲਾ_buf_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
        {
          ਸਥਿਤੀ = TINFL_ਸਥਿਤੀ_FAILED;
          ਰੋਕੋ;
        }
        cur_file_ofs += read_buf_avail;
        ਬਾਹਰਲਾ_buf_ofs += read_buf_avail;
        comp_ਬਚਿਆ -= read_buf_avail;
      }
    }
  }
  ਨਹੀਂਤਾਂ
  {
    tinfl_decompressor inflator;
    tinfl_init(&inflator);

    ਜੇ (ਨਿਰਾ == (pWrite_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, TINFL_LZ_DICT_ਮਾਪ)))
      ਸਥਿਤੀ = TINFL_ਸਥਿਤੀ_FAILED;
    ਨਹੀਂਤਾਂ
    {
      ਕਰੋ
      {
        mz_uint8 *pWrite_buf_cur = (mz_uint8 *)pWrite_buf + (ਬਾਹਰਲਾ_buf_ofs & (TINFL_LZ_DICT_ਮਾਪ - 1));
        size_t ਵਿੱਚ_buf_ਮਾਪ, ਬਾਹਰਲਾ_buf_ਮਾਪ = TINFL_LZ_DICT_ਮਾਪ - (ਬਾਹਰਲਾ_buf_ofs & (TINFL_LZ_DICT_ਮਾਪ - 1));
        ਜੇ ((!read_buf_avail) && (!pZip->m_pState->m_pMem))
        {
          read_buf_avail = MZ_MIN(read_buf_ਮਾਪ, comp_ਬਚਿਆ);
          ਜੇ (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
          {
            ਸਥਿਤੀ = TINFL_ਸਥਿਤੀ_FAILED;
            ਰੋਕੋ;
          }
          cur_file_ofs += read_buf_avail;
          comp_ਬਚਿਆ -= read_buf_avail;
          read_buf_ofs = 0;
        }

        ਵਿੱਚ_buf_ਮਾਪ = (size_t)read_buf_avail;
        ਸਥਿਤੀ = tinfl_decompress(&inflator, (ਅਚਲ mz_uint8 *)pRead_buf + read_buf_ofs, &ਵਿੱਚ_buf_ਮਾਪ, (mz_uint8 *)pWrite_buf, pWrite_buf_cur, &ਬਾਹਰਲਾ_buf_ਮਾਪ, comp_ਬਚਿਆ ? TINFL_FLAG_HAS_ਹੋਰ_ਨਿਵੇਸ਼ : 0);
        read_buf_avail -= ਵਿੱਚ_buf_ਮਾਪ;
        read_buf_ofs += ਵਿੱਚ_buf_ਮਾਪ;

        ਜੇ (ਬਾਹਰਲਾ_buf_ਮਾਪ)
        {
          ਜੇ (pCallback(pOpaque, ਬਾਹਰਲਾ_buf_ofs, pWrite_buf_cur, ਬਾਹਰਲਾ_buf_ਮਾਪ) != ਬਾਹਰਲਾ_buf_ਮਾਪ)
          {
            ਸਥਿਤੀ = TINFL_ਸਥਿਤੀ_FAILED;
            ਰੋਕੋ;
          }
          file_ਚੱਕਰੀ_ਜਾਂਚ_32 = (mz_uint32)mz_ਚੱਕਰੀ_ਜਾਂਚ_32(file_ਚੱਕਰੀ_ਜਾਂਚ_32, pWrite_buf_cur, ਬਾਹਰਲਾ_buf_ਮਾਪ);
          ਜੇ ((ਬਾਹਰਲਾ_buf_ofs += ਬਾਹਰਲਾ_buf_ਮਾਪ) > file_stat.m_uncomp_ਮਾਪ)
          {
            ਸਥਿਤੀ = TINFL_ਸਥਿਤੀ_FAILED;
            ਰੋਕੋ;
          }
        }
      } ਜਦੋਂ ((ਸਥਿਤੀ == TINFL_ਸਥਿਤੀ_NEEDS_ਹੋਰ_ਨਿਵੇਸ਼) || (ਸਥਿਤੀ == TINFL_ਸਥਿਤੀ_HAS_ਹੋਰ_OUTPUT));
    }
  }

  ਜੇ ((ਸਥਿਤੀ == TINFL_ਸਥਿਤੀ_ਪੂਰਾ) && (!(flags & MZ_ZIP_FLAG_COMPRESSED_ਅੰਕੜੇ)))
  {
    // Make sure the entire file was decompressed, and check its CRC.
    ਜੇ ((ਬਾਹਰਲਾ_buf_ofs != file_stat.m_uncomp_ਮਾਪ) || (file_ਚੱਕਰੀ_ਜਾਂਚ_32 != file_stat.m_ਚੱਕਰੀ_ਜਾਂਚ_32))
      ਸਥਿਤੀ = TINFL_ਸਥਿਤੀ_FAILED;
  }

  ਜੇ (!pZip->m_pState->m_pMem)
    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
  ਜੇ (pWrite_buf)
    pZip->m_pFree(pZip->m_pAlloc_opaque, pWrite_buf);

  ਵਾਪਸ ਸਥਿਤੀ == TINFL_ਸਥਿਤੀ_ਪੂਰਾ;
}

mz_bool mz_zip_reader_ਕੱਢੋ_file_ਮੰਜ਼ਿਲ_callback(mz_zip_archive *pZip, ਅਚਲ ਅੱਖਰ *pFilename, mz_file_write_func pCallback, ਖਾਲੀ *pOpaque, mz_uint flags)
{
  ਪੂਰਨ file_ਸੂਚਕਾਂਕ = mz_zip_reader_locate_file(pZip, pFilename, ਨਿਰਾ, flags);
  ਜੇ (file_ਸੂਚਕਾਂਕ < 0)
    ਵਾਪਸ MZ_FALSE;
  ਵਾਪਸ mz_zip_reader_ਕੱਢੋ_ਮੰਜ਼ਿਲ_callback(pZip, file_ਸੂਚਕਾਂਕ, pCallback, pOpaque, flags);
}

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_STDIO
ਸਥਿਰ size_t mz_zip_file_write_callback(ਖਾਲੀ *pOpaque, mz_uint64 ofs, ਅਚਲ ਖਾਲੀ *pBuf, size_t n)
{
  (ਖਾਲੀ)ofs; ਵਾਪਸ MZ_FWRITE(pBuf, 1, n, (MZ_FILE*)pOpaque);
}

mz_bool mz_zip_reader_ਕੱਢੋ_ਮੰਜ਼ਿਲ_file(mz_zip_archive *pZip, mz_uint file_ਸੂਚਕਾਂਕ, ਅਚਲ ਅੱਖਰ *pDst_filename, mz_uint flags)
{
  mz_bool ਸਥਿਤੀ;
  mz_zip_archive_file_stat file_stat;
  MZ_FILE *pFile;
  ਜੇ (!mz_zip_reader_file_stat(pZip, file_ਸੂਚਕਾਂਕ, &file_stat))
    ਵਾਪਸ MZ_FALSE;
  pFile = MZ_FOPEN(pDst_filename, "wb");
  ਜੇ (!pFile)
    ਵਾਪਸ MZ_FALSE;
  ਸਥਿਤੀ = mz_zip_reader_ਕੱਢੋ_ਮੰਜ਼ਿਲ_callback(pZip, file_ਸੂਚਕਾਂਕ, mz_zip_file_write_callback, pFile, flags);
  ਜੇ (MZ_FCLOSE(pFile) == EOF)
    ਵਾਪਸ MZ_FALSE;
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_ਸਮਾਂ
  ਜੇ (ਸਥਿਤੀ)
    mz_zip_ਸੈੱਟ_file_times(pDst_filename, file_stat.m_ਸਮਾਂ, file_stat.m_ਸਮਾਂ);
#ਜੇ_ਅੰਤ
  ਵਾਪਸ ਸਥਿਤੀ;
}
#ਜੇ_ਅੰਤ // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_reader_ਸਿਰਾ(mz_zip_archive *pZip)
{
  ਜੇ ((!pZip) || (!pZip->m_pState) || (!pZip->m_pAlloc) || (!pZip->m_pFree) || (pZip->m_zip_ਬਹੁਲਕ != MZ_ZIP_ਬਹੁਲਕ_READING))
    ਵਾਪਸ MZ_FALSE;

  ਜੇ (pZip->m_pState)
  {
    mz_zip_ਅੰਦਰੂਨੀ_state *pState = pZip->m_pState; pZip->m_pState = ਨਿਰਾ;
    mz_zip_array_clear(pZip, &pState->m_central_dir);
    mz_zip_array_clear(pZip, &pState->m_central_dir_offsets);
    mz_zip_array_clear(pZip, &pState->m_sorted_central_dir_offsets);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_STDIO
    ਜੇ (pState->m_pFile)
    {
      MZ_FCLOSE(pState->m_pFile);
      pState->m_pFile = ਨਿਰਾ;
    }
#ਜੇ_ਅੰਤ // #ifndef MINIZ_NO_STDIO

    pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
  }
  pZip->m_zip_ਬਹੁਲਕ = MZ_ZIP_ਬਹੁਲਕ_INVALID;

  ਵਾਪਸ MZ_TRUE;
}

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_STDIO
mz_bool mz_zip_reader_ਕੱਢੋ_file_ਮੰਜ਼ਿਲ_file(mz_zip_archive *pZip, ਅਚਲ ਅੱਖਰ *pArchive_filename, ਅਚਲ ਅੱਖਰ *pDst_filename, mz_uint flags)
{
  ਪੂਰਨ file_ਸੂਚਕਾਂਕ = mz_zip_reader_locate_file(pZip, pArchive_filename, ਨਿਰਾ, flags);
  ਜੇ (file_ਸੂਚਕਾਂਕ < 0)
    ਵਾਪਸ MZ_FALSE;
  ਵਾਪਸ mz_zip_reader_ਕੱਢੋ_ਮੰਜ਼ਿਲ_file(pZip, file_ਸੂਚਕਾਂਕ, pDst_filename, flags);
}
#ਜੇ_ਅੰਤ

// ------------------- .ZIP archive writing

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_ARCHIVE_WRITING_APIS

ਸਥਿਰ ਖਾਲੀ mz_write_le16(mz_uint8 *p, mz_uint16 v) { p[0] = (mz_uint8)v; p[1] = (mz_uint8)(v >> 8); }
ਸਥਿਰ ਖਾਲੀ mz_write_le32(mz_uint8 *p, mz_uint32 v) { p[0] = (mz_uint8)v; p[1] = (mz_uint8)(v >> 8); p[2] = (mz_uint8)(v >> 16); p[3] = (mz_uint8)(v >> 24); }
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_WRITE_LE16(p, v) mz_write_le16((mz_uint8 *)(p), (mz_uint16)(v))
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ MZ_WRITE_LE32(p, v) mz_write_le32((mz_uint8 *)(p), (mz_uint32)(v))

mz_bool mz_zip_writer_init(mz_zip_archive *pZip, mz_uint64 existing_ਮਾਪ)
{
  ਜੇ ((!pZip) || (pZip->m_pState) || (!pZip->m_pWrite) || (pZip->m_zip_ਬਹੁਲਕ != MZ_ZIP_ਬਹੁਲਕ_INVALID))
    ਵਾਪਸ MZ_FALSE;

  ਜੇ (pZip->m_file_ਵਿੱਥ_alignment)
  {
    // Ensure user specified file offset alignment is a power of 2.
    ਜੇ (pZip->m_file_ਵਿੱਥ_alignment & (pZip->m_file_ਵਿੱਥ_alignment - 1))
      ਵਾਪਸ MZ_FALSE;
  }

  ਜੇ (!pZip->m_pAlloc) pZip->m_pAlloc = def_alloc_func;
  ਜੇ (!pZip->m_pFree) pZip->m_pFree = def_free_func;
  ਜੇ (!pZip->m_pRealloc) pZip->m_pRealloc = def_realloc_func;

  pZip->m_zip_ਬਹੁਲਕ = MZ_ZIP_ਬਹੁਲਕ_WRITING;
  pZip->m_archive_ਮਾਪ = existing_ਮਾਪ;
  pZip->m_central_directory_file_ofs = 0;
  pZip->m_ਕੁੱਲ_files = 0;

  ਜੇ (ਨਿਰਾ == (pZip->m_pState = (mz_zip_ਅੰਦਰੂਨੀ_state *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, ਆਕਾਰ(mz_zip_ਅੰਦਰੂਨੀ_state))))
    ਵਾਪਸ MZ_FALSE;
  memset(pZip->m_pState, 0, ਆਕਾਰ(mz_zip_ਅੰਦਰੂਨੀ_state));
  MZ_ZIP_ARRAY_ਸੈੱਟ_ELEMENT_ਮਾਪ(&pZip->m_pState->m_central_dir, ਆਕਾਰ(mz_uint8));
  MZ_ZIP_ARRAY_ਸੈੱਟ_ELEMENT_ਮਾਪ(&pZip->m_pState->m_central_dir_offsets, ਆਕਾਰ(mz_uint32));
  MZ_ZIP_ARRAY_ਸੈੱਟ_ELEMENT_ਮਾਪ(&pZip->m_pState->m_sorted_central_dir_offsets, ਆਕਾਰ(mz_uint32));
  ਵਾਪਸ MZ_TRUE;
}

ਸਥਿਰ size_t mz_zip_ਢੇਰ_write_func(ਖਾਲੀ *pOpaque, mz_uint64 file_ofs, ਅਚਲ ਖਾਲੀ *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_zip_ਅੰਦਰੂਨੀ_state *pState = pZip->m_pState;
  mz_uint64 new_ਮਾਪ = MZ_MAX(file_ofs + n, pState->m_mem_ਮਾਪ);
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _MSC_VER
  ਜੇ ((!n) || ((0, ਆਕਾਰ(size_t) == ਆਕਾਰ(mz_uint32)) && (new_ਮਾਪ > 0x7FFFFFFF)))
#ਨਹੀਂਤਾਂ
  ਜੇ ((!n) || ((ਆਕਾਰ(size_t) == ਆਕਾਰ(mz_uint32)) && (new_ਮਾਪ > 0x7FFFFFFF)))
#ਜੇ_ਅੰਤ
    ਵਾਪਸ 0;
  ਜੇ (new_ਮਾਪ > pState->m_mem_ਸਮਰੱਥਾ)
  {
    ਖਾਲੀ *p_New_ਖੰਡ;
    size_t new_ਸਮਰੱਥਾ = MZ_MAX(64, pState->m_mem_ਸਮਰੱਥਾ); ਜਦੋਂ (new_ਸਮਰੱਥਾ < new_ਮਾਪ) new_ਸਮਰੱਥਾ *= 2;
    ਜੇ (ਨਿਰਾ == (p_New_ਖੰਡ = pZip->m_pRealloc(pZip->m_pAlloc_opaque, pState->m_pMem, 1, new_ਸਮਰੱਥਾ)))
      ਵਾਪਸ 0;
    pState->m_pMem = p_New_ਖੰਡ; pState->m_mem_ਸਮਰੱਥਾ = new_ਸਮਰੱਥਾ;
  }
  ਸਮ੍ਰਿਤੀ_ਨਕਲ((mz_uint8 *)pState->m_pMem + file_ofs, pBuf, n);
  pState->m_mem_ਮਾਪ = (size_t)new_ਮਾਪ;
  ਵਾਪਸ n;
}

mz_bool mz_zip_writer_init_ਢੇਰ(mz_zip_archive *pZip, size_t ਮਾਪ_ਮੰਜ਼ਿਲ_reserve_at_beginning, size_t initial_ਵੰਡ_ਮਾਪ)
{
  pZip->m_pWrite = mz_zip_ਢੇਰ_write_func;
  pZip->m_pIO_opaque = pZip;
  ਜੇ (!mz_zip_writer_init(pZip, ਮਾਪ_ਮੰਜ਼ਿਲ_reserve_at_beginning))
    ਵਾਪਸ MZ_FALSE;
  ਜੇ (0 != (initial_ਵੰਡ_ਮਾਪ = MZ_MAX(initial_ਵੰਡ_ਮਾਪ, ਮਾਪ_ਮੰਜ਼ਿਲ_reserve_at_beginning)))
  {
    ਜੇ (ਨਿਰਾ == (pZip->m_pState->m_pMem = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, initial_ਵੰਡ_ਮਾਪ)))
    {
      mz_zip_writer_ਸਿਰਾ(pZip);
      ਵਾਪਸ MZ_FALSE;
    }
    pZip->m_pState->m_mem_ਸਮਰੱਥਾ = initial_ਵੰਡ_ਮਾਪ;
  }
  ਵਾਪਸ MZ_TRUE;
}

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_STDIO
ਸਥਿਰ size_t mz_zip_file_write_func(ਖਾਲੀ *pOpaque, mz_uint64 file_ofs, ਅਚਲ ਖਾਲੀ *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_int64 cur_ofs = MZ_FTELL64(pZip->m_pState->m_pFile);
  ਜੇ (((mz_int64)file_ofs < 0) || (((cur_ofs != (mz_int64)file_ofs)) && (MZ_FSEEK64(pZip->m_pState->m_pFile, (mz_int64)file_ofs, SEEK_SET))))
    ਵਾਪਸ 0;
  ਵਾਪਸ MZ_FWRITE(pBuf, 1, n, pZip->m_pState->m_pFile);
}

mz_bool mz_zip_writer_init_file(mz_zip_archive *pZip, ਅਚਲ ਅੱਖਰ *pFilename, mz_uint64 ਮਾਪ_ਮੰਜ਼ਿਲ_reserve_at_beginning)
{
  MZ_FILE *pFile;
  pZip->m_pWrite = mz_zip_file_write_func;
  pZip->m_pIO_opaque = pZip;
  ਜੇ (!mz_zip_writer_init(pZip, ਮਾਪ_ਮੰਜ਼ਿਲ_reserve_at_beginning))
    ਵਾਪਸ MZ_FALSE;
  ਜੇ (ਨਿਰਾ == (pFile = MZ_FOPEN(pFilename, "wb")))
  {
    mz_zip_writer_ਸਿਰਾ(pZip);
    ਵਾਪਸ MZ_FALSE;
  }
  pZip->m_pState->m_pFile = pFile;
  ਜੇ (ਮਾਪ_ਮੰਜ਼ਿਲ_reserve_at_beginning)
  {
    mz_uint64 cur_ofs = 0; ਅੱਖਰ buf[4096]; MZ_CLEAR_ARR(buf);
    ਕਰੋ
    {
      size_t n = (size_t)MZ_MIN(ਆਕਾਰ(buf), ਮਾਪ_ਮੰਜ਼ਿਲ_reserve_at_beginning);
      ਜੇ (pZip->m_pWrite(pZip->m_pIO_opaque, cur_ofs, buf, n) != n)
      {
        mz_zip_writer_ਸਿਰਾ(pZip);
        ਵਾਪਸ MZ_FALSE;
      }
      cur_ofs += n; ਮਾਪ_ਮੰਜ਼ਿਲ_reserve_at_beginning -= n;
    } ਜਦੋਂ (ਮਾਪ_ਮੰਜ਼ਿਲ_reserve_at_beginning);
  }
  ਵਾਪਸ MZ_TRUE;
}
#ਜੇ_ਅੰਤ // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_writer_init_from_reader(mz_zip_archive *pZip, ਅਚਲ ਅੱਖਰ *pFilename)
{
  mz_zip_ਅੰਦਰੂਨੀ_state *pState;
  ਜੇ ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_ਬਹੁਲਕ != MZ_ZIP_ਬਹੁਲਕ_READING))
    ਵਾਪਸ MZ_FALSE;
  // No sense in trying to write to an archive that's already at the support max size
  ਜੇ ((pZip->m_ਕੁੱਲ_files == 0xFFFF) || ((pZip->m_archive_ਮਾਪ + MZ_ZIP_CENTRAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ + MZ_ZIP_LOCAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ) > 0xFFFFFFFF))
    ਵਾਪਸ MZ_FALSE;

  pState = pZip->m_pState;

  ਜੇ (pState->m_pFile)
  {
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_STDIO
    pFilename; ਵਾਪਸ MZ_FALSE;
#ਨਹੀਂਤਾਂ
    // Archive is being read from stdio - try to reopen as writable.
    ਜੇ (pZip->m_pIO_opaque != pZip)
      ਵਾਪਸ MZ_FALSE;
    ਜੇ (!pFilename)
      ਵਾਪਸ MZ_FALSE;
    pZip->m_pWrite = mz_zip_file_write_func;
    ਜੇ (ਨਿਰਾ == (pState->m_pFile = MZ_FREOPEN(pFilename, "r+b", pState->m_pFile)))
    {
      // The mz_zip_archive is now in a bogus state because pState->m_pFile is NULL, so just close it.
      mz_zip_reader_ਸਿਰਾ(pZip);
      ਵਾਪਸ MZ_FALSE;
    }
#ਜੇ_ਅੰਤ // #ifdef MINIZ_NO_STDIO
  }
  ਨਹੀਂਤਾਂ ਜੇ (pState->m_pMem)
  {
    // Archive lives in a memory block. Assume it's from the heap that we can resize using the realloc callback.
    ਜੇ (pZip->m_pIO_opaque != pZip)
      ਵਾਪਸ MZ_FALSE;
    pState->m_mem_ਸਮਰੱਥਾ = pState->m_mem_ਮਾਪ;
    pZip->m_pWrite = mz_zip_ਢੇਰ_write_func;
  }
  // Archive is being read via a user provided read function - make sure the user has specified a write function too.
  ਨਹੀਂਤਾਂ ਜੇ (!pZip->m_pWrite)
    ਵਾਪਸ MZ_FALSE;

  // Start writing new files at the archive's current central directory location.
  pZip->m_archive_ਮਾਪ = pZip->m_central_directory_file_ofs;
  pZip->m_zip_ਬਹੁਲਕ = MZ_ZIP_ਬਹੁਲਕ_WRITING;
  pZip->m_central_directory_file_ofs = 0;

  ਵਾਪਸ MZ_TRUE;
}

mz_bool mz_zip_writer_ਜੋੜੋ_mem(mz_zip_archive *pZip, ਅਚਲ ਅੱਖਰ *pArchive_name, ਅਚਲ ਖਾਲੀ *pBuf, size_t buf_ਮਾਪ_2, mz_uint level_and_flags)
{
  ਵਾਪਸ mz_zip_writer_ਜੋੜੋ_mem_ex(pZip, pArchive_name, pBuf, buf_ਮਾਪ_2, ਨਿਰਾ, 0, level_and_flags, 0, 0);
}

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
  mz_zip_archive *m_pZip;
  mz_uint64 m_cur_archive_file_ofs;
  mz_uint64 m_comp_ਮਾਪ;
} mz_zip_writer_ਜੋੜੋ_state;

ਸਥਿਰ mz_bool mz_zip_writer_ਜੋੜੋ_put_buf_callback(ਅਚਲ ਖਾਲੀ* pBuf, ਪੂਰਨ len, ਖਾਲੀ *pUser)
{
  mz_zip_writer_ਜੋੜੋ_state *pState = (mz_zip_writer_ਜੋੜੋ_state *)pUser;
  ਜੇ ((ਪੂਰਨ)pState->m_pZip->m_pWrite(pState->m_pZip->m_pIO_opaque, pState->m_cur_archive_file_ofs, pBuf, len) != len)
    ਵਾਪਸ MZ_FALSE;
  pState->m_cur_archive_file_ofs += len;
  pState->m_comp_ਮਾਪ += len;
  ਵਾਪਸ MZ_TRUE;
}

ਸਥਿਰ mz_bool mz_zip_writer_create_local_dir_ਸਿਰਲੇਖ(mz_zip_archive *pZip, mz_uint8 *pDst, mz_uint16 filename_ਮਾਪ, mz_uint16 extra_ਮਾਪ, mz_uint64 uncomp_ਮਾਪ, mz_uint64 comp_ਮਾਪ, mz_uint32 uncomp_ਚੱਕਰੀ_ਜਾਂਚ_32, mz_uint16 ਵਿਧੀ, mz_uint16 ਦੋਆਧਾਰੀ_ਅੰਕ_flags, mz_uint16 dos_ਸਮਾਂ, mz_uint16 dos_date)
{
  (ਖਾਲੀ)pZip;
  memset(pDst, 0, MZ_ZIP_LOCAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_SIG_OFS, MZ_ZIP_LOCAL_DIR_ਸਿਰਲੇਖ_SIG);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_ਸੰਸਕਰਣ_NEEDED_OFS, ਵਿਧੀ ? 20 : 0);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_ਦੋਆਧਾਰੀ_ਅੰਕ_FLAG_OFS, ਦੋਆਧਾਰੀ_ਅੰਕ_flags);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_ਵਿਧੀ_OFS, ਵਿਧੀ);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILE_ਸਮਾਂ_OFS, dos_ਸਮਾਂ);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILE_DATE_OFS, dos_date);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_ਚੱਕਰੀ_ਜਾਂਚ_32_OFS, uncomp_ਚੱਕਰੀ_ਜਾਂਚ_32);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_COMPRESSED_ਮਾਪ_OFS, comp_ਮਾਪ);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_DECOMPRESSED_ਮਾਪ_OFS, uncomp_ਮਾਪ);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILENAME_LEN_OFS, filename_ਮਾਪ);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_EXTRA_LEN_OFS, extra_ਮਾਪ);
  ਵਾਪਸ MZ_TRUE;
}

ਸਥਿਰ mz_bool mz_zip_writer_create_central_dir_ਸਿਰਲੇਖ(mz_zip_archive *pZip, mz_uint8 *pDst, mz_uint16 filename_ਮਾਪ, mz_uint16 extra_ਮਾਪ, mz_uint16 comment_ਮਾਪ, mz_uint64 uncomp_ਮਾਪ, mz_uint64 comp_ਮਾਪ, mz_uint32 uncomp_ਚੱਕਰੀ_ਜਾਂਚ_32, mz_uint16 ਵਿਧੀ, mz_uint16 ਦੋਆਧਾਰੀ_ਅੰਕ_flags, mz_uint16 dos_ਸਮਾਂ, mz_uint16 dos_date, mz_uint64 local_ਸਿਰਲੇਖ_ofs, mz_uint32 ext_ਗੁਣ)
{
  (ਖਾਲੀ)pZip;
  memset(pDst, 0, MZ_ZIP_CENTRAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_SIG_OFS, MZ_ZIP_CENTRAL_DIR_ਸਿਰਲੇਖ_SIG);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_ਸੰਸਕਰਣ_NEEDED_OFS, ਵਿਧੀ ? 20 : 0);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_ਦੋਆਧਾਰੀ_ਅੰਕ_FLAG_OFS, ਦੋਆਧਾਰੀ_ਅੰਕ_flags);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_ਵਿਧੀ_OFS, ਵਿਧੀ);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILE_ਸਮਾਂ_OFS, dos_ਸਮਾਂ);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILE_DATE_OFS, dos_date);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_ਚੱਕਰੀ_ਜਾਂਚ_32_OFS, uncomp_ਚੱਕਰੀ_ਜਾਂਚ_32);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_COMPRESSED_ਮਾਪ_OFS, comp_ਮਾਪ);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_DECOMPRESSED_ਮਾਪ_OFS, uncomp_ਮਾਪ);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILENAME_LEN_OFS, filename_ਮਾਪ);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_EXTRA_LEN_OFS, extra_ਮਾਪ);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_COMMENT_LEN_OFS, comment_ਮਾਪ);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS, ext_ਗੁਣ);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_LOCAL_ਸਿਰਲੇਖ_OFS, local_ਸਿਰਲੇਖ_ofs);
  ਵਾਪਸ MZ_TRUE;
}

ਸਥਿਰ mz_bool mz_zip_writer_ਜੋੜੋ_ਮੰਜ਼ਿਲ_central_dir(mz_zip_archive *pZip, ਅਚਲ ਅੱਖਰ *pFilename, mz_uint16 filename_ਮਾਪ, ਅਚਲ ਖਾਲੀ *pExtra, mz_uint16 extra_ਮਾਪ, ਅਚਲ ਖਾਲੀ *pComment, mz_uint16 comment_ਮਾਪ, mz_uint64 uncomp_ਮਾਪ, mz_uint64 comp_ਮਾਪ, mz_uint32 uncomp_ਚੱਕਰੀ_ਜਾਂਚ_32, mz_uint16 ਵਿਧੀ, mz_uint16 ਦੋਆਧਾਰੀ_ਅੰਕ_flags, mz_uint16 dos_ਸਮਾਂ, mz_uint16 dos_date, mz_uint64 local_ਸਿਰਲੇਖ_ofs, mz_uint32 ext_ਗੁਣ)
{
  mz_zip_ਅੰਦਰੂਨੀ_state *pState = pZip->m_pState;
  mz_uint32 central_dir_ofs = (mz_uint32)pState->m_central_dir.m_ਮਾਪ;
  size_t orig_central_dir_ਮਾਪ = pState->m_central_dir.m_ਮਾਪ;
  mz_uint8 central_dir_ਸਿਰਲੇਖ[MZ_ZIP_CENTRAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ];

  // No zip64 support yet
  ਜੇ ((local_ਸਿਰਲੇਖ_ofs > 0xFFFFFFFF) || (((mz_uint64)pState->m_central_dir.m_ਮਾਪ + MZ_ZIP_CENTRAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ + filename_ਮਾਪ + extra_ਮਾਪ + comment_ਮਾਪ) > 0xFFFFFFFF))
    ਵਾਪਸ MZ_FALSE;

  ਜੇ (!mz_zip_writer_create_central_dir_ਸਿਰਲੇਖ(pZip, central_dir_ਸਿਰਲੇਖ, filename_ਮਾਪ, extra_ਮਾਪ, comment_ਮਾਪ, uncomp_ਮਾਪ, comp_ਮਾਪ, uncomp_ਚੱਕਰੀ_ਜਾਂਚ_32, ਵਿਧੀ, ਦੋਆਧਾਰੀ_ਅੰਕ_flags, dos_ਸਮਾਂ, dos_date, local_ਸਿਰਲੇਖ_ofs, ext_ਗੁਣ))
    ਵਾਪਸ MZ_FALSE;

  ਜੇ ((!mz_zip_array_ਧੱਕੋ_ਪਿੱਠ(pZip, &pState->m_central_dir, central_dir_ਸਿਰਲੇਖ, MZ_ZIP_CENTRAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ)) ||
      (!mz_zip_array_ਧੱਕੋ_ਪਿੱਠ(pZip, &pState->m_central_dir, pFilename, filename_ਮਾਪ)) ||
      (!mz_zip_array_ਧੱਕੋ_ਪਿੱਠ(pZip, &pState->m_central_dir, pExtra, extra_ਮਾਪ)) ||
      (!mz_zip_array_ਧੱਕੋ_ਪਿੱਠ(pZip, &pState->m_central_dir, pComment, comment_ਮਾਪ)) ||
      (!mz_zip_array_ਧੱਕੋ_ਪਿੱਠ(pZip, &pState->m_central_dir_offsets, &central_dir_ofs, 1)))
  {
    // Try to push the central directory array back into its original state.
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_ਮਾਪ, MZ_FALSE);
    ਵਾਪਸ MZ_FALSE;
  }

  ਵਾਪਸ MZ_TRUE;
}

ਸਥਿਰ mz_bool mz_zip_writer_validate_archive_name(ਅਚਲ ਅੱਖਰ *pArchive_name)
{
  // Basic ZIP archive filename validity checks: Valid filenames cannot start with a forward slash, cannot contain a drive letter, and cannot use DOS-style backward slashes.
  ਜੇ (*pArchive_name == '/')
    ਵਾਪਸ MZ_FALSE;
  ਜਦੋਂ (*pArchive_name)
  {
    ਜੇ ((*pArchive_name == '\\') || (*pArchive_name == ':'))
      ਵਾਪਸ MZ_FALSE;
    pArchive_name++;
  }
  ਵਾਪਸ MZ_TRUE;
}

ਸਥਿਰ mz_uint mz_zip_writer_compute_padding_needed_for_file_alignment(mz_zip_archive *pZip)
{
  mz_uint32 n;
  ਜੇ (!pZip->m_file_ਵਿੱਥ_alignment)
    ਵਾਪਸ 0;
  n = (mz_uint32)(pZip->m_archive_ਮਾਪ & (pZip->m_file_ਵਿੱਥ_alignment - 1));
  ਵਾਪਸ (pZip->m_file_ਵਿੱਥ_alignment - n) & (pZip->m_file_ਵਿੱਥ_alignment - 1);
}

ਸਥਿਰ mz_bool mz_zip_writer_write_zeros(mz_zip_archive *pZip, mz_uint64 cur_file_ofs, mz_uint32 n)
{
  ਅੱਖਰ buf[4096];
  memset(buf, 0, MZ_MIN(ਆਕਾਰ(buf), n));
  ਜਦੋਂ (n)
  {
    mz_uint32 s = MZ_MIN(ਆਕਾਰ(buf), n);
    ਜੇ (pZip->m_pWrite(pZip->m_pIO_opaque, cur_file_ofs, buf, s) != s)
      ਵਾਪਸ MZ_FALSE;
    cur_file_ofs += s; n -= s;
  }
  ਵਾਪਸ MZ_TRUE;
}

mz_bool mz_zip_writer_ਜੋੜੋ_mem_ex(mz_zip_archive *pZip, ਅਚਲ ਅੱਖਰ *pArchive_name, ਅਚਲ ਖਾਲੀ *pBuf, size_t buf_ਮਾਪ_2, ਅਚਲ ਖਾਲੀ *pComment, mz_uint16 comment_ਮਾਪ, mz_uint level_and_flags, mz_uint64 uncomp_ਮਾਪ, mz_uint32 uncomp_ਚੱਕਰੀ_ਜਾਂਚ_32)
{
  mz_uint16 ਵਿਧੀ = 0, dos_ਸਮਾਂ = 0, dos_date = 0;
  mz_uint level, ext_ਗੁਣ = 0, ਅੰਕ_alignment_padding_ਬਾਈਟਾਂ;
  mz_uint64 local_dir_ਸਿਰਲੇਖ_ofs = pZip->m_archive_ਮਾਪ, cur_archive_file_ofs = pZip->m_archive_ਮਾਪ, comp_ਮਾਪ = 0;
  size_t archive_name_ਮਾਪ;
  mz_uint8 local_dir_ਸਿਰਲੇਖ[MZ_ZIP_LOCAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ];
  tdefl_compressor *pComp = ਨਿਰਾ;
  mz_bool store_ਅੰਕੜੇ_uncompressed;
  mz_zip_ਅੰਦਰੂਨੀ_state *pState;

  ਜੇ ((ਪੂਰਨ)level_and_flags < 0)
    level_and_flags = MZ_DEFAULT_LEVEL;
  level = level_and_flags & 0xF;
  store_ਅੰਕੜੇ_uncompressed = ((!level) || (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_ਅੰਕੜੇ));

  ਜੇ ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_ਬਹੁਲਕ != MZ_ZIP_ਬਹੁਲਕ_WRITING) || ((buf_ਮਾਪ_2) && (!pBuf)) || (!pArchive_name) || ((comment_ਮਾਪ) && (!pComment)) || (pZip->m_ਕੁੱਲ_files == 0xFFFF) || (level > MZ_UBER_COMPRESSION))
    ਵਾਪਸ MZ_FALSE;

  pState = pZip->m_pState;

  ਜੇ ((!(level_and_flags & MZ_ZIP_FLAG_COMPRESSED_ਅੰਕੜੇ)) && (uncomp_ਮਾਪ))
    ਵਾਪਸ MZ_FALSE;
  // No zip64 support yet
  ਜੇ ((buf_ਮਾਪ_2 > 0xFFFFFFFF) || (uncomp_ਮਾਪ > 0xFFFFFFFF))
    ਵਾਪਸ MZ_FALSE;
  ਜੇ (!mz_zip_writer_validate_archive_name(pArchive_name))
    ਵਾਪਸ MZ_FALSE;

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_ਸਮਾਂ
  {
    ਸਮਾਂ_t cur_ਸਮਾਂ; ਸਮਾਂ(&cur_ਸਮਾਂ);
    mz_zip_ਸਮਾਂ_ਮੰਜ਼ਿਲ_dos_ਸਮਾਂ(cur_ਸਮਾਂ, &dos_ਸਮਾਂ, &dos_date);
  }
#ਜੇ_ਅੰਤ // #ifndef MINIZ_NO_TIME

  archive_name_ਮਾਪ = ਲੜੀ_ਲੰਬਾਈ(pArchive_name);
  ਜੇ (archive_name_ਮਾਪ > 0xFFFF)
    ਵਾਪਸ MZ_FALSE;

  ਅੰਕ_alignment_padding_ਬਾਈਟਾਂ = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  ਜੇ ((pZip->m_ਕੁੱਲ_files == 0xFFFF) || ((pZip->m_archive_ਮਾਪ + ਅੰਕ_alignment_padding_ਬਾਈਟਾਂ + MZ_ZIP_LOCAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ + MZ_ZIP_CENTRAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ + comment_ਮਾਪ + archive_name_ਮਾਪ) > 0xFFFFFFFF))
    ਵਾਪਸ MZ_FALSE;

  ਜੇ ((archive_name_ਮਾਪ) && (pArchive_name[archive_name_ਮਾਪ - 1] == '/'))
  {
    // Set DOS Subdirectory attribute bit.
    ext_ਗੁਣ |= 0x10;
    // Subdirectories cannot contain data.
    ਜੇ ((buf_ਮਾਪ_2) || (uncomp_ਮਾਪ))
      ਵਾਪਸ MZ_FALSE;
  }

  // Try to do any allocations before writing to the archive, so if an allocation fails the file remains unmodified. (A good idea if we're doing an in-place modification.)
  ਜੇ ((!mz_zip_array_ensure_ਗੁੰਜਾਇਸ਼(pZip, &pState->m_central_dir, MZ_ZIP_CENTRAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ + archive_name_ਮਾਪ + comment_ਮਾਪ)) || (!mz_zip_array_ensure_ਗੁੰਜਾਇਸ਼(pZip, &pState->m_central_dir_offsets, 1)))
    ਵਾਪਸ MZ_FALSE;

  ਜੇ ((!store_ਅੰਕੜੇ_uncompressed) && (buf_ਮਾਪ_2))
  {
    ਜੇ (ਨਿਰਾ == (pComp = (tdefl_compressor *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, ਆਕਾਰ(tdefl_compressor))))
      ਵਾਪਸ MZ_FALSE;
  }

  ਜੇ (!mz_zip_writer_write_zeros(pZip, cur_archive_file_ofs, ਅੰਕ_alignment_padding_ਬਾਈਟਾਂ + ਆਕਾਰ(local_dir_ਸਿਰਲੇਖ)))
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
    ਵਾਪਸ MZ_FALSE;
  }
  local_dir_ਸਿਰਲੇਖ_ofs += ਅੰਕ_alignment_padding_ਬਾਈਟਾਂ;
  ਜੇ (pZip->m_file_ਵਿੱਥ_alignment) { MZ_ASSERT((local_dir_ਸਿਰਲੇਖ_ofs & (pZip->m_file_ਵਿੱਥ_alignment - 1)) == 0); }
  cur_archive_file_ofs += ਅੰਕ_alignment_padding_ਬਾਈਟਾਂ + ਆਕਾਰ(local_dir_ਸਿਰਲੇਖ);

  MZ_CLEAR_ARR(local_dir_ਸਿਰਲੇਖ);
  ਜੇ (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pArchive_name, archive_name_ਮਾਪ) != archive_name_ਮਾਪ)
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
    ਵਾਪਸ MZ_FALSE;
  }
  cur_archive_file_ofs += archive_name_ਮਾਪ;

  ਜੇ (!(level_and_flags & MZ_ZIP_FLAG_COMPRESSED_ਅੰਕੜੇ))
  {
    uncomp_ਚੱਕਰੀ_ਜਾਂਚ_32 = (mz_uint32)mz_ਚੱਕਰੀ_ਜਾਂਚ_32(MZ_ਚੱਕਰੀ_ਜਾਂਚ_32_INIT, (ਅਚਲ mz_uint8*)pBuf, buf_ਮਾਪ_2);
    uncomp_ਮਾਪ = buf_ਮਾਪ_2;
    ਜੇ (uncomp_ਮਾਪ <= 3)
    {
      level = 0;
      store_ਅੰਕੜੇ_uncompressed = MZ_TRUE;
    }
  }

  ਜੇ (store_ਅੰਕੜੇ_uncompressed)
  {
    ਜੇ (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pBuf, buf_ਮਾਪ_2) != buf_ਮਾਪ_2)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
      ਵਾਪਸ MZ_FALSE;
    }

    cur_archive_file_ofs += buf_ਮਾਪ_2;
    comp_ਮਾਪ = buf_ਮਾਪ_2;

    ਜੇ (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_ਅੰਕੜੇ)
      ਵਿਧੀ = MZ_DEFLATED;
  }
  ਨਹੀਂਤਾਂ ਜੇ (buf_ਮਾਪ_2)
  {
    mz_zip_writer_ਜੋੜੋ_state state;

    state.m_pZip = pZip;
    state.m_cur_archive_file_ofs = cur_archive_file_ofs;
    state.m_comp_ਮਾਪ = 0;

    ਜੇ ((tdefl_init(pComp, mz_zip_writer_ਜੋੜੋ_put_buf_callback, &state, tdefl_create_comp_flags_from_zip_params(level, -15, MZ_DEFAULT_STRATEGY)) != TDEFL_ਸਥਿਤੀ_OKAY) ||
        (tdefl_compress_ਬਫਰ(pComp, pBuf, buf_ਮਾਪ_2, TDEFL_ਅੰਤ) != TDEFL_ਸਥਿਤੀ_ਪੂਰਾ))
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
      ਵਾਪਸ MZ_FALSE;
    }

    comp_ਮਾਪ = state.m_comp_ਮਾਪ;
    cur_archive_file_ofs = state.m_cur_archive_file_ofs;

    ਵਿਧੀ = MZ_DEFLATED;
  }

  pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
  pComp = ਨਿਰਾ;

  // no zip64 support yet
  ਜੇ ((comp_ਮਾਪ > 0xFFFFFFFF) || (cur_archive_file_ofs > 0xFFFFFFFF))
    ਵਾਪਸ MZ_FALSE;

  ਜੇ (!mz_zip_writer_create_local_dir_ਸਿਰਲੇਖ(pZip, local_dir_ਸਿਰਲੇਖ, (mz_uint16)archive_name_ਮਾਪ, 0, uncomp_ਮਾਪ, comp_ਮਾਪ, uncomp_ਚੱਕਰੀ_ਜਾਂਚ_32, ਵਿਧੀ, 0, dos_ਸਮਾਂ, dos_date))
    ਵਾਪਸ MZ_FALSE;

  ਜੇ (pZip->m_pWrite(pZip->m_pIO_opaque, local_dir_ਸਿਰਲੇਖ_ofs, local_dir_ਸਿਰਲੇਖ, ਆਕਾਰ(local_dir_ਸਿਰਲੇਖ)) != ਆਕਾਰ(local_dir_ਸਿਰਲੇਖ))
    ਵਾਪਸ MZ_FALSE;

  ਜੇ (!mz_zip_writer_ਜੋੜੋ_ਮੰਜ਼ਿਲ_central_dir(pZip, pArchive_name, (mz_uint16)archive_name_ਮਾਪ, ਨਿਰਾ, 0, pComment, comment_ਮਾਪ, uncomp_ਮਾਪ, comp_ਮਾਪ, uncomp_ਚੱਕਰੀ_ਜਾਂਚ_32, ਵਿਧੀ, 0, dos_ਸਮਾਂ, dos_date, local_dir_ਸਿਰਲੇਖ_ofs, ext_ਗੁਣ))
    ਵਾਪਸ MZ_FALSE;

  pZip->m_ਕੁੱਲ_files++;
  pZip->m_archive_ਮਾਪ = cur_archive_file_ofs;

  ਵਾਪਸ MZ_TRUE;
}

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_STDIO
mz_bool mz_zip_writer_ਜੋੜੋ_file(mz_zip_archive *pZip, ਅਚਲ ਅੱਖਰ *pArchive_name, ਅਚਲ ਅੱਖਰ *pSrc_filename, ਅਚਲ ਖਾਲੀ *pComment, mz_uint16 comment_ਮਾਪ, mz_uint level_and_flags)
{
  mz_uint uncomp_ਚੱਕਰੀ_ਜਾਂਚ_32 = MZ_ਚੱਕਰੀ_ਜਾਂਚ_32_INIT, level, ਅੰਕ_alignment_padding_ਬਾਈਟਾਂ;
  mz_uint16 ਵਿਧੀ = 0, dos_ਸਮਾਂ = 0, dos_date = 0, ext_ਗੁਣ = 0;
  mz_uint64 local_dir_ਸਿਰਲੇਖ_ofs = pZip->m_archive_ਮਾਪ, cur_archive_file_ofs = pZip->m_archive_ਮਾਪ, uncomp_ਮਾਪ = 0, comp_ਮਾਪ = 0;
  size_t archive_name_ਮਾਪ;
  mz_uint8 local_dir_ਸਿਰਲੇਖ[MZ_ZIP_LOCAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ];
  MZ_FILE *pSrc_file = ਨਿਰਾ;

  ਜੇ ((ਪੂਰਨ)level_and_flags < 0)
    level_and_flags = MZ_DEFAULT_LEVEL;
  level = level_and_flags & 0xF;

  ਜੇ ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_ਬਹੁਲਕ != MZ_ZIP_ਬਹੁਲਕ_WRITING) || (!pArchive_name) || ((comment_ਮਾਪ) && (!pComment)) || (level > MZ_UBER_COMPRESSION))
    ਵਾਪਸ MZ_FALSE;
  ਜੇ (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_ਅੰਕੜੇ)
    ਵਾਪਸ MZ_FALSE;
  ਜੇ (!mz_zip_writer_validate_archive_name(pArchive_name))
    ਵਾਪਸ MZ_FALSE;

  archive_name_ਮਾਪ = ਲੜੀ_ਲੰਬਾਈ(pArchive_name);
  ਜੇ (archive_name_ਮਾਪ > 0xFFFF)
    ਵਾਪਸ MZ_FALSE;

  ਅੰਕ_alignment_padding_ਬਾਈਟਾਂ = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  ਜੇ ((pZip->m_ਕੁੱਲ_files == 0xFFFF) || ((pZip->m_archive_ਮਾਪ + ਅੰਕ_alignment_padding_ਬਾਈਟਾਂ + MZ_ZIP_LOCAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ + MZ_ZIP_CENTRAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ + comment_ਮਾਪ + archive_name_ਮਾਪ) > 0xFFFFFFFF))
    ਵਾਪਸ MZ_FALSE;

  ਜੇ (!mz_zip_get_file_modified_ਸਮਾਂ(pSrc_filename, &dos_ਸਮਾਂ, &dos_date))
    ਵਾਪਸ MZ_FALSE;

  pSrc_file = MZ_FOPEN(pSrc_filename, "rb");
  ਜੇ (!pSrc_file)
    ਵਾਪਸ MZ_FALSE;
  MZ_FSEEK64(pSrc_file, 0, SEEK_END);
  uncomp_ਮਾਪ = MZ_FTELL64(pSrc_file);
  MZ_FSEEK64(pSrc_file, 0, SEEK_SET);

  ਜੇ (uncomp_ਮਾਪ > 0xFFFFFFFF)
  {
    // No zip64 support yet
    MZ_FCLOSE(pSrc_file);
    ਵਾਪਸ MZ_FALSE;
  }
  ਜੇ (uncomp_ਮਾਪ <= 3)
    level = 0;

  ਜੇ (!mz_zip_writer_write_zeros(pZip, cur_archive_file_ofs, ਅੰਕ_alignment_padding_ਬਾਈਟਾਂ + ਆਕਾਰ(local_dir_ਸਿਰਲੇਖ)))
  {
    MZ_FCLOSE(pSrc_file);
    ਵਾਪਸ MZ_FALSE;
  }
  local_dir_ਸਿਰਲੇਖ_ofs += ਅੰਕ_alignment_padding_ਬਾਈਟਾਂ;
  ਜੇ (pZip->m_file_ਵਿੱਥ_alignment) { MZ_ASSERT((local_dir_ਸਿਰਲੇਖ_ofs & (pZip->m_file_ਵਿੱਥ_alignment - 1)) == 0); }
  cur_archive_file_ofs += ਅੰਕ_alignment_padding_ਬਾਈਟਾਂ + ਆਕਾਰ(local_dir_ਸਿਰਲੇਖ);

  MZ_CLEAR_ARR(local_dir_ਸਿਰਲੇਖ);
  ਜੇ (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pArchive_name, archive_name_ਮਾਪ) != archive_name_ਮਾਪ)
  {
    MZ_FCLOSE(pSrc_file);
    ਵਾਪਸ MZ_FALSE;
  }
  cur_archive_file_ofs += archive_name_ਮਾਪ;

  ਜੇ (uncomp_ਮਾਪ)
  {
    mz_uint64 uncomp_ਬਚਿਆ = uncomp_ਮਾਪ;
    ਖਾਲੀ *pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, MZ_ZIP_MAX_IO_BUF_ਮਾਪ);
    ਜੇ (!pRead_buf)
    {
      MZ_FCLOSE(pSrc_file);
      ਵਾਪਸ MZ_FALSE;
    }

    ਜੇ (!level)
    {
      ਜਦੋਂ (uncomp_ਬਚਿਆ)
      {
        mz_uint n = (mz_uint)MZ_MIN(MZ_ZIP_MAX_IO_BUF_ਮਾਪ, uncomp_ਬਚਿਆ);
        ਜੇ ((MZ_FREAD(pRead_buf, 1, n, pSrc_file) != n) || (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pRead_buf, n) != n))
        {
          pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
          MZ_FCLOSE(pSrc_file);
          ਵਾਪਸ MZ_FALSE;
        }
        uncomp_ਚੱਕਰੀ_ਜਾਂਚ_32 = (mz_uint32)mz_ਚੱਕਰੀ_ਜਾਂਚ_32(uncomp_ਚੱਕਰੀ_ਜਾਂਚ_32, (ਅਚਲ mz_uint8 *)pRead_buf, n);
        uncomp_ਬਚਿਆ -= n;
        cur_archive_file_ofs += n;
      }
      comp_ਮਾਪ = uncomp_ਮਾਪ;
    }
    ਨਹੀਂਤਾਂ
    {
      mz_bool ਨਤੀਜਾ = MZ_FALSE;
      mz_zip_writer_ਜੋੜੋ_state state;
      tdefl_compressor *pComp = (tdefl_compressor *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, ਆਕਾਰ(tdefl_compressor));
      ਜੇ (!pComp)
      {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        ਵਾਪਸ MZ_FALSE;
      }

      state.m_pZip = pZip;
      state.m_cur_archive_file_ofs = cur_archive_file_ofs;
      state.m_comp_ਮਾਪ = 0;

      ਜੇ (tdefl_init(pComp, mz_zip_writer_ਜੋੜੋ_put_buf_callback, &state, tdefl_create_comp_flags_from_zip_params(level, -15, MZ_DEFAULT_STRATEGY)) != TDEFL_ਸਥਿਤੀ_OKAY)
      {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        ਵਾਪਸ MZ_FALSE;
      }

      ਲਈ ( ; ; )
      {
        size_t ਵਿੱਚ_buf_ਮਾਪ = (mz_uint32)MZ_MIN(uncomp_ਬਚਿਆ, MZ_ZIP_MAX_IO_BUF_ਮਾਪ);
        tdefl_ਸਥਿਤੀ ਸਥਿਤੀ;

        ਜੇ (MZ_FREAD(pRead_buf, 1, ਵਿੱਚ_buf_ਮਾਪ, pSrc_file) != ਵਿੱਚ_buf_ਮਾਪ)
          ਰੋਕੋ;

        uncomp_ਚੱਕਰੀ_ਜਾਂਚ_32 = (mz_uint32)mz_ਚੱਕਰੀ_ਜਾਂਚ_32(uncomp_ਚੱਕਰੀ_ਜਾਂਚ_32, (ਅਚਲ mz_uint8 *)pRead_buf, ਵਿੱਚ_buf_ਮਾਪ);
        uncomp_ਬਚਿਆ -= ਵਿੱਚ_buf_ਮਾਪ;

        ਸਥਿਤੀ = tdefl_compress_ਬਫਰ(pComp, pRead_buf, ਵਿੱਚ_buf_ਮਾਪ, uncomp_ਬਚਿਆ ? TDEFL_NO_FLUSH : TDEFL_ਅੰਤ);
        ਜੇ (ਸਥਿਤੀ == TDEFL_ਸਥਿਤੀ_ਪੂਰਾ)
        {
          ਨਤੀਜਾ = MZ_TRUE;
          ਰੋਕੋ;
        }
        ਨਹੀਂਤਾਂ ਜੇ (ਸਥਿਤੀ != TDEFL_ਸਥਿਤੀ_OKAY)
          ਰੋਕੋ;
      }

      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);

      ਜੇ (!ਨਤੀਜਾ)
      {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        ਵਾਪਸ MZ_FALSE;
      }

      comp_ਮਾਪ = state.m_comp_ਮਾਪ;
      cur_archive_file_ofs = state.m_cur_archive_file_ofs;

      ਵਿਧੀ = MZ_DEFLATED;
    }

    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
  }

  MZ_FCLOSE(pSrc_file); pSrc_file = ਨਿਰਾ;

  // no zip64 support yet
  ਜੇ ((comp_ਮਾਪ > 0xFFFFFFFF) || (cur_archive_file_ofs > 0xFFFFFFFF))
    ਵਾਪਸ MZ_FALSE;

  ਜੇ (!mz_zip_writer_create_local_dir_ਸਿਰਲੇਖ(pZip, local_dir_ਸਿਰਲੇਖ, (mz_uint16)archive_name_ਮਾਪ, 0, uncomp_ਮਾਪ, comp_ਮਾਪ, uncomp_ਚੱਕਰੀ_ਜਾਂਚ_32, ਵਿਧੀ, 0, dos_ਸਮਾਂ, dos_date))
    ਵਾਪਸ MZ_FALSE;

  ਜੇ (pZip->m_pWrite(pZip->m_pIO_opaque, local_dir_ਸਿਰਲੇਖ_ofs, local_dir_ਸਿਰਲੇਖ, ਆਕਾਰ(local_dir_ਸਿਰਲੇਖ)) != ਆਕਾਰ(local_dir_ਸਿਰਲੇਖ))
    ਵਾਪਸ MZ_FALSE;

  ਜੇ (!mz_zip_writer_ਜੋੜੋ_ਮੰਜ਼ਿਲ_central_dir(pZip, pArchive_name, (mz_uint16)archive_name_ਮਾਪ, ਨਿਰਾ, 0, pComment, comment_ਮਾਪ, uncomp_ਮਾਪ, comp_ਮਾਪ, uncomp_ਚੱਕਰੀ_ਜਾਂਚ_32, ਵਿਧੀ, 0, dos_ਸਮਾਂ, dos_date, local_dir_ਸਿਰਲੇਖ_ofs, ext_ਗੁਣ))
    ਵਾਪਸ MZ_FALSE;

  pZip->m_ਕੁੱਲ_files++;
  pZip->m_archive_ਮਾਪ = cur_archive_file_ofs;

  ਵਾਪਸ MZ_TRUE;
}
#ਜੇ_ਅੰਤ // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_writer_ਜੋੜੋ_from_zip_reader(mz_zip_archive *pZip, mz_zip_archive *p_ਸਰੋਤ_zip, mz_uint file_ਸੂਚਕਾਂਕ)
{
  mz_uint n, ਦੋਆਧਾਰੀ_ਅੰਕ_flags, ਅੰਕ_alignment_padding_ਬਾਈਟਾਂ;
  mz_uint64 comp_ਬਾਈਟਾਂ_ਬਚਿਆ, local_dir_ਸਿਰਲੇਖ_ofs;
  mz_uint64 cur_src_file_ofs, cur_dst_file_ofs;
  mz_uint32 local_ਸਿਰਲੇਖ_u32[(MZ_ZIP_LOCAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ + ਆਕਾਰ(mz_uint32) - 1) / ਆਕਾਰ(mz_uint32)]; mz_uint8 *p_Local_ਸਿਰਲੇਖ = (mz_uint8 *)local_ਸਿਰਲੇਖ_u32;
  mz_uint8 central_ਸਿਰਲੇਖ[MZ_ZIP_CENTRAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ];
  size_t orig_central_dir_ਮਾਪ;
  mz_zip_ਅੰਦਰੂਨੀ_state *pState;
  ਖਾਲੀ *pBuf; ਅਚਲ mz_uint8 *p_Src_central_ਸਿਰਲੇਖ;

  ਜੇ ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_ਬਹੁਲਕ != MZ_ZIP_ਬਹੁਲਕ_WRITING))
    ਵਾਪਸ MZ_FALSE;
  ਜੇ (ਨਿਰਾ == (p_Src_central_ਸਿਰਲੇਖ = mz_zip_reader_get_cdh(p_ਸਰੋਤ_zip, file_ਸੂਚਕਾਂਕ)))
    ਵਾਪਸ MZ_FALSE;
  pState = pZip->m_pState;

  ਅੰਕ_alignment_padding_ਬਾਈਟਾਂ = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  ਜੇ ((pZip->m_ਕੁੱਲ_files == 0xFFFF) || ((pZip->m_archive_ਮਾਪ + ਅੰਕ_alignment_padding_ਬਾਈਟਾਂ + MZ_ZIP_LOCAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ + MZ_ZIP_CENTRAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ) > 0xFFFFFFFF))
    ਵਾਪਸ MZ_FALSE;

  cur_src_file_ofs = MZ_READ_LE32(p_Src_central_ਸਿਰਲੇਖ + MZ_ZIP_CDH_LOCAL_ਸਿਰਲੇਖ_OFS);
  cur_dst_file_ofs = pZip->m_archive_ਮਾਪ;

  ਜੇ (p_ਸਰੋਤ_zip->m_pRead(p_ਸਰੋਤ_zip->m_pIO_opaque, cur_src_file_ofs, p_Local_ਸਿਰਲੇਖ, MZ_ZIP_LOCAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ) != MZ_ZIP_LOCAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ)
    ਵਾਪਸ MZ_FALSE;
  ਜੇ (MZ_READ_LE32(p_Local_ਸਿਰਲੇਖ) != MZ_ZIP_LOCAL_DIR_ਸਿਰਲੇਖ_SIG)
    ਵਾਪਸ MZ_FALSE;
  cur_src_file_ofs += MZ_ZIP_LOCAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ;

  ਜੇ (!mz_zip_writer_write_zeros(pZip, cur_dst_file_ofs, ਅੰਕ_alignment_padding_ਬਾਈਟਾਂ))
    ਵਾਪਸ MZ_FALSE;
  cur_dst_file_ofs += ਅੰਕ_alignment_padding_ਬਾਈਟਾਂ;
  local_dir_ਸਿਰਲੇਖ_ofs = cur_dst_file_ofs;
  ਜੇ (pZip->m_file_ਵਿੱਥ_alignment) { MZ_ASSERT((local_dir_ਸਿਰਲੇਖ_ofs & (pZip->m_file_ਵਿੱਥ_alignment - 1)) == 0); }

  ਜੇ (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, p_Local_ਸਿਰਲੇਖ, MZ_ZIP_LOCAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ) != MZ_ZIP_LOCAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ)
    ਵਾਪਸ MZ_FALSE;
  cur_dst_file_ofs += MZ_ZIP_LOCAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ;

  n = MZ_READ_LE16(p_Local_ਸਿਰਲੇਖ + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p_Local_ਸਿਰਲੇਖ + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  comp_ਬਾਈਟਾਂ_ਬਚਿਆ = n + MZ_READ_LE32(p_Src_central_ਸਿਰਲੇਖ + MZ_ZIP_CDH_COMPRESSED_ਮਾਪ_OFS);

  ਜੇ (ਨਿਰਾ == (pBuf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)MZ_MAX(ਆਕਾਰ(mz_uint32) * 4, MZ_MIN(MZ_ZIP_MAX_IO_BUF_ਮਾਪ, comp_ਬਾਈਟਾਂ_ਬਚਿਆ)))))
    ਵਾਪਸ MZ_FALSE;

  ਜਦੋਂ (comp_ਬਾਈਟਾਂ_ਬਚਿਆ)
  {
    n = (mz_uint)MZ_MIN(MZ_ZIP_MAX_IO_BUF_ਮਾਪ, comp_ਬਾਈਟਾਂ_ਬਚਿਆ);
    ਜੇ (p_ਸਰੋਤ_zip->m_pRead(p_ਸਰੋਤ_zip->m_pIO_opaque, cur_src_file_ofs, pBuf, n) != n)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      ਵਾਪਸ MZ_FALSE;
    }
    cur_src_file_ofs += n;

    ਜੇ (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, pBuf, n) != n)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      ਵਾਪਸ MZ_FALSE;
    }
    cur_dst_file_ofs += n;

    comp_ਬਾਈਟਾਂ_ਬਚਿਆ -= n;
  }

  ਦੋਆਧਾਰੀ_ਅੰਕ_flags = MZ_READ_LE16(p_Local_ਸਿਰਲੇਖ + MZ_ZIP_LDH_ਦੋਆਧਾਰੀ_ਅੰਕ_FLAG_OFS);
  ਜੇ (ਦੋਆਧਾਰੀ_ਅੰਕ_flags & 8)
  {
    // Copy data descriptor
    ਜੇ (p_ਸਰੋਤ_zip->m_pRead(p_ਸਰੋਤ_zip->m_pIO_opaque, cur_src_file_ofs, pBuf, ਆਕਾਰ(mz_uint32) * 4) != ਆਕਾਰ(mz_uint32) * 4)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      ਵਾਪਸ MZ_FALSE;
    }

    n = ਆਕਾਰ(mz_uint32) * ((MZ_READ_LE32(pBuf) == 0x08074b50) ? 4 : 3);
    ਜੇ (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, pBuf, n) != n)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      ਵਾਪਸ MZ_FALSE;
    }

    cur_src_file_ofs += n;
    cur_dst_file_ofs += n;
  }
  pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);

  // no zip64 support yet
  ਜੇ (cur_dst_file_ofs > 0xFFFFFFFF)
    ਵਾਪਸ MZ_FALSE;

  orig_central_dir_ਮਾਪ = pState->m_central_dir.m_ਮਾਪ;

  ਸਮ੍ਰਿਤੀ_ਨਕਲ(central_ਸਿਰਲੇਖ, p_Src_central_ਸਿਰਲੇਖ, MZ_ZIP_CENTRAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ);
  MZ_WRITE_LE32(central_ਸਿਰਲੇਖ + MZ_ZIP_CDH_LOCAL_ਸਿਰਲੇਖ_OFS, local_dir_ਸਿਰਲੇਖ_ofs);
  ਜੇ (!mz_zip_array_ਧੱਕੋ_ਪਿੱਠ(pZip, &pState->m_central_dir, central_ਸਿਰਲੇਖ, MZ_ZIP_CENTRAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ))
    ਵਾਪਸ MZ_FALSE;

  n = MZ_READ_LE16(p_Src_central_ਸਿਰਲੇਖ + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p_Src_central_ਸਿਰਲੇਖ + MZ_ZIP_CDH_EXTRA_LEN_OFS) + MZ_READ_LE16(p_Src_central_ਸਿਰਲੇਖ + MZ_ZIP_CDH_COMMENT_LEN_OFS);
  ਜੇ (!mz_zip_array_ਧੱਕੋ_ਪਿੱਠ(pZip, &pState->m_central_dir, p_Src_central_ਸਿਰਲੇਖ + MZ_ZIP_CENTRAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ, n))
  {
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_ਮਾਪ, MZ_FALSE);
    ਵਾਪਸ MZ_FALSE;
  }

  ਜੇ (pState->m_central_dir.m_ਮਾਪ > 0xFFFFFFFF)
    ਵਾਪਸ MZ_FALSE;
  n = (mz_uint32)orig_central_dir_ਮਾਪ;
  ਜੇ (!mz_zip_array_ਧੱਕੋ_ਪਿੱਠ(pZip, &pState->m_central_dir_offsets, &n, 1))
  {
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_ਮਾਪ, MZ_FALSE);
    ਵਾਪਸ MZ_FALSE;
  }

  pZip->m_ਕੁੱਲ_files++;
  pZip->m_archive_ਮਾਪ = cur_dst_file_ofs;

  ਵਾਪਸ MZ_TRUE;
}

mz_bool mz_zip_writer_finalize_archive(mz_zip_archive *pZip)
{
  mz_zip_ਅੰਦਰੂਨੀ_state *pState;
  mz_uint64 central_dir_ofs, central_dir_ਮਾਪ;
  mz_uint8 hdr[MZ_ZIP_ਸਿਰਾ_ਦਾ_CENTRAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ];

  ਜੇ ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_ਬਹੁਲਕ != MZ_ZIP_ਬਹੁਲਕ_WRITING))
    ਵਾਪਸ MZ_FALSE;

  pState = pZip->m_pState;

  // no zip64 support yet
  ਜੇ ((pZip->m_ਕੁੱਲ_files > 0xFFFF) || ((pZip->m_archive_ਮਾਪ + pState->m_central_dir.m_ਮਾਪ + MZ_ZIP_ਸਿਰਾ_ਦਾ_CENTRAL_DIR_ਸਿਰਲੇਖ_ਮਾਪ) > 0xFFFFFFFF))
    ਵਾਪਸ MZ_FALSE;

  central_dir_ofs = 0;
  central_dir_ਮਾਪ = 0;
  ਜੇ (pZip->m_ਕੁੱਲ_files)
  {
    // Write central directory
    central_dir_ofs = pZip->m_archive_ਮਾਪ;
    central_dir_ਮਾਪ = pState->m_central_dir.m_ਮਾਪ;
    pZip->m_central_directory_file_ofs = central_dir_ofs;
    ਜੇ (pZip->m_pWrite(pZip->m_pIO_opaque, central_dir_ofs, pState->m_central_dir.m_p, (size_t)central_dir_ਮਾਪ) != central_dir_ਮਾਪ)
      ਵਾਪਸ MZ_FALSE;
    pZip->m_archive_ਮਾਪ += central_dir_ਮਾਪ;
  }

  // Write end of central directory record
  MZ_CLEAR_ARR(hdr);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_SIG_OFS, MZ_ZIP_ਸਿਰਾ_ਦਾ_CENTRAL_DIR_ਸਿਰਲੇਖ_SIG);
  MZ_WRITE_LE16(hdr + MZ_ZIP_ECDH_CDIR_ਅੰਕ_ENTRIES_ON_DISK_OFS, pZip->m_ਕੁੱਲ_files);
  MZ_WRITE_LE16(hdr + MZ_ZIP_ECDH_CDIR_ਕੁੱਲ_ENTRIES_OFS, pZip->m_ਕੁੱਲ_files);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_CDIR_ਮਾਪ_OFS, central_dir_ਮਾਪ);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_CDIR_OFS_OFS, central_dir_ofs);

  ਜੇ (pZip->m_pWrite(pZip->m_pIO_opaque, pZip->m_archive_ਮਾਪ, hdr, ਆਕਾਰ(hdr)) != ਆਕਾਰ(hdr))
    ਵਾਪਸ MZ_FALSE;
#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_STDIO
  ਜੇ ((pState->m_pFile) && (MZ_FFLUSH(pState->m_pFile) == EOF))
    ਵਾਪਸ MZ_FALSE;
#ਜੇ_ਅੰਤ // #ifndef MINIZ_NO_STDIO

  pZip->m_archive_ਮਾਪ += ਆਕਾਰ(hdr);

  pZip->m_zip_ਬਹੁਲਕ = MZ_ZIP_ਬਹੁਲਕ_WRITING_HAS_BEEN_FINALIZED;
  ਵਾਪਸ MZ_TRUE;
}

mz_bool mz_zip_writer_finalize_ਢੇਰ_archive(mz_zip_archive *pZip, ਖਾਲੀ **pBuf, size_t *p_ਮਾਪ)
{
  ਜੇ ((!pZip) || (!pZip->m_pState) || (!pBuf) || (!p_ਮਾਪ))
    ਵਾਪਸ MZ_FALSE;
  ਜੇ (pZip->m_pWrite != mz_zip_ਢੇਰ_write_func)
    ਵਾਪਸ MZ_FALSE;
  ਜੇ (!mz_zip_writer_finalize_archive(pZip))
    ਵਾਪਸ MZ_FALSE;

  *pBuf = pZip->m_pState->m_pMem;
  *p_ਮਾਪ = pZip->m_pState->m_mem_ਮਾਪ;
  pZip->m_pState->m_pMem = ਨਿਰਾ;
  pZip->m_pState->m_mem_ਮਾਪ = pZip->m_pState->m_mem_ਸਮਰੱਥਾ = 0;
  ਵਾਪਸ MZ_TRUE;
}

mz_bool mz_zip_writer_ਸਿਰਾ(mz_zip_archive *pZip)
{
  mz_zip_ਅੰਦਰੂਨੀ_state *pState;
  mz_bool ਸਥਿਤੀ = MZ_TRUE;
  ਜੇ ((!pZip) || (!pZip->m_pState) || (!pZip->m_pAlloc) || (!pZip->m_pFree) || ((pZip->m_zip_ਬਹੁਲਕ != MZ_ZIP_ਬਹੁਲਕ_WRITING) && (pZip->m_zip_ਬਹੁਲਕ != MZ_ZIP_ਬਹੁਲਕ_WRITING_HAS_BEEN_FINALIZED)))
    ਵਾਪਸ MZ_FALSE;

  pState = pZip->m_pState;
  pZip->m_pState = ਨਿਰਾ;
  mz_zip_array_clear(pZip, &pState->m_central_dir);
  mz_zip_array_clear(pZip, &pState->m_central_dir_offsets);
  mz_zip_array_clear(pZip, &pState->m_sorted_central_dir_offsets);

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_STDIO
  ਜੇ (pState->m_pFile)
  {
    MZ_FCLOSE(pState->m_pFile);
    pState->m_pFile = ਨਿਰਾ;
  }
#ਜੇ_ਅੰਤ // #ifndef MINIZ_NO_STDIO

  ਜੇ ((pZip->m_pWrite == mz_zip_ਢੇਰ_write_func) && (pState->m_pMem))
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pState->m_pMem);
    pState->m_pMem = ਨਿਰਾ;
  }

  pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
  pZip->m_zip_ਬਹੁਲਕ = MZ_ZIP_ਬਹੁਲਕ_INVALID;
  ਵਾਪਸ ਸਥਿਤੀ;
}

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ MINIZ_NO_STDIO
mz_bool mz_zip_ਜੋੜੋ_mem_ਮੰਜ਼ਿਲ_archive_file_ਵਿੱਚ_ਰੱਖੋ(ਅਚਲ ਅੱਖਰ *pZip_filename, ਅਚਲ ਅੱਖਰ *pArchive_name, ਅਚਲ ਖਾਲੀ *pBuf, size_t buf_ਮਾਪ_2, ਅਚਲ ਖਾਲੀ *pComment, mz_uint16 comment_ਮਾਪ, mz_uint level_and_flags)
{
  mz_bool ਸਥਿਤੀ, created_new_archive = MZ_FALSE;
  mz_zip_archive zip_archive;
  ਬਣਤਰ MZ_FILE_STAT_STRUCT file_stat;
  MZ_CLEAR_OBJ(zip_archive);
  ਜੇ ((ਪੂਰਨ)level_and_flags < 0)
     level_and_flags = MZ_DEFAULT_LEVEL;
  ਜੇ ((!pZip_filename) || (!pArchive_name) || ((buf_ਮਾਪ_2) && (!pBuf)) || ((comment_ਮਾਪ) && (!pComment)) || ((level_and_flags & 0xF) > MZ_UBER_COMPRESSION))
    ਵਾਪਸ MZ_FALSE;
  ਜੇ (!mz_zip_writer_validate_archive_name(pArchive_name))
    ਵਾਪਸ MZ_FALSE;
  ਜੇ (MZ_FILE_STAT(pZip_filename, &file_stat) != 0)
  {
    // Create a new archive.
    ਜੇ (!mz_zip_writer_init_file(&zip_archive, pZip_filename, 0))
      ਵਾਪਸ MZ_FALSE;
    created_new_archive = MZ_TRUE;
  }
  ਨਹੀਂਤਾਂ
  {
    // Append to an existing archive.
    ਜੇ (!mz_zip_reader_init_file(&zip_archive, pZip_filename, level_and_flags | MZ_ZIP_FLAG_DO_NOT_ਛਾਂਟੋ_CENTRAL_DIRECTORY))
      ਵਾਪਸ MZ_FALSE;
    ਜੇ (!mz_zip_writer_init_from_reader(&zip_archive, pZip_filename))
    {
      mz_zip_reader_ਸਿਰਾ(&zip_archive);
      ਵਾਪਸ MZ_FALSE;
    }
  }
  ਸਥਿਤੀ = mz_zip_writer_ਜੋੜੋ_mem_ex(&zip_archive, pArchive_name, pBuf, buf_ਮਾਪ_2, pComment, comment_ਮਾਪ, level_and_flags, 0, 0);
  // Always finalize, even if adding failed for some reason, so we have a valid central directory. (This may not always succeed, but we can try.)
  ਜੇ (!mz_zip_writer_finalize_archive(&zip_archive))
    ਸਥਿਤੀ = MZ_FALSE;
  ਜੇ (!mz_zip_writer_ਸਿਰਾ(&zip_archive))
    ਸਥਿਤੀ = MZ_FALSE;
  ਜੇ ((!ਸਥਿਤੀ) && (created_new_archive))
  {
    // It's a new archive and something went wrong, so just delete it.
    ਪੂਰਨ ignored_ਸਥਿਤੀ = MZ_DELETE_FILE(pZip_filename);
    (ਖਾਲੀ)ignored_ਸਥਿਤੀ;
  }
  ਵਾਪਸ ਸਥਿਤੀ;
}

ਖਾਲੀ *mz_zip_ਕੱਢੋ_archive_file_ਮੰਜ਼ਿਲ_ਢੇਰ(ਅਚਲ ਅੱਖਰ *pZip_filename, ਅਚਲ ਅੱਖਰ *pArchive_name, size_t *p_ਮਾਪ, mz_uint flags)
{
  ਪੂਰਨ file_ਸੂਚਕਾਂਕ;
  mz_zip_archive zip_archive;
  ਖਾਲੀ *p = ਨਿਰਾ;

  ਜੇ (p_ਮਾਪ)
    *p_ਮਾਪ = 0;

  ਜੇ ((!pZip_filename) || (!pArchive_name))
    ਵਾਪਸ ਨਿਰਾ;

  MZ_CLEAR_OBJ(zip_archive);
  ਜੇ (!mz_zip_reader_init_file(&zip_archive, pZip_filename, flags | MZ_ZIP_FLAG_DO_NOT_ਛਾਂਟੋ_CENTRAL_DIRECTORY))
    ਵਾਪਸ ਨਿਰਾ;

  ਜੇ ((file_ਸੂਚਕਾਂਕ = mz_zip_reader_locate_file(&zip_archive, pArchive_name, ਨਿਰਾ, flags)) >= 0)
    p = mz_zip_reader_ਕੱਢੋ_ਮੰਜ਼ਿਲ_ਢੇਰ(&zip_archive, file_ਸੂਚਕਾਂਕ, p_ਮਾਪ, flags);

  mz_zip_reader_ਸਿਰਾ(&zip_archive);
  ਵਾਪਸ p;
}

#ਜੇ_ਅੰਤ // #ifndef MINIZ_NO_STDIO

#ਜੇ_ਅੰਤ // #ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

#ਜੇ_ਅੰਤ // #ifndef MINIZ_NO_ARCHIVE_APIS

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __cplusplus
}
#ਜੇ_ਅੰਤ

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _MSC_VER
#ਹਦਾਇਤ warning (ਕੱਢੋ)
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ // MINIZ_HEADER_FILE_ONLY

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

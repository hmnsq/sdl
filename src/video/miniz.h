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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_ಶೀರ್ಷಿಕೆ_INCLUDED
#ವ್ಯಾಖ್ಯಾನಿಸು MINIZ_ಶೀರ್ಷಿಕೆ_INCLUDED

/*#include <stdlib.h>*/

// Defines to completely disable specific portions of miniz.c:
// If all macros here are defined the only functionality remaining will be CRC-32, adler-32, tinfl, and tdefl.

// Define MINIZ_NO_STDIO to disable all usage and any functions which rely on stdio for file I/O.
#ವ್ಯಾಖ್ಯಾನಿಸು MINIZ_NO_STDIO

// If MINIZ_NO_TIME is specified then the ZIP archive functions will not be able to get the current time, or
// get/set file times, and the C run-time funcs that get/set times won't be called.
// The current downside is the times written to your archives will be from 1979.
#ವ್ಯಾಖ್ಯಾನಿಸು MINIZ_NO_ಸಮಯ

// Define MINIZ_NO_DEFLATE_APIS to disable all compression API's.
//#define MINIZ_NO_DEFLATE_APIS

// Define MINIZ_NO_INFLATE_APIS to disable all decompression API's.
#ವ್ಯಾಖ್ಯಾನಿಸು MINIZ_NO_INFLATE_APIS

// Define MINIZ_NO_ARCHIVE_APIS to disable all ZIP archive API's.
#ವ್ಯಾಖ್ಯಾನಿಸು MINIZ_NO_ARCHIVE_APIS

// Define MINIZ_NO_ARCHIVE_APIS to disable all writing related ZIP archive API's.
#ವ್ಯಾಖ್ಯಾನಿಸು MINIZ_NO_ARCHIVE_WRITING_APIS

// Define MINIZ_NO_ZLIB_APIS to remove all ZLIB-style compression/decompression API's.
#ವ್ಯಾಖ್ಯಾನಿಸು MINIZ_NO_ZLIB_APIS

// Define MINIZ_NO_ZLIB_COMPATIBLE_NAME to disable zlib names, to prevent conflicts against stock zlib.
#ವ್ಯಾಖ್ಯಾನಿಸು MINIZ_NO_ZLIB_COMPATIBLE_ಹೆಸರುಗಳು

// Define MINIZ_NO_MALLOC to disable all calls to malloc, free, and realloc.
// Note if MINIZ_NO_MALLOC is defined then the user must always provide custom user alloc/free/realloc
// callbacks to the zlib and archive API's, and a few stand-alone helper API's which don't provide custom user
// functions (such as tdefl_compress_mem_to_heap() and tinfl_decompress_mem_to_heap()) won't work.
//#define MINIZ_NO_MALLOC
#ವ್ಯಾಖ್ಯಾನಿಸು MINIZ_SDL_MALLOC

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ MINIZ_NO_INFLATE_APIS
#ವ್ಯಾಖ್ಯಾನಿಸು MINIZ_NO_ARCHIVE_APIS
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ MINIZ_NO_DEFLATE_APIS
#ವ್ಯಾಖ್ಯಾನಿಸು MINIZ_NO_ARCHIVE_WRITING_APIS
#ಆದರೆ_ಅಂತ್ಯ

// Define MINIZ_STATIC_FUNCTIONS to make all functions static. You probably
// want this if you're using miniz in a library
#ವ್ಯಾಖ್ಯಾನಿಸು MINIZ_STATIC_FUNCTIONS

#ಆದರೆ defined(__TINYC__) && (defined(__linux) || defined(__linux__))
  // TODO: Work around "error: include file 'sys\utime.h' when compiling with tcc on Linux
  #ವ್ಯಾಖ್ಯಾನಿಸು MINIZ_NO_ಸಮಯ
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ !defined(MINIZ_NO_ಸಮಯ) && !defined(MINIZ_NO_ARCHIVE_APIS)
  #ಅನ್ತರ್ಭಾವ <time.h>
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ defined(_M_IX86) || defined(_M_X64) || defined(__i386__) || defined(__i386) || defined(__i486__) || defined(__i486) || defined(i386) || defined(__ia64__) || defined(__x86_64__)
// MINIZ_X86_OR_X64_CPU is only used to help set the below macros.
#ವ್ಯಾಖ್ಯಾನಿಸು MINIZ_X86_OR_X64_CPU 1
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_LITTLE_ENDIAN /* if not defined by SDL */
#ಆದರೆ (__BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__) || MINIZ_X86_OR_X64_CPU
// Set MINIZ_LITTLE_ENDIAN to 1 if the processor is little endian.
#ವ್ಯಾಖ್ಯಾನಿಸು MINIZ_LITTLE_ENDIAN 1
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ // MINIZ_LITTLE_ENDIAN /* if not defined by SDL */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_USE_UNALIGNED_LOADS_AND_STORES
#ಆದರೆ MINIZ_X86_OR_X64_CPU
// Set MINIZ_USE_UNALIGNED_LOADS_AND_STORES to 1 on CPU's that permit efficient integer loads and stores from unaligned addresses.
#ವ್ಯಾಖ್ಯಾನಿಸು MINIZ_USE_UNALIGNED_LOADS_AND_STORES 1
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ // MINIZ_USE_UNALIGNED_LOADS_AND_STORES

#ಆದರೆ defined(_M_X64) || defined(_WIN64) || defined(__MINGW64__) || defined(_LP64) || defined(__LP64__) || defined(__ia64__) || defined(__x86_64__)
// Set MINIZ_HAS_64BIT_REGISTERS to 1 if operations on 64-bit integers are reasonably fast (and don't involve compiler generated calls to helper functions).
#ವ್ಯಾಖ್ಯಾನಿಸು MINIZ_HAS_64_ಬಿಟ್_REGISTERS 1
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ MINIZ_STATIC_FUNCTIONS
#ವ್ಯಾಖ್ಯಾನಿಸು MINIZ_STATIC ಸ್ಥಿರ
#ಇಲ್ಲದಿದ್ದರೆ
#ವ್ಯಾಖ್ಯಾನಿಸು MINIZ_STATIC
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ

// ------------------- zlib-style API Definitions.

// For more compatibility with zlib, miniz.c uses unsigned long for some parameters/struct members. Beware: mz_ulong can be either 32 or 64-bits!
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ mz_ulong;

// mz_free() internally uses the MZ_FREE() macro (which by default calls free() unless you've modified the MZ_MALLOC macro) to release a block allocated from the heap.
MINIZ_STATIC ಶೂನ್ಯ mz_free(ಶೂನ್ಯ *p);

#ವ್ಯಾಖ್ಯಾನಿಸು MZ_ADLER32_INIT (1)
// mz_adler32() returns the initial adler-32 value to use when called with ptr==NULL.
MINIZ_STATIC mz_ulong mz_adler32(mz_ulong adler, ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *ptr, size_t buf_len);

#ವ್ಯಾಖ್ಯಾನಿಸು MZ_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_INIT (0)
// mz_crc32() returns the initial CRC-32 value to use when called with ptr==NULL.
MINIZ_STATIC mz_ulong mz_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32(mz_ulong ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ, ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *ptr, size_t buf_len);

// Compression strategies.
ಎಣಿಕೆ { MZ_DEFAULT_STRATEGY = 0, MZ_FILTERED = 1, MZ_HUFFMAN_ONLY = 2, MZ_RLE = 3, MZ_FIXED = 4 };

//ವಿಧಾನ
#ವ್ಯಾಖ್ಯಾನಿಸು MZ_DEFLATED 8

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_ZLIB_APIS

// Heap allocation callbacks.
// Note that mz_alloc_func parameter types purpsosely differ from zlib's: items/size is size_t, not unsigned long.
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ *(*mz_alloc_func)(ಶೂನ್ಯ *opaque, size_t ವಸ್ತುಗಳು, size_t ಗಾತ್ರ_2);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (*mz_free_func)(ಶೂನ್ಯ *opaque, ಶೂನ್ಯ *ವಿಳಾಸ);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ *(*mz_realloc_func)(ಶೂನ್ಯ *opaque, ಶೂನ್ಯ *ವಿಳಾಸ, size_t ವಸ್ತುಗಳು, size_t ಗಾತ್ರ_2);

#ವ್ಯಾಖ್ಯಾನಿಸು MZ_ಆವೃತ್ತಿ          "9.1.15"
#ವ್ಯಾಖ್ಯಾನಿಸು MZ_VERNUM           0x91F0
#ವ್ಯಾಖ್ಯಾನಿಸು MZ_VER_MAJOR        9
#ವ್ಯಾಖ್ಯಾನಿಸು MZ_VER_MINOR        1
#ವ್ಯಾಖ್ಯಾನಿಸು MZ_VER_REVISION     15
#ವ್ಯಾಖ್ಯಾನಿಸು MZ_VER_SUBREVISION  0

// Flush values. For typical usage you only need MZ_NO_FLUSH and MZ_FINISH. The other values are for advanced use (refer to the zlib docs).
ಎಣಿಕೆ { MZ_NO_FLUSH = 0, MZ_PARTIAL_FLUSH = 1, MZ_SYNC_FLUSH = 2, MZ_ತುಂಬಿದ_FLUSH = 3, MZ_ಮುಕ್ತಾಯ = 4, MZ_ಖಂಡ = 5 };

// Return status codes. MZ_PARAM_ERROR is non-standard.
ಎಣಿಕೆ { MZ_OK = 0, MZ_ಹರಿವು_ಕೊನೆ = 1, MZ_NEED_DICT = 2, MZ_ERRNO = -1, MZ_ಹರಿವು_ERROR = -2, MZ_ದತ್ತಾಂಶ_ERROR = -3, MZ_MEM_ERROR = -4, MZ_BUF_ERROR = -5, MZ_ಆವೃತ್ತಿ_ERROR = -6, MZ_PARAM_ERROR = -10000 };

// Compression levels: 0-9 are the standard zlib-style levels, 10 is best possible compression (not zlib compatible, and may be very slow), MZ_DEFAULT_COMPRESSION=MZ_DEFAULT_LEVEL.
ಎಣಿಕೆ { MZ_NO_COMPRESSION = 0, MZ_ಉತ್ತಮ_ವೇಗ = 1, MZ_ಉತ್ತಮ_COMPRESSION = 9, MZ_UBER_COMPRESSION = 10, MZ_DEFAULT_LEVEL = 6, MZ_DEFAULT_COMPRESSION = -1 };

// Window bits
#ವ್ಯಾಖ್ಯಾನಿಸು MZ_DEFAULT_ಕಿಟಕಿ_ಬಿಟ್ಟುಗಳು 15

ರಚನೆ mz_ಆಂತರಿಕ_state;

// Compression/decompression stream struct.
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ mz_ಹರಿವು_s
{
  ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *ಮುಂದಿನ_ಒಳ;     // pointer to next byte to read
  ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ avail_ಒಳ;            // number of bytes available at next_in
  mz_ulong ಒಟ್ಟು_ಒಳ;                // total number of bytes consumed so far

  ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *ಮುಂದಿನ_ಹೊರಹೋಗು;          // pointer to next byte to write
  ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ avail_ಹೊರಹೋಗು;           // number of bytes that can be written to next_out
  mz_ulong ಒಟ್ಟು_ಹೊರಹೋಗು;               // total number of bytes produced so far

  ಅಕ್ಷರ *ಸಂದೇಶ_2;                        // error msg (unused)
  ರಚನೆ mz_ಆಂತರಿಕ_state *state;  // internal state, allocated by zalloc/zfree

  mz_alloc_func zalloc;             // optional heap allocation function (defaults to malloc)
  mz_free_func zfree;               // optional heap free function (defaults to free)
  ಶೂನ್ಯ *opaque;                     // heap alloc function user pointer

  ಪೂರ್ಣಾಂಕ ದತ್ತಾಂಶ_type;                    // data_type (unused)
  mz_ulong adler;                   // adler32 of the source or uncompressed data
  mz_ulong reserved;                // not used
} mz_ಹರಿವು;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ mz_ಹರಿವು *mz_streamp;

// Returns the version string of miniz.c.
MINIZ_STATIC ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mz_ಆವೃತ್ತಿ(ಶೂನ್ಯ);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_DEFLATE_APIS

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
MINIZ_STATIC ಪೂರ್ಣಾಂಕ mz_deflateInit(mz_streamp p_ಹರಿವು, ಪೂರ್ಣಾಂಕ level);

// mz_deflateInit2() is like mz_deflate(), except with more control:
// Additional parameters:
//   method must be MZ_DEFLATED
//   window_bits must be MZ_DEFAULT_WINDOW_BITS (to wrap the deflate stream with zlib header/adler-32 footer) or -MZ_DEFAULT_WINDOW_BITS (raw deflate/no header or footer)
//   mem_level must be between [1, 9] (it's checked but ignored by miniz.c)
MINIZ_STATIC ಪೂರ್ಣಾಂಕ mz_deflateInit2(mz_streamp p_ಹರಿವು, ಪೂರ್ಣಾಂಕ level, ಪೂರ್ಣಾಂಕ ವಿಧಾನ, ಪೂರ್ಣಾಂಕ ಕಿಟಕಿ_ಬಿಟ್ಟುಗಳು, ಪೂರ್ಣಾಂಕ mem_level, ಪೂರ್ಣಾಂಕ strategy);

// Quickly resets a compressor without having to reallocate anything. Same as calling mz_deflateEnd() followed by mz_deflateInit()/mz_deflateInit2().
MINIZ_STATIC ಪೂರ್ಣಾಂಕ mz_deflateReset(mz_streamp p_ಹರಿವು);

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
MINIZ_STATIC ಪೂರ್ಣಾಂಕ mz_deflate(mz_streamp p_ಹರಿವು, ಪೂರ್ಣಾಂಕ flush);

// mz_deflateEnd() deinitializes a compressor:
// Return values:
//  MZ_OK on success.
//  MZ_STREAM_ERROR if the stream is bogus.
MINIZ_STATIC ಪೂರ್ಣಾಂಕ mz_deflate_ಕೊನೆ(mz_streamp p_ಹರಿವು);

// mz_deflateBound() returns a (very) conservative upper bound on the amount of data that could be generated by deflate(), assuming flush is set to only MZ_NO_FLUSH or MZ_FINISH.
MINIZ_STATIC mz_ulong mz_deflateBound(mz_streamp p_ಹರಿವು, mz_ulong ಮೂಲ_len);

// Single-call compression functions mz_compress() and mz_compress2():
// Returns MZ_OK on success, or one of the error codes from mz_deflate() on failure.
MINIZ_STATIC ಪೂರ್ಣಾಂಕ mz_compress(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *pDest, mz_ulong *pDest_len, ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *p_ಮೂಲ, mz_ulong ಮೂಲ_len);
MINIZ_STATIC ಪೂರ್ಣಾಂಕ mz_compress2(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *pDest, mz_ulong *pDest_len, ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *p_ಮೂಲ, mz_ulong ಮೂಲ_len, ಪೂರ್ಣಾಂಕ level);

// mz_compressBound() returns a (very) conservative upper bound on the amount of data that could be generated by calling mz_compress().
MINIZ_STATIC mz_ulong mz_compressBound(mz_ulong ಮೂಲ_len);

#ಆದರೆ_ಅಂತ್ಯ /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_INFLATE_APIS

// Initializes a decompressor.
MINIZ_STATIC ಪೂರ್ಣಾಂಕ mz_inflateInit(mz_streamp p_ಹರಿವು);

// mz_inflateInit2() is like mz_inflateInit() with an additional option that controls the window size and whether or not the stream has been wrapped with a zlib header/footer:
// window_bits must be MZ_DEFAULT_WINDOW_BITS (to parse zlib header/footer) or -MZ_DEFAULT_WINDOW_BITS (raw deflate).
MINIZ_STATIC ಪೂರ್ಣಾಂಕ mz_inflateInit2(mz_streamp p_ಹರಿವು, ಪೂರ್ಣಾಂಕ ಕಿಟಕಿ_ಬಿಟ್ಟುಗಳು);

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
MINIZ_STATIC ಪೂರ್ಣಾಂಕ mz_inflate(mz_streamp p_ಹರಿವು, ಪೂರ್ಣಾಂಕ flush);

// Deinitializes a decompressor.
MINIZ_STATIC ಪೂರ್ಣಾಂಕ mz_inflate_ಕೊನೆ(mz_streamp p_ಹರಿವು);

// Single-call decompression.
// Returns MZ_OK on success, or one of the error codes from mz_inflate() on failure.
MINIZ_STATIC ಪೂರ್ಣಾಂಕ mz_uncompress(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *pDest, mz_ulong *pDest_len, ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *p_ಮೂಲ, mz_ulong ಮೂಲ_len);
#ಆದರೆ_ಅಂತ್ಯ /*#ifndef MINIZ_NO_INFLATE_APIS*/

// Returns a string description of the specified error code, or NULL if the error code is invalid.
MINIZ_STATIC ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mz_error(ಪೂರ್ಣಾಂಕ err);

// Redefine zlib-compatible names to miniz equivalents, so miniz.c can be used as a drop-in replacement for the subset of zlib that miniz.c supports.
// Define MINIZ_NO_ZLIB_COMPATIBLE_NAMES to disable zlib-compatibility if you use zlib in the same project.
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_ZLIB_COMPATIBLE_ಹೆಸರುಗಳು
  ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ Byte;
  ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ uInt;
  ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ mz_ulong uLong;
  ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Byte Bytef;
  ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uInt uIntf;
  ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಅಕ್ಷರ charf;
  ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೂರ್ಣಾಂಕ intf;
  ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ *voidpf;
  ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ uLong uLongf;
  ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ *voidp;
  ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ *ಸ್ಥಿರಾಂಕ voidpc;
  #ವ್ಯಾಖ್ಯಾನಿಸು Z_NULL                0
  #ವ್ಯಾಖ್ಯಾನಿಸು Z_NO_FLUSH            MZ_NO_FLUSH
  #ವ್ಯಾಖ್ಯಾನಿಸು Z_PARTIAL_FLUSH       MZ_PARTIAL_FLUSH
  #ವ್ಯಾಖ್ಯಾನಿಸು Z_SYNC_FLUSH          MZ_SYNC_FLUSH
  #ವ್ಯಾಖ್ಯಾನಿಸು Z_ತುಂಬಿದ_FLUSH          MZ_ತುಂಬಿದ_FLUSH
  #ವ್ಯಾಖ್ಯಾನಿಸು Z_ಮುಕ್ತಾಯ              MZ_ಮುಕ್ತಾಯ
  #ವ್ಯಾಖ್ಯಾನಿಸು Z_ಖಂಡ               MZ_ಖಂಡ
  #ವ್ಯಾಖ್ಯಾನಿಸು Z_OK                  MZ_OK
  #ವ್ಯಾಖ್ಯಾನಿಸು Z_ಹರಿವು_ಕೊನೆ          MZ_ಹರಿವು_ಕೊನೆ
  #ವ್ಯಾಖ್ಯಾನಿಸು Z_NEED_DICT           MZ_NEED_DICT
  #ವ್ಯಾಖ್ಯಾನಿಸು Z_ERRNO               MZ_ERRNO
  #ವ್ಯಾಖ್ಯಾನಿಸು Z_ಹರಿವು_ERROR        MZ_ಹರಿವು_ERROR
  #ವ್ಯಾಖ್ಯಾನಿಸು Z_ದತ್ತಾಂಶ_ERROR          MZ_ದತ್ತಾಂಶ_ERROR
  #ವ್ಯಾಖ್ಯಾನಿಸು Z_MEM_ERROR           MZ_MEM_ERROR
  #ವ್ಯಾಖ್ಯಾನಿಸು Z_BUF_ERROR           MZ_BUF_ERROR
  #ವ್ಯಾಖ್ಯಾನಿಸು Z_ಆವೃತ್ತಿ_ERROR       MZ_ಆವೃತ್ತಿ_ERROR
  #ವ್ಯಾಖ್ಯಾನಿಸು Z_PARAM_ERROR         MZ_PARAM_ERROR
  #ವ್ಯಾಖ್ಯಾನಿಸು Z_NO_COMPRESSION      MZ_NO_COMPRESSION
  #ವ್ಯಾಖ್ಯಾನಿಸು Z_ಉತ್ತಮ_ವೇಗ          MZ_ಉತ್ತಮ_ವೇಗ
  #ವ್ಯಾಖ್ಯಾನಿಸು Z_ಉತ್ತಮ_COMPRESSION    MZ_ಉತ್ತಮ_COMPRESSION
  #ವ್ಯಾಖ್ಯಾನಿಸು Z_DEFAULT_COMPRESSION MZ_DEFAULT_COMPRESSION
  #ವ್ಯಾಖ್ಯಾನಿಸು Z_DEFAULT_STRATEGY    MZ_DEFAULT_STRATEGY
  #ವ್ಯಾಖ್ಯಾನಿಸು Z_FILTERED            MZ_FILTERED
  #ವ್ಯಾಖ್ಯಾನಿಸು Z_HUFFMAN_ONLY        MZ_HUFFMAN_ONLY
  #ವ್ಯಾಖ್ಯಾನಿಸು Z_RLE                 MZ_RLE
  #ವ್ಯಾಖ್ಯಾನಿಸು Z_FIXED               MZ_FIXED
  #ವ್ಯಾಖ್ಯಾನಿಸು Z_DEFLATED            MZ_DEFLATED
  #ವ್ಯಾಖ್ಯಾನಿಸು Z_DEFAULT_ಕಿಟಕಿ_ಬಿಟ್ಟುಗಳು MZ_DEFAULT_ಕಿಟಕಿ_ಬಿಟ್ಟುಗಳು
  #ವ್ಯಾಖ್ಯಾನಿಸು alloc_func            mz_alloc_func
  #ವ್ಯಾಖ್ಯಾನಿಸು free_func             mz_free_func
  #ವ್ಯಾಖ್ಯಾನಿಸು ಆಂತರಿಕ_state        mz_ಆಂತರಿಕ_state
  #ವ್ಯಾಖ್ಯಾನಿಸು z_ಹರಿವು              mz_ಹರಿವು
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_DEFLATE_APIS
  #ವ್ಯಾಖ್ಯಾನಿಸು deflateInit           mz_deflateInit
  #ವ್ಯಾಖ್ಯಾನಿಸು deflateInit2          mz_deflateInit2
  #ವ್ಯಾಖ್ಯಾನಿಸು deflateReset          mz_deflateReset
  #ವ್ಯಾಖ್ಯಾನಿಸು deflate               mz_deflate
  #ವ್ಯಾಖ್ಯಾನಿಸು deflate_ಕೊನೆ            mz_deflate_ಕೊನೆ
  #ವ್ಯಾಖ್ಯಾನಿಸು deflateBound          mz_deflateBound
  #ವ್ಯಾಖ್ಯಾನಿಸು compress              mz_compress
  #ವ್ಯಾಖ್ಯಾನಿಸು compress2             mz_compress2
  #ವ್ಯಾಖ್ಯಾನಿಸು compressBound         mz_compressBound
#ಆದರೆ_ಅಂತ್ಯ /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_INFLATE_APIS
  #ವ್ಯಾಖ್ಯಾನಿಸು inflateInit           mz_inflateInit
  #ವ್ಯಾಖ್ಯಾನಿಸು inflateInit2          mz_inflateInit2
  #ವ್ಯಾಖ್ಯಾನಿಸು inflate               mz_inflate
  #ವ್ಯಾಖ್ಯಾನಿಸು inflate_ಕೊನೆ            mz_inflate_ಕೊನೆ
  #ವ್ಯಾಖ್ಯಾನಿಸು uncompress            mz_uncompress
#ಆದರೆ_ಅಂತ್ಯ /*#ifndef MINIZ_NO_INFLATE_APIS*/
  #ವ್ಯಾಖ್ಯಾನಿಸು ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32                 mz_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32
  #ವ್ಯಾಖ್ಯಾನಿಸು adler32               mz_adler32
  #ವ್ಯಾಖ್ಯಾನಿಸು MAX_WBITS             15
  #ವ್ಯಾಖ್ಯಾನಿಸು MAX_MEM_LEVEL         9
  #ವ್ಯಾಖ್ಯಾನಿಸು zError                mz_error
  #ವ್ಯಾಖ್ಯಾನಿಸು ZLIB_ಆವೃತ್ತಿ          MZ_ಆವೃತ್ತಿ
  #ವ್ಯಾಖ್ಯಾನಿಸು ZLIB_VERNUM           MZ_VERNUM
  #ವ್ಯಾಖ್ಯಾನಿಸು ZLIB_VER_MAJOR        MZ_VER_MAJOR
  #ವ್ಯಾಖ್ಯಾನಿಸು ZLIB_VER_MINOR        MZ_VER_MINOR
  #ವ್ಯಾಖ್ಯಾನಿಸು ZLIB_VER_REVISION     MZ_VER_REVISION
  #ವ್ಯಾಖ್ಯಾನಿಸು ZLIB_VER_SUBREVISION  MZ_VER_SUBREVISION
  #ವ್ಯಾಖ್ಯಾನಿಸು zlib_ಆವೃತ್ತಿ           mz_ಆವೃತ್ತಿ
  #ವ್ಯಾಖ್ಯಾನಿಸು zlib_ಆವೃತ್ತಿ_2          mz_ಆವೃತ್ತಿ()
#ಆದರೆ_ಅಂತ್ಯ // #ifndef MINIZ_NO_ZLIB_COMPATIBLE_NAMES

#ಆದರೆ_ಅಂತ್ಯ // MINIZ_NO_ZLIB_APIS

// ------------------- Types and macros

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ mz_uint8;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆಯುಳ್ಳ ಗಿಡ್ಡ mz_int16;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ ಗಿಡ್ಡ mz_uint16;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ mz_uint32;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ mz_uint;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ದೀರ್ಘ ದೀರ್ಘ mz_int64;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ದೀರ್ಘ mz_uint64;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೂರ್ಣಾಂಕ mz_bool;

#ವ್ಯಾಖ್ಯಾನಿಸು MZ_FALSE (0)
#ವ್ಯಾಖ್ಯಾನಿಸು MZ_TRUE (1)

// An attempt to work around MSVC's spammy "warning C4127: conditional expression is constant" message.
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _MSC_VER
   #ವ್ಯಾಖ್ಯಾನಿಸು MZ_MACRO_ಕೊನೆ ಆಗ (0, 0)
#ಇಲ್ಲದಿದ್ದರೆ
   #ವ್ಯಾಖ್ಯಾನಿಸು MZ_MACRO_ಕೊನೆ ಆಗ (0)
#ಆದರೆ_ಅಂತ್ಯ

// ------------------- ZIP archive reading/writing

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_ARCHIVE_APIS

ಎಣಿಕೆ
{
  MZ_ZIP_MAX_IO_BUF_ಗಾತ್ರ = 64*1024,
  MZ_ZIP_MAX_ARCHIVE_FILENAME_ಗಾತ್ರ = 260,
  MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_ಗಾತ್ರ = 256
};

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
  mz_uint32 m_file_ಸೂಚ್ಯಂಕ;
  mz_uint32 m_central_dir_ofs;
  mz_uint16 m_ಆವೃತ್ತಿ_made_by;
  mz_uint16 m_ಆವೃತ್ತಿ_needed;
  mz_uint16 m_ಬಿಟ್_flag;
  mz_uint16 m_ವಿಧಾನ;
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_ಸಮಯ
  ಸಮಯ_t m_ಸಮಯ;
#ಆದರೆ_ಅಂತ್ಯ
  mz_uint32 m_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32;
  mz_uint64 m_comp_ಗಾತ್ರ;
  mz_uint64 m_uncomp_ಗಾತ್ರ;
  mz_uint16 m_ಆಂತರಿಕ_attr;
  mz_uint32 m_external_attr;
  mz_uint64 m_local_ಶೀರ್ಷಿಕೆ_ofs;
  mz_uint32 m_comment_ಗಾತ್ರ;
  ಅಕ್ಷರ m_filename[MZ_ZIP_MAX_ARCHIVE_FILENAME_ಗಾತ್ರ];
  ಅಕ್ಷರ m_comment[MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_ಗಾತ್ರ];
} mz_zip_archive_file_stat;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ size_t (*mz_file_read_func)(ಶೂನ್ಯ *pOpaque, mz_uint64 file_ofs, ಶೂನ್ಯ *pBuf, size_t n);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ size_t (*mz_file_write_func)(ಶೂನ್ಯ *pOpaque, mz_uint64 file_ofs, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *pBuf, size_t n);

ರಚನೆ mz_zip_ಆಂತರಿಕ_state_ಟ್ಯಾಗ್;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ mz_zip_ಆಂತರಿಕ_state_ಟ್ಯಾಗ್ mz_zip_ಆಂತರಿಕ_state;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ
{
  MZ_ZIP_ಬಹುಲಕ_INVALID = 0,
  MZ_ZIP_ಬಹುಲಕ_READING = 1,
  MZ_ZIP_ಬಹುಲಕ_WRITING = 2,
  MZ_ZIP_ಬಹುಲಕ_WRITING_HAS_BEEN_FINALIZED = 3
} mz_zip_ಬಹುಲಕ;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ mz_zip_archive_ಟ್ಯಾಗ್
{
  mz_uint64 m_archive_ಗಾತ್ರ;
  mz_uint64 m_central_directory_file_ofs;
  mz_uint m_ಒಟ್ಟು_files;
  mz_zip_ಬಹುಲಕ m_zip_ಬಹುಲಕ;

  mz_uint m_file_ಸ್ಥಾನಾಂತರ_alignment;

  mz_alloc_func m_pAlloc;
  mz_free_func m_pFree;
  mz_realloc_func m_pRealloc;
  ಶೂನ್ಯ *m_pAlloc_opaque;

  mz_file_read_func m_pRead;
  mz_file_write_func m_pWrite;
  ಶೂನ್ಯ *m_pIO_opaque;

  mz_zip_ಆಂತರಿಕ_state *m_pState;

} mz_zip_archive;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ
{
  MZ_ZIP_FLAG_CASE_SENSITIVE                = 0x0100,
  MZ_ZIP_FLAG_IGNORE_ಮಾರ್ಗ                   = 0x0200,
  MZ_ZIP_FLAG_COMPRESSED_ದತ್ತಾಂಶ               = 0x0400,
  MZ_ZIP_FLAG_DO_NOT_ವಿಂಗಡಿಸು_CENTRAL_DIRECTORY = 0x0800
} mz_zip_flags;

// ZIP archive reading

// Inits a ZIP archive reader.
// These functions read and validate the archive's central directory.
MINIZ_STATIC mz_bool mz_zip_reader_init(mz_zip_archive *pZip, mz_uint64 ಗಾತ್ರ_2, mz_uint32 flags);
MINIZ_STATIC mz_bool mz_zip_reader_init_mem(mz_zip_archive *pZip, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *pMem, size_t ಗಾತ್ರ_2, mz_uint32 flags);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_STDIO
MINIZ_STATIC mz_bool mz_zip_reader_init_file(mz_zip_archive *pZip, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pFilename, mz_uint32 flags);
#ಆದರೆ_ಅಂತ್ಯ

// Returns the total number of files in the archive.
MINIZ_STATIC mz_uint mz_zip_reader_get_ಅಂಕೆ_files(mz_zip_archive *pZip);

// Returns detailed information about an archive file entry.
MINIZ_STATIC mz_bool mz_zip_reader_file_stat(mz_zip_archive *pZip, mz_uint file_ಸೂಚ್ಯಂಕ, mz_zip_archive_file_stat *pStat);

// Determines if an archive file entry is a directory entry.
MINIZ_STATIC mz_bool mz_zip_reader_is_file_a_directory(mz_zip_archive *pZip, mz_uint file_ಸೂಚ್ಯಂಕ);
MINIZ_STATIC mz_bool mz_zip_reader_is_file_encrypted(mz_zip_archive *pZip, mz_uint file_ಸೂಚ್ಯಂಕ);

// Retrieves the filename of an archive file entry.
// Returns the number of bytes written to pFilename, or if filename_buf_size is 0 this function returns the number of bytes needed to fully store the filename.
MINIZ_STATIC mz_uint mz_zip_reader_get_filename(mz_zip_archive *pZip, mz_uint file_ಸೂಚ್ಯಂಕ, ಅಕ್ಷರ *pFilename, mz_uint filename_buf_ಗಾತ್ರ);

// Attempts to locates a file in the archive's central directory.
// Valid flags: MZ_ZIP_FLAG_CASE_SENSITIVE, MZ_ZIP_FLAG_IGNORE_PATH
// Returns -1 if the file cannot be found.
MINIZ_STATIC ಪೂರ್ಣಾಂಕ mz_zip_reader_locate_file(mz_zip_archive *pZip, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pName, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pComment, mz_uint flags);

// Extracts a archive file to a memory buffer using no memory allocation.
MINIZ_STATIC mz_bool mz_zip_reader_ಹೊರತೆಗೆ_ಗಮ್ಯ_mem_no_alloc(mz_zip_archive *pZip, mz_uint file_ಸೂಚ್ಯಂಕ, ಶೂನ್ಯ *pBuf, size_t buf_ಗಾತ್ರ_2, mz_uint flags, ಶೂನ್ಯ *pUser_read_buf, size_t user_read_buf_ಗಾತ್ರ);
MINIZ_STATIC mz_bool mz_zip_reader_ಹೊರತೆಗೆ_file_ಗಮ್ಯ_mem_no_alloc(mz_zip_archive *pZip, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pFilename, ಶೂನ್ಯ *pBuf, size_t buf_ಗಾತ್ರ_2, mz_uint flags, ಶೂನ್ಯ *pUser_read_buf, size_t user_read_buf_ಗಾತ್ರ);

// Extracts a archive file to a memory buffer.
MINIZ_STATIC mz_bool mz_zip_reader_ಹೊರತೆಗೆ_ಗಮ್ಯ_mem(mz_zip_archive *pZip, mz_uint file_ಸೂಚ್ಯಂಕ, ಶೂನ್ಯ *pBuf, size_t buf_ಗಾತ್ರ_2, mz_uint flags);
MINIZ_STATIC mz_bool mz_zip_reader_ಹೊರತೆಗೆ_file_ಗಮ್ಯ_mem(mz_zip_archive *pZip, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pFilename, ಶೂನ್ಯ *pBuf, size_t buf_ಗಾತ್ರ_2, mz_uint flags);

// Extracts a archive file to a dynamically allocated heap buffer.
MINIZ_STATIC ಶೂನ್ಯ *mz_zip_reader_ಹೊರತೆಗೆ_ಗಮ್ಯ_ರಾಶಿ(mz_zip_archive *pZip, mz_uint file_ಸೂಚ್ಯಂಕ, size_t *p_ಗಾತ್ರ, mz_uint flags);
MINIZ_STATIC ಶೂನ್ಯ *mz_zip_reader_ಹೊರತೆಗೆ_file_ಗಮ್ಯ_ರಾಶಿ(mz_zip_archive *pZip, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pFilename, size_t *p_ಗಾತ್ರ, mz_uint flags);

// Extracts a archive file using a callback function to output the file's data.
MINIZ_STATIC mz_bool mz_zip_reader_ಹೊರತೆಗೆ_ಗಮ್ಯ_callback(mz_zip_archive *pZip, mz_uint file_ಸೂಚ್ಯಂಕ, mz_file_write_func pCallback, ಶೂನ್ಯ *pOpaque, mz_uint flags);
MINIZ_STATIC mz_bool mz_zip_reader_ಹೊರತೆಗೆ_file_ಗಮ್ಯ_callback(mz_zip_archive *pZip, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pFilename, mz_file_write_func pCallback, ಶೂನ್ಯ *pOpaque, mz_uint flags);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_STDIO
// Extracts a archive file to a disk file and sets its last accessed and modified times.
// This function only extracts files, not archive directory records.
MINIZ_STATIC mz_bool mz_zip_reader_ಹೊರತೆಗೆ_ಗಮ್ಯ_file(mz_zip_archive *pZip, mz_uint file_ಸೂಚ್ಯಂಕ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pDst_filename, mz_uint flags);
MINIZ_STATIC mz_bool mz_zip_reader_ಹೊರತೆಗೆ_file_ಗಮ್ಯ_file(mz_zip_archive *pZip, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pArchive_filename, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pDst_filename, mz_uint flags);
#ಆದರೆ_ಅಂತ್ಯ

// Ends archive reading, freeing all allocations, and closing the input archive file if mz_zip_reader_init_file() was used.
MINIZ_STATIC mz_bool mz_zip_reader_ಕೊನೆ(mz_zip_archive *pZip);

// ZIP archive writing

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_ARCHIVE_WRITING_APIS

// Inits a ZIP archive writer.
MINIZ_STATIC mz_bool mz_zip_writer_init(mz_zip_archive *pZip, mz_uint64 existing_ಗಾತ್ರ);
MINIZ_STATIC mz_bool mz_zip_writer_init_ರಾಶಿ(mz_zip_archive *pZip, size_t ಗಾತ್ರ_ಗಮ್ಯ_reserve_at_beginning, size_t initial_ಹಂಚಿಕೆ_ಗಾತ್ರ);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_STDIO
MINIZ_STATIC mz_bool mz_zip_writer_init_file(mz_zip_archive *pZip, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pFilename, mz_uint64 ಗಾತ್ರ_ಗಮ್ಯ_reserve_at_beginning);
#ಆದರೆ_ಅಂತ್ಯ

// Converts a ZIP archive reader object into a writer object, to allow efficient in-place file appends to occur on an existing archive.
// For archives opened using mz_zip_reader_init_file, pFilename must be the archive's filename so it can be reopened for writing. If the file can't be reopened, mz_zip_reader_end() will be called.
// For archives opened using mz_zip_reader_init_mem, the memory block must be growable using the realloc callback (which defaults to realloc unless you've overridden it).
// Finally, for archives opened using mz_zip_reader_init, the mz_zip_archive's user provided m_pWrite function cannot be NULL.
// Note: In-place archive modification is not recommended unless you know what you're doing, because if execution stops or something goes wrong before
// the archive is finalized the file's central directory will be hosed.
MINIZ_STATIC mz_bool mz_zip_writer_init_from_reader(mz_zip_archive *pZip, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pFilename);

// Adds the contents of a memory buffer to an archive. These functions record the current local time into the archive.
// To add a directory entry, call this method with an archive name ending in a forwardslash with empty buffer.
// level_and_flags - compression level (0-10, see MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or just set to MZ_DEFAULT_COMPRESSION.
MINIZ_STATIC mz_bool mz_zip_writer_ಕೂಡಿಸು_mem(mz_zip_archive *pZip, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pArchive_name, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *pBuf, size_t buf_ಗಾತ್ರ_2, mz_uint level_and_flags);
MINIZ_STATIC mz_bool mz_zip_writer_ಕೂಡಿಸು_mem_ex(mz_zip_archive *pZip, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pArchive_name, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *pBuf, size_t buf_ಗಾತ್ರ_2, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *pComment, mz_uint16 comment_ಗಾತ್ರ, mz_uint level_and_flags, mz_uint64 uncomp_ಗಾತ್ರ, mz_uint32 uncomp_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_STDIO
// Adds the contents of a disk file to an archive. This function also records the disk file's modified time into the archive.
// level_and_flags - compression level (0-10, see MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or just set to MZ_DEFAULT_COMPRESSION.
MINIZ_STATIC mz_bool mz_zip_writer_ಕೂಡಿಸು_file(mz_zip_archive *pZip, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pArchive_name, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pSrc_filename, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *pComment, mz_uint16 comment_ಗಾತ್ರ, mz_uint level_and_flags);
#ಆದರೆ_ಅಂತ್ಯ

// Adds a file to an archive by fully cloning the data from another archive.
// This function fully clones the source file's compressed data (no recompression), along with its full filename, extra data, and comment fields.
MINIZ_STATIC mz_bool mz_zip_writer_ಕೂಡಿಸು_from_zip_reader(mz_zip_archive *pZip, mz_zip_archive *p_ಮೂಲ_zip, mz_uint file_ಸೂಚ್ಯಂಕ);

// Finalizes the archive by writing the central directory records followed by the end of central directory record.
// After an archive is finalized, the only valid call on the mz_zip_archive struct is mz_zip_writer_end().
// An archive must be manually finalized by calling this function for it to be valid.
MINIZ_STATIC mz_bool mz_zip_writer_finalize_archive(mz_zip_archive *pZip);
MINIZ_STATIC mz_bool mz_zip_writer_finalize_ರಾಶಿ_archive(mz_zip_archive *pZip, ಶೂನ್ಯ **pBuf, size_t *p_ಗಾತ್ರ);

// Ends archive writing, freeing all allocations, and closing the output file if mz_zip_writer_init_file() was used.
// Note for the archive to be valid, it must have been finalized before ending.
MINIZ_STATIC mz_bool mz_zip_writer_ಕೊನೆ(mz_zip_archive *pZip);

// Misc. high-level helper functions:

// mz_zip_add_mem_to_archive_file_in_place() efficiently (but not atomically) appends a memory blob to a ZIP archive.
// level_and_flags - compression level (0-10, see MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or just set to MZ_DEFAULT_COMPRESSION.
MINIZ_STATIC mz_bool mz_zip_ಕೂಡಿಸು_mem_ಗಮ್ಯ_archive_file_ಒಳ_ಇರಿಸು(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pZip_filename, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pArchive_name, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *pBuf, size_t buf_ಗಾತ್ರ_2, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *pComment, mz_uint16 comment_ಗಾತ್ರ, mz_uint level_and_flags);

// Reads a single file from an archive into a heap block.
// Returns NULL on failure.
MINIZ_STATIC ಶೂನ್ಯ *mz_zip_ಹೊರತೆಗೆ_archive_file_ಗಮ್ಯ_ರಾಶಿ(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pZip_filename, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pArchive_name, size_t *p_ಗಾತ್ರ, mz_uint zip_flags);

#ಆದರೆ_ಅಂತ್ಯ // #ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

#ಆದರೆ_ಅಂತ್ಯ // #ifndef MINIZ_NO_ARCHIVE_APIS

// ------------------- Low-level Decompression API Definitions
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_INFLATE_APIS

// Decompression flags used by tinfl_decompress().
// TINFL_FLAG_PARSE_ZLIB_HEADER: If set, the input has a valid zlib header and ends with an adler32 checksum (it's a valid zlib stream). Otherwise, the input is a raw deflate stream.
// TINFL_FLAG_HAS_MORE_INPUT: If set, there are more input bytes available beyond the end of the supplied input buffer. If clear, the input buffer contains all remaining input.
// TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF: If set, the output buffer is large enough to hold the entire decompressed stream. If clear, the output buffer is at least the size of the dictionary (typically 32KB).
// TINFL_FLAG_COMPUTE_ADLER32: Force adler-32 checksum computation of the decompressed bytes.
ಎಣಿಕೆ
{
  TINFL_FLAG_PARSE_ZLIB_ಶೀರ್ಷಿಕೆ = 1,
  TINFL_FLAG_HAS_ಇನ್ನಷ್ಟು_ಒಳಹರಿವು = 2,
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
MINIZ_STATIC ಶೂನ್ಯ *tinfl_decompress_mem_ಗಮ್ಯ_ರಾಶಿ(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *pSrc_buf, size_t src_buf_len, size_t *p_ಹೊರಹೋಗು_len, ಪೂರ್ಣಾಂಕ flags);

// tinfl_decompress_mem_to_mem() decompresses a block in memory to another block in memory.
// Returns TINFL_DECOMPRESS_MEM_TO_MEM_FAILED on failure, or the number of bytes written on success.
#ವ್ಯಾಖ್ಯಾನಿಸು TINFL_DECOMPRESS_MEM_ಗಮ್ಯ_MEM_FAILED ((size_t)(-1))
MINIZ_STATIC size_t tinfl_decompress_mem_ಗಮ್ಯ_mem(ಶೂನ್ಯ *p_ಹೊರಹೋಗು_buf, size_t ಹೊರಹೋಗು_buf_len, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *pSrc_buf, size_t src_buf_len, ಪೂರ್ಣಾಂಕ flags);

// tinfl_decompress_mem_to_callback() decompresses a block in memory to an internal 32KB buffer, and a user provided callback function will be called to flush the buffer.
// Returns 1 on success or 0 on failure.
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಪೂರ್ಣಾಂಕ (*tinfl_put_buf_func_ptr)(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ* pBuf, ಪೂರ್ಣಾಂಕ len, ಶೂನ್ಯ *pUser);
MINIZ_STATIC ಪೂರ್ಣಾಂಕ tinfl_decompress_mem_ಗಮ್ಯ_callback(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *p_ಒಳ_buf, size_t *p_ಒಳ_buf_ಗಾತ್ರ, tinfl_put_buf_func_ptr pPut_buf_func, ಶೂನ್ಯ *pPut_buf_user, ಪೂರ್ಣಾಂಕ flags);

ರಚನೆ tinfl_decompressor_ಟ್ಯಾಗ್; ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ tinfl_decompressor_ಟ್ಯಾಗ್ tinfl_decompressor;

// Max size of LZ dictionary.
#ವ್ಯಾಖ್ಯಾನಿಸು TINFL_LZ_DICT_ಗಾತ್ರ 32768

// Return status.
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ
{
  TINFL_ಸ್ಥಿತಿ_BAD_PARAM = -3,
  TINFL_ಸ್ಥಿತಿ_ADLER32_MISMATCH = -2,
  TINFL_ಸ್ಥಿತಿ_FAILED = -1,
  TINFL_ಸ್ಥಿತಿ_ಮುಗಿದ = 0,
  TINFL_ಸ್ಥಿತಿ_NEEDS_ಇನ್ನಷ್ಟು_ಒಳಹರಿವು = 1,
  TINFL_ಸ್ಥಿತಿ_HAS_ಇನ್ನಷ್ಟು_OUTPUT = 2
} tinfl_ಸ್ಥಿತಿ;

// Initializes the decompressor to its initial state.
#ವ್ಯಾಖ್ಯಾನಿಸು tinfl_init(r) ಮಾಡು { (r)->m_state = 0; } MZ_MACRO_ಕೊನೆ
#ವ್ಯಾಖ್ಯಾನಿಸು tinfl_get_adler32(r) (r)->m_check_adler32

// Main low-level decompressor coroutine function. This is the only function actually needed for decompression. All the other functions are just high-level helpers for improved usability.
// This is a universal API, i.e. it can be used as a building block to build any desired higher level decompression API. In the limit case, it can be called once per every byte input or output.
MINIZ_STATIC tinfl_ಸ್ಥಿತಿ tinfl_decompress(tinfl_decompressor *r, ಸ್ಥಿರಾಂಕ mz_uint8 *p_ಒಳ_buf_ಮುಂದಿನ, size_t *p_ಒಳ_buf_ಗಾತ್ರ, mz_uint8 *p_ಹೊರಹೋಗು_buf_ಆರಂಭ, mz_uint8 *p_ಹೊರಹೋಗು_buf_ಮುಂದಿನ, size_t *p_ಹೊರಹೋಗು_buf_ಗಾತ್ರ, ಸ್ಥಿರಾಂಕ mz_uint32 decomp_flags);

// Internal/private bits follow.
ಎಣಿಕೆ
{
  TINFL_MAX_HUFF_TABLES = 3, TINFL_MAX_HUFF_SYMBOLS_0 = 288, TINFL_MAX_HUFF_SYMBOLS_1 = 32, TINFL_MAX_HUFF_SYMBOLS_2 = 19,
  TINFL_FAST_LOOKUP_ಬಿಟ್ಟುಗಳು = 10, TINFL_FAST_LOOKUP_ಗಾತ್ರ = 1 << TINFL_FAST_LOOKUP_ಬಿಟ್ಟುಗಳು
};

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
  mz_uint8 m_ಸಂಕೇತ_ಗಾತ್ರ[TINFL_MAX_HUFF_SYMBOLS_0];
  mz_int16 m_look_ಮೇಲೆ[TINFL_FAST_LOOKUP_ಗಾತ್ರ], m_ವೃಕ್ಷ[TINFL_MAX_HUFF_SYMBOLS_0 * 2];
} tinfl_huff_ಕೋಷ್ಟಕ;

#ಆದರೆ MINIZ_HAS_64_ಬಿಟ್_REGISTERS
  #ವ್ಯಾಖ್ಯಾನಿಸು TINFL_USE_64_ಬಿಟ್_BITBUF 1
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ TINFL_USE_64_ಬಿಟ್_BITBUF
  ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ mz_uint64 tinfl_ಬಿಟ್_buf_t;
  #ವ್ಯಾಖ್ಯಾನಿಸು TINFL_BITBUF_ಗಾತ್ರ (64)
#ಇಲ್ಲದಿದ್ದರೆ
  ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ mz_uint32 tinfl_ಬಿಟ್_buf_t;
  #ವ್ಯಾಖ್ಯಾನಿಸು TINFL_BITBUF_ಗಾತ್ರ (32)
#ಆದರೆ_ಅಂತ್ಯ

ರಚನೆ tinfl_decompressor_ಟ್ಯಾಗ್
{
  mz_uint32 m_state, m_ಅಂಕೆ_ಬಿಟ್ಟುಗಳು, m_zhdr0, m_zhdr1, m_z_adler32, m_final, m_type, m_check_adler32, m_dist, m_counter, m_ಅಂಕೆ_extra, m_ಕೋಷ್ಟಕ_sizes[TINFL_MAX_HUFF_TABLES];
  tinfl_ಬಿಟ್_buf_t m_ಬಿಟ್_buf;
  size_t m_dist_from_ಹೊರಹೋಗು_buf_ಆರಂಭ;
  tinfl_huff_ಕೋಷ್ಟಕ m_tables[TINFL_MAX_HUFF_TABLES];
  mz_uint8 m_raw_ಶೀರ್ಷಿಕೆ[4], m_len_codes[TINFL_MAX_HUFF_SYMBOLS_0 + TINFL_MAX_HUFF_SYMBOLS_1 + 137];
};
#ಆದರೆ_ಅಂತ್ಯ /*#ifndef MINIZ_NO_INFLATE_APIS*/

// ------------------- Low-level Compression API Definitions
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_DEFLATE_APIS

// Set TDEFL_LESS_MEMORY to 1 to use less memory (compression will be slightly slower, and raw/dynamic blocks will be output more frequently).
#ವ್ಯಾಖ್ಯಾನಿಸು TDEFL_LESS_ಸ್ಮರಣೆ 0

// tdefl_init() compression flags logically OR'd together (low 12 bits contain the max. number of probes per dictionary search):
// TDEFL_DEFAULT_MAX_PROBES: The compressor defaults to 128 dictionary probes per dictionary search. 0=Huffman only, 1=Huffman+LZ (fastest/crap compression), 4095=Huffman+LZ (slowest/best compression).
ಎಣಿಕೆ
{
  TDEFL_HUFFMAN_ONLY = 0, TDEFL_DEFAULT_MAX_PROBES = 128, TDEFL_MAX_PROBES_ಮುಖವಾಡ = 0xFFF
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
ಎಣಿಕೆ
{
  TDEFL_WRITE_ZLIB_ಶೀರ್ಷಿಕೆ             = 0x01000,
  TDEFL_COMPUTE_ADLER32               = 0x02000,
  TDEFL_GREEDY_PARSING_FLAG           = 0x04000,
  TDEFL_NONDETERMINISTIC_PARSING_FLAG = 0x08000,
  TDEFL_RLE_MATCHES                   = 0x10000,
  TDEFL_FILTER_MATCHES                = 0x20000,
  TDEFL_FORCE_ALL_STATIC_ಖಂಡಗಳು       = 0x40000,
  TDEFL_FORCE_ALL_RAW_ಖಂಡಗಳು          = 0x80000
};

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_SDL_NOUNUSED
// High level compression functions:
// tdefl_compress_mem_to_heap() compresses a block in memory to a heap block allocated via malloc().
// On entry:
//  pSrc_buf, src_buf_len: Pointer and size of source block to compress.
//  flags: The max match finder probes (default is 128) logically OR'd against the above flags. Higher probes are slower but improve compression.
// On return:
//  Function returns a pointer to the compressed data, or NULL on failure.
//  *pOut_len will be set to the compressed data's size, which could be larger than src_buf_len on uncompressible data.
//  The caller must free() the returned block when it's no longer needed.
MINIZ_STATIC ಶೂನ್ಯ *tdefl_compress_mem_ಗಮ್ಯ_ರಾಶಿ(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *pSrc_buf, size_t src_buf_len, size_t *p_ಹೊರಹೋಗು_len, ಪೂರ್ಣಾಂಕ flags);

// tdefl_compress_mem_to_mem() compresses a block in memory to another block in memory.
// Returns 0 on failure.
MINIZ_STATIC size_t tdefl_compress_mem_ಗಮ್ಯ_mem(ಶೂನ್ಯ *p_ಹೊರಹೋಗು_buf, size_t ಹೊರಹೋಗು_buf_len, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *pSrc_buf, size_t src_buf_len, ಪೂರ್ಣಾಂಕ flags);
#ಆದರೆ_ಅಂತ್ಯ /* MINIZ_SDL_NOUNUSED */

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
MINIZ_STATIC ಶೂನ್ಯ *tdefl_write_image_ಗಮ್ಯ_png_file_ಒಳ_ಸ್ಮರಣೆ_ex(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *pImage, ಪೂರ್ಣಾಂಕ w, ಪೂರ್ಣಾಂಕ h, ಪೂರ್ಣಾಂಕ ಅಂಕೆ_chans, ಪೂರ್ಣಾಂಕ bpl, size_t *p_Len_ಹೊರಹೋಗು, mz_uint level, mz_bool flip, mz_uint8 *plte, ಪೂರ್ಣಾಂಕ plte_ಗಾತ್ರ, mz_uint8 *trns, ಪೂರ್ಣಾಂಕ trns_ಗಾತ್ರ);
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_SDL_NOUNUSED
MINIZ_STATIC ಶೂನ್ಯ *tdefl_write_image_ಗಮ್ಯ_png_file_ಒಳ_ಸ್ಮರಣೆ(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *pImage, ಪೂರ್ಣಾಂಕ w, ಪೂರ್ಣಾಂಕ h, ಪೂರ್ಣಾಂಕ ಅಂಕೆ_chans, ಪೂರ್ಣಾಂಕ bpl, size_t *p_Len_ಹೊರಹೋಗು);
#ಆದರೆ_ಅಂತ್ಯ

// Output stream interface. The compressor uses this interface to write compressed data. It'll typically be called TDEFL_OUT_BUF_SIZE at a time.
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ mz_bool (*tdefl_put_buf_func_ptr)(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ* pBuf, ಪೂರ್ಣಾಂಕ len, ಶೂನ್ಯ *pUser);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_SDL_NOUNUSED
// tdefl_compress_mem_to_output() compresses a block to an output stream. The above helpers use this function internally.
MINIZ_STATIC mz_bool tdefl_compress_mem_ಗಮ್ಯ_output(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *pBuf, size_t buf_len, tdefl_put_buf_func_ptr pPut_buf_func, ಶೂನ್ಯ *pPut_buf_user, ಪೂರ್ಣಾಂಕ flags);
#ಆದರೆ_ಅಂತ್ಯ

//enum { TDEFL_MAX_HUFF_TABLES = 3, TDEFL_MAX_HUFF_SYMBOLS_0 = 288, TDEFL_MAX_HUFF_SYMBOLS_1 = 32, TDEFL_MAX_HUFF_SYMBOLS_2 = 19, TDEFL_LZ_DICT_SIZE = 32768, TDEFL_LZ_DICT_SIZE_MASK = TDEFL_LZ_DICT_SIZE - 1, TDEFL_MIN_MATCH_LEN = 3, TDEFL_MAX_MATCH_LEN = 258 };
#ವ್ಯಾಖ್ಯಾನಿಸು TDEFL_MAX_HUFF_TABLES	3
#ವ್ಯಾಖ್ಯಾನಿಸು TDEFL_MAX_HUFF_SYMBOLS_0 288
#ವ್ಯಾಖ್ಯಾನಿಸು TDEFL_MAX_HUFF_SYMBOLS_1 32
#ವ್ಯಾಖ್ಯಾನಿಸು TDEFL_MAX_HUFF_SYMBOLS_2 19
#ವ್ಯಾಖ್ಯಾನಿಸು TDEFL_LZ_DICT_ಗಾತ್ರ 32768
#ವ್ಯಾಖ್ಯಾನಿಸು TDEFL_LZ_DICT_ಗಾತ್ರ_ಮುಖವಾಡ	( TDEFL_LZ_DICT_ಗಾತ್ರ - 1 )
#ವ್ಯಾಖ್ಯಾನಿಸು TDEFL_MIN_ಹೊಂದಿಕೆ_LEN	3
#ವ್ಯಾಖ್ಯಾನಿಸು TDEFL_MAX_ಹೊಂದಿಕೆ_LEN 258

// TDEFL_OUT_BUF_SIZE MUST be large enough to hold a single entire compressed output block (using static/fixed Huffman codes).
#ಆದರೆ TDEFL_LESS_ಸ್ಮರಣೆ
ಎಣಿಕೆ { TDEFL_LZ_ಸಂಕೇತ_BUF_ಗಾತ್ರ = 24 * 1024, TDEFL_ಹೊರಹೋಗು_BUF_ಗಾತ್ರ = (TDEFL_LZ_ಸಂಕೇತ_BUF_ಗಾತ್ರ * 13 ) / 10, TDEFL_MAX_HUFF_SYMBOLS = 288, TDEFL_LZ_HASH_ಬಿಟ್ಟುಗಳು = 12, TDEFL_LEVEL1_HASH_ಗಾತ್ರ_ಮುಖವಾಡ = 4095, TDEFL_LZ_HASH_ಸರಿಸು = (TDEFL_LZ_HASH_ಬಿಟ್ಟುಗಳು + 2) / 3, TDEFL_LZ_HASH_ಗಾತ್ರ = 1 << TDEFL_LZ_HASH_ಬಿಟ್ಟುಗಳು };
#ಇಲ್ಲದಿದ್ದರೆ
ಎಣಿಕೆ { TDEFL_LZ_ಸಂಕೇತ_BUF_ಗಾತ್ರ = 64 * 1024, TDEFL_ಹೊರಹೋಗು_BUF_ಗಾತ್ರ = (TDEFL_LZ_ಸಂಕೇತ_BUF_ಗಾತ್ರ * 13 ) / 10, TDEFL_MAX_HUFF_SYMBOLS = 288, TDEFL_LZ_HASH_ಬಿಟ್ಟುಗಳು = 15, TDEFL_LEVEL1_HASH_ಗಾತ್ರ_ಮುಖವಾಡ = 4095, TDEFL_LZ_HASH_ಸರಿಸು = (TDEFL_LZ_HASH_ಬಿಟ್ಟುಗಳು + 2) / 3, TDEFL_LZ_HASH_ಗಾತ್ರ = 1 << TDEFL_LZ_HASH_ಬಿಟ್ಟುಗಳು };
#ಆದರೆ_ಅಂತ್ಯ

// The low-level tdefl functions below may be used directly if the above helper functions aren't flexible enough. The low-level functions don't make any heap allocations, unlike the above helper functions.
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ
{
  TDEFL_ಸ್ಥಿತಿ_BAD_PARAM = -2,
  TDEFL_ಸ್ಥಿತಿ_PUT_BUF_FAILED = -1,
  TDEFL_ಸ್ಥಿತಿ_OKAY = 0,
  TDEFL_ಸ್ಥಿತಿ_ಮುಗಿದ = 1,
} tdefl_ಸ್ಥಿತಿ;

// Must map to MZ_NO_FLUSH, MZ_SYNC_FLUSH, etc. enums
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ
{
  TDEFL_NO_FLUSH = 0,
  TDEFL_SYNC_FLUSH = 2,
  TDEFL_ತುಂಬಿದ_FLUSH = 3,
  TDEFL_ಮುಕ್ತಾಯ = 4
} tdefl_flush;

// tdefl's compression state structure.
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
  tdefl_put_buf_func_ptr m_pPut_buf_func;
  ಶೂನ್ಯ *m_pPut_buf_user;
  mz_uint m_flags, m_max_probes[2];
  ಪೂರ್ಣಾಂಕ m_greedy_parsing;
  mz_uint m_adler32, m_lookahead_pos, m_lookahead_ಗಾತ್ರ, m_dict_ಗಾತ್ರ;
  mz_uint8 *m_p_LZ_ಸಂಕೇತ_buf, *m_pLZ_flags, *m_pOutput_buf, *m_p_Output_buf_ಕೊನೆ;
  mz_uint m_ಅಂಕೆ_flags_ಎಡ, m_ಒಟ್ಟು_lz_ಬೈಟುಗಳು, m_lz_ಸಂಕೇತ_buf_dict_pos, m_ಬಿಟ್ಟುಗಳು_ಒಳ, m_ಬಿಟ್_ಬಫರ್;
  mz_uint m_saved_ಹೊಂದಿಕೆ_dist, m_saved_ಹೊಂದಿಕೆ_len, m_saved_lit, m_output_flush_ofs, m_output_flush_ಉಳಿದ, m_ಪೂರ್ಣಗೊಂಡ, m_ಖಂಡ_ಸೂಚ್ಯಂಕ, m_ಬಯಸುತ್ತದೆ_ಗಮ್ಯ_ಮುಕ್ತಾಯ;
  tdefl_ಸ್ಥಿತಿ m_prev_return_ಸ್ಥಿತಿ;
  ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *m_p_ಒಳ_buf;
  ಶೂನ್ಯ *m_p_ಹೊರಹೋಗು_buf;
  size_t *m_p_ಒಳ_buf_ಗಾತ್ರ, *m_p_ಹೊರಹೋಗು_buf_ಗಾತ್ರ;
  tdefl_flush m_flush;
  ಸ್ಥಿರಾಂಕ mz_uint8 *m_pSrc;
  size_t m_src_buf_ಎಡ, m_ಹೊರಹೋಗು_buf_ofs;
  mz_uint8 m_dict[TDEFL_LZ_DICT_ಗಾತ್ರ + TDEFL_MAX_ಹೊಂದಿಕೆ_LEN - 1];
  mz_uint16 m_huff_ಎಣಿಕೆ[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint16 m_huff_codes[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint8 m_huff_ಸಂಕೇತ_sizes[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint8 m_lz_ಸಂಕೇತ_buf[TDEFL_LZ_ಸಂಕೇತ_BUF_ಗಾತ್ರ];
  mz_uint16 m_ಮುಂದಿನ[TDEFL_LZ_DICT_ಗಾತ್ರ];
  mz_uint16 m_hash[TDEFL_LZ_HASH_ಗಾತ್ರ];
  mz_uint8 m_output_buf[TDEFL_ಹೊರಹೋಗು_BUF_ಗಾತ್ರ];
} tdefl_compressor;

// Initializes the compressor.
// There is no corresponding deinit() function because the tdefl API's do not dynamically allocate memory.
// pBut_buf_func: If NULL, output data will be supplied to the specified callback. In this case, the user should call the tdefl_compress_buffer() API for compression.
// If pBut_buf_func is NULL the user should always call the tdefl_compress() API.
// flags: See the above enums (TDEFL_HUFFMAN_ONLY, TDEFL_WRITE_ZLIB_HEADER, etc.)
MINIZ_STATIC tdefl_ಸ್ಥಿತಿ tdefl_init(tdefl_compressor *d, tdefl_put_buf_func_ptr pPut_buf_func, ಶೂನ್ಯ *pPut_buf_user, ಪೂರ್ಣಾಂಕ flags);

// Compresses a block of data, consuming as much of the specified input buffer as possible, and writing as much compressed data to the specified output buffer as possible.
MINIZ_STATIC tdefl_ಸ್ಥಿತಿ tdefl_compress(tdefl_compressor *d, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *p_ಒಳ_buf, size_t *p_ಒಳ_buf_ಗಾತ್ರ, ಶೂನ್ಯ *p_ಹೊರಹೋಗು_buf, size_t *p_ಹೊರಹೋಗು_buf_ಗಾತ್ರ, tdefl_flush flush);

// tdefl_compress_buffer() is only usable when the tdefl_init() is called with a non-NULL tdefl_put_buf_func_ptr.
// tdefl_compress_buffer() always consumes the entire input buffer.
MINIZ_STATIC tdefl_ಸ್ಥಿತಿ tdefl_compress_ಬಫರ್(tdefl_compressor *d, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *p_ಒಳ_buf, size_t ಒಳ_buf_ಗಾತ್ರ, tdefl_flush flush);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_SDL_NOUNUSED
MINIZ_STATIC tdefl_ಸ್ಥಿತಿ tdefl_get_prev_return_ಸ್ಥಿತಿ(tdefl_compressor *d);
MINIZ_STATIC mz_uint32 tdefl_get_adler32(tdefl_compressor *d);
#ಆದರೆ_ಅಂತ್ಯ

// Can't use tdefl_create_comp_flags_from_zip_params if MINIZ_NO_ZLIB_APIS isn't defined, because it uses some of its macros.
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_ZLIB_APIS
// Create tdefl_compress() flags given zlib-style compression parameters.
// level may range from [0,10] (where 10 is absolute max compression, but may be much slower on some files)
// window_bits may be -15 (raw deflate) or 15 (zlib)
// strategy may be either MZ_DEFAULT_STRATEGY, MZ_FILTERED, MZ_HUFFMAN_ONLY, MZ_RLE, or MZ_FIXED
MINIZ_STATIC mz_uint tdefl_create_comp_flags_from_zip_params(ಪೂರ್ಣಾಂಕ level, ಪೂರ್ಣಾಂಕ ಕಿಟಕಿ_ಬಿಟ್ಟುಗಳು, ಪೂರ್ಣಾಂಕ strategy);
#ಆದರೆ_ಅಂತ್ಯ // #ifndef MINIZ_NO_ZLIB_APIS

#ಆದರೆ_ಅಂತ್ಯ /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ // MINIZ_HEADER_INCLUDED

// ------------------- End of Header: Implementation follows. (If you only want the header, define MINIZ_HEADER_FILE_ONLY.)

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_ಶೀರ್ಷಿಕೆ_FILE_ONLY

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _MSC_VER
#ಸೂಚನೆ warning (ತಳ್ಳು)
#ಸೂಚನೆ warning (disable:4505) // unreferenced local function has been removed
#ಆದರೆ_ಅಂತ್ಯ

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ mz_validate_uint16[ಗಾತ್ರ(mz_uint16)==2 ? 1 : -1];
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ mz_validate_uint32[ಗಾತ್ರ(mz_uint32)==4 ? 1 : -1];
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ mz_validate_uint64[ಗಾತ್ರ(mz_uint64)==8 ? 1 : -1];

/*#include <string.h>*/

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MZ_ASSERT
#ಅನ್ತರ್ಭಾವ <assert.h>
#ವ್ಯಾಖ್ಯಾನಿಸು MZ_ASSERT(x) ಪ್ರತಿಜ್ಞಾ(x)
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ MINIZ_NO_MALLOC
  #ವ್ಯಾಖ್ಯಾನಿಸು MZ_MALLOC(x) ಖಾಲಿ
  #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FREE(x) (ಶೂನ್ಯ)x, ((ಶೂನ್ಯ)0)
  #ವ್ಯಾಖ್ಯಾನಿಸು MZ_REALLOC(p, x) ಖಾಲಿ
#ಅಥವಾಆದರೆ defined(MINIZ_SDL_MALLOC)
  #ವ್ಯಾಖ್ಯಾನಿಸು MZ_MALLOC(x) SDL_malloc(x)
  #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FREE(x) SDL_free(x)
  #ವ್ಯಾಖ್ಯಾನಿಸು MZ_REALLOC(p, x) SDL_realloc(p, x)
#ಇಲ್ಲದಿದ್ದರೆ
  #ವ್ಯಾಖ್ಯಾನಿಸು MZ_MALLOC(x) ಸ್ಮರಣೆ_ಕೊಡು(x)
  #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FREE(x) ಬಿಡುಗಡೆ(x)
  #ವ್ಯಾಖ್ಯಾನಿಸು MZ_REALLOC(p, x) realloc(p, x)
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿಸು MZ_MAX(a,b) (((a)>(b))?(a):(b))
#ವ್ಯಾಖ್ಯಾನಿಸು MZ_MIN(a,b) (((a)<(b))?(a):(b))
#ವ್ಯಾಖ್ಯಾನಿಸು MZ_CLEAR_OBJ(obj) memset(&(obj), 0, ಗಾತ್ರ(obj))
#ವ್ಯಾಖ್ಯಾನಿಸು MZ_CLEAR_ARR(obj) memset((obj), 0, ಗಾತ್ರ(obj))
#ವ್ಯಾಖ್ಯಾನಿಸು MZ_CLEAR_PTR(obj) memset((obj), 0, ಗಾತ್ರ(*obj))

#ಆದರೆ MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  #ವ್ಯಾಖ್ಯಾನಿಸು MZ_READ_LE16(p) *((ಸ್ಥಿರಾಂಕ mz_uint16 *)(p))
  #ವ್ಯಾಖ್ಯಾನಿಸು MZ_READ_LE32(p) *((ಸ್ಥಿರಾಂಕ mz_uint32 *)(p))
#ಇಲ್ಲದಿದ್ದರೆ
  #ವ್ಯಾಖ್ಯಾನಿಸು MZ_READ_LE16(p) ((mz_uint32)(((ಸ್ಥಿರಾಂಕ mz_uint8 *)(p))[0]) | ((mz_uint32)(((ಸ್ಥಿರಾಂಕ mz_uint8 *)(p))[1]) << 8U))
  #ವ್ಯಾಖ್ಯಾನಿಸು MZ_READ_LE32(p) ((mz_uint32)(((ಸ್ಥಿರಾಂಕ mz_uint8 *)(p))[0]) | ((mz_uint32)(((ಸ್ಥಿರಾಂಕ mz_uint8 *)(p))[1]) << 8U) | ((mz_uint32)(((ಸ್ಥಿರಾಂಕ mz_uint8 *)(p))[2]) << 16U) | ((mz_uint32)(((ಸ್ಥಿರಾಂಕ mz_uint8 *)(p))[3]) << 24U))
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _MSC_VER
  #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FORCEINLINE __forceinline
#ಅಥವಾಆದರೆ defined(__GNUC__)
  #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FORCEINLINE ಸಾಲೊಳಗೆ __attribute__((__always_inline__))
#ಇಲ್ಲದಿದ್ದರೆ
  #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FORCEINLINE ಸಾಲೊಳಗೆ
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
  ಬಾಹ್ಯ "C" {
#ಆದರೆ_ಅಂತ್ಯ

// ------------------- zlib-style API's

mz_ulong mz_adler32(mz_ulong adler, ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *ptr, size_t buf_len)
{
  mz_uint32 i, s1 = (mz_uint32)(adler & 0xffff), s2 = (mz_uint32)(adler >> 16); size_t ಖಂಡ_len = buf_len % 5552;
  ಆದರೆ (!ptr) ಹಿಂತಿರುಗಿ MZ_ADLER32_INIT;
  ಆಗ (buf_len) {
    ಗಾಗಿ (i = 0; i + 7 < ಖಂಡ_len; i += 8, ptr += 8) {
      s1 += ptr[0]; s2 += s1; s1 += ptr[1]; s2 += s1; s1 += ptr[2]; s2 += s1; s1 += ptr[3]; s2 += s1;
      s1 += ptr[4]; s2 += s1; s1 += ptr[5]; s2 += s1; s1 += ptr[6]; s2 += s1; s1 += ptr[7]; s2 += s1;
    }
    ಗಾಗಿ ( ; i < ಖಂಡ_len; ++i) { s1 += *ptr++; s2 += s1; }
    s1 %= 65521U; s2 %= 65521U; buf_len -= ಖಂಡ_len; ಖಂಡ_len = 5552;
  }
  ಹಿಂತಿರುಗಿ (s2 << 16) + s1;
}

// Karl Malbrain's compact CRC-32. See "A compact CCITT crc16 and crc32 C implementation that balances processor cache usage against speed": http://www.geocities.com/malbrain/
mz_ulong mz_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32(mz_ulong ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ, ಸ್ಥಿರಾಂಕ mz_uint8 *ptr, size_t buf_len)
{
  ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ mz_uint32 s_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32[16] = { 0, 0x1db71064, 0x3b6e20c8, 0x26d930ac, 0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
    0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c, 0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c };
  mz_uint32 crcu32 = (mz_uint32)ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ;
  ಆದರೆ (!ptr) ಹಿಂತಿರುಗಿ MZ_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_INIT;
  crcu32 = ~crcu32; ಆಗ (buf_len--) { mz_uint8 b = *ptr++; crcu32 = (crcu32 >> 4) ^ s_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32[(crcu32 & 0xF) ^ (b & 0xF)]; crcu32 = (crcu32 >> 4) ^ s_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32[(crcu32 & 0xF) ^ (b >> 4)]; }
  ಹಿಂತಿರುಗಿ ~crcu32;
}

MINIZ_STATIC ಶೂನ್ಯ mz_free(ಶೂನ್ಯ *p)
{
  MZ_FREE(p);
}

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_ZLIB_APIS

ಸ್ಥಿರ ಶೂನ್ಯ *def_alloc_func(ಶೂನ್ಯ *opaque, size_t ವಸ್ತುಗಳು, size_t ಗಾತ್ರ_2) { (ಶೂನ್ಯ)opaque, (ಶೂನ್ಯ)ವಸ್ತುಗಳು, (ಶೂನ್ಯ)ಗಾತ್ರ_2; ಹಿಂತಿರುಗಿ MZ_MALLOC(ವಸ್ತುಗಳು * ಗಾತ್ರ_2); }
ಸ್ಥಿರ ಶೂನ್ಯ def_free_func(ಶೂನ್ಯ *opaque, ಶೂನ್ಯ *ವಿಳಾಸ) { (ಶೂನ್ಯ)opaque, (ಶೂನ್ಯ)ವಿಳಾಸ; MZ_FREE(ವಿಳಾಸ); }
ಸ್ಥಿರ ಶೂನ್ಯ *def_realloc_func(ಶೂನ್ಯ *opaque, ಶೂನ್ಯ *ವಿಳಾಸ, size_t ವಸ್ತುಗಳು, size_t ಗಾತ್ರ_2) { (ಶೂನ್ಯ)opaque, (ಶೂನ್ಯ)ವಿಳಾಸ, (ಶೂನ್ಯ)ವಸ್ತುಗಳು, (ಶೂನ್ಯ)ಗಾತ್ರ_2; ಹಿಂತಿರುಗಿ MZ_REALLOC(ವಿಳಾಸ, ವಸ್ತುಗಳು * ಗಾತ್ರ_2); }

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mz_ಆವೃತ್ತಿ(ಶೂನ್ಯ)
{
  ಹಿಂತಿರುಗಿ MZ_ಆವೃತ್ತಿ;
}

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_DEFLATE_APIS

ಪೂರ್ಣಾಂಕ mz_deflateInit(mz_streamp p_ಹರಿವು, ಪೂರ್ಣಾಂಕ level)
{
  ಹಿಂತಿರುಗಿ mz_deflateInit2(p_ಹರಿವು, level, MZ_DEFLATED, MZ_DEFAULT_ಕಿಟಕಿ_ಬಿಟ್ಟುಗಳು, 9, MZ_DEFAULT_STRATEGY);
}

ಪೂರ್ಣಾಂಕ mz_deflateInit2(mz_streamp p_ಹರಿವು, ಪೂರ್ಣಾಂಕ level, ಪೂರ್ಣಾಂಕ ವಿಧಾನ, ಪೂರ್ಣಾಂಕ ಕಿಟಕಿ_ಬಿಟ್ಟುಗಳು, ಪೂರ್ಣಾಂಕ mem_level, ಪೂರ್ಣಾಂಕ strategy)
{
  tdefl_compressor *pComp;
  mz_uint comp_flags = TDEFL_COMPUTE_ADLER32 | tdefl_create_comp_flags_from_zip_params(level, ಕಿಟಕಿ_ಬಿಟ್ಟುಗಳು, strategy);

  ಆದರೆ (!p_ಹರಿವು) ಹಿಂತಿರುಗಿ MZ_ಹರಿವು_ERROR;
  ಆದರೆ ((ವಿಧಾನ != MZ_DEFLATED) || ((mem_level < 1) || (mem_level > 9)) || ((ಕಿಟಕಿ_ಬಿಟ್ಟುಗಳು != MZ_DEFAULT_ಕಿಟಕಿ_ಬಿಟ್ಟುಗಳು) && (-ಕಿಟಕಿ_ಬಿಟ್ಟುಗಳು != MZ_DEFAULT_ಕಿಟಕಿ_ಬಿಟ್ಟುಗಳು))) ಹಿಂತಿರುಗಿ MZ_PARAM_ERROR;

  p_ಹರಿವು->ದತ್ತಾಂಶ_type = 0;
  p_ಹರಿವು->adler = MZ_ADLER32_INIT;
  p_ಹರಿವು->ಸಂದೇಶ_2 = ಖಾಲಿ;
  p_ಹರಿವು->reserved = 0;
  p_ಹರಿವು->ಒಟ್ಟು_ಒಳ = 0;
  p_ಹರಿವು->ಒಟ್ಟು_ಹೊರಹೋಗು = 0;
  ಆದರೆ (!p_ಹರಿವು->zalloc) p_ಹರಿವು->zalloc = def_alloc_func;
  ಆದರೆ (!p_ಹರಿವು->zfree) p_ಹರಿವು->zfree = def_free_func;

  pComp = (tdefl_compressor *)p_ಹರಿವು->zalloc(p_ಹರಿವು->opaque, 1, ಗಾತ್ರ(tdefl_compressor));
  ಆದರೆ (!pComp)
    ಹಿಂತಿರುಗಿ MZ_MEM_ERROR;

  p_ಹರಿವು->state = (ರಚನೆ mz_ಆಂತರಿಕ_state *)pComp;

  ಆದರೆ (tdefl_init(pComp, ಖಾಲಿ, ಖಾಲಿ, comp_flags) != TDEFL_ಸ್ಥಿತಿ_OKAY)
  {
    mz_deflate_ಕೊನೆ(p_ಹರಿವು);
    ಹಿಂತಿರುಗಿ MZ_PARAM_ERROR;
  }

  ಹಿಂತಿರುಗಿ MZ_OK;
}

ಪೂರ್ಣಾಂಕ mz_deflateReset(mz_streamp p_ಹರಿವು)
{
  ಆದರೆ ((!p_ಹರಿವು) || (!p_ಹರಿವು->state) || (!p_ಹರಿವು->zalloc) || (!p_ಹರಿವು->zfree)) ಹಿಂತಿರುಗಿ MZ_ಹರಿವು_ERROR;
  p_ಹರಿವು->ಒಟ್ಟು_ಒಳ = p_ಹರಿವು->ಒಟ್ಟು_ಹೊರಹೋಗು = 0;
  tdefl_init((tdefl_compressor*)p_ಹರಿವು->state, ಖಾಲಿ, ಖಾಲಿ, ((tdefl_compressor*)p_ಹರಿವು->state)->m_flags);
  ಹಿಂತಿರುಗಿ MZ_OK;
}

ಪೂರ್ಣಾಂಕ mz_deflate(mz_streamp p_ಹರಿವು, ಪೂರ್ಣಾಂಕ flush)
{
  size_t ಒಳ_ಬೈಟುಗಳು, ಹೊರಹೋಗು_ಬೈಟುಗಳು;
  mz_ulong orig_ಒಟ್ಟು_ಒಳ, orig_ಒಟ್ಟು_ಹೊರಹೋಗು;
  ಪೂರ್ಣಾಂಕ mz_ಸ್ಥಿತಿ = MZ_OK;

  ಆದರೆ ((!p_ಹರಿವು) || (!p_ಹರಿವು->state) || (flush < 0) || (flush > MZ_ಮುಕ್ತಾಯ) || (!p_ಹರಿವು->ಮುಂದಿನ_ಹೊರಹೋಗು)) ಹಿಂತಿರುಗಿ MZ_ಹರಿವು_ERROR;
  ಆದರೆ (!p_ಹರಿವು->avail_ಹೊರಹೋಗು) ಹಿಂತಿರುಗಿ MZ_BUF_ERROR;

  ಆದರೆ (flush == MZ_PARTIAL_FLUSH) flush = MZ_SYNC_FLUSH;

  ಆದರೆ (((tdefl_compressor*)p_ಹರಿವು->state)->m_prev_return_ಸ್ಥಿತಿ == TDEFL_ಸ್ಥಿತಿ_ಮುಗಿದ)
    ಹಿಂತಿರುಗಿ (flush == MZ_ಮುಕ್ತಾಯ) ? MZ_ಹರಿವು_ಕೊನೆ : MZ_BUF_ERROR;

  orig_ಒಟ್ಟು_ಒಳ = p_ಹರಿವು->ಒಟ್ಟು_ಒಳ; orig_ಒಟ್ಟು_ಹೊರಹೋಗು = p_ಹರಿವು->ಒಟ್ಟು_ಹೊರಹೋಗು;
  ಗಾಗಿ ( ; ; )
  {
    tdefl_ಸ್ಥಿತಿ defl_ಸ್ಥಿತಿ;
    ಒಳ_ಬೈಟುಗಳು = p_ಹರಿವು->avail_ಒಳ; ಹೊರಹೋಗು_ಬೈಟುಗಳು = p_ಹರಿವು->avail_ಹೊರಹೋಗು;

    defl_ಸ್ಥಿತಿ = tdefl_compress((tdefl_compressor*)p_ಹರಿವು->state, p_ಹರಿವು->ಮುಂದಿನ_ಒಳ, &ಒಳ_ಬೈಟುಗಳು, p_ಹರಿವು->ಮುಂದಿನ_ಹೊರಹೋಗು, &ಹೊರಹೋಗು_ಬೈಟುಗಳು, (tdefl_flush)flush);
    p_ಹರಿವು->ಮುಂದಿನ_ಒಳ += (mz_uint)ಒಳ_ಬೈಟುಗಳು; p_ಹರಿವು->avail_ಒಳ -= (mz_uint)ಒಳ_ಬೈಟುಗಳು;
    p_ಹರಿವು->ಒಟ್ಟು_ಒಳ += (mz_uint)ಒಳ_ಬೈಟುಗಳು; p_ಹರಿವು->adler = tdefl_get_adler32((tdefl_compressor*)p_ಹರಿವು->state);

    p_ಹರಿವು->ಮುಂದಿನ_ಹೊರಹೋಗು += (mz_uint)ಹೊರಹೋಗು_ಬೈಟುಗಳು; p_ಹರಿವು->avail_ಹೊರಹೋಗು -= (mz_uint)ಹೊರಹೋಗು_ಬೈಟುಗಳು;
    p_ಹರಿವು->ಒಟ್ಟು_ಹೊರಹೋಗು += (mz_uint)ಹೊರಹೋಗು_ಬೈಟುಗಳು;

    ಆದರೆ (defl_ಸ್ಥಿತಿ < 0)
    {
      mz_ಸ್ಥಿತಿ = MZ_ಹರಿವು_ERROR;
      ನಿಲ್ಲಿಸು;
    }
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (defl_ಸ್ಥಿತಿ == TDEFL_ಸ್ಥಿತಿ_ಮುಗಿದ)
    {
      mz_ಸ್ಥಿತಿ = MZ_ಹರಿವು_ಕೊನೆ;
      ನಿಲ್ಲಿಸು;
    }
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!p_ಹರಿವು->avail_ಹೊರಹೋಗು)
      ನಿಲ್ಲಿಸು;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((!p_ಹರಿವು->avail_ಒಳ) && (flush != MZ_ಮುಕ್ತಾಯ))
    {
      ಆದರೆ ((flush) || (p_ಹರಿವು->ಒಟ್ಟು_ಒಳ != orig_ಒಟ್ಟು_ಒಳ) || (p_ಹರಿವು->ಒಟ್ಟು_ಹೊರಹೋಗು != orig_ಒಟ್ಟು_ಹೊರಹೋಗು))
        ನಿಲ್ಲಿಸು;
      ಹಿಂತಿರುಗಿ MZ_BUF_ERROR; // Can't make forward progress without some input.
    }
  }
  ಹಿಂತಿರುಗಿ mz_ಸ್ಥಿತಿ;
}

ಪೂರ್ಣಾಂಕ mz_deflate_ಕೊನೆ(mz_streamp p_ಹರಿವು)
{
  ಆದರೆ (!p_ಹರಿವು) ಹಿಂತಿರುಗಿ MZ_ಹರಿವು_ERROR;
  ಆದರೆ (p_ಹರಿವು->state)
  {
    p_ಹರಿವು->zfree(p_ಹರಿವು->opaque, p_ಹರಿವು->state);
    p_ಹರಿವು->state = ಖಾಲಿ;
  }
  ಹಿಂತಿರುಗಿ MZ_OK;
}

mz_ulong mz_deflateBound(mz_streamp p_ಹರಿವು, mz_ulong ಮೂಲ_len)
{
  (ಶೂನ್ಯ)p_ಹರಿವು;
  // This is really over conservative. (And lame, but it's actually pretty tricky to compute a true upper bound given the way tdefl's blocking works.)
  ಹಿಂತಿರುಗಿ MZ_MAX(128 + (ಮೂಲ_len * 110) / 100, 128 + ಮೂಲ_len + ((ಮೂಲ_len / (31 * 1024)) + 1) * 5);
}

ಪೂರ್ಣಾಂಕ mz_compress2(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *pDest, mz_ulong *pDest_len, ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *p_ಮೂಲ, mz_ulong ಮೂಲ_len, ಪೂರ್ಣಾಂಕ level)
{
  ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_2;
  mz_ಹರಿವು ಹರಿವು;
  memset(&ಹರಿವು, 0, ಗಾತ್ರ(ಹರಿವು));

  // In case mz_ulong is 64-bits (argh I hate longs).
  ಆದರೆ ((ಮೂಲ_len | *pDest_len) > 0xFFFFFFFFU) ಹಿಂತಿರುಗಿ MZ_PARAM_ERROR;

  ಹರಿವು.ಮುಂದಿನ_ಒಳ = p_ಮೂಲ;
  ಹರಿವು.avail_ಒಳ = (mz_uint32)ಮೂಲ_len;
  ಹರಿವು.ಮುಂದಿನ_ಹೊರಹೋಗು = pDest;
  ಹರಿವು.avail_ಹೊರಹೋಗು = (mz_uint32)*pDest_len;

  ಸ್ಥಿತಿ_2 = mz_deflateInit(&ಹರಿವು, level);
  ಆದರೆ (ಸ್ಥಿತಿ_2 != MZ_OK) ಹಿಂತಿರುಗಿ ಸ್ಥಿತಿ_2;

  ಸ್ಥಿತಿ_2 = mz_deflate(&ಹರಿವು, MZ_ಮುಕ್ತಾಯ);
  ಆದರೆ (ಸ್ಥಿತಿ_2 != MZ_ಹರಿವು_ಕೊನೆ)
  {
    mz_deflate_ಕೊನೆ(&ಹರಿವು);
    ಹಿಂತಿರುಗಿ (ಸ್ಥಿತಿ_2 == MZ_OK) ? MZ_BUF_ERROR : ಸ್ಥಿತಿ_2;
  }

  *pDest_len = ಹರಿವು.ಒಟ್ಟು_ಹೊರಹೋಗು;
  ಹಿಂತಿರುಗಿ mz_deflate_ಕೊನೆ(&ಹರಿವು);
}

ಪೂರ್ಣಾಂಕ mz_compress(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *pDest, mz_ulong *pDest_len, ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *p_ಮೂಲ, mz_ulong ಮೂಲ_len)
{
  ಹಿಂತಿರುಗಿ mz_compress2(pDest, pDest_len, p_ಮೂಲ, ಮೂಲ_len, MZ_DEFAULT_COMPRESSION);
}

mz_ulong mz_compressBound(mz_ulong ಮೂಲ_len)
{
  ಹಿಂತಿರುಗಿ mz_deflateBound(ಖಾಲಿ, ಮೂಲ_len);
}

#ಆದರೆ_ಅಂತ್ಯ /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_INFLATE_APIS

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
  tinfl_decompressor m_decomp;
  mz_uint m_dict_ofs, m_dict_avail, m_ಮೊದಲ_call, m_has_flushed; ಪೂರ್ಣಾಂಕ m_ಕಿಟಕಿ_ಬಿಟ್ಟುಗಳು;
  mz_uint8 m_dict[TINFL_LZ_DICT_ಗಾತ್ರ];
  tinfl_ಸ್ಥಿತಿ m_ಕೊನೆಯ_ಸ್ಥಿತಿ;
} inflate_state;

ಪೂರ್ಣಾಂಕ mz_inflateInit2(mz_streamp p_ಹರಿವು, ಪೂರ್ಣಾಂಕ ಕಿಟಕಿ_ಬಿಟ್ಟುಗಳು)
{
  inflate_state *pDecomp;
  ಆದರೆ (!p_ಹರಿವು) ಹಿಂತಿರುಗಿ MZ_ಹರಿವು_ERROR;
  ಆದರೆ ((ಕಿಟಕಿ_ಬಿಟ್ಟುಗಳು != MZ_DEFAULT_ಕಿಟಕಿ_ಬಿಟ್ಟುಗಳು) && (-ಕಿಟಕಿ_ಬಿಟ್ಟುಗಳು != MZ_DEFAULT_ಕಿಟಕಿ_ಬಿಟ್ಟುಗಳು)) ಹಿಂತಿರುಗಿ MZ_PARAM_ERROR;

  p_ಹರಿವು->ದತ್ತಾಂಶ_type = 0;
  p_ಹರಿವು->adler = 0;
  p_ಹರಿವು->ಸಂದೇಶ_2 = ಖಾಲಿ;
  p_ಹರಿವು->ಒಟ್ಟು_ಒಳ = 0;
  p_ಹರಿವು->ಒಟ್ಟು_ಹೊರಹೋಗು = 0;
  p_ಹರಿವು->reserved = 0;
  ಆದರೆ (!p_ಹರಿವು->zalloc) p_ಹರಿವು->zalloc = def_alloc_func;
  ಆದರೆ (!p_ಹರಿವು->zfree) p_ಹರಿವು->zfree = def_free_func;

  pDecomp = (inflate_state*)p_ಹರಿವು->zalloc(p_ಹರಿವು->opaque, 1, ಗಾತ್ರ(inflate_state));
  ಆದರೆ (!pDecomp) ಹಿಂತಿರುಗಿ MZ_MEM_ERROR;

  p_ಹರಿವು->state = (ರಚನೆ mz_ಆಂತರಿಕ_state *)pDecomp;

  tinfl_init(&pDecomp->m_decomp);
  pDecomp->m_dict_ofs = 0;
  pDecomp->m_dict_avail = 0;
  pDecomp->m_ಕೊನೆಯ_ಸ್ಥಿತಿ = TINFL_ಸ್ಥಿತಿ_NEEDS_ಇನ್ನಷ್ಟು_ಒಳಹರಿವು;
  pDecomp->m_ಮೊದಲ_call = 1;
  pDecomp->m_has_flushed = 0;
  pDecomp->m_ಕಿಟಕಿ_ಬಿಟ್ಟುಗಳು = ಕಿಟಕಿ_ಬಿಟ್ಟುಗಳು;

  ಹಿಂತಿರುಗಿ MZ_OK;
}

ಪೂರ್ಣಾಂಕ mz_inflateInit(mz_streamp p_ಹರಿವು)
{
   ಹಿಂತಿರುಗಿ mz_inflateInit2(p_ಹರಿವು, MZ_DEFAULT_ಕಿಟಕಿ_ಬಿಟ್ಟುಗಳು);
}

ಪೂರ್ಣಾಂಕ mz_inflate(mz_streamp p_ಹರಿವು, ಪೂರ್ಣಾಂಕ flush)
{
  inflate_state* pState;
  mz_uint n, ಮೊದಲ_call, decomp_flags = TINFL_FLAG_COMPUTE_ADLER32;
  size_t ಒಳ_ಬೈಟುಗಳು, ಹೊರಹೋಗು_ಬೈಟುಗಳು, orig_avail_ಒಳ;
  tinfl_ಸ್ಥಿತಿ ಸ್ಥಿತಿ_2;

  ಆದರೆ ((!p_ಹರಿವು) || (!p_ಹರಿವು->state)) ಹಿಂತಿರುಗಿ MZ_ಹರಿವು_ERROR;
  ಆದರೆ (flush == MZ_PARTIAL_FLUSH) flush = MZ_SYNC_FLUSH;
  ಆದರೆ ((flush) && (flush != MZ_SYNC_FLUSH) && (flush != MZ_ಮುಕ್ತಾಯ)) ಹಿಂತಿರುಗಿ MZ_ಹರಿವು_ERROR;

  pState = (inflate_state*)p_ಹರಿವು->state;
  ಆದರೆ (pState->m_ಕಿಟಕಿ_ಬಿಟ್ಟುಗಳು > 0) decomp_flags |= TINFL_FLAG_PARSE_ZLIB_ಶೀರ್ಷಿಕೆ;
  orig_avail_ಒಳ = p_ಹರಿವು->avail_ಒಳ;

  ಮೊದಲ_call = pState->m_ಮೊದಲ_call; pState->m_ಮೊದಲ_call = 0;
  ಆದರೆ (pState->m_ಕೊನೆಯ_ಸ್ಥಿತಿ < 0) ಹಿಂತಿರುಗಿ MZ_ದತ್ತಾಂಶ_ERROR;

  ಆದರೆ (pState->m_has_flushed && (flush != MZ_ಮುಕ್ತಾಯ)) ಹಿಂತಿರುಗಿ MZ_ಹರಿವು_ERROR;
  pState->m_has_flushed |= (flush == MZ_ಮುಕ್ತಾಯ);

  ಆದರೆ ((flush == MZ_ಮುಕ್ತಾಯ) && (ಮೊದಲ_call))
  {
    // MZ_FINISH on the first call implies that the input and output buffers are large enough to hold the entire compressed/decompressed file.
    decomp_flags |= TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF;
    ಒಳ_ಬೈಟುಗಳು = p_ಹರಿವು->avail_ಒಳ; ಹೊರಹೋಗು_ಬೈಟುಗಳು = p_ಹರಿವು->avail_ಹೊರಹೋಗು;
    ಸ್ಥಿತಿ_2 = tinfl_decompress(&pState->m_decomp, p_ಹರಿವು->ಮುಂದಿನ_ಒಳ, &ಒಳ_ಬೈಟುಗಳು, p_ಹರಿವು->ಮುಂದಿನ_ಹೊರಹೋಗು, p_ಹರಿವು->ಮುಂದಿನ_ಹೊರಹೋಗು, &ಹೊರಹೋಗು_ಬೈಟುಗಳು, decomp_flags);
    pState->m_ಕೊನೆಯ_ಸ್ಥಿತಿ = ಸ್ಥಿತಿ_2;
    p_ಹರಿವು->ಮುಂದಿನ_ಒಳ += (mz_uint)ಒಳ_ಬೈಟುಗಳು; p_ಹರಿವು->avail_ಒಳ -= (mz_uint)ಒಳ_ಬೈಟುಗಳು; p_ಹರಿವು->ಒಟ್ಟು_ಒಳ += (mz_uint)ಒಳ_ಬೈಟುಗಳು;
    p_ಹರಿವು->adler = tinfl_get_adler32(&pState->m_decomp);
    p_ಹರಿವು->ಮುಂದಿನ_ಹೊರಹೋಗು += (mz_uint)ಹೊರಹೋಗು_ಬೈಟುಗಳು; p_ಹರಿವು->avail_ಹೊರಹೋಗು -= (mz_uint)ಹೊರಹೋಗು_ಬೈಟುಗಳು; p_ಹರಿವು->ಒಟ್ಟು_ಹೊರಹೋಗು += (mz_uint)ಹೊರಹೋಗು_ಬೈಟುಗಳು;

    ಆದರೆ (ಸ್ಥಿತಿ_2 < 0)
      ಹಿಂತಿರುಗಿ MZ_ದತ್ತಾಂಶ_ERROR;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಸ್ಥಿತಿ_2 != TINFL_ಸ್ಥಿತಿ_ಮುಗಿದ)
    {
      pState->m_ಕೊನೆಯ_ಸ್ಥಿತಿ = TINFL_ಸ್ಥಿತಿ_FAILED;
      ಹಿಂತಿರುಗಿ MZ_BUF_ERROR;
    }
    ಹಿಂತಿರುಗಿ MZ_ಹರಿವು_ಕೊನೆ;
  }
  // flush != MZ_FINISH then we must assume there's more input.
  ಆದರೆ (flush != MZ_ಮುಕ್ತಾಯ) decomp_flags |= TINFL_FLAG_HAS_ಇನ್ನಷ್ಟು_ಒಳಹರಿವು;

  ಆದರೆ (pState->m_dict_avail)
  {
    n = MZ_MIN(pState->m_dict_avail, p_ಹರಿವು->avail_ಹೊರಹೋಗು);
    ಸ್ಮರಣೆ_ನಕಲು(p_ಹರಿವು->ಮುಂದಿನ_ಹೊರಹೋಗು, pState->m_dict + pState->m_dict_ofs, n);
    p_ಹರಿವು->ಮುಂದಿನ_ಹೊರಹೋಗು += n; p_ಹರಿವು->avail_ಹೊರಹೋಗು -= n; p_ಹರಿವು->ಒಟ್ಟು_ಹೊರಹೋಗು += n;
    pState->m_dict_avail -= n; pState->m_dict_ofs = (pState->m_dict_ofs + n) & (TINFL_LZ_DICT_ಗಾತ್ರ - 1);
    ಹಿಂತಿರುಗಿ ((pState->m_ಕೊನೆಯ_ಸ್ಥಿತಿ == TINFL_ಸ್ಥಿತಿ_ಮುಗಿದ) && (!pState->m_dict_avail)) ? MZ_ಹರಿವು_ಕೊನೆ : MZ_OK;
  }

  ಗಾಗಿ ( ; ; )
  {
    ಒಳ_ಬೈಟುಗಳು = p_ಹರಿವು->avail_ಒಳ;
    ಹೊರಹೋಗು_ಬೈಟುಗಳು = TINFL_LZ_DICT_ಗಾತ್ರ - pState->m_dict_ofs;

    ಸ್ಥಿತಿ_2 = tinfl_decompress(&pState->m_decomp, p_ಹರಿವು->ಮುಂದಿನ_ಒಳ, &ಒಳ_ಬೈಟುಗಳು, pState->m_dict, pState->m_dict + pState->m_dict_ofs, &ಹೊರಹೋಗು_ಬೈಟುಗಳು, decomp_flags);
    pState->m_ಕೊನೆಯ_ಸ್ಥಿತಿ = ಸ್ಥಿತಿ_2;

    p_ಹರಿವು->ಮುಂದಿನ_ಒಳ += (mz_uint)ಒಳ_ಬೈಟುಗಳು; p_ಹರಿವು->avail_ಒಳ -= (mz_uint)ಒಳ_ಬೈಟುಗಳು;
    p_ಹರಿವು->ಒಟ್ಟು_ಒಳ += (mz_uint)ಒಳ_ಬೈಟುಗಳು; p_ಹರಿವು->adler = tinfl_get_adler32(&pState->m_decomp);

    pState->m_dict_avail = (mz_uint)ಹೊರಹೋಗು_ಬೈಟುಗಳು;

    n = MZ_MIN(pState->m_dict_avail, p_ಹರಿವು->avail_ಹೊರಹೋಗು);
    ಸ್ಮರಣೆ_ನಕಲು(p_ಹರಿವು->ಮುಂದಿನ_ಹೊರಹೋಗು, pState->m_dict + pState->m_dict_ofs, n);
    p_ಹರಿವು->ಮುಂದಿನ_ಹೊರಹೋಗು += n; p_ಹರಿವು->avail_ಹೊರಹೋಗು -= n; p_ಹರಿವು->ಒಟ್ಟು_ಹೊರಹೋಗು += n;
    pState->m_dict_avail -= n; pState->m_dict_ofs = (pState->m_dict_ofs + n) & (TINFL_LZ_DICT_ಗಾತ್ರ - 1);

    ಆದರೆ (ಸ್ಥಿತಿ_2 < 0)
       ಹಿಂತಿರುಗಿ MZ_ದತ್ತಾಂಶ_ERROR; // Stream is corrupted (there could be some uncompressed data left in the output dictionary - oh well).
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((ಸ್ಥಿತಿ_2 == TINFL_ಸ್ಥಿತಿ_NEEDS_ಇನ್ನಷ್ಟು_ಒಳಹರಿವು) && (!orig_avail_ಒಳ))
      ಹಿಂತಿರುಗಿ MZ_BUF_ERROR; // Signal caller that we can't make forward progress without supplying more input or by setting flush to MZ_FINISH.
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (flush == MZ_ಮುಕ್ತಾಯ)
    {
       // The output buffer MUST be large to hold the remaining uncompressed data when flush==MZ_FINISH.
       ಆದರೆ (ಸ್ಥಿತಿ_2 == TINFL_ಸ್ಥಿತಿ_ಮುಗಿದ)
          ಹಿಂತಿರುಗಿ pState->m_dict_avail ? MZ_BUF_ERROR : MZ_ಹರಿವು_ಕೊನೆ;
       // status here must be TINFL_STATUS_HAS_MORE_OUTPUT, which means there's at least 1 more byte on the way. If there's no more room left in the output buffer then something is wrong.
       ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!p_ಹರಿವು->avail_ಹೊರಹೋಗು)
          ಹಿಂತಿರುಗಿ MZ_BUF_ERROR;
    }
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((ಸ್ಥಿತಿ_2 == TINFL_ಸ್ಥಿತಿ_ಮುಗಿದ) || (!p_ಹರಿವು->avail_ಒಳ) || (!p_ಹರಿವು->avail_ಹೊರಹೋಗು) || (pState->m_dict_avail))
      ನಿಲ್ಲಿಸು;
  }

  ಹಿಂತಿರುಗಿ ((ಸ್ಥಿತಿ_2 == TINFL_ಸ್ಥಿತಿ_ಮುಗಿದ) && (!pState->m_dict_avail)) ? MZ_ಹರಿವು_ಕೊನೆ : MZ_OK;
}

ಪೂರ್ಣಾಂಕ mz_inflate_ಕೊನೆ(mz_streamp p_ಹರಿವು)
{
  ಆದರೆ (!p_ಹರಿವು)
    ಹಿಂತಿರುಗಿ MZ_ಹರಿವು_ERROR;
  ಆದರೆ (p_ಹರಿವು->state)
  {
    p_ಹರಿವು->zfree(p_ಹರಿವು->opaque, p_ಹರಿವು->state);
    p_ಹರಿವು->state = ಖಾಲಿ;
  }
  ಹಿಂತಿರುಗಿ MZ_OK;
}

ಪೂರ್ಣಾಂಕ mz_uncompress(ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *pDest, mz_ulong *pDest_len, ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *p_ಮೂಲ, mz_ulong ಮೂಲ_len)
{
  mz_ಹರಿವು ಹರಿವು;
  ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_2;
  memset(&ಹರಿವು, 0, ಗಾತ್ರ(ಹರಿವು));

  // In case mz_ulong is 64-bits (argh I hate longs).
  ಆದರೆ ((ಮೂಲ_len | *pDest_len) > 0xFFFFFFFFU) ಹಿಂತಿರುಗಿ MZ_PARAM_ERROR;

  ಹರಿವು.ಮುಂದಿನ_ಒಳ = p_ಮೂಲ;
  ಹರಿವು.avail_ಒಳ = (mz_uint32)ಮೂಲ_len;
  ಹರಿವು.ಮುಂದಿನ_ಹೊರಹೋಗು = pDest;
  ಹರಿವು.avail_ಹೊರಹೋಗು = (mz_uint32)*pDest_len;

  ಸ್ಥಿತಿ_2 = mz_inflateInit(&ಹರಿವು);
  ಆದರೆ (ಸ್ಥಿತಿ_2 != MZ_OK)
    ಹಿಂತಿರುಗಿ ಸ್ಥಿತಿ_2;

  ಸ್ಥಿತಿ_2 = mz_inflate(&ಹರಿವು, MZ_ಮುಕ್ತಾಯ);
  ಆದರೆ (ಸ್ಥಿತಿ_2 != MZ_ಹರಿವು_ಕೊನೆ)
  {
    mz_inflate_ಕೊನೆ(&ಹರಿವು);
    ಹಿಂತಿರುಗಿ ((ಸ್ಥಿತಿ_2 == MZ_BUF_ERROR) && (!ಹರಿವು.avail_ಒಳ)) ? MZ_ದತ್ತಾಂಶ_ERROR : ಸ್ಥಿತಿ_2;
  }
  *pDest_len = ಹರಿವು.ಒಟ್ಟು_ಹೊರಹೋಗು;

  ಹಿಂತಿರುಗಿ mz_inflate_ಕೊನೆ(&ಹರಿವು);
}

#ಆದರೆ_ಅಂತ್ಯ /*#ifndef MINIZ_NO_INFLATE_APIS*/

ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *mz_error(ಪೂರ್ಣಾಂಕ err)
{
  ಸ್ಥಿರ ರಚನೆ { ಪೂರ್ಣಾಂಕ m_err; ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *m_pDesc; } s_error_descs[] =
  {
    { MZ_OK, "" }, { MZ_ಹರಿವು_ಕೊನೆ, "stream end" }, { MZ_NEED_DICT, "need dictionary" }, { MZ_ERRNO, "file error" }, { MZ_ಹರಿವು_ERROR, "stream error" },
    { MZ_ದತ್ತಾಂಶ_ERROR, "data error" }, { MZ_MEM_ERROR, "out of memory" }, { MZ_BUF_ERROR, "buf error" }, { MZ_ಆವೃತ್ತಿ_ERROR, "version error" }, { MZ_PARAM_ERROR, "parameter error" }
  };
  mz_uint i; ಗಾಗಿ (i = 0; i < ಗಾತ್ರ(s_error_descs) / ಗಾತ್ರ(s_error_descs[0]); ++i) ಆದರೆ (s_error_descs[i].m_err == err) ಹಿಂತಿರುಗಿ s_error_descs[i].m_pDesc;
  ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

#ಆದರೆ_ಅಂತ್ಯ //MINIZ_NO_ZLIB_APIS

// ------------------- Low-level Decompression (completely independent from all compression API's)
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_INFLATE_APIS

#ವ್ಯಾಖ್ಯಾನಿಸು TINFL_MEMCPY(d, s, l) ಸ್ಮರಣೆ_ನಕಲು(d, s, l)
#ವ್ಯಾಖ್ಯಾನಿಸು TINFL_MEMSET(p, c, l) memset(p, c, l)

#ವ್ಯಾಖ್ಯಾನಿಸು TINFL_CR_BEGIN ಆಯ್ಕೆ(r->m_state) { ಸ್ಥಿತಿ 0:
#ವ್ಯಾಖ್ಯಾನಿಸು TINFL_CR_RETURN(state_ಸೂಚ್ಯಂಕ, ಫಲಿತಾಂಶ) ಮಾಡು { ಸ್ಥಿತಿ_2 = ಫಲಿತಾಂಶ; r->m_state = state_ಸೂಚ್ಯಂಕ; ಹೋಗು common_exit; ಸ್ಥಿತಿ state_ಸೂಚ್ಯಂಕ:; } MZ_MACRO_ಕೊನೆ
#ವ್ಯಾಖ್ಯಾನಿಸು TINFL_CR_RETURN_FOREVER(state_ಸೂಚ್ಯಂಕ, ಫಲಿತಾಂಶ) ಮಾಡು { ಗಾಗಿ ( ; ; ) { TINFL_CR_RETURN(state_ಸೂಚ್ಯಂಕ, ಫಲಿತಾಂಶ); } } MZ_MACRO_ಕೊನೆ
#ವ್ಯಾಖ್ಯಾನಿಸು TINFL_CR_ಮುಕ್ತಾಯ }

// TODO: If the caller has indicated that there's no more input, and we attempt to read beyond the input buf, then something is wrong with the input because the inflator never
// reads ahead more than it needs to. Currently TINFL_GET_BYTE() pads the end of the stream with 0's in this scenario.
#ವ್ಯಾಖ್ಯಾನಿಸು TINFL_GET_BYTE(state_ಸೂಚ್ಯಂಕ, c) ಮಾಡು { \
  ಆದರೆ (p_ಒಳ_buf_cur >= p_ಒಳ_buf_ಕೊನೆ) { \
    ಗಾಗಿ ( ; ; ) { \
      ಆದರೆ (decomp_flags & TINFL_FLAG_HAS_ಇನ್ನಷ್ಟು_ಒಳಹರಿವು) { \
        TINFL_CR_RETURN(state_ಸೂಚ್ಯಂಕ, TINFL_ಸ್ಥಿತಿ_NEEDS_ಇನ್ನಷ್ಟು_ಒಳಹರಿವು); \
        ಆದರೆ (p_ಒಳ_buf_cur < p_ಒಳ_buf_ಕೊನೆ) { \
          c = *p_ಒಳ_buf_cur++; \
          ನಿಲ್ಲಿಸು; \
        } \
      } ಇಲ್ಲದಿದ್ದರೆ { \
        c = 0; \
        ನಿಲ್ಲಿಸು; \
      } \
    } \
  } ಇಲ್ಲದಿದ್ದರೆ c = *p_ಒಳ_buf_cur++; } MZ_MACRO_ಕೊನೆ

#ವ್ಯಾಖ್ಯಾನಿಸು TINFL_NEED_ಬಿಟ್ಟುಗಳು(state_ಸೂಚ್ಯಂಕ, n) ಮಾಡು { mz_uint c; TINFL_GET_BYTE(state_ಸೂಚ್ಯಂಕ, c); ಬಿಟ್_buf |= (((tinfl_ಬಿಟ್_buf_t)c) << ಅಂಕೆ_ಬಿಟ್ಟುಗಳು); ಅಂಕೆ_ಬಿಟ್ಟುಗಳು += 8; } ಆಗ (ಅಂಕೆ_ಬಿಟ್ಟುಗಳು < (mz_uint)(n))
#ವ್ಯಾಖ್ಯಾನಿಸು TINFL_SKIP_ಬಿಟ್ಟುಗಳು(state_ಸೂಚ್ಯಂಕ, n) ಮಾಡು { ಆದರೆ (ಅಂಕೆ_ಬಿಟ್ಟುಗಳು < (mz_uint)(n)) { TINFL_NEED_ಬಿಟ್ಟುಗಳು(state_ಸೂಚ್ಯಂಕ, n); } ಬಿಟ್_buf >>= (n); ಅಂಕೆ_ಬಿಟ್ಟುಗಳು -= (n); } MZ_MACRO_ಕೊನೆ
#ವ್ಯಾಖ್ಯಾನಿಸು TINFL_GET_ಬಿಟ್ಟುಗಳು(state_ಸೂಚ್ಯಂಕ, b, n) ಮಾಡು { ಆದರೆ (ಅಂಕೆ_ಬಿಟ್ಟುಗಳು < (mz_uint)(n)) { TINFL_NEED_ಬಿಟ್ಟುಗಳು(state_ಸೂಚ್ಯಂಕ, n); } b = ಬಿಟ್_buf & ((1 << (n)) - 1); ಬಿಟ್_buf >>= (n); ಅಂಕೆ_ಬಿಟ್ಟುಗಳು -= (n); } MZ_MACRO_ಕೊನೆ

// TINFL_HUFF_BITBUF_FILL() is only used rarely, when the number of bytes remaining in the input buffer falls below 2.
// It reads just enough bytes from the input stream that are needed to decode the next Huffman code (and absolutely no more). It works by trying to fully decode a
// Huffman code by using whatever bits are currently present in the bit buffer. If this fails, it reads another byte, and tries again until it succeeds or until the
// bit buffer contains >=15 bits (deflate's max. Huffman code size).
#ವ್ಯಾಖ್ಯಾನಿಸು TINFL_HUFF_BITBUF_FILL(state_ಸೂಚ್ಯಂಕ, pHuff) \
  ಮಾಡು { \
    ತಾತ್ಕಾಲಿಕ = (pHuff)->m_look_ಮೇಲೆ[ಬಿಟ್_buf & (TINFL_FAST_LOOKUP_ಗಾತ್ರ - 1)]; \
    ಆದರೆ (ತಾತ್ಕಾಲಿಕ >= 0) { \
      ಸಂಕೇತ_len = ತಾತ್ಕಾಲಿಕ >> 9; \
      ಆದರೆ ((ಸಂಕೇತ_len) && (ಅಂಕೆ_ಬಿಟ್ಟುಗಳು >= ಸಂಕೇತ_len)) \
          ನಿಲ್ಲಿಸು; \
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಅಂಕೆ_ಬಿಟ್ಟುಗಳು > TINFL_FAST_LOOKUP_ಬಿಟ್ಟುಗಳು) { \
       ಸಂಕೇತ_len = TINFL_FAST_LOOKUP_ಬಿಟ್ಟುಗಳು; \
       ಮಾಡು { \
          ತಾತ್ಕಾಲಿಕ = (pHuff)->m_ವೃಕ್ಷ[~ತಾತ್ಕಾಲಿಕ + ((ಬಿಟ್_buf >> ಸಂಕೇತ_len++) & 1)]; \
       } ಆಗ ((ತಾತ್ಕಾಲಿಕ < 0) && (ಅಂಕೆ_ಬಿಟ್ಟುಗಳು >= (ಸಂಕೇತ_len + 1))); \
       ಆದರೆ (ತಾತ್ಕಾಲಿಕ >= 0) ನಿಲ್ಲಿಸು; \
    } \
    TINFL_GET_BYTE(state_ಸೂಚ್ಯಂಕ, c); \
    ಬಿಟ್_buf |= (((tinfl_ಬಿಟ್_buf_t)c) << ಅಂಕೆ_ಬಿಟ್ಟುಗಳು); \
    ಅಂಕೆ_ಬಿಟ್ಟುಗಳು += 8; \
  } ಆಗ (ಅಂಕೆ_ಬಿಟ್ಟುಗಳು < 15);

// TINFL_HUFF_DECODE() decodes the next Huffman coded symbol. It's more complex than you would initially expect because the zlib API expects the decompressor to never read
// beyond the final byte of the deflate stream. (In other words, when this macro wants to read another byte from the input, it REALLY needs another byte in order to fully
// decode the next Huffman code.) Handling this properly is particularly important on raw deflate (non-zlib) streams, which aren't followed by a byte aligned adler-32.
// The slow path is only executed at the very end of the input buffer.
#ವ್ಯಾಖ್ಯಾನಿಸು TINFL_HUFF_DECODE(state_ಸೂಚ್ಯಂಕ, sym, pHuff) ಮಾಡು { \
  ಪೂರ್ಣಾಂಕ ತಾತ್ಕಾಲಿಕ; mz_uint ಸಂಕೇತ_len, c; \
  ಆದರೆ (ಅಂಕೆ_ಬಿಟ್ಟುಗಳು < 15) { \
    ಆದರೆ ((p_ಒಳ_buf_ಕೊನೆ - p_ಒಳ_buf_cur) < 2) { \
       TINFL_HUFF_BITBUF_FILL(state_ಸೂಚ್ಯಂಕ, pHuff); \
    } ಇಲ್ಲದಿದ್ದರೆ { \
       ಬಿಟ್_buf |= (((tinfl_ಬಿಟ್_buf_t)p_ಒಳ_buf_cur[0]) << ಅಂಕೆ_ಬಿಟ್ಟುಗಳು) | (((tinfl_ಬಿಟ್_buf_t)p_ಒಳ_buf_cur[1]) << (ಅಂಕೆ_ಬಿಟ್ಟುಗಳು + 8)); p_ಒಳ_buf_cur += 2; ಅಂಕೆ_ಬಿಟ್ಟುಗಳು += 16; \
    } \
  } \
  ಆದರೆ ((ತಾತ್ಕಾಲಿಕ = (pHuff)->m_look_ಮೇಲೆ[ಬಿಟ್_buf & (TINFL_FAST_LOOKUP_ಗಾತ್ರ - 1)]) >= 0) \
    ಸಂಕೇತ_len = ತಾತ್ಕಾಲಿಕ >> 9, ತಾತ್ಕಾಲಿಕ &= 511; \
  ಇಲ್ಲದಿದ್ದರೆ { \
    ಸಂಕೇತ_len = TINFL_FAST_LOOKUP_ಬಿಟ್ಟುಗಳು; ಮಾಡು { ತಾತ್ಕಾಲಿಕ = (pHuff)->m_ವೃಕ್ಷ[~ತಾತ್ಕಾಲಿಕ + ((ಬಿಟ್_buf >> ಸಂಕೇತ_len++) & 1)]; } ಆಗ (ತಾತ್ಕಾಲಿಕ < 0); \
  } sym = ತಾತ್ಕಾಲಿಕ; ಬಿಟ್_buf >>= ಸಂಕೇತ_len; ಅಂಕೆ_ಬಿಟ್ಟುಗಳು -= ಸಂಕೇತ_len; } MZ_MACRO_ಕೊನೆ

tinfl_ಸ್ಥಿತಿ tinfl_decompress(tinfl_decompressor *r, ಸ್ಥಿರಾಂಕ mz_uint8 *p_ಒಳ_buf_ಮುಂದಿನ, size_t *p_ಒಳ_buf_ಗಾತ್ರ, mz_uint8 *p_ಹೊರಹೋಗು_buf_ಆರಂಭ, mz_uint8 *p_ಹೊರಹೋಗು_buf_ಮುಂದಿನ, size_t *p_ಹೊರಹೋಗು_buf_ಗಾತ್ರ, ಸ್ಥಿರಾಂಕ mz_uint32 decomp_flags)
{
  ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ s_ಉದ್ದಳತೆ_ತಳ[31] = { 3,4,5,6,7,8,9,10,11,13, 15,17,19,23,27,31,35,43,51,59, 67,83,99,115,131,163,195,227,258,0,0 };
  ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ s_ಉದ್ದಳತೆ_extra[31]= { 0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,0,0,0 };
  ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ s_dist_ತಳ[32] = { 1,2,3,4,5,7,9,13,17,25,33,49,65,97,129,193, 257,385,513,769,1025,1537,2049,3073,4097,6145,8193,12289,16385,24577,0,0};
  ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ s_dist_extra[32] = { 0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13};
  ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ mz_uint8 s_ಉದ್ದಳತೆ_dezigzag[19] = { 16,17,18,0,8,7,9,6,10,5,11,4,12,3,13,2,14,1,15 };
  ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ s_min_ಕೋಷ್ಟಕ_sizes[3] = { 257, 1, 4 };

  tinfl_ಸ್ಥಿತಿ ಸ್ಥಿತಿ_2 = TINFL_ಸ್ಥಿತಿ_FAILED; mz_uint32 ಅಂಕೆ_ಬಿಟ್ಟುಗಳು, dist, counter, ಅಂಕೆ_extra; tinfl_ಬಿಟ್_buf_t ಬಿಟ್_buf;
  ಸ್ಥಿರಾಂಕ mz_uint8 *p_ಒಳ_buf_cur = p_ಒಳ_buf_ಮುಂದಿನ, *ಸ್ಥಿರಾಂಕ p_ಒಳ_buf_ಕೊನೆ = p_ಒಳ_buf_ಮುಂದಿನ + *p_ಒಳ_buf_ಗಾತ್ರ;
  mz_uint8 *p_ಹೊರಹೋಗು_buf_cur = p_ಹೊರಹೋಗು_buf_ಮುಂದಿನ, *ಸ್ಥಿರಾಂಕ p_ಹೊರಹೋಗು_buf_ಕೊನೆ = p_ಹೊರಹೋಗು_buf_ಮುಂದಿನ + *p_ಹೊರಹೋಗು_buf_ಗಾತ್ರ;
  size_t ಹೊರಹೋಗು_buf_ಗಾತ್ರ_ಮುಖವಾಡ = (decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF) ? (size_t)-1 : ((p_ಹೊರಹೋಗು_buf_ಮುಂದಿನ - p_ಹೊರಹೋಗು_buf_ಆರಂಭ) + *p_ಹೊರಹೋಗು_buf_ಗಾತ್ರ) - 1, dist_from_ಹೊರಹೋಗು_buf_ಆರಂಭ;

  // Ensure the output buffer's size is a power of 2, unless the output buffer is large enough to hold the entire output file (in which case it doesn't matter).
  ಆದರೆ (((ಹೊರಹೋಗು_buf_ಗಾತ್ರ_ಮುಖವಾಡ + 1) & ಹೊರಹೋಗು_buf_ಗಾತ್ರ_ಮುಖವಾಡ) || (p_ಹೊರಹೋಗು_buf_ಮುಂದಿನ < p_ಹೊರಹೋಗು_buf_ಆರಂಭ)) { *p_ಒಳ_buf_ಗಾತ್ರ = *p_ಹೊರಹೋಗು_buf_ಗಾತ್ರ = 0; ಹಿಂತಿರುಗಿ TINFL_ಸ್ಥಿತಿ_BAD_PARAM; }

  ಅಂಕೆ_ಬಿಟ್ಟುಗಳು = r->m_ಅಂಕೆ_ಬಿಟ್ಟುಗಳು; ಬಿಟ್_buf = r->m_ಬಿಟ್_buf; dist = r->m_dist; counter = r->m_counter; ಅಂಕೆ_extra = r->m_ಅಂಕೆ_extra; dist_from_ಹೊರಹೋಗು_buf_ಆರಂಭ = r->m_dist_from_ಹೊರಹೋಗು_buf_ಆರಂಭ;
  TINFL_CR_BEGIN

  ಬಿಟ್_buf = ಅಂಕೆ_ಬಿಟ್ಟುಗಳು = dist = counter = ಅಂಕೆ_extra = r->m_zhdr0 = r->m_zhdr1 = 0; r->m_z_adler32 = r->m_check_adler32 = 1;
  ಆದರೆ (decomp_flags & TINFL_FLAG_PARSE_ZLIB_ಶೀರ್ಷಿಕೆ)
  {
    TINFL_GET_BYTE(1, r->m_zhdr0); TINFL_GET_BYTE(2, r->m_zhdr1);
    counter = (((r->m_zhdr0 * 256 + r->m_zhdr1) % 31 != 0) || (r->m_zhdr1 & 32) || ((r->m_zhdr0 & 15) != 8));
    ಆದರೆ (!(decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF)) counter |= (((1U << (8U + (r->m_zhdr0 >> 4))) > 32768U) || ((ಹೊರಹೋಗು_buf_ಗಾತ್ರ_ಮುಖವಾಡ + 1) < (size_t)(1U << (8U + (r->m_zhdr0 >> 4)))));
    ಆದರೆ (counter) { TINFL_CR_RETURN_FOREVER(36, TINFL_ಸ್ಥಿತಿ_FAILED); }
  }

  ಮಾಡು
  {
    TINFL_GET_ಬಿಟ್ಟುಗಳು(3, r->m_final, 3); r->m_type = r->m_final >> 1;
    ಆದರೆ (r->m_type == 0)
    {
      TINFL_SKIP_ಬಿಟ್ಟುಗಳು(5, ಅಂಕೆ_ಬಿಟ್ಟುಗಳು & 7);
      ಗಾಗಿ (counter = 0; counter < 4; ++counter) { ಆದರೆ (ಅಂಕೆ_ಬಿಟ್ಟುಗಳು) TINFL_GET_ಬಿಟ್ಟುಗಳು(6, r->m_raw_ಶೀರ್ಷಿಕೆ[counter], 8); ಇಲ್ಲದಿದ್ದರೆ TINFL_GET_BYTE(7, r->m_raw_ಶೀರ್ಷಿಕೆ[counter]); }
      ಆದರೆ ((counter = (r->m_raw_ಶೀರ್ಷಿಕೆ[0] | (r->m_raw_ಶೀರ್ಷಿಕೆ[1] << 8))) != (mz_uint)(0xFFFF ^ (r->m_raw_ಶೀರ್ಷಿಕೆ[2] | (r->m_raw_ಶೀರ್ಷಿಕೆ[3] << 8)))) { TINFL_CR_RETURN_FOREVER(39, TINFL_ಸ್ಥಿತಿ_FAILED); }
      ಆಗ ((counter) && (ಅಂಕೆ_ಬಿಟ್ಟುಗಳು))
      {
        TINFL_GET_ಬಿಟ್ಟುಗಳು(51, dist, 8);
        ಆಗ (p_ಹೊರಹೋಗು_buf_cur >= p_ಹೊರಹೋಗು_buf_ಕೊನೆ) { TINFL_CR_RETURN(52, TINFL_ಸ್ಥಿತಿ_HAS_ಇನ್ನಷ್ಟು_OUTPUT); }
        *p_ಹೊರಹೋಗು_buf_cur++ = (mz_uint8)dist;
        counter--;
      }
      ಆಗ (counter)
      {
        size_t n; ಆಗ (p_ಹೊರಹೋಗು_buf_cur >= p_ಹೊರಹೋಗು_buf_ಕೊನೆ) { TINFL_CR_RETURN(9, TINFL_ಸ್ಥಿತಿ_HAS_ಇನ್ನಷ್ಟು_OUTPUT); }
        ಆಗ (p_ಒಳ_buf_cur >= p_ಒಳ_buf_ಕೊನೆ)
        {
          ಆದರೆ (decomp_flags & TINFL_FLAG_HAS_ಇನ್ನಷ್ಟು_ಒಳಹರಿವು)
          {
            TINFL_CR_RETURN(38, TINFL_ಸ್ಥಿತಿ_NEEDS_ಇನ್ನಷ್ಟು_ಒಳಹರಿವು);
          }
          ಇಲ್ಲದಿದ್ದರೆ
          {
            TINFL_CR_RETURN_FOREVER(40, TINFL_ಸ್ಥಿತಿ_FAILED);
          }
        }
        n = MZ_MIN(MZ_MIN((size_t)(p_ಹೊರಹೋಗು_buf_ಕೊನೆ - p_ಹೊರಹೋಗು_buf_cur), (size_t)(p_ಒಳ_buf_ಕೊನೆ - p_ಒಳ_buf_cur)), counter);
        TINFL_MEMCPY(p_ಹೊರಹೋಗು_buf_cur, p_ಒಳ_buf_cur, n); p_ಒಳ_buf_cur += n; p_ಹೊರಹೋಗು_buf_cur += n; counter -= (mz_uint)n;
      }
    }
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (r->m_type == 3)
    {
      TINFL_CR_RETURN_FOREVER(10, TINFL_ಸ್ಥಿತಿ_FAILED);
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
      ಆದರೆ (r->m_type == 1)
      {
        mz_uint8 *p = r->m_tables[0].m_ಸಂಕೇತ_ಗಾತ್ರ; mz_uint i;
        r->m_ಕೋಷ್ಟಕ_sizes[0] = 288; r->m_ಕೋಷ್ಟಕ_sizes[1] = 32; TINFL_MEMSET(r->m_tables[1].m_ಸಂಕೇತ_ಗಾತ್ರ, 5, 32);
        ಗಾಗಿ ( i = 0; i <= 143; ++i) *p++ = 8;
        ಗಾಗಿ ( ; i <= 255; ++i) *p++ = 9;
        ಗಾಗಿ ( ; i <= 279; ++i) *p++ = 7;
        ಗಾಗಿ ( ; i <= 287; ++i) *p++ = 8;
      }
      ಇಲ್ಲದಿದ್ದರೆ
      {
        ಗಾಗಿ (counter = 0; counter < 3; counter++) { TINFL_GET_ಬಿಟ್ಟುಗಳು(11, r->m_ಕೋಷ್ಟಕ_sizes[counter], "\05\05\04"[counter]); r->m_ಕೋಷ್ಟಕ_sizes[counter] += s_min_ಕೋಷ್ಟಕ_sizes[counter]; }
        MZ_CLEAR_ARR(r->m_tables[2].m_ಸಂಕೇತ_ಗಾತ್ರ); ಗಾಗಿ (counter = 0; counter < r->m_ಕೋಷ್ಟಕ_sizes[2]; counter++) { mz_uint s; TINFL_GET_ಬಿಟ್ಟುಗಳು(14, s, 3); r->m_tables[2].m_ಸಂಕೇತ_ಗಾತ್ರ[s_ಉದ್ದಳತೆ_dezigzag[counter]] = (mz_uint8)s; }
        r->m_ಕೋಷ್ಟಕ_sizes[2] = 19;
      }
      ಗಾಗಿ ( ; (ಪೂರ್ಣಾಂಕ)r->m_type >= 0; r->m_type--)
      {
        ಪೂರ್ಣಾಂಕ ವೃಕ್ಷ_ಮುಂದಿನ, ವೃಕ್ಷ_cur; tinfl_huff_ಕೋಷ್ಟಕ *p_ಕೋಷ್ಟಕ;
        mz_uint i, j, ಬಳಸಿದ_syms, ಒಟ್ಟು, sym_ಸೂಚ್ಯಂಕ, ಮುಂದಿನ_ಸಂಕೇತ[17], ಒಟ್ಟು_syms[16]; p_ಕೋಷ್ಟಕ = &r->m_tables[r->m_type]; MZ_CLEAR_ARR(ಒಟ್ಟು_syms); MZ_CLEAR_ARR(p_ಕೋಷ್ಟಕ->m_look_ಮೇಲೆ); MZ_CLEAR_ARR(p_ಕೋಷ್ಟಕ->m_ವೃಕ್ಷ);
        ಗಾಗಿ (i = 0; i < r->m_ಕೋಷ್ಟಕ_sizes[r->m_type]; ++i) ಒಟ್ಟು_syms[p_ಕೋಷ್ಟಕ->m_ಸಂಕೇತ_ಗಾತ್ರ[i]]++;
        ಬಳಸಿದ_syms = 0, ಒಟ್ಟು = 0; ಮುಂದಿನ_ಸಂಕೇತ[0] = ಮುಂದಿನ_ಸಂಕೇತ[1] = 0;
        ಗಾಗಿ (i = 1; i <= 15; ++i) { ಬಳಸಿದ_syms += ಒಟ್ಟು_syms[i]; ಮುಂದಿನ_ಸಂಕೇತ[i + 1] = (ಒಟ್ಟು = ((ಒಟ್ಟು + ಒಟ್ಟು_syms[i]) << 1)); }
        ಆದರೆ ((65536 != ಒಟ್ಟು) && (ಬಳಸಿದ_syms > 1))
        {
          TINFL_CR_RETURN_FOREVER(35, TINFL_ಸ್ಥಿತಿ_FAILED);
        }
        ಗಾಗಿ (ವೃಕ್ಷ_ಮುಂದಿನ = -1, sym_ಸೂಚ್ಯಂಕ = 0; sym_ಸೂಚ್ಯಂಕ < r->m_ಕೋಷ್ಟಕ_sizes[r->m_type]; ++sym_ಸೂಚ್ಯಂಕ)
        {
          mz_uint rev_ಸಂಕೇತ = 0, l, cur_ಸಂಕೇತ, ಸಂಕೇತ_ಗಾತ್ರ_2 = p_ಕೋಷ್ಟಕ->m_ಸಂಕೇತ_ಗಾತ್ರ[sym_ಸೂಚ್ಯಂಕ]; ಆದರೆ (!ಸಂಕೇತ_ಗಾತ್ರ_2) ಮುಂದುವರಿ;
          cur_ಸಂಕೇತ = ಮುಂದಿನ_ಸಂಕೇತ[ಸಂಕೇತ_ಗಾತ್ರ_2]++; ಗಾಗಿ (l = ಸಂಕೇತ_ಗಾತ್ರ_2; l > 0; l--, cur_ಸಂಕೇತ >>= 1) rev_ಸಂಕೇತ = (rev_ಸಂಕೇತ << 1) | (cur_ಸಂಕೇತ & 1);
          ಆದರೆ (ಸಂಕೇತ_ಗಾತ್ರ_2 <= TINFL_FAST_LOOKUP_ಬಿಟ್ಟುಗಳು) { mz_int16 k = (mz_int16)((ಸಂಕೇತ_ಗಾತ್ರ_2 << 9) | sym_ಸೂಚ್ಯಂಕ); ಆಗ (rev_ಸಂಕೇತ < TINFL_FAST_LOOKUP_ಗಾತ್ರ) { p_ಕೋಷ್ಟಕ->m_look_ಮೇಲೆ[rev_ಸಂಕೇತ] = k; rev_ಸಂಕೇತ += (1 << ಸಂಕೇತ_ಗಾತ್ರ_2); } ಮುಂದುವರಿ; }
          ಆದರೆ (0 == (ವೃಕ್ಷ_cur = p_ಕೋಷ್ಟಕ->m_look_ಮೇಲೆ[rev_ಸಂಕೇತ & (TINFL_FAST_LOOKUP_ಗಾತ್ರ - 1)])) { p_ಕೋಷ್ಟಕ->m_look_ಮೇಲೆ[rev_ಸಂಕೇತ & (TINFL_FAST_LOOKUP_ಗಾತ್ರ - 1)] = (mz_int16)ವೃಕ್ಷ_ಮುಂದಿನ; ವೃಕ್ಷ_cur = ವೃಕ್ಷ_ಮುಂದಿನ; ವೃಕ್ಷ_ಮುಂದಿನ -= 2; }
          rev_ಸಂಕೇತ >>= (TINFL_FAST_LOOKUP_ಬಿಟ್ಟುಗಳು - 1);
          ಗಾಗಿ (j = ಸಂಕೇತ_ಗಾತ್ರ_2; j > (TINFL_FAST_LOOKUP_ಬಿಟ್ಟುಗಳು + 1); j--)
          {
            ವೃಕ್ಷ_cur -= ((rev_ಸಂಕೇತ >>= 1) & 1);
            ಆದರೆ (!p_ಕೋಷ್ಟಕ->m_ವೃಕ್ಷ[-ವೃಕ್ಷ_cur - 1]) { p_ಕೋಷ್ಟಕ->m_ವೃಕ್ಷ[-ವೃಕ್ಷ_cur - 1] = (mz_int16)ವೃಕ್ಷ_ಮುಂದಿನ; ವೃಕ್ಷ_cur = ವೃಕ್ಷ_ಮುಂದಿನ; ವೃಕ್ಷ_ಮುಂದಿನ -= 2; } ಇಲ್ಲದಿದ್ದರೆ ವೃಕ್ಷ_cur = p_ಕೋಷ್ಟಕ->m_ವೃಕ್ಷ[-ವೃಕ್ಷ_cur - 1];
          }
          ವೃಕ್ಷ_cur -= ((rev_ಸಂಕೇತ >>= 1) & 1); p_ಕೋಷ್ಟಕ->m_ವೃಕ್ಷ[-ವೃಕ್ಷ_cur - 1] = (mz_int16)sym_ಸೂಚ್ಯಂಕ;
        }
        ಆದರೆ (r->m_type == 2)
        {
          ಗಾಗಿ (counter = 0; counter < (r->m_ಕೋಷ್ಟಕ_sizes[0] + r->m_ಕೋಷ್ಟಕ_sizes[1]); )
          {
            mz_uint s; TINFL_HUFF_DECODE(16, dist, &r->m_tables[2]); ಆದರೆ (dist < 16) { r->m_len_codes[counter++] = (mz_uint8)dist; ಮುಂದುವರಿ; }
            ಆದರೆ ((dist == 16) && (!counter))
            {
              TINFL_CR_RETURN_FOREVER(17, TINFL_ಸ್ಥಿತಿ_FAILED);
            }
            ಅಂಕೆ_extra = "\02\03\07"[dist - 16]; TINFL_GET_ಬಿಟ್ಟುಗಳು(18, s, ಅಂಕೆ_extra); s += "\03\03\013"[dist - 16];
            TINFL_MEMSET(r->m_len_codes + counter, (dist == 16) ? r->m_len_codes[counter - 1] : 0, s); counter += s;
          }
          ಆದರೆ ((r->m_ಕೋಷ್ಟಕ_sizes[0] + r->m_ಕೋಷ್ಟಕ_sizes[1]) != counter)
          {
            TINFL_CR_RETURN_FOREVER(21, TINFL_ಸ್ಥಿತಿ_FAILED);
          }
          TINFL_MEMCPY(r->m_tables[0].m_ಸಂಕೇತ_ಗಾತ್ರ, r->m_len_codes, r->m_ಕೋಷ್ಟಕ_sizes[0]); TINFL_MEMCPY(r->m_tables[1].m_ಸಂಕೇತ_ಗಾತ್ರ, r->m_len_codes + r->m_ಕೋಷ್ಟಕ_sizes[0], r->m_ಕೋಷ್ಟಕ_sizes[1]);
        }
      }
      ಗಾಗಿ ( ; ; )
      {
        mz_uint8 *pSrc;
        ಗಾಗಿ ( ; ; )
        {
          ಆದರೆ (((p_ಒಳ_buf_ಕೊನೆ - p_ಒಳ_buf_cur) < 4) || ((p_ಹೊರಹೋಗು_buf_ಕೊನೆ - p_ಹೊರಹೋಗು_buf_cur) < 2))
          {
            TINFL_HUFF_DECODE(23, counter, &r->m_tables[0]);
            ಆದರೆ (counter >= 256)
              ನಿಲ್ಲಿಸು;
            ಆಗ (p_ಹೊರಹೋಗು_buf_cur >= p_ಹೊರಹೋಗು_buf_ಕೊನೆ) { TINFL_CR_RETURN(24, TINFL_ಸ್ಥಿತಿ_HAS_ಇನ್ನಷ್ಟು_OUTPUT); }
            *p_ಹೊರಹೋಗು_buf_cur++ = (mz_uint8)counter;
          }
          ಇಲ್ಲದಿದ್ದರೆ
          {
            ಪೂರ್ಣಾಂಕ sym2; mz_uint ಸಂಕೇತ_len;
#ಆದರೆ TINFL_USE_64_ಬಿಟ್_BITBUF
            ಆದರೆ (ಅಂಕೆ_ಬಿಟ್ಟುಗಳು < 30) { ಬಿಟ್_buf |= (((tinfl_ಬಿಟ್_buf_t)MZ_READ_LE32(p_ಒಳ_buf_cur)) << ಅಂಕೆ_ಬಿಟ್ಟುಗಳು); p_ಒಳ_buf_cur += 4; ಅಂಕೆ_ಬಿಟ್ಟುಗಳು += 32; }
#ಇಲ್ಲದಿದ್ದರೆ
            ಆದರೆ (ಅಂಕೆ_ಬಿಟ್ಟುಗಳು < 15) { ಬಿಟ್_buf |= (((tinfl_ಬಿಟ್_buf_t)MZ_READ_LE16(p_ಒಳ_buf_cur)) << ಅಂಕೆ_ಬಿಟ್ಟುಗಳು); p_ಒಳ_buf_cur += 2; ಅಂಕೆ_ಬಿಟ್ಟುಗಳು += 16; }
#ಆದರೆ_ಅಂತ್ಯ
            ಆದರೆ ((sym2 = r->m_tables[0].m_look_ಮೇಲೆ[ಬಿಟ್_buf & (TINFL_FAST_LOOKUP_ಗಾತ್ರ - 1)]) >= 0)
              ಸಂಕೇತ_len = sym2 >> 9;
            ಇಲ್ಲದಿದ್ದರೆ
            {
              ಸಂಕೇತ_len = TINFL_FAST_LOOKUP_ಬಿಟ್ಟುಗಳು; ಮಾಡು { sym2 = r->m_tables[0].m_ವೃಕ್ಷ[~sym2 + ((ಬಿಟ್_buf >> ಸಂಕೇತ_len++) & 1)]; } ಆಗ (sym2 < 0);
            }
            counter = sym2; ಬಿಟ್_buf >>= ಸಂಕೇತ_len; ಅಂಕೆ_ಬಿಟ್ಟುಗಳು -= ಸಂಕೇತ_len;
            ಆದರೆ (counter & 256)
              ನಿಲ್ಲಿಸು;

#ಆದರೆ !TINFL_USE_64_ಬಿಟ್_BITBUF
            ಆದರೆ (ಅಂಕೆ_ಬಿಟ್ಟುಗಳು < 15) { ಬಿಟ್_buf |= (((tinfl_ಬಿಟ್_buf_t)MZ_READ_LE16(p_ಒಳ_buf_cur)) << ಅಂಕೆ_ಬಿಟ್ಟುಗಳು); p_ಒಳ_buf_cur += 2; ಅಂಕೆ_ಬಿಟ್ಟುಗಳು += 16; }
#ಆದರೆ_ಅಂತ್ಯ
            ಆದರೆ ((sym2 = r->m_tables[0].m_look_ಮೇಲೆ[ಬಿಟ್_buf & (TINFL_FAST_LOOKUP_ಗಾತ್ರ - 1)]) >= 0)
              ಸಂಕೇತ_len = sym2 >> 9;
            ಇಲ್ಲದಿದ್ದರೆ
            {
              ಸಂಕೇತ_len = TINFL_FAST_LOOKUP_ಬಿಟ್ಟುಗಳು; ಮಾಡು { sym2 = r->m_tables[0].m_ವೃಕ್ಷ[~sym2 + ((ಬಿಟ್_buf >> ಸಂಕೇತ_len++) & 1)]; } ಆಗ (sym2 < 0);
            }
            ಬಿಟ್_buf >>= ಸಂಕೇತ_len; ಅಂಕೆ_ಬಿಟ್ಟುಗಳು -= ಸಂಕೇತ_len;

            p_ಹೊರಹೋಗು_buf_cur[0] = (mz_uint8)counter;
            ಆದರೆ (sym2 & 256)
            {
              p_ಹೊರಹೋಗು_buf_cur++;
              counter = sym2;
              ನಿಲ್ಲಿಸು;
            }
            p_ಹೊರಹೋಗು_buf_cur[1] = (mz_uint8)sym2;
            p_ಹೊರಹೋಗು_buf_cur += 2;
          }
        }
        ಆದರೆ ((counter &= 511) == 256) ನಿಲ್ಲಿಸು;

        ಅಂಕೆ_extra = s_ಉದ್ದಳತೆ_extra[counter - 257]; counter = s_ಉದ್ದಳತೆ_ತಳ[counter - 257];
        ಆದರೆ (ಅಂಕೆ_extra) { mz_uint extra_ಬಿಟ್ಟುಗಳು; TINFL_GET_ಬಿಟ್ಟುಗಳು(25, extra_ಬಿಟ್ಟುಗಳು, ಅಂಕೆ_extra); counter += extra_ಬಿಟ್ಟುಗಳು; }

        TINFL_HUFF_DECODE(26, dist, &r->m_tables[1]);
        ಅಂಕೆ_extra = s_dist_extra[dist]; dist = s_dist_ತಳ[dist];
        ಆದರೆ (ಅಂಕೆ_extra) { mz_uint extra_ಬಿಟ್ಟುಗಳು; TINFL_GET_ಬಿಟ್ಟುಗಳು(27, extra_ಬಿಟ್ಟುಗಳು, ಅಂಕೆ_extra); dist += extra_ಬಿಟ್ಟುಗಳು; }

        dist_from_ಹೊರಹೋಗು_buf_ಆರಂಭ = p_ಹೊರಹೋಗು_buf_cur - p_ಹೊರಹೋಗು_buf_ಆರಂಭ;
        ಆದರೆ ((dist > dist_from_ಹೊರಹೋಗು_buf_ಆರಂಭ) && (decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF))
        {
          TINFL_CR_RETURN_FOREVER(37, TINFL_ಸ್ಥಿತಿ_FAILED);
        }

        pSrc = p_ಹೊರಹೋಗು_buf_ಆರಂಭ + ((dist_from_ಹೊರಹೋಗು_buf_ಆರಂಭ - dist) & ಹೊರಹೋಗು_buf_ಗಾತ್ರ_ಮುಖವಾಡ);

        ಆದರೆ ((MZ_MAX(p_ಹೊರಹೋಗು_buf_cur, pSrc) + counter) > p_ಹೊರಹೋಗು_buf_ಕೊನೆ)
        {
          ಆಗ (counter--)
          {
            ಆಗ (p_ಹೊರಹೋಗು_buf_cur >= p_ಹೊರಹೋಗು_buf_ಕೊನೆ) { TINFL_CR_RETURN(53, TINFL_ಸ್ಥಿತಿ_HAS_ಇನ್ನಷ್ಟು_OUTPUT); }
            *p_ಹೊರಹೋಗು_buf_cur++ = p_ಹೊರಹೋಗು_buf_ಆರಂಭ[(dist_from_ಹೊರಹೋಗು_buf_ಆರಂಭ++ - dist) & ಹೊರಹೋಗು_buf_ಗಾತ್ರ_ಮುಖವಾಡ];
          }
          ಮುಂದುವರಿ;
        }
#ಆದರೆ MINIZ_USE_UNALIGNED_LOADS_AND_STORES
        ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((counter >= 9) && (counter <= dist))
        {
          ಸ್ಥಿರಾಂಕ mz_uint8 *p_Src_ಕೊನೆ = pSrc + (counter & ~7);
          ಮಾಡು
          {
            ((mz_uint32 *)p_ಹೊರಹೋಗು_buf_cur)[0] = ((ಸ್ಥಿರಾಂಕ mz_uint32 *)pSrc)[0];
            ((mz_uint32 *)p_ಹೊರಹೋಗು_buf_cur)[1] = ((ಸ್ಥಿರಾಂಕ mz_uint32 *)pSrc)[1];
            p_ಹೊರಹೋಗು_buf_cur += 8;
          } ಆಗ ((pSrc += 8) < p_Src_ಕೊನೆ);
          ಆದರೆ ((counter &= 7) < 3)
          {
            ಆದರೆ (counter)
            {
              p_ಹೊರಹೋಗು_buf_cur[0] = pSrc[0];
              ಆದರೆ (counter > 1)
                p_ಹೊರಹೋಗು_buf_cur[1] = pSrc[1];
              p_ಹೊರಹೋಗು_buf_cur += counter;
            }
            ಮುಂದುವರಿ;
          }
        }
#ಆದರೆ_ಅಂತ್ಯ
        ಮಾಡು
        {
          p_ಹೊರಹೋಗು_buf_cur[0] = pSrc[0];
          p_ಹೊರಹೋಗು_buf_cur[1] = pSrc[1];
          p_ಹೊರಹೋಗು_buf_cur[2] = pSrc[2];
          p_ಹೊರಹೋಗು_buf_cur += 3; pSrc += 3;
        } ಆಗ ((ಪೂರ್ಣಾಂಕ)(counter -= 3) > 2);
        ಆದರೆ ((ಪೂರ್ಣಾಂಕ)counter > 0)
        {
          p_ಹೊರಹೋಗು_buf_cur[0] = pSrc[0];
          ಆದರೆ ((ಪೂರ್ಣಾಂಕ)counter > 1)
            p_ಹೊರಹೋಗು_buf_cur[1] = pSrc[1];
          p_ಹೊರಹೋಗು_buf_cur += counter;
        }
      }
    }
  } ಆಗ (!(r->m_final & 1));
  ಆದರೆ (decomp_flags & TINFL_FLAG_PARSE_ZLIB_ಶೀರ್ಷಿಕೆ)
  {
    TINFL_SKIP_ಬಿಟ್ಟುಗಳು(32, ಅಂಕೆ_ಬಿಟ್ಟುಗಳು & 7); ಗಾಗಿ (counter = 0; counter < 4; ++counter) { mz_uint s; ಆದರೆ (ಅಂಕೆ_ಬಿಟ್ಟುಗಳು) TINFL_GET_ಬಿಟ್ಟುಗಳು(41, s, 8); ಇಲ್ಲದಿದ್ದರೆ TINFL_GET_BYTE(42, s); r->m_z_adler32 = (r->m_z_adler32 << 8) | s; }
  }
  TINFL_CR_RETURN_FOREVER(34, TINFL_ಸ್ಥಿತಿ_ಮುಗಿದ);
  TINFL_CR_ಮುಕ್ತಾಯ

common_exit:
  r->m_ಅಂಕೆ_ಬಿಟ್ಟುಗಳು = ಅಂಕೆ_ಬಿಟ್ಟುಗಳು; r->m_ಬಿಟ್_buf = ಬಿಟ್_buf; r->m_dist = dist; r->m_counter = counter; r->m_ಅಂಕೆ_extra = ಅಂಕೆ_extra; r->m_dist_from_ಹೊರಹೋಗು_buf_ಆರಂಭ = dist_from_ಹೊರಹೋಗು_buf_ಆರಂಭ;
  *p_ಒಳ_buf_ಗಾತ್ರ = p_ಒಳ_buf_cur - p_ಒಳ_buf_ಮುಂದಿನ; *p_ಹೊರಹೋಗು_buf_ಗಾತ್ರ = p_ಹೊರಹೋಗು_buf_cur - p_ಹೊರಹೋಗು_buf_ಮುಂದಿನ;
  ಆದರೆ ((decomp_flags & (TINFL_FLAG_PARSE_ZLIB_ಶೀರ್ಷಿಕೆ | TINFL_FLAG_COMPUTE_ADLER32)) && (ಸ್ಥಿತಿ_2 >= 0))
  {
    ಸ್ಥಿರಾಂಕ mz_uint8 *ptr = p_ಹೊರಹೋಗು_buf_ಮುಂದಿನ; size_t buf_len = *p_ಹೊರಹೋಗು_buf_ಗಾತ್ರ;
    mz_uint32 i, s1 = r->m_check_adler32 & 0xffff, s2 = r->m_check_adler32 >> 16; size_t ಖಂಡ_len = buf_len % 5552;
    ಆಗ (buf_len)
    {
      ಗಾಗಿ (i = 0; i + 7 < ಖಂಡ_len; i += 8, ptr += 8)
      {
        s1 += ptr[0], s2 += s1; s1 += ptr[1], s2 += s1; s1 += ptr[2], s2 += s1; s1 += ptr[3], s2 += s1;
        s1 += ptr[4], s2 += s1; s1 += ptr[5], s2 += s1; s1 += ptr[6], s2 += s1; s1 += ptr[7], s2 += s1;
      }
      ಗಾಗಿ ( ; i < ಖಂಡ_len; ++i) s1 += *ptr++, s2 += s1;
      s1 %= 65521U, s2 %= 65521U; buf_len -= ಖಂಡ_len; ಖಂಡ_len = 5552;
    }
    r->m_check_adler32 = (s2 << 16) + s1; ಆದರೆ ((ಸ್ಥಿತಿ_2 == TINFL_ಸ್ಥಿತಿ_ಮುಗಿದ) && (decomp_flags & TINFL_FLAG_PARSE_ZLIB_ಶೀರ್ಷಿಕೆ) && (r->m_check_adler32 != r->m_z_adler32)) ಸ್ಥಿತಿ_2 = TINFL_ಸ್ಥಿತಿ_ADLER32_MISMATCH;
  }
  ಹಿಂತಿರುಗಿ ಸ್ಥಿತಿ_2;
}

// Higher level helper functions.
ಶೂನ್ಯ *tinfl_decompress_mem_ಗಮ್ಯ_ರಾಶಿ(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *pSrc_buf, size_t src_buf_len, size_t *p_ಹೊರಹೋಗು_len, ಪೂರ್ಣಾಂಕ flags)
{
  tinfl_decompressor decomp; ಶೂನ್ಯ *pBuf = ಖಾಲಿ, *pNew_buf; size_t src_buf_ofs = 0, ಹೊರಹೋಗು_buf_ಸಾಮರ್ಥ್ಯ = 0;
  *p_ಹೊರಹೋಗು_len = 0;
  tinfl_init(&decomp);
  ಗಾಗಿ ( ; ; )
  {
    size_t src_buf_ಗಾತ್ರ = src_buf_len - src_buf_ofs, dst_buf_ಗಾತ್ರ = ಹೊರಹೋಗು_buf_ಸಾಮರ್ಥ್ಯ - *p_ಹೊರಹೋಗು_len, new_ಹೊರಹೋಗು_buf_ಸಾಮರ್ಥ್ಯ;
    tinfl_ಸ್ಥಿತಿ ಸ್ಥಿತಿ_2 = tinfl_decompress(&decomp, (ಸ್ಥಿರಾಂಕ mz_uint8*)pSrc_buf + src_buf_ofs, &src_buf_ಗಾತ್ರ, (mz_uint8*)pBuf, pBuf ? (mz_uint8*)pBuf + *p_ಹೊರಹೋಗು_len : ಖಾಲಿ, &dst_buf_ಗಾತ್ರ,
      (flags & ~TINFL_FLAG_HAS_ಇನ್ನಷ್ಟು_ಒಳಹರಿವು) | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF);
    ಆದರೆ ((ಸ್ಥಿತಿ_2 < 0) || (ಸ್ಥಿತಿ_2 == TINFL_ಸ್ಥಿತಿ_NEEDS_ಇನ್ನಷ್ಟು_ಒಳಹರಿವು))
    {
      MZ_FREE(pBuf); *p_ಹೊರಹೋಗು_len = 0; ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    src_buf_ofs += src_buf_ಗಾತ್ರ;
    *p_ಹೊರಹೋಗು_len += dst_buf_ಗಾತ್ರ;
    ಆದರೆ (ಸ್ಥಿತಿ_2 == TINFL_ಸ್ಥಿತಿ_ಮುಗಿದ) ನಿಲ್ಲಿಸು;
    new_ಹೊರಹೋಗು_buf_ಸಾಮರ್ಥ್ಯ = ಹೊರಹೋಗು_buf_ಸಾಮರ್ಥ್ಯ * 2; ಆದರೆ (new_ಹೊರಹೋಗು_buf_ಸಾಮರ್ಥ್ಯ < 128) new_ಹೊರಹೋಗು_buf_ಸಾಮರ್ಥ್ಯ = 128;
    pNew_buf = MZ_REALLOC(pBuf, new_ಹೊರಹೋಗು_buf_ಸಾಮರ್ಥ್ಯ);
    ಆದರೆ (!pNew_buf)
    {
      MZ_FREE(pBuf); *p_ಹೊರಹೋಗು_len = 0; ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    pBuf = pNew_buf; ಹೊರಹೋಗು_buf_ಸಾಮರ್ಥ್ಯ = new_ಹೊರಹೋಗು_buf_ಸಾಮರ್ಥ್ಯ;
  }
  ಹಿಂತಿರುಗಿ pBuf;
}

size_t tinfl_decompress_mem_ಗಮ್ಯ_mem(ಶೂನ್ಯ *p_ಹೊರಹೋಗು_buf, size_t ಹೊರಹೋಗು_buf_len, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *pSrc_buf, size_t src_buf_len, ಪೂರ್ಣಾಂಕ flags)
{
  tinfl_decompressor decomp; tinfl_ಸ್ಥಿತಿ ಸ್ಥಿತಿ_2; tinfl_init(&decomp);
  ಸ್ಥಿತಿ_2 = tinfl_decompress(&decomp, (ಸ್ಥಿರಾಂಕ mz_uint8*)pSrc_buf, &src_buf_len, (mz_uint8*)p_ಹೊರಹೋಗು_buf, (mz_uint8*)p_ಹೊರಹೋಗು_buf, &ಹೊರಹೋಗು_buf_len, (flags & ~TINFL_FLAG_HAS_ಇನ್ನಷ್ಟು_ಒಳಹರಿವು) | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF);
  ಹಿಂತಿರುಗಿ (ಸ್ಥಿತಿ_2 != TINFL_ಸ್ಥಿತಿ_ಮುಗಿದ) ? TINFL_DECOMPRESS_MEM_ಗಮ್ಯ_MEM_FAILED : ಹೊರಹೋಗು_buf_len;
}

ಪೂರ್ಣಾಂಕ tinfl_decompress_mem_ಗಮ್ಯ_callback(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *p_ಒಳ_buf, size_t *p_ಒಳ_buf_ಗಾತ್ರ, tinfl_put_buf_func_ptr pPut_buf_func, ಶೂನ್ಯ *pPut_buf_user, ಪೂರ್ಣಾಂಕ flags)
{
  ಪೂರ್ಣಾಂಕ ಫಲಿತಾಂಶ = 0;
  tinfl_decompressor decomp;
  mz_uint8 *pDict = (mz_uint8*)MZ_MALLOC(TINFL_LZ_DICT_ಗಾತ್ರ); size_t ಒಳ_buf_ofs = 0, dict_ofs = 0;
  ಆದರೆ (!pDict)
    ಹಿಂತಿರುಗಿ TINFL_ಸ್ಥಿತಿ_FAILED;
  memset(pDict,0,TINFL_LZ_DICT_ಗಾತ್ರ);
  tinfl_init(&decomp);
  ಗಾಗಿ ( ; ; )
  {
    size_t ಒಳ_buf_ಗಾತ್ರ = *p_ಒಳ_buf_ಗಾತ್ರ - ಒಳ_buf_ofs, dst_buf_ಗಾತ್ರ = TINFL_LZ_DICT_ಗಾತ್ರ - dict_ofs;
    tinfl_ಸ್ಥಿತಿ ಸ್ಥಿತಿ_2 = tinfl_decompress(&decomp, (ಸ್ಥಿರಾಂಕ mz_uint8*)p_ಒಳ_buf + ಒಳ_buf_ofs, &ಒಳ_buf_ಗಾತ್ರ, pDict, pDict + dict_ofs, &dst_buf_ಗಾತ್ರ,
      (flags & ~(TINFL_FLAG_HAS_ಇನ್ನಷ್ಟು_ಒಳಹರಿವು | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF)));
    ಒಳ_buf_ofs += ಒಳ_buf_ಗಾತ್ರ;
    ಆದರೆ ((dst_buf_ಗಾತ್ರ) && (!(*pPut_buf_func)(pDict + dict_ofs, (ಪೂರ್ಣಾಂಕ)dst_buf_ಗಾತ್ರ, pPut_buf_user)))
      ನಿಲ್ಲಿಸು;
    ಆದರೆ (ಸ್ಥಿತಿ_2 != TINFL_ಸ್ಥಿತಿ_HAS_ಇನ್ನಷ್ಟು_OUTPUT)
    {
      ಫಲಿತಾಂಶ = (ಸ್ಥಿತಿ_2 == TINFL_ಸ್ಥಿತಿ_ಮುಗಿದ);
      ನಿಲ್ಲಿಸು;
    }
    dict_ofs = (dict_ofs + dst_buf_ಗಾತ್ರ) & (TINFL_LZ_DICT_ಗಾತ್ರ - 1);
  }
  MZ_FREE(pDict);
  *p_ಒಳ_buf_ಗಾತ್ರ = ಒಳ_buf_ofs;
  ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}
#ಆದರೆ_ಅಂತ್ಯ /*#ifndef MINIZ_NO_INFLATE_APIS*/

// ------------------- Low-level Compression (independent from all decompression API's)
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_DEFLATE_APIS

// Purposely making these tables static for faster init and thread safety.
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ mz_uint16 s_tdefl_len_sym[256] = {
  257,258,259,260,261,262,263,264,265,265,266,266,267,267,268,268,269,269,269,269,270,270,270,270,271,271,271,271,272,272,272,272,
  273,273,273,273,273,273,273,273,274,274,274,274,274,274,274,274,275,275,275,275,275,275,275,275,276,276,276,276,276,276,276,276,
  277,277,277,277,277,277,277,277,277,277,277,277,277,277,277,277,278,278,278,278,278,278,278,278,278,278,278,278,278,278,278,278,
  279,279,279,279,279,279,279,279,279,279,279,279,279,279,279,279,280,280,280,280,280,280,280,280,280,280,280,280,280,280,280,280,
  281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,
  282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,
  283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,
  284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,285 };

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ mz_uint8 s_tdefl_len_extra[256] = {
  0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0 };

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ mz_uint8 s_tdefl_small_dist_sym[512] = {
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

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ mz_uint8 s_tdefl_small_dist_extra[512] = {
  0,0,0,0,1,1,1,1,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
  6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
  6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7 };

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ mz_uint8 s_tdefl_large_dist_sym[128] = {
  0,0,18,19,20,20,21,21,22,22,22,22,23,23,23,23,24,24,24,24,24,24,24,24,25,25,25,25,25,25,25,25,26,26,26,26,26,26,26,26,26,26,26,26,
  26,26,26,26,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,
  28,28,28,28,28,28,28,28,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29 };

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ mz_uint8 s_tdefl_large_dist_extra[128] = {
  0,0,8,8,9,9,9,9,10,10,10,10,10,10,10,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,
  12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
  13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13 };

// Radix sorts tdefl_sym_freq[] array by 16-bit key m_key. Returns ptr to sorted values.
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ { mz_uint16 m_ಕೀಲಿ, m_sym_ಸೂಚ್ಯಂಕ; } tdefl_sym_freq;
ಸ್ಥಿರ tdefl_sym_freq* tdefl_radix_ವಿಂಗಡಿಸು_syms(mz_uint ಅಂಕೆ_syms, tdefl_sym_freq* pSyms0, tdefl_sym_freq* pSyms1)
{
  mz_uint32 ಒಟ್ಟು_passes = 2, pass_ಸರಿಸು, pass, i, hist[256 * 2]; tdefl_sym_freq* pCur_syms = pSyms0, *pNew_syms = pSyms1; MZ_CLEAR_ARR(hist);
  ಗಾಗಿ (i = 0; i < ಅಂಕೆ_syms; i++) { mz_uint freq = pSyms0[i].m_ಕೀಲಿ; hist[freq & 0xFF]++; hist[256 + ((freq >> 8) & 0xFF)]++; }
  ಆಗ ((ಒಟ್ಟು_passes > 1) && (ಅಂಕೆ_syms == hist[(ಒಟ್ಟು_passes - 1) * 256])) ಒಟ್ಟು_passes--;
  ಗಾಗಿ (pass_ಸರಿಸು = 0, pass = 0; pass < ಒಟ್ಟು_passes; pass++, pass_ಸರಿಸು += 8)
  {
    ಸ್ಥಿರಾಂಕ mz_uint32* pHist = &hist[pass << 8];
    mz_uint offsets[256], cur_ofs = 0;
    ಗಾಗಿ (i = 0; i < 256; i++) { offsets[i] = cur_ofs; cur_ofs += pHist[i]; }
    ಗಾಗಿ (i = 0; i < ಅಂಕೆ_syms; i++) pNew_syms[offsets[(pCur_syms[i].m_ಕೀಲಿ >> pass_ಸರಿಸು) & 0xFF]++] = pCur_syms[i];
    { tdefl_sym_freq* t = pCur_syms; pCur_syms = pNew_syms; pNew_syms = t; }
  }
  ಹಿಂತಿರುಗಿ pCur_syms;
}

// tdefl_calculate_minimum_redundancy() originally written by: Alistair Moffat, alistair@cs.mu.oz.au, Jyrki Katajainen, jyrki@diku.dk, November 1996.
ಸ್ಥಿರ ಶೂನ್ಯ tdefl_calculate_minimum_redundancy(tdefl_sym_freq *A, ಪೂರ್ಣಾಂಕ n)
{
  ಪೂರ್ಣಾಂಕ ಬೇರು, ಎಲೆ, ಮುಂದಿನ, avbl, ಬಳಸಿದ, dpth;
  ಆದರೆ (n==0) ಹಿಂತಿರುಗಿ; ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (n==1) { A[0].m_ಕೀಲಿ = 1; ಹಿಂತಿರುಗಿ; }
  A[0].m_ಕೀಲಿ += A[1].m_ಕೀಲಿ; ಬೇರು = 0; ಎಲೆ = 2;
  ಗಾಗಿ (ಮುಂದಿನ=1; ಮುಂದಿನ < n-1; ಮುಂದಿನ++)
  {
    ಆದರೆ (ಎಲೆ>=n || A[ಬೇರು].m_ಕೀಲಿ<A[ಎಲೆ].m_ಕೀಲಿ) { A[ಮುಂದಿನ].m_ಕೀಲಿ = A[ಬೇರು].m_ಕೀಲಿ; A[ಬೇರು++].m_ಕೀಲಿ = (mz_uint16)ಮುಂದಿನ; } ಇಲ್ಲದಿದ್ದರೆ A[ಮುಂದಿನ].m_ಕೀಲಿ = A[ಎಲೆ++].m_ಕೀಲಿ;
    ಆದರೆ (ಎಲೆ>=n || (ಬೇರು<ಮುಂದಿನ && A[ಬೇರು].m_ಕೀಲಿ<A[ಎಲೆ].m_ಕೀಲಿ)) { A[ಮುಂದಿನ].m_ಕೀಲಿ = (mz_uint16)(A[ಮುಂದಿನ].m_ಕೀಲಿ + A[ಬೇರು].m_ಕೀಲಿ); A[ಬೇರು++].m_ಕೀಲಿ = (mz_uint16)ಮುಂದಿನ; } ಇಲ್ಲದಿದ್ದರೆ A[ಮುಂದಿನ].m_ಕೀಲಿ = (mz_uint16)(A[ಮುಂದಿನ].m_ಕೀಲಿ + A[ಎಲೆ++].m_ಕೀಲಿ);
  }
  A[n-2].m_ಕೀಲಿ = 0; ಗಾಗಿ (ಮುಂದಿನ=n-3; ಮುಂದಿನ>=0; ಮುಂದಿನ--) A[ಮುಂದಿನ].m_ಕೀಲಿ = A[A[ಮುಂದಿನ].m_ಕೀಲಿ].m_ಕೀಲಿ+1;
  avbl = 1; ಬಳಸಿದ = dpth = 0; ಬೇರು = n-2; ಮುಂದಿನ = n-1;
  ಆಗ (avbl>0)
  {
    ಆಗ (ಬೇರು>=0 && (ಪೂರ್ಣಾಂಕ)A[ಬೇರು].m_ಕೀಲಿ==dpth) { ಬಳಸಿದ++; ಬೇರು--; }
    ಆಗ (avbl>ಬಳಸಿದ) { A[ಮುಂದಿನ--].m_ಕೀಲಿ = (mz_uint16)(dpth); avbl--; }
    avbl = 2*ಬಳಸಿದ; dpth++; ಬಳಸಿದ = 0;
  }
}

// Limits canonical Huffman code table's max code size.
ಎಣಿಕೆ { TDEFL_MAX_SUPPORTED_HUFF_CODESIZE = 32 };
ಸ್ಥಿರ ಶೂನ್ಯ tdefl_huffman_enforce_max_ಸಂಕೇತ_ಗಾತ್ರ(ಪೂರ್ಣಾಂಕ *p_ಅಂಕೆ_codes, ಪೂರ್ಣಾಂಕ ಸಂಕೇತ_list_len, ಪೂರ್ಣಾಂಕ max_ಸಂಕೇತ_ಗಾತ್ರ)
{
  ಪೂರ್ಣಾಂಕ i; mz_uint32 ಒಟ್ಟು = 0; ಆದರೆ (ಸಂಕೇತ_list_len <= 1) ಹಿಂತಿರುಗಿ;
  ಗಾಗಿ (i = max_ಸಂಕೇತ_ಗಾತ್ರ + 1; i <= TDEFL_MAX_SUPPORTED_HUFF_CODESIZE; i++) p_ಅಂಕೆ_codes[max_ಸಂಕೇತ_ಗಾತ್ರ] += p_ಅಂಕೆ_codes[i];
  ಗಾಗಿ (i = max_ಸಂಕೇತ_ಗಾತ್ರ; i > 0; i--) ಒಟ್ಟು += (((mz_uint32)p_ಅಂಕೆ_codes[i]) << (max_ಸಂಕೇತ_ಗಾತ್ರ - i));
  ಆಗ (ಒಟ್ಟು != (1UL << max_ಸಂಕೇತ_ಗಾತ್ರ))
  {
    p_ಅಂಕೆ_codes[max_ಸಂಕೇತ_ಗಾತ್ರ]--;
    ಗಾಗಿ (i = max_ಸಂಕೇತ_ಗಾತ್ರ - 1; i > 0; i--) ಆದರೆ (p_ಅಂಕೆ_codes[i]) { p_ಅಂಕೆ_codes[i]--; p_ಅಂಕೆ_codes[i + 1] += 2; ನಿಲ್ಲಿಸು; }
    ಒಟ್ಟು--;
  }
}

ಸ್ಥಿರ ಶೂನ್ಯ tdefl_optimize_huffman_ಕೋಷ್ಟಕ(tdefl_compressor *d, ಪೂರ್ಣಾಂಕ ಕೋಷ್ಟಕ_ಅಂಕೆ, ಪೂರ್ಣಾಂಕ ಕೋಷ್ಟಕ_len, ಪೂರ್ಣಾಂಕ ಸಂಕೇತ_ಗಾತ್ರ_ಎಲ್ಲೆ, ಪೂರ್ಣಾಂಕ static_ಕೋಷ್ಟಕ)
{
  ಪೂರ್ಣಾಂಕ i, j, l, ಅಂಕೆ_codes[1 + TDEFL_MAX_SUPPORTED_HUFF_CODESIZE]; mz_uint ಮುಂದಿನ_ಸಂಕೇತ[TDEFL_MAX_SUPPORTED_HUFF_CODESIZE + 1]; MZ_CLEAR_ARR(ಅಂಕೆ_codes);
  ಆದರೆ (static_ಕೋಷ್ಟಕ)
  {
    ಗಾಗಿ (i = 0; i < ಕೋಷ್ಟಕ_len; i++) ಅಂಕೆ_codes[d->m_huff_ಸಂಕೇತ_sizes[ಕೋಷ್ಟಕ_ಅಂಕೆ][i]]++;
  }
  ಇಲ್ಲದಿದ್ದರೆ
  {
    tdefl_sym_freq syms0[TDEFL_MAX_HUFF_SYMBOLS], syms1[TDEFL_MAX_HUFF_SYMBOLS], *pSyms;
    ಪೂರ್ಣಾಂಕ ಅಂಕೆ_ಬಳಸಿದ_syms = 0;
    ಸ್ಥಿರಾಂಕ mz_uint16 *p_Sym_ಎಣಿಕೆ = &d->m_huff_ಎಣಿಕೆ[ಕೋಷ್ಟಕ_ಅಂಕೆ][0];
    ಗಾಗಿ (i = 0; i < ಕೋಷ್ಟಕ_len; i++) ಆದರೆ (p_Sym_ಎಣಿಕೆ[i]) { syms0[ಅಂಕೆ_ಬಳಸಿದ_syms].m_ಕೀಲಿ = (mz_uint16)p_Sym_ಎಣಿಕೆ[i]; syms0[ಅಂಕೆ_ಬಳಸಿದ_syms++].m_sym_ಸೂಚ್ಯಂಕ = (mz_uint16)i; }

    pSyms = tdefl_radix_ವಿಂಗಡಿಸು_syms(ಅಂಕೆ_ಬಳಸಿದ_syms, syms0, syms1); tdefl_calculate_minimum_redundancy(pSyms, ಅಂಕೆ_ಬಳಸಿದ_syms);

    ಗಾಗಿ (i = 0; i < ಅಂಕೆ_ಬಳಸಿದ_syms; i++) ಅಂಕೆ_codes[pSyms[i].m_ಕೀಲಿ]++;

    tdefl_huffman_enforce_max_ಸಂಕೇತ_ಗಾತ್ರ(ಅಂಕೆ_codes, ಅಂಕೆ_ಬಳಸಿದ_syms, ಸಂಕೇತ_ಗಾತ್ರ_ಎಲ್ಲೆ);

    MZ_CLEAR_ARR(d->m_huff_ಸಂಕೇತ_sizes[ಕೋಷ್ಟಕ_ಅಂಕೆ]); MZ_CLEAR_ARR(d->m_huff_codes[ಕೋಷ್ಟಕ_ಅಂಕೆ]);
    ಗಾಗಿ (i = 1, j = ಅಂಕೆ_ಬಳಸಿದ_syms; i <= ಸಂಕೇತ_ಗಾತ್ರ_ಎಲ್ಲೆ; i++)
      ಗಾಗಿ (l = ಅಂಕೆ_codes[i]; l > 0; l--) d->m_huff_ಸಂಕೇತ_sizes[ಕೋಷ್ಟಕ_ಅಂಕೆ][pSyms[--j].m_sym_ಸೂಚ್ಯಂಕ] = (mz_uint8)(i);
  }

  ಮುಂದಿನ_ಸಂಕೇತ[1] = 0; ಗಾಗಿ (j = 0, i = 2; i <= ಸಂಕೇತ_ಗಾತ್ರ_ಎಲ್ಲೆ; i++) ಮುಂದಿನ_ಸಂಕೇತ[i] = j = ((j + ಅಂಕೆ_codes[i - 1]) << 1);

  ಗಾಗಿ (i = 0; i < ಕೋಷ್ಟಕ_len; i++)
  {
    mz_uint rev_ಸಂಕೇತ = 0, ಸಂಕೇತ_2, ಸಂಕೇತ_ಗಾತ್ರ_2; ಆದರೆ ((ಸಂಕೇತ_ಗಾತ್ರ_2 = d->m_huff_ಸಂಕೇತ_sizes[ಕೋಷ್ಟಕ_ಅಂಕೆ][i]) == 0) ಮುಂದುವರಿ;
    ಸಂಕೇತ_2 = ಮುಂದಿನ_ಸಂಕೇತ[ಸಂಕೇತ_ಗಾತ್ರ_2]++; ಗಾಗಿ (l = ಸಂಕೇತ_ಗಾತ್ರ_2; l > 0; l--, ಸಂಕೇತ_2 >>= 1) rev_ಸಂಕೇತ = (rev_ಸಂಕೇತ << 1) | (ಸಂಕೇತ_2 & 1);
    d->m_huff_codes[ಕೋಷ್ಟಕ_ಅಂಕೆ][i] = (mz_uint16)rev_ಸಂಕೇತ;
  }
}

#ವ್ಯಾಖ್ಯಾನಿಸು TDEFL_PUT_ಬಿಟ್ಟುಗಳು(b, l) ಮಾಡು { \
  mz_uint ಬಿಟ್ಟುಗಳು = b; mz_uint len = l; MZ_ASSERT(ಬಿಟ್ಟುಗಳು <= ((1U << len) - 1U)); \
  d->m_ಬಿಟ್_ಬಫರ್ |= (ಬಿಟ್ಟುಗಳು << d->m_ಬಿಟ್ಟುಗಳು_ಒಳ); d->m_ಬಿಟ್ಟುಗಳು_ಒಳ += len; \
  ಆಗ (d->m_ಬಿಟ್ಟುಗಳು_ಒಳ >= 8) { \
    ಆದರೆ (d->m_pOutput_buf < d->m_p_Output_buf_ಕೊನೆ) \
      *d->m_pOutput_buf++ = (mz_uint8)(d->m_ಬಿಟ್_ಬಫರ್); \
    d->m_ಬಿಟ್_ಬಫರ್ >>= 8; \
    d->m_ಬಿಟ್ಟುಗಳು_ಒಳ -= 8; \
  } \
} MZ_MACRO_ಕೊನೆ

#ವ್ಯಾಖ್ಯಾನಿಸು TDEFL_RLE_PREV_ಸಂಕೇತ_ಗಾತ್ರ() ಮಾಡು { \
  ಆದರೆ (rle_repeat_ಎಣಿಕೆ) { \
    ಆದರೆ (rle_repeat_ಎಣಿಕೆ < 3) { \
      d->m_huff_ಎಣಿಕೆ[2][prev_ಸಂಕೇತ_ಗಾತ್ರ] = (mz_uint16)(d->m_huff_ಎಣಿಕೆ[2][prev_ಸಂಕೇತ_ಗಾತ್ರ] + rle_repeat_ಎಣಿಕೆ); \
      ಆಗ (rle_repeat_ಎಣಿಕೆ--) packed_ಸಂಕೇತ_sizes[ಅಂಕೆ_packed_ಸಂಕೇತ_sizes++] = prev_ಸಂಕೇತ_ಗಾತ್ರ; \
    } ಇಲ್ಲದಿದ್ದರೆ { \
      d->m_huff_ಎಣಿಕೆ[2][16] = (mz_uint16)(d->m_huff_ಎಣಿಕೆ[2][16] + 1); packed_ಸಂಕೇತ_sizes[ಅಂಕೆ_packed_ಸಂಕೇತ_sizes++] = 16; packed_ಸಂಕೇತ_sizes[ಅಂಕೆ_packed_ಸಂಕೇತ_sizes++] = (mz_uint8)(rle_repeat_ಎಣಿಕೆ - 3); \
  } rle_repeat_ಎಣಿಕೆ = 0; } \
} MZ_MACRO_ಕೊನೆ

#ವ್ಯಾಖ್ಯಾನಿಸು TDEFL_RLE_ZERO_ಸಂಕೇತ_ಗಾತ್ರ() ಮಾಡು { \
  ಆದರೆ (rle_z_ಎಣಿಕೆ) { \
    ಆದರೆ (rle_z_ಎಣಿಕೆ < 3) { \
      d->m_huff_ಎಣಿಕೆ[2][0] = (mz_uint16)(d->m_huff_ಎಣಿಕೆ[2][0] + rle_z_ಎಣಿಕೆ); ಆಗ (rle_z_ಎಣಿಕೆ--) packed_ಸಂಕೇತ_sizes[ಅಂಕೆ_packed_ಸಂಕೇತ_sizes++] = 0; \
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (rle_z_ಎಣಿಕೆ <= 10) { \
      d->m_huff_ಎಣಿಕೆ[2][17] = (mz_uint16)(d->m_huff_ಎಣಿಕೆ[2][17] + 1); packed_ಸಂಕೇತ_sizes[ಅಂಕೆ_packed_ಸಂಕೇತ_sizes++] = 17; packed_ಸಂಕೇತ_sizes[ಅಂಕೆ_packed_ಸಂಕೇತ_sizes++] = (mz_uint8)(rle_z_ಎಣಿಕೆ - 3); \
    } ಇಲ್ಲದಿದ್ದರೆ { \
      d->m_huff_ಎಣಿಕೆ[2][18] = (mz_uint16)(d->m_huff_ಎಣಿಕೆ[2][18] + 1); packed_ಸಂಕೇತ_sizes[ಅಂಕೆ_packed_ಸಂಕೇತ_sizes++] = 18; packed_ಸಂಕೇತ_sizes[ಅಂಕೆ_packed_ಸಂಕೇತ_sizes++] = (mz_uint8)(rle_z_ಎಣಿಕೆ - 11); \
  } rle_z_ಎಣಿಕೆ = 0; } \
} MZ_MACRO_ಕೊನೆ

ಸ್ಥಿರ mz_uint8 s_tdefl_packed_ಸಂಕೇತ_ಗಾತ್ರ_syms_swizzle[] = { 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 };

ಸ್ಥಿರ ಶೂನ್ಯ tdefl_ಆರಂಭ_dynamic_ಖಂಡ(tdefl_compressor *d)
{
  ಪೂರ್ಣಾಂಕ ಅಂಕೆ_lit_codes, ಅಂಕೆ_dist_codes, ಅಂಕೆ_ಬಿಟ್_lengths; mz_uint i, ಒಟ್ಟು_ಸಂಕೇತ_sizes_ಗಮ್ಯ_pack, ಅಂಕೆ_packed_ಸಂಕೇತ_sizes, rle_z_ಎಣಿಕೆ, rle_repeat_ಎಣಿಕೆ, packed_ಸಂಕೇತ_sizes_ಸೂಚ್ಯಂಕ;
  mz_uint8 ಸಂಕೇತ_sizes_ಗಮ್ಯ_pack[TDEFL_MAX_HUFF_SYMBOLS_0 + TDEFL_MAX_HUFF_SYMBOLS_1], packed_ಸಂಕೇತ_sizes[TDEFL_MAX_HUFF_SYMBOLS_0 + TDEFL_MAX_HUFF_SYMBOLS_1], prev_ಸಂಕೇತ_ಗಾತ್ರ = 0xFF;

  d->m_huff_ಎಣಿಕೆ[0][256] = 1;

  tdefl_optimize_huffman_ಕೋಷ್ಟಕ(d, 0, TDEFL_MAX_HUFF_SYMBOLS_0, 15, MZ_FALSE);
  tdefl_optimize_huffman_ಕೋಷ್ಟಕ(d, 1, TDEFL_MAX_HUFF_SYMBOLS_1, 15, MZ_FALSE);

  ಗಾಗಿ (ಅಂಕೆ_lit_codes = 286; ಅಂಕೆ_lit_codes > 257; ಅಂಕೆ_lit_codes--) ಆದರೆ (d->m_huff_ಸಂಕೇತ_sizes[0][ಅಂಕೆ_lit_codes - 1]) ನಿಲ್ಲಿಸು;
  ಗಾಗಿ (ಅಂಕೆ_dist_codes = 30; ಅಂಕೆ_dist_codes > 1; ಅಂಕೆ_dist_codes--) ಆದರೆ (d->m_huff_ಸಂಕೇತ_sizes[1][ಅಂಕೆ_dist_codes - 1]) ನಿಲ್ಲಿಸು;

  ಸ್ಮರಣೆ_ನಕಲು(ಸಂಕೇತ_sizes_ಗಮ್ಯ_pack, &d->m_huff_ಸಂಕೇತ_sizes[0][0], ಅಂಕೆ_lit_codes);
  ಸ್ಮರಣೆ_ನಕಲು(ಸಂಕೇತ_sizes_ಗಮ್ಯ_pack + ಅಂಕೆ_lit_codes, &d->m_huff_ಸಂಕೇತ_sizes[1][0], ಅಂಕೆ_dist_codes);
  ಒಟ್ಟು_ಸಂಕೇತ_sizes_ಗಮ್ಯ_pack = ಅಂಕೆ_lit_codes + ಅಂಕೆ_dist_codes; ಅಂಕೆ_packed_ಸಂಕೇತ_sizes = 0; rle_z_ಎಣಿಕೆ = 0; rle_repeat_ಎಣಿಕೆ = 0;

  memset(&d->m_huff_ಎಣಿಕೆ[2][0], 0, ಗಾತ್ರ(d->m_huff_ಎಣಿಕೆ[2][0]) * TDEFL_MAX_HUFF_SYMBOLS_2);
  ಗಾಗಿ (i = 0; i < ಒಟ್ಟು_ಸಂಕೇತ_sizes_ಗಮ್ಯ_pack; i++)
  {
    mz_uint8 ಸಂಕೇತ_ಗಾತ್ರ_2 = ಸಂಕೇತ_sizes_ಗಮ್ಯ_pack[i];
    ಆದರೆ (!ಸಂಕೇತ_ಗಾತ್ರ_2)
    {
      TDEFL_RLE_PREV_ಸಂಕೇತ_ಗಾತ್ರ();
      ಆದರೆ (++rle_z_ಎಣಿಕೆ == 138) { TDEFL_RLE_ZERO_ಸಂಕೇತ_ಗಾತ್ರ(); }
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
      TDEFL_RLE_ZERO_ಸಂಕೇತ_ಗಾತ್ರ();
      ಆದರೆ (ಸಂಕೇತ_ಗಾತ್ರ_2 != prev_ಸಂಕೇತ_ಗಾತ್ರ)
      {
        TDEFL_RLE_PREV_ಸಂಕೇತ_ಗಾತ್ರ();
        d->m_huff_ಎಣಿಕೆ[2][ಸಂಕೇತ_ಗಾತ್ರ_2] = (mz_uint16)(d->m_huff_ಎಣಿಕೆ[2][ಸಂಕೇತ_ಗಾತ್ರ_2] + 1); packed_ಸಂಕೇತ_sizes[ಅಂಕೆ_packed_ಸಂಕೇತ_sizes++] = ಸಂಕೇತ_ಗಾತ್ರ_2;
      }
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (++rle_repeat_ಎಣಿಕೆ == 6)
      {
        TDEFL_RLE_PREV_ಸಂಕೇತ_ಗಾತ್ರ();
      }
    }
    prev_ಸಂಕೇತ_ಗಾತ್ರ = ಸಂಕೇತ_ಗಾತ್ರ_2;
  }
  ಆದರೆ (rle_repeat_ಎಣಿಕೆ) { TDEFL_RLE_PREV_ಸಂಕೇತ_ಗಾತ್ರ(); } ಇಲ್ಲದಿದ್ದರೆ { TDEFL_RLE_ZERO_ಸಂಕೇತ_ಗಾತ್ರ(); }

  tdefl_optimize_huffman_ಕೋಷ್ಟಕ(d, 2, TDEFL_MAX_HUFF_SYMBOLS_2, 7, MZ_FALSE);

  TDEFL_PUT_ಬಿಟ್ಟುಗಳು(2, 2);

  TDEFL_PUT_ಬಿಟ್ಟುಗಳು(ಅಂಕೆ_lit_codes - 257, 5);
  TDEFL_PUT_ಬಿಟ್ಟುಗಳು(ಅಂಕೆ_dist_codes - 1, 5);

  ಗಾಗಿ (ಅಂಕೆ_ಬಿಟ್_lengths = 18; ಅಂಕೆ_ಬಿಟ್_lengths >= 0; ಅಂಕೆ_ಬಿಟ್_lengths--) ಆದರೆ (d->m_huff_ಸಂಕೇತ_sizes[2][s_tdefl_packed_ಸಂಕೇತ_ಗಾತ್ರ_syms_swizzle[ಅಂಕೆ_ಬಿಟ್_lengths]]) ನಿಲ್ಲಿಸು;
  ಅಂಕೆ_ಬಿಟ್_lengths = MZ_MAX(4, (ಅಂಕೆ_ಬಿಟ್_lengths + 1)); TDEFL_PUT_ಬಿಟ್ಟುಗಳು(ಅಂಕೆ_ಬಿಟ್_lengths - 4, 4);
  ಗಾಗಿ (i = 0; (ಪೂರ್ಣಾಂಕ)i < ಅಂಕೆ_ಬಿಟ್_lengths; i++) TDEFL_PUT_ಬಿಟ್ಟುಗಳು(d->m_huff_ಸಂಕೇತ_sizes[2][s_tdefl_packed_ಸಂಕೇತ_ಗಾತ್ರ_syms_swizzle[i]], 3);

  ಗಾಗಿ (packed_ಸಂಕೇತ_sizes_ಸೂಚ್ಯಂಕ = 0; packed_ಸಂಕೇತ_sizes_ಸೂಚ್ಯಂಕ < ಅಂಕೆ_packed_ಸಂಕೇತ_sizes; )
  {
    mz_uint ಸಂಕೇತ_2 = packed_ಸಂಕೇತ_sizes[packed_ಸಂಕೇತ_sizes_ಸೂಚ್ಯಂಕ++]; MZ_ASSERT(ಸಂಕೇತ_2 < TDEFL_MAX_HUFF_SYMBOLS_2);
    TDEFL_PUT_ಬಿಟ್ಟುಗಳು(d->m_huff_codes[2][ಸಂಕೇತ_2], d->m_huff_ಸಂಕೇತ_sizes[2][ಸಂಕೇತ_2]);
    ಆದರೆ (ಸಂಕೇತ_2 >= 16) TDEFL_PUT_ಬಿಟ್ಟುಗಳು(packed_ಸಂಕೇತ_sizes[packed_ಸಂಕೇತ_sizes_ಸೂಚ್ಯಂಕ++], "\02\03\07"[ಸಂಕೇತ_2 - 16]);
  }
}

ಸ್ಥಿರ ಶೂನ್ಯ tdefl_ಆರಂಭ_static_ಖಂಡ(tdefl_compressor *d)
{
  mz_uint i;
  mz_uint8 *p = &d->m_huff_ಸಂಕೇತ_sizes[0][0];

  ಗಾಗಿ (i = 0; i <= 143; ++i) *p++ = 8;
  ಗಾಗಿ ( ; i <= 255; ++i) *p++ = 9;
  ಗಾಗಿ ( ; i <= 279; ++i) *p++ = 7;
  ಗಾಗಿ ( ; i <= 287; ++i) *p++ = 8;

  memset(d->m_huff_ಸಂಕೇತ_sizes[1], 5, 32);

  tdefl_optimize_huffman_ಕೋಷ್ಟಕ(d, 0, 288, 15, MZ_TRUE);
  tdefl_optimize_huffman_ಕೋಷ್ಟಕ(d, 1, 32, 15, MZ_TRUE);

  TDEFL_PUT_ಬಿಟ್ಟುಗಳು(1, 2);
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ mz_uint mz_bitmasks[17] = { 0x0000, 0x0001, 0x0003, 0x0007, 0x000F, 0x001F, 0x003F, 0x007F, 0x00FF, 0x01FF, 0x03FF, 0x07FF, 0x0FFF, 0x1FFF, 0x3FFF, 0x7FFF, 0xFFFF };

#ಆದರೆ MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN && MINIZ_HAS_64_ಬಿಟ್_REGISTERS
ಸ್ಥಿರ mz_bool tdefl_compress_lz_codes(tdefl_compressor *d)
{
  mz_uint flags;
  mz_uint8 *pLZ_codes;
  mz_uint8 *pOutput_buf = d->m_pOutput_buf;
  mz_uint8 *p_LZ_ಸಂಕೇತ_buf_ಕೊನೆ = d->m_p_LZ_ಸಂಕೇತ_buf;
  mz_uint64 ಬಿಟ್_ಬಫರ್ = d->m_ಬಿಟ್_ಬಫರ್;
  mz_uint ಬಿಟ್ಟುಗಳು_ಒಳ = d->m_ಬಿಟ್ಟುಗಳು_ಒಳ;

#ವ್ಯಾಖ್ಯಾನಿಸು TDEFL_PUT_ಬಿಟ್ಟುಗಳು_FAST(b, l) { ಬಿಟ್_ಬಫರ್ |= (((mz_uint64)(b)) << ಬಿಟ್ಟುಗಳು_ಒಳ); ಬಿಟ್ಟುಗಳು_ಒಳ += (l); }

  flags = 1;
  ಗಾಗಿ (pLZ_codes = d->m_lz_ಸಂಕೇತ_buf; pLZ_codes < p_LZ_ಸಂಕೇತ_buf_ಕೊನೆ; flags >>= 1)
  {
    ಆದರೆ (flags == 1)
      flags = *pLZ_codes++ | 0x100;

    ಆದರೆ (flags & 1)
    {
      mz_uint s0, s1, n0, n1, sym, ಅಂಕೆ_extra_ಬಿಟ್ಟುಗಳು;
      mz_uint ಹೊಂದಿಕೆ_len = pLZ_codes[0], ಹೊಂದಿಕೆ_dist = *(ಸ್ಥಿರಾಂಕ mz_uint16 *)(pLZ_codes + 1); pLZ_codes += 3;

      MZ_ASSERT(d->m_huff_ಸಂಕೇತ_sizes[0][s_tdefl_len_sym[ಹೊಂದಿಕೆ_len]]);
      TDEFL_PUT_ಬಿಟ್ಟುಗಳು_FAST(d->m_huff_codes[0][s_tdefl_len_sym[ಹೊಂದಿಕೆ_len]], d->m_huff_ಸಂಕೇತ_sizes[0][s_tdefl_len_sym[ಹೊಂದಿಕೆ_len]]);
      TDEFL_PUT_ಬಿಟ್ಟುಗಳು_FAST(ಹೊಂದಿಕೆ_len & mz_bitmasks[s_tdefl_len_extra[ಹೊಂದಿಕೆ_len]], s_tdefl_len_extra[ಹೊಂದಿಕೆ_len]);

      // This sequence coaxes MSVC into using cmov's vs. jmp's.
      s0 = s_tdefl_small_dist_sym[ಹೊಂದಿಕೆ_dist & 511];
      n0 = s_tdefl_small_dist_extra[ಹೊಂದಿಕೆ_dist & 511];
      s1 = s_tdefl_large_dist_sym[ಹೊಂದಿಕೆ_dist >> 8];
      n1 = s_tdefl_large_dist_extra[ಹೊಂದಿಕೆ_dist >> 8];
      sym = (ಹೊಂದಿಕೆ_dist < 512) ? s0 : s1;
      ಅಂಕೆ_extra_ಬಿಟ್ಟುಗಳು = (ಹೊಂದಿಕೆ_dist < 512) ? n0 : n1;

      MZ_ASSERT(d->m_huff_ಸಂಕೇತ_sizes[1][sym]);
      TDEFL_PUT_ಬಿಟ್ಟುಗಳು_FAST(d->m_huff_codes[1][sym], d->m_huff_ಸಂಕೇತ_sizes[1][sym]);
      TDEFL_PUT_ಬಿಟ್ಟುಗಳು_FAST(ಹೊಂದಿಕೆ_dist & mz_bitmasks[ಅಂಕೆ_extra_ಬಿಟ್ಟುಗಳು], ಅಂಕೆ_extra_ಬಿಟ್ಟುಗಳು);
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
      mz_uint lit = *pLZ_codes++;
      MZ_ASSERT(d->m_huff_ಸಂಕೇತ_sizes[0][lit]);
      TDEFL_PUT_ಬಿಟ್ಟುಗಳು_FAST(d->m_huff_codes[0][lit], d->m_huff_ಸಂಕೇತ_sizes[0][lit]);

      ಆದರೆ (((flags & 2) == 0) && (pLZ_codes < p_LZ_ಸಂಕೇತ_buf_ಕೊನೆ))
      {
        flags >>= 1;
        lit = *pLZ_codes++;
        MZ_ASSERT(d->m_huff_ಸಂಕೇತ_sizes[0][lit]);
        TDEFL_PUT_ಬಿಟ್ಟುಗಳು_FAST(d->m_huff_codes[0][lit], d->m_huff_ಸಂಕೇತ_sizes[0][lit]);

        ಆದರೆ (((flags & 2) == 0) && (pLZ_codes < p_LZ_ಸಂಕೇತ_buf_ಕೊನೆ))
        {
          flags >>= 1;
          lit = *pLZ_codes++;
          MZ_ASSERT(d->m_huff_ಸಂಕೇತ_sizes[0][lit]);
          TDEFL_PUT_ಬಿಟ್ಟುಗಳು_FAST(d->m_huff_codes[0][lit], d->m_huff_ಸಂಕೇತ_sizes[0][lit]);
        }
      }
    }

    ಆದರೆ (pOutput_buf >= d->m_p_Output_buf_ಕೊನೆ)
      ಹಿಂತಿರುಗಿ MZ_FALSE;

    *(mz_uint64*)pOutput_buf = ಬಿಟ್_ಬಫರ್;
    pOutput_buf += (ಬಿಟ್ಟುಗಳು_ಒಳ >> 3);
    ಬಿಟ್_ಬಫರ್ >>= (ಬಿಟ್ಟುಗಳು_ಒಳ & ~7);
    ಬಿಟ್ಟುಗಳು_ಒಳ &= 7;
  }

#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು TDEFL_PUT_ಬಿಟ್ಟುಗಳು_FAST

  d->m_pOutput_buf = pOutput_buf;
  d->m_ಬಿಟ್ಟುಗಳು_ಒಳ = 0;
  d->m_ಬಿಟ್_ಬಫರ್ = 0;

  ಆಗ (ಬಿಟ್ಟುಗಳು_ಒಳ)
  {
    mz_uint32 n = MZ_MIN(ಬಿಟ್ಟುಗಳು_ಒಳ, 16);
    TDEFL_PUT_ಬಿಟ್ಟುಗಳು((mz_uint)ಬಿಟ್_ಬಫರ್ & mz_bitmasks[n], n);
    ಬಿಟ್_ಬಫರ್ >>= n;
    ಬಿಟ್ಟುಗಳು_ಒಳ -= n;
  }

  TDEFL_PUT_ಬಿಟ್ಟುಗಳು(d->m_huff_codes[0][256], d->m_huff_ಸಂಕೇತ_sizes[0][256]);

  ಹಿಂತಿರುಗಿ (d->m_pOutput_buf < d->m_p_Output_buf_ಕೊನೆ);
}
#ಇಲ್ಲದಿದ್ದರೆ
ಸ್ಥಿರ mz_bool tdefl_compress_lz_codes(tdefl_compressor *d)
{
  mz_uint flags;
  mz_uint8 *pLZ_codes;

  flags = 1;
  ಗಾಗಿ (pLZ_codes = d->m_lz_ಸಂಕೇತ_buf; pLZ_codes < d->m_p_LZ_ಸಂಕೇತ_buf; flags >>= 1)
  {
    ಆದರೆ (flags == 1)
      flags = *pLZ_codes++ | 0x100;
    ಆದರೆ (flags & 1)
    {
      mz_uint sym, ಅಂಕೆ_extra_ಬಿಟ್ಟುಗಳು;
      mz_uint ಹೊಂದಿಕೆ_len = pLZ_codes[0], ಹೊಂದಿಕೆ_dist = (pLZ_codes[1] | (pLZ_codes[2] << 8)); pLZ_codes += 3;

      MZ_ASSERT(d->m_huff_ಸಂಕೇತ_sizes[0][s_tdefl_len_sym[ಹೊಂದಿಕೆ_len]]);
      TDEFL_PUT_ಬಿಟ್ಟುಗಳು(d->m_huff_codes[0][s_tdefl_len_sym[ಹೊಂದಿಕೆ_len]], d->m_huff_ಸಂಕೇತ_sizes[0][s_tdefl_len_sym[ಹೊಂದಿಕೆ_len]]);
      TDEFL_PUT_ಬಿಟ್ಟುಗಳು(ಹೊಂದಿಕೆ_len & mz_bitmasks[s_tdefl_len_extra[ಹೊಂದಿಕೆ_len]], s_tdefl_len_extra[ಹೊಂದಿಕೆ_len]);

      ಆದರೆ (ಹೊಂದಿಕೆ_dist < 512)
      {
        sym = s_tdefl_small_dist_sym[ಹೊಂದಿಕೆ_dist]; ಅಂಕೆ_extra_ಬಿಟ್ಟುಗಳು = s_tdefl_small_dist_extra[ಹೊಂದಿಕೆ_dist];
      }
      ಇಲ್ಲದಿದ್ದರೆ
      {
        sym = s_tdefl_large_dist_sym[ಹೊಂದಿಕೆ_dist >> 8]; ಅಂಕೆ_extra_ಬಿಟ್ಟುಗಳು = s_tdefl_large_dist_extra[ಹೊಂದಿಕೆ_dist >> 8];
      }
      MZ_ASSERT(d->m_huff_ಸಂಕೇತ_sizes[1][sym]);
      TDEFL_PUT_ಬಿಟ್ಟುಗಳು(d->m_huff_codes[1][sym], d->m_huff_ಸಂಕೇತ_sizes[1][sym]);
      TDEFL_PUT_ಬಿಟ್ಟುಗಳು(ಹೊಂದಿಕೆ_dist & mz_bitmasks[ಅಂಕೆ_extra_ಬಿಟ್ಟುಗಳು], ಅಂಕೆ_extra_ಬಿಟ್ಟುಗಳು);
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
      mz_uint lit = *pLZ_codes++;
      MZ_ASSERT(d->m_huff_ಸಂಕೇತ_sizes[0][lit]);
      TDEFL_PUT_ಬಿಟ್ಟುಗಳು(d->m_huff_codes[0][lit], d->m_huff_ಸಂಕೇತ_sizes[0][lit]);
    }
  }

  TDEFL_PUT_ಬಿಟ್ಟುಗಳು(d->m_huff_codes[0][256], d->m_huff_ಸಂಕೇತ_sizes[0][256]);

  ಹಿಂತಿರುಗಿ (d->m_pOutput_buf < d->m_p_Output_buf_ಕೊನೆ);
}
#ಆದರೆ_ಅಂತ್ಯ // MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN && MINIZ_HAS_64BIT_REGISTERS

ಸ್ಥಿರ mz_bool tdefl_compress_ಖಂಡ(tdefl_compressor *d, mz_bool static_ಖಂಡ)
{
  ಆದರೆ (static_ಖಂಡ)
    tdefl_ಆರಂಭ_static_ಖಂಡ(d);
  ಇಲ್ಲದಿದ್ದರೆ
    tdefl_ಆರಂಭ_dynamic_ಖಂಡ(d);
  ಹಿಂತಿರುಗಿ tdefl_compress_lz_codes(d);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ tdefl_flush_ಖಂಡ(tdefl_compressor *d, ಪೂರ್ಣಾಂಕ flush)
{
  mz_uint saved_ಬಿಟ್_buf, saved_ಬಿಟ್ಟುಗಳು_ಒಳ;
  mz_uint8 *pSaved_output_buf;
  mz_bool comp_ಖಂಡ_succeeded = MZ_FALSE;
  ಪೂರ್ಣಾಂಕ n, use_raw_ಖಂಡ = ((d->m_flags & TDEFL_FORCE_ALL_RAW_ಖಂಡಗಳು) != 0) && (d->m_lookahead_pos - d->m_lz_ಸಂಕೇತ_buf_dict_pos) <= d->m_dict_ಗಾತ್ರ;
  mz_uint8 *p_Output_buf_ಆರಂಭ = ((d->m_pPut_buf_func == ಖಾಲಿ) && ((*d->m_p_ಹೊರಹೋಗು_buf_ಗಾತ್ರ - d->m_ಹೊರಹೋಗು_buf_ofs) >= TDEFL_ಹೊರಹೋಗು_BUF_ಗಾತ್ರ)) ? ((mz_uint8 *)d->m_p_ಹೊರಹೋಗು_buf + d->m_ಹೊರಹೋಗು_buf_ofs) : d->m_output_buf;

  d->m_pOutput_buf = p_Output_buf_ಆರಂಭ;
  d->m_p_Output_buf_ಕೊನೆ = d->m_pOutput_buf + TDEFL_ಹೊರಹೋಗು_BUF_ಗಾತ್ರ - 16;

  MZ_ASSERT(!d->m_output_flush_ಉಳಿದ);
  d->m_output_flush_ofs = 0;
  d->m_output_flush_ಉಳಿದ = 0;

  *d->m_pLZ_flags = (mz_uint8)(*d->m_pLZ_flags >> d->m_ಅಂಕೆ_flags_ಎಡ);
  d->m_p_LZ_ಸಂಕೇತ_buf -= (d->m_ಅಂಕೆ_flags_ಎಡ == 8);

  ಆದರೆ ((d->m_flags & TDEFL_WRITE_ZLIB_ಶೀರ್ಷಿಕೆ) && (!d->m_ಖಂಡ_ಸೂಚ್ಯಂಕ))
  {
    TDEFL_PUT_ಬಿಟ್ಟುಗಳು(0x78, 8); TDEFL_PUT_ಬಿಟ್ಟುಗಳು(0x01, 8);
  }

  TDEFL_PUT_ಬಿಟ್ಟುಗಳು(flush == TDEFL_ಮುಕ್ತಾಯ, 1);

  pSaved_output_buf = d->m_pOutput_buf; saved_ಬಿಟ್_buf = d->m_ಬಿಟ್_ಬಫರ್; saved_ಬಿಟ್ಟುಗಳು_ಒಳ = d->m_ಬಿಟ್ಟುಗಳು_ಒಳ;

  ಆದರೆ (!use_raw_ಖಂಡ)
    comp_ಖಂಡ_succeeded = tdefl_compress_ಖಂಡ(d, (d->m_flags & TDEFL_FORCE_ALL_STATIC_ಖಂಡಗಳು) || (d->m_ಒಟ್ಟು_lz_ಬೈಟುಗಳು < 48));

  // If the block gets expanded, forget the current contents of the output buffer and send a raw block instead.
  ಆದರೆ ( ((use_raw_ಖಂಡ) || ((d->m_ಒಟ್ಟು_lz_ಬೈಟುಗಳು) && ((d->m_pOutput_buf - pSaved_output_buf + 1U) >= d->m_ಒಟ್ಟು_lz_ಬೈಟುಗಳು))) &&
       ((d->m_lookahead_pos - d->m_lz_ಸಂಕೇತ_buf_dict_pos) <= d->m_dict_ಗಾತ್ರ) )
  {
    mz_uint i; d->m_pOutput_buf = pSaved_output_buf; d->m_ಬಿಟ್_ಬಫರ್ = saved_ಬಿಟ್_buf; d->m_ಬಿಟ್ಟುಗಳು_ಒಳ = saved_ಬಿಟ್ಟುಗಳು_ಒಳ;
    TDEFL_PUT_ಬಿಟ್ಟುಗಳು(0, 2);
    ಆದರೆ (d->m_ಬಿಟ್ಟುಗಳು_ಒಳ) { TDEFL_PUT_ಬಿಟ್ಟುಗಳು(0, 8 - d->m_ಬಿಟ್ಟುಗಳು_ಒಳ); }
    ಗಾಗಿ (i = 2; i; --i, d->m_ಒಟ್ಟು_lz_ಬೈಟುಗಳು ^= 0xFFFF)
    {
      TDEFL_PUT_ಬಿಟ್ಟುಗಳು(d->m_ಒಟ್ಟು_lz_ಬೈಟುಗಳು & 0xFFFF, 16);
    }
    ಗಾಗಿ (i = 0; i < d->m_ಒಟ್ಟು_lz_ಬೈಟುಗಳು; ++i)
    {
      TDEFL_PUT_ಬಿಟ್ಟುಗಳು(d->m_dict[(d->m_lz_ಸಂಕೇತ_buf_dict_pos + i) & TDEFL_LZ_DICT_ಗಾತ್ರ_ಮುಖವಾಡ], 8);
    }
  }
  // Check for the extremely unlikely (if not impossible) case of the compressed block not fitting into the output buffer when using dynamic codes.
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!comp_ಖಂಡ_succeeded)
  {
    d->m_pOutput_buf = pSaved_output_buf; d->m_ಬಿಟ್_ಬಫರ್ = saved_ಬಿಟ್_buf; d->m_ಬಿಟ್ಟುಗಳು_ಒಳ = saved_ಬಿಟ್ಟುಗಳು_ಒಳ;
    tdefl_compress_ಖಂಡ(d, MZ_TRUE);
  }

  ಆದರೆ (flush)
  {
    ಆದರೆ (flush == TDEFL_ಮುಕ್ತಾಯ)
    {
      ಆದರೆ (d->m_ಬಿಟ್ಟುಗಳು_ಒಳ) { TDEFL_PUT_ಬಿಟ್ಟುಗಳು(0, 8 - d->m_ಬಿಟ್ಟುಗಳು_ಒಳ); }
      ಆದರೆ (d->m_flags & TDEFL_WRITE_ZLIB_ಶೀರ್ಷಿಕೆ) { mz_uint i, a = d->m_adler32; ಗಾಗಿ (i = 0; i < 4; i++) { TDEFL_PUT_ಬಿಟ್ಟುಗಳು((a >> 24) & 0xFF, 8); a <<= 8; } }
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
      mz_uint i, z = 0; TDEFL_PUT_ಬಿಟ್ಟುಗಳು(0, 3); ಆದರೆ (d->m_ಬಿಟ್ಟುಗಳು_ಒಳ) { TDEFL_PUT_ಬಿಟ್ಟುಗಳು(0, 8 - d->m_ಬಿಟ್ಟುಗಳು_ಒಳ); } ಗಾಗಿ (i = 2; i; --i, z ^= 0xFFFF) { TDEFL_PUT_ಬಿಟ್ಟುಗಳು(z & 0xFFFF, 16); }
    }
  }

  MZ_ASSERT(d->m_pOutput_buf < d->m_p_Output_buf_ಕೊನೆ);

  memset(&d->m_huff_ಎಣಿಕೆ[0][0], 0, ಗಾತ್ರ(d->m_huff_ಎಣಿಕೆ[0][0]) * TDEFL_MAX_HUFF_SYMBOLS_0);
  memset(&d->m_huff_ಎಣಿಕೆ[1][0], 0, ಗಾತ್ರ(d->m_huff_ಎಣಿಕೆ[1][0]) * TDEFL_MAX_HUFF_SYMBOLS_1);

  d->m_p_LZ_ಸಂಕೇತ_buf = d->m_lz_ಸಂಕೇತ_buf + 1; d->m_pLZ_flags = d->m_lz_ಸಂಕೇತ_buf; d->m_ಅಂಕೆ_flags_ಎಡ = 8; d->m_lz_ಸಂಕೇತ_buf_dict_pos += d->m_ಒಟ್ಟು_lz_ಬೈಟುಗಳು; d->m_ಒಟ್ಟು_lz_ಬೈಟುಗಳು = 0; d->m_ಖಂಡ_ಸೂಚ್ಯಂಕ++;

  ಆದರೆ ((n = (ಪೂರ್ಣಾಂಕ)(d->m_pOutput_buf - p_Output_buf_ಆರಂಭ)) != 0)
  {
    ಆದರೆ (d->m_pPut_buf_func)
    {
      *d->m_p_ಒಳ_buf_ಗಾತ್ರ = d->m_pSrc - (ಸ್ಥಿರಾಂಕ mz_uint8 *)d->m_p_ಒಳ_buf;
      ಆದರೆ (!(*d->m_pPut_buf_func)(d->m_output_buf, n, d->m_pPut_buf_user))
        ಹಿಂತಿರುಗಿ (d->m_prev_return_ಸ್ಥಿತಿ = TDEFL_ಸ್ಥಿತಿ_PUT_BUF_FAILED);
    }
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (p_Output_buf_ಆರಂಭ == d->m_output_buf)
    {
      ಪೂರ್ಣಾಂಕ ಬೈಟುಗಳು_ಗಮ್ಯ_copy = (ಪೂರ್ಣಾಂಕ)MZ_MIN((size_t)n, (size_t)(*d->m_p_ಹೊರಹೋಗು_buf_ಗಾತ್ರ - d->m_ಹೊರಹೋಗು_buf_ofs));
      ಸ್ಮರಣೆ_ನಕಲು((mz_uint8 *)d->m_p_ಹೊರಹೋಗು_buf + d->m_ಹೊರಹೋಗು_buf_ofs, d->m_output_buf, ಬೈಟುಗಳು_ಗಮ್ಯ_copy);
      d->m_ಹೊರಹೋಗು_buf_ofs += ಬೈಟುಗಳು_ಗಮ್ಯ_copy;
      ಆದರೆ ((n -= ಬೈಟುಗಳು_ಗಮ್ಯ_copy) != 0)
      {
        d->m_output_flush_ofs = ಬೈಟುಗಳು_ಗಮ್ಯ_copy;
        d->m_output_flush_ಉಳಿದ = n;
      }
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
      d->m_ಹೊರಹೋಗು_buf_ofs += n;
    }
  }

  ಹಿಂತಿರುಗಿ d->m_output_flush_ಉಳಿದ;
}

#ಆದರೆ MINIZ_USE_UNALIGNED_LOADS_AND_STORES
#ವ್ಯಾಖ್ಯಾನಿಸು TDEFL_READ_UNALIGNED_ಶಬ್ದ(p) *(ಸ್ಥಿರಾಂಕ mz_uint16*)(p)
ಸ್ಥಿರ MZ_FORCEINLINE ಶೂನ್ಯ tdefl_ಕಂಡುಹಿಡಿ_ಹೊಂದಿಕೆ(tdefl_compressor *d, mz_uint lookahead_pos, mz_uint max_dist, mz_uint max_ಹೊಂದಿಕೆ_len, mz_uint *p_ಹೊಂದಿಕೆ_dist, mz_uint *p_ಹೊಂದಿಕೆ_len)
{
  mz_uint dist, pos = lookahead_pos & TDEFL_LZ_DICT_ಗಾತ್ರ_ಮುಖವಾಡ, ಹೊಂದಿಕೆ_len = *p_ಹೊಂದಿಕೆ_len, probe_pos = pos, ಮುಂದಿನ_probe_pos, probe_len;
  mz_uint ಅಂಕೆ_probes_ಎಡ = d->m_max_probes[ಹೊಂದಿಕೆ_len >= 32];
  ಸ್ಥಿರಾಂಕ mz_uint16 *s = (ಸ್ಥಿರಾಂಕ mz_uint16*)(d->m_dict + pos), *p, *q;
  mz_uint16 c01 = TDEFL_READ_UNALIGNED_ಶಬ್ದ(&d->m_dict[pos + ಹೊಂದಿಕೆ_len - 1]), s01 = TDEFL_READ_UNALIGNED_ಶಬ್ದ(s);
  MZ_ASSERT(max_ಹೊಂದಿಕೆ_len <= TDEFL_MAX_ಹೊಂದಿಕೆ_LEN); ಆದರೆ (max_ಹೊಂದಿಕೆ_len <= ಹೊಂದಿಕೆ_len) ಹಿಂತಿರುಗಿ;
  ಗಾಗಿ ( ; ; )
  {
    ಗಾಗಿ ( ; ; )
    {
      ಆದರೆ (--ಅಂಕೆ_probes_ಎಡ == 0) ಹಿಂತಿರುಗಿ;
      #ವ್ಯಾಖ್ಯಾನಿಸು TDEFL_PROBE \
        ಮುಂದಿನ_probe_pos = d->m_ಮುಂದಿನ[probe_pos]; \
        ಆದರೆ ((!ಮುಂದಿನ_probe_pos) || ((dist = (mz_uint16)(lookahead_pos - ಮುಂದಿನ_probe_pos)) > max_dist)) ಹಿಂತಿರುಗಿ; \
        probe_pos = ಮುಂದಿನ_probe_pos & TDEFL_LZ_DICT_ಗಾತ್ರ_ಮುಖವಾಡ; \
        ಆದರೆ (TDEFL_READ_UNALIGNED_ಶಬ್ದ(&d->m_dict[probe_pos + ಹೊಂದಿಕೆ_len - 1]) == c01) ನಿಲ್ಲಿಸು;
      TDEFL_PROBE
      TDEFL_PROBE
      TDEFL_PROBE
    }
    ಆದರೆ (!dist) ನಿಲ್ಲಿಸು;
    q = (ಸ್ಥಿರಾಂಕ mz_uint16*)(d->m_dict + probe_pos);
    ಆದರೆ (TDEFL_READ_UNALIGNED_ಶಬ್ದ(q) != s01) ಮುಂದುವರಿ;
    p = s; probe_len = 32;
    ಮಾಡು { } ಆಗ ( (TDEFL_READ_UNALIGNED_ಶಬ್ದ(++p) == TDEFL_READ_UNALIGNED_ಶಬ್ದ(++q)) && (TDEFL_READ_UNALIGNED_ಶಬ್ದ(++p) == TDEFL_READ_UNALIGNED_ಶಬ್ದ(++q)) &&
                   (TDEFL_READ_UNALIGNED_ಶಬ್ದ(++p) == TDEFL_READ_UNALIGNED_ಶಬ್ದ(++q)) && (TDEFL_READ_UNALIGNED_ಶಬ್ದ(++p) == TDEFL_READ_UNALIGNED_ಶಬ್ದ(++q)) && (--probe_len > 0) );
    ಆದರೆ (!probe_len)
    {
      *p_ಹೊಂದಿಕೆ_dist = dist; *p_ಹೊಂದಿಕೆ_len = MZ_MIN(max_ಹೊಂದಿಕೆ_len, TDEFL_MAX_ಹೊಂದಿಕೆ_LEN); ನಿಲ್ಲಿಸು;
    }
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((probe_len = ((mz_uint)(p - s) * 2) + (mz_uint)(*(ಸ್ಥಿರಾಂಕ mz_uint8*)p == *(ಸ್ಥಿರಾಂಕ mz_uint8*)q)) > ಹೊಂದಿಕೆ_len)
    {
      *p_ಹೊಂದಿಕೆ_dist = dist; ಆದರೆ ((*p_ಹೊಂದಿಕೆ_len = ಹೊಂದಿಕೆ_len = MZ_MIN(max_ಹೊಂದಿಕೆ_len, probe_len)) == max_ಹೊಂದಿಕೆ_len) ನಿಲ್ಲಿಸು;
      c01 = TDEFL_READ_UNALIGNED_ಶಬ್ದ(&d->m_dict[pos + ಹೊಂದಿಕೆ_len - 1]);
    }
  }
}
#ಇಲ್ಲದಿದ್ದರೆ
ಸ್ಥಿರ MZ_FORCEINLINE ಶೂನ್ಯ tdefl_ಕಂಡುಹಿಡಿ_ಹೊಂದಿಕೆ(tdefl_compressor *d, mz_uint lookahead_pos, mz_uint max_dist, mz_uint max_ಹೊಂದಿಕೆ_len, mz_uint *p_ಹೊಂದಿಕೆ_dist, mz_uint *p_ಹೊಂದಿಕೆ_len)
{
  mz_uint dist, pos = lookahead_pos & TDEFL_LZ_DICT_ಗಾತ್ರ_ಮುಖವಾಡ, ಹೊಂದಿಕೆ_len = *p_ಹೊಂದಿಕೆ_len, probe_pos = pos, ಮುಂದಿನ_probe_pos, probe_len;
  mz_uint ಅಂಕೆ_probes_ಎಡ = d->m_max_probes[ಹೊಂದಿಕೆ_len >= 32];
  ಸ್ಥಿರಾಂಕ mz_uint8 *s = d->m_dict + pos, *p, *q;
  mz_uint8 c0 = d->m_dict[pos + ಹೊಂದಿಕೆ_len], c1 = d->m_dict[pos + ಹೊಂದಿಕೆ_len - 1];
  MZ_ASSERT(max_ಹೊಂದಿಕೆ_len <= TDEFL_MAX_ಹೊಂದಿಕೆ_LEN); ಆದರೆ (max_ಹೊಂದಿಕೆ_len <= ಹೊಂದಿಕೆ_len) ಹಿಂತಿರುಗಿ;
  ಗಾಗಿ ( ; ; )
  {
    ಗಾಗಿ ( ; ; )
    {
      ಆದರೆ (--ಅಂಕೆ_probes_ಎಡ == 0) ಹಿಂತಿರುಗಿ;
      #ವ್ಯಾಖ್ಯಾನಿಸು TDEFL_PROBE \
        ಮುಂದಿನ_probe_pos = d->m_ಮುಂದಿನ[probe_pos]; \
        ಆದರೆ ((!ಮುಂದಿನ_probe_pos) || ((dist = (mz_uint16)(lookahead_pos - ಮುಂದಿನ_probe_pos)) > max_dist)) ಹಿಂತಿರುಗಿ; \
        probe_pos = ಮುಂದಿನ_probe_pos & TDEFL_LZ_DICT_ಗಾತ್ರ_ಮುಖವಾಡ; \
        ಆದರೆ ((d->m_dict[probe_pos + ಹೊಂದಿಕೆ_len] == c0) && (d->m_dict[probe_pos + ಹೊಂದಿಕೆ_len - 1] == c1)) ನಿಲ್ಲಿಸು;
      TDEFL_PROBE
      TDEFL_PROBE
      TDEFL_PROBE
    }
    ಆದರೆ (!dist) ನಿಲ್ಲಿಸು;
    p = s; q = d->m_dict + probe_pos;
    ಗಾಗಿ (probe_len = 0; probe_len < max_ಹೊಂದಿಕೆ_len; probe_len++) {
        ಆದರೆ (*p++ != *q++) ನಿಲ್ಲಿಸು;
    }
    ಆದರೆ (probe_len > ಹೊಂದಿಕೆ_len)
    {
      *p_ಹೊಂದಿಕೆ_dist = dist;
      ಆದರೆ ((*p_ಹೊಂದಿಕೆ_len = ಹೊಂದಿಕೆ_len = probe_len) == max_ಹೊಂದಿಕೆ_len) ಹಿಂತಿರುಗಿ;
      c0 = d->m_dict[pos + ಹೊಂದಿಕೆ_len]; c1 = d->m_dict[pos + ಹೊಂದಿಕೆ_len - 1];
    }
  }
}
#ಆದರೆ_ಅಂತ್ಯ // #if MINIZ_USE_UNALIGNED_LOADS_AND_STORES

#ಆದರೆ MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
ಸ್ಥಿರ mz_bool tdefl_compress_fast(tdefl_compressor *d)
{
  // Faster, minimally featured LZRW1-style match+parse loop with better register utilization. Intended for applications where raw throughput is valued more highly than ratio.
  mz_uint lookahead_pos = d->m_lookahead_pos, lookahead_ಗಾತ್ರ = d->m_lookahead_ಗಾತ್ರ, dict_ಗಾತ್ರ = d->m_dict_ಗಾತ್ರ, ಒಟ್ಟು_lz_ಬೈಟುಗಳು = d->m_ಒಟ್ಟು_lz_ಬೈಟುಗಳು, ಅಂಕೆ_flags_ಎಡ = d->m_ಅಂಕೆ_flags_ಎಡ;
  mz_uint8 *p_LZ_ಸಂಕೇತ_buf = d->m_p_LZ_ಸಂಕೇತ_buf, *pLZ_flags = d->m_pLZ_flags;
  mz_uint cur_pos = lookahead_pos & TDEFL_LZ_DICT_ಗಾತ್ರ_ಮುಖವಾಡ;

  ಆಗ ((d->m_src_buf_ಎಡ) || ((d->m_flush) && (lookahead_ಗಾತ್ರ)))
  {
    ಸ್ಥಿರಾಂಕ mz_uint TDEFL_COMP_FAST_LOOKAHEAD_ಗಾತ್ರ = 4096;
    mz_uint dst_pos = (lookahead_pos + lookahead_ಗಾತ್ರ) & TDEFL_LZ_DICT_ಗಾತ್ರ_ಮುಖವಾಡ;
    mz_uint ಅಂಕೆ_ಬೈಟುಗಳು_ಗಮ್ಯ_process = (mz_uint)MZ_MIN(d->m_src_buf_ಎಡ, TDEFL_COMP_FAST_LOOKAHEAD_ಗಾತ್ರ - lookahead_ಗಾತ್ರ);
    d->m_src_buf_ಎಡ -= ಅಂಕೆ_ಬೈಟುಗಳು_ಗಮ್ಯ_process;
    lookahead_ಗಾತ್ರ += ಅಂಕೆ_ಬೈಟುಗಳು_ಗಮ್ಯ_process;

    ಆಗ (ಅಂಕೆ_ಬೈಟುಗಳು_ಗಮ್ಯ_process)
    {
      mz_uint32 n = MZ_MIN(TDEFL_LZ_DICT_ಗಾತ್ರ - dst_pos, ಅಂಕೆ_ಬೈಟುಗಳು_ಗಮ್ಯ_process);
      ಸ್ಮರಣೆ_ನಕಲು(d->m_dict + dst_pos, d->m_pSrc, n);
      ಆದರೆ (dst_pos < (TDEFL_MAX_ಹೊಂದಿಕೆ_LEN - 1))
        ಸ್ಮರಣೆ_ನಕಲು(d->m_dict + TDEFL_LZ_DICT_ಗಾತ್ರ + dst_pos, d->m_pSrc, MZ_MIN(n, (TDEFL_MAX_ಹೊಂದಿಕೆ_LEN - 1) - dst_pos));
      d->m_pSrc += n;
      dst_pos = (dst_pos + n) & TDEFL_LZ_DICT_ಗಾತ್ರ_ಮುಖವಾಡ;
      ಅಂಕೆ_ಬೈಟುಗಳು_ಗಮ್ಯ_process -= n;
    }

    dict_ಗಾತ್ರ = MZ_MIN(TDEFL_LZ_DICT_ಗಾತ್ರ - lookahead_ಗಾತ್ರ, dict_ಗಾತ್ರ);
    ಆದರೆ ((!d->m_flush) && (lookahead_ಗಾತ್ರ < TDEFL_COMP_FAST_LOOKAHEAD_ಗಾತ್ರ)) ನಿಲ್ಲಿಸು;

    ಆಗ (lookahead_ಗಾತ್ರ >= 4)
    {
      mz_uint cur_ಹೊಂದಿಕೆ_dist, cur_ಹೊಂದಿಕೆ_len = 1;
      mz_uint8 *pCur_dict = d->m_dict + cur_pos;
      mz_uint ಮೊದಲ_trigram = (*(ಸ್ಥಿರಾಂಕ mz_uint32 *)pCur_dict) & 0xFFFFFF;
      mz_uint hash = (ಮೊದಲ_trigram ^ (ಮೊದಲ_trigram >> (24 - (TDEFL_LZ_HASH_ಬಿಟ್ಟುಗಳು - 8)))) & TDEFL_LEVEL1_HASH_ಗಾತ್ರ_ಮುಖವಾಡ;
      mz_uint probe_pos = d->m_hash[hash];
      d->m_hash[hash] = (mz_uint16)lookahead_pos;

      ಆದರೆ (((cur_ಹೊಂದಿಕೆ_dist = (mz_uint16)(lookahead_pos - probe_pos)) <= dict_ಗಾತ್ರ) && ((*(ಸ್ಥಿರಾಂಕ mz_uint32 *)(d->m_dict + (probe_pos &= TDEFL_LZ_DICT_ಗಾತ್ರ_ಮುಖವಾಡ)) & 0xFFFFFF) == ಮೊದಲ_trigram))
      {
        ಸ್ಥಿರಾಂಕ mz_uint16 *p = (ಸ್ಥಿರಾಂಕ mz_uint16 *)pCur_dict;
        ಸ್ಥಿರಾಂಕ mz_uint16 *q = (ಸ್ಥಿರಾಂಕ mz_uint16 *)(d->m_dict + probe_pos);
        mz_uint32 probe_len = 32;
        ಮಾಡು { } ಆಗ ( (TDEFL_READ_UNALIGNED_ಶಬ್ದ(++p) == TDEFL_READ_UNALIGNED_ಶಬ್ದ(++q)) && (TDEFL_READ_UNALIGNED_ಶಬ್ದ(++p) == TDEFL_READ_UNALIGNED_ಶಬ್ದ(++q)) &&
          (TDEFL_READ_UNALIGNED_ಶಬ್ದ(++p) == TDEFL_READ_UNALIGNED_ಶಬ್ದ(++q)) && (TDEFL_READ_UNALIGNED_ಶಬ್ದ(++p) == TDEFL_READ_UNALIGNED_ಶಬ್ದ(++q)) && (--probe_len > 0) );
        cur_ಹೊಂದಿಕೆ_len = ((mz_uint)(p - (ಸ್ಥಿರಾಂಕ mz_uint16 *)pCur_dict) * 2) + (mz_uint)(*(ಸ್ಥಿರಾಂಕ mz_uint8 *)p == *(ಸ್ಥಿರಾಂಕ mz_uint8 *)q);
        ಆದರೆ (!probe_len)
          cur_ಹೊಂದಿಕೆ_len = cur_ಹೊಂದಿಕೆ_dist ? TDEFL_MAX_ಹೊಂದಿಕೆ_LEN : 0;

        ಆದರೆ ((cur_ಹೊಂದಿಕೆ_len < TDEFL_MIN_ಹೊಂದಿಕೆ_LEN) || ((cur_ಹೊಂದಿಕೆ_len == TDEFL_MIN_ಹೊಂದಿಕೆ_LEN) && (cur_ಹೊಂದಿಕೆ_dist >= 8U*1024U)))
        {
          cur_ಹೊಂದಿಕೆ_len = 1;
          *p_LZ_ಸಂಕೇತ_buf++ = (mz_uint8)ಮೊದಲ_trigram;
          *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
          d->m_huff_ಎಣಿಕೆ[0][(mz_uint8)ಮೊದಲ_trigram]++;
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
          mz_uint32 s0, s1;
          cur_ಹೊಂದಿಕೆ_len = MZ_MIN(cur_ಹೊಂದಿಕೆ_len, lookahead_ಗಾತ್ರ);

          MZ_ASSERT((cur_ಹೊಂದಿಕೆ_len >= TDEFL_MIN_ಹೊಂದಿಕೆ_LEN) && (cur_ಹೊಂದಿಕೆ_dist >= 1) && (cur_ಹೊಂದಿಕೆ_dist <= TDEFL_LZ_DICT_ಗಾತ್ರ));

          cur_ಹೊಂದಿಕೆ_dist--;

          p_LZ_ಸಂಕೇತ_buf[0] = (mz_uint8)(cur_ಹೊಂದಿಕೆ_len - TDEFL_MIN_ಹೊಂದಿಕೆ_LEN);
          *(mz_uint16 *)(&p_LZ_ಸಂಕೇತ_buf[1]) = (mz_uint16)cur_ಹೊಂದಿಕೆ_dist;
          p_LZ_ಸಂಕೇತ_buf += 3;
          *pLZ_flags = (mz_uint8)((*pLZ_flags >> 1) | 0x80);

          s0 = s_tdefl_small_dist_sym[cur_ಹೊಂದಿಕೆ_dist & 511];
          s1 = s_tdefl_large_dist_sym[cur_ಹೊಂದಿಕೆ_dist >> 8];
          d->m_huff_ಎಣಿಕೆ[1][(cur_ಹೊಂದಿಕೆ_dist < 512) ? s0 : s1]++;

          d->m_huff_ಎಣಿಕೆ[0][s_tdefl_len_sym[cur_ಹೊಂದಿಕೆ_len - TDEFL_MIN_ಹೊಂದಿಕೆ_LEN]]++;
        }
      }
      ಇಲ್ಲದಿದ್ದರೆ
      {
        *p_LZ_ಸಂಕೇತ_buf++ = (mz_uint8)ಮೊದಲ_trigram;
        *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
        d->m_huff_ಎಣಿಕೆ[0][(mz_uint8)ಮೊದಲ_trigram]++;
      }

      ಆದರೆ (--ಅಂಕೆ_flags_ಎಡ == 0) { ಅಂಕೆ_flags_ಎಡ = 8; pLZ_flags = p_LZ_ಸಂಕೇತ_buf++; }

      ಒಟ್ಟು_lz_ಬೈಟುಗಳು += cur_ಹೊಂದಿಕೆ_len;
      lookahead_pos += cur_ಹೊಂದಿಕೆ_len;
      dict_ಗಾತ್ರ = MZ_MIN(dict_ಗಾತ್ರ + cur_ಹೊಂದಿಕೆ_len, TDEFL_LZ_DICT_ಗಾತ್ರ);
      cur_pos = (cur_pos + cur_ಹೊಂದಿಕೆ_len) & TDEFL_LZ_DICT_ಗಾತ್ರ_ಮುಖವಾಡ;
      MZ_ASSERT(lookahead_ಗಾತ್ರ >= cur_ಹೊಂದಿಕೆ_len);
      lookahead_ಗಾತ್ರ -= cur_ಹೊಂದಿಕೆ_len;

      ಆದರೆ (p_LZ_ಸಂಕೇತ_buf > &d->m_lz_ಸಂಕೇತ_buf[TDEFL_LZ_ಸಂಕೇತ_BUF_ಗಾತ್ರ - 8])
      {
        ಪೂರ್ಣಾಂಕ n;
        d->m_lookahead_pos = lookahead_pos; d->m_lookahead_ಗಾತ್ರ = lookahead_ಗಾತ್ರ; d->m_dict_ಗಾತ್ರ = dict_ಗಾತ್ರ;
        d->m_ಒಟ್ಟು_lz_ಬೈಟುಗಳು = ಒಟ್ಟು_lz_ಬೈಟುಗಳು; d->m_p_LZ_ಸಂಕೇತ_buf = p_LZ_ಸಂಕೇತ_buf; d->m_pLZ_flags = pLZ_flags; d->m_ಅಂಕೆ_flags_ಎಡ = ಅಂಕೆ_flags_ಎಡ;
        ಆದರೆ ((n = tdefl_flush_ಖಂಡ(d, 0)) != 0)
          ಹಿಂತಿರುಗಿ (n < 0) ? MZ_FALSE : MZ_TRUE;
        ಒಟ್ಟು_lz_ಬೈಟುಗಳು = d->m_ಒಟ್ಟು_lz_ಬೈಟುಗಳು; p_LZ_ಸಂಕೇತ_buf = d->m_p_LZ_ಸಂಕೇತ_buf; pLZ_flags = d->m_pLZ_flags; ಅಂಕೆ_flags_ಎಡ = d->m_ಅಂಕೆ_flags_ಎಡ;
      }
    }

    ಆಗ (lookahead_ಗಾತ್ರ)
    {
      mz_uint8 lit = d->m_dict[cur_pos];

      ಒಟ್ಟು_lz_ಬೈಟುಗಳು++;
      *p_LZ_ಸಂಕೇತ_buf++ = lit;
      *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
      ಆದರೆ (--ಅಂಕೆ_flags_ಎಡ == 0) { ಅಂಕೆ_flags_ಎಡ = 8; pLZ_flags = p_LZ_ಸಂಕೇತ_buf++; }

      d->m_huff_ಎಣಿಕೆ[0][lit]++;

      lookahead_pos++;
      dict_ಗಾತ್ರ = MZ_MIN(dict_ಗಾತ್ರ + 1, TDEFL_LZ_DICT_ಗಾತ್ರ);
      cur_pos = (cur_pos + 1) & TDEFL_LZ_DICT_ಗಾತ್ರ_ಮುಖವಾಡ;
      lookahead_ಗಾತ್ರ--;

      ಆದರೆ (p_LZ_ಸಂಕೇತ_buf > &d->m_lz_ಸಂಕೇತ_buf[TDEFL_LZ_ಸಂಕೇತ_BUF_ಗಾತ್ರ - 8])
      {
        ಪೂರ್ಣಾಂಕ n;
        d->m_lookahead_pos = lookahead_pos; d->m_lookahead_ಗಾತ್ರ = lookahead_ಗಾತ್ರ; d->m_dict_ಗಾತ್ರ = dict_ಗಾತ್ರ;
        d->m_ಒಟ್ಟು_lz_ಬೈಟುಗಳು = ಒಟ್ಟು_lz_ಬೈಟುಗಳು; d->m_p_LZ_ಸಂಕೇತ_buf = p_LZ_ಸಂಕೇತ_buf; d->m_pLZ_flags = pLZ_flags; d->m_ಅಂಕೆ_flags_ಎಡ = ಅಂಕೆ_flags_ಎಡ;
        ಆದರೆ ((n = tdefl_flush_ಖಂಡ(d, 0)) != 0)
          ಹಿಂತಿರುಗಿ (n < 0) ? MZ_FALSE : MZ_TRUE;
        ಒಟ್ಟು_lz_ಬೈಟುಗಳು = d->m_ಒಟ್ಟು_lz_ಬೈಟುಗಳು; p_LZ_ಸಂಕೇತ_buf = d->m_p_LZ_ಸಂಕೇತ_buf; pLZ_flags = d->m_pLZ_flags; ಅಂಕೆ_flags_ಎಡ = d->m_ಅಂಕೆ_flags_ಎಡ;
      }
    }
  }

  d->m_lookahead_pos = lookahead_pos; d->m_lookahead_ಗಾತ್ರ = lookahead_ಗಾತ್ರ; d->m_dict_ಗಾತ್ರ = dict_ಗಾತ್ರ;
  d->m_ಒಟ್ಟು_lz_ಬೈಟುಗಳು = ಒಟ್ಟು_lz_ಬೈಟುಗಳು; d->m_p_LZ_ಸಂಕೇತ_buf = p_LZ_ಸಂಕೇತ_buf; d->m_pLZ_flags = pLZ_flags; d->m_ಅಂಕೆ_flags_ಎಡ = ಅಂಕೆ_flags_ಎಡ;
  ಹಿಂತಿರುಗಿ MZ_TRUE;
}
#ಆದರೆ_ಅಂತ್ಯ // MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN

ಸ್ಥಿರ MZ_FORCEINLINE ಶೂನ್ಯ tdefl_ದಾಖಲೆ_literal(tdefl_compressor *d, mz_uint8 lit)
{
  d->m_ಒಟ್ಟು_lz_ಬೈಟುಗಳು++;
  *d->m_p_LZ_ಸಂಕೇತ_buf++ = lit;
  *d->m_pLZ_flags = (mz_uint8)(*d->m_pLZ_flags >> 1); ಆದರೆ (--d->m_ಅಂಕೆ_flags_ಎಡ == 0) { d->m_ಅಂಕೆ_flags_ಎಡ = 8; d->m_pLZ_flags = d->m_p_LZ_ಸಂಕೇತ_buf++; }
  d->m_huff_ಎಣಿಕೆ[0][lit]++;
}

ಸ್ಥಿರ MZ_FORCEINLINE ಶೂನ್ಯ tdefl_ದಾಖಲೆ_ಹೊಂದಿಕೆ(tdefl_compressor *d, mz_uint ಹೊಂದಿಕೆ_len, mz_uint ಹೊಂದಿಕೆ_dist)
{
  mz_uint32 s0, s1;

  MZ_ASSERT((ಹೊಂದಿಕೆ_len >= TDEFL_MIN_ಹೊಂದಿಕೆ_LEN) && (ಹೊಂದಿಕೆ_dist >= 1) && (ಹೊಂದಿಕೆ_dist <= TDEFL_LZ_DICT_ಗಾತ್ರ));

  d->m_ಒಟ್ಟು_lz_ಬೈಟುಗಳು += ಹೊಂದಿಕೆ_len;

  d->m_p_LZ_ಸಂಕೇತ_buf[0] = (mz_uint8)(ಹೊಂದಿಕೆ_len - TDEFL_MIN_ಹೊಂದಿಕೆ_LEN);

  ಹೊಂದಿಕೆ_dist -= 1;
  d->m_p_LZ_ಸಂಕೇತ_buf[1] = (mz_uint8)(ಹೊಂದಿಕೆ_dist & 0xFF);
  d->m_p_LZ_ಸಂಕೇತ_buf[2] = (mz_uint8)(ಹೊಂದಿಕೆ_dist >> 8); d->m_p_LZ_ಸಂಕೇತ_buf += 3;

  *d->m_pLZ_flags = (mz_uint8)((*d->m_pLZ_flags >> 1) | 0x80); ಆದರೆ (--d->m_ಅಂಕೆ_flags_ಎಡ == 0) { d->m_ಅಂಕೆ_flags_ಎಡ = 8; d->m_pLZ_flags = d->m_p_LZ_ಸಂಕೇತ_buf++; }

  s0 = s_tdefl_small_dist_sym[ಹೊಂದಿಕೆ_dist & 511]; s1 = s_tdefl_large_dist_sym[(ಹೊಂದಿಕೆ_dist >> 8) & 127];
  d->m_huff_ಎಣಿಕೆ[1][(ಹೊಂದಿಕೆ_dist < 512) ? s0 : s1]++;

  ಆದರೆ (ಹೊಂದಿಕೆ_len >= TDEFL_MIN_ಹೊಂದಿಕೆ_LEN) d->m_huff_ಎಣಿಕೆ[0][s_tdefl_len_sym[ಹೊಂದಿಕೆ_len - TDEFL_MIN_ಹೊಂದಿಕೆ_LEN]]++;
}

ಸ್ಥಿರ mz_bool tdefl_compress_ಸಾಮಾನ್ಯ(tdefl_compressor *d)
{
  ಸ್ಥಿರಾಂಕ mz_uint8 *pSrc = d->m_pSrc; size_t src_buf_ಎಡ = d->m_src_buf_ಎಡ;
  tdefl_flush flush = d->m_flush;

  ಆಗ ((src_buf_ಎಡ) || ((flush) && (d->m_lookahead_ಗಾತ್ರ)))
  {
    mz_uint len_ಗಮ್ಯ_move, cur_ಹೊಂದಿಕೆ_dist, cur_ಹೊಂದಿಕೆ_len, cur_pos;
    // Update dictionary and hash chains. Keeps the lookahead size equal to TDEFL_MAX_MATCH_LEN.
    ಆದರೆ ((d->m_lookahead_ಗಾತ್ರ + d->m_dict_ಗಾತ್ರ) >= (TDEFL_MIN_ಹೊಂದಿಕೆ_LEN - 1))
    {
      mz_uint dst_pos = (d->m_lookahead_pos + d->m_lookahead_ಗಾತ್ರ) & TDEFL_LZ_DICT_ಗಾತ್ರ_ಮುಖವಾಡ, ins_pos = d->m_lookahead_pos + d->m_lookahead_ಗಾತ್ರ - 2;
      mz_uint hash = (d->m_dict[ins_pos & TDEFL_LZ_DICT_ಗಾತ್ರ_ಮುಖವಾಡ] << TDEFL_LZ_HASH_ಸರಿಸು) ^ d->m_dict[(ins_pos + 1) & TDEFL_LZ_DICT_ಗಾತ್ರ_ಮುಖವಾಡ];
      mz_uint ಅಂಕೆ_ಬೈಟುಗಳು_ಗಮ್ಯ_process = (mz_uint)MZ_MIN(src_buf_ಎಡ, TDEFL_MAX_ಹೊಂದಿಕೆ_LEN - d->m_lookahead_ಗಾತ್ರ);
      ಸ್ಥಿರಾಂಕ mz_uint8 *p_Src_ಕೊನೆ = pSrc ? pSrc + ಅಂಕೆ_ಬೈಟುಗಳು_ಗಮ್ಯ_process : ಖಾಲಿ;
      src_buf_ಎಡ -= ಅಂಕೆ_ಬೈಟುಗಳು_ಗಮ್ಯ_process;
      d->m_lookahead_ಗಾತ್ರ += ಅಂಕೆ_ಬೈಟುಗಳು_ಗಮ್ಯ_process;
      ಆಗ (pSrc != p_Src_ಕೊನೆ)
      {
        mz_uint8 c = *pSrc++; d->m_dict[dst_pos] = c; ಆದರೆ (dst_pos < (TDEFL_MAX_ಹೊಂದಿಕೆ_LEN - 1)) d->m_dict[TDEFL_LZ_DICT_ಗಾತ್ರ + dst_pos] = c;
        hash = ((hash << TDEFL_LZ_HASH_ಸರಿಸು) ^ c) & (TDEFL_LZ_HASH_ಗಾತ್ರ - 1);
        d->m_ಮುಂದಿನ[ins_pos & TDEFL_LZ_DICT_ಗಾತ್ರ_ಮುಖವಾಡ] = d->m_hash[hash]; d->m_hash[hash] = (mz_uint16)(ins_pos);
        dst_pos = (dst_pos + 1) & TDEFL_LZ_DICT_ಗಾತ್ರ_ಮುಖವಾಡ; ins_pos++;
      }
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
      ಆಗ ((src_buf_ಎಡ) && (d->m_lookahead_ಗಾತ್ರ < TDEFL_MAX_ಹೊಂದಿಕೆ_LEN))
      {
        mz_uint8 c = *pSrc++;
        mz_uint dst_pos = (d->m_lookahead_pos + d->m_lookahead_ಗಾತ್ರ) & TDEFL_LZ_DICT_ಗಾತ್ರ_ಮುಖವಾಡ;
        src_buf_ಎಡ--;
        d->m_dict[dst_pos] = c;
        ಆದರೆ (dst_pos < (TDEFL_MAX_ಹೊಂದಿಕೆ_LEN - 1))
          d->m_dict[TDEFL_LZ_DICT_ಗಾತ್ರ + dst_pos] = c;
        ಆದರೆ ((++d->m_lookahead_ಗಾತ್ರ + d->m_dict_ಗಾತ್ರ) >= TDEFL_MIN_ಹೊಂದಿಕೆ_LEN)
        {
          mz_uint ins_pos = d->m_lookahead_pos + (d->m_lookahead_ಗಾತ್ರ - 1) - 2;
          mz_uint hash = ((d->m_dict[ins_pos & TDEFL_LZ_DICT_ಗಾತ್ರ_ಮುಖವಾಡ] << (TDEFL_LZ_HASH_ಸರಿಸು * 2)) ^ (d->m_dict[(ins_pos + 1) & TDEFL_LZ_DICT_ಗಾತ್ರ_ಮುಖವಾಡ] << TDEFL_LZ_HASH_ಸರಿಸು) ^ c) & (TDEFL_LZ_HASH_ಗಾತ್ರ - 1);
          d->m_ಮುಂದಿನ[ins_pos & TDEFL_LZ_DICT_ಗಾತ್ರ_ಮುಖವಾಡ] = d->m_hash[hash]; d->m_hash[hash] = (mz_uint16)(ins_pos);
        }
      }
    }
    d->m_dict_ಗಾತ್ರ = MZ_MIN(TDEFL_LZ_DICT_ಗಾತ್ರ - d->m_lookahead_ಗಾತ್ರ, d->m_dict_ಗಾತ್ರ);
    ಆದರೆ ((!flush) && (d->m_lookahead_ಗಾತ್ರ < TDEFL_MAX_ಹೊಂದಿಕೆ_LEN))
      ನಿಲ್ಲಿಸು;

    // Simple lazy/greedy parsing state machine.
    len_ಗಮ್ಯ_move = 1; cur_ಹೊಂದಿಕೆ_dist = 0; cur_ಹೊಂದಿಕೆ_len = d->m_saved_ಹೊಂದಿಕೆ_len ? d->m_saved_ಹೊಂದಿಕೆ_len : (TDEFL_MIN_ಹೊಂದಿಕೆ_LEN - 1); cur_pos = d->m_lookahead_pos & TDEFL_LZ_DICT_ಗಾತ್ರ_ಮುಖವಾಡ;
    ಆದರೆ (d->m_flags & (TDEFL_RLE_MATCHES | TDEFL_FORCE_ALL_RAW_ಖಂಡಗಳು))
    {
      ಆದರೆ ((d->m_dict_ಗಾತ್ರ) && (!(d->m_flags & TDEFL_FORCE_ALL_RAW_ಖಂಡಗಳು)))
      {
        mz_uint8 c = d->m_dict[(cur_pos - 1) & TDEFL_LZ_DICT_ಗಾತ್ರ_ಮುಖವಾಡ];
        cur_ಹೊಂದಿಕೆ_len = 0; ಆಗ (cur_ಹೊಂದಿಕೆ_len < d->m_lookahead_ಗಾತ್ರ) { ಆದರೆ (d->m_dict[cur_pos + cur_ಹೊಂದಿಕೆ_len] != c) ನಿಲ್ಲಿಸು; cur_ಹೊಂದಿಕೆ_len++; }
        ಆದರೆ (cur_ಹೊಂದಿಕೆ_len < TDEFL_MIN_ಹೊಂದಿಕೆ_LEN) cur_ಹೊಂದಿಕೆ_len = 0; ಇಲ್ಲದಿದ್ದರೆ cur_ಹೊಂದಿಕೆ_dist = 1;
      }
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
      tdefl_ಕಂಡುಹಿಡಿ_ಹೊಂದಿಕೆ(d, d->m_lookahead_pos, d->m_dict_ಗಾತ್ರ, d->m_lookahead_ಗಾತ್ರ, &cur_ಹೊಂದಿಕೆ_dist, &cur_ಹೊಂದಿಕೆ_len);
    }
    ಆದರೆ (((cur_ಹೊಂದಿಕೆ_len == TDEFL_MIN_ಹೊಂದಿಕೆ_LEN) && (cur_ಹೊಂದಿಕೆ_dist >= 8U*1024U)) || (cur_pos == cur_ಹೊಂದಿಕೆ_dist) || ((d->m_flags & TDEFL_FILTER_MATCHES) && (cur_ಹೊಂದಿಕೆ_len <= 5)))
    {
      cur_ಹೊಂದಿಕೆ_dist = cur_ಹೊಂದಿಕೆ_len = 0;
    }
    ಆದರೆ (d->m_saved_ಹೊಂದಿಕೆ_len)
    {
      ಆದರೆ (cur_ಹೊಂದಿಕೆ_len > d->m_saved_ಹೊಂದಿಕೆ_len)
      {
        tdefl_ದಾಖಲೆ_literal(d, (mz_uint8)d->m_saved_lit);
        ಆದರೆ (cur_ಹೊಂದಿಕೆ_len >= 128)
        {
          tdefl_ದಾಖಲೆ_ಹೊಂದಿಕೆ(d, cur_ಹೊಂದಿಕೆ_len, cur_ಹೊಂದಿಕೆ_dist);
          d->m_saved_ಹೊಂದಿಕೆ_len = 0; len_ಗಮ್ಯ_move = cur_ಹೊಂದಿಕೆ_len;
        }
        ಇಲ್ಲದಿದ್ದರೆ
        {
          d->m_saved_lit = d->m_dict[cur_pos]; d->m_saved_ಹೊಂದಿಕೆ_dist = cur_ಹೊಂದಿಕೆ_dist; d->m_saved_ಹೊಂದಿಕೆ_len = cur_ಹೊಂದಿಕೆ_len;
        }
      }
      ಇಲ್ಲದಿದ್ದರೆ
      {
        tdefl_ದಾಖಲೆ_ಹೊಂದಿಕೆ(d, d->m_saved_ಹೊಂದಿಕೆ_len, d->m_saved_ಹೊಂದಿಕೆ_dist);
        len_ಗಮ್ಯ_move = d->m_saved_ಹೊಂದಿಕೆ_len - 1; d->m_saved_ಹೊಂದಿಕೆ_len = 0;
      }
    }
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!cur_ಹೊಂದಿಕೆ_dist)
      tdefl_ದಾಖಲೆ_literal(d, d->m_dict[MZ_MIN(cur_pos, ಗಾತ್ರ(d->m_dict) - 1)]);
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((d->m_greedy_parsing) || (d->m_flags & TDEFL_RLE_MATCHES) || (cur_ಹೊಂದಿಕೆ_len >= 128))
    {
      tdefl_ದಾಖಲೆ_ಹೊಂದಿಕೆ(d, cur_ಹೊಂದಿಕೆ_len, cur_ಹೊಂದಿಕೆ_dist);
      len_ಗಮ್ಯ_move = cur_ಹೊಂದಿಕೆ_len;
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
      d->m_saved_lit = d->m_dict[MZ_MIN(cur_pos, ಗಾತ್ರ(d->m_dict) - 1)]; d->m_saved_ಹೊಂದಿಕೆ_dist = cur_ಹೊಂದಿಕೆ_dist; d->m_saved_ಹೊಂದಿಕೆ_len = cur_ಹೊಂದಿಕೆ_len;
    }
    // Move the lookahead forward by len_to_move bytes.
    d->m_lookahead_pos += len_ಗಮ್ಯ_move;
    MZ_ASSERT(d->m_lookahead_ಗಾತ್ರ >= len_ಗಮ್ಯ_move);
    d->m_lookahead_ಗಾತ್ರ -= len_ಗಮ್ಯ_move;
    d->m_dict_ಗಾತ್ರ = MZ_MIN(d->m_dict_ಗಾತ್ರ + len_ಗಮ್ಯ_move, TDEFL_LZ_DICT_ಗಾತ್ರ);
    // Check if it's time to flush the current LZ codes to the internal output buffer.
    ಆದರೆ ( (d->m_p_LZ_ಸಂಕೇತ_buf > &d->m_lz_ಸಂಕೇತ_buf[TDEFL_LZ_ಸಂಕೇತ_BUF_ಗಾತ್ರ - 8]) ||
         ( (d->m_ಒಟ್ಟು_lz_ಬೈಟುಗಳು > 31*1024) && (((((mz_uint)(d->m_p_LZ_ಸಂಕೇತ_buf - d->m_lz_ಸಂಕೇತ_buf) * 115) >> 7) >= d->m_ಒಟ್ಟು_lz_ಬೈಟುಗಳು) || (d->m_flags & TDEFL_FORCE_ALL_RAW_ಖಂಡಗಳು))) )
    {
      ಪೂರ್ಣಾಂಕ n;
      d->m_pSrc = pSrc; d->m_src_buf_ಎಡ = src_buf_ಎಡ;
      ಆದರೆ ((n = tdefl_flush_ಖಂಡ(d, 0)) != 0)
        ಹಿಂತಿರುಗಿ (n < 0) ? MZ_FALSE : MZ_TRUE;
    }
  }

  d->m_pSrc = pSrc; d->m_src_buf_ಎಡ = src_buf_ಎಡ;
  ಹಿಂತಿರುಗಿ MZ_TRUE;
}

ಸ್ಥಿರ tdefl_ಸ್ಥಿತಿ tdefl_flush_output_ಬಫರ್(tdefl_compressor *d)
{
  ಆದರೆ (d->m_p_ಒಳ_buf_ಗಾತ್ರ)
  {
    *d->m_p_ಒಳ_buf_ಗಾತ್ರ = d->m_pSrc - (ಸ್ಥಿರಾಂಕ mz_uint8 *)d->m_p_ಒಳ_buf;
  }

  ಆದರೆ (d->m_p_ಹೊರಹೋಗು_buf_ಗಾತ್ರ)
  {
    size_t n = MZ_MIN(*d->m_p_ಹೊರಹೋಗು_buf_ಗಾತ್ರ - d->m_ಹೊರಹೋಗು_buf_ofs, d->m_output_flush_ಉಳಿದ);
    ಸ್ಮರಣೆ_ನಕಲು((mz_uint8 *)d->m_p_ಹೊರಹೋಗು_buf + d->m_ಹೊರಹೋಗು_buf_ofs, d->m_output_buf + d->m_output_flush_ofs, n);
    d->m_output_flush_ofs += (mz_uint)n;
    d->m_output_flush_ಉಳಿದ -= (mz_uint)n;
    d->m_ಹೊರಹೋಗು_buf_ofs += n;

    *d->m_p_ಹೊರಹೋಗು_buf_ಗಾತ್ರ = d->m_ಹೊರಹೋಗು_buf_ofs;
  }

  ಹಿಂತಿರುಗಿ (d->m_ಪೂರ್ಣಗೊಂಡ && !d->m_output_flush_ಉಳಿದ) ? TDEFL_ಸ್ಥಿತಿ_ಮುಗಿದ : TDEFL_ಸ್ಥಿತಿ_OKAY;
}

tdefl_ಸ್ಥಿತಿ tdefl_compress(tdefl_compressor *d, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *p_ಒಳ_buf, size_t *p_ಒಳ_buf_ಗಾತ್ರ, ಶೂನ್ಯ *p_ಹೊರಹೋಗು_buf, size_t *p_ಹೊರಹೋಗು_buf_ಗಾತ್ರ, tdefl_flush flush)
{
  ಆದರೆ (!d)
  {
    ಆದರೆ (p_ಒಳ_buf_ಗಾತ್ರ) *p_ಒಳ_buf_ಗಾತ್ರ = 0;
    ಆದರೆ (p_ಹೊರಹೋಗು_buf_ಗಾತ್ರ) *p_ಹೊರಹೋಗು_buf_ಗಾತ್ರ = 0;
    ಹಿಂತಿರುಗಿ TDEFL_ಸ್ಥಿತಿ_BAD_PARAM;
  }

  d->m_p_ಒಳ_buf = p_ಒಳ_buf; d->m_p_ಒಳ_buf_ಗಾತ್ರ = p_ಒಳ_buf_ಗಾತ್ರ;
  d->m_p_ಹೊರಹೋಗು_buf = p_ಹೊರಹೋಗು_buf; d->m_p_ಹೊರಹೋಗು_buf_ಗಾತ್ರ = p_ಹೊರಹೋಗು_buf_ಗಾತ್ರ;
  d->m_pSrc = (ಸ್ಥಿರಾಂಕ mz_uint8 *)(p_ಒಳ_buf); d->m_src_buf_ಎಡ = p_ಒಳ_buf_ಗಾತ್ರ ? *p_ಒಳ_buf_ಗಾತ್ರ : 0;
  d->m_ಹೊರಹೋಗು_buf_ofs = 0;
  d->m_flush = flush;

  ಆದರೆ ( ((d->m_pPut_buf_func != ಖಾಲಿ) == ((p_ಹೊರಹೋಗು_buf != ಖಾಲಿ) || (p_ಹೊರಹೋಗು_buf_ಗಾತ್ರ != ಖಾಲಿ))) || (d->m_prev_return_ಸ್ಥಿತಿ != TDEFL_ಸ್ಥಿತಿ_OKAY) ||
        (d->m_ಬಯಸುತ್ತದೆ_ಗಮ್ಯ_ಮುಕ್ತಾಯ && (flush != TDEFL_ಮುಕ್ತಾಯ)) || (p_ಒಳ_buf_ಗಾತ್ರ && *p_ಒಳ_buf_ಗಾತ್ರ && !p_ಒಳ_buf) || (p_ಹೊರಹೋಗು_buf_ಗಾತ್ರ && *p_ಹೊರಹೋಗು_buf_ಗಾತ್ರ && !p_ಹೊರಹೋಗು_buf) )
  {
    ಆದರೆ (p_ಒಳ_buf_ಗಾತ್ರ) *p_ಒಳ_buf_ಗಾತ್ರ = 0;
    ಆದರೆ (p_ಹೊರಹೋಗು_buf_ಗಾತ್ರ) *p_ಹೊರಹೋಗು_buf_ಗಾತ್ರ = 0;
    ಹಿಂತಿರುಗಿ (d->m_prev_return_ಸ್ಥಿತಿ = TDEFL_ಸ್ಥಿತಿ_BAD_PARAM);
  }
  d->m_ಬಯಸುತ್ತದೆ_ಗಮ್ಯ_ಮುಕ್ತಾಯ |= (flush == TDEFL_ಮುಕ್ತಾಯ);

  ಆದರೆ ((d->m_output_flush_ಉಳಿದ) || (d->m_ಪೂರ್ಣಗೊಂಡ))
    ಹಿಂತಿರುಗಿ (d->m_prev_return_ಸ್ಥಿತಿ = tdefl_flush_output_ಬಫರ್(d));

#ಆದರೆ MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  ಆದರೆ (((d->m_flags & TDEFL_MAX_PROBES_ಮುಖವಾಡ) == 1) &&
      ((d->m_flags & TDEFL_GREEDY_PARSING_FLAG) != 0) &&
      ((d->m_flags & (TDEFL_FILTER_MATCHES | TDEFL_FORCE_ALL_RAW_ಖಂಡಗಳು | TDEFL_RLE_MATCHES)) == 0))
  {
    ಆದರೆ (!tdefl_compress_fast(d))
      ಹಿಂತಿರುಗಿ d->m_prev_return_ಸ್ಥಿತಿ;
  }
  ಇಲ್ಲದಿದ್ದರೆ
#ಆದರೆ_ಅಂತ್ಯ // #if MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  {
    ಆದರೆ (!tdefl_compress_ಸಾಮಾನ್ಯ(d))
      ಹಿಂತಿರುಗಿ d->m_prev_return_ಸ್ಥಿತಿ;
  }

  ಆದರೆ ((d->m_flags & (TDEFL_WRITE_ZLIB_ಶೀರ್ಷಿಕೆ | TDEFL_COMPUTE_ADLER32)) && (p_ಒಳ_buf))
    d->m_adler32 = (mz_uint32)mz_adler32(d->m_adler32, (ಸ್ಥಿರಾಂಕ mz_uint8 *)p_ಒಳ_buf, d->m_pSrc - (ಸ್ಥಿರಾಂಕ mz_uint8 *)p_ಒಳ_buf);

  ಆದರೆ ((flush) && (!d->m_lookahead_ಗಾತ್ರ) && (!d->m_src_buf_ಎಡ) && (!d->m_output_flush_ಉಳಿದ))
  {
    ಆದರೆ (tdefl_flush_ಖಂಡ(d, flush) < 0)
      ಹಿಂತಿರುಗಿ d->m_prev_return_ಸ್ಥಿತಿ;
    d->m_ಪೂರ್ಣಗೊಂಡ = (flush == TDEFL_ಮುಕ್ತಾಯ);
    ಆದರೆ (flush == TDEFL_ತುಂಬಿದ_FLUSH) { MZ_CLEAR_ARR(d->m_hash); MZ_CLEAR_ARR(d->m_ಮುಂದಿನ); d->m_dict_ಗಾತ್ರ = 0; }
  }

  ಹಿಂತಿರುಗಿ (d->m_prev_return_ಸ್ಥಿತಿ = tdefl_flush_output_ಬಫರ್(d));
}

tdefl_ಸ್ಥಿತಿ tdefl_compress_ಬಫರ್(tdefl_compressor *d, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *p_ಒಳ_buf, size_t ಒಳ_buf_ಗಾತ್ರ, tdefl_flush flush)
{
  MZ_ASSERT(d->m_pPut_buf_func); ಹಿಂತಿರುಗಿ tdefl_compress(d, p_ಒಳ_buf, &ಒಳ_buf_ಗಾತ್ರ, ಖಾಲಿ, ಖಾಲಿ, flush);
}

tdefl_ಸ್ಥಿತಿ tdefl_init(tdefl_compressor *d, tdefl_put_buf_func_ptr pPut_buf_func, ಶೂನ್ಯ *pPut_buf_user, ಪೂರ್ಣಾಂಕ flags)
{
  d->m_pPut_buf_func = pPut_buf_func; d->m_pPut_buf_user = pPut_buf_user;
  d->m_flags = (mz_uint)(flags); d->m_max_probes[0] = 1 + ((flags & 0xFFF) + 2) / 3; d->m_greedy_parsing = (flags & TDEFL_GREEDY_PARSING_FLAG) != 0;
  d->m_max_probes[1] = 1 + (((flags & 0xFFF) >> 2) + 2) / 3;
  ಆದರೆ (!(flags & TDEFL_NONDETERMINISTIC_PARSING_FLAG)) MZ_CLEAR_ARR(d->m_hash);
  d->m_lookahead_pos = d->m_lookahead_ಗಾತ್ರ = d->m_dict_ಗಾತ್ರ = d->m_ಒಟ್ಟು_lz_ಬೈಟುಗಳು = d->m_lz_ಸಂಕೇತ_buf_dict_pos = d->m_ಬಿಟ್ಟುಗಳು_ಒಳ = 0;
  d->m_output_flush_ofs = d->m_output_flush_ಉಳಿದ = d->m_ಪೂರ್ಣಗೊಂಡ = d->m_ಖಂಡ_ಸೂಚ್ಯಂಕ = d->m_ಬಿಟ್_ಬಫರ್ = d->m_ಬಯಸುತ್ತದೆ_ಗಮ್ಯ_ಮುಕ್ತಾಯ = 0;
  d->m_p_LZ_ಸಂಕೇತ_buf = d->m_lz_ಸಂಕೇತ_buf + 1; d->m_pLZ_flags = d->m_lz_ಸಂಕೇತ_buf; d->m_ಅಂಕೆ_flags_ಎಡ = 8;
  d->m_pOutput_buf = d->m_output_buf; d->m_p_Output_buf_ಕೊನೆ = d->m_output_buf; d->m_prev_return_ಸ್ಥಿತಿ = TDEFL_ಸ್ಥಿತಿ_OKAY;
  d->m_saved_ಹೊಂದಿಕೆ_dist = d->m_saved_ಹೊಂದಿಕೆ_len = d->m_saved_lit = 0; d->m_adler32 = 1;
  d->m_p_ಒಳ_buf = ಖಾಲಿ; d->m_p_ಹೊರಹೋಗು_buf = ಖಾಲಿ;
  d->m_p_ಒಳ_buf_ಗಾತ್ರ = ಖಾಲಿ; d->m_p_ಹೊರಹೋಗು_buf_ಗಾತ್ರ = ಖಾಲಿ;
  d->m_flush = TDEFL_NO_FLUSH; d->m_pSrc = ಖಾಲಿ; d->m_src_buf_ಎಡ = 0; d->m_ಹೊರಹೋಗು_buf_ofs = 0;
  memset(&d->m_huff_ಎಣಿಕೆ[0][0], 0, ಗಾತ್ರ(d->m_huff_ಎಣಿಕೆ[0][0]) * TDEFL_MAX_HUFF_SYMBOLS_0);
  memset(&d->m_huff_ಎಣಿಕೆ[1][0], 0, ಗಾತ್ರ(d->m_huff_ಎಣಿಕೆ[1][0]) * TDEFL_MAX_HUFF_SYMBOLS_1);
  ಹಿಂತಿರುಗಿ TDEFL_ಸ್ಥಿತಿ_OKAY;
}

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_SDL_NOUNUSED
tdefl_ಸ್ಥಿತಿ tdefl_get_prev_return_ಸ್ಥಿತಿ(tdefl_compressor *d)
{
  ಹಿಂತಿರುಗಿ d->m_prev_return_ಸ್ಥಿತಿ;
}

mz_uint32 tdefl_get_adler32(tdefl_compressor *d)
{
  ಹಿಂತಿರುಗಿ d->m_adler32;
}

mz_bool tdefl_compress_mem_ಗಮ್ಯ_output(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *pBuf, size_t buf_len, tdefl_put_buf_func_ptr pPut_buf_func, ಶೂನ್ಯ *pPut_buf_user, ಪೂರ್ಣಾಂಕ flags)
{
  tdefl_compressor *pComp; mz_bool succeeded; ಆದರೆ (((buf_len) && (!pBuf)) || (!pPut_buf_func)) ಹಿಂತಿರುಗಿ MZ_FALSE;
  pComp = (tdefl_compressor*)MZ_MALLOC(ಗಾತ್ರ(tdefl_compressor)); ಆದರೆ (!pComp) ಹಿಂತಿರುಗಿ MZ_FALSE;
  succeeded = (tdefl_init(pComp, pPut_buf_func, pPut_buf_user, flags) == TDEFL_ಸ್ಥಿತಿ_OKAY);
  succeeded = succeeded && (tdefl_compress_ಬಫರ್(pComp, pBuf, buf_len, TDEFL_ಮುಕ್ತಾಯ) == TDEFL_ಸ್ಥಿತಿ_ಮುಗಿದ);
  MZ_FREE(pComp); ಹಿಂತಿರುಗಿ succeeded;
}
#ಆದರೆ_ಅಂತ್ಯ /* MINIZ_SDL_NOUNUSED */

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
  size_t m_ಗಾತ್ರ, m_ಸಾಮರ್ಥ್ಯ;
  mz_uint8 *m_pBuf;
  mz_bool m_expandable;
} tdefl_output_ಬಫರ್;

ಸ್ಥಿರ mz_bool tdefl_output_ಬಫರ್_putter(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *pBuf, ಪೂರ್ಣಾಂಕ len, ಶೂನ್ಯ *pUser)
{
  tdefl_output_ಬಫರ್ *p = (tdefl_output_ಬಫರ್ *)pUser;
  size_t new_ಗಾತ್ರ = p->m_ಗಾತ್ರ + len;
  ಆದರೆ (new_ಗಾತ್ರ > p->m_ಸಾಮರ್ಥ್ಯ)
  {
    size_t new_ಸಾಮರ್ಥ್ಯ = p->m_ಸಾಮರ್ಥ್ಯ; mz_uint8 *pNew_buf; ಆದರೆ (!p->m_expandable) ಹಿಂತಿರುಗಿ MZ_FALSE;
    ಮಾಡು { new_ಸಾಮರ್ಥ್ಯ = MZ_MAX(128U, new_ಸಾಮರ್ಥ್ಯ << 1U); } ಆಗ (new_ಗಾತ್ರ > new_ಸಾಮರ್ಥ್ಯ);
    pNew_buf = (mz_uint8*)MZ_REALLOC(p->m_pBuf, new_ಸಾಮರ್ಥ್ಯ); ಆದರೆ (!pNew_buf) ಹಿಂತಿರುಗಿ MZ_FALSE;
    p->m_pBuf = pNew_buf; p->m_ಸಾಮರ್ಥ್ಯ = new_ಸಾಮರ್ಥ್ಯ;
  }
  ಸ್ಮರಣೆ_ನಕಲು((mz_uint8*)p->m_pBuf + p->m_ಗಾತ್ರ, pBuf, len); p->m_ಗಾತ್ರ = new_ಗಾತ್ರ;
  ಹಿಂತಿರುಗಿ MZ_TRUE;
}

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_SDL_NOUNUSED
ಶೂನ್ಯ *tdefl_compress_mem_ಗಮ್ಯ_ರಾಶಿ(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *pSrc_buf, size_t src_buf_len, size_t *p_ಹೊರಹೋಗು_len, ಪೂರ್ಣಾಂಕ flags)
{
  tdefl_output_ಬಫರ್ ಹೊರಹೋಗು_buf; MZ_CLEAR_OBJ(ಹೊರಹೋಗು_buf);
  ಆದರೆ (!p_ಹೊರಹೋಗು_len) ಹಿಂತಿರುಗಿ MZ_FALSE; ಇಲ್ಲದಿದ್ದರೆ *p_ಹೊರಹೋಗು_len = 0;
  ಹೊರಹೋಗು_buf.m_expandable = MZ_TRUE;
  ಆದರೆ (!tdefl_compress_mem_ಗಮ್ಯ_output(pSrc_buf, src_buf_len, tdefl_output_ಬಫರ್_putter, &ಹೊರಹೋಗು_buf, flags)) ಹಿಂತಿರುಗಿ ಖಾಲಿ;
  *p_ಹೊರಹೋಗು_len = ಹೊರಹೋಗು_buf.m_ಗಾತ್ರ; ಹಿಂತಿರುಗಿ ಹೊರಹೋಗು_buf.m_pBuf;
}

size_t tdefl_compress_mem_ಗಮ್ಯ_mem(ಶೂನ್ಯ *p_ಹೊರಹೋಗು_buf, size_t ಹೊರಹೋಗು_buf_len, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *pSrc_buf, size_t src_buf_len, ಪೂರ್ಣಾಂಕ flags)
{
  tdefl_output_ಬಫರ್ ಹೊರಹೋಗು_buf; MZ_CLEAR_OBJ(ಹೊರಹೋಗು_buf);
  ಆದರೆ (!p_ಹೊರಹೋಗು_buf) ಹಿಂತಿರುಗಿ 0;
  ಹೊರಹೋಗು_buf.m_pBuf = (mz_uint8*)p_ಹೊರಹೋಗು_buf; ಹೊರಹೋಗು_buf.m_ಸಾಮರ್ಥ್ಯ = ಹೊರಹೋಗು_buf_len;
  ಆದರೆ (!tdefl_compress_mem_ಗಮ್ಯ_output(pSrc_buf, src_buf_len, tdefl_output_ಬಫರ್_putter, &ಹೊರಹೋಗು_buf, flags)) ಹಿಂತಿರುಗಿ 0;
  ಹಿಂತಿರುಗಿ ಹೊರಹೋಗು_buf.m_ಗಾತ್ರ;
}
#ಆದರೆ_ಅಂತ್ಯ /* MINIZ_SDL_NOUNUSED */

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_ZLIB_APIS
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ mz_uint s_tdefl_ಅಂಕೆ_probes[11] = { 0, 1, 6, 32,  16, 32, 128, 256,  512, 768, 1500 };

// level may actually range from [0,10] (10 is a "hidden" max level, where we want a bit more compression and it's fine if throughput to fall off a cliff on some files).
mz_uint tdefl_create_comp_flags_from_zip_params(ಪೂರ್ಣಾಂಕ level, ಪೂರ್ಣಾಂಕ ಕಿಟಕಿ_ಬಿಟ್ಟುಗಳು, ಪೂರ್ಣಾಂಕ strategy)
{
  mz_uint comp_flags = s_tdefl_ಅಂಕೆ_probes[(level >= 0) ? MZ_MIN(10, level) : MZ_DEFAULT_LEVEL] | ((level <= 3) ? TDEFL_GREEDY_PARSING_FLAG : 0);
  ಆದರೆ (ಕಿಟಕಿ_ಬಿಟ್ಟುಗಳು > 0) comp_flags |= TDEFL_WRITE_ZLIB_ಶೀರ್ಷಿಕೆ;

  ಆದರೆ (!level) comp_flags |= TDEFL_FORCE_ALL_RAW_ಖಂಡಗಳು;
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strategy == MZ_FILTERED) comp_flags |= TDEFL_FILTER_MATCHES;
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strategy == MZ_HUFFMAN_ONLY) comp_flags &= ~TDEFL_MAX_PROBES_ಮುಖವಾಡ;
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strategy == MZ_FIXED) comp_flags |= TDEFL_FORCE_ALL_STATIC_ಖಂಡಗಳು;
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strategy == MZ_RLE) comp_flags |= TDEFL_RLE_MATCHES;

  ಹಿಂತಿರುಗಿ comp_flags;
}
#ಆದರೆ_ಅಂತ್ಯ //MINIZ_NO_ZLIB_APIS

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _MSC_VER
#ಸೂಚನೆ warning (ತಳ್ಳು)
#ಸೂಚನೆ warning (disable:4204) // nonstandard extension used : non-constant aggregate initializer (also supported by GNU C and C99, so no big deal)
#ಆದರೆ_ಅಂತ್ಯ

// Simple PNG writer function by Alex Evans, 2011. Released into the public domain: https://gist.github.com/908299, more context at
// http://altdevblogaday.org/2011/04/06/a-smaller-jpg-encoder/.
// This is actually a modification of Alex's original code so PNG files generated by this function pass pngcheck.
MINIZ_STATIC ಶೂನ್ಯ *tdefl_write_image_ಗಮ್ಯ_png_file_ಒಳ_ಸ್ಮರಣೆ_ex(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *pImage, ಪೂರ್ಣಾಂಕ w, ಪೂರ್ಣಾಂಕ h, ಪೂರ್ಣಾಂಕ ಅಂಕೆ_chans, ಪೂರ್ಣಾಂಕ bpl, size_t *p_Len_ಹೊರಹೋಗು, mz_uint level, mz_bool flip, mz_uint8 *plte, ಪೂರ್ಣಾಂಕ plte_ಗಾತ್ರ, mz_uint8 *trns, ಪೂರ್ಣಾಂಕ trns_ಗಾತ್ರ)
{
  // Using a local copy of this array here in case MINIZ_NO_ZLIB_APIS was defined.
  ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ mz_uint s_tdefl_png_ಅಂಕೆ_probes[11] = { 0, 1, 6, 32,  16, 32, 128, 256,  512, 768, 1500 };
  tdefl_compressor *pComp = (tdefl_compressor *)MZ_MALLOC(ಗಾತ್ರ(tdefl_compressor)); tdefl_output_ಬಫರ್ ಹೊರಹೋಗು_buf; ಪೂರ್ಣಾಂಕ i, y, z = 0; mz_uint32 c; *p_Len_ಹೊರಹೋಗು = 0; size_t ದತ್ತಾಂಶ_ಆರಂಭ, ದತ್ತಾಂಶ_ಗಾತ್ರ_3;
  ಆದರೆ (!pComp) ಹಿಂತಿರುಗಿ ಖಾಲಿ;
  MZ_CLEAR_OBJ(ಹೊರಹೋಗು_buf); ಹೊರಹೋಗು_buf.m_expandable = MZ_TRUE;
  ಹೊರಹೋಗು_buf.m_ಸಾಮರ್ಥ್ಯ = 57+MZ_MAX(64, (1+w*ಅಂಕೆ_chans)*h);
  ಆದರೆ (plte_ಗಾತ್ರ > 0)
    ಹೊರಹೋಗು_buf.m_ಸಾಮರ್ಥ್ಯ += 12+plte_ಗಾತ್ರ;
  ಆದರೆ (trns_ಗಾತ್ರ > 0)
    ಹೊರಹೋಗು_buf.m_ಸಾಮರ್ಥ್ಯ += 12+trns_ಗಾತ್ರ;
  ಆದರೆ (ಖಾಲಿ == (ಹೊರಹೋಗು_buf.m_pBuf = (mz_uint8*)MZ_MALLOC(ಹೊರಹೋಗು_buf.m_ಸಾಮರ್ಥ್ಯ))) { MZ_FREE(pComp); ಹಿಂತಿರುಗಿ ಖಾಲಿ; }
  // write header
  {
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ mz_uint8 chans[] = {0x00, 0x00, 0x04, 0x02, 0x06};

    mz_uint8 pnghdr[33]={ 0x89,0x50,0x4e,0x47,0x0d,0x0a,0x1a,0x0a,
                          0x00,0x00,0x00,0x0d,0x49,0x48,0x44,0x52,
                          0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                          0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

    pnghdr[18] = (mz_uint8)(w>>8);
    pnghdr[19] = (mz_uint8)(w>>0);

    pnghdr[22] = (mz_uint8)(h>>8);
    pnghdr[23] = (mz_uint8)(h>>0);

    ಆದರೆ (ಅಂಕೆ_chans == 1 && plte_ಗಾತ್ರ > 0)
      pnghdr[25] = 3;
    ಇಲ್ಲದಿದ್ದರೆ
      pnghdr[25] = (chans[ಅಂಕೆ_chans]);

    c = (mz_uint32)mz_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32(MZ_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_INIT,pnghdr+12,17);
    ಗಾಗಿ (i=0; i<4; ++i, c<<=8) ((mz_uint8*)(pnghdr+29))[i] = (mz_uint8)(c>>24);
    ಆದರೆ (!tdefl_output_ಬಫರ್_putter(pnghdr, ಗಾತ್ರ(pnghdr), &ಹೊರಹೋಗು_buf)) { *p_Len_ಹೊರಹೋಗು = 0; MZ_FREE(pComp); MZ_FREE(ಹೊರಹೋಗು_buf.m_pBuf); ಹಿಂತಿರುಗಿ ಖಾಲಿ; }
  }
  // write PLTE chunk
  ಆದರೆ (plte_ಗಾತ್ರ > 0)
  {
    mz_uint8 hdr[8]={0x00,0x00,0x00,0x00,0x50,0x4c,0x54,0x45};

    hdr[0] = (mz_uint8)(plte_ಗಾತ್ರ>>24);
    hdr[1] = (mz_uint8)(plte_ಗಾತ್ರ>>16);
    hdr[2] = (mz_uint8)(plte_ಗಾತ್ರ>> 8);
    hdr[3] = (mz_uint8)(plte_ಗಾತ್ರ>> 0);
    ಆದರೆ (!tdefl_output_ಬಫರ್_putter(hdr, ಗಾತ್ರ(hdr), &ಹೊರಹೋಗು_buf)) { *p_Len_ಹೊರಹೋಗು = 0; MZ_FREE(pComp); MZ_FREE(ಹೊರಹೋಗು_buf.m_pBuf); ಹಿಂತಿರುಗಿ ಖಾಲಿ; }
    ದತ್ತಾಂಶ_ಆರಂಭ = ಹೊರಹೋಗು_buf.m_ಗಾತ್ರ;
    ಆದರೆ (!tdefl_output_ಬಫರ್_putter(plte, plte_ಗಾತ್ರ, &ಹೊರಹೋಗು_buf)) { *p_Len_ಹೊರಹೋಗು = 0; MZ_FREE(pComp); MZ_FREE(ಹೊರಹೋಗು_buf.m_pBuf); ಹಿಂತಿರುಗಿ ಖಾಲಿ; }
    ಆದರೆ (!tdefl_output_ಬಫರ್_putter("\0\0\0\0", 4, &ಹೊರಹೋಗು_buf)) { *p_Len_ಹೊರಹೋಗು = 0; MZ_FREE(pComp); MZ_FREE(ಹೊರಹೋಗು_buf.m_pBuf); ಹಿಂತಿರುಗಿ ಖಾಲಿ; }
    c = (mz_uint32)mz_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32(MZ_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_INIT,ಹೊರಹೋಗು_buf.m_pBuf+ದತ್ತಾಂಶ_ಆರಂಭ-4, plte_ಗಾತ್ರ+4);
    ಗಾಗಿ (i=0; i<4; ++i, c<<=8) (ಹೊರಹೋಗು_buf.m_pBuf+ಹೊರಹೋಗು_buf.m_ಗಾತ್ರ-4)[i] = (mz_uint8)(c >> 24);
  }
  // write tRNS chunk
  ಆದರೆ (trns_ಗಾತ್ರ > 0)
  {
    mz_uint8 hdr[8]={0x00,0x00,0x00,0x00,0x74,0x52,0x4E,0x53};

    hdr[0] = (mz_uint8)(trns_ಗಾತ್ರ>>24);
    hdr[1] = (mz_uint8)(trns_ಗಾತ್ರ>>16);
    hdr[2] = (mz_uint8)(trns_ಗಾತ್ರ>> 8);
    hdr[3] = (mz_uint8)(trns_ಗಾತ್ರ>> 0);
    ಆದರೆ (!tdefl_output_ಬಫರ್_putter(hdr, ಗಾತ್ರ(hdr), &ಹೊರಹೋಗು_buf)) { *p_Len_ಹೊರಹೋಗು = 0; MZ_FREE(pComp); MZ_FREE(ಹೊರಹೋಗು_buf.m_pBuf); ಹಿಂತಿರುಗಿ ಖಾಲಿ; }
    ದತ್ತಾಂಶ_ಆರಂಭ = ಹೊರಹೋಗು_buf.m_ಗಾತ್ರ;
    ಆದರೆ (!tdefl_output_ಬಫರ್_putter(trns, trns_ಗಾತ್ರ, &ಹೊರಹೋಗು_buf)) { *p_Len_ಹೊರಹೋಗು = 0; MZ_FREE(pComp); MZ_FREE(ಹೊರಹೋಗು_buf.m_pBuf); ಹಿಂತಿರುಗಿ ಖಾಲಿ; }
    ಆದರೆ (!tdefl_output_ಬಫರ್_putter("\0\0\0\0", 4, &ಹೊರಹೋಗು_buf)) { *p_Len_ಹೊರಹೋಗು = 0; MZ_FREE(pComp); MZ_FREE(ಹೊರಹೋಗು_buf.m_pBuf); ಹಿಂತಿರುಗಿ ಖಾಲಿ; }
    c = (mz_uint32)mz_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32(MZ_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_INIT,ಹೊರಹೋಗು_buf.m_pBuf+ದತ್ತಾಂಶ_ಆರಂಭ-4, trns_ಗಾತ್ರ+4);
    ಗಾಗಿ (i=0; i<4; ++i, c<<=8) (ಹೊರಹೋಗು_buf.m_pBuf+ಹೊರಹೋಗು_buf.m_ಗಾತ್ರ-4)[i] = (mz_uint8)(c >> 24);
  }
  // write IDAT chunk
  ಆದರೆ (!tdefl_output_ಬಫರ್_putter("\0\0\0\0\x49\x44\x41\x54", 8, &ಹೊರಹೋಗು_buf)) { *p_Len_ಹೊರಹೋಗು = 0; MZ_FREE(pComp); MZ_FREE(ಹೊರಹೋಗು_buf.m_pBuf); ಹಿಂತಿರುಗಿ ಖಾಲಿ; }
  ದತ್ತಾಂಶ_ಆರಂಭ = ಹೊರಹೋಗು_buf.m_ಗಾತ್ರ;
  // compress image data
  tdefl_init(pComp, tdefl_output_ಬಫರ್_putter, &ಹೊರಹೋಗು_buf, s_tdefl_png_ಅಂಕೆ_probes[MZ_MIN(10, level)] | TDEFL_WRITE_ZLIB_ಶೀರ್ಷಿಕೆ);
  ಗಾಗಿ (y = 0; y < h; ++y) { tdefl_compress_ಬಫರ್(pComp, &z, 1, TDEFL_NO_FLUSH); tdefl_compress_ಬಫರ್(pComp, (mz_uint8*)pImage + (flip ? (h - 1 - y) : y) * bpl, w * ಅಂಕೆ_chans, TDEFL_NO_FLUSH); }
  ಆದರೆ (tdefl_compress_ಬಫರ್(pComp, ಖಾಲಿ, 0, TDEFL_ಮುಕ್ತಾಯ) != TDEFL_ಸ್ಥಿತಿ_ಮುಗಿದ) { MZ_FREE(pComp); MZ_FREE(ಹೊರಹೋಗು_buf.m_pBuf); ಹಿಂತಿರುಗಿ ಖಾಲಿ; }
  // write IDAT size
  ದತ್ತಾಂಶ_ಗಾತ್ರ_3 = ಹೊರಹೋಗು_buf.m_ಗಾತ್ರ-ದತ್ತಾಂಶ_ಆರಂಭ;
  (ಹೊರಹೋಗು_buf.m_pBuf+ದತ್ತಾಂಶ_ಆರಂಭ-8)[0] = (mz_uint8)(ದತ್ತಾಂಶ_ಗಾತ್ರ_3>>24);
  (ಹೊರಹೋಗು_buf.m_pBuf+ದತ್ತಾಂಶ_ಆರಂಭ-8)[1] = (mz_uint8)(ದತ್ತಾಂಶ_ಗಾತ್ರ_3>>16);
  (ಹೊರಹೋಗು_buf.m_pBuf+ದತ್ತಾಂಶ_ಆರಂಭ-8)[2] = (mz_uint8)(ದತ್ತಾಂಶ_ಗಾತ್ರ_3>> 8);
  (ಹೊರಹೋಗು_buf.m_pBuf+ದತ್ತಾಂಶ_ಆರಂಭ-8)[3] = (mz_uint8)(ದತ್ತಾಂಶ_ಗಾತ್ರ_3>> 0);
  // write footer (IDAT CRC-32, followed by IEND chunk)
  ಆದರೆ (!tdefl_output_ಬಫರ್_putter("\0\0\0\0\0\0\0\0\x49\x45\x4e\x44\xae\x42\x60\x82", 16, &ಹೊರಹೋಗು_buf)) { *p_Len_ಹೊರಹೋಗು = 0; MZ_FREE(pComp); MZ_FREE(ಹೊರಹೋಗು_buf.m_pBuf); ಹಿಂತಿರುಗಿ ಖಾಲಿ; }
  c = (mz_uint32)mz_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32(MZ_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_INIT,ಹೊರಹೋಗು_buf.m_pBuf+ದತ್ತಾಂಶ_ಆರಂಭ-4, ದತ್ತಾಂಶ_ಗಾತ್ರ_3+4);
  ಗಾಗಿ (i=0; i<4; ++i, c<<=8) (ಹೊರಹೋಗು_buf.m_pBuf+ಹೊರಹೋಗು_buf.m_ಗಾತ್ರ-16)[i] = (mz_uint8)(c >> 24);
  // compute final size of file, grab compressed data buffer and return
  *p_Len_ಹೊರಹೋಗು = ಹೊರಹೋಗು_buf.m_ಗಾತ್ರ;
  MZ_FREE(pComp);
  ಹಿಂತಿರುಗಿ ಹೊರಹೋಗು_buf.m_pBuf;
}
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_SDL_NOUNUSED
MINIZ_STATIC ಶೂನ್ಯ *tdefl_write_image_ಗಮ್ಯ_png_file_ಒಳ_ಸ್ಮರಣೆ(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *pImage, ಪೂರ್ಣಾಂಕ w, ಪೂರ್ಣಾಂಕ h, ಪೂರ್ಣಾಂಕ ಅಂಕೆ_chans, ಪೂರ್ಣಾಂಕ bpl, size_t *p_Len_ಹೊರಹೋಗು)
{
  // Level 6 corresponds to TDEFL_DEFAULT_MAX_PROBES or MZ_DEFAULT_LEVEL (but we can't depend on MZ_DEFAULT_LEVEL being available in case the zlib API's where #defined out)
  ಹಿಂತಿರುಗಿ tdefl_write_image_ಗಮ್ಯ_png_file_ಒಳ_ಸ್ಮರಣೆ_ex(pImage, w, h, ಅಂಕೆ_chans, bpl, p_Len_ಹೊರಹೋಗು, 6, MZ_FALSE, ಖಾಲಿ, 0, ಖಾಲಿ, 0);
}
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _MSC_VER
#ಸೂಚನೆ warning (ತೆಗೆ)
#ಆದರೆ_ಅಂತ್ಯ
#ಆದರೆ_ಅಂತ್ಯ /*#ifndef MINIZ_NO_DEFLATE_APIS*/

// ------------------- .ZIP archive reading

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_ARCHIVE_APIS

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ MINIZ_NO_STDIO
  #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FILE ಶೂನ್ಯ *
#ಇಲ್ಲದಿದ್ದರೆ
  #ಅನ್ತರ್ಭಾವ <stdio.h>
  #ಅನ್ತರ್ಭಾವ <sys/stat.h>

  #ಆದರೆ defined(_MSC_VER) || defined(__MINGW64__)
    ಸ್ಥಿರ FILE *mz_fopen(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pFilename, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *p_ಬಹುಲಕ)
    {
      FILE* pFile = ಖಾಲಿ;
      fopen_s(&pFile, pFilename, p_ಬಹುಲಕ);
      ಹಿಂತಿರುಗಿ pFile;
    }
    ಸ್ಥಿರ FILE *mz_freopen(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *p_ಮಾರ್ಗ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *p_ಬಹುಲಕ, FILE *p_ಹರಿವು)
    {
      FILE* pFile = ಖಾಲಿ;
      ಆದರೆ (freopen_s(&pFile, p_ಮಾರ್ಗ, p_ಬಹುಲಕ, p_ಹರಿವು))
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
      ಹಿಂತಿರುಗಿ pFile;
    }
    #ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_ಸಮಯ
      #ಅನ್ತರ್ಭಾವ <sys/utime.h>
    #ಆದರೆ_ಅಂತ್ಯ
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FILE FILE
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FOPEN mz_fopen
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FCLOSE fclose
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FREAD fread
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FWRITE fwrite
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FTELL64 _ftelli64
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FSEEK64 _fseeki64
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FILE_STAT_STRUCT _stat
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FILE_STAT _stat
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FFLUSH fflush
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FREOPEN mz_freopen
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_DELETE_FILE remove
  #ಅಥವಾಆದರೆ defined(__MINGW32__)
    #ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_ಸಮಯ
      #ಅನ್ತರ್ಭಾವ <sys/utime.h>
    #ಆದರೆ_ಅಂತ್ಯ
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FILE FILE
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FOPEN(f, m) fopen(f, m)
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FCLOSE fclose
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FREAD fread
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FWRITE fwrite
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FTELL64 ftello64
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FSEEK64 fseeko64
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FILE_STAT_STRUCT _stat
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FILE_STAT _stat
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FFLUSH fflush
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FREOPEN(f, m, s) freopen(f, m, s)
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_DELETE_FILE remove
  #ಅಥವಾಆದರೆ defined(__TINYC__)
    #ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_ಸಮಯ
      #ಅನ್ತರ್ಭಾವ <sys/utime.h>
    #ಆದರೆ_ಅಂತ್ಯ
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FILE FILE
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FOPEN(f, m) fopen(f, m)
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FCLOSE fclose
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FREAD fread
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FWRITE fwrite
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FTELL64 ftell
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FSEEK64 fseek
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FILE_STAT_STRUCT stat
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FILE_STAT stat
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FFLUSH fflush
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FREOPEN(f, m, s) freopen(f, m, s)
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_DELETE_FILE remove
  #ಅಥವಾಆದರೆ defined(__GNUC__) && LARGEFILE64_ಮೂಲ
    #ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_ಸಮಯ
      #ಅನ್ತರ್ಭಾವ <utime.h>
    #ಆದರೆ_ಅಂತ್ಯ
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FILE FILE
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FOPEN(f, m) fopen64(f, m)
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FCLOSE fclose
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FREAD fread
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FWRITE fwrite
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FTELL64 ftello64
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FSEEK64 fseeko64
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FILE_STAT_STRUCT stat64
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FILE_STAT stat64
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FFLUSH fflush
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FREOPEN(p, m, s) freopen64(p, m, s)
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_DELETE_FILE remove
  #ಇಲ್ಲದಿದ್ದರೆ
    #ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_ಸಮಯ
      #ಅನ್ತರ್ಭಾವ <utime.h>
    #ಆದರೆ_ಅಂತ್ಯ
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FILE FILE
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FOPEN(f, m) fopen(f, m)
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FCLOSE fclose
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FREAD fread
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FWRITE fwrite
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FTELL64 ftello
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FSEEK64 fseeko
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FILE_STAT_STRUCT stat
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FILE_STAT stat
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FFLUSH fflush
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_FREOPEN(f, m, s) freopen(f, m, s)
    #ವ್ಯಾಖ್ಯಾನಿಸು MZ_DELETE_FILE remove
  #ಆದರೆ_ಅಂತ್ಯ // #ifdef _MSC_VER
#ಆದರೆ_ಅಂತ್ಯ // #ifdef MINIZ_NO_STDIO

#ವ್ಯಾಖ್ಯಾನಿಸು MZ_TOLOWER(c) ((((c) >= 'A') && ((c) <= 'Z')) ? ((c) - 'A' + 'a') : (c))

// Various ZIP archive enums. To completely avoid cross platform compiler alignment and platform endian issues, miniz.c doesn't use structs for any of this stuff.
ಎಣಿಕೆ
{
  // ZIP archive identifiers and record sizes
  MZ_ZIP_ಕೊನೆ_ದ_CENTRAL_DIR_ಶೀರ್ಷಿಕೆ_SIG = 0x06054b50, MZ_ZIP_CENTRAL_DIR_ಶೀರ್ಷಿಕೆ_SIG = 0x02014b50, MZ_ZIP_LOCAL_DIR_ಶೀರ್ಷಿಕೆ_SIG = 0x04034b50,
  MZ_ZIP_LOCAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ = 30, MZ_ZIP_CENTRAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ = 46, MZ_ZIP_ಕೊನೆ_ದ_CENTRAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ = 22,
  // Central directory header record offsets
  MZ_ZIP_CDH_SIG_OFS = 0, MZ_ZIP_CDH_ಆವೃತ್ತಿ_MADE_BY_OFS = 4, MZ_ZIP_CDH_ಆವೃತ್ತಿ_NEEDED_OFS = 6, MZ_ZIP_CDH_ಬಿಟ್_FLAG_OFS = 8,
  MZ_ZIP_CDH_ವಿಧಾನ_OFS = 10, MZ_ZIP_CDH_FILE_ಸಮಯ_OFS = 12, MZ_ZIP_CDH_FILE_DATE_OFS = 14, MZ_ZIP_CDH_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_OFS = 16,
  MZ_ZIP_CDH_COMPRESSED_ಗಾತ್ರ_OFS = 20, MZ_ZIP_CDH_DECOMPRESSED_ಗಾತ್ರ_OFS = 24, MZ_ZIP_CDH_FILENAME_LEN_OFS = 28, MZ_ZIP_CDH_EXTRA_LEN_OFS = 30,
  MZ_ZIP_CDH_COMMENT_LEN_OFS = 32, MZ_ZIP_CDH_DISK_ಆರಂಭ_OFS = 34, MZ_ZIP_CDH_ಆಂತರಿಕ_ATTR_OFS = 36, MZ_ZIP_CDH_EXTERNAL_ATTR_OFS = 38, MZ_ZIP_CDH_LOCAL_ಶೀರ್ಷಿಕೆ_OFS = 42,
  // Local directory header offsets
  MZ_ZIP_LDH_SIG_OFS = 0, MZ_ZIP_LDH_ಆವೃತ್ತಿ_NEEDED_OFS = 4, MZ_ZIP_LDH_ಬಿಟ್_FLAG_OFS = 6, MZ_ZIP_LDH_ವಿಧಾನ_OFS = 8, MZ_ZIP_LDH_FILE_ಸಮಯ_OFS = 10,
  MZ_ZIP_LDH_FILE_DATE_OFS = 12, MZ_ZIP_LDH_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_OFS = 14, MZ_ZIP_LDH_COMPRESSED_ಗಾತ್ರ_OFS = 18, MZ_ZIP_LDH_DECOMPRESSED_ಗಾತ್ರ_OFS = 22,
  MZ_ZIP_LDH_FILENAME_LEN_OFS = 26, MZ_ZIP_LDH_EXTRA_LEN_OFS = 28,
  // End of central directory offsets
  MZ_ZIP_ECDH_SIG_OFS = 0, MZ_ZIP_ECDH_ಅಂಕೆ_THIS_DISK_OFS = 4, MZ_ZIP_ECDH_ಅಂಕೆ_DISK_CDIR_OFS = 6, MZ_ZIP_ECDH_CDIR_ಅಂಕೆ_ENTRIES_ON_DISK_OFS = 8,
  MZ_ZIP_ECDH_CDIR_ಒಟ್ಟು_ENTRIES_OFS = 10, MZ_ZIP_ECDH_CDIR_ಗಾತ್ರ_OFS = 12, MZ_ZIP_ECDH_CDIR_OFS_OFS = 16, MZ_ZIP_ECDH_COMMENT_ಗಾತ್ರ_OFS = 20,
};

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
  ಶೂನ್ಯ *m_p;
  size_t m_ಗಾತ್ರ, m_ಸಾಮರ್ಥ್ಯ;
  mz_uint m_element_ಗಾತ್ರ;
} mz_zip_array;

ರಚನೆ mz_zip_ಆಂತರಿಕ_state_ಟ್ಯಾಗ್
{
  mz_zip_array m_central_dir;
  mz_zip_array m_central_dir_offsets;
  mz_zip_array m_sorted_central_dir_offsets;
  MZ_FILE *m_pFile;
  ಶೂನ್ಯ *m_pMem;
  size_t m_mem_ಗಾತ್ರ;
  size_t m_mem_ಸಾಮರ್ಥ್ಯ;
};

#ವ್ಯಾಖ್ಯಾನಿಸು MZ_ZIP_ARRAY_ಗಣ_ELEMENT_ಗಾತ್ರ(array_ptr, element_ಗಾತ್ರ) (array_ptr)->m_element_ಗಾತ್ರ = element_ಗಾತ್ರ
#ವ್ಯಾಖ್ಯಾನಿಸು MZ_ZIP_ARRAY_ELEMENT(array_ptr, element_type, ಸೂಚ್ಯಂಕ) ((element_type *)((array_ptr)->m_p))[ಸೂಚ್ಯಂಕ]

ಸ್ಥಿರ MZ_FORCEINLINE ಶೂನ್ಯ mz_zip_array_clear(mz_zip_archive *pZip, mz_zip_array *pArray)
{
  pZip->m_pFree(pZip->m_pAlloc_opaque, pArray->m_p);
  memset(pArray, 0, ಗಾತ್ರ(mz_zip_array));
}

ಸ್ಥಿರ mz_bool mz_zip_array_ensure_ಸಾಮರ್ಥ್ಯ(mz_zip_archive *pZip, mz_zip_array *pArray, size_t min_new_ಸಾಮರ್ಥ್ಯ, mz_uint growing)
{
  ಶೂನ್ಯ *pNew_p; size_t new_ಸಾಮರ್ಥ್ಯ = min_new_ಸಾಮರ್ಥ್ಯ; MZ_ASSERT(pArray->m_element_ಗಾತ್ರ); ಆದರೆ (pArray->m_ಸಾಮರ್ಥ್ಯ >= min_new_ಸಾಮರ್ಥ್ಯ) ಹಿಂತಿರುಗಿ MZ_TRUE;
  ಆದರೆ (growing) { new_ಸಾಮರ್ಥ್ಯ = MZ_MAX(1, pArray->m_ಸಾಮರ್ಥ್ಯ); ಆಗ (new_ಸಾಮರ್ಥ್ಯ < min_new_ಸಾಮರ್ಥ್ಯ) new_ಸಾಮರ್ಥ್ಯ *= 2; }
  ಆದರೆ (ಖಾಲಿ == (pNew_p = pZip->m_pRealloc(pZip->m_pAlloc_opaque, pArray->m_p, pArray->m_element_ಗಾತ್ರ, new_ಸಾಮರ್ಥ್ಯ))) ಹಿಂತಿರುಗಿ MZ_FALSE;
  pArray->m_p = pNew_p; pArray->m_ಸಾಮರ್ಥ್ಯ = new_ಸಾಮರ್ಥ್ಯ;
  ಹಿಂತಿರುಗಿ MZ_TRUE;
}

ಸ್ಥಿರ MZ_FORCEINLINE mz_bool mz_zip_array_reserve(mz_zip_archive *pZip, mz_zip_array *pArray, size_t new_ಸಾಮರ್ಥ್ಯ, mz_uint growing)
{
  ಆದರೆ (new_ಸಾಮರ್ಥ್ಯ > pArray->m_ಸಾಮರ್ಥ್ಯ) { ಆದರೆ (!mz_zip_array_ensure_ಸಾಮರ್ಥ್ಯ(pZip, pArray, new_ಸಾಮರ್ಥ್ಯ, growing)) ಹಿಂತಿರುಗಿ MZ_FALSE; }
  ಹಿಂತಿರುಗಿ MZ_TRUE;
}

ಸ್ಥಿರ MZ_FORCEINLINE mz_bool mz_zip_array_resize(mz_zip_archive *pZip, mz_zip_array *pArray, size_t new_ಗಾತ್ರ, mz_uint growing)
{
  ಆದರೆ (new_ಗಾತ್ರ > pArray->m_ಸಾಮರ್ಥ್ಯ) { ಆದರೆ (!mz_zip_array_ensure_ಸಾಮರ್ಥ್ಯ(pZip, pArray, new_ಗಾತ್ರ, growing)) ಹಿಂತಿರುಗಿ MZ_FALSE; }
  pArray->m_ಗಾತ್ರ = new_ಗಾತ್ರ;
  ಹಿಂತಿರುಗಿ MZ_TRUE;
}

ಸ್ಥಿರ MZ_FORCEINLINE mz_bool mz_zip_array_ensure_ಸ್ಥಳ(mz_zip_archive *pZip, mz_zip_array *pArray, size_t n)
{
  ಹಿಂತಿರುಗಿ mz_zip_array_reserve(pZip, pArray, pArray->m_ಗಾತ್ರ + n, MZ_TRUE);
}

ಸ್ಥಿರ MZ_FORCEINLINE mz_bool mz_zip_array_ತಳ್ಳು_ಹಿಂಭಾಗ(mz_zip_archive *pZip, mz_zip_array *pArray, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *pElements, size_t n)
{
  size_t orig_ಗಾತ್ರ = pArray->m_ಗಾತ್ರ; ಆದರೆ (!mz_zip_array_resize(pZip, pArray, orig_ಗಾತ್ರ + n, MZ_TRUE)) ಹಿಂತಿರುಗಿ MZ_FALSE;
  ಸ್ಮರಣೆ_ನಕಲು((mz_uint8*)pArray->m_p + orig_ಗಾತ್ರ * pArray->m_element_ಗಾತ್ರ, pElements, n * pArray->m_element_ಗಾತ್ರ);
  ಹಿಂತಿರುಗಿ MZ_TRUE;
}

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_ಸಮಯ
ಸ್ಥಿರ ಸಮಯ_t mz_zip_dos_ಗಮ್ಯ_ಸಮಯ_t(ಪೂರ್ಣಾಂಕ dos_ಸಮಯ, ಪೂರ್ಣಾಂಕ dos_date)
{
  ರಚನೆ tm tm;
  memset(&tm, 0, ಗಾತ್ರ(tm)); tm.tm_isdst = -1;
  tm.tm_year = ((dos_date >> 9) & 127) + 1980 - 1900; tm.tm_mon = ((dos_date >> 5) & 15) - 1; tm.tm_mday = dos_date & 31;
  tm.tm_hour = (dos_ಸಮಯ >> 11) & 31; tm.tm_min = (dos_ಸಮಯ >> 5) & 63; tm.tm_sec = (dos_ಸಮಯ << 1) & 62;
  ಹಿಂತಿರುಗಿ mktime(&tm);
}

ಸ್ಥಿರ ಶೂನ್ಯ mz_zip_ಸಮಯ_ಗಮ್ಯ_dos_ಸಮಯ(ಸಮಯ_t ಸಮಯ, mz_uint16 *p_DOS_ಸಮಯ, mz_uint16 *pDOS_date)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _MSC_VER
  ರಚನೆ tm tm_struct;
  ರಚನೆ tm *tm = &tm_struct;
  errno_t err = localtime_s(tm, &ಸಮಯ);
  ಆದರೆ (err)
  {
    *pDOS_date = 0; *p_DOS_ಸಮಯ = 0;
    ಹಿಂತಿರುಗಿ;
  }
#ಇಲ್ಲದಿದ್ದರೆ
  ರಚನೆ tm *tm = localtime(&ಸಮಯ);
#ಆದರೆ_ಅಂತ್ಯ
  *p_DOS_ಸಮಯ = (mz_uint16)(((tm->tm_hour) << 11) + ((tm->tm_min) << 5) + ((tm->tm_sec) >> 1));
  *pDOS_date = (mz_uint16)(((tm->tm_year + 1900 - 1980) << 9) + ((tm->tm_mon + 1) << 5) + tm->tm_mday);
}
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_STDIO
ಸ್ಥಿರ mz_bool mz_zip_get_file_modified_ಸಮಯ(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pFilename, mz_uint16 *p_DOS_ಸಮಯ, mz_uint16 *pDOS_date)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ MINIZ_NO_ಸಮಯ
  (ಶೂನ್ಯ)pFilename; *pDOS_date = *p_DOS_ಸಮಯ = 0;
#ಇಲ್ಲದಿದ್ದರೆ
  ರಚನೆ MZ_FILE_STAT_STRUCT file_stat;
  // On Linux with x86 glibc, this call will fail on large files (>= 0x80000000 bytes) unless you compiled with _LARGEFILE64_SOURCE. Argh.
  ಆದರೆ (MZ_FILE_STAT(pFilename, &file_stat) != 0)
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  mz_zip_ಸಮಯ_ಗಮ್ಯ_dos_ಸಮಯ(file_stat.st_mtime, p_DOS_ಸಮಯ, pDOS_date);
#ಆದರೆ_ಅಂತ್ಯ // #ifdef MINIZ_NO_TIME
  ಹಿಂತಿರುಗಿ MZ_TRUE;
}

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_ಸಮಯ
ಸ್ಥಿರ mz_bool mz_zip_ಗಣ_file_times(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pFilename, ಸಮಯ_t access_ಸಮಯ, ಸಮಯ_t modified_ಸಮಯ)
{
  ರಚನೆ utimbuf t; t.actime = access_ಸಮಯ; t.modtime = modified_ಸಮಯ;
  ಹಿಂತಿರುಗಿ !utime(pFilename, &t);
}
#ಆದರೆ_ಅಂತ್ಯ // #ifndef MINIZ_NO_TIME
#ಆದರೆ_ಅಂತ್ಯ // #ifndef MINIZ_NO_STDIO

ಸ್ಥಿರ mz_bool mz_zip_reader_init_ಆಂತರಿಕ(mz_zip_archive *pZip, mz_uint32 flags)
{
  (ಶೂನ್ಯ)flags;
  ಆದರೆ ((!pZip) || (pZip->m_pState) || (pZip->m_zip_ಬಹುಲಕ != MZ_ZIP_ಬಹುಲಕ_INVALID))
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  ಆದರೆ (!pZip->m_pAlloc) pZip->m_pAlloc = def_alloc_func;
  ಆದರೆ (!pZip->m_pFree) pZip->m_pFree = def_free_func;
  ಆದರೆ (!pZip->m_pRealloc) pZip->m_pRealloc = def_realloc_func;

  pZip->m_zip_ಬಹುಲಕ = MZ_ZIP_ಬಹುಲಕ_READING;
  pZip->m_archive_ಗಾತ್ರ = 0;
  pZip->m_central_directory_file_ofs = 0;
  pZip->m_ಒಟ್ಟು_files = 0;

  ಆದರೆ (ಖಾಲಿ == (pZip->m_pState = (mz_zip_ಆಂತರಿಕ_state *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, ಗಾತ್ರ(mz_zip_ಆಂತರಿಕ_state))))
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  memset(pZip->m_pState, 0, ಗಾತ್ರ(mz_zip_ಆಂತರಿಕ_state));
  MZ_ZIP_ARRAY_ಗಣ_ELEMENT_ಗಾತ್ರ(&pZip->m_pState->m_central_dir, ಗಾತ್ರ(mz_uint8));
  MZ_ZIP_ARRAY_ಗಣ_ELEMENT_ಗಾತ್ರ(&pZip->m_pState->m_central_dir_offsets, ಗಾತ್ರ(mz_uint32));
  MZ_ZIP_ARRAY_ಗಣ_ELEMENT_ಗಾತ್ರ(&pZip->m_pState->m_sorted_central_dir_offsets, ಗಾತ್ರ(mz_uint32));
  ಹಿಂತಿರುಗಿ MZ_TRUE;
}

ಸ್ಥಿರ MZ_FORCEINLINE mz_bool mz_zip_reader_filename_less(ಸ್ಥಿರಾಂಕ mz_zip_array *pCentral_dir_array, ಸ್ಥಿರಾಂಕ mz_zip_array *pCentral_dir_offsets, mz_uint l_ಸೂಚ್ಯಂಕ, mz_uint r_ಸೂಚ್ಯಂಕ)
{
  ಸ್ಥಿರಾಂಕ mz_uint8 *pL = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, l_ಸೂಚ್ಯಂಕ)), *pE;
  ಸ್ಥಿರಾಂಕ mz_uint8 *pR = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, r_ಸೂಚ್ಯಂಕ));
  mz_uint l_len = MZ_READ_LE16(pL + MZ_ZIP_CDH_FILENAME_LEN_OFS), r_len = MZ_READ_LE16(pR + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  mz_uint8 l = 0, r = 0;
  pL += MZ_ZIP_CENTRAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ; pR += MZ_ZIP_CENTRAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ;
  pE = pL + MZ_MIN(l_len, r_len);
  ಆಗ (pL < pE)
  {
    ಆದರೆ ((l = MZ_TOLOWER(*pL)) != (r = MZ_TOLOWER(*pR)))
      ನಿಲ್ಲಿಸು;
    pL++; pR++;
  }
  ಹಿಂತಿರುಗಿ (pL == pE) ? (l_len < r_len) : (l < r);
}

#ವ್ಯಾಖ್ಯಾನಿಸು MZ_ಅದಲುಬದಲು_UINT32(a, b) ಮಾಡು { mz_uint32 t = a; a = b; b = t; } MZ_MACRO_ಕೊನೆ

// Heap sort of lowercased filenames, used to help accelerate plain central directory searches by mz_zip_reader_locate_file(). (Could also use qsort(), but it could allocate memory.)
ಸ್ಥಿರ ಶೂನ್ಯ mz_zip_reader_ವಿಂಗಡಿಸು_central_dir_offsets_by_filename(mz_zip_archive *pZip)
{
  mz_zip_ಆಂತರಿಕ_state *pState = pZip->m_pState;
  ಸ್ಥಿರಾಂಕ mz_zip_array *pCentral_dir_offsets = &pState->m_central_dir_offsets;
  ಸ್ಥಿರಾಂಕ mz_zip_array *pCentral_dir = &pState->m_central_dir;
  mz_uint32 *pIndices = &MZ_ZIP_ARRAY_ELEMENT(&pState->m_sorted_central_dir_offsets, mz_uint32, 0);
  ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2 = pZip->m_ಒಟ್ಟು_files;
  ಪೂರ್ಣಾಂಕ ಆರಂಭ = (ಗಾತ್ರ_2 - 2) >> 1, ಕೊನೆ;
  ಆಗ (ಆರಂಭ >= 0)
  {
    ಪೂರ್ಣಾಂಕ ಮಗು, ಬೇರು = ಆರಂಭ;
    ಗಾಗಿ ( ; ; )
    {
      ಆದರೆ ((ಮಗು = (ಬೇರು << 1) + 1) >= ಗಾತ್ರ_2)
        ನಿಲ್ಲಿಸು;
      ಮಗು += (((ಮಗು + 1) < ಗಾತ್ರ_2) && (mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[ಮಗು], pIndices[ಮಗು + 1])));
      ಆದರೆ (!mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[ಬೇರು], pIndices[ಮಗು]))
        ನಿಲ್ಲಿಸು;
      MZ_ಅದಲುಬದಲು_UINT32(pIndices[ಬೇರು], pIndices[ಮಗು]); ಬೇರು = ಮಗು;
    }
    ಆರಂಭ--;
  }

  ಕೊನೆ = ಗಾತ್ರ_2 - 1;
  ಆಗ (ಕೊನೆ > 0)
  {
    ಪೂರ್ಣಾಂಕ ಮಗು, ಬೇರು = 0;
    MZ_ಅದಲುಬದಲು_UINT32(pIndices[ಕೊನೆ], pIndices[0]);
    ಗಾಗಿ ( ; ; )
    {
      ಆದರೆ ((ಮಗು = (ಬೇರು << 1) + 1) >= ಕೊನೆ)
        ನಿಲ್ಲಿಸು;
      ಮಗು += (((ಮಗು + 1) < ಕೊನೆ) && mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[ಮಗು], pIndices[ಮಗು + 1]));
      ಆದರೆ (!mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[ಬೇರು], pIndices[ಮಗು]))
        ನಿಲ್ಲಿಸು;
      MZ_ಅದಲುಬದಲು_UINT32(pIndices[ಬೇರು], pIndices[ಮಗು]); ಬೇರು = ಮಗು;
    }
    ಕೊನೆ--;
  }
}

ಸ್ಥಿರ mz_bool mz_zip_reader_read_central_dir(mz_zip_archive *pZip, mz_uint32 flags)
{
  mz_uint cdir_ಗಾತ್ರ, ಅಂಕೆ_this_disk, cdir_disk_ಸೂಚ್ಯಂಕ;
  mz_uint64 cdir_ofs;
  mz_int64 cur_file_ofs;
  ಸ್ಥಿರಾಂಕ mz_uint8 *p;
  mz_uint32 buf_u32[4096 / ಗಾತ್ರ(mz_uint32)]; mz_uint8 *pBuf = (mz_uint8 *)buf_u32;
  mz_bool ವಿಂಗಡಿಸು_central_dir = ((flags & MZ_ZIP_FLAG_DO_NOT_ವಿಂಗಡಿಸು_CENTRAL_DIRECTORY) == 0);
  // Basic sanity checks - reject files which are too small, and check the first 4 bytes of the file to make sure a local header is there.
  ಆದರೆ (pZip->m_archive_ಗಾತ್ರ < MZ_ZIP_ಕೊನೆ_ದ_CENTRAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  // Find the end of central directory record by scanning the file from the end towards the beginning.
  cur_file_ofs = MZ_MAX((mz_int64)pZip->m_archive_ಗಾತ್ರ - (mz_int64)ಗಾತ್ರ(buf_u32), 0);
  ಗಾಗಿ ( ; ; )
  {
    ಪೂರ್ಣಾಂಕ i, n = (ಪೂರ್ಣಾಂಕ)MZ_MIN(ಗಾತ್ರ(buf_u32), pZip->m_archive_ಗಾತ್ರ - cur_file_ofs);
    ಆದರೆ (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, n) != (mz_uint)n)
      ಹಿಂತಿರುಗಿ MZ_FALSE;
    ಗಾಗಿ (i = n - 4; i >= 0; --i)
      ಆದರೆ (MZ_READ_LE32(pBuf + i) == MZ_ZIP_ಕೊನೆ_ದ_CENTRAL_DIR_ಶೀರ್ಷಿಕೆ_SIG)
        ನಿಲ್ಲಿಸು;
    ಆದರೆ (i >= 0)
    {
      cur_file_ofs += i;
      ನಿಲ್ಲಿಸು;
    }
    ಆದರೆ ((!cur_file_ofs) || ((pZip->m_archive_ಗಾತ್ರ - cur_file_ofs) >= (0xFFFF + MZ_ZIP_ಕೊನೆ_ದ_CENTRAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ)))
      ಹಿಂತಿರುಗಿ MZ_FALSE;
    cur_file_ofs = MZ_MAX(cur_file_ofs - (ಗಾತ್ರ(buf_u32) - 3), 0);
  }
  // Read and verify the end of central directory record.
  ಆದರೆ (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, MZ_ZIP_ಕೊನೆ_ದ_CENTRAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ) != MZ_ZIP_ಕೊನೆ_ದ_CENTRAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  ಆದರೆ ((MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_SIG_OFS) != MZ_ZIP_ಕೊನೆ_ದ_CENTRAL_DIR_ಶೀರ್ಷಿಕೆ_SIG) ||
      ((pZip->m_ಒಟ್ಟು_files = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_CDIR_ಒಟ್ಟು_ENTRIES_OFS)) != MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_CDIR_ಅಂಕೆ_ENTRIES_ON_DISK_OFS)))
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  ಅಂಕೆ_this_disk = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_ಅಂಕೆ_THIS_DISK_OFS);
  cdir_disk_ಸೂಚ್ಯಂಕ = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_ಅಂಕೆ_DISK_CDIR_OFS);
  ಆದರೆ (((ಅಂಕೆ_this_disk | cdir_disk_ಸೂಚ್ಯಂಕ) != 0) && ((ಅಂಕೆ_this_disk != 1) || (cdir_disk_ಸೂಚ್ಯಂಕ != 1)))
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  ಆದರೆ ((cdir_ಗಾತ್ರ = MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_CDIR_ಗಾತ್ರ_OFS)) < pZip->m_ಒಟ್ಟು_files * MZ_ZIP_CENTRAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  cdir_ofs = MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_CDIR_OFS_OFS);
  ಆದರೆ ((cdir_ofs + (mz_uint64)cdir_ಗಾತ್ರ) > pZip->m_archive_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  pZip->m_central_directory_file_ofs = cdir_ofs;

  ಆದರೆ (pZip->m_ಒಟ್ಟು_files)
  {
     mz_uint i, n;

    // Read the entire central directory into a heap block, and allocate another heap block to hold the unsorted central dir file record offsets, and another to hold the sorted indices.
    ಆದರೆ ((!mz_zip_array_resize(pZip, &pZip->m_pState->m_central_dir, cdir_ಗಾತ್ರ, MZ_FALSE)) ||
        (!mz_zip_array_resize(pZip, &pZip->m_pState->m_central_dir_offsets, pZip->m_ಒಟ್ಟು_files, MZ_FALSE)))
      ಹಿಂತಿರುಗಿ MZ_FALSE;

    ಆದರೆ (ವಿಂಗಡಿಸು_central_dir)
    {
      ಆದರೆ (!mz_zip_array_resize(pZip, &pZip->m_pState->m_sorted_central_dir_offsets, pZip->m_ಒಟ್ಟು_files, MZ_FALSE))
        ಹಿಂತಿರುಗಿ MZ_FALSE;
    }

    ಆದರೆ (pZip->m_pRead(pZip->m_pIO_opaque, cdir_ofs, pZip->m_pState->m_central_dir.m_p, cdir_ಗಾತ್ರ) != cdir_ಗಾತ್ರ)
      ಹಿಂತಿರುಗಿ MZ_FALSE;

    // Now create an index into the central directory file records, do some basic sanity checking on each record, and check for zip64 entries (which are not yet supported).
    p = (ಸ್ಥಿರಾಂಕ mz_uint8 *)pZip->m_pState->m_central_dir.m_p;
    ಗಾಗಿ (n = cdir_ಗಾತ್ರ, i = 0; i < pZip->m_ಒಟ್ಟು_files; ++i)
    {
      mz_uint ಒಟ್ಟು_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ, comp_ಗಾತ್ರ, decomp_ಗಾತ್ರ, disk_ಸೂಚ್ಯಂಕ;
      ಆದರೆ ((n < MZ_ZIP_CENTRAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ) || (MZ_READ_LE32(p) != MZ_ZIP_CENTRAL_DIR_ಶೀರ್ಷಿಕೆ_SIG))
        ಹಿಂತಿರುಗಿ MZ_FALSE;
      MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, i) = (mz_uint32)(p - (ಸ್ಥಿರಾಂಕ mz_uint8 *)pZip->m_pState->m_central_dir.m_p);
      ಆದರೆ (ವಿಂಗಡಿಸು_central_dir)
        MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_sorted_central_dir_offsets, mz_uint32, i) = i;
      comp_ಗಾತ್ರ = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_ಗಾತ್ರ_OFS);
      decomp_ಗಾತ್ರ = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_ಗಾತ್ರ_OFS);
      ಆದರೆ (((!MZ_READ_LE32(p + MZ_ZIP_CDH_ವಿಧಾನ_OFS)) && (decomp_ಗಾತ್ರ != comp_ಗಾತ್ರ)) || (decomp_ಗಾತ್ರ && !comp_ಗಾತ್ರ) || (decomp_ಗಾತ್ರ == 0xFFFFFFFF) || (comp_ಗಾತ್ರ == 0xFFFFFFFF))
        ಹಿಂತಿರುಗಿ MZ_FALSE;
      disk_ಸೂಚ್ಯಂಕ = MZ_READ_LE16(p + MZ_ZIP_CDH_DISK_ಆರಂಭ_OFS);
      ಆದರೆ ((disk_ಸೂಚ್ಯಂಕ != ಅಂಕೆ_this_disk) && (disk_ಸೂಚ್ಯಂಕ != 1))
        ಹಿಂತಿರುಗಿ MZ_FALSE;
      ಆದರೆ (((mz_uint64)MZ_READ_LE32(p + MZ_ZIP_CDH_LOCAL_ಶೀರ್ಷಿಕೆ_OFS) + MZ_ZIP_LOCAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ + comp_ಗಾತ್ರ) > pZip->m_archive_ಗಾತ್ರ)
        ಹಿಂತಿರುಗಿ MZ_FALSE;
      ಆದರೆ ((ಒಟ್ಟು_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ = MZ_ZIP_CENTRAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ + MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_EXTRA_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_COMMENT_LEN_OFS)) > n)
        ಹಿಂತಿರುಗಿ MZ_FALSE;
      n -= ಒಟ್ಟು_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ; p += ಒಟ್ಟು_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ;
    }
  }

  ಆದರೆ (ವಿಂಗಡಿಸು_central_dir)
    mz_zip_reader_ವಿಂಗಡಿಸು_central_dir_offsets_by_filename(pZip);

  ಹಿಂತಿರುಗಿ MZ_TRUE;
}

mz_bool mz_zip_reader_init(mz_zip_archive *pZip, mz_uint64 ಗಾತ್ರ_2, mz_uint32 flags)
{
  ಆದರೆ ((!pZip) || (!pZip->m_pRead))
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  ಆದರೆ (!mz_zip_reader_init_ಆಂತರಿಕ(pZip, flags))
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  pZip->m_archive_ಗಾತ್ರ = ಗಾತ್ರ_2;
  ಆದರೆ (!mz_zip_reader_read_central_dir(pZip, flags))
  {
    mz_zip_reader_ಕೊನೆ(pZip);
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  }
  ಹಿಂತಿರುಗಿ MZ_TRUE;
}

ಸ್ಥಿರ size_t mz_zip_mem_read_func(ಶೂನ್ಯ *pOpaque, mz_uint64 file_ofs, ಶೂನ್ಯ *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  size_t s = (file_ofs >= pZip->m_archive_ಗಾತ್ರ) ? 0 : (size_t)MZ_MIN(pZip->m_archive_ಗಾತ್ರ - file_ofs, n);
  ಸ್ಮರಣೆ_ನಕಲು(pBuf, (ಸ್ಥಿರಾಂಕ mz_uint8 *)pZip->m_pState->m_pMem + file_ofs, s);
  ಹಿಂತಿರುಗಿ s;
}

mz_bool mz_zip_reader_init_mem(mz_zip_archive *pZip, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *pMem, size_t ಗಾತ್ರ_2, mz_uint32 flags)
{
  ಆದರೆ (!mz_zip_reader_init_ಆಂತರಿಕ(pZip, flags))
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  pZip->m_archive_ಗಾತ್ರ = ಗಾತ್ರ_2;
  pZip->m_pRead = mz_zip_mem_read_func;
  pZip->m_pIO_opaque = pZip;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
  pZip->m_pState->m_pMem = const_cast<ಶೂನ್ಯ *>(pMem);
#ಇಲ್ಲದಿದ್ದರೆ
  pZip->m_pState->m_pMem = (ಶೂನ್ಯ *)pMem;
#ಆದರೆ_ಅಂತ್ಯ
  pZip->m_pState->m_mem_ಗಾತ್ರ = ಗಾತ್ರ_2;
  ಆದರೆ (!mz_zip_reader_read_central_dir(pZip, flags))
  {
    mz_zip_reader_ಕೊನೆ(pZip);
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  }
  ಹಿಂತಿರುಗಿ MZ_TRUE;
}

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_STDIO
ಸ್ಥಿರ size_t mz_zip_file_read_func(ಶೂನ್ಯ *pOpaque, mz_uint64 file_ofs, ಶೂನ್ಯ *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_int64 cur_ofs = MZ_FTELL64(pZip->m_pState->m_pFile);
  ಆದರೆ (((mz_int64)file_ofs < 0) || (((cur_ofs != (mz_int64)file_ofs)) && (MZ_FSEEK64(pZip->m_pState->m_pFile, (mz_int64)file_ofs, SEEK_SET))))
    ಹಿಂತಿರುಗಿ 0;
  ಹಿಂತಿರುಗಿ MZ_FREAD(pBuf, 1, n, pZip->m_pState->m_pFile);
}

mz_bool mz_zip_reader_init_file(mz_zip_archive *pZip, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pFilename, mz_uint32 flags)
{
  mz_uint64 file_ಗಾತ್ರ;
  MZ_FILE *pFile = MZ_FOPEN(pFilename, "rb");
  ಆದರೆ (!pFile)
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  ಆದರೆ (MZ_FSEEK64(pFile, 0, SEEK_END))
  {
    MZ_FCLOSE(pFile);
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  }
  file_ಗಾತ್ರ = MZ_FTELL64(pFile);
  ಆದರೆ (!mz_zip_reader_init_ಆಂತರಿಕ(pZip, flags))
  {
    MZ_FCLOSE(pFile);
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  }
  pZip->m_pRead = mz_zip_file_read_func;
  pZip->m_pIO_opaque = pZip;
  pZip->m_pState->m_pFile = pFile;
  pZip->m_archive_ಗಾತ್ರ = file_ಗಾತ್ರ;
  ಆದರೆ (!mz_zip_reader_read_central_dir(pZip, flags))
  {
    mz_zip_reader_ಕೊನೆ(pZip);
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  }
  ಹಿಂತಿರುಗಿ MZ_TRUE;
}
#ಆದರೆ_ಅಂತ್ಯ // #ifndef MINIZ_NO_STDIO

mz_uint mz_zip_reader_get_ಅಂಕೆ_files(mz_zip_archive *pZip)
{
  ಹಿಂತಿರುಗಿ pZip ? pZip->m_ಒಟ್ಟು_files : 0;
}

ಸ್ಥಿರ MZ_FORCEINLINE ಸ್ಥಿರಾಂಕ mz_uint8 *mz_zip_reader_get_cdh(mz_zip_archive *pZip, mz_uint file_ಸೂಚ್ಯಂಕ)
{
  ಆದರೆ ((!pZip) || (!pZip->m_pState) || (file_ಸೂಚ್ಯಂಕ >= pZip->m_ಒಟ್ಟು_files) || (pZip->m_zip_ಬಹುಲಕ != MZ_ZIP_ಬಹುಲಕ_READING))
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
  ಹಿಂತಿರುಗಿ &MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_ಸೂಚ್ಯಂಕ));
}

mz_bool mz_zip_reader_is_file_encrypted(mz_zip_archive *pZip, mz_uint file_ಸೂಚ್ಯಂಕ)
{
  mz_uint m_ಬಿಟ್_flag;
  ಸ್ಥಿರಾಂಕ mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_ಸೂಚ್ಯಂಕ);
  ಆದರೆ (!p)
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  m_ಬಿಟ್_flag = MZ_READ_LE16(p + MZ_ZIP_CDH_ಬಿಟ್_FLAG_OFS);
  ಹಿಂತಿರುಗಿ (m_ಬಿಟ್_flag & 1);
}

mz_bool mz_zip_reader_is_file_a_directory(mz_zip_archive *pZip, mz_uint file_ಸೂಚ್ಯಂಕ)
{
  mz_uint filename_len, external_attr;
  ಸ್ಥಿರಾಂಕ mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_ಸೂಚ್ಯಂಕ);
  ಆದರೆ (!p)
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  // First see if the filename ends with a '/' character.
  filename_len = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  ಆದರೆ (filename_len)
  {
    ಆದರೆ (*(p + MZ_ZIP_CENTRAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ + filename_len - 1) == '/')
      ಹಿಂತಿರುಗಿ MZ_TRUE;
  }

  // Bugfix: This code was also checking if the internal attribute was non-zero, which wasn't correct.
  // Most/all zip writers (hopefully) set DOS file/directory attributes in the low 16-bits, so check for the DOS directory flag and ignore the source OS ID in the created by field.
  // FIXME: Remove this check? Is it necessary - we already check the filename.
  external_attr = MZ_READ_LE32(p + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS);
  ಆದರೆ ((external_attr & 0x10) != 0)
    ಹಿಂತಿರುಗಿ MZ_TRUE;

  ಹಿಂತಿರುಗಿ MZ_FALSE;
}

mz_bool mz_zip_reader_file_stat(mz_zip_archive *pZip, mz_uint file_ಸೂಚ್ಯಂಕ, mz_zip_archive_file_stat *pStat)
{
  mz_uint n;
  ಸ್ಥಿರಾಂಕ mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_ಸೂಚ್ಯಂಕ);
  ಆದರೆ ((!p) || (!pStat))
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  // Unpack the central directory record.
  pStat->m_file_ಸೂಚ್ಯಂಕ = file_ಸೂಚ್ಯಂಕ;
  pStat->m_central_dir_ofs = MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_ಸೂಚ್ಯಂಕ);
  pStat->m_ಆವೃತ್ತಿ_made_by = MZ_READ_LE16(p + MZ_ZIP_CDH_ಆವೃತ್ತಿ_MADE_BY_OFS);
  pStat->m_ಆವೃತ್ತಿ_needed = MZ_READ_LE16(p + MZ_ZIP_CDH_ಆವೃತ್ತಿ_NEEDED_OFS);
  pStat->m_ಬಿಟ್_flag = MZ_READ_LE16(p + MZ_ZIP_CDH_ಬಿಟ್_FLAG_OFS);
  pStat->m_ವಿಧಾನ = MZ_READ_LE16(p + MZ_ZIP_CDH_ವಿಧಾನ_OFS);
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_ಸಮಯ
  pStat->m_ಸಮಯ = mz_zip_dos_ಗಮ್ಯ_ಸಮಯ_t(MZ_READ_LE16(p + MZ_ZIP_CDH_FILE_ಸಮಯ_OFS), MZ_READ_LE16(p + MZ_ZIP_CDH_FILE_DATE_OFS));
#ಆದರೆ_ಅಂತ್ಯ
  pStat->m_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32 = MZ_READ_LE32(p + MZ_ZIP_CDH_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_OFS);
  pStat->m_comp_ಗಾತ್ರ = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_ಗಾತ್ರ_OFS);
  pStat->m_uncomp_ಗಾತ್ರ = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_ಗಾತ್ರ_OFS);
  pStat->m_ಆಂತರಿಕ_attr = MZ_READ_LE16(p + MZ_ZIP_CDH_ಆಂತರಿಕ_ATTR_OFS);
  pStat->m_external_attr = MZ_READ_LE32(p + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS);
  pStat->m_local_ಶೀರ್ಷಿಕೆ_ofs = MZ_READ_LE32(p + MZ_ZIP_CDH_LOCAL_ಶೀರ್ಷಿಕೆ_OFS);

  // Copy as much of the filename and comment as possible.
  n = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS); n = MZ_MIN(n, MZ_ZIP_MAX_ARCHIVE_FILENAME_ಗಾತ್ರ - 1);
  ಸ್ಮರಣೆ_ನಕಲು(pStat->m_filename, p + MZ_ZIP_CENTRAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ, n); pStat->m_filename[n] = '\0';

  n = MZ_READ_LE16(p + MZ_ZIP_CDH_COMMENT_LEN_OFS); n = MZ_MIN(n, MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_ಗಾತ್ರ - 1);
  pStat->m_comment_ಗಾತ್ರ = n;
  ಸ್ಮರಣೆ_ನಕಲು(pStat->m_comment, p + MZ_ZIP_CENTRAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ + MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_EXTRA_LEN_OFS), n); pStat->m_comment[n] = '\0';

  ಹಿಂತಿರುಗಿ MZ_TRUE;
}

mz_uint mz_zip_reader_get_filename(mz_zip_archive *pZip, mz_uint file_ಸೂಚ್ಯಂಕ, ಅಕ್ಷರ *pFilename, mz_uint filename_buf_ಗಾತ್ರ)
{
  mz_uint n;
  ಸ್ಥಿರಾಂಕ mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_ಸೂಚ್ಯಂಕ);
  ಆದರೆ (!p) { ಆದರೆ (filename_buf_ಗಾತ್ರ) pFilename[0] = '\0'; ಹಿಂತಿರುಗಿ 0; }
  n = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  ಆದರೆ (filename_buf_ಗಾತ್ರ)
  {
    n = MZ_MIN(n, filename_buf_ಗಾತ್ರ - 1);
    ಸ್ಮರಣೆ_ನಕಲು(pFilename, p + MZ_ZIP_CENTRAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ, n);
    pFilename[n] = '\0';
  }
  ಹಿಂತಿರುಗಿ n + 1;
}

ಸ್ಥಿರ MZ_FORCEINLINE mz_bool mz_zip_reader_string_equal(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pA, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pB, mz_uint len, mz_uint flags)
{
  mz_uint i;
  ಆದರೆ (flags & MZ_ZIP_FLAG_CASE_SENSITIVE)
    ಹಿಂತಿರುಗಿ 0 == memcmp(pA, pB, len);
  ಗಾಗಿ (i = 0; i < len; ++i)
    ಆದರೆ (MZ_TOLOWER(pA[i]) != MZ_TOLOWER(pB[i]))
      ಹಿಂತಿರುಗಿ MZ_FALSE;
  ಹಿಂತಿರುಗಿ MZ_TRUE;
}

ಸ್ಥಿರ MZ_FORCEINLINE ಪೂರ್ಣಾಂಕ mz_zip_reader_filename_compare(ಸ್ಥಿರಾಂಕ mz_zip_array *pCentral_dir_array, ಸ್ಥಿರಾಂಕ mz_zip_array *pCentral_dir_offsets, mz_uint l_ಸೂಚ್ಯಂಕ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pR, mz_uint r_len)
{
  ಸ್ಥಿರಾಂಕ mz_uint8 *pL = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, l_ಸೂಚ್ಯಂಕ)), *pE;
  mz_uint l_len = MZ_READ_LE16(pL + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  mz_uint8 l = 0, r = 0;
  pL += MZ_ZIP_CENTRAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ;
  pE = pL + MZ_MIN(l_len, r_len);
  ಆಗ (pL < pE)
  {
    ಆದರೆ ((l = MZ_TOLOWER(*pL)) != (r = MZ_TOLOWER(*pR)))
      ನಿಲ್ಲಿಸು;
    pL++; pR++;
  }
  ಹಿಂತಿರುಗಿ (pL == pE) ? (ಪೂರ್ಣಾಂಕ)(l_len - r_len) : (l - r);
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ mz_zip_reader_locate_file_ದ್ವಿಮಾನ_ಹುಡುಕು(mz_zip_archive *pZip, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pFilename)
{
  mz_zip_ಆಂತರಿಕ_state *pState = pZip->m_pState;
  ಸ್ಥಿರಾಂಕ mz_zip_array *pCentral_dir_offsets = &pState->m_central_dir_offsets;
  ಸ್ಥಿರಾಂಕ mz_zip_array *pCentral_dir = &pState->m_central_dir;
  mz_uint32 *pIndices = &MZ_ZIP_ARRAY_ELEMENT(&pState->m_sorted_central_dir_offsets, mz_uint32, 0);
  ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ ಗಾತ್ರ_2 = pZip->m_ಒಟ್ಟು_files;
  ಸ್ಥಿರಾಂಕ mz_uint filename_len = (mz_uint)ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(pFilename);
  ಪೂರ್ಣಾಂಕ l = 0, h = ಗಾತ್ರ_2 - 1;
  ಆಗ (l <= h)
  {
    ಪೂರ್ಣಾಂಕ m = (l + h) >> 1, file_ಸೂಚ್ಯಂಕ = pIndices[m], comp = mz_zip_reader_filename_compare(pCentral_dir, pCentral_dir_offsets, file_ಸೂಚ್ಯಂಕ, pFilename, filename_len);
    ಆದರೆ (!comp)
      ಹಿಂತಿರುಗಿ file_ಸೂಚ್ಯಂಕ;
    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (comp < 0)
      l = m + 1;
    ಇಲ್ಲದಿದ್ದರೆ
      h = m - 1;
  }
  ಹಿಂತಿರುಗಿ -1;
}

ಪೂರ್ಣಾಂಕ mz_zip_reader_locate_file(mz_zip_archive *pZip, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pName, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pComment, mz_uint flags)
{
  mz_uint file_ಸೂಚ್ಯಂಕ; size_t name_len, comment_len;
  ಆದರೆ ((!pZip) || (!pZip->m_pState) || (!pName) || (pZip->m_zip_ಬಹುಲಕ != MZ_ZIP_ಬಹುಲಕ_READING))
    ಹಿಂತಿರುಗಿ -1;
  ಆದರೆ (((flags & (MZ_ZIP_FLAG_IGNORE_ಮಾರ್ಗ | MZ_ZIP_FLAG_CASE_SENSITIVE)) == 0) && (!pComment) && (pZip->m_pState->m_sorted_central_dir_offsets.m_ಗಾತ್ರ))
    ಹಿಂತಿರುಗಿ mz_zip_reader_locate_file_ದ್ವಿಮಾನ_ಹುಡುಕು(pZip, pName);
  name_len = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(pName); ಆದರೆ (name_len > 0xFFFF) ಹಿಂತಿರುಗಿ -1;
  comment_len = pComment ? ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(pComment) : 0; ಆದರೆ (comment_len > 0xFFFF) ಹಿಂತಿರುಗಿ -1;
  ಗಾಗಿ (file_ಸೂಚ್ಯಂಕ = 0; file_ಸೂಚ್ಯಂಕ < pZip->m_ಒಟ್ಟು_files; file_ಸೂಚ್ಯಂಕ++)
  {
    ಸ್ಥಿರಾಂಕ mz_uint8 *p_ಶೀರ್ಷಿಕೆ = &MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_ಸೂಚ್ಯಂಕ));
    mz_uint filename_len = MZ_READ_LE16(p_ಶೀರ್ಷಿಕೆ + MZ_ZIP_CDH_FILENAME_LEN_OFS);
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pFilename = (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *)p_ಶೀರ್ಷಿಕೆ + MZ_ZIP_CENTRAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ;
    ಆದರೆ (filename_len < name_len)
      ಮುಂದುವರಿ;
    ಆದರೆ (comment_len)
    {
      mz_uint file_extra_len = MZ_READ_LE16(p_ಶೀರ್ಷಿಕೆ + MZ_ZIP_CDH_EXTRA_LEN_OFS), file_comment_len = MZ_READ_LE16(p_ಶೀರ್ಷಿಕೆ + MZ_ZIP_CDH_COMMENT_LEN_OFS);
      ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pFile_comment = pFilename + filename_len + file_extra_len;
      ಆದರೆ ((file_comment_len != comment_len) || (!mz_zip_reader_string_equal(pComment, pFile_comment, file_comment_len, flags)))
        ಮುಂದುವರಿ;
    }
    ಆದರೆ ((flags & MZ_ZIP_FLAG_IGNORE_ಮಾರ್ಗ) && (filename_len))
    {
      ಪೂರ್ಣಾಂಕ ofs = filename_len - 1;
      ಮಾಡು
      {
        ಆದರೆ ((pFilename[ofs] == '/') || (pFilename[ofs] == '\\') || (pFilename[ofs] == ':'))
          ನಿಲ್ಲಿಸು;
      } ಆಗ (--ofs >= 0);
      ofs++;
      pFilename += ofs; filename_len -= ofs;
    }
    ಆದರೆ ((filename_len == name_len) && (mz_zip_reader_string_equal(pName, pFilename, filename_len, flags)))
      ಹಿಂತಿರುಗಿ file_ಸೂಚ್ಯಂಕ;
  }
  ಹಿಂತಿರುಗಿ -1;
}

mz_bool mz_zip_reader_ಹೊರತೆಗೆ_ಗಮ್ಯ_mem_no_alloc(mz_zip_archive *pZip, mz_uint file_ಸೂಚ್ಯಂಕ, ಶೂನ್ಯ *pBuf, size_t buf_ಗಾತ್ರ_2, mz_uint flags, ಶೂನ್ಯ *pUser_read_buf, size_t user_read_buf_ಗಾತ್ರ)
{
  ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_2 = TINFL_ಸ್ಥಿತಿ_ಮುಗಿದ;
  mz_uint64 needed_ಗಾತ್ರ, cur_file_ofs, comp_ಉಳಿದ, ಹೊರಹೋಗು_buf_ofs = 0, read_buf_ಗಾತ್ರ, read_buf_ofs = 0, read_buf_avail;
  mz_zip_archive_file_stat file_stat;
  ಶೂನ್ಯ *pRead_buf;
  mz_uint32 local_ಶೀರ್ಷಿಕೆ_u32[(MZ_ZIP_LOCAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ + ಗಾತ್ರ(mz_uint32) - 1) / ಗಾತ್ರ(mz_uint32)]; mz_uint8 *p_Local_ಶೀರ್ಷಿಕೆ = (mz_uint8 *)local_ಶೀರ್ಷಿಕೆ_u32;
  tinfl_decompressor inflator;

  ಆದರೆ ((buf_ಗಾತ್ರ_2) && (!pBuf))
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  ಆದರೆ (!mz_zip_reader_file_stat(pZip, file_ಸೂಚ್ಯಂಕ, &file_stat))
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  // Empty file, or a directory (but not always a directory - I've seen odd zips with directories that have compressed data which inflates to 0 bytes)
  ಆದರೆ (!file_stat.m_comp_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ MZ_TRUE;

  // Entry is a subdirectory (I've seen old zips with dir entries which have compressed deflate data which inflates to 0 bytes, but these entries claim to uncompress to 512 bytes in the headers).
  // I'm torn how to handle this case - should it fail instead?
  ಆದರೆ (mz_zip_reader_is_file_a_directory(pZip, file_ಸೂಚ್ಯಂಕ))
    ಹಿಂತಿರುಗಿ MZ_TRUE;

  // Encryption and patch files are not supported.
  ಆದರೆ (file_stat.m_ಬಿಟ್_flag & (1 | 32))
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  // This function only supports stored and deflate.
  ಆದರೆ ((!(flags & MZ_ZIP_FLAG_COMPRESSED_ದತ್ತಾಂಶ)) && (file_stat.m_ವಿಧಾನ != 0) && (file_stat.m_ವಿಧಾನ != MZ_DEFLATED))
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  // Ensure supplied output buffer is large enough.
  needed_ಗಾತ್ರ = (flags & MZ_ZIP_FLAG_COMPRESSED_ದತ್ತಾಂಶ) ? file_stat.m_comp_ಗಾತ್ರ : file_stat.m_uncomp_ಗಾತ್ರ;
  ಆದರೆ (buf_ಗಾತ್ರ_2 < needed_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  // Read and parse the local directory entry.
  cur_file_ofs = file_stat.m_local_ಶೀರ್ಷಿಕೆ_ofs;
  ಆದರೆ (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, p_Local_ಶೀರ್ಷಿಕೆ, MZ_ZIP_LOCAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ) != MZ_ZIP_LOCAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  ಆದರೆ (MZ_READ_LE32(p_Local_ಶೀರ್ಷಿಕೆ) != MZ_ZIP_LOCAL_DIR_ಶೀರ್ಷಿಕೆ_SIG)
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  cur_file_ofs += MZ_ZIP_LOCAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ + MZ_READ_LE16(p_Local_ಶೀರ್ಷಿಕೆ + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p_Local_ಶೀರ್ಷಿಕೆ + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  ಆದರೆ ((cur_file_ofs + file_stat.m_comp_ಗಾತ್ರ) > pZip->m_archive_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  ಆದರೆ ((flags & MZ_ZIP_FLAG_COMPRESSED_ದತ್ತಾಂಶ) || (!file_stat.m_ವಿಧಾನ))
  {
    // The file is stored or the caller has requested the compressed data.
    ಆದರೆ (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, (size_t)needed_ಗಾತ್ರ) != needed_ಗಾತ್ರ)
      ಹಿಂತಿರುಗಿ MZ_FALSE;
    ಹಿಂತಿರುಗಿ ((flags & MZ_ZIP_FLAG_COMPRESSED_ದತ್ತಾಂಶ) != 0) || (mz_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32(MZ_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_INIT, (ಸ್ಥಿರಾಂಕ mz_uint8 *)pBuf, (size_t)file_stat.m_uncomp_ಗಾತ್ರ) == file_stat.m_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32);
  }

  // Decompress the file either directly from memory or from a file input buffer.
  tinfl_init(&inflator);

  ಆದರೆ (pZip->m_pState->m_pMem)
  {
    // Read directly from the archive in memory.
    pRead_buf = (mz_uint8 *)pZip->m_pState->m_pMem + cur_file_ofs;
    read_buf_ಗಾತ್ರ = read_buf_avail = file_stat.m_comp_ಗಾತ್ರ;
    comp_ಉಳಿದ = 0;
  }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (pUser_read_buf)
  {
    // Use a user provided read buffer.
    ಆದರೆ (!user_read_buf_ಗಾತ್ರ)
      ಹಿಂತಿರುಗಿ MZ_FALSE;
    pRead_buf = (mz_uint8 *)pUser_read_buf;
    read_buf_ಗಾತ್ರ = user_read_buf_ಗಾತ್ರ;
    read_buf_avail = 0;
    comp_ಉಳಿದ = file_stat.m_comp_ಗಾತ್ರ;
  }
  ಇಲ್ಲದಿದ್ದರೆ
  {
    // Temporarily allocate a read buffer.
    read_buf_ಗಾತ್ರ = MZ_MIN(file_stat.m_comp_ಗಾತ್ರ, MZ_ZIP_MAX_IO_BUF_ಗಾತ್ರ);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _MSC_VER
    ಆದರೆ (((0, ಗಾತ್ರ(size_t) == ಗಾತ್ರ(mz_uint32))) && (read_buf_ಗಾತ್ರ > 0x7FFFFFFF))
#ಇಲ್ಲದಿದ್ದರೆ
    ಆದರೆ (((ಗಾತ್ರ(size_t) == ಗಾತ್ರ(mz_uint32))) && (read_buf_ಗಾತ್ರ > 0x7FFFFFFF))
#ಆದರೆ_ಅಂತ್ಯ
      ಹಿಂತಿರುಗಿ MZ_FALSE;
    ಆದರೆ (ಖಾಲಿ == (pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)read_buf_ಗಾತ್ರ)))
      ಹಿಂತಿರುಗಿ MZ_FALSE;
    read_buf_avail = 0;
    comp_ಉಳಿದ = file_stat.m_comp_ಗಾತ್ರ;
  }

  ಮಾಡು
  {
    size_t ಒಳ_buf_ಗಾತ್ರ, ಹೊರಹೋಗು_buf_ಗಾತ್ರ = (size_t)(file_stat.m_uncomp_ಗಾತ್ರ - ಹೊರಹೋಗು_buf_ofs);
    ಆದರೆ ((!read_buf_avail) && (!pZip->m_pState->m_pMem))
    {
      read_buf_avail = MZ_MIN(read_buf_ಗಾತ್ರ, comp_ಉಳಿದ);
      ಆದರೆ (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
      {
        ಸ್ಥಿತಿ_2 = TINFL_ಸ್ಥಿತಿ_FAILED;
        ನಿಲ್ಲಿಸು;
      }
      cur_file_ofs += read_buf_avail;
      comp_ಉಳಿದ -= read_buf_avail;
      read_buf_ofs = 0;
    }
    ಒಳ_buf_ಗಾತ್ರ = (size_t)read_buf_avail;
    ಸ್ಥಿತಿ_2 = tinfl_decompress(&inflator, (mz_uint8 *)pRead_buf + read_buf_ofs, &ಒಳ_buf_ಗಾತ್ರ, (mz_uint8 *)pBuf, (mz_uint8 *)pBuf + ಹೊರಹೋಗು_buf_ofs, &ಹೊರಹೋಗು_buf_ಗಾತ್ರ, TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF | (comp_ಉಳಿದ ? TINFL_FLAG_HAS_ಇನ್ನಷ್ಟು_ಒಳಹರಿವು : 0));
    read_buf_avail -= ಒಳ_buf_ಗಾತ್ರ;
    read_buf_ofs += ಒಳ_buf_ಗಾತ್ರ;
    ಹೊರಹೋಗು_buf_ofs += ಹೊರಹೋಗು_buf_ಗಾತ್ರ;
  } ಆಗ (ಸ್ಥಿತಿ_2 == TINFL_ಸ್ಥಿತಿ_NEEDS_ಇನ್ನಷ್ಟು_ಒಳಹರಿವು);

  ಆದರೆ (ಸ್ಥಿತಿ_2 == TINFL_ಸ್ಥಿತಿ_ಮುಗಿದ)
  {
    // Make sure the entire file was decompressed, and check its CRC.
    ಆದರೆ ((ಹೊರಹೋಗು_buf_ofs != file_stat.m_uncomp_ಗಾತ್ರ) || (mz_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32(MZ_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_INIT, (ಸ್ಥಿರಾಂಕ mz_uint8 *)pBuf, (size_t)file_stat.m_uncomp_ಗಾತ್ರ) != file_stat.m_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32))
      ಸ್ಥಿತಿ_2 = TINFL_ಸ್ಥಿತಿ_FAILED;
  }

  ಆದರೆ ((!pZip->m_pState->m_pMem) && (!pUser_read_buf))
    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);

  ಹಿಂತಿರುಗಿ ಸ್ಥಿತಿ_2 == TINFL_ಸ್ಥಿತಿ_ಮುಗಿದ;
}

mz_bool mz_zip_reader_ಹೊರತೆಗೆ_file_ಗಮ್ಯ_mem_no_alloc(mz_zip_archive *pZip, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pFilename, ಶೂನ್ಯ *pBuf, size_t buf_ಗಾತ್ರ_2, mz_uint flags, ಶೂನ್ಯ *pUser_read_buf, size_t user_read_buf_ಗಾತ್ರ)
{
  ಪೂರ್ಣಾಂಕ file_ಸೂಚ್ಯಂಕ = mz_zip_reader_locate_file(pZip, pFilename, ಖಾಲಿ, flags);
  ಆದರೆ (file_ಸೂಚ್ಯಂಕ < 0)
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  ಹಿಂತಿರುಗಿ mz_zip_reader_ಹೊರತೆಗೆ_ಗಮ್ಯ_mem_no_alloc(pZip, file_ಸೂಚ್ಯಂಕ, pBuf, buf_ಗಾತ್ರ_2, flags, pUser_read_buf, user_read_buf_ಗಾತ್ರ);
}

mz_bool mz_zip_reader_ಹೊರತೆಗೆ_ಗಮ್ಯ_mem(mz_zip_archive *pZip, mz_uint file_ಸೂಚ್ಯಂಕ, ಶೂನ್ಯ *pBuf, size_t buf_ಗಾತ್ರ_2, mz_uint flags)
{
  ಹಿಂತಿರುಗಿ mz_zip_reader_ಹೊರತೆಗೆ_ಗಮ್ಯ_mem_no_alloc(pZip, file_ಸೂಚ್ಯಂಕ, pBuf, buf_ಗಾತ್ರ_2, flags, ಖಾಲಿ, 0);
}

mz_bool mz_zip_reader_ಹೊರತೆಗೆ_file_ಗಮ್ಯ_mem(mz_zip_archive *pZip, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pFilename, ಶೂನ್ಯ *pBuf, size_t buf_ಗಾತ್ರ_2, mz_uint flags)
{
  ಹಿಂತಿರುಗಿ mz_zip_reader_ಹೊರತೆಗೆ_file_ಗಮ್ಯ_mem_no_alloc(pZip, pFilename, pBuf, buf_ಗಾತ್ರ_2, flags, ಖಾಲಿ, 0);
}

ಶೂನ್ಯ *mz_zip_reader_ಹೊರತೆಗೆ_ಗಮ್ಯ_ರಾಶಿ(mz_zip_archive *pZip, mz_uint file_ಸೂಚ್ಯಂಕ, size_t *p_ಗಾತ್ರ, mz_uint flags)
{
  mz_uint64 comp_ಗಾತ್ರ, uncomp_ಗಾತ್ರ, alloc_ಗಾತ್ರ_2;
  ಸ್ಥಿರಾಂಕ mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_ಸೂಚ್ಯಂಕ);
  ಶೂನ್ಯ *pBuf;

  ಆದರೆ (p_ಗಾತ್ರ)
    *p_ಗಾತ್ರ = 0;
  ಆದರೆ (!p)
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;

  comp_ಗಾತ್ರ = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_ಗಾತ್ರ_OFS);
  uncomp_ಗಾತ್ರ = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_ಗಾತ್ರ_OFS);

  alloc_ಗಾತ್ರ_2 = (flags & MZ_ZIP_FLAG_COMPRESSED_ದತ್ತಾಂಶ) ? comp_ಗಾತ್ರ : uncomp_ಗಾತ್ರ;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _MSC_VER
  ಆದರೆ (((0, ಗಾತ್ರ(size_t) == ಗಾತ್ರ(mz_uint32))) && (alloc_ಗಾತ್ರ_2 > 0x7FFFFFFF))
#ಇಲ್ಲದಿದ್ದರೆ
  ಆದರೆ (((ಗಾತ್ರ(size_t) == ಗಾತ್ರ(mz_uint32))) && (alloc_ಗಾತ್ರ_2 > 0x7FFFFFFF))
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
  ಆದರೆ (ಖಾಲಿ == (pBuf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)alloc_ಗಾತ್ರ_2)))
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;

  ಆದರೆ (!mz_zip_reader_ಹೊರತೆಗೆ_ಗಮ್ಯ_mem(pZip, file_ಸೂಚ್ಯಂಕ, pBuf, (size_t)alloc_ಗಾತ್ರ_2, flags))
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
  }

  ಆದರೆ (p_ಗಾತ್ರ) *p_ಗಾತ್ರ = (size_t)alloc_ಗಾತ್ರ_2;
  ಹಿಂತಿರುಗಿ pBuf;
}

ಶೂನ್ಯ *mz_zip_reader_ಹೊರತೆಗೆ_file_ಗಮ್ಯ_ರಾಶಿ(mz_zip_archive *pZip, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pFilename, size_t *p_ಗಾತ್ರ, mz_uint flags)
{
  ಪೂರ್ಣಾಂಕ file_ಸೂಚ್ಯಂಕ = mz_zip_reader_locate_file(pZip, pFilename, ಖಾಲಿ, flags);
  ಆದರೆ (file_ಸೂಚ್ಯಂಕ < 0)
  {
    ಆದರೆ (p_ಗಾತ್ರ) *p_ಗಾತ್ರ = 0;
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  }
  ಹಿಂತಿರುಗಿ mz_zip_reader_ಹೊರತೆಗೆ_ಗಮ್ಯ_ರಾಶಿ(pZip, file_ಸೂಚ್ಯಂಕ, p_ಗಾತ್ರ, flags);
}

mz_bool mz_zip_reader_ಹೊರತೆಗೆ_ಗಮ್ಯ_callback(mz_zip_archive *pZip, mz_uint file_ಸೂಚ್ಯಂಕ, mz_file_write_func pCallback, ಶೂನ್ಯ *pOpaque, mz_uint flags)
{
  ಪೂರ್ಣಾಂಕ ಸ್ಥಿತಿ_2 = TINFL_ಸ್ಥಿತಿ_ಮುಗಿದ; mz_uint file_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32 = MZ_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_INIT;
  mz_uint64 read_buf_ಗಾತ್ರ, read_buf_ofs = 0, read_buf_avail, comp_ಉಳಿದ, ಹೊರಹೋಗು_buf_ofs = 0, cur_file_ofs;
  mz_zip_archive_file_stat file_stat;
  ಶೂನ್ಯ *pRead_buf = ಖಾಲಿ; ಶೂನ್ಯ *pWrite_buf = ಖಾಲಿ;
  mz_uint32 local_ಶೀರ್ಷಿಕೆ_u32[(MZ_ZIP_LOCAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ + ಗಾತ್ರ(mz_uint32) - 1) / ಗಾತ್ರ(mz_uint32)]; mz_uint8 *p_Local_ಶೀರ್ಷಿಕೆ = (mz_uint8 *)local_ಶೀರ್ಷಿಕೆ_u32;

  ಆದರೆ (!mz_zip_reader_file_stat(pZip, file_ಸೂಚ್ಯಂಕ, &file_stat))
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  // Empty file, or a directory (but not always a directory - I've seen odd zips with directories that have compressed data which inflates to 0 bytes)
  ಆದರೆ (!file_stat.m_comp_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ MZ_TRUE;

  // Entry is a subdirectory (I've seen old zips with dir entries which have compressed deflate data which inflates to 0 bytes, but these entries claim to uncompress to 512 bytes in the headers).
  // I'm torn how to handle this case - should it fail instead?
  ಆದರೆ (mz_zip_reader_is_file_a_directory(pZip, file_ಸೂಚ್ಯಂಕ))
    ಹಿಂತಿರುಗಿ MZ_TRUE;

  // Encryption and patch files are not supported.
  ಆದರೆ (file_stat.m_ಬಿಟ್_flag & (1 | 32))
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  // This function only supports stored and deflate.
  ಆದರೆ ((!(flags & MZ_ZIP_FLAG_COMPRESSED_ದತ್ತಾಂಶ)) && (file_stat.m_ವಿಧಾನ != 0) && (file_stat.m_ವಿಧಾನ != MZ_DEFLATED))
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  // Read and parse the local directory entry.
  cur_file_ofs = file_stat.m_local_ಶೀರ್ಷಿಕೆ_ofs;
  ಆದರೆ (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, p_Local_ಶೀರ್ಷಿಕೆ, MZ_ZIP_LOCAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ) != MZ_ZIP_LOCAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  ಆದರೆ (MZ_READ_LE32(p_Local_ಶೀರ್ಷಿಕೆ) != MZ_ZIP_LOCAL_DIR_ಶೀರ್ಷಿಕೆ_SIG)
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  cur_file_ofs += MZ_ZIP_LOCAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ + MZ_READ_LE16(p_Local_ಶೀರ್ಷಿಕೆ + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p_Local_ಶೀರ್ಷಿಕೆ + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  ಆದರೆ ((cur_file_ofs + file_stat.m_comp_ಗಾತ್ರ) > pZip->m_archive_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  // Decompress the file either directly from memory or from a file input buffer.
  ಆದರೆ (pZip->m_pState->m_pMem)
  {
    pRead_buf = (mz_uint8 *)pZip->m_pState->m_pMem + cur_file_ofs;
    read_buf_ಗಾತ್ರ = read_buf_avail = file_stat.m_comp_ಗಾತ್ರ;
    comp_ಉಳಿದ = 0;
  }
  ಇಲ್ಲದಿದ್ದರೆ
  {
    read_buf_ಗಾತ್ರ = MZ_MIN(file_stat.m_comp_ಗಾತ್ರ, MZ_ZIP_MAX_IO_BUF_ಗಾತ್ರ);
    ಆದರೆ (ಖಾಲಿ == (pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)read_buf_ಗಾತ್ರ)))
      ಹಿಂತಿರುಗಿ MZ_FALSE;
    read_buf_avail = 0;
    comp_ಉಳಿದ = file_stat.m_comp_ಗಾತ್ರ;
  }

  ಆದರೆ ((flags & MZ_ZIP_FLAG_COMPRESSED_ದತ್ತಾಂಶ) || (!file_stat.m_ವಿಧಾನ))
  {
    // The file is stored or the caller has requested the compressed data.
    ಆದರೆ (pZip->m_pState->m_pMem)
    {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _MSC_VER
      ಆದರೆ (((0, ಗಾತ್ರ(size_t) == ಗಾತ್ರ(mz_uint32))) && (file_stat.m_comp_ಗಾತ್ರ > 0xFFFFFFFF))
#ಇಲ್ಲದಿದ್ದರೆ
      ಆದರೆ (((ಗಾತ್ರ(size_t) == ಗಾತ್ರ(mz_uint32))) && (file_stat.m_comp_ಗಾತ್ರ > 0xFFFFFFFF))
#ಆದರೆ_ಅಂತ್ಯ
        ಹಿಂತಿರುಗಿ MZ_FALSE;
      ಆದರೆ (pCallback(pOpaque, ಹೊರಹೋಗು_buf_ofs, pRead_buf, (size_t)file_stat.m_comp_ಗಾತ್ರ) != file_stat.m_comp_ಗಾತ್ರ)
        ಸ್ಥಿತಿ_2 = TINFL_ಸ್ಥಿತಿ_FAILED;
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!(flags & MZ_ZIP_FLAG_COMPRESSED_ದತ್ತಾಂಶ))
        file_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32 = (mz_uint32)mz_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32(file_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32, (ಸ್ಥಿರಾಂಕ mz_uint8 *)pRead_buf, (size_t)file_stat.m_comp_ಗಾತ್ರ);
      cur_file_ofs += file_stat.m_comp_ಗಾತ್ರ;
      ಹೊರಹೋಗು_buf_ofs += file_stat.m_comp_ಗಾತ್ರ;
      comp_ಉಳಿದ = 0;
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
      ಆಗ (comp_ಉಳಿದ)
      {
        read_buf_avail = MZ_MIN(read_buf_ಗಾತ್ರ, comp_ಉಳಿದ);
        ಆದರೆ (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
        {
          ಸ್ಥಿತಿ_2 = TINFL_ಸ್ಥಿತಿ_FAILED;
          ನಿಲ್ಲಿಸು;
        }

        ಆದರೆ (!(flags & MZ_ZIP_FLAG_COMPRESSED_ದತ್ತಾಂಶ))
          file_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32 = (mz_uint32)mz_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32(file_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32, (ಸ್ಥಿರಾಂಕ mz_uint8 *)pRead_buf, (size_t)read_buf_avail);

        ಆದರೆ (pCallback(pOpaque, ಹೊರಹೋಗು_buf_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
        {
          ಸ್ಥಿತಿ_2 = TINFL_ಸ್ಥಿತಿ_FAILED;
          ನಿಲ್ಲಿಸು;
        }
        cur_file_ofs += read_buf_avail;
        ಹೊರಹೋಗು_buf_ofs += read_buf_avail;
        comp_ಉಳಿದ -= read_buf_avail;
      }
    }
  }
  ಇಲ್ಲದಿದ್ದರೆ
  {
    tinfl_decompressor inflator;
    tinfl_init(&inflator);

    ಆದರೆ (ಖಾಲಿ == (pWrite_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, TINFL_LZ_DICT_ಗಾತ್ರ)))
      ಸ್ಥಿತಿ_2 = TINFL_ಸ್ಥಿತಿ_FAILED;
    ಇಲ್ಲದಿದ್ದರೆ
    {
      ಮಾಡು
      {
        mz_uint8 *pWrite_buf_cur = (mz_uint8 *)pWrite_buf + (ಹೊರಹೋಗು_buf_ofs & (TINFL_LZ_DICT_ಗಾತ್ರ - 1));
        size_t ಒಳ_buf_ಗಾತ್ರ, ಹೊರಹೋಗು_buf_ಗಾತ್ರ = TINFL_LZ_DICT_ಗಾತ್ರ - (ಹೊರಹೋಗು_buf_ofs & (TINFL_LZ_DICT_ಗಾತ್ರ - 1));
        ಆದರೆ ((!read_buf_avail) && (!pZip->m_pState->m_pMem))
        {
          read_buf_avail = MZ_MIN(read_buf_ಗಾತ್ರ, comp_ಉಳಿದ);
          ಆದರೆ (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
          {
            ಸ್ಥಿತಿ_2 = TINFL_ಸ್ಥಿತಿ_FAILED;
            ನಿಲ್ಲಿಸು;
          }
          cur_file_ofs += read_buf_avail;
          comp_ಉಳಿದ -= read_buf_avail;
          read_buf_ofs = 0;
        }

        ಒಳ_buf_ಗಾತ್ರ = (size_t)read_buf_avail;
        ಸ್ಥಿತಿ_2 = tinfl_decompress(&inflator, (ಸ್ಥಿರಾಂಕ mz_uint8 *)pRead_buf + read_buf_ofs, &ಒಳ_buf_ಗಾತ್ರ, (mz_uint8 *)pWrite_buf, pWrite_buf_cur, &ಹೊರಹೋಗು_buf_ಗಾತ್ರ, comp_ಉಳಿದ ? TINFL_FLAG_HAS_ಇನ್ನಷ್ಟು_ಒಳಹರಿವು : 0);
        read_buf_avail -= ಒಳ_buf_ಗಾತ್ರ;
        read_buf_ofs += ಒಳ_buf_ಗಾತ್ರ;

        ಆದರೆ (ಹೊರಹೋಗು_buf_ಗಾತ್ರ)
        {
          ಆದರೆ (pCallback(pOpaque, ಹೊರಹೋಗು_buf_ofs, pWrite_buf_cur, ಹೊರಹೋಗು_buf_ಗಾತ್ರ) != ಹೊರಹೋಗು_buf_ಗಾತ್ರ)
          {
            ಸ್ಥಿತಿ_2 = TINFL_ಸ್ಥಿತಿ_FAILED;
            ನಿಲ್ಲಿಸು;
          }
          file_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32 = (mz_uint32)mz_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32(file_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32, pWrite_buf_cur, ಹೊರಹೋಗು_buf_ಗಾತ್ರ);
          ಆದರೆ ((ಹೊರಹೋಗು_buf_ofs += ಹೊರಹೋಗು_buf_ಗಾತ್ರ) > file_stat.m_uncomp_ಗಾತ್ರ)
          {
            ಸ್ಥಿತಿ_2 = TINFL_ಸ್ಥಿತಿ_FAILED;
            ನಿಲ್ಲಿಸು;
          }
        }
      } ಆಗ ((ಸ್ಥಿತಿ_2 == TINFL_ಸ್ಥಿತಿ_NEEDS_ಇನ್ನಷ್ಟು_ಒಳಹರಿವು) || (ಸ್ಥಿತಿ_2 == TINFL_ಸ್ಥಿತಿ_HAS_ಇನ್ನಷ್ಟು_OUTPUT));
    }
  }

  ಆದರೆ ((ಸ್ಥಿತಿ_2 == TINFL_ಸ್ಥಿತಿ_ಮುಗಿದ) && (!(flags & MZ_ZIP_FLAG_COMPRESSED_ದತ್ತಾಂಶ)))
  {
    // Make sure the entire file was decompressed, and check its CRC.
    ಆದರೆ ((ಹೊರಹೋಗು_buf_ofs != file_stat.m_uncomp_ಗಾತ್ರ) || (file_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32 != file_stat.m_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32))
      ಸ್ಥಿತಿ_2 = TINFL_ಸ್ಥಿತಿ_FAILED;
  }

  ಆದರೆ (!pZip->m_pState->m_pMem)
    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
  ಆದರೆ (pWrite_buf)
    pZip->m_pFree(pZip->m_pAlloc_opaque, pWrite_buf);

  ಹಿಂತಿರುಗಿ ಸ್ಥಿತಿ_2 == TINFL_ಸ್ಥಿತಿ_ಮುಗಿದ;
}

mz_bool mz_zip_reader_ಹೊರತೆಗೆ_file_ಗಮ್ಯ_callback(mz_zip_archive *pZip, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pFilename, mz_file_write_func pCallback, ಶೂನ್ಯ *pOpaque, mz_uint flags)
{
  ಪೂರ್ಣಾಂಕ file_ಸೂಚ್ಯಂಕ = mz_zip_reader_locate_file(pZip, pFilename, ಖಾಲಿ, flags);
  ಆದರೆ (file_ಸೂಚ್ಯಂಕ < 0)
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  ಹಿಂತಿರುಗಿ mz_zip_reader_ಹೊರತೆಗೆ_ಗಮ್ಯ_callback(pZip, file_ಸೂಚ್ಯಂಕ, pCallback, pOpaque, flags);
}

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_STDIO
ಸ್ಥಿರ size_t mz_zip_file_write_callback(ಶೂನ್ಯ *pOpaque, mz_uint64 ofs, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *pBuf, size_t n)
{
  (ಶೂನ್ಯ)ofs; ಹಿಂತಿರುಗಿ MZ_FWRITE(pBuf, 1, n, (MZ_FILE*)pOpaque);
}

mz_bool mz_zip_reader_ಹೊರತೆಗೆ_ಗಮ್ಯ_file(mz_zip_archive *pZip, mz_uint file_ಸೂಚ್ಯಂಕ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pDst_filename, mz_uint flags)
{
  mz_bool ಸ್ಥಿತಿ_2;
  mz_zip_archive_file_stat file_stat;
  MZ_FILE *pFile;
  ಆದರೆ (!mz_zip_reader_file_stat(pZip, file_ಸೂಚ್ಯಂಕ, &file_stat))
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  pFile = MZ_FOPEN(pDst_filename, "wb");
  ಆದರೆ (!pFile)
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  ಸ್ಥಿತಿ_2 = mz_zip_reader_ಹೊರತೆಗೆ_ಗಮ್ಯ_callback(pZip, file_ಸೂಚ್ಯಂಕ, mz_zip_file_write_callback, pFile, flags);
  ಆದರೆ (MZ_FCLOSE(pFile) == EOF)
    ಹಿಂತಿರುಗಿ MZ_FALSE;
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_ಸಮಯ
  ಆದರೆ (ಸ್ಥಿತಿ_2)
    mz_zip_ಗಣ_file_times(pDst_filename, file_stat.m_ಸಮಯ, file_stat.m_ಸಮಯ);
#ಆದರೆ_ಅಂತ್ಯ
  ಹಿಂತಿರುಗಿ ಸ್ಥಿತಿ_2;
}
#ಆದರೆ_ಅಂತ್ಯ // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_reader_ಕೊನೆ(mz_zip_archive *pZip)
{
  ಆದರೆ ((!pZip) || (!pZip->m_pState) || (!pZip->m_pAlloc) || (!pZip->m_pFree) || (pZip->m_zip_ಬಹುಲಕ != MZ_ZIP_ಬಹುಲಕ_READING))
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  ಆದರೆ (pZip->m_pState)
  {
    mz_zip_ಆಂತರಿಕ_state *pState = pZip->m_pState; pZip->m_pState = ಖಾಲಿ;
    mz_zip_array_clear(pZip, &pState->m_central_dir);
    mz_zip_array_clear(pZip, &pState->m_central_dir_offsets);
    mz_zip_array_clear(pZip, &pState->m_sorted_central_dir_offsets);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_STDIO
    ಆದರೆ (pState->m_pFile)
    {
      MZ_FCLOSE(pState->m_pFile);
      pState->m_pFile = ಖಾಲಿ;
    }
#ಆದರೆ_ಅಂತ್ಯ // #ifndef MINIZ_NO_STDIO

    pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
  }
  pZip->m_zip_ಬಹುಲಕ = MZ_ZIP_ಬಹುಲಕ_INVALID;

  ಹಿಂತಿರುಗಿ MZ_TRUE;
}

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_STDIO
mz_bool mz_zip_reader_ಹೊರತೆಗೆ_file_ಗಮ್ಯ_file(mz_zip_archive *pZip, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pArchive_filename, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pDst_filename, mz_uint flags)
{
  ಪೂರ್ಣಾಂಕ file_ಸೂಚ್ಯಂಕ = mz_zip_reader_locate_file(pZip, pArchive_filename, ಖಾಲಿ, flags);
  ಆದರೆ (file_ಸೂಚ್ಯಂಕ < 0)
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  ಹಿಂತಿರುಗಿ mz_zip_reader_ಹೊರತೆಗೆ_ಗಮ್ಯ_file(pZip, file_ಸೂಚ್ಯಂಕ, pDst_filename, flags);
}
#ಆದರೆ_ಅಂತ್ಯ

// ------------------- .ZIP archive writing

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_ARCHIVE_WRITING_APIS

ಸ್ಥಿರ ಶೂನ್ಯ mz_write_le16(mz_uint8 *p, mz_uint16 v) { p[0] = (mz_uint8)v; p[1] = (mz_uint8)(v >> 8); }
ಸ್ಥಿರ ಶೂನ್ಯ mz_write_le32(mz_uint8 *p, mz_uint32 v) { p[0] = (mz_uint8)v; p[1] = (mz_uint8)(v >> 8); p[2] = (mz_uint8)(v >> 16); p[3] = (mz_uint8)(v >> 24); }
#ವ್ಯಾಖ್ಯಾನಿಸು MZ_WRITE_LE16(p, v) mz_write_le16((mz_uint8 *)(p), (mz_uint16)(v))
#ವ್ಯಾಖ್ಯಾನಿಸು MZ_WRITE_LE32(p, v) mz_write_le32((mz_uint8 *)(p), (mz_uint32)(v))

mz_bool mz_zip_writer_init(mz_zip_archive *pZip, mz_uint64 existing_ಗಾತ್ರ)
{
  ಆದರೆ ((!pZip) || (pZip->m_pState) || (!pZip->m_pWrite) || (pZip->m_zip_ಬಹುಲಕ != MZ_ZIP_ಬಹುಲಕ_INVALID))
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  ಆದರೆ (pZip->m_file_ಸ್ಥಾನಾಂತರ_alignment)
  {
    // Ensure user specified file offset alignment is a power of 2.
    ಆದರೆ (pZip->m_file_ಸ್ಥಾನಾಂತರ_alignment & (pZip->m_file_ಸ್ಥಾನಾಂತರ_alignment - 1))
      ಹಿಂತಿರುಗಿ MZ_FALSE;
  }

  ಆದರೆ (!pZip->m_pAlloc) pZip->m_pAlloc = def_alloc_func;
  ಆದರೆ (!pZip->m_pFree) pZip->m_pFree = def_free_func;
  ಆದರೆ (!pZip->m_pRealloc) pZip->m_pRealloc = def_realloc_func;

  pZip->m_zip_ಬಹುಲಕ = MZ_ZIP_ಬಹುಲಕ_WRITING;
  pZip->m_archive_ಗಾತ್ರ = existing_ಗಾತ್ರ;
  pZip->m_central_directory_file_ofs = 0;
  pZip->m_ಒಟ್ಟು_files = 0;

  ಆದರೆ (ಖಾಲಿ == (pZip->m_pState = (mz_zip_ಆಂತರಿಕ_state *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, ಗಾತ್ರ(mz_zip_ಆಂತರಿಕ_state))))
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  memset(pZip->m_pState, 0, ಗಾತ್ರ(mz_zip_ಆಂತರಿಕ_state));
  MZ_ZIP_ARRAY_ಗಣ_ELEMENT_ಗಾತ್ರ(&pZip->m_pState->m_central_dir, ಗಾತ್ರ(mz_uint8));
  MZ_ZIP_ARRAY_ಗಣ_ELEMENT_ಗಾತ್ರ(&pZip->m_pState->m_central_dir_offsets, ಗಾತ್ರ(mz_uint32));
  MZ_ZIP_ARRAY_ಗಣ_ELEMENT_ಗಾತ್ರ(&pZip->m_pState->m_sorted_central_dir_offsets, ಗಾತ್ರ(mz_uint32));
  ಹಿಂತಿರುಗಿ MZ_TRUE;
}

ಸ್ಥಿರ size_t mz_zip_ರಾಶಿ_write_func(ಶೂನ್ಯ *pOpaque, mz_uint64 file_ofs, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_zip_ಆಂತರಿಕ_state *pState = pZip->m_pState;
  mz_uint64 new_ಗಾತ್ರ = MZ_MAX(file_ofs + n, pState->m_mem_ಗಾತ್ರ);
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _MSC_VER
  ಆದರೆ ((!n) || ((0, ಗಾತ್ರ(size_t) == ಗಾತ್ರ(mz_uint32)) && (new_ಗಾತ್ರ > 0x7FFFFFFF)))
#ಇಲ್ಲದಿದ್ದರೆ
  ಆದರೆ ((!n) || ((ಗಾತ್ರ(size_t) == ಗಾತ್ರ(mz_uint32)) && (new_ಗಾತ್ರ > 0x7FFFFFFF)))
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ 0;
  ಆದರೆ (new_ಗಾತ್ರ > pState->m_mem_ಸಾಮರ್ಥ್ಯ)
  {
    ಶೂನ್ಯ *p_New_ಖಂಡ;
    size_t new_ಸಾಮರ್ಥ್ಯ = MZ_MAX(64, pState->m_mem_ಸಾಮರ್ಥ್ಯ); ಆಗ (new_ಸಾಮರ್ಥ್ಯ < new_ಗಾತ್ರ) new_ಸಾಮರ್ಥ್ಯ *= 2;
    ಆದರೆ (ಖಾಲಿ == (p_New_ಖಂಡ = pZip->m_pRealloc(pZip->m_pAlloc_opaque, pState->m_pMem, 1, new_ಸಾಮರ್ಥ್ಯ)))
      ಹಿಂತಿರುಗಿ 0;
    pState->m_pMem = p_New_ಖಂಡ; pState->m_mem_ಸಾಮರ್ಥ್ಯ = new_ಸಾಮರ್ಥ್ಯ;
  }
  ಸ್ಮರಣೆ_ನಕಲು((mz_uint8 *)pState->m_pMem + file_ofs, pBuf, n);
  pState->m_mem_ಗಾತ್ರ = (size_t)new_ಗಾತ್ರ;
  ಹಿಂತಿರುಗಿ n;
}

mz_bool mz_zip_writer_init_ರಾಶಿ(mz_zip_archive *pZip, size_t ಗಾತ್ರ_ಗಮ್ಯ_reserve_at_beginning, size_t initial_ಹಂಚಿಕೆ_ಗಾತ್ರ)
{
  pZip->m_pWrite = mz_zip_ರಾಶಿ_write_func;
  pZip->m_pIO_opaque = pZip;
  ಆದರೆ (!mz_zip_writer_init(pZip, ಗಾತ್ರ_ಗಮ್ಯ_reserve_at_beginning))
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  ಆದರೆ (0 != (initial_ಹಂಚಿಕೆ_ಗಾತ್ರ = MZ_MAX(initial_ಹಂಚಿಕೆ_ಗಾತ್ರ, ಗಾತ್ರ_ಗಮ್ಯ_reserve_at_beginning)))
  {
    ಆದರೆ (ಖಾಲಿ == (pZip->m_pState->m_pMem = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, initial_ಹಂಚಿಕೆ_ಗಾತ್ರ)))
    {
      mz_zip_writer_ಕೊನೆ(pZip);
      ಹಿಂತಿರುಗಿ MZ_FALSE;
    }
    pZip->m_pState->m_mem_ಸಾಮರ್ಥ್ಯ = initial_ಹಂಚಿಕೆ_ಗಾತ್ರ;
  }
  ಹಿಂತಿರುಗಿ MZ_TRUE;
}

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_STDIO
ಸ್ಥಿರ size_t mz_zip_file_write_func(ಶೂನ್ಯ *pOpaque, mz_uint64 file_ofs, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_int64 cur_ofs = MZ_FTELL64(pZip->m_pState->m_pFile);
  ಆದರೆ (((mz_int64)file_ofs < 0) || (((cur_ofs != (mz_int64)file_ofs)) && (MZ_FSEEK64(pZip->m_pState->m_pFile, (mz_int64)file_ofs, SEEK_SET))))
    ಹಿಂತಿರುಗಿ 0;
  ಹಿಂತಿರುಗಿ MZ_FWRITE(pBuf, 1, n, pZip->m_pState->m_pFile);
}

mz_bool mz_zip_writer_init_file(mz_zip_archive *pZip, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pFilename, mz_uint64 ಗಾತ್ರ_ಗಮ್ಯ_reserve_at_beginning)
{
  MZ_FILE *pFile;
  pZip->m_pWrite = mz_zip_file_write_func;
  pZip->m_pIO_opaque = pZip;
  ಆದರೆ (!mz_zip_writer_init(pZip, ಗಾತ್ರ_ಗಮ್ಯ_reserve_at_beginning))
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  ಆದರೆ (ಖಾಲಿ == (pFile = MZ_FOPEN(pFilename, "wb")))
  {
    mz_zip_writer_ಕೊನೆ(pZip);
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  }
  pZip->m_pState->m_pFile = pFile;
  ಆದರೆ (ಗಾತ್ರ_ಗಮ್ಯ_reserve_at_beginning)
  {
    mz_uint64 cur_ofs = 0; ಅಕ್ಷರ buf[4096]; MZ_CLEAR_ARR(buf);
    ಮಾಡು
    {
      size_t n = (size_t)MZ_MIN(ಗಾತ್ರ(buf), ಗಾತ್ರ_ಗಮ್ಯ_reserve_at_beginning);
      ಆದರೆ (pZip->m_pWrite(pZip->m_pIO_opaque, cur_ofs, buf, n) != n)
      {
        mz_zip_writer_ಕೊನೆ(pZip);
        ಹಿಂತಿರುಗಿ MZ_FALSE;
      }
      cur_ofs += n; ಗಾತ್ರ_ಗಮ್ಯ_reserve_at_beginning -= n;
    } ಆಗ (ಗಾತ್ರ_ಗಮ್ಯ_reserve_at_beginning);
  }
  ಹಿಂತಿರುಗಿ MZ_TRUE;
}
#ಆದರೆ_ಅಂತ್ಯ // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_writer_init_from_reader(mz_zip_archive *pZip, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pFilename)
{
  mz_zip_ಆಂತರಿಕ_state *pState;
  ಆದರೆ ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_ಬಹುಲಕ != MZ_ZIP_ಬಹುಲಕ_READING))
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  // No sense in trying to write to an archive that's already at the support max size
  ಆದರೆ ((pZip->m_ಒಟ್ಟು_files == 0xFFFF) || ((pZip->m_archive_ಗಾತ್ರ + MZ_ZIP_CENTRAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ + MZ_ZIP_LOCAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ) > 0xFFFFFFFF))
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  pState = pZip->m_pState;

  ಆದರೆ (pState->m_pFile)
  {
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ MINIZ_NO_STDIO
    pFilename; ಹಿಂತಿರುಗಿ MZ_FALSE;
#ಇಲ್ಲದಿದ್ದರೆ
    // Archive is being read from stdio - try to reopen as writable.
    ಆದರೆ (pZip->m_pIO_opaque != pZip)
      ಹಿಂತಿರುಗಿ MZ_FALSE;
    ಆದರೆ (!pFilename)
      ಹಿಂತಿರುಗಿ MZ_FALSE;
    pZip->m_pWrite = mz_zip_file_write_func;
    ಆದರೆ (ಖಾಲಿ == (pState->m_pFile = MZ_FREOPEN(pFilename, "r+b", pState->m_pFile)))
    {
      // The mz_zip_archive is now in a bogus state because pState->m_pFile is NULL, so just close it.
      mz_zip_reader_ಕೊನೆ(pZip);
      ಹಿಂತಿರುಗಿ MZ_FALSE;
    }
#ಆದರೆ_ಅಂತ್ಯ // #ifdef MINIZ_NO_STDIO
  }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (pState->m_pMem)
  {
    // Archive lives in a memory block. Assume it's from the heap that we can resize using the realloc callback.
    ಆದರೆ (pZip->m_pIO_opaque != pZip)
      ಹಿಂತಿರುಗಿ MZ_FALSE;
    pState->m_mem_ಸಾಮರ್ಥ್ಯ = pState->m_mem_ಗಾತ್ರ;
    pZip->m_pWrite = mz_zip_ರಾಶಿ_write_func;
  }
  // Archive is being read via a user provided read function - make sure the user has specified a write function too.
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!pZip->m_pWrite)
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  // Start writing new files at the archive's current central directory location.
  pZip->m_archive_ಗಾತ್ರ = pZip->m_central_directory_file_ofs;
  pZip->m_zip_ಬಹುಲಕ = MZ_ZIP_ಬಹುಲಕ_WRITING;
  pZip->m_central_directory_file_ofs = 0;

  ಹಿಂತಿರುಗಿ MZ_TRUE;
}

mz_bool mz_zip_writer_ಕೂಡಿಸು_mem(mz_zip_archive *pZip, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pArchive_name, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *pBuf, size_t buf_ಗಾತ್ರ_2, mz_uint level_and_flags)
{
  ಹಿಂತಿರುಗಿ mz_zip_writer_ಕೂಡಿಸು_mem_ex(pZip, pArchive_name, pBuf, buf_ಗಾತ್ರ_2, ಖಾಲಿ, 0, level_and_flags, 0, 0);
}

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
  mz_zip_archive *m_pZip;
  mz_uint64 m_cur_archive_file_ofs;
  mz_uint64 m_comp_ಗಾತ್ರ;
} mz_zip_writer_ಕೂಡಿಸು_state;

ಸ್ಥಿರ mz_bool mz_zip_writer_ಕೂಡಿಸು_put_buf_callback(ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ* pBuf, ಪೂರ್ಣಾಂಕ len, ಶೂನ್ಯ *pUser)
{
  mz_zip_writer_ಕೂಡಿಸು_state *pState = (mz_zip_writer_ಕೂಡಿಸು_state *)pUser;
  ಆದರೆ ((ಪೂರ್ಣಾಂಕ)pState->m_pZip->m_pWrite(pState->m_pZip->m_pIO_opaque, pState->m_cur_archive_file_ofs, pBuf, len) != len)
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  pState->m_cur_archive_file_ofs += len;
  pState->m_comp_ಗಾತ್ರ += len;
  ಹಿಂತಿರುಗಿ MZ_TRUE;
}

ಸ್ಥಿರ mz_bool mz_zip_writer_create_local_dir_ಶೀರ್ಷಿಕೆ(mz_zip_archive *pZip, mz_uint8 *pDst, mz_uint16 filename_ಗಾತ್ರ, mz_uint16 extra_ಗಾತ್ರ, mz_uint64 uncomp_ಗಾತ್ರ, mz_uint64 comp_ಗಾತ್ರ, mz_uint32 uncomp_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32, mz_uint16 ವಿಧಾನ, mz_uint16 ಬಿಟ್_flags, mz_uint16 dos_ಸಮಯ, mz_uint16 dos_date)
{
  (ಶೂನ್ಯ)pZip;
  memset(pDst, 0, MZ_ZIP_LOCAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_SIG_OFS, MZ_ZIP_LOCAL_DIR_ಶೀರ್ಷಿಕೆ_SIG);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_ಆವೃತ್ತಿ_NEEDED_OFS, ವಿಧಾನ ? 20 : 0);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_ಬಿಟ್_FLAG_OFS, ಬಿಟ್_flags);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_ವಿಧಾನ_OFS, ವಿಧಾನ);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILE_ಸಮಯ_OFS, dos_ಸಮಯ);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILE_DATE_OFS, dos_date);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_OFS, uncomp_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_COMPRESSED_ಗಾತ್ರ_OFS, comp_ಗಾತ್ರ);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_DECOMPRESSED_ಗಾತ್ರ_OFS, uncomp_ಗಾತ್ರ);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILENAME_LEN_OFS, filename_ಗಾತ್ರ);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_EXTRA_LEN_OFS, extra_ಗಾತ್ರ);
  ಹಿಂತಿರುಗಿ MZ_TRUE;
}

ಸ್ಥಿರ mz_bool mz_zip_writer_create_central_dir_ಶೀರ್ಷಿಕೆ(mz_zip_archive *pZip, mz_uint8 *pDst, mz_uint16 filename_ಗಾತ್ರ, mz_uint16 extra_ಗಾತ್ರ, mz_uint16 comment_ಗಾತ್ರ, mz_uint64 uncomp_ಗಾತ್ರ, mz_uint64 comp_ಗಾತ್ರ, mz_uint32 uncomp_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32, mz_uint16 ವಿಧಾನ, mz_uint16 ಬಿಟ್_flags, mz_uint16 dos_ಸಮಯ, mz_uint16 dos_date, mz_uint64 local_ಶೀರ್ಷಿಕೆ_ofs, mz_uint32 ext_ಗುಣಲಕ್ಷಣಗಳು)
{
  (ಶೂನ್ಯ)pZip;
  memset(pDst, 0, MZ_ZIP_CENTRAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_SIG_OFS, MZ_ZIP_CENTRAL_DIR_ಶೀರ್ಷಿಕೆ_SIG);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_ಆವೃತ್ತಿ_NEEDED_OFS, ವಿಧಾನ ? 20 : 0);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_ಬಿಟ್_FLAG_OFS, ಬಿಟ್_flags);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_ವಿಧಾನ_OFS, ವಿಧಾನ);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILE_ಸಮಯ_OFS, dos_ಸಮಯ);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILE_DATE_OFS, dos_date);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_OFS, uncomp_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_COMPRESSED_ಗಾತ್ರ_OFS, comp_ಗಾತ್ರ);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_DECOMPRESSED_ಗಾತ್ರ_OFS, uncomp_ಗಾತ್ರ);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILENAME_LEN_OFS, filename_ಗಾತ್ರ);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_EXTRA_LEN_OFS, extra_ಗಾತ್ರ);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_COMMENT_LEN_OFS, comment_ಗಾತ್ರ);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS, ext_ಗುಣಲಕ್ಷಣಗಳು);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_LOCAL_ಶೀರ್ಷಿಕೆ_OFS, local_ಶೀರ್ಷಿಕೆ_ofs);
  ಹಿಂತಿರುಗಿ MZ_TRUE;
}

ಸ್ಥಿರ mz_bool mz_zip_writer_ಕೂಡಿಸು_ಗಮ್ಯ_central_dir(mz_zip_archive *pZip, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pFilename, mz_uint16 filename_ಗಾತ್ರ, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *pExtra, mz_uint16 extra_ಗಾತ್ರ, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *pComment, mz_uint16 comment_ಗಾತ್ರ, mz_uint64 uncomp_ಗಾತ್ರ, mz_uint64 comp_ಗಾತ್ರ, mz_uint32 uncomp_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32, mz_uint16 ವಿಧಾನ, mz_uint16 ಬಿಟ್_flags, mz_uint16 dos_ಸಮಯ, mz_uint16 dos_date, mz_uint64 local_ಶೀರ್ಷಿಕೆ_ofs, mz_uint32 ext_ಗುಣಲಕ್ಷಣಗಳು)
{
  mz_zip_ಆಂತರಿಕ_state *pState = pZip->m_pState;
  mz_uint32 central_dir_ofs = (mz_uint32)pState->m_central_dir.m_ಗಾತ್ರ;
  size_t orig_central_dir_ಗಾತ್ರ = pState->m_central_dir.m_ಗಾತ್ರ;
  mz_uint8 central_dir_ಶೀರ್ಷಿಕೆ[MZ_ZIP_CENTRAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ];

  // No zip64 support yet
  ಆದರೆ ((local_ಶೀರ್ಷಿಕೆ_ofs > 0xFFFFFFFF) || (((mz_uint64)pState->m_central_dir.m_ಗಾತ್ರ + MZ_ZIP_CENTRAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ + filename_ಗಾತ್ರ + extra_ಗಾತ್ರ + comment_ಗಾತ್ರ) > 0xFFFFFFFF))
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  ಆದರೆ (!mz_zip_writer_create_central_dir_ಶೀರ್ಷಿಕೆ(pZip, central_dir_ಶೀರ್ಷಿಕೆ, filename_ಗಾತ್ರ, extra_ಗಾತ್ರ, comment_ಗಾತ್ರ, uncomp_ಗಾತ್ರ, comp_ಗಾತ್ರ, uncomp_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32, ವಿಧಾನ, ಬಿಟ್_flags, dos_ಸಮಯ, dos_date, local_ಶೀರ್ಷಿಕೆ_ofs, ext_ಗುಣಲಕ್ಷಣಗಳು))
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  ಆದರೆ ((!mz_zip_array_ತಳ್ಳು_ಹಿಂಭಾಗ(pZip, &pState->m_central_dir, central_dir_ಶೀರ್ಷಿಕೆ, MZ_ZIP_CENTRAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ)) ||
      (!mz_zip_array_ತಳ್ಳು_ಹಿಂಭಾಗ(pZip, &pState->m_central_dir, pFilename, filename_ಗಾತ್ರ)) ||
      (!mz_zip_array_ತಳ್ಳು_ಹಿಂಭಾಗ(pZip, &pState->m_central_dir, pExtra, extra_ಗಾತ್ರ)) ||
      (!mz_zip_array_ತಳ್ಳು_ಹಿಂಭಾಗ(pZip, &pState->m_central_dir, pComment, comment_ಗಾತ್ರ)) ||
      (!mz_zip_array_ತಳ್ಳು_ಹಿಂಭಾಗ(pZip, &pState->m_central_dir_offsets, &central_dir_ofs, 1)))
  {
    // Try to push the central directory array back into its original state.
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_ಗಾತ್ರ, MZ_FALSE);
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  }

  ಹಿಂತಿರುಗಿ MZ_TRUE;
}

ಸ್ಥಿರ mz_bool mz_zip_writer_validate_archive_name(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pArchive_name)
{
  // Basic ZIP archive filename validity checks: Valid filenames cannot start with a forward slash, cannot contain a drive letter, and cannot use DOS-style backward slashes.
  ಆದರೆ (*pArchive_name == '/')
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  ಆಗ (*pArchive_name)
  {
    ಆದರೆ ((*pArchive_name == '\\') || (*pArchive_name == ':'))
      ಹಿಂತಿರುಗಿ MZ_FALSE;
    pArchive_name++;
  }
  ಹಿಂತಿರುಗಿ MZ_TRUE;
}

ಸ್ಥಿರ mz_uint mz_zip_writer_compute_padding_needed_for_file_alignment(mz_zip_archive *pZip)
{
  mz_uint32 n;
  ಆದರೆ (!pZip->m_file_ಸ್ಥಾನಾಂತರ_alignment)
    ಹಿಂತಿರುಗಿ 0;
  n = (mz_uint32)(pZip->m_archive_ಗಾತ್ರ & (pZip->m_file_ಸ್ಥಾನಾಂತರ_alignment - 1));
  ಹಿಂತಿರುಗಿ (pZip->m_file_ಸ್ಥಾನಾಂತರ_alignment - n) & (pZip->m_file_ಸ್ಥಾನಾಂತರ_alignment - 1);
}

ಸ್ಥಿರ mz_bool mz_zip_writer_write_zeros(mz_zip_archive *pZip, mz_uint64 cur_file_ofs, mz_uint32 n)
{
  ಅಕ್ಷರ buf[4096];
  memset(buf, 0, MZ_MIN(ಗಾತ್ರ(buf), n));
  ಆಗ (n)
  {
    mz_uint32 s = MZ_MIN(ಗಾತ್ರ(buf), n);
    ಆದರೆ (pZip->m_pWrite(pZip->m_pIO_opaque, cur_file_ofs, buf, s) != s)
      ಹಿಂತಿರುಗಿ MZ_FALSE;
    cur_file_ofs += s; n -= s;
  }
  ಹಿಂತಿರುಗಿ MZ_TRUE;
}

mz_bool mz_zip_writer_ಕೂಡಿಸು_mem_ex(mz_zip_archive *pZip, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pArchive_name, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *pBuf, size_t buf_ಗಾತ್ರ_2, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *pComment, mz_uint16 comment_ಗಾತ್ರ, mz_uint level_and_flags, mz_uint64 uncomp_ಗಾತ್ರ, mz_uint32 uncomp_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32)
{
  mz_uint16 ವಿಧಾನ = 0, dos_ಸಮಯ = 0, dos_date = 0;
  mz_uint level, ext_ಗುಣಲಕ್ಷಣಗಳು = 0, ಅಂಕೆ_alignment_padding_ಬೈಟುಗಳು;
  mz_uint64 local_dir_ಶೀರ್ಷಿಕೆ_ofs = pZip->m_archive_ಗಾತ್ರ, cur_archive_file_ofs = pZip->m_archive_ಗಾತ್ರ, comp_ಗಾತ್ರ = 0;
  size_t archive_name_ಗಾತ್ರ;
  mz_uint8 local_dir_ಶೀರ್ಷಿಕೆ[MZ_ZIP_LOCAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ];
  tdefl_compressor *pComp = ಖಾಲಿ;
  mz_bool store_ದತ್ತಾಂಶ_uncompressed;
  mz_zip_ಆಂತರಿಕ_state *pState;

  ಆದರೆ ((ಪೂರ್ಣಾಂಕ)level_and_flags < 0)
    level_and_flags = MZ_DEFAULT_LEVEL;
  level = level_and_flags & 0xF;
  store_ದತ್ತಾಂಶ_uncompressed = ((!level) || (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_ದತ್ತಾಂಶ));

  ಆದರೆ ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_ಬಹುಲಕ != MZ_ZIP_ಬಹುಲಕ_WRITING) || ((buf_ಗಾತ್ರ_2) && (!pBuf)) || (!pArchive_name) || ((comment_ಗಾತ್ರ) && (!pComment)) || (pZip->m_ಒಟ್ಟು_files == 0xFFFF) || (level > MZ_UBER_COMPRESSION))
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  pState = pZip->m_pState;

  ಆದರೆ ((!(level_and_flags & MZ_ZIP_FLAG_COMPRESSED_ದತ್ತಾಂಶ)) && (uncomp_ಗಾತ್ರ))
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  // No zip64 support yet
  ಆದರೆ ((buf_ಗಾತ್ರ_2 > 0xFFFFFFFF) || (uncomp_ಗಾತ್ರ > 0xFFFFFFFF))
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  ಆದರೆ (!mz_zip_writer_validate_archive_name(pArchive_name))
    ಹಿಂತಿರುಗಿ MZ_FALSE;

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_ಸಮಯ
  {
    ಸಮಯ_t cur_ಸಮಯ; ಸಮಯ(&cur_ಸಮಯ);
    mz_zip_ಸಮಯ_ಗಮ್ಯ_dos_ಸಮಯ(cur_ಸಮಯ, &dos_ಸಮಯ, &dos_date);
  }
#ಆದರೆ_ಅಂತ್ಯ // #ifndef MINIZ_NO_TIME

  archive_name_ಗಾತ್ರ = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(pArchive_name);
  ಆದರೆ (archive_name_ಗಾತ್ರ > 0xFFFF)
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  ಅಂಕೆ_alignment_padding_ಬೈಟುಗಳು = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  ಆದರೆ ((pZip->m_ಒಟ್ಟು_files == 0xFFFF) || ((pZip->m_archive_ಗಾತ್ರ + ಅಂಕೆ_alignment_padding_ಬೈಟುಗಳು + MZ_ZIP_LOCAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ + MZ_ZIP_CENTRAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ + comment_ಗಾತ್ರ + archive_name_ಗಾತ್ರ) > 0xFFFFFFFF))
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  ಆದರೆ ((archive_name_ಗಾತ್ರ) && (pArchive_name[archive_name_ಗಾತ್ರ - 1] == '/'))
  {
    // Set DOS Subdirectory attribute bit.
    ext_ಗುಣಲಕ್ಷಣಗಳು |= 0x10;
    // Subdirectories cannot contain data.
    ಆದರೆ ((buf_ಗಾತ್ರ_2) || (uncomp_ಗಾತ್ರ))
      ಹಿಂತಿರುಗಿ MZ_FALSE;
  }

  // Try to do any allocations before writing to the archive, so if an allocation fails the file remains unmodified. (A good idea if we're doing an in-place modification.)
  ಆದರೆ ((!mz_zip_array_ensure_ಸ್ಥಳ(pZip, &pState->m_central_dir, MZ_ZIP_CENTRAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ + archive_name_ಗಾತ್ರ + comment_ಗಾತ್ರ)) || (!mz_zip_array_ensure_ಸ್ಥಳ(pZip, &pState->m_central_dir_offsets, 1)))
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  ಆದರೆ ((!store_ದತ್ತಾಂಶ_uncompressed) && (buf_ಗಾತ್ರ_2))
  {
    ಆದರೆ (ಖಾಲಿ == (pComp = (tdefl_compressor *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, ಗಾತ್ರ(tdefl_compressor))))
      ಹಿಂತಿರುಗಿ MZ_FALSE;
  }

  ಆದರೆ (!mz_zip_writer_write_zeros(pZip, cur_archive_file_ofs, ಅಂಕೆ_alignment_padding_ಬೈಟುಗಳು + ಗಾತ್ರ(local_dir_ಶೀರ್ಷಿಕೆ)))
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  }
  local_dir_ಶೀರ್ಷಿಕೆ_ofs += ಅಂಕೆ_alignment_padding_ಬೈಟುಗಳು;
  ಆದರೆ (pZip->m_file_ಸ್ಥಾನಾಂತರ_alignment) { MZ_ASSERT((local_dir_ಶೀರ್ಷಿಕೆ_ofs & (pZip->m_file_ಸ್ಥಾನಾಂತರ_alignment - 1)) == 0); }
  cur_archive_file_ofs += ಅಂಕೆ_alignment_padding_ಬೈಟುಗಳು + ಗಾತ್ರ(local_dir_ಶೀರ್ಷಿಕೆ);

  MZ_CLEAR_ARR(local_dir_ಶೀರ್ಷಿಕೆ);
  ಆದರೆ (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pArchive_name, archive_name_ಗಾತ್ರ) != archive_name_ಗಾತ್ರ)
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  }
  cur_archive_file_ofs += archive_name_ಗಾತ್ರ;

  ಆದರೆ (!(level_and_flags & MZ_ZIP_FLAG_COMPRESSED_ದತ್ತಾಂಶ))
  {
    uncomp_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32 = (mz_uint32)mz_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32(MZ_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_INIT, (ಸ್ಥಿರಾಂಕ mz_uint8*)pBuf, buf_ಗಾತ್ರ_2);
    uncomp_ಗಾತ್ರ = buf_ಗಾತ್ರ_2;
    ಆದರೆ (uncomp_ಗಾತ್ರ <= 3)
    {
      level = 0;
      store_ದತ್ತಾಂಶ_uncompressed = MZ_TRUE;
    }
  }

  ಆದರೆ (store_ದತ್ತಾಂಶ_uncompressed)
  {
    ಆದರೆ (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pBuf, buf_ಗಾತ್ರ_2) != buf_ಗಾತ್ರ_2)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
      ಹಿಂತಿರುಗಿ MZ_FALSE;
    }

    cur_archive_file_ofs += buf_ಗಾತ್ರ_2;
    comp_ಗಾತ್ರ = buf_ಗಾತ್ರ_2;

    ಆದರೆ (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_ದತ್ತಾಂಶ)
      ವಿಧಾನ = MZ_DEFLATED;
  }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (buf_ಗಾತ್ರ_2)
  {
    mz_zip_writer_ಕೂಡಿಸು_state state;

    state.m_pZip = pZip;
    state.m_cur_archive_file_ofs = cur_archive_file_ofs;
    state.m_comp_ಗಾತ್ರ = 0;

    ಆದರೆ ((tdefl_init(pComp, mz_zip_writer_ಕೂಡಿಸು_put_buf_callback, &state, tdefl_create_comp_flags_from_zip_params(level, -15, MZ_DEFAULT_STRATEGY)) != TDEFL_ಸ್ಥಿತಿ_OKAY) ||
        (tdefl_compress_ಬಫರ್(pComp, pBuf, buf_ಗಾತ್ರ_2, TDEFL_ಮುಕ್ತಾಯ) != TDEFL_ಸ್ಥಿತಿ_ಮುಗಿದ))
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
      ಹಿಂತಿರುಗಿ MZ_FALSE;
    }

    comp_ಗಾತ್ರ = state.m_comp_ಗಾತ್ರ;
    cur_archive_file_ofs = state.m_cur_archive_file_ofs;

    ವಿಧಾನ = MZ_DEFLATED;
  }

  pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
  pComp = ಖಾಲಿ;

  // no zip64 support yet
  ಆದರೆ ((comp_ಗಾತ್ರ > 0xFFFFFFFF) || (cur_archive_file_ofs > 0xFFFFFFFF))
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  ಆದರೆ (!mz_zip_writer_create_local_dir_ಶೀರ್ಷಿಕೆ(pZip, local_dir_ಶೀರ್ಷಿಕೆ, (mz_uint16)archive_name_ಗಾತ್ರ, 0, uncomp_ಗಾತ್ರ, comp_ಗಾತ್ರ, uncomp_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32, ವಿಧಾನ, 0, dos_ಸಮಯ, dos_date))
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  ಆದರೆ (pZip->m_pWrite(pZip->m_pIO_opaque, local_dir_ಶೀರ್ಷಿಕೆ_ofs, local_dir_ಶೀರ್ಷಿಕೆ, ಗಾತ್ರ(local_dir_ಶೀರ್ಷಿಕೆ)) != ಗಾತ್ರ(local_dir_ಶೀರ್ಷಿಕೆ))
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  ಆದರೆ (!mz_zip_writer_ಕೂಡಿಸು_ಗಮ್ಯ_central_dir(pZip, pArchive_name, (mz_uint16)archive_name_ಗಾತ್ರ, ಖಾಲಿ, 0, pComment, comment_ಗಾತ್ರ, uncomp_ಗಾತ್ರ, comp_ಗಾತ್ರ, uncomp_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32, ವಿಧಾನ, 0, dos_ಸಮಯ, dos_date, local_dir_ಶೀರ್ಷಿಕೆ_ofs, ext_ಗುಣಲಕ್ಷಣಗಳು))
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  pZip->m_ಒಟ್ಟು_files++;
  pZip->m_archive_ಗಾತ್ರ = cur_archive_file_ofs;

  ಹಿಂತಿರುಗಿ MZ_TRUE;
}

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_STDIO
mz_bool mz_zip_writer_ಕೂಡಿಸು_file(mz_zip_archive *pZip, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pArchive_name, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pSrc_filename, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *pComment, mz_uint16 comment_ಗಾತ್ರ, mz_uint level_and_flags)
{
  mz_uint uncomp_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32 = MZ_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32_INIT, level, ಅಂಕೆ_alignment_padding_ಬೈಟುಗಳು;
  mz_uint16 ವಿಧಾನ = 0, dos_ಸಮಯ = 0, dos_date = 0, ext_ಗುಣಲಕ್ಷಣಗಳು = 0;
  mz_uint64 local_dir_ಶೀರ್ಷಿಕೆ_ofs = pZip->m_archive_ಗಾತ್ರ, cur_archive_file_ofs = pZip->m_archive_ಗಾತ್ರ, uncomp_ಗಾತ್ರ = 0, comp_ಗಾತ್ರ = 0;
  size_t archive_name_ಗಾತ್ರ;
  mz_uint8 local_dir_ಶೀರ್ಷಿಕೆ[MZ_ZIP_LOCAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ];
  MZ_FILE *pSrc_file = ಖಾಲಿ;

  ಆದರೆ ((ಪೂರ್ಣಾಂಕ)level_and_flags < 0)
    level_and_flags = MZ_DEFAULT_LEVEL;
  level = level_and_flags & 0xF;

  ಆದರೆ ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_ಬಹುಲಕ != MZ_ZIP_ಬಹುಲಕ_WRITING) || (!pArchive_name) || ((comment_ಗಾತ್ರ) && (!pComment)) || (level > MZ_UBER_COMPRESSION))
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  ಆದರೆ (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_ದತ್ತಾಂಶ)
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  ಆದರೆ (!mz_zip_writer_validate_archive_name(pArchive_name))
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  archive_name_ಗಾತ್ರ = ಅಕ್ಷರಸರಣಿ_ಉದ್ದ(pArchive_name);
  ಆದರೆ (archive_name_ಗಾತ್ರ > 0xFFFF)
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  ಅಂಕೆ_alignment_padding_ಬೈಟುಗಳು = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  ಆದರೆ ((pZip->m_ಒಟ್ಟು_files == 0xFFFF) || ((pZip->m_archive_ಗಾತ್ರ + ಅಂಕೆ_alignment_padding_ಬೈಟುಗಳು + MZ_ZIP_LOCAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ + MZ_ZIP_CENTRAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ + comment_ಗಾತ್ರ + archive_name_ಗಾತ್ರ) > 0xFFFFFFFF))
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  ಆದರೆ (!mz_zip_get_file_modified_ಸಮಯ(pSrc_filename, &dos_ಸಮಯ, &dos_date))
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  pSrc_file = MZ_FOPEN(pSrc_filename, "rb");
  ಆದರೆ (!pSrc_file)
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  MZ_FSEEK64(pSrc_file, 0, SEEK_END);
  uncomp_ಗಾತ್ರ = MZ_FTELL64(pSrc_file);
  MZ_FSEEK64(pSrc_file, 0, SEEK_SET);

  ಆದರೆ (uncomp_ಗಾತ್ರ > 0xFFFFFFFF)
  {
    // No zip64 support yet
    MZ_FCLOSE(pSrc_file);
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  }
  ಆದರೆ (uncomp_ಗಾತ್ರ <= 3)
    level = 0;

  ಆದರೆ (!mz_zip_writer_write_zeros(pZip, cur_archive_file_ofs, ಅಂಕೆ_alignment_padding_ಬೈಟುಗಳು + ಗಾತ್ರ(local_dir_ಶೀರ್ಷಿಕೆ)))
  {
    MZ_FCLOSE(pSrc_file);
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  }
  local_dir_ಶೀರ್ಷಿಕೆ_ofs += ಅಂಕೆ_alignment_padding_ಬೈಟುಗಳು;
  ಆದರೆ (pZip->m_file_ಸ್ಥಾನಾಂತರ_alignment) { MZ_ASSERT((local_dir_ಶೀರ್ಷಿಕೆ_ofs & (pZip->m_file_ಸ್ಥಾನಾಂತರ_alignment - 1)) == 0); }
  cur_archive_file_ofs += ಅಂಕೆ_alignment_padding_ಬೈಟುಗಳು + ಗಾತ್ರ(local_dir_ಶೀರ್ಷಿಕೆ);

  MZ_CLEAR_ARR(local_dir_ಶೀರ್ಷಿಕೆ);
  ಆದರೆ (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pArchive_name, archive_name_ಗಾತ್ರ) != archive_name_ಗಾತ್ರ)
  {
    MZ_FCLOSE(pSrc_file);
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  }
  cur_archive_file_ofs += archive_name_ಗಾತ್ರ;

  ಆದರೆ (uncomp_ಗಾತ್ರ)
  {
    mz_uint64 uncomp_ಉಳಿದ = uncomp_ಗಾತ್ರ;
    ಶೂನ್ಯ *pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, MZ_ZIP_MAX_IO_BUF_ಗಾತ್ರ);
    ಆದರೆ (!pRead_buf)
    {
      MZ_FCLOSE(pSrc_file);
      ಹಿಂತಿರುಗಿ MZ_FALSE;
    }

    ಆದರೆ (!level)
    {
      ಆಗ (uncomp_ಉಳಿದ)
      {
        mz_uint n = (mz_uint)MZ_MIN(MZ_ZIP_MAX_IO_BUF_ಗಾತ್ರ, uncomp_ಉಳಿದ);
        ಆದರೆ ((MZ_FREAD(pRead_buf, 1, n, pSrc_file) != n) || (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pRead_buf, n) != n))
        {
          pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
          MZ_FCLOSE(pSrc_file);
          ಹಿಂತಿರುಗಿ MZ_FALSE;
        }
        uncomp_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32 = (mz_uint32)mz_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32(uncomp_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32, (ಸ್ಥಿರಾಂಕ mz_uint8 *)pRead_buf, n);
        uncomp_ಉಳಿದ -= n;
        cur_archive_file_ofs += n;
      }
      comp_ಗಾತ್ರ = uncomp_ಗಾತ್ರ;
    }
    ಇಲ್ಲದಿದ್ದರೆ
    {
      mz_bool ಫಲಿತಾಂಶ = MZ_FALSE;
      mz_zip_writer_ಕೂಡಿಸು_state state;
      tdefl_compressor *pComp = (tdefl_compressor *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, ಗಾತ್ರ(tdefl_compressor));
      ಆದರೆ (!pComp)
      {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        ಹಿಂತಿರುಗಿ MZ_FALSE;
      }

      state.m_pZip = pZip;
      state.m_cur_archive_file_ofs = cur_archive_file_ofs;
      state.m_comp_ಗಾತ್ರ = 0;

      ಆದರೆ (tdefl_init(pComp, mz_zip_writer_ಕೂಡಿಸು_put_buf_callback, &state, tdefl_create_comp_flags_from_zip_params(level, -15, MZ_DEFAULT_STRATEGY)) != TDEFL_ಸ್ಥಿತಿ_OKAY)
      {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        ಹಿಂತಿರುಗಿ MZ_FALSE;
      }

      ಗಾಗಿ ( ; ; )
      {
        size_t ಒಳ_buf_ಗಾತ್ರ = (mz_uint32)MZ_MIN(uncomp_ಉಳಿದ, MZ_ZIP_MAX_IO_BUF_ಗಾತ್ರ);
        tdefl_ಸ್ಥಿತಿ ಸ್ಥಿತಿ_2;

        ಆದರೆ (MZ_FREAD(pRead_buf, 1, ಒಳ_buf_ಗಾತ್ರ, pSrc_file) != ಒಳ_buf_ಗಾತ್ರ)
          ನಿಲ್ಲಿಸು;

        uncomp_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32 = (mz_uint32)mz_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32(uncomp_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32, (ಸ್ಥಿರಾಂಕ mz_uint8 *)pRead_buf, ಒಳ_buf_ಗಾತ್ರ);
        uncomp_ಉಳಿದ -= ಒಳ_buf_ಗಾತ್ರ;

        ಸ್ಥಿತಿ_2 = tdefl_compress_ಬಫರ್(pComp, pRead_buf, ಒಳ_buf_ಗಾತ್ರ, uncomp_ಉಳಿದ ? TDEFL_NO_FLUSH : TDEFL_ಮುಕ್ತಾಯ);
        ಆದರೆ (ಸ್ಥಿತಿ_2 == TDEFL_ಸ್ಥಿತಿ_ಮುಗಿದ)
        {
          ಫಲಿತಾಂಶ = MZ_TRUE;
          ನಿಲ್ಲಿಸು;
        }
        ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಸ್ಥಿತಿ_2 != TDEFL_ಸ್ಥಿತಿ_OKAY)
          ನಿಲ್ಲಿಸು;
      }

      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);

      ಆದರೆ (!ಫಲಿತಾಂಶ)
      {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        ಹಿಂತಿರುಗಿ MZ_FALSE;
      }

      comp_ಗಾತ್ರ = state.m_comp_ಗಾತ್ರ;
      cur_archive_file_ofs = state.m_cur_archive_file_ofs;

      ವಿಧಾನ = MZ_DEFLATED;
    }

    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
  }

  MZ_FCLOSE(pSrc_file); pSrc_file = ಖಾಲಿ;

  // no zip64 support yet
  ಆದರೆ ((comp_ಗಾತ್ರ > 0xFFFFFFFF) || (cur_archive_file_ofs > 0xFFFFFFFF))
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  ಆದರೆ (!mz_zip_writer_create_local_dir_ಶೀರ್ಷಿಕೆ(pZip, local_dir_ಶೀರ್ಷಿಕೆ, (mz_uint16)archive_name_ಗಾತ್ರ, 0, uncomp_ಗಾತ್ರ, comp_ಗಾತ್ರ, uncomp_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32, ವಿಧಾನ, 0, dos_ಸಮಯ, dos_date))
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  ಆದರೆ (pZip->m_pWrite(pZip->m_pIO_opaque, local_dir_ಶೀರ್ಷಿಕೆ_ofs, local_dir_ಶೀರ್ಷಿಕೆ, ಗಾತ್ರ(local_dir_ಶೀರ್ಷಿಕೆ)) != ಗಾತ್ರ(local_dir_ಶೀರ್ಷಿಕೆ))
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  ಆದರೆ (!mz_zip_writer_ಕೂಡಿಸು_ಗಮ್ಯ_central_dir(pZip, pArchive_name, (mz_uint16)archive_name_ಗಾತ್ರ, ಖಾಲಿ, 0, pComment, comment_ಗಾತ್ರ, uncomp_ಗಾತ್ರ, comp_ಗಾತ್ರ, uncomp_ಚಕ್ರೀಯ_ಪರೀಕ್ಷೆ_32, ವಿಧಾನ, 0, dos_ಸಮಯ, dos_date, local_dir_ಶೀರ್ಷಿಕೆ_ofs, ext_ಗುಣಲಕ್ಷಣಗಳು))
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  pZip->m_ಒಟ್ಟು_files++;
  pZip->m_archive_ಗಾತ್ರ = cur_archive_file_ofs;

  ಹಿಂತಿರುಗಿ MZ_TRUE;
}
#ಆದರೆ_ಅಂತ್ಯ // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_writer_ಕೂಡಿಸು_from_zip_reader(mz_zip_archive *pZip, mz_zip_archive *p_ಮೂಲ_zip, mz_uint file_ಸೂಚ್ಯಂಕ)
{
  mz_uint n, ಬಿಟ್_flags, ಅಂಕೆ_alignment_padding_ಬೈಟುಗಳು;
  mz_uint64 comp_ಬೈಟುಗಳು_ಉಳಿದ, local_dir_ಶೀರ್ಷಿಕೆ_ofs;
  mz_uint64 cur_src_file_ofs, cur_dst_file_ofs;
  mz_uint32 local_ಶೀರ್ಷಿಕೆ_u32[(MZ_ZIP_LOCAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ + ಗಾತ್ರ(mz_uint32) - 1) / ಗಾತ್ರ(mz_uint32)]; mz_uint8 *p_Local_ಶೀರ್ಷಿಕೆ = (mz_uint8 *)local_ಶೀರ್ಷಿಕೆ_u32;
  mz_uint8 central_ಶೀರ್ಷಿಕೆ[MZ_ZIP_CENTRAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ];
  size_t orig_central_dir_ಗಾತ್ರ;
  mz_zip_ಆಂತರಿಕ_state *pState;
  ಶೂನ್ಯ *pBuf; ಸ್ಥಿರಾಂಕ mz_uint8 *p_Src_central_ಶೀರ್ಷಿಕೆ;

  ಆದರೆ ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_ಬಹುಲಕ != MZ_ZIP_ಬಹುಲಕ_WRITING))
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  ಆದರೆ (ಖಾಲಿ == (p_Src_central_ಶೀರ್ಷಿಕೆ = mz_zip_reader_get_cdh(p_ಮೂಲ_zip, file_ಸೂಚ್ಯಂಕ)))
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  pState = pZip->m_pState;

  ಅಂಕೆ_alignment_padding_ಬೈಟುಗಳು = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  ಆದರೆ ((pZip->m_ಒಟ್ಟು_files == 0xFFFF) || ((pZip->m_archive_ಗಾತ್ರ + ಅಂಕೆ_alignment_padding_ಬೈಟುಗಳು + MZ_ZIP_LOCAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ + MZ_ZIP_CENTRAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ) > 0xFFFFFFFF))
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  cur_src_file_ofs = MZ_READ_LE32(p_Src_central_ಶೀರ್ಷಿಕೆ + MZ_ZIP_CDH_LOCAL_ಶೀರ್ಷಿಕೆ_OFS);
  cur_dst_file_ofs = pZip->m_archive_ಗಾತ್ರ;

  ಆದರೆ (p_ಮೂಲ_zip->m_pRead(p_ಮೂಲ_zip->m_pIO_opaque, cur_src_file_ofs, p_Local_ಶೀರ್ಷಿಕೆ, MZ_ZIP_LOCAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ) != MZ_ZIP_LOCAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  ಆದರೆ (MZ_READ_LE32(p_Local_ಶೀರ್ಷಿಕೆ) != MZ_ZIP_LOCAL_DIR_ಶೀರ್ಷಿಕೆ_SIG)
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  cur_src_file_ofs += MZ_ZIP_LOCAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ;

  ಆದರೆ (!mz_zip_writer_write_zeros(pZip, cur_dst_file_ofs, ಅಂಕೆ_alignment_padding_ಬೈಟುಗಳು))
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  cur_dst_file_ofs += ಅಂಕೆ_alignment_padding_ಬೈಟುಗಳು;
  local_dir_ಶೀರ್ಷಿಕೆ_ofs = cur_dst_file_ofs;
  ಆದರೆ (pZip->m_file_ಸ್ಥಾನಾಂತರ_alignment) { MZ_ASSERT((local_dir_ಶೀರ್ಷಿಕೆ_ofs & (pZip->m_file_ಸ್ಥಾನಾಂತರ_alignment - 1)) == 0); }

  ಆದರೆ (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, p_Local_ಶೀರ್ಷಿಕೆ, MZ_ZIP_LOCAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ) != MZ_ZIP_LOCAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ)
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  cur_dst_file_ofs += MZ_ZIP_LOCAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ;

  n = MZ_READ_LE16(p_Local_ಶೀರ್ಷಿಕೆ + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p_Local_ಶೀರ್ಷಿಕೆ + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  comp_ಬೈಟುಗಳು_ಉಳಿದ = n + MZ_READ_LE32(p_Src_central_ಶೀರ್ಷಿಕೆ + MZ_ZIP_CDH_COMPRESSED_ಗಾತ್ರ_OFS);

  ಆದರೆ (ಖಾಲಿ == (pBuf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)MZ_MAX(ಗಾತ್ರ(mz_uint32) * 4, MZ_MIN(MZ_ZIP_MAX_IO_BUF_ಗಾತ್ರ, comp_ಬೈಟುಗಳು_ಉಳಿದ)))))
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  ಆಗ (comp_ಬೈಟುಗಳು_ಉಳಿದ)
  {
    n = (mz_uint)MZ_MIN(MZ_ZIP_MAX_IO_BUF_ಗಾತ್ರ, comp_ಬೈಟುಗಳು_ಉಳಿದ);
    ಆದರೆ (p_ಮೂಲ_zip->m_pRead(p_ಮೂಲ_zip->m_pIO_opaque, cur_src_file_ofs, pBuf, n) != n)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      ಹಿಂತಿರುಗಿ MZ_FALSE;
    }
    cur_src_file_ofs += n;

    ಆದರೆ (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, pBuf, n) != n)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      ಹಿಂತಿರುಗಿ MZ_FALSE;
    }
    cur_dst_file_ofs += n;

    comp_ಬೈಟುಗಳು_ಉಳಿದ -= n;
  }

  ಬಿಟ್_flags = MZ_READ_LE16(p_Local_ಶೀರ್ಷಿಕೆ + MZ_ZIP_LDH_ಬಿಟ್_FLAG_OFS);
  ಆದರೆ (ಬಿಟ್_flags & 8)
  {
    // Copy data descriptor
    ಆದರೆ (p_ಮೂಲ_zip->m_pRead(p_ಮೂಲ_zip->m_pIO_opaque, cur_src_file_ofs, pBuf, ಗಾತ್ರ(mz_uint32) * 4) != ಗಾತ್ರ(mz_uint32) * 4)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      ಹಿಂತಿರುಗಿ MZ_FALSE;
    }

    n = ಗಾತ್ರ(mz_uint32) * ((MZ_READ_LE32(pBuf) == 0x08074b50) ? 4 : 3);
    ಆದರೆ (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, pBuf, n) != n)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      ಹಿಂತಿರುಗಿ MZ_FALSE;
    }

    cur_src_file_ofs += n;
    cur_dst_file_ofs += n;
  }
  pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);

  // no zip64 support yet
  ಆದರೆ (cur_dst_file_ofs > 0xFFFFFFFF)
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  orig_central_dir_ಗಾತ್ರ = pState->m_central_dir.m_ಗಾತ್ರ;

  ಸ್ಮರಣೆ_ನಕಲು(central_ಶೀರ್ಷಿಕೆ, p_Src_central_ಶೀರ್ಷಿಕೆ, MZ_ZIP_CENTRAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ);
  MZ_WRITE_LE32(central_ಶೀರ್ಷಿಕೆ + MZ_ZIP_CDH_LOCAL_ಶೀರ್ಷಿಕೆ_OFS, local_dir_ಶೀರ್ಷಿಕೆ_ofs);
  ಆದರೆ (!mz_zip_array_ತಳ್ಳು_ಹಿಂಭಾಗ(pZip, &pState->m_central_dir, central_ಶೀರ್ಷಿಕೆ, MZ_ZIP_CENTRAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ))
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  n = MZ_READ_LE16(p_Src_central_ಶೀರ್ಷಿಕೆ + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p_Src_central_ಶೀರ್ಷಿಕೆ + MZ_ZIP_CDH_EXTRA_LEN_OFS) + MZ_READ_LE16(p_Src_central_ಶೀರ್ಷಿಕೆ + MZ_ZIP_CDH_COMMENT_LEN_OFS);
  ಆದರೆ (!mz_zip_array_ತಳ್ಳು_ಹಿಂಭಾಗ(pZip, &pState->m_central_dir, p_Src_central_ಶೀರ್ಷಿಕೆ + MZ_ZIP_CENTRAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ, n))
  {
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_ಗಾತ್ರ, MZ_FALSE);
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  }

  ಆದರೆ (pState->m_central_dir.m_ಗಾತ್ರ > 0xFFFFFFFF)
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  n = (mz_uint32)orig_central_dir_ಗಾತ್ರ;
  ಆದರೆ (!mz_zip_array_ತಳ್ಳು_ಹಿಂಭಾಗ(pZip, &pState->m_central_dir_offsets, &n, 1))
  {
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_ಗಾತ್ರ, MZ_FALSE);
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  }

  pZip->m_ಒಟ್ಟು_files++;
  pZip->m_archive_ಗಾತ್ರ = cur_dst_file_ofs;

  ಹಿಂತಿರುಗಿ MZ_TRUE;
}

mz_bool mz_zip_writer_finalize_archive(mz_zip_archive *pZip)
{
  mz_zip_ಆಂತರಿಕ_state *pState;
  mz_uint64 central_dir_ofs, central_dir_ಗಾತ್ರ;
  mz_uint8 hdr[MZ_ZIP_ಕೊನೆ_ದ_CENTRAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ];

  ಆದರೆ ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_ಬಹುಲಕ != MZ_ZIP_ಬಹುಲಕ_WRITING))
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  pState = pZip->m_pState;

  // no zip64 support yet
  ಆದರೆ ((pZip->m_ಒಟ್ಟು_files > 0xFFFF) || ((pZip->m_archive_ಗಾತ್ರ + pState->m_central_dir.m_ಗಾತ್ರ + MZ_ZIP_ಕೊನೆ_ದ_CENTRAL_DIR_ಶೀರ್ಷಿಕೆ_ಗಾತ್ರ) > 0xFFFFFFFF))
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  central_dir_ofs = 0;
  central_dir_ಗಾತ್ರ = 0;
  ಆದರೆ (pZip->m_ಒಟ್ಟು_files)
  {
    // Write central directory
    central_dir_ofs = pZip->m_archive_ಗಾತ್ರ;
    central_dir_ಗಾತ್ರ = pState->m_central_dir.m_ಗಾತ್ರ;
    pZip->m_central_directory_file_ofs = central_dir_ofs;
    ಆದರೆ (pZip->m_pWrite(pZip->m_pIO_opaque, central_dir_ofs, pState->m_central_dir.m_p, (size_t)central_dir_ಗಾತ್ರ) != central_dir_ಗಾತ್ರ)
      ಹಿಂತಿರುಗಿ MZ_FALSE;
    pZip->m_archive_ಗಾತ್ರ += central_dir_ಗಾತ್ರ;
  }

  // Write end of central directory record
  MZ_CLEAR_ARR(hdr);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_SIG_OFS, MZ_ZIP_ಕೊನೆ_ದ_CENTRAL_DIR_ಶೀರ್ಷಿಕೆ_SIG);
  MZ_WRITE_LE16(hdr + MZ_ZIP_ECDH_CDIR_ಅಂಕೆ_ENTRIES_ON_DISK_OFS, pZip->m_ಒಟ್ಟು_files);
  MZ_WRITE_LE16(hdr + MZ_ZIP_ECDH_CDIR_ಒಟ್ಟು_ENTRIES_OFS, pZip->m_ಒಟ್ಟು_files);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_CDIR_ಗಾತ್ರ_OFS, central_dir_ಗಾತ್ರ);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_CDIR_OFS_OFS, central_dir_ofs);

  ಆದರೆ (pZip->m_pWrite(pZip->m_pIO_opaque, pZip->m_archive_ಗಾತ್ರ, hdr, ಗಾತ್ರ(hdr)) != ಗಾತ್ರ(hdr))
    ಹಿಂತಿರುಗಿ MZ_FALSE;
#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_STDIO
  ಆದರೆ ((pState->m_pFile) && (MZ_FFLUSH(pState->m_pFile) == EOF))
    ಹಿಂತಿರುಗಿ MZ_FALSE;
#ಆದರೆ_ಅಂತ್ಯ // #ifndef MINIZ_NO_STDIO

  pZip->m_archive_ಗಾತ್ರ += ಗಾತ್ರ(hdr);

  pZip->m_zip_ಬಹುಲಕ = MZ_ZIP_ಬಹುಲಕ_WRITING_HAS_BEEN_FINALIZED;
  ಹಿಂತಿರುಗಿ MZ_TRUE;
}

mz_bool mz_zip_writer_finalize_ರಾಶಿ_archive(mz_zip_archive *pZip, ಶೂನ್ಯ **pBuf, size_t *p_ಗಾತ್ರ)
{
  ಆದರೆ ((!pZip) || (!pZip->m_pState) || (!pBuf) || (!p_ಗಾತ್ರ))
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  ಆದರೆ (pZip->m_pWrite != mz_zip_ರಾಶಿ_write_func)
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  ಆದರೆ (!mz_zip_writer_finalize_archive(pZip))
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  *pBuf = pZip->m_pState->m_pMem;
  *p_ಗಾತ್ರ = pZip->m_pState->m_mem_ಗಾತ್ರ;
  pZip->m_pState->m_pMem = ಖಾಲಿ;
  pZip->m_pState->m_mem_ಗಾತ್ರ = pZip->m_pState->m_mem_ಸಾಮರ್ಥ್ಯ = 0;
  ಹಿಂತಿರುಗಿ MZ_TRUE;
}

mz_bool mz_zip_writer_ಕೊನೆ(mz_zip_archive *pZip)
{
  mz_zip_ಆಂತರಿಕ_state *pState;
  mz_bool ಸ್ಥಿತಿ_2 = MZ_TRUE;
  ಆದರೆ ((!pZip) || (!pZip->m_pState) || (!pZip->m_pAlloc) || (!pZip->m_pFree) || ((pZip->m_zip_ಬಹುಲಕ != MZ_ZIP_ಬಹುಲಕ_WRITING) && (pZip->m_zip_ಬಹುಲಕ != MZ_ZIP_ಬಹುಲಕ_WRITING_HAS_BEEN_FINALIZED)))
    ಹಿಂತಿರುಗಿ MZ_FALSE;

  pState = pZip->m_pState;
  pZip->m_pState = ಖಾಲಿ;
  mz_zip_array_clear(pZip, &pState->m_central_dir);
  mz_zip_array_clear(pZip, &pState->m_central_dir_offsets);
  mz_zip_array_clear(pZip, &pState->m_sorted_central_dir_offsets);

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_STDIO
  ಆದರೆ (pState->m_pFile)
  {
    MZ_FCLOSE(pState->m_pFile);
    pState->m_pFile = ಖಾಲಿ;
  }
#ಆದರೆ_ಅಂತ್ಯ // #ifndef MINIZ_NO_STDIO

  ಆದರೆ ((pZip->m_pWrite == mz_zip_ರಾಶಿ_write_func) && (pState->m_pMem))
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pState->m_pMem);
    pState->m_pMem = ಖಾಲಿ;
  }

  pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
  pZip->m_zip_ಬಹುಲಕ = MZ_ZIP_ಬಹುಲಕ_INVALID;
  ಹಿಂತಿರುಗಿ ಸ್ಥಿತಿ_2;
}

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ MINIZ_NO_STDIO
mz_bool mz_zip_ಕೂಡಿಸು_mem_ಗಮ್ಯ_archive_file_ಒಳ_ಇರಿಸು(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pZip_filename, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pArchive_name, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *pBuf, size_t buf_ಗಾತ್ರ_2, ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *pComment, mz_uint16 comment_ಗಾತ್ರ, mz_uint level_and_flags)
{
  mz_bool ಸ್ಥಿತಿ_2, created_new_archive = MZ_FALSE;
  mz_zip_archive zip_archive;
  ರಚನೆ MZ_FILE_STAT_STRUCT file_stat;
  MZ_CLEAR_OBJ(zip_archive);
  ಆದರೆ ((ಪೂರ್ಣಾಂಕ)level_and_flags < 0)
     level_and_flags = MZ_DEFAULT_LEVEL;
  ಆದರೆ ((!pZip_filename) || (!pArchive_name) || ((buf_ಗಾತ್ರ_2) && (!pBuf)) || ((comment_ಗಾತ್ರ) && (!pComment)) || ((level_and_flags & 0xF) > MZ_UBER_COMPRESSION))
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  ಆದರೆ (!mz_zip_writer_validate_archive_name(pArchive_name))
    ಹಿಂತಿರುಗಿ MZ_FALSE;
  ಆದರೆ (MZ_FILE_STAT(pZip_filename, &file_stat) != 0)
  {
    // Create a new archive.
    ಆದರೆ (!mz_zip_writer_init_file(&zip_archive, pZip_filename, 0))
      ಹಿಂತಿರುಗಿ MZ_FALSE;
    created_new_archive = MZ_TRUE;
  }
  ಇಲ್ಲದಿದ್ದರೆ
  {
    // Append to an existing archive.
    ಆದರೆ (!mz_zip_reader_init_file(&zip_archive, pZip_filename, level_and_flags | MZ_ZIP_FLAG_DO_NOT_ವಿಂಗಡಿಸು_CENTRAL_DIRECTORY))
      ಹಿಂತಿರುಗಿ MZ_FALSE;
    ಆದರೆ (!mz_zip_writer_init_from_reader(&zip_archive, pZip_filename))
    {
      mz_zip_reader_ಕೊನೆ(&zip_archive);
      ಹಿಂತಿರುಗಿ MZ_FALSE;
    }
  }
  ಸ್ಥಿತಿ_2 = mz_zip_writer_ಕೂಡಿಸು_mem_ex(&zip_archive, pArchive_name, pBuf, buf_ಗಾತ್ರ_2, pComment, comment_ಗಾತ್ರ, level_and_flags, 0, 0);
  // Always finalize, even if adding failed for some reason, so we have a valid central directory. (This may not always succeed, but we can try.)
  ಆದರೆ (!mz_zip_writer_finalize_archive(&zip_archive))
    ಸ್ಥಿತಿ_2 = MZ_FALSE;
  ಆದರೆ (!mz_zip_writer_ಕೊನೆ(&zip_archive))
    ಸ್ಥಿತಿ_2 = MZ_FALSE;
  ಆದರೆ ((!ಸ್ಥಿತಿ_2) && (created_new_archive))
  {
    // It's a new archive and something went wrong, so just delete it.
    ಪೂರ್ಣಾಂಕ ignored_ಸ್ಥಿತಿ = MZ_DELETE_FILE(pZip_filename);
    (ಶೂನ್ಯ)ignored_ಸ್ಥಿತಿ;
  }
  ಹಿಂತಿರುಗಿ ಸ್ಥಿತಿ_2;
}

ಶೂನ್ಯ *mz_zip_ಹೊರತೆಗೆ_archive_file_ಗಮ್ಯ_ರಾಶಿ(ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pZip_filename, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *pArchive_name, size_t *p_ಗಾತ್ರ, mz_uint flags)
{
  ಪೂರ್ಣಾಂಕ file_ಸೂಚ್ಯಂಕ;
  mz_zip_archive zip_archive;
  ಶೂನ್ಯ *p = ಖಾಲಿ;

  ಆದರೆ (p_ಗಾತ್ರ)
    *p_ಗಾತ್ರ = 0;

  ಆದರೆ ((!pZip_filename) || (!pArchive_name))
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;

  MZ_CLEAR_OBJ(zip_archive);
  ಆದರೆ (!mz_zip_reader_init_file(&zip_archive, pZip_filename, flags | MZ_ZIP_FLAG_DO_NOT_ವಿಂಗಡಿಸು_CENTRAL_DIRECTORY))
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;

  ಆದರೆ ((file_ಸೂಚ್ಯಂಕ = mz_zip_reader_locate_file(&zip_archive, pArchive_name, ಖಾಲಿ, flags)) >= 0)
    p = mz_zip_reader_ಹೊರತೆಗೆ_ಗಮ್ಯ_ರಾಶಿ(&zip_archive, file_ಸೂಚ್ಯಂಕ, p_ಗಾತ್ರ, flags);

  mz_zip_reader_ಕೊನೆ(&zip_archive);
  ಹಿಂತಿರುಗಿ p;
}

#ಆದರೆ_ಅಂತ್ಯ // #ifndef MINIZ_NO_STDIO

#ಆದರೆ_ಅಂತ್ಯ // #ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

#ಆದರೆ_ಅಂತ್ಯ // #ifndef MINIZ_NO_ARCHIVE_APIS

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ __cplusplus
}
#ಆದರೆ_ಅಂತ್ಯ

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _MSC_VER
#ಸೂಚನೆ warning (ತೆಗೆ)
#ಆದರೆ_ಅಂತ್ಯ

#ಆದರೆ_ಅಂತ್ಯ // MINIZ_HEADER_FILE_ONLY

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

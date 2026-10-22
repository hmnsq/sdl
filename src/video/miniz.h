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

#यदि_अपरिभाषितम् MINIZ_शीर्षकम्_INCLUDED
#परिभाषय MINIZ_शीर्षकम्_INCLUDED

/*#include <stdlib.h>*/

// Defines to completely disable specific portions of miniz.c:
// If all macros here are defined the only functionality remaining will be CRC-32, adler-32, tinfl, and tdefl.

// Define MINIZ_NO_STDIO to disable all usage and any functions which rely on stdio for file I/O.
#परिभाषय MINIZ_NO_STDIO

// If MINIZ_NO_TIME is specified then the ZIP archive functions will not be able to get the current time, or
// get/set file times, and the C run-time funcs that get/set times won't be called.
// The current downside is the times written to your archives will be from 1979.
#परिभाषय MINIZ_NO_TIME

// Define MINIZ_NO_DEFLATE_APIS to disable all compression API's.
//#define MINIZ_NO_DEFLATE_APIS

// Define MINIZ_NO_INFLATE_APIS to disable all decompression API's.
#परिभाषय MINIZ_NO_INFLATE_APIS

// Define MINIZ_NO_ARCHIVE_APIS to disable all ZIP archive API's.
#परिभाषय MINIZ_NO_ARCHIVE_APIS

// Define MINIZ_NO_ARCHIVE_APIS to disable all writing related ZIP archive API's.
#परिभाषय MINIZ_NO_ARCHIVE_WRITING_APIS

// Define MINIZ_NO_ZLIB_APIS to remove all ZLIB-style compression/decompression API's.
#परिभाषय MINIZ_NO_ZLIB_APIS

// Define MINIZ_NO_ZLIB_COMPATIBLE_NAME to disable zlib names, to prevent conflicts against stock zlib.
#परिभाषय MINIZ_NO_ZLIB_COMPATIBLE_नामानि

// Define MINIZ_NO_MALLOC to disable all calls to malloc, free, and realloc.
// Note if MINIZ_NO_MALLOC is defined then the user must always provide custom user alloc/free/realloc
// callbacks to the zlib and archive API's, and a few stand-alone helper API's which don't provide custom user
// functions (such as tdefl_compress_mem_to_heap() and tinfl_decompress_mem_to_heap()) won't work.
//#define MINIZ_NO_MALLOC
#परिभाषय MINIZ_SDL_MALLOC

#यदि_परिभाषितम् MINIZ_NO_INFLATE_APIS
#परिभाषय MINIZ_NO_ARCHIVE_APIS
#यदि_अन्तः

#यदि_परिभाषितम् MINIZ_NO_DEFLATE_APIS
#परिभाषय MINIZ_NO_ARCHIVE_WRITING_APIS
#यदि_अन्तः

// Define MINIZ_STATIC_FUNCTIONS to make all functions static. You probably
// want this if you're using miniz in a library
#परिभाषय MINIZ_STATIC_FUNCTIONS

#यदि defined(__TINYC__) && (defined(__linux) || defined(__linux__))
  // TODO: Work around "error: include file 'sys\utime.h' when compiling with tcc on Linux
  #परिभाषय MINIZ_NO_TIME
#यदि_अन्तः

#यदि !defined(MINIZ_NO_TIME) && !defined(MINIZ_NO_ARCHIVE_APIS)
  #अन्तर्भाव <time.h>
#यदि_अन्तः

#यदि defined(_M_IX86) || defined(_M_X64) || defined(__i386__) || defined(__i386) || defined(__i486__) || defined(__i486) || defined(i386) || defined(__ia64__) || defined(__x86_64__)
// MINIZ_X86_OR_X64_CPU is only used to help set the below macros.
#परिभाषय MINIZ_X86_OR_X64_CPU 1
#यदि_अन्तः

#यदि_अपरिभाषितम् MINIZ_LITTLE_ENDIAN /* if not defined by SDL */
#यदि (__BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__) || MINIZ_X86_OR_X64_CPU
// Set MINIZ_LITTLE_ENDIAN to 1 if the processor is little endian.
#परिभाषय MINIZ_LITTLE_ENDIAN 1
#यदि_अन्तः
#यदि_अन्तः // MINIZ_LITTLE_ENDIAN /* if not defined by SDL */

#यदि_अपरिभाषितम् MINIZ_USE_UNALIGNED_LOADS_AND_STORES
#यदि MINIZ_X86_OR_X64_CPU
// Set MINIZ_USE_UNALIGNED_LOADS_AND_STORES to 1 on CPU's that permit efficient integer loads and stores from unaligned addresses.
#परिभाषय MINIZ_USE_UNALIGNED_LOADS_AND_STORES 1
#यदि_अन्तः
#यदि_अन्तः // MINIZ_USE_UNALIGNED_LOADS_AND_STORES

#यदि defined(_M_X64) || defined(_WIN64) || defined(__MINGW64__) || defined(_LP64) || defined(__LP64__) || defined(__ia64__) || defined(__x86_64__)
// Set MINIZ_HAS_64BIT_REGISTERS to 1 if operations on 64-bit integers are reasonably fast (and don't involve compiler generated calls to helper functions).
#परिभाषय MINIZ_HAS_64BIT_REGISTERS 1
#यदि_अन्तः

#यदि_परिभाषितम् MINIZ_STATIC_FUNCTIONS
#परिभाषय MINIZ_STATIC स्थिर
#अन्यथा
#परिभाषय MINIZ_STATIC
#यदि_अन्तः

#यदि_परिभाषितम् __cplusplus
बाह्य "C" {
#यदि_अन्तः

// ------------------- zlib-style API Definitions.

// For more compatibility with zlib, miniz.c uses unsigned long for some parameters/struct members. Beware: mz_ulong can be either 32 or 64-bits!
प्रकारनिर्देश अचिह्नित दीर्घ mz_ulong;

// mz_free() internally uses the MZ_FREE() macro (which by default calls free() unless you've modified the MZ_MALLOC macro) to release a block allocated from the heap.
MINIZ_STATIC शून्य mz_free(शून्य *p);

#परिभाषय MZ_ADLER32_INIT (1)
// mz_adler32() returns the initial adler-32 value to use when called with ptr==NULL.
MINIZ_STATIC mz_ulong mz_adler32(mz_ulong adler, ध्रुव अचिह्नित वर्ण *ptr, size_t buf_len);

#परिभाषय MZ_चक्रीयपरीक्षा_32_INIT (0)
// mz_crc32() returns the initial CRC-32 value to use when called with ptr==NULL.
MINIZ_STATIC mz_ulong mz_चक्रीयपरीक्षा_32(mz_ulong crc, ध्रुव अचिह्नित वर्ण *ptr, size_t buf_len);

// Compression strategies.
गणना { MZ_DEFAULT_STRATEGY = 0, MZ_FILTERED = 1, MZ_HUFFMAN_ONLY = 2, MZ_RLE = 3, MZ_FIXED = 4 };

//विधानम्
#परिभाषय MZ_DEFLATED 8

#यदि_अपरिभाषितम् MINIZ_NO_ZLIB_APIS

// Heap allocation callbacks.
// Note that mz_alloc_func parameter types purpsosely differ from zlib's: items/size is size_t, not unsigned long.
प्रकारनिर्देश शून्य *(*mz_alloc_func)(शून्य *opaque, size_t वस्तूनि, size_t आकार);
प्रकारनिर्देश शून्य (*mz_free_func)(शून्य *opaque, शून्य *स्थानाङ्कः);
प्रकारनिर्देश शून्य *(*mz_realloc_func)(शून्य *opaque, शून्य *स्थानाङ्कः, size_t वस्तूनि, size_t आकार);

#परिभाषय MZ_संस्करणम्          "9.1.15"
#परिभाषय MZ_VERNUM           0x91F0
#परिभाषय MZ_VER_MAJOR        9
#परिभाषय MZ_VER_MINOR        1
#परिभाषय MZ_VER_REVISION     15
#परिभाषय MZ_VER_SUBREVISION  0

// Flush values. For typical usage you only need MZ_NO_FLUSH and MZ_FINISH. The other values are for advanced use (refer to the zlib docs).
गणना { MZ_NO_FLUSH = 0, MZ_PARTIAL_FLUSH = 1, MZ_SYNC_FLUSH = 2, MZ_पूर्णम्_FLUSH = 3, MZ_FINISH = 4, MZ_खण्डम् = 5 };

// Return status codes. MZ_PARAM_ERROR is non-standard.
गणना { MZ_OK = 0, MZ_प्रवाहः_अन्तः = 1, MZ_NEED_DICT = 2, MZ_ERRNO = -1, MZ_प्रवाहः_ERROR = -2, MZ_दत्त_ERROR = -3, MZ_MEM_ERROR = -4, MZ_BUF_ERROR = -5, MZ_संस्करणम्_ERROR = -6, MZ_PARAM_ERROR = -10000 };

// Compression levels: 0-9 are the standard zlib-style levels, 10 is best possible compression (not zlib compatible, and may be very slow), MZ_DEFAULT_COMPRESSION=MZ_DEFAULT_LEVEL.
गणना { MZ_NO_COMPRESSION = 0, MZ_BEST_जवः = 1, MZ_BEST_COMPRESSION = 9, MZ_UBER_COMPRESSION = 10, MZ_DEFAULT_LEVEL = 6, MZ_DEFAULT_COMPRESSION = -1 };

// Window bits
#परिभाषय MZ_DEFAULT_गवाक्षः_द्वयङ्काः 15

संरचना mz_आन्तरिकम्_state;

// Compression/decompression stream struct.
प्रकारनिर्देश संरचना mz_प्रवाहः_s
{
  ध्रुव अचिह्नित वर्ण *अग्र_अन्तर्;     // pointer to next byte to read
  अचिह्नित पूर्णाङ्क avail_अन्तर्;            // number of bytes available at next_in
  mz_ulong योग_अन्तर्;                // total number of bytes consumed so far

  अचिह्नित वर्ण *अग्र_बहिर्गमनम्;          // pointer to next byte to write
  अचिह्नित पूर्णाङ्क avail_बहिर्गमनम्;           // number of bytes that can be written to next_out
  mz_ulong योग_बहिर्गमनम्;               // total number of bytes produced so far

  वर्ण *सन्देशः_2;                        // error msg (unused)
  संरचना mz_आन्तरिकम्_state *state;  // internal state, allocated by zalloc/zfree

  mz_alloc_func zalloc;             // optional heap allocation function (defaults to malloc)
  mz_free_func zfree;               // optional heap free function (defaults to free)
  शून्य *opaque;                     // heap alloc function user pointer

  पूर्णाङ्क दत्त_type;                    // data_type (unused)
  mz_ulong adler;                   // adler32 of the source or uncompressed data
  mz_ulong reserved;                // not used
} mz_प्रवाहः;

प्रकारनिर्देश mz_प्रवाहः *mz_streamp;

// Returns the version string of miniz.c.
MINIZ_STATIC ध्रुव वर्ण *mz_संस्करणम्(शून्य);

#यदि_अपरिभाषितम् MINIZ_NO_DEFLATE_APIS

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
MINIZ_STATIC पूर्णाङ्क mz_deflateInit(mz_streamp p_प्रवाहः, पूर्णाङ्क level);

// mz_deflateInit2() is like mz_deflate(), except with more control:
// Additional parameters:
//   method must be MZ_DEFLATED
//   window_bits must be MZ_DEFAULT_WINDOW_BITS (to wrap the deflate stream with zlib header/adler-32 footer) or -MZ_DEFAULT_WINDOW_BITS (raw deflate/no header or footer)
//   mem_level must be between [1, 9] (it's checked but ignored by miniz.c)
MINIZ_STATIC पूर्णाङ्क mz_deflateInit2(mz_streamp p_प्रवाहः, पूर्णाङ्क level, पूर्णाङ्क विधानम्, पूर्णाङ्क गवाक्षः_द्वयङ्काः, पूर्णाङ्क mem_level, पूर्णाङ्क strategy);

// Quickly resets a compressor without having to reallocate anything. Same as calling mz_deflateEnd() followed by mz_deflateInit()/mz_deflateInit2().
MINIZ_STATIC पूर्णाङ्क mz_deflateReset(mz_streamp p_प्रवाहः);

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
MINIZ_STATIC पूर्णाङ्क mz_deflate(mz_streamp p_प्रवाहः, पूर्णाङ्क flush);

// mz_deflateEnd() deinitializes a compressor:
// Return values:
//  MZ_OK on success.
//  MZ_STREAM_ERROR if the stream is bogus.
MINIZ_STATIC पूर्णाङ्क mz_deflate_अन्तः(mz_streamp p_प्रवाहः);

// mz_deflateBound() returns a (very) conservative upper bound on the amount of data that could be generated by deflate(), assuming flush is set to only MZ_NO_FLUSH or MZ_FINISH.
MINIZ_STATIC mz_ulong mz_deflateBound(mz_streamp p_प्रवाहः, mz_ulong source_len);

// Single-call compression functions mz_compress() and mz_compress2():
// Returns MZ_OK on success, or one of the error codes from mz_deflate() on failure.
MINIZ_STATIC पूर्णाङ्क mz_compress(अचिह्नित वर्ण *pDest, mz_ulong *pDest_len, ध्रुव अचिह्नित वर्ण *pSource, mz_ulong source_len);
MINIZ_STATIC पूर्णाङ्क mz_compress2(अचिह्नित वर्ण *pDest, mz_ulong *pDest_len, ध्रुव अचिह्नित वर्ण *pSource, mz_ulong source_len, पूर्णाङ्क level);

// mz_compressBound() returns a (very) conservative upper bound on the amount of data that could be generated by calling mz_compress().
MINIZ_STATIC mz_ulong mz_compressBound(mz_ulong source_len);

#यदि_अन्तः /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#यदि_अपरिभाषितम् MINIZ_NO_INFLATE_APIS

// Initializes a decompressor.
MINIZ_STATIC पूर्णाङ्क mz_inflateInit(mz_streamp p_प्रवाहः);

// mz_inflateInit2() is like mz_inflateInit() with an additional option that controls the window size and whether or not the stream has been wrapped with a zlib header/footer:
// window_bits must be MZ_DEFAULT_WINDOW_BITS (to parse zlib header/footer) or -MZ_DEFAULT_WINDOW_BITS (raw deflate).
MINIZ_STATIC पूर्णाङ्क mz_inflateInit2(mz_streamp p_प्रवाहः, पूर्णाङ्क गवाक्षः_द्वयङ्काः);

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
MINIZ_STATIC पूर्णाङ्क mz_inflate(mz_streamp p_प्रवाहः, पूर्णाङ्क flush);

// Deinitializes a decompressor.
MINIZ_STATIC पूर्णाङ्क mz_inflate_अन्तः(mz_streamp p_प्रवाहः);

// Single-call decompression.
// Returns MZ_OK on success, or one of the error codes from mz_inflate() on failure.
MINIZ_STATIC पूर्णाङ्क mz_uncompress(अचिह्नित वर्ण *pDest, mz_ulong *pDest_len, ध्रुव अचिह्नित वर्ण *pSource, mz_ulong source_len);
#यदि_अन्तः /*#ifndef MINIZ_NO_INFLATE_APIS*/

// Returns a string description of the specified error code, or NULL if the error code is invalid.
MINIZ_STATIC ध्रुव वर्ण *mz_error(पूर्णाङ्क err);

// Redefine zlib-compatible names to miniz equivalents, so miniz.c can be used as a drop-in replacement for the subset of zlib that miniz.c supports.
// Define MINIZ_NO_ZLIB_COMPATIBLE_NAMES to disable zlib-compatibility if you use zlib in the same project.
#यदि_अपरिभाषितम् MINIZ_NO_ZLIB_COMPATIBLE_नामानि
  प्रकारनिर्देश अचिह्नित वर्ण Byte;
  प्रकारनिर्देश अचिह्नित पूर्णाङ्क uInt;
  प्रकारनिर्देश mz_ulong uLong;
  प्रकारनिर्देश Byte Bytef;
  प्रकारनिर्देश uInt uIntf;
  प्रकारनिर्देश वर्ण charf;
  प्रकारनिर्देश पूर्णाङ्क intf;
  प्रकारनिर्देश शून्य *voidpf;
  प्रकारनिर्देश uLong uLongf;
  प्रकारनिर्देश शून्य *voidp;
  प्रकारनिर्देश शून्य *ध्रुव voidpc;
  #परिभाषय Z_NULL                0
  #परिभाषय Z_NO_FLUSH            MZ_NO_FLUSH
  #परिभाषय Z_PARTIAL_FLUSH       MZ_PARTIAL_FLUSH
  #परिभाषय Z_SYNC_FLUSH          MZ_SYNC_FLUSH
  #परिभाषय Z_पूर्णम्_FLUSH          MZ_पूर्णम्_FLUSH
  #परिभाषय Z_FINISH              MZ_FINISH
  #परिभाषय Z_खण्डम्               MZ_खण्डम्
  #परिभाषय Z_OK                  MZ_OK
  #परिभाषय Z_प्रवाहः_अन्तः          MZ_प्रवाहः_अन्तः
  #परिभाषय Z_NEED_DICT           MZ_NEED_DICT
  #परिभाषय Z_ERRNO               MZ_ERRNO
  #परिभाषय Z_प्रवाहः_ERROR        MZ_प्रवाहः_ERROR
  #परिभाषय Z_दत्त_ERROR          MZ_दत्त_ERROR
  #परिभाषय Z_MEM_ERROR           MZ_MEM_ERROR
  #परिभाषय Z_BUF_ERROR           MZ_BUF_ERROR
  #परिभाषय Z_संस्करणम्_ERROR       MZ_संस्करणम्_ERROR
  #परिभाषय Z_PARAM_ERROR         MZ_PARAM_ERROR
  #परिभाषय Z_NO_COMPRESSION      MZ_NO_COMPRESSION
  #परिभाषय Z_BEST_जवः          MZ_BEST_जवः
  #परिभाषय Z_BEST_COMPRESSION    MZ_BEST_COMPRESSION
  #परिभाषय Z_DEFAULT_COMPRESSION MZ_DEFAULT_COMPRESSION
  #परिभाषय Z_DEFAULT_STRATEGY    MZ_DEFAULT_STRATEGY
  #परिभाषय Z_FILTERED            MZ_FILTERED
  #परिभाषय Z_HUFFMAN_ONLY        MZ_HUFFMAN_ONLY
  #परिभाषय Z_RLE                 MZ_RLE
  #परिभाषय Z_FIXED               MZ_FIXED
  #परिभाषय Z_DEFLATED            MZ_DEFLATED
  #परिभाषय Z_DEFAULT_गवाक्षः_द्वयङ्काः MZ_DEFAULT_गवाक्षः_द्वयङ्काः
  #परिभाषय alloc_func            mz_alloc_func
  #परिभाषय free_func             mz_free_func
  #परिभाषय आन्तरिकम्_state        mz_आन्तरिकम्_state
  #परिभाषय z_प्रवाहः              mz_प्रवाहः
#यदि_अपरिभाषितम् MINIZ_NO_DEFLATE_APIS
  #परिभाषय deflateInit           mz_deflateInit
  #परिभाषय deflateInit2          mz_deflateInit2
  #परिभाषय deflateReset          mz_deflateReset
  #परिभाषय deflate               mz_deflate
  #परिभाषय deflate_अन्तः            mz_deflate_अन्तः
  #परिभाषय deflateBound          mz_deflateBound
  #परिभाषय compress              mz_compress
  #परिभाषय compress2             mz_compress2
  #परिभाषय compressBound         mz_compressBound
#यदि_अन्तः /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#यदि_अपरिभाषितम् MINIZ_NO_INFLATE_APIS
  #परिभाषय inflateInit           mz_inflateInit
  #परिभाषय inflateInit2          mz_inflateInit2
  #परिभाषय inflate               mz_inflate
  #परिभाषय inflate_अन्तः            mz_inflate_अन्तः
  #परिभाषय uncompress            mz_uncompress
#यदि_अन्तः /*#ifndef MINIZ_NO_INFLATE_APIS*/
  #परिभाषय चक्रीयपरीक्षा_32                 mz_चक्रीयपरीक्षा_32
  #परिभाषय adler32               mz_adler32
  #परिभाषय MAX_WBITS             15
  #परिभाषय MAX_MEM_LEVEL         9
  #परिभाषय zError                mz_error
  #परिभाषय ZLIB_संस्करणम्          MZ_संस्करणम्
  #परिभाषय ZLIB_VERNUM           MZ_VERNUM
  #परिभाषय ZLIB_VER_MAJOR        MZ_VER_MAJOR
  #परिभाषय ZLIB_VER_MINOR        MZ_VER_MINOR
  #परिभाषय ZLIB_VER_REVISION     MZ_VER_REVISION
  #परिभाषय ZLIB_VER_SUBREVISION  MZ_VER_SUBREVISION
  #परिभाषय zlib_संस्करणम्           mz_संस्करणम्
  #परिभाषय zlib_संस्करणम्_2          mz_संस्करणम्()
#यदि_अन्तः // #ifndef MINIZ_NO_ZLIB_COMPATIBLE_NAMES

#यदि_अन्तः // MINIZ_NO_ZLIB_APIS

// ------------------- Types and macros

प्रकारनिर्देश अचिह्नित वर्ण mz_uint8;
प्रकारनिर्देश चिह्नित ह्रस्व mz_int16;
प्रकारनिर्देश अचिह्नित ह्रस्व mz_uint16;
प्रकारनिर्देश अचिह्नित पूर्णाङ्क mz_uint32;
प्रकारनिर्देश अचिह्नित पूर्णाङ्क mz_uint;
प्रकारनिर्देश दीर्घ दीर्घ mz_int64;
प्रकारनिर्देश अचिह्नित दीर्घ दीर्घ mz_uint64;
प्रकारनिर्देश पूर्णाङ्क mz_bool;

#परिभाषय MZ_FALSE (0)
#परिभाषय MZ_TRUE (1)

// An attempt to work around MSVC's spammy "warning C4127: conditional expression is constant" message.
#यदि_परिभाषितम् _MSC_VER
   #परिभाषय MZ_MACRO_अन्तः यावत् (0, 0)
#अन्यथा
   #परिभाषय MZ_MACRO_अन्तः यावत् (0)
#यदि_अन्तः

// ------------------- ZIP archive reading/writing

#यदि_अपरिभाषितम् MINIZ_NO_ARCHIVE_APIS

गणना
{
  MZ_ZIP_MAX_IO_BUF_आकार = 64*1024,
  MZ_ZIP_MAX_ARCHIVE_FILENAME_आकार = 260,
  MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_आकार = 256
};

प्रकारनिर्देश संरचना
{
  mz_uint32 m_file_सूचकांक;
  mz_uint32 m_central_dir_ofs;
  mz_uint16 m_संस्करणम्_made_by;
  mz_uint16 m_संस्करणम्_needed;
  mz_uint16 m_bit_flag;
  mz_uint16 m_विधानम्;
#यदि_अपरिभाषितम् MINIZ_NO_TIME
  time_t m_time;
#यदि_अन्तः
  mz_uint32 m_चक्रीयपरीक्षा_32;
  mz_uint64 m_comp_आकार;
  mz_uint64 m_uncomp_आकार;
  mz_uint16 m_आन्तरिकम्_attr;
  mz_uint32 m_external_attr;
  mz_uint64 m_local_शीर्षकम्_ofs;
  mz_uint32 m_comment_आकार;
  वर्ण m_filename[MZ_ZIP_MAX_ARCHIVE_FILENAME_आकार];
  वर्ण m_comment[MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_आकार];
} mz_zip_archive_file_stat;

प्रकारनिर्देश size_t (*mz_file_read_func)(शून्य *pOpaque, mz_uint64 file_ofs, शून्य *pBuf, size_t n);
प्रकारनिर्देश size_t (*mz_file_write_func)(शून्य *pOpaque, mz_uint64 file_ofs, ध्रुव शून्य *pBuf, size_t n);

संरचना mz_zip_आन्तरिकम्_state_चिह्नकम्;
प्रकारनिर्देश संरचना mz_zip_आन्तरिकम्_state_चिह्नकम् mz_zip_आन्तरिकम्_state;

प्रकारनिर्देश गणना
{
  MZ_ZIP_बहुलकम्_INVALID = 0,
  MZ_ZIP_बहुलकम्_READING = 1,
  MZ_ZIP_बहुलकम्_WRITING = 2,
  MZ_ZIP_बहुलकम्_WRITING_HAS_BEEN_FINALIZED = 3
} mz_zip_बहुलकम्;

प्रकारनिर्देश संरचना mz_zip_archive_चिह्नकम्
{
  mz_uint64 m_archive_आकार;
  mz_uint64 m_central_directory_file_ofs;
  mz_uint m_योग_files;
  mz_zip_बहुलकम् m_zip_बहुलकम्;

  mz_uint m_file_विस्थापनम्_alignment;

  mz_alloc_func m_pAlloc;
  mz_free_func m_pFree;
  mz_realloc_func m_pRealloc;
  शून्य *m_pAlloc_opaque;

  mz_file_read_func m_pRead;
  mz_file_write_func m_pWrite;
  शून्य *m_pIO_opaque;

  mz_zip_आन्तरिकम्_state *m_pState;

} mz_zip_archive;

प्रकारनिर्देश गणना
{
  MZ_ZIP_FLAG_CASE_SENSITIVE                = 0x0100,
  MZ_ZIP_FLAG_IGNORE_मार्गः                   = 0x0200,
  MZ_ZIP_FLAG_COMPRESSED_दत्त               = 0x0400,
  MZ_ZIP_FLAG_DO_NOT_क्रमय_CENTRAL_DIRECTORY = 0x0800
} mz_zip_flags;

// ZIP archive reading

// Inits a ZIP archive reader.
// These functions read and validate the archive's central directory.
MINIZ_STATIC mz_bool mz_zip_reader_init(mz_zip_archive *pZip, mz_uint64 आकार, mz_uint32 flags);
MINIZ_STATIC mz_bool mz_zip_reader_init_mem(mz_zip_archive *pZip, ध्रुव शून्य *pMem, size_t आकार, mz_uint32 flags);

#यदि_अपरिभाषितम् MINIZ_NO_STDIO
MINIZ_STATIC mz_bool mz_zip_reader_init_file(mz_zip_archive *pZip, ध्रुव वर्ण *pFilename, mz_uint32 flags);
#यदि_अन्तः

// Returns the total number of files in the archive.
MINIZ_STATIC mz_uint mz_zip_reader_get_अङ्कः_files(mz_zip_archive *pZip);

// Returns detailed information about an archive file entry.
MINIZ_STATIC mz_bool mz_zip_reader_file_stat(mz_zip_archive *pZip, mz_uint file_सूचकांक, mz_zip_archive_file_stat *pStat);

// Determines if an archive file entry is a directory entry.
MINIZ_STATIC mz_bool mz_zip_reader_is_file_a_directory(mz_zip_archive *pZip, mz_uint file_सूचकांक);
MINIZ_STATIC mz_bool mz_zip_reader_is_file_encrypted(mz_zip_archive *pZip, mz_uint file_सूचकांक);

// Retrieves the filename of an archive file entry.
// Returns the number of bytes written to pFilename, or if filename_buf_size is 0 this function returns the number of bytes needed to fully store the filename.
MINIZ_STATIC mz_uint mz_zip_reader_get_filename(mz_zip_archive *pZip, mz_uint file_सूचकांक, वर्ण *pFilename, mz_uint filename_buf_आकार);

// Attempts to locates a file in the archive's central directory.
// Valid flags: MZ_ZIP_FLAG_CASE_SENSITIVE, MZ_ZIP_FLAG_IGNORE_PATH
// Returns -1 if the file cannot be found.
MINIZ_STATIC पूर्णाङ्क mz_zip_reader_locate_file(mz_zip_archive *pZip, ध्रुव वर्ण *pName, ध्रुव वर्ण *pComment, mz_uint flags);

// Extracts a archive file to a memory buffer using no memory allocation.
MINIZ_STATIC mz_bool mz_zip_reader_extract_गन्तव्यम्_mem_no_alloc(mz_zip_archive *pZip, mz_uint file_सूचकांक, शून्य *pBuf, size_t buf_आकार_2, mz_uint flags, शून्य *pUser_read_buf, size_t user_read_buf_आकार);
MINIZ_STATIC mz_bool mz_zip_reader_extract_file_गन्तव्यम्_mem_no_alloc(mz_zip_archive *pZip, ध्रुव वर्ण *pFilename, शून्य *pBuf, size_t buf_आकार_2, mz_uint flags, शून्य *pUser_read_buf, size_t user_read_buf_आकार);

// Extracts a archive file to a memory buffer.
MINIZ_STATIC mz_bool mz_zip_reader_extract_गन्तव्यम्_mem(mz_zip_archive *pZip, mz_uint file_सूचकांक, शून्य *pBuf, size_t buf_आकार_2, mz_uint flags);
MINIZ_STATIC mz_bool mz_zip_reader_extract_file_गन्तव्यम्_mem(mz_zip_archive *pZip, ध्रुव वर्ण *pFilename, शून्य *pBuf, size_t buf_आकार_2, mz_uint flags);

// Extracts a archive file to a dynamically allocated heap buffer.
MINIZ_STATIC शून्य *mz_zip_reader_extract_गन्तव्यम्_heap(mz_zip_archive *pZip, mz_uint file_सूचकांक, size_t *p_आकार, mz_uint flags);
MINIZ_STATIC शून्य *mz_zip_reader_extract_file_गन्तव्यम्_heap(mz_zip_archive *pZip, ध्रुव वर्ण *pFilename, size_t *p_आकार, mz_uint flags);

// Extracts a archive file using a callback function to output the file's data.
MINIZ_STATIC mz_bool mz_zip_reader_extract_गन्तव्यम्_callback(mz_zip_archive *pZip, mz_uint file_सूचकांक, mz_file_write_func pCallback, शून्य *pOpaque, mz_uint flags);
MINIZ_STATIC mz_bool mz_zip_reader_extract_file_गन्तव्यम्_callback(mz_zip_archive *pZip, ध्रुव वर्ण *pFilename, mz_file_write_func pCallback, शून्य *pOpaque, mz_uint flags);

#यदि_अपरिभाषितम् MINIZ_NO_STDIO
// Extracts a archive file to a disk file and sets its last accessed and modified times.
// This function only extracts files, not archive directory records.
MINIZ_STATIC mz_bool mz_zip_reader_extract_गन्तव्यम्_file(mz_zip_archive *pZip, mz_uint file_सूचकांक, ध्रुव वर्ण *pDst_filename, mz_uint flags);
MINIZ_STATIC mz_bool mz_zip_reader_extract_file_गन्तव्यम्_file(mz_zip_archive *pZip, ध्रुव वर्ण *pArchive_filename, ध्रुव वर्ण *pDst_filename, mz_uint flags);
#यदि_अन्तः

// Ends archive reading, freeing all allocations, and closing the input archive file if mz_zip_reader_init_file() was used.
MINIZ_STATIC mz_bool mz_zip_reader_अन्तः(mz_zip_archive *pZip);

// ZIP archive writing

#यदि_अपरिभाषितम् MINIZ_NO_ARCHIVE_WRITING_APIS

// Inits a ZIP archive writer.
MINIZ_STATIC mz_bool mz_zip_writer_init(mz_zip_archive *pZip, mz_uint64 existing_आकार);
MINIZ_STATIC mz_bool mz_zip_writer_init_heap(mz_zip_archive *pZip, size_t आकार_गन्तव्यम्_reserve_at_beginning, size_t initial_आवण्टनम्_आकार);

#यदि_अपरिभाषितम् MINIZ_NO_STDIO
MINIZ_STATIC mz_bool mz_zip_writer_init_file(mz_zip_archive *pZip, ध्रुव वर्ण *pFilename, mz_uint64 आकार_गन्तव्यम्_reserve_at_beginning);
#यदि_अन्तः

// Converts a ZIP archive reader object into a writer object, to allow efficient in-place file appends to occur on an existing archive.
// For archives opened using mz_zip_reader_init_file, pFilename must be the archive's filename so it can be reopened for writing. If the file can't be reopened, mz_zip_reader_end() will be called.
// For archives opened using mz_zip_reader_init_mem, the memory block must be growable using the realloc callback (which defaults to realloc unless you've overridden it).
// Finally, for archives opened using mz_zip_reader_init, the mz_zip_archive's user provided m_pWrite function cannot be NULL.
// Note: In-place archive modification is not recommended unless you know what you're doing, because if execution stops or something goes wrong before
// the archive is finalized the file's central directory will be hosed.
MINIZ_STATIC mz_bool mz_zip_writer_init_from_reader(mz_zip_archive *pZip, ध्रुव वर्ण *pFilename);

// Adds the contents of a memory buffer to an archive. These functions record the current local time into the archive.
// To add a directory entry, call this method with an archive name ending in a forwardslash with empty buffer.
// level_and_flags - compression level (0-10, see MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or just set to MZ_DEFAULT_COMPRESSION.
MINIZ_STATIC mz_bool mz_zip_writer_सङ्कलय_mem(mz_zip_archive *pZip, ध्रुव वर्ण *pArchive_name, ध्रुव शून्य *pBuf, size_t buf_आकार_2, mz_uint level_and_flags);
MINIZ_STATIC mz_bool mz_zip_writer_सङ्कलय_mem_ex(mz_zip_archive *pZip, ध्रुव वर्ण *pArchive_name, ध्रुव शून्य *pBuf, size_t buf_आकार_2, ध्रुव शून्य *pComment, mz_uint16 comment_आकार, mz_uint level_and_flags, mz_uint64 uncomp_आकार, mz_uint32 uncomp_चक्रीयपरीक्षा_32);

#यदि_अपरिभाषितम् MINIZ_NO_STDIO
// Adds the contents of a disk file to an archive. This function also records the disk file's modified time into the archive.
// level_and_flags - compression level (0-10, see MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or just set to MZ_DEFAULT_COMPRESSION.
MINIZ_STATIC mz_bool mz_zip_writer_सङ्कलय_file(mz_zip_archive *pZip, ध्रुव वर्ण *pArchive_name, ध्रुव वर्ण *pSrc_filename, ध्रुव शून्य *pComment, mz_uint16 comment_आकार, mz_uint level_and_flags);
#यदि_अन्तः

// Adds a file to an archive by fully cloning the data from another archive.
// This function fully clones the source file's compressed data (no recompression), along with its full filename, extra data, and comment fields.
MINIZ_STATIC mz_bool mz_zip_writer_सङ्कलय_from_zip_reader(mz_zip_archive *pZip, mz_zip_archive *pSource_zip, mz_uint file_सूचकांक);

// Finalizes the archive by writing the central directory records followed by the end of central directory record.
// After an archive is finalized, the only valid call on the mz_zip_archive struct is mz_zip_writer_end().
// An archive must be manually finalized by calling this function for it to be valid.
MINIZ_STATIC mz_bool mz_zip_writer_finalize_archive(mz_zip_archive *pZip);
MINIZ_STATIC mz_bool mz_zip_writer_finalize_heap_archive(mz_zip_archive *pZip, शून्य **pBuf, size_t *p_आकार);

// Ends archive writing, freeing all allocations, and closing the output file if mz_zip_writer_init_file() was used.
// Note for the archive to be valid, it must have been finalized before ending.
MINIZ_STATIC mz_bool mz_zip_writer_अन्तः(mz_zip_archive *pZip);

// Misc. high-level helper functions:

// mz_zip_add_mem_to_archive_file_in_place() efficiently (but not atomically) appends a memory blob to a ZIP archive.
// level_and_flags - compression level (0-10, see MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or just set to MZ_DEFAULT_COMPRESSION.
MINIZ_STATIC mz_bool mz_zip_सङ्कलय_mem_गन्तव्यम्_archive_file_अन्तर्_place(ध्रुव वर्ण *pZip_filename, ध्रुव वर्ण *pArchive_name, ध्रुव शून्य *pBuf, size_t buf_आकार_2, ध्रुव शून्य *pComment, mz_uint16 comment_आकार, mz_uint level_and_flags);

// Reads a single file from an archive into a heap block.
// Returns NULL on failure.
MINIZ_STATIC शून्य *mz_zip_extract_archive_file_गन्तव्यम्_heap(ध्रुव वर्ण *pZip_filename, ध्रुव वर्ण *pArchive_name, size_t *p_आकार, mz_uint zip_flags);

#यदि_अन्तः // #ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

#यदि_अन्तः // #ifndef MINIZ_NO_ARCHIVE_APIS

// ------------------- Low-level Decompression API Definitions
#यदि_अपरिभाषितम् MINIZ_NO_INFLATE_APIS

// Decompression flags used by tinfl_decompress().
// TINFL_FLAG_PARSE_ZLIB_HEADER: If set, the input has a valid zlib header and ends with an adler32 checksum (it's a valid zlib stream). Otherwise, the input is a raw deflate stream.
// TINFL_FLAG_HAS_MORE_INPUT: If set, there are more input bytes available beyond the end of the supplied input buffer. If clear, the input buffer contains all remaining input.
// TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF: If set, the output buffer is large enough to hold the entire decompressed stream. If clear, the output buffer is at least the size of the dictionary (typically 32KB).
// TINFL_FLAG_COMPUTE_ADLER32: Force adler-32 checksum computation of the decompressed bytes.
गणना
{
  TINFL_FLAG_PARSE_ZLIB_शीर्षकम् = 1,
  TINFL_FLAG_HAS_अधिकम्_निवेशः = 2,
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
MINIZ_STATIC शून्य *tinfl_decompress_mem_गन्तव्यम्_heap(ध्रुव शून्य *pSrc_buf, size_t src_buf_len, size_t *p_बहिर्गमनम्_len, पूर्णाङ्क flags);

// tinfl_decompress_mem_to_mem() decompresses a block in memory to another block in memory.
// Returns TINFL_DECOMPRESS_MEM_TO_MEM_FAILED on failure, or the number of bytes written on success.
#परिभाषय TINFL_DECOMPRESS_MEM_गन्तव्यम्_MEM_FAILED ((size_t)(-1))
MINIZ_STATIC size_t tinfl_decompress_mem_गन्तव्यम्_mem(शून्य *p_बहिर्गमनम्_buf, size_t बहिर्गमनम्_buf_len, ध्रुव शून्य *pSrc_buf, size_t src_buf_len, पूर्णाङ्क flags);

// tinfl_decompress_mem_to_callback() decompresses a block in memory to an internal 32KB buffer, and a user provided callback function will be called to flush the buffer.
// Returns 1 on success or 0 on failure.
प्रकारनिर्देश पूर्णाङ्क (*tinfl_put_buf_func_ptr)(ध्रुव शून्य* pBuf, पूर्णाङ्क len, शून्य *pUser);
MINIZ_STATIC पूर्णाङ्क tinfl_decompress_mem_गन्तव्यम्_callback(ध्रुव शून्य *p_अन्तर्_buf, size_t *p_अन्तर्_buf_आकार, tinfl_put_buf_func_ptr pPut_buf_func, शून्य *pPut_buf_user, पूर्णाङ्क flags);

संरचना tinfl_decompressor_चिह्नकम्; प्रकारनिर्देश संरचना tinfl_decompressor_चिह्नकम् tinfl_decompressor;

// Max size of LZ dictionary.
#परिभाषय TINFL_LZ_DICT_आकार 32768

// Return status.
प्रकारनिर्देश गणना
{
  TINFL_स्थितिः_BAD_PARAM = -3,
  TINFL_स्थितिः_ADLER32_MISMATCH = -2,
  TINFL_स्थितिः_FAILED = -1,
  TINFL_स्थितिः_समाप्तम् = 0,
  TINFL_स्थितिः_NEEDS_अधिकम्_निवेशः = 1,
  TINFL_स्थितिः_HAS_अधिकम्_OUTPUT = 2
} tinfl_स्थितिः;

// Initializes the decompressor to its initial state.
#परिभाषय tinfl_init(r) कुरु { (r)->m_state = 0; } MZ_MACRO_अन्तः
#परिभाषय tinfl_get_adler32(r) (r)->m_check_adler32

// Main low-level decompressor coroutine function. This is the only function actually needed for decompression. All the other functions are just high-level helpers for improved usability.
// This is a universal API, i.e. it can be used as a building block to build any desired higher level decompression API. In the limit case, it can be called once per every byte input or output.
MINIZ_STATIC tinfl_स्थितिः tinfl_decompress(tinfl_decompressor *r, ध्रुव mz_uint8 *p_अन्तर्_buf_अग्र, size_t *p_अन्तर्_buf_आकार, mz_uint8 *p_बहिर्गमनम्_buf_start, mz_uint8 *p_बहिर्गमनम्_buf_अग्र, size_t *p_बहिर्गमनम्_buf_आकार, ध्रुव mz_uint32 decomp_flags);

// Internal/private bits follow.
गणना
{
  TINFL_MAX_HUFF_TABLES = 3, TINFL_MAX_HUFF_SYMBOLS_0 = 288, TINFL_MAX_HUFF_SYMBOLS_1 = 32, TINFL_MAX_HUFF_SYMBOLS_2 = 19,
  TINFL_FAST_LOOKUP_द्वयङ्काः = 10, TINFL_FAST_LOOKUP_आकार = 1 << TINFL_FAST_LOOKUP_द्वयङ्काः
};

प्रकारनिर्देश संरचना
{
  mz_uint8 m_संहिता_आकार[TINFL_MAX_HUFF_SYMBOLS_0];
  mz_int16 m_look_ऊर्ध्वम्[TINFL_FAST_LOOKUP_आकार], m_वृक्षः[TINFL_MAX_HUFF_SYMBOLS_0 * 2];
} tinfl_huff_सारणी;

#यदि MINIZ_HAS_64BIT_REGISTERS
  #परिभाषय TINFL_USE_64BIT_BITBUF 1
#यदि_अन्तः

#यदि TINFL_USE_64BIT_BITBUF
  प्रकारनिर्देश mz_uint64 tinfl_bit_buf_t;
  #परिभाषय TINFL_BITBUF_आकार (64)
#अन्यथा
  प्रकारनिर्देश mz_uint32 tinfl_bit_buf_t;
  #परिभाषय TINFL_BITBUF_आकार (32)
#यदि_अन्तः

संरचना tinfl_decompressor_चिह्नकम्
{
  mz_uint32 m_state, m_अङ्कः_द्वयङ्काः, m_zhdr0, m_zhdr1, m_z_adler32, m_final, m_type, m_check_adler32, m_dist, m_गणक, m_अङ्कः_extra, m_सारणी_sizes[TINFL_MAX_HUFF_TABLES];
  tinfl_bit_buf_t m_bit_buf;
  size_t m_dist_from_बहिर्गमनम्_buf_start;
  tinfl_huff_सारणी m_tables[TINFL_MAX_HUFF_TABLES];
  mz_uint8 m_raw_शीर्षकम्[4], m_len_codes[TINFL_MAX_HUFF_SYMBOLS_0 + TINFL_MAX_HUFF_SYMBOLS_1 + 137];
};
#यदि_अन्तः /*#ifndef MINIZ_NO_INFLATE_APIS*/

// ------------------- Low-level Compression API Definitions
#यदि_अपरिभाषितम् MINIZ_NO_DEFLATE_APIS

// Set TDEFL_LESS_MEMORY to 1 to use less memory (compression will be slightly slower, and raw/dynamic blocks will be output more frequently).
#परिभाषय TDEFL_LESS_स्मृतिः 0

// tdefl_init() compression flags logically OR'd together (low 12 bits contain the max. number of probes per dictionary search):
// TDEFL_DEFAULT_MAX_PROBES: The compressor defaults to 128 dictionary probes per dictionary search. 0=Huffman only, 1=Huffman+LZ (fastest/crap compression), 4095=Huffman+LZ (slowest/best compression).
गणना
{
  TDEFL_HUFFMAN_ONLY = 0, TDEFL_DEFAULT_MAX_PROBES = 128, TDEFL_MAX_PROBES_आवरणम् = 0xFFF
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
गणना
{
  TDEFL_WRITE_ZLIB_शीर्षकम्             = 0x01000,
  TDEFL_COMPUTE_ADLER32               = 0x02000,
  TDEFL_GREEDY_PARSING_FLAG           = 0x04000,
  TDEFL_NONDETERMINISTIC_PARSING_FLAG = 0x08000,
  TDEFL_RLE_MATCHES                   = 0x10000,
  TDEFL_FILTER_MATCHES                = 0x20000,
  TDEFL_FORCE_ALL_STATIC_खण्डानि       = 0x40000,
  TDEFL_FORCE_ALL_RAW_खण्डानि          = 0x80000
};

#यदि_अपरिभाषितम् MINIZ_SDL_NOUNUSED
// High level compression functions:
// tdefl_compress_mem_to_heap() compresses a block in memory to a heap block allocated via malloc().
// On entry:
//  pSrc_buf, src_buf_len: Pointer and size of source block to compress.
//  flags: The max match finder probes (default is 128) logically OR'd against the above flags. Higher probes are slower but improve compression.
// On return:
//  Function returns a pointer to the compressed data, or NULL on failure.
//  *pOut_len will be set to the compressed data's size, which could be larger than src_buf_len on uncompressible data.
//  The caller must free() the returned block when it's no longer needed.
MINIZ_STATIC शून्य *tdefl_compress_mem_गन्तव्यम्_heap(ध्रुव शून्य *pSrc_buf, size_t src_buf_len, size_t *p_बहिर्गमनम्_len, पूर्णाङ्क flags);

// tdefl_compress_mem_to_mem() compresses a block in memory to another block in memory.
// Returns 0 on failure.
MINIZ_STATIC size_t tdefl_compress_mem_गन्तव्यम्_mem(शून्य *p_बहिर्गमनम्_buf, size_t बहिर्गमनम्_buf_len, ध्रुव शून्य *pSrc_buf, size_t src_buf_len, पूर्णाङ्क flags);
#यदि_अन्तः /* MINIZ_SDL_NOUNUSED */

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
MINIZ_STATIC शून्य *tdefl_write_image_गन्तव्यम्_png_file_अन्तर्_स्मृतिः_ex(ध्रुव शून्य *pImage, पूर्णाङ्क w, पूर्णाङ्क h, पूर्णाङ्क अङ्कः_chans, पूर्णाङ्क bpl, size_t *p_Len_बहिर्गमनम्, mz_uint level, mz_bool flip, mz_uint8 *plte, पूर्णाङ्क plte_आकार, mz_uint8 *trns, पूर्णाङ्क trns_आकार);
#यदि_अपरिभाषितम् MINIZ_SDL_NOUNUSED
MINIZ_STATIC शून्य *tdefl_write_image_गन्तव्यम्_png_file_अन्तर्_स्मृतिः(ध्रुव शून्य *pImage, पूर्णाङ्क w, पूर्णाङ्क h, पूर्णाङ्क अङ्कः_chans, पूर्णाङ्क bpl, size_t *p_Len_बहिर्गमनम्);
#यदि_अन्तः

// Output stream interface. The compressor uses this interface to write compressed data. It'll typically be called TDEFL_OUT_BUF_SIZE at a time.
प्रकारनिर्देश mz_bool (*tdefl_put_buf_func_ptr)(ध्रुव शून्य* pBuf, पूर्णाङ्क len, शून्य *pUser);

#यदि_अपरिभाषितम् MINIZ_SDL_NOUNUSED
// tdefl_compress_mem_to_output() compresses a block to an output stream. The above helpers use this function internally.
MINIZ_STATIC mz_bool tdefl_compress_mem_गन्तव्यम्_output(ध्रुव शून्य *pBuf, size_t buf_len, tdefl_put_buf_func_ptr pPut_buf_func, शून्य *pPut_buf_user, पूर्णाङ्क flags);
#यदि_अन्तः

//enum { TDEFL_MAX_HUFF_TABLES = 3, TDEFL_MAX_HUFF_SYMBOLS_0 = 288, TDEFL_MAX_HUFF_SYMBOLS_1 = 32, TDEFL_MAX_HUFF_SYMBOLS_2 = 19, TDEFL_LZ_DICT_SIZE = 32768, TDEFL_LZ_DICT_SIZE_MASK = TDEFL_LZ_DICT_SIZE - 1, TDEFL_MIN_MATCH_LEN = 3, TDEFL_MAX_MATCH_LEN = 258 };
#परिभाषय TDEFL_MAX_HUFF_TABLES	3
#परिभाषय TDEFL_MAX_HUFF_SYMBOLS_0 288
#परिभाषय TDEFL_MAX_HUFF_SYMBOLS_1 32
#परिभाषय TDEFL_MAX_HUFF_SYMBOLS_2 19
#परिभाषय TDEFL_LZ_DICT_आकार 32768
#परिभाषय TDEFL_LZ_DICT_आकार_आवरणम्	( TDEFL_LZ_DICT_आकार - 1 )
#परिभाषय TDEFL_MIN_मेलनम्_LEN	3
#परिभाषय TDEFL_MAX_मेलनम्_LEN 258

// TDEFL_OUT_BUF_SIZE MUST be large enough to hold a single entire compressed output block (using static/fixed Huffman codes).
#यदि TDEFL_LESS_स्मृतिः
गणना { TDEFL_LZ_संहिता_BUF_आकार = 24 * 1024, TDEFL_बहिर्गमनम्_BUF_आकार = (TDEFL_LZ_संहिता_BUF_आकार * 13 ) / 10, TDEFL_MAX_HUFF_SYMBOLS = 288, TDEFL_LZ_HASH_द्वयङ्काः = 12, TDEFL_LEVEL1_HASH_आकार_आवरणम् = 4095, TDEFL_LZ_HASH_सरणम् = (TDEFL_LZ_HASH_द्वयङ्काः + 2) / 3, TDEFL_LZ_HASH_आकार = 1 << TDEFL_LZ_HASH_द्वयङ्काः };
#अन्यथा
गणना { TDEFL_LZ_संहिता_BUF_आकार = 64 * 1024, TDEFL_बहिर्गमनम्_BUF_आकार = (TDEFL_LZ_संहिता_BUF_आकार * 13 ) / 10, TDEFL_MAX_HUFF_SYMBOLS = 288, TDEFL_LZ_HASH_द्वयङ्काः = 15, TDEFL_LEVEL1_HASH_आकार_आवरणम् = 4095, TDEFL_LZ_HASH_सरणम् = (TDEFL_LZ_HASH_द्वयङ्काः + 2) / 3, TDEFL_LZ_HASH_आकार = 1 << TDEFL_LZ_HASH_द्वयङ्काः };
#यदि_अन्तः

// The low-level tdefl functions below may be used directly if the above helper functions aren't flexible enough. The low-level functions don't make any heap allocations, unlike the above helper functions.
प्रकारनिर्देश गणना
{
  TDEFL_स्थितिः_BAD_PARAM = -2,
  TDEFL_स्थितिः_PUT_BUF_FAILED = -1,
  TDEFL_स्थितिः_OKAY = 0,
  TDEFL_स्थितिः_समाप्तम् = 1,
} tdefl_स्थितिः;

// Must map to MZ_NO_FLUSH, MZ_SYNC_FLUSH, etc. enums
प्रकारनिर्देश गणना
{
  TDEFL_NO_FLUSH = 0,
  TDEFL_SYNC_FLUSH = 2,
  TDEFL_पूर्णम्_FLUSH = 3,
  TDEFL_FINISH = 4
} tdefl_flush;

// tdefl's compression state structure.
प्रकारनिर्देश संरचना
{
  tdefl_put_buf_func_ptr m_pPut_buf_func;
  शून्य *m_pPut_buf_user;
  mz_uint m_flags, m_max_probes[2];
  पूर्णाङ्क m_greedy_parsing;
  mz_uint m_adler32, m_lookahead_pos, m_lookahead_आकार, m_dict_आकार;
  mz_uint8 *m_p_LZ_संहिता_buf, *m_pLZ_flags, *m_pOutput_buf, *m_p_Output_buf_अन्तः;
  mz_uint m_अङ्कः_flags_वामः, m_योग_lz_अष्टकानि, m_lz_संहिता_buf_dict_pos, m_द्वयङ्काः_अन्तर्, m_bit_बफर;
  mz_uint m_saved_मेलनम्_dist, m_saved_मेलनम्_len, m_saved_lit, m_output_flush_ofs, m_output_flush_remaining, m_परिसमाप्तम्, m_खण्डम्_सूचकांक, m_इच्छति_गन्तव्यम्_finish;
  tdefl_स्थितिः m_पूर्व_return_स्थितिः;
  ध्रुव शून्य *m_p_अन्तर्_buf;
  शून्य *m_p_बहिर्गमनम्_buf;
  size_t *m_p_अन्तर्_buf_आकार, *m_p_बहिर्गमनम्_buf_आकार;
  tdefl_flush m_flush;
  ध्रुव mz_uint8 *m_pSrc;
  size_t m_src_buf_वामः, m_बहिर्गमनम्_buf_ofs;
  mz_uint8 m_dict[TDEFL_LZ_DICT_आकार + TDEFL_MAX_मेलनम्_LEN - 1];
  mz_uint16 m_huff_गणनम्[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint16 m_huff_codes[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint8 m_huff_संहिता_sizes[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint8 m_lz_संहिता_buf[TDEFL_LZ_संहिता_BUF_आकार];
  mz_uint16 m_अग्र[TDEFL_LZ_DICT_आकार];
  mz_uint16 m_hash[TDEFL_LZ_HASH_आकार];
  mz_uint8 m_output_buf[TDEFL_बहिर्गमनम्_BUF_आकार];
} tdefl_compressor;

// Initializes the compressor.
// There is no corresponding deinit() function because the tdefl API's do not dynamically allocate memory.
// pBut_buf_func: If NULL, output data will be supplied to the specified callback. In this case, the user should call the tdefl_compress_buffer() API for compression.
// If pBut_buf_func is NULL the user should always call the tdefl_compress() API.
// flags: See the above enums (TDEFL_HUFFMAN_ONLY, TDEFL_WRITE_ZLIB_HEADER, etc.)
MINIZ_STATIC tdefl_स्थितिः tdefl_init(tdefl_compressor *d, tdefl_put_buf_func_ptr pPut_buf_func, शून्य *pPut_buf_user, पूर्णाङ्क flags);

// Compresses a block of data, consuming as much of the specified input buffer as possible, and writing as much compressed data to the specified output buffer as possible.
MINIZ_STATIC tdefl_स्थितिः tdefl_compress(tdefl_compressor *d, ध्रुव शून्य *p_अन्तर्_buf, size_t *p_अन्तर्_buf_आकार, शून्य *p_बहिर्गमनम्_buf, size_t *p_बहिर्गमनम्_buf_आकार, tdefl_flush flush);

// tdefl_compress_buffer() is only usable when the tdefl_init() is called with a non-NULL tdefl_put_buf_func_ptr.
// tdefl_compress_buffer() always consumes the entire input buffer.
MINIZ_STATIC tdefl_स्थितिः tdefl_compress_बफर(tdefl_compressor *d, ध्रुव शून्य *p_अन्तर्_buf, size_t अन्तर्_buf_आकार, tdefl_flush flush);

#यदि_अपरिभाषितम् MINIZ_SDL_NOUNUSED
MINIZ_STATIC tdefl_स्थितिः tdefl_get_पूर्व_return_स्थितिः(tdefl_compressor *d);
MINIZ_STATIC mz_uint32 tdefl_get_adler32(tdefl_compressor *d);
#यदि_अन्तः

// Can't use tdefl_create_comp_flags_from_zip_params if MINIZ_NO_ZLIB_APIS isn't defined, because it uses some of its macros.
#यदि_अपरिभाषितम् MINIZ_NO_ZLIB_APIS
// Create tdefl_compress() flags given zlib-style compression parameters.
// level may range from [0,10] (where 10 is absolute max compression, but may be much slower on some files)
// window_bits may be -15 (raw deflate) or 15 (zlib)
// strategy may be either MZ_DEFAULT_STRATEGY, MZ_FILTERED, MZ_HUFFMAN_ONLY, MZ_RLE, or MZ_FIXED
MINIZ_STATIC mz_uint tdefl_create_comp_flags_from_zip_params(पूर्णाङ्क level, पूर्णाङ्क गवाक्षः_द्वयङ्काः, पूर्णाङ्क strategy);
#यदि_अन्तः // #ifndef MINIZ_NO_ZLIB_APIS

#यदि_अन्तः /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः // MINIZ_HEADER_INCLUDED

// ------------------- End of Header: Implementation follows. (If you only want the header, define MINIZ_HEADER_FILE_ONLY.)

#यदि_अपरिभाषितम् MINIZ_शीर्षकम्_FILE_ONLY

#यदि_परिभाषितम् _MSC_VER
#निर्देशः warning (प्रक्षिप)
#निर्देशः warning (disable:4505) // unreferenced local function has been removed
#यदि_अन्तः

प्रकारनिर्देश अचिह्नित वर्ण mz_validate_uint16[परिमाण(mz_uint16)==2 ? 1 : -1];
प्रकारनिर्देश अचिह्नित वर्ण mz_validate_uint32[परिमाण(mz_uint32)==4 ? 1 : -1];
प्रकारनिर्देश अचिह्नित वर्ण mz_validate_uint64[परिमाण(mz_uint64)==8 ? 1 : -1];

/*#include <string.h>*/

#यदि_अपरिभाषितम् MZ_ASSERT
#अन्तर्भाव <assert.h>
#परिभाषय MZ_ASSERT(x) प्रतिज्ञा(x)
#यदि_अन्तः

#यदि_परिभाषितम् MINIZ_NO_MALLOC
  #परिभाषय MZ_MALLOC(x) रिक्त
  #परिभाषय MZ_FREE(x) (शून्य)x, ((शून्य)0)
  #परिभाषय MZ_REALLOC(p, x) रिक्त
#नोचेद्यदि defined(MINIZ_SDL_MALLOC)
  #परिभाषय MZ_MALLOC(x) SDL_malloc(x)
  #परिभाषय MZ_FREE(x) SDL_free(x)
  #परिभाषय MZ_REALLOC(p, x) SDL_realloc(p, x)
#अन्यथा
  #परिभाषय MZ_MALLOC(x) स्मृतिं_देहि(x)
  #परिभाषय MZ_FREE(x) मुक्त(x)
  #परिभाषय MZ_REALLOC(p, x) realloc(p, x)
#यदि_अन्तः

#परिभाषय MZ_MAX(a,b) (((a)>(b))?(a):(b))
#परिभाषय MZ_MIN(a,b) (((a)<(b))?(a):(b))
#परिभाषय MZ_CLEAR_OBJ(obj) स्मृतिं_पूरय(&(obj), 0, परिमाण(obj))
#परिभाषय MZ_CLEAR_ARR(obj) स्मृतिं_पूरय((obj), 0, परिमाण(obj))
#परिभाषय MZ_CLEAR_PTR(obj) स्मृतिं_पूरय((obj), 0, परिमाण(*obj))

#यदि MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  #परिभाषय MZ_READ_LE16(p) *((ध्रुव mz_uint16 *)(p))
  #परिभाषय MZ_READ_LE32(p) *((ध्रुव mz_uint32 *)(p))
#अन्यथा
  #परिभाषय MZ_READ_LE16(p) ((mz_uint32)(((ध्रुव mz_uint8 *)(p))[0]) | ((mz_uint32)(((ध्रुव mz_uint8 *)(p))[1]) << 8U))
  #परिभाषय MZ_READ_LE32(p) ((mz_uint32)(((ध्रुव mz_uint8 *)(p))[0]) | ((mz_uint32)(((ध्रुव mz_uint8 *)(p))[1]) << 8U) | ((mz_uint32)(((ध्रुव mz_uint8 *)(p))[2]) << 16U) | ((mz_uint32)(((ध्रुव mz_uint8 *)(p))[3]) << 24U))
#यदि_अन्तः

#यदि_परिभाषितम् _MSC_VER
  #परिभाषय MZ_FORCEINLINE __forceinline
#नोचेद्यदि defined(__GNUC__)
  #परिभाषय MZ_FORCEINLINE अन्तःस्थ __attribute__((__always_inline__))
#अन्यथा
  #परिभाषय MZ_FORCEINLINE अन्तःस्थ
#यदि_अन्तः

#यदि_परिभाषितम् __cplusplus
  बाह्य "C" {
#यदि_अन्तः

// ------------------- zlib-style API's

mz_ulong mz_adler32(mz_ulong adler, ध्रुव अचिह्नित वर्ण *ptr, size_t buf_len)
{
  mz_uint32 i, s1 = (mz_uint32)(adler & 0xffff), s2 = (mz_uint32)(adler >> 16); size_t खण्डम्_len = buf_len % 5552;
  यदि (!ptr) प्रत्यागम MZ_ADLER32_INIT;
  यावत् (buf_len) {
    प्रति (i = 0; i + 7 < खण्डम्_len; i += 8, ptr += 8) {
      s1 += ptr[0]; s2 += s1; s1 += ptr[1]; s2 += s1; s1 += ptr[2]; s2 += s1; s1 += ptr[3]; s2 += s1;
      s1 += ptr[4]; s2 += s1; s1 += ptr[5]; s2 += s1; s1 += ptr[6]; s2 += s1; s1 += ptr[7]; s2 += s1;
    }
    प्रति ( ; i < खण्डम्_len; ++i) { s1 += *ptr++; s2 += s1; }
    s1 %= 65521U; s2 %= 65521U; buf_len -= खण्डम्_len; खण्डम्_len = 5552;
  }
  प्रत्यागम (s2 << 16) + s1;
}

// Karl Malbrain's compact CRC-32. See "A compact CCITT crc16 and crc32 C implementation that balances processor cache usage against speed": http://www.geocities.com/malbrain/
mz_ulong mz_चक्रीयपरीक्षा_32(mz_ulong crc, ध्रुव mz_uint8 *ptr, size_t buf_len)
{
  स्थिर ध्रुव mz_uint32 s_चक्रीयपरीक्षा_32[16] = { 0, 0x1db71064, 0x3b6e20c8, 0x26d930ac, 0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
    0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c, 0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c };
  mz_uint32 crcu32 = (mz_uint32)crc;
  यदि (!ptr) प्रत्यागम MZ_चक्रीयपरीक्षा_32_INIT;
  crcu32 = ~crcu32; यावत् (buf_len--) { mz_uint8 b = *ptr++; crcu32 = (crcu32 >> 4) ^ s_चक्रीयपरीक्षा_32[(crcu32 & 0xF) ^ (b & 0xF)]; crcu32 = (crcu32 >> 4) ^ s_चक्रीयपरीक्षा_32[(crcu32 & 0xF) ^ (b >> 4)]; }
  प्रत्यागम ~crcu32;
}

MINIZ_STATIC शून्य mz_free(शून्य *p)
{
  MZ_FREE(p);
}

#यदि_अपरिभाषितम् MINIZ_NO_ZLIB_APIS

स्थिर शून्य *def_alloc_func(शून्य *opaque, size_t वस्तूनि, size_t आकार) { (शून्य)opaque, (शून्य)वस्तूनि, (शून्य)आकार; प्रत्यागम MZ_MALLOC(वस्तूनि * आकार); }
स्थिर शून्य def_free_func(शून्य *opaque, शून्य *स्थानाङ्कः) { (शून्य)opaque, (शून्य)स्थानाङ्कः; MZ_FREE(स्थानाङ्कः); }
स्थिर शून्य *def_realloc_func(शून्य *opaque, शून्य *स्थानाङ्कः, size_t वस्तूनि, size_t आकार) { (शून्य)opaque, (शून्य)स्थानाङ्कः, (शून्य)वस्तूनि, (शून्य)आकार; प्रत्यागम MZ_REALLOC(स्थानाङ्कः, वस्तूनि * आकार); }

ध्रुव वर्ण *mz_संस्करणम्(शून्य)
{
  प्रत्यागम MZ_संस्करणम्;
}

#यदि_अपरिभाषितम् MINIZ_NO_DEFLATE_APIS

पूर्णाङ्क mz_deflateInit(mz_streamp p_प्रवाहः, पूर्णाङ्क level)
{
  प्रत्यागम mz_deflateInit2(p_प्रवाहः, level, MZ_DEFLATED, MZ_DEFAULT_गवाक्षः_द्वयङ्काः, 9, MZ_DEFAULT_STRATEGY);
}

पूर्णाङ्क mz_deflateInit2(mz_streamp p_प्रवाहः, पूर्णाङ्क level, पूर्णाङ्क विधानम्, पूर्णाङ्क गवाक्षः_द्वयङ्काः, पूर्णाङ्क mem_level, पूर्णाङ्क strategy)
{
  tdefl_compressor *pComp;
  mz_uint comp_flags = TDEFL_COMPUTE_ADLER32 | tdefl_create_comp_flags_from_zip_params(level, गवाक्षः_द्वयङ्काः, strategy);

  यदि (!p_प्रवाहः) प्रत्यागम MZ_प्रवाहः_ERROR;
  यदि ((विधानम् != MZ_DEFLATED) || ((mem_level < 1) || (mem_level > 9)) || ((गवाक्षः_द्वयङ्काः != MZ_DEFAULT_गवाक्षः_द्वयङ्काः) && (-गवाक्षः_द्वयङ्काः != MZ_DEFAULT_गवाक्षः_द्वयङ्काः))) प्रत्यागम MZ_PARAM_ERROR;

  p_प्रवाहः->दत्त_type = 0;
  p_प्रवाहः->adler = MZ_ADLER32_INIT;
  p_प्रवाहः->सन्देशः_2 = रिक्त;
  p_प्रवाहः->reserved = 0;
  p_प्रवाहः->योग_अन्तर् = 0;
  p_प्रवाहः->योग_बहिर्गमनम् = 0;
  यदि (!p_प्रवाहः->zalloc) p_प्रवाहः->zalloc = def_alloc_func;
  यदि (!p_प्रवाहः->zfree) p_प्रवाहः->zfree = def_free_func;

  pComp = (tdefl_compressor *)p_प्रवाहः->zalloc(p_प्रवाहः->opaque, 1, परिमाण(tdefl_compressor));
  यदि (!pComp)
    प्रत्यागम MZ_MEM_ERROR;

  p_प्रवाहः->state = (संरचना mz_आन्तरिकम्_state *)pComp;

  यदि (tdefl_init(pComp, रिक्त, रिक्त, comp_flags) != TDEFL_स्थितिः_OKAY)
  {
    mz_deflate_अन्तः(p_प्रवाहः);
    प्रत्यागम MZ_PARAM_ERROR;
  }

  प्रत्यागम MZ_OK;
}

पूर्णाङ्क mz_deflateReset(mz_streamp p_प्रवाहः)
{
  यदि ((!p_प्रवाहः) || (!p_प्रवाहः->state) || (!p_प्रवाहः->zalloc) || (!p_प्रवाहः->zfree)) प्रत्यागम MZ_प्रवाहः_ERROR;
  p_प्रवाहः->योग_अन्तर् = p_प्रवाहः->योग_बहिर्गमनम् = 0;
  tdefl_init((tdefl_compressor*)p_प्रवाहः->state, रिक्त, रिक्त, ((tdefl_compressor*)p_प्रवाहः->state)->m_flags);
  प्रत्यागम MZ_OK;
}

पूर्णाङ्क mz_deflate(mz_streamp p_प्रवाहः, पूर्णाङ्क flush)
{
  size_t अन्तर्_अष्टकानि, बहिर्गमनम्_अष्टकानि;
  mz_ulong orig_योग_अन्तर्, orig_योग_बहिर्गमनम्;
  पूर्णाङ्क mz_स्थितिः = MZ_OK;

  यदि ((!p_प्रवाहः) || (!p_प्रवाहः->state) || (flush < 0) || (flush > MZ_FINISH) || (!p_प्रवाहः->अग्र_बहिर्गमनम्)) प्रत्यागम MZ_प्रवाहः_ERROR;
  यदि (!p_प्रवाहः->avail_बहिर्गमनम्) प्रत्यागम MZ_BUF_ERROR;

  यदि (flush == MZ_PARTIAL_FLUSH) flush = MZ_SYNC_FLUSH;

  यदि (((tdefl_compressor*)p_प्रवाहः->state)->m_पूर्व_return_स्थितिः == TDEFL_स्थितिः_समाप्तम्)
    प्रत्यागम (flush == MZ_FINISH) ? MZ_प्रवाहः_अन्तः : MZ_BUF_ERROR;

  orig_योग_अन्तर् = p_प्रवाहः->योग_अन्तर्; orig_योग_बहिर्गमनम् = p_प्रवाहः->योग_बहिर्गमनम्;
  प्रति ( ; ; )
  {
    tdefl_स्थितिः defl_स्थितिः;
    अन्तर्_अष्टकानि = p_प्रवाहः->avail_अन्तर्; बहिर्गमनम्_अष्टकानि = p_प्रवाहः->avail_बहिर्गमनम्;

    defl_स्थितिः = tdefl_compress((tdefl_compressor*)p_प्रवाहः->state, p_प्रवाहः->अग्र_अन्तर्, &अन्तर्_अष्टकानि, p_प्रवाहः->अग्र_बहिर्गमनम्, &बहिर्गमनम्_अष्टकानि, (tdefl_flush)flush);
    p_प्रवाहः->अग्र_अन्तर् += (mz_uint)अन्तर्_अष्टकानि; p_प्रवाहः->avail_अन्तर् -= (mz_uint)अन्तर्_अष्टकानि;
    p_प्रवाहः->योग_अन्तर् += (mz_uint)अन्तर्_अष्टकानि; p_प्रवाहः->adler = tdefl_get_adler32((tdefl_compressor*)p_प्रवाहः->state);

    p_प्रवाहः->अग्र_बहिर्गमनम् += (mz_uint)बहिर्गमनम्_अष्टकानि; p_प्रवाहः->avail_बहिर्गमनम् -= (mz_uint)बहिर्गमनम्_अष्टकानि;
    p_प्रवाहः->योग_बहिर्गमनम् += (mz_uint)बहिर्गमनम्_अष्टकानि;

    यदि (defl_स्थितिः < 0)
    {
      mz_स्थितिः = MZ_प्रवाहः_ERROR;
      भङ्ग;
    }
    अन्यथा यदि (defl_स्थितिः == TDEFL_स्थितिः_समाप्तम्)
    {
      mz_स्थितिः = MZ_प्रवाहः_अन्तः;
      भङ्ग;
    }
    अन्यथा यदि (!p_प्रवाहः->avail_बहिर्गमनम्)
      भङ्ग;
    अन्यथा यदि ((!p_प्रवाहः->avail_अन्तर्) && (flush != MZ_FINISH))
    {
      यदि ((flush) || (p_प्रवाहः->योग_अन्तर् != orig_योग_अन्तर्) || (p_प्रवाहः->योग_बहिर्गमनम् != orig_योग_बहिर्गमनम्))
        भङ्ग;
      प्रत्यागम MZ_BUF_ERROR; // Can't make forward progress without some input.
    }
  }
  प्रत्यागम mz_स्थितिः;
}

पूर्णाङ्क mz_deflate_अन्तः(mz_streamp p_प्रवाहः)
{
  यदि (!p_प्रवाहः) प्रत्यागम MZ_प्रवाहः_ERROR;
  यदि (p_प्रवाहः->state)
  {
    p_प्रवाहः->zfree(p_प्रवाहः->opaque, p_प्रवाहः->state);
    p_प्रवाहः->state = रिक्त;
  }
  प्रत्यागम MZ_OK;
}

mz_ulong mz_deflateBound(mz_streamp p_प्रवाहः, mz_ulong source_len)
{
  (शून्य)p_प्रवाहः;
  // This is really over conservative. (And lame, but it's actually pretty tricky to compute a true upper bound given the way tdefl's blocking works.)
  प्रत्यागम MZ_MAX(128 + (source_len * 110) / 100, 128 + source_len + ((source_len / (31 * 1024)) + 1) * 5);
}

पूर्णाङ्क mz_compress2(अचिह्नित वर्ण *pDest, mz_ulong *pDest_len, ध्रुव अचिह्नित वर्ण *pSource, mz_ulong source_len, पूर्णाङ्क level)
{
  पूर्णाङ्क स्थितिः;
  mz_प्रवाहः प्रवाहः;
  स्मृतिं_पूरय(&प्रवाहः, 0, परिमाण(प्रवाहः));

  // In case mz_ulong is 64-bits (argh I hate longs).
  यदि ((source_len | *pDest_len) > 0xFFFFFFFFU) प्रत्यागम MZ_PARAM_ERROR;

  प्रवाहः.अग्र_अन्तर् = pSource;
  प्रवाहः.avail_अन्तर् = (mz_uint32)source_len;
  प्रवाहः.अग्र_बहिर्गमनम् = pDest;
  प्रवाहः.avail_बहिर्गमनम् = (mz_uint32)*pDest_len;

  स्थितिः = mz_deflateInit(&प्रवाहः, level);
  यदि (स्थितिः != MZ_OK) प्रत्यागम स्थितिः;

  स्थितिः = mz_deflate(&प्रवाहः, MZ_FINISH);
  यदि (स्थितिः != MZ_प्रवाहः_अन्तः)
  {
    mz_deflate_अन्तः(&प्रवाहः);
    प्रत्यागम (स्थितिः == MZ_OK) ? MZ_BUF_ERROR : स्थितिः;
  }

  *pDest_len = प्रवाहः.योग_बहिर्गमनम्;
  प्रत्यागम mz_deflate_अन्तः(&प्रवाहः);
}

पूर्णाङ्क mz_compress(अचिह्नित वर्ण *pDest, mz_ulong *pDest_len, ध्रुव अचिह्नित वर्ण *pSource, mz_ulong source_len)
{
  प्रत्यागम mz_compress2(pDest, pDest_len, pSource, source_len, MZ_DEFAULT_COMPRESSION);
}

mz_ulong mz_compressBound(mz_ulong source_len)
{
  प्रत्यागम mz_deflateBound(रिक्त, source_len);
}

#यदि_अन्तः /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#यदि_अपरिभाषितम् MINIZ_NO_INFLATE_APIS

प्रकारनिर्देश संरचना
{
  tinfl_decompressor m_decomp;
  mz_uint m_dict_ofs, m_dict_avail, m_first_call, m_has_flushed; पूर्णाङ्क m_गवाक्षः_द्वयङ्काः;
  mz_uint8 m_dict[TINFL_LZ_DICT_आकार];
  tinfl_स्थितिः m_चरमः_स्थितिः;
} inflate_state;

पूर्णाङ्क mz_inflateInit2(mz_streamp p_प्रवाहः, पूर्णाङ्क गवाक्षः_द्वयङ्काः)
{
  inflate_state *pDecomp;
  यदि (!p_प्रवाहः) प्रत्यागम MZ_प्रवाहः_ERROR;
  यदि ((गवाक्षः_द्वयङ्काः != MZ_DEFAULT_गवाक्षः_द्वयङ्काः) && (-गवाक्षः_द्वयङ्काः != MZ_DEFAULT_गवाक्षः_द्वयङ्काः)) प्रत्यागम MZ_PARAM_ERROR;

  p_प्रवाहः->दत्त_type = 0;
  p_प्रवाहः->adler = 0;
  p_प्रवाहः->सन्देशः_2 = रिक्त;
  p_प्रवाहः->योग_अन्तर् = 0;
  p_प्रवाहः->योग_बहिर्गमनम् = 0;
  p_प्रवाहः->reserved = 0;
  यदि (!p_प्रवाहः->zalloc) p_प्रवाहः->zalloc = def_alloc_func;
  यदि (!p_प्रवाहः->zfree) p_प्रवाहः->zfree = def_free_func;

  pDecomp = (inflate_state*)p_प्रवाहः->zalloc(p_प्रवाहः->opaque, 1, परिमाण(inflate_state));
  यदि (!pDecomp) प्रत्यागम MZ_MEM_ERROR;

  p_प्रवाहः->state = (संरचना mz_आन्तरिकम्_state *)pDecomp;

  tinfl_init(&pDecomp->m_decomp);
  pDecomp->m_dict_ofs = 0;
  pDecomp->m_dict_avail = 0;
  pDecomp->m_चरमः_स्थितिः = TINFL_स्थितिः_NEEDS_अधिकम्_निवेशः;
  pDecomp->m_first_call = 1;
  pDecomp->m_has_flushed = 0;
  pDecomp->m_गवाक्षः_द्वयङ्काः = गवाक्षः_द्वयङ्काः;

  प्रत्यागम MZ_OK;
}

पूर्णाङ्क mz_inflateInit(mz_streamp p_प्रवाहः)
{
   प्रत्यागम mz_inflateInit2(p_प्रवाहः, MZ_DEFAULT_गवाक्षः_द्वयङ्काः);
}

पूर्णाङ्क mz_inflate(mz_streamp p_प्रवाहः, पूर्णाङ्क flush)
{
  inflate_state* pState;
  mz_uint n, first_call, decomp_flags = TINFL_FLAG_COMPUTE_ADLER32;
  size_t अन्तर्_अष्टकानि, बहिर्गमनम्_अष्टकानि, orig_avail_अन्तर्;
  tinfl_स्थितिः स्थितिः;

  यदि ((!p_प्रवाहः) || (!p_प्रवाहः->state)) प्रत्यागम MZ_प्रवाहः_ERROR;
  यदि (flush == MZ_PARTIAL_FLUSH) flush = MZ_SYNC_FLUSH;
  यदि ((flush) && (flush != MZ_SYNC_FLUSH) && (flush != MZ_FINISH)) प्रत्यागम MZ_प्रवाहः_ERROR;

  pState = (inflate_state*)p_प्रवाहः->state;
  यदि (pState->m_गवाक्षः_द्वयङ्काः > 0) decomp_flags |= TINFL_FLAG_PARSE_ZLIB_शीर्षकम्;
  orig_avail_अन्तर् = p_प्रवाहः->avail_अन्तर्;

  first_call = pState->m_first_call; pState->m_first_call = 0;
  यदि (pState->m_चरमः_स्थितिः < 0) प्रत्यागम MZ_दत्त_ERROR;

  यदि (pState->m_has_flushed && (flush != MZ_FINISH)) प्रत्यागम MZ_प्रवाहः_ERROR;
  pState->m_has_flushed |= (flush == MZ_FINISH);

  यदि ((flush == MZ_FINISH) && (first_call))
  {
    // MZ_FINISH on the first call implies that the input and output buffers are large enough to hold the entire compressed/decompressed file.
    decomp_flags |= TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF;
    अन्तर्_अष्टकानि = p_प्रवाहः->avail_अन्तर्; बहिर्गमनम्_अष्टकानि = p_प्रवाहः->avail_बहिर्गमनम्;
    स्थितिः = tinfl_decompress(&pState->m_decomp, p_प्रवाहः->अग्र_अन्तर्, &अन्तर्_अष्टकानि, p_प्रवाहः->अग्र_बहिर्गमनम्, p_प्रवाहः->अग्र_बहिर्गमनम्, &बहिर्गमनम्_अष्टकानि, decomp_flags);
    pState->m_चरमः_स्थितिः = स्थितिः;
    p_प्रवाहः->अग्र_अन्तर् += (mz_uint)अन्तर्_अष्टकानि; p_प्रवाहः->avail_अन्तर् -= (mz_uint)अन्तर्_अष्टकानि; p_प्रवाहः->योग_अन्तर् += (mz_uint)अन्तर्_अष्टकानि;
    p_प्रवाहः->adler = tinfl_get_adler32(&pState->m_decomp);
    p_प्रवाहः->अग्र_बहिर्गमनम् += (mz_uint)बहिर्गमनम्_अष्टकानि; p_प्रवाहः->avail_बहिर्गमनम् -= (mz_uint)बहिर्गमनम्_अष्टकानि; p_प्रवाहः->योग_बहिर्गमनम् += (mz_uint)बहिर्गमनम्_अष्टकानि;

    यदि (स्थितिः < 0)
      प्रत्यागम MZ_दत्त_ERROR;
    अन्यथा यदि (स्थितिः != TINFL_स्थितिः_समाप्तम्)
    {
      pState->m_चरमः_स्थितिः = TINFL_स्थितिः_FAILED;
      प्रत्यागम MZ_BUF_ERROR;
    }
    प्रत्यागम MZ_प्रवाहः_अन्तः;
  }
  // flush != MZ_FINISH then we must assume there's more input.
  यदि (flush != MZ_FINISH) decomp_flags |= TINFL_FLAG_HAS_अधिकम्_निवेशः;

  यदि (pState->m_dict_avail)
  {
    n = MZ_MIN(pState->m_dict_avail, p_प्रवाहः->avail_बहिर्गमनम्);
    स्मृतिं_प्रतिलिख(p_प्रवाहः->अग्र_बहिर्गमनम्, pState->m_dict + pState->m_dict_ofs, n);
    p_प्रवाहः->अग्र_बहिर्गमनम् += n; p_प्रवाहः->avail_बहिर्गमनम् -= n; p_प्रवाहः->योग_बहिर्गमनम् += n;
    pState->m_dict_avail -= n; pState->m_dict_ofs = (pState->m_dict_ofs + n) & (TINFL_LZ_DICT_आकार - 1);
    प्रत्यागम ((pState->m_चरमः_स्थितिः == TINFL_स्थितिः_समाप्तम्) && (!pState->m_dict_avail)) ? MZ_प्रवाहः_अन्तः : MZ_OK;
  }

  प्रति ( ; ; )
  {
    अन्तर्_अष्टकानि = p_प्रवाहः->avail_अन्तर्;
    बहिर्गमनम्_अष्टकानि = TINFL_LZ_DICT_आकार - pState->m_dict_ofs;

    स्थितिः = tinfl_decompress(&pState->m_decomp, p_प्रवाहः->अग्र_अन्तर्, &अन्तर्_अष्टकानि, pState->m_dict, pState->m_dict + pState->m_dict_ofs, &बहिर्गमनम्_अष्टकानि, decomp_flags);
    pState->m_चरमः_स्थितिः = स्थितिः;

    p_प्रवाहः->अग्र_अन्तर् += (mz_uint)अन्तर्_अष्टकानि; p_प्रवाहः->avail_अन्तर् -= (mz_uint)अन्तर्_अष्टकानि;
    p_प्रवाहः->योग_अन्तर् += (mz_uint)अन्तर्_अष्टकानि; p_प्रवाहः->adler = tinfl_get_adler32(&pState->m_decomp);

    pState->m_dict_avail = (mz_uint)बहिर्गमनम्_अष्टकानि;

    n = MZ_MIN(pState->m_dict_avail, p_प्रवाहः->avail_बहिर्गमनम्);
    स्मृतिं_प्रतिलिख(p_प्रवाहः->अग्र_बहिर्गमनम्, pState->m_dict + pState->m_dict_ofs, n);
    p_प्रवाहः->अग्र_बहिर्गमनम् += n; p_प्रवाहः->avail_बहिर्गमनम् -= n; p_प्रवाहः->योग_बहिर्गमनम् += n;
    pState->m_dict_avail -= n; pState->m_dict_ofs = (pState->m_dict_ofs + n) & (TINFL_LZ_DICT_आकार - 1);

    यदि (स्थितिः < 0)
       प्रत्यागम MZ_दत्त_ERROR; // Stream is corrupted (there could be some uncompressed data left in the output dictionary - oh well).
    अन्यथा यदि ((स्थितिः == TINFL_स्थितिः_NEEDS_अधिकम्_निवेशः) && (!orig_avail_अन्तर्))
      प्रत्यागम MZ_BUF_ERROR; // Signal caller that we can't make forward progress without supplying more input or by setting flush to MZ_FINISH.
    अन्यथा यदि (flush == MZ_FINISH)
    {
       // The output buffer MUST be large to hold the remaining uncompressed data when flush==MZ_FINISH.
       यदि (स्थितिः == TINFL_स्थितिः_समाप्तम्)
          प्रत्यागम pState->m_dict_avail ? MZ_BUF_ERROR : MZ_प्रवाहः_अन्तः;
       // status here must be TINFL_STATUS_HAS_MORE_OUTPUT, which means there's at least 1 more byte on the way. If there's no more room left in the output buffer then something is wrong.
       अन्यथा यदि (!p_प्रवाहः->avail_बहिर्गमनम्)
          प्रत्यागम MZ_BUF_ERROR;
    }
    अन्यथा यदि ((स्थितिः == TINFL_स्थितिः_समाप्तम्) || (!p_प्रवाहः->avail_अन्तर्) || (!p_प्रवाहः->avail_बहिर्गमनम्) || (pState->m_dict_avail))
      भङ्ग;
  }

  प्रत्यागम ((स्थितिः == TINFL_स्थितिः_समाप्तम्) && (!pState->m_dict_avail)) ? MZ_प्रवाहः_अन्तः : MZ_OK;
}

पूर्णाङ्क mz_inflate_अन्तः(mz_streamp p_प्रवाहः)
{
  यदि (!p_प्रवाहः)
    प्रत्यागम MZ_प्रवाहः_ERROR;
  यदि (p_प्रवाहः->state)
  {
    p_प्रवाहः->zfree(p_प्रवाहः->opaque, p_प्रवाहः->state);
    p_प्रवाहः->state = रिक्त;
  }
  प्रत्यागम MZ_OK;
}

पूर्णाङ्क mz_uncompress(अचिह्नित वर्ण *pDest, mz_ulong *pDest_len, ध्रुव अचिह्नित वर्ण *pSource, mz_ulong source_len)
{
  mz_प्रवाहः प्रवाहः;
  पूर्णाङ्क स्थितिः;
  स्मृतिं_पूरय(&प्रवाहः, 0, परिमाण(प्रवाहः));

  // In case mz_ulong is 64-bits (argh I hate longs).
  यदि ((source_len | *pDest_len) > 0xFFFFFFFFU) प्रत्यागम MZ_PARAM_ERROR;

  प्रवाहः.अग्र_अन्तर् = pSource;
  प्रवाहः.avail_अन्तर् = (mz_uint32)source_len;
  प्रवाहः.अग्र_बहिर्गमनम् = pDest;
  प्रवाहः.avail_बहिर्गमनम् = (mz_uint32)*pDest_len;

  स्थितिः = mz_inflateInit(&प्रवाहः);
  यदि (स्थितिः != MZ_OK)
    प्रत्यागम स्थितिः;

  स्थितिः = mz_inflate(&प्रवाहः, MZ_FINISH);
  यदि (स्थितिः != MZ_प्रवाहः_अन्तः)
  {
    mz_inflate_अन्तः(&प्रवाहः);
    प्रत्यागम ((स्थितिः == MZ_BUF_ERROR) && (!प्रवाहः.avail_अन्तर्)) ? MZ_दत्त_ERROR : स्थितिः;
  }
  *pDest_len = प्रवाहः.योग_बहिर्गमनम्;

  प्रत्यागम mz_inflate_अन्तः(&प्रवाहः);
}

#यदि_अन्तः /*#ifndef MINIZ_NO_INFLATE_APIS*/

ध्रुव वर्ण *mz_error(पूर्णाङ्क err)
{
  स्थिर संरचना { पूर्णाङ्क m_err; ध्रुव वर्ण *m_pDesc; } s_error_descs[] =
  {
    { MZ_OK, "" }, { MZ_प्रवाहः_अन्तः, "stream end" }, { MZ_NEED_DICT, "need dictionary" }, { MZ_ERRNO, "file error" }, { MZ_प्रवाहः_ERROR, "stream error" },
    { MZ_दत्त_ERROR, "data error" }, { MZ_MEM_ERROR, "out of memory" }, { MZ_BUF_ERROR, "buf error" }, { MZ_संस्करणम्_ERROR, "version error" }, { MZ_PARAM_ERROR, "parameter error" }
  };
  mz_uint i; प्रति (i = 0; i < परिमाण(s_error_descs) / परिमाण(s_error_descs[0]); ++i) यदि (s_error_descs[i].m_err == err) प्रत्यागम s_error_descs[i].m_pDesc;
  प्रत्यागम रिक्त;
}

#यदि_अन्तः //MINIZ_NO_ZLIB_APIS

// ------------------- Low-level Decompression (completely independent from all compression API's)
#यदि_अपरिभाषितम् MINIZ_NO_INFLATE_APIS

#परिभाषय TINFL_MEMCPY(d, s, l) स्मृतिं_प्रतिलिख(d, s, l)
#परिभाषय TINFL_MEMSET(p, c, l) स्मृतिं_पूरय(p, c, l)

#परिभाषय TINFL_CR_BEGIN विकल्प(r->m_state) { पक्ष 0:
#परिभाषय TINFL_CR_RETURN(state_सूचकांक, परिणाम) कुरु { स्थितिः = परिणाम; r->m_state = state_सूचकांक; गच्छ common_exit; पक्ष state_सूचकांक:; } MZ_MACRO_अन्तः
#परिभाषय TINFL_CR_RETURN_FOREVER(state_सूचकांक, परिणाम) कुरु { प्रति ( ; ; ) { TINFL_CR_RETURN(state_सूचकांक, परिणाम); } } MZ_MACRO_अन्तः
#परिभाषय TINFL_CR_FINISH }

// TODO: If the caller has indicated that there's no more input, and we attempt to read beyond the input buf, then something is wrong with the input because the inflator never
// reads ahead more than it needs to. Currently TINFL_GET_BYTE() pads the end of the stream with 0's in this scenario.
#परिभाषय TINFL_GET_BYTE(state_सूचकांक, c) कुरु { \
  यदि (p_अन्तर्_buf_cur >= p_अन्तर्_buf_अन्तः) { \
    प्रति ( ; ; ) { \
      यदि (decomp_flags & TINFL_FLAG_HAS_अधिकम्_निवेशः) { \
        TINFL_CR_RETURN(state_सूचकांक, TINFL_स्थितिः_NEEDS_अधिकम्_निवेशः); \
        यदि (p_अन्तर्_buf_cur < p_अन्तर्_buf_अन्तः) { \
          c = *p_अन्तर्_buf_cur++; \
          भङ्ग; \
        } \
      } अन्यथा { \
        c = 0; \
        भङ्ग; \
      } \
    } \
  } अन्यथा c = *p_अन्तर्_buf_cur++; } MZ_MACRO_अन्तः

#परिभाषय TINFL_NEED_द्वयङ्काः(state_सूचकांक, n) कुरु { mz_uint c; TINFL_GET_BYTE(state_सूचकांक, c); bit_buf |= (((tinfl_bit_buf_t)c) << अङ्कः_द्वयङ्काः); अङ्कः_द्वयङ्काः += 8; } यावत् (अङ्कः_द्वयङ्काः < (mz_uint)(n))
#परिभाषय TINFL_SKIP_द्वयङ्काः(state_सूचकांक, n) कुरु { यदि (अङ्कः_द्वयङ्काः < (mz_uint)(n)) { TINFL_NEED_द्वयङ्काः(state_सूचकांक, n); } bit_buf >>= (n); अङ्कः_द्वयङ्काः -= (n); } MZ_MACRO_अन्तः
#परिभाषय TINFL_GET_द्वयङ्काः(state_सूचकांक, b, n) कुरु { यदि (अङ्कः_द्वयङ्काः < (mz_uint)(n)) { TINFL_NEED_द्वयङ्काः(state_सूचकांक, n); } b = bit_buf & ((1 << (n)) - 1); bit_buf >>= (n); अङ्कः_द्वयङ्काः -= (n); } MZ_MACRO_अन्तः

// TINFL_HUFF_BITBUF_FILL() is only used rarely, when the number of bytes remaining in the input buffer falls below 2.
// It reads just enough bytes from the input stream that are needed to decode the next Huffman code (and absolutely no more). It works by trying to fully decode a
// Huffman code by using whatever bits are currently present in the bit buffer. If this fails, it reads another byte, and tries again until it succeeds or until the
// bit buffer contains >=15 bits (deflate's max. Huffman code size).
#परिभाषय TINFL_HUFF_BITBUF_FILL(state_सूचकांक, pHuff) \
  कुरु { \
    अस्थायी = (pHuff)->m_look_ऊर्ध्वम्[bit_buf & (TINFL_FAST_LOOKUP_आकार - 1)]; \
    यदि (अस्थायी >= 0) { \
      संहिता_len = अस्थायी >> 9; \
      यदि ((संहिता_len) && (अङ्कः_द्वयङ्काः >= संहिता_len)) \
          भङ्ग; \
    } अन्यथा यदि (अङ्कः_द्वयङ्काः > TINFL_FAST_LOOKUP_द्वयङ्काः) { \
       संहिता_len = TINFL_FAST_LOOKUP_द्वयङ्काः; \
       कुरु { \
          अस्थायी = (pHuff)->m_वृक्षः[~अस्थायी + ((bit_buf >> संहिता_len++) & 1)]; \
       } यावत् ((अस्थायी < 0) && (अङ्कः_द्वयङ्काः >= (संहिता_len + 1))); \
       यदि (अस्थायी >= 0) भङ्ग; \
    } \
    TINFL_GET_BYTE(state_सूचकांक, c); \
    bit_buf |= (((tinfl_bit_buf_t)c) << अङ्कः_द्वयङ्काः); \
    अङ्कः_द्वयङ्काः += 8; \
  } यावत् (अङ्कः_द्वयङ्काः < 15);

// TINFL_HUFF_DECODE() decodes the next Huffman coded symbol. It's more complex than you would initially expect because the zlib API expects the decompressor to never read
// beyond the final byte of the deflate stream. (In other words, when this macro wants to read another byte from the input, it REALLY needs another byte in order to fully
// decode the next Huffman code.) Handling this properly is particularly important on raw deflate (non-zlib) streams, which aren't followed by a byte aligned adler-32.
// The slow path is only executed at the very end of the input buffer.
#परिभाषय TINFL_HUFF_DECODE(state_सूचकांक, sym, pHuff) कुरु { \
  पूर्णाङ्क अस्थायी; mz_uint संहिता_len, c; \
  यदि (अङ्कः_द्वयङ्काः < 15) { \
    यदि ((p_अन्तर्_buf_अन्तः - p_अन्तर्_buf_cur) < 2) { \
       TINFL_HUFF_BITBUF_FILL(state_सूचकांक, pHuff); \
    } अन्यथा { \
       bit_buf |= (((tinfl_bit_buf_t)p_अन्तर्_buf_cur[0]) << अङ्कः_द्वयङ्काः) | (((tinfl_bit_buf_t)p_अन्तर्_buf_cur[1]) << (अङ्कः_द्वयङ्काः + 8)); p_अन्तर्_buf_cur += 2; अङ्कः_द्वयङ्काः += 16; \
    } \
  } \
  यदि ((अस्थायी = (pHuff)->m_look_ऊर्ध्वम्[bit_buf & (TINFL_FAST_LOOKUP_आकार - 1)]) >= 0) \
    संहिता_len = अस्थायी >> 9, अस्थायी &= 511; \
  अन्यथा { \
    संहिता_len = TINFL_FAST_LOOKUP_द्वयङ्काः; कुरु { अस्थायी = (pHuff)->m_वृक्षः[~अस्थायी + ((bit_buf >> संहिता_len++) & 1)]; } यावत् (अस्थायी < 0); \
  } sym = अस्थायी; bit_buf >>= संहिता_len; अङ्कः_द्वयङ्काः -= संहिता_len; } MZ_MACRO_अन्तः

tinfl_स्थितिः tinfl_decompress(tinfl_decompressor *r, ध्रुव mz_uint8 *p_अन्तर्_buf_अग्र, size_t *p_अन्तर्_buf_आकार, mz_uint8 *p_बहिर्गमनम्_buf_start, mz_uint8 *p_बहिर्गमनम्_buf_अग्र, size_t *p_बहिर्गमनम्_buf_आकार, ध्रुव mz_uint32 decomp_flags)
{
  स्थिर ध्रुव पूर्णाङ्क s_दीर्घता_आधारः[31] = { 3,4,5,6,7,8,9,10,11,13, 15,17,19,23,27,31,35,43,51,59, 67,83,99,115,131,163,195,227,258,0,0 };
  स्थिर ध्रुव पूर्णाङ्क s_दीर्घता_extra[31]= { 0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,0,0,0 };
  स्थिर ध्रुव पूर्णाङ्क s_dist_आधारः[32] = { 1,2,3,4,5,7,9,13,17,25,33,49,65,97,129,193, 257,385,513,769,1025,1537,2049,3073,4097,6145,8193,12289,16385,24577,0,0};
  स्थिर ध्रुव पूर्णाङ्क s_dist_extra[32] = { 0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13};
  स्थिर ध्रुव mz_uint8 s_दीर्घता_dezigzag[19] = { 16,17,18,0,8,7,9,6,10,5,11,4,12,3,13,2,14,1,15 };
  स्थिर ध्रुव पूर्णाङ्क s_min_सारणी_sizes[3] = { 257, 1, 4 };

  tinfl_स्थितिः स्थितिः = TINFL_स्थितिः_FAILED; mz_uint32 अङ्कः_द्वयङ्काः, dist, गणक, अङ्कः_extra; tinfl_bit_buf_t bit_buf;
  ध्रुव mz_uint8 *p_अन्तर्_buf_cur = p_अन्तर्_buf_अग्र, *ध्रुव p_अन्तर्_buf_अन्तः = p_अन्तर्_buf_अग्र + *p_अन्तर्_buf_आकार;
  mz_uint8 *p_बहिर्गमनम्_buf_cur = p_बहिर्गमनम्_buf_अग्र, *ध्रुव p_बहिर्गमनम्_buf_अन्तः = p_बहिर्गमनम्_buf_अग्र + *p_बहिर्गमनम्_buf_आकार;
  size_t बहिर्गमनम्_buf_आकार_आवरणम् = (decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF) ? (size_t)-1 : ((p_बहिर्गमनम्_buf_अग्र - p_बहिर्गमनम्_buf_start) + *p_बहिर्गमनम्_buf_आकार) - 1, dist_from_बहिर्गमनम्_buf_start;

  // Ensure the output buffer's size is a power of 2, unless the output buffer is large enough to hold the entire output file (in which case it doesn't matter).
  यदि (((बहिर्गमनम्_buf_आकार_आवरणम् + 1) & बहिर्गमनम्_buf_आकार_आवरणम्) || (p_बहिर्गमनम्_buf_अग्र < p_बहिर्गमनम्_buf_start)) { *p_अन्तर्_buf_आकार = *p_बहिर्गमनम्_buf_आकार = 0; प्रत्यागम TINFL_स्थितिः_BAD_PARAM; }

  अङ्कः_द्वयङ्काः = r->m_अङ्कः_द्वयङ्काः; bit_buf = r->m_bit_buf; dist = r->m_dist; गणक = r->m_गणक; अङ्कः_extra = r->m_अङ्कः_extra; dist_from_बहिर्गमनम्_buf_start = r->m_dist_from_बहिर्गमनम्_buf_start;
  TINFL_CR_BEGIN

  bit_buf = अङ्कः_द्वयङ्काः = dist = गणक = अङ्कः_extra = r->m_zhdr0 = r->m_zhdr1 = 0; r->m_z_adler32 = r->m_check_adler32 = 1;
  यदि (decomp_flags & TINFL_FLAG_PARSE_ZLIB_शीर्षकम्)
  {
    TINFL_GET_BYTE(1, r->m_zhdr0); TINFL_GET_BYTE(2, r->m_zhdr1);
    गणक = (((r->m_zhdr0 * 256 + r->m_zhdr1) % 31 != 0) || (r->m_zhdr1 & 32) || ((r->m_zhdr0 & 15) != 8));
    यदि (!(decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF)) गणक |= (((1U << (8U + (r->m_zhdr0 >> 4))) > 32768U) || ((बहिर्गमनम्_buf_आकार_आवरणम् + 1) < (size_t)(1U << (8U + (r->m_zhdr0 >> 4)))));
    यदि (गणक) { TINFL_CR_RETURN_FOREVER(36, TINFL_स्थितिः_FAILED); }
  }

  कुरु
  {
    TINFL_GET_द्वयङ्काः(3, r->m_final, 3); r->m_type = r->m_final >> 1;
    यदि (r->m_type == 0)
    {
      TINFL_SKIP_द्वयङ्काः(5, अङ्कः_द्वयङ्काः & 7);
      प्रति (गणक = 0; गणक < 4; ++गणक) { यदि (अङ्कः_द्वयङ्काः) TINFL_GET_द्वयङ्काः(6, r->m_raw_शीर्षकम्[गणक], 8); अन्यथा TINFL_GET_BYTE(7, r->m_raw_शीर्षकम्[गणक]); }
      यदि ((गणक = (r->m_raw_शीर्षकम्[0] | (r->m_raw_शीर्षकम्[1] << 8))) != (mz_uint)(0xFFFF ^ (r->m_raw_शीर्षकम्[2] | (r->m_raw_शीर्षकम्[3] << 8)))) { TINFL_CR_RETURN_FOREVER(39, TINFL_स्थितिः_FAILED); }
      यावत् ((गणक) && (अङ्कः_द्वयङ्काः))
      {
        TINFL_GET_द्वयङ्काः(51, dist, 8);
        यावत् (p_बहिर्गमनम्_buf_cur >= p_बहिर्गमनम्_buf_अन्तः) { TINFL_CR_RETURN(52, TINFL_स्थितिः_HAS_अधिकम्_OUTPUT); }
        *p_बहिर्गमनम्_buf_cur++ = (mz_uint8)dist;
        गणक--;
      }
      यावत् (गणक)
      {
        size_t n; यावत् (p_बहिर्गमनम्_buf_cur >= p_बहिर्गमनम्_buf_अन्तः) { TINFL_CR_RETURN(9, TINFL_स्थितिः_HAS_अधिकम्_OUTPUT); }
        यावत् (p_अन्तर्_buf_cur >= p_अन्तर्_buf_अन्तः)
        {
          यदि (decomp_flags & TINFL_FLAG_HAS_अधिकम्_निवेशः)
          {
            TINFL_CR_RETURN(38, TINFL_स्थितिः_NEEDS_अधिकम्_निवेशः);
          }
          अन्यथा
          {
            TINFL_CR_RETURN_FOREVER(40, TINFL_स्थितिः_FAILED);
          }
        }
        n = MZ_MIN(MZ_MIN((size_t)(p_बहिर्गमनम्_buf_अन्तः - p_बहिर्गमनम्_buf_cur), (size_t)(p_अन्तर्_buf_अन्तः - p_अन्तर्_buf_cur)), गणक);
        TINFL_MEMCPY(p_बहिर्गमनम्_buf_cur, p_अन्तर्_buf_cur, n); p_अन्तर्_buf_cur += n; p_बहिर्गमनम्_buf_cur += n; गणक -= (mz_uint)n;
      }
    }
    अन्यथा यदि (r->m_type == 3)
    {
      TINFL_CR_RETURN_FOREVER(10, TINFL_स्थितिः_FAILED);
    }
    अन्यथा
    {
      यदि (r->m_type == 1)
      {
        mz_uint8 *p = r->m_tables[0].m_संहिता_आकार; mz_uint i;
        r->m_सारणी_sizes[0] = 288; r->m_सारणी_sizes[1] = 32; TINFL_MEMSET(r->m_tables[1].m_संहिता_आकार, 5, 32);
        प्रति ( i = 0; i <= 143; ++i) *p++ = 8;
        प्रति ( ; i <= 255; ++i) *p++ = 9;
        प्रति ( ; i <= 279; ++i) *p++ = 7;
        प्रति ( ; i <= 287; ++i) *p++ = 8;
      }
      अन्यथा
      {
        प्रति (गणक = 0; गणक < 3; गणक++) { TINFL_GET_द्वयङ्काः(11, r->m_सारणी_sizes[गणक], "\05\05\04"[गणक]); r->m_सारणी_sizes[गणक] += s_min_सारणी_sizes[गणक]; }
        MZ_CLEAR_ARR(r->m_tables[2].m_संहिता_आकार); प्रति (गणक = 0; गणक < r->m_सारणी_sizes[2]; गणक++) { mz_uint s; TINFL_GET_द्वयङ्काः(14, s, 3); r->m_tables[2].m_संहिता_आकार[s_दीर्घता_dezigzag[गणक]] = (mz_uint8)s; }
        r->m_सारणी_sizes[2] = 19;
      }
      प्रति ( ; (पूर्णाङ्क)r->m_type >= 0; r->m_type--)
      {
        पूर्णाङ्क वृक्षः_अग्र, वृक्षः_cur; tinfl_huff_सारणी *p_सारणी;
        mz_uint i, j, प्रयुक्तम्_syms, योग, sym_सूचकांक, अग्र_संहिता[17], योग_syms[16]; p_सारणी = &r->m_tables[r->m_type]; MZ_CLEAR_ARR(योग_syms); MZ_CLEAR_ARR(p_सारणी->m_look_ऊर्ध्वम्); MZ_CLEAR_ARR(p_सारणी->m_वृक्षः);
        प्रति (i = 0; i < r->m_सारणी_sizes[r->m_type]; ++i) योग_syms[p_सारणी->m_संहिता_आकार[i]]++;
        प्रयुक्तम्_syms = 0, योग = 0; अग्र_संहिता[0] = अग्र_संहिता[1] = 0;
        प्रति (i = 1; i <= 15; ++i) { प्रयुक्तम्_syms += योग_syms[i]; अग्र_संहिता[i + 1] = (योग = ((योग + योग_syms[i]) << 1)); }
        यदि ((65536 != योग) && (प्रयुक्तम्_syms > 1))
        {
          TINFL_CR_RETURN_FOREVER(35, TINFL_स्थितिः_FAILED);
        }
        प्रति (वृक्षः_अग्र = -1, sym_सूचकांक = 0; sym_सूचकांक < r->m_सारणी_sizes[r->m_type]; ++sym_सूचकांक)
        {
          mz_uint rev_संहिता = 0, l, cur_संहिता, संहिता_आकार_2 = p_सारणी->m_संहिता_आकार[sym_सूचकांक]; यदि (!संहिता_आकार_2) अनुवर्त;
          cur_संहिता = अग्र_संहिता[संहिता_आकार_2]++; प्रति (l = संहिता_आकार_2; l > 0; l--, cur_संहिता >>= 1) rev_संहिता = (rev_संहिता << 1) | (cur_संहिता & 1);
          यदि (संहिता_आकार_2 <= TINFL_FAST_LOOKUP_द्वयङ्काः) { mz_int16 k = (mz_int16)((संहिता_आकार_2 << 9) | sym_सूचकांक); यावत् (rev_संहिता < TINFL_FAST_LOOKUP_आकार) { p_सारणी->m_look_ऊर्ध्वम्[rev_संहिता] = k; rev_संहिता += (1 << संहिता_आकार_2); } अनुवर्त; }
          यदि (0 == (वृक्षः_cur = p_सारणी->m_look_ऊर्ध्वम्[rev_संहिता & (TINFL_FAST_LOOKUP_आकार - 1)])) { p_सारणी->m_look_ऊर्ध्वम्[rev_संहिता & (TINFL_FAST_LOOKUP_आकार - 1)] = (mz_int16)वृक्षः_अग्र; वृक्षः_cur = वृक्षः_अग्र; वृक्षः_अग्र -= 2; }
          rev_संहिता >>= (TINFL_FAST_LOOKUP_द्वयङ्काः - 1);
          प्रति (j = संहिता_आकार_2; j > (TINFL_FAST_LOOKUP_द्वयङ्काः + 1); j--)
          {
            वृक्षः_cur -= ((rev_संहिता >>= 1) & 1);
            यदि (!p_सारणी->m_वृक्षः[-वृक्षः_cur - 1]) { p_सारणी->m_वृक्षः[-वृक्षः_cur - 1] = (mz_int16)वृक्षः_अग्र; वृक्षः_cur = वृक्षः_अग्र; वृक्षः_अग्र -= 2; } अन्यथा वृक्षः_cur = p_सारणी->m_वृक्षः[-वृक्षः_cur - 1];
          }
          वृक्षः_cur -= ((rev_संहिता >>= 1) & 1); p_सारणी->m_वृक्षः[-वृक्षः_cur - 1] = (mz_int16)sym_सूचकांक;
        }
        यदि (r->m_type == 2)
        {
          प्रति (गणक = 0; गणक < (r->m_सारणी_sizes[0] + r->m_सारणी_sizes[1]); )
          {
            mz_uint s; TINFL_HUFF_DECODE(16, dist, &r->m_tables[2]); यदि (dist < 16) { r->m_len_codes[गणक++] = (mz_uint8)dist; अनुवर्त; }
            यदि ((dist == 16) && (!गणक))
            {
              TINFL_CR_RETURN_FOREVER(17, TINFL_स्थितिः_FAILED);
            }
            अङ्कः_extra = "\02\03\07"[dist - 16]; TINFL_GET_द्वयङ्काः(18, s, अङ्कः_extra); s += "\03\03\013"[dist - 16];
            TINFL_MEMSET(r->m_len_codes + गणक, (dist == 16) ? r->m_len_codes[गणक - 1] : 0, s); गणक += s;
          }
          यदि ((r->m_सारणी_sizes[0] + r->m_सारणी_sizes[1]) != गणक)
          {
            TINFL_CR_RETURN_FOREVER(21, TINFL_स्थितिः_FAILED);
          }
          TINFL_MEMCPY(r->m_tables[0].m_संहिता_आकार, r->m_len_codes, r->m_सारणी_sizes[0]); TINFL_MEMCPY(r->m_tables[1].m_संहिता_आकार, r->m_len_codes + r->m_सारणी_sizes[0], r->m_सारणी_sizes[1]);
        }
      }
      प्रति ( ; ; )
      {
        mz_uint8 *pSrc;
        प्रति ( ; ; )
        {
          यदि (((p_अन्तर्_buf_अन्तः - p_अन्तर्_buf_cur) < 4) || ((p_बहिर्गमनम्_buf_अन्तः - p_बहिर्गमनम्_buf_cur) < 2))
          {
            TINFL_HUFF_DECODE(23, गणक, &r->m_tables[0]);
            यदि (गणक >= 256)
              भङ्ग;
            यावत् (p_बहिर्गमनम्_buf_cur >= p_बहिर्गमनम्_buf_अन्तः) { TINFL_CR_RETURN(24, TINFL_स्थितिः_HAS_अधिकम्_OUTPUT); }
            *p_बहिर्गमनम्_buf_cur++ = (mz_uint8)गणक;
          }
          अन्यथा
          {
            पूर्णाङ्क sym2; mz_uint संहिता_len;
#यदि TINFL_USE_64BIT_BITBUF
            यदि (अङ्कः_द्वयङ्काः < 30) { bit_buf |= (((tinfl_bit_buf_t)MZ_READ_LE32(p_अन्तर्_buf_cur)) << अङ्कः_द्वयङ्काः); p_अन्तर्_buf_cur += 4; अङ्कः_द्वयङ्काः += 32; }
#अन्यथा
            यदि (अङ्कः_द्वयङ्काः < 15) { bit_buf |= (((tinfl_bit_buf_t)MZ_READ_LE16(p_अन्तर्_buf_cur)) << अङ्कः_द्वयङ्काः); p_अन्तर्_buf_cur += 2; अङ्कः_द्वयङ्काः += 16; }
#यदि_अन्तः
            यदि ((sym2 = r->m_tables[0].m_look_ऊर्ध्वम्[bit_buf & (TINFL_FAST_LOOKUP_आकार - 1)]) >= 0)
              संहिता_len = sym2 >> 9;
            अन्यथा
            {
              संहिता_len = TINFL_FAST_LOOKUP_द्वयङ्काः; कुरु { sym2 = r->m_tables[0].m_वृक्षः[~sym2 + ((bit_buf >> संहिता_len++) & 1)]; } यावत् (sym2 < 0);
            }
            गणक = sym2; bit_buf >>= संहिता_len; अङ्कः_द्वयङ्काः -= संहिता_len;
            यदि (गणक & 256)
              भङ्ग;

#यदि !TINFL_USE_64BIT_BITBUF
            यदि (अङ्कः_द्वयङ्काः < 15) { bit_buf |= (((tinfl_bit_buf_t)MZ_READ_LE16(p_अन्तर्_buf_cur)) << अङ्कः_द्वयङ्काः); p_अन्तर्_buf_cur += 2; अङ्कः_द्वयङ्काः += 16; }
#यदि_अन्तः
            यदि ((sym2 = r->m_tables[0].m_look_ऊर्ध्वम्[bit_buf & (TINFL_FAST_LOOKUP_आकार - 1)]) >= 0)
              संहिता_len = sym2 >> 9;
            अन्यथा
            {
              संहिता_len = TINFL_FAST_LOOKUP_द्वयङ्काः; कुरु { sym2 = r->m_tables[0].m_वृक्षः[~sym2 + ((bit_buf >> संहिता_len++) & 1)]; } यावत् (sym2 < 0);
            }
            bit_buf >>= संहिता_len; अङ्कः_द्वयङ्काः -= संहिता_len;

            p_बहिर्गमनम्_buf_cur[0] = (mz_uint8)गणक;
            यदि (sym2 & 256)
            {
              p_बहिर्गमनम्_buf_cur++;
              गणक = sym2;
              भङ्ग;
            }
            p_बहिर्गमनम्_buf_cur[1] = (mz_uint8)sym2;
            p_बहिर्गमनम्_buf_cur += 2;
          }
        }
        यदि ((गणक &= 511) == 256) भङ्ग;

        अङ्कः_extra = s_दीर्घता_extra[गणक - 257]; गणक = s_दीर्घता_आधारः[गणक - 257];
        यदि (अङ्कः_extra) { mz_uint extra_द्वयङ्काः; TINFL_GET_द्वयङ्काः(25, extra_द्वयङ्काः, अङ्कः_extra); गणक += extra_द्वयङ्काः; }

        TINFL_HUFF_DECODE(26, dist, &r->m_tables[1]);
        अङ्कः_extra = s_dist_extra[dist]; dist = s_dist_आधारः[dist];
        यदि (अङ्कः_extra) { mz_uint extra_द्वयङ्काः; TINFL_GET_द्वयङ्काः(27, extra_द्वयङ्काः, अङ्कः_extra); dist += extra_द्वयङ्काः; }

        dist_from_बहिर्गमनम्_buf_start = p_बहिर्गमनम्_buf_cur - p_बहिर्गमनम्_buf_start;
        यदि ((dist > dist_from_बहिर्गमनम्_buf_start) && (decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF))
        {
          TINFL_CR_RETURN_FOREVER(37, TINFL_स्थितिः_FAILED);
        }

        pSrc = p_बहिर्गमनम्_buf_start + ((dist_from_बहिर्गमनम्_buf_start - dist) & बहिर्गमनम्_buf_आकार_आवरणम्);

        यदि ((MZ_MAX(p_बहिर्गमनम्_buf_cur, pSrc) + गणक) > p_बहिर्गमनम्_buf_अन्तः)
        {
          यावत् (गणक--)
          {
            यावत् (p_बहिर्गमनम्_buf_cur >= p_बहिर्गमनम्_buf_अन्तः) { TINFL_CR_RETURN(53, TINFL_स्थितिः_HAS_अधिकम्_OUTPUT); }
            *p_बहिर्गमनम्_buf_cur++ = p_बहिर्गमनम्_buf_start[(dist_from_बहिर्गमनम्_buf_start++ - dist) & बहिर्गमनम्_buf_आकार_आवरणम्];
          }
          अनुवर्त;
        }
#यदि MINIZ_USE_UNALIGNED_LOADS_AND_STORES
        अन्यथा यदि ((गणक >= 9) && (गणक <= dist))
        {
          ध्रुव mz_uint8 *p_Src_अन्तः = pSrc + (गणक & ~7);
          कुरु
          {
            ((mz_uint32 *)p_बहिर्गमनम्_buf_cur)[0] = ((ध्रुव mz_uint32 *)pSrc)[0];
            ((mz_uint32 *)p_बहिर्गमनम्_buf_cur)[1] = ((ध्रुव mz_uint32 *)pSrc)[1];
            p_बहिर्गमनम्_buf_cur += 8;
          } यावत् ((pSrc += 8) < p_Src_अन्तः);
          यदि ((गणक &= 7) < 3)
          {
            यदि (गणक)
            {
              p_बहिर्गमनम्_buf_cur[0] = pSrc[0];
              यदि (गणक > 1)
                p_बहिर्गमनम्_buf_cur[1] = pSrc[1];
              p_बहिर्गमनम्_buf_cur += गणक;
            }
            अनुवर्त;
          }
        }
#यदि_अन्तः
        कुरु
        {
          p_बहिर्गमनम्_buf_cur[0] = pSrc[0];
          p_बहिर्गमनम्_buf_cur[1] = pSrc[1];
          p_बहिर्गमनम्_buf_cur[2] = pSrc[2];
          p_बहिर्गमनम्_buf_cur += 3; pSrc += 3;
        } यावत् ((पूर्णाङ्क)(गणक -= 3) > 2);
        यदि ((पूर्णाङ्क)गणक > 0)
        {
          p_बहिर्गमनम्_buf_cur[0] = pSrc[0];
          यदि ((पूर्णाङ्क)गणक > 1)
            p_बहिर्गमनम्_buf_cur[1] = pSrc[1];
          p_बहिर्गमनम्_buf_cur += गणक;
        }
      }
    }
  } यावत् (!(r->m_final & 1));
  यदि (decomp_flags & TINFL_FLAG_PARSE_ZLIB_शीर्षकम्)
  {
    TINFL_SKIP_द्वयङ्काः(32, अङ्कः_द्वयङ्काः & 7); प्रति (गणक = 0; गणक < 4; ++गणक) { mz_uint s; यदि (अङ्कः_द्वयङ्काः) TINFL_GET_द्वयङ्काः(41, s, 8); अन्यथा TINFL_GET_BYTE(42, s); r->m_z_adler32 = (r->m_z_adler32 << 8) | s; }
  }
  TINFL_CR_RETURN_FOREVER(34, TINFL_स्थितिः_समाप्तम्);
  TINFL_CR_FINISH

common_exit:
  r->m_अङ्कः_द्वयङ्काः = अङ्कः_द्वयङ्काः; r->m_bit_buf = bit_buf; r->m_dist = dist; r->m_गणक = गणक; r->m_अङ्कः_extra = अङ्कः_extra; r->m_dist_from_बहिर्गमनम्_buf_start = dist_from_बहिर्गमनम्_buf_start;
  *p_अन्तर्_buf_आकार = p_अन्तर्_buf_cur - p_अन्तर्_buf_अग्र; *p_बहिर्गमनम्_buf_आकार = p_बहिर्गमनम्_buf_cur - p_बहिर्गमनम्_buf_अग्र;
  यदि ((decomp_flags & (TINFL_FLAG_PARSE_ZLIB_शीर्षकम् | TINFL_FLAG_COMPUTE_ADLER32)) && (स्थितिः >= 0))
  {
    ध्रुव mz_uint8 *ptr = p_बहिर्गमनम्_buf_अग्र; size_t buf_len = *p_बहिर्गमनम्_buf_आकार;
    mz_uint32 i, s1 = r->m_check_adler32 & 0xffff, s2 = r->m_check_adler32 >> 16; size_t खण्डम्_len = buf_len % 5552;
    यावत् (buf_len)
    {
      प्रति (i = 0; i + 7 < खण्डम्_len; i += 8, ptr += 8)
      {
        s1 += ptr[0], s2 += s1; s1 += ptr[1], s2 += s1; s1 += ptr[2], s2 += s1; s1 += ptr[3], s2 += s1;
        s1 += ptr[4], s2 += s1; s1 += ptr[5], s2 += s1; s1 += ptr[6], s2 += s1; s1 += ptr[7], s2 += s1;
      }
      प्रति ( ; i < खण्डम्_len; ++i) s1 += *ptr++, s2 += s1;
      s1 %= 65521U, s2 %= 65521U; buf_len -= खण्डम्_len; खण्डम्_len = 5552;
    }
    r->m_check_adler32 = (s2 << 16) + s1; यदि ((स्थितिः == TINFL_स्थितिः_समाप्तम्) && (decomp_flags & TINFL_FLAG_PARSE_ZLIB_शीर्षकम्) && (r->m_check_adler32 != r->m_z_adler32)) स्थितिः = TINFL_स्थितिः_ADLER32_MISMATCH;
  }
  प्रत्यागम स्थितिः;
}

// Higher level helper functions.
शून्य *tinfl_decompress_mem_गन्तव्यम्_heap(ध्रुव शून्य *pSrc_buf, size_t src_buf_len, size_t *p_बहिर्गमनम्_len, पूर्णाङ्क flags)
{
  tinfl_decompressor decomp; शून्य *pBuf = रिक्त, *pNew_buf; size_t src_buf_ofs = 0, बहिर्गमनम्_buf_क्षमता = 0;
  *p_बहिर्गमनम्_len = 0;
  tinfl_init(&decomp);
  प्रति ( ; ; )
  {
    size_t src_buf_आकार = src_buf_len - src_buf_ofs, dst_buf_आकार = बहिर्गमनम्_buf_क्षमता - *p_बहिर्गमनम्_len, new_बहिर्गमनम्_buf_क्षमता;
    tinfl_स्थितिः स्थितिः = tinfl_decompress(&decomp, (ध्रुव mz_uint8*)pSrc_buf + src_buf_ofs, &src_buf_आकार, (mz_uint8*)pBuf, pBuf ? (mz_uint8*)pBuf + *p_बहिर्गमनम्_len : रिक्त, &dst_buf_आकार,
      (flags & ~TINFL_FLAG_HAS_अधिकम्_निवेशः) | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF);
    यदि ((स्थितिः < 0) || (स्थितिः == TINFL_स्थितिः_NEEDS_अधिकम्_निवेशः))
    {
      MZ_FREE(pBuf); *p_बहिर्गमनम्_len = 0; प्रत्यागम रिक्त;
    }
    src_buf_ofs += src_buf_आकार;
    *p_बहिर्गमनम्_len += dst_buf_आकार;
    यदि (स्थितिः == TINFL_स्थितिः_समाप्तम्) भङ्ग;
    new_बहिर्गमनम्_buf_क्षमता = बहिर्गमनम्_buf_क्षमता * 2; यदि (new_बहिर्गमनम्_buf_क्षमता < 128) new_बहिर्गमनम्_buf_क्षमता = 128;
    pNew_buf = MZ_REALLOC(pBuf, new_बहिर्गमनम्_buf_क्षमता);
    यदि (!pNew_buf)
    {
      MZ_FREE(pBuf); *p_बहिर्गमनम्_len = 0; प्रत्यागम रिक्त;
    }
    pBuf = pNew_buf; बहिर्गमनम्_buf_क्षमता = new_बहिर्गमनम्_buf_क्षमता;
  }
  प्रत्यागम pBuf;
}

size_t tinfl_decompress_mem_गन्तव्यम्_mem(शून्य *p_बहिर्गमनम्_buf, size_t बहिर्गमनम्_buf_len, ध्रुव शून्य *pSrc_buf, size_t src_buf_len, पूर्णाङ्क flags)
{
  tinfl_decompressor decomp; tinfl_स्थितिः स्थितिः; tinfl_init(&decomp);
  स्थितिः = tinfl_decompress(&decomp, (ध्रुव mz_uint8*)pSrc_buf, &src_buf_len, (mz_uint8*)p_बहिर्गमनम्_buf, (mz_uint8*)p_बहिर्गमनम्_buf, &बहिर्गमनम्_buf_len, (flags & ~TINFL_FLAG_HAS_अधिकम्_निवेशः) | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF);
  प्रत्यागम (स्थितिः != TINFL_स्थितिः_समाप्तम्) ? TINFL_DECOMPRESS_MEM_गन्तव्यम्_MEM_FAILED : बहिर्गमनम्_buf_len;
}

पूर्णाङ्क tinfl_decompress_mem_गन्तव्यम्_callback(ध्रुव शून्य *p_अन्तर्_buf, size_t *p_अन्तर्_buf_आकार, tinfl_put_buf_func_ptr pPut_buf_func, शून्य *pPut_buf_user, पूर्णाङ्क flags)
{
  पूर्णाङ्क परिणाम = 0;
  tinfl_decompressor decomp;
  mz_uint8 *pDict = (mz_uint8*)MZ_MALLOC(TINFL_LZ_DICT_आकार); size_t अन्तर्_buf_ofs = 0, dict_ofs = 0;
  यदि (!pDict)
    प्रत्यागम TINFL_स्थितिः_FAILED;
  स्मृतिं_पूरय(pDict,0,TINFL_LZ_DICT_आकार);
  tinfl_init(&decomp);
  प्रति ( ; ; )
  {
    size_t अन्तर्_buf_आकार = *p_अन्तर्_buf_आकार - अन्तर्_buf_ofs, dst_buf_आकार = TINFL_LZ_DICT_आकार - dict_ofs;
    tinfl_स्थितिः स्थितिः = tinfl_decompress(&decomp, (ध्रुव mz_uint8*)p_अन्तर्_buf + अन्तर्_buf_ofs, &अन्तर्_buf_आकार, pDict, pDict + dict_ofs, &dst_buf_आकार,
      (flags & ~(TINFL_FLAG_HAS_अधिकम्_निवेशः | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF)));
    अन्तर्_buf_ofs += अन्तर्_buf_आकार;
    यदि ((dst_buf_आकार) && (!(*pPut_buf_func)(pDict + dict_ofs, (पूर्णाङ्क)dst_buf_आकार, pPut_buf_user)))
      भङ्ग;
    यदि (स्थितिः != TINFL_स्थितिः_HAS_अधिकम्_OUTPUT)
    {
      परिणाम = (स्थितिः == TINFL_स्थितिः_समाप्तम्);
      भङ्ग;
    }
    dict_ofs = (dict_ofs + dst_buf_आकार) & (TINFL_LZ_DICT_आकार - 1);
  }
  MZ_FREE(pDict);
  *p_अन्तर्_buf_आकार = अन्तर्_buf_ofs;
  प्रत्यागम परिणाम;
}
#यदि_अन्तः /*#ifndef MINIZ_NO_INFLATE_APIS*/

// ------------------- Low-level Compression (independent from all decompression API's)
#यदि_अपरिभाषितम् MINIZ_NO_DEFLATE_APIS

// Purposely making these tables static for faster init and thread safety.
स्थिर ध्रुव mz_uint16 s_tdefl_len_sym[256] = {
  257,258,259,260,261,262,263,264,265,265,266,266,267,267,268,268,269,269,269,269,270,270,270,270,271,271,271,271,272,272,272,272,
  273,273,273,273,273,273,273,273,274,274,274,274,274,274,274,274,275,275,275,275,275,275,275,275,276,276,276,276,276,276,276,276,
  277,277,277,277,277,277,277,277,277,277,277,277,277,277,277,277,278,278,278,278,278,278,278,278,278,278,278,278,278,278,278,278,
  279,279,279,279,279,279,279,279,279,279,279,279,279,279,279,279,280,280,280,280,280,280,280,280,280,280,280,280,280,280,280,280,
  281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,
  282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,
  283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,
  284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,285 };

स्थिर ध्रुव mz_uint8 s_tdefl_len_extra[256] = {
  0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0 };

स्थिर ध्रुव mz_uint8 s_tdefl_small_dist_sym[512] = {
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

स्थिर ध्रुव mz_uint8 s_tdefl_small_dist_extra[512] = {
  0,0,0,0,1,1,1,1,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
  6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
  6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7 };

स्थिर ध्रुव mz_uint8 s_tdefl_large_dist_sym[128] = {
  0,0,18,19,20,20,21,21,22,22,22,22,23,23,23,23,24,24,24,24,24,24,24,24,25,25,25,25,25,25,25,25,26,26,26,26,26,26,26,26,26,26,26,26,
  26,26,26,26,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,
  28,28,28,28,28,28,28,28,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29 };

स्थिर ध्रुव mz_uint8 s_tdefl_large_dist_extra[128] = {
  0,0,8,8,9,9,9,9,10,10,10,10,10,10,10,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,
  12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
  13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13 };

// Radix sorts tdefl_sym_freq[] array by 16-bit key m_key. Returns ptr to sorted values.
प्रकारनिर्देश संरचना { mz_uint16 m_कुञ्चिका, m_sym_सूचकांक; } tdefl_sym_freq;
स्थिर tdefl_sym_freq* tdefl_radix_क्रमय_syms(mz_uint अङ्कः_syms, tdefl_sym_freq* pSyms0, tdefl_sym_freq* pSyms1)
{
  mz_uint32 योग_passes = 2, pass_सरणम्, pass, i, hist[256 * 2]; tdefl_sym_freq* pCur_syms = pSyms0, *pNew_syms = pSyms1; MZ_CLEAR_ARR(hist);
  प्रति (i = 0; i < अङ्कः_syms; i++) { mz_uint freq = pSyms0[i].m_कुञ्चिका; hist[freq & 0xFF]++; hist[256 + ((freq >> 8) & 0xFF)]++; }
  यावत् ((योग_passes > 1) && (अङ्कः_syms == hist[(योग_passes - 1) * 256])) योग_passes--;
  प्रति (pass_सरणम् = 0, pass = 0; pass < योग_passes; pass++, pass_सरणम् += 8)
  {
    ध्रुव mz_uint32* pHist = &hist[pass << 8];
    mz_uint offsets[256], cur_ofs = 0;
    प्रति (i = 0; i < 256; i++) { offsets[i] = cur_ofs; cur_ofs += pHist[i]; }
    प्रति (i = 0; i < अङ्कः_syms; i++) pNew_syms[offsets[(pCur_syms[i].m_कुञ्चिका >> pass_सरणम्) & 0xFF]++] = pCur_syms[i];
    { tdefl_sym_freq* t = pCur_syms; pCur_syms = pNew_syms; pNew_syms = t; }
  }
  प्रत्यागम pCur_syms;
}

// tdefl_calculate_minimum_redundancy() originally written by: Alistair Moffat, alistair@cs.mu.oz.au, Jyrki Katajainen, jyrki@diku.dk, November 1996.
स्थिर शून्य tdefl_calculate_minimum_redundancy(tdefl_sym_freq *A, पूर्णाङ्क n)
{
  पूर्णाङ्क मूलम्, पर्णम्, अग्र, avbl, प्रयुक्तम्, dpth;
  यदि (n==0) प्रत्यागम; अन्यथा यदि (n==1) { A[0].m_कुञ्चिका = 1; प्रत्यागम; }
  A[0].m_कुञ्चिका += A[1].m_कुञ्चिका; मूलम् = 0; पर्णम् = 2;
  प्रति (अग्र=1; अग्र < n-1; अग्र++)
  {
    यदि (पर्णम्>=n || A[मूलम्].m_कुञ्चिका<A[पर्णम्].m_कुञ्चिका) { A[अग्र].m_कुञ्चिका = A[मूलम्].m_कुञ्चिका; A[मूलम्++].m_कुञ्चिका = (mz_uint16)अग्र; } अन्यथा A[अग्र].m_कुञ्चिका = A[पर्णम्++].m_कुञ्चिका;
    यदि (पर्णम्>=n || (मूलम्<अग्र && A[मूलम्].m_कुञ्चिका<A[पर्णम्].m_कुञ्चिका)) { A[अग्र].m_कुञ्चिका = (mz_uint16)(A[अग्र].m_कुञ्चिका + A[मूलम्].m_कुञ्चिका); A[मूलम्++].m_कुञ्चिका = (mz_uint16)अग्र; } अन्यथा A[अग्र].m_कुञ्चिका = (mz_uint16)(A[अग्र].m_कुञ्चिका + A[पर्णम्++].m_कुञ्चिका);
  }
  A[n-2].m_कुञ्चिका = 0; प्रति (अग्र=n-3; अग्र>=0; अग्र--) A[अग्र].m_कुञ्चिका = A[A[अग्र].m_कुञ्चिका].m_कुञ्चिका+1;
  avbl = 1; प्रयुक्तम् = dpth = 0; मूलम् = n-2; अग्र = n-1;
  यावत् (avbl>0)
  {
    यावत् (मूलम्>=0 && (पूर्णाङ्क)A[मूलम्].m_कुञ्चिका==dpth) { प्रयुक्तम्++; मूलम्--; }
    यावत् (avbl>प्रयुक्तम्) { A[अग्र--].m_कुञ्चिका = (mz_uint16)(dpth); avbl--; }
    avbl = 2*प्रयुक्तम्; dpth++; प्रयुक्तम् = 0;
  }
}

// Limits canonical Huffman code table's max code size.
गणना { TDEFL_MAX_SUPPORTED_HUFF_CODESIZE = 32 };
स्थिर शून्य tdefl_huffman_enforce_max_संहिता_आकार(पूर्णाङ्क *p_अङ्कः_codes, पूर्णाङ्क संहिता_list_len, पूर्णाङ्क max_संहिता_आकार)
{
  पूर्णाङ्क i; mz_uint32 योग = 0; यदि (संहिता_list_len <= 1) प्रत्यागम;
  प्रति (i = max_संहिता_आकार + 1; i <= TDEFL_MAX_SUPPORTED_HUFF_CODESIZE; i++) p_अङ्कः_codes[max_संहिता_आकार] += p_अङ्कः_codes[i];
  प्रति (i = max_संहिता_आकार; i > 0; i--) योग += (((mz_uint32)p_अङ्कः_codes[i]) << (max_संहिता_आकार - i));
  यावत् (योग != (1UL << max_संहिता_आकार))
  {
    p_अङ्कः_codes[max_संहिता_आकार]--;
    प्रति (i = max_संहिता_आकार - 1; i > 0; i--) यदि (p_अङ्कः_codes[i]) { p_अङ्कः_codes[i]--; p_अङ्कः_codes[i + 1] += 2; भङ्ग; }
    योग--;
  }
}

स्थिर शून्य tdefl_optimize_huffman_सारणी(tdefl_compressor *d, पूर्णाङ्क सारणी_अङ्कः, पूर्णाङ्क सारणी_len, पूर्णाङ्क संहिता_आकार_सीमा, पूर्णाङ्क static_सारणी)
{
  पूर्णाङ्क i, j, l, अङ्कः_codes[1 + TDEFL_MAX_SUPPORTED_HUFF_CODESIZE]; mz_uint अग्र_संहिता[TDEFL_MAX_SUPPORTED_HUFF_CODESIZE + 1]; MZ_CLEAR_ARR(अङ्कः_codes);
  यदि (static_सारणी)
  {
    प्रति (i = 0; i < सारणी_len; i++) अङ्कः_codes[d->m_huff_संहिता_sizes[सारणी_अङ्कः][i]]++;
  }
  अन्यथा
  {
    tdefl_sym_freq syms0[TDEFL_MAX_HUFF_SYMBOLS], syms1[TDEFL_MAX_HUFF_SYMBOLS], *pSyms;
    पूर्णाङ्क अङ्कः_प्रयुक्तम्_syms = 0;
    ध्रुव mz_uint16 *p_Sym_गणनम् = &d->m_huff_गणनम्[सारणी_अङ्कः][0];
    प्रति (i = 0; i < सारणी_len; i++) यदि (p_Sym_गणनम्[i]) { syms0[अङ्कः_प्रयुक्तम्_syms].m_कुञ्चिका = (mz_uint16)p_Sym_गणनम्[i]; syms0[अङ्कः_प्रयुक्तम्_syms++].m_sym_सूचकांक = (mz_uint16)i; }

    pSyms = tdefl_radix_क्रमय_syms(अङ्कः_प्रयुक्तम्_syms, syms0, syms1); tdefl_calculate_minimum_redundancy(pSyms, अङ्कः_प्रयुक्तम्_syms);

    प्रति (i = 0; i < अङ्कः_प्रयुक्तम्_syms; i++) अङ्कः_codes[pSyms[i].m_कुञ्चिका]++;

    tdefl_huffman_enforce_max_संहिता_आकार(अङ्कः_codes, अङ्कः_प्रयुक्तम्_syms, संहिता_आकार_सीमा);

    MZ_CLEAR_ARR(d->m_huff_संहिता_sizes[सारणी_अङ्कः]); MZ_CLEAR_ARR(d->m_huff_codes[सारणी_अङ्कः]);
    प्रति (i = 1, j = अङ्कः_प्रयुक्तम्_syms; i <= संहिता_आकार_सीमा; i++)
      प्रति (l = अङ्कः_codes[i]; l > 0; l--) d->m_huff_संहिता_sizes[सारणी_अङ्कः][pSyms[--j].m_sym_सूचकांक] = (mz_uint8)(i);
  }

  अग्र_संहिता[1] = 0; प्रति (j = 0, i = 2; i <= संहिता_आकार_सीमा; i++) अग्र_संहिता[i] = j = ((j + अङ्कः_codes[i - 1]) << 1);

  प्रति (i = 0; i < सारणी_len; i++)
  {
    mz_uint rev_संहिता = 0, संहिता, संहिता_आकार_2; यदि ((संहिता_आकार_2 = d->m_huff_संहिता_sizes[सारणी_अङ्कः][i]) == 0) अनुवर्त;
    संहिता = अग्र_संहिता[संहिता_आकार_2]++; प्रति (l = संहिता_आकार_2; l > 0; l--, संहिता >>= 1) rev_संहिता = (rev_संहिता << 1) | (संहिता & 1);
    d->m_huff_codes[सारणी_अङ्कः][i] = (mz_uint16)rev_संहिता;
  }
}

#परिभाषय TDEFL_PUT_द्वयङ्काः(b, l) कुरु { \
  mz_uint द्वयङ्काः = b; mz_uint len = l; MZ_ASSERT(द्वयङ्काः <= ((1U << len) - 1U)); \
  d->m_bit_बफर |= (द्वयङ्काः << d->m_द्वयङ्काः_अन्तर्); d->m_द्वयङ्काः_अन्तर् += len; \
  यावत् (d->m_द्वयङ्काः_अन्तर् >= 8) { \
    यदि (d->m_pOutput_buf < d->m_p_Output_buf_अन्तः) \
      *d->m_pOutput_buf++ = (mz_uint8)(d->m_bit_बफर); \
    d->m_bit_बफर >>= 8; \
    d->m_द्वयङ्काः_अन्तर् -= 8; \
  } \
} MZ_MACRO_अन्तः

#परिभाषय TDEFL_RLE_पूर्व_संहिता_आकार() कुरु { \
  यदि (rle_repeat_गणनम्) { \
    यदि (rle_repeat_गणनम् < 3) { \
      d->m_huff_गणनम्[2][पूर्व_संहिता_आकार] = (mz_uint16)(d->m_huff_गणनम्[2][पूर्व_संहिता_आकार] + rle_repeat_गणनम्); \
      यावत् (rle_repeat_गणनम्--) packed_संहिता_sizes[अङ्कः_packed_संहिता_sizes++] = पूर्व_संहिता_आकार; \
    } अन्यथा { \
      d->m_huff_गणनम्[2][16] = (mz_uint16)(d->m_huff_गणनम्[2][16] + 1); packed_संहिता_sizes[अङ्कः_packed_संहिता_sizes++] = 16; packed_संहिता_sizes[अङ्कः_packed_संहिता_sizes++] = (mz_uint8)(rle_repeat_गणनम् - 3); \
  } rle_repeat_गणनम् = 0; } \
} MZ_MACRO_अन्तः

#परिभाषय TDEFL_RLE_ZERO_संहिता_आकार() कुरु { \
  यदि (rle_z_गणनम्) { \
    यदि (rle_z_गणनम् < 3) { \
      d->m_huff_गणनम्[2][0] = (mz_uint16)(d->m_huff_गणनम्[2][0] + rle_z_गणनम्); यावत् (rle_z_गणनम्--) packed_संहिता_sizes[अङ्कः_packed_संहिता_sizes++] = 0; \
    } अन्यथा यदि (rle_z_गणनम् <= 10) { \
      d->m_huff_गणनम्[2][17] = (mz_uint16)(d->m_huff_गणनम्[2][17] + 1); packed_संहिता_sizes[अङ्कः_packed_संहिता_sizes++] = 17; packed_संहिता_sizes[अङ्कः_packed_संहिता_sizes++] = (mz_uint8)(rle_z_गणनम् - 3); \
    } अन्यथा { \
      d->m_huff_गणनम्[2][18] = (mz_uint16)(d->m_huff_गणनम्[2][18] + 1); packed_संहिता_sizes[अङ्कः_packed_संहिता_sizes++] = 18; packed_संहिता_sizes[अङ्कः_packed_संहिता_sizes++] = (mz_uint8)(rle_z_गणनम् - 11); \
  } rle_z_गणनम् = 0; } \
} MZ_MACRO_अन्तः

स्थिर mz_uint8 s_tdefl_packed_संहिता_आकार_syms_swizzle[] = { 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 };

स्थिर शून्य tdefl_start_dynamic_खण्डम्(tdefl_compressor *d)
{
  पूर्णाङ्क अङ्कः_lit_codes, अङ्कः_dist_codes, अङ्कः_bit_lengths; mz_uint i, योग_संहिता_sizes_गन्तव्यम्_pack, अङ्कः_packed_संहिता_sizes, rle_z_गणनम्, rle_repeat_गणनम्, packed_संहिता_sizes_सूचकांक;
  mz_uint8 संहिता_sizes_गन्तव्यम्_pack[TDEFL_MAX_HUFF_SYMBOLS_0 + TDEFL_MAX_HUFF_SYMBOLS_1], packed_संहिता_sizes[TDEFL_MAX_HUFF_SYMBOLS_0 + TDEFL_MAX_HUFF_SYMBOLS_1], पूर्व_संहिता_आकार = 0xFF;

  d->m_huff_गणनम्[0][256] = 1;

  tdefl_optimize_huffman_सारणी(d, 0, TDEFL_MAX_HUFF_SYMBOLS_0, 15, MZ_FALSE);
  tdefl_optimize_huffman_सारणी(d, 1, TDEFL_MAX_HUFF_SYMBOLS_1, 15, MZ_FALSE);

  प्रति (अङ्कः_lit_codes = 286; अङ्कः_lit_codes > 257; अङ्कः_lit_codes--) यदि (d->m_huff_संहिता_sizes[0][अङ्कः_lit_codes - 1]) भङ्ग;
  प्रति (अङ्कः_dist_codes = 30; अङ्कः_dist_codes > 1; अङ्कः_dist_codes--) यदि (d->m_huff_संहिता_sizes[1][अङ्कः_dist_codes - 1]) भङ्ग;

  स्मृतिं_प्रतिलिख(संहिता_sizes_गन्तव्यम्_pack, &d->m_huff_संहिता_sizes[0][0], अङ्कः_lit_codes);
  स्मृतिं_प्रतिलिख(संहिता_sizes_गन्तव्यम्_pack + अङ्कः_lit_codes, &d->m_huff_संहिता_sizes[1][0], अङ्कः_dist_codes);
  योग_संहिता_sizes_गन्तव्यम्_pack = अङ्कः_lit_codes + अङ्कः_dist_codes; अङ्कः_packed_संहिता_sizes = 0; rle_z_गणनम् = 0; rle_repeat_गणनम् = 0;

  स्मृतिं_पूरय(&d->m_huff_गणनम्[2][0], 0, परिमाण(d->m_huff_गणनम्[2][0]) * TDEFL_MAX_HUFF_SYMBOLS_2);
  प्रति (i = 0; i < योग_संहिता_sizes_गन्तव्यम्_pack; i++)
  {
    mz_uint8 संहिता_आकार_2 = संहिता_sizes_गन्तव्यम्_pack[i];
    यदि (!संहिता_आकार_2)
    {
      TDEFL_RLE_पूर्व_संहिता_आकार();
      यदि (++rle_z_गणनम् == 138) { TDEFL_RLE_ZERO_संहिता_आकार(); }
    }
    अन्यथा
    {
      TDEFL_RLE_ZERO_संहिता_आकार();
      यदि (संहिता_आकार_2 != पूर्व_संहिता_आकार)
      {
        TDEFL_RLE_पूर्व_संहिता_आकार();
        d->m_huff_गणनम्[2][संहिता_आकार_2] = (mz_uint16)(d->m_huff_गणनम्[2][संहिता_आकार_2] + 1); packed_संहिता_sizes[अङ्कः_packed_संहिता_sizes++] = संहिता_आकार_2;
      }
      अन्यथा यदि (++rle_repeat_गणनम् == 6)
      {
        TDEFL_RLE_पूर्व_संहिता_आकार();
      }
    }
    पूर्व_संहिता_आकार = संहिता_आकार_2;
  }
  यदि (rle_repeat_गणनम्) { TDEFL_RLE_पूर्व_संहिता_आकार(); } अन्यथा { TDEFL_RLE_ZERO_संहिता_आकार(); }

  tdefl_optimize_huffman_सारणी(d, 2, TDEFL_MAX_HUFF_SYMBOLS_2, 7, MZ_FALSE);

  TDEFL_PUT_द्वयङ्काः(2, 2);

  TDEFL_PUT_द्वयङ्काः(अङ्कः_lit_codes - 257, 5);
  TDEFL_PUT_द्वयङ्काः(अङ्कः_dist_codes - 1, 5);

  प्रति (अङ्कः_bit_lengths = 18; अङ्कः_bit_lengths >= 0; अङ्कः_bit_lengths--) यदि (d->m_huff_संहिता_sizes[2][s_tdefl_packed_संहिता_आकार_syms_swizzle[अङ्कः_bit_lengths]]) भङ्ग;
  अङ्कः_bit_lengths = MZ_MAX(4, (अङ्कः_bit_lengths + 1)); TDEFL_PUT_द्वयङ्काः(अङ्कः_bit_lengths - 4, 4);
  प्रति (i = 0; (पूर्णाङ्क)i < अङ्कः_bit_lengths; i++) TDEFL_PUT_द्वयङ्काः(d->m_huff_संहिता_sizes[2][s_tdefl_packed_संहिता_आकार_syms_swizzle[i]], 3);

  प्रति (packed_संहिता_sizes_सूचकांक = 0; packed_संहिता_sizes_सूचकांक < अङ्कः_packed_संहिता_sizes; )
  {
    mz_uint संहिता = packed_संहिता_sizes[packed_संहिता_sizes_सूचकांक++]; MZ_ASSERT(संहिता < TDEFL_MAX_HUFF_SYMBOLS_2);
    TDEFL_PUT_द्वयङ्काः(d->m_huff_codes[2][संहिता], d->m_huff_संहिता_sizes[2][संहिता]);
    यदि (संहिता >= 16) TDEFL_PUT_द्वयङ्काः(packed_संहिता_sizes[packed_संहिता_sizes_सूचकांक++], "\02\03\07"[संहिता - 16]);
  }
}

स्थिर शून्य tdefl_start_static_खण्डम्(tdefl_compressor *d)
{
  mz_uint i;
  mz_uint8 *p = &d->m_huff_संहिता_sizes[0][0];

  प्रति (i = 0; i <= 143; ++i) *p++ = 8;
  प्रति ( ; i <= 255; ++i) *p++ = 9;
  प्रति ( ; i <= 279; ++i) *p++ = 7;
  प्रति ( ; i <= 287; ++i) *p++ = 8;

  स्मृतिं_पूरय(d->m_huff_संहिता_sizes[1], 5, 32);

  tdefl_optimize_huffman_सारणी(d, 0, 288, 15, MZ_TRUE);
  tdefl_optimize_huffman_सारणी(d, 1, 32, 15, MZ_TRUE);

  TDEFL_PUT_द्वयङ्काः(1, 2);
}

स्थिर ध्रुव mz_uint mz_bitmasks[17] = { 0x0000, 0x0001, 0x0003, 0x0007, 0x000F, 0x001F, 0x003F, 0x007F, 0x00FF, 0x01FF, 0x03FF, 0x07FF, 0x0FFF, 0x1FFF, 0x3FFF, 0x7FFF, 0xFFFF };

#यदि MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN && MINIZ_HAS_64BIT_REGISTERS
स्थिर mz_bool tdefl_compress_lz_codes(tdefl_compressor *d)
{
  mz_uint flags;
  mz_uint8 *pLZ_codes;
  mz_uint8 *pOutput_buf = d->m_pOutput_buf;
  mz_uint8 *p_LZ_संहिता_buf_अन्तः = d->m_p_LZ_संहिता_buf;
  mz_uint64 bit_बफर = d->m_bit_बफर;
  mz_uint द्वयङ्काः_अन्तर् = d->m_द्वयङ्काः_अन्तर्;

#परिभाषय TDEFL_PUT_द्वयङ्काः_FAST(b, l) { bit_बफर |= (((mz_uint64)(b)) << द्वयङ्काः_अन्तर्); द्वयङ्काः_अन्तर् += (l); }

  flags = 1;
  प्रति (pLZ_codes = d->m_lz_संहिता_buf; pLZ_codes < p_LZ_संहिता_buf_अन्तः; flags >>= 1)
  {
    यदि (flags == 1)
      flags = *pLZ_codes++ | 0x100;

    यदि (flags & 1)
    {
      mz_uint s0, s1, n0, n1, sym, अङ्कः_extra_द्वयङ्काः;
      mz_uint मेलनम्_len = pLZ_codes[0], मेलनम्_dist = *(ध्रुव mz_uint16 *)(pLZ_codes + 1); pLZ_codes += 3;

      MZ_ASSERT(d->m_huff_संहिता_sizes[0][s_tdefl_len_sym[मेलनम्_len]]);
      TDEFL_PUT_द्वयङ्काः_FAST(d->m_huff_codes[0][s_tdefl_len_sym[मेलनम्_len]], d->m_huff_संहिता_sizes[0][s_tdefl_len_sym[मेलनम्_len]]);
      TDEFL_PUT_द्वयङ्काः_FAST(मेलनम्_len & mz_bitmasks[s_tdefl_len_extra[मेलनम्_len]], s_tdefl_len_extra[मेलनम्_len]);

      // This sequence coaxes MSVC into using cmov's vs. jmp's.
      s0 = s_tdefl_small_dist_sym[मेलनम्_dist & 511];
      n0 = s_tdefl_small_dist_extra[मेलनम्_dist & 511];
      s1 = s_tdefl_large_dist_sym[मेलनम्_dist >> 8];
      n1 = s_tdefl_large_dist_extra[मेलनम्_dist >> 8];
      sym = (मेलनम्_dist < 512) ? s0 : s1;
      अङ्कः_extra_द्वयङ्काः = (मेलनम्_dist < 512) ? n0 : n1;

      MZ_ASSERT(d->m_huff_संहिता_sizes[1][sym]);
      TDEFL_PUT_द्वयङ्काः_FAST(d->m_huff_codes[1][sym], d->m_huff_संहिता_sizes[1][sym]);
      TDEFL_PUT_द्वयङ्काः_FAST(मेलनम्_dist & mz_bitmasks[अङ्कः_extra_द्वयङ्काः], अङ्कः_extra_द्वयङ्काः);
    }
    अन्यथा
    {
      mz_uint lit = *pLZ_codes++;
      MZ_ASSERT(d->m_huff_संहिता_sizes[0][lit]);
      TDEFL_PUT_द्वयङ्काः_FAST(d->m_huff_codes[0][lit], d->m_huff_संहिता_sizes[0][lit]);

      यदि (((flags & 2) == 0) && (pLZ_codes < p_LZ_संहिता_buf_अन्तः))
      {
        flags >>= 1;
        lit = *pLZ_codes++;
        MZ_ASSERT(d->m_huff_संहिता_sizes[0][lit]);
        TDEFL_PUT_द्वयङ्काः_FAST(d->m_huff_codes[0][lit], d->m_huff_संहिता_sizes[0][lit]);

        यदि (((flags & 2) == 0) && (pLZ_codes < p_LZ_संहिता_buf_अन्तः))
        {
          flags >>= 1;
          lit = *pLZ_codes++;
          MZ_ASSERT(d->m_huff_संहिता_sizes[0][lit]);
          TDEFL_PUT_द्वयङ्काः_FAST(d->m_huff_codes[0][lit], d->m_huff_संहिता_sizes[0][lit]);
        }
      }
    }

    यदि (pOutput_buf >= d->m_p_Output_buf_अन्तः)
      प्रत्यागम MZ_FALSE;

    *(mz_uint64*)pOutput_buf = bit_बफर;
    pOutput_buf += (द्वयङ्काः_अन्तर् >> 3);
    bit_बफर >>= (द्वयङ्काः_अन्तर् & ~7);
    द्वयङ्काः_अन्तर् &= 7;
  }

#अपरिभाषय TDEFL_PUT_द्वयङ्काः_FAST

  d->m_pOutput_buf = pOutput_buf;
  d->m_द्वयङ्काः_अन्तर् = 0;
  d->m_bit_बफर = 0;

  यावत् (द्वयङ्काः_अन्तर्)
  {
    mz_uint32 n = MZ_MIN(द्वयङ्काः_अन्तर्, 16);
    TDEFL_PUT_द्वयङ्काः((mz_uint)bit_बफर & mz_bitmasks[n], n);
    bit_बफर >>= n;
    द्वयङ्काः_अन्तर् -= n;
  }

  TDEFL_PUT_द्वयङ्काः(d->m_huff_codes[0][256], d->m_huff_संहिता_sizes[0][256]);

  प्रत्यागम (d->m_pOutput_buf < d->m_p_Output_buf_अन्तः);
}
#अन्यथा
स्थिर mz_bool tdefl_compress_lz_codes(tdefl_compressor *d)
{
  mz_uint flags;
  mz_uint8 *pLZ_codes;

  flags = 1;
  प्रति (pLZ_codes = d->m_lz_संहिता_buf; pLZ_codes < d->m_p_LZ_संहिता_buf; flags >>= 1)
  {
    यदि (flags == 1)
      flags = *pLZ_codes++ | 0x100;
    यदि (flags & 1)
    {
      mz_uint sym, अङ्कः_extra_द्वयङ्काः;
      mz_uint मेलनम्_len = pLZ_codes[0], मेलनम्_dist = (pLZ_codes[1] | (pLZ_codes[2] << 8)); pLZ_codes += 3;

      MZ_ASSERT(d->m_huff_संहिता_sizes[0][s_tdefl_len_sym[मेलनम्_len]]);
      TDEFL_PUT_द्वयङ्काः(d->m_huff_codes[0][s_tdefl_len_sym[मेलनम्_len]], d->m_huff_संहिता_sizes[0][s_tdefl_len_sym[मेलनम्_len]]);
      TDEFL_PUT_द्वयङ्काः(मेलनम्_len & mz_bitmasks[s_tdefl_len_extra[मेलनम्_len]], s_tdefl_len_extra[मेलनम्_len]);

      यदि (मेलनम्_dist < 512)
      {
        sym = s_tdefl_small_dist_sym[मेलनम्_dist]; अङ्कः_extra_द्वयङ्काः = s_tdefl_small_dist_extra[मेलनम्_dist];
      }
      अन्यथा
      {
        sym = s_tdefl_large_dist_sym[मेलनम्_dist >> 8]; अङ्कः_extra_द्वयङ्काः = s_tdefl_large_dist_extra[मेलनम्_dist >> 8];
      }
      MZ_ASSERT(d->m_huff_संहिता_sizes[1][sym]);
      TDEFL_PUT_द्वयङ्काः(d->m_huff_codes[1][sym], d->m_huff_संहिता_sizes[1][sym]);
      TDEFL_PUT_द्वयङ्काः(मेलनम्_dist & mz_bitmasks[अङ्कः_extra_द्वयङ्काः], अङ्कः_extra_द्वयङ्काः);
    }
    अन्यथा
    {
      mz_uint lit = *pLZ_codes++;
      MZ_ASSERT(d->m_huff_संहिता_sizes[0][lit]);
      TDEFL_PUT_द्वयङ्काः(d->m_huff_codes[0][lit], d->m_huff_संहिता_sizes[0][lit]);
    }
  }

  TDEFL_PUT_द्वयङ्काः(d->m_huff_codes[0][256], d->m_huff_संहिता_sizes[0][256]);

  प्रत्यागम (d->m_pOutput_buf < d->m_p_Output_buf_अन्तः);
}
#यदि_अन्तः // MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN && MINIZ_HAS_64BIT_REGISTERS

स्थिर mz_bool tdefl_compress_खण्डम्(tdefl_compressor *d, mz_bool static_खण्डम्)
{
  यदि (static_खण्डम्)
    tdefl_start_static_खण्डम्(d);
  अन्यथा
    tdefl_start_dynamic_खण्डम्(d);
  प्रत्यागम tdefl_compress_lz_codes(d);
}

स्थिर पूर्णाङ्क tdefl_flush_खण्डम्(tdefl_compressor *d, पूर्णाङ्क flush)
{
  mz_uint saved_bit_buf, saved_द्वयङ्काः_अन्तर्;
  mz_uint8 *pSaved_output_buf;
  mz_bool comp_खण्डम्_succeeded = MZ_FALSE;
  पूर्णाङ्क n, use_raw_खण्डम् = ((d->m_flags & TDEFL_FORCE_ALL_RAW_खण्डानि) != 0) && (d->m_lookahead_pos - d->m_lz_संहिता_buf_dict_pos) <= d->m_dict_आकार;
  mz_uint8 *pOutput_buf_start = ((d->m_pPut_buf_func == रिक्त) && ((*d->m_p_बहिर्गमनम्_buf_आकार - d->m_बहिर्गमनम्_buf_ofs) >= TDEFL_बहिर्गमनम्_BUF_आकार)) ? ((mz_uint8 *)d->m_p_बहिर्गमनम्_buf + d->m_बहिर्गमनम्_buf_ofs) : d->m_output_buf;

  d->m_pOutput_buf = pOutput_buf_start;
  d->m_p_Output_buf_अन्तः = d->m_pOutput_buf + TDEFL_बहिर्गमनम्_BUF_आकार - 16;

  MZ_ASSERT(!d->m_output_flush_remaining);
  d->m_output_flush_ofs = 0;
  d->m_output_flush_remaining = 0;

  *d->m_pLZ_flags = (mz_uint8)(*d->m_pLZ_flags >> d->m_अङ्कः_flags_वामः);
  d->m_p_LZ_संहिता_buf -= (d->m_अङ्कः_flags_वामः == 8);

  यदि ((d->m_flags & TDEFL_WRITE_ZLIB_शीर्षकम्) && (!d->m_खण्डम्_सूचकांक))
  {
    TDEFL_PUT_द्वयङ्काः(0x78, 8); TDEFL_PUT_द्वयङ्काः(0x01, 8);
  }

  TDEFL_PUT_द्वयङ्काः(flush == TDEFL_FINISH, 1);

  pSaved_output_buf = d->m_pOutput_buf; saved_bit_buf = d->m_bit_बफर; saved_द्वयङ्काः_अन्तर् = d->m_द्वयङ्काः_अन्तर्;

  यदि (!use_raw_खण्डम्)
    comp_खण्डम्_succeeded = tdefl_compress_खण्डम्(d, (d->m_flags & TDEFL_FORCE_ALL_STATIC_खण्डानि) || (d->m_योग_lz_अष्टकानि < 48));

  // If the block gets expanded, forget the current contents of the output buffer and send a raw block instead.
  यदि ( ((use_raw_खण्डम्) || ((d->m_योग_lz_अष्टकानि) && ((d->m_pOutput_buf - pSaved_output_buf + 1U) >= d->m_योग_lz_अष्टकानि))) &&
       ((d->m_lookahead_pos - d->m_lz_संहिता_buf_dict_pos) <= d->m_dict_आकार) )
  {
    mz_uint i; d->m_pOutput_buf = pSaved_output_buf; d->m_bit_बफर = saved_bit_buf; d->m_द्वयङ्काः_अन्तर् = saved_द्वयङ्काः_अन्तर्;
    TDEFL_PUT_द्वयङ्काः(0, 2);
    यदि (d->m_द्वयङ्काः_अन्तर्) { TDEFL_PUT_द्वयङ्काः(0, 8 - d->m_द्वयङ्काः_अन्तर्); }
    प्रति (i = 2; i; --i, d->m_योग_lz_अष्टकानि ^= 0xFFFF)
    {
      TDEFL_PUT_द्वयङ्काः(d->m_योग_lz_अष्टकानि & 0xFFFF, 16);
    }
    प्रति (i = 0; i < d->m_योग_lz_अष्टकानि; ++i)
    {
      TDEFL_PUT_द्वयङ्काः(d->m_dict[(d->m_lz_संहिता_buf_dict_pos + i) & TDEFL_LZ_DICT_आकार_आवरणम्], 8);
    }
  }
  // Check for the extremely unlikely (if not impossible) case of the compressed block not fitting into the output buffer when using dynamic codes.
  अन्यथा यदि (!comp_खण्डम्_succeeded)
  {
    d->m_pOutput_buf = pSaved_output_buf; d->m_bit_बफर = saved_bit_buf; d->m_द्वयङ्काः_अन्तर् = saved_द्वयङ्काः_अन्तर्;
    tdefl_compress_खण्डम्(d, MZ_TRUE);
  }

  यदि (flush)
  {
    यदि (flush == TDEFL_FINISH)
    {
      यदि (d->m_द्वयङ्काः_अन्तर्) { TDEFL_PUT_द्वयङ्काः(0, 8 - d->m_द्वयङ्काः_अन्तर्); }
      यदि (d->m_flags & TDEFL_WRITE_ZLIB_शीर्षकम्) { mz_uint i, a = d->m_adler32; प्रति (i = 0; i < 4; i++) { TDEFL_PUT_द्वयङ्काः((a >> 24) & 0xFF, 8); a <<= 8; } }
    }
    अन्यथा
    {
      mz_uint i, z = 0; TDEFL_PUT_द्वयङ्काः(0, 3); यदि (d->m_द्वयङ्काः_अन्तर्) { TDEFL_PUT_द्वयङ्काः(0, 8 - d->m_द्वयङ्काः_अन्तर्); } प्रति (i = 2; i; --i, z ^= 0xFFFF) { TDEFL_PUT_द्वयङ्काः(z & 0xFFFF, 16); }
    }
  }

  MZ_ASSERT(d->m_pOutput_buf < d->m_p_Output_buf_अन्तः);

  स्मृतिं_पूरय(&d->m_huff_गणनम्[0][0], 0, परिमाण(d->m_huff_गणनम्[0][0]) * TDEFL_MAX_HUFF_SYMBOLS_0);
  स्मृतिं_पूरय(&d->m_huff_गणनम्[1][0], 0, परिमाण(d->m_huff_गणनम्[1][0]) * TDEFL_MAX_HUFF_SYMBOLS_1);

  d->m_p_LZ_संहिता_buf = d->m_lz_संहिता_buf + 1; d->m_pLZ_flags = d->m_lz_संहिता_buf; d->m_अङ्कः_flags_वामः = 8; d->m_lz_संहिता_buf_dict_pos += d->m_योग_lz_अष्टकानि; d->m_योग_lz_अष्टकानि = 0; d->m_खण्डम्_सूचकांक++;

  यदि ((n = (पूर्णाङ्क)(d->m_pOutput_buf - pOutput_buf_start)) != 0)
  {
    यदि (d->m_pPut_buf_func)
    {
      *d->m_p_अन्तर्_buf_आकार = d->m_pSrc - (ध्रुव mz_uint8 *)d->m_p_अन्तर्_buf;
      यदि (!(*d->m_pPut_buf_func)(d->m_output_buf, n, d->m_pPut_buf_user))
        प्रत्यागम (d->m_पूर्व_return_स्थितिः = TDEFL_स्थितिः_PUT_BUF_FAILED);
    }
    अन्यथा यदि (pOutput_buf_start == d->m_output_buf)
    {
      पूर्णाङ्क अष्टकानि_गन्तव्यम्_copy = (पूर्णाङ्क)MZ_MIN((size_t)n, (size_t)(*d->m_p_बहिर्गमनम्_buf_आकार - d->m_बहिर्गमनम्_buf_ofs));
      स्मृतिं_प्रतिलिख((mz_uint8 *)d->m_p_बहिर्गमनम्_buf + d->m_बहिर्गमनम्_buf_ofs, d->m_output_buf, अष्टकानि_गन्तव्यम्_copy);
      d->m_बहिर्गमनम्_buf_ofs += अष्टकानि_गन्तव्यम्_copy;
      यदि ((n -= अष्टकानि_गन्तव्यम्_copy) != 0)
      {
        d->m_output_flush_ofs = अष्टकानि_गन्तव्यम्_copy;
        d->m_output_flush_remaining = n;
      }
    }
    अन्यथा
    {
      d->m_बहिर्गमनम्_buf_ofs += n;
    }
  }

  प्रत्यागम d->m_output_flush_remaining;
}

#यदि MINIZ_USE_UNALIGNED_LOADS_AND_STORES
#परिभाषय TDEFL_READ_UNALIGNED_WORD(p) *(ध्रुव mz_uint16*)(p)
स्थिर MZ_FORCEINLINE शून्य tdefl_find_मेलनम्(tdefl_compressor *d, mz_uint lookahead_pos, mz_uint max_dist, mz_uint max_मेलनम्_len, mz_uint *p_मेलनम्_dist, mz_uint *p_मेलनम्_len)
{
  mz_uint dist, pos = lookahead_pos & TDEFL_LZ_DICT_आकार_आवरणम्, मेलनम्_len = *p_मेलनम्_len, probe_pos = pos, अग्र_probe_pos, probe_len;
  mz_uint अङ्कः_probes_वामः = d->m_max_probes[मेलनम्_len >= 32];
  ध्रुव mz_uint16 *s = (ध्रुव mz_uint16*)(d->m_dict + pos), *p, *q;
  mz_uint16 c01 = TDEFL_READ_UNALIGNED_WORD(&d->m_dict[pos + मेलनम्_len - 1]), s01 = TDEFL_READ_UNALIGNED_WORD(s);
  MZ_ASSERT(max_मेलनम्_len <= TDEFL_MAX_मेलनम्_LEN); यदि (max_मेलनम्_len <= मेलनम्_len) प्रत्यागम;
  प्रति ( ; ; )
  {
    प्रति ( ; ; )
    {
      यदि (--अङ्कः_probes_वामः == 0) प्रत्यागम;
      #परिभाषय TDEFL_PROBE \
        अग्र_probe_pos = d->m_अग्र[probe_pos]; \
        यदि ((!अग्र_probe_pos) || ((dist = (mz_uint16)(lookahead_pos - अग्र_probe_pos)) > max_dist)) प्रत्यागम; \
        probe_pos = अग्र_probe_pos & TDEFL_LZ_DICT_आकार_आवरणम्; \
        यदि (TDEFL_READ_UNALIGNED_WORD(&d->m_dict[probe_pos + मेलनम्_len - 1]) == c01) भङ्ग;
      TDEFL_PROBE
      TDEFL_PROBE
      TDEFL_PROBE
    }
    यदि (!dist) भङ्ग;
    q = (ध्रुव mz_uint16*)(d->m_dict + probe_pos);
    यदि (TDEFL_READ_UNALIGNED_WORD(q) != s01) अनुवर्त;
    p = s; probe_len = 32;
    कुरु { } यावत् ( (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) && (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) &&
                   (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) && (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) && (--probe_len > 0) );
    यदि (!probe_len)
    {
      *p_मेलनम्_dist = dist; *p_मेलनम्_len = MZ_MIN(max_मेलनम्_len, TDEFL_MAX_मेलनम्_LEN); भङ्ग;
    }
    अन्यथा यदि ((probe_len = ((mz_uint)(p - s) * 2) + (mz_uint)(*(ध्रुव mz_uint8*)p == *(ध्रुव mz_uint8*)q)) > मेलनम्_len)
    {
      *p_मेलनम्_dist = dist; यदि ((*p_मेलनम्_len = मेलनम्_len = MZ_MIN(max_मेलनम्_len, probe_len)) == max_मेलनम्_len) भङ्ग;
      c01 = TDEFL_READ_UNALIGNED_WORD(&d->m_dict[pos + मेलनम्_len - 1]);
    }
  }
}
#अन्यथा
स्थिर MZ_FORCEINLINE शून्य tdefl_find_मेलनम्(tdefl_compressor *d, mz_uint lookahead_pos, mz_uint max_dist, mz_uint max_मेलनम्_len, mz_uint *p_मेलनम्_dist, mz_uint *p_मेलनम्_len)
{
  mz_uint dist, pos = lookahead_pos & TDEFL_LZ_DICT_आकार_आवरणम्, मेलनम्_len = *p_मेलनम्_len, probe_pos = pos, अग्र_probe_pos, probe_len;
  mz_uint अङ्कः_probes_वामः = d->m_max_probes[मेलनम्_len >= 32];
  ध्रुव mz_uint8 *s = d->m_dict + pos, *p, *q;
  mz_uint8 c0 = d->m_dict[pos + मेलनम्_len], c1 = d->m_dict[pos + मेलनम्_len - 1];
  MZ_ASSERT(max_मेलनम्_len <= TDEFL_MAX_मेलनम्_LEN); यदि (max_मेलनम्_len <= मेलनम्_len) प्रत्यागम;
  प्रति ( ; ; )
  {
    प्रति ( ; ; )
    {
      यदि (--अङ्कः_probes_वामः == 0) प्रत्यागम;
      #परिभाषय TDEFL_PROBE \
        अग्र_probe_pos = d->m_अग्र[probe_pos]; \
        यदि ((!अग्र_probe_pos) || ((dist = (mz_uint16)(lookahead_pos - अग्र_probe_pos)) > max_dist)) प्रत्यागम; \
        probe_pos = अग्र_probe_pos & TDEFL_LZ_DICT_आकार_आवरणम्; \
        यदि ((d->m_dict[probe_pos + मेलनम्_len] == c0) && (d->m_dict[probe_pos + मेलनम्_len - 1] == c1)) भङ्ग;
      TDEFL_PROBE
      TDEFL_PROBE
      TDEFL_PROBE
    }
    यदि (!dist) भङ्ग;
    p = s; q = d->m_dict + probe_pos;
    प्रति (probe_len = 0; probe_len < max_मेलनम्_len; probe_len++) {
        यदि (*p++ != *q++) भङ्ग;
    }
    यदि (probe_len > मेलनम्_len)
    {
      *p_मेलनम्_dist = dist;
      यदि ((*p_मेलनम्_len = मेलनम्_len = probe_len) == max_मेलनम्_len) प्रत्यागम;
      c0 = d->m_dict[pos + मेलनम्_len]; c1 = d->m_dict[pos + मेलनम्_len - 1];
    }
  }
}
#यदि_अन्तः // #if MINIZ_USE_UNALIGNED_LOADS_AND_STORES

#यदि MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
स्थिर mz_bool tdefl_compress_fast(tdefl_compressor *d)
{
  // Faster, minimally featured LZRW1-style match+parse loop with better register utilization. Intended for applications where raw throughput is valued more highly than ratio.
  mz_uint lookahead_pos = d->m_lookahead_pos, lookahead_आकार = d->m_lookahead_आकार, dict_आकार = d->m_dict_आकार, योग_lz_अष्टकानि = d->m_योग_lz_अष्टकानि, अङ्कः_flags_वामः = d->m_अङ्कः_flags_वामः;
  mz_uint8 *p_LZ_संहिता_buf = d->m_p_LZ_संहिता_buf, *pLZ_flags = d->m_pLZ_flags;
  mz_uint cur_pos = lookahead_pos & TDEFL_LZ_DICT_आकार_आवरणम्;

  यावत् ((d->m_src_buf_वामः) || ((d->m_flush) && (lookahead_आकार)))
  {
    ध्रुव mz_uint TDEFL_COMP_FAST_LOOKAHEAD_आकार = 4096;
    mz_uint dst_pos = (lookahead_pos + lookahead_आकार) & TDEFL_LZ_DICT_आकार_आवरणम्;
    mz_uint अङ्कः_अष्टकानि_गन्तव्यम्_process = (mz_uint)MZ_MIN(d->m_src_buf_वामः, TDEFL_COMP_FAST_LOOKAHEAD_आकार - lookahead_आकार);
    d->m_src_buf_वामः -= अङ्कः_अष्टकानि_गन्तव्यम्_process;
    lookahead_आकार += अङ्कः_अष्टकानि_गन्तव्यम्_process;

    यावत् (अङ्कः_अष्टकानि_गन्तव्यम्_process)
    {
      mz_uint32 n = MZ_MIN(TDEFL_LZ_DICT_आकार - dst_pos, अङ्कः_अष्टकानि_गन्तव्यम्_process);
      स्मृतिं_प्रतिलिख(d->m_dict + dst_pos, d->m_pSrc, n);
      यदि (dst_pos < (TDEFL_MAX_मेलनम्_LEN - 1))
        स्मृतिं_प्रतिलिख(d->m_dict + TDEFL_LZ_DICT_आकार + dst_pos, d->m_pSrc, MZ_MIN(n, (TDEFL_MAX_मेलनम्_LEN - 1) - dst_pos));
      d->m_pSrc += n;
      dst_pos = (dst_pos + n) & TDEFL_LZ_DICT_आकार_आवरणम्;
      अङ्कः_अष्टकानि_गन्तव्यम्_process -= n;
    }

    dict_आकार = MZ_MIN(TDEFL_LZ_DICT_आकार - lookahead_आकार, dict_आकार);
    यदि ((!d->m_flush) && (lookahead_आकार < TDEFL_COMP_FAST_LOOKAHEAD_आकार)) भङ्ग;

    यावत् (lookahead_आकार >= 4)
    {
      mz_uint cur_मेलनम्_dist, cur_मेलनम्_len = 1;
      mz_uint8 *pCur_dict = d->m_dict + cur_pos;
      mz_uint first_trigram = (*(ध्रुव mz_uint32 *)pCur_dict) & 0xFFFFFF;
      mz_uint hash = (first_trigram ^ (first_trigram >> (24 - (TDEFL_LZ_HASH_द्वयङ्काः - 8)))) & TDEFL_LEVEL1_HASH_आकार_आवरणम्;
      mz_uint probe_pos = d->m_hash[hash];
      d->m_hash[hash] = (mz_uint16)lookahead_pos;

      यदि (((cur_मेलनम्_dist = (mz_uint16)(lookahead_pos - probe_pos)) <= dict_आकार) && ((*(ध्रुव mz_uint32 *)(d->m_dict + (probe_pos &= TDEFL_LZ_DICT_आकार_आवरणम्)) & 0xFFFFFF) == first_trigram))
      {
        ध्रुव mz_uint16 *p = (ध्रुव mz_uint16 *)pCur_dict;
        ध्रुव mz_uint16 *q = (ध्रुव mz_uint16 *)(d->m_dict + probe_pos);
        mz_uint32 probe_len = 32;
        कुरु { } यावत् ( (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) && (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) &&
          (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) && (TDEFL_READ_UNALIGNED_WORD(++p) == TDEFL_READ_UNALIGNED_WORD(++q)) && (--probe_len > 0) );
        cur_मेलनम्_len = ((mz_uint)(p - (ध्रुव mz_uint16 *)pCur_dict) * 2) + (mz_uint)(*(ध्रुव mz_uint8 *)p == *(ध्रुव mz_uint8 *)q);
        यदि (!probe_len)
          cur_मेलनम्_len = cur_मेलनम्_dist ? TDEFL_MAX_मेलनम्_LEN : 0;

        यदि ((cur_मेलनम्_len < TDEFL_MIN_मेलनम्_LEN) || ((cur_मेलनम्_len == TDEFL_MIN_मेलनम्_LEN) && (cur_मेलनम्_dist >= 8U*1024U)))
        {
          cur_मेलनम्_len = 1;
          *p_LZ_संहिता_buf++ = (mz_uint8)first_trigram;
          *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
          d->m_huff_गणनम्[0][(mz_uint8)first_trigram]++;
        }
        अन्यथा
        {
          mz_uint32 s0, s1;
          cur_मेलनम्_len = MZ_MIN(cur_मेलनम्_len, lookahead_आकार);

          MZ_ASSERT((cur_मेलनम्_len >= TDEFL_MIN_मेलनम्_LEN) && (cur_मेलनम्_dist >= 1) && (cur_मेलनम्_dist <= TDEFL_LZ_DICT_आकार));

          cur_मेलनम्_dist--;

          p_LZ_संहिता_buf[0] = (mz_uint8)(cur_मेलनम्_len - TDEFL_MIN_मेलनम्_LEN);
          *(mz_uint16 *)(&p_LZ_संहिता_buf[1]) = (mz_uint16)cur_मेलनम्_dist;
          p_LZ_संहिता_buf += 3;
          *pLZ_flags = (mz_uint8)((*pLZ_flags >> 1) | 0x80);

          s0 = s_tdefl_small_dist_sym[cur_मेलनम्_dist & 511];
          s1 = s_tdefl_large_dist_sym[cur_मेलनम्_dist >> 8];
          d->m_huff_गणनम्[1][(cur_मेलनम्_dist < 512) ? s0 : s1]++;

          d->m_huff_गणनम्[0][s_tdefl_len_sym[cur_मेलनम्_len - TDEFL_MIN_मेलनम्_LEN]]++;
        }
      }
      अन्यथा
      {
        *p_LZ_संहिता_buf++ = (mz_uint8)first_trigram;
        *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
        d->m_huff_गणनम्[0][(mz_uint8)first_trigram]++;
      }

      यदि (--अङ्कः_flags_वामः == 0) { अङ्कः_flags_वामः = 8; pLZ_flags = p_LZ_संहिता_buf++; }

      योग_lz_अष्टकानि += cur_मेलनम्_len;
      lookahead_pos += cur_मेलनम्_len;
      dict_आकार = MZ_MIN(dict_आकार + cur_मेलनम्_len, TDEFL_LZ_DICT_आकार);
      cur_pos = (cur_pos + cur_मेलनम्_len) & TDEFL_LZ_DICT_आकार_आवरणम्;
      MZ_ASSERT(lookahead_आकार >= cur_मेलनम्_len);
      lookahead_आकार -= cur_मेलनम्_len;

      यदि (p_LZ_संहिता_buf > &d->m_lz_संहिता_buf[TDEFL_LZ_संहिता_BUF_आकार - 8])
      {
        पूर्णाङ्क n;
        d->m_lookahead_pos = lookahead_pos; d->m_lookahead_आकार = lookahead_आकार; d->m_dict_आकार = dict_आकार;
        d->m_योग_lz_अष्टकानि = योग_lz_अष्टकानि; d->m_p_LZ_संहिता_buf = p_LZ_संहिता_buf; d->m_pLZ_flags = pLZ_flags; d->m_अङ्कः_flags_वामः = अङ्कः_flags_वामः;
        यदि ((n = tdefl_flush_खण्डम्(d, 0)) != 0)
          प्रत्यागम (n < 0) ? MZ_FALSE : MZ_TRUE;
        योग_lz_अष्टकानि = d->m_योग_lz_अष्टकानि; p_LZ_संहिता_buf = d->m_p_LZ_संहिता_buf; pLZ_flags = d->m_pLZ_flags; अङ्कः_flags_वामः = d->m_अङ्कः_flags_वामः;
      }
    }

    यावत् (lookahead_आकार)
    {
      mz_uint8 lit = d->m_dict[cur_pos];

      योग_lz_अष्टकानि++;
      *p_LZ_संहिता_buf++ = lit;
      *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
      यदि (--अङ्कः_flags_वामः == 0) { अङ्कः_flags_वामः = 8; pLZ_flags = p_LZ_संहिता_buf++; }

      d->m_huff_गणनम्[0][lit]++;

      lookahead_pos++;
      dict_आकार = MZ_MIN(dict_आकार + 1, TDEFL_LZ_DICT_आकार);
      cur_pos = (cur_pos + 1) & TDEFL_LZ_DICT_आकार_आवरणम्;
      lookahead_आकार--;

      यदि (p_LZ_संहिता_buf > &d->m_lz_संहिता_buf[TDEFL_LZ_संहिता_BUF_आकार - 8])
      {
        पूर्णाङ्क n;
        d->m_lookahead_pos = lookahead_pos; d->m_lookahead_आकार = lookahead_आकार; d->m_dict_आकार = dict_आकार;
        d->m_योग_lz_अष्टकानि = योग_lz_अष्टकानि; d->m_p_LZ_संहिता_buf = p_LZ_संहिता_buf; d->m_pLZ_flags = pLZ_flags; d->m_अङ्कः_flags_वामः = अङ्कः_flags_वामः;
        यदि ((n = tdefl_flush_खण्डम्(d, 0)) != 0)
          प्रत्यागम (n < 0) ? MZ_FALSE : MZ_TRUE;
        योग_lz_अष्टकानि = d->m_योग_lz_अष्टकानि; p_LZ_संहिता_buf = d->m_p_LZ_संहिता_buf; pLZ_flags = d->m_pLZ_flags; अङ्कः_flags_वामः = d->m_अङ्कः_flags_वामः;
      }
    }
  }

  d->m_lookahead_pos = lookahead_pos; d->m_lookahead_आकार = lookahead_आकार; d->m_dict_आकार = dict_आकार;
  d->m_योग_lz_अष्टकानि = योग_lz_अष्टकानि; d->m_p_LZ_संहिता_buf = p_LZ_संहिता_buf; d->m_pLZ_flags = pLZ_flags; d->m_अङ्कः_flags_वामः = अङ्कः_flags_वामः;
  प्रत्यागम MZ_TRUE;
}
#यदि_अन्तः // MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN

स्थिर MZ_FORCEINLINE शून्य tdefl_लेखः_literal(tdefl_compressor *d, mz_uint8 lit)
{
  d->m_योग_lz_अष्टकानि++;
  *d->m_p_LZ_संहिता_buf++ = lit;
  *d->m_pLZ_flags = (mz_uint8)(*d->m_pLZ_flags >> 1); यदि (--d->m_अङ्कः_flags_वामः == 0) { d->m_अङ्कः_flags_वामः = 8; d->m_pLZ_flags = d->m_p_LZ_संहिता_buf++; }
  d->m_huff_गणनम्[0][lit]++;
}

स्थिर MZ_FORCEINLINE शून्य tdefl_लेखः_मेलनम्(tdefl_compressor *d, mz_uint मेलनम्_len, mz_uint मेलनम्_dist)
{
  mz_uint32 s0, s1;

  MZ_ASSERT((मेलनम्_len >= TDEFL_MIN_मेलनम्_LEN) && (मेलनम्_dist >= 1) && (मेलनम्_dist <= TDEFL_LZ_DICT_आकार));

  d->m_योग_lz_अष्टकानि += मेलनम्_len;

  d->m_p_LZ_संहिता_buf[0] = (mz_uint8)(मेलनम्_len - TDEFL_MIN_मेलनम्_LEN);

  मेलनम्_dist -= 1;
  d->m_p_LZ_संहिता_buf[1] = (mz_uint8)(मेलनम्_dist & 0xFF);
  d->m_p_LZ_संहिता_buf[2] = (mz_uint8)(मेलनम्_dist >> 8); d->m_p_LZ_संहिता_buf += 3;

  *d->m_pLZ_flags = (mz_uint8)((*d->m_pLZ_flags >> 1) | 0x80); यदि (--d->m_अङ्कः_flags_वामः == 0) { d->m_अङ्कः_flags_वामः = 8; d->m_pLZ_flags = d->m_p_LZ_संहिता_buf++; }

  s0 = s_tdefl_small_dist_sym[मेलनम्_dist & 511]; s1 = s_tdefl_large_dist_sym[(मेलनम्_dist >> 8) & 127];
  d->m_huff_गणनम्[1][(मेलनम्_dist < 512) ? s0 : s1]++;

  यदि (मेलनम्_len >= TDEFL_MIN_मेलनम्_LEN) d->m_huff_गणनम्[0][s_tdefl_len_sym[मेलनम्_len - TDEFL_MIN_मेलनम्_LEN]]++;
}

स्थिर mz_bool tdefl_compress_प्रसामान्यम्(tdefl_compressor *d)
{
  ध्रुव mz_uint8 *pSrc = d->m_pSrc; size_t src_buf_वामः = d->m_src_buf_वामः;
  tdefl_flush flush = d->m_flush;

  यावत् ((src_buf_वामः) || ((flush) && (d->m_lookahead_आकार)))
  {
    mz_uint len_गन्तव्यम्_move, cur_मेलनम्_dist, cur_मेलनम्_len, cur_pos;
    // Update dictionary and hash chains. Keeps the lookahead size equal to TDEFL_MAX_MATCH_LEN.
    यदि ((d->m_lookahead_आकार + d->m_dict_आकार) >= (TDEFL_MIN_मेलनम्_LEN - 1))
    {
      mz_uint dst_pos = (d->m_lookahead_pos + d->m_lookahead_आकार) & TDEFL_LZ_DICT_आकार_आवरणम्, ins_pos = d->m_lookahead_pos + d->m_lookahead_आकार - 2;
      mz_uint hash = (d->m_dict[ins_pos & TDEFL_LZ_DICT_आकार_आवरणम्] << TDEFL_LZ_HASH_सरणम्) ^ d->m_dict[(ins_pos + 1) & TDEFL_LZ_DICT_आकार_आवरणम्];
      mz_uint अङ्कः_अष्टकानि_गन्तव्यम्_process = (mz_uint)MZ_MIN(src_buf_वामः, TDEFL_MAX_मेलनम्_LEN - d->m_lookahead_आकार);
      ध्रुव mz_uint8 *p_Src_अन्तः = pSrc ? pSrc + अङ्कः_अष्टकानि_गन्तव्यम्_process : रिक्त;
      src_buf_वामः -= अङ्कः_अष्टकानि_गन्तव्यम्_process;
      d->m_lookahead_आकार += अङ्कः_अष्टकानि_गन्तव्यम्_process;
      यावत् (pSrc != p_Src_अन्तः)
      {
        mz_uint8 c = *pSrc++; d->m_dict[dst_pos] = c; यदि (dst_pos < (TDEFL_MAX_मेलनम्_LEN - 1)) d->m_dict[TDEFL_LZ_DICT_आकार + dst_pos] = c;
        hash = ((hash << TDEFL_LZ_HASH_सरणम्) ^ c) & (TDEFL_LZ_HASH_आकार - 1);
        d->m_अग्र[ins_pos & TDEFL_LZ_DICT_आकार_आवरणम्] = d->m_hash[hash]; d->m_hash[hash] = (mz_uint16)(ins_pos);
        dst_pos = (dst_pos + 1) & TDEFL_LZ_DICT_आकार_आवरणम्; ins_pos++;
      }
    }
    अन्यथा
    {
      यावत् ((src_buf_वामः) && (d->m_lookahead_आकार < TDEFL_MAX_मेलनम्_LEN))
      {
        mz_uint8 c = *pSrc++;
        mz_uint dst_pos = (d->m_lookahead_pos + d->m_lookahead_आकार) & TDEFL_LZ_DICT_आकार_आवरणम्;
        src_buf_वामः--;
        d->m_dict[dst_pos] = c;
        यदि (dst_pos < (TDEFL_MAX_मेलनम्_LEN - 1))
          d->m_dict[TDEFL_LZ_DICT_आकार + dst_pos] = c;
        यदि ((++d->m_lookahead_आकार + d->m_dict_आकार) >= TDEFL_MIN_मेलनम्_LEN)
        {
          mz_uint ins_pos = d->m_lookahead_pos + (d->m_lookahead_आकार - 1) - 2;
          mz_uint hash = ((d->m_dict[ins_pos & TDEFL_LZ_DICT_आकार_आवरणम्] << (TDEFL_LZ_HASH_सरणम् * 2)) ^ (d->m_dict[(ins_pos + 1) & TDEFL_LZ_DICT_आकार_आवरणम्] << TDEFL_LZ_HASH_सरणम्) ^ c) & (TDEFL_LZ_HASH_आकार - 1);
          d->m_अग्र[ins_pos & TDEFL_LZ_DICT_आकार_आवरणम्] = d->m_hash[hash]; d->m_hash[hash] = (mz_uint16)(ins_pos);
        }
      }
    }
    d->m_dict_आकार = MZ_MIN(TDEFL_LZ_DICT_आकार - d->m_lookahead_आकार, d->m_dict_आकार);
    यदि ((!flush) && (d->m_lookahead_आकार < TDEFL_MAX_मेलनम्_LEN))
      भङ्ग;

    // Simple lazy/greedy parsing state machine.
    len_गन्तव्यम्_move = 1; cur_मेलनम्_dist = 0; cur_मेलनम्_len = d->m_saved_मेलनम्_len ? d->m_saved_मेलनम्_len : (TDEFL_MIN_मेलनम्_LEN - 1); cur_pos = d->m_lookahead_pos & TDEFL_LZ_DICT_आकार_आवरणम्;
    यदि (d->m_flags & (TDEFL_RLE_MATCHES | TDEFL_FORCE_ALL_RAW_खण्डानि))
    {
      यदि ((d->m_dict_आकार) && (!(d->m_flags & TDEFL_FORCE_ALL_RAW_खण्डानि)))
      {
        mz_uint8 c = d->m_dict[(cur_pos - 1) & TDEFL_LZ_DICT_आकार_आवरणम्];
        cur_मेलनम्_len = 0; यावत् (cur_मेलनम्_len < d->m_lookahead_आकार) { यदि (d->m_dict[cur_pos + cur_मेलनम्_len] != c) भङ्ग; cur_मेलनम्_len++; }
        यदि (cur_मेलनम्_len < TDEFL_MIN_मेलनम्_LEN) cur_मेलनम्_len = 0; अन्यथा cur_मेलनम्_dist = 1;
      }
    }
    अन्यथा
    {
      tdefl_find_मेलनम्(d, d->m_lookahead_pos, d->m_dict_आकार, d->m_lookahead_आकार, &cur_मेलनम्_dist, &cur_मेलनम्_len);
    }
    यदि (((cur_मेलनम्_len == TDEFL_MIN_मेलनम्_LEN) && (cur_मेलनम्_dist >= 8U*1024U)) || (cur_pos == cur_मेलनम्_dist) || ((d->m_flags & TDEFL_FILTER_MATCHES) && (cur_मेलनम्_len <= 5)))
    {
      cur_मेलनम्_dist = cur_मेलनम्_len = 0;
    }
    यदि (d->m_saved_मेलनम्_len)
    {
      यदि (cur_मेलनम्_len > d->m_saved_मेलनम्_len)
      {
        tdefl_लेखः_literal(d, (mz_uint8)d->m_saved_lit);
        यदि (cur_मेलनम्_len >= 128)
        {
          tdefl_लेखः_मेलनम्(d, cur_मेलनम्_len, cur_मेलनम्_dist);
          d->m_saved_मेलनम्_len = 0; len_गन्तव्यम्_move = cur_मेलनम्_len;
        }
        अन्यथा
        {
          d->m_saved_lit = d->m_dict[cur_pos]; d->m_saved_मेलनम्_dist = cur_मेलनम्_dist; d->m_saved_मेलनम्_len = cur_मेलनम्_len;
        }
      }
      अन्यथा
      {
        tdefl_लेखः_मेलनम्(d, d->m_saved_मेलनम्_len, d->m_saved_मेलनम्_dist);
        len_गन्तव्यम्_move = d->m_saved_मेलनम्_len - 1; d->m_saved_मेलनम्_len = 0;
      }
    }
    अन्यथा यदि (!cur_मेलनम्_dist)
      tdefl_लेखः_literal(d, d->m_dict[MZ_MIN(cur_pos, परिमाण(d->m_dict) - 1)]);
    अन्यथा यदि ((d->m_greedy_parsing) || (d->m_flags & TDEFL_RLE_MATCHES) || (cur_मेलनम्_len >= 128))
    {
      tdefl_लेखः_मेलनम्(d, cur_मेलनम्_len, cur_मेलनम्_dist);
      len_गन्तव्यम्_move = cur_मेलनम्_len;
    }
    अन्यथा
    {
      d->m_saved_lit = d->m_dict[MZ_MIN(cur_pos, परिमाण(d->m_dict) - 1)]; d->m_saved_मेलनम्_dist = cur_मेलनम्_dist; d->m_saved_मेलनम्_len = cur_मेलनम्_len;
    }
    // Move the lookahead forward by len_to_move bytes.
    d->m_lookahead_pos += len_गन्तव्यम्_move;
    MZ_ASSERT(d->m_lookahead_आकार >= len_गन्तव्यम्_move);
    d->m_lookahead_आकार -= len_गन्तव्यम्_move;
    d->m_dict_आकार = MZ_MIN(d->m_dict_आकार + len_गन्तव्यम्_move, TDEFL_LZ_DICT_आकार);
    // Check if it's time to flush the current LZ codes to the internal output buffer.
    यदि ( (d->m_p_LZ_संहिता_buf > &d->m_lz_संहिता_buf[TDEFL_LZ_संहिता_BUF_आकार - 8]) ||
         ( (d->m_योग_lz_अष्टकानि > 31*1024) && (((((mz_uint)(d->m_p_LZ_संहिता_buf - d->m_lz_संहिता_buf) * 115) >> 7) >= d->m_योग_lz_अष्टकानि) || (d->m_flags & TDEFL_FORCE_ALL_RAW_खण्डानि))) )
    {
      पूर्णाङ्क n;
      d->m_pSrc = pSrc; d->m_src_buf_वामः = src_buf_वामः;
      यदि ((n = tdefl_flush_खण्डम्(d, 0)) != 0)
        प्रत्यागम (n < 0) ? MZ_FALSE : MZ_TRUE;
    }
  }

  d->m_pSrc = pSrc; d->m_src_buf_वामः = src_buf_वामः;
  प्रत्यागम MZ_TRUE;
}

स्थिर tdefl_स्थितिः tdefl_flush_output_बफर(tdefl_compressor *d)
{
  यदि (d->m_p_अन्तर्_buf_आकार)
  {
    *d->m_p_अन्तर्_buf_आकार = d->m_pSrc - (ध्रुव mz_uint8 *)d->m_p_अन्तर्_buf;
  }

  यदि (d->m_p_बहिर्गमनम्_buf_आकार)
  {
    size_t n = MZ_MIN(*d->m_p_बहिर्गमनम्_buf_आकार - d->m_बहिर्गमनम्_buf_ofs, d->m_output_flush_remaining);
    स्मृतिं_प्रतिलिख((mz_uint8 *)d->m_p_बहिर्गमनम्_buf + d->m_बहिर्गमनम्_buf_ofs, d->m_output_buf + d->m_output_flush_ofs, n);
    d->m_output_flush_ofs += (mz_uint)n;
    d->m_output_flush_remaining -= (mz_uint)n;
    d->m_बहिर्गमनम्_buf_ofs += n;

    *d->m_p_बहिर्गमनम्_buf_आकार = d->m_बहिर्गमनम्_buf_ofs;
  }

  प्रत्यागम (d->m_परिसमाप्तम् && !d->m_output_flush_remaining) ? TDEFL_स्थितिः_समाप्तम् : TDEFL_स्थितिः_OKAY;
}

tdefl_स्थितिः tdefl_compress(tdefl_compressor *d, ध्रुव शून्य *p_अन्तर्_buf, size_t *p_अन्तर्_buf_आकार, शून्य *p_बहिर्गमनम्_buf, size_t *p_बहिर्गमनम्_buf_आकार, tdefl_flush flush)
{
  यदि (!d)
  {
    यदि (p_अन्तर्_buf_आकार) *p_अन्तर्_buf_आकार = 0;
    यदि (p_बहिर्गमनम्_buf_आकार) *p_बहिर्गमनम्_buf_आकार = 0;
    प्रत्यागम TDEFL_स्थितिः_BAD_PARAM;
  }

  d->m_p_अन्तर्_buf = p_अन्तर्_buf; d->m_p_अन्तर्_buf_आकार = p_अन्तर्_buf_आकार;
  d->m_p_बहिर्गमनम्_buf = p_बहिर्गमनम्_buf; d->m_p_बहिर्गमनम्_buf_आकार = p_बहिर्गमनम्_buf_आकार;
  d->m_pSrc = (ध्रुव mz_uint8 *)(p_अन्तर्_buf); d->m_src_buf_वामः = p_अन्तर्_buf_आकार ? *p_अन्तर्_buf_आकार : 0;
  d->m_बहिर्गमनम्_buf_ofs = 0;
  d->m_flush = flush;

  यदि ( ((d->m_pPut_buf_func != रिक्त) == ((p_बहिर्गमनम्_buf != रिक्त) || (p_बहिर्गमनम्_buf_आकार != रिक्त))) || (d->m_पूर्व_return_स्थितिः != TDEFL_स्थितिः_OKAY) ||
        (d->m_इच्छति_गन्तव्यम्_finish && (flush != TDEFL_FINISH)) || (p_अन्तर्_buf_आकार && *p_अन्तर्_buf_आकार && !p_अन्तर्_buf) || (p_बहिर्गमनम्_buf_आकार && *p_बहिर्गमनम्_buf_आकार && !p_बहिर्गमनम्_buf) )
  {
    यदि (p_अन्तर्_buf_आकार) *p_अन्तर्_buf_आकार = 0;
    यदि (p_बहिर्गमनम्_buf_आकार) *p_बहिर्गमनम्_buf_आकार = 0;
    प्रत्यागम (d->m_पूर्व_return_स्थितिः = TDEFL_स्थितिः_BAD_PARAM);
  }
  d->m_इच्छति_गन्तव्यम्_finish |= (flush == TDEFL_FINISH);

  यदि ((d->m_output_flush_remaining) || (d->m_परिसमाप्तम्))
    प्रत्यागम (d->m_पूर्व_return_स्थितिः = tdefl_flush_output_बफर(d));

#यदि MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  यदि (((d->m_flags & TDEFL_MAX_PROBES_आवरणम्) == 1) &&
      ((d->m_flags & TDEFL_GREEDY_PARSING_FLAG) != 0) &&
      ((d->m_flags & (TDEFL_FILTER_MATCHES | TDEFL_FORCE_ALL_RAW_खण्डानि | TDEFL_RLE_MATCHES)) == 0))
  {
    यदि (!tdefl_compress_fast(d))
      प्रत्यागम d->m_पूर्व_return_स्थितिः;
  }
  अन्यथा
#यदि_अन्तः // #if MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  {
    यदि (!tdefl_compress_प्रसामान्यम्(d))
      प्रत्यागम d->m_पूर्व_return_स्थितिः;
  }

  यदि ((d->m_flags & (TDEFL_WRITE_ZLIB_शीर्षकम् | TDEFL_COMPUTE_ADLER32)) && (p_अन्तर्_buf))
    d->m_adler32 = (mz_uint32)mz_adler32(d->m_adler32, (ध्रुव mz_uint8 *)p_अन्तर्_buf, d->m_pSrc - (ध्रुव mz_uint8 *)p_अन्तर्_buf);

  यदि ((flush) && (!d->m_lookahead_आकार) && (!d->m_src_buf_वामः) && (!d->m_output_flush_remaining))
  {
    यदि (tdefl_flush_खण्डम्(d, flush) < 0)
      प्रत्यागम d->m_पूर्व_return_स्थितिः;
    d->m_परिसमाप्तम् = (flush == TDEFL_FINISH);
    यदि (flush == TDEFL_पूर्णम्_FLUSH) { MZ_CLEAR_ARR(d->m_hash); MZ_CLEAR_ARR(d->m_अग्र); d->m_dict_आकार = 0; }
  }

  प्रत्यागम (d->m_पूर्व_return_स्थितिः = tdefl_flush_output_बफर(d));
}

tdefl_स्थितिः tdefl_compress_बफर(tdefl_compressor *d, ध्रुव शून्य *p_अन्तर्_buf, size_t अन्तर्_buf_आकार, tdefl_flush flush)
{
  MZ_ASSERT(d->m_pPut_buf_func); प्रत्यागम tdefl_compress(d, p_अन्तर्_buf, &अन्तर्_buf_आकार, रिक्त, रिक्त, flush);
}

tdefl_स्थितिः tdefl_init(tdefl_compressor *d, tdefl_put_buf_func_ptr pPut_buf_func, शून्य *pPut_buf_user, पूर्णाङ्क flags)
{
  d->m_pPut_buf_func = pPut_buf_func; d->m_pPut_buf_user = pPut_buf_user;
  d->m_flags = (mz_uint)(flags); d->m_max_probes[0] = 1 + ((flags & 0xFFF) + 2) / 3; d->m_greedy_parsing = (flags & TDEFL_GREEDY_PARSING_FLAG) != 0;
  d->m_max_probes[1] = 1 + (((flags & 0xFFF) >> 2) + 2) / 3;
  यदि (!(flags & TDEFL_NONDETERMINISTIC_PARSING_FLAG)) MZ_CLEAR_ARR(d->m_hash);
  d->m_lookahead_pos = d->m_lookahead_आकार = d->m_dict_आकार = d->m_योग_lz_अष्टकानि = d->m_lz_संहिता_buf_dict_pos = d->m_द्वयङ्काः_अन्तर् = 0;
  d->m_output_flush_ofs = d->m_output_flush_remaining = d->m_परिसमाप्तम् = d->m_खण्डम्_सूचकांक = d->m_bit_बफर = d->m_इच्छति_गन्तव्यम्_finish = 0;
  d->m_p_LZ_संहिता_buf = d->m_lz_संहिता_buf + 1; d->m_pLZ_flags = d->m_lz_संहिता_buf; d->m_अङ्कः_flags_वामः = 8;
  d->m_pOutput_buf = d->m_output_buf; d->m_p_Output_buf_अन्तः = d->m_output_buf; d->m_पूर्व_return_स्थितिः = TDEFL_स्थितिः_OKAY;
  d->m_saved_मेलनम्_dist = d->m_saved_मेलनम्_len = d->m_saved_lit = 0; d->m_adler32 = 1;
  d->m_p_अन्तर्_buf = रिक्त; d->m_p_बहिर्गमनम्_buf = रिक्त;
  d->m_p_अन्तर्_buf_आकार = रिक्त; d->m_p_बहिर्गमनम्_buf_आकार = रिक्त;
  d->m_flush = TDEFL_NO_FLUSH; d->m_pSrc = रिक्त; d->m_src_buf_वामः = 0; d->m_बहिर्गमनम्_buf_ofs = 0;
  स्मृतिं_पूरय(&d->m_huff_गणनम्[0][0], 0, परिमाण(d->m_huff_गणनम्[0][0]) * TDEFL_MAX_HUFF_SYMBOLS_0);
  स्मृतिं_पूरय(&d->m_huff_गणनम्[1][0], 0, परिमाण(d->m_huff_गणनम्[1][0]) * TDEFL_MAX_HUFF_SYMBOLS_1);
  प्रत्यागम TDEFL_स्थितिः_OKAY;
}

#यदि_अपरिभाषितम् MINIZ_SDL_NOUNUSED
tdefl_स्थितिः tdefl_get_पूर्व_return_स्थितिः(tdefl_compressor *d)
{
  प्रत्यागम d->m_पूर्व_return_स्थितिः;
}

mz_uint32 tdefl_get_adler32(tdefl_compressor *d)
{
  प्रत्यागम d->m_adler32;
}

mz_bool tdefl_compress_mem_गन्तव्यम्_output(ध्रुव शून्य *pBuf, size_t buf_len, tdefl_put_buf_func_ptr pPut_buf_func, शून्य *pPut_buf_user, पूर्णाङ्क flags)
{
  tdefl_compressor *pComp; mz_bool succeeded; यदि (((buf_len) && (!pBuf)) || (!pPut_buf_func)) प्रत्यागम MZ_FALSE;
  pComp = (tdefl_compressor*)MZ_MALLOC(परिमाण(tdefl_compressor)); यदि (!pComp) प्रत्यागम MZ_FALSE;
  succeeded = (tdefl_init(pComp, pPut_buf_func, pPut_buf_user, flags) == TDEFL_स्थितिः_OKAY);
  succeeded = succeeded && (tdefl_compress_बफर(pComp, pBuf, buf_len, TDEFL_FINISH) == TDEFL_स्थितिः_समाप्तम्);
  MZ_FREE(pComp); प्रत्यागम succeeded;
}
#यदि_अन्तः /* MINIZ_SDL_NOUNUSED */

प्रकारनिर्देश संरचना
{
  size_t m_आकार, m_क्षमता;
  mz_uint8 *m_pBuf;
  mz_bool m_expandable;
} tdefl_output_बफर;

स्थिर mz_bool tdefl_output_बफर_putter(ध्रुव शून्य *pBuf, पूर्णाङ्क len, शून्य *pUser)
{
  tdefl_output_बफर *p = (tdefl_output_बफर *)pUser;
  size_t new_आकार = p->m_आकार + len;
  यदि (new_आकार > p->m_क्षमता)
  {
    size_t new_क्षमता = p->m_क्षमता; mz_uint8 *pNew_buf; यदि (!p->m_expandable) प्रत्यागम MZ_FALSE;
    कुरु { new_क्षमता = MZ_MAX(128U, new_क्षमता << 1U); } यावत् (new_आकार > new_क्षमता);
    pNew_buf = (mz_uint8*)MZ_REALLOC(p->m_pBuf, new_क्षमता); यदि (!pNew_buf) प्रत्यागम MZ_FALSE;
    p->m_pBuf = pNew_buf; p->m_क्षमता = new_क्षमता;
  }
  स्मृतिं_प्रतिलिख((mz_uint8*)p->m_pBuf + p->m_आकार, pBuf, len); p->m_आकार = new_आकार;
  प्रत्यागम MZ_TRUE;
}

#यदि_अपरिभाषितम् MINIZ_SDL_NOUNUSED
शून्य *tdefl_compress_mem_गन्तव्यम्_heap(ध्रुव शून्य *pSrc_buf, size_t src_buf_len, size_t *p_बहिर्गमनम्_len, पूर्णाङ्क flags)
{
  tdefl_output_बफर बहिर्गमनम्_buf; MZ_CLEAR_OBJ(बहिर्गमनम्_buf);
  यदि (!p_बहिर्गमनम्_len) प्रत्यागम MZ_FALSE; अन्यथा *p_बहिर्गमनम्_len = 0;
  बहिर्गमनम्_buf.m_expandable = MZ_TRUE;
  यदि (!tdefl_compress_mem_गन्तव्यम्_output(pSrc_buf, src_buf_len, tdefl_output_बफर_putter, &बहिर्गमनम्_buf, flags)) प्रत्यागम रिक्त;
  *p_बहिर्गमनम्_len = बहिर्गमनम्_buf.m_आकार; प्रत्यागम बहिर्गमनम्_buf.m_pBuf;
}

size_t tdefl_compress_mem_गन्तव्यम्_mem(शून्य *p_बहिर्गमनम्_buf, size_t बहिर्गमनम्_buf_len, ध्रुव शून्य *pSrc_buf, size_t src_buf_len, पूर्णाङ्क flags)
{
  tdefl_output_बफर बहिर्गमनम्_buf; MZ_CLEAR_OBJ(बहिर्गमनम्_buf);
  यदि (!p_बहिर्गमनम्_buf) प्रत्यागम 0;
  बहिर्गमनम्_buf.m_pBuf = (mz_uint8*)p_बहिर्गमनम्_buf; बहिर्गमनम्_buf.m_क्षमता = बहिर्गमनम्_buf_len;
  यदि (!tdefl_compress_mem_गन्तव्यम्_output(pSrc_buf, src_buf_len, tdefl_output_बफर_putter, &बहिर्गमनम्_buf, flags)) प्रत्यागम 0;
  प्रत्यागम बहिर्गमनम्_buf.m_आकार;
}
#यदि_अन्तः /* MINIZ_SDL_NOUNUSED */

#यदि_अपरिभाषितम् MINIZ_NO_ZLIB_APIS
स्थिर ध्रुव mz_uint s_tdefl_अङ्कः_probes[11] = { 0, 1, 6, 32,  16, 32, 128, 256,  512, 768, 1500 };

// level may actually range from [0,10] (10 is a "hidden" max level, where we want a bit more compression and it's fine if throughput to fall off a cliff on some files).
mz_uint tdefl_create_comp_flags_from_zip_params(पूर्णाङ्क level, पूर्णाङ्क गवाक्षः_द्वयङ्काः, पूर्णाङ्क strategy)
{
  mz_uint comp_flags = s_tdefl_अङ्कः_probes[(level >= 0) ? MZ_MIN(10, level) : MZ_DEFAULT_LEVEL] | ((level <= 3) ? TDEFL_GREEDY_PARSING_FLAG : 0);
  यदि (गवाक्षः_द्वयङ्काः > 0) comp_flags |= TDEFL_WRITE_ZLIB_शीर्षकम्;

  यदि (!level) comp_flags |= TDEFL_FORCE_ALL_RAW_खण्डानि;
  अन्यथा यदि (strategy == MZ_FILTERED) comp_flags |= TDEFL_FILTER_MATCHES;
  अन्यथा यदि (strategy == MZ_HUFFMAN_ONLY) comp_flags &= ~TDEFL_MAX_PROBES_आवरणम्;
  अन्यथा यदि (strategy == MZ_FIXED) comp_flags |= TDEFL_FORCE_ALL_STATIC_खण्डानि;
  अन्यथा यदि (strategy == MZ_RLE) comp_flags |= TDEFL_RLE_MATCHES;

  प्रत्यागम comp_flags;
}
#यदि_अन्तः //MINIZ_NO_ZLIB_APIS

#यदि_परिभाषितम् _MSC_VER
#निर्देशः warning (प्रक्षिप)
#निर्देशः warning (disable:4204) // nonstandard extension used : non-constant aggregate initializer (also supported by GNU C and C99, so no big deal)
#यदि_अन्तः

// Simple PNG writer function by Alex Evans, 2011. Released into the public domain: https://gist.github.com/908299, more context at
// http://altdevblogaday.org/2011/04/06/a-smaller-jpg-encoder/.
// This is actually a modification of Alex's original code so PNG files generated by this function pass pngcheck.
MINIZ_STATIC शून्य *tdefl_write_image_गन्तव्यम्_png_file_अन्तर्_स्मृतिः_ex(ध्रुव शून्य *pImage, पूर्णाङ्क w, पूर्णाङ्क h, पूर्णाङ्क अङ्कः_chans, पूर्णाङ्क bpl, size_t *p_Len_बहिर्गमनम्, mz_uint level, mz_bool flip, mz_uint8 *plte, पूर्णाङ्क plte_आकार, mz_uint8 *trns, पूर्णाङ्क trns_आकार)
{
  // Using a local copy of this array here in case MINIZ_NO_ZLIB_APIS was defined.
  स्थिर ध्रुव mz_uint s_tdefl_png_अङ्कः_probes[11] = { 0, 1, 6, 32,  16, 32, 128, 256,  512, 768, 1500 };
  tdefl_compressor *pComp = (tdefl_compressor *)MZ_MALLOC(परिमाण(tdefl_compressor)); tdefl_output_बफर बहिर्गमनम्_buf; पूर्णाङ्क i, y, z = 0; mz_uint32 c; *p_Len_बहिर्गमनम् = 0; size_t दत्त_start, दत्त_आकार_3;
  यदि (!pComp) प्रत्यागम रिक्त;
  MZ_CLEAR_OBJ(बहिर्गमनम्_buf); बहिर्गमनम्_buf.m_expandable = MZ_TRUE;
  बहिर्गमनम्_buf.m_क्षमता = 57+MZ_MAX(64, (1+w*अङ्कः_chans)*h);
  यदि (plte_आकार > 0)
    बहिर्गमनम्_buf.m_क्षमता += 12+plte_आकार;
  यदि (trns_आकार > 0)
    बहिर्गमनम्_buf.m_क्षमता += 12+trns_आकार;
  यदि (रिक्त == (बहिर्गमनम्_buf.m_pBuf = (mz_uint8*)MZ_MALLOC(बहिर्गमनम्_buf.m_क्षमता))) { MZ_FREE(pComp); प्रत्यागम रिक्त; }
  // write header
  {
    स्थिर ध्रुव mz_uint8 chans[] = {0x00, 0x00, 0x04, 0x02, 0x06};

    mz_uint8 pnghdr[33]={ 0x89,0x50,0x4e,0x47,0x0d,0x0a,0x1a,0x0a,
                          0x00,0x00,0x00,0x0d,0x49,0x48,0x44,0x52,
                          0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                          0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

    pnghdr[18] = (mz_uint8)(w>>8);
    pnghdr[19] = (mz_uint8)(w>>0);

    pnghdr[22] = (mz_uint8)(h>>8);
    pnghdr[23] = (mz_uint8)(h>>0);

    यदि (अङ्कः_chans == 1 && plte_आकार > 0)
      pnghdr[25] = 3;
    अन्यथा
      pnghdr[25] = (chans[अङ्कः_chans]);

    c = (mz_uint32)mz_चक्रीयपरीक्षा_32(MZ_चक्रीयपरीक्षा_32_INIT,pnghdr+12,17);
    प्रति (i=0; i<4; ++i, c<<=8) ((mz_uint8*)(pnghdr+29))[i] = (mz_uint8)(c>>24);
    यदि (!tdefl_output_बफर_putter(pnghdr, परिमाण(pnghdr), &बहिर्गमनम्_buf)) { *p_Len_बहिर्गमनम् = 0; MZ_FREE(pComp); MZ_FREE(बहिर्गमनम्_buf.m_pBuf); प्रत्यागम रिक्त; }
  }
  // write PLTE chunk
  यदि (plte_आकार > 0)
  {
    mz_uint8 hdr[8]={0x00,0x00,0x00,0x00,0x50,0x4c,0x54,0x45};

    hdr[0] = (mz_uint8)(plte_आकार>>24);
    hdr[1] = (mz_uint8)(plte_आकार>>16);
    hdr[2] = (mz_uint8)(plte_आकार>> 8);
    hdr[3] = (mz_uint8)(plte_आकार>> 0);
    यदि (!tdefl_output_बफर_putter(hdr, परिमाण(hdr), &बहिर्गमनम्_buf)) { *p_Len_बहिर्गमनम् = 0; MZ_FREE(pComp); MZ_FREE(बहिर्गमनम्_buf.m_pBuf); प्रत्यागम रिक्त; }
    दत्त_start = बहिर्गमनम्_buf.m_आकार;
    यदि (!tdefl_output_बफर_putter(plte, plte_आकार, &बहिर्गमनम्_buf)) { *p_Len_बहिर्गमनम् = 0; MZ_FREE(pComp); MZ_FREE(बहिर्गमनम्_buf.m_pBuf); प्रत्यागम रिक्त; }
    यदि (!tdefl_output_बफर_putter("\0\0\0\0", 4, &बहिर्गमनम्_buf)) { *p_Len_बहिर्गमनम् = 0; MZ_FREE(pComp); MZ_FREE(बहिर्गमनम्_buf.m_pBuf); प्रत्यागम रिक्त; }
    c = (mz_uint32)mz_चक्रीयपरीक्षा_32(MZ_चक्रीयपरीक्षा_32_INIT,बहिर्गमनम्_buf.m_pBuf+दत्त_start-4, plte_आकार+4);
    प्रति (i=0; i<4; ++i, c<<=8) (बहिर्गमनम्_buf.m_pBuf+बहिर्गमनम्_buf.m_आकार-4)[i] = (mz_uint8)(c >> 24);
  }
  // write tRNS chunk
  यदि (trns_आकार > 0)
  {
    mz_uint8 hdr[8]={0x00,0x00,0x00,0x00,0x74,0x52,0x4E,0x53};

    hdr[0] = (mz_uint8)(trns_आकार>>24);
    hdr[1] = (mz_uint8)(trns_आकार>>16);
    hdr[2] = (mz_uint8)(trns_आकार>> 8);
    hdr[3] = (mz_uint8)(trns_आकार>> 0);
    यदि (!tdefl_output_बफर_putter(hdr, परिमाण(hdr), &बहिर्गमनम्_buf)) { *p_Len_बहिर्गमनम् = 0; MZ_FREE(pComp); MZ_FREE(बहिर्गमनम्_buf.m_pBuf); प्रत्यागम रिक्त; }
    दत्त_start = बहिर्गमनम्_buf.m_आकार;
    यदि (!tdefl_output_बफर_putter(trns, trns_आकार, &बहिर्गमनम्_buf)) { *p_Len_बहिर्गमनम् = 0; MZ_FREE(pComp); MZ_FREE(बहिर्गमनम्_buf.m_pBuf); प्रत्यागम रिक्त; }
    यदि (!tdefl_output_बफर_putter("\0\0\0\0", 4, &बहिर्गमनम्_buf)) { *p_Len_बहिर्गमनम् = 0; MZ_FREE(pComp); MZ_FREE(बहिर्गमनम्_buf.m_pBuf); प्रत्यागम रिक्त; }
    c = (mz_uint32)mz_चक्रीयपरीक्षा_32(MZ_चक्रीयपरीक्षा_32_INIT,बहिर्गमनम्_buf.m_pBuf+दत्त_start-4, trns_आकार+4);
    प्रति (i=0; i<4; ++i, c<<=8) (बहिर्गमनम्_buf.m_pBuf+बहिर्गमनम्_buf.m_आकार-4)[i] = (mz_uint8)(c >> 24);
  }
  // write IDAT chunk
  यदि (!tdefl_output_बफर_putter("\0\0\0\0\x49\x44\x41\x54", 8, &बहिर्गमनम्_buf)) { *p_Len_बहिर्गमनम् = 0; MZ_FREE(pComp); MZ_FREE(बहिर्गमनम्_buf.m_pBuf); प्रत्यागम रिक्त; }
  दत्त_start = बहिर्गमनम्_buf.m_आकार;
  // compress image data
  tdefl_init(pComp, tdefl_output_बफर_putter, &बहिर्गमनम्_buf, s_tdefl_png_अङ्कः_probes[MZ_MIN(10, level)] | TDEFL_WRITE_ZLIB_शीर्षकम्);
  प्रति (y = 0; y < h; ++y) { tdefl_compress_बफर(pComp, &z, 1, TDEFL_NO_FLUSH); tdefl_compress_बफर(pComp, (mz_uint8*)pImage + (flip ? (h - 1 - y) : y) * bpl, w * अङ्कः_chans, TDEFL_NO_FLUSH); }
  यदि (tdefl_compress_बफर(pComp, रिक्त, 0, TDEFL_FINISH) != TDEFL_स्थितिः_समाप्तम्) { MZ_FREE(pComp); MZ_FREE(बहिर्गमनम्_buf.m_pBuf); प्रत्यागम रिक्त; }
  // write IDAT size
  दत्त_आकार_3 = बहिर्गमनम्_buf.m_आकार-दत्त_start;
  (बहिर्गमनम्_buf.m_pBuf+दत्त_start-8)[0] = (mz_uint8)(दत्त_आकार_3>>24);
  (बहिर्गमनम्_buf.m_pBuf+दत्त_start-8)[1] = (mz_uint8)(दत्त_आकार_3>>16);
  (बहिर्गमनम्_buf.m_pBuf+दत्त_start-8)[2] = (mz_uint8)(दत्त_आकार_3>> 8);
  (बहिर्गमनम्_buf.m_pBuf+दत्त_start-8)[3] = (mz_uint8)(दत्त_आकार_3>> 0);
  // write footer (IDAT CRC-32, followed by IEND chunk)
  यदि (!tdefl_output_बफर_putter("\0\0\0\0\0\0\0\0\x49\x45\x4e\x44\xae\x42\x60\x82", 16, &बहिर्गमनम्_buf)) { *p_Len_बहिर्गमनम् = 0; MZ_FREE(pComp); MZ_FREE(बहिर्गमनम्_buf.m_pBuf); प्रत्यागम रिक्त; }
  c = (mz_uint32)mz_चक्रीयपरीक्षा_32(MZ_चक्रीयपरीक्षा_32_INIT,बहिर्गमनम्_buf.m_pBuf+दत्त_start-4, दत्त_आकार_3+4);
  प्रति (i=0; i<4; ++i, c<<=8) (बहिर्गमनम्_buf.m_pBuf+बहिर्गमनम्_buf.m_आकार-16)[i] = (mz_uint8)(c >> 24);
  // compute final size of file, grab compressed data buffer and return
  *p_Len_बहिर्गमनम् = बहिर्गमनम्_buf.m_आकार;
  MZ_FREE(pComp);
  प्रत्यागम बहिर्गमनम्_buf.m_pBuf;
}
#यदि_अपरिभाषितम् MINIZ_SDL_NOUNUSED
MINIZ_STATIC शून्य *tdefl_write_image_गन्तव्यम्_png_file_अन्तर्_स्मृतिः(ध्रुव शून्य *pImage, पूर्णाङ्क w, पूर्णाङ्क h, पूर्णाङ्क अङ्कः_chans, पूर्णाङ्क bpl, size_t *p_Len_बहिर्गमनम्)
{
  // Level 6 corresponds to TDEFL_DEFAULT_MAX_PROBES or MZ_DEFAULT_LEVEL (but we can't depend on MZ_DEFAULT_LEVEL being available in case the zlib API's where #defined out)
  प्रत्यागम tdefl_write_image_गन्तव्यम्_png_file_अन्तर्_स्मृतिः_ex(pImage, w, h, अङ्कः_chans, bpl, p_Len_बहिर्गमनम्, 6, MZ_FALSE, रिक्त, 0, रिक्त, 0);
}
#यदि_अन्तः

#यदि_परिभाषितम् _MSC_VER
#निर्देशः warning (निष्कासय)
#यदि_अन्तः
#यदि_अन्तः /*#ifndef MINIZ_NO_DEFLATE_APIS*/

// ------------------- .ZIP archive reading

#यदि_अपरिभाषितम् MINIZ_NO_ARCHIVE_APIS

#यदि_परिभाषितम् MINIZ_NO_STDIO
  #परिभाषय MZ_FILE शून्य *
#अन्यथा
  #अन्तर्भाव <stdio.h>
  #अन्तर्भाव <sys/stat.h>

  #यदि defined(_MSC_VER) || defined(__MINGW64__)
    स्थिर FILE *mz_fopen(ध्रुव वर्ण *pFilename, ध्रुव वर्ण *p_बहुलकम्)
    {
      FILE* pFile = रिक्त;
      fopen_s(&pFile, pFilename, p_बहुलकम्);
      प्रत्यागम pFile;
    }
    स्थिर FILE *mz_freopen(ध्रुव वर्ण *p_मार्गः, ध्रुव वर्ण *p_बहुलकम्, FILE *p_प्रवाहः)
    {
      FILE* pFile = रिक्त;
      यदि (freopen_s(&pFile, p_मार्गः, p_बहुलकम्, p_प्रवाहः))
        प्रत्यागम रिक्त;
      प्रत्यागम pFile;
    }
    #यदि_अपरिभाषितम् MINIZ_NO_TIME
      #अन्तर्भाव <sys/utime.h>
    #यदि_अन्तः
    #परिभाषय MZ_FILE FILE
    #परिभाषय MZ_FOPEN mz_fopen
    #परिभाषय MZ_FCLOSE fclose
    #परिभाषय MZ_FREAD fread
    #परिभाषय MZ_FWRITE fwrite
    #परिभाषय MZ_FTELL64 _ftelli64
    #परिभाषय MZ_FSEEK64 _fseeki64
    #परिभाषय MZ_FILE_STAT_STRUCT _stat
    #परिभाषय MZ_FILE_STAT _stat
    #परिभाषय MZ_FFLUSH fflush
    #परिभाषय MZ_FREOPEN mz_freopen
    #परिभाषय MZ_DELETE_FILE remove
  #नोचेद्यदि defined(__MINGW32__)
    #यदि_अपरिभाषितम् MINIZ_NO_TIME
      #अन्तर्भाव <sys/utime.h>
    #यदि_अन्तः
    #परिभाषय MZ_FILE FILE
    #परिभाषय MZ_FOPEN(f, m) fopen(f, m)
    #परिभाषय MZ_FCLOSE fclose
    #परिभाषय MZ_FREAD fread
    #परिभाषय MZ_FWRITE fwrite
    #परिभाषय MZ_FTELL64 ftello64
    #परिभाषय MZ_FSEEK64 fseeko64
    #परिभाषय MZ_FILE_STAT_STRUCT _stat
    #परिभाषय MZ_FILE_STAT _stat
    #परिभाषय MZ_FFLUSH fflush
    #परिभाषय MZ_FREOPEN(f, m, s) freopen(f, m, s)
    #परिभाषय MZ_DELETE_FILE remove
  #नोचेद्यदि defined(__TINYC__)
    #यदि_अपरिभाषितम् MINIZ_NO_TIME
      #अन्तर्भाव <sys/utime.h>
    #यदि_अन्तः
    #परिभाषय MZ_FILE FILE
    #परिभाषय MZ_FOPEN(f, m) fopen(f, m)
    #परिभाषय MZ_FCLOSE fclose
    #परिभाषय MZ_FREAD fread
    #परिभाषय MZ_FWRITE fwrite
    #परिभाषय MZ_FTELL64 ftell
    #परिभाषय MZ_FSEEK64 fseek
    #परिभाषय MZ_FILE_STAT_STRUCT stat
    #परिभाषय MZ_FILE_STAT stat
    #परिभाषय MZ_FFLUSH fflush
    #परिभाषय MZ_FREOPEN(f, m, s) freopen(f, m, s)
    #परिभाषय MZ_DELETE_FILE remove
  #नोचेद्यदि defined(__GNUC__) && _LARGEFILE64_SOURCE
    #यदि_अपरिभाषितम् MINIZ_NO_TIME
      #अन्तर्भाव <utime.h>
    #यदि_अन्तः
    #परिभाषय MZ_FILE FILE
    #परिभाषय MZ_FOPEN(f, m) fopen64(f, m)
    #परिभाषय MZ_FCLOSE fclose
    #परिभाषय MZ_FREAD fread
    #परिभाषय MZ_FWRITE fwrite
    #परिभाषय MZ_FTELL64 ftello64
    #परिभाषय MZ_FSEEK64 fseeko64
    #परिभाषय MZ_FILE_STAT_STRUCT stat64
    #परिभाषय MZ_FILE_STAT stat64
    #परिभाषय MZ_FFLUSH fflush
    #परिभाषय MZ_FREOPEN(p, m, s) freopen64(p, m, s)
    #परिभाषय MZ_DELETE_FILE remove
  #अन्यथा
    #यदि_अपरिभाषितम् MINIZ_NO_TIME
      #अन्तर्भाव <utime.h>
    #यदि_अन्तः
    #परिभाषय MZ_FILE FILE
    #परिभाषय MZ_FOPEN(f, m) fopen(f, m)
    #परिभाषय MZ_FCLOSE fclose
    #परिभाषय MZ_FREAD fread
    #परिभाषय MZ_FWRITE fwrite
    #परिभाषय MZ_FTELL64 ftello
    #परिभाषय MZ_FSEEK64 fseeko
    #परिभाषय MZ_FILE_STAT_STRUCT stat
    #परिभाषय MZ_FILE_STAT stat
    #परिभाषय MZ_FFLUSH fflush
    #परिभाषय MZ_FREOPEN(f, m, s) freopen(f, m, s)
    #परिभाषय MZ_DELETE_FILE remove
  #यदि_अन्तः // #ifdef _MSC_VER
#यदि_अन्तः // #ifdef MINIZ_NO_STDIO

#परिभाषय MZ_TOLOWER(c) ((((c) >= 'A') && ((c) <= 'Z')) ? ((c) - 'A' + 'a') : (c))

// Various ZIP archive enums. To completely avoid cross platform compiler alignment and platform endian issues, miniz.c doesn't use structs for any of this stuff.
गणना
{
  // ZIP archive identifiers and record sizes
  MZ_ZIP_अन्तः_सम्बन्धि_CENTRAL_DIR_शीर्षकम्_SIG = 0x06054b50, MZ_ZIP_CENTRAL_DIR_शीर्षकम्_SIG = 0x02014b50, MZ_ZIP_LOCAL_DIR_शीर्षकम्_SIG = 0x04034b50,
  MZ_ZIP_LOCAL_DIR_शीर्षकम्_आकार = 30, MZ_ZIP_CENTRAL_DIR_शीर्षकम्_आकार = 46, MZ_ZIP_अन्तः_सम्बन्धि_CENTRAL_DIR_शीर्षकम्_आकार = 22,
  // Central directory header record offsets
  MZ_ZIP_CDH_SIG_OFS = 0, MZ_ZIP_CDH_संस्करणम्_MADE_BY_OFS = 4, MZ_ZIP_CDH_संस्करणम्_NEEDED_OFS = 6, MZ_ZIP_CDH_BIT_FLAG_OFS = 8,
  MZ_ZIP_CDH_विधानम्_OFS = 10, MZ_ZIP_CDH_FILE_TIME_OFS = 12, MZ_ZIP_CDH_FILE_DATE_OFS = 14, MZ_ZIP_CDH_चक्रीयपरीक्षा_32_OFS = 16,
  MZ_ZIP_CDH_COMPRESSED_आकार_OFS = 20, MZ_ZIP_CDH_DECOMPRESSED_आकार_OFS = 24, MZ_ZIP_CDH_FILENAME_LEN_OFS = 28, MZ_ZIP_CDH_EXTRA_LEN_OFS = 30,
  MZ_ZIP_CDH_COMMENT_LEN_OFS = 32, MZ_ZIP_CDH_DISK_START_OFS = 34, MZ_ZIP_CDH_आन्तरिकम्_ATTR_OFS = 36, MZ_ZIP_CDH_EXTERNAL_ATTR_OFS = 38, MZ_ZIP_CDH_LOCAL_शीर्षकम्_OFS = 42,
  // Local directory header offsets
  MZ_ZIP_LDH_SIG_OFS = 0, MZ_ZIP_LDH_संस्करणम्_NEEDED_OFS = 4, MZ_ZIP_LDH_BIT_FLAG_OFS = 6, MZ_ZIP_LDH_विधानम्_OFS = 8, MZ_ZIP_LDH_FILE_TIME_OFS = 10,
  MZ_ZIP_LDH_FILE_DATE_OFS = 12, MZ_ZIP_LDH_चक्रीयपरीक्षा_32_OFS = 14, MZ_ZIP_LDH_COMPRESSED_आकार_OFS = 18, MZ_ZIP_LDH_DECOMPRESSED_आकार_OFS = 22,
  MZ_ZIP_LDH_FILENAME_LEN_OFS = 26, MZ_ZIP_LDH_EXTRA_LEN_OFS = 28,
  // End of central directory offsets
  MZ_ZIP_ECDH_SIG_OFS = 0, MZ_ZIP_ECDH_अङ्कः_THIS_DISK_OFS = 4, MZ_ZIP_ECDH_अङ्कः_DISK_CDIR_OFS = 6, MZ_ZIP_ECDH_CDIR_अङ्कः_ENTRIES_ON_DISK_OFS = 8,
  MZ_ZIP_ECDH_CDIR_योग_ENTRIES_OFS = 10, MZ_ZIP_ECDH_CDIR_आकार_OFS = 12, MZ_ZIP_ECDH_CDIR_OFS_OFS = 16, MZ_ZIP_ECDH_COMMENT_आकार_OFS = 20,
};

प्रकारनिर्देश संरचना
{
  शून्य *m_p;
  size_t m_आकार, m_क्षमता;
  mz_uint m_element_आकार;
} mz_zip_array;

संरचना mz_zip_आन्तरिकम्_state_चिह्नकम्
{
  mz_zip_array m_central_dir;
  mz_zip_array m_central_dir_offsets;
  mz_zip_array m_sorted_central_dir_offsets;
  MZ_FILE *m_pFile;
  शून्य *m_pMem;
  size_t m_mem_आकार;
  size_t m_mem_क्षमता;
};

#परिभाषय MZ_ZIP_ARRAY_समुच्चयः_ELEMENT_आकार(array_ptr, element_आकार) (array_ptr)->m_element_आकार = element_आकार
#परिभाषय MZ_ZIP_ARRAY_ELEMENT(array_ptr, element_type, सूचकांक) ((element_type *)((array_ptr)->m_p))[सूचकांक]

स्थिर MZ_FORCEINLINE शून्य mz_zip_array_clear(mz_zip_archive *pZip, mz_zip_array *pArray)
{
  pZip->m_pFree(pZip->m_pAlloc_opaque, pArray->m_p);
  स्मृतिं_पूरय(pArray, 0, परिमाण(mz_zip_array));
}

स्थिर mz_bool mz_zip_array_ensure_क्षमता(mz_zip_archive *pZip, mz_zip_array *pArray, size_t min_new_क्षमता, mz_uint growing)
{
  शून्य *pNew_p; size_t new_क्षमता = min_new_क्षमता; MZ_ASSERT(pArray->m_element_आकार); यदि (pArray->m_क्षमता >= min_new_क्षमता) प्रत्यागम MZ_TRUE;
  यदि (growing) { new_क्षमता = MZ_MAX(1, pArray->m_क्षमता); यावत् (new_क्षमता < min_new_क्षमता) new_क्षमता *= 2; }
  यदि (रिक्त == (pNew_p = pZip->m_pRealloc(pZip->m_pAlloc_opaque, pArray->m_p, pArray->m_element_आकार, new_क्षमता))) प्रत्यागम MZ_FALSE;
  pArray->m_p = pNew_p; pArray->m_क्षमता = new_क्षमता;
  प्रत्यागम MZ_TRUE;
}

स्थिर MZ_FORCEINLINE mz_bool mz_zip_array_reserve(mz_zip_archive *pZip, mz_zip_array *pArray, size_t new_क्षमता, mz_uint growing)
{
  यदि (new_क्षमता > pArray->m_क्षमता) { यदि (!mz_zip_array_ensure_क्षमता(pZip, pArray, new_क्षमता, growing)) प्रत्यागम MZ_FALSE; }
  प्रत्यागम MZ_TRUE;
}

स्थिर MZ_FORCEINLINE mz_bool mz_zip_array_resize(mz_zip_archive *pZip, mz_zip_array *pArray, size_t new_आकार, mz_uint growing)
{
  यदि (new_आकार > pArray->m_क्षमता) { यदि (!mz_zip_array_ensure_क्षमता(pZip, pArray, new_आकार, growing)) प्रत्यागम MZ_FALSE; }
  pArray->m_आकार = new_आकार;
  प्रत्यागम MZ_TRUE;
}

स्थिर MZ_FORCEINLINE mz_bool mz_zip_array_ensure_अवकाशः(mz_zip_archive *pZip, mz_zip_array *pArray, size_t n)
{
  प्रत्यागम mz_zip_array_reserve(pZip, pArray, pArray->m_आकार + n, MZ_TRUE);
}

स्थिर MZ_FORCEINLINE mz_bool mz_zip_array_प्रक्षिप_पृष्ठभागः(mz_zip_archive *pZip, mz_zip_array *pArray, ध्रुव शून्य *pElements, size_t n)
{
  size_t orig_आकार = pArray->m_आकार; यदि (!mz_zip_array_resize(pZip, pArray, orig_आकार + n, MZ_TRUE)) प्रत्यागम MZ_FALSE;
  स्मृतिं_प्रतिलिख((mz_uint8*)pArray->m_p + orig_आकार * pArray->m_element_आकार, pElements, n * pArray->m_element_आकार);
  प्रत्यागम MZ_TRUE;
}

#यदि_अपरिभाषितम् MINIZ_NO_TIME
स्थिर time_t mz_zip_dos_गन्तव्यम्_time_t(पूर्णाङ्क dos_time, पूर्णाङ्क dos_date)
{
  संरचना tm tm;
  स्मृतिं_पूरय(&tm, 0, परिमाण(tm)); tm.tm_isdst = -1;
  tm.tm_year = ((dos_date >> 9) & 127) + 1980 - 1900; tm.tm_mon = ((dos_date >> 5) & 15) - 1; tm.tm_mday = dos_date & 31;
  tm.tm_hour = (dos_time >> 11) & 31; tm.tm_min = (dos_time >> 5) & 63; tm.tm_sec = (dos_time << 1) & 62;
  प्रत्यागम mktime(&tm);
}

स्थिर शून्य mz_zip_time_गन्तव्यम्_dos_time(time_t time, mz_uint16 *pDOS_time, mz_uint16 *pDOS_date)
{
#यदि_परिभाषितम् _MSC_VER
  संरचना tm tm_struct;
  संरचना tm *tm = &tm_struct;
  errno_t err = localtime_s(tm, &time);
  यदि (err)
  {
    *pDOS_date = 0; *pDOS_time = 0;
    प्रत्यागम;
  }
#अन्यथा
  संरचना tm *tm = localtime(&time);
#यदि_अन्तः
  *pDOS_time = (mz_uint16)(((tm->tm_hour) << 11) + ((tm->tm_min) << 5) + ((tm->tm_sec) >> 1));
  *pDOS_date = (mz_uint16)(((tm->tm_year + 1900 - 1980) << 9) + ((tm->tm_mon + 1) << 5) + tm->tm_mday);
}
#यदि_अन्तः

#यदि_अपरिभाषितम् MINIZ_NO_STDIO
स्थिर mz_bool mz_zip_get_file_modified_time(ध्रुव वर्ण *pFilename, mz_uint16 *pDOS_time, mz_uint16 *pDOS_date)
{
#यदि_परिभाषितम् MINIZ_NO_TIME
  (शून्य)pFilename; *pDOS_date = *pDOS_time = 0;
#अन्यथा
  संरचना MZ_FILE_STAT_STRUCT file_stat;
  // On Linux with x86 glibc, this call will fail on large files (>= 0x80000000 bytes) unless you compiled with _LARGEFILE64_SOURCE. Argh.
  यदि (MZ_FILE_STAT(pFilename, &file_stat) != 0)
    प्रत्यागम MZ_FALSE;
  mz_zip_time_गन्तव्यम्_dos_time(file_stat.st_mtime, pDOS_time, pDOS_date);
#यदि_अन्तः // #ifdef MINIZ_NO_TIME
  प्रत्यागम MZ_TRUE;
}

#यदि_अपरिभाषितम् MINIZ_NO_TIME
स्थिर mz_bool mz_zip_समुच्चयः_file_times(ध्रुव वर्ण *pFilename, time_t access_time, time_t modified_time)
{
  संरचना utimbuf t; t.actime = access_time; t.modtime = modified_time;
  प्रत्यागम !utime(pFilename, &t);
}
#यदि_अन्तः // #ifndef MINIZ_NO_TIME
#यदि_अन्तः // #ifndef MINIZ_NO_STDIO

स्थिर mz_bool mz_zip_reader_init_आन्तरिकम्(mz_zip_archive *pZip, mz_uint32 flags)
{
  (शून्य)flags;
  यदि ((!pZip) || (pZip->m_pState) || (pZip->m_zip_बहुलकम् != MZ_ZIP_बहुलकम्_INVALID))
    प्रत्यागम MZ_FALSE;

  यदि (!pZip->m_pAlloc) pZip->m_pAlloc = def_alloc_func;
  यदि (!pZip->m_pFree) pZip->m_pFree = def_free_func;
  यदि (!pZip->m_pRealloc) pZip->m_pRealloc = def_realloc_func;

  pZip->m_zip_बहुलकम् = MZ_ZIP_बहुलकम्_READING;
  pZip->m_archive_आकार = 0;
  pZip->m_central_directory_file_ofs = 0;
  pZip->m_योग_files = 0;

  यदि (रिक्त == (pZip->m_pState = (mz_zip_आन्तरिकम्_state *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, परिमाण(mz_zip_आन्तरिकम्_state))))
    प्रत्यागम MZ_FALSE;
  स्मृतिं_पूरय(pZip->m_pState, 0, परिमाण(mz_zip_आन्तरिकम्_state));
  MZ_ZIP_ARRAY_समुच्चयः_ELEMENT_आकार(&pZip->m_pState->m_central_dir, परिमाण(mz_uint8));
  MZ_ZIP_ARRAY_समुच्चयः_ELEMENT_आकार(&pZip->m_pState->m_central_dir_offsets, परिमाण(mz_uint32));
  MZ_ZIP_ARRAY_समुच्चयः_ELEMENT_आकार(&pZip->m_pState->m_sorted_central_dir_offsets, परिमाण(mz_uint32));
  प्रत्यागम MZ_TRUE;
}

स्थिर MZ_FORCEINLINE mz_bool mz_zip_reader_filename_less(ध्रुव mz_zip_array *pCentral_dir_array, ध्रुव mz_zip_array *pCentral_dir_offsets, mz_uint l_सूचकांक, mz_uint r_सूचकांक)
{
  ध्रुव mz_uint8 *pL = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, l_सूचकांक)), *pE;
  ध्रुव mz_uint8 *pR = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, r_सूचकांक));
  mz_uint l_len = MZ_READ_LE16(pL + MZ_ZIP_CDH_FILENAME_LEN_OFS), r_len = MZ_READ_LE16(pR + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  mz_uint8 l = 0, r = 0;
  pL += MZ_ZIP_CENTRAL_DIR_शीर्षकम्_आकार; pR += MZ_ZIP_CENTRAL_DIR_शीर्षकम्_आकार;
  pE = pL + MZ_MIN(l_len, r_len);
  यावत् (pL < pE)
  {
    यदि ((l = MZ_TOLOWER(*pL)) != (r = MZ_TOLOWER(*pR)))
      भङ्ग;
    pL++; pR++;
  }
  प्रत्यागम (pL == pE) ? (l_len < r_len) : (l < r);
}

#परिभाषय MZ_SWAP_UINT32(a, b) कुरु { mz_uint32 t = a; a = b; b = t; } MZ_MACRO_अन्तः

// Heap sort of lowercased filenames, used to help accelerate plain central directory searches by mz_zip_reader_locate_file(). (Could also use qsort(), but it could allocate memory.)
स्थिर शून्य mz_zip_reader_क्रमय_central_dir_offsets_by_filename(mz_zip_archive *pZip)
{
  mz_zip_आन्तरिकम्_state *pState = pZip->m_pState;
  ध्रुव mz_zip_array *pCentral_dir_offsets = &pState->m_central_dir_offsets;
  ध्रुव mz_zip_array *pCentral_dir = &pState->m_central_dir;
  mz_uint32 *pIndices = &MZ_ZIP_ARRAY_ELEMENT(&pState->m_sorted_central_dir_offsets, mz_uint32, 0);
  ध्रुव पूर्णाङ्क आकार = pZip->m_योग_files;
  पूर्णाङ्क start = (आकार - 2) >> 1, अन्तः;
  यावत् (start >= 0)
  {
    पूर्णाङ्क child, मूलम् = start;
    प्रति ( ; ; )
    {
      यदि ((child = (मूलम् << 1) + 1) >= आकार)
        भङ्ग;
      child += (((child + 1) < आकार) && (mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[child], pIndices[child + 1])));
      यदि (!mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[मूलम्], pIndices[child]))
        भङ्ग;
      MZ_SWAP_UINT32(pIndices[मूलम्], pIndices[child]); मूलम् = child;
    }
    start--;
  }

  अन्तः = आकार - 1;
  यावत् (अन्तः > 0)
  {
    पूर्णाङ्क child, मूलम् = 0;
    MZ_SWAP_UINT32(pIndices[अन्तः], pIndices[0]);
    प्रति ( ; ; )
    {
      यदि ((child = (मूलम् << 1) + 1) >= अन्तः)
        भङ्ग;
      child += (((child + 1) < अन्तः) && mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[child], pIndices[child + 1]));
      यदि (!mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[मूलम्], pIndices[child]))
        भङ्ग;
      MZ_SWAP_UINT32(pIndices[मूलम्], pIndices[child]); मूलम् = child;
    }
    अन्तः--;
  }
}

स्थिर mz_bool mz_zip_reader_read_central_dir(mz_zip_archive *pZip, mz_uint32 flags)
{
  mz_uint cdir_आकार, अङ्कः_this_disk, cdir_disk_सूचकांक;
  mz_uint64 cdir_ofs;
  mz_int64 cur_file_ofs;
  ध्रुव mz_uint8 *p;
  mz_uint32 buf_u32[4096 / परिमाण(mz_uint32)]; mz_uint8 *pBuf = (mz_uint8 *)buf_u32;
  mz_bool क्रमय_central_dir = ((flags & MZ_ZIP_FLAG_DO_NOT_क्रमय_CENTRAL_DIRECTORY) == 0);
  // Basic sanity checks - reject files which are too small, and check the first 4 bytes of the file to make sure a local header is there.
  यदि (pZip->m_archive_आकार < MZ_ZIP_अन्तः_सम्बन्धि_CENTRAL_DIR_शीर्षकम्_आकार)
    प्रत्यागम MZ_FALSE;
  // Find the end of central directory record by scanning the file from the end towards the beginning.
  cur_file_ofs = MZ_MAX((mz_int64)pZip->m_archive_आकार - (mz_int64)परिमाण(buf_u32), 0);
  प्रति ( ; ; )
  {
    पूर्णाङ्क i, n = (पूर्णाङ्क)MZ_MIN(परिमाण(buf_u32), pZip->m_archive_आकार - cur_file_ofs);
    यदि (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, n) != (mz_uint)n)
      प्रत्यागम MZ_FALSE;
    प्रति (i = n - 4; i >= 0; --i)
      यदि (MZ_READ_LE32(pBuf + i) == MZ_ZIP_अन्तः_सम्बन्धि_CENTRAL_DIR_शीर्षकम्_SIG)
        भङ्ग;
    यदि (i >= 0)
    {
      cur_file_ofs += i;
      भङ्ग;
    }
    यदि ((!cur_file_ofs) || ((pZip->m_archive_आकार - cur_file_ofs) >= (0xFFFF + MZ_ZIP_अन्तः_सम्बन्धि_CENTRAL_DIR_शीर्षकम्_आकार)))
      प्रत्यागम MZ_FALSE;
    cur_file_ofs = MZ_MAX(cur_file_ofs - (परिमाण(buf_u32) - 3), 0);
  }
  // Read and verify the end of central directory record.
  यदि (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, MZ_ZIP_अन्तः_सम्बन्धि_CENTRAL_DIR_शीर्षकम्_आकार) != MZ_ZIP_अन्तः_सम्बन्धि_CENTRAL_DIR_शीर्षकम्_आकार)
    प्रत्यागम MZ_FALSE;
  यदि ((MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_SIG_OFS) != MZ_ZIP_अन्तः_सम्बन्धि_CENTRAL_DIR_शीर्षकम्_SIG) ||
      ((pZip->m_योग_files = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_CDIR_योग_ENTRIES_OFS)) != MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_CDIR_अङ्कः_ENTRIES_ON_DISK_OFS)))
    प्रत्यागम MZ_FALSE;

  अङ्कः_this_disk = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_अङ्कः_THIS_DISK_OFS);
  cdir_disk_सूचकांक = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_अङ्कः_DISK_CDIR_OFS);
  यदि (((अङ्कः_this_disk | cdir_disk_सूचकांक) != 0) && ((अङ्कः_this_disk != 1) || (cdir_disk_सूचकांक != 1)))
    प्रत्यागम MZ_FALSE;

  यदि ((cdir_आकार = MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_CDIR_आकार_OFS)) < pZip->m_योग_files * MZ_ZIP_CENTRAL_DIR_शीर्षकम्_आकार)
    प्रत्यागम MZ_FALSE;

  cdir_ofs = MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_CDIR_OFS_OFS);
  यदि ((cdir_ofs + (mz_uint64)cdir_आकार) > pZip->m_archive_आकार)
    प्रत्यागम MZ_FALSE;

  pZip->m_central_directory_file_ofs = cdir_ofs;

  यदि (pZip->m_योग_files)
  {
     mz_uint i, n;

    // Read the entire central directory into a heap block, and allocate another heap block to hold the unsorted central dir file record offsets, and another to hold the sorted indices.
    यदि ((!mz_zip_array_resize(pZip, &pZip->m_pState->m_central_dir, cdir_आकार, MZ_FALSE)) ||
        (!mz_zip_array_resize(pZip, &pZip->m_pState->m_central_dir_offsets, pZip->m_योग_files, MZ_FALSE)))
      प्रत्यागम MZ_FALSE;

    यदि (क्रमय_central_dir)
    {
      यदि (!mz_zip_array_resize(pZip, &pZip->m_pState->m_sorted_central_dir_offsets, pZip->m_योग_files, MZ_FALSE))
        प्रत्यागम MZ_FALSE;
    }

    यदि (pZip->m_pRead(pZip->m_pIO_opaque, cdir_ofs, pZip->m_pState->m_central_dir.m_p, cdir_आकार) != cdir_आकार)
      प्रत्यागम MZ_FALSE;

    // Now create an index into the central directory file records, do some basic sanity checking on each record, and check for zip64 entries (which are not yet supported).
    p = (ध्रुव mz_uint8 *)pZip->m_pState->m_central_dir.m_p;
    प्रति (n = cdir_आकार, i = 0; i < pZip->m_योग_files; ++i)
    {
      mz_uint योग_शीर्षकम्_आकार, comp_आकार, decomp_आकार, disk_सूचकांक;
      यदि ((n < MZ_ZIP_CENTRAL_DIR_शीर्षकम्_आकार) || (MZ_READ_LE32(p) != MZ_ZIP_CENTRAL_DIR_शीर्षकम्_SIG))
        प्रत्यागम MZ_FALSE;
      MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, i) = (mz_uint32)(p - (ध्रुव mz_uint8 *)pZip->m_pState->m_central_dir.m_p);
      यदि (क्रमय_central_dir)
        MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_sorted_central_dir_offsets, mz_uint32, i) = i;
      comp_आकार = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_आकार_OFS);
      decomp_आकार = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_आकार_OFS);
      यदि (((!MZ_READ_LE32(p + MZ_ZIP_CDH_विधानम्_OFS)) && (decomp_आकार != comp_आकार)) || (decomp_आकार && !comp_आकार) || (decomp_आकार == 0xFFFFFFFF) || (comp_आकार == 0xFFFFFFFF))
        प्रत्यागम MZ_FALSE;
      disk_सूचकांक = MZ_READ_LE16(p + MZ_ZIP_CDH_DISK_START_OFS);
      यदि ((disk_सूचकांक != अङ्कः_this_disk) && (disk_सूचकांक != 1))
        प्रत्यागम MZ_FALSE;
      यदि (((mz_uint64)MZ_READ_LE32(p + MZ_ZIP_CDH_LOCAL_शीर्षकम्_OFS) + MZ_ZIP_LOCAL_DIR_शीर्षकम्_आकार + comp_आकार) > pZip->m_archive_आकार)
        प्रत्यागम MZ_FALSE;
      यदि ((योग_शीर्षकम्_आकार = MZ_ZIP_CENTRAL_DIR_शीर्षकम्_आकार + MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_EXTRA_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_COMMENT_LEN_OFS)) > n)
        प्रत्यागम MZ_FALSE;
      n -= योग_शीर्षकम्_आकार; p += योग_शीर्षकम्_आकार;
    }
  }

  यदि (क्रमय_central_dir)
    mz_zip_reader_क्रमय_central_dir_offsets_by_filename(pZip);

  प्रत्यागम MZ_TRUE;
}

mz_bool mz_zip_reader_init(mz_zip_archive *pZip, mz_uint64 आकार, mz_uint32 flags)
{
  यदि ((!pZip) || (!pZip->m_pRead))
    प्रत्यागम MZ_FALSE;
  यदि (!mz_zip_reader_init_आन्तरिकम्(pZip, flags))
    प्रत्यागम MZ_FALSE;
  pZip->m_archive_आकार = आकार;
  यदि (!mz_zip_reader_read_central_dir(pZip, flags))
  {
    mz_zip_reader_अन्तः(pZip);
    प्रत्यागम MZ_FALSE;
  }
  प्रत्यागम MZ_TRUE;
}

स्थिर size_t mz_zip_mem_read_func(शून्य *pOpaque, mz_uint64 file_ofs, शून्य *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  size_t s = (file_ofs >= pZip->m_archive_आकार) ? 0 : (size_t)MZ_MIN(pZip->m_archive_आकार - file_ofs, n);
  स्मृतिं_प्रतिलिख(pBuf, (ध्रुव mz_uint8 *)pZip->m_pState->m_pMem + file_ofs, s);
  प्रत्यागम s;
}

mz_bool mz_zip_reader_init_mem(mz_zip_archive *pZip, ध्रुव शून्य *pMem, size_t आकार, mz_uint32 flags)
{
  यदि (!mz_zip_reader_init_आन्तरिकम्(pZip, flags))
    प्रत्यागम MZ_FALSE;
  pZip->m_archive_आकार = आकार;
  pZip->m_pRead = mz_zip_mem_read_func;
  pZip->m_pIO_opaque = pZip;
#यदि_परिभाषितम् __cplusplus
  pZip->m_pState->m_pMem = const_cast<शून्य *>(pMem);
#अन्यथा
  pZip->m_pState->m_pMem = (शून्य *)pMem;
#यदि_अन्तः
  pZip->m_pState->m_mem_आकार = आकार;
  यदि (!mz_zip_reader_read_central_dir(pZip, flags))
  {
    mz_zip_reader_अन्तः(pZip);
    प्रत्यागम MZ_FALSE;
  }
  प्रत्यागम MZ_TRUE;
}

#यदि_अपरिभाषितम् MINIZ_NO_STDIO
स्थिर size_t mz_zip_file_read_func(शून्य *pOpaque, mz_uint64 file_ofs, शून्य *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_int64 cur_ofs = MZ_FTELL64(pZip->m_pState->m_pFile);
  यदि (((mz_int64)file_ofs < 0) || (((cur_ofs != (mz_int64)file_ofs)) && (MZ_FSEEK64(pZip->m_pState->m_pFile, (mz_int64)file_ofs, SEEK_SET))))
    प्रत्यागम 0;
  प्रत्यागम MZ_FREAD(pBuf, 1, n, pZip->m_pState->m_pFile);
}

mz_bool mz_zip_reader_init_file(mz_zip_archive *pZip, ध्रुव वर्ण *pFilename, mz_uint32 flags)
{
  mz_uint64 file_आकार;
  MZ_FILE *pFile = MZ_FOPEN(pFilename, "rb");
  यदि (!pFile)
    प्रत्यागम MZ_FALSE;
  यदि (MZ_FSEEK64(pFile, 0, SEEK_END))
  {
    MZ_FCLOSE(pFile);
    प्रत्यागम MZ_FALSE;
  }
  file_आकार = MZ_FTELL64(pFile);
  यदि (!mz_zip_reader_init_आन्तरिकम्(pZip, flags))
  {
    MZ_FCLOSE(pFile);
    प्रत्यागम MZ_FALSE;
  }
  pZip->m_pRead = mz_zip_file_read_func;
  pZip->m_pIO_opaque = pZip;
  pZip->m_pState->m_pFile = pFile;
  pZip->m_archive_आकार = file_आकार;
  यदि (!mz_zip_reader_read_central_dir(pZip, flags))
  {
    mz_zip_reader_अन्तः(pZip);
    प्रत्यागम MZ_FALSE;
  }
  प्रत्यागम MZ_TRUE;
}
#यदि_अन्तः // #ifndef MINIZ_NO_STDIO

mz_uint mz_zip_reader_get_अङ्कः_files(mz_zip_archive *pZip)
{
  प्रत्यागम pZip ? pZip->m_योग_files : 0;
}

स्थिर MZ_FORCEINLINE ध्रुव mz_uint8 *mz_zip_reader_get_cdh(mz_zip_archive *pZip, mz_uint file_सूचकांक)
{
  यदि ((!pZip) || (!pZip->m_pState) || (file_सूचकांक >= pZip->m_योग_files) || (pZip->m_zip_बहुलकम् != MZ_ZIP_बहुलकम्_READING))
    प्रत्यागम रिक्त;
  प्रत्यागम &MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_सूचकांक));
}

mz_bool mz_zip_reader_is_file_encrypted(mz_zip_archive *pZip, mz_uint file_सूचकांक)
{
  mz_uint m_bit_flag;
  ध्रुव mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_सूचकांक);
  यदि (!p)
    प्रत्यागम MZ_FALSE;
  m_bit_flag = MZ_READ_LE16(p + MZ_ZIP_CDH_BIT_FLAG_OFS);
  प्रत्यागम (m_bit_flag & 1);
}

mz_bool mz_zip_reader_is_file_a_directory(mz_zip_archive *pZip, mz_uint file_सूचकांक)
{
  mz_uint filename_len, external_attr;
  ध्रुव mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_सूचकांक);
  यदि (!p)
    प्रत्यागम MZ_FALSE;

  // First see if the filename ends with a '/' character.
  filename_len = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  यदि (filename_len)
  {
    यदि (*(p + MZ_ZIP_CENTRAL_DIR_शीर्षकम्_आकार + filename_len - 1) == '/')
      प्रत्यागम MZ_TRUE;
  }

  // Bugfix: This code was also checking if the internal attribute was non-zero, which wasn't correct.
  // Most/all zip writers (hopefully) set DOS file/directory attributes in the low 16-bits, so check for the DOS directory flag and ignore the source OS ID in the created by field.
  // FIXME: Remove this check? Is it necessary - we already check the filename.
  external_attr = MZ_READ_LE32(p + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS);
  यदि ((external_attr & 0x10) != 0)
    प्रत्यागम MZ_TRUE;

  प्रत्यागम MZ_FALSE;
}

mz_bool mz_zip_reader_file_stat(mz_zip_archive *pZip, mz_uint file_सूचकांक, mz_zip_archive_file_stat *pStat)
{
  mz_uint n;
  ध्रुव mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_सूचकांक);
  यदि ((!p) || (!pStat))
    प्रत्यागम MZ_FALSE;

  // Unpack the central directory record.
  pStat->m_file_सूचकांक = file_सूचकांक;
  pStat->m_central_dir_ofs = MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_सूचकांक);
  pStat->m_संस्करणम्_made_by = MZ_READ_LE16(p + MZ_ZIP_CDH_संस्करणम्_MADE_BY_OFS);
  pStat->m_संस्करणम्_needed = MZ_READ_LE16(p + MZ_ZIP_CDH_संस्करणम्_NEEDED_OFS);
  pStat->m_bit_flag = MZ_READ_LE16(p + MZ_ZIP_CDH_BIT_FLAG_OFS);
  pStat->m_विधानम् = MZ_READ_LE16(p + MZ_ZIP_CDH_विधानम्_OFS);
#यदि_अपरिभाषितम् MINIZ_NO_TIME
  pStat->m_time = mz_zip_dos_गन्तव्यम्_time_t(MZ_READ_LE16(p + MZ_ZIP_CDH_FILE_TIME_OFS), MZ_READ_LE16(p + MZ_ZIP_CDH_FILE_DATE_OFS));
#यदि_अन्तः
  pStat->m_चक्रीयपरीक्षा_32 = MZ_READ_LE32(p + MZ_ZIP_CDH_चक्रीयपरीक्षा_32_OFS);
  pStat->m_comp_आकार = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_आकार_OFS);
  pStat->m_uncomp_आकार = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_आकार_OFS);
  pStat->m_आन्तरिकम्_attr = MZ_READ_LE16(p + MZ_ZIP_CDH_आन्तरिकम्_ATTR_OFS);
  pStat->m_external_attr = MZ_READ_LE32(p + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS);
  pStat->m_local_शीर्षकम्_ofs = MZ_READ_LE32(p + MZ_ZIP_CDH_LOCAL_शीर्षकम्_OFS);

  // Copy as much of the filename and comment as possible.
  n = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS); n = MZ_MIN(n, MZ_ZIP_MAX_ARCHIVE_FILENAME_आकार - 1);
  स्मृतिं_प्रतिलिख(pStat->m_filename, p + MZ_ZIP_CENTRAL_DIR_शीर्षकम्_आकार, n); pStat->m_filename[n] = '\0';

  n = MZ_READ_LE16(p + MZ_ZIP_CDH_COMMENT_LEN_OFS); n = MZ_MIN(n, MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_आकार - 1);
  pStat->m_comment_आकार = n;
  स्मृतिं_प्रतिलिख(pStat->m_comment, p + MZ_ZIP_CENTRAL_DIR_शीर्षकम्_आकार + MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_EXTRA_LEN_OFS), n); pStat->m_comment[n] = '\0';

  प्रत्यागम MZ_TRUE;
}

mz_uint mz_zip_reader_get_filename(mz_zip_archive *pZip, mz_uint file_सूचकांक, वर्ण *pFilename, mz_uint filename_buf_आकार)
{
  mz_uint n;
  ध्रुव mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_सूचकांक);
  यदि (!p) { यदि (filename_buf_आकार) pFilename[0] = '\0'; प्रत्यागम 0; }
  n = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  यदि (filename_buf_आकार)
  {
    n = MZ_MIN(n, filename_buf_आकार - 1);
    स्मृतिं_प्रतिलिख(pFilename, p + MZ_ZIP_CENTRAL_DIR_शीर्षकम्_आकार, n);
    pFilename[n] = '\0';
  }
  प्रत्यागम n + 1;
}

स्थिर MZ_FORCEINLINE mz_bool mz_zip_reader_string_equal(ध्रुव वर्ण *pA, ध्रुव वर्ण *pB, mz_uint len, mz_uint flags)
{
  mz_uint i;
  यदि (flags & MZ_ZIP_FLAG_CASE_SENSITIVE)
    प्रत्यागम 0 == memcmp(pA, pB, len);
  प्रति (i = 0; i < len; ++i)
    यदि (MZ_TOLOWER(pA[i]) != MZ_TOLOWER(pB[i]))
      प्रत्यागम MZ_FALSE;
  प्रत्यागम MZ_TRUE;
}

स्थिर MZ_FORCEINLINE पूर्णाङ्क mz_zip_reader_filename_compare(ध्रुव mz_zip_array *pCentral_dir_array, ध्रुव mz_zip_array *pCentral_dir_offsets, mz_uint l_सूचकांक, ध्रुव वर्ण *pR, mz_uint r_len)
{
  ध्रुव mz_uint8 *pL = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, l_सूचकांक)), *pE;
  mz_uint l_len = MZ_READ_LE16(pL + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  mz_uint8 l = 0, r = 0;
  pL += MZ_ZIP_CENTRAL_DIR_शीर्षकम्_आकार;
  pE = pL + MZ_MIN(l_len, r_len);
  यावत् (pL < pE)
  {
    यदि ((l = MZ_TOLOWER(*pL)) != (r = MZ_TOLOWER(*pR)))
      भङ्ग;
    pL++; pR++;
  }
  प्रत्यागम (pL == pE) ? (पूर्णाङ्क)(l_len - r_len) : (l - r);
}

स्थिर पूर्णाङ्क mz_zip_reader_locate_file_द्विमान_अन्वेषणम्(mz_zip_archive *pZip, ध्रुव वर्ण *pFilename)
{
  mz_zip_आन्तरिकम्_state *pState = pZip->m_pState;
  ध्रुव mz_zip_array *pCentral_dir_offsets = &pState->m_central_dir_offsets;
  ध्रुव mz_zip_array *pCentral_dir = &pState->m_central_dir;
  mz_uint32 *pIndices = &MZ_ZIP_ARRAY_ELEMENT(&pState->m_sorted_central_dir_offsets, mz_uint32, 0);
  ध्रुव पूर्णाङ्क आकार = pZip->m_योग_files;
  ध्रुव mz_uint filename_len = (mz_uint)वाक्यदैर्घ्यम्(pFilename);
  पूर्णाङ्क l = 0, h = आकार - 1;
  यावत् (l <= h)
  {
    पूर्णाङ्क m = (l + h) >> 1, file_सूचकांक = pIndices[m], comp = mz_zip_reader_filename_compare(pCentral_dir, pCentral_dir_offsets, file_सूचकांक, pFilename, filename_len);
    यदि (!comp)
      प्रत्यागम file_सूचकांक;
    अन्यथा यदि (comp < 0)
      l = m + 1;
    अन्यथा
      h = m - 1;
  }
  प्रत्यागम -1;
}

पूर्णाङ्क mz_zip_reader_locate_file(mz_zip_archive *pZip, ध्रुव वर्ण *pName, ध्रुव वर्ण *pComment, mz_uint flags)
{
  mz_uint file_सूचकांक; size_t name_len, comment_len;
  यदि ((!pZip) || (!pZip->m_pState) || (!pName) || (pZip->m_zip_बहुलकम् != MZ_ZIP_बहुलकम्_READING))
    प्रत्यागम -1;
  यदि (((flags & (MZ_ZIP_FLAG_IGNORE_मार्गः | MZ_ZIP_FLAG_CASE_SENSITIVE)) == 0) && (!pComment) && (pZip->m_pState->m_sorted_central_dir_offsets.m_आकार))
    प्रत्यागम mz_zip_reader_locate_file_द्विमान_अन्वेषणम्(pZip, pName);
  name_len = वाक्यदैर्घ्यम्(pName); यदि (name_len > 0xFFFF) प्रत्यागम -1;
  comment_len = pComment ? वाक्यदैर्घ्यम्(pComment) : 0; यदि (comment_len > 0xFFFF) प्रत्यागम -1;
  प्रति (file_सूचकांक = 0; file_सूचकांक < pZip->m_योग_files; file_सूचकांक++)
  {
    ध्रुव mz_uint8 *p_शीर्षकम् = &MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_सूचकांक));
    mz_uint filename_len = MZ_READ_LE16(p_शीर्षकम् + MZ_ZIP_CDH_FILENAME_LEN_OFS);
    ध्रुव वर्ण *pFilename = (ध्रुव वर्ण *)p_शीर्षकम् + MZ_ZIP_CENTRAL_DIR_शीर्षकम्_आकार;
    यदि (filename_len < name_len)
      अनुवर्त;
    यदि (comment_len)
    {
      mz_uint file_extra_len = MZ_READ_LE16(p_शीर्षकम् + MZ_ZIP_CDH_EXTRA_LEN_OFS), file_comment_len = MZ_READ_LE16(p_शीर्षकम् + MZ_ZIP_CDH_COMMENT_LEN_OFS);
      ध्रुव वर्ण *pFile_comment = pFilename + filename_len + file_extra_len;
      यदि ((file_comment_len != comment_len) || (!mz_zip_reader_string_equal(pComment, pFile_comment, file_comment_len, flags)))
        अनुवर्त;
    }
    यदि ((flags & MZ_ZIP_FLAG_IGNORE_मार्गः) && (filename_len))
    {
      पूर्णाङ्क ofs = filename_len - 1;
      कुरु
      {
        यदि ((pFilename[ofs] == '/') || (pFilename[ofs] == '\\') || (pFilename[ofs] == ':'))
          भङ्ग;
      } यावत् (--ofs >= 0);
      ofs++;
      pFilename += ofs; filename_len -= ofs;
    }
    यदि ((filename_len == name_len) && (mz_zip_reader_string_equal(pName, pFilename, filename_len, flags)))
      प्रत्यागम file_सूचकांक;
  }
  प्रत्यागम -1;
}

mz_bool mz_zip_reader_extract_गन्तव्यम्_mem_no_alloc(mz_zip_archive *pZip, mz_uint file_सूचकांक, शून्य *pBuf, size_t buf_आकार_2, mz_uint flags, शून्य *pUser_read_buf, size_t user_read_buf_आकार)
{
  पूर्णाङ्क स्थितिः = TINFL_स्थितिः_समाप्तम्;
  mz_uint64 needed_आकार, cur_file_ofs, comp_remaining, बहिर्गमनम्_buf_ofs = 0, read_buf_आकार, read_buf_ofs = 0, read_buf_avail;
  mz_zip_archive_file_stat file_stat;
  शून्य *pRead_buf;
  mz_uint32 local_शीर्षकम्_u32[(MZ_ZIP_LOCAL_DIR_शीर्षकम्_आकार + परिमाण(mz_uint32) - 1) / परिमाण(mz_uint32)]; mz_uint8 *p_Local_शीर्षकम् = (mz_uint8 *)local_शीर्षकम्_u32;
  tinfl_decompressor inflator;

  यदि ((buf_आकार_2) && (!pBuf))
    प्रत्यागम MZ_FALSE;

  यदि (!mz_zip_reader_file_stat(pZip, file_सूचकांक, &file_stat))
    प्रत्यागम MZ_FALSE;

  // Empty file, or a directory (but not always a directory - I've seen odd zips with directories that have compressed data which inflates to 0 bytes)
  यदि (!file_stat.m_comp_आकार)
    प्रत्यागम MZ_TRUE;

  // Entry is a subdirectory (I've seen old zips with dir entries which have compressed deflate data which inflates to 0 bytes, but these entries claim to uncompress to 512 bytes in the headers).
  // I'm torn how to handle this case - should it fail instead?
  यदि (mz_zip_reader_is_file_a_directory(pZip, file_सूचकांक))
    प्रत्यागम MZ_TRUE;

  // Encryption and patch files are not supported.
  यदि (file_stat.m_bit_flag & (1 | 32))
    प्रत्यागम MZ_FALSE;

  // This function only supports stored and deflate.
  यदि ((!(flags & MZ_ZIP_FLAG_COMPRESSED_दत्त)) && (file_stat.m_विधानम् != 0) && (file_stat.m_विधानम् != MZ_DEFLATED))
    प्रत्यागम MZ_FALSE;

  // Ensure supplied output buffer is large enough.
  needed_आकार = (flags & MZ_ZIP_FLAG_COMPRESSED_दत्त) ? file_stat.m_comp_आकार : file_stat.m_uncomp_आकार;
  यदि (buf_आकार_2 < needed_आकार)
    प्रत्यागम MZ_FALSE;

  // Read and parse the local directory entry.
  cur_file_ofs = file_stat.m_local_शीर्षकम्_ofs;
  यदि (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, p_Local_शीर्षकम्, MZ_ZIP_LOCAL_DIR_शीर्षकम्_आकार) != MZ_ZIP_LOCAL_DIR_शीर्षकम्_आकार)
    प्रत्यागम MZ_FALSE;
  यदि (MZ_READ_LE32(p_Local_शीर्षकम्) != MZ_ZIP_LOCAL_DIR_शीर्षकम्_SIG)
    प्रत्यागम MZ_FALSE;

  cur_file_ofs += MZ_ZIP_LOCAL_DIR_शीर्षकम्_आकार + MZ_READ_LE16(p_Local_शीर्षकम् + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p_Local_शीर्षकम् + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  यदि ((cur_file_ofs + file_stat.m_comp_आकार) > pZip->m_archive_आकार)
    प्रत्यागम MZ_FALSE;

  यदि ((flags & MZ_ZIP_FLAG_COMPRESSED_दत्त) || (!file_stat.m_विधानम्))
  {
    // The file is stored or the caller has requested the compressed data.
    यदि (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, (size_t)needed_आकार) != needed_आकार)
      प्रत्यागम MZ_FALSE;
    प्रत्यागम ((flags & MZ_ZIP_FLAG_COMPRESSED_दत्त) != 0) || (mz_चक्रीयपरीक्षा_32(MZ_चक्रीयपरीक्षा_32_INIT, (ध्रुव mz_uint8 *)pBuf, (size_t)file_stat.m_uncomp_आकार) == file_stat.m_चक्रीयपरीक्षा_32);
  }

  // Decompress the file either directly from memory or from a file input buffer.
  tinfl_init(&inflator);

  यदि (pZip->m_pState->m_pMem)
  {
    // Read directly from the archive in memory.
    pRead_buf = (mz_uint8 *)pZip->m_pState->m_pMem + cur_file_ofs;
    read_buf_आकार = read_buf_avail = file_stat.m_comp_आकार;
    comp_remaining = 0;
  }
  अन्यथा यदि (pUser_read_buf)
  {
    // Use a user provided read buffer.
    यदि (!user_read_buf_आकार)
      प्रत्यागम MZ_FALSE;
    pRead_buf = (mz_uint8 *)pUser_read_buf;
    read_buf_आकार = user_read_buf_आकार;
    read_buf_avail = 0;
    comp_remaining = file_stat.m_comp_आकार;
  }
  अन्यथा
  {
    // Temporarily allocate a read buffer.
    read_buf_आकार = MZ_MIN(file_stat.m_comp_आकार, MZ_ZIP_MAX_IO_BUF_आकार);
#यदि_परिभाषितम् _MSC_VER
    यदि (((0, परिमाण(size_t) == परिमाण(mz_uint32))) && (read_buf_आकार > 0x7FFFFFFF))
#अन्यथा
    यदि (((परिमाण(size_t) == परिमाण(mz_uint32))) && (read_buf_आकार > 0x7FFFFFFF))
#यदि_अन्तः
      प्रत्यागम MZ_FALSE;
    यदि (रिक्त == (pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)read_buf_आकार)))
      प्रत्यागम MZ_FALSE;
    read_buf_avail = 0;
    comp_remaining = file_stat.m_comp_आकार;
  }

  कुरु
  {
    size_t अन्तर्_buf_आकार, बहिर्गमनम्_buf_आकार = (size_t)(file_stat.m_uncomp_आकार - बहिर्गमनम्_buf_ofs);
    यदि ((!read_buf_avail) && (!pZip->m_pState->m_pMem))
    {
      read_buf_avail = MZ_MIN(read_buf_आकार, comp_remaining);
      यदि (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
      {
        स्थितिः = TINFL_स्थितिः_FAILED;
        भङ्ग;
      }
      cur_file_ofs += read_buf_avail;
      comp_remaining -= read_buf_avail;
      read_buf_ofs = 0;
    }
    अन्तर्_buf_आकार = (size_t)read_buf_avail;
    स्थितिः = tinfl_decompress(&inflator, (mz_uint8 *)pRead_buf + read_buf_ofs, &अन्तर्_buf_आकार, (mz_uint8 *)pBuf, (mz_uint8 *)pBuf + बहिर्गमनम्_buf_ofs, &बहिर्गमनम्_buf_आकार, TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF | (comp_remaining ? TINFL_FLAG_HAS_अधिकम्_निवेशः : 0));
    read_buf_avail -= अन्तर्_buf_आकार;
    read_buf_ofs += अन्तर्_buf_आकार;
    बहिर्गमनम्_buf_ofs += बहिर्गमनम्_buf_आकार;
  } यावत् (स्थितिः == TINFL_स्थितिः_NEEDS_अधिकम्_निवेशः);

  यदि (स्थितिः == TINFL_स्थितिः_समाप्तम्)
  {
    // Make sure the entire file was decompressed, and check its CRC.
    यदि ((बहिर्गमनम्_buf_ofs != file_stat.m_uncomp_आकार) || (mz_चक्रीयपरीक्षा_32(MZ_चक्रीयपरीक्षा_32_INIT, (ध्रुव mz_uint8 *)pBuf, (size_t)file_stat.m_uncomp_आकार) != file_stat.m_चक्रीयपरीक्षा_32))
      स्थितिः = TINFL_स्थितिः_FAILED;
  }

  यदि ((!pZip->m_pState->m_pMem) && (!pUser_read_buf))
    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);

  प्रत्यागम स्थितिः == TINFL_स्थितिः_समाप्तम्;
}

mz_bool mz_zip_reader_extract_file_गन्तव्यम्_mem_no_alloc(mz_zip_archive *pZip, ध्रुव वर्ण *pFilename, शून्य *pBuf, size_t buf_आकार_2, mz_uint flags, शून्य *pUser_read_buf, size_t user_read_buf_आकार)
{
  पूर्णाङ्क file_सूचकांक = mz_zip_reader_locate_file(pZip, pFilename, रिक्त, flags);
  यदि (file_सूचकांक < 0)
    प्रत्यागम MZ_FALSE;
  प्रत्यागम mz_zip_reader_extract_गन्तव्यम्_mem_no_alloc(pZip, file_सूचकांक, pBuf, buf_आकार_2, flags, pUser_read_buf, user_read_buf_आकार);
}

mz_bool mz_zip_reader_extract_गन्तव्यम्_mem(mz_zip_archive *pZip, mz_uint file_सूचकांक, शून्य *pBuf, size_t buf_आकार_2, mz_uint flags)
{
  प्रत्यागम mz_zip_reader_extract_गन्तव्यम्_mem_no_alloc(pZip, file_सूचकांक, pBuf, buf_आकार_2, flags, रिक्त, 0);
}

mz_bool mz_zip_reader_extract_file_गन्तव्यम्_mem(mz_zip_archive *pZip, ध्रुव वर्ण *pFilename, शून्य *pBuf, size_t buf_आकार_2, mz_uint flags)
{
  प्रत्यागम mz_zip_reader_extract_file_गन्तव्यम्_mem_no_alloc(pZip, pFilename, pBuf, buf_आकार_2, flags, रिक्त, 0);
}

शून्य *mz_zip_reader_extract_गन्तव्यम्_heap(mz_zip_archive *pZip, mz_uint file_सूचकांक, size_t *p_आकार, mz_uint flags)
{
  mz_uint64 comp_आकार, uncomp_आकार, alloc_आकार_2;
  ध्रुव mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_सूचकांक);
  शून्य *pBuf;

  यदि (p_आकार)
    *p_आकार = 0;
  यदि (!p)
    प्रत्यागम रिक्त;

  comp_आकार = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_आकार_OFS);
  uncomp_आकार = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_आकार_OFS);

  alloc_आकार_2 = (flags & MZ_ZIP_FLAG_COMPRESSED_दत्त) ? comp_आकार : uncomp_आकार;
#यदि_परिभाषितम् _MSC_VER
  यदि (((0, परिमाण(size_t) == परिमाण(mz_uint32))) && (alloc_आकार_2 > 0x7FFFFFFF))
#अन्यथा
  यदि (((परिमाण(size_t) == परिमाण(mz_uint32))) && (alloc_आकार_2 > 0x7FFFFFFF))
#यदि_अन्तः
    प्रत्यागम रिक्त;
  यदि (रिक्त == (pBuf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)alloc_आकार_2)))
    प्रत्यागम रिक्त;

  यदि (!mz_zip_reader_extract_गन्तव्यम्_mem(pZip, file_सूचकांक, pBuf, (size_t)alloc_आकार_2, flags))
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
    प्रत्यागम रिक्त;
  }

  यदि (p_आकार) *p_आकार = (size_t)alloc_आकार_2;
  प्रत्यागम pBuf;
}

शून्य *mz_zip_reader_extract_file_गन्तव्यम्_heap(mz_zip_archive *pZip, ध्रुव वर्ण *pFilename, size_t *p_आकार, mz_uint flags)
{
  पूर्णाङ्क file_सूचकांक = mz_zip_reader_locate_file(pZip, pFilename, रिक्त, flags);
  यदि (file_सूचकांक < 0)
  {
    यदि (p_आकार) *p_आकार = 0;
    प्रत्यागम MZ_FALSE;
  }
  प्रत्यागम mz_zip_reader_extract_गन्तव्यम्_heap(pZip, file_सूचकांक, p_आकार, flags);
}

mz_bool mz_zip_reader_extract_गन्तव्यम्_callback(mz_zip_archive *pZip, mz_uint file_सूचकांक, mz_file_write_func pCallback, शून्य *pOpaque, mz_uint flags)
{
  पूर्णाङ्क स्थितिः = TINFL_स्थितिः_समाप्तम्; mz_uint file_चक्रीयपरीक्षा_32 = MZ_चक्रीयपरीक्षा_32_INIT;
  mz_uint64 read_buf_आकार, read_buf_ofs = 0, read_buf_avail, comp_remaining, बहिर्गमनम्_buf_ofs = 0, cur_file_ofs;
  mz_zip_archive_file_stat file_stat;
  शून्य *pRead_buf = रिक्त; शून्य *pWrite_buf = रिक्त;
  mz_uint32 local_शीर्षकम्_u32[(MZ_ZIP_LOCAL_DIR_शीर्षकम्_आकार + परिमाण(mz_uint32) - 1) / परिमाण(mz_uint32)]; mz_uint8 *p_Local_शीर्षकम् = (mz_uint8 *)local_शीर्षकम्_u32;

  यदि (!mz_zip_reader_file_stat(pZip, file_सूचकांक, &file_stat))
    प्रत्यागम MZ_FALSE;

  // Empty file, or a directory (but not always a directory - I've seen odd zips with directories that have compressed data which inflates to 0 bytes)
  यदि (!file_stat.m_comp_आकार)
    प्रत्यागम MZ_TRUE;

  // Entry is a subdirectory (I've seen old zips with dir entries which have compressed deflate data which inflates to 0 bytes, but these entries claim to uncompress to 512 bytes in the headers).
  // I'm torn how to handle this case - should it fail instead?
  यदि (mz_zip_reader_is_file_a_directory(pZip, file_सूचकांक))
    प्रत्यागम MZ_TRUE;

  // Encryption and patch files are not supported.
  यदि (file_stat.m_bit_flag & (1 | 32))
    प्रत्यागम MZ_FALSE;

  // This function only supports stored and deflate.
  यदि ((!(flags & MZ_ZIP_FLAG_COMPRESSED_दत्त)) && (file_stat.m_विधानम् != 0) && (file_stat.m_विधानम् != MZ_DEFLATED))
    प्रत्यागम MZ_FALSE;

  // Read and parse the local directory entry.
  cur_file_ofs = file_stat.m_local_शीर्षकम्_ofs;
  यदि (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, p_Local_शीर्षकम्, MZ_ZIP_LOCAL_DIR_शीर्षकम्_आकार) != MZ_ZIP_LOCAL_DIR_शीर्षकम्_आकार)
    प्रत्यागम MZ_FALSE;
  यदि (MZ_READ_LE32(p_Local_शीर्षकम्) != MZ_ZIP_LOCAL_DIR_शीर्षकम्_SIG)
    प्रत्यागम MZ_FALSE;

  cur_file_ofs += MZ_ZIP_LOCAL_DIR_शीर्षकम्_आकार + MZ_READ_LE16(p_Local_शीर्षकम् + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p_Local_शीर्षकम् + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  यदि ((cur_file_ofs + file_stat.m_comp_आकार) > pZip->m_archive_आकार)
    प्रत्यागम MZ_FALSE;

  // Decompress the file either directly from memory or from a file input buffer.
  यदि (pZip->m_pState->m_pMem)
  {
    pRead_buf = (mz_uint8 *)pZip->m_pState->m_pMem + cur_file_ofs;
    read_buf_आकार = read_buf_avail = file_stat.m_comp_आकार;
    comp_remaining = 0;
  }
  अन्यथा
  {
    read_buf_आकार = MZ_MIN(file_stat.m_comp_आकार, MZ_ZIP_MAX_IO_BUF_आकार);
    यदि (रिक्त == (pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)read_buf_आकार)))
      प्रत्यागम MZ_FALSE;
    read_buf_avail = 0;
    comp_remaining = file_stat.m_comp_आकार;
  }

  यदि ((flags & MZ_ZIP_FLAG_COMPRESSED_दत्त) || (!file_stat.m_विधानम्))
  {
    // The file is stored or the caller has requested the compressed data.
    यदि (pZip->m_pState->m_pMem)
    {
#यदि_परिभाषितम् _MSC_VER
      यदि (((0, परिमाण(size_t) == परिमाण(mz_uint32))) && (file_stat.m_comp_आकार > 0xFFFFFFFF))
#अन्यथा
      यदि (((परिमाण(size_t) == परिमाण(mz_uint32))) && (file_stat.m_comp_आकार > 0xFFFFFFFF))
#यदि_अन्तः
        प्रत्यागम MZ_FALSE;
      यदि (pCallback(pOpaque, बहिर्गमनम्_buf_ofs, pRead_buf, (size_t)file_stat.m_comp_आकार) != file_stat.m_comp_आकार)
        स्थितिः = TINFL_स्थितिः_FAILED;
      अन्यथा यदि (!(flags & MZ_ZIP_FLAG_COMPRESSED_दत्त))
        file_चक्रीयपरीक्षा_32 = (mz_uint32)mz_चक्रीयपरीक्षा_32(file_चक्रीयपरीक्षा_32, (ध्रुव mz_uint8 *)pRead_buf, (size_t)file_stat.m_comp_आकार);
      cur_file_ofs += file_stat.m_comp_आकार;
      बहिर्गमनम्_buf_ofs += file_stat.m_comp_आकार;
      comp_remaining = 0;
    }
    अन्यथा
    {
      यावत् (comp_remaining)
      {
        read_buf_avail = MZ_MIN(read_buf_आकार, comp_remaining);
        यदि (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
        {
          स्थितिः = TINFL_स्थितिः_FAILED;
          भङ्ग;
        }

        यदि (!(flags & MZ_ZIP_FLAG_COMPRESSED_दत्त))
          file_चक्रीयपरीक्षा_32 = (mz_uint32)mz_चक्रीयपरीक्षा_32(file_चक्रीयपरीक्षा_32, (ध्रुव mz_uint8 *)pRead_buf, (size_t)read_buf_avail);

        यदि (pCallback(pOpaque, बहिर्गमनम्_buf_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
        {
          स्थितिः = TINFL_स्थितिः_FAILED;
          भङ्ग;
        }
        cur_file_ofs += read_buf_avail;
        बहिर्गमनम्_buf_ofs += read_buf_avail;
        comp_remaining -= read_buf_avail;
      }
    }
  }
  अन्यथा
  {
    tinfl_decompressor inflator;
    tinfl_init(&inflator);

    यदि (रिक्त == (pWrite_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, TINFL_LZ_DICT_आकार)))
      स्थितिः = TINFL_स्थितिः_FAILED;
    अन्यथा
    {
      कुरु
      {
        mz_uint8 *pWrite_buf_cur = (mz_uint8 *)pWrite_buf + (बहिर्गमनम्_buf_ofs & (TINFL_LZ_DICT_आकार - 1));
        size_t अन्तर्_buf_आकार, बहिर्गमनम्_buf_आकार = TINFL_LZ_DICT_आकार - (बहिर्गमनम्_buf_ofs & (TINFL_LZ_DICT_आकार - 1));
        यदि ((!read_buf_avail) && (!pZip->m_pState->m_pMem))
        {
          read_buf_avail = MZ_MIN(read_buf_आकार, comp_remaining);
          यदि (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
          {
            स्थितिः = TINFL_स्थितिः_FAILED;
            भङ्ग;
          }
          cur_file_ofs += read_buf_avail;
          comp_remaining -= read_buf_avail;
          read_buf_ofs = 0;
        }

        अन्तर्_buf_आकार = (size_t)read_buf_avail;
        स्थितिः = tinfl_decompress(&inflator, (ध्रुव mz_uint8 *)pRead_buf + read_buf_ofs, &अन्तर्_buf_आकार, (mz_uint8 *)pWrite_buf, pWrite_buf_cur, &बहिर्गमनम्_buf_आकार, comp_remaining ? TINFL_FLAG_HAS_अधिकम्_निवेशः : 0);
        read_buf_avail -= अन्तर्_buf_आकार;
        read_buf_ofs += अन्तर्_buf_आकार;

        यदि (बहिर्गमनम्_buf_आकार)
        {
          यदि (pCallback(pOpaque, बहिर्गमनम्_buf_ofs, pWrite_buf_cur, बहिर्गमनम्_buf_आकार) != बहिर्गमनम्_buf_आकार)
          {
            स्थितिः = TINFL_स्थितिः_FAILED;
            भङ्ग;
          }
          file_चक्रीयपरीक्षा_32 = (mz_uint32)mz_चक्रीयपरीक्षा_32(file_चक्रीयपरीक्षा_32, pWrite_buf_cur, बहिर्गमनम्_buf_आकार);
          यदि ((बहिर्गमनम्_buf_ofs += बहिर्गमनम्_buf_आकार) > file_stat.m_uncomp_आकार)
          {
            स्थितिः = TINFL_स्थितिः_FAILED;
            भङ्ग;
          }
        }
      } यावत् ((स्थितिः == TINFL_स्थितिः_NEEDS_अधिकम्_निवेशः) || (स्थितिः == TINFL_स्थितिः_HAS_अधिकम्_OUTPUT));
    }
  }

  यदि ((स्थितिः == TINFL_स्थितिः_समाप्तम्) && (!(flags & MZ_ZIP_FLAG_COMPRESSED_दत्त)))
  {
    // Make sure the entire file was decompressed, and check its CRC.
    यदि ((बहिर्गमनम्_buf_ofs != file_stat.m_uncomp_आकार) || (file_चक्रीयपरीक्षा_32 != file_stat.m_चक्रीयपरीक्षा_32))
      स्थितिः = TINFL_स्थितिः_FAILED;
  }

  यदि (!pZip->m_pState->m_pMem)
    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
  यदि (pWrite_buf)
    pZip->m_pFree(pZip->m_pAlloc_opaque, pWrite_buf);

  प्रत्यागम स्थितिः == TINFL_स्थितिः_समाप्तम्;
}

mz_bool mz_zip_reader_extract_file_गन्तव्यम्_callback(mz_zip_archive *pZip, ध्रुव वर्ण *pFilename, mz_file_write_func pCallback, शून्य *pOpaque, mz_uint flags)
{
  पूर्णाङ्क file_सूचकांक = mz_zip_reader_locate_file(pZip, pFilename, रिक्त, flags);
  यदि (file_सूचकांक < 0)
    प्रत्यागम MZ_FALSE;
  प्रत्यागम mz_zip_reader_extract_गन्तव्यम्_callback(pZip, file_सूचकांक, pCallback, pOpaque, flags);
}

#यदि_अपरिभाषितम् MINIZ_NO_STDIO
स्थिर size_t mz_zip_file_write_callback(शून्य *pOpaque, mz_uint64 ofs, ध्रुव शून्य *pBuf, size_t n)
{
  (शून्य)ofs; प्रत्यागम MZ_FWRITE(pBuf, 1, n, (MZ_FILE*)pOpaque);
}

mz_bool mz_zip_reader_extract_गन्तव्यम्_file(mz_zip_archive *pZip, mz_uint file_सूचकांक, ध्रुव वर्ण *pDst_filename, mz_uint flags)
{
  mz_bool स्थितिः;
  mz_zip_archive_file_stat file_stat;
  MZ_FILE *pFile;
  यदि (!mz_zip_reader_file_stat(pZip, file_सूचकांक, &file_stat))
    प्रत्यागम MZ_FALSE;
  pFile = MZ_FOPEN(pDst_filename, "wb");
  यदि (!pFile)
    प्रत्यागम MZ_FALSE;
  स्थितिः = mz_zip_reader_extract_गन्तव्यम्_callback(pZip, file_सूचकांक, mz_zip_file_write_callback, pFile, flags);
  यदि (MZ_FCLOSE(pFile) == EOF)
    प्रत्यागम MZ_FALSE;
#यदि_अपरिभाषितम् MINIZ_NO_TIME
  यदि (स्थितिः)
    mz_zip_समुच्चयः_file_times(pDst_filename, file_stat.m_time, file_stat.m_time);
#यदि_अन्तः
  प्रत्यागम स्थितिः;
}
#यदि_अन्तः // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_reader_अन्तः(mz_zip_archive *pZip)
{
  यदि ((!pZip) || (!pZip->m_pState) || (!pZip->m_pAlloc) || (!pZip->m_pFree) || (pZip->m_zip_बहुलकम् != MZ_ZIP_बहुलकम्_READING))
    प्रत्यागम MZ_FALSE;

  यदि (pZip->m_pState)
  {
    mz_zip_आन्तरिकम्_state *pState = pZip->m_pState; pZip->m_pState = रिक्त;
    mz_zip_array_clear(pZip, &pState->m_central_dir);
    mz_zip_array_clear(pZip, &pState->m_central_dir_offsets);
    mz_zip_array_clear(pZip, &pState->m_sorted_central_dir_offsets);

#यदि_अपरिभाषितम् MINIZ_NO_STDIO
    यदि (pState->m_pFile)
    {
      MZ_FCLOSE(pState->m_pFile);
      pState->m_pFile = रिक्त;
    }
#यदि_अन्तः // #ifndef MINIZ_NO_STDIO

    pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
  }
  pZip->m_zip_बहुलकम् = MZ_ZIP_बहुलकम्_INVALID;

  प्रत्यागम MZ_TRUE;
}

#यदि_अपरिभाषितम् MINIZ_NO_STDIO
mz_bool mz_zip_reader_extract_file_गन्तव्यम्_file(mz_zip_archive *pZip, ध्रुव वर्ण *pArchive_filename, ध्रुव वर्ण *pDst_filename, mz_uint flags)
{
  पूर्णाङ्क file_सूचकांक = mz_zip_reader_locate_file(pZip, pArchive_filename, रिक्त, flags);
  यदि (file_सूचकांक < 0)
    प्रत्यागम MZ_FALSE;
  प्रत्यागम mz_zip_reader_extract_गन्तव्यम्_file(pZip, file_सूचकांक, pDst_filename, flags);
}
#यदि_अन्तः

// ------------------- .ZIP archive writing

#यदि_अपरिभाषितम् MINIZ_NO_ARCHIVE_WRITING_APIS

स्थिर शून्य mz_write_le16(mz_uint8 *p, mz_uint16 v) { p[0] = (mz_uint8)v; p[1] = (mz_uint8)(v >> 8); }
स्थिर शून्य mz_write_le32(mz_uint8 *p, mz_uint32 v) { p[0] = (mz_uint8)v; p[1] = (mz_uint8)(v >> 8); p[2] = (mz_uint8)(v >> 16); p[3] = (mz_uint8)(v >> 24); }
#परिभाषय MZ_WRITE_LE16(p, v) mz_write_le16((mz_uint8 *)(p), (mz_uint16)(v))
#परिभाषय MZ_WRITE_LE32(p, v) mz_write_le32((mz_uint8 *)(p), (mz_uint32)(v))

mz_bool mz_zip_writer_init(mz_zip_archive *pZip, mz_uint64 existing_आकार)
{
  यदि ((!pZip) || (pZip->m_pState) || (!pZip->m_pWrite) || (pZip->m_zip_बहुलकम् != MZ_ZIP_बहुलकम्_INVALID))
    प्रत्यागम MZ_FALSE;

  यदि (pZip->m_file_विस्थापनम्_alignment)
  {
    // Ensure user specified file offset alignment is a power of 2.
    यदि (pZip->m_file_विस्थापनम्_alignment & (pZip->m_file_विस्थापनम्_alignment - 1))
      प्रत्यागम MZ_FALSE;
  }

  यदि (!pZip->m_pAlloc) pZip->m_pAlloc = def_alloc_func;
  यदि (!pZip->m_pFree) pZip->m_pFree = def_free_func;
  यदि (!pZip->m_pRealloc) pZip->m_pRealloc = def_realloc_func;

  pZip->m_zip_बहुलकम् = MZ_ZIP_बहुलकम्_WRITING;
  pZip->m_archive_आकार = existing_आकार;
  pZip->m_central_directory_file_ofs = 0;
  pZip->m_योग_files = 0;

  यदि (रिक्त == (pZip->m_pState = (mz_zip_आन्तरिकम्_state *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, परिमाण(mz_zip_आन्तरिकम्_state))))
    प्रत्यागम MZ_FALSE;
  स्मृतिं_पूरय(pZip->m_pState, 0, परिमाण(mz_zip_आन्तरिकम्_state));
  MZ_ZIP_ARRAY_समुच्चयः_ELEMENT_आकार(&pZip->m_pState->m_central_dir, परिमाण(mz_uint8));
  MZ_ZIP_ARRAY_समुच्चयः_ELEMENT_आकार(&pZip->m_pState->m_central_dir_offsets, परिमाण(mz_uint32));
  MZ_ZIP_ARRAY_समुच्चयः_ELEMENT_आकार(&pZip->m_pState->m_sorted_central_dir_offsets, परिमाण(mz_uint32));
  प्रत्यागम MZ_TRUE;
}

स्थिर size_t mz_zip_heap_write_func(शून्य *pOpaque, mz_uint64 file_ofs, ध्रुव शून्य *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_zip_आन्तरिकम्_state *pState = pZip->m_pState;
  mz_uint64 new_आकार = MZ_MAX(file_ofs + n, pState->m_mem_आकार);
#यदि_परिभाषितम् _MSC_VER
  यदि ((!n) || ((0, परिमाण(size_t) == परिमाण(mz_uint32)) && (new_आकार > 0x7FFFFFFF)))
#अन्यथा
  यदि ((!n) || ((परिमाण(size_t) == परिमाण(mz_uint32)) && (new_आकार > 0x7FFFFFFF)))
#यदि_अन्तः
    प्रत्यागम 0;
  यदि (new_आकार > pState->m_mem_क्षमता)
  {
    शून्य *p_New_खण्डम्;
    size_t new_क्षमता = MZ_MAX(64, pState->m_mem_क्षमता); यावत् (new_क्षमता < new_आकार) new_क्षमता *= 2;
    यदि (रिक्त == (p_New_खण्डम् = pZip->m_pRealloc(pZip->m_pAlloc_opaque, pState->m_pMem, 1, new_क्षमता)))
      प्रत्यागम 0;
    pState->m_pMem = p_New_खण्डम्; pState->m_mem_क्षमता = new_क्षमता;
  }
  स्मृतिं_प्रतिलिख((mz_uint8 *)pState->m_pMem + file_ofs, pBuf, n);
  pState->m_mem_आकार = (size_t)new_आकार;
  प्रत्यागम n;
}

mz_bool mz_zip_writer_init_heap(mz_zip_archive *pZip, size_t आकार_गन्तव्यम्_reserve_at_beginning, size_t initial_आवण्टनम्_आकार)
{
  pZip->m_pWrite = mz_zip_heap_write_func;
  pZip->m_pIO_opaque = pZip;
  यदि (!mz_zip_writer_init(pZip, आकार_गन्तव्यम्_reserve_at_beginning))
    प्रत्यागम MZ_FALSE;
  यदि (0 != (initial_आवण्टनम्_आकार = MZ_MAX(initial_आवण्टनम्_आकार, आकार_गन्तव्यम्_reserve_at_beginning)))
  {
    यदि (रिक्त == (pZip->m_pState->m_pMem = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, initial_आवण्टनम्_आकार)))
    {
      mz_zip_writer_अन्तः(pZip);
      प्रत्यागम MZ_FALSE;
    }
    pZip->m_pState->m_mem_क्षमता = initial_आवण्टनम्_आकार;
  }
  प्रत्यागम MZ_TRUE;
}

#यदि_अपरिभाषितम् MINIZ_NO_STDIO
स्थिर size_t mz_zip_file_write_func(शून्य *pOpaque, mz_uint64 file_ofs, ध्रुव शून्य *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_int64 cur_ofs = MZ_FTELL64(pZip->m_pState->m_pFile);
  यदि (((mz_int64)file_ofs < 0) || (((cur_ofs != (mz_int64)file_ofs)) && (MZ_FSEEK64(pZip->m_pState->m_pFile, (mz_int64)file_ofs, SEEK_SET))))
    प्रत्यागम 0;
  प्रत्यागम MZ_FWRITE(pBuf, 1, n, pZip->m_pState->m_pFile);
}

mz_bool mz_zip_writer_init_file(mz_zip_archive *pZip, ध्रुव वर्ण *pFilename, mz_uint64 आकार_गन्तव्यम्_reserve_at_beginning)
{
  MZ_FILE *pFile;
  pZip->m_pWrite = mz_zip_file_write_func;
  pZip->m_pIO_opaque = pZip;
  यदि (!mz_zip_writer_init(pZip, आकार_गन्तव्यम्_reserve_at_beginning))
    प्रत्यागम MZ_FALSE;
  यदि (रिक्त == (pFile = MZ_FOPEN(pFilename, "wb")))
  {
    mz_zip_writer_अन्तः(pZip);
    प्रत्यागम MZ_FALSE;
  }
  pZip->m_pState->m_pFile = pFile;
  यदि (आकार_गन्तव्यम्_reserve_at_beginning)
  {
    mz_uint64 cur_ofs = 0; वर्ण buf[4096]; MZ_CLEAR_ARR(buf);
    कुरु
    {
      size_t n = (size_t)MZ_MIN(परिमाण(buf), आकार_गन्तव्यम्_reserve_at_beginning);
      यदि (pZip->m_pWrite(pZip->m_pIO_opaque, cur_ofs, buf, n) != n)
      {
        mz_zip_writer_अन्तः(pZip);
        प्रत्यागम MZ_FALSE;
      }
      cur_ofs += n; आकार_गन्तव्यम्_reserve_at_beginning -= n;
    } यावत् (आकार_गन्तव्यम्_reserve_at_beginning);
  }
  प्रत्यागम MZ_TRUE;
}
#यदि_अन्तः // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_writer_init_from_reader(mz_zip_archive *pZip, ध्रुव वर्ण *pFilename)
{
  mz_zip_आन्तरिकम्_state *pState;
  यदि ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_बहुलकम् != MZ_ZIP_बहुलकम्_READING))
    प्रत्यागम MZ_FALSE;
  // No sense in trying to write to an archive that's already at the support max size
  यदि ((pZip->m_योग_files == 0xFFFF) || ((pZip->m_archive_आकार + MZ_ZIP_CENTRAL_DIR_शीर्षकम्_आकार + MZ_ZIP_LOCAL_DIR_शीर्षकम्_आकार) > 0xFFFFFFFF))
    प्रत्यागम MZ_FALSE;

  pState = pZip->m_pState;

  यदि (pState->m_pFile)
  {
#यदि_परिभाषितम् MINIZ_NO_STDIO
    pFilename; प्रत्यागम MZ_FALSE;
#अन्यथा
    // Archive is being read from stdio - try to reopen as writable.
    यदि (pZip->m_pIO_opaque != pZip)
      प्रत्यागम MZ_FALSE;
    यदि (!pFilename)
      प्रत्यागम MZ_FALSE;
    pZip->m_pWrite = mz_zip_file_write_func;
    यदि (रिक्त == (pState->m_pFile = MZ_FREOPEN(pFilename, "r+b", pState->m_pFile)))
    {
      // The mz_zip_archive is now in a bogus state because pState->m_pFile is NULL, so just close it.
      mz_zip_reader_अन्तः(pZip);
      प्रत्यागम MZ_FALSE;
    }
#यदि_अन्तः // #ifdef MINIZ_NO_STDIO
  }
  अन्यथा यदि (pState->m_pMem)
  {
    // Archive lives in a memory block. Assume it's from the heap that we can resize using the realloc callback.
    यदि (pZip->m_pIO_opaque != pZip)
      प्रत्यागम MZ_FALSE;
    pState->m_mem_क्षमता = pState->m_mem_आकार;
    pZip->m_pWrite = mz_zip_heap_write_func;
  }
  // Archive is being read via a user provided read function - make sure the user has specified a write function too.
  अन्यथा यदि (!pZip->m_pWrite)
    प्रत्यागम MZ_FALSE;

  // Start writing new files at the archive's current central directory location.
  pZip->m_archive_आकार = pZip->m_central_directory_file_ofs;
  pZip->m_zip_बहुलकम् = MZ_ZIP_बहुलकम्_WRITING;
  pZip->m_central_directory_file_ofs = 0;

  प्रत्यागम MZ_TRUE;
}

mz_bool mz_zip_writer_सङ्कलय_mem(mz_zip_archive *pZip, ध्रुव वर्ण *pArchive_name, ध्रुव शून्य *pBuf, size_t buf_आकार_2, mz_uint level_and_flags)
{
  प्रत्यागम mz_zip_writer_सङ्कलय_mem_ex(pZip, pArchive_name, pBuf, buf_आकार_2, रिक्त, 0, level_and_flags, 0, 0);
}

प्रकारनिर्देश संरचना
{
  mz_zip_archive *m_pZip;
  mz_uint64 m_cur_archive_file_ofs;
  mz_uint64 m_comp_आकार;
} mz_zip_writer_सङ्कलय_state;

स्थिर mz_bool mz_zip_writer_सङ्कलय_put_buf_callback(ध्रुव शून्य* pBuf, पूर्णाङ्क len, शून्य *pUser)
{
  mz_zip_writer_सङ्कलय_state *pState = (mz_zip_writer_सङ्कलय_state *)pUser;
  यदि ((पूर्णाङ्क)pState->m_pZip->m_pWrite(pState->m_pZip->m_pIO_opaque, pState->m_cur_archive_file_ofs, pBuf, len) != len)
    प्रत्यागम MZ_FALSE;
  pState->m_cur_archive_file_ofs += len;
  pState->m_comp_आकार += len;
  प्रत्यागम MZ_TRUE;
}

स्थिर mz_bool mz_zip_writer_create_local_dir_शीर्षकम्(mz_zip_archive *pZip, mz_uint8 *pDst, mz_uint16 filename_आकार, mz_uint16 extra_आकार, mz_uint64 uncomp_आकार, mz_uint64 comp_आकार, mz_uint32 uncomp_चक्रीयपरीक्षा_32, mz_uint16 विधानम्, mz_uint16 bit_flags, mz_uint16 dos_time, mz_uint16 dos_date)
{
  (शून्य)pZip;
  स्मृतिं_पूरय(pDst, 0, MZ_ZIP_LOCAL_DIR_शीर्षकम्_आकार);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_SIG_OFS, MZ_ZIP_LOCAL_DIR_शीर्षकम्_SIG);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_संस्करणम्_NEEDED_OFS, विधानम् ? 20 : 0);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_BIT_FLAG_OFS, bit_flags);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_विधानम्_OFS, विधानम्);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILE_TIME_OFS, dos_time);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILE_DATE_OFS, dos_date);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_चक्रीयपरीक्षा_32_OFS, uncomp_चक्रीयपरीक्षा_32);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_COMPRESSED_आकार_OFS, comp_आकार);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_DECOMPRESSED_आकार_OFS, uncomp_आकार);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILENAME_LEN_OFS, filename_आकार);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_EXTRA_LEN_OFS, extra_आकार);
  प्रत्यागम MZ_TRUE;
}

स्थिर mz_bool mz_zip_writer_create_central_dir_शीर्षकम्(mz_zip_archive *pZip, mz_uint8 *pDst, mz_uint16 filename_आकार, mz_uint16 extra_आकार, mz_uint16 comment_आकार, mz_uint64 uncomp_आकार, mz_uint64 comp_आकार, mz_uint32 uncomp_चक्रीयपरीक्षा_32, mz_uint16 विधानम्, mz_uint16 bit_flags, mz_uint16 dos_time, mz_uint16 dos_date, mz_uint64 local_शीर्षकम्_ofs, mz_uint32 ext_गुणाः)
{
  (शून्य)pZip;
  स्मृतिं_पूरय(pDst, 0, MZ_ZIP_CENTRAL_DIR_शीर्षकम्_आकार);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_SIG_OFS, MZ_ZIP_CENTRAL_DIR_शीर्षकम्_SIG);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_संस्करणम्_NEEDED_OFS, विधानम् ? 20 : 0);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_BIT_FLAG_OFS, bit_flags);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_विधानम्_OFS, विधानम्);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILE_TIME_OFS, dos_time);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILE_DATE_OFS, dos_date);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_चक्रीयपरीक्षा_32_OFS, uncomp_चक्रीयपरीक्षा_32);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_COMPRESSED_आकार_OFS, comp_आकार);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_DECOMPRESSED_आकार_OFS, uncomp_आकार);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILENAME_LEN_OFS, filename_आकार);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_EXTRA_LEN_OFS, extra_आकार);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_COMMENT_LEN_OFS, comment_आकार);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS, ext_गुणाः);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_LOCAL_शीर्षकम्_OFS, local_शीर्षकम्_ofs);
  प्रत्यागम MZ_TRUE;
}

स्थिर mz_bool mz_zip_writer_सङ्कलय_गन्तव्यम्_central_dir(mz_zip_archive *pZip, ध्रुव वर्ण *pFilename, mz_uint16 filename_आकार, ध्रुव शून्य *pExtra, mz_uint16 extra_आकार, ध्रुव शून्य *pComment, mz_uint16 comment_आकार, mz_uint64 uncomp_आकार, mz_uint64 comp_आकार, mz_uint32 uncomp_चक्रीयपरीक्षा_32, mz_uint16 विधानम्, mz_uint16 bit_flags, mz_uint16 dos_time, mz_uint16 dos_date, mz_uint64 local_शीर्षकम्_ofs, mz_uint32 ext_गुणाः)
{
  mz_zip_आन्तरिकम्_state *pState = pZip->m_pState;
  mz_uint32 central_dir_ofs = (mz_uint32)pState->m_central_dir.m_आकार;
  size_t orig_central_dir_आकार = pState->m_central_dir.m_आकार;
  mz_uint8 central_dir_शीर्षकम्[MZ_ZIP_CENTRAL_DIR_शीर्षकम्_आकार];

  // No zip64 support yet
  यदि ((local_शीर्षकम्_ofs > 0xFFFFFFFF) || (((mz_uint64)pState->m_central_dir.m_आकार + MZ_ZIP_CENTRAL_DIR_शीर्षकम्_आकार + filename_आकार + extra_आकार + comment_आकार) > 0xFFFFFFFF))
    प्रत्यागम MZ_FALSE;

  यदि (!mz_zip_writer_create_central_dir_शीर्षकम्(pZip, central_dir_शीर्षकम्, filename_आकार, extra_आकार, comment_आकार, uncomp_आकार, comp_आकार, uncomp_चक्रीयपरीक्षा_32, विधानम्, bit_flags, dos_time, dos_date, local_शीर्षकम्_ofs, ext_गुणाः))
    प्रत्यागम MZ_FALSE;

  यदि ((!mz_zip_array_प्रक्षिप_पृष्ठभागः(pZip, &pState->m_central_dir, central_dir_शीर्षकम्, MZ_ZIP_CENTRAL_DIR_शीर्षकम्_आकार)) ||
      (!mz_zip_array_प्रक्षिप_पृष्ठभागः(pZip, &pState->m_central_dir, pFilename, filename_आकार)) ||
      (!mz_zip_array_प्रक्षिप_पृष्ठभागः(pZip, &pState->m_central_dir, pExtra, extra_आकार)) ||
      (!mz_zip_array_प्रक्षिप_पृष्ठभागः(pZip, &pState->m_central_dir, pComment, comment_आकार)) ||
      (!mz_zip_array_प्रक्षिप_पृष्ठभागः(pZip, &pState->m_central_dir_offsets, &central_dir_ofs, 1)))
  {
    // Try to push the central directory array back into its original state.
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_आकार, MZ_FALSE);
    प्रत्यागम MZ_FALSE;
  }

  प्रत्यागम MZ_TRUE;
}

स्थिर mz_bool mz_zip_writer_validate_archive_name(ध्रुव वर्ण *pArchive_name)
{
  // Basic ZIP archive filename validity checks: Valid filenames cannot start with a forward slash, cannot contain a drive letter, and cannot use DOS-style backward slashes.
  यदि (*pArchive_name == '/')
    प्रत्यागम MZ_FALSE;
  यावत् (*pArchive_name)
  {
    यदि ((*pArchive_name == '\\') || (*pArchive_name == ':'))
      प्रत्यागम MZ_FALSE;
    pArchive_name++;
  }
  प्रत्यागम MZ_TRUE;
}

स्थिर mz_uint mz_zip_writer_compute_padding_needed_for_file_alignment(mz_zip_archive *pZip)
{
  mz_uint32 n;
  यदि (!pZip->m_file_विस्थापनम्_alignment)
    प्रत्यागम 0;
  n = (mz_uint32)(pZip->m_archive_आकार & (pZip->m_file_विस्थापनम्_alignment - 1));
  प्रत्यागम (pZip->m_file_विस्थापनम्_alignment - n) & (pZip->m_file_विस्थापनम्_alignment - 1);
}

स्थिर mz_bool mz_zip_writer_write_zeros(mz_zip_archive *pZip, mz_uint64 cur_file_ofs, mz_uint32 n)
{
  वर्ण buf[4096];
  स्मृतिं_पूरय(buf, 0, MZ_MIN(परिमाण(buf), n));
  यावत् (n)
  {
    mz_uint32 s = MZ_MIN(परिमाण(buf), n);
    यदि (pZip->m_pWrite(pZip->m_pIO_opaque, cur_file_ofs, buf, s) != s)
      प्रत्यागम MZ_FALSE;
    cur_file_ofs += s; n -= s;
  }
  प्रत्यागम MZ_TRUE;
}

mz_bool mz_zip_writer_सङ्कलय_mem_ex(mz_zip_archive *pZip, ध्रुव वर्ण *pArchive_name, ध्रुव शून्य *pBuf, size_t buf_आकार_2, ध्रुव शून्य *pComment, mz_uint16 comment_आकार, mz_uint level_and_flags, mz_uint64 uncomp_आकार, mz_uint32 uncomp_चक्रीयपरीक्षा_32)
{
  mz_uint16 विधानम् = 0, dos_time = 0, dos_date = 0;
  mz_uint level, ext_गुणाः = 0, अङ्कः_alignment_padding_अष्टकानि;
  mz_uint64 local_dir_शीर्षकम्_ofs = pZip->m_archive_आकार, cur_archive_file_ofs = pZip->m_archive_आकार, comp_आकार = 0;
  size_t archive_name_आकार;
  mz_uint8 local_dir_शीर्षकम्[MZ_ZIP_LOCAL_DIR_शीर्षकम्_आकार];
  tdefl_compressor *pComp = रिक्त;
  mz_bool store_दत्त_uncompressed;
  mz_zip_आन्तरिकम्_state *pState;

  यदि ((पूर्णाङ्क)level_and_flags < 0)
    level_and_flags = MZ_DEFAULT_LEVEL;
  level = level_and_flags & 0xF;
  store_दत्त_uncompressed = ((!level) || (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_दत्त));

  यदि ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_बहुलकम् != MZ_ZIP_बहुलकम्_WRITING) || ((buf_आकार_2) && (!pBuf)) || (!pArchive_name) || ((comment_आकार) && (!pComment)) || (pZip->m_योग_files == 0xFFFF) || (level > MZ_UBER_COMPRESSION))
    प्रत्यागम MZ_FALSE;

  pState = pZip->m_pState;

  यदि ((!(level_and_flags & MZ_ZIP_FLAG_COMPRESSED_दत्त)) && (uncomp_आकार))
    प्रत्यागम MZ_FALSE;
  // No zip64 support yet
  यदि ((buf_आकार_2 > 0xFFFFFFFF) || (uncomp_आकार > 0xFFFFFFFF))
    प्रत्यागम MZ_FALSE;
  यदि (!mz_zip_writer_validate_archive_name(pArchive_name))
    प्रत्यागम MZ_FALSE;

#यदि_अपरिभाषितम् MINIZ_NO_TIME
  {
    time_t cur_time; time(&cur_time);
    mz_zip_time_गन्तव्यम्_dos_time(cur_time, &dos_time, &dos_date);
  }
#यदि_अन्तः // #ifndef MINIZ_NO_TIME

  archive_name_आकार = वाक्यदैर्घ्यम्(pArchive_name);
  यदि (archive_name_आकार > 0xFFFF)
    प्रत्यागम MZ_FALSE;

  अङ्कः_alignment_padding_अष्टकानि = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  यदि ((pZip->m_योग_files == 0xFFFF) || ((pZip->m_archive_आकार + अङ्कः_alignment_padding_अष्टकानि + MZ_ZIP_LOCAL_DIR_शीर्षकम्_आकार + MZ_ZIP_CENTRAL_DIR_शीर्षकम्_आकार + comment_आकार + archive_name_आकार) > 0xFFFFFFFF))
    प्रत्यागम MZ_FALSE;

  यदि ((archive_name_आकार) && (pArchive_name[archive_name_आकार - 1] == '/'))
  {
    // Set DOS Subdirectory attribute bit.
    ext_गुणाः |= 0x10;
    // Subdirectories cannot contain data.
    यदि ((buf_आकार_2) || (uncomp_आकार))
      प्रत्यागम MZ_FALSE;
  }

  // Try to do any allocations before writing to the archive, so if an allocation fails the file remains unmodified. (A good idea if we're doing an in-place modification.)
  यदि ((!mz_zip_array_ensure_अवकाशः(pZip, &pState->m_central_dir, MZ_ZIP_CENTRAL_DIR_शीर्षकम्_आकार + archive_name_आकार + comment_आकार)) || (!mz_zip_array_ensure_अवकाशः(pZip, &pState->m_central_dir_offsets, 1)))
    प्रत्यागम MZ_FALSE;

  यदि ((!store_दत्त_uncompressed) && (buf_आकार_2))
  {
    यदि (रिक्त == (pComp = (tdefl_compressor *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, परिमाण(tdefl_compressor))))
      प्रत्यागम MZ_FALSE;
  }

  यदि (!mz_zip_writer_write_zeros(pZip, cur_archive_file_ofs, अङ्कः_alignment_padding_अष्टकानि + परिमाण(local_dir_शीर्षकम्)))
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
    प्रत्यागम MZ_FALSE;
  }
  local_dir_शीर्षकम्_ofs += अङ्कः_alignment_padding_अष्टकानि;
  यदि (pZip->m_file_विस्थापनम्_alignment) { MZ_ASSERT((local_dir_शीर्षकम्_ofs & (pZip->m_file_विस्थापनम्_alignment - 1)) == 0); }
  cur_archive_file_ofs += अङ्कः_alignment_padding_अष्टकानि + परिमाण(local_dir_शीर्षकम्);

  MZ_CLEAR_ARR(local_dir_शीर्षकम्);
  यदि (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pArchive_name, archive_name_आकार) != archive_name_आकार)
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
    प्रत्यागम MZ_FALSE;
  }
  cur_archive_file_ofs += archive_name_आकार;

  यदि (!(level_and_flags & MZ_ZIP_FLAG_COMPRESSED_दत्त))
  {
    uncomp_चक्रीयपरीक्षा_32 = (mz_uint32)mz_चक्रीयपरीक्षा_32(MZ_चक्रीयपरीक्षा_32_INIT, (ध्रुव mz_uint8*)pBuf, buf_आकार_2);
    uncomp_आकार = buf_आकार_2;
    यदि (uncomp_आकार <= 3)
    {
      level = 0;
      store_दत्त_uncompressed = MZ_TRUE;
    }
  }

  यदि (store_दत्त_uncompressed)
  {
    यदि (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pBuf, buf_आकार_2) != buf_आकार_2)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
      प्रत्यागम MZ_FALSE;
    }

    cur_archive_file_ofs += buf_आकार_2;
    comp_आकार = buf_आकार_2;

    यदि (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_दत्त)
      विधानम् = MZ_DEFLATED;
  }
  अन्यथा यदि (buf_आकार_2)
  {
    mz_zip_writer_सङ्कलय_state state;

    state.m_pZip = pZip;
    state.m_cur_archive_file_ofs = cur_archive_file_ofs;
    state.m_comp_आकार = 0;

    यदि ((tdefl_init(pComp, mz_zip_writer_सङ्कलय_put_buf_callback, &state, tdefl_create_comp_flags_from_zip_params(level, -15, MZ_DEFAULT_STRATEGY)) != TDEFL_स्थितिः_OKAY) ||
        (tdefl_compress_बफर(pComp, pBuf, buf_आकार_2, TDEFL_FINISH) != TDEFL_स्थितिः_समाप्तम्))
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
      प्रत्यागम MZ_FALSE;
    }

    comp_आकार = state.m_comp_आकार;
    cur_archive_file_ofs = state.m_cur_archive_file_ofs;

    विधानम् = MZ_DEFLATED;
  }

  pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
  pComp = रिक्त;

  // no zip64 support yet
  यदि ((comp_आकार > 0xFFFFFFFF) || (cur_archive_file_ofs > 0xFFFFFFFF))
    प्रत्यागम MZ_FALSE;

  यदि (!mz_zip_writer_create_local_dir_शीर्षकम्(pZip, local_dir_शीर्षकम्, (mz_uint16)archive_name_आकार, 0, uncomp_आकार, comp_आकार, uncomp_चक्रीयपरीक्षा_32, विधानम्, 0, dos_time, dos_date))
    प्रत्यागम MZ_FALSE;

  यदि (pZip->m_pWrite(pZip->m_pIO_opaque, local_dir_शीर्षकम्_ofs, local_dir_शीर्षकम्, परिमाण(local_dir_शीर्षकम्)) != परिमाण(local_dir_शीर्षकम्))
    प्रत्यागम MZ_FALSE;

  यदि (!mz_zip_writer_सङ्कलय_गन्तव्यम्_central_dir(pZip, pArchive_name, (mz_uint16)archive_name_आकार, रिक्त, 0, pComment, comment_आकार, uncomp_आकार, comp_आकार, uncomp_चक्रीयपरीक्षा_32, विधानम्, 0, dos_time, dos_date, local_dir_शीर्षकम्_ofs, ext_गुणाः))
    प्रत्यागम MZ_FALSE;

  pZip->m_योग_files++;
  pZip->m_archive_आकार = cur_archive_file_ofs;

  प्रत्यागम MZ_TRUE;
}

#यदि_अपरिभाषितम् MINIZ_NO_STDIO
mz_bool mz_zip_writer_सङ्कलय_file(mz_zip_archive *pZip, ध्रुव वर्ण *pArchive_name, ध्रुव वर्ण *pSrc_filename, ध्रुव शून्य *pComment, mz_uint16 comment_आकार, mz_uint level_and_flags)
{
  mz_uint uncomp_चक्रीयपरीक्षा_32 = MZ_चक्रीयपरीक्षा_32_INIT, level, अङ्कः_alignment_padding_अष्टकानि;
  mz_uint16 विधानम् = 0, dos_time = 0, dos_date = 0, ext_गुणाः = 0;
  mz_uint64 local_dir_शीर्षकम्_ofs = pZip->m_archive_आकार, cur_archive_file_ofs = pZip->m_archive_आकार, uncomp_आकार = 0, comp_आकार = 0;
  size_t archive_name_आकार;
  mz_uint8 local_dir_शीर्षकम्[MZ_ZIP_LOCAL_DIR_शीर्षकम्_आकार];
  MZ_FILE *pSrc_file = रिक्त;

  यदि ((पूर्णाङ्क)level_and_flags < 0)
    level_and_flags = MZ_DEFAULT_LEVEL;
  level = level_and_flags & 0xF;

  यदि ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_बहुलकम् != MZ_ZIP_बहुलकम्_WRITING) || (!pArchive_name) || ((comment_आकार) && (!pComment)) || (level > MZ_UBER_COMPRESSION))
    प्रत्यागम MZ_FALSE;
  यदि (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_दत्त)
    प्रत्यागम MZ_FALSE;
  यदि (!mz_zip_writer_validate_archive_name(pArchive_name))
    प्रत्यागम MZ_FALSE;

  archive_name_आकार = वाक्यदैर्घ्यम्(pArchive_name);
  यदि (archive_name_आकार > 0xFFFF)
    प्रत्यागम MZ_FALSE;

  अङ्कः_alignment_padding_अष्टकानि = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  यदि ((pZip->m_योग_files == 0xFFFF) || ((pZip->m_archive_आकार + अङ्कः_alignment_padding_अष्टकानि + MZ_ZIP_LOCAL_DIR_शीर्षकम्_आकार + MZ_ZIP_CENTRAL_DIR_शीर्षकम्_आकार + comment_आकार + archive_name_आकार) > 0xFFFFFFFF))
    प्रत्यागम MZ_FALSE;

  यदि (!mz_zip_get_file_modified_time(pSrc_filename, &dos_time, &dos_date))
    प्रत्यागम MZ_FALSE;

  pSrc_file = MZ_FOPEN(pSrc_filename, "rb");
  यदि (!pSrc_file)
    प्रत्यागम MZ_FALSE;
  MZ_FSEEK64(pSrc_file, 0, SEEK_END);
  uncomp_आकार = MZ_FTELL64(pSrc_file);
  MZ_FSEEK64(pSrc_file, 0, SEEK_SET);

  यदि (uncomp_आकार > 0xFFFFFFFF)
  {
    // No zip64 support yet
    MZ_FCLOSE(pSrc_file);
    प्रत्यागम MZ_FALSE;
  }
  यदि (uncomp_आकार <= 3)
    level = 0;

  यदि (!mz_zip_writer_write_zeros(pZip, cur_archive_file_ofs, अङ्कः_alignment_padding_अष्टकानि + परिमाण(local_dir_शीर्षकम्)))
  {
    MZ_FCLOSE(pSrc_file);
    प्रत्यागम MZ_FALSE;
  }
  local_dir_शीर्षकम्_ofs += अङ्कः_alignment_padding_अष्टकानि;
  यदि (pZip->m_file_विस्थापनम्_alignment) { MZ_ASSERT((local_dir_शीर्षकम्_ofs & (pZip->m_file_विस्थापनम्_alignment - 1)) == 0); }
  cur_archive_file_ofs += अङ्कः_alignment_padding_अष्टकानि + परिमाण(local_dir_शीर्षकम्);

  MZ_CLEAR_ARR(local_dir_शीर्षकम्);
  यदि (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pArchive_name, archive_name_आकार) != archive_name_आकार)
  {
    MZ_FCLOSE(pSrc_file);
    प्रत्यागम MZ_FALSE;
  }
  cur_archive_file_ofs += archive_name_आकार;

  यदि (uncomp_आकार)
  {
    mz_uint64 uncomp_remaining = uncomp_आकार;
    शून्य *pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, MZ_ZIP_MAX_IO_BUF_आकार);
    यदि (!pRead_buf)
    {
      MZ_FCLOSE(pSrc_file);
      प्रत्यागम MZ_FALSE;
    }

    यदि (!level)
    {
      यावत् (uncomp_remaining)
      {
        mz_uint n = (mz_uint)MZ_MIN(MZ_ZIP_MAX_IO_BUF_आकार, uncomp_remaining);
        यदि ((MZ_FREAD(pRead_buf, 1, n, pSrc_file) != n) || (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pRead_buf, n) != n))
        {
          pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
          MZ_FCLOSE(pSrc_file);
          प्रत्यागम MZ_FALSE;
        }
        uncomp_चक्रीयपरीक्षा_32 = (mz_uint32)mz_चक्रीयपरीक्षा_32(uncomp_चक्रीयपरीक्षा_32, (ध्रुव mz_uint8 *)pRead_buf, n);
        uncomp_remaining -= n;
        cur_archive_file_ofs += n;
      }
      comp_आकार = uncomp_आकार;
    }
    अन्यथा
    {
      mz_bool परिणाम = MZ_FALSE;
      mz_zip_writer_सङ्कलय_state state;
      tdefl_compressor *pComp = (tdefl_compressor *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, परिमाण(tdefl_compressor));
      यदि (!pComp)
      {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        प्रत्यागम MZ_FALSE;
      }

      state.m_pZip = pZip;
      state.m_cur_archive_file_ofs = cur_archive_file_ofs;
      state.m_comp_आकार = 0;

      यदि (tdefl_init(pComp, mz_zip_writer_सङ्कलय_put_buf_callback, &state, tdefl_create_comp_flags_from_zip_params(level, -15, MZ_DEFAULT_STRATEGY)) != TDEFL_स्थितिः_OKAY)
      {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        प्रत्यागम MZ_FALSE;
      }

      प्रति ( ; ; )
      {
        size_t अन्तर्_buf_आकार = (mz_uint32)MZ_MIN(uncomp_remaining, MZ_ZIP_MAX_IO_BUF_आकार);
        tdefl_स्थितिः स्थितिः;

        यदि (MZ_FREAD(pRead_buf, 1, अन्तर्_buf_आकार, pSrc_file) != अन्तर्_buf_आकार)
          भङ्ग;

        uncomp_चक्रीयपरीक्षा_32 = (mz_uint32)mz_चक्रीयपरीक्षा_32(uncomp_चक्रीयपरीक्षा_32, (ध्रुव mz_uint8 *)pRead_buf, अन्तर्_buf_आकार);
        uncomp_remaining -= अन्तर्_buf_आकार;

        स्थितिः = tdefl_compress_बफर(pComp, pRead_buf, अन्तर्_buf_आकार, uncomp_remaining ? TDEFL_NO_FLUSH : TDEFL_FINISH);
        यदि (स्थितिः == TDEFL_स्थितिः_समाप्तम्)
        {
          परिणाम = MZ_TRUE;
          भङ्ग;
        }
        अन्यथा यदि (स्थितिः != TDEFL_स्थितिः_OKAY)
          भङ्ग;
      }

      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);

      यदि (!परिणाम)
      {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        प्रत्यागम MZ_FALSE;
      }

      comp_आकार = state.m_comp_आकार;
      cur_archive_file_ofs = state.m_cur_archive_file_ofs;

      विधानम् = MZ_DEFLATED;
    }

    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
  }

  MZ_FCLOSE(pSrc_file); pSrc_file = रिक्त;

  // no zip64 support yet
  यदि ((comp_आकार > 0xFFFFFFFF) || (cur_archive_file_ofs > 0xFFFFFFFF))
    प्रत्यागम MZ_FALSE;

  यदि (!mz_zip_writer_create_local_dir_शीर्षकम्(pZip, local_dir_शीर्षकम्, (mz_uint16)archive_name_आकार, 0, uncomp_आकार, comp_आकार, uncomp_चक्रीयपरीक्षा_32, विधानम्, 0, dos_time, dos_date))
    प्रत्यागम MZ_FALSE;

  यदि (pZip->m_pWrite(pZip->m_pIO_opaque, local_dir_शीर्षकम्_ofs, local_dir_शीर्षकम्, परिमाण(local_dir_शीर्षकम्)) != परिमाण(local_dir_शीर्षकम्))
    प्रत्यागम MZ_FALSE;

  यदि (!mz_zip_writer_सङ्कलय_गन्तव्यम्_central_dir(pZip, pArchive_name, (mz_uint16)archive_name_आकार, रिक्त, 0, pComment, comment_आकार, uncomp_आकार, comp_आकार, uncomp_चक्रीयपरीक्षा_32, विधानम्, 0, dos_time, dos_date, local_dir_शीर्षकम्_ofs, ext_गुणाः))
    प्रत्यागम MZ_FALSE;

  pZip->m_योग_files++;
  pZip->m_archive_आकार = cur_archive_file_ofs;

  प्रत्यागम MZ_TRUE;
}
#यदि_अन्तः // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_writer_सङ्कलय_from_zip_reader(mz_zip_archive *pZip, mz_zip_archive *pSource_zip, mz_uint file_सूचकांक)
{
  mz_uint n, bit_flags, अङ्कः_alignment_padding_अष्टकानि;
  mz_uint64 comp_अष्टकानि_remaining, local_dir_शीर्षकम्_ofs;
  mz_uint64 cur_src_file_ofs, cur_dst_file_ofs;
  mz_uint32 local_शीर्षकम्_u32[(MZ_ZIP_LOCAL_DIR_शीर्षकम्_आकार + परिमाण(mz_uint32) - 1) / परिमाण(mz_uint32)]; mz_uint8 *p_Local_शीर्षकम् = (mz_uint8 *)local_शीर्षकम्_u32;
  mz_uint8 central_शीर्षकम्[MZ_ZIP_CENTRAL_DIR_शीर्षकम्_आकार];
  size_t orig_central_dir_आकार;
  mz_zip_आन्तरिकम्_state *pState;
  शून्य *pBuf; ध्रुव mz_uint8 *p_Src_central_शीर्षकम्;

  यदि ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_बहुलकम् != MZ_ZIP_बहुलकम्_WRITING))
    प्रत्यागम MZ_FALSE;
  यदि (रिक्त == (p_Src_central_शीर्षकम् = mz_zip_reader_get_cdh(pSource_zip, file_सूचकांक)))
    प्रत्यागम MZ_FALSE;
  pState = pZip->m_pState;

  अङ्कः_alignment_padding_अष्टकानि = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  यदि ((pZip->m_योग_files == 0xFFFF) || ((pZip->m_archive_आकार + अङ्कः_alignment_padding_अष्टकानि + MZ_ZIP_LOCAL_DIR_शीर्षकम्_आकार + MZ_ZIP_CENTRAL_DIR_शीर्षकम्_आकार) > 0xFFFFFFFF))
    प्रत्यागम MZ_FALSE;

  cur_src_file_ofs = MZ_READ_LE32(p_Src_central_शीर्षकम् + MZ_ZIP_CDH_LOCAL_शीर्षकम्_OFS);
  cur_dst_file_ofs = pZip->m_archive_आकार;

  यदि (pSource_zip->m_pRead(pSource_zip->m_pIO_opaque, cur_src_file_ofs, p_Local_शीर्षकम्, MZ_ZIP_LOCAL_DIR_शीर्षकम्_आकार) != MZ_ZIP_LOCAL_DIR_शीर्षकम्_आकार)
    प्रत्यागम MZ_FALSE;
  यदि (MZ_READ_LE32(p_Local_शीर्षकम्) != MZ_ZIP_LOCAL_DIR_शीर्षकम्_SIG)
    प्रत्यागम MZ_FALSE;
  cur_src_file_ofs += MZ_ZIP_LOCAL_DIR_शीर्षकम्_आकार;

  यदि (!mz_zip_writer_write_zeros(pZip, cur_dst_file_ofs, अङ्कः_alignment_padding_अष्टकानि))
    प्रत्यागम MZ_FALSE;
  cur_dst_file_ofs += अङ्कः_alignment_padding_अष्टकानि;
  local_dir_शीर्षकम्_ofs = cur_dst_file_ofs;
  यदि (pZip->m_file_विस्थापनम्_alignment) { MZ_ASSERT((local_dir_शीर्षकम्_ofs & (pZip->m_file_विस्थापनम्_alignment - 1)) == 0); }

  यदि (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, p_Local_शीर्षकम्, MZ_ZIP_LOCAL_DIR_शीर्षकम्_आकार) != MZ_ZIP_LOCAL_DIR_शीर्षकम्_आकार)
    प्रत्यागम MZ_FALSE;
  cur_dst_file_ofs += MZ_ZIP_LOCAL_DIR_शीर्षकम्_आकार;

  n = MZ_READ_LE16(p_Local_शीर्षकम् + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p_Local_शीर्षकम् + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  comp_अष्टकानि_remaining = n + MZ_READ_LE32(p_Src_central_शीर्षकम् + MZ_ZIP_CDH_COMPRESSED_आकार_OFS);

  यदि (रिक्त == (pBuf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)MZ_MAX(परिमाण(mz_uint32) * 4, MZ_MIN(MZ_ZIP_MAX_IO_BUF_आकार, comp_अष्टकानि_remaining)))))
    प्रत्यागम MZ_FALSE;

  यावत् (comp_अष्टकानि_remaining)
  {
    n = (mz_uint)MZ_MIN(MZ_ZIP_MAX_IO_BUF_आकार, comp_अष्टकानि_remaining);
    यदि (pSource_zip->m_pRead(pSource_zip->m_pIO_opaque, cur_src_file_ofs, pBuf, n) != n)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      प्रत्यागम MZ_FALSE;
    }
    cur_src_file_ofs += n;

    यदि (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, pBuf, n) != n)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      प्रत्यागम MZ_FALSE;
    }
    cur_dst_file_ofs += n;

    comp_अष्टकानि_remaining -= n;
  }

  bit_flags = MZ_READ_LE16(p_Local_शीर्षकम् + MZ_ZIP_LDH_BIT_FLAG_OFS);
  यदि (bit_flags & 8)
  {
    // Copy data descriptor
    यदि (pSource_zip->m_pRead(pSource_zip->m_pIO_opaque, cur_src_file_ofs, pBuf, परिमाण(mz_uint32) * 4) != परिमाण(mz_uint32) * 4)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      प्रत्यागम MZ_FALSE;
    }

    n = परिमाण(mz_uint32) * ((MZ_READ_LE32(pBuf) == 0x08074b50) ? 4 : 3);
    यदि (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, pBuf, n) != n)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      प्रत्यागम MZ_FALSE;
    }

    cur_src_file_ofs += n;
    cur_dst_file_ofs += n;
  }
  pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);

  // no zip64 support yet
  यदि (cur_dst_file_ofs > 0xFFFFFFFF)
    प्रत्यागम MZ_FALSE;

  orig_central_dir_आकार = pState->m_central_dir.m_आकार;

  स्मृतिं_प्रतिलिख(central_शीर्षकम्, p_Src_central_शीर्षकम्, MZ_ZIP_CENTRAL_DIR_शीर्षकम्_आकार);
  MZ_WRITE_LE32(central_शीर्षकम् + MZ_ZIP_CDH_LOCAL_शीर्षकम्_OFS, local_dir_शीर्षकम्_ofs);
  यदि (!mz_zip_array_प्रक्षिप_पृष्ठभागः(pZip, &pState->m_central_dir, central_शीर्षकम्, MZ_ZIP_CENTRAL_DIR_शीर्षकम्_आकार))
    प्रत्यागम MZ_FALSE;

  n = MZ_READ_LE16(p_Src_central_शीर्षकम् + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p_Src_central_शीर्षकम् + MZ_ZIP_CDH_EXTRA_LEN_OFS) + MZ_READ_LE16(p_Src_central_शीर्षकम् + MZ_ZIP_CDH_COMMENT_LEN_OFS);
  यदि (!mz_zip_array_प्रक्षिप_पृष्ठभागः(pZip, &pState->m_central_dir, p_Src_central_शीर्षकम् + MZ_ZIP_CENTRAL_DIR_शीर्षकम्_आकार, n))
  {
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_आकार, MZ_FALSE);
    प्रत्यागम MZ_FALSE;
  }

  यदि (pState->m_central_dir.m_आकार > 0xFFFFFFFF)
    प्रत्यागम MZ_FALSE;
  n = (mz_uint32)orig_central_dir_आकार;
  यदि (!mz_zip_array_प्रक्षिप_पृष्ठभागः(pZip, &pState->m_central_dir_offsets, &n, 1))
  {
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_आकार, MZ_FALSE);
    प्रत्यागम MZ_FALSE;
  }

  pZip->m_योग_files++;
  pZip->m_archive_आकार = cur_dst_file_ofs;

  प्रत्यागम MZ_TRUE;
}

mz_bool mz_zip_writer_finalize_archive(mz_zip_archive *pZip)
{
  mz_zip_आन्तरिकम्_state *pState;
  mz_uint64 central_dir_ofs, central_dir_आकार;
  mz_uint8 hdr[MZ_ZIP_अन्तः_सम्बन्धि_CENTRAL_DIR_शीर्षकम्_आकार];

  यदि ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_बहुलकम् != MZ_ZIP_बहुलकम्_WRITING))
    प्रत्यागम MZ_FALSE;

  pState = pZip->m_pState;

  // no zip64 support yet
  यदि ((pZip->m_योग_files > 0xFFFF) || ((pZip->m_archive_आकार + pState->m_central_dir.m_आकार + MZ_ZIP_अन्तः_सम्बन्धि_CENTRAL_DIR_शीर्षकम्_आकार) > 0xFFFFFFFF))
    प्रत्यागम MZ_FALSE;

  central_dir_ofs = 0;
  central_dir_आकार = 0;
  यदि (pZip->m_योग_files)
  {
    // Write central directory
    central_dir_ofs = pZip->m_archive_आकार;
    central_dir_आकार = pState->m_central_dir.m_आकार;
    pZip->m_central_directory_file_ofs = central_dir_ofs;
    यदि (pZip->m_pWrite(pZip->m_pIO_opaque, central_dir_ofs, pState->m_central_dir.m_p, (size_t)central_dir_आकार) != central_dir_आकार)
      प्रत्यागम MZ_FALSE;
    pZip->m_archive_आकार += central_dir_आकार;
  }

  // Write end of central directory record
  MZ_CLEAR_ARR(hdr);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_SIG_OFS, MZ_ZIP_अन्तः_सम्बन्धि_CENTRAL_DIR_शीर्षकम्_SIG);
  MZ_WRITE_LE16(hdr + MZ_ZIP_ECDH_CDIR_अङ्कः_ENTRIES_ON_DISK_OFS, pZip->m_योग_files);
  MZ_WRITE_LE16(hdr + MZ_ZIP_ECDH_CDIR_योग_ENTRIES_OFS, pZip->m_योग_files);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_CDIR_आकार_OFS, central_dir_आकार);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_CDIR_OFS_OFS, central_dir_ofs);

  यदि (pZip->m_pWrite(pZip->m_pIO_opaque, pZip->m_archive_आकार, hdr, परिमाण(hdr)) != परिमाण(hdr))
    प्रत्यागम MZ_FALSE;
#यदि_अपरिभाषितम् MINIZ_NO_STDIO
  यदि ((pState->m_pFile) && (MZ_FFLUSH(pState->m_pFile) == EOF))
    प्रत्यागम MZ_FALSE;
#यदि_अन्तः // #ifndef MINIZ_NO_STDIO

  pZip->m_archive_आकार += परिमाण(hdr);

  pZip->m_zip_बहुलकम् = MZ_ZIP_बहुलकम्_WRITING_HAS_BEEN_FINALIZED;
  प्रत्यागम MZ_TRUE;
}

mz_bool mz_zip_writer_finalize_heap_archive(mz_zip_archive *pZip, शून्य **pBuf, size_t *p_आकार)
{
  यदि ((!pZip) || (!pZip->m_pState) || (!pBuf) || (!p_आकार))
    प्रत्यागम MZ_FALSE;
  यदि (pZip->m_pWrite != mz_zip_heap_write_func)
    प्रत्यागम MZ_FALSE;
  यदि (!mz_zip_writer_finalize_archive(pZip))
    प्रत्यागम MZ_FALSE;

  *pBuf = pZip->m_pState->m_pMem;
  *p_आकार = pZip->m_pState->m_mem_आकार;
  pZip->m_pState->m_pMem = रिक्त;
  pZip->m_pState->m_mem_आकार = pZip->m_pState->m_mem_क्षमता = 0;
  प्रत्यागम MZ_TRUE;
}

mz_bool mz_zip_writer_अन्तः(mz_zip_archive *pZip)
{
  mz_zip_आन्तरिकम्_state *pState;
  mz_bool स्थितिः = MZ_TRUE;
  यदि ((!pZip) || (!pZip->m_pState) || (!pZip->m_pAlloc) || (!pZip->m_pFree) || ((pZip->m_zip_बहुलकम् != MZ_ZIP_बहुलकम्_WRITING) && (pZip->m_zip_बहुलकम् != MZ_ZIP_बहुलकम्_WRITING_HAS_BEEN_FINALIZED)))
    प्रत्यागम MZ_FALSE;

  pState = pZip->m_pState;
  pZip->m_pState = रिक्त;
  mz_zip_array_clear(pZip, &pState->m_central_dir);
  mz_zip_array_clear(pZip, &pState->m_central_dir_offsets);
  mz_zip_array_clear(pZip, &pState->m_sorted_central_dir_offsets);

#यदि_अपरिभाषितम् MINIZ_NO_STDIO
  यदि (pState->m_pFile)
  {
    MZ_FCLOSE(pState->m_pFile);
    pState->m_pFile = रिक्त;
  }
#यदि_अन्तः // #ifndef MINIZ_NO_STDIO

  यदि ((pZip->m_pWrite == mz_zip_heap_write_func) && (pState->m_pMem))
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pState->m_pMem);
    pState->m_pMem = रिक्त;
  }

  pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
  pZip->m_zip_बहुलकम् = MZ_ZIP_बहुलकम्_INVALID;
  प्रत्यागम स्थितिः;
}

#यदि_अपरिभाषितम् MINIZ_NO_STDIO
mz_bool mz_zip_सङ्कलय_mem_गन्तव्यम्_archive_file_अन्तर्_place(ध्रुव वर्ण *pZip_filename, ध्रुव वर्ण *pArchive_name, ध्रुव शून्य *pBuf, size_t buf_आकार_2, ध्रुव शून्य *pComment, mz_uint16 comment_आकार, mz_uint level_and_flags)
{
  mz_bool स्थितिः, created_new_archive = MZ_FALSE;
  mz_zip_archive zip_archive;
  संरचना MZ_FILE_STAT_STRUCT file_stat;
  MZ_CLEAR_OBJ(zip_archive);
  यदि ((पूर्णाङ्क)level_and_flags < 0)
     level_and_flags = MZ_DEFAULT_LEVEL;
  यदि ((!pZip_filename) || (!pArchive_name) || ((buf_आकार_2) && (!pBuf)) || ((comment_आकार) && (!pComment)) || ((level_and_flags & 0xF) > MZ_UBER_COMPRESSION))
    प्रत्यागम MZ_FALSE;
  यदि (!mz_zip_writer_validate_archive_name(pArchive_name))
    प्रत्यागम MZ_FALSE;
  यदि (MZ_FILE_STAT(pZip_filename, &file_stat) != 0)
  {
    // Create a new archive.
    यदि (!mz_zip_writer_init_file(&zip_archive, pZip_filename, 0))
      प्रत्यागम MZ_FALSE;
    created_new_archive = MZ_TRUE;
  }
  अन्यथा
  {
    // Append to an existing archive.
    यदि (!mz_zip_reader_init_file(&zip_archive, pZip_filename, level_and_flags | MZ_ZIP_FLAG_DO_NOT_क्रमय_CENTRAL_DIRECTORY))
      प्रत्यागम MZ_FALSE;
    यदि (!mz_zip_writer_init_from_reader(&zip_archive, pZip_filename))
    {
      mz_zip_reader_अन्तः(&zip_archive);
      प्रत्यागम MZ_FALSE;
    }
  }
  स्थितिः = mz_zip_writer_सङ्कलय_mem_ex(&zip_archive, pArchive_name, pBuf, buf_आकार_2, pComment, comment_आकार, level_and_flags, 0, 0);
  // Always finalize, even if adding failed for some reason, so we have a valid central directory. (This may not always succeed, but we can try.)
  यदि (!mz_zip_writer_finalize_archive(&zip_archive))
    स्थितिः = MZ_FALSE;
  यदि (!mz_zip_writer_अन्तः(&zip_archive))
    स्थितिः = MZ_FALSE;
  यदि ((!स्थितिः) && (created_new_archive))
  {
    // It's a new archive and something went wrong, so just delete it.
    पूर्णाङ्क ignored_स्थितिः = MZ_DELETE_FILE(pZip_filename);
    (शून्य)ignored_स्थितिः;
  }
  प्रत्यागम स्थितिः;
}

शून्य *mz_zip_extract_archive_file_गन्तव्यम्_heap(ध्रुव वर्ण *pZip_filename, ध्रुव वर्ण *pArchive_name, size_t *p_आकार, mz_uint flags)
{
  पूर्णाङ्क file_सूचकांक;
  mz_zip_archive zip_archive;
  शून्य *p = रिक्त;

  यदि (p_आकार)
    *p_आकार = 0;

  यदि ((!pZip_filename) || (!pArchive_name))
    प्रत्यागम रिक्त;

  MZ_CLEAR_OBJ(zip_archive);
  यदि (!mz_zip_reader_init_file(&zip_archive, pZip_filename, flags | MZ_ZIP_FLAG_DO_NOT_क्रमय_CENTRAL_DIRECTORY))
    प्रत्यागम रिक्त;

  यदि ((file_सूचकांक = mz_zip_reader_locate_file(&zip_archive, pArchive_name, रिक्त, flags)) >= 0)
    p = mz_zip_reader_extract_गन्तव्यम्_heap(&zip_archive, file_सूचकांक, p_आकार, flags);

  mz_zip_reader_अन्तः(&zip_archive);
  प्रत्यागम p;
}

#यदि_अन्तः // #ifndef MINIZ_NO_STDIO

#यदि_अन्तः // #ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

#यदि_अन्तः // #ifndef MINIZ_NO_ARCHIVE_APIS

#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_परिभाषितम् _MSC_VER
#निर्देशः warning (निष्कासय)
#यदि_अन्तः

#यदि_अन्तः // MINIZ_HEADER_FILE_ONLY

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

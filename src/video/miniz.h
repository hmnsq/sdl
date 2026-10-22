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

#నిర్వచితం_కాకపోతే MINIZ_శీర్షిక_INCLUDED
#నిర్వచించు MINIZ_శీర్షిక_INCLUDED

/*#include <stdlib.h>*/

// Defines to completely disable specific portions of miniz.c:
// If all macros here are defined the only functionality remaining will be CRC-32, adler-32, tinfl, and tdefl.

// Define MINIZ_NO_STDIO to disable all usage and any functions which rely on stdio for file I/O.
#నిర్వచించు MINIZ_NO_STDIO

// If MINIZ_NO_TIME is specified then the ZIP archive functions will not be able to get the current time, or
// get/set file times, and the C run-time funcs that get/set times won't be called.
// The current downside is the times written to your archives will be from 1979.
#నిర్వచించు MINIZ_NO_సమయం

// Define MINIZ_NO_DEFLATE_APIS to disable all compression API's.
//#define MINIZ_NO_DEFLATE_APIS

// Define MINIZ_NO_INFLATE_APIS to disable all decompression API's.
#నిర్వచించు MINIZ_NO_INFLATE_APIS

// Define MINIZ_NO_ARCHIVE_APIS to disable all ZIP archive API's.
#నిర్వచించు MINIZ_NO_ARCHIVE_APIS

// Define MINIZ_NO_ARCHIVE_APIS to disable all writing related ZIP archive API's.
#నిర్వచించు MINIZ_NO_ARCHIVE_WRITING_APIS

// Define MINIZ_NO_ZLIB_APIS to remove all ZLIB-style compression/decompression API's.
#నిర్వచించు MINIZ_NO_ZLIB_APIS

// Define MINIZ_NO_ZLIB_COMPATIBLE_NAME to disable zlib names, to prevent conflicts against stock zlib.
#నిర్వచించు MINIZ_NO_ZLIB_COMPATIBLE_పేర్లు

// Define MINIZ_NO_MALLOC to disable all calls to malloc, free, and realloc.
// Note if MINIZ_NO_MALLOC is defined then the user must always provide custom user alloc/free/realloc
// callbacks to the zlib and archive API's, and a few stand-alone helper API's which don't provide custom user
// functions (such as tdefl_compress_mem_to_heap() and tinfl_decompress_mem_to_heap()) won't work.
//#define MINIZ_NO_MALLOC
#నిర్వచించు MINIZ_SDL_MALLOC

#నిర్వచితమైతే MINIZ_NO_INFLATE_APIS
#నిర్వచించు MINIZ_NO_ARCHIVE_APIS
#అయితే_ముగింపు

#నిర్వచితమైతే MINIZ_NO_DEFLATE_APIS
#నిర్వచించు MINIZ_NO_ARCHIVE_WRITING_APIS
#అయితే_ముగింపు

// Define MINIZ_STATIC_FUNCTIONS to make all functions static. You probably
// want this if you're using miniz in a library
#నిర్వచించు MINIZ_STATIC_FUNCTIONS

#ఒకవేళ defined(__TINYC__) && (defined(__linux) || defined(__linux__))
  // TODO: Work around "error: include file 'sys\utime.h' when compiling with tcc on Linux
  #నిర్వచించు MINIZ_NO_సమయం
#అయితే_ముగింపు

#ఒకవేళ !defined(MINIZ_NO_సమయం) && !defined(MINIZ_NO_ARCHIVE_APIS)
  #అన్తర్భావ <time.h>
#అయితే_ముగింపు

#ఒకవేళ defined(_M_IX86) || defined(_M_X64) || defined(__i386__) || defined(__i386) || defined(__i486__) || defined(__i486) || defined(i386) || defined(__ia64__) || defined(__x86_64__)
// MINIZ_X86_OR_X64_CPU is only used to help set the below macros.
#నిర్వచించు MINIZ_X86_OR_X64_CPU 1
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే MINIZ_LITTLE_ENDIAN /* if not defined by SDL */
#ఒకవేళ (__BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__) || MINIZ_X86_OR_X64_CPU
// Set MINIZ_LITTLE_ENDIAN to 1 if the processor is little endian.
#నిర్వచించు MINIZ_LITTLE_ENDIAN 1
#అయితే_ముగింపు
#అయితే_ముగింపు // MINIZ_LITTLE_ENDIAN /* if not defined by SDL */

#నిర్వచితం_కాకపోతే MINIZ_USE_UNALIGNED_LOADS_AND_STORES
#ఒకవేళ MINIZ_X86_OR_X64_CPU
// Set MINIZ_USE_UNALIGNED_LOADS_AND_STORES to 1 on CPU's that permit efficient integer loads and stores from unaligned addresses.
#నిర్వచించు MINIZ_USE_UNALIGNED_LOADS_AND_STORES 1
#అయితే_ముగింపు
#అయితే_ముగింపు // MINIZ_USE_UNALIGNED_LOADS_AND_STORES

#ఒకవేళ defined(_M_X64) || defined(_WIN64) || defined(__MINGW64__) || defined(_LP64) || defined(__LP64__) || defined(__ia64__) || defined(__x86_64__)
// Set MINIZ_HAS_64BIT_REGISTERS to 1 if operations on 64-bit integers are reasonably fast (and don't involve compiler generated calls to helper functions).
#నిర్వచించు MINIZ_HAS_64_బిట్టు_REGISTERS 1
#అయితే_ముగింపు

#నిర్వచితమైతే MINIZ_STATIC_FUNCTIONS
#నిర్వచించు MINIZ_STATIC స్థిర
#లేకపోతే
#నిర్వచించు MINIZ_STATIC
#అయితే_ముగింపు

#నిర్వచితమైతే __cplusplus
బాహ్య "C" {
#అయితే_ముగింపు

// ------------------- zlib-style API Definitions.

// For more compatibility with zlib, miniz.c uses unsigned long for some parameters/struct members. Beware: mz_ulong can be either 32 or 64-bits!
రకనిర్వచనం గుర్తులేని దీర్ఘ mz_ulong;

// mz_free() internally uses the MZ_FREE() macro (which by default calls free() unless you've modified the MZ_MALLOC macro) to release a block allocated from the heap.
MINIZ_STATIC శూన్య mz_free(శూన్య *p);

#నిర్వచించు MZ_ADLER32_INIT (1)
// mz_adler32() returns the initial adler-32 value to use when called with ptr==NULL.
MINIZ_STATIC mz_ulong mz_adler32(mz_ulong adler, స్థిరరాశి గుర్తులేని అక్షరం *ptr, size_t buf_len);

#నిర్వచించు MZ_చక్రీయ_తనిఖీ_32_INIT (0)
// mz_crc32() returns the initial CRC-32 value to use when called with ptr==NULL.
MINIZ_STATIC mz_ulong mz_చక్రీయ_తనిఖీ_32(mz_ulong చక్రీయ_తనిఖీ, స్థిరరాశి గుర్తులేని అక్షరం *ptr, size_t buf_len);

// Compression strategies.
గణన { MZ_DEFAULT_STRATEGY = 0, MZ_FILTERED = 1, MZ_HUFFMAN_ONLY = 2, MZ_RLE = 3, MZ_FIXED = 4 };

//పద్ధతి
#నిర్వచించు MZ_DEFLATED 8

#నిర్వచితం_కాకపోతే MINIZ_NO_ZLIB_APIS

// Heap allocation callbacks.
// Note that mz_alloc_func parameter types purpsosely differ from zlib's: items/size is size_t, not unsigned long.
రకనిర్వచనం శూన్య *(*mz_alloc_func)(శూన్య *opaque, size_t వస్తువులు, size_t కొలత);
రకనిర్వచనం శూన్య (*mz_free_func)(శూన్య *opaque, శూన్య *చిరునామా);
రకనిర్వచనం శూన్య *(*mz_realloc_func)(శూన్య *opaque, శూన్య *చిరునామా, size_t వస్తువులు, size_t కొలత);

#నిర్వచించు MZ_సంస్కరణ          "9.1.15"
#నిర్వచించు MZ_VERNUM           0x91F0
#నిర్వచించు MZ_VER_MAJOR        9
#నిర్వచించు MZ_VER_MINOR        1
#నిర్వచించు MZ_VER_REVISION     15
#నిర్వచించు MZ_VER_SUBREVISION  0

// Flush values. For typical usage you only need MZ_NO_FLUSH and MZ_FINISH. The other values are for advanced use (refer to the zlib docs).
గణన { MZ_NO_FLUSH = 0, MZ_PARTIAL_FLUSH = 1, MZ_SYNC_FLUSH = 2, MZ_నిండిన_FLUSH = 3, MZ_ముగింపు = 4, MZ_ఖండం = 5 };

// Return status codes. MZ_PARAM_ERROR is non-standard.
గణన { MZ_OK = 0, MZ_ప్రవాహం_చివర = 1, MZ_NEED_DICT = 2, MZ_ERRNO = -1, MZ_ప్రవాహం_ERROR = -2, MZ_దత్తాంశం_ERROR = -3, MZ_MEM_ERROR = -4, MZ_BUF_ERROR = -5, MZ_సంస్కరణ_ERROR = -6, MZ_PARAM_ERROR = -10000 };

// Compression levels: 0-9 are the standard zlib-style levels, 10 is best possible compression (not zlib compatible, and may be very slow), MZ_DEFAULT_COMPRESSION=MZ_DEFAULT_LEVEL.
గణన { MZ_NO_COMPRESSION = 0, MZ_ఉత్తమ_వేగం = 1, MZ_ఉత్తమ_COMPRESSION = 9, MZ_UBER_COMPRESSION = 10, MZ_DEFAULT_LEVEL = 6, MZ_DEFAULT_COMPRESSION = -1 };

// Window bits
#నిర్వచించు MZ_DEFAULT_కిటికీ_బిట్లు 15

నిర్మాణం mz_అంతర్గత_state;

// Compression/decompression stream struct.
రకనిర్వచనం నిర్మాణం mz_ప్రవాహం_s
{
  స్థిరరాశి గుర్తులేని అక్షరం *తదుపరి_లోపల;     // pointer to next byte to read
  గుర్తులేని పూర్ణాంకం avail_లోపల;            // number of bytes available at next_in
  mz_ulong మొత్తం_లోపల;                // total number of bytes consumed so far

  గుర్తులేని అక్షరం *తదుపరి_బహిర్గతం;          // pointer to next byte to write
  గుర్తులేని పూర్ణాంకం avail_బహిర్గతం;           // number of bytes that can be written to next_out
  mz_ulong మొత్తం_బహిర్గతం;               // total number of bytes produced so far

  అక్షరం *సందేశం_2;                        // error msg (unused)
  నిర్మాణం mz_అంతర్గత_state *state;  // internal state, allocated by zalloc/zfree

  mz_alloc_func zalloc;             // optional heap allocation function (defaults to malloc)
  mz_free_func zfree;               // optional heap free function (defaults to free)
  శూన్య *opaque;                     // heap alloc function user pointer

  పూర్ణాంకం దత్తాంశం_type;                    // data_type (unused)
  mz_ulong adler;                   // adler32 of the source or uncompressed data
  mz_ulong reserved;                // not used
} mz_ప్రవాహం;

రకనిర్వచనం mz_ప్రవాహం *mz_streamp;

// Returns the version string of miniz.c.
MINIZ_STATIC స్థిరరాశి అక్షరం *mz_సంస్కరణ(శూన్య);

#నిర్వచితం_కాకపోతే MINIZ_NO_DEFLATE_APIS

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
MINIZ_STATIC పూర్ణాంకం mz_deflateInit(mz_streamp p_ప్రవాహం, పూర్ణాంకం level);

// mz_deflateInit2() is like mz_deflate(), except with more control:
// Additional parameters:
//   method must be MZ_DEFLATED
//   window_bits must be MZ_DEFAULT_WINDOW_BITS (to wrap the deflate stream with zlib header/adler-32 footer) or -MZ_DEFAULT_WINDOW_BITS (raw deflate/no header or footer)
//   mem_level must be between [1, 9] (it's checked but ignored by miniz.c)
MINIZ_STATIC పూర్ణాంకం mz_deflateInit2(mz_streamp p_ప్రవాహం, పూర్ణాంకం level, పూర్ణాంకం పద్ధతి, పూర్ణాంకం కిటికీ_బిట్లు, పూర్ణాంకం mem_level, పూర్ణాంకం strategy);

// Quickly resets a compressor without having to reallocate anything. Same as calling mz_deflateEnd() followed by mz_deflateInit()/mz_deflateInit2().
MINIZ_STATIC పూర్ణాంకం mz_deflateReset(mz_streamp p_ప్రవాహం);

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
MINIZ_STATIC పూర్ణాంకం mz_deflate(mz_streamp p_ప్రవాహం, పూర్ణాంకం flush);

// mz_deflateEnd() deinitializes a compressor:
// Return values:
//  MZ_OK on success.
//  MZ_STREAM_ERROR if the stream is bogus.
MINIZ_STATIC పూర్ణాంకం mz_deflate_చివర(mz_streamp p_ప్రవాహం);

// mz_deflateBound() returns a (very) conservative upper bound on the amount of data that could be generated by deflate(), assuming flush is set to only MZ_NO_FLUSH or MZ_FINISH.
MINIZ_STATIC mz_ulong mz_deflateBound(mz_streamp p_ప్రవాహం, mz_ulong ఆధారం_len);

// Single-call compression functions mz_compress() and mz_compress2():
// Returns MZ_OK on success, or one of the error codes from mz_deflate() on failure.
MINIZ_STATIC పూర్ణాంకం mz_compress(గుర్తులేని అక్షరం *pDest, mz_ulong *pDest_len, స్థిరరాశి గుర్తులేని అక్షరం *p_ఆధారం, mz_ulong ఆధారం_len);
MINIZ_STATIC పూర్ణాంకం mz_compress2(గుర్తులేని అక్షరం *pDest, mz_ulong *pDest_len, స్థిరరాశి గుర్తులేని అక్షరం *p_ఆధారం, mz_ulong ఆధారం_len, పూర్ణాంకం level);

// mz_compressBound() returns a (very) conservative upper bound on the amount of data that could be generated by calling mz_compress().
MINIZ_STATIC mz_ulong mz_compressBound(mz_ulong ఆధారం_len);

#అయితే_ముగింపు /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#నిర్వచితం_కాకపోతే MINIZ_NO_INFLATE_APIS

// Initializes a decompressor.
MINIZ_STATIC పూర్ణాంకం mz_inflateInit(mz_streamp p_ప్రవాహం);

// mz_inflateInit2() is like mz_inflateInit() with an additional option that controls the window size and whether or not the stream has been wrapped with a zlib header/footer:
// window_bits must be MZ_DEFAULT_WINDOW_BITS (to parse zlib header/footer) or -MZ_DEFAULT_WINDOW_BITS (raw deflate).
MINIZ_STATIC పూర్ణాంకం mz_inflateInit2(mz_streamp p_ప్రవాహం, పూర్ణాంకం కిటికీ_బిట్లు);

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
MINIZ_STATIC పూర్ణాంకం mz_inflate(mz_streamp p_ప్రవాహం, పూర్ణాంకం flush);

// Deinitializes a decompressor.
MINIZ_STATIC పూర్ణాంకం mz_inflate_చివర(mz_streamp p_ప్రవాహం);

// Single-call decompression.
// Returns MZ_OK on success, or one of the error codes from mz_inflate() on failure.
MINIZ_STATIC పూర్ణాంకం mz_uncompress(గుర్తులేని అక్షరం *pDest, mz_ulong *pDest_len, స్థిరరాశి గుర్తులేని అక్షరం *p_ఆధారం, mz_ulong ఆధారం_len);
#అయితే_ముగింపు /*#ifndef MINIZ_NO_INFLATE_APIS*/

// Returns a string description of the specified error code, or NULL if the error code is invalid.
MINIZ_STATIC స్థిరరాశి అక్షరం *mz_error(పూర్ణాంకం err);

// Redefine zlib-compatible names to miniz equivalents, so miniz.c can be used as a drop-in replacement for the subset of zlib that miniz.c supports.
// Define MINIZ_NO_ZLIB_COMPATIBLE_NAMES to disable zlib-compatibility if you use zlib in the same project.
#నిర్వచితం_కాకపోతే MINIZ_NO_ZLIB_COMPATIBLE_పేర్లు
  రకనిర్వచనం గుర్తులేని అక్షరం Byte;
  రకనిర్వచనం గుర్తులేని పూర్ణాంకం uInt;
  రకనిర్వచనం mz_ulong uLong;
  రకనిర్వచనం Byte Bytef;
  రకనిర్వచనం uInt uIntf;
  రకనిర్వచనం అక్షరం charf;
  రకనిర్వచనం పూర్ణాంకం intf;
  రకనిర్వచనం శూన్య *voidpf;
  రకనిర్వచనం uLong uLongf;
  రకనిర్వచనం శూన్య *voidp;
  రకనిర్వచనం శూన్య *స్థిరరాశి voidpc;
  #నిర్వచించు Z_NULL                0
  #నిర్వచించు Z_NO_FLUSH            MZ_NO_FLUSH
  #నిర్వచించు Z_PARTIAL_FLUSH       MZ_PARTIAL_FLUSH
  #నిర్వచించు Z_SYNC_FLUSH          MZ_SYNC_FLUSH
  #నిర్వచించు Z_నిండిన_FLUSH          MZ_నిండిన_FLUSH
  #నిర్వచించు Z_ముగింపు              MZ_ముగింపు
  #నిర్వచించు Z_ఖండం               MZ_ఖండం
  #నిర్వచించు Z_OK                  MZ_OK
  #నిర్వచించు Z_ప్రవాహం_చివర          MZ_ప్రవాహం_చివర
  #నిర్వచించు Z_NEED_DICT           MZ_NEED_DICT
  #నిర్వచించు Z_ERRNO               MZ_ERRNO
  #నిర్వచించు Z_ప్రవాహం_ERROR        MZ_ప్రవాహం_ERROR
  #నిర్వచించు Z_దత్తాంశం_ERROR          MZ_దత్తాంశం_ERROR
  #నిర్వచించు Z_MEM_ERROR           MZ_MEM_ERROR
  #నిర్వచించు Z_BUF_ERROR           MZ_BUF_ERROR
  #నిర్వచించు Z_సంస్కరణ_ERROR       MZ_సంస్కరణ_ERROR
  #నిర్వచించు Z_PARAM_ERROR         MZ_PARAM_ERROR
  #నిర్వచించు Z_NO_COMPRESSION      MZ_NO_COMPRESSION
  #నిర్వచించు Z_ఉత్తమ_వేగం          MZ_ఉత్తమ_వేగం
  #నిర్వచించు Z_ఉత్తమ_COMPRESSION    MZ_ఉత్తమ_COMPRESSION
  #నిర్వచించు Z_DEFAULT_COMPRESSION MZ_DEFAULT_COMPRESSION
  #నిర్వచించు Z_DEFAULT_STRATEGY    MZ_DEFAULT_STRATEGY
  #నిర్వచించు Z_FILTERED            MZ_FILTERED
  #నిర్వచించు Z_HUFFMAN_ONLY        MZ_HUFFMAN_ONLY
  #నిర్వచించు Z_RLE                 MZ_RLE
  #నిర్వచించు Z_FIXED               MZ_FIXED
  #నిర్వచించు Z_DEFLATED            MZ_DEFLATED
  #నిర్వచించు Z_DEFAULT_కిటికీ_బిట్లు MZ_DEFAULT_కిటికీ_బిట్లు
  #నిర్వచించు alloc_func            mz_alloc_func
  #నిర్వచించు free_func             mz_free_func
  #నిర్వచించు అంతర్గత_state        mz_అంతర్గత_state
  #నిర్వచించు z_ప్రవాహం              mz_ప్రవాహం
#నిర్వచితం_కాకపోతే MINIZ_NO_DEFLATE_APIS
  #నిర్వచించు deflateInit           mz_deflateInit
  #నిర్వచించు deflateInit2          mz_deflateInit2
  #నిర్వచించు deflateReset          mz_deflateReset
  #నిర్వచించు deflate               mz_deflate
  #నిర్వచించు deflate_చివర            mz_deflate_చివర
  #నిర్వచించు deflateBound          mz_deflateBound
  #నిర్వచించు compress              mz_compress
  #నిర్వచించు compress2             mz_compress2
  #నిర్వచించు compressBound         mz_compressBound
#అయితే_ముగింపు /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#నిర్వచితం_కాకపోతే MINIZ_NO_INFLATE_APIS
  #నిర్వచించు inflateInit           mz_inflateInit
  #నిర్వచించు inflateInit2          mz_inflateInit2
  #నిర్వచించు inflate               mz_inflate
  #నిర్వచించు inflate_చివర            mz_inflate_చివర
  #నిర్వచించు uncompress            mz_uncompress
#అయితే_ముగింపు /*#ifndef MINIZ_NO_INFLATE_APIS*/
  #నిర్వచించు చక్రీయ_తనిఖీ_32                 mz_చక్రీయ_తనిఖీ_32
  #నిర్వచించు adler32               mz_adler32
  #నిర్వచించు MAX_WBITS             15
  #నిర్వచించు MAX_MEM_LEVEL         9
  #నిర్వచించు zError                mz_error
  #నిర్వచించు ZLIB_సంస్కరణ          MZ_సంస్కరణ
  #నిర్వచించు ZLIB_VERNUM           MZ_VERNUM
  #నిర్వచించు ZLIB_VER_MAJOR        MZ_VER_MAJOR
  #నిర్వచించు ZLIB_VER_MINOR        MZ_VER_MINOR
  #నిర్వచించు ZLIB_VER_REVISION     MZ_VER_REVISION
  #నిర్వచించు ZLIB_VER_SUBREVISION  MZ_VER_SUBREVISION
  #నిర్వచించు zlib_సంస్కరణ           mz_సంస్కరణ
  #నిర్వచించు zlib_సంస్కరణ_2          mz_సంస్కరణ()
#అయితే_ముగింపు // #ifndef MINIZ_NO_ZLIB_COMPATIBLE_NAMES

#అయితే_ముగింపు // MINIZ_NO_ZLIB_APIS

// ------------------- Types and macros

రకనిర్వచనం గుర్తులేని అక్షరం mz_uint8;
రకనిర్వచనం గుర్తుగల పొట్టి mz_int16;
రకనిర్వచనం గుర్తులేని పొట్టి mz_uint16;
రకనిర్వచనం గుర్తులేని పూర్ణాంకం mz_uint32;
రకనిర్వచనం గుర్తులేని పూర్ణాంకం mz_uint;
రకనిర్వచనం దీర్ఘ దీర్ఘ mz_int64;
రకనిర్వచనం గుర్తులేని దీర్ఘ దీర్ఘ mz_uint64;
రకనిర్వచనం పూర్ణాంకం mz_bool;

#నిర్వచించు MZ_FALSE (0)
#నిర్వచించు MZ_TRUE (1)

// An attempt to work around MSVC's spammy "warning C4127: conditional expression is constant" message.
#నిర్వచితమైతే _MSC_VER
   #నిర్వచించు MZ_MACRO_చివర అయితే (0, 0)
#లేకపోతే
   #నిర్వచించు MZ_MACRO_చివర అయితే (0)
#అయితే_ముగింపు

// ------------------- ZIP archive reading/writing

#నిర్వచితం_కాకపోతే MINIZ_NO_ARCHIVE_APIS

గణన
{
  MZ_ZIP_MAX_IO_BUF_కొలత = 64*1024,
  MZ_ZIP_MAX_ARCHIVE_FILENAME_కొలత = 260,
  MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_కొలత = 256
};

రకనిర్వచనం నిర్మాణం
{
  mz_uint32 m_file_సూచీ;
  mz_uint32 m_central_dir_ofs;
  mz_uint16 m_సంస్కరణ_made_by;
  mz_uint16 m_సంస్కరణ_needed;
  mz_uint16 m_బిట్టు_flag;
  mz_uint16 m_పద్ధతి;
#నిర్వచితం_కాకపోతే MINIZ_NO_సమయం
  సమయం_t m_సమయం;
#అయితే_ముగింపు
  mz_uint32 m_చక్రీయ_తనిఖీ_32;
  mz_uint64 m_comp_కొలత;
  mz_uint64 m_uncomp_కొలత;
  mz_uint16 m_అంతర్గత_attr;
  mz_uint32 m_external_attr;
  mz_uint64 m_local_శీర్షిక_ofs;
  mz_uint32 m_comment_కొలత;
  అక్షరం m_filename[MZ_ZIP_MAX_ARCHIVE_FILENAME_కొలత];
  అక్షరం m_comment[MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_కొలత];
} mz_zip_archive_file_stat;

రకనిర్వచనం size_t (*mz_file_read_func)(శూన్య *pOpaque, mz_uint64 file_ofs, శూన్య *pBuf, size_t n);
రకనిర్వచనం size_t (*mz_file_write_func)(శూన్య *pOpaque, mz_uint64 file_ofs, స్థిరరాశి శూన్య *pBuf, size_t n);

నిర్మాణం mz_zip_అంతర్గత_state_ట్యాగ్;
రకనిర్వచనం నిర్మాణం mz_zip_అంతర్గత_state_ట్యాగ్ mz_zip_అంతర్గత_state;

రకనిర్వచనం గణన
{
  MZ_ZIP_బహుళకం_INVALID = 0,
  MZ_ZIP_బహుళకం_READING = 1,
  MZ_ZIP_బహుళకం_WRITING = 2,
  MZ_ZIP_బహుళకం_WRITING_HAS_BEEN_FINALIZED = 3
} mz_zip_బహుళకం;

రకనిర్వచనం నిర్మాణం mz_zip_archive_ట్యాగ్
{
  mz_uint64 m_archive_కొలత;
  mz_uint64 m_central_directory_file_ofs;
  mz_uint m_మొత్తం_files;
  mz_zip_బహుళకం m_zip_బహుళకం;

  mz_uint m_file_స్థానభ్రంశం_alignment;

  mz_alloc_func m_pAlloc;
  mz_free_func m_pFree;
  mz_realloc_func m_pRealloc;
  శూన్య *m_pAlloc_opaque;

  mz_file_read_func m_pRead;
  mz_file_write_func m_pWrite;
  శూన్య *m_pIO_opaque;

  mz_zip_అంతర్గత_state *m_pState;

} mz_zip_archive;

రకనిర్వచనం గణన
{
  MZ_ZIP_FLAG_CASE_SENSITIVE                = 0x0100,
  MZ_ZIP_FLAG_IGNORE_మార్గం                   = 0x0200,
  MZ_ZIP_FLAG_COMPRESSED_దత్తాంశం               = 0x0400,
  MZ_ZIP_FLAG_DO_NOT_క్రమీకరించు_CENTRAL_DIRECTORY = 0x0800
} mz_zip_flags;

// ZIP archive reading

// Inits a ZIP archive reader.
// These functions read and validate the archive's central directory.
MINIZ_STATIC mz_bool mz_zip_reader_init(mz_zip_archive *pZip, mz_uint64 కొలత, mz_uint32 flags);
MINIZ_STATIC mz_bool mz_zip_reader_init_mem(mz_zip_archive *pZip, స్థిరరాశి శూన్య *pMem, size_t కొలత, mz_uint32 flags);

#నిర్వచితం_కాకపోతే MINIZ_NO_STDIO
MINIZ_STATIC mz_bool mz_zip_reader_init_file(mz_zip_archive *pZip, స్థిరరాశి అక్షరం *pFilename, mz_uint32 flags);
#అయితే_ముగింపు

// Returns the total number of files in the archive.
MINIZ_STATIC mz_uint mz_zip_reader_get_అంకె_files(mz_zip_archive *pZip);

// Returns detailed information about an archive file entry.
MINIZ_STATIC mz_bool mz_zip_reader_file_stat(mz_zip_archive *pZip, mz_uint file_సూచీ, mz_zip_archive_file_stat *pStat);

// Determines if an archive file entry is a directory entry.
MINIZ_STATIC mz_bool mz_zip_reader_is_file_a_directory(mz_zip_archive *pZip, mz_uint file_సూచీ);
MINIZ_STATIC mz_bool mz_zip_reader_is_file_encrypted(mz_zip_archive *pZip, mz_uint file_సూచీ);

// Retrieves the filename of an archive file entry.
// Returns the number of bytes written to pFilename, or if filename_buf_size is 0 this function returns the number of bytes needed to fully store the filename.
MINIZ_STATIC mz_uint mz_zip_reader_get_filename(mz_zip_archive *pZip, mz_uint file_సూచీ, అక్షరం *pFilename, mz_uint filename_buf_కొలత);

// Attempts to locates a file in the archive's central directory.
// Valid flags: MZ_ZIP_FLAG_CASE_SENSITIVE, MZ_ZIP_FLAG_IGNORE_PATH
// Returns -1 if the file cannot be found.
MINIZ_STATIC పూర్ణాంకం mz_zip_reader_locate_file(mz_zip_archive *pZip, స్థిరరాశి అక్షరం *pName, స్థిరరాశి అక్షరం *pComment, mz_uint flags);

// Extracts a archive file to a memory buffer using no memory allocation.
MINIZ_STATIC mz_bool mz_zip_reader_వెలికితీయి_గమ్యం_mem_no_alloc(mz_zip_archive *pZip, mz_uint file_సూచీ, శూన్య *pBuf, size_t buf_కొలత_2, mz_uint flags, శూన్య *pUser_read_buf, size_t user_read_buf_కొలత);
MINIZ_STATIC mz_bool mz_zip_reader_వెలికితీయి_file_గమ్యం_mem_no_alloc(mz_zip_archive *pZip, స్థిరరాశి అక్షరం *pFilename, శూన్య *pBuf, size_t buf_కొలత_2, mz_uint flags, శూన్య *pUser_read_buf, size_t user_read_buf_కొలత);

// Extracts a archive file to a memory buffer.
MINIZ_STATIC mz_bool mz_zip_reader_వెలికితీయి_గమ్యం_mem(mz_zip_archive *pZip, mz_uint file_సూచీ, శూన్య *pBuf, size_t buf_కొలత_2, mz_uint flags);
MINIZ_STATIC mz_bool mz_zip_reader_వెలికితీయి_file_గమ్యం_mem(mz_zip_archive *pZip, స్థిరరాశి అక్షరం *pFilename, శూన్య *pBuf, size_t buf_కొలత_2, mz_uint flags);

// Extracts a archive file to a dynamically allocated heap buffer.
MINIZ_STATIC శూన్య *mz_zip_reader_వెలికితీయి_గమ్యం_కుప్ప(mz_zip_archive *pZip, mz_uint file_సూచీ, size_t *p_కొలత, mz_uint flags);
MINIZ_STATIC శూన్య *mz_zip_reader_వెలికితీయి_file_గమ్యం_కుప్ప(mz_zip_archive *pZip, స్థిరరాశి అక్షరం *pFilename, size_t *p_కొలత, mz_uint flags);

// Extracts a archive file using a callback function to output the file's data.
MINIZ_STATIC mz_bool mz_zip_reader_వెలికితీయి_గమ్యం_callback(mz_zip_archive *pZip, mz_uint file_సూచీ, mz_file_write_func pCallback, శూన్య *pOpaque, mz_uint flags);
MINIZ_STATIC mz_bool mz_zip_reader_వెలికితీయి_file_గమ్యం_callback(mz_zip_archive *pZip, స్థిరరాశి అక్షరం *pFilename, mz_file_write_func pCallback, శూన్య *pOpaque, mz_uint flags);

#నిర్వచితం_కాకపోతే MINIZ_NO_STDIO
// Extracts a archive file to a disk file and sets its last accessed and modified times.
// This function only extracts files, not archive directory records.
MINIZ_STATIC mz_bool mz_zip_reader_వెలికితీయి_గమ్యం_file(mz_zip_archive *pZip, mz_uint file_సూచీ, స్థిరరాశి అక్షరం *pDst_filename, mz_uint flags);
MINIZ_STATIC mz_bool mz_zip_reader_వెలికితీయి_file_గమ్యం_file(mz_zip_archive *pZip, స్థిరరాశి అక్షరం *pArchive_filename, స్థిరరాశి అక్షరం *pDst_filename, mz_uint flags);
#అయితే_ముగింపు

// Ends archive reading, freeing all allocations, and closing the input archive file if mz_zip_reader_init_file() was used.
MINIZ_STATIC mz_bool mz_zip_reader_చివర(mz_zip_archive *pZip);

// ZIP archive writing

#నిర్వచితం_కాకపోతే MINIZ_NO_ARCHIVE_WRITING_APIS

// Inits a ZIP archive writer.
MINIZ_STATIC mz_bool mz_zip_writer_init(mz_zip_archive *pZip, mz_uint64 existing_కొలత);
MINIZ_STATIC mz_bool mz_zip_writer_init_కుప్ప(mz_zip_archive *pZip, size_t కొలత_గమ్యం_reserve_at_beginning, size_t initial_కేటాయింపు_కొలత);

#నిర్వచితం_కాకపోతే MINIZ_NO_STDIO
MINIZ_STATIC mz_bool mz_zip_writer_init_file(mz_zip_archive *pZip, స్థిరరాశి అక్షరం *pFilename, mz_uint64 కొలత_గమ్యం_reserve_at_beginning);
#అయితే_ముగింపు

// Converts a ZIP archive reader object into a writer object, to allow efficient in-place file appends to occur on an existing archive.
// For archives opened using mz_zip_reader_init_file, pFilename must be the archive's filename so it can be reopened for writing. If the file can't be reopened, mz_zip_reader_end() will be called.
// For archives opened using mz_zip_reader_init_mem, the memory block must be growable using the realloc callback (which defaults to realloc unless you've overridden it).
// Finally, for archives opened using mz_zip_reader_init, the mz_zip_archive's user provided m_pWrite function cannot be NULL.
// Note: In-place archive modification is not recommended unless you know what you're doing, because if execution stops or something goes wrong before
// the archive is finalized the file's central directory will be hosed.
MINIZ_STATIC mz_bool mz_zip_writer_init_from_reader(mz_zip_archive *pZip, స్థిరరాశి అక్షరం *pFilename);

// Adds the contents of a memory buffer to an archive. These functions record the current local time into the archive.
// To add a directory entry, call this method with an archive name ending in a forwardslash with empty buffer.
// level_and_flags - compression level (0-10, see MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or just set to MZ_DEFAULT_COMPRESSION.
MINIZ_STATIC mz_bool mz_zip_writer_కూడు_mem(mz_zip_archive *pZip, స్థిరరాశి అక్షరం *pArchive_name, స్థిరరాశి శూన్య *pBuf, size_t buf_కొలత_2, mz_uint level_and_flags);
MINIZ_STATIC mz_bool mz_zip_writer_కూడు_mem_ex(mz_zip_archive *pZip, స్థిరరాశి అక్షరం *pArchive_name, స్థిరరాశి శూన్య *pBuf, size_t buf_కొలత_2, స్థిరరాశి శూన్య *pComment, mz_uint16 comment_కొలత, mz_uint level_and_flags, mz_uint64 uncomp_కొలత, mz_uint32 uncomp_చక్రీయ_తనిఖీ_32);

#నిర్వచితం_కాకపోతే MINIZ_NO_STDIO
// Adds the contents of a disk file to an archive. This function also records the disk file's modified time into the archive.
// level_and_flags - compression level (0-10, see MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or just set to MZ_DEFAULT_COMPRESSION.
MINIZ_STATIC mz_bool mz_zip_writer_కూడు_file(mz_zip_archive *pZip, స్థిరరాశి అక్షరం *pArchive_name, స్థిరరాశి అక్షరం *pSrc_filename, స్థిరరాశి శూన్య *pComment, mz_uint16 comment_కొలత, mz_uint level_and_flags);
#అయితే_ముగింపు

// Adds a file to an archive by fully cloning the data from another archive.
// This function fully clones the source file's compressed data (no recompression), along with its full filename, extra data, and comment fields.
MINIZ_STATIC mz_bool mz_zip_writer_కూడు_from_zip_reader(mz_zip_archive *pZip, mz_zip_archive *p_ఆధారం_zip, mz_uint file_సూచీ);

// Finalizes the archive by writing the central directory records followed by the end of central directory record.
// After an archive is finalized, the only valid call on the mz_zip_archive struct is mz_zip_writer_end().
// An archive must be manually finalized by calling this function for it to be valid.
MINIZ_STATIC mz_bool mz_zip_writer_finalize_archive(mz_zip_archive *pZip);
MINIZ_STATIC mz_bool mz_zip_writer_finalize_కుప్ప_archive(mz_zip_archive *pZip, శూన్య **pBuf, size_t *p_కొలత);

// Ends archive writing, freeing all allocations, and closing the output file if mz_zip_writer_init_file() was used.
// Note for the archive to be valid, it must have been finalized before ending.
MINIZ_STATIC mz_bool mz_zip_writer_చివర(mz_zip_archive *pZip);

// Misc. high-level helper functions:

// mz_zip_add_mem_to_archive_file_in_place() efficiently (but not atomically) appends a memory blob to a ZIP archive.
// level_and_flags - compression level (0-10, see MZ_BEST_SPEED, MZ_BEST_COMPRESSION, etc.) logically OR'd with zero or more mz_zip_flags, or just set to MZ_DEFAULT_COMPRESSION.
MINIZ_STATIC mz_bool mz_zip_కూడు_mem_గమ్యం_archive_file_లోపల_ఉంచు(స్థిరరాశి అక్షరం *pZip_filename, స్థిరరాశి అక్షరం *pArchive_name, స్థిరరాశి శూన్య *pBuf, size_t buf_కొలత_2, స్థిరరాశి శూన్య *pComment, mz_uint16 comment_కొలత, mz_uint level_and_flags);

// Reads a single file from an archive into a heap block.
// Returns NULL on failure.
MINIZ_STATIC శూన్య *mz_zip_వెలికితీయి_archive_file_గమ్యం_కుప్ప(స్థిరరాశి అక్షరం *pZip_filename, స్థిరరాశి అక్షరం *pArchive_name, size_t *p_కొలత, mz_uint zip_flags);

#అయితే_ముగింపు // #ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

#అయితే_ముగింపు // #ifndef MINIZ_NO_ARCHIVE_APIS

// ------------------- Low-level Decompression API Definitions
#నిర్వచితం_కాకపోతే MINIZ_NO_INFLATE_APIS

// Decompression flags used by tinfl_decompress().
// TINFL_FLAG_PARSE_ZLIB_HEADER: If set, the input has a valid zlib header and ends with an adler32 checksum (it's a valid zlib stream). Otherwise, the input is a raw deflate stream.
// TINFL_FLAG_HAS_MORE_INPUT: If set, there are more input bytes available beyond the end of the supplied input buffer. If clear, the input buffer contains all remaining input.
// TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF: If set, the output buffer is large enough to hold the entire decompressed stream. If clear, the output buffer is at least the size of the dictionary (typically 32KB).
// TINFL_FLAG_COMPUTE_ADLER32: Force adler-32 checksum computation of the decompressed bytes.
గణన
{
  TINFL_FLAG_PARSE_ZLIB_శీర్షిక = 1,
  TINFL_FLAG_HAS_మరిన్ని_ఆదానం = 2,
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
MINIZ_STATIC శూన్య *tinfl_decompress_mem_గమ్యం_కుప్ప(స్థిరరాశి శూన్య *pSrc_buf, size_t src_buf_len, size_t *p_బహిర్గతం_len, పూర్ణాంకం flags);

// tinfl_decompress_mem_to_mem() decompresses a block in memory to another block in memory.
// Returns TINFL_DECOMPRESS_MEM_TO_MEM_FAILED on failure, or the number of bytes written on success.
#నిర్వచించు TINFL_DECOMPRESS_MEM_గమ్యం_MEM_FAILED ((size_t)(-1))
MINIZ_STATIC size_t tinfl_decompress_mem_గమ్యం_mem(శూన్య *p_బహిర్గతం_buf, size_t బహిర్గతం_buf_len, స్థిరరాశి శూన్య *pSrc_buf, size_t src_buf_len, పూర్ణాంకం flags);

// tinfl_decompress_mem_to_callback() decompresses a block in memory to an internal 32KB buffer, and a user provided callback function will be called to flush the buffer.
// Returns 1 on success or 0 on failure.
రకనిర్వచనం పూర్ణాంకం (*tinfl_put_buf_func_ptr)(స్థిరరాశి శూన్య* pBuf, పూర్ణాంకం len, శూన్య *pUser);
MINIZ_STATIC పూర్ణాంకం tinfl_decompress_mem_గమ్యం_callback(స్థిరరాశి శూన్య *p_లోపల_buf, size_t *p_లోపల_buf_కొలత, tinfl_put_buf_func_ptr pPut_buf_func, శూన్య *pPut_buf_user, పూర్ణాంకం flags);

నిర్మాణం tinfl_decompressor_ట్యాగ్; రకనిర్వచనం నిర్మాణం tinfl_decompressor_ట్యాగ్ tinfl_decompressor;

// Max size of LZ dictionary.
#నిర్వచించు TINFL_LZ_DICT_కొలత 32768

// Return status.
రకనిర్వచనం గణన
{
  TINFL_స్థితి_BAD_PARAM = -3,
  TINFL_స్థితి_ADLER32_MISMATCH = -2,
  TINFL_స్థితి_FAILED = -1,
  TINFL_స్థితి_పూర్తి = 0,
  TINFL_స్థితి_NEEDS_మరిన్ని_ఆదానం = 1,
  TINFL_స్థితి_HAS_మరిన్ని_OUTPUT = 2
} tinfl_స్థితి;

// Initializes the decompressor to its initial state.
#నిర్వచించు tinfl_init(r) చేయి { (r)->m_state = 0; } MZ_MACRO_చివర
#నిర్వచించు tinfl_get_adler32(r) (r)->m_check_adler32

// Main low-level decompressor coroutine function. This is the only function actually needed for decompression. All the other functions are just high-level helpers for improved usability.
// This is a universal API, i.e. it can be used as a building block to build any desired higher level decompression API. In the limit case, it can be called once per every byte input or output.
MINIZ_STATIC tinfl_స్థితి tinfl_decompress(tinfl_decompressor *r, స్థిరరాశి mz_uint8 *p_లోపల_buf_తదుపరి, size_t *p_లోపల_buf_కొలత, mz_uint8 *p_బహిర్గతం_buf_ప్రారంభం, mz_uint8 *p_బహిర్గతం_buf_తదుపరి, size_t *p_బహిర్గతం_buf_కొలత, స్థిరరాశి mz_uint32 decomp_flags);

// Internal/private bits follow.
గణన
{
  TINFL_MAX_HUFF_TABLES = 3, TINFL_MAX_HUFF_SYMBOLS_0 = 288, TINFL_MAX_HUFF_SYMBOLS_1 = 32, TINFL_MAX_HUFF_SYMBOLS_2 = 19,
  TINFL_FAST_LOOKUP_బిట్లు = 10, TINFL_FAST_LOOKUP_కొలత = 1 << TINFL_FAST_LOOKUP_బిట్లు
};

రకనిర్వచనం నిర్మాణం
{
  mz_uint8 m_సంకేతం_కొలత[TINFL_MAX_HUFF_SYMBOLS_0];
  mz_int16 m_look_పైకి[TINFL_FAST_LOOKUP_కొలత], m_వృక్షం[TINFL_MAX_HUFF_SYMBOLS_0 * 2];
} tinfl_huff_పట్టిక;

#ఒకవేళ MINIZ_HAS_64_బిట్టు_REGISTERS
  #నిర్వచించు TINFL_USE_64_బిట్టు_BITBUF 1
#అయితే_ముగింపు

#ఒకవేళ TINFL_USE_64_బిట్టు_BITBUF
  రకనిర్వచనం mz_uint64 tinfl_బిట్టు_buf_t;
  #నిర్వచించు TINFL_BITBUF_కొలత (64)
#లేకపోతే
  రకనిర్వచనం mz_uint32 tinfl_బిట్టు_buf_t;
  #నిర్వచించు TINFL_BITBUF_కొలత (32)
#అయితే_ముగింపు

నిర్మాణం tinfl_decompressor_ట్యాగ్
{
  mz_uint32 m_state, m_అంకె_బిట్లు, m_zhdr0, m_zhdr1, m_z_adler32, m_final, m_type, m_check_adler32, m_dist, m_counter, m_అంకె_extra, m_పట్టిక_sizes[TINFL_MAX_HUFF_TABLES];
  tinfl_బిట్టు_buf_t m_బిట్టు_buf;
  size_t m_dist_from_బహిర్గతం_buf_ప్రారంభం;
  tinfl_huff_పట్టిక m_tables[TINFL_MAX_HUFF_TABLES];
  mz_uint8 m_raw_శీర్షిక[4], m_len_codes[TINFL_MAX_HUFF_SYMBOLS_0 + TINFL_MAX_HUFF_SYMBOLS_1 + 137];
};
#అయితే_ముగింపు /*#ifndef MINIZ_NO_INFLATE_APIS*/

// ------------------- Low-level Compression API Definitions
#నిర్వచితం_కాకపోతే MINIZ_NO_DEFLATE_APIS

// Set TDEFL_LESS_MEMORY to 1 to use less memory (compression will be slightly slower, and raw/dynamic blocks will be output more frequently).
#నిర్వచించు TDEFL_LESS_జ్ఞాపకం 0

// tdefl_init() compression flags logically OR'd together (low 12 bits contain the max. number of probes per dictionary search):
// TDEFL_DEFAULT_MAX_PROBES: The compressor defaults to 128 dictionary probes per dictionary search. 0=Huffman only, 1=Huffman+LZ (fastest/crap compression), 4095=Huffman+LZ (slowest/best compression).
గణన
{
  TDEFL_HUFFMAN_ONLY = 0, TDEFL_DEFAULT_MAX_PROBES = 128, TDEFL_MAX_PROBES_ముసుగు = 0xFFF
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
గణన
{
  TDEFL_WRITE_ZLIB_శీర్షిక             = 0x01000,
  TDEFL_COMPUTE_ADLER32               = 0x02000,
  TDEFL_GREEDY_PARSING_FLAG           = 0x04000,
  TDEFL_NONDETERMINISTIC_PARSING_FLAG = 0x08000,
  TDEFL_RLE_MATCHES                   = 0x10000,
  TDEFL_FILTER_MATCHES                = 0x20000,
  TDEFL_FORCE_ALL_STATIC_ఖండాలు       = 0x40000,
  TDEFL_FORCE_ALL_RAW_ఖండాలు          = 0x80000
};

#నిర్వచితం_కాకపోతే MINIZ_SDL_NOUNUSED
// High level compression functions:
// tdefl_compress_mem_to_heap() compresses a block in memory to a heap block allocated via malloc().
// On entry:
//  pSrc_buf, src_buf_len: Pointer and size of source block to compress.
//  flags: The max match finder probes (default is 128) logically OR'd against the above flags. Higher probes are slower but improve compression.
// On return:
//  Function returns a pointer to the compressed data, or NULL on failure.
//  *pOut_len will be set to the compressed data's size, which could be larger than src_buf_len on uncompressible data.
//  The caller must free() the returned block when it's no longer needed.
MINIZ_STATIC శూన్య *tdefl_compress_mem_గమ్యం_కుప్ప(స్థిరరాశి శూన్య *pSrc_buf, size_t src_buf_len, size_t *p_బహిర్గతం_len, పూర్ణాంకం flags);

// tdefl_compress_mem_to_mem() compresses a block in memory to another block in memory.
// Returns 0 on failure.
MINIZ_STATIC size_t tdefl_compress_mem_గమ్యం_mem(శూన్య *p_బహిర్గతం_buf, size_t బహిర్గతం_buf_len, స్థిరరాశి శూన్య *pSrc_buf, size_t src_buf_len, పూర్ణాంకం flags);
#అయితే_ముగింపు /* MINIZ_SDL_NOUNUSED */

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
MINIZ_STATIC శూన్య *tdefl_write_image_గమ్యం_png_file_లోపల_జ్ఞాపకం_ex(స్థిరరాశి శూన్య *pImage, పూర్ణాంకం w, పూర్ణాంకం h, పూర్ణాంకం అంకె_chans, పూర్ణాంకం bpl, size_t *p_Len_బహిర్గతం, mz_uint level, mz_bool flip, mz_uint8 *plte, పూర్ణాంకం plte_కొలత, mz_uint8 *trns, పూర్ణాంకం trns_కొలత);
#నిర్వచితం_కాకపోతే MINIZ_SDL_NOUNUSED
MINIZ_STATIC శూన్య *tdefl_write_image_గమ్యం_png_file_లోపల_జ్ఞాపకం(స్థిరరాశి శూన్య *pImage, పూర్ణాంకం w, పూర్ణాంకం h, పూర్ణాంకం అంకె_chans, పూర్ణాంకం bpl, size_t *p_Len_బహిర్గతం);
#అయితే_ముగింపు

// Output stream interface. The compressor uses this interface to write compressed data. It'll typically be called TDEFL_OUT_BUF_SIZE at a time.
రకనిర్వచనం mz_bool (*tdefl_put_buf_func_ptr)(స్థిరరాశి శూన్య* pBuf, పూర్ణాంకం len, శూన్య *pUser);

#నిర్వచితం_కాకపోతే MINIZ_SDL_NOUNUSED
// tdefl_compress_mem_to_output() compresses a block to an output stream. The above helpers use this function internally.
MINIZ_STATIC mz_bool tdefl_compress_mem_గమ్యం_output(స్థిరరాశి శూన్య *pBuf, size_t buf_len, tdefl_put_buf_func_ptr pPut_buf_func, శూన్య *pPut_buf_user, పూర్ణాంకం flags);
#అయితే_ముగింపు

//enum { TDEFL_MAX_HUFF_TABLES = 3, TDEFL_MAX_HUFF_SYMBOLS_0 = 288, TDEFL_MAX_HUFF_SYMBOLS_1 = 32, TDEFL_MAX_HUFF_SYMBOLS_2 = 19, TDEFL_LZ_DICT_SIZE = 32768, TDEFL_LZ_DICT_SIZE_MASK = TDEFL_LZ_DICT_SIZE - 1, TDEFL_MIN_MATCH_LEN = 3, TDEFL_MAX_MATCH_LEN = 258 };
#నిర్వచించు TDEFL_MAX_HUFF_TABLES	3
#నిర్వచించు TDEFL_MAX_HUFF_SYMBOLS_0 288
#నిర్వచించు TDEFL_MAX_HUFF_SYMBOLS_1 32
#నిర్వచించు TDEFL_MAX_HUFF_SYMBOLS_2 19
#నిర్వచించు TDEFL_LZ_DICT_కొలత 32768
#నిర్వచించు TDEFL_LZ_DICT_కొలత_ముసుగు	( TDEFL_LZ_DICT_కొలత - 1 )
#నిర్వచించు TDEFL_MIN_సరిపోలిక_LEN	3
#నిర్వచించు TDEFL_MAX_సరిపోలిక_LEN 258

// TDEFL_OUT_BUF_SIZE MUST be large enough to hold a single entire compressed output block (using static/fixed Huffman codes).
#ఒకవేళ TDEFL_LESS_జ్ఞాపకం
గణన { TDEFL_LZ_సంకేతం_BUF_కొలత = 24 * 1024, TDEFL_బహిర్గతం_BUF_కొలత = (TDEFL_LZ_సంకేతం_BUF_కొలత * 13 ) / 10, TDEFL_MAX_HUFF_SYMBOLS = 288, TDEFL_LZ_HASH_బిట్లు = 12, TDEFL_LEVEL1_HASH_కొలత_ముసుగు = 4095, TDEFL_LZ_HASH_జరుపు = (TDEFL_LZ_HASH_బిట్లు + 2) / 3, TDEFL_LZ_HASH_కొలత = 1 << TDEFL_LZ_HASH_బిట్లు };
#లేకపోతే
గణన { TDEFL_LZ_సంకేతం_BUF_కొలత = 64 * 1024, TDEFL_బహిర్గతం_BUF_కొలత = (TDEFL_LZ_సంకేతం_BUF_కొలత * 13 ) / 10, TDEFL_MAX_HUFF_SYMBOLS = 288, TDEFL_LZ_HASH_బిట్లు = 15, TDEFL_LEVEL1_HASH_కొలత_ముసుగు = 4095, TDEFL_LZ_HASH_జరుపు = (TDEFL_LZ_HASH_బిట్లు + 2) / 3, TDEFL_LZ_HASH_కొలత = 1 << TDEFL_LZ_HASH_బిట్లు };
#అయితే_ముగింపు

// The low-level tdefl functions below may be used directly if the above helper functions aren't flexible enough. The low-level functions don't make any heap allocations, unlike the above helper functions.
రకనిర్వచనం గణన
{
  TDEFL_స్థితి_BAD_PARAM = -2,
  TDEFL_స్థితి_PUT_BUF_FAILED = -1,
  TDEFL_స్థితి_OKAY = 0,
  TDEFL_స్థితి_పూర్తి = 1,
} tdefl_స్థితి;

// Must map to MZ_NO_FLUSH, MZ_SYNC_FLUSH, etc. enums
రకనిర్వచనం గణన
{
  TDEFL_NO_FLUSH = 0,
  TDEFL_SYNC_FLUSH = 2,
  TDEFL_నిండిన_FLUSH = 3,
  TDEFL_ముగింపు = 4
} tdefl_flush;

// tdefl's compression state structure.
రకనిర్వచనం నిర్మాణం
{
  tdefl_put_buf_func_ptr m_pPut_buf_func;
  శూన్య *m_pPut_buf_user;
  mz_uint m_flags, m_max_probes[2];
  పూర్ణాంకం m_greedy_parsing;
  mz_uint m_adler32, m_lookahead_pos, m_lookahead_కొలత, m_dict_కొలత;
  mz_uint8 *m_p_LZ_సంకేతం_buf, *m_pLZ_flags, *m_pOutput_buf, *m_p_Output_buf_చివర;
  mz_uint m_అంకె_flags_ఎడమ, m_మొత్తం_lz_బైట్లు, m_lz_సంకేతం_buf_dict_pos, m_బిట్లు_లోపల, m_బిట్టు_బఫరు;
  mz_uint m_saved_సరిపోలిక_dist, m_saved_సరిపోలిక_len, m_saved_lit, m_output_flush_ofs, m_output_flush_మిగిలిన, m_ముగిసిన, m_ఖండం_సూచీ, m_కోరుతుంది_గమ్యం_ముగింపు;
  tdefl_స్థితి m_prev_return_స్థితి;
  స్థిరరాశి శూన్య *m_p_లోపల_buf;
  శూన్య *m_p_బహిర్గతం_buf;
  size_t *m_p_లోపల_buf_కొలత, *m_p_బహిర్గతం_buf_కొలత;
  tdefl_flush m_flush;
  స్థిరరాశి mz_uint8 *m_pSrc;
  size_t m_src_buf_ఎడమ, m_బహిర్గతం_buf_ofs;
  mz_uint8 m_dict[TDEFL_LZ_DICT_కొలత + TDEFL_MAX_సరిపోలిక_LEN - 1];
  mz_uint16 m_huff_లెక్క[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint16 m_huff_codes[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint8 m_huff_సంకేతం_sizes[TDEFL_MAX_HUFF_TABLES][TDEFL_MAX_HUFF_SYMBOLS];
  mz_uint8 m_lz_సంకేతం_buf[TDEFL_LZ_సంకేతం_BUF_కొలత];
  mz_uint16 m_తదుపరి[TDEFL_LZ_DICT_కొలత];
  mz_uint16 m_hash[TDEFL_LZ_HASH_కొలత];
  mz_uint8 m_output_buf[TDEFL_బహిర్గతం_BUF_కొలత];
} tdefl_compressor;

// Initializes the compressor.
// There is no corresponding deinit() function because the tdefl API's do not dynamically allocate memory.
// pBut_buf_func: If NULL, output data will be supplied to the specified callback. In this case, the user should call the tdefl_compress_buffer() API for compression.
// If pBut_buf_func is NULL the user should always call the tdefl_compress() API.
// flags: See the above enums (TDEFL_HUFFMAN_ONLY, TDEFL_WRITE_ZLIB_HEADER, etc.)
MINIZ_STATIC tdefl_స్థితి tdefl_init(tdefl_compressor *d, tdefl_put_buf_func_ptr pPut_buf_func, శూన్య *pPut_buf_user, పూర్ణాంకం flags);

// Compresses a block of data, consuming as much of the specified input buffer as possible, and writing as much compressed data to the specified output buffer as possible.
MINIZ_STATIC tdefl_స్థితి tdefl_compress(tdefl_compressor *d, స్థిరరాశి శూన్య *p_లోపల_buf, size_t *p_లోపల_buf_కొలత, శూన్య *p_బహిర్గతం_buf, size_t *p_బహిర్గతం_buf_కొలత, tdefl_flush flush);

// tdefl_compress_buffer() is only usable when the tdefl_init() is called with a non-NULL tdefl_put_buf_func_ptr.
// tdefl_compress_buffer() always consumes the entire input buffer.
MINIZ_STATIC tdefl_స్థితి tdefl_compress_బఫరు(tdefl_compressor *d, స్థిరరాశి శూన్య *p_లోపల_buf, size_t లోపల_buf_కొలత, tdefl_flush flush);

#నిర్వచితం_కాకపోతే MINIZ_SDL_NOUNUSED
MINIZ_STATIC tdefl_స్థితి tdefl_get_prev_return_స్థితి(tdefl_compressor *d);
MINIZ_STATIC mz_uint32 tdefl_get_adler32(tdefl_compressor *d);
#అయితే_ముగింపు

// Can't use tdefl_create_comp_flags_from_zip_params if MINIZ_NO_ZLIB_APIS isn't defined, because it uses some of its macros.
#నిర్వచితం_కాకపోతే MINIZ_NO_ZLIB_APIS
// Create tdefl_compress() flags given zlib-style compression parameters.
// level may range from [0,10] (where 10 is absolute max compression, but may be much slower on some files)
// window_bits may be -15 (raw deflate) or 15 (zlib)
// strategy may be either MZ_DEFAULT_STRATEGY, MZ_FILTERED, MZ_HUFFMAN_ONLY, MZ_RLE, or MZ_FIXED
MINIZ_STATIC mz_uint tdefl_create_comp_flags_from_zip_params(పూర్ణాంకం level, పూర్ణాంకం కిటికీ_బిట్లు, పూర్ణాంకం strategy);
#అయితే_ముగింపు // #ifndef MINIZ_NO_ZLIB_APIS

#అయితే_ముగింపు /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు // MINIZ_HEADER_INCLUDED

// ------------------- End of Header: Implementation follows. (If you only want the header, define MINIZ_HEADER_FILE_ONLY.)

#నిర్వచితం_కాకపోతే MINIZ_శీర్షిక_FILE_ONLY

#నిర్వచితమైతే _MSC_VER
#సూచన warning (నెట్టు)
#సూచన warning (disable:4505) // unreferenced local function has been removed
#అయితే_ముగింపు

రకనిర్వచనం గుర్తులేని అక్షరం mz_validate_uint16[పరిమాణం(mz_uint16)==2 ? 1 : -1];
రకనిర్వచనం గుర్తులేని అక్షరం mz_validate_uint32[పరిమాణం(mz_uint32)==4 ? 1 : -1];
రకనిర్వచనం గుర్తులేని అక్షరం mz_validate_uint64[పరిమాణం(mz_uint64)==8 ? 1 : -1];

/*#include <string.h>*/

#నిర్వచితం_కాకపోతే MZ_ASSERT
#అన్తర్భావ <assert.h>
#నిర్వచించు MZ_ASSERT(x) ప్రతిజ్ఞా(x)
#అయితే_ముగింపు

#నిర్వచితమైతే MINIZ_NO_MALLOC
  #నిర్వచించు MZ_MALLOC(x) ఖాళీ
  #నిర్వచించు MZ_FREE(x) (శూన్య)x, ((శూన్య)0)
  #నిర్వచించు MZ_REALLOC(p, x) ఖాళీ
#లేదావేళ defined(MINIZ_SDL_MALLOC)
  #నిర్వచించు MZ_MALLOC(x) SDL_malloc(x)
  #నిర్వచించు MZ_FREE(x) SDL_free(x)
  #నిర్వచించు MZ_REALLOC(p, x) SDL_realloc(p, x)
#లేకపోతే
  #నిర్వచించు MZ_MALLOC(x) జ్ఞాపకం_ఇవ్వు(x)
  #నిర్వచించు MZ_FREE(x) విడుదల(x)
  #నిర్వచించు MZ_REALLOC(p, x) realloc(p, x)
#అయితే_ముగింపు

#నిర్వచించు MZ_MAX(a,b) (((a)>(b))?(a):(b))
#నిర్వచించు MZ_MIN(a,b) (((a)<(b))?(a):(b))
#నిర్వచించు MZ_CLEAR_OBJ(obj) memset(&(obj), 0, పరిమాణం(obj))
#నిర్వచించు MZ_CLEAR_ARR(obj) memset((obj), 0, పరిమాణం(obj))
#నిర్వచించు MZ_CLEAR_PTR(obj) memset((obj), 0, పరిమాణం(*obj))

#ఒకవేళ MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  #నిర్వచించు MZ_READ_LE16(p) *((స్థిరరాశి mz_uint16 *)(p))
  #నిర్వచించు MZ_READ_LE32(p) *((స్థిరరాశి mz_uint32 *)(p))
#లేకపోతే
  #నిర్వచించు MZ_READ_LE16(p) ((mz_uint32)(((స్థిరరాశి mz_uint8 *)(p))[0]) | ((mz_uint32)(((స్థిరరాశి mz_uint8 *)(p))[1]) << 8U))
  #నిర్వచించు MZ_READ_LE32(p) ((mz_uint32)(((స్థిరరాశి mz_uint8 *)(p))[0]) | ((mz_uint32)(((స్థిరరాశి mz_uint8 *)(p))[1]) << 8U) | ((mz_uint32)(((స్థిరరాశి mz_uint8 *)(p))[2]) << 16U) | ((mz_uint32)(((స్థిరరాశి mz_uint8 *)(p))[3]) << 24U))
#అయితే_ముగింపు

#నిర్వచితమైతే _MSC_VER
  #నిర్వచించు MZ_FORCEINLINE __forceinline
#లేదావేళ defined(__GNUC__)
  #నిర్వచించు MZ_FORCEINLINE అంతఃవరుస __attribute__((__always_inline__))
#లేకపోతే
  #నిర్వచించు MZ_FORCEINLINE అంతఃవరుస
#అయితే_ముగింపు

#నిర్వచితమైతే __cplusplus
  బాహ్య "C" {
#అయితే_ముగింపు

// ------------------- zlib-style API's

mz_ulong mz_adler32(mz_ulong adler, స్థిరరాశి గుర్తులేని అక్షరం *ptr, size_t buf_len)
{
  mz_uint32 i, s1 = (mz_uint32)(adler & 0xffff), s2 = (mz_uint32)(adler >> 16); size_t ఖండం_len = buf_len % 5552;
  ఒకవేళ (!ptr) తిరిగి MZ_ADLER32_INIT;
  అయితే (buf_len) {
    కొరకు (i = 0; i + 7 < ఖండం_len; i += 8, ptr += 8) {
      s1 += ptr[0]; s2 += s1; s1 += ptr[1]; s2 += s1; s1 += ptr[2]; s2 += s1; s1 += ptr[3]; s2 += s1;
      s1 += ptr[4]; s2 += s1; s1 += ptr[5]; s2 += s1; s1 += ptr[6]; s2 += s1; s1 += ptr[7]; s2 += s1;
    }
    కొరకు ( ; i < ఖండం_len; ++i) { s1 += *ptr++; s2 += s1; }
    s1 %= 65521U; s2 %= 65521U; buf_len -= ఖండం_len; ఖండం_len = 5552;
  }
  తిరిగి (s2 << 16) + s1;
}

// Karl Malbrain's compact CRC-32. See "A compact CCITT crc16 and crc32 C implementation that balances processor cache usage against speed": http://www.geocities.com/malbrain/
mz_ulong mz_చక్రీయ_తనిఖీ_32(mz_ulong చక్రీయ_తనిఖీ, స్థిరరాశి mz_uint8 *ptr, size_t buf_len)
{
  స్థిర స్థిరరాశి mz_uint32 s_చక్రీయ_తనిఖీ_32[16] = { 0, 0x1db71064, 0x3b6e20c8, 0x26d930ac, 0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
    0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c, 0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c };
  mz_uint32 crcu32 = (mz_uint32)చక్రీయ_తనిఖీ;
  ఒకవేళ (!ptr) తిరిగి MZ_చక్రీయ_తనిఖీ_32_INIT;
  crcu32 = ~crcu32; అయితే (buf_len--) { mz_uint8 b = *ptr++; crcu32 = (crcu32 >> 4) ^ s_చక్రీయ_తనిఖీ_32[(crcu32 & 0xF) ^ (b & 0xF)]; crcu32 = (crcu32 >> 4) ^ s_చక్రీయ_తనిఖీ_32[(crcu32 & 0xF) ^ (b >> 4)]; }
  తిరిగి ~crcu32;
}

MINIZ_STATIC శూన్య mz_free(శూన్య *p)
{
  MZ_FREE(p);
}

#నిర్వచితం_కాకపోతే MINIZ_NO_ZLIB_APIS

స్థిర శూన్య *def_alloc_func(శూన్య *opaque, size_t వస్తువులు, size_t కొలత) { (శూన్య)opaque, (శూన్య)వస్తువులు, (శూన్య)కొలత; తిరిగి MZ_MALLOC(వస్తువులు * కొలత); }
స్థిర శూన్య def_free_func(శూన్య *opaque, శూన్య *చిరునామా) { (శూన్య)opaque, (శూన్య)చిరునామా; MZ_FREE(చిరునామా); }
స్థిర శూన్య *def_realloc_func(శూన్య *opaque, శూన్య *చిరునామా, size_t వస్తువులు, size_t కొలత) { (శూన్య)opaque, (శూన్య)చిరునామా, (శూన్య)వస్తువులు, (శూన్య)కొలత; తిరిగి MZ_REALLOC(చిరునామా, వస్తువులు * కొలత); }

స్థిరరాశి అక్షరం *mz_సంస్కరణ(శూన్య)
{
  తిరిగి MZ_సంస్కరణ;
}

#నిర్వచితం_కాకపోతే MINIZ_NO_DEFLATE_APIS

పూర్ణాంకం mz_deflateInit(mz_streamp p_ప్రవాహం, పూర్ణాంకం level)
{
  తిరిగి mz_deflateInit2(p_ప్రవాహం, level, MZ_DEFLATED, MZ_DEFAULT_కిటికీ_బిట్లు, 9, MZ_DEFAULT_STRATEGY);
}

పూర్ణాంకం mz_deflateInit2(mz_streamp p_ప్రవాహం, పూర్ణాంకం level, పూర్ణాంకం పద్ధతి, పూర్ణాంకం కిటికీ_బిట్లు, పూర్ణాంకం mem_level, పూర్ణాంకం strategy)
{
  tdefl_compressor *pComp;
  mz_uint comp_flags = TDEFL_COMPUTE_ADLER32 | tdefl_create_comp_flags_from_zip_params(level, కిటికీ_బిట్లు, strategy);

  ఒకవేళ (!p_ప్రవాహం) తిరిగి MZ_ప్రవాహం_ERROR;
  ఒకవేళ ((పద్ధతి != MZ_DEFLATED) || ((mem_level < 1) || (mem_level > 9)) || ((కిటికీ_బిట్లు != MZ_DEFAULT_కిటికీ_బిట్లు) && (-కిటికీ_బిట్లు != MZ_DEFAULT_కిటికీ_బిట్లు))) తిరిగి MZ_PARAM_ERROR;

  p_ప్రవాహం->దత్తాంశం_type = 0;
  p_ప్రవాహం->adler = MZ_ADLER32_INIT;
  p_ప్రవాహం->సందేశం_2 = ఖాళీ;
  p_ప్రవాహం->reserved = 0;
  p_ప్రవాహం->మొత్తం_లోపల = 0;
  p_ప్రవాహం->మొత్తం_బహిర్గతం = 0;
  ఒకవేళ (!p_ప్రవాహం->zalloc) p_ప్రవాహం->zalloc = def_alloc_func;
  ఒకవేళ (!p_ప్రవాహం->zfree) p_ప్రవాహం->zfree = def_free_func;

  pComp = (tdefl_compressor *)p_ప్రవాహం->zalloc(p_ప్రవాహం->opaque, 1, పరిమాణం(tdefl_compressor));
  ఒకవేళ (!pComp)
    తిరిగి MZ_MEM_ERROR;

  p_ప్రవాహం->state = (నిర్మాణం mz_అంతర్గత_state *)pComp;

  ఒకవేళ (tdefl_init(pComp, ఖాళీ, ఖాళీ, comp_flags) != TDEFL_స్థితి_OKAY)
  {
    mz_deflate_చివర(p_ప్రవాహం);
    తిరిగి MZ_PARAM_ERROR;
  }

  తిరిగి MZ_OK;
}

పూర్ణాంకం mz_deflateReset(mz_streamp p_ప్రవాహం)
{
  ఒకవేళ ((!p_ప్రవాహం) || (!p_ప్రవాహం->state) || (!p_ప్రవాహం->zalloc) || (!p_ప్రవాహం->zfree)) తిరిగి MZ_ప్రవాహం_ERROR;
  p_ప్రవాహం->మొత్తం_లోపల = p_ప్రవాహం->మొత్తం_బహిర్గతం = 0;
  tdefl_init((tdefl_compressor*)p_ప్రవాహం->state, ఖాళీ, ఖాళీ, ((tdefl_compressor*)p_ప్రవాహం->state)->m_flags);
  తిరిగి MZ_OK;
}

పూర్ణాంకం mz_deflate(mz_streamp p_ప్రవాహం, పూర్ణాంకం flush)
{
  size_t లోపల_బైట్లు, బహిర్గతం_బైట్లు;
  mz_ulong orig_మొత్తం_లోపల, orig_మొత్తం_బహిర్గతం;
  పూర్ణాంకం mz_స్థితి = MZ_OK;

  ఒకవేళ ((!p_ప్రవాహం) || (!p_ప్రవాహం->state) || (flush < 0) || (flush > MZ_ముగింపు) || (!p_ప్రవాహం->తదుపరి_బహిర్గతం)) తిరిగి MZ_ప్రవాహం_ERROR;
  ఒకవేళ (!p_ప్రవాహం->avail_బహిర్గతం) తిరిగి MZ_BUF_ERROR;

  ఒకవేళ (flush == MZ_PARTIAL_FLUSH) flush = MZ_SYNC_FLUSH;

  ఒకవేళ (((tdefl_compressor*)p_ప్రవాహం->state)->m_prev_return_స్థితి == TDEFL_స్థితి_పూర్తి)
    తిరిగి (flush == MZ_ముగింపు) ? MZ_ప్రవాహం_చివర : MZ_BUF_ERROR;

  orig_మొత్తం_లోపల = p_ప్రవాహం->మొత్తం_లోపల; orig_మొత్తం_బహిర్గతం = p_ప్రవాహం->మొత్తం_బహిర్గతం;
  కొరకు ( ; ; )
  {
    tdefl_స్థితి defl_స్థితి;
    లోపల_బైట్లు = p_ప్రవాహం->avail_లోపల; బహిర్గతం_బైట్లు = p_ప్రవాహం->avail_బహిర్గతం;

    defl_స్థితి = tdefl_compress((tdefl_compressor*)p_ప్రవాహం->state, p_ప్రవాహం->తదుపరి_లోపల, &లోపల_బైట్లు, p_ప్రవాహం->తదుపరి_బహిర్గతం, &బహిర్గతం_బైట్లు, (tdefl_flush)flush);
    p_ప్రవాహం->తదుపరి_లోపల += (mz_uint)లోపల_బైట్లు; p_ప్రవాహం->avail_లోపల -= (mz_uint)లోపల_బైట్లు;
    p_ప్రవాహం->మొత్తం_లోపల += (mz_uint)లోపల_బైట్లు; p_ప్రవాహం->adler = tdefl_get_adler32((tdefl_compressor*)p_ప్రవాహం->state);

    p_ప్రవాహం->తదుపరి_బహిర్గతం += (mz_uint)బహిర్గతం_బైట్లు; p_ప్రవాహం->avail_బహిర్గతం -= (mz_uint)బహిర్గతం_బైట్లు;
    p_ప్రవాహం->మొత్తం_బహిర్గతం += (mz_uint)బహిర్గతం_బైట్లు;

    ఒకవేళ (defl_స్థితి < 0)
    {
      mz_స్థితి = MZ_ప్రవాహం_ERROR;
      ఆపు;
    }
    లేకపోతే ఒకవేళ (defl_స్థితి == TDEFL_స్థితి_పూర్తి)
    {
      mz_స్థితి = MZ_ప్రవాహం_చివర;
      ఆపు;
    }
    లేకపోతే ఒకవేళ (!p_ప్రవాహం->avail_బహిర్గతం)
      ఆపు;
    లేకపోతే ఒకవేళ ((!p_ప్రవాహం->avail_లోపల) && (flush != MZ_ముగింపు))
    {
      ఒకవేళ ((flush) || (p_ప్రవాహం->మొత్తం_లోపల != orig_మొత్తం_లోపల) || (p_ప్రవాహం->మొత్తం_బహిర్గతం != orig_మొత్తం_బహిర్గతం))
        ఆపు;
      తిరిగి MZ_BUF_ERROR; // Can't make forward progress without some input.
    }
  }
  తిరిగి mz_స్థితి;
}

పూర్ణాంకం mz_deflate_చివర(mz_streamp p_ప్రవాహం)
{
  ఒకవేళ (!p_ప్రవాహం) తిరిగి MZ_ప్రవాహం_ERROR;
  ఒకవేళ (p_ప్రవాహం->state)
  {
    p_ప్రవాహం->zfree(p_ప్రవాహం->opaque, p_ప్రవాహం->state);
    p_ప్రవాహం->state = ఖాళీ;
  }
  తిరిగి MZ_OK;
}

mz_ulong mz_deflateBound(mz_streamp p_ప్రవాహం, mz_ulong ఆధారం_len)
{
  (శూన్య)p_ప్రవాహం;
  // This is really over conservative. (And lame, but it's actually pretty tricky to compute a true upper bound given the way tdefl's blocking works.)
  తిరిగి MZ_MAX(128 + (ఆధారం_len * 110) / 100, 128 + ఆధారం_len + ((ఆధారం_len / (31 * 1024)) + 1) * 5);
}

పూర్ణాంకం mz_compress2(గుర్తులేని అక్షరం *pDest, mz_ulong *pDest_len, స్థిరరాశి గుర్తులేని అక్షరం *p_ఆధారం, mz_ulong ఆధారం_len, పూర్ణాంకం level)
{
  పూర్ణాంకం స్థితి_2;
  mz_ప్రవాహం ప్రవాహం;
  memset(&ప్రవాహం, 0, పరిమాణం(ప్రవాహం));

  // In case mz_ulong is 64-bits (argh I hate longs).
  ఒకవేళ ((ఆధారం_len | *pDest_len) > 0xFFFFFFFFU) తిరిగి MZ_PARAM_ERROR;

  ప్రవాహం.తదుపరి_లోపల = p_ఆధారం;
  ప్రవాహం.avail_లోపల = (mz_uint32)ఆధారం_len;
  ప్రవాహం.తదుపరి_బహిర్గతం = pDest;
  ప్రవాహం.avail_బహిర్గతం = (mz_uint32)*pDest_len;

  స్థితి_2 = mz_deflateInit(&ప్రవాహం, level);
  ఒకవేళ (స్థితి_2 != MZ_OK) తిరిగి స్థితి_2;

  స్థితి_2 = mz_deflate(&ప్రవాహం, MZ_ముగింపు);
  ఒకవేళ (స్థితి_2 != MZ_ప్రవాహం_చివర)
  {
    mz_deflate_చివర(&ప్రవాహం);
    తిరిగి (స్థితి_2 == MZ_OK) ? MZ_BUF_ERROR : స్థితి_2;
  }

  *pDest_len = ప్రవాహం.మొత్తం_బహిర్గతం;
  తిరిగి mz_deflate_చివర(&ప్రవాహం);
}

పూర్ణాంకం mz_compress(గుర్తులేని అక్షరం *pDest, mz_ulong *pDest_len, స్థిరరాశి గుర్తులేని అక్షరం *p_ఆధారం, mz_ulong ఆధారం_len)
{
  తిరిగి mz_compress2(pDest, pDest_len, p_ఆధారం, ఆధారం_len, MZ_DEFAULT_COMPRESSION);
}

mz_ulong mz_compressBound(mz_ulong ఆధారం_len)
{
  తిరిగి mz_deflateBound(ఖాళీ, ఆధారం_len);
}

#అయితే_ముగింపు /*#ifndef MINIZ_NO_DEFLATE_APIS*/

#నిర్వచితం_కాకపోతే MINIZ_NO_INFLATE_APIS

రకనిర్వచనం నిర్మాణం
{
  tinfl_decompressor m_decomp;
  mz_uint m_dict_ofs, m_dict_avail, m_మొదటి_call, m_has_flushed; పూర్ణాంకం m_కిటికీ_బిట్లు;
  mz_uint8 m_dict[TINFL_LZ_DICT_కొలత];
  tinfl_స్థితి m_చివరి_స్థితి;
} inflate_state;

పూర్ణాంకం mz_inflateInit2(mz_streamp p_ప్రవాహం, పూర్ణాంకం కిటికీ_బిట్లు)
{
  inflate_state *pDecomp;
  ఒకవేళ (!p_ప్రవాహం) తిరిగి MZ_ప్రవాహం_ERROR;
  ఒకవేళ ((కిటికీ_బిట్లు != MZ_DEFAULT_కిటికీ_బిట్లు) && (-కిటికీ_బిట్లు != MZ_DEFAULT_కిటికీ_బిట్లు)) తిరిగి MZ_PARAM_ERROR;

  p_ప్రవాహం->దత్తాంశం_type = 0;
  p_ప్రవాహం->adler = 0;
  p_ప్రవాహం->సందేశం_2 = ఖాళీ;
  p_ప్రవాహం->మొత్తం_లోపల = 0;
  p_ప్రవాహం->మొత్తం_బహిర్గతం = 0;
  p_ప్రవాహం->reserved = 0;
  ఒకవేళ (!p_ప్రవాహం->zalloc) p_ప్రవాహం->zalloc = def_alloc_func;
  ఒకవేళ (!p_ప్రవాహం->zfree) p_ప్రవాహం->zfree = def_free_func;

  pDecomp = (inflate_state*)p_ప్రవాహం->zalloc(p_ప్రవాహం->opaque, 1, పరిమాణం(inflate_state));
  ఒకవేళ (!pDecomp) తిరిగి MZ_MEM_ERROR;

  p_ప్రవాహం->state = (నిర్మాణం mz_అంతర్గత_state *)pDecomp;

  tinfl_init(&pDecomp->m_decomp);
  pDecomp->m_dict_ofs = 0;
  pDecomp->m_dict_avail = 0;
  pDecomp->m_చివరి_స్థితి = TINFL_స్థితి_NEEDS_మరిన్ని_ఆదానం;
  pDecomp->m_మొదటి_call = 1;
  pDecomp->m_has_flushed = 0;
  pDecomp->m_కిటికీ_బిట్లు = కిటికీ_బిట్లు;

  తిరిగి MZ_OK;
}

పూర్ణాంకం mz_inflateInit(mz_streamp p_ప్రవాహం)
{
   తిరిగి mz_inflateInit2(p_ప్రవాహం, MZ_DEFAULT_కిటికీ_బిట్లు);
}

పూర్ణాంకం mz_inflate(mz_streamp p_ప్రవాహం, పూర్ణాంకం flush)
{
  inflate_state* pState;
  mz_uint n, మొదటి_call, decomp_flags = TINFL_FLAG_COMPUTE_ADLER32;
  size_t లోపల_బైట్లు, బహిర్గతం_బైట్లు, orig_avail_లోపల;
  tinfl_స్థితి స్థితి_2;

  ఒకవేళ ((!p_ప్రవాహం) || (!p_ప్రవాహం->state)) తిరిగి MZ_ప్రవాహం_ERROR;
  ఒకవేళ (flush == MZ_PARTIAL_FLUSH) flush = MZ_SYNC_FLUSH;
  ఒకవేళ ((flush) && (flush != MZ_SYNC_FLUSH) && (flush != MZ_ముగింపు)) తిరిగి MZ_ప్రవాహం_ERROR;

  pState = (inflate_state*)p_ప్రవాహం->state;
  ఒకవేళ (pState->m_కిటికీ_బిట్లు > 0) decomp_flags |= TINFL_FLAG_PARSE_ZLIB_శీర్షిక;
  orig_avail_లోపల = p_ప్రవాహం->avail_లోపల;

  మొదటి_call = pState->m_మొదటి_call; pState->m_మొదటి_call = 0;
  ఒకవేళ (pState->m_చివరి_స్థితి < 0) తిరిగి MZ_దత్తాంశం_ERROR;

  ఒకవేళ (pState->m_has_flushed && (flush != MZ_ముగింపు)) తిరిగి MZ_ప్రవాహం_ERROR;
  pState->m_has_flushed |= (flush == MZ_ముగింపు);

  ఒకవేళ ((flush == MZ_ముగింపు) && (మొదటి_call))
  {
    // MZ_FINISH on the first call implies that the input and output buffers are large enough to hold the entire compressed/decompressed file.
    decomp_flags |= TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF;
    లోపల_బైట్లు = p_ప్రవాహం->avail_లోపల; బహిర్గతం_బైట్లు = p_ప్రవాహం->avail_బహిర్గతం;
    స్థితి_2 = tinfl_decompress(&pState->m_decomp, p_ప్రవాహం->తదుపరి_లోపల, &లోపల_బైట్లు, p_ప్రవాహం->తదుపరి_బహిర్గతం, p_ప్రవాహం->తదుపరి_బహిర్గతం, &బహిర్గతం_బైట్లు, decomp_flags);
    pState->m_చివరి_స్థితి = స్థితి_2;
    p_ప్రవాహం->తదుపరి_లోపల += (mz_uint)లోపల_బైట్లు; p_ప్రవాహం->avail_లోపల -= (mz_uint)లోపల_బైట్లు; p_ప్రవాహం->మొత్తం_లోపల += (mz_uint)లోపల_బైట్లు;
    p_ప్రవాహం->adler = tinfl_get_adler32(&pState->m_decomp);
    p_ప్రవాహం->తదుపరి_బహిర్గతం += (mz_uint)బహిర్గతం_బైట్లు; p_ప్రవాహం->avail_బహిర్గతం -= (mz_uint)బహిర్గతం_బైట్లు; p_ప్రవాహం->మొత్తం_బహిర్గతం += (mz_uint)బహిర్గతం_బైట్లు;

    ఒకవేళ (స్థితి_2 < 0)
      తిరిగి MZ_దత్తాంశం_ERROR;
    లేకపోతే ఒకవేళ (స్థితి_2 != TINFL_స్థితి_పూర్తి)
    {
      pState->m_చివరి_స్థితి = TINFL_స్థితి_FAILED;
      తిరిగి MZ_BUF_ERROR;
    }
    తిరిగి MZ_ప్రవాహం_చివర;
  }
  // flush != MZ_FINISH then we must assume there's more input.
  ఒకవేళ (flush != MZ_ముగింపు) decomp_flags |= TINFL_FLAG_HAS_మరిన్ని_ఆదానం;

  ఒకవేళ (pState->m_dict_avail)
  {
    n = MZ_MIN(pState->m_dict_avail, p_ప్రవాహం->avail_బహిర్గతం);
    జ్ఞాపకం_నకలు(p_ప్రవాహం->తదుపరి_బహిర్గతం, pState->m_dict + pState->m_dict_ofs, n);
    p_ప్రవాహం->తదుపరి_బహిర్గతం += n; p_ప్రవాహం->avail_బహిర్గతం -= n; p_ప్రవాహం->మొత్తం_బహిర్గతం += n;
    pState->m_dict_avail -= n; pState->m_dict_ofs = (pState->m_dict_ofs + n) & (TINFL_LZ_DICT_కొలత - 1);
    తిరిగి ((pState->m_చివరి_స్థితి == TINFL_స్థితి_పూర్తి) && (!pState->m_dict_avail)) ? MZ_ప్రవాహం_చివర : MZ_OK;
  }

  కొరకు ( ; ; )
  {
    లోపల_బైట్లు = p_ప్రవాహం->avail_లోపల;
    బహిర్గతం_బైట్లు = TINFL_LZ_DICT_కొలత - pState->m_dict_ofs;

    స్థితి_2 = tinfl_decompress(&pState->m_decomp, p_ప్రవాహం->తదుపరి_లోపల, &లోపల_బైట్లు, pState->m_dict, pState->m_dict + pState->m_dict_ofs, &బహిర్గతం_బైట్లు, decomp_flags);
    pState->m_చివరి_స్థితి = స్థితి_2;

    p_ప్రవాహం->తదుపరి_లోపల += (mz_uint)లోపల_బైట్లు; p_ప్రవాహం->avail_లోపల -= (mz_uint)లోపల_బైట్లు;
    p_ప్రవాహం->మొత్తం_లోపల += (mz_uint)లోపల_బైట్లు; p_ప్రవాహం->adler = tinfl_get_adler32(&pState->m_decomp);

    pState->m_dict_avail = (mz_uint)బహిర్గతం_బైట్లు;

    n = MZ_MIN(pState->m_dict_avail, p_ప్రవాహం->avail_బహిర్గతం);
    జ్ఞాపకం_నకలు(p_ప్రవాహం->తదుపరి_బహిర్గతం, pState->m_dict + pState->m_dict_ofs, n);
    p_ప్రవాహం->తదుపరి_బహిర్గతం += n; p_ప్రవాహం->avail_బహిర్గతం -= n; p_ప్రవాహం->మొత్తం_బహిర్గతం += n;
    pState->m_dict_avail -= n; pState->m_dict_ofs = (pState->m_dict_ofs + n) & (TINFL_LZ_DICT_కొలత - 1);

    ఒకవేళ (స్థితి_2 < 0)
       తిరిగి MZ_దత్తాంశం_ERROR; // Stream is corrupted (there could be some uncompressed data left in the output dictionary - oh well).
    లేకపోతే ఒకవేళ ((స్థితి_2 == TINFL_స్థితి_NEEDS_మరిన్ని_ఆదానం) && (!orig_avail_లోపల))
      తిరిగి MZ_BUF_ERROR; // Signal caller that we can't make forward progress without supplying more input or by setting flush to MZ_FINISH.
    లేకపోతే ఒకవేళ (flush == MZ_ముగింపు)
    {
       // The output buffer MUST be large to hold the remaining uncompressed data when flush==MZ_FINISH.
       ఒకవేళ (స్థితి_2 == TINFL_స్థితి_పూర్తి)
          తిరిగి pState->m_dict_avail ? MZ_BUF_ERROR : MZ_ప్రవాహం_చివర;
       // status here must be TINFL_STATUS_HAS_MORE_OUTPUT, which means there's at least 1 more byte on the way. If there's no more room left in the output buffer then something is wrong.
       లేకపోతే ఒకవేళ (!p_ప్రవాహం->avail_బహిర్గతం)
          తిరిగి MZ_BUF_ERROR;
    }
    లేకపోతే ఒకవేళ ((స్థితి_2 == TINFL_స్థితి_పూర్తి) || (!p_ప్రవాహం->avail_లోపల) || (!p_ప్రవాహం->avail_బహిర్గతం) || (pState->m_dict_avail))
      ఆపు;
  }

  తిరిగి ((స్థితి_2 == TINFL_స్థితి_పూర్తి) && (!pState->m_dict_avail)) ? MZ_ప్రవాహం_చివర : MZ_OK;
}

పూర్ణాంకం mz_inflate_చివర(mz_streamp p_ప్రవాహం)
{
  ఒకవేళ (!p_ప్రవాహం)
    తిరిగి MZ_ప్రవాహం_ERROR;
  ఒకవేళ (p_ప్రవాహం->state)
  {
    p_ప్రవాహం->zfree(p_ప్రవాహం->opaque, p_ప్రవాహం->state);
    p_ప్రవాహం->state = ఖాళీ;
  }
  తిరిగి MZ_OK;
}

పూర్ణాంకం mz_uncompress(గుర్తులేని అక్షరం *pDest, mz_ulong *pDest_len, స్థిరరాశి గుర్తులేని అక్షరం *p_ఆధారం, mz_ulong ఆధారం_len)
{
  mz_ప్రవాహం ప్రవాహం;
  పూర్ణాంకం స్థితి_2;
  memset(&ప్రవాహం, 0, పరిమాణం(ప్రవాహం));

  // In case mz_ulong is 64-bits (argh I hate longs).
  ఒకవేళ ((ఆధారం_len | *pDest_len) > 0xFFFFFFFFU) తిరిగి MZ_PARAM_ERROR;

  ప్రవాహం.తదుపరి_లోపల = p_ఆధారం;
  ప్రవాహం.avail_లోపల = (mz_uint32)ఆధారం_len;
  ప్రవాహం.తదుపరి_బహిర్గతం = pDest;
  ప్రవాహం.avail_బహిర్గతం = (mz_uint32)*pDest_len;

  స్థితి_2 = mz_inflateInit(&ప్రవాహం);
  ఒకవేళ (స్థితి_2 != MZ_OK)
    తిరిగి స్థితి_2;

  స్థితి_2 = mz_inflate(&ప్రవాహం, MZ_ముగింపు);
  ఒకవేళ (స్థితి_2 != MZ_ప్రవాహం_చివర)
  {
    mz_inflate_చివర(&ప్రవాహం);
    తిరిగి ((స్థితి_2 == MZ_BUF_ERROR) && (!ప్రవాహం.avail_లోపల)) ? MZ_దత్తాంశం_ERROR : స్థితి_2;
  }
  *pDest_len = ప్రవాహం.మొత్తం_బహిర్గతం;

  తిరిగి mz_inflate_చివర(&ప్రవాహం);
}

#అయితే_ముగింపు /*#ifndef MINIZ_NO_INFLATE_APIS*/

స్థిరరాశి అక్షరం *mz_error(పూర్ణాంకం err)
{
  స్థిర నిర్మాణం { పూర్ణాంకం m_err; స్థిరరాశి అక్షరం *m_pDesc; } s_error_descs[] =
  {
    { MZ_OK, "" }, { MZ_ప్రవాహం_చివర, "stream end" }, { MZ_NEED_DICT, "need dictionary" }, { MZ_ERRNO, "file error" }, { MZ_ప్రవాహం_ERROR, "stream error" },
    { MZ_దత్తాంశం_ERROR, "data error" }, { MZ_MEM_ERROR, "out of memory" }, { MZ_BUF_ERROR, "buf error" }, { MZ_సంస్కరణ_ERROR, "version error" }, { MZ_PARAM_ERROR, "parameter error" }
  };
  mz_uint i; కొరకు (i = 0; i < పరిమాణం(s_error_descs) / పరిమాణం(s_error_descs[0]); ++i) ఒకవేళ (s_error_descs[i].m_err == err) తిరిగి s_error_descs[i].m_pDesc;
  తిరిగి ఖాళీ;
}

#అయితే_ముగింపు //MINIZ_NO_ZLIB_APIS

// ------------------- Low-level Decompression (completely independent from all compression API's)
#నిర్వచితం_కాకపోతే MINIZ_NO_INFLATE_APIS

#నిర్వచించు TINFL_MEMCPY(d, s, l) జ్ఞాపకం_నకలు(d, s, l)
#నిర్వచించు TINFL_MEMSET(p, c, l) memset(p, c, l)

#నిర్వచించు TINFL_CR_BEGIN ఎంపిక(r->m_state) { స్థితి 0:
#నిర్వచించు TINFL_CR_RETURN(state_సూచీ, ఫలితం) చేయి { స్థితి_2 = ఫలితం; r->m_state = state_సూచీ; వెళ్ళు common_exit; స్థితి state_సూచీ:; } MZ_MACRO_చివర
#నిర్వచించు TINFL_CR_RETURN_FOREVER(state_సూచీ, ఫలితం) చేయి { కొరకు ( ; ; ) { TINFL_CR_RETURN(state_సూచీ, ఫలితం); } } MZ_MACRO_చివర
#నిర్వచించు TINFL_CR_ముగింపు }

// TODO: If the caller has indicated that there's no more input, and we attempt to read beyond the input buf, then something is wrong with the input because the inflator never
// reads ahead more than it needs to. Currently TINFL_GET_BYTE() pads the end of the stream with 0's in this scenario.
#నిర్వచించు TINFL_GET_BYTE(state_సూచీ, c) చేయి { \
  ఒకవేళ (p_లోపల_buf_cur >= p_లోపల_buf_చివర) { \
    కొరకు ( ; ; ) { \
      ఒకవేళ (decomp_flags & TINFL_FLAG_HAS_మరిన్ని_ఆదానం) { \
        TINFL_CR_RETURN(state_సూచీ, TINFL_స్థితి_NEEDS_మరిన్ని_ఆదానం); \
        ఒకవేళ (p_లోపల_buf_cur < p_లోపల_buf_చివర) { \
          c = *p_లోపల_buf_cur++; \
          ఆపు; \
        } \
      } లేకపోతే { \
        c = 0; \
        ఆపు; \
      } \
    } \
  } లేకపోతే c = *p_లోపల_buf_cur++; } MZ_MACRO_చివర

#నిర్వచించు TINFL_NEED_బిట్లు(state_సూచీ, n) చేయి { mz_uint c; TINFL_GET_BYTE(state_సూచీ, c); బిట్టు_buf |= (((tinfl_బిట్టు_buf_t)c) << అంకె_బిట్లు); అంకె_బిట్లు += 8; } అయితే (అంకె_బిట్లు < (mz_uint)(n))
#నిర్వచించు TINFL_SKIP_బిట్లు(state_సూచీ, n) చేయి { ఒకవేళ (అంకె_బిట్లు < (mz_uint)(n)) { TINFL_NEED_బిట్లు(state_సూచీ, n); } బిట్టు_buf >>= (n); అంకె_బిట్లు -= (n); } MZ_MACRO_చివర
#నిర్వచించు TINFL_GET_బిట్లు(state_సూచీ, b, n) చేయి { ఒకవేళ (అంకె_బిట్లు < (mz_uint)(n)) { TINFL_NEED_బిట్లు(state_సూచీ, n); } b = బిట్టు_buf & ((1 << (n)) - 1); బిట్టు_buf >>= (n); అంకె_బిట్లు -= (n); } MZ_MACRO_చివర

// TINFL_HUFF_BITBUF_FILL() is only used rarely, when the number of bytes remaining in the input buffer falls below 2.
// It reads just enough bytes from the input stream that are needed to decode the next Huffman code (and absolutely no more). It works by trying to fully decode a
// Huffman code by using whatever bits are currently present in the bit buffer. If this fails, it reads another byte, and tries again until it succeeds or until the
// bit buffer contains >=15 bits (deflate's max. Huffman code size).
#నిర్వచించు TINFL_HUFF_BITBUF_FILL(state_సూచీ, pHuff) \
  చేయి { \
    తాత్కాలిక = (pHuff)->m_look_పైకి[బిట్టు_buf & (TINFL_FAST_LOOKUP_కొలత - 1)]; \
    ఒకవేళ (తాత్కాలిక >= 0) { \
      సంకేతం_len = తాత్కాలిక >> 9; \
      ఒకవేళ ((సంకేతం_len) && (అంకె_బిట్లు >= సంకేతం_len)) \
          ఆపు; \
    } లేకపోతే ఒకవేళ (అంకె_బిట్లు > TINFL_FAST_LOOKUP_బిట్లు) { \
       సంకేతం_len = TINFL_FAST_LOOKUP_బిట్లు; \
       చేయి { \
          తాత్కాలిక = (pHuff)->m_వృక్షం[~తాత్కాలిక + ((బిట్టు_buf >> సంకేతం_len++) & 1)]; \
       } అయితే ((తాత్కాలిక < 0) && (అంకె_బిట్లు >= (సంకేతం_len + 1))); \
       ఒకవేళ (తాత్కాలిక >= 0) ఆపు; \
    } \
    TINFL_GET_BYTE(state_సూచీ, c); \
    బిట్టు_buf |= (((tinfl_బిట్టు_buf_t)c) << అంకె_బిట్లు); \
    అంకె_బిట్లు += 8; \
  } అయితే (అంకె_బిట్లు < 15);

// TINFL_HUFF_DECODE() decodes the next Huffman coded symbol. It's more complex than you would initially expect because the zlib API expects the decompressor to never read
// beyond the final byte of the deflate stream. (In other words, when this macro wants to read another byte from the input, it REALLY needs another byte in order to fully
// decode the next Huffman code.) Handling this properly is particularly important on raw deflate (non-zlib) streams, which aren't followed by a byte aligned adler-32.
// The slow path is only executed at the very end of the input buffer.
#నిర్వచించు TINFL_HUFF_DECODE(state_సూచీ, sym, pHuff) చేయి { \
  పూర్ణాంకం తాత్కాలిక; mz_uint సంకేతం_len, c; \
  ఒకవేళ (అంకె_బిట్లు < 15) { \
    ఒకవేళ ((p_లోపల_buf_చివర - p_లోపల_buf_cur) < 2) { \
       TINFL_HUFF_BITBUF_FILL(state_సూచీ, pHuff); \
    } లేకపోతే { \
       బిట్టు_buf |= (((tinfl_బిట్టు_buf_t)p_లోపల_buf_cur[0]) << అంకె_బిట్లు) | (((tinfl_బిట్టు_buf_t)p_లోపల_buf_cur[1]) << (అంకె_బిట్లు + 8)); p_లోపల_buf_cur += 2; అంకె_బిట్లు += 16; \
    } \
  } \
  ఒకవేళ ((తాత్కాలిక = (pHuff)->m_look_పైకి[బిట్టు_buf & (TINFL_FAST_LOOKUP_కొలత - 1)]) >= 0) \
    సంకేతం_len = తాత్కాలిక >> 9, తాత్కాలిక &= 511; \
  లేకపోతే { \
    సంకేతం_len = TINFL_FAST_LOOKUP_బిట్లు; చేయి { తాత్కాలిక = (pHuff)->m_వృక్షం[~తాత్కాలిక + ((బిట్టు_buf >> సంకేతం_len++) & 1)]; } అయితే (తాత్కాలిక < 0); \
  } sym = తాత్కాలిక; బిట్టు_buf >>= సంకేతం_len; అంకె_బిట్లు -= సంకేతం_len; } MZ_MACRO_చివర

tinfl_స్థితి tinfl_decompress(tinfl_decompressor *r, స్థిరరాశి mz_uint8 *p_లోపల_buf_తదుపరి, size_t *p_లోపల_buf_కొలత, mz_uint8 *p_బహిర్గతం_buf_ప్రారంభం, mz_uint8 *p_బహిర్గతం_buf_తదుపరి, size_t *p_బహిర్గతం_buf_కొలత, స్థిరరాశి mz_uint32 decomp_flags)
{
  స్థిర స్థిరరాశి పూర్ణాంకం s_నిడివి_పునాది[31] = { 3,4,5,6,7,8,9,10,11,13, 15,17,19,23,27,31,35,43,51,59, 67,83,99,115,131,163,195,227,258,0,0 };
  స్థిర స్థిరరాశి పూర్ణాంకం s_నిడివి_extra[31]= { 0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,0,0,0 };
  స్థిర స్థిరరాశి పూర్ణాంకం s_dist_పునాది[32] = { 1,2,3,4,5,7,9,13,17,25,33,49,65,97,129,193, 257,385,513,769,1025,1537,2049,3073,4097,6145,8193,12289,16385,24577,0,0};
  స్థిర స్థిరరాశి పూర్ణాంకం s_dist_extra[32] = { 0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13};
  స్థిర స్థిరరాశి mz_uint8 s_నిడివి_dezigzag[19] = { 16,17,18,0,8,7,9,6,10,5,11,4,12,3,13,2,14,1,15 };
  స్థిర స్థిరరాశి పూర్ణాంకం s_min_పట్టిక_sizes[3] = { 257, 1, 4 };

  tinfl_స్థితి స్థితి_2 = TINFL_స్థితి_FAILED; mz_uint32 అంకె_బిట్లు, dist, counter, అంకె_extra; tinfl_బిట్టు_buf_t బిట్టు_buf;
  స్థిరరాశి mz_uint8 *p_లోపల_buf_cur = p_లోపల_buf_తదుపరి, *స్థిరరాశి p_లోపల_buf_చివర = p_లోపల_buf_తదుపరి + *p_లోపల_buf_కొలత;
  mz_uint8 *p_బహిర్గతం_buf_cur = p_బహిర్గతం_buf_తదుపరి, *స్థిరరాశి p_బహిర్గతం_buf_చివర = p_బహిర్గతం_buf_తదుపరి + *p_బహిర్గతం_buf_కొలత;
  size_t బహిర్గతం_buf_కొలత_ముసుగు = (decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF) ? (size_t)-1 : ((p_బహిర్గతం_buf_తదుపరి - p_బహిర్గతం_buf_ప్రారంభం) + *p_బహిర్గతం_buf_కొలత) - 1, dist_from_బహిర్గతం_buf_ప్రారంభం;

  // Ensure the output buffer's size is a power of 2, unless the output buffer is large enough to hold the entire output file (in which case it doesn't matter).
  ఒకవేళ (((బహిర్గతం_buf_కొలత_ముసుగు + 1) & బహిర్గతం_buf_కొలత_ముసుగు) || (p_బహిర్గతం_buf_తదుపరి < p_బహిర్గతం_buf_ప్రారంభం)) { *p_లోపల_buf_కొలత = *p_బహిర్గతం_buf_కొలత = 0; తిరిగి TINFL_స్థితి_BAD_PARAM; }

  అంకె_బిట్లు = r->m_అంకె_బిట్లు; బిట్టు_buf = r->m_బిట్టు_buf; dist = r->m_dist; counter = r->m_counter; అంకె_extra = r->m_అంకె_extra; dist_from_బహిర్గతం_buf_ప్రారంభం = r->m_dist_from_బహిర్గతం_buf_ప్రారంభం;
  TINFL_CR_BEGIN

  బిట్టు_buf = అంకె_బిట్లు = dist = counter = అంకె_extra = r->m_zhdr0 = r->m_zhdr1 = 0; r->m_z_adler32 = r->m_check_adler32 = 1;
  ఒకవేళ (decomp_flags & TINFL_FLAG_PARSE_ZLIB_శీర్షిక)
  {
    TINFL_GET_BYTE(1, r->m_zhdr0); TINFL_GET_BYTE(2, r->m_zhdr1);
    counter = (((r->m_zhdr0 * 256 + r->m_zhdr1) % 31 != 0) || (r->m_zhdr1 & 32) || ((r->m_zhdr0 & 15) != 8));
    ఒకవేళ (!(decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF)) counter |= (((1U << (8U + (r->m_zhdr0 >> 4))) > 32768U) || ((బహిర్గతం_buf_కొలత_ముసుగు + 1) < (size_t)(1U << (8U + (r->m_zhdr0 >> 4)))));
    ఒకవేళ (counter) { TINFL_CR_RETURN_FOREVER(36, TINFL_స్థితి_FAILED); }
  }

  చేయి
  {
    TINFL_GET_బిట్లు(3, r->m_final, 3); r->m_type = r->m_final >> 1;
    ఒకవేళ (r->m_type == 0)
    {
      TINFL_SKIP_బిట్లు(5, అంకె_బిట్లు & 7);
      కొరకు (counter = 0; counter < 4; ++counter) { ఒకవేళ (అంకె_బిట్లు) TINFL_GET_బిట్లు(6, r->m_raw_శీర్షిక[counter], 8); లేకపోతే TINFL_GET_BYTE(7, r->m_raw_శీర్షిక[counter]); }
      ఒకవేళ ((counter = (r->m_raw_శీర్షిక[0] | (r->m_raw_శీర్షిక[1] << 8))) != (mz_uint)(0xFFFF ^ (r->m_raw_శీర్షిక[2] | (r->m_raw_శీర్షిక[3] << 8)))) { TINFL_CR_RETURN_FOREVER(39, TINFL_స్థితి_FAILED); }
      అయితే ((counter) && (అంకె_బిట్లు))
      {
        TINFL_GET_బిట్లు(51, dist, 8);
        అయితే (p_బహిర్గతం_buf_cur >= p_బహిర్గతం_buf_చివర) { TINFL_CR_RETURN(52, TINFL_స్థితి_HAS_మరిన్ని_OUTPUT); }
        *p_బహిర్గతం_buf_cur++ = (mz_uint8)dist;
        counter--;
      }
      అయితే (counter)
      {
        size_t n; అయితే (p_బహిర్గతం_buf_cur >= p_బహిర్గతం_buf_చివర) { TINFL_CR_RETURN(9, TINFL_స్థితి_HAS_మరిన్ని_OUTPUT); }
        అయితే (p_లోపల_buf_cur >= p_లోపల_buf_చివర)
        {
          ఒకవేళ (decomp_flags & TINFL_FLAG_HAS_మరిన్ని_ఆదానం)
          {
            TINFL_CR_RETURN(38, TINFL_స్థితి_NEEDS_మరిన్ని_ఆదానం);
          }
          లేకపోతే
          {
            TINFL_CR_RETURN_FOREVER(40, TINFL_స్థితి_FAILED);
          }
        }
        n = MZ_MIN(MZ_MIN((size_t)(p_బహిర్గతం_buf_చివర - p_బహిర్గతం_buf_cur), (size_t)(p_లోపల_buf_చివర - p_లోపల_buf_cur)), counter);
        TINFL_MEMCPY(p_బహిర్గతం_buf_cur, p_లోపల_buf_cur, n); p_లోపల_buf_cur += n; p_బహిర్గతం_buf_cur += n; counter -= (mz_uint)n;
      }
    }
    లేకపోతే ఒకవేళ (r->m_type == 3)
    {
      TINFL_CR_RETURN_FOREVER(10, TINFL_స్థితి_FAILED);
    }
    లేకపోతే
    {
      ఒకవేళ (r->m_type == 1)
      {
        mz_uint8 *p = r->m_tables[0].m_సంకేతం_కొలత; mz_uint i;
        r->m_పట్టిక_sizes[0] = 288; r->m_పట్టిక_sizes[1] = 32; TINFL_MEMSET(r->m_tables[1].m_సంకేతం_కొలత, 5, 32);
        కొరకు ( i = 0; i <= 143; ++i) *p++ = 8;
        కొరకు ( ; i <= 255; ++i) *p++ = 9;
        కొరకు ( ; i <= 279; ++i) *p++ = 7;
        కొరకు ( ; i <= 287; ++i) *p++ = 8;
      }
      లేకపోతే
      {
        కొరకు (counter = 0; counter < 3; counter++) { TINFL_GET_బిట్లు(11, r->m_పట్టిక_sizes[counter], "\05\05\04"[counter]); r->m_పట్టిక_sizes[counter] += s_min_పట్టిక_sizes[counter]; }
        MZ_CLEAR_ARR(r->m_tables[2].m_సంకేతం_కొలత); కొరకు (counter = 0; counter < r->m_పట్టిక_sizes[2]; counter++) { mz_uint s; TINFL_GET_బిట్లు(14, s, 3); r->m_tables[2].m_సంకేతం_కొలత[s_నిడివి_dezigzag[counter]] = (mz_uint8)s; }
        r->m_పట్టిక_sizes[2] = 19;
      }
      కొరకు ( ; (పూర్ణాంకం)r->m_type >= 0; r->m_type--)
      {
        పూర్ణాంకం వృక్షం_తదుపరి, వృక్షం_cur; tinfl_huff_పట్టిక *p_పట్టిక;
        mz_uint i, j, వాడిన_syms, మొత్తం, sym_సూచీ, తదుపరి_సంకేతం[17], మొత్తం_syms[16]; p_పట్టిక = &r->m_tables[r->m_type]; MZ_CLEAR_ARR(మొత్తం_syms); MZ_CLEAR_ARR(p_పట్టిక->m_look_పైకి); MZ_CLEAR_ARR(p_పట్టిక->m_వృక్షం);
        కొరకు (i = 0; i < r->m_పట్టిక_sizes[r->m_type]; ++i) మొత్తం_syms[p_పట్టిక->m_సంకేతం_కొలత[i]]++;
        వాడిన_syms = 0, మొత్తం = 0; తదుపరి_సంకేతం[0] = తదుపరి_సంకేతం[1] = 0;
        కొరకు (i = 1; i <= 15; ++i) { వాడిన_syms += మొత్తం_syms[i]; తదుపరి_సంకేతం[i + 1] = (మొత్తం = ((మొత్తం + మొత్తం_syms[i]) << 1)); }
        ఒకవేళ ((65536 != మొత్తం) && (వాడిన_syms > 1))
        {
          TINFL_CR_RETURN_FOREVER(35, TINFL_స్థితి_FAILED);
        }
        కొరకు (వృక్షం_తదుపరి = -1, sym_సూచీ = 0; sym_సూచీ < r->m_పట్టిక_sizes[r->m_type]; ++sym_సూచీ)
        {
          mz_uint rev_సంకేతం = 0, l, cur_సంకేతం, సంకేతం_కొలత_2 = p_పట్టిక->m_సంకేతం_కొలత[sym_సూచీ]; ఒకవేళ (!సంకేతం_కొలత_2) కొనసాగు;
          cur_సంకేతం = తదుపరి_సంకేతం[సంకేతం_కొలత_2]++; కొరకు (l = సంకేతం_కొలత_2; l > 0; l--, cur_సంకేతం >>= 1) rev_సంకేతం = (rev_సంకేతం << 1) | (cur_సంకేతం & 1);
          ఒకవేళ (సంకేతం_కొలత_2 <= TINFL_FAST_LOOKUP_బిట్లు) { mz_int16 k = (mz_int16)((సంకేతం_కొలత_2 << 9) | sym_సూచీ); అయితే (rev_సంకేతం < TINFL_FAST_LOOKUP_కొలత) { p_పట్టిక->m_look_పైకి[rev_సంకేతం] = k; rev_సంకేతం += (1 << సంకేతం_కొలత_2); } కొనసాగు; }
          ఒకవేళ (0 == (వృక్షం_cur = p_పట్టిక->m_look_పైకి[rev_సంకేతం & (TINFL_FAST_LOOKUP_కొలత - 1)])) { p_పట్టిక->m_look_పైకి[rev_సంకేతం & (TINFL_FAST_LOOKUP_కొలత - 1)] = (mz_int16)వృక్షం_తదుపరి; వృక్షం_cur = వృక్షం_తదుపరి; వృక్షం_తదుపరి -= 2; }
          rev_సంకేతం >>= (TINFL_FAST_LOOKUP_బిట్లు - 1);
          కొరకు (j = సంకేతం_కొలత_2; j > (TINFL_FAST_LOOKUP_బిట్లు + 1); j--)
          {
            వృక్షం_cur -= ((rev_సంకేతం >>= 1) & 1);
            ఒకవేళ (!p_పట్టిక->m_వృక్షం[-వృక్షం_cur - 1]) { p_పట్టిక->m_వృక్షం[-వృక్షం_cur - 1] = (mz_int16)వృక్షం_తదుపరి; వృక్షం_cur = వృక్షం_తదుపరి; వృక్షం_తదుపరి -= 2; } లేకపోతే వృక్షం_cur = p_పట్టిక->m_వృక్షం[-వృక్షం_cur - 1];
          }
          వృక్షం_cur -= ((rev_సంకేతం >>= 1) & 1); p_పట్టిక->m_వృక్షం[-వృక్షం_cur - 1] = (mz_int16)sym_సూచీ;
        }
        ఒకవేళ (r->m_type == 2)
        {
          కొరకు (counter = 0; counter < (r->m_పట్టిక_sizes[0] + r->m_పట్టిక_sizes[1]); )
          {
            mz_uint s; TINFL_HUFF_DECODE(16, dist, &r->m_tables[2]); ఒకవేళ (dist < 16) { r->m_len_codes[counter++] = (mz_uint8)dist; కొనసాగు; }
            ఒకవేళ ((dist == 16) && (!counter))
            {
              TINFL_CR_RETURN_FOREVER(17, TINFL_స్థితి_FAILED);
            }
            అంకె_extra = "\02\03\07"[dist - 16]; TINFL_GET_బిట్లు(18, s, అంకె_extra); s += "\03\03\013"[dist - 16];
            TINFL_MEMSET(r->m_len_codes + counter, (dist == 16) ? r->m_len_codes[counter - 1] : 0, s); counter += s;
          }
          ఒకవేళ ((r->m_పట్టిక_sizes[0] + r->m_పట్టిక_sizes[1]) != counter)
          {
            TINFL_CR_RETURN_FOREVER(21, TINFL_స్థితి_FAILED);
          }
          TINFL_MEMCPY(r->m_tables[0].m_సంకేతం_కొలత, r->m_len_codes, r->m_పట్టిక_sizes[0]); TINFL_MEMCPY(r->m_tables[1].m_సంకేతం_కొలత, r->m_len_codes + r->m_పట్టిక_sizes[0], r->m_పట్టిక_sizes[1]);
        }
      }
      కొరకు ( ; ; )
      {
        mz_uint8 *pSrc;
        కొరకు ( ; ; )
        {
          ఒకవేళ (((p_లోపల_buf_చివర - p_లోపల_buf_cur) < 4) || ((p_బహిర్గతం_buf_చివర - p_బహిర్గతం_buf_cur) < 2))
          {
            TINFL_HUFF_DECODE(23, counter, &r->m_tables[0]);
            ఒకవేళ (counter >= 256)
              ఆపు;
            అయితే (p_బహిర్గతం_buf_cur >= p_బహిర్గతం_buf_చివర) { TINFL_CR_RETURN(24, TINFL_స్థితి_HAS_మరిన్ని_OUTPUT); }
            *p_బహిర్గతం_buf_cur++ = (mz_uint8)counter;
          }
          లేకపోతే
          {
            పూర్ణాంకం sym2; mz_uint సంకేతం_len;
#ఒకవేళ TINFL_USE_64_బిట్టు_BITBUF
            ఒకవేళ (అంకె_బిట్లు < 30) { బిట్టు_buf |= (((tinfl_బిట్టు_buf_t)MZ_READ_LE32(p_లోపల_buf_cur)) << అంకె_బిట్లు); p_లోపల_buf_cur += 4; అంకె_బిట్లు += 32; }
#లేకపోతే
            ఒకవేళ (అంకె_బిట్లు < 15) { బిట్టు_buf |= (((tinfl_బిట్టు_buf_t)MZ_READ_LE16(p_లోపల_buf_cur)) << అంకె_బిట్లు); p_లోపల_buf_cur += 2; అంకె_బిట్లు += 16; }
#అయితే_ముగింపు
            ఒకవేళ ((sym2 = r->m_tables[0].m_look_పైకి[బిట్టు_buf & (TINFL_FAST_LOOKUP_కొలత - 1)]) >= 0)
              సంకేతం_len = sym2 >> 9;
            లేకపోతే
            {
              సంకేతం_len = TINFL_FAST_LOOKUP_బిట్లు; చేయి { sym2 = r->m_tables[0].m_వృక్షం[~sym2 + ((బిట్టు_buf >> సంకేతం_len++) & 1)]; } అయితే (sym2 < 0);
            }
            counter = sym2; బిట్టు_buf >>= సంకేతం_len; అంకె_బిట్లు -= సంకేతం_len;
            ఒకవేళ (counter & 256)
              ఆపు;

#ఒకవేళ !TINFL_USE_64_బిట్టు_BITBUF
            ఒకవేళ (అంకె_బిట్లు < 15) { బిట్టు_buf |= (((tinfl_బిట్టు_buf_t)MZ_READ_LE16(p_లోపల_buf_cur)) << అంకె_బిట్లు); p_లోపల_buf_cur += 2; అంకె_బిట్లు += 16; }
#అయితే_ముగింపు
            ఒకవేళ ((sym2 = r->m_tables[0].m_look_పైకి[బిట్టు_buf & (TINFL_FAST_LOOKUP_కొలత - 1)]) >= 0)
              సంకేతం_len = sym2 >> 9;
            లేకపోతే
            {
              సంకేతం_len = TINFL_FAST_LOOKUP_బిట్లు; చేయి { sym2 = r->m_tables[0].m_వృక్షం[~sym2 + ((బిట్టు_buf >> సంకేతం_len++) & 1)]; } అయితే (sym2 < 0);
            }
            బిట్టు_buf >>= సంకేతం_len; అంకె_బిట్లు -= సంకేతం_len;

            p_బహిర్గతం_buf_cur[0] = (mz_uint8)counter;
            ఒకవేళ (sym2 & 256)
            {
              p_బహిర్గతం_buf_cur++;
              counter = sym2;
              ఆపు;
            }
            p_బహిర్గతం_buf_cur[1] = (mz_uint8)sym2;
            p_బహిర్గతం_buf_cur += 2;
          }
        }
        ఒకవేళ ((counter &= 511) == 256) ఆపు;

        అంకె_extra = s_నిడివి_extra[counter - 257]; counter = s_నిడివి_పునాది[counter - 257];
        ఒకవేళ (అంకె_extra) { mz_uint extra_బిట్లు; TINFL_GET_బిట్లు(25, extra_బిట్లు, అంకె_extra); counter += extra_బిట్లు; }

        TINFL_HUFF_DECODE(26, dist, &r->m_tables[1]);
        అంకె_extra = s_dist_extra[dist]; dist = s_dist_పునాది[dist];
        ఒకవేళ (అంకె_extra) { mz_uint extra_బిట్లు; TINFL_GET_బిట్లు(27, extra_బిట్లు, అంకె_extra); dist += extra_బిట్లు; }

        dist_from_బహిర్గతం_buf_ప్రారంభం = p_బహిర్గతం_buf_cur - p_బహిర్గతం_buf_ప్రారంభం;
        ఒకవేళ ((dist > dist_from_బహిర్గతం_buf_ప్రారంభం) && (decomp_flags & TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF))
        {
          TINFL_CR_RETURN_FOREVER(37, TINFL_స్థితి_FAILED);
        }

        pSrc = p_బహిర్గతం_buf_ప్రారంభం + ((dist_from_బహిర్గతం_buf_ప్రారంభం - dist) & బహిర్గతం_buf_కొలత_ముసుగు);

        ఒకవేళ ((MZ_MAX(p_బహిర్గతం_buf_cur, pSrc) + counter) > p_బహిర్గతం_buf_చివర)
        {
          అయితే (counter--)
          {
            అయితే (p_బహిర్గతం_buf_cur >= p_బహిర్గతం_buf_చివర) { TINFL_CR_RETURN(53, TINFL_స్థితి_HAS_మరిన్ని_OUTPUT); }
            *p_బహిర్గతం_buf_cur++ = p_బహిర్గతం_buf_ప్రారంభం[(dist_from_బహిర్గతం_buf_ప్రారంభం++ - dist) & బహిర్గతం_buf_కొలత_ముసుగు];
          }
          కొనసాగు;
        }
#ఒకవేళ MINIZ_USE_UNALIGNED_LOADS_AND_STORES
        లేకపోతే ఒకవేళ ((counter >= 9) && (counter <= dist))
        {
          స్థిరరాశి mz_uint8 *p_Src_చివర = pSrc + (counter & ~7);
          చేయి
          {
            ((mz_uint32 *)p_బహిర్గతం_buf_cur)[0] = ((స్థిరరాశి mz_uint32 *)pSrc)[0];
            ((mz_uint32 *)p_బహిర్గతం_buf_cur)[1] = ((స్థిరరాశి mz_uint32 *)pSrc)[1];
            p_బహిర్గతం_buf_cur += 8;
          } అయితే ((pSrc += 8) < p_Src_చివర);
          ఒకవేళ ((counter &= 7) < 3)
          {
            ఒకవేళ (counter)
            {
              p_బహిర్గతం_buf_cur[0] = pSrc[0];
              ఒకవేళ (counter > 1)
                p_బహిర్గతం_buf_cur[1] = pSrc[1];
              p_బహిర్గతం_buf_cur += counter;
            }
            కొనసాగు;
          }
        }
#అయితే_ముగింపు
        చేయి
        {
          p_బహిర్గతం_buf_cur[0] = pSrc[0];
          p_బహిర్గతం_buf_cur[1] = pSrc[1];
          p_బహిర్గతం_buf_cur[2] = pSrc[2];
          p_బహిర్గతం_buf_cur += 3; pSrc += 3;
        } అయితే ((పూర్ణాంకం)(counter -= 3) > 2);
        ఒకవేళ ((పూర్ణాంకం)counter > 0)
        {
          p_బహిర్గతం_buf_cur[0] = pSrc[0];
          ఒకవేళ ((పూర్ణాంకం)counter > 1)
            p_బహిర్గతం_buf_cur[1] = pSrc[1];
          p_బహిర్గతం_buf_cur += counter;
        }
      }
    }
  } అయితే (!(r->m_final & 1));
  ఒకవేళ (decomp_flags & TINFL_FLAG_PARSE_ZLIB_శీర్షిక)
  {
    TINFL_SKIP_బిట్లు(32, అంకె_బిట్లు & 7); కొరకు (counter = 0; counter < 4; ++counter) { mz_uint s; ఒకవేళ (అంకె_బిట్లు) TINFL_GET_బిట్లు(41, s, 8); లేకపోతే TINFL_GET_BYTE(42, s); r->m_z_adler32 = (r->m_z_adler32 << 8) | s; }
  }
  TINFL_CR_RETURN_FOREVER(34, TINFL_స్థితి_పూర్తి);
  TINFL_CR_ముగింపు

common_exit:
  r->m_అంకె_బిట్లు = అంకె_బిట్లు; r->m_బిట్టు_buf = బిట్టు_buf; r->m_dist = dist; r->m_counter = counter; r->m_అంకె_extra = అంకె_extra; r->m_dist_from_బహిర్గతం_buf_ప్రారంభం = dist_from_బహిర్గతం_buf_ప్రారంభం;
  *p_లోపల_buf_కొలత = p_లోపల_buf_cur - p_లోపల_buf_తదుపరి; *p_బహిర్గతం_buf_కొలత = p_బహిర్గతం_buf_cur - p_బహిర్గతం_buf_తదుపరి;
  ఒకవేళ ((decomp_flags & (TINFL_FLAG_PARSE_ZLIB_శీర్షిక | TINFL_FLAG_COMPUTE_ADLER32)) && (స్థితి_2 >= 0))
  {
    స్థిరరాశి mz_uint8 *ptr = p_బహిర్గతం_buf_తదుపరి; size_t buf_len = *p_బహిర్గతం_buf_కొలత;
    mz_uint32 i, s1 = r->m_check_adler32 & 0xffff, s2 = r->m_check_adler32 >> 16; size_t ఖండం_len = buf_len % 5552;
    అయితే (buf_len)
    {
      కొరకు (i = 0; i + 7 < ఖండం_len; i += 8, ptr += 8)
      {
        s1 += ptr[0], s2 += s1; s1 += ptr[1], s2 += s1; s1 += ptr[2], s2 += s1; s1 += ptr[3], s2 += s1;
        s1 += ptr[4], s2 += s1; s1 += ptr[5], s2 += s1; s1 += ptr[6], s2 += s1; s1 += ptr[7], s2 += s1;
      }
      కొరకు ( ; i < ఖండం_len; ++i) s1 += *ptr++, s2 += s1;
      s1 %= 65521U, s2 %= 65521U; buf_len -= ఖండం_len; ఖండం_len = 5552;
    }
    r->m_check_adler32 = (s2 << 16) + s1; ఒకవేళ ((స్థితి_2 == TINFL_స్థితి_పూర్తి) && (decomp_flags & TINFL_FLAG_PARSE_ZLIB_శీర్షిక) && (r->m_check_adler32 != r->m_z_adler32)) స్థితి_2 = TINFL_స్థితి_ADLER32_MISMATCH;
  }
  తిరిగి స్థితి_2;
}

// Higher level helper functions.
శూన్య *tinfl_decompress_mem_గమ్యం_కుప్ప(స్థిరరాశి శూన్య *pSrc_buf, size_t src_buf_len, size_t *p_బహిర్గతం_len, పూర్ణాంకం flags)
{
  tinfl_decompressor decomp; శూన్య *pBuf = ఖాళీ, *pNew_buf; size_t src_buf_ofs = 0, బహిర్గతం_buf_సామర్థ్యం = 0;
  *p_బహిర్గతం_len = 0;
  tinfl_init(&decomp);
  కొరకు ( ; ; )
  {
    size_t src_buf_కొలత = src_buf_len - src_buf_ofs, dst_buf_కొలత = బహిర్గతం_buf_సామర్థ్యం - *p_బహిర్గతం_len, new_బహిర్గతం_buf_సామర్థ్యం;
    tinfl_స్థితి స్థితి_2 = tinfl_decompress(&decomp, (స్థిరరాశి mz_uint8*)pSrc_buf + src_buf_ofs, &src_buf_కొలత, (mz_uint8*)pBuf, pBuf ? (mz_uint8*)pBuf + *p_బహిర్గతం_len : ఖాళీ, &dst_buf_కొలత,
      (flags & ~TINFL_FLAG_HAS_మరిన్ని_ఆదానం) | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF);
    ఒకవేళ ((స్థితి_2 < 0) || (స్థితి_2 == TINFL_స్థితి_NEEDS_మరిన్ని_ఆదానం))
    {
      MZ_FREE(pBuf); *p_బహిర్గతం_len = 0; తిరిగి ఖాళీ;
    }
    src_buf_ofs += src_buf_కొలత;
    *p_బహిర్గతం_len += dst_buf_కొలత;
    ఒకవేళ (స్థితి_2 == TINFL_స్థితి_పూర్తి) ఆపు;
    new_బహిర్గతం_buf_సామర్థ్యం = బహిర్గతం_buf_సామర్థ్యం * 2; ఒకవేళ (new_బహిర్గతం_buf_సామర్థ్యం < 128) new_బహిర్గతం_buf_సామర్థ్యం = 128;
    pNew_buf = MZ_REALLOC(pBuf, new_బహిర్గతం_buf_సామర్థ్యం);
    ఒకవేళ (!pNew_buf)
    {
      MZ_FREE(pBuf); *p_బహిర్గతం_len = 0; తిరిగి ఖాళీ;
    }
    pBuf = pNew_buf; బహిర్గతం_buf_సామర్థ్యం = new_బహిర్గతం_buf_సామర్థ్యం;
  }
  తిరిగి pBuf;
}

size_t tinfl_decompress_mem_గమ్యం_mem(శూన్య *p_బహిర్గతం_buf, size_t బహిర్గతం_buf_len, స్థిరరాశి శూన్య *pSrc_buf, size_t src_buf_len, పూర్ణాంకం flags)
{
  tinfl_decompressor decomp; tinfl_స్థితి స్థితి_2; tinfl_init(&decomp);
  స్థితి_2 = tinfl_decompress(&decomp, (స్థిరరాశి mz_uint8*)pSrc_buf, &src_buf_len, (mz_uint8*)p_బహిర్గతం_buf, (mz_uint8*)p_బహిర్గతం_buf, &బహిర్గతం_buf_len, (flags & ~TINFL_FLAG_HAS_మరిన్ని_ఆదానం) | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF);
  తిరిగి (స్థితి_2 != TINFL_స్థితి_పూర్తి) ? TINFL_DECOMPRESS_MEM_గమ్యం_MEM_FAILED : బహిర్గతం_buf_len;
}

పూర్ణాంకం tinfl_decompress_mem_గమ్యం_callback(స్థిరరాశి శూన్య *p_లోపల_buf, size_t *p_లోపల_buf_కొలత, tinfl_put_buf_func_ptr pPut_buf_func, శూన్య *pPut_buf_user, పూర్ణాంకం flags)
{
  పూర్ణాంకం ఫలితం = 0;
  tinfl_decompressor decomp;
  mz_uint8 *pDict = (mz_uint8*)MZ_MALLOC(TINFL_LZ_DICT_కొలత); size_t లోపల_buf_ofs = 0, dict_ofs = 0;
  ఒకవేళ (!pDict)
    తిరిగి TINFL_స్థితి_FAILED;
  memset(pDict,0,TINFL_LZ_DICT_కొలత);
  tinfl_init(&decomp);
  కొరకు ( ; ; )
  {
    size_t లోపల_buf_కొలత = *p_లోపల_buf_కొలత - లోపల_buf_ofs, dst_buf_కొలత = TINFL_LZ_DICT_కొలత - dict_ofs;
    tinfl_స్థితి స్థితి_2 = tinfl_decompress(&decomp, (స్థిరరాశి mz_uint8*)p_లోపల_buf + లోపల_buf_ofs, &లోపల_buf_కొలత, pDict, pDict + dict_ofs, &dst_buf_కొలత,
      (flags & ~(TINFL_FLAG_HAS_మరిన్ని_ఆదానం | TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF)));
    లోపల_buf_ofs += లోపల_buf_కొలత;
    ఒకవేళ ((dst_buf_కొలత) && (!(*pPut_buf_func)(pDict + dict_ofs, (పూర్ణాంకం)dst_buf_కొలత, pPut_buf_user)))
      ఆపు;
    ఒకవేళ (స్థితి_2 != TINFL_స్థితి_HAS_మరిన్ని_OUTPUT)
    {
      ఫలితం = (స్థితి_2 == TINFL_స్థితి_పూర్తి);
      ఆపు;
    }
    dict_ofs = (dict_ofs + dst_buf_కొలత) & (TINFL_LZ_DICT_కొలత - 1);
  }
  MZ_FREE(pDict);
  *p_లోపల_buf_కొలత = లోపల_buf_ofs;
  తిరిగి ఫలితం;
}
#అయితే_ముగింపు /*#ifndef MINIZ_NO_INFLATE_APIS*/

// ------------------- Low-level Compression (independent from all decompression API's)
#నిర్వచితం_కాకపోతే MINIZ_NO_DEFLATE_APIS

// Purposely making these tables static for faster init and thread safety.
స్థిర స్థిరరాశి mz_uint16 s_tdefl_len_sym[256] = {
  257,258,259,260,261,262,263,264,265,265,266,266,267,267,268,268,269,269,269,269,270,270,270,270,271,271,271,271,272,272,272,272,
  273,273,273,273,273,273,273,273,274,274,274,274,274,274,274,274,275,275,275,275,275,275,275,275,276,276,276,276,276,276,276,276,
  277,277,277,277,277,277,277,277,277,277,277,277,277,277,277,277,278,278,278,278,278,278,278,278,278,278,278,278,278,278,278,278,
  279,279,279,279,279,279,279,279,279,279,279,279,279,279,279,279,280,280,280,280,280,280,280,280,280,280,280,280,280,280,280,280,
  281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,281,
  282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,282,
  283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,283,
  284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,284,285 };

స్థిర స్థిరరాశి mz_uint8 s_tdefl_len_extra[256] = {
  0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
  4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,0 };

స్థిర స్థిరరాశి mz_uint8 s_tdefl_small_dist_sym[512] = {
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

స్థిర స్థిరరాశి mz_uint8 s_tdefl_small_dist_extra[512] = {
  0,0,0,0,1,1,1,1,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,
  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
  6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
  6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7 };

స్థిర స్థిరరాశి mz_uint8 s_tdefl_large_dist_sym[128] = {
  0,0,18,19,20,20,21,21,22,22,22,22,23,23,23,23,24,24,24,24,24,24,24,24,25,25,25,25,25,25,25,25,26,26,26,26,26,26,26,26,26,26,26,26,
  26,26,26,26,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,27,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,
  28,28,28,28,28,28,28,28,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29,29 };

స్థిర స్థిరరాశి mz_uint8 s_tdefl_large_dist_extra[128] = {
  0,0,8,8,9,9,9,9,10,10,10,10,10,10,10,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,
  12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,
  13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13,13 };

// Radix sorts tdefl_sym_freq[] array by 16-bit key m_key. Returns ptr to sorted values.
రకనిర్వచనం నిర్మాణం { mz_uint16 m_కీలకం, m_sym_సూచీ; } tdefl_sym_freq;
స్థిర tdefl_sym_freq* tdefl_radix_క్రమీకరించు_syms(mz_uint అంకె_syms, tdefl_sym_freq* pSyms0, tdefl_sym_freq* pSyms1)
{
  mz_uint32 మొత్తం_passes = 2, pass_జరుపు, pass, i, hist[256 * 2]; tdefl_sym_freq* pCur_syms = pSyms0, *pNew_syms = pSyms1; MZ_CLEAR_ARR(hist);
  కొరకు (i = 0; i < అంకె_syms; i++) { mz_uint freq = pSyms0[i].m_కీలకం; hist[freq & 0xFF]++; hist[256 + ((freq >> 8) & 0xFF)]++; }
  అయితే ((మొత్తం_passes > 1) && (అంకె_syms == hist[(మొత్తం_passes - 1) * 256])) మొత్తం_passes--;
  కొరకు (pass_జరుపు = 0, pass = 0; pass < మొత్తం_passes; pass++, pass_జరుపు += 8)
  {
    స్థిరరాశి mz_uint32* pHist = &hist[pass << 8];
    mz_uint offsets[256], cur_ofs = 0;
    కొరకు (i = 0; i < 256; i++) { offsets[i] = cur_ofs; cur_ofs += pHist[i]; }
    కొరకు (i = 0; i < అంకె_syms; i++) pNew_syms[offsets[(pCur_syms[i].m_కీలకం >> pass_జరుపు) & 0xFF]++] = pCur_syms[i];
    { tdefl_sym_freq* t = pCur_syms; pCur_syms = pNew_syms; pNew_syms = t; }
  }
  తిరిగి pCur_syms;
}

// tdefl_calculate_minimum_redundancy() originally written by: Alistair Moffat, alistair@cs.mu.oz.au, Jyrki Katajainen, jyrki@diku.dk, November 1996.
స్థిర శూన్య tdefl_calculate_minimum_redundancy(tdefl_sym_freq *A, పూర్ణాంకం n)
{
  పూర్ణాంకం మూలం, ఆకు, తదుపరి, avbl, వాడిన, dpth;
  ఒకవేళ (n==0) తిరిగి; లేకపోతే ఒకవేళ (n==1) { A[0].m_కీలకం = 1; తిరిగి; }
  A[0].m_కీలకం += A[1].m_కీలకం; మూలం = 0; ఆకు = 2;
  కొరకు (తదుపరి=1; తదుపరి < n-1; తదుపరి++)
  {
    ఒకవేళ (ఆకు>=n || A[మూలం].m_కీలకం<A[ఆకు].m_కీలకం) { A[తదుపరి].m_కీలకం = A[మూలం].m_కీలకం; A[మూలం++].m_కీలకం = (mz_uint16)తదుపరి; } లేకపోతే A[తదుపరి].m_కీలకం = A[ఆకు++].m_కీలకం;
    ఒకవేళ (ఆకు>=n || (మూలం<తదుపరి && A[మూలం].m_కీలకం<A[ఆకు].m_కీలకం)) { A[తదుపరి].m_కీలకం = (mz_uint16)(A[తదుపరి].m_కీలకం + A[మూలం].m_కీలకం); A[మూలం++].m_కీలకం = (mz_uint16)తదుపరి; } లేకపోతే A[తదుపరి].m_కీలకం = (mz_uint16)(A[తదుపరి].m_కీలకం + A[ఆకు++].m_కీలకం);
  }
  A[n-2].m_కీలకం = 0; కొరకు (తదుపరి=n-3; తదుపరి>=0; తదుపరి--) A[తదుపరి].m_కీలకం = A[A[తదుపరి].m_కీలకం].m_కీలకం+1;
  avbl = 1; వాడిన = dpth = 0; మూలం = n-2; తదుపరి = n-1;
  అయితే (avbl>0)
  {
    అయితే (మూలం>=0 && (పూర్ణాంకం)A[మూలం].m_కీలకం==dpth) { వాడిన++; మూలం--; }
    అయితే (avbl>వాడిన) { A[తదుపరి--].m_కీలకం = (mz_uint16)(dpth); avbl--; }
    avbl = 2*వాడిన; dpth++; వాడిన = 0;
  }
}

// Limits canonical Huffman code table's max code size.
గణన { TDEFL_MAX_SUPPORTED_HUFF_CODESIZE = 32 };
స్థిర శూన్య tdefl_huffman_enforce_max_సంకేతం_కొలత(పూర్ణాంకం *p_అంకె_codes, పూర్ణాంకం సంకేతం_list_len, పూర్ణాంకం max_సంకేతం_కొలత)
{
  పూర్ణాంకం i; mz_uint32 మొత్తం = 0; ఒకవేళ (సంకేతం_list_len <= 1) తిరిగి;
  కొరకు (i = max_సంకేతం_కొలత + 1; i <= TDEFL_MAX_SUPPORTED_HUFF_CODESIZE; i++) p_అంకె_codes[max_సంకేతం_కొలత] += p_అంకె_codes[i];
  కొరకు (i = max_సంకేతం_కొలత; i > 0; i--) మొత్తం += (((mz_uint32)p_అంకె_codes[i]) << (max_సంకేతం_కొలత - i));
  అయితే (మొత్తం != (1UL << max_సంకేతం_కొలత))
  {
    p_అంకె_codes[max_సంకేతం_కొలత]--;
    కొరకు (i = max_సంకేతం_కొలత - 1; i > 0; i--) ఒకవేళ (p_అంకె_codes[i]) { p_అంకె_codes[i]--; p_అంకె_codes[i + 1] += 2; ఆపు; }
    మొత్తం--;
  }
}

స్థిర శూన్య tdefl_optimize_huffman_పట్టిక(tdefl_compressor *d, పూర్ణాంకం పట్టిక_అంకె, పూర్ణాంకం పట్టిక_len, పూర్ణాంకం సంకేతం_కొలత_హద్దు, పూర్ణాంకం static_పట్టిక)
{
  పూర్ణాంకం i, j, l, అంకె_codes[1 + TDEFL_MAX_SUPPORTED_HUFF_CODESIZE]; mz_uint తదుపరి_సంకేతం[TDEFL_MAX_SUPPORTED_HUFF_CODESIZE + 1]; MZ_CLEAR_ARR(అంకె_codes);
  ఒకవేళ (static_పట్టిక)
  {
    కొరకు (i = 0; i < పట్టిక_len; i++) అంకె_codes[d->m_huff_సంకేతం_sizes[పట్టిక_అంకె][i]]++;
  }
  లేకపోతే
  {
    tdefl_sym_freq syms0[TDEFL_MAX_HUFF_SYMBOLS], syms1[TDEFL_MAX_HUFF_SYMBOLS], *pSyms;
    పూర్ణాంకం అంకె_వాడిన_syms = 0;
    స్థిరరాశి mz_uint16 *p_Sym_లెక్క = &d->m_huff_లెక్క[పట్టిక_అంకె][0];
    కొరకు (i = 0; i < పట్టిక_len; i++) ఒకవేళ (p_Sym_లెక్క[i]) { syms0[అంకె_వాడిన_syms].m_కీలకం = (mz_uint16)p_Sym_లెక్క[i]; syms0[అంకె_వాడిన_syms++].m_sym_సూచీ = (mz_uint16)i; }

    pSyms = tdefl_radix_క్రమీకరించు_syms(అంకె_వాడిన_syms, syms0, syms1); tdefl_calculate_minimum_redundancy(pSyms, అంకె_వాడిన_syms);

    కొరకు (i = 0; i < అంకె_వాడిన_syms; i++) అంకె_codes[pSyms[i].m_కీలకం]++;

    tdefl_huffman_enforce_max_సంకేతం_కొలత(అంకె_codes, అంకె_వాడిన_syms, సంకేతం_కొలత_హద్దు);

    MZ_CLEAR_ARR(d->m_huff_సంకేతం_sizes[పట్టిక_అంకె]); MZ_CLEAR_ARR(d->m_huff_codes[పట్టిక_అంకె]);
    కొరకు (i = 1, j = అంకె_వాడిన_syms; i <= సంకేతం_కొలత_హద్దు; i++)
      కొరకు (l = అంకె_codes[i]; l > 0; l--) d->m_huff_సంకేతం_sizes[పట్టిక_అంకె][pSyms[--j].m_sym_సూచీ] = (mz_uint8)(i);
  }

  తదుపరి_సంకేతం[1] = 0; కొరకు (j = 0, i = 2; i <= సంకేతం_కొలత_హద్దు; i++) తదుపరి_సంకేతం[i] = j = ((j + అంకె_codes[i - 1]) << 1);

  కొరకు (i = 0; i < పట్టిక_len; i++)
  {
    mz_uint rev_సంకేతం = 0, సంకేతం_2, సంకేతం_కొలత_2; ఒకవేళ ((సంకేతం_కొలత_2 = d->m_huff_సంకేతం_sizes[పట్టిక_అంకె][i]) == 0) కొనసాగు;
    సంకేతం_2 = తదుపరి_సంకేతం[సంకేతం_కొలత_2]++; కొరకు (l = సంకేతం_కొలత_2; l > 0; l--, సంకేతం_2 >>= 1) rev_సంకేతం = (rev_సంకేతం << 1) | (సంకేతం_2 & 1);
    d->m_huff_codes[పట్టిక_అంకె][i] = (mz_uint16)rev_సంకేతం;
  }
}

#నిర్వచించు TDEFL_PUT_బిట్లు(b, l) చేయి { \
  mz_uint బిట్లు = b; mz_uint len = l; MZ_ASSERT(బిట్లు <= ((1U << len) - 1U)); \
  d->m_బిట్టు_బఫరు |= (బిట్లు << d->m_బిట్లు_లోపల); d->m_బిట్లు_లోపల += len; \
  అయితే (d->m_బిట్లు_లోపల >= 8) { \
    ఒకవేళ (d->m_pOutput_buf < d->m_p_Output_buf_చివర) \
      *d->m_pOutput_buf++ = (mz_uint8)(d->m_బిట్టు_బఫరు); \
    d->m_బిట్టు_బఫరు >>= 8; \
    d->m_బిట్లు_లోపల -= 8; \
  } \
} MZ_MACRO_చివర

#నిర్వచించు TDEFL_RLE_PREV_సంకేతం_కొలత() చేయి { \
  ఒకవేళ (rle_repeat_లెక్క) { \
    ఒకవేళ (rle_repeat_లెక్క < 3) { \
      d->m_huff_లెక్క[2][prev_సంకేతం_కొలత] = (mz_uint16)(d->m_huff_లెక్క[2][prev_సంకేతం_కొలత] + rle_repeat_లెక్క); \
      అయితే (rle_repeat_లెక్క--) packed_సంకేతం_sizes[అంకె_packed_సంకేతం_sizes++] = prev_సంకేతం_కొలత; \
    } లేకపోతే { \
      d->m_huff_లెక్క[2][16] = (mz_uint16)(d->m_huff_లెక్క[2][16] + 1); packed_సంకేతం_sizes[అంకె_packed_సంకేతం_sizes++] = 16; packed_సంకేతం_sizes[అంకె_packed_సంకేతం_sizes++] = (mz_uint8)(rle_repeat_లెక్క - 3); \
  } rle_repeat_లెక్క = 0; } \
} MZ_MACRO_చివర

#నిర్వచించు TDEFL_RLE_ZERO_సంకేతం_కొలత() చేయి { \
  ఒకవేళ (rle_z_లెక్క) { \
    ఒకవేళ (rle_z_లెక్క < 3) { \
      d->m_huff_లెక్క[2][0] = (mz_uint16)(d->m_huff_లెక్క[2][0] + rle_z_లెక్క); అయితే (rle_z_లెక్క--) packed_సంకేతం_sizes[అంకె_packed_సంకేతం_sizes++] = 0; \
    } లేకపోతే ఒకవేళ (rle_z_లెక్క <= 10) { \
      d->m_huff_లెక్క[2][17] = (mz_uint16)(d->m_huff_లెక్క[2][17] + 1); packed_సంకేతం_sizes[అంకె_packed_సంకేతం_sizes++] = 17; packed_సంకేతం_sizes[అంకె_packed_సంకేతం_sizes++] = (mz_uint8)(rle_z_లెక్క - 3); \
    } లేకపోతే { \
      d->m_huff_లెక్క[2][18] = (mz_uint16)(d->m_huff_లెక్క[2][18] + 1); packed_సంకేతం_sizes[అంకె_packed_సంకేతం_sizes++] = 18; packed_సంకేతం_sizes[అంకె_packed_సంకేతం_sizes++] = (mz_uint8)(rle_z_లెక్క - 11); \
  } rle_z_లెక్క = 0; } \
} MZ_MACRO_చివర

స్థిర mz_uint8 s_tdefl_packed_సంకేతం_కొలత_syms_swizzle[] = { 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 };

స్థిర శూన్య tdefl_ప్రారంభం_dynamic_ఖండం(tdefl_compressor *d)
{
  పూర్ణాంకం అంకె_lit_codes, అంకె_dist_codes, అంకె_బిట్టు_lengths; mz_uint i, మొత్తం_సంకేతం_sizes_గమ్యం_pack, అంకె_packed_సంకేతం_sizes, rle_z_లెక్క, rle_repeat_లెక్క, packed_సంకేతం_sizes_సూచీ;
  mz_uint8 సంకేతం_sizes_గమ్యం_pack[TDEFL_MAX_HUFF_SYMBOLS_0 + TDEFL_MAX_HUFF_SYMBOLS_1], packed_సంకేతం_sizes[TDEFL_MAX_HUFF_SYMBOLS_0 + TDEFL_MAX_HUFF_SYMBOLS_1], prev_సంకేతం_కొలత = 0xFF;

  d->m_huff_లెక్క[0][256] = 1;

  tdefl_optimize_huffman_పట్టిక(d, 0, TDEFL_MAX_HUFF_SYMBOLS_0, 15, MZ_FALSE);
  tdefl_optimize_huffman_పట్టిక(d, 1, TDEFL_MAX_HUFF_SYMBOLS_1, 15, MZ_FALSE);

  కొరకు (అంకె_lit_codes = 286; అంకె_lit_codes > 257; అంకె_lit_codes--) ఒకవేళ (d->m_huff_సంకేతం_sizes[0][అంకె_lit_codes - 1]) ఆపు;
  కొరకు (అంకె_dist_codes = 30; అంకె_dist_codes > 1; అంకె_dist_codes--) ఒకవేళ (d->m_huff_సంకేతం_sizes[1][అంకె_dist_codes - 1]) ఆపు;

  జ్ఞాపకం_నకలు(సంకేతం_sizes_గమ్యం_pack, &d->m_huff_సంకేతం_sizes[0][0], అంకె_lit_codes);
  జ్ఞాపకం_నకలు(సంకేతం_sizes_గమ్యం_pack + అంకె_lit_codes, &d->m_huff_సంకేతం_sizes[1][0], అంకె_dist_codes);
  మొత్తం_సంకేతం_sizes_గమ్యం_pack = అంకె_lit_codes + అంకె_dist_codes; అంకె_packed_సంకేతం_sizes = 0; rle_z_లెక్క = 0; rle_repeat_లెక్క = 0;

  memset(&d->m_huff_లెక్క[2][0], 0, పరిమాణం(d->m_huff_లెక్క[2][0]) * TDEFL_MAX_HUFF_SYMBOLS_2);
  కొరకు (i = 0; i < మొత్తం_సంకేతం_sizes_గమ్యం_pack; i++)
  {
    mz_uint8 సంకేతం_కొలత_2 = సంకేతం_sizes_గమ్యం_pack[i];
    ఒకవేళ (!సంకేతం_కొలత_2)
    {
      TDEFL_RLE_PREV_సంకేతం_కొలత();
      ఒకవేళ (++rle_z_లెక్క == 138) { TDEFL_RLE_ZERO_సంకేతం_కొలత(); }
    }
    లేకపోతే
    {
      TDEFL_RLE_ZERO_సంకేతం_కొలత();
      ఒకవేళ (సంకేతం_కొలత_2 != prev_సంకేతం_కొలత)
      {
        TDEFL_RLE_PREV_సంకేతం_కొలత();
        d->m_huff_లెక్క[2][సంకేతం_కొలత_2] = (mz_uint16)(d->m_huff_లెక్క[2][సంకేతం_కొలత_2] + 1); packed_సంకేతం_sizes[అంకె_packed_సంకేతం_sizes++] = సంకేతం_కొలత_2;
      }
      లేకపోతే ఒకవేళ (++rle_repeat_లెక్క == 6)
      {
        TDEFL_RLE_PREV_సంకేతం_కొలత();
      }
    }
    prev_సంకేతం_కొలత = సంకేతం_కొలత_2;
  }
  ఒకవేళ (rle_repeat_లెక్క) { TDEFL_RLE_PREV_సంకేతం_కొలత(); } లేకపోతే { TDEFL_RLE_ZERO_సంకేతం_కొలత(); }

  tdefl_optimize_huffman_పట్టిక(d, 2, TDEFL_MAX_HUFF_SYMBOLS_2, 7, MZ_FALSE);

  TDEFL_PUT_బిట్లు(2, 2);

  TDEFL_PUT_బిట్లు(అంకె_lit_codes - 257, 5);
  TDEFL_PUT_బిట్లు(అంకె_dist_codes - 1, 5);

  కొరకు (అంకె_బిట్టు_lengths = 18; అంకె_బిట్టు_lengths >= 0; అంకె_బిట్టు_lengths--) ఒకవేళ (d->m_huff_సంకేతం_sizes[2][s_tdefl_packed_సంకేతం_కొలత_syms_swizzle[అంకె_బిట్టు_lengths]]) ఆపు;
  అంకె_బిట్టు_lengths = MZ_MAX(4, (అంకె_బిట్టు_lengths + 1)); TDEFL_PUT_బిట్లు(అంకె_బిట్టు_lengths - 4, 4);
  కొరకు (i = 0; (పూర్ణాంకం)i < అంకె_బిట్టు_lengths; i++) TDEFL_PUT_బిట్లు(d->m_huff_సంకేతం_sizes[2][s_tdefl_packed_సంకేతం_కొలత_syms_swizzle[i]], 3);

  కొరకు (packed_సంకేతం_sizes_సూచీ = 0; packed_సంకేతం_sizes_సూచీ < అంకె_packed_సంకేతం_sizes; )
  {
    mz_uint సంకేతం_2 = packed_సంకేతం_sizes[packed_సంకేతం_sizes_సూచీ++]; MZ_ASSERT(సంకేతం_2 < TDEFL_MAX_HUFF_SYMBOLS_2);
    TDEFL_PUT_బిట్లు(d->m_huff_codes[2][సంకేతం_2], d->m_huff_సంకేతం_sizes[2][సంకేతం_2]);
    ఒకవేళ (సంకేతం_2 >= 16) TDEFL_PUT_బిట్లు(packed_సంకేతం_sizes[packed_సంకేతం_sizes_సూచీ++], "\02\03\07"[సంకేతం_2 - 16]);
  }
}

స్థిర శూన్య tdefl_ప్రారంభం_static_ఖండం(tdefl_compressor *d)
{
  mz_uint i;
  mz_uint8 *p = &d->m_huff_సంకేతం_sizes[0][0];

  కొరకు (i = 0; i <= 143; ++i) *p++ = 8;
  కొరకు ( ; i <= 255; ++i) *p++ = 9;
  కొరకు ( ; i <= 279; ++i) *p++ = 7;
  కొరకు ( ; i <= 287; ++i) *p++ = 8;

  memset(d->m_huff_సంకేతం_sizes[1], 5, 32);

  tdefl_optimize_huffman_పట్టిక(d, 0, 288, 15, MZ_TRUE);
  tdefl_optimize_huffman_పట్టిక(d, 1, 32, 15, MZ_TRUE);

  TDEFL_PUT_బిట్లు(1, 2);
}

స్థిర స్థిరరాశి mz_uint mz_bitmasks[17] = { 0x0000, 0x0001, 0x0003, 0x0007, 0x000F, 0x001F, 0x003F, 0x007F, 0x00FF, 0x01FF, 0x03FF, 0x07FF, 0x0FFF, 0x1FFF, 0x3FFF, 0x7FFF, 0xFFFF };

#ఒకవేళ MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN && MINIZ_HAS_64_బిట్టు_REGISTERS
స్థిర mz_bool tdefl_compress_lz_codes(tdefl_compressor *d)
{
  mz_uint flags;
  mz_uint8 *pLZ_codes;
  mz_uint8 *pOutput_buf = d->m_pOutput_buf;
  mz_uint8 *p_LZ_సంకేతం_buf_చివర = d->m_p_LZ_సంకేతం_buf;
  mz_uint64 బిట్టు_బఫరు = d->m_బిట్టు_బఫరు;
  mz_uint బిట్లు_లోపల = d->m_బిట్లు_లోపల;

#నిర్వచించు TDEFL_PUT_బిట్లు_FAST(b, l) { బిట్టు_బఫరు |= (((mz_uint64)(b)) << బిట్లు_లోపల); బిట్లు_లోపల += (l); }

  flags = 1;
  కొరకు (pLZ_codes = d->m_lz_సంకేతం_buf; pLZ_codes < p_LZ_సంకేతం_buf_చివర; flags >>= 1)
  {
    ఒకవేళ (flags == 1)
      flags = *pLZ_codes++ | 0x100;

    ఒకవేళ (flags & 1)
    {
      mz_uint s0, s1, n0, n1, sym, అంకె_extra_బిట్లు;
      mz_uint సరిపోలిక_len = pLZ_codes[0], సరిపోలిక_dist = *(స్థిరరాశి mz_uint16 *)(pLZ_codes + 1); pLZ_codes += 3;

      MZ_ASSERT(d->m_huff_సంకేతం_sizes[0][s_tdefl_len_sym[సరిపోలిక_len]]);
      TDEFL_PUT_బిట్లు_FAST(d->m_huff_codes[0][s_tdefl_len_sym[సరిపోలిక_len]], d->m_huff_సంకేతం_sizes[0][s_tdefl_len_sym[సరిపోలిక_len]]);
      TDEFL_PUT_బిట్లు_FAST(సరిపోలిక_len & mz_bitmasks[s_tdefl_len_extra[సరిపోలిక_len]], s_tdefl_len_extra[సరిపోలిక_len]);

      // This sequence coaxes MSVC into using cmov's vs. jmp's.
      s0 = s_tdefl_small_dist_sym[సరిపోలిక_dist & 511];
      n0 = s_tdefl_small_dist_extra[సరిపోలిక_dist & 511];
      s1 = s_tdefl_large_dist_sym[సరిపోలిక_dist >> 8];
      n1 = s_tdefl_large_dist_extra[సరిపోలిక_dist >> 8];
      sym = (సరిపోలిక_dist < 512) ? s0 : s1;
      అంకె_extra_బిట్లు = (సరిపోలిక_dist < 512) ? n0 : n1;

      MZ_ASSERT(d->m_huff_సంకేతం_sizes[1][sym]);
      TDEFL_PUT_బిట్లు_FAST(d->m_huff_codes[1][sym], d->m_huff_సంకేతం_sizes[1][sym]);
      TDEFL_PUT_బిట్లు_FAST(సరిపోలిక_dist & mz_bitmasks[అంకె_extra_బిట్లు], అంకె_extra_బిట్లు);
    }
    లేకపోతే
    {
      mz_uint lit = *pLZ_codes++;
      MZ_ASSERT(d->m_huff_సంకేతం_sizes[0][lit]);
      TDEFL_PUT_బిట్లు_FAST(d->m_huff_codes[0][lit], d->m_huff_సంకేతం_sizes[0][lit]);

      ఒకవేళ (((flags & 2) == 0) && (pLZ_codes < p_LZ_సంకేతం_buf_చివర))
      {
        flags >>= 1;
        lit = *pLZ_codes++;
        MZ_ASSERT(d->m_huff_సంకేతం_sizes[0][lit]);
        TDEFL_PUT_బిట్లు_FAST(d->m_huff_codes[0][lit], d->m_huff_సంకేతం_sizes[0][lit]);

        ఒకవేళ (((flags & 2) == 0) && (pLZ_codes < p_LZ_సంకేతం_buf_చివర))
        {
          flags >>= 1;
          lit = *pLZ_codes++;
          MZ_ASSERT(d->m_huff_సంకేతం_sizes[0][lit]);
          TDEFL_PUT_బిట్లు_FAST(d->m_huff_codes[0][lit], d->m_huff_సంకేతం_sizes[0][lit]);
        }
      }
    }

    ఒకవేళ (pOutput_buf >= d->m_p_Output_buf_చివర)
      తిరిగి MZ_FALSE;

    *(mz_uint64*)pOutput_buf = బిట్టు_బఫరు;
    pOutput_buf += (బిట్లు_లోపల >> 3);
    బిట్టు_బఫరు >>= (బిట్లు_లోపల & ~7);
    బిట్లు_లోపల &= 7;
  }

#నిర్వచనం_రద్దు TDEFL_PUT_బిట్లు_FAST

  d->m_pOutput_buf = pOutput_buf;
  d->m_బిట్లు_లోపల = 0;
  d->m_బిట్టు_బఫరు = 0;

  అయితే (బిట్లు_లోపల)
  {
    mz_uint32 n = MZ_MIN(బిట్లు_లోపల, 16);
    TDEFL_PUT_బిట్లు((mz_uint)బిట్టు_బఫరు & mz_bitmasks[n], n);
    బిట్టు_బఫరు >>= n;
    బిట్లు_లోపల -= n;
  }

  TDEFL_PUT_బిట్లు(d->m_huff_codes[0][256], d->m_huff_సంకేతం_sizes[0][256]);

  తిరిగి (d->m_pOutput_buf < d->m_p_Output_buf_చివర);
}
#లేకపోతే
స్థిర mz_bool tdefl_compress_lz_codes(tdefl_compressor *d)
{
  mz_uint flags;
  mz_uint8 *pLZ_codes;

  flags = 1;
  కొరకు (pLZ_codes = d->m_lz_సంకేతం_buf; pLZ_codes < d->m_p_LZ_సంకేతం_buf; flags >>= 1)
  {
    ఒకవేళ (flags == 1)
      flags = *pLZ_codes++ | 0x100;
    ఒకవేళ (flags & 1)
    {
      mz_uint sym, అంకె_extra_బిట్లు;
      mz_uint సరిపోలిక_len = pLZ_codes[0], సరిపోలిక_dist = (pLZ_codes[1] | (pLZ_codes[2] << 8)); pLZ_codes += 3;

      MZ_ASSERT(d->m_huff_సంకేతం_sizes[0][s_tdefl_len_sym[సరిపోలిక_len]]);
      TDEFL_PUT_బిట్లు(d->m_huff_codes[0][s_tdefl_len_sym[సరిపోలిక_len]], d->m_huff_సంకేతం_sizes[0][s_tdefl_len_sym[సరిపోలిక_len]]);
      TDEFL_PUT_బిట్లు(సరిపోలిక_len & mz_bitmasks[s_tdefl_len_extra[సరిపోలిక_len]], s_tdefl_len_extra[సరిపోలిక_len]);

      ఒకవేళ (సరిపోలిక_dist < 512)
      {
        sym = s_tdefl_small_dist_sym[సరిపోలిక_dist]; అంకె_extra_బిట్లు = s_tdefl_small_dist_extra[సరిపోలిక_dist];
      }
      లేకపోతే
      {
        sym = s_tdefl_large_dist_sym[సరిపోలిక_dist >> 8]; అంకె_extra_బిట్లు = s_tdefl_large_dist_extra[సరిపోలిక_dist >> 8];
      }
      MZ_ASSERT(d->m_huff_సంకేతం_sizes[1][sym]);
      TDEFL_PUT_బిట్లు(d->m_huff_codes[1][sym], d->m_huff_సంకేతం_sizes[1][sym]);
      TDEFL_PUT_బిట్లు(సరిపోలిక_dist & mz_bitmasks[అంకె_extra_బిట్లు], అంకె_extra_బిట్లు);
    }
    లేకపోతే
    {
      mz_uint lit = *pLZ_codes++;
      MZ_ASSERT(d->m_huff_సంకేతం_sizes[0][lit]);
      TDEFL_PUT_బిట్లు(d->m_huff_codes[0][lit], d->m_huff_సంకేతం_sizes[0][lit]);
    }
  }

  TDEFL_PUT_బిట్లు(d->m_huff_codes[0][256], d->m_huff_సంకేతం_sizes[0][256]);

  తిరిగి (d->m_pOutput_buf < d->m_p_Output_buf_చివర);
}
#అయితే_ముగింపు // MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN && MINIZ_HAS_64BIT_REGISTERS

స్థిర mz_bool tdefl_compress_ఖండం(tdefl_compressor *d, mz_bool static_ఖండం)
{
  ఒకవేళ (static_ఖండం)
    tdefl_ప్రారంభం_static_ఖండం(d);
  లేకపోతే
    tdefl_ప్రారంభం_dynamic_ఖండం(d);
  తిరిగి tdefl_compress_lz_codes(d);
}

స్థిర పూర్ణాంకం tdefl_flush_ఖండం(tdefl_compressor *d, పూర్ణాంకం flush)
{
  mz_uint saved_బిట్టు_buf, saved_బిట్లు_లోపల;
  mz_uint8 *pSaved_output_buf;
  mz_bool comp_ఖండం_succeeded = MZ_FALSE;
  పూర్ణాంకం n, use_raw_ఖండం = ((d->m_flags & TDEFL_FORCE_ALL_RAW_ఖండాలు) != 0) && (d->m_lookahead_pos - d->m_lz_సంకేతం_buf_dict_pos) <= d->m_dict_కొలత;
  mz_uint8 *p_Output_buf_ప్రారంభం = ((d->m_pPut_buf_func == ఖాళీ) && ((*d->m_p_బహిర్గతం_buf_కొలత - d->m_బహిర్గతం_buf_ofs) >= TDEFL_బహిర్గతం_BUF_కొలత)) ? ((mz_uint8 *)d->m_p_బహిర్గతం_buf + d->m_బహిర్గతం_buf_ofs) : d->m_output_buf;

  d->m_pOutput_buf = p_Output_buf_ప్రారంభం;
  d->m_p_Output_buf_చివర = d->m_pOutput_buf + TDEFL_బహిర్గతం_BUF_కొలత - 16;

  MZ_ASSERT(!d->m_output_flush_మిగిలిన);
  d->m_output_flush_ofs = 0;
  d->m_output_flush_మిగిలిన = 0;

  *d->m_pLZ_flags = (mz_uint8)(*d->m_pLZ_flags >> d->m_అంకె_flags_ఎడమ);
  d->m_p_LZ_సంకేతం_buf -= (d->m_అంకె_flags_ఎడమ == 8);

  ఒకవేళ ((d->m_flags & TDEFL_WRITE_ZLIB_శీర్షిక) && (!d->m_ఖండం_సూచీ))
  {
    TDEFL_PUT_బిట్లు(0x78, 8); TDEFL_PUT_బిట్లు(0x01, 8);
  }

  TDEFL_PUT_బిట్లు(flush == TDEFL_ముగింపు, 1);

  pSaved_output_buf = d->m_pOutput_buf; saved_బిట్టు_buf = d->m_బిట్టు_బఫరు; saved_బిట్లు_లోపల = d->m_బిట్లు_లోపల;

  ఒకవేళ (!use_raw_ఖండం)
    comp_ఖండం_succeeded = tdefl_compress_ఖండం(d, (d->m_flags & TDEFL_FORCE_ALL_STATIC_ఖండాలు) || (d->m_మొత్తం_lz_బైట్లు < 48));

  // If the block gets expanded, forget the current contents of the output buffer and send a raw block instead.
  ఒకవేళ ( ((use_raw_ఖండం) || ((d->m_మొత్తం_lz_బైట్లు) && ((d->m_pOutput_buf - pSaved_output_buf + 1U) >= d->m_మొత్తం_lz_బైట్లు))) &&
       ((d->m_lookahead_pos - d->m_lz_సంకేతం_buf_dict_pos) <= d->m_dict_కొలత) )
  {
    mz_uint i; d->m_pOutput_buf = pSaved_output_buf; d->m_బిట్టు_బఫరు = saved_బిట్టు_buf; d->m_బిట్లు_లోపల = saved_బిట్లు_లోపల;
    TDEFL_PUT_బిట్లు(0, 2);
    ఒకవేళ (d->m_బిట్లు_లోపల) { TDEFL_PUT_బిట్లు(0, 8 - d->m_బిట్లు_లోపల); }
    కొరకు (i = 2; i; --i, d->m_మొత్తం_lz_బైట్లు ^= 0xFFFF)
    {
      TDEFL_PUT_బిట్లు(d->m_మొత్తం_lz_బైట్లు & 0xFFFF, 16);
    }
    కొరకు (i = 0; i < d->m_మొత్తం_lz_బైట్లు; ++i)
    {
      TDEFL_PUT_బిట్లు(d->m_dict[(d->m_lz_సంకేతం_buf_dict_pos + i) & TDEFL_LZ_DICT_కొలత_ముసుగు], 8);
    }
  }
  // Check for the extremely unlikely (if not impossible) case of the compressed block not fitting into the output buffer when using dynamic codes.
  లేకపోతే ఒకవేళ (!comp_ఖండం_succeeded)
  {
    d->m_pOutput_buf = pSaved_output_buf; d->m_బిట్టు_బఫరు = saved_బిట్టు_buf; d->m_బిట్లు_లోపల = saved_బిట్లు_లోపల;
    tdefl_compress_ఖండం(d, MZ_TRUE);
  }

  ఒకవేళ (flush)
  {
    ఒకవేళ (flush == TDEFL_ముగింపు)
    {
      ఒకవేళ (d->m_బిట్లు_లోపల) { TDEFL_PUT_బిట్లు(0, 8 - d->m_బిట్లు_లోపల); }
      ఒకవేళ (d->m_flags & TDEFL_WRITE_ZLIB_శీర్షిక) { mz_uint i, a = d->m_adler32; కొరకు (i = 0; i < 4; i++) { TDEFL_PUT_బిట్లు((a >> 24) & 0xFF, 8); a <<= 8; } }
    }
    లేకపోతే
    {
      mz_uint i, z = 0; TDEFL_PUT_బిట్లు(0, 3); ఒకవేళ (d->m_బిట్లు_లోపల) { TDEFL_PUT_బిట్లు(0, 8 - d->m_బిట్లు_లోపల); } కొరకు (i = 2; i; --i, z ^= 0xFFFF) { TDEFL_PUT_బిట్లు(z & 0xFFFF, 16); }
    }
  }

  MZ_ASSERT(d->m_pOutput_buf < d->m_p_Output_buf_చివర);

  memset(&d->m_huff_లెక్క[0][0], 0, పరిమాణం(d->m_huff_లెక్క[0][0]) * TDEFL_MAX_HUFF_SYMBOLS_0);
  memset(&d->m_huff_లెక్క[1][0], 0, పరిమాణం(d->m_huff_లెక్క[1][0]) * TDEFL_MAX_HUFF_SYMBOLS_1);

  d->m_p_LZ_సంకేతం_buf = d->m_lz_సంకేతం_buf + 1; d->m_pLZ_flags = d->m_lz_సంకేతం_buf; d->m_అంకె_flags_ఎడమ = 8; d->m_lz_సంకేతం_buf_dict_pos += d->m_మొత్తం_lz_బైట్లు; d->m_మొత్తం_lz_బైట్లు = 0; d->m_ఖండం_సూచీ++;

  ఒకవేళ ((n = (పూర్ణాంకం)(d->m_pOutput_buf - p_Output_buf_ప్రారంభం)) != 0)
  {
    ఒకవేళ (d->m_pPut_buf_func)
    {
      *d->m_p_లోపల_buf_కొలత = d->m_pSrc - (స్థిరరాశి mz_uint8 *)d->m_p_లోపల_buf;
      ఒకవేళ (!(*d->m_pPut_buf_func)(d->m_output_buf, n, d->m_pPut_buf_user))
        తిరిగి (d->m_prev_return_స్థితి = TDEFL_స్థితి_PUT_BUF_FAILED);
    }
    లేకపోతే ఒకవేళ (p_Output_buf_ప్రారంభం == d->m_output_buf)
    {
      పూర్ణాంకం బైట్లు_గమ్యం_copy = (పూర్ణాంకం)MZ_MIN((size_t)n, (size_t)(*d->m_p_బహిర్గతం_buf_కొలత - d->m_బహిర్గతం_buf_ofs));
      జ్ఞాపకం_నకలు((mz_uint8 *)d->m_p_బహిర్గతం_buf + d->m_బహిర్గతం_buf_ofs, d->m_output_buf, బైట్లు_గమ్యం_copy);
      d->m_బహిర్గతం_buf_ofs += బైట్లు_గమ్యం_copy;
      ఒకవేళ ((n -= బైట్లు_గమ్యం_copy) != 0)
      {
        d->m_output_flush_ofs = బైట్లు_గమ్యం_copy;
        d->m_output_flush_మిగిలిన = n;
      }
    }
    లేకపోతే
    {
      d->m_బహిర్గతం_buf_ofs += n;
    }
  }

  తిరిగి d->m_output_flush_మిగిలిన;
}

#ఒకవేళ MINIZ_USE_UNALIGNED_LOADS_AND_STORES
#నిర్వచించు TDEFL_READ_UNALIGNED_మాట(p) *(స్థిరరాశి mz_uint16*)(p)
స్థిర MZ_FORCEINLINE శూన్య tdefl_కనుగొను_సరిపోలిక(tdefl_compressor *d, mz_uint lookahead_pos, mz_uint max_dist, mz_uint max_సరిపోలిక_len, mz_uint *p_సరిపోలిక_dist, mz_uint *p_సరిపోలిక_len)
{
  mz_uint dist, pos = lookahead_pos & TDEFL_LZ_DICT_కొలత_ముసుగు, సరిపోలిక_len = *p_సరిపోలిక_len, probe_pos = pos, తదుపరి_probe_pos, probe_len;
  mz_uint అంకె_probes_ఎడమ = d->m_max_probes[సరిపోలిక_len >= 32];
  స్థిరరాశి mz_uint16 *s = (స్థిరరాశి mz_uint16*)(d->m_dict + pos), *p, *q;
  mz_uint16 c01 = TDEFL_READ_UNALIGNED_మాట(&d->m_dict[pos + సరిపోలిక_len - 1]), s01 = TDEFL_READ_UNALIGNED_మాట(s);
  MZ_ASSERT(max_సరిపోలిక_len <= TDEFL_MAX_సరిపోలిక_LEN); ఒకవేళ (max_సరిపోలిక_len <= సరిపోలిక_len) తిరిగి;
  కొరకు ( ; ; )
  {
    కొరకు ( ; ; )
    {
      ఒకవేళ (--అంకె_probes_ఎడమ == 0) తిరిగి;
      #నిర్వచించు TDEFL_PROBE \
        తదుపరి_probe_pos = d->m_తదుపరి[probe_pos]; \
        ఒకవేళ ((!తదుపరి_probe_pos) || ((dist = (mz_uint16)(lookahead_pos - తదుపరి_probe_pos)) > max_dist)) తిరిగి; \
        probe_pos = తదుపరి_probe_pos & TDEFL_LZ_DICT_కొలత_ముసుగు; \
        ఒకవేళ (TDEFL_READ_UNALIGNED_మాట(&d->m_dict[probe_pos + సరిపోలిక_len - 1]) == c01) ఆపు;
      TDEFL_PROBE
      TDEFL_PROBE
      TDEFL_PROBE
    }
    ఒకవేళ (!dist) ఆపు;
    q = (స్థిరరాశి mz_uint16*)(d->m_dict + probe_pos);
    ఒకవేళ (TDEFL_READ_UNALIGNED_మాట(q) != s01) కొనసాగు;
    p = s; probe_len = 32;
    చేయి { } అయితే ( (TDEFL_READ_UNALIGNED_మాట(++p) == TDEFL_READ_UNALIGNED_మాట(++q)) && (TDEFL_READ_UNALIGNED_మాట(++p) == TDEFL_READ_UNALIGNED_మాట(++q)) &&
                   (TDEFL_READ_UNALIGNED_మాట(++p) == TDEFL_READ_UNALIGNED_మాట(++q)) && (TDEFL_READ_UNALIGNED_మాట(++p) == TDEFL_READ_UNALIGNED_మాట(++q)) && (--probe_len > 0) );
    ఒకవేళ (!probe_len)
    {
      *p_సరిపోలిక_dist = dist; *p_సరిపోలిక_len = MZ_MIN(max_సరిపోలిక_len, TDEFL_MAX_సరిపోలిక_LEN); ఆపు;
    }
    లేకపోతే ఒకవేళ ((probe_len = ((mz_uint)(p - s) * 2) + (mz_uint)(*(స్థిరరాశి mz_uint8*)p == *(స్థిరరాశి mz_uint8*)q)) > సరిపోలిక_len)
    {
      *p_సరిపోలిక_dist = dist; ఒకవేళ ((*p_సరిపోలిక_len = సరిపోలిక_len = MZ_MIN(max_సరిపోలిక_len, probe_len)) == max_సరిపోలిక_len) ఆపు;
      c01 = TDEFL_READ_UNALIGNED_మాట(&d->m_dict[pos + సరిపోలిక_len - 1]);
    }
  }
}
#లేకపోతే
స్థిర MZ_FORCEINLINE శూన్య tdefl_కనుగొను_సరిపోలిక(tdefl_compressor *d, mz_uint lookahead_pos, mz_uint max_dist, mz_uint max_సరిపోలిక_len, mz_uint *p_సరిపోలిక_dist, mz_uint *p_సరిపోలిక_len)
{
  mz_uint dist, pos = lookahead_pos & TDEFL_LZ_DICT_కొలత_ముసుగు, సరిపోలిక_len = *p_సరిపోలిక_len, probe_pos = pos, తదుపరి_probe_pos, probe_len;
  mz_uint అంకె_probes_ఎడమ = d->m_max_probes[సరిపోలిక_len >= 32];
  స్థిరరాశి mz_uint8 *s = d->m_dict + pos, *p, *q;
  mz_uint8 c0 = d->m_dict[pos + సరిపోలిక_len], c1 = d->m_dict[pos + సరిపోలిక_len - 1];
  MZ_ASSERT(max_సరిపోలిక_len <= TDEFL_MAX_సరిపోలిక_LEN); ఒకవేళ (max_సరిపోలిక_len <= సరిపోలిక_len) తిరిగి;
  కొరకు ( ; ; )
  {
    కొరకు ( ; ; )
    {
      ఒకవేళ (--అంకె_probes_ఎడమ == 0) తిరిగి;
      #నిర్వచించు TDEFL_PROBE \
        తదుపరి_probe_pos = d->m_తదుపరి[probe_pos]; \
        ఒకవేళ ((!తదుపరి_probe_pos) || ((dist = (mz_uint16)(lookahead_pos - తదుపరి_probe_pos)) > max_dist)) తిరిగి; \
        probe_pos = తదుపరి_probe_pos & TDEFL_LZ_DICT_కొలత_ముసుగు; \
        ఒకవేళ ((d->m_dict[probe_pos + సరిపోలిక_len] == c0) && (d->m_dict[probe_pos + సరిపోలిక_len - 1] == c1)) ఆపు;
      TDEFL_PROBE
      TDEFL_PROBE
      TDEFL_PROBE
    }
    ఒకవేళ (!dist) ఆపు;
    p = s; q = d->m_dict + probe_pos;
    కొరకు (probe_len = 0; probe_len < max_సరిపోలిక_len; probe_len++) {
        ఒకవేళ (*p++ != *q++) ఆపు;
    }
    ఒకవేళ (probe_len > సరిపోలిక_len)
    {
      *p_సరిపోలిక_dist = dist;
      ఒకవేళ ((*p_సరిపోలిక_len = సరిపోలిక_len = probe_len) == max_సరిపోలిక_len) తిరిగి;
      c0 = d->m_dict[pos + సరిపోలిక_len]; c1 = d->m_dict[pos + సరిపోలిక_len - 1];
    }
  }
}
#అయితే_ముగింపు // #if MINIZ_USE_UNALIGNED_LOADS_AND_STORES

#ఒకవేళ MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
స్థిర mz_bool tdefl_compress_fast(tdefl_compressor *d)
{
  // Faster, minimally featured LZRW1-style match+parse loop with better register utilization. Intended for applications where raw throughput is valued more highly than ratio.
  mz_uint lookahead_pos = d->m_lookahead_pos, lookahead_కొలత = d->m_lookahead_కొలత, dict_కొలత = d->m_dict_కొలత, మొత్తం_lz_బైట్లు = d->m_మొత్తం_lz_బైట్లు, అంకె_flags_ఎడమ = d->m_అంకె_flags_ఎడమ;
  mz_uint8 *p_LZ_సంకేతం_buf = d->m_p_LZ_సంకేతం_buf, *pLZ_flags = d->m_pLZ_flags;
  mz_uint cur_pos = lookahead_pos & TDEFL_LZ_DICT_కొలత_ముసుగు;

  అయితే ((d->m_src_buf_ఎడమ) || ((d->m_flush) && (lookahead_కొలత)))
  {
    స్థిరరాశి mz_uint TDEFL_COMP_FAST_LOOKAHEAD_కొలత = 4096;
    mz_uint dst_pos = (lookahead_pos + lookahead_కొలత) & TDEFL_LZ_DICT_కొలత_ముసుగు;
    mz_uint అంకె_బైట్లు_గమ్యం_process = (mz_uint)MZ_MIN(d->m_src_buf_ఎడమ, TDEFL_COMP_FAST_LOOKAHEAD_కొలత - lookahead_కొలత);
    d->m_src_buf_ఎడమ -= అంకె_బైట్లు_గమ్యం_process;
    lookahead_కొలత += అంకె_బైట్లు_గమ్యం_process;

    అయితే (అంకె_బైట్లు_గమ్యం_process)
    {
      mz_uint32 n = MZ_MIN(TDEFL_LZ_DICT_కొలత - dst_pos, అంకె_బైట్లు_గమ్యం_process);
      జ్ఞాపకం_నకలు(d->m_dict + dst_pos, d->m_pSrc, n);
      ఒకవేళ (dst_pos < (TDEFL_MAX_సరిపోలిక_LEN - 1))
        జ్ఞాపకం_నకలు(d->m_dict + TDEFL_LZ_DICT_కొలత + dst_pos, d->m_pSrc, MZ_MIN(n, (TDEFL_MAX_సరిపోలిక_LEN - 1) - dst_pos));
      d->m_pSrc += n;
      dst_pos = (dst_pos + n) & TDEFL_LZ_DICT_కొలత_ముసుగు;
      అంకె_బైట్లు_గమ్యం_process -= n;
    }

    dict_కొలత = MZ_MIN(TDEFL_LZ_DICT_కొలత - lookahead_కొలత, dict_కొలత);
    ఒకవేళ ((!d->m_flush) && (lookahead_కొలత < TDEFL_COMP_FAST_LOOKAHEAD_కొలత)) ఆపు;

    అయితే (lookahead_కొలత >= 4)
    {
      mz_uint cur_సరిపోలిక_dist, cur_సరిపోలిక_len = 1;
      mz_uint8 *pCur_dict = d->m_dict + cur_pos;
      mz_uint మొదటి_trigram = (*(స్థిరరాశి mz_uint32 *)pCur_dict) & 0xFFFFFF;
      mz_uint hash = (మొదటి_trigram ^ (మొదటి_trigram >> (24 - (TDEFL_LZ_HASH_బిట్లు - 8)))) & TDEFL_LEVEL1_HASH_కొలత_ముసుగు;
      mz_uint probe_pos = d->m_hash[hash];
      d->m_hash[hash] = (mz_uint16)lookahead_pos;

      ఒకవేళ (((cur_సరిపోలిక_dist = (mz_uint16)(lookahead_pos - probe_pos)) <= dict_కొలత) && ((*(స్థిరరాశి mz_uint32 *)(d->m_dict + (probe_pos &= TDEFL_LZ_DICT_కొలత_ముసుగు)) & 0xFFFFFF) == మొదటి_trigram))
      {
        స్థిరరాశి mz_uint16 *p = (స్థిరరాశి mz_uint16 *)pCur_dict;
        స్థిరరాశి mz_uint16 *q = (స్థిరరాశి mz_uint16 *)(d->m_dict + probe_pos);
        mz_uint32 probe_len = 32;
        చేయి { } అయితే ( (TDEFL_READ_UNALIGNED_మాట(++p) == TDEFL_READ_UNALIGNED_మాట(++q)) && (TDEFL_READ_UNALIGNED_మాట(++p) == TDEFL_READ_UNALIGNED_మాట(++q)) &&
          (TDEFL_READ_UNALIGNED_మాట(++p) == TDEFL_READ_UNALIGNED_మాట(++q)) && (TDEFL_READ_UNALIGNED_మాట(++p) == TDEFL_READ_UNALIGNED_మాట(++q)) && (--probe_len > 0) );
        cur_సరిపోలిక_len = ((mz_uint)(p - (స్థిరరాశి mz_uint16 *)pCur_dict) * 2) + (mz_uint)(*(స్థిరరాశి mz_uint8 *)p == *(స్థిరరాశి mz_uint8 *)q);
        ఒకవేళ (!probe_len)
          cur_సరిపోలిక_len = cur_సరిపోలిక_dist ? TDEFL_MAX_సరిపోలిక_LEN : 0;

        ఒకవేళ ((cur_సరిపోలిక_len < TDEFL_MIN_సరిపోలిక_LEN) || ((cur_సరిపోలిక_len == TDEFL_MIN_సరిపోలిక_LEN) && (cur_సరిపోలిక_dist >= 8U*1024U)))
        {
          cur_సరిపోలిక_len = 1;
          *p_LZ_సంకేతం_buf++ = (mz_uint8)మొదటి_trigram;
          *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
          d->m_huff_లెక్క[0][(mz_uint8)మొదటి_trigram]++;
        }
        లేకపోతే
        {
          mz_uint32 s0, s1;
          cur_సరిపోలిక_len = MZ_MIN(cur_సరిపోలిక_len, lookahead_కొలత);

          MZ_ASSERT((cur_సరిపోలిక_len >= TDEFL_MIN_సరిపోలిక_LEN) && (cur_సరిపోలిక_dist >= 1) && (cur_సరిపోలిక_dist <= TDEFL_LZ_DICT_కొలత));

          cur_సరిపోలిక_dist--;

          p_LZ_సంకేతం_buf[0] = (mz_uint8)(cur_సరిపోలిక_len - TDEFL_MIN_సరిపోలిక_LEN);
          *(mz_uint16 *)(&p_LZ_సంకేతం_buf[1]) = (mz_uint16)cur_సరిపోలిక_dist;
          p_LZ_సంకేతం_buf += 3;
          *pLZ_flags = (mz_uint8)((*pLZ_flags >> 1) | 0x80);

          s0 = s_tdefl_small_dist_sym[cur_సరిపోలిక_dist & 511];
          s1 = s_tdefl_large_dist_sym[cur_సరిపోలిక_dist >> 8];
          d->m_huff_లెక్క[1][(cur_సరిపోలిక_dist < 512) ? s0 : s1]++;

          d->m_huff_లెక్క[0][s_tdefl_len_sym[cur_సరిపోలిక_len - TDEFL_MIN_సరిపోలిక_LEN]]++;
        }
      }
      లేకపోతే
      {
        *p_LZ_సంకేతం_buf++ = (mz_uint8)మొదటి_trigram;
        *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
        d->m_huff_లెక్క[0][(mz_uint8)మొదటి_trigram]++;
      }

      ఒకవేళ (--అంకె_flags_ఎడమ == 0) { అంకె_flags_ఎడమ = 8; pLZ_flags = p_LZ_సంకేతం_buf++; }

      మొత్తం_lz_బైట్లు += cur_సరిపోలిక_len;
      lookahead_pos += cur_సరిపోలిక_len;
      dict_కొలత = MZ_MIN(dict_కొలత + cur_సరిపోలిక_len, TDEFL_LZ_DICT_కొలత);
      cur_pos = (cur_pos + cur_సరిపోలిక_len) & TDEFL_LZ_DICT_కొలత_ముసుగు;
      MZ_ASSERT(lookahead_కొలత >= cur_సరిపోలిక_len);
      lookahead_కొలత -= cur_సరిపోలిక_len;

      ఒకవేళ (p_LZ_సంకేతం_buf > &d->m_lz_సంకేతం_buf[TDEFL_LZ_సంకేతం_BUF_కొలత - 8])
      {
        పూర్ణాంకం n;
        d->m_lookahead_pos = lookahead_pos; d->m_lookahead_కొలత = lookahead_కొలత; d->m_dict_కొలత = dict_కొలత;
        d->m_మొత్తం_lz_బైట్లు = మొత్తం_lz_బైట్లు; d->m_p_LZ_సంకేతం_buf = p_LZ_సంకేతం_buf; d->m_pLZ_flags = pLZ_flags; d->m_అంకె_flags_ఎడమ = అంకె_flags_ఎడమ;
        ఒకవేళ ((n = tdefl_flush_ఖండం(d, 0)) != 0)
          తిరిగి (n < 0) ? MZ_FALSE : MZ_TRUE;
        మొత్తం_lz_బైట్లు = d->m_మొత్తం_lz_బైట్లు; p_LZ_సంకేతం_buf = d->m_p_LZ_సంకేతం_buf; pLZ_flags = d->m_pLZ_flags; అంకె_flags_ఎడమ = d->m_అంకె_flags_ఎడమ;
      }
    }

    అయితే (lookahead_కొలత)
    {
      mz_uint8 lit = d->m_dict[cur_pos];

      మొత్తం_lz_బైట్లు++;
      *p_LZ_సంకేతం_buf++ = lit;
      *pLZ_flags = (mz_uint8)(*pLZ_flags >> 1);
      ఒకవేళ (--అంకె_flags_ఎడమ == 0) { అంకె_flags_ఎడమ = 8; pLZ_flags = p_LZ_సంకేతం_buf++; }

      d->m_huff_లెక్క[0][lit]++;

      lookahead_pos++;
      dict_కొలత = MZ_MIN(dict_కొలత + 1, TDEFL_LZ_DICT_కొలత);
      cur_pos = (cur_pos + 1) & TDEFL_LZ_DICT_కొలత_ముసుగు;
      lookahead_కొలత--;

      ఒకవేళ (p_LZ_సంకేతం_buf > &d->m_lz_సంకేతం_buf[TDEFL_LZ_సంకేతం_BUF_కొలత - 8])
      {
        పూర్ణాంకం n;
        d->m_lookahead_pos = lookahead_pos; d->m_lookahead_కొలత = lookahead_కొలత; d->m_dict_కొలత = dict_కొలత;
        d->m_మొత్తం_lz_బైట్లు = మొత్తం_lz_బైట్లు; d->m_p_LZ_సంకేతం_buf = p_LZ_సంకేతం_buf; d->m_pLZ_flags = pLZ_flags; d->m_అంకె_flags_ఎడమ = అంకె_flags_ఎడమ;
        ఒకవేళ ((n = tdefl_flush_ఖండం(d, 0)) != 0)
          తిరిగి (n < 0) ? MZ_FALSE : MZ_TRUE;
        మొత్తం_lz_బైట్లు = d->m_మొత్తం_lz_బైట్లు; p_LZ_సంకేతం_buf = d->m_p_LZ_సంకేతం_buf; pLZ_flags = d->m_pLZ_flags; అంకె_flags_ఎడమ = d->m_అంకె_flags_ఎడమ;
      }
    }
  }

  d->m_lookahead_pos = lookahead_pos; d->m_lookahead_కొలత = lookahead_కొలత; d->m_dict_కొలత = dict_కొలత;
  d->m_మొత్తం_lz_బైట్లు = మొత్తం_lz_బైట్లు; d->m_p_LZ_సంకేతం_buf = p_LZ_సంకేతం_buf; d->m_pLZ_flags = pLZ_flags; d->m_అంకె_flags_ఎడమ = అంకె_flags_ఎడమ;
  తిరిగి MZ_TRUE;
}
#అయితే_ముగింపు // MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN

స్థిర MZ_FORCEINLINE శూన్య tdefl_రికార్డు_literal(tdefl_compressor *d, mz_uint8 lit)
{
  d->m_మొత్తం_lz_బైట్లు++;
  *d->m_p_LZ_సంకేతం_buf++ = lit;
  *d->m_pLZ_flags = (mz_uint8)(*d->m_pLZ_flags >> 1); ఒకవేళ (--d->m_అంకె_flags_ఎడమ == 0) { d->m_అంకె_flags_ఎడమ = 8; d->m_pLZ_flags = d->m_p_LZ_సంకేతం_buf++; }
  d->m_huff_లెక్క[0][lit]++;
}

స్థిర MZ_FORCEINLINE శూన్య tdefl_రికార్డు_సరిపోలిక(tdefl_compressor *d, mz_uint సరిపోలిక_len, mz_uint సరిపోలిక_dist)
{
  mz_uint32 s0, s1;

  MZ_ASSERT((సరిపోలిక_len >= TDEFL_MIN_సరిపోలిక_LEN) && (సరిపోలిక_dist >= 1) && (సరిపోలిక_dist <= TDEFL_LZ_DICT_కొలత));

  d->m_మొత్తం_lz_బైట్లు += సరిపోలిక_len;

  d->m_p_LZ_సంకేతం_buf[0] = (mz_uint8)(సరిపోలిక_len - TDEFL_MIN_సరిపోలిక_LEN);

  సరిపోలిక_dist -= 1;
  d->m_p_LZ_సంకేతం_buf[1] = (mz_uint8)(సరిపోలిక_dist & 0xFF);
  d->m_p_LZ_సంకేతం_buf[2] = (mz_uint8)(సరిపోలిక_dist >> 8); d->m_p_LZ_సంకేతం_buf += 3;

  *d->m_pLZ_flags = (mz_uint8)((*d->m_pLZ_flags >> 1) | 0x80); ఒకవేళ (--d->m_అంకె_flags_ఎడమ == 0) { d->m_అంకె_flags_ఎడమ = 8; d->m_pLZ_flags = d->m_p_LZ_సంకేతం_buf++; }

  s0 = s_tdefl_small_dist_sym[సరిపోలిక_dist & 511]; s1 = s_tdefl_large_dist_sym[(సరిపోలిక_dist >> 8) & 127];
  d->m_huff_లెక్క[1][(సరిపోలిక_dist < 512) ? s0 : s1]++;

  ఒకవేళ (సరిపోలిక_len >= TDEFL_MIN_సరిపోలిక_LEN) d->m_huff_లెక్క[0][s_tdefl_len_sym[సరిపోలిక_len - TDEFL_MIN_సరిపోలిక_LEN]]++;
}

స్థిర mz_bool tdefl_compress_సాధారణ(tdefl_compressor *d)
{
  స్థిరరాశి mz_uint8 *pSrc = d->m_pSrc; size_t src_buf_ఎడమ = d->m_src_buf_ఎడమ;
  tdefl_flush flush = d->m_flush;

  అయితే ((src_buf_ఎడమ) || ((flush) && (d->m_lookahead_కొలత)))
  {
    mz_uint len_గమ్యం_move, cur_సరిపోలిక_dist, cur_సరిపోలిక_len, cur_pos;
    // Update dictionary and hash chains. Keeps the lookahead size equal to TDEFL_MAX_MATCH_LEN.
    ఒకవేళ ((d->m_lookahead_కొలత + d->m_dict_కొలత) >= (TDEFL_MIN_సరిపోలిక_LEN - 1))
    {
      mz_uint dst_pos = (d->m_lookahead_pos + d->m_lookahead_కొలత) & TDEFL_LZ_DICT_కొలత_ముసుగు, ins_pos = d->m_lookahead_pos + d->m_lookahead_కొలత - 2;
      mz_uint hash = (d->m_dict[ins_pos & TDEFL_LZ_DICT_కొలత_ముసుగు] << TDEFL_LZ_HASH_జరుపు) ^ d->m_dict[(ins_pos + 1) & TDEFL_LZ_DICT_కొలత_ముసుగు];
      mz_uint అంకె_బైట్లు_గమ్యం_process = (mz_uint)MZ_MIN(src_buf_ఎడమ, TDEFL_MAX_సరిపోలిక_LEN - d->m_lookahead_కొలత);
      స్థిరరాశి mz_uint8 *p_Src_చివర = pSrc ? pSrc + అంకె_బైట్లు_గమ్యం_process : ఖాళీ;
      src_buf_ఎడమ -= అంకె_బైట్లు_గమ్యం_process;
      d->m_lookahead_కొలత += అంకె_బైట్లు_గమ్యం_process;
      అయితే (pSrc != p_Src_చివర)
      {
        mz_uint8 c = *pSrc++; d->m_dict[dst_pos] = c; ఒకవేళ (dst_pos < (TDEFL_MAX_సరిపోలిక_LEN - 1)) d->m_dict[TDEFL_LZ_DICT_కొలత + dst_pos] = c;
        hash = ((hash << TDEFL_LZ_HASH_జరుపు) ^ c) & (TDEFL_LZ_HASH_కొలత - 1);
        d->m_తదుపరి[ins_pos & TDEFL_LZ_DICT_కొలత_ముసుగు] = d->m_hash[hash]; d->m_hash[hash] = (mz_uint16)(ins_pos);
        dst_pos = (dst_pos + 1) & TDEFL_LZ_DICT_కొలత_ముసుగు; ins_pos++;
      }
    }
    లేకపోతే
    {
      అయితే ((src_buf_ఎడమ) && (d->m_lookahead_కొలత < TDEFL_MAX_సరిపోలిక_LEN))
      {
        mz_uint8 c = *pSrc++;
        mz_uint dst_pos = (d->m_lookahead_pos + d->m_lookahead_కొలత) & TDEFL_LZ_DICT_కొలత_ముసుగు;
        src_buf_ఎడమ--;
        d->m_dict[dst_pos] = c;
        ఒకవేళ (dst_pos < (TDEFL_MAX_సరిపోలిక_LEN - 1))
          d->m_dict[TDEFL_LZ_DICT_కొలత + dst_pos] = c;
        ఒకవేళ ((++d->m_lookahead_కొలత + d->m_dict_కొలత) >= TDEFL_MIN_సరిపోలిక_LEN)
        {
          mz_uint ins_pos = d->m_lookahead_pos + (d->m_lookahead_కొలత - 1) - 2;
          mz_uint hash = ((d->m_dict[ins_pos & TDEFL_LZ_DICT_కొలత_ముసుగు] << (TDEFL_LZ_HASH_జరుపు * 2)) ^ (d->m_dict[(ins_pos + 1) & TDEFL_LZ_DICT_కొలత_ముసుగు] << TDEFL_LZ_HASH_జరుపు) ^ c) & (TDEFL_LZ_HASH_కొలత - 1);
          d->m_తదుపరి[ins_pos & TDEFL_LZ_DICT_కొలత_ముసుగు] = d->m_hash[hash]; d->m_hash[hash] = (mz_uint16)(ins_pos);
        }
      }
    }
    d->m_dict_కొలత = MZ_MIN(TDEFL_LZ_DICT_కొలత - d->m_lookahead_కొలత, d->m_dict_కొలత);
    ఒకవేళ ((!flush) && (d->m_lookahead_కొలత < TDEFL_MAX_సరిపోలిక_LEN))
      ఆపు;

    // Simple lazy/greedy parsing state machine.
    len_గమ్యం_move = 1; cur_సరిపోలిక_dist = 0; cur_సరిపోలిక_len = d->m_saved_సరిపోలిక_len ? d->m_saved_సరిపోలిక_len : (TDEFL_MIN_సరిపోలిక_LEN - 1); cur_pos = d->m_lookahead_pos & TDEFL_LZ_DICT_కొలత_ముసుగు;
    ఒకవేళ (d->m_flags & (TDEFL_RLE_MATCHES | TDEFL_FORCE_ALL_RAW_ఖండాలు))
    {
      ఒకవేళ ((d->m_dict_కొలత) && (!(d->m_flags & TDEFL_FORCE_ALL_RAW_ఖండాలు)))
      {
        mz_uint8 c = d->m_dict[(cur_pos - 1) & TDEFL_LZ_DICT_కొలత_ముసుగు];
        cur_సరిపోలిక_len = 0; అయితే (cur_సరిపోలిక_len < d->m_lookahead_కొలత) { ఒకవేళ (d->m_dict[cur_pos + cur_సరిపోలిక_len] != c) ఆపు; cur_సరిపోలిక_len++; }
        ఒకవేళ (cur_సరిపోలిక_len < TDEFL_MIN_సరిపోలిక_LEN) cur_సరిపోలిక_len = 0; లేకపోతే cur_సరిపోలిక_dist = 1;
      }
    }
    లేకపోతే
    {
      tdefl_కనుగొను_సరిపోలిక(d, d->m_lookahead_pos, d->m_dict_కొలత, d->m_lookahead_కొలత, &cur_సరిపోలిక_dist, &cur_సరిపోలిక_len);
    }
    ఒకవేళ (((cur_సరిపోలిక_len == TDEFL_MIN_సరిపోలిక_LEN) && (cur_సరిపోలిక_dist >= 8U*1024U)) || (cur_pos == cur_సరిపోలిక_dist) || ((d->m_flags & TDEFL_FILTER_MATCHES) && (cur_సరిపోలిక_len <= 5)))
    {
      cur_సరిపోలిక_dist = cur_సరిపోలిక_len = 0;
    }
    ఒకవేళ (d->m_saved_సరిపోలిక_len)
    {
      ఒకవేళ (cur_సరిపోలిక_len > d->m_saved_సరిపోలిక_len)
      {
        tdefl_రికార్డు_literal(d, (mz_uint8)d->m_saved_lit);
        ఒకవేళ (cur_సరిపోలిక_len >= 128)
        {
          tdefl_రికార్డు_సరిపోలిక(d, cur_సరిపోలిక_len, cur_సరిపోలిక_dist);
          d->m_saved_సరిపోలిక_len = 0; len_గమ్యం_move = cur_సరిపోలిక_len;
        }
        లేకపోతే
        {
          d->m_saved_lit = d->m_dict[cur_pos]; d->m_saved_సరిపోలిక_dist = cur_సరిపోలిక_dist; d->m_saved_సరిపోలిక_len = cur_సరిపోలిక_len;
        }
      }
      లేకపోతే
      {
        tdefl_రికార్డు_సరిపోలిక(d, d->m_saved_సరిపోలిక_len, d->m_saved_సరిపోలిక_dist);
        len_గమ్యం_move = d->m_saved_సరిపోలిక_len - 1; d->m_saved_సరిపోలిక_len = 0;
      }
    }
    లేకపోతే ఒకవేళ (!cur_సరిపోలిక_dist)
      tdefl_రికార్డు_literal(d, d->m_dict[MZ_MIN(cur_pos, పరిమాణం(d->m_dict) - 1)]);
    లేకపోతే ఒకవేళ ((d->m_greedy_parsing) || (d->m_flags & TDEFL_RLE_MATCHES) || (cur_సరిపోలిక_len >= 128))
    {
      tdefl_రికార్డు_సరిపోలిక(d, cur_సరిపోలిక_len, cur_సరిపోలిక_dist);
      len_గమ్యం_move = cur_సరిపోలిక_len;
    }
    లేకపోతే
    {
      d->m_saved_lit = d->m_dict[MZ_MIN(cur_pos, పరిమాణం(d->m_dict) - 1)]; d->m_saved_సరిపోలిక_dist = cur_సరిపోలిక_dist; d->m_saved_సరిపోలిక_len = cur_సరిపోలిక_len;
    }
    // Move the lookahead forward by len_to_move bytes.
    d->m_lookahead_pos += len_గమ్యం_move;
    MZ_ASSERT(d->m_lookahead_కొలత >= len_గమ్యం_move);
    d->m_lookahead_కొలత -= len_గమ్యం_move;
    d->m_dict_కొలత = MZ_MIN(d->m_dict_కొలత + len_గమ్యం_move, TDEFL_LZ_DICT_కొలత);
    // Check if it's time to flush the current LZ codes to the internal output buffer.
    ఒకవేళ ( (d->m_p_LZ_సంకేతం_buf > &d->m_lz_సంకేతం_buf[TDEFL_LZ_సంకేతం_BUF_కొలత - 8]) ||
         ( (d->m_మొత్తం_lz_బైట్లు > 31*1024) && (((((mz_uint)(d->m_p_LZ_సంకేతం_buf - d->m_lz_సంకేతం_buf) * 115) >> 7) >= d->m_మొత్తం_lz_బైట్లు) || (d->m_flags & TDEFL_FORCE_ALL_RAW_ఖండాలు))) )
    {
      పూర్ణాంకం n;
      d->m_pSrc = pSrc; d->m_src_buf_ఎడమ = src_buf_ఎడమ;
      ఒకవేళ ((n = tdefl_flush_ఖండం(d, 0)) != 0)
        తిరిగి (n < 0) ? MZ_FALSE : MZ_TRUE;
    }
  }

  d->m_pSrc = pSrc; d->m_src_buf_ఎడమ = src_buf_ఎడమ;
  తిరిగి MZ_TRUE;
}

స్థిర tdefl_స్థితి tdefl_flush_output_బఫరు(tdefl_compressor *d)
{
  ఒకవేళ (d->m_p_లోపల_buf_కొలత)
  {
    *d->m_p_లోపల_buf_కొలత = d->m_pSrc - (స్థిరరాశి mz_uint8 *)d->m_p_లోపల_buf;
  }

  ఒకవేళ (d->m_p_బహిర్గతం_buf_కొలత)
  {
    size_t n = MZ_MIN(*d->m_p_బహిర్గతం_buf_కొలత - d->m_బహిర్గతం_buf_ofs, d->m_output_flush_మిగిలిన);
    జ్ఞాపకం_నకలు((mz_uint8 *)d->m_p_బహిర్గతం_buf + d->m_బహిర్గతం_buf_ofs, d->m_output_buf + d->m_output_flush_ofs, n);
    d->m_output_flush_ofs += (mz_uint)n;
    d->m_output_flush_మిగిలిన -= (mz_uint)n;
    d->m_బహిర్గతం_buf_ofs += n;

    *d->m_p_బహిర్గతం_buf_కొలత = d->m_బహిర్గతం_buf_ofs;
  }

  తిరిగి (d->m_ముగిసిన && !d->m_output_flush_మిగిలిన) ? TDEFL_స్థితి_పూర్తి : TDEFL_స్థితి_OKAY;
}

tdefl_స్థితి tdefl_compress(tdefl_compressor *d, స్థిరరాశి శూన్య *p_లోపల_buf, size_t *p_లోపల_buf_కొలత, శూన్య *p_బహిర్గతం_buf, size_t *p_బహిర్గతం_buf_కొలత, tdefl_flush flush)
{
  ఒకవేళ (!d)
  {
    ఒకవేళ (p_లోపల_buf_కొలత) *p_లోపల_buf_కొలత = 0;
    ఒకవేళ (p_బహిర్గతం_buf_కొలత) *p_బహిర్గతం_buf_కొలత = 0;
    తిరిగి TDEFL_స్థితి_BAD_PARAM;
  }

  d->m_p_లోపల_buf = p_లోపల_buf; d->m_p_లోపల_buf_కొలత = p_లోపల_buf_కొలత;
  d->m_p_బహిర్గతం_buf = p_బహిర్గతం_buf; d->m_p_బహిర్గతం_buf_కొలత = p_బహిర్గతం_buf_కొలత;
  d->m_pSrc = (స్థిరరాశి mz_uint8 *)(p_లోపల_buf); d->m_src_buf_ఎడమ = p_లోపల_buf_కొలత ? *p_లోపల_buf_కొలత : 0;
  d->m_బహిర్గతం_buf_ofs = 0;
  d->m_flush = flush;

  ఒకవేళ ( ((d->m_pPut_buf_func != ఖాళీ) == ((p_బహిర్గతం_buf != ఖాళీ) || (p_బహిర్గతం_buf_కొలత != ఖాళీ))) || (d->m_prev_return_స్థితి != TDEFL_స్థితి_OKAY) ||
        (d->m_కోరుతుంది_గమ్యం_ముగింపు && (flush != TDEFL_ముగింపు)) || (p_లోపల_buf_కొలత && *p_లోపల_buf_కొలత && !p_లోపల_buf) || (p_బహిర్గతం_buf_కొలత && *p_బహిర్గతం_buf_కొలత && !p_బహిర్గతం_buf) )
  {
    ఒకవేళ (p_లోపల_buf_కొలత) *p_లోపల_buf_కొలత = 0;
    ఒకవేళ (p_బహిర్గతం_buf_కొలత) *p_బహిర్గతం_buf_కొలత = 0;
    తిరిగి (d->m_prev_return_స్థితి = TDEFL_స్థితి_BAD_PARAM);
  }
  d->m_కోరుతుంది_గమ్యం_ముగింపు |= (flush == TDEFL_ముగింపు);

  ఒకవేళ ((d->m_output_flush_మిగిలిన) || (d->m_ముగిసిన))
    తిరిగి (d->m_prev_return_స్థితి = tdefl_flush_output_బఫరు(d));

#ఒకవేళ MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  ఒకవేళ (((d->m_flags & TDEFL_MAX_PROBES_ముసుగు) == 1) &&
      ((d->m_flags & TDEFL_GREEDY_PARSING_FLAG) != 0) &&
      ((d->m_flags & (TDEFL_FILTER_MATCHES | TDEFL_FORCE_ALL_RAW_ఖండాలు | TDEFL_RLE_MATCHES)) == 0))
  {
    ఒకవేళ (!tdefl_compress_fast(d))
      తిరిగి d->m_prev_return_స్థితి;
  }
  లేకపోతే
#అయితే_ముగింపు // #if MINIZ_USE_UNALIGNED_LOADS_AND_STORES && MINIZ_LITTLE_ENDIAN
  {
    ఒకవేళ (!tdefl_compress_సాధారణ(d))
      తిరిగి d->m_prev_return_స్థితి;
  }

  ఒకవేళ ((d->m_flags & (TDEFL_WRITE_ZLIB_శీర్షిక | TDEFL_COMPUTE_ADLER32)) && (p_లోపల_buf))
    d->m_adler32 = (mz_uint32)mz_adler32(d->m_adler32, (స్థిరరాశి mz_uint8 *)p_లోపల_buf, d->m_pSrc - (స్థిరరాశి mz_uint8 *)p_లోపల_buf);

  ఒకవేళ ((flush) && (!d->m_lookahead_కొలత) && (!d->m_src_buf_ఎడమ) && (!d->m_output_flush_మిగిలిన))
  {
    ఒకవేళ (tdefl_flush_ఖండం(d, flush) < 0)
      తిరిగి d->m_prev_return_స్థితి;
    d->m_ముగిసిన = (flush == TDEFL_ముగింపు);
    ఒకవేళ (flush == TDEFL_నిండిన_FLUSH) { MZ_CLEAR_ARR(d->m_hash); MZ_CLEAR_ARR(d->m_తదుపరి); d->m_dict_కొలత = 0; }
  }

  తిరిగి (d->m_prev_return_స్థితి = tdefl_flush_output_బఫరు(d));
}

tdefl_స్థితి tdefl_compress_బఫరు(tdefl_compressor *d, స్థిరరాశి శూన్య *p_లోపల_buf, size_t లోపల_buf_కొలత, tdefl_flush flush)
{
  MZ_ASSERT(d->m_pPut_buf_func); తిరిగి tdefl_compress(d, p_లోపల_buf, &లోపల_buf_కొలత, ఖాళీ, ఖాళీ, flush);
}

tdefl_స్థితి tdefl_init(tdefl_compressor *d, tdefl_put_buf_func_ptr pPut_buf_func, శూన్య *pPut_buf_user, పూర్ణాంకం flags)
{
  d->m_pPut_buf_func = pPut_buf_func; d->m_pPut_buf_user = pPut_buf_user;
  d->m_flags = (mz_uint)(flags); d->m_max_probes[0] = 1 + ((flags & 0xFFF) + 2) / 3; d->m_greedy_parsing = (flags & TDEFL_GREEDY_PARSING_FLAG) != 0;
  d->m_max_probes[1] = 1 + (((flags & 0xFFF) >> 2) + 2) / 3;
  ఒకవేళ (!(flags & TDEFL_NONDETERMINISTIC_PARSING_FLAG)) MZ_CLEAR_ARR(d->m_hash);
  d->m_lookahead_pos = d->m_lookahead_కొలత = d->m_dict_కొలత = d->m_మొత్తం_lz_బైట్లు = d->m_lz_సంకేతం_buf_dict_pos = d->m_బిట్లు_లోపల = 0;
  d->m_output_flush_ofs = d->m_output_flush_మిగిలిన = d->m_ముగిసిన = d->m_ఖండం_సూచీ = d->m_బిట్టు_బఫరు = d->m_కోరుతుంది_గమ్యం_ముగింపు = 0;
  d->m_p_LZ_సంకేతం_buf = d->m_lz_సంకేతం_buf + 1; d->m_pLZ_flags = d->m_lz_సంకేతం_buf; d->m_అంకె_flags_ఎడమ = 8;
  d->m_pOutput_buf = d->m_output_buf; d->m_p_Output_buf_చివర = d->m_output_buf; d->m_prev_return_స్థితి = TDEFL_స్థితి_OKAY;
  d->m_saved_సరిపోలిక_dist = d->m_saved_సరిపోలిక_len = d->m_saved_lit = 0; d->m_adler32 = 1;
  d->m_p_లోపల_buf = ఖాళీ; d->m_p_బహిర్గతం_buf = ఖాళీ;
  d->m_p_లోపల_buf_కొలత = ఖాళీ; d->m_p_బహిర్గతం_buf_కొలత = ఖాళీ;
  d->m_flush = TDEFL_NO_FLUSH; d->m_pSrc = ఖాళీ; d->m_src_buf_ఎడమ = 0; d->m_బహిర్గతం_buf_ofs = 0;
  memset(&d->m_huff_లెక్క[0][0], 0, పరిమాణం(d->m_huff_లెక్క[0][0]) * TDEFL_MAX_HUFF_SYMBOLS_0);
  memset(&d->m_huff_లెక్క[1][0], 0, పరిమాణం(d->m_huff_లెక్క[1][0]) * TDEFL_MAX_HUFF_SYMBOLS_1);
  తిరిగి TDEFL_స్థితి_OKAY;
}

#నిర్వచితం_కాకపోతే MINIZ_SDL_NOUNUSED
tdefl_స్థితి tdefl_get_prev_return_స్థితి(tdefl_compressor *d)
{
  తిరిగి d->m_prev_return_స్థితి;
}

mz_uint32 tdefl_get_adler32(tdefl_compressor *d)
{
  తిరిగి d->m_adler32;
}

mz_bool tdefl_compress_mem_గమ్యం_output(స్థిరరాశి శూన్య *pBuf, size_t buf_len, tdefl_put_buf_func_ptr pPut_buf_func, శూన్య *pPut_buf_user, పూర్ణాంకం flags)
{
  tdefl_compressor *pComp; mz_bool succeeded; ఒకవేళ (((buf_len) && (!pBuf)) || (!pPut_buf_func)) తిరిగి MZ_FALSE;
  pComp = (tdefl_compressor*)MZ_MALLOC(పరిమాణం(tdefl_compressor)); ఒకవేళ (!pComp) తిరిగి MZ_FALSE;
  succeeded = (tdefl_init(pComp, pPut_buf_func, pPut_buf_user, flags) == TDEFL_స్థితి_OKAY);
  succeeded = succeeded && (tdefl_compress_బఫరు(pComp, pBuf, buf_len, TDEFL_ముగింపు) == TDEFL_స్థితి_పూర్తి);
  MZ_FREE(pComp); తిరిగి succeeded;
}
#అయితే_ముగింపు /* MINIZ_SDL_NOUNUSED */

రకనిర్వచనం నిర్మాణం
{
  size_t m_కొలత, m_సామర్థ్యం;
  mz_uint8 *m_pBuf;
  mz_bool m_expandable;
} tdefl_output_బఫరు;

స్థిర mz_bool tdefl_output_బఫరు_putter(స్థిరరాశి శూన్య *pBuf, పూర్ణాంకం len, శూన్య *pUser)
{
  tdefl_output_బఫరు *p = (tdefl_output_బఫరు *)pUser;
  size_t new_కొలత = p->m_కొలత + len;
  ఒకవేళ (new_కొలత > p->m_సామర్థ్యం)
  {
    size_t new_సామర్థ్యం = p->m_సామర్థ్యం; mz_uint8 *pNew_buf; ఒకవేళ (!p->m_expandable) తిరిగి MZ_FALSE;
    చేయి { new_సామర్థ్యం = MZ_MAX(128U, new_సామర్థ్యం << 1U); } అయితే (new_కొలత > new_సామర్థ్యం);
    pNew_buf = (mz_uint8*)MZ_REALLOC(p->m_pBuf, new_సామర్థ్యం); ఒకవేళ (!pNew_buf) తిరిగి MZ_FALSE;
    p->m_pBuf = pNew_buf; p->m_సామర్థ్యం = new_సామర్థ్యం;
  }
  జ్ఞాపకం_నకలు((mz_uint8*)p->m_pBuf + p->m_కొలత, pBuf, len); p->m_కొలత = new_కొలత;
  తిరిగి MZ_TRUE;
}

#నిర్వచితం_కాకపోతే MINIZ_SDL_NOUNUSED
శూన్య *tdefl_compress_mem_గమ్యం_కుప్ప(స్థిరరాశి శూన్య *pSrc_buf, size_t src_buf_len, size_t *p_బహిర్గతం_len, పూర్ణాంకం flags)
{
  tdefl_output_బఫరు బహిర్గతం_buf; MZ_CLEAR_OBJ(బహిర్గతం_buf);
  ఒకవేళ (!p_బహిర్గతం_len) తిరిగి MZ_FALSE; లేకపోతే *p_బహిర్గతం_len = 0;
  బహిర్గతం_buf.m_expandable = MZ_TRUE;
  ఒకవేళ (!tdefl_compress_mem_గమ్యం_output(pSrc_buf, src_buf_len, tdefl_output_బఫరు_putter, &బహిర్గతం_buf, flags)) తిరిగి ఖాళీ;
  *p_బహిర్గతం_len = బహిర్గతం_buf.m_కొలత; తిరిగి బహిర్గతం_buf.m_pBuf;
}

size_t tdefl_compress_mem_గమ్యం_mem(శూన్య *p_బహిర్గతం_buf, size_t బహిర్గతం_buf_len, స్థిరరాశి శూన్య *pSrc_buf, size_t src_buf_len, పూర్ణాంకం flags)
{
  tdefl_output_బఫరు బహిర్గతం_buf; MZ_CLEAR_OBJ(బహిర్గతం_buf);
  ఒకవేళ (!p_బహిర్గతం_buf) తిరిగి 0;
  బహిర్గతం_buf.m_pBuf = (mz_uint8*)p_బహిర్గతం_buf; బహిర్గతం_buf.m_సామర్థ్యం = బహిర్గతం_buf_len;
  ఒకవేళ (!tdefl_compress_mem_గమ్యం_output(pSrc_buf, src_buf_len, tdefl_output_బఫరు_putter, &బహిర్గతం_buf, flags)) తిరిగి 0;
  తిరిగి బహిర్గతం_buf.m_కొలత;
}
#అయితే_ముగింపు /* MINIZ_SDL_NOUNUSED */

#నిర్వచితం_కాకపోతే MINIZ_NO_ZLIB_APIS
స్థిర స్థిరరాశి mz_uint s_tdefl_అంకె_probes[11] = { 0, 1, 6, 32,  16, 32, 128, 256,  512, 768, 1500 };

// level may actually range from [0,10] (10 is a "hidden" max level, where we want a bit more compression and it's fine if throughput to fall off a cliff on some files).
mz_uint tdefl_create_comp_flags_from_zip_params(పూర్ణాంకం level, పూర్ణాంకం కిటికీ_బిట్లు, పూర్ణాంకం strategy)
{
  mz_uint comp_flags = s_tdefl_అంకె_probes[(level >= 0) ? MZ_MIN(10, level) : MZ_DEFAULT_LEVEL] | ((level <= 3) ? TDEFL_GREEDY_PARSING_FLAG : 0);
  ఒకవేళ (కిటికీ_బిట్లు > 0) comp_flags |= TDEFL_WRITE_ZLIB_శీర్షిక;

  ఒకవేళ (!level) comp_flags |= TDEFL_FORCE_ALL_RAW_ఖండాలు;
  లేకపోతే ఒకవేళ (strategy == MZ_FILTERED) comp_flags |= TDEFL_FILTER_MATCHES;
  లేకపోతే ఒకవేళ (strategy == MZ_HUFFMAN_ONLY) comp_flags &= ~TDEFL_MAX_PROBES_ముసుగు;
  లేకపోతే ఒకవేళ (strategy == MZ_FIXED) comp_flags |= TDEFL_FORCE_ALL_STATIC_ఖండాలు;
  లేకపోతే ఒకవేళ (strategy == MZ_RLE) comp_flags |= TDEFL_RLE_MATCHES;

  తిరిగి comp_flags;
}
#అయితే_ముగింపు //MINIZ_NO_ZLIB_APIS

#నిర్వచితమైతే _MSC_VER
#సూచన warning (నెట్టు)
#సూచన warning (disable:4204) // nonstandard extension used : non-constant aggregate initializer (also supported by GNU C and C99, so no big deal)
#అయితే_ముగింపు

// Simple PNG writer function by Alex Evans, 2011. Released into the public domain: https://gist.github.com/908299, more context at
// http://altdevblogaday.org/2011/04/06/a-smaller-jpg-encoder/.
// This is actually a modification of Alex's original code so PNG files generated by this function pass pngcheck.
MINIZ_STATIC శూన్య *tdefl_write_image_గమ్యం_png_file_లోపల_జ్ఞాపకం_ex(స్థిరరాశి శూన్య *pImage, పూర్ణాంకం w, పూర్ణాంకం h, పూర్ణాంకం అంకె_chans, పూర్ణాంకం bpl, size_t *p_Len_బహిర్గతం, mz_uint level, mz_bool flip, mz_uint8 *plte, పూర్ణాంకం plte_కొలత, mz_uint8 *trns, పూర్ణాంకం trns_కొలత)
{
  // Using a local copy of this array here in case MINIZ_NO_ZLIB_APIS was defined.
  స్థిర స్థిరరాశి mz_uint s_tdefl_png_అంకె_probes[11] = { 0, 1, 6, 32,  16, 32, 128, 256,  512, 768, 1500 };
  tdefl_compressor *pComp = (tdefl_compressor *)MZ_MALLOC(పరిమాణం(tdefl_compressor)); tdefl_output_బఫరు బహిర్గతం_buf; పూర్ణాంకం i, y, z = 0; mz_uint32 c; *p_Len_బహిర్గతం = 0; size_t దత్తాంశం_ప్రారంభం, దత్తాంశం_కొలత_3;
  ఒకవేళ (!pComp) తిరిగి ఖాళీ;
  MZ_CLEAR_OBJ(బహిర్గతం_buf); బహిర్గతం_buf.m_expandable = MZ_TRUE;
  బహిర్గతం_buf.m_సామర్థ్యం = 57+MZ_MAX(64, (1+w*అంకె_chans)*h);
  ఒకవేళ (plte_కొలత > 0)
    బహిర్గతం_buf.m_సామర్థ్యం += 12+plte_కొలత;
  ఒకవేళ (trns_కొలత > 0)
    బహిర్గతం_buf.m_సామర్థ్యం += 12+trns_కొలత;
  ఒకవేళ (ఖాళీ == (బహిర్గతం_buf.m_pBuf = (mz_uint8*)MZ_MALLOC(బహిర్గతం_buf.m_సామర్థ్యం))) { MZ_FREE(pComp); తిరిగి ఖాళీ; }
  // write header
  {
    స్థిర స్థిరరాశి mz_uint8 chans[] = {0x00, 0x00, 0x04, 0x02, 0x06};

    mz_uint8 pnghdr[33]={ 0x89,0x50,0x4e,0x47,0x0d,0x0a,0x1a,0x0a,
                          0x00,0x00,0x00,0x0d,0x49,0x48,0x44,0x52,
                          0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                          0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

    pnghdr[18] = (mz_uint8)(w>>8);
    pnghdr[19] = (mz_uint8)(w>>0);

    pnghdr[22] = (mz_uint8)(h>>8);
    pnghdr[23] = (mz_uint8)(h>>0);

    ఒకవేళ (అంకె_chans == 1 && plte_కొలత > 0)
      pnghdr[25] = 3;
    లేకపోతే
      pnghdr[25] = (chans[అంకె_chans]);

    c = (mz_uint32)mz_చక్రీయ_తనిఖీ_32(MZ_చక్రీయ_తనిఖీ_32_INIT,pnghdr+12,17);
    కొరకు (i=0; i<4; ++i, c<<=8) ((mz_uint8*)(pnghdr+29))[i] = (mz_uint8)(c>>24);
    ఒకవేళ (!tdefl_output_బఫరు_putter(pnghdr, పరిమాణం(pnghdr), &బహిర్గతం_buf)) { *p_Len_బహిర్గతం = 0; MZ_FREE(pComp); MZ_FREE(బహిర్గతం_buf.m_pBuf); తిరిగి ఖాళీ; }
  }
  // write PLTE chunk
  ఒకవేళ (plte_కొలత > 0)
  {
    mz_uint8 hdr[8]={0x00,0x00,0x00,0x00,0x50,0x4c,0x54,0x45};

    hdr[0] = (mz_uint8)(plte_కొలత>>24);
    hdr[1] = (mz_uint8)(plte_కొలత>>16);
    hdr[2] = (mz_uint8)(plte_కొలత>> 8);
    hdr[3] = (mz_uint8)(plte_కొలత>> 0);
    ఒకవేళ (!tdefl_output_బఫరు_putter(hdr, పరిమాణం(hdr), &బహిర్గతం_buf)) { *p_Len_బహిర్గతం = 0; MZ_FREE(pComp); MZ_FREE(బహిర్గతం_buf.m_pBuf); తిరిగి ఖాళీ; }
    దత్తాంశం_ప్రారంభం = బహిర్గతం_buf.m_కొలత;
    ఒకవేళ (!tdefl_output_బఫరు_putter(plte, plte_కొలత, &బహిర్గతం_buf)) { *p_Len_బహిర్గతం = 0; MZ_FREE(pComp); MZ_FREE(బహిర్గతం_buf.m_pBuf); తిరిగి ఖాళీ; }
    ఒకవేళ (!tdefl_output_బఫరు_putter("\0\0\0\0", 4, &బహిర్గతం_buf)) { *p_Len_బహిర్గతం = 0; MZ_FREE(pComp); MZ_FREE(బహిర్గతం_buf.m_pBuf); తిరిగి ఖాళీ; }
    c = (mz_uint32)mz_చక్రీయ_తనిఖీ_32(MZ_చక్రీయ_తనిఖీ_32_INIT,బహిర్గతం_buf.m_pBuf+దత్తాంశం_ప్రారంభం-4, plte_కొలత+4);
    కొరకు (i=0; i<4; ++i, c<<=8) (బహిర్గతం_buf.m_pBuf+బహిర్గతం_buf.m_కొలత-4)[i] = (mz_uint8)(c >> 24);
  }
  // write tRNS chunk
  ఒకవేళ (trns_కొలత > 0)
  {
    mz_uint8 hdr[8]={0x00,0x00,0x00,0x00,0x74,0x52,0x4E,0x53};

    hdr[0] = (mz_uint8)(trns_కొలత>>24);
    hdr[1] = (mz_uint8)(trns_కొలత>>16);
    hdr[2] = (mz_uint8)(trns_కొలత>> 8);
    hdr[3] = (mz_uint8)(trns_కొలత>> 0);
    ఒకవేళ (!tdefl_output_బఫరు_putter(hdr, పరిమాణం(hdr), &బహిర్గతం_buf)) { *p_Len_బహిర్గతం = 0; MZ_FREE(pComp); MZ_FREE(బహిర్గతం_buf.m_pBuf); తిరిగి ఖాళీ; }
    దత్తాంశం_ప్రారంభం = బహిర్గతం_buf.m_కొలత;
    ఒకవేళ (!tdefl_output_బఫరు_putter(trns, trns_కొలత, &బహిర్గతం_buf)) { *p_Len_బహిర్గతం = 0; MZ_FREE(pComp); MZ_FREE(బహిర్గతం_buf.m_pBuf); తిరిగి ఖాళీ; }
    ఒకవేళ (!tdefl_output_బఫరు_putter("\0\0\0\0", 4, &బహిర్గతం_buf)) { *p_Len_బహిర్గతం = 0; MZ_FREE(pComp); MZ_FREE(బహిర్గతం_buf.m_pBuf); తిరిగి ఖాళీ; }
    c = (mz_uint32)mz_చక్రీయ_తనిఖీ_32(MZ_చక్రీయ_తనిఖీ_32_INIT,బహిర్గతం_buf.m_pBuf+దత్తాంశం_ప్రారంభం-4, trns_కొలత+4);
    కొరకు (i=0; i<4; ++i, c<<=8) (బహిర్గతం_buf.m_pBuf+బహిర్గతం_buf.m_కొలత-4)[i] = (mz_uint8)(c >> 24);
  }
  // write IDAT chunk
  ఒకవేళ (!tdefl_output_బఫరు_putter("\0\0\0\0\x49\x44\x41\x54", 8, &బహిర్గతం_buf)) { *p_Len_బహిర్గతం = 0; MZ_FREE(pComp); MZ_FREE(బహిర్గతం_buf.m_pBuf); తిరిగి ఖాళీ; }
  దత్తాంశం_ప్రారంభం = బహిర్గతం_buf.m_కొలత;
  // compress image data
  tdefl_init(pComp, tdefl_output_బఫరు_putter, &బహిర్గతం_buf, s_tdefl_png_అంకె_probes[MZ_MIN(10, level)] | TDEFL_WRITE_ZLIB_శీర్షిక);
  కొరకు (y = 0; y < h; ++y) { tdefl_compress_బఫరు(pComp, &z, 1, TDEFL_NO_FLUSH); tdefl_compress_బఫరు(pComp, (mz_uint8*)pImage + (flip ? (h - 1 - y) : y) * bpl, w * అంకె_chans, TDEFL_NO_FLUSH); }
  ఒకవేళ (tdefl_compress_బఫరు(pComp, ఖాళీ, 0, TDEFL_ముగింపు) != TDEFL_స్థితి_పూర్తి) { MZ_FREE(pComp); MZ_FREE(బహిర్గతం_buf.m_pBuf); తిరిగి ఖాళీ; }
  // write IDAT size
  దత్తాంశం_కొలత_3 = బహిర్గతం_buf.m_కొలత-దత్తాంశం_ప్రారంభం;
  (బహిర్గతం_buf.m_pBuf+దత్తాంశం_ప్రారంభం-8)[0] = (mz_uint8)(దత్తాంశం_కొలత_3>>24);
  (బహిర్గతం_buf.m_pBuf+దత్తాంశం_ప్రారంభం-8)[1] = (mz_uint8)(దత్తాంశం_కొలత_3>>16);
  (బహిర్గతం_buf.m_pBuf+దత్తాంశం_ప్రారంభం-8)[2] = (mz_uint8)(దత్తాంశం_కొలత_3>> 8);
  (బహిర్గతం_buf.m_pBuf+దత్తాంశం_ప్రారంభం-8)[3] = (mz_uint8)(దత్తాంశం_కొలత_3>> 0);
  // write footer (IDAT CRC-32, followed by IEND chunk)
  ఒకవేళ (!tdefl_output_బఫరు_putter("\0\0\0\0\0\0\0\0\x49\x45\x4e\x44\xae\x42\x60\x82", 16, &బహిర్గతం_buf)) { *p_Len_బహిర్గతం = 0; MZ_FREE(pComp); MZ_FREE(బహిర్గతం_buf.m_pBuf); తిరిగి ఖాళీ; }
  c = (mz_uint32)mz_చక్రీయ_తనిఖీ_32(MZ_చక్రీయ_తనిఖీ_32_INIT,బహిర్గతం_buf.m_pBuf+దత్తాంశం_ప్రారంభం-4, దత్తాంశం_కొలత_3+4);
  కొరకు (i=0; i<4; ++i, c<<=8) (బహిర్గతం_buf.m_pBuf+బహిర్గతం_buf.m_కొలత-16)[i] = (mz_uint8)(c >> 24);
  // compute final size of file, grab compressed data buffer and return
  *p_Len_బహిర్గతం = బహిర్గతం_buf.m_కొలత;
  MZ_FREE(pComp);
  తిరిగి బహిర్గతం_buf.m_pBuf;
}
#నిర్వచితం_కాకపోతే MINIZ_SDL_NOUNUSED
MINIZ_STATIC శూన్య *tdefl_write_image_గమ్యం_png_file_లోపల_జ్ఞాపకం(స్థిరరాశి శూన్య *pImage, పూర్ణాంకం w, పూర్ణాంకం h, పూర్ణాంకం అంకె_chans, పూర్ణాంకం bpl, size_t *p_Len_బహిర్గతం)
{
  // Level 6 corresponds to TDEFL_DEFAULT_MAX_PROBES or MZ_DEFAULT_LEVEL (but we can't depend on MZ_DEFAULT_LEVEL being available in case the zlib API's where #defined out)
  తిరిగి tdefl_write_image_గమ్యం_png_file_లోపల_జ్ఞాపకం_ex(pImage, w, h, అంకె_chans, bpl, p_Len_బహిర్గతం, 6, MZ_FALSE, ఖాళీ, 0, ఖాళీ, 0);
}
#అయితే_ముగింపు

#నిర్వచితమైతే _MSC_VER
#సూచన warning (తీయి)
#అయితే_ముగింపు
#అయితే_ముగింపు /*#ifndef MINIZ_NO_DEFLATE_APIS*/

// ------------------- .ZIP archive reading

#నిర్వచితం_కాకపోతే MINIZ_NO_ARCHIVE_APIS

#నిర్వచితమైతే MINIZ_NO_STDIO
  #నిర్వచించు MZ_FILE శూన్య *
#లేకపోతే
  #అన్తర్భావ <stdio.h>
  #అన్తర్భావ <sys/stat.h>

  #ఒకవేళ defined(_MSC_VER) || defined(__MINGW64__)
    స్థిర FILE *mz_fopen(స్థిరరాశి అక్షరం *pFilename, స్థిరరాశి అక్షరం *p_బహుళకం)
    {
      FILE* pFile = ఖాళీ;
      fopen_s(&pFile, pFilename, p_బహుళకం);
      తిరిగి pFile;
    }
    స్థిర FILE *mz_freopen(స్థిరరాశి అక్షరం *p_మార్గం, స్థిరరాశి అక్షరం *p_బహుళకం, FILE *p_ప్రవాహం)
    {
      FILE* pFile = ఖాళీ;
      ఒకవేళ (freopen_s(&pFile, p_మార్గం, p_బహుళకం, p_ప్రవాహం))
        తిరిగి ఖాళీ;
      తిరిగి pFile;
    }
    #నిర్వచితం_కాకపోతే MINIZ_NO_సమయం
      #అన్తర్భావ <sys/utime.h>
    #అయితే_ముగింపు
    #నిర్వచించు MZ_FILE FILE
    #నిర్వచించు MZ_FOPEN mz_fopen
    #నిర్వచించు MZ_FCLOSE fclose
    #నిర్వచించు MZ_FREAD fread
    #నిర్వచించు MZ_FWRITE fwrite
    #నిర్వచించు MZ_FTELL64 _ftelli64
    #నిర్వచించు MZ_FSEEK64 _fseeki64
    #నిర్వచించు MZ_FILE_STAT_STRUCT _stat
    #నిర్వచించు MZ_FILE_STAT _stat
    #నిర్వచించు MZ_FFLUSH fflush
    #నిర్వచించు MZ_FREOPEN mz_freopen
    #నిర్వచించు MZ_DELETE_FILE remove
  #లేదావేళ defined(__MINGW32__)
    #నిర్వచితం_కాకపోతే MINIZ_NO_సమయం
      #అన్తర్భావ <sys/utime.h>
    #అయితే_ముగింపు
    #నిర్వచించు MZ_FILE FILE
    #నిర్వచించు MZ_FOPEN(f, m) fopen(f, m)
    #నిర్వచించు MZ_FCLOSE fclose
    #నిర్వచించు MZ_FREAD fread
    #నిర్వచించు MZ_FWRITE fwrite
    #నిర్వచించు MZ_FTELL64 ftello64
    #నిర్వచించు MZ_FSEEK64 fseeko64
    #నిర్వచించు MZ_FILE_STAT_STRUCT _stat
    #నిర్వచించు MZ_FILE_STAT _stat
    #నిర్వచించు MZ_FFLUSH fflush
    #నిర్వచించు MZ_FREOPEN(f, m, s) freopen(f, m, s)
    #నిర్వచించు MZ_DELETE_FILE remove
  #లేదావేళ defined(__TINYC__)
    #నిర్వచితం_కాకపోతే MINIZ_NO_సమయం
      #అన్తర్భావ <sys/utime.h>
    #అయితే_ముగింపు
    #నిర్వచించు MZ_FILE FILE
    #నిర్వచించు MZ_FOPEN(f, m) fopen(f, m)
    #నిర్వచించు MZ_FCLOSE fclose
    #నిర్వచించు MZ_FREAD fread
    #నిర్వచించు MZ_FWRITE fwrite
    #నిర్వచించు MZ_FTELL64 ftell
    #నిర్వచించు MZ_FSEEK64 fseek
    #నిర్వచించు MZ_FILE_STAT_STRUCT stat
    #నిర్వచించు MZ_FILE_STAT stat
    #నిర్వచించు MZ_FFLUSH fflush
    #నిర్వచించు MZ_FREOPEN(f, m, s) freopen(f, m, s)
    #నిర్వచించు MZ_DELETE_FILE remove
  #లేదావేళ defined(__GNUC__) && LARGEFILE64_ఆధారం
    #నిర్వచితం_కాకపోతే MINIZ_NO_సమయం
      #అన్తర్భావ <utime.h>
    #అయితే_ముగింపు
    #నిర్వచించు MZ_FILE FILE
    #నిర్వచించు MZ_FOPEN(f, m) fopen64(f, m)
    #నిర్వచించు MZ_FCLOSE fclose
    #నిర్వచించు MZ_FREAD fread
    #నిర్వచించు MZ_FWRITE fwrite
    #నిర్వచించు MZ_FTELL64 ftello64
    #నిర్వచించు MZ_FSEEK64 fseeko64
    #నిర్వచించు MZ_FILE_STAT_STRUCT stat64
    #నిర్వచించు MZ_FILE_STAT stat64
    #నిర్వచించు MZ_FFLUSH fflush
    #నిర్వచించు MZ_FREOPEN(p, m, s) freopen64(p, m, s)
    #నిర్వచించు MZ_DELETE_FILE remove
  #లేకపోతే
    #నిర్వచితం_కాకపోతే MINIZ_NO_సమయం
      #అన్తర్భావ <utime.h>
    #అయితే_ముగింపు
    #నిర్వచించు MZ_FILE FILE
    #నిర్వచించు MZ_FOPEN(f, m) fopen(f, m)
    #నిర్వచించు MZ_FCLOSE fclose
    #నిర్వచించు MZ_FREAD fread
    #నిర్వచించు MZ_FWRITE fwrite
    #నిర్వచించు MZ_FTELL64 ftello
    #నిర్వచించు MZ_FSEEK64 fseeko
    #నిర్వచించు MZ_FILE_STAT_STRUCT stat
    #నిర్వచించు MZ_FILE_STAT stat
    #నిర్వచించు MZ_FFLUSH fflush
    #నిర్వచించు MZ_FREOPEN(f, m, s) freopen(f, m, s)
    #నిర్వచించు MZ_DELETE_FILE remove
  #అయితే_ముగింపు // #ifdef _MSC_VER
#అయితే_ముగింపు // #ifdef MINIZ_NO_STDIO

#నిర్వచించు MZ_TOLOWER(c) ((((c) >= 'A') && ((c) <= 'Z')) ? ((c) - 'A' + 'a') : (c))

// Various ZIP archive enums. To completely avoid cross platform compiler alignment and platform endian issues, miniz.c doesn't use structs for any of this stuff.
గణన
{
  // ZIP archive identifiers and record sizes
  MZ_ZIP_చివర_యొక్క_CENTRAL_DIR_శీర్షిక_SIG = 0x06054b50, MZ_ZIP_CENTRAL_DIR_శీర్షిక_SIG = 0x02014b50, MZ_ZIP_LOCAL_DIR_శీర్షిక_SIG = 0x04034b50,
  MZ_ZIP_LOCAL_DIR_శీర్షిక_కొలత = 30, MZ_ZIP_CENTRAL_DIR_శీర్షిక_కొలత = 46, MZ_ZIP_చివర_యొక్క_CENTRAL_DIR_శీర్షిక_కొలత = 22,
  // Central directory header record offsets
  MZ_ZIP_CDH_SIG_OFS = 0, MZ_ZIP_CDH_సంస్కరణ_MADE_BY_OFS = 4, MZ_ZIP_CDH_సంస్కరణ_NEEDED_OFS = 6, MZ_ZIP_CDH_బిట్టు_FLAG_OFS = 8,
  MZ_ZIP_CDH_పద్ధతి_OFS = 10, MZ_ZIP_CDH_FILE_సమయం_OFS = 12, MZ_ZIP_CDH_FILE_DATE_OFS = 14, MZ_ZIP_CDH_చక్రీయ_తనిఖీ_32_OFS = 16,
  MZ_ZIP_CDH_COMPRESSED_కొలత_OFS = 20, MZ_ZIP_CDH_DECOMPRESSED_కొలత_OFS = 24, MZ_ZIP_CDH_FILENAME_LEN_OFS = 28, MZ_ZIP_CDH_EXTRA_LEN_OFS = 30,
  MZ_ZIP_CDH_COMMENT_LEN_OFS = 32, MZ_ZIP_CDH_DISK_ప్రారంభం_OFS = 34, MZ_ZIP_CDH_అంతర్గత_ATTR_OFS = 36, MZ_ZIP_CDH_EXTERNAL_ATTR_OFS = 38, MZ_ZIP_CDH_LOCAL_శీర్షిక_OFS = 42,
  // Local directory header offsets
  MZ_ZIP_LDH_SIG_OFS = 0, MZ_ZIP_LDH_సంస్కరణ_NEEDED_OFS = 4, MZ_ZIP_LDH_బిట్టు_FLAG_OFS = 6, MZ_ZIP_LDH_పద్ధతి_OFS = 8, MZ_ZIP_LDH_FILE_సమయం_OFS = 10,
  MZ_ZIP_LDH_FILE_DATE_OFS = 12, MZ_ZIP_LDH_చక్రీయ_తనిఖీ_32_OFS = 14, MZ_ZIP_LDH_COMPRESSED_కొలత_OFS = 18, MZ_ZIP_LDH_DECOMPRESSED_కొలత_OFS = 22,
  MZ_ZIP_LDH_FILENAME_LEN_OFS = 26, MZ_ZIP_LDH_EXTRA_LEN_OFS = 28,
  // End of central directory offsets
  MZ_ZIP_ECDH_SIG_OFS = 0, MZ_ZIP_ECDH_అంకె_THIS_DISK_OFS = 4, MZ_ZIP_ECDH_అంకె_DISK_CDIR_OFS = 6, MZ_ZIP_ECDH_CDIR_అంకె_ENTRIES_ON_DISK_OFS = 8,
  MZ_ZIP_ECDH_CDIR_మొత్తం_ENTRIES_OFS = 10, MZ_ZIP_ECDH_CDIR_కొలత_OFS = 12, MZ_ZIP_ECDH_CDIR_OFS_OFS = 16, MZ_ZIP_ECDH_COMMENT_కొలత_OFS = 20,
};

రకనిర్వచనం నిర్మాణం
{
  శూన్య *m_p;
  size_t m_కొలత, m_సామర్థ్యం;
  mz_uint m_element_కొలత;
} mz_zip_array;

నిర్మాణం mz_zip_అంతర్గత_state_ట్యాగ్
{
  mz_zip_array m_central_dir;
  mz_zip_array m_central_dir_offsets;
  mz_zip_array m_sorted_central_dir_offsets;
  MZ_FILE *m_pFile;
  శూన్య *m_pMem;
  size_t m_mem_కొలత;
  size_t m_mem_సామర్థ్యం;
};

#నిర్వచించు MZ_ZIP_ARRAY_సమితి_ELEMENT_కొలత(array_ptr, element_కొలత) (array_ptr)->m_element_కొలత = element_కొలత
#నిర్వచించు MZ_ZIP_ARRAY_ELEMENT(array_ptr, element_type, సూచీ) ((element_type *)((array_ptr)->m_p))[సూచీ]

స్థిర MZ_FORCEINLINE శూన్య mz_zip_array_clear(mz_zip_archive *pZip, mz_zip_array *pArray)
{
  pZip->m_pFree(pZip->m_pAlloc_opaque, pArray->m_p);
  memset(pArray, 0, పరిమాణం(mz_zip_array));
}

స్థిర mz_bool mz_zip_array_ensure_సామర్థ్యం(mz_zip_archive *pZip, mz_zip_array *pArray, size_t min_new_సామర్థ్యం, mz_uint growing)
{
  శూన్య *pNew_p; size_t new_సామర్థ్యం = min_new_సామర్థ్యం; MZ_ASSERT(pArray->m_element_కొలత); ఒకవేళ (pArray->m_సామర్థ్యం >= min_new_సామర్థ్యం) తిరిగి MZ_TRUE;
  ఒకవేళ (growing) { new_సామర్థ్యం = MZ_MAX(1, pArray->m_సామర్థ్యం); అయితే (new_సామర్థ్యం < min_new_సామర్థ్యం) new_సామర్థ్యం *= 2; }
  ఒకవేళ (ఖాళీ == (pNew_p = pZip->m_pRealloc(pZip->m_pAlloc_opaque, pArray->m_p, pArray->m_element_కొలత, new_సామర్థ్యం))) తిరిగి MZ_FALSE;
  pArray->m_p = pNew_p; pArray->m_సామర్థ్యం = new_సామర్థ్యం;
  తిరిగి MZ_TRUE;
}

స్థిర MZ_FORCEINLINE mz_bool mz_zip_array_reserve(mz_zip_archive *pZip, mz_zip_array *pArray, size_t new_సామర్థ్యం, mz_uint growing)
{
  ఒకవేళ (new_సామర్థ్యం > pArray->m_సామర్థ్యం) { ఒకవేళ (!mz_zip_array_ensure_సామర్థ్యం(pZip, pArray, new_సామర్థ్యం, growing)) తిరిగి MZ_FALSE; }
  తిరిగి MZ_TRUE;
}

స్థిర MZ_FORCEINLINE mz_bool mz_zip_array_resize(mz_zip_archive *pZip, mz_zip_array *pArray, size_t new_కొలత, mz_uint growing)
{
  ఒకవేళ (new_కొలత > pArray->m_సామర్థ్యం) { ఒకవేళ (!mz_zip_array_ensure_సామర్థ్యం(pZip, pArray, new_కొలత, growing)) తిరిగి MZ_FALSE; }
  pArray->m_కొలత = new_కొలత;
  తిరిగి MZ_TRUE;
}

స్థిర MZ_FORCEINLINE mz_bool mz_zip_array_ensure_స్థలం(mz_zip_archive *pZip, mz_zip_array *pArray, size_t n)
{
  తిరిగి mz_zip_array_reserve(pZip, pArray, pArray->m_కొలత + n, MZ_TRUE);
}

స్థిర MZ_FORCEINLINE mz_bool mz_zip_array_నెట్టు_వెనుక(mz_zip_archive *pZip, mz_zip_array *pArray, స్థిరరాశి శూన్య *pElements, size_t n)
{
  size_t orig_కొలత = pArray->m_కొలత; ఒకవేళ (!mz_zip_array_resize(pZip, pArray, orig_కొలత + n, MZ_TRUE)) తిరిగి MZ_FALSE;
  జ్ఞాపకం_నకలు((mz_uint8*)pArray->m_p + orig_కొలత * pArray->m_element_కొలత, pElements, n * pArray->m_element_కొలత);
  తిరిగి MZ_TRUE;
}

#నిర్వచితం_కాకపోతే MINIZ_NO_సమయం
స్థిర సమయం_t mz_zip_dos_గమ్యం_సమయం_t(పూర్ణాంకం dos_సమయం, పూర్ణాంకం dos_date)
{
  నిర్మాణం tm tm;
  memset(&tm, 0, పరిమాణం(tm)); tm.tm_isdst = -1;
  tm.tm_year = ((dos_date >> 9) & 127) + 1980 - 1900; tm.tm_mon = ((dos_date >> 5) & 15) - 1; tm.tm_mday = dos_date & 31;
  tm.tm_hour = (dos_సమయం >> 11) & 31; tm.tm_min = (dos_సమయం >> 5) & 63; tm.tm_sec = (dos_సమయం << 1) & 62;
  తిరిగి mktime(&tm);
}

స్థిర శూన్య mz_zip_సమయం_గమ్యం_dos_సమయం(సమయం_t సమయం, mz_uint16 *p_DOS_సమయం, mz_uint16 *pDOS_date)
{
#నిర్వచితమైతే _MSC_VER
  నిర్మాణం tm tm_struct;
  నిర్మాణం tm *tm = &tm_struct;
  errno_t err = localtime_s(tm, &సమయం);
  ఒకవేళ (err)
  {
    *pDOS_date = 0; *p_DOS_సమయం = 0;
    తిరిగి;
  }
#లేకపోతే
  నిర్మాణం tm *tm = localtime(&సమయం);
#అయితే_ముగింపు
  *p_DOS_సమయం = (mz_uint16)(((tm->tm_hour) << 11) + ((tm->tm_min) << 5) + ((tm->tm_sec) >> 1));
  *pDOS_date = (mz_uint16)(((tm->tm_year + 1900 - 1980) << 9) + ((tm->tm_mon + 1) << 5) + tm->tm_mday);
}
#అయితే_ముగింపు

#నిర్వచితం_కాకపోతే MINIZ_NO_STDIO
స్థిర mz_bool mz_zip_get_file_modified_సమయం(స్థిరరాశి అక్షరం *pFilename, mz_uint16 *p_DOS_సమయం, mz_uint16 *pDOS_date)
{
#నిర్వచితమైతే MINIZ_NO_సమయం
  (శూన్య)pFilename; *pDOS_date = *p_DOS_సమయం = 0;
#లేకపోతే
  నిర్మాణం MZ_FILE_STAT_STRUCT file_stat;
  // On Linux with x86 glibc, this call will fail on large files (>= 0x80000000 bytes) unless you compiled with _LARGEFILE64_SOURCE. Argh.
  ఒకవేళ (MZ_FILE_STAT(pFilename, &file_stat) != 0)
    తిరిగి MZ_FALSE;
  mz_zip_సమయం_గమ్యం_dos_సమయం(file_stat.st_mtime, p_DOS_సమయం, pDOS_date);
#అయితే_ముగింపు // #ifdef MINIZ_NO_TIME
  తిరిగి MZ_TRUE;
}

#నిర్వచితం_కాకపోతే MINIZ_NO_సమయం
స్థిర mz_bool mz_zip_సమితి_file_times(స్థిరరాశి అక్షరం *pFilename, సమయం_t access_సమయం, సమయం_t modified_సమయం)
{
  నిర్మాణం utimbuf t; t.actime = access_సమయం; t.modtime = modified_సమయం;
  తిరిగి !utime(pFilename, &t);
}
#అయితే_ముగింపు // #ifndef MINIZ_NO_TIME
#అయితే_ముగింపు // #ifndef MINIZ_NO_STDIO

స్థిర mz_bool mz_zip_reader_init_అంతర్గత(mz_zip_archive *pZip, mz_uint32 flags)
{
  (శూన్య)flags;
  ఒకవేళ ((!pZip) || (pZip->m_pState) || (pZip->m_zip_బహుళకం != MZ_ZIP_బహుళకం_INVALID))
    తిరిగి MZ_FALSE;

  ఒకవేళ (!pZip->m_pAlloc) pZip->m_pAlloc = def_alloc_func;
  ఒకవేళ (!pZip->m_pFree) pZip->m_pFree = def_free_func;
  ఒకవేళ (!pZip->m_pRealloc) pZip->m_pRealloc = def_realloc_func;

  pZip->m_zip_బహుళకం = MZ_ZIP_బహుళకం_READING;
  pZip->m_archive_కొలత = 0;
  pZip->m_central_directory_file_ofs = 0;
  pZip->m_మొత్తం_files = 0;

  ఒకవేళ (ఖాళీ == (pZip->m_pState = (mz_zip_అంతర్గత_state *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, పరిమాణం(mz_zip_అంతర్గత_state))))
    తిరిగి MZ_FALSE;
  memset(pZip->m_pState, 0, పరిమాణం(mz_zip_అంతర్గత_state));
  MZ_ZIP_ARRAY_సమితి_ELEMENT_కొలత(&pZip->m_pState->m_central_dir, పరిమాణం(mz_uint8));
  MZ_ZIP_ARRAY_సమితి_ELEMENT_కొలత(&pZip->m_pState->m_central_dir_offsets, పరిమాణం(mz_uint32));
  MZ_ZIP_ARRAY_సమితి_ELEMENT_కొలత(&pZip->m_pState->m_sorted_central_dir_offsets, పరిమాణం(mz_uint32));
  తిరిగి MZ_TRUE;
}

స్థిర MZ_FORCEINLINE mz_bool mz_zip_reader_filename_less(స్థిరరాశి mz_zip_array *pCentral_dir_array, స్థిరరాశి mz_zip_array *pCentral_dir_offsets, mz_uint l_సూచీ, mz_uint r_సూచీ)
{
  స్థిరరాశి mz_uint8 *pL = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, l_సూచీ)), *pE;
  స్థిరరాశి mz_uint8 *pR = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, r_సూచీ));
  mz_uint l_len = MZ_READ_LE16(pL + MZ_ZIP_CDH_FILENAME_LEN_OFS), r_len = MZ_READ_LE16(pR + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  mz_uint8 l = 0, r = 0;
  pL += MZ_ZIP_CENTRAL_DIR_శీర్షిక_కొలత; pR += MZ_ZIP_CENTRAL_DIR_శీర్షిక_కొలత;
  pE = pL + MZ_MIN(l_len, r_len);
  అయితే (pL < pE)
  {
    ఒకవేళ ((l = MZ_TOLOWER(*pL)) != (r = MZ_TOLOWER(*pR)))
      ఆపు;
    pL++; pR++;
  }
  తిరిగి (pL == pE) ? (l_len < r_len) : (l < r);
}

#నిర్వచించు MZ_మార్పిడి_UINT32(a, b) చేయి { mz_uint32 t = a; a = b; b = t; } MZ_MACRO_చివర

// Heap sort of lowercased filenames, used to help accelerate plain central directory searches by mz_zip_reader_locate_file(). (Could also use qsort(), but it could allocate memory.)
స్థిర శూన్య mz_zip_reader_క్రమీకరించు_central_dir_offsets_by_filename(mz_zip_archive *pZip)
{
  mz_zip_అంతర్గత_state *pState = pZip->m_pState;
  స్థిరరాశి mz_zip_array *pCentral_dir_offsets = &pState->m_central_dir_offsets;
  స్థిరరాశి mz_zip_array *pCentral_dir = &pState->m_central_dir;
  mz_uint32 *pIndices = &MZ_ZIP_ARRAY_ELEMENT(&pState->m_sorted_central_dir_offsets, mz_uint32, 0);
  స్థిరరాశి పూర్ణాంకం కొలత = pZip->m_మొత్తం_files;
  పూర్ణాంకం ప్రారంభం = (కొలత - 2) >> 1, చివర;
  అయితే (ప్రారంభం >= 0)
  {
    పూర్ణాంకం బిడ్డ, మూలం = ప్రారంభం;
    కొరకు ( ; ; )
    {
      ఒకవేళ ((బిడ్డ = (మూలం << 1) + 1) >= కొలత)
        ఆపు;
      బిడ్డ += (((బిడ్డ + 1) < కొలత) && (mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[బిడ్డ], pIndices[బిడ్డ + 1])));
      ఒకవేళ (!mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[మూలం], pIndices[బిడ్డ]))
        ఆపు;
      MZ_మార్పిడి_UINT32(pIndices[మూలం], pIndices[బిడ్డ]); మూలం = బిడ్డ;
    }
    ప్రారంభం--;
  }

  చివర = కొలత - 1;
  అయితే (చివర > 0)
  {
    పూర్ణాంకం బిడ్డ, మూలం = 0;
    MZ_మార్పిడి_UINT32(pIndices[చివర], pIndices[0]);
    కొరకు ( ; ; )
    {
      ఒకవేళ ((బిడ్డ = (మూలం << 1) + 1) >= చివర)
        ఆపు;
      బిడ్డ += (((బిడ్డ + 1) < చివర) && mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[బిడ్డ], pIndices[బిడ్డ + 1]));
      ఒకవేళ (!mz_zip_reader_filename_less(pCentral_dir, pCentral_dir_offsets, pIndices[మూలం], pIndices[బిడ్డ]))
        ఆపు;
      MZ_మార్పిడి_UINT32(pIndices[మూలం], pIndices[బిడ్డ]); మూలం = బిడ్డ;
    }
    చివర--;
  }
}

స్థిర mz_bool mz_zip_reader_read_central_dir(mz_zip_archive *pZip, mz_uint32 flags)
{
  mz_uint cdir_కొలత, అంకె_this_disk, cdir_disk_సూచీ;
  mz_uint64 cdir_ofs;
  mz_int64 cur_file_ofs;
  స్థిరరాశి mz_uint8 *p;
  mz_uint32 buf_u32[4096 / పరిమాణం(mz_uint32)]; mz_uint8 *pBuf = (mz_uint8 *)buf_u32;
  mz_bool క్రమీకరించు_central_dir = ((flags & MZ_ZIP_FLAG_DO_NOT_క్రమీకరించు_CENTRAL_DIRECTORY) == 0);
  // Basic sanity checks - reject files which are too small, and check the first 4 bytes of the file to make sure a local header is there.
  ఒకవేళ (pZip->m_archive_కొలత < MZ_ZIP_చివర_యొక్క_CENTRAL_DIR_శీర్షిక_కొలత)
    తిరిగి MZ_FALSE;
  // Find the end of central directory record by scanning the file from the end towards the beginning.
  cur_file_ofs = MZ_MAX((mz_int64)pZip->m_archive_కొలత - (mz_int64)పరిమాణం(buf_u32), 0);
  కొరకు ( ; ; )
  {
    పూర్ణాంకం i, n = (పూర్ణాంకం)MZ_MIN(పరిమాణం(buf_u32), pZip->m_archive_కొలత - cur_file_ofs);
    ఒకవేళ (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, n) != (mz_uint)n)
      తిరిగి MZ_FALSE;
    కొరకు (i = n - 4; i >= 0; --i)
      ఒకవేళ (MZ_READ_LE32(pBuf + i) == MZ_ZIP_చివర_యొక్క_CENTRAL_DIR_శీర్షిక_SIG)
        ఆపు;
    ఒకవేళ (i >= 0)
    {
      cur_file_ofs += i;
      ఆపు;
    }
    ఒకవేళ ((!cur_file_ofs) || ((pZip->m_archive_కొలత - cur_file_ofs) >= (0xFFFF + MZ_ZIP_చివర_యొక్క_CENTRAL_DIR_శీర్షిక_కొలత)))
      తిరిగి MZ_FALSE;
    cur_file_ofs = MZ_MAX(cur_file_ofs - (పరిమాణం(buf_u32) - 3), 0);
  }
  // Read and verify the end of central directory record.
  ఒకవేళ (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, MZ_ZIP_చివర_యొక్క_CENTRAL_DIR_శీర్షిక_కొలత) != MZ_ZIP_చివర_యొక్క_CENTRAL_DIR_శీర్షిక_కొలత)
    తిరిగి MZ_FALSE;
  ఒకవేళ ((MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_SIG_OFS) != MZ_ZIP_చివర_యొక్క_CENTRAL_DIR_శీర్షిక_SIG) ||
      ((pZip->m_మొత్తం_files = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_CDIR_మొత్తం_ENTRIES_OFS)) != MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_CDIR_అంకె_ENTRIES_ON_DISK_OFS)))
    తిరిగి MZ_FALSE;

  అంకె_this_disk = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_అంకె_THIS_DISK_OFS);
  cdir_disk_సూచీ = MZ_READ_LE16(pBuf + MZ_ZIP_ECDH_అంకె_DISK_CDIR_OFS);
  ఒకవేళ (((అంకె_this_disk | cdir_disk_సూచీ) != 0) && ((అంకె_this_disk != 1) || (cdir_disk_సూచీ != 1)))
    తిరిగి MZ_FALSE;

  ఒకవేళ ((cdir_కొలత = MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_CDIR_కొలత_OFS)) < pZip->m_మొత్తం_files * MZ_ZIP_CENTRAL_DIR_శీర్షిక_కొలత)
    తిరిగి MZ_FALSE;

  cdir_ofs = MZ_READ_LE32(pBuf + MZ_ZIP_ECDH_CDIR_OFS_OFS);
  ఒకవేళ ((cdir_ofs + (mz_uint64)cdir_కొలత) > pZip->m_archive_కొలత)
    తిరిగి MZ_FALSE;

  pZip->m_central_directory_file_ofs = cdir_ofs;

  ఒకవేళ (pZip->m_మొత్తం_files)
  {
     mz_uint i, n;

    // Read the entire central directory into a heap block, and allocate another heap block to hold the unsorted central dir file record offsets, and another to hold the sorted indices.
    ఒకవేళ ((!mz_zip_array_resize(pZip, &pZip->m_pState->m_central_dir, cdir_కొలత, MZ_FALSE)) ||
        (!mz_zip_array_resize(pZip, &pZip->m_pState->m_central_dir_offsets, pZip->m_మొత్తం_files, MZ_FALSE)))
      తిరిగి MZ_FALSE;

    ఒకవేళ (క్రమీకరించు_central_dir)
    {
      ఒకవేళ (!mz_zip_array_resize(pZip, &pZip->m_pState->m_sorted_central_dir_offsets, pZip->m_మొత్తం_files, MZ_FALSE))
        తిరిగి MZ_FALSE;
    }

    ఒకవేళ (pZip->m_pRead(pZip->m_pIO_opaque, cdir_ofs, pZip->m_pState->m_central_dir.m_p, cdir_కొలత) != cdir_కొలత)
      తిరిగి MZ_FALSE;

    // Now create an index into the central directory file records, do some basic sanity checking on each record, and check for zip64 entries (which are not yet supported).
    p = (స్థిరరాశి mz_uint8 *)pZip->m_pState->m_central_dir.m_p;
    కొరకు (n = cdir_కొలత, i = 0; i < pZip->m_మొత్తం_files; ++i)
    {
      mz_uint మొత్తం_శీర్షిక_కొలత, comp_కొలత, decomp_కొలత, disk_సూచీ;
      ఒకవేళ ((n < MZ_ZIP_CENTRAL_DIR_శీర్షిక_కొలత) || (MZ_READ_LE32(p) != MZ_ZIP_CENTRAL_DIR_శీర్షిక_SIG))
        తిరిగి MZ_FALSE;
      MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, i) = (mz_uint32)(p - (స్థిరరాశి mz_uint8 *)pZip->m_pState->m_central_dir.m_p);
      ఒకవేళ (క్రమీకరించు_central_dir)
        MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_sorted_central_dir_offsets, mz_uint32, i) = i;
      comp_కొలత = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_కొలత_OFS);
      decomp_కొలత = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_కొలత_OFS);
      ఒకవేళ (((!MZ_READ_LE32(p + MZ_ZIP_CDH_పద్ధతి_OFS)) && (decomp_కొలత != comp_కొలత)) || (decomp_కొలత && !comp_కొలత) || (decomp_కొలత == 0xFFFFFFFF) || (comp_కొలత == 0xFFFFFFFF))
        తిరిగి MZ_FALSE;
      disk_సూచీ = MZ_READ_LE16(p + MZ_ZIP_CDH_DISK_ప్రారంభం_OFS);
      ఒకవేళ ((disk_సూచీ != అంకె_this_disk) && (disk_సూచీ != 1))
        తిరిగి MZ_FALSE;
      ఒకవేళ (((mz_uint64)MZ_READ_LE32(p + MZ_ZIP_CDH_LOCAL_శీర్షిక_OFS) + MZ_ZIP_LOCAL_DIR_శీర్షిక_కొలత + comp_కొలత) > pZip->m_archive_కొలత)
        తిరిగి MZ_FALSE;
      ఒకవేళ ((మొత్తం_శీర్షిక_కొలత = MZ_ZIP_CENTRAL_DIR_శీర్షిక_కొలత + MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_EXTRA_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_COMMENT_LEN_OFS)) > n)
        తిరిగి MZ_FALSE;
      n -= మొత్తం_శీర్షిక_కొలత; p += మొత్తం_శీర్షిక_కొలత;
    }
  }

  ఒకవేళ (క్రమీకరించు_central_dir)
    mz_zip_reader_క్రమీకరించు_central_dir_offsets_by_filename(pZip);

  తిరిగి MZ_TRUE;
}

mz_bool mz_zip_reader_init(mz_zip_archive *pZip, mz_uint64 కొలత, mz_uint32 flags)
{
  ఒకవేళ ((!pZip) || (!pZip->m_pRead))
    తిరిగి MZ_FALSE;
  ఒకవేళ (!mz_zip_reader_init_అంతర్గత(pZip, flags))
    తిరిగి MZ_FALSE;
  pZip->m_archive_కొలత = కొలత;
  ఒకవేళ (!mz_zip_reader_read_central_dir(pZip, flags))
  {
    mz_zip_reader_చివర(pZip);
    తిరిగి MZ_FALSE;
  }
  తిరిగి MZ_TRUE;
}

స్థిర size_t mz_zip_mem_read_func(శూన్య *pOpaque, mz_uint64 file_ofs, శూన్య *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  size_t s = (file_ofs >= pZip->m_archive_కొలత) ? 0 : (size_t)MZ_MIN(pZip->m_archive_కొలత - file_ofs, n);
  జ్ఞాపకం_నకలు(pBuf, (స్థిరరాశి mz_uint8 *)pZip->m_pState->m_pMem + file_ofs, s);
  తిరిగి s;
}

mz_bool mz_zip_reader_init_mem(mz_zip_archive *pZip, స్థిరరాశి శూన్య *pMem, size_t కొలత, mz_uint32 flags)
{
  ఒకవేళ (!mz_zip_reader_init_అంతర్గత(pZip, flags))
    తిరిగి MZ_FALSE;
  pZip->m_archive_కొలత = కొలత;
  pZip->m_pRead = mz_zip_mem_read_func;
  pZip->m_pIO_opaque = pZip;
#నిర్వచితమైతే __cplusplus
  pZip->m_pState->m_pMem = const_cast<శూన్య *>(pMem);
#లేకపోతే
  pZip->m_pState->m_pMem = (శూన్య *)pMem;
#అయితే_ముగింపు
  pZip->m_pState->m_mem_కొలత = కొలత;
  ఒకవేళ (!mz_zip_reader_read_central_dir(pZip, flags))
  {
    mz_zip_reader_చివర(pZip);
    తిరిగి MZ_FALSE;
  }
  తిరిగి MZ_TRUE;
}

#నిర్వచితం_కాకపోతే MINIZ_NO_STDIO
స్థిర size_t mz_zip_file_read_func(శూన్య *pOpaque, mz_uint64 file_ofs, శూన్య *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_int64 cur_ofs = MZ_FTELL64(pZip->m_pState->m_pFile);
  ఒకవేళ (((mz_int64)file_ofs < 0) || (((cur_ofs != (mz_int64)file_ofs)) && (MZ_FSEEK64(pZip->m_pState->m_pFile, (mz_int64)file_ofs, SEEK_SET))))
    తిరిగి 0;
  తిరిగి MZ_FREAD(pBuf, 1, n, pZip->m_pState->m_pFile);
}

mz_bool mz_zip_reader_init_file(mz_zip_archive *pZip, స్థిరరాశి అక్షరం *pFilename, mz_uint32 flags)
{
  mz_uint64 file_కొలత;
  MZ_FILE *pFile = MZ_FOPEN(pFilename, "rb");
  ఒకవేళ (!pFile)
    తిరిగి MZ_FALSE;
  ఒకవేళ (MZ_FSEEK64(pFile, 0, SEEK_END))
  {
    MZ_FCLOSE(pFile);
    తిరిగి MZ_FALSE;
  }
  file_కొలత = MZ_FTELL64(pFile);
  ఒకవేళ (!mz_zip_reader_init_అంతర్గత(pZip, flags))
  {
    MZ_FCLOSE(pFile);
    తిరిగి MZ_FALSE;
  }
  pZip->m_pRead = mz_zip_file_read_func;
  pZip->m_pIO_opaque = pZip;
  pZip->m_pState->m_pFile = pFile;
  pZip->m_archive_కొలత = file_కొలత;
  ఒకవేళ (!mz_zip_reader_read_central_dir(pZip, flags))
  {
    mz_zip_reader_చివర(pZip);
    తిరిగి MZ_FALSE;
  }
  తిరిగి MZ_TRUE;
}
#అయితే_ముగింపు // #ifndef MINIZ_NO_STDIO

mz_uint mz_zip_reader_get_అంకె_files(mz_zip_archive *pZip)
{
  తిరిగి pZip ? pZip->m_మొత్తం_files : 0;
}

స్థిర MZ_FORCEINLINE స్థిరరాశి mz_uint8 *mz_zip_reader_get_cdh(mz_zip_archive *pZip, mz_uint file_సూచీ)
{
  ఒకవేళ ((!pZip) || (!pZip->m_pState) || (file_సూచీ >= pZip->m_మొత్తం_files) || (pZip->m_zip_బహుళకం != MZ_ZIP_బహుళకం_READING))
    తిరిగి ఖాళీ;
  తిరిగి &MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_సూచీ));
}

mz_bool mz_zip_reader_is_file_encrypted(mz_zip_archive *pZip, mz_uint file_సూచీ)
{
  mz_uint m_బిట్టు_flag;
  స్థిరరాశి mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_సూచీ);
  ఒకవేళ (!p)
    తిరిగి MZ_FALSE;
  m_బిట్టు_flag = MZ_READ_LE16(p + MZ_ZIP_CDH_బిట్టు_FLAG_OFS);
  తిరిగి (m_బిట్టు_flag & 1);
}

mz_bool mz_zip_reader_is_file_a_directory(mz_zip_archive *pZip, mz_uint file_సూచీ)
{
  mz_uint filename_len, external_attr;
  స్థిరరాశి mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_సూచీ);
  ఒకవేళ (!p)
    తిరిగి MZ_FALSE;

  // First see if the filename ends with a '/' character.
  filename_len = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  ఒకవేళ (filename_len)
  {
    ఒకవేళ (*(p + MZ_ZIP_CENTRAL_DIR_శీర్షిక_కొలత + filename_len - 1) == '/')
      తిరిగి MZ_TRUE;
  }

  // Bugfix: This code was also checking if the internal attribute was non-zero, which wasn't correct.
  // Most/all zip writers (hopefully) set DOS file/directory attributes in the low 16-bits, so check for the DOS directory flag and ignore the source OS ID in the created by field.
  // FIXME: Remove this check? Is it necessary - we already check the filename.
  external_attr = MZ_READ_LE32(p + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS);
  ఒకవేళ ((external_attr & 0x10) != 0)
    తిరిగి MZ_TRUE;

  తిరిగి MZ_FALSE;
}

mz_bool mz_zip_reader_file_stat(mz_zip_archive *pZip, mz_uint file_సూచీ, mz_zip_archive_file_stat *pStat)
{
  mz_uint n;
  స్థిరరాశి mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_సూచీ);
  ఒకవేళ ((!p) || (!pStat))
    తిరిగి MZ_FALSE;

  // Unpack the central directory record.
  pStat->m_file_సూచీ = file_సూచీ;
  pStat->m_central_dir_ofs = MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_సూచీ);
  pStat->m_సంస్కరణ_made_by = MZ_READ_LE16(p + MZ_ZIP_CDH_సంస్కరణ_MADE_BY_OFS);
  pStat->m_సంస్కరణ_needed = MZ_READ_LE16(p + MZ_ZIP_CDH_సంస్కరణ_NEEDED_OFS);
  pStat->m_బిట్టు_flag = MZ_READ_LE16(p + MZ_ZIP_CDH_బిట్టు_FLAG_OFS);
  pStat->m_పద్ధతి = MZ_READ_LE16(p + MZ_ZIP_CDH_పద్ధతి_OFS);
#నిర్వచితం_కాకపోతే MINIZ_NO_సమయం
  pStat->m_సమయం = mz_zip_dos_గమ్యం_సమయం_t(MZ_READ_LE16(p + MZ_ZIP_CDH_FILE_సమయం_OFS), MZ_READ_LE16(p + MZ_ZIP_CDH_FILE_DATE_OFS));
#అయితే_ముగింపు
  pStat->m_చక్రీయ_తనిఖీ_32 = MZ_READ_LE32(p + MZ_ZIP_CDH_చక్రీయ_తనిఖీ_32_OFS);
  pStat->m_comp_కొలత = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_కొలత_OFS);
  pStat->m_uncomp_కొలత = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_కొలత_OFS);
  pStat->m_అంతర్గత_attr = MZ_READ_LE16(p + MZ_ZIP_CDH_అంతర్గత_ATTR_OFS);
  pStat->m_external_attr = MZ_READ_LE32(p + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS);
  pStat->m_local_శీర్షిక_ofs = MZ_READ_LE32(p + MZ_ZIP_CDH_LOCAL_శీర్షిక_OFS);

  // Copy as much of the filename and comment as possible.
  n = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS); n = MZ_MIN(n, MZ_ZIP_MAX_ARCHIVE_FILENAME_కొలత - 1);
  జ్ఞాపకం_నకలు(pStat->m_filename, p + MZ_ZIP_CENTRAL_DIR_శీర్షిక_కొలత, n); pStat->m_filename[n] = '\0';

  n = MZ_READ_LE16(p + MZ_ZIP_CDH_COMMENT_LEN_OFS); n = MZ_MIN(n, MZ_ZIP_MAX_ARCHIVE_FILE_COMMENT_కొలత - 1);
  pStat->m_comment_కొలత = n;
  జ్ఞాపకం_నకలు(pStat->m_comment, p + MZ_ZIP_CENTRAL_DIR_శీర్షిక_కొలత + MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p + MZ_ZIP_CDH_EXTRA_LEN_OFS), n); pStat->m_comment[n] = '\0';

  తిరిగి MZ_TRUE;
}

mz_uint mz_zip_reader_get_filename(mz_zip_archive *pZip, mz_uint file_సూచీ, అక్షరం *pFilename, mz_uint filename_buf_కొలత)
{
  mz_uint n;
  స్థిరరాశి mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_సూచీ);
  ఒకవేళ (!p) { ఒకవేళ (filename_buf_కొలత) pFilename[0] = '\0'; తిరిగి 0; }
  n = MZ_READ_LE16(p + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  ఒకవేళ (filename_buf_కొలత)
  {
    n = MZ_MIN(n, filename_buf_కొలత - 1);
    జ్ఞాపకం_నకలు(pFilename, p + MZ_ZIP_CENTRAL_DIR_శీర్షిక_కొలత, n);
    pFilename[n] = '\0';
  }
  తిరిగి n + 1;
}

స్థిర MZ_FORCEINLINE mz_bool mz_zip_reader_string_equal(స్థిరరాశి అక్షరం *pA, స్థిరరాశి అక్షరం *pB, mz_uint len, mz_uint flags)
{
  mz_uint i;
  ఒకవేళ (flags & MZ_ZIP_FLAG_CASE_SENSITIVE)
    తిరిగి 0 == memcmp(pA, pB, len);
  కొరకు (i = 0; i < len; ++i)
    ఒకవేళ (MZ_TOLOWER(pA[i]) != MZ_TOLOWER(pB[i]))
      తిరిగి MZ_FALSE;
  తిరిగి MZ_TRUE;
}

స్థిర MZ_FORCEINLINE పూర్ణాంకం mz_zip_reader_filename_compare(స్థిరరాశి mz_zip_array *pCentral_dir_array, స్థిరరాశి mz_zip_array *pCentral_dir_offsets, mz_uint l_సూచీ, స్థిరరాశి అక్షరం *pR, mz_uint r_len)
{
  స్థిరరాశి mz_uint8 *pL = &MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_array, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(pCentral_dir_offsets, mz_uint32, l_సూచీ)), *pE;
  mz_uint l_len = MZ_READ_LE16(pL + MZ_ZIP_CDH_FILENAME_LEN_OFS);
  mz_uint8 l = 0, r = 0;
  pL += MZ_ZIP_CENTRAL_DIR_శీర్షిక_కొలత;
  pE = pL + MZ_MIN(l_len, r_len);
  అయితే (pL < pE)
  {
    ఒకవేళ ((l = MZ_TOLOWER(*pL)) != (r = MZ_TOLOWER(*pR)))
      ఆపు;
    pL++; pR++;
  }
  తిరిగి (pL == pE) ? (పూర్ణాంకం)(l_len - r_len) : (l - r);
}

స్థిర పూర్ణాంకం mz_zip_reader_locate_file_ద్విమాన_శోధన(mz_zip_archive *pZip, స్థిరరాశి అక్షరం *pFilename)
{
  mz_zip_అంతర్గత_state *pState = pZip->m_pState;
  స్థిరరాశి mz_zip_array *pCentral_dir_offsets = &pState->m_central_dir_offsets;
  స్థిరరాశి mz_zip_array *pCentral_dir = &pState->m_central_dir;
  mz_uint32 *pIndices = &MZ_ZIP_ARRAY_ELEMENT(&pState->m_sorted_central_dir_offsets, mz_uint32, 0);
  స్థిరరాశి పూర్ణాంకం కొలత = pZip->m_మొత్తం_files;
  స్థిరరాశి mz_uint filename_len = (mz_uint)అక్షరశ్రేణి_పొడవు(pFilename);
  పూర్ణాంకం l = 0, h = కొలత - 1;
  అయితే (l <= h)
  {
    పూర్ణాంకం m = (l + h) >> 1, file_సూచీ = pIndices[m], comp = mz_zip_reader_filename_compare(pCentral_dir, pCentral_dir_offsets, file_సూచీ, pFilename, filename_len);
    ఒకవేళ (!comp)
      తిరిగి file_సూచీ;
    లేకపోతే ఒకవేళ (comp < 0)
      l = m + 1;
    లేకపోతే
      h = m - 1;
  }
  తిరిగి -1;
}

పూర్ణాంకం mz_zip_reader_locate_file(mz_zip_archive *pZip, స్థిరరాశి అక్షరం *pName, స్థిరరాశి అక్షరం *pComment, mz_uint flags)
{
  mz_uint file_సూచీ; size_t name_len, comment_len;
  ఒకవేళ ((!pZip) || (!pZip->m_pState) || (!pName) || (pZip->m_zip_బహుళకం != MZ_ZIP_బహుళకం_READING))
    తిరిగి -1;
  ఒకవేళ (((flags & (MZ_ZIP_FLAG_IGNORE_మార్గం | MZ_ZIP_FLAG_CASE_SENSITIVE)) == 0) && (!pComment) && (pZip->m_pState->m_sorted_central_dir_offsets.m_కొలత))
    తిరిగి mz_zip_reader_locate_file_ద్విమాన_శోధన(pZip, pName);
  name_len = అక్షరశ్రేణి_పొడవు(pName); ఒకవేళ (name_len > 0xFFFF) తిరిగి -1;
  comment_len = pComment ? అక్షరశ్రేణి_పొడవు(pComment) : 0; ఒకవేళ (comment_len > 0xFFFF) తిరిగి -1;
  కొరకు (file_సూచీ = 0; file_సూచీ < pZip->m_మొత్తం_files; file_సూచీ++)
  {
    స్థిరరాశి mz_uint8 *p_శీర్షిక = &MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir, mz_uint8, MZ_ZIP_ARRAY_ELEMENT(&pZip->m_pState->m_central_dir_offsets, mz_uint32, file_సూచీ));
    mz_uint filename_len = MZ_READ_LE16(p_శీర్షిక + MZ_ZIP_CDH_FILENAME_LEN_OFS);
    స్థిరరాశి అక్షరం *pFilename = (స్థిరరాశి అక్షరం *)p_శీర్షిక + MZ_ZIP_CENTRAL_DIR_శీర్షిక_కొలత;
    ఒకవేళ (filename_len < name_len)
      కొనసాగు;
    ఒకవేళ (comment_len)
    {
      mz_uint file_extra_len = MZ_READ_LE16(p_శీర్షిక + MZ_ZIP_CDH_EXTRA_LEN_OFS), file_comment_len = MZ_READ_LE16(p_శీర్షిక + MZ_ZIP_CDH_COMMENT_LEN_OFS);
      స్థిరరాశి అక్షరం *pFile_comment = pFilename + filename_len + file_extra_len;
      ఒకవేళ ((file_comment_len != comment_len) || (!mz_zip_reader_string_equal(pComment, pFile_comment, file_comment_len, flags)))
        కొనసాగు;
    }
    ఒకవేళ ((flags & MZ_ZIP_FLAG_IGNORE_మార్గం) && (filename_len))
    {
      పూర్ణాంకం ofs = filename_len - 1;
      చేయి
      {
        ఒకవేళ ((pFilename[ofs] == '/') || (pFilename[ofs] == '\\') || (pFilename[ofs] == ':'))
          ఆపు;
      } అయితే (--ofs >= 0);
      ofs++;
      pFilename += ofs; filename_len -= ofs;
    }
    ఒకవేళ ((filename_len == name_len) && (mz_zip_reader_string_equal(pName, pFilename, filename_len, flags)))
      తిరిగి file_సూచీ;
  }
  తిరిగి -1;
}

mz_bool mz_zip_reader_వెలికితీయి_గమ్యం_mem_no_alloc(mz_zip_archive *pZip, mz_uint file_సూచీ, శూన్య *pBuf, size_t buf_కొలత_2, mz_uint flags, శూన్య *pUser_read_buf, size_t user_read_buf_కొలత)
{
  పూర్ణాంకం స్థితి_2 = TINFL_స్థితి_పూర్తి;
  mz_uint64 needed_కొలత, cur_file_ofs, comp_మిగిలిన, బహిర్గతం_buf_ofs = 0, read_buf_కొలత, read_buf_ofs = 0, read_buf_avail;
  mz_zip_archive_file_stat file_stat;
  శూన్య *pRead_buf;
  mz_uint32 local_శీర్షిక_u32[(MZ_ZIP_LOCAL_DIR_శీర్షిక_కొలత + పరిమాణం(mz_uint32) - 1) / పరిమాణం(mz_uint32)]; mz_uint8 *p_Local_శీర్షిక = (mz_uint8 *)local_శీర్షిక_u32;
  tinfl_decompressor inflator;

  ఒకవేళ ((buf_కొలత_2) && (!pBuf))
    తిరిగి MZ_FALSE;

  ఒకవేళ (!mz_zip_reader_file_stat(pZip, file_సూచీ, &file_stat))
    తిరిగి MZ_FALSE;

  // Empty file, or a directory (but not always a directory - I've seen odd zips with directories that have compressed data which inflates to 0 bytes)
  ఒకవేళ (!file_stat.m_comp_కొలత)
    తిరిగి MZ_TRUE;

  // Entry is a subdirectory (I've seen old zips with dir entries which have compressed deflate data which inflates to 0 bytes, but these entries claim to uncompress to 512 bytes in the headers).
  // I'm torn how to handle this case - should it fail instead?
  ఒకవేళ (mz_zip_reader_is_file_a_directory(pZip, file_సూచీ))
    తిరిగి MZ_TRUE;

  // Encryption and patch files are not supported.
  ఒకవేళ (file_stat.m_బిట్టు_flag & (1 | 32))
    తిరిగి MZ_FALSE;

  // This function only supports stored and deflate.
  ఒకవేళ ((!(flags & MZ_ZIP_FLAG_COMPRESSED_దత్తాంశం)) && (file_stat.m_పద్ధతి != 0) && (file_stat.m_పద్ధతి != MZ_DEFLATED))
    తిరిగి MZ_FALSE;

  // Ensure supplied output buffer is large enough.
  needed_కొలత = (flags & MZ_ZIP_FLAG_COMPRESSED_దత్తాంశం) ? file_stat.m_comp_కొలత : file_stat.m_uncomp_కొలత;
  ఒకవేళ (buf_కొలత_2 < needed_కొలత)
    తిరిగి MZ_FALSE;

  // Read and parse the local directory entry.
  cur_file_ofs = file_stat.m_local_శీర్షిక_ofs;
  ఒకవేళ (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, p_Local_శీర్షిక, MZ_ZIP_LOCAL_DIR_శీర్షిక_కొలత) != MZ_ZIP_LOCAL_DIR_శీర్షిక_కొలత)
    తిరిగి MZ_FALSE;
  ఒకవేళ (MZ_READ_LE32(p_Local_శీర్షిక) != MZ_ZIP_LOCAL_DIR_శీర్షిక_SIG)
    తిరిగి MZ_FALSE;

  cur_file_ofs += MZ_ZIP_LOCAL_DIR_శీర్షిక_కొలత + MZ_READ_LE16(p_Local_శీర్షిక + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p_Local_శీర్షిక + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  ఒకవేళ ((cur_file_ofs + file_stat.m_comp_కొలత) > pZip->m_archive_కొలత)
    తిరిగి MZ_FALSE;

  ఒకవేళ ((flags & MZ_ZIP_FLAG_COMPRESSED_దత్తాంశం) || (!file_stat.m_పద్ధతి))
  {
    // The file is stored or the caller has requested the compressed data.
    ఒకవేళ (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pBuf, (size_t)needed_కొలత) != needed_కొలత)
      తిరిగి MZ_FALSE;
    తిరిగి ((flags & MZ_ZIP_FLAG_COMPRESSED_దత్తాంశం) != 0) || (mz_చక్రీయ_తనిఖీ_32(MZ_చక్రీయ_తనిఖీ_32_INIT, (స్థిరరాశి mz_uint8 *)pBuf, (size_t)file_stat.m_uncomp_కొలత) == file_stat.m_చక్రీయ_తనిఖీ_32);
  }

  // Decompress the file either directly from memory or from a file input buffer.
  tinfl_init(&inflator);

  ఒకవేళ (pZip->m_pState->m_pMem)
  {
    // Read directly from the archive in memory.
    pRead_buf = (mz_uint8 *)pZip->m_pState->m_pMem + cur_file_ofs;
    read_buf_కొలత = read_buf_avail = file_stat.m_comp_కొలత;
    comp_మిగిలిన = 0;
  }
  లేకపోతే ఒకవేళ (pUser_read_buf)
  {
    // Use a user provided read buffer.
    ఒకవేళ (!user_read_buf_కొలత)
      తిరిగి MZ_FALSE;
    pRead_buf = (mz_uint8 *)pUser_read_buf;
    read_buf_కొలత = user_read_buf_కొలత;
    read_buf_avail = 0;
    comp_మిగిలిన = file_stat.m_comp_కొలత;
  }
  లేకపోతే
  {
    // Temporarily allocate a read buffer.
    read_buf_కొలత = MZ_MIN(file_stat.m_comp_కొలత, MZ_ZIP_MAX_IO_BUF_కొలత);
#నిర్వచితమైతే _MSC_VER
    ఒకవేళ (((0, పరిమాణం(size_t) == పరిమాణం(mz_uint32))) && (read_buf_కొలత > 0x7FFFFFFF))
#లేకపోతే
    ఒకవేళ (((పరిమాణం(size_t) == పరిమాణం(mz_uint32))) && (read_buf_కొలత > 0x7FFFFFFF))
#అయితే_ముగింపు
      తిరిగి MZ_FALSE;
    ఒకవేళ (ఖాళీ == (pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)read_buf_కొలత)))
      తిరిగి MZ_FALSE;
    read_buf_avail = 0;
    comp_మిగిలిన = file_stat.m_comp_కొలత;
  }

  చేయి
  {
    size_t లోపల_buf_కొలత, బహిర్గతం_buf_కొలత = (size_t)(file_stat.m_uncomp_కొలత - బహిర్గతం_buf_ofs);
    ఒకవేళ ((!read_buf_avail) && (!pZip->m_pState->m_pMem))
    {
      read_buf_avail = MZ_MIN(read_buf_కొలత, comp_మిగిలిన);
      ఒకవేళ (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
      {
        స్థితి_2 = TINFL_స్థితి_FAILED;
        ఆపు;
      }
      cur_file_ofs += read_buf_avail;
      comp_మిగిలిన -= read_buf_avail;
      read_buf_ofs = 0;
    }
    లోపల_buf_కొలత = (size_t)read_buf_avail;
    స్థితి_2 = tinfl_decompress(&inflator, (mz_uint8 *)pRead_buf + read_buf_ofs, &లోపల_buf_కొలత, (mz_uint8 *)pBuf, (mz_uint8 *)pBuf + బహిర్గతం_buf_ofs, &బహిర్గతం_buf_కొలత, TINFL_FLAG_USING_NON_WRAPPING_OUTPUT_BUF | (comp_మిగిలిన ? TINFL_FLAG_HAS_మరిన్ని_ఆదానం : 0));
    read_buf_avail -= లోపల_buf_కొలత;
    read_buf_ofs += లోపల_buf_కొలత;
    బహిర్గతం_buf_ofs += బహిర్గతం_buf_కొలత;
  } అయితే (స్థితి_2 == TINFL_స్థితి_NEEDS_మరిన్ని_ఆదానం);

  ఒకవేళ (స్థితి_2 == TINFL_స్థితి_పూర్తి)
  {
    // Make sure the entire file was decompressed, and check its CRC.
    ఒకవేళ ((బహిర్గతం_buf_ofs != file_stat.m_uncomp_కొలత) || (mz_చక్రీయ_తనిఖీ_32(MZ_చక్రీయ_తనిఖీ_32_INIT, (స్థిరరాశి mz_uint8 *)pBuf, (size_t)file_stat.m_uncomp_కొలత) != file_stat.m_చక్రీయ_తనిఖీ_32))
      స్థితి_2 = TINFL_స్థితి_FAILED;
  }

  ఒకవేళ ((!pZip->m_pState->m_pMem) && (!pUser_read_buf))
    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);

  తిరిగి స్థితి_2 == TINFL_స్థితి_పూర్తి;
}

mz_bool mz_zip_reader_వెలికితీయి_file_గమ్యం_mem_no_alloc(mz_zip_archive *pZip, స్థిరరాశి అక్షరం *pFilename, శూన్య *pBuf, size_t buf_కొలత_2, mz_uint flags, శూన్య *pUser_read_buf, size_t user_read_buf_కొలత)
{
  పూర్ణాంకం file_సూచీ = mz_zip_reader_locate_file(pZip, pFilename, ఖాళీ, flags);
  ఒకవేళ (file_సూచీ < 0)
    తిరిగి MZ_FALSE;
  తిరిగి mz_zip_reader_వెలికితీయి_గమ్యం_mem_no_alloc(pZip, file_సూచీ, pBuf, buf_కొలత_2, flags, pUser_read_buf, user_read_buf_కొలత);
}

mz_bool mz_zip_reader_వెలికితీయి_గమ్యం_mem(mz_zip_archive *pZip, mz_uint file_సూచీ, శూన్య *pBuf, size_t buf_కొలత_2, mz_uint flags)
{
  తిరిగి mz_zip_reader_వెలికితీయి_గమ్యం_mem_no_alloc(pZip, file_సూచీ, pBuf, buf_కొలత_2, flags, ఖాళీ, 0);
}

mz_bool mz_zip_reader_వెలికితీయి_file_గమ్యం_mem(mz_zip_archive *pZip, స్థిరరాశి అక్షరం *pFilename, శూన్య *pBuf, size_t buf_కొలత_2, mz_uint flags)
{
  తిరిగి mz_zip_reader_వెలికితీయి_file_గమ్యం_mem_no_alloc(pZip, pFilename, pBuf, buf_కొలత_2, flags, ఖాళీ, 0);
}

శూన్య *mz_zip_reader_వెలికితీయి_గమ్యం_కుప్ప(mz_zip_archive *pZip, mz_uint file_సూచీ, size_t *p_కొలత, mz_uint flags)
{
  mz_uint64 comp_కొలత, uncomp_కొలత, alloc_కొలత_2;
  స్థిరరాశి mz_uint8 *p = mz_zip_reader_get_cdh(pZip, file_సూచీ);
  శూన్య *pBuf;

  ఒకవేళ (p_కొలత)
    *p_కొలత = 0;
  ఒకవేళ (!p)
    తిరిగి ఖాళీ;

  comp_కొలత = MZ_READ_LE32(p + MZ_ZIP_CDH_COMPRESSED_కొలత_OFS);
  uncomp_కొలత = MZ_READ_LE32(p + MZ_ZIP_CDH_DECOMPRESSED_కొలత_OFS);

  alloc_కొలత_2 = (flags & MZ_ZIP_FLAG_COMPRESSED_దత్తాంశం) ? comp_కొలత : uncomp_కొలత;
#నిర్వచితమైతే _MSC_VER
  ఒకవేళ (((0, పరిమాణం(size_t) == పరిమాణం(mz_uint32))) && (alloc_కొలత_2 > 0x7FFFFFFF))
#లేకపోతే
  ఒకవేళ (((పరిమాణం(size_t) == పరిమాణం(mz_uint32))) && (alloc_కొలత_2 > 0x7FFFFFFF))
#అయితే_ముగింపు
    తిరిగి ఖాళీ;
  ఒకవేళ (ఖాళీ == (pBuf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)alloc_కొలత_2)))
    తిరిగి ఖాళీ;

  ఒకవేళ (!mz_zip_reader_వెలికితీయి_గమ్యం_mem(pZip, file_సూచీ, pBuf, (size_t)alloc_కొలత_2, flags))
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
    తిరిగి ఖాళీ;
  }

  ఒకవేళ (p_కొలత) *p_కొలత = (size_t)alloc_కొలత_2;
  తిరిగి pBuf;
}

శూన్య *mz_zip_reader_వెలికితీయి_file_గమ్యం_కుప్ప(mz_zip_archive *pZip, స్థిరరాశి అక్షరం *pFilename, size_t *p_కొలత, mz_uint flags)
{
  పూర్ణాంకం file_సూచీ = mz_zip_reader_locate_file(pZip, pFilename, ఖాళీ, flags);
  ఒకవేళ (file_సూచీ < 0)
  {
    ఒకవేళ (p_కొలత) *p_కొలత = 0;
    తిరిగి MZ_FALSE;
  }
  తిరిగి mz_zip_reader_వెలికితీయి_గమ్యం_కుప్ప(pZip, file_సూచీ, p_కొలత, flags);
}

mz_bool mz_zip_reader_వెలికితీయి_గమ్యం_callback(mz_zip_archive *pZip, mz_uint file_సూచీ, mz_file_write_func pCallback, శూన్య *pOpaque, mz_uint flags)
{
  పూర్ణాంకం స్థితి_2 = TINFL_స్థితి_పూర్తి; mz_uint file_చక్రీయ_తనిఖీ_32 = MZ_చక్రీయ_తనిఖీ_32_INIT;
  mz_uint64 read_buf_కొలత, read_buf_ofs = 0, read_buf_avail, comp_మిగిలిన, బహిర్గతం_buf_ofs = 0, cur_file_ofs;
  mz_zip_archive_file_stat file_stat;
  శూన్య *pRead_buf = ఖాళీ; శూన్య *pWrite_buf = ఖాళీ;
  mz_uint32 local_శీర్షిక_u32[(MZ_ZIP_LOCAL_DIR_శీర్షిక_కొలత + పరిమాణం(mz_uint32) - 1) / పరిమాణం(mz_uint32)]; mz_uint8 *p_Local_శీర్షిక = (mz_uint8 *)local_శీర్షిక_u32;

  ఒకవేళ (!mz_zip_reader_file_stat(pZip, file_సూచీ, &file_stat))
    తిరిగి MZ_FALSE;

  // Empty file, or a directory (but not always a directory - I've seen odd zips with directories that have compressed data which inflates to 0 bytes)
  ఒకవేళ (!file_stat.m_comp_కొలత)
    తిరిగి MZ_TRUE;

  // Entry is a subdirectory (I've seen old zips with dir entries which have compressed deflate data which inflates to 0 bytes, but these entries claim to uncompress to 512 bytes in the headers).
  // I'm torn how to handle this case - should it fail instead?
  ఒకవేళ (mz_zip_reader_is_file_a_directory(pZip, file_సూచీ))
    తిరిగి MZ_TRUE;

  // Encryption and patch files are not supported.
  ఒకవేళ (file_stat.m_బిట్టు_flag & (1 | 32))
    తిరిగి MZ_FALSE;

  // This function only supports stored and deflate.
  ఒకవేళ ((!(flags & MZ_ZIP_FLAG_COMPRESSED_దత్తాంశం)) && (file_stat.m_పద్ధతి != 0) && (file_stat.m_పద్ధతి != MZ_DEFLATED))
    తిరిగి MZ_FALSE;

  // Read and parse the local directory entry.
  cur_file_ofs = file_stat.m_local_శీర్షిక_ofs;
  ఒకవేళ (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, p_Local_శీర్షిక, MZ_ZIP_LOCAL_DIR_శీర్షిక_కొలత) != MZ_ZIP_LOCAL_DIR_శీర్షిక_కొలత)
    తిరిగి MZ_FALSE;
  ఒకవేళ (MZ_READ_LE32(p_Local_శీర్షిక) != MZ_ZIP_LOCAL_DIR_శీర్షిక_SIG)
    తిరిగి MZ_FALSE;

  cur_file_ofs += MZ_ZIP_LOCAL_DIR_శీర్షిక_కొలత + MZ_READ_LE16(p_Local_శీర్షిక + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p_Local_శీర్షిక + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  ఒకవేళ ((cur_file_ofs + file_stat.m_comp_కొలత) > pZip->m_archive_కొలత)
    తిరిగి MZ_FALSE;

  // Decompress the file either directly from memory or from a file input buffer.
  ఒకవేళ (pZip->m_pState->m_pMem)
  {
    pRead_buf = (mz_uint8 *)pZip->m_pState->m_pMem + cur_file_ofs;
    read_buf_కొలత = read_buf_avail = file_stat.m_comp_కొలత;
    comp_మిగిలిన = 0;
  }
  లేకపోతే
  {
    read_buf_కొలత = MZ_MIN(file_stat.m_comp_కొలత, MZ_ZIP_MAX_IO_BUF_కొలత);
    ఒకవేళ (ఖాళీ == (pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)read_buf_కొలత)))
      తిరిగి MZ_FALSE;
    read_buf_avail = 0;
    comp_మిగిలిన = file_stat.m_comp_కొలత;
  }

  ఒకవేళ ((flags & MZ_ZIP_FLAG_COMPRESSED_దత్తాంశం) || (!file_stat.m_పద్ధతి))
  {
    // The file is stored or the caller has requested the compressed data.
    ఒకవేళ (pZip->m_pState->m_pMem)
    {
#నిర్వచితమైతే _MSC_VER
      ఒకవేళ (((0, పరిమాణం(size_t) == పరిమాణం(mz_uint32))) && (file_stat.m_comp_కొలత > 0xFFFFFFFF))
#లేకపోతే
      ఒకవేళ (((పరిమాణం(size_t) == పరిమాణం(mz_uint32))) && (file_stat.m_comp_కొలత > 0xFFFFFFFF))
#అయితే_ముగింపు
        తిరిగి MZ_FALSE;
      ఒకవేళ (pCallback(pOpaque, బహిర్గతం_buf_ofs, pRead_buf, (size_t)file_stat.m_comp_కొలత) != file_stat.m_comp_కొలత)
        స్థితి_2 = TINFL_స్థితి_FAILED;
      లేకపోతే ఒకవేళ (!(flags & MZ_ZIP_FLAG_COMPRESSED_దత్తాంశం))
        file_చక్రీయ_తనిఖీ_32 = (mz_uint32)mz_చక్రీయ_తనిఖీ_32(file_చక్రీయ_తనిఖీ_32, (స్థిరరాశి mz_uint8 *)pRead_buf, (size_t)file_stat.m_comp_కొలత);
      cur_file_ofs += file_stat.m_comp_కొలత;
      బహిర్గతం_buf_ofs += file_stat.m_comp_కొలత;
      comp_మిగిలిన = 0;
    }
    లేకపోతే
    {
      అయితే (comp_మిగిలిన)
      {
        read_buf_avail = MZ_MIN(read_buf_కొలత, comp_మిగిలిన);
        ఒకవేళ (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
        {
          స్థితి_2 = TINFL_స్థితి_FAILED;
          ఆపు;
        }

        ఒకవేళ (!(flags & MZ_ZIP_FLAG_COMPRESSED_దత్తాంశం))
          file_చక్రీయ_తనిఖీ_32 = (mz_uint32)mz_చక్రీయ_తనిఖీ_32(file_చక్రీయ_తనిఖీ_32, (స్థిరరాశి mz_uint8 *)pRead_buf, (size_t)read_buf_avail);

        ఒకవేళ (pCallback(pOpaque, బహిర్గతం_buf_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
        {
          స్థితి_2 = TINFL_స్థితి_FAILED;
          ఆపు;
        }
        cur_file_ofs += read_buf_avail;
        బహిర్గతం_buf_ofs += read_buf_avail;
        comp_మిగిలిన -= read_buf_avail;
      }
    }
  }
  లేకపోతే
  {
    tinfl_decompressor inflator;
    tinfl_init(&inflator);

    ఒకవేళ (ఖాళీ == (pWrite_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, TINFL_LZ_DICT_కొలత)))
      స్థితి_2 = TINFL_స్థితి_FAILED;
    లేకపోతే
    {
      చేయి
      {
        mz_uint8 *pWrite_buf_cur = (mz_uint8 *)pWrite_buf + (బహిర్గతం_buf_ofs & (TINFL_LZ_DICT_కొలత - 1));
        size_t లోపల_buf_కొలత, బహిర్గతం_buf_కొలత = TINFL_LZ_DICT_కొలత - (బహిర్గతం_buf_ofs & (TINFL_LZ_DICT_కొలత - 1));
        ఒకవేళ ((!read_buf_avail) && (!pZip->m_pState->m_pMem))
        {
          read_buf_avail = MZ_MIN(read_buf_కొలత, comp_మిగిలిన);
          ఒకవేళ (pZip->m_pRead(pZip->m_pIO_opaque, cur_file_ofs, pRead_buf, (size_t)read_buf_avail) != read_buf_avail)
          {
            స్థితి_2 = TINFL_స్థితి_FAILED;
            ఆపు;
          }
          cur_file_ofs += read_buf_avail;
          comp_మిగిలిన -= read_buf_avail;
          read_buf_ofs = 0;
        }

        లోపల_buf_కొలత = (size_t)read_buf_avail;
        స్థితి_2 = tinfl_decompress(&inflator, (స్థిరరాశి mz_uint8 *)pRead_buf + read_buf_ofs, &లోపల_buf_కొలత, (mz_uint8 *)pWrite_buf, pWrite_buf_cur, &బహిర్గతం_buf_కొలత, comp_మిగిలిన ? TINFL_FLAG_HAS_మరిన్ని_ఆదానం : 0);
        read_buf_avail -= లోపల_buf_కొలత;
        read_buf_ofs += లోపల_buf_కొలత;

        ఒకవేళ (బహిర్గతం_buf_కొలత)
        {
          ఒకవేళ (pCallback(pOpaque, బహిర్గతం_buf_ofs, pWrite_buf_cur, బహిర్గతం_buf_కొలత) != బహిర్గతం_buf_కొలత)
          {
            స్థితి_2 = TINFL_స్థితి_FAILED;
            ఆపు;
          }
          file_చక్రీయ_తనిఖీ_32 = (mz_uint32)mz_చక్రీయ_తనిఖీ_32(file_చక్రీయ_తనిఖీ_32, pWrite_buf_cur, బహిర్గతం_buf_కొలత);
          ఒకవేళ ((బహిర్గతం_buf_ofs += బహిర్గతం_buf_కొలత) > file_stat.m_uncomp_కొలత)
          {
            స్థితి_2 = TINFL_స్థితి_FAILED;
            ఆపు;
          }
        }
      } అయితే ((స్థితి_2 == TINFL_స్థితి_NEEDS_మరిన్ని_ఆదానం) || (స్థితి_2 == TINFL_స్థితి_HAS_మరిన్ని_OUTPUT));
    }
  }

  ఒకవేళ ((స్థితి_2 == TINFL_స్థితి_పూర్తి) && (!(flags & MZ_ZIP_FLAG_COMPRESSED_దత్తాంశం)))
  {
    // Make sure the entire file was decompressed, and check its CRC.
    ఒకవేళ ((బహిర్గతం_buf_ofs != file_stat.m_uncomp_కొలత) || (file_చక్రీయ_తనిఖీ_32 != file_stat.m_చక్రీయ_తనిఖీ_32))
      స్థితి_2 = TINFL_స్థితి_FAILED;
  }

  ఒకవేళ (!pZip->m_pState->m_pMem)
    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
  ఒకవేళ (pWrite_buf)
    pZip->m_pFree(pZip->m_pAlloc_opaque, pWrite_buf);

  తిరిగి స్థితి_2 == TINFL_స్థితి_పూర్తి;
}

mz_bool mz_zip_reader_వెలికితీయి_file_గమ్యం_callback(mz_zip_archive *pZip, స్థిరరాశి అక్షరం *pFilename, mz_file_write_func pCallback, శూన్య *pOpaque, mz_uint flags)
{
  పూర్ణాంకం file_సూచీ = mz_zip_reader_locate_file(pZip, pFilename, ఖాళీ, flags);
  ఒకవేళ (file_సూచీ < 0)
    తిరిగి MZ_FALSE;
  తిరిగి mz_zip_reader_వెలికితీయి_గమ్యం_callback(pZip, file_సూచీ, pCallback, pOpaque, flags);
}

#నిర్వచితం_కాకపోతే MINIZ_NO_STDIO
స్థిర size_t mz_zip_file_write_callback(శూన్య *pOpaque, mz_uint64 ofs, స్థిరరాశి శూన్య *pBuf, size_t n)
{
  (శూన్య)ofs; తిరిగి MZ_FWRITE(pBuf, 1, n, (MZ_FILE*)pOpaque);
}

mz_bool mz_zip_reader_వెలికితీయి_గమ్యం_file(mz_zip_archive *pZip, mz_uint file_సూచీ, స్థిరరాశి అక్షరం *pDst_filename, mz_uint flags)
{
  mz_bool స్థితి_2;
  mz_zip_archive_file_stat file_stat;
  MZ_FILE *pFile;
  ఒకవేళ (!mz_zip_reader_file_stat(pZip, file_సూచీ, &file_stat))
    తిరిగి MZ_FALSE;
  pFile = MZ_FOPEN(pDst_filename, "wb");
  ఒకవేళ (!pFile)
    తిరిగి MZ_FALSE;
  స్థితి_2 = mz_zip_reader_వెలికితీయి_గమ్యం_callback(pZip, file_సూచీ, mz_zip_file_write_callback, pFile, flags);
  ఒకవేళ (MZ_FCLOSE(pFile) == EOF)
    తిరిగి MZ_FALSE;
#నిర్వచితం_కాకపోతే MINIZ_NO_సమయం
  ఒకవేళ (స్థితి_2)
    mz_zip_సమితి_file_times(pDst_filename, file_stat.m_సమయం, file_stat.m_సమయం);
#అయితే_ముగింపు
  తిరిగి స్థితి_2;
}
#అయితే_ముగింపు // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_reader_చివర(mz_zip_archive *pZip)
{
  ఒకవేళ ((!pZip) || (!pZip->m_pState) || (!pZip->m_pAlloc) || (!pZip->m_pFree) || (pZip->m_zip_బహుళకం != MZ_ZIP_బహుళకం_READING))
    తిరిగి MZ_FALSE;

  ఒకవేళ (pZip->m_pState)
  {
    mz_zip_అంతర్గత_state *pState = pZip->m_pState; pZip->m_pState = ఖాళీ;
    mz_zip_array_clear(pZip, &pState->m_central_dir);
    mz_zip_array_clear(pZip, &pState->m_central_dir_offsets);
    mz_zip_array_clear(pZip, &pState->m_sorted_central_dir_offsets);

#నిర్వచితం_కాకపోతే MINIZ_NO_STDIO
    ఒకవేళ (pState->m_pFile)
    {
      MZ_FCLOSE(pState->m_pFile);
      pState->m_pFile = ఖాళీ;
    }
#అయితే_ముగింపు // #ifndef MINIZ_NO_STDIO

    pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
  }
  pZip->m_zip_బహుళకం = MZ_ZIP_బహుళకం_INVALID;

  తిరిగి MZ_TRUE;
}

#నిర్వచితం_కాకపోతే MINIZ_NO_STDIO
mz_bool mz_zip_reader_వెలికితీయి_file_గమ్యం_file(mz_zip_archive *pZip, స్థిరరాశి అక్షరం *pArchive_filename, స్థిరరాశి అక్షరం *pDst_filename, mz_uint flags)
{
  పూర్ణాంకం file_సూచీ = mz_zip_reader_locate_file(pZip, pArchive_filename, ఖాళీ, flags);
  ఒకవేళ (file_సూచీ < 0)
    తిరిగి MZ_FALSE;
  తిరిగి mz_zip_reader_వెలికితీయి_గమ్యం_file(pZip, file_సూచీ, pDst_filename, flags);
}
#అయితే_ముగింపు

// ------------------- .ZIP archive writing

#నిర్వచితం_కాకపోతే MINIZ_NO_ARCHIVE_WRITING_APIS

స్థిర శూన్య mz_write_le16(mz_uint8 *p, mz_uint16 v) { p[0] = (mz_uint8)v; p[1] = (mz_uint8)(v >> 8); }
స్థిర శూన్య mz_write_le32(mz_uint8 *p, mz_uint32 v) { p[0] = (mz_uint8)v; p[1] = (mz_uint8)(v >> 8); p[2] = (mz_uint8)(v >> 16); p[3] = (mz_uint8)(v >> 24); }
#నిర్వచించు MZ_WRITE_LE16(p, v) mz_write_le16((mz_uint8 *)(p), (mz_uint16)(v))
#నిర్వచించు MZ_WRITE_LE32(p, v) mz_write_le32((mz_uint8 *)(p), (mz_uint32)(v))

mz_bool mz_zip_writer_init(mz_zip_archive *pZip, mz_uint64 existing_కొలత)
{
  ఒకవేళ ((!pZip) || (pZip->m_pState) || (!pZip->m_pWrite) || (pZip->m_zip_బహుళకం != MZ_ZIP_బహుళకం_INVALID))
    తిరిగి MZ_FALSE;

  ఒకవేళ (pZip->m_file_స్థానభ్రంశం_alignment)
  {
    // Ensure user specified file offset alignment is a power of 2.
    ఒకవేళ (pZip->m_file_స్థానభ్రంశం_alignment & (pZip->m_file_స్థానభ్రంశం_alignment - 1))
      తిరిగి MZ_FALSE;
  }

  ఒకవేళ (!pZip->m_pAlloc) pZip->m_pAlloc = def_alloc_func;
  ఒకవేళ (!pZip->m_pFree) pZip->m_pFree = def_free_func;
  ఒకవేళ (!pZip->m_pRealloc) pZip->m_pRealloc = def_realloc_func;

  pZip->m_zip_బహుళకం = MZ_ZIP_బహుళకం_WRITING;
  pZip->m_archive_కొలత = existing_కొలత;
  pZip->m_central_directory_file_ofs = 0;
  pZip->m_మొత్తం_files = 0;

  ఒకవేళ (ఖాళీ == (pZip->m_pState = (mz_zip_అంతర్గత_state *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, పరిమాణం(mz_zip_అంతర్గత_state))))
    తిరిగి MZ_FALSE;
  memset(pZip->m_pState, 0, పరిమాణం(mz_zip_అంతర్గత_state));
  MZ_ZIP_ARRAY_సమితి_ELEMENT_కొలత(&pZip->m_pState->m_central_dir, పరిమాణం(mz_uint8));
  MZ_ZIP_ARRAY_సమితి_ELEMENT_కొలత(&pZip->m_pState->m_central_dir_offsets, పరిమాణం(mz_uint32));
  MZ_ZIP_ARRAY_సమితి_ELEMENT_కొలత(&pZip->m_pState->m_sorted_central_dir_offsets, పరిమాణం(mz_uint32));
  తిరిగి MZ_TRUE;
}

స్థిర size_t mz_zip_కుప్ప_write_func(శూన్య *pOpaque, mz_uint64 file_ofs, స్థిరరాశి శూన్య *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_zip_అంతర్గత_state *pState = pZip->m_pState;
  mz_uint64 new_కొలత = MZ_MAX(file_ofs + n, pState->m_mem_కొలత);
#నిర్వచితమైతే _MSC_VER
  ఒకవేళ ((!n) || ((0, పరిమాణం(size_t) == పరిమాణం(mz_uint32)) && (new_కొలత > 0x7FFFFFFF)))
#లేకపోతే
  ఒకవేళ ((!n) || ((పరిమాణం(size_t) == పరిమాణం(mz_uint32)) && (new_కొలత > 0x7FFFFFFF)))
#అయితే_ముగింపు
    తిరిగి 0;
  ఒకవేళ (new_కొలత > pState->m_mem_సామర్థ్యం)
  {
    శూన్య *p_New_ఖండం;
    size_t new_సామర్థ్యం = MZ_MAX(64, pState->m_mem_సామర్థ్యం); అయితే (new_సామర్థ్యం < new_కొలత) new_సామర్థ్యం *= 2;
    ఒకవేళ (ఖాళీ == (p_New_ఖండం = pZip->m_pRealloc(pZip->m_pAlloc_opaque, pState->m_pMem, 1, new_సామర్థ్యం)))
      తిరిగి 0;
    pState->m_pMem = p_New_ఖండం; pState->m_mem_సామర్థ్యం = new_సామర్థ్యం;
  }
  జ్ఞాపకం_నకలు((mz_uint8 *)pState->m_pMem + file_ofs, pBuf, n);
  pState->m_mem_కొలత = (size_t)new_కొలత;
  తిరిగి n;
}

mz_bool mz_zip_writer_init_కుప్ప(mz_zip_archive *pZip, size_t కొలత_గమ్యం_reserve_at_beginning, size_t initial_కేటాయింపు_కొలత)
{
  pZip->m_pWrite = mz_zip_కుప్ప_write_func;
  pZip->m_pIO_opaque = pZip;
  ఒకవేళ (!mz_zip_writer_init(pZip, కొలత_గమ్యం_reserve_at_beginning))
    తిరిగి MZ_FALSE;
  ఒకవేళ (0 != (initial_కేటాయింపు_కొలత = MZ_MAX(initial_కేటాయింపు_కొలత, కొలత_గమ్యం_reserve_at_beginning)))
  {
    ఒకవేళ (ఖాళీ == (pZip->m_pState->m_pMem = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, initial_కేటాయింపు_కొలత)))
    {
      mz_zip_writer_చివర(pZip);
      తిరిగి MZ_FALSE;
    }
    pZip->m_pState->m_mem_సామర్థ్యం = initial_కేటాయింపు_కొలత;
  }
  తిరిగి MZ_TRUE;
}

#నిర్వచితం_కాకపోతే MINIZ_NO_STDIO
స్థిర size_t mz_zip_file_write_func(శూన్య *pOpaque, mz_uint64 file_ofs, స్థిరరాశి శూన్య *pBuf, size_t n)
{
  mz_zip_archive *pZip = (mz_zip_archive *)pOpaque;
  mz_int64 cur_ofs = MZ_FTELL64(pZip->m_pState->m_pFile);
  ఒకవేళ (((mz_int64)file_ofs < 0) || (((cur_ofs != (mz_int64)file_ofs)) && (MZ_FSEEK64(pZip->m_pState->m_pFile, (mz_int64)file_ofs, SEEK_SET))))
    తిరిగి 0;
  తిరిగి MZ_FWRITE(pBuf, 1, n, pZip->m_pState->m_pFile);
}

mz_bool mz_zip_writer_init_file(mz_zip_archive *pZip, స్థిరరాశి అక్షరం *pFilename, mz_uint64 కొలత_గమ్యం_reserve_at_beginning)
{
  MZ_FILE *pFile;
  pZip->m_pWrite = mz_zip_file_write_func;
  pZip->m_pIO_opaque = pZip;
  ఒకవేళ (!mz_zip_writer_init(pZip, కొలత_గమ్యం_reserve_at_beginning))
    తిరిగి MZ_FALSE;
  ఒకవేళ (ఖాళీ == (pFile = MZ_FOPEN(pFilename, "wb")))
  {
    mz_zip_writer_చివర(pZip);
    తిరిగి MZ_FALSE;
  }
  pZip->m_pState->m_pFile = pFile;
  ఒకవేళ (కొలత_గమ్యం_reserve_at_beginning)
  {
    mz_uint64 cur_ofs = 0; అక్షరం buf[4096]; MZ_CLEAR_ARR(buf);
    చేయి
    {
      size_t n = (size_t)MZ_MIN(పరిమాణం(buf), కొలత_గమ్యం_reserve_at_beginning);
      ఒకవేళ (pZip->m_pWrite(pZip->m_pIO_opaque, cur_ofs, buf, n) != n)
      {
        mz_zip_writer_చివర(pZip);
        తిరిగి MZ_FALSE;
      }
      cur_ofs += n; కొలత_గమ్యం_reserve_at_beginning -= n;
    } అయితే (కొలత_గమ్యం_reserve_at_beginning);
  }
  తిరిగి MZ_TRUE;
}
#అయితే_ముగింపు // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_writer_init_from_reader(mz_zip_archive *pZip, స్థిరరాశి అక్షరం *pFilename)
{
  mz_zip_అంతర్గత_state *pState;
  ఒకవేళ ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_బహుళకం != MZ_ZIP_బహుళకం_READING))
    తిరిగి MZ_FALSE;
  // No sense in trying to write to an archive that's already at the support max size
  ఒకవేళ ((pZip->m_మొత్తం_files == 0xFFFF) || ((pZip->m_archive_కొలత + MZ_ZIP_CENTRAL_DIR_శీర్షిక_కొలత + MZ_ZIP_LOCAL_DIR_శీర్షిక_కొలత) > 0xFFFFFFFF))
    తిరిగి MZ_FALSE;

  pState = pZip->m_pState;

  ఒకవేళ (pState->m_pFile)
  {
#నిర్వచితమైతే MINIZ_NO_STDIO
    pFilename; తిరిగి MZ_FALSE;
#లేకపోతే
    // Archive is being read from stdio - try to reopen as writable.
    ఒకవేళ (pZip->m_pIO_opaque != pZip)
      తిరిగి MZ_FALSE;
    ఒకవేళ (!pFilename)
      తిరిగి MZ_FALSE;
    pZip->m_pWrite = mz_zip_file_write_func;
    ఒకవేళ (ఖాళీ == (pState->m_pFile = MZ_FREOPEN(pFilename, "r+b", pState->m_pFile)))
    {
      // The mz_zip_archive is now in a bogus state because pState->m_pFile is NULL, so just close it.
      mz_zip_reader_చివర(pZip);
      తిరిగి MZ_FALSE;
    }
#అయితే_ముగింపు // #ifdef MINIZ_NO_STDIO
  }
  లేకపోతే ఒకవేళ (pState->m_pMem)
  {
    // Archive lives in a memory block. Assume it's from the heap that we can resize using the realloc callback.
    ఒకవేళ (pZip->m_pIO_opaque != pZip)
      తిరిగి MZ_FALSE;
    pState->m_mem_సామర్థ్యం = pState->m_mem_కొలత;
    pZip->m_pWrite = mz_zip_కుప్ప_write_func;
  }
  // Archive is being read via a user provided read function - make sure the user has specified a write function too.
  లేకపోతే ఒకవేళ (!pZip->m_pWrite)
    తిరిగి MZ_FALSE;

  // Start writing new files at the archive's current central directory location.
  pZip->m_archive_కొలత = pZip->m_central_directory_file_ofs;
  pZip->m_zip_బహుళకం = MZ_ZIP_బహుళకం_WRITING;
  pZip->m_central_directory_file_ofs = 0;

  తిరిగి MZ_TRUE;
}

mz_bool mz_zip_writer_కూడు_mem(mz_zip_archive *pZip, స్థిరరాశి అక్షరం *pArchive_name, స్థిరరాశి శూన్య *pBuf, size_t buf_కొలత_2, mz_uint level_and_flags)
{
  తిరిగి mz_zip_writer_కూడు_mem_ex(pZip, pArchive_name, pBuf, buf_కొలత_2, ఖాళీ, 0, level_and_flags, 0, 0);
}

రకనిర్వచనం నిర్మాణం
{
  mz_zip_archive *m_pZip;
  mz_uint64 m_cur_archive_file_ofs;
  mz_uint64 m_comp_కొలత;
} mz_zip_writer_కూడు_state;

స్థిర mz_bool mz_zip_writer_కూడు_put_buf_callback(స్థిరరాశి శూన్య* pBuf, పూర్ణాంకం len, శూన్య *pUser)
{
  mz_zip_writer_కూడు_state *pState = (mz_zip_writer_కూడు_state *)pUser;
  ఒకవేళ ((పూర్ణాంకం)pState->m_pZip->m_pWrite(pState->m_pZip->m_pIO_opaque, pState->m_cur_archive_file_ofs, pBuf, len) != len)
    తిరిగి MZ_FALSE;
  pState->m_cur_archive_file_ofs += len;
  pState->m_comp_కొలత += len;
  తిరిగి MZ_TRUE;
}

స్థిర mz_bool mz_zip_writer_create_local_dir_శీర్షిక(mz_zip_archive *pZip, mz_uint8 *pDst, mz_uint16 filename_కొలత, mz_uint16 extra_కొలత, mz_uint64 uncomp_కొలత, mz_uint64 comp_కొలత, mz_uint32 uncomp_చక్రీయ_తనిఖీ_32, mz_uint16 పద్ధతి, mz_uint16 బిట్టు_flags, mz_uint16 dos_సమయం, mz_uint16 dos_date)
{
  (శూన్య)pZip;
  memset(pDst, 0, MZ_ZIP_LOCAL_DIR_శీర్షిక_కొలత);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_SIG_OFS, MZ_ZIP_LOCAL_DIR_శీర్షిక_SIG);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_సంస్కరణ_NEEDED_OFS, పద్ధతి ? 20 : 0);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_బిట్టు_FLAG_OFS, బిట్టు_flags);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_పద్ధతి_OFS, పద్ధతి);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILE_సమయం_OFS, dos_సమయం);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILE_DATE_OFS, dos_date);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_చక్రీయ_తనిఖీ_32_OFS, uncomp_చక్రీయ_తనిఖీ_32);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_COMPRESSED_కొలత_OFS, comp_కొలత);
  MZ_WRITE_LE32(pDst + MZ_ZIP_LDH_DECOMPRESSED_కొలత_OFS, uncomp_కొలత);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_FILENAME_LEN_OFS, filename_కొలత);
  MZ_WRITE_LE16(pDst + MZ_ZIP_LDH_EXTRA_LEN_OFS, extra_కొలత);
  తిరిగి MZ_TRUE;
}

స్థిర mz_bool mz_zip_writer_create_central_dir_శీర్షిక(mz_zip_archive *pZip, mz_uint8 *pDst, mz_uint16 filename_కొలత, mz_uint16 extra_కొలత, mz_uint16 comment_కొలత, mz_uint64 uncomp_కొలత, mz_uint64 comp_కొలత, mz_uint32 uncomp_చక్రీయ_తనిఖీ_32, mz_uint16 పద్ధతి, mz_uint16 బిట్టు_flags, mz_uint16 dos_సమయం, mz_uint16 dos_date, mz_uint64 local_శీర్షిక_ofs, mz_uint32 ext_లక్షణాలు)
{
  (శూన్య)pZip;
  memset(pDst, 0, MZ_ZIP_CENTRAL_DIR_శీర్షిక_కొలత);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_SIG_OFS, MZ_ZIP_CENTRAL_DIR_శీర్షిక_SIG);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_సంస్కరణ_NEEDED_OFS, పద్ధతి ? 20 : 0);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_బిట్టు_FLAG_OFS, బిట్టు_flags);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_పద్ధతి_OFS, పద్ధతి);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILE_సమయం_OFS, dos_సమయం);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILE_DATE_OFS, dos_date);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_చక్రీయ_తనిఖీ_32_OFS, uncomp_చక్రీయ_తనిఖీ_32);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_COMPRESSED_కొలత_OFS, comp_కొలత);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_DECOMPRESSED_కొలత_OFS, uncomp_కొలత);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_FILENAME_LEN_OFS, filename_కొలత);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_EXTRA_LEN_OFS, extra_కొలత);
  MZ_WRITE_LE16(pDst + MZ_ZIP_CDH_COMMENT_LEN_OFS, comment_కొలత);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_EXTERNAL_ATTR_OFS, ext_లక్షణాలు);
  MZ_WRITE_LE32(pDst + MZ_ZIP_CDH_LOCAL_శీర్షిక_OFS, local_శీర్షిక_ofs);
  తిరిగి MZ_TRUE;
}

స్థిర mz_bool mz_zip_writer_కూడు_గమ్యం_central_dir(mz_zip_archive *pZip, స్థిరరాశి అక్షరం *pFilename, mz_uint16 filename_కొలత, స్థిరరాశి శూన్య *pExtra, mz_uint16 extra_కొలత, స్థిరరాశి శూన్య *pComment, mz_uint16 comment_కొలత, mz_uint64 uncomp_కొలత, mz_uint64 comp_కొలత, mz_uint32 uncomp_చక్రీయ_తనిఖీ_32, mz_uint16 పద్ధతి, mz_uint16 బిట్టు_flags, mz_uint16 dos_సమయం, mz_uint16 dos_date, mz_uint64 local_శీర్షిక_ofs, mz_uint32 ext_లక్షణాలు)
{
  mz_zip_అంతర్గత_state *pState = pZip->m_pState;
  mz_uint32 central_dir_ofs = (mz_uint32)pState->m_central_dir.m_కొలత;
  size_t orig_central_dir_కొలత = pState->m_central_dir.m_కొలత;
  mz_uint8 central_dir_శీర్షిక[MZ_ZIP_CENTRAL_DIR_శీర్షిక_కొలత];

  // No zip64 support yet
  ఒకవేళ ((local_శీర్షిక_ofs > 0xFFFFFFFF) || (((mz_uint64)pState->m_central_dir.m_కొలత + MZ_ZIP_CENTRAL_DIR_శీర్షిక_కొలత + filename_కొలత + extra_కొలత + comment_కొలత) > 0xFFFFFFFF))
    తిరిగి MZ_FALSE;

  ఒకవేళ (!mz_zip_writer_create_central_dir_శీర్షిక(pZip, central_dir_శీర్షిక, filename_కొలత, extra_కొలత, comment_కొలత, uncomp_కొలత, comp_కొలత, uncomp_చక్రీయ_తనిఖీ_32, పద్ధతి, బిట్టు_flags, dos_సమయం, dos_date, local_శీర్షిక_ofs, ext_లక్షణాలు))
    తిరిగి MZ_FALSE;

  ఒకవేళ ((!mz_zip_array_నెట్టు_వెనుక(pZip, &pState->m_central_dir, central_dir_శీర్షిక, MZ_ZIP_CENTRAL_DIR_శీర్షిక_కొలత)) ||
      (!mz_zip_array_నెట్టు_వెనుక(pZip, &pState->m_central_dir, pFilename, filename_కొలత)) ||
      (!mz_zip_array_నెట్టు_వెనుక(pZip, &pState->m_central_dir, pExtra, extra_కొలత)) ||
      (!mz_zip_array_నెట్టు_వెనుక(pZip, &pState->m_central_dir, pComment, comment_కొలత)) ||
      (!mz_zip_array_నెట్టు_వెనుక(pZip, &pState->m_central_dir_offsets, &central_dir_ofs, 1)))
  {
    // Try to push the central directory array back into its original state.
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_కొలత, MZ_FALSE);
    తిరిగి MZ_FALSE;
  }

  తిరిగి MZ_TRUE;
}

స్థిర mz_bool mz_zip_writer_validate_archive_name(స్థిరరాశి అక్షరం *pArchive_name)
{
  // Basic ZIP archive filename validity checks: Valid filenames cannot start with a forward slash, cannot contain a drive letter, and cannot use DOS-style backward slashes.
  ఒకవేళ (*pArchive_name == '/')
    తిరిగి MZ_FALSE;
  అయితే (*pArchive_name)
  {
    ఒకవేళ ((*pArchive_name == '\\') || (*pArchive_name == ':'))
      తిరిగి MZ_FALSE;
    pArchive_name++;
  }
  తిరిగి MZ_TRUE;
}

స్థిర mz_uint mz_zip_writer_compute_padding_needed_for_file_alignment(mz_zip_archive *pZip)
{
  mz_uint32 n;
  ఒకవేళ (!pZip->m_file_స్థానభ్రంశం_alignment)
    తిరిగి 0;
  n = (mz_uint32)(pZip->m_archive_కొలత & (pZip->m_file_స్థానభ్రంశం_alignment - 1));
  తిరిగి (pZip->m_file_స్థానభ్రంశం_alignment - n) & (pZip->m_file_స్థానభ్రంశం_alignment - 1);
}

స్థిర mz_bool mz_zip_writer_write_zeros(mz_zip_archive *pZip, mz_uint64 cur_file_ofs, mz_uint32 n)
{
  అక్షరం buf[4096];
  memset(buf, 0, MZ_MIN(పరిమాణం(buf), n));
  అయితే (n)
  {
    mz_uint32 s = MZ_MIN(పరిమాణం(buf), n);
    ఒకవేళ (pZip->m_pWrite(pZip->m_pIO_opaque, cur_file_ofs, buf, s) != s)
      తిరిగి MZ_FALSE;
    cur_file_ofs += s; n -= s;
  }
  తిరిగి MZ_TRUE;
}

mz_bool mz_zip_writer_కూడు_mem_ex(mz_zip_archive *pZip, స్థిరరాశి అక్షరం *pArchive_name, స్థిరరాశి శూన్య *pBuf, size_t buf_కొలత_2, స్థిరరాశి శూన్య *pComment, mz_uint16 comment_కొలత, mz_uint level_and_flags, mz_uint64 uncomp_కొలత, mz_uint32 uncomp_చక్రీయ_తనిఖీ_32)
{
  mz_uint16 పద్ధతి = 0, dos_సమయం = 0, dos_date = 0;
  mz_uint level, ext_లక్షణాలు = 0, అంకె_alignment_padding_బైట్లు;
  mz_uint64 local_dir_శీర్షిక_ofs = pZip->m_archive_కొలత, cur_archive_file_ofs = pZip->m_archive_కొలత, comp_కొలత = 0;
  size_t archive_name_కొలత;
  mz_uint8 local_dir_శీర్షిక[MZ_ZIP_LOCAL_DIR_శీర్షిక_కొలత];
  tdefl_compressor *pComp = ఖాళీ;
  mz_bool store_దత్తాంశం_uncompressed;
  mz_zip_అంతర్గత_state *pState;

  ఒకవేళ ((పూర్ణాంకం)level_and_flags < 0)
    level_and_flags = MZ_DEFAULT_LEVEL;
  level = level_and_flags & 0xF;
  store_దత్తాంశం_uncompressed = ((!level) || (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_దత్తాంశం));

  ఒకవేళ ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_బహుళకం != MZ_ZIP_బహుళకం_WRITING) || ((buf_కొలత_2) && (!pBuf)) || (!pArchive_name) || ((comment_కొలత) && (!pComment)) || (pZip->m_మొత్తం_files == 0xFFFF) || (level > MZ_UBER_COMPRESSION))
    తిరిగి MZ_FALSE;

  pState = pZip->m_pState;

  ఒకవేళ ((!(level_and_flags & MZ_ZIP_FLAG_COMPRESSED_దత్తాంశం)) && (uncomp_కొలత))
    తిరిగి MZ_FALSE;
  // No zip64 support yet
  ఒకవేళ ((buf_కొలత_2 > 0xFFFFFFFF) || (uncomp_కొలత > 0xFFFFFFFF))
    తిరిగి MZ_FALSE;
  ఒకవేళ (!mz_zip_writer_validate_archive_name(pArchive_name))
    తిరిగి MZ_FALSE;

#నిర్వచితం_కాకపోతే MINIZ_NO_సమయం
  {
    సమయం_t cur_సమయం; సమయం(&cur_సమయం);
    mz_zip_సమయం_గమ్యం_dos_సమయం(cur_సమయం, &dos_సమయం, &dos_date);
  }
#అయితే_ముగింపు // #ifndef MINIZ_NO_TIME

  archive_name_కొలత = అక్షరశ్రేణి_పొడవు(pArchive_name);
  ఒకవేళ (archive_name_కొలత > 0xFFFF)
    తిరిగి MZ_FALSE;

  అంకె_alignment_padding_బైట్లు = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  ఒకవేళ ((pZip->m_మొత్తం_files == 0xFFFF) || ((pZip->m_archive_కొలత + అంకె_alignment_padding_బైట్లు + MZ_ZIP_LOCAL_DIR_శీర్షిక_కొలత + MZ_ZIP_CENTRAL_DIR_శీర్షిక_కొలత + comment_కొలత + archive_name_కొలత) > 0xFFFFFFFF))
    తిరిగి MZ_FALSE;

  ఒకవేళ ((archive_name_కొలత) && (pArchive_name[archive_name_కొలత - 1] == '/'))
  {
    // Set DOS Subdirectory attribute bit.
    ext_లక్షణాలు |= 0x10;
    // Subdirectories cannot contain data.
    ఒకవేళ ((buf_కొలత_2) || (uncomp_కొలత))
      తిరిగి MZ_FALSE;
  }

  // Try to do any allocations before writing to the archive, so if an allocation fails the file remains unmodified. (A good idea if we're doing an in-place modification.)
  ఒకవేళ ((!mz_zip_array_ensure_స్థలం(pZip, &pState->m_central_dir, MZ_ZIP_CENTRAL_DIR_శీర్షిక_కొలత + archive_name_కొలత + comment_కొలత)) || (!mz_zip_array_ensure_స్థలం(pZip, &pState->m_central_dir_offsets, 1)))
    తిరిగి MZ_FALSE;

  ఒకవేళ ((!store_దత్తాంశం_uncompressed) && (buf_కొలత_2))
  {
    ఒకవేళ (ఖాళీ == (pComp = (tdefl_compressor *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, పరిమాణం(tdefl_compressor))))
      తిరిగి MZ_FALSE;
  }

  ఒకవేళ (!mz_zip_writer_write_zeros(pZip, cur_archive_file_ofs, అంకె_alignment_padding_బైట్లు + పరిమాణం(local_dir_శీర్షిక)))
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
    తిరిగి MZ_FALSE;
  }
  local_dir_శీర్షిక_ofs += అంకె_alignment_padding_బైట్లు;
  ఒకవేళ (pZip->m_file_స్థానభ్రంశం_alignment) { MZ_ASSERT((local_dir_శీర్షిక_ofs & (pZip->m_file_స్థానభ్రంశం_alignment - 1)) == 0); }
  cur_archive_file_ofs += అంకె_alignment_padding_బైట్లు + పరిమాణం(local_dir_శీర్షిక);

  MZ_CLEAR_ARR(local_dir_శీర్షిక);
  ఒకవేళ (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pArchive_name, archive_name_కొలత) != archive_name_కొలత)
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
    తిరిగి MZ_FALSE;
  }
  cur_archive_file_ofs += archive_name_కొలత;

  ఒకవేళ (!(level_and_flags & MZ_ZIP_FLAG_COMPRESSED_దత్తాంశం))
  {
    uncomp_చక్రీయ_తనిఖీ_32 = (mz_uint32)mz_చక్రీయ_తనిఖీ_32(MZ_చక్రీయ_తనిఖీ_32_INIT, (స్థిరరాశి mz_uint8*)pBuf, buf_కొలత_2);
    uncomp_కొలత = buf_కొలత_2;
    ఒకవేళ (uncomp_కొలత <= 3)
    {
      level = 0;
      store_దత్తాంశం_uncompressed = MZ_TRUE;
    }
  }

  ఒకవేళ (store_దత్తాంశం_uncompressed)
  {
    ఒకవేళ (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pBuf, buf_కొలత_2) != buf_కొలత_2)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
      తిరిగి MZ_FALSE;
    }

    cur_archive_file_ofs += buf_కొలత_2;
    comp_కొలత = buf_కొలత_2;

    ఒకవేళ (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_దత్తాంశం)
      పద్ధతి = MZ_DEFLATED;
  }
  లేకపోతే ఒకవేళ (buf_కొలత_2)
  {
    mz_zip_writer_కూడు_state state;

    state.m_pZip = pZip;
    state.m_cur_archive_file_ofs = cur_archive_file_ofs;
    state.m_comp_కొలత = 0;

    ఒకవేళ ((tdefl_init(pComp, mz_zip_writer_కూడు_put_buf_callback, &state, tdefl_create_comp_flags_from_zip_params(level, -15, MZ_DEFAULT_STRATEGY)) != TDEFL_స్థితి_OKAY) ||
        (tdefl_compress_బఫరు(pComp, pBuf, buf_కొలత_2, TDEFL_ముగింపు) != TDEFL_స్థితి_పూర్తి))
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
      తిరిగి MZ_FALSE;
    }

    comp_కొలత = state.m_comp_కొలత;
    cur_archive_file_ofs = state.m_cur_archive_file_ofs;

    పద్ధతి = MZ_DEFLATED;
  }

  pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
  pComp = ఖాళీ;

  // no zip64 support yet
  ఒకవేళ ((comp_కొలత > 0xFFFFFFFF) || (cur_archive_file_ofs > 0xFFFFFFFF))
    తిరిగి MZ_FALSE;

  ఒకవేళ (!mz_zip_writer_create_local_dir_శీర్షిక(pZip, local_dir_శీర్షిక, (mz_uint16)archive_name_కొలత, 0, uncomp_కొలత, comp_కొలత, uncomp_చక్రీయ_తనిఖీ_32, పద్ధతి, 0, dos_సమయం, dos_date))
    తిరిగి MZ_FALSE;

  ఒకవేళ (pZip->m_pWrite(pZip->m_pIO_opaque, local_dir_శీర్షిక_ofs, local_dir_శీర్షిక, పరిమాణం(local_dir_శీర్షిక)) != పరిమాణం(local_dir_శీర్షిక))
    తిరిగి MZ_FALSE;

  ఒకవేళ (!mz_zip_writer_కూడు_గమ్యం_central_dir(pZip, pArchive_name, (mz_uint16)archive_name_కొలత, ఖాళీ, 0, pComment, comment_కొలత, uncomp_కొలత, comp_కొలత, uncomp_చక్రీయ_తనిఖీ_32, పద్ధతి, 0, dos_సమయం, dos_date, local_dir_శీర్షిక_ofs, ext_లక్షణాలు))
    తిరిగి MZ_FALSE;

  pZip->m_మొత్తం_files++;
  pZip->m_archive_కొలత = cur_archive_file_ofs;

  తిరిగి MZ_TRUE;
}

#నిర్వచితం_కాకపోతే MINIZ_NO_STDIO
mz_bool mz_zip_writer_కూడు_file(mz_zip_archive *pZip, స్థిరరాశి అక్షరం *pArchive_name, స్థిరరాశి అక్షరం *pSrc_filename, స్థిరరాశి శూన్య *pComment, mz_uint16 comment_కొలత, mz_uint level_and_flags)
{
  mz_uint uncomp_చక్రీయ_తనిఖీ_32 = MZ_చక్రీయ_తనిఖీ_32_INIT, level, అంకె_alignment_padding_బైట్లు;
  mz_uint16 పద్ధతి = 0, dos_సమయం = 0, dos_date = 0, ext_లక్షణాలు = 0;
  mz_uint64 local_dir_శీర్షిక_ofs = pZip->m_archive_కొలత, cur_archive_file_ofs = pZip->m_archive_కొలత, uncomp_కొలత = 0, comp_కొలత = 0;
  size_t archive_name_కొలత;
  mz_uint8 local_dir_శీర్షిక[MZ_ZIP_LOCAL_DIR_శీర్షిక_కొలత];
  MZ_FILE *pSrc_file = ఖాళీ;

  ఒకవేళ ((పూర్ణాంకం)level_and_flags < 0)
    level_and_flags = MZ_DEFAULT_LEVEL;
  level = level_and_flags & 0xF;

  ఒకవేళ ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_బహుళకం != MZ_ZIP_బహుళకం_WRITING) || (!pArchive_name) || ((comment_కొలత) && (!pComment)) || (level > MZ_UBER_COMPRESSION))
    తిరిగి MZ_FALSE;
  ఒకవేళ (level_and_flags & MZ_ZIP_FLAG_COMPRESSED_దత్తాంశం)
    తిరిగి MZ_FALSE;
  ఒకవేళ (!mz_zip_writer_validate_archive_name(pArchive_name))
    తిరిగి MZ_FALSE;

  archive_name_కొలత = అక్షరశ్రేణి_పొడవు(pArchive_name);
  ఒకవేళ (archive_name_కొలత > 0xFFFF)
    తిరిగి MZ_FALSE;

  అంకె_alignment_padding_బైట్లు = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  ఒకవేళ ((pZip->m_మొత్తం_files == 0xFFFF) || ((pZip->m_archive_కొలత + అంకె_alignment_padding_బైట్లు + MZ_ZIP_LOCAL_DIR_శీర్షిక_కొలత + MZ_ZIP_CENTRAL_DIR_శీర్షిక_కొలత + comment_కొలత + archive_name_కొలత) > 0xFFFFFFFF))
    తిరిగి MZ_FALSE;

  ఒకవేళ (!mz_zip_get_file_modified_సమయం(pSrc_filename, &dos_సమయం, &dos_date))
    తిరిగి MZ_FALSE;

  pSrc_file = MZ_FOPEN(pSrc_filename, "rb");
  ఒకవేళ (!pSrc_file)
    తిరిగి MZ_FALSE;
  MZ_FSEEK64(pSrc_file, 0, SEEK_END);
  uncomp_కొలత = MZ_FTELL64(pSrc_file);
  MZ_FSEEK64(pSrc_file, 0, SEEK_SET);

  ఒకవేళ (uncomp_కొలత > 0xFFFFFFFF)
  {
    // No zip64 support yet
    MZ_FCLOSE(pSrc_file);
    తిరిగి MZ_FALSE;
  }
  ఒకవేళ (uncomp_కొలత <= 3)
    level = 0;

  ఒకవేళ (!mz_zip_writer_write_zeros(pZip, cur_archive_file_ofs, అంకె_alignment_padding_బైట్లు + పరిమాణం(local_dir_శీర్షిక)))
  {
    MZ_FCLOSE(pSrc_file);
    తిరిగి MZ_FALSE;
  }
  local_dir_శీర్షిక_ofs += అంకె_alignment_padding_బైట్లు;
  ఒకవేళ (pZip->m_file_స్థానభ్రంశం_alignment) { MZ_ASSERT((local_dir_శీర్షిక_ofs & (pZip->m_file_స్థానభ్రంశం_alignment - 1)) == 0); }
  cur_archive_file_ofs += అంకె_alignment_padding_బైట్లు + పరిమాణం(local_dir_శీర్షిక);

  MZ_CLEAR_ARR(local_dir_శీర్షిక);
  ఒకవేళ (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pArchive_name, archive_name_కొలత) != archive_name_కొలత)
  {
    MZ_FCLOSE(pSrc_file);
    తిరిగి MZ_FALSE;
  }
  cur_archive_file_ofs += archive_name_కొలత;

  ఒకవేళ (uncomp_కొలత)
  {
    mz_uint64 uncomp_మిగిలిన = uncomp_కొలత;
    శూన్య *pRead_buf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, MZ_ZIP_MAX_IO_BUF_కొలత);
    ఒకవేళ (!pRead_buf)
    {
      MZ_FCLOSE(pSrc_file);
      తిరిగి MZ_FALSE;
    }

    ఒకవేళ (!level)
    {
      అయితే (uncomp_మిగిలిన)
      {
        mz_uint n = (mz_uint)MZ_MIN(MZ_ZIP_MAX_IO_BUF_కొలత, uncomp_మిగిలిన);
        ఒకవేళ ((MZ_FREAD(pRead_buf, 1, n, pSrc_file) != n) || (pZip->m_pWrite(pZip->m_pIO_opaque, cur_archive_file_ofs, pRead_buf, n) != n))
        {
          pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
          MZ_FCLOSE(pSrc_file);
          తిరిగి MZ_FALSE;
        }
        uncomp_చక్రీయ_తనిఖీ_32 = (mz_uint32)mz_చక్రీయ_తనిఖీ_32(uncomp_చక్రీయ_తనిఖీ_32, (స్థిరరాశి mz_uint8 *)pRead_buf, n);
        uncomp_మిగిలిన -= n;
        cur_archive_file_ofs += n;
      }
      comp_కొలత = uncomp_కొలత;
    }
    లేకపోతే
    {
      mz_bool ఫలితం = MZ_FALSE;
      mz_zip_writer_కూడు_state state;
      tdefl_compressor *pComp = (tdefl_compressor *)pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, పరిమాణం(tdefl_compressor));
      ఒకవేళ (!pComp)
      {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        తిరిగి MZ_FALSE;
      }

      state.m_pZip = pZip;
      state.m_cur_archive_file_ofs = cur_archive_file_ofs;
      state.m_comp_కొలత = 0;

      ఒకవేళ (tdefl_init(pComp, mz_zip_writer_కూడు_put_buf_callback, &state, tdefl_create_comp_flags_from_zip_params(level, -15, MZ_DEFAULT_STRATEGY)) != TDEFL_స్థితి_OKAY)
      {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        తిరిగి MZ_FALSE;
      }

      కొరకు ( ; ; )
      {
        size_t లోపల_buf_కొలత = (mz_uint32)MZ_MIN(uncomp_మిగిలిన, MZ_ZIP_MAX_IO_BUF_కొలత);
        tdefl_స్థితి స్థితి_2;

        ఒకవేళ (MZ_FREAD(pRead_buf, 1, లోపల_buf_కొలత, pSrc_file) != లోపల_buf_కొలత)
          ఆపు;

        uncomp_చక్రీయ_తనిఖీ_32 = (mz_uint32)mz_చక్రీయ_తనిఖీ_32(uncomp_చక్రీయ_తనిఖీ_32, (స్థిరరాశి mz_uint8 *)pRead_buf, లోపల_buf_కొలత);
        uncomp_మిగిలిన -= లోపల_buf_కొలత;

        స్థితి_2 = tdefl_compress_బఫరు(pComp, pRead_buf, లోపల_buf_కొలత, uncomp_మిగిలిన ? TDEFL_NO_FLUSH : TDEFL_ముగింపు);
        ఒకవేళ (స్థితి_2 == TDEFL_స్థితి_పూర్తి)
        {
          ఫలితం = MZ_TRUE;
          ఆపు;
        }
        లేకపోతే ఒకవేళ (స్థితి_2 != TDEFL_స్థితి_OKAY)
          ఆపు;
      }

      pZip->m_pFree(pZip->m_pAlloc_opaque, pComp);

      ఒకవేళ (!ఫలితం)
      {
        pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
        MZ_FCLOSE(pSrc_file);
        తిరిగి MZ_FALSE;
      }

      comp_కొలత = state.m_comp_కొలత;
      cur_archive_file_ofs = state.m_cur_archive_file_ofs;

      పద్ధతి = MZ_DEFLATED;
    }

    pZip->m_pFree(pZip->m_pAlloc_opaque, pRead_buf);
  }

  MZ_FCLOSE(pSrc_file); pSrc_file = ఖాళీ;

  // no zip64 support yet
  ఒకవేళ ((comp_కొలత > 0xFFFFFFFF) || (cur_archive_file_ofs > 0xFFFFFFFF))
    తిరిగి MZ_FALSE;

  ఒకవేళ (!mz_zip_writer_create_local_dir_శీర్షిక(pZip, local_dir_శీర్షిక, (mz_uint16)archive_name_కొలత, 0, uncomp_కొలత, comp_కొలత, uncomp_చక్రీయ_తనిఖీ_32, పద్ధతి, 0, dos_సమయం, dos_date))
    తిరిగి MZ_FALSE;

  ఒకవేళ (pZip->m_pWrite(pZip->m_pIO_opaque, local_dir_శీర్షిక_ofs, local_dir_శీర్షిక, పరిమాణం(local_dir_శీర్షిక)) != పరిమాణం(local_dir_శీర్షిక))
    తిరిగి MZ_FALSE;

  ఒకవేళ (!mz_zip_writer_కూడు_గమ్యం_central_dir(pZip, pArchive_name, (mz_uint16)archive_name_కొలత, ఖాళీ, 0, pComment, comment_కొలత, uncomp_కొలత, comp_కొలత, uncomp_చక్రీయ_తనిఖీ_32, పద్ధతి, 0, dos_సమయం, dos_date, local_dir_శీర్షిక_ofs, ext_లక్షణాలు))
    తిరిగి MZ_FALSE;

  pZip->m_మొత్తం_files++;
  pZip->m_archive_కొలత = cur_archive_file_ofs;

  తిరిగి MZ_TRUE;
}
#అయితే_ముగింపు // #ifndef MINIZ_NO_STDIO

mz_bool mz_zip_writer_కూడు_from_zip_reader(mz_zip_archive *pZip, mz_zip_archive *p_ఆధారం_zip, mz_uint file_సూచీ)
{
  mz_uint n, బిట్టు_flags, అంకె_alignment_padding_బైట్లు;
  mz_uint64 comp_బైట్లు_మిగిలిన, local_dir_శీర్షిక_ofs;
  mz_uint64 cur_src_file_ofs, cur_dst_file_ofs;
  mz_uint32 local_శీర్షిక_u32[(MZ_ZIP_LOCAL_DIR_శీర్షిక_కొలత + పరిమాణం(mz_uint32) - 1) / పరిమాణం(mz_uint32)]; mz_uint8 *p_Local_శీర్షిక = (mz_uint8 *)local_శీర్షిక_u32;
  mz_uint8 central_శీర్షిక[MZ_ZIP_CENTRAL_DIR_శీర్షిక_కొలత];
  size_t orig_central_dir_కొలత;
  mz_zip_అంతర్గత_state *pState;
  శూన్య *pBuf; స్థిరరాశి mz_uint8 *p_Src_central_శీర్షిక;

  ఒకవేళ ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_బహుళకం != MZ_ZIP_బహుళకం_WRITING))
    తిరిగి MZ_FALSE;
  ఒకవేళ (ఖాళీ == (p_Src_central_శీర్షిక = mz_zip_reader_get_cdh(p_ఆధారం_zip, file_సూచీ)))
    తిరిగి MZ_FALSE;
  pState = pZip->m_pState;

  అంకె_alignment_padding_బైట్లు = mz_zip_writer_compute_padding_needed_for_file_alignment(pZip);

  // no zip64 support yet
  ఒకవేళ ((pZip->m_మొత్తం_files == 0xFFFF) || ((pZip->m_archive_కొలత + అంకె_alignment_padding_బైట్లు + MZ_ZIP_LOCAL_DIR_శీర్షిక_కొలత + MZ_ZIP_CENTRAL_DIR_శీర్షిక_కొలత) > 0xFFFFFFFF))
    తిరిగి MZ_FALSE;

  cur_src_file_ofs = MZ_READ_LE32(p_Src_central_శీర్షిక + MZ_ZIP_CDH_LOCAL_శీర్షిక_OFS);
  cur_dst_file_ofs = pZip->m_archive_కొలత;

  ఒకవేళ (p_ఆధారం_zip->m_pRead(p_ఆధారం_zip->m_pIO_opaque, cur_src_file_ofs, p_Local_శీర్షిక, MZ_ZIP_LOCAL_DIR_శీర్షిక_కొలత) != MZ_ZIP_LOCAL_DIR_శీర్షిక_కొలత)
    తిరిగి MZ_FALSE;
  ఒకవేళ (MZ_READ_LE32(p_Local_శీర్షిక) != MZ_ZIP_LOCAL_DIR_శీర్షిక_SIG)
    తిరిగి MZ_FALSE;
  cur_src_file_ofs += MZ_ZIP_LOCAL_DIR_శీర్షిక_కొలత;

  ఒకవేళ (!mz_zip_writer_write_zeros(pZip, cur_dst_file_ofs, అంకె_alignment_padding_బైట్లు))
    తిరిగి MZ_FALSE;
  cur_dst_file_ofs += అంకె_alignment_padding_బైట్లు;
  local_dir_శీర్షిక_ofs = cur_dst_file_ofs;
  ఒకవేళ (pZip->m_file_స్థానభ్రంశం_alignment) { MZ_ASSERT((local_dir_శీర్షిక_ofs & (pZip->m_file_స్థానభ్రంశం_alignment - 1)) == 0); }

  ఒకవేళ (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, p_Local_శీర్షిక, MZ_ZIP_LOCAL_DIR_శీర్షిక_కొలత) != MZ_ZIP_LOCAL_DIR_శీర్షిక_కొలత)
    తిరిగి MZ_FALSE;
  cur_dst_file_ofs += MZ_ZIP_LOCAL_DIR_శీర్షిక_కొలత;

  n = MZ_READ_LE16(p_Local_శీర్షిక + MZ_ZIP_LDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p_Local_శీర్షిక + MZ_ZIP_LDH_EXTRA_LEN_OFS);
  comp_బైట్లు_మిగిలిన = n + MZ_READ_LE32(p_Src_central_శీర్షిక + MZ_ZIP_CDH_COMPRESSED_కొలత_OFS);

  ఒకవేళ (ఖాళీ == (pBuf = pZip->m_pAlloc(pZip->m_pAlloc_opaque, 1, (size_t)MZ_MAX(పరిమాణం(mz_uint32) * 4, MZ_MIN(MZ_ZIP_MAX_IO_BUF_కొలత, comp_బైట్లు_మిగిలిన)))))
    తిరిగి MZ_FALSE;

  అయితే (comp_బైట్లు_మిగిలిన)
  {
    n = (mz_uint)MZ_MIN(MZ_ZIP_MAX_IO_BUF_కొలత, comp_బైట్లు_మిగిలిన);
    ఒకవేళ (p_ఆధారం_zip->m_pRead(p_ఆధారం_zip->m_pIO_opaque, cur_src_file_ofs, pBuf, n) != n)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      తిరిగి MZ_FALSE;
    }
    cur_src_file_ofs += n;

    ఒకవేళ (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, pBuf, n) != n)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      తిరిగి MZ_FALSE;
    }
    cur_dst_file_ofs += n;

    comp_బైట్లు_మిగిలిన -= n;
  }

  బిట్టు_flags = MZ_READ_LE16(p_Local_శీర్షిక + MZ_ZIP_LDH_బిట్టు_FLAG_OFS);
  ఒకవేళ (బిట్టు_flags & 8)
  {
    // Copy data descriptor
    ఒకవేళ (p_ఆధారం_zip->m_pRead(p_ఆధారం_zip->m_pIO_opaque, cur_src_file_ofs, pBuf, పరిమాణం(mz_uint32) * 4) != పరిమాణం(mz_uint32) * 4)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      తిరిగి MZ_FALSE;
    }

    n = పరిమాణం(mz_uint32) * ((MZ_READ_LE32(pBuf) == 0x08074b50) ? 4 : 3);
    ఒకవేళ (pZip->m_pWrite(pZip->m_pIO_opaque, cur_dst_file_ofs, pBuf, n) != n)
    {
      pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);
      తిరిగి MZ_FALSE;
    }

    cur_src_file_ofs += n;
    cur_dst_file_ofs += n;
  }
  pZip->m_pFree(pZip->m_pAlloc_opaque, pBuf);

  // no zip64 support yet
  ఒకవేళ (cur_dst_file_ofs > 0xFFFFFFFF)
    తిరిగి MZ_FALSE;

  orig_central_dir_కొలత = pState->m_central_dir.m_కొలత;

  జ్ఞాపకం_నకలు(central_శీర్షిక, p_Src_central_శీర్షిక, MZ_ZIP_CENTRAL_DIR_శీర్షిక_కొలత);
  MZ_WRITE_LE32(central_శీర్షిక + MZ_ZIP_CDH_LOCAL_శీర్షిక_OFS, local_dir_శీర్షిక_ofs);
  ఒకవేళ (!mz_zip_array_నెట్టు_వెనుక(pZip, &pState->m_central_dir, central_శీర్షిక, MZ_ZIP_CENTRAL_DIR_శీర్షిక_కొలత))
    తిరిగి MZ_FALSE;

  n = MZ_READ_LE16(p_Src_central_శీర్షిక + MZ_ZIP_CDH_FILENAME_LEN_OFS) + MZ_READ_LE16(p_Src_central_శీర్షిక + MZ_ZIP_CDH_EXTRA_LEN_OFS) + MZ_READ_LE16(p_Src_central_శీర్షిక + MZ_ZIP_CDH_COMMENT_LEN_OFS);
  ఒకవేళ (!mz_zip_array_నెట్టు_వెనుక(pZip, &pState->m_central_dir, p_Src_central_శీర్షిక + MZ_ZIP_CENTRAL_DIR_శీర్షిక_కొలత, n))
  {
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_కొలత, MZ_FALSE);
    తిరిగి MZ_FALSE;
  }

  ఒకవేళ (pState->m_central_dir.m_కొలత > 0xFFFFFFFF)
    తిరిగి MZ_FALSE;
  n = (mz_uint32)orig_central_dir_కొలత;
  ఒకవేళ (!mz_zip_array_నెట్టు_వెనుక(pZip, &pState->m_central_dir_offsets, &n, 1))
  {
    mz_zip_array_resize(pZip, &pState->m_central_dir, orig_central_dir_కొలత, MZ_FALSE);
    తిరిగి MZ_FALSE;
  }

  pZip->m_మొత్తం_files++;
  pZip->m_archive_కొలత = cur_dst_file_ofs;

  తిరిగి MZ_TRUE;
}

mz_bool mz_zip_writer_finalize_archive(mz_zip_archive *pZip)
{
  mz_zip_అంతర్గత_state *pState;
  mz_uint64 central_dir_ofs, central_dir_కొలత;
  mz_uint8 hdr[MZ_ZIP_చివర_యొక్క_CENTRAL_DIR_శీర్షిక_కొలత];

  ఒకవేళ ((!pZip) || (!pZip->m_pState) || (pZip->m_zip_బహుళకం != MZ_ZIP_బహుళకం_WRITING))
    తిరిగి MZ_FALSE;

  pState = pZip->m_pState;

  // no zip64 support yet
  ఒకవేళ ((pZip->m_మొత్తం_files > 0xFFFF) || ((pZip->m_archive_కొలత + pState->m_central_dir.m_కొలత + MZ_ZIP_చివర_యొక్క_CENTRAL_DIR_శీర్షిక_కొలత) > 0xFFFFFFFF))
    తిరిగి MZ_FALSE;

  central_dir_ofs = 0;
  central_dir_కొలత = 0;
  ఒకవేళ (pZip->m_మొత్తం_files)
  {
    // Write central directory
    central_dir_ofs = pZip->m_archive_కొలత;
    central_dir_కొలత = pState->m_central_dir.m_కొలత;
    pZip->m_central_directory_file_ofs = central_dir_ofs;
    ఒకవేళ (pZip->m_pWrite(pZip->m_pIO_opaque, central_dir_ofs, pState->m_central_dir.m_p, (size_t)central_dir_కొలత) != central_dir_కొలత)
      తిరిగి MZ_FALSE;
    pZip->m_archive_కొలత += central_dir_కొలత;
  }

  // Write end of central directory record
  MZ_CLEAR_ARR(hdr);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_SIG_OFS, MZ_ZIP_చివర_యొక్క_CENTRAL_DIR_శీర్షిక_SIG);
  MZ_WRITE_LE16(hdr + MZ_ZIP_ECDH_CDIR_అంకె_ENTRIES_ON_DISK_OFS, pZip->m_మొత్తం_files);
  MZ_WRITE_LE16(hdr + MZ_ZIP_ECDH_CDIR_మొత్తం_ENTRIES_OFS, pZip->m_మొత్తం_files);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_CDIR_కొలత_OFS, central_dir_కొలత);
  MZ_WRITE_LE32(hdr + MZ_ZIP_ECDH_CDIR_OFS_OFS, central_dir_ofs);

  ఒకవేళ (pZip->m_pWrite(pZip->m_pIO_opaque, pZip->m_archive_కొలత, hdr, పరిమాణం(hdr)) != పరిమాణం(hdr))
    తిరిగి MZ_FALSE;
#నిర్వచితం_కాకపోతే MINIZ_NO_STDIO
  ఒకవేళ ((pState->m_pFile) && (MZ_FFLUSH(pState->m_pFile) == EOF))
    తిరిగి MZ_FALSE;
#అయితే_ముగింపు // #ifndef MINIZ_NO_STDIO

  pZip->m_archive_కొలత += పరిమాణం(hdr);

  pZip->m_zip_బహుళకం = MZ_ZIP_బహుళకం_WRITING_HAS_BEEN_FINALIZED;
  తిరిగి MZ_TRUE;
}

mz_bool mz_zip_writer_finalize_కుప్ప_archive(mz_zip_archive *pZip, శూన్య **pBuf, size_t *p_కొలత)
{
  ఒకవేళ ((!pZip) || (!pZip->m_pState) || (!pBuf) || (!p_కొలత))
    తిరిగి MZ_FALSE;
  ఒకవేళ (pZip->m_pWrite != mz_zip_కుప్ప_write_func)
    తిరిగి MZ_FALSE;
  ఒకవేళ (!mz_zip_writer_finalize_archive(pZip))
    తిరిగి MZ_FALSE;

  *pBuf = pZip->m_pState->m_pMem;
  *p_కొలత = pZip->m_pState->m_mem_కొలత;
  pZip->m_pState->m_pMem = ఖాళీ;
  pZip->m_pState->m_mem_కొలత = pZip->m_pState->m_mem_సామర్థ్యం = 0;
  తిరిగి MZ_TRUE;
}

mz_bool mz_zip_writer_చివర(mz_zip_archive *pZip)
{
  mz_zip_అంతర్గత_state *pState;
  mz_bool స్థితి_2 = MZ_TRUE;
  ఒకవేళ ((!pZip) || (!pZip->m_pState) || (!pZip->m_pAlloc) || (!pZip->m_pFree) || ((pZip->m_zip_బహుళకం != MZ_ZIP_బహుళకం_WRITING) && (pZip->m_zip_బహుళకం != MZ_ZIP_బహుళకం_WRITING_HAS_BEEN_FINALIZED)))
    తిరిగి MZ_FALSE;

  pState = pZip->m_pState;
  pZip->m_pState = ఖాళీ;
  mz_zip_array_clear(pZip, &pState->m_central_dir);
  mz_zip_array_clear(pZip, &pState->m_central_dir_offsets);
  mz_zip_array_clear(pZip, &pState->m_sorted_central_dir_offsets);

#నిర్వచితం_కాకపోతే MINIZ_NO_STDIO
  ఒకవేళ (pState->m_pFile)
  {
    MZ_FCLOSE(pState->m_pFile);
    pState->m_pFile = ఖాళీ;
  }
#అయితే_ముగింపు // #ifndef MINIZ_NO_STDIO

  ఒకవేళ ((pZip->m_pWrite == mz_zip_కుప్ప_write_func) && (pState->m_pMem))
  {
    pZip->m_pFree(pZip->m_pAlloc_opaque, pState->m_pMem);
    pState->m_pMem = ఖాళీ;
  }

  pZip->m_pFree(pZip->m_pAlloc_opaque, pState);
  pZip->m_zip_బహుళకం = MZ_ZIP_బహుళకం_INVALID;
  తిరిగి స్థితి_2;
}

#నిర్వచితం_కాకపోతే MINIZ_NO_STDIO
mz_bool mz_zip_కూడు_mem_గమ్యం_archive_file_లోపల_ఉంచు(స్థిరరాశి అక్షరం *pZip_filename, స్థిరరాశి అక్షరం *pArchive_name, స్థిరరాశి శూన్య *pBuf, size_t buf_కొలత_2, స్థిరరాశి శూన్య *pComment, mz_uint16 comment_కొలత, mz_uint level_and_flags)
{
  mz_bool స్థితి_2, created_new_archive = MZ_FALSE;
  mz_zip_archive zip_archive;
  నిర్మాణం MZ_FILE_STAT_STRUCT file_stat;
  MZ_CLEAR_OBJ(zip_archive);
  ఒకవేళ ((పూర్ణాంకం)level_and_flags < 0)
     level_and_flags = MZ_DEFAULT_LEVEL;
  ఒకవేళ ((!pZip_filename) || (!pArchive_name) || ((buf_కొలత_2) && (!pBuf)) || ((comment_కొలత) && (!pComment)) || ((level_and_flags & 0xF) > MZ_UBER_COMPRESSION))
    తిరిగి MZ_FALSE;
  ఒకవేళ (!mz_zip_writer_validate_archive_name(pArchive_name))
    తిరిగి MZ_FALSE;
  ఒకవేళ (MZ_FILE_STAT(pZip_filename, &file_stat) != 0)
  {
    // Create a new archive.
    ఒకవేళ (!mz_zip_writer_init_file(&zip_archive, pZip_filename, 0))
      తిరిగి MZ_FALSE;
    created_new_archive = MZ_TRUE;
  }
  లేకపోతే
  {
    // Append to an existing archive.
    ఒకవేళ (!mz_zip_reader_init_file(&zip_archive, pZip_filename, level_and_flags | MZ_ZIP_FLAG_DO_NOT_క్రమీకరించు_CENTRAL_DIRECTORY))
      తిరిగి MZ_FALSE;
    ఒకవేళ (!mz_zip_writer_init_from_reader(&zip_archive, pZip_filename))
    {
      mz_zip_reader_చివర(&zip_archive);
      తిరిగి MZ_FALSE;
    }
  }
  స్థితి_2 = mz_zip_writer_కూడు_mem_ex(&zip_archive, pArchive_name, pBuf, buf_కొలత_2, pComment, comment_కొలత, level_and_flags, 0, 0);
  // Always finalize, even if adding failed for some reason, so we have a valid central directory. (This may not always succeed, but we can try.)
  ఒకవేళ (!mz_zip_writer_finalize_archive(&zip_archive))
    స్థితి_2 = MZ_FALSE;
  ఒకవేళ (!mz_zip_writer_చివర(&zip_archive))
    స్థితి_2 = MZ_FALSE;
  ఒకవేళ ((!స్థితి_2) && (created_new_archive))
  {
    // It's a new archive and something went wrong, so just delete it.
    పూర్ణాంకం ignored_స్థితి = MZ_DELETE_FILE(pZip_filename);
    (శూన్య)ignored_స్థితి;
  }
  తిరిగి స్థితి_2;
}

శూన్య *mz_zip_వెలికితీయి_archive_file_గమ్యం_కుప్ప(స్థిరరాశి అక్షరం *pZip_filename, స్థిరరాశి అక్షరం *pArchive_name, size_t *p_కొలత, mz_uint flags)
{
  పూర్ణాంకం file_సూచీ;
  mz_zip_archive zip_archive;
  శూన్య *p = ఖాళీ;

  ఒకవేళ (p_కొలత)
    *p_కొలత = 0;

  ఒకవేళ ((!pZip_filename) || (!pArchive_name))
    తిరిగి ఖాళీ;

  MZ_CLEAR_OBJ(zip_archive);
  ఒకవేళ (!mz_zip_reader_init_file(&zip_archive, pZip_filename, flags | MZ_ZIP_FLAG_DO_NOT_క్రమీకరించు_CENTRAL_DIRECTORY))
    తిరిగి ఖాళీ;

  ఒకవేళ ((file_సూచీ = mz_zip_reader_locate_file(&zip_archive, pArchive_name, ఖాళీ, flags)) >= 0)
    p = mz_zip_reader_వెలికితీయి_గమ్యం_కుప్ప(&zip_archive, file_సూచీ, p_కొలత, flags);

  mz_zip_reader_చివర(&zip_archive);
  తిరిగి p;
}

#అయితే_ముగింపు // #ifndef MINIZ_NO_STDIO

#అయితే_ముగింపు // #ifndef MINIZ_NO_ARCHIVE_WRITING_APIS

#అయితే_ముగింపు // #ifndef MINIZ_NO_ARCHIVE_APIS

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#నిర్వచితమైతే _MSC_VER
#సూచన warning (తీయి)
#అయితే_ముగింపు

#అయితే_ముగింపు // MINIZ_HEADER_FILE_ONLY

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

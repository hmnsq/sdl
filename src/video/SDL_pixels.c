/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

// General (mostly internal) pixel/color manipulation routines for SDL

#ಅನ್ತರ್ಭಾವ "SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_pixels_c.h"
#ಅನ್ತರ್ಭಾವ "SDL_RLEaccel_c.h"

// Lookup tables to expand partial bytes to the full 0..255 range

// This is the code used to generate the lookup tables below:
#ಆದರೆ 0
#ಅನ್ತರ್ಭಾವ <SDL3/SDL.h>

#ವ್ಯಾಖ್ಯಾನಿಸು GENERATE_SHIFTS

ಸ್ಥಿರ Uint32 Calculate(ಪೂರ್ಣಾಂಕ v, ಪೂರ್ಣಾಂಕ ಬಿಟ್ಟುಗಳು, ಪೂರ್ಣಾಂಕ vmax, ಪೂರ್ಣಾಂಕ ಸರಿಸು)
{
#ಆದರೆ defined(GENERATE_FLOOR)
    (ಶೂನ್ಯ)ಬಿಟ್ಟುಗಳು;
    ಹಿಂತಿರುಗಿ (Uint32)SDL_floor(v * 255.0f / vmax) << ಸರಿಸು;
#ಅಥವಾಆದರೆ defined(GENERATE_ಸುತ್ತು)
    (ಶೂನ್ಯ)ಬಿಟ್ಟುಗಳು;
    ಹಿಂತಿರುಗಿ (Uint32)SDL_roundf(v * 255.0f / vmax) << ಸರಿಸು;
#ಅಥವಾಆದರೆ defined(GENERATE_SHIFTS)
    (ಶೂನ್ಯ)vmax;
    ಆಯ್ಕೆ (ಬಿಟ್ಟುಗಳು) {
    ಸ್ಥಿತಿ 1:
        v = (v << 7) | (v << 6) | (v << 5) | (v << 4) | (v << 3) | (v << 2) | (v << 1) | v;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 2:
        v = (v << 6) | (v << 4) | (v << 2) | v;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 3:
        v = (v << 5) | (v << 2) | (v >> 1);
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 4:
        v = (v << 4) | v;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 5:
        v = (v << 3) | (v >> 2);
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 6:
        v = (v << 2) | (v >> 4);
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 7:
        v = (v << 1) | (v >> 6);
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 8:
        ನಿಲ್ಲಿಸು;
    }
    ಹಿಂತಿರುಗಿ (Uint32)v << ಸರಿಸು;
#ಆದರೆ_ಅಂತ್ಯ
}

ಪೂರ್ಣಾಂಕ ಮುಖ್ಯ(ಪೂರ್ಣಾಂಕ argc, ಅಕ್ಷರ *argv[])
{
    ಪೂರ್ಣಾಂಕ i, b;
    SDL_IOStream *io = SDL_IOFromDynamicMem();

    (ಶೂನ್ಯ)argc;
    (ಶೂನ್ಯ)argv;
    ಗಾಗಿ (b = 1; b <= 8; ++b) {
        SDL_IOprintf(io, "static const Uint8 lookup_%d[] = {\n    ", b);
        ಗಾಗಿ (i = 0; i < (1 << b); ++i) {
            ಆದರೆ (i > 0) {
                SDL_IOprintf(io, ", ");
            }
            SDL_IOprintf(io, "%d", Calculate(i, b, (1 << b) - 1, 0));
        }
        SDL_Log("%s\n};\n\n", (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *)SDL_Get_ಸೂಚಕ_Property(SDL_GetIOProperties(io), SDL_PROP_IOSTREAM_DYNAMIC_ಸ್ಮರಣೆ_ಸೂಚಕ, ಖಾಲಿ));
        SDL_SeekIO(io, 0, SDL_IO_SEEK_ಗಣ);
        SDL_WriteIO(io, "", 1);
        SDL_SeekIO(io, 0, SDL_IO_SEEK_ಗಣ);
    }
    SDL_CloseIO(io);
    ಹಿಂತಿರುಗಿ 0;
}
#ಆದರೆ_ಅಂತ್ಯ

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ Uint8 lookup_0[] = {
    255
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ Uint8 lookup_1[] = {
    0, 255
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ Uint8 lookup_2[] = {
    0, 85, 170, 255
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ Uint8 lookup_3[] = {
    0, 36, 73, 109, 146, 182, 219, 255
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ Uint8 lookup_4[] = {
    0, 17, 34, 51, 68, 85, 102, 119, 136, 153, 170, 187, 204, 221, 238, 255
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ Uint8 lookup_5[] = {
    0, 8, 16, 24, 33, 41, 49, 57, 66, 74, 82, 90, 99, 107, 115, 123, 132, 140, 148, 156, 165, 173, 181, 189, 198, 206, 214, 222, 231, 239, 247, 255
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ Uint8 lookup_6[] = {
    0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 65, 69, 73, 77, 81, 85, 89, 93, 97, 101, 105, 109, 113, 117, 121, 125, 130, 134, 138, 142, 146, 150, 154, 158, 162, 166, 170, 174, 178, 182, 186, 190, 195, 199, 203, 207, 211, 215, 219, 223, 227, 231, 235, 239, 243, 247, 251, 255
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ Uint8 lookup_7[] = {
    0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64, 66, 68, 70, 72, 74, 76, 78, 80, 82, 84, 86, 88, 90, 92, 94, 96, 98, 100, 102, 104, 106, 108, 110, 112, 114, 116, 118, 120, 122, 124, 126, 129, 131, 133, 135, 137, 139, 141, 143, 145, 147, 149, 151, 153, 155, 157, 159, 161, 163, 165, 167, 169, 171, 173, 175, 177, 179, 181, 183, 185, 187, 189, 191, 193, 195, 197, 199, 201, 203, 205, 207, 209, 211, 213, 215, 217, 219, 221, 223, 225, 227, 229, 231, 233, 235, 237, 239, 241, 243, 245, 247, 249, 251, 253, 255
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ Uint8 lookup_8[] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255
};

ಸ್ಥಿರಾಂಕ Uint8 *SDL_expand_byte[9] = {
    lookup_0,
    lookup_1,
    lookup_2,
    lookup_3,
    lookup_4,
    lookup_5,
    lookup_6,
    lookup_7,
    lookup_8
};

// Lookup tables to expand 8 bit to 10 bit range
ಸ್ಥಿರಾಂಕ Uint16 SDL_expand_byte_10[] = {
    0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 68, 72, 76, 80, 84, 88, 92, 96, 100, 104, 108, 112, 116, 120, 124, 128, 132, 136, 140, 144, 148, 152, 156, 160, 164, 168, 173, 177, 181, 185, 189, 193, 197, 201, 205, 209, 213, 217, 221, 225, 229, 233, 237, 241, 245, 249, 253, 257, 261, 265, 269, 273, 277, 281, 285, 289, 293, 297, 301, 305, 309, 313, 317, 321, 325, 329, 333, 337, 341, 345, 349, 353, 357, 361, 365, 369, 373, 377, 381, 385, 389, 393, 397, 401, 405, 409, 413, 417, 421, 425, 429, 433, 437, 441, 445, 449, 453, 457, 461, 465, 469, 473, 477, 481, 485, 489, 493, 497, 501, 505, 509, 514, 518, 522, 526, 530, 534, 538, 542, 546, 550, 554, 558, 562, 566, 570, 574, 578, 582, 586, 590, 594, 598, 602, 606, 610, 614, 618, 622, 626, 630, 634, 638, 642, 646, 650, 654, 658, 662, 666, 670, 674, 678, 682, 686, 690, 694, 698, 702, 706, 710, 714, 718, 722, 726, 730, 734, 738, 742, 746, 750, 754, 758, 762, 766, 770, 774, 778, 782, 786, 790, 794, 798, 802, 806, 810, 814, 818, 822, 826, 830, 834, 838, 842, 846, 850, 855, 859, 863, 867, 871, 875, 879, 883, 887, 891, 895, 899, 903, 907, 911, 915, 919, 923, 927, 931, 935, 939, 943, 947, 951, 955, 959, 963, 967, 971, 975, 979, 983, 987, 991, 995, 999, 1003, 1007, 1011, 1015, 1019, 1023
};
SDL_COMPILE_ಸಮಯ_ASSERT(SDL_expand_byte_10_ಗಾತ್ರ, SDL_arraysize(SDL_expand_byte_10) == (1 << 8));


// Helper functions

#ವ್ಯಾಖ್ಯಾನಿಸು CASE(X) \
    ಸ್ಥಿತಿ X:     \
        ಹಿಂತಿರುಗಿ #X;
ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *SDL_GetPixelFormatName(SDL_PixelFormat format)
{
    ಆಯ್ಕೆ (format) {

        CASE(SDL_PIXELFORMAT_INDEX1LSB)
        CASE(SDL_PIXELFORMAT_INDEX1MSB)
        CASE(SDL_PIXELFORMAT_INDEX2LSB)
        CASE(SDL_PIXELFORMAT_INDEX2MSB)
        CASE(SDL_PIXELFORMAT_INDEX4LSB)
        CASE(SDL_PIXELFORMAT_INDEX4MSB)
        CASE(SDL_PIXELFORMAT_INDEX8)
        CASE(SDL_PIXELFORMAT_RGB332)
        CASE(SDL_PIXELFORMAT_XRGB4444)
        CASE(SDL_PIXELFORMAT_XBGR4444)
        CASE(SDL_PIXELFORMAT_XRGB1555)
        CASE(SDL_PIXELFORMAT_XBGR1555)
        CASE(SDL_PIXELFORMAT_ARGB4444)
        CASE(SDL_PIXELFORMAT_RGBA4444)
        CASE(SDL_PIXELFORMAT_ABGR4444)
        CASE(SDL_PIXELFORMAT_BGRA4444)
        CASE(SDL_PIXELFORMAT_ARGB1555)
        CASE(SDL_PIXELFORMAT_RGBA5551)
        CASE(SDL_PIXELFORMAT_ABGR1555)
        CASE(SDL_PIXELFORMAT_BGRA5551)
        CASE(SDL_PIXELFORMAT_RGB565)
        CASE(SDL_PIXELFORMAT_BGR565)
        CASE(SDL_PIXELFORMAT_RGB24)
        CASE(SDL_PIXELFORMAT_BGR24)
        CASE(SDL_PIXELFORMAT_XRGB8888)
        CASE(SDL_PIXELFORMAT_RGBX8888)
        CASE(SDL_PIXELFORMAT_XBGR8888)
        CASE(SDL_PIXELFORMAT_BGRX8888)
        CASE(SDL_PIXELFORMAT_ARGB8888)
        CASE(SDL_PIXELFORMAT_RGBA8888)
        CASE(SDL_PIXELFORMAT_ABGR8888)
        CASE(SDL_PIXELFORMAT_BGRA8888)
        CASE(SDL_PIXELFORMAT_XRGB2101010)
        CASE(SDL_PIXELFORMAT_XBGR2101010)
        CASE(SDL_PIXELFORMAT_ARGB2101010)
        CASE(SDL_PIXELFORMAT_ABGR2101010)
        CASE(SDL_PIXELFORMAT_RGB48)
        CASE(SDL_PIXELFORMAT_BGR48)
        CASE(SDL_PIXELFORMAT_RGBA64)
        CASE(SDL_PIXELFORMAT_ARGB64)
        CASE(SDL_PIXELFORMAT_BGRA64)
        CASE(SDL_PIXELFORMAT_ABGR64)
        CASE(SDL_PIXELFORMAT_RGB48_FLOAT)
        CASE(SDL_PIXELFORMAT_BGR48_FLOAT)
        CASE(SDL_PIXELFORMAT_RGBA64_FLOAT)
        CASE(SDL_PIXELFORMAT_ARGB64_FLOAT)
        CASE(SDL_PIXELFORMAT_BGRA64_FLOAT)
        CASE(SDL_PIXELFORMAT_ABGR64_FLOAT)
        CASE(SDL_PIXELFORMAT_RGB96_FLOAT)
        CASE(SDL_PIXELFORMAT_BGR96_FLOAT)
        CASE(SDL_PIXELFORMAT_RGBA128_FLOAT)
        CASE(SDL_PIXELFORMAT_ARGB128_FLOAT)
        CASE(SDL_PIXELFORMAT_BGRA128_FLOAT)
        CASE(SDL_PIXELFORMAT_ABGR128_FLOAT)
        CASE(SDL_PIXELFORMAT_YV12)
        CASE(SDL_PIXELFORMAT_IYUV)
        CASE(SDL_PIXELFORMAT_YUY2)
        CASE(SDL_PIXELFORMAT_UYVY)
        CASE(SDL_PIXELFORMAT_YVYU)
        CASE(SDL_PIXELFORMAT_NV12)
        CASE(SDL_PIXELFORMAT_NV21)
        CASE(SDL_PIXELFORMAT_P010)
        CASE(SDL_PIXELFORMAT_I444)
        CASE(SDL_PIXELFORMAT_I0FL)
        CASE(SDL_PIXELFORMAT_I4FL)
        CASE(SDL_PIXELFORMAT_EXTERNAL_OES)
        CASE(SDL_PIXELFORMAT_MJPG)

    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ "SDL_PIXELFORMAT_UNKNOWN";
    }
}
#ವ್ಯಾಖ್ಯಾನ_ರದ್ದು CASE

bool SDL_GetMasksForPixelFormat(SDL_PixelFormat format, ಪೂರ್ಣಾಂಕ *bpp, Uint32 *Rmask, Uint32 *Gmask, Uint32 *Bmask, Uint32 *Amask)
{
    Uint32 masks[4];

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_HAVE_YUV
    // Partial support for SDL_Surface with FOURCC
    ಆದರೆ (SDL_ISPIXELFORMAT_FOURCC(format)) {
        // Not a format that uses masks
        *Rmask = *Gmask = *Bmask = *Amask = 0;
        // however, some of these are packed formats, and can legit declare bits-per-pixel!
        ಆಯ್ಕೆ (format) {
            ಸ್ಥಿತಿ SDL_PIXELFORMAT_YUY2:
            ಸ್ಥಿತಿ SDL_PIXELFORMAT_UYVY:
            ಸ್ಥಿತಿ SDL_PIXELFORMAT_YVYU:
                *bpp = 32;
                ನಿಲ್ಲಿಸು;
            ಪೂರ್ವನಿಯೋಜಿತ:
                *bpp = 0;  // oh well.
        }
        ಹಿಂತಿರುಗಿ true;
    }
#ಇಲ್ಲದಿದ್ದರೆ
    ಆದರೆ (SDL_ISPIXELFORMAT_FOURCC(format)) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("SDL not built with YUV support");
    }
#ಆದರೆ_ಅಂತ್ಯ

    // Initialize the values here
    ಆದರೆ (SDL_BYTESPERPIXEL(format) <= 2) {
        *bpp = SDL_BITSPERPIXEL(format);
    } ಇಲ್ಲದಿದ್ದರೆ {
        *bpp = SDL_BYTESPERPIXEL(format) * 8;
    }
    *Rmask = *Gmask = *Bmask = *Amask = 0;

    ಆದರೆ (SDL_PIXELTYPE(format) == SDL_PIXELTYPE_ARRAYU8) {
        ಆಯ್ಕೆ (SDL_BYTESPERPIXEL(format)) {
        ಸ್ಥಿತಿ 3:
            ಆಯ್ಕೆ (SDL_PIXELORDER(format)) {
            ಸ್ಥಿತಿ SDL_ARRAYORDER_RGB:
#ಆದರೆ SDL_BYTEORDER == SDL_BIG_ENDIAN
                *Rmask = 0x00FF0000;
                *Gmask = 0x0000FF00;
                *Bmask = 0x000000FF;
#ಇಲ್ಲದಿದ್ದರೆ
                *Rmask = 0x000000FF;
                *Gmask = 0x0000FF00;
                *Bmask = 0x00FF0000;
#ಆದರೆ_ಅಂತ್ಯ
                ಹಿಂತಿರುಗಿ true;
            ಸ್ಥಿತಿ SDL_ARRAYORDER_BGR:
#ಆದರೆ SDL_BYTEORDER == SDL_BIG_ENDIAN
                *Rmask = 0x000000FF;
                *Gmask = 0x0000FF00;
                *Bmask = 0x00FF0000;
#ಇಲ್ಲದಿದ್ದರೆ
                *Rmask = 0x00FF0000;
                *Gmask = 0x0000FF00;
                *Bmask = 0x000000FF;
#ಆದರೆ_ಅಂತ್ಯ
                ಹಿಂತಿರುಗಿ true;
            ಪೂರ್ವನಿಯೋಜಿತ:
                ನಿಲ್ಲಿಸು;
            }
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ 4:
            ಆಯ್ಕೆ (SDL_PIXELORDER(format)) {
            ಸ್ಥಿತಿ SDL_ARRAYORDER_RGBA:
#ಆದರೆ SDL_BYTEORDER == SDL_BIG_ENDIAN
                *Rmask = 0xFF000000;
                *Gmask = 0x00FF0000;
                *Bmask = 0x0000FF00;
                *Amask = 0x000000FF;
#ಇಲ್ಲದಿದ್ದರೆ
                *Rmask = 0x000000FF;
                *Gmask = 0x0000FF00;
                *Bmask = 0x00FF0000;
                *Amask = 0xFF000000;
#ಆದರೆ_ಅಂತ್ಯ
                ಹಿಂತಿರುಗಿ true;
            ಸ್ಥಿತಿ SDL_ARRAYORDER_ARGB:
#ಆದರೆ SDL_BYTEORDER == SDL_BIG_ENDIAN
                *Rmask = 0x00FF0000;
                *Gmask = 0x0000FF00;
                *Bmask = 0x000000FF;
                *Amask = 0xFF000000;
#ಇಲ್ಲದಿದ್ದರೆ
                *Rmask = 0x0000FF00;
                *Gmask = 0x00FF0000;
                *Bmask = 0xFF000000;
                *Amask = 0x000000FF;
#ಆದರೆ_ಅಂತ್ಯ
                ಹಿಂತಿರುಗಿ true;
            ಸ್ಥಿತಿ SDL_ARRAYORDER_BGRA:
#ಆದರೆ SDL_BYTEORDER == SDL_BIG_ENDIAN
                *Rmask = 0x0000FF00;
                *Gmask = 0x00FF0000;
                *Bmask = 0xFF000000;
                *Amask = 0x000000FF;
#ಇಲ್ಲದಿದ್ದರೆ
                *Rmask = 0x00FF0000;
                *Gmask = 0x0000FF00;
                *Bmask = 0x000000FF;
                *Amask = 0xFF000000;
#ಆದರೆ_ಅಂತ್ಯ
                ಹಿಂತಿರುಗಿ true;
            ಸ್ಥಿತಿ SDL_ARRAYORDER_ABGR:
#ಆದರೆ SDL_BYTEORDER == SDL_BIG_ENDIAN
                *Rmask = 0x000000FF;
                *Gmask = 0x0000FF00;
                *Bmask = 0x00FF0000;
                *Amask = 0xFF000000;
#ಇಲ್ಲದಿದ್ದರೆ
                *Rmask = 0xFF000000;
                *Gmask = 0x00FF0000;
                *Bmask = 0x0000FF00;
                *Amask = 0x000000FF;
#ಆದರೆ_ಅಂತ್ಯ
                ಹಿಂತಿರುಗಿ true;
            ಪೂರ್ವನಿಯೋಜಿತ:
                ನಿಲ್ಲಿಸು;
            }
            ನಿಲ್ಲಿಸು;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ನಿಲ್ಲಿಸು;
        }
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Unknown pixel format");
    }

    ಆದರೆ (SDL_PIXELTYPE(format) != SDL_PIXELTYPE_PACKED8 &&
        SDL_PIXELTYPE(format) != SDL_PIXELTYPE_PACKED16 &&
        SDL_PIXELTYPE(format) != SDL_PIXELTYPE_PACKED32) {
        // Not a format that uses masks
        ಹಿಂತಿರುಗಿ true;
    }

    ಆಯ್ಕೆ (SDL_PIXELLAYOUT(format)) {
    ಸ್ಥಿತಿ SDL_PACKEDLAYOUT_332:
        masks[0] = 0x00000000;
        masks[1] = 0x000000E0;
        masks[2] = 0x0000001C;
        masks[3] = 0x00000003;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_PACKEDLAYOUT_4444:
        masks[0] = 0x0000F000;
        masks[1] = 0x00000F00;
        masks[2] = 0x000000F0;
        masks[3] = 0x0000000F;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_PACKEDLAYOUT_1555:
        masks[0] = 0x00008000;
        masks[1] = 0x00007C00;
        masks[2] = 0x000003E0;
        masks[3] = 0x0000001F;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_PACKEDLAYOUT_5551:
        masks[0] = 0x0000F800;
        masks[1] = 0x000007C0;
        masks[2] = 0x0000003E;
        masks[3] = 0x00000001;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_PACKEDLAYOUT_565:
        masks[0] = 0x00000000;
        masks[1] = 0x0000F800;
        masks[2] = 0x000007E0;
        masks[3] = 0x0000001F;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_PACKEDLAYOUT_8888:
        masks[0] = 0xFF000000;
        masks[1] = 0x00FF0000;
        masks[2] = 0x0000FF00;
        masks[3] = 0x000000FF;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_PACKEDLAYOUT_2101010:
        masks[0] = 0xC0000000;
        masks[1] = 0x3FF00000;
        masks[2] = 0x000FFC00;
        masks[3] = 0x000003FF;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_PACKEDLAYOUT_1010102:
        masks[0] = 0xFFC00000;
        masks[1] = 0x003FF000;
        masks[2] = 0x00000FFC;
        masks[3] = 0x00000003;
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Unknown pixel format");
    }

    ಆಯ್ಕೆ (SDL_PIXELORDER(format)) {
    ಸ್ಥಿತಿ SDL_PACKEDORDER_XRGB:
        *Rmask = masks[1];
        *Gmask = masks[2];
        *Bmask = masks[3];
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_PACKEDORDER_RGBX:
        *Rmask = masks[0];
        *Gmask = masks[1];
        *Bmask = masks[2];
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_PACKEDORDER_ARGB:
        *Amask = masks[0];
        *Rmask = masks[1];
        *Gmask = masks[2];
        *Bmask = masks[3];
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_PACKEDORDER_RGBA:
        *Rmask = masks[0];
        *Gmask = masks[1];
        *Bmask = masks[2];
        *Amask = masks[3];
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_PACKEDORDER_XBGR:
        *Bmask = masks[1];
        *Gmask = masks[2];
        *Rmask = masks[3];
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_PACKEDORDER_BGRX:
        *Bmask = masks[0];
        *Gmask = masks[1];
        *Rmask = masks[2];
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_PACKEDORDER_BGRA:
        *Bmask = masks[0];
        *Gmask = masks[1];
        *Rmask = masks[2];
        *Amask = masks[3];
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_PACKEDORDER_ABGR:
        *Amask = masks[0];
        *Bmask = masks[1];
        *Gmask = masks[2];
        *Rmask = masks[3];
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("Unknown pixel format");
    }
    ಹಿಂತಿರುಗಿ true;
}

SDL_PixelFormat SDL_GetPixelFormatForMasks(ಪೂರ್ಣಾಂಕ bpp, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask)
{
    ಆಯ್ಕೆ (bpp) {
    ಸ್ಥಿತಿ 1:
        // SDL defaults to MSB ordering
        ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_INDEX1MSB;
    ಸ್ಥಿತಿ 2:
        // SDL defaults to MSB ordering
        ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_INDEX2MSB;
    ಸ್ಥಿತಿ 4:
        // SDL defaults to MSB ordering
        ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_INDEX4MSB;
    ಸ್ಥಿತಿ 8:
        ಆದರೆ (Rmask == 0xE0 &&
            Gmask == 0x1C &&
            Bmask == 0x03 &&
            Amask == 0x00) {
            ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_RGB332;
        }
        ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_INDEX8;
    ಸ್ಥಿತಿ 12:
        ಆದರೆ (Rmask == 0) {
            ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_XRGB4444;
        }
        ಆದರೆ (Rmask == 0x0F00 &&
            Gmask == 0x00F0 &&
            Bmask == 0x000F &&
            Amask == 0x0000) {
            ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_XRGB4444;
        }
        ಆದರೆ (Rmask == 0x000F &&
            Gmask == 0x00F0 &&
            Bmask == 0x0F00 &&
            Amask == 0x0000) {
            ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_XBGR4444;
        }
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 15:
        ಆದರೆ (Rmask == 0) {
            ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_XRGB1555;
        }
        SDL_FALLTHROUGH;
    ಸ್ಥಿತಿ 16:
        ಆದರೆ (Rmask == 0) {
            ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_RGB565;
        }
        ಆದರೆ (Rmask == 0x7C00 &&
            Gmask == 0x03E0 &&
            Bmask == 0x001F &&
            Amask == 0x0000) {
            ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_XRGB1555;
        }
        ಆದರೆ (Rmask == 0x001F &&
            Gmask == 0x03E0 &&
            Bmask == 0x7C00 &&
            Amask == 0x0000) {
            ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_XBGR1555;
        }
        ಆದರೆ (Rmask == 0x0F00 &&
            Gmask == 0x00F0 &&
            Bmask == 0x000F &&
            Amask == 0xF000) {
            ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_ARGB4444;
        }
        ಆದರೆ (Rmask == 0xF000 &&
            Gmask == 0x0F00 &&
            Bmask == 0x00F0 &&
            Amask == 0x000F) {
            ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_RGBA4444;
        }
        ಆದರೆ (Rmask == 0x000F &&
            Gmask == 0x00F0 &&
            Bmask == 0x0F00 &&
            Amask == 0xF000) {
            ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_ABGR4444;
        }
        ಆದರೆ (Rmask == 0x00F0 &&
            Gmask == 0x0F00 &&
            Bmask == 0xF000 &&
            Amask == 0x000F) {
            ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_BGRA4444;
        }
        ಆದರೆ (Rmask == 0x7C00 &&
            Gmask == 0x03E0 &&
            Bmask == 0x001F &&
            Amask == 0x8000) {
            ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_ARGB1555;
        }
        ಆದರೆ (Rmask == 0xF800 &&
            Gmask == 0x07C0 &&
            Bmask == 0x003E &&
            Amask == 0x0001) {
            ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_RGBA5551;
        }
        ಆದರೆ (Rmask == 0x001F &&
            Gmask == 0x03E0 &&
            Bmask == 0x7C00 &&
            Amask == 0x8000) {
            ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_ABGR1555;
        }
        ಆದರೆ (Rmask == 0x003E &&
            Gmask == 0x07C0 &&
            Bmask == 0xF800 &&
            Amask == 0x0001) {
            ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_BGRA5551;
        }
        ಆದರೆ (Rmask == 0xF800 &&
            Gmask == 0x07E0 &&
            Bmask == 0x001F &&
            Amask == 0x0000) {
            ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_RGB565;
        }
        ಆದರೆ (Rmask == 0x001F &&
            Gmask == 0x07E0 &&
            Bmask == 0xF800 &&
            Amask == 0x0000) {
            ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_BGR565;
        }
        ಆದರೆ (Rmask == 0x003F &&
            Gmask == 0x07C0 &&
            Bmask == 0xF800 &&
            Amask == 0x0000) {
            // Technically this would be BGR556, but Witek says this works in bug 3158
            ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_RGB565;
        }
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 24:
        ಆಯ್ಕೆ (Rmask) {
        ಸ್ಥಿತಿ 0:
        ಸ್ಥಿತಿ 0x00FF0000:
#ಆದರೆ SDL_BYTEORDER == SDL_BIG_ENDIAN
            ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_RGB24;
#ಇಲ್ಲದಿದ್ದರೆ
            ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_BGR24;
#ಆದರೆ_ಅಂತ್ಯ
        ಸ್ಥಿತಿ 0x000000FF:
#ಆದರೆ SDL_BYTEORDER == SDL_BIG_ENDIAN
            ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_BGR24;
#ಇಲ್ಲದಿದ್ದರೆ
            ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_RGB24;
#ಆದರೆ_ಅಂತ್ಯ
        }
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 30:
        ಆದರೆ (Rmask == 0x3FF00000 &&
            Gmask == 0x000FFC00 &&
            Bmask == 0x000003FF &&
            Amask == 0x00000000) {
            ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_XRGB2101010;
        }
        ಆದರೆ (Rmask == 0x000003FF &&
            Gmask == 0x000FFC00 &&
            Bmask == 0x3FF00000 &&
            Amask == 0x00000000) {
            ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_XBGR2101010;
        }
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ 32:
        ಆದರೆ (Rmask == 0) {
            ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_XRGB8888;
        }
        ಆದರೆ (Rmask == 0x00FF0000 &&
            Gmask == 0x0000FF00 &&
            Bmask == 0x000000FF &&
            Amask == 0x00000000) {
            ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_XRGB8888;
        }
        ಆದರೆ (Rmask == 0xFF000000 &&
            Gmask == 0x00FF0000 &&
            Bmask == 0x0000FF00 &&
            Amask == 0x00000000) {
            ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_RGBX8888;
        }
        ಆದರೆ (Rmask == 0x000000FF &&
            Gmask == 0x0000FF00 &&
            Bmask == 0x00FF0000 &&
            Amask == 0x00000000) {
            ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_XBGR8888;
        }
        ಆದರೆ (Rmask == 0x0000FF00 &&
            Gmask == 0x00FF0000 &&
            Bmask == 0xFF000000 &&
            Amask == 0x00000000) {
            ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_BGRX8888;
        }
        ಆದರೆ (Rmask == 0x00FF0000 &&
            Gmask == 0x0000FF00 &&
            Bmask == 0x000000FF &&
            Amask == 0xFF000000) {
            ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_ARGB8888;
        }
        ಆದರೆ (Rmask == 0xFF000000 &&
            Gmask == 0x00FF0000 &&
            Bmask == 0x0000FF00 &&
            Amask == 0x000000FF) {
            ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_RGBA8888;
        }
        ಆದರೆ (Rmask == 0x000000FF &&
            Gmask == 0x0000FF00 &&
            Bmask == 0x00FF0000 &&
            Amask == 0xFF000000) {
            ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_ABGR8888;
        }
        ಆದರೆ (Rmask == 0x0000FF00 &&
            Gmask == 0x00FF0000 &&
            Bmask == 0xFF000000 &&
            Amask == 0x000000FF) {
            ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_BGRA8888;
        }
        ಆದರೆ (Rmask == 0x3FF00000 &&
            Gmask == 0x000FFC00 &&
            Bmask == 0x000003FF &&
            Amask == 0x00000000) {
            ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_XRGB2101010;
        }
        ಆದರೆ (Rmask == 0x000003FF &&
            Gmask == 0x000FFC00 &&
            Bmask == 0x3FF00000 &&
            Amask == 0x00000000) {
            ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_XBGR2101010;
        }
        ಆದರೆ (Rmask == 0x3FF00000 &&
            Gmask == 0x000FFC00 &&
            Bmask == 0x000003FF &&
            Amask == 0xC0000000) {
            ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_ARGB2101010;
        }
        ಆದರೆ (Rmask == 0x000003FF &&
            Gmask == 0x000FFC00 &&
            Bmask == 0x3FF00000 &&
            Amask == 0xC0000000) {
            ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_ABGR2101010;
        }
        ನಿಲ್ಲಿಸು;
    }
    ಹಿಂತಿರುಗಿ SDL_PIXELFORMAT_UNKNOWN;
}

ಸ್ಥಿರ SDL_InitState SDL_format_details_init;
ಸ್ಥಿರ SDL_Hash_ಕೋಷ್ಟಕ *SDL_format_details;

ಸ್ಥಿರ bool SDL_InitPixelFormatDetails(SDL_PixelFormatDetails *details, SDL_PixelFormat format)
{
    ಪೂರ್ಣಾಂಕ bpp;
    Uint32 Rmask, Gmask, Bmask, Amask;
    Uint32 ಮುಖವಾಡ;

    ಆದರೆ (!SDL_GetMasksForPixelFormat(format, &bpp, &Rmask, &Gmask, &Bmask, &Amask)) {
        ಹಿಂತಿರುಗಿ false;
    }

    // Set up the format
    SDL_zerop(details);
    details->format = format;
    details->ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_pixel = (Uint8)bpp;
    details->ಬೈಟುಗಳು_ಪ್ರತಿ_pixel = (Uint8)((bpp + 7) / 8);

    details->Rmask = Rmask;
    details->Rshift = 0;
    details->Rbits = 0;
    ಆದರೆ (Rmask) {
        ಗಾಗಿ (ಮುಖವಾಡ = Rmask; !(ಮುಖವಾಡ & 0x01); ಮುಖವಾಡ >>= 1) {
            ++details->Rshift;
        }
        ಗಾಗಿ (; (ಮುಖವಾಡ & 0x01); ಮುಖವಾಡ >>= 1) {
            ++details->Rbits;
        }
    }

    details->Gmask = Gmask;
    details->Gshift = 0;
    details->Gbits = 0;
    ಆದರೆ (Gmask) {
        ಗಾಗಿ (ಮುಖವಾಡ = Gmask; !(ಮುಖವಾಡ & 0x01); ಮುಖವಾಡ >>= 1) {
            ++details->Gshift;
        }
        ಗಾಗಿ (; (ಮುಖವಾಡ & 0x01); ಮುಖವಾಡ >>= 1) {
            ++details->Gbits;
        }
    }

    details->Bmask = Bmask;
    details->Bshift = 0;
    details->Bbits = 0;
    ಆದರೆ (Bmask) {
        ಗಾಗಿ (ಮುಖವಾಡ = Bmask; !(ಮುಖವಾಡ & 0x01); ಮುಖವಾಡ >>= 1) {
            ++details->Bshift;
        }
        ಗಾಗಿ (; (ಮುಖವಾಡ & 0x01); ಮುಖವಾಡ >>= 1) {
            ++details->Bbits;
        }
    }

    details->Amask = Amask;
    details->Ashift = 0;
    details->Abits = 0;
    ಆದರೆ (Amask) {
        ಗಾಗಿ (ಮುಖವಾಡ = Amask; !(ಮುಖವಾಡ & 0x01); ಮುಖವಾಡ >>= 1) {
            ++details->Ashift;
        }
        ಗಾಗಿ (; (ಮುಖವಾಡ & 0x01); ಮುಖವಾಡ >>= 1) {
            ++details->Abits;
        }
    }

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *SDL_GetPixelFormatDetails(SDL_PixelFormat format)
{
    SDL_PixelFormatDetails *details;

    ಆದರೆ (SDL_ShouldInit(&SDL_format_details_init)) {
        SDL_format_details = SDL_Create_Hash_ಕೋಷ್ಟಕ(0, true, SDL_HashID, SDL_ಕೀಲಿ_ಹೊಂದಿಕೆ_ID, SDL_Destroy_Hash_ಮೌಲ್ಯ, ಖಾಲಿ);
        ಆದರೆ (!SDL_format_details) {
            SDL_ಗಣ_Initialized(&SDL_format_details_init, false);
            ಹಿಂತಿರುಗಿ ಖಾಲಿ;
        }
        SDL_ಗಣ_Initialized(&SDL_format_details_init, true);
    }

    ಆದರೆ (SDL_ಕಂಡುಹಿಡಿ_ಒಳ_Hash_ಕೋಷ್ಟಕ(SDL_format_details, (ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *)(uintptr_t)format, (ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ **)&details)) {
        ಹಿಂತಿರುಗಿ details;
    }

    // Allocate an empty pixel format structure, and initialize it
    details = (SDL_PixelFormatDetails *)SDL_malloc(ಗಾತ್ರ(*details));
    ಆದರೆ (!details) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಆದರೆ (!SDL_InitPixelFormatDetails(details, format)) {
        SDL_free(details);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಆದರೆ (!SDL_ಸೇರಿಸು_Into_Hash_ಕೋಷ್ಟಕ(SDL_format_details, (ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *)(uintptr_t)format, (ಶೂನ್ಯ *)details, false)) {
        SDL_free(details);
        // uh...did another thread beat us to inserting this?
        ಆದರೆ (SDL_ಕಂಡುಹಿಡಿ_ಒಳ_Hash_ಕೋಷ್ಟಕ(SDL_format_details, (ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *)(uintptr_t)format, (ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ **)&details)) {
            ಹಿಂತಿರುಗಿ details;
        }
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;  // oh well.
    }

    ಹಿಂತಿರುಗಿ details;
}

ಶೂನ್ಯ SDL_QuitPixelFormatDetails(ಶೂನ್ಯ)
{
    ಆದರೆ (SDL_ShouldQuit(&SDL_format_details_init)) {
        SDL_Destroy_Hash_ಕೋಷ್ಟಕ(SDL_format_details);
        SDL_format_details = ಖಾಲಿ;
        SDL_ಗಣ_Initialized(&SDL_format_details_init, false);
    }
}

ಶೂನ್ಯ SDL_Get8888_Alpha_ಮುಖವಾಡ_And_ಸರಿಸು(ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *fmt, Uint32 *ಮುಖವಾಡ, Uint32 *ಸರಿಸು)
{
    ಆದರೆ (fmt->Amask) {
        *ಮುಖವಾಡ = fmt->Amask;
        *ಸರಿಸು = fmt->Ashift;
    } ಇಲ್ಲದಿದ್ದರೆ {
        *ಮುಖವಾಡ = ~(fmt->Rmask | fmt->Gmask | fmt->Bmask);
        ಆಯ್ಕೆ (*ಮುಖವಾಡ) {
        ಸ್ಥಿತಿ 0x000000FF:
            *ಸರಿಸು = 0;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ 0x0000FF00:
            *ಸರಿಸು = 8;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ 0x00FF0000:
            *ಸರಿಸು = 16;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ 0xFF000000:
            *ಸರಿಸು = 24;
            ನಿಲ್ಲಿಸು;
        ಪೂರ್ವನಿಯೋಜಿತ:
            // Should never happen
            *ಸರಿಸು = 0;
            ನಿಲ್ಲಿಸು;
        }
    }
}

SDL_Colorspace SDL_GetDefaultColorspaceForFormat(SDL_PixelFormat format)
{
    ಆದರೆ (SDL_ISPIXELFORMAT_FOURCC(format)) {
        ಆದರೆ (format == SDL_PIXELFORMAT_MJPG) {
            ಹಿಂತಿರುಗಿ SDL_COLORSPACE_SRGB;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (format == SDL_PIXELFORMAT_P010 || format == SDL_PIXELFORMAT_I0FL || format == SDL_PIXELFORMAT_I4FL) {
            ಹಿಂತಿರುಗಿ SDL_COLORSPACE_HDR10;
        } ಇಲ್ಲದಿದ್ದರೆ {
            ಹಿಂತಿರುಗಿ SDL_COLORSPACE_YUV_DEFAULT;
        }
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_ISPIXELFORMAT_FLOAT(format)) {
        ಹಿಂತಿರುಗಿ SDL_COLORSPACE_SRGB_ರೇಖೀಯ;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (SDL_ISPIXELFORMAT_10_ಬಿಟ್(format)) {
        ಹಿಂತಿರುಗಿ SDL_COLORSPACE_HDR10;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ SDL_COLORSPACE_RGB_DEFAULT;
    }
}

ದಶಮಾಂಶ SDL_s_RGBto_ರೇಖೀಯ(ದಶಮಾಂಶ v)
{
    ಆದರೆ (v <= 0.04045f) {
        v = (v / 12.92f);
    } ಇಲ್ಲದಿದ್ದರೆ {
        v = SDL_powf((v + 0.055f) / 1.055f, 2.4f);
    }
    ಹಿಂತಿರುಗಿ v;
}

ದಶಮಾಂಶ SDL_s_RGBfrom_ರೇಖೀಯ(ದಶಮಾಂಶ v)
{
    ಆದರೆ (v <= 0.0031308f) {
        v = (v * 12.92f);
    } ಇಲ್ಲದಿದ್ದರೆ {
        v = (SDL_powf(v, 1.0f / 2.4f) * 1.055f - 0.055f);
    }
    ಹಿಂತಿರುಗಿ v;
}

ದಶಮಾಂಶ SDL_PQtoNits(ದಶಮಾಂಶ v)
{
    ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ c1 = 0.8359375f;
    ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ c2 = 18.8515625f;
    ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ c3 = 18.6875f;
    ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ oo_m1 = 1.0f / 0.1593017578125f;
    ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ oo_m2 = 1.0f / 78.84375f;

    ದಶಮಾಂಶ ಅಂಕೆ = SDL_max(SDL_powf(v, oo_m2) - c1, 0.0f);
    ದಶಮಾಂಶ den = c2 - c3 * SDL_powf(v, oo_m2);
    ಹಿಂತಿರುಗಿ 10000.0f * SDL_powf(ಅಂಕೆ / den, oo_m1);
}

ದಶಮಾಂಶ SDL_PQfromNits(ದಶಮಾಂಶ v)
{
    ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ c1 = 0.8359375f;
    ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ c2 = 18.8515625f;
    ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ c3 = 18.6875f;
    ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ m1 = 0.1593017578125f;
    ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ m2 = 78.84375f;

    ದಶಮಾಂಶ y = SDL_clamp(v / 10000.0f, 0.0f, 1.0f);
    ದಶಮಾಂಶ ಅಂಕೆ = c1 + c2 * SDL_powf(y, m1);
    ದಶಮಾಂಶ den = 1.0f + c3 * SDL_powf(y, m1);
    ಹಿಂತಿರುಗಿ SDL_powf(ಅಂಕೆ / den, m2);
}

/* This is a helpful tool for deriving these:
 * https://kdashg.github.io/misc/colors/from-coeffs.html
 */
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ mat_BT601_Limited_8bit[] = {
    -0.0627451017f, -0.501960814f, -0.501960814f, 0.0f, //ಸ್ಥಾನಾಂತರ
    1.1644f, 0.0000f, 1.5960f, 0.0f,                    // Rcoeff
    1.1644f, -0.3918f, -0.8130f, 0.0f,                  // Gcoeff
    1.1644f, 2.0172f, 0.0000f, 0.0f,                    // Bcoeff
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ mat_BT601_ತುಂಬಿದ_8bit[] = {
    0.0f, -0.501960814f, -0.501960814f, 0.0f,           //ಸ್ಥಾನಾಂತರ
    1.0000f, 0.0000f, 1.4075f, 0.0f,                    // Rcoeff
    1.0000f, -0.3455f, -0.7169f, 0.0f,                  // Gcoeff
    1.0000f, 1.7790f, 0.0000f, 0.0f,                    // Bcoeff
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ mat_BT709_Limited_8bit[] = {
    -0.0627451017f, -0.501960814f, -0.501960814f, 0.0f, //ಸ್ಥಾನಾಂತರ
    1.1644f, 0.0000f, 1.7927f, 0.0f,                    // Rcoeff
    1.1644f, -0.2132f, -0.5329f, 0.0f,                  // Gcoeff
    1.1644f, 2.1124f, 0.0000f, 0.0f,                    // Bcoeff
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ mat_BT709_ತುಂಬಿದ_8bit[] = {
    0.0f, -0.501960814f, -0.501960814f, 0.0f,           //ಸ್ಥಾನಾಂತರ
    1.0000f, 0.0000f, 1.5810f, 0.0f,                    // Rcoeff
    1.0000f, -0.1881f, -0.4700f, 0.0f,                  // Gcoeff
    1.0000f, 1.8629f, 0.0000f, 0.0f,                    // Bcoeff
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ mat_BT2020_Limited_10bit[] = {
    -0.062561095f, -0.500488759f, -0.500488759f, 0.0f,  //ಸ್ಥಾನಾಂತರ
    1.1678f, 0.0000f, 1.6836f, 0.0f,                    // Rcoeff
    1.1678f, -0.1879f, -0.6523f, 0.0f,                  // Gcoeff
    1.1678f, 2.1481f, 0.0000f, 0.0f,                    // Bcoeff
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ mat_BT2020_ತುಂಬಿದ_10bit[] = {
    0.0f, -0.500488759f, -0.500488759f, 0.0f,           //ಸ್ಥಾನಾಂತರ
    1.0000f, 0.0000f, 1.4760f, 0.0f,                    // Rcoeff
    1.0000f, -0.1647f, -0.5719f, 0.0f,                  // Gcoeff
    1.0000f, 1.8832f, 0.0000f, 0.0f,                    // Bcoeff
};

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *SDL_Get_BT601_Conversion_ಮಾತೃಕೆ( SDL_Colorspace colorspace )
{
    ಆಯ್ಕೆ (SDL_COLORSPACERANGE(colorspace)) {
    ಸ್ಥಿತಿ SDL_COLOR_RANGE_LIMITED:
    ಸ್ಥಿತಿ SDL_COLOR_RANGE_UNKNOWN:
        ಹಿಂತಿರುಗಿ mat_BT601_Limited_8bit;
    ಸ್ಥಿತಿ SDL_COLOR_RANGE_ತುಂಬಿದ:
        ಹಿಂತಿರುಗಿ mat_BT601_ತುಂಬಿದ_8bit;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ನಿಲ್ಲಿಸು;
    }
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *SDL_Get_BT709_Conversion_ಮಾತೃಕೆ(SDL_Colorspace colorspace)
{
    ಆಯ್ಕೆ (SDL_COLORSPACERANGE(colorspace)) {
    ಸ್ಥಿತಿ SDL_COLOR_RANGE_LIMITED:
    ಸ್ಥಿತಿ SDL_COLOR_RANGE_UNKNOWN:
        ಹಿಂತಿರುಗಿ mat_BT709_Limited_8bit;
    ಸ್ಥಿತಿ SDL_COLOR_RANGE_ತುಂಬಿದ:
        ಹಿಂತಿರುಗಿ mat_BT709_ತುಂಬಿದ_8bit;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ನಿಲ್ಲಿಸು;
    }
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *SDL_Get_BT2020_Conversion_ಮಾತೃಕೆ(SDL_Colorspace colorspace)
{
    ಆಯ್ಕೆ (SDL_COLORSPACERANGE(colorspace)) {
    ಸ್ಥಿತಿ SDL_COLOR_RANGE_LIMITED:
    ಸ್ಥಿತಿ SDL_COLOR_RANGE_UNKNOWN:
        ಹಿಂತಿರುಗಿ mat_BT2020_Limited_10bit;
    ಸ್ಥಿತಿ SDL_COLOR_RANGE_ತುಂಬಿದ:
        ಹಿಂತಿರುಗಿ mat_BT2020_ತುಂಬಿದ_10bit;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ನಿಲ್ಲಿಸು;
    }
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *SDL_Get_YCb_CRto_RGBConversion_ಮಾತೃಕೆ(SDL_Colorspace colorspace, ಪೂರ್ಣಾಂಕ w, ಪೂರ್ಣಾಂಕ h, ಪೂರ್ಣಾಂಕ ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_pixel)
{
    ಆಯ್ಕೆ (SDL_COLORSPACEMATRIX(colorspace)) {
    ಸ್ಥಿತಿ SDL_ಮಾತೃಕೆ_COEFFICIENTS_BT601:
    ಸ್ಥಿತಿ SDL_ಮಾತೃಕೆ_COEFFICIENTS_BT470_BG:
        ಹಿಂತಿರುಗಿ SDL_Get_BT601_Conversion_ಮಾತೃಕೆ(colorspace);

    ಸ್ಥಿತಿ SDL_ಮಾತೃಕೆ_COEFFICIENTS_BT709:
        ಹಿಂತಿರುಗಿ SDL_Get_BT709_Conversion_ಮಾತೃಕೆ(colorspace);

    ಸ್ಥಿತಿ SDL_ಮಾತೃಕೆ_COEFFICIENTS_BT2020_NCL:
        ಹಿಂತಿರುಗಿ SDL_Get_BT2020_Conversion_ಮಾತೃಕೆ(colorspace);

    ಸ್ಥಿತಿ SDL_ಮಾತೃಕೆ_COEFFICIENTS_UNSPECIFIED:
        ಆಯ್ಕೆ (ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_pixel) {
        ಸ್ಥಿತಿ 8:
            ಆದರೆ (h <= YUV_SD_ಮಿತಿ) {
                ಹಿಂತಿರುಗಿ SDL_Get_BT601_Conversion_ಮಾತೃಕೆ(colorspace);
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಹಿಂತಿರುಗಿ SDL_Get_BT709_Conversion_ಮಾತೃಕೆ(colorspace);
            }
        ಸ್ಥಿತಿ 10:
        ಸ್ಥಿತಿ 16:
            ಹಿಂತಿರುಗಿ SDL_Get_BT2020_Conversion_ಮಾತೃಕೆ(colorspace);
        ಪೂರ್ವನಿಯೋಜಿತ:
            ನಿಲ್ಲಿಸು;
        }
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ನಿಲ್ಲಿಸು;
    }
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

/* Conversion matrices generated using gamescope color helpers and the primaries definitions at:
    * https://www.itu.int/rec/T-REC-H.273-201612-S/en
    *
    * You can also generate these online using the RGB-XYZ matrix calculator, and then multiplying
    * XYZ_to_dst * src_to_XYZ to get the combined conversion matrix:
    * https://www.russellcottrell.com/photo/matrixCalculator.htm
    */
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ mat601to709[] = {
    0.939542f, 0.050181f, 0.010277f,
    0.017772f, 0.965793f, 0.016435f,
    -0.001622f, -0.004370f, 1.005991f,
};
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ mat601to2020[] = {
    0.595254f, 0.349314f, 0.055432f,
    0.081244f, 0.891503f, 0.027253f,
    0.015512f, 0.081912f, 0.902576f,
};
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ mat709to601[] = {
    1.065379f, -0.055401f, -0.009978f,
    -0.019633f, 1.036363f, -0.016731f,
    0.001632f, 0.004412f, 0.993956f,
};
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ mat709to2020[] = {
    0.627404f, 0.329283f, 0.043313f,
    0.069097f, 0.919541f, 0.011362f,
    0.016391f, 0.088013f, 0.895595f,
};
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ mat2020to601[] = {
    1.776133f, -0.687820f, -0.088313f,
    -0.161376f, 1.187315f, -0.025940f,
    -0.015881f, -0.095931f, 1.111812f,
};
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ mat2020to709[] = {
    1.660496f, -0.587656f, -0.072840f,
    -0.124547f, 1.132895f, -0.008348f,
    -0.018154f, -0.100597f, 1.118751f
};
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ matSMPTE431to709[] = {
    1.120713f, -0.234649f, 0.000000f,
    -0.038478f, 1.087034f, 0.000000f,
    -0.017967f, -0.082030f, 0.954576f,
};
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ matSMPTE431to2020[] = {
    0.689691f, 0.207169f, 0.041346f,
    0.041852f, 0.982426f, 0.010846f,
    -0.001107f, 0.018362f, 0.854914f,
};
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ matSMPTE432to709[] = {
    1.224940f, -0.224940f, -0.000000f,
    -0.042057f, 1.042057f, 0.000000f,
    -0.019638f, -0.078636f, 1.098273f,
};
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ matSMPTE432to2020[] = {
    0.753833f, 0.198597f, 0.047570f,
    0.045744f, 0.941777f, 0.012479f,
    -0.001210f, 0.017602f, 0.983609f,
};

ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *SDL_Get_Color_Primaries_Conversion_ಮಾತೃಕೆ(SDL_ColorPrimaries src, SDL_ColorPrimaries dst)
{
    ಆಯ್ಕೆ (dst) {
    ಸ್ಥಿತಿ SDL_COLOR_PRIMARIES_BT601:
    ಸ್ಥಿತಿ SDL_COLOR_PRIMARIES_SMPTE240:
        ಆಯ್ಕೆ (src) {
        ಸ್ಥಿತಿ SDL_COLOR_PRIMARIES_BT709:
            ಹಿಂತಿರುಗಿ mat709to601;
        ಸ್ಥಿತಿ SDL_COLOR_PRIMARIES_BT2020:
            ಹಿಂತಿರುಗಿ mat2020to601;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ನಿಲ್ಲಿಸು;
        }
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_COLOR_PRIMARIES_BT709:
        ಆಯ್ಕೆ (src) {
        ಸ್ಥಿತಿ SDL_COLOR_PRIMARIES_BT601:
        ಸ್ಥಿತಿ SDL_COLOR_PRIMARIES_SMPTE240:
            ಹಿಂತಿರುಗಿ mat601to709;
        ಸ್ಥಿತಿ SDL_COLOR_PRIMARIES_BT2020:
            ಹಿಂತಿರುಗಿ mat2020to709;
        ಸ್ಥಿತಿ SDL_COLOR_PRIMARIES_SMPTE431:
            ಹಿಂತಿರುಗಿ matSMPTE431to709;
        ಸ್ಥಿತಿ SDL_COLOR_PRIMARIES_SMPTE432:
            ಹಿಂತಿರುಗಿ matSMPTE432to709;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ನಿಲ್ಲಿಸು;
        }
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_COLOR_PRIMARIES_BT2020:
        ಆಯ್ಕೆ (src) {
        ಸ್ಥಿತಿ SDL_COLOR_PRIMARIES_BT601:
        ಸ್ಥಿತಿ SDL_COLOR_PRIMARIES_SMPTE240:
            ಹಿಂತಿರುಗಿ mat601to2020;
        ಸ್ಥಿತಿ SDL_COLOR_PRIMARIES_BT709:
            ಹಿಂತಿರುಗಿ mat709to2020;
        ಸ್ಥಿತಿ SDL_COLOR_PRIMARIES_SMPTE431:
            ಹಿಂತಿರುಗಿ matSMPTE431to2020;
        ಸ್ಥಿತಿ SDL_COLOR_PRIMARIES_SMPTE432:
            ಹಿಂತಿರುಗಿ matSMPTE432to2020;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ನಿಲ್ಲಿಸು;
        }
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ನಿಲ್ಲಿಸು;
    }
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಶೂನ್ಯ SDL_ConvertColorPrimaries(ದಶಮಾಂಶ *fR, ದಶಮಾಂಶ *fG, ದಶಮಾಂಶ *fB, ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ *ಮಾತೃಕೆ)
{
    ದಶಮಾಂಶ v[3];

    v[0] = *fR;
    v[1] = *fG;
    v[2] = *fB;

    *fR = ಮಾತೃಕೆ[0 * 3 + 0] * v[0] + ಮಾತೃಕೆ[0 * 3 + 1] * v[1] + ಮಾತೃಕೆ[0 * 3 + 2] * v[2];
    *fG = ಮಾತೃಕೆ[1 * 3 + 0] * v[0] + ಮಾತೃಕೆ[1 * 3 + 1] * v[1] + ಮಾತೃಕೆ[1 * 3 + 2] * v[2];
    *fB = ಮಾತೃಕೆ[2 * 3 + 0] * v[0] + ಮಾತೃಕೆ[2 * 3 + 1] * v[1] + ಮಾತೃಕೆ[2 * 3 + 2] * v[2];
}

ಶೂನ್ಯ SDL_ConvertColor709to2020(ದಶಮಾಂಶ *fR, ದಶಮಾಂಶ *fG, ದಶಮಾಂಶ *fB)
{
    SDL_ConvertColorPrimaries(fR, fG, fB, mat709to2020);
}

SDL_Palette *SDL_CreatePalette(ಪೂರ್ಣಾಂಕ ncolors)
{
    SDL_Palette *palette;

    // Input validation
    CHECK_PARAM(ncolors < 1) {
        SDL_InvalidParamError("ncolors");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    palette = (SDL_Palette *)SDL_malloc(ಗಾತ್ರ(*palette));
    ಆದರೆ (!palette) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    palette->colors = (SDL_Color *)SDL_malloc(ncolors * ಗಾತ್ರ(*palette->colors));
    ಆದರೆ (!palette->colors) {
        SDL_free(palette);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    palette->ncolors = ncolors;
    palette->ಆವೃತ್ತಿ = 1;
    palette->refcount = 1;

    SDL_memset(palette->colors, 0xFF, ncolors * ಗಾತ್ರ(*palette->colors));

    ಹಿಂತಿರುಗಿ palette;
}

bool SDL_ಗಣ_Palette_Colors(SDL_Palette *palette, ಸ್ಥಿರಾಂಕ SDL_Color *colors, ಪೂರ್ಣಾಂಕ firstcolor, ಪೂರ್ಣಾಂಕ ncolors)
{
    // Verify the parameters
    ಆದರೆ (!palette) {
        ಹಿಂತಿರುಗಿ false;
    }
    ಆದರೆ (ncolors > (palette->ncolors - firstcolor)) {
        ncolors = (palette->ncolors - firstcolor);
    }

    ಆದರೆ (colors != (palette->colors + firstcolor)) {
        SDL_memcpy(palette->colors + firstcolor, colors,
                   ncolors * ಗಾತ್ರ(*colors));
    }
    ++palette->ಆವೃತ್ತಿ;
    ಆದರೆ (!palette->ಆವೃತ್ತಿ) {
        palette->ಆವೃತ್ತಿ = 1;
    }

    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ SDL_DestroyPalette(SDL_Palette *palette)
{
    ಆದರೆ (!palette) {
        ಹಿಂತಿರುಗಿ;
    }
    ಆದರೆ (--palette->refcount > 0) {
        ಹಿಂತಿರುಗಿ;
    }
    SDL_free(palette->colors);
    SDL_free(palette);
}

/*
 * Calculate an 8-bit (3 red, 3 green, 2 blue) dithered palette of colors
 */
ಶೂನ್ಯ SDL_DitherPalette(SDL_Palette *palette)
{
    ಪೂರ್ಣಾಂಕ i;
    ಆದರೆ (palette->ncolors != 256) {
        ಹಿಂತಿರುಗಿ; // only 8bpp supported right now
    }

    ಗಾಗಿ (i = 0; i < palette->ncolors; i++) {
        ಪೂರ್ಣಾಂಕ r, g, b;
        /* map each bit field to the full [0, 255] interval,
           so 0 is mapped to (0, 0, 0) and 255 to (255, 255, 255) */
        r = i & 0xe0;
        r |= r >> 3 | r >> 6;
        palette->colors[i].r = (Uint8)r;
        g = (i << 3) & 0xe0;
        g |= g >> 3 | g >> 6;
        palette->colors[i].g = (Uint8)g;
        b = i & 0x3;
        b |= b << 2;
        b |= b << 4;
        palette->colors[i].b = (Uint8)b;
        palette->colors[i].a = SDL_ALPHA_OPAQUE;
    }
}

/*
 * Match an RGB value to a particular palette index
 */
ಸ್ಥಿರ Uint8 SDL_ಕಂಡುಹಿಡಿ_Color(ಸ್ಥಿರಾಂಕ SDL_Palette *pal, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    // Do colorspace distance matching
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಅತಿಚಿಕ್ಕ;
    ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ದೂರ;
    ಪೂರ್ಣಾಂಕ rd, gd, bd, ad;
    ಪೂರ್ಣಾಂಕ i;
    Uint8 pixelvalue = 0;

    ಅತಿಚಿಕ್ಕ = ~0U;
    ಗಾಗಿ (i = 0; i < pal->ncolors; ++i) {
        rd = pal->colors[i].r - r;
        gd = pal->colors[i].g - g;
        bd = pal->colors[i].b - b;
        ad = pal->colors[i].a - a;
        ದೂರ = (rd * rd) + (gd * gd) + (bd * bd) + (ad * ad);
        ಆದರೆ (ದೂರ < ಅತಿಚಿಕ್ಕ) {
            pixelvalue = (Uint8)i;
            ಆದರೆ (ದೂರ == 0) { // Perfect match!
                ನಿಲ್ಲಿಸು;
            }
            ಅತಿಚಿಕ್ಕ = ದೂರ;
        }
    }
    ಹಿಂತಿರುಗಿ pixelvalue;
}

Uint8 SDL_LookupRGBAColor(SDL_Hash_ಕೋಷ್ಟಕ *palette_map, Uint32 pixelvalue, ಸ್ಥಿರಾಂಕ SDL_Palette *pal)
{
    Uint8 color_ಸೂಚ್ಯಂಕ = 0;
    ಆದರೆ (pal) {
        ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *ಮೌಲ್ಯ;
        ಆದರೆ (SDL_ಕಂಡುಹಿಡಿ_ಒಳ_Hash_ಕೋಷ್ಟಕ(palette_map, (ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *)(uintptr_t)pixelvalue, &ಮೌಲ್ಯ)) {
            color_ಸೂಚ್ಯಂಕ = (Uint8)(uintptr_t)ಮೌಲ್ಯ;
        } ಇಲ್ಲದಿದ್ದರೆ {
            Uint8 r = (Uint8)((pixelvalue >> 24) & 0xFF);
            Uint8 g = (Uint8)((pixelvalue >> 16) & 0xFF);
            Uint8 b = (Uint8)((pixelvalue >>  8) & 0xFF);
            Uint8 a = (Uint8)((pixelvalue >>  0) & 0xFF);
            color_ಸೂಚ್ಯಂಕ = SDL_ಕಂಡುಹಿಡಿ_Color(pal, r, g, b, a);
            SDL_ಸೇರಿಸು_Into_Hash_ಕೋಷ್ಟಕ(palette_map, (ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *)(uintptr_t)pixelvalue, (ಸ್ಥಿರಾಂಕ ಶೂನ್ಯ *)(uintptr_t)color_ಸೂಚ್ಯಂಕ, true);
        }
    }
    ಹಿಂತಿರುಗಿ color_ಸೂಚ್ಯಂಕ;
}

// Tell whether palette is opaque, and if it has an alpha_channel
ಶೂನ್ಯ SDL_DetectPalette(ಸ್ಥಿರಾಂಕ SDL_Palette *pal, bool *is_opaque, bool *has_alpha_channel)
{
    ಪೂರ್ಣಾಂಕ i;

    {
        bool all_opaque = true;
        ಗಾಗಿ (i = 0; i < pal->ncolors; i++) {
            Uint8 alpha_ಮೌಲ್ಯ = pal->colors[i].a;
            ಆದರೆ (alpha_ಮೌಲ್ಯ != SDL_ALPHA_OPAQUE) {
                all_opaque = false;
                ನಿಲ್ಲಿಸು;
            }
        }

        ಆದರೆ (all_opaque) {
            // Palette is opaque, with an alpha channel
            *is_opaque = true;
            *has_alpha_channel = true;
            ಹಿಂತಿರುಗಿ;
        }
    }

    {
        bool all_transparent = true;
        ಗಾಗಿ (i = 0; i < pal->ncolors; i++) {
            Uint8 alpha_ಮೌಲ್ಯ = pal->colors[i].a;
            ಆದರೆ (alpha_ಮೌಲ್ಯ != SDL_ALPHA_TRANSPARENT) {
                all_transparent = false;
                ನಿಲ್ಲಿಸು;
            }
        }

        ಆದರೆ (all_transparent) {
            // Palette is opaque, without an alpha channel
            *is_opaque = true;
            *has_alpha_channel = false;
            ಹಿಂತಿರುಗಿ;
        }
    }

    // Palette has alpha values
    *is_opaque = false;
    *has_alpha_channel = true;
}

// Find the opaque pixel value corresponding to an RGB triple
Uint32 SDL_MapRGB(ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *format, ಸ್ಥಿರಾಂಕ SDL_Palette *palette, Uint8 r, Uint8 g, Uint8 b)
{
    CHECK_PARAM(!format) {
        SDL_InvalidParamError("format");
        ಹಿಂತಿರುಗಿ 0;
    }

    ಆದರೆ (SDL_ISPIXELFORMAT_ಸೂಚ್ಯಂಕಿತ(format->format)) {
        CHECK_PARAM(!palette) {
            SDL_InvalidParamError("palette");
            ಹಿಂತಿರುಗಿ 0;
        }
        ಹಿಂತಿರುಗಿ SDL_ಕಂಡುಹಿಡಿ_Color(palette, r, g, b, SDL_ALPHA_OPAQUE);
    }

    ಆದರೆ (SDL_ISPIXELFORMAT_10_ಬಿಟ್(format->format)) {
        ಹಿಂತಿರುಗಿ (((Uint32)SDL_expand_byte_10[r]) << format->Rshift) |
               (((Uint32)SDL_expand_byte_10[g]) << format->Gshift) |
               (((Uint32)SDL_expand_byte_10[b]) << format->Bshift) |
               format->Amask;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ ((Uint32)(r >> (8 - format->Rbits))) << format->Rshift |
               ((Uint32)(g >> (8 - format->Gbits))) << format->Gshift |
               ((Uint32)(b >> (8 - format->Bbits))) << format->Bshift |
               format->Amask;
    }
}

// Find the pixel value corresponding to an RGBA quadruple
Uint32 SDL_MapRGBA(ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *format, ಸ್ಥಿರಾಂಕ SDL_Palette *palette, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    CHECK_PARAM(!format) {
        SDL_InvalidParamError("format");
        ಹಿಂತಿರುಗಿ 0;
    }

    ಆದರೆ (SDL_ISPIXELFORMAT_ಸೂಚ್ಯಂಕಿತ(format->format)) {
        CHECK_PARAM(!palette) {
            SDL_InvalidParamError("palette");
            ಹಿಂತಿರುಗಿ 0;
        }
        ಹಿಂತಿರುಗಿ SDL_ಕಂಡುಹಿಡಿ_Color(palette, r, g, b, a);
    }

    ಆದರೆ (SDL_ISPIXELFORMAT_10_ಬಿಟ್(format->format)) {
        ಹಿಂತಿರುಗಿ (((Uint32)SDL_expand_byte_10[r]) << format->Rshift) |
               (((Uint32)SDL_expand_byte_10[g]) << format->Gshift) |
               (((Uint32)SDL_expand_byte_10[b]) << format->Bshift) |
               ((((Uint32)(a >> (8 - format->Abits))) << format->Ashift) & format->Amask);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ ((Uint32)(r >> (8 - format->Rbits))) << format->Rshift |
               ((Uint32)(g >> (8 - format->Gbits))) << format->Gshift |
               ((Uint32)(b >> (8 - format->Bbits))) << format->Bshift |
               ((((Uint32)(a >> (8 - format->Abits))) << format->Ashift) & format->Amask);
    }
}

ಶೂನ್ಯ SDL_GetRGB(Uint32 pixelvalue, ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *format, ಸ್ಥಿರಾಂಕ SDL_Palette *palette, Uint8 *r, Uint8 *g, Uint8 *b)
{
    Uint8 ಬಳಸದ;

    ಆದರೆ (!r) {
        r = &ಬಳಸದ;
    }
    ಆದರೆ (!g) {
        g = &ಬಳಸದ;
    }
    ಆದರೆ (!b) {
        b = &ಬಳಸದ;
    }

    ಆದರೆ (!format) {
        *r = *g = *b = 0;
        ಹಿಂತಿರುಗಿ;
    }

    ಆದರೆ (SDL_ISPIXELFORMAT_ಸೂಚ್ಯಂಕಿತ(format->format)) {
        ಆದರೆ (palette && pixelvalue < (ಚಿಹ್ನೆರಹಿತ)palette->ncolors) {
            *r = palette->colors[pixelvalue].r;
            *g = palette->colors[pixelvalue].g;
            *b = palette->colors[pixelvalue].b;
        } ಇಲ್ಲದಿದ್ದರೆ {
            *r = *g = *b = 0;
        }
        ಹಿಂತಿರುಗಿ;
    }

    ಆದರೆ (SDL_ISPIXELFORMAT_10_ಬಿಟ್(format->format)) {
        ಚಿಹ್ನೆರಹಿತ v;
        v = (pixelvalue & format->Rmask) >> format->Rshift;
        *r = (Uint8)(v >> 2);
        v = (pixelvalue & format->Gmask) >> format->Gshift;
        *g = (Uint8)(v >> 2);
        v = (pixelvalue & format->Bmask) >> format->Bshift;
        *b = (Uint8)(v >> 2);
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಚಿಹ್ನೆರಹಿತ v;
        v = (pixelvalue & format->Rmask) >> format->Rshift;
        *r = SDL_expand_byte[format->Rbits][v];
        v = (pixelvalue & format->Gmask) >> format->Gshift;
        *g = SDL_expand_byte[format->Gbits][v];
        v = (pixelvalue & format->Bmask) >> format->Bshift;
        *b = SDL_expand_byte[format->Bbits][v];
    }
}

ಶೂನ್ಯ SDL_GetRGBA(Uint32 pixelvalue, ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *format, ಸ್ಥಿರಾಂಕ SDL_Palette *palette, Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a)
{
    Uint8 ಬಳಸದ;

    ಆದರೆ (!r) {
        r = &ಬಳಸದ;
    }
    ಆದರೆ (!g) {
        g = &ಬಳಸದ;
    }
    ಆದರೆ (!b) {
        b = &ಬಳಸದ;
    }
    ಆದರೆ (!a) {
        a = &ಬಳಸದ;
    }

    ಆದರೆ (!format) {
        *r = *g = *b = *a = 0;
        ಹಿಂತಿರುಗಿ;
    }

    ಆದರೆ (SDL_ISPIXELFORMAT_ಸೂಚ್ಯಂಕಿತ(format->format)) {
        ಆದರೆ (palette && pixelvalue < (ಚಿಹ್ನೆರಹಿತ)palette->ncolors) {
            *r = palette->colors[pixelvalue].r;
            *g = palette->colors[pixelvalue].g;
            *b = palette->colors[pixelvalue].b;
            *a = palette->colors[pixelvalue].a;
        } ಇಲ್ಲದಿದ್ದರೆ {
            *r = *g = *b = *a = 0;
        }
        ಹಿಂತಿರುಗಿ;
    }

    ಆದರೆ (SDL_ISPIXELFORMAT_10_ಬಿಟ್(format->format)) {
        ಚಿಹ್ನೆರಹಿತ v;
        v = (pixelvalue & format->Rmask) >> format->Rshift;
        *r = (Uint8)(v >> 2);
        v = (pixelvalue & format->Gmask) >> format->Gshift;
        *g = (Uint8)(v >> 2);
        v = (pixelvalue & format->Bmask) >> format->Bshift;
        *b = (Uint8)(v >> 2);
        v = (pixelvalue & format->Amask) >> format->Ashift;
        *a = SDL_expand_byte[format->Abits][v];
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಚಿಹ್ನೆರಹಿತ v;
        v = (pixelvalue & format->Rmask) >> format->Rshift;
        *r = SDL_expand_byte[format->Rbits][v];
        v = (pixelvalue & format->Gmask) >> format->Gshift;
        *g = SDL_expand_byte[format->Gbits][v];
        v = (pixelvalue & format->Bmask) >> format->Bshift;
        *b = SDL_expand_byte[format->Bbits][v];
        v = (pixelvalue & format->Amask) >> format->Ashift;
        *a = SDL_expand_byte[format->Abits][v];
    }
}

bool SDL_IsSamePalette(ಸ್ಥಿರಾಂಕ SDL_Palette *src, ಸ್ಥಿರಾಂಕ SDL_Palette *dst)
{
    ಆದರೆ (src->ncolors <= dst->ncolors) {
        // If an identical palette, no need to map
        ಆದರೆ (src == dst ||
            (SDL_memcmp(src->colors, dst->colors,
                        src->ncolors * ಗಾತ್ರ(SDL_Color)) == 0)) {
            ಹಿಂತಿರುಗಿ true;
        }
    }
    ಹಿಂತಿರುಗಿ false;
}

// Map from Palette to Palette
ಸ್ಥಿರ Uint8 *Map1to1(ಸ್ಥಿರಾಂಕ SDL_Palette *src, ಸ್ಥಿರಾಂಕ SDL_Palette *dst, ಪೂರ್ಣಾಂಕ *identical)
{
    Uint8 *map;
    ಪೂರ್ಣಾಂಕ i;

    ಆದರೆ (SDL_IsSamePalette(src, dst)) {
        *identical = 1;
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    *identical = 0;

    map = (Uint8 *)SDL_calloc(256, ಗಾತ್ರ(Uint8));
    ಆದರೆ (!map) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    ಗಾಗಿ (i = 0; i < src->ncolors; ++i) {
        map[i] = SDL_ಕಂಡುಹಿಡಿ_Color(dst,
                               src->colors[i].r, src->colors[i].g,
                               src->colors[i].b, src->colors[i].a);
    }
    ಹಿಂತಿರುಗಿ map;
}

// Map from Palette to BitField
ಸ್ಥಿರ Uint8 *Map1toN(ಸ್ಥಿರಾಂಕ SDL_Palette *pal, Uint8 Rmod, Uint8 Gmod, Uint8 Bmod, Uint8 Amod, ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *dst)
{
    Uint8 *map;
    ಪೂರ್ಣಾಂಕ i;
    ಪೂರ್ಣಾಂಕ bpp;

    ಆದರೆ (!pal) {
        SDL_ಗಣ_Error("src does not have a palette set");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    bpp = ((SDL_BYTESPERPIXEL(dst->format) == 3) ? 4 : SDL_BYTESPERPIXEL(dst->format));
    map = (Uint8 *)SDL_calloc(256, bpp);
    ಆದರೆ (!map) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    // We memory copy to the pixel map so the endianness is preserved
    ಗಾಗಿ (i = 0; i < pal->ncolors; ++i) {
        Uint8 R = (Uint8)((pal->colors[i].r * Rmod) / 255);
        Uint8 G = (Uint8)((pal->colors[i].g * Gmod) / 255);
        Uint8 B = (Uint8)((pal->colors[i].b * Bmod) / 255);
        Uint8 A = (Uint8)((pal->colors[i].a * Amod) / 255);
        ASSEMBLE_RGBA(&map[i * bpp], SDL_BYTESPERPIXEL(dst->format), dst, (Uint32)R,
                      (Uint32)G, (Uint32)B, (Uint32)A);
    }
    ಹಿಂತಿರುಗಿ map;
}

bool SDL_ValidateMap(SDL_Surface *src, SDL_Surface *dst)
{
    SDL_BlitMap *map = &src->map;

    ಆದರೆ (map->info.dst_fmt != dst->fmt ||
        map->info.dst_pal != dst->palette ||
        (dst->palette &&
         map->dst_palette_ಆವೃತ್ತಿ != dst->palette->ಆವೃತ್ತಿ) ||
        (src->palette &&
         map->src_palette_ಆವೃತ್ತಿ != src->palette->ಆವೃತ್ತಿ)) {
        ಆದರೆ (!SDL_MapSurface(src, dst)) {
            ಹಿಂತಿರುಗಿ false;
        }
#ಆದರೆ 0
        // just here for debugging
        SDL_Log("src = %p src->flags = %08X map->info.flags = %08x\ndst = %p dst->flags = %08X dst->map.info.flags = %08X\nmap->blit = %p",
            src, dst->flags, map->info.flags, dst, dst->flags,
            dst->map.info.flags, map->blit);
#ಆದರೆ_ಅಂತ್ಯ
    } ಇಲ್ಲದಿದ್ದರೆ {
        map->info.dst_surface = dst;
    }
    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ SDL_InvalidateMap(SDL_BlitMap *map)
{
    map->info.dst_fmt = ಖಾಲಿ;
    map->info.dst_pal = ಖಾಲಿ;
    map->src_palette_ಆವೃತ್ತಿ = 0;
    map->dst_palette_ಆವೃತ್ತಿ = 0;
    ಆದರೆ (map->info.ಕೋಷ್ಟಕ) {
        SDL_free(map->info.ಕೋಷ್ಟಕ);
        map->info.ಕೋಷ್ಟಕ = ಖಾಲಿ;
    }
    ಆದರೆ (map->info.palette_map) {
        SDL_Destroy_Hash_ಕೋಷ್ಟಕ(map->info.palette_map);
        map->info.palette_map = ಖಾಲಿ;
    }
}

bool SDL_MapSurface(SDL_Surface *src, SDL_Surface *dst)
{
    ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *srcfmt;
    ಸ್ಥಿರಾಂಕ SDL_Palette *srcpal;
    ಸ್ಥಿರಾಂಕ SDL_PixelFormatDetails *dstfmt;
    ಸ್ಥಿರಾಂಕ SDL_Palette *dstpal;
    SDL_BlitMap *map;

    // Clear out any previous mapping
    map = &src->map;
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_HAVE_RLE
    ಆದರೆ (src->ಆಂತರಿಕ_flags & SDL_ಆಂತರಿಕ_SURFACE_RLEACCEL) {
        SDL_UnRLESurface(src);
    }
#ಆದರೆ_ಅಂತ್ಯ
    SDL_InvalidateMap(map);

    // Figure out what kind of mapping we're doing
    map->ತಟಸ್ಥ = 0;
    srcfmt = src->fmt;
    srcpal = src->palette;
    dstfmt = dst->fmt;
    dstpal = dst->palette;
    ಆದರೆ (SDL_ISPIXELFORMAT_ಸೂಚ್ಯಂಕಿತ(srcfmt->format)) {
        ಆದರೆ (SDL_ISPIXELFORMAT_ಸೂಚ್ಯಂಕಿತ(dstfmt->format)) {
            // Palette --> Palette
            ಆದರೆ (srcpal && dstpal) {
                map->info.ಕೋಷ್ಟಕ = Map1to1(srcpal, dstpal, &map->ತಟಸ್ಥ);
            } ಇಲ್ಲದಿದ್ದರೆ {
                map->ತಟಸ್ಥ = 1;
            }
            ಆದರೆ (!map->ತಟಸ್ಥ) {
                ಆದರೆ (!map->info.ಕೋಷ್ಟಕ) {
                    ಹಿಂತಿರುಗಿ false;
                }
            }
            ಆದರೆ (srcfmt->ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_pixel != dstfmt->ಬಿಟ್ಟುಗಳು_ಪ್ರತಿ_pixel) {
                map->ತಟಸ್ಥ = 0;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            // Palette --> BitField
            map->info.ಕೋಷ್ಟಕ =
                Map1toN(srcpal, src->map.info.r, src->map.info.g,
                        src->map.info.b, src->map.info.a, dstfmt);
            ಆದರೆ (!map->info.ಕೋಷ್ಟಕ) {
                ಹಿಂತಿರುಗಿ false;
            }
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (SDL_ISPIXELFORMAT_ಸೂಚ್ಯಂಕಿತ(dstfmt->format)) {
            // BitField --> Palette
            map->info.palette_map = SDL_Create_Hash_ಕೋಷ್ಟಕ(0, false, SDL_HashID, SDL_ಕೀಲಿ_ಹೊಂದಿಕೆ_ID, ಖಾಲಿ, ಖಾಲಿ);
        } ಇಲ್ಲದಿದ್ದರೆ {
            // BitField --> BitField
            ಆದರೆ (srcfmt == dstfmt) {
                map->ತಟಸ್ಥ = 1;
            }
        }
    }

    ಆದರೆ (dstpal) {
        map->dst_palette_ಆವೃತ್ತಿ = dstpal->ಆವೃತ್ತಿ;
    } ಇಲ್ಲದಿದ್ದರೆ {
        map->dst_palette_ಆವೃತ್ತಿ = 0;
    }

    ಆದರೆ (srcpal) {
        map->src_palette_ಆವೃತ್ತಿ = srcpal->ಆವೃತ್ತಿ;
    } ಇಲ್ಲದಿದ್ದರೆ {
        map->src_palette_ಆವೃತ್ತಿ = 0;
    }

    // Choose your blitters wisely
    ಹಿಂತಿರುಗಿ SDL_CalculateBlit(src, dst);
}


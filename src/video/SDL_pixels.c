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
#அந்தர்பாவ "SDL_internal.h"

// General (mostly internal) pixel/color manipulation routines for SDL

#அந்தர்பாவ "SDL_sysvideo.h"
#அந்தர்பாவ "SDL_pixels_c.h"
#அந்தர்பாவ "SDL_RLEaccel_c.h"

// Lookup tables to expand partial bytes to the full 0..255 range

// This is the code used to generate the lookup tables below:
#எனில் 0
#அந்தர்பாவ <SDL3/SDL.h>

#define GENERATE_SHIFTS

நிலையான Uint32 Calculate(முழு v, முழு bits, முழு vmax, முழு shift)
{
#எனில் defined(GENERATE_FLOOR)
    (வெறுமை)bits;
    திரும்பு (Uint32)SDL_floor(v * 255.0f / vmax) << shift;
#அல்லதெனில் defined(GENERATE_ROUND)
    (வெறுமை)bits;
    திரும்பு (Uint32)SDL_roundf(v * 255.0f / vmax) << shift;
#அல்லதெனில் defined(GENERATE_SHIFTS)
    (வெறுமை)vmax;
    தேர்வு (bits) {
    நிலை 1:
        v = (v << 7) | (v << 6) | (v << 5) | (v << 4) | (v << 3) | (v << 2) | (v << 1) | v;
        நிறுத்து;
    நிலை 2:
        v = (v << 6) | (v << 4) | (v << 2) | v;
        நிறுத்து;
    நிலை 3:
        v = (v << 5) | (v << 2) | (v >> 1);
        நிறுத்து;
    நிலை 4:
        v = (v << 4) | v;
        நிறுத்து;
    நிலை 5:
        v = (v << 3) | (v >> 2);
        நிறுத்து;
    நிலை 6:
        v = (v << 2) | (v >> 4);
        நிறுத்து;
    நிலை 7:
        v = (v << 1) | (v >> 6);
        நிறுத்து;
    நிலை 8:
        நிறுத்து;
    }
    திரும்பு (Uint32)v << shift;
#endif
}

முழு முதன்மை(முழு argc, எழுத்து *argv[])
{
    முழு i, b;
    SDL_IOStream *io = SDL_IOFromDynamicMem();

    (வெறுமை)argc;
    (வெறுமை)argv;
    க்கு (b = 1; b <= 8; ++b) {
        SDL_IOprintf(io, "static const Uint8 lookup_%d[] = {\n    ", b);
        க்கு (i = 0; i < (1 << b); ++i) {
            எனில் (i > 0) {
                SDL_IOprintf(io, ", ");
            }
            SDL_IOprintf(io, "%d", Calculate(i, b, (1 << b) - 1, 0));
        }
        SDL_Log("%s\n};\n\n", (மாறிலி எழுத்து *)SDL_GetPointerProperty(SDL_GetIOProperties(io), SDL_PROP_IOSTREAM_DYNAMIC_MEMORY_POINTER, வெற்று));
        SDL_SeekIO(io, 0, SDL_IO_SEEK_SET);
        SDL_WriteIO(io, "", 1);
        SDL_SeekIO(io, 0, SDL_IO_SEEK_SET);
    }
    SDL_CloseIO(io);
    திரும்பு 0;
}
#endif

நிலையான மாறிலி Uint8 lookup_0[] = {
    255
};

நிலையான மாறிலி Uint8 lookup_1[] = {
    0, 255
};

நிலையான மாறிலி Uint8 lookup_2[] = {
    0, 85, 170, 255
};

நிலையான மாறிலி Uint8 lookup_3[] = {
    0, 36, 73, 109, 146, 182, 219, 255
};

நிலையான மாறிலி Uint8 lookup_4[] = {
    0, 17, 34, 51, 68, 85, 102, 119, 136, 153, 170, 187, 204, 221, 238, 255
};

நிலையான மாறிலி Uint8 lookup_5[] = {
    0, 8, 16, 24, 33, 41, 49, 57, 66, 74, 82, 90, 99, 107, 115, 123, 132, 140, 148, 156, 165, 173, 181, 189, 198, 206, 214, 222, 231, 239, 247, 255
};

நிலையான மாறிலி Uint8 lookup_6[] = {
    0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 65, 69, 73, 77, 81, 85, 89, 93, 97, 101, 105, 109, 113, 117, 121, 125, 130, 134, 138, 142, 146, 150, 154, 158, 162, 166, 170, 174, 178, 182, 186, 190, 195, 199, 203, 207, 211, 215, 219, 223, 227, 231, 235, 239, 243, 247, 251, 255
};

நிலையான மாறிலி Uint8 lookup_7[] = {
    0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64, 66, 68, 70, 72, 74, 76, 78, 80, 82, 84, 86, 88, 90, 92, 94, 96, 98, 100, 102, 104, 106, 108, 110, 112, 114, 116, 118, 120, 122, 124, 126, 129, 131, 133, 135, 137, 139, 141, 143, 145, 147, 149, 151, 153, 155, 157, 159, 161, 163, 165, 167, 169, 171, 173, 175, 177, 179, 181, 183, 185, 187, 189, 191, 193, 195, 197, 199, 201, 203, 205, 207, 209, 211, 213, 215, 217, 219, 221, 223, 225, 227, 229, 231, 233, 235, 237, 239, 241, 243, 245, 247, 249, 251, 253, 255
};

நிலையான மாறிலி Uint8 lookup_8[] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255
};

மாறிலி Uint8 *SDL_expand_byte[9] = {
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
மாறிலி Uint16 SDL_expand_byte_10[] = {
    0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 68, 72, 76, 80, 84, 88, 92, 96, 100, 104, 108, 112, 116, 120, 124, 128, 132, 136, 140, 144, 148, 152, 156, 160, 164, 168, 173, 177, 181, 185, 189, 193, 197, 201, 205, 209, 213, 217, 221, 225, 229, 233, 237, 241, 245, 249, 253, 257, 261, 265, 269, 273, 277, 281, 285, 289, 293, 297, 301, 305, 309, 313, 317, 321, 325, 329, 333, 337, 341, 345, 349, 353, 357, 361, 365, 369, 373, 377, 381, 385, 389, 393, 397, 401, 405, 409, 413, 417, 421, 425, 429, 433, 437, 441, 445, 449, 453, 457, 461, 465, 469, 473, 477, 481, 485, 489, 493, 497, 501, 505, 509, 514, 518, 522, 526, 530, 534, 538, 542, 546, 550, 554, 558, 562, 566, 570, 574, 578, 582, 586, 590, 594, 598, 602, 606, 610, 614, 618, 622, 626, 630, 634, 638, 642, 646, 650, 654, 658, 662, 666, 670, 674, 678, 682, 686, 690, 694, 698, 702, 706, 710, 714, 718, 722, 726, 730, 734, 738, 742, 746, 750, 754, 758, 762, 766, 770, 774, 778, 782, 786, 790, 794, 798, 802, 806, 810, 814, 818, 822, 826, 830, 834, 838, 842, 846, 850, 855, 859, 863, 867, 871, 875, 879, 883, 887, 891, 895, 899, 903, 907, 911, 915, 919, 923, 927, 931, 935, 939, 943, 947, 951, 955, 959, 963, 967, 971, 975, 979, 983, 987, 991, 995, 999, 1003, 1007, 1011, 1015, 1019, 1023
};
SDL_COMPILE_TIME_ASSERT(SDL_expand_byte_10_size, SDL_arraysize(SDL_expand_byte_10) == (1 << 8));


// Helper functions

#define CASE(X) \
    நிலை X:     \
        திரும்பு #X;
மாறிலி எழுத்து *SDL_GetPixelFormatName(SDL_PixelFormat format)
{
    தேர்வு (format) {

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

    இயல்பு:
        திரும்பு "SDL_PIXELFORMAT_UNKNOWN";
    }
}
#undef CASE

bool SDL_GetMasksForPixelFormat(SDL_PixelFormat format, முழு *bpp, Uint32 *Rmask, Uint32 *Gmask, Uint32 *Bmask, Uint32 *Amask)
{
    Uint32 masks[4];

#ifdef SDL_HAVE_YUV
    // Partial support for SDL_Surface with FOURCC
    எனில் (SDL_ISPIXELFORMAT_FOURCC(format)) {
        // Not a format that uses masks
        *Rmask = *Gmask = *Bmask = *Amask = 0;
        // however, some of these are packed formats, and can legit declare bits-per-pixel!
        தேர்வு (format) {
            நிலை SDL_PIXELFORMAT_YUY2:
            நிலை SDL_PIXELFORMAT_UYVY:
            நிலை SDL_PIXELFORMAT_YVYU:
                *bpp = 32;
                நிறுத்து;
            இயல்பு:
                *bpp = 0;  // oh well.
        }
        திரும்பு true;
    }
#இல்லையெனில்
    எனில் (SDL_ISPIXELFORMAT_FOURCC(format)) {
        திரும்பு SDL_SetError("SDL not built with YUV support");
    }
#endif

    // Initialize the values here
    எனில் (SDL_BYTESPERPIXEL(format) <= 2) {
        *bpp = SDL_BITSPERPIXEL(format);
    } இல்லையெனில் {
        *bpp = SDL_BYTESPERPIXEL(format) * 8;
    }
    *Rmask = *Gmask = *Bmask = *Amask = 0;

    எனில் (SDL_PIXELTYPE(format) == SDL_PIXELTYPE_ARRAYU8) {
        தேர்வு (SDL_BYTESPERPIXEL(format)) {
        நிலை 3:
            தேர்வு (SDL_PIXELORDER(format)) {
            நிலை SDL_ARRAYORDER_RGB:
#எனில் SDL_BYTEORDER == SDL_BIG_ENDIAN
                *Rmask = 0x00FF0000;
                *Gmask = 0x0000FF00;
                *Bmask = 0x000000FF;
#இல்லையெனில்
                *Rmask = 0x000000FF;
                *Gmask = 0x0000FF00;
                *Bmask = 0x00FF0000;
#endif
                திரும்பு true;
            நிலை SDL_ARRAYORDER_BGR:
#எனில் SDL_BYTEORDER == SDL_BIG_ENDIAN
                *Rmask = 0x000000FF;
                *Gmask = 0x0000FF00;
                *Bmask = 0x00FF0000;
#இல்லையெனில்
                *Rmask = 0x00FF0000;
                *Gmask = 0x0000FF00;
                *Bmask = 0x000000FF;
#endif
                திரும்பு true;
            இயல்பு:
                நிறுத்து;
            }
            நிறுத்து;
        நிலை 4:
            தேர்வு (SDL_PIXELORDER(format)) {
            நிலை SDL_ARRAYORDER_RGBA:
#எனில் SDL_BYTEORDER == SDL_BIG_ENDIAN
                *Rmask = 0xFF000000;
                *Gmask = 0x00FF0000;
                *Bmask = 0x0000FF00;
                *Amask = 0x000000FF;
#இல்லையெனில்
                *Rmask = 0x000000FF;
                *Gmask = 0x0000FF00;
                *Bmask = 0x00FF0000;
                *Amask = 0xFF000000;
#endif
                திரும்பு true;
            நிலை SDL_ARRAYORDER_ARGB:
#எனில் SDL_BYTEORDER == SDL_BIG_ENDIAN
                *Rmask = 0x00FF0000;
                *Gmask = 0x0000FF00;
                *Bmask = 0x000000FF;
                *Amask = 0xFF000000;
#இல்லையெனில்
                *Rmask = 0x0000FF00;
                *Gmask = 0x00FF0000;
                *Bmask = 0xFF000000;
                *Amask = 0x000000FF;
#endif
                திரும்பு true;
            நிலை SDL_ARRAYORDER_BGRA:
#எனில் SDL_BYTEORDER == SDL_BIG_ENDIAN
                *Rmask = 0x0000FF00;
                *Gmask = 0x00FF0000;
                *Bmask = 0xFF000000;
                *Amask = 0x000000FF;
#இல்லையெனில்
                *Rmask = 0x00FF0000;
                *Gmask = 0x0000FF00;
                *Bmask = 0x000000FF;
                *Amask = 0xFF000000;
#endif
                திரும்பு true;
            நிலை SDL_ARRAYORDER_ABGR:
#எனில் SDL_BYTEORDER == SDL_BIG_ENDIAN
                *Rmask = 0x000000FF;
                *Gmask = 0x0000FF00;
                *Bmask = 0x00FF0000;
                *Amask = 0xFF000000;
#இல்லையெனில்
                *Rmask = 0xFF000000;
                *Gmask = 0x00FF0000;
                *Bmask = 0x0000FF00;
                *Amask = 0x000000FF;
#endif
                திரும்பு true;
            இயல்பு:
                நிறுத்து;
            }
            நிறுத்து;
        இயல்பு:
            நிறுத்து;
        }
        திரும்பு SDL_SetError("Unknown pixel format");
    }

    எனில் (SDL_PIXELTYPE(format) != SDL_PIXELTYPE_PACKED8 &&
        SDL_PIXELTYPE(format) != SDL_PIXELTYPE_PACKED16 &&
        SDL_PIXELTYPE(format) != SDL_PIXELTYPE_PACKED32) {
        // Not a format that uses masks
        திரும்பு true;
    }

    தேர்வு (SDL_PIXELLAYOUT(format)) {
    நிலை SDL_PACKEDLAYOUT_332:
        masks[0] = 0x00000000;
        masks[1] = 0x000000E0;
        masks[2] = 0x0000001C;
        masks[3] = 0x00000003;
        நிறுத்து;
    நிலை SDL_PACKEDLAYOUT_4444:
        masks[0] = 0x0000F000;
        masks[1] = 0x00000F00;
        masks[2] = 0x000000F0;
        masks[3] = 0x0000000F;
        நிறுத்து;
    நிலை SDL_PACKEDLAYOUT_1555:
        masks[0] = 0x00008000;
        masks[1] = 0x00007C00;
        masks[2] = 0x000003E0;
        masks[3] = 0x0000001F;
        நிறுத்து;
    நிலை SDL_PACKEDLAYOUT_5551:
        masks[0] = 0x0000F800;
        masks[1] = 0x000007C0;
        masks[2] = 0x0000003E;
        masks[3] = 0x00000001;
        நிறுத்து;
    நிலை SDL_PACKEDLAYOUT_565:
        masks[0] = 0x00000000;
        masks[1] = 0x0000F800;
        masks[2] = 0x000007E0;
        masks[3] = 0x0000001F;
        நிறுத்து;
    நிலை SDL_PACKEDLAYOUT_8888:
        masks[0] = 0xFF000000;
        masks[1] = 0x00FF0000;
        masks[2] = 0x0000FF00;
        masks[3] = 0x000000FF;
        நிறுத்து;
    நிலை SDL_PACKEDLAYOUT_2101010:
        masks[0] = 0xC0000000;
        masks[1] = 0x3FF00000;
        masks[2] = 0x000FFC00;
        masks[3] = 0x000003FF;
        நிறுத்து;
    நிலை SDL_PACKEDLAYOUT_1010102:
        masks[0] = 0xFFC00000;
        masks[1] = 0x003FF000;
        masks[2] = 0x00000FFC;
        masks[3] = 0x00000003;
        நிறுத்து;
    இயல்பு:
        திரும்பு SDL_SetError("Unknown pixel format");
    }

    தேர்வு (SDL_PIXELORDER(format)) {
    நிலை SDL_PACKEDORDER_XRGB:
        *Rmask = masks[1];
        *Gmask = masks[2];
        *Bmask = masks[3];
        நிறுத்து;
    நிலை SDL_PACKEDORDER_RGBX:
        *Rmask = masks[0];
        *Gmask = masks[1];
        *Bmask = masks[2];
        நிறுத்து;
    நிலை SDL_PACKEDORDER_ARGB:
        *Amask = masks[0];
        *Rmask = masks[1];
        *Gmask = masks[2];
        *Bmask = masks[3];
        நிறுத்து;
    நிலை SDL_PACKEDORDER_RGBA:
        *Rmask = masks[0];
        *Gmask = masks[1];
        *Bmask = masks[2];
        *Amask = masks[3];
        நிறுத்து;
    நிலை SDL_PACKEDORDER_XBGR:
        *Bmask = masks[1];
        *Gmask = masks[2];
        *Rmask = masks[3];
        நிறுத்து;
    நிலை SDL_PACKEDORDER_BGRX:
        *Bmask = masks[0];
        *Gmask = masks[1];
        *Rmask = masks[2];
        நிறுத்து;
    நிலை SDL_PACKEDORDER_BGRA:
        *Bmask = masks[0];
        *Gmask = masks[1];
        *Rmask = masks[2];
        *Amask = masks[3];
        நிறுத்து;
    நிலை SDL_PACKEDORDER_ABGR:
        *Amask = masks[0];
        *Bmask = masks[1];
        *Gmask = masks[2];
        *Rmask = masks[3];
        நிறுத்து;
    இயல்பு:
        திரும்பு SDL_SetError("Unknown pixel format");
    }
    திரும்பு true;
}

SDL_PixelFormat SDL_GetPixelFormatForMasks(முழு bpp, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask)
{
    தேர்வு (bpp) {
    நிலை 1:
        // SDL defaults to MSB ordering
        திரும்பு SDL_PIXELFORMAT_INDEX1MSB;
    நிலை 2:
        // SDL defaults to MSB ordering
        திரும்பு SDL_PIXELFORMAT_INDEX2MSB;
    நிலை 4:
        // SDL defaults to MSB ordering
        திரும்பு SDL_PIXELFORMAT_INDEX4MSB;
    நிலை 8:
        எனில் (Rmask == 0xE0 &&
            Gmask == 0x1C &&
            Bmask == 0x03 &&
            Amask == 0x00) {
            திரும்பு SDL_PIXELFORMAT_RGB332;
        }
        திரும்பு SDL_PIXELFORMAT_INDEX8;
    நிலை 12:
        எனில் (Rmask == 0) {
            திரும்பு SDL_PIXELFORMAT_XRGB4444;
        }
        எனில் (Rmask == 0x0F00 &&
            Gmask == 0x00F0 &&
            Bmask == 0x000F &&
            Amask == 0x0000) {
            திரும்பு SDL_PIXELFORMAT_XRGB4444;
        }
        எனில் (Rmask == 0x000F &&
            Gmask == 0x00F0 &&
            Bmask == 0x0F00 &&
            Amask == 0x0000) {
            திரும்பு SDL_PIXELFORMAT_XBGR4444;
        }
        நிறுத்து;
    நிலை 15:
        எனில் (Rmask == 0) {
            திரும்பு SDL_PIXELFORMAT_XRGB1555;
        }
        SDL_FALLTHROUGH;
    நிலை 16:
        எனில் (Rmask == 0) {
            திரும்பு SDL_PIXELFORMAT_RGB565;
        }
        எனில் (Rmask == 0x7C00 &&
            Gmask == 0x03E0 &&
            Bmask == 0x001F &&
            Amask == 0x0000) {
            திரும்பு SDL_PIXELFORMAT_XRGB1555;
        }
        எனில் (Rmask == 0x001F &&
            Gmask == 0x03E0 &&
            Bmask == 0x7C00 &&
            Amask == 0x0000) {
            திரும்பு SDL_PIXELFORMAT_XBGR1555;
        }
        எனில் (Rmask == 0x0F00 &&
            Gmask == 0x00F0 &&
            Bmask == 0x000F &&
            Amask == 0xF000) {
            திரும்பு SDL_PIXELFORMAT_ARGB4444;
        }
        எனில் (Rmask == 0xF000 &&
            Gmask == 0x0F00 &&
            Bmask == 0x00F0 &&
            Amask == 0x000F) {
            திரும்பு SDL_PIXELFORMAT_RGBA4444;
        }
        எனில் (Rmask == 0x000F &&
            Gmask == 0x00F0 &&
            Bmask == 0x0F00 &&
            Amask == 0xF000) {
            திரும்பு SDL_PIXELFORMAT_ABGR4444;
        }
        எனில் (Rmask == 0x00F0 &&
            Gmask == 0x0F00 &&
            Bmask == 0xF000 &&
            Amask == 0x000F) {
            திரும்பு SDL_PIXELFORMAT_BGRA4444;
        }
        எனில் (Rmask == 0x7C00 &&
            Gmask == 0x03E0 &&
            Bmask == 0x001F &&
            Amask == 0x8000) {
            திரும்பு SDL_PIXELFORMAT_ARGB1555;
        }
        எனில் (Rmask == 0xF800 &&
            Gmask == 0x07C0 &&
            Bmask == 0x003E &&
            Amask == 0x0001) {
            திரும்பு SDL_PIXELFORMAT_RGBA5551;
        }
        எனில் (Rmask == 0x001F &&
            Gmask == 0x03E0 &&
            Bmask == 0x7C00 &&
            Amask == 0x8000) {
            திரும்பு SDL_PIXELFORMAT_ABGR1555;
        }
        எனில் (Rmask == 0x003E &&
            Gmask == 0x07C0 &&
            Bmask == 0xF800 &&
            Amask == 0x0001) {
            திரும்பு SDL_PIXELFORMAT_BGRA5551;
        }
        எனில் (Rmask == 0xF800 &&
            Gmask == 0x07E0 &&
            Bmask == 0x001F &&
            Amask == 0x0000) {
            திரும்பு SDL_PIXELFORMAT_RGB565;
        }
        எனில் (Rmask == 0x001F &&
            Gmask == 0x07E0 &&
            Bmask == 0xF800 &&
            Amask == 0x0000) {
            திரும்பு SDL_PIXELFORMAT_BGR565;
        }
        எனில் (Rmask == 0x003F &&
            Gmask == 0x07C0 &&
            Bmask == 0xF800 &&
            Amask == 0x0000) {
            // Technically this would be BGR556, but Witek says this works in bug 3158
            திரும்பு SDL_PIXELFORMAT_RGB565;
        }
        நிறுத்து;
    நிலை 24:
        தேர்வு (Rmask) {
        நிலை 0:
        நிலை 0x00FF0000:
#எனில் SDL_BYTEORDER == SDL_BIG_ENDIAN
            திரும்பு SDL_PIXELFORMAT_RGB24;
#இல்லையெனில்
            திரும்பு SDL_PIXELFORMAT_BGR24;
#endif
        நிலை 0x000000FF:
#எனில் SDL_BYTEORDER == SDL_BIG_ENDIAN
            திரும்பு SDL_PIXELFORMAT_BGR24;
#இல்லையெனில்
            திரும்பு SDL_PIXELFORMAT_RGB24;
#endif
        }
        நிறுத்து;
    நிலை 30:
        எனில் (Rmask == 0x3FF00000 &&
            Gmask == 0x000FFC00 &&
            Bmask == 0x000003FF &&
            Amask == 0x00000000) {
            திரும்பு SDL_PIXELFORMAT_XRGB2101010;
        }
        எனில் (Rmask == 0x000003FF &&
            Gmask == 0x000FFC00 &&
            Bmask == 0x3FF00000 &&
            Amask == 0x00000000) {
            திரும்பு SDL_PIXELFORMAT_XBGR2101010;
        }
        நிறுத்து;
    நிலை 32:
        எனில் (Rmask == 0) {
            திரும்பு SDL_PIXELFORMAT_XRGB8888;
        }
        எனில் (Rmask == 0x00FF0000 &&
            Gmask == 0x0000FF00 &&
            Bmask == 0x000000FF &&
            Amask == 0x00000000) {
            திரும்பு SDL_PIXELFORMAT_XRGB8888;
        }
        எனில் (Rmask == 0xFF000000 &&
            Gmask == 0x00FF0000 &&
            Bmask == 0x0000FF00 &&
            Amask == 0x00000000) {
            திரும்பு SDL_PIXELFORMAT_RGBX8888;
        }
        எனில் (Rmask == 0x000000FF &&
            Gmask == 0x0000FF00 &&
            Bmask == 0x00FF0000 &&
            Amask == 0x00000000) {
            திரும்பு SDL_PIXELFORMAT_XBGR8888;
        }
        எனில் (Rmask == 0x0000FF00 &&
            Gmask == 0x00FF0000 &&
            Bmask == 0xFF000000 &&
            Amask == 0x00000000) {
            திரும்பு SDL_PIXELFORMAT_BGRX8888;
        }
        எனில் (Rmask == 0x00FF0000 &&
            Gmask == 0x0000FF00 &&
            Bmask == 0x000000FF &&
            Amask == 0xFF000000) {
            திரும்பு SDL_PIXELFORMAT_ARGB8888;
        }
        எனில் (Rmask == 0xFF000000 &&
            Gmask == 0x00FF0000 &&
            Bmask == 0x0000FF00 &&
            Amask == 0x000000FF) {
            திரும்பு SDL_PIXELFORMAT_RGBA8888;
        }
        எனில் (Rmask == 0x000000FF &&
            Gmask == 0x0000FF00 &&
            Bmask == 0x00FF0000 &&
            Amask == 0xFF000000) {
            திரும்பு SDL_PIXELFORMAT_ABGR8888;
        }
        எனில் (Rmask == 0x0000FF00 &&
            Gmask == 0x00FF0000 &&
            Bmask == 0xFF000000 &&
            Amask == 0x000000FF) {
            திரும்பு SDL_PIXELFORMAT_BGRA8888;
        }
        எனில் (Rmask == 0x3FF00000 &&
            Gmask == 0x000FFC00 &&
            Bmask == 0x000003FF &&
            Amask == 0x00000000) {
            திரும்பு SDL_PIXELFORMAT_XRGB2101010;
        }
        எனில் (Rmask == 0x000003FF &&
            Gmask == 0x000FFC00 &&
            Bmask == 0x3FF00000 &&
            Amask == 0x00000000) {
            திரும்பு SDL_PIXELFORMAT_XBGR2101010;
        }
        எனில் (Rmask == 0x3FF00000 &&
            Gmask == 0x000FFC00 &&
            Bmask == 0x000003FF &&
            Amask == 0xC0000000) {
            திரும்பு SDL_PIXELFORMAT_ARGB2101010;
        }
        எனில் (Rmask == 0x000003FF &&
            Gmask == 0x000FFC00 &&
            Bmask == 0x3FF00000 &&
            Amask == 0xC0000000) {
            திரும்பு SDL_PIXELFORMAT_ABGR2101010;
        }
        நிறுத்து;
    }
    திரும்பு SDL_PIXELFORMAT_UNKNOWN;
}

நிலையான SDL_InitState SDL_format_details_init;
நிலையான SDL_HashTable *SDL_format_details;

நிலையான bool SDL_InitPixelFormatDetails(SDL_PixelFormatDetails *details, SDL_PixelFormat format)
{
    முழு bpp;
    Uint32 Rmask, Gmask, Bmask, Amask;
    Uint32 mask;

    எனில் (!SDL_GetMasksForPixelFormat(format, &bpp, &Rmask, &Gmask, &Bmask, &Amask)) {
        திரும்பு false;
    }

    // Set up the format
    SDL_zerop(details);
    details->format = format;
    details->bits_per_pixel = (Uint8)bpp;
    details->bytes_per_pixel = (Uint8)((bpp + 7) / 8);

    details->Rmask = Rmask;
    details->Rshift = 0;
    details->Rbits = 0;
    எனில் (Rmask) {
        க்கு (mask = Rmask; !(mask & 0x01); mask >>= 1) {
            ++details->Rshift;
        }
        க்கு (; (mask & 0x01); mask >>= 1) {
            ++details->Rbits;
        }
    }

    details->Gmask = Gmask;
    details->Gshift = 0;
    details->Gbits = 0;
    எனில் (Gmask) {
        க்கு (mask = Gmask; !(mask & 0x01); mask >>= 1) {
            ++details->Gshift;
        }
        க்கு (; (mask & 0x01); mask >>= 1) {
            ++details->Gbits;
        }
    }

    details->Bmask = Bmask;
    details->Bshift = 0;
    details->Bbits = 0;
    எனில் (Bmask) {
        க்கு (mask = Bmask; !(mask & 0x01); mask >>= 1) {
            ++details->Bshift;
        }
        க்கு (; (mask & 0x01); mask >>= 1) {
            ++details->Bbits;
        }
    }

    details->Amask = Amask;
    details->Ashift = 0;
    details->Abits = 0;
    எனில் (Amask) {
        க்கு (mask = Amask; !(mask & 0x01); mask >>= 1) {
            ++details->Ashift;
        }
        க்கு (; (mask & 0x01); mask >>= 1) {
            ++details->Abits;
        }
    }

    திரும்பு true;
}

மாறிலி SDL_PixelFormatDetails *SDL_GetPixelFormatDetails(SDL_PixelFormat format)
{
    SDL_PixelFormatDetails *details;

    எனில் (SDL_ShouldInit(&SDL_format_details_init)) {
        SDL_format_details = SDL_CreateHashTable(0, true, SDL_HashID, SDL_சாவி_Match_ID, SDL_Destroy_Hash_மதிப்பு, வெற்று);
        எனில் (!SDL_format_details) {
            SDL_SetInitialized(&SDL_format_details_init, false);
            திரும்பு வெற்று;
        }
        SDL_SetInitialized(&SDL_format_details_init, true);
    }

    எனில் (SDL_FindInHashTable(SDL_format_details, (மாறிலி வெறுமை *)(uintptr_t)format, (மாறிலி வெறுமை **)&details)) {
        திரும்பு details;
    }

    // Allocate an empty pixel format structure, and initialize it
    details = (SDL_PixelFormatDetails *)SDL_malloc(அளவு(*details));
    எனில் (!details) {
        திரும்பு வெற்று;
    }

    எனில் (!SDL_InitPixelFormatDetails(details, format)) {
        SDL_free(details);
        திரும்பு வெற்று;
    }

    எனில் (!SDL_செருகு_Into_Hash_Table(SDL_format_details, (மாறிலி வெறுமை *)(uintptr_t)format, (வெறுமை *)details, false)) {
        SDL_free(details);
        // uh...did another thread beat us to inserting this?
        எனில் (SDL_FindInHashTable(SDL_format_details, (மாறிலி வெறுமை *)(uintptr_t)format, (மாறிலி வெறுமை **)&details)) {
            திரும்பு details;
        }
        திரும்பு வெற்று;  // oh well.
    }

    திரும்பு details;
}

வெறுமை SDL_QuitPixelFormatDetails(வெறுமை)
{
    எனில் (SDL_ShouldQuit(&SDL_format_details_init)) {
        SDL_DestroyHashTable(SDL_format_details);
        SDL_format_details = வெற்று;
        SDL_SetInitialized(&SDL_format_details_init, false);
    }
}

வெறுமை SDL_Get8888AlphaMaskAndShift(மாறிலி SDL_PixelFormatDetails *fmt, Uint32 *mask, Uint32 *shift)
{
    எனில் (fmt->Amask) {
        *mask = fmt->Amask;
        *shift = fmt->Ashift;
    } இல்லையெனில் {
        *mask = ~(fmt->Rmask | fmt->Gmask | fmt->Bmask);
        தேர்வு (*mask) {
        நிலை 0x000000FF:
            *shift = 0;
            நிறுத்து;
        நிலை 0x0000FF00:
            *shift = 8;
            நிறுத்து;
        நிலை 0x00FF0000:
            *shift = 16;
            நிறுத்து;
        நிலை 0xFF000000:
            *shift = 24;
            நிறுத்து;
        இயல்பு:
            // Should never happen
            *shift = 0;
            நிறுத்து;
        }
    }
}

SDL_Colorspace SDL_GetDefaultColorspaceForFormat(SDL_PixelFormat format)
{
    எனில் (SDL_ISPIXELFORMAT_FOURCC(format)) {
        எனில் (format == SDL_PIXELFORMAT_MJPG) {
            திரும்பு SDL_COLORSPACE_SRGB;
        } இல்லையெனில் எனில் (format == SDL_PIXELFORMAT_P010 || format == SDL_PIXELFORMAT_I0FL || format == SDL_PIXELFORMAT_I4FL) {
            திரும்பு SDL_COLORSPACE_HDR10;
        } இல்லையெனில் {
            திரும்பு SDL_COLORSPACE_YUV_DEFAULT;
        }
    } இல்லையெனில் எனில் (SDL_ISPIXELFORMAT_FLOAT(format)) {
        திரும்பு SDL_COLORSPACE_SRGB_LINEAR;
    } இல்லையெனில் எனில் (SDL_ISPIXELFORMAT_10BIT(format)) {
        திரும்பு SDL_COLORSPACE_HDR10;
    } இல்லையெனில் {
        திரும்பு SDL_COLORSPACE_RGB_DEFAULT;
    }
}

தசம SDL_sRGBtoLinear(தசம v)
{
    எனில் (v <= 0.04045f) {
        v = (v / 12.92f);
    } இல்லையெனில் {
        v = SDL_powf((v + 0.055f) / 1.055f, 2.4f);
    }
    திரும்பு v;
}

தசம SDL_sRGBfromLinear(தசம v)
{
    எனில் (v <= 0.0031308f) {
        v = (v * 12.92f);
    } இல்லையெனில் {
        v = (SDL_powf(v, 1.0f / 2.4f) * 1.055f - 0.055f);
    }
    திரும்பு v;
}

தசம SDL_PQtoNits(தசம v)
{
    மாறிலி தசம c1 = 0.8359375f;
    மாறிலி தசம c2 = 18.8515625f;
    மாறிலி தசம c3 = 18.6875f;
    மாறிலி தசம oo_m1 = 1.0f / 0.1593017578125f;
    மாறிலி தசம oo_m2 = 1.0f / 78.84375f;

    தசம இலக்கம் = SDL_max(SDL_powf(v, oo_m2) - c1, 0.0f);
    தசம den = c2 - c3 * SDL_powf(v, oo_m2);
    திரும்பு 10000.0f * SDL_powf(இலக்கம் / den, oo_m1);
}

தசம SDL_PQfromNits(தசம v)
{
    மாறிலி தசம c1 = 0.8359375f;
    மாறிலி தசம c2 = 18.8515625f;
    மாறிலி தசம c3 = 18.6875f;
    மாறிலி தசம m1 = 0.1593017578125f;
    மாறிலி தசம m2 = 78.84375f;

    தசம y = SDL_clamp(v / 10000.0f, 0.0f, 1.0f);
    தசம இலக்கம் = c1 + c2 * SDL_powf(y, m1);
    தசம den = 1.0f + c3 * SDL_powf(y, m1);
    திரும்பு SDL_powf(இலக்கம் / den, m2);
}

/* This is a helpful tool for deriving these:
 * https://kdashg.github.io/misc/colors/from-coeffs.html
 */
நிலையான மாறிலி தசம mat_BT601_Limited_8bit[] = {
    -0.0627451017f, -0.501960814f, -0.501960814f, 0.0f, // offset
    1.1644f, 0.0000f, 1.5960f, 0.0f,                    // Rcoeff
    1.1644f, -0.3918f, -0.8130f, 0.0f,                  // Gcoeff
    1.1644f, 2.0172f, 0.0000f, 0.0f,                    // Bcoeff
};

நிலையான மாறிலி தசம mat_BT601_Full_8bit[] = {
    0.0f, -0.501960814f, -0.501960814f, 0.0f,           // offset
    1.0000f, 0.0000f, 1.4075f, 0.0f,                    // Rcoeff
    1.0000f, -0.3455f, -0.7169f, 0.0f,                  // Gcoeff
    1.0000f, 1.7790f, 0.0000f, 0.0f,                    // Bcoeff
};

நிலையான மாறிலி தசம mat_BT709_Limited_8bit[] = {
    -0.0627451017f, -0.501960814f, -0.501960814f, 0.0f, // offset
    1.1644f, 0.0000f, 1.7927f, 0.0f,                    // Rcoeff
    1.1644f, -0.2132f, -0.5329f, 0.0f,                  // Gcoeff
    1.1644f, 2.1124f, 0.0000f, 0.0f,                    // Bcoeff
};

நிலையான மாறிலி தசம mat_BT709_Full_8bit[] = {
    0.0f, -0.501960814f, -0.501960814f, 0.0f,           // offset
    1.0000f, 0.0000f, 1.5810f, 0.0f,                    // Rcoeff
    1.0000f, -0.1881f, -0.4700f, 0.0f,                  // Gcoeff
    1.0000f, 1.8629f, 0.0000f, 0.0f,                    // Bcoeff
};

நிலையான மாறிலி தசம mat_BT2020_Limited_10bit[] = {
    -0.062561095f, -0.500488759f, -0.500488759f, 0.0f,  // offset
    1.1678f, 0.0000f, 1.6836f, 0.0f,                    // Rcoeff
    1.1678f, -0.1879f, -0.6523f, 0.0f,                  // Gcoeff
    1.1678f, 2.1481f, 0.0000f, 0.0f,                    // Bcoeff
};

நிலையான மாறிலி தசம mat_BT2020_Full_10bit[] = {
    0.0f, -0.500488759f, -0.500488759f, 0.0f,           // offset
    1.0000f, 0.0000f, 1.4760f, 0.0f,                    // Rcoeff
    1.0000f, -0.1647f, -0.5719f, 0.0f,                  // Gcoeff
    1.0000f, 1.8832f, 0.0000f, 0.0f,                    // Bcoeff
};

நிலையான மாறிலி தசம *SDL_GetBT601ConversionMatrix( SDL_Colorspace colorspace )
{
    தேர்வு (SDL_COLORSPACERANGE(colorspace)) {
    நிலை SDL_COLOR_RANGE_LIMITED:
    நிலை SDL_COLOR_RANGE_UNKNOWN:
        திரும்பு mat_BT601_Limited_8bit;
    நிலை SDL_COLOR_RANGE_FULL:
        திரும்பு mat_BT601_Full_8bit;
    இயல்பு:
        நிறுத்து;
    }
    திரும்பு வெற்று;
}

நிலையான மாறிலி தசம *SDL_GetBT709ConversionMatrix(SDL_Colorspace colorspace)
{
    தேர்வு (SDL_COLORSPACERANGE(colorspace)) {
    நிலை SDL_COLOR_RANGE_LIMITED:
    நிலை SDL_COLOR_RANGE_UNKNOWN:
        திரும்பு mat_BT709_Limited_8bit;
    நிலை SDL_COLOR_RANGE_FULL:
        திரும்பு mat_BT709_Full_8bit;
    இயல்பு:
        நிறுத்து;
    }
    திரும்பு வெற்று;
}

நிலையான மாறிலி தசம *SDL_GetBT2020ConversionMatrix(SDL_Colorspace colorspace)
{
    தேர்வு (SDL_COLORSPACERANGE(colorspace)) {
    நிலை SDL_COLOR_RANGE_LIMITED:
    நிலை SDL_COLOR_RANGE_UNKNOWN:
        திரும்பு mat_BT2020_Limited_10bit;
    நிலை SDL_COLOR_RANGE_FULL:
        திரும்பு mat_BT2020_Full_10bit;
    இயல்பு:
        நிறுத்து;
    }
    திரும்பு வெற்று;
}

மாறிலி தசம *SDL_GetYCbCRtoRGBConversionMatrix(SDL_Colorspace colorspace, முழு w, முழு h, முழு bits_per_pixel)
{
    தேர்வு (SDL_COLORSPACEMATRIX(colorspace)) {
    நிலை SDL_MATRIX_COEFFICIENTS_BT601:
    நிலை SDL_MATRIX_COEFFICIENTS_BT470BG:
        திரும்பு SDL_GetBT601ConversionMatrix(colorspace);

    நிலை SDL_MATRIX_COEFFICIENTS_BT709:
        திரும்பு SDL_GetBT709ConversionMatrix(colorspace);

    நிலை SDL_MATRIX_COEFFICIENTS_BT2020_NCL:
        திரும்பு SDL_GetBT2020ConversionMatrix(colorspace);

    நிலை SDL_MATRIX_COEFFICIENTS_UNSPECIFIED:
        தேர்வு (bits_per_pixel) {
        நிலை 8:
            எனில் (h <= YUV_SD_THRESHOLD) {
                திரும்பு SDL_GetBT601ConversionMatrix(colorspace);
            } இல்லையெனில் {
                திரும்பு SDL_GetBT709ConversionMatrix(colorspace);
            }
        நிலை 10:
        நிலை 16:
            திரும்பு SDL_GetBT2020ConversionMatrix(colorspace);
        இயல்பு:
            நிறுத்து;
        }
        நிறுத்து;
    இயல்பு:
        நிறுத்து;
    }
    திரும்பு வெற்று;
}

/* Conversion matrices generated using gamescope color helpers and the primaries definitions at:
    * https://www.itu.int/rec/T-REC-H.273-201612-S/en
    *
    * You can also generate these online using the RGB-XYZ matrix calculator, and then multiplying
    * XYZ_to_dst * src_to_XYZ to get the combined conversion matrix:
    * https://www.russellcottrell.com/photo/matrixCalculator.htm
    */
நிலையான மாறிலி தசம mat601to709[] = {
    0.939542f, 0.050181f, 0.010277f,
    0.017772f, 0.965793f, 0.016435f,
    -0.001622f, -0.004370f, 1.005991f,
};
நிலையான மாறிலி தசம mat601to2020[] = {
    0.595254f, 0.349314f, 0.055432f,
    0.081244f, 0.891503f, 0.027253f,
    0.015512f, 0.081912f, 0.902576f,
};
நிலையான மாறிலி தசம mat709to601[] = {
    1.065379f, -0.055401f, -0.009978f,
    -0.019633f, 1.036363f, -0.016731f,
    0.001632f, 0.004412f, 0.993956f,
};
நிலையான மாறிலி தசம mat709to2020[] = {
    0.627404f, 0.329283f, 0.043313f,
    0.069097f, 0.919541f, 0.011362f,
    0.016391f, 0.088013f, 0.895595f,
};
நிலையான மாறிலி தசம mat2020to601[] = {
    1.776133f, -0.687820f, -0.088313f,
    -0.161376f, 1.187315f, -0.025940f,
    -0.015881f, -0.095931f, 1.111812f,
};
நிலையான மாறிலி தசம mat2020to709[] = {
    1.660496f, -0.587656f, -0.072840f,
    -0.124547f, 1.132895f, -0.008348f,
    -0.018154f, -0.100597f, 1.118751f
};
நிலையான மாறிலி தசம matSMPTE431to709[] = {
    1.120713f, -0.234649f, 0.000000f,
    -0.038478f, 1.087034f, 0.000000f,
    -0.017967f, -0.082030f, 0.954576f,
};
நிலையான மாறிலி தசம matSMPTE431to2020[] = {
    0.689691f, 0.207169f, 0.041346f,
    0.041852f, 0.982426f, 0.010846f,
    -0.001107f, 0.018362f, 0.854914f,
};
நிலையான மாறிலி தசம matSMPTE432to709[] = {
    1.224940f, -0.224940f, -0.000000f,
    -0.042057f, 1.042057f, 0.000000f,
    -0.019638f, -0.078636f, 1.098273f,
};
நிலையான மாறிலி தசம matSMPTE432to2020[] = {
    0.753833f, 0.198597f, 0.047570f,
    0.045744f, 0.941777f, 0.012479f,
    -0.001210f, 0.017602f, 0.983609f,
};

மாறிலி தசம *SDL_GetColorPrimariesConversionMatrix(SDL_ColorPrimaries src, SDL_ColorPrimaries dst)
{
    தேர்வு (dst) {
    நிலை SDL_COLOR_PRIMARIES_BT601:
    நிலை SDL_COLOR_PRIMARIES_SMPTE240:
        தேர்வு (src) {
        நிலை SDL_COLOR_PRIMARIES_BT709:
            திரும்பு mat709to601;
        நிலை SDL_COLOR_PRIMARIES_BT2020:
            திரும்பு mat2020to601;
        இயல்பு:
            நிறுத்து;
        }
        நிறுத்து;
    நிலை SDL_COLOR_PRIMARIES_BT709:
        தேர்வு (src) {
        நிலை SDL_COLOR_PRIMARIES_BT601:
        நிலை SDL_COLOR_PRIMARIES_SMPTE240:
            திரும்பு mat601to709;
        நிலை SDL_COLOR_PRIMARIES_BT2020:
            திரும்பு mat2020to709;
        நிலை SDL_COLOR_PRIMARIES_SMPTE431:
            திரும்பு matSMPTE431to709;
        நிலை SDL_COLOR_PRIMARIES_SMPTE432:
            திரும்பு matSMPTE432to709;
        இயல்பு:
            நிறுத்து;
        }
        நிறுத்து;
    நிலை SDL_COLOR_PRIMARIES_BT2020:
        தேர்வு (src) {
        நிலை SDL_COLOR_PRIMARIES_BT601:
        நிலை SDL_COLOR_PRIMARIES_SMPTE240:
            திரும்பு mat601to2020;
        நிலை SDL_COLOR_PRIMARIES_BT709:
            திரும்பு mat709to2020;
        நிலை SDL_COLOR_PRIMARIES_SMPTE431:
            திரும்பு matSMPTE431to2020;
        நிலை SDL_COLOR_PRIMARIES_SMPTE432:
            திரும்பு matSMPTE432to2020;
        இயல்பு:
            நிறுத்து;
        }
        நிறுத்து;
    இயல்பு:
        நிறுத்து;
    }
    திரும்பு வெற்று;
}

வெறுமை SDL_ConvertColorPrimaries(தசம *fR, தசம *fG, தசம *fB, மாறிலி தசம *matrix)
{
    தசம v[3];

    v[0] = *fR;
    v[1] = *fG;
    v[2] = *fB;

    *fR = matrix[0 * 3 + 0] * v[0] + matrix[0 * 3 + 1] * v[1] + matrix[0 * 3 + 2] * v[2];
    *fG = matrix[1 * 3 + 0] * v[0] + matrix[1 * 3 + 1] * v[1] + matrix[1 * 3 + 2] * v[2];
    *fB = matrix[2 * 3 + 0] * v[0] + matrix[2 * 3 + 1] * v[1] + matrix[2 * 3 + 2] * v[2];
}

வெறுமை SDL_ConvertColor709to2020(தசம *fR, தசம *fG, தசம *fB)
{
    SDL_ConvertColorPrimaries(fR, fG, fB, mat709to2020);
}

SDL_Palette *SDL_CreatePalette(முழு ncolors)
{
    SDL_Palette *palette;

    // Input validation
    CHECK_PARAM(ncolors < 1) {
        SDL_InvalidParamError("ncolors");
        திரும்பு வெற்று;
    }

    palette = (SDL_Palette *)SDL_malloc(அளவு(*palette));
    எனில் (!palette) {
        திரும்பு வெற்று;
    }
    palette->colors = (SDL_Color *)SDL_malloc(ncolors * அளவு(*palette->colors));
    எனில் (!palette->colors) {
        SDL_free(palette);
        திரும்பு வெற்று;
    }
    palette->ncolors = ncolors;
    palette->version = 1;
    palette->refcount = 1;

    SDL_memset(palette->colors, 0xFF, ncolors * அளவு(*palette->colors));

    திரும்பு palette;
}

bool SDL_SetPaletteColors(SDL_Palette *palette, மாறிலி SDL_Color *colors, முழு firstcolor, முழு ncolors)
{
    // Verify the parameters
    எனில் (!palette) {
        திரும்பு false;
    }
    எனில் (ncolors > (palette->ncolors - firstcolor)) {
        ncolors = (palette->ncolors - firstcolor);
    }

    எனில் (colors != (palette->colors + firstcolor)) {
        SDL_memcpy(palette->colors + firstcolor, colors,
                   ncolors * அளவு(*colors));
    }
    ++palette->version;
    எனில் (!palette->version) {
        palette->version = 1;
    }

    திரும்பு true;
}

வெறுமை SDL_DestroyPalette(SDL_Palette *palette)
{
    எனில் (!palette) {
        திரும்பு;
    }
    எனில் (--palette->refcount > 0) {
        திரும்பு;
    }
    SDL_free(palette->colors);
    SDL_free(palette);
}

/*
 * Calculate an 8-bit (3 red, 3 green, 2 blue) dithered palette of colors
 */
வெறுமை SDL_DitherPalette(SDL_Palette *palette)
{
    முழு i;
    எனில் (palette->ncolors != 256) {
        திரும்பு; // only 8bpp supported right now
    }

    க்கு (i = 0; i < palette->ncolors; i++) {
        முழு r, g, b;
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
நிலையான Uint8 SDL_FindColor(மாறிலி SDL_Palette *pal, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    // Do colorspace distance matching
    unsigned முழு smallest;
    unsigned முழு distance;
    முழு rd, gd, bd, ad;
    முழு i;
    Uint8 pixelvalue = 0;

    smallest = ~0U;
    க்கு (i = 0; i < pal->ncolors; ++i) {
        rd = pal->colors[i].r - r;
        gd = pal->colors[i].g - g;
        bd = pal->colors[i].b - b;
        ad = pal->colors[i].a - a;
        distance = (rd * rd) + (gd * gd) + (bd * bd) + (ad * ad);
        எனில் (distance < smallest) {
            pixelvalue = (Uint8)i;
            எனில் (distance == 0) { // Perfect match!
                நிறுத்து;
            }
            smallest = distance;
        }
    }
    திரும்பு pixelvalue;
}

Uint8 SDL_LookupRGBAColor(SDL_HashTable *palette_map, Uint32 pixelvalue, மாறிலி SDL_Palette *pal)
{
    Uint8 color_index = 0;
    எனில் (pal) {
        மாறிலி வெறுமை *மதிப்பு;
        எனில் (SDL_FindInHashTable(palette_map, (மாறிலி வெறுமை *)(uintptr_t)pixelvalue, &மதிப்பு)) {
            color_index = (Uint8)(uintptr_t)மதிப்பு;
        } இல்லையெனில் {
            Uint8 r = (Uint8)((pixelvalue >> 24) & 0xFF);
            Uint8 g = (Uint8)((pixelvalue >> 16) & 0xFF);
            Uint8 b = (Uint8)((pixelvalue >>  8) & 0xFF);
            Uint8 a = (Uint8)((pixelvalue >>  0) & 0xFF);
            color_index = SDL_FindColor(pal, r, g, b, a);
            SDL_செருகு_Into_Hash_Table(palette_map, (மாறிலி வெறுமை *)(uintptr_t)pixelvalue, (மாறிலி வெறுமை *)(uintptr_t)color_index, true);
        }
    }
    திரும்பு color_index;
}

// Tell whether palette is opaque, and if it has an alpha_channel
வெறுமை SDL_DetectPalette(மாறிலி SDL_Palette *pal, bool *is_opaque, bool *has_alpha_channel)
{
    முழு i;

    {
        bool all_opaque = true;
        க்கு (i = 0; i < pal->ncolors; i++) {
            Uint8 alpha_மதிப்பு = pal->colors[i].a;
            எனில் (alpha_மதிப்பு != SDL_ALPHA_OPAQUE) {
                all_opaque = false;
                நிறுத்து;
            }
        }

        எனில் (all_opaque) {
            // Palette is opaque, with an alpha channel
            *is_opaque = true;
            *has_alpha_channel = true;
            திரும்பு;
        }
    }

    {
        bool all_transparent = true;
        க்கு (i = 0; i < pal->ncolors; i++) {
            Uint8 alpha_மதிப்பு = pal->colors[i].a;
            எனில் (alpha_மதிப்பு != SDL_ALPHA_TRANSPARENT) {
                all_transparent = false;
                நிறுத்து;
            }
        }

        எனில் (all_transparent) {
            // Palette is opaque, without an alpha channel
            *is_opaque = true;
            *has_alpha_channel = false;
            திரும்பு;
        }
    }

    // Palette has alpha values
    *is_opaque = false;
    *has_alpha_channel = true;
}

// Find the opaque pixel value corresponding to an RGB triple
Uint32 SDL_MapRGB(மாறிலி SDL_PixelFormatDetails *format, மாறிலி SDL_Palette *palette, Uint8 r, Uint8 g, Uint8 b)
{
    CHECK_PARAM(!format) {
        SDL_InvalidParamError("format");
        திரும்பு 0;
    }

    எனில் (SDL_ISPIXELFORMAT_INDEXED(format->format)) {
        CHECK_PARAM(!palette) {
            SDL_InvalidParamError("palette");
            திரும்பு 0;
        }
        திரும்பு SDL_FindColor(palette, r, g, b, SDL_ALPHA_OPAQUE);
    }

    எனில் (SDL_ISPIXELFORMAT_10BIT(format->format)) {
        திரும்பு (((Uint32)SDL_expand_byte_10[r]) << format->Rshift) |
               (((Uint32)SDL_expand_byte_10[g]) << format->Gshift) |
               (((Uint32)SDL_expand_byte_10[b]) << format->Bshift) |
               format->Amask;
    } இல்லையெனில் {
        திரும்பு ((Uint32)(r >> (8 - format->Rbits))) << format->Rshift |
               ((Uint32)(g >> (8 - format->Gbits))) << format->Gshift |
               ((Uint32)(b >> (8 - format->Bbits))) << format->Bshift |
               format->Amask;
    }
}

// Find the pixel value corresponding to an RGBA quadruple
Uint32 SDL_MapRGBA(மாறிலி SDL_PixelFormatDetails *format, மாறிலி SDL_Palette *palette, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    CHECK_PARAM(!format) {
        SDL_InvalidParamError("format");
        திரும்பு 0;
    }

    எனில் (SDL_ISPIXELFORMAT_INDEXED(format->format)) {
        CHECK_PARAM(!palette) {
            SDL_InvalidParamError("palette");
            திரும்பு 0;
        }
        திரும்பு SDL_FindColor(palette, r, g, b, a);
    }

    எனில் (SDL_ISPIXELFORMAT_10BIT(format->format)) {
        திரும்பு (((Uint32)SDL_expand_byte_10[r]) << format->Rshift) |
               (((Uint32)SDL_expand_byte_10[g]) << format->Gshift) |
               (((Uint32)SDL_expand_byte_10[b]) << format->Bshift) |
               ((((Uint32)(a >> (8 - format->Abits))) << format->Ashift) & format->Amask);
    } இல்லையெனில் {
        திரும்பு ((Uint32)(r >> (8 - format->Rbits))) << format->Rshift |
               ((Uint32)(g >> (8 - format->Gbits))) << format->Gshift |
               ((Uint32)(b >> (8 - format->Bbits))) << format->Bshift |
               ((((Uint32)(a >> (8 - format->Abits))) << format->Ashift) & format->Amask);
    }
}

வெறுமை SDL_GetRGB(Uint32 pixelvalue, மாறிலி SDL_PixelFormatDetails *format, மாறிலி SDL_Palette *palette, Uint8 *r, Uint8 *g, Uint8 *b)
{
    Uint8 unused;

    எனில் (!r) {
        r = &unused;
    }
    எனில் (!g) {
        g = &unused;
    }
    எனில் (!b) {
        b = &unused;
    }

    எனில் (!format) {
        *r = *g = *b = 0;
        திரும்பு;
    }

    எனில் (SDL_ISPIXELFORMAT_INDEXED(format->format)) {
        எனில் (palette && pixelvalue < (unsigned)palette->ncolors) {
            *r = palette->colors[pixelvalue].r;
            *g = palette->colors[pixelvalue].g;
            *b = palette->colors[pixelvalue].b;
        } இல்லையெனில் {
            *r = *g = *b = 0;
        }
        திரும்பு;
    }

    எனில் (SDL_ISPIXELFORMAT_10BIT(format->format)) {
        unsigned v;
        v = (pixelvalue & format->Rmask) >> format->Rshift;
        *r = (Uint8)(v >> 2);
        v = (pixelvalue & format->Gmask) >> format->Gshift;
        *g = (Uint8)(v >> 2);
        v = (pixelvalue & format->Bmask) >> format->Bshift;
        *b = (Uint8)(v >> 2);
    } இல்லையெனில் {
        unsigned v;
        v = (pixelvalue & format->Rmask) >> format->Rshift;
        *r = SDL_expand_byte[format->Rbits][v];
        v = (pixelvalue & format->Gmask) >> format->Gshift;
        *g = SDL_expand_byte[format->Gbits][v];
        v = (pixelvalue & format->Bmask) >> format->Bshift;
        *b = SDL_expand_byte[format->Bbits][v];
    }
}

வெறுமை SDL_GetRGBA(Uint32 pixelvalue, மாறிலி SDL_PixelFormatDetails *format, மாறிலி SDL_Palette *palette, Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a)
{
    Uint8 unused;

    எனில் (!r) {
        r = &unused;
    }
    எனில் (!g) {
        g = &unused;
    }
    எனில் (!b) {
        b = &unused;
    }
    எனில் (!a) {
        a = &unused;
    }

    எனில் (!format) {
        *r = *g = *b = *a = 0;
        திரும்பு;
    }

    எனில் (SDL_ISPIXELFORMAT_INDEXED(format->format)) {
        எனில் (palette && pixelvalue < (unsigned)palette->ncolors) {
            *r = palette->colors[pixelvalue].r;
            *g = palette->colors[pixelvalue].g;
            *b = palette->colors[pixelvalue].b;
            *a = palette->colors[pixelvalue].a;
        } இல்லையெனில் {
            *r = *g = *b = *a = 0;
        }
        திரும்பு;
    }

    எனில் (SDL_ISPIXELFORMAT_10BIT(format->format)) {
        unsigned v;
        v = (pixelvalue & format->Rmask) >> format->Rshift;
        *r = (Uint8)(v >> 2);
        v = (pixelvalue & format->Gmask) >> format->Gshift;
        *g = (Uint8)(v >> 2);
        v = (pixelvalue & format->Bmask) >> format->Bshift;
        *b = (Uint8)(v >> 2);
        v = (pixelvalue & format->Amask) >> format->Ashift;
        *a = SDL_expand_byte[format->Abits][v];
    } இல்லையெனில் {
        unsigned v;
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

bool SDL_IsSamePalette(மாறிலி SDL_Palette *src, மாறிலி SDL_Palette *dst)
{
    எனில் (src->ncolors <= dst->ncolors) {
        // If an identical palette, no need to map
        எனில் (src == dst ||
            (SDL_memcmp(src->colors, dst->colors,
                        src->ncolors * அளவு(SDL_Color)) == 0)) {
            திரும்பு true;
        }
    }
    திரும்பு false;
}

// Map from Palette to Palette
நிலையான Uint8 *Map1to1(மாறிலி SDL_Palette *src, மாறிலி SDL_Palette *dst, முழு *identical)
{
    Uint8 *map;
    முழு i;

    எனில் (SDL_IsSamePalette(src, dst)) {
        *identical = 1;
        திரும்பு வெற்று;
    }
    *identical = 0;

    map = (Uint8 *)SDL_calloc(256, அளவு(Uint8));
    எனில் (!map) {
        திரும்பு வெற்று;
    }
    க்கு (i = 0; i < src->ncolors; ++i) {
        map[i] = SDL_FindColor(dst,
                               src->colors[i].r, src->colors[i].g,
                               src->colors[i].b, src->colors[i].a);
    }
    திரும்பு map;
}

// Map from Palette to BitField
நிலையான Uint8 *Map1toN(மாறிலி SDL_Palette *pal, Uint8 Rmod, Uint8 Gmod, Uint8 Bmod, Uint8 Amod, மாறிலி SDL_PixelFormatDetails *dst)
{
    Uint8 *map;
    முழு i;
    முழு bpp;

    எனில் (!pal) {
        SDL_SetError("src does not have a palette set");
        திரும்பு வெற்று;
    }

    bpp = ((SDL_BYTESPERPIXEL(dst->format) == 3) ? 4 : SDL_BYTESPERPIXEL(dst->format));
    map = (Uint8 *)SDL_calloc(256, bpp);
    எனில் (!map) {
        திரும்பு வெற்று;
    }

    // We memory copy to the pixel map so the endianness is preserved
    க்கு (i = 0; i < pal->ncolors; ++i) {
        Uint8 R = (Uint8)((pal->colors[i].r * Rmod) / 255);
        Uint8 G = (Uint8)((pal->colors[i].g * Gmod) / 255);
        Uint8 B = (Uint8)((pal->colors[i].b * Bmod) / 255);
        Uint8 A = (Uint8)((pal->colors[i].a * Amod) / 255);
        ASSEMBLE_RGBA(&map[i * bpp], SDL_BYTESPERPIXEL(dst->format), dst, (Uint32)R,
                      (Uint32)G, (Uint32)B, (Uint32)A);
    }
    திரும்பு map;
}

bool SDL_ValidateMap(SDL_Surface *src, SDL_Surface *dst)
{
    SDL_BlitMap *map = &src->map;

    எனில் (map->info.dst_fmt != dst->fmt ||
        map->info.dst_pal != dst->palette ||
        (dst->palette &&
         map->dst_palette_version != dst->palette->version) ||
        (src->palette &&
         map->src_palette_version != src->palette->version)) {
        எனில் (!SDL_MapSurface(src, dst)) {
            திரும்பு false;
        }
#எனில் 0
        // just here for debugging
        SDL_Log("src = %p src->flags = %08X map->info.flags = %08x\ndst = %p dst->flags = %08X dst->map.info.flags = %08X\nmap->blit = %p",
            src, dst->flags, map->info.flags, dst, dst->flags,
            dst->map.info.flags, map->blit);
#endif
    } இல்லையெனில் {
        map->info.dst_surface = dst;
    }
    திரும்பு true;
}

வெறுமை SDL_InvalidateMap(SDL_BlitMap *map)
{
    map->info.dst_fmt = வெற்று;
    map->info.dst_pal = வெற்று;
    map->src_palette_version = 0;
    map->dst_palette_version = 0;
    எனில் (map->info.table) {
        SDL_free(map->info.table);
        map->info.table = வெற்று;
    }
    எனில் (map->info.palette_map) {
        SDL_DestroyHashTable(map->info.palette_map);
        map->info.palette_map = வெற்று;
    }
}

bool SDL_MapSurface(SDL_Surface *src, SDL_Surface *dst)
{
    மாறிலி SDL_PixelFormatDetails *srcfmt;
    மாறிலி SDL_Palette *srcpal;
    மாறிலி SDL_PixelFormatDetails *dstfmt;
    மாறிலி SDL_Palette *dstpal;
    SDL_BlitMap *map;

    // Clear out any previous mapping
    map = &src->map;
#ifdef SDL_HAVE_RLE
    எனில் (src->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL) {
        SDL_UnRLESurface(src);
    }
#endif
    SDL_InvalidateMap(map);

    // Figure out what kind of mapping we're doing
    map->identity = 0;
    srcfmt = src->fmt;
    srcpal = src->palette;
    dstfmt = dst->fmt;
    dstpal = dst->palette;
    எனில் (SDL_ISPIXELFORMAT_INDEXED(srcfmt->format)) {
        எனில் (SDL_ISPIXELFORMAT_INDEXED(dstfmt->format)) {
            // Palette --> Palette
            எனில் (srcpal && dstpal) {
                map->info.table = Map1to1(srcpal, dstpal, &map->identity);
            } இல்லையெனில் {
                map->identity = 1;
            }
            எனில் (!map->identity) {
                எனில் (!map->info.table) {
                    திரும்பு false;
                }
            }
            எனில் (srcfmt->bits_per_pixel != dstfmt->bits_per_pixel) {
                map->identity = 0;
            }
        } இல்லையெனில் {
            // Palette --> BitField
            map->info.table =
                Map1toN(srcpal, src->map.info.r, src->map.info.g,
                        src->map.info.b, src->map.info.a, dstfmt);
            எனில் (!map->info.table) {
                திரும்பு false;
            }
        }
    } இல்லையெனில் {
        எனில் (SDL_ISPIXELFORMAT_INDEXED(dstfmt->format)) {
            // BitField --> Palette
            map->info.palette_map = SDL_CreateHashTable(0, false, SDL_HashID, SDL_சாவி_Match_ID, வெற்று, வெற்று);
        } இல்லையெனில் {
            // BitField --> BitField
            எனில் (srcfmt == dstfmt) {
                map->identity = 1;
            }
        }
    }

    எனில் (dstpal) {
        map->dst_palette_version = dstpal->version;
    } இல்லையெனில் {
        map->dst_palette_version = 0;
    }

    எனில் (srcpal) {
        map->src_palette_version = srcpal->version;
    } இல்லையெனில் {
        map->src_palette_version = 0;
    }

    // Choose your blitters wisely
    திரும்பு SDL_CalculateBlit(src, dst);
}


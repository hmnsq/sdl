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
#अन्तर्भाव "SDL_internal.h"

// General (mostly internal) pixel/color manipulation routines for SDL

#अन्तर्भाव "SDL_sysvideo.h"
#अन्तर्भाव "SDL_pixels_c.h"
#अन्तर्भाव "SDL_RLEaccel_c.h"

// Lookup tables to expand partial bytes to the full 0..255 range

// This is the code used to generate the lookup tables below:
#यदि 0
#अन्तर्भाव <SDL3/SDL.h>

#define GENERATE_SHIFTS

स्थिर Uint32 Calculate(पूर्णाङ्क v, पूर्णाङ्क bits, पूर्णाङ्क vmax, पूर्णाङ्क shift)
{
#यदि defined(GENERATE_FLOOR)
    (शून्य)bits;
    प्रत्यागम (Uint32)SDL_floor(v * 255.0f / vmax) << shift;
#नोचेद्यदि defined(GENERATE_ROUND)
    (शून्य)bits;
    प्रत्यागम (Uint32)SDL_roundf(v * 255.0f / vmax) << shift;
#नोचेद्यदि defined(GENERATE_SHIFTS)
    (शून्य)vmax;
    विकल्प (bits) {
    पक्ष 1:
        v = (v << 7) | (v << 6) | (v << 5) | (v << 4) | (v << 3) | (v << 2) | (v << 1) | v;
        भङ्ग;
    पक्ष 2:
        v = (v << 6) | (v << 4) | (v << 2) | v;
        भङ्ग;
    पक्ष 3:
        v = (v << 5) | (v << 2) | (v >> 1);
        भङ्ग;
    पक्ष 4:
        v = (v << 4) | v;
        भङ्ग;
    पक्ष 5:
        v = (v << 3) | (v >> 2);
        भङ्ग;
    पक्ष 6:
        v = (v << 2) | (v >> 4);
        भङ्ग;
    पक्ष 7:
        v = (v << 1) | (v >> 6);
        भङ्ग;
    पक्ष 8:
        भङ्ग;
    }
    प्रत्यागम (Uint32)v << shift;
#endif
}

पूर्णाङ्क main(पूर्णाङ्क argc, वर्ण *argv[])
{
    पूर्णाङ्क i, b;
    SDL_IOStream *io = SDL_IOFromDynamicMem();

    (शून्य)argc;
    (शून्य)argv;
    प्रति (b = 1; b <= 8; ++b) {
        SDL_IOprintf(io, "static const Uint8 lookup_%d[] = {\n    ", b);
        प्रति (i = 0; i < (1 << b); ++i) {
            यदि (i > 0) {
                SDL_IOprintf(io, ", ");
            }
            SDL_IOprintf(io, "%d", Calculate(i, b, (1 << b) - 1, 0));
        }
        SDL_Log("%s\n};\n\n", (ध्रुव वर्ण *)SDL_GetPointerProperty(SDL_GetIOProperties(io), SDL_PROP_IOSTREAM_DYNAMIC_MEMORY_POINTER, रिक्त));
        SDL_SeekIO(io, 0, SDL_IO_SEEK_SET);
        SDL_WriteIO(io, "", 1);
        SDL_SeekIO(io, 0, SDL_IO_SEEK_SET);
    }
    SDL_CloseIO(io);
    प्रत्यागम 0;
}
#endif

स्थिर ध्रुव Uint8 lookup_0[] = {
    255
};

स्थिर ध्रुव Uint8 lookup_1[] = {
    0, 255
};

स्थिर ध्रुव Uint8 lookup_2[] = {
    0, 85, 170, 255
};

स्थिर ध्रुव Uint8 lookup_3[] = {
    0, 36, 73, 109, 146, 182, 219, 255
};

स्थिर ध्रुव Uint8 lookup_4[] = {
    0, 17, 34, 51, 68, 85, 102, 119, 136, 153, 170, 187, 204, 221, 238, 255
};

स्थिर ध्रुव Uint8 lookup_5[] = {
    0, 8, 16, 24, 33, 41, 49, 57, 66, 74, 82, 90, 99, 107, 115, 123, 132, 140, 148, 156, 165, 173, 181, 189, 198, 206, 214, 222, 231, 239, 247, 255
};

स्थिर ध्रुव Uint8 lookup_6[] = {
    0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 65, 69, 73, 77, 81, 85, 89, 93, 97, 101, 105, 109, 113, 117, 121, 125, 130, 134, 138, 142, 146, 150, 154, 158, 162, 166, 170, 174, 178, 182, 186, 190, 195, 199, 203, 207, 211, 215, 219, 223, 227, 231, 235, 239, 243, 247, 251, 255
};

स्थिर ध्रुव Uint8 lookup_7[] = {
    0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64, 66, 68, 70, 72, 74, 76, 78, 80, 82, 84, 86, 88, 90, 92, 94, 96, 98, 100, 102, 104, 106, 108, 110, 112, 114, 116, 118, 120, 122, 124, 126, 129, 131, 133, 135, 137, 139, 141, 143, 145, 147, 149, 151, 153, 155, 157, 159, 161, 163, 165, 167, 169, 171, 173, 175, 177, 179, 181, 183, 185, 187, 189, 191, 193, 195, 197, 199, 201, 203, 205, 207, 209, 211, 213, 215, 217, 219, 221, 223, 225, 227, 229, 231, 233, 235, 237, 239, 241, 243, 245, 247, 249, 251, 253, 255
};

स्थिर ध्रुव Uint8 lookup_8[] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255
};

ध्रुव Uint8 *SDL_expand_byte[9] = {
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
ध्रुव Uint16 SDL_expand_byte_10[] = {
    0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 64, 68, 72, 76, 80, 84, 88, 92, 96, 100, 104, 108, 112, 116, 120, 124, 128, 132, 136, 140, 144, 148, 152, 156, 160, 164, 168, 173, 177, 181, 185, 189, 193, 197, 201, 205, 209, 213, 217, 221, 225, 229, 233, 237, 241, 245, 249, 253, 257, 261, 265, 269, 273, 277, 281, 285, 289, 293, 297, 301, 305, 309, 313, 317, 321, 325, 329, 333, 337, 341, 345, 349, 353, 357, 361, 365, 369, 373, 377, 381, 385, 389, 393, 397, 401, 405, 409, 413, 417, 421, 425, 429, 433, 437, 441, 445, 449, 453, 457, 461, 465, 469, 473, 477, 481, 485, 489, 493, 497, 501, 505, 509, 514, 518, 522, 526, 530, 534, 538, 542, 546, 550, 554, 558, 562, 566, 570, 574, 578, 582, 586, 590, 594, 598, 602, 606, 610, 614, 618, 622, 626, 630, 634, 638, 642, 646, 650, 654, 658, 662, 666, 670, 674, 678, 682, 686, 690, 694, 698, 702, 706, 710, 714, 718, 722, 726, 730, 734, 738, 742, 746, 750, 754, 758, 762, 766, 770, 774, 778, 782, 786, 790, 794, 798, 802, 806, 810, 814, 818, 822, 826, 830, 834, 838, 842, 846, 850, 855, 859, 863, 867, 871, 875, 879, 883, 887, 891, 895, 899, 903, 907, 911, 915, 919, 923, 927, 931, 935, 939, 943, 947, 951, 955, 959, 963, 967, 971, 975, 979, 983, 987, 991, 995, 999, 1003, 1007, 1011, 1015, 1019, 1023
};
SDL_COMPILE_TIME_ASSERT(SDL_expand_byte_10_size, SDL_arraysize(SDL_expand_byte_10) == (1 << 8));


// Helper functions

#define CASE(X) \
    पक्ष X:     \
        प्रत्यागम #X;
ध्रुव वर्ण *SDL_GetPixelFormatName(SDL_PixelFormat format)
{
    विकल्प (format) {

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

    स्वभाव:
        प्रत्यागम "SDL_PIXELFORMAT_UNKNOWN";
    }
}
#undef CASE

bool SDL_GetMasksForPixelFormat(SDL_PixelFormat format, पूर्णाङ्क *bpp, Uint32 *Rmask, Uint32 *Gmask, Uint32 *Bmask, Uint32 *Amask)
{
    Uint32 masks[4];

#ifdef SDL_HAVE_YUV
    // Partial support for SDL_Surface with FOURCC
    यदि (SDL_ISPIXELFORMAT_FOURCC(format)) {
        // Not a format that uses masks
        *Rmask = *Gmask = *Bmask = *Amask = 0;
        // however, some of these are packed formats, and can legit declare bits-per-pixel!
        विकल्प (format) {
            पक्ष SDL_PIXELFORMAT_YUY2:
            पक्ष SDL_PIXELFORMAT_UYVY:
            पक्ष SDL_PIXELFORMAT_YVYU:
                *bpp = 32;
                भङ्ग;
            स्वभाव:
                *bpp = 0;  // oh well.
        }
        प्रत्यागम true;
    }
#अन्यथा
    यदि (SDL_ISPIXELFORMAT_FOURCC(format)) {
        प्रत्यागम SDL_SetError("SDL not built with YUV support");
    }
#endif

    // Initialize the values here
    यदि (SDL_BYTESPERPIXEL(format) <= 2) {
        *bpp = SDL_BITSPERPIXEL(format);
    } अन्यथा {
        *bpp = SDL_BYTESPERPIXEL(format) * 8;
    }
    *Rmask = *Gmask = *Bmask = *Amask = 0;

    यदि (SDL_PIXELTYPE(format) == SDL_PIXELTYPE_ARRAYU8) {
        विकल्प (SDL_BYTESPERPIXEL(format)) {
        पक्ष 3:
            विकल्प (SDL_PIXELORDER(format)) {
            पक्ष SDL_ARRAYORDER_RGB:
#यदि SDL_BYTEORDER == SDL_BIG_ENDIAN
                *Rmask = 0x00FF0000;
                *Gmask = 0x0000FF00;
                *Bmask = 0x000000FF;
#अन्यथा
                *Rmask = 0x000000FF;
                *Gmask = 0x0000FF00;
                *Bmask = 0x00FF0000;
#endif
                प्रत्यागम true;
            पक्ष SDL_ARRAYORDER_BGR:
#यदि SDL_BYTEORDER == SDL_BIG_ENDIAN
                *Rmask = 0x000000FF;
                *Gmask = 0x0000FF00;
                *Bmask = 0x00FF0000;
#अन्यथा
                *Rmask = 0x00FF0000;
                *Gmask = 0x0000FF00;
                *Bmask = 0x000000FF;
#endif
                प्रत्यागम true;
            स्वभाव:
                भङ्ग;
            }
            भङ्ग;
        पक्ष 4:
            विकल्प (SDL_PIXELORDER(format)) {
            पक्ष SDL_ARRAYORDER_RGBA:
#यदि SDL_BYTEORDER == SDL_BIG_ENDIAN
                *Rmask = 0xFF000000;
                *Gmask = 0x00FF0000;
                *Bmask = 0x0000FF00;
                *Amask = 0x000000FF;
#अन्यथा
                *Rmask = 0x000000FF;
                *Gmask = 0x0000FF00;
                *Bmask = 0x00FF0000;
                *Amask = 0xFF000000;
#endif
                प्रत्यागम true;
            पक्ष SDL_ARRAYORDER_ARGB:
#यदि SDL_BYTEORDER == SDL_BIG_ENDIAN
                *Rmask = 0x00FF0000;
                *Gmask = 0x0000FF00;
                *Bmask = 0x000000FF;
                *Amask = 0xFF000000;
#अन्यथा
                *Rmask = 0x0000FF00;
                *Gmask = 0x00FF0000;
                *Bmask = 0xFF000000;
                *Amask = 0x000000FF;
#endif
                प्रत्यागम true;
            पक्ष SDL_ARRAYORDER_BGRA:
#यदि SDL_BYTEORDER == SDL_BIG_ENDIAN
                *Rmask = 0x0000FF00;
                *Gmask = 0x00FF0000;
                *Bmask = 0xFF000000;
                *Amask = 0x000000FF;
#अन्यथा
                *Rmask = 0x00FF0000;
                *Gmask = 0x0000FF00;
                *Bmask = 0x000000FF;
                *Amask = 0xFF000000;
#endif
                प्रत्यागम true;
            पक्ष SDL_ARRAYORDER_ABGR:
#यदि SDL_BYTEORDER == SDL_BIG_ENDIAN
                *Rmask = 0x000000FF;
                *Gmask = 0x0000FF00;
                *Bmask = 0x00FF0000;
                *Amask = 0xFF000000;
#अन्यथा
                *Rmask = 0xFF000000;
                *Gmask = 0x00FF0000;
                *Bmask = 0x0000FF00;
                *Amask = 0x000000FF;
#endif
                प्रत्यागम true;
            स्वभाव:
                भङ्ग;
            }
            भङ्ग;
        स्वभाव:
            भङ्ग;
        }
        प्रत्यागम SDL_SetError("Unknown pixel format");
    }

    यदि (SDL_PIXELTYPE(format) != SDL_PIXELTYPE_PACKED8 &&
        SDL_PIXELTYPE(format) != SDL_PIXELTYPE_PACKED16 &&
        SDL_PIXELTYPE(format) != SDL_PIXELTYPE_PACKED32) {
        // Not a format that uses masks
        प्रत्यागम true;
    }

    विकल्प (SDL_PIXELLAYOUT(format)) {
    पक्ष SDL_PACKEDLAYOUT_332:
        masks[0] = 0x00000000;
        masks[1] = 0x000000E0;
        masks[2] = 0x0000001C;
        masks[3] = 0x00000003;
        भङ्ग;
    पक्ष SDL_PACKEDLAYOUT_4444:
        masks[0] = 0x0000F000;
        masks[1] = 0x00000F00;
        masks[2] = 0x000000F0;
        masks[3] = 0x0000000F;
        भङ्ग;
    पक्ष SDL_PACKEDLAYOUT_1555:
        masks[0] = 0x00008000;
        masks[1] = 0x00007C00;
        masks[2] = 0x000003E0;
        masks[3] = 0x0000001F;
        भङ्ग;
    पक्ष SDL_PACKEDLAYOUT_5551:
        masks[0] = 0x0000F800;
        masks[1] = 0x000007C0;
        masks[2] = 0x0000003E;
        masks[3] = 0x00000001;
        भङ्ग;
    पक्ष SDL_PACKEDLAYOUT_565:
        masks[0] = 0x00000000;
        masks[1] = 0x0000F800;
        masks[2] = 0x000007E0;
        masks[3] = 0x0000001F;
        भङ्ग;
    पक्ष SDL_PACKEDLAYOUT_8888:
        masks[0] = 0xFF000000;
        masks[1] = 0x00FF0000;
        masks[2] = 0x0000FF00;
        masks[3] = 0x000000FF;
        भङ्ग;
    पक्ष SDL_PACKEDLAYOUT_2101010:
        masks[0] = 0xC0000000;
        masks[1] = 0x3FF00000;
        masks[2] = 0x000FFC00;
        masks[3] = 0x000003FF;
        भङ्ग;
    पक्ष SDL_PACKEDLAYOUT_1010102:
        masks[0] = 0xFFC00000;
        masks[1] = 0x003FF000;
        masks[2] = 0x00000FFC;
        masks[3] = 0x00000003;
        भङ्ग;
    स्वभाव:
        प्रत्यागम SDL_SetError("Unknown pixel format");
    }

    विकल्प (SDL_PIXELORDER(format)) {
    पक्ष SDL_PACKEDORDER_XRGB:
        *Rmask = masks[1];
        *Gmask = masks[2];
        *Bmask = masks[3];
        भङ्ग;
    पक्ष SDL_PACKEDORDER_RGBX:
        *Rmask = masks[0];
        *Gmask = masks[1];
        *Bmask = masks[2];
        भङ्ग;
    पक्ष SDL_PACKEDORDER_ARGB:
        *Amask = masks[0];
        *Rmask = masks[1];
        *Gmask = masks[2];
        *Bmask = masks[3];
        भङ्ग;
    पक्ष SDL_PACKEDORDER_RGBA:
        *Rmask = masks[0];
        *Gmask = masks[1];
        *Bmask = masks[2];
        *Amask = masks[3];
        भङ्ग;
    पक्ष SDL_PACKEDORDER_XBGR:
        *Bmask = masks[1];
        *Gmask = masks[2];
        *Rmask = masks[3];
        भङ्ग;
    पक्ष SDL_PACKEDORDER_BGRX:
        *Bmask = masks[0];
        *Gmask = masks[1];
        *Rmask = masks[2];
        भङ्ग;
    पक्ष SDL_PACKEDORDER_BGRA:
        *Bmask = masks[0];
        *Gmask = masks[1];
        *Rmask = masks[2];
        *Amask = masks[3];
        भङ्ग;
    पक्ष SDL_PACKEDORDER_ABGR:
        *Amask = masks[0];
        *Bmask = masks[1];
        *Gmask = masks[2];
        *Rmask = masks[3];
        भङ्ग;
    स्वभाव:
        प्रत्यागम SDL_SetError("Unknown pixel format");
    }
    प्रत्यागम true;
}

SDL_PixelFormat SDL_GetPixelFormatForMasks(पूर्णाङ्क bpp, Uint32 Rmask, Uint32 Gmask, Uint32 Bmask, Uint32 Amask)
{
    विकल्प (bpp) {
    पक्ष 1:
        // SDL defaults to MSB ordering
        प्रत्यागम SDL_PIXELFORMAT_INDEX1MSB;
    पक्ष 2:
        // SDL defaults to MSB ordering
        प्रत्यागम SDL_PIXELFORMAT_INDEX2MSB;
    पक्ष 4:
        // SDL defaults to MSB ordering
        प्रत्यागम SDL_PIXELFORMAT_INDEX4MSB;
    पक्ष 8:
        यदि (Rmask == 0xE0 &&
            Gmask == 0x1C &&
            Bmask == 0x03 &&
            Amask == 0x00) {
            प्रत्यागम SDL_PIXELFORMAT_RGB332;
        }
        प्रत्यागम SDL_PIXELFORMAT_INDEX8;
    पक्ष 12:
        यदि (Rmask == 0) {
            प्रत्यागम SDL_PIXELFORMAT_XRGB4444;
        }
        यदि (Rmask == 0x0F00 &&
            Gmask == 0x00F0 &&
            Bmask == 0x000F &&
            Amask == 0x0000) {
            प्रत्यागम SDL_PIXELFORMAT_XRGB4444;
        }
        यदि (Rmask == 0x000F &&
            Gmask == 0x00F0 &&
            Bmask == 0x0F00 &&
            Amask == 0x0000) {
            प्रत्यागम SDL_PIXELFORMAT_XBGR4444;
        }
        भङ्ग;
    पक्ष 15:
        यदि (Rmask == 0) {
            प्रत्यागम SDL_PIXELFORMAT_XRGB1555;
        }
        SDL_FALLTHROUGH;
    पक्ष 16:
        यदि (Rmask == 0) {
            प्रत्यागम SDL_PIXELFORMAT_RGB565;
        }
        यदि (Rmask == 0x7C00 &&
            Gmask == 0x03E0 &&
            Bmask == 0x001F &&
            Amask == 0x0000) {
            प्रत्यागम SDL_PIXELFORMAT_XRGB1555;
        }
        यदि (Rmask == 0x001F &&
            Gmask == 0x03E0 &&
            Bmask == 0x7C00 &&
            Amask == 0x0000) {
            प्रत्यागम SDL_PIXELFORMAT_XBGR1555;
        }
        यदि (Rmask == 0x0F00 &&
            Gmask == 0x00F0 &&
            Bmask == 0x000F &&
            Amask == 0xF000) {
            प्रत्यागम SDL_PIXELFORMAT_ARGB4444;
        }
        यदि (Rmask == 0xF000 &&
            Gmask == 0x0F00 &&
            Bmask == 0x00F0 &&
            Amask == 0x000F) {
            प्रत्यागम SDL_PIXELFORMAT_RGBA4444;
        }
        यदि (Rmask == 0x000F &&
            Gmask == 0x00F0 &&
            Bmask == 0x0F00 &&
            Amask == 0xF000) {
            प्रत्यागम SDL_PIXELFORMAT_ABGR4444;
        }
        यदि (Rmask == 0x00F0 &&
            Gmask == 0x0F00 &&
            Bmask == 0xF000 &&
            Amask == 0x000F) {
            प्रत्यागम SDL_PIXELFORMAT_BGRA4444;
        }
        यदि (Rmask == 0x7C00 &&
            Gmask == 0x03E0 &&
            Bmask == 0x001F &&
            Amask == 0x8000) {
            प्रत्यागम SDL_PIXELFORMAT_ARGB1555;
        }
        यदि (Rmask == 0xF800 &&
            Gmask == 0x07C0 &&
            Bmask == 0x003E &&
            Amask == 0x0001) {
            प्रत्यागम SDL_PIXELFORMAT_RGBA5551;
        }
        यदि (Rmask == 0x001F &&
            Gmask == 0x03E0 &&
            Bmask == 0x7C00 &&
            Amask == 0x8000) {
            प्रत्यागम SDL_PIXELFORMAT_ABGR1555;
        }
        यदि (Rmask == 0x003E &&
            Gmask == 0x07C0 &&
            Bmask == 0xF800 &&
            Amask == 0x0001) {
            प्रत्यागम SDL_PIXELFORMAT_BGRA5551;
        }
        यदि (Rmask == 0xF800 &&
            Gmask == 0x07E0 &&
            Bmask == 0x001F &&
            Amask == 0x0000) {
            प्रत्यागम SDL_PIXELFORMAT_RGB565;
        }
        यदि (Rmask == 0x001F &&
            Gmask == 0x07E0 &&
            Bmask == 0xF800 &&
            Amask == 0x0000) {
            प्रत्यागम SDL_PIXELFORMAT_BGR565;
        }
        यदि (Rmask == 0x003F &&
            Gmask == 0x07C0 &&
            Bmask == 0xF800 &&
            Amask == 0x0000) {
            // Technically this would be BGR556, but Witek says this works in bug 3158
            प्रत्यागम SDL_PIXELFORMAT_RGB565;
        }
        भङ्ग;
    पक्ष 24:
        विकल्प (Rmask) {
        पक्ष 0:
        पक्ष 0x00FF0000:
#यदि SDL_BYTEORDER == SDL_BIG_ENDIAN
            प्रत्यागम SDL_PIXELFORMAT_RGB24;
#अन्यथा
            प्रत्यागम SDL_PIXELFORMAT_BGR24;
#endif
        पक्ष 0x000000FF:
#यदि SDL_BYTEORDER == SDL_BIG_ENDIAN
            प्रत्यागम SDL_PIXELFORMAT_BGR24;
#अन्यथा
            प्रत्यागम SDL_PIXELFORMAT_RGB24;
#endif
        }
        भङ्ग;
    पक्ष 30:
        यदि (Rmask == 0x3FF00000 &&
            Gmask == 0x000FFC00 &&
            Bmask == 0x000003FF &&
            Amask == 0x00000000) {
            प्रत्यागम SDL_PIXELFORMAT_XRGB2101010;
        }
        यदि (Rmask == 0x000003FF &&
            Gmask == 0x000FFC00 &&
            Bmask == 0x3FF00000 &&
            Amask == 0x00000000) {
            प्रत्यागम SDL_PIXELFORMAT_XBGR2101010;
        }
        भङ्ग;
    पक्ष 32:
        यदि (Rmask == 0) {
            प्रत्यागम SDL_PIXELFORMAT_XRGB8888;
        }
        यदि (Rmask == 0x00FF0000 &&
            Gmask == 0x0000FF00 &&
            Bmask == 0x000000FF &&
            Amask == 0x00000000) {
            प्रत्यागम SDL_PIXELFORMAT_XRGB8888;
        }
        यदि (Rmask == 0xFF000000 &&
            Gmask == 0x00FF0000 &&
            Bmask == 0x0000FF00 &&
            Amask == 0x00000000) {
            प्रत्यागम SDL_PIXELFORMAT_RGBX8888;
        }
        यदि (Rmask == 0x000000FF &&
            Gmask == 0x0000FF00 &&
            Bmask == 0x00FF0000 &&
            Amask == 0x00000000) {
            प्रत्यागम SDL_PIXELFORMAT_XBGR8888;
        }
        यदि (Rmask == 0x0000FF00 &&
            Gmask == 0x00FF0000 &&
            Bmask == 0xFF000000 &&
            Amask == 0x00000000) {
            प्रत्यागम SDL_PIXELFORMAT_BGRX8888;
        }
        यदि (Rmask == 0x00FF0000 &&
            Gmask == 0x0000FF00 &&
            Bmask == 0x000000FF &&
            Amask == 0xFF000000) {
            प्रत्यागम SDL_PIXELFORMAT_ARGB8888;
        }
        यदि (Rmask == 0xFF000000 &&
            Gmask == 0x00FF0000 &&
            Bmask == 0x0000FF00 &&
            Amask == 0x000000FF) {
            प्रत्यागम SDL_PIXELFORMAT_RGBA8888;
        }
        यदि (Rmask == 0x000000FF &&
            Gmask == 0x0000FF00 &&
            Bmask == 0x00FF0000 &&
            Amask == 0xFF000000) {
            प्रत्यागम SDL_PIXELFORMAT_ABGR8888;
        }
        यदि (Rmask == 0x0000FF00 &&
            Gmask == 0x00FF0000 &&
            Bmask == 0xFF000000 &&
            Amask == 0x000000FF) {
            प्रत्यागम SDL_PIXELFORMAT_BGRA8888;
        }
        यदि (Rmask == 0x3FF00000 &&
            Gmask == 0x000FFC00 &&
            Bmask == 0x000003FF &&
            Amask == 0x00000000) {
            प्रत्यागम SDL_PIXELFORMAT_XRGB2101010;
        }
        यदि (Rmask == 0x000003FF &&
            Gmask == 0x000FFC00 &&
            Bmask == 0x3FF00000 &&
            Amask == 0x00000000) {
            प्रत्यागम SDL_PIXELFORMAT_XBGR2101010;
        }
        यदि (Rmask == 0x3FF00000 &&
            Gmask == 0x000FFC00 &&
            Bmask == 0x000003FF &&
            Amask == 0xC0000000) {
            प्रत्यागम SDL_PIXELFORMAT_ARGB2101010;
        }
        यदि (Rmask == 0x000003FF &&
            Gmask == 0x000FFC00 &&
            Bmask == 0x3FF00000 &&
            Amask == 0xC0000000) {
            प्रत्यागम SDL_PIXELFORMAT_ABGR2101010;
        }
        भङ्ग;
    }
    प्रत्यागम SDL_PIXELFORMAT_UNKNOWN;
}

स्थिर SDL_InitState SDL_format_details_init;
स्थिर SDL_HashTable *SDL_format_details;

स्थिर bool SDL_InitPixelFormatDetails(SDL_PixelFormatDetails *details, SDL_PixelFormat format)
{
    पूर्णाङ्क bpp;
    Uint32 Rmask, Gmask, Bmask, Amask;
    Uint32 mask;

    यदि (!SDL_GetMasksForPixelFormat(format, &bpp, &Rmask, &Gmask, &Bmask, &Amask)) {
        प्रत्यागम false;
    }

    // Set up the format
    SDL_zerop(details);
    details->format = format;
    details->bits_per_pixel = (Uint8)bpp;
    details->bytes_per_pixel = (Uint8)((bpp + 7) / 8);

    details->Rmask = Rmask;
    details->Rshift = 0;
    details->Rbits = 0;
    यदि (Rmask) {
        प्रति (mask = Rmask; !(mask & 0x01); mask >>= 1) {
            ++details->Rshift;
        }
        प्रति (; (mask & 0x01); mask >>= 1) {
            ++details->Rbits;
        }
    }

    details->Gmask = Gmask;
    details->Gshift = 0;
    details->Gbits = 0;
    यदि (Gmask) {
        प्रति (mask = Gmask; !(mask & 0x01); mask >>= 1) {
            ++details->Gshift;
        }
        प्रति (; (mask & 0x01); mask >>= 1) {
            ++details->Gbits;
        }
    }

    details->Bmask = Bmask;
    details->Bshift = 0;
    details->Bbits = 0;
    यदि (Bmask) {
        प्रति (mask = Bmask; !(mask & 0x01); mask >>= 1) {
            ++details->Bshift;
        }
        प्रति (; (mask & 0x01); mask >>= 1) {
            ++details->Bbits;
        }
    }

    details->Amask = Amask;
    details->Ashift = 0;
    details->Abits = 0;
    यदि (Amask) {
        प्रति (mask = Amask; !(mask & 0x01); mask >>= 1) {
            ++details->Ashift;
        }
        प्रति (; (mask & 0x01); mask >>= 1) {
            ++details->Abits;
        }
    }

    प्रत्यागम true;
}

ध्रुव SDL_PixelFormatDetails *SDL_GetPixelFormatDetails(SDL_PixelFormat format)
{
    SDL_PixelFormatDetails *details;

    यदि (SDL_ShouldInit(&SDL_format_details_init)) {
        SDL_format_details = SDL_CreateHashTable(0, true, SDL_HashID, SDL_कुंजी_Match_ID, SDL_Destroy_Hash_मूल्य, रिक्त);
        यदि (!SDL_format_details) {
            SDL_SetInitialized(&SDL_format_details_init, false);
            प्रत्यागम रिक्त;
        }
        SDL_SetInitialized(&SDL_format_details_init, true);
    }

    यदि (SDL_FindInHashTable(SDL_format_details, (ध्रुव शून्य *)(uintptr_t)format, (ध्रुव शून्य **)&details)) {
        प्रत्यागम details;
    }

    // Allocate an empty pixel format structure, and initialize it
    details = (SDL_PixelFormatDetails *)SDL_malloc(परिमाण(*details));
    यदि (!details) {
        प्रत्यागम रिक्त;
    }

    यदि (!SDL_InitPixelFormatDetails(details, format)) {
        SDL_free(details);
        प्रत्यागम रिक्त;
    }

    यदि (!SDL_जोड़ो_Into_Hash_Table(SDL_format_details, (ध्रुव शून्य *)(uintptr_t)format, (शून्य *)details, false)) {
        SDL_free(details);
        // uh...did another thread beat us to inserting this?
        यदि (SDL_FindInHashTable(SDL_format_details, (ध्रुव शून्य *)(uintptr_t)format, (ध्रुव शून्य **)&details)) {
            प्रत्यागम details;
        }
        प्रत्यागम रिक्त;  // oh well.
    }

    प्रत्यागम details;
}

शून्य SDL_QuitPixelFormatDetails(शून्य)
{
    यदि (SDL_ShouldQuit(&SDL_format_details_init)) {
        SDL_DestroyHashTable(SDL_format_details);
        SDL_format_details = रिक्त;
        SDL_SetInitialized(&SDL_format_details_init, false);
    }
}

शून्य SDL_Get8888AlphaMaskAndShift(ध्रुव SDL_PixelFormatDetails *fmt, Uint32 *mask, Uint32 *shift)
{
    यदि (fmt->Amask) {
        *mask = fmt->Amask;
        *shift = fmt->Ashift;
    } अन्यथा {
        *mask = ~(fmt->Rmask | fmt->Gmask | fmt->Bmask);
        विकल्प (*mask) {
        पक्ष 0x000000FF:
            *shift = 0;
            भङ्ग;
        पक्ष 0x0000FF00:
            *shift = 8;
            भङ्ग;
        पक्ष 0x00FF0000:
            *shift = 16;
            भङ्ग;
        पक्ष 0xFF000000:
            *shift = 24;
            भङ्ग;
        स्वभाव:
            // Should never happen
            *shift = 0;
            भङ्ग;
        }
    }
}

SDL_Colorspace SDL_GetDefaultColorspaceForFormat(SDL_PixelFormat format)
{
    यदि (SDL_ISPIXELFORMAT_FOURCC(format)) {
        यदि (format == SDL_PIXELFORMAT_MJPG) {
            प्रत्यागम SDL_COLORSPACE_SRGB;
        } अन्यथा यदि (format == SDL_PIXELFORMAT_P010 || format == SDL_PIXELFORMAT_I0FL || format == SDL_PIXELFORMAT_I4FL) {
            प्रत्यागम SDL_COLORSPACE_HDR10;
        } अन्यथा {
            प्रत्यागम SDL_COLORSPACE_YUV_DEFAULT;
        }
    } अन्यथा यदि (SDL_ISPIXELFORMAT_FLOAT(format)) {
        प्रत्यागम SDL_COLORSPACE_SRGB_LINEAR;
    } अन्यथा यदि (SDL_ISPIXELFORMAT_10BIT(format)) {
        प्रत्यागम SDL_COLORSPACE_HDR10;
    } अन्यथा {
        प्रत्यागम SDL_COLORSPACE_RGB_DEFAULT;
    }
}

भिन्न SDL_sRGBtoLinear(भिन्न v)
{
    यदि (v <= 0.04045f) {
        v = (v / 12.92f);
    } अन्यथा {
        v = SDL_powf((v + 0.055f) / 1.055f, 2.4f);
    }
    प्रत्यागम v;
}

भिन्न SDL_sRGBfromLinear(भिन्न v)
{
    यदि (v <= 0.0031308f) {
        v = (v * 12.92f);
    } अन्यथा {
        v = (SDL_powf(v, 1.0f / 2.4f) * 1.055f - 0.055f);
    }
    प्रत्यागम v;
}

भिन्न SDL_PQtoNits(भिन्न v)
{
    ध्रुव भिन्न c1 = 0.8359375f;
    ध्रुव भिन्न c2 = 18.8515625f;
    ध्रुव भिन्न c3 = 18.6875f;
    ध्रुव भिन्न oo_m1 = 1.0f / 0.1593017578125f;
    ध्रुव भिन्न oo_m2 = 1.0f / 78.84375f;

    भिन्न अंक = SDL_max(SDL_powf(v, oo_m2) - c1, 0.0f);
    भिन्न den = c2 - c3 * SDL_powf(v, oo_m2);
    प्रत्यागम 10000.0f * SDL_powf(अंक / den, oo_m1);
}

भिन्न SDL_PQfromNits(भिन्न v)
{
    ध्रुव भिन्न c1 = 0.8359375f;
    ध्रुव भिन्न c2 = 18.8515625f;
    ध्रुव भिन्न c3 = 18.6875f;
    ध्रुव भिन्न m1 = 0.1593017578125f;
    ध्रुव भिन्न m2 = 78.84375f;

    भिन्न y = SDL_clamp(v / 10000.0f, 0.0f, 1.0f);
    भिन्न अंक = c1 + c2 * SDL_powf(y, m1);
    भिन्न den = 1.0f + c3 * SDL_powf(y, m1);
    प्रत्यागम SDL_powf(अंक / den, m2);
}

/* This is a helpful tool for deriving these:
 * https://kdashg.github.io/misc/colors/from-coeffs.html
 */
स्थिर ध्रुव भिन्न mat_BT601_Limited_8bit[] = {
    -0.0627451017f, -0.501960814f, -0.501960814f, 0.0f, // offset
    1.1644f, 0.0000f, 1.5960f, 0.0f,                    // Rcoeff
    1.1644f, -0.3918f, -0.8130f, 0.0f,                  // Gcoeff
    1.1644f, 2.0172f, 0.0000f, 0.0f,                    // Bcoeff
};

स्थिर ध्रुव भिन्न mat_BT601_Full_8bit[] = {
    0.0f, -0.501960814f, -0.501960814f, 0.0f,           // offset
    1.0000f, 0.0000f, 1.4075f, 0.0f,                    // Rcoeff
    1.0000f, -0.3455f, -0.7169f, 0.0f,                  // Gcoeff
    1.0000f, 1.7790f, 0.0000f, 0.0f,                    // Bcoeff
};

स्थिर ध्रुव भिन्न mat_BT709_Limited_8bit[] = {
    -0.0627451017f, -0.501960814f, -0.501960814f, 0.0f, // offset
    1.1644f, 0.0000f, 1.7927f, 0.0f,                    // Rcoeff
    1.1644f, -0.2132f, -0.5329f, 0.0f,                  // Gcoeff
    1.1644f, 2.1124f, 0.0000f, 0.0f,                    // Bcoeff
};

स्थिर ध्रुव भिन्न mat_BT709_Full_8bit[] = {
    0.0f, -0.501960814f, -0.501960814f, 0.0f,           // offset
    1.0000f, 0.0000f, 1.5810f, 0.0f,                    // Rcoeff
    1.0000f, -0.1881f, -0.4700f, 0.0f,                  // Gcoeff
    1.0000f, 1.8629f, 0.0000f, 0.0f,                    // Bcoeff
};

स्थिर ध्रुव भिन्न mat_BT2020_Limited_10bit[] = {
    -0.062561095f, -0.500488759f, -0.500488759f, 0.0f,  // offset
    1.1678f, 0.0000f, 1.6836f, 0.0f,                    // Rcoeff
    1.1678f, -0.1879f, -0.6523f, 0.0f,                  // Gcoeff
    1.1678f, 2.1481f, 0.0000f, 0.0f,                    // Bcoeff
};

स्थिर ध्रुव भिन्न mat_BT2020_Full_10bit[] = {
    0.0f, -0.500488759f, -0.500488759f, 0.0f,           // offset
    1.0000f, 0.0000f, 1.4760f, 0.0f,                    // Rcoeff
    1.0000f, -0.1647f, -0.5719f, 0.0f,                  // Gcoeff
    1.0000f, 1.8832f, 0.0000f, 0.0f,                    // Bcoeff
};

स्थिर ध्रुव भिन्न *SDL_GetBT601ConversionMatrix( SDL_Colorspace colorspace )
{
    विकल्प (SDL_COLORSPACERANGE(colorspace)) {
    पक्ष SDL_COLOR_RANGE_LIMITED:
    पक्ष SDL_COLOR_RANGE_UNKNOWN:
        प्रत्यागम mat_BT601_Limited_8bit;
    पक्ष SDL_COLOR_RANGE_FULL:
        प्रत्यागम mat_BT601_Full_8bit;
    स्वभाव:
        भङ्ग;
    }
    प्रत्यागम रिक्त;
}

स्थिर ध्रुव भिन्न *SDL_GetBT709ConversionMatrix(SDL_Colorspace colorspace)
{
    विकल्प (SDL_COLORSPACERANGE(colorspace)) {
    पक्ष SDL_COLOR_RANGE_LIMITED:
    पक्ष SDL_COLOR_RANGE_UNKNOWN:
        प्रत्यागम mat_BT709_Limited_8bit;
    पक्ष SDL_COLOR_RANGE_FULL:
        प्रत्यागम mat_BT709_Full_8bit;
    स्वभाव:
        भङ्ग;
    }
    प्रत्यागम रिक्त;
}

स्थिर ध्रुव भिन्न *SDL_GetBT2020ConversionMatrix(SDL_Colorspace colorspace)
{
    विकल्प (SDL_COLORSPACERANGE(colorspace)) {
    पक्ष SDL_COLOR_RANGE_LIMITED:
    पक्ष SDL_COLOR_RANGE_UNKNOWN:
        प्रत्यागम mat_BT2020_Limited_10bit;
    पक्ष SDL_COLOR_RANGE_FULL:
        प्रत्यागम mat_BT2020_Full_10bit;
    स्वभाव:
        भङ्ग;
    }
    प्रत्यागम रिक्त;
}

ध्रुव भिन्न *SDL_GetYCbCRtoRGBConversionMatrix(SDL_Colorspace colorspace, पूर्णाङ्क w, पूर्णाङ्क h, पूर्णाङ्क bits_per_pixel)
{
    विकल्प (SDL_COLORSPACEMATRIX(colorspace)) {
    पक्ष SDL_MATRIX_COEFFICIENTS_BT601:
    पक्ष SDL_MATRIX_COEFFICIENTS_BT470BG:
        प्रत्यागम SDL_GetBT601ConversionMatrix(colorspace);

    पक्ष SDL_MATRIX_COEFFICIENTS_BT709:
        प्रत्यागम SDL_GetBT709ConversionMatrix(colorspace);

    पक्ष SDL_MATRIX_COEFFICIENTS_BT2020_NCL:
        प्रत्यागम SDL_GetBT2020ConversionMatrix(colorspace);

    पक्ष SDL_MATRIX_COEFFICIENTS_UNSPECIFIED:
        विकल्प (bits_per_pixel) {
        पक्ष 8:
            यदि (h <= YUV_SD_THRESHOLD) {
                प्रत्यागम SDL_GetBT601ConversionMatrix(colorspace);
            } अन्यथा {
                प्रत्यागम SDL_GetBT709ConversionMatrix(colorspace);
            }
        पक्ष 10:
        पक्ष 16:
            प्रत्यागम SDL_GetBT2020ConversionMatrix(colorspace);
        स्वभाव:
            भङ्ग;
        }
        भङ्ग;
    स्वभाव:
        भङ्ग;
    }
    प्रत्यागम रिक्त;
}

/* Conversion matrices generated using gamescope color helpers and the primaries definitions at:
    * https://www.itu.int/rec/T-REC-H.273-201612-S/en
    *
    * You can also generate these online using the RGB-XYZ matrix calculator, and then multiplying
    * XYZ_to_dst * src_to_XYZ to get the combined conversion matrix:
    * https://www.russellcottrell.com/photo/matrixCalculator.htm
    */
स्थिर ध्रुव भिन्न mat601to709[] = {
    0.939542f, 0.050181f, 0.010277f,
    0.017772f, 0.965793f, 0.016435f,
    -0.001622f, -0.004370f, 1.005991f,
};
स्थिर ध्रुव भिन्न mat601to2020[] = {
    0.595254f, 0.349314f, 0.055432f,
    0.081244f, 0.891503f, 0.027253f,
    0.015512f, 0.081912f, 0.902576f,
};
स्थिर ध्रुव भिन्न mat709to601[] = {
    1.065379f, -0.055401f, -0.009978f,
    -0.019633f, 1.036363f, -0.016731f,
    0.001632f, 0.004412f, 0.993956f,
};
स्थिर ध्रुव भिन्न mat709to2020[] = {
    0.627404f, 0.329283f, 0.043313f,
    0.069097f, 0.919541f, 0.011362f,
    0.016391f, 0.088013f, 0.895595f,
};
स्थिर ध्रुव भिन्न mat2020to601[] = {
    1.776133f, -0.687820f, -0.088313f,
    -0.161376f, 1.187315f, -0.025940f,
    -0.015881f, -0.095931f, 1.111812f,
};
स्थिर ध्रुव भिन्न mat2020to709[] = {
    1.660496f, -0.587656f, -0.072840f,
    -0.124547f, 1.132895f, -0.008348f,
    -0.018154f, -0.100597f, 1.118751f
};
स्थिर ध्रुव भिन्न matSMPTE431to709[] = {
    1.120713f, -0.234649f, 0.000000f,
    -0.038478f, 1.087034f, 0.000000f,
    -0.017967f, -0.082030f, 0.954576f,
};
स्थिर ध्रुव भिन्न matSMPTE431to2020[] = {
    0.689691f, 0.207169f, 0.041346f,
    0.041852f, 0.982426f, 0.010846f,
    -0.001107f, 0.018362f, 0.854914f,
};
स्थिर ध्रुव भिन्न matSMPTE432to709[] = {
    1.224940f, -0.224940f, -0.000000f,
    -0.042057f, 1.042057f, 0.000000f,
    -0.019638f, -0.078636f, 1.098273f,
};
स्थिर ध्रुव भिन्न matSMPTE432to2020[] = {
    0.753833f, 0.198597f, 0.047570f,
    0.045744f, 0.941777f, 0.012479f,
    -0.001210f, 0.017602f, 0.983609f,
};

ध्रुव भिन्न *SDL_GetColorPrimariesConversionMatrix(SDL_ColorPrimaries src, SDL_ColorPrimaries dst)
{
    विकल्प (dst) {
    पक्ष SDL_COLOR_PRIMARIES_BT601:
    पक्ष SDL_COLOR_PRIMARIES_SMPTE240:
        विकल्प (src) {
        पक्ष SDL_COLOR_PRIMARIES_BT709:
            प्रत्यागम mat709to601;
        पक्ष SDL_COLOR_PRIMARIES_BT2020:
            प्रत्यागम mat2020to601;
        स्वभाव:
            भङ्ग;
        }
        भङ्ग;
    पक्ष SDL_COLOR_PRIMARIES_BT709:
        विकल्प (src) {
        पक्ष SDL_COLOR_PRIMARIES_BT601:
        पक्ष SDL_COLOR_PRIMARIES_SMPTE240:
            प्रत्यागम mat601to709;
        पक्ष SDL_COLOR_PRIMARIES_BT2020:
            प्रत्यागम mat2020to709;
        पक्ष SDL_COLOR_PRIMARIES_SMPTE431:
            प्रत्यागम matSMPTE431to709;
        पक्ष SDL_COLOR_PRIMARIES_SMPTE432:
            प्रत्यागम matSMPTE432to709;
        स्वभाव:
            भङ्ग;
        }
        भङ्ग;
    पक्ष SDL_COLOR_PRIMARIES_BT2020:
        विकल्प (src) {
        पक्ष SDL_COLOR_PRIMARIES_BT601:
        पक्ष SDL_COLOR_PRIMARIES_SMPTE240:
            प्रत्यागम mat601to2020;
        पक्ष SDL_COLOR_PRIMARIES_BT709:
            प्रत्यागम mat709to2020;
        पक्ष SDL_COLOR_PRIMARIES_SMPTE431:
            प्रत्यागम matSMPTE431to2020;
        पक्ष SDL_COLOR_PRIMARIES_SMPTE432:
            प्रत्यागम matSMPTE432to2020;
        स्वभाव:
            भङ्ग;
        }
        भङ्ग;
    स्वभाव:
        भङ्ग;
    }
    प्रत्यागम रिक्त;
}

शून्य SDL_ConvertColorPrimaries(भिन्न *fR, भिन्न *fG, भिन्न *fB, ध्रुव भिन्न *matrix)
{
    भिन्न v[3];

    v[0] = *fR;
    v[1] = *fG;
    v[2] = *fB;

    *fR = matrix[0 * 3 + 0] * v[0] + matrix[0 * 3 + 1] * v[1] + matrix[0 * 3 + 2] * v[2];
    *fG = matrix[1 * 3 + 0] * v[0] + matrix[1 * 3 + 1] * v[1] + matrix[1 * 3 + 2] * v[2];
    *fB = matrix[2 * 3 + 0] * v[0] + matrix[2 * 3 + 1] * v[1] + matrix[2 * 3 + 2] * v[2];
}

शून्य SDL_ConvertColor709to2020(भिन्न *fR, भिन्न *fG, भिन्न *fB)
{
    SDL_ConvertColorPrimaries(fR, fG, fB, mat709to2020);
}

SDL_Palette *SDL_CreatePalette(पूर्णाङ्क ncolors)
{
    SDL_Palette *palette;

    // Input validation
    CHECK_PARAM(ncolors < 1) {
        SDL_InvalidParamError("ncolors");
        प्रत्यागम रिक्त;
    }

    palette = (SDL_Palette *)SDL_malloc(परिमाण(*palette));
    यदि (!palette) {
        प्रत्यागम रिक्त;
    }
    palette->colors = (SDL_Color *)SDL_malloc(ncolors * परिमाण(*palette->colors));
    यदि (!palette->colors) {
        SDL_free(palette);
        प्रत्यागम रिक्त;
    }
    palette->ncolors = ncolors;
    palette->version = 1;
    palette->refcount = 1;

    SDL_memset(palette->colors, 0xFF, ncolors * परिमाण(*palette->colors));

    प्रत्यागम palette;
}

bool SDL_SetPaletteColors(SDL_Palette *palette, ध्रुव SDL_Color *colors, पूर्णाङ्क firstcolor, पूर्णाङ्क ncolors)
{
    // Verify the parameters
    यदि (!palette) {
        प्रत्यागम false;
    }
    यदि (ncolors > (palette->ncolors - firstcolor)) {
        ncolors = (palette->ncolors - firstcolor);
    }

    यदि (colors != (palette->colors + firstcolor)) {
        SDL_memcpy(palette->colors + firstcolor, colors,
                   ncolors * परिमाण(*colors));
    }
    ++palette->version;
    यदि (!palette->version) {
        palette->version = 1;
    }

    प्रत्यागम true;
}

शून्य SDL_DestroyPalette(SDL_Palette *palette)
{
    यदि (!palette) {
        प्रत्यागम;
    }
    यदि (--palette->refcount > 0) {
        प्रत्यागम;
    }
    SDL_free(palette->colors);
    SDL_free(palette);
}

/*
 * Calculate an 8-bit (3 red, 3 green, 2 blue) dithered palette of colors
 */
शून्य SDL_DitherPalette(SDL_Palette *palette)
{
    पूर्णाङ्क i;
    यदि (palette->ncolors != 256) {
        प्रत्यागम; // only 8bpp supported right now
    }

    प्रति (i = 0; i < palette->ncolors; i++) {
        पूर्णाङ्क r, g, b;
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
स्थिर Uint8 SDL_FindColor(ध्रुव SDL_Palette *pal, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    // Do colorspace distance matching
    unsigned पूर्णाङ्क smallest;
    unsigned पूर्णाङ्क distance;
    पूर्णाङ्क rd, gd, bd, ad;
    पूर्णाङ्क i;
    Uint8 pixelvalue = 0;

    smallest = ~0U;
    प्रति (i = 0; i < pal->ncolors; ++i) {
        rd = pal->colors[i].r - r;
        gd = pal->colors[i].g - g;
        bd = pal->colors[i].b - b;
        ad = pal->colors[i].a - a;
        distance = (rd * rd) + (gd * gd) + (bd * bd) + (ad * ad);
        यदि (distance < smallest) {
            pixelvalue = (Uint8)i;
            यदि (distance == 0) { // Perfect match!
                भङ्ग;
            }
            smallest = distance;
        }
    }
    प्रत्यागम pixelvalue;
}

Uint8 SDL_LookupRGBAColor(SDL_HashTable *palette_map, Uint32 pixelvalue, ध्रुव SDL_Palette *pal)
{
    Uint8 color_index = 0;
    यदि (pal) {
        ध्रुव शून्य *मूल्य;
        यदि (SDL_FindInHashTable(palette_map, (ध्रुव शून्य *)(uintptr_t)pixelvalue, &मूल्य)) {
            color_index = (Uint8)(uintptr_t)मूल्य;
        } अन्यथा {
            Uint8 r = (Uint8)((pixelvalue >> 24) & 0xFF);
            Uint8 g = (Uint8)((pixelvalue >> 16) & 0xFF);
            Uint8 b = (Uint8)((pixelvalue >>  8) & 0xFF);
            Uint8 a = (Uint8)((pixelvalue >>  0) & 0xFF);
            color_index = SDL_FindColor(pal, r, g, b, a);
            SDL_जोड़ो_Into_Hash_Table(palette_map, (ध्रुव शून्य *)(uintptr_t)pixelvalue, (ध्रुव शून्य *)(uintptr_t)color_index, true);
        }
    }
    प्रत्यागम color_index;
}

// Tell whether palette is opaque, and if it has an alpha_channel
शून्य SDL_DetectPalette(ध्रुव SDL_Palette *pal, bool *is_opaque, bool *has_alpha_channel)
{
    पूर्णाङ्क i;

    {
        bool all_opaque = true;
        प्रति (i = 0; i < pal->ncolors; i++) {
            Uint8 alpha_मूल्य = pal->colors[i].a;
            यदि (alpha_मूल्य != SDL_ALPHA_OPAQUE) {
                all_opaque = false;
                भङ्ग;
            }
        }

        यदि (all_opaque) {
            // Palette is opaque, with an alpha channel
            *is_opaque = true;
            *has_alpha_channel = true;
            प्रत्यागम;
        }
    }

    {
        bool all_transparent = true;
        प्रति (i = 0; i < pal->ncolors; i++) {
            Uint8 alpha_मूल्य = pal->colors[i].a;
            यदि (alpha_मूल्य != SDL_ALPHA_TRANSPARENT) {
                all_transparent = false;
                भङ्ग;
            }
        }

        यदि (all_transparent) {
            // Palette is opaque, without an alpha channel
            *is_opaque = true;
            *has_alpha_channel = false;
            प्रत्यागम;
        }
    }

    // Palette has alpha values
    *is_opaque = false;
    *has_alpha_channel = true;
}

// Find the opaque pixel value corresponding to an RGB triple
Uint32 SDL_MapRGB(ध्रुव SDL_PixelFormatDetails *format, ध्रुव SDL_Palette *palette, Uint8 r, Uint8 g, Uint8 b)
{
    CHECK_PARAM(!format) {
        SDL_InvalidParamError("format");
        प्रत्यागम 0;
    }

    यदि (SDL_ISPIXELFORMAT_INDEXED(format->format)) {
        CHECK_PARAM(!palette) {
            SDL_InvalidParamError("palette");
            प्रत्यागम 0;
        }
        प्रत्यागम SDL_FindColor(palette, r, g, b, SDL_ALPHA_OPAQUE);
    }

    यदि (SDL_ISPIXELFORMAT_10BIT(format->format)) {
        प्रत्यागम (((Uint32)SDL_expand_byte_10[r]) << format->Rshift) |
               (((Uint32)SDL_expand_byte_10[g]) << format->Gshift) |
               (((Uint32)SDL_expand_byte_10[b]) << format->Bshift) |
               format->Amask;
    } अन्यथा {
        प्रत्यागम ((Uint32)(r >> (8 - format->Rbits))) << format->Rshift |
               ((Uint32)(g >> (8 - format->Gbits))) << format->Gshift |
               ((Uint32)(b >> (8 - format->Bbits))) << format->Bshift |
               format->Amask;
    }
}

// Find the pixel value corresponding to an RGBA quadruple
Uint32 SDL_MapRGBA(ध्रुव SDL_PixelFormatDetails *format, ध्रुव SDL_Palette *palette, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    CHECK_PARAM(!format) {
        SDL_InvalidParamError("format");
        प्रत्यागम 0;
    }

    यदि (SDL_ISPIXELFORMAT_INDEXED(format->format)) {
        CHECK_PARAM(!palette) {
            SDL_InvalidParamError("palette");
            प्रत्यागम 0;
        }
        प्रत्यागम SDL_FindColor(palette, r, g, b, a);
    }

    यदि (SDL_ISPIXELFORMAT_10BIT(format->format)) {
        प्रत्यागम (((Uint32)SDL_expand_byte_10[r]) << format->Rshift) |
               (((Uint32)SDL_expand_byte_10[g]) << format->Gshift) |
               (((Uint32)SDL_expand_byte_10[b]) << format->Bshift) |
               ((((Uint32)(a >> (8 - format->Abits))) << format->Ashift) & format->Amask);
    } अन्यथा {
        प्रत्यागम ((Uint32)(r >> (8 - format->Rbits))) << format->Rshift |
               ((Uint32)(g >> (8 - format->Gbits))) << format->Gshift |
               ((Uint32)(b >> (8 - format->Bbits))) << format->Bshift |
               ((((Uint32)(a >> (8 - format->Abits))) << format->Ashift) & format->Amask);
    }
}

शून्य SDL_GetRGB(Uint32 pixelvalue, ध्रुव SDL_PixelFormatDetails *format, ध्रुव SDL_Palette *palette, Uint8 *r, Uint8 *g, Uint8 *b)
{
    Uint8 unused;

    यदि (!r) {
        r = &unused;
    }
    यदि (!g) {
        g = &unused;
    }
    यदि (!b) {
        b = &unused;
    }

    यदि (!format) {
        *r = *g = *b = 0;
        प्रत्यागम;
    }

    यदि (SDL_ISPIXELFORMAT_INDEXED(format->format)) {
        यदि (palette && pixelvalue < (unsigned)palette->ncolors) {
            *r = palette->colors[pixelvalue].r;
            *g = palette->colors[pixelvalue].g;
            *b = palette->colors[pixelvalue].b;
        } अन्यथा {
            *r = *g = *b = 0;
        }
        प्रत्यागम;
    }

    यदि (SDL_ISPIXELFORMAT_10BIT(format->format)) {
        unsigned v;
        v = (pixelvalue & format->Rmask) >> format->Rshift;
        *r = (Uint8)(v >> 2);
        v = (pixelvalue & format->Gmask) >> format->Gshift;
        *g = (Uint8)(v >> 2);
        v = (pixelvalue & format->Bmask) >> format->Bshift;
        *b = (Uint8)(v >> 2);
    } अन्यथा {
        unsigned v;
        v = (pixelvalue & format->Rmask) >> format->Rshift;
        *r = SDL_expand_byte[format->Rbits][v];
        v = (pixelvalue & format->Gmask) >> format->Gshift;
        *g = SDL_expand_byte[format->Gbits][v];
        v = (pixelvalue & format->Bmask) >> format->Bshift;
        *b = SDL_expand_byte[format->Bbits][v];
    }
}

शून्य SDL_GetRGBA(Uint32 pixelvalue, ध्रुव SDL_PixelFormatDetails *format, ध्रुव SDL_Palette *palette, Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a)
{
    Uint8 unused;

    यदि (!r) {
        r = &unused;
    }
    यदि (!g) {
        g = &unused;
    }
    यदि (!b) {
        b = &unused;
    }
    यदि (!a) {
        a = &unused;
    }

    यदि (!format) {
        *r = *g = *b = *a = 0;
        प्रत्यागम;
    }

    यदि (SDL_ISPIXELFORMAT_INDEXED(format->format)) {
        यदि (palette && pixelvalue < (unsigned)palette->ncolors) {
            *r = palette->colors[pixelvalue].r;
            *g = palette->colors[pixelvalue].g;
            *b = palette->colors[pixelvalue].b;
            *a = palette->colors[pixelvalue].a;
        } अन्यथा {
            *r = *g = *b = *a = 0;
        }
        प्रत्यागम;
    }

    यदि (SDL_ISPIXELFORMAT_10BIT(format->format)) {
        unsigned v;
        v = (pixelvalue & format->Rmask) >> format->Rshift;
        *r = (Uint8)(v >> 2);
        v = (pixelvalue & format->Gmask) >> format->Gshift;
        *g = (Uint8)(v >> 2);
        v = (pixelvalue & format->Bmask) >> format->Bshift;
        *b = (Uint8)(v >> 2);
        v = (pixelvalue & format->Amask) >> format->Ashift;
        *a = SDL_expand_byte[format->Abits][v];
    } अन्यथा {
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

bool SDL_IsSamePalette(ध्रुव SDL_Palette *src, ध्रुव SDL_Palette *dst)
{
    यदि (src->ncolors <= dst->ncolors) {
        // If an identical palette, no need to map
        यदि (src == dst ||
            (SDL_memcmp(src->colors, dst->colors,
                        src->ncolors * परिमाण(SDL_Color)) == 0)) {
            प्रत्यागम true;
        }
    }
    प्रत्यागम false;
}

// Map from Palette to Palette
स्थिर Uint8 *Map1to1(ध्रुव SDL_Palette *src, ध्रुव SDL_Palette *dst, पूर्णाङ्क *identical)
{
    Uint8 *map;
    पूर्णाङ्क i;

    यदि (SDL_IsSamePalette(src, dst)) {
        *identical = 1;
        प्रत्यागम रिक्त;
    }
    *identical = 0;

    map = (Uint8 *)SDL_calloc(256, परिमाण(Uint8));
    यदि (!map) {
        प्रत्यागम रिक्त;
    }
    प्रति (i = 0; i < src->ncolors; ++i) {
        map[i] = SDL_FindColor(dst,
                               src->colors[i].r, src->colors[i].g,
                               src->colors[i].b, src->colors[i].a);
    }
    प्रत्यागम map;
}

// Map from Palette to BitField
स्थिर Uint8 *Map1toN(ध्रुव SDL_Palette *pal, Uint8 Rmod, Uint8 Gmod, Uint8 Bmod, Uint8 Amod, ध्रुव SDL_PixelFormatDetails *dst)
{
    Uint8 *map;
    पूर्णाङ्क i;
    पूर्णाङ्क bpp;

    यदि (!pal) {
        SDL_SetError("src does not have a palette set");
        प्रत्यागम रिक्त;
    }

    bpp = ((SDL_BYTESPERPIXEL(dst->format) == 3) ? 4 : SDL_BYTESPERPIXEL(dst->format));
    map = (Uint8 *)SDL_calloc(256, bpp);
    यदि (!map) {
        प्रत्यागम रिक्त;
    }

    // We memory copy to the pixel map so the endianness is preserved
    प्रति (i = 0; i < pal->ncolors; ++i) {
        Uint8 R = (Uint8)((pal->colors[i].r * Rmod) / 255);
        Uint8 G = (Uint8)((pal->colors[i].g * Gmod) / 255);
        Uint8 B = (Uint8)((pal->colors[i].b * Bmod) / 255);
        Uint8 A = (Uint8)((pal->colors[i].a * Amod) / 255);
        ASSEMBLE_RGBA(&map[i * bpp], SDL_BYTESPERPIXEL(dst->format), dst, (Uint32)R,
                      (Uint32)G, (Uint32)B, (Uint32)A);
    }
    प्रत्यागम map;
}

bool SDL_ValidateMap(SDL_Surface *src, SDL_Surface *dst)
{
    SDL_BlitMap *map = &src->map;

    यदि (map->info.dst_fmt != dst->fmt ||
        map->info.dst_pal != dst->palette ||
        (dst->palette &&
         map->dst_palette_version != dst->palette->version) ||
        (src->palette &&
         map->src_palette_version != src->palette->version)) {
        यदि (!SDL_MapSurface(src, dst)) {
            प्रत्यागम false;
        }
#यदि 0
        // just here for debugging
        SDL_Log("src = %p src->flags = %08X map->info.flags = %08x\ndst = %p dst->flags = %08X dst->map.info.flags = %08X\nmap->blit = %p",
            src, dst->flags, map->info.flags, dst, dst->flags,
            dst->map.info.flags, map->blit);
#endif
    } अन्यथा {
        map->info.dst_surface = dst;
    }
    प्रत्यागम true;
}

शून्य SDL_InvalidateMap(SDL_BlitMap *map)
{
    map->info.dst_fmt = रिक्त;
    map->info.dst_pal = रिक्त;
    map->src_palette_version = 0;
    map->dst_palette_version = 0;
    यदि (map->info.table) {
        SDL_free(map->info.table);
        map->info.table = रिक्त;
    }
    यदि (map->info.palette_map) {
        SDL_DestroyHashTable(map->info.palette_map);
        map->info.palette_map = रिक्त;
    }
}

bool SDL_MapSurface(SDL_Surface *src, SDL_Surface *dst)
{
    ध्रुव SDL_PixelFormatDetails *srcfmt;
    ध्रुव SDL_Palette *srcpal;
    ध्रुव SDL_PixelFormatDetails *dstfmt;
    ध्रुव SDL_Palette *dstpal;
    SDL_BlitMap *map;

    // Clear out any previous mapping
    map = &src->map;
#ifdef SDL_HAVE_RLE
    यदि (src->internal_flags & SDL_INTERNAL_SURFACE_RLEACCEL) {
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
    यदि (SDL_ISPIXELFORMAT_INDEXED(srcfmt->format)) {
        यदि (SDL_ISPIXELFORMAT_INDEXED(dstfmt->format)) {
            // Palette --> Palette
            यदि (srcpal && dstpal) {
                map->info.table = Map1to1(srcpal, dstpal, &map->identity);
            } अन्यथा {
                map->identity = 1;
            }
            यदि (!map->identity) {
                यदि (!map->info.table) {
                    प्रत्यागम false;
                }
            }
            यदि (srcfmt->bits_per_pixel != dstfmt->bits_per_pixel) {
                map->identity = 0;
            }
        } अन्यथा {
            // Palette --> BitField
            map->info.table =
                Map1toN(srcpal, src->map.info.r, src->map.info.g,
                        src->map.info.b, src->map.info.a, dstfmt);
            यदि (!map->info.table) {
                प्रत्यागम false;
            }
        }
    } अन्यथा {
        यदि (SDL_ISPIXELFORMAT_INDEXED(dstfmt->format)) {
            // BitField --> Palette
            map->info.palette_map = SDL_CreateHashTable(0, false, SDL_HashID, SDL_कुंजी_Match_ID, रिक्त, रिक्त);
        } अन्यथा {
            // BitField --> BitField
            यदि (srcfmt == dstfmt) {
                map->identity = 1;
            }
        }
    }

    यदि (dstpal) {
        map->dst_palette_version = dstpal->version;
    } अन्यथा {
        map->dst_palette_version = 0;
    }

    यदि (srcpal) {
        map->src_palette_version = srcpal->version;
    } अन्यथा {
        map->src_palette_version = 0;
    }

    // Choose your blitters wisely
    प्रत्यागम SDL_CalculateBlit(src, dst);
}


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

#ಆದರೆ defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ಅನ್ತರ್ಭಾವ "SDL_windowsvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_windowsevents.h"
#ಅನ್ತರ್ಭಾವ "SDL_windowsrawinput.h"

#ಅನ್ತರ್ಭಾವ "../SDL_video_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"
#ಅನ್ತರ್ಭಾವ "../../joystick/usb_ids.h"
#ಅನ್ತರ್ಭಾವ "../../core/windows/SDL_windows.h" // for checking windows version

#ವ್ಯಾಖ್ಯಾನಿಸು RIFF_FOURCC(c0, c1, c2, c3)                 \
    ((DWORD)(BYTE)(c0) | ((DWORD)(BYTE)(c1) << 8) | \
     ((DWORD)(BYTE)(c2) << 16) | ((DWORD)(BYTE)(c3) << 24))

#ವ್ಯಾಖ್ಯಾನಿಸು ANI_FLAG_ICON 0x1

#ಸೂಚನೆ pack(ತಳ್ಳು, 1)

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    BYTE b_ಅಗಲ;
    BYTE b_ಎತ್ತರ;
    BYTE b_Color_ಎಣಿಕೆ;
    BYTE bReserved;
    ಶಬ್ದ xHotspot;
    ಶಬ್ದ yHotspot;
    DWORD dw_Image_ಗಾತ್ರ;
    DWORD dw_Image_ಸ್ಥಾನಾಂತರ;
} CURSORICONFILEDIRENTRY;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    ಶಬ್ದ idReserved;
    ಶಬ್ದ idType;
    ಶಬ್ದ id_ಎಣಿಕೆ;
} CURSORICONFILEDIR;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    DWORD cbSizeof; // sizeof(ANIHEADER) = 36 bytes.
    DWORD ಚೌಕಟ್ಟುಗಳು;   // Number of frames in the frame list.
    DWORD ಹೆಜ್ಜೆಗಳು;    // Number of steps in the animation loop.
    DWORD ಅಗಲ;    //ಅಗಲ
    DWORD ಎತ್ತರ;   //ಎತ್ತರ
    DWORD bpp;      // bpp
    DWORD planes;   // Not used
    DWORD jif_ದರ;  // Default display rate, in jiffies (1/60s)
    DWORD fl;       // AF_ICON should be set. AF_SEQUENCE is optional
} ANIHEADER;

#ಸೂಚನೆ pack(ತೆಗೆ)

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ CachedCursor
{
    ದಶಮಾಂಶ scale;
    HCURSOR cursor;
    ರಚನೆ CachedCursor *ಮುಂದಿನ;
} CachedCursor;

ರಚನೆ SDL_Cursor_ದತ್ತಾಂಶ
{
    HCURSOR cursor;

    CachedCursor *cache;
    ಪೂರ್ಣಾಂಕ hot_x;
    ಪೂರ್ಣಾಂಕ hot_y;
    ಪೂರ್ಣಾಂಕ ಅಂಕೆ_ಚೌಕಟ್ಟುಗಳು;
    SDL_Cursor_ಚೌಕಟ್ಟು_Info ಚೌಕಟ್ಟುಗಳು[1];
};

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    Uint64 xs[5];
    Uint64 ys[5];
    Sint64 residual[2];
    Uint32 dpiscale;
    Uint32 dpidenom;
    ಪೂರ್ಣಾಂಕ ಕೊನೆಯ_ಗಂಟು;
    bool enhanced;
    bool dpiaware;
} WIN_Mouse_ದತ್ತಾಂಶ;

DWORD SDL_ಕೊನೆಯ_warp_ಸಮಯ = 0;
HCURSOR SDL_cursor = ಖಾಲಿ;
ಸ್ಥಿರ SDL_Cursor *SDL_blank_cursor = ಖಾಲಿ;
ಸ್ಥಿರ WIN_Mouse_ದತ್ತಾಂಶ WIN_system_scale_ದತ್ತಾಂಶ;

ಸ್ಥಿರ SDL_Cursor *WIN_Create_Cursor_And_ದತ್ತಾಂಶ(HCURSOR hcursor)
{
    ಆದರೆ (!hcursor) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, ಗಾತ್ರ(*cursor));
    ಆದರೆ (!cursor) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    SDL_Cursor_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = (SDL_Cursor_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(*ದತ್ತಾಂಶ));
    ಆದರೆ (!ದತ್ತಾಂಶ) {
        SDL_free(cursor);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ದತ್ತಾಂಶ->cursor = hcursor;
    cursor->ಆಂತರಿಕ = ದತ್ತಾಂಶ;
    ಹಿಂತಿರುಗಿ cursor;
}

ಸ್ಥಿರ SDL_Cursor *WIN_Create_Animated_Cursor_And_ದತ್ತಾಂಶ(SDL_Cursor_ಚೌಕಟ್ಟು_Info *ಚೌಕಟ್ಟುಗಳು, ಪೂರ್ಣಾಂಕ ಚೌಕಟ್ಟು_ಎಣಿಕೆ, ಪೂರ್ಣಾಂಕ hot_x, ಪೂರ್ಣಾಂಕ hot_y)
{
    // Dynamically generate cursors at the appropriate DPI
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, ಗಾತ್ರ(*cursor));
    ಆದರೆ (!cursor) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    SDL_Cursor_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = (SDL_Cursor_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(*ದತ್ತಾಂಶ) + (ಗಾತ್ರ(SDL_Cursor_ಚೌಕಟ್ಟು_Info) * (ಚೌಕಟ್ಟು_ಎಣಿಕೆ - 1)));
    ಆದರೆ (!ದತ್ತಾಂಶ) {
        SDL_free(cursor);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ದತ್ತಾಂಶ->hot_x = hot_x;
    ದತ್ತಾಂಶ->hot_y = hot_y;
    ದತ್ತಾಂಶ->ಅಂಕೆ_ಚೌಕಟ್ಟುಗಳು = ಚೌಕಟ್ಟು_ಎಣಿಕೆ;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಚೌಕಟ್ಟು_ಎಣಿಕೆ; ++i) {
        SDL_Surface *surface = ಚೌಕಟ್ಟುಗಳು[i].surface;
        ಆದರೆ (surface->flags & SDL_SURFACE_PREALLOCATED) {
            surface = SDL_DuplicateSurface(surface);
            ಆದರೆ (!surface) {
                ಆಗ (i > 0) {
                    --i;
                    SDL_DestroySurface(ದತ್ತಾಂಶ->ಚೌಕಟ್ಟುಗಳು[i].surface);
                }
                SDL_free(ದತ್ತಾಂಶ);
                SDL_free(cursor);
                ಹಿಂತಿರುಗಿ ಖಾಲಿ;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            ++surface->refcount;
        }
        ದತ್ತಾಂಶ->ಚೌಕಟ್ಟುಗಳು[i].surface = surface;
        ದತ್ತಾಂಶ->ಚೌಕಟ್ಟುಗಳು[i].duration = ಚೌಕಟ್ಟುಗಳು[i].duration;
    }
    cursor->ಆಂತರಿಕ = ದತ್ತಾಂಶ;
    ಹಿಂತಿರುಗಿ cursor;
}

ಸ್ಥಿರ bool Save_Chunk_ಗಾತ್ರ(SDL_IOStream* dst, Sint64 ಸ್ಥಾನಾಂತರ_2)
{
    Sint64 ಇಲ್ಲಿ = SDL_TellIO(dst);
    ಆದರೆ (ಇಲ್ಲಿ < 0) {
        ಹಿಂತಿರುಗಿ false;
    }
    ಆದರೆ (SDL_SeekIO(dst, ಸ್ಥಾನಾಂತರ_2, SDL_IO_SEEK_ಗಣ) < 0) {
        ಹಿಂತಿರುಗಿ false;
    }

    DWORD ಗಾತ್ರ_2 = (DWORD)(ಇಲ್ಲಿ - (ಸ್ಥಾನಾಂತರ_2 + ಗಾತ್ರ(DWORD)));
    ಆದರೆ (!SDL_WriteU32LE(dst, ಗಾತ್ರ_2)) {
        ಹಿಂತಿರುಗಿ false;
    }
    ಹಿಂತಿರುಗಿ SDL_SeekIO(dst, ಇಲ್ಲಿ, SDL_IO_SEEK_ಗಣ);
}

ಸ್ಥಿರ bool Fill_Icon_ನಮೂದು(CURSORICONFILEDIRENTRY *ನಮೂದು, SDL_Surface *surface, ಪೂರ್ಣಾಂಕ hot_x, ಪೂರ್ಣಾಂಕ hot_y, DWORD dw_Image_ಗಾತ್ರ, DWORD dw_Image_ಸ್ಥಾನಾಂತರ)
{
    ಆದರೆ (surface->props) {
        hot_x = (ಪೂರ್ಣಾಂಕ)SDL_Get_ಸಂಖ್ಯೆ_Property(surface->props, SDL_PROP_SURFACE_HOTSPOT_X_ಸಂಖ್ಯೆ, hot_x);
        hot_y = (ಪೂರ್ಣಾಂಕ)SDL_Get_ಸಂಖ್ಯೆ_Property(surface->props, SDL_PROP_SURFACE_HOTSPOT_Y_ಸಂಖ್ಯೆ, hot_y);
    }
    hot_x = SDL_clamp(hot_x, 0, surface->w - 1);
    hot_y = SDL_clamp(hot_y, 0, surface->h - 1);

    SDL_zerop(ನಮೂದು);
    ನಮೂದು->b_ಅಗಲ = surface->w < 256 ? surface->w : 0;  // 0 means a width of 256
    ನಮೂದು->b_ಎತ್ತರ = surface->h < 256 ? surface->h : 0; // 0 means a height of 256
    ನಮೂದು->xHotspot = hot_x;
    ನಮೂದು->yHotspot = hot_y;
    ನಮೂದು->dw_Image_ಗಾತ್ರ = dw_Image_ಗಾತ್ರ;
    ನಮೂದು->dw_Image_ಸ್ಥಾನಾಂತರ = dw_Image_ಸ್ಥಾನಾಂತರ;
    ಹಿಂತಿರುಗಿ true;
}

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SAVE_ICON_PNG

ಸ್ಥಿರ bool WriteIconSurface(SDL_IOStream *dst, SDL_Surface *surface)
{
    ಆದರೆ (!SDL_SavePNG_IO(surface, dst, false)) {
        ಹಿಂತಿರುಗಿ false;
    }

    // Image data offsets must be WORD aligned
    Sint64 ಸ್ಥಾನಾಂತರ_2 = SDL_TellIO(dst);
    ಆದರೆ (ಸ್ಥಾನಾಂತರ_2 & 1) {
        ಆದರೆ (!SDL_WriteU8(dst, 0)) {
            ಹಿಂತಿರುಗಿ false;
        }
    }
    ಹಿಂತಿರುಗಿ true;
}

#ಇಲ್ಲದಿದ್ದರೆ

/* For info on the expected mask format see:
 * https://devblogs.microsoft.com/oldnewthing/20101018-00/?p=12513
 */
ಸ್ಥಿರ ಶೂನ್ಯ *Create_Icon_ಮುಖವಾಡ(SDL_Surface *surface, size_t *ಮುಖವಾಡ_ಗಾತ್ರ)
{
    Uint8 *dst;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ w = (surface->w + 7) / 8;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ pad = (((w) % 4) ? (4 - ((w) % 4)) : 0);
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ pitch = (w + pad);
    ಸ್ಥಿರಾಂಕ size_t ಗಾತ್ರ_2 = pitch * surface->h;
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ masks[] = { 0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1 };

    ಶೂನ್ಯ *ಮುಖವಾಡ = SDL_malloc(ಗಾತ್ರ_2);
    ಆದರೆ (!ಮುಖವಾಡ) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    dst = (Uint8 *)ಮುಖವಾಡ;

    // Make the mask completely transparent.
    SDL_memset(dst, 0xff, ಗಾತ್ರ_2);
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ y = surface->h - 1; y >= 0; --y, dst += pitch) {
        ಗಾಗಿ (ಪೂರ್ಣಾಂಕ x = 0; x < surface->w; ++x) {
            Uint8 r, g, b, a;
            SDL_ReadSurfacePixel(surface, x, y, &r, &g, &b, &a);

            ಆದರೆ (a != 0) {
                // Reset bit of an opaque pixel.
                dst[x >> 3] &= ~masks[x & 7];
            }
        }
    }
    *ಮುಖವಾಡ_ಗಾತ್ರ = ಗಾತ್ರ_2;
    ಹಿಂತಿರುಗಿ ಮುಖವಾಡ;
}

ಸ್ಥಿರ bool WriteIconSurface(SDL_IOStream *dst, SDL_Surface *surface)
{
    SDL_Surface *ತಾತ್ಕಾಲಿಕ = ಖಾಲಿ;

    ಆದರೆ (surface->format != SDL_PIXELFORMAT_ARGB8888) {
        ತಾತ್ಕಾಲಿಕ = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        ಆದರೆ (!ತಾತ್ಕಾಲಿಕ) {
            ಹಿಂತಿರುಗಿ false;
        }
        surface = ತಾತ್ಕಾಲಿಕ;
    }

    // Cursor data is double height (DIB and mask), stored bottom-up
    bool ok = true;
    size_t ಮುಖವಾಡ_ಗಾತ್ರ = 0;
    ಶೂನ್ಯ *ಮುಖವಾಡ = Create_Icon_ಮುಖವಾಡ(surface, &ಮುಖವಾಡ_ಗಾತ್ರ);
    ಆದರೆ (!ಮುಖವಾಡ) {
        ok = false;
        ಹೋಗು ಮುಗಿದ;
    }

    BITMAPINFOHEADER bmih;
    SDL_zero(bmih);
    DWORD ಅಡ್ಡಸಾಲು_ಗಾತ್ರ = surface->w * 4;
    bmih.bi_ಗಾತ್ರ = ಗಾತ್ರ(BITMAPINFOHEADER);
    bmih.bi_ಅಗಲ = surface->w;
    bmih.bi_ಎತ್ತರ = surface->h * 2;
    bmih.biPlanes = 1;
    bmih.bi_ಬಿಟ್_ಎಣಿಕೆ = 32;
    bmih.biCompression = BI_RGB;
    bmih.bi_ಗಾತ್ರ_Image = (DWORD)(surface->h * ಅಡ್ಡಸಾಲು_ಗಾತ್ರ + ಮುಖವಾಡ_ಗಾತ್ರ);
    ok &= (SDL_WriteIO(dst, &bmih, ಗಾತ್ರ(bmih)) == ಗಾತ್ರ(bmih));

    ಸ್ಥಿರಾಂಕ Uint8 *pix = surface->pixels;
    pix += (surface->h - 1) * surface->pitch;
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < surface->h; ++i) {
        ok &= (SDL_WriteIO(dst, pix, ಅಡ್ಡಸಾಲು_ಗಾತ್ರ) == ಅಡ್ಡಸಾಲು_ಗಾತ್ರ);
        pix -= surface->pitch;
    }
    ok &= (SDL_WriteIO(dst, ಮುಖವಾಡ, ಮುಖವಾಡ_ಗಾತ್ರ) == ಮುಖವಾಡ_ಗಾತ್ರ);

ಮುಗಿದ:
    SDL_free(ಮುಖವಾಡ);
    SDL_DestroySurface(ತಾತ್ಕಾಲಿಕ);
    ಹಿಂತಿರುಗಿ ok;
}

#ಆದರೆ_ಅಂತ್ಯ // SAVE_ICON_PNG

ಸ್ಥಿರ bool Write_Icon_ಚೌಕಟ್ಟು(SDL_IOStream *dst, SDL_Surface *surface, ಪೂರ್ಣಾಂಕ hot_x, ಪೂರ್ಣಾಂಕ hot_y, ದಶಮಾಂಶ scale)
{
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SAVE_ಅಪವರ್ತ್ಯ_ICONS
    ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2 = 0;
    SDL_Surface **surfaces = SDL_GetSurfaceImages(surface, &ಎಣಿಕೆ_2);
    ಆದರೆ (!surfaces) {
        ಹಿಂತಿರುಗಿ false;
    }
#ಇಲ್ಲದಿದ್ದರೆ
    surface = SDL_GetSurfaceImage(surface, scale);
    ಆದರೆ (!surface) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಪೂರ್ಣಾಂಕ ಎಣಿಕೆ_2 = 1;
    SDL_Surface **surfaces = &surface;
#ಆದರೆ_ಅಂತ್ಯ

    // Raymond Chen has more insight into this format at:
    // https://devblogs.microsoft.com/oldnewthing/20101018-00/?p=12513
    bool ok = true;
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('i', 'c', 'o', 'n'));
    Sint64 icon_ಗಾತ್ರ_ಸ್ಥಾನಾಂತರ = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    Sint64 ತಳ_ಸ್ಥಾನಾಂತರ_2 = icon_ಗಾತ್ರ_ಸ್ಥಾನಾಂತರ + ಗಾತ್ರ(DWORD);

    CURSORICONFILEDIR dir;
    dir.idReserved = 0;
    dir.idType = 2; // Cursor
    dir.id_ಎಣಿಕೆ = ಎಣಿಕೆ_2;
    ok &= (SDL_WriteIO(dst, &dir, ಗಾತ್ರ(dir)) == ಗಾತ್ರ(dir));

    DWORD entries_ಗಾತ್ರ = ಎಣಿಕೆ_2 * ಗಾತ್ರ(CURSORICONFILEDIRENTRY);
    CURSORICONFILEDIRENTRY *entries = (CURSORICONFILEDIRENTRY *)SDL_malloc(entries_ಗಾತ್ರ);
    ಆದರೆ (!entries) {
        ok = false;
        ಹೋಗು ಮುಗಿದ;
    }
    ok &= (SDL_WriteIO(dst, entries, entries_ಗಾತ್ರ) == entries_ಗಾತ್ರ);

    Sint64 image_ಸ್ಥಾನಾಂತರ_2 = SDL_TellIO(dst);
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಎಣಿಕೆ_2; ++i) {
        ok &= WriteIconSurface(dst, surfaces[i]);

        Sint64 ಮುಂದಿನ_ಸ್ಥಾನಾಂತರ = SDL_TellIO(dst);
        DWORD dw_Image_ಗಾತ್ರ = (DWORD)(ಮುಂದಿನ_ಸ್ಥಾನಾಂತರ - image_ಸ್ಥಾನಾಂತರ_2);
        DWORD dw_Image_ಸ್ಥಾನಾಂತರ = (DWORD)(image_ಸ್ಥಾನಾಂತರ_2 - ತಳ_ಸ್ಥಾನಾಂತರ_2);

        ok &= Fill_Icon_ನಮೂದು(&entries[i], surfaces[i], hot_x, hot_y, dw_Image_ಗಾತ್ರ, dw_Image_ಸ್ಥಾನಾಂತರ);

        image_ಸ್ಥಾನಾಂತರ_2 = ಮುಂದಿನ_ಸ್ಥಾನಾಂತರ;
    }

    // Now that we have the icon entries filled out, rewrite them
    ok &= (SDL_SeekIO(dst, ತಳ_ಸ್ಥಾನಾಂತರ_2 + ಗಾತ್ರ(dir), SDL_IO_SEEK_ಗಣ) >= 0);
    ok &= (SDL_WriteIO(dst, entries, entries_ಗಾತ್ರ) == entries_ಗಾತ್ರ);
    ok &= (SDL_SeekIO(dst, image_ಸ್ಥಾನಾಂತರ_2, SDL_IO_SEEK_ಗಣ) >= 0);
    SDL_free(entries);

    ok &= Save_Chunk_ಗಾತ್ರ(dst, icon_ಗಾತ್ರ_ಸ್ಥಾನಾಂತರ);

ಮುಗಿದ:
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SAVE_ಅಪವರ್ತ್ಯ_ICONS
    SDL_free(surfaces);
#ಇಲ್ಲದಿದ್ದರೆ
    SDL_DestroySurface(surface);
#ಆದರೆ_ಅಂತ್ಯ
    ಹಿಂತಿರುಗಿ ok;
}

/* Windows doesn't have an API to easily create animated cursors from a sequence of images,
 * so we have to build an animated cursor resource file in memory and load it.
 */
ಸ್ಥಿರ HCURSOR WIN_Create_Animated_Cursor_ಆಂತರಿಕ(SDL_Cursor_ಚೌಕಟ್ಟು_Info *ಚೌಕಟ್ಟುಗಳು, ಪೂರ್ಣಾಂಕ ಚೌಕಟ್ಟು_ಎಣಿಕೆ, ಪೂರ್ಣಾಂಕ hot_x, ಪೂರ್ಣಾಂಕ hot_y, ದಶಮಾಂಶ scale)
{
    HCURSOR hcursor = ಖಾಲಿ;
    SDL_IOStream *dst = SDL_IOFromDynamicMem();
    ಆದರೆ (!dst) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    ಪೂರ್ಣಾಂಕ w = (ಪೂರ್ಣಾಂಕ)SDL_roundf(ಚೌಕಟ್ಟುಗಳು[0].surface->w * scale);
    ಪೂರ್ಣಾಂಕ h = (ಪೂರ್ಣಾಂಕ)SDL_roundf(ಚೌಕಟ್ಟುಗಳು[0].surface->h * scale);

    bool ok = true;
    // RIFF header
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('R', 'I', 'F', 'F'));
    Sint64 riff_ಗಾತ್ರ_ಸ್ಥಾನಾಂತರ = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('A', 'C', 'O', 'N'));

    // anih header chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('a', 'n', 'i', 'h'));
    ok &= SDL_WriteU32LE(dst, ಗಾತ್ರ(ANIHEADER));

    ANIHEADER anih;
    SDL_zero(anih);
    anih.cbSizeof = ಗಾತ್ರ(anih);
    anih.ಚೌಕಟ್ಟುಗಳು = ಚೌಕಟ್ಟು_ಎಣಿಕೆ;
    anih.ಹೆಜ್ಜೆಗಳು = ಚೌಕಟ್ಟು_ಎಣಿಕೆ;
    anih.jif_ದರ = 1;
    anih.fl = ANI_FLAG_ICON;
    ok &= (SDL_WriteIO(dst, &anih, ಗಾತ್ರ(anih)) == ಗಾತ್ರ(anih));

    // Rate chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('r', 'a', 't', 'e'));
    ok &= SDL_WriteU32LE(dst, ಗಾತ್ರ(DWORD) * ಚೌಕಟ್ಟು_ಎಣಿಕೆ);
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಚೌಕಟ್ಟು_ಎಣಿಕೆ; ++i) {
        // Animated Win32 cursors are in jiffy units, and one jiffy is 1/60 of a second.
        ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ WIN32_JIFFY = 1000.0 / 60.0;
        DWORD duration = (ಚೌಕಟ್ಟುಗಳು[i].duration ? SDL_lround(ಚೌಕಟ್ಟುಗಳು[i].duration / WIN32_JIFFY) : 0xFFFFFFFF);
        ok &= SDL_WriteU32LE(dst, duration);
    }

    // Frame list
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('L', 'I', 'S', 'T'));
    Sint64 ಚೌಕಟ್ಟು_list_ಗಾತ್ರ_ಸ್ಥಾನಾಂತರ = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('f', 'r', 'a', 'm'));

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ಚೌಕಟ್ಟು_ಎಣಿಕೆ; ++i) {
        ok &= Write_Icon_ಚೌಕಟ್ಟು(dst, ಚೌಕಟ್ಟುಗಳು[i].surface, hot_x, hot_y, scale);
    }
    ok &= Save_Chunk_ಗಾತ್ರ(dst, ಚೌಕಟ್ಟು_list_ಗಾತ್ರ_ಸ್ಥಾನಾಂತರ);

    // All done!
    ok &= Save_Chunk_ಗಾತ್ರ(dst, riff_ಗಾತ್ರ_ಸ್ಥಾನಾಂತರ);
    ಆದರೆ (!ok) {
        // The error has been set above
        ಹೋಗು ಮುಗಿದ;
    }

    BYTE *mem = (BYTE *)SDL_Get_ಸೂಚಕ_Property(SDL_GetIOProperties(dst), SDL_PROP_IOSTREAM_DYNAMIC_ಸ್ಮರಣೆ_ಸೂಚಕ, ಖಾಲಿ);
    DWORD ಗಾತ್ರ_2 = (DWORD)SDL_GetIOSize(dst);
    hcursor = (HCURSOR)CreateIconFromResourceEx(mem, ಗಾತ್ರ_2, FALSE, 0x00030000, w, h, 0);
    ಆದರೆ (!hcursor) {
        SDL_ಗಣ_Error("CreateIconFromResource failed");
    }

ಮುಗಿದ:
    SDL_CloseIO(dst);

    ಹಿಂತಿರುಗಿ hcursor;
}

ಸ್ಥಿರ SDL_Cursor *WIN_CreateCursor(SDL_Surface *surface, ಪೂರ್ಣಾಂಕ hot_x, ಪೂರ್ಣಾಂಕ hot_y)
{
    SDL_Cursor_ಚೌಕಟ್ಟು_Info ಚೌಕಟ್ಟು = { surface, 0 };
    ಹಿಂತಿರುಗಿ WIN_Create_Animated_Cursor_And_ದತ್ತಾಂಶ(&ಚೌಕಟ್ಟು, 1, hot_x, hot_y);
}

ಸ್ಥಿರ SDL_Cursor *WIN_CreateAnimatedCursor(SDL_Cursor_ಚೌಕಟ್ಟು_Info *ಚೌಕಟ್ಟುಗಳು, ಪೂರ್ಣಾಂಕ ಚೌಕಟ್ಟು_ಎಣಿಕೆ, ಪೂರ್ಣಾಂಕ hot_x, ಪೂರ್ಣಾಂಕ hot_y)
{
    ಹಿಂತಿರುಗಿ WIN_Create_Animated_Cursor_And_ದತ್ತಾಂಶ(ಚೌಕಟ್ಟುಗಳು, ಚೌಕಟ್ಟು_ಎಣಿಕೆ, hot_x, hot_y);
}

ಸ್ಥಿರ SDL_Cursor *WIN_CreateBlankCursor(ಶೂನ್ಯ)
{
    SDL_Cursor *cursor = ಖಾಲಿ;
    SDL_Surface *surface = SDL_CreateSurfaceZeroed(32, 32, SDL_PIXELFORMAT_ARGB8888);
    ಆದರೆ (surface) {
        cursor = WIN_CreateCursor(surface, 0, 0);
        SDL_DestroySurface(surface);
    }
    ಹಿಂತಿರುಗಿ cursor;
}

ಸ್ಥಿರ SDL_Cursor *WIN_CreateSystemCursor(SDL_SystemCursor id)
{
    LPCTSTR name;

    ಆಯ್ಕೆ (id) {
    ಪೂರ್ವನಿಯೋಜಿತ:
        SDL_assert(!"Unknown system cursor ID");
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_DEFAULT:
        name = IDC_ARROW;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ಪಠ್ಯ:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_VERTICAL_ಪಠ್ಯ:
        name = IDC_IBEAM;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_WAIT:
        name = IDC_WAIT;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_CROSSHAIR:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_CELL:
        name = IDC_CROSS;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ಪ್ರಗತಿ:
        name = IDC_APPSTARTING;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_NWSE_RESIZE:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_NW_RESIZE:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_SE_RESIZE:
        name = IDC_SIZENWSE;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_NESW_RESIZE:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_NE_RESIZE:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_SW_RESIZE:
        name = IDC_SIZENESW;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_EW_RESIZE:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_E_RESIZE:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_W_RESIZE:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ಲಂಬಸಾಲು_RESIZE:
        name = IDC_SIZEWE;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_NS_RESIZE:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_N_RESIZE:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_S_RESIZE:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ಅಡ್ಡಸಾಲು_RESIZE:
        name = IDC_SIZENS;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_MOVE:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ALL_SCROLL:
        name = IDC_SIZEALL;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_NOT_ALLOWED:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_NO_DROP:
        name = IDC_NO;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ಸೂಚಕ:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_CONTEXT_MENU:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ALIAS:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_COPY:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_GRAB:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_GRABBING:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ZOOM_ಒಳ:
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_ZOOM_ಹೊರಹೋಗು:
        name = IDC_HAND;
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_SYSTEM_CURSOR_HELP:
        name = IDC_HELP;
        ನಿಲ್ಲಿಸು;
    }
    ಹಿಂತಿರುಗಿ WIN_Create_Cursor_And_ದತ್ತಾಂಶ(ತುಂಬು_Cursor(ಖಾಲಿ, name));
}

ಸ್ಥಿರ SDL_Cursor *WIN_CreateDefaultCursor(ಶೂನ್ಯ)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    ಹಿಂತಿರುಗಿ WIN_CreateSystemCursor(id);
}

ಸ್ಥಿರ ಶೂನ್ಯ WIN_FreeCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = cursor->ಆಂತರಿಕ;

    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < ದತ್ತಾಂಶ->ಅಂಕೆ_ಚೌಕಟ್ಟುಗಳು; ++i) {
        SDL_DestroySurface(ದತ್ತಾಂಶ->ಚೌಕಟ್ಟುಗಳು[i].surface);
    }
    ಆಗ (ದತ್ತಾಂಶ->cache) {
        CachedCursor *ನಮೂದು = ದತ್ತಾಂಶ->cache;
        ದತ್ತಾಂಶ->cache = ನಮೂದು->ಮುಂದಿನ;
        ಆದರೆ (ನಮೂದು->cursor) {
            DestroyCursor(ನಮೂದು->cursor);
        }
        SDL_free(ನಮೂದು);
    }
    ಆದರೆ (ದತ್ತಾಂಶ->cursor) {
        DestroyCursor(ದತ್ತಾಂಶ->cursor);
    }
    SDL_free(ದತ್ತಾಂಶ);
    SDL_free(cursor);
}

ಸ್ಥಿರ HCURSOR GetCachedCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = cursor->ಆಂತರಿಕ;

    ದಶಮಾಂಶ scale = 1.0f;
    ಆದರೆ (SDL_GetHintBoolean(SDL_HINT_MOUSE_DPI_SCALE_CURSORS, false)) {
        scale = SDL_GetDisplayContentScale(SDL_Get_Display_For_ಕಿಟಕಿ(SDL_GetMouseFocus()));
        ಆದರೆ (scale == 0.0f) {
            scale = 1.0f;
        }
    }
    ಗಾಗಿ (CachedCursor *ನಮೂದು = ದತ್ತಾಂಶ->cache; ನಮೂದು; ನಮೂದು = ನಮೂದು->ಮುಂದಿನ) {
        ಆದರೆ (scale == ನಮೂದು->scale) {
            ಹಿಂತಿರುಗಿ ನಮೂದು->cursor;
        }
    }

    // Need to create a cursor for this content scale
    HCURSOR hcursor = WIN_Create_Animated_Cursor_ಆಂತರಿಕ(ದತ್ತಾಂಶ->ಚೌಕಟ್ಟುಗಳು, ದತ್ತಾಂಶ->ಅಂಕೆ_ಚೌಕಟ್ಟುಗಳು, ದತ್ತಾಂಶ->hot_x, ದತ್ತಾಂಶ->hot_y, scale);
    ಆದರೆ (!hcursor) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    CachedCursor *ನಮೂದು = (CachedCursor *)SDL_calloc(1, ಗಾತ್ರ(*ನಮೂದು));
    ಆದರೆ (!ನಮೂದು) {
        DestroyCursor(hcursor);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    ನಮೂದು->cursor = hcursor;
    ನಮೂದು->scale = scale;
    ನಮೂದು->ಮುಂದಿನ = ದತ್ತಾಂಶ->cache;
    ದತ್ತಾಂಶ->cache = ನಮೂದು;

    ಹಿಂತಿರುಗಿ hcursor;
}

ಸ್ಥಿರ bool WIN_ShowCursor(SDL_Cursor *cursor)
{
    ಆದರೆ (!cursor) {
        ಆದರೆ (GetSystemMetrics(SM_REMOTESESSION)) {
            // Use a blank cursor so we continue to get relative motion over RDP
            cursor = SDL_blank_cursor;
        }
    }
    ಆದರೆ (cursor) {
        SDL_Cursor_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = cursor->ಆಂತರಿಕ;
        ಆದರೆ (ದತ್ತಾಂಶ->ಅಂಕೆ_ಚೌಕಟ್ಟುಗಳು > 0) {
            SDL_cursor = GetCachedCursor(cursor);
        } ಇಲ್ಲದಿದ್ದರೆ {
            SDL_cursor = ದತ್ತಾಂಶ->cursor;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_cursor = ಖಾಲಿ;
    }
    ಆದರೆ (SDL_GetMouseFocus() != ಖಾಲಿ) {
        ಗಣ_Cursor(SDL_cursor);
    }
    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ WIN_ಗಣ_Cursor_Pos(ಪೂರ್ಣಾಂಕ x, ಪೂರ್ಣಾಂಕ y)
{
    // We need to jitter the value because otherwise Windows will occasionally inexplicably ignore the SetCursorPos() or SendInput()
    ಗಣ_Cursor_Pos(x, y);
    ಗಣ_Cursor_Pos(x + 1, y);
    ಗಣ_Cursor_Pos(x, y);

    // Flush any mouse motion prior to or associated with this warp
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _MSC_VER // We explicitly want to use GetTickCount(), not GetTickCount64()
#ಸೂಚನೆ warning(ತಳ್ಳು)
#ಸೂಚನೆ warning(disable : 28159)
#ಆದರೆ_ಅಂತ್ಯ
    SDL_ಕೊನೆಯ_warp_ಸಮಯ = Get_Tick_ಎಣಿಕೆ();
    ಆದರೆ (!SDL_ಕೊನೆಯ_warp_ಸಮಯ) {
        SDL_ಕೊನೆಯ_warp_ಸಮಯ = 1;
    }
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ _MSC_VER
#ಸೂಚನೆ warning(ತೆಗೆ)
#ಆದರೆ_ಅಂತ್ಯ
}

ಸ್ಥಿರ bool WIN_WarpMouse(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ದಶಮಾಂಶ x, ದಶಮಾಂಶ y)
{
    SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
    HWND hwnd = ದತ್ತಾಂಶ->hwnd;
    ಬಿಂದು_2 pt;

    // Don't warp the mouse while we're doing a modal interaction
    ಆದರೆ (ದತ್ತಾಂಶ->ಒಳ_title_click || ದತ್ತಾಂಶ->focus_click_pending) {
        ಹಿಂತಿರುಗಿ true;
    }

    pt.x = (ಪೂರ್ಣಾಂಕ)SDL_roundf(x);
    pt.y = (ಪೂರ್ಣಾಂಕ)SDL_roundf(y);
    Client_ಗಮ್ಯ_Screen(hwnd, &pt);
    WIN_ಗಣ_Cursor_Pos(pt.x, pt.y);

    // Send the exact mouse motion associated with this warp
    SDL_SendMouseMotion(0, ಕಿಟಕಿ, SDL_GLOBAL_MOUSE_ID, false, x, y);
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool WIN_WarpMouseGlobal(ದಶಮಾಂಶ x, ದಶಮಾಂಶ y)
{
    ಬಿಂದು_2 pt;

    pt.x = (ಪೂರ್ಣಾಂಕ)SDL_roundf(x);
    pt.y = (ಪೂರ್ಣಾಂಕ)SDL_roundf(y);
    ಗಣ_Cursor_Pos(pt.x, pt.y);
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool WIN_ಗಣ_Relative_Mouse_ಬಹುಲಕ(bool enabled)
{
    ಹಿಂತಿರುಗಿ WIN_ಗಣ_Raw_Mouse_Enabled(SDL_GetVideoDevice(), enabled);
}

ಸ್ಥಿರ bool WIN_CaptureMouse(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಆದರೆ (ಕಿಟಕಿ) {
        SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
        ಗಣ_Capture(ದತ್ತಾಂಶ->hwnd);
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_ಕಿಟಕಿ *focus_ಕಿಟಕಿ_2 = SDL_GetMouseFocus();

        ಆದರೆ (focus_ಕಿಟಕಿ_2) {
            SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = focus_ಕಿಟಕಿ_2->ಆಂತರಿಕ;
            ಆದರೆ (!ದತ್ತಾಂಶ->mouse_tracked) {
                SDL_ಗಣ_Mouse_Focus(ಖಾಲಿ);
            }
        }
        ReleaseCapture();
    }

    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ SDL_MouseButtonFlags WIN_GetGlobalMouseState(ದಶಮಾಂಶ *x, ದಶಮಾಂಶ *y)
{
    SDL_MouseButtonFlags ಫಲಿತಾಂಶ = 0;
    ಬಿಂದು_2 pt = { 0, 0 };
    bool ಅದಲುಬದಲು_Buttons = GetSystemMetrics(SM_SWAPBUTTON) != 0;

    GetCursorPos(&pt);
    *x = (ದಶಮಾಂಶ)pt.x;
    *y = (ದಶಮಾಂಶ)pt.y;

    ಫಲಿತಾಂಶ |= Get_Async_ಕೀಲಿ_State(!ಅದಲುಬದಲು_Buttons ? VK_LBUTTON : VK_RBUTTON) & 0x8000 ? SDL_BUTTON_LMASK : 0;
    ಫಲಿತಾಂಶ |= Get_Async_ಕೀಲಿ_State(!ಅದಲುಬದಲು_Buttons ? VK_RBUTTON : VK_LBUTTON) & 0x8000 ? SDL_BUTTON_RMASK : 0;
    ಫಲಿತಾಂಶ |= Get_Async_ಕೀಲಿ_State(VK_MBUTTON) & 0x8000 ? SDL_BUTTON_MMASK : 0;
    ಫಲಿತಾಂಶ |= Get_Async_ಕೀಲಿ_State(VK_XBUTTON1) & 0x8000 ? SDL_BUTTON_X1_ಮುಖವಾಡ : 0;
    ಫಲಿತಾಂಶ |= Get_Async_ಕೀಲಿ_State(VK_XBUTTON2) & 0x8000 ? SDL_BUTTON_X2_ಮುಖವಾಡ : 0;

    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

ಸ್ಥಿರ ಶೂನ್ಯ WIN_ApplySystemScale(ಶೂನ್ಯ *ಆಂತರಿಕ, Uint64 timestamp, SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, SDL_MouseID mouseID, ದಶಮಾಂಶ *x, ದಶಮಾಂಶ *y)
{
    ಆದರೆ (!ಆಂತರಿಕ) {
        ಹಿಂತಿರುಗಿ;
    }
    WIN_Mouse_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = (WIN_Mouse_ದತ್ತಾಂಶ *)ಆಂತರಿಕ;

    SDL_VideoDisplay *display = ಕಿಟಕಿ ? SDL_Get_Video_Display_For_ಕಿಟಕಿ(ಕಿಟಕಿ) : SDL_GetVideoDisplay(SDL_GetPrimaryDisplay());

    Sint64 ix = (Sint64)*x * 65536;
    Sint64 iy = (Sint64)*y * 65536;
    Uint32 dpi = display ? (Uint32)(display->content_scale * USER_DEFAULT_SCREEN_DPI) : USER_DEFAULT_SCREEN_DPI;

    ಆದರೆ (!ದತ್ತಾಂಶ->enhanced) { // early return if flat scale
        dpi = ದತ್ತಾಂಶ->dpiscale * (ದತ್ತಾಂಶ->dpiaware ? dpi : USER_DEFAULT_SCREEN_DPI);
        ix *= dpi;
        iy *= dpi;
        ix /= USER_DEFAULT_SCREEN_DPI;
        iy /= USER_DEFAULT_SCREEN_DPI;
        ix /= 32;
        iy /= 32;
        // data->residual[0] += ix;
        // data->residual[1] += iy;
        // ix = 65536 * (data->residual[0] / 65536);
        // iy = 65536 * (data->residual[1] / 65536);
        // data->residual[0] -= ix;
        // data->residual[1] -= iy;
        *x = (ದಶಮಾಂಶ)ix / 65536.0f;
        *y = (ದಶಮಾಂಶ)iy / 65536.0f;
        ಹಿಂತಿರುಗಿ;
    }

    Uint64 *xs = ದತ್ತಾಂಶ->xs;
    Uint64 *ys = ದತ್ತಾಂಶ->ys;
    Uint64 absx = SDL_abs(ix);
    Uint64 absy = SDL_abs(iy);
    Uint64 ವೇಗ = SDL_min(absx, absy) + (SDL_max(absx, absy) << 1); // super cursed approximation used by Windows
    ಆದರೆ (ವೇಗ == 0) {
        ಹಿಂತಿರುಗಿ;
    }

    ಪೂರ್ಣಾಂಕ i, j, k;
    ಗಾಗಿ (i = 1; i < 5; i++) {
        j = i;
        ಆದರೆ (ವೇಗ < xs[j]) {
            ನಿಲ್ಲಿಸು;
        }
    }
    i -= 1;
    j -= 1;
    k = ದತ್ತಾಂಶ->ಕೊನೆಯ_ಗಂಟು;
    ದತ್ತಾಂಶ->ಕೊನೆಯ_ಗಂಟು = j;

    Uint32 denom = ದತ್ತಾಂಶ->dpidenom;
    Sint64 scale = 0;
    Sint64 xdiff = xs[j+1] - xs[j];
    Sint64 ydiff = ys[j+1] - ys[j];
    ಆದರೆ (xdiff != 0) {
        Sint64 ಇಳಿಜಾರು = ydiff / xdiff;
        Sint64 inter = ಇಳಿಜಾರು * xs[i] - ys[i];
        scale += ಇಳಿಜಾರು - inter / ವೇಗ;
    }

    ಆದರೆ (j > k) {
        denom <<= 1;
        xdiff = xs[k+1] - xs[k];
        ydiff = ys[k+1] - ys[k];
        ಆದರೆ (xdiff != 0) {
            Sint64 ಇಳಿಜಾರು = ydiff / xdiff;
            Sint64 inter = ಇಳಿಜಾರು * xs[k] - ys[k];
            scale += ಇಳಿಜಾರು - inter / ವೇಗ;
        }
    }

    scale *= dpi;
    ix *= scale;
    iy *= scale;
    ix /= denom;
    iy /= denom;
    // data->residual[0] += ix;
    // data->residual[1] += iy;
    // ix = 65536 * (data->residual[0] / 65536);
    // iy = 65536 * (data->residual[1] / 65536);
    // data->residual[0] -= ix;
    // data->residual[1] -= iy;
    *x = (ದಶಮಾಂಶ)ix / 65536.0f;
    *y = (ದಶಮಾಂಶ)iy / 65536.0f;
}

ಶೂನ್ಯ WIN_InitMouse(SDL_VideoDevice *_this)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    mouse->CreateCursor = WIN_CreateCursor;
    mouse->CreateAnimatedCursor = WIN_CreateAnimatedCursor;
    mouse->CreateSystemCursor = WIN_CreateSystemCursor;
    mouse->ShowCursor = WIN_ShowCursor;
    mouse->FreeCursor = WIN_FreeCursor;
    mouse->WarpMouse = WIN_WarpMouse;
    mouse->WarpMouseGlobal = WIN_WarpMouseGlobal;
    mouse->ಗಣ_Relative_Mouse_ಬಹುಲಕ = WIN_ಗಣ_Relative_Mouse_ಬಹುಲಕ;
    mouse->CaptureMouse = WIN_CaptureMouse;
    mouse->GetGlobalMouseState = WIN_GetGlobalMouseState;
    mouse->ApplySystemScale = WIN_ApplySystemScale;
    mouse->system_scale_ದತ್ತಾಂಶ = &WIN_system_scale_ದತ್ತಾಂಶ;

    SDL_ಗಣ_Default_Cursor(WIN_CreateDefaultCursor());

    SDL_blank_cursor = WIN_CreateBlankCursor();

    WIN_UpdateMouseSystemScale();
}

ಶೂನ್ಯ WIN_QuitMouse(SDL_VideoDevice *_this)
{
    ಆದರೆ (SDL_blank_cursor) {
        WIN_FreeCursor(SDL_blank_cursor);
        SDL_blank_cursor = ಖಾಲಿ;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Read_Mouse_ವಕ್ರ(ಪೂರ್ಣಾಂಕ v, Uint64 xs[5], Uint64 ys[5])
{
    bool win8 = WIN_IsWindows8OrGreater();
    DWORD xbuff[10] = {
        0x00000000, 0,
        0x00006e15, 0,
        0x00014000, 0,
        0x0003dc29, 0,
        0x00280000, 0
    };
    DWORD ybuff[10] = {
        0x00000000, 0,
        win8 ? 0x000111fd : 0x00015eb8, 0,
        win8 ? 0x00042400 : 0x00054ccd, 0,
        win8 ? 0x0012fc00 : 0x00184ccd, 0,
        win8 ? 0x01bbc000 : 0x02380000, 0
    };
    DWORD xsize = ಗಾತ್ರ(xbuff);
    DWORD ysize = ಗಾತ್ರ(ybuff);
    HKEY open_handle;
    ಆದರೆ (Reg_Open_ಕೀಲಿ_Ex_W(HKEY_CURRENT_USER, L"Control Panel\\Mouse", 0, ಕೀಲಿ_READ, &open_handle) == ERROR_SUCCESS) {
        Reg_Query_ಮೌಲ್ಯ_Ex_W(open_handle, L"SmoothMouseXCurve", ಖಾಲಿ, ಖಾಲಿ, (BYTE*)xbuff, &xsize);
        Reg_Query_ಮೌಲ್ಯ_Ex_W(open_handle, L"SmoothMouseYCurve", ಖಾಲಿ, ಖಾಲಿ, (BYTE*)ybuff, &ysize);
        Reg_Close_ಕೀಲಿ(open_handle);
    }
    xs[0] = 0; // first node must always be origin
    ys[0] = 0; // first node must always be origin
    ಪೂರ್ಣಾಂಕ i;
    ಗಾಗಿ (i = 1; i < 5; i++) {
        xs[i] = (7 * (Uint64)xbuff[i * 2]);
        ys[i] = (v * (Uint64)ybuff[i * 2]) << 17;
    }
}

ಶೂನ್ಯ WIN_UpdateMouseSystemScale(ಶೂನ್ಯ)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    ಆದರೆ (mouse->ApplySystemScale == WIN_ApplySystemScale) {
        mouse->system_scale_ದತ್ತಾಂಶ = &WIN_system_scale_ದತ್ತಾಂಶ;
    }

    // always reinitialize to valid defaults, whether fetch was successful or not.
    WIN_Mouse_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = &WIN_system_scale_ದತ್ತಾಂಶ;
    ದತ್ತಾಂಶ->residual[0] = 0;
    ದತ್ತಾಂಶ->residual[1] = 0;
    ದತ್ತಾಂಶ->dpiscale = 32;
    ದತ್ತಾಂಶ->dpidenom = (10 * (WIN_IsWindows8OrGreater() ? 120 : 150)) << 16;
    ದತ್ತಾಂಶ->dpiaware = WIN_Is_ಪ್ರತಿ_Monitor_V2_DPIAware(SDL_GetVideoDevice());
    ದತ್ತಾಂಶ->enhanced = false;

    ಪೂರ್ಣಾಂಕ v = 10;
    ಆದರೆ (SystemParametersInfo(SPI_GETMOUSESPEED, 0, &v, 0)) {
        v = SDL_max(1, SDL_min(v, 20));
        ದತ್ತಾಂಶ->dpiscale = SDL_max(SDL_max(v, (v - 2) * 4), (v - 6) * 8);
    }

    ಪೂರ್ಣಾಂಕ params[3];
    ಆದರೆ (SystemParametersInfo(SPI_GETMOUSE, 0, &params, 0)) {
        ದತ್ತಾಂಶ->enhanced = params[2] ? true : false;
        ಆದರೆ (params[2]) {
            Read_Mouse_ವಕ್ರ(v, ದತ್ತಾಂಶ->xs, ದತ್ತಾಂಶ->ys);
        }
    }
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_WINDOWS

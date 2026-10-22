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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_windowsvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_windowsevents.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_windowsrawinput.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_video_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_mouse_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../joystick/usb_ids.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/windows/SDL_windows.h" // for checking windows version

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RIFF_FOURCC(c0, c1, c2, c3)                 \
    ((DWORD)(BYTE)(c0) | ((DWORD)(BYTE)(c1) << 8) | \
     ((DWORD)(BYTE)(c2) << 16) | ((DWORD)(BYTE)(c3) << 24))

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ANI_FLAG_ICON 0x1

#ਹਦਾਇਤ pack(ਧੱਕੋ, 1)

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    BYTE b_ਚੌੜਾਈ;
    BYTE b_ਉਚਾਈ;
    BYTE b_Color_ਗਿਣਤੀ;
    BYTE bReserved;
    ਸ਼ਬਦ_2 xHotspot;
    ਸ਼ਬਦ_2 yHotspot;
    DWORD dw_Image_ਮਾਪ;
    DWORD dw_Image_ਵਿੱਥ;
} CURSORICONFILEDIRENTRY;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    ਸ਼ਬਦ_2 idReserved;
    ਸ਼ਬਦ_2 idType;
    ਸ਼ਬਦ_2 id_ਗਿਣਤੀ;
} CURSORICONFILEDIR;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    DWORD cbSizeof; // sizeof(ANIHEADER) = 36 bytes.
    DWORD ਚੌਖਟੇ;   // Number of frames in the frame list.
    DWORD ਕਦਮਾਂ;    // Number of steps in the animation loop.
    DWORD ਚੌੜਾਈ;    //ਚੌੜਾਈ
    DWORD ਉਚਾਈ;   //ਉਚਾਈ
    DWORD bpp;      // bpp
    DWORD planes;   // Not used
    DWORD jif_ਦਰ;  // Default display rate, in jiffies (1/60s)
    DWORD fl;       // AF_ICON should be set. AF_SEQUENCE is optional
} ANIHEADER;

#ਹਦਾਇਤ pack(ਕੱਢੋ)

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ CachedCursor
{
    ਦਸ਼ਮਲਵ scale;
    HCURSOR cursor;
    ਬਣਤਰ CachedCursor *ਅਗਲਾ;
} CachedCursor;

ਬਣਤਰ SDL_Cursor_ਅੰਕੜੇ
{
    HCURSOR cursor;

    CachedCursor *cache;
    ਪੂਰਨ hot_x;
    ਪੂਰਨ hot_y;
    ਪੂਰਨ ਅੰਕ_ਚੌਖਟੇ;
    SDL_Cursor_ਚੌਖਟਾ_Info ਚੌਖਟੇ[1];
};

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    Uint64 xs[5];
    Uint64 ys[5];
    Sint64 residual[2];
    Uint32 dpiscale;
    Uint32 dpidenom;
    ਪੂਰਨ ਆਖਰੀ_ਗੰਢ;
    bool enhanced;
    bool dpiaware;
} WIN_Mouse_ਅੰਕੜੇ;

DWORD SDL_ਆਖਰੀ_warp_ਸਮਾਂ = 0;
HCURSOR SDL_cursor = ਨਿਰਾ;
ਸਥਿਰ SDL_Cursor *SDL_blank_cursor = ਨਿਰਾ;
ਸਥਿਰ WIN_Mouse_ਅੰਕੜੇ WIN_system_scale_ਅੰਕੜੇ;

ਸਥਿਰ SDL_Cursor *WIN_Create_Cursor_And_ਅੰਕੜੇ(HCURSOR hcursor)
{
    ਜੇ (!hcursor) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, ਆਕਾਰ(*cursor));
    ਜੇ (!cursor) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    SDL_Cursor_ਅੰਕੜੇ *ਅੰਕੜੇ = (SDL_Cursor_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(*ਅੰਕੜੇ));
    ਜੇ (!ਅੰਕੜੇ) {
        SDL_free(cursor);
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਅੰਕੜੇ->cursor = hcursor;
    cursor->ਅੰਦਰੂਨੀ = ਅੰਕੜੇ;
    ਵਾਪਸ cursor;
}

ਸਥਿਰ SDL_Cursor *WIN_Create_Animated_Cursor_And_ਅੰਕੜੇ(SDL_Cursor_ਚੌਖਟਾ_Info *ਚੌਖਟੇ, ਪੂਰਨ ਚੌਖਟਾ_ਗਿਣਤੀ, ਪੂਰਨ hot_x, ਪੂਰਨ hot_y)
{
    // Dynamically generate cursors at the appropriate DPI
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, ਆਕਾਰ(*cursor));
    ਜੇ (!cursor) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    SDL_Cursor_ਅੰਕੜੇ *ਅੰਕੜੇ = (SDL_Cursor_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(*ਅੰਕੜੇ) + (ਆਕਾਰ(SDL_Cursor_ਚੌਖਟਾ_Info) * (ਚੌਖਟਾ_ਗਿਣਤੀ - 1)));
    ਜੇ (!ਅੰਕੜੇ) {
        SDL_free(cursor);
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਅੰਕੜੇ->hot_x = hot_x;
    ਅੰਕੜੇ->hot_y = hot_y;
    ਅੰਕੜੇ->ਅੰਕ_ਚੌਖਟੇ = ਚੌਖਟਾ_ਗਿਣਤੀ;
    ਲਈ (ਪੂਰਨ i = 0; i < ਚੌਖਟਾ_ਗਿਣਤੀ; ++i) {
        SDL_Surface *surface = ਚੌਖਟੇ[i].surface;
        ਜੇ (surface->flags & SDL_SURFACE_PREALLOCATED) {
            surface = SDL_DuplicateSurface(surface);
            ਜੇ (!surface) {
                ਜਦੋਂ (i > 0) {
                    --i;
                    SDL_DestroySurface(ਅੰਕੜੇ->ਚੌਖਟੇ[i].surface);
                }
                SDL_free(ਅੰਕੜੇ);
                SDL_free(cursor);
                ਵਾਪਸ ਨਿਰਾ;
            }
        } ਨਹੀਂਤਾਂ {
            ++surface->refcount;
        }
        ਅੰਕੜੇ->ਚੌਖਟੇ[i].surface = surface;
        ਅੰਕੜੇ->ਚੌਖਟੇ[i].duration = ਚੌਖਟੇ[i].duration;
    }
    cursor->ਅੰਦਰੂਨੀ = ਅੰਕੜੇ;
    ਵਾਪਸ cursor;
}

ਸਥਿਰ bool Save_Chunk_ਮਾਪ(SDL_IOStream* dst, Sint64 ਵਿੱਥ_2)
{
    Sint64 ਇੱਥੇ = SDL_TellIO(dst);
    ਜੇ (ਇੱਥੇ < 0) {
        ਵਾਪਸ false;
    }
    ਜੇ (SDL_SeekIO(dst, ਵਿੱਥ_2, SDL_IO_SEEK_ਸੈੱਟ) < 0) {
        ਵਾਪਸ false;
    }

    DWORD ਮਾਪ = (DWORD)(ਇੱਥੇ - (ਵਿੱਥ_2 + ਆਕਾਰ(DWORD)));
    ਜੇ (!SDL_WriteU32LE(dst, ਮਾਪ)) {
        ਵਾਪਸ false;
    }
    ਵਾਪਸ SDL_SeekIO(dst, ਇੱਥੇ, SDL_IO_SEEK_ਸੈੱਟ);
}

ਸਥਿਰ bool Fill_Icon_ਇੰਦਰਾਜ(CURSORICONFILEDIRENTRY *ਇੰਦਰਾਜ, SDL_Surface *surface, ਪੂਰਨ hot_x, ਪੂਰਨ hot_y, DWORD dw_Image_ਮਾਪ, DWORD dw_Image_ਵਿੱਥ)
{
    ਜੇ (surface->props) {
        hot_x = (ਪੂਰਨ)SDL_Get_ਸੰਖਿਆ_Property(surface->props, SDL_PROP_SURFACE_HOTSPOT_X_ਸੰਖਿਆ, hot_x);
        hot_y = (ਪੂਰਨ)SDL_Get_ਸੰਖਿਆ_Property(surface->props, SDL_PROP_SURFACE_HOTSPOT_Y_ਸੰਖਿਆ, hot_y);
    }
    hot_x = SDL_clamp(hot_x, 0, surface->w - 1);
    hot_y = SDL_clamp(hot_y, 0, surface->h - 1);

    SDL_zerop(ਇੰਦਰਾਜ);
    ਇੰਦਰਾਜ->b_ਚੌੜਾਈ = surface->w < 256 ? surface->w : 0;  // 0 means a width of 256
    ਇੰਦਰਾਜ->b_ਉਚਾਈ = surface->h < 256 ? surface->h : 0; // 0 means a height of 256
    ਇੰਦਰਾਜ->xHotspot = hot_x;
    ਇੰਦਰਾਜ->yHotspot = hot_y;
    ਇੰਦਰਾਜ->dw_Image_ਮਾਪ = dw_Image_ਮਾਪ;
    ਇੰਦਰਾਜ->dw_Image_ਵਿੱਥ = dw_Image_ਵਿੱਥ;
    ਵਾਪਸ true;
}

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SAVE_ICON_PNG

ਸਥਿਰ bool WriteIconSurface(SDL_IOStream *dst, SDL_Surface *surface)
{
    ਜੇ (!SDL_SavePNG_IO(surface, dst, false)) {
        ਵਾਪਸ false;
    }

    // Image data offsets must be WORD aligned
    Sint64 ਵਿੱਥ_2 = SDL_TellIO(dst);
    ਜੇ (ਵਿੱਥ_2 & 1) {
        ਜੇ (!SDL_WriteU8(dst, 0)) {
            ਵਾਪਸ false;
        }
    }
    ਵਾਪਸ true;
}

#ਨਹੀਂਤਾਂ

/* For info on the expected mask format see:
 * https://devblogs.microsoft.com/oldnewthing/20101018-00/?p=12513
 */
ਸਥਿਰ ਖਾਲੀ *Create_Icon_ਨਕਾਬ(SDL_Surface *surface, size_t *ਨਕਾਬ_ਮਾਪ)
{
    Uint8 *dst;
    ਅਚਲ ਪੂਰਨ w = (surface->w + 7) / 8;
    ਅਚਲ ਪੂਰਨ pad = (((w) % 4) ? (4 - ((w) % 4)) : 0);
    ਅਚਲ ਪੂਰਨ pitch = (w + pad);
    ਅਚਲ size_t ਮਾਪ = pitch * surface->h;
    ਸਥਿਰ ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ masks[] = { 0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1 };

    ਖਾਲੀ *ਨਕਾਬ = SDL_malloc(ਮਾਪ);
    ਜੇ (!ਨਕਾਬ) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    dst = (Uint8 *)ਨਕਾਬ;

    // Make the mask completely transparent.
    SDL_memset(dst, 0xff, ਮਾਪ);
    ਲਈ (ਪੂਰਨ y = surface->h - 1; y >= 0; --y, dst += pitch) {
        ਲਈ (ਪੂਰਨ x = 0; x < surface->w; ++x) {
            Uint8 r, g, b, a;
            SDL_ReadSurfacePixel(surface, x, y, &r, &g, &b, &a);

            ਜੇ (a != 0) {
                // Reset bit of an opaque pixel.
                dst[x >> 3] &= ~masks[x & 7];
            }
        }
    }
    *ਨਕਾਬ_ਮਾਪ = ਮਾਪ;
    ਵਾਪਸ ਨਕਾਬ;
}

ਸਥਿਰ bool WriteIconSurface(SDL_IOStream *dst, SDL_Surface *surface)
{
    SDL_Surface *ਆਰਜ਼ੀ = ਨਿਰਾ;

    ਜੇ (surface->format != SDL_PIXELFORMAT_ARGB8888) {
        ਆਰਜ਼ੀ = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        ਜੇ (!ਆਰਜ਼ੀ) {
            ਵਾਪਸ false;
        }
        surface = ਆਰਜ਼ੀ;
    }

    // Cursor data is double height (DIB and mask), stored bottom-up
    bool ok = true;
    size_t ਨਕਾਬ_ਮਾਪ = 0;
    ਖਾਲੀ *ਨਕਾਬ = Create_Icon_ਨਕਾਬ(surface, &ਨਕਾਬ_ਮਾਪ);
    ਜੇ (!ਨਕਾਬ) {
        ok = false;
        ਜਾਓ ਪੂਰਾ;
    }

    BITMAPINFOHEADER bmih;
    SDL_zero(bmih);
    DWORD ਪੰਕਤੀ_ਮਾਪ = surface->w * 4;
    bmih.bi_ਮਾਪ = ਆਕਾਰ(BITMAPINFOHEADER);
    bmih.bi_ਚੌੜਾਈ = surface->w;
    bmih.bi_ਉਚਾਈ = surface->h * 2;
    bmih.biPlanes = 1;
    bmih.bi_ਦੋਆਧਾਰੀ_ਅੰਕ_ਗਿਣਤੀ = 32;
    bmih.biCompression = BI_RGB;
    bmih.bi_ਮਾਪ_Image = (DWORD)(surface->h * ਪੰਕਤੀ_ਮਾਪ + ਨਕਾਬ_ਮਾਪ);
    ok &= (SDL_WriteIO(dst, &bmih, ਆਕਾਰ(bmih)) == ਆਕਾਰ(bmih));

    ਅਚਲ Uint8 *pix = surface->pixels;
    pix += (surface->h - 1) * surface->pitch;
    ਲਈ (ਪੂਰਨ i = 0; i < surface->h; ++i) {
        ok &= (SDL_WriteIO(dst, pix, ਪੰਕਤੀ_ਮਾਪ) == ਪੰਕਤੀ_ਮਾਪ);
        pix -= surface->pitch;
    }
    ok &= (SDL_WriteIO(dst, ਨਕਾਬ, ਨਕਾਬ_ਮਾਪ) == ਨਕਾਬ_ਮਾਪ);

ਪੂਰਾ:
    SDL_free(ਨਕਾਬ);
    SDL_DestroySurface(ਆਰਜ਼ੀ);
    ਵਾਪਸ ok;
}

#ਜੇ_ਅੰਤ // SAVE_ICON_PNG

ਸਥਿਰ bool Write_Icon_ਚੌਖਟਾ(SDL_IOStream *dst, SDL_Surface *surface, ਪੂਰਨ hot_x, ਪੂਰਨ hot_y, ਦਸ਼ਮਲਵ scale)
{
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SAVE_ਗੁਣਜ_ICONS
    ਪੂਰਨ ਗਿਣਤੀ_2 = 0;
    SDL_Surface **surfaces = SDL_GetSurfaceImages(surface, &ਗਿਣਤੀ_2);
    ਜੇ (!surfaces) {
        ਵਾਪਸ false;
    }
#ਨਹੀਂਤਾਂ
    surface = SDL_GetSurfaceImage(surface, scale);
    ਜੇ (!surface) {
        ਵਾਪਸ false;
    }

    ਪੂਰਨ ਗਿਣਤੀ_2 = 1;
    SDL_Surface **surfaces = &surface;
#ਜੇ_ਅੰਤ

    // Raymond Chen has more insight into this format at:
    // https://devblogs.microsoft.com/oldnewthing/20101018-00/?p=12513
    bool ok = true;
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('i', 'c', 'o', 'n'));
    Sint64 icon_ਮਾਪ_ਵਿੱਥ = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    Sint64 ਅਧਾਰ_ਵਿੱਥ_2 = icon_ਮਾਪ_ਵਿੱਥ + ਆਕਾਰ(DWORD);

    CURSORICONFILEDIR dir;
    dir.idReserved = 0;
    dir.idType = 2; // Cursor
    dir.id_ਗਿਣਤੀ = ਗਿਣਤੀ_2;
    ok &= (SDL_WriteIO(dst, &dir, ਆਕਾਰ(dir)) == ਆਕਾਰ(dir));

    DWORD entries_ਮਾਪ = ਗਿਣਤੀ_2 * ਆਕਾਰ(CURSORICONFILEDIRENTRY);
    CURSORICONFILEDIRENTRY *entries = (CURSORICONFILEDIRENTRY *)SDL_malloc(entries_ਮਾਪ);
    ਜੇ (!entries) {
        ok = false;
        ਜਾਓ ਪੂਰਾ;
    }
    ok &= (SDL_WriteIO(dst, entries, entries_ਮਾਪ) == entries_ਮਾਪ);

    Sint64 image_ਵਿੱਥ_2 = SDL_TellIO(dst);
    ਲਈ (ਪੂਰਨ i = 0; i < ਗਿਣਤੀ_2; ++i) {
        ok &= WriteIconSurface(dst, surfaces[i]);

        Sint64 ਅਗਲਾ_ਵਿੱਥ = SDL_TellIO(dst);
        DWORD dw_Image_ਮਾਪ = (DWORD)(ਅਗਲਾ_ਵਿੱਥ - image_ਵਿੱਥ_2);
        DWORD dw_Image_ਵਿੱਥ = (DWORD)(image_ਵਿੱਥ_2 - ਅਧਾਰ_ਵਿੱਥ_2);

        ok &= Fill_Icon_ਇੰਦਰਾਜ(&entries[i], surfaces[i], hot_x, hot_y, dw_Image_ਮਾਪ, dw_Image_ਵਿੱਥ);

        image_ਵਿੱਥ_2 = ਅਗਲਾ_ਵਿੱਥ;
    }

    // Now that we have the icon entries filled out, rewrite them
    ok &= (SDL_SeekIO(dst, ਅਧਾਰ_ਵਿੱਥ_2 + ਆਕਾਰ(dir), SDL_IO_SEEK_ਸੈੱਟ) >= 0);
    ok &= (SDL_WriteIO(dst, entries, entries_ਮਾਪ) == entries_ਮਾਪ);
    ok &= (SDL_SeekIO(dst, image_ਵਿੱਥ_2, SDL_IO_SEEK_ਸੈੱਟ) >= 0);
    SDL_free(entries);

    ok &= Save_Chunk_ਮਾਪ(dst, icon_ਮਾਪ_ਵਿੱਥ);

ਪੂਰਾ:
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SAVE_ਗੁਣਜ_ICONS
    SDL_free(surfaces);
#ਨਹੀਂਤਾਂ
    SDL_DestroySurface(surface);
#ਜੇ_ਅੰਤ
    ਵਾਪਸ ok;
}

/* Windows doesn't have an API to easily create animated cursors from a sequence of images,
 * so we have to build an animated cursor resource file in memory and load it.
 */
ਸਥਿਰ HCURSOR WIN_Create_Animated_Cursor_ਅੰਦਰੂਨੀ(SDL_Cursor_ਚੌਖਟਾ_Info *ਚੌਖਟੇ, ਪੂਰਨ ਚੌਖਟਾ_ਗਿਣਤੀ, ਪੂਰਨ hot_x, ਪੂਰਨ hot_y, ਦਸ਼ਮਲਵ scale)
{
    HCURSOR hcursor = ਨਿਰਾ;
    SDL_IOStream *dst = SDL_IOFromDynamicMem();
    ਜੇ (!dst) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    ਪੂਰਨ w = (ਪੂਰਨ)SDL_roundf(ਚੌਖਟੇ[0].surface->w * scale);
    ਪੂਰਨ h = (ਪੂਰਨ)SDL_roundf(ਚੌਖਟੇ[0].surface->h * scale);

    bool ok = true;
    // RIFF header
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('R', 'I', 'F', 'F'));
    Sint64 riff_ਮਾਪ_ਵਿੱਥ = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('A', 'C', 'O', 'N'));

    // anih header chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('a', 'n', 'i', 'h'));
    ok &= SDL_WriteU32LE(dst, ਆਕਾਰ(ANIHEADER));

    ANIHEADER anih;
    SDL_zero(anih);
    anih.cbSizeof = ਆਕਾਰ(anih);
    anih.ਚੌਖਟੇ = ਚੌਖਟਾ_ਗਿਣਤੀ;
    anih.ਕਦਮਾਂ = ਚੌਖਟਾ_ਗਿਣਤੀ;
    anih.jif_ਦਰ = 1;
    anih.fl = ANI_FLAG_ICON;
    ok &= (SDL_WriteIO(dst, &anih, ਆਕਾਰ(anih)) == ਆਕਾਰ(anih));

    // Rate chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('r', 'a', 't', 'e'));
    ok &= SDL_WriteU32LE(dst, ਆਕਾਰ(DWORD) * ਚੌਖਟਾ_ਗਿਣਤੀ);
    ਲਈ (ਪੂਰਨ i = 0; i < ਚੌਖਟਾ_ਗਿਣਤੀ; ++i) {
        // Animated Win32 cursors are in jiffy units, and one jiffy is 1/60 of a second.
        ਅਚਲ ਦੁੱਗਣਾ WIN32_JIFFY = 1000.0 / 60.0;
        DWORD duration = (ਚੌਖਟੇ[i].duration ? SDL_lround(ਚੌਖਟੇ[i].duration / WIN32_JIFFY) : 0xFFFFFFFF);
        ok &= SDL_WriteU32LE(dst, duration);
    }

    // Frame list
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('L', 'I', 'S', 'T'));
    Sint64 ਚੌਖਟਾ_list_ਮਾਪ_ਵਿੱਥ = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('f', 'r', 'a', 'm'));

    ਲਈ (ਪੂਰਨ i = 0; i < ਚੌਖਟਾ_ਗਿਣਤੀ; ++i) {
        ok &= Write_Icon_ਚੌਖਟਾ(dst, ਚੌਖਟੇ[i].surface, hot_x, hot_y, scale);
    }
    ok &= Save_Chunk_ਮਾਪ(dst, ਚੌਖਟਾ_list_ਮਾਪ_ਵਿੱਥ);

    // All done!
    ok &= Save_Chunk_ਮਾਪ(dst, riff_ਮਾਪ_ਵਿੱਥ);
    ਜੇ (!ok) {
        // The error has been set above
        ਜਾਓ ਪੂਰਾ;
    }

    BYTE *mem = (BYTE *)SDL_Get_ਸੂਚਕ_Property(SDL_GetIOProperties(dst), SDL_PROP_IOSTREAM_DYNAMIC_ਸਮ੍ਰਿਤੀ_ਸੂਚਕ, ਨਿਰਾ);
    DWORD ਮਾਪ = (DWORD)SDL_GetIOSize(dst);
    hcursor = (HCURSOR)CreateIconFromResourceEx(mem, ਮਾਪ, FALSE, 0x00030000, w, h, 0);
    ਜੇ (!hcursor) {
        SDL_ਸੈੱਟ_Error("CreateIconFromResource failed");
    }

ਪੂਰਾ:
    SDL_CloseIO(dst);

    ਵਾਪਸ hcursor;
}

ਸਥਿਰ SDL_Cursor *WIN_CreateCursor(SDL_Surface *surface, ਪੂਰਨ hot_x, ਪੂਰਨ hot_y)
{
    SDL_Cursor_ਚੌਖਟਾ_Info ਚੌਖਟਾ = { surface, 0 };
    ਵਾਪਸ WIN_Create_Animated_Cursor_And_ਅੰਕੜੇ(&ਚੌਖਟਾ, 1, hot_x, hot_y);
}

ਸਥਿਰ SDL_Cursor *WIN_CreateAnimatedCursor(SDL_Cursor_ਚੌਖਟਾ_Info *ਚੌਖਟੇ, ਪੂਰਨ ਚੌਖਟਾ_ਗਿਣਤੀ, ਪੂਰਨ hot_x, ਪੂਰਨ hot_y)
{
    ਵਾਪਸ WIN_Create_Animated_Cursor_And_ਅੰਕੜੇ(ਚੌਖਟੇ, ਚੌਖਟਾ_ਗਿਣਤੀ, hot_x, hot_y);
}

ਸਥਿਰ SDL_Cursor *WIN_CreateBlankCursor(ਖਾਲੀ)
{
    SDL_Cursor *cursor = ਨਿਰਾ;
    SDL_Surface *surface = SDL_CreateSurfaceZeroed(32, 32, SDL_PIXELFORMAT_ARGB8888);
    ਜੇ (surface) {
        cursor = WIN_CreateCursor(surface, 0, 0);
        SDL_DestroySurface(surface);
    }
    ਵਾਪਸ cursor;
}

ਸਥਿਰ SDL_Cursor *WIN_CreateSystemCursor(SDL_SystemCursor id)
{
    LPCTSTR name;

    ਚੋਣ (id) {
    ਮੂਲ:
        SDL_assert(!"Unknown system cursor ID");
        ਵਾਪਸ ਨਿਰਾ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_DEFAULT:
        name = IDC_ARROW;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_ਪਾਠ:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_VERTICAL_ਪਾਠ:
        name = IDC_IBEAM;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_WAIT:
        name = IDC_WAIT;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_CROSSHAIR:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_CELL:
        name = IDC_CROSS;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_ਤਰੱਕੀ:
        name = IDC_APPSTARTING;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_NWSE_RESIZE:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_NW_RESIZE:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_SE_RESIZE:
        name = IDC_SIZENWSE;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_NESW_RESIZE:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_NE_RESIZE:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_SW_RESIZE:
        name = IDC_SIZENESW;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_EW_RESIZE:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_E_RESIZE:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_W_RESIZE:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_ਖਾਨਾ_RESIZE:
        name = IDC_SIZEWE;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_NS_RESIZE:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_N_RESIZE:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_S_RESIZE:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_ਪੰਕਤੀ_RESIZE:
        name = IDC_SIZENS;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_MOVE:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_ALL_SCROLL:
        name = IDC_SIZEALL;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_NOT_ALLOWED:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_NO_DROP:
        name = IDC_NO;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_ਸੂਚਕ:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_CONTEXT_MENU:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_ALIAS:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_COPY:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_GRAB:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_GRABBING:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_ZOOM_ਵਿੱਚ:
    ਹਾਲਤ SDL_SYSTEM_CURSOR_ZOOM_ਬਾਹਰਲਾ:
        name = IDC_HAND;
        ਰੋਕੋ;
    ਹਾਲਤ SDL_SYSTEM_CURSOR_HELP:
        name = IDC_HELP;
        ਰੋਕੋ;
    }
    ਵਾਪਸ WIN_Create_Cursor_And_ਅੰਕੜੇ(ਲੱਦੋ_Cursor(ਨਿਰਾ, name));
}

ਸਥਿਰ SDL_Cursor *WIN_CreateDefaultCursor(ਖਾਲੀ)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    ਵਾਪਸ WIN_CreateSystemCursor(id);
}

ਸਥਿਰ ਖਾਲੀ WIN_FreeCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_ਅੰਕੜੇ *ਅੰਕੜੇ = cursor->ਅੰਦਰੂਨੀ;

    ਲਈ (ਪੂਰਨ i = 0; i < ਅੰਕੜੇ->ਅੰਕ_ਚੌਖਟੇ; ++i) {
        SDL_DestroySurface(ਅੰਕੜੇ->ਚੌਖਟੇ[i].surface);
    }
    ਜਦੋਂ (ਅੰਕੜੇ->cache) {
        CachedCursor *ਇੰਦਰਾਜ = ਅੰਕੜੇ->cache;
        ਅੰਕੜੇ->cache = ਇੰਦਰਾਜ->ਅਗਲਾ;
        ਜੇ (ਇੰਦਰਾਜ->cursor) {
            DestroyCursor(ਇੰਦਰਾਜ->cursor);
        }
        SDL_free(ਇੰਦਰਾਜ);
    }
    ਜੇ (ਅੰਕੜੇ->cursor) {
        DestroyCursor(ਅੰਕੜੇ->cursor);
    }
    SDL_free(ਅੰਕੜੇ);
    SDL_free(cursor);
}

ਸਥਿਰ HCURSOR GetCachedCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_ਅੰਕੜੇ *ਅੰਕੜੇ = cursor->ਅੰਦਰੂਨੀ;

    ਦਸ਼ਮਲਵ scale = 1.0f;
    ਜੇ (SDL_GetHintBoolean(SDL_HINT_MOUSE_DPI_SCALE_CURSORS, false)) {
        scale = SDL_GetDisplayContentScale(SDL_Get_Display_For_ਖਿੜਕੀ(SDL_GetMouseFocus()));
        ਜੇ (scale == 0.0f) {
            scale = 1.0f;
        }
    }
    ਲਈ (CachedCursor *ਇੰਦਰਾਜ = ਅੰਕੜੇ->cache; ਇੰਦਰਾਜ; ਇੰਦਰਾਜ = ਇੰਦਰਾਜ->ਅਗਲਾ) {
        ਜੇ (scale == ਇੰਦਰਾਜ->scale) {
            ਵਾਪਸ ਇੰਦਰਾਜ->cursor;
        }
    }

    // Need to create a cursor for this content scale
    HCURSOR hcursor = WIN_Create_Animated_Cursor_ਅੰਦਰੂਨੀ(ਅੰਕੜੇ->ਚੌਖਟੇ, ਅੰਕੜੇ->ਅੰਕ_ਚੌਖਟੇ, ਅੰਕੜੇ->hot_x, ਅੰਕੜੇ->hot_y, scale);
    ਜੇ (!hcursor) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    CachedCursor *ਇੰਦਰਾਜ = (CachedCursor *)SDL_calloc(1, ਆਕਾਰ(*ਇੰਦਰਾਜ));
    ਜੇ (!ਇੰਦਰਾਜ) {
        DestroyCursor(hcursor);
        ਵਾਪਸ ਨਿਰਾ;
    }
    ਇੰਦਰਾਜ->cursor = hcursor;
    ਇੰਦਰਾਜ->scale = scale;
    ਇੰਦਰਾਜ->ਅਗਲਾ = ਅੰਕੜੇ->cache;
    ਅੰਕੜੇ->cache = ਇੰਦਰਾਜ;

    ਵਾਪਸ hcursor;
}

ਸਥਿਰ bool WIN_ShowCursor(SDL_Cursor *cursor)
{
    ਜੇ (!cursor) {
        ਜੇ (GetSystemMetrics(SM_REMOTESESSION)) {
            // Use a blank cursor so we continue to get relative motion over RDP
            cursor = SDL_blank_cursor;
        }
    }
    ਜੇ (cursor) {
        SDL_Cursor_ਅੰਕੜੇ *ਅੰਕੜੇ = cursor->ਅੰਦਰੂਨੀ;
        ਜੇ (ਅੰਕੜੇ->ਅੰਕ_ਚੌਖਟੇ > 0) {
            SDL_cursor = GetCachedCursor(cursor);
        } ਨਹੀਂਤਾਂ {
            SDL_cursor = ਅੰਕੜੇ->cursor;
        }
    } ਨਹੀਂਤਾਂ {
        SDL_cursor = ਨਿਰਾ;
    }
    ਜੇ (SDL_GetMouseFocus() != ਨਿਰਾ) {
        ਸੈੱਟ_Cursor(SDL_cursor);
    }
    ਵਾਪਸ true;
}

ਖਾਲੀ WIN_ਸੈੱਟ_Cursor_Pos(ਪੂਰਨ x, ਪੂਰਨ y)
{
    // We need to jitter the value because otherwise Windows will occasionally inexplicably ignore the SetCursorPos() or SendInput()
    ਸੈੱਟ_Cursor_Pos(x, y);
    ਸੈੱਟ_Cursor_Pos(x + 1, y);
    ਸੈੱਟ_Cursor_Pos(x, y);

    // Flush any mouse motion prior to or associated with this warp
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _MSC_VER // We explicitly want to use GetTickCount(), not GetTickCount64()
#ਹਦਾਇਤ warning(ਧੱਕੋ)
#ਹਦਾਇਤ warning(disable : 28159)
#ਜੇ_ਅੰਤ
    SDL_ਆਖਰੀ_warp_ਸਮਾਂ = Get_Tick_ਗਿਣਤੀ();
    ਜੇ (!SDL_ਆਖਰੀ_warp_ਸਮਾਂ) {
        SDL_ਆਖਰੀ_warp_ਸਮਾਂ = 1;
    }
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ _MSC_VER
#ਹਦਾਇਤ warning(ਕੱਢੋ)
#ਜੇ_ਅੰਤ
}

ਸਥਿਰ bool WIN_WarpMouse(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਦਸ਼ਮਲਵ x, ਦਸ਼ਮਲਵ y)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
    HWND hwnd = ਅੰਕੜੇ->hwnd;
    ਬਿੰਦੂ_2 pt;

    // Don't warp the mouse while we're doing a modal interaction
    ਜੇ (ਅੰਕੜੇ->ਵਿੱਚ_title_click || ਅੰਕੜੇ->focus_click_pending) {
        ਵਾਪਸ true;
    }

    pt.x = (ਪੂਰਨ)SDL_roundf(x);
    pt.y = (ਪੂਰਨ)SDL_roundf(y);
    Client_ਮੰਜ਼ਿਲ_Screen(hwnd, &pt);
    WIN_ਸੈੱਟ_Cursor_Pos(pt.x, pt.y);

    // Send the exact mouse motion associated with this warp
    SDL_SendMouseMotion(0, ਖਿੜਕੀ, SDL_GLOBAL_MOUSE_ID, false, x, y);
    ਵਾਪਸ true;
}

ਸਥਿਰ bool WIN_WarpMouseGlobal(ਦਸ਼ਮਲਵ x, ਦਸ਼ਮਲਵ y)
{
    ਬਿੰਦੂ_2 pt;

    pt.x = (ਪੂਰਨ)SDL_roundf(x);
    pt.y = (ਪੂਰਨ)SDL_roundf(y);
    ਸੈੱਟ_Cursor_Pos(pt.x, pt.y);
    ਵਾਪਸ true;
}

ਸਥਿਰ bool WIN_ਸੈੱਟ_Relative_Mouse_ਬਹੁਲਕ(bool enabled)
{
    ਵਾਪਸ WIN_ਸੈੱਟ_Raw_Mouse_Enabled(SDL_GetVideoDevice(), enabled);
}

ਸਥਿਰ bool WIN_CaptureMouse(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਜੇ (ਖਿੜਕੀ) {
        SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
        ਸੈੱਟ_Capture(ਅੰਕੜੇ->hwnd);
    } ਨਹੀਂਤਾਂ {
        SDL_ਖਿੜਕੀ *focus_ਖਿੜਕੀ_2 = SDL_GetMouseFocus();

        ਜੇ (focus_ਖਿੜਕੀ_2) {
            SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = focus_ਖਿੜਕੀ_2->ਅੰਦਰੂਨੀ;
            ਜੇ (!ਅੰਕੜੇ->mouse_tracked) {
                SDL_ਸੈੱਟ_Mouse_Focus(ਨਿਰਾ);
            }
        }
        ReleaseCapture();
    }

    ਵਾਪਸ true;
}

ਸਥਿਰ SDL_MouseButtonFlags WIN_GetGlobalMouseState(ਦਸ਼ਮਲਵ *x, ਦਸ਼ਮਲਵ *y)
{
    SDL_MouseButtonFlags ਨਤੀਜਾ = 0;
    ਬਿੰਦੂ_2 pt = { 0, 0 };
    bool ਅਦਲਾ_ਬਦਲੀ_Buttons = GetSystemMetrics(SM_SWAPBUTTON) != 0;

    GetCursorPos(&pt);
    *x = (ਦਸ਼ਮਲਵ)pt.x;
    *y = (ਦਸ਼ਮਲਵ)pt.y;

    ਨਤੀਜਾ |= Get_Async_ਕੁੰਜੀ_State(!ਅਦਲਾ_ਬਦਲੀ_Buttons ? VK_LBUTTON : VK_RBUTTON) & 0x8000 ? SDL_BUTTON_LMASK : 0;
    ਨਤੀਜਾ |= Get_Async_ਕੁੰਜੀ_State(!ਅਦਲਾ_ਬਦਲੀ_Buttons ? VK_RBUTTON : VK_LBUTTON) & 0x8000 ? SDL_BUTTON_RMASK : 0;
    ਨਤੀਜਾ |= Get_Async_ਕੁੰਜੀ_State(VK_MBUTTON) & 0x8000 ? SDL_BUTTON_MMASK : 0;
    ਨਤੀਜਾ |= Get_Async_ਕੁੰਜੀ_State(VK_XBUTTON1) & 0x8000 ? SDL_BUTTON_X1_ਨਕਾਬ : 0;
    ਨਤੀਜਾ |= Get_Async_ਕੁੰਜੀ_State(VK_XBUTTON2) & 0x8000 ? SDL_BUTTON_X2_ਨਕਾਬ : 0;

    ਵਾਪਸ ਨਤੀਜਾ;
}

ਸਥਿਰ ਖਾਲੀ WIN_ApplySystemScale(ਖਾਲੀ *ਅੰਦਰੂਨੀ, Uint64 timestamp, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_MouseID mouseID, ਦਸ਼ਮਲਵ *x, ਦਸ਼ਮਲਵ *y)
{
    ਜੇ (!ਅੰਦਰੂਨੀ) {
        ਵਾਪਸ;
    }
    WIN_Mouse_ਅੰਕੜੇ *ਅੰਕੜੇ = (WIN_Mouse_ਅੰਕੜੇ *)ਅੰਦਰੂਨੀ;

    SDL_VideoDisplay *display = ਖਿੜਕੀ ? SDL_Get_Video_Display_For_ਖਿੜਕੀ(ਖਿੜਕੀ) : SDL_GetVideoDisplay(SDL_GetPrimaryDisplay());

    Sint64 ix = (Sint64)*x * 65536;
    Sint64 iy = (Sint64)*y * 65536;
    Uint32 dpi = display ? (Uint32)(display->content_scale * USER_DEFAULT_SCREEN_DPI) : USER_DEFAULT_SCREEN_DPI;

    ਜੇ (!ਅੰਕੜੇ->enhanced) { // early return if flat scale
        dpi = ਅੰਕੜੇ->dpiscale * (ਅੰਕੜੇ->dpiaware ? dpi : USER_DEFAULT_SCREEN_DPI);
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
        *x = (ਦਸ਼ਮਲਵ)ix / 65536.0f;
        *y = (ਦਸ਼ਮਲਵ)iy / 65536.0f;
        ਵਾਪਸ;
    }

    Uint64 *xs = ਅੰਕੜੇ->xs;
    Uint64 *ys = ਅੰਕੜੇ->ys;
    Uint64 absx = SDL_abs(ix);
    Uint64 absy = SDL_abs(iy);
    Uint64 ਰਫਤਾਰ = SDL_min(absx, absy) + (SDL_max(absx, absy) << 1); // super cursed approximation used by Windows
    ਜੇ (ਰਫਤਾਰ == 0) {
        ਵਾਪਸ;
    }

    ਪੂਰਨ i, j, k;
    ਲਈ (i = 1; i < 5; i++) {
        j = i;
        ਜੇ (ਰਫਤਾਰ < xs[j]) {
            ਰੋਕੋ;
        }
    }
    i -= 1;
    j -= 1;
    k = ਅੰਕੜੇ->ਆਖਰੀ_ਗੰਢ;
    ਅੰਕੜੇ->ਆਖਰੀ_ਗੰਢ = j;

    Uint32 denom = ਅੰਕੜੇ->dpidenom;
    Sint64 scale = 0;
    Sint64 xdiff = xs[j+1] - xs[j];
    Sint64 ydiff = ys[j+1] - ys[j];
    ਜੇ (xdiff != 0) {
        Sint64 ਢਲਾਨ = ydiff / xdiff;
        Sint64 inter = ਢਲਾਨ * xs[i] - ys[i];
        scale += ਢਲਾਨ - inter / ਰਫਤਾਰ;
    }

    ਜੇ (j > k) {
        denom <<= 1;
        xdiff = xs[k+1] - xs[k];
        ydiff = ys[k+1] - ys[k];
        ਜੇ (xdiff != 0) {
            Sint64 ਢਲਾਨ = ydiff / xdiff;
            Sint64 inter = ਢਲਾਨ * xs[k] - ys[k];
            scale += ਢਲਾਨ - inter / ਰਫਤਾਰ;
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
    *x = (ਦਸ਼ਮਲਵ)ix / 65536.0f;
    *y = (ਦਸ਼ਮਲਵ)iy / 65536.0f;
}

ਖਾਲੀ WIN_InitMouse(SDL_VideoDevice *_this)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    mouse->CreateCursor = WIN_CreateCursor;
    mouse->CreateAnimatedCursor = WIN_CreateAnimatedCursor;
    mouse->CreateSystemCursor = WIN_CreateSystemCursor;
    mouse->ShowCursor = WIN_ShowCursor;
    mouse->FreeCursor = WIN_FreeCursor;
    mouse->WarpMouse = WIN_WarpMouse;
    mouse->WarpMouseGlobal = WIN_WarpMouseGlobal;
    mouse->ਸੈੱਟ_Relative_Mouse_ਬਹੁਲਕ = WIN_ਸੈੱਟ_Relative_Mouse_ਬਹੁਲਕ;
    mouse->CaptureMouse = WIN_CaptureMouse;
    mouse->GetGlobalMouseState = WIN_GetGlobalMouseState;
    mouse->ApplySystemScale = WIN_ApplySystemScale;
    mouse->system_scale_ਅੰਕੜੇ = &WIN_system_scale_ਅੰਕੜੇ;

    SDL_ਸੈੱਟ_Default_Cursor(WIN_CreateDefaultCursor());

    SDL_blank_cursor = WIN_CreateBlankCursor();

    WIN_UpdateMouseSystemScale();
}

ਖਾਲੀ WIN_QuitMouse(SDL_VideoDevice *_this)
{
    ਜੇ (SDL_blank_cursor) {
        WIN_FreeCursor(SDL_blank_cursor);
        SDL_blank_cursor = ਨਿਰਾ;
    }
}

ਸਥਿਰ ਖਾਲੀ Read_Mouse_ਵਕਰ(ਪੂਰਨ v, Uint64 xs[5], Uint64 ys[5])
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
    DWORD xsize = ਆਕਾਰ(xbuff);
    DWORD ysize = ਆਕਾਰ(ybuff);
    HKEY open_handle;
    ਜੇ (Reg_Open_ਕੁੰਜੀ_Ex_W(HKEY_CURRENT_USER, L"Control Panel\\Mouse", 0, ਕੁੰਜੀ_READ, &open_handle) == ERROR_SUCCESS) {
        Reg_Query_ਮੁੱਲ_Ex_W(open_handle, L"SmoothMouseXCurve", ਨਿਰਾ, ਨਿਰਾ, (BYTE*)xbuff, &xsize);
        Reg_Query_ਮੁੱਲ_Ex_W(open_handle, L"SmoothMouseYCurve", ਨਿਰਾ, ਨਿਰਾ, (BYTE*)ybuff, &ysize);
        Reg_Close_ਕੁੰਜੀ(open_handle);
    }
    xs[0] = 0; // first node must always be origin
    ys[0] = 0; // first node must always be origin
    ਪੂਰਨ i;
    ਲਈ (i = 1; i < 5; i++) {
        xs[i] = (7 * (Uint64)xbuff[i * 2]);
        ys[i] = (v * (Uint64)ybuff[i * 2]) << 17;
    }
}

ਖਾਲੀ WIN_UpdateMouseSystemScale(ਖਾਲੀ)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    ਜੇ (mouse->ApplySystemScale == WIN_ApplySystemScale) {
        mouse->system_scale_ਅੰਕੜੇ = &WIN_system_scale_ਅੰਕੜੇ;
    }

    // always reinitialize to valid defaults, whether fetch was successful or not.
    WIN_Mouse_ਅੰਕੜੇ *ਅੰਕੜੇ = &WIN_system_scale_ਅੰਕੜੇ;
    ਅੰਕੜੇ->residual[0] = 0;
    ਅੰਕੜੇ->residual[1] = 0;
    ਅੰਕੜੇ->dpiscale = 32;
    ਅੰਕੜੇ->dpidenom = (10 * (WIN_IsWindows8OrGreater() ? 120 : 150)) << 16;
    ਅੰਕੜੇ->dpiaware = WIN_Is_ਪ੍ਰਤੀ_Monitor_V2_DPIAware(SDL_GetVideoDevice());
    ਅੰਕੜੇ->enhanced = false;

    ਪੂਰਨ v = 10;
    ਜੇ (SystemParametersInfo(SPI_GETMOUSESPEED, 0, &v, 0)) {
        v = SDL_max(1, SDL_min(v, 20));
        ਅੰਕੜੇ->dpiscale = SDL_max(SDL_max(v, (v - 2) * 4), (v - 6) * 8);
    }

    ਪੂਰਨ params[3];
    ਜੇ (SystemParametersInfo(SPI_GETMOUSE, 0, &params, 0)) {
        ਅੰਕੜੇ->enhanced = params[2] ? true : false;
        ਜੇ (params[2]) {
            Read_Mouse_ਵਕਰ(v, ਅੰਕੜੇ->xs, ਅੰਕੜੇ->ys);
        }
    }
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_WINDOWS

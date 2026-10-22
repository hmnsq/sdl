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

#ಯದಿ defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ಅನ್ತರ್ಭಾವ "SDL_windowsvideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_windowsevents.h"
#ಅನ್ತರ್ಭಾವ "SDL_windowsrawinput.h"

#ಅನ್ತರ್ಭಾವ "../SDL_video_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"
#ಅನ್ತರ್ಭಾವ "../../joystick/usb_ids.h"
#ಅನ್ತರ್ಭಾವ "../../core/windows/SDL_windows.h" // for checking windows version

#define RIFF_FOURCC(c0, c1, c2, c3)                 \
    ((DWORD)(BYTE)(c0) | ((DWORD)(BYTE)(c1) << 8) | \
     ((DWORD)(BYTE)(c2) << 16) | ((DWORD)(BYTE)(c3) << 24))

#define ANI_FLAG_ICON 0x1

#pragma pack(ತಳ್ಳು, 1)

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ
{
    BYTE bWidth;
    BYTE bHeight;
    BYTE b_Color_ಎಣಿಕೆ;
    BYTE bReserved;
    WORD xHotspot;
    WORD yHotspot;
    DWORD dwImageSize;
    DWORD dwImageOffset;
} CURSORICONFILEDIRENTRY;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ
{
    WORD idReserved;
    WORD idType;
    WORD id_ಎಣಿಕೆ;
} CURSORICONFILEDIR;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ
{
    DWORD cbSizeof; // sizeof(ANIHEADER) = 36 bytes.
    DWORD frames;   // Number of frames in the frame list.
    DWORD steps;    // Number of steps in the animation loop.
    DWORD width;    // Width
    DWORD height;   // Height
    DWORD bpp;      // bpp
    DWORD planes;   // Not used
    DWORD jifRate;  // Default display rate, in jiffies (1/60s)
    DWORD fl;       // AF_ICON should be set. AF_SEQUENCE is optional
} ANIHEADER;

#pragma pack(ತೆಗೆ)

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ CachedCursor
{
    ಭಿನ್ನ scale;
    HCURSOR cursor;
    ಸಂರಚನಾ CachedCursor *next;
} CachedCursor;

ಸಂರಚನಾ SDL_CursorData
{
    HCURSOR cursor;

    CachedCursor *cache;
    ಪೂರ್ಣಾಙ್ಕ hot_x;
    ಪೂರ್ಣಾಙ್ಕ hot_y;
    ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ_frames;
    SDL_CursorFrameInfo frames[1];
};

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ
{
    Uint64 xs[5];
    Uint64 ys[5];
    Sint64 residual[2];
    Uint32 dpiscale;
    Uint32 dpidenom;
    ಪೂರ್ಣಾಙ್ಕ last_ಗಂಟು;
    bool enhanced;
    bool dpiaware;
} WIN_MouseData;

DWORD SDL_last_warp_time = 0;
HCURSOR SDL_cursor = ರಿಕ್ತ;
ಸ್ಥಿರ SDL_Cursor *SDL_blank_cursor = ರಿಕ್ತ;
ಸ್ಥಿರ WIN_MouseData WIN_system_scale_data;

ಸ್ಥಿರ SDL_Cursor *WIN_CreateCursorAndData(HCURSOR hcursor)
{
    ಯದಿ (!hcursor) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, ಪರಿಮಾಣ(*cursor));
    ಯದಿ (!cursor) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, ಪರಿಮಾಣ(*data));
    ಯದಿ (!data) {
        SDL_free(cursor);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    data->cursor = hcursor;
    cursor->internal = data;
    ಪ್ರತ್ಯಾಗಮ cursor;
}

ಸ್ಥಿರ SDL_Cursor *WIN_CreateAnimatedCursorAndData(SDL_CursorFrameInfo *frames, ಪೂರ್ಣಾಙ್ಕ frame_ಎಣಿಕೆ, ಪೂರ್ಣಾಙ್ಕ hot_x, ಪೂರ್ಣಾಙ್ಕ hot_y)
{
    // Dynamically generate cursors at the appropriate DPI
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, ಪರಿಮಾಣ(*cursor));
    ಯದಿ (!cursor) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, ಪರಿಮಾಣ(*data) + (ಪರಿಮಾಣ(SDL_CursorFrameInfo) * (frame_ಎಣಿಕೆ - 1)));
    ಯದಿ (!data) {
        SDL_free(cursor);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    data->hot_x = hot_x;
    data->hot_y = hot_y;
    data->ಅಂಕೆ_frames = frame_ಎಣಿಕೆ;
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < frame_ಎಣಿಕೆ; ++i) {
        SDL_Surface *surface = frames[i].surface;
        ಯದಿ (surface->flags & SDL_SURFACE_PREALLOCATED) {
            surface = SDL_DuplicateSurface(surface);
            ಯದಿ (!surface) {
                ಯಾವತ್ (i > 0) {
                    --i;
                    SDL_DestroySurface(data->frames[i].surface);
                }
                SDL_free(data);
                SDL_free(cursor);
                ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
            }
        } ಅನ್ಯಥಾ {
            ++surface->refcount;
        }
        data->frames[i].surface = surface;
        data->frames[i].duration = frames[i].duration;
    }
    cursor->internal = data;
    ಪ್ರತ್ಯಾಗಮ cursor;
}

ಸ್ಥಿರ bool SaveChunkSize(SDL_IOStream* dst, Sint64 offset)
{
    Sint64 here = SDL_TellIO(dst);
    ಯದಿ (here < 0) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    ಯದಿ (SDL_SeekIO(dst, offset, SDL_IO_SEEK_SET) < 0) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    DWORD size = (DWORD)(here - (offset + ಪರಿಮಾಣ(DWORD)));
    ಯದಿ (!SDL_WriteU32LE(dst, size)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
    ಪ್ರತ್ಯಾಗಮ SDL_SeekIO(dst, here, SDL_IO_SEEK_SET);
}

ಸ್ಥಿರ bool FillIconEntry(CURSORICONFILEDIRENTRY *entry, SDL_Surface *surface, ಪೂರ್ಣಾಙ್ಕ hot_x, ಪೂರ್ಣಾಙ್ಕ hot_y, DWORD dwImageSize, DWORD dwImageOffset)
{
    ಯದಿ (surface->props) {
        hot_x = (ಪೂರ್ಣಾಙ್ಕ)SDL_Get_ಸಂಖ್ಯೆ_Property(surface->props, SDL_PROP_SURFACE_HOTSPOT_X_ಸಂಖ್ಯೆ, hot_x);
        hot_y = (ಪೂರ್ಣಾಙ್ಕ)SDL_Get_ಸಂಖ್ಯೆ_Property(surface->props, SDL_PROP_SURFACE_HOTSPOT_Y_ಸಂಖ್ಯೆ, hot_y);
    }
    hot_x = SDL_clamp(hot_x, 0, surface->w - 1);
    hot_y = SDL_clamp(hot_y, 0, surface->h - 1);

    SDL_zerop(entry);
    entry->bWidth = surface->w < 256 ? surface->w : 0;  // 0 means a width of 256
    entry->bHeight = surface->h < 256 ? surface->h : 0; // 0 means a height of 256
    entry->xHotspot = hot_x;
    entry->yHotspot = hot_y;
    entry->dwImageSize = dwImageSize;
    entry->dwImageOffset = dwImageOffset;
    ಪ್ರತ್ಯಾಗಮ true;
}

#ifdef SAVE_ICON_PNG

ಸ್ಥಿರ bool WriteIconSurface(SDL_IOStream *dst, SDL_Surface *surface)
{
    ಯದಿ (!SDL_SavePNG_IO(surface, dst, false)) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    // Image data offsets must be WORD aligned
    Sint64 offset = SDL_TellIO(dst);
    ಯದಿ (offset & 1) {
        ಯದಿ (!SDL_WriteU8(dst, 0)) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

#ಅನ್ಯಥಾ

/* For info on the expected mask format see:
 * https://devblogs.microsoft.com/oldnewthing/20101018-00/?p=12513
 */
ಸ್ಥಿರ ಶೂನ್ಯ *CreateIconMask(SDL_Surface *surface, size_t *mask_size)
{
    Uint8 *dst;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ w = (surface->w + 7) / 8;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ pad = (((w) % 4) ? (4 - ((w) % 4)) : 0);
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ pitch = (w + pad);
    ಧ್ರುವ size_t size = pitch * surface->h;
    ಸ್ಥಿರ ಧ್ರುವ unsigned ವರ್ಣ masks[] = { 0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1 };

    ಶೂನ್ಯ *mask = SDL_malloc(size);
    ಯದಿ (!mask) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    dst = (Uint8 *)mask;

    // Make the mask completely transparent.
    SDL_memset(dst, 0xff, size);
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ y = surface->h - 1; y >= 0; --y, dst += pitch) {
        ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ x = 0; x < surface->w; ++x) {
            Uint8 r, g, b, a;
            SDL_ReadSurfacePixel(surface, x, y, &r, &g, &b, &a);

            ಯದಿ (a != 0) {
                // Reset bit of an opaque pixel.
                dst[x >> 3] &= ~masks[x & 7];
            }
        }
    }
    *mask_size = size;
    ಪ್ರತ್ಯಾಗಮ mask;
}

ಸ್ಥಿರ bool WriteIconSurface(SDL_IOStream *dst, SDL_Surface *surface)
{
    SDL_Surface *temp = ರಿಕ್ತ;

    ಯದಿ (surface->format != SDL_PIXELFORMAT_ARGB8888) {
        temp = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        ಯದಿ (!temp) {
            ಪ್ರತ್ಯಾಗಮ false;
        }
        surface = temp;
    }

    // Cursor data is double height (DIB and mask), stored bottom-up
    bool ok = true;
    size_t mask_size = 0;
    ಶೂನ್ಯ *mask = CreateIconMask(surface, &mask_size);
    ಯದಿ (!mask) {
        ok = false;
        ಗಚ್ಛ done;
    }

    BITMAPINFOHEADER bmih;
    SDL_zero(bmih);
    DWORD row_size = surface->w * 4;
    bmih.biSize = ಪರಿಮಾಣ(BITMAPINFOHEADER);
    bmih.biWidth = surface->w;
    bmih.biHeight = surface->h * 2;
    bmih.biPlanes = 1;
    bmih.bi_Bit_ಎಣಿಕೆ = 32;
    bmih.biCompression = BI_RGB;
    bmih.biSizeImage = (DWORD)(surface->h * row_size + mask_size);
    ok &= (SDL_WriteIO(dst, &bmih, ಪರಿಮಾಣ(bmih)) == ಪರಿಮಾಣ(bmih));

    ಧ್ರುವ Uint8 *pix = surface->pixels;
    pix += (surface->h - 1) * surface->pitch;
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < surface->h; ++i) {
        ok &= (SDL_WriteIO(dst, pix, row_size) == row_size);
        pix -= surface->pitch;
    }
    ok &= (SDL_WriteIO(dst, mask, mask_size) == mask_size);

done:
    SDL_free(mask);
    SDL_DestroySurface(temp);
    ಪ್ರತ್ಯಾಗಮ ok;
}

#endif // SAVE_ICON_PNG

ಸ್ಥಿರ bool WriteIconFrame(SDL_IOStream *dst, SDL_Surface *surface, ಪೂರ್ಣಾಙ್ಕ hot_x, ಪೂರ್ಣಾಙ್ಕ hot_y, ಭಿನ್ನ scale)
{
#ifdef SAVE_MULTIPLE_ICONS
    ಪೂರ್ಣಾಙ್ಕ ಎಣಿಕೆ = 0;
    SDL_Surface **surfaces = SDL_GetSurfaceImages(surface, &ಎಣಿಕೆ);
    ಯದಿ (!surfaces) {
        ಪ್ರತ್ಯಾಗಮ false;
    }
#ಅನ್ಯಥಾ
    surface = SDL_GetSurfaceImage(surface, scale);
    ಯದಿ (!surface) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಪೂರ್ಣಾಙ್ಕ ಎಣಿಕೆ = 1;
    SDL_Surface **surfaces = &surface;
#endif

    // Raymond Chen has more insight into this format at:
    // https://devblogs.microsoft.com/oldnewthing/20101018-00/?p=12513
    bool ok = true;
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('i', 'c', 'o', 'n'));
    Sint64 icon_size_offset = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    Sint64 base_offset = icon_size_offset + ಪರಿಮಾಣ(DWORD);

    CURSORICONFILEDIR dir;
    dir.idReserved = 0;
    dir.idType = 2; // Cursor
    dir.id_ಎಣಿಕೆ = ಎಣಿಕೆ;
    ok &= (SDL_WriteIO(dst, &dir, ಪರಿಮಾಣ(dir)) == ಪರಿಮಾಣ(dir));

    DWORD entries_size = ಎಣಿಕೆ * ಪರಿಮಾಣ(CURSORICONFILEDIRENTRY);
    CURSORICONFILEDIRENTRY *entries = (CURSORICONFILEDIRENTRY *)SDL_malloc(entries_size);
    ಯದಿ (!entries) {
        ok = false;
        ಗಚ್ಛ done;
    }
    ok &= (SDL_WriteIO(dst, entries, entries_size) == entries_size);

    Sint64 image_offset = SDL_TellIO(dst);
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < ಎಣಿಕೆ; ++i) {
        ok &= WriteIconSurface(dst, surfaces[i]);

        Sint64 next_offset = SDL_TellIO(dst);
        DWORD dwImageSize = (DWORD)(next_offset - image_offset);
        DWORD dwImageOffset = (DWORD)(image_offset - base_offset);

        ok &= FillIconEntry(&entries[i], surfaces[i], hot_x, hot_y, dwImageSize, dwImageOffset);

        image_offset = next_offset;
    }

    // Now that we have the icon entries filled out, rewrite them
    ok &= (SDL_SeekIO(dst, base_offset + ಪರಿಮಾಣ(dir), SDL_IO_SEEK_SET) >= 0);
    ok &= (SDL_WriteIO(dst, entries, entries_size) == entries_size);
    ok &= (SDL_SeekIO(dst, image_offset, SDL_IO_SEEK_SET) >= 0);
    SDL_free(entries);

    ok &= SaveChunkSize(dst, icon_size_offset);

done:
#ifdef SAVE_MULTIPLE_ICONS
    SDL_free(surfaces);
#ಅನ್ಯಥಾ
    SDL_DestroySurface(surface);
#endif
    ಪ್ರತ್ಯಾಗಮ ok;
}

/* Windows doesn't have an API to easily create animated cursors from a sequence of images,
 * so we have to build an animated cursor resource file in memory and load it.
 */
ಸ್ಥಿರ HCURSOR WIN_CreateAnimatedCursorInternal(SDL_CursorFrameInfo *frames, ಪೂರ್ಣಾಙ್ಕ frame_ಎಣಿಕೆ, ಪೂರ್ಣಾಙ್ಕ hot_x, ಪೂರ್ಣಾಙ್ಕ hot_y, ಭಿನ್ನ scale)
{
    HCURSOR hcursor = ರಿಕ್ತ;
    SDL_IOStream *dst = SDL_IOFromDynamicMem();
    ಯದಿ (!dst) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    ಪೂರ್ಣಾಙ್ಕ w = (ಪೂರ್ಣಾಙ್ಕ)SDL_roundf(frames[0].surface->w * scale);
    ಪೂರ್ಣಾಙ್ಕ h = (ಪೂರ್ಣಾಙ್ಕ)SDL_roundf(frames[0].surface->h * scale);

    bool ok = true;
    // RIFF header
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('R', 'I', 'F', 'F'));
    Sint64 riff_size_offset = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('A', 'C', 'O', 'N'));

    // anih header chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('a', 'n', 'i', 'h'));
    ok &= SDL_WriteU32LE(dst, ಪರಿಮಾಣ(ANIHEADER));

    ANIHEADER anih;
    SDL_zero(anih);
    anih.cbSizeof = ಪರಿಮಾಣ(anih);
    anih.frames = frame_ಎಣಿಕೆ;
    anih.steps = frame_ಎಣಿಕೆ;
    anih.jifRate = 1;
    anih.fl = ANI_FLAG_ICON;
    ok &= (SDL_WriteIO(dst, &anih, ಪರಿಮಾಣ(anih)) == ಪರಿಮಾಣ(anih));

    // Rate chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('r', 'a', 't', 'e'));
    ok &= SDL_WriteU32LE(dst, ಪರಿಮಾಣ(DWORD) * frame_ಎಣಿಕೆ);
    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < frame_ಎಣಿಕೆ; ++i) {
        // Animated Win32 cursors are in jiffy units, and one jiffy is 1/60 of a second.
        ಧ್ರುವ ದ್ವಿಗುಣ WIN32_JIFFY = 1000.0 / 60.0;
        DWORD duration = (frames[i].duration ? SDL_lround(frames[i].duration / WIN32_JIFFY) : 0xFFFFFFFF);
        ok &= SDL_WriteU32LE(dst, duration);
    }

    // Frame list
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('L', 'I', 'S', 'T'));
    Sint64 frame_list_size_offset = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('f', 'r', 'a', 'm'));

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < frame_ಎಣಿಕೆ; ++i) {
        ok &= WriteIconFrame(dst, frames[i].surface, hot_x, hot_y, scale);
    }
    ok &= SaveChunkSize(dst, frame_list_size_offset);

    // All done!
    ok &= SaveChunkSize(dst, riff_size_offset);
    ಯದಿ (!ok) {
        // The error has been set above
        ಗಚ್ಛ done;
    }

    BYTE *mem = (BYTE *)SDL_GetPointerProperty(SDL_GetIOProperties(dst), SDL_PROP_IOSTREAM_DYNAMIC_MEMORY_POINTER, ರಿಕ್ತ);
    DWORD size = (DWORD)SDL_GetIOSize(dst);
    hcursor = (HCURSOR)CreateIconFromResourceEx(mem, size, FALSE, 0x00030000, w, h, 0);
    ಯದಿ (!hcursor) {
        SDL_SetError("CreateIconFromResource failed");
    }

done:
    SDL_CloseIO(dst);

    ಪ್ರತ್ಯಾಗಮ hcursor;
}

ಸ್ಥಿರ SDL_Cursor *WIN_CreateCursor(SDL_Surface *surface, ಪೂರ್ಣಾಙ್ಕ hot_x, ಪೂರ್ಣಾಙ್ಕ hot_y)
{
    SDL_CursorFrameInfo frame = { surface, 0 };
    ಪ್ರತ್ಯಾಗಮ WIN_CreateAnimatedCursorAndData(&frame, 1, hot_x, hot_y);
}

ಸ್ಥಿರ SDL_Cursor *WIN_CreateAnimatedCursor(SDL_CursorFrameInfo *frames, ಪೂರ್ಣಾಙ್ಕ frame_ಎಣಿಕೆ, ಪೂರ್ಣಾಙ್ಕ hot_x, ಪೂರ್ಣಾಙ್ಕ hot_y)
{
    ಪ್ರತ್ಯಾಗಮ WIN_CreateAnimatedCursorAndData(frames, frame_ಎಣಿಕೆ, hot_x, hot_y);
}

ಸ್ಥಿರ SDL_Cursor *WIN_CreateBlankCursor(ಶೂನ್ಯ)
{
    SDL_Cursor *cursor = ರಿಕ್ತ;
    SDL_Surface *surface = SDL_CreateSurfaceZeroed(32, 32, SDL_PIXELFORMAT_ARGB8888);
    ಯದಿ (surface) {
        cursor = WIN_CreateCursor(surface, 0, 0);
        SDL_DestroySurface(surface);
    }
    ಪ್ರತ್ಯಾಗಮ cursor;
}

ಸ್ಥಿರ SDL_Cursor *WIN_CreateSystemCursor(SDL_SystemCursor id)
{
    LPCTSTR name;

    ವಿಕಲ್ಪ (id) {
    ಸ್ವಭಾವ:
        SDL_assert(!"Unknown system cursor ID");
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_DEFAULT:
        name = IDC_ARROW;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_TEXT:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        name = IDC_IBEAM;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_WAIT:
        name = IDC_WAIT;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_CROSSHAIR:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_CELL:
        name = IDC_CROSS;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_PROGRESS:
        name = IDC_APPSTARTING;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_NWSE_RESIZE:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_NW_RESIZE:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_SE_RESIZE:
        name = IDC_SIZENWSE;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_NESW_RESIZE:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_NE_RESIZE:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_SW_RESIZE:
        name = IDC_SIZENESW;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_EW_RESIZE:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_E_RESIZE:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_W_RESIZE:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_COL_RESIZE:
        name = IDC_SIZEWE;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_NS_RESIZE:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_N_RESIZE:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_S_RESIZE:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_ROW_RESIZE:
        name = IDC_SIZENS;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_MOVE:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_ALL_SCROLL:
        name = IDC_SIZEALL;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_NOT_ALLOWED:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_NO_DROP:
        name = IDC_NO;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_POINTER:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_CONTEXT_MENU:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_ALIAS:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_COPY:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_GRAB:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_GRABBING:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_ZOOM_IN:
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_ZOOM_OUT:
        name = IDC_HAND;
        ಭಙ್ಗ;
    ಪಕ್ಷ SDL_SYSTEM_CURSOR_HELP:
        name = IDC_HELP;
        ಭಙ್ಗ;
    }
    ಪ್ರತ್ಯಾಗಮ WIN_CreateCursorAndData(LoadCursor(ರಿಕ್ತ, name));
}

ಸ್ಥಿರ SDL_Cursor *WIN_CreateDefaultCursor(ಶೂನ್ಯ)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    ಪ್ರತ್ಯಾಗಮ WIN_CreateSystemCursor(id);
}

ಸ್ಥಿರ ಶೂನ್ಯ WIN_FreeCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *data = cursor->internal;

    ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < data->ಅಂಕೆ_frames; ++i) {
        SDL_DestroySurface(data->frames[i].surface);
    }
    ಯಾವತ್ (data->cache) {
        CachedCursor *entry = data->cache;
        data->cache = entry->next;
        ಯದಿ (entry->cursor) {
            DestroyCursor(entry->cursor);
        }
        SDL_free(entry);
    }
    ಯದಿ (data->cursor) {
        DestroyCursor(data->cursor);
    }
    SDL_free(data);
    SDL_free(cursor);
}

ಸ್ಥಿರ HCURSOR GetCachedCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *data = cursor->internal;

    ಭಿನ್ನ scale = 1.0f;
    ಯದಿ (SDL_GetHintBoolean(SDL_HINT_MOUSE_DPI_SCALE_CURSORS, false)) {
        scale = SDL_GetDisplayContentScale(SDL_GetDisplayForWindow(SDL_GetMouseFocus()));
        ಯದಿ (scale == 0.0f) {
            scale = 1.0f;
        }
    }
    ಪ್ರತಿ (CachedCursor *entry = data->cache; entry; entry = entry->next) {
        ಯದಿ (scale == entry->scale) {
            ಪ್ರತ್ಯಾಗಮ entry->cursor;
        }
    }

    // Need to create a cursor for this content scale
    HCURSOR hcursor = WIN_CreateAnimatedCursorInternal(data->frames, data->ಅಂಕೆ_frames, data->hot_x, data->hot_y, scale);
    ಯದಿ (!hcursor) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    CachedCursor *entry = (CachedCursor *)SDL_calloc(1, ಪರಿಮಾಣ(*entry));
    ಯದಿ (!entry) {
        DestroyCursor(hcursor);
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    entry->cursor = hcursor;
    entry->scale = scale;
    entry->next = data->cache;
    data->cache = entry;

    ಪ್ರತ್ಯಾಗಮ hcursor;
}

ಸ್ಥಿರ bool WIN_ShowCursor(SDL_Cursor *cursor)
{
    ಯದಿ (!cursor) {
        ಯದಿ (GetSystemMetrics(SM_REMOTESESSION)) {
            // Use a blank cursor so we continue to get relative motion over RDP
            cursor = SDL_blank_cursor;
        }
    }
    ಯದಿ (cursor) {
        SDL_CursorData *data = cursor->internal;
        ಯದಿ (data->ಅಂಕೆ_frames > 0) {
            SDL_cursor = GetCachedCursor(cursor);
        } ಅನ್ಯಥಾ {
            SDL_cursor = data->cursor;
        }
    } ಅನ್ಯಥಾ {
        SDL_cursor = ರಿಕ್ತ;
    }
    ಯದಿ (SDL_GetMouseFocus() != ರಿಕ್ತ) {
        SetCursor(SDL_cursor);
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

ಶೂನ್ಯ WIN_SetCursorPos(ಪೂರ್ಣಾಙ್ಕ x, ಪೂರ್ಣಾಙ್ಕ y)
{
    // We need to jitter the value because otherwise Windows will occasionally inexplicably ignore the SetCursorPos() or SendInput()
    SetCursorPos(x, y);
    SetCursorPos(x + 1, y);
    SetCursorPos(x, y);

    // Flush any mouse motion prior to or associated with this warp
#ifdef _MSC_VER // We explicitly want to use GetTickCount(), not GetTickCount64()
#pragma warning(ತಳ್ಳು)
#pragma warning(disable : 28159)
#endif
    SDL_last_warp_time = Get_Tick_ಎಣಿಕೆ();
    ಯದಿ (!SDL_last_warp_time) {
        SDL_last_warp_time = 1;
    }
#ifdef _MSC_VER
#pragma warning(ತೆಗೆ)
#endif
}

ಸ್ಥಿರ bool WIN_WarpMouse(SDL_Window *window, ಭಿನ್ನ x, ಭಿನ್ನ y)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    POINT pt;

    // Don't warp the mouse while we're doing a modal interaction
    ಯದಿ (data->in_title_click || data->focus_click_pending) {
        ಪ್ರತ್ಯಾಗಮ true;
    }

    pt.x = (ಪೂರ್ಣಾಙ್ಕ)SDL_roundf(x);
    pt.y = (ಪೂರ್ಣಾಙ್ಕ)SDL_roundf(y);
    ClientToScreen(hwnd, &pt);
    WIN_SetCursorPos(pt.x, pt.y);

    // Send the exact mouse motion associated with this warp
    SDL_SendMouseMotion(0, window, SDL_GLOBAL_MOUSE_ID, false, x, y);
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool WIN_WarpMouseGlobal(ಭಿನ್ನ x, ಭಿನ್ನ y)
{
    POINT pt;

    pt.x = (ಪೂರ್ಣಾಙ್ಕ)SDL_roundf(x);
    pt.y = (ಪೂರ್ಣಾಙ್ಕ)SDL_roundf(y);
    SetCursorPos(pt.x, pt.y);
    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ bool WIN_SetRelativeMouseMode(bool enabled)
{
    ಪ್ರತ್ಯಾಗಮ WIN_SetRawMouseEnabled(SDL_GetVideoDevice(), enabled);
}

ಸ್ಥಿರ bool WIN_CaptureMouse(SDL_Window *window)
{
    ಯದಿ (window) {
        SDL_WindowData *data = window->internal;
        SetCapture(data->hwnd);
    } ಅನ್ಯಥಾ {
        SDL_Window *focus_window = SDL_GetMouseFocus();

        ಯದಿ (focus_window) {
            SDL_WindowData *data = focus_window->internal;
            ಯದಿ (!data->mouse_tracked) {
                SDL_SetMouseFocus(ರಿಕ್ತ);
            }
        }
        ReleaseCapture();
    }

    ಪ್ರತ್ಯಾಗಮ true;
}

ಸ್ಥಿರ SDL_MouseButtonFlags WIN_GetGlobalMouseState(ಭಿನ್ನ *x, ಭಿನ್ನ *y)
{
    SDL_MouseButtonFlags result = 0;
    POINT pt = { 0, 0 };
    bool swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;

    GetCursorPos(&pt);
    *x = (ಭಿನ್ನ)pt.x;
    *y = (ಭಿನ್ನ)pt.y;

    result |= Get_Async_ಕೀಲಿ_State(!swapButtons ? VK_LBUTTON : VK_RBUTTON) & 0x8000 ? SDL_BUTTON_LMASK : 0;
    result |= Get_Async_ಕೀಲಿ_State(!swapButtons ? VK_RBUTTON : VK_LBUTTON) & 0x8000 ? SDL_BUTTON_RMASK : 0;
    result |= Get_Async_ಕೀಲಿ_State(VK_MBUTTON) & 0x8000 ? SDL_BUTTON_MMASK : 0;
    result |= Get_Async_ಕೀಲಿ_State(VK_XBUTTON1) & 0x8000 ? SDL_BUTTON_X1MASK : 0;
    result |= Get_Async_ಕೀಲಿ_State(VK_XBUTTON2) & 0x8000 ? SDL_BUTTON_X2MASK : 0;

    ಪ್ರತ್ಯಾಗಮ result;
}

ಸ್ಥಿರ ಶೂನ್ಯ WIN_ApplySystemScale(ಶೂನ್ಯ *internal, Uint64 timestamp, SDL_Window *window, SDL_MouseID mouseID, ಭಿನ್ನ *x, ಭಿನ್ನ *y)
{
    ಯದಿ (!internal) {
        ಪ್ರತ್ಯಾಗಮ;
    }
    WIN_MouseData *data = (WIN_MouseData *)internal;

    SDL_VideoDisplay *display = window ? SDL_GetVideoDisplayForWindow(window) : SDL_GetVideoDisplay(SDL_GetPrimaryDisplay());

    Sint64 ix = (Sint64)*x * 65536;
    Sint64 iy = (Sint64)*y * 65536;
    Uint32 dpi = display ? (Uint32)(display->content_scale * USER_DEFAULT_SCREEN_DPI) : USER_DEFAULT_SCREEN_DPI;

    ಯದಿ (!data->enhanced) { // early return if flat scale
        dpi = data->dpiscale * (data->dpiaware ? dpi : USER_DEFAULT_SCREEN_DPI);
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
        *x = (ಭಿನ್ನ)ix / 65536.0f;
        *y = (ಭಿನ್ನ)iy / 65536.0f;
        ಪ್ರತ್ಯಾಗಮ;
    }

    Uint64 *xs = data->xs;
    Uint64 *ys = data->ys;
    Uint64 absx = SDL_abs(ix);
    Uint64 absy = SDL_abs(iy);
    Uint64 speed = SDL_min(absx, absy) + (SDL_max(absx, absy) << 1); // super cursed approximation used by Windows
    ಯದಿ (speed == 0) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    ಪೂರ್ಣಾಙ್ಕ i, j, k;
    ಪ್ರತಿ (i = 1; i < 5; i++) {
        j = i;
        ಯದಿ (speed < xs[j]) {
            ಭಙ್ಗ;
        }
    }
    i -= 1;
    j -= 1;
    k = data->last_ಗಂಟು;
    data->last_ಗಂಟು = j;

    Uint32 denom = data->dpidenom;
    Sint64 scale = 0;
    Sint64 xdiff = xs[j+1] - xs[j];
    Sint64 ydiff = ys[j+1] - ys[j];
    ಯದಿ (xdiff != 0) {
        Sint64 slope = ydiff / xdiff;
        Sint64 inter = slope * xs[i] - ys[i];
        scale += slope - inter / speed;
    }

    ಯದಿ (j > k) {
        denom <<= 1;
        xdiff = xs[k+1] - xs[k];
        ydiff = ys[k+1] - ys[k];
        ಯದಿ (xdiff != 0) {
            Sint64 slope = ydiff / xdiff;
            Sint64 inter = slope * xs[k] - ys[k];
            scale += slope - inter / speed;
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
    *x = (ಭಿನ್ನ)ix / 65536.0f;
    *y = (ಭಿನ್ನ)iy / 65536.0f;
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
    mouse->SetRelativeMouseMode = WIN_SetRelativeMouseMode;
    mouse->CaptureMouse = WIN_CaptureMouse;
    mouse->GetGlobalMouseState = WIN_GetGlobalMouseState;
    mouse->ApplySystemScale = WIN_ApplySystemScale;
    mouse->system_scale_data = &WIN_system_scale_data;

    SDL_SetDefaultCursor(WIN_CreateDefaultCursor());

    SDL_blank_cursor = WIN_CreateBlankCursor();

    WIN_UpdateMouseSystemScale();
}

ಶೂನ್ಯ WIN_QuitMouse(SDL_VideoDevice *_this)
{
    ಯದಿ (SDL_blank_cursor) {
        WIN_FreeCursor(SDL_blank_cursor);
        SDL_blank_cursor = ರಿಕ್ತ;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ ReadMouseCurve(ಪೂರ್ಣಾಙ್ಕ v, Uint64 xs[5], Uint64 ys[5])
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
    DWORD xsize = ಪರಿಮಾಣ(xbuff);
    DWORD ysize = ಪರಿಮಾಣ(ybuff);
    HKEY open_handle;
    ಯದಿ (Reg_Open_ಕೀಲಿ_Ex_W(HKEY_CURRENT_USER, L"Control Panel\\Mouse", 0, ಕೀಲಿ_READ, &open_handle) == ERROR_SUCCESS) {
        Reg_Query_ಮೌಲ್ಯ_Ex_W(open_handle, L"SmoothMouseXCurve", ರಿಕ್ತ, ರಿಕ್ತ, (BYTE*)xbuff, &xsize);
        Reg_Query_ಮೌಲ್ಯ_Ex_W(open_handle, L"SmoothMouseYCurve", ರಿಕ್ತ, ರಿಕ್ತ, (BYTE*)ybuff, &ysize);
        Reg_Close_ಕೀಲಿ(open_handle);
    }
    xs[0] = 0; // first node must always be origin
    ys[0] = 0; // first node must always be origin
    ಪೂರ್ಣಾಙ್ಕ i;
    ಪ್ರತಿ (i = 1; i < 5; i++) {
        xs[i] = (7 * (Uint64)xbuff[i * 2]);
        ys[i] = (v * (Uint64)ybuff[i * 2]) << 17;
    }
}

ಶೂನ್ಯ WIN_UpdateMouseSystemScale(ಶೂನ್ಯ)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    ಯದಿ (mouse->ApplySystemScale == WIN_ApplySystemScale) {
        mouse->system_scale_data = &WIN_system_scale_data;
    }

    // always reinitialize to valid defaults, whether fetch was successful or not.
    WIN_MouseData *data = &WIN_system_scale_data;
    data->residual[0] = 0;
    data->residual[1] = 0;
    data->dpiscale = 32;
    data->dpidenom = (10 * (WIN_IsWindows8OrGreater() ? 120 : 150)) << 16;
    data->dpiaware = WIN_IsPerMonitorV2DPIAware(SDL_GetVideoDevice());
    data->enhanced = false;

    ಪೂರ್ಣಾಙ್ಕ v = 10;
    ಯದಿ (SystemParametersInfo(SPI_GETMOUSESPEED, 0, &v, 0)) {
        v = SDL_max(1, SDL_min(v, 20));
        data->dpiscale = SDL_max(SDL_max(v, (v - 2) * 4), (v - 6) * 8);
    }

    ಪೂರ್ಣಾಙ್ಕ params[3];
    ಯದಿ (SystemParametersInfo(SPI_GETMOUSE, 0, &params, 0)) {
        data->enhanced = params[2] ? true : false;
        ಯದಿ (params[2]) {
            ReadMouseCurve(v, data->xs, data->ys);
        }
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS

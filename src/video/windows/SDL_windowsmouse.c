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
#include "SDL_internal.h"

#ᮚᮦᮔ᮪ defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#include "SDL_windowsvideo.h"
#include "SDL_windowsevents.h"
#include "SDL_windowsrawinput.h"

#include "../SDL_video_c.h"
#include "../../events/SDL_mouse_c.h"
#include "../../joystick/usb_ids.h"
#include "../../core/windows/SDL_windows.h" // for checking windows version

#define RIFF_FOURCC(c0, c1, c2, c3)                 \
    ((DWORD)(BYTE)(c0) | ((DWORD)(BYTE)(c1) << 8) | \
     ((DWORD)(BYTE)(c2) << 16) | ((DWORD)(BYTE)(c3) << 24))

#define ANI_FLAG_ICON 0x1

#pragma pack(push, 1)

typedef sa_nracanaa
{
    BYTE bWidth;
    BYTE bHeight;
    BYTE bColorCount;
    BYTE bReserved;
    WORD xHotspot;
    WORD yHotspot;
    DWORD dwImageSize;
    DWORD dwImageOffset;
} CURSORICONFILEDIRENTRY;

typedef sa_nracanaa
{
    WORD idReserved;
    WORD idType;
    WORD idCount;
} CURSORICONFILEDIR;

typedef sa_nracanaa
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

#pragma pack(pop)

typedef sa_nracanaa CachedCursor
{
    float scale;
    HCURSOR cursor;
    sa_nracanaa CachedCursor *next;
} CachedCursor;

sa_nracanaa SDL_CursorData
{
    HCURSOR cursor;

    CachedCursor *cache;
    puur_naa_nka hot_x;
    puur_naa_nka hot_y;
    puur_naa_nka num_frames;
    SDL_CursorFrameInfo frames[1];
};

typedef sa_nracanaa
{
    Uint64 xs[5];
    Uint64 ys[5];
    Sint64 residual[2];
    Uint32 dpiscale;
    Uint32 dpidenom;
    puur_naa_nka last_node;
    bool enhanced;
    bool dpiaware;
} WIN_MouseData;

DWORD SDL_last_warp_time = 0;
HCURSOR SDL_cursor = NULL;
static SDL_Cursor *SDL_blank_cursor = NULL;
static WIN_MouseData WIN_system_scale_data;

static SDL_Cursor *WIN_CreateCursorAndData(HCURSOR hcursor)
{
    ᮚᮦᮔ᮪ (!hcursor) {
        ᮝᮜᮤ NULL;
    }

    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, parimaa_na(*cursor));
    ᮚᮦᮔ᮪ (!cursor) {
        ᮝᮜᮤ NULL;
    }

    SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, parimaa_na(*data));
    ᮚᮦᮔ᮪ (!data) {
        SDL_free(cursor);
        ᮝᮜᮤ NULL;
    }

    data->cursor = hcursor;
    cursor->internal = data;
    ᮝᮜᮤ cursor;
}

static SDL_Cursor *WIN_CreateAnimatedCursorAndData(SDL_CursorFrameInfo *frames, puur_naa_nka frame_count, puur_naa_nka hot_x, puur_naa_nka hot_y)
{
    // Dynamically generate cursors at the appropriate DPI
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, parimaa_na(*cursor));
    ᮚᮦᮔ᮪ (!cursor) {
        ᮝᮜᮤ NULL;
    }

    SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, parimaa_na(*data) + (parimaa_na(SDL_CursorFrameInfo) * (frame_count - 1)));
    ᮚᮦᮔ᮪ (!data) {
        SDL_free(cursor);
        ᮝᮜᮤ NULL;
    }

    data->hot_x = hot_x;
    data->hot_y = hot_y;
    data->num_frames = frame_count;
    for (puur_naa_nka i = 0; i < frame_count; ++i) {
        SDL_Surface *surface = frames[i].surface;
        ᮚᮦᮔ᮪ (surface->flags & SDL_SURFACE_PREALLOCATED) {
            surface = SDL_DuplicateSurface(surface);
            ᮚᮦᮔ᮪ (!surface) {
                ᮞᮨᮓᮨᮜ (i > 0) {
                    --i;
                    SDL_DestroySurface(data->frames[i].surface);
                }
                SDL_free(data);
                SDL_free(cursor);
                ᮝᮜᮤ NULL;
            }
        } ᮜᮤᮚ {
            ++surface->refcount;
        }
        data->frames[i].surface = surface;
        data->frames[i].duration = frames[i].duration;
    }
    cursor->internal = data;
    ᮝᮜᮤ cursor;
}

static bool SaveChunkSize(SDL_IOStream* dst, Sint64 offset)
{
    Sint64 here = SDL_TellIO(dst);
    ᮚᮦᮔ᮪ (here < 0) {
        ᮝᮜᮤ false;
    }
    ᮚᮦᮔ᮪ (SDL_SeekIO(dst, offset, SDL_IO_SEEK_SET) < 0) {
        ᮝᮜᮤ false;
    }

    DWORD size = (DWORD)(here - (offset + parimaa_na(DWORD)));
    ᮚᮦᮔ᮪ (!SDL_WriteU32LE(dst, size)) {
        ᮝᮜᮤ false;
    }
    ᮝᮜᮤ SDL_SeekIO(dst, here, SDL_IO_SEEK_SET);
}

static bool FillIconEntry(CURSORICONFILEDIRENTRY *entry, SDL_Surface *surface, puur_naa_nka hot_x, puur_naa_nka hot_y, DWORD dwImageSize, DWORD dwImageOffset)
{
    ᮚᮦᮔ᮪ (surface->props) {
        hot_x = (puur_naa_nka)SDL_GetNumberProperty(surface->props, SDL_PROP_SURFACE_HOTSPOT_X_NUMBER, hot_x);
        hot_y = (puur_naa_nka)SDL_GetNumberProperty(surface->props, SDL_PROP_SURFACE_HOTSPOT_Y_NUMBER, hot_y);
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
    ᮝᮜᮤ true;
}

#ifdef SAVE_ICON_PNG

static bool WriteIconSurface(SDL_IOStream *dst, SDL_Surface *surface)
{
    ᮚᮦᮔ᮪ (!SDL_SavePNG_IO(surface, dst, false)) {
        ᮝᮜᮤ false;
    }

    // Image data offsets must be WORD aligned
    Sint64 offset = SDL_TellIO(dst);
    ᮚᮦᮔ᮪ (offset & 1) {
        ᮚᮦᮔ᮪ (!SDL_WriteU8(dst, 0)) {
            ᮝᮜᮤ false;
        }
    }
    ᮝᮜᮤ true;
}

#ᮜᮤᮚ

/* For info on the expected mask format see:
 * https://devblogs.microsoft.com/oldnewthing/20101018-00/?p=12513
 */
static void *CreateIconMask(SDL_Surface *surface, size_t *mask_size)
{
    Uint8 *dst;
    const puur_naa_nka w = (surface->w + 7) / 8;
    const puur_naa_nka pad = (((w) % 4) ? (4 - ((w) % 4)) : 0);
    const puur_naa_nka pitch = (w + pad);
    const size_t size = pitch * surface->h;
    static const unsigned var_na masks[] = { 0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1 };

    void *mask = SDL_malloc(size);
    ᮚᮦᮔ᮪ (!mask) {
        ᮝᮜᮤ NULL;
    }

    dst = (Uint8 *)mask;

    // Make the mask completely transparent.
    SDL_memset(dst, 0xff, size);
    for (puur_naa_nka y = surface->h - 1; y >= 0; --y, dst += pitch) {
        for (puur_naa_nka x = 0; x < surface->w; ++x) {
            Uint8 r, g, b, a;
            SDL_ReadSurfacePixel(surface, x, y, &r, &g, &b, &a);

            ᮚᮦᮔ᮪ (a != 0) {
                // Reset bit of an opaque pixel.
                dst[x >> 3] &= ~masks[x & 7];
            }
        }
    }
    *mask_size = size;
    ᮝᮜᮤ mask;
}

static bool WriteIconSurface(SDL_IOStream *dst, SDL_Surface *surface)
{
    SDL_Surface *temp = NULL;

    ᮚᮦᮔ᮪ (surface->format != SDL_PIXELFORMAT_ARGB8888) {
        temp = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        ᮚᮦᮔ᮪ (!temp) {
            ᮝᮜᮤ false;
        }
        surface = temp;
    }

    // Cursor data is double height (DIB and mask), stored bottom-up
    bool ok = true;
    size_t mask_size = 0;
    void *mask = CreateIconMask(surface, &mask_size);
    ᮚᮦᮔ᮪ (!mask) {
        ok = false;
        goto done;
    }

    BITMAPINFOHEADER bmih;
    SDL_zero(bmih);
    DWORD row_size = surface->w * 4;
    bmih.biSize = parimaa_na(BITMAPINFOHEADER);
    bmih.biWidth = surface->w;
    bmih.biHeight = surface->h * 2;
    bmih.biPlanes = 1;
    bmih.biBitCount = 32;
    bmih.biCompression = BI_RGB;
    bmih.biSizeImage = (DWORD)(surface->h * row_size + mask_size);
    ok &= (SDL_WriteIO(dst, &bmih, parimaa_na(bmih)) == parimaa_na(bmih));

    const Uint8 *pix = surface->pixels;
    pix += (surface->h - 1) * surface->pitch;
    for (puur_naa_nka i = 0; i < surface->h; ++i) {
        ok &= (SDL_WriteIO(dst, pix, row_size) == row_size);
        pix -= surface->pitch;
    }
    ok &= (SDL_WriteIO(dst, mask, mask_size) == mask_size);

done:
    SDL_free(mask);
    SDL_DestroySurface(temp);
    ᮝᮜᮤ ok;
}

#endif // SAVE_ICON_PNG

static bool WriteIconFrame(SDL_IOStream *dst, SDL_Surface *surface, puur_naa_nka hot_x, puur_naa_nka hot_y, float scale)
{
#ifdef SAVE_MULTIPLE_ICONS
    puur_naa_nka count = 0;
    SDL_Surface **surfaces = SDL_GetSurfaceImages(surface, &count);
    ᮚᮦᮔ᮪ (!surfaces) {
        ᮝᮜᮤ false;
    }
#ᮜᮤᮚ
    surface = SDL_GetSurfaceImage(surface, scale);
    ᮚᮦᮔ᮪ (!surface) {
        ᮝᮜᮤ false;
    }

    puur_naa_nka count = 1;
    SDL_Surface **surfaces = &surface;
#endif

    // Raymond Chen has more insight into this format at:
    // https://devblogs.microsoft.com/oldnewthing/20101018-00/?p=12513
    bool ok = true;
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('i', 'c', 'o', 'n'));
    Sint64 icon_size_offset = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    Sint64 base_offset = icon_size_offset + parimaa_na(DWORD);

    CURSORICONFILEDIR dir;
    dir.idReserved = 0;
    dir.idType = 2; // Cursor
    dir.idCount = count;
    ok &= (SDL_WriteIO(dst, &dir, parimaa_na(dir)) == parimaa_na(dir));

    DWORD entries_size = count * parimaa_na(CURSORICONFILEDIRENTRY);
    CURSORICONFILEDIRENTRY *entries = (CURSORICONFILEDIRENTRY *)SDL_malloc(entries_size);
    ᮚᮦᮔ᮪ (!entries) {
        ok = false;
        goto done;
    }
    ok &= (SDL_WriteIO(dst, entries, entries_size) == entries_size);

    Sint64 image_offset = SDL_TellIO(dst);
    for (puur_naa_nka i = 0; i < count; ++i) {
        ok &= WriteIconSurface(dst, surfaces[i]);

        Sint64 next_offset = SDL_TellIO(dst);
        DWORD dwImageSize = (DWORD)(next_offset - image_offset);
        DWORD dwImageOffset = (DWORD)(image_offset - base_offset);

        ok &= FillIconEntry(&entries[i], surfaces[i], hot_x, hot_y, dwImageSize, dwImageOffset);

        image_offset = next_offset;
    }

    // Now that we have the icon entries filled out, rewrite them
    ok &= (SDL_SeekIO(dst, base_offset + parimaa_na(dir), SDL_IO_SEEK_SET) >= 0);
    ok &= (SDL_WriteIO(dst, entries, entries_size) == entries_size);
    ok &= (SDL_SeekIO(dst, image_offset, SDL_IO_SEEK_SET) >= 0);
    SDL_free(entries);

    ok &= SaveChunkSize(dst, icon_size_offset);

done:
#ifdef SAVE_MULTIPLE_ICONS
    SDL_free(surfaces);
#ᮜᮤᮚ
    SDL_DestroySurface(surface);
#endif
    ᮝᮜᮤ ok;
}

/* Windows doesn't have an API to easily create animated cursors from a sequence of images,
 * so we have to build an animated cursor resource file in memory and load it.
 */
static HCURSOR WIN_CreateAnimatedCursorInternal(SDL_CursorFrameInfo *frames, puur_naa_nka frame_count, puur_naa_nka hot_x, puur_naa_nka hot_y, float scale)
{
    HCURSOR hcursor = NULL;
    SDL_IOStream *dst = SDL_IOFromDynamicMem();
    ᮚᮦᮔ᮪ (!dst) {
        ᮝᮜᮤ NULL;
    }

    puur_naa_nka w = (puur_naa_nka)SDL_roundf(frames[0].surface->w * scale);
    puur_naa_nka h = (puur_naa_nka)SDL_roundf(frames[0].surface->h * scale);

    bool ok = true;
    // RIFF header
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('R', 'I', 'F', 'F'));
    Sint64 riff_size_offset = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('A', 'C', 'O', 'N'));

    // anih header chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('a', 'n', 'i', 'h'));
    ok &= SDL_WriteU32LE(dst, parimaa_na(ANIHEADER));

    ANIHEADER anih;
    SDL_zero(anih);
    anih.cbSizeof = parimaa_na(anih);
    anih.frames = frame_count;
    anih.steps = frame_count;
    anih.jifRate = 1;
    anih.fl = ANI_FLAG_ICON;
    ok &= (SDL_WriteIO(dst, &anih, parimaa_na(anih)) == parimaa_na(anih));

    // Rate chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('r', 'a', 't', 'e'));
    ok &= SDL_WriteU32LE(dst, parimaa_na(DWORD) * frame_count);
    for (puur_naa_nka i = 0; i < frame_count; ++i) {
        // Animated Win32 cursors are in jiffy units, and one jiffy is 1/60 of a second.
        const dviguu_na WIN32_JIFFY = 1000.0 / 60.0;
        DWORD duration = (frames[i].duration ? SDL_lround(frames[i].duration / WIN32_JIFFY) : 0xFFFFFFFF);
        ok &= SDL_WriteU32LE(dst, duration);
    }

    // Frame list
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('L', 'I', 'S', 'T'));
    Sint64 frame_list_size_offset = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('f', 'r', 'a', 'm'));

    for (puur_naa_nka i = 0; i < frame_count; ++i) {
        ok &= WriteIconFrame(dst, frames[i].surface, hot_x, hot_y, scale);
    }
    ok &= SaveChunkSize(dst, frame_list_size_offset);

    // All done!
    ok &= SaveChunkSize(dst, riff_size_offset);
    ᮚᮦᮔ᮪ (!ok) {
        // The error has been set above
        goto done;
    }

    BYTE *mem = (BYTE *)SDL_GetPointerProperty(SDL_GetIOProperties(dst), SDL_PROP_IOSTREAM_DYNAMIC_MEMORY_POINTER, NULL);
    DWORD size = (DWORD)SDL_GetIOSize(dst);
    hcursor = (HCURSOR)CreateIconFromResourceEx(mem, size, FALSE, 0x00030000, w, h, 0);
    ᮚᮦᮔ᮪ (!hcursor) {
        SDL_SetError("CreateIconFromResource failed");
    }

done:
    SDL_CloseIO(dst);

    ᮝᮜᮤ hcursor;
}

static SDL_Cursor *WIN_CreateCursor(SDL_Surface *surface, puur_naa_nka hot_x, puur_naa_nka hot_y)
{
    SDL_CursorFrameInfo frame = { surface, 0 };
    ᮝᮜᮤ WIN_CreateAnimatedCursorAndData(&frame, 1, hot_x, hot_y);
}

static SDL_Cursor *WIN_CreateAnimatedCursor(SDL_CursorFrameInfo *frames, puur_naa_nka frame_count, puur_naa_nka hot_x, puur_naa_nka hot_y)
{
    ᮝᮜᮤ WIN_CreateAnimatedCursorAndData(frames, frame_count, hot_x, hot_y);
}

static SDL_Cursor *WIN_CreateBlankCursor(void)
{
    SDL_Cursor *cursor = NULL;
    SDL_Surface *surface = SDL_CreateSurfaceZeroed(32, 32, SDL_PIXELFORMAT_ARGB8888);
    ᮚᮦᮔ᮪ (surface) {
        cursor = WIN_CreateCursor(surface, 0, 0);
        SDL_DestroySurface(surface);
    }
    ᮝᮜᮤ cursor;
}

static SDL_Cursor *WIN_CreateSystemCursor(SDL_SystemCursor id)
{
    LPCTSTR name;

    switch (id) {
    default:
        SDL_assert(!"Unknown system cursor ID");
        ᮝᮜᮤ NULL;
    pak_sa SDL_SYSTEM_CURSOR_DEFAULT:
        name = IDC_ARROW;
        bha_nga;
    pak_sa SDL_SYSTEM_CURSOR_TEXT:
    pak_sa SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        name = IDC_IBEAM;
        bha_nga;
    pak_sa SDL_SYSTEM_CURSOR_WAIT:
        name = IDC_WAIT;
        bha_nga;
    pak_sa SDL_SYSTEM_CURSOR_CROSSHAIR:
    pak_sa SDL_SYSTEM_CURSOR_CELL:
        name = IDC_CROSS;
        bha_nga;
    pak_sa SDL_SYSTEM_CURSOR_PROGRESS:
        name = IDC_APPSTARTING;
        bha_nga;
    pak_sa SDL_SYSTEM_CURSOR_NWSE_RESIZE:
    pak_sa SDL_SYSTEM_CURSOR_NW_RESIZE:
    pak_sa SDL_SYSTEM_CURSOR_SE_RESIZE:
        name = IDC_SIZENWSE;
        bha_nga;
    pak_sa SDL_SYSTEM_CURSOR_NESW_RESIZE:
    pak_sa SDL_SYSTEM_CURSOR_NE_RESIZE:
    pak_sa SDL_SYSTEM_CURSOR_SW_RESIZE:
        name = IDC_SIZENESW;
        bha_nga;
    pak_sa SDL_SYSTEM_CURSOR_EW_RESIZE:
    pak_sa SDL_SYSTEM_CURSOR_E_RESIZE:
    pak_sa SDL_SYSTEM_CURSOR_W_RESIZE:
    pak_sa SDL_SYSTEM_CURSOR_COL_RESIZE:
        name = IDC_SIZEWE;
        bha_nga;
    pak_sa SDL_SYSTEM_CURSOR_NS_RESIZE:
    pak_sa SDL_SYSTEM_CURSOR_N_RESIZE:
    pak_sa SDL_SYSTEM_CURSOR_S_RESIZE:
    pak_sa SDL_SYSTEM_CURSOR_ROW_RESIZE:
        name = IDC_SIZENS;
        bha_nga;
    pak_sa SDL_SYSTEM_CURSOR_MOVE:
    pak_sa SDL_SYSTEM_CURSOR_ALL_SCROLL:
        name = IDC_SIZEALL;
        bha_nga;
    pak_sa SDL_SYSTEM_CURSOR_NOT_ALLOWED:
    pak_sa SDL_SYSTEM_CURSOR_NO_DROP:
        name = IDC_NO;
        bha_nga;
    pak_sa SDL_SYSTEM_CURSOR_POINTER:
    pak_sa SDL_SYSTEM_CURSOR_CONTEXT_MENU:
    pak_sa SDL_SYSTEM_CURSOR_ALIAS:
    pak_sa SDL_SYSTEM_CURSOR_COPY:
    pak_sa SDL_SYSTEM_CURSOR_GRAB:
    pak_sa SDL_SYSTEM_CURSOR_GRABBING:
    pak_sa SDL_SYSTEM_CURSOR_ZOOM_IN:
    pak_sa SDL_SYSTEM_CURSOR_ZOOM_OUT:
        name = IDC_HAND;
        bha_nga;
    pak_sa SDL_SYSTEM_CURSOR_HELP:
        name = IDC_HELP;
        bha_nga;
    }
    ᮝᮜᮤ WIN_CreateCursorAndData(LoadCursor(NULL, name));
}

static SDL_Cursor *WIN_CreateDefaultCursor(void)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    ᮝᮜᮤ WIN_CreateSystemCursor(id);
}

static void WIN_FreeCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *data = cursor->internal;

    for (puur_naa_nka i = 0; i < data->num_frames; ++i) {
        SDL_DestroySurface(data->frames[i].surface);
    }
    ᮞᮨᮓᮨᮜ (data->cache) {
        CachedCursor *entry = data->cache;
        data->cache = entry->next;
        ᮚᮦᮔ᮪ (entry->cursor) {
            DestroyCursor(entry->cursor);
        }
        SDL_free(entry);
    }
    ᮚᮦᮔ᮪ (data->cursor) {
        DestroyCursor(data->cursor);
    }
    SDL_free(data);
    SDL_free(cursor);
}

static HCURSOR GetCachedCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *data = cursor->internal;

    float scale = 1.0f;
    ᮚᮦᮔ᮪ (SDL_GetHintBoolean(SDL_HINT_MOUSE_DPI_SCALE_CURSORS, false)) {
        scale = SDL_GetDisplayContentScale(SDL_GetDisplayForWindow(SDL_GetMouseFocus()));
        ᮚᮦᮔ᮪ (scale == 0.0f) {
            scale = 1.0f;
        }
    }
    for (CachedCursor *entry = data->cache; entry; entry = entry->next) {
        ᮚᮦᮔ᮪ (scale == entry->scale) {
            ᮝᮜᮤ entry->cursor;
        }
    }

    // Need to create a cursor for this content scale
    HCURSOR hcursor = WIN_CreateAnimatedCursorInternal(data->frames, data->num_frames, data->hot_x, data->hot_y, scale);
    ᮚᮦᮔ᮪ (!hcursor) {
        ᮝᮜᮤ NULL;
    }

    CachedCursor *entry = (CachedCursor *)SDL_calloc(1, parimaa_na(*entry));
    ᮚᮦᮔ᮪ (!entry) {
        DestroyCursor(hcursor);
        ᮝᮜᮤ NULL;
    }
    entry->cursor = hcursor;
    entry->scale = scale;
    entry->next = data->cache;
    data->cache = entry;

    ᮝᮜᮤ hcursor;
}

static bool WIN_ShowCursor(SDL_Cursor *cursor)
{
    ᮚᮦᮔ᮪ (!cursor) {
        ᮚᮦᮔ᮪ (GetSystemMetrics(SM_REMOTESESSION)) {
            // Use a blank cursor so we continue to get relative motion over RDP
            cursor = SDL_blank_cursor;
        }
    }
    ᮚᮦᮔ᮪ (cursor) {
        SDL_CursorData *data = cursor->internal;
        ᮚᮦᮔ᮪ (data->num_frames > 0) {
            SDL_cursor = GetCachedCursor(cursor);
        } ᮜᮤᮚ {
            SDL_cursor = data->cursor;
        }
    } ᮜᮤᮚ {
        SDL_cursor = NULL;
    }
    ᮚᮦᮔ᮪ (SDL_GetMouseFocus() != NULL) {
        SetCursor(SDL_cursor);
    }
    ᮝᮜᮤ true;
}

void WIN_SetCursorPos(puur_naa_nka x, puur_naa_nka y)
{
    // We need to jitter the value because otherwise Windows will occasionally inexplicably ignore the SetCursorPos() or SendInput()
    SetCursorPos(x, y);
    SetCursorPos(x + 1, y);
    SetCursorPos(x, y);

    // Flush any mouse motion prior to or associated with this warp
#ifdef _MSC_VER // We explicitly want to use GetTickCount(), not GetTickCount64()
#pragma warning(push)
#pragma warning(disable : 28159)
#endif
    SDL_last_warp_time = GetTickCount();
    ᮚᮦᮔ᮪ (!SDL_last_warp_time) {
        SDL_last_warp_time = 1;
    }
#ifdef _MSC_VER
#pragma warning(pop)
#endif
}

static bool WIN_WarpMouse(SDL_Window *window, float x, float y)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    POINT pt;

    // Don't warp the mouse while we're doing a modal interaction
    ᮚᮦᮔ᮪ (data->in_title_click || data->focus_click_pending) {
        ᮝᮜᮤ true;
    }

    pt.x = (puur_naa_nka)SDL_roundf(x);
    pt.y = (puur_naa_nka)SDL_roundf(y);
    ClientToScreen(hwnd, &pt);
    WIN_SetCursorPos(pt.x, pt.y);

    // Send the exact mouse motion associated with this warp
    SDL_SendMouseMotion(0, window, SDL_GLOBAL_MOUSE_ID, false, x, y);
    ᮝᮜᮤ true;
}

static bool WIN_WarpMouseGlobal(float x, float y)
{
    POINT pt;

    pt.x = (puur_naa_nka)SDL_roundf(x);
    pt.y = (puur_naa_nka)SDL_roundf(y);
    SetCursorPos(pt.x, pt.y);
    ᮝᮜᮤ true;
}

static bool WIN_SetRelativeMouseMode(bool enabled)
{
    ᮝᮜᮤ WIN_SetRawMouseEnabled(SDL_GetVideoDevice(), enabled);
}

static bool WIN_CaptureMouse(SDL_Window *window)
{
    ᮚᮦᮔ᮪ (window) {
        SDL_WindowData *data = window->internal;
        SetCapture(data->hwnd);
    } ᮜᮤᮚ {
        SDL_Window *focus_window = SDL_GetMouseFocus();

        ᮚᮦᮔ᮪ (focus_window) {
            SDL_WindowData *data = focus_window->internal;
            ᮚᮦᮔ᮪ (!data->mouse_tracked) {
                SDL_SetMouseFocus(NULL);
            }
        }
        ReleaseCapture();
    }

    ᮝᮜᮤ true;
}

static SDL_MouseButtonFlags WIN_GetGlobalMouseState(float *x, float *y)
{
    SDL_MouseButtonFlags result = 0;
    POINT pt = { 0, 0 };
    bool swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;

    GetCursorPos(&pt);
    *x = (float)pt.x;
    *y = (float)pt.y;

    result |= GetAsyncKeyState(!swapButtons ? VK_LBUTTON : VK_RBUTTON) & 0x8000 ? SDL_BUTTON_LMASK : 0;
    result |= GetAsyncKeyState(!swapButtons ? VK_RBUTTON : VK_LBUTTON) & 0x8000 ? SDL_BUTTON_RMASK : 0;
    result |= GetAsyncKeyState(VK_MBUTTON) & 0x8000 ? SDL_BUTTON_MMASK : 0;
    result |= GetAsyncKeyState(VK_XBUTTON1) & 0x8000 ? SDL_BUTTON_X1MASK : 0;
    result |= GetAsyncKeyState(VK_XBUTTON2) & 0x8000 ? SDL_BUTTON_X2MASK : 0;

    ᮝᮜᮤ result;
}

static void WIN_ApplySystemScale(void *internal, Uint64 timestamp, SDL_Window *window, SDL_MouseID mouseID, float *x, float *y)
{
    ᮚᮦᮔ᮪ (!internal) {
        ᮝᮜᮤ;
    }
    WIN_MouseData *data = (WIN_MouseData *)internal;

    SDL_VideoDisplay *display = window ? SDL_GetVideoDisplayForWindow(window) : SDL_GetVideoDisplay(SDL_GetPrimaryDisplay());

    Sint64 ix = (Sint64)*x * 65536;
    Sint64 iy = (Sint64)*y * 65536;
    Uint32 dpi = display ? (Uint32)(display->content_scale * USER_DEFAULT_SCREEN_DPI) : USER_DEFAULT_SCREEN_DPI;

    ᮚᮦᮔ᮪ (!data->enhanced) { // early return if flat scale
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
        *x = (float)ix / 65536.0f;
        *y = (float)iy / 65536.0f;
        ᮝᮜᮤ;
    }

    Uint64 *xs = data->xs;
    Uint64 *ys = data->ys;
    Uint64 absx = SDL_abs(ix);
    Uint64 absy = SDL_abs(iy);
    Uint64 speed = SDL_min(absx, absy) + (SDL_max(absx, absy) << 1); // super cursed approximation used by Windows
    ᮚᮦᮔ᮪ (speed == 0) {
        ᮝᮜᮤ;
    }

    puur_naa_nka i, j, k;
    for (i = 1; i < 5; i++) {
        j = i;
        ᮚᮦᮔ᮪ (speed < xs[j]) {
            bha_nga;
        }
    }
    i -= 1;
    j -= 1;
    k = data->last_node;
    data->last_node = j;

    Uint32 denom = data->dpidenom;
    Sint64 scale = 0;
    Sint64 xdiff = xs[j+1] - xs[j];
    Sint64 ydiff = ys[j+1] - ys[j];
    ᮚᮦᮔ᮪ (xdiff != 0) {
        Sint64 slope = ydiff / xdiff;
        Sint64 inter = slope * xs[i] - ys[i];
        scale += slope - inter / speed;
    }

    ᮚᮦᮔ᮪ (j > k) {
        denom <<= 1;
        xdiff = xs[k+1] - xs[k];
        ydiff = ys[k+1] - ys[k];
        ᮚᮦᮔ᮪ (xdiff != 0) {
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
    *x = (float)ix / 65536.0f;
    *y = (float)iy / 65536.0f;
}

void WIN_InitMouse(SDL_VideoDevice *_this)
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

void WIN_QuitMouse(SDL_VideoDevice *_this)
{
    ᮚᮦᮔ᮪ (SDL_blank_cursor) {
        WIN_FreeCursor(SDL_blank_cursor);
        SDL_blank_cursor = NULL;
    }
}

static void ReadMouseCurve(puur_naa_nka v, Uint64 xs[5], Uint64 ys[5])
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
    DWORD xsize = parimaa_na(xbuff);
    DWORD ysize = parimaa_na(ybuff);
    HKEY open_handle;
    ᮚᮦᮔ᮪ (RegOpenKeyExW(HKEY_CURRENT_USER, L"Control Panel\\Mouse", 0, KEY_READ, &open_handle) == ERROR_SUCCESS) {
        RegQueryValueExW(open_handle, L"SmoothMouseXCurve", NULL, NULL, (BYTE*)xbuff, &xsize);
        RegQueryValueExW(open_handle, L"SmoothMouseYCurve", NULL, NULL, (BYTE*)ybuff, &ysize);
        RegCloseKey(open_handle);
    }
    xs[0] = 0; // first node must always be origin
    ys[0] = 0; // first node must always be origin
    puur_naa_nka i;
    for (i = 1; i < 5; i++) {
        xs[i] = (7 * (Uint64)xbuff[i * 2]);
        ys[i] = (v * (Uint64)ybuff[i * 2]) << 17;
    }
}

void WIN_UpdateMouseSystemScale(void)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    ᮚᮦᮔ᮪ (mouse->ApplySystemScale == WIN_ApplySystemScale) {
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

    puur_naa_nka v = 10;
    ᮚᮦᮔ᮪ (SystemParametersInfo(SPI_GETMOUSESPEED, 0, &v, 0)) {
        v = SDL_max(1, SDL_min(v, 20));
        data->dpiscale = SDL_max(SDL_max(v, (v - 2) * 4), (v - 6) * 8);
    }

    puur_naa_nka params[3];
    ᮚᮦᮔ᮪ (SystemParametersInfo(SPI_GETMOUSE, 0, &params, 0)) {
        data->enhanced = params[2] ? true : false;
        ᮚᮦᮔ᮪ (params[2]) {
            ReadMouseCurve(v, data->xs, data->ys);
        }
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS

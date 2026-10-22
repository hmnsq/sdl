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
#અન્તર્ભાવ "SDL_internal.h"

#જો defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#અન્તર્ભાવ "SDL_windowsvideo.h"
#અન્તર્ભાવ "SDL_windowsevents.h"
#અન્તર્ભાવ "SDL_windowsrawinput.h"

#અન્તર્ભાવ "../SDL_video_c.h"
#અન્તર્ભાવ "../../events/SDL_mouse_c.h"
#અન્તર્ભાવ "../../joystick/usb_ids.h"
#અન્તર્ભાવ "../../core/windows/SDL_windows.h" // for checking windows version

#define RIFF_FOURCC(c0, c1, c2, c3)                 \
    ((DWORD)(BYTE)(c0) | ((DWORD)(BYTE)(c1) << 8) | \
     ((DWORD)(BYTE)(c2) << 16) | ((DWORD)(BYTE)(c3) << 24))

#define ANI_FLAG_ICON 0x1

#pragma pack(ધકેલો, 1)

પ્રકારવ્યાખ્યા સંરચના
{
    BYTE bWidth;
    BYTE bHeight;
    BYTE b_Color_ગણતરી;
    BYTE bReserved;
    WORD xHotspot;
    WORD yHotspot;
    DWORD dwImageSize;
    DWORD dwImageOffset;
} CURSORICONFILEDIRENTRY;

પ્રકારવ્યાખ્યા સંરચના
{
    WORD idReserved;
    WORD idType;
    WORD id_ગણતરી;
} CURSORICONFILEDIR;

પ્રકારવ્યાખ્યા સંરચના
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

#pragma pack(કાઢો)

પ્રકારવ્યાખ્યા સંરચના CachedCursor
{
    દશાંશ scale;
    HCURSOR cursor;
    સંરચના CachedCursor *next;
} CachedCursor;

સંરચના SDL_CursorData
{
    HCURSOR cursor;

    CachedCursor *cache;
    પૂર્ણાંક hot_x;
    પૂર્ણાંક hot_y;
    પૂર્ણાંક અંક_frames;
    SDL_CursorFrameInfo frames[1];
};

પ્રકારવ્યાખ્યા સંરચના
{
    Uint64 xs[5];
    Uint64 ys[5];
    Sint64 residual[2];
    Uint32 dpiscale;
    Uint32 dpidenom;
    પૂર્ણાંક last_ગાંઠ;
    bool enhanced;
    bool dpiaware;
} WIN_MouseData;

DWORD SDL_last_warp_time = 0;
HCURSOR SDL_cursor = ખાલી;
સ્થિર SDL_Cursor *SDL_blank_cursor = ખાલી;
સ્થિર WIN_MouseData WIN_system_scale_data;

સ્થિર SDL_Cursor *WIN_CreateCursorAndData(HCURSOR hcursor)
{
    જો (!hcursor) {
        પાછા ખાલી;
    }

    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, કદ(*cursor));
    જો (!cursor) {
        પાછા ખાલી;
    }

    SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, કદ(*data));
    જો (!data) {
        SDL_free(cursor);
        પાછા ખાલી;
    }

    data->cursor = hcursor;
    cursor->internal = data;
    પાછા cursor;
}

સ્થિર SDL_Cursor *WIN_CreateAnimatedCursorAndData(SDL_CursorFrameInfo *frames, પૂર્ણાંક frame_ગણતરી, પૂર્ણાંક hot_x, પૂર્ણાંક hot_y)
{
    // Dynamically generate cursors at the appropriate DPI
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, કદ(*cursor));
    જો (!cursor) {
        પાછા ખાલી;
    }

    SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, કદ(*data) + (કદ(SDL_CursorFrameInfo) * (frame_ગણતરી - 1)));
    જો (!data) {
        SDL_free(cursor);
        પાછા ખાલી;
    }

    data->hot_x = hot_x;
    data->hot_y = hot_y;
    data->અંક_frames = frame_ગણતરી;
    માટે (પૂર્ણાંક i = 0; i < frame_ગણતરી; ++i) {
        SDL_Surface *surface = frames[i].surface;
        જો (surface->flags & SDL_SURFACE_PREALLOCATED) {
            surface = SDL_DuplicateSurface(surface);
            જો (!surface) {
                જ્યારે (i > 0) {
                    --i;
                    SDL_DestroySurface(data->frames[i].surface);
                }
                SDL_free(data);
                SDL_free(cursor);
                પાછા ખાલી;
            }
        } નહીંતર {
            ++surface->refcount;
        }
        data->frames[i].surface = surface;
        data->frames[i].duration = frames[i].duration;
    }
    cursor->internal = data;
    પાછા cursor;
}

સ્થિર bool SaveChunkSize(SDL_IOStream* dst, Sint64 offset)
{
    Sint64 here = SDL_TellIO(dst);
    જો (here < 0) {
        પાછા false;
    }
    જો (SDL_SeekIO(dst, offset, SDL_IO_SEEK_SET) < 0) {
        પાછા false;
    }

    DWORD size = (DWORD)(here - (offset + કદ(DWORD)));
    જો (!SDL_WriteU32LE(dst, size)) {
        પાછા false;
    }
    પાછા SDL_SeekIO(dst, here, SDL_IO_SEEK_SET);
}

સ્થિર bool FillIconEntry(CURSORICONFILEDIRENTRY *entry, SDL_Surface *surface, પૂર્ણાંક hot_x, પૂર્ણાંક hot_y, DWORD dwImageSize, DWORD dwImageOffset)
{
    જો (surface->props) {
        hot_x = (પૂર્ણાંક)SDL_Get_સંખ્યા_Property(surface->props, SDL_PROP_SURFACE_HOTSPOT_X_સંખ્યા, hot_x);
        hot_y = (પૂર્ણાંક)SDL_Get_સંખ્યા_Property(surface->props, SDL_PROP_SURFACE_HOTSPOT_Y_સંખ્યા, hot_y);
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
    પાછા true;
}

#ifdef SAVE_ICON_PNG

સ્થિર bool WriteIconSurface(SDL_IOStream *dst, SDL_Surface *surface)
{
    જો (!SDL_SavePNG_IO(surface, dst, false)) {
        પાછા false;
    }

    // Image data offsets must be WORD aligned
    Sint64 offset = SDL_TellIO(dst);
    જો (offset & 1) {
        જો (!SDL_WriteU8(dst, 0)) {
            પાછા false;
        }
    }
    પાછા true;
}

#નહીંતર

/* For info on the expected mask format see:
 * https://devblogs.microsoft.com/oldnewthing/20101018-00/?p=12513
 */
સ્થિર શૂન્ય *CreateIconMask(SDL_Surface *surface, size_t *mask_size)
{
    Uint8 *dst;
    અચલ પૂર્ણાંક w = (surface->w + 7) / 8;
    અચલ પૂર્ણાંક pad = (((w) % 4) ? (4 - ((w) % 4)) : 0);
    અચલ પૂર્ણાંક pitch = (w + pad);
    અચલ size_t size = pitch * surface->h;
    સ્થિર અચલ unsigned અક્ષર masks[] = { 0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1 };

    શૂન્ય *mask = SDL_malloc(size);
    જો (!mask) {
        પાછા ખાલી;
    }

    dst = (Uint8 *)mask;

    // Make the mask completely transparent.
    SDL_memset(dst, 0xff, size);
    માટે (પૂર્ણાંક y = surface->h - 1; y >= 0; --y, dst += pitch) {
        માટે (પૂર્ણાંક x = 0; x < surface->w; ++x) {
            Uint8 r, g, b, a;
            SDL_ReadSurfacePixel(surface, x, y, &r, &g, &b, &a);

            જો (a != 0) {
                // Reset bit of an opaque pixel.
                dst[x >> 3] &= ~masks[x & 7];
            }
        }
    }
    *mask_size = size;
    પાછા mask;
}

સ્થિર bool WriteIconSurface(SDL_IOStream *dst, SDL_Surface *surface)
{
    SDL_Surface *temp = ખાલી;

    જો (surface->format != SDL_PIXELFORMAT_ARGB8888) {
        temp = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        જો (!temp) {
            પાછા false;
        }
        surface = temp;
    }

    // Cursor data is double height (DIB and mask), stored bottom-up
    bool ok = true;
    size_t mask_size = 0;
    શૂન્ય *mask = CreateIconMask(surface, &mask_size);
    જો (!mask) {
        ok = false;
        જાઓ done;
    }

    BITMAPINFOHEADER bmih;
    SDL_zero(bmih);
    DWORD row_size = surface->w * 4;
    bmih.biSize = કદ(BITMAPINFOHEADER);
    bmih.biWidth = surface->w;
    bmih.biHeight = surface->h * 2;
    bmih.biPlanes = 1;
    bmih.bi_Bit_ગણતરી = 32;
    bmih.biCompression = BI_RGB;
    bmih.biSizeImage = (DWORD)(surface->h * row_size + mask_size);
    ok &= (SDL_WriteIO(dst, &bmih, કદ(bmih)) == કદ(bmih));

    અચલ Uint8 *pix = surface->pixels;
    pix += (surface->h - 1) * surface->pitch;
    માટે (પૂર્ણાંક i = 0; i < surface->h; ++i) {
        ok &= (SDL_WriteIO(dst, pix, row_size) == row_size);
        pix -= surface->pitch;
    }
    ok &= (SDL_WriteIO(dst, mask, mask_size) == mask_size);

done:
    SDL_free(mask);
    SDL_DestroySurface(temp);
    પાછા ok;
}

#endif // SAVE_ICON_PNG

સ્થિર bool WriteIconFrame(SDL_IOStream *dst, SDL_Surface *surface, પૂર્ણાંક hot_x, પૂર્ણાંક hot_y, દશાંશ scale)
{
#ifdef SAVE_MULTIPLE_ICONS
    પૂર્ણાંક ગણતરી = 0;
    SDL_Surface **surfaces = SDL_GetSurfaceImages(surface, &ગણતરી);
    જો (!surfaces) {
        પાછા false;
    }
#નહીંતર
    surface = SDL_GetSurfaceImage(surface, scale);
    જો (!surface) {
        પાછા false;
    }

    પૂર્ણાંક ગણતરી = 1;
    SDL_Surface **surfaces = &surface;
#endif

    // Raymond Chen has more insight into this format at:
    // https://devblogs.microsoft.com/oldnewthing/20101018-00/?p=12513
    bool ok = true;
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('i', 'c', 'o', 'n'));
    Sint64 icon_size_offset = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    Sint64 base_offset = icon_size_offset + કદ(DWORD);

    CURSORICONFILEDIR dir;
    dir.idReserved = 0;
    dir.idType = 2; // Cursor
    dir.id_ગણતરી = ગણતરી;
    ok &= (SDL_WriteIO(dst, &dir, કદ(dir)) == કદ(dir));

    DWORD entries_size = ગણતરી * કદ(CURSORICONFILEDIRENTRY);
    CURSORICONFILEDIRENTRY *entries = (CURSORICONFILEDIRENTRY *)SDL_malloc(entries_size);
    જો (!entries) {
        ok = false;
        જાઓ done;
    }
    ok &= (SDL_WriteIO(dst, entries, entries_size) == entries_size);

    Sint64 image_offset = SDL_TellIO(dst);
    માટે (પૂર્ણાંક i = 0; i < ગણતરી; ++i) {
        ok &= WriteIconSurface(dst, surfaces[i]);

        Sint64 next_offset = SDL_TellIO(dst);
        DWORD dwImageSize = (DWORD)(next_offset - image_offset);
        DWORD dwImageOffset = (DWORD)(image_offset - base_offset);

        ok &= FillIconEntry(&entries[i], surfaces[i], hot_x, hot_y, dwImageSize, dwImageOffset);

        image_offset = next_offset;
    }

    // Now that we have the icon entries filled out, rewrite them
    ok &= (SDL_SeekIO(dst, base_offset + કદ(dir), SDL_IO_SEEK_SET) >= 0);
    ok &= (SDL_WriteIO(dst, entries, entries_size) == entries_size);
    ok &= (SDL_SeekIO(dst, image_offset, SDL_IO_SEEK_SET) >= 0);
    SDL_free(entries);

    ok &= SaveChunkSize(dst, icon_size_offset);

done:
#ifdef SAVE_MULTIPLE_ICONS
    SDL_free(surfaces);
#નહીંતર
    SDL_DestroySurface(surface);
#endif
    પાછા ok;
}

/* Windows doesn't have an API to easily create animated cursors from a sequence of images,
 * so we have to build an animated cursor resource file in memory and load it.
 */
સ્થિર HCURSOR WIN_CreateAnimatedCursorInternal(SDL_CursorFrameInfo *frames, પૂર્ણાંક frame_ગણતરી, પૂર્ણાંક hot_x, પૂર્ણાંક hot_y, દશાંશ scale)
{
    HCURSOR hcursor = ખાલી;
    SDL_IOStream *dst = SDL_IOFromDynamicMem();
    જો (!dst) {
        પાછા ખાલી;
    }

    પૂર્ણાંક w = (પૂર્ણાંક)SDL_roundf(frames[0].surface->w * scale);
    પૂર્ણાંક h = (પૂર્ણાંક)SDL_roundf(frames[0].surface->h * scale);

    bool ok = true;
    // RIFF header
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('R', 'I', 'F', 'F'));
    Sint64 riff_size_offset = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('A', 'C', 'O', 'N'));

    // anih header chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('a', 'n', 'i', 'h'));
    ok &= SDL_WriteU32LE(dst, કદ(ANIHEADER));

    ANIHEADER anih;
    SDL_zero(anih);
    anih.cbSizeof = કદ(anih);
    anih.frames = frame_ગણતરી;
    anih.steps = frame_ગણતરી;
    anih.jifRate = 1;
    anih.fl = ANI_FLAG_ICON;
    ok &= (SDL_WriteIO(dst, &anih, કદ(anih)) == કદ(anih));

    // Rate chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('r', 'a', 't', 'e'));
    ok &= SDL_WriteU32LE(dst, કદ(DWORD) * frame_ગણતરી);
    માટે (પૂર્ણાંક i = 0; i < frame_ગણતરી; ++i) {
        // Animated Win32 cursors are in jiffy units, and one jiffy is 1/60 of a second.
        અચલ દ્વિગુણ WIN32_JIFFY = 1000.0 / 60.0;
        DWORD duration = (frames[i].duration ? SDL_lround(frames[i].duration / WIN32_JIFFY) : 0xFFFFFFFF);
        ok &= SDL_WriteU32LE(dst, duration);
    }

    // Frame list
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('L', 'I', 'S', 'T'));
    Sint64 frame_list_size_offset = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('f', 'r', 'a', 'm'));

    માટે (પૂર્ણાંક i = 0; i < frame_ગણતરી; ++i) {
        ok &= WriteIconFrame(dst, frames[i].surface, hot_x, hot_y, scale);
    }
    ok &= SaveChunkSize(dst, frame_list_size_offset);

    // All done!
    ok &= SaveChunkSize(dst, riff_size_offset);
    જો (!ok) {
        // The error has been set above
        જાઓ done;
    }

    BYTE *mem = (BYTE *)SDL_GetPointerProperty(SDL_GetIOProperties(dst), SDL_PROP_IOSTREAM_DYNAMIC_MEMORY_POINTER, ખાલી);
    DWORD size = (DWORD)SDL_GetIOSize(dst);
    hcursor = (HCURSOR)CreateIconFromResourceEx(mem, size, FALSE, 0x00030000, w, h, 0);
    જો (!hcursor) {
        SDL_SetError("CreateIconFromResource failed");
    }

done:
    SDL_CloseIO(dst);

    પાછા hcursor;
}

સ્થિર SDL_Cursor *WIN_CreateCursor(SDL_Surface *surface, પૂર્ણાંક hot_x, પૂર્ણાંક hot_y)
{
    SDL_CursorFrameInfo frame = { surface, 0 };
    પાછા WIN_CreateAnimatedCursorAndData(&frame, 1, hot_x, hot_y);
}

સ્થિર SDL_Cursor *WIN_CreateAnimatedCursor(SDL_CursorFrameInfo *frames, પૂર્ણાંક frame_ગણતરી, પૂર્ણાંક hot_x, પૂર્ણાંક hot_y)
{
    પાછા WIN_CreateAnimatedCursorAndData(frames, frame_ગણતરી, hot_x, hot_y);
}

સ્થિર SDL_Cursor *WIN_CreateBlankCursor(શૂન્ય)
{
    SDL_Cursor *cursor = ખાલી;
    SDL_Surface *surface = SDL_CreateSurfaceZeroed(32, 32, SDL_PIXELFORMAT_ARGB8888);
    જો (surface) {
        cursor = WIN_CreateCursor(surface, 0, 0);
        SDL_DestroySurface(surface);
    }
    પાછા cursor;
}

સ્થિર SDL_Cursor *WIN_CreateSystemCursor(SDL_SystemCursor id)
{
    LPCTSTR name;

    પસંદગી (id) {
    મૂળભૂત:
        SDL_assert(!"Unknown system cursor ID");
        પાછા ખાલી;
    સ્થિતિ SDL_SYSTEM_CURSOR_DEFAULT:
        name = IDC_ARROW;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_TEXT:
    સ્થિતિ SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        name = IDC_IBEAM;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_WAIT:
        name = IDC_WAIT;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_CROSSHAIR:
    સ્થિતિ SDL_SYSTEM_CURSOR_CELL:
        name = IDC_CROSS;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_PROGRESS:
        name = IDC_APPSTARTING;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_NWSE_RESIZE:
    સ્થિતિ SDL_SYSTEM_CURSOR_NW_RESIZE:
    સ્થિતિ SDL_SYSTEM_CURSOR_SE_RESIZE:
        name = IDC_SIZENWSE;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_NESW_RESIZE:
    સ્થિતિ SDL_SYSTEM_CURSOR_NE_RESIZE:
    સ્થિતિ SDL_SYSTEM_CURSOR_SW_RESIZE:
        name = IDC_SIZENESW;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_EW_RESIZE:
    સ્થિતિ SDL_SYSTEM_CURSOR_E_RESIZE:
    સ્થિતિ SDL_SYSTEM_CURSOR_W_RESIZE:
    સ્થિતિ SDL_SYSTEM_CURSOR_COL_RESIZE:
        name = IDC_SIZEWE;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_NS_RESIZE:
    સ્થિતિ SDL_SYSTEM_CURSOR_N_RESIZE:
    સ્થિતિ SDL_SYSTEM_CURSOR_S_RESIZE:
    સ્થિતિ SDL_SYSTEM_CURSOR_ROW_RESIZE:
        name = IDC_SIZENS;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_MOVE:
    સ્થિતિ SDL_SYSTEM_CURSOR_ALL_SCROLL:
        name = IDC_SIZEALL;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_NOT_ALLOWED:
    સ્થિતિ SDL_SYSTEM_CURSOR_NO_DROP:
        name = IDC_NO;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_POINTER:
    સ્થિતિ SDL_SYSTEM_CURSOR_CONTEXT_MENU:
    સ્થિતિ SDL_SYSTEM_CURSOR_ALIAS:
    સ્થિતિ SDL_SYSTEM_CURSOR_COPY:
    સ્થિતિ SDL_SYSTEM_CURSOR_GRAB:
    સ્થિતિ SDL_SYSTEM_CURSOR_GRABBING:
    સ્થિતિ SDL_SYSTEM_CURSOR_ZOOM_IN:
    સ્થિતિ SDL_SYSTEM_CURSOR_ZOOM_OUT:
        name = IDC_HAND;
        તોડો;
    સ્થિતિ SDL_SYSTEM_CURSOR_HELP:
        name = IDC_HELP;
        તોડો;
    }
    પાછા WIN_CreateCursorAndData(LoadCursor(ખાલી, name));
}

સ્થિર SDL_Cursor *WIN_CreateDefaultCursor(શૂન્ય)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    પાછા WIN_CreateSystemCursor(id);
}

સ્થિર શૂન્ય WIN_FreeCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *data = cursor->internal;

    માટે (પૂર્ણાંક i = 0; i < data->અંક_frames; ++i) {
        SDL_DestroySurface(data->frames[i].surface);
    }
    જ્યારે (data->cache) {
        CachedCursor *entry = data->cache;
        data->cache = entry->next;
        જો (entry->cursor) {
            DestroyCursor(entry->cursor);
        }
        SDL_free(entry);
    }
    જો (data->cursor) {
        DestroyCursor(data->cursor);
    }
    SDL_free(data);
    SDL_free(cursor);
}

સ્થિર HCURSOR GetCachedCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *data = cursor->internal;

    દશાંશ scale = 1.0f;
    જો (SDL_GetHintBoolean(SDL_HINT_MOUSE_DPI_SCALE_CURSORS, false)) {
        scale = SDL_GetDisplayContentScale(SDL_GetDisplayForWindow(SDL_GetMouseFocus()));
        જો (scale == 0.0f) {
            scale = 1.0f;
        }
    }
    માટે (CachedCursor *entry = data->cache; entry; entry = entry->next) {
        જો (scale == entry->scale) {
            પાછા entry->cursor;
        }
    }

    // Need to create a cursor for this content scale
    HCURSOR hcursor = WIN_CreateAnimatedCursorInternal(data->frames, data->અંક_frames, data->hot_x, data->hot_y, scale);
    જો (!hcursor) {
        પાછા ખાલી;
    }

    CachedCursor *entry = (CachedCursor *)SDL_calloc(1, કદ(*entry));
    જો (!entry) {
        DestroyCursor(hcursor);
        પાછા ખાલી;
    }
    entry->cursor = hcursor;
    entry->scale = scale;
    entry->next = data->cache;
    data->cache = entry;

    પાછા hcursor;
}

સ્થિર bool WIN_ShowCursor(SDL_Cursor *cursor)
{
    જો (!cursor) {
        જો (GetSystemMetrics(SM_REMOTESESSION)) {
            // Use a blank cursor so we continue to get relative motion over RDP
            cursor = SDL_blank_cursor;
        }
    }
    જો (cursor) {
        SDL_CursorData *data = cursor->internal;
        જો (data->અંક_frames > 0) {
            SDL_cursor = GetCachedCursor(cursor);
        } નહીંતર {
            SDL_cursor = data->cursor;
        }
    } નહીંતર {
        SDL_cursor = ખાલી;
    }
    જો (SDL_GetMouseFocus() != ખાલી) {
        SetCursor(SDL_cursor);
    }
    પાછા true;
}

શૂન્ય WIN_SetCursorPos(પૂર્ણાંક x, પૂર્ણાંક y)
{
    // We need to jitter the value because otherwise Windows will occasionally inexplicably ignore the SetCursorPos() or SendInput()
    SetCursorPos(x, y);
    SetCursorPos(x + 1, y);
    SetCursorPos(x, y);

    // Flush any mouse motion prior to or associated with this warp
#ifdef _MSC_VER // We explicitly want to use GetTickCount(), not GetTickCount64()
#pragma warning(ધકેલો)
#pragma warning(disable : 28159)
#endif
    SDL_last_warp_time = Get_Tick_ગણતરી();
    જો (!SDL_last_warp_time) {
        SDL_last_warp_time = 1;
    }
#ifdef _MSC_VER
#pragma warning(કાઢો)
#endif
}

સ્થિર bool WIN_WarpMouse(SDL_Window *window, દશાંશ x, દશાંશ y)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    POINT pt;

    // Don't warp the mouse while we're doing a modal interaction
    જો (data->in_title_click || data->focus_click_pending) {
        પાછા true;
    }

    pt.x = (પૂર્ણાંક)SDL_roundf(x);
    pt.y = (પૂર્ણાંક)SDL_roundf(y);
    ClientToScreen(hwnd, &pt);
    WIN_SetCursorPos(pt.x, pt.y);

    // Send the exact mouse motion associated with this warp
    SDL_SendMouseMotion(0, window, SDL_GLOBAL_MOUSE_ID, false, x, y);
    પાછા true;
}

સ્થિર bool WIN_WarpMouseGlobal(દશાંશ x, દશાંશ y)
{
    POINT pt;

    pt.x = (પૂર્ણાંક)SDL_roundf(x);
    pt.y = (પૂર્ણાંક)SDL_roundf(y);
    SetCursorPos(pt.x, pt.y);
    પાછા true;
}

સ્થિર bool WIN_SetRelativeMouseMode(bool enabled)
{
    પાછા WIN_SetRawMouseEnabled(SDL_GetVideoDevice(), enabled);
}

સ્થિર bool WIN_CaptureMouse(SDL_Window *window)
{
    જો (window) {
        SDL_WindowData *data = window->internal;
        SetCapture(data->hwnd);
    } નહીંતર {
        SDL_Window *focus_window = SDL_GetMouseFocus();

        જો (focus_window) {
            SDL_WindowData *data = focus_window->internal;
            જો (!data->mouse_tracked) {
                SDL_SetMouseFocus(ખાલી);
            }
        }
        ReleaseCapture();
    }

    પાછા true;
}

સ્થિર SDL_MouseButtonFlags WIN_GetGlobalMouseState(દશાંશ *x, દશાંશ *y)
{
    SDL_MouseButtonFlags result = 0;
    POINT pt = { 0, 0 };
    bool swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;

    GetCursorPos(&pt);
    *x = (દશાંશ)pt.x;
    *y = (દશાંશ)pt.y;

    result |= Get_Async_ચાવી_State(!swapButtons ? VK_LBUTTON : VK_RBUTTON) & 0x8000 ? SDL_BUTTON_LMASK : 0;
    result |= Get_Async_ચાવી_State(!swapButtons ? VK_RBUTTON : VK_LBUTTON) & 0x8000 ? SDL_BUTTON_RMASK : 0;
    result |= Get_Async_ચાવી_State(VK_MBUTTON) & 0x8000 ? SDL_BUTTON_MMASK : 0;
    result |= Get_Async_ચાવી_State(VK_XBUTTON1) & 0x8000 ? SDL_BUTTON_X1MASK : 0;
    result |= Get_Async_ચાવી_State(VK_XBUTTON2) & 0x8000 ? SDL_BUTTON_X2MASK : 0;

    પાછા result;
}

સ્થિર શૂન્ય WIN_ApplySystemScale(શૂન્ય *internal, Uint64 timestamp, SDL_Window *window, SDL_MouseID mouseID, દશાંશ *x, દશાંશ *y)
{
    જો (!internal) {
        પાછા;
    }
    WIN_MouseData *data = (WIN_MouseData *)internal;

    SDL_VideoDisplay *display = window ? SDL_GetVideoDisplayForWindow(window) : SDL_GetVideoDisplay(SDL_GetPrimaryDisplay());

    Sint64 ix = (Sint64)*x * 65536;
    Sint64 iy = (Sint64)*y * 65536;
    Uint32 dpi = display ? (Uint32)(display->content_scale * USER_DEFAULT_SCREEN_DPI) : USER_DEFAULT_SCREEN_DPI;

    જો (!data->enhanced) { // early return if flat scale
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
        *x = (દશાંશ)ix / 65536.0f;
        *y = (દશાંશ)iy / 65536.0f;
        પાછા;
    }

    Uint64 *xs = data->xs;
    Uint64 *ys = data->ys;
    Uint64 absx = SDL_abs(ix);
    Uint64 absy = SDL_abs(iy);
    Uint64 speed = SDL_min(absx, absy) + (SDL_max(absx, absy) << 1); // super cursed approximation used by Windows
    જો (speed == 0) {
        પાછા;
    }

    પૂર્ણાંક i, j, k;
    માટે (i = 1; i < 5; i++) {
        j = i;
        જો (speed < xs[j]) {
            તોડો;
        }
    }
    i -= 1;
    j -= 1;
    k = data->last_ગાંઠ;
    data->last_ગાંઠ = j;

    Uint32 denom = data->dpidenom;
    Sint64 scale = 0;
    Sint64 xdiff = xs[j+1] - xs[j];
    Sint64 ydiff = ys[j+1] - ys[j];
    જો (xdiff != 0) {
        Sint64 slope = ydiff / xdiff;
        Sint64 inter = slope * xs[i] - ys[i];
        scale += slope - inter / speed;
    }

    જો (j > k) {
        denom <<= 1;
        xdiff = xs[k+1] - xs[k];
        ydiff = ys[k+1] - ys[k];
        જો (xdiff != 0) {
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
    *x = (દશાંશ)ix / 65536.0f;
    *y = (દશાંશ)iy / 65536.0f;
}

શૂન્ય WIN_InitMouse(SDL_VideoDevice *_this)
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

શૂન્ય WIN_QuitMouse(SDL_VideoDevice *_this)
{
    જો (SDL_blank_cursor) {
        WIN_FreeCursor(SDL_blank_cursor);
        SDL_blank_cursor = ખાલી;
    }
}

સ્થિર શૂન્ય ReadMouseCurve(પૂર્ણાંક v, Uint64 xs[5], Uint64 ys[5])
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
    DWORD xsize = કદ(xbuff);
    DWORD ysize = કદ(ybuff);
    HKEY open_handle;
    જો (Reg_Open_ચાવી_Ex_W(HKEY_CURRENT_USER, L"Control Panel\\Mouse", 0, ચાવી_READ, &open_handle) == ERROR_SUCCESS) {
        Reg_Query_કિંમત_Ex_W(open_handle, L"SmoothMouseXCurve", ખાલી, ખાલી, (BYTE*)xbuff, &xsize);
        Reg_Query_કિંમત_Ex_W(open_handle, L"SmoothMouseYCurve", ખાલી, ખાલી, (BYTE*)ybuff, &ysize);
        Reg_Close_ચાવી(open_handle);
    }
    xs[0] = 0; // first node must always be origin
    ys[0] = 0; // first node must always be origin
    પૂર્ણાંક i;
    માટે (i = 1; i < 5; i++) {
        xs[i] = (7 * (Uint64)xbuff[i * 2]);
        ys[i] = (v * (Uint64)ybuff[i * 2]) << 17;
    }
}

શૂન્ય WIN_UpdateMouseSystemScale(શૂન્ય)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    જો (mouse->ApplySystemScale == WIN_ApplySystemScale) {
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

    પૂર્ણાંક v = 10;
    જો (SystemParametersInfo(SPI_GETMOUSESPEED, 0, &v, 0)) {
        v = SDL_max(1, SDL_min(v, 20));
        data->dpiscale = SDL_max(SDL_max(v, (v - 2) * 4), (v - 6) * 8);
    }

    પૂર્ણાંક params[3];
    જો (SystemParametersInfo(SPI_GETMOUSE, 0, &params, 0)) {
        data->enhanced = params[2] ? true : false;
        જો (params[2]) {
            ReadMouseCurve(v, data->xs, data->ys);
        }
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS

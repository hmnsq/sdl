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

#எனில் defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#அந்தர்பாவ "SDL_windowsvideo.h"
#அந்தர்பாவ "SDL_windowsevents.h"
#அந்தர்பாவ "SDL_windowsrawinput.h"

#அந்தர்பாவ "../SDL_video_c.h"
#அந்தர்பாவ "../../events/SDL_mouse_c.h"
#அந்தர்பாவ "../../joystick/usb_ids.h"
#அந்தர்பாவ "../../core/windows/SDL_windows.h" // for checking windows version

#define RIFF_FOURCC(c0, c1, c2, c3)                 \
    ((DWORD)(BYTE)(c0) | ((DWORD)(BYTE)(c1) << 8) | \
     ((DWORD)(BYTE)(c2) << 16) | ((DWORD)(BYTE)(c3) << 24))

#define ANI_FLAG_ICON 0x1

#pragma pack(தள்ளு, 1)

வகைவரை கட்டமைப்பு
{
    BYTE bWidth;
    BYTE bHeight;
    BYTE b_Color_மொத்தம்;
    BYTE bReserved;
    WORD xHotspot;
    WORD yHotspot;
    DWORD dwImageSize;
    DWORD dwImageOffset;
} CURSORICONFILEDIRENTRY;

வகைவரை கட்டமைப்பு
{
    WORD idReserved;
    WORD idType;
    WORD id_மொத்தம்;
} CURSORICONFILEDIR;

வகைவரை கட்டமைப்பு
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

#pragma pack(எடு)

வகைவரை கட்டமைப்பு CachedCursor
{
    தசம scale;
    HCURSOR cursor;
    கட்டமைப்பு CachedCursor *next;
} CachedCursor;

கட்டமைப்பு SDL_CursorData
{
    HCURSOR cursor;

    CachedCursor *cache;
    முழு hot_x;
    முழு hot_y;
    முழு இலக்கம்_frames;
    SDL_CursorFrameInfo frames[1];
};

வகைவரை கட்டமைப்பு
{
    Uint64 xs[5];
    Uint64 ys[5];
    Sint64 residual[2];
    Uint32 dpiscale;
    Uint32 dpidenom;
    முழு last_முனை;
    bool enhanced;
    bool dpiaware;
} WIN_MouseData;

DWORD SDL_last_warp_time = 0;
HCURSOR SDL_cursor = வெற்று;
நிலையான SDL_Cursor *SDL_blank_cursor = வெற்று;
நிலையான WIN_MouseData WIN_system_scale_data;

நிலையான SDL_Cursor *WIN_CreateCursorAndData(HCURSOR hcursor)
{
    எனில் (!hcursor) {
        திரும்பு வெற்று;
    }

    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, அளவு(*cursor));
    எனில் (!cursor) {
        திரும்பு வெற்று;
    }

    SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, அளவு(*data));
    எனில் (!data) {
        SDL_free(cursor);
        திரும்பு வெற்று;
    }

    data->cursor = hcursor;
    cursor->internal = data;
    திரும்பு cursor;
}

நிலையான SDL_Cursor *WIN_CreateAnimatedCursorAndData(SDL_CursorFrameInfo *frames, முழு frame_மொத்தம், முழு hot_x, முழு hot_y)
{
    // Dynamically generate cursors at the appropriate DPI
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, அளவு(*cursor));
    எனில் (!cursor) {
        திரும்பு வெற்று;
    }

    SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, அளவு(*data) + (அளவு(SDL_CursorFrameInfo) * (frame_மொத்தம் - 1)));
    எனில் (!data) {
        SDL_free(cursor);
        திரும்பு வெற்று;
    }

    data->hot_x = hot_x;
    data->hot_y = hot_y;
    data->இலக்கம்_frames = frame_மொத்தம்;
    க்கு (முழு i = 0; i < frame_மொத்தம்; ++i) {
        SDL_Surface *surface = frames[i].surface;
        எனில் (surface->flags & SDL_SURFACE_PREALLOCATED) {
            surface = SDL_DuplicateSurface(surface);
            எனில் (!surface) {
                போது (i > 0) {
                    --i;
                    SDL_DestroySurface(data->frames[i].surface);
                }
                SDL_free(data);
                SDL_free(cursor);
                திரும்பு வெற்று;
            }
        } இல்லையெனில் {
            ++surface->refcount;
        }
        data->frames[i].surface = surface;
        data->frames[i].duration = frames[i].duration;
    }
    cursor->internal = data;
    திரும்பு cursor;
}

நிலையான bool SaveChunkSize(SDL_IOStream* dst, Sint64 offset)
{
    Sint64 here = SDL_TellIO(dst);
    எனில் (here < 0) {
        திரும்பு false;
    }
    எனில் (SDL_SeekIO(dst, offset, SDL_IO_SEEK_SET) < 0) {
        திரும்பு false;
    }

    DWORD size = (DWORD)(here - (offset + அளவு(DWORD)));
    எனில் (!SDL_WriteU32LE(dst, size)) {
        திரும்பு false;
    }
    திரும்பு SDL_SeekIO(dst, here, SDL_IO_SEEK_SET);
}

நிலையான bool FillIconEntry(CURSORICONFILEDIRENTRY *entry, SDL_Surface *surface, முழு hot_x, முழு hot_y, DWORD dwImageSize, DWORD dwImageOffset)
{
    எனில் (surface->props) {
        hot_x = (முழு)SDL_Get_எண்_Property(surface->props, SDL_PROP_SURFACE_HOTSPOT_X_எண், hot_x);
        hot_y = (முழு)SDL_Get_எண்_Property(surface->props, SDL_PROP_SURFACE_HOTSPOT_Y_எண், hot_y);
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
    திரும்பு true;
}

#ifdef SAVE_ICON_PNG

நிலையான bool WriteIconSurface(SDL_IOStream *dst, SDL_Surface *surface)
{
    எனில் (!SDL_SavePNG_IO(surface, dst, false)) {
        திரும்பு false;
    }

    // Image data offsets must be WORD aligned
    Sint64 offset = SDL_TellIO(dst);
    எனில் (offset & 1) {
        எனில் (!SDL_WriteU8(dst, 0)) {
            திரும்பு false;
        }
    }
    திரும்பு true;
}

#இல்லையெனில்

/* For info on the expected mask format see:
 * https://devblogs.microsoft.com/oldnewthing/20101018-00/?p=12513
 */
நிலையான வெறுமை *CreateIconMask(SDL_Surface *surface, size_t *mask_size)
{
    Uint8 *dst;
    மாறிலி முழு w = (surface->w + 7) / 8;
    மாறிலி முழு pad = (((w) % 4) ? (4 - ((w) % 4)) : 0);
    மாறிலி முழு pitch = (w + pad);
    மாறிலி size_t size = pitch * surface->h;
    நிலையான மாறிலி unsigned எழுத்து masks[] = { 0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1 };

    வெறுமை *mask = SDL_malloc(size);
    எனில் (!mask) {
        திரும்பு வெற்று;
    }

    dst = (Uint8 *)mask;

    // Make the mask completely transparent.
    SDL_memset(dst, 0xff, size);
    க்கு (முழு y = surface->h - 1; y >= 0; --y, dst += pitch) {
        க்கு (முழு x = 0; x < surface->w; ++x) {
            Uint8 r, g, b, a;
            SDL_ReadSurfacePixel(surface, x, y, &r, &g, &b, &a);

            எனில் (a != 0) {
                // Reset bit of an opaque pixel.
                dst[x >> 3] &= ~masks[x & 7];
            }
        }
    }
    *mask_size = size;
    திரும்பு mask;
}

நிலையான bool WriteIconSurface(SDL_IOStream *dst, SDL_Surface *surface)
{
    SDL_Surface *temp = வெற்று;

    எனில் (surface->format != SDL_PIXELFORMAT_ARGB8888) {
        temp = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        எனில் (!temp) {
            திரும்பு false;
        }
        surface = temp;
    }

    // Cursor data is double height (DIB and mask), stored bottom-up
    bool ok = true;
    size_t mask_size = 0;
    வெறுமை *mask = CreateIconMask(surface, &mask_size);
    எனில் (!mask) {
        ok = false;
        செல் done;
    }

    BITMAPINFOHEADER bmih;
    SDL_zero(bmih);
    DWORD row_size = surface->w * 4;
    bmih.biSize = அளவு(BITMAPINFOHEADER);
    bmih.biWidth = surface->w;
    bmih.biHeight = surface->h * 2;
    bmih.biPlanes = 1;
    bmih.bi_Bit_மொத்தம் = 32;
    bmih.biCompression = BI_RGB;
    bmih.biSizeImage = (DWORD)(surface->h * row_size + mask_size);
    ok &= (SDL_WriteIO(dst, &bmih, அளவு(bmih)) == அளவு(bmih));

    மாறிலி Uint8 *pix = surface->pixels;
    pix += (surface->h - 1) * surface->pitch;
    க்கு (முழு i = 0; i < surface->h; ++i) {
        ok &= (SDL_WriteIO(dst, pix, row_size) == row_size);
        pix -= surface->pitch;
    }
    ok &= (SDL_WriteIO(dst, mask, mask_size) == mask_size);

done:
    SDL_free(mask);
    SDL_DestroySurface(temp);
    திரும்பு ok;
}

#endif // SAVE_ICON_PNG

நிலையான bool WriteIconFrame(SDL_IOStream *dst, SDL_Surface *surface, முழு hot_x, முழு hot_y, தசம scale)
{
#ifdef SAVE_MULTIPLE_ICONS
    முழு மொத்தம் = 0;
    SDL_Surface **surfaces = SDL_GetSurfaceImages(surface, &மொத்தம்);
    எனில் (!surfaces) {
        திரும்பு false;
    }
#இல்லையெனில்
    surface = SDL_GetSurfaceImage(surface, scale);
    எனில் (!surface) {
        திரும்பு false;
    }

    முழு மொத்தம் = 1;
    SDL_Surface **surfaces = &surface;
#endif

    // Raymond Chen has more insight into this format at:
    // https://devblogs.microsoft.com/oldnewthing/20101018-00/?p=12513
    bool ok = true;
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('i', 'c', 'o', 'n'));
    Sint64 icon_size_offset = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    Sint64 base_offset = icon_size_offset + அளவு(DWORD);

    CURSORICONFILEDIR dir;
    dir.idReserved = 0;
    dir.idType = 2; // Cursor
    dir.id_மொத்தம் = மொத்தம்;
    ok &= (SDL_WriteIO(dst, &dir, அளவு(dir)) == அளவு(dir));

    DWORD entries_size = மொத்தம் * அளவு(CURSORICONFILEDIRENTRY);
    CURSORICONFILEDIRENTRY *entries = (CURSORICONFILEDIRENTRY *)SDL_malloc(entries_size);
    எனில் (!entries) {
        ok = false;
        செல் done;
    }
    ok &= (SDL_WriteIO(dst, entries, entries_size) == entries_size);

    Sint64 image_offset = SDL_TellIO(dst);
    க்கு (முழு i = 0; i < மொத்தம்; ++i) {
        ok &= WriteIconSurface(dst, surfaces[i]);

        Sint64 next_offset = SDL_TellIO(dst);
        DWORD dwImageSize = (DWORD)(next_offset - image_offset);
        DWORD dwImageOffset = (DWORD)(image_offset - base_offset);

        ok &= FillIconEntry(&entries[i], surfaces[i], hot_x, hot_y, dwImageSize, dwImageOffset);

        image_offset = next_offset;
    }

    // Now that we have the icon entries filled out, rewrite them
    ok &= (SDL_SeekIO(dst, base_offset + அளவு(dir), SDL_IO_SEEK_SET) >= 0);
    ok &= (SDL_WriteIO(dst, entries, entries_size) == entries_size);
    ok &= (SDL_SeekIO(dst, image_offset, SDL_IO_SEEK_SET) >= 0);
    SDL_free(entries);

    ok &= SaveChunkSize(dst, icon_size_offset);

done:
#ifdef SAVE_MULTIPLE_ICONS
    SDL_free(surfaces);
#இல்லையெனில்
    SDL_DestroySurface(surface);
#endif
    திரும்பு ok;
}

/* Windows doesn't have an API to easily create animated cursors from a sequence of images,
 * so we have to build an animated cursor resource file in memory and load it.
 */
நிலையான HCURSOR WIN_CreateAnimatedCursorInternal(SDL_CursorFrameInfo *frames, முழு frame_மொத்தம், முழு hot_x, முழு hot_y, தசம scale)
{
    HCURSOR hcursor = வெற்று;
    SDL_IOStream *dst = SDL_IOFromDynamicMem();
    எனில் (!dst) {
        திரும்பு வெற்று;
    }

    முழு w = (முழு)SDL_roundf(frames[0].surface->w * scale);
    முழு h = (முழு)SDL_roundf(frames[0].surface->h * scale);

    bool ok = true;
    // RIFF header
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('R', 'I', 'F', 'F'));
    Sint64 riff_size_offset = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('A', 'C', 'O', 'N'));

    // anih header chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('a', 'n', 'i', 'h'));
    ok &= SDL_WriteU32LE(dst, அளவு(ANIHEADER));

    ANIHEADER anih;
    SDL_zero(anih);
    anih.cbSizeof = அளவு(anih);
    anih.frames = frame_மொத்தம்;
    anih.steps = frame_மொத்தம்;
    anih.jifRate = 1;
    anih.fl = ANI_FLAG_ICON;
    ok &= (SDL_WriteIO(dst, &anih, அளவு(anih)) == அளவு(anih));

    // Rate chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('r', 'a', 't', 'e'));
    ok &= SDL_WriteU32LE(dst, அளவு(DWORD) * frame_மொத்தம்);
    க்கு (முழு i = 0; i < frame_மொத்தம்; ++i) {
        // Animated Win32 cursors are in jiffy units, and one jiffy is 1/60 of a second.
        மாறிலி இரட்டை WIN32_JIFFY = 1000.0 / 60.0;
        DWORD duration = (frames[i].duration ? SDL_lround(frames[i].duration / WIN32_JIFFY) : 0xFFFFFFFF);
        ok &= SDL_WriteU32LE(dst, duration);
    }

    // Frame list
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('L', 'I', 'S', 'T'));
    Sint64 frame_list_size_offset = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('f', 'r', 'a', 'm'));

    க்கு (முழு i = 0; i < frame_மொத்தம்; ++i) {
        ok &= WriteIconFrame(dst, frames[i].surface, hot_x, hot_y, scale);
    }
    ok &= SaveChunkSize(dst, frame_list_size_offset);

    // All done!
    ok &= SaveChunkSize(dst, riff_size_offset);
    எனில் (!ok) {
        // The error has been set above
        செல் done;
    }

    BYTE *mem = (BYTE *)SDL_GetPointerProperty(SDL_GetIOProperties(dst), SDL_PROP_IOSTREAM_DYNAMIC_MEMORY_POINTER, வெற்று);
    DWORD size = (DWORD)SDL_GetIOSize(dst);
    hcursor = (HCURSOR)CreateIconFromResourceEx(mem, size, FALSE, 0x00030000, w, h, 0);
    எனில் (!hcursor) {
        SDL_SetError("CreateIconFromResource failed");
    }

done:
    SDL_CloseIO(dst);

    திரும்பு hcursor;
}

நிலையான SDL_Cursor *WIN_CreateCursor(SDL_Surface *surface, முழு hot_x, முழு hot_y)
{
    SDL_CursorFrameInfo frame = { surface, 0 };
    திரும்பு WIN_CreateAnimatedCursorAndData(&frame, 1, hot_x, hot_y);
}

நிலையான SDL_Cursor *WIN_CreateAnimatedCursor(SDL_CursorFrameInfo *frames, முழு frame_மொத்தம், முழு hot_x, முழு hot_y)
{
    திரும்பு WIN_CreateAnimatedCursorAndData(frames, frame_மொத்தம், hot_x, hot_y);
}

நிலையான SDL_Cursor *WIN_CreateBlankCursor(வெறுமை)
{
    SDL_Cursor *cursor = வெற்று;
    SDL_Surface *surface = SDL_CreateSurfaceZeroed(32, 32, SDL_PIXELFORMAT_ARGB8888);
    எனில் (surface) {
        cursor = WIN_CreateCursor(surface, 0, 0);
        SDL_DestroySurface(surface);
    }
    திரும்பு cursor;
}

நிலையான SDL_Cursor *WIN_CreateSystemCursor(SDL_SystemCursor id)
{
    LPCTSTR name;

    தேர்வு (id) {
    இயல்பு:
        SDL_assert(!"Unknown system cursor ID");
        திரும்பு வெற்று;
    நிலை SDL_SYSTEM_CURSOR_DEFAULT:
        name = IDC_ARROW;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_TEXT:
    நிலை SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        name = IDC_IBEAM;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_WAIT:
        name = IDC_WAIT;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_CROSSHAIR:
    நிலை SDL_SYSTEM_CURSOR_CELL:
        name = IDC_CROSS;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_PROGRESS:
        name = IDC_APPSTARTING;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_NWSE_RESIZE:
    நிலை SDL_SYSTEM_CURSOR_NW_RESIZE:
    நிலை SDL_SYSTEM_CURSOR_SE_RESIZE:
        name = IDC_SIZENWSE;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_NESW_RESIZE:
    நிலை SDL_SYSTEM_CURSOR_NE_RESIZE:
    நிலை SDL_SYSTEM_CURSOR_SW_RESIZE:
        name = IDC_SIZENESW;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_EW_RESIZE:
    நிலை SDL_SYSTEM_CURSOR_E_RESIZE:
    நிலை SDL_SYSTEM_CURSOR_W_RESIZE:
    நிலை SDL_SYSTEM_CURSOR_COL_RESIZE:
        name = IDC_SIZEWE;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_NS_RESIZE:
    நிலை SDL_SYSTEM_CURSOR_N_RESIZE:
    நிலை SDL_SYSTEM_CURSOR_S_RESIZE:
    நிலை SDL_SYSTEM_CURSOR_ROW_RESIZE:
        name = IDC_SIZENS;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_MOVE:
    நிலை SDL_SYSTEM_CURSOR_ALL_SCROLL:
        name = IDC_SIZEALL;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_NOT_ALLOWED:
    நிலை SDL_SYSTEM_CURSOR_NO_DROP:
        name = IDC_NO;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_POINTER:
    நிலை SDL_SYSTEM_CURSOR_CONTEXT_MENU:
    நிலை SDL_SYSTEM_CURSOR_ALIAS:
    நிலை SDL_SYSTEM_CURSOR_COPY:
    நிலை SDL_SYSTEM_CURSOR_GRAB:
    நிலை SDL_SYSTEM_CURSOR_GRABBING:
    நிலை SDL_SYSTEM_CURSOR_ZOOM_IN:
    நிலை SDL_SYSTEM_CURSOR_ZOOM_OUT:
        name = IDC_HAND;
        நிறுத்து;
    நிலை SDL_SYSTEM_CURSOR_HELP:
        name = IDC_HELP;
        நிறுத்து;
    }
    திரும்பு WIN_CreateCursorAndData(LoadCursor(வெற்று, name));
}

நிலையான SDL_Cursor *WIN_CreateDefaultCursor(வெறுமை)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    திரும்பு WIN_CreateSystemCursor(id);
}

நிலையான வெறுமை WIN_FreeCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *data = cursor->internal;

    க்கு (முழு i = 0; i < data->இலக்கம்_frames; ++i) {
        SDL_DestroySurface(data->frames[i].surface);
    }
    போது (data->cache) {
        CachedCursor *entry = data->cache;
        data->cache = entry->next;
        எனில் (entry->cursor) {
            DestroyCursor(entry->cursor);
        }
        SDL_free(entry);
    }
    எனில் (data->cursor) {
        DestroyCursor(data->cursor);
    }
    SDL_free(data);
    SDL_free(cursor);
}

நிலையான HCURSOR GetCachedCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *data = cursor->internal;

    தசம scale = 1.0f;
    எனில் (SDL_GetHintBoolean(SDL_HINT_MOUSE_DPI_SCALE_CURSORS, false)) {
        scale = SDL_GetDisplayContentScale(SDL_GetDisplayForWindow(SDL_GetMouseFocus()));
        எனில் (scale == 0.0f) {
            scale = 1.0f;
        }
    }
    க்கு (CachedCursor *entry = data->cache; entry; entry = entry->next) {
        எனில் (scale == entry->scale) {
            திரும்பு entry->cursor;
        }
    }

    // Need to create a cursor for this content scale
    HCURSOR hcursor = WIN_CreateAnimatedCursorInternal(data->frames, data->இலக்கம்_frames, data->hot_x, data->hot_y, scale);
    எனில் (!hcursor) {
        திரும்பு வெற்று;
    }

    CachedCursor *entry = (CachedCursor *)SDL_calloc(1, அளவு(*entry));
    எனில் (!entry) {
        DestroyCursor(hcursor);
        திரும்பு வெற்று;
    }
    entry->cursor = hcursor;
    entry->scale = scale;
    entry->next = data->cache;
    data->cache = entry;

    திரும்பு hcursor;
}

நிலையான bool WIN_ShowCursor(SDL_Cursor *cursor)
{
    எனில் (!cursor) {
        எனில் (GetSystemMetrics(SM_REMOTESESSION)) {
            // Use a blank cursor so we continue to get relative motion over RDP
            cursor = SDL_blank_cursor;
        }
    }
    எனில் (cursor) {
        SDL_CursorData *data = cursor->internal;
        எனில் (data->இலக்கம்_frames > 0) {
            SDL_cursor = GetCachedCursor(cursor);
        } இல்லையெனில் {
            SDL_cursor = data->cursor;
        }
    } இல்லையெனில் {
        SDL_cursor = வெற்று;
    }
    எனில் (SDL_GetMouseFocus() != வெற்று) {
        SetCursor(SDL_cursor);
    }
    திரும்பு true;
}

வெறுமை WIN_SetCursorPos(முழு x, முழு y)
{
    // We need to jitter the value because otherwise Windows will occasionally inexplicably ignore the SetCursorPos() or SendInput()
    SetCursorPos(x, y);
    SetCursorPos(x + 1, y);
    SetCursorPos(x, y);

    // Flush any mouse motion prior to or associated with this warp
#ifdef _MSC_VER // We explicitly want to use GetTickCount(), not GetTickCount64()
#pragma warning(தள்ளு)
#pragma warning(disable : 28159)
#endif
    SDL_last_warp_time = Get_Tick_மொத்தம்();
    எனில் (!SDL_last_warp_time) {
        SDL_last_warp_time = 1;
    }
#ifdef _MSC_VER
#pragma warning(எடு)
#endif
}

நிலையான bool WIN_WarpMouse(SDL_Window *window, தசம x, தசம y)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    POINT pt;

    // Don't warp the mouse while we're doing a modal interaction
    எனில் (data->in_title_click || data->focus_click_pending) {
        திரும்பு true;
    }

    pt.x = (முழு)SDL_roundf(x);
    pt.y = (முழு)SDL_roundf(y);
    ClientToScreen(hwnd, &pt);
    WIN_SetCursorPos(pt.x, pt.y);

    // Send the exact mouse motion associated with this warp
    SDL_SendMouseMotion(0, window, SDL_GLOBAL_MOUSE_ID, false, x, y);
    திரும்பு true;
}

நிலையான bool WIN_WarpMouseGlobal(தசம x, தசம y)
{
    POINT pt;

    pt.x = (முழு)SDL_roundf(x);
    pt.y = (முழு)SDL_roundf(y);
    SetCursorPos(pt.x, pt.y);
    திரும்பு true;
}

நிலையான bool WIN_SetRelativeMouseMode(bool enabled)
{
    திரும்பு WIN_SetRawMouseEnabled(SDL_GetVideoDevice(), enabled);
}

நிலையான bool WIN_CaptureMouse(SDL_Window *window)
{
    எனில் (window) {
        SDL_WindowData *data = window->internal;
        SetCapture(data->hwnd);
    } இல்லையெனில் {
        SDL_Window *focus_window = SDL_GetMouseFocus();

        எனில் (focus_window) {
            SDL_WindowData *data = focus_window->internal;
            எனில் (!data->mouse_tracked) {
                SDL_SetMouseFocus(வெற்று);
            }
        }
        ReleaseCapture();
    }

    திரும்பு true;
}

நிலையான SDL_MouseButtonFlags WIN_GetGlobalMouseState(தசம *x, தசம *y)
{
    SDL_MouseButtonFlags result = 0;
    POINT pt = { 0, 0 };
    bool swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;

    GetCursorPos(&pt);
    *x = (தசம)pt.x;
    *y = (தசம)pt.y;

    result |= Get_Async_சாவி_State(!swapButtons ? VK_LBUTTON : VK_RBUTTON) & 0x8000 ? SDL_BUTTON_LMASK : 0;
    result |= Get_Async_சாவி_State(!swapButtons ? VK_RBUTTON : VK_LBUTTON) & 0x8000 ? SDL_BUTTON_RMASK : 0;
    result |= Get_Async_சாவி_State(VK_MBUTTON) & 0x8000 ? SDL_BUTTON_MMASK : 0;
    result |= Get_Async_சாவி_State(VK_XBUTTON1) & 0x8000 ? SDL_BUTTON_X1MASK : 0;
    result |= Get_Async_சாவி_State(VK_XBUTTON2) & 0x8000 ? SDL_BUTTON_X2MASK : 0;

    திரும்பு result;
}

நிலையான வெறுமை WIN_ApplySystemScale(வெறுமை *internal, Uint64 timestamp, SDL_Window *window, SDL_MouseID mouseID, தசம *x, தசம *y)
{
    எனில் (!internal) {
        திரும்பு;
    }
    WIN_MouseData *data = (WIN_MouseData *)internal;

    SDL_VideoDisplay *display = window ? SDL_GetVideoDisplayForWindow(window) : SDL_GetVideoDisplay(SDL_GetPrimaryDisplay());

    Sint64 ix = (Sint64)*x * 65536;
    Sint64 iy = (Sint64)*y * 65536;
    Uint32 dpi = display ? (Uint32)(display->content_scale * USER_DEFAULT_SCREEN_DPI) : USER_DEFAULT_SCREEN_DPI;

    எனில் (!data->enhanced) { // early return if flat scale
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
        *x = (தசம)ix / 65536.0f;
        *y = (தசம)iy / 65536.0f;
        திரும்பு;
    }

    Uint64 *xs = data->xs;
    Uint64 *ys = data->ys;
    Uint64 absx = SDL_abs(ix);
    Uint64 absy = SDL_abs(iy);
    Uint64 speed = SDL_min(absx, absy) + (SDL_max(absx, absy) << 1); // super cursed approximation used by Windows
    எனில் (speed == 0) {
        திரும்பு;
    }

    முழு i, j, k;
    க்கு (i = 1; i < 5; i++) {
        j = i;
        எனில் (speed < xs[j]) {
            நிறுத்து;
        }
    }
    i -= 1;
    j -= 1;
    k = data->last_முனை;
    data->last_முனை = j;

    Uint32 denom = data->dpidenom;
    Sint64 scale = 0;
    Sint64 xdiff = xs[j+1] - xs[j];
    Sint64 ydiff = ys[j+1] - ys[j];
    எனில் (xdiff != 0) {
        Sint64 slope = ydiff / xdiff;
        Sint64 inter = slope * xs[i] - ys[i];
        scale += slope - inter / speed;
    }

    எனில் (j > k) {
        denom <<= 1;
        xdiff = xs[k+1] - xs[k];
        ydiff = ys[k+1] - ys[k];
        எனில் (xdiff != 0) {
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
    *x = (தசம)ix / 65536.0f;
    *y = (தசம)iy / 65536.0f;
}

வெறுமை WIN_InitMouse(SDL_VideoDevice *_this)
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

வெறுமை WIN_QuitMouse(SDL_VideoDevice *_this)
{
    எனில் (SDL_blank_cursor) {
        WIN_FreeCursor(SDL_blank_cursor);
        SDL_blank_cursor = வெற்று;
    }
}

நிலையான வெறுமை ReadMouseCurve(முழு v, Uint64 xs[5], Uint64 ys[5])
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
    DWORD xsize = அளவு(xbuff);
    DWORD ysize = அளவு(ybuff);
    HKEY open_handle;
    எனில் (Reg_Open_சாவி_Ex_W(HKEY_CURRENT_USER, L"Control Panel\\Mouse", 0, சாவி_READ, &open_handle) == ERROR_SUCCESS) {
        Reg_Query_மதிப்பு_Ex_W(open_handle, L"SmoothMouseXCurve", வெற்று, வெற்று, (BYTE*)xbuff, &xsize);
        Reg_Query_மதிப்பு_Ex_W(open_handle, L"SmoothMouseYCurve", வெற்று, வெற்று, (BYTE*)ybuff, &ysize);
        Reg_Close_சாவி(open_handle);
    }
    xs[0] = 0; // first node must always be origin
    ys[0] = 0; // first node must always be origin
    முழு i;
    க்கு (i = 1; i < 5; i++) {
        xs[i] = (7 * (Uint64)xbuff[i * 2]);
        ys[i] = (v * (Uint64)ybuff[i * 2]) << 17;
    }
}

வெறுமை WIN_UpdateMouseSystemScale(வெறுமை)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    எனில் (mouse->ApplySystemScale == WIN_ApplySystemScale) {
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

    முழு v = 10;
    எனில் (SystemParametersInfo(SPI_GETMOUSESPEED, 0, &v, 0)) {
        v = SDL_max(1, SDL_min(v, 20));
        data->dpiscale = SDL_max(SDL_max(v, (v - 2) * 4), (v - 6) * 8);
    }

    முழு params[3];
    எனில் (SystemParametersInfo(SPI_GETMOUSE, 0, &params, 0)) {
        data->enhanced = params[2] ? true : false;
        எனில் (params[2]) {
            ReadMouseCurve(v, data->xs, data->ys);
        }
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS

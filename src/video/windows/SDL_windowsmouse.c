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
#ضمن "SDL_internal.h"

#إذا defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ضمن "SDL_windowsvideo.h"
#ضمن "SDL_windowsevents.h"
#ضمن "SDL_windowsrawinput.h"

#ضمن "../SDL_video_c.h"
#ضمن "../../events/SDL_mouse_c.h"
#ضمن "../../joystick/usb_ids.h"
#ضمن "../../core/windows/SDL_windows.h" // for checking windows version

#define RIFF_FOURCC(c0, c1, c2, c3)                 \
    ((DWORD)(BYTE)(c0) | ((DWORD)(BYTE)(c1) << 8) | \
     ((DWORD)(BYTE)(c2) << 16) | ((DWORD)(BYTE)(c3) << 24))

#define ANI_FLAG_ICON 0x1

#pragma pack(تور, 1)

تعريفنوع بنية
{
    BYTE bWidth;
    BYTE bHeight;
    BYTE b_Color_كدي;
    BYTE bReserved;
    WORD xHotspot;
    WORD yHotspot;
    DWORD dwImageSize;
    DWORD dwImageOffset;
} CURSORICONFILEDIRENTRY;

تعريفنوع بنية
{
    WORD idReserved;
    WORD idType;
    WORD id_كدي;
} CURSORICONFILEDIR;

تعريفنوع بنية
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

#pragma pack(چرو)

تعريفنوع بنية CachedCursor
{
    عائم scale;
    HCURSOR cursor;
    بنية CachedCursor *next;
} CachedCursor;

بنية SDL_CursorData
{
    HCURSOR cursor;

    CachedCursor *cache;
    صحيح hot_x;
    صحيح hot_y;
    صحيح لمب_frames;
    SDL_CursorFrameInfo frames[1];
};

تعريفنوع بنية
{
    Uint64 xs[5];
    Uint64 ys[5];
    Sint64 residual[2];
    Uint32 dpiscale;
    Uint32 dpidenom;
    صحيح last_كلي;
    bool enhanced;
    bool dpiaware;
} WIN_MouseData;

DWORD SDL_last_warp_time = 0;
HCURSOR SDL_cursor = عدم;
ساكن SDL_Cursor *SDL_blank_cursor = عدم;
ساكن WIN_MouseData WIN_system_scale_data;

ساكن SDL_Cursor *WIN_CreateCursorAndData(HCURSOR hcursor)
{
    إذا (!hcursor) {
        أرجع عدم;
    }

    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, حجم(*cursor));
    إذا (!cursor) {
        أرجع عدم;
    }

    SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, حجم(*data));
    إذا (!data) {
        SDL_free(cursor);
        أرجع عدم;
    }

    data->cursor = hcursor;
    cursor->internal = data;
    أرجع cursor;
}

ساكن SDL_Cursor *WIN_CreateAnimatedCursorAndData(SDL_CursorFrameInfo *frames, صحيح frame_كدي, صحيح hot_x, صحيح hot_y)
{
    // Dynamically generate cursors at the appropriate DPI
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, حجم(*cursor));
    إذا (!cursor) {
        أرجع عدم;
    }

    SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, حجم(*data) + (حجم(SDL_CursorFrameInfo) * (frame_كدي - 1)));
    إذا (!data) {
        SDL_free(cursor);
        أرجع عدم;
    }

    data->hot_x = hot_x;
    data->hot_y = hot_y;
    data->لمب_frames = frame_كدي;
    لكل (صحيح i = 0; i < frame_كدي; ++i) {
        SDL_Surface *surface = frames[i].surface;
        إذا (surface->flags & SDL_SURFACE_PREALLOCATED) {
            surface = SDL_DuplicateSurface(surface);
            إذا (!surface) {
                طالما (i > 0) {
                    --i;
                    SDL_DestroySurface(data->frames[i].surface);
                }
                SDL_free(data);
                SDL_free(cursor);
                أرجع عدم;
            }
        } وإلا {
            ++surface->refcount;
        }
        data->frames[i].surface = surface;
        data->frames[i].duration = frames[i].duration;
    }
    cursor->internal = data;
    أرجع cursor;
}

ساكن bool SaveChunkSize(SDL_IOStream* dst, Sint64 offset)
{
    Sint64 here = SDL_TellIO(dst);
    إذا (here < 0) {
        أرجع false;
    }
    إذا (SDL_SeekIO(dst, offset, SDL_IO_SEEK_SET) < 0) {
        أرجع false;
    }

    DWORD size = (DWORD)(here - (offset + حجم(DWORD)));
    إذا (!SDL_WriteU32LE(dst, size)) {
        أرجع false;
    }
    أرجع SDL_SeekIO(dst, here, SDL_IO_SEEK_SET);
}

ساكن bool FillIconEntry(CURSORICONFILEDIRENTRY *entry, SDL_Surface *surface, صحيح hot_x, صحيح hot_y, DWORD dwImageSize, DWORD dwImageOffset)
{
    إذا (surface->props) {
        hot_x = (صحيح)SDL_Get_لمب_Property(surface->props, SDL_PROP_SURFACE_HOTSPOT_X_لمب, hot_x);
        hot_y = (صحيح)SDL_Get_لمب_Property(surface->props, SDL_PROP_SURFACE_HOTSPOT_Y_لمب, hot_y);
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
    أرجع true;
}

#ifdef SAVE_ICON_PNG

ساكن bool WriteIconSurface(SDL_IOStream *dst, SDL_Surface *surface)
{
    إذا (!SDL_SavePNG_IO(surface, dst, false)) {
        أرجع false;
    }

    // Image data offsets must be WORD aligned
    Sint64 offset = SDL_TellIO(dst);
    إذا (offset & 1) {
        إذا (!SDL_WriteU8(dst, 0)) {
            أرجع false;
        }
    }
    أرجع true;
}

#وإلا

/* For info on the expected mask format see:
 * https://devblogs.microsoft.com/oldnewthing/20101018-00/?p=12513
 */
ساكن فراغ *CreateIconMask(SDL_Surface *surface, size_t *mask_size)
{
    Uint8 *dst;
    ثابت صحيح w = (surface->w + 7) / 8;
    ثابت صحيح pad = (((w) % 4) ? (4 - ((w) % 4)) : 0);
    ثابت صحيح pitch = (w + pad);
    ثابت size_t size = pitch * surface->h;
    ساكن ثابت unsigned حرف masks[] = { 0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1 };

    فراغ *mask = SDL_malloc(size);
    إذا (!mask) {
        أرجع عدم;
    }

    dst = (Uint8 *)mask;

    // Make the mask completely transparent.
    SDL_memset(dst, 0xff, size);
    لكل (صحيح y = surface->h - 1; y >= 0; --y, dst += pitch) {
        لكل (صحيح x = 0; x < surface->w; ++x) {
            Uint8 r, g, b, a;
            SDL_ReadSurfacePixel(surface, x, y, &r, &g, &b, &a);

            إذا (a != 0) {
                // Reset bit of an opaque pixel.
                dst[x >> 3] &= ~masks[x & 7];
            }
        }
    }
    *mask_size = size;
    أرجع mask;
}

ساكن bool WriteIconSurface(SDL_IOStream *dst, SDL_Surface *surface)
{
    SDL_Surface *temp = عدم;

    إذا (surface->format != SDL_PIXELFORMAT_ARGB8888) {
        temp = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        إذا (!temp) {
            أرجع false;
        }
        surface = temp;
    }

    // Cursor data is double height (DIB and mask), stored bottom-up
    bool ok = true;
    size_t mask_size = 0;
    فراغ *mask = CreateIconMask(surface, &mask_size);
    إذا (!mask) {
        ok = false;
        اذهب done;
    }

    BITMAPINFOHEADER bmih;
    SDL_zero(bmih);
    DWORD row_size = surface->w * 4;
    bmih.biSize = حجم(BITMAPINFOHEADER);
    bmih.biWidth = surface->w;
    bmih.biHeight = surface->h * 2;
    bmih.biPlanes = 1;
    bmih.bi_Bit_كدي = 32;
    bmih.biCompression = BI_RGB;
    bmih.biSizeImage = (DWORD)(surface->h * row_size + mask_size);
    ok &= (SDL_WriteIO(dst, &bmih, حجم(bmih)) == حجم(bmih));

    ثابت Uint8 *pix = surface->pixels;
    pix += (surface->h - 1) * surface->pitch;
    لكل (صحيح i = 0; i < surface->h; ++i) {
        ok &= (SDL_WriteIO(dst, pix, row_size) == row_size);
        pix -= surface->pitch;
    }
    ok &= (SDL_WriteIO(dst, mask, mask_size) == mask_size);

done:
    SDL_free(mask);
    SDL_DestroySurface(temp);
    أرجع ok;
}

#endif // SAVE_ICON_PNG

ساكن bool WriteIconFrame(SDL_IOStream *dst, SDL_Surface *surface, صحيح hot_x, صحيح hot_y, عائم scale)
{
#ifdef SAVE_MULTIPLE_ICONS
    صحيح كدي = 0;
    SDL_Surface **surfaces = SDL_GetSurfaceImages(surface, &كدي);
    إذا (!surfaces) {
        أرجع false;
    }
#وإلا
    surface = SDL_GetSurfaceImage(surface, scale);
    إذا (!surface) {
        أرجع false;
    }

    صحيح كدي = 1;
    SDL_Surface **surfaces = &surface;
#endif

    // Raymond Chen has more insight into this format at:
    // https://devblogs.microsoft.com/oldnewthing/20101018-00/?p=12513
    bool ok = true;
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('i', 'c', 'o', 'n'));
    Sint64 icon_size_offset = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    Sint64 base_offset = icon_size_offset + حجم(DWORD);

    CURSORICONFILEDIR dir;
    dir.idReserved = 0;
    dir.idType = 2; // Cursor
    dir.id_كدي = كدي;
    ok &= (SDL_WriteIO(dst, &dir, حجم(dir)) == حجم(dir));

    DWORD entries_size = كدي * حجم(CURSORICONFILEDIRENTRY);
    CURSORICONFILEDIRENTRY *entries = (CURSORICONFILEDIRENTRY *)SDL_malloc(entries_size);
    إذا (!entries) {
        ok = false;
        اذهب done;
    }
    ok &= (SDL_WriteIO(dst, entries, entries_size) == entries_size);

    Sint64 image_offset = SDL_TellIO(dst);
    لكل (صحيح i = 0; i < كدي; ++i) {
        ok &= WriteIconSurface(dst, surfaces[i]);

        Sint64 next_offset = SDL_TellIO(dst);
        DWORD dwImageSize = (DWORD)(next_offset - image_offset);
        DWORD dwImageOffset = (DWORD)(image_offset - base_offset);

        ok &= FillIconEntry(&entries[i], surfaces[i], hot_x, hot_y, dwImageSize, dwImageOffset);

        image_offset = next_offset;
    }

    // Now that we have the icon entries filled out, rewrite them
    ok &= (SDL_SeekIO(dst, base_offset + حجم(dir), SDL_IO_SEEK_SET) >= 0);
    ok &= (SDL_WriteIO(dst, entries, entries_size) == entries_size);
    ok &= (SDL_SeekIO(dst, image_offset, SDL_IO_SEEK_SET) >= 0);
    SDL_free(entries);

    ok &= SaveChunkSize(dst, icon_size_offset);

done:
#ifdef SAVE_MULTIPLE_ICONS
    SDL_free(surfaces);
#وإلا
    SDL_DestroySurface(surface);
#endif
    أرجع ok;
}

/* Windows doesn't have an API to easily create animated cursors from a sequence of images,
 * so we have to build an animated cursor resource file in memory and load it.
 */
ساكن HCURSOR WIN_CreateAnimatedCursorInternal(SDL_CursorFrameInfo *frames, صحيح frame_كدي, صحيح hot_x, صحيح hot_y, عائم scale)
{
    HCURSOR hcursor = عدم;
    SDL_IOStream *dst = SDL_IOFromDynamicMem();
    إذا (!dst) {
        أرجع عدم;
    }

    صحيح w = (صحيح)SDL_roundf(frames[0].surface->w * scale);
    صحيح h = (صحيح)SDL_roundf(frames[0].surface->h * scale);

    bool ok = true;
    // RIFF header
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('R', 'I', 'F', 'F'));
    Sint64 riff_size_offset = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('A', 'C', 'O', 'N'));

    // anih header chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('a', 'n', 'i', 'h'));
    ok &= SDL_WriteU32LE(dst, حجم(ANIHEADER));

    ANIHEADER anih;
    SDL_zero(anih);
    anih.cbSizeof = حجم(anih);
    anih.frames = frame_كدي;
    anih.steps = frame_كدي;
    anih.jifRate = 1;
    anih.fl = ANI_FLAG_ICON;
    ok &= (SDL_WriteIO(dst, &anih, حجم(anih)) == حجم(anih));

    // Rate chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('r', 'a', 't', 'e'));
    ok &= SDL_WriteU32LE(dst, حجم(DWORD) * frame_كدي);
    لكل (صحيح i = 0; i < frame_كدي; ++i) {
        // Animated Win32 cursors are in jiffy units, and one jiffy is 1/60 of a second.
        ثابت مزدوج WIN32_JIFFY = 1000.0 / 60.0;
        DWORD duration = (frames[i].duration ? SDL_lround(frames[i].duration / WIN32_JIFFY) : 0xFFFFFFFF);
        ok &= SDL_WriteU32LE(dst, duration);
    }

    // Frame list
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('L', 'I', 'S', 'T'));
    Sint64 frame_list_size_offset = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('f', 'r', 'a', 'm'));

    لكل (صحيح i = 0; i < frame_كدي; ++i) {
        ok &= WriteIconFrame(dst, frames[i].surface, hot_x, hot_y, scale);
    }
    ok &= SaveChunkSize(dst, frame_list_size_offset);

    // All done!
    ok &= SaveChunkSize(dst, riff_size_offset);
    إذا (!ok) {
        // The error has been set above
        اذهب done;
    }

    BYTE *mem = (BYTE *)SDL_GetPointerProperty(SDL_GetIOProperties(dst), SDL_PROP_IOSTREAM_DYNAMIC_MEMORY_POINTER, عدم);
    DWORD size = (DWORD)SDL_GetIOSize(dst);
    hcursor = (HCURSOR)CreateIconFromResourceEx(mem, size, FALSE, 0x00030000, w, h, 0);
    إذا (!hcursor) {
        SDL_SetError("CreateIconFromResource failed");
    }

done:
    SDL_CloseIO(dst);

    أرجع hcursor;
}

ساكن SDL_Cursor *WIN_CreateCursor(SDL_Surface *surface, صحيح hot_x, صحيح hot_y)
{
    SDL_CursorFrameInfo frame = { surface, 0 };
    أرجع WIN_CreateAnimatedCursorAndData(&frame, 1, hot_x, hot_y);
}

ساكن SDL_Cursor *WIN_CreateAnimatedCursor(SDL_CursorFrameInfo *frames, صحيح frame_كدي, صحيح hot_x, صحيح hot_y)
{
    أرجع WIN_CreateAnimatedCursorAndData(frames, frame_كدي, hot_x, hot_y);
}

ساكن SDL_Cursor *WIN_CreateBlankCursor(فراغ)
{
    SDL_Cursor *cursor = عدم;
    SDL_Surface *surface = SDL_CreateSurfaceZeroed(32, 32, SDL_PIXELFORMAT_ARGB8888);
    إذا (surface) {
        cursor = WIN_CreateCursor(surface, 0, 0);
        SDL_DestroySurface(surface);
    }
    أرجع cursor;
}

ساكن SDL_Cursor *WIN_CreateSystemCursor(SDL_SystemCursor id)
{
    LPCTSTR name;

    بدل (id) {
    افتراضي:
        SDL_assert(!"Unknown system cursor ID");
        أرجع عدم;
    حالة SDL_SYSTEM_CURSOR_DEFAULT:
        name = IDC_ARROW;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_TEXT:
    حالة SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        name = IDC_IBEAM;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_WAIT:
        name = IDC_WAIT;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_CROSSHAIR:
    حالة SDL_SYSTEM_CURSOR_CELL:
        name = IDC_CROSS;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_PROGRESS:
        name = IDC_APPSTARTING;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_NWSE_RESIZE:
    حالة SDL_SYSTEM_CURSOR_NW_RESIZE:
    حالة SDL_SYSTEM_CURSOR_SE_RESIZE:
        name = IDC_SIZENWSE;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_NESW_RESIZE:
    حالة SDL_SYSTEM_CURSOR_NE_RESIZE:
    حالة SDL_SYSTEM_CURSOR_SW_RESIZE:
        name = IDC_SIZENESW;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_EW_RESIZE:
    حالة SDL_SYSTEM_CURSOR_E_RESIZE:
    حالة SDL_SYSTEM_CURSOR_W_RESIZE:
    حالة SDL_SYSTEM_CURSOR_COL_RESIZE:
        name = IDC_SIZEWE;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_NS_RESIZE:
    حالة SDL_SYSTEM_CURSOR_N_RESIZE:
    حالة SDL_SYSTEM_CURSOR_S_RESIZE:
    حالة SDL_SYSTEM_CURSOR_ROW_RESIZE:
        name = IDC_SIZENS;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_MOVE:
    حالة SDL_SYSTEM_CURSOR_ALL_SCROLL:
        name = IDC_SIZEALL;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_NOT_ALLOWED:
    حالة SDL_SYSTEM_CURSOR_NO_DROP:
        name = IDC_NO;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_POINTER:
    حالة SDL_SYSTEM_CURSOR_CONTEXT_MENU:
    حالة SDL_SYSTEM_CURSOR_ALIAS:
    حالة SDL_SYSTEM_CURSOR_COPY:
    حالة SDL_SYSTEM_CURSOR_GRAB:
    حالة SDL_SYSTEM_CURSOR_GRABBING:
    حالة SDL_SYSTEM_CURSOR_ZOOM_IN:
    حالة SDL_SYSTEM_CURSOR_ZOOM_OUT:
        name = IDC_HAND;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_HELP:
        name = IDC_HELP;
        اكسر;
    }
    أرجع WIN_CreateCursorAndData(LoadCursor(عدم, name));
}

ساكن SDL_Cursor *WIN_CreateDefaultCursor(فراغ)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    أرجع WIN_CreateSystemCursor(id);
}

ساكن فراغ WIN_FreeCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *data = cursor->internal;

    لكل (صحيح i = 0; i < data->لمب_frames; ++i) {
        SDL_DestroySurface(data->frames[i].surface);
    }
    طالما (data->cache) {
        CachedCursor *entry = data->cache;
        data->cache = entry->next;
        إذا (entry->cursor) {
            DestroyCursor(entry->cursor);
        }
        SDL_free(entry);
    }
    إذا (data->cursor) {
        DestroyCursor(data->cursor);
    }
    SDL_free(data);
    SDL_free(cursor);
}

ساكن HCURSOR GetCachedCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *data = cursor->internal;

    عائم scale = 1.0f;
    إذا (SDL_GetHintBoolean(SDL_HINT_MOUSE_DPI_SCALE_CURSORS, false)) {
        scale = SDL_GetDisplayContentScale(SDL_GetDisplayForWindow(SDL_GetMouseFocus()));
        إذا (scale == 0.0f) {
            scale = 1.0f;
        }
    }
    لكل (CachedCursor *entry = data->cache; entry; entry = entry->next) {
        إذا (scale == entry->scale) {
            أرجع entry->cursor;
        }
    }

    // Need to create a cursor for this content scale
    HCURSOR hcursor = WIN_CreateAnimatedCursorInternal(data->frames, data->لمب_frames, data->hot_x, data->hot_y, scale);
    إذا (!hcursor) {
        أرجع عدم;
    }

    CachedCursor *entry = (CachedCursor *)SDL_calloc(1, حجم(*entry));
    إذا (!entry) {
        DestroyCursor(hcursor);
        أرجع عدم;
    }
    entry->cursor = hcursor;
    entry->scale = scale;
    entry->next = data->cache;
    data->cache = entry;

    أرجع hcursor;
}

ساكن bool WIN_ShowCursor(SDL_Cursor *cursor)
{
    إذا (!cursor) {
        إذا (GetSystemMetrics(SM_REMOTESESSION)) {
            // Use a blank cursor so we continue to get relative motion over RDP
            cursor = SDL_blank_cursor;
        }
    }
    إذا (cursor) {
        SDL_CursorData *data = cursor->internal;
        إذا (data->لمب_frames > 0) {
            SDL_cursor = GetCachedCursor(cursor);
        } وإلا {
            SDL_cursor = data->cursor;
        }
    } وإلا {
        SDL_cursor = عدم;
    }
    إذا (SDL_GetMouseFocus() != عدم) {
        SetCursor(SDL_cursor);
    }
    أرجع true;
}

فراغ WIN_SetCursorPos(صحيح x, صحيح y)
{
    // We need to jitter the value because otherwise Windows will occasionally inexplicably ignore the SetCursorPos() or SendInput()
    SetCursorPos(x, y);
    SetCursorPos(x + 1, y);
    SetCursorPos(x, y);

    // Flush any mouse motion prior to or associated with this warp
#ifdef _MSC_VER // We explicitly want to use GetTickCount(), not GetTickCount64()
#pragma warning(تور)
#pragma warning(disable : 28159)
#endif
    SDL_last_warp_time = Get_Tick_كدي();
    إذا (!SDL_last_warp_time) {
        SDL_last_warp_time = 1;
    }
#ifdef _MSC_VER
#pragma warning(چرو)
#endif
}

ساكن bool WIN_WarpMouse(SDL_Window *window, عائم x, عائم y)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    POINT pt;

    // Don't warp the mouse while we're doing a modal interaction
    إذا (data->in_title_click || data->focus_click_pending) {
        أرجع true;
    }

    pt.x = (صحيح)SDL_roundf(x);
    pt.y = (صحيح)SDL_roundf(y);
    ClientToScreen(hwnd, &pt);
    WIN_SetCursorPos(pt.x, pt.y);

    // Send the exact mouse motion associated with this warp
    SDL_SendMouseMotion(0, window, SDL_GLOBAL_MOUSE_ID, false, x, y);
    أرجع true;
}

ساكن bool WIN_WarpMouseGlobal(عائم x, عائم y)
{
    POINT pt;

    pt.x = (صحيح)SDL_roundf(x);
    pt.y = (صحيح)SDL_roundf(y);
    SetCursorPos(pt.x, pt.y);
    أرجع true;
}

ساكن bool WIN_SetRelativeMouseMode(bool enabled)
{
    أرجع WIN_SetRawMouseEnabled(SDL_GetVideoDevice(), enabled);
}

ساكن bool WIN_CaptureMouse(SDL_Window *window)
{
    إذا (window) {
        SDL_WindowData *data = window->internal;
        SetCapture(data->hwnd);
    } وإلا {
        SDL_Window *focus_window = SDL_GetMouseFocus();

        إذا (focus_window) {
            SDL_WindowData *data = focus_window->internal;
            إذا (!data->mouse_tracked) {
                SDL_SetMouseFocus(عدم);
            }
        }
        ReleaseCapture();
    }

    أرجع true;
}

ساكن SDL_MouseButtonFlags WIN_GetGlobalMouseState(عائم *x, عائم *y)
{
    SDL_MouseButtonFlags result = 0;
    POINT pt = { 0, 0 };
    bool swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;

    GetCursorPos(&pt);
    *x = (عائم)pt.x;
    *y = (عائم)pt.y;

    result |= Get_Async_مبودي_State(!swapButtons ? VK_LBUTTON : VK_RBUTTON) & 0x8000 ? SDL_BUTTON_LMASK : 0;
    result |= Get_Async_مبودي_State(!swapButtons ? VK_RBUTTON : VK_LBUTTON) & 0x8000 ? SDL_BUTTON_RMASK : 0;
    result |= Get_Async_مبودي_State(VK_MBUTTON) & 0x8000 ? SDL_BUTTON_MMASK : 0;
    result |= Get_Async_مبودي_State(VK_XBUTTON1) & 0x8000 ? SDL_BUTTON_X1MASK : 0;
    result |= Get_Async_مبودي_State(VK_XBUTTON2) & 0x8000 ? SDL_BUTTON_X2MASK : 0;

    أرجع result;
}

ساكن فراغ WIN_ApplySystemScale(فراغ *internal, Uint64 timestamp, SDL_Window *window, SDL_MouseID mouseID, عائم *x, عائم *y)
{
    إذا (!internal) {
        أرجع;
    }
    WIN_MouseData *data = (WIN_MouseData *)internal;

    SDL_VideoDisplay *display = window ? SDL_GetVideoDisplayForWindow(window) : SDL_GetVideoDisplay(SDL_GetPrimaryDisplay());

    Sint64 ix = (Sint64)*x * 65536;
    Sint64 iy = (Sint64)*y * 65536;
    Uint32 dpi = display ? (Uint32)(display->content_scale * USER_DEFAULT_SCREEN_DPI) : USER_DEFAULT_SCREEN_DPI;

    إذا (!data->enhanced) { // early return if flat scale
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
        *x = (عائم)ix / 65536.0f;
        *y = (عائم)iy / 65536.0f;
        أرجع;
    }

    Uint64 *xs = data->xs;
    Uint64 *ys = data->ys;
    Uint64 absx = SDL_abs(ix);
    Uint64 absy = SDL_abs(iy);
    Uint64 speed = SDL_min(absx, absy) + (SDL_max(absx, absy) << 1); // super cursed approximation used by Windows
    إذا (speed == 0) {
        أرجع;
    }

    صحيح i, j, k;
    لكل (i = 1; i < 5; i++) {
        j = i;
        إذا (speed < xs[j]) {
            اكسر;
        }
    }
    i -= 1;
    j -= 1;
    k = data->last_كلي;
    data->last_كلي = j;

    Uint32 denom = data->dpidenom;
    Sint64 scale = 0;
    Sint64 xdiff = xs[j+1] - xs[j];
    Sint64 ydiff = ys[j+1] - ys[j];
    إذا (xdiff != 0) {
        Sint64 slope = ydiff / xdiff;
        Sint64 inter = slope * xs[i] - ys[i];
        scale += slope - inter / speed;
    }

    إذا (j > k) {
        denom <<= 1;
        xdiff = xs[k+1] - xs[k];
        ydiff = ys[k+1] - ys[k];
        إذا (xdiff != 0) {
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
    *x = (عائم)ix / 65536.0f;
    *y = (عائم)iy / 65536.0f;
}

فراغ WIN_InitMouse(SDL_VideoDevice *_this)
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

فراغ WIN_QuitMouse(SDL_VideoDevice *_this)
{
    إذا (SDL_blank_cursor) {
        WIN_FreeCursor(SDL_blank_cursor);
        SDL_blank_cursor = عدم;
    }
}

ساكن فراغ ReadMouseCurve(صحيح v, Uint64 xs[5], Uint64 ys[5])
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
    DWORD xsize = حجم(xbuff);
    DWORD ysize = حجم(ybuff);
    HKEY open_handle;
    إذا (Reg_Open_مبودي_Ex_W(HKEY_CURRENT_USER, L"Control Panel\\Mouse", 0, مبودي_READ, &open_handle) == ERROR_SUCCESS) {
        Reg_Query_درج_Ex_W(open_handle, L"SmoothMouseXCurve", عدم, عدم, (BYTE*)xbuff, &xsize);
        Reg_Query_درج_Ex_W(open_handle, L"SmoothMouseYCurve", عدم, عدم, (BYTE*)ybuff, &ysize);
        Reg_Close_مبودي(open_handle);
    }
    xs[0] = 0; // first node must always be origin
    ys[0] = 0; // first node must always be origin
    صحيح i;
    لكل (i = 1; i < 5; i++) {
        xs[i] = (7 * (Uint64)xbuff[i * 2]);
        ys[i] = (v * (Uint64)ybuff[i * 2]) << 17;
    }
}

فراغ WIN_UpdateMouseSystemScale(فراغ)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    إذا (mouse->ApplySystemScale == WIN_ApplySystemScale) {
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

    صحيح v = 10;
    إذا (SystemParametersInfo(SPI_GETMOUSESPEED, 0, &v, 0)) {
        v = SDL_max(1, SDL_min(v, 20));
        data->dpiscale = SDL_max(SDL_max(v, (v - 2) * 4), (v - 6) * 8);
    }

    صحيح params[3];
    إذا (SystemParametersInfo(SPI_GETMOUSE, 0, &params, 0)) {
        data->enhanced = params[2] ? true : false;
        إذا (params[2]) {
            ReadMouseCurve(v, data->xs, data->ys);
        }
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS

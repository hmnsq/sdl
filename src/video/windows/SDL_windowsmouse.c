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
#شامل "SDL_internal.h"

#اگر defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#شامل "SDL_windowsvideo.h"
#شامل "SDL_windowsevents.h"
#شامل "SDL_windowsrawinput.h"

#شامل "../SDL_video_c.h"
#شامل "../../events/SDL_mouse_c.h"
#شامل "../../joystick/usb_ids.h"
#شامل "../../core/windows/SDL_windows.h" // for checking windows version

#define RIFF_FOURCC(c0, c1, c2, c3)                 \
    ((DWORD)(BYTE)(c0) | ((DWORD)(BYTE)(c1) << 8) | \
     ((DWORD)(BYTE)(c2) << 16) | ((DWORD)(BYTE)(c3) << 24))

#define ANI_FLAG_ICON 0x1

#pragma pack(افزودن, 1)

تعریفنوع ساختار
{
    BYTE bWidth;
    BYTE bHeight;
    BYTE b_Color_شمار;
    BYTE bReserved;
    WORD xHotspot;
    WORD yHotspot;
    DWORD dwImageSize;
    DWORD dwImageOffset;
} CURSORICONFILEDIRENTRY;

تعریفنوع ساختار
{
    WORD idReserved;
    WORD idType;
    WORD id_شمار;
} CURSORICONFILEDIR;

تعریفنوع ساختار
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

#pragma pack(برداشت)

تعریفنوع ساختار CachedCursor
{
    اعشاری scale;
    HCURSOR cursor;
    ساختار CachedCursor *next;
} CachedCursor;

ساختار SDL_CursorData
{
    HCURSOR cursor;

    CachedCursor *cache;
    صحیح hot_x;
    صحیح hot_y;
    صحیح رقم_frames;
    SDL_CursorFrameInfo frames[1];
};

تعریفنوع ساختار
{
    Uint64 xs[5];
    Uint64 ys[5];
    Sint64 residual[2];
    Uint32 dpiscale;
    Uint32 dpidenom;
    صحیح last_گره;
    bool enhanced;
    bool dpiaware;
} WIN_MouseData;

DWORD SDL_last_warp_time = 0;
HCURSOR SDL_cursor = پوچ;
ایستا SDL_Cursor *SDL_blank_cursor = پوچ;
ایستا WIN_MouseData WIN_system_scale_data;

ایستا SDL_Cursor *WIN_CreateCursorAndData(HCURSOR hcursor)
{
    اگر (!hcursor) {
        بازگشت پوچ;
    }

    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, اندازه(*cursor));
    اگر (!cursor) {
        بازگشت پوچ;
    }

    SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, اندازه(*data));
    اگر (!data) {
        SDL_free(cursor);
        بازگشت پوچ;
    }

    data->cursor = hcursor;
    cursor->internal = data;
    بازگشت cursor;
}

ایستا SDL_Cursor *WIN_CreateAnimatedCursorAndData(SDL_CursorFrameInfo *frames, صحیح frame_شمار, صحیح hot_x, صحیح hot_y)
{
    // Dynamically generate cursors at the appropriate DPI
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, اندازه(*cursor));
    اگر (!cursor) {
        بازگشت پوچ;
    }

    SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, اندازه(*data) + (اندازه(SDL_CursorFrameInfo) * (frame_شمار - 1)));
    اگر (!data) {
        SDL_free(cursor);
        بازگشت پوچ;
    }

    data->hot_x = hot_x;
    data->hot_y = hot_y;
    data->رقم_frames = frame_شمار;
    برای (صحیح i = 0; i < frame_شمار; ++i) {
        SDL_Surface *surface = frames[i].surface;
        اگر (surface->flags & SDL_SURFACE_PREALLOCATED) {
            surface = SDL_DuplicateSurface(surface);
            اگر (!surface) {
                وقتی (i > 0) {
                    --i;
                    SDL_DestroySurface(data->frames[i].surface);
                }
                SDL_free(data);
                SDL_free(cursor);
                بازگشت پوچ;
            }
        } وگرنه {
            ++surface->refcount;
        }
        data->frames[i].surface = surface;
        data->frames[i].duration = frames[i].duration;
    }
    cursor->internal = data;
    بازگشت cursor;
}

ایستا bool SaveChunkSize(SDL_IOStream* dst, Sint64 offset)
{
    Sint64 here = SDL_TellIO(dst);
    اگر (here < 0) {
        بازگشت false;
    }
    اگر (SDL_SeekIO(dst, offset, SDL_IO_SEEK_SET) < 0) {
        بازگشت false;
    }

    DWORD size = (DWORD)(here - (offset + اندازه(DWORD)));
    اگر (!SDL_WriteU32LE(dst, size)) {
        بازگشت false;
    }
    بازگشت SDL_SeekIO(dst, here, SDL_IO_SEEK_SET);
}

ایستا bool FillIconEntry(CURSORICONFILEDIRENTRY *entry, SDL_Surface *surface, صحیح hot_x, صحیح hot_y, DWORD dwImageSize, DWORD dwImageOffset)
{
    اگر (surface->props) {
        hot_x = (صحیح)SDL_Get_عدد_Property(surface->props, SDL_PROP_SURFACE_HOTSPOT_X_عدد, hot_x);
        hot_y = (صحیح)SDL_Get_عدد_Property(surface->props, SDL_PROP_SURFACE_HOTSPOT_Y_عدد, hot_y);
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
    بازگشت true;
}

#ifdef SAVE_ICON_PNG

ایستا bool WriteIconSurface(SDL_IOStream *dst, SDL_Surface *surface)
{
    اگر (!SDL_SavePNG_IO(surface, dst, false)) {
        بازگشت false;
    }

    // Image data offsets must be WORD aligned
    Sint64 offset = SDL_TellIO(dst);
    اگر (offset & 1) {
        اگر (!SDL_WriteU8(dst, 0)) {
            بازگشت false;
        }
    }
    بازگشت true;
}

#وگرنه

/* For info on the expected mask format see:
 * https://devblogs.microsoft.com/oldnewthing/20101018-00/?p=12513
 */
ایستا تهی *CreateIconMask(SDL_Surface *surface, size_t *mask_size)
{
    Uint8 *dst;
    ثابت صحیح w = (surface->w + 7) / 8;
    ثابت صحیح pad = (((w) % 4) ? (4 - ((w) % 4)) : 0);
    ثابت صحیح pitch = (w + pad);
    ثابت size_t size = pitch * surface->h;
    ایستا ثابت unsigned نویسه masks[] = { 0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1 };

    تهی *mask = SDL_malloc(size);
    اگر (!mask) {
        بازگشت پوچ;
    }

    dst = (Uint8 *)mask;

    // Make the mask completely transparent.
    SDL_memset(dst, 0xff, size);
    برای (صحیح y = surface->h - 1; y >= 0; --y, dst += pitch) {
        برای (صحیح x = 0; x < surface->w; ++x) {
            Uint8 r, g, b, a;
            SDL_ReadSurfacePixel(surface, x, y, &r, &g, &b, &a);

            اگر (a != 0) {
                // Reset bit of an opaque pixel.
                dst[x >> 3] &= ~masks[x & 7];
            }
        }
    }
    *mask_size = size;
    بازگشت mask;
}

ایستا bool WriteIconSurface(SDL_IOStream *dst, SDL_Surface *surface)
{
    SDL_Surface *temp = پوچ;

    اگر (surface->format != SDL_PIXELFORMAT_ARGB8888) {
        temp = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        اگر (!temp) {
            بازگشت false;
        }
        surface = temp;
    }

    // Cursor data is double height (DIB and mask), stored bottom-up
    bool ok = true;
    size_t mask_size = 0;
    تهی *mask = CreateIconMask(surface, &mask_size);
    اگر (!mask) {
        ok = false;
        برو done;
    }

    BITMAPINFOHEADER bmih;
    SDL_zero(bmih);
    DWORD row_size = surface->w * 4;
    bmih.biSize = اندازه(BITMAPINFOHEADER);
    bmih.biWidth = surface->w;
    bmih.biHeight = surface->h * 2;
    bmih.biPlanes = 1;
    bmih.bi_Bit_شمار = 32;
    bmih.biCompression = BI_RGB;
    bmih.biSizeImage = (DWORD)(surface->h * row_size + mask_size);
    ok &= (SDL_WriteIO(dst, &bmih, اندازه(bmih)) == اندازه(bmih));

    ثابت Uint8 *pix = surface->pixels;
    pix += (surface->h - 1) * surface->pitch;
    برای (صحیح i = 0; i < surface->h; ++i) {
        ok &= (SDL_WriteIO(dst, pix, row_size) == row_size);
        pix -= surface->pitch;
    }
    ok &= (SDL_WriteIO(dst, mask, mask_size) == mask_size);

done:
    SDL_free(mask);
    SDL_DestroySurface(temp);
    بازگشت ok;
}

#endif // SAVE_ICON_PNG

ایستا bool WriteIconFrame(SDL_IOStream *dst, SDL_Surface *surface, صحیح hot_x, صحیح hot_y, اعشاری scale)
{
#ifdef SAVE_MULTIPLE_ICONS
    صحیح شمار = 0;
    SDL_Surface **surfaces = SDL_GetSurfaceImages(surface, &شمار);
    اگر (!surfaces) {
        بازگشت false;
    }
#وگرنه
    surface = SDL_GetSurfaceImage(surface, scale);
    اگر (!surface) {
        بازگشت false;
    }

    صحیح شمار = 1;
    SDL_Surface **surfaces = &surface;
#endif

    // Raymond Chen has more insight into this format at:
    // https://devblogs.microsoft.com/oldnewthing/20101018-00/?p=12513
    bool ok = true;
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('i', 'c', 'o', 'n'));
    Sint64 icon_size_offset = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    Sint64 base_offset = icon_size_offset + اندازه(DWORD);

    CURSORICONFILEDIR dir;
    dir.idReserved = 0;
    dir.idType = 2; // Cursor
    dir.id_شمار = شمار;
    ok &= (SDL_WriteIO(dst, &dir, اندازه(dir)) == اندازه(dir));

    DWORD entries_size = شمار * اندازه(CURSORICONFILEDIRENTRY);
    CURSORICONFILEDIRENTRY *entries = (CURSORICONFILEDIRENTRY *)SDL_malloc(entries_size);
    اگر (!entries) {
        ok = false;
        برو done;
    }
    ok &= (SDL_WriteIO(dst, entries, entries_size) == entries_size);

    Sint64 image_offset = SDL_TellIO(dst);
    برای (صحیح i = 0; i < شمار; ++i) {
        ok &= WriteIconSurface(dst, surfaces[i]);

        Sint64 next_offset = SDL_TellIO(dst);
        DWORD dwImageSize = (DWORD)(next_offset - image_offset);
        DWORD dwImageOffset = (DWORD)(image_offset - base_offset);

        ok &= FillIconEntry(&entries[i], surfaces[i], hot_x, hot_y, dwImageSize, dwImageOffset);

        image_offset = next_offset;
    }

    // Now that we have the icon entries filled out, rewrite them
    ok &= (SDL_SeekIO(dst, base_offset + اندازه(dir), SDL_IO_SEEK_SET) >= 0);
    ok &= (SDL_WriteIO(dst, entries, entries_size) == entries_size);
    ok &= (SDL_SeekIO(dst, image_offset, SDL_IO_SEEK_SET) >= 0);
    SDL_free(entries);

    ok &= SaveChunkSize(dst, icon_size_offset);

done:
#ifdef SAVE_MULTIPLE_ICONS
    SDL_free(surfaces);
#وگرنه
    SDL_DestroySurface(surface);
#endif
    بازگشت ok;
}

/* Windows doesn't have an API to easily create animated cursors from a sequence of images,
 * so we have to build an animated cursor resource file in memory and load it.
 */
ایستا HCURSOR WIN_CreateAnimatedCursorInternal(SDL_CursorFrameInfo *frames, صحیح frame_شمار, صحیح hot_x, صحیح hot_y, اعشاری scale)
{
    HCURSOR hcursor = پوچ;
    SDL_IOStream *dst = SDL_IOFromDynamicMem();
    اگر (!dst) {
        بازگشت پوچ;
    }

    صحیح w = (صحیح)SDL_roundf(frames[0].surface->w * scale);
    صحیح h = (صحیح)SDL_roundf(frames[0].surface->h * scale);

    bool ok = true;
    // RIFF header
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('R', 'I', 'F', 'F'));
    Sint64 riff_size_offset = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('A', 'C', 'O', 'N'));

    // anih header chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('a', 'n', 'i', 'h'));
    ok &= SDL_WriteU32LE(dst, اندازه(ANIHEADER));

    ANIHEADER anih;
    SDL_zero(anih);
    anih.cbSizeof = اندازه(anih);
    anih.frames = frame_شمار;
    anih.steps = frame_شمار;
    anih.jifRate = 1;
    anih.fl = ANI_FLAG_ICON;
    ok &= (SDL_WriteIO(dst, &anih, اندازه(anih)) == اندازه(anih));

    // Rate chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('r', 'a', 't', 'e'));
    ok &= SDL_WriteU32LE(dst, اندازه(DWORD) * frame_شمار);
    برای (صحیح i = 0; i < frame_شمار; ++i) {
        // Animated Win32 cursors are in jiffy units, and one jiffy is 1/60 of a second.
        ثابت دوگانه WIN32_JIFFY = 1000.0 / 60.0;
        DWORD duration = (frames[i].duration ? SDL_lround(frames[i].duration / WIN32_JIFFY) : 0xFFFFFFFF);
        ok &= SDL_WriteU32LE(dst, duration);
    }

    // Frame list
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('L', 'I', 'S', 'T'));
    Sint64 frame_list_size_offset = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('f', 'r', 'a', 'm'));

    برای (صحیح i = 0; i < frame_شمار; ++i) {
        ok &= WriteIconFrame(dst, frames[i].surface, hot_x, hot_y, scale);
    }
    ok &= SaveChunkSize(dst, frame_list_size_offset);

    // All done!
    ok &= SaveChunkSize(dst, riff_size_offset);
    اگر (!ok) {
        // The error has been set above
        برو done;
    }

    BYTE *mem = (BYTE *)SDL_GetPointerProperty(SDL_GetIOProperties(dst), SDL_PROP_IOSTREAM_DYNAMIC_MEMORY_POINTER, پوچ);
    DWORD size = (DWORD)SDL_GetIOSize(dst);
    hcursor = (HCURSOR)CreateIconFromResourceEx(mem, size, FALSE, 0x00030000, w, h, 0);
    اگر (!hcursor) {
        SDL_SetError("CreateIconFromResource failed");
    }

done:
    SDL_CloseIO(dst);

    بازگشت hcursor;
}

ایستا SDL_Cursor *WIN_CreateCursor(SDL_Surface *surface, صحیح hot_x, صحیح hot_y)
{
    SDL_CursorFrameInfo frame = { surface, 0 };
    بازگشت WIN_CreateAnimatedCursorAndData(&frame, 1, hot_x, hot_y);
}

ایستا SDL_Cursor *WIN_CreateAnimatedCursor(SDL_CursorFrameInfo *frames, صحیح frame_شمار, صحیح hot_x, صحیح hot_y)
{
    بازگشت WIN_CreateAnimatedCursorAndData(frames, frame_شمار, hot_x, hot_y);
}

ایستا SDL_Cursor *WIN_CreateBlankCursor(تهی)
{
    SDL_Cursor *cursor = پوچ;
    SDL_Surface *surface = SDL_CreateSurfaceZeroed(32, 32, SDL_PIXELFORMAT_ARGB8888);
    اگر (surface) {
        cursor = WIN_CreateCursor(surface, 0, 0);
        SDL_DestroySurface(surface);
    }
    بازگشت cursor;
}

ایستا SDL_Cursor *WIN_CreateSystemCursor(SDL_SystemCursor id)
{
    LPCTSTR name;

    انتخاب (id) {
    پیشفرض:
        SDL_assert(!"Unknown system cursor ID");
        بازگشت پوچ;
    حالت SDL_SYSTEM_CURSOR_DEFAULT:
        name = IDC_ARROW;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_TEXT:
    حالت SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        name = IDC_IBEAM;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_WAIT:
        name = IDC_WAIT;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_CROSSHAIR:
    حالت SDL_SYSTEM_CURSOR_CELL:
        name = IDC_CROSS;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_PROGRESS:
        name = IDC_APPSTARTING;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_NWSE_RESIZE:
    حالت SDL_SYSTEM_CURSOR_NW_RESIZE:
    حالت SDL_SYSTEM_CURSOR_SE_RESIZE:
        name = IDC_SIZENWSE;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_NESW_RESIZE:
    حالت SDL_SYSTEM_CURSOR_NE_RESIZE:
    حالت SDL_SYSTEM_CURSOR_SW_RESIZE:
        name = IDC_SIZENESW;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_EW_RESIZE:
    حالت SDL_SYSTEM_CURSOR_E_RESIZE:
    حالت SDL_SYSTEM_CURSOR_W_RESIZE:
    حالت SDL_SYSTEM_CURSOR_COL_RESIZE:
        name = IDC_SIZEWE;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_NS_RESIZE:
    حالت SDL_SYSTEM_CURSOR_N_RESIZE:
    حالت SDL_SYSTEM_CURSOR_S_RESIZE:
    حالت SDL_SYSTEM_CURSOR_ROW_RESIZE:
        name = IDC_SIZENS;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_MOVE:
    حالت SDL_SYSTEM_CURSOR_ALL_SCROLL:
        name = IDC_SIZEALL;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_NOT_ALLOWED:
    حالت SDL_SYSTEM_CURSOR_NO_DROP:
        name = IDC_NO;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_POINTER:
    حالت SDL_SYSTEM_CURSOR_CONTEXT_MENU:
    حالت SDL_SYSTEM_CURSOR_ALIAS:
    حالت SDL_SYSTEM_CURSOR_COPY:
    حالت SDL_SYSTEM_CURSOR_GRAB:
    حالت SDL_SYSTEM_CURSOR_GRABBING:
    حالت SDL_SYSTEM_CURSOR_ZOOM_IN:
    حالت SDL_SYSTEM_CURSOR_ZOOM_OUT:
        name = IDC_HAND;
        بشکن;
    حالت SDL_SYSTEM_CURSOR_HELP:
        name = IDC_HELP;
        بشکن;
    }
    بازگشت WIN_CreateCursorAndData(LoadCursor(پوچ, name));
}

ایستا SDL_Cursor *WIN_CreateDefaultCursor(تهی)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    بازگشت WIN_CreateSystemCursor(id);
}

ایستا تهی WIN_FreeCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *data = cursor->internal;

    برای (صحیح i = 0; i < data->رقم_frames; ++i) {
        SDL_DestroySurface(data->frames[i].surface);
    }
    وقتی (data->cache) {
        CachedCursor *entry = data->cache;
        data->cache = entry->next;
        اگر (entry->cursor) {
            DestroyCursor(entry->cursor);
        }
        SDL_free(entry);
    }
    اگر (data->cursor) {
        DestroyCursor(data->cursor);
    }
    SDL_free(data);
    SDL_free(cursor);
}

ایستا HCURSOR GetCachedCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *data = cursor->internal;

    اعشاری scale = 1.0f;
    اگر (SDL_GetHintBoolean(SDL_HINT_MOUSE_DPI_SCALE_CURSORS, false)) {
        scale = SDL_GetDisplayContentScale(SDL_GetDisplayForWindow(SDL_GetMouseFocus()));
        اگر (scale == 0.0f) {
            scale = 1.0f;
        }
    }
    برای (CachedCursor *entry = data->cache; entry; entry = entry->next) {
        اگر (scale == entry->scale) {
            بازگشت entry->cursor;
        }
    }

    // Need to create a cursor for this content scale
    HCURSOR hcursor = WIN_CreateAnimatedCursorInternal(data->frames, data->رقم_frames, data->hot_x, data->hot_y, scale);
    اگر (!hcursor) {
        بازگشت پوچ;
    }

    CachedCursor *entry = (CachedCursor *)SDL_calloc(1, اندازه(*entry));
    اگر (!entry) {
        DestroyCursor(hcursor);
        بازگشت پوچ;
    }
    entry->cursor = hcursor;
    entry->scale = scale;
    entry->next = data->cache;
    data->cache = entry;

    بازگشت hcursor;
}

ایستا bool WIN_ShowCursor(SDL_Cursor *cursor)
{
    اگر (!cursor) {
        اگر (GetSystemMetrics(SM_REMOTESESSION)) {
            // Use a blank cursor so we continue to get relative motion over RDP
            cursor = SDL_blank_cursor;
        }
    }
    اگر (cursor) {
        SDL_CursorData *data = cursor->internal;
        اگر (data->رقم_frames > 0) {
            SDL_cursor = GetCachedCursor(cursor);
        } وگرنه {
            SDL_cursor = data->cursor;
        }
    } وگرنه {
        SDL_cursor = پوچ;
    }
    اگر (SDL_GetMouseFocus() != پوچ) {
        SetCursor(SDL_cursor);
    }
    بازگشت true;
}

تهی WIN_SetCursorPos(صحیح x, صحیح y)
{
    // We need to jitter the value because otherwise Windows will occasionally inexplicably ignore the SetCursorPos() or SendInput()
    SetCursorPos(x, y);
    SetCursorPos(x + 1, y);
    SetCursorPos(x, y);

    // Flush any mouse motion prior to or associated with this warp
#ifdef _MSC_VER // We explicitly want to use GetTickCount(), not GetTickCount64()
#pragma warning(افزودن)
#pragma warning(disable : 28159)
#endif
    SDL_last_warp_time = Get_Tick_شمار();
    اگر (!SDL_last_warp_time) {
        SDL_last_warp_time = 1;
    }
#ifdef _MSC_VER
#pragma warning(برداشت)
#endif
}

ایستا bool WIN_WarpMouse(SDL_Window *window, اعشاری x, اعشاری y)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    POINT pt;

    // Don't warp the mouse while we're doing a modal interaction
    اگر (data->in_title_click || data->focus_click_pending) {
        بازگشت true;
    }

    pt.x = (صحیح)SDL_roundf(x);
    pt.y = (صحیح)SDL_roundf(y);
    ClientToScreen(hwnd, &pt);
    WIN_SetCursorPos(pt.x, pt.y);

    // Send the exact mouse motion associated with this warp
    SDL_SendMouseMotion(0, window, SDL_GLOBAL_MOUSE_ID, false, x, y);
    بازگشت true;
}

ایستا bool WIN_WarpMouseGlobal(اعشاری x, اعشاری y)
{
    POINT pt;

    pt.x = (صحیح)SDL_roundf(x);
    pt.y = (صحیح)SDL_roundf(y);
    SetCursorPos(pt.x, pt.y);
    بازگشت true;
}

ایستا bool WIN_SetRelativeMouseMode(bool enabled)
{
    بازگشت WIN_SetRawMouseEnabled(SDL_GetVideoDevice(), enabled);
}

ایستا bool WIN_CaptureMouse(SDL_Window *window)
{
    اگر (window) {
        SDL_WindowData *data = window->internal;
        SetCapture(data->hwnd);
    } وگرنه {
        SDL_Window *focus_window = SDL_GetMouseFocus();

        اگر (focus_window) {
            SDL_WindowData *data = focus_window->internal;
            اگر (!data->mouse_tracked) {
                SDL_SetMouseFocus(پوچ);
            }
        }
        ReleaseCapture();
    }

    بازگشت true;
}

ایستا SDL_MouseButtonFlags WIN_GetGlobalMouseState(اعشاری *x, اعشاری *y)
{
    SDL_MouseButtonFlags result = 0;
    POINT pt = { 0, 0 };
    bool swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;

    GetCursorPos(&pt);
    *x = (اعشاری)pt.x;
    *y = (اعشاری)pt.y;

    result |= Get_Async_کلید_State(!swapButtons ? VK_LBUTTON : VK_RBUTTON) & 0x8000 ? SDL_BUTTON_LMASK : 0;
    result |= Get_Async_کلید_State(!swapButtons ? VK_RBUTTON : VK_LBUTTON) & 0x8000 ? SDL_BUTTON_RMASK : 0;
    result |= Get_Async_کلید_State(VK_MBUTTON) & 0x8000 ? SDL_BUTTON_MMASK : 0;
    result |= Get_Async_کلید_State(VK_XBUTTON1) & 0x8000 ? SDL_BUTTON_X1MASK : 0;
    result |= Get_Async_کلید_State(VK_XBUTTON2) & 0x8000 ? SDL_BUTTON_X2MASK : 0;

    بازگشت result;
}

ایستا تهی WIN_ApplySystemScale(تهی *internal, Uint64 timestamp, SDL_Window *window, SDL_MouseID mouseID, اعشاری *x, اعشاری *y)
{
    اگر (!internal) {
        بازگشت;
    }
    WIN_MouseData *data = (WIN_MouseData *)internal;

    SDL_VideoDisplay *display = window ? SDL_GetVideoDisplayForWindow(window) : SDL_GetVideoDisplay(SDL_GetPrimaryDisplay());

    Sint64 ix = (Sint64)*x * 65536;
    Sint64 iy = (Sint64)*y * 65536;
    Uint32 dpi = display ? (Uint32)(display->content_scale * USER_DEFAULT_SCREEN_DPI) : USER_DEFAULT_SCREEN_DPI;

    اگر (!data->enhanced) { // early return if flat scale
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
        *x = (اعشاری)ix / 65536.0f;
        *y = (اعشاری)iy / 65536.0f;
        بازگشت;
    }

    Uint64 *xs = data->xs;
    Uint64 *ys = data->ys;
    Uint64 absx = SDL_abs(ix);
    Uint64 absy = SDL_abs(iy);
    Uint64 speed = SDL_min(absx, absy) + (SDL_max(absx, absy) << 1); // super cursed approximation used by Windows
    اگر (speed == 0) {
        بازگشت;
    }

    صحیح i, j, k;
    برای (i = 1; i < 5; i++) {
        j = i;
        اگر (speed < xs[j]) {
            بشکن;
        }
    }
    i -= 1;
    j -= 1;
    k = data->last_گره;
    data->last_گره = j;

    Uint32 denom = data->dpidenom;
    Sint64 scale = 0;
    Sint64 xdiff = xs[j+1] - xs[j];
    Sint64 ydiff = ys[j+1] - ys[j];
    اگر (xdiff != 0) {
        Sint64 slope = ydiff / xdiff;
        Sint64 inter = slope * xs[i] - ys[i];
        scale += slope - inter / speed;
    }

    اگر (j > k) {
        denom <<= 1;
        xdiff = xs[k+1] - xs[k];
        ydiff = ys[k+1] - ys[k];
        اگر (xdiff != 0) {
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
    *x = (اعشاری)ix / 65536.0f;
    *y = (اعشاری)iy / 65536.0f;
}

تهی WIN_InitMouse(SDL_VideoDevice *_this)
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

تهی WIN_QuitMouse(SDL_VideoDevice *_this)
{
    اگر (SDL_blank_cursor) {
        WIN_FreeCursor(SDL_blank_cursor);
        SDL_blank_cursor = پوچ;
    }
}

ایستا تهی ReadMouseCurve(صحیح v, Uint64 xs[5], Uint64 ys[5])
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
    DWORD xsize = اندازه(xbuff);
    DWORD ysize = اندازه(ybuff);
    HKEY open_handle;
    اگر (Reg_Open_کلید_Ex_W(HKEY_CURRENT_USER, L"Control Panel\\Mouse", 0, کلید_READ, &open_handle) == ERROR_SUCCESS) {
        Reg_Query_مقدار_Ex_W(open_handle, L"SmoothMouseXCurve", پوچ, پوچ, (BYTE*)xbuff, &xsize);
        Reg_Query_مقدار_Ex_W(open_handle, L"SmoothMouseYCurve", پوچ, پوچ, (BYTE*)ybuff, &ysize);
        Reg_Close_کلید(open_handle);
    }
    xs[0] = 0; // first node must always be origin
    ys[0] = 0; // first node must always be origin
    صحیح i;
    برای (i = 1; i < 5; i++) {
        xs[i] = (7 * (Uint64)xbuff[i * 2]);
        ys[i] = (v * (Uint64)ybuff[i * 2]) << 17;
    }
}

تهی WIN_UpdateMouseSystemScale(تهی)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    اگر (mouse->ApplySystemScale == WIN_ApplySystemScale) {
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

    صحیح v = 10;
    اگر (SystemParametersInfo(SPI_GETMOUSESPEED, 0, &v, 0)) {
        v = SDL_max(1, SDL_min(v, 20));
        data->dpiscale = SDL_max(SDL_max(v, (v - 2) * 4), (v - 6) * 8);
    }

    صحیح params[3];
    اگر (SystemParametersInfo(SPI_GETMOUSE, 0, &params, 0)) {
        data->enhanced = params[2] ? true : false;
        اگر (params[2]) {
            ReadMouseCurve(v, data->xs, data->ys);
        }
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS

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
#অন্তর্ভাব "SDL_internal.h"

#যদি defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#অন্তর্ভাব "SDL_windowsvideo.h"
#অন্তর্ভাব "SDL_windowsevents.h"
#অন্তর্ভাব "SDL_windowsrawinput.h"

#অন্তর্ভাব "../SDL_video_c.h"
#অন্তর্ভাব "../../events/SDL_mouse_c.h"
#অন্তর্ভাব "../../joystick/usb_ids.h"
#অন্তর্ভাব "../../core/windows/SDL_windows.h" // for checking windows version

#define RIFF_FOURCC(c0, c1, c2, c3)                 \
    ((DWORD)(BYTE)(c0) | ((DWORD)(BYTE)(c1) << 8) | \
     ((DWORD)(BYTE)(c2) << 16) | ((DWORD)(BYTE)(c3) << 24))

#define ANI_FLAG_ICON 0x1

#pragma pack(ঠেলো, 1)

প্রকারনির্দেশ সংরচনা
{
    BYTE bWidth;
    BYTE bHeight;
    BYTE b_Color_গুনতি;
    BYTE bReserved;
    WORD xHotspot;
    WORD yHotspot;
    DWORD dwImageSize;
    DWORD dwImageOffset;
} CURSORICONFILEDIRENTRY;

প্রকারনির্দেশ সংরচনা
{
    WORD idReserved;
    WORD idType;
    WORD id_গুনতি;
} CURSORICONFILEDIR;

প্রকারনির্দেশ সংরচনা
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

#pragma pack(বের_করো)

প্রকারনির্দেশ সংরচনা CachedCursor
{
    ভিন্ন scale;
    HCURSOR cursor;
    সংরচনা CachedCursor *next;
} CachedCursor;

সংরচনা SDL_CursorData
{
    HCURSOR cursor;

    CachedCursor *cache;
    পূর্ণাঙ্ক hot_x;
    পূর্ণাঙ্ক hot_y;
    পূর্ণাঙ্ক অঙ্ক_frames;
    SDL_CursorFrameInfo frames[1];
};

প্রকারনির্দেশ সংরচনা
{
    Uint64 xs[5];
    Uint64 ys[5];
    Sint64 residual[2];
    Uint32 dpiscale;
    Uint32 dpidenom;
    পূর্ণাঙ্ক last_গ্রন্থি;
    bool enhanced;
    bool dpiaware;
} WIN_MouseData;

DWORD SDL_last_warp_time = 0;
HCURSOR SDL_cursor = রিক্ত;
স্থির SDL_Cursor *SDL_blank_cursor = রিক্ত;
স্থির WIN_MouseData WIN_system_scale_data;

স্থির SDL_Cursor *WIN_CreateCursorAndData(HCURSOR hcursor)
{
    যদি (!hcursor) {
        প্রত্যাগম রিক্ত;
    }

    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, পরিমাণ(*cursor));
    যদি (!cursor) {
        প্রত্যাগম রিক্ত;
    }

    SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, পরিমাণ(*data));
    যদি (!data) {
        SDL_free(cursor);
        প্রত্যাগম রিক্ত;
    }

    data->cursor = hcursor;
    cursor->internal = data;
    প্রত্যাগম cursor;
}

স্থির SDL_Cursor *WIN_CreateAnimatedCursorAndData(SDL_CursorFrameInfo *frames, পূর্ণাঙ্ক frame_গুনতি, পূর্ণাঙ্ক hot_x, পূর্ণাঙ্ক hot_y)
{
    // Dynamically generate cursors at the appropriate DPI
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, পরিমাণ(*cursor));
    যদি (!cursor) {
        প্রত্যাগম রিক্ত;
    }

    SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, পরিমাণ(*data) + (পরিমাণ(SDL_CursorFrameInfo) * (frame_গুনতি - 1)));
    যদি (!data) {
        SDL_free(cursor);
        প্রত্যাগম রিক্ত;
    }

    data->hot_x = hot_x;
    data->hot_y = hot_y;
    data->অঙ্ক_frames = frame_গুনতি;
    প্রতি (পূর্ণাঙ্ক i = 0; i < frame_গুনতি; ++i) {
        SDL_Surface *surface = frames[i].surface;
        যদি (surface->flags & SDL_SURFACE_PREALLOCATED) {
            surface = SDL_DuplicateSurface(surface);
            যদি (!surface) {
                যাবত্ (i > 0) {
                    --i;
                    SDL_DestroySurface(data->frames[i].surface);
                }
                SDL_free(data);
                SDL_free(cursor);
                প্রত্যাগম রিক্ত;
            }
        } অন্যথা {
            ++surface->refcount;
        }
        data->frames[i].surface = surface;
        data->frames[i].duration = frames[i].duration;
    }
    cursor->internal = data;
    প্রত্যাগম cursor;
}

স্থির bool SaveChunkSize(SDL_IOStream* dst, Sint64 offset)
{
    Sint64 here = SDL_TellIO(dst);
    যদি (here < 0) {
        প্রত্যাগম false;
    }
    যদি (SDL_SeekIO(dst, offset, SDL_IO_SEEK_SET) < 0) {
        প্রত্যাগম false;
    }

    DWORD size = (DWORD)(here - (offset + পরিমাণ(DWORD)));
    যদি (!SDL_WriteU32LE(dst, size)) {
        প্রত্যাগম false;
    }
    প্রত্যাগম SDL_SeekIO(dst, here, SDL_IO_SEEK_SET);
}

স্থির bool FillIconEntry(CURSORICONFILEDIRENTRY *entry, SDL_Surface *surface, পূর্ণাঙ্ক hot_x, পূর্ণাঙ্ক hot_y, DWORD dwImageSize, DWORD dwImageOffset)
{
    যদি (surface->props) {
        hot_x = (পূর্ণাঙ্ক)SDL_Get_সংখ্যা_Property(surface->props, SDL_PROP_SURFACE_HOTSPOT_X_সংখ্যা, hot_x);
        hot_y = (পূর্ণাঙ্ক)SDL_Get_সংখ্যা_Property(surface->props, SDL_PROP_SURFACE_HOTSPOT_Y_সংখ্যা, hot_y);
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
    প্রত্যাগম true;
}

#ifdef SAVE_ICON_PNG

স্থির bool WriteIconSurface(SDL_IOStream *dst, SDL_Surface *surface)
{
    যদি (!SDL_SavePNG_IO(surface, dst, false)) {
        প্রত্যাগম false;
    }

    // Image data offsets must be WORD aligned
    Sint64 offset = SDL_TellIO(dst);
    যদি (offset & 1) {
        যদি (!SDL_WriteU8(dst, 0)) {
            প্রত্যাগম false;
        }
    }
    প্রত্যাগম true;
}

#অন্যথা

/* For info on the expected mask format see:
 * https://devblogs.microsoft.com/oldnewthing/20101018-00/?p=12513
 */
স্থির শূন্য *CreateIconMask(SDL_Surface *surface, size_t *mask_size)
{
    Uint8 *dst;
    ধ্রুব পূর্ণাঙ্ক w = (surface->w + 7) / 8;
    ধ্রুব পূর্ণাঙ্ক pad = (((w) % 4) ? (4 - ((w) % 4)) : 0);
    ধ্রুব পূর্ণাঙ্ক pitch = (w + pad);
    ধ্রুব size_t size = pitch * surface->h;
    স্থির ধ্রুব unsigned বর্ণ masks[] = { 0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1 };

    শূন্য *mask = SDL_malloc(size);
    যদি (!mask) {
        প্রত্যাগম রিক্ত;
    }

    dst = (Uint8 *)mask;

    // Make the mask completely transparent.
    SDL_memset(dst, 0xff, size);
    প্রতি (পূর্ণাঙ্ক y = surface->h - 1; y >= 0; --y, dst += pitch) {
        প্রতি (পূর্ণাঙ্ক x = 0; x < surface->w; ++x) {
            Uint8 r, g, b, a;
            SDL_ReadSurfacePixel(surface, x, y, &r, &g, &b, &a);

            যদি (a != 0) {
                // Reset bit of an opaque pixel.
                dst[x >> 3] &= ~masks[x & 7];
            }
        }
    }
    *mask_size = size;
    প্রত্যাগম mask;
}

স্থির bool WriteIconSurface(SDL_IOStream *dst, SDL_Surface *surface)
{
    SDL_Surface *temp = রিক্ত;

    যদি (surface->format != SDL_PIXELFORMAT_ARGB8888) {
        temp = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        যদি (!temp) {
            প্রত্যাগম false;
        }
        surface = temp;
    }

    // Cursor data is double height (DIB and mask), stored bottom-up
    bool ok = true;
    size_t mask_size = 0;
    শূন্য *mask = CreateIconMask(surface, &mask_size);
    যদি (!mask) {
        ok = false;
        গচ্ছ done;
    }

    BITMAPINFOHEADER bmih;
    SDL_zero(bmih);
    DWORD row_size = surface->w * 4;
    bmih.biSize = পরিমাণ(BITMAPINFOHEADER);
    bmih.biWidth = surface->w;
    bmih.biHeight = surface->h * 2;
    bmih.biPlanes = 1;
    bmih.bi_Bit_গুনতি = 32;
    bmih.biCompression = BI_RGB;
    bmih.biSizeImage = (DWORD)(surface->h * row_size + mask_size);
    ok &= (SDL_WriteIO(dst, &bmih, পরিমাণ(bmih)) == পরিমাণ(bmih));

    ধ্রুব Uint8 *pix = surface->pixels;
    pix += (surface->h - 1) * surface->pitch;
    প্রতি (পূর্ণাঙ্ক i = 0; i < surface->h; ++i) {
        ok &= (SDL_WriteIO(dst, pix, row_size) == row_size);
        pix -= surface->pitch;
    }
    ok &= (SDL_WriteIO(dst, mask, mask_size) == mask_size);

done:
    SDL_free(mask);
    SDL_DestroySurface(temp);
    প্রত্যাগম ok;
}

#endif // SAVE_ICON_PNG

স্থির bool WriteIconFrame(SDL_IOStream *dst, SDL_Surface *surface, পূর্ণাঙ্ক hot_x, পূর্ণাঙ্ক hot_y, ভিন্ন scale)
{
#ifdef SAVE_MULTIPLE_ICONS
    পূর্ণাঙ্ক গুনতি = 0;
    SDL_Surface **surfaces = SDL_GetSurfaceImages(surface, &গুনতি);
    যদি (!surfaces) {
        প্রত্যাগম false;
    }
#অন্যথা
    surface = SDL_GetSurfaceImage(surface, scale);
    যদি (!surface) {
        প্রত্যাগম false;
    }

    পূর্ণাঙ্ক গুনতি = 1;
    SDL_Surface **surfaces = &surface;
#endif

    // Raymond Chen has more insight into this format at:
    // https://devblogs.microsoft.com/oldnewthing/20101018-00/?p=12513
    bool ok = true;
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('i', 'c', 'o', 'n'));
    Sint64 icon_size_offset = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    Sint64 base_offset = icon_size_offset + পরিমাণ(DWORD);

    CURSORICONFILEDIR dir;
    dir.idReserved = 0;
    dir.idType = 2; // Cursor
    dir.id_গুনতি = গুনতি;
    ok &= (SDL_WriteIO(dst, &dir, পরিমাণ(dir)) == পরিমাণ(dir));

    DWORD entries_size = গুনতি * পরিমাণ(CURSORICONFILEDIRENTRY);
    CURSORICONFILEDIRENTRY *entries = (CURSORICONFILEDIRENTRY *)SDL_malloc(entries_size);
    যদি (!entries) {
        ok = false;
        গচ্ছ done;
    }
    ok &= (SDL_WriteIO(dst, entries, entries_size) == entries_size);

    Sint64 image_offset = SDL_TellIO(dst);
    প্রতি (পূর্ণাঙ্ক i = 0; i < গুনতি; ++i) {
        ok &= WriteIconSurface(dst, surfaces[i]);

        Sint64 next_offset = SDL_TellIO(dst);
        DWORD dwImageSize = (DWORD)(next_offset - image_offset);
        DWORD dwImageOffset = (DWORD)(image_offset - base_offset);

        ok &= FillIconEntry(&entries[i], surfaces[i], hot_x, hot_y, dwImageSize, dwImageOffset);

        image_offset = next_offset;
    }

    // Now that we have the icon entries filled out, rewrite them
    ok &= (SDL_SeekIO(dst, base_offset + পরিমাণ(dir), SDL_IO_SEEK_SET) >= 0);
    ok &= (SDL_WriteIO(dst, entries, entries_size) == entries_size);
    ok &= (SDL_SeekIO(dst, image_offset, SDL_IO_SEEK_SET) >= 0);
    SDL_free(entries);

    ok &= SaveChunkSize(dst, icon_size_offset);

done:
#ifdef SAVE_MULTIPLE_ICONS
    SDL_free(surfaces);
#অন্যথা
    SDL_DestroySurface(surface);
#endif
    প্রত্যাগম ok;
}

/* Windows doesn't have an API to easily create animated cursors from a sequence of images,
 * so we have to build an animated cursor resource file in memory and load it.
 */
স্থির HCURSOR WIN_CreateAnimatedCursorInternal(SDL_CursorFrameInfo *frames, পূর্ণাঙ্ক frame_গুনতি, পূর্ণাঙ্ক hot_x, পূর্ণাঙ্ক hot_y, ভিন্ন scale)
{
    HCURSOR hcursor = রিক্ত;
    SDL_IOStream *dst = SDL_IOFromDynamicMem();
    যদি (!dst) {
        প্রত্যাগম রিক্ত;
    }

    পূর্ণাঙ্ক w = (পূর্ণাঙ্ক)SDL_roundf(frames[0].surface->w * scale);
    পূর্ণাঙ্ক h = (পূর্ণাঙ্ক)SDL_roundf(frames[0].surface->h * scale);

    bool ok = true;
    // RIFF header
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('R', 'I', 'F', 'F'));
    Sint64 riff_size_offset = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('A', 'C', 'O', 'N'));

    // anih header chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('a', 'n', 'i', 'h'));
    ok &= SDL_WriteU32LE(dst, পরিমাণ(ANIHEADER));

    ANIHEADER anih;
    SDL_zero(anih);
    anih.cbSizeof = পরিমাণ(anih);
    anih.frames = frame_গুনতি;
    anih.steps = frame_গুনতি;
    anih.jifRate = 1;
    anih.fl = ANI_FLAG_ICON;
    ok &= (SDL_WriteIO(dst, &anih, পরিমাণ(anih)) == পরিমাণ(anih));

    // Rate chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('r', 'a', 't', 'e'));
    ok &= SDL_WriteU32LE(dst, পরিমাণ(DWORD) * frame_গুনতি);
    প্রতি (পূর্ণাঙ্ক i = 0; i < frame_গুনতি; ++i) {
        // Animated Win32 cursors are in jiffy units, and one jiffy is 1/60 of a second.
        ধ্রুব দ্বিগুণ WIN32_JIFFY = 1000.0 / 60.0;
        DWORD duration = (frames[i].duration ? SDL_lround(frames[i].duration / WIN32_JIFFY) : 0xFFFFFFFF);
        ok &= SDL_WriteU32LE(dst, duration);
    }

    // Frame list
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('L', 'I', 'S', 'T'));
    Sint64 frame_list_size_offset = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('f', 'r', 'a', 'm'));

    প্রতি (পূর্ণাঙ্ক i = 0; i < frame_গুনতি; ++i) {
        ok &= WriteIconFrame(dst, frames[i].surface, hot_x, hot_y, scale);
    }
    ok &= SaveChunkSize(dst, frame_list_size_offset);

    // All done!
    ok &= SaveChunkSize(dst, riff_size_offset);
    যদি (!ok) {
        // The error has been set above
        গচ্ছ done;
    }

    BYTE *mem = (BYTE *)SDL_GetPointerProperty(SDL_GetIOProperties(dst), SDL_PROP_IOSTREAM_DYNAMIC_MEMORY_POINTER, রিক্ত);
    DWORD size = (DWORD)SDL_GetIOSize(dst);
    hcursor = (HCURSOR)CreateIconFromResourceEx(mem, size, FALSE, 0x00030000, w, h, 0);
    যদি (!hcursor) {
        SDL_SetError("CreateIconFromResource failed");
    }

done:
    SDL_CloseIO(dst);

    প্রত্যাগম hcursor;
}

স্থির SDL_Cursor *WIN_CreateCursor(SDL_Surface *surface, পূর্ণাঙ্ক hot_x, পূর্ণাঙ্ক hot_y)
{
    SDL_CursorFrameInfo frame = { surface, 0 };
    প্রত্যাগম WIN_CreateAnimatedCursorAndData(&frame, 1, hot_x, hot_y);
}

স্থির SDL_Cursor *WIN_CreateAnimatedCursor(SDL_CursorFrameInfo *frames, পূর্ণাঙ্ক frame_গুনতি, পূর্ণাঙ্ক hot_x, পূর্ণাঙ্ক hot_y)
{
    প্রত্যাগম WIN_CreateAnimatedCursorAndData(frames, frame_গুনতি, hot_x, hot_y);
}

স্থির SDL_Cursor *WIN_CreateBlankCursor(শূন্য)
{
    SDL_Cursor *cursor = রিক্ত;
    SDL_Surface *surface = SDL_CreateSurfaceZeroed(32, 32, SDL_PIXELFORMAT_ARGB8888);
    যদি (surface) {
        cursor = WIN_CreateCursor(surface, 0, 0);
        SDL_DestroySurface(surface);
    }
    প্রত্যাগম cursor;
}

স্থির SDL_Cursor *WIN_CreateSystemCursor(SDL_SystemCursor id)
{
    LPCTSTR name;

    বিকল্প (id) {
    স্বভাব:
        SDL_assert(!"Unknown system cursor ID");
        প্রত্যাগম রিক্ত;
    পক্ষ SDL_SYSTEM_CURSOR_DEFAULT:
        name = IDC_ARROW;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_TEXT:
    পক্ষ SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        name = IDC_IBEAM;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_WAIT:
        name = IDC_WAIT;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_CROSSHAIR:
    পক্ষ SDL_SYSTEM_CURSOR_CELL:
        name = IDC_CROSS;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_PROGRESS:
        name = IDC_APPSTARTING;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_NWSE_RESIZE:
    পক্ষ SDL_SYSTEM_CURSOR_NW_RESIZE:
    পক্ষ SDL_SYSTEM_CURSOR_SE_RESIZE:
        name = IDC_SIZENWSE;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_NESW_RESIZE:
    পক্ষ SDL_SYSTEM_CURSOR_NE_RESIZE:
    পক্ষ SDL_SYSTEM_CURSOR_SW_RESIZE:
        name = IDC_SIZENESW;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_EW_RESIZE:
    পক্ষ SDL_SYSTEM_CURSOR_E_RESIZE:
    পক্ষ SDL_SYSTEM_CURSOR_W_RESIZE:
    পক্ষ SDL_SYSTEM_CURSOR_COL_RESIZE:
        name = IDC_SIZEWE;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_NS_RESIZE:
    পক্ষ SDL_SYSTEM_CURSOR_N_RESIZE:
    পক্ষ SDL_SYSTEM_CURSOR_S_RESIZE:
    পক্ষ SDL_SYSTEM_CURSOR_ROW_RESIZE:
        name = IDC_SIZENS;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_MOVE:
    পক্ষ SDL_SYSTEM_CURSOR_ALL_SCROLL:
        name = IDC_SIZEALL;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_NOT_ALLOWED:
    পক্ষ SDL_SYSTEM_CURSOR_NO_DROP:
        name = IDC_NO;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_POINTER:
    পক্ষ SDL_SYSTEM_CURSOR_CONTEXT_MENU:
    পক্ষ SDL_SYSTEM_CURSOR_ALIAS:
    পক্ষ SDL_SYSTEM_CURSOR_COPY:
    পক্ষ SDL_SYSTEM_CURSOR_GRAB:
    পক্ষ SDL_SYSTEM_CURSOR_GRABBING:
    পক্ষ SDL_SYSTEM_CURSOR_ZOOM_IN:
    পক্ষ SDL_SYSTEM_CURSOR_ZOOM_OUT:
        name = IDC_HAND;
        ভঙ্গ;
    পক্ষ SDL_SYSTEM_CURSOR_HELP:
        name = IDC_HELP;
        ভঙ্গ;
    }
    প্রত্যাগম WIN_CreateCursorAndData(LoadCursor(রিক্ত, name));
}

স্থির SDL_Cursor *WIN_CreateDefaultCursor(শূন্য)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    প্রত্যাগম WIN_CreateSystemCursor(id);
}

স্থির শূন্য WIN_FreeCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *data = cursor->internal;

    প্রতি (পূর্ণাঙ্ক i = 0; i < data->অঙ্ক_frames; ++i) {
        SDL_DestroySurface(data->frames[i].surface);
    }
    যাবত্ (data->cache) {
        CachedCursor *entry = data->cache;
        data->cache = entry->next;
        যদি (entry->cursor) {
            DestroyCursor(entry->cursor);
        }
        SDL_free(entry);
    }
    যদি (data->cursor) {
        DestroyCursor(data->cursor);
    }
    SDL_free(data);
    SDL_free(cursor);
}

স্থির HCURSOR GetCachedCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *data = cursor->internal;

    ভিন্ন scale = 1.0f;
    যদি (SDL_GetHintBoolean(SDL_HINT_MOUSE_DPI_SCALE_CURSORS, false)) {
        scale = SDL_GetDisplayContentScale(SDL_GetDisplayForWindow(SDL_GetMouseFocus()));
        যদি (scale == 0.0f) {
            scale = 1.0f;
        }
    }
    প্রতি (CachedCursor *entry = data->cache; entry; entry = entry->next) {
        যদি (scale == entry->scale) {
            প্রত্যাগম entry->cursor;
        }
    }

    // Need to create a cursor for this content scale
    HCURSOR hcursor = WIN_CreateAnimatedCursorInternal(data->frames, data->অঙ্ক_frames, data->hot_x, data->hot_y, scale);
    যদি (!hcursor) {
        প্রত্যাগম রিক্ত;
    }

    CachedCursor *entry = (CachedCursor *)SDL_calloc(1, পরিমাণ(*entry));
    যদি (!entry) {
        DestroyCursor(hcursor);
        প্রত্যাগম রিক্ত;
    }
    entry->cursor = hcursor;
    entry->scale = scale;
    entry->next = data->cache;
    data->cache = entry;

    প্রত্যাগম hcursor;
}

স্থির bool WIN_ShowCursor(SDL_Cursor *cursor)
{
    যদি (!cursor) {
        যদি (GetSystemMetrics(SM_REMOTESESSION)) {
            // Use a blank cursor so we continue to get relative motion over RDP
            cursor = SDL_blank_cursor;
        }
    }
    যদি (cursor) {
        SDL_CursorData *data = cursor->internal;
        যদি (data->অঙ্ক_frames > 0) {
            SDL_cursor = GetCachedCursor(cursor);
        } অন্যথা {
            SDL_cursor = data->cursor;
        }
    } অন্যথা {
        SDL_cursor = রিক্ত;
    }
    যদি (SDL_GetMouseFocus() != রিক্ত) {
        SetCursor(SDL_cursor);
    }
    প্রত্যাগম true;
}

শূন্য WIN_SetCursorPos(পূর্ণাঙ্ক x, পূর্ণাঙ্ক y)
{
    // We need to jitter the value because otherwise Windows will occasionally inexplicably ignore the SetCursorPos() or SendInput()
    SetCursorPos(x, y);
    SetCursorPos(x + 1, y);
    SetCursorPos(x, y);

    // Flush any mouse motion prior to or associated with this warp
#ifdef _MSC_VER // We explicitly want to use GetTickCount(), not GetTickCount64()
#pragma warning(ঠেলো)
#pragma warning(disable : 28159)
#endif
    SDL_last_warp_time = Get_Tick_গুনতি();
    যদি (!SDL_last_warp_time) {
        SDL_last_warp_time = 1;
    }
#ifdef _MSC_VER
#pragma warning(বের_করো)
#endif
}

স্থির bool WIN_WarpMouse(SDL_Window *window, ভিন্ন x, ভিন্ন y)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    POINT pt;

    // Don't warp the mouse while we're doing a modal interaction
    যদি (data->in_title_click || data->focus_click_pending) {
        প্রত্যাগম true;
    }

    pt.x = (পূর্ণাঙ্ক)SDL_roundf(x);
    pt.y = (পূর্ণাঙ্ক)SDL_roundf(y);
    ClientToScreen(hwnd, &pt);
    WIN_SetCursorPos(pt.x, pt.y);

    // Send the exact mouse motion associated with this warp
    SDL_SendMouseMotion(0, window, SDL_GLOBAL_MOUSE_ID, false, x, y);
    প্রত্যাগম true;
}

স্থির bool WIN_WarpMouseGlobal(ভিন্ন x, ভিন্ন y)
{
    POINT pt;

    pt.x = (পূর্ণাঙ্ক)SDL_roundf(x);
    pt.y = (পূর্ণাঙ্ক)SDL_roundf(y);
    SetCursorPos(pt.x, pt.y);
    প্রত্যাগম true;
}

স্থির bool WIN_SetRelativeMouseMode(bool enabled)
{
    প্রত্যাগম WIN_SetRawMouseEnabled(SDL_GetVideoDevice(), enabled);
}

স্থির bool WIN_CaptureMouse(SDL_Window *window)
{
    যদি (window) {
        SDL_WindowData *data = window->internal;
        SetCapture(data->hwnd);
    } অন্যথা {
        SDL_Window *focus_window = SDL_GetMouseFocus();

        যদি (focus_window) {
            SDL_WindowData *data = focus_window->internal;
            যদি (!data->mouse_tracked) {
                SDL_SetMouseFocus(রিক্ত);
            }
        }
        ReleaseCapture();
    }

    প্রত্যাগম true;
}

স্থির SDL_MouseButtonFlags WIN_GetGlobalMouseState(ভিন্ন *x, ভিন্ন *y)
{
    SDL_MouseButtonFlags result = 0;
    POINT pt = { 0, 0 };
    bool swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;

    GetCursorPos(&pt);
    *x = (ভিন্ন)pt.x;
    *y = (ভিন্ন)pt.y;

    result |= Get_Async_চাবি_State(!swapButtons ? VK_LBUTTON : VK_RBUTTON) & 0x8000 ? SDL_BUTTON_LMASK : 0;
    result |= Get_Async_চাবি_State(!swapButtons ? VK_RBUTTON : VK_LBUTTON) & 0x8000 ? SDL_BUTTON_RMASK : 0;
    result |= Get_Async_চাবি_State(VK_MBUTTON) & 0x8000 ? SDL_BUTTON_MMASK : 0;
    result |= Get_Async_চাবি_State(VK_XBUTTON1) & 0x8000 ? SDL_BUTTON_X1MASK : 0;
    result |= Get_Async_চাবি_State(VK_XBUTTON2) & 0x8000 ? SDL_BUTTON_X2MASK : 0;

    প্রত্যাগম result;
}

স্থির শূন্য WIN_ApplySystemScale(শূন্য *internal, Uint64 timestamp, SDL_Window *window, SDL_MouseID mouseID, ভিন্ন *x, ভিন্ন *y)
{
    যদি (!internal) {
        প্রত্যাগম;
    }
    WIN_MouseData *data = (WIN_MouseData *)internal;

    SDL_VideoDisplay *display = window ? SDL_GetVideoDisplayForWindow(window) : SDL_GetVideoDisplay(SDL_GetPrimaryDisplay());

    Sint64 ix = (Sint64)*x * 65536;
    Sint64 iy = (Sint64)*y * 65536;
    Uint32 dpi = display ? (Uint32)(display->content_scale * USER_DEFAULT_SCREEN_DPI) : USER_DEFAULT_SCREEN_DPI;

    যদি (!data->enhanced) { // early return if flat scale
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
        *x = (ভিন্ন)ix / 65536.0f;
        *y = (ভিন্ন)iy / 65536.0f;
        প্রত্যাগম;
    }

    Uint64 *xs = data->xs;
    Uint64 *ys = data->ys;
    Uint64 absx = SDL_abs(ix);
    Uint64 absy = SDL_abs(iy);
    Uint64 speed = SDL_min(absx, absy) + (SDL_max(absx, absy) << 1); // super cursed approximation used by Windows
    যদি (speed == 0) {
        প্রত্যাগম;
    }

    পূর্ণাঙ্ক i, j, k;
    প্রতি (i = 1; i < 5; i++) {
        j = i;
        যদি (speed < xs[j]) {
            ভঙ্গ;
        }
    }
    i -= 1;
    j -= 1;
    k = data->last_গ্রন্থি;
    data->last_গ্রন্থি = j;

    Uint32 denom = data->dpidenom;
    Sint64 scale = 0;
    Sint64 xdiff = xs[j+1] - xs[j];
    Sint64 ydiff = ys[j+1] - ys[j];
    যদি (xdiff != 0) {
        Sint64 slope = ydiff / xdiff;
        Sint64 inter = slope * xs[i] - ys[i];
        scale += slope - inter / speed;
    }

    যদি (j > k) {
        denom <<= 1;
        xdiff = xs[k+1] - xs[k];
        ydiff = ys[k+1] - ys[k];
        যদি (xdiff != 0) {
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
    *x = (ভিন্ন)ix / 65536.0f;
    *y = (ভিন্ন)iy / 65536.0f;
}

শূন্য WIN_InitMouse(SDL_VideoDevice *_this)
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

শূন্য WIN_QuitMouse(SDL_VideoDevice *_this)
{
    যদি (SDL_blank_cursor) {
        WIN_FreeCursor(SDL_blank_cursor);
        SDL_blank_cursor = রিক্ত;
    }
}

স্থির শূন্য ReadMouseCurve(পূর্ণাঙ্ক v, Uint64 xs[5], Uint64 ys[5])
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
    DWORD xsize = পরিমাণ(xbuff);
    DWORD ysize = পরিমাণ(ybuff);
    HKEY open_handle;
    যদি (Reg_Open_চাবি_Ex_W(HKEY_CURRENT_USER, L"Control Panel\\Mouse", 0, চাবি_READ, &open_handle) == ERROR_SUCCESS) {
        Reg_Query_মান_Ex_W(open_handle, L"SmoothMouseXCurve", রিক্ত, রিক্ত, (BYTE*)xbuff, &xsize);
        Reg_Query_মান_Ex_W(open_handle, L"SmoothMouseYCurve", রিক্ত, রিক্ত, (BYTE*)ybuff, &ysize);
        Reg_Close_চাবি(open_handle);
    }
    xs[0] = 0; // first node must always be origin
    ys[0] = 0; // first node must always be origin
    পূর্ণাঙ্ক i;
    প্রতি (i = 1; i < 5; i++) {
        xs[i] = (7 * (Uint64)xbuff[i * 2]);
        ys[i] = (v * (Uint64)ybuff[i * 2]) << 17;
    }
}

শূন্য WIN_UpdateMouseSystemScale(শূন্য)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    যদি (mouse->ApplySystemScale == WIN_ApplySystemScale) {
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

    পূর্ণাঙ্ক v = 10;
    যদি (SystemParametersInfo(SPI_GETMOUSESPEED, 0, &v, 0)) {
        v = SDL_max(1, SDL_min(v, 20));
        data->dpiscale = SDL_max(SDL_max(v, (v - 2) * 4), (v - 6) * 8);
    }

    পূর্ণাঙ্ক params[3];
    যদি (SystemParametersInfo(SPI_GETMOUSE, 0, &params, 0)) {
        data->enhanced = params[2] ? true : false;
        যদি (params[2]) {
            ReadMouseCurve(v, data->xs, data->ys);
        }
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS

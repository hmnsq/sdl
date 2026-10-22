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

#यदि defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#अन्तर्भाव "SDL_windowsvideo.h"
#अन्तर्भाव "SDL_windowsevents.h"
#अन्तर्भाव "SDL_windowsrawinput.h"

#अन्तर्भाव "../SDL_video_c.h"
#अन्तर्भाव "../../events/SDL_mouse_c.h"
#अन्तर्भाव "../../joystick/usb_ids.h"
#अन्तर्भाव "../../core/windows/SDL_windows.h" // for checking windows version

#define RIFF_FOURCC(c0, c1, c2, c3)                 \
    ((DWORD)(BYTE)(c0) | ((DWORD)(BYTE)(c1) << 8) | \
     ((DWORD)(BYTE)(c2) << 16) | ((DWORD)(BYTE)(c3) << 24))

#define ANI_FLAG_ICON 0x1

#pragma pack(धकेलो, 1)

प्रकारनिर्देश संरचना
{
    BYTE bWidth;
    BYTE bHeight;
    BYTE b_Color_गिनती;
    BYTE bReserved;
    WORD xHotspot;
    WORD yHotspot;
    DWORD dwImageSize;
    DWORD dwImageOffset;
} CURSORICONFILEDIRENTRY;

प्रकारनिर्देश संरचना
{
    WORD idReserved;
    WORD idType;
    WORD id_गिनती;
} CURSORICONFILEDIR;

प्रकारनिर्देश संरचना
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

#pragma pack(निकालो)

प्रकारनिर्देश संरचना CachedCursor
{
    भिन्न scale;
    HCURSOR cursor;
    संरचना CachedCursor *next;
} CachedCursor;

संरचना SDL_CursorData
{
    HCURSOR cursor;

    CachedCursor *cache;
    पूर्णाङ्क hot_x;
    पूर्णाङ्क hot_y;
    पूर्णाङ्क अंक_frames;
    SDL_CursorFrameInfo frames[1];
};

प्रकारनिर्देश संरचना
{
    Uint64 xs[5];
    Uint64 ys[5];
    Sint64 residual[2];
    Uint32 dpiscale;
    Uint32 dpidenom;
    पूर्णाङ्क last_गाँठ;
    bool enhanced;
    bool dpiaware;
} WIN_MouseData;

DWORD SDL_last_warp_time = 0;
HCURSOR SDL_cursor = रिक्त;
स्थिर SDL_Cursor *SDL_blank_cursor = रिक्त;
स्थिर WIN_MouseData WIN_system_scale_data;

स्थिर SDL_Cursor *WIN_CreateCursorAndData(HCURSOR hcursor)
{
    यदि (!hcursor) {
        प्रत्यागम रिक्त;
    }

    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, परिमाण(*cursor));
    यदि (!cursor) {
        प्रत्यागम रिक्त;
    }

    SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, परिमाण(*data));
    यदि (!data) {
        SDL_free(cursor);
        प्रत्यागम रिक्त;
    }

    data->cursor = hcursor;
    cursor->internal = data;
    प्रत्यागम cursor;
}

स्थिर SDL_Cursor *WIN_CreateAnimatedCursorAndData(SDL_CursorFrameInfo *frames, पूर्णाङ्क frame_गिनती, पूर्णाङ्क hot_x, पूर्णाङ्क hot_y)
{
    // Dynamically generate cursors at the appropriate DPI
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, परिमाण(*cursor));
    यदि (!cursor) {
        प्रत्यागम रिक्त;
    }

    SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, परिमाण(*data) + (परिमाण(SDL_CursorFrameInfo) * (frame_गिनती - 1)));
    यदि (!data) {
        SDL_free(cursor);
        प्रत्यागम रिक्त;
    }

    data->hot_x = hot_x;
    data->hot_y = hot_y;
    data->अंक_frames = frame_गिनती;
    प्रति (पूर्णाङ्क i = 0; i < frame_गिनती; ++i) {
        SDL_Surface *surface = frames[i].surface;
        यदि (surface->flags & SDL_SURFACE_PREALLOCATED) {
            surface = SDL_DuplicateSurface(surface);
            यदि (!surface) {
                यावत् (i > 0) {
                    --i;
                    SDL_DestroySurface(data->frames[i].surface);
                }
                SDL_free(data);
                SDL_free(cursor);
                प्रत्यागम रिक्त;
            }
        } अन्यथा {
            ++surface->refcount;
        }
        data->frames[i].surface = surface;
        data->frames[i].duration = frames[i].duration;
    }
    cursor->internal = data;
    प्रत्यागम cursor;
}

स्थिर bool SaveChunkSize(SDL_IOStream* dst, Sint64 offset)
{
    Sint64 here = SDL_TellIO(dst);
    यदि (here < 0) {
        प्रत्यागम false;
    }
    यदि (SDL_SeekIO(dst, offset, SDL_IO_SEEK_SET) < 0) {
        प्रत्यागम false;
    }

    DWORD size = (DWORD)(here - (offset + परिमाण(DWORD)));
    यदि (!SDL_WriteU32LE(dst, size)) {
        प्रत्यागम false;
    }
    प्रत्यागम SDL_SeekIO(dst, here, SDL_IO_SEEK_SET);
}

स्थिर bool FillIconEntry(CURSORICONFILEDIRENTRY *entry, SDL_Surface *surface, पूर्णाङ्क hot_x, पूर्णाङ्क hot_y, DWORD dwImageSize, DWORD dwImageOffset)
{
    यदि (surface->props) {
        hot_x = (पूर्णाङ्क)SDL_Get_संख्या_Property(surface->props, SDL_PROP_SURFACE_HOTSPOT_X_संख्या, hot_x);
        hot_y = (पूर्णाङ्क)SDL_Get_संख्या_Property(surface->props, SDL_PROP_SURFACE_HOTSPOT_Y_संख्या, hot_y);
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
    प्रत्यागम true;
}

#ifdef SAVE_ICON_PNG

स्थिर bool WriteIconSurface(SDL_IOStream *dst, SDL_Surface *surface)
{
    यदि (!SDL_SavePNG_IO(surface, dst, false)) {
        प्रत्यागम false;
    }

    // Image data offsets must be WORD aligned
    Sint64 offset = SDL_TellIO(dst);
    यदि (offset & 1) {
        यदि (!SDL_WriteU8(dst, 0)) {
            प्रत्यागम false;
        }
    }
    प्रत्यागम true;
}

#अन्यथा

/* For info on the expected mask format see:
 * https://devblogs.microsoft.com/oldnewthing/20101018-00/?p=12513
 */
स्थिर शून्य *CreateIconMask(SDL_Surface *surface, माप_प्रकार *mask_size)
{
    Uint8 *dst;
    ध्रुव पूर्णाङ्क w = (surface->w + 7) / 8;
    ध्रुव पूर्णाङ्क pad = (((w) % 4) ? (4 - ((w) % 4)) : 0);
    ध्रुव पूर्णाङ्क pitch = (w + pad);
    ध्रुव माप_प्रकार size = pitch * surface->h;
    स्थिर ध्रुव अचिन्हित वर्ण masks[] = { 0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1 };

    शून्य *mask = SDL_malloc(size);
    यदि (!mask) {
        प्रत्यागम रिक्त;
    }

    dst = (Uint8 *)mask;

    // Make the mask completely transparent.
    SDL_memset(dst, 0xff, size);
    प्रति (पूर्णाङ्क y = surface->h - 1; y >= 0; --y, dst += pitch) {
        प्रति (पूर्णाङ्क x = 0; x < surface->w; ++x) {
            Uint8 r, g, b, a;
            SDL_ReadSurfacePixel(surface, x, y, &r, &g, &b, &a);

            यदि (a != 0) {
                // Reset bit of an opaque pixel.
                dst[x >> 3] &= ~masks[x & 7];
            }
        }
    }
    *mask_size = size;
    प्रत्यागम mask;
}

स्थिर bool WriteIconSurface(SDL_IOStream *dst, SDL_Surface *surface)
{
    SDL_Surface *temp = रिक्त;

    यदि (surface->format != SDL_PIXELFORMAT_ARGB8888) {
        temp = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        यदि (!temp) {
            प्रत्यागम false;
        }
        surface = temp;
    }

    // Cursor data is double height (DIB and mask), stored bottom-up
    bool ok = true;
    माप_प्रकार mask_size = 0;
    शून्य *mask = CreateIconMask(surface, &mask_size);
    यदि (!mask) {
        ok = false;
        गच्छ done;
    }

    BITMAPINFOHEADER bmih;
    SDL_zero(bmih);
    DWORD row_size = surface->w * 4;
    bmih.biSize = परिमाण(BITMAPINFOHEADER);
    bmih.biWidth = surface->w;
    bmih.biHeight = surface->h * 2;
    bmih.biPlanes = 1;
    bmih.bi_Bit_गिनती = 32;
    bmih.biCompression = BI_RGB;
    bmih.biSizeImage = (DWORD)(surface->h * row_size + mask_size);
    ok &= (SDL_WriteIO(dst, &bmih, परिमाण(bmih)) == परिमाण(bmih));

    ध्रुव Uint8 *pix = surface->pixels;
    pix += (surface->h - 1) * surface->pitch;
    प्रति (पूर्णाङ्क i = 0; i < surface->h; ++i) {
        ok &= (SDL_WriteIO(dst, pix, row_size) == row_size);
        pix -= surface->pitch;
    }
    ok &= (SDL_WriteIO(dst, mask, mask_size) == mask_size);

done:
    SDL_free(mask);
    SDL_DestroySurface(temp);
    प्रत्यागम ok;
}

#endif // SAVE_ICON_PNG

स्थिर bool WriteIconFrame(SDL_IOStream *dst, SDL_Surface *surface, पूर्णाङ्क hot_x, पूर्णाङ्क hot_y, भिन्न scale)
{
#ifdef SAVE_MULTIPLE_ICONS
    पूर्णाङ्क गिनती = 0;
    SDL_Surface **surfaces = SDL_GetSurfaceImages(surface, &गिनती);
    यदि (!surfaces) {
        प्रत्यागम false;
    }
#अन्यथा
    surface = SDL_GetSurfaceImage(surface, scale);
    यदि (!surface) {
        प्रत्यागम false;
    }

    पूर्णाङ्क गिनती = 1;
    SDL_Surface **surfaces = &surface;
#endif

    // Raymond Chen has more insight into this format at:
    // https://devblogs.microsoft.com/oldnewthing/20101018-00/?p=12513
    bool ok = true;
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('i', 'c', 'o', 'n'));
    Sint64 icon_size_offset = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    Sint64 base_offset = icon_size_offset + परिमाण(DWORD);

    CURSORICONFILEDIR dir;
    dir.idReserved = 0;
    dir.idType = 2; // Cursor
    dir.id_गिनती = गिनती;
    ok &= (SDL_WriteIO(dst, &dir, परिमाण(dir)) == परिमाण(dir));

    DWORD entries_size = गिनती * परिमाण(CURSORICONFILEDIRENTRY);
    CURSORICONFILEDIRENTRY *entries = (CURSORICONFILEDIRENTRY *)SDL_malloc(entries_size);
    यदि (!entries) {
        ok = false;
        गच्छ done;
    }
    ok &= (SDL_WriteIO(dst, entries, entries_size) == entries_size);

    Sint64 image_offset = SDL_TellIO(dst);
    प्रति (पूर्णाङ्क i = 0; i < गिनती; ++i) {
        ok &= WriteIconSurface(dst, surfaces[i]);

        Sint64 next_offset = SDL_TellIO(dst);
        DWORD dwImageSize = (DWORD)(next_offset - image_offset);
        DWORD dwImageOffset = (DWORD)(image_offset - base_offset);

        ok &= FillIconEntry(&entries[i], surfaces[i], hot_x, hot_y, dwImageSize, dwImageOffset);

        image_offset = next_offset;
    }

    // Now that we have the icon entries filled out, rewrite them
    ok &= (SDL_SeekIO(dst, base_offset + परिमाण(dir), SDL_IO_SEEK_SET) >= 0);
    ok &= (SDL_WriteIO(dst, entries, entries_size) == entries_size);
    ok &= (SDL_SeekIO(dst, image_offset, SDL_IO_SEEK_SET) >= 0);
    SDL_free(entries);

    ok &= SaveChunkSize(dst, icon_size_offset);

done:
#ifdef SAVE_MULTIPLE_ICONS
    SDL_free(surfaces);
#अन्यथा
    SDL_DestroySurface(surface);
#endif
    प्रत्यागम ok;
}

/* Windows doesn't have an API to easily create animated cursors from a sequence of images,
 * so we have to build an animated cursor resource file in memory and load it.
 */
स्थिर HCURSOR WIN_CreateAnimatedCursorInternal(SDL_CursorFrameInfo *frames, पूर्णाङ्क frame_गिनती, पूर्णाङ्क hot_x, पूर्णाङ्क hot_y, भिन्न scale)
{
    HCURSOR hcursor = रिक्त;
    SDL_IOStream *dst = SDL_IOFromDynamicMem();
    यदि (!dst) {
        प्रत्यागम रिक्त;
    }

    पूर्णाङ्क w = (पूर्णाङ्क)SDL_roundf(frames[0].surface->w * scale);
    पूर्णाङ्क h = (पूर्णाङ्क)SDL_roundf(frames[0].surface->h * scale);

    bool ok = true;
    // RIFF header
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('R', 'I', 'F', 'F'));
    Sint64 riff_size_offset = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('A', 'C', 'O', 'N'));

    // anih header chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('a', 'n', 'i', 'h'));
    ok &= SDL_WriteU32LE(dst, परिमाण(ANIHEADER));

    ANIHEADER anih;
    SDL_zero(anih);
    anih.cbSizeof = परिमाण(anih);
    anih.frames = frame_गिनती;
    anih.steps = frame_गिनती;
    anih.jifRate = 1;
    anih.fl = ANI_FLAG_ICON;
    ok &= (SDL_WriteIO(dst, &anih, परिमाण(anih)) == परिमाण(anih));

    // Rate chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('r', 'a', 't', 'e'));
    ok &= SDL_WriteU32LE(dst, परिमाण(DWORD) * frame_गिनती);
    प्रति (पूर्णाङ्क i = 0; i < frame_गिनती; ++i) {
        // Animated Win32 cursors are in jiffy units, and one jiffy is 1/60 of a second.
        ध्रुव द्विगुण WIN32_JIFFY = 1000.0 / 60.0;
        DWORD duration = (frames[i].duration ? SDL_lround(frames[i].duration / WIN32_JIFFY) : 0xFFFFFFFF);
        ok &= SDL_WriteU32LE(dst, duration);
    }

    // Frame list
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('L', 'I', 'S', 'T'));
    Sint64 frame_list_size_offset = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('f', 'r', 'a', 'm'));

    प्रति (पूर्णाङ्क i = 0; i < frame_गिनती; ++i) {
        ok &= WriteIconFrame(dst, frames[i].surface, hot_x, hot_y, scale);
    }
    ok &= SaveChunkSize(dst, frame_list_size_offset);

    // All done!
    ok &= SaveChunkSize(dst, riff_size_offset);
    यदि (!ok) {
        // The error has been set above
        गच्छ done;
    }

    BYTE *mem = (BYTE *)SDL_GetPointerProperty(SDL_GetIOProperties(dst), SDL_PROP_IOSTREAM_DYNAMIC_MEMORY_POINTER, रिक्त);
    DWORD size = (DWORD)SDL_GetIOSize(dst);
    hcursor = (HCURSOR)CreateIconFromResourceEx(mem, size, FALSE, 0x00030000, w, h, 0);
    यदि (!hcursor) {
        SDL_SetError("CreateIconFromResource failed");
    }

done:
    SDL_CloseIO(dst);

    प्रत्यागम hcursor;
}

स्थिर SDL_Cursor *WIN_CreateCursor(SDL_Surface *surface, पूर्णाङ्क hot_x, पूर्णाङ्क hot_y)
{
    SDL_CursorFrameInfo frame = { surface, 0 };
    प्रत्यागम WIN_CreateAnimatedCursorAndData(&frame, 1, hot_x, hot_y);
}

स्थिर SDL_Cursor *WIN_CreateAnimatedCursor(SDL_CursorFrameInfo *frames, पूर्णाङ्क frame_गिनती, पूर्णाङ्क hot_x, पूर्णाङ्क hot_y)
{
    प्रत्यागम WIN_CreateAnimatedCursorAndData(frames, frame_गिनती, hot_x, hot_y);
}

स्थिर SDL_Cursor *WIN_CreateBlankCursor(शून्य)
{
    SDL_Cursor *cursor = रिक्त;
    SDL_Surface *surface = SDL_CreateSurfaceZeroed(32, 32, SDL_PIXELFORMAT_ARGB8888);
    यदि (surface) {
        cursor = WIN_CreateCursor(surface, 0, 0);
        SDL_DestroySurface(surface);
    }
    प्रत्यागम cursor;
}

स्थिर SDL_Cursor *WIN_CreateSystemCursor(SDL_SystemCursor id)
{
    LPCTSTR name;

    विकल्प (id) {
    स्वभाव:
        SDL_assert(!"Unknown system cursor ID");
        प्रत्यागम रिक्त;
    पक्ष SDL_SYSTEM_CURSOR_DEFAULT:
        name = IDC_ARROW;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_TEXT:
    पक्ष SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        name = IDC_IBEAM;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_WAIT:
        name = IDC_WAIT;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_CROSSHAIR:
    पक्ष SDL_SYSTEM_CURSOR_CELL:
        name = IDC_CROSS;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_PROGRESS:
        name = IDC_APPSTARTING;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_NWSE_RESIZE:
    पक्ष SDL_SYSTEM_CURSOR_NW_RESIZE:
    पक्ष SDL_SYSTEM_CURSOR_SE_RESIZE:
        name = IDC_SIZENWSE;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_NESW_RESIZE:
    पक्ष SDL_SYSTEM_CURSOR_NE_RESIZE:
    पक्ष SDL_SYSTEM_CURSOR_SW_RESIZE:
        name = IDC_SIZENESW;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_EW_RESIZE:
    पक्ष SDL_SYSTEM_CURSOR_E_RESIZE:
    पक्ष SDL_SYSTEM_CURSOR_W_RESIZE:
    पक्ष SDL_SYSTEM_CURSOR_COL_RESIZE:
        name = IDC_SIZEWE;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_NS_RESIZE:
    पक्ष SDL_SYSTEM_CURSOR_N_RESIZE:
    पक्ष SDL_SYSTEM_CURSOR_S_RESIZE:
    पक्ष SDL_SYSTEM_CURSOR_ROW_RESIZE:
        name = IDC_SIZENS;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_MOVE:
    पक्ष SDL_SYSTEM_CURSOR_ALL_SCROLL:
        name = IDC_SIZEALL;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_NOT_ALLOWED:
    पक्ष SDL_SYSTEM_CURSOR_NO_DROP:
        name = IDC_NO;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_POINTER:
    पक्ष SDL_SYSTEM_CURSOR_CONTEXT_MENU:
    पक्ष SDL_SYSTEM_CURSOR_ALIAS:
    पक्ष SDL_SYSTEM_CURSOR_COPY:
    पक्ष SDL_SYSTEM_CURSOR_GRAB:
    पक्ष SDL_SYSTEM_CURSOR_GRABBING:
    पक्ष SDL_SYSTEM_CURSOR_ZOOM_IN:
    पक्ष SDL_SYSTEM_CURSOR_ZOOM_OUT:
        name = IDC_HAND;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_HELP:
        name = IDC_HELP;
        भङ्ग;
    }
    प्रत्यागम WIN_CreateCursorAndData(LoadCursor(रिक्त, name));
}

स्थिर SDL_Cursor *WIN_CreateDefaultCursor(शून्य)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    प्रत्यागम WIN_CreateSystemCursor(id);
}

स्थिर शून्य WIN_FreeCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *data = cursor->internal;

    प्रति (पूर्णाङ्क i = 0; i < data->अंक_frames; ++i) {
        SDL_DestroySurface(data->frames[i].surface);
    }
    यावत् (data->cache) {
        CachedCursor *entry = data->cache;
        data->cache = entry->next;
        यदि (entry->cursor) {
            DestroyCursor(entry->cursor);
        }
        SDL_free(entry);
    }
    यदि (data->cursor) {
        DestroyCursor(data->cursor);
    }
    SDL_free(data);
    SDL_free(cursor);
}

स्थिर HCURSOR GetCachedCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *data = cursor->internal;

    भिन्न scale = 1.0f;
    यदि (SDL_GetHintBoolean(SDL_HINT_MOUSE_DPI_SCALE_CURSORS, false)) {
        scale = SDL_GetDisplayContentScale(SDL_GetDisplayForWindow(SDL_GetMouseFocus()));
        यदि (scale == 0.0f) {
            scale = 1.0f;
        }
    }
    प्रति (CachedCursor *entry = data->cache; entry; entry = entry->next) {
        यदि (scale == entry->scale) {
            प्रत्यागम entry->cursor;
        }
    }

    // Need to create a cursor for this content scale
    HCURSOR hcursor = WIN_CreateAnimatedCursorInternal(data->frames, data->अंक_frames, data->hot_x, data->hot_y, scale);
    यदि (!hcursor) {
        प्रत्यागम रिक्त;
    }

    CachedCursor *entry = (CachedCursor *)SDL_calloc(1, परिमाण(*entry));
    यदि (!entry) {
        DestroyCursor(hcursor);
        प्रत्यागम रिक्त;
    }
    entry->cursor = hcursor;
    entry->scale = scale;
    entry->next = data->cache;
    data->cache = entry;

    प्रत्यागम hcursor;
}

स्थिर bool WIN_ShowCursor(SDL_Cursor *cursor)
{
    यदि (!cursor) {
        यदि (GetSystemMetrics(SM_REMOTESESSION)) {
            // Use a blank cursor so we continue to get relative motion over RDP
            cursor = SDL_blank_cursor;
        }
    }
    यदि (cursor) {
        SDL_CursorData *data = cursor->internal;
        यदि (data->अंक_frames > 0) {
            SDL_cursor = GetCachedCursor(cursor);
        } अन्यथा {
            SDL_cursor = data->cursor;
        }
    } अन्यथा {
        SDL_cursor = रिक्त;
    }
    यदि (SDL_GetMouseFocus() != रिक्त) {
        SetCursor(SDL_cursor);
    }
    प्रत्यागम true;
}

शून्य WIN_SetCursorPos(पूर्णाङ्क x, पूर्णाङ्क y)
{
    // We need to jitter the value because otherwise Windows will occasionally inexplicably ignore the SetCursorPos() or SendInput()
    SetCursorPos(x, y);
    SetCursorPos(x + 1, y);
    SetCursorPos(x, y);

    // Flush any mouse motion prior to or associated with this warp
#ifdef _MSC_VER // We explicitly want to use GetTickCount(), not GetTickCount64()
#pragma warning(धकेलो)
#pragma warning(disable : 28159)
#endif
    SDL_last_warp_time = Get_Tick_गिनती();
    यदि (!SDL_last_warp_time) {
        SDL_last_warp_time = 1;
    }
#ifdef _MSC_VER
#pragma warning(निकालो)
#endif
}

स्थिर bool WIN_WarpMouse(SDL_Window *window, भिन्न x, भिन्न y)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    POINT pt;

    // Don't warp the mouse while we're doing a modal interaction
    यदि (data->in_title_click || data->focus_click_pending) {
        प्रत्यागम true;
    }

    pt.x = (पूर्णाङ्क)SDL_roundf(x);
    pt.y = (पूर्णाङ्क)SDL_roundf(y);
    ClientToScreen(hwnd, &pt);
    WIN_SetCursorPos(pt.x, pt.y);

    // Send the exact mouse motion associated with this warp
    SDL_SendMouseMotion(0, window, SDL_GLOBAL_MOUSE_ID, false, x, y);
    प्रत्यागम true;
}

स्थिर bool WIN_WarpMouseGlobal(भिन्न x, भिन्न y)
{
    POINT pt;

    pt.x = (पूर्णाङ्क)SDL_roundf(x);
    pt.y = (पूर्णाङ्क)SDL_roundf(y);
    SetCursorPos(pt.x, pt.y);
    प्रत्यागम true;
}

स्थिर bool WIN_SetRelativeMouseMode(bool enabled)
{
    प्रत्यागम WIN_SetRawMouseEnabled(SDL_GetVideoDevice(), enabled);
}

स्थिर bool WIN_CaptureMouse(SDL_Window *window)
{
    यदि (window) {
        SDL_WindowData *data = window->internal;
        SetCapture(data->hwnd);
    } अन्यथा {
        SDL_Window *focus_window = SDL_GetMouseFocus();

        यदि (focus_window) {
            SDL_WindowData *data = focus_window->internal;
            यदि (!data->mouse_tracked) {
                SDL_SetMouseFocus(रिक्त);
            }
        }
        ReleaseCapture();
    }

    प्रत्यागम true;
}

स्थिर SDL_MouseButtonFlags WIN_GetGlobalMouseState(भिन्न *x, भिन्न *y)
{
    SDL_MouseButtonFlags result = 0;
    POINT pt = { 0, 0 };
    bool swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;

    GetCursorPos(&pt);
    *x = (भिन्न)pt.x;
    *y = (भिन्न)pt.y;

    result |= Get_Async_कुंजी_State(!swapButtons ? VK_LBUTTON : VK_RBUTTON) & 0x8000 ? SDL_BUTTON_LMASK : 0;
    result |= Get_Async_कुंजी_State(!swapButtons ? VK_RBUTTON : VK_LBUTTON) & 0x8000 ? SDL_BUTTON_RMASK : 0;
    result |= Get_Async_कुंजी_State(VK_MBUTTON) & 0x8000 ? SDL_BUTTON_MMASK : 0;
    result |= Get_Async_कुंजी_State(VK_XBUTTON1) & 0x8000 ? SDL_BUTTON_X1MASK : 0;
    result |= Get_Async_कुंजी_State(VK_XBUTTON2) & 0x8000 ? SDL_BUTTON_X2MASK : 0;

    प्रत्यागम result;
}

स्थिर शून्य WIN_ApplySystemScale(शून्य *internal, Uint64 timestamp, SDL_Window *window, SDL_MouseID mouseID, भिन्न *x, भिन्न *y)
{
    यदि (!internal) {
        प्रत्यागम;
    }
    WIN_MouseData *data = (WIN_MouseData *)internal;

    SDL_VideoDisplay *display = window ? SDL_GetVideoDisplayForWindow(window) : SDL_GetVideoDisplay(SDL_GetPrimaryDisplay());

    Sint64 ix = (Sint64)*x * 65536;
    Sint64 iy = (Sint64)*y * 65536;
    Uint32 dpi = display ? (Uint32)(display->content_scale * USER_DEFAULT_SCREEN_DPI) : USER_DEFAULT_SCREEN_DPI;

    यदि (!data->enhanced) { // early return if flat scale
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
        *x = (भिन्न)ix / 65536.0f;
        *y = (भिन्न)iy / 65536.0f;
        प्रत्यागम;
    }

    Uint64 *xs = data->xs;
    Uint64 *ys = data->ys;
    Uint64 absx = SDL_abs(ix);
    Uint64 absy = SDL_abs(iy);
    Uint64 speed = SDL_min(absx, absy) + (SDL_max(absx, absy) << 1); // super cursed approximation used by Windows
    यदि (speed == 0) {
        प्रत्यागम;
    }

    पूर्णाङ्क i, j, k;
    प्रति (i = 1; i < 5; i++) {
        j = i;
        यदि (speed < xs[j]) {
            भङ्ग;
        }
    }
    i -= 1;
    j -= 1;
    k = data->last_गाँठ;
    data->last_गाँठ = j;

    Uint32 denom = data->dpidenom;
    Sint64 scale = 0;
    Sint64 xdiff = xs[j+1] - xs[j];
    Sint64 ydiff = ys[j+1] - ys[j];
    यदि (xdiff != 0) {
        Sint64 slope = ydiff / xdiff;
        Sint64 inter = slope * xs[i] - ys[i];
        scale += slope - inter / speed;
    }

    यदि (j > k) {
        denom <<= 1;
        xdiff = xs[k+1] - xs[k];
        ydiff = ys[k+1] - ys[k];
        यदि (xdiff != 0) {
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
    *x = (भिन्न)ix / 65536.0f;
    *y = (भिन्न)iy / 65536.0f;
}

शून्य WIN_InitMouse(SDL_VideoDevice *_this)
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

शून्य WIN_QuitMouse(SDL_VideoDevice *_this)
{
    यदि (SDL_blank_cursor) {
        WIN_FreeCursor(SDL_blank_cursor);
        SDL_blank_cursor = रिक्त;
    }
}

स्थिर शून्य ReadMouseCurve(पूर्णाङ्क v, Uint64 xs[5], Uint64 ys[5])
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
    DWORD xsize = परिमाण(xbuff);
    DWORD ysize = परिमाण(ybuff);
    HKEY open_handle;
    यदि (Reg_Open_कुंजी_Ex_W(HKEY_CURRENT_USER, L"Control Panel\\Mouse", 0, कुंजी_READ, &open_handle) == ERROR_SUCCESS) {
        Reg_Query_मूल्य_Ex_W(open_handle, L"SmoothMouseXCurve", रिक्त, रिक्त, (BYTE*)xbuff, &xsize);
        Reg_Query_मूल्य_Ex_W(open_handle, L"SmoothMouseYCurve", रिक्त, रिक्त, (BYTE*)ybuff, &ysize);
        Reg_Close_कुंजी(open_handle);
    }
    xs[0] = 0; // first node must always be origin
    ys[0] = 0; // first node must always be origin
    पूर्णाङ्क i;
    प्रति (i = 1; i < 5; i++) {
        xs[i] = (7 * (Uint64)xbuff[i * 2]);
        ys[i] = (v * (Uint64)ybuff[i * 2]) << 17;
    }
}

शून्य WIN_UpdateMouseSystemScale(शून्य)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    यदि (mouse->ApplySystemScale == WIN_ApplySystemScale) {
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

    पूर्णाङ्क v = 10;
    यदि (SystemParametersInfo(SPI_GETMOUSESPEED, 0, &v, 0)) {
        v = SDL_max(1, SDL_min(v, 20));
        data->dpiscale = SDL_max(SDL_max(v, (v - 2) * 4), (v - 6) * 8);
    }

    पूर्णाङ्क params[3];
    यदि (SystemParametersInfo(SPI_GETMOUSE, 0, &params, 0)) {
        data->enhanced = params[2] ? true : false;
        यदि (params[2]) {
            ReadMouseCurve(v, data->xs, data->ys);
        }
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS

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
#അന്തര്ഭാവ "SDL_internal.h"

#എങ്കിൽ defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#അന്തര്ഭാവ "SDL_windowsvideo.h"
#അന്തര്ഭാവ "SDL_windowsevents.h"
#അന്തര്ഭാവ "SDL_windowsrawinput.h"

#അന്തര്ഭാവ "../SDL_video_c.h"
#അന്തര്ഭാവ "../../events/SDL_mouse_c.h"
#അന്തര്ഭാവ "../../joystick/usb_ids.h"
#അന്തര്ഭാവ "../../core/windows/SDL_windows.h" // for checking windows version

#define RIFF_FOURCC(c0, c1, c2, c3)                 \
    ((DWORD)(BYTE)(c0) | ((DWORD)(BYTE)(c1) << 8) | \
     ((DWORD)(BYTE)(c2) << 16) | ((DWORD)(BYTE)(c3) << 24))

#define ANI_FLAG_ICON 0x1

#pragma pack(തള്ളുക, 1)

തരനിർവചനം ഘടന
{
    BYTE bWidth;
    BYTE bHeight;
    BYTE b_Color_എണ്ണം;
    BYTE bReserved;
    WORD xHotspot;
    WORD yHotspot;
    DWORD dwImageSize;
    DWORD dwImageOffset;
} CURSORICONFILEDIRENTRY;

തരനിർവചനം ഘടന
{
    WORD idReserved;
    WORD idType;
    WORD id_എണ്ണം;
} CURSORICONFILEDIR;

തരനിർവചനം ഘടന
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

#pragma pack(എടുക്കുക)

തരനിർവചനം ഘടന CachedCursor
{
    ദശാംശം scale;
    HCURSOR cursor;
    ഘടന CachedCursor *next;
} CachedCursor;

ഘടന SDL_CursorData
{
    HCURSOR cursor;

    CachedCursor *cache;
    പൂർണ്ണസംഖ്യ hot_x;
    പൂർണ്ണസംഖ്യ hot_y;
    പൂർണ്ണസംഖ്യ അക്കം_frames;
    SDL_CursorFrameInfo frames[1];
};

തരനിർവചനം ഘടന
{
    Uint64 xs[5];
    Uint64 ys[5];
    Sint64 residual[2];
    Uint32 dpiscale;
    Uint32 dpidenom;
    പൂർണ്ണസംഖ്യ last_കണ്ണി;
    bool enhanced;
    bool dpiaware;
} WIN_MouseData;

DWORD SDL_last_warp_time = 0;
HCURSOR SDL_cursor = ശൂന്യ;
സ്ഥിതം SDL_Cursor *SDL_blank_cursor = ശൂന്യ;
സ്ഥിതം WIN_MouseData WIN_system_scale_data;

സ്ഥിതം SDL_Cursor *WIN_CreateCursorAndData(HCURSOR hcursor)
{
    എങ്കിൽ (!hcursor) {
        തിരികെ ശൂന്യ;
    }

    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, വലുപ്പം(*cursor));
    എങ്കിൽ (!cursor) {
        തിരികെ ശൂന്യ;
    }

    SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, വലുപ്പം(*data));
    എങ്കിൽ (!data) {
        SDL_free(cursor);
        തിരികെ ശൂന്യ;
    }

    data->cursor = hcursor;
    cursor->internal = data;
    തിരികെ cursor;
}

സ്ഥിതം SDL_Cursor *WIN_CreateAnimatedCursorAndData(SDL_CursorFrameInfo *frames, പൂർണ്ണസംഖ്യ frame_എണ്ണം, പൂർണ്ണസംഖ്യ hot_x, പൂർണ്ണസംഖ്യ hot_y)
{
    // Dynamically generate cursors at the appropriate DPI
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, വലുപ്പം(*cursor));
    എങ്കിൽ (!cursor) {
        തിരികെ ശൂന്യ;
    }

    SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, വലുപ്പം(*data) + (വലുപ്പം(SDL_CursorFrameInfo) * (frame_എണ്ണം - 1)));
    എങ്കിൽ (!data) {
        SDL_free(cursor);
        തിരികെ ശൂന്യ;
    }

    data->hot_x = hot_x;
    data->hot_y = hot_y;
    data->അക്കം_frames = frame_എണ്ണം;
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < frame_എണ്ണം; ++i) {
        SDL_Surface *surface = frames[i].surface;
        എങ്കിൽ (surface->flags & SDL_SURFACE_PREALLOCATED) {
            surface = SDL_DuplicateSurface(surface);
            എങ്കിൽ (!surface) {
                ആകുമ്പോൾ (i > 0) {
                    --i;
                    SDL_DestroySurface(data->frames[i].surface);
                }
                SDL_free(data);
                SDL_free(cursor);
                തിരികെ ശൂന്യ;
            }
        } അല്ലെങ്കിൽ {
            ++surface->refcount;
        }
        data->frames[i].surface = surface;
        data->frames[i].duration = frames[i].duration;
    }
    cursor->internal = data;
    തിരികെ cursor;
}

സ്ഥിതം bool SaveChunkSize(SDL_IOStream* dst, Sint64 offset)
{
    Sint64 here = SDL_TellIO(dst);
    എങ്കിൽ (here < 0) {
        തിരികെ false;
    }
    എങ്കിൽ (SDL_SeekIO(dst, offset, SDL_IO_SEEK_SET) < 0) {
        തിരികെ false;
    }

    DWORD size = (DWORD)(here - (offset + വലുപ്പം(DWORD)));
    എങ്കിൽ (!SDL_WriteU32LE(dst, size)) {
        തിരികെ false;
    }
    തിരികെ SDL_SeekIO(dst, here, SDL_IO_SEEK_SET);
}

സ്ഥിതം bool FillIconEntry(CURSORICONFILEDIRENTRY *entry, SDL_Surface *surface, പൂർണ്ണസംഖ്യ hot_x, പൂർണ്ണസംഖ്യ hot_y, DWORD dwImageSize, DWORD dwImageOffset)
{
    എങ്കിൽ (surface->props) {
        hot_x = (പൂർണ്ണസംഖ്യ)SDL_Get_സംഖ്യ_Property(surface->props, SDL_PROP_SURFACE_HOTSPOT_X_സംഖ്യ, hot_x);
        hot_y = (പൂർണ്ണസംഖ്യ)SDL_Get_സംഖ്യ_Property(surface->props, SDL_PROP_SURFACE_HOTSPOT_Y_സംഖ്യ, hot_y);
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
    തിരികെ true;
}

#ifdef SAVE_ICON_PNG

സ്ഥിതം bool WriteIconSurface(SDL_IOStream *dst, SDL_Surface *surface)
{
    എങ്കിൽ (!SDL_SavePNG_IO(surface, dst, false)) {
        തിരികെ false;
    }

    // Image data offsets must be WORD aligned
    Sint64 offset = SDL_TellIO(dst);
    എങ്കിൽ (offset & 1) {
        എങ്കിൽ (!SDL_WriteU8(dst, 0)) {
            തിരികെ false;
        }
    }
    തിരികെ true;
}

#അല്ലെങ്കിൽ

/* For info on the expected mask format see:
 * https://devblogs.microsoft.com/oldnewthing/20101018-00/?p=12513
 */
സ്ഥിതം ശൂന്യം *CreateIconMask(SDL_Surface *surface, size_t *mask_size)
{
    Uint8 *dst;
    സ്ഥിരം പൂർണ്ണസംഖ്യ w = (surface->w + 7) / 8;
    സ്ഥിരം പൂർണ്ണസംഖ്യ pad = (((w) % 4) ? (4 - ((w) % 4)) : 0);
    സ്ഥിരം പൂർണ്ണസംഖ്യ pitch = (w + pad);
    സ്ഥിരം size_t size = pitch * surface->h;
    സ്ഥിതം സ്ഥിരം unsigned അക്ഷരം masks[] = { 0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1 };

    ശൂന്യം *mask = SDL_malloc(size);
    എങ്കിൽ (!mask) {
        തിരികെ ശൂന്യ;
    }

    dst = (Uint8 *)mask;

    // Make the mask completely transparent.
    SDL_memset(dst, 0xff, size);
    വേണ്ടി (പൂർണ്ണസംഖ്യ y = surface->h - 1; y >= 0; --y, dst += pitch) {
        വേണ്ടി (പൂർണ്ണസംഖ്യ x = 0; x < surface->w; ++x) {
            Uint8 r, g, b, a;
            SDL_ReadSurfacePixel(surface, x, y, &r, &g, &b, &a);

            എങ്കിൽ (a != 0) {
                // Reset bit of an opaque pixel.
                dst[x >> 3] &= ~masks[x & 7];
            }
        }
    }
    *mask_size = size;
    തിരികെ mask;
}

സ്ഥിതം bool WriteIconSurface(SDL_IOStream *dst, SDL_Surface *surface)
{
    SDL_Surface *temp = ശൂന്യ;

    എങ്കിൽ (surface->format != SDL_PIXELFORMAT_ARGB8888) {
        temp = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        എങ്കിൽ (!temp) {
            തിരികെ false;
        }
        surface = temp;
    }

    // Cursor data is double height (DIB and mask), stored bottom-up
    bool ok = true;
    size_t mask_size = 0;
    ശൂന്യം *mask = CreateIconMask(surface, &mask_size);
    എങ്കിൽ (!mask) {
        ok = false;
        പോകുക done;
    }

    BITMAPINFOHEADER bmih;
    SDL_zero(bmih);
    DWORD row_size = surface->w * 4;
    bmih.biSize = വലുപ്പം(BITMAPINFOHEADER);
    bmih.biWidth = surface->w;
    bmih.biHeight = surface->h * 2;
    bmih.biPlanes = 1;
    bmih.bi_Bit_എണ്ണം = 32;
    bmih.biCompression = BI_RGB;
    bmih.biSizeImage = (DWORD)(surface->h * row_size + mask_size);
    ok &= (SDL_WriteIO(dst, &bmih, വലുപ്പം(bmih)) == വലുപ്പം(bmih));

    സ്ഥിരം Uint8 *pix = surface->pixels;
    pix += (surface->h - 1) * surface->pitch;
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < surface->h; ++i) {
        ok &= (SDL_WriteIO(dst, pix, row_size) == row_size);
        pix -= surface->pitch;
    }
    ok &= (SDL_WriteIO(dst, mask, mask_size) == mask_size);

done:
    SDL_free(mask);
    SDL_DestroySurface(temp);
    തിരികെ ok;
}

#endif // SAVE_ICON_PNG

സ്ഥിതം bool WriteIconFrame(SDL_IOStream *dst, SDL_Surface *surface, പൂർണ്ണസംഖ്യ hot_x, പൂർണ്ണസംഖ്യ hot_y, ദശാംശം scale)
{
#ifdef SAVE_MULTIPLE_ICONS
    പൂർണ്ണസംഖ്യ എണ്ണം = 0;
    SDL_Surface **surfaces = SDL_GetSurfaceImages(surface, &എണ്ണം);
    എങ്കിൽ (!surfaces) {
        തിരികെ false;
    }
#അല്ലെങ്കിൽ
    surface = SDL_GetSurfaceImage(surface, scale);
    എങ്കിൽ (!surface) {
        തിരികെ false;
    }

    പൂർണ്ണസംഖ്യ എണ്ണം = 1;
    SDL_Surface **surfaces = &surface;
#endif

    // Raymond Chen has more insight into this format at:
    // https://devblogs.microsoft.com/oldnewthing/20101018-00/?p=12513
    bool ok = true;
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('i', 'c', 'o', 'n'));
    Sint64 icon_size_offset = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    Sint64 base_offset = icon_size_offset + വലുപ്പം(DWORD);

    CURSORICONFILEDIR dir;
    dir.idReserved = 0;
    dir.idType = 2; // Cursor
    dir.id_എണ്ണം = എണ്ണം;
    ok &= (SDL_WriteIO(dst, &dir, വലുപ്പം(dir)) == വലുപ്പം(dir));

    DWORD entries_size = എണ്ണം * വലുപ്പം(CURSORICONFILEDIRENTRY);
    CURSORICONFILEDIRENTRY *entries = (CURSORICONFILEDIRENTRY *)SDL_malloc(entries_size);
    എങ്കിൽ (!entries) {
        ok = false;
        പോകുക done;
    }
    ok &= (SDL_WriteIO(dst, entries, entries_size) == entries_size);

    Sint64 image_offset = SDL_TellIO(dst);
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < എണ്ണം; ++i) {
        ok &= WriteIconSurface(dst, surfaces[i]);

        Sint64 next_offset = SDL_TellIO(dst);
        DWORD dwImageSize = (DWORD)(next_offset - image_offset);
        DWORD dwImageOffset = (DWORD)(image_offset - base_offset);

        ok &= FillIconEntry(&entries[i], surfaces[i], hot_x, hot_y, dwImageSize, dwImageOffset);

        image_offset = next_offset;
    }

    // Now that we have the icon entries filled out, rewrite them
    ok &= (SDL_SeekIO(dst, base_offset + വലുപ്പം(dir), SDL_IO_SEEK_SET) >= 0);
    ok &= (SDL_WriteIO(dst, entries, entries_size) == entries_size);
    ok &= (SDL_SeekIO(dst, image_offset, SDL_IO_SEEK_SET) >= 0);
    SDL_free(entries);

    ok &= SaveChunkSize(dst, icon_size_offset);

done:
#ifdef SAVE_MULTIPLE_ICONS
    SDL_free(surfaces);
#അല്ലെങ്കിൽ
    SDL_DestroySurface(surface);
#endif
    തിരികെ ok;
}

/* Windows doesn't have an API to easily create animated cursors from a sequence of images,
 * so we have to build an animated cursor resource file in memory and load it.
 */
സ്ഥിതം HCURSOR WIN_CreateAnimatedCursorInternal(SDL_CursorFrameInfo *frames, പൂർണ്ണസംഖ്യ frame_എണ്ണം, പൂർണ്ണസംഖ്യ hot_x, പൂർണ്ണസംഖ്യ hot_y, ദശാംശം scale)
{
    HCURSOR hcursor = ശൂന്യ;
    SDL_IOStream *dst = SDL_IOFromDynamicMem();
    എങ്കിൽ (!dst) {
        തിരികെ ശൂന്യ;
    }

    പൂർണ്ണസംഖ്യ w = (പൂർണ്ണസംഖ്യ)SDL_roundf(frames[0].surface->w * scale);
    പൂർണ്ണസംഖ്യ h = (പൂർണ്ണസംഖ്യ)SDL_roundf(frames[0].surface->h * scale);

    bool ok = true;
    // RIFF header
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('R', 'I', 'F', 'F'));
    Sint64 riff_size_offset = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('A', 'C', 'O', 'N'));

    // anih header chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('a', 'n', 'i', 'h'));
    ok &= SDL_WriteU32LE(dst, വലുപ്പം(ANIHEADER));

    ANIHEADER anih;
    SDL_zero(anih);
    anih.cbSizeof = വലുപ്പം(anih);
    anih.frames = frame_എണ്ണം;
    anih.steps = frame_എണ്ണം;
    anih.jifRate = 1;
    anih.fl = ANI_FLAG_ICON;
    ok &= (SDL_WriteIO(dst, &anih, വലുപ്പം(anih)) == വലുപ്പം(anih));

    // Rate chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('r', 'a', 't', 'e'));
    ok &= SDL_WriteU32LE(dst, വലുപ്പം(DWORD) * frame_എണ്ണം);
    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < frame_എണ്ണം; ++i) {
        // Animated Win32 cursors are in jiffy units, and one jiffy is 1/60 of a second.
        സ്ഥിരം ഇരട്ട WIN32_JIFFY = 1000.0 / 60.0;
        DWORD duration = (frames[i].duration ? SDL_lround(frames[i].duration / WIN32_JIFFY) : 0xFFFFFFFF);
        ok &= SDL_WriteU32LE(dst, duration);
    }

    // Frame list
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('L', 'I', 'S', 'T'));
    Sint64 frame_list_size_offset = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('f', 'r', 'a', 'm'));

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < frame_എണ്ണം; ++i) {
        ok &= WriteIconFrame(dst, frames[i].surface, hot_x, hot_y, scale);
    }
    ok &= SaveChunkSize(dst, frame_list_size_offset);

    // All done!
    ok &= SaveChunkSize(dst, riff_size_offset);
    എങ്കിൽ (!ok) {
        // The error has been set above
        പോകുക done;
    }

    BYTE *mem = (BYTE *)SDL_GetPointerProperty(SDL_GetIOProperties(dst), SDL_PROP_IOSTREAM_DYNAMIC_MEMORY_POINTER, ശൂന്യ);
    DWORD size = (DWORD)SDL_GetIOSize(dst);
    hcursor = (HCURSOR)CreateIconFromResourceEx(mem, size, FALSE, 0x00030000, w, h, 0);
    എങ്കിൽ (!hcursor) {
        SDL_SetError("CreateIconFromResource failed");
    }

done:
    SDL_CloseIO(dst);

    തിരികെ hcursor;
}

സ്ഥിതം SDL_Cursor *WIN_CreateCursor(SDL_Surface *surface, പൂർണ്ണസംഖ്യ hot_x, പൂർണ്ണസംഖ്യ hot_y)
{
    SDL_CursorFrameInfo frame = { surface, 0 };
    തിരികെ WIN_CreateAnimatedCursorAndData(&frame, 1, hot_x, hot_y);
}

സ്ഥിതം SDL_Cursor *WIN_CreateAnimatedCursor(SDL_CursorFrameInfo *frames, പൂർണ്ണസംഖ്യ frame_എണ്ണം, പൂർണ്ണസംഖ്യ hot_x, പൂർണ്ണസംഖ്യ hot_y)
{
    തിരികെ WIN_CreateAnimatedCursorAndData(frames, frame_എണ്ണം, hot_x, hot_y);
}

സ്ഥിതം SDL_Cursor *WIN_CreateBlankCursor(ശൂന്യം)
{
    SDL_Cursor *cursor = ശൂന്യ;
    SDL_Surface *surface = SDL_CreateSurfaceZeroed(32, 32, SDL_PIXELFORMAT_ARGB8888);
    എങ്കിൽ (surface) {
        cursor = WIN_CreateCursor(surface, 0, 0);
        SDL_DestroySurface(surface);
    }
    തിരികെ cursor;
}

സ്ഥിതം SDL_Cursor *WIN_CreateSystemCursor(SDL_SystemCursor id)
{
    LPCTSTR name;

    തിരഞ്ഞെടുപ്പ് (id) {
    സ്ഥിരസ്ഥിതി:
        SDL_assert(!"Unknown system cursor ID");
        തിരികെ ശൂന്യ;
    അവസ്ഥ SDL_SYSTEM_CURSOR_DEFAULT:
        name = IDC_ARROW;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_TEXT:
    അവസ്ഥ SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        name = IDC_IBEAM;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_WAIT:
        name = IDC_WAIT;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_CROSSHAIR:
    അവസ്ഥ SDL_SYSTEM_CURSOR_CELL:
        name = IDC_CROSS;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_PROGRESS:
        name = IDC_APPSTARTING;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_NWSE_RESIZE:
    അവസ്ഥ SDL_SYSTEM_CURSOR_NW_RESIZE:
    അവസ്ഥ SDL_SYSTEM_CURSOR_SE_RESIZE:
        name = IDC_SIZENWSE;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_NESW_RESIZE:
    അവസ്ഥ SDL_SYSTEM_CURSOR_NE_RESIZE:
    അവസ്ഥ SDL_SYSTEM_CURSOR_SW_RESIZE:
        name = IDC_SIZENESW;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_EW_RESIZE:
    അവസ്ഥ SDL_SYSTEM_CURSOR_E_RESIZE:
    അവസ്ഥ SDL_SYSTEM_CURSOR_W_RESIZE:
    അവസ്ഥ SDL_SYSTEM_CURSOR_COL_RESIZE:
        name = IDC_SIZEWE;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_NS_RESIZE:
    അവസ്ഥ SDL_SYSTEM_CURSOR_N_RESIZE:
    അവസ്ഥ SDL_SYSTEM_CURSOR_S_RESIZE:
    അവസ്ഥ SDL_SYSTEM_CURSOR_ROW_RESIZE:
        name = IDC_SIZENS;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_MOVE:
    അവസ്ഥ SDL_SYSTEM_CURSOR_ALL_SCROLL:
        name = IDC_SIZEALL;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_NOT_ALLOWED:
    അവസ്ഥ SDL_SYSTEM_CURSOR_NO_DROP:
        name = IDC_NO;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_POINTER:
    അവസ്ഥ SDL_SYSTEM_CURSOR_CONTEXT_MENU:
    അവസ്ഥ SDL_SYSTEM_CURSOR_ALIAS:
    അവസ്ഥ SDL_SYSTEM_CURSOR_COPY:
    അവസ്ഥ SDL_SYSTEM_CURSOR_GRAB:
    അവസ്ഥ SDL_SYSTEM_CURSOR_GRABBING:
    അവസ്ഥ SDL_SYSTEM_CURSOR_ZOOM_IN:
    അവസ്ഥ SDL_SYSTEM_CURSOR_ZOOM_OUT:
        name = IDC_HAND;
        നിർത്തുക;
    അവസ്ഥ SDL_SYSTEM_CURSOR_HELP:
        name = IDC_HELP;
        നിർത്തുക;
    }
    തിരികെ WIN_CreateCursorAndData(LoadCursor(ശൂന്യ, name));
}

സ്ഥിതം SDL_Cursor *WIN_CreateDefaultCursor(ശൂന്യം)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    തിരികെ WIN_CreateSystemCursor(id);
}

സ്ഥിതം ശൂന്യം WIN_FreeCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *data = cursor->internal;

    വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < data->അക്കം_frames; ++i) {
        SDL_DestroySurface(data->frames[i].surface);
    }
    ആകുമ്പോൾ (data->cache) {
        CachedCursor *entry = data->cache;
        data->cache = entry->next;
        എങ്കിൽ (entry->cursor) {
            DestroyCursor(entry->cursor);
        }
        SDL_free(entry);
    }
    എങ്കിൽ (data->cursor) {
        DestroyCursor(data->cursor);
    }
    SDL_free(data);
    SDL_free(cursor);
}

സ്ഥിതം HCURSOR GetCachedCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *data = cursor->internal;

    ദശാംശം scale = 1.0f;
    എങ്കിൽ (SDL_GetHintBoolean(SDL_HINT_MOUSE_DPI_SCALE_CURSORS, false)) {
        scale = SDL_GetDisplayContentScale(SDL_GetDisplayForWindow(SDL_GetMouseFocus()));
        എങ്കിൽ (scale == 0.0f) {
            scale = 1.0f;
        }
    }
    വേണ്ടി (CachedCursor *entry = data->cache; entry; entry = entry->next) {
        എങ്കിൽ (scale == entry->scale) {
            തിരികെ entry->cursor;
        }
    }

    // Need to create a cursor for this content scale
    HCURSOR hcursor = WIN_CreateAnimatedCursorInternal(data->frames, data->അക്കം_frames, data->hot_x, data->hot_y, scale);
    എങ്കിൽ (!hcursor) {
        തിരികെ ശൂന്യ;
    }

    CachedCursor *entry = (CachedCursor *)SDL_calloc(1, വലുപ്പം(*entry));
    എങ്കിൽ (!entry) {
        DestroyCursor(hcursor);
        തിരികെ ശൂന്യ;
    }
    entry->cursor = hcursor;
    entry->scale = scale;
    entry->next = data->cache;
    data->cache = entry;

    തിരികെ hcursor;
}

സ്ഥിതം bool WIN_ShowCursor(SDL_Cursor *cursor)
{
    എങ്കിൽ (!cursor) {
        എങ്കിൽ (GetSystemMetrics(SM_REMOTESESSION)) {
            // Use a blank cursor so we continue to get relative motion over RDP
            cursor = SDL_blank_cursor;
        }
    }
    എങ്കിൽ (cursor) {
        SDL_CursorData *data = cursor->internal;
        എങ്കിൽ (data->അക്കം_frames > 0) {
            SDL_cursor = GetCachedCursor(cursor);
        } അല്ലെങ്കിൽ {
            SDL_cursor = data->cursor;
        }
    } അല്ലെങ്കിൽ {
        SDL_cursor = ശൂന്യ;
    }
    എങ്കിൽ (SDL_GetMouseFocus() != ശൂന്യ) {
        SetCursor(SDL_cursor);
    }
    തിരികെ true;
}

ശൂന്യം WIN_SetCursorPos(പൂർണ്ണസംഖ്യ x, പൂർണ്ണസംഖ്യ y)
{
    // We need to jitter the value because otherwise Windows will occasionally inexplicably ignore the SetCursorPos() or SendInput()
    SetCursorPos(x, y);
    SetCursorPos(x + 1, y);
    SetCursorPos(x, y);

    // Flush any mouse motion prior to or associated with this warp
#ifdef _MSC_VER // We explicitly want to use GetTickCount(), not GetTickCount64()
#pragma warning(തള്ളുക)
#pragma warning(disable : 28159)
#endif
    SDL_last_warp_time = Get_Tick_എണ്ണം();
    എങ്കിൽ (!SDL_last_warp_time) {
        SDL_last_warp_time = 1;
    }
#ifdef _MSC_VER
#pragma warning(എടുക്കുക)
#endif
}

സ്ഥിതം bool WIN_WarpMouse(SDL_Window *window, ദശാംശം x, ദശാംശം y)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    POINT pt;

    // Don't warp the mouse while we're doing a modal interaction
    എങ്കിൽ (data->in_title_click || data->focus_click_pending) {
        തിരികെ true;
    }

    pt.x = (പൂർണ്ണസംഖ്യ)SDL_roundf(x);
    pt.y = (പൂർണ്ണസംഖ്യ)SDL_roundf(y);
    ClientToScreen(hwnd, &pt);
    WIN_SetCursorPos(pt.x, pt.y);

    // Send the exact mouse motion associated with this warp
    SDL_SendMouseMotion(0, window, SDL_GLOBAL_MOUSE_ID, false, x, y);
    തിരികെ true;
}

സ്ഥിതം bool WIN_WarpMouseGlobal(ദശാംശം x, ദശാംശം y)
{
    POINT pt;

    pt.x = (പൂർണ്ണസംഖ്യ)SDL_roundf(x);
    pt.y = (പൂർണ്ണസംഖ്യ)SDL_roundf(y);
    SetCursorPos(pt.x, pt.y);
    തിരികെ true;
}

സ്ഥിതം bool WIN_SetRelativeMouseMode(bool enabled)
{
    തിരികെ WIN_SetRawMouseEnabled(SDL_GetVideoDevice(), enabled);
}

സ്ഥിതം bool WIN_CaptureMouse(SDL_Window *window)
{
    എങ്കിൽ (window) {
        SDL_WindowData *data = window->internal;
        SetCapture(data->hwnd);
    } അല്ലെങ്കിൽ {
        SDL_Window *focus_window = SDL_GetMouseFocus();

        എങ്കിൽ (focus_window) {
            SDL_WindowData *data = focus_window->internal;
            എങ്കിൽ (!data->mouse_tracked) {
                SDL_SetMouseFocus(ശൂന്യ);
            }
        }
        ReleaseCapture();
    }

    തിരികെ true;
}

സ്ഥിതം SDL_MouseButtonFlags WIN_GetGlobalMouseState(ദശാംശം *x, ദശാംശം *y)
{
    SDL_MouseButtonFlags result = 0;
    POINT pt = { 0, 0 };
    bool swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;

    GetCursorPos(&pt);
    *x = (ദശാംശം)pt.x;
    *y = (ദശാംശം)pt.y;

    result |= Get_Async_താക്കോൽ_State(!swapButtons ? VK_LBUTTON : VK_RBUTTON) & 0x8000 ? SDL_BUTTON_LMASK : 0;
    result |= Get_Async_താക്കോൽ_State(!swapButtons ? VK_RBUTTON : VK_LBUTTON) & 0x8000 ? SDL_BUTTON_RMASK : 0;
    result |= Get_Async_താക്കോൽ_State(VK_MBUTTON) & 0x8000 ? SDL_BUTTON_MMASK : 0;
    result |= Get_Async_താക്കോൽ_State(VK_XBUTTON1) & 0x8000 ? SDL_BUTTON_X1MASK : 0;
    result |= Get_Async_താക്കോൽ_State(VK_XBUTTON2) & 0x8000 ? SDL_BUTTON_X2MASK : 0;

    തിരികെ result;
}

സ്ഥിതം ശൂന്യം WIN_ApplySystemScale(ശൂന്യം *internal, Uint64 timestamp, SDL_Window *window, SDL_MouseID mouseID, ദശാംശം *x, ദശാംശം *y)
{
    എങ്കിൽ (!internal) {
        തിരികെ;
    }
    WIN_MouseData *data = (WIN_MouseData *)internal;

    SDL_VideoDisplay *display = window ? SDL_GetVideoDisplayForWindow(window) : SDL_GetVideoDisplay(SDL_GetPrimaryDisplay());

    Sint64 ix = (Sint64)*x * 65536;
    Sint64 iy = (Sint64)*y * 65536;
    Uint32 dpi = display ? (Uint32)(display->content_scale * USER_DEFAULT_SCREEN_DPI) : USER_DEFAULT_SCREEN_DPI;

    എങ്കിൽ (!data->enhanced) { // early return if flat scale
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
        *x = (ദശാംശം)ix / 65536.0f;
        *y = (ദശാംശം)iy / 65536.0f;
        തിരികെ;
    }

    Uint64 *xs = data->xs;
    Uint64 *ys = data->ys;
    Uint64 absx = SDL_abs(ix);
    Uint64 absy = SDL_abs(iy);
    Uint64 speed = SDL_min(absx, absy) + (SDL_max(absx, absy) << 1); // super cursed approximation used by Windows
    എങ്കിൽ (speed == 0) {
        തിരികെ;
    }

    പൂർണ്ണസംഖ്യ i, j, k;
    വേണ്ടി (i = 1; i < 5; i++) {
        j = i;
        എങ്കിൽ (speed < xs[j]) {
            നിർത്തുക;
        }
    }
    i -= 1;
    j -= 1;
    k = data->last_കണ്ണി;
    data->last_കണ്ണി = j;

    Uint32 denom = data->dpidenom;
    Sint64 scale = 0;
    Sint64 xdiff = xs[j+1] - xs[j];
    Sint64 ydiff = ys[j+1] - ys[j];
    എങ്കിൽ (xdiff != 0) {
        Sint64 slope = ydiff / xdiff;
        Sint64 inter = slope * xs[i] - ys[i];
        scale += slope - inter / speed;
    }

    എങ്കിൽ (j > k) {
        denom <<= 1;
        xdiff = xs[k+1] - xs[k];
        ydiff = ys[k+1] - ys[k];
        എങ്കിൽ (xdiff != 0) {
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
    *x = (ദശാംശം)ix / 65536.0f;
    *y = (ദശാംശം)iy / 65536.0f;
}

ശൂന്യം WIN_InitMouse(SDL_VideoDevice *_this)
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

ശൂന്യം WIN_QuitMouse(SDL_VideoDevice *_this)
{
    എങ്കിൽ (SDL_blank_cursor) {
        WIN_FreeCursor(SDL_blank_cursor);
        SDL_blank_cursor = ശൂന്യ;
    }
}

സ്ഥിതം ശൂന്യം ReadMouseCurve(പൂർണ്ണസംഖ്യ v, Uint64 xs[5], Uint64 ys[5])
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
    DWORD xsize = വലുപ്പം(xbuff);
    DWORD ysize = വലുപ്പം(ybuff);
    HKEY open_handle;
    എങ്കിൽ (Reg_Open_താക്കോൽ_Ex_W(HKEY_CURRENT_USER, L"Control Panel\\Mouse", 0, താക്കോൽ_READ, &open_handle) == ERROR_SUCCESS) {
        Reg_Query_മൂല്യം_Ex_W(open_handle, L"SmoothMouseXCurve", ശൂന്യ, ശൂന്യ, (BYTE*)xbuff, &xsize);
        Reg_Query_മൂല്യം_Ex_W(open_handle, L"SmoothMouseYCurve", ശൂന്യ, ശൂന്യ, (BYTE*)ybuff, &ysize);
        Reg_Close_താക്കോൽ(open_handle);
    }
    xs[0] = 0; // first node must always be origin
    ys[0] = 0; // first node must always be origin
    പൂർണ്ണസംഖ്യ i;
    വേണ്ടി (i = 1; i < 5; i++) {
        xs[i] = (7 * (Uint64)xbuff[i * 2]);
        ys[i] = (v * (Uint64)ybuff[i * 2]) << 17;
    }
}

ശൂന്യം WIN_UpdateMouseSystemScale(ശൂന്യം)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    എങ്കിൽ (mouse->ApplySystemScale == WIN_ApplySystemScale) {
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

    പൂർണ്ണസംഖ്യ v = 10;
    എങ്കിൽ (SystemParametersInfo(SPI_GETMOUSESPEED, 0, &v, 0)) {
        v = SDL_max(1, SDL_min(v, 20));
        data->dpiscale = SDL_max(SDL_max(v, (v - 2) * 4), (v - 6) * 8);
    }

    പൂർണ്ണസംഖ്യ params[3];
    എങ്കിൽ (SystemParametersInfo(SPI_GETMOUSE, 0, &params, 0)) {
        data->enhanced = params[2] ? true : false;
        എങ്കിൽ (params[2]) {
            ReadMouseCurve(v, data->xs, data->ys);
        }
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS

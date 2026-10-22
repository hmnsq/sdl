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

প্রকারলেখ কাঠামো
{
    BYTE bWidth;
    BYTE bHeight;
    BYTE b_Color_গুনতি;
    BYTE bReserved;
    WORD xHotspot;
    WORD yHotspot;
    DWORD dw_Image_আকার;
    DWORD dwImageOffset;
} CURSORICONFILEDIRENTRY;

প্রকারলেখ কাঠামো
{
    WORD idReserved;
    WORD idType;
    WORD id_গুনতি;
} CURSORICONFILEDIR;

প্রকারলেখ কাঠামো
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

প্রকারলেখ কাঠামো CachedCursor
{
    দশমিক scale;
    HCURSOR cursor;
    কাঠামো CachedCursor *পরবর্তী;
} CachedCursor;

কাঠামো SDL_Cursor_তথ্য
{
    HCURSOR cursor;

    CachedCursor *cache;
    পূর্ণসংখ্যা hot_x;
    পূর্ণসংখ্যা hot_y;
    পূর্ণসংখ্যা অঙ্ক_frames;
    SDL_CursorFrameInfo frames[1];
};

প্রকারলেখ কাঠামো
{
    Uint64 xs[5];
    Uint64 ys[5];
    Sint64 residual[2];
    Uint32 dpiscale;
    Uint32 dpidenom;
    পূর্ণসংখ্যা last_গ্রন্থি;
    bool enhanced;
    bool dpiaware;
} WIN_Mouse_তথ্য;

DWORD SDL_last_warp_time = 0;
HCURSOR SDL_cursor = ফাঁকা;
স্থির SDL_Cursor *SDL_blank_cursor = ফাঁকা;
স্থির WIN_Mouse_তথ্য WIN_system_scale_তথ্য;

স্থির SDL_Cursor *WIN_Create_Cursor_And_তথ্য(HCURSOR hcursor)
{
    যদি (!hcursor) {
        ফেরত ফাঁকা;
    }

    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, আকার(*cursor));
    যদি (!cursor) {
        ফেরত ফাঁকা;
    }

    SDL_Cursor_তথ্য *তথ্য = (SDL_Cursor_তথ্য *)SDL_calloc(1, আকার(*তথ্য));
    যদি (!তথ্য) {
        SDL_free(cursor);
        ফেরত ফাঁকা;
    }

    তথ্য->cursor = hcursor;
    cursor->internal = তথ্য;
    ফেরত cursor;
}

স্থির SDL_Cursor *WIN_Create_Animated_Cursor_And_তথ্য(SDL_CursorFrameInfo *frames, পূর্ণসংখ্যা frame_গুনতি, পূর্ণসংখ্যা hot_x, পূর্ণসংখ্যা hot_y)
{
    // Dynamically generate cursors at the appropriate DPI
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, আকার(*cursor));
    যদি (!cursor) {
        ফেরত ফাঁকা;
    }

    SDL_Cursor_তথ্য *তথ্য = (SDL_Cursor_তথ্য *)SDL_calloc(1, আকার(*তথ্য) + (আকার(SDL_CursorFrameInfo) * (frame_গুনতি - 1)));
    যদি (!তথ্য) {
        SDL_free(cursor);
        ফেরত ফাঁকা;
    }

    তথ্য->hot_x = hot_x;
    তথ্য->hot_y = hot_y;
    তথ্য->অঙ্ক_frames = frame_গুনতি;
    জন্য (পূর্ণসংখ্যা i = 0; i < frame_গুনতি; ++i) {
        SDL_Surface *surface = frames[i].surface;
        যদি (surface->flags & SDL_SURFACE_PREALLOCATED) {
            surface = SDL_DuplicateSurface(surface);
            যদি (!surface) {
                যখন (i > 0) {
                    --i;
                    SDL_DestroySurface(তথ্য->frames[i].surface);
                }
                SDL_free(তথ্য);
                SDL_free(cursor);
                ফেরত ফাঁকা;
            }
        } অন্যথা {
            ++surface->refcount;
        }
        তথ্য->frames[i].surface = surface;
        তথ্য->frames[i].duration = frames[i].duration;
    }
    cursor->internal = তথ্য;
    ফেরত cursor;
}

স্থির bool Save_Chunk_আকার(SDL_IOStream* dst, Sint64 offset)
{
    Sint64 here = SDL_TellIO(dst);
    যদি (here < 0) {
        ফেরত false;
    }
    যদি (SDL_SeekIO(dst, offset, SDL_IO_SEEK_SET) < 0) {
        ফেরত false;
    }

    DWORD আকার_2 = (DWORD)(here - (offset + আকার(DWORD)));
    যদি (!SDL_WriteU32LE(dst, আকার_2)) {
        ফেরত false;
    }
    ফেরত SDL_SeekIO(dst, here, SDL_IO_SEEK_SET);
}

স্থির bool FillIconEntry(CURSORICONFILEDIRENTRY *entry, SDL_Surface *surface, পূর্ণসংখ্যা hot_x, পূর্ণসংখ্যা hot_y, DWORD dw_Image_আকার, DWORD dwImageOffset)
{
    যদি (surface->props) {
        hot_x = (পূর্ণসংখ্যা)SDL_Get_সংখ্যা_Property(surface->props, SDL_PROP_SURFACE_HOTSPOT_X_সংখ্যা, hot_x);
        hot_y = (পূর্ণসংখ্যা)SDL_Get_সংখ্যা_Property(surface->props, SDL_PROP_SURFACE_HOTSPOT_Y_সংখ্যা, hot_y);
    }
    hot_x = SDL_clamp(hot_x, 0, surface->w - 1);
    hot_y = SDL_clamp(hot_y, 0, surface->h - 1);

    SDL_zerop(entry);
    entry->bWidth = surface->w < 256 ? surface->w : 0;  // 0 means a width of 256
    entry->bHeight = surface->h < 256 ? surface->h : 0; // 0 means a height of 256
    entry->xHotspot = hot_x;
    entry->yHotspot = hot_y;
    entry->dw_Image_আকার = dw_Image_আকার;
    entry->dwImageOffset = dwImageOffset;
    ফেরত true;
}

#ifdef SAVE_ICON_PNG

স্থির bool WriteIconSurface(SDL_IOStream *dst, SDL_Surface *surface)
{
    যদি (!SDL_SavePNG_IO(surface, dst, false)) {
        ফেরত false;
    }

    // Image data offsets must be WORD aligned
    Sint64 offset = SDL_TellIO(dst);
    যদি (offset & 1) {
        যদি (!SDL_WriteU8(dst, 0)) {
            ফেরত false;
        }
    }
    ফেরত true;
}

#অন্যথা

/* For info on the expected mask format see:
 * https://devblogs.microsoft.com/oldnewthing/20101018-00/?p=12513
 */
স্থির শূন্য *CreateIconMask(SDL_Surface *surface, size_t *mask_আকার)
{
    Uint8 *dst;
    ধ্রুবক পূর্ণসংখ্যা w = (surface->w + 7) / 8;
    ধ্রুবক পূর্ণসংখ্যা pad = (((w) % 4) ? (4 - ((w) % 4)) : 0);
    ধ্রুবক পূর্ণসংখ্যা pitch = (w + pad);
    ধ্রুবক size_t আকার_2 = pitch * surface->h;
    স্থির ধ্রুবক unsigned অক্ষর masks[] = { 0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1 };

    শূন্য *mask = SDL_malloc(আকার_2);
    যদি (!mask) {
        ফেরত ফাঁকা;
    }

    dst = (Uint8 *)mask;

    // Make the mask completely transparent.
    SDL_memset(dst, 0xff, আকার_2);
    জন্য (পূর্ণসংখ্যা y = surface->h - 1; y >= 0; --y, dst += pitch) {
        জন্য (পূর্ণসংখ্যা x = 0; x < surface->w; ++x) {
            Uint8 r, g, b, a;
            SDL_ReadSurfacePixel(surface, x, y, &r, &g, &b, &a);

            যদি (a != 0) {
                // Reset bit of an opaque pixel.
                dst[x >> 3] &= ~masks[x & 7];
            }
        }
    }
    *mask_আকার = আকার_2;
    ফেরত mask;
}

স্থির bool WriteIconSurface(SDL_IOStream *dst, SDL_Surface *surface)
{
    SDL_Surface *অস্থায়ী = ফাঁকা;

    যদি (surface->format != SDL_PIXELFORMAT_ARGB8888) {
        অস্থায়ী = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        যদি (!অস্থায়ী) {
            ফেরত false;
        }
        surface = অস্থায়ী;
    }

    // Cursor data is double height (DIB and mask), stored bottom-up
    bool ok = true;
    size_t mask_আকার = 0;
    শূন্য *mask = CreateIconMask(surface, &mask_আকার);
    যদি (!mask) {
        ok = false;
        যাও done;
    }

    BITMAPINFOHEADER bmih;
    SDL_zero(bmih);
    DWORD row_আকার = surface->w * 4;
    bmih.bi_আকার = আকার(BITMAPINFOHEADER);
    bmih.biWidth = surface->w;
    bmih.biHeight = surface->h * 2;
    bmih.biPlanes = 1;
    bmih.bi_Bit_গুনতি = 32;
    bmih.biCompression = BI_RGB;
    bmih.bi_আকার_Image = (DWORD)(surface->h * row_আকার + mask_আকার);
    ok &= (SDL_WriteIO(dst, &bmih, আকার(bmih)) == আকার(bmih));

    ধ্রুবক Uint8 *pix = surface->pixels;
    pix += (surface->h - 1) * surface->pitch;
    জন্য (পূর্ণসংখ্যা i = 0; i < surface->h; ++i) {
        ok &= (SDL_WriteIO(dst, pix, row_আকার) == row_আকার);
        pix -= surface->pitch;
    }
    ok &= (SDL_WriteIO(dst, mask, mask_আকার) == mask_আকার);

done:
    SDL_free(mask);
    SDL_DestroySurface(অস্থায়ী);
    ফেরত ok;
}

#endif // SAVE_ICON_PNG

স্থির bool WriteIconFrame(SDL_IOStream *dst, SDL_Surface *surface, পূর্ণসংখ্যা hot_x, পূর্ণসংখ্যা hot_y, দশমিক scale)
{
#ifdef SAVE_MULTIPLE_ICONS
    পূর্ণসংখ্যা গুনতি = 0;
    SDL_Surface **surfaces = SDL_GetSurfaceImages(surface, &গুনতি);
    যদি (!surfaces) {
        ফেরত false;
    }
#অন্যথা
    surface = SDL_GetSurfaceImage(surface, scale);
    যদি (!surface) {
        ফেরত false;
    }

    পূর্ণসংখ্যা গুনতি = 1;
    SDL_Surface **surfaces = &surface;
#endif

    // Raymond Chen has more insight into this format at:
    // https://devblogs.microsoft.com/oldnewthing/20101018-00/?p=12513
    bool ok = true;
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('i', 'c', 'o', 'n'));
    Sint64 icon_আকার_offset = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    Sint64 base_offset = icon_আকার_offset + আকার(DWORD);

    CURSORICONFILEDIR dir;
    dir.idReserved = 0;
    dir.idType = 2; // Cursor
    dir.id_গুনতি = গুনতি;
    ok &= (SDL_WriteIO(dst, &dir, আকার(dir)) == আকার(dir));

    DWORD entries_আকার = গুনতি * আকার(CURSORICONFILEDIRENTRY);
    CURSORICONFILEDIRENTRY *entries = (CURSORICONFILEDIRENTRY *)SDL_malloc(entries_আকার);
    যদি (!entries) {
        ok = false;
        যাও done;
    }
    ok &= (SDL_WriteIO(dst, entries, entries_আকার) == entries_আকার);

    Sint64 image_offset = SDL_TellIO(dst);
    জন্য (পূর্ণসংখ্যা i = 0; i < গুনতি; ++i) {
        ok &= WriteIconSurface(dst, surfaces[i]);

        Sint64 পরবর্তী_offset = SDL_TellIO(dst);
        DWORD dw_Image_আকার = (DWORD)(পরবর্তী_offset - image_offset);
        DWORD dwImageOffset = (DWORD)(image_offset - base_offset);

        ok &= FillIconEntry(&entries[i], surfaces[i], hot_x, hot_y, dw_Image_আকার, dwImageOffset);

        image_offset = পরবর্তী_offset;
    }

    // Now that we have the icon entries filled out, rewrite them
    ok &= (SDL_SeekIO(dst, base_offset + আকার(dir), SDL_IO_SEEK_SET) >= 0);
    ok &= (SDL_WriteIO(dst, entries, entries_আকার) == entries_আকার);
    ok &= (SDL_SeekIO(dst, image_offset, SDL_IO_SEEK_SET) >= 0);
    SDL_free(entries);

    ok &= Save_Chunk_আকার(dst, icon_আকার_offset);

done:
#ifdef SAVE_MULTIPLE_ICONS
    SDL_free(surfaces);
#অন্যথা
    SDL_DestroySurface(surface);
#endif
    ফেরত ok;
}

/* Windows doesn't have an API to easily create animated cursors from a sequence of images,
 * so we have to build an animated cursor resource file in memory and load it.
 */
স্থির HCURSOR WIN_CreateAnimatedCursorInternal(SDL_CursorFrameInfo *frames, পূর্ণসংখ্যা frame_গুনতি, পূর্ণসংখ্যা hot_x, পূর্ণসংখ্যা hot_y, দশমিক scale)
{
    HCURSOR hcursor = ফাঁকা;
    SDL_IOStream *dst = SDL_IOFromDynamicMem();
    যদি (!dst) {
        ফেরত ফাঁকা;
    }

    পূর্ণসংখ্যা w = (পূর্ণসংখ্যা)SDL_roundf(frames[0].surface->w * scale);
    পূর্ণসংখ্যা h = (পূর্ণসংখ্যা)SDL_roundf(frames[0].surface->h * scale);

    bool ok = true;
    // RIFF header
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('R', 'I', 'F', 'F'));
    Sint64 riff_আকার_offset = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('A', 'C', 'O', 'N'));

    // anih header chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('a', 'n', 'i', 'h'));
    ok &= SDL_WriteU32LE(dst, আকার(ANIHEADER));

    ANIHEADER anih;
    SDL_zero(anih);
    anih.cbSizeof = আকার(anih);
    anih.frames = frame_গুনতি;
    anih.steps = frame_গুনতি;
    anih.jifRate = 1;
    anih.fl = ANI_FLAG_ICON;
    ok &= (SDL_WriteIO(dst, &anih, আকার(anih)) == আকার(anih));

    // Rate chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('r', 'a', 't', 'e'));
    ok &= SDL_WriteU32LE(dst, আকার(DWORD) * frame_গুনতি);
    জন্য (পূর্ণসংখ্যা i = 0; i < frame_গুনতি; ++i) {
        // Animated Win32 cursors are in jiffy units, and one jiffy is 1/60 of a second.
        ধ্রুবক দ্বিগুণ WIN32_JIFFY = 1000.0 / 60.0;
        DWORD duration = (frames[i].duration ? SDL_lround(frames[i].duration / WIN32_JIFFY) : 0xFFFFFFFF);
        ok &= SDL_WriteU32LE(dst, duration);
    }

    // Frame list
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('L', 'I', 'S', 'T'));
    Sint64 frame_list_আকার_offset = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('f', 'r', 'a', 'm'));

    জন্য (পূর্ণসংখ্যা i = 0; i < frame_গুনতি; ++i) {
        ok &= WriteIconFrame(dst, frames[i].surface, hot_x, hot_y, scale);
    }
    ok &= Save_Chunk_আকার(dst, frame_list_আকার_offset);

    // All done!
    ok &= Save_Chunk_আকার(dst, riff_আকার_offset);
    যদি (!ok) {
        // The error has been set above
        যাও done;
    }

    BYTE *mem = (BYTE *)SDL_GetPointerProperty(SDL_GetIOProperties(dst), SDL_PROP_IOSTREAM_DYNAMIC_MEMORY_POINTER, ফাঁকা);
    DWORD আকার_2 = (DWORD)SDL_GetIOSize(dst);
    hcursor = (HCURSOR)CreateIconFromResourceEx(mem, আকার_2, FALSE, 0x00030000, w, h, 0);
    যদি (!hcursor) {
        SDL_SetError("CreateIconFromResource failed");
    }

done:
    SDL_CloseIO(dst);

    ফেরত hcursor;
}

স্থির SDL_Cursor *WIN_CreateCursor(SDL_Surface *surface, পূর্ণসংখ্যা hot_x, পূর্ণসংখ্যা hot_y)
{
    SDL_CursorFrameInfo frame = { surface, 0 };
    ফেরত WIN_Create_Animated_Cursor_And_তথ্য(&frame, 1, hot_x, hot_y);
}

স্থির SDL_Cursor *WIN_CreateAnimatedCursor(SDL_CursorFrameInfo *frames, পূর্ণসংখ্যা frame_গুনতি, পূর্ণসংখ্যা hot_x, পূর্ণসংখ্যা hot_y)
{
    ফেরত WIN_Create_Animated_Cursor_And_তথ্য(frames, frame_গুনতি, hot_x, hot_y);
}

স্থির SDL_Cursor *WIN_CreateBlankCursor(শূন্য)
{
    SDL_Cursor *cursor = ফাঁকা;
    SDL_Surface *surface = SDL_CreateSurfaceZeroed(32, 32, SDL_PIXELFORMAT_ARGB8888);
    যদি (surface) {
        cursor = WIN_CreateCursor(surface, 0, 0);
        SDL_DestroySurface(surface);
    }
    ফেরত cursor;
}

স্থির SDL_Cursor *WIN_CreateSystemCursor(SDL_SystemCursor id)
{
    LPCTSTR name;

    নির্বাচন (id) {
    পূর্বনির্ধারিত:
        SDL_assert(!"Unknown system cursor ID");
        ফেরত ফাঁকা;
    ক্ষেত্র SDL_SYSTEM_CURSOR_DEFAULT:
        name = IDC_ARROW;
        বিরতি;
    ক্ষেত্র SDL_SYSTEM_CURSOR_TEXT:
    ক্ষেত্র SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        name = IDC_IBEAM;
        বিরতি;
    ক্ষেত্র SDL_SYSTEM_CURSOR_WAIT:
        name = IDC_WAIT;
        বিরতি;
    ক্ষেত্র SDL_SYSTEM_CURSOR_CROSSHAIR:
    ক্ষেত্র SDL_SYSTEM_CURSOR_CELL:
        name = IDC_CROSS;
        বিরতি;
    ক্ষেত্র SDL_SYSTEM_CURSOR_PROGRESS:
        name = IDC_APPSTARTING;
        বিরতি;
    ক্ষেত্র SDL_SYSTEM_CURSOR_NWSE_RESIZE:
    ক্ষেত্র SDL_SYSTEM_CURSOR_NW_RESIZE:
    ক্ষেত্র SDL_SYSTEM_CURSOR_SE_RESIZE:
        name = IDC_SIZENWSE;
        বিরতি;
    ক্ষেত্র SDL_SYSTEM_CURSOR_NESW_RESIZE:
    ক্ষেত্র SDL_SYSTEM_CURSOR_NE_RESIZE:
    ক্ষেত্র SDL_SYSTEM_CURSOR_SW_RESIZE:
        name = IDC_SIZENESW;
        বিরতি;
    ক্ষেত্র SDL_SYSTEM_CURSOR_EW_RESIZE:
    ক্ষেত্র SDL_SYSTEM_CURSOR_E_RESIZE:
    ক্ষেত্র SDL_SYSTEM_CURSOR_W_RESIZE:
    ক্ষেত্র SDL_SYSTEM_CURSOR_COL_RESIZE:
        name = IDC_SIZEWE;
        বিরতি;
    ক্ষেত্র SDL_SYSTEM_CURSOR_NS_RESIZE:
    ক্ষেত্র SDL_SYSTEM_CURSOR_N_RESIZE:
    ক্ষেত্র SDL_SYSTEM_CURSOR_S_RESIZE:
    ক্ষেত্র SDL_SYSTEM_CURSOR_ROW_RESIZE:
        name = IDC_SIZENS;
        বিরতি;
    ক্ষেত্র SDL_SYSTEM_CURSOR_MOVE:
    ক্ষেত্র SDL_SYSTEM_CURSOR_ALL_SCROLL:
        name = IDC_SIZEALL;
        বিরতি;
    ক্ষেত্র SDL_SYSTEM_CURSOR_NOT_ALLOWED:
    ক্ষেত্র SDL_SYSTEM_CURSOR_NO_DROP:
        name = IDC_NO;
        বিরতি;
    ক্ষেত্র SDL_SYSTEM_CURSOR_POINTER:
    ক্ষেত্র SDL_SYSTEM_CURSOR_CONTEXT_MENU:
    ক্ষেত্র SDL_SYSTEM_CURSOR_ALIAS:
    ক্ষেত্র SDL_SYSTEM_CURSOR_COPY:
    ক্ষেত্র SDL_SYSTEM_CURSOR_GRAB:
    ক্ষেত্র SDL_SYSTEM_CURSOR_GRABBING:
    ক্ষেত্র SDL_SYSTEM_CURSOR_ZOOM_IN:
    ক্ষেত্র SDL_SYSTEM_CURSOR_ZOOM_OUT:
        name = IDC_HAND;
        বিরতি;
    ক্ষেত্র SDL_SYSTEM_CURSOR_HELP:
        name = IDC_HELP;
        বিরতি;
    }
    ফেরত WIN_Create_Cursor_And_তথ্য(LoadCursor(ফাঁকা, name));
}

স্থির SDL_Cursor *WIN_CreateDefaultCursor(শূন্য)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    ফেরত WIN_CreateSystemCursor(id);
}

স্থির শূন্য WIN_FreeCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_তথ্য *তথ্য = cursor->internal;

    জন্য (পূর্ণসংখ্যা i = 0; i < তথ্য->অঙ্ক_frames; ++i) {
        SDL_DestroySurface(তথ্য->frames[i].surface);
    }
    যখন (তথ্য->cache) {
        CachedCursor *entry = তথ্য->cache;
        তথ্য->cache = entry->পরবর্তী;
        যদি (entry->cursor) {
            DestroyCursor(entry->cursor);
        }
        SDL_free(entry);
    }
    যদি (তথ্য->cursor) {
        DestroyCursor(তথ্য->cursor);
    }
    SDL_free(তথ্য);
    SDL_free(cursor);
}

স্থির HCURSOR GetCachedCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_তথ্য *তথ্য = cursor->internal;

    দশমিক scale = 1.0f;
    যদি (SDL_GetHintBoolean(SDL_HINT_MOUSE_DPI_SCALE_CURSORS, false)) {
        scale = SDL_GetDisplayContentScale(SDL_GetDisplayForWindow(SDL_GetMouseFocus()));
        যদি (scale == 0.0f) {
            scale = 1.0f;
        }
    }
    জন্য (CachedCursor *entry = তথ্য->cache; entry; entry = entry->পরবর্তী) {
        যদি (scale == entry->scale) {
            ফেরত entry->cursor;
        }
    }

    // Need to create a cursor for this content scale
    HCURSOR hcursor = WIN_CreateAnimatedCursorInternal(তথ্য->frames, তথ্য->অঙ্ক_frames, তথ্য->hot_x, তথ্য->hot_y, scale);
    যদি (!hcursor) {
        ফেরত ফাঁকা;
    }

    CachedCursor *entry = (CachedCursor *)SDL_calloc(1, আকার(*entry));
    যদি (!entry) {
        DestroyCursor(hcursor);
        ফেরত ফাঁকা;
    }
    entry->cursor = hcursor;
    entry->scale = scale;
    entry->পরবর্তী = তথ্য->cache;
    তথ্য->cache = entry;

    ফেরত hcursor;
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
        SDL_Cursor_তথ্য *তথ্য = cursor->internal;
        যদি (তথ্য->অঙ্ক_frames > 0) {
            SDL_cursor = GetCachedCursor(cursor);
        } অন্যথা {
            SDL_cursor = তথ্য->cursor;
        }
    } অন্যথা {
        SDL_cursor = ফাঁকা;
    }
    যদি (SDL_GetMouseFocus() != ফাঁকা) {
        SetCursor(SDL_cursor);
    }
    ফেরত true;
}

শূন্য WIN_SetCursorPos(পূর্ণসংখ্যা x, পূর্ণসংখ্যা y)
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

স্থির bool WIN_WarpMouse(SDL_Window *window, দশমিক x, দশমিক y)
{
    SDL_Window_তথ্য *তথ্য = window->internal;
    HWND hwnd = তথ্য->hwnd;
    POINT pt;

    // Don't warp the mouse while we're doing a modal interaction
    যদি (তথ্য->in_title_click || তথ্য->focus_click_pending) {
        ফেরত true;
    }

    pt.x = (পূর্ণসংখ্যা)SDL_roundf(x);
    pt.y = (পূর্ণসংখ্যা)SDL_roundf(y);
    ClientToScreen(hwnd, &pt);
    WIN_SetCursorPos(pt.x, pt.y);

    // Send the exact mouse motion associated with this warp
    SDL_SendMouseMotion(0, window, SDL_GLOBAL_MOUSE_ID, false, x, y);
    ফেরত true;
}

স্থির bool WIN_WarpMouseGlobal(দশমিক x, দশমিক y)
{
    POINT pt;

    pt.x = (পূর্ণসংখ্যা)SDL_roundf(x);
    pt.y = (পূর্ণসংখ্যা)SDL_roundf(y);
    SetCursorPos(pt.x, pt.y);
    ফেরত true;
}

স্থির bool WIN_SetRelativeMouseMode(bool enabled)
{
    ফেরত WIN_SetRawMouseEnabled(SDL_GetVideoDevice(), enabled);
}

স্থির bool WIN_CaptureMouse(SDL_Window *window)
{
    যদি (window) {
        SDL_Window_তথ্য *তথ্য = window->internal;
        SetCapture(তথ্য->hwnd);
    } অন্যথা {
        SDL_Window *focus_window = SDL_GetMouseFocus();

        যদি (focus_window) {
            SDL_Window_তথ্য *তথ্য = focus_window->internal;
            যদি (!তথ্য->mouse_tracked) {
                SDL_SetMouseFocus(ফাঁকা);
            }
        }
        ReleaseCapture();
    }

    ফেরত true;
}

স্থির SDL_MouseButtonFlags WIN_GetGlobalMouseState(দশমিক *x, দশমিক *y)
{
    SDL_MouseButtonFlags ফলাফল = 0;
    POINT pt = { 0, 0 };
    bool swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;

    GetCursorPos(&pt);
    *x = (দশমিক)pt.x;
    *y = (দশমিক)pt.y;

    ফলাফল |= Get_Async_চাবি_State(!swapButtons ? VK_LBUTTON : VK_RBUTTON) & 0x8000 ? SDL_BUTTON_LMASK : 0;
    ফলাফল |= Get_Async_চাবি_State(!swapButtons ? VK_RBUTTON : VK_LBUTTON) & 0x8000 ? SDL_BUTTON_RMASK : 0;
    ফলাফল |= Get_Async_চাবি_State(VK_MBUTTON) & 0x8000 ? SDL_BUTTON_MMASK : 0;
    ফলাফল |= Get_Async_চাবি_State(VK_XBUTTON1) & 0x8000 ? SDL_BUTTON_X1MASK : 0;
    ফলাফল |= Get_Async_চাবি_State(VK_XBUTTON2) & 0x8000 ? SDL_BUTTON_X2MASK : 0;

    ফেরত ফলাফল;
}

স্থির শূন্য WIN_ApplySystemScale(শূন্য *internal, Uint64 timestamp, SDL_Window *window, SDL_MouseID mouseID, দশমিক *x, দশমিক *y)
{
    যদি (!internal) {
        ফেরত;
    }
    WIN_Mouse_তথ্য *তথ্য = (WIN_Mouse_তথ্য *)internal;

    SDL_VideoDisplay *display = window ? SDL_GetVideoDisplayForWindow(window) : SDL_GetVideoDisplay(SDL_GetPrimaryDisplay());

    Sint64 ix = (Sint64)*x * 65536;
    Sint64 iy = (Sint64)*y * 65536;
    Uint32 dpi = display ? (Uint32)(display->content_scale * USER_DEFAULT_SCREEN_DPI) : USER_DEFAULT_SCREEN_DPI;

    যদি (!তথ্য->enhanced) { // early return if flat scale
        dpi = তথ্য->dpiscale * (তথ্য->dpiaware ? dpi : USER_DEFAULT_SCREEN_DPI);
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
        *x = (দশমিক)ix / 65536.0f;
        *y = (দশমিক)iy / 65536.0f;
        ফেরত;
    }

    Uint64 *xs = তথ্য->xs;
    Uint64 *ys = তথ্য->ys;
    Uint64 absx = SDL_abs(ix);
    Uint64 absy = SDL_abs(iy);
    Uint64 speed = SDL_min(absx, absy) + (SDL_max(absx, absy) << 1); // super cursed approximation used by Windows
    যদি (speed == 0) {
        ফেরত;
    }

    পূর্ণসংখ্যা i, j, k;
    জন্য (i = 1; i < 5; i++) {
        j = i;
        যদি (speed < xs[j]) {
            বিরতি;
        }
    }
    i -= 1;
    j -= 1;
    k = তথ্য->last_গ্রন্থি;
    তথ্য->last_গ্রন্থি = j;

    Uint32 denom = তথ্য->dpidenom;
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
    *x = (দশমিক)ix / 65536.0f;
    *y = (দশমিক)iy / 65536.0f;
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
    mouse->system_scale_তথ্য = &WIN_system_scale_তথ্য;

    SDL_SetDefaultCursor(WIN_CreateDefaultCursor());

    SDL_blank_cursor = WIN_CreateBlankCursor();

    WIN_UpdateMouseSystemScale();
}

শূন্য WIN_QuitMouse(SDL_VideoDevice *_this)
{
    যদি (SDL_blank_cursor) {
        WIN_FreeCursor(SDL_blank_cursor);
        SDL_blank_cursor = ফাঁকা;
    }
}

স্থির শূন্য ReadMouseCurve(পূর্ণসংখ্যা v, Uint64 xs[5], Uint64 ys[5])
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
    DWORD xsize = আকার(xbuff);
    DWORD ysize = আকার(ybuff);
    HKEY open_handle;
    যদি (Reg_Open_চাবি_Ex_W(HKEY_CURRENT_USER, L"Control Panel\\Mouse", 0, চাবি_READ, &open_handle) == ERROR_SUCCESS) {
        Reg_Query_মান_Ex_W(open_handle, L"SmoothMouseXCurve", ফাঁকা, ফাঁকা, (BYTE*)xbuff, &xsize);
        Reg_Query_মান_Ex_W(open_handle, L"SmoothMouseYCurve", ফাঁকা, ফাঁকা, (BYTE*)ybuff, &ysize);
        Reg_Close_চাবি(open_handle);
    }
    xs[0] = 0; // first node must always be origin
    ys[0] = 0; // first node must always be origin
    পূর্ণসংখ্যা i;
    জন্য (i = 1; i < 5; i++) {
        xs[i] = (7 * (Uint64)xbuff[i * 2]);
        ys[i] = (v * (Uint64)ybuff[i * 2]) << 17;
    }
}

শূন্য WIN_UpdateMouseSystemScale(শূন্য)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    যদি (mouse->ApplySystemScale == WIN_ApplySystemScale) {
        mouse->system_scale_তথ্য = &WIN_system_scale_তথ্য;
    }

    // always reinitialize to valid defaults, whether fetch was successful or not.
    WIN_Mouse_তথ্য *তথ্য = &WIN_system_scale_তথ্য;
    তথ্য->residual[0] = 0;
    তথ্য->residual[1] = 0;
    তথ্য->dpiscale = 32;
    তথ্য->dpidenom = (10 * (WIN_IsWindows8OrGreater() ? 120 : 150)) << 16;
    তথ্য->dpiaware = WIN_IsPerMonitorV2DPIAware(SDL_GetVideoDevice());
    তথ্য->enhanced = false;

    পূর্ণসংখ্যা v = 10;
    যদি (SystemParametersInfo(SPI_GETMOUSESPEED, 0, &v, 0)) {
        v = SDL_max(1, SDL_min(v, 20));
        তথ্য->dpiscale = SDL_max(SDL_max(v, (v - 2) * 4), (v - 6) * 8);
    }

    পূর্ণসংখ্যা params[3];
    যদি (SystemParametersInfo(SPI_GETMOUSE, 0, &params, 0)) {
        তথ্য->enhanced = params[2] ? true : false;
        যদি (params[2]) {
            ReadMouseCurve(v, তথ্য->xs, তথ্য->ys);
        }
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS

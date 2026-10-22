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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ଯଦି defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ଅନ୍ତର୍ଭାଵ "SDL_windowsvideo.h"
#ଅନ୍ତର୍ଭାଵ "SDL_windowsevents.h"
#ଅନ୍ତର୍ଭାଵ "SDL_windowsrawinput.h"

#ଅନ୍ତର୍ଭାଵ "../SDL_video_c.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_mouse_c.h"
#ଅନ୍ତର୍ଭାଵ "../../joystick/usb_ids.h"
#ଅନ୍ତର୍ଭାଵ "../../core/windows/SDL_windows.h" // for checking windows version

#define RIFF_FOURCC(c0, c1, c2, c3)                 \
    ((DWORD)(BYTE)(c0) | ((DWORD)(BYTE)(c1) << 8) | \
     ((DWORD)(BYTE)(c2) << 16) | ((DWORD)(BYTE)(c3) << 24))

#define ANI_FLAG_ICON 0x1

#pragma pack(ଠେଲ, 1)

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା
{
    BYTE bWidth;
    BYTE bHeight;
    BYTE b_Color_ଗଣନା;
    BYTE bReserved;
    WORD xHotspot;
    WORD yHotspot;
    DWORD dwImageSize;
    DWORD dwImageOffset;
} CURSORICONFILEDIRENTRY;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା
{
    WORD idReserved;
    WORD idType;
    WORD id_ଗଣନା;
} CURSORICONFILEDIR;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା
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

#pragma pack(କାଢ଼)

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା CachedCursor
{
    ଦଶମିକ scale;
    HCURSOR cursor;
    ସଂରଚନା CachedCursor *next;
} CachedCursor;

ସଂରଚନା SDL_CursorData
{
    HCURSOR cursor;

    CachedCursor *cache;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_x;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_y;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ_frames;
    SDL_CursorFrameInfo frames[1];
};

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା
{
    Uint64 xs[5];
    Uint64 ys[5];
    Sint64 residual[2];
    Uint32 dpiscale;
    Uint32 dpidenom;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା last_ଗଣ୍ଠି;
    bool enhanced;
    bool dpiaware;
} WIN_MouseData;

DWORD SDL_last_warp_time = 0;
HCURSOR SDL_cursor = ଖାଲି;
ସ୍ଥିର SDL_Cursor *SDL_blank_cursor = ଖାଲି;
ସ୍ଥିର WIN_MouseData WIN_system_scale_data;

ସ୍ଥିର SDL_Cursor *WIN_CreateCursorAndData(HCURSOR hcursor)
{
    ଯଦି (!hcursor) {
        ଫେରନ୍ତୁ ଖାଲି;
    }

    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, ଆକାର(*cursor));
    ଯଦି (!cursor) {
        ଫେରନ୍ତୁ ଖାଲି;
    }

    SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, ଆକାର(*data));
    ଯଦି (!data) {
        SDL_free(cursor);
        ଫେରନ୍ତୁ ଖାଲି;
    }

    data->cursor = hcursor;
    cursor->internal = data;
    ଫେରନ୍ତୁ cursor;
}

ସ୍ଥିର SDL_Cursor *WIN_CreateAnimatedCursorAndData(SDL_CursorFrameInfo *frames, ପୂର୍ଣ୍ଣସଂଖ୍ୟା frame_ଗଣନା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_y)
{
    // Dynamically generate cursors at the appropriate DPI
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, ଆକାର(*cursor));
    ଯଦି (!cursor) {
        ଫେରନ୍ତୁ ଖାଲି;
    }

    SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, ଆକାର(*data) + (ଆକାର(SDL_CursorFrameInfo) * (frame_ଗଣନା - 1)));
    ଯଦି (!data) {
        SDL_free(cursor);
        ଫେରନ୍ତୁ ଖାଲି;
    }

    data->hot_x = hot_x;
    data->hot_y = hot_y;
    data->ଅଙ୍କ_frames = frame_ଗଣନା;
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < frame_ଗଣନା; ++i) {
        SDL_Surface *surface = frames[i].surface;
        ଯଦି (surface->flags & SDL_SURFACE_PREALLOCATED) {
            surface = SDL_DuplicateSurface(surface);
            ଯଦି (!surface) {
                ଯେତେବେଳେ (i > 0) {
                    --i;
                    SDL_DestroySurface(data->frames[i].surface);
                }
                SDL_free(data);
                SDL_free(cursor);
                ଫେରନ୍ତୁ ଖାଲି;
            }
        } ଅନ୍ୟଥା {
            ++surface->refcount;
        }
        data->frames[i].surface = surface;
        data->frames[i].duration = frames[i].duration;
    }
    cursor->internal = data;
    ଫେରନ୍ତୁ cursor;
}

ସ୍ଥିର bool SaveChunkSize(SDL_IOStream* dst, Sint64 offset)
{
    Sint64 here = SDL_TellIO(dst);
    ଯଦି (here < 0) {
        ଫେରନ୍ତୁ false;
    }
    ଯଦି (SDL_SeekIO(dst, offset, SDL_IO_SEEK_SET) < 0) {
        ଫେରନ୍ତୁ false;
    }

    DWORD size = (DWORD)(here - (offset + ଆକାର(DWORD)));
    ଯଦି (!SDL_WriteU32LE(dst, size)) {
        ଫେରନ୍ତୁ false;
    }
    ଫେରନ୍ତୁ SDL_SeekIO(dst, here, SDL_IO_SEEK_SET);
}

ସ୍ଥିର bool FillIconEntry(CURSORICONFILEDIRENTRY *entry, SDL_Surface *surface, ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_y, DWORD dwImageSize, DWORD dwImageOffset)
{
    ଯଦି (surface->props) {
        hot_x = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)SDL_Get_ସଂଖ୍ୟା_Property(surface->props, SDL_PROP_SURFACE_HOTSPOT_X_ସଂଖ୍ୟା, hot_x);
        hot_y = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)SDL_Get_ସଂଖ୍ୟା_Property(surface->props, SDL_PROP_SURFACE_HOTSPOT_Y_ସଂଖ୍ୟା, hot_y);
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
    ଫେରନ୍ତୁ true;
}

#ifdef SAVE_ICON_PNG

ସ୍ଥିର bool WriteIconSurface(SDL_IOStream *dst, SDL_Surface *surface)
{
    ଯଦି (!SDL_SavePNG_IO(surface, dst, false)) {
        ଫେରନ୍ତୁ false;
    }

    // Image data offsets must be WORD aligned
    Sint64 offset = SDL_TellIO(dst);
    ଯଦି (offset & 1) {
        ଯଦି (!SDL_WriteU8(dst, 0)) {
            ଫେରନ୍ତୁ false;
        }
    }
    ଫେରନ୍ତୁ true;
}

#ଅନ୍ୟଥା

/* For info on the expected mask format see:
 * https://devblogs.microsoft.com/oldnewthing/20101018-00/?p=12513
 */
ସ୍ଥିର ଶୂନ୍ୟ *CreateIconMask(SDL_Surface *surface, size_t *mask_size)
{
    Uint8 *dst;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା w = (surface->w + 7) / 8;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା pad = (((w) % 4) ? (4 - ((w) % 4)) : 0);
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା pitch = (w + pad);
    ଅଚଳ size_t size = pitch * surface->h;
    ସ୍ଥିର ଅଚଳ unsigned ଅକ୍ଷର masks[] = { 0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1 };

    ଶୂନ୍ୟ *mask = SDL_malloc(size);
    ଯଦି (!mask) {
        ଫେରନ୍ତୁ ଖାଲି;
    }

    dst = (Uint8 *)mask;

    // Make the mask completely transparent.
    SDL_memset(dst, 0xff, size);
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା y = surface->h - 1; y >= 0; --y, dst += pitch) {
        ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା x = 0; x < surface->w; ++x) {
            Uint8 r, g, b, a;
            SDL_ReadSurfacePixel(surface, x, y, &r, &g, &b, &a);

            ଯଦି (a != 0) {
                // Reset bit of an opaque pixel.
                dst[x >> 3] &= ~masks[x & 7];
            }
        }
    }
    *mask_size = size;
    ଫେରନ୍ତୁ mask;
}

ସ୍ଥିର bool WriteIconSurface(SDL_IOStream *dst, SDL_Surface *surface)
{
    SDL_Surface *temp = ଖାଲି;

    ଯଦି (surface->format != SDL_PIXELFORMAT_ARGB8888) {
        temp = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        ଯଦି (!temp) {
            ଫେରନ୍ତୁ false;
        }
        surface = temp;
    }

    // Cursor data is double height (DIB and mask), stored bottom-up
    bool ok = true;
    size_t mask_size = 0;
    ଶୂନ୍ୟ *mask = CreateIconMask(surface, &mask_size);
    ଯଦି (!mask) {
        ok = false;
        ଯାଅ done;
    }

    BITMAPINFOHEADER bmih;
    SDL_zero(bmih);
    DWORD row_size = surface->w * 4;
    bmih.biSize = ଆକାର(BITMAPINFOHEADER);
    bmih.biWidth = surface->w;
    bmih.biHeight = surface->h * 2;
    bmih.biPlanes = 1;
    bmih.bi_Bit_ଗଣନା = 32;
    bmih.biCompression = BI_RGB;
    bmih.biSizeImage = (DWORD)(surface->h * row_size + mask_size);
    ok &= (SDL_WriteIO(dst, &bmih, ଆକାର(bmih)) == ଆକାର(bmih));

    ଅଚଳ Uint8 *pix = surface->pixels;
    pix += (surface->h - 1) * surface->pitch;
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < surface->h; ++i) {
        ok &= (SDL_WriteIO(dst, pix, row_size) == row_size);
        pix -= surface->pitch;
    }
    ok &= (SDL_WriteIO(dst, mask, mask_size) == mask_size);

done:
    SDL_free(mask);
    SDL_DestroySurface(temp);
    ଫେରନ୍ତୁ ok;
}

#endif // SAVE_ICON_PNG

ସ୍ଥିର bool WriteIconFrame(SDL_IOStream *dst, SDL_Surface *surface, ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_y, ଦଶମିକ scale)
{
#ifdef SAVE_MULTIPLE_ICONS
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଗଣନା_2 = 0;
    SDL_Surface **surfaces = SDL_GetSurfaceImages(surface, &ଗଣନା_2);
    ଯଦି (!surfaces) {
        ଫେରନ୍ତୁ false;
    }
#ଅନ୍ୟଥା
    surface = SDL_GetSurfaceImage(surface, scale);
    ଯଦି (!surface) {
        ଫେରନ୍ତୁ false;
    }

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଗଣନା_2 = 1;
    SDL_Surface **surfaces = &surface;
#endif

    // Raymond Chen has more insight into this format at:
    // https://devblogs.microsoft.com/oldnewthing/20101018-00/?p=12513
    bool ok = true;
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('i', 'c', 'o', 'n'));
    Sint64 icon_size_offset = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    Sint64 base_offset = icon_size_offset + ଆକାର(DWORD);

    CURSORICONFILEDIR dir;
    dir.idReserved = 0;
    dir.idType = 2; // Cursor
    dir.id_ଗଣନା = ଗଣନା_2;
    ok &= (SDL_WriteIO(dst, &dir, ଆକାର(dir)) == ଆକାର(dir));

    DWORD entries_size = ଗଣନା_2 * ଆକାର(CURSORICONFILEDIRENTRY);
    CURSORICONFILEDIRENTRY *entries = (CURSORICONFILEDIRENTRY *)SDL_malloc(entries_size);
    ଯଦି (!entries) {
        ok = false;
        ଯାଅ done;
    }
    ok &= (SDL_WriteIO(dst, entries, entries_size) == entries_size);

    Sint64 image_offset = SDL_TellIO(dst);
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < ଗଣନା_2; ++i) {
        ok &= WriteIconSurface(dst, surfaces[i]);

        Sint64 next_offset = SDL_TellIO(dst);
        DWORD dwImageSize = (DWORD)(next_offset - image_offset);
        DWORD dwImageOffset = (DWORD)(image_offset - base_offset);

        ok &= FillIconEntry(&entries[i], surfaces[i], hot_x, hot_y, dwImageSize, dwImageOffset);

        image_offset = next_offset;
    }

    // Now that we have the icon entries filled out, rewrite them
    ok &= (SDL_SeekIO(dst, base_offset + ଆକାର(dir), SDL_IO_SEEK_SET) >= 0);
    ok &= (SDL_WriteIO(dst, entries, entries_size) == entries_size);
    ok &= (SDL_SeekIO(dst, image_offset, SDL_IO_SEEK_SET) >= 0);
    SDL_free(entries);

    ok &= SaveChunkSize(dst, icon_size_offset);

done:
#ifdef SAVE_MULTIPLE_ICONS
    SDL_free(surfaces);
#ଅନ୍ୟଥା
    SDL_DestroySurface(surface);
#endif
    ଫେରନ୍ତୁ ok;
}

/* Windows doesn't have an API to easily create animated cursors from a sequence of images,
 * so we have to build an animated cursor resource file in memory and load it.
 */
ସ୍ଥିର HCURSOR WIN_CreateAnimatedCursorInternal(SDL_CursorFrameInfo *frames, ପୂର୍ଣ୍ଣସଂଖ୍ୟା frame_ଗଣନା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_y, ଦଶମିକ scale)
{
    HCURSOR hcursor = ଖାଲି;
    SDL_IOStream *dst = SDL_IOFromDynamicMem();
    ଯଦି (!dst) {
        ଫେରନ୍ତୁ ଖାଲି;
    }

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା w = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)SDL_roundf(frames[0].surface->w * scale);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା h = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)SDL_roundf(frames[0].surface->h * scale);

    bool ok = true;
    // RIFF header
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('R', 'I', 'F', 'F'));
    Sint64 riff_size_offset = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('A', 'C', 'O', 'N'));

    // anih header chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('a', 'n', 'i', 'h'));
    ok &= SDL_WriteU32LE(dst, ଆକାର(ANIHEADER));

    ANIHEADER anih;
    SDL_zero(anih);
    anih.cbSizeof = ଆକାର(anih);
    anih.frames = frame_ଗଣନା;
    anih.steps = frame_ଗଣନା;
    anih.jifRate = 1;
    anih.fl = ANI_FLAG_ICON;
    ok &= (SDL_WriteIO(dst, &anih, ଆକାର(anih)) == ଆକାର(anih));

    // Rate chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('r', 'a', 't', 'e'));
    ok &= SDL_WriteU32LE(dst, ଆକାର(DWORD) * frame_ଗଣନା);
    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < frame_ଗଣନା; ++i) {
        // Animated Win32 cursors are in jiffy units, and one jiffy is 1/60 of a second.
        ଅଚଳ ଦ୍ୱିଗୁଣ WIN32_JIFFY = 1000.0 / 60.0;
        DWORD duration = (frames[i].duration ? SDL_lround(frames[i].duration / WIN32_JIFFY) : 0xFFFFFFFF);
        ok &= SDL_WriteU32LE(dst, duration);
    }

    // Frame list
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('L', 'I', 'S', 'T'));
    Sint64 frame_list_size_offset = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('f', 'r', 'a', 'm'));

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < frame_ଗଣନା; ++i) {
        ok &= WriteIconFrame(dst, frames[i].surface, hot_x, hot_y, scale);
    }
    ok &= SaveChunkSize(dst, frame_list_size_offset);

    // All done!
    ok &= SaveChunkSize(dst, riff_size_offset);
    ଯଦି (!ok) {
        // The error has been set above
        ଯାଅ done;
    }

    BYTE *mem = (BYTE *)SDL_GetPointerProperty(SDL_GetIOProperties(dst), SDL_PROP_IOSTREAM_DYNAMIC_MEMORY_POINTER, ଖାଲି);
    DWORD size = (DWORD)SDL_GetIOSize(dst);
    hcursor = (HCURSOR)CreateIconFromResourceEx(mem, size, FALSE, 0x00030000, w, h, 0);
    ଯଦି (!hcursor) {
        SDL_SetError("CreateIconFromResource failed");
    }

done:
    SDL_CloseIO(dst);

    ଫେରନ୍ତୁ hcursor;
}

ସ୍ଥିର SDL_Cursor *WIN_CreateCursor(SDL_Surface *surface, ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_y)
{
    SDL_CursorFrameInfo frame = { surface, 0 };
    ଫେରନ୍ତୁ WIN_CreateAnimatedCursorAndData(&frame, 1, hot_x, hot_y);
}

ସ୍ଥିର SDL_Cursor *WIN_CreateAnimatedCursor(SDL_CursorFrameInfo *frames, ପୂର୍ଣ୍ଣସଂଖ୍ୟା frame_ଗଣନା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_y)
{
    ଫେରନ୍ତୁ WIN_CreateAnimatedCursorAndData(frames, frame_ଗଣନା, hot_x, hot_y);
}

ସ୍ଥିର SDL_Cursor *WIN_CreateBlankCursor(ଶୂନ୍ୟ)
{
    SDL_Cursor *cursor = ଖାଲି;
    SDL_Surface *surface = SDL_CreateSurfaceZeroed(32, 32, SDL_PIXELFORMAT_ARGB8888);
    ଯଦି (surface) {
        cursor = WIN_CreateCursor(surface, 0, 0);
        SDL_DestroySurface(surface);
    }
    ଫେରନ୍ତୁ cursor;
}

ସ୍ଥିର SDL_Cursor *WIN_CreateSystemCursor(SDL_SystemCursor id)
{
    LPCTSTR name;

    ବାଛ (id) {
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        SDL_assert(!"Unknown system cursor ID");
        ଫେରନ୍ତୁ ଖାଲି;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_DEFAULT:
        name = IDC_ARROW;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_TEXT:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        name = IDC_IBEAM;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_WAIT:
        name = IDC_WAIT;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_CROSSHAIR:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_CELL:
        name = IDC_CROSS;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_PROGRESS:
        name = IDC_APPSTARTING;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_NWSE_RESIZE:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_NW_RESIZE:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_SE_RESIZE:
        name = IDC_SIZENWSE;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_NESW_RESIZE:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_NE_RESIZE:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_SW_RESIZE:
        name = IDC_SIZENESW;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_EW_RESIZE:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_E_RESIZE:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_W_RESIZE:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_COL_RESIZE:
        name = IDC_SIZEWE;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_NS_RESIZE:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_N_RESIZE:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_S_RESIZE:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_ROW_RESIZE:
        name = IDC_SIZENS;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_MOVE:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_ALL_SCROLL:
        name = IDC_SIZEALL;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_NOT_ALLOWED:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_NO_DROP:
        name = IDC_NO;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_POINTER:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_CONTEXT_MENU:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_ALIAS:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_COPY:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_GRAB:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_GRABBING:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_ZOOM_IN:
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_ZOOM_OUT:
        name = IDC_HAND;
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_SYSTEM_CURSOR_HELP:
        name = IDC_HELP;
        ଭାଙ୍ଗ;
    }
    ଫେରନ୍ତୁ WIN_CreateCursorAndData(LoadCursor(ଖାଲି, name));
}

ସ୍ଥିର SDL_Cursor *WIN_CreateDefaultCursor(ଶୂନ୍ୟ)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    ଫେରନ୍ତୁ WIN_CreateSystemCursor(id);
}

ସ୍ଥିର ଶୂନ୍ୟ WIN_FreeCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *data = cursor->internal;

    ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < data->ଅଙ୍କ_frames; ++i) {
        SDL_DestroySurface(data->frames[i].surface);
    }
    ଯେତେବେଳେ (data->cache) {
        CachedCursor *entry = data->cache;
        data->cache = entry->next;
        ଯଦି (entry->cursor) {
            DestroyCursor(entry->cursor);
        }
        SDL_free(entry);
    }
    ଯଦି (data->cursor) {
        DestroyCursor(data->cursor);
    }
    SDL_free(data);
    SDL_free(cursor);
}

ସ୍ଥିର HCURSOR GetCachedCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *data = cursor->internal;

    ଦଶମିକ scale = 1.0f;
    ଯଦି (SDL_GetHintBoolean(SDL_HINT_MOUSE_DPI_SCALE_CURSORS, false)) {
        scale = SDL_GetDisplayContentScale(SDL_GetDisplayForWindow(SDL_GetMouseFocus()));
        ଯଦି (scale == 0.0f) {
            scale = 1.0f;
        }
    }
    ପାଇଁ (CachedCursor *entry = data->cache; entry; entry = entry->next) {
        ଯଦି (scale == entry->scale) {
            ଫେରନ୍ତୁ entry->cursor;
        }
    }

    // Need to create a cursor for this content scale
    HCURSOR hcursor = WIN_CreateAnimatedCursorInternal(data->frames, data->ଅଙ୍କ_frames, data->hot_x, data->hot_y, scale);
    ଯଦି (!hcursor) {
        ଫେରନ୍ତୁ ଖାଲି;
    }

    CachedCursor *entry = (CachedCursor *)SDL_calloc(1, ଆକାର(*entry));
    ଯଦି (!entry) {
        DestroyCursor(hcursor);
        ଫେରନ୍ତୁ ଖାଲି;
    }
    entry->cursor = hcursor;
    entry->scale = scale;
    entry->next = data->cache;
    data->cache = entry;

    ଫେରନ୍ତୁ hcursor;
}

ସ୍ଥିର bool WIN_ShowCursor(SDL_Cursor *cursor)
{
    ଯଦି (!cursor) {
        ଯଦି (GetSystemMetrics(SM_REMOTESESSION)) {
            // Use a blank cursor so we continue to get relative motion over RDP
            cursor = SDL_blank_cursor;
        }
    }
    ଯଦି (cursor) {
        SDL_CursorData *data = cursor->internal;
        ଯଦି (data->ଅଙ୍କ_frames > 0) {
            SDL_cursor = GetCachedCursor(cursor);
        } ଅନ୍ୟଥା {
            SDL_cursor = data->cursor;
        }
    } ଅନ୍ୟଥା {
        SDL_cursor = ଖାଲି;
    }
    ଯଦି (SDL_GetMouseFocus() != ଖାଲି) {
        SetCursor(SDL_cursor);
    }
    ଫେରନ୍ତୁ true;
}

ଶୂନ୍ୟ WIN_SetCursorPos(ପୂର୍ଣ୍ଣସଂଖ୍ୟା x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା y)
{
    // We need to jitter the value because otherwise Windows will occasionally inexplicably ignore the SetCursorPos() or SendInput()
    SetCursorPos(x, y);
    SetCursorPos(x + 1, y);
    SetCursorPos(x, y);

    // Flush any mouse motion prior to or associated with this warp
#ifdef _MSC_VER // We explicitly want to use GetTickCount(), not GetTickCount64()
#pragma warning(ଠେଲ)
#pragma warning(disable : 28159)
#endif
    SDL_last_warp_time = Get_Tick_ଗଣନା();
    ଯଦି (!SDL_last_warp_time) {
        SDL_last_warp_time = 1;
    }
#ifdef _MSC_VER
#pragma warning(କାଢ଼)
#endif
}

ସ୍ଥିର bool WIN_WarpMouse(SDL_Window *window, ଦଶମିକ x, ଦଶମିକ y)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    POINT pt;

    // Don't warp the mouse while we're doing a modal interaction
    ଯଦି (data->in_title_click || data->focus_click_pending) {
        ଫେରନ୍ତୁ true;
    }

    pt.x = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)SDL_roundf(x);
    pt.y = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)SDL_roundf(y);
    ClientToScreen(hwnd, &pt);
    WIN_SetCursorPos(pt.x, pt.y);

    // Send the exact mouse motion associated with this warp
    SDL_SendMouseMotion(0, window, SDL_GLOBAL_MOUSE_ID, false, x, y);
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool WIN_WarpMouseGlobal(ଦଶମିକ x, ଦଶମିକ y)
{
    POINT pt;

    pt.x = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)SDL_roundf(x);
    pt.y = (ପୂର୍ଣ୍ଣସଂଖ୍ୟା)SDL_roundf(y);
    SetCursorPos(pt.x, pt.y);
    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର bool WIN_SetRelativeMouseMode(bool enabled)
{
    ଫେରନ୍ତୁ WIN_SetRawMouseEnabled(SDL_GetVideoDevice(), enabled);
}

ସ୍ଥିର bool WIN_CaptureMouse(SDL_Window *window)
{
    ଯଦି (window) {
        SDL_WindowData *data = window->internal;
        SetCapture(data->hwnd);
    } ଅନ୍ୟଥା {
        SDL_Window *focus_window = SDL_GetMouseFocus();

        ଯଦି (focus_window) {
            SDL_WindowData *data = focus_window->internal;
            ଯଦି (!data->mouse_tracked) {
                SDL_SetMouseFocus(ଖାଲି);
            }
        }
        ReleaseCapture();
    }

    ଫେରନ୍ତୁ true;
}

ସ୍ଥିର SDL_MouseButtonFlags WIN_GetGlobalMouseState(ଦଶମିକ *x, ଦଶମିକ *y)
{
    SDL_MouseButtonFlags result = 0;
    POINT pt = { 0, 0 };
    bool swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;

    GetCursorPos(&pt);
    *x = (ଦଶମିକ)pt.x;
    *y = (ଦଶମିକ)pt.y;

    result |= Get_Async_ଚାବି_State(!swapButtons ? VK_LBUTTON : VK_RBUTTON) & 0x8000 ? SDL_BUTTON_LMASK : 0;
    result |= Get_Async_ଚାବି_State(!swapButtons ? VK_RBUTTON : VK_LBUTTON) & 0x8000 ? SDL_BUTTON_RMASK : 0;
    result |= Get_Async_ଚାବି_State(VK_MBUTTON) & 0x8000 ? SDL_BUTTON_MMASK : 0;
    result |= Get_Async_ଚାବି_State(VK_XBUTTON1) & 0x8000 ? SDL_BUTTON_X1MASK : 0;
    result |= Get_Async_ଚାବି_State(VK_XBUTTON2) & 0x8000 ? SDL_BUTTON_X2MASK : 0;

    ଫେରନ୍ତୁ result;
}

ସ୍ଥିର ଶୂନ୍ୟ WIN_ApplySystemScale(ଶୂନ୍ୟ *internal, Uint64 timestamp, SDL_Window *window, SDL_MouseID mouseID, ଦଶମିକ *x, ଦଶମିକ *y)
{
    ଯଦି (!internal) {
        ଫେରନ୍ତୁ;
    }
    WIN_MouseData *data = (WIN_MouseData *)internal;

    SDL_VideoDisplay *display = window ? SDL_GetVideoDisplayForWindow(window) : SDL_GetVideoDisplay(SDL_GetPrimaryDisplay());

    Sint64 ix = (Sint64)*x * 65536;
    Sint64 iy = (Sint64)*y * 65536;
    Uint32 dpi = display ? (Uint32)(display->content_scale * USER_DEFAULT_SCREEN_DPI) : USER_DEFAULT_SCREEN_DPI;

    ଯଦି (!data->enhanced) { // early return if flat scale
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
        *x = (ଦଶମିକ)ix / 65536.0f;
        *y = (ଦଶମିକ)iy / 65536.0f;
        ଫେରନ୍ତୁ;
    }

    Uint64 *xs = data->xs;
    Uint64 *ys = data->ys;
    Uint64 absx = SDL_abs(ix);
    Uint64 absy = SDL_abs(iy);
    Uint64 speed = SDL_min(absx, absy) + (SDL_max(absx, absy) << 1); // super cursed approximation used by Windows
    ଯଦି (speed == 0) {
        ଫେରନ୍ତୁ;
    }

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i, j, k;
    ପାଇଁ (i = 1; i < 5; i++) {
        j = i;
        ଯଦି (speed < xs[j]) {
            ଭାଙ୍ଗ;
        }
    }
    i -= 1;
    j -= 1;
    k = data->last_ଗଣ୍ଠି;
    data->last_ଗଣ୍ଠି = j;

    Uint32 denom = data->dpidenom;
    Sint64 scale = 0;
    Sint64 xdiff = xs[j+1] - xs[j];
    Sint64 ydiff = ys[j+1] - ys[j];
    ଯଦି (xdiff != 0) {
        Sint64 slope = ydiff / xdiff;
        Sint64 inter = slope * xs[i] - ys[i];
        scale += slope - inter / speed;
    }

    ଯଦି (j > k) {
        denom <<= 1;
        xdiff = xs[k+1] - xs[k];
        ydiff = ys[k+1] - ys[k];
        ଯଦି (xdiff != 0) {
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
    *x = (ଦଶମିକ)ix / 65536.0f;
    *y = (ଦଶମିକ)iy / 65536.0f;
}

ଶୂନ୍ୟ WIN_InitMouse(SDL_VideoDevice *_this)
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

ଶୂନ୍ୟ WIN_QuitMouse(SDL_VideoDevice *_this)
{
    ଯଦି (SDL_blank_cursor) {
        WIN_FreeCursor(SDL_blank_cursor);
        SDL_blank_cursor = ଖାଲି;
    }
}

ସ୍ଥିର ଶୂନ୍ୟ ReadMouseCurve(ପୂର୍ଣ୍ଣସଂଖ୍ୟା v, Uint64 xs[5], Uint64 ys[5])
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
    DWORD xsize = ଆକାର(xbuff);
    DWORD ysize = ଆକାର(ybuff);
    HKEY open_handle;
    ଯଦି (Reg_Open_ଚାବି_Ex_W(HKEY_CURRENT_USER, L"Control Panel\\Mouse", 0, ଚାବି_READ, &open_handle) == ERROR_SUCCESS) {
        Reg_Query_ମୂଲ୍ୟ_Ex_W(open_handle, L"SmoothMouseXCurve", ଖାଲି, ଖାଲି, (BYTE*)xbuff, &xsize);
        Reg_Query_ମୂଲ୍ୟ_Ex_W(open_handle, L"SmoothMouseYCurve", ଖାଲି, ଖାଲି, (BYTE*)ybuff, &ysize);
        Reg_Close_ଚାବି(open_handle);
    }
    xs[0] = 0; // first node must always be origin
    ys[0] = 0; // first node must always be origin
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା i;
    ପାଇଁ (i = 1; i < 5; i++) {
        xs[i] = (7 * (Uint64)xbuff[i * 2]);
        ys[i] = (v * (Uint64)ybuff[i * 2]) << 17;
    }
}

ଶୂନ୍ୟ WIN_UpdateMouseSystemScale(ଶୂନ୍ୟ)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    ଯଦି (mouse->ApplySystemScale == WIN_ApplySystemScale) {
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

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା v = 10;
    ଯଦି (SystemParametersInfo(SPI_GETMOUSESPEED, 0, &v, 0)) {
        v = SDL_max(1, SDL_min(v, 20));
        data->dpiscale = SDL_max(SDL_max(v, (v - 2) * 4), (v - 6) * 8);
    }

    ପୂର୍ଣ୍ଣସଂଖ୍ୟା params[3];
    ଯଦି (SystemParametersInfo(SPI_GETMOUSE, 0, &params, 0)) {
        data->enhanced = params[2] ? true : false;
        ଯଦି (params[2]) {
            ReadMouseCurve(v, data->xs, data->ys);
        }
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS

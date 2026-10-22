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
#समावेश "SDL_internal.h"

#अगर defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#समावेश "SDL_windowsvideo.h"
#समावेश "SDL_windowsevents.h"
#समावेश "SDL_windowsrawinput.h"

#समावेश "../SDL_video_c.h"
#समावेश "../../events/SDL_mouse_c.h"
#समावेश "../../joystick/usb_ids.h"
#समावेश "../../core/windows/SDL_windows.h" // for checking windows version

#घोषणा RIFF_FOURCC(c0, c1, c2, c3)                 \
    ((DWORD)(BYTE)(c0) | ((DWORD)(BYTE)(c1) << 8) | \
     ((DWORD)(BYTE)(c2) << 16) | ((DWORD)(BYTE)(c3) << 24))

#घोषणा ANI_FLAG_ICON 0x1

#आशय pack(धकेलो, 1)

प्रकार काष्ठा
{
    BYTE bWidth;
    BYTE bHeight;
    BYTE b_Color_गिनती;
    BYTE bReserved;
    WORD xHotspot;
    WORD yHotspot;
    DWORD dw_Image_आकार;
    DWORD dwImageOffset;
} CURSORICONFILEDIRENTRY;

प्रकार काष्ठा
{
    WORD idReserved;
    WORD idType;
    WORD id_गिनती;
} CURSORICONFILEDIR;

प्रकार काष्ठा
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

#आशय pack(निकालो)

प्रकार काष्ठा CachedCursor
{
    भग्न scale;
    HCURSOR cursor;
    काष्ठा CachedCursor *अग्र;
} CachedCursor;

काष्ठा SDL_Cursor_तथ्य
{
    HCURSOR cursor;

    CachedCursor *cache;
    पूर्णांक hot_x;
    पूर्णांक hot_y;
    पूर्णांक अंक_frames;
    SDL_CursorFrameInfo frames[1];
};

प्रकार काष्ठा
{
    Uint64 xs[5];
    Uint64 ys[5];
    Sint64 residual[2];
    Uint32 dpiscale;
    Uint32 dpidenom;
    पूर्णांक last_गाँठ;
    bool enhanced;
    bool dpiaware;
} WIN_Mouse_तथ्य;

DWORD SDL_last_warp_time = 0;
HCURSOR SDL_cursor = शून्य;
अटल SDL_Cursor *SDL_blank_cursor = शून्य;
अटल WIN_Mouse_तथ्य WIN_system_scale_तथ्य;

अटल SDL_Cursor *WIN_Create_Cursor_And_तथ्य(HCURSOR hcursor)
{
    अगर (!hcursor) {
        वापस शून्य;
    }

    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, माप(*cursor));
    अगर (!cursor) {
        वापस शून्य;
    }

    SDL_Cursor_तथ्य *तथ्य = (SDL_Cursor_तथ्य *)SDL_calloc(1, माप(*तथ्य));
    अगर (!तथ्य) {
        SDL_free(cursor);
        वापस शून्य;
    }

    तथ्य->cursor = hcursor;
    cursor->internal = तथ्य;
    वापस cursor;
}

अटल SDL_Cursor *WIN_Create_Animated_Cursor_And_तथ्य(SDL_CursorFrameInfo *frames, पूर्णांक frame_गिनती, पूर्णांक hot_x, पूर्णांक hot_y)
{
    // Dynamically generate cursors at the appropriate DPI
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, माप(*cursor));
    अगर (!cursor) {
        वापस शून्य;
    }

    SDL_Cursor_तथ्य *तथ्य = (SDL_Cursor_तथ्य *)SDL_calloc(1, माप(*तथ्य) + (माप(SDL_CursorFrameInfo) * (frame_गिनती - 1)));
    अगर (!तथ्य) {
        SDL_free(cursor);
        वापस शून्य;
    }

    तथ्य->hot_x = hot_x;
    तथ्य->hot_y = hot_y;
    तथ्य->अंक_frames = frame_गिनती;
    क्रम (पूर्णांक i = 0; i < frame_गिनती; ++i) {
        SDL_Surface *surface = frames[i].surface;
        अगर (surface->flags & SDL_SURFACE_PREALLOCATED) {
            surface = SDL_DuplicateSurface(surface);
            अगर (!surface) {
                जबतक (i > 0) {
                    --i;
                    SDL_DestroySurface(तथ्य->frames[i].surface);
                }
                SDL_free(तथ्य);
                SDL_free(cursor);
                वापस शून्य;
            }
        } अन्यथा {
            ++surface->refcount;
        }
        तथ्य->frames[i].surface = surface;
        तथ्य->frames[i].duration = frames[i].duration;
    }
    cursor->internal = तथ्य;
    वापस cursor;
}

अटल bool Save_Chunk_आकार(SDL_IOStream* dst, Sint64 offset)
{
    Sint64 here = SDL_TellIO(dst);
    अगर (here < 0) {
        वापस false;
    }
    अगर (SDL_SeekIO(dst, offset, SDL_IO_SEEK_SET) < 0) {
        वापस false;
    }

    DWORD आकार = (DWORD)(here - (offset + माप(DWORD)));
    अगर (!SDL_WriteU32LE(dst, आकार)) {
        वापस false;
    }
    वापस SDL_SeekIO(dst, here, SDL_IO_SEEK_SET);
}

अटल bool FillIconEntry(CURSORICONFILEDIRENTRY *entry, SDL_Surface *surface, पूर्णांक hot_x, पूर्णांक hot_y, DWORD dw_Image_आकार, DWORD dwImageOffset)
{
    अगर (surface->props) {
        hot_x = (पूर्णांक)SDL_Get_संख्या_Property(surface->props, SDL_PROP_SURFACE_HOTSPOT_X_संख्या, hot_x);
        hot_y = (पूर्णांक)SDL_Get_संख्या_Property(surface->props, SDL_PROP_SURFACE_HOTSPOT_Y_संख्या, hot_y);
    }
    hot_x = SDL_clamp(hot_x, 0, surface->w - 1);
    hot_y = SDL_clamp(hot_y, 0, surface->h - 1);

    SDL_zerop(entry);
    entry->bWidth = surface->w < 256 ? surface->w : 0;  // 0 means a width of 256
    entry->bHeight = surface->h < 256 ? surface->h : 0; // 0 means a height of 256
    entry->xHotspot = hot_x;
    entry->yHotspot = hot_y;
    entry->dw_Image_आकार = dw_Image_आकार;
    entry->dwImageOffset = dwImageOffset;
    वापस true;
}

#अगर_घोषित SAVE_ICON_PNG

अटल bool WriteIconSurface(SDL_IOStream *dst, SDL_Surface *surface)
{
    अगर (!SDL_SavePNG_IO(surface, dst, false)) {
        वापस false;
    }

    // Image data offsets must be WORD aligned
    Sint64 offset = SDL_TellIO(dst);
    अगर (offset & 1) {
        अगर (!SDL_WriteU8(dst, 0)) {
            वापस false;
        }
    }
    वापस true;
}

#अन्यथा

/* For info on the expected mask format see:
 * https://devblogs.microsoft.com/oldnewthing/20101018-00/?p=12513
 */
अटल व्योम *CreateIconMask(SDL_Surface *surface, माप_प्रकार *mask_आकार)
{
    Uint8 *dst;
    स्थिर पूर्णांक w = (surface->w + 7) / 8;
    स्थिर पूर्णांक pad = (((w) % 4) ? (4 - ((w) % 4)) : 0);
    स्थिर पूर्णांक pitch = (w + pad);
    स्थिर माप_प्रकार आकार = pitch * surface->h;
    अटल स्थिर अचिन्हित अक्षर masks[] = { 0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1 };

    व्योम *mask = SDL_malloc(आकार);
    अगर (!mask) {
        वापस शून्य;
    }

    dst = (Uint8 *)mask;

    // Make the mask completely transparent.
    SDL_memset(dst, 0xff, आकार);
    क्रम (पूर्णांक y = surface->h - 1; y >= 0; --y, dst += pitch) {
        क्रम (पूर्णांक x = 0; x < surface->w; ++x) {
            Uint8 r, g, b, a;
            SDL_ReadSurfacePixel(surface, x, y, &r, &g, &b, &a);

            अगर (a != 0) {
                // Reset bit of an opaque pixel.
                dst[x >> 3] &= ~masks[x & 7];
            }
        }
    }
    *mask_आकार = आकार;
    वापस mask;
}

अटल bool WriteIconSurface(SDL_IOStream *dst, SDL_Surface *surface)
{
    SDL_Surface *अस्थायी = शून्य;

    अगर (surface->format != SDL_PIXELFORMAT_ARGB8888) {
        अस्थायी = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        अगर (!अस्थायी) {
            वापस false;
        }
        surface = अस्थायी;
    }

    // Cursor data is double height (DIB and mask), stored bottom-up
    bool ok = true;
    माप_प्रकार mask_आकार = 0;
    व्योम *mask = CreateIconMask(surface, &mask_आकार);
    अगर (!mask) {
        ok = false;
        जाओ done;
    }

    BITMAPINFOHEADER bmih;
    SDL_zero(bmih);
    DWORD row_आकार = surface->w * 4;
    bmih.bi_आकार = माप(BITMAPINFOHEADER);
    bmih.biWidth = surface->w;
    bmih.biHeight = surface->h * 2;
    bmih.biPlanes = 1;
    bmih.bi_Bit_गिनती = 32;
    bmih.biCompression = BI_RGB;
    bmih.bi_आकार_Image = (DWORD)(surface->h * row_आकार + mask_आकार);
    ok &= (SDL_WriteIO(dst, &bmih, माप(bmih)) == माप(bmih));

    स्थिर Uint8 *pix = surface->pixels;
    pix += (surface->h - 1) * surface->pitch;
    क्रम (पूर्णांक i = 0; i < surface->h; ++i) {
        ok &= (SDL_WriteIO(dst, pix, row_आकार) == row_आकार);
        pix -= surface->pitch;
    }
    ok &= (SDL_WriteIO(dst, mask, mask_आकार) == mask_आकार);

done:
    SDL_free(mask);
    SDL_DestroySurface(अस्थायी);
    वापस ok;
}

#पूर्ण_अगर // SAVE_ICON_PNG

अटल bool WriteIconFrame(SDL_IOStream *dst, SDL_Surface *surface, पूर्णांक hot_x, पूर्णांक hot_y, भग्न scale)
{
#अगर_घोषित SAVE_MULTIPLE_ICONS
    पूर्णांक गिनती = 0;
    SDL_Surface **surfaces = SDL_GetSurfaceImages(surface, &गिनती);
    अगर (!surfaces) {
        वापस false;
    }
#अन्यथा
    surface = SDL_GetSurfaceImage(surface, scale);
    अगर (!surface) {
        वापस false;
    }

    पूर्णांक गिनती = 1;
    SDL_Surface **surfaces = &surface;
#पूर्ण_अगर

    // Raymond Chen has more insight into this format at:
    // https://devblogs.microsoft.com/oldnewthing/20101018-00/?p=12513
    bool ok = true;
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('i', 'c', 'o', 'n'));
    Sint64 icon_आकार_offset = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    Sint64 base_offset = icon_आकार_offset + माप(DWORD);

    CURSORICONFILEDIR dir;
    dir.idReserved = 0;
    dir.idType = 2; // Cursor
    dir.id_गिनती = गिनती;
    ok &= (SDL_WriteIO(dst, &dir, माप(dir)) == माप(dir));

    DWORD entries_आकार = गिनती * माप(CURSORICONFILEDIRENTRY);
    CURSORICONFILEDIRENTRY *entries = (CURSORICONFILEDIRENTRY *)SDL_malloc(entries_आकार);
    अगर (!entries) {
        ok = false;
        जाओ done;
    }
    ok &= (SDL_WriteIO(dst, entries, entries_आकार) == entries_आकार);

    Sint64 image_offset = SDL_TellIO(dst);
    क्रम (पूर्णांक i = 0; i < गिनती; ++i) {
        ok &= WriteIconSurface(dst, surfaces[i]);

        Sint64 अग्र_offset = SDL_TellIO(dst);
        DWORD dw_Image_आकार = (DWORD)(अग्र_offset - image_offset);
        DWORD dwImageOffset = (DWORD)(image_offset - base_offset);

        ok &= FillIconEntry(&entries[i], surfaces[i], hot_x, hot_y, dw_Image_आकार, dwImageOffset);

        image_offset = अग्र_offset;
    }

    // Now that we have the icon entries filled out, rewrite them
    ok &= (SDL_SeekIO(dst, base_offset + माप(dir), SDL_IO_SEEK_SET) >= 0);
    ok &= (SDL_WriteIO(dst, entries, entries_आकार) == entries_आकार);
    ok &= (SDL_SeekIO(dst, image_offset, SDL_IO_SEEK_SET) >= 0);
    SDL_free(entries);

    ok &= Save_Chunk_आकार(dst, icon_आकार_offset);

done:
#अगर_घोषित SAVE_MULTIPLE_ICONS
    SDL_free(surfaces);
#अन्यथा
    SDL_DestroySurface(surface);
#पूर्ण_अगर
    वापस ok;
}

/* Windows doesn't have an API to easily create animated cursors from a sequence of images,
 * so we have to build an animated cursor resource file in memory and load it.
 */
अटल HCURSOR WIN_CreateAnimatedCursorInternal(SDL_CursorFrameInfo *frames, पूर्णांक frame_गिनती, पूर्णांक hot_x, पूर्णांक hot_y, भग्न scale)
{
    HCURSOR hcursor = शून्य;
    SDL_IOStream *dst = SDL_IOFromDynamicMem();
    अगर (!dst) {
        वापस शून्य;
    }

    पूर्णांक w = (पूर्णांक)SDL_roundf(frames[0].surface->w * scale);
    पूर्णांक h = (पूर्णांक)SDL_roundf(frames[0].surface->h * scale);

    bool ok = true;
    // RIFF header
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('R', 'I', 'F', 'F'));
    Sint64 riff_आकार_offset = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('A', 'C', 'O', 'N'));

    // anih header chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('a', 'n', 'i', 'h'));
    ok &= SDL_WriteU32LE(dst, माप(ANIHEADER));

    ANIHEADER anih;
    SDL_zero(anih);
    anih.cbSizeof = माप(anih);
    anih.frames = frame_गिनती;
    anih.steps = frame_गिनती;
    anih.jifRate = 1;
    anih.fl = ANI_FLAG_ICON;
    ok &= (SDL_WriteIO(dst, &anih, माप(anih)) == माप(anih));

    // Rate chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('r', 'a', 't', 'e'));
    ok &= SDL_WriteU32LE(dst, माप(DWORD) * frame_गिनती);
    क्रम (पूर्णांक i = 0; i < frame_गिनती; ++i) {
        // Animated Win32 cursors are in jiffy units, and one jiffy is 1/60 of a second.
        स्थिर द्विगुन WIN32_JIFFY = 1000.0 / 60.0;
        DWORD duration = (frames[i].duration ? SDL_lround(frames[i].duration / WIN32_JIFFY) : 0xFFFFFFFF);
        ok &= SDL_WriteU32LE(dst, duration);
    }

    // Frame list
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('L', 'I', 'S', 'T'));
    Sint64 frame_list_आकार_offset = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('f', 'r', 'a', 'm'));

    क्रम (पूर्णांक i = 0; i < frame_गिनती; ++i) {
        ok &= WriteIconFrame(dst, frames[i].surface, hot_x, hot_y, scale);
    }
    ok &= Save_Chunk_आकार(dst, frame_list_आकार_offset);

    // All done!
    ok &= Save_Chunk_आकार(dst, riff_आकार_offset);
    अगर (!ok) {
        // The error has been set above
        जाओ done;
    }

    BYTE *mem = (BYTE *)SDL_GetPointerProperty(SDL_GetIOProperties(dst), SDL_PROP_IOSTREAM_DYNAMIC_MEMORY_POINTER, शून्य);
    DWORD आकार = (DWORD)SDL_GetIOSize(dst);
    hcursor = (HCURSOR)CreateIconFromResourceEx(mem, आकार, FALSE, 0x00030000, w, h, 0);
    अगर (!hcursor) {
        SDL_SetError("CreateIconFromResource failed");
    }

done:
    SDL_CloseIO(dst);

    वापस hcursor;
}

अटल SDL_Cursor *WIN_CreateCursor(SDL_Surface *surface, पूर्णांक hot_x, पूर्णांक hot_y)
{
    SDL_CursorFrameInfo frame = { surface, 0 };
    वापस WIN_Create_Animated_Cursor_And_तथ्य(&frame, 1, hot_x, hot_y);
}

अटल SDL_Cursor *WIN_CreateAnimatedCursor(SDL_CursorFrameInfo *frames, पूर्णांक frame_गिनती, पूर्णांक hot_x, पूर्णांक hot_y)
{
    वापस WIN_Create_Animated_Cursor_And_तथ्य(frames, frame_गिनती, hot_x, hot_y);
}

अटल SDL_Cursor *WIN_CreateBlankCursor(व्योम)
{
    SDL_Cursor *cursor = शून्य;
    SDL_Surface *surface = SDL_CreateSurfaceZeroed(32, 32, SDL_PIXELFORMAT_ARGB8888);
    अगर (surface) {
        cursor = WIN_CreateCursor(surface, 0, 0);
        SDL_DestroySurface(surface);
    }
    वापस cursor;
}

अटल SDL_Cursor *WIN_CreateSystemCursor(SDL_SystemCursor id)
{
    LPCTSTR name;

    चयन (id) {
    शेष:
        SDL_assert(!"Unknown system cursor ID");
        वापस शून्य;
    हाल SDL_SYSTEM_CURSOR_DEFAULT:
        name = IDC_ARROW;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_TEXT:
    हाल SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        name = IDC_IBEAM;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_WAIT:
        name = IDC_WAIT;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_CROSSHAIR:
    हाल SDL_SYSTEM_CURSOR_CELL:
        name = IDC_CROSS;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_PROGRESS:
        name = IDC_APPSTARTING;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_NWSE_RESIZE:
    हाल SDL_SYSTEM_CURSOR_NW_RESIZE:
    हाल SDL_SYSTEM_CURSOR_SE_RESIZE:
        name = IDC_SIZENWSE;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_NESW_RESIZE:
    हाल SDL_SYSTEM_CURSOR_NE_RESIZE:
    हाल SDL_SYSTEM_CURSOR_SW_RESIZE:
        name = IDC_SIZENESW;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_EW_RESIZE:
    हाल SDL_SYSTEM_CURSOR_E_RESIZE:
    हाल SDL_SYSTEM_CURSOR_W_RESIZE:
    हाल SDL_SYSTEM_CURSOR_COL_RESIZE:
        name = IDC_SIZEWE;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_NS_RESIZE:
    हाल SDL_SYSTEM_CURSOR_N_RESIZE:
    हाल SDL_SYSTEM_CURSOR_S_RESIZE:
    हाल SDL_SYSTEM_CURSOR_ROW_RESIZE:
        name = IDC_SIZENS;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_MOVE:
    हाल SDL_SYSTEM_CURSOR_ALL_SCROLL:
        name = IDC_SIZEALL;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_NOT_ALLOWED:
    हाल SDL_SYSTEM_CURSOR_NO_DROP:
        name = IDC_NO;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_POINTER:
    हाल SDL_SYSTEM_CURSOR_CONTEXT_MENU:
    हाल SDL_SYSTEM_CURSOR_ALIAS:
    हाल SDL_SYSTEM_CURSOR_COPY:
    हाल SDL_SYSTEM_CURSOR_GRAB:
    हाल SDL_SYSTEM_CURSOR_GRABBING:
    हाल SDL_SYSTEM_CURSOR_ZOOM_IN:
    हाल SDL_SYSTEM_CURSOR_ZOOM_OUT:
        name = IDC_HAND;
        अवरोध;
    हाल SDL_SYSTEM_CURSOR_HELP:
        name = IDC_HELP;
        अवरोध;
    }
    वापस WIN_Create_Cursor_And_तथ्य(LoadCursor(शून्य, name));
}

अटल SDL_Cursor *WIN_CreateDefaultCursor(व्योम)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    वापस WIN_CreateSystemCursor(id);
}

अटल व्योम WIN_FreeCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_तथ्य *तथ्य = cursor->internal;

    क्रम (पूर्णांक i = 0; i < तथ्य->अंक_frames; ++i) {
        SDL_DestroySurface(तथ्य->frames[i].surface);
    }
    जबतक (तथ्य->cache) {
        CachedCursor *entry = तथ्य->cache;
        तथ्य->cache = entry->अग्र;
        अगर (entry->cursor) {
            DestroyCursor(entry->cursor);
        }
        SDL_free(entry);
    }
    अगर (तथ्य->cursor) {
        DestroyCursor(तथ्य->cursor);
    }
    SDL_free(तथ्य);
    SDL_free(cursor);
}

अटल HCURSOR GetCachedCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_तथ्य *तथ्य = cursor->internal;

    भग्न scale = 1.0f;
    अगर (SDL_GetHintBoolean(SDL_HINT_MOUSE_DPI_SCALE_CURSORS, false)) {
        scale = SDL_GetDisplayContentScale(SDL_GetDisplayForWindow(SDL_GetMouseFocus()));
        अगर (scale == 0.0f) {
            scale = 1.0f;
        }
    }
    क्रम (CachedCursor *entry = तथ्य->cache; entry; entry = entry->अग्र) {
        अगर (scale == entry->scale) {
            वापस entry->cursor;
        }
    }

    // Need to create a cursor for this content scale
    HCURSOR hcursor = WIN_CreateAnimatedCursorInternal(तथ्य->frames, तथ्य->अंक_frames, तथ्य->hot_x, तथ्य->hot_y, scale);
    अगर (!hcursor) {
        वापस शून्य;
    }

    CachedCursor *entry = (CachedCursor *)SDL_calloc(1, माप(*entry));
    अगर (!entry) {
        DestroyCursor(hcursor);
        वापस शून्य;
    }
    entry->cursor = hcursor;
    entry->scale = scale;
    entry->अग्र = तथ्य->cache;
    तथ्य->cache = entry;

    वापस hcursor;
}

अटल bool WIN_ShowCursor(SDL_Cursor *cursor)
{
    अगर (!cursor) {
        अगर (GetSystemMetrics(SM_REMOTESESSION)) {
            // Use a blank cursor so we continue to get relative motion over RDP
            cursor = SDL_blank_cursor;
        }
    }
    अगर (cursor) {
        SDL_Cursor_तथ्य *तथ्य = cursor->internal;
        अगर (तथ्य->अंक_frames > 0) {
            SDL_cursor = GetCachedCursor(cursor);
        } अन्यथा {
            SDL_cursor = तथ्य->cursor;
        }
    } अन्यथा {
        SDL_cursor = शून्य;
    }
    अगर (SDL_GetMouseFocus() != शून्य) {
        SetCursor(SDL_cursor);
    }
    वापस true;
}

व्योम WIN_SetCursorPos(पूर्णांक x, पूर्णांक y)
{
    // We need to jitter the value because otherwise Windows will occasionally inexplicably ignore the SetCursorPos() or SendInput()
    SetCursorPos(x, y);
    SetCursorPos(x + 1, y);
    SetCursorPos(x, y);

    // Flush any mouse motion prior to or associated with this warp
#अगर_घोषित _MSC_VER // We explicitly want to use GetTickCount(), not GetTickCount64()
#आशय warning(धकेलो)
#आशय warning(disable : 28159)
#पूर्ण_अगर
    SDL_last_warp_time = Get_Tick_गिनती();
    अगर (!SDL_last_warp_time) {
        SDL_last_warp_time = 1;
    }
#अगर_घोषित _MSC_VER
#आशय warning(निकालो)
#पूर्ण_अगर
}

अटल bool WIN_WarpMouse(SDL_Window *window, भग्न x, भग्न y)
{
    SDL_Window_तथ्य *तथ्य = window->internal;
    HWND hwnd = तथ्य->hwnd;
    POINT pt;

    // Don't warp the mouse while we're doing a modal interaction
    अगर (तथ्य->in_title_click || तथ्य->focus_click_pending) {
        वापस true;
    }

    pt.x = (पूर्णांक)SDL_roundf(x);
    pt.y = (पूर्णांक)SDL_roundf(y);
    ClientToScreen(hwnd, &pt);
    WIN_SetCursorPos(pt.x, pt.y);

    // Send the exact mouse motion associated with this warp
    SDL_SendMouseMotion(0, window, SDL_GLOBAL_MOUSE_ID, false, x, y);
    वापस true;
}

अटल bool WIN_WarpMouseGlobal(भग्न x, भग्न y)
{
    POINT pt;

    pt.x = (पूर्णांक)SDL_roundf(x);
    pt.y = (पूर्णांक)SDL_roundf(y);
    SetCursorPos(pt.x, pt.y);
    वापस true;
}

अटल bool WIN_SetRelativeMouseMode(bool enabled)
{
    वापस WIN_SetRawMouseEnabled(SDL_GetVideoDevice(), enabled);
}

अटल bool WIN_CaptureMouse(SDL_Window *window)
{
    अगर (window) {
        SDL_Window_तथ्य *तथ्य = window->internal;
        SetCapture(तथ्य->hwnd);
    } अन्यथा {
        SDL_Window *focus_window = SDL_GetMouseFocus();

        अगर (focus_window) {
            SDL_Window_तथ्य *तथ्य = focus_window->internal;
            अगर (!तथ्य->mouse_tracked) {
                SDL_SetMouseFocus(शून्य);
            }
        }
        ReleaseCapture();
    }

    वापस true;
}

अटल SDL_MouseButtonFlags WIN_GetGlobalMouseState(भग्न *x, भग्न *y)
{
    SDL_MouseButtonFlags परिणाम = 0;
    POINT pt = { 0, 0 };
    bool swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;

    GetCursorPos(&pt);
    *x = (भग्न)pt.x;
    *y = (भग्न)pt.y;

    परिणाम |= Get_Async_कुंजी_State(!swapButtons ? VK_LBUTTON : VK_RBUTTON) & 0x8000 ? SDL_BUTTON_LMASK : 0;
    परिणाम |= Get_Async_कुंजी_State(!swapButtons ? VK_RBUTTON : VK_LBUTTON) & 0x8000 ? SDL_BUTTON_RMASK : 0;
    परिणाम |= Get_Async_कुंजी_State(VK_MBUTTON) & 0x8000 ? SDL_BUTTON_MMASK : 0;
    परिणाम |= Get_Async_कुंजी_State(VK_XBUTTON1) & 0x8000 ? SDL_BUTTON_X1MASK : 0;
    परिणाम |= Get_Async_कुंजी_State(VK_XBUTTON2) & 0x8000 ? SDL_BUTTON_X2MASK : 0;

    वापस परिणाम;
}

अटल व्योम WIN_ApplySystemScale(व्योम *internal, Uint64 timestamp, SDL_Window *window, SDL_MouseID mouseID, भग्न *x, भग्न *y)
{
    अगर (!internal) {
        वापस;
    }
    WIN_Mouse_तथ्य *तथ्य = (WIN_Mouse_तथ्य *)internal;

    SDL_VideoDisplay *display = window ? SDL_GetVideoDisplayForWindow(window) : SDL_GetVideoDisplay(SDL_GetPrimaryDisplay());

    Sint64 ix = (Sint64)*x * 65536;
    Sint64 iy = (Sint64)*y * 65536;
    Uint32 dpi = display ? (Uint32)(display->content_scale * USER_DEFAULT_SCREEN_DPI) : USER_DEFAULT_SCREEN_DPI;

    अगर (!तथ्य->enhanced) { // early return if flat scale
        dpi = तथ्य->dpiscale * (तथ्य->dpiaware ? dpi : USER_DEFAULT_SCREEN_DPI);
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
        *x = (भग्न)ix / 65536.0f;
        *y = (भग्न)iy / 65536.0f;
        वापस;
    }

    Uint64 *xs = तथ्य->xs;
    Uint64 *ys = तथ्य->ys;
    Uint64 absx = SDL_abs(ix);
    Uint64 absy = SDL_abs(iy);
    Uint64 speed = SDL_min(absx, absy) + (SDL_max(absx, absy) << 1); // super cursed approximation used by Windows
    अगर (speed == 0) {
        वापस;
    }

    पूर्णांक i, j, k;
    क्रम (i = 1; i < 5; i++) {
        j = i;
        अगर (speed < xs[j]) {
            अवरोध;
        }
    }
    i -= 1;
    j -= 1;
    k = तथ्य->last_गाँठ;
    तथ्य->last_गाँठ = j;

    Uint32 denom = तथ्य->dpidenom;
    Sint64 scale = 0;
    Sint64 xdiff = xs[j+1] - xs[j];
    Sint64 ydiff = ys[j+1] - ys[j];
    अगर (xdiff != 0) {
        Sint64 slope = ydiff / xdiff;
        Sint64 inter = slope * xs[i] - ys[i];
        scale += slope - inter / speed;
    }

    अगर (j > k) {
        denom <<= 1;
        xdiff = xs[k+1] - xs[k];
        ydiff = ys[k+1] - ys[k];
        अगर (xdiff != 0) {
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
    *x = (भग्न)ix / 65536.0f;
    *y = (भग्न)iy / 65536.0f;
}

व्योम WIN_InitMouse(SDL_VideoDevice *_this)
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
    mouse->system_scale_तथ्य = &WIN_system_scale_तथ्य;

    SDL_SetDefaultCursor(WIN_CreateDefaultCursor());

    SDL_blank_cursor = WIN_CreateBlankCursor();

    WIN_UpdateMouseSystemScale();
}

व्योम WIN_QuitMouse(SDL_VideoDevice *_this)
{
    अगर (SDL_blank_cursor) {
        WIN_FreeCursor(SDL_blank_cursor);
        SDL_blank_cursor = शून्य;
    }
}

अटल व्योम ReadMouseCurve(पूर्णांक v, Uint64 xs[5], Uint64 ys[5])
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
    DWORD xsize = माप(xbuff);
    DWORD ysize = माप(ybuff);
    HKEY open_handle;
    अगर (Reg_Open_कुंजी_Ex_W(HKEY_CURRENT_USER, L"Control Panel\\Mouse", 0, कुंजी_READ, &open_handle) == ERROR_SUCCESS) {
        Reg_Query_मूल्य_Ex_W(open_handle, L"SmoothMouseXCurve", शून्य, शून्य, (BYTE*)xbuff, &xsize);
        Reg_Query_मूल्य_Ex_W(open_handle, L"SmoothMouseYCurve", शून्य, शून्य, (BYTE*)ybuff, &ysize);
        Reg_Close_कुंजी(open_handle);
    }
    xs[0] = 0; // first node must always be origin
    ys[0] = 0; // first node must always be origin
    पूर्णांक i;
    क्रम (i = 1; i < 5; i++) {
        xs[i] = (7 * (Uint64)xbuff[i * 2]);
        ys[i] = (v * (Uint64)ybuff[i * 2]) << 17;
    }
}

व्योम WIN_UpdateMouseSystemScale(व्योम)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    अगर (mouse->ApplySystemScale == WIN_ApplySystemScale) {
        mouse->system_scale_तथ्य = &WIN_system_scale_तथ्य;
    }

    // always reinitialize to valid defaults, whether fetch was successful or not.
    WIN_Mouse_तथ्य *तथ्य = &WIN_system_scale_तथ्य;
    तथ्य->residual[0] = 0;
    तथ्य->residual[1] = 0;
    तथ्य->dpiscale = 32;
    तथ्य->dpidenom = (10 * (WIN_IsWindows8OrGreater() ? 120 : 150)) << 16;
    तथ्य->dpiaware = WIN_IsPerMonitorV2DPIAware(SDL_GetVideoDevice());
    तथ्य->enhanced = false;

    पूर्णांक v = 10;
    अगर (SystemParametersInfo(SPI_GETMOUSESPEED, 0, &v, 0)) {
        v = SDL_max(1, SDL_min(v, 20));
        तथ्य->dpiscale = SDL_max(SDL_max(v, (v - 2) * 4), (v - 6) * 8);
    }

    पूर्णांक params[3];
    अगर (SystemParametersInfo(SPI_GETMOUSE, 0, &params, 0)) {
        तथ्य->enhanced = params[2] ? true : false;
        अगर (params[2]) {
            ReadMouseCurve(v, तथ्य->xs, तथ्य->ys);
        }
    }
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_WINDOWS

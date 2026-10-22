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

#परिभाषय RIFF_FOURCC(c0, c1, c2, c3)                 \
    ((DWORD)(BYTE)(c0) | ((DWORD)(BYTE)(c1) << 8) | \
     ((DWORD)(BYTE)(c2) << 16) | ((DWORD)(BYTE)(c3) << 24))

#परिभाषय ANI_FLAG_ICON 0x1

#निर्देशः pack(प्रक्षिप, 1)

प्रकारनिर्देश संरचना
{
    BYTE b_विस्तारः;
    BYTE bHeight;
    BYTE b_Color_गणनम्;
    BYTE bReserved;
    WORD xHotspot;
    WORD yHotspot;
    DWORD dw_Image_आकार;
    DWORD dw_Image_विस्थापनम्;
} CURSORICONFILEDIRENTRY;

प्रकारनिर्देश संरचना
{
    WORD idReserved;
    WORD idType;
    WORD id_गणनम्;
} CURSORICONFILEDIR;

प्रकारनिर्देश संरचना
{
    DWORD cbSizeof; // sizeof(ANIHEADER) = 36 bytes.
    DWORD चौकटाः;   // Number of frames in the frame list.
    DWORD चरणाः;    // Number of steps in the animation loop.
    DWORD विस्तारः;    //विस्तारः
    DWORD height;   // Height
    DWORD bpp;      // bpp
    DWORD planes;   // Not used
    DWORD jif_दरः;  // Default display rate, in jiffies (1/60s)
    DWORD fl;       // AF_ICON should be set. AF_SEQUENCE is optional
} ANIHEADER;

#निर्देशः pack(निष्कासय)

प्रकारनिर्देश संरचना CachedCursor
{
    भिन्न scale;
    HCURSOR cursor;
    संरचना CachedCursor *अग्र;
} CachedCursor;

संरचना SDL_Cursor_दत्त
{
    HCURSOR cursor;

    CachedCursor *cache;
    पूर्णाङ्क hot_x;
    पूर्णाङ्क hot_y;
    पूर्णाङ्क अङ्कः_चौकटाः;
    SDL_CursorFrameInfo चौकटाः[1];
};

प्रकारनिर्देश संरचना
{
    Uint64 xs[5];
    Uint64 ys[5];
    Sint64 residual[2];
    Uint32 dpiscale;
    Uint32 dpidenom;
    पूर्णाङ्क चरमः_ग्रन्थिः;
    bool enhanced;
    bool dpiaware;
} WIN_Mouse_दत्त;

DWORD SDL_चरमः_warp_time = 0;
HCURSOR SDL_cursor = रिक्त;
स्थिर SDL_Cursor *SDL_blank_cursor = रिक्त;
स्थिर WIN_Mouse_दत्त WIN_system_scale_दत्त;

स्थिर SDL_Cursor *WIN_Create_Cursor_And_दत्त(HCURSOR hcursor)
{
    यदि (!hcursor) {
        प्रत्यागम रिक्त;
    }

    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, परिमाण(*cursor));
    यदि (!cursor) {
        प्रत्यागम रिक्त;
    }

    SDL_Cursor_दत्त *दत्त = (SDL_Cursor_दत्त *)SDL_calloc(1, परिमाण(*दत्त));
    यदि (!दत्त) {
        SDL_free(cursor);
        प्रत्यागम रिक्त;
    }

    दत्त->cursor = hcursor;
    cursor->आन्तरिकम् = दत्त;
    प्रत्यागम cursor;
}

स्थिर SDL_Cursor *WIN_Create_Animated_Cursor_And_दत्त(SDL_CursorFrameInfo *चौकटाः, पूर्णाङ्क frame_गणनम्, पूर्णाङ्क hot_x, पूर्णाङ्क hot_y)
{
    // Dynamically generate cursors at the appropriate DPI
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, परिमाण(*cursor));
    यदि (!cursor) {
        प्रत्यागम रिक्त;
    }

    SDL_Cursor_दत्त *दत्त = (SDL_Cursor_दत्त *)SDL_calloc(1, परिमाण(*दत्त) + (परिमाण(SDL_CursorFrameInfo) * (frame_गणनम् - 1)));
    यदि (!दत्त) {
        SDL_free(cursor);
        प्रत्यागम रिक्त;
    }

    दत्त->hot_x = hot_x;
    दत्त->hot_y = hot_y;
    दत्त->अङ्कः_चौकटाः = frame_गणनम्;
    प्रति (पूर्णाङ्क i = 0; i < frame_गणनम्; ++i) {
        SDL_Surface *surface = चौकटाः[i].surface;
        यदि (surface->flags & SDL_SURFACE_PREALLOCATED) {
            surface = SDL_DuplicateSurface(surface);
            यदि (!surface) {
                यावत् (i > 0) {
                    --i;
                    SDL_DestroySurface(दत्त->चौकटाः[i].surface);
                }
                SDL_free(दत्त);
                SDL_free(cursor);
                प्रत्यागम रिक्त;
            }
        } अन्यथा {
            ++surface->refcount;
        }
        दत्त->चौकटाः[i].surface = surface;
        दत्त->चौकटाः[i].duration = चौकटाः[i].duration;
    }
    cursor->आन्तरिकम् = दत्त;
    प्रत्यागम cursor;
}

स्थिर bool Save_Chunk_आकार(SDL_IOStream* dst, Sint64 विस्थापनम्_2)
{
    Sint64 अत्र = SDL_TellIO(dst);
    यदि (अत्र < 0) {
        प्रत्यागम false;
    }
    यदि (SDL_SeekIO(dst, विस्थापनम्_2, SDL_IO_SEEK_समुच्चयः) < 0) {
        प्रत्यागम false;
    }

    DWORD आकार = (DWORD)(अत्र - (विस्थापनम्_2 + परिमाण(DWORD)));
    यदि (!SDL_WriteU32LE(dst, आकार)) {
        प्रत्यागम false;
    }
    प्रत्यागम SDL_SeekIO(dst, अत्र, SDL_IO_SEEK_समुच्चयः);
}

स्थिर bool Fill_Icon_प्रविष्टिः(CURSORICONFILEDIRENTRY *प्रविष्टिः, SDL_Surface *surface, पूर्णाङ्क hot_x, पूर्णाङ्क hot_y, DWORD dw_Image_आकार, DWORD dw_Image_विस्थापनम्)
{
    यदि (surface->props) {
        hot_x = (पूर्णाङ्क)SDL_Get_सङ्ख्या_Property(surface->props, SDL_PROP_SURFACE_HOTSPOT_X_सङ्ख्या, hot_x);
        hot_y = (पूर्णाङ्क)SDL_Get_सङ्ख्या_Property(surface->props, SDL_PROP_SURFACE_HOTSPOT_Y_सङ्ख्या, hot_y);
    }
    hot_x = SDL_clamp(hot_x, 0, surface->w - 1);
    hot_y = SDL_clamp(hot_y, 0, surface->h - 1);

    SDL_zerop(प्रविष्टिः);
    प्रविष्टिः->b_विस्तारः = surface->w < 256 ? surface->w : 0;  // 0 means a width of 256
    प्रविष्टिः->bHeight = surface->h < 256 ? surface->h : 0; // 0 means a height of 256
    प्रविष्टिः->xHotspot = hot_x;
    प्रविष्टिः->yHotspot = hot_y;
    प्रविष्टिः->dw_Image_आकार = dw_Image_आकार;
    प्रविष्टिः->dw_Image_विस्थापनम् = dw_Image_विस्थापनम्;
    प्रत्यागम true;
}

#यदि_परिभाषितम् SAVE_ICON_PNG

स्थिर bool WriteIconSurface(SDL_IOStream *dst, SDL_Surface *surface)
{
    यदि (!SDL_SavePNG_IO(surface, dst, false)) {
        प्रत्यागम false;
    }

    // Image data offsets must be WORD aligned
    Sint64 विस्थापनम्_2 = SDL_TellIO(dst);
    यदि (विस्थापनम्_2 & 1) {
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
स्थिर शून्य *Create_Icon_आवरणम्(SDL_Surface *surface, size_t *आवरणम्_आकार)
{
    Uint8 *dst;
    ध्रुव पूर्णाङ्क w = (surface->w + 7) / 8;
    ध्रुव पूर्णाङ्क pad = (((w) % 4) ? (4 - ((w) % 4)) : 0);
    ध्रुव पूर्णाङ्क pitch = (w + pad);
    ध्रुव size_t आकार = pitch * surface->h;
    स्थिर ध्रुव अचिह्नित वर्ण masks[] = { 0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1 };

    शून्य *आवरणम् = SDL_malloc(आकार);
    यदि (!आवरणम्) {
        प्रत्यागम रिक्त;
    }

    dst = (Uint8 *)आवरणम्;

    // Make the mask completely transparent.
    SDL_memset(dst, 0xff, आकार);
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
    *आवरणम्_आकार = आकार;
    प्रत्यागम आवरणम्;
}

स्थिर bool WriteIconSurface(SDL_IOStream *dst, SDL_Surface *surface)
{
    SDL_Surface *अस्थायी = रिक्त;

    यदि (surface->format != SDL_PIXELFORMAT_ARGB8888) {
        अस्थायी = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        यदि (!अस्थायी) {
            प्रत्यागम false;
        }
        surface = अस्थायी;
    }

    // Cursor data is double height (DIB and mask), stored bottom-up
    bool ok = true;
    size_t आवरणम्_आकार = 0;
    शून्य *आवरणम् = Create_Icon_आवरणम्(surface, &आवरणम्_आकार);
    यदि (!आवरणम्) {
        ok = false;
        गच्छ समाप्तम्;
    }

    BITMAPINFOHEADER bmih;
    SDL_zero(bmih);
    DWORD row_आकार = surface->w * 4;
    bmih.bi_आकार = परिमाण(BITMAPINFOHEADER);
    bmih.bi_विस्तारः = surface->w;
    bmih.biHeight = surface->h * 2;
    bmih.biPlanes = 1;
    bmih.bi_Bit_गणनम् = 32;
    bmih.biCompression = BI_RGB;
    bmih.bi_आकार_Image = (DWORD)(surface->h * row_आकार + आवरणम्_आकार);
    ok &= (SDL_WriteIO(dst, &bmih, परिमाण(bmih)) == परिमाण(bmih));

    ध्रुव Uint8 *pix = surface->pixels;
    pix += (surface->h - 1) * surface->pitch;
    प्रति (पूर्णाङ्क i = 0; i < surface->h; ++i) {
        ok &= (SDL_WriteIO(dst, pix, row_आकार) == row_आकार);
        pix -= surface->pitch;
    }
    ok &= (SDL_WriteIO(dst, आवरणम्, आवरणम्_आकार) == आवरणम्_आकार);

समाप्तम्:
    SDL_free(आवरणम्);
    SDL_DestroySurface(अस्थायी);
    प्रत्यागम ok;
}

#यदि_अन्तः // SAVE_ICON_PNG

स्थिर bool WriteIconFrame(SDL_IOStream *dst, SDL_Surface *surface, पूर्णाङ्क hot_x, पूर्णाङ्क hot_y, भिन्न scale)
{
#यदि_परिभाषितम् SAVE_गुणजः_ICONS
    पूर्णाङ्क गणनम् = 0;
    SDL_Surface **surfaces = SDL_GetSurfaceImages(surface, &गणनम्);
    यदि (!surfaces) {
        प्रत्यागम false;
    }
#अन्यथा
    surface = SDL_GetSurfaceImage(surface, scale);
    यदि (!surface) {
        प्रत्यागम false;
    }

    पूर्णाङ्क गणनम् = 1;
    SDL_Surface **surfaces = &surface;
#यदि_अन्तः

    // Raymond Chen has more insight into this format at:
    // https://devblogs.microsoft.com/oldnewthing/20101018-00/?p=12513
    bool ok = true;
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('i', 'c', 'o', 'n'));
    Sint64 icon_आकार_विस्थापनम् = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    Sint64 आधारः_विस्थापनम्_2 = icon_आकार_विस्थापनम् + परिमाण(DWORD);

    CURSORICONFILEDIR dir;
    dir.idReserved = 0;
    dir.idType = 2; // Cursor
    dir.id_गणनम् = गणनम्;
    ok &= (SDL_WriteIO(dst, &dir, परिमाण(dir)) == परिमाण(dir));

    DWORD entries_आकार = गणनम् * परिमाण(CURSORICONFILEDIRENTRY);
    CURSORICONFILEDIRENTRY *entries = (CURSORICONFILEDIRENTRY *)SDL_malloc(entries_आकार);
    यदि (!entries) {
        ok = false;
        गच्छ समाप्तम्;
    }
    ok &= (SDL_WriteIO(dst, entries, entries_आकार) == entries_आकार);

    Sint64 image_विस्थापनम्_2 = SDL_TellIO(dst);
    प्रति (पूर्णाङ्क i = 0; i < गणनम्; ++i) {
        ok &= WriteIconSurface(dst, surfaces[i]);

        Sint64 अग्र_विस्थापनम् = SDL_TellIO(dst);
        DWORD dw_Image_आकार = (DWORD)(अग्र_विस्थापनम् - image_विस्थापनम्_2);
        DWORD dw_Image_विस्थापनम् = (DWORD)(image_विस्थापनम्_2 - आधारः_विस्थापनम्_2);

        ok &= Fill_Icon_प्रविष्टिः(&entries[i], surfaces[i], hot_x, hot_y, dw_Image_आकार, dw_Image_विस्थापनम्);

        image_विस्थापनम्_2 = अग्र_विस्थापनम्;
    }

    // Now that we have the icon entries filled out, rewrite them
    ok &= (SDL_SeekIO(dst, आधारः_विस्थापनम्_2 + परिमाण(dir), SDL_IO_SEEK_समुच्चयः) >= 0);
    ok &= (SDL_WriteIO(dst, entries, entries_आकार) == entries_आकार);
    ok &= (SDL_SeekIO(dst, image_विस्थापनम्_2, SDL_IO_SEEK_समुच्चयः) >= 0);
    SDL_free(entries);

    ok &= Save_Chunk_आकार(dst, icon_आकार_विस्थापनम्);

समाप्तम्:
#यदि_परिभाषितम् SAVE_गुणजः_ICONS
    SDL_free(surfaces);
#अन्यथा
    SDL_DestroySurface(surface);
#यदि_अन्तः
    प्रत्यागम ok;
}

/* Windows doesn't have an API to easily create animated cursors from a sequence of images,
 * so we have to build an animated cursor resource file in memory and load it.
 */
स्थिर HCURSOR WIN_Create_Animated_Cursor_आन्तरिकम्(SDL_CursorFrameInfo *चौकटाः, पूर्णाङ्क frame_गणनम्, पूर्णाङ्क hot_x, पूर्णाङ्क hot_y, भिन्न scale)
{
    HCURSOR hcursor = रिक्त;
    SDL_IOStream *dst = SDL_IOFromDynamicMem();
    यदि (!dst) {
        प्रत्यागम रिक्त;
    }

    पूर्णाङ्क w = (पूर्णाङ्क)SDL_roundf(चौकटाः[0].surface->w * scale);
    पूर्णाङ्क h = (पूर्णाङ्क)SDL_roundf(चौकटाः[0].surface->h * scale);

    bool ok = true;
    // RIFF header
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('R', 'I', 'F', 'F'));
    Sint64 riff_आकार_विस्थापनम् = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('A', 'C', 'O', 'N'));

    // anih header chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('a', 'n', 'i', 'h'));
    ok &= SDL_WriteU32LE(dst, परिमाण(ANIHEADER));

    ANIHEADER anih;
    SDL_zero(anih);
    anih.cbSizeof = परिमाण(anih);
    anih.चौकटाः = frame_गणनम्;
    anih.चरणाः = frame_गणनम्;
    anih.jif_दरः = 1;
    anih.fl = ANI_FLAG_ICON;
    ok &= (SDL_WriteIO(dst, &anih, परिमाण(anih)) == परिमाण(anih));

    // Rate chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('r', 'a', 't', 'e'));
    ok &= SDL_WriteU32LE(dst, परिमाण(DWORD) * frame_गणनम्);
    प्रति (पूर्णाङ्क i = 0; i < frame_गणनम्; ++i) {
        // Animated Win32 cursors are in jiffy units, and one jiffy is 1/60 of a second.
        ध्रुव द्विगुण WIN32_JIFFY = 1000.0 / 60.0;
        DWORD duration = (चौकटाः[i].duration ? SDL_lround(चौकटाः[i].duration / WIN32_JIFFY) : 0xFFFFFFFF);
        ok &= SDL_WriteU32LE(dst, duration);
    }

    // Frame list
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('L', 'I', 'S', 'T'));
    Sint64 frame_list_आकार_विस्थापनम् = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('f', 'r', 'a', 'm'));

    प्रति (पूर्णाङ्क i = 0; i < frame_गणनम्; ++i) {
        ok &= WriteIconFrame(dst, चौकटाः[i].surface, hot_x, hot_y, scale);
    }
    ok &= Save_Chunk_आकार(dst, frame_list_आकार_विस्थापनम्);

    // All done!
    ok &= Save_Chunk_आकार(dst, riff_आकार_विस्थापनम्);
    यदि (!ok) {
        // The error has been set above
        गच्छ समाप्तम्;
    }

    BYTE *mem = (BYTE *)SDL_GetPointerProperty(SDL_GetIOProperties(dst), SDL_PROP_IOSTREAM_DYNAMIC_स्मृतिः_POINTER, रिक्त);
    DWORD आकार = (DWORD)SDL_GetIOSize(dst);
    hcursor = (HCURSOR)CreateIconFromResourceEx(mem, आकार, FALSE, 0x00030000, w, h, 0);
    यदि (!hcursor) {
        SDL_समुच्चयः_Error("CreateIconFromResource failed");
    }

समाप्तम्:
    SDL_CloseIO(dst);

    प्रत्यागम hcursor;
}

स्थिर SDL_Cursor *WIN_CreateCursor(SDL_Surface *surface, पूर्णाङ्क hot_x, पूर्णाङ्क hot_y)
{
    SDL_CursorFrameInfo frame = { surface, 0 };
    प्रत्यागम WIN_Create_Animated_Cursor_And_दत्त(&frame, 1, hot_x, hot_y);
}

स्थिर SDL_Cursor *WIN_CreateAnimatedCursor(SDL_CursorFrameInfo *चौकटाः, पूर्णाङ्क frame_गणनम्, पूर्णाङ्क hot_x, पूर्णाङ्क hot_y)
{
    प्रत्यागम WIN_Create_Animated_Cursor_And_दत्त(चौकटाः, frame_गणनम्, hot_x, hot_y);
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
    पक्ष SDL_SYSTEM_CURSOR_प्रगतिः:
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
    पक्ष SDL_SYSTEM_CURSOR_ZOOM_अन्तर्:
    पक्ष SDL_SYSTEM_CURSOR_ZOOM_बहिर्गमनम्:
        name = IDC_HAND;
        भङ्ग;
    पक्ष SDL_SYSTEM_CURSOR_HELP:
        name = IDC_HELP;
        भङ्ग;
    }
    प्रत्यागम WIN_Create_Cursor_And_दत्त(आरोपय_Cursor(रिक्त, name));
}

स्थिर SDL_Cursor *WIN_CreateDefaultCursor(शून्य)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    प्रत्यागम WIN_CreateSystemCursor(id);
}

स्थिर शून्य WIN_FreeCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_दत्त *दत्त = cursor->आन्तरिकम्;

    प्रति (पूर्णाङ्क i = 0; i < दत्त->अङ्कः_चौकटाः; ++i) {
        SDL_DestroySurface(दत्त->चौकटाः[i].surface);
    }
    यावत् (दत्त->cache) {
        CachedCursor *प्रविष्टिः = दत्त->cache;
        दत्त->cache = प्रविष्टिः->अग्र;
        यदि (प्रविष्टिः->cursor) {
            DestroyCursor(प्रविष्टिः->cursor);
        }
        SDL_free(प्रविष्टिः);
    }
    यदि (दत्त->cursor) {
        DestroyCursor(दत्त->cursor);
    }
    SDL_free(दत्त);
    SDL_free(cursor);
}

स्थिर HCURSOR GetCachedCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_दत्त *दत्त = cursor->आन्तरिकम्;

    भिन्न scale = 1.0f;
    यदि (SDL_GetHintBoolean(SDL_HINT_MOUSE_DPI_SCALE_CURSORS, false)) {
        scale = SDL_GetDisplayContentScale(SDL_Get_Display_For_गवाक्षः(SDL_GetMouseFocus()));
        यदि (scale == 0.0f) {
            scale = 1.0f;
        }
    }
    प्रति (CachedCursor *प्रविष्टिः = दत्त->cache; प्रविष्टिः; प्रविष्टिः = प्रविष्टिः->अग्र) {
        यदि (scale == प्रविष्टिः->scale) {
            प्रत्यागम प्रविष्टिः->cursor;
        }
    }

    // Need to create a cursor for this content scale
    HCURSOR hcursor = WIN_Create_Animated_Cursor_आन्तरिकम्(दत्त->चौकटाः, दत्त->अङ्कः_चौकटाः, दत्त->hot_x, दत्त->hot_y, scale);
    यदि (!hcursor) {
        प्रत्यागम रिक्त;
    }

    CachedCursor *प्रविष्टिः = (CachedCursor *)SDL_calloc(1, परिमाण(*प्रविष्टिः));
    यदि (!प्रविष्टिः) {
        DestroyCursor(hcursor);
        प्रत्यागम रिक्त;
    }
    प्रविष्टिः->cursor = hcursor;
    प्रविष्टिः->scale = scale;
    प्रविष्टिः->अग्र = दत्त->cache;
    दत्त->cache = प्रविष्टिः;

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
        SDL_Cursor_दत्त *दत्त = cursor->आन्तरिकम्;
        यदि (दत्त->अङ्कः_चौकटाः > 0) {
            SDL_cursor = GetCachedCursor(cursor);
        } अन्यथा {
            SDL_cursor = दत्त->cursor;
        }
    } अन्यथा {
        SDL_cursor = रिक्त;
    }
    यदि (SDL_GetMouseFocus() != रिक्त) {
        समुच्चयः_Cursor(SDL_cursor);
    }
    प्रत्यागम true;
}

शून्य WIN_समुच्चयः_Cursor_Pos(पूर्णाङ्क x, पूर्णाङ्क y)
{
    // We need to jitter the value because otherwise Windows will occasionally inexplicably ignore the SetCursorPos() or SendInput()
    समुच्चयः_Cursor_Pos(x, y);
    समुच्चयः_Cursor_Pos(x + 1, y);
    समुच्चयः_Cursor_Pos(x, y);

    // Flush any mouse motion prior to or associated with this warp
#यदि_परिभाषितम् _MSC_VER // We explicitly want to use GetTickCount(), not GetTickCount64()
#निर्देशः warning(प्रक्षिप)
#निर्देशः warning(disable : 28159)
#यदि_अन्तः
    SDL_चरमः_warp_time = Get_Tick_गणनम्();
    यदि (!SDL_चरमः_warp_time) {
        SDL_चरमः_warp_time = 1;
    }
#यदि_परिभाषितम् _MSC_VER
#निर्देशः warning(निष्कासय)
#यदि_अन्तः
}

स्थिर bool WIN_WarpMouse(SDL_गवाक्षः *गवाक्षः, भिन्न x, भिन्न y)
{
    SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
    HWND hwnd = दत्त->hwnd;
    POINT pt;

    // Don't warp the mouse while we're doing a modal interaction
    यदि (दत्त->अन्तर्_title_click || दत्त->focus_click_pending) {
        प्रत्यागम true;
    }

    pt.x = (पूर्णाङ्क)SDL_roundf(x);
    pt.y = (पूर्णाङ्क)SDL_roundf(y);
    Client_गन्तव्यम्_Screen(hwnd, &pt);
    WIN_समुच्चयः_Cursor_Pos(pt.x, pt.y);

    // Send the exact mouse motion associated with this warp
    SDL_SendMouseMotion(0, गवाक्षः, SDL_GLOBAL_MOUSE_ID, false, x, y);
    प्रत्यागम true;
}

स्थिर bool WIN_WarpMouseGlobal(भिन्न x, भिन्न y)
{
    POINT pt;

    pt.x = (पूर्णाङ्क)SDL_roundf(x);
    pt.y = (पूर्णाङ्क)SDL_roundf(y);
    समुच्चयः_Cursor_Pos(pt.x, pt.y);
    प्रत्यागम true;
}

स्थिर bool WIN_समुच्चयः_Relative_Mouse_बहुलकम्(bool enabled)
{
    प्रत्यागम WIN_समुच्चयः_Raw_Mouse_Enabled(SDL_GetVideoDevice(), enabled);
}

स्थिर bool WIN_CaptureMouse(SDL_गवाक्षः *गवाक्षः)
{
    यदि (गवाक्षः) {
        SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
        समुच्चयः_Capture(दत्त->hwnd);
    } अन्यथा {
        SDL_गवाक्षः *focus_गवाक्षः_2 = SDL_GetMouseFocus();

        यदि (focus_गवाक्षः_2) {
            SDL_गवाक्षः_दत्त *दत्त = focus_गवाक्षः_2->आन्तरिकम्;
            यदि (!दत्त->mouse_tracked) {
                SDL_समुच्चयः_Mouse_Focus(रिक्त);
            }
        }
        ReleaseCapture();
    }

    प्रत्यागम true;
}

स्थिर SDL_MouseButtonFlags WIN_GetGlobalMouseState(भिन्न *x, भिन्न *y)
{
    SDL_MouseButtonFlags परिणाम = 0;
    POINT pt = { 0, 0 };
    bool swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;

    GetCursorPos(&pt);
    *x = (भिन्न)pt.x;
    *y = (भिन्न)pt.y;

    परिणाम |= Get_Async_कुञ्चिका_State(!swapButtons ? VK_LBUTTON : VK_RBUTTON) & 0x8000 ? SDL_BUTTON_LMASK : 0;
    परिणाम |= Get_Async_कुञ्चिका_State(!swapButtons ? VK_RBUTTON : VK_LBUTTON) & 0x8000 ? SDL_BUTTON_RMASK : 0;
    परिणाम |= Get_Async_कुञ्चिका_State(VK_MBUTTON) & 0x8000 ? SDL_BUTTON_MMASK : 0;
    परिणाम |= Get_Async_कुञ्चिका_State(VK_XBUTTON1) & 0x8000 ? SDL_BUTTON_X1_आवरणम् : 0;
    परिणाम |= Get_Async_कुञ्चिका_State(VK_XBUTTON2) & 0x8000 ? SDL_BUTTON_X2_आवरणम् : 0;

    प्रत्यागम परिणाम;
}

स्थिर शून्य WIN_ApplySystemScale(शून्य *आन्तरिकम्, Uint64 timestamp, SDL_गवाक्षः *गवाक्षः, SDL_MouseID mouseID, भिन्न *x, भिन्न *y)
{
    यदि (!आन्तरिकम्) {
        प्रत्यागम;
    }
    WIN_Mouse_दत्त *दत्त = (WIN_Mouse_दत्त *)आन्तरिकम्;

    SDL_VideoDisplay *display = गवाक्षः ? SDL_Get_Video_Display_For_गवाक्षः(गवाक्षः) : SDL_GetVideoDisplay(SDL_GetPrimaryDisplay());

    Sint64 ix = (Sint64)*x * 65536;
    Sint64 iy = (Sint64)*y * 65536;
    Uint32 dpi = display ? (Uint32)(display->content_scale * USER_DEFAULT_SCREEN_DPI) : USER_DEFAULT_SCREEN_DPI;

    यदि (!दत्त->enhanced) { // early return if flat scale
        dpi = दत्त->dpiscale * (दत्त->dpiaware ? dpi : USER_DEFAULT_SCREEN_DPI);
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

    Uint64 *xs = दत्त->xs;
    Uint64 *ys = दत्त->ys;
    Uint64 absx = SDL_abs(ix);
    Uint64 absy = SDL_abs(iy);
    Uint64 जवः = SDL_min(absx, absy) + (SDL_max(absx, absy) << 1); // super cursed approximation used by Windows
    यदि (जवः == 0) {
        प्रत्यागम;
    }

    पूर्णाङ्क i, j, k;
    प्रति (i = 1; i < 5; i++) {
        j = i;
        यदि (जवः < xs[j]) {
            भङ्ग;
        }
    }
    i -= 1;
    j -= 1;
    k = दत्त->चरमः_ग्रन्थिः;
    दत्त->चरमः_ग्रन्थिः = j;

    Uint32 denom = दत्त->dpidenom;
    Sint64 scale = 0;
    Sint64 xdiff = xs[j+1] - xs[j];
    Sint64 ydiff = ys[j+1] - ys[j];
    यदि (xdiff != 0) {
        Sint64 नतिः = ydiff / xdiff;
        Sint64 inter = नतिः * xs[i] - ys[i];
        scale += नतिः - inter / जवः;
    }

    यदि (j > k) {
        denom <<= 1;
        xdiff = xs[k+1] - xs[k];
        ydiff = ys[k+1] - ys[k];
        यदि (xdiff != 0) {
            Sint64 नतिः = ydiff / xdiff;
            Sint64 inter = नतिः * xs[k] - ys[k];
            scale += नतिः - inter / जवः;
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
    mouse->समुच्चयः_Relative_Mouse_बहुलकम् = WIN_समुच्चयः_Relative_Mouse_बहुलकम्;
    mouse->CaptureMouse = WIN_CaptureMouse;
    mouse->GetGlobalMouseState = WIN_GetGlobalMouseState;
    mouse->ApplySystemScale = WIN_ApplySystemScale;
    mouse->system_scale_दत्त = &WIN_system_scale_दत्त;

    SDL_समुच्चयः_Default_Cursor(WIN_CreateDefaultCursor());

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

स्थिर शून्य Read_Mouse_वक्रम्(पूर्णाङ्क v, Uint64 xs[5], Uint64 ys[5])
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
    यदि (Reg_Open_कुञ्चिका_Ex_W(HKEY_CURRENT_USER, L"Control Panel\\Mouse", 0, कुञ्चिका_READ, &open_handle) == ERROR_SUCCESS) {
        Reg_Query_मानम्_Ex_W(open_handle, L"SmoothMouseXCurve", रिक्त, रिक्त, (BYTE*)xbuff, &xsize);
        Reg_Query_मानम्_Ex_W(open_handle, L"SmoothMouseYCurve", रिक्त, रिक्त, (BYTE*)ybuff, &ysize);
        Reg_Close_कुञ्चिका(open_handle);
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
        mouse->system_scale_दत्त = &WIN_system_scale_दत्त;
    }

    // always reinitialize to valid defaults, whether fetch was successful or not.
    WIN_Mouse_दत्त *दत्त = &WIN_system_scale_दत्त;
    दत्त->residual[0] = 0;
    दत्त->residual[1] = 0;
    दत्त->dpiscale = 32;
    दत्त->dpidenom = (10 * (WIN_IsWindows8OrGreater() ? 120 : 150)) << 16;
    दत्त->dpiaware = WIN_Is_प्रत्येकम्_Monitor_V2_DPIAware(SDL_GetVideoDevice());
    दत्त->enhanced = false;

    पूर्णाङ्क v = 10;
    यदि (SystemParametersInfo(SPI_GETMOUSESPEED, 0, &v, 0)) {
        v = SDL_max(1, SDL_min(v, 20));
        दत्त->dpiscale = SDL_max(SDL_max(v, (v - 2) * 4), (v - 6) * 8);
    }

    पूर्णाङ्क params[3];
    यदि (SystemParametersInfo(SPI_GETMOUSE, 0, &params, 0)) {
        दत्त->enhanced = params[2] ? true : false;
        यदि (params[2]) {
            Read_Mouse_वक्रम्(v, दत्त->xs, दत्त->ys);
        }
    }
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_WINDOWS

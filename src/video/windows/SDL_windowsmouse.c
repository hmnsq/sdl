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
#అన్తర్భావ "SDL_internal.h"

#ఒకవేళ defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#అన్తర్భావ "SDL_windowsvideo.h"
#అన్తర్భావ "SDL_windowsevents.h"
#అన్తర్భావ "SDL_windowsrawinput.h"

#అన్తర్భావ "../SDL_video_c.h"
#అన్తర్భావ "../../events/SDL_mouse_c.h"
#అన్తర్భావ "../../joystick/usb_ids.h"
#అన్తర్భావ "../../core/windows/SDL_windows.h" // for checking windows version

#నిర్వచించు RIFF_FOURCC(c0, c1, c2, c3)                 \
    ((DWORD)(BYTE)(c0) | ((DWORD)(BYTE)(c1) << 8) | \
     ((DWORD)(BYTE)(c2) << 16) | ((DWORD)(BYTE)(c3) << 24))

#నిర్వచించు ANI_FLAG_ICON 0x1

#సూచన pack(నెట్టు, 1)

రకనిర్వచనం నిర్మాణం
{
    BYTE b_వెడల్పు;
    BYTE b_ఎత్తు;
    BYTE b_Color_లెక్క;
    BYTE bReserved;
    మాట xHotspot;
    మాట yHotspot;
    DWORD dw_Image_కొలత;
    DWORD dw_Image_స్థానభ్రంశం;
} CURSORICONFILEDIRENTRY;

రకనిర్వచనం నిర్మాణం
{
    మాట idReserved;
    మాట idType;
    మాట id_లెక్క;
} CURSORICONFILEDIR;

రకనిర్వచనం నిర్మాణం
{
    DWORD cbSizeof; // sizeof(ANIHEADER) = 36 bytes.
    DWORD చట్రాలు;   // Number of frames in the frame list.
    DWORD అడుగులు;    // Number of steps in the animation loop.
    DWORD వెడల్పు;    //వెడల్పు
    DWORD ఎత్తు;   //ఎత్తు
    DWORD bpp;      // bpp
    DWORD planes;   // Not used
    DWORD jif_రేటు;  // Default display rate, in jiffies (1/60s)
    DWORD fl;       // AF_ICON should be set. AF_SEQUENCE is optional
} ANIHEADER;

#సూచన pack(తీయి)

రకనిర్వచనం నిర్మాణం CachedCursor
{
    దశాంశం scale;
    HCURSOR cursor;
    నిర్మాణం CachedCursor *తదుపరి;
} CachedCursor;

నిర్మాణం SDL_Cursor_దత్తాంశం
{
    HCURSOR cursor;

    CachedCursor *cache;
    పూర్ణాంకం hot_x;
    పూర్ణాంకం hot_y;
    పూర్ణాంకం అంకె_చట్రాలు;
    SDL_Cursor_చట్రం_Info చట్రాలు[1];
};

రకనిర్వచనం నిర్మాణం
{
    Uint64 xs[5];
    Uint64 ys[5];
    Sint64 residual[2];
    Uint32 dpiscale;
    Uint32 dpidenom;
    పూర్ణాంకం చివరి_కణుపు;
    bool enhanced;
    bool dpiaware;
} WIN_Mouse_దత్తాంశం;

DWORD SDL_చివరి_warp_సమయం = 0;
HCURSOR SDL_cursor = ఖాళీ;
స్థిర SDL_Cursor *SDL_blank_cursor = ఖాళీ;
స్థిర WIN_Mouse_దత్తాంశం WIN_system_scale_దత్తాంశం;

స్థిర SDL_Cursor *WIN_Create_Cursor_And_దత్తాంశం(HCURSOR hcursor)
{
    ఒకవేళ (!hcursor) {
        తిరిగి ఖాళీ;
    }

    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, పరిమాణం(*cursor));
    ఒకవేళ (!cursor) {
        తిరిగి ఖాళీ;
    }

    SDL_Cursor_దత్తాంశం *దత్తాంశం = (SDL_Cursor_దత్తాంశం *)SDL_calloc(1, పరిమాణం(*దత్తాంశం));
    ఒకవేళ (!దత్తాంశం) {
        SDL_free(cursor);
        తిరిగి ఖాళీ;
    }

    దత్తాంశం->cursor = hcursor;
    cursor->అంతర్గత = దత్తాంశం;
    తిరిగి cursor;
}

స్థిర SDL_Cursor *WIN_Create_Animated_Cursor_And_దత్తాంశం(SDL_Cursor_చట్రం_Info *చట్రాలు, పూర్ణాంకం చట్రం_లెక్క, పూర్ణాంకం hot_x, పూర్ణాంకం hot_y)
{
    // Dynamically generate cursors at the appropriate DPI
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, పరిమాణం(*cursor));
    ఒకవేళ (!cursor) {
        తిరిగి ఖాళీ;
    }

    SDL_Cursor_దత్తాంశం *దత్తాంశం = (SDL_Cursor_దత్తాంశం *)SDL_calloc(1, పరిమాణం(*దత్తాంశం) + (పరిమాణం(SDL_Cursor_చట్రం_Info) * (చట్రం_లెక్క - 1)));
    ఒకవేళ (!దత్తాంశం) {
        SDL_free(cursor);
        తిరిగి ఖాళీ;
    }

    దత్తాంశం->hot_x = hot_x;
    దత్తాంశం->hot_y = hot_y;
    దత్తాంశం->అంకె_చట్రాలు = చట్రం_లెక్క;
    కొరకు (పూర్ణాంకం i = 0; i < చట్రం_లెక్క; ++i) {
        SDL_Surface *surface = చట్రాలు[i].surface;
        ఒకవేళ (surface->flags & SDL_SURFACE_PREALLOCATED) {
            surface = SDL_DuplicateSurface(surface);
            ఒకవేళ (!surface) {
                అయితే (i > 0) {
                    --i;
                    SDL_DestroySurface(దత్తాంశం->చట్రాలు[i].surface);
                }
                SDL_free(దత్తాంశం);
                SDL_free(cursor);
                తిరిగి ఖాళీ;
            }
        } లేకపోతే {
            ++surface->refcount;
        }
        దత్తాంశం->చట్రాలు[i].surface = surface;
        దత్తాంశం->చట్రాలు[i].duration = చట్రాలు[i].duration;
    }
    cursor->అంతర్గత = దత్తాంశం;
    తిరిగి cursor;
}

స్థిర bool Save_Chunk_కొలత(SDL_IOStream* dst, Sint64 స్థానభ్రంశం_2)
{
    Sint64 ఇక్కడ = SDL_TellIO(dst);
    ఒకవేళ (ఇక్కడ < 0) {
        తిరిగి false;
    }
    ఒకవేళ (SDL_SeekIO(dst, స్థానభ్రంశం_2, SDL_IO_SEEK_సమితి) < 0) {
        తిరిగి false;
    }

    DWORD కొలత = (DWORD)(ఇక్కడ - (స్థానభ్రంశం_2 + పరిమాణం(DWORD)));
    ఒకవేళ (!SDL_WriteU32LE(dst, కొలత)) {
        తిరిగి false;
    }
    తిరిగి SDL_SeekIO(dst, ఇక్కడ, SDL_IO_SEEK_సమితి);
}

స్థిర bool Fill_Icon_నమోదు(CURSORICONFILEDIRENTRY *నమోదు_2, SDL_Surface *surface, పూర్ణాంకం hot_x, పూర్ణాంకం hot_y, DWORD dw_Image_కొలత, DWORD dw_Image_స్థానభ్రంశం)
{
    ఒకవేళ (surface->props) {
        hot_x = (పూర్ణాంకం)SDL_Get_సంఖ్య_Property(surface->props, SDL_PROP_SURFACE_HOTSPOT_X_సంఖ్య, hot_x);
        hot_y = (పూర్ణాంకం)SDL_Get_సంఖ్య_Property(surface->props, SDL_PROP_SURFACE_HOTSPOT_Y_సంఖ్య, hot_y);
    }
    hot_x = SDL_clamp(hot_x, 0, surface->w - 1);
    hot_y = SDL_clamp(hot_y, 0, surface->h - 1);

    SDL_zerop(నమోదు_2);
    నమోదు_2->b_వెడల్పు = surface->w < 256 ? surface->w : 0;  // 0 means a width of 256
    నమోదు_2->b_ఎత్తు = surface->h < 256 ? surface->h : 0; // 0 means a height of 256
    నమోదు_2->xHotspot = hot_x;
    నమోదు_2->yHotspot = hot_y;
    నమోదు_2->dw_Image_కొలత = dw_Image_కొలత;
    నమోదు_2->dw_Image_స్థానభ్రంశం = dw_Image_స్థానభ్రంశం;
    తిరిగి true;
}

#నిర్వచితమైతే SAVE_ICON_PNG

స్థిర bool WriteIconSurface(SDL_IOStream *dst, SDL_Surface *surface)
{
    ఒకవేళ (!SDL_SavePNG_IO(surface, dst, false)) {
        తిరిగి false;
    }

    // Image data offsets must be WORD aligned
    Sint64 స్థానభ్రంశం_2 = SDL_TellIO(dst);
    ఒకవేళ (స్థానభ్రంశం_2 & 1) {
        ఒకవేళ (!SDL_WriteU8(dst, 0)) {
            తిరిగి false;
        }
    }
    తిరిగి true;
}

#లేకపోతే

/* For info on the expected mask format see:
 * https://devblogs.microsoft.com/oldnewthing/20101018-00/?p=12513
 */
స్థిర శూన్య *Create_Icon_ముసుగు(SDL_Surface *surface, size_t *ముసుగు_కొలత)
{
    Uint8 *dst;
    స్థిరరాశి పూర్ణాంకం w = (surface->w + 7) / 8;
    స్థిరరాశి పూర్ణాంకం pad = (((w) % 4) ? (4 - ((w) % 4)) : 0);
    స్థిరరాశి పూర్ణాంకం pitch = (w + pad);
    స్థిరరాశి size_t కొలత = pitch * surface->h;
    స్థిర స్థిరరాశి గుర్తులేని అక్షరం masks[] = { 0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1 };

    శూన్య *ముసుగు = SDL_malloc(కొలత);
    ఒకవేళ (!ముసుగు) {
        తిరిగి ఖాళీ;
    }

    dst = (Uint8 *)ముసుగు;

    // Make the mask completely transparent.
    SDL_memset(dst, 0xff, కొలత);
    కొరకు (పూర్ణాంకం y = surface->h - 1; y >= 0; --y, dst += pitch) {
        కొరకు (పూర్ణాంకం x = 0; x < surface->w; ++x) {
            Uint8 r, g, b, a;
            SDL_ReadSurfacePixel(surface, x, y, &r, &g, &b, &a);

            ఒకవేళ (a != 0) {
                // Reset bit of an opaque pixel.
                dst[x >> 3] &= ~masks[x & 7];
            }
        }
    }
    *ముసుగు_కొలత = కొలత;
    తిరిగి ముసుగు;
}

స్థిర bool WriteIconSurface(SDL_IOStream *dst, SDL_Surface *surface)
{
    SDL_Surface *తాత్కాలిక = ఖాళీ;

    ఒకవేళ (surface->format != SDL_PIXELFORMAT_ARGB8888) {
        తాత్కాలిక = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        ఒకవేళ (!తాత్కాలిక) {
            తిరిగి false;
        }
        surface = తాత్కాలిక;
    }

    // Cursor data is double height (DIB and mask), stored bottom-up
    bool ok = true;
    size_t ముసుగు_కొలత = 0;
    శూన్య *ముసుగు = Create_Icon_ముసుగు(surface, &ముసుగు_కొలత);
    ఒకవేళ (!ముసుగు) {
        ok = false;
        వెళ్ళు పూర్తి;
    }

    BITMAPINFOHEADER bmih;
    SDL_zero(bmih);
    DWORD అడ్డువరుస_కొలత = surface->w * 4;
    bmih.bi_కొలత = పరిమాణం(BITMAPINFOHEADER);
    bmih.bi_వెడల్పు = surface->w;
    bmih.bi_ఎత్తు = surface->h * 2;
    bmih.biPlanes = 1;
    bmih.bi_బిట్టు_లెక్క = 32;
    bmih.biCompression = BI_RGB;
    bmih.bi_కొలత_Image = (DWORD)(surface->h * అడ్డువరుస_కొలత + ముసుగు_కొలత);
    ok &= (SDL_WriteIO(dst, &bmih, పరిమాణం(bmih)) == పరిమాణం(bmih));

    స్థిరరాశి Uint8 *pix = surface->pixels;
    pix += (surface->h - 1) * surface->pitch;
    కొరకు (పూర్ణాంకం i = 0; i < surface->h; ++i) {
        ok &= (SDL_WriteIO(dst, pix, అడ్డువరుస_కొలత) == అడ్డువరుస_కొలత);
        pix -= surface->pitch;
    }
    ok &= (SDL_WriteIO(dst, ముసుగు, ముసుగు_కొలత) == ముసుగు_కొలత);

పూర్తి:
    SDL_free(ముసుగు);
    SDL_DestroySurface(తాత్కాలిక);
    తిరిగి ok;
}

#అయితే_ముగింపు // SAVE_ICON_PNG

స్థిర bool Write_Icon_చట్రం(SDL_IOStream *dst, SDL_Surface *surface, పూర్ణాంకం hot_x, పూర్ణాంకం hot_y, దశాంశం scale)
{
#నిర్వచితమైతే SAVE_గుణిజం_ICONS
    పూర్ణాంకం లెక్క = 0;
    SDL_Surface **surfaces = SDL_GetSurfaceImages(surface, &లెక్క);
    ఒకవేళ (!surfaces) {
        తిరిగి false;
    }
#లేకపోతే
    surface = SDL_GetSurfaceImage(surface, scale);
    ఒకవేళ (!surface) {
        తిరిగి false;
    }

    పూర్ణాంకం లెక్క = 1;
    SDL_Surface **surfaces = &surface;
#అయితే_ముగింపు

    // Raymond Chen has more insight into this format at:
    // https://devblogs.microsoft.com/oldnewthing/20101018-00/?p=12513
    bool ok = true;
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('i', 'c', 'o', 'n'));
    Sint64 icon_కొలత_స్థానభ్రంశం = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    Sint64 పునాది_స్థానభ్రంశం_2 = icon_కొలత_స్థానభ్రంశం + పరిమాణం(DWORD);

    CURSORICONFILEDIR dir;
    dir.idReserved = 0;
    dir.idType = 2; // Cursor
    dir.id_లెక్క = లెక్క;
    ok &= (SDL_WriteIO(dst, &dir, పరిమాణం(dir)) == పరిమాణం(dir));

    DWORD entries_కొలత = లెక్క * పరిమాణం(CURSORICONFILEDIRENTRY);
    CURSORICONFILEDIRENTRY *entries = (CURSORICONFILEDIRENTRY *)SDL_malloc(entries_కొలత);
    ఒకవేళ (!entries) {
        ok = false;
        వెళ్ళు పూర్తి;
    }
    ok &= (SDL_WriteIO(dst, entries, entries_కొలత) == entries_కొలత);

    Sint64 image_స్థానభ్రంశం_2 = SDL_TellIO(dst);
    కొరకు (పూర్ణాంకం i = 0; i < లెక్క; ++i) {
        ok &= WriteIconSurface(dst, surfaces[i]);

        Sint64 తదుపరి_స్థానభ్రంశం = SDL_TellIO(dst);
        DWORD dw_Image_కొలత = (DWORD)(తదుపరి_స్థానభ్రంశం - image_స్థానభ్రంశం_2);
        DWORD dw_Image_స్థానభ్రంశం = (DWORD)(image_స్థానభ్రంశం_2 - పునాది_స్థానభ్రంశం_2);

        ok &= Fill_Icon_నమోదు(&entries[i], surfaces[i], hot_x, hot_y, dw_Image_కొలత, dw_Image_స్థానభ్రంశం);

        image_స్థానభ్రంశం_2 = తదుపరి_స్థానభ్రంశం;
    }

    // Now that we have the icon entries filled out, rewrite them
    ok &= (SDL_SeekIO(dst, పునాది_స్థానభ్రంశం_2 + పరిమాణం(dir), SDL_IO_SEEK_సమితి) >= 0);
    ok &= (SDL_WriteIO(dst, entries, entries_కొలత) == entries_కొలత);
    ok &= (SDL_SeekIO(dst, image_స్థానభ్రంశం_2, SDL_IO_SEEK_సమితి) >= 0);
    SDL_free(entries);

    ok &= Save_Chunk_కొలత(dst, icon_కొలత_స్థానభ్రంశం);

పూర్తి:
#నిర్వచితమైతే SAVE_గుణిజం_ICONS
    SDL_free(surfaces);
#లేకపోతే
    SDL_DestroySurface(surface);
#అయితే_ముగింపు
    తిరిగి ok;
}

/* Windows doesn't have an API to easily create animated cursors from a sequence of images,
 * so we have to build an animated cursor resource file in memory and load it.
 */
స్థిర HCURSOR WIN_Create_Animated_Cursor_అంతర్గత(SDL_Cursor_చట్రం_Info *చట్రాలు, పూర్ణాంకం చట్రం_లెక్క, పూర్ణాంకం hot_x, పూర్ణాంకం hot_y, దశాంశం scale)
{
    HCURSOR hcursor = ఖాళీ;
    SDL_IOStream *dst = SDL_IOFromDynamicMem();
    ఒకవేళ (!dst) {
        తిరిగి ఖాళీ;
    }

    పూర్ణాంకం w = (పూర్ణాంకం)SDL_roundf(చట్రాలు[0].surface->w * scale);
    పూర్ణాంకం h = (పూర్ణాంకం)SDL_roundf(చట్రాలు[0].surface->h * scale);

    bool ok = true;
    // RIFF header
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('R', 'I', 'F', 'F'));
    Sint64 riff_కొలత_స్థానభ్రంశం = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('A', 'C', 'O', 'N'));

    // anih header chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('a', 'n', 'i', 'h'));
    ok &= SDL_WriteU32LE(dst, పరిమాణం(ANIHEADER));

    ANIHEADER anih;
    SDL_zero(anih);
    anih.cbSizeof = పరిమాణం(anih);
    anih.చట్రాలు = చట్రం_లెక్క;
    anih.అడుగులు = చట్రం_లెక్క;
    anih.jif_రేటు = 1;
    anih.fl = ANI_FLAG_ICON;
    ok &= (SDL_WriteIO(dst, &anih, పరిమాణం(anih)) == పరిమాణం(anih));

    // Rate chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('r', 'a', 't', 'e'));
    ok &= SDL_WriteU32LE(dst, పరిమాణం(DWORD) * చట్రం_లెక్క);
    కొరకు (పూర్ణాంకం i = 0; i < చట్రం_లెక్క; ++i) {
        // Animated Win32 cursors are in jiffy units, and one jiffy is 1/60 of a second.
        స్థిరరాశి ద్విగుణ WIN32_JIFFY = 1000.0 / 60.0;
        DWORD duration = (చట్రాలు[i].duration ? SDL_lround(చట్రాలు[i].duration / WIN32_JIFFY) : 0xFFFFFFFF);
        ok &= SDL_WriteU32LE(dst, duration);
    }

    // Frame list
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('L', 'I', 'S', 'T'));
    Sint64 చట్రం_list_కొలత_స్థానభ్రంశం = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('f', 'r', 'a', 'm'));

    కొరకు (పూర్ణాంకం i = 0; i < చట్రం_లెక్క; ++i) {
        ok &= Write_Icon_చట్రం(dst, చట్రాలు[i].surface, hot_x, hot_y, scale);
    }
    ok &= Save_Chunk_కొలత(dst, చట్రం_list_కొలత_స్థానభ్రంశం);

    // All done!
    ok &= Save_Chunk_కొలత(dst, riff_కొలత_స్థానభ్రంశం);
    ఒకవేళ (!ok) {
        // The error has been set above
        వెళ్ళు పూర్తి;
    }

    BYTE *mem = (BYTE *)SDL_Get_సూచిక_Property(SDL_GetIOProperties(dst), SDL_PROP_IOSTREAM_DYNAMIC_జ్ఞాపకం_సూచిక, ఖాళీ);
    DWORD కొలత = (DWORD)SDL_GetIOSize(dst);
    hcursor = (HCURSOR)CreateIconFromResourceEx(mem, కొలత, FALSE, 0x00030000, w, h, 0);
    ఒకవేళ (!hcursor) {
        SDL_సమితి_Error("CreateIconFromResource failed");
    }

పూర్తి:
    SDL_CloseIO(dst);

    తిరిగి hcursor;
}

స్థిర SDL_Cursor *WIN_CreateCursor(SDL_Surface *surface, పూర్ణాంకం hot_x, పూర్ణాంకం hot_y)
{
    SDL_Cursor_చట్రం_Info చట్రం = { surface, 0 };
    తిరిగి WIN_Create_Animated_Cursor_And_దత్తాంశం(&చట్రం, 1, hot_x, hot_y);
}

స్థిర SDL_Cursor *WIN_CreateAnimatedCursor(SDL_Cursor_చట్రం_Info *చట్రాలు, పూర్ణాంకం చట్రం_లెక్క, పూర్ణాంకం hot_x, పూర్ణాంకం hot_y)
{
    తిరిగి WIN_Create_Animated_Cursor_And_దత్తాంశం(చట్రాలు, చట్రం_లెక్క, hot_x, hot_y);
}

స్థిర SDL_Cursor *WIN_CreateBlankCursor(శూన్య)
{
    SDL_Cursor *cursor = ఖాళీ;
    SDL_Surface *surface = SDL_CreateSurfaceZeroed(32, 32, SDL_PIXELFORMAT_ARGB8888);
    ఒకవేళ (surface) {
        cursor = WIN_CreateCursor(surface, 0, 0);
        SDL_DestroySurface(surface);
    }
    తిరిగి cursor;
}

స్థిర SDL_Cursor *WIN_CreateSystemCursor(SDL_SystemCursor id)
{
    LPCTSTR name;

    ఎంపిక (id) {
    అప్రమేయ:
        SDL_assert(!"Unknown system cursor ID");
        తిరిగి ఖాళీ;
    స్థితి SDL_SYSTEM_CURSOR_DEFAULT:
        name = IDC_ARROW;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_పాఠ్యం:
    స్థితి SDL_SYSTEM_CURSOR_VERTICAL_పాఠ్యం:
        name = IDC_IBEAM;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_WAIT:
        name = IDC_WAIT;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_CROSSHAIR:
    స్థితి SDL_SYSTEM_CURSOR_CELL:
        name = IDC_CROSS;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_పురోగతి:
        name = IDC_APPSTARTING;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_NWSE_RESIZE:
    స్థితి SDL_SYSTEM_CURSOR_NW_RESIZE:
    స్థితి SDL_SYSTEM_CURSOR_SE_RESIZE:
        name = IDC_SIZENWSE;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_NESW_RESIZE:
    స్థితి SDL_SYSTEM_CURSOR_NE_RESIZE:
    స్థితి SDL_SYSTEM_CURSOR_SW_RESIZE:
        name = IDC_SIZENESW;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_EW_RESIZE:
    స్థితి SDL_SYSTEM_CURSOR_E_RESIZE:
    స్థితి SDL_SYSTEM_CURSOR_W_RESIZE:
    స్థితి SDL_SYSTEM_CURSOR_నిలువు_RESIZE:
        name = IDC_SIZEWE;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_NS_RESIZE:
    స్థితి SDL_SYSTEM_CURSOR_N_RESIZE:
    స్థితి SDL_SYSTEM_CURSOR_S_RESIZE:
    స్థితి SDL_SYSTEM_CURSOR_అడ్డువరుస_RESIZE:
        name = IDC_SIZENS;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_MOVE:
    స్థితి SDL_SYSTEM_CURSOR_ALL_SCROLL:
        name = IDC_SIZEALL;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_NOT_ALLOWED:
    స్థితి SDL_SYSTEM_CURSOR_NO_DROP:
        name = IDC_NO;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_సూచిక:
    స్థితి SDL_SYSTEM_CURSOR_CONTEXT_MENU:
    స్థితి SDL_SYSTEM_CURSOR_ALIAS:
    స్థితి SDL_SYSTEM_CURSOR_COPY:
    స్థితి SDL_SYSTEM_CURSOR_GRAB:
    స్థితి SDL_SYSTEM_CURSOR_GRABBING:
    స్థితి SDL_SYSTEM_CURSOR_ZOOM_లోపల:
    స్థితి SDL_SYSTEM_CURSOR_ZOOM_బహిర్గతం:
        name = IDC_HAND;
        ఆపు;
    స్థితి SDL_SYSTEM_CURSOR_HELP:
        name = IDC_HELP;
        ఆపు;
    }
    తిరిగి WIN_Create_Cursor_And_దత్తాంశం(ఎక్కించు_Cursor(ఖాళీ, name));
}

స్థిర SDL_Cursor *WIN_CreateDefaultCursor(శూన్య)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    తిరిగి WIN_CreateSystemCursor(id);
}

స్థిర శూన్య WIN_FreeCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_దత్తాంశం *దత్తాంశం = cursor->అంతర్గత;

    కొరకు (పూర్ణాంకం i = 0; i < దత్తాంశం->అంకె_చట్రాలు; ++i) {
        SDL_DestroySurface(దత్తాంశం->చట్రాలు[i].surface);
    }
    అయితే (దత్తాంశం->cache) {
        CachedCursor *నమోదు_2 = దత్తాంశం->cache;
        దత్తాంశం->cache = నమోదు_2->తదుపరి;
        ఒకవేళ (నమోదు_2->cursor) {
            DestroyCursor(నమోదు_2->cursor);
        }
        SDL_free(నమోదు_2);
    }
    ఒకవేళ (దత్తాంశం->cursor) {
        DestroyCursor(దత్తాంశం->cursor);
    }
    SDL_free(దత్తాంశం);
    SDL_free(cursor);
}

స్థిర HCURSOR GetCachedCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_దత్తాంశం *దత్తాంశం = cursor->అంతర్గత;

    దశాంశం scale = 1.0f;
    ఒకవేళ (SDL_GetHintBoolean(SDL_HINT_MOUSE_DPI_SCALE_CURSORS, false)) {
        scale = SDL_GetDisplayContentScale(SDL_Get_Display_For_కిటికీ(SDL_GetMouseFocus()));
        ఒకవేళ (scale == 0.0f) {
            scale = 1.0f;
        }
    }
    కొరకు (CachedCursor *నమోదు_2 = దత్తాంశం->cache; నమోదు_2; నమోదు_2 = నమోదు_2->తదుపరి) {
        ఒకవేళ (scale == నమోదు_2->scale) {
            తిరిగి నమోదు_2->cursor;
        }
    }

    // Need to create a cursor for this content scale
    HCURSOR hcursor = WIN_Create_Animated_Cursor_అంతర్గత(దత్తాంశం->చట్రాలు, దత్తాంశం->అంకె_చట్రాలు, దత్తాంశం->hot_x, దత్తాంశం->hot_y, scale);
    ఒకవేళ (!hcursor) {
        తిరిగి ఖాళీ;
    }

    CachedCursor *నమోదు_2 = (CachedCursor *)SDL_calloc(1, పరిమాణం(*నమోదు_2));
    ఒకవేళ (!నమోదు_2) {
        DestroyCursor(hcursor);
        తిరిగి ఖాళీ;
    }
    నమోదు_2->cursor = hcursor;
    నమోదు_2->scale = scale;
    నమోదు_2->తదుపరి = దత్తాంశం->cache;
    దత్తాంశం->cache = నమోదు_2;

    తిరిగి hcursor;
}

స్థిర bool WIN_ShowCursor(SDL_Cursor *cursor)
{
    ఒకవేళ (!cursor) {
        ఒకవేళ (GetSystemMetrics(SM_REMOTESESSION)) {
            // Use a blank cursor so we continue to get relative motion over RDP
            cursor = SDL_blank_cursor;
        }
    }
    ఒకవేళ (cursor) {
        SDL_Cursor_దత్తాంశం *దత్తాంశం = cursor->అంతర్గత;
        ఒకవేళ (దత్తాంశం->అంకె_చట్రాలు > 0) {
            SDL_cursor = GetCachedCursor(cursor);
        } లేకపోతే {
            SDL_cursor = దత్తాంశం->cursor;
        }
    } లేకపోతే {
        SDL_cursor = ఖాళీ;
    }
    ఒకవేళ (SDL_GetMouseFocus() != ఖాళీ) {
        సమితి_Cursor(SDL_cursor);
    }
    తిరిగి true;
}

శూన్య WIN_సమితి_Cursor_Pos(పూర్ణాంకం x, పూర్ణాంకం y)
{
    // We need to jitter the value because otherwise Windows will occasionally inexplicably ignore the SetCursorPos() or SendInput()
    సమితి_Cursor_Pos(x, y);
    సమితి_Cursor_Pos(x + 1, y);
    సమితి_Cursor_Pos(x, y);

    // Flush any mouse motion prior to or associated with this warp
#నిర్వచితమైతే _MSC_VER // We explicitly want to use GetTickCount(), not GetTickCount64()
#సూచన warning(నెట్టు)
#సూచన warning(disable : 28159)
#అయితే_ముగింపు
    SDL_చివరి_warp_సమయం = Get_Tick_లెక్క();
    ఒకవేళ (!SDL_చివరి_warp_సమయం) {
        SDL_చివరి_warp_సమయం = 1;
    }
#నిర్వచితమైతే _MSC_VER
#సూచన warning(తీయి)
#అయితే_ముగింపు
}

స్థిర bool WIN_WarpMouse(SDL_కిటికీ *కిటికీ, దశాంశం x, దశాంశం y)
{
    SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
    HWND hwnd = దత్తాంశం->hwnd;
    బిందువు_2 pt;

    // Don't warp the mouse while we're doing a modal interaction
    ఒకవేళ (దత్తాంశం->లోపల_title_click || దత్తాంశం->focus_click_pending) {
        తిరిగి true;
    }

    pt.x = (పూర్ణాంకం)SDL_roundf(x);
    pt.y = (పూర్ణాంకం)SDL_roundf(y);
    Client_గమ్యం_Screen(hwnd, &pt);
    WIN_సమితి_Cursor_Pos(pt.x, pt.y);

    // Send the exact mouse motion associated with this warp
    SDL_SendMouseMotion(0, కిటికీ, SDL_GLOBAL_MOUSE_ID, false, x, y);
    తిరిగి true;
}

స్థిర bool WIN_WarpMouseGlobal(దశాంశం x, దశాంశం y)
{
    బిందువు_2 pt;

    pt.x = (పూర్ణాంకం)SDL_roundf(x);
    pt.y = (పూర్ణాంకం)SDL_roundf(y);
    సమితి_Cursor_Pos(pt.x, pt.y);
    తిరిగి true;
}

స్థిర bool WIN_సమితి_Relative_Mouse_బహుళకం(bool enabled)
{
    తిరిగి WIN_సమితి_Raw_Mouse_Enabled(SDL_GetVideoDevice(), enabled);
}

స్థిర bool WIN_CaptureMouse(SDL_కిటికీ *కిటికీ)
{
    ఒకవేళ (కిటికీ) {
        SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
        సమితి_Capture(దత్తాంశం->hwnd);
    } లేకపోతే {
        SDL_కిటికీ *focus_కిటికీ_2 = SDL_GetMouseFocus();

        ఒకవేళ (focus_కిటికీ_2) {
            SDL_కిటికీ_దత్తాంశం *దత్తాంశం = focus_కిటికీ_2->అంతర్గత;
            ఒకవేళ (!దత్తాంశం->mouse_tracked) {
                SDL_సమితి_Mouse_Focus(ఖాళీ);
            }
        }
        ReleaseCapture();
    }

    తిరిగి true;
}

స్థిర SDL_MouseButtonFlags WIN_GetGlobalMouseState(దశాంశం *x, దశాంశం *y)
{
    SDL_MouseButtonFlags ఫలితం = 0;
    బిందువు_2 pt = { 0, 0 };
    bool మార్పిడి_Buttons = GetSystemMetrics(SM_SWAPBUTTON) != 0;

    GetCursorPos(&pt);
    *x = (దశాంశం)pt.x;
    *y = (దశాంశం)pt.y;

    ఫలితం |= Get_Async_కీలకం_State(!మార్పిడి_Buttons ? VK_LBUTTON : VK_RBUTTON) & 0x8000 ? SDL_BUTTON_LMASK : 0;
    ఫలితం |= Get_Async_కీలకం_State(!మార్పిడి_Buttons ? VK_RBUTTON : VK_LBUTTON) & 0x8000 ? SDL_BUTTON_RMASK : 0;
    ఫలితం |= Get_Async_కీలకం_State(VK_MBUTTON) & 0x8000 ? SDL_BUTTON_MMASK : 0;
    ఫలితం |= Get_Async_కీలకం_State(VK_XBUTTON1) & 0x8000 ? SDL_BUTTON_X1_ముసుగు : 0;
    ఫలితం |= Get_Async_కీలకం_State(VK_XBUTTON2) & 0x8000 ? SDL_BUTTON_X2_ముసుగు : 0;

    తిరిగి ఫలితం;
}

స్థిర శూన్య WIN_ApplySystemScale(శూన్య *అంతర్గత, Uint64 timestamp, SDL_కిటికీ *కిటికీ, SDL_MouseID mouseID, దశాంశం *x, దశాంశం *y)
{
    ఒకవేళ (!అంతర్గత) {
        తిరిగి;
    }
    WIN_Mouse_దత్తాంశం *దత్తాంశం = (WIN_Mouse_దత్తాంశం *)అంతర్గత;

    SDL_VideoDisplay *display = కిటికీ ? SDL_Get_Video_Display_For_కిటికీ(కిటికీ) : SDL_GetVideoDisplay(SDL_GetPrimaryDisplay());

    Sint64 ix = (Sint64)*x * 65536;
    Sint64 iy = (Sint64)*y * 65536;
    Uint32 dpi = display ? (Uint32)(display->content_scale * USER_DEFAULT_SCREEN_DPI) : USER_DEFAULT_SCREEN_DPI;

    ఒకవేళ (!దత్తాంశం->enhanced) { // early return if flat scale
        dpi = దత్తాంశం->dpiscale * (దత్తాంశం->dpiaware ? dpi : USER_DEFAULT_SCREEN_DPI);
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
        *x = (దశాంశం)ix / 65536.0f;
        *y = (దశాంశం)iy / 65536.0f;
        తిరిగి;
    }

    Uint64 *xs = దత్తాంశం->xs;
    Uint64 *ys = దత్తాంశం->ys;
    Uint64 absx = SDL_abs(ix);
    Uint64 absy = SDL_abs(iy);
    Uint64 వేగం = SDL_min(absx, absy) + (SDL_max(absx, absy) << 1); // super cursed approximation used by Windows
    ఒకవేళ (వేగం == 0) {
        తిరిగి;
    }

    పూర్ణాంకం i, j, k;
    కొరకు (i = 1; i < 5; i++) {
        j = i;
        ఒకవేళ (వేగం < xs[j]) {
            ఆపు;
        }
    }
    i -= 1;
    j -= 1;
    k = దత్తాంశం->చివరి_కణుపు;
    దత్తాంశం->చివరి_కణుపు = j;

    Uint32 denom = దత్తాంశం->dpidenom;
    Sint64 scale = 0;
    Sint64 xdiff = xs[j+1] - xs[j];
    Sint64 ydiff = ys[j+1] - ys[j];
    ఒకవేళ (xdiff != 0) {
        Sint64 వాలు = ydiff / xdiff;
        Sint64 inter = వాలు * xs[i] - ys[i];
        scale += వాలు - inter / వేగం;
    }

    ఒకవేళ (j > k) {
        denom <<= 1;
        xdiff = xs[k+1] - xs[k];
        ydiff = ys[k+1] - ys[k];
        ఒకవేళ (xdiff != 0) {
            Sint64 వాలు = ydiff / xdiff;
            Sint64 inter = వాలు * xs[k] - ys[k];
            scale += వాలు - inter / వేగం;
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
    *x = (దశాంశం)ix / 65536.0f;
    *y = (దశాంశం)iy / 65536.0f;
}

శూన్య WIN_InitMouse(SDL_VideoDevice *_this)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    mouse->CreateCursor = WIN_CreateCursor;
    mouse->CreateAnimatedCursor = WIN_CreateAnimatedCursor;
    mouse->CreateSystemCursor = WIN_CreateSystemCursor;
    mouse->ShowCursor = WIN_ShowCursor;
    mouse->FreeCursor = WIN_FreeCursor;
    mouse->WarpMouse = WIN_WarpMouse;
    mouse->WarpMouseGlobal = WIN_WarpMouseGlobal;
    mouse->సమితి_Relative_Mouse_బహుళకం = WIN_సమితి_Relative_Mouse_బహుళకం;
    mouse->CaptureMouse = WIN_CaptureMouse;
    mouse->GetGlobalMouseState = WIN_GetGlobalMouseState;
    mouse->ApplySystemScale = WIN_ApplySystemScale;
    mouse->system_scale_దత్తాంశం = &WIN_system_scale_దత్తాంశం;

    SDL_సమితి_Default_Cursor(WIN_CreateDefaultCursor());

    SDL_blank_cursor = WIN_CreateBlankCursor();

    WIN_UpdateMouseSystemScale();
}

శూన్య WIN_QuitMouse(SDL_VideoDevice *_this)
{
    ఒకవేళ (SDL_blank_cursor) {
        WIN_FreeCursor(SDL_blank_cursor);
        SDL_blank_cursor = ఖాళీ;
    }
}

స్థిర శూన్య Read_Mouse_వక్రం(పూర్ణాంకం v, Uint64 xs[5], Uint64 ys[5])
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
    DWORD xsize = పరిమాణం(xbuff);
    DWORD ysize = పరిమాణం(ybuff);
    HKEY open_handle;
    ఒకవేళ (Reg_Open_కీలకం_Ex_W(HKEY_CURRENT_USER, L"Control Panel\\Mouse", 0, కీలకం_READ, &open_handle) == ERROR_SUCCESS) {
        Reg_Query_విలువ_Ex_W(open_handle, L"SmoothMouseXCurve", ఖాళీ, ఖాళీ, (BYTE*)xbuff, &xsize);
        Reg_Query_విలువ_Ex_W(open_handle, L"SmoothMouseYCurve", ఖాళీ, ఖాళీ, (BYTE*)ybuff, &ysize);
        Reg_Close_కీలకం(open_handle);
    }
    xs[0] = 0; // first node must always be origin
    ys[0] = 0; // first node must always be origin
    పూర్ణాంకం i;
    కొరకు (i = 1; i < 5; i++) {
        xs[i] = (7 * (Uint64)xbuff[i * 2]);
        ys[i] = (v * (Uint64)ybuff[i * 2]) << 17;
    }
}

శూన్య WIN_UpdateMouseSystemScale(శూన్య)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    ఒకవేళ (mouse->ApplySystemScale == WIN_ApplySystemScale) {
        mouse->system_scale_దత్తాంశం = &WIN_system_scale_దత్తాంశం;
    }

    // always reinitialize to valid defaults, whether fetch was successful or not.
    WIN_Mouse_దత్తాంశం *దత్తాంశం = &WIN_system_scale_దత్తాంశం;
    దత్తాంశం->residual[0] = 0;
    దత్తాంశం->residual[1] = 0;
    దత్తాంశం->dpiscale = 32;
    దత్తాంశం->dpidenom = (10 * (WIN_IsWindows8OrGreater() ? 120 : 150)) << 16;
    దత్తాంశం->dpiaware = WIN_Is_చొప్పున_Monitor_V2_DPIAware(SDL_GetVideoDevice());
    దత్తాంశం->enhanced = false;

    పూర్ణాంకం v = 10;
    ఒకవేళ (SystemParametersInfo(SPI_GETMOUSESPEED, 0, &v, 0)) {
        v = SDL_max(1, SDL_min(v, 20));
        దత్తాంశం->dpiscale = SDL_max(SDL_max(v, (v - 2) * 4), (v - 6) * 8);
    }

    పూర్ణాంకం params[3];
    ఒకవేళ (SystemParametersInfo(SPI_GETMOUSE, 0, &params, 0)) {
        దత్తాంశం->enhanced = params[2] ? true : false;
        ఒకవేళ (params[2]) {
            Read_Mouse_వక్రం(v, దత్తాంశం->xs, దత్తాంశం->ys);
        }
    }
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_WINDOWS

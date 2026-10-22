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

#تعریف_کرو RIFF_FOURCC(c0, c1, c2, c3)                 \
    ((DWORD)(BYTE)(c0) | ((DWORD)(BYTE)(c1) << 8) | \
     ((DWORD)(BYTE)(c2) << 16) | ((DWORD)(BYTE)(c3) << 24))

#تعریف_کرو ANI_FLAG_ICON 0x1

#ہدایت pack(ڈالو, 1)

تعريفنوع بنية
{
    BYTE b_چوڑائی;
    BYTE b_اچائی;
    BYTE b_Color_گنتی;
    BYTE bReserved;
    لفظ xHotspot;
    لفظ yHotspot;
    DWORD dw_Image_ناپ;
    DWORD dw_Image_وتھ;
} CURSORICONFILEDIRENTRY;

تعريفنوع بنية
{
    لفظ idReserved;
    لفظ idType;
    لفظ id_گنتی;
} CURSORICONFILEDIR;

تعريفنوع بنية
{
    DWORD cbSizeof; // sizeof(ANIHEADER) = 36 bytes.
    DWORD چوکھٹے;   // Number of frames in the frame list.
    DWORD قدماں;    // Number of steps in the animation loop.
    DWORD چوڑائی;    //چوڑائی
    DWORD اچائی;   //اچائی
    DWORD bpp;      // bpp
    DWORD planes;   // Not used
    DWORD jif_شرح;  // Default display rate, in jiffies (1/60s)
    DWORD fl;       // AF_ICON should be set. AF_SEQUENCE is optional
} ANIHEADER;

#ہدایت pack(نکالو)

تعريفنوع بنية CachedCursor
{
    عائم scale;
    HCURSOR cursor;
    بنية CachedCursor *اگلا;
} CachedCursor;

بنية SDL_Cursor_انکڑے
{
    HCURSOR cursor;

    CachedCursor *cache;
    صحيح hot_x;
    صحيح hot_y;
    صحيح عدد_چوکھٹے;
    SDL_Cursor_چوکھٹا_Info چوکھٹے[1];
};

تعريفنوع بنية
{
    Uint64 xs[5];
    Uint64 ys[5];
    Sint64 residual[2];
    Uint32 dpiscale;
    Uint32 dpidenom;
    صحيح آخری_گرہ;
    bool enhanced;
    bool dpiaware;
} WIN_Mouse_انکڑے;

DWORD SDL_آخری_warp_ویلا = 0;
HCURSOR SDL_cursor = عدم;
ساكن SDL_Cursor *SDL_blank_cursor = عدم;
ساكن WIN_Mouse_انکڑے WIN_system_scale_انکڑے;

ساكن SDL_Cursor *WIN_Create_Cursor_And_انکڑے(HCURSOR hcursor)
{
    إذا (!hcursor) {
        أرجع عدم;
    }

    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, حجم(*cursor));
    إذا (!cursor) {
        أرجع عدم;
    }

    SDL_Cursor_انکڑے *انکڑے = (SDL_Cursor_انکڑے *)SDL_calloc(1, حجم(*انکڑے));
    إذا (!انکڑے) {
        SDL_free(cursor);
        أرجع عدم;
    }

    انکڑے->cursor = hcursor;
    cursor->اندرونی = انکڑے;
    أرجع cursor;
}

ساكن SDL_Cursor *WIN_Create_Animated_Cursor_And_انکڑے(SDL_Cursor_چوکھٹا_Info *چوکھٹے, صحيح چوکھٹا_گنتی, صحيح hot_x, صحيح hot_y)
{
    // Dynamically generate cursors at the appropriate DPI
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, حجم(*cursor));
    إذا (!cursor) {
        أرجع عدم;
    }

    SDL_Cursor_انکڑے *انکڑے = (SDL_Cursor_انکڑے *)SDL_calloc(1, حجم(*انکڑے) + (حجم(SDL_Cursor_چوکھٹا_Info) * (چوکھٹا_گنتی - 1)));
    إذا (!انکڑے) {
        SDL_free(cursor);
        أرجع عدم;
    }

    انکڑے->hot_x = hot_x;
    انکڑے->hot_y = hot_y;
    انکڑے->عدد_چوکھٹے = چوکھٹا_گنتی;
    لكل (صحيح i = 0; i < چوکھٹا_گنتی; ++i) {
        SDL_Surface *surface = چوکھٹے[i].surface;
        إذا (surface->flags & SDL_SURFACE_PREALLOCATED) {
            surface = SDL_DuplicateSurface(surface);
            إذا (!surface) {
                طالما (i > 0) {
                    --i;
                    SDL_DestroySurface(انکڑے->چوکھٹے[i].surface);
                }
                SDL_free(انکڑے);
                SDL_free(cursor);
                أرجع عدم;
            }
        } وإلا {
            ++surface->refcount;
        }
        انکڑے->چوکھٹے[i].surface = surface;
        انکڑے->چوکھٹے[i].duration = چوکھٹے[i].duration;
    }
    cursor->اندرونی = انکڑے;
    أرجع cursor;
}

ساكن bool Save_Chunk_ناپ(SDL_IOStream* dst, Sint64 وتھ_2)
{
    Sint64 ایتھے = SDL_TellIO(dst);
    إذا (ایتھے < 0) {
        أرجع false;
    }
    إذا (SDL_SeekIO(dst, وتھ_2, SDL_IO_SEEK_سیٹ) < 0) {
        أرجع false;
    }

    DWORD ناپ = (DWORD)(ایتھے - (وتھ_2 + حجم(DWORD)));
    إذا (!SDL_WriteU32LE(dst, ناپ)) {
        أرجع false;
    }
    أرجع SDL_SeekIO(dst, ایتھے, SDL_IO_SEEK_سیٹ);
}

ساكن bool Fill_Icon_اندراج(CURSORICONFILEDIRENTRY *اندراج, SDL_Surface *surface, صحيح hot_x, صحيح hot_y, DWORD dw_Image_ناپ, DWORD dw_Image_وتھ)
{
    إذا (surface->props) {
        hot_x = (صحيح)SDL_Get_نمبر_Property(surface->props, SDL_PROP_SURFACE_HOTSPOT_X_نمبر, hot_x);
        hot_y = (صحيح)SDL_Get_نمبر_Property(surface->props, SDL_PROP_SURFACE_HOTSPOT_Y_نمبر, hot_y);
    }
    hot_x = SDL_clamp(hot_x, 0, surface->w - 1);
    hot_y = SDL_clamp(hot_y, 0, surface->h - 1);

    SDL_zerop(اندراج);
    اندراج->b_چوڑائی = surface->w < 256 ? surface->w : 0;  // 0 means a width of 256
    اندراج->b_اچائی = surface->h < 256 ? surface->h : 0; // 0 means a height of 256
    اندراج->xHotspot = hot_x;
    اندراج->yHotspot = hot_y;
    اندراج->dw_Image_ناپ = dw_Image_ناپ;
    اندراج->dw_Image_وتھ = dw_Image_وتھ;
    أرجع true;
}

#جے_تعریف_شدہ SAVE_ICON_PNG

ساكن bool WriteIconSurface(SDL_IOStream *dst, SDL_Surface *surface)
{
    إذا (!SDL_SavePNG_IO(surface, dst, false)) {
        أرجع false;
    }

    // Image data offsets must be WORD aligned
    Sint64 وتھ_2 = SDL_TellIO(dst);
    إذا (وتھ_2 & 1) {
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
ساكن فراغ *Create_Icon_نقاب(SDL_Surface *surface, size_t *نقاب_ناپ)
{
    Uint8 *dst;
    ثابت صحيح w = (surface->w + 7) / 8;
    ثابت صحيح pad = (((w) % 4) ? (4 - ((w) % 4)) : 0);
    ثابت صحيح pitch = (w + pad);
    ثابت size_t ناپ = pitch * surface->h;
    ساكن ثابت بنانشانی حرف masks[] = { 0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1 };

    فراغ *نقاب = SDL_malloc(ناپ);
    إذا (!نقاب) {
        أرجع عدم;
    }

    dst = (Uint8 *)نقاب;

    // Make the mask completely transparent.
    SDL_memset(dst, 0xff, ناپ);
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
    *نقاب_ناپ = ناپ;
    أرجع نقاب;
}

ساكن bool WriteIconSurface(SDL_IOStream *dst, SDL_Surface *surface)
{
    SDL_Surface *عارضی = عدم;

    إذا (surface->format != SDL_PIXELFORMAT_ARGB8888) {
        عارضی = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        إذا (!عارضی) {
            أرجع false;
        }
        surface = عارضی;
    }

    // Cursor data is double height (DIB and mask), stored bottom-up
    bool ok = true;
    size_t نقاب_ناپ = 0;
    فراغ *نقاب = Create_Icon_نقاب(surface, &نقاب_ناپ);
    إذا (!نقاب) {
        ok = false;
        اذهب پورا;
    }

    BITMAPINFOHEADER bmih;
    SDL_zero(bmih);
    DWORD صف_ناپ = surface->w * 4;
    bmih.bi_ناپ = حجم(BITMAPINFOHEADER);
    bmih.bi_چوڑائی = surface->w;
    bmih.bi_اچائی = surface->h * 2;
    bmih.biPlanes = 1;
    bmih.bi_ثنائی_ہندسہ_گنتی = 32;
    bmih.biCompression = BI_RGB;
    bmih.bi_ناپ_Image = (DWORD)(surface->h * صف_ناپ + نقاب_ناپ);
    ok &= (SDL_WriteIO(dst, &bmih, حجم(bmih)) == حجم(bmih));

    ثابت Uint8 *pix = surface->pixels;
    pix += (surface->h - 1) * surface->pitch;
    لكل (صحيح i = 0; i < surface->h; ++i) {
        ok &= (SDL_WriteIO(dst, pix, صف_ناپ) == صف_ناپ);
        pix -= surface->pitch;
    }
    ok &= (SDL_WriteIO(dst, نقاب, نقاب_ناپ) == نقاب_ناپ);

پورا:
    SDL_free(نقاب);
    SDL_DestroySurface(عارضی);
    أرجع ok;
}

#جے_انت // SAVE_ICON_PNG

ساكن bool Write_Icon_چوکھٹا(SDL_IOStream *dst, SDL_Surface *surface, صحيح hot_x, صحيح hot_y, عائم scale)
{
#جے_تعریف_شدہ SAVE_مضرب_ICONS
    صحيح گنتی = 0;
    SDL_Surface **surfaces = SDL_GetSurfaceImages(surface, &گنتی);
    إذا (!surfaces) {
        أرجع false;
    }
#وإلا
    surface = SDL_GetSurfaceImage(surface, scale);
    إذا (!surface) {
        أرجع false;
    }

    صحيح گنتی = 1;
    SDL_Surface **surfaces = &surface;
#جے_انت

    // Raymond Chen has more insight into this format at:
    // https://devblogs.microsoft.com/oldnewthing/20101018-00/?p=12513
    bool ok = true;
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('i', 'c', 'o', 'n'));
    Sint64 icon_ناپ_وتھ = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    Sint64 ادھار_وتھ_2 = icon_ناپ_وتھ + حجم(DWORD);

    CURSORICONFILEDIR dir;
    dir.idReserved = 0;
    dir.idType = 2; // Cursor
    dir.id_گنتی = گنتی;
    ok &= (SDL_WriteIO(dst, &dir, حجم(dir)) == حجم(dir));

    DWORD entries_ناپ = گنتی * حجم(CURSORICONFILEDIRENTRY);
    CURSORICONFILEDIRENTRY *entries = (CURSORICONFILEDIRENTRY *)SDL_malloc(entries_ناپ);
    إذا (!entries) {
        ok = false;
        اذهب پورا;
    }
    ok &= (SDL_WriteIO(dst, entries, entries_ناپ) == entries_ناپ);

    Sint64 image_وتھ_2 = SDL_TellIO(dst);
    لكل (صحيح i = 0; i < گنتی; ++i) {
        ok &= WriteIconSurface(dst, surfaces[i]);

        Sint64 اگلا_وتھ = SDL_TellIO(dst);
        DWORD dw_Image_ناپ = (DWORD)(اگلا_وتھ - image_وتھ_2);
        DWORD dw_Image_وتھ = (DWORD)(image_وتھ_2 - ادھار_وتھ_2);

        ok &= Fill_Icon_اندراج(&entries[i], surfaces[i], hot_x, hot_y, dw_Image_ناپ, dw_Image_وتھ);

        image_وتھ_2 = اگلا_وتھ;
    }

    // Now that we have the icon entries filled out, rewrite them
    ok &= (SDL_SeekIO(dst, ادھار_وتھ_2 + حجم(dir), SDL_IO_SEEK_سیٹ) >= 0);
    ok &= (SDL_WriteIO(dst, entries, entries_ناپ) == entries_ناپ);
    ok &= (SDL_SeekIO(dst, image_وتھ_2, SDL_IO_SEEK_سیٹ) >= 0);
    SDL_free(entries);

    ok &= Save_Chunk_ناپ(dst, icon_ناپ_وتھ);

پورا:
#جے_تعریف_شدہ SAVE_مضرب_ICONS
    SDL_free(surfaces);
#وإلا
    SDL_DestroySurface(surface);
#جے_انت
    أرجع ok;
}

/* Windows doesn't have an API to easily create animated cursors from a sequence of images,
 * so we have to build an animated cursor resource file in memory and load it.
 */
ساكن HCURSOR WIN_Create_Animated_Cursor_اندرونی(SDL_Cursor_چوکھٹا_Info *چوکھٹے, صحيح چوکھٹا_گنتی, صحيح hot_x, صحيح hot_y, عائم scale)
{
    HCURSOR hcursor = عدم;
    SDL_IOStream *dst = SDL_IOFromDynamicMem();
    إذا (!dst) {
        أرجع عدم;
    }

    صحيح w = (صحيح)SDL_roundf(چوکھٹے[0].surface->w * scale);
    صحيح h = (صحيح)SDL_roundf(چوکھٹے[0].surface->h * scale);

    bool ok = true;
    // RIFF header
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('R', 'I', 'F', 'F'));
    Sint64 riff_ناپ_وتھ = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('A', 'C', 'O', 'N'));

    // anih header chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('a', 'n', 'i', 'h'));
    ok &= SDL_WriteU32LE(dst, حجم(ANIHEADER));

    ANIHEADER anih;
    SDL_zero(anih);
    anih.cbSizeof = حجم(anih);
    anih.چوکھٹے = چوکھٹا_گنتی;
    anih.قدماں = چوکھٹا_گنتی;
    anih.jif_شرح = 1;
    anih.fl = ANI_FLAG_ICON;
    ok &= (SDL_WriteIO(dst, &anih, حجم(anih)) == حجم(anih));

    // Rate chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('r', 'a', 't', 'e'));
    ok &= SDL_WriteU32LE(dst, حجم(DWORD) * چوکھٹا_گنتی);
    لكل (صحيح i = 0; i < چوکھٹا_گنتی; ++i) {
        // Animated Win32 cursors are in jiffy units, and one jiffy is 1/60 of a second.
        ثابت مزدوج WIN32_JIFFY = 1000.0 / 60.0;
        DWORD duration = (چوکھٹے[i].duration ? SDL_lround(چوکھٹے[i].duration / WIN32_JIFFY) : 0xFFFFFFFF);
        ok &= SDL_WriteU32LE(dst, duration);
    }

    // Frame list
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('L', 'I', 'S', 'T'));
    Sint64 چوکھٹا_list_ناپ_وتھ = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('f', 'r', 'a', 'm'));

    لكل (صحيح i = 0; i < چوکھٹا_گنتی; ++i) {
        ok &= Write_Icon_چوکھٹا(dst, چوکھٹے[i].surface, hot_x, hot_y, scale);
    }
    ok &= Save_Chunk_ناپ(dst, چوکھٹا_list_ناپ_وتھ);

    // All done!
    ok &= Save_Chunk_ناپ(dst, riff_ناپ_وتھ);
    إذا (!ok) {
        // The error has been set above
        اذهب پورا;
    }

    BYTE *mem = (BYTE *)SDL_Get_اشارہ_گر_Property(SDL_GetIOProperties(dst), SDL_PROP_IOSTREAM_DYNAMIC_حافظہ_اشارہ_گر, عدم);
    DWORD ناپ = (DWORD)SDL_GetIOSize(dst);
    hcursor = (HCURSOR)CreateIconFromResourceEx(mem, ناپ, FALSE, 0x00030000, w, h, 0);
    إذا (!hcursor) {
        SDL_سیٹ_Error("CreateIconFromResource failed");
    }

پورا:
    SDL_CloseIO(dst);

    أرجع hcursor;
}

ساكن SDL_Cursor *WIN_CreateCursor(SDL_Surface *surface, صحيح hot_x, صحيح hot_y)
{
    SDL_Cursor_چوکھٹا_Info چوکھٹا = { surface, 0 };
    أرجع WIN_Create_Animated_Cursor_And_انکڑے(&چوکھٹا, 1, hot_x, hot_y);
}

ساكن SDL_Cursor *WIN_CreateAnimatedCursor(SDL_Cursor_چوکھٹا_Info *چوکھٹے, صحيح چوکھٹا_گنتی, صحيح hot_x, صحيح hot_y)
{
    أرجع WIN_Create_Animated_Cursor_And_انکڑے(چوکھٹے, چوکھٹا_گنتی, hot_x, hot_y);
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
    حالة SDL_SYSTEM_CURSOR_متن:
    حالة SDL_SYSTEM_CURSOR_VERTICAL_متن:
        name = IDC_IBEAM;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_WAIT:
        name = IDC_WAIT;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_CROSSHAIR:
    حالة SDL_SYSTEM_CURSOR_CELL:
        name = IDC_CROSS;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_ترقی:
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
    حالة SDL_SYSTEM_CURSOR_خانہ_RESIZE:
        name = IDC_SIZEWE;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_NS_RESIZE:
    حالة SDL_SYSTEM_CURSOR_N_RESIZE:
    حالة SDL_SYSTEM_CURSOR_S_RESIZE:
    حالة SDL_SYSTEM_CURSOR_صف_RESIZE:
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
    حالة SDL_SYSTEM_CURSOR_اشارہ_گر:
    حالة SDL_SYSTEM_CURSOR_CONTEXT_MENU:
    حالة SDL_SYSTEM_CURSOR_ALIAS:
    حالة SDL_SYSTEM_CURSOR_COPY:
    حالة SDL_SYSTEM_CURSOR_GRAB:
    حالة SDL_SYSTEM_CURSOR_GRABBING:
    حالة SDL_SYSTEM_CURSOR_ZOOM_وچ:
    حالة SDL_SYSTEM_CURSOR_ZOOM_باہرلا:
        name = IDC_HAND;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_HELP:
        name = IDC_HELP;
        اكسر;
    }
    أرجع WIN_Create_Cursor_And_انکڑے(لدو_Cursor(عدم, name));
}

ساكن SDL_Cursor *WIN_CreateDefaultCursor(فراغ)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    أرجع WIN_CreateSystemCursor(id);
}

ساكن فراغ WIN_FreeCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_انکڑے *انکڑے = cursor->اندرونی;

    لكل (صحيح i = 0; i < انکڑے->عدد_چوکھٹے; ++i) {
        SDL_DestroySurface(انکڑے->چوکھٹے[i].surface);
    }
    طالما (انکڑے->cache) {
        CachedCursor *اندراج = انکڑے->cache;
        انکڑے->cache = اندراج->اگلا;
        إذا (اندراج->cursor) {
            DestroyCursor(اندراج->cursor);
        }
        SDL_free(اندراج);
    }
    إذا (انکڑے->cursor) {
        DestroyCursor(انکڑے->cursor);
    }
    SDL_free(انکڑے);
    SDL_free(cursor);
}

ساكن HCURSOR GetCachedCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_انکڑے *انکڑے = cursor->اندرونی;

    عائم scale = 1.0f;
    إذا (SDL_GetHintBoolean(SDL_HINT_MOUSE_DPI_SCALE_CURSORS, false)) {
        scale = SDL_GetDisplayContentScale(SDL_Get_Display_For_کھڑکی(SDL_GetMouseFocus()));
        إذا (scale == 0.0f) {
            scale = 1.0f;
        }
    }
    لكل (CachedCursor *اندراج = انکڑے->cache; اندراج; اندراج = اندراج->اگلا) {
        إذا (scale == اندراج->scale) {
            أرجع اندراج->cursor;
        }
    }

    // Need to create a cursor for this content scale
    HCURSOR hcursor = WIN_Create_Animated_Cursor_اندرونی(انکڑے->چوکھٹے, انکڑے->عدد_چوکھٹے, انکڑے->hot_x, انکڑے->hot_y, scale);
    إذا (!hcursor) {
        أرجع عدم;
    }

    CachedCursor *اندراج = (CachedCursor *)SDL_calloc(1, حجم(*اندراج));
    إذا (!اندراج) {
        DestroyCursor(hcursor);
        أرجع عدم;
    }
    اندراج->cursor = hcursor;
    اندراج->scale = scale;
    اندراج->اگلا = انکڑے->cache;
    انکڑے->cache = اندراج;

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
        SDL_Cursor_انکڑے *انکڑے = cursor->اندرونی;
        إذا (انکڑے->عدد_چوکھٹے > 0) {
            SDL_cursor = GetCachedCursor(cursor);
        } وإلا {
            SDL_cursor = انکڑے->cursor;
        }
    } وإلا {
        SDL_cursor = عدم;
    }
    إذا (SDL_GetMouseFocus() != عدم) {
        سیٹ_Cursor(SDL_cursor);
    }
    أرجع true;
}

فراغ WIN_سیٹ_Cursor_Pos(صحيح x, صحيح y)
{
    // We need to jitter the value because otherwise Windows will occasionally inexplicably ignore the SetCursorPos() or SendInput()
    سیٹ_Cursor_Pos(x, y);
    سیٹ_Cursor_Pos(x + 1, y);
    سیٹ_Cursor_Pos(x, y);

    // Flush any mouse motion prior to or associated with this warp
#جے_تعریف_شدہ _MSC_VER // We explicitly want to use GetTickCount(), not GetTickCount64()
#ہدایت warning(ڈالو)
#ہدایت warning(disable : 28159)
#جے_انت
    SDL_آخری_warp_ویلا = Get_Tick_گنتی();
    إذا (!SDL_آخری_warp_ویلا) {
        SDL_آخری_warp_ویلا = 1;
    }
#جے_تعریف_شدہ _MSC_VER
#ہدایت warning(نکالو)
#جے_انت
}

ساكن bool WIN_WarpMouse(SDL_کھڑکی *کھڑکی, عائم x, عائم y)
{
    SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
    HWND hwnd = انکڑے->hwnd;
    نقطہ_2 pt;

    // Don't warp the mouse while we're doing a modal interaction
    إذا (انکڑے->وچ_title_click || انکڑے->focus_click_pending) {
        أرجع true;
    }

    pt.x = (صحيح)SDL_roundf(x);
    pt.y = (صحيح)SDL_roundf(y);
    Client_منزل_Screen(hwnd, &pt);
    WIN_سیٹ_Cursor_Pos(pt.x, pt.y);

    // Send the exact mouse motion associated with this warp
    SDL_SendMouseMotion(0, کھڑکی, SDL_GLOBAL_MOUSE_ID, false, x, y);
    أرجع true;
}

ساكن bool WIN_WarpMouseGlobal(عائم x, عائم y)
{
    نقطہ_2 pt;

    pt.x = (صحيح)SDL_roundf(x);
    pt.y = (صحيح)SDL_roundf(y);
    سیٹ_Cursor_Pos(pt.x, pt.y);
    أرجع true;
}

ساكن bool WIN_سیٹ_Relative_Mouse_منوال(bool enabled)
{
    أرجع WIN_سیٹ_Raw_Mouse_Enabled(SDL_GetVideoDevice(), enabled);
}

ساكن bool WIN_CaptureMouse(SDL_کھڑکی *کھڑکی)
{
    إذا (کھڑکی) {
        SDL_کھڑکی_انکڑے *انکڑے = کھڑکی->اندرونی;
        سیٹ_Capture(انکڑے->hwnd);
    } وإلا {
        SDL_کھڑکی *focus_کھڑکی_2 = SDL_GetMouseFocus();

        إذا (focus_کھڑکی_2) {
            SDL_کھڑکی_انکڑے *انکڑے = focus_کھڑکی_2->اندرونی;
            إذا (!انکڑے->mouse_tracked) {
                SDL_سیٹ_Mouse_Focus(عدم);
            }
        }
        ReleaseCapture();
    }

    أرجع true;
}

ساكن SDL_MouseButtonFlags WIN_GetGlobalMouseState(عائم *x, عائم *y)
{
    SDL_MouseButtonFlags نتیجہ = 0;
    نقطہ_2 pt = { 0, 0 };
    bool وٹاندرا_Buttons = GetSystemMetrics(SM_SWAPBUTTON) != 0;

    GetCursorPos(&pt);
    *x = (عائم)pt.x;
    *y = (عائم)pt.y;

    نتیجہ |= Get_Async_کلید_State(!وٹاندرا_Buttons ? VK_LBUTTON : VK_RBUTTON) & 0x8000 ? SDL_BUTTON_LMASK : 0;
    نتیجہ |= Get_Async_کلید_State(!وٹاندرا_Buttons ? VK_RBUTTON : VK_LBUTTON) & 0x8000 ? SDL_BUTTON_RMASK : 0;
    نتیجہ |= Get_Async_کلید_State(VK_MBUTTON) & 0x8000 ? SDL_BUTTON_MMASK : 0;
    نتیجہ |= Get_Async_کلید_State(VK_XBUTTON1) & 0x8000 ? SDL_BUTTON_X1_نقاب : 0;
    نتیجہ |= Get_Async_کلید_State(VK_XBUTTON2) & 0x8000 ? SDL_BUTTON_X2_نقاب : 0;

    أرجع نتیجہ;
}

ساكن فراغ WIN_ApplySystemScale(فراغ *اندرونی, Uint64 timestamp, SDL_کھڑکی *کھڑکی, SDL_MouseID mouseID, عائم *x, عائم *y)
{
    إذا (!اندرونی) {
        أرجع;
    }
    WIN_Mouse_انکڑے *انکڑے = (WIN_Mouse_انکڑے *)اندرونی;

    SDL_VideoDisplay *display = کھڑکی ? SDL_Get_Video_Display_For_کھڑکی(کھڑکی) : SDL_GetVideoDisplay(SDL_GetPrimaryDisplay());

    Sint64 ix = (Sint64)*x * 65536;
    Sint64 iy = (Sint64)*y * 65536;
    Uint32 dpi = display ? (Uint32)(display->content_scale * USER_DEFAULT_SCREEN_DPI) : USER_DEFAULT_SCREEN_DPI;

    إذا (!انکڑے->enhanced) { // early return if flat scale
        dpi = انکڑے->dpiscale * (انکڑے->dpiaware ? dpi : USER_DEFAULT_SCREEN_DPI);
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

    Uint64 *xs = انکڑے->xs;
    Uint64 *ys = انکڑے->ys;
    Uint64 absx = SDL_abs(ix);
    Uint64 absy = SDL_abs(iy);
    Uint64 رفتار = SDL_min(absx, absy) + (SDL_max(absx, absy) << 1); // super cursed approximation used by Windows
    إذا (رفتار == 0) {
        أرجع;
    }

    صحيح i, j, k;
    لكل (i = 1; i < 5; i++) {
        j = i;
        إذا (رفتار < xs[j]) {
            اكسر;
        }
    }
    i -= 1;
    j -= 1;
    k = انکڑے->آخری_گرہ;
    انکڑے->آخری_گرہ = j;

    Uint32 denom = انکڑے->dpidenom;
    Sint64 scale = 0;
    Sint64 xdiff = xs[j+1] - xs[j];
    Sint64 ydiff = ys[j+1] - ys[j];
    إذا (xdiff != 0) {
        Sint64 ڈھلوان = ydiff / xdiff;
        Sint64 inter = ڈھلوان * xs[i] - ys[i];
        scale += ڈھلوان - inter / رفتار;
    }

    إذا (j > k) {
        denom <<= 1;
        xdiff = xs[k+1] - xs[k];
        ydiff = ys[k+1] - ys[k];
        إذا (xdiff != 0) {
            Sint64 ڈھلوان = ydiff / xdiff;
            Sint64 inter = ڈھلوان * xs[k] - ys[k];
            scale += ڈھلوان - inter / رفتار;
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
    mouse->سیٹ_Relative_Mouse_منوال = WIN_سیٹ_Relative_Mouse_منوال;
    mouse->CaptureMouse = WIN_CaptureMouse;
    mouse->GetGlobalMouseState = WIN_GetGlobalMouseState;
    mouse->ApplySystemScale = WIN_ApplySystemScale;
    mouse->system_scale_انکڑے = &WIN_system_scale_انکڑے;

    SDL_سیٹ_Default_Cursor(WIN_CreateDefaultCursor());

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

ساكن فراغ Read_Mouse_ونگ(صحيح v, Uint64 xs[5], Uint64 ys[5])
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
    إذا (Reg_Open_کلید_Ex_W(HKEY_CURRENT_USER, L"Control Panel\\Mouse", 0, کلید_READ, &open_handle) == ERROR_SUCCESS) {
        Reg_Query_قدر_Ex_W(open_handle, L"SmoothMouseXCurve", عدم, عدم, (BYTE*)xbuff, &xsize);
        Reg_Query_قدر_Ex_W(open_handle, L"SmoothMouseYCurve", عدم, عدم, (BYTE*)ybuff, &ysize);
        Reg_Close_کلید(open_handle);
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
        mouse->system_scale_انکڑے = &WIN_system_scale_انکڑے;
    }

    // always reinitialize to valid defaults, whether fetch was successful or not.
    WIN_Mouse_انکڑے *انکڑے = &WIN_system_scale_انکڑے;
    انکڑے->residual[0] = 0;
    انکڑے->residual[1] = 0;
    انکڑے->dpiscale = 32;
    انکڑے->dpidenom = (10 * (WIN_IsWindows8OrGreater() ? 120 : 150)) << 16;
    انکڑے->dpiaware = WIN_Is_فی_Monitor_V2_DPIAware(SDL_GetVideoDevice());
    انکڑے->enhanced = false;

    صحيح v = 10;
    إذا (SystemParametersInfo(SPI_GETMOUSESPEED, 0, &v, 0)) {
        v = SDL_max(1, SDL_min(v, 20));
        انکڑے->dpiscale = SDL_max(SDL_max(v, (v - 2) * 4), (v - 6) * 8);
    }

    صحيح params[3];
    إذا (SystemParametersInfo(SPI_GETMOUSE, 0, &params, 0)) {
        انکڑے->enhanced = params[2] ? true : false;
        إذا (params[2]) {
            Read_Mouse_ونگ(v, انکڑے->xs, انکڑے->ys);
        }
    }
}

#جے_انت // SDL_VIDEO_DRIVER_WINDOWS

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

#تعریف_کن RIFF_FOURCC(c0, c1, c2, c3)                 \
    ((DWORD)(BYTE)(c0) | ((DWORD)(BYTE)(c1) << 8) | \
     ((DWORD)(BYTE)(c2) << 16) | ((DWORD)(BYTE)(c3) << 24))

#تعریف_کن ANI_FLAG_ICON 0x1

#رهنمود pack(افزودن, 1)

تعريفنوع بنية
{
    BYTE b_عرض;
    BYTE b_ارتفاع;
    BYTE b_Color_شمار;
    BYTE bReserved;
    کلمه xHotspot;
    کلمه yHotspot;
    DWORD dw_Image_اندازه;
    DWORD dw_Image_جابه_جایی;
} CURSORICONFILEDIRENTRY;

تعريفنوع بنية
{
    کلمه idReserved;
    کلمه idType;
    کلمه id_شمار;
} CURSORICONFILEDIR;

تعريفنوع بنية
{
    DWORD cbSizeof; // sizeof(ANIHEADER) = 36 bytes.
    DWORD قابها;   // Number of frames in the frame list.
    DWORD گامها;    // Number of steps in the animation loop.
    DWORD عرض;    //عرض
    DWORD ارتفاع;   //ارتفاع
    DWORD bpp;      // bpp
    DWORD planes;   // Not used
    DWORD jif_نرخ;  // Default display rate, in jiffies (1/60s)
    DWORD fl;       // AF_ICON should be set. AF_SEQUENCE is optional
} ANIHEADER;

#رهنمود pack(برداشت)

تعريفنوع بنية CachedCursor
{
    عائم scale;
    HCURSOR cursor;
    بنية CachedCursor *بعدی;
} CachedCursor;

بنية SDL_Cursor_داده
{
    HCURSOR cursor;

    CachedCursor *cache;
    صحيح hot_x;
    صحيح hot_y;
    صحيح رقم_قابها;
    SDL_Cursor_قاب_Info قابها[1];
};

تعريفنوع بنية
{
    Uint64 xs[5];
    Uint64 ys[5];
    Sint64 residual[2];
    Uint32 dpiscale;
    Uint32 dpidenom;
    صحيح آخرین_گره;
    bool enhanced;
    bool dpiaware;
} WIN_Mouse_داده;

DWORD SDL_آخرین_warp_زمان = 0;
HCURSOR SDL_cursor = عدم;
ساكن SDL_Cursor *SDL_blank_cursor = عدم;
ساكن WIN_Mouse_داده WIN_system_scale_داده;

ساكن SDL_Cursor *WIN_Create_Cursor_And_داده(HCURSOR hcursor)
{
    إذا (!hcursor) {
        أرجع عدم;
    }

    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, حجم(*cursor));
    إذا (!cursor) {
        أرجع عدم;
    }

    SDL_Cursor_داده *داده = (SDL_Cursor_داده *)SDL_calloc(1, حجم(*داده));
    إذا (!داده) {
        SDL_free(cursor);
        أرجع عدم;
    }

    داده->cursor = hcursor;
    cursor->داخلی = داده;
    أرجع cursor;
}

ساكن SDL_Cursor *WIN_Create_Animated_Cursor_And_داده(SDL_Cursor_قاب_Info *قابها, صحيح قاب_شمار, صحيح hot_x, صحيح hot_y)
{
    // Dynamically generate cursors at the appropriate DPI
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, حجم(*cursor));
    إذا (!cursor) {
        أرجع عدم;
    }

    SDL_Cursor_داده *داده = (SDL_Cursor_داده *)SDL_calloc(1, حجم(*داده) + (حجم(SDL_Cursor_قاب_Info) * (قاب_شمار - 1)));
    إذا (!داده) {
        SDL_free(cursor);
        أرجع عدم;
    }

    داده->hot_x = hot_x;
    داده->hot_y = hot_y;
    داده->رقم_قابها = قاب_شمار;
    لكل (صحيح i = 0; i < قاب_شمار; ++i) {
        SDL_Surface *surface = قابها[i].surface;
        إذا (surface->flags & SDL_SURFACE_PREALLOCATED) {
            surface = SDL_DuplicateSurface(surface);
            إذا (!surface) {
                طالما (i > 0) {
                    --i;
                    SDL_DestroySurface(داده->قابها[i].surface);
                }
                SDL_free(داده);
                SDL_free(cursor);
                أرجع عدم;
            }
        } وإلا {
            ++surface->refcount;
        }
        داده->قابها[i].surface = surface;
        داده->قابها[i].duration = قابها[i].duration;
    }
    cursor->داخلی = داده;
    أرجع cursor;
}

ساكن bool Save_Chunk_اندازه(SDL_IOStream* dst, Sint64 جابه_جایی_2)
{
    Sint64 اینجا = SDL_TellIO(dst);
    إذا (اینجا < 0) {
        أرجع false;
    }
    إذا (SDL_SeekIO(dst, جابه_جایی_2, SDL_IO_SEEK_مجموعه) < 0) {
        أرجع false;
    }

    DWORD اندازه = (DWORD)(اینجا - (جابه_جایی_2 + حجم(DWORD)));
    إذا (!SDL_WriteU32LE(dst, اندازه)) {
        أرجع false;
    }
    أرجع SDL_SeekIO(dst, اینجا, SDL_IO_SEEK_مجموعه);
}

ساكن bool Fill_Icon_مدخل(CURSORICONFILEDIRENTRY *مدخل, SDL_Surface *surface, صحيح hot_x, صحيح hot_y, DWORD dw_Image_اندازه, DWORD dw_Image_جابه_جایی)
{
    إذا (surface->props) {
        hot_x = (صحيح)SDL_Get_عدد_Property(surface->props, SDL_PROP_SURFACE_HOTSPOT_X_عدد, hot_x);
        hot_y = (صحيح)SDL_Get_عدد_Property(surface->props, SDL_PROP_SURFACE_HOTSPOT_Y_عدد, hot_y);
    }
    hot_x = SDL_clamp(hot_x, 0, surface->w - 1);
    hot_y = SDL_clamp(hot_y, 0, surface->h - 1);

    SDL_zerop(مدخل);
    مدخل->b_عرض = surface->w < 256 ? surface->w : 0;  // 0 means a width of 256
    مدخل->b_ارتفاع = surface->h < 256 ? surface->h : 0; // 0 means a height of 256
    مدخل->xHotspot = hot_x;
    مدخل->yHotspot = hot_y;
    مدخل->dw_Image_اندازه = dw_Image_اندازه;
    مدخل->dw_Image_جابه_جایی = dw_Image_جابه_جایی;
    أرجع true;
}

#اگر_تعریف_شده SAVE_ICON_PNG

ساكن bool WriteIconSurface(SDL_IOStream *dst, SDL_Surface *surface)
{
    إذا (!SDL_SavePNG_IO(surface, dst, false)) {
        أرجع false;
    }

    // Image data offsets must be WORD aligned
    Sint64 جابه_جایی_2 = SDL_TellIO(dst);
    إذا (جابه_جایی_2 & 1) {
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
ساكن فراغ *Create_Icon_ماسک(SDL_Surface *surface, size_t *ماسک_اندازه)
{
    Uint8 *dst;
    ثابت صحيح w = (surface->w + 7) / 8;
    ثابت صحيح pad = (((w) % 4) ? (4 - ((w) % 4)) : 0);
    ثابت صحيح pitch = (w + pad);
    ثابت size_t اندازه = pitch * surface->h;
    ساكن ثابت بیعلامت حرف masks[] = { 0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1 };

    فراغ *ماسک = SDL_malloc(اندازه);
    إذا (!ماسک) {
        أرجع عدم;
    }

    dst = (Uint8 *)ماسک;

    // Make the mask completely transparent.
    SDL_memset(dst, 0xff, اندازه);
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
    *ماسک_اندازه = اندازه;
    أرجع ماسک;
}

ساكن bool WriteIconSurface(SDL_IOStream *dst, SDL_Surface *surface)
{
    SDL_Surface *موقت = عدم;

    إذا (surface->format != SDL_PIXELFORMAT_ARGB8888) {
        موقت = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        إذا (!موقت) {
            أرجع false;
        }
        surface = موقت;
    }

    // Cursor data is double height (DIB and mask), stored bottom-up
    bool ok = true;
    size_t ماسک_اندازه = 0;
    فراغ *ماسک = Create_Icon_ماسک(surface, &ماسک_اندازه);
    إذا (!ماسک) {
        ok = false;
        اذهب انجامشده;
    }

    BITMAPINFOHEADER bmih;
    SDL_zero(bmih);
    DWORD ردیف_اندازه = surface->w * 4;
    bmih.bi_اندازه = حجم(BITMAPINFOHEADER);
    bmih.bi_عرض = surface->w;
    bmih.bi_ارتفاع = surface->h * 2;
    bmih.biPlanes = 1;
    bmih.bi_بیت_شمار = 32;
    bmih.biCompression = BI_RGB;
    bmih.bi_اندازه_Image = (DWORD)(surface->h * ردیف_اندازه + ماسک_اندازه);
    ok &= (SDL_WriteIO(dst, &bmih, حجم(bmih)) == حجم(bmih));

    ثابت Uint8 *pix = surface->pixels;
    pix += (surface->h - 1) * surface->pitch;
    لكل (صحيح i = 0; i < surface->h; ++i) {
        ok &= (SDL_WriteIO(dst, pix, ردیف_اندازه) == ردیف_اندازه);
        pix -= surface->pitch;
    }
    ok &= (SDL_WriteIO(dst, ماسک, ماسک_اندازه) == ماسک_اندازه);

انجامشده:
    SDL_free(ماسک);
    SDL_DestroySurface(موقت);
    أرجع ok;
}

#پایان_اگر // SAVE_ICON_PNG

ساكن bool Write_Icon_قاب(SDL_IOStream *dst, SDL_Surface *surface, صحيح hot_x, صحيح hot_y, عائم scale)
{
#اگر_تعریف_شده SAVE_مضرب_ICONS
    صحيح شمار = 0;
    SDL_Surface **surfaces = SDL_GetSurfaceImages(surface, &شمار);
    إذا (!surfaces) {
        أرجع false;
    }
#وإلا
    surface = SDL_GetSurfaceImage(surface, scale);
    إذا (!surface) {
        أرجع false;
    }

    صحيح شمار = 1;
    SDL_Surface **surfaces = &surface;
#پایان_اگر

    // Raymond Chen has more insight into this format at:
    // https://devblogs.microsoft.com/oldnewthing/20101018-00/?p=12513
    bool ok = true;
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('i', 'c', 'o', 'n'));
    Sint64 icon_اندازه_جابه_جایی = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    Sint64 پایه_جابه_جایی_2 = icon_اندازه_جابه_جایی + حجم(DWORD);

    CURSORICONFILEDIR dir;
    dir.idReserved = 0;
    dir.idType = 2; // Cursor
    dir.id_شمار = شمار;
    ok &= (SDL_WriteIO(dst, &dir, حجم(dir)) == حجم(dir));

    DWORD entries_اندازه = شمار * حجم(CURSORICONFILEDIRENTRY);
    CURSORICONFILEDIRENTRY *entries = (CURSORICONFILEDIRENTRY *)SDL_malloc(entries_اندازه);
    إذا (!entries) {
        ok = false;
        اذهب انجامشده;
    }
    ok &= (SDL_WriteIO(dst, entries, entries_اندازه) == entries_اندازه);

    Sint64 image_جابه_جایی_2 = SDL_TellIO(dst);
    لكل (صحيح i = 0; i < شمار; ++i) {
        ok &= WriteIconSurface(dst, surfaces[i]);

        Sint64 بعدی_جابه_جایی = SDL_TellIO(dst);
        DWORD dw_Image_اندازه = (DWORD)(بعدی_جابه_جایی - image_جابه_جایی_2);
        DWORD dw_Image_جابه_جایی = (DWORD)(image_جابه_جایی_2 - پایه_جابه_جایی_2);

        ok &= Fill_Icon_مدخل(&entries[i], surfaces[i], hot_x, hot_y, dw_Image_اندازه, dw_Image_جابه_جایی);

        image_جابه_جایی_2 = بعدی_جابه_جایی;
    }

    // Now that we have the icon entries filled out, rewrite them
    ok &= (SDL_SeekIO(dst, پایه_جابه_جایی_2 + حجم(dir), SDL_IO_SEEK_مجموعه) >= 0);
    ok &= (SDL_WriteIO(dst, entries, entries_اندازه) == entries_اندازه);
    ok &= (SDL_SeekIO(dst, image_جابه_جایی_2, SDL_IO_SEEK_مجموعه) >= 0);
    SDL_free(entries);

    ok &= Save_Chunk_اندازه(dst, icon_اندازه_جابه_جایی);

انجامشده:
#اگر_تعریف_شده SAVE_مضرب_ICONS
    SDL_free(surfaces);
#وإلا
    SDL_DestroySurface(surface);
#پایان_اگر
    أرجع ok;
}

/* Windows doesn't have an API to easily create animated cursors from a sequence of images,
 * so we have to build an animated cursor resource file in memory and load it.
 */
ساكن HCURSOR WIN_Create_Animated_Cursor_داخلی(SDL_Cursor_قاب_Info *قابها, صحيح قاب_شمار, صحيح hot_x, صحيح hot_y, عائم scale)
{
    HCURSOR hcursor = عدم;
    SDL_IOStream *dst = SDL_IOFromDynamicMem();
    إذا (!dst) {
        أرجع عدم;
    }

    صحيح w = (صحيح)SDL_roundf(قابها[0].surface->w * scale);
    صحيح h = (صحيح)SDL_roundf(قابها[0].surface->h * scale);

    bool ok = true;
    // RIFF header
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('R', 'I', 'F', 'F'));
    Sint64 riff_اندازه_جابه_جایی = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('A', 'C', 'O', 'N'));

    // anih header chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('a', 'n', 'i', 'h'));
    ok &= SDL_WriteU32LE(dst, حجم(ANIHEADER));

    ANIHEADER anih;
    SDL_zero(anih);
    anih.cbSizeof = حجم(anih);
    anih.قابها = قاب_شمار;
    anih.گامها = قاب_شمار;
    anih.jif_نرخ = 1;
    anih.fl = ANI_FLAG_ICON;
    ok &= (SDL_WriteIO(dst, &anih, حجم(anih)) == حجم(anih));

    // Rate chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('r', 'a', 't', 'e'));
    ok &= SDL_WriteU32LE(dst, حجم(DWORD) * قاب_شمار);
    لكل (صحيح i = 0; i < قاب_شمار; ++i) {
        // Animated Win32 cursors are in jiffy units, and one jiffy is 1/60 of a second.
        ثابت مزدوج WIN32_JIFFY = 1000.0 / 60.0;
        DWORD duration = (قابها[i].duration ? SDL_lround(قابها[i].duration / WIN32_JIFFY) : 0xFFFFFFFF);
        ok &= SDL_WriteU32LE(dst, duration);
    }

    // Frame list
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('L', 'I', 'S', 'T'));
    Sint64 قاب_list_اندازه_جابه_جایی = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('f', 'r', 'a', 'm'));

    لكل (صحيح i = 0; i < قاب_شمار; ++i) {
        ok &= Write_Icon_قاب(dst, قابها[i].surface, hot_x, hot_y, scale);
    }
    ok &= Save_Chunk_اندازه(dst, قاب_list_اندازه_جابه_جایی);

    // All done!
    ok &= Save_Chunk_اندازه(dst, riff_اندازه_جابه_جایی);
    إذا (!ok) {
        // The error has been set above
        اذهب انجامشده;
    }

    BYTE *mem = (BYTE *)SDL_Get_اشاره_گر_Property(SDL_GetIOProperties(dst), SDL_PROP_IOSTREAM_DYNAMIC_حافظه_اشاره_گر, عدم);
    DWORD اندازه = (DWORD)SDL_GetIOSize(dst);
    hcursor = (HCURSOR)CreateIconFromResourceEx(mem, اندازه, FALSE, 0x00030000, w, h, 0);
    إذا (!hcursor) {
        SDL_مجموعه_Error("CreateIconFromResource failed");
    }

انجامشده:
    SDL_CloseIO(dst);

    أرجع hcursor;
}

ساكن SDL_Cursor *WIN_CreateCursor(SDL_Surface *surface, صحيح hot_x, صحيح hot_y)
{
    SDL_Cursor_قاب_Info قاب = { surface, 0 };
    أرجع WIN_Create_Animated_Cursor_And_داده(&قاب, 1, hot_x, hot_y);
}

ساكن SDL_Cursor *WIN_CreateAnimatedCursor(SDL_Cursor_قاب_Info *قابها, صحيح قاب_شمار, صحيح hot_x, صحيح hot_y)
{
    أرجع WIN_Create_Animated_Cursor_And_داده(قابها, قاب_شمار, hot_x, hot_y);
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
    حالة SDL_SYSTEM_CURSOR_پیشرفت:
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
    حالة SDL_SYSTEM_CURSOR_ستون_RESIZE:
        name = IDC_SIZEWE;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_NS_RESIZE:
    حالة SDL_SYSTEM_CURSOR_N_RESIZE:
    حالة SDL_SYSTEM_CURSOR_S_RESIZE:
    حالة SDL_SYSTEM_CURSOR_ردیف_RESIZE:
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
    حالة SDL_SYSTEM_CURSOR_اشاره_گر:
    حالة SDL_SYSTEM_CURSOR_CONTEXT_MENU:
    حالة SDL_SYSTEM_CURSOR_ALIAS:
    حالة SDL_SYSTEM_CURSOR_COPY:
    حالة SDL_SYSTEM_CURSOR_GRAB:
    حالة SDL_SYSTEM_CURSOR_GRABBING:
    حالة SDL_SYSTEM_CURSOR_ZOOM_درون:
    حالة SDL_SYSTEM_CURSOR_ZOOM_بیرون:
        name = IDC_HAND;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_HELP:
        name = IDC_HELP;
        اكسر;
    }
    أرجع WIN_Create_Cursor_And_داده(بارگیری_Cursor(عدم, name));
}

ساكن SDL_Cursor *WIN_CreateDefaultCursor(فراغ)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    أرجع WIN_CreateSystemCursor(id);
}

ساكن فراغ WIN_FreeCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_داده *داده = cursor->داخلی;

    لكل (صحيح i = 0; i < داده->رقم_قابها; ++i) {
        SDL_DestroySurface(داده->قابها[i].surface);
    }
    طالما (داده->cache) {
        CachedCursor *مدخل = داده->cache;
        داده->cache = مدخل->بعدی;
        إذا (مدخل->cursor) {
            DestroyCursor(مدخل->cursor);
        }
        SDL_free(مدخل);
    }
    إذا (داده->cursor) {
        DestroyCursor(داده->cursor);
    }
    SDL_free(داده);
    SDL_free(cursor);
}

ساكن HCURSOR GetCachedCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_داده *داده = cursor->داخلی;

    عائم scale = 1.0f;
    إذا (SDL_GetHintBoolean(SDL_HINT_MOUSE_DPI_SCALE_CURSORS, false)) {
        scale = SDL_GetDisplayContentScale(SDL_Get_Display_For_پنجره(SDL_GetMouseFocus()));
        إذا (scale == 0.0f) {
            scale = 1.0f;
        }
    }
    لكل (CachedCursor *مدخل = داده->cache; مدخل; مدخل = مدخل->بعدی) {
        إذا (scale == مدخل->scale) {
            أرجع مدخل->cursor;
        }
    }

    // Need to create a cursor for this content scale
    HCURSOR hcursor = WIN_Create_Animated_Cursor_داخلی(داده->قابها, داده->رقم_قابها, داده->hot_x, داده->hot_y, scale);
    إذا (!hcursor) {
        أرجع عدم;
    }

    CachedCursor *مدخل = (CachedCursor *)SDL_calloc(1, حجم(*مدخل));
    إذا (!مدخل) {
        DestroyCursor(hcursor);
        أرجع عدم;
    }
    مدخل->cursor = hcursor;
    مدخل->scale = scale;
    مدخل->بعدی = داده->cache;
    داده->cache = مدخل;

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
        SDL_Cursor_داده *داده = cursor->داخلی;
        إذا (داده->رقم_قابها > 0) {
            SDL_cursor = GetCachedCursor(cursor);
        } وإلا {
            SDL_cursor = داده->cursor;
        }
    } وإلا {
        SDL_cursor = عدم;
    }
    إذا (SDL_GetMouseFocus() != عدم) {
        مجموعه_Cursor(SDL_cursor);
    }
    أرجع true;
}

فراغ WIN_مجموعه_Cursor_Pos(صحيح x, صحيح y)
{
    // We need to jitter the value because otherwise Windows will occasionally inexplicably ignore the SetCursorPos() or SendInput()
    مجموعه_Cursor_Pos(x, y);
    مجموعه_Cursor_Pos(x + 1, y);
    مجموعه_Cursor_Pos(x, y);

    // Flush any mouse motion prior to or associated with this warp
#اگر_تعریف_شده _MSC_VER // We explicitly want to use GetTickCount(), not GetTickCount64()
#رهنمود warning(افزودن)
#رهنمود warning(disable : 28159)
#پایان_اگر
    SDL_آخرین_warp_زمان = Get_Tick_شمار();
    إذا (!SDL_آخرین_warp_زمان) {
        SDL_آخرین_warp_زمان = 1;
    }
#اگر_تعریف_شده _MSC_VER
#رهنمود warning(برداشت)
#پایان_اگر
}

ساكن bool WIN_WarpMouse(SDL_پنجره *پنجره, عائم x, عائم y)
{
    SDL_پنجره_داده *داده = پنجره->داخلی;
    HWND hwnd = داده->hwnd;
    نقطه_2 pt;

    // Don't warp the mouse while we're doing a modal interaction
    إذا (داده->درون_title_click || داده->focus_click_pending) {
        أرجع true;
    }

    pt.x = (صحيح)SDL_roundf(x);
    pt.y = (صحيح)SDL_roundf(y);
    Client_مقصد_Screen(hwnd, &pt);
    WIN_مجموعه_Cursor_Pos(pt.x, pt.y);

    // Send the exact mouse motion associated with this warp
    SDL_SendMouseMotion(0, پنجره, SDL_GLOBAL_MOUSE_ID, false, x, y);
    أرجع true;
}

ساكن bool WIN_WarpMouseGlobal(عائم x, عائم y)
{
    نقطه_2 pt;

    pt.x = (صحيح)SDL_roundf(x);
    pt.y = (صحيح)SDL_roundf(y);
    مجموعه_Cursor_Pos(pt.x, pt.y);
    أرجع true;
}

ساكن bool WIN_مجموعه_Relative_Mouse_نما(bool enabled)
{
    أرجع WIN_مجموعه_Raw_Mouse_Enabled(SDL_GetVideoDevice(), enabled);
}

ساكن bool WIN_CaptureMouse(SDL_پنجره *پنجره)
{
    إذا (پنجره) {
        SDL_پنجره_داده *داده = پنجره->داخلی;
        مجموعه_Capture(داده->hwnd);
    } وإلا {
        SDL_پنجره *focus_پنجره_2 = SDL_GetMouseFocus();

        إذا (focus_پنجره_2) {
            SDL_پنجره_داده *داده = focus_پنجره_2->داخلی;
            إذا (!داده->mouse_tracked) {
                SDL_مجموعه_Mouse_Focus(عدم);
            }
        }
        ReleaseCapture();
    }

    أرجع true;
}

ساكن SDL_MouseButtonFlags WIN_GetGlobalMouseState(عائم *x, عائم *y)
{
    SDL_MouseButtonFlags نتیجه = 0;
    نقطه_2 pt = { 0, 0 };
    bool جابجا_Buttons = GetSystemMetrics(SM_SWAPBUTTON) != 0;

    GetCursorPos(&pt);
    *x = (عائم)pt.x;
    *y = (عائم)pt.y;

    نتیجه |= Get_Async_کلید_State(!جابجا_Buttons ? VK_LBUTTON : VK_RBUTTON) & 0x8000 ? SDL_BUTTON_LMASK : 0;
    نتیجه |= Get_Async_کلید_State(!جابجا_Buttons ? VK_RBUTTON : VK_LBUTTON) & 0x8000 ? SDL_BUTTON_RMASK : 0;
    نتیجه |= Get_Async_کلید_State(VK_MBUTTON) & 0x8000 ? SDL_BUTTON_MMASK : 0;
    نتیجه |= Get_Async_کلید_State(VK_XBUTTON1) & 0x8000 ? SDL_BUTTON_X1_ماسک : 0;
    نتیجه |= Get_Async_کلید_State(VK_XBUTTON2) & 0x8000 ? SDL_BUTTON_X2_ماسک : 0;

    أرجع نتیجه;
}

ساكن فراغ WIN_ApplySystemScale(فراغ *داخلی, Uint64 timestamp, SDL_پنجره *پنجره, SDL_MouseID mouseID, عائم *x, عائم *y)
{
    إذا (!داخلی) {
        أرجع;
    }
    WIN_Mouse_داده *داده = (WIN_Mouse_داده *)داخلی;

    SDL_VideoDisplay *display = پنجره ? SDL_Get_Video_Display_For_پنجره(پنجره) : SDL_GetVideoDisplay(SDL_GetPrimaryDisplay());

    Sint64 ix = (Sint64)*x * 65536;
    Sint64 iy = (Sint64)*y * 65536;
    Uint32 dpi = display ? (Uint32)(display->content_scale * USER_DEFAULT_SCREEN_DPI) : USER_DEFAULT_SCREEN_DPI;

    إذا (!داده->enhanced) { // early return if flat scale
        dpi = داده->dpiscale * (داده->dpiaware ? dpi : USER_DEFAULT_SCREEN_DPI);
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

    Uint64 *xs = داده->xs;
    Uint64 *ys = داده->ys;
    Uint64 absx = SDL_abs(ix);
    Uint64 absy = SDL_abs(iy);
    Uint64 سرعت = SDL_min(absx, absy) + (SDL_max(absx, absy) << 1); // super cursed approximation used by Windows
    إذا (سرعت == 0) {
        أرجع;
    }

    صحيح i, j, k;
    لكل (i = 1; i < 5; i++) {
        j = i;
        إذا (سرعت < xs[j]) {
            اكسر;
        }
    }
    i -= 1;
    j -= 1;
    k = داده->آخرین_گره;
    داده->آخرین_گره = j;

    Uint32 denom = داده->dpidenom;
    Sint64 scale = 0;
    Sint64 xdiff = xs[j+1] - xs[j];
    Sint64 ydiff = ys[j+1] - ys[j];
    إذا (xdiff != 0) {
        Sint64 شیب = ydiff / xdiff;
        Sint64 inter = شیب * xs[i] - ys[i];
        scale += شیب - inter / سرعت;
    }

    إذا (j > k) {
        denom <<= 1;
        xdiff = xs[k+1] - xs[k];
        ydiff = ys[k+1] - ys[k];
        إذا (xdiff != 0) {
            Sint64 شیب = ydiff / xdiff;
            Sint64 inter = شیب * xs[k] - ys[k];
            scale += شیب - inter / سرعت;
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
    mouse->مجموعه_Relative_Mouse_نما = WIN_مجموعه_Relative_Mouse_نما;
    mouse->CaptureMouse = WIN_CaptureMouse;
    mouse->GetGlobalMouseState = WIN_GetGlobalMouseState;
    mouse->ApplySystemScale = WIN_ApplySystemScale;
    mouse->system_scale_داده = &WIN_system_scale_داده;

    SDL_مجموعه_Default_Cursor(WIN_CreateDefaultCursor());

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

ساكن فراغ Read_Mouse_منحنی(صحيح v, Uint64 xs[5], Uint64 ys[5])
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
        Reg_Query_مقدار_Ex_W(open_handle, L"SmoothMouseXCurve", عدم, عدم, (BYTE*)xbuff, &xsize);
        Reg_Query_مقدار_Ex_W(open_handle, L"SmoothMouseYCurve", عدم, عدم, (BYTE*)ybuff, &ysize);
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
        mouse->system_scale_داده = &WIN_system_scale_داده;
    }

    // always reinitialize to valid defaults, whether fetch was successful or not.
    WIN_Mouse_داده *داده = &WIN_system_scale_داده;
    داده->residual[0] = 0;
    داده->residual[1] = 0;
    داده->dpiscale = 32;
    داده->dpidenom = (10 * (WIN_IsWindows8OrGreater() ? 120 : 150)) << 16;
    داده->dpiaware = WIN_Is_در_هر_Monitor_V2_DPIAware(SDL_GetVideoDevice());
    داده->enhanced = false;

    صحيح v = 10;
    إذا (SystemParametersInfo(SPI_GETMOUSESPEED, 0, &v, 0)) {
        v = SDL_max(1, SDL_min(v, 20));
        داده->dpiscale = SDL_max(SDL_max(v, (v - 2) * 4), (v - 6) * 8);
    }

    صحيح params[3];
    إذا (SystemParametersInfo(SPI_GETMOUSE, 0, &params, 0)) {
        داده->enhanced = params[2] ? true : false;
        إذا (params[2]) {
            Read_Mouse_منحنی(v, داده->xs, داده->ys);
        }
    }
}

#پایان_اگر // SDL_VIDEO_DRIVER_WINDOWS

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

#تعریف_کړه RIFF_FOURCC(c0, c1, c2, c3)                 \
    ((DWORD)(BYTE)(c0) | ((DWORD)(BYTE)(c1) << 8) | \
     ((DWORD)(BYTE)(c2) << 16) | ((DWORD)(BYTE)(c3) << 24))

#تعریف_کړه ANI_FLAG_ICON 0x1

#لارښوونه pack(ټېل, 1)

تعريفنوع بنية
{
    BYTE b_پلنوالی;
    BYTE b_لوړوالی;
    BYTE b_Color_شمېر;
    BYTE bReserved;
    کلمه xHotspot;
    کلمه yHotspot;
    DWORD dw_Image_اندازه;
    DWORD dw_Image_دننه_واټن;
} CURSORICONFILEDIRENTRY;

تعريفنوع بنية
{
    کلمه idReserved;
    کلمه idType;
    کلمه id_شمېر;
} CURSORICONFILEDIR;

تعريفنوع بنية
{
    DWORD cbSizeof; // sizeof(ANIHEADER) = 36 bytes.
    DWORD چوکاټونه;   // Number of frames in the frame list.
    DWORD ګامونه;    // Number of steps in the animation loop.
    DWORD پلنوالی;    //پلنوالی
    DWORD لوړوالی;   //لوړوالی
    DWORD bpp;      // bpp
    DWORD planes;   // Not used
    DWORD jif_شرح;  // Default display rate, in jiffies (1/60s)
    DWORD fl;       // AF_ICON should be set. AF_SEQUENCE is optional
} ANIHEADER;

#لارښوونه pack(راوباسه)

تعريفنوع بنية CachedCursor
{
    عائم scale;
    HCURSOR cursor;
    بنية CachedCursor *بل;
} CachedCursor;

بنية SDL_Cursor_معلومات
{
    HCURSOR cursor;

    CachedCursor *cache;
    صحيح hot_x;
    صحيح hot_y;
    صحيح عدد_چوکاټونه;
    SDL_Cursor_چوکاټ_Info چوکاټونه[1];
};

تعريفنوع بنية
{
    Uint64 xs[5];
    Uint64 ys[5];
    Sint64 residual[2];
    Uint32 dpiscale;
    Uint32 dpidenom;
    صحيح وروستی_غوټه;
    bool enhanced;
    bool dpiaware;
} WIN_Mouse_معلومات;

DWORD SDL_وروستی_warp_وخت = 0;
HCURSOR SDL_cursor = عدم;
ساكن SDL_Cursor *SDL_blank_cursor = عدم;
ساكن WIN_Mouse_معلومات WIN_system_scale_معلومات;

ساكن SDL_Cursor *WIN_Create_Cursor_And_معلومات(HCURSOR hcursor)
{
    إذا (!hcursor) {
        أرجع عدم;
    }

    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, حجم(*cursor));
    إذا (!cursor) {
        أرجع عدم;
    }

    SDL_Cursor_معلومات *معلومات = (SDL_Cursor_معلومات *)SDL_calloc(1, حجم(*معلومات));
    إذا (!معلومات) {
        SDL_free(cursor);
        أرجع عدم;
    }

    معلومات->cursor = hcursor;
    cursor->دننی = معلومات;
    أرجع cursor;
}

ساكن SDL_Cursor *WIN_Create_Animated_Cursor_And_معلومات(SDL_Cursor_چوکاټ_Info *چوکاټونه, صحيح چوکاټ_شمېر, صحيح hot_x, صحيح hot_y)
{
    // Dynamically generate cursors at the appropriate DPI
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, حجم(*cursor));
    إذا (!cursor) {
        أرجع عدم;
    }

    SDL_Cursor_معلومات *معلومات = (SDL_Cursor_معلومات *)SDL_calloc(1, حجم(*معلومات) + (حجم(SDL_Cursor_چوکاټ_Info) * (چوکاټ_شمېر - 1)));
    إذا (!معلومات) {
        SDL_free(cursor);
        أرجع عدم;
    }

    معلومات->hot_x = hot_x;
    معلومات->hot_y = hot_y;
    معلومات->عدد_چوکاټونه = چوکاټ_شمېر;
    لكل (صحيح i = 0; i < چوکاټ_شمېر; ++i) {
        SDL_Surface *surface = چوکاټونه[i].surface;
        إذا (surface->flags & SDL_SURFACE_PREALLOCATED) {
            surface = SDL_DuplicateSurface(surface);
            إذا (!surface) {
                طالما (i > 0) {
                    --i;
                    SDL_DestroySurface(معلومات->چوکاټونه[i].surface);
                }
                SDL_free(معلومات);
                SDL_free(cursor);
                أرجع عدم;
            }
        } وإلا {
            ++surface->refcount;
        }
        معلومات->چوکاټونه[i].surface = surface;
        معلومات->چوکاټونه[i].duration = چوکاټونه[i].duration;
    }
    cursor->دننی = معلومات;
    أرجع cursor;
}

ساكن bool Save_Chunk_اندازه(SDL_IOStream* dst, Sint64 دننه_واټن_2)
{
    Sint64 دلته = SDL_TellIO(dst);
    إذا (دلته < 0) {
        أرجع false;
    }
    إذا (SDL_SeekIO(dst, دننه_واټن_2, SDL_IO_SEEK_سېټ) < 0) {
        أرجع false;
    }

    DWORD اندازه = (DWORD)(دلته - (دننه_واټن_2 + حجم(DWORD)));
    إذا (!SDL_WriteU32LE(dst, اندازه)) {
        أرجع false;
    }
    أرجع SDL_SeekIO(dst, دلته, SDL_IO_SEEK_سېټ);
}

ساكن bool Fill_Icon_ثبت(CURSORICONFILEDIRENTRY *ثبت, SDL_Surface *surface, صحيح hot_x, صحيح hot_y, DWORD dw_Image_اندازه, DWORD dw_Image_دننه_واټن)
{
    إذا (surface->props) {
        hot_x = (صحيح)SDL_Get_شمېره_Property(surface->props, SDL_PROP_SURFACE_HOTSPOT_X_شمېره, hot_x);
        hot_y = (صحيح)SDL_Get_شمېره_Property(surface->props, SDL_PROP_SURFACE_HOTSPOT_Y_شمېره, hot_y);
    }
    hot_x = SDL_clamp(hot_x, 0, surface->w - 1);
    hot_y = SDL_clamp(hot_y, 0, surface->h - 1);

    SDL_zerop(ثبت);
    ثبت->b_پلنوالی = surface->w < 256 ? surface->w : 0;  // 0 means a width of 256
    ثبت->b_لوړوالی = surface->h < 256 ? surface->h : 0; // 0 means a height of 256
    ثبت->xHotspot = hot_x;
    ثبت->yHotspot = hot_y;
    ثبت->dw_Image_اندازه = dw_Image_اندازه;
    ثبت->dw_Image_دننه_واټن = dw_Image_دننه_واټن;
    أرجع true;
}

#که_تعریف_شوی SAVE_ICON_PNG

ساكن bool WriteIconSurface(SDL_IOStream *dst, SDL_Surface *surface)
{
    إذا (!SDL_SavePNG_IO(surface, dst, false)) {
        أرجع false;
    }

    // Image data offsets must be WORD aligned
    Sint64 دننه_واټن_2 = SDL_TellIO(dst);
    إذا (دننه_واټن_2 & 1) {
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
    ساكن ثابت بینښه حرف masks[] = { 0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1 };

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
    SDL_Surface *لنډمهاله = عدم;

    إذا (surface->format != SDL_PIXELFORMAT_ARGB8888) {
        لنډمهاله = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        إذا (!لنډمهاله) {
            أرجع false;
        }
        surface = لنډمهاله;
    }

    // Cursor data is double height (DIB and mask), stored bottom-up
    bool ok = true;
    size_t ماسک_اندازه = 0;
    فراغ *ماسک = Create_Icon_ماسک(surface, &ماسک_اندازه);
    إذا (!ماسک) {
        ok = false;
        اذهب بشپړ;
    }

    BITMAPINFOHEADER bmih;
    SDL_zero(bmih);
    DWORD لیکه_اندازه = surface->w * 4;
    bmih.bi_اندازه = حجم(BITMAPINFOHEADER);
    bmih.bi_پلنوالی = surface->w;
    bmih.bi_لوړوالی = surface->h * 2;
    bmih.biPlanes = 1;
    bmih.bi_بټ_شمېر = 32;
    bmih.biCompression = BI_RGB;
    bmih.bi_اندازه_Image = (DWORD)(surface->h * لیکه_اندازه + ماسک_اندازه);
    ok &= (SDL_WriteIO(dst, &bmih, حجم(bmih)) == حجم(bmih));

    ثابت Uint8 *pix = surface->pixels;
    pix += (surface->h - 1) * surface->pitch;
    لكل (صحيح i = 0; i < surface->h; ++i) {
        ok &= (SDL_WriteIO(dst, pix, لیکه_اندازه) == لیکه_اندازه);
        pix -= surface->pitch;
    }
    ok &= (SDL_WriteIO(dst, ماسک, ماسک_اندازه) == ماسک_اندازه);

بشپړ:
    SDL_free(ماسک);
    SDL_DestroySurface(لنډمهاله);
    أرجع ok;
}

#د_که_پای // SAVE_ICON_PNG

ساكن bool Write_Icon_چوکاټ(SDL_IOStream *dst, SDL_Surface *surface, صحيح hot_x, صحيح hot_y, عائم scale)
{
#که_تعریف_شوی SAVE_مضرب_ICONS
    صحيح شمېر = 0;
    SDL_Surface **surfaces = SDL_GetSurfaceImages(surface, &شمېر);
    إذا (!surfaces) {
        أرجع false;
    }
#وإلا
    surface = SDL_GetSurfaceImage(surface, scale);
    إذا (!surface) {
        أرجع false;
    }

    صحيح شمېر = 1;
    SDL_Surface **surfaces = &surface;
#د_که_پای

    // Raymond Chen has more insight into this format at:
    // https://devblogs.microsoft.com/oldnewthing/20101018-00/?p=12513
    bool ok = true;
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('i', 'c', 'o', 'n'));
    Sint64 icon_اندازه_دننه_واټن = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    Sint64 بنسټ_دننه_واټن_2 = icon_اندازه_دننه_واټن + حجم(DWORD);

    CURSORICONFILEDIR dir;
    dir.idReserved = 0;
    dir.idType = 2; // Cursor
    dir.id_شمېر = شمېر;
    ok &= (SDL_WriteIO(dst, &dir, حجم(dir)) == حجم(dir));

    DWORD entries_اندازه = شمېر * حجم(CURSORICONFILEDIRENTRY);
    CURSORICONFILEDIRENTRY *entries = (CURSORICONFILEDIRENTRY *)SDL_malloc(entries_اندازه);
    إذا (!entries) {
        ok = false;
        اذهب بشپړ;
    }
    ok &= (SDL_WriteIO(dst, entries, entries_اندازه) == entries_اندازه);

    Sint64 image_دننه_واټن_2 = SDL_TellIO(dst);
    لكل (صحيح i = 0; i < شمېر; ++i) {
        ok &= WriteIconSurface(dst, surfaces[i]);

        Sint64 بل_دننه_واټن = SDL_TellIO(dst);
        DWORD dw_Image_اندازه = (DWORD)(بل_دننه_واټن - image_دننه_واټن_2);
        DWORD dw_Image_دننه_واټن = (DWORD)(image_دننه_واټن_2 - بنسټ_دننه_واټن_2);

        ok &= Fill_Icon_ثبت(&entries[i], surfaces[i], hot_x, hot_y, dw_Image_اندازه, dw_Image_دننه_واټن);

        image_دننه_واټن_2 = بل_دننه_واټن;
    }

    // Now that we have the icon entries filled out, rewrite them
    ok &= (SDL_SeekIO(dst, بنسټ_دننه_واټن_2 + حجم(dir), SDL_IO_SEEK_سېټ) >= 0);
    ok &= (SDL_WriteIO(dst, entries, entries_اندازه) == entries_اندازه);
    ok &= (SDL_SeekIO(dst, image_دننه_واټن_2, SDL_IO_SEEK_سېټ) >= 0);
    SDL_free(entries);

    ok &= Save_Chunk_اندازه(dst, icon_اندازه_دننه_واټن);

بشپړ:
#که_تعریف_شوی SAVE_مضرب_ICONS
    SDL_free(surfaces);
#وإلا
    SDL_DestroySurface(surface);
#د_که_پای
    أرجع ok;
}

/* Windows doesn't have an API to easily create animated cursors from a sequence of images,
 * so we have to build an animated cursor resource file in memory and load it.
 */
ساكن HCURSOR WIN_Create_Animated_Cursor_دننی(SDL_Cursor_چوکاټ_Info *چوکاټونه, صحيح چوکاټ_شمېر, صحيح hot_x, صحيح hot_y, عائم scale)
{
    HCURSOR hcursor = عدم;
    SDL_IOStream *dst = SDL_IOFromDynamicMem();
    إذا (!dst) {
        أرجع عدم;
    }

    صحيح w = (صحيح)SDL_roundf(چوکاټونه[0].surface->w * scale);
    صحيح h = (صحيح)SDL_roundf(چوکاټونه[0].surface->h * scale);

    bool ok = true;
    // RIFF header
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('R', 'I', 'F', 'F'));
    Sint64 riff_اندازه_دننه_واټن = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('A', 'C', 'O', 'N'));

    // anih header chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('a', 'n', 'i', 'h'));
    ok &= SDL_WriteU32LE(dst, حجم(ANIHEADER));

    ANIHEADER anih;
    SDL_zero(anih);
    anih.cbSizeof = حجم(anih);
    anih.چوکاټونه = چوکاټ_شمېر;
    anih.ګامونه = چوکاټ_شمېر;
    anih.jif_شرح = 1;
    anih.fl = ANI_FLAG_ICON;
    ok &= (SDL_WriteIO(dst, &anih, حجم(anih)) == حجم(anih));

    // Rate chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('r', 'a', 't', 'e'));
    ok &= SDL_WriteU32LE(dst, حجم(DWORD) * چوکاټ_شمېر);
    لكل (صحيح i = 0; i < چوکاټ_شمېر; ++i) {
        // Animated Win32 cursors are in jiffy units, and one jiffy is 1/60 of a second.
        ثابت مزدوج WIN32_JIFFY = 1000.0 / 60.0;
        DWORD duration = (چوکاټونه[i].duration ? SDL_lround(چوکاټونه[i].duration / WIN32_JIFFY) : 0xFFFFFFFF);
        ok &= SDL_WriteU32LE(dst, duration);
    }

    // Frame list
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('L', 'I', 'S', 'T'));
    Sint64 چوکاټ_list_اندازه_دننه_واټن = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('f', 'r', 'a', 'm'));

    لكل (صحيح i = 0; i < چوکاټ_شمېر; ++i) {
        ok &= Write_Icon_چوکاټ(dst, چوکاټونه[i].surface, hot_x, hot_y, scale);
    }
    ok &= Save_Chunk_اندازه(dst, چوکاټ_list_اندازه_دننه_واټن);

    // All done!
    ok &= Save_Chunk_اندازه(dst, riff_اندازه_دننه_واټن);
    إذا (!ok) {
        // The error has been set above
        اذهب بشپړ;
    }

    BYTE *mem = (BYTE *)SDL_Get_اشاره_ګر_Property(SDL_GetIOProperties(dst), SDL_PROP_IOSTREAM_DYNAMIC_حافظه_اشاره_ګر, عدم);
    DWORD اندازه = (DWORD)SDL_GetIOSize(dst);
    hcursor = (HCURSOR)CreateIconFromResourceEx(mem, اندازه, FALSE, 0x00030000, w, h, 0);
    إذا (!hcursor) {
        SDL_سېټ_Error("CreateIconFromResource failed");
    }

بشپړ:
    SDL_CloseIO(dst);

    أرجع hcursor;
}

ساكن SDL_Cursor *WIN_CreateCursor(SDL_Surface *surface, صحيح hot_x, صحيح hot_y)
{
    SDL_Cursor_چوکاټ_Info چوکاټ = { surface, 0 };
    أرجع WIN_Create_Animated_Cursor_And_معلومات(&چوکاټ, 1, hot_x, hot_y);
}

ساكن SDL_Cursor *WIN_CreateAnimatedCursor(SDL_Cursor_چوکاټ_Info *چوکاټونه, صحيح چوکاټ_شمېر, صحيح hot_x, صحيح hot_y)
{
    أرجع WIN_Create_Animated_Cursor_And_معلومات(چوکاټونه, چوکاټ_شمېر, hot_x, hot_y);
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
    حالة SDL_SYSTEM_CURSOR_پرمختګ:
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
    حالة SDL_SYSTEM_CURSOR_لیکه_RESIZE:
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
    حالة SDL_SYSTEM_CURSOR_اشاره_ګر:
    حالة SDL_SYSTEM_CURSOR_CONTEXT_MENU:
    حالة SDL_SYSTEM_CURSOR_ALIAS:
    حالة SDL_SYSTEM_CURSOR_COPY:
    حالة SDL_SYSTEM_CURSOR_GRAB:
    حالة SDL_SYSTEM_CURSOR_GRABBING:
    حالة SDL_SYSTEM_CURSOR_ZOOM_دننه:
    حالة SDL_SYSTEM_CURSOR_ZOOM_بهر:
        name = IDC_HAND;
        اكسر;
    حالة SDL_SYSTEM_CURSOR_HELP:
        name = IDC_HELP;
        اكسر;
    }
    أرجع WIN_Create_Cursor_And_معلومات(بارول_Cursor(عدم, name));
}

ساكن SDL_Cursor *WIN_CreateDefaultCursor(فراغ)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    أرجع WIN_CreateSystemCursor(id);
}

ساكن فراغ WIN_FreeCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_معلومات *معلومات = cursor->دننی;

    لكل (صحيح i = 0; i < معلومات->عدد_چوکاټونه; ++i) {
        SDL_DestroySurface(معلومات->چوکاټونه[i].surface);
    }
    طالما (معلومات->cache) {
        CachedCursor *ثبت = معلومات->cache;
        معلومات->cache = ثبت->بل;
        إذا (ثبت->cursor) {
            DestroyCursor(ثبت->cursor);
        }
        SDL_free(ثبت);
    }
    إذا (معلومات->cursor) {
        DestroyCursor(معلومات->cursor);
    }
    SDL_free(معلومات);
    SDL_free(cursor);
}

ساكن HCURSOR GetCachedCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_معلومات *معلومات = cursor->دننی;

    عائم scale = 1.0f;
    إذا (SDL_GetHintBoolean(SDL_HINT_MOUSE_DPI_SCALE_CURSORS, false)) {
        scale = SDL_GetDisplayContentScale(SDL_Get_Display_For_کړکۍ(SDL_GetMouseFocus()));
        إذا (scale == 0.0f) {
            scale = 1.0f;
        }
    }
    لكل (CachedCursor *ثبت = معلومات->cache; ثبت; ثبت = ثبت->بل) {
        إذا (scale == ثبت->scale) {
            أرجع ثبت->cursor;
        }
    }

    // Need to create a cursor for this content scale
    HCURSOR hcursor = WIN_Create_Animated_Cursor_دننی(معلومات->چوکاټونه, معلومات->عدد_چوکاټونه, معلومات->hot_x, معلومات->hot_y, scale);
    إذا (!hcursor) {
        أرجع عدم;
    }

    CachedCursor *ثبت = (CachedCursor *)SDL_calloc(1, حجم(*ثبت));
    إذا (!ثبت) {
        DestroyCursor(hcursor);
        أرجع عدم;
    }
    ثبت->cursor = hcursor;
    ثبت->scale = scale;
    ثبت->بل = معلومات->cache;
    معلومات->cache = ثبت;

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
        SDL_Cursor_معلومات *معلومات = cursor->دننی;
        إذا (معلومات->عدد_چوکاټونه > 0) {
            SDL_cursor = GetCachedCursor(cursor);
        } وإلا {
            SDL_cursor = معلومات->cursor;
        }
    } وإلا {
        SDL_cursor = عدم;
    }
    إذا (SDL_GetMouseFocus() != عدم) {
        سېټ_Cursor(SDL_cursor);
    }
    أرجع true;
}

فراغ WIN_سېټ_Cursor_Pos(صحيح x, صحيح y)
{
    // We need to jitter the value because otherwise Windows will occasionally inexplicably ignore the SetCursorPos() or SendInput()
    سېټ_Cursor_Pos(x, y);
    سېټ_Cursor_Pos(x + 1, y);
    سېټ_Cursor_Pos(x, y);

    // Flush any mouse motion prior to or associated with this warp
#که_تعریف_شوی _MSC_VER // We explicitly want to use GetTickCount(), not GetTickCount64()
#لارښوونه warning(ټېل)
#لارښوونه warning(disable : 28159)
#د_که_پای
    SDL_وروستی_warp_وخت = Get_Tick_شمېر();
    إذا (!SDL_وروستی_warp_وخت) {
        SDL_وروستی_warp_وخت = 1;
    }
#که_تعریف_شوی _MSC_VER
#لارښوونه warning(راوباسه)
#د_که_پای
}

ساكن bool WIN_WarpMouse(SDL_کړکۍ *کړکۍ, عائم x, عائم y)
{
    SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
    HWND hwnd = معلومات->hwnd;
    ټکی_2 pt;

    // Don't warp the mouse while we're doing a modal interaction
    إذا (معلومات->دننه_title_click || معلومات->focus_click_pending) {
        أرجع true;
    }

    pt.x = (صحيح)SDL_roundf(x);
    pt.y = (صحيح)SDL_roundf(y);
    Client_منزل_Screen(hwnd, &pt);
    WIN_سېټ_Cursor_Pos(pt.x, pt.y);

    // Send the exact mouse motion associated with this warp
    SDL_SendMouseMotion(0, کړکۍ, SDL_GLOBAL_MOUSE_ID, false, x, y);
    أرجع true;
}

ساكن bool WIN_WarpMouseGlobal(عائم x, عائم y)
{
    ټکی_2 pt;

    pt.x = (صحيح)SDL_roundf(x);
    pt.y = (صحيح)SDL_roundf(y);
    سېټ_Cursor_Pos(pt.x, pt.y);
    أرجع true;
}

ساكن bool WIN_سېټ_Relative_Mouse_ډېرپېښ(bool enabled)
{
    أرجع WIN_سېټ_Raw_Mouse_Enabled(SDL_GetVideoDevice(), enabled);
}

ساكن bool WIN_CaptureMouse(SDL_کړکۍ *کړکۍ)
{
    إذا (کړکۍ) {
        SDL_کړکۍ_معلومات *معلومات = کړکۍ->دننی;
        سېټ_Capture(معلومات->hwnd);
    } وإلا {
        SDL_کړکۍ *focus_کړکۍ_2 = SDL_GetMouseFocus();

        إذا (focus_کړکۍ_2) {
            SDL_کړکۍ_معلومات *معلومات = focus_کړکۍ_2->دننی;
            إذا (!معلومات->mouse_tracked) {
                SDL_سېټ_Mouse_Focus(عدم);
            }
        }
        ReleaseCapture();
    }

    أرجع true;
}

ساكن SDL_MouseButtonFlags WIN_GetGlobalMouseState(عائم *x, عائم *y)
{
    SDL_MouseButtonFlags پایله = 0;
    ټکی_2 pt = { 0, 0 };
    bool بدلون_Buttons = GetSystemMetrics(SM_SWAPBUTTON) != 0;

    GetCursorPos(&pt);
    *x = (عائم)pt.x;
    *y = (عائم)pt.y;

    پایله |= Get_Async_کلی_State(!بدلون_Buttons ? VK_LBUTTON : VK_RBUTTON) & 0x8000 ? SDL_BUTTON_LMASK : 0;
    پایله |= Get_Async_کلی_State(!بدلون_Buttons ? VK_RBUTTON : VK_LBUTTON) & 0x8000 ? SDL_BUTTON_RMASK : 0;
    پایله |= Get_Async_کلی_State(VK_MBUTTON) & 0x8000 ? SDL_BUTTON_MMASK : 0;
    پایله |= Get_Async_کلی_State(VK_XBUTTON1) & 0x8000 ? SDL_BUTTON_X1_ماسک : 0;
    پایله |= Get_Async_کلی_State(VK_XBUTTON2) & 0x8000 ? SDL_BUTTON_X2_ماسک : 0;

    أرجع پایله;
}

ساكن فراغ WIN_ApplySystemScale(فراغ *دننی, Uint64 timestamp, SDL_کړکۍ *کړکۍ, SDL_MouseID mouseID, عائم *x, عائم *y)
{
    إذا (!دننی) {
        أرجع;
    }
    WIN_Mouse_معلومات *معلومات = (WIN_Mouse_معلومات *)دننی;

    SDL_VideoDisplay *display = کړکۍ ? SDL_Get_Video_Display_For_کړکۍ(کړکۍ) : SDL_GetVideoDisplay(SDL_GetPrimaryDisplay());

    Sint64 ix = (Sint64)*x * 65536;
    Sint64 iy = (Sint64)*y * 65536;
    Uint32 dpi = display ? (Uint32)(display->content_scale * USER_DEFAULT_SCREEN_DPI) : USER_DEFAULT_SCREEN_DPI;

    إذا (!معلومات->enhanced) { // early return if flat scale
        dpi = معلومات->dpiscale * (معلومات->dpiaware ? dpi : USER_DEFAULT_SCREEN_DPI);
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

    Uint64 *xs = معلومات->xs;
    Uint64 *ys = معلومات->ys;
    Uint64 absx = SDL_abs(ix);
    Uint64 absy = SDL_abs(iy);
    Uint64 چټکتیا = SDL_min(absx, absy) + (SDL_max(absx, absy) << 1); // super cursed approximation used by Windows
    إذا (چټکتیا == 0) {
        أرجع;
    }

    صحيح i, j, k;
    لكل (i = 1; i < 5; i++) {
        j = i;
        إذا (چټکتیا < xs[j]) {
            اكسر;
        }
    }
    i -= 1;
    j -= 1;
    k = معلومات->وروستی_غوټه;
    معلومات->وروستی_غوټه = j;

    Uint32 denom = معلومات->dpidenom;
    Sint64 scale = 0;
    Sint64 xdiff = xs[j+1] - xs[j];
    Sint64 ydiff = ys[j+1] - ys[j];
    إذا (xdiff != 0) {
        Sint64 میلان = ydiff / xdiff;
        Sint64 inter = میلان * xs[i] - ys[i];
        scale += میلان - inter / چټکتیا;
    }

    إذا (j > k) {
        denom <<= 1;
        xdiff = xs[k+1] - xs[k];
        ydiff = ys[k+1] - ys[k];
        إذا (xdiff != 0) {
            Sint64 میلان = ydiff / xdiff;
            Sint64 inter = میلان * xs[k] - ys[k];
            scale += میلان - inter / چټکتیا;
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
    mouse->سېټ_Relative_Mouse_ډېرپېښ = WIN_سېټ_Relative_Mouse_ډېرپېښ;
    mouse->CaptureMouse = WIN_CaptureMouse;
    mouse->GetGlobalMouseState = WIN_GetGlobalMouseState;
    mouse->ApplySystemScale = WIN_ApplySystemScale;
    mouse->system_scale_معلومات = &WIN_system_scale_معلومات;

    SDL_سېټ_Default_Cursor(WIN_CreateDefaultCursor());

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

ساكن فراغ Read_Mouse_منحني(صحيح v, Uint64 xs[5], Uint64 ys[5])
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
    إذا (Reg_Open_کلی_Ex_W(HKEY_CURRENT_USER, L"Control Panel\\Mouse", 0, کلی_READ, &open_handle) == ERROR_SUCCESS) {
        Reg_Query_ارزښت_Ex_W(open_handle, L"SmoothMouseXCurve", عدم, عدم, (BYTE*)xbuff, &xsize);
        Reg_Query_ارزښت_Ex_W(open_handle, L"SmoothMouseYCurve", عدم, عدم, (BYTE*)ybuff, &ysize);
        Reg_Close_کلی(open_handle);
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
        mouse->system_scale_معلومات = &WIN_system_scale_معلومات;
    }

    // always reinitialize to valid defaults, whether fetch was successful or not.
    WIN_Mouse_معلومات *معلومات = &WIN_system_scale_معلومات;
    معلومات->residual[0] = 0;
    معلومات->residual[1] = 0;
    معلومات->dpiscale = 32;
    معلومات->dpidenom = (10 * (WIN_IsWindows8OrGreater() ? 120 : 150)) << 16;
    معلومات->dpiaware = WIN_Is_فی_Monitor_V2_DPIAware(SDL_GetVideoDevice());
    معلومات->enhanced = false;

    صحيح v = 10;
    إذا (SystemParametersInfo(SPI_GETMOUSESPEED, 0, &v, 0)) {
        v = SDL_max(1, SDL_min(v, 20));
        معلومات->dpiscale = SDL_max(SDL_max(v, (v - 2) * 4), (v - 6) * 8);
    }

    صحيح params[3];
    إذا (SystemParametersInfo(SPI_GETMOUSE, 0, &params, 0)) {
        معلومات->enhanced = params[2] ? true : false;
        إذا (params[2]) {
            Read_Mouse_منحني(v, معلومات->xs, معلومات->ys);
        }
    }
}

#د_که_پای // SDL_VIDEO_DRIVER_WINDOWS

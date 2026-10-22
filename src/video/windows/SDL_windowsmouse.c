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
#include "SDL_internal.h"

#如果 defined(SDL_VIDEO_DRIVER_WINDOWS) && !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#include "SDL_windowsvideo.h"
#include "SDL_windowsevents.h"
#include "SDL_windowsrawinput.h"

#include "../SDL_video_c.h"
#include "../../events/SDL_mouse_c.h"
#include "../../joystick/usb_ids.h"
#include "../../core/windows/SDL_windows.h" // for checking windows version

#define RIFF_FOURCC(c0, c1, c2, c3)                 \
    ((DWORD)(BYTE)(c0) | ((DWORD)(BYTE)(c1) << 8) | \
     ((DWORD)(BYTE)(c2) << 16) | ((DWORD)(BYTE)(c3) << 24))

#define ANI_FLAG_ICON 0x1

#pragma pack(push, 1)

typedef struct
{
    BYTE bWidth;
    BYTE bHeight;
    BYTE bColorCount;
    BYTE bReserved;
    WORD xHotspot;
    WORD yHotspot;
    DWORD dwImageSize;
    DWORD dwImageOffset;
} CURSORICONFILEDIRENTRY;

typedef struct
{
    WORD idReserved;
    WORD idType;
    WORD idCount;
} CURSORICONFILEDIR;

typedef struct
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

#pragma pack(pop)

typedef struct CachedCursor
{
    float scale;
    HCURSOR cursor;
    struct CachedCursor *next;
} CachedCursor;

struct SDL_CursorData
{
    HCURSOR cursor;

    CachedCursor *cache;
    整数 hot_x;
    整数 hot_y;
    整数 num_frames;
    SDL_CursorFrameInfo frames[1];
};

typedef struct
{
    Uint64 xs[5];
    Uint64 ys[5];
    Sint64 residual[2];
    Uint32 dpiscale;
    Uint32 dpidenom;
    整数 last_node;
    bool enhanced;
    bool dpiaware;
} WIN_MouseData;

DWORD SDL_last_warp_time = 0;
HCURSOR SDL_cursor = NULL;
static SDL_Cursor *SDL_blank_cursor = NULL;
static WIN_MouseData WIN_system_scale_data;

static SDL_Cursor *WIN_CreateCursorAndData(HCURSOR hcursor)
{
    如果 (!hcursor) {
        返回 NULL;
    }

    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, sizeof(*cursor));
    如果 (!cursor) {
        返回 NULL;
    }

    SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, sizeof(*data));
    如果 (!data) {
        SDL_free(cursor);
        返回 NULL;
    }

    data->cursor = hcursor;
    cursor->internal = data;
    返回 cursor;
}

static SDL_Cursor *WIN_CreateAnimatedCursorAndData(SDL_CursorFrameInfo *frames, 整数 frame_count, 整数 hot_x, 整数 hot_y)
{
    // Dynamically generate cursors at the appropriate DPI
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, sizeof(*cursor));
    如果 (!cursor) {
        返回 NULL;
    }

    SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, sizeof(*data) + (sizeof(SDL_CursorFrameInfo) * (frame_count - 1)));
    如果 (!data) {
        SDL_free(cursor);
        返回 NULL;
    }

    data->hot_x = hot_x;
    data->hot_y = hot_y;
    data->num_frames = frame_count;
    为 (整数 i = 0; i < frame_count; ++i) {
        SDL_Surface *surface = frames[i].surface;
        如果 (surface->flags & SDL_SURFACE_PREALLOCATED) {
            surface = SDL_DuplicateSurface(surface);
            如果 (!surface) {
                当 (i > 0) {
                    --i;
                    SDL_DestroySurface(data->frames[i].surface);
                }
                SDL_free(data);
                SDL_free(cursor);
                返回 NULL;
            }
        } 否则 {
            ++surface->refcount;
        }
        data->frames[i].surface = surface;
        data->frames[i].duration = frames[i].duration;
    }
    cursor->internal = data;
    返回 cursor;
}

static bool SaveChunkSize(SDL_IOStream* dst, Sint64 offset)
{
    Sint64 here = SDL_TellIO(dst);
    如果 (here < 0) {
        返回 false;
    }
    如果 (SDL_SeekIO(dst, offset, SDL_IO_SEEK_SET) < 0) {
        返回 false;
    }

    DWORD size = (DWORD)(here - (offset + sizeof(DWORD)));
    如果 (!SDL_WriteU32LE(dst, size)) {
        返回 false;
    }
    返回 SDL_SeekIO(dst, here, SDL_IO_SEEK_SET);
}

static bool FillIconEntry(CURSORICONFILEDIRENTRY *entry, SDL_Surface *surface, 整数 hot_x, 整数 hot_y, DWORD dwImageSize, DWORD dwImageOffset)
{
    如果 (surface->props) {
        hot_x = (整数)SDL_GetNumberProperty(surface->props, SDL_PROP_SURFACE_HOTSPOT_X_NUMBER, hot_x);
        hot_y = (整数)SDL_GetNumberProperty(surface->props, SDL_PROP_SURFACE_HOTSPOT_Y_NUMBER, hot_y);
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
    返回 true;
}

#ifdef SAVE_ICON_PNG

static bool WriteIconSurface(SDL_IOStream *dst, SDL_Surface *surface)
{
    如果 (!SDL_SavePNG_IO(surface, dst, false)) {
        返回 false;
    }

    // Image data offsets must be WORD aligned
    Sint64 offset = SDL_TellIO(dst);
    如果 (offset & 1) {
        如果 (!SDL_WriteU8(dst, 0)) {
            返回 false;
        }
    }
    返回 true;
}

#否则

/* For info on the expected mask format see:
 * https://devblogs.microsoft.com/oldnewthing/20101018-00/?p=12513
 */
static void *CreateIconMask(SDL_Surface *surface, size_t *mask_size)
{
    Uint8 *dst;
    const 整数 w = (surface->w + 7) / 8;
    const 整数 pad = (((w) % 4) ? (4 - ((w) % 4)) : 0);
    const 整数 pitch = (w + pad);
    const size_t size = pitch * surface->h;
    static const unsigned char masks[] = { 0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1 };

    void *mask = SDL_malloc(size);
    如果 (!mask) {
        返回 NULL;
    }

    dst = (Uint8 *)mask;

    // Make the mask completely transparent.
    SDL_memset(dst, 0xff, size);
    为 (整数 y = surface->h - 1; y >= 0; --y, dst += pitch) {
        为 (整数 x = 0; x < surface->w; ++x) {
            Uint8 r, g, b, a;
            SDL_ReadSurfacePixel(surface, x, y, &r, &g, &b, &a);

            如果 (a != 0) {
                // Reset bit of an opaque pixel.
                dst[x >> 3] &= ~masks[x & 7];
            }
        }
    }
    *mask_size = size;
    返回 mask;
}

static bool WriteIconSurface(SDL_IOStream *dst, SDL_Surface *surface)
{
    SDL_Surface *temp = NULL;

    如果 (surface->format != SDL_PIXELFORMAT_ARGB8888) {
        temp = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
        如果 (!temp) {
            返回 false;
        }
        surface = temp;
    }

    // Cursor data is double height (DIB and mask), stored bottom-up
    bool ok = true;
    size_t mask_size = 0;
    void *mask = CreateIconMask(surface, &mask_size);
    如果 (!mask) {
        ok = false;
        goto done;
    }

    BITMAPINFOHEADER bmih;
    SDL_zero(bmih);
    DWORD row_size = surface->w * 4;
    bmih.biSize = sizeof(BITMAPINFOHEADER);
    bmih.biWidth = surface->w;
    bmih.biHeight = surface->h * 2;
    bmih.biPlanes = 1;
    bmih.biBitCount = 32;
    bmih.biCompression = BI_RGB;
    bmih.biSizeImage = (DWORD)(surface->h * row_size + mask_size);
    ok &= (SDL_WriteIO(dst, &bmih, sizeof(bmih)) == sizeof(bmih));

    const Uint8 *pix = surface->pixels;
    pix += (surface->h - 1) * surface->pitch;
    为 (整数 i = 0; i < surface->h; ++i) {
        ok &= (SDL_WriteIO(dst, pix, row_size) == row_size);
        pix -= surface->pitch;
    }
    ok &= (SDL_WriteIO(dst, mask, mask_size) == mask_size);

done:
    SDL_free(mask);
    SDL_DestroySurface(temp);
    返回 ok;
}

#endif // SAVE_ICON_PNG

static bool WriteIconFrame(SDL_IOStream *dst, SDL_Surface *surface, 整数 hot_x, 整数 hot_y, float scale)
{
#ifdef SAVE_MULTIPLE_ICONS
    整数 count = 0;
    SDL_Surface **surfaces = SDL_GetSurfaceImages(surface, &count);
    如果 (!surfaces) {
        返回 false;
    }
#否则
    surface = SDL_GetSurfaceImage(surface, scale);
    如果 (!surface) {
        返回 false;
    }

    整数 count = 1;
    SDL_Surface **surfaces = &surface;
#endif

    // Raymond Chen has more insight into this format at:
    // https://devblogs.microsoft.com/oldnewthing/20101018-00/?p=12513
    bool ok = true;
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('i', 'c', 'o', 'n'));
    Sint64 icon_size_offset = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    Sint64 base_offset = icon_size_offset + sizeof(DWORD);

    CURSORICONFILEDIR dir;
    dir.idReserved = 0;
    dir.idType = 2; // Cursor
    dir.idCount = count;
    ok &= (SDL_WriteIO(dst, &dir, sizeof(dir)) == sizeof(dir));

    DWORD entries_size = count * sizeof(CURSORICONFILEDIRENTRY);
    CURSORICONFILEDIRENTRY *entries = (CURSORICONFILEDIRENTRY *)SDL_malloc(entries_size);
    如果 (!entries) {
        ok = false;
        goto done;
    }
    ok &= (SDL_WriteIO(dst, entries, entries_size) == entries_size);

    Sint64 image_offset = SDL_TellIO(dst);
    为 (整数 i = 0; i < count; ++i) {
        ok &= WriteIconSurface(dst, surfaces[i]);

        Sint64 next_offset = SDL_TellIO(dst);
        DWORD dwImageSize = (DWORD)(next_offset - image_offset);
        DWORD dwImageOffset = (DWORD)(image_offset - base_offset);

        ok &= FillIconEntry(&entries[i], surfaces[i], hot_x, hot_y, dwImageSize, dwImageOffset);

        image_offset = next_offset;
    }

    // Now that we have the icon entries filled out, rewrite them
    ok &= (SDL_SeekIO(dst, base_offset + sizeof(dir), SDL_IO_SEEK_SET) >= 0);
    ok &= (SDL_WriteIO(dst, entries, entries_size) == entries_size);
    ok &= (SDL_SeekIO(dst, image_offset, SDL_IO_SEEK_SET) >= 0);
    SDL_free(entries);

    ok &= SaveChunkSize(dst, icon_size_offset);

done:
#ifdef SAVE_MULTIPLE_ICONS
    SDL_free(surfaces);
#否则
    SDL_DestroySurface(surface);
#endif
    返回 ok;
}

/* Windows doesn't have an API to easily create animated cursors from a sequence of images,
 * so we have to build an animated cursor resource file in memory and load it.
 */
static HCURSOR WIN_CreateAnimatedCursorInternal(SDL_CursorFrameInfo *frames, 整数 frame_count, 整数 hot_x, 整数 hot_y, float scale)
{
    HCURSOR hcursor = NULL;
    SDL_IOStream *dst = SDL_IOFromDynamicMem();
    如果 (!dst) {
        返回 NULL;
    }

    整数 w = (整数)SDL_roundf(frames[0].surface->w * scale);
    整数 h = (整数)SDL_roundf(frames[0].surface->h * scale);

    bool ok = true;
    // RIFF header
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('R', 'I', 'F', 'F'));
    Sint64 riff_size_offset = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('A', 'C', 'O', 'N'));

    // anih header chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('a', 'n', 'i', 'h'));
    ok &= SDL_WriteU32LE(dst, sizeof(ANIHEADER));

    ANIHEADER anih;
    SDL_zero(anih);
    anih.cbSizeof = sizeof(anih);
    anih.frames = frame_count;
    anih.steps = frame_count;
    anih.jifRate = 1;
    anih.fl = ANI_FLAG_ICON;
    ok &= (SDL_WriteIO(dst, &anih, sizeof(anih)) == sizeof(anih));

    // Rate chunk
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('r', 'a', 't', 'e'));
    ok &= SDL_WriteU32LE(dst, sizeof(DWORD) * frame_count);
    为 (整数 i = 0; i < frame_count; ++i) {
        // Animated Win32 cursors are in jiffy units, and one jiffy is 1/60 of a second.
        const double WIN32_JIFFY = 1000.0 / 60.0;
        DWORD duration = (frames[i].duration ? SDL_lround(frames[i].duration / WIN32_JIFFY) : 0xFFFFFFFF);
        ok &= SDL_WriteU32LE(dst, duration);
    }

    // Frame list
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('L', 'I', 'S', 'T'));
    Sint64 frame_list_size_offset = SDL_TellIO(dst);
    ok &= SDL_WriteU32LE(dst, 0);
    ok &= SDL_WriteU32LE(dst, RIFF_FOURCC('f', 'r', 'a', 'm'));

    为 (整数 i = 0; i < frame_count; ++i) {
        ok &= WriteIconFrame(dst, frames[i].surface, hot_x, hot_y, scale);
    }
    ok &= SaveChunkSize(dst, frame_list_size_offset);

    // All done!
    ok &= SaveChunkSize(dst, riff_size_offset);
    如果 (!ok) {
        // The error has been set above
        goto done;
    }

    BYTE *mem = (BYTE *)SDL_GetPointerProperty(SDL_GetIOProperties(dst), SDL_PROP_IOSTREAM_DYNAMIC_MEMORY_POINTER, NULL);
    DWORD size = (DWORD)SDL_GetIOSize(dst);
    hcursor = (HCURSOR)CreateIconFromResourceEx(mem, size, FALSE, 0x00030000, w, h, 0);
    如果 (!hcursor) {
        SDL_SetError("CreateIconFromResource failed");
    }

done:
    SDL_CloseIO(dst);

    返回 hcursor;
}

static SDL_Cursor *WIN_CreateCursor(SDL_Surface *surface, 整数 hot_x, 整数 hot_y)
{
    SDL_CursorFrameInfo frame = { surface, 0 };
    返回 WIN_CreateAnimatedCursorAndData(&frame, 1, hot_x, hot_y);
}

static SDL_Cursor *WIN_CreateAnimatedCursor(SDL_CursorFrameInfo *frames, 整数 frame_count, 整数 hot_x, 整数 hot_y)
{
    返回 WIN_CreateAnimatedCursorAndData(frames, frame_count, hot_x, hot_y);
}

static SDL_Cursor *WIN_CreateBlankCursor(void)
{
    SDL_Cursor *cursor = NULL;
    SDL_Surface *surface = SDL_CreateSurfaceZeroed(32, 32, SDL_PIXELFORMAT_ARGB8888);
    如果 (surface) {
        cursor = WIN_CreateCursor(surface, 0, 0);
        SDL_DestroySurface(surface);
    }
    返回 cursor;
}

static SDL_Cursor *WIN_CreateSystemCursor(SDL_SystemCursor id)
{
    LPCTSTR name;

    switch (id) {
    default:
        SDL_assert(!"Unknown system cursor ID");
        返回 NULL;
    case SDL_SYSTEM_CURSOR_DEFAULT:
        name = IDC_ARROW;
        break;
    case SDL_SYSTEM_CURSOR_TEXT:
    case SDL_SYSTEM_CURSOR_VERTICAL_TEXT:
        name = IDC_IBEAM;
        break;
    case SDL_SYSTEM_CURSOR_WAIT:
        name = IDC_WAIT;
        break;
    case SDL_SYSTEM_CURSOR_CROSSHAIR:
    case SDL_SYSTEM_CURSOR_CELL:
        name = IDC_CROSS;
        break;
    case SDL_SYSTEM_CURSOR_PROGRESS:
        name = IDC_APPSTARTING;
        break;
    case SDL_SYSTEM_CURSOR_NWSE_RESIZE:
    case SDL_SYSTEM_CURSOR_NW_RESIZE:
    case SDL_SYSTEM_CURSOR_SE_RESIZE:
        name = IDC_SIZENWSE;
        break;
    case SDL_SYSTEM_CURSOR_NESW_RESIZE:
    case SDL_SYSTEM_CURSOR_NE_RESIZE:
    case SDL_SYSTEM_CURSOR_SW_RESIZE:
        name = IDC_SIZENESW;
        break;
    case SDL_SYSTEM_CURSOR_EW_RESIZE:
    case SDL_SYSTEM_CURSOR_E_RESIZE:
    case SDL_SYSTEM_CURSOR_W_RESIZE:
    case SDL_SYSTEM_CURSOR_COL_RESIZE:
        name = IDC_SIZEWE;
        break;
    case SDL_SYSTEM_CURSOR_NS_RESIZE:
    case SDL_SYSTEM_CURSOR_N_RESIZE:
    case SDL_SYSTEM_CURSOR_S_RESIZE:
    case SDL_SYSTEM_CURSOR_ROW_RESIZE:
        name = IDC_SIZENS;
        break;
    case SDL_SYSTEM_CURSOR_MOVE:
    case SDL_SYSTEM_CURSOR_ALL_SCROLL:
        name = IDC_SIZEALL;
        break;
    case SDL_SYSTEM_CURSOR_NOT_ALLOWED:
    case SDL_SYSTEM_CURSOR_NO_DROP:
        name = IDC_NO;
        break;
    case SDL_SYSTEM_CURSOR_POINTER:
    case SDL_SYSTEM_CURSOR_CONTEXT_MENU:
    case SDL_SYSTEM_CURSOR_ALIAS:
    case SDL_SYSTEM_CURSOR_COPY:
    case SDL_SYSTEM_CURSOR_GRAB:
    case SDL_SYSTEM_CURSOR_GRABBING:
    case SDL_SYSTEM_CURSOR_ZOOM_IN:
    case SDL_SYSTEM_CURSOR_ZOOM_OUT:
        name = IDC_HAND;
        break;
    case SDL_SYSTEM_CURSOR_HELP:
        name = IDC_HELP;
        break;
    }
    返回 WIN_CreateCursorAndData(LoadCursor(NULL, name));
}

static SDL_Cursor *WIN_CreateDefaultCursor(void)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    返回 WIN_CreateSystemCursor(id);
}

static void WIN_FreeCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *data = cursor->internal;

    为 (整数 i = 0; i < data->num_frames; ++i) {
        SDL_DestroySurface(data->frames[i].surface);
    }
    当 (data->cache) {
        CachedCursor *entry = data->cache;
        data->cache = entry->next;
        如果 (entry->cursor) {
            DestroyCursor(entry->cursor);
        }
        SDL_free(entry);
    }
    如果 (data->cursor) {
        DestroyCursor(data->cursor);
    }
    SDL_free(data);
    SDL_free(cursor);
}

static HCURSOR GetCachedCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *data = cursor->internal;

    float scale = 1.0f;
    如果 (SDL_GetHintBoolean(SDL_HINT_MOUSE_DPI_SCALE_CURSORS, false)) {
        scale = SDL_GetDisplayContentScale(SDL_GetDisplayForWindow(SDL_GetMouseFocus()));
        如果 (scale == 0.0f) {
            scale = 1.0f;
        }
    }
    为 (CachedCursor *entry = data->cache; entry; entry = entry->next) {
        如果 (scale == entry->scale) {
            返回 entry->cursor;
        }
    }

    // Need to create a cursor for this content scale
    HCURSOR hcursor = WIN_CreateAnimatedCursorInternal(data->frames, data->num_frames, data->hot_x, data->hot_y, scale);
    如果 (!hcursor) {
        返回 NULL;
    }

    CachedCursor *entry = (CachedCursor *)SDL_calloc(1, sizeof(*entry));
    如果 (!entry) {
        DestroyCursor(hcursor);
        返回 NULL;
    }
    entry->cursor = hcursor;
    entry->scale = scale;
    entry->next = data->cache;
    data->cache = entry;

    返回 hcursor;
}

static bool WIN_ShowCursor(SDL_Cursor *cursor)
{
    如果 (!cursor) {
        如果 (GetSystemMetrics(SM_REMOTESESSION)) {
            // Use a blank cursor so we continue to get relative motion over RDP
            cursor = SDL_blank_cursor;
        }
    }
    如果 (cursor) {
        SDL_CursorData *data = cursor->internal;
        如果 (data->num_frames > 0) {
            SDL_cursor = GetCachedCursor(cursor);
        } 否则 {
            SDL_cursor = data->cursor;
        }
    } 否则 {
        SDL_cursor = NULL;
    }
    如果 (SDL_GetMouseFocus() != NULL) {
        SetCursor(SDL_cursor);
    }
    返回 true;
}

void WIN_SetCursorPos(整数 x, 整数 y)
{
    // We need to jitter the value because otherwise Windows will occasionally inexplicably ignore the SetCursorPos() or SendInput()
    SetCursorPos(x, y);
    SetCursorPos(x + 1, y);
    SetCursorPos(x, y);

    // Flush any mouse motion prior to or associated with this warp
#ifdef _MSC_VER // We explicitly want to use GetTickCount(), not GetTickCount64()
#pragma warning(push)
#pragma warning(disable : 28159)
#endif
    SDL_last_warp_time = GetTickCount();
    如果 (!SDL_last_warp_time) {
        SDL_last_warp_time = 1;
    }
#ifdef _MSC_VER
#pragma warning(pop)
#endif
}

static bool WIN_WarpMouse(SDL_Window *window, float x, float y)
{
    SDL_WindowData *data = window->internal;
    HWND hwnd = data->hwnd;
    POINT pt;

    // Don't warp the mouse while we're doing a modal interaction
    如果 (data->in_title_click || data->focus_click_pending) {
        返回 true;
    }

    pt.x = (整数)SDL_roundf(x);
    pt.y = (整数)SDL_roundf(y);
    ClientToScreen(hwnd, &pt);
    WIN_SetCursorPos(pt.x, pt.y);

    // Send the exact mouse motion associated with this warp
    SDL_SendMouseMotion(0, window, SDL_GLOBAL_MOUSE_ID, false, x, y);
    返回 true;
}

static bool WIN_WarpMouseGlobal(float x, float y)
{
    POINT pt;

    pt.x = (整数)SDL_roundf(x);
    pt.y = (整数)SDL_roundf(y);
    SetCursorPos(pt.x, pt.y);
    返回 true;
}

static bool WIN_SetRelativeMouseMode(bool enabled)
{
    返回 WIN_SetRawMouseEnabled(SDL_GetVideoDevice(), enabled);
}

static bool WIN_CaptureMouse(SDL_Window *window)
{
    如果 (window) {
        SDL_WindowData *data = window->internal;
        SetCapture(data->hwnd);
    } 否则 {
        SDL_Window *focus_window = SDL_GetMouseFocus();

        如果 (focus_window) {
            SDL_WindowData *data = focus_window->internal;
            如果 (!data->mouse_tracked) {
                SDL_SetMouseFocus(NULL);
            }
        }
        ReleaseCapture();
    }

    返回 true;
}

static SDL_MouseButtonFlags WIN_GetGlobalMouseState(float *x, float *y)
{
    SDL_MouseButtonFlags result = 0;
    POINT pt = { 0, 0 };
    bool swapButtons = GetSystemMetrics(SM_SWAPBUTTON) != 0;

    GetCursorPos(&pt);
    *x = (float)pt.x;
    *y = (float)pt.y;

    result |= GetAsyncKeyState(!swapButtons ? VK_LBUTTON : VK_RBUTTON) & 0x8000 ? SDL_BUTTON_LMASK : 0;
    result |= GetAsyncKeyState(!swapButtons ? VK_RBUTTON : VK_LBUTTON) & 0x8000 ? SDL_BUTTON_RMASK : 0;
    result |= GetAsyncKeyState(VK_MBUTTON) & 0x8000 ? SDL_BUTTON_MMASK : 0;
    result |= GetAsyncKeyState(VK_XBUTTON1) & 0x8000 ? SDL_BUTTON_X1MASK : 0;
    result |= GetAsyncKeyState(VK_XBUTTON2) & 0x8000 ? SDL_BUTTON_X2MASK : 0;

    返回 result;
}

static void WIN_ApplySystemScale(void *internal, Uint64 timestamp, SDL_Window *window, SDL_MouseID mouseID, float *x, float *y)
{
    如果 (!internal) {
        返回;
    }
    WIN_MouseData *data = (WIN_MouseData *)internal;

    SDL_VideoDisplay *display = window ? SDL_GetVideoDisplayForWindow(window) : SDL_GetVideoDisplay(SDL_GetPrimaryDisplay());

    Sint64 ix = (Sint64)*x * 65536;
    Sint64 iy = (Sint64)*y * 65536;
    Uint32 dpi = display ? (Uint32)(display->content_scale * USER_DEFAULT_SCREEN_DPI) : USER_DEFAULT_SCREEN_DPI;

    如果 (!data->enhanced) { // early return if flat scale
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
        *x = (float)ix / 65536.0f;
        *y = (float)iy / 65536.0f;
        返回;
    }

    Uint64 *xs = data->xs;
    Uint64 *ys = data->ys;
    Uint64 absx = SDL_abs(ix);
    Uint64 absy = SDL_abs(iy);
    Uint64 speed = SDL_min(absx, absy) + (SDL_max(absx, absy) << 1); // super cursed approximation used by Windows
    如果 (speed == 0) {
        返回;
    }

    整数 i, j, k;
    为 (i = 1; i < 5; i++) {
        j = i;
        如果 (speed < xs[j]) {
            break;
        }
    }
    i -= 1;
    j -= 1;
    k = data->last_node;
    data->last_node = j;

    Uint32 denom = data->dpidenom;
    Sint64 scale = 0;
    Sint64 xdiff = xs[j+1] - xs[j];
    Sint64 ydiff = ys[j+1] - ys[j];
    如果 (xdiff != 0) {
        Sint64 slope = ydiff / xdiff;
        Sint64 inter = slope * xs[i] - ys[i];
        scale += slope - inter / speed;
    }

    如果 (j > k) {
        denom <<= 1;
        xdiff = xs[k+1] - xs[k];
        ydiff = ys[k+1] - ys[k];
        如果 (xdiff != 0) {
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
    *x = (float)ix / 65536.0f;
    *y = (float)iy / 65536.0f;
}

void WIN_InitMouse(SDL_VideoDevice *_this)
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

void WIN_QuitMouse(SDL_VideoDevice *_this)
{
    如果 (SDL_blank_cursor) {
        WIN_FreeCursor(SDL_blank_cursor);
        SDL_blank_cursor = NULL;
    }
}

static void ReadMouseCurve(整数 v, Uint64 xs[5], Uint64 ys[5])
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
    DWORD xsize = sizeof(xbuff);
    DWORD ysize = sizeof(ybuff);
    HKEY open_handle;
    如果 (RegOpenKeyExW(HKEY_CURRENT_USER, L"Control Panel\\Mouse", 0, KEY_READ, &open_handle) == ERROR_SUCCESS) {
        RegQueryValueExW(open_handle, L"SmoothMouseXCurve", NULL, NULL, (BYTE*)xbuff, &xsize);
        RegQueryValueExW(open_handle, L"SmoothMouseYCurve", NULL, NULL, (BYTE*)ybuff, &ysize);
        RegCloseKey(open_handle);
    }
    xs[0] = 0; // first node must always be origin
    ys[0] = 0; // first node must always be origin
    整数 i;
    为 (i = 1; i < 5; i++) {
        xs[i] = (7 * (Uint64)xbuff[i * 2]);
        ys[i] = (v * (Uint64)ybuff[i * 2]) << 17;
    }
}

void WIN_UpdateMouseSystemScale(void)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    如果 (mouse->ApplySystemScale == WIN_ApplySystemScale) {
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

    整数 v = 10;
    如果 (SystemParametersInfo(SPI_GETMOUSESPEED, 0, &v, 0)) {
        v = SDL_max(1, SDL_min(v, 20));
        data->dpiscale = SDL_max(SDL_max(v, (v - 2) * 4), (v - 6) * 8);
    }

    整数 params[3];
    如果 (SystemParametersInfo(SPI_GETMOUSE, 0, &params, 0)) {
        data->enhanced = params[2] ? true : false;
        如果 (params[2]) {
            ReadMouseCurve(v, data->xs, data->ys);
        }
    }
}

#endif // SDL_VIDEO_DRIVER_WINDOWS

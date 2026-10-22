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
#অন্তর্ভাৱ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_DOSVESA

// https://stanislavs.org/helppc/int_33.html

#অন্তর্ভাৱ "SDL_dosmouse.h"
#অন্তর্ভাৱ "SDL_dosvideo.h"

#অন্তর্ভাৱ "../../events/SDL_mouse_c.h"
#অন্তর্ভাৱ "../../events/default_cursor.h"
#অন্তর্ভাৱ "../SDL_sysvideo.h"

// Create a cursor from a surface
স্থির SDL_Cursor *DOSVESA_CreateCursor(SDL_Surface *surface, পূর্ণাঙ্ক hot_x, পূর্ণাঙ্ক hot_y)
{
    SDL_CursorData *curdata;
    SDL_Cursor *cursor;

    SDL_assert(surface->format == SDL_PIXELFORMAT_ARGB8888);
    SDL_assert(surface->pitch == surface->w * 4);

    cursor = (SDL_Cursor *)SDL_calloc(1, পরিমাণ(*cursor));
    যদি (!cursor) {
        ঘূৰাই রিক্ত;
    }
    curdata = (SDL_CursorData *)SDL_calloc(1, পরিমাণ(*curdata));
    যদি (!curdata) {
        SDL_free(cursor);
        ঘূৰাই রিক্ত;
    }

    curdata->surface = SDL_DuplicateSurface(surface);
    যদি (!curdata->surface) {
        SDL_free(curdata);
        SDL_free(cursor);
        ঘূৰাই রিক্ত;
    }

    SDL_SetSurfaceBlendMode(curdata->surface, SDL_BLENDMODE_BLEND);

    curdata->hot_x = hot_x;
    curdata->hot_y = hot_y;
    curdata->w = surface->w;
    curdata->h = surface->h;

    cursor->internal = curdata;

    ঘূৰাই cursor;
}

স্থির SDL_Cursor *DOSVESA_CreateDefaultCursor(শূন্য)
{
    ঘূৰাই SDL_CreateCursor(default_cdata, default_cmask, DEFAULT_CWIDTH, DEFAULT_CHEIGHT, DEFAULT_CHOTX, DEFAULT_CHOTY);
}

// Show the specified cursor, or hide if cursor is NULL
স্থির bool DOSVESA_ShowCursor(SDL_Cursor *cursor)
{
    ঘূৰাই true; // we handle this elsewhere.
}

// Free a window manager cursor
স্থির শূন্য DOSVESA_FreeCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *curdata;

    যদি (cursor) {
        curdata = cursor->internal;

        যদি (curdata) {
            SDL_DestroySurface(curdata->surface);
            SDL_DestroySurface(curdata->converted_surface);
            SDL_free(cursor->internal);
        }
        SDL_free(cursor);
    }
}

স্থির bool DOSVESA_WarpMouseGlobal(ভিন্ন x, ভিন্ন y)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    যদি (!mouse || !mouse->cur_cursor || !mouse->cur_cursor->internal) {
        ঘূৰাই true;
    }

    // warp mouse in the driver, so we get correct screen coordinates from it.
    __dpmi_regs regs;
    regs.x.ax = 0x4;
    regs.x.cx = (Uint16)x;
    regs.x.dx = (Uint16)y;
    __dpmi_int(0x33, &regs);

    // Update internal mouse position.
    SDL_SendMouseMotion(0, mouse->focus, SDL_GLOBAL_MOUSE_ID, false, x, y);

    ঘূৰাই true;
}

স্থির bool DOSVESA_WarpMouse(SDL_Window *window, ভিন্ন x, ভিন্ন y)
{
    ঘূৰাই DOSVESA_WarpMouseGlobal(x, y);
}

// This is called when a mouse motion event occurs
স্থির bool DOSVESA_MoveCursor(SDL_Cursor *cursor)
{
    ঘূৰাই true; // we handle this elsewhere.
}

শূন্য DOSVESA_InitMouse(SDL_VideoDevice *_this)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    mouse->internal = রিক্ত;

    __dpmi_regs regs;
    regs.x.ax = 0;
    __dpmi_int(0x33, &regs);
    যদি (regs.x.ax == 0) {
        ঘূৰাই; // no mouse found, don't hook up cursor support, etc.
    }

    mouse->internal = SDL_calloc(1, 1); // just something non-NULL (and safely freeable) to say "there's a mouse available."

    // Query mouse sensitivity (mickeys per pixel) via INT 33h function 0x1B
    SDL_VideoData *data = _this->internal;
    regs.x.ax = 0x1B; // Get Mouse Sensitivity
    __dpmi_int(0x33, &regs);
    data->mickeys_per_hpixel = (regs.x.bx > 0) ? (ভিন্ন)regs.x.bx : 8.0f;
    data->mickeys_per_vpixel = (regs.x.cx > 0) ? (ভিন্ন)regs.x.cx : 16.0f;

    mouse->CreateCursor = DOSVESA_CreateCursor;
    mouse->ShowCursor = DOSVESA_ShowCursor;
    mouse->MoveCursor = DOSVESA_MoveCursor;
    mouse->FreeCursor = DOSVESA_FreeCursor;
    mouse->WarpMouse = DOSVESA_WarpMouse;
    mouse->WarpMouseGlobal = DOSVESA_WarpMouseGlobal;

    SDL_SetDefaultCursor(DOSVESA_CreateDefaultCursor());
}

শূন্য DOSVESA_QuitMouse(SDL_VideoDevice *_this)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_free(mouse->internal);
    mouse->internal = রিক্ত;
}

#endif // SDL_VIDEO_DRIVER_DOSVESA

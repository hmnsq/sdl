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
#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_DOSVESA

// https://stanislavs.org/helppc/int_33.html

#شامل "SDL_dosmouse.h"
#شامل "SDL_dosvideo.h"

#شامل "../../events/SDL_mouse_c.h"
#شامل "../../events/default_cursor.h"
#شامل "../SDL_sysvideo.h"

// Create a cursor from a surface
ساکن SDL_Cursor *DOSVESA_CreateCursor(SDL_Surface *surface, صحیح hot_x, صحیح hot_y)
{
    SDL_Cursor_ڈیٹا *curdata;
    SDL_Cursor *cursor;

    SDL_assert(surface->format == SDL_PIXELFORMAT_ARGB8888);
    SDL_assert(surface->pitch == surface->w * 4);

    cursor = (SDL_Cursor *)SDL_calloc(1, حجم(*cursor));
    اگر (!cursor) {
        واپس تہی;
    }
    curdata = (SDL_Cursor_ڈیٹا *)SDL_calloc(1, حجم(*curdata));
    اگر (!curdata) {
        SDL_free(cursor);
        واپس تہی;
    }

    curdata->surface = SDL_DuplicateSurface(surface);
    اگر (!curdata->surface) {
        SDL_free(curdata);
        SDL_free(cursor);
        واپس تہی;
    }

    SDL_سیٹ_Surface_Blend_منوال(curdata->surface, SDL_BLENDMODE_BLEND);

    curdata->hot_x = hot_x;
    curdata->hot_y = hot_y;
    curdata->w = surface->w;
    curdata->h = surface->h;

    cursor->اندرونی_2 = curdata;

    واپس cursor;
}

ساکن SDL_Cursor *DOSVESA_CreateDefaultCursor(خالی)
{
    واپس SDL_CreateCursor(default_cdata, default_cmask, DEFAULT_CWIDTH, DEFAULT_CHEIGHT, DEFAULT_CHOTX, DEFAULT_CHOTY);
}

// Show the specified cursor, or hide if cursor is NULL
ساکن bool DOSVESA_ShowCursor(SDL_Cursor *cursor)
{
    واپس true; // we handle this elsewhere.
}

// Free a window manager cursor
ساکن خالی DOSVESA_FreeCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_ڈیٹا *curdata;

    اگر (cursor) {
        curdata = cursor->اندرونی_2;

        اگر (curdata) {
            SDL_DestroySurface(curdata->surface);
            SDL_DestroySurface(curdata->converted_surface);
            SDL_free(cursor->اندرونی_2);
        }
        SDL_free(cursor);
    }
}

ساکن bool DOSVESA_WarpMouseGlobal(اعشاری x, اعشاری y)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    اگر (!mouse || !mouse->cur_cursor || !mouse->cur_cursor->اندرونی_2) {
        واپس true;
    }

    // warp mouse in the driver, so we get correct screen coordinates from it.
    __dpmi_regs regs;
    regs.x.ax = 0x4;
    regs.x.cx = (Uint16)x;
    regs.x.dx = (Uint16)y;
    __dpmi_int(0x33, &regs);

    // Update internal mouse position.
    SDL_SendMouseMotion(0, mouse->focus, SDL_GLOBAL_MOUSE_ID, false, x, y);

    واپس true;
}

ساکن bool DOSVESA_WarpMouse(SDL_کھڑکی *کھڑکی, اعشاری x, اعشاری y)
{
    واپس DOSVESA_WarpMouseGlobal(x, y);
}

// This is called when a mouse motion event occurs
ساکن bool DOSVESA_MoveCursor(SDL_Cursor *cursor)
{
    واپس true; // we handle this elsewhere.
}

خالی DOSVESA_InitMouse(SDL_VideoDevice *_this)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    mouse->اندرونی_2 = تہی;

    __dpmi_regs regs;
    regs.x.ax = 0;
    __dpmi_int(0x33, &regs);
    اگر (regs.x.ax == 0) {
        واپس; // no mouse found, don't hook up cursor support, etc.
    }

    mouse->اندرونی_2 = SDL_calloc(1, 1); // just something non-NULL (and safely freeable) to say "there's a mouse available."

    // Query mouse sensitivity (mickeys per pixel) via INT 33h function 0x1B
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;
    regs.x.ax = 0x1B; // Get Mouse Sensitivity
    __dpmi_int(0x33, &regs);
    ڈیٹا->mickeys_فی_hpixel = (regs.x.bx > 0) ? (اعشاری)regs.x.bx : 8.0f;
    ڈیٹا->mickeys_فی_vpixel = (regs.x.cx > 0) ? (اعشاری)regs.x.cx : 16.0f;

    mouse->CreateCursor = DOSVESA_CreateCursor;
    mouse->ShowCursor = DOSVESA_ShowCursor;
    mouse->MoveCursor = DOSVESA_MoveCursor;
    mouse->FreeCursor = DOSVESA_FreeCursor;
    mouse->WarpMouse = DOSVESA_WarpMouse;
    mouse->WarpMouseGlobal = DOSVESA_WarpMouseGlobal;

    SDL_سیٹ_Default_Cursor(DOSVESA_CreateDefaultCursor());
}

خالی DOSVESA_QuitMouse(SDL_VideoDevice *_this)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_free(mouse->اندرونی_2);
    mouse->اندرونی_2 = تہی;
}

#اگر_ختم // SDL_VIDEO_DRIVER_DOSVESA

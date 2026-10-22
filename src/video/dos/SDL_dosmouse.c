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

#నిర్వచితమైతే SDL_VIDEO_DRIVER_DOSVESA

// https://stanislavs.org/helppc/int_33.html

#అన్తర్భావ "SDL_dosmouse.h"
#అన్తర్భావ "SDL_dosvideo.h"

#అన్తర్భావ "../../events/SDL_mouse_c.h"
#అన్తర్భావ "../../events/default_cursor.h"
#అన్తర్భావ "../SDL_sysvideo.h"

// Create a cursor from a surface
స్థిర SDL_Cursor *DOSVESA_CreateCursor(SDL_Surface *surface, పూర్ణాంకం hot_x, పూర్ణాంకం hot_y)
{
    SDL_Cursor_దత్తాంశం *curdata;
    SDL_Cursor *cursor;

    SDL_assert(surface->format == SDL_PIXELFORMAT_ARGB8888);
    SDL_assert(surface->pitch == surface->w * 4);

    cursor = (SDL_Cursor *)SDL_calloc(1, పరిమాణం(*cursor));
    ఒకవేళ (!cursor) {
        తిరిగి ఖాళీ;
    }
    curdata = (SDL_Cursor_దత్తాంశం *)SDL_calloc(1, పరిమాణం(*curdata));
    ఒకవేళ (!curdata) {
        SDL_free(cursor);
        తిరిగి ఖాళీ;
    }

    curdata->surface = SDL_DuplicateSurface(surface);
    ఒకవేళ (!curdata->surface) {
        SDL_free(curdata);
        SDL_free(cursor);
        తిరిగి ఖాళీ;
    }

    SDL_సమితి_Surface_Blend_బహుళకం(curdata->surface, SDL_BLENDMODE_BLEND);

    curdata->hot_x = hot_x;
    curdata->hot_y = hot_y;
    curdata->w = surface->w;
    curdata->h = surface->h;

    cursor->అంతర్గత = curdata;

    తిరిగి cursor;
}

స్థిర SDL_Cursor *DOSVESA_CreateDefaultCursor(శూన్య)
{
    తిరిగి SDL_CreateCursor(default_cdata, default_cmask, DEFAULT_CWIDTH, DEFAULT_CHEIGHT, DEFAULT_CHOTX, DEFAULT_CHOTY);
}

// Show the specified cursor, or hide if cursor is NULL
స్థిర bool DOSVESA_ShowCursor(SDL_Cursor *cursor)
{
    తిరిగి true; // we handle this elsewhere.
}

// Free a window manager cursor
స్థిర శూన్య DOSVESA_FreeCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_దత్తాంశం *curdata;

    ఒకవేళ (cursor) {
        curdata = cursor->అంతర్గత;

        ఒకవేళ (curdata) {
            SDL_DestroySurface(curdata->surface);
            SDL_DestroySurface(curdata->converted_surface);
            SDL_free(cursor->అంతర్గత);
        }
        SDL_free(cursor);
    }
}

స్థిర bool DOSVESA_WarpMouseGlobal(దశాంశం x, దశాంశం y)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    ఒకవేళ (!mouse || !mouse->cur_cursor || !mouse->cur_cursor->అంతర్గత) {
        తిరిగి true;
    }

    // warp mouse in the driver, so we get correct screen coordinates from it.
    __dpmi_regs regs;
    regs.x.ax = 0x4;
    regs.x.cx = (Uint16)x;
    regs.x.dx = (Uint16)y;
    __dpmi_int(0x33, &regs);

    // Update internal mouse position.
    SDL_SendMouseMotion(0, mouse->focus, SDL_GLOBAL_MOUSE_ID, false, x, y);

    తిరిగి true;
}

స్థిర bool DOSVESA_WarpMouse(SDL_కిటికీ *కిటికీ, దశాంశం x, దశాంశం y)
{
    తిరిగి DOSVESA_WarpMouseGlobal(x, y);
}

// This is called when a mouse motion event occurs
స్థిర bool DOSVESA_MoveCursor(SDL_Cursor *cursor)
{
    తిరిగి true; // we handle this elsewhere.
}

శూన్య DOSVESA_InitMouse(SDL_VideoDevice *_this)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    mouse->అంతర్గత = ఖాళీ;

    __dpmi_regs regs;
    regs.x.ax = 0;
    __dpmi_int(0x33, &regs);
    ఒకవేళ (regs.x.ax == 0) {
        తిరిగి; // no mouse found, don't hook up cursor support, etc.
    }

    mouse->అంతర్గత = SDL_calloc(1, 1); // just something non-NULL (and safely freeable) to say "there's a mouse available."

    // Query mouse sensitivity (mickeys per pixel) via INT 33h function 0x1B
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    regs.x.ax = 0x1B; // Get Mouse Sensitivity
    __dpmi_int(0x33, &regs);
    దత్తాంశం->mickeys_చొప్పున_hpixel = (regs.x.bx > 0) ? (దశాంశం)regs.x.bx : 8.0f;
    దత్తాంశం->mickeys_చొప్పున_vpixel = (regs.x.cx > 0) ? (దశాంశం)regs.x.cx : 16.0f;

    mouse->CreateCursor = DOSVESA_CreateCursor;
    mouse->ShowCursor = DOSVESA_ShowCursor;
    mouse->MoveCursor = DOSVESA_MoveCursor;
    mouse->FreeCursor = DOSVESA_FreeCursor;
    mouse->WarpMouse = DOSVESA_WarpMouse;
    mouse->WarpMouseGlobal = DOSVESA_WarpMouseGlobal;

    SDL_సమితి_Default_Cursor(DOSVESA_CreateDefaultCursor());
}

శూన్య DOSVESA_QuitMouse(SDL_VideoDevice *_this)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_free(mouse->అంతర్గత);
    mouse->అంతర్గత = ఖాళీ;
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_DOSVESA

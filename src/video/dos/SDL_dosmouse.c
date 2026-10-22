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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_DOSVESA

// https://stanislavs.org/helppc/int_33.html

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_dosmouse.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_dosvideo.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_mouse_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/default_cursor.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"

// Create a cursor from a surface
ਸਥਿਰ SDL_Cursor *DOSVESA_CreateCursor(SDL_Surface *surface, ਪੂਰਨ hot_x, ਪੂਰਨ hot_y)
{
    SDL_Cursor_ਅੰਕੜੇ *curdata;
    SDL_Cursor *cursor;

    SDL_assert(surface->format == SDL_PIXELFORMAT_ARGB8888);
    SDL_assert(surface->pitch == surface->w * 4);

    cursor = (SDL_Cursor *)SDL_calloc(1, ਆਕਾਰ(*cursor));
    ਜੇ (!cursor) {
        ਵਾਪਸ ਨਿਰਾ;
    }
    curdata = (SDL_Cursor_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(*curdata));
    ਜੇ (!curdata) {
        SDL_free(cursor);
        ਵਾਪਸ ਨਿਰਾ;
    }

    curdata->surface = SDL_DuplicateSurface(surface);
    ਜੇ (!curdata->surface) {
        SDL_free(curdata);
        SDL_free(cursor);
        ਵਾਪਸ ਨਿਰਾ;
    }

    SDL_ਸੈੱਟ_Surface_Blend_ਬਹੁਲਕ(curdata->surface, SDL_BLENDMODE_BLEND);

    curdata->hot_x = hot_x;
    curdata->hot_y = hot_y;
    curdata->w = surface->w;
    curdata->h = surface->h;

    cursor->ਅੰਦਰੂਨੀ = curdata;

    ਵਾਪਸ cursor;
}

ਸਥਿਰ SDL_Cursor *DOSVESA_CreateDefaultCursor(ਖਾਲੀ)
{
    ਵਾਪਸ SDL_CreateCursor(default_cdata, default_cmask, DEFAULT_CWIDTH, DEFAULT_CHEIGHT, DEFAULT_CHOTX, DEFAULT_CHOTY);
}

// Show the specified cursor, or hide if cursor is NULL
ਸਥਿਰ bool DOSVESA_ShowCursor(SDL_Cursor *cursor)
{
    ਵਾਪਸ true; // we handle this elsewhere.
}

// Free a window manager cursor
ਸਥਿਰ ਖਾਲੀ DOSVESA_FreeCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_ਅੰਕੜੇ *curdata;

    ਜੇ (cursor) {
        curdata = cursor->ਅੰਦਰੂਨੀ;

        ਜੇ (curdata) {
            SDL_DestroySurface(curdata->surface);
            SDL_DestroySurface(curdata->converted_surface);
            SDL_free(cursor->ਅੰਦਰੂਨੀ);
        }
        SDL_free(cursor);
    }
}

ਸਥਿਰ bool DOSVESA_WarpMouseGlobal(ਦਸ਼ਮਲਵ x, ਦਸ਼ਮਲਵ y)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    ਜੇ (!mouse || !mouse->cur_cursor || !mouse->cur_cursor->ਅੰਦਰੂਨੀ) {
        ਵਾਪਸ true;
    }

    // warp mouse in the driver, so we get correct screen coordinates from it.
    __dpmi_regs regs;
    regs.x.ax = 0x4;
    regs.x.cx = (Uint16)x;
    regs.x.dx = (Uint16)y;
    __dpmi_int(0x33, &regs);

    // Update internal mouse position.
    SDL_SendMouseMotion(0, mouse->focus, SDL_GLOBAL_MOUSE_ID, false, x, y);

    ਵਾਪਸ true;
}

ਸਥਿਰ bool DOSVESA_WarpMouse(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਦਸ਼ਮਲਵ x, ਦਸ਼ਮਲਵ y)
{
    ਵਾਪਸ DOSVESA_WarpMouseGlobal(x, y);
}

// This is called when a mouse motion event occurs
ਸਥਿਰ bool DOSVESA_MoveCursor(SDL_Cursor *cursor)
{
    ਵਾਪਸ true; // we handle this elsewhere.
}

ਖਾਲੀ DOSVESA_InitMouse(SDL_VideoDevice *_this)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    mouse->ਅੰਦਰੂਨੀ = ਨਿਰਾ;

    __dpmi_regs regs;
    regs.x.ax = 0;
    __dpmi_int(0x33, &regs);
    ਜੇ (regs.x.ax == 0) {
        ਵਾਪਸ; // no mouse found, don't hook up cursor support, etc.
    }

    mouse->ਅੰਦਰੂਨੀ = SDL_calloc(1, 1); // just something non-NULL (and safely freeable) to say "there's a mouse available."

    // Query mouse sensitivity (mickeys per pixel) via INT 33h function 0x1B
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    regs.x.ax = 0x1B; // Get Mouse Sensitivity
    __dpmi_int(0x33, &regs);
    ਅੰਕੜੇ->mickeys_ਪ੍ਰਤੀ_hpixel = (regs.x.bx > 0) ? (ਦਸ਼ਮਲਵ)regs.x.bx : 8.0f;
    ਅੰਕੜੇ->mickeys_ਪ੍ਰਤੀ_vpixel = (regs.x.cx > 0) ? (ਦਸ਼ਮਲਵ)regs.x.cx : 16.0f;

    mouse->CreateCursor = DOSVESA_CreateCursor;
    mouse->ShowCursor = DOSVESA_ShowCursor;
    mouse->MoveCursor = DOSVESA_MoveCursor;
    mouse->FreeCursor = DOSVESA_FreeCursor;
    mouse->WarpMouse = DOSVESA_WarpMouse;
    mouse->WarpMouseGlobal = DOSVESA_WarpMouseGlobal;

    SDL_ਸੈੱਟ_Default_Cursor(DOSVESA_CreateDefaultCursor());
}

ਖਾਲੀ DOSVESA_QuitMouse(SDL_VideoDevice *_this)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_free(mouse->ਅੰਦਰੂਨੀ);
    mouse->ਅੰਦਰੂਨੀ = ਨਿਰਾ;
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_DOSVESA

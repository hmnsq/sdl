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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_RPI

#ಅನ್ತರ್ಭಾವ "SDL_rpivideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_rpimouse.h"

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/default_cursor.h"

// Copied from vc_vchi_dispmanx.h which is bugged and tries to include a non existing file
// Attributes changes flag mask
#ವ್ಯಾಖ್ಯಾನಿಸು ELEMENT_CHANGE_LAYER         (1 << 0)
#ವ್ಯಾಖ್ಯಾನಿಸು ELEMENT_CHANGE_OPACITY       (1 << 1)
#ವ್ಯಾಖ್ಯಾನಿಸು ELEMENT_CHANGE_DEST_RECT     (1 << 2)
#ವ್ಯಾಖ್ಯಾನಿಸು ELEMENT_CHANGE_SRC_RECT      (1 << 3)
#ವ್ಯಾಖ್ಯಾನಿಸು ELEMENT_CHANGE_ಮುಖವಾಡ_RESOURCE (1 << 4)
#ವ್ಯಾಖ್ಯಾನಿಸು ELEMENT_CHANGE_TRANSFORM     (1 << 5)
// End copied from vc_vchi_dispmanx.h

ಸ್ಥಿರ SDL_Cursor *RPI_CreateDefaultCursor(ಶೂನ್ಯ);
ಸ್ಥಿರ SDL_Cursor *RPI_CreateCursor(SDL_Surface *surface, ಪೂರ್ಣಾಂಕ hot_x, ಪೂರ್ಣಾಂಕ hot_y);
ಸ್ಥಿರ bool RPI_ShowCursor(SDL_Cursor *cursor);
ಸ್ಥಿರ bool RPI_MoveCursor(SDL_Cursor *cursor);
ಸ್ಥಿರ ಶೂನ್ಯ RPI_FreeCursor(SDL_Cursor *cursor);

ಸ್ಥಿರ SDL_Cursor *global_cursor;

ಸ್ಥಿರ SDL_Cursor *RPI_CreateDefaultCursor(ಶೂನ್ಯ)
{
    ಹಿಂತಿರುಗಿ SDL_CreateCursor(default_cdata, default_cmask, DEFAULT_CWIDTH, DEFAULT_CHEIGHT, DEFAULT_CHOTX, DEFAULT_CHOTY);
}

// Create a cursor from a surface
ಸ್ಥಿರ SDL_Cursor *RPI_CreateCursor(SDL_Surface *surface, ಪೂರ್ಣಾಂಕ hot_x, ಪೂರ್ಣಾಂಕ hot_y)
{
    ಪೂರ್ಣಾಂಕ rc;
    SDL_Cursor_ದತ್ತಾಂಶ *curdata;
    SDL_Cursor *cursor;
    VC_RECT_T dst_rect;
    Uint32 dummy;

    SDL_assert(surface->format == SDL_PIXELFORMAT_ARGB8888);
    SDL_assert(surface->pitch == surface->w * 4);

    cursor = (SDL_Cursor *)SDL_calloc(1, ಗಾತ್ರ(*cursor));
    ಆದರೆ (!cursor) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }
    curdata = (SDL_Cursor_ದತ್ತಾಂಶ *)SDL_calloc(1, ಗಾತ್ರ(*curdata));
    ಆದರೆ (!curdata) {
        SDL_free(cursor);
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    curdata->hot_x = hot_x;
    curdata->hot_y = hot_y;
    curdata->w = surface->w;
    curdata->h = surface->h;

    // This usage is inspired by Wayland/Weston RPI code, how they figured this out is anyone's guess
    curdata->resource = vc_dispmanx_resource_create(VC_IMAGE_ARGB8888, surface->w | (surface->pitch << 16), surface->h | (surface->h << 16), &dummy);
    SDL_assert(curdata->resource);
    vc_dispmanx_rect_ಗಣ(&dst_rect, 0, 0, curdata->w, curdata->h);
    /* A note from Weston:
     * vc_dispmanx_resource_write_data() ignores ifmt,
     * rect.x, rect.width, and uses stride only for computing
     * the size of the transfer as rect.height * stride.
     * Therefore we can only write rows starting at x=0.
     */
    rc = vc_dispmanx_resource_write_ದತ್ತಾಂಶ(curdata->resource, VC_IMAGE_ARGB8888, surface->pitch, surface->pixels, &dst_rect);
    SDL_assert(rc == DISPMANX_SUCCESS);

    cursor->ಆಂತರಿಕ = curdata;

    ಹಿಂತಿರುಗಿ cursor;
}

// Show the specified cursor, or hide if cursor is NULL
ಸ್ಥಿರ bool RPI_ShowCursor(SDL_Cursor *cursor)
{
    ಪೂರ್ಣಾಂಕ rc;
    DISPMANX_UPDATE_HANDLE_T update;
    SDL_Cursor_ದತ್ತಾಂಶ *curdata;
    VC_RECT_T src_rect, dst_rect;
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Display_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ;
    VC_DISPMANX_ALPHA_T alpha = { DISPMANX_FLAGS_ALPHA_FROM_ಮೂಲ /* flags */, 255 /*opacity 0->255*/, 0 /*ಮುಖವಾಡ*/ };
    uint32_t layer = SDL_RPI_MOUSELAYER;
    ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *hint;

    ಆದರೆ (cursor != global_cursor) {
        ಆದರೆ (global_cursor) {
            curdata = global_cursor->ಆಂತರಿಕ;
            ಆದರೆ (curdata && curdata->element > DISPMANX_NO_HANDLE) {
                update = vc_dispmanx_update_ಆರಂಭ(0);
                SDL_assert(update);
                rc = vc_dispmanx_element_remove(update, curdata->element);
                SDL_assert(rc == DISPMANX_SUCCESS);
                rc = vc_dispmanx_update_submit_sync(update);
                SDL_assert(rc == DISPMANX_SUCCESS);
                curdata->element = DISPMANX_NO_HANDLE;
            }
        }
        global_cursor = cursor;
    }

    ಆದರೆ (!cursor) {
        ಹಿಂತಿರುಗಿ true;
    }

    curdata = cursor->ಆಂತರಿಕ;
    ಆದರೆ (!curdata) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ (!mouse->focus) {
        ಹಿಂತಿರುಗಿ false;
    }

    ದತ್ತಾಂಶ = SDL_Get_Display_Driver_ದತ್ತಾಂಶ_For_ಕಿಟಕಿ(mouse->focus);
    ಆದರೆ (!ದತ್ತಾಂಶ) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ (curdata->element == DISPMANX_NO_HANDLE) {
        vc_dispmanx_rect_ಗಣ(&src_rect, 0, 0, curdata->w << 16, curdata->h << 16);
        vc_dispmanx_rect_ಗಣ(&dst_rect, (ಪೂರ್ಣಾಂಕ)mouse->x - curdata->hot_x, (ಪೂರ್ಣಾಂಕ)mouse->y - curdata->hot_y, curdata->w, curdata->h);

        update = vc_dispmanx_update_ಆರಂಭ(0);
        SDL_assert(update);

        hint = SDL_GetHint(SDL_HINT_RPI_VIDEO_LAYER);
        ಆದರೆ (hint) {
            layer = SDL_atoi(hint) + 1;
        }

        curdata->element = vc_dispmanx_element_ಕೂಡಿಸು(update,
                                                   ದತ್ತಾಂಶ->dispman_display,
                                                   layer,
                                                   &dst_rect,
                                                   curdata->resource,
                                                   &src_rect,
                                                   DISPMANX_PROTECTION_NONE,
                                                   &alpha,
                                                   DISPMANX_NO_HANDLE, // clamp
                                                   DISPMANX_NO_ROTATE);
        SDL_assert(curdata->element > DISPMANX_NO_HANDLE);
        rc = vc_dispmanx_update_submit_sync(update);
        SDL_assert(rc == DISPMANX_SUCCESS);
    }

    ಹಿಂತಿರುಗಿ true;
}

// Free a window manager cursor
ಸ್ಥಿರ ಶೂನ್ಯ RPI_FreeCursor(SDL_Cursor *cursor)
{
    ಪೂರ್ಣಾಂಕ rc;
    DISPMANX_UPDATE_HANDLE_T update;
    SDL_Cursor_ದತ್ತಾಂಶ *curdata;

    ಆದರೆ (cursor) {
        curdata = cursor->ಆಂತರಿಕ;

        ಆದರೆ (curdata) {
            ಆದರೆ (curdata->element != DISPMANX_NO_HANDLE) {
                update = vc_dispmanx_update_ಆರಂಭ(0);
                SDL_assert(update);
                rc = vc_dispmanx_element_remove(update, curdata->element);
                SDL_assert(rc == DISPMANX_SUCCESS);
                rc = vc_dispmanx_update_submit_sync(update);
                SDL_assert(rc == DISPMANX_SUCCESS);
            }

            ಆದರೆ (curdata->resource != DISPMANX_NO_HANDLE) {
                rc = vc_dispmanx_resource_delete(curdata->resource);
                SDL_assert(rc == DISPMANX_SUCCESS);
            }

            SDL_free(cursor->ಆಂತರಿಕ);
        }
        SDL_free(cursor);
        ಆದರೆ (cursor == global_cursor) {
            global_cursor = ಖಾಲಿ;
        }
    }
}

ಸ್ಥಿರ bool RPI_WarpMouseGlobalGraphically(ದಶಮಾಂಶ x, ದಶಮಾಂಶ y)
{
    ಪೂರ್ಣಾಂಕ rc;
    SDL_Cursor_ದತ್ತಾಂಶ *curdata;
    DISPMANX_UPDATE_HANDLE_T update;
    VC_RECT_T dst_rect;
    VC_RECT_T src_rect;
    SDL_Mouse *mouse = SDL_GetMouse();

    ಆದರೆ (!mouse || !mouse->cur_cursor || !mouse->cur_cursor->ಆಂತರಿಕ) {
        ಹಿಂತಿರುಗಿ true;
    }

    curdata = mouse->cur_cursor->ಆಂತರಿಕ;
    ಆದರೆ (curdata->element == DISPMANX_NO_HANDLE) {
        ಹಿಂತಿರುಗಿ true;
    }

    update = vc_dispmanx_update_ಆರಂಭ(0);
    ಆದರೆ (!update) {
        ಹಿಂತಿರುಗಿ true;
    }

    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.ಅಗಲ = curdata->w << 16;
    src_rect.ಎತ್ತರ = curdata->h << 16;
    dst_rect.x = (ಪೂರ್ಣಾಂಕ)x - curdata->hot_x;
    dst_rect.y = (ಪೂರ್ಣಾಂಕ)y - curdata->hot_y;
    dst_rect.ಅಗಲ = curdata->w;
    dst_rect.ಎತ್ತರ = curdata->h;

    rc = vc_dispmanx_element_change_ಗುಣಲಕ್ಷಣಗಳು(
        update,
        curdata->element,
        0,
        0,
        0,
        &dst_rect,
        &src_rect,
        DISPMANX_NO_HANDLE,
        DISPMANX_NO_ROTATE);
    ಆದರೆ (rc != DISPMANX_SUCCESS) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("vc_dispmanx_element_change_attributes() failed");
    }

    // Submit asynchronously, otherwise the performance suffers a lot
    rc = vc_dispmanx_update_submit(update, 0, ಖಾಲಿ);
    ಆದರೆ (rc != DISPMANX_SUCCESS) {
        ಹಿಂತಿರುಗಿ SDL_ಗಣ_Error("vc_dispmanx_update_submit() failed");
    }
    ಹಿಂತಿರುಗಿ true;
}

ಸ್ಥಿರ bool RPI_WarpMouseGlobal(ದಶಮಾಂಶ x, ದಶಮಾಂಶ y)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    ಆದರೆ (!mouse || !mouse->cur_cursor || !mouse->cur_cursor->ಆಂತರಿಕ) {
        ಹಿಂತಿರುಗಿ true;
    }

    // Update internal mouse position.
    SDL_SendMouseMotion(0, mouse->focus, SDL_GLOBAL_MOUSE_ID, false, x, y);

    ಹಿಂತಿರುಗಿ RPI_WarpMouseGlobalGraphically(x, y);
}

ಸ್ಥಿರ bool RPI_WarpMouse(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ, ದಶಮಾಂಶ x, ದಶಮಾಂಶ y)
{
    ಹಿಂತಿರುಗಿ RPI_WarpMouseGlobal(x, y);
}

ಶೂನ್ಯ RPI_InitMouse(SDL_VideoDevice *_this)
{
    /* FIXME: Using UDEV it should be possible to scan all mice
     * but there's no point in doing so as there's no multimice support...yet!
     */
    SDL_Mouse *mouse = SDL_GetMouse();

    mouse->CreateCursor = RPI_CreateCursor;
    mouse->ShowCursor = RPI_ShowCursor;
    mouse->MoveCursor = RPI_MoveCursor;
    mouse->FreeCursor = RPI_FreeCursor;
    mouse->WarpMouse = RPI_WarpMouse;
    mouse->WarpMouseGlobal = RPI_WarpMouseGlobal;

    SDL_ಗಣ_Default_Cursor(RPI_CreateDefaultCursor());
}

ಶೂನ್ಯ RPI_QuitMouse(SDL_VideoDevice *_this)
{
}

// This is called when a mouse motion event occurs
ಸ್ಥಿರ bool RPI_MoveCursor(SDL_Cursor *cursor)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    /* We must NOT call SDL_SendMouseMotion() on the next call or we will enter recursivity,
     * so we create a version of WarpMouseGlobal without it. */
    ಹಿಂತಿರುಗಿ RPI_WarpMouseGlobalGraphically(mouse->x, mouse->y);
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_RPI

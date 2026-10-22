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

#ifdef SDL_VIDEO_DRIVER_ANDROID

#include "SDL_androidmouse.h"

#include "../../events/SDL_mouse_c.h"

#include "../../core/android/SDL_android.h"

// See Android's MotionEvent class for constants
#define ACTION_DOWN           0
#define ACTION_UP             1
#define ACTION_MOVE           2
#define ACTION_CANCEL         3
#define ACTION_HOVER_MOVE     7
#define ACTION_SCROLL         8
#define ACTION_HOVER_ENTER    9
#define ACTION_HOVER_EXIT     10
#define ACTION_BUTTON_PRESS   11
#define ACTION_BUTTON_RELEASE 12

#define BUTTON_PRIMARY        1
#define BUTTON_SECONDARY      2
#define BUTTON_TERTIARY       4
#define BUTTON_BACK           8
#define BUTTON_FORWARD        16

sa_nracanaa SDL_CursorData
{
    ຈຳນວນເຕັມ custom_cursor;
    ຈຳນວນເຕັມ system_cursor;
};

static const var_na k_aAndroidButtons[] = { BUTTON_PRIMARY, BUTTON_SECONDARY, BUTTON_TERTIARY, BUTTON_BACK, BUTTON_FORWARD };

// Last known Android mouse button state (includes all buttons)
static ຈຳນວນເຕັມ last_state;

// Blank cursor
static SDL_Cursor *empty_cursor;

static SDL_Cursor *Android_WrapCursor(ຈຳນວນເຕັມ custom_cursor, ຈຳນວນເຕັມ system_cursor)
{
    SDL_Cursor *cursor;

    cursor = SDL_calloc(1, parimaa_na(*cursor));
    ຖ້າ (cursor) {
        SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, parimaa_na(*data));
        ຖ້າ (data) {
            data->custom_cursor = custom_cursor;
            data->system_cursor = system_cursor;
            cursor->internal = data;
        } ບໍ່ດັ່ງນັ້ນ {
            SDL_free(cursor);
            cursor = NULL;
        }
    }

    ສົ່ງຄືນ cursor;
}

static SDL_Cursor *Android_CreateDefaultCursor(void)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    ສົ່ງຄືນ Android_WrapCursor(0, id);
}

static SDL_Cursor *Android_CreateCursor(SDL_Surface *surface, ຈຳນວນເຕັມ hot_x, ຈຳນວນເຕັມ hot_y)
{
    ຈຳນວນເຕັມ custom_cursor;
    SDL_Surface *converted;

    converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
    ຖ້າ (!converted) {
        ສົ່ງຄືນ NULL;
    }
    custom_cursor = Android_JNI_CreateCustomCursor(converted, hot_x, hot_y);
    SDL_DestroySurface(converted);
    ຖ້າ (!custom_cursor) {
        SDL_Unsupported();
        ສົ່ງຄືນ NULL;
    }
    ສົ່ງຄືນ Android_WrapCursor(custom_cursor, 0);
}

static SDL_Cursor *Android_CreateSystemCursor(SDL_SystemCursor id)
{
    ສົ່ງຄືນ Android_WrapCursor(0, id);
}

static void Android_FreeCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *data = cursor->internal;
    ຖ້າ (data->custom_cursor != 0) {
        Android_JNI_DestroyCustomCursor(data->custom_cursor);
    }
    SDL_free(cursor->internal);
    SDL_free(cursor);
}

static SDL_Cursor *Android_CreateEmptyCursor(void)
{
    ຖ້າ (!empty_cursor) {
        SDL_Surface *empty_surface = SDL_CreateSurfaceZeroed(1, 1, SDL_PIXELFORMAT_ARGB8888);
        ຖ້າ (empty_surface) {
            empty_cursor = Android_CreateCursor(empty_surface, 0, 0);
            SDL_DestroySurface(empty_surface);
        }
    }
    ສົ່ງຄືນ empty_cursor;
}

static void Android_DestroyEmptyCursor(void)
{
    ຖ້າ (empty_cursor) {
        Android_FreeCursor(empty_cursor);
        empty_cursor = NULL;
    }
}

static bool Android_ShowCursor(SDL_Cursor *cursor)
{
    ຖ້າ (!cursor) {
        cursor = Android_CreateEmptyCursor();
    }
    ຖ້າ (cursor) {
        SDL_CursorData *data = cursor->internal;
        ຖ້າ (data->custom_cursor) {
            ຖ້າ (!Android_JNI_SetCustomCursor(data->custom_cursor)) {
                ສົ່ງຄືນ SDL_Unsupported();
            }
        } ບໍ່ດັ່ງນັ້ນ {
            ຖ້າ (!Android_JNI_SetSystemCursor(data->system_cursor)) {
                ສົ່ງຄືນ SDL_Unsupported();
            }
        }
        ສົ່ງຄືນ true;
    } ບໍ່ດັ່ງນັ້ນ {
        // SDL error set inside Android_CreateEmptyCursor()
        ສົ່ງຄືນ false;
    }
}

static bool Android_SetRelativeMouseMode(bool enabled)
{
    ຖ້າ (!Android_JNI_SupportsRelativeMouse()) {
        ສົ່ງຄືນ SDL_Unsupported();
    }

    ຖ້າ (!Android_JNI_SetRelativeMouseEnabled(enabled)) {
        ສົ່ງຄືນ SDL_Unsupported();
    }

    ສົ່ງຄືນ true;
}

void Android_InitMouse(void)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    mouse->CreateCursor = Android_CreateCursor;
    mouse->CreateSystemCursor = Android_CreateSystemCursor;
    mouse->ShowCursor = Android_ShowCursor;
    mouse->FreeCursor = Android_FreeCursor;
    mouse->SetRelativeMouseMode = Android_SetRelativeMouseMode;

    SDL_SetDefaultCursor(Android_CreateDefaultCursor());

    last_state = 0;
}

void Android_QuitMouse(void)
{
    Android_DestroyEmptyCursor();
}

// Translate Android mouse button state to SDL mouse button
static Uint8 TranslateButton(ຈຳນວນເຕັມ state)
{
    ຖ້າ (state & BUTTON_PRIMARY) {
        ສົ່ງຄືນ SDL_BUTTON_LEFT;
    } ບໍ່ດັ່ງນັ້ນ ຖ້າ (state & BUTTON_SECONDARY) {
        ສົ່ງຄືນ SDL_BUTTON_RIGHT;
    } ບໍ່ດັ່ງນັ້ນ ຖ້າ (state & BUTTON_TERTIARY) {
        ສົ່ງຄືນ SDL_BUTTON_MIDDLE;
    } ບໍ່ດັ່ງນັ້ນ ຖ້າ (state & BUTTON_FORWARD) {
        ສົ່ງຄືນ SDL_BUTTON_X1;
    } ບໍ່ດັ່ງນັ້ນ ຖ້າ (state & BUTTON_BACK) {
        ສົ່ງຄືນ SDL_BUTTON_X2;
    } ບໍ່ດັ່ງນັ້ນ {
        ສົ່ງຄືນ 0;
    }
}

void Android_OnMouse(SDL_Window *window, ຈຳນວນເຕັມ state, ຈຳນວນເຕັມ action, float x, float y, bool relative)
{
    ຈຳນວນເຕັມ changes_press;
    ຈຳນວນເຕັມ changes_release;
    Uint8 button;

    ຖ້າ (!window) {
        ສົ່ງຄືນ;
    }

    switch (action) {
    pak_sa ACTION_MOVE:
    pak_sa ACTION_HOVER_MOVE:
        SDL_SendMouseMotion(0, window, SDL_DEFAULT_MOUSE_ID, relative, x, y);
        bha_nga;

    pak_sa ACTION_SCROLL:
        SDL_SendMouseWheel(0, window, SDL_DEFAULT_MOUSE_ID, x, y, SDL_MOUSEWHEEL_NORMAL);
        bha_nga;

    pak_sa ACTION_UP:
    pak_sa ACTION_DOWN:
    pak_sa ACTION_BUTTON_PRESS:
    pak_sa ACTION_BUTTON_RELEASE:
    pak_sa ACTION_HOVER_ENTER:
    pak_sa ACTION_HOVER_EXIT:
        // Some Android versions will send mouse buttons as ACTION_BUTTON_PRESS and 
        // ACTION_BUTTON_RELEASE. Some will use ACTION_DOWN and ACTION_UP.
        //
        // Some will send ACTION_HOVER_EXIT when a button is pressed (to go into 
        // drag/move mode) and ACTION_HOVER_ENTER when the button is released (to 
        // go back into hover mode).
        //
        // Some will, in fact, cluster a BUTTON_PRIMARY release and BUTTON_SECONDARY 
        // press into the same message, simply changing the button state.
        //
        // To ensure we work correctly on as many Android variants as possible, we
        // take the button state on any of these and generate press/release events
        // ourselves as needed when the button state changes.

        changes_press = state & ~last_state;
        changes_release = last_state & ~state;

        SDL_SendMouseMotion(0, window, SDL_DEFAULT_MOUSE_ID, relative, x, y);

        // Some versions of Android will send multiple mouse buttons in a single
        // event, so read it bit-by-bit.
        ຖ້າ (changes_press) {
            ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < parimaa_na(k_aAndroidButtons); i++) {
                ຖ້າ (changes_press & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, window, SDL_DEFAULT_MOUSE_ID, button, true);
                }
            }
            last_state = state;
        }

        ຖ້າ (changes_release) {
            ສຳລັບ (ຈຳນວນເຕັມ i = 0; i < parimaa_na(k_aAndroidButtons); i++) {
                ຖ້າ (changes_release & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, window, SDL_DEFAULT_MOUSE_ID, button, false);
                }
            }
            last_state = state;
        }
        bha_nga;        

    default:
        bha_nga;
    }
}

#endif // SDL_VIDEO_DRIVER_ANDROID

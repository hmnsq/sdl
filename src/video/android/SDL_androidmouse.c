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

struct SDL_CursorData
{
    số_nguyên custom_cursor;
    số_nguyên system_cursor;
};

static const char k_aAndroidButtons[] = { BUTTON_PRIMARY, BUTTON_SECONDARY, BUTTON_TERTIARY, BUTTON_BACK, BUTTON_FORWARD };

// Last known Android mouse button state (includes all buttons)
static số_nguyên last_state;

// Blank cursor
static SDL_Cursor *empty_cursor;

static SDL_Cursor *Android_WrapCursor(số_nguyên custom_cursor, số_nguyên system_cursor)
{
    SDL_Cursor *cursor;

    cursor = SDL_calloc(1, sizeof(*cursor));
    nếu (cursor) {
        SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, sizeof(*data));
        nếu (data) {
            data->custom_cursor = custom_cursor;
            data->system_cursor = system_cursor;
            cursor->internal = data;
        } không_thì {
            SDL_free(cursor);
            cursor = NULL;
        }
    }

    trả_về cursor;
}

static SDL_Cursor *Android_CreateDefaultCursor(void)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    trả_về Android_WrapCursor(0, id);
}

static SDL_Cursor *Android_CreateCursor(SDL_Surface *surface, số_nguyên hot_x, số_nguyên hot_y)
{
    số_nguyên custom_cursor;
    SDL_Surface *converted;

    converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
    nếu (!converted) {
        trả_về NULL;
    }
    custom_cursor = Android_JNI_CreateCustomCursor(converted, hot_x, hot_y);
    SDL_DestroySurface(converted);
    nếu (!custom_cursor) {
        SDL_Unsupported();
        trả_về NULL;
    }
    trả_về Android_WrapCursor(custom_cursor, 0);
}

static SDL_Cursor *Android_CreateSystemCursor(SDL_SystemCursor id)
{
    trả_về Android_WrapCursor(0, id);
}

static void Android_FreeCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *data = cursor->internal;
    nếu (data->custom_cursor != 0) {
        Android_JNI_DestroyCustomCursor(data->custom_cursor);
    }
    SDL_free(cursor->internal);
    SDL_free(cursor);
}

static SDL_Cursor *Android_CreateEmptyCursor(void)
{
    nếu (!empty_cursor) {
        SDL_Surface *empty_surface = SDL_CreateSurfaceZeroed(1, 1, SDL_PIXELFORMAT_ARGB8888);
        nếu (empty_surface) {
            empty_cursor = Android_CreateCursor(empty_surface, 0, 0);
            SDL_DestroySurface(empty_surface);
        }
    }
    trả_về empty_cursor;
}

static void Android_DestroyEmptyCursor(void)
{
    nếu (empty_cursor) {
        Android_FreeCursor(empty_cursor);
        empty_cursor = NULL;
    }
}

static bool Android_ShowCursor(SDL_Cursor *cursor)
{
    nếu (!cursor) {
        cursor = Android_CreateEmptyCursor();
    }
    nếu (cursor) {
        SDL_CursorData *data = cursor->internal;
        nếu (data->custom_cursor) {
            nếu (!Android_JNI_SetCustomCursor(data->custom_cursor)) {
                trả_về SDL_Unsupported();
            }
        } không_thì {
            nếu (!Android_JNI_SetSystemCursor(data->system_cursor)) {
                trả_về SDL_Unsupported();
            }
        }
        trả_về true;
    } không_thì {
        // SDL error set inside Android_CreateEmptyCursor()
        trả_về false;
    }
}

static bool Android_SetRelativeMouseMode(bool enabled)
{
    nếu (!Android_JNI_SupportsRelativeMouse()) {
        trả_về SDL_Unsupported();
    }

    nếu (!Android_JNI_SetRelativeMouseEnabled(enabled)) {
        trả_về SDL_Unsupported();
    }

    trả_về true;
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
static Uint8 TranslateButton(số_nguyên state)
{
    nếu (state & BUTTON_PRIMARY) {
        trả_về SDL_BUTTON_LEFT;
    } không_thì nếu (state & BUTTON_SECONDARY) {
        trả_về SDL_BUTTON_RIGHT;
    } không_thì nếu (state & BUTTON_TERTIARY) {
        trả_về SDL_BUTTON_MIDDLE;
    } không_thì nếu (state & BUTTON_FORWARD) {
        trả_về SDL_BUTTON_X1;
    } không_thì nếu (state & BUTTON_BACK) {
        trả_về SDL_BUTTON_X2;
    } không_thì {
        trả_về 0;
    }
}

void Android_OnMouse(SDL_Window *window, số_nguyên state, số_nguyên action, float x, float y, bool relative)
{
    số_nguyên changes_press;
    số_nguyên changes_release;
    Uint8 button;

    nếu (!window) {
        trả_về;
    }

    switch (action) {
    case ACTION_MOVE:
    case ACTION_HOVER_MOVE:
        SDL_SendMouseMotion(0, window, SDL_DEFAULT_MOUSE_ID, relative, x, y);
        break;

    case ACTION_SCROLL:
        SDL_SendMouseWheel(0, window, SDL_DEFAULT_MOUSE_ID, x, y, SDL_MOUSEWHEEL_NORMAL);
        break;

    case ACTION_UP:
    case ACTION_DOWN:
    case ACTION_BUTTON_PRESS:
    case ACTION_BUTTON_RELEASE:
    case ACTION_HOVER_ENTER:
    case ACTION_HOVER_EXIT:
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
        nếu (changes_press) {
            cho (số_nguyên i = 0; i < sizeof(k_aAndroidButtons); i++) {
                nếu (changes_press & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, window, SDL_DEFAULT_MOUSE_ID, button, true);
                }
            }
            last_state = state;
        }

        nếu (changes_release) {
            cho (số_nguyên i = 0; i < sizeof(k_aAndroidButtons); i++) {
                nếu (changes_release & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, window, SDL_DEFAULT_MOUSE_ID, button, false);
                }
            }
            last_state = state;
        }
        break;        

    default:
        break;
    }
}

#endif // SDL_VIDEO_DRIVER_ANDROID

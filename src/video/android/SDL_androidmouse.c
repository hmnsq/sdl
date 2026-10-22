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

#ifdef SDL_VIDEO_DRIVER_ANDROID

#ضمن "SDL_androidmouse.h"

#ضمن "../../events/SDL_mouse_c.h"

#ضمن "../../core/android/SDL_android.h"

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

بنية SDL_CursorData
{
    صحيح custom_cursor;
    صحيح system_cursor;
};

ساكن ثابت حرف k_aAndroidButtons[] = { BUTTON_PRIMARY, BUTTON_SECONDARY, BUTTON_TERTIARY, BUTTON_BACK, BUTTON_FORWARD };

// Last known Android mouse button state (includes all buttons)
ساكن صحيح last_state;

// Blank cursor
ساكن SDL_Cursor *empty_cursor;

ساكن SDL_Cursor *Android_WrapCursor(صحيح custom_cursor, صحيح system_cursor)
{
    SDL_Cursor *cursor;

    cursor = SDL_calloc(1, حجم(*cursor));
    إذا (cursor) {
        SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, حجم(*data));
        إذا (data) {
            data->custom_cursor = custom_cursor;
            data->system_cursor = system_cursor;
            cursor->internal = data;
        } وإلا {
            SDL_free(cursor);
            cursor = عدم;
        }
    }

    أرجع cursor;
}

ساكن SDL_Cursor *Android_CreateDefaultCursor(فراغ)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    أرجع Android_WrapCursor(0, id);
}

ساكن SDL_Cursor *Android_CreateCursor(SDL_Surface *surface, صحيح hot_x, صحيح hot_y)
{
    صحيح custom_cursor;
    SDL_Surface *converted;

    converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
    إذا (!converted) {
        أرجع عدم;
    }
    custom_cursor = Android_JNI_CreateCustomCursor(converted, hot_x, hot_y);
    SDL_DestroySurface(converted);
    إذا (!custom_cursor) {
        SDL_Unsupported();
        أرجع عدم;
    }
    أرجع Android_WrapCursor(custom_cursor, 0);
}

ساكن SDL_Cursor *Android_CreateSystemCursor(SDL_SystemCursor id)
{
    أرجع Android_WrapCursor(0, id);
}

ساكن فراغ Android_FreeCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *data = cursor->internal;
    إذا (data->custom_cursor != 0) {
        Android_JNI_DestroyCustomCursor(data->custom_cursor);
    }
    SDL_free(cursor->internal);
    SDL_free(cursor);
}

ساكن SDL_Cursor *Android_CreateEmptyCursor(فراغ)
{
    إذا (!empty_cursor) {
        SDL_Surface *empty_surface = SDL_CreateSurfaceZeroed(1, 1, SDL_PIXELFORMAT_ARGB8888);
        إذا (empty_surface) {
            empty_cursor = Android_CreateCursor(empty_surface, 0, 0);
            SDL_DestroySurface(empty_surface);
        }
    }
    أرجع empty_cursor;
}

ساكن فراغ Android_DestroyEmptyCursor(فراغ)
{
    إذا (empty_cursor) {
        Android_FreeCursor(empty_cursor);
        empty_cursor = عدم;
    }
}

ساكن bool Android_ShowCursor(SDL_Cursor *cursor)
{
    إذا (!cursor) {
        cursor = Android_CreateEmptyCursor();
    }
    إذا (cursor) {
        SDL_CursorData *data = cursor->internal;
        إذا (data->custom_cursor) {
            إذا (!Android_JNI_SetCustomCursor(data->custom_cursor)) {
                أرجع SDL_Unsupported();
            }
        } وإلا {
            إذا (!Android_JNI_SetSystemCursor(data->system_cursor)) {
                أرجع SDL_Unsupported();
            }
        }
        أرجع true;
    } وإلا {
        // SDL error set inside Android_CreateEmptyCursor()
        أرجع false;
    }
}

ساكن bool Android_SetRelativeMouseMode(bool enabled)
{
    إذا (!Android_JNI_SupportsRelativeMouse()) {
        أرجع SDL_Unsupported();
    }

    إذا (!Android_JNI_SetRelativeMouseEnabled(enabled)) {
        أرجع SDL_Unsupported();
    }

    أرجع true;
}

فراغ Android_InitMouse(فراغ)
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

فراغ Android_QuitMouse(فراغ)
{
    Android_DestroyEmptyCursor();
}

// Translate Android mouse button state to SDL mouse button
ساكن Uint8 TranslateButton(صحيح state)
{
    إذا (state & BUTTON_PRIMARY) {
        أرجع SDL_BUTTON_بایاں;
    } وإلا إذا (state & BUTTON_SECONDARY) {
        أرجع SDL_BUTTON_دایاں;
    } وإلا إذا (state & BUTTON_TERTIARY) {
        أرجع SDL_BUTTON_درمیان;
    } وإلا إذا (state & BUTTON_FORWARD) {
        أرجع SDL_BUTTON_X1;
    } وإلا إذا (state & BUTTON_BACK) {
        أرجع SDL_BUTTON_X2;
    } وإلا {
        أرجع 0;
    }
}

فراغ Android_OnMouse(SDL_Window *window, صحيح state, صحيح action, عائم x, عائم y, bool relative)
{
    صحيح changes_press;
    صحيح changes_release;
    Uint8 button;

    إذا (!window) {
        أرجع;
    }

    بدل (action) {
    حالة ACTION_MOVE:
    حالة ACTION_HOVER_MOVE:
        SDL_SendMouseMotion(0, window, SDL_DEFAULT_MOUSE_ID, relative, x, y);
        اكسر;

    حالة ACTION_SCROLL:
        SDL_SendMouseWheel(0, window, SDL_DEFAULT_MOUSE_ID, x, y, SDL_MOUSEWHEEL_NORMAL);
        اكسر;

    حالة ACTION_UP:
    حالة ACTION_DOWN:
    حالة ACTION_BUTTON_PRESS:
    حالة ACTION_BUTTON_RELEASE:
    حالة ACTION_HOVER_ENTER:
    حالة ACTION_HOVER_EXIT:
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
        إذا (changes_press) {
            لكل (صحيح i = 0; i < حجم(k_aAndroidButtons); i++) {
                إذا (changes_press & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, window, SDL_DEFAULT_MOUSE_ID, button, true);
                }
            }
            last_state = state;
        }

        إذا (changes_release) {
            لكل (صحيح i = 0; i < حجم(k_aAndroidButtons); i++) {
                إذا (changes_release & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, window, SDL_DEFAULT_MOUSE_ID, button, false);
                }
            }
            last_state = state;
        }
        اكسر;        

    افتراضي:
        اكسر;
    }
}

#endif // SDL_VIDEO_DRIVER_ANDROID

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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_ANDROID

#ضمن "SDL_androidmouse.h"

#ضمن "../../events/SDL_mouse_c.h"

#ضمن "../../core/android/SDL_android.h"

// See Android's MotionEvent class for constants
#تعریف_کرو ACTION_تھلے           0
#تعریف_کرو ACTION_اتے             1
#تعریف_کرو ACTION_MOVE           2
#تعریف_کرو ACTION_CANCEL         3
#تعریف_کرو ACTION_HOVER_MOVE     7
#تعریف_کرو ACTION_SCROLL         8
#تعریف_کرو ACTION_HOVER_ENTER    9
#تعریف_کرو ACTION_HOVER_EXIT     10
#تعریف_کرو ACTION_BUTTON_PRESS   11
#تعریف_کرو ACTION_BUTTON_RELEASE 12

#تعریف_کرو BUTTON_PRIMARY        1
#تعریف_کرو BUTTON_SECONDARY      2
#تعریف_کرو BUTTON_TERTIARY       4
#تعریف_کرو BUTTON_پٹھ           8
#تعریف_کرو BUTTON_FORWARD        16

بنية SDL_Cursor_انکڑے
{
    صحيح custom_cursor;
    صحيح system_cursor;
};

ساكن ثابت حرف k_aAndroidButtons[] = { BUTTON_PRIMARY, BUTTON_SECONDARY, BUTTON_TERTIARY, BUTTON_پٹھ, BUTTON_FORWARD };

// Last known Android mouse button state (includes all buttons)
ساكن صحيح آخری_state;

// Blank cursor
ساكن SDL_Cursor *خالی_تھاواں_cursor;

ساكن SDL_Cursor *Android_WrapCursor(صحيح custom_cursor, صحيح system_cursor)
{
    SDL_Cursor *cursor;

    cursor = SDL_calloc(1, حجم(*cursor));
    إذا (cursor) {
        SDL_Cursor_انکڑے *انکڑے = (SDL_Cursor_انکڑے *)SDL_calloc(1, حجم(*انکڑے));
        إذا (انکڑے) {
            انکڑے->custom_cursor = custom_cursor;
            انکڑے->system_cursor = system_cursor;
            cursor->اندرونی = انکڑے;
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
    SDL_Cursor_انکڑے *انکڑے = cursor->اندرونی;
    إذا (انکڑے->custom_cursor != 0) {
        Android_JNI_DestroyCustomCursor(انکڑے->custom_cursor);
    }
    SDL_free(cursor->اندرونی);
    SDL_free(cursor);
}

ساكن SDL_Cursor *Android_Create_خالی_تھاواں_Cursor(فراغ)
{
    إذا (!خالی_تھاواں_cursor) {
        SDL_Surface *خالی_تھاواں_surface = SDL_CreateSurfaceZeroed(1, 1, SDL_PIXELFORMAT_ARGB8888);
        إذا (خالی_تھاواں_surface) {
            خالی_تھاواں_cursor = Android_CreateCursor(خالی_تھاواں_surface, 0, 0);
            SDL_DestroySurface(خالی_تھاواں_surface);
        }
    }
    أرجع خالی_تھاواں_cursor;
}

ساكن فراغ Android_Destroy_خالی_تھاواں_Cursor(فراغ)
{
    إذا (خالی_تھاواں_cursor) {
        Android_FreeCursor(خالی_تھاواں_cursor);
        خالی_تھاواں_cursor = عدم;
    }
}

ساكن bool Android_ShowCursor(SDL_Cursor *cursor)
{
    إذا (!cursor) {
        cursor = Android_Create_خالی_تھاواں_Cursor();
    }
    إذا (cursor) {
        SDL_Cursor_انکڑے *انکڑے = cursor->اندرونی;
        إذا (انکڑے->custom_cursor) {
            إذا (!Android_JNI_سیٹ_Custom_Cursor(انکڑے->custom_cursor)) {
                أرجع SDL_Unsupported();
            }
        } وإلا {
            إذا (!Android_JNI_سیٹ_System_Cursor(انکڑے->system_cursor)) {
                أرجع SDL_Unsupported();
            }
        }
        أرجع true;
    } وإلا {
        // SDL error set inside Android_CreateEmptyCursor()
        أرجع false;
    }
}

ساكن bool Android_سیٹ_Relative_Mouse_منوال(bool enabled)
{
    إذا (!Android_JNI_SupportsRelativeMouse()) {
        أرجع SDL_Unsupported();
    }

    إذا (!Android_JNI_سیٹ_Relative_Mouse_Enabled(enabled)) {
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
    mouse->سیٹ_Relative_Mouse_منوال = Android_سیٹ_Relative_Mouse_منوال;

    SDL_سیٹ_Default_Cursor(Android_CreateDefaultCursor());

    آخری_state = 0;
}

فراغ Android_QuitMouse(فراغ)
{
    Android_Destroy_خالی_تھاواں_Cursor();
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
    } وإلا إذا (state & BUTTON_پٹھ) {
        أرجع SDL_BUTTON_X2;
    } وإلا {
        أرجع 0;
    }
}

فراغ Android_OnMouse(SDL_کھڑکی *کھڑکی, صحيح state, صحيح action, عائم x, عائم y, bool relative)
{
    صحيح changes_press;
    صحيح changes_release;
    Uint8 button;

    إذا (!کھڑکی) {
        أرجع;
    }

    بدل (action) {
    حالة ACTION_MOVE:
    حالة ACTION_HOVER_MOVE:
        SDL_SendMouseMotion(0, کھڑکی, SDL_DEFAULT_MOUSE_ID, relative, x, y);
        اكسر;

    حالة ACTION_SCROLL:
        SDL_SendMouseWheel(0, کھڑکی, SDL_DEFAULT_MOUSE_ID, x, y, SDL_MOUSEWHEEL_عام);
        اكسر;

    حالة ACTION_اتے:
    حالة ACTION_تھلے:
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

        changes_press = state & ~آخری_state;
        changes_release = آخری_state & ~state;

        SDL_SendMouseMotion(0, کھڑکی, SDL_DEFAULT_MOUSE_ID, relative, x, y);

        // Some versions of Android will send multiple mouse buttons in a single
        // event, so read it bit-by-bit.
        إذا (changes_press) {
            لكل (صحيح i = 0; i < حجم(k_aAndroidButtons); i++) {
                إذا (changes_press & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, کھڑکی, SDL_DEFAULT_MOUSE_ID, button, true);
                }
            }
            آخری_state = state;
        }

        إذا (changes_release) {
            لكل (صحيح i = 0; i < حجم(k_aAndroidButtons); i++) {
                إذا (changes_release & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, کھڑکی, SDL_DEFAULT_MOUSE_ID, button, false);
                }
            }
            آخری_state = state;
        }
        اكسر;        

    افتراضي:
        اكسر;
    }
}

#جے_انت // SDL_VIDEO_DRIVER_ANDROID

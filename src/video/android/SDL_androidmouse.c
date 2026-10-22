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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_ANDROID

#ضمن "SDL_androidmouse.h"

#ضمن "../../events/SDL_mouse_c.h"

#ضمن "../../core/android/SDL_android.h"

// See Android's MotionEvent class for constants
#تعریف_کن ACTION_پایین           0
#تعریف_کن ACTION_به_بالا             1
#تعریف_کن ACTION_MOVE           2
#تعریف_کن ACTION_CANCEL         3
#تعریف_کن ACTION_HOVER_MOVE     7
#تعریف_کن ACTION_SCROLL         8
#تعریف_کن ACTION_HOVER_ENTER    9
#تعریف_کن ACTION_HOVER_EXIT     10
#تعریف_کن ACTION_BUTTON_PRESS   11
#تعریف_کن ACTION_BUTTON_RELEASE 12

#تعریف_کن BUTTON_PRIMARY        1
#تعریف_کن BUTTON_SECONDARY      2
#تعریف_کن BUTTON_TERTIARY       4
#تعریف_کن BUTTON_پشت           8
#تعریف_کن BUTTON_FORWARD        16

بنية SDL_Cursor_داده
{
    صحيح custom_cursor;
    صحيح system_cursor;
};

ساكن ثابت حرف k_aAndroidButtons[] = { BUTTON_PRIMARY, BUTTON_SECONDARY, BUTTON_TERTIARY, BUTTON_پشت, BUTTON_FORWARD };

// Last known Android mouse button state (includes all buttons)
ساكن صحيح آخرین_state;

// Blank cursor
ساكن SDL_Cursor *خالی_cursor;

ساكن SDL_Cursor *Android_WrapCursor(صحيح custom_cursor, صحيح system_cursor)
{
    SDL_Cursor *cursor;

    cursor = SDL_calloc(1, حجم(*cursor));
    إذا (cursor) {
        SDL_Cursor_داده *داده = (SDL_Cursor_داده *)SDL_calloc(1, حجم(*داده));
        إذا (داده) {
            داده->custom_cursor = custom_cursor;
            داده->system_cursor = system_cursor;
            cursor->داخلی = داده;
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
    SDL_Cursor_داده *داده = cursor->داخلی;
    إذا (داده->custom_cursor != 0) {
        Android_JNI_DestroyCustomCursor(داده->custom_cursor);
    }
    SDL_free(cursor->داخلی);
    SDL_free(cursor);
}

ساكن SDL_Cursor *Android_Create_خالی_Cursor(فراغ)
{
    إذا (!خالی_cursor) {
        SDL_Surface *خالی_surface = SDL_CreateSurfaceZeroed(1, 1, SDL_PIXELFORMAT_ARGB8888);
        إذا (خالی_surface) {
            خالی_cursor = Android_CreateCursor(خالی_surface, 0, 0);
            SDL_DestroySurface(خالی_surface);
        }
    }
    أرجع خالی_cursor;
}

ساكن فراغ Android_Destroy_خالی_Cursor(فراغ)
{
    إذا (خالی_cursor) {
        Android_FreeCursor(خالی_cursor);
        خالی_cursor = عدم;
    }
}

ساكن bool Android_ShowCursor(SDL_Cursor *cursor)
{
    إذا (!cursor) {
        cursor = Android_Create_خالی_Cursor();
    }
    إذا (cursor) {
        SDL_Cursor_داده *داده = cursor->داخلی;
        إذا (داده->custom_cursor) {
            إذا (!Android_JNI_مجموعه_Custom_Cursor(داده->custom_cursor)) {
                أرجع SDL_Unsupported();
            }
        } وإلا {
            إذا (!Android_JNI_مجموعه_System_Cursor(داده->system_cursor)) {
                أرجع SDL_Unsupported();
            }
        }
        أرجع true;
    } وإلا {
        // SDL error set inside Android_CreateEmptyCursor()
        أرجع false;
    }
}

ساكن bool Android_مجموعه_Relative_Mouse_نما(bool enabled)
{
    إذا (!Android_JNI_SupportsRelativeMouse()) {
        أرجع SDL_Unsupported();
    }

    إذا (!Android_JNI_مجموعه_Relative_Mouse_Enabled(enabled)) {
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
    mouse->مجموعه_Relative_Mouse_نما = Android_مجموعه_Relative_Mouse_نما;

    SDL_مجموعه_Default_Cursor(Android_CreateDefaultCursor());

    آخرین_state = 0;
}

فراغ Android_QuitMouse(فراغ)
{
    Android_Destroy_خالی_Cursor();
}

// Translate Android mouse button state to SDL mouse button
ساكن Uint8 TranslateButton(صحيح state)
{
    إذا (state & BUTTON_PRIMARY) {
        أرجع SDL_BUTTON_چپ;
    } وإلا إذا (state & BUTTON_SECONDARY) {
        أرجع SDL_BUTTON_راست;
    } وإلا إذا (state & BUTTON_TERTIARY) {
        أرجع SDL_BUTTON_میانه;
    } وإلا إذا (state & BUTTON_FORWARD) {
        أرجع SDL_BUTTON_X1;
    } وإلا إذا (state & BUTTON_پشت) {
        أرجع SDL_BUTTON_X2;
    } وإلا {
        أرجع 0;
    }
}

فراغ Android_OnMouse(SDL_پنجره *پنجره, صحيح state, صحيح action, عائم x, عائم y, bool relative)
{
    صحيح changes_press;
    صحيح changes_release;
    Uint8 button;

    إذا (!پنجره) {
        أرجع;
    }

    بدل (action) {
    حالة ACTION_MOVE:
    حالة ACTION_HOVER_MOVE:
        SDL_SendMouseMotion(0, پنجره, SDL_DEFAULT_MOUSE_ID, relative, x, y);
        اكسر;

    حالة ACTION_SCROLL:
        SDL_SendMouseWheel(0, پنجره, SDL_DEFAULT_MOUSE_ID, x, y, SDL_MOUSEWHEEL_نرمال);
        اكسر;

    حالة ACTION_به_بالا:
    حالة ACTION_پایین:
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

        changes_press = state & ~آخرین_state;
        changes_release = آخرین_state & ~state;

        SDL_SendMouseMotion(0, پنجره, SDL_DEFAULT_MOUSE_ID, relative, x, y);

        // Some versions of Android will send multiple mouse buttons in a single
        // event, so read it bit-by-bit.
        إذا (changes_press) {
            لكل (صحيح i = 0; i < حجم(k_aAndroidButtons); i++) {
                إذا (changes_press & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, پنجره, SDL_DEFAULT_MOUSE_ID, button, true);
                }
            }
            آخرین_state = state;
        }

        إذا (changes_release) {
            لكل (صحيح i = 0; i < حجم(k_aAndroidButtons); i++) {
                إذا (changes_release & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, پنجره, SDL_DEFAULT_MOUSE_ID, button, false);
                }
            }
            آخرین_state = state;
        }
        اكسر;        

    افتراضي:
        اكسر;
    }
}

#پایان_اگر // SDL_VIDEO_DRIVER_ANDROID

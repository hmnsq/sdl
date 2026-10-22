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

#که_تعریف_شوی SDL_VIDEO_DRIVER_ANDROID

#ضمن "SDL_androidmouse.h"

#ضمن "../../events/SDL_mouse_c.h"

#ضمن "../../core/android/SDL_android.h"

// See Android's MotionEvent class for constants
#تعریف_کړه ACTION_ښکته           0
#تعریف_کړه ACTION_پورته             1
#تعریف_کړه ACTION_MOVE           2
#تعریف_کړه ACTION_CANCEL         3
#تعریف_کړه ACTION_HOVER_MOVE     7
#تعریف_کړه ACTION_SCROLL         8
#تعریف_کړه ACTION_HOVER_ENTER    9
#تعریف_کړه ACTION_HOVER_EXIT     10
#تعریف_کړه ACTION_BUTTON_PRESS   11
#تعریف_کړه ACTION_BUTTON_RELEASE 12

#تعریف_کړه BUTTON_PRIMARY        1
#تعریف_کړه BUTTON_SECONDARY      2
#تعریف_کړه BUTTON_TERTIARY       4
#تعریف_کړه BUTTON_شا           8
#تعریف_کړه BUTTON_FORWARD        16

بنية SDL_Cursor_معلومات
{
    صحيح custom_cursor;
    صحيح system_cursor;
};

ساكن ثابت حرف k_aAndroidButtons[] = { BUTTON_PRIMARY, BUTTON_SECONDARY, BUTTON_TERTIARY, BUTTON_شا, BUTTON_FORWARD };

// Last known Android mouse button state (includes all buttons)
ساكن صحيح وروستی_state;

// Blank cursor
ساكن SDL_Cursor *تشه_cursor;

ساكن SDL_Cursor *Android_WrapCursor(صحيح custom_cursor, صحيح system_cursor)
{
    SDL_Cursor *cursor;

    cursor = SDL_calloc(1, حجم(*cursor));
    إذا (cursor) {
        SDL_Cursor_معلومات *معلومات = (SDL_Cursor_معلومات *)SDL_calloc(1, حجم(*معلومات));
        إذا (معلومات) {
            معلومات->custom_cursor = custom_cursor;
            معلومات->system_cursor = system_cursor;
            cursor->دننی = معلومات;
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
    SDL_Cursor_معلومات *معلومات = cursor->دننی;
    إذا (معلومات->custom_cursor != 0) {
        Android_JNI_DestroyCustomCursor(معلومات->custom_cursor);
    }
    SDL_free(cursor->دننی);
    SDL_free(cursor);
}

ساكن SDL_Cursor *Android_Create_تشه_Cursor(فراغ)
{
    إذا (!تشه_cursor) {
        SDL_Surface *تشه_surface = SDL_CreateSurfaceZeroed(1, 1, SDL_PIXELFORMAT_ARGB8888);
        إذا (تشه_surface) {
            تشه_cursor = Android_CreateCursor(تشه_surface, 0, 0);
            SDL_DestroySurface(تشه_surface);
        }
    }
    أرجع تشه_cursor;
}

ساكن فراغ Android_Destroy_تشه_Cursor(فراغ)
{
    إذا (تشه_cursor) {
        Android_FreeCursor(تشه_cursor);
        تشه_cursor = عدم;
    }
}

ساكن bool Android_ShowCursor(SDL_Cursor *cursor)
{
    إذا (!cursor) {
        cursor = Android_Create_تشه_Cursor();
    }
    إذا (cursor) {
        SDL_Cursor_معلومات *معلومات = cursor->دننی;
        إذا (معلومات->custom_cursor) {
            إذا (!Android_JNI_سېټ_Custom_Cursor(معلومات->custom_cursor)) {
                أرجع SDL_Unsupported();
            }
        } وإلا {
            إذا (!Android_JNI_سېټ_System_Cursor(معلومات->system_cursor)) {
                أرجع SDL_Unsupported();
            }
        }
        أرجع true;
    } وإلا {
        // SDL error set inside Android_CreateEmptyCursor()
        أرجع false;
    }
}

ساكن bool Android_سېټ_Relative_Mouse_ډېرپېښ(bool enabled)
{
    إذا (!Android_JNI_SupportsRelativeMouse()) {
        أرجع SDL_Unsupported();
    }

    إذا (!Android_JNI_سېټ_Relative_Mouse_Enabled(enabled)) {
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
    mouse->سېټ_Relative_Mouse_ډېرپېښ = Android_سېټ_Relative_Mouse_ډېرپېښ;

    SDL_سېټ_Default_Cursor(Android_CreateDefaultCursor());

    وروستی_state = 0;
}

فراغ Android_QuitMouse(فراغ)
{
    Android_Destroy_تشه_Cursor();
}

// Translate Android mouse button state to SDL mouse button
ساكن Uint8 TranslateButton(صحيح state)
{
    إذا (state & BUTTON_PRIMARY) {
        أرجع SDL_BUTTON_کیڼ;
    } وإلا إذا (state & BUTTON_SECONDARY) {
        أرجع SDL_BUTTON_ښی;
    } وإلا إذا (state & BUTTON_TERTIARY) {
        أرجع SDL_BUTTON_منځ;
    } وإلا إذا (state & BUTTON_FORWARD) {
        أرجع SDL_BUTTON_X1;
    } وإلا إذا (state & BUTTON_شا) {
        أرجع SDL_BUTTON_X2;
    } وإلا {
        أرجع 0;
    }
}

فراغ Android_OnMouse(SDL_کړکۍ *کړکۍ, صحيح state, صحيح action, عائم x, عائم y, bool relative)
{
    صحيح changes_press;
    صحيح changes_release;
    Uint8 button;

    إذا (!کړکۍ) {
        أرجع;
    }

    بدل (action) {
    حالة ACTION_MOVE:
    حالة ACTION_HOVER_MOVE:
        SDL_SendMouseMotion(0, کړکۍ, SDL_DEFAULT_MOUSE_ID, relative, x, y);
        اكسر;

    حالة ACTION_SCROLL:
        SDL_SendMouseWheel(0, کړکۍ, SDL_DEFAULT_MOUSE_ID, x, y, SDL_MOUSEWHEEL_نورمال);
        اكسر;

    حالة ACTION_پورته:
    حالة ACTION_ښکته:
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

        changes_press = state & ~وروستی_state;
        changes_release = وروستی_state & ~state;

        SDL_SendMouseMotion(0, کړکۍ, SDL_DEFAULT_MOUSE_ID, relative, x, y);

        // Some versions of Android will send multiple mouse buttons in a single
        // event, so read it bit-by-bit.
        إذا (changes_press) {
            لكل (صحيح i = 0; i < حجم(k_aAndroidButtons); i++) {
                إذا (changes_press & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, کړکۍ, SDL_DEFAULT_MOUSE_ID, button, true);
                }
            }
            وروستی_state = state;
        }

        إذا (changes_release) {
            لكل (صحيح i = 0; i < حجم(k_aAndroidButtons); i++) {
                إذا (changes_release & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, کړکۍ, SDL_DEFAULT_MOUSE_ID, button, false);
                }
            }
            وروستی_state = state;
        }
        اكسر;        

    افتراضي:
        اكسر;
    }
}

#د_که_پای // SDL_VIDEO_DRIVER_ANDROID

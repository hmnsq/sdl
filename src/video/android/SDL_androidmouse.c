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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_ANDROID

#ضمن "SDL_androidmouse.h"

#ضمن "../../events/SDL_mouse_c.h"

#ضمن "../../core/android/SDL_android.h"

// See Android's MotionEvent class for constants
#وصف_ڪريو ACTION_هيٺ_ڏانهن           0
#وصف_ڪريو ACTION_مٿي             1
#وصف_ڪريو ACTION_MOVE           2
#وصف_ڪريو ACTION_CANCEL         3
#وصف_ڪريو ACTION_HOVER_MOVE     7
#وصف_ڪريو ACTION_SCROLL         8
#وصف_ڪريو ACTION_HOVER_ENTER    9
#وصف_ڪريو ACTION_HOVER_EXIT     10
#وصف_ڪريو ACTION_BUTTON_PRESS   11
#وصف_ڪريو ACTION_BUTTON_RELEASE 12

#وصف_ڪريو BUTTON_PRIMARY        1
#وصف_ڪريو BUTTON_SECONDARY      2
#وصف_ڪريو BUTTON_TERTIARY       4
#وصف_ڪريو BUTTON_پٺ           8
#وصف_ڪريو BUTTON_FORWARD        16

بنية SDL_Cursor_معلومات
{
    صحيح custom_cursor;
    صحيح system_cursor;
};

ساكن ثابت حرف k_aAndroidButtons[] = { BUTTON_PRIMARY, BUTTON_SECONDARY, BUTTON_TERTIARY, BUTTON_پٺ, BUTTON_FORWARD };

// Last known Android mouse button state (includes all buttons)
ساكن صحيح آخري_state;

// Blank cursor
ساكن SDL_Cursor *خالي_جايون_cursor;

ساكن SDL_Cursor *Android_WrapCursor(صحيح custom_cursor, صحيح system_cursor)
{
    SDL_Cursor *cursor;

    cursor = SDL_calloc(1, حجم(*cursor));
    إذا (cursor) {
        SDL_Cursor_معلومات *معلومات = (SDL_Cursor_معلومات *)SDL_calloc(1, حجم(*معلومات));
        إذا (معلومات) {
            معلومات->custom_cursor = custom_cursor;
            معلومات->system_cursor = system_cursor;
            cursor->اندروني = معلومات;
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
    SDL_Cursor_معلومات *معلومات = cursor->اندروني;
    إذا (معلومات->custom_cursor != 0) {
        Android_JNI_DestroyCustomCursor(معلومات->custom_cursor);
    }
    SDL_free(cursor->اندروني);
    SDL_free(cursor);
}

ساكن SDL_Cursor *Android_Create_خالي_جايون_Cursor(فراغ)
{
    إذا (!خالي_جايون_cursor) {
        SDL_Surface *خالي_جايون_surface = SDL_CreateSurfaceZeroed(1, 1, SDL_PIXELFORMAT_ARGB8888);
        إذا (خالي_جايون_surface) {
            خالي_جايون_cursor = Android_CreateCursor(خالي_جايون_surface, 0, 0);
            SDL_DestroySurface(خالي_جايون_surface);
        }
    }
    أرجع خالي_جايون_cursor;
}

ساكن فراغ Android_Destroy_خالي_جايون_Cursor(فراغ)
{
    إذا (خالي_جايون_cursor) {
        Android_FreeCursor(خالي_جايون_cursor);
        خالي_جايون_cursor = عدم;
    }
}

ساكن bool Android_ShowCursor(SDL_Cursor *cursor)
{
    إذا (!cursor) {
        cursor = Android_Create_خالي_جايون_Cursor();
    }
    إذا (cursor) {
        SDL_Cursor_معلومات *معلومات = cursor->اندروني;
        إذا (معلومات->custom_cursor) {
            إذا (!Android_JNI_سيٽ_Custom_Cursor(معلومات->custom_cursor)) {
                أرجع SDL_Unsupported();
            }
        } وإلا {
            إذا (!Android_JNI_سيٽ_System_Cursor(معلومات->system_cursor)) {
                أرجع SDL_Unsupported();
            }
        }
        أرجع true;
    } وإلا {
        // SDL error set inside Android_CreateEmptyCursor()
        أرجع false;
    }
}

ساكن bool Android_سيٽ_Relative_Mouse_گهڻائي(bool enabled)
{
    إذا (!Android_JNI_SupportsRelativeMouse()) {
        أرجع SDL_Unsupported();
    }

    إذا (!Android_JNI_سيٽ_Relative_Mouse_Enabled(enabled)) {
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
    mouse->سيٽ_Relative_Mouse_گهڻائي = Android_سيٽ_Relative_Mouse_گهڻائي;

    SDL_سيٽ_Default_Cursor(Android_CreateDefaultCursor());

    آخري_state = 0;
}

فراغ Android_QuitMouse(فراغ)
{
    Android_Destroy_خالي_جايون_Cursor();
}

// Translate Android mouse button state to SDL mouse button
ساكن Uint8 TranslateButton(صحيح state)
{
    إذا (state & BUTTON_PRIMARY) {
        أرجع SDL_BUTTON_کاٻو;
    } وإلا إذا (state & BUTTON_SECONDARY) {
        أرجع SDL_BUTTON_ساڄو;
    } وإلا إذا (state & BUTTON_TERTIARY) {
        أرجع SDL_BUTTON_وچ;
    } وإلا إذا (state & BUTTON_FORWARD) {
        أرجع SDL_BUTTON_X1;
    } وإلا إذا (state & BUTTON_پٺ) {
        أرجع SDL_BUTTON_X2;
    } وإلا {
        أرجع 0;
    }
}

فراغ Android_OnMouse(SDL_دري *دري, صحيح state, صحيح action, عائم x, عائم y, bool relative)
{
    صحيح changes_press;
    صحيح changes_release;
    Uint8 button;

    إذا (!دري) {
        أرجع;
    }

    بدل (action) {
    حالة ACTION_MOVE:
    حالة ACTION_HOVER_MOVE:
        SDL_SendMouseMotion(0, دري, SDL_DEFAULT_MOUSE_ID, relative, x, y);
        اكسر;

    حالة ACTION_SCROLL:
        SDL_SendMouseWheel(0, دري, SDL_DEFAULT_MOUSE_ID, x, y, SDL_MOUSEWHEEL_عام);
        اكسر;

    حالة ACTION_مٿي:
    حالة ACTION_هيٺ_ڏانهن:
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

        changes_press = state & ~آخري_state;
        changes_release = آخري_state & ~state;

        SDL_SendMouseMotion(0, دري, SDL_DEFAULT_MOUSE_ID, relative, x, y);

        // Some versions of Android will send multiple mouse buttons in a single
        // event, so read it bit-by-bit.
        إذا (changes_press) {
            لكل (صحيح i = 0; i < حجم(k_aAndroidButtons); i++) {
                إذا (changes_press & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, دري, SDL_DEFAULT_MOUSE_ID, button, true);
                }
            }
            آخري_state = state;
        }

        إذا (changes_release) {
            لكل (صحيح i = 0; i < حجم(k_aAndroidButtons); i++) {
                إذا (changes_release & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, دري, SDL_DEFAULT_MOUSE_ID, button, false);
                }
            }
            آخري_state = state;
        }
        اكسر;        

    افتراضي:
        اكسر;
    }
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_ANDROID

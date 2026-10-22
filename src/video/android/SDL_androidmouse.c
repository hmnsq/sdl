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

#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_ANDROID

#شامل "SDL_androidmouse.h"

#شامل "../../events/SDL_mouse_c.h"

#شامل "../../core/android/SDL_android.h"

// See Android's MotionEvent class for constants
#تعریف_کرو ACTION_نیچے_کو           0
#تعریف_کرو ACTION_اوپر             1
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
#تعریف_کرو BUTTON_عقب           8
#تعریف_کرو BUTTON_FORWARD        16

ساخت SDL_Cursor_ڈیٹا
{
    صحیح custom_cursor;
    صحیح system_cursor;
};

ساکن ثابت حرف k_aAndroidButtons[] = { BUTTON_PRIMARY, BUTTON_SECONDARY, BUTTON_TERTIARY, BUTTON_عقب, BUTTON_FORWARD };

// Last known Android mouse button state (includes all buttons)
ساکن صحیح آخری_state;

// Blank cursor
ساکن SDL_Cursor *خالی_خانے_cursor;

ساکن SDL_Cursor *Android_WrapCursor(صحیح custom_cursor, صحیح system_cursor)
{
    SDL_Cursor *cursor;

    cursor = SDL_calloc(1, حجم(*cursor));
    اگر (cursor) {
        SDL_Cursor_ڈیٹا *ڈیٹا = (SDL_Cursor_ڈیٹا *)SDL_calloc(1, حجم(*ڈیٹا));
        اگر (ڈیٹا) {
            ڈیٹا->custom_cursor = custom_cursor;
            ڈیٹا->system_cursor = system_cursor;
            cursor->اندرونی_2 = ڈیٹا;
        } ورنہ {
            SDL_free(cursor);
            cursor = تہی;
        }
    }

    واپس cursor;
}

ساکن SDL_Cursor *Android_CreateDefaultCursor(خالی)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    واپس Android_WrapCursor(0, id);
}

ساکن SDL_Cursor *Android_CreateCursor(SDL_Surface *surface, صحیح hot_x, صحیح hot_y)
{
    صحیح custom_cursor;
    SDL_Surface *converted;

    converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
    اگر (!converted) {
        واپس تہی;
    }
    custom_cursor = Android_JNI_CreateCustomCursor(converted, hot_x, hot_y);
    SDL_DestroySurface(converted);
    اگر (!custom_cursor) {
        SDL_Unsupported();
        واپس تہی;
    }
    واپس Android_WrapCursor(custom_cursor, 0);
}

ساکن SDL_Cursor *Android_CreateSystemCursor(SDL_SystemCursor id)
{
    واپس Android_WrapCursor(0, id);
}

ساکن خالی Android_FreeCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_ڈیٹا *ڈیٹا = cursor->اندرونی_2;
    اگر (ڈیٹا->custom_cursor != 0) {
        Android_JNI_DestroyCustomCursor(ڈیٹا->custom_cursor);
    }
    SDL_free(cursor->اندرونی_2);
    SDL_free(cursor);
}

ساکن SDL_Cursor *Android_Create_خالی_خانے_Cursor(خالی)
{
    اگر (!خالی_خانے_cursor) {
        SDL_Surface *خالی_خانے_surface = SDL_CreateSurfaceZeroed(1, 1, SDL_PIXELFORMAT_ARGB8888);
        اگر (خالی_خانے_surface) {
            خالی_خانے_cursor = Android_CreateCursor(خالی_خانے_surface, 0, 0);
            SDL_DestroySurface(خالی_خانے_surface);
        }
    }
    واپس خالی_خانے_cursor;
}

ساکن خالی Android_Destroy_خالی_خانے_Cursor(خالی)
{
    اگر (خالی_خانے_cursor) {
        Android_FreeCursor(خالی_خانے_cursor);
        خالی_خانے_cursor = تہی;
    }
}

ساکن bool Android_ShowCursor(SDL_Cursor *cursor)
{
    اگر (!cursor) {
        cursor = Android_Create_خالی_خانے_Cursor();
    }
    اگر (cursor) {
        SDL_Cursor_ڈیٹا *ڈیٹا = cursor->اندرونی_2;
        اگر (ڈیٹا->custom_cursor) {
            اگر (!Android_JNI_سیٹ_Custom_Cursor(ڈیٹا->custom_cursor)) {
                واپس SDL_Unsupported();
            }
        } ورنہ {
            اگر (!Android_JNI_سیٹ_System_Cursor(ڈیٹا->system_cursor)) {
                واپس SDL_Unsupported();
            }
        }
        واپس true;
    } ورنہ {
        // SDL error set inside Android_CreateEmptyCursor()
        واپس false;
    }
}

ساکن bool Android_سیٹ_Relative_Mouse_منوال(bool enabled)
{
    اگر (!Android_JNI_SupportsRelativeMouse()) {
        واپس SDL_Unsupported();
    }

    اگر (!Android_JNI_سیٹ_Relative_Mouse_Enabled(enabled)) {
        واپس SDL_Unsupported();
    }

    واپس true;
}

خالی Android_InitMouse(خالی)
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

خالی Android_QuitMouse(خالی)
{
    Android_Destroy_خالی_خانے_Cursor();
}

// Translate Android mouse button state to SDL mouse button
ساکن Uint8 TranslateButton(صحیح state)
{
    اگر (state & BUTTON_PRIMARY) {
        واپس SDL_BUTTON_بایاں;
    } ورنہ اگر (state & BUTTON_SECONDARY) {
        واپس SDL_BUTTON_دایاں;
    } ورنہ اگر (state & BUTTON_TERTIARY) {
        واپس SDL_BUTTON_درمیان;
    } ورنہ اگر (state & BUTTON_FORWARD) {
        واپس SDL_BUTTON_X1;
    } ورنہ اگر (state & BUTTON_عقب) {
        واپس SDL_BUTTON_X2;
    } ورنہ {
        واپس 0;
    }
}

خالی Android_OnMouse(SDL_کھڑکی *کھڑکی, صحیح state, صحیح action, اعشاری x, اعشاری y, bool relative)
{
    صحیح changes_press;
    صحیح changes_release;
    Uint8 button;

    اگر (!کھڑکی) {
        واپس;
    }

    انتخاب (action) {
    حالت ACTION_MOVE:
    حالت ACTION_HOVER_MOVE:
        SDL_SendMouseMotion(0, کھڑکی, SDL_DEFAULT_MOUSE_ID, relative, x, y);
        توڑو;

    حالت ACTION_SCROLL:
        SDL_SendMouseWheel(0, کھڑکی, SDL_DEFAULT_MOUSE_ID, x, y, SDL_MOUSEWHEEL_معمول);
        توڑو;

    حالت ACTION_اوپر:
    حالت ACTION_نیچے_کو:
    حالت ACTION_BUTTON_PRESS:
    حالت ACTION_BUTTON_RELEASE:
    حالت ACTION_HOVER_ENTER:
    حالت ACTION_HOVER_EXIT:
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
        اگر (changes_press) {
            برائے (صحیح i = 0; i < حجم(k_aAndroidButtons); i++) {
                اگر (changes_press & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, کھڑکی, SDL_DEFAULT_MOUSE_ID, button, true);
                }
            }
            آخری_state = state;
        }

        اگر (changes_release) {
            برائے (صحیح i = 0; i < حجم(k_aAndroidButtons); i++) {
                اگر (changes_release & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, کھڑکی, SDL_DEFAULT_MOUSE_ID, button, false);
                }
            }
            آخری_state = state;
        }
        توڑو;        

    طےشدہ:
        توڑو;
    }
}

#اگر_ختم // SDL_VIDEO_DRIVER_ANDROID

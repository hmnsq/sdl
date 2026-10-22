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

#ifdef SDL_VIDEO_DRIVER_ANDROID

#شامل "SDL_androidmouse.h"

#شامل "../../events/SDL_mouse_c.h"

#شامل "../../core/android/SDL_android.h"

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

ساختار SDL_CursorData
{
    صحیح custom_cursor;
    صحیح system_cursor;
};

ایستا ثابت نویسه k_aAndroidButtons[] = { BUTTON_PRIMARY, BUTTON_SECONDARY, BUTTON_TERTIARY, BUTTON_BACK, BUTTON_FORWARD };

// Last known Android mouse button state (includes all buttons)
ایستا صحیح last_state;

// Blank cursor
ایستا SDL_Cursor *empty_cursor;

ایستا SDL_Cursor *Android_WrapCursor(صحیح custom_cursor, صحیح system_cursor)
{
    SDL_Cursor *cursor;

    cursor = SDL_calloc(1, اندازه(*cursor));
    اگر (cursor) {
        SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, اندازه(*data));
        اگر (data) {
            data->custom_cursor = custom_cursor;
            data->system_cursor = system_cursor;
            cursor->internal = data;
        } وگرنه {
            SDL_free(cursor);
            cursor = پوچ;
        }
    }

    بازگشت cursor;
}

ایستا SDL_Cursor *Android_CreateDefaultCursor(تهی)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    بازگشت Android_WrapCursor(0, id);
}

ایستا SDL_Cursor *Android_CreateCursor(SDL_Surface *surface, صحیح hot_x, صحیح hot_y)
{
    صحیح custom_cursor;
    SDL_Surface *converted;

    converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
    اگر (!converted) {
        بازگشت پوچ;
    }
    custom_cursor = Android_JNI_CreateCustomCursor(converted, hot_x, hot_y);
    SDL_DestroySurface(converted);
    اگر (!custom_cursor) {
        SDL_Unsupported();
        بازگشت پوچ;
    }
    بازگشت Android_WrapCursor(custom_cursor, 0);
}

ایستا SDL_Cursor *Android_CreateSystemCursor(SDL_SystemCursor id)
{
    بازگشت Android_WrapCursor(0, id);
}

ایستا تهی Android_FreeCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *data = cursor->internal;
    اگر (data->custom_cursor != 0) {
        Android_JNI_DestroyCustomCursor(data->custom_cursor);
    }
    SDL_free(cursor->internal);
    SDL_free(cursor);
}

ایستا SDL_Cursor *Android_CreateEmptyCursor(تهی)
{
    اگر (!empty_cursor) {
        SDL_Surface *empty_surface = SDL_CreateSurfaceZeroed(1, 1, SDL_PIXELFORMAT_ARGB8888);
        اگر (empty_surface) {
            empty_cursor = Android_CreateCursor(empty_surface, 0, 0);
            SDL_DestroySurface(empty_surface);
        }
    }
    بازگشت empty_cursor;
}

ایستا تهی Android_DestroyEmptyCursor(تهی)
{
    اگر (empty_cursor) {
        Android_FreeCursor(empty_cursor);
        empty_cursor = پوچ;
    }
}

ایستا bool Android_ShowCursor(SDL_Cursor *cursor)
{
    اگر (!cursor) {
        cursor = Android_CreateEmptyCursor();
    }
    اگر (cursor) {
        SDL_CursorData *data = cursor->internal;
        اگر (data->custom_cursor) {
            اگر (!Android_JNI_SetCustomCursor(data->custom_cursor)) {
                بازگشت SDL_Unsupported();
            }
        } وگرنه {
            اگر (!Android_JNI_SetSystemCursor(data->system_cursor)) {
                بازگشت SDL_Unsupported();
            }
        }
        بازگشت true;
    } وگرنه {
        // SDL error set inside Android_CreateEmptyCursor()
        بازگشت false;
    }
}

ایستا bool Android_SetRelativeMouseMode(bool enabled)
{
    اگر (!Android_JNI_SupportsRelativeMouse()) {
        بازگشت SDL_Unsupported();
    }

    اگر (!Android_JNI_SetRelativeMouseEnabled(enabled)) {
        بازگشت SDL_Unsupported();
    }

    بازگشت true;
}

تهی Android_InitMouse(تهی)
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

تهی Android_QuitMouse(تهی)
{
    Android_DestroyEmptyCursor();
}

// Translate Android mouse button state to SDL mouse button
ایستا Uint8 TranslateButton(صحیح state)
{
    اگر (state & BUTTON_PRIMARY) {
        بازگشت SDL_BUTTON_چپ;
    } وگرنه اگر (state & BUTTON_SECONDARY) {
        بازگشت SDL_BUTTON_راست;
    } وگرنه اگر (state & BUTTON_TERTIARY) {
        بازگشت SDL_BUTTON_میانه;
    } وگرنه اگر (state & BUTTON_FORWARD) {
        بازگشت SDL_BUTTON_X1;
    } وگرنه اگر (state & BUTTON_BACK) {
        بازگشت SDL_BUTTON_X2;
    } وگرنه {
        بازگشت 0;
    }
}

تهی Android_OnMouse(SDL_Window *window, صحیح state, صحیح action, اعشاری x, اعشاری y, bool relative)
{
    صحیح changes_press;
    صحیح changes_release;
    Uint8 button;

    اگر (!window) {
        بازگشت;
    }

    انتخاب (action) {
    حالت ACTION_MOVE:
    حالت ACTION_HOVER_MOVE:
        SDL_SendMouseMotion(0, window, SDL_DEFAULT_MOUSE_ID, relative, x, y);
        بشکن;

    حالت ACTION_SCROLL:
        SDL_SendMouseWheel(0, window, SDL_DEFAULT_MOUSE_ID, x, y, SDL_MOUSEWHEEL_NORMAL);
        بشکن;

    حالت ACTION_UP:
    حالت ACTION_DOWN:
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

        changes_press = state & ~last_state;
        changes_release = last_state & ~state;

        SDL_SendMouseMotion(0, window, SDL_DEFAULT_MOUSE_ID, relative, x, y);

        // Some versions of Android will send multiple mouse buttons in a single
        // event, so read it bit-by-bit.
        اگر (changes_press) {
            برای (صحیح i = 0; i < اندازه(k_aAndroidButtons); i++) {
                اگر (changes_press & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, window, SDL_DEFAULT_MOUSE_ID, button, true);
                }
            }
            last_state = state;
        }

        اگر (changes_release) {
            برای (صحیح i = 0; i < اندازه(k_aAndroidButtons); i++) {
                اگر (changes_release & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, window, SDL_DEFAULT_MOUSE_ID, button, false);
                }
            }
            last_state = state;
        }
        بشکن;        

    پیشفرض:
        بشکن;
    }
}

#endif // SDL_VIDEO_DRIVER_ANDROID

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

#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_ANDROID

#அந்தர்பாவ "SDL_androidmouse.h"

#அந்தர்பாவ "../../events/SDL_mouse_c.h"

#அந்தர்பாவ "../../core/android/SDL_android.h"

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

கட்டமைப்பு SDL_CursorData
{
    முழு custom_cursor;
    முழு system_cursor;
};

நிலையான மாறிலி எழுத்து k_aAndroidButtons[] = { BUTTON_PRIMARY, BUTTON_SECONDARY, BUTTON_TERTIARY, BUTTON_BACK, BUTTON_FORWARD };

// Last known Android mouse button state (includes all buttons)
நிலையான முழு last_state;

// Blank cursor
நிலையான SDL_Cursor *empty_cursor;

நிலையான SDL_Cursor *Android_WrapCursor(முழு custom_cursor, முழு system_cursor)
{
    SDL_Cursor *cursor;

    cursor = SDL_calloc(1, அளவு(*cursor));
    எனில் (cursor) {
        SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, அளவு(*data));
        எனில் (data) {
            data->custom_cursor = custom_cursor;
            data->system_cursor = system_cursor;
            cursor->internal = data;
        } இல்லையெனில் {
            SDL_free(cursor);
            cursor = வெற்று;
        }
    }

    திரும்பு cursor;
}

நிலையான SDL_Cursor *Android_CreateDefaultCursor(வெறுமை)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    திரும்பு Android_WrapCursor(0, id);
}

நிலையான SDL_Cursor *Android_CreateCursor(SDL_Surface *surface, முழு hot_x, முழு hot_y)
{
    முழு custom_cursor;
    SDL_Surface *converted;

    converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
    எனில் (!converted) {
        திரும்பு வெற்று;
    }
    custom_cursor = Android_JNI_CreateCustomCursor(converted, hot_x, hot_y);
    SDL_DestroySurface(converted);
    எனில் (!custom_cursor) {
        SDL_Unsupported();
        திரும்பு வெற்று;
    }
    திரும்பு Android_WrapCursor(custom_cursor, 0);
}

நிலையான SDL_Cursor *Android_CreateSystemCursor(SDL_SystemCursor id)
{
    திரும்பு Android_WrapCursor(0, id);
}

நிலையான வெறுமை Android_FreeCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *data = cursor->internal;
    எனில் (data->custom_cursor != 0) {
        Android_JNI_DestroyCustomCursor(data->custom_cursor);
    }
    SDL_free(cursor->internal);
    SDL_free(cursor);
}

நிலையான SDL_Cursor *Android_CreateEmptyCursor(வெறுமை)
{
    எனில் (!empty_cursor) {
        SDL_Surface *empty_surface = SDL_CreateSurfaceZeroed(1, 1, SDL_PIXELFORMAT_ARGB8888);
        எனில் (empty_surface) {
            empty_cursor = Android_CreateCursor(empty_surface, 0, 0);
            SDL_DestroySurface(empty_surface);
        }
    }
    திரும்பு empty_cursor;
}

நிலையான வெறுமை Android_DestroyEmptyCursor(வெறுமை)
{
    எனில் (empty_cursor) {
        Android_FreeCursor(empty_cursor);
        empty_cursor = வெற்று;
    }
}

நிலையான bool Android_ShowCursor(SDL_Cursor *cursor)
{
    எனில் (!cursor) {
        cursor = Android_CreateEmptyCursor();
    }
    எனில் (cursor) {
        SDL_CursorData *data = cursor->internal;
        எனில் (data->custom_cursor) {
            எனில் (!Android_JNI_SetCustomCursor(data->custom_cursor)) {
                திரும்பு SDL_Unsupported();
            }
        } இல்லையெனில் {
            எனில் (!Android_JNI_SetSystemCursor(data->system_cursor)) {
                திரும்பு SDL_Unsupported();
            }
        }
        திரும்பு true;
    } இல்லையெனில் {
        // SDL error set inside Android_CreateEmptyCursor()
        திரும்பு false;
    }
}

நிலையான bool Android_SetRelativeMouseMode(bool enabled)
{
    எனில் (!Android_JNI_SupportsRelativeMouse()) {
        திரும்பு SDL_Unsupported();
    }

    எனில் (!Android_JNI_SetRelativeMouseEnabled(enabled)) {
        திரும்பு SDL_Unsupported();
    }

    திரும்பு true;
}

வெறுமை Android_InitMouse(வெறுமை)
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

வெறுமை Android_QuitMouse(வெறுமை)
{
    Android_DestroyEmptyCursor();
}

// Translate Android mouse button state to SDL mouse button
நிலையான Uint8 TranslateButton(முழு state)
{
    எனில் (state & BUTTON_PRIMARY) {
        திரும்பு SDL_BUTTON_இடது;
    } இல்லையெனில் எனில் (state & BUTTON_SECONDARY) {
        திரும்பு SDL_BUTTON_வலது;
    } இல்லையெனில் எனில் (state & BUTTON_TERTIARY) {
        திரும்பு SDL_BUTTON_நடு;
    } இல்லையெனில் எனில் (state & BUTTON_FORWARD) {
        திரும்பு SDL_BUTTON_X1;
    } இல்லையெனில் எனில் (state & BUTTON_BACK) {
        திரும்பு SDL_BUTTON_X2;
    } இல்லையெனில் {
        திரும்பு 0;
    }
}

வெறுமை Android_OnMouse(SDL_Window *window, முழு state, முழு action, தசம x, தசம y, bool relative)
{
    முழு changes_press;
    முழு changes_release;
    Uint8 button;

    எனில் (!window) {
        திரும்பு;
    }

    தேர்வு (action) {
    நிலை ACTION_MOVE:
    நிலை ACTION_HOVER_MOVE:
        SDL_SendMouseMotion(0, window, SDL_DEFAULT_MOUSE_ID, relative, x, y);
        நிறுத்து;

    நிலை ACTION_SCROLL:
        SDL_SendMouseWheel(0, window, SDL_DEFAULT_MOUSE_ID, x, y, SDL_MOUSEWHEEL_NORMAL);
        நிறுத்து;

    நிலை ACTION_UP:
    நிலை ACTION_DOWN:
    நிலை ACTION_BUTTON_PRESS:
    நிலை ACTION_BUTTON_RELEASE:
    நிலை ACTION_HOVER_ENTER:
    நிலை ACTION_HOVER_EXIT:
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
        எனில் (changes_press) {
            க்கு (முழு i = 0; i < அளவு(k_aAndroidButtons); i++) {
                எனில் (changes_press & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, window, SDL_DEFAULT_MOUSE_ID, button, true);
                }
            }
            last_state = state;
        }

        எனில் (changes_release) {
            க்கு (முழு i = 0; i < அளவு(k_aAndroidButtons); i++) {
                எனில் (changes_release & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, window, SDL_DEFAULT_MOUSE_ID, button, false);
                }
            }
            last_state = state;
        }
        நிறுத்து;        

    இயல்பு:
        நிறுத்து;
    }
}

#endif // SDL_VIDEO_DRIVER_ANDROID

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

#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_ANDROID

#ಅನ್ತರ್ಭಾವ "SDL_androidmouse.h"

#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"

#ಅನ್ತರ್ಭಾವ "../../core/android/SDL_android.h"

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

ಸಂರಚನಾ SDL_CursorData
{
    ಪೂರ್ಣಾಙ್ಕ custom_cursor;
    ಪೂರ್ಣಾಙ್ಕ system_cursor;
};

ಸ್ಥಿರ ಧ್ರುವ ವರ್ಣ k_aAndroidButtons[] = { BUTTON_PRIMARY, BUTTON_SECONDARY, BUTTON_TERTIARY, BUTTON_BACK, BUTTON_FORWARD };

// Last known Android mouse button state (includes all buttons)
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ last_state;

// Blank cursor
ಸ್ಥಿರ SDL_Cursor *empty_cursor;

ಸ್ಥಿರ SDL_Cursor *Android_WrapCursor(ಪೂರ್ಣಾಙ್ಕ custom_cursor, ಪೂರ್ಣಾಙ್ಕ system_cursor)
{
    SDL_Cursor *cursor;

    cursor = SDL_calloc(1, ಪರಿಮಾಣ(*cursor));
    ಯದಿ (cursor) {
        SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, ಪರಿಮಾಣ(*data));
        ಯದಿ (data) {
            data->custom_cursor = custom_cursor;
            data->system_cursor = system_cursor;
            cursor->internal = data;
        } ಅನ್ಯಥಾ {
            SDL_free(cursor);
            cursor = ರಿಕ್ತ;
        }
    }

    ಪ್ರತ್ಯಾಗಮ cursor;
}

ಸ್ಥಿರ SDL_Cursor *Android_CreateDefaultCursor(ಶೂನ್ಯ)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    ಪ್ರತ್ಯಾಗಮ Android_WrapCursor(0, id);
}

ಸ್ಥಿರ SDL_Cursor *Android_CreateCursor(SDL_Surface *surface, ಪೂರ್ಣಾಙ್ಕ hot_x, ಪೂರ್ಣಾಙ್ಕ hot_y)
{
    ಪೂರ್ಣಾಙ್ಕ custom_cursor;
    SDL_Surface *converted;

    converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
    ಯದಿ (!converted) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    custom_cursor = Android_JNI_CreateCustomCursor(converted, hot_x, hot_y);
    SDL_DestroySurface(converted);
    ಯದಿ (!custom_cursor) {
        SDL_Unsupported();
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }
    ಪ್ರತ್ಯಾಗಮ Android_WrapCursor(custom_cursor, 0);
}

ಸ್ಥಿರ SDL_Cursor *Android_CreateSystemCursor(SDL_SystemCursor id)
{
    ಪ್ರತ್ಯಾಗಮ Android_WrapCursor(0, id);
}

ಸ್ಥಿರ ಶೂನ್ಯ Android_FreeCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *data = cursor->internal;
    ಯದಿ (data->custom_cursor != 0) {
        Android_JNI_DestroyCustomCursor(data->custom_cursor);
    }
    SDL_free(cursor->internal);
    SDL_free(cursor);
}

ಸ್ಥಿರ SDL_Cursor *Android_CreateEmptyCursor(ಶೂನ್ಯ)
{
    ಯದಿ (!empty_cursor) {
        SDL_Surface *empty_surface = SDL_CreateSurfaceZeroed(1, 1, SDL_PIXELFORMAT_ARGB8888);
        ಯದಿ (empty_surface) {
            empty_cursor = Android_CreateCursor(empty_surface, 0, 0);
            SDL_DestroySurface(empty_surface);
        }
    }
    ಪ್ರತ್ಯಾಗಮ empty_cursor;
}

ಸ್ಥಿರ ಶೂನ್ಯ Android_DestroyEmptyCursor(ಶೂನ್ಯ)
{
    ಯದಿ (empty_cursor) {
        Android_FreeCursor(empty_cursor);
        empty_cursor = ರಿಕ್ತ;
    }
}

ಸ್ಥಿರ bool Android_ShowCursor(SDL_Cursor *cursor)
{
    ಯದಿ (!cursor) {
        cursor = Android_CreateEmptyCursor();
    }
    ಯದಿ (cursor) {
        SDL_CursorData *data = cursor->internal;
        ಯದಿ (data->custom_cursor) {
            ಯದಿ (!Android_JNI_SetCustomCursor(data->custom_cursor)) {
                ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
            }
        } ಅನ್ಯಥಾ {
            ಯದಿ (!Android_JNI_SetSystemCursor(data->system_cursor)) {
                ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
            }
        }
        ಪ್ರತ್ಯಾಗಮ true;
    } ಅನ್ಯಥಾ {
        // SDL error set inside Android_CreateEmptyCursor()
        ಪ್ರತ್ಯಾಗಮ false;
    }
}

ಸ್ಥಿರ bool Android_SetRelativeMouseMode(bool enabled)
{
    ಯದಿ (!Android_JNI_SupportsRelativeMouse()) {
        ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
    }

    ಯದಿ (!Android_JNI_SetRelativeMouseEnabled(enabled)) {
        ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
    }

    ಪ್ರತ್ಯಾಗಮ true;
}

ಶೂನ್ಯ Android_InitMouse(ಶೂನ್ಯ)
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

ಶೂನ್ಯ Android_QuitMouse(ಶೂನ್ಯ)
{
    Android_DestroyEmptyCursor();
}

// Translate Android mouse button state to SDL mouse button
ಸ್ಥಿರ Uint8 TranslateButton(ಪೂರ್ಣಾಙ್ಕ state)
{
    ಯದಿ (state & BUTTON_PRIMARY) {
        ಪ್ರತ್ಯಾಗಮ SDL_BUTTON_ಎಡ;
    } ಅನ್ಯಥಾ ಯದಿ (state & BUTTON_SECONDARY) {
        ಪ್ರತ್ಯಾಗಮ SDL_BUTTON_ಬಲ;
    } ಅನ್ಯಥಾ ಯದಿ (state & BUTTON_TERTIARY) {
        ಪ್ರತ್ಯಾಗಮ SDL_BUTTON_ಮಧ್ಯ;
    } ಅನ್ಯಥಾ ಯದಿ (state & BUTTON_FORWARD) {
        ಪ್ರತ್ಯಾಗಮ SDL_BUTTON_X1;
    } ಅನ್ಯಥಾ ಯದಿ (state & BUTTON_BACK) {
        ಪ್ರತ್ಯಾಗಮ SDL_BUTTON_X2;
    } ಅನ್ಯಥಾ {
        ಪ್ರತ್ಯಾಗಮ 0;
    }
}

ಶೂನ್ಯ Android_OnMouse(SDL_Window *window, ಪೂರ್ಣಾಙ್ಕ state, ಪೂರ್ಣಾಙ್ಕ action, ಭಿನ್ನ x, ಭಿನ್ನ y, bool relative)
{
    ಪೂರ್ಣಾಙ್ಕ changes_press;
    ಪೂರ್ಣಾಙ್ಕ changes_release;
    Uint8 button;

    ಯದಿ (!window) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    ವಿಕಲ್ಪ (action) {
    ಪಕ್ಷ ACTION_MOVE:
    ಪಕ್ಷ ACTION_HOVER_MOVE:
        SDL_SendMouseMotion(0, window, SDL_DEFAULT_MOUSE_ID, relative, x, y);
        ಭಙ್ಗ;

    ಪಕ್ಷ ACTION_SCROLL:
        SDL_SendMouseWheel(0, window, SDL_DEFAULT_MOUSE_ID, x, y, SDL_MOUSEWHEEL_NORMAL);
        ಭಙ್ಗ;

    ಪಕ್ಷ ACTION_UP:
    ಪಕ್ಷ ACTION_DOWN:
    ಪಕ್ಷ ACTION_BUTTON_PRESS:
    ಪಕ್ಷ ACTION_BUTTON_RELEASE:
    ಪಕ್ಷ ACTION_HOVER_ENTER:
    ಪಕ್ಷ ACTION_HOVER_EXIT:
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
        ಯದಿ (changes_press) {
            ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < ಪರಿಮಾಣ(k_aAndroidButtons); i++) {
                ಯದಿ (changes_press & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, window, SDL_DEFAULT_MOUSE_ID, button, true);
                }
            }
            last_state = state;
        }

        ಯದಿ (changes_release) {
            ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < ಪರಿಮಾಣ(k_aAndroidButtons); i++) {
                ಯದಿ (changes_release & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, window, SDL_DEFAULT_MOUSE_ID, button, false);
                }
            }
            last_state = state;
        }
        ಭಙ್ಗ;        

    ಸ್ವಭಾವ:
        ಭಙ್ಗ;
    }
}

#endif // SDL_VIDEO_DRIVER_ANDROID

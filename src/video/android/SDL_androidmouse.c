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

#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_ANDROID

#അന്തര്ഭാവ "SDL_androidmouse.h"

#അന്തര്ഭാവ "../../events/SDL_mouse_c.h"

#അന്തര്ഭാവ "../../core/android/SDL_android.h"

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

ഘടന SDL_CursorData
{
    പൂർണ്ണസംഖ്യ custom_cursor;
    പൂർണ്ണസംഖ്യ system_cursor;
};

സ്ഥിതം സ്ഥിരം അക്ഷരം k_aAndroidButtons[] = { BUTTON_PRIMARY, BUTTON_SECONDARY, BUTTON_TERTIARY, BUTTON_BACK, BUTTON_FORWARD };

// Last known Android mouse button state (includes all buttons)
സ്ഥിതം പൂർണ്ണസംഖ്യ last_state;

// Blank cursor
സ്ഥിതം SDL_Cursor *empty_cursor;

സ്ഥിതം SDL_Cursor *Android_WrapCursor(പൂർണ്ണസംഖ്യ custom_cursor, പൂർണ്ണസംഖ്യ system_cursor)
{
    SDL_Cursor *cursor;

    cursor = SDL_calloc(1, വലുപ്പം(*cursor));
    എങ്കിൽ (cursor) {
        SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, വലുപ്പം(*data));
        എങ്കിൽ (data) {
            data->custom_cursor = custom_cursor;
            data->system_cursor = system_cursor;
            cursor->internal = data;
        } അല്ലെങ്കിൽ {
            SDL_free(cursor);
            cursor = ശൂന്യ;
        }
    }

    തിരികെ cursor;
}

സ്ഥിതം SDL_Cursor *Android_CreateDefaultCursor(ശൂന്യം)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    തിരികെ Android_WrapCursor(0, id);
}

സ്ഥിതം SDL_Cursor *Android_CreateCursor(SDL_Surface *surface, പൂർണ്ണസംഖ്യ hot_x, പൂർണ്ണസംഖ്യ hot_y)
{
    പൂർണ്ണസംഖ്യ custom_cursor;
    SDL_Surface *converted;

    converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
    എങ്കിൽ (!converted) {
        തിരികെ ശൂന്യ;
    }
    custom_cursor = Android_JNI_CreateCustomCursor(converted, hot_x, hot_y);
    SDL_DestroySurface(converted);
    എങ്കിൽ (!custom_cursor) {
        SDL_Unsupported();
        തിരികെ ശൂന്യ;
    }
    തിരികെ Android_WrapCursor(custom_cursor, 0);
}

സ്ഥിതം SDL_Cursor *Android_CreateSystemCursor(SDL_SystemCursor id)
{
    തിരികെ Android_WrapCursor(0, id);
}

സ്ഥിതം ശൂന്യം Android_FreeCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *data = cursor->internal;
    എങ്കിൽ (data->custom_cursor != 0) {
        Android_JNI_DestroyCustomCursor(data->custom_cursor);
    }
    SDL_free(cursor->internal);
    SDL_free(cursor);
}

സ്ഥിതം SDL_Cursor *Android_CreateEmptyCursor(ശൂന്യം)
{
    എങ്കിൽ (!empty_cursor) {
        SDL_Surface *empty_surface = SDL_CreateSurfaceZeroed(1, 1, SDL_PIXELFORMAT_ARGB8888);
        എങ്കിൽ (empty_surface) {
            empty_cursor = Android_CreateCursor(empty_surface, 0, 0);
            SDL_DestroySurface(empty_surface);
        }
    }
    തിരികെ empty_cursor;
}

സ്ഥിതം ശൂന്യം Android_DestroyEmptyCursor(ശൂന്യം)
{
    എങ്കിൽ (empty_cursor) {
        Android_FreeCursor(empty_cursor);
        empty_cursor = ശൂന്യ;
    }
}

സ്ഥിതം bool Android_ShowCursor(SDL_Cursor *cursor)
{
    എങ്കിൽ (!cursor) {
        cursor = Android_CreateEmptyCursor();
    }
    എങ്കിൽ (cursor) {
        SDL_CursorData *data = cursor->internal;
        എങ്കിൽ (data->custom_cursor) {
            എങ്കിൽ (!Android_JNI_SetCustomCursor(data->custom_cursor)) {
                തിരികെ SDL_Unsupported();
            }
        } അല്ലെങ്കിൽ {
            എങ്കിൽ (!Android_JNI_SetSystemCursor(data->system_cursor)) {
                തിരികെ SDL_Unsupported();
            }
        }
        തിരികെ true;
    } അല്ലെങ്കിൽ {
        // SDL error set inside Android_CreateEmptyCursor()
        തിരികെ false;
    }
}

സ്ഥിതം bool Android_SetRelativeMouseMode(bool enabled)
{
    എങ്കിൽ (!Android_JNI_SupportsRelativeMouse()) {
        തിരികെ SDL_Unsupported();
    }

    എങ്കിൽ (!Android_JNI_SetRelativeMouseEnabled(enabled)) {
        തിരികെ SDL_Unsupported();
    }

    തിരികെ true;
}

ശൂന്യം Android_InitMouse(ശൂന്യം)
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

ശൂന്യം Android_QuitMouse(ശൂന്യം)
{
    Android_DestroyEmptyCursor();
}

// Translate Android mouse button state to SDL mouse button
സ്ഥിതം Uint8 TranslateButton(പൂർണ്ണസംഖ്യ state)
{
    എങ്കിൽ (state & BUTTON_PRIMARY) {
        തിരികെ SDL_BUTTON_ഇടത്;
    } അല്ലെങ്കിൽ എങ്കിൽ (state & BUTTON_SECONDARY) {
        തിരികെ SDL_BUTTON_വലത്;
    } അല്ലെങ്കിൽ എങ്കിൽ (state & BUTTON_TERTIARY) {
        തിരികെ SDL_BUTTON_നടുവ്;
    } അല്ലെങ്കിൽ എങ്കിൽ (state & BUTTON_FORWARD) {
        തിരികെ SDL_BUTTON_X1;
    } അല്ലെങ്കിൽ എങ്കിൽ (state & BUTTON_BACK) {
        തിരികെ SDL_BUTTON_X2;
    } അല്ലെങ്കിൽ {
        തിരികെ 0;
    }
}

ശൂന്യം Android_OnMouse(SDL_Window *window, പൂർണ്ണസംഖ്യ state, പൂർണ്ണസംഖ്യ action, ദശാംശം x, ദശാംശം y, bool relative)
{
    പൂർണ്ണസംഖ്യ changes_press;
    പൂർണ്ണസംഖ്യ changes_release;
    Uint8 button;

    എങ്കിൽ (!window) {
        തിരികെ;
    }

    തിരഞ്ഞെടുപ്പ് (action) {
    അവസ്ഥ ACTION_MOVE:
    അവസ്ഥ ACTION_HOVER_MOVE:
        SDL_SendMouseMotion(0, window, SDL_DEFAULT_MOUSE_ID, relative, x, y);
        നിർത്തുക;

    അവസ്ഥ ACTION_SCROLL:
        SDL_SendMouseWheel(0, window, SDL_DEFAULT_MOUSE_ID, x, y, SDL_MOUSEWHEEL_NORMAL);
        നിർത്തുക;

    അവസ്ഥ ACTION_UP:
    അവസ്ഥ ACTION_DOWN:
    അവസ്ഥ ACTION_BUTTON_PRESS:
    അവസ്ഥ ACTION_BUTTON_RELEASE:
    അവസ്ഥ ACTION_HOVER_ENTER:
    അവസ്ഥ ACTION_HOVER_EXIT:
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
        എങ്കിൽ (changes_press) {
            വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < വലുപ്പം(k_aAndroidButtons); i++) {
                എങ്കിൽ (changes_press & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, window, SDL_DEFAULT_MOUSE_ID, button, true);
                }
            }
            last_state = state;
        }

        എങ്കിൽ (changes_release) {
            വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i < വലുപ്പം(k_aAndroidButtons); i++) {
                എങ്കിൽ (changes_release & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, window, SDL_DEFAULT_MOUSE_ID, button, false);
                }
            }
            last_state = state;
        }
        നിർത്തുക;        

    സ്ഥിരസ്ഥിതി:
        നിർത്തുക;
    }
}

#endif // SDL_VIDEO_DRIVER_ANDROID

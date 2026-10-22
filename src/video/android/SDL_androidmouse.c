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

#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_ANDROID

#ଅନ୍ତର୍ଭାଵ "SDL_androidmouse.h"

#ଅନ୍ତର୍ଭାଵ "../../events/SDL_mouse_c.h"

#ଅନ୍ତର୍ଭାଵ "../../core/android/SDL_android.h"

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

ସଂରଚନା SDL_CursorData
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା custom_cursor;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା system_cursor;
};

ସ୍ଥିର ଅଚଳ ଅକ୍ଷର k_aAndroidButtons[] = { BUTTON_PRIMARY, BUTTON_SECONDARY, BUTTON_TERTIARY, BUTTON_BACK, BUTTON_FORWARD };

// Last known Android mouse button state (includes all buttons)
ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା last_state;

// Blank cursor
ସ୍ଥିର SDL_Cursor *empty_cursor;

ସ୍ଥିର SDL_Cursor *Android_WrapCursor(ପୂର୍ଣ୍ଣସଂଖ୍ୟା custom_cursor, ପୂର୍ଣ୍ଣସଂଖ୍ୟା system_cursor)
{
    SDL_Cursor *cursor;

    cursor = SDL_calloc(1, ଆକାର(*cursor));
    ଯଦି (cursor) {
        SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, ଆକାର(*data));
        ଯଦି (data) {
            data->custom_cursor = custom_cursor;
            data->system_cursor = system_cursor;
            cursor->internal = data;
        } ଅନ୍ୟଥା {
            SDL_free(cursor);
            cursor = ଖାଲି;
        }
    }

    ଫେରନ୍ତୁ cursor;
}

ସ୍ଥିର SDL_Cursor *Android_CreateDefaultCursor(ଶୂନ୍ୟ)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    ଫେରନ୍ତୁ Android_WrapCursor(0, id);
}

ସ୍ଥିର SDL_Cursor *Android_CreateCursor(SDL_Surface *surface, ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_x, ପୂର୍ଣ୍ଣସଂଖ୍ୟା hot_y)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା custom_cursor;
    SDL_Surface *converted;

    converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
    ଯଦି (!converted) {
        ଫେରନ୍ତୁ ଖାଲି;
    }
    custom_cursor = Android_JNI_CreateCustomCursor(converted, hot_x, hot_y);
    SDL_DestroySurface(converted);
    ଯଦି (!custom_cursor) {
        SDL_Unsupported();
        ଫେରନ୍ତୁ ଖାଲି;
    }
    ଫେରନ୍ତୁ Android_WrapCursor(custom_cursor, 0);
}

ସ୍ଥିର SDL_Cursor *Android_CreateSystemCursor(SDL_SystemCursor id)
{
    ଫେରନ୍ତୁ Android_WrapCursor(0, id);
}

ସ୍ଥିର ଶୂନ୍ୟ Android_FreeCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *data = cursor->internal;
    ଯଦି (data->custom_cursor != 0) {
        Android_JNI_DestroyCustomCursor(data->custom_cursor);
    }
    SDL_free(cursor->internal);
    SDL_free(cursor);
}

ସ୍ଥିର SDL_Cursor *Android_CreateEmptyCursor(ଶୂନ୍ୟ)
{
    ଯଦି (!empty_cursor) {
        SDL_Surface *empty_surface = SDL_CreateSurfaceZeroed(1, 1, SDL_PIXELFORMAT_ARGB8888);
        ଯଦି (empty_surface) {
            empty_cursor = Android_CreateCursor(empty_surface, 0, 0);
            SDL_DestroySurface(empty_surface);
        }
    }
    ଫେରନ୍ତୁ empty_cursor;
}

ସ୍ଥିର ଶୂନ୍ୟ Android_DestroyEmptyCursor(ଶୂନ୍ୟ)
{
    ଯଦି (empty_cursor) {
        Android_FreeCursor(empty_cursor);
        empty_cursor = ଖାଲି;
    }
}

ସ୍ଥିର bool Android_ShowCursor(SDL_Cursor *cursor)
{
    ଯଦି (!cursor) {
        cursor = Android_CreateEmptyCursor();
    }
    ଯଦି (cursor) {
        SDL_CursorData *data = cursor->internal;
        ଯଦି (data->custom_cursor) {
            ଯଦି (!Android_JNI_SetCustomCursor(data->custom_cursor)) {
                ଫେରନ୍ତୁ SDL_Unsupported();
            }
        } ଅନ୍ୟଥା {
            ଯଦି (!Android_JNI_SetSystemCursor(data->system_cursor)) {
                ଫେରନ୍ତୁ SDL_Unsupported();
            }
        }
        ଫେରନ୍ତୁ true;
    } ଅନ୍ୟଥା {
        // SDL error set inside Android_CreateEmptyCursor()
        ଫେରନ୍ତୁ false;
    }
}

ସ୍ଥିର bool Android_SetRelativeMouseMode(bool enabled)
{
    ଯଦି (!Android_JNI_SupportsRelativeMouse()) {
        ଫେରନ୍ତୁ SDL_Unsupported();
    }

    ଯଦି (!Android_JNI_SetRelativeMouseEnabled(enabled)) {
        ଫେରନ୍ତୁ SDL_Unsupported();
    }

    ଫେରନ୍ତୁ true;
}

ଶୂନ୍ୟ Android_InitMouse(ଶୂନ୍ୟ)
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

ଶୂନ୍ୟ Android_QuitMouse(ଶୂନ୍ୟ)
{
    Android_DestroyEmptyCursor();
}

// Translate Android mouse button state to SDL mouse button
ସ୍ଥିର Uint8 TranslateButton(ପୂର୍ଣ୍ଣସଂଖ୍ୟା state)
{
    ଯଦି (state & BUTTON_PRIMARY) {
        ଫେରନ୍ତୁ SDL_BUTTON_ବାମ;
    } ଅନ୍ୟଥା ଯଦି (state & BUTTON_SECONDARY) {
        ଫେରନ୍ତୁ SDL_BUTTON_ଡାହାଣ;
    } ଅନ୍ୟଥା ଯଦି (state & BUTTON_TERTIARY) {
        ଫେରନ୍ତୁ SDL_BUTTON_ମଧ୍ୟ;
    } ଅନ୍ୟଥା ଯଦି (state & BUTTON_FORWARD) {
        ଫେରନ୍ତୁ SDL_BUTTON_X1;
    } ଅନ୍ୟଥା ଯଦି (state & BUTTON_BACK) {
        ଫେରନ୍ତୁ SDL_BUTTON_X2;
    } ଅନ୍ୟଥା {
        ଫେରନ୍ତୁ 0;
    }
}

ଶୂନ୍ୟ Android_OnMouse(SDL_Window *window, ପୂର୍ଣ୍ଣସଂଖ୍ୟା state, ପୂର୍ଣ୍ଣସଂଖ୍ୟା action, ଦଶମିକ x, ଦଶମିକ y, bool relative)
{
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା changes_press;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା changes_release;
    Uint8 button;

    ଯଦି (!window) {
        ଫେରନ୍ତୁ;
    }

    ବାଛ (action) {
    ସ୍ଥିତି ACTION_MOVE:
    ସ୍ଥିତି ACTION_HOVER_MOVE:
        SDL_SendMouseMotion(0, window, SDL_DEFAULT_MOUSE_ID, relative, x, y);
        ଭାଙ୍ଗ;

    ସ୍ଥିତି ACTION_SCROLL:
        SDL_SendMouseWheel(0, window, SDL_DEFAULT_MOUSE_ID, x, y, SDL_MOUSEWHEEL_NORMAL);
        ଭାଙ୍ଗ;

    ସ୍ଥିତି ACTION_UP:
    ସ୍ଥିତି ACTION_DOWN:
    ସ୍ଥିତି ACTION_BUTTON_PRESS:
    ସ୍ଥିତି ACTION_BUTTON_RELEASE:
    ସ୍ଥିତି ACTION_HOVER_ENTER:
    ସ୍ଥିତି ACTION_HOVER_EXIT:
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
        ଯଦି (changes_press) {
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < ଆକାର(k_aAndroidButtons); i++) {
                ଯଦି (changes_press & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, window, SDL_DEFAULT_MOUSE_ID, button, true);
                }
            }
            last_state = state;
        }

        ଯଦି (changes_release) {
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i < ଆକାର(k_aAndroidButtons); i++) {
                ଯଦି (changes_release & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, window, SDL_DEFAULT_MOUSE_ID, button, false);
                }
            }
            last_state = state;
        }
        ଭାଙ୍ଗ;        

    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଭାଙ୍ଗ;
    }
}

#endif // SDL_VIDEO_DRIVER_ANDROID

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

#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_ANDROID

#અન્તર્ભાવ "SDL_androidmouse.h"

#અન્તર્ભાવ "../../events/SDL_mouse_c.h"

#અન્તર્ભાવ "../../core/android/SDL_android.h"

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

સંરચના SDL_CursorData
{
    પૂર્ણાંક custom_cursor;
    પૂર્ણાંક system_cursor;
};

સ્થિર અચલ અક્ષર k_aAndroidButtons[] = { BUTTON_PRIMARY, BUTTON_SECONDARY, BUTTON_TERTIARY, BUTTON_BACK, BUTTON_FORWARD };

// Last known Android mouse button state (includes all buttons)
સ્થિર પૂર્ણાંક last_state;

// Blank cursor
સ્થિર SDL_Cursor *empty_cursor;

સ્થિર SDL_Cursor *Android_WrapCursor(પૂર્ણાંક custom_cursor, પૂર્ણાંક system_cursor)
{
    SDL_Cursor *cursor;

    cursor = SDL_calloc(1, કદ(*cursor));
    જો (cursor) {
        SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, કદ(*data));
        જો (data) {
            data->custom_cursor = custom_cursor;
            data->system_cursor = system_cursor;
            cursor->internal = data;
        } નહીંતર {
            SDL_free(cursor);
            cursor = ખાલી;
        }
    }

    પાછા cursor;
}

સ્થિર SDL_Cursor *Android_CreateDefaultCursor(શૂન્ય)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    પાછા Android_WrapCursor(0, id);
}

સ્થિર SDL_Cursor *Android_CreateCursor(SDL_Surface *surface, પૂર્ણાંક hot_x, પૂર્ણાંક hot_y)
{
    પૂર્ણાંક custom_cursor;
    SDL_Surface *converted;

    converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
    જો (!converted) {
        પાછા ખાલી;
    }
    custom_cursor = Android_JNI_CreateCustomCursor(converted, hot_x, hot_y);
    SDL_DestroySurface(converted);
    જો (!custom_cursor) {
        SDL_Unsupported();
        પાછા ખાલી;
    }
    પાછા Android_WrapCursor(custom_cursor, 0);
}

સ્થિર SDL_Cursor *Android_CreateSystemCursor(SDL_SystemCursor id)
{
    પાછા Android_WrapCursor(0, id);
}

સ્થિર શૂન્ય Android_FreeCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *data = cursor->internal;
    જો (data->custom_cursor != 0) {
        Android_JNI_DestroyCustomCursor(data->custom_cursor);
    }
    SDL_free(cursor->internal);
    SDL_free(cursor);
}

સ્થિર SDL_Cursor *Android_CreateEmptyCursor(શૂન્ય)
{
    જો (!empty_cursor) {
        SDL_Surface *empty_surface = SDL_CreateSurfaceZeroed(1, 1, SDL_PIXELFORMAT_ARGB8888);
        જો (empty_surface) {
            empty_cursor = Android_CreateCursor(empty_surface, 0, 0);
            SDL_DestroySurface(empty_surface);
        }
    }
    પાછા empty_cursor;
}

સ્થિર શૂન્ય Android_DestroyEmptyCursor(શૂન્ય)
{
    જો (empty_cursor) {
        Android_FreeCursor(empty_cursor);
        empty_cursor = ખાલી;
    }
}

સ્થિર bool Android_ShowCursor(SDL_Cursor *cursor)
{
    જો (!cursor) {
        cursor = Android_CreateEmptyCursor();
    }
    જો (cursor) {
        SDL_CursorData *data = cursor->internal;
        જો (data->custom_cursor) {
            જો (!Android_JNI_SetCustomCursor(data->custom_cursor)) {
                પાછા SDL_Unsupported();
            }
        } નહીંતર {
            જો (!Android_JNI_SetSystemCursor(data->system_cursor)) {
                પાછા SDL_Unsupported();
            }
        }
        પાછા true;
    } નહીંતર {
        // SDL error set inside Android_CreateEmptyCursor()
        પાછા false;
    }
}

સ્થિર bool Android_SetRelativeMouseMode(bool enabled)
{
    જો (!Android_JNI_SupportsRelativeMouse()) {
        પાછા SDL_Unsupported();
    }

    જો (!Android_JNI_SetRelativeMouseEnabled(enabled)) {
        પાછા SDL_Unsupported();
    }

    પાછા true;
}

શૂન્ય Android_InitMouse(શૂન્ય)
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

શૂન્ય Android_QuitMouse(શૂન્ય)
{
    Android_DestroyEmptyCursor();
}

// Translate Android mouse button state to SDL mouse button
સ્થિર Uint8 TranslateButton(પૂર્ણાંક state)
{
    જો (state & BUTTON_PRIMARY) {
        પાછા SDL_BUTTON_ડાબું;
    } નહીંતર જો (state & BUTTON_SECONDARY) {
        પાછા SDL_BUTTON_જમણું;
    } નહીંતર જો (state & BUTTON_TERTIARY) {
        પાછા SDL_BUTTON_મધ્ય;
    } નહીંતર જો (state & BUTTON_FORWARD) {
        પાછા SDL_BUTTON_X1;
    } નહીંતર જો (state & BUTTON_BACK) {
        પાછા SDL_BUTTON_X2;
    } નહીંતર {
        પાછા 0;
    }
}

શૂન્ય Android_OnMouse(SDL_Window *window, પૂર્ણાંક state, પૂર્ણાંક action, દશાંશ x, દશાંશ y, bool relative)
{
    પૂર્ણાંક changes_press;
    પૂર્ણાંક changes_release;
    Uint8 button;

    જો (!window) {
        પાછા;
    }

    પસંદગી (action) {
    સ્થિતિ ACTION_MOVE:
    સ્થિતિ ACTION_HOVER_MOVE:
        SDL_SendMouseMotion(0, window, SDL_DEFAULT_MOUSE_ID, relative, x, y);
        તોડો;

    સ્થિતિ ACTION_SCROLL:
        SDL_SendMouseWheel(0, window, SDL_DEFAULT_MOUSE_ID, x, y, SDL_MOUSEWHEEL_NORMAL);
        તોડો;

    સ્થિતિ ACTION_UP:
    સ્થિતિ ACTION_DOWN:
    સ્થિતિ ACTION_BUTTON_PRESS:
    સ્થિતિ ACTION_BUTTON_RELEASE:
    સ્થિતિ ACTION_HOVER_ENTER:
    સ્થિતિ ACTION_HOVER_EXIT:
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
        જો (changes_press) {
            માટે (પૂર્ણાંક i = 0; i < કદ(k_aAndroidButtons); i++) {
                જો (changes_press & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, window, SDL_DEFAULT_MOUSE_ID, button, true);
                }
            }
            last_state = state;
        }

        જો (changes_release) {
            માટે (પૂર્ણાંક i = 0; i < કદ(k_aAndroidButtons); i++) {
                જો (changes_release & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, window, SDL_DEFAULT_MOUSE_ID, button, false);
                }
            }
            last_state = state;
        }
        તોડો;        

    મૂળભૂત:
        તોડો;
    }
}

#endif // SDL_VIDEO_DRIVER_ANDROID

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

#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_ANDROID

#অন্তর্ভাব "SDL_androidmouse.h"

#অন্তর্ভাব "../../events/SDL_mouse_c.h"

#অন্তর্ভাব "../../core/android/SDL_android.h"

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

সংরচনা SDL_CursorData
{
    পূর্ণাঙ্ক custom_cursor;
    পূর্ণাঙ্ক system_cursor;
};

স্থির ধ্রুব বর্ণ k_aAndroidButtons[] = { BUTTON_PRIMARY, BUTTON_SECONDARY, BUTTON_TERTIARY, BUTTON_BACK, BUTTON_FORWARD };

// Last known Android mouse button state (includes all buttons)
স্থির পূর্ণাঙ্ক last_state;

// Blank cursor
স্থির SDL_Cursor *empty_cursor;

স্থির SDL_Cursor *Android_WrapCursor(পূর্ণাঙ্ক custom_cursor, পূর্ণাঙ্ক system_cursor)
{
    SDL_Cursor *cursor;

    cursor = SDL_calloc(1, পরিমাণ(*cursor));
    যদি (cursor) {
        SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, পরিমাণ(*data));
        যদি (data) {
            data->custom_cursor = custom_cursor;
            data->system_cursor = system_cursor;
            cursor->internal = data;
        } অন্যথা {
            SDL_free(cursor);
            cursor = রিক্ত;
        }
    }

    প্রত্যাগম cursor;
}

স্থির SDL_Cursor *Android_CreateDefaultCursor(শূন্য)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    প্রত্যাগম Android_WrapCursor(0, id);
}

স্থির SDL_Cursor *Android_CreateCursor(SDL_Surface *surface, পূর্ণাঙ্ক hot_x, পূর্ণাঙ্ক hot_y)
{
    পূর্ণাঙ্ক custom_cursor;
    SDL_Surface *converted;

    converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
    যদি (!converted) {
        প্রত্যাগম রিক্ত;
    }
    custom_cursor = Android_JNI_CreateCustomCursor(converted, hot_x, hot_y);
    SDL_DestroySurface(converted);
    যদি (!custom_cursor) {
        SDL_Unsupported();
        প্রত্যাগম রিক্ত;
    }
    প্রত্যাগম Android_WrapCursor(custom_cursor, 0);
}

স্থির SDL_Cursor *Android_CreateSystemCursor(SDL_SystemCursor id)
{
    প্রত্যাগম Android_WrapCursor(0, id);
}

স্থির শূন্য Android_FreeCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *data = cursor->internal;
    যদি (data->custom_cursor != 0) {
        Android_JNI_DestroyCustomCursor(data->custom_cursor);
    }
    SDL_free(cursor->internal);
    SDL_free(cursor);
}

স্থির SDL_Cursor *Android_CreateEmptyCursor(শূন্য)
{
    যদি (!empty_cursor) {
        SDL_Surface *empty_surface = SDL_CreateSurfaceZeroed(1, 1, SDL_PIXELFORMAT_ARGB8888);
        যদি (empty_surface) {
            empty_cursor = Android_CreateCursor(empty_surface, 0, 0);
            SDL_DestroySurface(empty_surface);
        }
    }
    প্রত্যাগম empty_cursor;
}

স্থির শূন্য Android_DestroyEmptyCursor(শূন্য)
{
    যদি (empty_cursor) {
        Android_FreeCursor(empty_cursor);
        empty_cursor = রিক্ত;
    }
}

স্থির bool Android_ShowCursor(SDL_Cursor *cursor)
{
    যদি (!cursor) {
        cursor = Android_CreateEmptyCursor();
    }
    যদি (cursor) {
        SDL_CursorData *data = cursor->internal;
        যদি (data->custom_cursor) {
            যদি (!Android_JNI_SetCustomCursor(data->custom_cursor)) {
                প্রত্যাগম SDL_Unsupported();
            }
        } অন্যথা {
            যদি (!Android_JNI_SetSystemCursor(data->system_cursor)) {
                প্রত্যাগম SDL_Unsupported();
            }
        }
        প্রত্যাগম true;
    } অন্যথা {
        // SDL error set inside Android_CreateEmptyCursor()
        প্রত্যাগম false;
    }
}

স্থির bool Android_SetRelativeMouseMode(bool enabled)
{
    যদি (!Android_JNI_SupportsRelativeMouse()) {
        প্রত্যাগম SDL_Unsupported();
    }

    যদি (!Android_JNI_SetRelativeMouseEnabled(enabled)) {
        প্রত্যাগম SDL_Unsupported();
    }

    প্রত্যাগম true;
}

শূন্য Android_InitMouse(শূন্য)
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

শূন্য Android_QuitMouse(শূন্য)
{
    Android_DestroyEmptyCursor();
}

// Translate Android mouse button state to SDL mouse button
স্থির Uint8 TranslateButton(পূর্ণাঙ্ক state)
{
    যদি (state & BUTTON_PRIMARY) {
        প্রত্যাগম SDL_BUTTON_বাম;
    } অন্যথা যদি (state & BUTTON_SECONDARY) {
        প্রত্যাগম SDL_BUTTON_ডান;
    } অন্যথা যদি (state & BUTTON_TERTIARY) {
        প্রত্যাগম SDL_BUTTON_মধ্য;
    } অন্যথা যদি (state & BUTTON_FORWARD) {
        প্রত্যাগম SDL_BUTTON_X1;
    } অন্যথা যদি (state & BUTTON_BACK) {
        প্রত্যাগম SDL_BUTTON_X2;
    } অন্যথা {
        প্রত্যাগম 0;
    }
}

শূন্য Android_OnMouse(SDL_Window *window, পূর্ণাঙ্ক state, পূর্ণাঙ্ক action, ভিন্ন x, ভিন্ন y, bool relative)
{
    পূর্ণাঙ্ক changes_press;
    পূর্ণাঙ্ক changes_release;
    Uint8 button;

    যদি (!window) {
        প্রত্যাগম;
    }

    বিকল্প (action) {
    পক্ষ ACTION_MOVE:
    পক্ষ ACTION_HOVER_MOVE:
        SDL_SendMouseMotion(0, window, SDL_DEFAULT_MOUSE_ID, relative, x, y);
        ভঙ্গ;

    পক্ষ ACTION_SCROLL:
        SDL_SendMouseWheel(0, window, SDL_DEFAULT_MOUSE_ID, x, y, SDL_MOUSEWHEEL_NORMAL);
        ভঙ্গ;

    পক্ষ ACTION_UP:
    পক্ষ ACTION_DOWN:
    পক্ষ ACTION_BUTTON_PRESS:
    পক্ষ ACTION_BUTTON_RELEASE:
    পক্ষ ACTION_HOVER_ENTER:
    পক্ষ ACTION_HOVER_EXIT:
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
        যদি (changes_press) {
            প্রতি (পূর্ণাঙ্ক i = 0; i < পরিমাণ(k_aAndroidButtons); i++) {
                যদি (changes_press & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, window, SDL_DEFAULT_MOUSE_ID, button, true);
                }
            }
            last_state = state;
        }

        যদি (changes_release) {
            প্রতি (পূর্ণাঙ্ক i = 0; i < পরিমাণ(k_aAndroidButtons); i++) {
                যদি (changes_release & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, window, SDL_DEFAULT_MOUSE_ID, button, false);
                }
            }
            last_state = state;
        }
        ভঙ্গ;        

    স্বভাব:
        ভঙ্গ;
    }
}

#endif // SDL_VIDEO_DRIVER_ANDROID

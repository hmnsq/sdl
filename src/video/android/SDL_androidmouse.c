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

#अन्तर्भाव "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_ANDROID

#अन्तर्भाव "SDL_androidmouse.h"

#अन्तर्भाव "../../events/SDL_mouse_c.h"

#अन्तर्भाव "../../core/android/SDL_android.h"

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

संरचना SDL_CursorData
{
    पूर्णाङ्क custom_cursor;
    पूर्णाङ्क system_cursor;
};

स्थिर ध्रुव वर्ण k_aAndroidButtons[] = { BUTTON_PRIMARY, BUTTON_SECONDARY, BUTTON_TERTIARY, BUTTON_BACK, BUTTON_FORWARD };

// Last known Android mouse button state (includes all buttons)
स्थिर पूर्णाङ्क last_state;

// Blank cursor
स्थिर SDL_Cursor *empty_cursor;

स्थिर SDL_Cursor *Android_WrapCursor(पूर्णाङ्क custom_cursor, पूर्णाङ्क system_cursor)
{
    SDL_Cursor *cursor;

    cursor = SDL_calloc(1, परिमाण(*cursor));
    यदि (cursor) {
        SDL_CursorData *data = (SDL_CursorData *)SDL_calloc(1, परिमाण(*data));
        यदि (data) {
            data->custom_cursor = custom_cursor;
            data->system_cursor = system_cursor;
            cursor->internal = data;
        } अन्यथा {
            SDL_free(cursor);
            cursor = रिक्त;
        }
    }

    प्रत्यागम cursor;
}

स्थिर SDL_Cursor *Android_CreateDefaultCursor(शून्य)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    प्रत्यागम Android_WrapCursor(0, id);
}

स्थिर SDL_Cursor *Android_CreateCursor(SDL_Surface *surface, पूर्णाङ्क hot_x, पूर्णाङ्क hot_y)
{
    पूर्णाङ्क custom_cursor;
    SDL_Surface *converted;

    converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
    यदि (!converted) {
        प्रत्यागम रिक्त;
    }
    custom_cursor = Android_JNI_CreateCustomCursor(converted, hot_x, hot_y);
    SDL_DestroySurface(converted);
    यदि (!custom_cursor) {
        SDL_Unsupported();
        प्रत्यागम रिक्त;
    }
    प्रत्यागम Android_WrapCursor(custom_cursor, 0);
}

स्थिर SDL_Cursor *Android_CreateSystemCursor(SDL_SystemCursor id)
{
    प्रत्यागम Android_WrapCursor(0, id);
}

स्थिर शून्य Android_FreeCursor(SDL_Cursor *cursor)
{
    SDL_CursorData *data = cursor->internal;
    यदि (data->custom_cursor != 0) {
        Android_JNI_DestroyCustomCursor(data->custom_cursor);
    }
    SDL_free(cursor->internal);
    SDL_free(cursor);
}

स्थिर SDL_Cursor *Android_CreateEmptyCursor(शून्य)
{
    यदि (!empty_cursor) {
        SDL_Surface *empty_surface = SDL_CreateSurfaceZeroed(1, 1, SDL_PIXELFORMAT_ARGB8888);
        यदि (empty_surface) {
            empty_cursor = Android_CreateCursor(empty_surface, 0, 0);
            SDL_DestroySurface(empty_surface);
        }
    }
    प्रत्यागम empty_cursor;
}

स्थिर शून्य Android_DestroyEmptyCursor(शून्य)
{
    यदि (empty_cursor) {
        Android_FreeCursor(empty_cursor);
        empty_cursor = रिक्त;
    }
}

स्थिर bool Android_ShowCursor(SDL_Cursor *cursor)
{
    यदि (!cursor) {
        cursor = Android_CreateEmptyCursor();
    }
    यदि (cursor) {
        SDL_CursorData *data = cursor->internal;
        यदि (data->custom_cursor) {
            यदि (!Android_JNI_SetCustomCursor(data->custom_cursor)) {
                प्रत्यागम SDL_Unsupported();
            }
        } अन्यथा {
            यदि (!Android_JNI_SetSystemCursor(data->system_cursor)) {
                प्रत्यागम SDL_Unsupported();
            }
        }
        प्रत्यागम true;
    } अन्यथा {
        // SDL error set inside Android_CreateEmptyCursor()
        प्रत्यागम false;
    }
}

स्थिर bool Android_SetRelativeMouseMode(bool enabled)
{
    यदि (!Android_JNI_SupportsRelativeMouse()) {
        प्रत्यागम SDL_Unsupported();
    }

    यदि (!Android_JNI_SetRelativeMouseEnabled(enabled)) {
        प्रत्यागम SDL_Unsupported();
    }

    प्रत्यागम true;
}

शून्य Android_InitMouse(शून्य)
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

शून्य Android_QuitMouse(शून्य)
{
    Android_DestroyEmptyCursor();
}

// Translate Android mouse button state to SDL mouse button
स्थिर Uint8 TranslateButton(पूर्णाङ्क state)
{
    यदि (state & BUTTON_PRIMARY) {
        प्रत्यागम SDL_BUTTON_बायाँ;
    } अन्यथा यदि (state & BUTTON_SECONDARY) {
        प्रत्यागम SDL_BUTTON_दायाँ;
    } अन्यथा यदि (state & BUTTON_TERTIARY) {
        प्रत्यागम SDL_BUTTON_मध्य;
    } अन्यथा यदि (state & BUTTON_FORWARD) {
        प्रत्यागम SDL_BUTTON_X1;
    } अन्यथा यदि (state & BUTTON_BACK) {
        प्रत्यागम SDL_BUTTON_X2;
    } अन्यथा {
        प्रत्यागम 0;
    }
}

शून्य Android_OnMouse(SDL_Window *window, पूर्णाङ्क state, पूर्णाङ्क action, भिन्न x, भिन्न y, bool relative)
{
    पूर्णाङ्क changes_press;
    पूर्णाङ्क changes_release;
    Uint8 button;

    यदि (!window) {
        प्रत्यागम;
    }

    विकल्प (action) {
    पक्ष ACTION_MOVE:
    पक्ष ACTION_HOVER_MOVE:
        SDL_SendMouseMotion(0, window, SDL_DEFAULT_MOUSE_ID, relative, x, y);
        भङ्ग;

    पक्ष ACTION_SCROLL:
        SDL_SendMouseWheel(0, window, SDL_DEFAULT_MOUSE_ID, x, y, SDL_MOUSEWHEEL_NORMAL);
        भङ्ग;

    पक्ष ACTION_UP:
    पक्ष ACTION_DOWN:
    पक्ष ACTION_BUTTON_PRESS:
    पक्ष ACTION_BUTTON_RELEASE:
    पक्ष ACTION_HOVER_ENTER:
    पक्ष ACTION_HOVER_EXIT:
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
        यदि (changes_press) {
            प्रति (पूर्णाङ्क i = 0; i < परिमाण(k_aAndroidButtons); i++) {
                यदि (changes_press & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, window, SDL_DEFAULT_MOUSE_ID, button, true);
                }
            }
            last_state = state;
        }

        यदि (changes_release) {
            प्रति (पूर्णाङ्क i = 0; i < परिमाण(k_aAndroidButtons); i++) {
                यदि (changes_release & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, window, SDL_DEFAULT_MOUSE_ID, button, false);
                }
            }
            last_state = state;
        }
        भङ्ग;        

    स्वभाव:
        भङ्ग;
    }
}

#endif // SDL_VIDEO_DRIVER_ANDROID

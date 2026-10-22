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

#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_ANDROID

#समावेश "SDL_androidmouse.h"

#समावेश "../../events/SDL_mouse_c.h"

#समावेश "../../core/android/SDL_android.h"

// See Android's MotionEvent class for constants
#घोषणा ACTION_DOWN           0
#घोषणा ACTION_UP             1
#घोषणा ACTION_MOVE           2
#घोषणा ACTION_CANCEL         3
#घोषणा ACTION_HOVER_MOVE     7
#घोषणा ACTION_SCROLL         8
#घोषणा ACTION_HOVER_ENTER    9
#घोषणा ACTION_HOVER_EXIT     10
#घोषणा ACTION_BUTTON_PRESS   11
#घोषणा ACTION_BUTTON_RELEASE 12

#घोषणा BUTTON_PRIMARY        1
#घोषणा BUTTON_SECONDARY      2
#घोषणा BUTTON_TERTIARY       4
#घोषणा BUTTON_BACK           8
#घोषणा BUTTON_FORWARD        16

काष्ठा SDL_Cursor_तथ्य
{
    पूर्णांक custom_cursor;
    पूर्णांक system_cursor;
};

अटल स्थिर अक्षर k_aAndroidButtons[] = { BUTTON_PRIMARY, BUTTON_SECONDARY, BUTTON_TERTIARY, BUTTON_BACK, BUTTON_FORWARD };

// Last known Android mouse button state (includes all buttons)
अटल पूर्णांक last_state;

// Blank cursor
अटल SDL_Cursor *empty_cursor;

अटल SDL_Cursor *Android_WrapCursor(पूर्णांक custom_cursor, पूर्णांक system_cursor)
{
    SDL_Cursor *cursor;

    cursor = SDL_calloc(1, माप(*cursor));
    अगर (cursor) {
        SDL_Cursor_तथ्य *तथ्य = (SDL_Cursor_तथ्य *)SDL_calloc(1, माप(*तथ्य));
        अगर (तथ्य) {
            तथ्य->custom_cursor = custom_cursor;
            तथ्य->system_cursor = system_cursor;
            cursor->internal = तथ्य;
        } अन्यथा {
            SDL_free(cursor);
            cursor = शून्य;
        }
    }

    वापस cursor;
}

अटल SDL_Cursor *Android_CreateDefaultCursor(व्योम)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    वापस Android_WrapCursor(0, id);
}

अटल SDL_Cursor *Android_CreateCursor(SDL_Surface *surface, पूर्णांक hot_x, पूर्णांक hot_y)
{
    पूर्णांक custom_cursor;
    SDL_Surface *converted;

    converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
    अगर (!converted) {
        वापस शून्य;
    }
    custom_cursor = Android_JNI_CreateCustomCursor(converted, hot_x, hot_y);
    SDL_DestroySurface(converted);
    अगर (!custom_cursor) {
        SDL_Unsupported();
        वापस शून्य;
    }
    वापस Android_WrapCursor(custom_cursor, 0);
}

अटल SDL_Cursor *Android_CreateSystemCursor(SDL_SystemCursor id)
{
    वापस Android_WrapCursor(0, id);
}

अटल व्योम Android_FreeCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_तथ्य *तथ्य = cursor->internal;
    अगर (तथ्य->custom_cursor != 0) {
        Android_JNI_DestroyCustomCursor(तथ्य->custom_cursor);
    }
    SDL_free(cursor->internal);
    SDL_free(cursor);
}

अटल SDL_Cursor *Android_CreateEmptyCursor(व्योम)
{
    अगर (!empty_cursor) {
        SDL_Surface *empty_surface = SDL_CreateSurfaceZeroed(1, 1, SDL_PIXELFORMAT_ARGB8888);
        अगर (empty_surface) {
            empty_cursor = Android_CreateCursor(empty_surface, 0, 0);
            SDL_DestroySurface(empty_surface);
        }
    }
    वापस empty_cursor;
}

अटल व्योम Android_DestroyEmptyCursor(व्योम)
{
    अगर (empty_cursor) {
        Android_FreeCursor(empty_cursor);
        empty_cursor = शून्य;
    }
}

अटल bool Android_ShowCursor(SDL_Cursor *cursor)
{
    अगर (!cursor) {
        cursor = Android_CreateEmptyCursor();
    }
    अगर (cursor) {
        SDL_Cursor_तथ्य *तथ्य = cursor->internal;
        अगर (तथ्य->custom_cursor) {
            अगर (!Android_JNI_SetCustomCursor(तथ्य->custom_cursor)) {
                वापस SDL_Unsupported();
            }
        } अन्यथा {
            अगर (!Android_JNI_SetSystemCursor(तथ्य->system_cursor)) {
                वापस SDL_Unsupported();
            }
        }
        वापस true;
    } अन्यथा {
        // SDL error set inside Android_CreateEmptyCursor()
        वापस false;
    }
}

अटल bool Android_SetRelativeMouseMode(bool enabled)
{
    अगर (!Android_JNI_SupportsRelativeMouse()) {
        वापस SDL_Unsupported();
    }

    अगर (!Android_JNI_SetRelativeMouseEnabled(enabled)) {
        वापस SDL_Unsupported();
    }

    वापस true;
}

व्योम Android_InitMouse(व्योम)
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

व्योम Android_QuitMouse(व्योम)
{
    Android_DestroyEmptyCursor();
}

// Translate Android mouse button state to SDL mouse button
अटल Uint8 TranslateButton(पूर्णांक state)
{
    अगर (state & BUTTON_PRIMARY) {
        वापस SDL_BUTTON_बायाँ;
    } अन्यथा अगर (state & BUTTON_SECONDARY) {
        वापस SDL_BUTTON_दायाँ;
    } अन्यथा अगर (state & BUTTON_TERTIARY) {
        वापस SDL_BUTTON_मध्य;
    } अन्यथा अगर (state & BUTTON_FORWARD) {
        वापस SDL_BUTTON_X1;
    } अन्यथा अगर (state & BUTTON_BACK) {
        वापस SDL_BUTTON_X2;
    } अन्यथा {
        वापस 0;
    }
}

व्योम Android_OnMouse(SDL_Window *window, पूर्णांक state, पूर्णांक action, भग्न x, भग्न y, bool relative)
{
    पूर्णांक changes_press;
    पूर्णांक changes_release;
    Uint8 button;

    अगर (!window) {
        वापस;
    }

    चयन (action) {
    हाल ACTION_MOVE:
    हाल ACTION_HOVER_MOVE:
        SDL_SendMouseMotion(0, window, SDL_DEFAULT_MOUSE_ID, relative, x, y);
        अवरोध;

    हाल ACTION_SCROLL:
        SDL_SendMouseWheel(0, window, SDL_DEFAULT_MOUSE_ID, x, y, SDL_MOUSEWHEEL_NORMAL);
        अवरोध;

    हाल ACTION_UP:
    हाल ACTION_DOWN:
    हाल ACTION_BUTTON_PRESS:
    हाल ACTION_BUTTON_RELEASE:
    हाल ACTION_HOVER_ENTER:
    हाल ACTION_HOVER_EXIT:
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
        अगर (changes_press) {
            क्रम (पूर्णांक i = 0; i < माप(k_aAndroidButtons); i++) {
                अगर (changes_press & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, window, SDL_DEFAULT_MOUSE_ID, button, true);
                }
            }
            last_state = state;
        }

        अगर (changes_release) {
            क्रम (पूर्णांक i = 0; i < माप(k_aAndroidButtons); i++) {
                अगर (changes_release & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, window, SDL_DEFAULT_MOUSE_ID, button, false);
                }
            }
            last_state = state;
        }
        अवरोध;        

    शेष:
        अवरोध;
    }
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_ANDROID

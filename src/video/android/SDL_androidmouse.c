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

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_ANDROID

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_androidmouse.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_mouse_c.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/android/SDL_android.h"

// See Android's MotionEvent class for constants
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ACTION_ਥੱਲੇ           0
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ACTION_ਉੱਪਰ             1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ACTION_MOVE           2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ACTION_CANCEL         3
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ACTION_HOVER_MOVE     7
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ACTION_SCROLL         8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ACTION_HOVER_ENTER    9
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ACTION_HOVER_EXIT     10
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ACTION_BUTTON_PRESS   11
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ACTION_BUTTON_RELEASE 12

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BUTTON_PRIMARY        1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BUTTON_SECONDARY      2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BUTTON_TERTIARY       4
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BUTTON_ਪਿੱਠ           8
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ BUTTON_FORWARD        16

ਬਣਤਰ SDL_Cursor_ਅੰਕੜੇ
{
    ਪੂਰਨ custom_cursor;
    ਪੂਰਨ system_cursor;
};

ਸਥਿਰ ਅਚਲ ਅੱਖਰ k_aAndroidButtons[] = { BUTTON_PRIMARY, BUTTON_SECONDARY, BUTTON_TERTIARY, BUTTON_ਪਿੱਠ, BUTTON_FORWARD };

// Last known Android mouse button state (includes all buttons)
ਸਥਿਰ ਪੂਰਨ ਆਖਰੀ_state;

// Blank cursor
ਸਥਿਰ SDL_Cursor *ਖਾਲੀ_ਥਾਵਾਂ_cursor;

ਸਥਿਰ SDL_Cursor *Android_WrapCursor(ਪੂਰਨ custom_cursor, ਪੂਰਨ system_cursor)
{
    SDL_Cursor *cursor;

    cursor = SDL_calloc(1, ਆਕਾਰ(*cursor));
    ਜੇ (cursor) {
        SDL_Cursor_ਅੰਕੜੇ *ਅੰਕੜੇ = (SDL_Cursor_ਅੰਕੜੇ *)SDL_calloc(1, ਆਕਾਰ(*ਅੰਕੜੇ));
        ਜੇ (ਅੰਕੜੇ) {
            ਅੰਕੜੇ->custom_cursor = custom_cursor;
            ਅੰਕੜੇ->system_cursor = system_cursor;
            cursor->ਅੰਦਰੂਨੀ = ਅੰਕੜੇ;
        } ਨਹੀਂਤਾਂ {
            SDL_free(cursor);
            cursor = ਨਿਰਾ;
        }
    }

    ਵਾਪਸ cursor;
}

ਸਥਿਰ SDL_Cursor *Android_CreateDefaultCursor(ਖਾਲੀ)
{
    SDL_SystemCursor id = SDL_GetDefaultSystemCursor();
    ਵਾਪਸ Android_WrapCursor(0, id);
}

ਸਥਿਰ SDL_Cursor *Android_CreateCursor(SDL_Surface *surface, ਪੂਰਨ hot_x, ਪੂਰਨ hot_y)
{
    ਪੂਰਨ custom_cursor;
    SDL_Surface *converted;

    converted = SDL_ConvertSurface(surface, SDL_PIXELFORMAT_ARGB8888);
    ਜੇ (!converted) {
        ਵਾਪਸ ਨਿਰਾ;
    }
    custom_cursor = Android_JNI_CreateCustomCursor(converted, hot_x, hot_y);
    SDL_DestroySurface(converted);
    ਜੇ (!custom_cursor) {
        SDL_Unsupported();
        ਵਾਪਸ ਨਿਰਾ;
    }
    ਵਾਪਸ Android_WrapCursor(custom_cursor, 0);
}

ਸਥਿਰ SDL_Cursor *Android_CreateSystemCursor(SDL_SystemCursor id)
{
    ਵਾਪਸ Android_WrapCursor(0, id);
}

ਸਥਿਰ ਖਾਲੀ Android_FreeCursor(SDL_Cursor *cursor)
{
    SDL_Cursor_ਅੰਕੜੇ *ਅੰਕੜੇ = cursor->ਅੰਦਰੂਨੀ;
    ਜੇ (ਅੰਕੜੇ->custom_cursor != 0) {
        Android_JNI_DestroyCustomCursor(ਅੰਕੜੇ->custom_cursor);
    }
    SDL_free(cursor->ਅੰਦਰੂਨੀ);
    SDL_free(cursor);
}

ਸਥਿਰ SDL_Cursor *Android_Create_ਖਾਲੀ_ਥਾਵਾਂ_Cursor(ਖਾਲੀ)
{
    ਜੇ (!ਖਾਲੀ_ਥਾਵਾਂ_cursor) {
        SDL_Surface *ਖਾਲੀ_ਥਾਵਾਂ_surface = SDL_CreateSurfaceZeroed(1, 1, SDL_PIXELFORMAT_ARGB8888);
        ਜੇ (ਖਾਲੀ_ਥਾਵਾਂ_surface) {
            ਖਾਲੀ_ਥਾਵਾਂ_cursor = Android_CreateCursor(ਖਾਲੀ_ਥਾਵਾਂ_surface, 0, 0);
            SDL_DestroySurface(ਖਾਲੀ_ਥਾਵਾਂ_surface);
        }
    }
    ਵਾਪਸ ਖਾਲੀ_ਥਾਵਾਂ_cursor;
}

ਸਥਿਰ ਖਾਲੀ Android_Destroy_ਖਾਲੀ_ਥਾਵਾਂ_Cursor(ਖਾਲੀ)
{
    ਜੇ (ਖਾਲੀ_ਥਾਵਾਂ_cursor) {
        Android_FreeCursor(ਖਾਲੀ_ਥਾਵਾਂ_cursor);
        ਖਾਲੀ_ਥਾਵਾਂ_cursor = ਨਿਰਾ;
    }
}

ਸਥਿਰ bool Android_ShowCursor(SDL_Cursor *cursor)
{
    ਜੇ (!cursor) {
        cursor = Android_Create_ਖਾਲੀ_ਥਾਵਾਂ_Cursor();
    }
    ਜੇ (cursor) {
        SDL_Cursor_ਅੰਕੜੇ *ਅੰਕੜੇ = cursor->ਅੰਦਰੂਨੀ;
        ਜੇ (ਅੰਕੜੇ->custom_cursor) {
            ਜੇ (!Android_JNI_ਸੈੱਟ_Custom_Cursor(ਅੰਕੜੇ->custom_cursor)) {
                ਵਾਪਸ SDL_Unsupported();
            }
        } ਨਹੀਂਤਾਂ {
            ਜੇ (!Android_JNI_ਸੈੱਟ_System_Cursor(ਅੰਕੜੇ->system_cursor)) {
                ਵਾਪਸ SDL_Unsupported();
            }
        }
        ਵਾਪਸ true;
    } ਨਹੀਂਤਾਂ {
        // SDL error set inside Android_CreateEmptyCursor()
        ਵਾਪਸ false;
    }
}

ਸਥਿਰ bool Android_ਸੈੱਟ_Relative_Mouse_ਬਹੁਲਕ(bool enabled)
{
    ਜੇ (!Android_JNI_SupportsRelativeMouse()) {
        ਵਾਪਸ SDL_Unsupported();
    }

    ਜੇ (!Android_JNI_ਸੈੱਟ_Relative_Mouse_Enabled(enabled)) {
        ਵਾਪਸ SDL_Unsupported();
    }

    ਵਾਪਸ true;
}

ਖਾਲੀ Android_InitMouse(ਖਾਲੀ)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    mouse->CreateCursor = Android_CreateCursor;
    mouse->CreateSystemCursor = Android_CreateSystemCursor;
    mouse->ShowCursor = Android_ShowCursor;
    mouse->FreeCursor = Android_FreeCursor;
    mouse->ਸੈੱਟ_Relative_Mouse_ਬਹੁਲਕ = Android_ਸੈੱਟ_Relative_Mouse_ਬਹੁਲਕ;

    SDL_ਸੈੱਟ_Default_Cursor(Android_CreateDefaultCursor());

    ਆਖਰੀ_state = 0;
}

ਖਾਲੀ Android_QuitMouse(ਖਾਲੀ)
{
    Android_Destroy_ਖਾਲੀ_ਥਾਵਾਂ_Cursor();
}

// Translate Android mouse button state to SDL mouse button
ਸਥਿਰ Uint8 TranslateButton(ਪੂਰਨ state)
{
    ਜੇ (state & BUTTON_PRIMARY) {
        ਵਾਪਸ SDL_BUTTON_ਖੱਬਾ;
    } ਨਹੀਂਤਾਂ ਜੇ (state & BUTTON_SECONDARY) {
        ਵਾਪਸ SDL_BUTTON_ਸੱਜਾ;
    } ਨਹੀਂਤਾਂ ਜੇ (state & BUTTON_TERTIARY) {
        ਵਾਪਸ SDL_BUTTON_ਵਿਚਕਾਰ;
    } ਨਹੀਂਤਾਂ ਜੇ (state & BUTTON_FORWARD) {
        ਵਾਪਸ SDL_BUTTON_X1;
    } ਨਹੀਂਤਾਂ ਜੇ (state & BUTTON_ਪਿੱਠ) {
        ਵਾਪਸ SDL_BUTTON_X2;
    } ਨਹੀਂਤਾਂ {
        ਵਾਪਸ 0;
    }
}

ਖਾਲੀ Android_OnMouse(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, ਪੂਰਨ state, ਪੂਰਨ action, ਦਸ਼ਮਲਵ x, ਦਸ਼ਮਲਵ y, bool relative)
{
    ਪੂਰਨ changes_press;
    ਪੂਰਨ changes_release;
    Uint8 button;

    ਜੇ (!ਖਿੜਕੀ) {
        ਵਾਪਸ;
    }

    ਚੋਣ (action) {
    ਹਾਲਤ ACTION_MOVE:
    ਹਾਲਤ ACTION_HOVER_MOVE:
        SDL_SendMouseMotion(0, ਖਿੜਕੀ, SDL_DEFAULT_MOUSE_ID, relative, x, y);
        ਰੋਕੋ;

    ਹਾਲਤ ACTION_SCROLL:
        SDL_SendMouseWheel(0, ਖਿੜਕੀ, SDL_DEFAULT_MOUSE_ID, x, y, SDL_MOUSEWHEEL_ਸਾਧਾਰਨ);
        ਰੋਕੋ;

    ਹਾਲਤ ACTION_ਉੱਪਰ:
    ਹਾਲਤ ACTION_ਥੱਲੇ:
    ਹਾਲਤ ACTION_BUTTON_PRESS:
    ਹਾਲਤ ACTION_BUTTON_RELEASE:
    ਹਾਲਤ ACTION_HOVER_ENTER:
    ਹਾਲਤ ACTION_HOVER_EXIT:
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

        changes_press = state & ~ਆਖਰੀ_state;
        changes_release = ਆਖਰੀ_state & ~state;

        SDL_SendMouseMotion(0, ਖਿੜਕੀ, SDL_DEFAULT_MOUSE_ID, relative, x, y);

        // Some versions of Android will send multiple mouse buttons in a single
        // event, so read it bit-by-bit.
        ਜੇ (changes_press) {
            ਲਈ (ਪੂਰਨ i = 0; i < ਆਕਾਰ(k_aAndroidButtons); i++) {
                ਜੇ (changes_press & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, ਖਿੜਕੀ, SDL_DEFAULT_MOUSE_ID, button, true);
                }
            }
            ਆਖਰੀ_state = state;
        }

        ਜੇ (changes_release) {
            ਲਈ (ਪੂਰਨ i = 0; i < ਆਕਾਰ(k_aAndroidButtons); i++) {
                ਜੇ (changes_release & k_aAndroidButtons[i]) {
                    button = TranslateButton(k_aAndroidButtons[i]);
                    SDL_SendMouseButton(0, ਖਿੜਕੀ, SDL_DEFAULT_MOUSE_ID, button, false);
                }
            }
            ਆਖਰੀ_state = state;
        }
        ਰੋਕੋ;        

    ਮੂਲ:
        ਰੋਕੋ;
    }
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_ANDROID

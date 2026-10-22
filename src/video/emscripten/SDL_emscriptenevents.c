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

#अगर_घोषित SDL_VIDEO_DRIVER_EMSCRIPTEN

#समावेश <emscripten/html5.h>
#समावेश <emscripten/dom_pk_codes.h>

#समावेश "../../events/SDL_dropevents_c.h"
#समावेश "../../events/SDL_events_c.h"
#समावेश "../../events/SDL_keyboard_c.h"
#समावेश "../../events/SDL_touch_c.h"

#समावेश "SDL_emscriptenevents.h"
#समावेश "SDL_emscriptenvideo.h"

/*
Emscripten PK code to scancode
https://developer.mozilla.org/en-US/docs/Web/API/KeyboardEvent
https://developer.mozilla.org/en-US/docs/Web/API/KeyboardEvent/code
*/
अटल स्थिर SDL_Scancode emscripten_scancode_table[] = {
    /* 0x00 "Unidentified"   */ SDL_SCANCODE_UNKNOWN,
    /* 0x01 "Escape"         */ SDL_SCANCODE_ESCAPE,
    /* 0x02 "Digit0"         */ SDL_SCANCODE_0,
    /* 0x03 "Digit1"         */ SDL_SCANCODE_1,
    /* 0x04 "Digit2"         */ SDL_SCANCODE_2,
    /* 0x05 "Digit3"         */ SDL_SCANCODE_3,
    /* 0x06 "Digit4"         */ SDL_SCANCODE_4,
    /* 0x07 "Digit5"         */ SDL_SCANCODE_5,
    /* 0x08 "Digit6"         */ SDL_SCANCODE_6,
    /* 0x09 "Digit7"         */ SDL_SCANCODE_7,
    /* 0x0A "Digit8"         */ SDL_SCANCODE_8,
    /* 0x0B "Digit9"         */ SDL_SCANCODE_9,
    /* 0x0C "Minus"          */ SDL_SCANCODE_MINUS,
    /* 0x0D "Equal"          */ SDL_SCANCODE_EQUALS,
    /* 0x0E "Backspace"      */ SDL_SCANCODE_BACKSPACE,
    /* 0x0F "Tab"            */ SDL_SCANCODE_TAB,
    /* 0x10 "KeyQ"           */ SDL_SCANCODE_Q,
    /* 0x11 "KeyW"           */ SDL_SCANCODE_W,
    /* 0x12 "KeyE"           */ SDL_SCANCODE_E,
    /* 0x13 "KeyR"           */ SDL_SCANCODE_R,
    /* 0x14 "KeyT"           */ SDL_SCANCODE_T,
    /* 0x15 "KeyY"           */ SDL_SCANCODE_Y,
    /* 0x16 "KeyU"           */ SDL_SCANCODE_U,
    /* 0x17 "KeyI"           */ SDL_SCANCODE_I,
    /* 0x18 "KeyO"           */ SDL_SCANCODE_O,
    /* 0x19 "KeyP"           */ SDL_SCANCODE_P,
    /* 0x1A "BracketLeft"    */ SDL_SCANCODE_LEFTBRACKET,
    /* 0x1B "BracketRight"   */ SDL_SCANCODE_RIGHTBRACKET,
    /* 0x1C "Enter"          */ SDL_SCANCODE_RETURN,
    /* 0x1D "ControlLeft"    */ SDL_SCANCODE_LCTRL,
    /* 0x1E "KeyA"           */ SDL_SCANCODE_A,
    /* 0x1F "KeyS"           */ SDL_SCANCODE_S,
    /* 0x20 "KeyD"           */ SDL_SCANCODE_D,
    /* 0x21 "KeyF"           */ SDL_SCANCODE_F,
    /* 0x22 "KeyG"           */ SDL_SCANCODE_G,
    /* 0x23 "KeyH"           */ SDL_SCANCODE_H,
    /* 0x24 "KeyJ"           */ SDL_SCANCODE_J,
    /* 0x25 "KeyK"           */ SDL_SCANCODE_K,
    /* 0x26 "KeyL"           */ SDL_SCANCODE_L,
    /* 0x27 "Semicolon"      */ SDL_SCANCODE_SEMICOLON,
    /* 0x28 "Quote"          */ SDL_SCANCODE_APOSTROPHE,
    /* 0x29 "Backquote"      */ SDL_SCANCODE_GRAVE,
    /* 0x2A "ShiftLeft"      */ SDL_SCANCODE_LSHIFT,
    /* 0x2B "Backslash"      */ SDL_SCANCODE_BACKSLASH,
    /* 0x2C "KeyZ"           */ SDL_SCANCODE_Z,
    /* 0x2D "KeyX"           */ SDL_SCANCODE_X,
    /* 0x2E "KeyC"           */ SDL_SCANCODE_C,
    /* 0x2F "KeyV"           */ SDL_SCANCODE_V,
    /* 0x30 "KeyB"           */ SDL_SCANCODE_B,
    /* 0x31 "KeyN"           */ SDL_SCANCODE_N,
    /* 0x32 "KeyM"           */ SDL_SCANCODE_M,
    /* 0x33 "Comma"          */ SDL_SCANCODE_COMMA,
    /* 0x34 "Period"         */ SDL_SCANCODE_PERIOD,
    /* 0x35 "Slash"          */ SDL_SCANCODE_SLASH,
    /* 0x36 "ShiftRight"     */ SDL_SCANCODE_RSHIFT,
    /* 0x37 "NumpadMultiply" */ SDL_SCANCODE_KP_MULTIPLY,
    /* 0x38 "AltLeft"        */ SDL_SCANCODE_LALT,
    /* 0x39 "Space"          */ SDL_SCANCODE_SPACE,
    /* 0x3A "CapsLock"       */ SDL_SCANCODE_CAPSLOCK,
    /* 0x3B "F1"             */ SDL_SCANCODE_F1,
    /* 0x3C "F2"             */ SDL_SCANCODE_F2,
    /* 0x3D "F3"             */ SDL_SCANCODE_F3,
    /* 0x3E "F4"             */ SDL_SCANCODE_F4,
    /* 0x3F "F5"             */ SDL_SCANCODE_F5,
    /* 0x40 "F6"             */ SDL_SCANCODE_F6,
    /* 0x41 "F7"             */ SDL_SCANCODE_F7,
    /* 0x42 "F8"             */ SDL_SCANCODE_F8,
    /* 0x43 "F9"             */ SDL_SCANCODE_F9,
    /* 0x44 "F10"            */ SDL_SCANCODE_F10,
    /* 0x45 "Pause"          */ SDL_SCANCODE_PAUSE,
    /* 0x46 "ScrollLock"     */ SDL_SCANCODE_SCROLLLOCK,
    /* 0x47 "Numpad7"        */ SDL_SCANCODE_KP_7,
    /* 0x48 "Numpad8"        */ SDL_SCANCODE_KP_8,
    /* 0x49 "Numpad9"        */ SDL_SCANCODE_KP_9,
    /* 0x4A "NumpadSubtract" */ SDL_SCANCODE_KP_MINUS,
    /* 0x4B "Numpad4"        */ SDL_SCANCODE_KP_4,
    /* 0x4C "Numpad5"        */ SDL_SCANCODE_KP_5,
    /* 0x4D "Numpad6"        */ SDL_SCANCODE_KP_6,
    /* 0x4E "NumpadAdd"      */ SDL_SCANCODE_KP_PLUS,
    /* 0x4F "Numpad1"        */ SDL_SCANCODE_KP_1,
    /* 0x50 "Numpad2"        */ SDL_SCANCODE_KP_2,
    /* 0x51 "Numpad3"        */ SDL_SCANCODE_KP_3,
    /* 0x52 "Numpad0"        */ SDL_SCANCODE_KP_0,
    /* 0x53 "NumpadDecimal"  */ SDL_SCANCODE_KP_PERIOD,
    /* 0x54 "PrintScreen"    */ SDL_SCANCODE_PRINTSCREEN,
    /* 0x55                  */ SDL_SCANCODE_UNKNOWN,
    /* 0x56 "IntlBackslash"  */ SDL_SCANCODE_NONUSBACKSLASH,
    /* 0x57 "F11"            */ SDL_SCANCODE_F11,
    /* 0x58 "F12"            */ SDL_SCANCODE_F12,
    /* 0x59 "NumpadEqual"    */ SDL_SCANCODE_KP_EQUALS,
    /* 0x5A                  */ SDL_SCANCODE_UNKNOWN,
    /* 0x5B                  */ SDL_SCANCODE_UNKNOWN,
    /* 0x5C                  */ SDL_SCANCODE_UNKNOWN,
    /* 0x5D                  */ SDL_SCANCODE_UNKNOWN,
    /* 0x5E                  */ SDL_SCANCODE_UNKNOWN,
    /* 0x5F                  */ SDL_SCANCODE_UNKNOWN,
    /* 0x60                  */ SDL_SCANCODE_UNKNOWN,
    /* 0x61                  */ SDL_SCANCODE_UNKNOWN,
    /* 0x62                  */ SDL_SCANCODE_UNKNOWN,
    /* 0x63                  */ SDL_SCANCODE_UNKNOWN,
    /* 0x64 "F13"            */ SDL_SCANCODE_F13,
    /* 0x65 "F14"            */ SDL_SCANCODE_F14,
    /* 0x66 "F15"            */ SDL_SCANCODE_F15,
    /* 0x67 "F16"            */ SDL_SCANCODE_F16,
    /* 0x68 "F17"            */ SDL_SCANCODE_F17,
    /* 0x69 "F18"            */ SDL_SCANCODE_F18,
    /* 0x6A "F19"            */ SDL_SCANCODE_F19,
    /* 0x6B "F20"            */ SDL_SCANCODE_F20,
    /* 0x6C "F21"            */ SDL_SCANCODE_F21,
    /* 0x6D "F22"            */ SDL_SCANCODE_F22,
    /* 0x6E "F23"            */ SDL_SCANCODE_F23,
    /* 0x6F                  */ SDL_SCANCODE_UNKNOWN,
    /* 0x70 "KanaMode"       */ SDL_SCANCODE_INTERNATIONAL2,
    /* 0x71 "Lang2"          */ SDL_SCANCODE_LANG2,
    /* 0x72 "Lang1"          */ SDL_SCANCODE_LANG1,
    /* 0x73 "IntlRo"         */ SDL_SCANCODE_INTERNATIONAL1,
    /* 0x74                  */ SDL_SCANCODE_UNKNOWN,
    /* 0x75                  */ SDL_SCANCODE_UNKNOWN,
    /* 0x76 "F24"            */ SDL_SCANCODE_F24,
    /* 0x77                  */ SDL_SCANCODE_UNKNOWN,
    /* 0x78                  */ SDL_SCANCODE_UNKNOWN,
    /* 0x79 "Convert"        */ SDL_SCANCODE_INTERNATIONAL4,
    /* 0x7A                  */ SDL_SCANCODE_UNKNOWN,
    /* 0x7B "NonConvert"     */ SDL_SCANCODE_INTERNATIONAL5,
    /* 0x7C                  */ SDL_SCANCODE_UNKNOWN,
    /* 0x7D "IntlYen"        */ SDL_SCANCODE_INTERNATIONAL3,
    /* 0x7E "NumpadComma"    */ SDL_SCANCODE_KP_COMMA
};

अटल SDL_Scancode Emscripten_MapScanCode(स्थिर अक्षर *code)
{
    स्थिर DOM_PK_CODE_TYPE pk_code = emscripten_compute_dom_pk_code(code);
    अगर (pk_code < SDL_arraysize(emscripten_scancode_table)) {
        वापस emscripten_scancode_table[pk_code];
    }

    चयन (pk_code) {
    हाल DOM_PK_PASTE:
        वापस SDL_SCANCODE_PASTE;
    हाल DOM_PK_MEDIA_TRACK_PREVIOUS:
        वापस SDL_SCANCODE_MEDIA_PREVIOUS_TRACK;
    हाल DOM_PK_CUT:
        वापस SDL_SCANCODE_CUT;
    हाल DOM_PK_COPY:
        वापस SDL_SCANCODE_COPY;
    हाल DOM_PK_MEDIA_TRACK_अग्र:
        वापस SDL_SCANCODE_MEDIA_अग्र_TRACK;
    हाल DOM_PK_NUMPAD_ENTER:
        वापस SDL_SCANCODE_KP_ENTER;
    हाल DOM_PK_CONTROL_दायाँ:
        वापस SDL_SCANCODE_RCTRL;
    हाल DOM_PK_AUDIO_VOLUME_MUTE:
        वापस SDL_SCANCODE_MUTE;
    हाल DOM_PK_MEDIA_PLAY_PAUSE:
        वापस SDL_SCANCODE_MEDIA_PLAY_PAUSE;
    हाल DOM_PK_MEDIA_STOP:
        वापस SDL_SCANCODE_MEDIA_STOP;
    हाल DOM_PK_EJECT:
        वापस SDL_SCANCODE_MEDIA_EJECT;
    हाल DOM_PK_AUDIO_VOLUME_DOWN:
        वापस SDL_SCANCODE_VOLUMEDOWN;
    हाल DOM_PK_AUDIO_VOLUME_UP:
        वापस SDL_SCANCODE_VOLUMEUP;
    हाल DOM_PK_BROWSER_HOME:
        वापस SDL_SCANCODE_AC_HOME;
    हाल DOM_PK_NUMPAD_DIVIDE:
        वापस SDL_SCANCODE_KP_DIVIDE;
    हाल DOM_PK_ALT_दायाँ:
        वापस SDL_SCANCODE_RALT;
    हाल DOM_PK_HELP:
        वापस SDL_SCANCODE_HELP;
    हाल DOM_PK_अंक_LOCK:
        वापस SDL_SCANCODE_NUMLOCKCLEAR;
    हाल DOM_PK_HOME:
        वापस SDL_SCANCODE_HOME;
    हाल DOM_PK_ARROW_UP:
        वापस SDL_SCANCODE_UP;
    हाल DOM_PK_PAGE_UP:
        वापस SDL_SCANCODE_PAGEUP;
    हाल DOM_PK_ARROW_बायाँ:
        वापस SDL_SCANCODE_बायाँ;
    हाल DOM_PK_ARROW_दायाँ:
        वापस SDL_SCANCODE_दायाँ;
    हाल DOM_PK_END:
        वापस SDL_SCANCODE_END;
    हाल DOM_PK_ARROW_DOWN:
        वापस SDL_SCANCODE_DOWN;
    हाल DOM_PK_PAGE_DOWN:
        वापस SDL_SCANCODE_PAGEDOWN;
    हाल DOM_PK_जोड़ो:
        वापस SDL_SCANCODE_जोड़ो;
    हाल DOM_PK_DELETE:
        वापस SDL_SCANCODE_DELETE;
    हाल DOM_PK_META_बायाँ:
        वापस SDL_SCANCODE_LGUI;
    हाल DOM_PK_META_दायाँ:
        वापस SDL_SCANCODE_RGUI;
    हाल DOM_PK_CONTEXT_MENU:
        वापस SDL_SCANCODE_APPLICATION;
    हाल DOM_PK_POWER:
        वापस SDL_SCANCODE_POWER;
    हाल DOM_PK_BROWSER_खोज:
        वापस SDL_SCANCODE_AC_खोज;
    हाल DOM_PK_BROWSER_FAVORITES:
        वापस SDL_SCANCODE_AC_BOOKMARKS;
    हाल DOM_PK_BROWSER_REFRESH:
        वापस SDL_SCANCODE_AC_REFRESH;
    हाल DOM_PK_BROWSER_STOP:
        वापस SDL_SCANCODE_AC_STOP;
    हाल DOM_PK_BROWSER_FORWARD:
        वापस SDL_SCANCODE_AC_FORWARD;
    हाल DOM_PK_BROWSER_BACK:
        वापस SDL_SCANCODE_AC_BACK;
    हाल DOM_PK_MEDIA_SELECT:
        वापस SDL_SCANCODE_MEDIA_SELECT;
    }

    वापस SDL_SCANCODE_UNKNOWN;
}

अटल SDL_Window *Emscripten_GetFocusedWindow(SDL_VideoDevice *device)
{
    SDL_Window *window;
    क्रम (window = device->windows; window; window = window->अग्र) {
        SDL_Window_तथ्य *wdata = window->internal;

        स्थिर पूर्णांक focused = MAIN_THREAD_EM_ASM_INT({
            var id = UTF8ToString($0);
            try
            {
                var canvas = document.querySelector(id);
                अगर (canvas) {
                    वापस canvas === document.activeElement;
                }
            }
            catch (e)
            {
                // querySelector throws if not a valid selector
            }
            वापस false;
        }, wdata->canvas_id);

        अगर (focused) {
            अवरोध;
        }
    }
    // If the DOM is focused, then at least one canvas in the DOM should be considered focused.
    // So in this case, just assume that the first canvas is focused.
    अगर (!window) {
        स्थिर पूर्णांक focused = MAIN_THREAD_EM_ASM_INT({
            वापस document.hasFocus();
        });
        अगर (focused) {
            window = device->windows;
        }
    }
    वापस window;
}

अटल EM_BOOL Emscripten_HandlePointerLockChange(पूर्णांक eventType, स्थिर EmscriptenPointerlockChangeEvent *changeEvent, व्योम *user_तथ्य)
{
    SDL_Window_तथ्य *window_तथ्य_2 = (SDL_Window_तथ्य *)user_तथ्य;
    // keep track of lock losses, so we can regrab if/when appropriate.
    window_तथ्य_2->has_pointer_lock = changeEvent->isActive;
    वापस 0;
}

अटल EM_BOOL Emscripten_HandlePointerLockChangeGlobal(पूर्णांक eventType, स्थिर EmscriptenPointerlockChangeEvent *changeEvent, व्योम *user_तथ्य)
{
    SDL_VideoDevice *device = user_तथ्य;
    bool prevent_default = false;
    SDL_Window *window;

    क्रम (window = device->windows; window; window = window->अग्र) {
        prevent_default |= Emscripten_HandlePointerLockChange(eventType, changeEvent, window->internal);
    }

    वापस prevent_default;
}

अटल EM_BOOL Emscripten_HandleWheel(पूर्णांक eventType, स्थिर EmscriptenWheelEvent *wheelEvent, व्योम *user_तथ्य)
{
    SDL_Window_तथ्य *window_तथ्य_2 = user_तथ्य;

    भग्न deltaY = wheelEvent->deltaY;
    भग्न deltaX = wheelEvent->deltaX;

    चयन (wheelEvent->deltaMode) {
    हाल DOM_DELTA_PIXEL:
        deltaX /= 100; // 100 pixels make up a step
        deltaY /= 100; // 100 pixels make up a step
        अवरोध;
    हाल DOM_DELTA_पंक्ति:
        deltaX /= 3; // 3 lines make up a step
        deltaY /= 3; // 3 lines make up a step
        अवरोध;
    हाल DOM_DELTA_PAGE:
        deltaX *= 80; // A page makes up 80 steps
        deltaY *= 80; // A page makes up 80 steps
        अवरोध;
    }

    SDL_SendMouseWheel(0, window_तथ्य_2->window, SDL_DEFAULT_MOUSE_ID, deltaX, -deltaY, SDL_MOUSEWHEEL_NORMAL);
    वापस SDL_EventEnabled(SDL_EVENT_MOUSE_WHEEL);
}

अटल EM_BOOL Emscripten_HandleFocus(पूर्णांक eventType, स्थिर EmscriptenFocusEvent *focusEvent, व्योम *user_तथ्य)
{
    SDL_VideoDevice *device = user_तथ्य;
    SDL_Window *window = Emscripten_GetFocusedWindow(device);

    SDL_EventType sdl_event_type;

    /* If the user switches away while keys are pressed (such as
     * via Alt+Tab), key release events won't be received. */
    अगर (eventType == EMSCRIPTEN_EVENT_BLUR) {
        SDL_ResetKeyboard();
    }

    sdl_event_type = (eventType == EMSCRIPTEN_EVENT_FOCUS) ? SDL_EVENT_WINDOW_FOCUS_GAINED : SDL_EVENT_WINDOW_FOCUS_LOST;
    SDL_SetKeyboardFocus(sdl_event_type == SDL_EVENT_WINDOW_FOCUS_GAINED ? window : शून्य);
    वापस SDL_EventEnabled(sdl_event_type);
}

अटल bool Is_Function_कुंजी(SDL_Scancode scancode)
{
    अगर (scancode >= SDL_SCANCODE_F1 && scancode <= SDL_SCANCODE_F12) {
        वापस true;
    }
    अगर (scancode >= SDL_SCANCODE_F13 && scancode <= SDL_SCANCODE_F24) {
        वापस true;
    }
    वापस false;
}

/* This is a great tool to see web keyboard events live:
 * https://w3c.github.io/uievents/tools/key-event-viewer.html
 */
अटल EM_BOOL Emscripten_Handle_कुंजी(पूर्णांक eventType, स्थिर EmscriptenKeyboardEvent *कुंजी_Event, व्योम *user_तथ्य)
{
    SDL_Window_तथ्य *window_तथ्य_2 = (SDL_Window_तथ्य *)user_तथ्य;
    SDL_Scancode scancode = Emscripten_MapScanCode(कुंजी_Event->code);
    SDL_Keycode keycode = SDLK_UNKNOWN;
    bool prevent_default = false;
    bool is_nav_कुंजी = false;

    अगर (scancode == SDL_SCANCODE_UNKNOWN) {
        अगर (SDL_strcmp(कुंजी_Event->कुंजी, "Sleep") == 0) {
            scancode = SDL_SCANCODE_SLEEP;
        } अन्यथा अगर (SDL_strcmp(कुंजी_Event->कुंजी, "ChannelUp") == 0) {
            scancode = SDL_SCANCODE_CHANNEL_INCREMENT;
        } अन्यथा अगर (SDL_strcmp(कुंजी_Event->कुंजी, "ChannelDown") == 0) {
            scancode = SDL_SCANCODE_CHANNEL_DECREMENT;
        } अन्यथा अगर (SDL_strcmp(कुंजी_Event->कुंजी, "MediaPlay") == 0) {
            scancode = SDL_SCANCODE_MEDIA_PLAY;
        } अन्यथा अगर (SDL_strcmp(कुंजी_Event->कुंजी, "MediaPause") == 0) {
            scancode = SDL_SCANCODE_MEDIA_PAUSE;
        } अन्यथा अगर (SDL_strcmp(कुंजी_Event->कुंजी, "MediaRecord") == 0) {
            scancode = SDL_SCANCODE_MEDIA_RECORD;
        } अन्यथा अगर (SDL_strcmp(कुंजी_Event->कुंजी, "MediaFastForward") == 0) {
            scancode = SDL_SCANCODE_MEDIA_FAST_FORWARD;
        } अन्यथा अगर (SDL_strcmp(कुंजी_Event->कुंजी, "MediaRewind") == 0) {
            scancode = SDL_SCANCODE_MEDIA_REWIND;
        } अन्यथा अगर (SDL_strcmp(कुंजी_Event->कुंजी, "Close") == 0) {
            scancode = SDL_SCANCODE_AC_CLOSE;
        } अन्यथा अगर (SDL_strcmp(कुंजी_Event->कुंजी, "New") == 0) {
            scancode = SDL_SCANCODE_AC_NEW;
        } अन्यथा अगर (SDL_strcmp(कुंजी_Event->कुंजी, "Open") == 0) {
            scancode = SDL_SCANCODE_AC_OPEN;
        } अन्यथा अगर (SDL_strcmp(कुंजी_Event->कुंजी, "Print") == 0) {
            scancode = SDL_SCANCODE_AC_PRINT;
        } अन्यथा अगर (SDL_strcmp(कुंजी_Event->कुंजी, "Save") == 0) {
            scancode = SDL_SCANCODE_AC_SAVE;
        } अन्यथा अगर (SDL_strcmp(कुंजी_Event->कुंजी, "Props") == 0) {
            scancode = SDL_SCANCODE_AC_PROPERTIES;
        }
    }

    अगर (scancode == SDL_SCANCODE_UNKNOWN) {
        // KaiOS Left Soft Key and Right Soft Key, they act as OK/Next/Menu and Cancel/Back/Clear
        अगर (SDL_strcmp(कुंजी_Event->कुंजी, "SoftLeft") == 0) {
            scancode = SDL_SCANCODE_AC_FORWARD;
        } अन्यथा अगर (SDL_strcmp(कुंजी_Event->कुंजी, "SoftRight") == 0) {
            scancode = SDL_SCANCODE_AC_BACK;
        }
    }

    अगर (कुंजी_Event->location == 0 && SDL_utf8strlen(कुंजी_Event->कुंजी) == 1) {
        स्थिर अक्षर *कुंजी = कुंजी_Event->कुंजी;
        keycode = SDL_StepUTF8(&कुंजी, शून्य);
        अगर (keycode == SDL_INVALID_UNICODE_CODEPOINT) {
            keycode = SDLK_UNKNOWN;
        }
    }

    अगर (keycode != SDLK_UNKNOWN) {
        prevent_default = SDL_Send_Keyboard_कुंजी_And_Keycode(0, SDL_DEFAULT_KEYBOARD_ID, 0, scancode, keycode, (eventType == EMSCRIPTEN_EVENT_KEYDOWN));
    } अन्यथा {
        prevent_default = SDL_Send_Keyboard_कुंजी(0, SDL_DEFAULT_KEYBOARD_ID, 0, scancode, (eventType == EMSCRIPTEN_EVENT_KEYDOWN));
    }

    /* if TEXTINPUT events are enabled we can't prevent keydown or we won't get keypress
     * we need to ALWAYS prevent backspace and tab otherwise chrome takes action and does bad navigation UX
     */
    अगर ((scancode == SDL_SCANCODE_BACKSPACE) ||
        (scancode == SDL_SCANCODE_TAB) ||
        (scancode == SDL_SCANCODE_बायाँ) ||
        (scancode == SDL_SCANCODE_UP) ||
        (scancode == SDL_SCANCODE_दायाँ) ||
        (scancode == SDL_SCANCODE_DOWN) ||
        Is_Function_कुंजी(scancode) ||
        कुंजी_Event->ctrl_कुंजी) {
        is_nav_कुंजी = true;
    }

    अगर ((eventType == EMSCRIPTEN_EVENT_KEYDOWN) && SDL_Text_निवेश_Active(window_तथ्य_2->window) && !is_nav_कुंजी) {
        prevent_default = false;
    }

    वापस prevent_default;
}

अटल EM_BOOL Emscripten_Handle_कुंजी_Press(पूर्णांक eventType, स्थिर EmscriptenKeyboardEvent *कुंजी_Event, व्योम *user_तथ्य)
{
    SDL_Window_तथ्य *window_तथ्य_2 = (SDL_Window_तथ्य *)user_तथ्य;

    अगर (SDL_Text_निवेश_Active(window_तथ्य_2->window)) {
        अगर (SDL_utf8strlen(कुंजी_Event->कुंजी) == 1) {
            SDL_SendKeyboardText(कुंजी_Event->कुंजी);
            वापस EM_TRUE;
        }
    }
    वापस EM_FALSE;
}

अटल EM_BOOL Emscripten_HandleFullscreenChange(पूर्णांक eventType, स्थिर EmscriptenFullscreenChangeEvent *fullscreenChangeEvent, व्योम *user_तथ्य)
{
    SDL_Window_तथ्य *window_तथ्य_2 = user_तथ्य;

    window_तथ्य_2->fullscreen_change_in_progress = false;

    अगर (fullscreenChangeEvent->isFullscreen) {
        SDL_SendWindowEvent(window_तथ्य_2->window, SDL_EVENT_WINDOW_ENTER_FULLSCREEN, 0, 0);
        window_तथ्य_2->fullscreen_mode_flags = 0;
    } अन्यथा {
        SDL_SendWindowEvent(window_तथ्य_2->window, SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
    }

    SDL_UpdateFullscreenMode(window_तथ्य_2->window, fullscreenChangeEvent->isFullscreen, false);

    वापस 0;
}

अटल EM_BOOL Emscripten_HandleFullscreenChangeGlobal(पूर्णांक eventType, स्थिर EmscriptenFullscreenChangeEvent *fullscreenChangeEvent, व्योम *user_तथ्य)
{
    SDL_VideoDevice *device = user_तथ्य;
    SDL_Window *window = शून्य;
    क्रम (window = device->windows; window != शून्य; window = window->अग्र) {
        स्थिर अक्षर *canvas_id = window->internal->canvas_id;
        अगर (*canvas_id == '#') {
            canvas_id++;
        }
        अगर (SDL_strcmp(fullscreenChangeEvent->id, canvas_id) == 0) {
            अवरोध;  // this is the window.
        }
    }

    अगर (window) {
        वापस Emscripten_HandleFullscreenChange(eventType, fullscreenChangeEvent, window->internal);
    }

    वापस EM_FALSE;
}

अटल EM_BOOL Emscripten_HandleResize(पूर्णांक eventType, स्थिर EmscriptenUiEvent *uiEvent, व्योम *user_तथ्य)
{
    SDL_Window_तथ्य *window_तथ्य_2 = user_तथ्य;

    bool force = false;

    // update pixel ratio
    अगर (window_तथ्य_2->window->flags & SDL_WINDOW_ऊपरी_PIXEL_DENSITY) {
        अगर (window_तथ्य_2->pixel_ratio != emscripten_get_device_pixel_ratio()) {
            window_तथ्य_2->pixel_ratio = emscripten_get_device_pixel_ratio();
            force = true;
        }
    }

    स्थिर bool fill_document = (Emscripten_fill_document_window == window_तथ्य_2->window);
    स्थिर bool fullscreen = (window_तथ्य_2->window->flags & SDL_WINDOW_FULLSCREEN) != 0;  // fullscreen windows can resize on Emscripten, and the canvas should fill it.
    स्थिर bool resizable = (window_तथ्य_2->window->flags & SDL_WINDOW_RESIZABLE) != 0;
    अगर (fill_document || fullscreen || resizable) {
        द्विगुन w, h;
        अगर (fill_document || fullscreen) {
            w = (द्विगुन) uiEvent->windowInnerWidth;
            h = (द्विगुन) uiEvent->windowInnerHeight;
        } अन्यथा {
            SDL_assert(window_तथ्य_2->window->flags & SDL_WINDOW_RESIZABLE);
            w = window_तथ्य_2->window->w;
            h = window_तथ्य_2->window->h;
            // this will only work if the canvas size is set through css
            अगर (window_तथ्य_2->external_आकार) {
                emscripten_get_element_css_आकार(window_तथ्य_2->canvas_id, &w, &h);
            }
        }

        emscripten_set_canvas_element_आकार(window_तथ्य_2->canvas_id, SDL_lroundf(w * window_तथ्य_2->pixel_ratio), SDL_lroundf(h * window_तथ्य_2->pixel_ratio));

        // set_canvas_size unsets this
        अगर (!window_तथ्य_2->external_आकार && window_तथ्य_2->pixel_ratio != 1.0f) {
            emscripten_set_element_css_आकार(window_तथ्य_2->canvas_id, w, h);
        }

        अगर (force) {
            // force the event to trigger, so pixel ratio changes can be handled
            window_तथ्य_2->window->w = 0;
            window_तथ्य_2->window->h = 0;
        }

        SDL_SendWindowEvent(window_तथ्य_2->window, SDL_EVENT_WINDOW_RESIZED, SDL_lroundf(w), SDL_lroundf(h));
    }

    वापस 0;
}

अटल EM_BOOL Emscripten_HandleResizeGlobal(पूर्णांक eventType, स्थिर EmscriptenUiEvent *uiEvent, व्योम *user_तथ्य)
{
    SDL_VideoDevice *device = user_तथ्य;
    bool prevent_default = false;
    SDL_Window *window;

    क्रम (window = device->windows; window; window = window->अग्र) {
        prevent_default |= Emscripten_HandleResize(eventType, uiEvent, window->internal);
    }

    वापस prevent_default;
}

EM_BOOL
Emscripten_HandleCanvasResize(पूर्णांक eventType, स्थिर व्योम *reserved, व्योम *user_तथ्य)
{
    // this is used during fullscreen changes
    SDL_Window_तथ्य *window_तथ्य_2 = user_तथ्य;

    अगर (window_तथ्य_2->fullscreen_resize) {
        द्विगुन css_w, css_h;
        emscripten_get_element_css_आकार(window_तथ्य_2->canvas_id, &css_w, &css_h);
        SDL_SendWindowEvent(window_तथ्य_2->window, SDL_EVENT_WINDOW_RESIZED, SDL_lroundf(css_w), SDL_lroundf(css_h));
    }

    वापस 0;
}

अटल EM_BOOL Emscripten_HandleVisibilityChange(पूर्णांक eventType, स्थिर EmscriptenVisibilityChangeEvent *visEvent, व्योम *user_तथ्य)
{
    SDL_Window_तथ्य *window_तथ्य_2 = user_तथ्य;
    SDL_SendWindowEvent(window_तथ्य_2->window, visEvent->hidden ? SDL_EVENT_WINDOW_HIDDEN : SDL_EVENT_WINDOW_SHOWN, 0, 0);
    वापस 0;
}

अटल स्थिर अक्षर *Emscripten_HandleBeforeUnload(पूर्णांक eventType, स्थिर व्योम *reserved, व्योम *user_तथ्य)
{
    /* This event will need to be handled synchronously, e.g. using
       SDL_AddEventWatch, as the page is being closed *now*. */
    SDL_SendQuit();  // the app might see this if they installed an event watcher.
    SDL_OnApplicationWillTerminate();  // calls SDL_AppQuit if appropriate, etc.
    वापस ""; // don't trigger confirmation dialog
}

अटल EM_BOOL Emscripten_HandleOrientationChange(पूर्णांक eventType, स्थिर EmscriptenOrientationChangeEvent *orientationChangeEvent, व्योम *user_तथ्य)
{
    SDL_DisplayOrientation orientation;
    चयन (orientationChangeEvent->orientation_सूचकांक) {
        #घोषणा CHECK_ORIENTATION(emsdk, sdl) हाल EMSCRIPTEN_ORIENTATION_##emsdk: orientation = SDL_ORIENTATION_##sdl; अवरोध
        CHECK_ORIENTATION(LANDSCAPE_PRIMARY, LANDSCAPE);
        CHECK_ORIENTATION(LANDSCAPE_SECONDARY, LANDSCAPE_FLIPPED);
        CHECK_ORIENTATION(PORTRAIT_PRIMARY, PORTRAIT);
        CHECK_ORIENTATION(PORTRAIT_SECONDARY, PORTRAIT_FLIPPED);
        #अघोषित CHECK_ORIENTATION
        शेष: orientation = SDL_ORIENTATION_UNKNOWN; अवरोध;
    }

    SDL_Window_तथ्य *window_तथ्य_2 = (SDL_Window_तथ्य *) user_तथ्य;
    SDL_SendDisplayEvent(SDL_GetVideoDisplayForWindow(window_तथ्य_2->window), SDL_EVENT_DISPLAY_ORIENTATION, orientation, 0);

    // fake a UI event so we can tell the app the canvas might have resized.
    EmscriptenUiEvent uiEvent;
    SDL_zero(uiEvent);
    uiEvent.documentBodyClientWidth = MAIN_THREAD_EM_ASM_INT( { वापस document.body.clientWidth; } );
    uiEvent.documentBodyClientHeight = MAIN_THREAD_EM_ASM_INT( { वापस document.body.clientHeight; } );
    uiEvent.windowInnerWidth = MAIN_THREAD_EM_ASM_INT( { वापस window.innerWidth; } );
    uiEvent.windowInnerHeight = MAIN_THREAD_EM_ASM_INT( { वापस window.innerHeight; } );
    uiEvent.windowOuterWidth = MAIN_THREAD_EM_ASM_INT( { वापस window.outerWidth; } );
    uiEvent.windowOuterHeight = MAIN_THREAD_EM_ASM_INT( { वापस window.outerHeight; } );
    uiEvent.scroll_शीर्ष = MAIN_THREAD_EM_ASM_INT( { वापस window.pageXOffset; } );
    uiEvent.scroll_बायाँ = MAIN_THREAD_EM_ASM_INT( { वापस window.pageYOffset; } );
    Emscripten_HandleResize(EMSCRIPTEN_EVENT_RESIZE, &uiEvent, user_तथ्य);

    वापस 0;
}

// IF YOU CHANGE THIS STRUCTURE, YOU NEED TO UPDATE THE JAVASCRIPT THAT FILLS IT IN: SDL3.makePointerEventCStruct, below.
#घोषणा PTRTYPE_MOUSE 1
#घोषणा PTRTYPE_TOUCH 2
#घोषणा PTRTYPE_PEN 3
प्रकार काष्ठा Emscripten_PointerEvent
{
    पूर्णांक pointer_type;
    पूर्णांक pointerid;
    पूर्णांक button;
    पूर्णांक buttons;
    पूर्णांक down;
    भग्न movementX;
    भग्न movementY;
    भग्न targetX;
    भग्न targetY;
    भग्न pressure;
    भग्न tangential_pressure;
    भग्न tiltx;
    भग्न tilty;
    भग्न rotation;
} Emscripten_PointerEvent;

अटल व्योम Emscripten_HandleMouseButton(SDL_Window_तथ्य *window_तथ्य_2, स्थिर Emscripten_PointerEvent *event)
{
    Uint8 sdl_button;
    bool down = false;
    चयन (event->button) {
        #घोषणा CHECK_MOUSE_BUTTON(jsbutton, downflag, sdlbutton) हाल jsbutton: sdl_button = SDL_BUTTON_##sdlbutton; down = (event->down != 0) || ((event->buttons & downflag) != 0); अवरोध
        CHECK_MOUSE_BUTTON(0, 1, बायाँ_2);
        CHECK_MOUSE_BUTTON(1, 4, मध्य_2);
        CHECK_MOUSE_BUTTON(2, 2, दायाँ_2);
        CHECK_MOUSE_BUTTON(3, 8, X1);
        CHECK_MOUSE_BUTTON(4, 16, X2);
        #अघोषित CHECK_MOUSE_BUTTON
        शेष: sdl_button = 0; अवरोध;
    }

    अगर (sdl_button) {
        स्थिर SDL_Mouse *mouse = SDL_GetMouse();
        SDL_assert(mouse != शून्य);

        अगर (down) {
            अगर (mouse->relative_mode && !window_तथ्य_2->has_pointer_lock) {
                emscripten_request_pointerlock(window_तथ्य_2->canvas_id, 0); // try to regrab lost pointer lock.
            }
        }

        SDL_SendMouseButton(0, window_तथ्य_2->window, SDL_DEFAULT_MOUSE_ID, sdl_button, down);

        // We have an imaginary mouse capture, because we need SDL to not drop our imaginary mouse focus when we leave the canvas.
        अगर (mouse->auto_capture) {
            अगर (SDL_GetMouseState(शून्य, शून्य) != 0) {
                window_तथ्य_2->window->flags |= SDL_WINDOW_MOUSE_CAPTURE;
            } अन्यथा {
                window_तथ्य_2->window->flags &= ~SDL_WINDOW_MOUSE_CAPTURE;
            }
        }

        अगर (!down && window_तथ्य_2->mouse_focus_loss_pending) {
            window_तथ्य_2->mouse_focus_loss_pending = (window_तथ्य_2->window->flags & SDL_WINDOW_MOUSE_CAPTURE) != 0;
            अगर (!window_तथ्य_2->mouse_focus_loss_pending) {
                SDL_SetMouseFocus(शून्य);
            }
        }
    }
}

अटल व्योम Emscripten_UpdateMouseFromEvent(SDL_Window_तथ्य *window_तथ्य_2, स्थिर Emscripten_PointerEvent *event)
{
    SDL_assert(event->pointer_type == PTRTYPE_MOUSE);

    // Hidden windows (e.g. a shared GL-context window) may share the DOM canvas with the
    // visible window. Their pointer-event listeners would otherwise fire alongside the
    // visible window's, fighting over `mouse->focus` and producing events tagged with the
    // hidden window's ID -- causing downstream consumers that key by window ID to silently
    // drop them. Hidden windows shouldn't take part in user-input dispatch.
    अगर (window_तथ्य_2->window->flags & SDL_WINDOW_HIDDEN) {
        वापस;
    }

    // rescale (in case canvas is being scaled)
    द्विगुन client_w, client_h;
    emscripten_get_element_css_आकार(window_तथ्य_2->canvas_id, &client_w, &client_h);
    स्थिर द्विगुन xscale = window_तथ्य_2->window->w / client_w;
    स्थिर द्विगुन yscale = window_तथ्य_2->window->h / client_h;

    स्थिर bool isPointerLocked = window_तथ्य_2->has_pointer_lock;
    भग्न mx, my;
    अगर (isPointerLocked) {
        mx = (भग्न)(event->movementX * xscale);
        my = (भग्न)(event->movementY * yscale);
    } अन्यथा {
        mx = (भग्न)(event->targetX * xscale);
        my = (भग्न)(event->targetY * yscale);
    }

    SDL_SendMouseMotion(0, window_तथ्य_2->window, SDL_DEFAULT_MOUSE_ID, isPointerLocked, mx, my);

    Emscripten_HandleMouseButton(window_तथ्य_2, event);
}

अटल व्योम Emscripten_UpdateTouchFromEvent(SDL_Window_तथ्य *window_तथ्य_2, स्थिर Emscripten_PointerEvent *event)
{
    SDL_assert(event->pointer_type == PTRTYPE_TOUCH);

    स्थिर SDL_TouchID deviceId = 1;
    अगर (SDL_AddTouch(deviceId, SDL_TOUCH_DEVICE_DIRECT, "") < 0) {
        वापस;
    }

    द्विगुन client_w, client_h;
    emscripten_get_element_css_आकार(window_तथ्य_2->canvas_id, &client_w, &client_h);

    स्थिर SDL_FingerID id = event->pointerid + 1;
    भग्न x, y;
    अगर (client_w <= 1) {
        x = 0.5f;
    } अन्यथा {
        x = event->targetX / (client_w - 1);
    }
    अगर (client_h <= 1) {
        y = 0.5f;
    } अन्यथा {
        y = event->targetY / (client_h - 1);
    }

    स्थिर bool down = (event->buttons & 1) != 0;
    अगर (event->button == 0) {  // touch is starting or ending if this is zero (-1 means "no change").
        अगर (down) {
            SDL_SendTouch(0, deviceId, id, window_तथ्य_2->window, SDL_EVENT_FINGER_DOWN, x, y, 1.0f);
        }
    }

    SDL_SendTouchMotion(0, deviceId, id, window_तथ्य_2->window, x, y, 1.0f);

    अगर (event->button == 0) {  // touch is starting or ending if this is zero (-1 means "no change").
        अगर (!down) {
            SDL_SendTouch(0, deviceId, id, window_तथ्य_2->window, SDL_EVENT_FINGER_UP, x, y, 1.0f);
        }
    }
}

अटल व्योम Emscripten_UpdatePenFromEvent(SDL_Window_तथ्य *window_तथ्य_2, स्थिर Emscripten_PointerEvent *event)
{
    SDL_assert(event->pointer_type == PTRTYPE_PEN);
    स्थिर SDL_PenID pen = SDL_FindPenByHandle((व्योम *) (माप_प्रकार) 1);   // something > 0 for the single pen handle.
    अगर (pen) {
        // rescale (in case canvas is being scaled)
        द्विगुन client_w, client_h;
        emscripten_get_element_css_आकार(window_तथ्य_2->canvas_id, &client_w, &client_h);
        स्थिर द्विगुन xscale = window_तथ्य_2->window->w / client_w;
        स्थिर द्विगुन yscale = window_तथ्य_2->window->h / client_h;

        स्थिर bool isPointerLocked = window_तथ्य_2->has_pointer_lock;
        भग्न mx, my;
        अगर (isPointerLocked) {
            mx = (भग्न)(event->movementX * xscale);
            my = (भग्न)(event->movementY * yscale);
        } अन्यथा {
            mx = (भग्न)(event->targetX * xscale);
            my = (भग्न)(event->targetY * yscale);
        }

        SDL_SendPenMotion(0, pen, window_तथ्य_2->window, mx, my);

        अगर (event->button == 0) {  // pen touch
            bool down = ((event->buttons & 1) != 0);
            SDL_SendPenTouch(0, pen, window_तथ्य_2->window, false, down);
        } अन्यथा अगर (event->button == 5) {  // eraser touch...? Not sure if this is right...
            bool down = ((event->buttons & 32) != 0);
            SDL_SendPenTouch(0, pen, window_तथ्य_2->window, true, down);
        } अन्यथा अगर (event->button == 1) {
            bool down = ((event->buttons & 4) != 0);
            SDL_SendPenButton(0, pen, window_तथ्य_2->window, 2, down);
        } अन्यथा अगर (event->button == 2) {
            bool down = ((event->buttons & 2) != 0);
            SDL_SendPenButton(0, pen, window_तथ्य_2->window, 1, down);
        }

        SDL_SendPenAxis(0, pen, window_तथ्य_2->window, SDL_PEN_AXIS_PRESSURE, event->pressure);
        SDL_SendPenAxis(0, pen, window_तथ्य_2->window, SDL_PEN_AXIS_TANGENTIAL_PRESSURE, event->tangential_pressure);
        SDL_SendPenAxis(0, pen, window_तथ्य_2->window, SDL_PEN_AXIS_XTILT, event->tiltx);
        SDL_SendPenAxis(0, pen, window_तथ्य_2->window, SDL_PEN_AXIS_YTILT, event->tilty);
        SDL_SendPenAxis(0, pen, window_तथ्य_2->window, SDL_PEN_AXIS_ROTATION, event->rotation);
    }
}

अटल व्योम Emscripten_UpdatePointerFromEvent(SDL_Window_तथ्य *window_तथ्य_2, स्थिर Emscripten_PointerEvent *event)
{
    SDL_assert(event != शून्य);
    अगर (event->pointer_type == PTRTYPE_MOUSE) {
        Emscripten_UpdateMouseFromEvent(window_तथ्य_2, event);
    } अन्यथा अगर (event->pointer_type == PTRTYPE_TOUCH) {
        Emscripten_UpdateTouchFromEvent(window_तथ्य_2, event);
    } अन्यथा अगर (event->pointer_type == PTRTYPE_PEN) {
        Emscripten_UpdatePenFromEvent(window_तथ्य_2, event);
    } अन्यथा {
        SDL_assert(!"Unexpected pointer event type");
    }
}

अटल व्योम Emscripten_HandleMouseFocus(SDL_Window_तथ्य *window_तथ्य_2, स्थिर Emscripten_PointerEvent *event, bool isenter)
{
    SDL_assert(event->pointer_type == PTRTYPE_MOUSE);

    // Hidden windows shouldn't ever become the mouse-focus target.
    अगर (window_तथ्य_2->window->flags & SDL_WINDOW_HIDDEN) {
        वापस;
    }

    स्थिर bool isPointerLocked = window_तथ्य_2->has_pointer_lock;

    अगर (!isPointerLocked) {
        // rescale (in case canvas is being scaled)
        भग्न mx, my;
        द्विगुन client_w, client_h;
        emscripten_get_element_css_आकार(window_तथ्य_2->canvas_id, &client_w, &client_h);

        mx = (भग्न)(event->targetX * (window_तथ्य_2->window->w / client_w));
        my = (भग्न)(event->targetY * (window_तथ्य_2->window->h / client_h));
        SDL_SendMouseMotion(0, window_तथ्य_2->window, SDL_GLOBAL_MOUSE_ID, isPointerLocked, mx, my);
    }

    अगर (isenter && window_तथ्य_2->mouse_focus_loss_pending) {
        window_तथ्य_2->mouse_focus_loss_pending = false;  // just drop the state, but don't send the enter event.
    } अन्यथा अगर (!isenter && (window_तथ्य_2->window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
        window_तथ्य_2->mouse_focus_loss_pending = true;  // waiting on a mouse button to let go before we send the mouse focus update.
    } अन्यथा {
        SDL_SetMouseFocus(isenter ? window_तथ्य_2->window : शून्य);
    }
}

अटल व्योम Emscripten_HandlePenEnter(SDL_Window_तथ्य *window_तथ्य_2, स्थिर Emscripten_PointerEvent *event)
{
    SDL_assert(event->pointer_type == PTRTYPE_PEN);

    // event->pointerid is one continuous interaction; it doesn't necessarily track a specific tool over time, like the same finger's ID changed on each new touch event.
    // as such, we only expose a single pen, and when the touch ends, we say it lost proximity instead of the calling SDL_RemovePenDevice().

    SDL_PenID pen = SDL_FindPenByHandle((व्योम *) (माप_प्रकार) 1);  // something > 0 for the single pen handle.
    अगर (pen) {
        SDL_SendPenProximity(0, pen, window_तथ्य_2->window, true, true);
    } अन्यथा {
        // Web browsers offer almost none of this information as specifics, but can without warning offer any of these specific things.
        SDL_PenInfo peninfo;
        SDL_zero(peninfo);
        peninfo.capabilities = SDL_PEN_CAPABILITY_PRESSURE | SDL_PEN_CAPABILITY_ROTATION | SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT | SDL_PEN_CAPABILITY_TANGENTIAL_PRESSURE | SDL_PEN_CAPABILITY_ERASER;
        peninfo.max_tilt = 90.0f;
        peninfo.अंक_buttons = 2;
        peninfo.subtype = SDL_PEN_TYPE_PEN;
        SDL_AddPenDevice(0, शून्य, window_तथ्य_2->window, &peninfo, (व्योम *) (माप_प्रकार) 1, true);
    }

    Emscripten_UpdatePenFromEvent(window_तथ्य_2, event);
}

EMSCRIPTEN_KEEPALIVE व्योम Emscripten_HandlePointerEnter(SDL_Window_तथ्य *window_तथ्य_2, स्थिर Emscripten_PointerEvent *event)
{
    SDL_assert(event != शून्य);
    अगर (event->pointer_type == PTRTYPE_MOUSE) {
        Emscripten_HandleMouseFocus(window_तथ्य_2, event, true);
    } अन्यथा अगर (event->pointer_type == PTRTYPE_PEN) {
        Emscripten_HandlePenEnter(window_तथ्य_2, event);
    } अन्यथा अगर (event->pointer_type == PTRTYPE_TOUCH) {
        // do nothing.
    } अन्यथा {
        SDL_assert(!"Unexpected pointer event type");
    }
}

अटल व्योम Emscripten_HandlePenLeave(SDL_Window_तथ्य *window_तथ्य_2, स्थिर Emscripten_PointerEvent *event)
{
    स्थिर SDL_PenID pen = SDL_FindPenByHandle((व्योम *) (माप_प्रकार) 1);   // something > 0 for the single pen handle.
    अगर (pen) {
        Emscripten_UpdatePointerFromEvent(window_तथ्य_2, event);  // last data updates?
        SDL_SendPenProximity(0, pen, window_तथ्य_2->window, false, false);
    }
}

अटल व्योम Emscripten_HandleTouchCancel(SDL_Window_तथ्य *window_तथ्य_2, स्थिर Emscripten_PointerEvent *event)
{
    SDL_assert(event->pointer_type == PTRTYPE_TOUCH);

    स्थिर SDL_TouchID deviceId = 1;
    अगर (SDL_AddTouch(deviceId, SDL_TOUCH_DEVICE_DIRECT, "") < 0) {
        वापस;
    }

    द्विगुन client_w, client_h;
    emscripten_get_element_css_आकार(window_तथ्य_2->canvas_id, &client_w, &client_h);

    स्थिर SDL_FingerID id = event->pointerid + 1;
    भग्न x, y;
    अगर (client_w <= 1) {
        x = 0.5f;
    } अन्यथा {
        x = event->targetX / (client_w - 1);
    }
    अगर (client_h <= 1) {
        y = 0.5f;
    } अन्यथा {
        y = event->targetY / (client_h - 1);
    }

    SDL_SendTouch(0, deviceId, id, window_तथ्य_2->window, SDL_EVENT_FINGER_CANCELED, x, y, 1.0f);
}

EMSCRIPTEN_KEEPALIVE व्योम Emscripten_HandlePointerLeave(SDL_Window_तथ्य *window_तथ्य_2, स्थिर Emscripten_PointerEvent *event)
{
    SDL_assert(event != शून्य);
    अगर (event->pointer_type == PTRTYPE_MOUSE) {
        Emscripten_HandleMouseFocus(window_तथ्य_2, event, false);
    } अन्यथा अगर (event->pointer_type == PTRTYPE_PEN) {
        Emscripten_HandlePenLeave(window_तथ्य_2, event);
    } अन्यथा अगर (event->pointer_type == PTRTYPE_TOUCH) {
        Emscripten_HandleTouchCancel(window_तथ्य_2, event);
    } अन्यथा {
        SDL_assert(!"Unexpected pointer event type");
    }
}

EMSCRIPTEN_KEEPALIVE व्योम Emscripten_HandlePointerGeneric(SDL_Window_तथ्य *window_तथ्य_2, स्थिर Emscripten_PointerEvent *event)
{
    SDL_assert(event != शून्य);
    Emscripten_UpdatePointerFromEvent(window_तथ्य_2, event);
}

अटल व्योम Emscripten_prep_pointer_event_callbacks(व्योम)
{
    MAIN_THREAD_EM_ASM({
        var SDL3 = Module['SDL3'];

        अगर (SDL3.makePointerEventCStruct === undefined) {
            SDL3.makePointerEventCStruct = function(बायाँ, शीर्ष, event) {
                var ptrtype = 0;
                अगर (event.pointerType == "mouse") {
                    ptrtype = 1;
                } अन्यथा अगर (event.pointerType == "touch") {
                    ptrtype = 2;
                } अन्यथा अगर (event.pointerType == "pen") {
                    ptrtype = 3;
                } अन्यथा {
                    वापस 0;
                }

                var ptr = _SDL_malloc($0);
                अगर (ptr != 0) {
                    var idx = SDL3.CPtr_To_Heap32_सूचकांक(ptr);
                    HEAP32[idx++] = ptrtype;
                    HEAP32[idx++] = event.pointerId;
                    HEAP32[idx++] = (typeof(event.button) !== "undefined") ? event.button : -1;
                    HEAP32[idx++] = event.buttons;
                    HEAP32[idx++] = (event.type == "pointerdown") ? 1 : 0;
                    HEAPF32[idx++] = event.movementX;
                    HEAPF32[idx++] = event.movementY;
                    HEAPF32[idx++] = event.clientX - बायाँ;
                    HEAPF32[idx++] = event.clientY - शीर्ष;
                    अगर (ptrtype == 3) {
                        HEAPF32[idx++] = event.pressure;
                        HEAPF32[idx++] = event.tangentialPressure;
                        HEAPF32[idx++] = event.tiltX;
                        HEAPF32[idx++] = event.tiltY;
                        HEAPF32[idx++] = event.twist;
                    }
                }
                वापस ptr;
            };
        }
    }, माप (Emscripten_PointerEvent));
}

अटल व्योम Emscripten_set_pointer_event_callbacks(SDL_Window_तथ्य *तथ्य)
{
    Emscripten_prep_pointer_event_callbacks();

    MAIN_THREAD_EM_ASM({
        var target = document.querySelector(UTF8ToString($1));
        अगर (target) {
            var SDL3 = Module['SDL3'];
            var तथ्य = $0;
            target.sdlEventHandlerPointerEnter = function(event) {
                var rect = target.getBoundingClientRect();
                var d = SDL3.makePointerEventCStruct(rect.बायाँ, rect.शीर्ष, event);
                अगर (d != 0)
                {
                    _Emscripten_HandlePointerEnter(SDL3.JSVarToCPtr(तथ्य), d);
                    _SDL_free(d);
                }
            };
            target.sdlEventHandlerPointerLeave = function(event) {
                var rect = target.getBoundingClientRect();
                var d = SDL3.makePointerEventCStruct(rect.बायाँ, rect.शीर्ष, event);
                अगर (d != 0)
                {
                    _Emscripten_HandlePointerLeave(SDL3.JSVarToCPtr(तथ्य), d);
                    _SDL_free(d);
                }
            };
            target.sdlEventHandlerPointerGeneric = function(event) {
                var rect = target.getBoundingClientRect();
                var d = SDL3.makePointerEventCStruct(rect.बायाँ, rect.शीर्ष, event);
                अगर (d != 0)
                {
                    _Emscripten_HandlePointerGeneric(SDL3.JSVarToCPtr(तथ्य), d);
                    _SDL_free(d);
                }
            };

            target.style.touchAction = "none";  // or mobile devices will scroll as your touch moves across the element.
            target.addEventListener("pointerenter", target.sdlEventHandlerPointerEnter);
            target.addEventListener("pointerleave", target.sdlEventHandlerPointerLeave);
            target.addEventListener("pointercancel", target.sdlEventHandlerPointerLeave);
            target.addEventListener("pointerdown", target.sdlEventHandlerPointerGeneric);
            target.addEventListener("pointermove", target.sdlEventHandlerPointerGeneric);
            target.addEventListener("pointerup", target.sdlEventHandlerPointerGeneric);
        }
    }, तथ्य, तथ्य->canvas_id);
}

अटल व्योम Emscripten_unset_pointer_event_callbacks(SDL_Window_तथ्य *तथ्य)
{
    MAIN_THREAD_EM_ASM({
        var target = document.querySelector(UTF8ToString($0));
        अगर (target) {
            target.removeEventListener("pointerenter", target.sdlEventHandlerPointerEnter);
            target.removeEventListener("pointerleave", target.sdlEventHandlerPointerLeave);
            target.removeEventListener("pointercancel", target.sdlEventHandlerPointerLeave);
            target.removeEventListener("pointerdown", target.sdlEventHandlerPointerGeneric);
            target.removeEventListener("pointermove", target.sdlEventHandlerPointerGeneric);
            target.removeEventListener("pointerup", target.sdlEventHandlerPointerGeneric);
            target.style.touchAction = "";  // let mobile devices scroll again as your touch moves across the element.
            target.sdlEventHandlerPointerEnter = undefined;
            target.sdlEventHandlerPointerLeave = undefined;
            target.sdlEventHandlerPointerGeneric = undefined;
        }
    }, तथ्य->canvas_id);
}

EMSCRIPTEN_KEEPALIVE व्योम Emscripten_HandleMouseButtonUpGlobal(SDL_VideoDevice *device, स्थिर Emscripten_PointerEvent *event)
{
    SDL_assert(device != शून्य);
    SDL_assert(event != शून्य);
    अगर (event->pointer_type == PTRTYPE_MOUSE) {
        क्रम (SDL_Window *window = device->windows; window; window = window->अग्र) {
            Emscripten_HandleMouseButton(window->internal, event);
        }
    }
}

अटल व्योम Emscripten_set_global_mouseup_callback(SDL_VideoDevice *device)
{
    Emscripten_prep_pointer_event_callbacks();

    MAIN_THREAD_EM_ASM({
        var target = document;
        अगर (target) {
            target.sdlEventHandlerMouseButtonUpGlobal = function(event) {
                var SDL3 = Module['SDL3'];
                var d = SDL3.makePointerEventCStruct(0, 0, event);
                अगर (d != 0)
                {
                    _Emscripten_HandleMouseButtonUpGlobal(SDL3.JSVarToCPtr($0), d);
                    _SDL_free(d);
                }
            };
            target.addEventListener("pointerup", target.sdlEventHandlerMouseButtonUpGlobal);
        }
    }, device);
}

अटल व्योम Emscripten_unset_global_mouseup_callback(SDL_VideoDevice *device)
{
    MAIN_THREAD_EM_ASM({
        var target = document;
        अगर (target) {
            target.removeEventListener("pointerup", target.sdlEventHandlerMouseButtonUpGlobal);
            target.sdlEventHandlerMouseButtonUpGlobal = undefined;
        }
    });
}

// IF YOU CHANGE THIS STRUCTURE, YOU NEED TO UPDATE THE JAVASCRIPT THAT FILLS IT IN: makeDropEventCStruct, below.
प्रकार काष्ठा Emscripten_DropEvent
{
    पूर्णांक x;
    पूर्णांक y;
} Emscripten_DropEvent;

EMSCRIPTEN_KEEPALIVE व्योम Emscripten_SendDragEvent(SDL_Window_तथ्य *window_तथ्य_2, स्थिर Emscripten_DropEvent *event)
{
    SDL_SendDropPosition(window_तथ्य_2->window, event->x, event->y);
}

EMSCRIPTEN_KEEPALIVE व्योम Emscripten_SendDragCompleteEvent(SDL_Window_तथ्य *window_तथ्य_2)
{
    SDL_SendDropComplete(window_तथ्य_2->window);
}

EMSCRIPTEN_KEEPALIVE व्योम Emscripten_SendDragTextEvent(SDL_Window_तथ्य *window_तथ्य_2, अक्षर *text)
{
    SDL_SendDropText(window_तथ्य_2->window, text);
}

EMSCRIPTEN_KEEPALIVE व्योम Emscripten_SendDragFileEvent(SDL_Window_तथ्य *window_तथ्य_2, अक्षर *filename)
{
    SDL_SendDropFile(window_तथ्य_2->window, शून्य, filename);
}

EM_JS_DEPS(dragndrop, "$writeArrayToMemory");

अटल व्योम Emscripten_set_drag_event_callbacks(SDL_Window_तथ्य *तथ्य)
{
    MAIN_THREAD_EM_ASM({
        var target = document.querySelector(UTF8ToString($1));
        अगर (target) {
            var तथ्य = $0;
            var SDL3 = Module['SDL3'];

            var makeDropEventCStruct = function(event) {
                var ptr = 0;
                ptr = _SDL_malloc($2);
                अगर (ptr != 0) {
                    var idx = ptr >> 2;
                    var rect = target.getBoundingClientRect();
                    HEAP32[idx++] = event.clientX - rect.बायाँ;
                    HEAP32[idx++] = event.clientY - rect.शीर्ष;
                }
                वापस ptr;
            };

            SDL3.eventHandlerDropDragover = function(event) {
                event.preventDefault();
                var d = makeDropEventCStruct(event); अगर (d != 0) { _Emscripten_SendDragEvent(तथ्य, d); _SDL_free(d); }
            };
            target.addEventListener("dragover", SDL3.eventHandlerDropDragover);

            SDL3.drop_गिनती = 0;

            // FS.* functions throw exceptions when there are errors (such as the temp dir already existing),
            //  but we ignore all of these in a catch handler; you just won't get the drop event if there's a problem.
            try { FS.सूची_गढ़ो("/tmp/filedrop"); } catch (e) {}

            SDL3.eventHandlerDropDrop = function(event) {
                event.preventDefault();
                अगर (event.तथ्य_Transfer.types.includes("text/plain")) {
                    let plain_text = stringToNewUTF8(event.तथ्य_Transfer.get_तथ्य("text/plain"));
                    _Emscripten_SendDragTextEvent(तथ्य, plain_text);
                    _Emscripten_force_free(plain_text);
                } अन्यथा अगर (event.तथ्य_Transfer.types.includes("Files")) {
                    let files_read = 0;
                    स्थिर files_to_read = event.तथ्य_Transfer.files.लंबाई;
                    क्रम (let i = 0; i < files_to_read; i++) {
                        स्थिर file = event.तथ्य_Transfer.files.item(i);
                        स्थिर file_reader = new FileReader();
                        file_reader.read_As_Array_बफर(file);
                        file_reader.onload = function(event) {
                            स्थिर fs_dropdir = `/tmp/filedrop/${SDL3.drop_गिनती}`;
                            SDL3.drop_गिनती += 1;

                            स्थिर fs_filepath = `${fs_dropdir}/${file.name}`;
                            स्थिर c_fs_filepath = stringToNewUTF8(fs_filepath);
                            स्थिर contents_array8 = new Uint8Array(event.target.परिणाम);

                            try {
                                FS.सूची_गढ़ो(fs_dropdir);
                                var stream = FS.खोलो(fs_filepath, "w");
                                FS.ग_लिखो(stream, contents_array8, 0, contents_array8.लंबाई, 0);
                                FS.बंद(stream);
                                _Emscripten_SendDragFileEvent(तथ्य, c_fs_filepath);
                            } catch (e) {
                                // if this threw an exception at any point, we skip this drop event. Sorry!
                            }
                            _Emscripten_force_free(c_fs_filepath);
                            onFileRead();
                        };
                        file_reader.onerror = function(event) {
                            // Handle when error occurs to ensure that the drag event can still complete
                            onFileRead();
                        };
                    }
                    function onFileRead() {
                        ++files_read;
                        अगर (files_read === files_to_read) {
                            _Emscripten_SendDragCompleteEvent(तथ्य);
                        }
                    }
                }
                _Emscripten_SendDragCompleteEvent(तथ्य);
            };
            target.addEventListener("drop", SDL3.eventHandlerDropDrop);

            SDL3.eventHandlerDropDragend = function(event) {
                event.preventDefault();
                _Emscripten_SendDragCompleteEvent(तथ्य);
            };
            target.addEventListener("dragend", SDL3.eventHandlerDropDragend);
            target.addEventListener("dragleave", SDL3.eventHandlerDropDragend);
        }
    }, तथ्य, तथ्य->canvas_id, माप (Emscripten_DropEvent));
}

अटल व्योम Emscripten_unset_drag_event_callbacks(SDL_Window_तथ्य *तथ्य)
{
    MAIN_THREAD_EM_ASM({
        var target = document.querySelector(UTF8ToString($0));
        अगर (target) {
            var SDL3 = Module['SDL3'];
            target.removeEventListener("dragleave", SDL3.eventHandlerDropDragend);
            target.removeEventListener("dragend", SDL3.eventHandlerDropDragend);
            target.removeEventListener("drop", SDL3.eventHandlerDropDrop);
            SDL3.drop_गिनती = undefined;

            function recursive_remove(dirpath) {
                FS.सूची_पढ़ो(dirpath).forEach((filename) => {
                    स्थिर p = `${dirpath}/${filename}`;
                    स्थिर p_s = FS.stat(p);
                    अगर (FS.isFile(p_s.mode)) {
                        FS.unlink(p);
                    } अन्यथा अगर (FS.isDir(p)) {
                        recursive_remove(p);
                    }
                });
                FS.सूची_हटाओ(dirpath);
            }("/tmp/filedrop");

            FS.सूची_हटाओ("/tmp/filedrop");
            target.removeEventListener("dragover", SDL3.eventHandlerDropDragover);
            SDL3.eventHandlerDropDragover = undefined;
            SDL3.eventHandlerDropDrop = undefined;
            SDL3.eventHandlerDropDragend = undefined;
        }
    }, तथ्य->canvas_id);
}

अटल स्थिर अक्षर *Emscripten_GetKeyboardTargetElement(स्थिर अक्षर *target)
{
    अगर (SDL_strcmp(target, "#none") == 0) {
        वापस शून्य;
    } अन्यथा अगर (SDL_strcmp(target, "#window") == 0) {
        वापस EMSCRIPTEN_EVENT_TARGET_WINDOW;
    } अन्यथा अगर (SDL_strcmp(target, "#document") == 0) {
        वापस EMSCRIPTEN_EVENT_TARGET_DOCUMENT;
    } अन्यथा अगर (SDL_strcmp(target, "#screen") == 0) {
        वापस EMSCRIPTEN_EVENT_TARGET_SCREEN;
    }

    वापस target;
}

व्योम Emscripten_RegisterGlobalEventHandlers(SDL_VideoDevice *device)
{
    Emscripten_set_global_mouseup_callback(device);

    emscripten_set_focus_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, device, 0, Emscripten_HandleFocus);
    emscripten_set_blur_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, device, 0, Emscripten_HandleFocus);

    emscripten_set_pointerlockchange_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, device, 0, Emscripten_HandlePointerLockChangeGlobal);

    emscripten_set_fullscreenchange_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, device, 0, Emscripten_HandleFullscreenChangeGlobal);

    emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, device, 0, Emscripten_HandleResizeGlobal);
}

व्योम Emscripten_UnregisterGlobalEventHandlers(SDL_VideoDevice *device)
{
    Emscripten_unset_global_mouseup_callback(device);

    emscripten_set_focus_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, शून्य, 0, शून्य);
    emscripten_set_blur_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, शून्य, 0, शून्य);

    emscripten_set_pointerlockchange_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, शून्य, 0, शून्य);

    emscripten_set_fullscreenchange_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, शून्य, 0, शून्य);

    emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, शून्य, 0, शून्य);
}

EMSCRIPTEN_KEEPALIVE व्योम Emscripten_Handle_Lock_कुंजियाँ_Check(SDL_Window_तथ्य *window_तथ्य_2, EM_BOOL capslock, EM_BOOL numlock, EM_BOOL scrolllock)
{
    स्थिर SDL_Keymod new_mods = (capslock ? SDL_KMOD_CAPS : 0) | (numlock ? SDL_KMOD_अंक : 0) | (scrolllock ? SDL_KMOD_SCROLL : 0);
    SDL_Keymod modstate = SDL_GetModState();
    अगर ((modstate & (SDL_KMOD_CAPS|SDL_KMOD_अंक|SDL_KMOD_SCROLL)) != new_mods) {
        modstate &= ~(SDL_KMOD_CAPS|SDL_KMOD_अंक|SDL_KMOD_SCROLL);
        modstate |= new_mods;
        SDL_SetModState(modstate);
    }
}

व्योम Emscripten_RegisterEventHandlers(SDL_Window_तथ्य *तथ्य)
{
    स्थिर अक्षर *कुंजी_Element;

    // There is only one window and that window is the canvas
    emscripten_set_wheel_callback(तथ्य->canvas_id, तथ्य, 0, Emscripten_HandleWheel);

    emscripten_set_orientationchange_callback(तथ्य, 0, Emscripten_HandleOrientationChange);

    कुंजी_Element = Emscripten_GetKeyboardTargetElement(तथ्य->keyboard_element);
    अगर (कुंजी_Element) {
        // Emscripten's HTML5 helpers do not deduplicate `addEventListener` calls:
        // see `registerOrRemoveHandler` in `emscripten/src/lib/libhtml5.js`.
        //
        // If a previous SDL window already registered keyboard handlers on the same
        // target, the new registration would *stack* a second listener, causing every
        // browser keydown to fire `Emscripten_HandleKey` twice.
        //
        // The duplicate calls then produce two `SDL_EVENT_KEY_DOWN` events per physical
        // keypress (the second one with `repeat=true`, due to the keystate-based repeat
        // detection in `SDL_SendKeyboardKeyInternal`).
        //
        // We must clear any prior handler on this target before installing ours:
        emscripten_set_keydown_callback(कुंजी_Element, शून्य, 0, शून्य);
        emscripten_set_keyup_callback(कुंजी_Element, शून्य, 0, शून्य);
        emscripten_set_keypress_callback(कुंजी_Element, शून्य, 0, शून्य);

        MAIN_THREAD_EM_ASM_INT({
            var तथ्य = $0;
            // our keymod state can get confused in various ways (changed capslock when browser didn't have focus, etc), and you can't query the current
            //  state from the DOM, outside of a keyboard event, so catch keypresses globally and reset mod state if it's unexpectedly wrong. Best we can do.
            //  Note that this thing _only_ adjusts the lock keys if necessary; the real SDL keypress handling happens elsewhere.

            // Remove any prior listener first -- `addEventListener` does not deduplicate either.
            अगर (document.sdl_Event_Handler_Lock_कुंजियाँ_Check) {
                document.removeEventListener("keydown", document.sdl_Event_Handler_Lock_कुंजियाँ_Check);
            }

            document.sdl_Event_Handler_Lock_कुंजियाँ_Check = function(event) {
                // don't try to adjust the state on the actual lock key presses; the normal key handler will catch that and adjust.
                अगर ((event.कुंजी != "CapsLock") && (event.कुंजी != "NumLock") && (event.कुंजी != "ScrollLock"))
                {
                    Emscripten_Handle_Lock_कुंजियाँ_Check_2(Module['SDL3'].JSVarToCPtr(तथ्य), event.getModifierState("CapsLock"), event.getModifierState("NumLock"), event.getModifierState("ScrollLock"));
                }
            };
            document.addEventListener("keydown", document.sdl_Event_Handler_Lock_कुंजियाँ_Check);
        }, तथ्य);
        emscripten_set_keydown_callback(कुंजी_Element, तथ्य, 0, Emscripten_Handle_कुंजी);
        emscripten_set_keyup_callback(कुंजी_Element, तथ्य, 0, Emscripten_Handle_कुंजी);
        emscripten_set_keypress_callback(कुंजी_Element, तथ्य, 0, Emscripten_Handle_कुंजी_Press);
    }

    emscripten_set_visibilitychange_callback(तथ्य, 0, Emscripten_HandleVisibilityChange);

    emscripten_set_beforeunload_callback(तथ्य, Emscripten_HandleBeforeUnload);

    // !!! FIXME: currently Emscripten doesn't have a Pointer Events functions like emscripten_set_*_callback, but we should use those when they do:
    // !!! FIXME:  https://github.com/emscripten-core/emscripten/issues/7278#issuecomment-2280024621
    Emscripten_set_pointer_event_callbacks(तथ्य);

    // !!! FIXME: currently Emscripten doesn't have a Drop Events functions like emscripten_set_*_callback, but we should use those when they do:
    Emscripten_set_drag_event_callbacks(तथ्य);
}

व्योम Emscripten_UnregisterEventHandlers(SDL_Window_तथ्य *तथ्य)
{
    स्थिर अक्षर *कुंजी_Element;

    // !!! FIXME: currently Emscripten doesn't have a Drop Events functions like emscripten_set_*_callback, but we should use those when they do:
    Emscripten_unset_drag_event_callbacks(तथ्य);

    // !!! FIXME: currently Emscripten doesn't have a Pointer Events functions like emscripten_set_*_callback, but we should use those when they do:
    // !!! FIXME:  https://github.com/emscripten-core/emscripten/issues/7278#issuecomment-2280024621
    Emscripten_unset_pointer_event_callbacks(तथ्य);

    // only works due to having one window
    emscripten_set_wheel_callback(तथ्य->canvas_id, शून्य, 0, शून्य);

    emscripten_set_orientationchange_callback(शून्य, 0, शून्य);

    कुंजी_Element = Emscripten_GetKeyboardTargetElement(तथ्य->keyboard_element);
    अगर (कुंजी_Element) {
        emscripten_set_keydown_callback(कुंजी_Element, शून्य, 0, शून्य);
        emscripten_set_keyup_callback(कुंजी_Element, शून्य, 0, शून्य);
        emscripten_set_keypress_callback(कुंजी_Element, शून्य, 0, शून्य);
        MAIN_THREAD_EM_ASM_INT({
            document.removeEventListener("keydown", document.sdl_Event_Handler_Lock_कुंजियाँ_Check);
        });
    }

    emscripten_set_visibilitychange_callback(शून्य, 0, शून्य);

    emscripten_set_beforeunload_callback(शून्य, शून्य);
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_EMSCRIPTEN

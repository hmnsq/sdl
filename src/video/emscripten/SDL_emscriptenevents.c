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

#ifdef SDL_VIDEO_DRIVER_EMSCRIPTEN

#অন্তর্ভাব <emscripten/html5.h>
#অন্তর্ভাব <emscripten/dom_pk_codes.h>

#অন্তর্ভাব "../../events/SDL_dropevents_c.h"
#অন্তর্ভাব "../../events/SDL_events_c.h"
#অন্তর্ভাব "../../events/SDL_keyboard_c.h"
#অন্তর্ভাব "../../events/SDL_touch_c.h"

#অন্তর্ভাব "SDL_emscriptenevents.h"
#অন্তর্ভাব "SDL_emscriptenvideo.h"

/*
Emscripten PK code to scancode
https://developer.mozilla.org/en-US/docs/Web/API/KeyboardEvent
https://developer.mozilla.org/en-US/docs/Web/API/KeyboardEvent/code
*/
স্থির ধ্রুবক SDL_Scancode emscripten_scancode_table[] = {
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

স্থির SDL_Scancode Emscripten_MapScanCode(ধ্রুবক অক্ষর *code)
{
    ধ্রুবক DOM_PK_CODE_TYPE pk_code = emscripten_compute_dom_pk_code(code);
    যদি (pk_code < SDL_arraysize(emscripten_scancode_table)) {
        ফেরত emscripten_scancode_table[pk_code];
    }

    নির্বাচন (pk_code) {
    ক্ষেত্র DOM_PK_PASTE:
        ফেরত SDL_SCANCODE_PASTE;
    ক্ষেত্র DOM_PK_MEDIA_TRACK_PREVIOUS:
        ফেরত SDL_SCANCODE_MEDIA_PREVIOUS_TRACK;
    ক্ষেত্র DOM_PK_CUT:
        ফেরত SDL_SCANCODE_CUT;
    ক্ষেত্র DOM_PK_COPY:
        ফেরত SDL_SCANCODE_COPY;
    ক্ষেত্র DOM_PK_MEDIA_TRACK_পরবর্তী:
        ফেরত SDL_SCANCODE_MEDIA_পরবর্তী_TRACK;
    ক্ষেত্র DOM_PK_NUMPAD_ENTER:
        ফেরত SDL_SCANCODE_KP_ENTER;
    ক্ষেত্র DOM_PK_CONTROL_ডান:
        ফেরত SDL_SCANCODE_RCTRL;
    ক্ষেত্র DOM_PK_AUDIO_VOLUME_MUTE:
        ফেরত SDL_SCANCODE_MUTE;
    ক্ষেত্র DOM_PK_MEDIA_PLAY_PAUSE:
        ফেরত SDL_SCANCODE_MEDIA_PLAY_PAUSE;
    ক্ষেত্র DOM_PK_MEDIA_STOP:
        ফেরত SDL_SCANCODE_MEDIA_STOP;
    ক্ষেত্র DOM_PK_EJECT:
        ফেরত SDL_SCANCODE_MEDIA_EJECT;
    ক্ষেত্র DOM_PK_AUDIO_VOLUME_DOWN:
        ফেরত SDL_SCANCODE_VOLUMEDOWN;
    ক্ষেত্র DOM_PK_AUDIO_VOLUME_UP:
        ফেরত SDL_SCANCODE_VOLUMEUP;
    ক্ষেত্র DOM_PK_BROWSER_HOME:
        ফেরত SDL_SCANCODE_AC_HOME;
    ক্ষেত্র DOM_PK_NUMPAD_DIVIDE:
        ফেরত SDL_SCANCODE_KP_DIVIDE;
    ক্ষেত্র DOM_PK_ALT_ডান:
        ফেরত SDL_SCANCODE_RALT;
    ক্ষেত্র DOM_PK_HELP:
        ফেরত SDL_SCANCODE_HELP;
    ক্ষেত্র DOM_PK_অঙ্ক_LOCK:
        ফেরত SDL_SCANCODE_NUMLOCKCLEAR;
    ক্ষেত্র DOM_PK_HOME:
        ফেরত SDL_SCANCODE_HOME;
    ক্ষেত্র DOM_PK_ARROW_UP:
        ফেরত SDL_SCANCODE_UP;
    ক্ষেত্র DOM_PK_PAGE_UP:
        ফেরত SDL_SCANCODE_PAGEUP;
    ক্ষেত্র DOM_PK_ARROW_বাম:
        ফেরত SDL_SCANCODE_বাম;
    ক্ষেত্র DOM_PK_ARROW_ডান:
        ফেরত SDL_SCANCODE_ডান;
    ক্ষেত্র DOM_PK_END:
        ফেরত SDL_SCANCODE_END;
    ক্ষেত্র DOM_PK_ARROW_DOWN:
        ফেরত SDL_SCANCODE_DOWN;
    ক্ষেত্র DOM_PK_PAGE_DOWN:
        ফেরত SDL_SCANCODE_PAGEDOWN;
    ক্ষেত্র DOM_PK_ঢোকাও:
        ফেরত SDL_SCANCODE_ঢোকাও;
    ক্ষেত্র DOM_PK_DELETE:
        ফেরত SDL_SCANCODE_DELETE;
    ক্ষেত্র DOM_PK_META_বাম:
        ফেরত SDL_SCANCODE_LGUI;
    ক্ষেত্র DOM_PK_META_ডান:
        ফেরত SDL_SCANCODE_RGUI;
    ক্ষেত্র DOM_PK_CONTEXT_MENU:
        ফেরত SDL_SCANCODE_APPLICATION;
    ক্ষেত্র DOM_PK_POWER:
        ফেরত SDL_SCANCODE_POWER;
    ক্ষেত্র DOM_PK_BROWSER_অনুসন্ধান:
        ফেরত SDL_SCANCODE_AC_অনুসন্ধান;
    ক্ষেত্র DOM_PK_BROWSER_FAVORITES:
        ফেরত SDL_SCANCODE_AC_BOOKMARKS;
    ক্ষেত্র DOM_PK_BROWSER_REFRESH:
        ফেরত SDL_SCANCODE_AC_REFRESH;
    ক্ষেত্র DOM_PK_BROWSER_STOP:
        ফেরত SDL_SCANCODE_AC_STOP;
    ক্ষেত্র DOM_PK_BROWSER_FORWARD:
        ফেরত SDL_SCANCODE_AC_FORWARD;
    ক্ষেত্র DOM_PK_BROWSER_BACK:
        ফেরত SDL_SCANCODE_AC_BACK;
    ক্ষেত্র DOM_PK_MEDIA_SELECT:
        ফেরত SDL_SCANCODE_MEDIA_SELECT;
    }

    ফেরত SDL_SCANCODE_UNKNOWN;
}

স্থির SDL_Window *Emscripten_GetFocusedWindow(SDL_VideoDevice *device)
{
    SDL_Window *window;
    জন্য (window = device->windows; window; window = window->পরবর্তী) {
        SDL_Window_তথ্য *wdata = window->internal;

        ধ্রুবক পূর্ণসংখ্যা focused = MAIN_THREAD_EM_ASM_INT({
            var id = UTF8ToString($0);
            try
            {
                var canvas = document.querySelector(id);
                যদি (canvas) {
                    ফেরত canvas === document.activeElement;
                }
            }
            catch (e)
            {
                // querySelector throws if not a valid selector
            }
            ফেরত false;
        }, wdata->canvas_id);

        যদি (focused) {
            বিরতি;
        }
    }
    // If the DOM is focused, then at least one canvas in the DOM should be considered focused.
    // So in this case, just assume that the first canvas is focused.
    যদি (!window) {
        ধ্রুবক পূর্ণসংখ্যা focused = MAIN_THREAD_EM_ASM_INT({
            ফেরত document.hasFocus();
        });
        যদি (focused) {
            window = device->windows;
        }
    }
    ফেরত window;
}

স্থির EM_BOOL Emscripten_HandlePointerLockChange(পূর্ণসংখ্যা eventType, ধ্রুবক EmscriptenPointerlockChangeEvent *changeEvent, শূন্য *user_তথ্য)
{
    SDL_Window_তথ্য *window_তথ্য_2 = (SDL_Window_তথ্য *)user_তথ্য;
    // keep track of lock losses, so we can regrab if/when appropriate.
    window_তথ্য_2->has_pointer_lock = changeEvent->isActive;
    ফেরত 0;
}

স্থির EM_BOOL Emscripten_HandlePointerLockChangeGlobal(পূর্ণসংখ্যা eventType, ধ্রুবক EmscriptenPointerlockChangeEvent *changeEvent, শূন্য *user_তথ্য)
{
    SDL_VideoDevice *device = user_তথ্য;
    bool prevent_default = false;
    SDL_Window *window;

    জন্য (window = device->windows; window; window = window->পরবর্তী) {
        prevent_default |= Emscripten_HandlePointerLockChange(eventType, changeEvent, window->internal);
    }

    ফেরত prevent_default;
}

স্থির EM_BOOL Emscripten_HandleWheel(পূর্ণসংখ্যা eventType, ধ্রুবক EmscriptenWheelEvent *wheelEvent, শূন্য *user_তথ্য)
{
    SDL_Window_তথ্য *window_তথ্য_2 = user_তথ্য;

    দশমিক deltaY = wheelEvent->deltaY;
    দশমিক deltaX = wheelEvent->deltaX;

    নির্বাচন (wheelEvent->deltaMode) {
    ক্ষেত্র DOM_DELTA_PIXEL:
        deltaX /= 100; // 100 pixels make up a step
        deltaY /= 100; // 100 pixels make up a step
        বিরতি;
    ক্ষেত্র DOM_DELTA_সারি:
        deltaX /= 3; // 3 lines make up a step
        deltaY /= 3; // 3 lines make up a step
        বিরতি;
    ক্ষেত্র DOM_DELTA_PAGE:
        deltaX *= 80; // A page makes up 80 steps
        deltaY *= 80; // A page makes up 80 steps
        বিরতি;
    }

    SDL_SendMouseWheel(0, window_তথ্য_2->window, SDL_DEFAULT_MOUSE_ID, deltaX, -deltaY, SDL_MOUSEWHEEL_NORMAL);
    ফেরত SDL_EventEnabled(SDL_EVENT_MOUSE_WHEEL);
}

স্থির EM_BOOL Emscripten_HandleFocus(পূর্ণসংখ্যা eventType, ধ্রুবক EmscriptenFocusEvent *focusEvent, শূন্য *user_তথ্য)
{
    SDL_VideoDevice *device = user_তথ্য;
    SDL_Window *window = Emscripten_GetFocusedWindow(device);

    SDL_EventType sdl_event_type;

    /* If the user switches away while keys are pressed (such as
     * via Alt+Tab), key release events won't be received. */
    যদি (eventType == EMSCRIPTEN_EVENT_BLUR) {
        SDL_ResetKeyboard();
    }

    sdl_event_type = (eventType == EMSCRIPTEN_EVENT_FOCUS) ? SDL_EVENT_WINDOW_FOCUS_GAINED : SDL_EVENT_WINDOW_FOCUS_LOST;
    SDL_SetKeyboardFocus(sdl_event_type == SDL_EVENT_WINDOW_FOCUS_GAINED ? window : ফাঁকা);
    ফেরত SDL_EventEnabled(sdl_event_type);
}

স্থির bool Is_Function_চাবি(SDL_Scancode scancode)
{
    যদি (scancode >= SDL_SCANCODE_F1 && scancode <= SDL_SCANCODE_F12) {
        ফেরত true;
    }
    যদি (scancode >= SDL_SCANCODE_F13 && scancode <= SDL_SCANCODE_F24) {
        ফেরত true;
    }
    ফেরত false;
}

/* This is a great tool to see web keyboard events live:
 * https://w3c.github.io/uievents/tools/key-event-viewer.html
 */
স্থির EM_BOOL Emscripten_Handle_চাবি(পূর্ণসংখ্যা eventType, ধ্রুবক EmscriptenKeyboardEvent *চাবি_Event, শূন্য *user_তথ্য)
{
    SDL_Window_তথ্য *window_তথ্য_2 = (SDL_Window_তথ্য *)user_তথ্য;
    SDL_Scancode scancode = Emscripten_MapScanCode(চাবি_Event->code);
    SDL_Keycode keycode = SDLK_UNKNOWN;
    bool prevent_default = false;
    bool is_nav_চাবি = false;

    যদি (scancode == SDL_SCANCODE_UNKNOWN) {
        যদি (SDL_strcmp(চাবি_Event->চাবি, "Sleep") == 0) {
            scancode = SDL_SCANCODE_SLEEP;
        } অন্যথা যদি (SDL_strcmp(চাবি_Event->চাবি, "ChannelUp") == 0) {
            scancode = SDL_SCANCODE_CHANNEL_INCREMENT;
        } অন্যথা যদি (SDL_strcmp(চাবি_Event->চাবি, "ChannelDown") == 0) {
            scancode = SDL_SCANCODE_CHANNEL_DECREMENT;
        } অন্যথা যদি (SDL_strcmp(চাবি_Event->চাবি, "MediaPlay") == 0) {
            scancode = SDL_SCANCODE_MEDIA_PLAY;
        } অন্যথা যদি (SDL_strcmp(চাবি_Event->চাবি, "MediaPause") == 0) {
            scancode = SDL_SCANCODE_MEDIA_PAUSE;
        } অন্যথা যদি (SDL_strcmp(চাবি_Event->চাবি, "MediaRecord") == 0) {
            scancode = SDL_SCANCODE_MEDIA_RECORD;
        } অন্যথা যদি (SDL_strcmp(চাবি_Event->চাবি, "MediaFastForward") == 0) {
            scancode = SDL_SCANCODE_MEDIA_FAST_FORWARD;
        } অন্যথা যদি (SDL_strcmp(চাবি_Event->চাবি, "MediaRewind") == 0) {
            scancode = SDL_SCANCODE_MEDIA_REWIND;
        } অন্যথা যদি (SDL_strcmp(চাবি_Event->চাবি, "Close") == 0) {
            scancode = SDL_SCANCODE_AC_CLOSE;
        } অন্যথা যদি (SDL_strcmp(চাবি_Event->চাবি, "New") == 0) {
            scancode = SDL_SCANCODE_AC_NEW;
        } অন্যথা যদি (SDL_strcmp(চাবি_Event->চাবি, "Open") == 0) {
            scancode = SDL_SCANCODE_AC_OPEN;
        } অন্যথা যদি (SDL_strcmp(চাবি_Event->চাবি, "Print") == 0) {
            scancode = SDL_SCANCODE_AC_PRINT;
        } অন্যথা যদি (SDL_strcmp(চাবি_Event->চাবি, "Save") == 0) {
            scancode = SDL_SCANCODE_AC_SAVE;
        } অন্যথা যদি (SDL_strcmp(চাবি_Event->চাবি, "Props") == 0) {
            scancode = SDL_SCANCODE_AC_PROPERTIES;
        }
    }

    যদি (scancode == SDL_SCANCODE_UNKNOWN) {
        // KaiOS Left Soft Key and Right Soft Key, they act as OK/Next/Menu and Cancel/Back/Clear
        যদি (SDL_strcmp(চাবি_Event->চাবি, "SoftLeft") == 0) {
            scancode = SDL_SCANCODE_AC_FORWARD;
        } অন্যথা যদি (SDL_strcmp(চাবি_Event->চাবি, "SoftRight") == 0) {
            scancode = SDL_SCANCODE_AC_BACK;
        }
    }

    যদি (চাবি_Event->location == 0 && SDL_utf8strlen(চাবি_Event->চাবি) == 1) {
        ধ্রুবক অক্ষর *চাবি = চাবি_Event->চাবি;
        keycode = SDL_StepUTF8(&চাবি, ফাঁকা);
        যদি (keycode == SDL_INVALID_UNICODE_CODEPOINT) {
            keycode = SDLK_UNKNOWN;
        }
    }

    যদি (keycode != SDLK_UNKNOWN) {
        prevent_default = SDL_Send_Keyboard_চাবি_And_Keycode(0, SDL_DEFAULT_KEYBOARD_ID, 0, scancode, keycode, (eventType == EMSCRIPTEN_EVENT_KEYDOWN));
    } অন্যথা {
        prevent_default = SDL_Send_Keyboard_চাবি(0, SDL_DEFAULT_KEYBOARD_ID, 0, scancode, (eventType == EMSCRIPTEN_EVENT_KEYDOWN));
    }

    /* if TEXTINPUT events are enabled we can't prevent keydown or we won't get keypress
     * we need to ALWAYS prevent backspace and tab otherwise chrome takes action and does bad navigation UX
     */
    যদি ((scancode == SDL_SCANCODE_BACKSPACE) ||
        (scancode == SDL_SCANCODE_TAB) ||
        (scancode == SDL_SCANCODE_বাম) ||
        (scancode == SDL_SCANCODE_UP) ||
        (scancode == SDL_SCANCODE_ডান) ||
        (scancode == SDL_SCANCODE_DOWN) ||
        Is_Function_চাবি(scancode) ||
        চাবি_Event->ctrl_চাবি) {
        is_nav_চাবি = true;
    }

    যদি ((eventType == EMSCRIPTEN_EVENT_KEYDOWN) && SDL_Text_প্রবেশ_Active(window_তথ্য_2->window) && !is_nav_চাবি) {
        prevent_default = false;
    }

    ফেরত prevent_default;
}

স্থির EM_BOOL Emscripten_Handle_চাবি_Press(পূর্ণসংখ্যা eventType, ধ্রুবক EmscriptenKeyboardEvent *চাবি_Event, শূন্য *user_তথ্য)
{
    SDL_Window_তথ্য *window_তথ্য_2 = (SDL_Window_তথ্য *)user_তথ্য;

    যদি (SDL_Text_প্রবেশ_Active(window_তথ্য_2->window)) {
        যদি (SDL_utf8strlen(চাবি_Event->চাবি) == 1) {
            SDL_SendKeyboardText(চাবি_Event->চাবি);
            ফেরত EM_TRUE;
        }
    }
    ফেরত EM_FALSE;
}

স্থির EM_BOOL Emscripten_HandleFullscreenChange(পূর্ণসংখ্যা eventType, ধ্রুবক EmscriptenFullscreenChangeEvent *fullscreenChangeEvent, শূন্য *user_তথ্য)
{
    SDL_Window_তথ্য *window_তথ্য_2 = user_তথ্য;

    window_তথ্য_2->fullscreen_change_in_progress = false;

    যদি (fullscreenChangeEvent->isFullscreen) {
        SDL_SendWindowEvent(window_তথ্য_2->window, SDL_EVENT_WINDOW_ENTER_FULLSCREEN, 0, 0);
        window_তথ্য_2->fullscreen_mode_flags = 0;
    } অন্যথা {
        SDL_SendWindowEvent(window_তথ্য_2->window, SDL_EVENT_WINDOW_LEAVE_FULLSCREEN, 0, 0);
    }

    SDL_UpdateFullscreenMode(window_তথ্য_2->window, fullscreenChangeEvent->isFullscreen, false);

    ফেরত 0;
}

স্থির EM_BOOL Emscripten_HandleFullscreenChangeGlobal(পূর্ণসংখ্যা eventType, ধ্রুবক EmscriptenFullscreenChangeEvent *fullscreenChangeEvent, শূন্য *user_তথ্য)
{
    SDL_VideoDevice *device = user_তথ্য;
    SDL_Window *window = ফাঁকা;
    জন্য (window = device->windows; window != ফাঁকা; window = window->পরবর্তী) {
        ধ্রুবক অক্ষর *canvas_id = window->internal->canvas_id;
        যদি (*canvas_id == '#') {
            canvas_id++;
        }
        যদি (SDL_strcmp(fullscreenChangeEvent->id, canvas_id) == 0) {
            বিরতি;  // this is the window.
        }
    }

    যদি (window) {
        ফেরত Emscripten_HandleFullscreenChange(eventType, fullscreenChangeEvent, window->internal);
    }

    ফেরত EM_FALSE;
}

স্থির EM_BOOL Emscripten_HandleResize(পূর্ণসংখ্যা eventType, ধ্রুবক EmscriptenUiEvent *uiEvent, শূন্য *user_তথ্য)
{
    SDL_Window_তথ্য *window_তথ্য_2 = user_তথ্য;

    bool force = false;

    // update pixel ratio
    যদি (window_তথ্য_2->window->flags & SDL_WINDOW_উপরের_PIXEL_DENSITY) {
        যদি (window_তথ্য_2->pixel_ratio != emscripten_get_device_pixel_ratio()) {
            window_তথ্য_2->pixel_ratio = emscripten_get_device_pixel_ratio();
            force = true;
        }
    }

    ধ্রুবক bool fill_document = (Emscripten_fill_document_window == window_তথ্য_2->window);
    ধ্রুবক bool fullscreen = (window_তথ্য_2->window->flags & SDL_WINDOW_FULLSCREEN) != 0;  // fullscreen windows can resize on Emscripten, and the canvas should fill it.
    ধ্রুবক bool resizable = (window_তথ্য_2->window->flags & SDL_WINDOW_RESIZABLE) != 0;
    যদি (fill_document || fullscreen || resizable) {
        দ্বিগুণ w, h;
        যদি (fill_document || fullscreen) {
            w = (দ্বিগুণ) uiEvent->windowInnerWidth;
            h = (দ্বিগুণ) uiEvent->windowInnerHeight;
        } অন্যথা {
            SDL_assert(window_তথ্য_2->window->flags & SDL_WINDOW_RESIZABLE);
            w = window_তথ্য_2->window->w;
            h = window_তথ্য_2->window->h;
            // this will only work if the canvas size is set through css
            যদি (window_তথ্য_2->external_আকার) {
                emscripten_get_element_css_আকার(window_তথ্য_2->canvas_id, &w, &h);
            }
        }

        emscripten_set_canvas_element_আকার(window_তথ্য_2->canvas_id, SDL_lroundf(w * window_তথ্য_2->pixel_ratio), SDL_lroundf(h * window_তথ্য_2->pixel_ratio));

        // set_canvas_size unsets this
        যদি (!window_তথ্য_2->external_আকার && window_তথ্য_2->pixel_ratio != 1.0f) {
            emscripten_set_element_css_আকার(window_তথ্য_2->canvas_id, w, h);
        }

        যদি (force) {
            // force the event to trigger, so pixel ratio changes can be handled
            window_তথ্য_2->window->w = 0;
            window_তথ্য_2->window->h = 0;
        }

        SDL_SendWindowEvent(window_তথ্য_2->window, SDL_EVENT_WINDOW_RESIZED, SDL_lroundf(w), SDL_lroundf(h));
    }

    ফেরত 0;
}

স্থির EM_BOOL Emscripten_HandleResizeGlobal(পূর্ণসংখ্যা eventType, ধ্রুবক EmscriptenUiEvent *uiEvent, শূন্য *user_তথ্য)
{
    SDL_VideoDevice *device = user_তথ্য;
    bool prevent_default = false;
    SDL_Window *window;

    জন্য (window = device->windows; window; window = window->পরবর্তী) {
        prevent_default |= Emscripten_HandleResize(eventType, uiEvent, window->internal);
    }

    ফেরত prevent_default;
}

EM_BOOL
Emscripten_HandleCanvasResize(পূর্ণসংখ্যা eventType, ধ্রুবক শূন্য *reserved, শূন্য *user_তথ্য)
{
    // this is used during fullscreen changes
    SDL_Window_তথ্য *window_তথ্য_2 = user_তথ্য;

    যদি (window_তথ্য_2->fullscreen_resize) {
        দ্বিগুণ css_w, css_h;
        emscripten_get_element_css_আকার(window_তথ্য_2->canvas_id, &css_w, &css_h);
        SDL_SendWindowEvent(window_তথ্য_2->window, SDL_EVENT_WINDOW_RESIZED, SDL_lroundf(css_w), SDL_lroundf(css_h));
    }

    ফেরত 0;
}

স্থির EM_BOOL Emscripten_HandleVisibilityChange(পূর্ণসংখ্যা eventType, ধ্রুবক EmscriptenVisibilityChangeEvent *visEvent, শূন্য *user_তথ্য)
{
    SDL_Window_তথ্য *window_তথ্য_2 = user_তথ্য;
    SDL_SendWindowEvent(window_তথ্য_2->window, visEvent->hidden ? SDL_EVENT_WINDOW_HIDDEN : SDL_EVENT_WINDOW_SHOWN, 0, 0);
    ফেরত 0;
}

স্থির ধ্রুবক অক্ষর *Emscripten_HandleBeforeUnload(পূর্ণসংখ্যা eventType, ধ্রুবক শূন্য *reserved, শূন্য *user_তথ্য)
{
    /* This event will need to be handled synchronously, e.g. using
       SDL_AddEventWatch, as the page is being closed *now*. */
    SDL_SendQuit();  // the app might see this if they installed an event watcher.
    SDL_OnApplicationWillTerminate();  // calls SDL_AppQuit if appropriate, etc.
    ফেরত ""; // don't trigger confirmation dialog
}

স্থির EM_BOOL Emscripten_HandleOrientationChange(পূর্ণসংখ্যা eventType, ধ্রুবক EmscriptenOrientationChangeEvent *orientationChangeEvent, শূন্য *user_তথ্য)
{
    SDL_DisplayOrientation orientation;
    নির্বাচন (orientationChangeEvent->orientation_সূচক) {
        #define CHECK_ORIENTATION(emsdk, sdl) ক্ষেত্র EMSCRIPTEN_ORIENTATION_##emsdk: orientation = SDL_ORIENTATION_##sdl; বিরতি
        CHECK_ORIENTATION(LANDSCAPE_PRIMARY, LANDSCAPE);
        CHECK_ORIENTATION(LANDSCAPE_SECONDARY, LANDSCAPE_FLIPPED);
        CHECK_ORIENTATION(PORTRAIT_PRIMARY, PORTRAIT);
        CHECK_ORIENTATION(PORTRAIT_SECONDARY, PORTRAIT_FLIPPED);
        #undef CHECK_ORIENTATION
        পূর্বনির্ধারিত: orientation = SDL_ORIENTATION_UNKNOWN; বিরতি;
    }

    SDL_Window_তথ্য *window_তথ্য_2 = (SDL_Window_তথ্য *) user_তথ্য;
    SDL_SendDisplayEvent(SDL_GetVideoDisplayForWindow(window_তথ্য_2->window), SDL_EVENT_DISPLAY_ORIENTATION, orientation, 0);

    // fake a UI event so we can tell the app the canvas might have resized.
    EmscriptenUiEvent uiEvent;
    SDL_zero(uiEvent);
    uiEvent.documentBodyClientWidth = MAIN_THREAD_EM_ASM_INT( { ফেরত document.body.clientWidth; } );
    uiEvent.documentBodyClientHeight = MAIN_THREAD_EM_ASM_INT( { ফেরত document.body.clientHeight; } );
    uiEvent.windowInnerWidth = MAIN_THREAD_EM_ASM_INT( { ফেরত window.innerWidth; } );
    uiEvent.windowInnerHeight = MAIN_THREAD_EM_ASM_INT( { ফেরত window.innerHeight; } );
    uiEvent.windowOuterWidth = MAIN_THREAD_EM_ASM_INT( { ফেরত window.outerWidth; } );
    uiEvent.windowOuterHeight = MAIN_THREAD_EM_ASM_INT( { ফেরত window.outerHeight; } );
    uiEvent.scroll_শীর্ষ = MAIN_THREAD_EM_ASM_INT( { ফেরত window.pageXOffset; } );
    uiEvent.scroll_বাম = MAIN_THREAD_EM_ASM_INT( { ফেরত window.pageYOffset; } );
    Emscripten_HandleResize(EMSCRIPTEN_EVENT_RESIZE, &uiEvent, user_তথ্য);

    ফেরত 0;
}

// IF YOU CHANGE THIS STRUCTURE, YOU NEED TO UPDATE THE JAVASCRIPT THAT FILLS IT IN: SDL3.makePointerEventCStruct, below.
#define PTRTYPE_MOUSE 1
#define PTRTYPE_TOUCH 2
#define PTRTYPE_PEN 3
প্রকারলেখ কাঠামো Emscripten_PointerEvent
{
    পূর্ণসংখ্যা pointer_type;
    পূর্ণসংখ্যা pointerid;
    পূর্ণসংখ্যা button;
    পূর্ণসংখ্যা buttons;
    পূর্ণসংখ্যা down;
    দশমিক movementX;
    দশমিক movementY;
    দশমিক targetX;
    দশমিক targetY;
    দশমিক pressure;
    দশমিক tangential_pressure;
    দশমিক tiltx;
    দশমিক tilty;
    দশমিক rotation;
} Emscripten_PointerEvent;

স্থির শূন্য Emscripten_HandleMouseButton(SDL_Window_তথ্য *window_তথ্য_2, ধ্রুবক Emscripten_PointerEvent *event)
{
    Uint8 sdl_button;
    bool down = false;
    নির্বাচন (event->button) {
        #define CHECK_MOUSE_BUTTON(jsbutton, downflag, sdlbutton) ক্ষেত্র jsbutton: sdl_button = SDL_BUTTON_##sdlbutton; down = (event->down != 0) || ((event->buttons & downflag) != 0); বিরতি
        CHECK_MOUSE_BUTTON(0, 1, বাম_2);
        CHECK_MOUSE_BUTTON(1, 4, মধ্য_2);
        CHECK_MOUSE_BUTTON(2, 2, ডান_2);
        CHECK_MOUSE_BUTTON(3, 8, X1);
        CHECK_MOUSE_BUTTON(4, 16, X2);
        #undef CHECK_MOUSE_BUTTON
        পূর্বনির্ধারিত: sdl_button = 0; বিরতি;
    }

    যদি (sdl_button) {
        ধ্রুবক SDL_Mouse *mouse = SDL_GetMouse();
        SDL_assert(mouse != ফাঁকা);

        যদি (down) {
            যদি (mouse->relative_mode && !window_তথ্য_2->has_pointer_lock) {
                emscripten_request_pointerlock(window_তথ্য_2->canvas_id, 0); // try to regrab lost pointer lock.
            }
        }

        SDL_SendMouseButton(0, window_তথ্য_2->window, SDL_DEFAULT_MOUSE_ID, sdl_button, down);

        // We have an imaginary mouse capture, because we need SDL to not drop our imaginary mouse focus when we leave the canvas.
        যদি (mouse->auto_capture) {
            যদি (SDL_GetMouseState(ফাঁকা, ফাঁকা) != 0) {
                window_তথ্য_2->window->flags |= SDL_WINDOW_MOUSE_CAPTURE;
            } অন্যথা {
                window_তথ্য_2->window->flags &= ~SDL_WINDOW_MOUSE_CAPTURE;
            }
        }

        যদি (!down && window_তথ্য_2->mouse_focus_loss_pending) {
            window_তথ্য_2->mouse_focus_loss_pending = (window_তথ্য_2->window->flags & SDL_WINDOW_MOUSE_CAPTURE) != 0;
            যদি (!window_তথ্য_2->mouse_focus_loss_pending) {
                SDL_SetMouseFocus(ফাঁকা);
            }
        }
    }
}

স্থির শূন্য Emscripten_UpdateMouseFromEvent(SDL_Window_তথ্য *window_তথ্য_2, ধ্রুবক Emscripten_PointerEvent *event)
{
    SDL_assert(event->pointer_type == PTRTYPE_MOUSE);

    // Hidden windows (e.g. a shared GL-context window) may share the DOM canvas with the
    // visible window. Their pointer-event listeners would otherwise fire alongside the
    // visible window's, fighting over `mouse->focus` and producing events tagged with the
    // hidden window's ID -- causing downstream consumers that key by window ID to silently
    // drop them. Hidden windows shouldn't take part in user-input dispatch.
    যদি (window_তথ্য_2->window->flags & SDL_WINDOW_HIDDEN) {
        ফেরত;
    }

    // rescale (in case canvas is being scaled)
    দ্বিগুণ client_w, client_h;
    emscripten_get_element_css_আকার(window_তথ্য_2->canvas_id, &client_w, &client_h);
    ধ্রুবক দ্বিগুণ xscale = window_তথ্য_2->window->w / client_w;
    ধ্রুবক দ্বিগুণ yscale = window_তথ্য_2->window->h / client_h;

    ধ্রুবক bool isPointerLocked = window_তথ্য_2->has_pointer_lock;
    দশমিক mx, my;
    যদি (isPointerLocked) {
        mx = (দশমিক)(event->movementX * xscale);
        my = (দশমিক)(event->movementY * yscale);
    } অন্যথা {
        mx = (দশমিক)(event->targetX * xscale);
        my = (দশমিক)(event->targetY * yscale);
    }

    SDL_SendMouseMotion(0, window_তথ্য_2->window, SDL_DEFAULT_MOUSE_ID, isPointerLocked, mx, my);

    Emscripten_HandleMouseButton(window_তথ্য_2, event);
}

স্থির শূন্য Emscripten_UpdateTouchFromEvent(SDL_Window_তথ্য *window_তথ্য_2, ধ্রুবক Emscripten_PointerEvent *event)
{
    SDL_assert(event->pointer_type == PTRTYPE_TOUCH);

    ধ্রুবক SDL_TouchID deviceId = 1;
    যদি (SDL_AddTouch(deviceId, SDL_TOUCH_DEVICE_DIRECT, "") < 0) {
        ফেরত;
    }

    দ্বিগুণ client_w, client_h;
    emscripten_get_element_css_আকার(window_তথ্য_2->canvas_id, &client_w, &client_h);

    ধ্রুবক SDL_FingerID id = event->pointerid + 1;
    দশমিক x, y;
    যদি (client_w <= 1) {
        x = 0.5f;
    } অন্যথা {
        x = event->targetX / (client_w - 1);
    }
    যদি (client_h <= 1) {
        y = 0.5f;
    } অন্যথা {
        y = event->targetY / (client_h - 1);
    }

    ধ্রুবক bool down = (event->buttons & 1) != 0;
    যদি (event->button == 0) {  // touch is starting or ending if this is zero (-1 means "no change").
        যদি (down) {
            SDL_SendTouch(0, deviceId, id, window_তথ্য_2->window, SDL_EVENT_FINGER_DOWN, x, y, 1.0f);
        }
    }

    SDL_SendTouchMotion(0, deviceId, id, window_তথ্য_2->window, x, y, 1.0f);

    যদি (event->button == 0) {  // touch is starting or ending if this is zero (-1 means "no change").
        যদি (!down) {
            SDL_SendTouch(0, deviceId, id, window_তথ্য_2->window, SDL_EVENT_FINGER_UP, x, y, 1.0f);
        }
    }
}

স্থির শূন্য Emscripten_UpdatePenFromEvent(SDL_Window_তথ্য *window_তথ্য_2, ধ্রুবক Emscripten_PointerEvent *event)
{
    SDL_assert(event->pointer_type == PTRTYPE_PEN);
    ধ্রুবক SDL_PenID pen = SDL_FindPenByHandle((শূন্য *) (size_t) 1);   // something > 0 for the single pen handle.
    যদি (pen) {
        // rescale (in case canvas is being scaled)
        দ্বিগুণ client_w, client_h;
        emscripten_get_element_css_আকার(window_তথ্য_2->canvas_id, &client_w, &client_h);
        ধ্রুবক দ্বিগুণ xscale = window_তথ্য_2->window->w / client_w;
        ধ্রুবক দ্বিগুণ yscale = window_তথ্য_2->window->h / client_h;

        ধ্রুবক bool isPointerLocked = window_তথ্য_2->has_pointer_lock;
        দশমিক mx, my;
        যদি (isPointerLocked) {
            mx = (দশমিক)(event->movementX * xscale);
            my = (দশমিক)(event->movementY * yscale);
        } অন্যথা {
            mx = (দশমিক)(event->targetX * xscale);
            my = (দশমিক)(event->targetY * yscale);
        }

        SDL_SendPenMotion(0, pen, window_তথ্য_2->window, mx, my);

        যদি (event->button == 0) {  // pen touch
            bool down = ((event->buttons & 1) != 0);
            SDL_SendPenTouch(0, pen, window_তথ্য_2->window, false, down);
        } অন্যথা যদি (event->button == 5) {  // eraser touch...? Not sure if this is right...
            bool down = ((event->buttons & 32) != 0);
            SDL_SendPenTouch(0, pen, window_তথ্য_2->window, true, down);
        } অন্যথা যদি (event->button == 1) {
            bool down = ((event->buttons & 4) != 0);
            SDL_SendPenButton(0, pen, window_তথ্য_2->window, 2, down);
        } অন্যথা যদি (event->button == 2) {
            bool down = ((event->buttons & 2) != 0);
            SDL_SendPenButton(0, pen, window_তথ্য_2->window, 1, down);
        }

        SDL_SendPenAxis(0, pen, window_তথ্য_2->window, SDL_PEN_AXIS_PRESSURE, event->pressure);
        SDL_SendPenAxis(0, pen, window_তথ্য_2->window, SDL_PEN_AXIS_TANGENTIAL_PRESSURE, event->tangential_pressure);
        SDL_SendPenAxis(0, pen, window_তথ্য_2->window, SDL_PEN_AXIS_XTILT, event->tiltx);
        SDL_SendPenAxis(0, pen, window_তথ্য_2->window, SDL_PEN_AXIS_YTILT, event->tilty);
        SDL_SendPenAxis(0, pen, window_তথ্য_2->window, SDL_PEN_AXIS_ROTATION, event->rotation);
    }
}

স্থির শূন্য Emscripten_UpdatePointerFromEvent(SDL_Window_তথ্য *window_তথ্য_2, ধ্রুবক Emscripten_PointerEvent *event)
{
    SDL_assert(event != ফাঁকা);
    যদি (event->pointer_type == PTRTYPE_MOUSE) {
        Emscripten_UpdateMouseFromEvent(window_তথ্য_2, event);
    } অন্যথা যদি (event->pointer_type == PTRTYPE_TOUCH) {
        Emscripten_UpdateTouchFromEvent(window_তথ্য_2, event);
    } অন্যথা যদি (event->pointer_type == PTRTYPE_PEN) {
        Emscripten_UpdatePenFromEvent(window_তথ্য_2, event);
    } অন্যথা {
        SDL_assert(!"Unexpected pointer event type");
    }
}

স্থির শূন্য Emscripten_HandleMouseFocus(SDL_Window_তথ্য *window_তথ্য_2, ধ্রুবক Emscripten_PointerEvent *event, bool isenter)
{
    SDL_assert(event->pointer_type == PTRTYPE_MOUSE);

    // Hidden windows shouldn't ever become the mouse-focus target.
    যদি (window_তথ্য_2->window->flags & SDL_WINDOW_HIDDEN) {
        ফেরত;
    }

    ধ্রুবক bool isPointerLocked = window_তথ্য_2->has_pointer_lock;

    যদি (!isPointerLocked) {
        // rescale (in case canvas is being scaled)
        দশমিক mx, my;
        দ্বিগুণ client_w, client_h;
        emscripten_get_element_css_আকার(window_তথ্য_2->canvas_id, &client_w, &client_h);

        mx = (দশমিক)(event->targetX * (window_তথ্য_2->window->w / client_w));
        my = (দশমিক)(event->targetY * (window_তথ্য_2->window->h / client_h));
        SDL_SendMouseMotion(0, window_তথ্য_2->window, SDL_GLOBAL_MOUSE_ID, isPointerLocked, mx, my);
    }

    যদি (isenter && window_তথ্য_2->mouse_focus_loss_pending) {
        window_তথ্য_2->mouse_focus_loss_pending = false;  // just drop the state, but don't send the enter event.
    } অন্যথা যদি (!isenter && (window_তথ্য_2->window->flags & SDL_WINDOW_MOUSE_CAPTURE)) {
        window_তথ্য_2->mouse_focus_loss_pending = true;  // waiting on a mouse button to let go before we send the mouse focus update.
    } অন্যথা {
        SDL_SetMouseFocus(isenter ? window_তথ্য_2->window : ফাঁকা);
    }
}

স্থির শূন্য Emscripten_HandlePenEnter(SDL_Window_তথ্য *window_তথ্য_2, ধ্রুবক Emscripten_PointerEvent *event)
{
    SDL_assert(event->pointer_type == PTRTYPE_PEN);

    // event->pointerid is one continuous interaction; it doesn't necessarily track a specific tool over time, like the same finger's ID changed on each new touch event.
    // as such, we only expose a single pen, and when the touch ends, we say it lost proximity instead of the calling SDL_RemovePenDevice().

    SDL_PenID pen = SDL_FindPenByHandle((শূন্য *) (size_t) 1);  // something > 0 for the single pen handle.
    যদি (pen) {
        SDL_SendPenProximity(0, pen, window_তথ্য_2->window, true, true);
    } অন্যথা {
        // Web browsers offer almost none of this information as specifics, but can without warning offer any of these specific things.
        SDL_PenInfo peninfo;
        SDL_zero(peninfo);
        peninfo.capabilities = SDL_PEN_CAPABILITY_PRESSURE | SDL_PEN_CAPABILITY_ROTATION | SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT | SDL_PEN_CAPABILITY_TANGENTIAL_PRESSURE | SDL_PEN_CAPABILITY_ERASER;
        peninfo.max_tilt = 90.0f;
        peninfo.অঙ্ক_buttons = 2;
        peninfo.subtype = SDL_PEN_TYPE_PEN;
        SDL_AddPenDevice(0, ফাঁকা, window_তথ্য_2->window, &peninfo, (শূন্য *) (size_t) 1, true);
    }

    Emscripten_UpdatePenFromEvent(window_তথ্য_2, event);
}

EMSCRIPTEN_KEEPALIVE শূন্য Emscripten_HandlePointerEnter(SDL_Window_তথ্য *window_তথ্য_2, ধ্রুবক Emscripten_PointerEvent *event)
{
    SDL_assert(event != ফাঁকা);
    যদি (event->pointer_type == PTRTYPE_MOUSE) {
        Emscripten_HandleMouseFocus(window_তথ্য_2, event, true);
    } অন্যথা যদি (event->pointer_type == PTRTYPE_PEN) {
        Emscripten_HandlePenEnter(window_তথ্য_2, event);
    } অন্যথা যদি (event->pointer_type == PTRTYPE_TOUCH) {
        // do nothing.
    } অন্যথা {
        SDL_assert(!"Unexpected pointer event type");
    }
}

স্থির শূন্য Emscripten_HandlePenLeave(SDL_Window_তথ্য *window_তথ্য_2, ধ্রুবক Emscripten_PointerEvent *event)
{
    ধ্রুবক SDL_PenID pen = SDL_FindPenByHandle((শূন্য *) (size_t) 1);   // something > 0 for the single pen handle.
    যদি (pen) {
        Emscripten_UpdatePointerFromEvent(window_তথ্য_2, event);  // last data updates?
        SDL_SendPenProximity(0, pen, window_তথ্য_2->window, false, false);
    }
}

স্থির শূন্য Emscripten_HandleTouchCancel(SDL_Window_তথ্য *window_তথ্য_2, ধ্রুবক Emscripten_PointerEvent *event)
{
    SDL_assert(event->pointer_type == PTRTYPE_TOUCH);

    ধ্রুবক SDL_TouchID deviceId = 1;
    যদি (SDL_AddTouch(deviceId, SDL_TOUCH_DEVICE_DIRECT, "") < 0) {
        ফেরত;
    }

    দ্বিগুণ client_w, client_h;
    emscripten_get_element_css_আকার(window_তথ্য_2->canvas_id, &client_w, &client_h);

    ধ্রুবক SDL_FingerID id = event->pointerid + 1;
    দশমিক x, y;
    যদি (client_w <= 1) {
        x = 0.5f;
    } অন্যথা {
        x = event->targetX / (client_w - 1);
    }
    যদি (client_h <= 1) {
        y = 0.5f;
    } অন্যথা {
        y = event->targetY / (client_h - 1);
    }

    SDL_SendTouch(0, deviceId, id, window_তথ্য_2->window, SDL_EVENT_FINGER_CANCELED, x, y, 1.0f);
}

EMSCRIPTEN_KEEPALIVE শূন্য Emscripten_HandlePointerLeave(SDL_Window_তথ্য *window_তথ্য_2, ধ্রুবক Emscripten_PointerEvent *event)
{
    SDL_assert(event != ফাঁকা);
    যদি (event->pointer_type == PTRTYPE_MOUSE) {
        Emscripten_HandleMouseFocus(window_তথ্য_2, event, false);
    } অন্যথা যদি (event->pointer_type == PTRTYPE_PEN) {
        Emscripten_HandlePenLeave(window_তথ্য_2, event);
    } অন্যথা যদি (event->pointer_type == PTRTYPE_TOUCH) {
        Emscripten_HandleTouchCancel(window_তথ্য_2, event);
    } অন্যথা {
        SDL_assert(!"Unexpected pointer event type");
    }
}

EMSCRIPTEN_KEEPALIVE শূন্য Emscripten_HandlePointerGeneric(SDL_Window_তথ্য *window_তথ্য_2, ধ্রুবক Emscripten_PointerEvent *event)
{
    SDL_assert(event != ফাঁকা);
    Emscripten_UpdatePointerFromEvent(window_তথ্য_2, event);
}

স্থির শূন্য Emscripten_prep_pointer_event_callbacks(শূন্য)
{
    MAIN_THREAD_EM_ASM({
        var SDL3 = Module['SDL3'];

        যদি (SDL3.makePointerEventCStruct === undefined) {
            SDL3.makePointerEventCStruct = function(বাম, শীর্ষ, event) {
                var ptrtype = 0;
                যদি (event.pointerType == "mouse") {
                    ptrtype = 1;
                } অন্যথা যদি (event.pointerType == "touch") {
                    ptrtype = 2;
                } অন্যথা যদি (event.pointerType == "pen") {
                    ptrtype = 3;
                } অন্যথা {
                    ফেরত 0;
                }

                var ptr = _SDL_malloc($0);
                যদি (ptr != 0) {
                    var idx = SDL3.CPtr_To_Heap32_সূচক(ptr);
                    HEAP32[idx++] = ptrtype;
                    HEAP32[idx++] = event.pointerId;
                    HEAP32[idx++] = (typeof(event.button) !== "undefined") ? event.button : -1;
                    HEAP32[idx++] = event.buttons;
                    HEAP32[idx++] = (event.type == "pointerdown") ? 1 : 0;
                    HEAPF32[idx++] = event.movementX;
                    HEAPF32[idx++] = event.movementY;
                    HEAPF32[idx++] = event.clientX - বাম;
                    HEAPF32[idx++] = event.clientY - শীর্ষ;
                    যদি (ptrtype == 3) {
                        HEAPF32[idx++] = event.pressure;
                        HEAPF32[idx++] = event.tangentialPressure;
                        HEAPF32[idx++] = event.tiltX;
                        HEAPF32[idx++] = event.tiltY;
                        HEAPF32[idx++] = event.twist;
                    }
                }
                ফেরত ptr;
            };
        }
    }, আকার (Emscripten_PointerEvent));
}

স্থির শূন্য Emscripten_set_pointer_event_callbacks(SDL_Window_তথ্য *তথ্য)
{
    Emscripten_prep_pointer_event_callbacks();

    MAIN_THREAD_EM_ASM({
        var target = document.querySelector(UTF8ToString($1));
        যদি (target) {
            var SDL3 = Module['SDL3'];
            var তথ্য = $0;
            target.sdlEventHandlerPointerEnter = function(event) {
                var rect = target.getBoundingClientRect();
                var d = SDL3.makePointerEventCStruct(rect.বাম, rect.শীর্ষ, event);
                যদি (d != 0)
                {
                    _Emscripten_HandlePointerEnter(SDL3.JSVarToCPtr(তথ্য), d);
                    _SDL_free(d);
                }
            };
            target.sdlEventHandlerPointerLeave = function(event) {
                var rect = target.getBoundingClientRect();
                var d = SDL3.makePointerEventCStruct(rect.বাম, rect.শীর্ষ, event);
                যদি (d != 0)
                {
                    _Emscripten_HandlePointerLeave(SDL3.JSVarToCPtr(তথ্য), d);
                    _SDL_free(d);
                }
            };
            target.sdlEventHandlerPointerGeneric = function(event) {
                var rect = target.getBoundingClientRect();
                var d = SDL3.makePointerEventCStruct(rect.বাম, rect.শীর্ষ, event);
                যদি (d != 0)
                {
                    _Emscripten_HandlePointerGeneric(SDL3.JSVarToCPtr(তথ্য), d);
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
    }, তথ্য, তথ্য->canvas_id);
}

স্থির শূন্য Emscripten_unset_pointer_event_callbacks(SDL_Window_তথ্য *তথ্য)
{
    MAIN_THREAD_EM_ASM({
        var target = document.querySelector(UTF8ToString($0));
        যদি (target) {
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
    }, তথ্য->canvas_id);
}

EMSCRIPTEN_KEEPALIVE শূন্য Emscripten_HandleMouseButtonUpGlobal(SDL_VideoDevice *device, ধ্রুবক Emscripten_PointerEvent *event)
{
    SDL_assert(device != ফাঁকা);
    SDL_assert(event != ফাঁকা);
    যদি (event->pointer_type == PTRTYPE_MOUSE) {
        জন্য (SDL_Window *window = device->windows; window; window = window->পরবর্তী) {
            Emscripten_HandleMouseButton(window->internal, event);
        }
    }
}

স্থির শূন্য Emscripten_set_global_mouseup_callback(SDL_VideoDevice *device)
{
    Emscripten_prep_pointer_event_callbacks();

    MAIN_THREAD_EM_ASM({
        var target = document;
        যদি (target) {
            target.sdlEventHandlerMouseButtonUpGlobal = function(event) {
                var SDL3 = Module['SDL3'];
                var d = SDL3.makePointerEventCStruct(0, 0, event);
                যদি (d != 0)
                {
                    _Emscripten_HandleMouseButtonUpGlobal(SDL3.JSVarToCPtr($0), d);
                    _SDL_free(d);
                }
            };
            target.addEventListener("pointerup", target.sdlEventHandlerMouseButtonUpGlobal);
        }
    }, device);
}

স্থির শূন্য Emscripten_unset_global_mouseup_callback(SDL_VideoDevice *device)
{
    MAIN_THREAD_EM_ASM({
        var target = document;
        যদি (target) {
            target.removeEventListener("pointerup", target.sdlEventHandlerMouseButtonUpGlobal);
            target.sdlEventHandlerMouseButtonUpGlobal = undefined;
        }
    });
}

// IF YOU CHANGE THIS STRUCTURE, YOU NEED TO UPDATE THE JAVASCRIPT THAT FILLS IT IN: makeDropEventCStruct, below.
প্রকারলেখ কাঠামো Emscripten_DropEvent
{
    পূর্ণসংখ্যা x;
    পূর্ণসংখ্যা y;
} Emscripten_DropEvent;

EMSCRIPTEN_KEEPALIVE শূন্য Emscripten_SendDragEvent(SDL_Window_তথ্য *window_তথ্য_2, ধ্রুবক Emscripten_DropEvent *event)
{
    SDL_SendDropPosition(window_তথ্য_2->window, event->x, event->y);
}

EMSCRIPTEN_KEEPALIVE শূন্য Emscripten_SendDragCompleteEvent(SDL_Window_তথ্য *window_তথ্য_2)
{
    SDL_SendDropComplete(window_তথ্য_2->window);
}

EMSCRIPTEN_KEEPALIVE শূন্য Emscripten_SendDragTextEvent(SDL_Window_তথ্য *window_তথ্য_2, অক্ষর *text)
{
    SDL_SendDropText(window_তথ্য_2->window, text);
}

EMSCRIPTEN_KEEPALIVE শূন্য Emscripten_SendDragFileEvent(SDL_Window_তথ্য *window_তথ্য_2, অক্ষর *filename)
{
    SDL_SendDropFile(window_তথ্য_2->window, ফাঁকা, filename);
}

EM_JS_DEPS(dragndrop, "$writeArrayToMemory");

স্থির শূন্য Emscripten_set_drag_event_callbacks(SDL_Window_তথ্য *তথ্য)
{
    MAIN_THREAD_EM_ASM({
        var target = document.querySelector(UTF8ToString($1));
        যদি (target) {
            var তথ্য = $0;
            var SDL3 = Module['SDL3'];

            var makeDropEventCStruct = function(event) {
                var ptr = 0;
                ptr = _SDL_malloc($2);
                যদি (ptr != 0) {
                    var idx = ptr >> 2;
                    var rect = target.getBoundingClientRect();
                    HEAP32[idx++] = event.clientX - rect.বাম;
                    HEAP32[idx++] = event.clientY - rect.শীর্ষ;
                }
                ফেরত ptr;
            };

            SDL3.eventHandlerDropDragover = function(event) {
                event.preventDefault();
                var d = makeDropEventCStruct(event); যদি (d != 0) { _Emscripten_SendDragEvent(তথ্য, d); _SDL_free(d); }
            };
            target.addEventListener("dragover", SDL3.eventHandlerDropDragover);

            SDL3.drop_গুনতি = 0;

            // FS.* functions throw exceptions when there are errors (such as the temp dir already existing),
            //  but we ignore all of these in a catch handler; you just won't get the drop event if there's a problem.
            try { FS.mkdir("/tmp/filedrop"); } catch (e) {}

            SDL3.eventHandlerDropDrop = function(event) {
                event.preventDefault();
                যদি (event.তথ্য_Transfer.types.includes("text/plain")) {
                    let plain_text = stringToNewUTF8(event.তথ্য_Transfer.get_তথ্য("text/plain"));
                    _Emscripten_SendDragTextEvent(তথ্য, plain_text);
                    _Emscripten_force_free(plain_text);
                } অন্যথা যদি (event.তথ্য_Transfer.types.includes("Files")) {
                    let files_read = 0;
                    ধ্রুবক files_to_read = event.তথ্য_Transfer.files.দৈর্ঘ্য;
                    জন্য (let i = 0; i < files_to_read; i++) {
                        ধ্রুবক file = event.তথ্য_Transfer.files.item(i);
                        ধ্রুবক file_reader = new FileReader();
                        file_reader.read_As_Array_বাফার(file);
                        file_reader.onload = function(event) {
                            ধ্রুবক fs_dropdir = `/tmp/filedrop/${SDL3.drop_গুনতি}`;
                            SDL3.drop_গুনতি += 1;

                            ধ্রুবক fs_filepath = `${fs_dropdir}/${file.name}`;
                            ধ্রুবক c_fs_filepath = stringToNewUTF8(fs_filepath);
                            ধ্রুবক contents_array8 = new Uint8Array(event.target.ফলাফল);

                            try {
                                FS.mkdir(fs_dropdir);
                                var stream = FS.open(fs_filepath, "w");
                                FS.লিখ(stream, contents_array8, 0, contents_array8.দৈর্ঘ্য, 0);
                                FS.close(stream);
                                _Emscripten_SendDragFileEvent(তথ্য, c_fs_filepath);
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
                        যদি (files_read === files_to_read) {
                            _Emscripten_SendDragCompleteEvent(তথ্য);
                        }
                    }
                }
                _Emscripten_SendDragCompleteEvent(তথ্য);
            };
            target.addEventListener("drop", SDL3.eventHandlerDropDrop);

            SDL3.eventHandlerDropDragend = function(event) {
                event.preventDefault();
                _Emscripten_SendDragCompleteEvent(তথ্য);
            };
            target.addEventListener("dragend", SDL3.eventHandlerDropDragend);
            target.addEventListener("dragleave", SDL3.eventHandlerDropDragend);
        }
    }, তথ্য, তথ্য->canvas_id, আকার (Emscripten_DropEvent));
}

স্থির শূন্য Emscripten_unset_drag_event_callbacks(SDL_Window_তথ্য *তথ্য)
{
    MAIN_THREAD_EM_ASM({
        var target = document.querySelector(UTF8ToString($0));
        যদি (target) {
            var SDL3 = Module['SDL3'];
            target.removeEventListener("dragleave", SDL3.eventHandlerDropDragend);
            target.removeEventListener("dragend", SDL3.eventHandlerDropDragend);
            target.removeEventListener("drop", SDL3.eventHandlerDropDrop);
            SDL3.drop_গুনতি = undefined;

            function recursive_remove(dirpath) {
                FS.readdir(dirpath).forEach((filename) => {
                    ধ্রুবক p = `${dirpath}/${filename}`;
                    ধ্রুবক p_s = FS.stat(p);
                    যদি (FS.isFile(p_s.mode)) {
                        FS.unlink(p);
                    } অন্যথা যদি (FS.isDir(p)) {
                        recursive_remove(p);
                    }
                });
                FS.rmdir(dirpath);
            }("/tmp/filedrop");

            FS.rmdir("/tmp/filedrop");
            target.removeEventListener("dragover", SDL3.eventHandlerDropDragover);
            SDL3.eventHandlerDropDragover = undefined;
            SDL3.eventHandlerDropDrop = undefined;
            SDL3.eventHandlerDropDragend = undefined;
        }
    }, তথ্য->canvas_id);
}

স্থির ধ্রুবক অক্ষর *Emscripten_GetKeyboardTargetElement(ধ্রুবক অক্ষর *target)
{
    যদি (SDL_strcmp(target, "#none") == 0) {
        ফেরত ফাঁকা;
    } অন্যথা যদি (SDL_strcmp(target, "#window") == 0) {
        ফেরত EMSCRIPTEN_EVENT_TARGET_WINDOW;
    } অন্যথা যদি (SDL_strcmp(target, "#document") == 0) {
        ফেরত EMSCRIPTEN_EVENT_TARGET_DOCUMENT;
    } অন্যথা যদি (SDL_strcmp(target, "#screen") == 0) {
        ফেরত EMSCRIPTEN_EVENT_TARGET_SCREEN;
    }

    ফেরত target;
}

শূন্য Emscripten_RegisterGlobalEventHandlers(SDL_VideoDevice *device)
{
    Emscripten_set_global_mouseup_callback(device);

    emscripten_set_focus_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, device, 0, Emscripten_HandleFocus);
    emscripten_set_blur_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, device, 0, Emscripten_HandleFocus);

    emscripten_set_pointerlockchange_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, device, 0, Emscripten_HandlePointerLockChangeGlobal);

    emscripten_set_fullscreenchange_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, device, 0, Emscripten_HandleFullscreenChangeGlobal);

    emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, device, 0, Emscripten_HandleResizeGlobal);
}

শূন্য Emscripten_UnregisterGlobalEventHandlers(SDL_VideoDevice *device)
{
    Emscripten_unset_global_mouseup_callback(device);

    emscripten_set_focus_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, ফাঁকা, 0, ফাঁকা);
    emscripten_set_blur_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, ফাঁকা, 0, ফাঁকা);

    emscripten_set_pointerlockchange_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, ফাঁকা, 0, ফাঁকা);

    emscripten_set_fullscreenchange_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, ফাঁকা, 0, ফাঁকা);

    emscripten_set_resize_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, ফাঁকা, 0, ফাঁকা);
}

EMSCRIPTEN_KEEPALIVE শূন্য Emscripten_Handle_Lock_চাবিগুলি_Check(SDL_Window_তথ্য *window_তথ্য_2, EM_BOOL capslock, EM_BOOL numlock, EM_BOOL scrolllock)
{
    ধ্রুবক SDL_Keymod new_mods = (capslock ? SDL_KMOD_CAPS : 0) | (numlock ? SDL_KMOD_অঙ্ক : 0) | (scrolllock ? SDL_KMOD_SCROLL : 0);
    SDL_Keymod modstate = SDL_GetModState();
    যদি ((modstate & (SDL_KMOD_CAPS|SDL_KMOD_অঙ্ক|SDL_KMOD_SCROLL)) != new_mods) {
        modstate &= ~(SDL_KMOD_CAPS|SDL_KMOD_অঙ্ক|SDL_KMOD_SCROLL);
        modstate |= new_mods;
        SDL_SetModState(modstate);
    }
}

শূন্য Emscripten_RegisterEventHandlers(SDL_Window_তথ্য *তথ্য)
{
    ধ্রুবক অক্ষর *চাবি_Element;

    // There is only one window and that window is the canvas
    emscripten_set_wheel_callback(তথ্য->canvas_id, তথ্য, 0, Emscripten_HandleWheel);

    emscripten_set_orientationchange_callback(তথ্য, 0, Emscripten_HandleOrientationChange);

    চাবি_Element = Emscripten_GetKeyboardTargetElement(তথ্য->keyboard_element);
    যদি (চাবি_Element) {
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
        emscripten_set_keydown_callback(চাবি_Element, ফাঁকা, 0, ফাঁকা);
        emscripten_set_keyup_callback(চাবি_Element, ফাঁকা, 0, ফাঁকা);
        emscripten_set_keypress_callback(চাবি_Element, ফাঁকা, 0, ফাঁকা);

        MAIN_THREAD_EM_ASM_INT({
            var তথ্য = $0;
            // our keymod state can get confused in various ways (changed capslock when browser didn't have focus, etc), and you can't query the current
            //  state from the DOM, outside of a keyboard event, so catch keypresses globally and reset mod state if it's unexpectedly wrong. Best we can do.
            //  Note that this thing _only_ adjusts the lock keys if necessary; the real SDL keypress handling happens elsewhere.

            // Remove any prior listener first -- `addEventListener` does not deduplicate either.
            যদি (document.sdl_Event_Handler_Lock_চাবিগুলি_Check) {
                document.removeEventListener("keydown", document.sdl_Event_Handler_Lock_চাবিগুলি_Check);
            }

            document.sdl_Event_Handler_Lock_চাবিগুলি_Check = function(event) {
                // don't try to adjust the state on the actual lock key presses; the normal key handler will catch that and adjust.
                যদি ((event.চাবি != "CapsLock") && (event.চাবি != "NumLock") && (event.চাবি != "ScrollLock"))
                {
                    Emscripten_Handle_Lock_চাবিগুলি_Check_2(Module['SDL3'].JSVarToCPtr(তথ্য), event.getModifierState("CapsLock"), event.getModifierState("NumLock"), event.getModifierState("ScrollLock"));
                }
            };
            document.addEventListener("keydown", document.sdl_Event_Handler_Lock_চাবিগুলি_Check);
        }, তথ্য);
        emscripten_set_keydown_callback(চাবি_Element, তথ্য, 0, Emscripten_Handle_চাবি);
        emscripten_set_keyup_callback(চাবি_Element, তথ্য, 0, Emscripten_Handle_চাবি);
        emscripten_set_keypress_callback(চাবি_Element, তথ্য, 0, Emscripten_Handle_চাবি_Press);
    }

    emscripten_set_visibilitychange_callback(তথ্য, 0, Emscripten_HandleVisibilityChange);

    emscripten_set_beforeunload_callback(তথ্য, Emscripten_HandleBeforeUnload);

    // !!! FIXME: currently Emscripten doesn't have a Pointer Events functions like emscripten_set_*_callback, but we should use those when they do:
    // !!! FIXME:  https://github.com/emscripten-core/emscripten/issues/7278#issuecomment-2280024621
    Emscripten_set_pointer_event_callbacks(তথ্য);

    // !!! FIXME: currently Emscripten doesn't have a Drop Events functions like emscripten_set_*_callback, but we should use those when they do:
    Emscripten_set_drag_event_callbacks(তথ্য);
}

শূন্য Emscripten_UnregisterEventHandlers(SDL_Window_তথ্য *তথ্য)
{
    ধ্রুবক অক্ষর *চাবি_Element;

    // !!! FIXME: currently Emscripten doesn't have a Drop Events functions like emscripten_set_*_callback, but we should use those when they do:
    Emscripten_unset_drag_event_callbacks(তথ্য);

    // !!! FIXME: currently Emscripten doesn't have a Pointer Events functions like emscripten_set_*_callback, but we should use those when they do:
    // !!! FIXME:  https://github.com/emscripten-core/emscripten/issues/7278#issuecomment-2280024621
    Emscripten_unset_pointer_event_callbacks(তথ্য);

    // only works due to having one window
    emscripten_set_wheel_callback(তথ্য->canvas_id, ফাঁকা, 0, ফাঁকা);

    emscripten_set_orientationchange_callback(ফাঁকা, 0, ফাঁকা);

    চাবি_Element = Emscripten_GetKeyboardTargetElement(তথ্য->keyboard_element);
    যদি (চাবি_Element) {
        emscripten_set_keydown_callback(চাবি_Element, ফাঁকা, 0, ফাঁকা);
        emscripten_set_keyup_callback(চাবি_Element, ফাঁকা, 0, ফাঁকা);
        emscripten_set_keypress_callback(চাবি_Element, ফাঁকা, 0, ফাঁকা);
        MAIN_THREAD_EM_ASM_INT({
            document.removeEventListener("keydown", document.sdl_Event_Handler_Lock_চাবিগুলি_Check);
        });
    }

    emscripten_set_visibilitychange_callback(ফাঁকা, 0, ফাঁকা);

    emscripten_set_beforeunload_callback(ফাঁকা, ফাঁকা);
}

#endif // SDL_VIDEO_DRIVER_EMSCRIPTEN

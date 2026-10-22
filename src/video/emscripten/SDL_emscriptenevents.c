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

#ضمن "SDL_internal.h"

#که_تعریف_شوی SDL_VIDEO_DRIVER_EMSCRIPTEN

#ضمن <emscripten/html5.h>
#ضمن <emscripten/dom_pk_codes.h>

#ضمن "../../events/SDL_dropevents_c.h"
#ضمن "../../events/SDL_events_c.h"
#ضمن "../../events/SDL_keyboard_c.h"
#ضمن "../../events/SDL_touch_c.h"

#ضمن "SDL_emscriptenevents.h"
#ضمن "SDL_emscriptenvideo.h"

/*
Emscripten PK code to scancode
https://developer.mozilla.org/en-US/docs/Web/API/KeyboardEvent
https://developer.mozilla.org/en-US/docs/Web/API/KeyboardEvent/code
*/
ساكن ثابت SDL_Scancode emscripten_scancode_جدول[] = {
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

ساكن SDL_Scancode Emscripten_Map_لټون_کوډ(ثابت حرف *کوډ)
{
    ثابت DOM_PK_کوډ_TYPE pk_کوډ = emscripten_compute_dom_pk_کوډ(کوډ);
    إذا (pk_کوډ < SDL_arraysize(emscripten_scancode_جدول)) {
        أرجع emscripten_scancode_جدول[pk_کوډ];
    }

    بدل (pk_کوډ) {
    حالة DOM_PK_PASTE:
        أرجع SDL_SCANCODE_PASTE;
    حالة DOM_PK_MEDIA_TRACK_پخوانی:
        أرجع SDL_SCANCODE_MEDIA_پخوانی_TRACK;
    حالة DOM_PK_CUT:
        أرجع SDL_SCANCODE_CUT;
    حالة DOM_PK_COPY:
        أرجع SDL_SCANCODE_COPY;
    حالة DOM_PK_MEDIA_TRACK_بل:
        أرجع SDL_SCANCODE_MEDIA_بل_TRACK;
    حالة DOM_PK_NUMPAD_ENTER:
        أرجع SDL_SCANCODE_KP_ENTER;
    حالة DOM_PK_CONTROL_ښی:
        أرجع SDL_SCANCODE_RCTRL;
    حالة DOM_PK_AUDIO_VOLUME_MUTE:
        أرجع SDL_SCANCODE_MUTE;
    حالة DOM_PK_MEDIA_PLAY_PAUSE:
        أرجع SDL_SCANCODE_MEDIA_PLAY_PAUSE;
    حالة DOM_PK_MEDIA_STOP:
        أرجع SDL_SCANCODE_MEDIA_STOP;
    حالة DOM_PK_EJECT:
        أرجع SDL_SCANCODE_MEDIA_EJECT;
    حالة DOM_PK_AUDIO_VOLUME_ښکته:
        أرجع SDL_SCANCODE_VOLUMEDOWN;
    حالة DOM_PK_AUDIO_VOLUME_پورته:
        أرجع SDL_SCANCODE_VOLUMEUP;
    حالة DOM_PK_BROWSER_HOME:
        أرجع SDL_SCANCODE_AC_HOME;
    حالة DOM_PK_NUMPAD_DIVIDE:
        أرجع SDL_SCANCODE_KP_DIVIDE;
    حالة DOM_PK_ALT_ښی:
        أرجع SDL_SCANCODE_RALT;
    حالة DOM_PK_HELP:
        أرجع SDL_SCANCODE_HELP;
    حالة DOM_PK_عدد_قلف:
        أرجع SDL_SCANCODE_NUMLOCKCLEAR;
    حالة DOM_PK_HOME:
        أرجع SDL_SCANCODE_HOME;
    حالة DOM_PK_ARROW_پورته:
        أرجع SDL_SCANCODE_پورته;
    حالة DOM_PK_پاڼه_پورته:
        أرجع SDL_SCANCODE_PAGEUP;
    حالة DOM_PK_ARROW_کیڼ:
        أرجع SDL_SCANCODE_کیڼ;
    حالة DOM_PK_ARROW_ښی:
        أرجع SDL_SCANCODE_ښی;
    حالة DOM_PK_پای_ټکی:
        أرجع SDL_SCANCODE_پای_ټکی;
    حالة DOM_PK_ARROW_ښکته:
        أرجع SDL_SCANCODE_ښکته;
    حالة DOM_PK_پاڼه_ښکته:
        أرجع SDL_SCANCODE_PAGEDOWN;
    حالة DOM_PK_ورننباسه:
        أرجع SDL_SCANCODE_ورننباسه;
    حالة DOM_PK_DELETE:
        أرجع SDL_SCANCODE_DELETE;
    حالة DOM_PK_META_کیڼ:
        أرجع SDL_SCANCODE_LGUI;
    حالة DOM_PK_META_ښی:
        أرجع SDL_SCANCODE_RGUI;
    حالة DOM_PK_CONTEXT_MENU:
        أرجع SDL_SCANCODE_APPLICATION;
    حالة DOM_PK_POWER:
        أرجع SDL_SCANCODE_POWER;
    حالة DOM_PK_BROWSER_پلټنه:
        أرجع SDL_SCANCODE_AC_پلټنه;
    حالة DOM_PK_BROWSER_FAVORITES:
        أرجع SDL_SCANCODE_AC_BOOKMARKS;
    حالة DOM_PK_BROWSER_REFRESH:
        أرجع SDL_SCANCODE_AC_REFRESH;
    حالة DOM_PK_BROWSER_STOP:
        أرجع SDL_SCANCODE_AC_STOP;
    حالة DOM_PK_BROWSER_FORWARD:
        أرجع SDL_SCANCODE_AC_FORWARD;
    حالة DOM_PK_BROWSER_شا:
        أرجع SDL_SCANCODE_AC_شا;
    حالة DOM_PK_MEDIA_SELECT:
        أرجع SDL_SCANCODE_MEDIA_SELECT;
    }

    أرجع SDL_SCANCODE_UNKNOWN;
}

ساكن SDL_کړکۍ *Emscripten_Get_Focused_کړکۍ(SDL_VideoDevice *device)
{
    SDL_کړکۍ *کړکۍ;
    لكل (کړکۍ = device->windows; کړکۍ; کړکۍ = کړکۍ->بل) {
        SDL_کړکۍ_معلومات *wdata = کړکۍ->دننی;

        ثابت صحيح focused = MAIN_THREAD_EM_ASM_INT({
            var id = UTF8_منزل_String($0);
            try
            {
                var canvas = document.querySelector(id);
                إذا (canvas) {
                    أرجع canvas === document.فعال_Element;
                }
            }
            catch (e)
            {
                // querySelector throws if not a valid selector
            }
            أرجع false;
        }, wdata->canvas_id);

        إذا (focused) {
            اكسر;
        }
    }
    // If the DOM is focused, then at least one canvas in the DOM should be considered focused.
    // So in this case, just assume that the first canvas is focused.
    إذا (!کړکۍ) {
        ثابت صحيح focused = MAIN_THREAD_EM_ASM_INT({
            أرجع document.hasFocus();
        });
        إذا (focused) {
            کړکۍ = device->windows;
        }
    }
    أرجع کړکۍ;
}

ساكن EM_BOOL Emscripten_Handle_اشاره_ګر_قلف_Change(صحيح eventType, ثابت EmscriptenPointerlockChangeEvent *changeEvent, فراغ *user_معلومات)
{
    SDL_کړکۍ_معلومات *کړکۍ_معلومات_2 = (SDL_کړکۍ_معلومات *)user_معلومات;
    // keep track of lock losses, so we can regrab if/when appropriate.
    کړکۍ_معلومات_2->has_اشاره_ګر_قلف = changeEvent->is_فعال;
    أرجع 0;
}

ساكن EM_BOOL Emscripten_Handle_اشاره_ګر_قلف_Change_Global(صحيح eventType, ثابت EmscriptenPointerlockChangeEvent *changeEvent, فراغ *user_معلومات)
{
    SDL_VideoDevice *device = user_معلومات;
    bool prevent_default = false;
    SDL_کړکۍ *کړکۍ;

    لكل (کړکۍ = device->windows; کړکۍ; کړکۍ = کړکۍ->بل) {
        prevent_default |= Emscripten_Handle_اشاره_ګر_قلف_Change(eventType, changeEvent, کړکۍ->دننی);
    }

    أرجع prevent_default;
}

ساكن EM_BOOL Emscripten_HandleWheel(صحيح eventType, ثابت EmscriptenWheelEvent *wheelEvent, فراغ *user_معلومات)
{
    SDL_کړکۍ_معلومات *کړکۍ_معلومات_2 = user_معلومات;

    عائم deltaY = wheelEvent->deltaY;
    عائم deltaX = wheelEvent->deltaX;

    بدل (wheelEvent->delta_ډېرپېښ) {
    حالة DOM_DELTA_PIXEL:
        deltaX /= 100; // 100 pixels make up a step
        deltaY /= 100; // 100 pixels make up a step
        اكسر;
    حالة DOM_DELTA_کرښه:
        deltaX /= 3; // 3 lines make up a step
        deltaY /= 3; // 3 lines make up a step
        اكسر;
    حالة DOM_DELTA_پاڼه:
        deltaX *= 80; // A page makes up 80 steps
        deltaY *= 80; // A page makes up 80 steps
        اكسر;
    }

    SDL_SendMouseWheel(0, کړکۍ_معلومات_2->کړکۍ, SDL_DEFAULT_MOUSE_ID, deltaX, -deltaY, SDL_MOUSEWHEEL_نورمال);
    أرجع SDL_EventEnabled(SDL_EVENT_MOUSE_WHEEL);
}

ساكن EM_BOOL Emscripten_HandleFocus(صحيح eventType, ثابت EmscriptenFocusEvent *focusEvent, فراغ *user_معلومات)
{
    SDL_VideoDevice *device = user_معلومات;
    SDL_کړکۍ *کړکۍ = Emscripten_Get_Focused_کړکۍ(device);

    SDL_EventType sdl_event_type;

    /* If the user switches away while keys are pressed (such as
     * via Alt+Tab), key release events won't be received. */
    إذا (eventType == EMSCRIPTEN_EVENT_BLUR) {
        SDL_ResetKeyboard();
    }

    sdl_event_type = (eventType == EMSCRIPTEN_EVENT_FOCUS) ? SDL_EVENT_کړکۍ_FOCUS_GAINED : SDL_EVENT_کړکۍ_FOCUS_ورک;
    SDL_سېټ_Keyboard_Focus(sdl_event_type == SDL_EVENT_کړکۍ_FOCUS_GAINED ? کړکۍ : عدم);
    أرجع SDL_EventEnabled(sdl_event_type);
}

ساكن bool Is_Function_کلی(SDL_Scancode scancode)
{
    إذا (scancode >= SDL_SCANCODE_F1 && scancode <= SDL_SCANCODE_F12) {
        أرجع true;
    }
    إذا (scancode >= SDL_SCANCODE_F13 && scancode <= SDL_SCANCODE_F24) {
        أرجع true;
    }
    أرجع false;
}

/* This is a great tool to see web keyboard events live:
 * https://w3c.github.io/uievents/tools/key-event-viewer.html
 */
ساكن EM_BOOL Emscripten_Handle_کلی(صحيح eventType, ثابت EmscriptenKeyboardEvent *کلی_Event, فراغ *user_معلومات)
{
    SDL_کړکۍ_معلومات *کړکۍ_معلومات_2 = (SDL_کړکۍ_معلومات *)user_معلومات;
    SDL_Scancode scancode = Emscripten_Map_لټون_کوډ(کلی_Event->کوډ);
    SDL_Keycode keycode = SDLK_UNKNOWN;
    bool prevent_default = false;
    bool is_nav_کلی = false;

    إذا (scancode == SDL_SCANCODE_UNKNOWN) {
        إذا (SDL_strcmp(کلی_Event->کلی, "Sleep") == 0) {
            scancode = SDL_SCANCODE_SLEEP;
        } وإلا إذا (SDL_strcmp(کلی_Event->کلی, "ChannelUp") == 0) {
            scancode = SDL_SCANCODE_CHANNEL_INCREMENT;
        } وإلا إذا (SDL_strcmp(کلی_Event->کلی, "ChannelDown") == 0) {
            scancode = SDL_SCANCODE_CHANNEL_DECREMENT;
        } وإلا إذا (SDL_strcmp(کلی_Event->کلی, "MediaPlay") == 0) {
            scancode = SDL_SCANCODE_MEDIA_PLAY;
        } وإلا إذا (SDL_strcmp(کلی_Event->کلی, "MediaPause") == 0) {
            scancode = SDL_SCANCODE_MEDIA_PAUSE;
        } وإلا إذا (SDL_strcmp(کلی_Event->کلی, "MediaRecord") == 0) {
            scancode = SDL_SCANCODE_MEDIA_ریکارډ;
        } وإلا إذا (SDL_strcmp(کلی_Event->کلی, "MediaFastForward") == 0) {
            scancode = SDL_SCANCODE_MEDIA_FAST_FORWARD;
        } وإلا إذا (SDL_strcmp(کلی_Event->کلی, "MediaRewind") == 0) {
            scancode = SDL_SCANCODE_MEDIA_REWIND;
        } وإلا إذا (SDL_strcmp(کلی_Event->کلی, "Close") == 0) {
            scancode = SDL_SCANCODE_AC_CLOSE;
        } وإلا إذا (SDL_strcmp(کلی_Event->کلی, "New") == 0) {
            scancode = SDL_SCANCODE_AC_NEW;
        } وإلا إذا (SDL_strcmp(کلی_Event->کلی, "Open") == 0) {
            scancode = SDL_SCANCODE_AC_OPEN;
        } وإلا إذا (SDL_strcmp(کلی_Event->کلی, "Print") == 0) {
            scancode = SDL_SCANCODE_AC_PRINT;
        } وإلا إذا (SDL_strcmp(کلی_Event->کلی, "Save") == 0) {
            scancode = SDL_SCANCODE_AC_SAVE;
        } وإلا إذا (SDL_strcmp(کلی_Event->کلی, "Props") == 0) {
            scancode = SDL_SCANCODE_AC_PROPERTIES;
        }
    }

    إذا (scancode == SDL_SCANCODE_UNKNOWN) {
        // KaiOS Left Soft Key and Right Soft Key, they act as OK/Next/Menu and Cancel/Back/Clear
        إذا (SDL_strcmp(کلی_Event->کلی, "SoftLeft") == 0) {
            scancode = SDL_SCANCODE_AC_FORWARD;
        } وإلا إذا (SDL_strcmp(کلی_Event->کلی, "SoftRight") == 0) {
            scancode = SDL_SCANCODE_AC_شا;
        }
    }

    إذا (کلی_Event->location == 0 && SDL_utf8strlen(کلی_Event->کلی) == 1) {
        ثابت حرف *کلی = کلی_Event->کلی;
        keycode = SDL_ګام_UTF8(&کلی, عدم);
        إذا (keycode == SDL_INVALID_UNICODE_CODEPOINT) {
            keycode = SDLK_UNKNOWN;
        }
    }

    إذا (keycode != SDLK_UNKNOWN) {
        prevent_default = SDL_Send_Keyboard_کلی_And_Keycode(0, SDL_DEFAULT_KEYBOARD_ID, 0, scancode, keycode, (eventType == EMSCRIPTEN_EVENT_KEYDOWN));
    } وإلا {
        prevent_default = SDL_Send_Keyboard_کلی(0, SDL_DEFAULT_KEYBOARD_ID, 0, scancode, (eventType == EMSCRIPTEN_EVENT_KEYDOWN));
    }

    /* if TEXTINPUT events are enabled we can't prevent keydown or we won't get keypress
     * we need to ALWAYS prevent backspace and tab otherwise chrome takes action and does bad navigation UX
     */
    إذا ((scancode == SDL_SCANCODE_BACKSPACE) ||
        (scancode == SDL_SCANCODE_TAB) ||
        (scancode == SDL_SCANCODE_کیڼ) ||
        (scancode == SDL_SCANCODE_پورته) ||
        (scancode == SDL_SCANCODE_ښی) ||
        (scancode == SDL_SCANCODE_ښکته) ||
        Is_Function_کلی(scancode) ||
        کلی_Event->ctrl_کلی) {
        is_nav_کلی = true;
    }

    إذا ((eventType == EMSCRIPTEN_EVENT_KEYDOWN) && SDL_متن_ننوت_فعال(کړکۍ_معلومات_2->کړکۍ) && !is_nav_کلی) {
        prevent_default = false;
    }

    أرجع prevent_default;
}

ساكن EM_BOOL Emscripten_Handle_کلی_Press(صحيح eventType, ثابت EmscriptenKeyboardEvent *کلی_Event, فراغ *user_معلومات)
{
    SDL_کړکۍ_معلومات *کړکۍ_معلومات_2 = (SDL_کړکۍ_معلومات *)user_معلومات;

    إذا (SDL_متن_ننوت_فعال(کړکۍ_معلومات_2->کړکۍ)) {
        إذا (SDL_utf8strlen(کلی_Event->کلی) == 1) {
            SDL_Send_Keyboard_متن(کلی_Event->کلی);
            أرجع EM_TRUE;
        }
    }
    أرجع EM_FALSE;
}

ساكن EM_BOOL Emscripten_HandleFullscreenChange(صحيح eventType, ثابت EmscriptenFullscreenChangeEvent *fullscreenChangeEvent, فراغ *user_معلومات)
{
    SDL_کړکۍ_معلومات *کړکۍ_معلومات_2 = user_معلومات;

    کړکۍ_معلومات_2->fullscreen_change_دننه_پرمختګ = false;

    إذا (fullscreenChangeEvent->isFullscreen) {
        SDL_Send_کړکۍ_Event(کړکۍ_معلومات_2->کړکۍ, SDL_EVENT_کړکۍ_ENTER_FULLSCREEN, 0, 0);
        کړکۍ_معلومات_2->fullscreen_ډېرپېښ_flags = 0;
    } وإلا {
        SDL_Send_کړکۍ_Event(کړکۍ_معلومات_2->کړکۍ, SDL_EVENT_کړکۍ_LEAVE_FULLSCREEN, 0, 0);
    }

    SDL_Update_Fullscreen_ډېرپېښ(کړکۍ_معلومات_2->کړکۍ, fullscreenChangeEvent->isFullscreen, false);

    أرجع 0;
}

ساكن EM_BOOL Emscripten_HandleFullscreenChangeGlobal(صحيح eventType, ثابت EmscriptenFullscreenChangeEvent *fullscreenChangeEvent, فراغ *user_معلومات)
{
    SDL_VideoDevice *device = user_معلومات;
    SDL_کړکۍ *کړکۍ = عدم;
    لكل (کړکۍ = device->windows; کړکۍ != عدم; کړکۍ = کړکۍ->بل) {
        ثابت حرف *canvas_id = کړکۍ->دننی->canvas_id;
        إذا (*canvas_id == '#') {
            canvas_id++;
        }
        إذا (SDL_strcmp(fullscreenChangeEvent->id, canvas_id) == 0) {
            اكسر;  // this is the window.
        }
    }

    إذا (کړکۍ) {
        أرجع Emscripten_HandleFullscreenChange(eventType, fullscreenChangeEvent, کړکۍ->دننی);
    }

    أرجع EM_FALSE;
}

ساكن EM_BOOL Emscripten_HandleResize(صحيح eventType, ثابت EmscriptenUiEvent *uiEvent, فراغ *user_معلومات)
{
    SDL_کړکۍ_معلومات *کړکۍ_معلومات_2 = user_معلومات;

    bool force = false;

    // update pixel ratio
    إذا (کړکۍ_معلومات_2->کړکۍ->flags & SDL_کړکۍ_لوړ_PIXEL_DENSITY) {
        إذا (کړکۍ_معلومات_2->pixel_نسبت != emscripten_get_device_pixel_نسبت()) {
            کړکۍ_معلومات_2->pixel_نسبت = emscripten_get_device_pixel_نسبت();
            force = true;
        }
    }

    ثابت bool fill_document = (Emscripten_fill_document_کړکۍ == کړکۍ_معلومات_2->کړکۍ);
    ثابت bool fullscreen = (کړکۍ_معلومات_2->کړکۍ->flags & SDL_کړکۍ_FULLSCREEN) != 0;  // fullscreen windows can resize on Emscripten, and the canvas should fill it.
    ثابت bool resizable = (کړکۍ_معلومات_2->کړکۍ->flags & SDL_کړکۍ_RESIZABLE) != 0;
    إذا (fill_document || fullscreen || resizable) {
        مزدوج w, h;
        إذا (fill_document || fullscreen) {
            w = (مزدوج) uiEvent->کړکۍ_Inner_پلنوالی;
            h = (مزدوج) uiEvent->کړکۍ_Inner_لوړوالی;
        } وإلا {
            SDL_assert(کړکۍ_معلومات_2->کړکۍ->flags & SDL_کړکۍ_RESIZABLE);
            w = کړکۍ_معلومات_2->کړکۍ->w;
            h = کړکۍ_معلومات_2->کړکۍ->h;
            // this will only work if the canvas size is set through css
            إذا (کړکۍ_معلومات_2->external_اندازه) {
                emscripten_get_element_css_اندازه(کړکۍ_معلومات_2->canvas_id, &w, &h);
            }
        }

        emscripten_سېټ_canvas_element_اندازه(کړکۍ_معلومات_2->canvas_id, SDL_lroundf(w * کړکۍ_معلومات_2->pixel_نسبت), SDL_lroundf(h * کړکۍ_معلومات_2->pixel_نسبت));

        // set_canvas_size unsets this
        إذا (!کړکۍ_معلومات_2->external_اندازه && کړکۍ_معلومات_2->pixel_نسبت != 1.0f) {
            emscripten_سېټ_element_css_اندازه(کړکۍ_معلومات_2->canvas_id, w, h);
        }

        إذا (force) {
            // force the event to trigger, so pixel ratio changes can be handled
            کړکۍ_معلومات_2->کړکۍ->w = 0;
            کړکۍ_معلومات_2->کړکۍ->h = 0;
        }

        SDL_Send_کړکۍ_Event(کړکۍ_معلومات_2->کړکۍ, SDL_EVENT_کړکۍ_RESIZED, SDL_lroundf(w), SDL_lroundf(h));
    }

    أرجع 0;
}

ساكن EM_BOOL Emscripten_HandleResizeGlobal(صحيح eventType, ثابت EmscriptenUiEvent *uiEvent, فراغ *user_معلومات)
{
    SDL_VideoDevice *device = user_معلومات;
    bool prevent_default = false;
    SDL_کړکۍ *کړکۍ;

    لكل (کړکۍ = device->windows; کړکۍ; کړکۍ = کړکۍ->بل) {
        prevent_default |= Emscripten_HandleResize(eventType, uiEvent, کړکۍ->دننی);
    }

    أرجع prevent_default;
}

EM_BOOL
Emscripten_HandleCanvasResize(صحيح eventType, ثابت فراغ *reserved, فراغ *user_معلومات)
{
    // this is used during fullscreen changes
    SDL_کړکۍ_معلومات *کړکۍ_معلومات_2 = user_معلومات;

    إذا (کړکۍ_معلومات_2->fullscreen_resize) {
        مزدوج css_w, css_h;
        emscripten_get_element_css_اندازه(کړکۍ_معلومات_2->canvas_id, &css_w, &css_h);
        SDL_Send_کړکۍ_Event(کړکۍ_معلومات_2->کړکۍ, SDL_EVENT_کړکۍ_RESIZED, SDL_lroundf(css_w), SDL_lroundf(css_h));
    }

    أرجع 0;
}

ساكن EM_BOOL Emscripten_HandleVisibilityChange(صحيح eventType, ثابت EmscriptenVisibilityChangeEvent *visEvent, فراغ *user_معلومات)
{
    SDL_کړکۍ_معلومات *کړکۍ_معلومات_2 = user_معلومات;
    SDL_Send_کړکۍ_Event(کړکۍ_معلومات_2->کړکۍ, visEvent->hidden ? SDL_EVENT_کړکۍ_HIDDEN : SDL_EVENT_کړکۍ_SHOWN, 0, 0);
    أرجع 0;
}

ساكن ثابت حرف *Emscripten_HandleBeforeUnload(صحيح eventType, ثابت فراغ *reserved, فراغ *user_معلومات)
{
    /* This event will need to be handled synchronously, e.g. using
       SDL_AddEventWatch, as the page is being closed *now*. */
    SDL_SendQuit();  // the app might see this if they installed an event watcher.
    SDL_OnApplicationWillTerminate();  // calls SDL_AppQuit if appropriate, etc.
    أرجع ""; // don't trigger confirmation dialog
}

ساكن EM_BOOL Emscripten_HandleOrientationChange(صحيح eventType, ثابت EmscriptenOrientationChangeEvent *orientationChangeEvent, فراغ *user_معلومات)
{
    SDL_DisplayOrientation orientation;
    بدل (orientationChangeEvent->orientation_شاخص) {
        #تعریف_کړه CHECK_ORIENTATION(emsdk, sdl) حالة EMSCRIPTEN_ORIENTATION_##emsdk: orientation = SDL_ORIENTATION_##sdl; اكسر
        CHECK_ORIENTATION(LANDSCAPE_PRIMARY, LANDSCAPE);
        CHECK_ORIENTATION(LANDSCAPE_SECONDARY, LANDSCAPE_FLIPPED);
        CHECK_ORIENTATION(PORTRAIT_PRIMARY, PORTRAIT);
        CHECK_ORIENTATION(PORTRAIT_SECONDARY, PORTRAIT_FLIPPED);
        #تعریف_لغوه CHECK_ORIENTATION
        افتراضي: orientation = SDL_ORIENTATION_UNKNOWN; اكسر;
    }

    SDL_کړکۍ_معلومات *کړکۍ_معلومات_2 = (SDL_کړکۍ_معلومات *) user_معلومات;
    SDL_SendDisplayEvent(SDL_Get_Video_Display_For_کړکۍ(کړکۍ_معلومات_2->کړکۍ), SDL_EVENT_DISPLAY_ORIENTATION, orientation, 0);

    // fake a UI event so we can tell the app the canvas might have resized.
    EmscriptenUiEvent uiEvent;
    SDL_zero(uiEvent);
    uiEvent.document_Body_Client_پلنوالی = MAIN_THREAD_EM_ASM_INT( { أرجع document.body.client_پلنوالی; } );
    uiEvent.document_Body_Client_لوړوالی = MAIN_THREAD_EM_ASM_INT( { أرجع document.body.client_لوړوالی; } );
    uiEvent.کړکۍ_Inner_پلنوالی = MAIN_THREAD_EM_ASM_INT( { أرجع کړکۍ.inner_پلنوالی; } );
    uiEvent.کړکۍ_Inner_لوړوالی = MAIN_THREAD_EM_ASM_INT( { أرجع کړکۍ.inner_لوړوالی; } );
    uiEvent.کړکۍ_Outer_پلنوالی = MAIN_THREAD_EM_ASM_INT( { أرجع کړکۍ.outer_پلنوالی; } );
    uiEvent.کړکۍ_Outer_لوړوالی = MAIN_THREAD_EM_ASM_INT( { أرجع کړکۍ.outer_لوړوالی; } );
    uiEvent.scroll_سر = MAIN_THREAD_EM_ASM_INT( { أرجع کړکۍ.پاڼه_XOffset; } );
    uiEvent.scroll_کیڼ = MAIN_THREAD_EM_ASM_INT( { أرجع کړکۍ.پاڼه_YOffset; } );
    Emscripten_HandleResize(EMSCRIPTEN_EVENT_RESIZE, &uiEvent, user_معلومات);

    أرجع 0;
}

// IF YOU CHANGE THIS STRUCTURE, YOU NEED TO UPDATE THE JAVASCRIPT THAT FILLS IT IN: SDL3.makePointerEventCStruct, below.
#تعریف_کړه PTRTYPE_MOUSE 1
#تعریف_کړه PTRTYPE_TOUCH 2
#تعریف_کړه PTRTYPE_PEN 3
تعريفنوع بنية Emscripten_اشاره_ګر_Event
{
    صحيح اشاره_ګر_type;
    صحيح pointerid;
    صحيح button;
    صحيح buttons;
    صحيح ښکته;
    عائم movementX;
    عائم movementY;
    عائم موخه_X;
    عائم موخه_Y;
    عائم pressure;
    عائم tangential_pressure;
    عائم tiltx;
    عائم tilty;
    عائم rotation;
} Emscripten_اشاره_ګر_Event;

ساكن فراغ Emscripten_HandleMouseButton(SDL_کړکۍ_معلومات *کړکۍ_معلومات_2, ثابت Emscripten_اشاره_ګر_Event *event)
{
    Uint8 sdl_button;
    bool ښکته = false;
    بدل (event->button) {
        #تعریف_کړه CHECK_MOUSE_BUTTON(jsbutton, downflag, sdlbutton) حالة jsbutton: sdl_button = SDL_BUTTON_##sdlbutton; ښکته = (event->ښکته != 0) || ((event->buttons & downflag) != 0); اكسر
        CHECK_MOUSE_BUTTON(0, 1, کیڼ_2);
        CHECK_MOUSE_BUTTON(1, 4, منځ_2);
        CHECK_MOUSE_BUTTON(2, 2, ښی_2);
        CHECK_MOUSE_BUTTON(3, 8, X1);
        CHECK_MOUSE_BUTTON(4, 16, X2);
        #تعریف_لغوه CHECK_MOUSE_BUTTON
        افتراضي: sdl_button = 0; اكسر;
    }

    إذا (sdl_button) {
        ثابت SDL_Mouse *mouse = SDL_GetMouse();
        SDL_assert(mouse != عدم);

        إذا (ښکته) {
            إذا (mouse->relative_ډېرپېښ && !کړکۍ_معلومات_2->has_اشاره_ګر_قلف) {
                emscripten_request_pointerlock(کړکۍ_معلومات_2->canvas_id, 0); // try to regrab lost pointer lock.
            }
        }

        SDL_SendMouseButton(0, کړکۍ_معلومات_2->کړکۍ, SDL_DEFAULT_MOUSE_ID, sdl_button, ښکته);

        // We have an imaginary mouse capture, because we need SDL to not drop our imaginary mouse focus when we leave the canvas.
        إذا (mouse->auto_capture) {
            إذا (SDL_GetMouseState(عدم, عدم) != 0) {
                کړکۍ_معلومات_2->کړکۍ->flags |= SDL_کړکۍ_MOUSE_CAPTURE;
            } وإلا {
                کړکۍ_معلومات_2->کړکۍ->flags &= ~SDL_کړکۍ_MOUSE_CAPTURE;
            }
        }

        إذا (!ښکته && کړکۍ_معلومات_2->mouse_focus_loss_pending) {
            کړکۍ_معلومات_2->mouse_focus_loss_pending = (کړکۍ_معلومات_2->کړکۍ->flags & SDL_کړکۍ_MOUSE_CAPTURE) != 0;
            إذا (!کړکۍ_معلومات_2->mouse_focus_loss_pending) {
                SDL_سېټ_Mouse_Focus(عدم);
            }
        }
    }
}

ساكن فراغ Emscripten_UpdateMouseFromEvent(SDL_کړکۍ_معلومات *کړکۍ_معلومات_2, ثابت Emscripten_اشاره_ګر_Event *event)
{
    SDL_assert(event->اشاره_ګر_type == PTRTYPE_MOUSE);

    // Hidden windows (e.g. a shared GL-context window) may share the DOM canvas with the
    // visible window. Their pointer-event listeners would otherwise fire alongside the
    // visible window's, fighting over `mouse->focus` and producing events tagged with the
    // hidden window's ID -- causing downstream consumers that key by window ID to silently
    // drop them. Hidden windows shouldn't take part in user-input dispatch.
    إذا (کړکۍ_معلومات_2->کړکۍ->flags & SDL_کړکۍ_HIDDEN) {
        أرجع;
    }

    // rescale (in case canvas is being scaled)
    مزدوج client_w, client_h;
    emscripten_get_element_css_اندازه(کړکۍ_معلومات_2->canvas_id, &client_w, &client_h);
    ثابت مزدوج xscale = کړکۍ_معلومات_2->کړکۍ->w / client_w;
    ثابت مزدوج yscale = کړکۍ_معلومات_2->کړکۍ->h / client_h;

    ثابت bool is_اشاره_ګر_Locked = کړکۍ_معلومات_2->has_اشاره_ګر_قلف;
    عائم mx, my;
    إذا (is_اشاره_ګر_Locked) {
        mx = (عائم)(event->movementX * xscale);
        my = (عائم)(event->movementY * yscale);
    } وإلا {
        mx = (عائم)(event->موخه_X * xscale);
        my = (عائم)(event->موخه_Y * yscale);
    }

    SDL_SendMouseMotion(0, کړکۍ_معلومات_2->کړکۍ, SDL_DEFAULT_MOUSE_ID, is_اشاره_ګر_Locked, mx, my);

    Emscripten_HandleMouseButton(کړکۍ_معلومات_2, event);
}

ساكن فراغ Emscripten_UpdateTouchFromEvent(SDL_کړکۍ_معلومات *کړکۍ_معلومات_2, ثابت Emscripten_اشاره_ګر_Event *event)
{
    SDL_assert(event->اشاره_ګر_type == PTRTYPE_TOUCH);

    ثابت SDL_TouchID deviceId = 1;
    إذا (SDL_جمع_کړه_Touch(deviceId, SDL_TOUCH_DEVICE_مستقیم, "") < 0) {
        أرجع;
    }

    مزدوج client_w, client_h;
    emscripten_get_element_css_اندازه(کړکۍ_معلومات_2->canvas_id, &client_w, &client_h);

    ثابت SDL_FingerID id = event->pointerid + 1;
    عائم x, y;
    إذا (client_w <= 1) {
        x = 0.5f;
    } وإلا {
        x = event->موخه_X / (client_w - 1);
    }
    إذا (client_h <= 1) {
        y = 0.5f;
    } وإلا {
        y = event->موخه_Y / (client_h - 1);
    }

    ثابت bool ښکته = (event->buttons & 1) != 0;
    إذا (event->button == 0) {  // touch is starting or ending if this is zero (-1 means "no change").
        إذا (ښکته) {
            SDL_SendTouch(0, deviceId, id, کړکۍ_معلومات_2->کړکۍ, SDL_EVENT_FINGER_ښکته, x, y, 1.0f);
        }
    }

    SDL_SendTouchMotion(0, deviceId, id, کړکۍ_معلومات_2->کړکۍ, x, y, 1.0f);

    إذا (event->button == 0) {  // touch is starting or ending if this is zero (-1 means "no change").
        إذا (!ښکته) {
            SDL_SendTouch(0, deviceId, id, کړکۍ_معلومات_2->کړکۍ, SDL_EVENT_FINGER_پورته, x, y, 1.0f);
        }
    }
}

ساكن فراغ Emscripten_UpdatePenFromEvent(SDL_کړکۍ_معلومات *کړکۍ_معلومات_2, ثابت Emscripten_اشاره_ګر_Event *event)
{
    SDL_assert(event->اشاره_ګر_type == PTRTYPE_PEN);
    ثابت SDL_PenID pen = SDL_پیدا_کړه_Pen_By_Handle((فراغ *) (size_t) 1);   // something > 0 for the single pen handle.
    إذا (pen) {
        // rescale (in case canvas is being scaled)
        مزدوج client_w, client_h;
        emscripten_get_element_css_اندازه(کړکۍ_معلومات_2->canvas_id, &client_w, &client_h);
        ثابت مزدوج xscale = کړکۍ_معلومات_2->کړکۍ->w / client_w;
        ثابت مزدوج yscale = کړکۍ_معلومات_2->کړکۍ->h / client_h;

        ثابت bool is_اشاره_ګر_Locked = کړکۍ_معلومات_2->has_اشاره_ګر_قلف;
        عائم mx, my;
        إذا (is_اشاره_ګر_Locked) {
            mx = (عائم)(event->movementX * xscale);
            my = (عائم)(event->movementY * yscale);
        } وإلا {
            mx = (عائم)(event->موخه_X * xscale);
            my = (عائم)(event->موخه_Y * yscale);
        }

        SDL_SendPenMotion(0, pen, کړکۍ_معلومات_2->کړکۍ, mx, my);

        إذا (event->button == 0) {  // pen touch
            bool ښکته = ((event->buttons & 1) != 0);
            SDL_SendPenTouch(0, pen, کړکۍ_معلومات_2->کړکۍ, false, ښکته);
        } وإلا إذا (event->button == 5) {  // eraser touch...? Not sure if this is right...
            bool ښکته = ((event->buttons & 32) != 0);
            SDL_SendPenTouch(0, pen, کړکۍ_معلومات_2->کړکۍ, true, ښکته);
        } وإلا إذا (event->button == 1) {
            bool ښکته = ((event->buttons & 4) != 0);
            SDL_SendPenButton(0, pen, کړکۍ_معلومات_2->کړکۍ, 2, ښکته);
        } وإلا إذا (event->button == 2) {
            bool ښکته = ((event->buttons & 2) != 0);
            SDL_SendPenButton(0, pen, کړکۍ_معلومات_2->کړکۍ, 1, ښکته);
        }

        SDL_SendPenAxis(0, pen, کړکۍ_معلومات_2->کړکۍ, SDL_PEN_AXIS_PRESSURE, event->pressure);
        SDL_SendPenAxis(0, pen, کړکۍ_معلومات_2->کړکۍ, SDL_PEN_AXIS_TANGENTIAL_PRESSURE, event->tangential_pressure);
        SDL_SendPenAxis(0, pen, کړکۍ_معلومات_2->کړکۍ, SDL_PEN_AXIS_XTILT, event->tiltx);
        SDL_SendPenAxis(0, pen, کړکۍ_معلومات_2->کړکۍ, SDL_PEN_AXIS_YTILT, event->tilty);
        SDL_SendPenAxis(0, pen, کړکۍ_معلومات_2->کړکۍ, SDL_PEN_AXIS_ROTATION, event->rotation);
    }
}

ساكن فراغ Emscripten_Update_اشاره_ګر_From_Event(SDL_کړکۍ_معلومات *کړکۍ_معلومات_2, ثابت Emscripten_اشاره_ګر_Event *event)
{
    SDL_assert(event != عدم);
    إذا (event->اشاره_ګر_type == PTRTYPE_MOUSE) {
        Emscripten_UpdateMouseFromEvent(کړکۍ_معلومات_2, event);
    } وإلا إذا (event->اشاره_ګر_type == PTRTYPE_TOUCH) {
        Emscripten_UpdateTouchFromEvent(کړکۍ_معلومات_2, event);
    } وإلا إذا (event->اشاره_ګر_type == PTRTYPE_PEN) {
        Emscripten_UpdatePenFromEvent(کړکۍ_معلومات_2, event);
    } وإلا {
        SDL_assert(!"Unexpected pointer event type");
    }
}

ساكن فراغ Emscripten_HandleMouseFocus(SDL_کړکۍ_معلومات *کړکۍ_معلومات_2, ثابت Emscripten_اشاره_ګر_Event *event, bool isenter)
{
    SDL_assert(event->اشاره_ګر_type == PTRTYPE_MOUSE);

    // Hidden windows shouldn't ever become the mouse-focus target.
    إذا (کړکۍ_معلومات_2->کړکۍ->flags & SDL_کړکۍ_HIDDEN) {
        أرجع;
    }

    ثابت bool is_اشاره_ګر_Locked = کړکۍ_معلومات_2->has_اشاره_ګر_قلف;

    إذا (!is_اشاره_ګر_Locked) {
        // rescale (in case canvas is being scaled)
        عائم mx, my;
        مزدوج client_w, client_h;
        emscripten_get_element_css_اندازه(کړکۍ_معلومات_2->canvas_id, &client_w, &client_h);

        mx = (عائم)(event->موخه_X * (کړکۍ_معلومات_2->کړکۍ->w / client_w));
        my = (عائم)(event->موخه_Y * (کړکۍ_معلومات_2->کړکۍ->h / client_h));
        SDL_SendMouseMotion(0, کړکۍ_معلومات_2->کړکۍ, SDL_GLOBAL_MOUSE_ID, is_اشاره_ګر_Locked, mx, my);
    }

    إذا (isenter && کړکۍ_معلومات_2->mouse_focus_loss_pending) {
        کړکۍ_معلومات_2->mouse_focus_loss_pending = false;  // just drop the state, but don't send the enter event.
    } وإلا إذا (!isenter && (کړکۍ_معلومات_2->کړکۍ->flags & SDL_کړکۍ_MOUSE_CAPTURE)) {
        کړکۍ_معلومات_2->mouse_focus_loss_pending = true;  // waiting on a mouse button to let go before we send the mouse focus update.
    } وإلا {
        SDL_سېټ_Mouse_Focus(isenter ? کړکۍ_معلومات_2->کړکۍ : عدم);
    }
}

ساكن فراغ Emscripten_HandlePenEnter(SDL_کړکۍ_معلومات *کړکۍ_معلومات_2, ثابت Emscripten_اشاره_ګر_Event *event)
{
    SDL_assert(event->اشاره_ګر_type == PTRTYPE_PEN);

    // event->pointerid is one continuous interaction; it doesn't necessarily track a specific tool over time, like the same finger's ID changed on each new touch event.
    // as such, we only expose a single pen, and when the touch ends, we say it lost proximity instead of the calling SDL_RemovePenDevice().

    SDL_PenID pen = SDL_پیدا_کړه_Pen_By_Handle((فراغ *) (size_t) 1);  // something > 0 for the single pen handle.
    إذا (pen) {
        SDL_SendPenProximity(0, pen, کړکۍ_معلومات_2->کړکۍ, true, true);
    } وإلا {
        // Web browsers offer almost none of this information as specifics, but can without warning offer any of these specific things.
        SDL_PenInfo peninfo;
        SDL_zero(peninfo);
        peninfo.capabilities = SDL_PEN_CAPABILITY_PRESSURE | SDL_PEN_CAPABILITY_ROTATION | SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT | SDL_PEN_CAPABILITY_TANGENTIAL_PRESSURE | SDL_PEN_CAPABILITY_ERASER;
        peninfo.max_tilt = 90.0f;
        peninfo.عدد_buttons = 2;
        peninfo.subtype = SDL_PEN_TYPE_PEN;
        SDL_جمع_کړه_Pen_Device(0, عدم, کړکۍ_معلومات_2->کړکۍ, &peninfo, (فراغ *) (size_t) 1, true);
    }

    Emscripten_UpdatePenFromEvent(کړکۍ_معلومات_2, event);
}

EMSCRIPTEN_KEEPALIVE فراغ Emscripten_Handle_اشاره_ګر_Enter(SDL_کړکۍ_معلومات *کړکۍ_معلومات_2, ثابت Emscripten_اشاره_ګر_Event *event)
{
    SDL_assert(event != عدم);
    إذا (event->اشاره_ګر_type == PTRTYPE_MOUSE) {
        Emscripten_HandleMouseFocus(کړکۍ_معلومات_2, event, true);
    } وإلا إذا (event->اشاره_ګر_type == PTRTYPE_PEN) {
        Emscripten_HandlePenEnter(کړکۍ_معلومات_2, event);
    } وإلا إذا (event->اشاره_ګر_type == PTRTYPE_TOUCH) {
        // do nothing.
    } وإلا {
        SDL_assert(!"Unexpected pointer event type");
    }
}

ساكن فراغ Emscripten_HandlePenLeave(SDL_کړکۍ_معلومات *کړکۍ_معلومات_2, ثابت Emscripten_اشاره_ګر_Event *event)
{
    ثابت SDL_PenID pen = SDL_پیدا_کړه_Pen_By_Handle((فراغ *) (size_t) 1);   // something > 0 for the single pen handle.
    إذا (pen) {
        Emscripten_Update_اشاره_ګر_From_Event(کړکۍ_معلومات_2, event);  // last data updates?
        SDL_SendPenProximity(0, pen, کړکۍ_معلومات_2->کړکۍ, false, false);
    }
}

ساكن فراغ Emscripten_HandleTouchCancel(SDL_کړکۍ_معلومات *کړکۍ_معلومات_2, ثابت Emscripten_اشاره_ګر_Event *event)
{
    SDL_assert(event->اشاره_ګر_type == PTRTYPE_TOUCH);

    ثابت SDL_TouchID deviceId = 1;
    إذا (SDL_جمع_کړه_Touch(deviceId, SDL_TOUCH_DEVICE_مستقیم, "") < 0) {
        أرجع;
    }

    مزدوج client_w, client_h;
    emscripten_get_element_css_اندازه(کړکۍ_معلومات_2->canvas_id, &client_w, &client_h);

    ثابت SDL_FingerID id = event->pointerid + 1;
    عائم x, y;
    إذا (client_w <= 1) {
        x = 0.5f;
    } وإلا {
        x = event->موخه_X / (client_w - 1);
    }
    إذا (client_h <= 1) {
        y = 0.5f;
    } وإلا {
        y = event->موخه_Y / (client_h - 1);
    }

    SDL_SendTouch(0, deviceId, id, کړکۍ_معلومات_2->کړکۍ, SDL_EVENT_FINGER_CANCELED, x, y, 1.0f);
}

EMSCRIPTEN_KEEPALIVE فراغ Emscripten_Handle_اشاره_ګر_Leave(SDL_کړکۍ_معلومات *کړکۍ_معلومات_2, ثابت Emscripten_اشاره_ګر_Event *event)
{
    SDL_assert(event != عدم);
    إذا (event->اشاره_ګر_type == PTRTYPE_MOUSE) {
        Emscripten_HandleMouseFocus(کړکۍ_معلومات_2, event, false);
    } وإلا إذا (event->اشاره_ګر_type == PTRTYPE_PEN) {
        Emscripten_HandlePenLeave(کړکۍ_معلومات_2, event);
    } وإلا إذا (event->اشاره_ګر_type == PTRTYPE_TOUCH) {
        Emscripten_HandleTouchCancel(کړکۍ_معلومات_2, event);
    } وإلا {
        SDL_assert(!"Unexpected pointer event type");
    }
}

EMSCRIPTEN_KEEPALIVE فراغ Emscripten_Handle_اشاره_ګر_Generic(SDL_کړکۍ_معلومات *کړکۍ_معلومات_2, ثابت Emscripten_اشاره_ګر_Event *event)
{
    SDL_assert(event != عدم);
    Emscripten_Update_اشاره_ګر_From_Event(کړکۍ_معلومات_2, event);
}

ساكن فراغ Emscripten_prep_اشاره_ګر_event_callbacks(فراغ)
{
    MAIN_THREAD_EM_ASM({
        var SDL3 = Module['SDL3'];

        إذا (SDL3.make_اشاره_ګر_Event_CStruct === undefined) {
            SDL3.make_اشاره_ګر_Event_CStruct = function(کیڼ, سر, event) {
                var ptrtype = 0;
                إذا (event.اشاره_ګر_Type == "mouse") {
                    ptrtype = 1;
                } وإلا إذا (event.اشاره_ګر_Type == "touch") {
                    ptrtype = 2;
                } وإلا إذا (event.اشاره_ګر_Type == "pen") {
                    ptrtype = 3;
                } وإلا {
                    أرجع 0;
                }

                var ptr = _SDL_malloc($0);
                إذا (ptr != 0) {
                    var idx = SDL3.CPtr_منزل_Heap32_شاخص(ptr);
                    HEAP32[idx++] = ptrtype;
                    HEAP32[idx++] = event.اشاره_ګر_Id;
                    HEAP32[idx++] = (typeof(event.button) !== "undefined") ? event.button : -1;
                    HEAP32[idx++] = event.buttons;
                    HEAP32[idx++] = (event.type == "pointerdown") ? 1 : 0;
                    HEAPF32[idx++] = event.movementX;
                    HEAPF32[idx++] = event.movementY;
                    HEAPF32[idx++] = event.clientX - کیڼ;
                    HEAPF32[idx++] = event.clientY - سر;
                    إذا (ptrtype == 3) {
                        HEAPF32[idx++] = event.pressure;
                        HEAPF32[idx++] = event.tangentialPressure;
                        HEAPF32[idx++] = event.tiltX;
                        HEAPF32[idx++] = event.tiltY;
                        HEAPF32[idx++] = event.twist;
                    }
                }
                أرجع ptr;
            };
        }
    }, حجم (Emscripten_اشاره_ګر_Event));
}

ساكن فراغ Emscripten_سېټ_اشاره_ګر_event_callbacks(SDL_کړکۍ_معلومات *معلومات)
{
    Emscripten_prep_اشاره_ګر_event_callbacks();

    MAIN_THREAD_EM_ASM({
        var موخه = document.querySelector(UTF8_منزل_String($1));
        إذا (موخه) {
            var SDL3 = Module['SDL3'];
            var معلومات = $0;
            موخه.sdl_Event_Handler_اشاره_ګر_Enter = function(event) {
                var rect = موخه.getBoundingClientRect();
                var d = SDL3.make_اشاره_ګر_Event_CStruct(rect.کیڼ, rect.سر, event);
                إذا (d != 0)
                {
                    Emscripten_Handle_اشاره_ګر_Enter_2(SDL3.JSVar_منزل_CPtr(معلومات), d);
                    _SDL_free(d);
                }
            };
            موخه.sdl_Event_Handler_اشاره_ګر_Leave = function(event) {
                var rect = موخه.getBoundingClientRect();
                var d = SDL3.make_اشاره_ګر_Event_CStruct(rect.کیڼ, rect.سر, event);
                إذا (d != 0)
                {
                    Emscripten_Handle_اشاره_ګر_Leave_2(SDL3.JSVar_منزل_CPtr(معلومات), d);
                    _SDL_free(d);
                }
            };
            موخه.sdl_Event_Handler_اشاره_ګر_Generic = function(event) {
                var rect = موخه.getBoundingClientRect();
                var d = SDL3.make_اشاره_ګر_Event_CStruct(rect.کیڼ, rect.سر, event);
                إذا (d != 0)
                {
                    Emscripten_Handle_اشاره_ګر_Generic_2(SDL3.JSVar_منزل_CPtr(معلومات), d);
                    _SDL_free(d);
                }
            };

            موخه.style.touchAction = "none";  // or mobile devices will scroll as your touch moves across the element.
            موخه.جمع_کړه_Event_Listener("pointerenter", موخه.sdl_Event_Handler_اشاره_ګر_Enter);
            موخه.جمع_کړه_Event_Listener("pointerleave", موخه.sdl_Event_Handler_اشاره_ګر_Leave);
            موخه.جمع_کړه_Event_Listener("pointercancel", موخه.sdl_Event_Handler_اشاره_ګر_Leave);
            موخه.جمع_کړه_Event_Listener("pointerdown", موخه.sdl_Event_Handler_اشاره_ګر_Generic);
            موخه.جمع_کړه_Event_Listener("pointermove", موخه.sdl_Event_Handler_اشاره_ګر_Generic);
            موخه.جمع_کړه_Event_Listener("pointerup", موخه.sdl_Event_Handler_اشاره_ګر_Generic);
        }
    }, معلومات, معلومات->canvas_id);
}

ساكن فراغ Emscripten_unset_اشاره_ګر_event_callbacks(SDL_کړکۍ_معلومات *معلومات)
{
    MAIN_THREAD_EM_ASM({
        var موخه = document.querySelector(UTF8_منزل_String($0));
        إذا (موخه) {
            موخه.removeEventListener("pointerenter", موخه.sdl_Event_Handler_اشاره_ګر_Enter);
            موخه.removeEventListener("pointerleave", موخه.sdl_Event_Handler_اشاره_ګر_Leave);
            موخه.removeEventListener("pointercancel", موخه.sdl_Event_Handler_اشاره_ګر_Leave);
            موخه.removeEventListener("pointerdown", موخه.sdl_Event_Handler_اشاره_ګر_Generic);
            موخه.removeEventListener("pointermove", موخه.sdl_Event_Handler_اشاره_ګر_Generic);
            موخه.removeEventListener("pointerup", موخه.sdl_Event_Handler_اشاره_ګر_Generic);
            موخه.style.touchAction = "";  // let mobile devices scroll again as your touch moves across the element.
            موخه.sdl_Event_Handler_اشاره_ګر_Enter = undefined;
            موخه.sdl_Event_Handler_اشاره_ګر_Leave = undefined;
            موخه.sdl_Event_Handler_اشاره_ګر_Generic = undefined;
        }
    }, معلومات->canvas_id);
}

EMSCRIPTEN_KEEPALIVE فراغ Emscripten_Handle_Mouse_Button_پورته_Global(SDL_VideoDevice *device, ثابت Emscripten_اشاره_ګر_Event *event)
{
    SDL_assert(device != عدم);
    SDL_assert(event != عدم);
    إذا (event->اشاره_ګر_type == PTRTYPE_MOUSE) {
        لكل (SDL_کړکۍ *کړکۍ = device->windows; کړکۍ; کړکۍ = کړکۍ->بل) {
            Emscripten_HandleMouseButton(کړکۍ->دننی, event);
        }
    }
}

ساكن فراغ Emscripten_سېټ_global_mouseup_callback(SDL_VideoDevice *device)
{
    Emscripten_prep_اشاره_ګر_event_callbacks();

    MAIN_THREAD_EM_ASM({
        var موخه = document;
        إذا (موخه) {
            موخه.sdl_Event_Handler_Mouse_Button_پورته_Global = function(event) {
                var SDL3 = Module['SDL3'];
                var d = SDL3.make_اشاره_ګر_Event_CStruct(0, 0, event);
                إذا (d != 0)
                {
                    Emscripten_Handle_Mouse_Button_پورته_Global_2(SDL3.JSVar_منزل_CPtr($0), d);
                    _SDL_free(d);
                }
            };
            موخه.جمع_کړه_Event_Listener("pointerup", موخه.sdl_Event_Handler_Mouse_Button_پورته_Global);
        }
    }, device);
}

ساكن فراغ Emscripten_unset_global_mouseup_callback(SDL_VideoDevice *device)
{
    MAIN_THREAD_EM_ASM({
        var موخه = document;
        إذا (موخه) {
            موخه.removeEventListener("pointerup", موخه.sdl_Event_Handler_Mouse_Button_پورته_Global);
            موخه.sdl_Event_Handler_Mouse_Button_پورته_Global = undefined;
        }
    });
}

// IF YOU CHANGE THIS STRUCTURE, YOU NEED TO UPDATE THE JAVASCRIPT THAT FILLS IT IN: makeDropEventCStruct, below.
تعريفنوع بنية Emscripten_DropEvent
{
    صحيح x;
    صحيح y;
} Emscripten_DropEvent;

EMSCRIPTEN_KEEPALIVE فراغ Emscripten_SendDragEvent(SDL_کړکۍ_معلومات *کړکۍ_معلومات_2, ثابت Emscripten_DropEvent *event)
{
    SDL_SendDropPosition(کړکۍ_معلومات_2->کړکۍ, event->x, event->y);
}

EMSCRIPTEN_KEEPALIVE فراغ Emscripten_SendDragCompleteEvent(SDL_کړکۍ_معلومات *کړکۍ_معلومات_2)
{
    SDL_SendDropComplete(کړکۍ_معلومات_2->کړکۍ);
}

EMSCRIPTEN_KEEPALIVE فراغ Emscripten_Send_Drag_متن_Event(SDL_کړکۍ_معلومات *کړکۍ_معلومات_2, حرف *متن)
{
    SDL_Send_Drop_متن(کړکۍ_معلومات_2->کړکۍ, متن);
}

EMSCRIPTEN_KEEPALIVE فراغ Emscripten_SendDragFileEvent(SDL_کړکۍ_معلومات *کړکۍ_معلومات_2, حرف *filename)
{
    SDL_SendDropFile(کړکۍ_معلومات_2->کړکۍ, عدم, filename);
}

EM_JS_DEPS(dragndrop, "$writeArrayToMemory");

ساكن فراغ Emscripten_سېټ_drag_event_callbacks(SDL_کړکۍ_معلومات *معلومات)
{
    MAIN_THREAD_EM_ASM({
        var موخه = document.querySelector(UTF8_منزل_String($1));
        إذا (موخه) {
            var معلومات = $0;
            var SDL3 = Module['SDL3'];

            var makeDropEventCStruct = function(event) {
                var ptr = 0;
                ptr = _SDL_malloc($2);
                إذا (ptr != 0) {
                    var idx = ptr >> 2;
                    var rect = موخه.getBoundingClientRect();
                    HEAP32[idx++] = event.clientX - rect.کیڼ;
                    HEAP32[idx++] = event.clientY - rect.سر;
                }
                أرجع ptr;
            };

            SDL3.eventHandlerDropDragover = function(event) {
                event.preventDefault();
                var d = makeDropEventCStruct(event); إذا (d != 0) { _Emscripten_SendDragEvent(معلومات, d); _SDL_free(d); }
            };
            موخه.جمع_کړه_Event_Listener("dragover", SDL3.eventHandlerDropDragover);

            SDL3.drop_شمېر = 0;

            // FS.* functions throw exceptions when there are errors (such as the temp dir already existing),
            //  but we ignore all of these in a catch handler; you just won't get the drop event if there's a problem.
            try { FS.mkdir("/tmp/filedrop"); } catch (e) {}

            SDL3.eventHandlerDropDrop = function(event) {
                event.preventDefault();
                إذا (event.معلومات_Transfer.types.includes("text/plain")) {
                    let plain_متن = string_منزل_New_UTF8(event.معلومات_Transfer.get_معلومات("text/plain"));
                    Emscripten_Send_Drag_متن_Event_2(معلومات, plain_متن);
                    _Emscripten_force_free(plain_متن);
                } وإلا إذا (event.معلومات_Transfer.types.includes("Files")) {
                    let files_read = 0;
                    ثابت files_منزل_read = event.معلومات_Transfer.files.اوږدتیا;
                    لكل (let i = 0; i < files_منزل_read; i++) {
                        ثابت file = event.معلومات_Transfer.files.توکی(i);
                        ثابت file_reader = new FileReader();
                        file_reader.read_As_Array_بفر(file);
                        file_reader.onload = function(event) {
                            ثابت fs_dropdir = `/tmp/filedrop/${SDL3.drop_شمېر}`;
                            SDL3.drop_شمېر += 1;

                            ثابت fs_filepath = `${fs_dropdir}/${file.name}`;
                            ثابت c_fs_filepath = string_منزل_New_UTF8(fs_filepath);
                            ثابت contents_array8 = new Uint8Array(event.موخه.پایله);

                            try {
                                FS.mkdir(fs_dropdir);
                                var بهیر = FS.open(fs_filepath, "w");
                                FS.اكتب(بهیر, contents_array8, 0, contents_array8.اوږدتیا, 0);
                                FS.close(بهیر);
                                _Emscripten_SendDragFileEvent(معلومات, c_fs_filepath);
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
                        إذا (files_read === files_منزل_read) {
                            _Emscripten_SendDragCompleteEvent(معلومات);
                        }
                    }
                }
                _Emscripten_SendDragCompleteEvent(معلومات);
            };
            موخه.جمع_کړه_Event_Listener("drop", SDL3.eventHandlerDropDrop);

            SDL3.eventHandlerDropDragend = function(event) {
                event.preventDefault();
                _Emscripten_SendDragCompleteEvent(معلومات);
            };
            موخه.جمع_کړه_Event_Listener("dragend", SDL3.eventHandlerDropDragend);
            موخه.جمع_کړه_Event_Listener("dragleave", SDL3.eventHandlerDropDragend);
        }
    }, معلومات, معلومات->canvas_id, حجم (Emscripten_DropEvent));
}

ساكن فراغ Emscripten_unset_drag_event_callbacks(SDL_کړکۍ_معلومات *معلومات)
{
    MAIN_THREAD_EM_ASM({
        var موخه = document.querySelector(UTF8_منزل_String($0));
        إذا (موخه) {
            var SDL3 = Module['SDL3'];
            موخه.removeEventListener("dragleave", SDL3.eventHandlerDropDragend);
            موخه.removeEventListener("dragend", SDL3.eventHandlerDropDragend);
            موخه.removeEventListener("drop", SDL3.eventHandlerDropDrop);
            SDL3.drop_شمېر = undefined;

            function recursive_remove(dirpath) {
                FS.readdir(dirpath).forEach((filename) => {
                    ثابت p = `${dirpath}/${filename}`;
                    ثابت p_s = FS.stat(p);
                    إذا (FS.isFile(p_s.ډېرپېښ)) {
                        FS.unlink(p);
                    } وإلا إذا (FS.isDir(p)) {
                        recursive_remove(p);
                    }
                });
                FS.rmdir(dirpath);
            }("/tmp/filedrop");

            FS.rmdir("/tmp/filedrop");
            موخه.removeEventListener("dragover", SDL3.eventHandlerDropDragover);
            SDL3.eventHandlerDropDragover = undefined;
            SDL3.eventHandlerDropDrop = undefined;
            SDL3.eventHandlerDropDragend = undefined;
        }
    }, معلومات->canvas_id);
}

ساكن ثابت حرف *Emscripten_Get_Keyboard_موخه_Element(ثابت حرف *موخه)
{
    إذا (SDL_strcmp(موخه, "#none") == 0) {
        أرجع عدم;
    } وإلا إذا (SDL_strcmp(موخه, "#window") == 0) {
        أرجع EMSCRIPTEN_EVENT_موخه_کړکۍ;
    } وإلا إذا (SDL_strcmp(موخه, "#document") == 0) {
        أرجع EMSCRIPTEN_EVENT_موخه_DOCUMENT;
    } وإلا إذا (SDL_strcmp(موخه, "#screen") == 0) {
        أرجع EMSCRIPTEN_EVENT_موخه_SCREEN;
    }

    أرجع موخه;
}

فراغ Emscripten_ثبتوونکی_Global_Event_Handlers(SDL_VideoDevice *device)
{
    Emscripten_سېټ_global_mouseup_callback(device);

    emscripten_سېټ_focus_callback(EMSCRIPTEN_EVENT_موخه_کړکۍ, device, 0, Emscripten_HandleFocus);
    emscripten_سېټ_blur_callback(EMSCRIPTEN_EVENT_موخه_کړکۍ, device, 0, Emscripten_HandleFocus);

    emscripten_سېټ_pointerlockchange_callback(EMSCRIPTEN_EVENT_موخه_DOCUMENT, device, 0, Emscripten_Handle_اشاره_ګر_قلف_Change_Global);

    emscripten_سېټ_fullscreenchange_callback(EMSCRIPTEN_EVENT_موخه_DOCUMENT, device, 0, Emscripten_HandleFullscreenChangeGlobal);

    emscripten_سېټ_resize_callback(EMSCRIPTEN_EVENT_موخه_کړکۍ, device, 0, Emscripten_HandleResizeGlobal);
}

فراغ Emscripten_UnregisterGlobalEventHandlers(SDL_VideoDevice *device)
{
    Emscripten_unset_global_mouseup_callback(device);

    emscripten_سېټ_focus_callback(EMSCRIPTEN_EVENT_موخه_کړکۍ, عدم, 0, عدم);
    emscripten_سېټ_blur_callback(EMSCRIPTEN_EVENT_موخه_کړکۍ, عدم, 0, عدم);

    emscripten_سېټ_pointerlockchange_callback(EMSCRIPTEN_EVENT_موخه_DOCUMENT, عدم, 0, عدم);

    emscripten_سېټ_fullscreenchange_callback(EMSCRIPTEN_EVENT_موخه_DOCUMENT, عدم, 0, عدم);

    emscripten_سېټ_resize_callback(EMSCRIPTEN_EVENT_موخه_کړکۍ, عدم, 0, عدم);
}

EMSCRIPTEN_KEEPALIVE فراغ Emscripten_Handle_قلف_کلیګانې_Check(SDL_کړکۍ_معلومات *کړکۍ_معلومات_2, EM_BOOL capslock, EM_BOOL numlock, EM_BOOL scrolllock)
{
    ثابت SDL_Keymod new_mods = (capslock ? SDL_KMOD_CAPS : 0) | (numlock ? SDL_KMOD_عدد : 0) | (scrolllock ? SDL_KMOD_SCROLL : 0);
    SDL_Keymod modstate = SDL_GetModState();
    إذا ((modstate & (SDL_KMOD_CAPS|SDL_KMOD_عدد|SDL_KMOD_SCROLL)) != new_mods) {
        modstate &= ~(SDL_KMOD_CAPS|SDL_KMOD_عدد|SDL_KMOD_SCROLL);
        modstate |= new_mods;
        SDL_سېټ_Mod_State(modstate);
    }
}

فراغ Emscripten_ثبتوونکی_Event_Handlers(SDL_کړکۍ_معلومات *معلومات)
{
    ثابت حرف *کلی_Element;

    // There is only one window and that window is the canvas
    emscripten_سېټ_wheel_callback(معلومات->canvas_id, معلومات, 0, Emscripten_HandleWheel);

    emscripten_سېټ_orientationchange_callback(معلومات, 0, Emscripten_HandleOrientationChange);

    کلی_Element = Emscripten_Get_Keyboard_موخه_Element(معلومات->keyboard_element);
    إذا (کلی_Element) {
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
        emscripten_سېټ_keydown_callback(کلی_Element, عدم, 0, عدم);
        emscripten_سېټ_keyup_callback(کلی_Element, عدم, 0, عدم);
        emscripten_سېټ_keypress_callback(کلی_Element, عدم, 0, عدم);

        MAIN_THREAD_EM_ASM_INT({
            var معلومات = $0;
            // our keymod state can get confused in various ways (changed capslock when browser didn't have focus, etc), and you can't query the current
            //  state from the DOM, outside of a keyboard event, so catch keypresses globally and reset mod state if it's unexpectedly wrong. Best we can do.
            //  Note that this thing _only_ adjusts the lock keys if necessary; the real SDL keypress handling happens elsewhere.

            // Remove any prior listener first -- `addEventListener` does not deduplicate either.
            إذا (document.sdl_Event_Handler_قلف_کلیګانې_Check) {
                document.removeEventListener("keydown", document.sdl_Event_Handler_قلف_کلیګانې_Check);
            }

            document.sdl_Event_Handler_قلف_کلیګانې_Check = function(event) {
                // don't try to adjust the state on the actual lock key presses; the normal key handler will catch that and adjust.
                إذا ((event.کلی != "CapsLock") && (event.کلی != "NumLock") && (event.کلی != "ScrollLock"))
                {
                    Emscripten_Handle_قلف_کلیګانې_Check_2(Module['SDL3'].JSVar_منزل_CPtr(معلومات), event.getModifierState("CapsLock"), event.getModifierState("NumLock"), event.getModifierState("ScrollLock"));
                }
            };
            document.جمع_کړه_Event_Listener("keydown", document.sdl_Event_Handler_قلف_کلیګانې_Check);
        }, معلومات);
        emscripten_سېټ_keydown_callback(کلی_Element, معلومات, 0, Emscripten_Handle_کلی);
        emscripten_سېټ_keyup_callback(کلی_Element, معلومات, 0, Emscripten_Handle_کلی);
        emscripten_سېټ_keypress_callback(کلی_Element, معلومات, 0, Emscripten_Handle_کلی_Press);
    }

    emscripten_سېټ_visibilitychange_callback(معلومات, 0, Emscripten_HandleVisibilityChange);

    emscripten_سېټ_beforeunload_callback(معلومات, Emscripten_HandleBeforeUnload);

    // !!! FIXME: currently Emscripten doesn't have a Pointer Events functions like emscripten_set_*_callback, but we should use those when they do:
    // !!! FIXME:  https://github.com/emscripten-core/emscripten/issues/7278#issuecomment-2280024621
    Emscripten_سېټ_اشاره_ګر_event_callbacks(معلومات);

    // !!! FIXME: currently Emscripten doesn't have a Drop Events functions like emscripten_set_*_callback, but we should use those when they do:
    Emscripten_سېټ_drag_event_callbacks(معلومات);
}

فراغ Emscripten_UnregisterEventHandlers(SDL_کړکۍ_معلومات *معلومات)
{
    ثابت حرف *کلی_Element;

    // !!! FIXME: currently Emscripten doesn't have a Drop Events functions like emscripten_set_*_callback, but we should use those when they do:
    Emscripten_unset_drag_event_callbacks(معلومات);

    // !!! FIXME: currently Emscripten doesn't have a Pointer Events functions like emscripten_set_*_callback, but we should use those when they do:
    // !!! FIXME:  https://github.com/emscripten-core/emscripten/issues/7278#issuecomment-2280024621
    Emscripten_unset_اشاره_ګر_event_callbacks(معلومات);

    // only works due to having one window
    emscripten_سېټ_wheel_callback(معلومات->canvas_id, عدم, 0, عدم);

    emscripten_سېټ_orientationchange_callback(عدم, 0, عدم);

    کلی_Element = Emscripten_Get_Keyboard_موخه_Element(معلومات->keyboard_element);
    إذا (کلی_Element) {
        emscripten_سېټ_keydown_callback(کلی_Element, عدم, 0, عدم);
        emscripten_سېټ_keyup_callback(کلی_Element, عدم, 0, عدم);
        emscripten_سېټ_keypress_callback(کلی_Element, عدم, 0, عدم);
        MAIN_THREAD_EM_ASM_INT({
            document.removeEventListener("keydown", document.sdl_Event_Handler_قلف_کلیګانې_Check);
        });
    }

    emscripten_سېټ_visibilitychange_callback(عدم, 0, عدم);

    emscripten_سېټ_beforeunload_callback(عدم, عدم);
}

#د_که_پای // SDL_VIDEO_DRIVER_EMSCRIPTEN

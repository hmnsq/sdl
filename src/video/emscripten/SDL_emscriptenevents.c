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

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_EMSCRIPTEN

#ਅਨ੍ਤਰ੍ਭਾਵ <emscripten/html5.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <emscripten/dom_pk_codes.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_dropevents_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_events_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_keyboard_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_touch_c.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_emscriptenevents.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_emscriptenvideo.h"

/*
Emscripten PK code to scancode
https://developer.mozilla.org/en-US/docs/Web/API/KeyboardEvent
https://developer.mozilla.org/en-US/docs/Web/API/KeyboardEvent/code
*/
ਸਥਿਰ ਅਚਲ SDL_Scancode emscripten_scancode_ਸਾਰਣੀ[] = {
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

ਸਥਿਰ SDL_Scancode Emscripten_Map_ਜਾਂਚ_ਕੋਡ(ਅਚਲ ਅੱਖਰ *ਕੋਡ)
{
    ਅਚਲ DOM_PK_ਕੋਡ_TYPE pk_ਕੋਡ = emscripten_compute_dom_pk_ਕੋਡ(ਕੋਡ);
    ਜੇ (pk_ਕੋਡ < SDL_arraysize(emscripten_scancode_ਸਾਰਣੀ)) {
        ਵਾਪਸ emscripten_scancode_ਸਾਰਣੀ[pk_ਕੋਡ];
    }

    ਚੋਣ (pk_ਕੋਡ) {
    ਹਾਲਤ DOM_PK_PASTE:
        ਵਾਪਸ SDL_SCANCODE_PASTE;
    ਹਾਲਤ DOM_PK_MEDIA_TRACK_ਪਿਛਲਾ:
        ਵਾਪਸ SDL_SCANCODE_MEDIA_ਪਿਛਲਾ_TRACK;
    ਹਾਲਤ DOM_PK_CUT:
        ਵਾਪਸ SDL_SCANCODE_CUT;
    ਹਾਲਤ DOM_PK_COPY:
        ਵਾਪਸ SDL_SCANCODE_COPY;
    ਹਾਲਤ DOM_PK_MEDIA_TRACK_ਅਗਲਾ:
        ਵਾਪਸ SDL_SCANCODE_MEDIA_ਅਗਲਾ_TRACK;
    ਹਾਲਤ DOM_PK_NUMPAD_ENTER:
        ਵਾਪਸ SDL_SCANCODE_KP_ENTER;
    ਹਾਲਤ DOM_PK_CONTROL_ਸੱਜਾ:
        ਵਾਪਸ SDL_SCANCODE_RCTRL;
    ਹਾਲਤ DOM_PK_AUDIO_VOLUME_MUTE:
        ਵਾਪਸ SDL_SCANCODE_MUTE;
    ਹਾਲਤ DOM_PK_MEDIA_PLAY_PAUSE:
        ਵਾਪਸ SDL_SCANCODE_MEDIA_PLAY_PAUSE;
    ਹਾਲਤ DOM_PK_MEDIA_STOP:
        ਵਾਪਸ SDL_SCANCODE_MEDIA_STOP;
    ਹਾਲਤ DOM_PK_EJECT:
        ਵਾਪਸ SDL_SCANCODE_MEDIA_EJECT;
    ਹਾਲਤ DOM_PK_AUDIO_VOLUME_ਥੱਲੇ:
        ਵਾਪਸ SDL_SCANCODE_VOLUMEDOWN;
    ਹਾਲਤ DOM_PK_AUDIO_VOLUME_ਉੱਪਰ:
        ਵਾਪਸ SDL_SCANCODE_VOLUMEUP;
    ਹਾਲਤ DOM_PK_BROWSER_HOME:
        ਵਾਪਸ SDL_SCANCODE_AC_HOME;
    ਹਾਲਤ DOM_PK_NUMPAD_DIVIDE:
        ਵਾਪਸ SDL_SCANCODE_KP_DIVIDE;
    ਹਾਲਤ DOM_PK_ALT_ਸੱਜਾ:
        ਵਾਪਸ SDL_SCANCODE_RALT;
    ਹਾਲਤ DOM_PK_HELP:
        ਵਾਪਸ SDL_SCANCODE_HELP;
    ਹਾਲਤ DOM_PK_ਅੰਕ_ਤਾਲਾ:
        ਵਾਪਸ SDL_SCANCODE_NUMLOCKCLEAR;
    ਹਾਲਤ DOM_PK_HOME:
        ਵਾਪਸ SDL_SCANCODE_HOME;
    ਹਾਲਤ DOM_PK_ARROW_ਉੱਪਰ:
        ਵਾਪਸ SDL_SCANCODE_ਉੱਪਰ;
    ਹਾਲਤ DOM_PK_ਪੰਨਾ_ਉੱਪਰ:
        ਵਾਪਸ SDL_SCANCODE_PAGEUP;
    ਹਾਲਤ DOM_PK_ARROW_ਖੱਬਾ:
        ਵਾਪਸ SDL_SCANCODE_ਖੱਬਾ;
    ਹਾਲਤ DOM_PK_ARROW_ਸੱਜਾ:
        ਵਾਪਸ SDL_SCANCODE_ਸੱਜਾ;
    ਹਾਲਤ DOM_PK_ਸਿਰਾ:
        ਵਾਪਸ SDL_SCANCODE_ਸਿਰਾ;
    ਹਾਲਤ DOM_PK_ARROW_ਥੱਲੇ:
        ਵਾਪਸ SDL_SCANCODE_ਥੱਲੇ;
    ਹਾਲਤ DOM_PK_ਪੰਨਾ_ਥੱਲੇ:
        ਵਾਪਸ SDL_SCANCODE_PAGEDOWN;
    ਹਾਲਤ DOM_PK_ਪਾਓ:
        ਵਾਪਸ SDL_SCANCODE_ਪਾਓ;
    ਹਾਲਤ DOM_PK_DELETE:
        ਵਾਪਸ SDL_SCANCODE_DELETE;
    ਹਾਲਤ DOM_PK_META_ਖੱਬਾ:
        ਵਾਪਸ SDL_SCANCODE_LGUI;
    ਹਾਲਤ DOM_PK_META_ਸੱਜਾ:
        ਵਾਪਸ SDL_SCANCODE_RGUI;
    ਹਾਲਤ DOM_PK_CONTEXT_MENU:
        ਵਾਪਸ SDL_SCANCODE_APPLICATION;
    ਹਾਲਤ DOM_PK_POWER:
        ਵਾਪਸ SDL_SCANCODE_POWER;
    ਹਾਲਤ DOM_PK_BROWSER_ਖੋਜ:
        ਵਾਪਸ SDL_SCANCODE_AC_ਖੋਜ;
    ਹਾਲਤ DOM_PK_BROWSER_FAVORITES:
        ਵਾਪਸ SDL_SCANCODE_AC_BOOKMARKS;
    ਹਾਲਤ DOM_PK_BROWSER_REFRESH:
        ਵਾਪਸ SDL_SCANCODE_AC_REFRESH;
    ਹਾਲਤ DOM_PK_BROWSER_STOP:
        ਵਾਪਸ SDL_SCANCODE_AC_STOP;
    ਹਾਲਤ DOM_PK_BROWSER_FORWARD:
        ਵਾਪਸ SDL_SCANCODE_AC_FORWARD;
    ਹਾਲਤ DOM_PK_BROWSER_ਪਿੱਠ:
        ਵਾਪਸ SDL_SCANCODE_AC_ਪਿੱਠ;
    ਹਾਲਤ DOM_PK_MEDIA_SELECT:
        ਵਾਪਸ SDL_SCANCODE_MEDIA_SELECT;
    }

    ਵਾਪਸ SDL_SCANCODE_UNKNOWN;
}

ਸਥਿਰ SDL_ਖਿੜਕੀ *Emscripten_Get_Focused_ਖਿੜਕੀ(SDL_VideoDevice *device)
{
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ;
    ਲਈ (ਖਿੜਕੀ = device->windows; ਖਿੜਕੀ; ਖਿੜਕੀ = ਖਿੜਕੀ->ਅਗਲਾ) {
        SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *wdata = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;

        ਅਚਲ ਪੂਰਨ focused = MAIN_THREAD_EM_ASM_INT({
            var id = UTF8_ਮੰਜ਼ਿਲ_String($0);
            try
            {
                var canvas = document.querySelector(id);
                ਜੇ (canvas) {
                    ਵਾਪਸ canvas === document.ਸਰਗਰਮ_Element;
                }
            }
            catch (e)
            {
                // querySelector throws if not a valid selector
            }
            ਵਾਪਸ false;
        }, wdata->canvas_id);

        ਜੇ (focused) {
            ਰੋਕੋ;
        }
    }
    // If the DOM is focused, then at least one canvas in the DOM should be considered focused.
    // So in this case, just assume that the first canvas is focused.
    ਜੇ (!ਖਿੜਕੀ) {
        ਅਚਲ ਪੂਰਨ focused = MAIN_THREAD_EM_ASM_INT({
            ਵਾਪਸ document.hasFocus();
        });
        ਜੇ (focused) {
            ਖਿੜਕੀ = device->windows;
        }
    }
    ਵਾਪਸ ਖਿੜਕੀ;
}

ਸਥਿਰ EM_BOOL Emscripten_Handle_ਸੂਚਕ_ਤਾਲਾ_Change(ਪੂਰਨ eventType, ਅਚਲ EmscriptenPointerlockChangeEvent *changeEvent, ਖਾਲੀ *user_ਅੰਕੜੇ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2 = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)user_ਅੰਕੜੇ;
    // keep track of lock losses, so we can regrab if/when appropriate.
    ਖਿੜਕੀ_ਅੰਕੜੇ_2->has_ਸੂਚਕ_ਤਾਲਾ = changeEvent->is_ਸਰਗਰਮ;
    ਵਾਪਸ 0;
}

ਸਥਿਰ EM_BOOL Emscripten_Handle_ਸੂਚਕ_ਤਾਲਾ_Change_Global(ਪੂਰਨ eventType, ਅਚਲ EmscriptenPointerlockChangeEvent *changeEvent, ਖਾਲੀ *user_ਅੰਕੜੇ)
{
    SDL_VideoDevice *device = user_ਅੰਕੜੇ;
    bool prevent_default = false;
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ;

    ਲਈ (ਖਿੜਕੀ = device->windows; ਖਿੜਕੀ; ਖਿੜਕੀ = ਖਿੜਕੀ->ਅਗਲਾ) {
        prevent_default |= Emscripten_Handle_ਸੂਚਕ_ਤਾਲਾ_Change(eventType, changeEvent, ਖਿੜਕੀ->ਅੰਦਰੂਨੀ);
    }

    ਵਾਪਸ prevent_default;
}

ਸਥਿਰ EM_BOOL Emscripten_HandleWheel(ਪੂਰਨ eventType, ਅਚਲ EmscriptenWheelEvent *wheelEvent, ਖਾਲੀ *user_ਅੰਕੜੇ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2 = user_ਅੰਕੜੇ;

    ਦਸ਼ਮਲਵ deltaY = wheelEvent->deltaY;
    ਦਸ਼ਮਲਵ deltaX = wheelEvent->deltaX;

    ਚੋਣ (wheelEvent->delta_ਬਹੁਲਕ) {
    ਹਾਲਤ DOM_DELTA_PIXEL:
        deltaX /= 100; // 100 pixels make up a step
        deltaY /= 100; // 100 pixels make up a step
        ਰੋਕੋ;
    ਹਾਲਤ DOM_DELTA_ਸਤਰ:
        deltaX /= 3; // 3 lines make up a step
        deltaY /= 3; // 3 lines make up a step
        ਰੋਕੋ;
    ਹਾਲਤ DOM_DELTA_ਪੰਨਾ:
        deltaX *= 80; // A page makes up 80 steps
        deltaY *= 80; // A page makes up 80 steps
        ਰੋਕੋ;
    }

    SDL_SendMouseWheel(0, ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ, SDL_DEFAULT_MOUSE_ID, deltaX, -deltaY, SDL_MOUSEWHEEL_ਸਾਧਾਰਨ);
    ਵਾਪਸ SDL_EventEnabled(SDL_EVENT_MOUSE_WHEEL);
}

ਸਥਿਰ EM_BOOL Emscripten_HandleFocus(ਪੂਰਨ eventType, ਅਚਲ EmscriptenFocusEvent *focusEvent, ਖਾਲੀ *user_ਅੰਕੜੇ)
{
    SDL_VideoDevice *device = user_ਅੰਕੜੇ;
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = Emscripten_Get_Focused_ਖਿੜਕੀ(device);

    SDL_EventType sdl_event_type;

    /* If the user switches away while keys are pressed (such as
     * via Alt+Tab), key release events won't be received. */
    ਜੇ (eventType == EMSCRIPTEN_EVENT_BLUR) {
        SDL_ResetKeyboard();
    }

    sdl_event_type = (eventType == EMSCRIPTEN_EVENT_FOCUS) ? SDL_EVENT_ਖਿੜਕੀ_FOCUS_GAINED : SDL_EVENT_ਖਿੜਕੀ_FOCUS_ਗੁਆਚਾ;
    SDL_ਸੈੱਟ_Keyboard_Focus(sdl_event_type == SDL_EVENT_ਖਿੜਕੀ_FOCUS_GAINED ? ਖਿੜਕੀ : ਨਿਰਾ);
    ਵਾਪਸ SDL_EventEnabled(sdl_event_type);
}

ਸਥਿਰ bool Is_Function_ਕੁੰਜੀ(SDL_Scancode scancode)
{
    ਜੇ (scancode >= SDL_SCANCODE_F1 && scancode <= SDL_SCANCODE_F12) {
        ਵਾਪਸ true;
    }
    ਜੇ (scancode >= SDL_SCANCODE_F13 && scancode <= SDL_SCANCODE_F24) {
        ਵਾਪਸ true;
    }
    ਵਾਪਸ false;
}

/* This is a great tool to see web keyboard events live:
 * https://w3c.github.io/uievents/tools/key-event-viewer.html
 */
ਸਥਿਰ EM_BOOL Emscripten_Handle_ਕੁੰਜੀ(ਪੂਰਨ eventType, ਅਚਲ EmscriptenKeyboardEvent *ਕੁੰਜੀ_Event, ਖਾਲੀ *user_ਅੰਕੜੇ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2 = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)user_ਅੰਕੜੇ;
    SDL_Scancode scancode = Emscripten_Map_ਜਾਂਚ_ਕੋਡ(ਕੁੰਜੀ_Event->ਕੋਡ);
    SDL_Keycode keycode = SDLK_UNKNOWN;
    bool prevent_default = false;
    bool is_nav_ਕੁੰਜੀ = false;

    ਜੇ (scancode == SDL_SCANCODE_UNKNOWN) {
        ਜੇ (SDL_strcmp(ਕੁੰਜੀ_Event->ਕੁੰਜੀ, "Sleep") == 0) {
            scancode = SDL_SCANCODE_SLEEP;
        } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(ਕੁੰਜੀ_Event->ਕੁੰਜੀ, "ChannelUp") == 0) {
            scancode = SDL_SCANCODE_CHANNEL_INCREMENT;
        } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(ਕੁੰਜੀ_Event->ਕੁੰਜੀ, "ChannelDown") == 0) {
            scancode = SDL_SCANCODE_CHANNEL_DECREMENT;
        } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(ਕੁੰਜੀ_Event->ਕੁੰਜੀ, "MediaPlay") == 0) {
            scancode = SDL_SCANCODE_MEDIA_PLAY;
        } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(ਕੁੰਜੀ_Event->ਕੁੰਜੀ, "MediaPause") == 0) {
            scancode = SDL_SCANCODE_MEDIA_PAUSE;
        } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(ਕੁੰਜੀ_Event->ਕੁੰਜੀ, "MediaRecord") == 0) {
            scancode = SDL_SCANCODE_MEDIA_ਰਿਕਾਰਡ;
        } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(ਕੁੰਜੀ_Event->ਕੁੰਜੀ, "MediaFastForward") == 0) {
            scancode = SDL_SCANCODE_MEDIA_FAST_FORWARD;
        } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(ਕੁੰਜੀ_Event->ਕੁੰਜੀ, "MediaRewind") == 0) {
            scancode = SDL_SCANCODE_MEDIA_REWIND;
        } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(ਕੁੰਜੀ_Event->ਕੁੰਜੀ, "Close") == 0) {
            scancode = SDL_SCANCODE_AC_CLOSE;
        } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(ਕੁੰਜੀ_Event->ਕੁੰਜੀ, "New") == 0) {
            scancode = SDL_SCANCODE_AC_NEW;
        } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(ਕੁੰਜੀ_Event->ਕੁੰਜੀ, "Open") == 0) {
            scancode = SDL_SCANCODE_AC_OPEN;
        } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(ਕੁੰਜੀ_Event->ਕੁੰਜੀ, "Print") == 0) {
            scancode = SDL_SCANCODE_AC_PRINT;
        } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(ਕੁੰਜੀ_Event->ਕੁੰਜੀ, "Save") == 0) {
            scancode = SDL_SCANCODE_AC_SAVE;
        } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(ਕੁੰਜੀ_Event->ਕੁੰਜੀ, "Props") == 0) {
            scancode = SDL_SCANCODE_AC_PROPERTIES;
        }
    }

    ਜੇ (scancode == SDL_SCANCODE_UNKNOWN) {
        // KaiOS Left Soft Key and Right Soft Key, they act as OK/Next/Menu and Cancel/Back/Clear
        ਜੇ (SDL_strcmp(ਕੁੰਜੀ_Event->ਕੁੰਜੀ, "SoftLeft") == 0) {
            scancode = SDL_SCANCODE_AC_FORWARD;
        } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(ਕੁੰਜੀ_Event->ਕੁੰਜੀ, "SoftRight") == 0) {
            scancode = SDL_SCANCODE_AC_ਪਿੱਠ;
        }
    }

    ਜੇ (ਕੁੰਜੀ_Event->location == 0 && SDL_utf8strlen(ਕੁੰਜੀ_Event->ਕੁੰਜੀ) == 1) {
        ਅਚਲ ਅੱਖਰ *ਕੁੰਜੀ = ਕੁੰਜੀ_Event->ਕੁੰਜੀ;
        keycode = SDL_ਕਦਮ_UTF8(&ਕੁੰਜੀ, ਨਿਰਾ);
        ਜੇ (keycode == SDL_INVALID_UNICODE_CODEPOINT) {
            keycode = SDLK_UNKNOWN;
        }
    }

    ਜੇ (keycode != SDLK_UNKNOWN) {
        prevent_default = SDL_Send_Keyboard_ਕੁੰਜੀ_And_Keycode(0, SDL_DEFAULT_KEYBOARD_ID, 0, scancode, keycode, (eventType == EMSCRIPTEN_EVENT_KEYDOWN));
    } ਨਹੀਂਤਾਂ {
        prevent_default = SDL_Send_Keyboard_ਕੁੰਜੀ(0, SDL_DEFAULT_KEYBOARD_ID, 0, scancode, (eventType == EMSCRIPTEN_EVENT_KEYDOWN));
    }

    /* if TEXTINPUT events are enabled we can't prevent keydown or we won't get keypress
     * we need to ALWAYS prevent backspace and tab otherwise chrome takes action and does bad navigation UX
     */
    ਜੇ ((scancode == SDL_SCANCODE_BACKSPACE) ||
        (scancode == SDL_SCANCODE_TAB) ||
        (scancode == SDL_SCANCODE_ਖੱਬਾ) ||
        (scancode == SDL_SCANCODE_ਉੱਪਰ) ||
        (scancode == SDL_SCANCODE_ਸੱਜਾ) ||
        (scancode == SDL_SCANCODE_ਥੱਲੇ) ||
        Is_Function_ਕੁੰਜੀ(scancode) ||
        ਕੁੰਜੀ_Event->ctrl_ਕੁੰਜੀ) {
        is_nav_ਕੁੰਜੀ = true;
    }

    ਜੇ ((eventType == EMSCRIPTEN_EVENT_KEYDOWN) && SDL_ਪਾਠ_ਨਿਵੇਸ਼_ਸਰਗਰਮ(ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ) && !is_nav_ਕੁੰਜੀ) {
        prevent_default = false;
    }

    ਵਾਪਸ prevent_default;
}

ਸਥਿਰ EM_BOOL Emscripten_Handle_ਕੁੰਜੀ_Press(ਪੂਰਨ eventType, ਅਚਲ EmscriptenKeyboardEvent *ਕੁੰਜੀ_Event, ਖਾਲੀ *user_ਅੰਕੜੇ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2 = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *)user_ਅੰਕੜੇ;

    ਜੇ (SDL_ਪਾਠ_ਨਿਵੇਸ਼_ਸਰਗਰਮ(ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ)) {
        ਜੇ (SDL_utf8strlen(ਕੁੰਜੀ_Event->ਕੁੰਜੀ) == 1) {
            SDL_Send_Keyboard_ਪਾਠ(ਕੁੰਜੀ_Event->ਕੁੰਜੀ);
            ਵਾਪਸ EM_TRUE;
        }
    }
    ਵਾਪਸ EM_FALSE;
}

ਸਥਿਰ EM_BOOL Emscripten_HandleFullscreenChange(ਪੂਰਨ eventType, ਅਚਲ EmscriptenFullscreenChangeEvent *fullscreenChangeEvent, ਖਾਲੀ *user_ਅੰਕੜੇ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2 = user_ਅੰਕੜੇ;

    ਖਿੜਕੀ_ਅੰਕੜੇ_2->fullscreen_change_ਵਿੱਚ_ਤਰੱਕੀ = false;

    ਜੇ (fullscreenChangeEvent->isFullscreen) {
        SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_ENTER_FULLSCREEN, 0, 0);
        ਖਿੜਕੀ_ਅੰਕੜੇ_2->fullscreen_ਬਹੁਲਕ_flags = 0;
    } ਨਹੀਂਤਾਂ {
        SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_LEAVE_FULLSCREEN, 0, 0);
    }

    SDL_Update_Fullscreen_ਬਹੁਲਕ(ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ, fullscreenChangeEvent->isFullscreen, false);

    ਵਾਪਸ 0;
}

ਸਥਿਰ EM_BOOL Emscripten_HandleFullscreenChangeGlobal(ਪੂਰਨ eventType, ਅਚਲ EmscriptenFullscreenChangeEvent *fullscreenChangeEvent, ਖਾਲੀ *user_ਅੰਕੜੇ)
{
    SDL_VideoDevice *device = user_ਅੰਕੜੇ;
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = ਨਿਰਾ;
    ਲਈ (ਖਿੜਕੀ = device->windows; ਖਿੜਕੀ != ਨਿਰਾ; ਖਿੜਕੀ = ਖਿੜਕੀ->ਅਗਲਾ) {
        ਅਚਲ ਅੱਖਰ *canvas_id = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ->canvas_id;
        ਜੇ (*canvas_id == '#') {
            canvas_id++;
        }
        ਜੇ (SDL_strcmp(fullscreenChangeEvent->id, canvas_id) == 0) {
            ਰੋਕੋ;  // this is the window.
        }
    }

    ਜੇ (ਖਿੜਕੀ) {
        ਵਾਪਸ Emscripten_HandleFullscreenChange(eventType, fullscreenChangeEvent, ਖਿੜਕੀ->ਅੰਦਰੂਨੀ);
    }

    ਵਾਪਸ EM_FALSE;
}

ਸਥਿਰ EM_BOOL Emscripten_HandleResize(ਪੂਰਨ eventType, ਅਚਲ EmscriptenUiEvent *uiEvent, ਖਾਲੀ *user_ਅੰਕੜੇ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2 = user_ਅੰਕੜੇ;

    bool force = false;

    // update pixel ratio
    ਜੇ (ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_ਉੱਚਾ_PIXEL_DENSITY) {
        ਜੇ (ਖਿੜਕੀ_ਅੰਕੜੇ_2->pixel_ਅਨੁਪਾਤ != emscripten_get_device_pixel_ਅਨੁਪਾਤ()) {
            ਖਿੜਕੀ_ਅੰਕੜੇ_2->pixel_ਅਨੁਪਾਤ = emscripten_get_device_pixel_ਅਨੁਪਾਤ();
            force = true;
        }
    }

    ਅਚਲ bool fill_document = (Emscripten_fill_document_ਖਿੜਕੀ == ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ);
    ਅਚਲ bool fullscreen = (ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_FULLSCREEN) != 0;  // fullscreen windows can resize on Emscripten, and the canvas should fill it.
    ਅਚਲ bool resizable = (ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_RESIZABLE) != 0;
    ਜੇ (fill_document || fullscreen || resizable) {
        ਦੁੱਗਣਾ w, h;
        ਜੇ (fill_document || fullscreen) {
            w = (ਦੁੱਗਣਾ) uiEvent->ਖਿੜਕੀ_Inner_ਚੌੜਾਈ;
            h = (ਦੁੱਗਣਾ) uiEvent->ਖਿੜਕੀ_Inner_ਉਚਾਈ;
        } ਨਹੀਂਤਾਂ {
            SDL_assert(ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_RESIZABLE);
            w = ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ->w;
            h = ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ->h;
            // this will only work if the canvas size is set through css
            ਜੇ (ਖਿੜਕੀ_ਅੰਕੜੇ_2->external_ਮਾਪ) {
                emscripten_get_element_css_ਮਾਪ(ਖਿੜਕੀ_ਅੰਕੜੇ_2->canvas_id, &w, &h);
            }
        }

        emscripten_ਸੈੱਟ_canvas_element_ਮਾਪ(ਖਿੜਕੀ_ਅੰਕੜੇ_2->canvas_id, SDL_lroundf(w * ਖਿੜਕੀ_ਅੰਕੜੇ_2->pixel_ਅਨੁਪਾਤ), SDL_lroundf(h * ਖਿੜਕੀ_ਅੰਕੜੇ_2->pixel_ਅਨੁਪਾਤ));

        // set_canvas_size unsets this
        ਜੇ (!ਖਿੜਕੀ_ਅੰਕੜੇ_2->external_ਮਾਪ && ਖਿੜਕੀ_ਅੰਕੜੇ_2->pixel_ਅਨੁਪਾਤ != 1.0f) {
            emscripten_ਸੈੱਟ_element_css_ਮਾਪ(ਖਿੜਕੀ_ਅੰਕੜੇ_2->canvas_id, w, h);
        }

        ਜੇ (force) {
            // force the event to trigger, so pixel ratio changes can be handled
            ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ->w = 0;
            ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ->h = 0;
        }

        SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_RESIZED, SDL_lroundf(w), SDL_lroundf(h));
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ EM_BOOL Emscripten_HandleResizeGlobal(ਪੂਰਨ eventType, ਅਚਲ EmscriptenUiEvent *uiEvent, ਖਾਲੀ *user_ਅੰਕੜੇ)
{
    SDL_VideoDevice *device = user_ਅੰਕੜੇ;
    bool prevent_default = false;
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ;

    ਲਈ (ਖਿੜਕੀ = device->windows; ਖਿੜਕੀ; ਖਿੜਕੀ = ਖਿੜਕੀ->ਅਗਲਾ) {
        prevent_default |= Emscripten_HandleResize(eventType, uiEvent, ਖਿੜਕੀ->ਅੰਦਰੂਨੀ);
    }

    ਵਾਪਸ prevent_default;
}

EM_BOOL
Emscripten_HandleCanvasResize(ਪੂਰਨ eventType, ਅਚਲ ਖਾਲੀ *reserved, ਖਾਲੀ *user_ਅੰਕੜੇ)
{
    // this is used during fullscreen changes
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2 = user_ਅੰਕੜੇ;

    ਜੇ (ਖਿੜਕੀ_ਅੰਕੜੇ_2->fullscreen_resize) {
        ਦੁੱਗਣਾ css_w, css_h;
        emscripten_get_element_css_ਮਾਪ(ਖਿੜਕੀ_ਅੰਕੜੇ_2->canvas_id, &css_w, &css_h);
        SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ, SDL_EVENT_ਖਿੜਕੀ_RESIZED, SDL_lroundf(css_w), SDL_lroundf(css_h));
    }

    ਵਾਪਸ 0;
}

ਸਥਿਰ EM_BOOL Emscripten_HandleVisibilityChange(ਪੂਰਨ eventType, ਅਚਲ EmscriptenVisibilityChangeEvent *visEvent, ਖਾਲੀ *user_ਅੰਕੜੇ)
{
    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2 = user_ਅੰਕੜੇ;
    SDL_Send_ਖਿੜਕੀ_Event(ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ, visEvent->hidden ? SDL_EVENT_ਖਿੜਕੀ_HIDDEN : SDL_EVENT_ਖਿੜਕੀ_SHOWN, 0, 0);
    ਵਾਪਸ 0;
}

ਸਥਿਰ ਅਚਲ ਅੱਖਰ *Emscripten_HandleBeforeUnload(ਪੂਰਨ eventType, ਅਚਲ ਖਾਲੀ *reserved, ਖਾਲੀ *user_ਅੰਕੜੇ)
{
    /* This event will need to be handled synchronously, e.g. using
       SDL_AddEventWatch, as the page is being closed *now*. */
    SDL_SendQuit();  // the app might see this if they installed an event watcher.
    SDL_OnApplicationWillTerminate();  // calls SDL_AppQuit if appropriate, etc.
    ਵਾਪਸ ""; // don't trigger confirmation dialog
}

ਸਥਿਰ EM_BOOL Emscripten_HandleOrientationChange(ਪੂਰਨ eventType, ਅਚਲ EmscriptenOrientationChangeEvent *orientationChangeEvent, ਖਾਲੀ *user_ਅੰਕੜੇ)
{
    SDL_DisplayOrientation orientation;
    ਚੋਣ (orientationChangeEvent->orientation_ਸੂਚਕਾਂਕ) {
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHECK_ORIENTATION(emsdk, sdl) ਹਾਲਤ EMSCRIPTEN_ORIENTATION_##emsdk: orientation = SDL_ORIENTATION_##sdl; ਰੋਕੋ
        CHECK_ORIENTATION(LANDSCAPE_PRIMARY, LANDSCAPE);
        CHECK_ORIENTATION(LANDSCAPE_SECONDARY, LANDSCAPE_FLIPPED);
        CHECK_ORIENTATION(PORTRAIT_PRIMARY, PORTRAIT);
        CHECK_ORIENTATION(PORTRAIT_SECONDARY, PORTRAIT_FLIPPED);
        #ਪਰਿਭਾਸ਼ਾ_ਰੱਦ CHECK_ORIENTATION
        ਮੂਲ: orientation = SDL_ORIENTATION_UNKNOWN; ਰੋਕੋ;
    }

    SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2 = (SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *) user_ਅੰਕੜੇ;
    SDL_SendDisplayEvent(SDL_Get_Video_Display_For_ਖਿੜਕੀ(ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ), SDL_EVENT_DISPLAY_ORIENTATION, orientation, 0);

    // fake a UI event so we can tell the app the canvas might have resized.
    EmscriptenUiEvent uiEvent;
    SDL_zero(uiEvent);
    uiEvent.document_Body_Client_ਚੌੜਾਈ = MAIN_THREAD_EM_ASM_INT( { ਵਾਪਸ document.body.client_ਚੌੜਾਈ; } );
    uiEvent.document_Body_Client_ਉਚਾਈ = MAIN_THREAD_EM_ASM_INT( { ਵਾਪਸ document.body.client_ਉਚਾਈ; } );
    uiEvent.ਖਿੜਕੀ_Inner_ਚੌੜਾਈ = MAIN_THREAD_EM_ASM_INT( { ਵਾਪਸ ਖਿੜਕੀ.inner_ਚੌੜਾਈ; } );
    uiEvent.ਖਿੜਕੀ_Inner_ਉਚਾਈ = MAIN_THREAD_EM_ASM_INT( { ਵਾਪਸ ਖਿੜਕੀ.inner_ਉਚਾਈ; } );
    uiEvent.ਖਿੜਕੀ_Outer_ਚੌੜਾਈ = MAIN_THREAD_EM_ASM_INT( { ਵਾਪਸ ਖਿੜਕੀ.outer_ਚੌੜਾਈ; } );
    uiEvent.ਖਿੜਕੀ_Outer_ਉਚਾਈ = MAIN_THREAD_EM_ASM_INT( { ਵਾਪਸ ਖਿੜਕੀ.outer_ਉਚਾਈ; } );
    uiEvent.scroll_ਸਿਖਰ = MAIN_THREAD_EM_ASM_INT( { ਵਾਪਸ ਖਿੜਕੀ.ਪੰਨਾ_XOffset; } );
    uiEvent.scroll_ਖੱਬਾ = MAIN_THREAD_EM_ASM_INT( { ਵਾਪਸ ਖਿੜਕੀ.ਪੰਨਾ_YOffset; } );
    Emscripten_HandleResize(EMSCRIPTEN_EVENT_RESIZE, &uiEvent, user_ਅੰਕੜੇ);

    ਵਾਪਸ 0;
}

// IF YOU CHANGE THIS STRUCTURE, YOU NEED TO UPDATE THE JAVASCRIPT THAT FILLS IT IN: SDL3.makePointerEventCStruct, below.
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PTRTYPE_MOUSE 1
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PTRTYPE_TOUCH 2
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ PTRTYPE_PEN 3
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Emscripten_ਸੂਚਕ_Event
{
    ਪੂਰਨ ਸੂਚਕ_type;
    ਪੂਰਨ pointerid;
    ਪੂਰਨ button;
    ਪੂਰਨ buttons;
    ਪੂਰਨ ਥੱਲੇ;
    ਦਸ਼ਮਲਵ movementX;
    ਦਸ਼ਮਲਵ movementY;
    ਦਸ਼ਮਲਵ ਨਿਸ਼ਾਨਾ_X;
    ਦਸ਼ਮਲਵ ਨਿਸ਼ਾਨਾ_Y;
    ਦਸ਼ਮਲਵ pressure;
    ਦਸ਼ਮਲਵ tangential_pressure;
    ਦਸ਼ਮਲਵ tiltx;
    ਦਸ਼ਮਲਵ tilty;
    ਦਸ਼ਮਲਵ rotation;
} Emscripten_ਸੂਚਕ_Event;

ਸਥਿਰ ਖਾਲੀ Emscripten_HandleMouseButton(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2, ਅਚਲ Emscripten_ਸੂਚਕ_Event *event)
{
    Uint8 sdl_button;
    bool ਥੱਲੇ = false;
    ਚੋਣ (event->button) {
        #ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ CHECK_MOUSE_BUTTON(jsbutton, downflag, sdlbutton) ਹਾਲਤ jsbutton: sdl_button = SDL_BUTTON_##sdlbutton; ਥੱਲੇ = (event->ਥੱਲੇ != 0) || ((event->buttons & downflag) != 0); ਰੋਕੋ
        CHECK_MOUSE_BUTTON(0, 1, ਖੱਬਾ_2);
        CHECK_MOUSE_BUTTON(1, 4, ਵਿਚਕਾਰ_2);
        CHECK_MOUSE_BUTTON(2, 2, ਸੱਜਾ_2);
        CHECK_MOUSE_BUTTON(3, 8, X1);
        CHECK_MOUSE_BUTTON(4, 16, X2);
        #ਪਰਿਭਾਸ਼ਾ_ਰੱਦ CHECK_MOUSE_BUTTON
        ਮੂਲ: sdl_button = 0; ਰੋਕੋ;
    }

    ਜੇ (sdl_button) {
        ਅਚਲ SDL_Mouse *mouse = SDL_GetMouse();
        SDL_assert(mouse != ਨਿਰਾ);

        ਜੇ (ਥੱਲੇ) {
            ਜੇ (mouse->relative_ਬਹੁਲਕ && !ਖਿੜਕੀ_ਅੰਕੜੇ_2->has_ਸੂਚਕ_ਤਾਲਾ) {
                emscripten_request_pointerlock(ਖਿੜਕੀ_ਅੰਕੜੇ_2->canvas_id, 0); // try to regrab lost pointer lock.
            }
        }

        SDL_SendMouseButton(0, ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ, SDL_DEFAULT_MOUSE_ID, sdl_button, ਥੱਲੇ);

        // We have an imaginary mouse capture, because we need SDL to not drop our imaginary mouse focus when we leave the canvas.
        ਜੇ (mouse->auto_capture) {
            ਜੇ (SDL_GetMouseState(ਨਿਰਾ, ਨਿਰਾ) != 0) {
                ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ->flags |= SDL_ਖਿੜਕੀ_MOUSE_CAPTURE;
            } ਨਹੀਂਤਾਂ {
                ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ->flags &= ~SDL_ਖਿੜਕੀ_MOUSE_CAPTURE;
            }
        }

        ਜੇ (!ਥੱਲੇ && ਖਿੜਕੀ_ਅੰਕੜੇ_2->mouse_focus_loss_pending) {
            ਖਿੜਕੀ_ਅੰਕੜੇ_2->mouse_focus_loss_pending = (ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MOUSE_CAPTURE) != 0;
            ਜੇ (!ਖਿੜਕੀ_ਅੰਕੜੇ_2->mouse_focus_loss_pending) {
                SDL_ਸੈੱਟ_Mouse_Focus(ਨਿਰਾ);
            }
        }
    }
}

ਸਥਿਰ ਖਾਲੀ Emscripten_UpdateMouseFromEvent(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2, ਅਚਲ Emscripten_ਸੂਚਕ_Event *event)
{
    SDL_assert(event->ਸੂਚਕ_type == PTRTYPE_MOUSE);

    // Hidden windows (e.g. a shared GL-context window) may share the DOM canvas with the
    // visible window. Their pointer-event listeners would otherwise fire alongside the
    // visible window's, fighting over `mouse->focus` and producing events tagged with the
    // hidden window's ID -- causing downstream consumers that key by window ID to silently
    // drop them. Hidden windows shouldn't take part in user-input dispatch.
    ਜੇ (ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_HIDDEN) {
        ਵਾਪਸ;
    }

    // rescale (in case canvas is being scaled)
    ਦੁੱਗਣਾ client_w, client_h;
    emscripten_get_element_css_ਮਾਪ(ਖਿੜਕੀ_ਅੰਕੜੇ_2->canvas_id, &client_w, &client_h);
    ਅਚਲ ਦੁੱਗਣਾ xscale = ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ->w / client_w;
    ਅਚਲ ਦੁੱਗਣਾ yscale = ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ->h / client_h;

    ਅਚਲ bool is_ਸੂਚਕ_Locked = ਖਿੜਕੀ_ਅੰਕੜੇ_2->has_ਸੂਚਕ_ਤਾਲਾ;
    ਦਸ਼ਮਲਵ mx, my;
    ਜੇ (is_ਸੂਚਕ_Locked) {
        mx = (ਦਸ਼ਮਲਵ)(event->movementX * xscale);
        my = (ਦਸ਼ਮਲਵ)(event->movementY * yscale);
    } ਨਹੀਂਤਾਂ {
        mx = (ਦਸ਼ਮਲਵ)(event->ਨਿਸ਼ਾਨਾ_X * xscale);
        my = (ਦਸ਼ਮਲਵ)(event->ਨਿਸ਼ਾਨਾ_Y * yscale);
    }

    SDL_SendMouseMotion(0, ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ, SDL_DEFAULT_MOUSE_ID, is_ਸੂਚਕ_Locked, mx, my);

    Emscripten_HandleMouseButton(ਖਿੜਕੀ_ਅੰਕੜੇ_2, event);
}

ਸਥਿਰ ਖਾਲੀ Emscripten_UpdateTouchFromEvent(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2, ਅਚਲ Emscripten_ਸੂਚਕ_Event *event)
{
    SDL_assert(event->ਸੂਚਕ_type == PTRTYPE_TOUCH);

    ਅਚਲ SDL_TouchID deviceId = 1;
    ਜੇ (SDL_ਜੋੜੋ_Touch(deviceId, SDL_TOUCH_DEVICE_ਸਿੱਧਾ, "") < 0) {
        ਵਾਪਸ;
    }

    ਦੁੱਗਣਾ client_w, client_h;
    emscripten_get_element_css_ਮਾਪ(ਖਿੜਕੀ_ਅੰਕੜੇ_2->canvas_id, &client_w, &client_h);

    ਅਚਲ SDL_FingerID id = event->pointerid + 1;
    ਦਸ਼ਮਲਵ x, y;
    ਜੇ (client_w <= 1) {
        x = 0.5f;
    } ਨਹੀਂਤਾਂ {
        x = event->ਨਿਸ਼ਾਨਾ_X / (client_w - 1);
    }
    ਜੇ (client_h <= 1) {
        y = 0.5f;
    } ਨਹੀਂਤਾਂ {
        y = event->ਨਿਸ਼ਾਨਾ_Y / (client_h - 1);
    }

    ਅਚਲ bool ਥੱਲੇ = (event->buttons & 1) != 0;
    ਜੇ (event->button == 0) {  // touch is starting or ending if this is zero (-1 means "no change").
        ਜੇ (ਥੱਲੇ) {
            SDL_SendTouch(0, deviceId, id, ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ, SDL_EVENT_FINGER_ਥੱਲੇ, x, y, 1.0f);
        }
    }

    SDL_SendTouchMotion(0, deviceId, id, ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ, x, y, 1.0f);

    ਜੇ (event->button == 0) {  // touch is starting or ending if this is zero (-1 means "no change").
        ਜੇ (!ਥੱਲੇ) {
            SDL_SendTouch(0, deviceId, id, ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ, SDL_EVENT_FINGER_ਉੱਪਰ, x, y, 1.0f);
        }
    }
}

ਸਥਿਰ ਖਾਲੀ Emscripten_UpdatePenFromEvent(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2, ਅਚਲ Emscripten_ਸੂਚਕ_Event *event)
{
    SDL_assert(event->ਸੂਚਕ_type == PTRTYPE_PEN);
    ਅਚਲ SDL_PenID pen = SDL_ਲੱਭੋ_Pen_By_Handle((ਖਾਲੀ *) (size_t) 1);   // something > 0 for the single pen handle.
    ਜੇ (pen) {
        // rescale (in case canvas is being scaled)
        ਦੁੱਗਣਾ client_w, client_h;
        emscripten_get_element_css_ਮਾਪ(ਖਿੜਕੀ_ਅੰਕੜੇ_2->canvas_id, &client_w, &client_h);
        ਅਚਲ ਦੁੱਗਣਾ xscale = ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ->w / client_w;
        ਅਚਲ ਦੁੱਗਣਾ yscale = ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ->h / client_h;

        ਅਚਲ bool is_ਸੂਚਕ_Locked = ਖਿੜਕੀ_ਅੰਕੜੇ_2->has_ਸੂਚਕ_ਤਾਲਾ;
        ਦਸ਼ਮਲਵ mx, my;
        ਜੇ (is_ਸੂਚਕ_Locked) {
            mx = (ਦਸ਼ਮਲਵ)(event->movementX * xscale);
            my = (ਦਸ਼ਮਲਵ)(event->movementY * yscale);
        } ਨਹੀਂਤਾਂ {
            mx = (ਦਸ਼ਮਲਵ)(event->ਨਿਸ਼ਾਨਾ_X * xscale);
            my = (ਦਸ਼ਮਲਵ)(event->ਨਿਸ਼ਾਨਾ_Y * yscale);
        }

        SDL_SendPenMotion(0, pen, ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ, mx, my);

        ਜੇ (event->button == 0) {  // pen touch
            bool ਥੱਲੇ = ((event->buttons & 1) != 0);
            SDL_SendPenTouch(0, pen, ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ, false, ਥੱਲੇ);
        } ਨਹੀਂਤਾਂ ਜੇ (event->button == 5) {  // eraser touch...? Not sure if this is right...
            bool ਥੱਲੇ = ((event->buttons & 32) != 0);
            SDL_SendPenTouch(0, pen, ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ, true, ਥੱਲੇ);
        } ਨਹੀਂਤਾਂ ਜੇ (event->button == 1) {
            bool ਥੱਲੇ = ((event->buttons & 4) != 0);
            SDL_SendPenButton(0, pen, ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ, 2, ਥੱਲੇ);
        } ਨਹੀਂਤਾਂ ਜੇ (event->button == 2) {
            bool ਥੱਲੇ = ((event->buttons & 2) != 0);
            SDL_SendPenButton(0, pen, ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ, 1, ਥੱਲੇ);
        }

        SDL_SendPenAxis(0, pen, ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ, SDL_PEN_AXIS_PRESSURE, event->pressure);
        SDL_SendPenAxis(0, pen, ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ, SDL_PEN_AXIS_TANGENTIAL_PRESSURE, event->tangential_pressure);
        SDL_SendPenAxis(0, pen, ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ, SDL_PEN_AXIS_XTILT, event->tiltx);
        SDL_SendPenAxis(0, pen, ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ, SDL_PEN_AXIS_YTILT, event->tilty);
        SDL_SendPenAxis(0, pen, ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ, SDL_PEN_AXIS_ROTATION, event->rotation);
    }
}

ਸਥਿਰ ਖਾਲੀ Emscripten_Update_ਸੂਚਕ_From_Event(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2, ਅਚਲ Emscripten_ਸੂਚਕ_Event *event)
{
    SDL_assert(event != ਨਿਰਾ);
    ਜੇ (event->ਸੂਚਕ_type == PTRTYPE_MOUSE) {
        Emscripten_UpdateMouseFromEvent(ਖਿੜਕੀ_ਅੰਕੜੇ_2, event);
    } ਨਹੀਂਤਾਂ ਜੇ (event->ਸੂਚਕ_type == PTRTYPE_TOUCH) {
        Emscripten_UpdateTouchFromEvent(ਖਿੜਕੀ_ਅੰਕੜੇ_2, event);
    } ਨਹੀਂਤਾਂ ਜੇ (event->ਸੂਚਕ_type == PTRTYPE_PEN) {
        Emscripten_UpdatePenFromEvent(ਖਿੜਕੀ_ਅੰਕੜੇ_2, event);
    } ਨਹੀਂਤਾਂ {
        SDL_assert(!"Unexpected pointer event type");
    }
}

ਸਥਿਰ ਖਾਲੀ Emscripten_HandleMouseFocus(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2, ਅਚਲ Emscripten_ਸੂਚਕ_Event *event, bool isenter)
{
    SDL_assert(event->ਸੂਚਕ_type == PTRTYPE_MOUSE);

    // Hidden windows shouldn't ever become the mouse-focus target.
    ਜੇ (ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_HIDDEN) {
        ਵਾਪਸ;
    }

    ਅਚਲ bool is_ਸੂਚਕ_Locked = ਖਿੜਕੀ_ਅੰਕੜੇ_2->has_ਸੂਚਕ_ਤਾਲਾ;

    ਜੇ (!is_ਸੂਚਕ_Locked) {
        // rescale (in case canvas is being scaled)
        ਦਸ਼ਮਲਵ mx, my;
        ਦੁੱਗਣਾ client_w, client_h;
        emscripten_get_element_css_ਮਾਪ(ਖਿੜਕੀ_ਅੰਕੜੇ_2->canvas_id, &client_w, &client_h);

        mx = (ਦਸ਼ਮਲਵ)(event->ਨਿਸ਼ਾਨਾ_X * (ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ->w / client_w));
        my = (ਦਸ਼ਮਲਵ)(event->ਨਿਸ਼ਾਨਾ_Y * (ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ->h / client_h));
        SDL_SendMouseMotion(0, ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ, SDL_GLOBAL_MOUSE_ID, is_ਸੂਚਕ_Locked, mx, my);
    }

    ਜੇ (isenter && ਖਿੜਕੀ_ਅੰਕੜੇ_2->mouse_focus_loss_pending) {
        ਖਿੜਕੀ_ਅੰਕੜੇ_2->mouse_focus_loss_pending = false;  // just drop the state, but don't send the enter event.
    } ਨਹੀਂਤਾਂ ਜੇ (!isenter && (ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_MOUSE_CAPTURE)) {
        ਖਿੜਕੀ_ਅੰਕੜੇ_2->mouse_focus_loss_pending = true;  // waiting on a mouse button to let go before we send the mouse focus update.
    } ਨਹੀਂਤਾਂ {
        SDL_ਸੈੱਟ_Mouse_Focus(isenter ? ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ : ਨਿਰਾ);
    }
}

ਸਥਿਰ ਖਾਲੀ Emscripten_HandlePenEnter(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2, ਅਚਲ Emscripten_ਸੂਚਕ_Event *event)
{
    SDL_assert(event->ਸੂਚਕ_type == PTRTYPE_PEN);

    // event->pointerid is one continuous interaction; it doesn't necessarily track a specific tool over time, like the same finger's ID changed on each new touch event.
    // as such, we only expose a single pen, and when the touch ends, we say it lost proximity instead of the calling SDL_RemovePenDevice().

    SDL_PenID pen = SDL_ਲੱਭੋ_Pen_By_Handle((ਖਾਲੀ *) (size_t) 1);  // something > 0 for the single pen handle.
    ਜੇ (pen) {
        SDL_SendPenProximity(0, pen, ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ, true, true);
    } ਨਹੀਂਤਾਂ {
        // Web browsers offer almost none of this information as specifics, but can without warning offer any of these specific things.
        SDL_PenInfo peninfo;
        SDL_zero(peninfo);
        peninfo.capabilities = SDL_PEN_CAPABILITY_PRESSURE | SDL_PEN_CAPABILITY_ROTATION | SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT | SDL_PEN_CAPABILITY_TANGENTIAL_PRESSURE | SDL_PEN_CAPABILITY_ERASER;
        peninfo.max_tilt = 90.0f;
        peninfo.ਅੰਕ_buttons = 2;
        peninfo.subtype = SDL_PEN_TYPE_PEN;
        SDL_ਜੋੜੋ_Pen_Device(0, ਨਿਰਾ, ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ, &peninfo, (ਖਾਲੀ *) (size_t) 1, true);
    }

    Emscripten_UpdatePenFromEvent(ਖਿੜਕੀ_ਅੰਕੜੇ_2, event);
}

EMSCRIPTEN_KEEPALIVE ਖਾਲੀ Emscripten_Handle_ਸੂਚਕ_Enter(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2, ਅਚਲ Emscripten_ਸੂਚਕ_Event *event)
{
    SDL_assert(event != ਨਿਰਾ);
    ਜੇ (event->ਸੂਚਕ_type == PTRTYPE_MOUSE) {
        Emscripten_HandleMouseFocus(ਖਿੜਕੀ_ਅੰਕੜੇ_2, event, true);
    } ਨਹੀਂਤਾਂ ਜੇ (event->ਸੂਚਕ_type == PTRTYPE_PEN) {
        Emscripten_HandlePenEnter(ਖਿੜਕੀ_ਅੰਕੜੇ_2, event);
    } ਨਹੀਂਤਾਂ ਜੇ (event->ਸੂਚਕ_type == PTRTYPE_TOUCH) {
        // do nothing.
    } ਨਹੀਂਤਾਂ {
        SDL_assert(!"Unexpected pointer event type");
    }
}

ਸਥਿਰ ਖਾਲੀ Emscripten_HandlePenLeave(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2, ਅਚਲ Emscripten_ਸੂਚਕ_Event *event)
{
    ਅਚਲ SDL_PenID pen = SDL_ਲੱਭੋ_Pen_By_Handle((ਖਾਲੀ *) (size_t) 1);   // something > 0 for the single pen handle.
    ਜੇ (pen) {
        Emscripten_Update_ਸੂਚਕ_From_Event(ਖਿੜਕੀ_ਅੰਕੜੇ_2, event);  // last data updates?
        SDL_SendPenProximity(0, pen, ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ, false, false);
    }
}

ਸਥਿਰ ਖਾਲੀ Emscripten_HandleTouchCancel(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2, ਅਚਲ Emscripten_ਸੂਚਕ_Event *event)
{
    SDL_assert(event->ਸੂਚਕ_type == PTRTYPE_TOUCH);

    ਅਚਲ SDL_TouchID deviceId = 1;
    ਜੇ (SDL_ਜੋੜੋ_Touch(deviceId, SDL_TOUCH_DEVICE_ਸਿੱਧਾ, "") < 0) {
        ਵਾਪਸ;
    }

    ਦੁੱਗਣਾ client_w, client_h;
    emscripten_get_element_css_ਮਾਪ(ਖਿੜਕੀ_ਅੰਕੜੇ_2->canvas_id, &client_w, &client_h);

    ਅਚਲ SDL_FingerID id = event->pointerid + 1;
    ਦਸ਼ਮਲਵ x, y;
    ਜੇ (client_w <= 1) {
        x = 0.5f;
    } ਨਹੀਂਤਾਂ {
        x = event->ਨਿਸ਼ਾਨਾ_X / (client_w - 1);
    }
    ਜੇ (client_h <= 1) {
        y = 0.5f;
    } ਨਹੀਂਤਾਂ {
        y = event->ਨਿਸ਼ਾਨਾ_Y / (client_h - 1);
    }

    SDL_SendTouch(0, deviceId, id, ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ, SDL_EVENT_FINGER_CANCELED, x, y, 1.0f);
}

EMSCRIPTEN_KEEPALIVE ਖਾਲੀ Emscripten_Handle_ਸੂਚਕ_Leave(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2, ਅਚਲ Emscripten_ਸੂਚਕ_Event *event)
{
    SDL_assert(event != ਨਿਰਾ);
    ਜੇ (event->ਸੂਚਕ_type == PTRTYPE_MOUSE) {
        Emscripten_HandleMouseFocus(ਖਿੜਕੀ_ਅੰਕੜੇ_2, event, false);
    } ਨਹੀਂਤਾਂ ਜੇ (event->ਸੂਚਕ_type == PTRTYPE_PEN) {
        Emscripten_HandlePenLeave(ਖਿੜਕੀ_ਅੰਕੜੇ_2, event);
    } ਨਹੀਂਤਾਂ ਜੇ (event->ਸੂਚਕ_type == PTRTYPE_TOUCH) {
        Emscripten_HandleTouchCancel(ਖਿੜਕੀ_ਅੰਕੜੇ_2, event);
    } ਨਹੀਂਤਾਂ {
        SDL_assert(!"Unexpected pointer event type");
    }
}

EMSCRIPTEN_KEEPALIVE ਖਾਲੀ Emscripten_Handle_ਸੂਚਕ_Generic(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2, ਅਚਲ Emscripten_ਸੂਚਕ_Event *event)
{
    SDL_assert(event != ਨਿਰਾ);
    Emscripten_Update_ਸੂਚਕ_From_Event(ਖਿੜਕੀ_ਅੰਕੜੇ_2, event);
}

ਸਥਿਰ ਖਾਲੀ Emscripten_prep_ਸੂਚਕ_event_callbacks(ਖਾਲੀ)
{
    MAIN_THREAD_EM_ASM({
        var SDL3 = Module['SDL3'];

        ਜੇ (SDL3.make_ਸੂਚਕ_Event_CStruct === undefined) {
            SDL3.make_ਸੂਚਕ_Event_CStruct = function(ਖੱਬਾ, ਸਿਖਰ, event) {
                var ptrtype = 0;
                ਜੇ (event.ਸੂਚਕ_Type == "mouse") {
                    ptrtype = 1;
                } ਨਹੀਂਤਾਂ ਜੇ (event.ਸੂਚਕ_Type == "touch") {
                    ptrtype = 2;
                } ਨਹੀਂਤਾਂ ਜੇ (event.ਸੂਚਕ_Type == "pen") {
                    ptrtype = 3;
                } ਨਹੀਂਤਾਂ {
                    ਵਾਪਸ 0;
                }

                var ptr = _SDL_malloc($0);
                ਜੇ (ptr != 0) {
                    var idx = SDL3.CPtr_ਮੰਜ਼ਿਲ_Heap32_ਸੂਚਕਾਂਕ(ptr);
                    HEAP32[idx++] = ptrtype;
                    HEAP32[idx++] = event.ਸੂਚਕ_Id;
                    HEAP32[idx++] = (typeof(event.button) !== "undefined") ? event.button : -1;
                    HEAP32[idx++] = event.buttons;
                    HEAP32[idx++] = (event.type == "pointerdown") ? 1 : 0;
                    HEAPF32[idx++] = event.movementX;
                    HEAPF32[idx++] = event.movementY;
                    HEAPF32[idx++] = event.clientX - ਖੱਬਾ;
                    HEAPF32[idx++] = event.clientY - ਸਿਖਰ;
                    ਜੇ (ptrtype == 3) {
                        HEAPF32[idx++] = event.pressure;
                        HEAPF32[idx++] = event.tangentialPressure;
                        HEAPF32[idx++] = event.tiltX;
                        HEAPF32[idx++] = event.tiltY;
                        HEAPF32[idx++] = event.twist;
                    }
                }
                ਵਾਪਸ ptr;
            };
        }
    }, ਆਕਾਰ (Emscripten_ਸੂਚਕ_Event));
}

ਸਥਿਰ ਖਾਲੀ Emscripten_ਸੈੱਟ_ਸੂਚਕ_event_callbacks(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ)
{
    Emscripten_prep_ਸੂਚਕ_event_callbacks();

    MAIN_THREAD_EM_ASM({
        var ਨਿਸ਼ਾਨਾ = document.querySelector(UTF8_ਮੰਜ਼ਿਲ_String($1));
        ਜੇ (ਨਿਸ਼ਾਨਾ) {
            var SDL3 = Module['SDL3'];
            var ਅੰਕੜੇ = $0;
            ਨਿਸ਼ਾਨਾ.sdl_Event_Handler_ਸੂਚਕ_Enter = function(event) {
                var rect = ਨਿਸ਼ਾਨਾ.getBoundingClientRect();
                var d = SDL3.make_ਸੂਚਕ_Event_CStruct(rect.ਖੱਬਾ, rect.ਸਿਖਰ, event);
                ਜੇ (d != 0)
                {
                    Emscripten_Handle_ਸੂਚਕ_Enter_2(SDL3.JSVar_ਮੰਜ਼ਿਲ_CPtr(ਅੰਕੜੇ), d);
                    _SDL_free(d);
                }
            };
            ਨਿਸ਼ਾਨਾ.sdl_Event_Handler_ਸੂਚਕ_Leave = function(event) {
                var rect = ਨਿਸ਼ਾਨਾ.getBoundingClientRect();
                var d = SDL3.make_ਸੂਚਕ_Event_CStruct(rect.ਖੱਬਾ, rect.ਸਿਖਰ, event);
                ਜੇ (d != 0)
                {
                    Emscripten_Handle_ਸੂਚਕ_Leave_2(SDL3.JSVar_ਮੰਜ਼ਿਲ_CPtr(ਅੰਕੜੇ), d);
                    _SDL_free(d);
                }
            };
            ਨਿਸ਼ਾਨਾ.sdl_Event_Handler_ਸੂਚਕ_Generic = function(event) {
                var rect = ਨਿਸ਼ਾਨਾ.getBoundingClientRect();
                var d = SDL3.make_ਸੂਚਕ_Event_CStruct(rect.ਖੱਬਾ, rect.ਸਿਖਰ, event);
                ਜੇ (d != 0)
                {
                    Emscripten_Handle_ਸੂਚਕ_Generic_2(SDL3.JSVar_ਮੰਜ਼ਿਲ_CPtr(ਅੰਕੜੇ), d);
                    _SDL_free(d);
                }
            };

            ਨਿਸ਼ਾਨਾ.style.touchAction = "none";  // or mobile devices will scroll as your touch moves across the element.
            ਨਿਸ਼ਾਨਾ.ਜੋੜੋ_Event_Listener("pointerenter", ਨਿਸ਼ਾਨਾ.sdl_Event_Handler_ਸੂਚਕ_Enter);
            ਨਿਸ਼ਾਨਾ.ਜੋੜੋ_Event_Listener("pointerleave", ਨਿਸ਼ਾਨਾ.sdl_Event_Handler_ਸੂਚਕ_Leave);
            ਨਿਸ਼ਾਨਾ.ਜੋੜੋ_Event_Listener("pointercancel", ਨਿਸ਼ਾਨਾ.sdl_Event_Handler_ਸੂਚਕ_Leave);
            ਨਿਸ਼ਾਨਾ.ਜੋੜੋ_Event_Listener("pointerdown", ਨਿਸ਼ਾਨਾ.sdl_Event_Handler_ਸੂਚਕ_Generic);
            ਨਿਸ਼ਾਨਾ.ਜੋੜੋ_Event_Listener("pointermove", ਨਿਸ਼ਾਨਾ.sdl_Event_Handler_ਸੂਚਕ_Generic);
            ਨਿਸ਼ਾਨਾ.ਜੋੜੋ_Event_Listener("pointerup", ਨਿਸ਼ਾਨਾ.sdl_Event_Handler_ਸੂਚਕ_Generic);
        }
    }, ਅੰਕੜੇ, ਅੰਕੜੇ->canvas_id);
}

ਸਥਿਰ ਖਾਲੀ Emscripten_unset_ਸੂਚਕ_event_callbacks(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ)
{
    MAIN_THREAD_EM_ASM({
        var ਨਿਸ਼ਾਨਾ = document.querySelector(UTF8_ਮੰਜ਼ਿਲ_String($0));
        ਜੇ (ਨਿਸ਼ਾਨਾ) {
            ਨਿਸ਼ਾਨਾ.removeEventListener("pointerenter", ਨਿਸ਼ਾਨਾ.sdl_Event_Handler_ਸੂਚਕ_Enter);
            ਨਿਸ਼ਾਨਾ.removeEventListener("pointerleave", ਨਿਸ਼ਾਨਾ.sdl_Event_Handler_ਸੂਚਕ_Leave);
            ਨਿਸ਼ਾਨਾ.removeEventListener("pointercancel", ਨਿਸ਼ਾਨਾ.sdl_Event_Handler_ਸੂਚਕ_Leave);
            ਨਿਸ਼ਾਨਾ.removeEventListener("pointerdown", ਨਿਸ਼ਾਨਾ.sdl_Event_Handler_ਸੂਚਕ_Generic);
            ਨਿਸ਼ਾਨਾ.removeEventListener("pointermove", ਨਿਸ਼ਾਨਾ.sdl_Event_Handler_ਸੂਚਕ_Generic);
            ਨਿਸ਼ਾਨਾ.removeEventListener("pointerup", ਨਿਸ਼ਾਨਾ.sdl_Event_Handler_ਸੂਚਕ_Generic);
            ਨਿਸ਼ਾਨਾ.style.touchAction = "";  // let mobile devices scroll again as your touch moves across the element.
            ਨਿਸ਼ਾਨਾ.sdl_Event_Handler_ਸੂਚਕ_Enter = undefined;
            ਨਿਸ਼ਾਨਾ.sdl_Event_Handler_ਸੂਚਕ_Leave = undefined;
            ਨਿਸ਼ਾਨਾ.sdl_Event_Handler_ਸੂਚਕ_Generic = undefined;
        }
    }, ਅੰਕੜੇ->canvas_id);
}

EMSCRIPTEN_KEEPALIVE ਖਾਲੀ Emscripten_Handle_Mouse_Button_ਉੱਪਰ_Global(SDL_VideoDevice *device, ਅਚਲ Emscripten_ਸੂਚਕ_Event *event)
{
    SDL_assert(device != ਨਿਰਾ);
    SDL_assert(event != ਨਿਰਾ);
    ਜੇ (event->ਸੂਚਕ_type == PTRTYPE_MOUSE) {
        ਲਈ (SDL_ਖਿੜਕੀ *ਖਿੜਕੀ = device->windows; ਖਿੜਕੀ; ਖਿੜਕੀ = ਖਿੜਕੀ->ਅਗਲਾ) {
            Emscripten_HandleMouseButton(ਖਿੜਕੀ->ਅੰਦਰੂਨੀ, event);
        }
    }
}

ਸਥਿਰ ਖਾਲੀ Emscripten_ਸੈੱਟ_global_mouseup_callback(SDL_VideoDevice *device)
{
    Emscripten_prep_ਸੂਚਕ_event_callbacks();

    MAIN_THREAD_EM_ASM({
        var ਨਿਸ਼ਾਨਾ = document;
        ਜੇ (ਨਿਸ਼ਾਨਾ) {
            ਨਿਸ਼ਾਨਾ.sdl_Event_Handler_Mouse_Button_ਉੱਪਰ_Global = function(event) {
                var SDL3 = Module['SDL3'];
                var d = SDL3.make_ਸੂਚਕ_Event_CStruct(0, 0, event);
                ਜੇ (d != 0)
                {
                    Emscripten_Handle_Mouse_Button_ਉੱਪਰ_Global_2(SDL3.JSVar_ਮੰਜ਼ਿਲ_CPtr($0), d);
                    _SDL_free(d);
                }
            };
            ਨਿਸ਼ਾਨਾ.ਜੋੜੋ_Event_Listener("pointerup", ਨਿਸ਼ਾਨਾ.sdl_Event_Handler_Mouse_Button_ਉੱਪਰ_Global);
        }
    }, device);
}

ਸਥਿਰ ਖਾਲੀ Emscripten_unset_global_mouseup_callback(SDL_VideoDevice *device)
{
    MAIN_THREAD_EM_ASM({
        var ਨਿਸ਼ਾਨਾ = document;
        ਜੇ (ਨਿਸ਼ਾਨਾ) {
            ਨਿਸ਼ਾਨਾ.removeEventListener("pointerup", ਨਿਸ਼ਾਨਾ.sdl_Event_Handler_Mouse_Button_ਉੱਪਰ_Global);
            ਨਿਸ਼ਾਨਾ.sdl_Event_Handler_Mouse_Button_ਉੱਪਰ_Global = undefined;
        }
    });
}

// IF YOU CHANGE THIS STRUCTURE, YOU NEED TO UPDATE THE JAVASCRIPT THAT FILLS IT IN: makeDropEventCStruct, below.
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Emscripten_DropEvent
{
    ਪੂਰਨ x;
    ਪੂਰਨ y;
} Emscripten_DropEvent;

EMSCRIPTEN_KEEPALIVE ਖਾਲੀ Emscripten_SendDragEvent(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2, ਅਚਲ Emscripten_DropEvent *event)
{
    SDL_SendDropPosition(ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ, event->x, event->y);
}

EMSCRIPTEN_KEEPALIVE ਖਾਲੀ Emscripten_SendDragCompleteEvent(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2)
{
    SDL_SendDropComplete(ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ);
}

EMSCRIPTEN_KEEPALIVE ਖਾਲੀ Emscripten_Send_Drag_ਪਾਠ_Event(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2, ਅੱਖਰ *ਪਾਠ)
{
    SDL_Send_Drop_ਪਾਠ(ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ, ਪਾਠ);
}

EMSCRIPTEN_KEEPALIVE ਖਾਲੀ Emscripten_SendDragFileEvent(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2, ਅੱਖਰ *filename)
{
    SDL_SendDropFile(ਖਿੜਕੀ_ਅੰਕੜੇ_2->ਖਿੜਕੀ, ਨਿਰਾ, filename);
}

EM_JS_DEPS(dragndrop, "$writeArrayToMemory");

ਸਥਿਰ ਖਾਲੀ Emscripten_ਸੈੱਟ_drag_event_callbacks(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ)
{
    MAIN_THREAD_EM_ASM({
        var ਨਿਸ਼ਾਨਾ = document.querySelector(UTF8_ਮੰਜ਼ਿਲ_String($1));
        ਜੇ (ਨਿਸ਼ਾਨਾ) {
            var ਅੰਕੜੇ = $0;
            var SDL3 = Module['SDL3'];

            var makeDropEventCStruct = function(event) {
                var ptr = 0;
                ptr = _SDL_malloc($2);
                ਜੇ (ptr != 0) {
                    var idx = ptr >> 2;
                    var rect = ਨਿਸ਼ਾਨਾ.getBoundingClientRect();
                    HEAP32[idx++] = event.clientX - rect.ਖੱਬਾ;
                    HEAP32[idx++] = event.clientY - rect.ਸਿਖਰ;
                }
                ਵਾਪਸ ptr;
            };

            SDL3.eventHandlerDropDragover = function(event) {
                event.preventDefault();
                var d = makeDropEventCStruct(event); ਜੇ (d != 0) { _Emscripten_SendDragEvent(ਅੰਕੜੇ, d); _SDL_free(d); }
            };
            ਨਿਸ਼ਾਨਾ.ਜੋੜੋ_Event_Listener("dragover", SDL3.eventHandlerDropDragover);

            SDL3.drop_ਗਿਣਤੀ = 0;

            // FS.* functions throw exceptions when there are errors (such as the temp dir already existing),
            //  but we ignore all of these in a catch handler; you just won't get the drop event if there's a problem.
            try { FS.mkdir("/tmp/filedrop"); } catch (e) {}

            SDL3.eventHandlerDropDrop = function(event) {
                event.preventDefault();
                ਜੇ (event.ਅੰਕੜੇ_Transfer.types.includes("text/plain")) {
                    let plain_ਪਾਠ = string_ਮੰਜ਼ਿਲ_New_UTF8(event.ਅੰਕੜੇ_Transfer.get_ਅੰਕੜੇ("text/plain"));
                    Emscripten_Send_Drag_ਪਾਠ_Event_2(ਅੰਕੜੇ, plain_ਪਾਠ);
                    _Emscripten_force_free(plain_ਪਾਠ);
                } ਨਹੀਂਤਾਂ ਜੇ (event.ਅੰਕੜੇ_Transfer.types.includes("Files")) {
                    let files_read = 0;
                    ਅਚਲ files_ਮੰਜ਼ਿਲ_read = event.ਅੰਕੜੇ_Transfer.files.ਲੰਮਾਈ;
                    ਲਈ (let i = 0; i < files_ਮੰਜ਼ਿਲ_read; i++) {
                        ਅਚਲ file = event.ਅੰਕੜੇ_Transfer.files.ਵਸਤੂ(i);
                        ਅਚਲ file_reader = new FileReader();
                        file_reader.read_As_Array_ਬਫਰ(file);
                        file_reader.onload = function(event) {
                            ਅਚਲ fs_dropdir = `/tmp/filedrop/${SDL3.drop_ਗਿਣਤੀ}`;
                            SDL3.drop_ਗਿਣਤੀ += 1;

                            ਅਚਲ fs_filepath = `${fs_dropdir}/${file.name}`;
                            ਅਚਲ c_fs_filepath = string_ਮੰਜ਼ਿਲ_New_UTF8(fs_filepath);
                            ਅਚਲ contents_array8 = new Uint8Array(event.ਨਿਸ਼ਾਨਾ.ਨਤੀਜਾ);

                            try {
                                FS.mkdir(fs_dropdir);
                                var ਧਾਰਾ = FS.open(fs_filepath, "w");
                                FS.ਲਿਖ(ਧਾਰਾ, contents_array8, 0, contents_array8.ਲੰਮਾਈ, 0);
                                FS.close(ਧਾਰਾ);
                                _Emscripten_SendDragFileEvent(ਅੰਕੜੇ, c_fs_filepath);
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
                        ਜੇ (files_read === files_ਮੰਜ਼ਿਲ_read) {
                            _Emscripten_SendDragCompleteEvent(ਅੰਕੜੇ);
                        }
                    }
                }
                _Emscripten_SendDragCompleteEvent(ਅੰਕੜੇ);
            };
            ਨਿਸ਼ਾਨਾ.ਜੋੜੋ_Event_Listener("drop", SDL3.eventHandlerDropDrop);

            SDL3.eventHandlerDropDragend = function(event) {
                event.preventDefault();
                _Emscripten_SendDragCompleteEvent(ਅੰਕੜੇ);
            };
            ਨਿਸ਼ਾਨਾ.ਜੋੜੋ_Event_Listener("dragend", SDL3.eventHandlerDropDragend);
            ਨਿਸ਼ਾਨਾ.ਜੋੜੋ_Event_Listener("dragleave", SDL3.eventHandlerDropDragend);
        }
    }, ਅੰਕੜੇ, ਅੰਕੜੇ->canvas_id, ਆਕਾਰ (Emscripten_DropEvent));
}

ਸਥਿਰ ਖਾਲੀ Emscripten_unset_drag_event_callbacks(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ)
{
    MAIN_THREAD_EM_ASM({
        var ਨਿਸ਼ਾਨਾ = document.querySelector(UTF8_ਮੰਜ਼ਿਲ_String($0));
        ਜੇ (ਨਿਸ਼ਾਨਾ) {
            var SDL3 = Module['SDL3'];
            ਨਿਸ਼ਾਨਾ.removeEventListener("dragleave", SDL3.eventHandlerDropDragend);
            ਨਿਸ਼ਾਨਾ.removeEventListener("dragend", SDL3.eventHandlerDropDragend);
            ਨਿਸ਼ਾਨਾ.removeEventListener("drop", SDL3.eventHandlerDropDrop);
            SDL3.drop_ਗਿਣਤੀ = undefined;

            function recursive_remove(dirpath) {
                FS.readdir(dirpath).forEach((filename) => {
                    ਅਚਲ p = `${dirpath}/${filename}`;
                    ਅਚਲ p_s = FS.stat(p);
                    ਜੇ (FS.isFile(p_s.ਬਹੁਲਕ)) {
                        FS.unlink(p);
                    } ਨਹੀਂਤਾਂ ਜੇ (FS.isDir(p)) {
                        recursive_remove(p);
                    }
                });
                FS.rmdir(dirpath);
            }("/tmp/filedrop");

            FS.rmdir("/tmp/filedrop");
            ਨਿਸ਼ਾਨਾ.removeEventListener("dragover", SDL3.eventHandlerDropDragover);
            SDL3.eventHandlerDropDragover = undefined;
            SDL3.eventHandlerDropDrop = undefined;
            SDL3.eventHandlerDropDragend = undefined;
        }
    }, ਅੰਕੜੇ->canvas_id);
}

ਸਥਿਰ ਅਚਲ ਅੱਖਰ *Emscripten_Get_Keyboard_ਨਿਸ਼ਾਨਾ_Element(ਅਚਲ ਅੱਖਰ *ਨਿਸ਼ਾਨਾ)
{
    ਜੇ (SDL_strcmp(ਨਿਸ਼ਾਨਾ, "#none") == 0) {
        ਵਾਪਸ ਨਿਰਾ;
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(ਨਿਸ਼ਾਨਾ, "#window") == 0) {
        ਵਾਪਸ EMSCRIPTEN_EVENT_ਨਿਸ਼ਾਨਾ_ਖਿੜਕੀ;
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(ਨਿਸ਼ਾਨਾ, "#document") == 0) {
        ਵਾਪਸ EMSCRIPTEN_EVENT_ਨਿਸ਼ਾਨਾ_DOCUMENT;
    } ਨਹੀਂਤਾਂ ਜੇ (SDL_strcmp(ਨਿਸ਼ਾਨਾ, "#screen") == 0) {
        ਵਾਪਸ EMSCRIPTEN_EVENT_ਨਿਸ਼ਾਨਾ_SCREEN;
    }

    ਵਾਪਸ ਨਿਸ਼ਾਨਾ;
}

ਖਾਲੀ Emscripten_ਰਜਿਸਟਰ_Global_Event_Handlers(SDL_VideoDevice *device)
{
    Emscripten_ਸੈੱਟ_global_mouseup_callback(device);

    emscripten_ਸੈੱਟ_focus_callback(EMSCRIPTEN_EVENT_ਨਿਸ਼ਾਨਾ_ਖਿੜਕੀ, device, 0, Emscripten_HandleFocus);
    emscripten_ਸੈੱਟ_blur_callback(EMSCRIPTEN_EVENT_ਨਿਸ਼ਾਨਾ_ਖਿੜਕੀ, device, 0, Emscripten_HandleFocus);

    emscripten_ਸੈੱਟ_pointerlockchange_callback(EMSCRIPTEN_EVENT_ਨਿਸ਼ਾਨਾ_DOCUMENT, device, 0, Emscripten_Handle_ਸੂਚਕ_ਤਾਲਾ_Change_Global);

    emscripten_ਸੈੱਟ_fullscreenchange_callback(EMSCRIPTEN_EVENT_ਨਿਸ਼ਾਨਾ_DOCUMENT, device, 0, Emscripten_HandleFullscreenChangeGlobal);

    emscripten_ਸੈੱਟ_resize_callback(EMSCRIPTEN_EVENT_ਨਿਸ਼ਾਨਾ_ਖਿੜਕੀ, device, 0, Emscripten_HandleResizeGlobal);
}

ਖਾਲੀ Emscripten_UnregisterGlobalEventHandlers(SDL_VideoDevice *device)
{
    Emscripten_unset_global_mouseup_callback(device);

    emscripten_ਸੈੱਟ_focus_callback(EMSCRIPTEN_EVENT_ਨਿਸ਼ਾਨਾ_ਖਿੜਕੀ, ਨਿਰਾ, 0, ਨਿਰਾ);
    emscripten_ਸੈੱਟ_blur_callback(EMSCRIPTEN_EVENT_ਨਿਸ਼ਾਨਾ_ਖਿੜਕੀ, ਨਿਰਾ, 0, ਨਿਰਾ);

    emscripten_ਸੈੱਟ_pointerlockchange_callback(EMSCRIPTEN_EVENT_ਨਿਸ਼ਾਨਾ_DOCUMENT, ਨਿਰਾ, 0, ਨਿਰਾ);

    emscripten_ਸੈੱਟ_fullscreenchange_callback(EMSCRIPTEN_EVENT_ਨਿਸ਼ਾਨਾ_DOCUMENT, ਨਿਰਾ, 0, ਨਿਰਾ);

    emscripten_ਸੈੱਟ_resize_callback(EMSCRIPTEN_EVENT_ਨਿਸ਼ਾਨਾ_ਖਿੜਕੀ, ਨਿਰਾ, 0, ਨਿਰਾ);
}

EMSCRIPTEN_KEEPALIVE ਖਾਲੀ Emscripten_Handle_ਤਾਲਾ_ਕੁੰਜੀਆਂ_Check(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਖਿੜਕੀ_ਅੰਕੜੇ_2, EM_BOOL capslock, EM_BOOL numlock, EM_BOOL scrolllock)
{
    ਅਚਲ SDL_Keymod new_mods = (capslock ? SDL_KMOD_CAPS : 0) | (numlock ? SDL_KMOD_ਅੰਕ : 0) | (scrolllock ? SDL_KMOD_SCROLL : 0);
    SDL_Keymod modstate = SDL_GetModState();
    ਜੇ ((modstate & (SDL_KMOD_CAPS|SDL_KMOD_ਅੰਕ|SDL_KMOD_SCROLL)) != new_mods) {
        modstate &= ~(SDL_KMOD_CAPS|SDL_KMOD_ਅੰਕ|SDL_KMOD_SCROLL);
        modstate |= new_mods;
        SDL_ਸੈੱਟ_Mod_State(modstate);
    }
}

ਖਾਲੀ Emscripten_ਰਜਿਸਟਰ_Event_Handlers(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ)
{
    ਅਚਲ ਅੱਖਰ *ਕੁੰਜੀ_Element;

    // There is only one window and that window is the canvas
    emscripten_ਸੈੱਟ_wheel_callback(ਅੰਕੜੇ->canvas_id, ਅੰਕੜੇ, 0, Emscripten_HandleWheel);

    emscripten_ਸੈੱਟ_orientationchange_callback(ਅੰਕੜੇ, 0, Emscripten_HandleOrientationChange);

    ਕੁੰਜੀ_Element = Emscripten_Get_Keyboard_ਨਿਸ਼ਾਨਾ_Element(ਅੰਕੜੇ->keyboard_element);
    ਜੇ (ਕੁੰਜੀ_Element) {
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
        emscripten_ਸੈੱਟ_keydown_callback(ਕੁੰਜੀ_Element, ਨਿਰਾ, 0, ਨਿਰਾ);
        emscripten_ਸੈੱਟ_keyup_callback(ਕੁੰਜੀ_Element, ਨਿਰਾ, 0, ਨਿਰਾ);
        emscripten_ਸੈੱਟ_keypress_callback(ਕੁੰਜੀ_Element, ਨਿਰਾ, 0, ਨਿਰਾ);

        MAIN_THREAD_EM_ASM_INT({
            var ਅੰਕੜੇ = $0;
            // our keymod state can get confused in various ways (changed capslock when browser didn't have focus, etc), and you can't query the current
            //  state from the DOM, outside of a keyboard event, so catch keypresses globally and reset mod state if it's unexpectedly wrong. Best we can do.
            //  Note that this thing _only_ adjusts the lock keys if necessary; the real SDL keypress handling happens elsewhere.

            // Remove any prior listener first -- `addEventListener` does not deduplicate either.
            ਜੇ (document.sdl_Event_Handler_ਤਾਲਾ_ਕੁੰਜੀਆਂ_Check) {
                document.removeEventListener("keydown", document.sdl_Event_Handler_ਤਾਲਾ_ਕੁੰਜੀਆਂ_Check);
            }

            document.sdl_Event_Handler_ਤਾਲਾ_ਕੁੰਜੀਆਂ_Check = function(event) {
                // don't try to adjust the state on the actual lock key presses; the normal key handler will catch that and adjust.
                ਜੇ ((event.ਕੁੰਜੀ != "CapsLock") && (event.ਕੁੰਜੀ != "NumLock") && (event.ਕੁੰਜੀ != "ScrollLock"))
                {
                    Emscripten_Handle_ਤਾਲਾ_ਕੁੰਜੀਆਂ_Check_2(Module['SDL3'].JSVar_ਮੰਜ਼ਿਲ_CPtr(ਅੰਕੜੇ), event.getModifierState("CapsLock"), event.getModifierState("NumLock"), event.getModifierState("ScrollLock"));
                }
            };
            document.ਜੋੜੋ_Event_Listener("keydown", document.sdl_Event_Handler_ਤਾਲਾ_ਕੁੰਜੀਆਂ_Check);
        }, ਅੰਕੜੇ);
        emscripten_ਸੈੱਟ_keydown_callback(ਕੁੰਜੀ_Element, ਅੰਕੜੇ, 0, Emscripten_Handle_ਕੁੰਜੀ);
        emscripten_ਸੈੱਟ_keyup_callback(ਕੁੰਜੀ_Element, ਅੰਕੜੇ, 0, Emscripten_Handle_ਕੁੰਜੀ);
        emscripten_ਸੈੱਟ_keypress_callback(ਕੁੰਜੀ_Element, ਅੰਕੜੇ, 0, Emscripten_Handle_ਕੁੰਜੀ_Press);
    }

    emscripten_ਸੈੱਟ_visibilitychange_callback(ਅੰਕੜੇ, 0, Emscripten_HandleVisibilityChange);

    emscripten_ਸੈੱਟ_beforeunload_callback(ਅੰਕੜੇ, Emscripten_HandleBeforeUnload);

    // !!! FIXME: currently Emscripten doesn't have a Pointer Events functions like emscripten_set_*_callback, but we should use those when they do:
    // !!! FIXME:  https://github.com/emscripten-core/emscripten/issues/7278#issuecomment-2280024621
    Emscripten_ਸੈੱਟ_ਸੂਚਕ_event_callbacks(ਅੰਕੜੇ);

    // !!! FIXME: currently Emscripten doesn't have a Drop Events functions like emscripten_set_*_callback, but we should use those when they do:
    Emscripten_ਸੈੱਟ_drag_event_callbacks(ਅੰਕੜੇ);
}

ਖਾਲੀ Emscripten_UnregisterEventHandlers(SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ)
{
    ਅਚਲ ਅੱਖਰ *ਕੁੰਜੀ_Element;

    // !!! FIXME: currently Emscripten doesn't have a Drop Events functions like emscripten_set_*_callback, but we should use those when they do:
    Emscripten_unset_drag_event_callbacks(ਅੰਕੜੇ);

    // !!! FIXME: currently Emscripten doesn't have a Pointer Events functions like emscripten_set_*_callback, but we should use those when they do:
    // !!! FIXME:  https://github.com/emscripten-core/emscripten/issues/7278#issuecomment-2280024621
    Emscripten_unset_ਸੂਚਕ_event_callbacks(ਅੰਕੜੇ);

    // only works due to having one window
    emscripten_ਸੈੱਟ_wheel_callback(ਅੰਕੜੇ->canvas_id, ਨਿਰਾ, 0, ਨਿਰਾ);

    emscripten_ਸੈੱਟ_orientationchange_callback(ਨਿਰਾ, 0, ਨਿਰਾ);

    ਕੁੰਜੀ_Element = Emscripten_Get_Keyboard_ਨਿਸ਼ਾਨਾ_Element(ਅੰਕੜੇ->keyboard_element);
    ਜੇ (ਕੁੰਜੀ_Element) {
        emscripten_ਸੈੱਟ_keydown_callback(ਕੁੰਜੀ_Element, ਨਿਰਾ, 0, ਨਿਰਾ);
        emscripten_ਸੈੱਟ_keyup_callback(ਕੁੰਜੀ_Element, ਨਿਰਾ, 0, ਨਿਰਾ);
        emscripten_ਸੈੱਟ_keypress_callback(ਕੁੰਜੀ_Element, ਨਿਰਾ, 0, ਨਿਰਾ);
        MAIN_THREAD_EM_ASM_INT({
            document.removeEventListener("keydown", document.sdl_Event_Handler_ਤਾਲਾ_ਕੁੰਜੀਆਂ_Check);
        });
    }

    emscripten_ਸੈੱਟ_visibilitychange_callback(ਨਿਰਾ, 0, ਨਿਰਾ);

    emscripten_ਸੈੱਟ_beforeunload_callback(ਨਿਰਾ, ਨਿਰਾ);
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_EMSCRIPTEN

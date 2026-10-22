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

#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_EMSCRIPTEN

#شامل <emscripten/html5.h>
#شامل <emscripten/dom_pk_codes.h>

#شامل "../../events/SDL_dropevents_c.h"
#شامل "../../events/SDL_events_c.h"
#شامل "../../events/SDL_keyboard_c.h"
#شامل "../../events/SDL_touch_c.h"

#شامل "SDL_emscriptenevents.h"
#شامل "SDL_emscriptenvideo.h"

/*
Emscripten PK code to scancode
https://developer.mozilla.org/en-US/docs/Web/API/KeyboardEvent
https://developer.mozilla.org/en-US/docs/Web/API/KeyboardEvent/code
*/
ساکن ثابت SDL_Scancode emscripten_scancode_جدول[] = {
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

ساکن SDL_Scancode Emscripten_Map_جائزہ_رمز(ثابت حرف *رمز)
{
    ثابت DOM_PK_رمز_TYPE pk_رمز = emscripten_compute_dom_pk_رمز(رمز);
    اگر (pk_رمز < SDL_arraysize(emscripten_scancode_جدول)) {
        واپس emscripten_scancode_جدول[pk_رمز];
    }

    انتخاب (pk_رمز) {
    حالت DOM_PK_PASTE:
        واپس SDL_SCANCODE_PASTE;
    حالت DOM_PK_MEDIA_TRACK_پچھلا:
        واپس SDL_SCANCODE_MEDIA_پچھلا_TRACK;
    حالت DOM_PK_CUT:
        واپس SDL_SCANCODE_CUT;
    حالت DOM_PK_COPY:
        واپس SDL_SCANCODE_COPY;
    حالت DOM_PK_MEDIA_TRACK_اگلا:
        واپس SDL_SCANCODE_MEDIA_اگلا_TRACK;
    حالت DOM_PK_NUMPAD_ENTER:
        واپس SDL_SCANCODE_KP_ENTER;
    حالت DOM_PK_CONTROL_دایاں:
        واپس SDL_SCANCODE_RCTRL;
    حالت DOM_PK_AUDIO_VOLUME_MUTE:
        واپس SDL_SCANCODE_MUTE;
    حالت DOM_PK_MEDIA_PLAY_PAUSE:
        واپس SDL_SCANCODE_MEDIA_PLAY_PAUSE;
    حالت DOM_PK_MEDIA_STOP:
        واپس SDL_SCANCODE_MEDIA_STOP;
    حالت DOM_PK_EJECT:
        واپس SDL_SCANCODE_MEDIA_EJECT;
    حالت DOM_PK_AUDIO_VOLUME_نیچے_کو:
        واپس SDL_SCANCODE_VOLUMEDOWN;
    حالت DOM_PK_AUDIO_VOLUME_اوپر:
        واپس SDL_SCANCODE_VOLUMEUP;
    حالت DOM_PK_BROWSER_HOME:
        واپس SDL_SCANCODE_AC_HOME;
    حالت DOM_PK_NUMPAD_DIVIDE:
        واپس SDL_SCANCODE_KP_DIVIDE;
    حالت DOM_PK_ALT_دایاں:
        واپس SDL_SCANCODE_RALT;
    حالت DOM_PK_HELP:
        واپس SDL_SCANCODE_HELP;
    حالت DOM_PK_عدد_تالا:
        واپس SDL_SCANCODE_NUMLOCKCLEAR;
    حالت DOM_PK_HOME:
        واپس SDL_SCANCODE_HOME;
    حالت DOM_PK_ARROW_اوپر:
        واپس SDL_SCANCODE_اوپر;
    حالت DOM_PK_صفحہ_اوپر:
        واپس SDL_SCANCODE_PAGEUP;
    حالت DOM_PK_ARROW_بایاں:
        واپس SDL_SCANCODE_بایاں;
    حالت DOM_PK_ARROW_دایاں:
        واپس SDL_SCANCODE_دایاں;
    حالت DOM_PK_انتہا:
        واپس SDL_SCANCODE_انتہا;
    حالت DOM_PK_ARROW_نیچے_کو:
        واپس SDL_SCANCODE_نیچے_کو;
    حالت DOM_PK_صفحہ_نیچے_کو:
        واپس SDL_SCANCODE_PAGEDOWN;
    حالت DOM_PK_داخل_کرو:
        واپس SDL_SCANCODE_داخل_کرو;
    حالت DOM_PK_DELETE:
        واپس SDL_SCANCODE_DELETE;
    حالت DOM_PK_META_بایاں:
        واپس SDL_SCANCODE_LGUI;
    حالت DOM_PK_META_دایاں:
        واپس SDL_SCANCODE_RGUI;
    حالت DOM_PK_CONTEXT_MENU:
        واپس SDL_SCANCODE_APPLICATION;
    حالت DOM_PK_POWER:
        واپس SDL_SCANCODE_POWER;
    حالت DOM_PK_BROWSER_تلاش:
        واپس SDL_SCANCODE_AC_تلاش;
    حالت DOM_PK_BROWSER_FAVORITES:
        واپس SDL_SCANCODE_AC_BOOKMARKS;
    حالت DOM_PK_BROWSER_REFRESH:
        واپس SDL_SCANCODE_AC_REFRESH;
    حالت DOM_PK_BROWSER_STOP:
        واپس SDL_SCANCODE_AC_STOP;
    حالت DOM_PK_BROWSER_FORWARD:
        واپس SDL_SCANCODE_AC_FORWARD;
    حالت DOM_PK_BROWSER_عقب:
        واپس SDL_SCANCODE_AC_عقب;
    حالت DOM_PK_MEDIA_SELECT:
        واپس SDL_SCANCODE_MEDIA_SELECT;
    }

    واپس SDL_SCANCODE_UNKNOWN;
}

ساکن SDL_کھڑکی *Emscripten_Get_Focused_کھڑکی(SDL_VideoDevice *device)
{
    SDL_کھڑکی *کھڑکی;
    برائے (کھڑکی = device->windows; کھڑکی; کھڑکی = کھڑکی->اگلا) {
        SDL_کھڑکی_ڈیٹا *wdata = کھڑکی->اندرونی_2;

        ثابت صحیح focused = MAIN_THREAD_EM_ASM_INT({
            var id = UTF8_مقصد_String($0);
            try
            {
                var canvas = document.querySelector(id);
                اگر (canvas) {
                    واپس canvas === document.فعال_Element;
                }
            }
            catch (e)
            {
                // querySelector throws if not a valid selector
            }
            واپس false;
        }, wdata->canvas_id);

        اگر (focused) {
            توڑو;
        }
    }
    // If the DOM is focused, then at least one canvas in the DOM should be considered focused.
    // So in this case, just assume that the first canvas is focused.
    اگر (!کھڑکی) {
        ثابت صحیح focused = MAIN_THREAD_EM_ASM_INT({
            واپس document.hasFocus();
        });
        اگر (focused) {
            کھڑکی = device->windows;
        }
    }
    واپس کھڑکی;
}

ساکن EM_BOOL Emscripten_Handle_اشارہ_گر_تالا_Change(صحیح eventType, ثابت EmscriptenPointerlockChangeEvent *changeEvent, خالی *user_ڈیٹا)
{
    SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2 = (SDL_کھڑکی_ڈیٹا *)user_ڈیٹا;
    // keep track of lock losses, so we can regrab if/when appropriate.
    کھڑکی_ڈیٹا_2->has_اشارہ_گر_تالا = changeEvent->is_فعال;
    واپس 0;
}

ساکن EM_BOOL Emscripten_Handle_اشارہ_گر_تالا_Change_Global(صحیح eventType, ثابت EmscriptenPointerlockChangeEvent *changeEvent, خالی *user_ڈیٹا)
{
    SDL_VideoDevice *device = user_ڈیٹا;
    bool prevent_default = false;
    SDL_کھڑکی *کھڑکی;

    برائے (کھڑکی = device->windows; کھڑکی; کھڑکی = کھڑکی->اگلا) {
        prevent_default |= Emscripten_Handle_اشارہ_گر_تالا_Change(eventType, changeEvent, کھڑکی->اندرونی_2);
    }

    واپس prevent_default;
}

ساکن EM_BOOL Emscripten_HandleWheel(صحیح eventType, ثابت EmscriptenWheelEvent *wheelEvent, خالی *user_ڈیٹا)
{
    SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2 = user_ڈیٹا;

    اعشاری deltaY = wheelEvent->deltaY;
    اعشاری deltaX = wheelEvent->deltaX;

    انتخاب (wheelEvent->delta_منوال) {
    حالت DOM_DELTA_PIXEL:
        deltaX /= 100; // 100 pixels make up a step
        deltaY /= 100; // 100 pixels make up a step
        توڑو;
    حالت DOM_DELTA_سطر:
        deltaX /= 3; // 3 lines make up a step
        deltaY /= 3; // 3 lines make up a step
        توڑو;
    حالت DOM_DELTA_صفحہ:
        deltaX *= 80; // A page makes up 80 steps
        deltaY *= 80; // A page makes up 80 steps
        توڑو;
    }

    SDL_SendMouseWheel(0, کھڑکی_ڈیٹا_2->کھڑکی, SDL_DEFAULT_MOUSE_ID, deltaX, -deltaY, SDL_MOUSEWHEEL_معمول);
    واپس SDL_EventEnabled(SDL_EVENT_MOUSE_WHEEL);
}

ساکن EM_BOOL Emscripten_HandleFocus(صحیح eventType, ثابت EmscriptenFocusEvent *focusEvent, خالی *user_ڈیٹا)
{
    SDL_VideoDevice *device = user_ڈیٹا;
    SDL_کھڑکی *کھڑکی = Emscripten_Get_Focused_کھڑکی(device);

    SDL_EventType sdl_event_type;

    /* If the user switches away while keys are pressed (such as
     * via Alt+Tab), key release events won't be received. */
    اگر (eventType == EMSCRIPTEN_EVENT_BLUR) {
        SDL_ResetKeyboard();
    }

    sdl_event_type = (eventType == EMSCRIPTEN_EVENT_FOCUS) ? SDL_EVENT_کھڑکی_FOCUS_GAINED : SDL_EVENT_کھڑکی_FOCUS_گمشدہ;
    SDL_سیٹ_Keyboard_Focus(sdl_event_type == SDL_EVENT_کھڑکی_FOCUS_GAINED ? کھڑکی : تہی);
    واپس SDL_EventEnabled(sdl_event_type);
}

ساکن bool Is_Function_کلید(SDL_Scancode scancode)
{
    اگر (scancode >= SDL_SCANCODE_F1 && scancode <= SDL_SCANCODE_F12) {
        واپس true;
    }
    اگر (scancode >= SDL_SCANCODE_F13 && scancode <= SDL_SCANCODE_F24) {
        واپس true;
    }
    واپس false;
}

/* This is a great tool to see web keyboard events live:
 * https://w3c.github.io/uievents/tools/key-event-viewer.html
 */
ساکن EM_BOOL Emscripten_Handle_کلید(صحیح eventType, ثابت EmscriptenKeyboardEvent *کلید_Event, خالی *user_ڈیٹا)
{
    SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2 = (SDL_کھڑکی_ڈیٹا *)user_ڈیٹا;
    SDL_Scancode scancode = Emscripten_Map_جائزہ_رمز(کلید_Event->رمز);
    SDL_Keycode keycode = SDLK_UNKNOWN;
    bool prevent_default = false;
    bool is_nav_کلید = false;

    اگر (scancode == SDL_SCANCODE_UNKNOWN) {
        اگر (SDL_strcmp(کلید_Event->کلید, "Sleep") == 0) {
            scancode = SDL_SCANCODE_SLEEP;
        } ورنہ اگر (SDL_strcmp(کلید_Event->کلید, "ChannelUp") == 0) {
            scancode = SDL_SCANCODE_CHANNEL_INCREMENT;
        } ورنہ اگر (SDL_strcmp(کلید_Event->کلید, "ChannelDown") == 0) {
            scancode = SDL_SCANCODE_CHANNEL_DECREMENT;
        } ورنہ اگر (SDL_strcmp(کلید_Event->کلید, "MediaPlay") == 0) {
            scancode = SDL_SCANCODE_MEDIA_PLAY;
        } ورنہ اگر (SDL_strcmp(کلید_Event->کلید, "MediaPause") == 0) {
            scancode = SDL_SCANCODE_MEDIA_PAUSE;
        } ورنہ اگر (SDL_strcmp(کلید_Event->کلید, "MediaRecord") == 0) {
            scancode = SDL_SCANCODE_MEDIA_ریکارڈ;
        } ورنہ اگر (SDL_strcmp(کلید_Event->کلید, "MediaFastForward") == 0) {
            scancode = SDL_SCANCODE_MEDIA_FAST_FORWARD;
        } ورنہ اگر (SDL_strcmp(کلید_Event->کلید, "MediaRewind") == 0) {
            scancode = SDL_SCANCODE_MEDIA_REWIND;
        } ورنہ اگر (SDL_strcmp(کلید_Event->کلید, "Close") == 0) {
            scancode = SDL_SCANCODE_AC_CLOSE;
        } ورنہ اگر (SDL_strcmp(کلید_Event->کلید, "New") == 0) {
            scancode = SDL_SCANCODE_AC_NEW;
        } ورنہ اگر (SDL_strcmp(کلید_Event->کلید, "Open") == 0) {
            scancode = SDL_SCANCODE_AC_OPEN;
        } ورنہ اگر (SDL_strcmp(کلید_Event->کلید, "Print") == 0) {
            scancode = SDL_SCANCODE_AC_PRINT;
        } ورنہ اگر (SDL_strcmp(کلید_Event->کلید, "Save") == 0) {
            scancode = SDL_SCANCODE_AC_SAVE;
        } ورنہ اگر (SDL_strcmp(کلید_Event->کلید, "Props") == 0) {
            scancode = SDL_SCANCODE_AC_PROPERTIES;
        }
    }

    اگر (scancode == SDL_SCANCODE_UNKNOWN) {
        // KaiOS Left Soft Key and Right Soft Key, they act as OK/Next/Menu and Cancel/Back/Clear
        اگر (SDL_strcmp(کلید_Event->کلید, "SoftLeft") == 0) {
            scancode = SDL_SCANCODE_AC_FORWARD;
        } ورنہ اگر (SDL_strcmp(کلید_Event->کلید, "SoftRight") == 0) {
            scancode = SDL_SCANCODE_AC_عقب;
        }
    }

    اگر (کلید_Event->location == 0 && SDL_utf8strlen(کلید_Event->کلید) == 1) {
        ثابت حرف *کلید = کلید_Event->کلید;
        keycode = SDL_قدم_UTF8(&کلید, تہی);
        اگر (keycode == SDL_INVALID_UNICODE_CODEPOINT) {
            keycode = SDLK_UNKNOWN;
        }
    }

    اگر (keycode != SDLK_UNKNOWN) {
        prevent_default = SDL_Send_Keyboard_کلید_And_Keycode(0, SDL_DEFAULT_KEYBOARD_ID, 0, scancode, keycode, (eventType == EMSCRIPTEN_EVENT_KEYDOWN));
    } ورنہ {
        prevent_default = SDL_Send_Keyboard_کلید(0, SDL_DEFAULT_KEYBOARD_ID, 0, scancode, (eventType == EMSCRIPTEN_EVENT_KEYDOWN));
    }

    /* if TEXTINPUT events are enabled we can't prevent keydown or we won't get keypress
     * we need to ALWAYS prevent backspace and tab otherwise chrome takes action and does bad navigation UX
     */
    اگر ((scancode == SDL_SCANCODE_BACKSPACE) ||
        (scancode == SDL_SCANCODE_TAB) ||
        (scancode == SDL_SCANCODE_بایاں) ||
        (scancode == SDL_SCANCODE_اوپر) ||
        (scancode == SDL_SCANCODE_دایاں) ||
        (scancode == SDL_SCANCODE_نیچے_کو) ||
        Is_Function_کلید(scancode) ||
        کلید_Event->ctrl_کلید) {
        is_nav_کلید = true;
    }

    اگر ((eventType == EMSCRIPTEN_EVENT_KEYDOWN) && SDL_متن_داخلہ_فعال(کھڑکی_ڈیٹا_2->کھڑکی) && !is_nav_کلید) {
        prevent_default = false;
    }

    واپس prevent_default;
}

ساکن EM_BOOL Emscripten_Handle_کلید_Press(صحیح eventType, ثابت EmscriptenKeyboardEvent *کلید_Event, خالی *user_ڈیٹا)
{
    SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2 = (SDL_کھڑکی_ڈیٹا *)user_ڈیٹا;

    اگر (SDL_متن_داخلہ_فعال(کھڑکی_ڈیٹا_2->کھڑکی)) {
        اگر (SDL_utf8strlen(کلید_Event->کلید) == 1) {
            SDL_Send_Keyboard_متن(کلید_Event->کلید);
            واپس EM_TRUE;
        }
    }
    واپس EM_FALSE;
}

ساکن EM_BOOL Emscripten_HandleFullscreenChange(صحیح eventType, ثابت EmscriptenFullscreenChangeEvent *fullscreenChangeEvent, خالی *user_ڈیٹا)
{
    SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2 = user_ڈیٹا;

    کھڑکی_ڈیٹا_2->fullscreen_change_اندر_پیش_رفت = false;

    اگر (fullscreenChangeEvent->isFullscreen) {
        SDL_Send_کھڑکی_Event(کھڑکی_ڈیٹا_2->کھڑکی, SDL_EVENT_کھڑکی_ENTER_FULLSCREEN, 0, 0);
        کھڑکی_ڈیٹا_2->fullscreen_منوال_flags = 0;
    } ورنہ {
        SDL_Send_کھڑکی_Event(کھڑکی_ڈیٹا_2->کھڑکی, SDL_EVENT_کھڑکی_LEAVE_FULLSCREEN, 0, 0);
    }

    SDL_Update_Fullscreen_منوال(کھڑکی_ڈیٹا_2->کھڑکی, fullscreenChangeEvent->isFullscreen, false);

    واپس 0;
}

ساکن EM_BOOL Emscripten_HandleFullscreenChangeGlobal(صحیح eventType, ثابت EmscriptenFullscreenChangeEvent *fullscreenChangeEvent, خالی *user_ڈیٹا)
{
    SDL_VideoDevice *device = user_ڈیٹا;
    SDL_کھڑکی *کھڑکی = تہی;
    برائے (کھڑکی = device->windows; کھڑکی != تہی; کھڑکی = کھڑکی->اگلا) {
        ثابت حرف *canvas_id = کھڑکی->اندرونی_2->canvas_id;
        اگر (*canvas_id == '#') {
            canvas_id++;
        }
        اگر (SDL_strcmp(fullscreenChangeEvent->id, canvas_id) == 0) {
            توڑو;  // this is the window.
        }
    }

    اگر (کھڑکی) {
        واپس Emscripten_HandleFullscreenChange(eventType, fullscreenChangeEvent, کھڑکی->اندرونی_2);
    }

    واپس EM_FALSE;
}

ساکن EM_BOOL Emscripten_HandleResize(صحیح eventType, ثابت EmscriptenUiEvent *uiEvent, خالی *user_ڈیٹا)
{
    SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2 = user_ڈیٹا;

    bool force = false;

    // update pixel ratio
    اگر (کھڑکی_ڈیٹا_2->کھڑکی->flags & SDL_کھڑکی_بلند_PIXEL_DENSITY) {
        اگر (کھڑکی_ڈیٹا_2->pixel_تناسب != emscripten_get_device_pixel_تناسب()) {
            کھڑکی_ڈیٹا_2->pixel_تناسب = emscripten_get_device_pixel_تناسب();
            force = true;
        }
    }

    ثابت bool fill_document = (Emscripten_fill_document_کھڑکی == کھڑکی_ڈیٹا_2->کھڑکی);
    ثابت bool fullscreen = (کھڑکی_ڈیٹا_2->کھڑکی->flags & SDL_کھڑکی_FULLSCREEN) != 0;  // fullscreen windows can resize on Emscripten, and the canvas should fill it.
    ثابت bool resizable = (کھڑکی_ڈیٹا_2->کھڑکی->flags & SDL_کھڑکی_RESIZABLE) != 0;
    اگر (fill_document || fullscreen || resizable) {
        دوہرا w, h;
        اگر (fill_document || fullscreen) {
            w = (دوہرا) uiEvent->کھڑکی_Inner_چوڑائی;
            h = (دوہرا) uiEvent->کھڑکی_Inner_اونچائی;
        } ورنہ {
            SDL_assert(کھڑکی_ڈیٹا_2->کھڑکی->flags & SDL_کھڑکی_RESIZABLE);
            w = کھڑکی_ڈیٹا_2->کھڑکی->w;
            h = کھڑکی_ڈیٹا_2->کھڑکی->h;
            // this will only work if the canvas size is set through css
            اگر (کھڑکی_ڈیٹا_2->external_سائز) {
                emscripten_get_element_css_سائز(کھڑکی_ڈیٹا_2->canvas_id, &w, &h);
            }
        }

        emscripten_سیٹ_canvas_element_سائز(کھڑکی_ڈیٹا_2->canvas_id, SDL_lroundf(w * کھڑکی_ڈیٹا_2->pixel_تناسب), SDL_lroundf(h * کھڑکی_ڈیٹا_2->pixel_تناسب));

        // set_canvas_size unsets this
        اگر (!کھڑکی_ڈیٹا_2->external_سائز && کھڑکی_ڈیٹا_2->pixel_تناسب != 1.0f) {
            emscripten_سیٹ_element_css_سائز(کھڑکی_ڈیٹا_2->canvas_id, w, h);
        }

        اگر (force) {
            // force the event to trigger, so pixel ratio changes can be handled
            کھڑکی_ڈیٹا_2->کھڑکی->w = 0;
            کھڑکی_ڈیٹا_2->کھڑکی->h = 0;
        }

        SDL_Send_کھڑکی_Event(کھڑکی_ڈیٹا_2->کھڑکی, SDL_EVENT_کھڑکی_RESIZED, SDL_lroundf(w), SDL_lroundf(h));
    }

    واپس 0;
}

ساکن EM_BOOL Emscripten_HandleResizeGlobal(صحیح eventType, ثابت EmscriptenUiEvent *uiEvent, خالی *user_ڈیٹا)
{
    SDL_VideoDevice *device = user_ڈیٹا;
    bool prevent_default = false;
    SDL_کھڑکی *کھڑکی;

    برائے (کھڑکی = device->windows; کھڑکی; کھڑکی = کھڑکی->اگلا) {
        prevent_default |= Emscripten_HandleResize(eventType, uiEvent, کھڑکی->اندرونی_2);
    }

    واپس prevent_default;
}

EM_BOOL
Emscripten_HandleCanvasResize(صحیح eventType, ثابت خالی *reserved, خالی *user_ڈیٹا)
{
    // this is used during fullscreen changes
    SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2 = user_ڈیٹا;

    اگر (کھڑکی_ڈیٹا_2->fullscreen_resize) {
        دوہرا css_w, css_h;
        emscripten_get_element_css_سائز(کھڑکی_ڈیٹا_2->canvas_id, &css_w, &css_h);
        SDL_Send_کھڑکی_Event(کھڑکی_ڈیٹا_2->کھڑکی, SDL_EVENT_کھڑکی_RESIZED, SDL_lroundf(css_w), SDL_lroundf(css_h));
    }

    واپس 0;
}

ساکن EM_BOOL Emscripten_HandleVisibilityChange(صحیح eventType, ثابت EmscriptenVisibilityChangeEvent *visEvent, خالی *user_ڈیٹا)
{
    SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2 = user_ڈیٹا;
    SDL_Send_کھڑکی_Event(کھڑکی_ڈیٹا_2->کھڑکی, visEvent->hidden ? SDL_EVENT_کھڑکی_HIDDEN : SDL_EVENT_کھڑکی_SHOWN, 0, 0);
    واپس 0;
}

ساکن ثابت حرف *Emscripten_HandleBeforeUnload(صحیح eventType, ثابت خالی *reserved, خالی *user_ڈیٹا)
{
    /* This event will need to be handled synchronously, e.g. using
       SDL_AddEventWatch, as the page is being closed *now*. */
    SDL_SendQuit();  // the app might see this if they installed an event watcher.
    SDL_OnApplicationWillTerminate();  // calls SDL_AppQuit if appropriate, etc.
    واپس ""; // don't trigger confirmation dialog
}

ساکن EM_BOOL Emscripten_HandleOrientationChange(صحیح eventType, ثابت EmscriptenOrientationChangeEvent *orientationChangeEvent, خالی *user_ڈیٹا)
{
    SDL_DisplayOrientation orientation;
    انتخاب (orientationChangeEvent->orientation_اشاریہ) {
        #تعریف_کرو CHECK_ORIENTATION(emsdk, sdl) حالت EMSCRIPTEN_ORIENTATION_##emsdk: orientation = SDL_ORIENTATION_##sdl; توڑو
        CHECK_ORIENTATION(LANDSCAPE_PRIMARY, LANDSCAPE);
        CHECK_ORIENTATION(LANDSCAPE_SECONDARY, LANDSCAPE_FLIPPED);
        CHECK_ORIENTATION(PORTRAIT_PRIMARY, PORTRAIT);
        CHECK_ORIENTATION(PORTRAIT_SECONDARY, PORTRAIT_FLIPPED);
        #تعریف_منسوخ CHECK_ORIENTATION
        طےشدہ: orientation = SDL_ORIENTATION_UNKNOWN; توڑو;
    }

    SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2 = (SDL_کھڑکی_ڈیٹا *) user_ڈیٹا;
    SDL_SendDisplayEvent(SDL_Get_Video_Display_For_کھڑکی(کھڑکی_ڈیٹا_2->کھڑکی), SDL_EVENT_DISPLAY_ORIENTATION, orientation, 0);

    // fake a UI event so we can tell the app the canvas might have resized.
    EmscriptenUiEvent uiEvent;
    SDL_zero(uiEvent);
    uiEvent.document_Body_Client_چوڑائی = MAIN_THREAD_EM_ASM_INT( { واپس document.body.client_چوڑائی; } );
    uiEvent.document_Body_Client_اونچائی = MAIN_THREAD_EM_ASM_INT( { واپس document.body.client_اونچائی; } );
    uiEvent.کھڑکی_Inner_چوڑائی = MAIN_THREAD_EM_ASM_INT( { واپس کھڑکی.inner_چوڑائی; } );
    uiEvent.کھڑکی_Inner_اونچائی = MAIN_THREAD_EM_ASM_INT( { واپس کھڑکی.inner_اونچائی; } );
    uiEvent.کھڑکی_Outer_چوڑائی = MAIN_THREAD_EM_ASM_INT( { واپس کھڑکی.outer_چوڑائی; } );
    uiEvent.کھڑکی_Outer_اونچائی = MAIN_THREAD_EM_ASM_INT( { واپس کھڑکی.outer_اونچائی; } );
    uiEvent.scroll_چوٹی = MAIN_THREAD_EM_ASM_INT( { واپس کھڑکی.صفحہ_XOffset; } );
    uiEvent.scroll_بایاں = MAIN_THREAD_EM_ASM_INT( { واپس کھڑکی.صفحہ_YOffset; } );
    Emscripten_HandleResize(EMSCRIPTEN_EVENT_RESIZE, &uiEvent, user_ڈیٹا);

    واپس 0;
}

// IF YOU CHANGE THIS STRUCTURE, YOU NEED TO UPDATE THE JAVASCRIPT THAT FILLS IT IN: SDL3.makePointerEventCStruct, below.
#تعریف_کرو PTRTYPE_MOUSE 1
#تعریف_کرو PTRTYPE_TOUCH 2
#تعریف_کرو PTRTYPE_PEN 3
قسمتعریف ساخت Emscripten_اشارہ_گر_Event
{
    صحیح اشارہ_گر_type;
    صحیح pointerid;
    صحیح button;
    صحیح buttons;
    صحیح نیچے_کو;
    اعشاری movementX;
    اعشاری movementY;
    اعشاری ہدف_X;
    اعشاری ہدف_Y;
    اعشاری pressure;
    اعشاری tangential_pressure;
    اعشاری tiltx;
    اعشاری tilty;
    اعشاری rotation;
} Emscripten_اشارہ_گر_Event;

ساکن خالی Emscripten_HandleMouseButton(SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2, ثابت Emscripten_اشارہ_گر_Event *event)
{
    Uint8 sdl_button;
    bool نیچے_کو = false;
    انتخاب (event->button) {
        #تعریف_کرو CHECK_MOUSE_BUTTON(jsbutton, downflag, sdlbutton) حالت jsbutton: sdl_button = SDL_BUTTON_##sdlbutton; نیچے_کو = (event->نیچے_کو != 0) || ((event->buttons & downflag) != 0); توڑو
        CHECK_MOUSE_BUTTON(0, 1, بایاں_2);
        CHECK_MOUSE_BUTTON(1, 4, درمیان_2);
        CHECK_MOUSE_BUTTON(2, 2, دایاں_2);
        CHECK_MOUSE_BUTTON(3, 8, X1);
        CHECK_MOUSE_BUTTON(4, 16, X2);
        #تعریف_منسوخ CHECK_MOUSE_BUTTON
        طےشدہ: sdl_button = 0; توڑو;
    }

    اگر (sdl_button) {
        ثابت SDL_Mouse *mouse = SDL_GetMouse();
        SDL_assert(mouse != تہی);

        اگر (نیچے_کو) {
            اگر (mouse->relative_منوال && !کھڑکی_ڈیٹا_2->has_اشارہ_گر_تالا) {
                emscripten_request_pointerlock(کھڑکی_ڈیٹا_2->canvas_id, 0); // try to regrab lost pointer lock.
            }
        }

        SDL_SendMouseButton(0, کھڑکی_ڈیٹا_2->کھڑکی, SDL_DEFAULT_MOUSE_ID, sdl_button, نیچے_کو);

        // We have an imaginary mouse capture, because we need SDL to not drop our imaginary mouse focus when we leave the canvas.
        اگر (mouse->auto_capture) {
            اگر (SDL_GetMouseState(تہی, تہی) != 0) {
                کھڑکی_ڈیٹا_2->کھڑکی->flags |= SDL_کھڑکی_MOUSE_CAPTURE;
            } ورنہ {
                کھڑکی_ڈیٹا_2->کھڑکی->flags &= ~SDL_کھڑکی_MOUSE_CAPTURE;
            }
        }

        اگر (!نیچے_کو && کھڑکی_ڈیٹا_2->mouse_focus_loss_pending) {
            کھڑکی_ڈیٹا_2->mouse_focus_loss_pending = (کھڑکی_ڈیٹا_2->کھڑکی->flags & SDL_کھڑکی_MOUSE_CAPTURE) != 0;
            اگر (!کھڑکی_ڈیٹا_2->mouse_focus_loss_pending) {
                SDL_سیٹ_Mouse_Focus(تہی);
            }
        }
    }
}

ساکن خالی Emscripten_UpdateMouseFromEvent(SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2, ثابت Emscripten_اشارہ_گر_Event *event)
{
    SDL_assert(event->اشارہ_گر_type == PTRTYPE_MOUSE);

    // Hidden windows (e.g. a shared GL-context window) may share the DOM canvas with the
    // visible window. Their pointer-event listeners would otherwise fire alongside the
    // visible window's, fighting over `mouse->focus` and producing events tagged with the
    // hidden window's ID -- causing downstream consumers that key by window ID to silently
    // drop them. Hidden windows shouldn't take part in user-input dispatch.
    اگر (کھڑکی_ڈیٹا_2->کھڑکی->flags & SDL_کھڑکی_HIDDEN) {
        واپس;
    }

    // rescale (in case canvas is being scaled)
    دوہرا client_w, client_h;
    emscripten_get_element_css_سائز(کھڑکی_ڈیٹا_2->canvas_id, &client_w, &client_h);
    ثابت دوہرا xscale = کھڑکی_ڈیٹا_2->کھڑکی->w / client_w;
    ثابت دوہرا yscale = کھڑکی_ڈیٹا_2->کھڑکی->h / client_h;

    ثابت bool is_اشارہ_گر_Locked = کھڑکی_ڈیٹا_2->has_اشارہ_گر_تالا;
    اعشاری mx, my;
    اگر (is_اشارہ_گر_Locked) {
        mx = (اعشاری)(event->movementX * xscale);
        my = (اعشاری)(event->movementY * yscale);
    } ورنہ {
        mx = (اعشاری)(event->ہدف_X * xscale);
        my = (اعشاری)(event->ہدف_Y * yscale);
    }

    SDL_SendMouseMotion(0, کھڑکی_ڈیٹا_2->کھڑکی, SDL_DEFAULT_MOUSE_ID, is_اشارہ_گر_Locked, mx, my);

    Emscripten_HandleMouseButton(کھڑکی_ڈیٹا_2, event);
}

ساکن خالی Emscripten_UpdateTouchFromEvent(SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2, ثابت Emscripten_اشارہ_گر_Event *event)
{
    SDL_assert(event->اشارہ_گر_type == PTRTYPE_TOUCH);

    ثابت SDL_TouchID deviceId = 1;
    اگر (SDL_جوڑو_Touch(deviceId, SDL_TOUCH_DEVICE_براہ_راست, "") < 0) {
        واپس;
    }

    دوہرا client_w, client_h;
    emscripten_get_element_css_سائز(کھڑکی_ڈیٹا_2->canvas_id, &client_w, &client_h);

    ثابت SDL_FingerID id = event->pointerid + 1;
    اعشاری x, y;
    اگر (client_w <= 1) {
        x = 0.5f;
    } ورنہ {
        x = event->ہدف_X / (client_w - 1);
    }
    اگر (client_h <= 1) {
        y = 0.5f;
    } ورنہ {
        y = event->ہدف_Y / (client_h - 1);
    }

    ثابت bool نیچے_کو = (event->buttons & 1) != 0;
    اگر (event->button == 0) {  // touch is starting or ending if this is zero (-1 means "no change").
        اگر (نیچے_کو) {
            SDL_SendTouch(0, deviceId, id, کھڑکی_ڈیٹا_2->کھڑکی, SDL_EVENT_FINGER_نیچے_کو, x, y, 1.0f);
        }
    }

    SDL_SendTouchMotion(0, deviceId, id, کھڑکی_ڈیٹا_2->کھڑکی, x, y, 1.0f);

    اگر (event->button == 0) {  // touch is starting or ending if this is zero (-1 means "no change").
        اگر (!نیچے_کو) {
            SDL_SendTouch(0, deviceId, id, کھڑکی_ڈیٹا_2->کھڑکی, SDL_EVENT_FINGER_اوپر, x, y, 1.0f);
        }
    }
}

ساکن خالی Emscripten_UpdatePenFromEvent(SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2, ثابت Emscripten_اشارہ_گر_Event *event)
{
    SDL_assert(event->اشارہ_گر_type == PTRTYPE_PEN);
    ثابت SDL_PenID pen = SDL_ڈھونڈو_Pen_By_Handle((خالی *) (size_t) 1);   // something > 0 for the single pen handle.
    اگر (pen) {
        // rescale (in case canvas is being scaled)
        دوہرا client_w, client_h;
        emscripten_get_element_css_سائز(کھڑکی_ڈیٹا_2->canvas_id, &client_w, &client_h);
        ثابت دوہرا xscale = کھڑکی_ڈیٹا_2->کھڑکی->w / client_w;
        ثابت دوہرا yscale = کھڑکی_ڈیٹا_2->کھڑکی->h / client_h;

        ثابت bool is_اشارہ_گر_Locked = کھڑکی_ڈیٹا_2->has_اشارہ_گر_تالا;
        اعشاری mx, my;
        اگر (is_اشارہ_گر_Locked) {
            mx = (اعشاری)(event->movementX * xscale);
            my = (اعشاری)(event->movementY * yscale);
        } ورنہ {
            mx = (اعشاری)(event->ہدف_X * xscale);
            my = (اعشاری)(event->ہدف_Y * yscale);
        }

        SDL_SendPenMotion(0, pen, کھڑکی_ڈیٹا_2->کھڑکی, mx, my);

        اگر (event->button == 0) {  // pen touch
            bool نیچے_کو = ((event->buttons & 1) != 0);
            SDL_SendPenTouch(0, pen, کھڑکی_ڈیٹا_2->کھڑکی, false, نیچے_کو);
        } ورنہ اگر (event->button == 5) {  // eraser touch...? Not sure if this is right...
            bool نیچے_کو = ((event->buttons & 32) != 0);
            SDL_SendPenTouch(0, pen, کھڑکی_ڈیٹا_2->کھڑکی, true, نیچے_کو);
        } ورنہ اگر (event->button == 1) {
            bool نیچے_کو = ((event->buttons & 4) != 0);
            SDL_SendPenButton(0, pen, کھڑکی_ڈیٹا_2->کھڑکی, 2, نیچے_کو);
        } ورنہ اگر (event->button == 2) {
            bool نیچے_کو = ((event->buttons & 2) != 0);
            SDL_SendPenButton(0, pen, کھڑکی_ڈیٹا_2->کھڑکی, 1, نیچے_کو);
        }

        SDL_SendPenAxis(0, pen, کھڑکی_ڈیٹا_2->کھڑکی, SDL_PEN_AXIS_PRESSURE, event->pressure);
        SDL_SendPenAxis(0, pen, کھڑکی_ڈیٹا_2->کھڑکی, SDL_PEN_AXIS_TANGENTIAL_PRESSURE, event->tangential_pressure);
        SDL_SendPenAxis(0, pen, کھڑکی_ڈیٹا_2->کھڑکی, SDL_PEN_AXIS_XTILT, event->tiltx);
        SDL_SendPenAxis(0, pen, کھڑکی_ڈیٹا_2->کھڑکی, SDL_PEN_AXIS_YTILT, event->tilty);
        SDL_SendPenAxis(0, pen, کھڑکی_ڈیٹا_2->کھڑکی, SDL_PEN_AXIS_ROTATION, event->rotation);
    }
}

ساکن خالی Emscripten_Update_اشارہ_گر_From_Event(SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2, ثابت Emscripten_اشارہ_گر_Event *event)
{
    SDL_assert(event != تہی);
    اگر (event->اشارہ_گر_type == PTRTYPE_MOUSE) {
        Emscripten_UpdateMouseFromEvent(کھڑکی_ڈیٹا_2, event);
    } ورنہ اگر (event->اشارہ_گر_type == PTRTYPE_TOUCH) {
        Emscripten_UpdateTouchFromEvent(کھڑکی_ڈیٹا_2, event);
    } ورنہ اگر (event->اشارہ_گر_type == PTRTYPE_PEN) {
        Emscripten_UpdatePenFromEvent(کھڑکی_ڈیٹا_2, event);
    } ورنہ {
        SDL_assert(!"Unexpected pointer event type");
    }
}

ساکن خالی Emscripten_HandleMouseFocus(SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2, ثابت Emscripten_اشارہ_گر_Event *event, bool isenter)
{
    SDL_assert(event->اشارہ_گر_type == PTRTYPE_MOUSE);

    // Hidden windows shouldn't ever become the mouse-focus target.
    اگر (کھڑکی_ڈیٹا_2->کھڑکی->flags & SDL_کھڑکی_HIDDEN) {
        واپس;
    }

    ثابت bool is_اشارہ_گر_Locked = کھڑکی_ڈیٹا_2->has_اشارہ_گر_تالا;

    اگر (!is_اشارہ_گر_Locked) {
        // rescale (in case canvas is being scaled)
        اعشاری mx, my;
        دوہرا client_w, client_h;
        emscripten_get_element_css_سائز(کھڑکی_ڈیٹا_2->canvas_id, &client_w, &client_h);

        mx = (اعشاری)(event->ہدف_X * (کھڑکی_ڈیٹا_2->کھڑکی->w / client_w));
        my = (اعشاری)(event->ہدف_Y * (کھڑکی_ڈیٹا_2->کھڑکی->h / client_h));
        SDL_SendMouseMotion(0, کھڑکی_ڈیٹا_2->کھڑکی, SDL_GLOBAL_MOUSE_ID, is_اشارہ_گر_Locked, mx, my);
    }

    اگر (isenter && کھڑکی_ڈیٹا_2->mouse_focus_loss_pending) {
        کھڑکی_ڈیٹا_2->mouse_focus_loss_pending = false;  // just drop the state, but don't send the enter event.
    } ورنہ اگر (!isenter && (کھڑکی_ڈیٹا_2->کھڑکی->flags & SDL_کھڑکی_MOUSE_CAPTURE)) {
        کھڑکی_ڈیٹا_2->mouse_focus_loss_pending = true;  // waiting on a mouse button to let go before we send the mouse focus update.
    } ورنہ {
        SDL_سیٹ_Mouse_Focus(isenter ? کھڑکی_ڈیٹا_2->کھڑکی : تہی);
    }
}

ساکن خالی Emscripten_HandlePenEnter(SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2, ثابت Emscripten_اشارہ_گر_Event *event)
{
    SDL_assert(event->اشارہ_گر_type == PTRTYPE_PEN);

    // event->pointerid is one continuous interaction; it doesn't necessarily track a specific tool over time, like the same finger's ID changed on each new touch event.
    // as such, we only expose a single pen, and when the touch ends, we say it lost proximity instead of the calling SDL_RemovePenDevice().

    SDL_PenID pen = SDL_ڈھونڈو_Pen_By_Handle((خالی *) (size_t) 1);  // something > 0 for the single pen handle.
    اگر (pen) {
        SDL_SendPenProximity(0, pen, کھڑکی_ڈیٹا_2->کھڑکی, true, true);
    } ورنہ {
        // Web browsers offer almost none of this information as specifics, but can without warning offer any of these specific things.
        SDL_PenInfo peninfo;
        SDL_zero(peninfo);
        peninfo.capabilities = SDL_PEN_CAPABILITY_PRESSURE | SDL_PEN_CAPABILITY_ROTATION | SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT | SDL_PEN_CAPABILITY_TANGENTIAL_PRESSURE | SDL_PEN_CAPABILITY_ERASER;
        peninfo.max_tilt = 90.0f;
        peninfo.عدد_buttons = 2;
        peninfo.subtype = SDL_PEN_TYPE_PEN;
        SDL_جوڑو_Pen_Device(0, تہی, کھڑکی_ڈیٹا_2->کھڑکی, &peninfo, (خالی *) (size_t) 1, true);
    }

    Emscripten_UpdatePenFromEvent(کھڑکی_ڈیٹا_2, event);
}

EMSCRIPTEN_KEEPALIVE خالی Emscripten_Handle_اشارہ_گر_Enter(SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2, ثابت Emscripten_اشارہ_گر_Event *event)
{
    SDL_assert(event != تہی);
    اگر (event->اشارہ_گر_type == PTRTYPE_MOUSE) {
        Emscripten_HandleMouseFocus(کھڑکی_ڈیٹا_2, event, true);
    } ورنہ اگر (event->اشارہ_گر_type == PTRTYPE_PEN) {
        Emscripten_HandlePenEnter(کھڑکی_ڈیٹا_2, event);
    } ورنہ اگر (event->اشارہ_گر_type == PTRTYPE_TOUCH) {
        // do nothing.
    } ورنہ {
        SDL_assert(!"Unexpected pointer event type");
    }
}

ساکن خالی Emscripten_HandlePenLeave(SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2, ثابت Emscripten_اشارہ_گر_Event *event)
{
    ثابت SDL_PenID pen = SDL_ڈھونڈو_Pen_By_Handle((خالی *) (size_t) 1);   // something > 0 for the single pen handle.
    اگر (pen) {
        Emscripten_Update_اشارہ_گر_From_Event(کھڑکی_ڈیٹا_2, event);  // last data updates?
        SDL_SendPenProximity(0, pen, کھڑکی_ڈیٹا_2->کھڑکی, false, false);
    }
}

ساکن خالی Emscripten_HandleTouchCancel(SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2, ثابت Emscripten_اشارہ_گر_Event *event)
{
    SDL_assert(event->اشارہ_گر_type == PTRTYPE_TOUCH);

    ثابت SDL_TouchID deviceId = 1;
    اگر (SDL_جوڑو_Touch(deviceId, SDL_TOUCH_DEVICE_براہ_راست, "") < 0) {
        واپس;
    }

    دوہرا client_w, client_h;
    emscripten_get_element_css_سائز(کھڑکی_ڈیٹا_2->canvas_id, &client_w, &client_h);

    ثابت SDL_FingerID id = event->pointerid + 1;
    اعشاری x, y;
    اگر (client_w <= 1) {
        x = 0.5f;
    } ورنہ {
        x = event->ہدف_X / (client_w - 1);
    }
    اگر (client_h <= 1) {
        y = 0.5f;
    } ورنہ {
        y = event->ہدف_Y / (client_h - 1);
    }

    SDL_SendTouch(0, deviceId, id, کھڑکی_ڈیٹا_2->کھڑکی, SDL_EVENT_FINGER_CANCELED, x, y, 1.0f);
}

EMSCRIPTEN_KEEPALIVE خالی Emscripten_Handle_اشارہ_گر_Leave(SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2, ثابت Emscripten_اشارہ_گر_Event *event)
{
    SDL_assert(event != تہی);
    اگر (event->اشارہ_گر_type == PTRTYPE_MOUSE) {
        Emscripten_HandleMouseFocus(کھڑکی_ڈیٹا_2, event, false);
    } ورنہ اگر (event->اشارہ_گر_type == PTRTYPE_PEN) {
        Emscripten_HandlePenLeave(کھڑکی_ڈیٹا_2, event);
    } ورنہ اگر (event->اشارہ_گر_type == PTRTYPE_TOUCH) {
        Emscripten_HandleTouchCancel(کھڑکی_ڈیٹا_2, event);
    } ورنہ {
        SDL_assert(!"Unexpected pointer event type");
    }
}

EMSCRIPTEN_KEEPALIVE خالی Emscripten_Handle_اشارہ_گر_Generic(SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2, ثابت Emscripten_اشارہ_گر_Event *event)
{
    SDL_assert(event != تہی);
    Emscripten_Update_اشارہ_گر_From_Event(کھڑکی_ڈیٹا_2, event);
}

ساکن خالی Emscripten_prep_اشارہ_گر_event_callbacks(خالی)
{
    MAIN_THREAD_EM_ASM({
        var SDL3 = Module['SDL3'];

        اگر (SDL3.make_اشارہ_گر_Event_CStruct === undefined) {
            SDL3.make_اشارہ_گر_Event_CStruct = function(بایاں, چوٹی, event) {
                var ptrtype = 0;
                اگر (event.اشارہ_گر_Type == "mouse") {
                    ptrtype = 1;
                } ورنہ اگر (event.اشارہ_گر_Type == "touch") {
                    ptrtype = 2;
                } ورنہ اگر (event.اشارہ_گر_Type == "pen") {
                    ptrtype = 3;
                } ورنہ {
                    واپس 0;
                }

                var ptr = _SDL_malloc($0);
                اگر (ptr != 0) {
                    var idx = SDL3.CPtr_مقصد_Heap32_اشاریہ(ptr);
                    HEAP32[idx++] = ptrtype;
                    HEAP32[idx++] = event.اشارہ_گر_Id;
                    HEAP32[idx++] = (typeof(event.button) !== "undefined") ? event.button : -1;
                    HEAP32[idx++] = event.buttons;
                    HEAP32[idx++] = (event.type == "pointerdown") ? 1 : 0;
                    HEAPF32[idx++] = event.movementX;
                    HEAPF32[idx++] = event.movementY;
                    HEAPF32[idx++] = event.clientX - بایاں;
                    HEAPF32[idx++] = event.clientY - چوٹی;
                    اگر (ptrtype == 3) {
                        HEAPF32[idx++] = event.pressure;
                        HEAPF32[idx++] = event.tangentialPressure;
                        HEAPF32[idx++] = event.tiltX;
                        HEAPF32[idx++] = event.tiltY;
                        HEAPF32[idx++] = event.twist;
                    }
                }
                واپس ptr;
            };
        }
    }, حجم (Emscripten_اشارہ_گر_Event));
}

ساکن خالی Emscripten_سیٹ_اشارہ_گر_event_callbacks(SDL_کھڑکی_ڈیٹا *ڈیٹا)
{
    Emscripten_prep_اشارہ_گر_event_callbacks();

    MAIN_THREAD_EM_ASM({
        var ہدف = document.querySelector(UTF8_مقصد_String($1));
        اگر (ہدف) {
            var SDL3 = Module['SDL3'];
            var ڈیٹا = $0;
            ہدف.sdl_Event_Handler_اشارہ_گر_Enter = function(event) {
                var rect = ہدف.getBoundingClientRect();
                var d = SDL3.make_اشارہ_گر_Event_CStruct(rect.بایاں, rect.چوٹی, event);
                اگر (d != 0)
                {
                    Emscripten_Handle_اشارہ_گر_Enter_2(SDL3.JSVar_مقصد_CPtr(ڈیٹا), d);
                    _SDL_free(d);
                }
            };
            ہدف.sdl_Event_Handler_اشارہ_گر_Leave = function(event) {
                var rect = ہدف.getBoundingClientRect();
                var d = SDL3.make_اشارہ_گر_Event_CStruct(rect.بایاں, rect.چوٹی, event);
                اگر (d != 0)
                {
                    Emscripten_Handle_اشارہ_گر_Leave_2(SDL3.JSVar_مقصد_CPtr(ڈیٹا), d);
                    _SDL_free(d);
                }
            };
            ہدف.sdl_Event_Handler_اشارہ_گر_Generic = function(event) {
                var rect = ہدف.getBoundingClientRect();
                var d = SDL3.make_اشارہ_گر_Event_CStruct(rect.بایاں, rect.چوٹی, event);
                اگر (d != 0)
                {
                    Emscripten_Handle_اشارہ_گر_Generic_2(SDL3.JSVar_مقصد_CPtr(ڈیٹا), d);
                    _SDL_free(d);
                }
            };

            ہدف.style.touchAction = "none";  // or mobile devices will scroll as your touch moves across the element.
            ہدف.جوڑو_Event_Listener("pointerenter", ہدف.sdl_Event_Handler_اشارہ_گر_Enter);
            ہدف.جوڑو_Event_Listener("pointerleave", ہدف.sdl_Event_Handler_اشارہ_گر_Leave);
            ہدف.جوڑو_Event_Listener("pointercancel", ہدف.sdl_Event_Handler_اشارہ_گر_Leave);
            ہدف.جوڑو_Event_Listener("pointerdown", ہدف.sdl_Event_Handler_اشارہ_گر_Generic);
            ہدف.جوڑو_Event_Listener("pointermove", ہدف.sdl_Event_Handler_اشارہ_گر_Generic);
            ہدف.جوڑو_Event_Listener("pointerup", ہدف.sdl_Event_Handler_اشارہ_گر_Generic);
        }
    }, ڈیٹا, ڈیٹا->canvas_id);
}

ساکن خالی Emscripten_unset_اشارہ_گر_event_callbacks(SDL_کھڑکی_ڈیٹا *ڈیٹا)
{
    MAIN_THREAD_EM_ASM({
        var ہدف = document.querySelector(UTF8_مقصد_String($0));
        اگر (ہدف) {
            ہدف.removeEventListener("pointerenter", ہدف.sdl_Event_Handler_اشارہ_گر_Enter);
            ہدف.removeEventListener("pointerleave", ہدف.sdl_Event_Handler_اشارہ_گر_Leave);
            ہدف.removeEventListener("pointercancel", ہدف.sdl_Event_Handler_اشارہ_گر_Leave);
            ہدف.removeEventListener("pointerdown", ہدف.sdl_Event_Handler_اشارہ_گر_Generic);
            ہدف.removeEventListener("pointermove", ہدف.sdl_Event_Handler_اشارہ_گر_Generic);
            ہدف.removeEventListener("pointerup", ہدف.sdl_Event_Handler_اشارہ_گر_Generic);
            ہدف.style.touchAction = "";  // let mobile devices scroll again as your touch moves across the element.
            ہدف.sdl_Event_Handler_اشارہ_گر_Enter = undefined;
            ہدف.sdl_Event_Handler_اشارہ_گر_Leave = undefined;
            ہدف.sdl_Event_Handler_اشارہ_گر_Generic = undefined;
        }
    }, ڈیٹا->canvas_id);
}

EMSCRIPTEN_KEEPALIVE خالی Emscripten_Handle_Mouse_Button_اوپر_Global(SDL_VideoDevice *device, ثابت Emscripten_اشارہ_گر_Event *event)
{
    SDL_assert(device != تہی);
    SDL_assert(event != تہی);
    اگر (event->اشارہ_گر_type == PTRTYPE_MOUSE) {
        برائے (SDL_کھڑکی *کھڑکی = device->windows; کھڑکی; کھڑکی = کھڑکی->اگلا) {
            Emscripten_HandleMouseButton(کھڑکی->اندرونی_2, event);
        }
    }
}

ساکن خالی Emscripten_سیٹ_global_mouseup_callback(SDL_VideoDevice *device)
{
    Emscripten_prep_اشارہ_گر_event_callbacks();

    MAIN_THREAD_EM_ASM({
        var ہدف = document;
        اگر (ہدف) {
            ہدف.sdl_Event_Handler_Mouse_Button_اوپر_Global = function(event) {
                var SDL3 = Module['SDL3'];
                var d = SDL3.make_اشارہ_گر_Event_CStruct(0, 0, event);
                اگر (d != 0)
                {
                    Emscripten_Handle_Mouse_Button_اوپر_Global_2(SDL3.JSVar_مقصد_CPtr($0), d);
                    _SDL_free(d);
                }
            };
            ہدف.جوڑو_Event_Listener("pointerup", ہدف.sdl_Event_Handler_Mouse_Button_اوپر_Global);
        }
    }, device);
}

ساکن خالی Emscripten_unset_global_mouseup_callback(SDL_VideoDevice *device)
{
    MAIN_THREAD_EM_ASM({
        var ہدف = document;
        اگر (ہدف) {
            ہدف.removeEventListener("pointerup", ہدف.sdl_Event_Handler_Mouse_Button_اوپر_Global);
            ہدف.sdl_Event_Handler_Mouse_Button_اوپر_Global = undefined;
        }
    });
}

// IF YOU CHANGE THIS STRUCTURE, YOU NEED TO UPDATE THE JAVASCRIPT THAT FILLS IT IN: makeDropEventCStruct, below.
قسمتعریف ساخت Emscripten_DropEvent
{
    صحیح x;
    صحیح y;
} Emscripten_DropEvent;

EMSCRIPTEN_KEEPALIVE خالی Emscripten_SendDragEvent(SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2, ثابت Emscripten_DropEvent *event)
{
    SDL_SendDropPosition(کھڑکی_ڈیٹا_2->کھڑکی, event->x, event->y);
}

EMSCRIPTEN_KEEPALIVE خالی Emscripten_SendDragCompleteEvent(SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2)
{
    SDL_SendDropComplete(کھڑکی_ڈیٹا_2->کھڑکی);
}

EMSCRIPTEN_KEEPALIVE خالی Emscripten_Send_Drag_متن_Event(SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2, حرف *متن)
{
    SDL_Send_Drop_متن(کھڑکی_ڈیٹا_2->کھڑکی, متن);
}

EMSCRIPTEN_KEEPALIVE خالی Emscripten_SendDragFileEvent(SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2, حرف *filename)
{
    SDL_SendDropFile(کھڑکی_ڈیٹا_2->کھڑکی, تہی, filename);
}

EM_JS_DEPS(dragndrop, "$writeArrayToMemory");

ساکن خالی Emscripten_سیٹ_drag_event_callbacks(SDL_کھڑکی_ڈیٹا *ڈیٹا)
{
    MAIN_THREAD_EM_ASM({
        var ہدف = document.querySelector(UTF8_مقصد_String($1));
        اگر (ہدف) {
            var ڈیٹا = $0;
            var SDL3 = Module['SDL3'];

            var makeDropEventCStruct = function(event) {
                var ptr = 0;
                ptr = _SDL_malloc($2);
                اگر (ptr != 0) {
                    var idx = ptr >> 2;
                    var rect = ہدف.getBoundingClientRect();
                    HEAP32[idx++] = event.clientX - rect.بایاں;
                    HEAP32[idx++] = event.clientY - rect.چوٹی;
                }
                واپس ptr;
            };

            SDL3.eventHandlerDropDragover = function(event) {
                event.preventDefault();
                var d = makeDropEventCStruct(event); اگر (d != 0) { _Emscripten_SendDragEvent(ڈیٹا, d); _SDL_free(d); }
            };
            ہدف.جوڑو_Event_Listener("dragover", SDL3.eventHandlerDropDragover);

            SDL3.drop_گنتی = 0;

            // FS.* functions throw exceptions when there are errors (such as the temp dir already existing),
            //  but we ignore all of these in a catch handler; you just won't get the drop event if there's a problem.
            try { FS.mkdir("/tmp/filedrop"); } catch (e) {}

            SDL3.eventHandlerDropDrop = function(event) {
                event.preventDefault();
                اگر (event.ڈیٹا_Transfer.types.includes("text/plain")) {
                    let plain_متن = string_مقصد_New_UTF8(event.ڈیٹا_Transfer.get_ڈیٹا("text/plain"));
                    Emscripten_Send_Drag_متن_Event_2(ڈیٹا, plain_متن);
                    _Emscripten_force_free(plain_متن);
                } ورنہ اگر (event.ڈیٹا_Transfer.types.includes("Files")) {
                    let files_read = 0;
                    ثابت files_مقصد_read = event.ڈیٹا_Transfer.files.لمبائی;
                    برائے (let i = 0; i < files_مقصد_read; i++) {
                        ثابت file = event.ڈیٹا_Transfer.files.شے(i);
                        ثابت file_reader = new FileReader();
                        file_reader.read_As_Array_بفر(file);
                        file_reader.onload = function(event) {
                            ثابت fs_dropdir = `/tmp/filedrop/${SDL3.drop_گنتی}`;
                            SDL3.drop_گنتی += 1;

                            ثابت fs_filepath = `${fs_dropdir}/${file.name}`;
                            ثابت c_fs_filepath = string_مقصد_New_UTF8(fs_filepath);
                            ثابت contents_array8 = new Uint8Array(event.ہدف.نتیجہ);

                            try {
                                FS.mkdir(fs_dropdir);
                                var دھارا = FS.open(fs_filepath, "w");
                                FS.اكتب(دھارا, contents_array8, 0, contents_array8.لمبائی, 0);
                                FS.close(دھارا);
                                _Emscripten_SendDragFileEvent(ڈیٹا, c_fs_filepath);
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
                        اگر (files_read === files_مقصد_read) {
                            _Emscripten_SendDragCompleteEvent(ڈیٹا);
                        }
                    }
                }
                _Emscripten_SendDragCompleteEvent(ڈیٹا);
            };
            ہدف.جوڑو_Event_Listener("drop", SDL3.eventHandlerDropDrop);

            SDL3.eventHandlerDropDragend = function(event) {
                event.preventDefault();
                _Emscripten_SendDragCompleteEvent(ڈیٹا);
            };
            ہدف.جوڑو_Event_Listener("dragend", SDL3.eventHandlerDropDragend);
            ہدف.جوڑو_Event_Listener("dragleave", SDL3.eventHandlerDropDragend);
        }
    }, ڈیٹا, ڈیٹا->canvas_id, حجم (Emscripten_DropEvent));
}

ساکن خالی Emscripten_unset_drag_event_callbacks(SDL_کھڑکی_ڈیٹا *ڈیٹا)
{
    MAIN_THREAD_EM_ASM({
        var ہدف = document.querySelector(UTF8_مقصد_String($0));
        اگر (ہدف) {
            var SDL3 = Module['SDL3'];
            ہدف.removeEventListener("dragleave", SDL3.eventHandlerDropDragend);
            ہدف.removeEventListener("dragend", SDL3.eventHandlerDropDragend);
            ہدف.removeEventListener("drop", SDL3.eventHandlerDropDrop);
            SDL3.drop_گنتی = undefined;

            function recursive_remove(dirpath) {
                FS.readdir(dirpath).forEach((filename) => {
                    ثابت p = `${dirpath}/${filename}`;
                    ثابت p_s = FS.stat(p);
                    اگر (FS.isFile(p_s.منوال)) {
                        FS.unlink(p);
                    } ورنہ اگر (FS.isDir(p)) {
                        recursive_remove(p);
                    }
                });
                FS.rmdir(dirpath);
            }("/tmp/filedrop");

            FS.rmdir("/tmp/filedrop");
            ہدف.removeEventListener("dragover", SDL3.eventHandlerDropDragover);
            SDL3.eventHandlerDropDragover = undefined;
            SDL3.eventHandlerDropDrop = undefined;
            SDL3.eventHandlerDropDragend = undefined;
        }
    }, ڈیٹا->canvas_id);
}

ساکن ثابت حرف *Emscripten_Get_Keyboard_ہدف_Element(ثابت حرف *ہدف)
{
    اگر (SDL_strcmp(ہدف, "#none") == 0) {
        واپس تہی;
    } ورنہ اگر (SDL_strcmp(ہدف, "#window") == 0) {
        واپس EMSCRIPTEN_EVENT_ہدف_کھڑکی;
    } ورنہ اگر (SDL_strcmp(ہدف, "#document") == 0) {
        واپس EMSCRIPTEN_EVENT_ہدف_DOCUMENT;
    } ورنہ اگر (SDL_strcmp(ہدف, "#screen") == 0) {
        واپس EMSCRIPTEN_EVENT_ہدف_SCREEN;
    }

    واپس ہدف;
}

خالی Emscripten_رجسٹر_Global_Event_Handlers(SDL_VideoDevice *device)
{
    Emscripten_سیٹ_global_mouseup_callback(device);

    emscripten_سیٹ_focus_callback(EMSCRIPTEN_EVENT_ہدف_کھڑکی, device, 0, Emscripten_HandleFocus);
    emscripten_سیٹ_blur_callback(EMSCRIPTEN_EVENT_ہدف_کھڑکی, device, 0, Emscripten_HandleFocus);

    emscripten_سیٹ_pointerlockchange_callback(EMSCRIPTEN_EVENT_ہدف_DOCUMENT, device, 0, Emscripten_Handle_اشارہ_گر_تالا_Change_Global);

    emscripten_سیٹ_fullscreenchange_callback(EMSCRIPTEN_EVENT_ہدف_DOCUMENT, device, 0, Emscripten_HandleFullscreenChangeGlobal);

    emscripten_سیٹ_resize_callback(EMSCRIPTEN_EVENT_ہدف_کھڑکی, device, 0, Emscripten_HandleResizeGlobal);
}

خالی Emscripten_UnregisterGlobalEventHandlers(SDL_VideoDevice *device)
{
    Emscripten_unset_global_mouseup_callback(device);

    emscripten_سیٹ_focus_callback(EMSCRIPTEN_EVENT_ہدف_کھڑکی, تہی, 0, تہی);
    emscripten_سیٹ_blur_callback(EMSCRIPTEN_EVENT_ہدف_کھڑکی, تہی, 0, تہی);

    emscripten_سیٹ_pointerlockchange_callback(EMSCRIPTEN_EVENT_ہدف_DOCUMENT, تہی, 0, تہی);

    emscripten_سیٹ_fullscreenchange_callback(EMSCRIPTEN_EVENT_ہدف_DOCUMENT, تہی, 0, تہی);

    emscripten_سیٹ_resize_callback(EMSCRIPTEN_EVENT_ہدف_کھڑکی, تہی, 0, تہی);
}

EMSCRIPTEN_KEEPALIVE خالی Emscripten_Handle_تالا_کلیدیں_Check(SDL_کھڑکی_ڈیٹا *کھڑکی_ڈیٹا_2, EM_BOOL capslock, EM_BOOL numlock, EM_BOOL scrolllock)
{
    ثابت SDL_Keymod new_mods = (capslock ? SDL_KMOD_CAPS : 0) | (numlock ? SDL_KMOD_عدد : 0) | (scrolllock ? SDL_KMOD_SCROLL : 0);
    SDL_Keymod modstate = SDL_GetModState();
    اگر ((modstate & (SDL_KMOD_CAPS|SDL_KMOD_عدد|SDL_KMOD_SCROLL)) != new_mods) {
        modstate &= ~(SDL_KMOD_CAPS|SDL_KMOD_عدد|SDL_KMOD_SCROLL);
        modstate |= new_mods;
        SDL_سیٹ_Mod_State(modstate);
    }
}

خالی Emscripten_رجسٹر_Event_Handlers(SDL_کھڑکی_ڈیٹا *ڈیٹا)
{
    ثابت حرف *کلید_Element;

    // There is only one window and that window is the canvas
    emscripten_سیٹ_wheel_callback(ڈیٹا->canvas_id, ڈیٹا, 0, Emscripten_HandleWheel);

    emscripten_سیٹ_orientationchange_callback(ڈیٹا, 0, Emscripten_HandleOrientationChange);

    کلید_Element = Emscripten_Get_Keyboard_ہدف_Element(ڈیٹا->keyboard_element);
    اگر (کلید_Element) {
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
        emscripten_سیٹ_keydown_callback(کلید_Element, تہی, 0, تہی);
        emscripten_سیٹ_keyup_callback(کلید_Element, تہی, 0, تہی);
        emscripten_سیٹ_keypress_callback(کلید_Element, تہی, 0, تہی);

        MAIN_THREAD_EM_ASM_INT({
            var ڈیٹا = $0;
            // our keymod state can get confused in various ways (changed capslock when browser didn't have focus, etc), and you can't query the current
            //  state from the DOM, outside of a keyboard event, so catch keypresses globally and reset mod state if it's unexpectedly wrong. Best we can do.
            //  Note that this thing _only_ adjusts the lock keys if necessary; the real SDL keypress handling happens elsewhere.

            // Remove any prior listener first -- `addEventListener` does not deduplicate either.
            اگر (document.sdl_Event_Handler_تالا_کلیدیں_Check) {
                document.removeEventListener("keydown", document.sdl_Event_Handler_تالا_کلیدیں_Check);
            }

            document.sdl_Event_Handler_تالا_کلیدیں_Check = function(event) {
                // don't try to adjust the state on the actual lock key presses; the normal key handler will catch that and adjust.
                اگر ((event.کلید != "CapsLock") && (event.کلید != "NumLock") && (event.کلید != "ScrollLock"))
                {
                    Emscripten_Handle_تالا_کلیدیں_Check_2(Module['SDL3'].JSVar_مقصد_CPtr(ڈیٹا), event.getModifierState("CapsLock"), event.getModifierState("NumLock"), event.getModifierState("ScrollLock"));
                }
            };
            document.جوڑو_Event_Listener("keydown", document.sdl_Event_Handler_تالا_کلیدیں_Check);
        }, ڈیٹا);
        emscripten_سیٹ_keydown_callback(کلید_Element, ڈیٹا, 0, Emscripten_Handle_کلید);
        emscripten_سیٹ_keyup_callback(کلید_Element, ڈیٹا, 0, Emscripten_Handle_کلید);
        emscripten_سیٹ_keypress_callback(کلید_Element, ڈیٹا, 0, Emscripten_Handle_کلید_Press);
    }

    emscripten_سیٹ_visibilitychange_callback(ڈیٹا, 0, Emscripten_HandleVisibilityChange);

    emscripten_سیٹ_beforeunload_callback(ڈیٹا, Emscripten_HandleBeforeUnload);

    // !!! FIXME: currently Emscripten doesn't have a Pointer Events functions like emscripten_set_*_callback, but we should use those when they do:
    // !!! FIXME:  https://github.com/emscripten-core/emscripten/issues/7278#issuecomment-2280024621
    Emscripten_سیٹ_اشارہ_گر_event_callbacks(ڈیٹا);

    // !!! FIXME: currently Emscripten doesn't have a Drop Events functions like emscripten_set_*_callback, but we should use those when they do:
    Emscripten_سیٹ_drag_event_callbacks(ڈیٹا);
}

خالی Emscripten_UnregisterEventHandlers(SDL_کھڑکی_ڈیٹا *ڈیٹا)
{
    ثابت حرف *کلید_Element;

    // !!! FIXME: currently Emscripten doesn't have a Drop Events functions like emscripten_set_*_callback, but we should use those when they do:
    Emscripten_unset_drag_event_callbacks(ڈیٹا);

    // !!! FIXME: currently Emscripten doesn't have a Pointer Events functions like emscripten_set_*_callback, but we should use those when they do:
    // !!! FIXME:  https://github.com/emscripten-core/emscripten/issues/7278#issuecomment-2280024621
    Emscripten_unset_اشارہ_گر_event_callbacks(ڈیٹا);

    // only works due to having one window
    emscripten_سیٹ_wheel_callback(ڈیٹا->canvas_id, تہی, 0, تہی);

    emscripten_سیٹ_orientationchange_callback(تہی, 0, تہی);

    کلید_Element = Emscripten_Get_Keyboard_ہدف_Element(ڈیٹا->keyboard_element);
    اگر (کلید_Element) {
        emscripten_سیٹ_keydown_callback(کلید_Element, تہی, 0, تہی);
        emscripten_سیٹ_keyup_callback(کلید_Element, تہی, 0, تہی);
        emscripten_سیٹ_keypress_callback(کلید_Element, تہی, 0, تہی);
        MAIN_THREAD_EM_ASM_INT({
            document.removeEventListener("keydown", document.sdl_Event_Handler_تالا_کلیدیں_Check);
        });
    }

    emscripten_سیٹ_visibilitychange_callback(تہی, 0, تہی);

    emscripten_سیٹ_beforeunload_callback(تہی, تہی);
}

#اگر_ختم // SDL_VIDEO_DRIVER_EMSCRIPTEN

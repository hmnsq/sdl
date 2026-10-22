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

#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_EMSCRIPTEN

#అన్తర్భావ <emscripten/html5.h>
#అన్తర్భావ <emscripten/dom_pk_codes.h>

#అన్తర్భావ "../../events/SDL_dropevents_c.h"
#అన్తర్భావ "../../events/SDL_events_c.h"
#అన్తర్భావ "../../events/SDL_keyboard_c.h"
#అన్తర్భావ "../../events/SDL_touch_c.h"

#అన్తర్భావ "SDL_emscriptenevents.h"
#అన్తర్భావ "SDL_emscriptenvideo.h"

/*
Emscripten PK code to scancode
https://developer.mozilla.org/en-US/docs/Web/API/KeyboardEvent
https://developer.mozilla.org/en-US/docs/Web/API/KeyboardEvent/code
*/
స్థిర స్థిరరాశి SDL_Scancode emscripten_scancode_పట్టిక[] = {
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

స్థిర SDL_Scancode Emscripten_Map_పరిశీలన_సంకేతం(స్థిరరాశి అక్షరం *సంకేతం_2)
{
    స్థిరరాశి DOM_PK_సంకేతం_TYPE pk_సంకేతం = emscripten_compute_dom_pk_సంకేతం(సంకేతం_2);
    ఒకవేళ (pk_సంకేతం < SDL_arraysize(emscripten_scancode_పట్టిక)) {
        తిరిగి emscripten_scancode_పట్టిక[pk_సంకేతం];
    }

    ఎంపిక (pk_సంకేతం) {
    స్థితి DOM_PK_PASTE:
        తిరిగి SDL_SCANCODE_PASTE;
    స్థితి DOM_PK_MEDIA_TRACK_మునుపటి:
        తిరిగి SDL_SCANCODE_MEDIA_మునుపటి_TRACK;
    స్థితి DOM_PK_CUT:
        తిరిగి SDL_SCANCODE_CUT;
    స్థితి DOM_PK_COPY:
        తిరిగి SDL_SCANCODE_COPY;
    స్థితి DOM_PK_MEDIA_TRACK_తదుపరి:
        తిరిగి SDL_SCANCODE_MEDIA_తదుపరి_TRACK;
    స్థితి DOM_PK_NUMPAD_ENTER:
        తిరిగి SDL_SCANCODE_KP_ENTER;
    స్థితి DOM_PK_CONTROL_కుడి:
        తిరిగి SDL_SCANCODE_RCTRL;
    స్థితి DOM_PK_AUDIO_VOLUME_MUTE:
        తిరిగి SDL_SCANCODE_MUTE;
    స్థితి DOM_PK_MEDIA_PLAY_PAUSE:
        తిరిగి SDL_SCANCODE_MEDIA_PLAY_PAUSE;
    స్థితి DOM_PK_MEDIA_STOP:
        తిరిగి SDL_SCANCODE_MEDIA_STOP;
    స్థితి DOM_PK_EJECT:
        తిరిగి SDL_SCANCODE_MEDIA_EJECT;
    స్థితి DOM_PK_AUDIO_VOLUME_కిందికి:
        తిరిగి SDL_SCANCODE_VOLUMEDOWN;
    స్థితి DOM_PK_AUDIO_VOLUME_పైకి:
        తిరిగి SDL_SCANCODE_VOLUMEUP;
    స్థితి DOM_PK_BROWSER_HOME:
        తిరిగి SDL_SCANCODE_AC_HOME;
    స్థితి DOM_PK_NUMPAD_DIVIDE:
        తిరిగి SDL_SCANCODE_KP_DIVIDE;
    స్థితి DOM_PK_ALT_కుడి:
        తిరిగి SDL_SCANCODE_RALT;
    స్థితి DOM_PK_HELP:
        తిరిగి SDL_SCANCODE_HELP;
    స్థితి DOM_PK_అంకె_తాళం:
        తిరిగి SDL_SCANCODE_NUMLOCKCLEAR;
    స్థితి DOM_PK_HOME:
        తిరిగి SDL_SCANCODE_HOME;
    స్థితి DOM_PK_ARROW_పైకి:
        తిరిగి SDL_SCANCODE_పైకి;
    స్థితి DOM_PK_పుట_పైకి:
        తిరిగి SDL_SCANCODE_PAGEUP;
    స్థితి DOM_PK_ARROW_ఎడమ:
        తిరిగి SDL_SCANCODE_ఎడమ;
    స్థితి DOM_PK_ARROW_కుడి:
        తిరిగి SDL_SCANCODE_కుడి;
    స్థితి DOM_PK_చివర:
        తిరిగి SDL_SCANCODE_చివర;
    స్థితి DOM_PK_ARROW_కిందికి:
        తిరిగి SDL_SCANCODE_కిందికి;
    స్థితి DOM_PK_పుట_కిందికి:
        తిరిగి SDL_SCANCODE_PAGEDOWN;
    స్థితి DOM_PK_చొప్పించు:
        తిరిగి SDL_SCANCODE_చొప్పించు;
    స్థితి DOM_PK_DELETE:
        తిరిగి SDL_SCANCODE_DELETE;
    స్థితి DOM_PK_META_ఎడమ:
        తిరిగి SDL_SCANCODE_LGUI;
    స్థితి DOM_PK_META_కుడి:
        తిరిగి SDL_SCANCODE_RGUI;
    స్థితి DOM_PK_CONTEXT_MENU:
        తిరిగి SDL_SCANCODE_APPLICATION;
    స్థితి DOM_PK_POWER:
        తిరిగి SDL_SCANCODE_POWER;
    స్థితి DOM_PK_BROWSER_శోధన:
        తిరిగి SDL_SCANCODE_AC_శోధన;
    స్థితి DOM_PK_BROWSER_FAVORITES:
        తిరిగి SDL_SCANCODE_AC_BOOKMARKS;
    స్థితి DOM_PK_BROWSER_REFRESH:
        తిరిగి SDL_SCANCODE_AC_REFRESH;
    స్థితి DOM_PK_BROWSER_STOP:
        తిరిగి SDL_SCANCODE_AC_STOP;
    స్థితి DOM_PK_BROWSER_FORWARD:
        తిరిగి SDL_SCANCODE_AC_FORWARD;
    స్థితి DOM_PK_BROWSER_వెనుక:
        తిరిగి SDL_SCANCODE_AC_వెనుక;
    స్థితి DOM_PK_MEDIA_SELECT:
        తిరిగి SDL_SCANCODE_MEDIA_SELECT;
    }

    తిరిగి SDL_SCANCODE_UNKNOWN;
}

స్థిర SDL_కిటికీ *Emscripten_Get_Focused_కిటికీ(SDL_VideoDevice *device)
{
    SDL_కిటికీ *కిటికీ;
    కొరకు (కిటికీ = device->windows; కిటికీ; కిటికీ = కిటికీ->తదుపరి) {
        SDL_కిటికీ_దత్తాంశం *wdata = కిటికీ->అంతర్గత;

        స్థిరరాశి పూర్ణాంకం focused = MAIN_THREAD_EM_ASM_INT({
            var id = UTF8_గమ్యం_String($0);
            try
            {
                var canvas = document.querySelector(id);
                ఒకవేళ (canvas) {
                    తిరిగి canvas === document.చురుకైన_Element;
                }
            }
            catch (e)
            {
                // querySelector throws if not a valid selector
            }
            తిరిగి false;
        }, wdata->canvas_id);

        ఒకవేళ (focused) {
            ఆపు;
        }
    }
    // If the DOM is focused, then at least one canvas in the DOM should be considered focused.
    // So in this case, just assume that the first canvas is focused.
    ఒకవేళ (!కిటికీ) {
        స్థిరరాశి పూర్ణాంకం focused = MAIN_THREAD_EM_ASM_INT({
            తిరిగి document.hasFocus();
        });
        ఒకవేళ (focused) {
            కిటికీ = device->windows;
        }
    }
    తిరిగి కిటికీ;
}

స్థిర EM_BOOL Emscripten_Handle_సూచిక_తాళం_Change(పూర్ణాంకం eventType, స్థిరరాశి EmscriptenPointerlockChangeEvent *changeEvent, శూన్య *user_దత్తాంశం)
{
    SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2 = (SDL_కిటికీ_దత్తాంశం *)user_దత్తాంశం;
    // keep track of lock losses, so we can regrab if/when appropriate.
    కిటికీ_దత్తాంశం_2->has_సూచిక_తాళం = changeEvent->is_చురుకైన;
    తిరిగి 0;
}

స్థిర EM_BOOL Emscripten_Handle_సూచిక_తాళం_Change_Global(పూర్ణాంకం eventType, స్థిరరాశి EmscriptenPointerlockChangeEvent *changeEvent, శూన్య *user_దత్తాంశం)
{
    SDL_VideoDevice *device = user_దత్తాంశం;
    bool prevent_default = false;
    SDL_కిటికీ *కిటికీ;

    కొరకు (కిటికీ = device->windows; కిటికీ; కిటికీ = కిటికీ->తదుపరి) {
        prevent_default |= Emscripten_Handle_సూచిక_తాళం_Change(eventType, changeEvent, కిటికీ->అంతర్గత);
    }

    తిరిగి prevent_default;
}

స్థిర EM_BOOL Emscripten_HandleWheel(పూర్ణాంకం eventType, స్థిరరాశి EmscriptenWheelEvent *wheelEvent, శూన్య *user_దత్తాంశం)
{
    SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2 = user_దత్తాంశం;

    దశాంశం deltaY = wheelEvent->deltaY;
    దశాంశం deltaX = wheelEvent->deltaX;

    ఎంపిక (wheelEvent->delta_బహుళకం) {
    స్థితి DOM_DELTA_PIXEL:
        deltaX /= 100; // 100 pixels make up a step
        deltaY /= 100; // 100 pixels make up a step
        ఆపు;
    స్థితి DOM_DELTA_పంక్తి:
        deltaX /= 3; // 3 lines make up a step
        deltaY /= 3; // 3 lines make up a step
        ఆపు;
    స్థితి DOM_DELTA_పుట:
        deltaX *= 80; // A page makes up 80 steps
        deltaY *= 80; // A page makes up 80 steps
        ఆపు;
    }

    SDL_SendMouseWheel(0, కిటికీ_దత్తాంశం_2->కిటికీ, SDL_DEFAULT_MOUSE_ID, deltaX, -deltaY, SDL_MOUSEWHEEL_సాధారణ);
    తిరిగి SDL_EventEnabled(SDL_EVENT_MOUSE_WHEEL);
}

స్థిర EM_BOOL Emscripten_HandleFocus(పూర్ణాంకం eventType, స్థిరరాశి EmscriptenFocusEvent *focusEvent, శూన్య *user_దత్తాంశం)
{
    SDL_VideoDevice *device = user_దత్తాంశం;
    SDL_కిటికీ *కిటికీ = Emscripten_Get_Focused_కిటికీ(device);

    SDL_EventType sdl_event_type;

    /* If the user switches away while keys are pressed (such as
     * via Alt+Tab), key release events won't be received. */
    ఒకవేళ (eventType == EMSCRIPTEN_EVENT_BLUR) {
        SDL_ResetKeyboard();
    }

    sdl_event_type = (eventType == EMSCRIPTEN_EVENT_FOCUS) ? SDL_EVENT_కిటికీ_FOCUS_GAINED : SDL_EVENT_కిటికీ_FOCUS_కోల్పోయిన;
    SDL_సమితి_Keyboard_Focus(sdl_event_type == SDL_EVENT_కిటికీ_FOCUS_GAINED ? కిటికీ : ఖాళీ);
    తిరిగి SDL_EventEnabled(sdl_event_type);
}

స్థిర bool Is_Function_కీలకం(SDL_Scancode scancode)
{
    ఒకవేళ (scancode >= SDL_SCANCODE_F1 && scancode <= SDL_SCANCODE_F12) {
        తిరిగి true;
    }
    ఒకవేళ (scancode >= SDL_SCANCODE_F13 && scancode <= SDL_SCANCODE_F24) {
        తిరిగి true;
    }
    తిరిగి false;
}

/* This is a great tool to see web keyboard events live:
 * https://w3c.github.io/uievents/tools/key-event-viewer.html
 */
స్థిర EM_BOOL Emscripten_Handle_కీలకం(పూర్ణాంకం eventType, స్థిరరాశి EmscriptenKeyboardEvent *కీలకం_Event, శూన్య *user_దత్తాంశం)
{
    SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2 = (SDL_కిటికీ_దత్తాంశం *)user_దత్తాంశం;
    SDL_Scancode scancode = Emscripten_Map_పరిశీలన_సంకేతం(కీలకం_Event->సంకేతం_2);
    SDL_Keycode keycode = SDLK_UNKNOWN;
    bool prevent_default = false;
    bool is_nav_కీలకం = false;

    ఒకవేళ (scancode == SDL_SCANCODE_UNKNOWN) {
        ఒకవేళ (SDL_strcmp(కీలకం_Event->కీలకం, "Sleep") == 0) {
            scancode = SDL_SCANCODE_SLEEP;
        } లేకపోతే ఒకవేళ (SDL_strcmp(కీలకం_Event->కీలకం, "ChannelUp") == 0) {
            scancode = SDL_SCANCODE_CHANNEL_INCREMENT;
        } లేకపోతే ఒకవేళ (SDL_strcmp(కీలకం_Event->కీలకం, "ChannelDown") == 0) {
            scancode = SDL_SCANCODE_CHANNEL_DECREMENT;
        } లేకపోతే ఒకవేళ (SDL_strcmp(కీలకం_Event->కీలకం, "MediaPlay") == 0) {
            scancode = SDL_SCANCODE_MEDIA_PLAY;
        } లేకపోతే ఒకవేళ (SDL_strcmp(కీలకం_Event->కీలకం, "MediaPause") == 0) {
            scancode = SDL_SCANCODE_MEDIA_PAUSE;
        } లేకపోతే ఒకవేళ (SDL_strcmp(కీలకం_Event->కీలకం, "MediaRecord") == 0) {
            scancode = SDL_SCANCODE_MEDIA_రికార్డు;
        } లేకపోతే ఒకవేళ (SDL_strcmp(కీలకం_Event->కీలకం, "MediaFastForward") == 0) {
            scancode = SDL_SCANCODE_MEDIA_FAST_FORWARD;
        } లేకపోతే ఒకవేళ (SDL_strcmp(కీలకం_Event->కీలకం, "MediaRewind") == 0) {
            scancode = SDL_SCANCODE_MEDIA_REWIND;
        } లేకపోతే ఒకవేళ (SDL_strcmp(కీలకం_Event->కీలకం, "Close") == 0) {
            scancode = SDL_SCANCODE_AC_CLOSE;
        } లేకపోతే ఒకవేళ (SDL_strcmp(కీలకం_Event->కీలకం, "New") == 0) {
            scancode = SDL_SCANCODE_AC_NEW;
        } లేకపోతే ఒకవేళ (SDL_strcmp(కీలకం_Event->కీలకం, "Open") == 0) {
            scancode = SDL_SCANCODE_AC_OPEN;
        } లేకపోతే ఒకవేళ (SDL_strcmp(కీలకం_Event->కీలకం, "Print") == 0) {
            scancode = SDL_SCANCODE_AC_PRINT;
        } లేకపోతే ఒకవేళ (SDL_strcmp(కీలకం_Event->కీలకం, "Save") == 0) {
            scancode = SDL_SCANCODE_AC_SAVE;
        } లేకపోతే ఒకవేళ (SDL_strcmp(కీలకం_Event->కీలకం, "Props") == 0) {
            scancode = SDL_SCANCODE_AC_PROPERTIES;
        }
    }

    ఒకవేళ (scancode == SDL_SCANCODE_UNKNOWN) {
        // KaiOS Left Soft Key and Right Soft Key, they act as OK/Next/Menu and Cancel/Back/Clear
        ఒకవేళ (SDL_strcmp(కీలకం_Event->కీలకం, "SoftLeft") == 0) {
            scancode = SDL_SCANCODE_AC_FORWARD;
        } లేకపోతే ఒకవేళ (SDL_strcmp(కీలకం_Event->కీలకం, "SoftRight") == 0) {
            scancode = SDL_SCANCODE_AC_వెనుక;
        }
    }

    ఒకవేళ (కీలకం_Event->location == 0 && SDL_utf8strlen(కీలకం_Event->కీలకం) == 1) {
        స్థిరరాశి అక్షరం *కీలకం = కీలకం_Event->కీలకం;
        keycode = SDL_అడుగు_UTF8(&కీలకం, ఖాళీ);
        ఒకవేళ (keycode == SDL_INVALID_UNICODE_CODEPOINT) {
            keycode = SDLK_UNKNOWN;
        }
    }

    ఒకవేళ (keycode != SDLK_UNKNOWN) {
        prevent_default = SDL_Send_Keyboard_కీలకం_And_Keycode(0, SDL_DEFAULT_KEYBOARD_ID, 0, scancode, keycode, (eventType == EMSCRIPTEN_EVENT_KEYDOWN));
    } లేకపోతే {
        prevent_default = SDL_Send_Keyboard_కీలకం(0, SDL_DEFAULT_KEYBOARD_ID, 0, scancode, (eventType == EMSCRIPTEN_EVENT_KEYDOWN));
    }

    /* if TEXTINPUT events are enabled we can't prevent keydown or we won't get keypress
     * we need to ALWAYS prevent backspace and tab otherwise chrome takes action and does bad navigation UX
     */
    ఒకవేళ ((scancode == SDL_SCANCODE_BACKSPACE) ||
        (scancode == SDL_SCANCODE_TAB) ||
        (scancode == SDL_SCANCODE_ఎడమ) ||
        (scancode == SDL_SCANCODE_పైకి) ||
        (scancode == SDL_SCANCODE_కుడి) ||
        (scancode == SDL_SCANCODE_కిందికి) ||
        Is_Function_కీలకం(scancode) ||
        కీలకం_Event->ctrl_కీలకం) {
        is_nav_కీలకం = true;
    }

    ఒకవేళ ((eventType == EMSCRIPTEN_EVENT_KEYDOWN) && SDL_పాఠ్యం_ఆదానం_చురుకైన(కిటికీ_దత్తాంశం_2->కిటికీ) && !is_nav_కీలకం) {
        prevent_default = false;
    }

    తిరిగి prevent_default;
}

స్థిర EM_BOOL Emscripten_Handle_కీలకం_Press(పూర్ణాంకం eventType, స్థిరరాశి EmscriptenKeyboardEvent *కీలకం_Event, శూన్య *user_దత్తాంశం)
{
    SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2 = (SDL_కిటికీ_దత్తాంశం *)user_దత్తాంశం;

    ఒకవేళ (SDL_పాఠ్యం_ఆదానం_చురుకైన(కిటికీ_దత్తాంశం_2->కిటికీ)) {
        ఒకవేళ (SDL_utf8strlen(కీలకం_Event->కీలకం) == 1) {
            SDL_Send_Keyboard_పాఠ్యం(కీలకం_Event->కీలకం);
            తిరిగి EM_TRUE;
        }
    }
    తిరిగి EM_FALSE;
}

స్థిర EM_BOOL Emscripten_HandleFullscreenChange(పూర్ణాంకం eventType, స్థిరరాశి EmscriptenFullscreenChangeEvent *fullscreenChangeEvent, శూన్య *user_దత్తాంశం)
{
    SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2 = user_దత్తాంశం;

    కిటికీ_దత్తాంశం_2->fullscreen_change_లోపల_పురోగతి = false;

    ఒకవేళ (fullscreenChangeEvent->isFullscreen) {
        SDL_Send_కిటికీ_Event(కిటికీ_దత్తాంశం_2->కిటికీ, SDL_EVENT_కిటికీ_ENTER_FULLSCREEN, 0, 0);
        కిటికీ_దత్తాంశం_2->fullscreen_బహుళకం_flags = 0;
    } లేకపోతే {
        SDL_Send_కిటికీ_Event(కిటికీ_దత్తాంశం_2->కిటికీ, SDL_EVENT_కిటికీ_LEAVE_FULLSCREEN, 0, 0);
    }

    SDL_Update_Fullscreen_బహుళకం(కిటికీ_దత్తాంశం_2->కిటికీ, fullscreenChangeEvent->isFullscreen, false);

    తిరిగి 0;
}

స్థిర EM_BOOL Emscripten_HandleFullscreenChangeGlobal(పూర్ణాంకం eventType, స్థిరరాశి EmscriptenFullscreenChangeEvent *fullscreenChangeEvent, శూన్య *user_దత్తాంశం)
{
    SDL_VideoDevice *device = user_దత్తాంశం;
    SDL_కిటికీ *కిటికీ = ఖాళీ;
    కొరకు (కిటికీ = device->windows; కిటికీ != ఖాళీ; కిటికీ = కిటికీ->తదుపరి) {
        స్థిరరాశి అక్షరం *canvas_id = కిటికీ->అంతర్గత->canvas_id;
        ఒకవేళ (*canvas_id == '#') {
            canvas_id++;
        }
        ఒకవేళ (SDL_strcmp(fullscreenChangeEvent->id, canvas_id) == 0) {
            ఆపు;  // this is the window.
        }
    }

    ఒకవేళ (కిటికీ) {
        తిరిగి Emscripten_HandleFullscreenChange(eventType, fullscreenChangeEvent, కిటికీ->అంతర్గత);
    }

    తిరిగి EM_FALSE;
}

స్థిర EM_BOOL Emscripten_HandleResize(పూర్ణాంకం eventType, స్థిరరాశి EmscriptenUiEvent *uiEvent, శూన్య *user_దత్తాంశం)
{
    SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2 = user_దత్తాంశం;

    bool force = false;

    // update pixel ratio
    ఒకవేళ (కిటికీ_దత్తాంశం_2->కిటికీ->flags & SDL_కిటికీ_ఎగువ_PIXEL_DENSITY) {
        ఒకవేళ (కిటికీ_దత్తాంశం_2->pixel_నిష్పత్తి != emscripten_get_device_pixel_నిష్పత్తి()) {
            కిటికీ_దత్తాంశం_2->pixel_నిష్పత్తి = emscripten_get_device_pixel_నిష్పత్తి();
            force = true;
        }
    }

    స్థిరరాశి bool fill_document = (Emscripten_fill_document_కిటికీ == కిటికీ_దత్తాంశం_2->కిటికీ);
    స్థిరరాశి bool fullscreen = (కిటికీ_దత్తాంశం_2->కిటికీ->flags & SDL_కిటికీ_FULLSCREEN) != 0;  // fullscreen windows can resize on Emscripten, and the canvas should fill it.
    స్థిరరాశి bool resizable = (కిటికీ_దత్తాంశం_2->కిటికీ->flags & SDL_కిటికీ_RESIZABLE) != 0;
    ఒకవేళ (fill_document || fullscreen || resizable) {
        ద్విగుణ w, h;
        ఒకవేళ (fill_document || fullscreen) {
            w = (ద్విగుణ) uiEvent->కిటికీ_Inner_వెడల్పు;
            h = (ద్విగుణ) uiEvent->కిటికీ_Inner_ఎత్తు;
        } లేకపోతే {
            SDL_assert(కిటికీ_దత్తాంశం_2->కిటికీ->flags & SDL_కిటికీ_RESIZABLE);
            w = కిటికీ_దత్తాంశం_2->కిటికీ->w;
            h = కిటికీ_దత్తాంశం_2->కిటికీ->h;
            // this will only work if the canvas size is set through css
            ఒకవేళ (కిటికీ_దత్తాంశం_2->external_కొలత) {
                emscripten_get_element_css_కొలత(కిటికీ_దత్తాంశం_2->canvas_id, &w, &h);
            }
        }

        emscripten_సమితి_canvas_element_కొలత(కిటికీ_దత్తాంశం_2->canvas_id, SDL_lroundf(w * కిటికీ_దత్తాంశం_2->pixel_నిష్పత్తి), SDL_lroundf(h * కిటికీ_దత్తాంశం_2->pixel_నిష్పత్తి));

        // set_canvas_size unsets this
        ఒకవేళ (!కిటికీ_దత్తాంశం_2->external_కొలత && కిటికీ_దత్తాంశం_2->pixel_నిష్పత్తి != 1.0f) {
            emscripten_సమితి_element_css_కొలత(కిటికీ_దత్తాంశం_2->canvas_id, w, h);
        }

        ఒకవేళ (force) {
            // force the event to trigger, so pixel ratio changes can be handled
            కిటికీ_దత్తాంశం_2->కిటికీ->w = 0;
            కిటికీ_దత్తాంశం_2->కిటికీ->h = 0;
        }

        SDL_Send_కిటికీ_Event(కిటికీ_దత్తాంశం_2->కిటికీ, SDL_EVENT_కిటికీ_RESIZED, SDL_lroundf(w), SDL_lroundf(h));
    }

    తిరిగి 0;
}

స్థిర EM_BOOL Emscripten_HandleResizeGlobal(పూర్ణాంకం eventType, స్థిరరాశి EmscriptenUiEvent *uiEvent, శూన్య *user_దత్తాంశం)
{
    SDL_VideoDevice *device = user_దత్తాంశం;
    bool prevent_default = false;
    SDL_కిటికీ *కిటికీ;

    కొరకు (కిటికీ = device->windows; కిటికీ; కిటికీ = కిటికీ->తదుపరి) {
        prevent_default |= Emscripten_HandleResize(eventType, uiEvent, కిటికీ->అంతర్గత);
    }

    తిరిగి prevent_default;
}

EM_BOOL
Emscripten_HandleCanvasResize(పూర్ణాంకం eventType, స్థిరరాశి శూన్య *reserved, శూన్య *user_దత్తాంశం)
{
    // this is used during fullscreen changes
    SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2 = user_దత్తాంశం;

    ఒకవేళ (కిటికీ_దత్తాంశం_2->fullscreen_resize) {
        ద్విగుణ css_w, css_h;
        emscripten_get_element_css_కొలత(కిటికీ_దత్తాంశం_2->canvas_id, &css_w, &css_h);
        SDL_Send_కిటికీ_Event(కిటికీ_దత్తాంశం_2->కిటికీ, SDL_EVENT_కిటికీ_RESIZED, SDL_lroundf(css_w), SDL_lroundf(css_h));
    }

    తిరిగి 0;
}

స్థిర EM_BOOL Emscripten_HandleVisibilityChange(పూర్ణాంకం eventType, స్థిరరాశి EmscriptenVisibilityChangeEvent *visEvent, శూన్య *user_దత్తాంశం)
{
    SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2 = user_దత్తాంశం;
    SDL_Send_కిటికీ_Event(కిటికీ_దత్తాంశం_2->కిటికీ, visEvent->hidden ? SDL_EVENT_కిటికీ_HIDDEN : SDL_EVENT_కిటికీ_SHOWN, 0, 0);
    తిరిగి 0;
}

స్థిర స్థిరరాశి అక్షరం *Emscripten_HandleBeforeUnload(పూర్ణాంకం eventType, స్థిరరాశి శూన్య *reserved, శూన్య *user_దత్తాంశం)
{
    /* This event will need to be handled synchronously, e.g. using
       SDL_AddEventWatch, as the page is being closed *now*. */
    SDL_SendQuit();  // the app might see this if they installed an event watcher.
    SDL_OnApplicationWillTerminate();  // calls SDL_AppQuit if appropriate, etc.
    తిరిగి ""; // don't trigger confirmation dialog
}

స్థిర EM_BOOL Emscripten_HandleOrientationChange(పూర్ణాంకం eventType, స్థిరరాశి EmscriptenOrientationChangeEvent *orientationChangeEvent, శూన్య *user_దత్తాంశం)
{
    SDL_DisplayOrientation orientation;
    ఎంపిక (orientationChangeEvent->orientation_సూచీ) {
        #నిర్వచించు CHECK_ORIENTATION(emsdk, sdl) స్థితి EMSCRIPTEN_ORIENTATION_##emsdk: orientation = SDL_ORIENTATION_##sdl; ఆపు
        CHECK_ORIENTATION(LANDSCAPE_PRIMARY, LANDSCAPE);
        CHECK_ORIENTATION(LANDSCAPE_SECONDARY, LANDSCAPE_FLIPPED);
        CHECK_ORIENTATION(PORTRAIT_PRIMARY, PORTRAIT);
        CHECK_ORIENTATION(PORTRAIT_SECONDARY, PORTRAIT_FLIPPED);
        #నిర్వచనం_రద్దు CHECK_ORIENTATION
        అప్రమేయ: orientation = SDL_ORIENTATION_UNKNOWN; ఆపు;
    }

    SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2 = (SDL_కిటికీ_దత్తాంశం *) user_దత్తాంశం;
    SDL_SendDisplayEvent(SDL_Get_Video_Display_For_కిటికీ(కిటికీ_దత్తాంశం_2->కిటికీ), SDL_EVENT_DISPLAY_ORIENTATION, orientation, 0);

    // fake a UI event so we can tell the app the canvas might have resized.
    EmscriptenUiEvent uiEvent;
    SDL_zero(uiEvent);
    uiEvent.document_Body_Client_వెడల్పు = MAIN_THREAD_EM_ASM_INT( { తిరిగి document.body.client_వెడల్పు; } );
    uiEvent.document_Body_Client_ఎత్తు = MAIN_THREAD_EM_ASM_INT( { తిరిగి document.body.client_ఎత్తు; } );
    uiEvent.కిటికీ_Inner_వెడల్పు = MAIN_THREAD_EM_ASM_INT( { తిరిగి కిటికీ.inner_వెడల్పు; } );
    uiEvent.కిటికీ_Inner_ఎత్తు = MAIN_THREAD_EM_ASM_INT( { తిరిగి కిటికీ.inner_ఎత్తు; } );
    uiEvent.కిటికీ_Outer_వెడల్పు = MAIN_THREAD_EM_ASM_INT( { తిరిగి కిటికీ.outer_వెడల్పు; } );
    uiEvent.కిటికీ_Outer_ఎత్తు = MAIN_THREAD_EM_ASM_INT( { తిరిగి కిటికీ.outer_ఎత్తు; } );
    uiEvent.scroll_శిఖరం = MAIN_THREAD_EM_ASM_INT( { తిరిగి కిటికీ.పుట_XOffset; } );
    uiEvent.scroll_ఎడమ = MAIN_THREAD_EM_ASM_INT( { తిరిగి కిటికీ.పుట_YOffset; } );
    Emscripten_HandleResize(EMSCRIPTEN_EVENT_RESIZE, &uiEvent, user_దత్తాంశం);

    తిరిగి 0;
}

// IF YOU CHANGE THIS STRUCTURE, YOU NEED TO UPDATE THE JAVASCRIPT THAT FILLS IT IN: SDL3.makePointerEventCStruct, below.
#నిర్వచించు PTRTYPE_MOUSE 1
#నిర్వచించు PTRTYPE_TOUCH 2
#నిర్వచించు PTRTYPE_PEN 3
రకనిర్వచనం నిర్మాణం Emscripten_సూచిక_Event
{
    పూర్ణాంకం సూచిక_type;
    పూర్ణాంకం pointerid;
    పూర్ణాంకం button;
    పూర్ణాంకం buttons;
    పూర్ణాంకం కిందికి;
    దశాంశం movementX;
    దశాంశం movementY;
    దశాంశం లక్ష్యం_X;
    దశాంశం లక్ష్యం_Y;
    దశాంశం pressure;
    దశాంశం tangential_pressure;
    దశాంశం tiltx;
    దశాంశం tilty;
    దశాంశం rotation;
} Emscripten_సూచిక_Event;

స్థిర శూన్య Emscripten_HandleMouseButton(SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2, స్థిరరాశి Emscripten_సూచిక_Event *event)
{
    Uint8 sdl_button;
    bool కిందికి = false;
    ఎంపిక (event->button) {
        #నిర్వచించు CHECK_MOUSE_BUTTON(jsbutton, downflag, sdlbutton) స్థితి jsbutton: sdl_button = SDL_BUTTON_##sdlbutton; కిందికి = (event->కిందికి != 0) || ((event->buttons & downflag) != 0); ఆపు
        CHECK_MOUSE_BUTTON(0, 1, ఎడమ_2);
        CHECK_MOUSE_BUTTON(1, 4, మధ్య_2);
        CHECK_MOUSE_BUTTON(2, 2, కుడి_2);
        CHECK_MOUSE_BUTTON(3, 8, X1);
        CHECK_MOUSE_BUTTON(4, 16, X2);
        #నిర్వచనం_రద్దు CHECK_MOUSE_BUTTON
        అప్రమేయ: sdl_button = 0; ఆపు;
    }

    ఒకవేళ (sdl_button) {
        స్థిరరాశి SDL_Mouse *mouse = SDL_GetMouse();
        SDL_assert(mouse != ఖాళీ);

        ఒకవేళ (కిందికి) {
            ఒకవేళ (mouse->relative_బహుళకం && !కిటికీ_దత్తాంశం_2->has_సూచిక_తాళం) {
                emscripten_request_pointerlock(కిటికీ_దత్తాంశం_2->canvas_id, 0); // try to regrab lost pointer lock.
            }
        }

        SDL_SendMouseButton(0, కిటికీ_దత్తాంశం_2->కిటికీ, SDL_DEFAULT_MOUSE_ID, sdl_button, కిందికి);

        // We have an imaginary mouse capture, because we need SDL to not drop our imaginary mouse focus when we leave the canvas.
        ఒకవేళ (mouse->auto_capture) {
            ఒకవేళ (SDL_GetMouseState(ఖాళీ, ఖాళీ) != 0) {
                కిటికీ_దత్తాంశం_2->కిటికీ->flags |= SDL_కిటికీ_MOUSE_CAPTURE;
            } లేకపోతే {
                కిటికీ_దత్తాంశం_2->కిటికీ->flags &= ~SDL_కిటికీ_MOUSE_CAPTURE;
            }
        }

        ఒకవేళ (!కిందికి && కిటికీ_దత్తాంశం_2->mouse_focus_loss_pending) {
            కిటికీ_దత్తాంశం_2->mouse_focus_loss_pending = (కిటికీ_దత్తాంశం_2->కిటికీ->flags & SDL_కిటికీ_MOUSE_CAPTURE) != 0;
            ఒకవేళ (!కిటికీ_దత్తాంశం_2->mouse_focus_loss_pending) {
                SDL_సమితి_Mouse_Focus(ఖాళీ);
            }
        }
    }
}

స్థిర శూన్య Emscripten_UpdateMouseFromEvent(SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2, స్థిరరాశి Emscripten_సూచిక_Event *event)
{
    SDL_assert(event->సూచిక_type == PTRTYPE_MOUSE);

    // Hidden windows (e.g. a shared GL-context window) may share the DOM canvas with the
    // visible window. Their pointer-event listeners would otherwise fire alongside the
    // visible window's, fighting over `mouse->focus` and producing events tagged with the
    // hidden window's ID -- causing downstream consumers that key by window ID to silently
    // drop them. Hidden windows shouldn't take part in user-input dispatch.
    ఒకవేళ (కిటికీ_దత్తాంశం_2->కిటికీ->flags & SDL_కిటికీ_HIDDEN) {
        తిరిగి;
    }

    // rescale (in case canvas is being scaled)
    ద్విగుణ client_w, client_h;
    emscripten_get_element_css_కొలత(కిటికీ_దత్తాంశం_2->canvas_id, &client_w, &client_h);
    స్థిరరాశి ద్విగుణ xscale = కిటికీ_దత్తాంశం_2->కిటికీ->w / client_w;
    స్థిరరాశి ద్విగుణ yscale = కిటికీ_దత్తాంశం_2->కిటికీ->h / client_h;

    స్థిరరాశి bool is_సూచిక_Locked = కిటికీ_దత్తాంశం_2->has_సూచిక_తాళం;
    దశాంశం mx, my;
    ఒకవేళ (is_సూచిక_Locked) {
        mx = (దశాంశం)(event->movementX * xscale);
        my = (దశాంశం)(event->movementY * yscale);
    } లేకపోతే {
        mx = (దశాంశం)(event->లక్ష్యం_X * xscale);
        my = (దశాంశం)(event->లక్ష్యం_Y * yscale);
    }

    SDL_SendMouseMotion(0, కిటికీ_దత్తాంశం_2->కిటికీ, SDL_DEFAULT_MOUSE_ID, is_సూచిక_Locked, mx, my);

    Emscripten_HandleMouseButton(కిటికీ_దత్తాంశం_2, event);
}

స్థిర శూన్య Emscripten_UpdateTouchFromEvent(SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2, స్థిరరాశి Emscripten_సూచిక_Event *event)
{
    SDL_assert(event->సూచిక_type == PTRTYPE_TOUCH);

    స్థిరరాశి SDL_TouchID deviceId = 1;
    ఒకవేళ (SDL_కూడు_Touch(deviceId, SDL_TOUCH_DEVICE_ప్రత్యక్ష, "") < 0) {
        తిరిగి;
    }

    ద్విగుణ client_w, client_h;
    emscripten_get_element_css_కొలత(కిటికీ_దత్తాంశం_2->canvas_id, &client_w, &client_h);

    స్థిరరాశి SDL_FingerID id = event->pointerid + 1;
    దశాంశం x, y;
    ఒకవేళ (client_w <= 1) {
        x = 0.5f;
    } లేకపోతే {
        x = event->లక్ష్యం_X / (client_w - 1);
    }
    ఒకవేళ (client_h <= 1) {
        y = 0.5f;
    } లేకపోతే {
        y = event->లక్ష్యం_Y / (client_h - 1);
    }

    స్థిరరాశి bool కిందికి = (event->buttons & 1) != 0;
    ఒకవేళ (event->button == 0) {  // touch is starting or ending if this is zero (-1 means "no change").
        ఒకవేళ (కిందికి) {
            SDL_SendTouch(0, deviceId, id, కిటికీ_దత్తాంశం_2->కిటికీ, SDL_EVENT_FINGER_కిందికి, x, y, 1.0f);
        }
    }

    SDL_SendTouchMotion(0, deviceId, id, కిటికీ_దత్తాంశం_2->కిటికీ, x, y, 1.0f);

    ఒకవేళ (event->button == 0) {  // touch is starting or ending if this is zero (-1 means "no change").
        ఒకవేళ (!కిందికి) {
            SDL_SendTouch(0, deviceId, id, కిటికీ_దత్తాంశం_2->కిటికీ, SDL_EVENT_FINGER_పైకి, x, y, 1.0f);
        }
    }
}

స్థిర శూన్య Emscripten_UpdatePenFromEvent(SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2, స్థిరరాశి Emscripten_సూచిక_Event *event)
{
    SDL_assert(event->సూచిక_type == PTRTYPE_PEN);
    స్థిరరాశి SDL_PenID pen = SDL_కనుగొను_Pen_By_Handle((శూన్య *) (size_t) 1);   // something > 0 for the single pen handle.
    ఒకవేళ (pen) {
        // rescale (in case canvas is being scaled)
        ద్విగుణ client_w, client_h;
        emscripten_get_element_css_కొలత(కిటికీ_దత్తాంశం_2->canvas_id, &client_w, &client_h);
        స్థిరరాశి ద్విగుణ xscale = కిటికీ_దత్తాంశం_2->కిటికీ->w / client_w;
        స్థిరరాశి ద్విగుణ yscale = కిటికీ_దత్తాంశం_2->కిటికీ->h / client_h;

        స్థిరరాశి bool is_సూచిక_Locked = కిటికీ_దత్తాంశం_2->has_సూచిక_తాళం;
        దశాంశం mx, my;
        ఒకవేళ (is_సూచిక_Locked) {
            mx = (దశాంశం)(event->movementX * xscale);
            my = (దశాంశం)(event->movementY * yscale);
        } లేకపోతే {
            mx = (దశాంశం)(event->లక్ష్యం_X * xscale);
            my = (దశాంశం)(event->లక్ష్యం_Y * yscale);
        }

        SDL_SendPenMotion(0, pen, కిటికీ_దత్తాంశం_2->కిటికీ, mx, my);

        ఒకవేళ (event->button == 0) {  // pen touch
            bool కిందికి = ((event->buttons & 1) != 0);
            SDL_SendPenTouch(0, pen, కిటికీ_దత్తాంశం_2->కిటికీ, false, కిందికి);
        } లేకపోతే ఒకవేళ (event->button == 5) {  // eraser touch...? Not sure if this is right...
            bool కిందికి = ((event->buttons & 32) != 0);
            SDL_SendPenTouch(0, pen, కిటికీ_దత్తాంశం_2->కిటికీ, true, కిందికి);
        } లేకపోతే ఒకవేళ (event->button == 1) {
            bool కిందికి = ((event->buttons & 4) != 0);
            SDL_SendPenButton(0, pen, కిటికీ_దత్తాంశం_2->కిటికీ, 2, కిందికి);
        } లేకపోతే ఒకవేళ (event->button == 2) {
            bool కిందికి = ((event->buttons & 2) != 0);
            SDL_SendPenButton(0, pen, కిటికీ_దత్తాంశం_2->కిటికీ, 1, కిందికి);
        }

        SDL_SendPenAxis(0, pen, కిటికీ_దత్తాంశం_2->కిటికీ, SDL_PEN_AXIS_PRESSURE, event->pressure);
        SDL_SendPenAxis(0, pen, కిటికీ_దత్తాంశం_2->కిటికీ, SDL_PEN_AXIS_TANGENTIAL_PRESSURE, event->tangential_pressure);
        SDL_SendPenAxis(0, pen, కిటికీ_దత్తాంశం_2->కిటికీ, SDL_PEN_AXIS_XTILT, event->tiltx);
        SDL_SendPenAxis(0, pen, కిటికీ_దత్తాంశం_2->కిటికీ, SDL_PEN_AXIS_YTILT, event->tilty);
        SDL_SendPenAxis(0, pen, కిటికీ_దత్తాంశం_2->కిటికీ, SDL_PEN_AXIS_ROTATION, event->rotation);
    }
}

స్థిర శూన్య Emscripten_Update_సూచిక_From_Event(SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2, స్థిరరాశి Emscripten_సూచిక_Event *event)
{
    SDL_assert(event != ఖాళీ);
    ఒకవేళ (event->సూచిక_type == PTRTYPE_MOUSE) {
        Emscripten_UpdateMouseFromEvent(కిటికీ_దత్తాంశం_2, event);
    } లేకపోతే ఒకవేళ (event->సూచిక_type == PTRTYPE_TOUCH) {
        Emscripten_UpdateTouchFromEvent(కిటికీ_దత్తాంశం_2, event);
    } లేకపోతే ఒకవేళ (event->సూచిక_type == PTRTYPE_PEN) {
        Emscripten_UpdatePenFromEvent(కిటికీ_దత్తాంశం_2, event);
    } లేకపోతే {
        SDL_assert(!"Unexpected pointer event type");
    }
}

స్థిర శూన్య Emscripten_HandleMouseFocus(SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2, స్థిరరాశి Emscripten_సూచిక_Event *event, bool isenter)
{
    SDL_assert(event->సూచిక_type == PTRTYPE_MOUSE);

    // Hidden windows shouldn't ever become the mouse-focus target.
    ఒకవేళ (కిటికీ_దత్తాంశం_2->కిటికీ->flags & SDL_కిటికీ_HIDDEN) {
        తిరిగి;
    }

    స్థిరరాశి bool is_సూచిక_Locked = కిటికీ_దత్తాంశం_2->has_సూచిక_తాళం;

    ఒకవేళ (!is_సూచిక_Locked) {
        // rescale (in case canvas is being scaled)
        దశాంశం mx, my;
        ద్విగుణ client_w, client_h;
        emscripten_get_element_css_కొలత(కిటికీ_దత్తాంశం_2->canvas_id, &client_w, &client_h);

        mx = (దశాంశం)(event->లక్ష్యం_X * (కిటికీ_దత్తాంశం_2->కిటికీ->w / client_w));
        my = (దశాంశం)(event->లక్ష్యం_Y * (కిటికీ_దత్తాంశం_2->కిటికీ->h / client_h));
        SDL_SendMouseMotion(0, కిటికీ_దత్తాంశం_2->కిటికీ, SDL_GLOBAL_MOUSE_ID, is_సూచిక_Locked, mx, my);
    }

    ఒకవేళ (isenter && కిటికీ_దత్తాంశం_2->mouse_focus_loss_pending) {
        కిటికీ_దత్తాంశం_2->mouse_focus_loss_pending = false;  // just drop the state, but don't send the enter event.
    } లేకపోతే ఒకవేళ (!isenter && (కిటికీ_దత్తాంశం_2->కిటికీ->flags & SDL_కిటికీ_MOUSE_CAPTURE)) {
        కిటికీ_దత్తాంశం_2->mouse_focus_loss_pending = true;  // waiting on a mouse button to let go before we send the mouse focus update.
    } లేకపోతే {
        SDL_సమితి_Mouse_Focus(isenter ? కిటికీ_దత్తాంశం_2->కిటికీ : ఖాళీ);
    }
}

స్థిర శూన్య Emscripten_HandlePenEnter(SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2, స్థిరరాశి Emscripten_సూచిక_Event *event)
{
    SDL_assert(event->సూచిక_type == PTRTYPE_PEN);

    // event->pointerid is one continuous interaction; it doesn't necessarily track a specific tool over time, like the same finger's ID changed on each new touch event.
    // as such, we only expose a single pen, and when the touch ends, we say it lost proximity instead of the calling SDL_RemovePenDevice().

    SDL_PenID pen = SDL_కనుగొను_Pen_By_Handle((శూన్య *) (size_t) 1);  // something > 0 for the single pen handle.
    ఒకవేళ (pen) {
        SDL_SendPenProximity(0, pen, కిటికీ_దత్తాంశం_2->కిటికీ, true, true);
    } లేకపోతే {
        // Web browsers offer almost none of this information as specifics, but can without warning offer any of these specific things.
        SDL_PenInfo peninfo;
        SDL_zero(peninfo);
        peninfo.capabilities = SDL_PEN_CAPABILITY_PRESSURE | SDL_PEN_CAPABILITY_ROTATION | SDL_PEN_CAPABILITY_XTILT | SDL_PEN_CAPABILITY_YTILT | SDL_PEN_CAPABILITY_TANGENTIAL_PRESSURE | SDL_PEN_CAPABILITY_ERASER;
        peninfo.max_tilt = 90.0f;
        peninfo.అంకె_buttons = 2;
        peninfo.subtype = SDL_PEN_TYPE_PEN;
        SDL_కూడు_Pen_Device(0, ఖాళీ, కిటికీ_దత్తాంశం_2->కిటికీ, &peninfo, (శూన్య *) (size_t) 1, true);
    }

    Emscripten_UpdatePenFromEvent(కిటికీ_దత్తాంశం_2, event);
}

EMSCRIPTEN_KEEPALIVE శూన్య Emscripten_Handle_సూచిక_Enter(SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2, స్థిరరాశి Emscripten_సూచిక_Event *event)
{
    SDL_assert(event != ఖాళీ);
    ఒకవేళ (event->సూచిక_type == PTRTYPE_MOUSE) {
        Emscripten_HandleMouseFocus(కిటికీ_దత్తాంశం_2, event, true);
    } లేకపోతే ఒకవేళ (event->సూచిక_type == PTRTYPE_PEN) {
        Emscripten_HandlePenEnter(కిటికీ_దత్తాంశం_2, event);
    } లేకపోతే ఒకవేళ (event->సూచిక_type == PTRTYPE_TOUCH) {
        // do nothing.
    } లేకపోతే {
        SDL_assert(!"Unexpected pointer event type");
    }
}

స్థిర శూన్య Emscripten_HandlePenLeave(SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2, స్థిరరాశి Emscripten_సూచిక_Event *event)
{
    స్థిరరాశి SDL_PenID pen = SDL_కనుగొను_Pen_By_Handle((శూన్య *) (size_t) 1);   // something > 0 for the single pen handle.
    ఒకవేళ (pen) {
        Emscripten_Update_సూచిక_From_Event(కిటికీ_దత్తాంశం_2, event);  // last data updates?
        SDL_SendPenProximity(0, pen, కిటికీ_దత్తాంశం_2->కిటికీ, false, false);
    }
}

స్థిర శూన్య Emscripten_HandleTouchCancel(SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2, స్థిరరాశి Emscripten_సూచిక_Event *event)
{
    SDL_assert(event->సూచిక_type == PTRTYPE_TOUCH);

    స్థిరరాశి SDL_TouchID deviceId = 1;
    ఒకవేళ (SDL_కూడు_Touch(deviceId, SDL_TOUCH_DEVICE_ప్రత్యక్ష, "") < 0) {
        తిరిగి;
    }

    ద్విగుణ client_w, client_h;
    emscripten_get_element_css_కొలత(కిటికీ_దత్తాంశం_2->canvas_id, &client_w, &client_h);

    స్థిరరాశి SDL_FingerID id = event->pointerid + 1;
    దశాంశం x, y;
    ఒకవేళ (client_w <= 1) {
        x = 0.5f;
    } లేకపోతే {
        x = event->లక్ష్యం_X / (client_w - 1);
    }
    ఒకవేళ (client_h <= 1) {
        y = 0.5f;
    } లేకపోతే {
        y = event->లక్ష్యం_Y / (client_h - 1);
    }

    SDL_SendTouch(0, deviceId, id, కిటికీ_దత్తాంశం_2->కిటికీ, SDL_EVENT_FINGER_CANCELED, x, y, 1.0f);
}

EMSCRIPTEN_KEEPALIVE శూన్య Emscripten_Handle_సూచిక_Leave(SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2, స్థిరరాశి Emscripten_సూచిక_Event *event)
{
    SDL_assert(event != ఖాళీ);
    ఒకవేళ (event->సూచిక_type == PTRTYPE_MOUSE) {
        Emscripten_HandleMouseFocus(కిటికీ_దత్తాంశం_2, event, false);
    } లేకపోతే ఒకవేళ (event->సూచిక_type == PTRTYPE_PEN) {
        Emscripten_HandlePenLeave(కిటికీ_దత్తాంశం_2, event);
    } లేకపోతే ఒకవేళ (event->సూచిక_type == PTRTYPE_TOUCH) {
        Emscripten_HandleTouchCancel(కిటికీ_దత్తాంశం_2, event);
    } లేకపోతే {
        SDL_assert(!"Unexpected pointer event type");
    }
}

EMSCRIPTEN_KEEPALIVE శూన్య Emscripten_Handle_సూచిక_Generic(SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2, స్థిరరాశి Emscripten_సూచిక_Event *event)
{
    SDL_assert(event != ఖాళీ);
    Emscripten_Update_సూచిక_From_Event(కిటికీ_దత్తాంశం_2, event);
}

స్థిర శూన్య Emscripten_prep_సూచిక_event_callbacks(శూన్య)
{
    MAIN_THREAD_EM_ASM({
        var SDL3 = Module['SDL3'];

        ఒకవేళ (SDL3.make_సూచిక_Event_CStruct === undefined) {
            SDL3.make_సూచిక_Event_CStruct = function(ఎడమ, శిఖరం, event) {
                var ptrtype = 0;
                ఒకవేళ (event.సూచిక_Type == "mouse") {
                    ptrtype = 1;
                } లేకపోతే ఒకవేళ (event.సూచిక_Type == "touch") {
                    ptrtype = 2;
                } లేకపోతే ఒకవేళ (event.సూచిక_Type == "pen") {
                    ptrtype = 3;
                } లేకపోతే {
                    తిరిగి 0;
                }

                var ptr = _SDL_malloc($0);
                ఒకవేళ (ptr != 0) {
                    var idx = SDL3.CPtr_గమ్యం_Heap32_సూచీ(ptr);
                    HEAP32[idx++] = ptrtype;
                    HEAP32[idx++] = event.సూచిక_Id;
                    HEAP32[idx++] = (typeof(event.button) !== "undefined") ? event.button : -1;
                    HEAP32[idx++] = event.buttons;
                    HEAP32[idx++] = (event.type == "pointerdown") ? 1 : 0;
                    HEAPF32[idx++] = event.movementX;
                    HEAPF32[idx++] = event.movementY;
                    HEAPF32[idx++] = event.clientX - ఎడమ;
                    HEAPF32[idx++] = event.clientY - శిఖరం;
                    ఒకవేళ (ptrtype == 3) {
                        HEAPF32[idx++] = event.pressure;
                        HEAPF32[idx++] = event.tangentialPressure;
                        HEAPF32[idx++] = event.tiltX;
                        HEAPF32[idx++] = event.tiltY;
                        HEAPF32[idx++] = event.twist;
                    }
                }
                తిరిగి ptr;
            };
        }
    }, పరిమాణం (Emscripten_సూచిక_Event));
}

స్థిర శూన్య Emscripten_సమితి_సూచిక_event_callbacks(SDL_కిటికీ_దత్తాంశం *దత్తాంశం)
{
    Emscripten_prep_సూచిక_event_callbacks();

    MAIN_THREAD_EM_ASM({
        var లక్ష్యం = document.querySelector(UTF8_గమ్యం_String($1));
        ఒకవేళ (లక్ష్యం) {
            var SDL3 = Module['SDL3'];
            var దత్తాంశం = $0;
            లక్ష్యం.sdl_Event_Handler_సూచిక_Enter = function(event) {
                var rect = లక్ష్యం.getBoundingClientRect();
                var d = SDL3.make_సూచిక_Event_CStruct(rect.ఎడమ, rect.శిఖరం, event);
                ఒకవేళ (d != 0)
                {
                    Emscripten_Handle_సూచిక_Enter_2(SDL3.JSVar_గమ్యం_CPtr(దత్తాంశం), d);
                    _SDL_free(d);
                }
            };
            లక్ష్యం.sdl_Event_Handler_సూచిక_Leave = function(event) {
                var rect = లక్ష్యం.getBoundingClientRect();
                var d = SDL3.make_సూచిక_Event_CStruct(rect.ఎడమ, rect.శిఖరం, event);
                ఒకవేళ (d != 0)
                {
                    Emscripten_Handle_సూచిక_Leave_2(SDL3.JSVar_గమ్యం_CPtr(దత్తాంశం), d);
                    _SDL_free(d);
                }
            };
            లక్ష్యం.sdl_Event_Handler_సూచిక_Generic = function(event) {
                var rect = లక్ష్యం.getBoundingClientRect();
                var d = SDL3.make_సూచిక_Event_CStruct(rect.ఎడమ, rect.శిఖరం, event);
                ఒకవేళ (d != 0)
                {
                    Emscripten_Handle_సూచిక_Generic_2(SDL3.JSVar_గమ్యం_CPtr(దత్తాంశం), d);
                    _SDL_free(d);
                }
            };

            లక్ష్యం.style.touchAction = "none";  // or mobile devices will scroll as your touch moves across the element.
            లక్ష్యం.కూడు_Event_Listener("pointerenter", లక్ష్యం.sdl_Event_Handler_సూచిక_Enter);
            లక్ష్యం.కూడు_Event_Listener("pointerleave", లక్ష్యం.sdl_Event_Handler_సూచిక_Leave);
            లక్ష్యం.కూడు_Event_Listener("pointercancel", లక్ష్యం.sdl_Event_Handler_సూచిక_Leave);
            లక్ష్యం.కూడు_Event_Listener("pointerdown", లక్ష్యం.sdl_Event_Handler_సూచిక_Generic);
            లక్ష్యం.కూడు_Event_Listener("pointermove", లక్ష్యం.sdl_Event_Handler_సూచిక_Generic);
            లక్ష్యం.కూడు_Event_Listener("pointerup", లక్ష్యం.sdl_Event_Handler_సూచిక_Generic);
        }
    }, దత్తాంశం, దత్తాంశం->canvas_id);
}

స్థిర శూన్య Emscripten_unset_సూచిక_event_callbacks(SDL_కిటికీ_దత్తాంశం *దత్తాంశం)
{
    MAIN_THREAD_EM_ASM({
        var లక్ష్యం = document.querySelector(UTF8_గమ్యం_String($0));
        ఒకవేళ (లక్ష్యం) {
            లక్ష్యం.removeEventListener("pointerenter", లక్ష్యం.sdl_Event_Handler_సూచిక_Enter);
            లక్ష్యం.removeEventListener("pointerleave", లక్ష్యం.sdl_Event_Handler_సూచిక_Leave);
            లక్ష్యం.removeEventListener("pointercancel", లక్ష్యం.sdl_Event_Handler_సూచిక_Leave);
            లక్ష్యం.removeEventListener("pointerdown", లక్ష్యం.sdl_Event_Handler_సూచిక_Generic);
            లక్ష్యం.removeEventListener("pointermove", లక్ష్యం.sdl_Event_Handler_సూచిక_Generic);
            లక్ష్యం.removeEventListener("pointerup", లక్ష్యం.sdl_Event_Handler_సూచిక_Generic);
            లక్ష్యం.style.touchAction = "";  // let mobile devices scroll again as your touch moves across the element.
            లక్ష్యం.sdl_Event_Handler_సూచిక_Enter = undefined;
            లక్ష్యం.sdl_Event_Handler_సూచిక_Leave = undefined;
            లక్ష్యం.sdl_Event_Handler_సూచిక_Generic = undefined;
        }
    }, దత్తాంశం->canvas_id);
}

EMSCRIPTEN_KEEPALIVE శూన్య Emscripten_Handle_Mouse_Button_పైకి_Global(SDL_VideoDevice *device, స్థిరరాశి Emscripten_సూచిక_Event *event)
{
    SDL_assert(device != ఖాళీ);
    SDL_assert(event != ఖాళీ);
    ఒకవేళ (event->సూచిక_type == PTRTYPE_MOUSE) {
        కొరకు (SDL_కిటికీ *కిటికీ = device->windows; కిటికీ; కిటికీ = కిటికీ->తదుపరి) {
            Emscripten_HandleMouseButton(కిటికీ->అంతర్గత, event);
        }
    }
}

స్థిర శూన్య Emscripten_సమితి_global_mouseup_callback(SDL_VideoDevice *device)
{
    Emscripten_prep_సూచిక_event_callbacks();

    MAIN_THREAD_EM_ASM({
        var లక్ష్యం = document;
        ఒకవేళ (లక్ష్యం) {
            లక్ష్యం.sdl_Event_Handler_Mouse_Button_పైకి_Global = function(event) {
                var SDL3 = Module['SDL3'];
                var d = SDL3.make_సూచిక_Event_CStruct(0, 0, event);
                ఒకవేళ (d != 0)
                {
                    Emscripten_Handle_Mouse_Button_పైకి_Global_2(SDL3.JSVar_గమ్యం_CPtr($0), d);
                    _SDL_free(d);
                }
            };
            లక్ష్యం.కూడు_Event_Listener("pointerup", లక్ష్యం.sdl_Event_Handler_Mouse_Button_పైకి_Global);
        }
    }, device);
}

స్థిర శూన్య Emscripten_unset_global_mouseup_callback(SDL_VideoDevice *device)
{
    MAIN_THREAD_EM_ASM({
        var లక్ష్యం = document;
        ఒకవేళ (లక్ష్యం) {
            లక్ష్యం.removeEventListener("pointerup", లక్ష్యం.sdl_Event_Handler_Mouse_Button_పైకి_Global);
            లక్ష్యం.sdl_Event_Handler_Mouse_Button_పైకి_Global = undefined;
        }
    });
}

// IF YOU CHANGE THIS STRUCTURE, YOU NEED TO UPDATE THE JAVASCRIPT THAT FILLS IT IN: makeDropEventCStruct, below.
రకనిర్వచనం నిర్మాణం Emscripten_DropEvent
{
    పూర్ణాంకం x;
    పూర్ణాంకం y;
} Emscripten_DropEvent;

EMSCRIPTEN_KEEPALIVE శూన్య Emscripten_SendDragEvent(SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2, స్థిరరాశి Emscripten_DropEvent *event)
{
    SDL_SendDropPosition(కిటికీ_దత్తాంశం_2->కిటికీ, event->x, event->y);
}

EMSCRIPTEN_KEEPALIVE శూన్య Emscripten_SendDragCompleteEvent(SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2)
{
    SDL_SendDropComplete(కిటికీ_దత్తాంశం_2->కిటికీ);
}

EMSCRIPTEN_KEEPALIVE శూన్య Emscripten_Send_Drag_పాఠ్యం_Event(SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2, అక్షరం *పాఠ్యం)
{
    SDL_Send_Drop_పాఠ్యం(కిటికీ_దత్తాంశం_2->కిటికీ, పాఠ్యం);
}

EMSCRIPTEN_KEEPALIVE శూన్య Emscripten_SendDragFileEvent(SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2, అక్షరం *filename)
{
    SDL_SendDropFile(కిటికీ_దత్తాంశం_2->కిటికీ, ఖాళీ, filename);
}

EM_JS_DEPS(dragndrop, "$writeArrayToMemory");

స్థిర శూన్య Emscripten_సమితి_drag_event_callbacks(SDL_కిటికీ_దత్తాంశం *దత్తాంశం)
{
    MAIN_THREAD_EM_ASM({
        var లక్ష్యం = document.querySelector(UTF8_గమ్యం_String($1));
        ఒకవేళ (లక్ష్యం) {
            var దత్తాంశం = $0;
            var SDL3 = Module['SDL3'];

            var makeDropEventCStruct = function(event) {
                var ptr = 0;
                ptr = _SDL_malloc($2);
                ఒకవేళ (ptr != 0) {
                    var idx = ptr >> 2;
                    var rect = లక్ష్యం.getBoundingClientRect();
                    HEAP32[idx++] = event.clientX - rect.ఎడమ;
                    HEAP32[idx++] = event.clientY - rect.శిఖరం;
                }
                తిరిగి ptr;
            };

            SDL3.eventHandlerDropDragover = function(event) {
                event.preventDefault();
                var d = makeDropEventCStruct(event); ఒకవేళ (d != 0) { _Emscripten_SendDragEvent(దత్తాంశం, d); _SDL_free(d); }
            };
            లక్ష్యం.కూడు_Event_Listener("dragover", SDL3.eventHandlerDropDragover);

            SDL3.drop_లెక్క = 0;

            // FS.* functions throw exceptions when there are errors (such as the temp dir already existing),
            //  but we ignore all of these in a catch handler; you just won't get the drop event if there's a problem.
            try { FS.mkdir("/tmp/filedrop"); } catch (e) {}

            SDL3.eventHandlerDropDrop = function(event) {
                event.preventDefault();
                ఒకవేళ (event.దత్తాంశం_Transfer.types.includes("text/plain")) {
                    let plain_పాఠ్యం = string_గమ్యం_New_UTF8(event.దత్తాంశం_Transfer.get_దత్తాంశం("text/plain"));
                    Emscripten_Send_Drag_పాఠ్యం_Event_2(దత్తాంశం, plain_పాఠ్యం);
                    _Emscripten_force_free(plain_పాఠ్యం);
                } లేకపోతే ఒకవేళ (event.దత్తాంశం_Transfer.types.includes("Files")) {
                    let files_read = 0;
                    స్థిరరాశి files_గమ్యం_read = event.దత్తాంశం_Transfer.files.నిడివి;
                    కొరకు (let i = 0; i < files_గమ్యం_read; i++) {
                        స్థిరరాశి file = event.దత్తాంశం_Transfer.files.అంశం(i);
                        స్థిరరాశి file_reader = new FileReader();
                        file_reader.read_As_Array_బఫరు(file);
                        file_reader.onload = function(event) {
                            స్థిరరాశి fs_dropdir = `/tmp/filedrop/${SDL3.drop_లెక్క}`;
                            SDL3.drop_లెక్క += 1;

                            స్థిరరాశి fs_filepath = `${fs_dropdir}/${file.name}`;
                            స్థిరరాశి c_fs_filepath = string_గమ్యం_New_UTF8(fs_filepath);
                            స్థిరరాశి contents_array8 = new Uint8Array(event.లక్ష్యం.ఫలితం);

                            try {
                                FS.mkdir(fs_dropdir);
                                var ప్రవాహం = FS.open(fs_filepath, "w");
                                FS.లిఖ(ప్రవాహం, contents_array8, 0, contents_array8.నిడివి, 0);
                                FS.close(ప్రవాహం);
                                _Emscripten_SendDragFileEvent(దత్తాంశం, c_fs_filepath);
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
                        ఒకవేళ (files_read === files_గమ్యం_read) {
                            _Emscripten_SendDragCompleteEvent(దత్తాంశం);
                        }
                    }
                }
                _Emscripten_SendDragCompleteEvent(దత్తాంశం);
            };
            లక్ష్యం.కూడు_Event_Listener("drop", SDL3.eventHandlerDropDrop);

            SDL3.eventHandlerDropDragend = function(event) {
                event.preventDefault();
                _Emscripten_SendDragCompleteEvent(దత్తాంశం);
            };
            లక్ష్యం.కూడు_Event_Listener("dragend", SDL3.eventHandlerDropDragend);
            లక్ష్యం.కూడు_Event_Listener("dragleave", SDL3.eventHandlerDropDragend);
        }
    }, దత్తాంశం, దత్తాంశం->canvas_id, పరిమాణం (Emscripten_DropEvent));
}

స్థిర శూన్య Emscripten_unset_drag_event_callbacks(SDL_కిటికీ_దత్తాంశం *దత్తాంశం)
{
    MAIN_THREAD_EM_ASM({
        var లక్ష్యం = document.querySelector(UTF8_గమ్యం_String($0));
        ఒకవేళ (లక్ష్యం) {
            var SDL3 = Module['SDL3'];
            లక్ష్యం.removeEventListener("dragleave", SDL3.eventHandlerDropDragend);
            లక్ష్యం.removeEventListener("dragend", SDL3.eventHandlerDropDragend);
            లక్ష్యం.removeEventListener("drop", SDL3.eventHandlerDropDrop);
            SDL3.drop_లెక్క = undefined;

            function recursive_remove(dirpath) {
                FS.readdir(dirpath).forEach((filename) => {
                    స్థిరరాశి p = `${dirpath}/${filename}`;
                    స్థిరరాశి p_s = FS.stat(p);
                    ఒకవేళ (FS.isFile(p_s.బహుళకం)) {
                        FS.unlink(p);
                    } లేకపోతే ఒకవేళ (FS.isDir(p)) {
                        recursive_remove(p);
                    }
                });
                FS.rmdir(dirpath);
            }("/tmp/filedrop");

            FS.rmdir("/tmp/filedrop");
            లక్ష్యం.removeEventListener("dragover", SDL3.eventHandlerDropDragover);
            SDL3.eventHandlerDropDragover = undefined;
            SDL3.eventHandlerDropDrop = undefined;
            SDL3.eventHandlerDropDragend = undefined;
        }
    }, దత్తాంశం->canvas_id);
}

స్థిర స్థిరరాశి అక్షరం *Emscripten_Get_Keyboard_లక్ష్యం_Element(స్థిరరాశి అక్షరం *లక్ష్యం)
{
    ఒకవేళ (SDL_strcmp(లక్ష్యం, "#none") == 0) {
        తిరిగి ఖాళీ;
    } లేకపోతే ఒకవేళ (SDL_strcmp(లక్ష్యం, "#window") == 0) {
        తిరిగి EMSCRIPTEN_EVENT_లక్ష్యం_కిటికీ;
    } లేకపోతే ఒకవేళ (SDL_strcmp(లక్ష్యం, "#document") == 0) {
        తిరిగి EMSCRIPTEN_EVENT_లక్ష్యం_DOCUMENT;
    } లేకపోతే ఒకవేళ (SDL_strcmp(లక్ష్యం, "#screen") == 0) {
        తిరిగి EMSCRIPTEN_EVENT_లక్ష్యం_SCREEN;
    }

    తిరిగి లక్ష్యం;
}

శూన్య Emscripten_రిజిస్టరు_Global_Event_Handlers(SDL_VideoDevice *device)
{
    Emscripten_సమితి_global_mouseup_callback(device);

    emscripten_సమితి_focus_callback(EMSCRIPTEN_EVENT_లక్ష్యం_కిటికీ, device, 0, Emscripten_HandleFocus);
    emscripten_సమితి_blur_callback(EMSCRIPTEN_EVENT_లక్ష్యం_కిటికీ, device, 0, Emscripten_HandleFocus);

    emscripten_సమితి_pointerlockchange_callback(EMSCRIPTEN_EVENT_లక్ష్యం_DOCUMENT, device, 0, Emscripten_Handle_సూచిక_తాళం_Change_Global);

    emscripten_సమితి_fullscreenchange_callback(EMSCRIPTEN_EVENT_లక్ష్యం_DOCUMENT, device, 0, Emscripten_HandleFullscreenChangeGlobal);

    emscripten_సమితి_resize_callback(EMSCRIPTEN_EVENT_లక్ష్యం_కిటికీ, device, 0, Emscripten_HandleResizeGlobal);
}

శూన్య Emscripten_UnregisterGlobalEventHandlers(SDL_VideoDevice *device)
{
    Emscripten_unset_global_mouseup_callback(device);

    emscripten_సమితి_focus_callback(EMSCRIPTEN_EVENT_లక్ష్యం_కిటికీ, ఖాళీ, 0, ఖాళీ);
    emscripten_సమితి_blur_callback(EMSCRIPTEN_EVENT_లక్ష్యం_కిటికీ, ఖాళీ, 0, ఖాళీ);

    emscripten_సమితి_pointerlockchange_callback(EMSCRIPTEN_EVENT_లక్ష్యం_DOCUMENT, ఖాళీ, 0, ఖాళీ);

    emscripten_సమితి_fullscreenchange_callback(EMSCRIPTEN_EVENT_లక్ష్యం_DOCUMENT, ఖాళీ, 0, ఖాళీ);

    emscripten_సమితి_resize_callback(EMSCRIPTEN_EVENT_లక్ష్యం_కిటికీ, ఖాళీ, 0, ఖాళీ);
}

EMSCRIPTEN_KEEPALIVE శూన్య Emscripten_Handle_తాళం_కీలకాలు_Check(SDL_కిటికీ_దత్తాంశం *కిటికీ_దత్తాంశం_2, EM_BOOL capslock, EM_BOOL numlock, EM_BOOL scrolllock)
{
    స్థిరరాశి SDL_Keymod new_mods = (capslock ? SDL_KMOD_CAPS : 0) | (numlock ? SDL_KMOD_అంకె : 0) | (scrolllock ? SDL_KMOD_SCROLL : 0);
    SDL_Keymod modstate = SDL_GetModState();
    ఒకవేళ ((modstate & (SDL_KMOD_CAPS|SDL_KMOD_అంకె|SDL_KMOD_SCROLL)) != new_mods) {
        modstate &= ~(SDL_KMOD_CAPS|SDL_KMOD_అంకె|SDL_KMOD_SCROLL);
        modstate |= new_mods;
        SDL_సమితి_Mod_State(modstate);
    }
}

శూన్య Emscripten_రిజిస్టరు_Event_Handlers(SDL_కిటికీ_దత్తాంశం *దత్తాంశం)
{
    స్థిరరాశి అక్షరం *కీలకం_Element;

    // There is only one window and that window is the canvas
    emscripten_సమితి_wheel_callback(దత్తాంశం->canvas_id, దత్తాంశం, 0, Emscripten_HandleWheel);

    emscripten_సమితి_orientationchange_callback(దత్తాంశం, 0, Emscripten_HandleOrientationChange);

    కీలకం_Element = Emscripten_Get_Keyboard_లక్ష్యం_Element(దత్తాంశం->keyboard_element);
    ఒకవేళ (కీలకం_Element) {
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
        emscripten_సమితి_keydown_callback(కీలకం_Element, ఖాళీ, 0, ఖాళీ);
        emscripten_సమితి_keyup_callback(కీలకం_Element, ఖాళీ, 0, ఖాళీ);
        emscripten_సమితి_keypress_callback(కీలకం_Element, ఖాళీ, 0, ఖాళీ);

        MAIN_THREAD_EM_ASM_INT({
            var దత్తాంశం = $0;
            // our keymod state can get confused in various ways (changed capslock when browser didn't have focus, etc), and you can't query the current
            //  state from the DOM, outside of a keyboard event, so catch keypresses globally and reset mod state if it's unexpectedly wrong. Best we can do.
            //  Note that this thing _only_ adjusts the lock keys if necessary; the real SDL keypress handling happens elsewhere.

            // Remove any prior listener first -- `addEventListener` does not deduplicate either.
            ఒకవేళ (document.sdl_Event_Handler_తాళం_కీలకాలు_Check) {
                document.removeEventListener("keydown", document.sdl_Event_Handler_తాళం_కీలకాలు_Check);
            }

            document.sdl_Event_Handler_తాళం_కీలకాలు_Check = function(event) {
                // don't try to adjust the state on the actual lock key presses; the normal key handler will catch that and adjust.
                ఒకవేళ ((event.కీలకం != "CapsLock") && (event.కీలకం != "NumLock") && (event.కీలకం != "ScrollLock"))
                {
                    Emscripten_Handle_తాళం_కీలకాలు_Check_2(Module['SDL3'].JSVar_గమ్యం_CPtr(దత్తాంశం), event.getModifierState("CapsLock"), event.getModifierState("NumLock"), event.getModifierState("ScrollLock"));
                }
            };
            document.కూడు_Event_Listener("keydown", document.sdl_Event_Handler_తాళం_కీలకాలు_Check);
        }, దత్తాంశం);
        emscripten_సమితి_keydown_callback(కీలకం_Element, దత్తాంశం, 0, Emscripten_Handle_కీలకం);
        emscripten_సమితి_keyup_callback(కీలకం_Element, దత్తాంశం, 0, Emscripten_Handle_కీలకం);
        emscripten_సమితి_keypress_callback(కీలకం_Element, దత్తాంశం, 0, Emscripten_Handle_కీలకం_Press);
    }

    emscripten_సమితి_visibilitychange_callback(దత్తాంశం, 0, Emscripten_HandleVisibilityChange);

    emscripten_సమితి_beforeunload_callback(దత్తాంశం, Emscripten_HandleBeforeUnload);

    // !!! FIXME: currently Emscripten doesn't have a Pointer Events functions like emscripten_set_*_callback, but we should use those when they do:
    // !!! FIXME:  https://github.com/emscripten-core/emscripten/issues/7278#issuecomment-2280024621
    Emscripten_సమితి_సూచిక_event_callbacks(దత్తాంశం);

    // !!! FIXME: currently Emscripten doesn't have a Drop Events functions like emscripten_set_*_callback, but we should use those when they do:
    Emscripten_సమితి_drag_event_callbacks(దత్తాంశం);
}

శూన్య Emscripten_UnregisterEventHandlers(SDL_కిటికీ_దత్తాంశం *దత్తాంశం)
{
    స్థిరరాశి అక్షరం *కీలకం_Element;

    // !!! FIXME: currently Emscripten doesn't have a Drop Events functions like emscripten_set_*_callback, but we should use those when they do:
    Emscripten_unset_drag_event_callbacks(దత్తాంశం);

    // !!! FIXME: currently Emscripten doesn't have a Pointer Events functions like emscripten_set_*_callback, but we should use those when they do:
    // !!! FIXME:  https://github.com/emscripten-core/emscripten/issues/7278#issuecomment-2280024621
    Emscripten_unset_సూచిక_event_callbacks(దత్తాంశం);

    // only works due to having one window
    emscripten_సమితి_wheel_callback(దత్తాంశం->canvas_id, ఖాళీ, 0, ఖాళీ);

    emscripten_సమితి_orientationchange_callback(ఖాళీ, 0, ఖాళీ);

    కీలకం_Element = Emscripten_Get_Keyboard_లక్ష్యం_Element(దత్తాంశం->keyboard_element);
    ఒకవేళ (కీలకం_Element) {
        emscripten_సమితి_keydown_callback(కీలకం_Element, ఖాళీ, 0, ఖాళీ);
        emscripten_సమితి_keyup_callback(కీలకం_Element, ఖాళీ, 0, ఖాళీ);
        emscripten_సమితి_keypress_callback(కీలకం_Element, ఖాళీ, 0, ఖాళీ);
        MAIN_THREAD_EM_ASM_INT({
            document.removeEventListener("keydown", document.sdl_Event_Handler_తాళం_కీలకాలు_Check);
        });
    }

    emscripten_సమితి_visibilitychange_callback(ఖాళీ, 0, ఖాళీ);

    emscripten_సమితి_beforeunload_callback(ఖాళీ, ఖాళీ);
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_EMSCRIPTEN

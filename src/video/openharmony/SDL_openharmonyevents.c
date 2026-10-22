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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_OPENHARMONY

// !!! FIXME: these are defined as "const uint32_t VARNAME = VALUE;" in native_interface_xcomponent.h, which becomes a global variable in _our_ C code! Maybe C++ handles this differently...?
#ವ್ಯಾಖ್ಯಾನಿಸು OH_XCOMPONENT_ID_LEN_MAX sdl_ohosevents_OH_XCOMPONENT_ID_LEN_MAX
#ವ್ಯಾಖ್ಯಾನಿಸು OH_MAX_TOUCH_POINTS_ಸಂಖ್ಯೆ sdl_ohosevents_OH_MAX_TOUCH_POINTS_ಸಂಖ್ಯೆ
#ಅನ್ತರ್ಭಾವ <ace/xcomponent/native_interface_xcomponent.h>

#ಅನ್ತರ್ಭಾವ "SDL_openharmonyevents.h"
//#include "SDL_openharmonykeyboard.h"
#ಅನ್ತರ್ಭಾವ "SDL_openharmonywindow.h"
#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_events_c.h"

ಸ್ಥಿರ SDL_Scancode Map_OHKeycode_ಗಮ್ಯ_SDLScancode(ಸ್ಥಿರಾಂಕ OH_Native_XComponent_ಕೀಲಿ_ಸಂಕೇತ ohcode)
{
    // !!! FIXME: this needs a serious looking-over.
    ಆಯ್ಕೆ (ohcode) {
        #ವ್ಯಾಖ್ಯಾನಿಸು KEYMAP(oh,sdl) ಸ್ಥಿತಿ ಕೀಲಿ_2##oh: ಹಿಂತಿರುಗಿ SDL_SCANCODE_##sdl
        KEYMAP(UNKNOWN, UNKNOWN);
        //case KEY_FN = 0,
        KEYMAP(HOME, AC_HOME);
        KEYMAP(ಹಿಂಭಾಗ_2, AC_ಹಿಂಭಾಗ);
        KEYMAP(MEDIA_PLAY_PAUSE, MEDIA_PLAY_PAUSE);
        KEYMAP(MEDIA_STOP, MEDIA_STOP);
        KEYMAP(MEDIA_ಮುಂದಿನ, MEDIA_ಮುಂದಿನ_TRACK);
        KEYMAP(MEDIA_ಹಿಂದಿನ, MEDIA_ಹಿಂದಿನ_TRACK);
        KEYMAP(MEDIA_REWIND, MEDIA_REWIND);
        KEYMAP(MEDIA_FAST_FORWARD, MEDIA_FAST_FORWARD);
        KEYMAP(VOLUME_ಮೇಲೆ, VOLUMEUP);
        KEYMAP(VOLUME_ಕೆಳಕ್ಕೆ, VOLUMEDOWN);
        KEYMAP(POWER, POWER);
        //KEYMAP(CAMERA, CAMERA);
        KEYMAP(VOLUME_MUTE, MUTE);
        KEYMAP(MUTE, MUTE);
        //KEYMAP(BRIGHTNESS_UP = 40,
        //KEYMAP(BRIGHTNESS_DOWN = 41,
        KEYMAP(0, 0);
        KEYMAP(1, 1);
        KEYMAP(2, 2);
        KEYMAP(3, 3);
        KEYMAP(4, 4);
        KEYMAP(5, 5);
        KEYMAP(6, 6);
        KEYMAP(7, 7);
        KEYMAP(8, 8);
        KEYMAP(9, 9);
        //KEYMAP(STAR = 2010,
        //KEYMAP(POUND = 2011,
        KEYMAP(DPAD_ಮೇಲೆ, ಮೇಲೆ);
        KEYMAP(DPAD_ಕೆಳಕ್ಕೆ, ಕೆಳಕ್ಕೆ_2);
        KEYMAP(DPAD_ಎಡ, ಎಡ_2);
        KEYMAP(DPAD_ಬಲ, ಬಲ_2);
        //KEYMAP(DPAD_CENTER = 2016,
        KEYMAP(A, A);
        KEYMAP(B, B);
        KEYMAP(C, C);
        KEYMAP(D, D);
        KEYMAP(E, E);
        KEYMAP(F, F);
        KEYMAP(G, G);
        KEYMAP(H, H);
        KEYMAP(I, I);
        KEYMAP(J, J);
        KEYMAP(K, K);
        KEYMAP(L, L);
        KEYMAP(M, M);
        KEYMAP(N, N);
        KEYMAP(O, O);
        KEYMAP(P, P);
        KEYMAP(Q, Q);
        KEYMAP(R, R);
        KEYMAP(S, S);
        KEYMAP(T, T);
        KEYMAP(U, U);
        KEYMAP(V, V);
        KEYMAP(W, W);
        KEYMAP(X, X);
        KEYMAP(Y, Y);
        KEYMAP(Z, Z);
        KEYMAP(COMMA, COMMA);
        KEYMAP(PERIOD, PERIOD);
        KEYMAP(ALT_ಎಡ, LALT);
        KEYMAP(ALT_ಬಲ, RALT);
        KEYMAP(ಸರಿಸು_ಎಡ, LSHIFT);
        KEYMAP(ಸರಿಸು_ಬಲ, RSHIFT);
        KEYMAP(TAB, TAB);
        KEYMAP(SPACE, SPACE);
        //KEYMAP(SYM = 2051,
        //KEYMAP(EXPLORER = 2052,
        //KEYMAP(ENVELOPE = 2053,
        KEYMAP(ENTER, RETURN);
        KEYMAP(DEL, DELETE);
        KEYMAP(GRAVE, GRAVE);
        KEYMAP(MINUS, MINUS);
        KEYMAP(EQUALS, EQUALS);
        KEYMAP(ಎಡ_BRACKET, LEFTBRACKET);
        KEYMAP(ಬಲ_BRACKET, RIGHTBRACKET);
        KEYMAP(BACKSLASH, BACKSLASH);
        KEYMAP(SEMICOLON, SEMICOLON);
        KEYMAP(APOSTROPHE, APOSTROPHE);
        KEYMAP(SLASH, SLASH);
        KEYMAP(AT, KP_AT);
        KEYMAP(PLUS, KP_PLUS);
        KEYMAP(MENU, MENU);
        KEYMAP(ಪುಟ_ಮೇಲೆ, PAGEUP);
        KEYMAP(ಪುಟ_ಕೆಳಕ್ಕೆ, PAGEDOWN);
        KEYMAP(ESCAPE, ESCAPE);
        //KEYMAP(FORWARD_DEL = 2071,
        KEYMAP(CTRL_ಎಡ, LCTRL);
        KEYMAP(CTRL_ಬಲ, RCTRL);
        KEYMAP(CAPS_ಬೀಗ, CAPSLOCK);
        KEYMAP(SCROLL_ಬೀಗ, SCROLLLOCK);
        KEYMAP(META_ಎಡ, LGUI);
        KEYMAP(META_ಬಲ, RGUI);
        //KEYMAP(FUNCTION = 2078,
        KEYMAP(SYSRQ, SYSREQ);
        //KEYMAP(BREAK = 2080,
        KEYMAP(MOVE_HOME, HOME);
        KEYMAP(MOVE_ಕೊನೆ, ಕೊನೆ_3);
        KEYMAP(ಸೇರಿಸು_2, ಸೇರಿಸು_2);
        KEYMAP(FORWARD, AC_FORWARD);
        KEYMAP(MEDIA_PLAY, MEDIA_PLAY);
        KEYMAP(MEDIA_PAUSE, MEDIA_PAUSE);
        //KEYMAP(MEDIA_CLOSE = 2087,
        KEYMAP(MEDIA_EJECT, MEDIA_EJECT);
        KEYMAP(MEDIA_ದಾಖಲೆ, MEDIA_ದಾಖಲೆ);
        KEYMAP(F1, F1);
        KEYMAP(F2, F2);
        KEYMAP(F3, F3);
        KEYMAP(F4, F4);
        KEYMAP(F5, F5);
        KEYMAP(F6, F6);
        KEYMAP(F7, F7);
        KEYMAP(F8, F8);
        KEYMAP(F9, F9);
        KEYMAP(F10, F10);
        KEYMAP(F11, F11);
        KEYMAP(F12, F12);
        KEYMAP(ಅಂಕೆ_ಬೀಗ, NUMLOCKCLEAR);
        KEYMAP(NUMPAD_0, KP_0);
        KEYMAP(NUMPAD_1, KP_1);
        KEYMAP(NUMPAD_2, KP_2);
        KEYMAP(NUMPAD_3, KP_3);
        KEYMAP(NUMPAD_4, KP_4);
        KEYMAP(NUMPAD_5, KP_5);
        KEYMAP(NUMPAD_6, KP_6);
        KEYMAP(NUMPAD_7, KP_7);
        KEYMAP(NUMPAD_8, KP_8);
        KEYMAP(NUMPAD_9, KP_9);
        KEYMAP(NUMPAD_DIVIDE, KP_DIVIDE);
        KEYMAP(NUMPAD_MULTIPLY, KP_MULTIPLY);
        KEYMAP(NUMPAD_ಕಳೆ, KP_MINUS);
        KEYMAP(NUMPAD_ಕೂಡಿಸು, KP_PLUS);
        KEYMAP(NUMPAD_DOT, KP_PERIOD);
        //KEYMAP(NUMPAD_COMMA = 2118,
        KEYMAP(NUMPAD_ENTER, KP_ENTER);
        //KEYMAP(NUMPAD_EQUALS = 2120,
        KEYMAP(NUMPAD_ಎಡ_PAREN, KP_LEFTPAREN);
        KEYMAP(NUMPAD_ಬಲ_PAREN, KP_RIGHTPAREN);
        //KEYMAP(VIRTUAL_MULTITASK = 2210,
        KEYMAP(SLEEP, SLEEP);
        KEYMAP(ZENKAKU_HANKAKU, LANG5);
        //KEYMAP(102ND = 2602,
        //KEYMAP(RO = 2603,
        KEYMAP(KATAKANA, LANG3);
        KEYMAP(HIRAGANA, LANG4);
        //KEYMAP(HENKAN = 2606,
        //KEYMAP(KATAKANA_HIRAGANA = 2607,
        //KEYMAP(MUHENKAN = 2608,
        //KEYMAP(LINEFEED = 2609,
        //KEYMAP(MACRO = 2610,
        KEYMAP(NUMPAD_PLUSMINUS, KP_PLUSMINUS);
        //KEYMAP(SCALE = 2612,
        //KEYMAP(HANGUEL = 2613,
        //KEYMAP(HANJA = 2614,
        //KEYMAP(YEN = 2615,
        KEYMAP(STOP, STOP);
        KEYMAP(AGAIN, AGAIN);
        KEYMAP(PROPS, AC_PROPERTIES);  // I think....?
        KEYMAP(UNDO, UNDO);
        KEYMAP(COPY, COPY);
        KEYMAP(OPEN, AC_OPEN);  /// I think...?
        KEYMAP(PASTE, PASTE);
        KEYMAP(ಕಂಡುಹಿಡಿ, ಕಂಡುಹಿಡಿ);
        KEYMAP(CUT, CUT);
        KEYMAP(HELP, HELP);
        //KEYMAP(CALC = 2626,
        //KEYMAP(FILE = 2627,
        KEYMAP(BOOKMARKS, AC_BOOKMARKS);
        KEYMAP(ಮುಂದಿನ_2, MEDIA_ಮುಂದಿನ_TRACK);
        KEYMAP(PLAYPAUSE, MEDIA_PLAY_PAUSE);
        KEYMAP(ಹಿಂದಿನ, MEDIA_ಹಿಂದಿನ_TRACK);
        KEYMAP(STOPCD, MEDIA_STOP);
        //KEYMAP(CONFIG = 2634,
        KEYMAP(REFRESH, AC_REFRESH);
        KEYMAP(EXIT, AC_EXIT);
        //KEYMAP(EDIT = 2637,
        //KEYMAP(SCROLLUP = 2638,
        //KEYMAP(SCROLLDOWN = 2639,
        KEYMAP(NEW, AC_NEW);
        KEYMAP(REDO, AGAIN);
        KEYMAP(CLOSE, AC_CLOSE);
        KEYMAP(PLAY, MEDIA_PLAY);
        //KEYMAP(BASSBOOST = 2644,
        KEYMAP(PRINT, PRINTSCREEN);
        //KEYMAP(CHAT = 2646,
        //KEYMAP(FINANCE = 2647,
        KEYMAP(CANCEL, CANCEL);
        //KEYMAP(KBDILLUM_TOGGLE = 2649,
        //KEYMAP(KBDILLUM_DOWN = 2650,
        //KEYMAP(KBDILLUM_UP = 2651,
        //KEYMAP(SEND = 2652,
        //KEYMAP(REPLY = 2653,
        //KEYMAP(FORWARDMAIL = 2654,
        KEYMAP(SAVE, AC_SAVE);
        //KEYMAP(DOCUMENTS = 2656,
        //KEYMAP(VIDEO_NEXT = 2657,
        //KEYMAP(VIDEO_PREV = 2658,
        //KEYMAP(BRIGHTNESS_CYCLE = 2659,
        //KEYMAP(BRIGHTNESS_ZERO = 2660,
        //KEYMAP(DISPLAY_OFF = 2661,
        //KEYMAP(BTN_MISC = 2662,
        //KEYMAP(GOTO = 2663,
        //KEYMAP(INFO = 2664,
        //KEYMAP(PROGRAM = 2665,
        //KEYMAP(PVR = 2666,
        //KEYMAP(SUBTITLE = 2667,
        //KEYMAP(FULL_SCREEN = 2668,
        //KEYMAP(KEYBOARD = 2669,
        //KEYMAP(ASPECT_RATIO = 2670,
        //KEYMAP(PC = 2671,
        //KEYMAP(TV = 2672,
        //KEYMAP(TV2 = 2673,
        //KEYMAP(VCR = 2674,
        //KEYMAP(VCR2 = 2675,
        //KEYMAP(SAT = 2676,
        //KEYMAP(CD = 2677,
        //KEYMAP(TAPE = 2678,
        //KEYMAP(TUNER = 2679,
        //KEYMAP(PLAYER = 2680,
        //KEYMAP(DVD = 2681,
        //KEYMAP(AUDIO = 2682,
        //KEYMAP(VIDEO = 2683,
        //KEYMAP(MEMO = 2684,
        //KEYMAP(CALENDAR = 2685,
        //KEYMAP(RED = 2686,
        //KEYMAP(GREEN = 2687,
        //KEYMAP(YELLOW = 2688,
        //KEYMAP(BLUE = 2689,
        //KEYMAP(CHANNELUP = 2690,
        //KEYMAP(CHANNELDOWN = 2691,
        //KEYMAP(LAST = 2692,
        //KEYMAP(RESTART = 2693,
        //KEYMAP(SLOW = 2694,
        //KEYMAP(SHUFFLE = 2695,
        //KEYMAP(VIDEOPHONE = 2696,
        //KEYMAP(GAMES = 2697,
        //KEYMAP(ZOOMIN = 2698,
        //KEYMAP(ZOOMOUT = 2699,
        //KEYMAP(ZOOMRESET = 2700,
        //KEYMAP(WORDPROCESSOR = 2701,
        //KEYMAP(EDITOR = 2702,
        //KEYMAP(SPREADSHEET = 2703,
        //KEYMAP(GRAPHICSEDITOR = 2704,
        //KEYMAP(PRESENTATION = 2705,
        //KEYMAP(DATABASE = 2706,
        //KEYMAP(NEWS = 2707,
        //KEYMAP(VOICEMAIL = 2708,
        //KEYMAP(ADDRESSBOOK = 2709,
        //KEYMAP(MESSENGER = 2710,
        //KEYMAP(BRIGHTNESS_TOGGLE = 2711,
        //KEYMAP(SPELLCHECK = 2712,
        //KEYMAP(COFFEE = 2713,
        //KEYMAP(MEDIA_REPEAT = 2714,
        //KEYMAP(IMAGES = 2715,
        //KEYMAP(BUTTONCONFIG = 2716,
        //KEYMAP(TASKMANAGER = 2717,
        //KEYMAP(JOURNAL = 2718,
        //KEYMAP(CONTROLPANEL = 2719,
        //KEYMAP(APPSELECT = 2720,
        //KEYMAP(SCREENSAVER = 2721,
        //KEYMAP(ASSISTANT = 2722,
        //KEYMAP(KBD_LAYOUT_NEXT = 2723,
        //KEYMAP(BRIGHTNESS_MIN = 2724,
        //KEYMAP(BRIGHTNESS_MAX = 2725,
        //KEYMAP(KBDINPUTASSIST_PREV = 2726,
        //KEYMAP(KBDINPUTASSIST_NEXT = 2727,
        //KEYMAP(KBDINPUTASSIST_PREVGROUP = 2728,
        //KEYMAP(KBDINPUTASSIST_NEXTGROUP = 2729,
        //KEYMAP(KBDINPUTASSIST_ACCEPT = 2730,
        //KEYMAP(KBDINPUTASSIST_CANCEL = 2731,
        //KEYMAP(FRONT = 2800,
        //KEYMAP(SETUP = 2801,
        //KEYMAP(WAKEUP = 2802,
        //KEYMAP(SENDFILE = 2803,
        //KEYMAP(DELETEFILE = 2804,
        //KEYMAP(XFER = 2805,
        //KEYMAP(PROG1 = 2806,
        //KEYMAP(PROG2 = 2807,
        //KEYMAP(MSDOS = 2808,
        //KEYMAP(SCREENLOCK = 2809,
        //KEYMAP(DIRECTION_ROTATE_DISPLAY = 2810,
        //KEYMAP(CYCLEWINDOWS = 2811,
        //KEYMAP(COMPUTER = 2812,
        //KEYMAP(EJECTCLOSECD = 2813,
        //KEYMAP(ISO = 2814,
        //KEYMAP(MOVE = 2815,
        KEYMAP(F13, F13);
        KEYMAP(F14, F14);
        KEYMAP(F15, F15);
        KEYMAP(F16, F16);
        KEYMAP(F17, F17);
        KEYMAP(F18, F18);
        KEYMAP(F19, F19);
        KEYMAP(F20, F20);
        KEYMAP(F21, F21);
        KEYMAP(F22, F22);
        KEYMAP(F23, F23);
        KEYMAP(F24, F24);
        //KEYMAP(PROG3 = 2828,
        //KEYMAP(PROG4 = 2829,
        //KEYMAP(DASHBOARD = 2830,
        //KEYMAP(SUSPEND = 2831,
        //KEYMAP(HP = 2832,
        //KEYMAP(SOUND = 2833,
        //KEYMAP(QUESTION = 2834,
        //KEYMAP(CONNECT = 2836,
        //KEYMAP(SPORT = 2837,
        //KEYMAP(SHOP = 2838,
        //KEYMAP(ALTERASE = 2839,
        //KEYMAP(SWITCHVIDEOMODE = 2841,
        //KEYMAP(BATTERY = 2842,
        //KEYMAP(BLUETOOTH = 2843,
        //KEYMAP(WLAN = 2844,
        //KEYMAP(UWB = 2845,
        //KEYMAP(WWAN_WIMAX = 2846,
        //KEYMAP(RFKILL = 2847,
        //KEYMAP(CHANNEL = 3001,
        //KEYMAP(BTN_0 = 3100,
        //KEYMAP(BTN_1 = 3101,
        //KEYMAP(BTN_2 = 3102,
        //KEYMAP(BTN_3 = 3103,
        //KEYMAP(BTN_4 = 3104,
        //KEYMAP(BTN_5 = 3105,
        //KEYMAP(BTN_6 = 3106,
        //KEYMAP(BTN_7 = 3107,
        //KEYMAP(BTN_8 = 3108,
        //KEYMAP(BTN_9 = 3109,
        #ವ್ಯಾಖ್ಯಾನ_ರದ್ದು KEYMAP
        ಪೂರ್ವನಿಯೋಜಿತ: ನಿಲ್ಲಿಸು;
    }

    ಹಿಂತಿರುಗಿ SDL_SCANCODE_UNKNOWN;
}

ಶೂನ್ಯ SDL_OpenHarmonyDispatchTouchEvent(ಶೂನ್ಯ *component, ಶೂನ್ಯ *ಕಿಟಕಿ)
{
    OH_NativeXComponent *xcomponent = (OH_NativeXComponent *) component;
    OH_NativeXComponent_TouchEvent event;
    ಆದರೆ (OH_NativeXComponent_GetTouchEvent(xcomponent, ಕಿಟಕಿ, &event) != OH_NATIVEXCOMPONENT_ಫಲಿತಾಂಶ_SUCCESS) {
        ಹಿಂತಿರುಗಿ;  // oh well.
    }

#ಆದರೆ 0
    SDL_Log("TOUCH EVENT! id=%d screenX=%f screenY=%f x=%f y=%f type=%d size=%f force=%f devid=%lld timestamp=%lld numpoints=%d", (ಪೂರ್ಣಾಂಕ) event.id, event.screenX, event.screenY, event.x, event.y, (ಪೂರ್ಣಾಂಕ) event.type, (ದಶಮಾಂಶ) event.ಗಾತ್ರ_2, event.force, (ದೀರ್ಘ ದೀರ್ಘ) event.deviceId, (ದೀರ್ಘ ದೀರ್ಘ) event.ಸಮಯ_Stamp, (ಪೂರ್ಣಾಂಕ) event.ಅಂಕೆ_Points);
    ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i < event.ಅಂಕೆ_Points; i++) {
        SDL_Log("TOUCH POINT #%d: id=%d screenX=%f screenY=%f x=%f y=%f type=%d size=%f force=%f timestamp=%lld ispressed=%s", i, (ಪೂರ್ಣಾಂಕ) event.touchPoints[i].id, event.touchPoints[i].screenX, event.touchPoints[i].screenY, event.touchPoints[i].x, event.touchPoints[i].y, (ಪೂರ್ಣಾಂಕ) event.touchPoints[i].type, (ದಶಮಾಂಶ) event.touchPoints[i].ಗಾತ್ರ_2, event.touchPoints[i].force, (ದೀರ್ಘ ದೀರ್ಘ) event.touchPoints[i].ಸಮಯ_Stamp, event.touchPoints[i].isPressed ? "true" : "false");
    }
#ಆದರೆ_ಅಂತ್ಯ

    SDL_EventType sdleventtype = SDL_EVENT_ಮೊದಲ;
    ಆಯ್ಕೆ (event.type) {
        #ವ್ಯಾಖ್ಯಾನಿಸು EVTYPEMAP(ohevent, sdlevent) ಸ್ಥಿತಿ OH_NATIVEXCOMPONENT_##ohevent: sdleventtype = SDL_EVENT_FINGER_##sdlevent; ನಿಲ್ಲಿಸು
        EVTYPEMAP(ಕೆಳಕ್ಕೆ_2, ಕೆಳಕ್ಕೆ_2);
        EVTYPEMAP(ಮೇಲೆ, ಮೇಲೆ);
        EVTYPEMAP(MOVE, MOTION);
        EVTYPEMAP(CANCEL, CANCELED);
        ಪೂರ್ವನಿಯೋಜಿತ: ನಿಲ್ಲಿಸು;
        #ವ್ಯಾಖ್ಯಾನ_ರದ್ದು EVTYPEMAP
    }

    ಆದರೆ (sdleventtype == SDL_EVENT_ಮೊದಲ) {  // FIRST == unknown event type.
        ಹಿಂತಿರುಗಿ;  // nothing to do.
    }

    ಪೂರ್ಣಾಂಕ touchidx = 0;
    ಆಗ (touchidx < event.ಅಂಕೆ_Points) {
        ಆದರೆ (event.touchPoints[touchidx].id == event.id) {
            ನಿಲ್ಲಿಸು;
        }
        touchidx++;
    }

    ಆದರೆ (touchidx >= event.ಅಂಕೆ_Points) {
        ಹಿಂತಿರುಗಿ;  // uh...we don't have this touch...?
    }

    OH_Native_XComponent_Touch_ಬಿಂದು_Tool_Type tooltype;
    ಆದರೆ (OH_Native_XComponent_Get_Touch_ಬಿಂದು_Tool_Type(xcomponent, touchidx, &tooltype) != OH_NATIVEXCOMPONENT_ಫಲಿತಾಂಶ_SUCCESS) {
        ಹಿಂತಿರುಗಿ;   // bad bad bad
    }

    ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ normalized_x = OPENHARMONY_ಕಿಟಕಿ->w ? (event.x / ((ದಶಮಾಂಶ) OPENHARMONY_ಕಿಟಕಿ->w)) : 0.0f;
    ಸ್ಥಿರಾಂಕ ದಶಮಾಂಶ normalized_y = OPENHARMONY_ಕಿಟಕಿ->h ? (event.y / ((ದಶಮಾಂಶ) OPENHARMONY_ಕಿಟಕಿ->h)) : 0.0f;

    ಆದರೆ (tooltype == OH_NATIVEXCOMPONENT_TOOL_TYPE_FINGER) {
        ಸ್ಥಿರಾಂಕ SDL_TouchID touchid = (SDL_TouchID)(((uintptr_t)event.deviceId) + 1);
        SDL_ಕೂಡಿಸು_Touch(touchid, SDL_TOUCH_DEVICE_ನೇರ, ಖಾಲಿ);
        ಆದರೆ (sdleventtype == SDL_EVENT_FINGER_MOTION) {
            SDL_SendTouchMotion((Uint64) event.ಸಮಯ_Stamp, touchid, (SDL_FingerID)(((uintptr_t)event.id)+1), OPENHARMONY_ಕಿಟಕಿ, normalized_x, normalized_y, event.force);
        } ಇಲ್ಲದಿದ್ದರೆ {
            SDL_SendTouch((Uint64) event.ಸಮಯ_Stamp, touchid, (SDL_FingerID)(((uintptr_t)event.id)+1), OPENHARMONY_ಕಿಟಕಿ, sdleventtype, normalized_x, normalized_y, event.force);
        }
        ಹಿಂತಿರುಗಿ;
    }

#ಆದರೆ 0  // !!! FIXME: see if Pen events are useful here.
    ಆಯ್ಕೆ (tooltype) {
    /** Indicates invalid tool type. */
    OH_NATIVEXCOMPONENT_TOOL_TYPE_UNKNOWN = 0,
    /** Indicates a finger. */
    OH_NATIVEXCOMPONENT_TOOL_TYPE_FINGER,
    /** Indicates a stylus. */
    OH_NATIVEXCOMPONENT_TOOL_TYPE_PEN,
    /** Indicates an eraser. */
    OH_NATIVEXCOMPONENT_TOOL_TYPE_RUBBER,
    /** Indicates a brush. */
    OH_NATIVEXCOMPONENT_TOOL_TYPE_BRUSH,
    /** Indicates a pencil. */
    OH_NATIVEXCOMPONENT_TOOL_TYPE_PENCIL,
    /** Indicates a brush. */
    OH_NATIVEXCOMPONENT_TOOL_TYPE_AIRBRUSH,
    /** Indicates a mouse. */
    OH_NATIVEXCOMPONENT_TOOL_TYPE_MOUSE,
    /** Indicates a lens. */
    OH_NATIVEXCOMPONENT_TOOL_TYPE_LENS,
    }
#ಆದರೆ_ಅಂತ್ಯ
}

ಶೂನ್ಯ SDL_OpenHarmonyDispatchMouseEvent(ಶೂನ್ಯ *component, ಶೂನ್ಯ *ಕಿಟಕಿ)
{
    OH_NativeXComponent *xcomponent = (OH_NativeXComponent *) component;
    OH_NativeXComponent_MouseEvent event;
    ಆದರೆ (OH_NativeXComponent_GetMouseEvent(xcomponent, ಕಿಟಕಿ, &event) != OH_NATIVEXCOMPONENT_ಫಲಿತಾಂಶ_SUCCESS) {
        ಹಿಂತಿರುಗಿ;  // oh well.
    }

#ಆದರೆ 1
    SDL_Log("MOUSE EVENT! screenX=%f screenY=%f x=%f y=%f timestamp=%lld action=%d button=0x%X", event.screenX, event.screenY, event.x, event.y, (ದೀರ್ಘ ದೀರ್ಘ) event.timestamp, (ಪೂರ್ಣಾಂಕ) event.action, (ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ) event.button);
#ಆದರೆ_ಅಂತ್ಯ

    ಸ್ಥಿರಾಂಕ SDL_MouseID mouseid = SDL_DEFAULT_MOUSE_ID;  // !!! FIXME: should this be SDL_GLOBAL_MOUSE_ID or SDL_DEFAULT_MOUSE_ID?
    bool ಕೆಳಕ್ಕೆ = false;
    ಆಯ್ಕೆ (event.action) {
        ಸ್ಥಿತಿ OH_NATIVEXCOMPONENT_MOUSE_PRESS:
            ಕೆಳಕ್ಕೆ = true;
            SDL_FALLTHROUGH;
        ಸ್ಥಿತಿ OH_NATIVEXCOMPONENT_MOUSE_RELEASE:
            // these are bitmasks, so while I _assume_ you won't see more than one button per event, check them all separately, just in case.
            #ವ್ಯಾಖ್ಯಾನಿಸು CHECK_BUTTON(ohos, sdl) ಆದರೆ (event.button & OH_NATIVEXCOMPONENT_##ohos##_BUTTON) { SDL_SendMouseButton((Uint64) event.timestamp, OPENHARMONY_ಕಿಟಕಿ, mouseid, SDL_BUTTON_##sdl, ಕೆಳಕ್ಕೆ); }
            CHECK_BUTTON(ಎಡ_2, ಎಡ_2);
            CHECK_BUTTON(ಬಲ_2, ಬಲ_2);
            CHECK_BUTTON(ಮಧ್ಯ_2, ಮಧ್ಯ_2);
            CHECK_BUTTON(ಹಿಂಭಾಗ_2, X1);
            CHECK_BUTTON(FORWARD, X2);
            #ವ್ಯಾಖ್ಯಾನ_ರದ್ದು CHECK_BUTTON
            ನಿಲ್ಲಿಸು;

        ಸ್ಥಿತಿ OH_NATIVEXCOMPONENT_MOUSE_MOVE:
            SDL_SendMouseMotion((Uint64) event.timestamp, OPENHARMONY_ಕಿಟಕಿ, mouseid, false, event.x, event.y);
            ನಿಲ್ಲಿಸು;

        ಪೂರ್ವನಿಯೋಜಿತ: ನಿಲ್ಲಿಸು;  // nothing to do?
    }
}

ಶೂನ್ಯ SDL_OpenHarmonyDispatchUIInputEvent(ಶೂನ್ಯ *vcomponent, ಶೂನ್ಯ *vevent, int32_t vtype)
{
//    OH_NativeXComponent *component = (OH_NativeXComponent *) vcomponent;
    ArkUI_UIInputEvent *event = (ArkUI_UIInputEvent *) vevent;
    ಸ್ಥಿರಾಂಕ ArkUI_UIInputEvent_Type type = (ಸ್ಥಿರಾಂಕ ArkUI_UIInputEvent_Type) vtype;

    ಆದರೆ (type != ARKUI_UIINPUTEVENT_TYPE_AXIS) {
        ಹಿಂತಿರುಗಿ;  // this is all we handle here for now. Maybe more in the future!
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (OH_Ark_UI_UIInput_Event_Get_ಮೂಲ_Type(event) != UI_ಒಳಹರಿವು_EVENT_ಮೂಲ_TYPE_MOUSE) {
        ಹಿಂತಿರುಗಿ;  // skip two-finger scrolling (...for now...?)
    }

    ಸ್ಥಿರಾಂಕ SDL_MouseID mouseid = SDL_DEFAULT_MOUSE_ID;  // !!! FIXME: should this be SDL_GLOBAL_MOUSE_ID or SDL_DEFAULT_MOUSE_ID?
    ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ vertical = OH_Ark_UI_Axis_Event_Get_Vertical_Axis_ಮೌಲ್ಯ(event);
    ಆದರೆ (vertical != 0.0) {
        // !!! FIXME: OpenHarmony has a system setting for "natural" scrolling we can use for SDL_MouseWheelDirection, but I
        // !!! FIXME: don't know how to access it right now.
        // a single "click" of the wheel on my mouse is 45 degrees (360 / 8 click positions), so let's assume that's normal (and what Windows would do with WHEEL_DELTA, which is a different value with the same concept).
        SDL_SendMouseWheel((Uint64) OH_Ark_UI_UIInput_Event_Get_Event_ಸಮಯ(event), OPENHARMONY_ಕಿಟಕಿ, mouseid, 0.0f, -(vertical / 45.0f), SDL_MOUSEWHEEL_ಸಾಮಾನ್ಯ);
    }

    // !!! FIXME: this is in pixels, not degrees, and I'm not sure how to convert that yet.
    // !!! FIXME: It's possible they don't support horizontal mouse wheels, and this is only for two-finger scrolling.
    #ಆದರೆ 0
    ಸ್ಥಿರಾಂಕ ದ್ವಿಗುಣ horizontal = OH_Ark_UI_Axis_Event_Get_Horizontal_Axis_ಮೌಲ್ಯ(event);
    ಆದರೆ (horizontal != 0.0) {
    }
    #ಆದರೆ_ಅಂತ್ಯ
}

ಶೂನ್ಯ SDL_Open_Harmony_Dispatch_ಕೀಲಿ_Event(ಶೂನ್ಯ *component, ಶೂನ್ಯ *ಕಿಟಕಿ)
{
    OH_NativeXComponent *xcomponent = (OH_NativeXComponent *) component;
    OH_Native_XComponent_ಕೀಲಿ_Event *event = ಖಾಲಿ;
    ಆದರೆ (OH_Native_XComponent_Get_ಕೀಲಿ_Event(xcomponent, &event) != OH_NATIVEXCOMPONENT_ಫಲಿತಾಂಶ_SUCCESS) {
        ಹಿಂತಿರುಗಿ;  // oh well.
    }

    OH_Native_XComponent_ಕೀಲಿ_ಸಂಕೇತ keycode = ಕೀಲಿ_UNKNOWN;
    OH_Native_XComponent_Get_ಕೀಲಿ_Event_ಸಂಕೇತ(event, &keycode);
    ಸ್ಥಿರಾಂಕ SDL_Scancode scancode = Map_OHKeycode_ಗಮ್ಯ_SDLScancode(keycode);
    ಆದರೆ (scancode == SDL_SCANCODE_UNKNOWN) {
        ಹಿಂತಿರುಗಿ;  // oh well.
    }

    OH_Native_XComponent_ಕೀಲಿ_Action action = OH_NATIVEXCOMPONENT_ಕೀಲಿ_ACTION_UNKNOWN;
    OH_Native_XComponent_Get_ಕೀಲಿ_Event_Action(event, &action);
    bool ಕೆಳಕ್ಕೆ;
    ಆದರೆ (action == OH_NATIVEXCOMPONENT_ಕೀಲಿ_ACTION_ಕೆಳಕ್ಕೆ) {
        ಕೆಳಕ್ಕೆ = true;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (action == OH_NATIVEXCOMPONENT_ಕೀಲಿ_ACTION_ಮೇಲೆ) {
        ಕೆಳಕ್ಕೆ = false;
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಹಿಂತಿರುಗಿ;  // oh well.
    }

    int64_t timestamp = 0;
    OH_Native_XComponent_Get_ಕೀಲಿ_Event_Timestamp(event, &timestamp);

    SDL_Send_Keyboard_ಕೀಲಿ((Uint64) timestamp, SDL_DEFAULT_KEYBOARD_ID, keycode, scancode, ಕೆಳಕ್ಕೆ);
}

ಶೂನ್ಯ OPENHARMONY_InitEvents(ಶೂನ್ಯ)
{
}

ಶೂನ್ಯ OPENHARMONY_PumpEvents(SDL_VideoDevice *_this)
{
}

ಶೂನ್ಯ OPENHARMONY_QuitEvents(ಶೂನ್ಯ)
{
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_OPENHARMONY

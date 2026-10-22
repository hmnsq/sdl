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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_OPENHARMONY

// !!! FIXME: these are defined as "const uint32_t VARNAME = VALUE;" in native_interface_xcomponent.h, which becomes a global variable in _our_ C code! Maybe C++ handles this differently...?
#تعریف_کن OH_XCOMPONENT_ID_LEN_MAX sdl_ohosevents_OH_XCOMPONENT_ID_LEN_MAX
#تعریف_کن OH_MAX_TOUCH_POINTS_عدد sdl_ohosevents_OH_MAX_TOUCH_POINTS_عدد
#ضمن <ace/xcomponent/native_interface_xcomponent.h>

#ضمن "SDL_openharmonyevents.h"
//#include "SDL_openharmonykeyboard.h"
#ضمن "SDL_openharmonywindow.h"
#ضمن "../SDL_sysvideo.h"
#ضمن "../../events/SDL_events_c.h"

ساكن SDL_Scancode Map_OHKeycode_مقصد_SDLScancode(ثابت OH_Native_XComponent_کلید_کد ohcode)
{
    // !!! FIXME: this needs a serious looking-over.
    بدل (ohcode) {
        #تعریف_کن KEYMAP(oh,sdl) حالة کلید_2##oh: أرجع SDL_SCANCODE_##sdl
        KEYMAP(UNKNOWN, UNKNOWN);
        //case KEY_FN = 0,
        KEYMAP(HOME, AC_HOME);
        KEYMAP(پشت_2, AC_پشت);
        KEYMAP(MEDIA_PLAY_PAUSE, MEDIA_PLAY_PAUSE);
        KEYMAP(MEDIA_STOP, MEDIA_STOP);
        KEYMAP(MEDIA_بعدی, MEDIA_بعدی_TRACK);
        KEYMAP(MEDIA_قبلی, MEDIA_قبلی_TRACK);
        KEYMAP(MEDIA_REWIND, MEDIA_REWIND);
        KEYMAP(MEDIA_FAST_FORWARD, MEDIA_FAST_FORWARD);
        KEYMAP(VOLUME_به_بالا, VOLUMEUP);
        KEYMAP(VOLUME_پایین, VOLUMEDOWN);
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
        KEYMAP(DPAD_به_بالا, به_بالا);
        KEYMAP(DPAD_پایین, پایین_2);
        KEYMAP(DPAD_چپ, چپ_2);
        KEYMAP(DPAD_راست, راست_2);
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
        KEYMAP(ALT_چپ, LALT);
        KEYMAP(ALT_راست, RALT);
        KEYMAP(لغزش_چپ, LSHIFT);
        KEYMAP(لغزش_راست, RSHIFT);
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
        KEYMAP(چپ_BRACKET, LEFTBRACKET);
        KEYMAP(راست_BRACKET, RIGHTBRACKET);
        KEYMAP(BACKSLASH, BACKSLASH);
        KEYMAP(SEMICOLON, SEMICOLON);
        KEYMAP(APOSTROPHE, APOSTROPHE);
        KEYMAP(SLASH, SLASH);
        KEYMAP(AT, KP_AT);
        KEYMAP(PLUS, KP_PLUS);
        KEYMAP(MENU, MENU);
        KEYMAP(صفحه_به_بالا, PAGEUP);
        KEYMAP(صفحه_پایین, PAGEDOWN);
        KEYMAP(ESCAPE, ESCAPE);
        //KEYMAP(FORWARD_DEL = 2071,
        KEYMAP(CTRL_چپ, LCTRL);
        KEYMAP(CTRL_راست, RCTRL);
        KEYMAP(CAPS_قفل, CAPSLOCK);
        KEYMAP(SCROLL_قفل, SCROLLLOCK);
        KEYMAP(META_چپ, LGUI);
        KEYMAP(META_راست, RGUI);
        //KEYMAP(FUNCTION = 2078,
        KEYMAP(SYSRQ, SYSREQ);
        //KEYMAP(BREAK = 2080,
        KEYMAP(MOVE_HOME, HOME);
        KEYMAP(MOVE_انتها, انتها_3);
        KEYMAP(درج_2, درج_2);
        KEYMAP(FORWARD, AC_FORWARD);
        KEYMAP(MEDIA_PLAY, MEDIA_PLAY);
        KEYMAP(MEDIA_PAUSE, MEDIA_PAUSE);
        //KEYMAP(MEDIA_CLOSE = 2087,
        KEYMAP(MEDIA_EJECT, MEDIA_EJECT);
        KEYMAP(MEDIA_رکورد, MEDIA_رکورد);
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
        KEYMAP(رقم_قفل, NUMLOCKCLEAR);
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
        KEYMAP(NUMPAD_تفریق, KP_MINUS);
        KEYMAP(NUMPAD_جمع_کن, KP_PLUS);
        KEYMAP(NUMPAD_DOT, KP_PERIOD);
        //KEYMAP(NUMPAD_COMMA = 2118,
        KEYMAP(NUMPAD_ENTER, KP_ENTER);
        //KEYMAP(NUMPAD_EQUALS = 2120,
        KEYMAP(NUMPAD_چپ_PAREN, KP_LEFTPAREN);
        KEYMAP(NUMPAD_راست_PAREN, KP_RIGHTPAREN);
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
        KEYMAP(پیدا_کن, پیدا_کن);
        KEYMAP(CUT, CUT);
        KEYMAP(HELP, HELP);
        //KEYMAP(CALC = 2626,
        //KEYMAP(FILE = 2627,
        KEYMAP(BOOKMARKS, AC_BOOKMARKS);
        KEYMAP(بعدی_2, MEDIA_بعدی_TRACK);
        KEYMAP(PLAYPAUSE, MEDIA_PLAY_PAUSE);
        KEYMAP(قبلی, MEDIA_قبلی_TRACK);
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
        #لغو_تعریف KEYMAP
        افتراضي: اكسر;
    }

    أرجع SDL_SCANCODE_UNKNOWN;
}

فراغ SDL_OpenHarmonyDispatchTouchEvent(فراغ *component, فراغ *پنجره)
{
    OH_NativeXComponent *xcomponent = (OH_NativeXComponent *) component;
    OH_NativeXComponent_TouchEvent event;
    إذا (OH_NativeXComponent_GetTouchEvent(xcomponent, پنجره, &event) != OH_NATIVEXCOMPONENT_نتیجه_SUCCESS) {
        أرجع;  // oh well.
    }

#إذا 0
    SDL_Log("TOUCH EVENT! id=%d screenX=%f screenY=%f x=%f y=%f type=%d size=%f force=%f devid=%lld timestamp=%lld numpoints=%d", (صحيح) event.id, event.screenX, event.screenY, event.x, event.y, (صحيح) event.type, (عائم) event.اندازه, event.force, (دراز دراز) event.deviceId, (دراز دراز) event.زمان_Stamp, (صحيح) event.رقم_Points);
    لكل (صحيح i = 0; i < event.رقم_Points; i++) {
        SDL_Log("TOUCH POINT #%d: id=%d screenX=%f screenY=%f x=%f y=%f type=%d size=%f force=%f timestamp=%lld ispressed=%s", i, (صحيح) event.touchPoints[i].id, event.touchPoints[i].screenX, event.touchPoints[i].screenY, event.touchPoints[i].x, event.touchPoints[i].y, (صحيح) event.touchPoints[i].type, (عائم) event.touchPoints[i].اندازه, event.touchPoints[i].force, (دراز دراز) event.touchPoints[i].زمان_Stamp, event.touchPoints[i].isPressed ? "true" : "false");
    }
#پایان_اگر

    SDL_EventType sdleventtype = SDL_EVENT_اولی;
    بدل (event.type) {
        #تعریف_کن EVTYPEMAP(ohevent, sdlevent) حالة OH_NATIVEXCOMPONENT_##ohevent: sdleventtype = SDL_EVENT_FINGER_##sdlevent; اكسر
        EVTYPEMAP(پایین_2, پایین_2);
        EVTYPEMAP(به_بالا, به_بالا);
        EVTYPEMAP(MOVE, MOTION);
        EVTYPEMAP(CANCEL, CANCELED);
        افتراضي: اكسر;
        #لغو_تعریف EVTYPEMAP
    }

    إذا (sdleventtype == SDL_EVENT_اولی) {  // FIRST == unknown event type.
        أرجع;  // nothing to do.
    }

    صحيح touchidx = 0;
    طالما (touchidx < event.رقم_Points) {
        إذا (event.touchPoints[touchidx].id == event.id) {
            اكسر;
        }
        touchidx++;
    }

    إذا (touchidx >= event.رقم_Points) {
        أرجع;  // uh...we don't have this touch...?
    }

    OH_Native_XComponent_Touch_نقطه_Tool_Type tooltype;
    إذا (OH_Native_XComponent_Get_Touch_نقطه_Tool_Type(xcomponent, touchidx, &tooltype) != OH_NATIVEXCOMPONENT_نتیجه_SUCCESS) {
        أرجع;   // bad bad bad
    }

    ثابت عائم normalized_x = OPENHARMONY_پنجره->w ? (event.x / ((عائم) OPENHARMONY_پنجره->w)) : 0.0f;
    ثابت عائم normalized_y = OPENHARMONY_پنجره->h ? (event.y / ((عائم) OPENHARMONY_پنجره->h)) : 0.0f;

    إذا (tooltype == OH_NATIVEXCOMPONENT_TOOL_TYPE_FINGER) {
        ثابت SDL_TouchID touchid = (SDL_TouchID)(((uintptr_t)event.deviceId) + 1);
        SDL_جمع_کن_Touch(touchid, SDL_TOUCH_DEVICE_مستقیم, عدم);
        إذا (sdleventtype == SDL_EVENT_FINGER_MOTION) {
            SDL_SendTouchMotion((Uint64) event.زمان_Stamp, touchid, (SDL_FingerID)(((uintptr_t)event.id)+1), OPENHARMONY_پنجره, normalized_x, normalized_y, event.force);
        } وإلا {
            SDL_SendTouch((Uint64) event.زمان_Stamp, touchid, (SDL_FingerID)(((uintptr_t)event.id)+1), OPENHARMONY_پنجره, sdleventtype, normalized_x, normalized_y, event.force);
        }
        أرجع;
    }

#إذا 0  // !!! FIXME: see if Pen events are useful here.
    بدل (tooltype) {
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
#پایان_اگر
}

فراغ SDL_OpenHarmonyDispatchMouseEvent(فراغ *component, فراغ *پنجره)
{
    OH_NativeXComponent *xcomponent = (OH_NativeXComponent *) component;
    OH_NativeXComponent_MouseEvent event;
    إذا (OH_NativeXComponent_GetMouseEvent(xcomponent, پنجره, &event) != OH_NATIVEXCOMPONENT_نتیجه_SUCCESS) {
        أرجع;  // oh well.
    }

#إذا 1
    SDL_Log("MOUSE EVENT! screenX=%f screenY=%f x=%f y=%f timestamp=%lld action=%d button=0x%X", event.screenX, event.screenY, event.x, event.y, (دراز دراز) event.timestamp, (صحيح) event.action, (بیعلامت صحيح) event.button);
#پایان_اگر

    ثابت SDL_MouseID mouseid = SDL_DEFAULT_MOUSE_ID;  // !!! FIXME: should this be SDL_GLOBAL_MOUSE_ID or SDL_DEFAULT_MOUSE_ID?
    bool پایین = false;
    بدل (event.action) {
        حالة OH_NATIVEXCOMPONENT_MOUSE_PRESS:
            پایین = true;
            SDL_FALLTHROUGH;
        حالة OH_NATIVEXCOMPONENT_MOUSE_RELEASE:
            // these are bitmasks, so while I _assume_ you won't see more than one button per event, check them all separately, just in case.
            #تعریف_کن CHECK_BUTTON(ohos, sdl) إذا (event.button & OH_NATIVEXCOMPONENT_##ohos##_BUTTON) { SDL_SendMouseButton((Uint64) event.timestamp, OPENHARMONY_پنجره, mouseid, SDL_BUTTON_##sdl, پایین); }
            CHECK_BUTTON(چپ_2, چپ_2);
            CHECK_BUTTON(راست_2, راست_2);
            CHECK_BUTTON(میانه_2, میانه_2);
            CHECK_BUTTON(پشت_2, X1);
            CHECK_BUTTON(FORWARD, X2);
            #لغو_تعریف CHECK_BUTTON
            اكسر;

        حالة OH_NATIVEXCOMPONENT_MOUSE_MOVE:
            SDL_SendMouseMotion((Uint64) event.timestamp, OPENHARMONY_پنجره, mouseid, false, event.x, event.y);
            اكسر;

        افتراضي: اكسر;  // nothing to do?
    }
}

فراغ SDL_OpenHarmonyDispatchUIInputEvent(فراغ *vcomponent, فراغ *vevent, int32_t vtype)
{
//    OH_NativeXComponent *component = (OH_NativeXComponent *) vcomponent;
    ArkUI_UIInputEvent *event = (ArkUI_UIInputEvent *) vevent;
    ثابت ArkUI_UIInputEvent_Type type = (ثابت ArkUI_UIInputEvent_Type) vtype;

    إذا (type != ARKUI_UIINPUTEVENT_TYPE_AXIS) {
        أرجع;  // this is all we handle here for now. Maybe more in the future!
    } وإلا إذا (OH_Ark_UI_UIInput_Event_Get_منبع_Type(event) != UI_درون_داد_EVENT_منبع_TYPE_MOUSE) {
        أرجع;  // skip two-finger scrolling (...for now...?)
    }

    ثابت SDL_MouseID mouseid = SDL_DEFAULT_MOUSE_ID;  // !!! FIXME: should this be SDL_GLOBAL_MOUSE_ID or SDL_DEFAULT_MOUSE_ID?
    ثابت مزدوج vertical = OH_Ark_UI_Axis_Event_Get_Vertical_Axis_مقدار(event);
    إذا (vertical != 0.0) {
        // !!! FIXME: OpenHarmony has a system setting for "natural" scrolling we can use for SDL_MouseWheelDirection, but I
        // !!! FIXME: don't know how to access it right now.
        // a single "click" of the wheel on my mouse is 45 degrees (360 / 8 click positions), so let's assume that's normal (and what Windows would do with WHEEL_DELTA, which is a different value with the same concept).
        SDL_SendMouseWheel((Uint64) OH_Ark_UI_UIInput_Event_Get_Event_زمان(event), OPENHARMONY_پنجره, mouseid, 0.0f, -(vertical / 45.0f), SDL_MOUSEWHEEL_نرمال);
    }

    // !!! FIXME: this is in pixels, not degrees, and I'm not sure how to convert that yet.
    // !!! FIXME: It's possible they don't support horizontal mouse wheels, and this is only for two-finger scrolling.
    #إذا 0
    ثابت مزدوج horizontal = OH_Ark_UI_Axis_Event_Get_Horizontal_Axis_مقدار(event);
    إذا (horizontal != 0.0) {
    }
    #پایان_اگر
}

فراغ SDL_Open_Harmony_Dispatch_کلید_Event(فراغ *component, فراغ *پنجره)
{
    OH_NativeXComponent *xcomponent = (OH_NativeXComponent *) component;
    OH_Native_XComponent_کلید_Event *event = عدم;
    إذا (OH_Native_XComponent_Get_کلید_Event(xcomponent, &event) != OH_NATIVEXCOMPONENT_نتیجه_SUCCESS) {
        أرجع;  // oh well.
    }

    OH_Native_XComponent_کلید_کد keycode = کلید_UNKNOWN;
    OH_Native_XComponent_Get_کلید_Event_کد(event, &keycode);
    ثابت SDL_Scancode scancode = Map_OHKeycode_مقصد_SDLScancode(keycode);
    إذا (scancode == SDL_SCANCODE_UNKNOWN) {
        أرجع;  // oh well.
    }

    OH_Native_XComponent_کلید_Action action = OH_NATIVEXCOMPONENT_کلید_ACTION_UNKNOWN;
    OH_Native_XComponent_Get_کلید_Event_Action(event, &action);
    bool پایین;
    إذا (action == OH_NATIVEXCOMPONENT_کلید_ACTION_پایین) {
        پایین = true;
    } وإلا إذا (action == OH_NATIVEXCOMPONENT_کلید_ACTION_به_بالا) {
        پایین = false;
    } وإلا {
        أرجع;  // oh well.
    }

    int64_t timestamp = 0;
    OH_Native_XComponent_Get_کلید_Event_Timestamp(event, &timestamp);

    SDL_Send_Keyboard_کلید((Uint64) timestamp, SDL_DEFAULT_KEYBOARD_ID, keycode, scancode, پایین);
}

فراغ OPENHARMONY_InitEvents(فراغ)
{
}

فراغ OPENHARMONY_PumpEvents(SDL_VideoDevice *_this)
{
}

فراغ OPENHARMONY_QuitEvents(فراغ)
{
}

#پایان_اگر // SDL_VIDEO_DRIVER_OPENHARMONY

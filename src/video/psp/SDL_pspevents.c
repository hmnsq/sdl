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

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_PSP

/* Being a null driver, there's no event stream. We just define stubs for
   most of the API. */

#شامل "../../events/SDL_events_c.h"
#شامل "../../events/SDL_keyboard_c.h"
#شامل "../SDL_sysvideo.h"
#شامل "SDL_pspvideo.h"
#شامل "SDL_pspevents_c.h"
#شامل "../../thread/SDL_systhread.h"
#شامل <psphprm.h>
#شامل <pspthreadman.h>

#اگر_تعریف_شدہ PSPIRKEYB
#شامل <pspirkeyb.h>
#شامل <pspirkeyb_rawkeys.h>

#تعریف_کرو IRKBD_CONFIG_FILE تہی // this will take ms0:/seplugins/pspirkeyb.ini

ساکن صحیح irkbd_ready = 0;
ساکن SDL_Scancode keymap[256];
#اگر_ختم

ساکن شمار Psp_Hprm_کلیدیں hprm = 0;
ساکن SDL_Semaphore *event_sem = تہی;
ساکن SDL_Thread *thread = تہی;
ساکن صحیح running = 0;
ساکن ساخت
{
    شمار Psp_Hprm_کلیدیں id;
    SDL_Scancode scancode;
} keymap_psp[] = {
    { PSP_HPRM_PLAYPAUSE, SDL_SCANCODE_F10 },
    { PSP_HPRM_FORWARD, SDL_SCANCODE_F11 },
    { PSP_HPRM_عقب, SDL_SCANCODE_F12 },
    { PSP_HPRM_VOL_اوپر, SDL_SCANCODE_F13 },
    { PSP_HPRM_VOL_نیچے_کو, SDL_SCANCODE_F14 },
    { PSP_HPRM_HOLD, SDL_SCANCODE_F15 }
};

صحیح EventUpdate(خالی *ڈیٹا)
{
    جب (running) {
        SDL_WaitSemaphore(event_sem);
        sce_Hprm_Peek_Current_کلید((u32 *)&hprm);
        SDL_SignalSemaphore(event_sem);
        // Delay 1/60th of a second
        sceKernelDelayThread(1000000 / 60);
    }
    واپس 0;
}

خالی PSP_PumpEvents(SDL_VideoDevice *_this)
{
    صحیح i;
    شمار Psp_Hprm_کلیدیں کلیدیں;
    شمار Psp_Hprm_کلیدیں بدلا;
    ساکن شمار Psp_Hprm_کلیدیں old_کلیدیں = 0;

    SDL_WaitSemaphore(event_sem);
    کلیدیں = hprm;
    SDL_SignalSemaphore(event_sem);

    // HPRM Keyboard
    بدلا = old_کلیدیں ^ کلیدیں;
    old_کلیدیں = کلیدیں;
    اگر (بدلا) {
        برائے (i = 0; i < SDL_arraysize(keymap_psp); i++) {
            اگر (بدلا & keymap_psp[i].id) {
                bool نیچے_کو = ((کلیدیں & keymap_psp[i].id) != 0);
                SDL_Send_Keyboard_کلید(0, SDL_GLOBAL_KEYBOARD_ID, keymap_psp[i].id, keymap_psp[i].scancode, نیچے_کو);
            }
        }
    }

#اگر_تعریف_شدہ PSPIRKEYB
    اگر (irkbd_ready) {
        غیرعلامتی حرف بفر_2[255];
        صحیح i, لمبائی, گنتی;
        SIr_Keyb_جائزہ_رمز_ڈیٹا *جائزہ_ڈیٹا;

        اگر (pspIrKeybReadinput(بفر_2, &لمبائی) >= 0) {
            اگر ((لمبائی % حجم(SIr_Keyb_جائزہ_رمز_ڈیٹا)) == 0) {
                گنتی = لمبائی / حجم(SIr_Keyb_جائزہ_رمز_ڈیٹا);
                برائے (i = 0; i < گنتی; i++) {
                    غیرعلامتی حرف raw;
                    bool نیچے_کو;
                    جائزہ_ڈیٹا = (SIr_Keyb_جائزہ_رمز_ڈیٹا *)بفر_2 + i;
                    raw = جائزہ_ڈیٹا->raw;
                    نیچے_کو = (جائزہ_ڈیٹا->pressed != 0);
                    SDL_Send_Keyboard_کلید(0, SDL_GLOBAL_KEYBOARD_ID, raw, keymap[raw], نیچے_کو);
                }
            }
        }
    }
#اگر_ختم
    sceKernelDelayThread(0);

    واپس;
}

خالی PSP_InitOSKeymap(SDL_VideoDevice *_this)
{
#اگر_تعریف_شدہ PSPIRKEYB
    صحیح i;
    برائے (i = 0; i < SDL_arraysize(keymap); ++i) {
        keymap[i] = SDL_SCANCODE_UNKNOWN;
    }

    keymap[کلید_ESC] = SDL_SCANCODE_ESCAPE;

    keymap[کلید_F1] = SDL_SCANCODE_F1;
    keymap[کلید_F2] = SDL_SCANCODE_F2;
    keymap[کلید_F3] = SDL_SCANCODE_F3;
    keymap[کلید_F4] = SDL_SCANCODE_F4;
    keymap[کلید_F5] = SDL_SCANCODE_F5;
    keymap[کلید_F6] = SDL_SCANCODE_F6;
    keymap[کلید_F7] = SDL_SCANCODE_F7;
    keymap[کلید_F8] = SDL_SCANCODE_F8;
    keymap[کلید_F9] = SDL_SCANCODE_F9;
    keymap[کلید_F10] = SDL_SCANCODE_F10;
    keymap[کلید_F11] = SDL_SCANCODE_F11;
    keymap[کلید_F12] = SDL_SCANCODE_F12;
    keymap[کلید_F13] = SDL_SCANCODE_PRINT;
    keymap[کلید_F14] = SDL_SCANCODE_PAUSE;

    keymap[کلید_GRAVE] = SDL_SCANCODE_GRAVE;
    keymap[کلید_1] = SDL_SCANCODE_1;
    keymap[کلید_2_2] = SDL_SCANCODE_2;
    keymap[کلید_3] = SDL_SCANCODE_3;
    keymap[کلید_4] = SDL_SCANCODE_4;
    keymap[کلید_5] = SDL_SCANCODE_5;
    keymap[کلید_6] = SDL_SCANCODE_6;
    keymap[کلید_7] = SDL_SCANCODE_7;
    keymap[کلید_8] = SDL_SCANCODE_8;
    keymap[کلید_9] = SDL_SCANCODE_9;
    keymap[کلید_0] = SDL_SCANCODE_0;
    keymap[کلید_MINUS] = SDL_SCANCODE_MINUS;
    keymap[کلید_EQUAL] = SDL_SCANCODE_EQUALS;
    keymap[کلید_BACKSPACE] = SDL_SCANCODE_BACKSPACE;

    keymap[کلید_TAB] = SDL_SCANCODE_TAB;
    keymap[کلید_Q] = SDL_SCANCODE_q;
    keymap[کلید_W] = SDL_SCANCODE_w;
    keymap[کلید_E] = SDL_SCANCODE_e;
    keymap[کلید_R] = SDL_SCANCODE_r;
    keymap[کلید_T] = SDL_SCANCODE_t;
    keymap[کلید_Y] = SDL_SCANCODE_y;
    keymap[کلید_U] = SDL_SCANCODE_u;
    keymap[کلید_I] = SDL_SCANCODE_i;
    keymap[کلید_O] = SDL_SCANCODE_o;
    keymap[کلید_P] = SDL_SCANCODE_p;
    keymap[کلید_LEFTBRACE] = SDL_SCANCODE_LEFTBRACKET;
    keymap[کلید_RIGHTBRACE] = SDL_SCANCODE_RIGHTBRACKET;
    keymap[کلید_ENTER] = SDL_SCANCODE_RETURN;

    keymap[کلید_CAPSLOCK] = SDL_SCANCODE_CAPSLOCK;
    keymap[کلید_A] = SDL_SCANCODE_a;
    keymap[کلید_S] = SDL_SCANCODE_s;
    keymap[کلید_D] = SDL_SCANCODE_d;
    keymap[کلید_F] = SDL_SCANCODE_f;
    keymap[کلید_G] = SDL_SCANCODE_g;
    keymap[کلید_H] = SDL_SCANCODE_h;
    keymap[کلید_J] = SDL_SCANCODE_j;
    keymap[کلید_K] = SDL_SCANCODE_k;
    keymap[کلید_L] = SDL_SCANCODE_l;
    keymap[کلید_SEMICOLON] = SDL_SCANCODE_SEMICOLON;
    keymap[کلید_APOSTROPHE] = SDL_SCANCODE_APOSTROPHE;
    keymap[کلید_BACKSLASH] = SDL_SCANCODE_BACKSLASH;

    keymap[کلید_Z] = SDL_SCANCODE_z;
    keymap[کلید_X] = SDL_SCANCODE_x;
    keymap[کلید_C] = SDL_SCANCODE_c;
    keymap[کلید_V] = SDL_SCANCODE_v;
    keymap[کلید_B] = SDL_SCANCODE_b;
    keymap[کلید_N] = SDL_SCANCODE_n;
    keymap[کلید_M] = SDL_SCANCODE_m;
    keymap[کلید_COMMA] = SDL_SCANCODE_COMMA;
    keymap[کلید_DOT] = SDL_SCANCODE_PERIOD;
    keymap[کلید_SLASH] = SDL_SCANCODE_SLASH;

    keymap[کلید_SPACE] = SDL_SCANCODE_SPACE;

    keymap[کلید_اوپر] = SDL_SCANCODE_اوپر;
    keymap[کلید_نیچے_کو] = SDL_SCANCODE_نیچے_کو;
    keymap[کلید_بایاں] = SDL_SCANCODE_بایاں;
    keymap[کلید_دایاں] = SDL_SCANCODE_دایاں;

    keymap[کلید_HOME] = SDL_SCANCODE_HOME;
    keymap[کلید_انتہا] = SDL_SCANCODE_انتہا;
    keymap[کلید_داخل_کرو] = SDL_SCANCODE_داخل_کرو;
    keymap[کلید_DELETE] = SDL_SCANCODE_DELETE;

    keymap[کلید_NUMLOCK] = SDL_SCANCODE_NUMLOCK;
    keymap[کلید_LEFTMETA] = SDL_SCANCODE_LSUPER;

    keymap[کلید_KPSLASH] = SDL_SCANCODE_KP_DIVIDE;
    keymap[کلید_KPASTERISK] = SDL_SCANCODE_KP_MULTIPLY;
    keymap[کلید_KPMINUS] = SDL_SCANCODE_KP_MINUS;
    keymap[کلید_KPPLUS] = SDL_SCANCODE_KP_PLUS;
    keymap[کلید_KPDOT] = SDL_SCANCODE_KP_PERIOD;
    keymap[کلید_KPEQUAL] = SDL_SCANCODE_KP_EQUALS;

    keymap[کلید_LEFTCTRL] = SDL_SCANCODE_LCTRL;
    keymap[کلید_RIGHTCTRL] = SDL_SCANCODE_RCTRL;
    keymap[کلید_LEFTALT] = SDL_SCANCODE_LALT;
    keymap[کلید_RIGHTALT] = SDL_SCANCODE_RALT;
    keymap[کلید_LEFTSHIFT] = SDL_SCANCODE_LSHIFT;
    keymap[کلید_RIGHTSHIFT] = SDL_SCANCODE_RSHIFT;
#اگر_ختم
}

bool PSP_EventInit(SDL_VideoDevice *_this)
{
#اگر_تعریف_شدہ PSPIRKEYB
    صحیح outputmode = PSP_IRKBD_OUTPUT_منوال_SCANCODE;
    صحیح ret = pspIrKeybInit(IRKBD_CONFIG_FILE, 0);
    اگر (ret == PSP_IRKBD_نتیجہ_OK) {
        psp_Ir_Keyb_Output_منوال(outputmode);
        irkbd_ready = 1;
    } ورنہ {
        irkbd_ready = 0;
    }
#اگر_ختم
    // Start thread to read data
    اگر ((event_sem = SDL_CreateSemaphore(1)) == تہی) {
        واپس SDL_سیٹ_Error("Can't create input semaphore");
    }
    running = 1;
    اگر ((thread = SDL_Create_Thread_With_ڈھیر_سائز(EventUpdate, "PSPInputThread", 4096, تہی)) == تہی) {
        واپس SDL_سیٹ_Error("Can't create input thread");
    }
    واپس true;
}

خالی PSP_EventQuit(SDL_VideoDevice *_this)
{
    running = 0;
    SDL_WaitThread(thread, تہی);
    SDL_DestroySemaphore(event_sem);
#اگر_تعریف_شدہ PSPIRKEYB
    اگر (irkbd_ready) {
        psp_Ir_Keyb_اختتام();
        irkbd_ready = 0;
    }
#اگر_ختم
}

// end of SDL_pspevents.c ...

#اگر_ختم // SDL_VIDEO_DRIVER_PSP

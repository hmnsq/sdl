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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_PSP

/* Being a null driver, there's no event stream. We just define stubs for
   most of the API. */

#ضمن "../../events/SDL_events_c.h"
#ضمن "../../events/SDL_keyboard_c.h"
#ضمن "../SDL_sysvideo.h"
#ضمن "SDL_pspvideo.h"
#ضمن "SDL_pspevents_c.h"
#ضمن "../../thread/SDL_systhread.h"
#ضمن <psphprm.h>
#ضمن <pspthreadman.h>

#جے_تعریف_شدہ PSPIRKEYB
#ضمن <pspirkeyb.h>
#ضمن <pspirkeyb_rawkeys.h>

#تعریف_کرو IRKBD_CONFIG_FILE عدم // this will take ms0:/seplugins/pspirkeyb.ini

ساكن صحيح irkbd_ready = 0;
ساكن SDL_Scancode keymap[256];
#جے_انت

ساكن تعداد Psp_Hprm_کلیدیں hprm = 0;
ساكن SDL_Semaphore *event_sem = عدم;
ساكن SDL_Thread *thread = عدم;
ساكن صحيح running = 0;
ساكن بنية
{
    تعداد Psp_Hprm_کلیدیں id;
    SDL_Scancode scancode;
} keymap_psp[] = {
    { PSP_HPRM_PLAYPAUSE, SDL_SCANCODE_F10 },
    { PSP_HPRM_FORWARD, SDL_SCANCODE_F11 },
    { PSP_HPRM_پٹھ, SDL_SCANCODE_F12 },
    { PSP_HPRM_VOL_اتے, SDL_SCANCODE_F13 },
    { PSP_HPRM_VOL_تھلے, SDL_SCANCODE_F14 },
    { PSP_HPRM_HOLD, SDL_SCANCODE_F15 }
};

صحيح EventUpdate(فراغ *انکڑے)
{
    طالما (running) {
        SDL_WaitSemaphore(event_sem);
        sce_Hprm_Peek_Current_کلید((u32 *)&hprm);
        SDL_SignalSemaphore(event_sem);
        // Delay 1/60th of a second
        sceKernelDelayThread(1000000 / 60);
    }
    أرجع 0;
}

فراغ PSP_PumpEvents(SDL_VideoDevice *_this)
{
    صحيح i;
    تعداد Psp_Hprm_کلیدیں کلیدیں;
    تعداد Psp_Hprm_کلیدیں بدلیا;
    ساكن تعداد Psp_Hprm_کلیدیں old_کلیدیں = 0;

    SDL_WaitSemaphore(event_sem);
    کلیدیں = hprm;
    SDL_SignalSemaphore(event_sem);

    // HPRM Keyboard
    بدلیا = old_کلیدیں ^ کلیدیں;
    old_کلیدیں = کلیدیں;
    إذا (بدلیا) {
        لكل (i = 0; i < SDL_arraysize(keymap_psp); i++) {
            إذا (بدلیا & keymap_psp[i].id) {
                bool تھلے = ((کلیدیں & keymap_psp[i].id) != 0);
                SDL_Send_Keyboard_کلید(0, SDL_GLOBAL_KEYBOARD_ID, keymap_psp[i].id, keymap_psp[i].scancode, تھلے);
            }
        }
    }

#جے_تعریف_شدہ PSPIRKEYB
    إذا (irkbd_ready) {
        بنانشانی حرف بفر_2[255];
        صحيح i, لمائی, گنتی;
        SIr_Keyb_جانچ_کوڈ_انکڑے *جانچ_انکڑے;

        إذا (pspIrKeybReadinput(بفر_2, &لمائی) >= 0) {
            إذا ((لمائی % حجم(SIr_Keyb_جانچ_کوڈ_انکڑے)) == 0) {
                گنتی = لمائی / حجم(SIr_Keyb_جانچ_کوڈ_انکڑے);
                لكل (i = 0; i < گنتی; i++) {
                    بنانشانی حرف raw;
                    bool تھلے;
                    جانچ_انکڑے = (SIr_Keyb_جانچ_کوڈ_انکڑے *)بفر_2 + i;
                    raw = جانچ_انکڑے->raw;
                    تھلے = (جانچ_انکڑے->pressed != 0);
                    SDL_Send_Keyboard_کلید(0, SDL_GLOBAL_KEYBOARD_ID, raw, keymap[raw], تھلے);
                }
            }
        }
    }
#جے_انت
    sceKernelDelayThread(0);

    أرجع;
}

فراغ PSP_InitOSKeymap(SDL_VideoDevice *_this)
{
#جے_تعریف_شدہ PSPIRKEYB
    صحيح i;
    لكل (i = 0; i < SDL_arraysize(keymap); ++i) {
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

    keymap[کلید_اتے] = SDL_SCANCODE_اتے;
    keymap[کلید_تھلے] = SDL_SCANCODE_تھلے;
    keymap[کلید_بایاں] = SDL_SCANCODE_بایاں;
    keymap[کلید_دایاں] = SDL_SCANCODE_دایاں;

    keymap[کلید_HOME] = SDL_SCANCODE_HOME;
    keymap[کلید_سرا] = SDL_SCANCODE_سرا;
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
#جے_انت
}

bool PSP_EventInit(SDL_VideoDevice *_this)
{
#جے_تعریف_شدہ PSPIRKEYB
    صحيح outputmode = PSP_IRKBD_OUTPUT_منوال_SCANCODE;
    صحيح ret = pspIrKeybInit(IRKBD_CONFIG_FILE, 0);
    إذا (ret == PSP_IRKBD_نتیجہ_OK) {
        psp_Ir_Keyb_Output_منوال(outputmode);
        irkbd_ready = 1;
    } وإلا {
        irkbd_ready = 0;
    }
#جے_انت
    // Start thread to read data
    إذا ((event_sem = SDL_CreateSemaphore(1)) == عدم) {
        أرجع SDL_سیٹ_Error("Can't create input semaphore");
    }
    running = 1;
    إذا ((thread = SDL_Create_Thread_With_ڈھیر_ناپ(EventUpdate, "PSPInputThread", 4096, عدم)) == عدم) {
        أرجع SDL_سیٹ_Error("Can't create input thread");
    }
    أرجع true;
}

فراغ PSP_EventQuit(SDL_VideoDevice *_this)
{
    running = 0;
    SDL_WaitThread(thread, عدم);
    SDL_DestroySemaphore(event_sem);
#جے_تعریف_شدہ PSPIRKEYB
    إذا (irkbd_ready) {
        psp_Ir_Keyb_انت();
        irkbd_ready = 0;
    }
#جے_انت
}

// end of SDL_pspevents.c ...

#جے_انت // SDL_VIDEO_DRIVER_PSP

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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_PSP

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

#جيڪڏهن_وصف_ٿيل PSPIRKEYB
#ضمن <pspirkeyb.h>
#ضمن <pspirkeyb_rawkeys.h>

#وصف_ڪريو IRKBD_CONFIG_FILE عدم // this will take ms0:/seplugins/pspirkeyb.ini

ساكن صحيح irkbd_ready = 0;
ساكن SDL_Scancode keymap[256];
#جيڪڏهن_پورو

ساكن تعداد Psp_Hprm_ڪنجيون hprm = 0;
ساكن SDL_Semaphore *event_sem = عدم;
ساكن SDL_Thread *thread = عدم;
ساكن صحيح running = 0;
ساكن بنية
{
    تعداد Psp_Hprm_ڪنجيون id;
    SDL_Scancode scancode;
} keymap_psp[] = {
    { PSP_HPRM_PLAYPAUSE, SDL_SCANCODE_F10 },
    { PSP_HPRM_FORWARD, SDL_SCANCODE_F11 },
    { PSP_HPRM_پٺ, SDL_SCANCODE_F12 },
    { PSP_HPRM_VOL_مٿي, SDL_SCANCODE_F13 },
    { PSP_HPRM_VOL_هيٺ_ڏانهن, SDL_SCANCODE_F14 },
    { PSP_HPRM_HOLD, SDL_SCANCODE_F15 }
};

صحيح EventUpdate(فراغ *معلومات)
{
    طالما (running) {
        SDL_WaitSemaphore(event_sem);
        sce_Hprm_Peek_Current_ڪنجي((u32 *)&hprm);
        SDL_SignalSemaphore(event_sem);
        // Delay 1/60th of a second
        sceKernelDelayThread(1000000 / 60);
    }
    أرجع 0;
}

فراغ PSP_PumpEvents(SDL_VideoDevice *_this)
{
    صحيح i;
    تعداد Psp_Hprm_ڪنجيون ڪنجيون;
    تعداد Psp_Hprm_ڪنجيون بدليو;
    ساكن تعداد Psp_Hprm_ڪنجيون old_ڪنجيون = 0;

    SDL_WaitSemaphore(event_sem);
    ڪنجيون = hprm;
    SDL_SignalSemaphore(event_sem);

    // HPRM Keyboard
    بدليو = old_ڪنجيون ^ ڪنجيون;
    old_ڪنجيون = ڪنجيون;
    إذا (بدليو) {
        لكل (i = 0; i < SDL_arraysize(keymap_psp); i++) {
            إذا (بدليو & keymap_psp[i].id) {
                bool هيٺ_ڏانهن = ((ڪنجيون & keymap_psp[i].id) != 0);
                SDL_Send_Keyboard_ڪنجي(0, SDL_GLOBAL_KEYBOARD_ID, keymap_psp[i].id, keymap_psp[i].scancode, هيٺ_ڏانهن);
            }
        }
    }

#جيڪڏهن_وصف_ٿيل PSPIRKEYB
    إذا (irkbd_ready) {
        بنانشان حرف بفر_2[255];
        صحيح i, ڊيگهائي, ڳڻپ;
        SIr_Keyb_جاچ_ڪوڊ_معلومات *جاچ_معلومات;

        إذا (pspIrKeybReadinput(بفر_2, &ڊيگهائي) >= 0) {
            إذا ((ڊيگهائي % حجم(SIr_Keyb_جاچ_ڪوڊ_معلومات)) == 0) {
                ڳڻپ = ڊيگهائي / حجم(SIr_Keyb_جاچ_ڪوڊ_معلومات);
                لكل (i = 0; i < ڳڻپ; i++) {
                    بنانشان حرف raw;
                    bool هيٺ_ڏانهن;
                    جاچ_معلومات = (SIr_Keyb_جاچ_ڪوڊ_معلومات *)بفر_2 + i;
                    raw = جاچ_معلومات->raw;
                    هيٺ_ڏانهن = (جاچ_معلومات->pressed != 0);
                    SDL_Send_Keyboard_ڪنجي(0, SDL_GLOBAL_KEYBOARD_ID, raw, keymap[raw], هيٺ_ڏانهن);
                }
            }
        }
    }
#جيڪڏهن_پورو
    sceKernelDelayThread(0);

    أرجع;
}

فراغ PSP_InitOSKeymap(SDL_VideoDevice *_this)
{
#جيڪڏهن_وصف_ٿيل PSPIRKEYB
    صحيح i;
    لكل (i = 0; i < SDL_arraysize(keymap); ++i) {
        keymap[i] = SDL_SCANCODE_UNKNOWN;
    }

    keymap[ڪنجي_ESC] = SDL_SCANCODE_ESCAPE;

    keymap[ڪنجي_F1] = SDL_SCANCODE_F1;
    keymap[ڪنجي_F2] = SDL_SCANCODE_F2;
    keymap[ڪنجي_F3] = SDL_SCANCODE_F3;
    keymap[ڪنجي_F4] = SDL_SCANCODE_F4;
    keymap[ڪنجي_F5] = SDL_SCANCODE_F5;
    keymap[ڪنجي_F6] = SDL_SCANCODE_F6;
    keymap[ڪنجي_F7] = SDL_SCANCODE_F7;
    keymap[ڪنجي_F8] = SDL_SCANCODE_F8;
    keymap[ڪنجي_F9] = SDL_SCANCODE_F9;
    keymap[ڪنجي_F10] = SDL_SCANCODE_F10;
    keymap[ڪنجي_F11] = SDL_SCANCODE_F11;
    keymap[ڪنجي_F12] = SDL_SCANCODE_F12;
    keymap[ڪنجي_F13] = SDL_SCANCODE_PRINT;
    keymap[ڪنجي_F14] = SDL_SCANCODE_PAUSE;

    keymap[ڪنجي_GRAVE] = SDL_SCANCODE_GRAVE;
    keymap[ڪنجي_1] = SDL_SCANCODE_1;
    keymap[ڪنجي_2_2] = SDL_SCANCODE_2;
    keymap[ڪنجي_3] = SDL_SCANCODE_3;
    keymap[ڪنجي_4] = SDL_SCANCODE_4;
    keymap[ڪنجي_5] = SDL_SCANCODE_5;
    keymap[ڪنجي_6] = SDL_SCANCODE_6;
    keymap[ڪنجي_7] = SDL_SCANCODE_7;
    keymap[ڪنجي_8] = SDL_SCANCODE_8;
    keymap[ڪنجي_9] = SDL_SCANCODE_9;
    keymap[ڪنجي_0] = SDL_SCANCODE_0;
    keymap[ڪنجي_MINUS] = SDL_SCANCODE_MINUS;
    keymap[ڪنجي_EQUAL] = SDL_SCANCODE_EQUALS;
    keymap[ڪنجي_BACKSPACE] = SDL_SCANCODE_BACKSPACE;

    keymap[ڪنجي_TAB] = SDL_SCANCODE_TAB;
    keymap[ڪنجي_Q] = SDL_SCANCODE_q;
    keymap[ڪنجي_W] = SDL_SCANCODE_w;
    keymap[ڪنجي_E] = SDL_SCANCODE_e;
    keymap[ڪنجي_R] = SDL_SCANCODE_r;
    keymap[ڪنجي_T] = SDL_SCANCODE_t;
    keymap[ڪنجي_Y] = SDL_SCANCODE_y;
    keymap[ڪنجي_U] = SDL_SCANCODE_u;
    keymap[ڪنجي_I] = SDL_SCANCODE_i;
    keymap[ڪنجي_O] = SDL_SCANCODE_o;
    keymap[ڪنجي_P] = SDL_SCANCODE_p;
    keymap[ڪنجي_LEFTBRACE] = SDL_SCANCODE_LEFTBRACKET;
    keymap[ڪنجي_RIGHTBRACE] = SDL_SCANCODE_RIGHTBRACKET;
    keymap[ڪنجي_ENTER] = SDL_SCANCODE_RETURN;

    keymap[ڪنجي_CAPSLOCK] = SDL_SCANCODE_CAPSLOCK;
    keymap[ڪنجي_A] = SDL_SCANCODE_a;
    keymap[ڪنجي_S] = SDL_SCANCODE_s;
    keymap[ڪنجي_D] = SDL_SCANCODE_d;
    keymap[ڪنجي_F] = SDL_SCANCODE_f;
    keymap[ڪنجي_G] = SDL_SCANCODE_g;
    keymap[ڪنجي_H] = SDL_SCANCODE_h;
    keymap[ڪنجي_J] = SDL_SCANCODE_j;
    keymap[ڪنجي_K] = SDL_SCANCODE_k;
    keymap[ڪنجي_L] = SDL_SCANCODE_l;
    keymap[ڪنجي_SEMICOLON] = SDL_SCANCODE_SEMICOLON;
    keymap[ڪنجي_APOSTROPHE] = SDL_SCANCODE_APOSTROPHE;
    keymap[ڪنجي_BACKSLASH] = SDL_SCANCODE_BACKSLASH;

    keymap[ڪنجي_Z] = SDL_SCANCODE_z;
    keymap[ڪنجي_X] = SDL_SCANCODE_x;
    keymap[ڪنجي_C] = SDL_SCANCODE_c;
    keymap[ڪنجي_V] = SDL_SCANCODE_v;
    keymap[ڪنجي_B] = SDL_SCANCODE_b;
    keymap[ڪنجي_N] = SDL_SCANCODE_n;
    keymap[ڪنجي_M] = SDL_SCANCODE_m;
    keymap[ڪنجي_COMMA] = SDL_SCANCODE_COMMA;
    keymap[ڪنجي_DOT] = SDL_SCANCODE_PERIOD;
    keymap[ڪنجي_SLASH] = SDL_SCANCODE_SLASH;

    keymap[ڪنجي_SPACE] = SDL_SCANCODE_SPACE;

    keymap[ڪنجي_مٿي] = SDL_SCANCODE_مٿي;
    keymap[ڪنجي_هيٺ_ڏانهن] = SDL_SCANCODE_هيٺ_ڏانهن;
    keymap[ڪنجي_کاٻو] = SDL_SCANCODE_کاٻو;
    keymap[ڪنجي_ساڄو] = SDL_SCANCODE_ساڄو;

    keymap[ڪنجي_HOME] = SDL_SCANCODE_HOME;
    keymap[ڪنجي_پڇاڙي] = SDL_SCANCODE_پڇاڙي;
    keymap[ڪنجي_وجهو] = SDL_SCANCODE_وجهو;
    keymap[ڪنجي_DELETE] = SDL_SCANCODE_DELETE;

    keymap[ڪنجي_NUMLOCK] = SDL_SCANCODE_NUMLOCK;
    keymap[ڪنجي_LEFTMETA] = SDL_SCANCODE_LSUPER;

    keymap[ڪنجي_KPSLASH] = SDL_SCANCODE_KP_DIVIDE;
    keymap[ڪنجي_KPASTERISK] = SDL_SCANCODE_KP_MULTIPLY;
    keymap[ڪنجي_KPMINUS] = SDL_SCANCODE_KP_MINUS;
    keymap[ڪنجي_KPPLUS] = SDL_SCANCODE_KP_PLUS;
    keymap[ڪنجي_KPDOT] = SDL_SCANCODE_KP_PERIOD;
    keymap[ڪنجي_KPEQUAL] = SDL_SCANCODE_KP_EQUALS;

    keymap[ڪنجي_LEFTCTRL] = SDL_SCANCODE_LCTRL;
    keymap[ڪنجي_RIGHTCTRL] = SDL_SCANCODE_RCTRL;
    keymap[ڪنجي_LEFTALT] = SDL_SCANCODE_LALT;
    keymap[ڪنجي_RIGHTALT] = SDL_SCANCODE_RALT;
    keymap[ڪنجي_LEFTSHIFT] = SDL_SCANCODE_LSHIFT;
    keymap[ڪنجي_RIGHTSHIFT] = SDL_SCANCODE_RSHIFT;
#جيڪڏهن_پورو
}

bool PSP_EventInit(SDL_VideoDevice *_this)
{
#جيڪڏهن_وصف_ٿيل PSPIRKEYB
    صحيح outputmode = PSP_IRKBD_OUTPUT_گهڻائي_SCANCODE;
    صحيح ret = pspIrKeybInit(IRKBD_CONFIG_FILE, 0);
    إذا (ret == PSP_IRKBD_نتيجو_OK) {
        psp_Ir_Keyb_Output_گهڻائي(outputmode);
        irkbd_ready = 1;
    } وإلا {
        irkbd_ready = 0;
    }
#جيڪڏهن_پورو
    // Start thread to read data
    إذا ((event_sem = SDL_CreateSemaphore(1)) == عدم) {
        أرجع SDL_سيٽ_Error("Can't create input semaphore");
    }
    running = 1;
    إذا ((thread = SDL_Create_Thread_With_ڍير_سائيز(EventUpdate, "PSPInputThread", 4096, عدم)) == عدم) {
        أرجع SDL_سيٽ_Error("Can't create input thread");
    }
    أرجع true;
}

فراغ PSP_EventQuit(SDL_VideoDevice *_this)
{
    running = 0;
    SDL_WaitThread(thread, عدم);
    SDL_DestroySemaphore(event_sem);
#جيڪڏهن_وصف_ٿيل PSPIRKEYB
    إذا (irkbd_ready) {
        psp_Ir_Keyb_پڄاڻي();
        irkbd_ready = 0;
    }
#جيڪڏهن_پورو
}

// end of SDL_pspevents.c ...

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_PSP

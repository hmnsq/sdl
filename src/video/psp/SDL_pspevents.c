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

#که_تعریف_شوی SDL_VIDEO_DRIVER_PSP

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

#که_تعریف_شوی PSPIRKEYB
#ضمن <pspirkeyb.h>
#ضمن <pspirkeyb_rawkeys.h>

#تعریف_کړه IRKBD_CONFIG_FILE عدم // this will take ms0:/seplugins/pspirkeyb.ini

ساكن صحيح irkbd_ready = 0;
ساكن SDL_Scancode keymap[256];
#د_که_پای

ساكن تعداد Psp_Hprm_کلیګانې hprm = 0;
ساكن SDL_Semaphore *event_sem = عدم;
ساكن SDL_Thread *thread = عدم;
ساكن صحيح running = 0;
ساكن بنية
{
    تعداد Psp_Hprm_کلیګانې id;
    SDL_Scancode scancode;
} keymap_psp[] = {
    { PSP_HPRM_PLAYPAUSE, SDL_SCANCODE_F10 },
    { PSP_HPRM_FORWARD, SDL_SCANCODE_F11 },
    { PSP_HPRM_شا, SDL_SCANCODE_F12 },
    { PSP_HPRM_VOL_پورته, SDL_SCANCODE_F13 },
    { PSP_HPRM_VOL_ښکته, SDL_SCANCODE_F14 },
    { PSP_HPRM_HOLD, SDL_SCANCODE_F15 }
};

صحيح EventUpdate(فراغ *معلومات)
{
    طالما (running) {
        SDL_WaitSemaphore(event_sem);
        sce_Hprm_Peek_Current_کلی((u32 *)&hprm);
        SDL_SignalSemaphore(event_sem);
        // Delay 1/60th of a second
        sceKernelDelayThread(1000000 / 60);
    }
    أرجع 0;
}

فراغ PSP_PumpEvents(SDL_VideoDevice *_this)
{
    صحيح i;
    تعداد Psp_Hprm_کلیګانې کلیګانې;
    تعداد Psp_Hprm_کلیګانې بدل_شوی;
    ساكن تعداد Psp_Hprm_کلیګانې old_کلیګانې = 0;

    SDL_WaitSemaphore(event_sem);
    کلیګانې = hprm;
    SDL_SignalSemaphore(event_sem);

    // HPRM Keyboard
    بدل_شوی = old_کلیګانې ^ کلیګانې;
    old_کلیګانې = کلیګانې;
    إذا (بدل_شوی) {
        لكل (i = 0; i < SDL_arraysize(keymap_psp); i++) {
            إذا (بدل_شوی & keymap_psp[i].id) {
                bool ښکته = ((کلیګانې & keymap_psp[i].id) != 0);
                SDL_Send_Keyboard_کلی(0, SDL_GLOBAL_KEYBOARD_ID, keymap_psp[i].id, keymap_psp[i].scancode, ښکته);
            }
        }
    }

#که_تعریف_شوی PSPIRKEYB
    إذا (irkbd_ready) {
        بینښه حرف بفر_2[255];
        صحيح i, اوږدتیا, شمېر;
        SIr_Keyb_لټون_کوډ_معلومات *لټون_معلومات;

        إذا (pspIrKeybReadinput(بفر_2, &اوږدتیا) >= 0) {
            إذا ((اوږدتیا % حجم(SIr_Keyb_لټون_کوډ_معلومات)) == 0) {
                شمېر = اوږدتیا / حجم(SIr_Keyb_لټون_کوډ_معلومات);
                لكل (i = 0; i < شمېر; i++) {
                    بینښه حرف raw;
                    bool ښکته;
                    لټون_معلومات = (SIr_Keyb_لټون_کوډ_معلومات *)بفر_2 + i;
                    raw = لټون_معلومات->raw;
                    ښکته = (لټون_معلومات->pressed != 0);
                    SDL_Send_Keyboard_کلی(0, SDL_GLOBAL_KEYBOARD_ID, raw, keymap[raw], ښکته);
                }
            }
        }
    }
#د_که_پای
    sceKernelDelayThread(0);

    أرجع;
}

فراغ PSP_InitOSKeymap(SDL_VideoDevice *_this)
{
#که_تعریف_شوی PSPIRKEYB
    صحيح i;
    لكل (i = 0; i < SDL_arraysize(keymap); ++i) {
        keymap[i] = SDL_SCANCODE_UNKNOWN;
    }

    keymap[کلی_ESC] = SDL_SCANCODE_ESCAPE;

    keymap[کلی_F1] = SDL_SCANCODE_F1;
    keymap[کلی_F2] = SDL_SCANCODE_F2;
    keymap[کلی_F3] = SDL_SCANCODE_F3;
    keymap[کلی_F4] = SDL_SCANCODE_F4;
    keymap[کلی_F5] = SDL_SCANCODE_F5;
    keymap[کلی_F6] = SDL_SCANCODE_F6;
    keymap[کلی_F7] = SDL_SCANCODE_F7;
    keymap[کلی_F8] = SDL_SCANCODE_F8;
    keymap[کلی_F9] = SDL_SCANCODE_F9;
    keymap[کلی_F10] = SDL_SCANCODE_F10;
    keymap[کلی_F11] = SDL_SCANCODE_F11;
    keymap[کلی_F12] = SDL_SCANCODE_F12;
    keymap[کلی_F13] = SDL_SCANCODE_PRINT;
    keymap[کلی_F14] = SDL_SCANCODE_PAUSE;

    keymap[کلی_GRAVE] = SDL_SCANCODE_GRAVE;
    keymap[کلی_1] = SDL_SCANCODE_1;
    keymap[کلی_2_2] = SDL_SCANCODE_2;
    keymap[کلی_3] = SDL_SCANCODE_3;
    keymap[کلی_4] = SDL_SCANCODE_4;
    keymap[کلی_5] = SDL_SCANCODE_5;
    keymap[کلی_6] = SDL_SCANCODE_6;
    keymap[کلی_7] = SDL_SCANCODE_7;
    keymap[کلی_8] = SDL_SCANCODE_8;
    keymap[کلی_9] = SDL_SCANCODE_9;
    keymap[کلی_0] = SDL_SCANCODE_0;
    keymap[کلی_MINUS] = SDL_SCANCODE_MINUS;
    keymap[کلی_EQUAL] = SDL_SCANCODE_EQUALS;
    keymap[کلی_BACKSPACE] = SDL_SCANCODE_BACKSPACE;

    keymap[کلی_TAB] = SDL_SCANCODE_TAB;
    keymap[کلی_Q] = SDL_SCANCODE_q;
    keymap[کلی_W] = SDL_SCANCODE_w;
    keymap[کلی_E] = SDL_SCANCODE_e;
    keymap[کلی_R] = SDL_SCANCODE_r;
    keymap[کلی_T] = SDL_SCANCODE_t;
    keymap[کلی_Y] = SDL_SCANCODE_y;
    keymap[کلی_U] = SDL_SCANCODE_u;
    keymap[کلی_I] = SDL_SCANCODE_i;
    keymap[کلی_O] = SDL_SCANCODE_o;
    keymap[کلی_P] = SDL_SCANCODE_p;
    keymap[کلی_LEFTBRACE] = SDL_SCANCODE_LEFTBRACKET;
    keymap[کلی_RIGHTBRACE] = SDL_SCANCODE_RIGHTBRACKET;
    keymap[کلی_ENTER] = SDL_SCANCODE_RETURN;

    keymap[کلی_CAPSLOCK] = SDL_SCANCODE_CAPSLOCK;
    keymap[کلی_A] = SDL_SCANCODE_a;
    keymap[کلی_S] = SDL_SCANCODE_s;
    keymap[کلی_D] = SDL_SCANCODE_d;
    keymap[کلی_F] = SDL_SCANCODE_f;
    keymap[کلی_G] = SDL_SCANCODE_g;
    keymap[کلی_H] = SDL_SCANCODE_h;
    keymap[کلی_J] = SDL_SCANCODE_j;
    keymap[کلی_K] = SDL_SCANCODE_k;
    keymap[کلی_L] = SDL_SCANCODE_l;
    keymap[کلی_SEMICOLON] = SDL_SCANCODE_SEMICOLON;
    keymap[کلی_APOSTROPHE] = SDL_SCANCODE_APOSTROPHE;
    keymap[کلی_BACKSLASH] = SDL_SCANCODE_BACKSLASH;

    keymap[کلی_Z] = SDL_SCANCODE_z;
    keymap[کلی_X] = SDL_SCANCODE_x;
    keymap[کلی_C] = SDL_SCANCODE_c;
    keymap[کلی_V] = SDL_SCANCODE_v;
    keymap[کلی_B] = SDL_SCANCODE_b;
    keymap[کلی_N] = SDL_SCANCODE_n;
    keymap[کلی_M] = SDL_SCANCODE_m;
    keymap[کلی_COMMA] = SDL_SCANCODE_COMMA;
    keymap[کلی_DOT] = SDL_SCANCODE_PERIOD;
    keymap[کلی_SLASH] = SDL_SCANCODE_SLASH;

    keymap[کلی_SPACE] = SDL_SCANCODE_SPACE;

    keymap[کلی_پورته] = SDL_SCANCODE_پورته;
    keymap[کلی_ښکته] = SDL_SCANCODE_ښکته;
    keymap[کلی_کیڼ] = SDL_SCANCODE_کیڼ;
    keymap[کلی_ښی] = SDL_SCANCODE_ښی;

    keymap[کلی_HOME] = SDL_SCANCODE_HOME;
    keymap[کلی_پای_ټکی] = SDL_SCANCODE_پای_ټکی;
    keymap[کلی_ورننباسه] = SDL_SCANCODE_ورننباسه;
    keymap[کلی_DELETE] = SDL_SCANCODE_DELETE;

    keymap[کلی_NUMLOCK] = SDL_SCANCODE_NUMLOCK;
    keymap[کلی_LEFTMETA] = SDL_SCANCODE_LSUPER;

    keymap[کلی_KPSLASH] = SDL_SCANCODE_KP_DIVIDE;
    keymap[کلی_KPASTERISK] = SDL_SCANCODE_KP_MULTIPLY;
    keymap[کلی_KPMINUS] = SDL_SCANCODE_KP_MINUS;
    keymap[کلی_KPPLUS] = SDL_SCANCODE_KP_PLUS;
    keymap[کلی_KPDOT] = SDL_SCANCODE_KP_PERIOD;
    keymap[کلی_KPEQUAL] = SDL_SCANCODE_KP_EQUALS;

    keymap[کلی_LEFTCTRL] = SDL_SCANCODE_LCTRL;
    keymap[کلی_RIGHTCTRL] = SDL_SCANCODE_RCTRL;
    keymap[کلی_LEFTALT] = SDL_SCANCODE_LALT;
    keymap[کلی_RIGHTALT] = SDL_SCANCODE_RALT;
    keymap[کلی_LEFTSHIFT] = SDL_SCANCODE_LSHIFT;
    keymap[کلی_RIGHTSHIFT] = SDL_SCANCODE_RSHIFT;
#د_که_پای
}

bool PSP_EventInit(SDL_VideoDevice *_this)
{
#که_تعریف_شوی PSPIRKEYB
    صحيح outputmode = PSP_IRKBD_OUTPUT_ډېرپېښ_SCANCODE;
    صحيح ret = pspIrKeybInit(IRKBD_CONFIG_FILE, 0);
    إذا (ret == PSP_IRKBD_پایله_OK) {
        psp_Ir_Keyb_Output_ډېرپېښ(outputmode);
        irkbd_ready = 1;
    } وإلا {
        irkbd_ready = 0;
    }
#د_که_پای
    // Start thread to read data
    إذا ((event_sem = SDL_CreateSemaphore(1)) == عدم) {
        أرجع SDL_سېټ_Error("Can't create input semaphore");
    }
    running = 1;
    إذا ((thread = SDL_Create_Thread_With_ډېری_اندازه(EventUpdate, "PSPInputThread", 4096, عدم)) == عدم) {
        أرجع SDL_سېټ_Error("Can't create input thread");
    }
    أرجع true;
}

فراغ PSP_EventQuit(SDL_VideoDevice *_this)
{
    running = 0;
    SDL_WaitThread(thread, عدم);
    SDL_DestroySemaphore(event_sem);
#که_تعریف_شوی PSPIRKEYB
    إذا (irkbd_ready) {
        psp_Ir_Keyb_پای();
        irkbd_ready = 0;
    }
#د_که_پای
}

// end of SDL_pspevents.c ...

#د_که_پای // SDL_VIDEO_DRIVER_PSP

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

#ifdef SDL_VIDEO_DRIVER_PSP

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

#ifdef PSPIRKEYB
#ضمن <pspirkeyb.h>
#ضمن <pspirkeyb_rawkeys.h>

#define IRKBD_CONFIG_FILE عدم // this will take ms0:/seplugins/pspirkeyb.ini

ساكن صحيح irkbd_ready = 0;
ساكن SDL_Scancode keymap[256];
#endif

ساكن تعداد Psp_Hprm_مفاتيح hprm = 0;
ساكن SDL_Semaphore *event_sem = عدم;
ساكن SDL_Thread *thread = عدم;
ساكن صحيح running = 0;
ساكن بنية
{
    تعداد Psp_Hprm_مفاتيح id;
    SDL_Scancode scancode;
} keymap_psp[] = {
    { PSP_HPRM_PLAYPAUSE, SDL_SCANCODE_F10 },
    { PSP_HPRM_FORWARD, SDL_SCANCODE_F11 },
    { PSP_HPRM_BACK, SDL_SCANCODE_F12 },
    { PSP_HPRM_VOL_UP, SDL_SCANCODE_F13 },
    { PSP_HPRM_VOL_DOWN, SDL_SCANCODE_F14 },
    { PSP_HPRM_HOLD, SDL_SCANCODE_F15 }
};

صحيح EventUpdate(فراغ *data)
{
    بينما (running) {
        SDL_WaitSemaphore(event_sem);
        sce_Hprm_Peek_Current_مفتاح((u32 *)&hprm);
        SDL_SignalSemaphore(event_sem);
        // Delay 1/60th of a second
        sceKernelDelayThread(1000000 / 60);
    }
    إرجاع 0;
}

فراغ PSP_PumpEvents(SDL_VideoDevice *_this)
{
    صحيح i;
    تعداد Psp_Hprm_مفاتيح مفاتيح;
    تعداد Psp_Hprm_مفاتيح changed;
    ساكن تعداد Psp_Hprm_مفاتيح old_مفاتيح = 0;

    SDL_WaitSemaphore(event_sem);
    مفاتيح = hprm;
    SDL_SignalSemaphore(event_sem);

    // HPRM Keyboard
    changed = old_مفاتيح ^ مفاتيح;
    old_مفاتيح = مفاتيح;
    إذا (changed) {
        لكل (i = 0; i < SDL_arraysize(keymap_psp); i++) {
            إذا (changed & keymap_psp[i].id) {
                bool down = ((مفاتيح & keymap_psp[i].id) != 0);
                SDL_Send_Keyboard_مفتاح(0, SDL_GLOBAL_KEYBOARD_ID, keymap_psp[i].id, keymap_psp[i].scancode, down);
            }
        }
    }

#ifdef PSPIRKEYB
    إذا (irkbd_ready) {
        unsigned حرف buffer[255];
        صحيح i, length, تعداد_2;
        SIrKeybScanCodeData *scanData;

        إذا (pspIrKeybReadinput(buffer, &length) >= 0) {
            إذا ((length % حجم(SIrKeybScanCodeData)) == 0) {
                تعداد_2 = length / حجم(SIrKeybScanCodeData);
                لكل (i = 0; i < تعداد_2; i++) {
                    unsigned حرف raw;
                    bool down;
                    scanData = (SIrKeybScanCodeData *)buffer + i;
                    raw = scanData->raw;
                    down = (scanData->pressed != 0);
                    SDL_Send_Keyboard_مفتاح(0, SDL_GLOBAL_KEYBOARD_ID, raw, keymap[raw], down);
                }
            }
        }
    }
#endif
    sceKernelDelayThread(0);

    إرجاع;
}

فراغ PSP_InitOSKeymap(SDL_VideoDevice *_this)
{
#ifdef PSPIRKEYB
    صحيح i;
    لكل (i = 0; i < SDL_arraysize(keymap); ++i) {
        keymap[i] = SDL_SCANCODE_UNKNOWN;
    }

    keymap[مفتاح_ESC] = SDL_SCANCODE_ESCAPE;

    keymap[مفتاح_F1] = SDL_SCANCODE_F1;
    keymap[مفتاح_F2] = SDL_SCANCODE_F2;
    keymap[مفتاح_F3] = SDL_SCANCODE_F3;
    keymap[مفتاح_F4] = SDL_SCANCODE_F4;
    keymap[مفتاح_F5] = SDL_SCANCODE_F5;
    keymap[مفتاح_F6] = SDL_SCANCODE_F6;
    keymap[مفتاح_F7] = SDL_SCANCODE_F7;
    keymap[مفتاح_F8] = SDL_SCANCODE_F8;
    keymap[مفتاح_F9] = SDL_SCANCODE_F9;
    keymap[مفتاح_F10] = SDL_SCANCODE_F10;
    keymap[مفتاح_F11] = SDL_SCANCODE_F11;
    keymap[مفتاح_F12] = SDL_SCANCODE_F12;
    keymap[مفتاح_F13] = SDL_SCANCODE_PRINT;
    keymap[مفتاح_F14] = SDL_SCANCODE_PAUSE;

    keymap[مفتاح_GRAVE] = SDL_SCANCODE_GRAVE;
    keymap[مفتاح_1] = SDL_SCANCODE_1;
    keymap[مفتاح_2_2] = SDL_SCANCODE_2;
    keymap[مفتاح_3] = SDL_SCANCODE_3;
    keymap[مفتاح_4] = SDL_SCANCODE_4;
    keymap[مفتاح_5] = SDL_SCANCODE_5;
    keymap[مفتاح_6] = SDL_SCANCODE_6;
    keymap[مفتاح_7] = SDL_SCANCODE_7;
    keymap[مفتاح_8] = SDL_SCANCODE_8;
    keymap[مفتاح_9] = SDL_SCANCODE_9;
    keymap[مفتاح_0] = SDL_SCANCODE_0;
    keymap[مفتاح_MINUS] = SDL_SCANCODE_MINUS;
    keymap[مفتاح_EQUAL] = SDL_SCANCODE_EQUALS;
    keymap[مفتاح_BACKSPACE] = SDL_SCANCODE_BACKSPACE;

    keymap[مفتاح_TAB] = SDL_SCANCODE_TAB;
    keymap[مفتاح_Q] = SDL_SCANCODE_q;
    keymap[مفتاح_W] = SDL_SCANCODE_w;
    keymap[مفتاح_E] = SDL_SCANCODE_e;
    keymap[مفتاح_R] = SDL_SCANCODE_r;
    keymap[مفتاح_T] = SDL_SCANCODE_t;
    keymap[مفتاح_Y] = SDL_SCANCODE_y;
    keymap[مفتاح_U] = SDL_SCANCODE_u;
    keymap[مفتاح_I] = SDL_SCANCODE_i;
    keymap[مفتاح_O] = SDL_SCANCODE_o;
    keymap[مفتاح_P] = SDL_SCANCODE_p;
    keymap[مفتاح_LEFTBRACE] = SDL_SCANCODE_LEFTBRACKET;
    keymap[مفتاح_RIGHTBRACE] = SDL_SCANCODE_RIGHTBRACKET;
    keymap[مفتاح_ENTER] = SDL_SCANCODE_RETURN;

    keymap[مفتاح_CAPSLOCK] = SDL_SCANCODE_CAPSLOCK;
    keymap[مفتاح_A] = SDL_SCANCODE_a;
    keymap[مفتاح_S] = SDL_SCANCODE_s;
    keymap[مفتاح_D] = SDL_SCANCODE_d;
    keymap[مفتاح_F] = SDL_SCANCODE_f;
    keymap[مفتاح_G] = SDL_SCANCODE_g;
    keymap[مفتاح_H] = SDL_SCANCODE_h;
    keymap[مفتاح_J] = SDL_SCANCODE_j;
    keymap[مفتاح_K] = SDL_SCANCODE_k;
    keymap[مفتاح_L] = SDL_SCANCODE_l;
    keymap[مفتاح_SEMICOLON] = SDL_SCANCODE_SEMICOLON;
    keymap[مفتاح_APOSTROPHE] = SDL_SCANCODE_APOSTROPHE;
    keymap[مفتاح_BACKSLASH] = SDL_SCANCODE_BACKSLASH;

    keymap[مفتاح_Z] = SDL_SCANCODE_z;
    keymap[مفتاح_X] = SDL_SCANCODE_x;
    keymap[مفتاح_C] = SDL_SCANCODE_c;
    keymap[مفتاح_V] = SDL_SCANCODE_v;
    keymap[مفتاح_B] = SDL_SCANCODE_b;
    keymap[مفتاح_N] = SDL_SCANCODE_n;
    keymap[مفتاح_M] = SDL_SCANCODE_m;
    keymap[مفتاح_COMMA] = SDL_SCANCODE_COMMA;
    keymap[مفتاح_DOT] = SDL_SCANCODE_PERIOD;
    keymap[مفتاح_SLASH] = SDL_SCANCODE_SLASH;

    keymap[مفتاح_SPACE] = SDL_SCANCODE_SPACE;

    keymap[مفتاح_UP] = SDL_SCANCODE_UP;
    keymap[مفتاح_DOWN] = SDL_SCANCODE_DOWN;
    keymap[مفتاح_يسار] = SDL_SCANCODE_يسار;
    keymap[مفتاح_يمين] = SDL_SCANCODE_يمين;

    keymap[مفتاح_HOME] = SDL_SCANCODE_HOME;
    keymap[مفتاح_END] = SDL_SCANCODE_END;
    keymap[مفتاح_أدرج] = SDL_SCANCODE_أدرج;
    keymap[مفتاح_DELETE] = SDL_SCANCODE_DELETE;

    keymap[مفتاح_NUMLOCK] = SDL_SCANCODE_NUMLOCK;
    keymap[مفتاح_LEFTMETA] = SDL_SCANCODE_LSUPER;

    keymap[مفتاح_KPSLASH] = SDL_SCANCODE_KP_DIVIDE;
    keymap[مفتاح_KPASTERISK] = SDL_SCANCODE_KP_MULTIPLY;
    keymap[مفتاح_KPMINUS] = SDL_SCANCODE_KP_MINUS;
    keymap[مفتاح_KPPLUS] = SDL_SCANCODE_KP_PLUS;
    keymap[مفتاح_KPDOT] = SDL_SCANCODE_KP_PERIOD;
    keymap[مفتاح_KPEQUAL] = SDL_SCANCODE_KP_EQUALS;

    keymap[مفتاح_LEFTCTRL] = SDL_SCANCODE_LCTRL;
    keymap[مفتاح_RIGHTCTRL] = SDL_SCANCODE_RCTRL;
    keymap[مفتاح_LEFTALT] = SDL_SCANCODE_LALT;
    keymap[مفتاح_RIGHTALT] = SDL_SCANCODE_RALT;
    keymap[مفتاح_LEFTSHIFT] = SDL_SCANCODE_LSHIFT;
    keymap[مفتاح_RIGHTSHIFT] = SDL_SCANCODE_RSHIFT;
#endif
}

bool PSP_EventInit(SDL_VideoDevice *_this)
{
#ifdef PSPIRKEYB
    صحيح outputmode = PSP_IRKBD_OUTPUT_MODE_SCANCODE;
    صحيح ret = pspIrKeybInit(IRKBD_CONFIG_FILE, 0);
    إذا (ret == PSP_IRKBD_RESULT_OK) {
        pspIrKeybOutputMode(outputmode);
        irkbd_ready = 1;
    } وإلا {
        irkbd_ready = 0;
    }
#endif
    // Start thread to read data
    إذا ((event_sem = SDL_CreateSemaphore(1)) == عدم) {
        إرجاع SDL_SetError("Can't create input semaphore");
    }
    running = 1;
    إذا ((thread = SDL_Create_Thread_With_مكدس_Size(EventUpdate, "PSPInputThread", 4096, عدم)) == عدم) {
        إرجاع SDL_SetError("Can't create input thread");
    }
    إرجاع true;
}

فراغ PSP_EventQuit(SDL_VideoDevice *_this)
{
    running = 0;
    SDL_WaitThread(thread, عدم);
    SDL_DestroySemaphore(event_sem);
#ifdef PSPIRKEYB
    إذا (irkbd_ready) {
        pspIrKeybFinish();
        irkbd_ready = 0;
    }
#endif
}

// end of SDL_pspevents.c ...

#endif // SDL_VIDEO_DRIVER_PSP

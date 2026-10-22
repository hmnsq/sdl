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
#अन्तर्भाव "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_PSP

/* Being a null driver, there's no event stream. We just define stubs for
   most of the API. */

#अन्तर्भाव "../../events/SDL_events_c.h"
#अन्तर्भाव "../../events/SDL_keyboard_c.h"
#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "SDL_pspvideo.h"
#अन्तर्भाव "SDL_pspevents_c.h"
#अन्तर्भाव "../../thread/SDL_systhread.h"
#अन्तर्भाव <psphprm.h>
#अन्तर्भाव <pspthreadman.h>

#ifdef PSPIRKEYB
#अन्तर्भाव <pspirkeyb.h>
#अन्तर्भाव <pspirkeyb_rawkeys.h>

#define IRKBD_CONFIG_FILE रिक्त // this will take ms0:/seplugins/pspirkeyb.ini

स्थिर पूर्णाङ्क irkbd_ready = 0;
स्थिर SDL_Scancode keymap[256];
#endif

स्थिर गणना Psp_Hprm_साँचोहरू hprm = 0;
स्थिर SDL_Semaphore *event_sem = रिक्त;
स्थिर SDL_Thread *thread = रिक्त;
स्थिर पूर्णाङ्क running = 0;
स्थिर संरचना
{
    गणना Psp_Hprm_साँचोहरू id;
    SDL_Scancode scancode;
} keymap_psp[] = {
    { PSP_HPRM_PLAYPAUSE, SDL_SCANCODE_F10 },
    { PSP_HPRM_FORWARD, SDL_SCANCODE_F11 },
    { PSP_HPRM_BACK, SDL_SCANCODE_F12 },
    { PSP_HPRM_VOL_UP, SDL_SCANCODE_F13 },
    { PSP_HPRM_VOL_DOWN, SDL_SCANCODE_F14 },
    { PSP_HPRM_HOLD, SDL_SCANCODE_F15 }
};

पूर्णाङ्क EventUpdate(शून्य *data)
{
    जबसम्म (running) {
        SDL_WaitSemaphore(event_sem);
        sce_Hprm_Peek_Current_साँचो((u32 *)&hprm);
        SDL_SignalSemaphore(event_sem);
        // Delay 1/60th of a second
        sceKernelDelayThread(1000000 / 60);
    }
    फर्काऊ 0;
}

शून्य PSP_PumpEvents(SDL_VideoDevice *_this)
{
    पूर्णाङ्क i;
    गणना Psp_Hprm_साँचोहरू साँचोहरू;
    गणना Psp_Hprm_साँचोहरू changed;
    स्थिर गणना Psp_Hprm_साँचोहरू old_साँचोहरू = 0;

    SDL_WaitSemaphore(event_sem);
    साँचोहरू = hprm;
    SDL_SignalSemaphore(event_sem);

    // HPRM Keyboard
    changed = old_साँचोहरू ^ साँचोहरू;
    old_साँचोहरू = साँचोहरू;
    यदि (changed) {
        लागि (i = 0; i < SDL_arraysize(keymap_psp); i++) {
            यदि (changed & keymap_psp[i].id) {
                bool down = ((साँचोहरू & keymap_psp[i].id) != 0);
                SDL_Send_Keyboard_साँचो(0, SDL_GLOBAL_KEYBOARD_ID, keymap_psp[i].id, keymap_psp[i].scancode, down);
            }
        }
    }

#ifdef PSPIRKEYB
    यदि (irkbd_ready) {
        अचिन्हित वर्ण buffer[255];
        पूर्णाङ्क i, length, गन्ती;
        SIrKeybScanCodeData *scanData;

        यदि (pspIrKeybReadinput(buffer, &length) >= 0) {
            यदि ((length % परिमाण(SIrKeybScanCodeData)) == 0) {
                गन्ती = length / परिमाण(SIrKeybScanCodeData);
                लागि (i = 0; i < गन्ती; i++) {
                    अचिन्हित वर्ण raw;
                    bool down;
                    scanData = (SIrKeybScanCodeData *)buffer + i;
                    raw = scanData->raw;
                    down = (scanData->pressed != 0);
                    SDL_Send_Keyboard_साँचो(0, SDL_GLOBAL_KEYBOARD_ID, raw, keymap[raw], down);
                }
            }
        }
    }
#endif
    sceKernelDelayThread(0);

    फर्काऊ;
}

शून्य PSP_InitOSKeymap(SDL_VideoDevice *_this)
{
#ifdef PSPIRKEYB
    पूर्णाङ्क i;
    लागि (i = 0; i < SDL_arraysize(keymap); ++i) {
        keymap[i] = SDL_SCANCODE_UNKNOWN;
    }

    keymap[साँचो_ESC] = SDL_SCANCODE_ESCAPE;

    keymap[साँचो_F1] = SDL_SCANCODE_F1;
    keymap[साँचो_F2] = SDL_SCANCODE_F2;
    keymap[साँचो_F3] = SDL_SCANCODE_F3;
    keymap[साँचो_F4] = SDL_SCANCODE_F4;
    keymap[साँचो_F5] = SDL_SCANCODE_F5;
    keymap[साँचो_F6] = SDL_SCANCODE_F6;
    keymap[साँचो_F7] = SDL_SCANCODE_F7;
    keymap[साँचो_F8] = SDL_SCANCODE_F8;
    keymap[साँचो_F9] = SDL_SCANCODE_F9;
    keymap[साँचो_F10] = SDL_SCANCODE_F10;
    keymap[साँचो_F11] = SDL_SCANCODE_F11;
    keymap[साँचो_F12] = SDL_SCANCODE_F12;
    keymap[साँचो_F13] = SDL_SCANCODE_PRINT;
    keymap[साँचो_F14] = SDL_SCANCODE_PAUSE;

    keymap[साँचो_GRAVE] = SDL_SCANCODE_GRAVE;
    keymap[साँचो_1] = SDL_SCANCODE_1;
    keymap[साँचो_2_2] = SDL_SCANCODE_2;
    keymap[साँचो_3] = SDL_SCANCODE_3;
    keymap[साँचो_4] = SDL_SCANCODE_4;
    keymap[साँचो_5] = SDL_SCANCODE_5;
    keymap[साँचो_6] = SDL_SCANCODE_6;
    keymap[साँचो_7] = SDL_SCANCODE_7;
    keymap[साँचो_8] = SDL_SCANCODE_8;
    keymap[साँचो_9] = SDL_SCANCODE_9;
    keymap[साँचो_0] = SDL_SCANCODE_0;
    keymap[साँचो_MINUS] = SDL_SCANCODE_MINUS;
    keymap[साँचो_EQUAL] = SDL_SCANCODE_EQUALS;
    keymap[साँचो_BACKSPACE] = SDL_SCANCODE_BACKSPACE;

    keymap[साँचो_TAB] = SDL_SCANCODE_TAB;
    keymap[साँचो_Q] = SDL_SCANCODE_q;
    keymap[साँचो_W] = SDL_SCANCODE_w;
    keymap[साँचो_E] = SDL_SCANCODE_e;
    keymap[साँचो_R] = SDL_SCANCODE_r;
    keymap[साँचो_T] = SDL_SCANCODE_t;
    keymap[साँचो_Y] = SDL_SCANCODE_y;
    keymap[साँचो_U] = SDL_SCANCODE_u;
    keymap[साँचो_I] = SDL_SCANCODE_i;
    keymap[साँचो_O] = SDL_SCANCODE_o;
    keymap[साँचो_P] = SDL_SCANCODE_p;
    keymap[साँचो_LEFTBRACE] = SDL_SCANCODE_LEFTBRACKET;
    keymap[साँचो_RIGHTBRACE] = SDL_SCANCODE_RIGHTBRACKET;
    keymap[साँचो_ENTER] = SDL_SCANCODE_RETURN;

    keymap[साँचो_CAPSLOCK] = SDL_SCANCODE_CAPSLOCK;
    keymap[साँचो_A] = SDL_SCANCODE_a;
    keymap[साँचो_S] = SDL_SCANCODE_s;
    keymap[साँचो_D] = SDL_SCANCODE_d;
    keymap[साँचो_F] = SDL_SCANCODE_f;
    keymap[साँचो_G] = SDL_SCANCODE_g;
    keymap[साँचो_H] = SDL_SCANCODE_h;
    keymap[साँचो_J] = SDL_SCANCODE_j;
    keymap[साँचो_K] = SDL_SCANCODE_k;
    keymap[साँचो_L] = SDL_SCANCODE_l;
    keymap[साँचो_SEMICOLON] = SDL_SCANCODE_SEMICOLON;
    keymap[साँचो_APOSTROPHE] = SDL_SCANCODE_APOSTROPHE;
    keymap[साँचो_BACKSLASH] = SDL_SCANCODE_BACKSLASH;

    keymap[साँचो_Z] = SDL_SCANCODE_z;
    keymap[साँचो_X] = SDL_SCANCODE_x;
    keymap[साँचो_C] = SDL_SCANCODE_c;
    keymap[साँचो_V] = SDL_SCANCODE_v;
    keymap[साँचो_B] = SDL_SCANCODE_b;
    keymap[साँचो_N] = SDL_SCANCODE_n;
    keymap[साँचो_M] = SDL_SCANCODE_m;
    keymap[साँचो_COMMA] = SDL_SCANCODE_COMMA;
    keymap[साँचो_DOT] = SDL_SCANCODE_PERIOD;
    keymap[साँचो_SLASH] = SDL_SCANCODE_SLASH;

    keymap[साँचो_SPACE] = SDL_SCANCODE_SPACE;

    keymap[साँचो_UP] = SDL_SCANCODE_UP;
    keymap[साँचो_DOWN] = SDL_SCANCODE_DOWN;
    keymap[साँचो_बायाँ] = SDL_SCANCODE_बायाँ;
    keymap[साँचो_दायाँ] = SDL_SCANCODE_दायाँ;

    keymap[साँचो_HOME] = SDL_SCANCODE_HOME;
    keymap[साँचो_END] = SDL_SCANCODE_END;
    keymap[साँचो_घुसाउ] = SDL_SCANCODE_घुसाउ;
    keymap[साँचो_DELETE] = SDL_SCANCODE_DELETE;

    keymap[साँचो_NUMLOCK] = SDL_SCANCODE_NUMLOCK;
    keymap[साँचो_LEFTMETA] = SDL_SCANCODE_LSUPER;

    keymap[साँचो_KPSLASH] = SDL_SCANCODE_KP_DIVIDE;
    keymap[साँचो_KPASTERISK] = SDL_SCANCODE_KP_MULTIPLY;
    keymap[साँचो_KPMINUS] = SDL_SCANCODE_KP_MINUS;
    keymap[साँचो_KPPLUS] = SDL_SCANCODE_KP_PLUS;
    keymap[साँचो_KPDOT] = SDL_SCANCODE_KP_PERIOD;
    keymap[साँचो_KPEQUAL] = SDL_SCANCODE_KP_EQUALS;

    keymap[साँचो_LEFTCTRL] = SDL_SCANCODE_LCTRL;
    keymap[साँचो_RIGHTCTRL] = SDL_SCANCODE_RCTRL;
    keymap[साँचो_LEFTALT] = SDL_SCANCODE_LALT;
    keymap[साँचो_RIGHTALT] = SDL_SCANCODE_RALT;
    keymap[साँचो_LEFTSHIFT] = SDL_SCANCODE_LSHIFT;
    keymap[साँचो_RIGHTSHIFT] = SDL_SCANCODE_RSHIFT;
#endif
}

bool PSP_EventInit(SDL_VideoDevice *_this)
{
#ifdef PSPIRKEYB
    पूर्णाङ्क outputmode = PSP_IRKBD_OUTPUT_MODE_SCANCODE;
    पूर्णाङ्क ret = pspIrKeybInit(IRKBD_CONFIG_FILE, 0);
    यदि (ret == PSP_IRKBD_RESULT_OK) {
        pspIrKeybOutputMode(outputmode);
        irkbd_ready = 1;
    } अन्यथा {
        irkbd_ready = 0;
    }
#endif
    // Start thread to read data
    यदि ((event_sem = SDL_CreateSemaphore(1)) == रिक्त) {
        फर्काऊ SDL_SetError("Can't create input semaphore");
    }
    running = 1;
    यदि ((thread = SDL_Create_Thread_With_थाक_Size(EventUpdate, "PSPInputThread", 4096, रिक्त)) == रिक्त) {
        फर्काऊ SDL_SetError("Can't create input thread");
    }
    फर्काऊ true;
}

शून्य PSP_EventQuit(SDL_VideoDevice *_this)
{
    running = 0;
    SDL_WaitThread(thread, रिक्त);
    SDL_DestroySemaphore(event_sem);
#ifdef PSPIRKEYB
    यदि (irkbd_ready) {
        pspIrKeybFinish();
        irkbd_ready = 0;
    }
#endif
}

// end of SDL_pspevents.c ...

#endif // SDL_VIDEO_DRIVER_PSP

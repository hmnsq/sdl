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

स्थिर गणना Psp_Hprm_कुञ्चिकाः hprm = 0;
स्थिर SDL_Semaphore *event_sem = रिक्त;
स्थिर SDL_Thread *thread = रिक्त;
स्थिर पूर्णाङ्क running = 0;
स्थिर संरचना
{
    गणना Psp_Hprm_कुञ्चिकाः id;
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
    जाव (running) {
        SDL_WaitSemaphore(event_sem);
        sce_Hprm_Peek_Current_कुञ्चिका((u32 *)&hprm);
        SDL_SignalSemaphore(event_sem);
        // Delay 1/60th of a second
        sceKernelDelayThread(1000000 / 60);
    }
    प्रत्यागम 0;
}

शून्य PSP_PumpEvents(SDL_VideoDevice *_this)
{
    पूर्णाङ्क i;
    गणना Psp_Hprm_कुञ्चिकाः कुञ्चिकाः;
    गणना Psp_Hprm_कुञ्चिकाः changed;
    स्थिर गणना Psp_Hprm_कुञ्चिकाः old_कुञ्चिकाः = 0;

    SDL_WaitSemaphore(event_sem);
    कुञ्चिकाः = hprm;
    SDL_SignalSemaphore(event_sem);

    // HPRM Keyboard
    changed = old_कुञ्चिकाः ^ कुञ्चिकाः;
    old_कुञ्चिकाः = कुञ्चिकाः;
    जइ (changed) {
        प्रति (i = 0; i < SDL_arraysize(keymap_psp); i++) {
            जइ (changed & keymap_psp[i].id) {
                bool down = ((कुञ्चिकाः & keymap_psp[i].id) != 0);
                SDL_Send_Keyboard_कुञ्चिका(0, SDL_GLOBAL_KEYBOARD_ID, keymap_psp[i].id, keymap_psp[i].scancode, down);
            }
        }
    }

#ifdef PSPIRKEYB
    जइ (irkbd_ready) {
        unsigned वर्ण buffer[255];
        पूर्णाङ्क i, length, गणनम्;
        SIrKeybScanCodeData *scanData;

        जइ (pspIrKeybReadinput(buffer, &length) >= 0) {
            जइ ((length % परिमाण(SIrKeybScanCodeData)) == 0) {
                गणनम् = length / परिमाण(SIrKeybScanCodeData);
                प्रति (i = 0; i < गणनम्; i++) {
                    unsigned वर्ण raw;
                    bool down;
                    scanData = (SIrKeybScanCodeData *)buffer + i;
                    raw = scanData->raw;
                    down = (scanData->pressed != 0);
                    SDL_Send_Keyboard_कुञ्चिका(0, SDL_GLOBAL_KEYBOARD_ID, raw, keymap[raw], down);
                }
            }
        }
    }
#endif
    sceKernelDelayThread(0);

    प्रत्यागम;
}

शून्य PSP_InitOSKeymap(SDL_VideoDevice *_this)
{
#ifdef PSPIRKEYB
    पूर्णाङ्क i;
    प्रति (i = 0; i < SDL_arraysize(keymap); ++i) {
        keymap[i] = SDL_SCANCODE_UNKNOWN;
    }

    keymap[कुञ्चिका_ESC] = SDL_SCANCODE_ESCAPE;

    keymap[कुञ्चिका_F1] = SDL_SCANCODE_F1;
    keymap[कुञ्चिका_F2] = SDL_SCANCODE_F2;
    keymap[कुञ्चिका_F3] = SDL_SCANCODE_F3;
    keymap[कुञ्चिका_F4] = SDL_SCANCODE_F4;
    keymap[कुञ्चिका_F5] = SDL_SCANCODE_F5;
    keymap[कुञ्चिका_F6] = SDL_SCANCODE_F6;
    keymap[कुञ्चिका_F7] = SDL_SCANCODE_F7;
    keymap[कुञ्चिका_F8] = SDL_SCANCODE_F8;
    keymap[कुञ्चिका_F9] = SDL_SCANCODE_F9;
    keymap[कुञ्चिका_F10] = SDL_SCANCODE_F10;
    keymap[कुञ्चिका_F11] = SDL_SCANCODE_F11;
    keymap[कुञ्चिका_F12] = SDL_SCANCODE_F12;
    keymap[कुञ्चिका_F13] = SDL_SCANCODE_PRINT;
    keymap[कुञ्चिका_F14] = SDL_SCANCODE_PAUSE;

    keymap[कुञ्चिका_GRAVE] = SDL_SCANCODE_GRAVE;
    keymap[कुञ्चिका_1] = SDL_SCANCODE_1;
    keymap[कुञ्चिका_2_2] = SDL_SCANCODE_2;
    keymap[कुञ्चिका_3] = SDL_SCANCODE_3;
    keymap[कुञ्चिका_4] = SDL_SCANCODE_4;
    keymap[कुञ्चिका_5] = SDL_SCANCODE_5;
    keymap[कुञ्चिका_6] = SDL_SCANCODE_6;
    keymap[कुञ्चिका_7] = SDL_SCANCODE_7;
    keymap[कुञ्चिका_8] = SDL_SCANCODE_8;
    keymap[कुञ्चिका_9] = SDL_SCANCODE_9;
    keymap[कुञ्चिका_0] = SDL_SCANCODE_0;
    keymap[कुञ्चिका_MINUS] = SDL_SCANCODE_MINUS;
    keymap[कुञ्चिका_EQUAL] = SDL_SCANCODE_EQUALS;
    keymap[कुञ्चिका_BACKSPACE] = SDL_SCANCODE_BACKSPACE;

    keymap[कुञ्चिका_TAB] = SDL_SCANCODE_TAB;
    keymap[कुञ्चिका_Q] = SDL_SCANCODE_q;
    keymap[कुञ्चिका_W] = SDL_SCANCODE_w;
    keymap[कुञ्चिका_E] = SDL_SCANCODE_e;
    keymap[कुञ्चिका_R] = SDL_SCANCODE_r;
    keymap[कुञ्चिका_T] = SDL_SCANCODE_t;
    keymap[कुञ्चिका_Y] = SDL_SCANCODE_y;
    keymap[कुञ्चिका_U] = SDL_SCANCODE_u;
    keymap[कुञ्चिका_I] = SDL_SCANCODE_i;
    keymap[कुञ्चिका_O] = SDL_SCANCODE_o;
    keymap[कुञ्चिका_P] = SDL_SCANCODE_p;
    keymap[कुञ्चिका_LEFTBRACE] = SDL_SCANCODE_LEFTBRACKET;
    keymap[कुञ्चिका_RIGHTBRACE] = SDL_SCANCODE_RIGHTBRACKET;
    keymap[कुञ्चिका_ENTER] = SDL_SCANCODE_RETURN;

    keymap[कुञ्चिका_CAPSLOCK] = SDL_SCANCODE_CAPSLOCK;
    keymap[कुञ्चिका_A] = SDL_SCANCODE_a;
    keymap[कुञ्चिका_S] = SDL_SCANCODE_s;
    keymap[कुञ्चिका_D] = SDL_SCANCODE_d;
    keymap[कुञ्चिका_F] = SDL_SCANCODE_f;
    keymap[कुञ्चिका_G] = SDL_SCANCODE_g;
    keymap[कुञ्चिका_H] = SDL_SCANCODE_h;
    keymap[कुञ्चिका_J] = SDL_SCANCODE_j;
    keymap[कुञ्चिका_K] = SDL_SCANCODE_k;
    keymap[कुञ्चिका_L] = SDL_SCANCODE_l;
    keymap[कुञ्चिका_SEMICOLON] = SDL_SCANCODE_SEMICOLON;
    keymap[कुञ्चिका_APOSTROPHE] = SDL_SCANCODE_APOSTROPHE;
    keymap[कुञ्चिका_BACKSLASH] = SDL_SCANCODE_BACKSLASH;

    keymap[कुञ्चिका_Z] = SDL_SCANCODE_z;
    keymap[कुञ्चिका_X] = SDL_SCANCODE_x;
    keymap[कुञ्चिका_C] = SDL_SCANCODE_c;
    keymap[कुञ्चिका_V] = SDL_SCANCODE_v;
    keymap[कुञ्चिका_B] = SDL_SCANCODE_b;
    keymap[कुञ्चिका_N] = SDL_SCANCODE_n;
    keymap[कुञ्चिका_M] = SDL_SCANCODE_m;
    keymap[कुञ्चिका_COMMA] = SDL_SCANCODE_COMMA;
    keymap[कुञ्चिका_DOT] = SDL_SCANCODE_PERIOD;
    keymap[कुञ्चिका_SLASH] = SDL_SCANCODE_SLASH;

    keymap[कुञ्चिका_SPACE] = SDL_SCANCODE_SPACE;

    keymap[कुञ्चिका_UP] = SDL_SCANCODE_UP;
    keymap[कुञ्चिका_DOWN] = SDL_SCANCODE_DOWN;
    keymap[कुञ्चिका_वामः] = SDL_SCANCODE_वामः;
    keymap[कुञ्चिका_दक्षिणः] = SDL_SCANCODE_दक्षिणः;

    keymap[कुञ्चिका_HOME] = SDL_SCANCODE_HOME;
    keymap[कुञ्चिका_END] = SDL_SCANCODE_END;
    keymap[कुञ्चिका_निवेशय] = SDL_SCANCODE_निवेशय;
    keymap[कुञ्चिका_DELETE] = SDL_SCANCODE_DELETE;

    keymap[कुञ्चिका_NUMLOCK] = SDL_SCANCODE_NUMLOCK;
    keymap[कुञ्चिका_LEFTMETA] = SDL_SCANCODE_LSUPER;

    keymap[कुञ्चिका_KPSLASH] = SDL_SCANCODE_KP_DIVIDE;
    keymap[कुञ्चिका_KPASTERISK] = SDL_SCANCODE_KP_MULTIPLY;
    keymap[कुञ्चिका_KPMINUS] = SDL_SCANCODE_KP_MINUS;
    keymap[कुञ्चिका_KPPLUS] = SDL_SCANCODE_KP_PLUS;
    keymap[कुञ्चिका_KPDOT] = SDL_SCANCODE_KP_PERIOD;
    keymap[कुञ्चिका_KPEQUAL] = SDL_SCANCODE_KP_EQUALS;

    keymap[कुञ्चिका_LEFTCTRL] = SDL_SCANCODE_LCTRL;
    keymap[कुञ्चिका_RIGHTCTRL] = SDL_SCANCODE_RCTRL;
    keymap[कुञ्चिका_LEFTALT] = SDL_SCANCODE_LALT;
    keymap[कुञ्चिका_RIGHTALT] = SDL_SCANCODE_RALT;
    keymap[कुञ्चिका_LEFTSHIFT] = SDL_SCANCODE_LSHIFT;
    keymap[कुञ्चिका_RIGHTSHIFT] = SDL_SCANCODE_RSHIFT;
#endif
}

bool PSP_EventInit(SDL_VideoDevice *_this)
{
#ifdef PSPIRKEYB
    पूर्णाङ्क outputmode = PSP_IRKBD_OUTPUT_MODE_SCANCODE;
    पूर्णाङ्क ret = pspIrKeybInit(IRKBD_CONFIG_FILE, 0);
    जइ (ret == PSP_IRKBD_RESULT_OK) {
        pspIrKeybOutputMode(outputmode);
        irkbd_ready = 1;
    } अण्णहा {
        irkbd_ready = 0;
    }
#endif
    // Start thread to read data
    जइ ((event_sem = SDL_CreateSemaphore(1)) == रिक्त) {
        प्रत्यागम SDL_SetError("Can't create input semaphore");
    }
    running = 1;
    जइ ((thread = SDL_Create_Thread_With_राशिः_Size(EventUpdate, "PSPInputThread", 4096, रिक्त)) == रिक्त) {
        प्रत्यागम SDL_SetError("Can't create input thread");
    }
    प्रत्यागम true;
}

शून्य PSP_EventQuit(SDL_VideoDevice *_this)
{
    running = 0;
    SDL_WaitThread(thread, रिक्त);
    SDL_DestroySemaphore(event_sem);
#ifdef PSPIRKEYB
    जइ (irkbd_ready) {
        pspIrKeybFinish();
        irkbd_ready = 0;
    }
#endif
}

// end of SDL_pspevents.c ...

#endif // SDL_VIDEO_DRIVER_PSP

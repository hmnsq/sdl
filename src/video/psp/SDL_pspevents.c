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

स्थिर गणना Psp_Hprm_कुंजियाँ hprm = 0;
स्थिर SDL_Semaphore *event_sem = रिक्त;
स्थिर SDL_Thread *thread = रिक्त;
स्थिर पूर्णाङ्क running = 0;
स्थिर संरचना
{
    गणना Psp_Hprm_कुंजियाँ id;
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
    यावत् (running) {
        SDL_WaitSemaphore(event_sem);
        sce_Hprm_Peek_Current_कुंजी((u32 *)&hprm);
        SDL_SignalSemaphore(event_sem);
        // Delay 1/60th of a second
        sceKernelDelayThread(1000000 / 60);
    }
    प्रत्यागम 0;
}

शून्य PSP_PumpEvents(SDL_VideoDevice *_this)
{
    पूर्णाङ्क i;
    गणना Psp_Hprm_कुंजियाँ कुंजियाँ;
    गणना Psp_Hprm_कुंजियाँ changed;
    स्थिर गणना Psp_Hprm_कुंजियाँ old_कुंजियाँ = 0;

    SDL_WaitSemaphore(event_sem);
    कुंजियाँ = hprm;
    SDL_SignalSemaphore(event_sem);

    // HPRM Keyboard
    changed = old_कुंजियाँ ^ कुंजियाँ;
    old_कुंजियाँ = कुंजियाँ;
    यदि (changed) {
        प्रति (i = 0; i < SDL_arraysize(keymap_psp); i++) {
            यदि (changed & keymap_psp[i].id) {
                bool down = ((कुंजियाँ & keymap_psp[i].id) != 0);
                SDL_Send_Keyboard_कुंजी(0, SDL_GLOBAL_KEYBOARD_ID, keymap_psp[i].id, keymap_psp[i].scancode, down);
            }
        }
    }

#ifdef PSPIRKEYB
    यदि (irkbd_ready) {
        अचिन्हित वर्ण buffer[255];
        पूर्णाङ्क i, length, गिनती;
        SIrKeybScanCodeData *scanData;

        यदि (pspIrKeybReadinput(buffer, &length) >= 0) {
            यदि ((length % परिमाण(SIrKeybScanCodeData)) == 0) {
                गिनती = length / परिमाण(SIrKeybScanCodeData);
                प्रति (i = 0; i < गिनती; i++) {
                    अचिन्हित वर्ण raw;
                    bool down;
                    scanData = (SIrKeybScanCodeData *)buffer + i;
                    raw = scanData->raw;
                    down = (scanData->pressed != 0);
                    SDL_Send_Keyboard_कुंजी(0, SDL_GLOBAL_KEYBOARD_ID, raw, keymap[raw], down);
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

    keymap[कुंजी_ESC] = SDL_SCANCODE_ESCAPE;

    keymap[कुंजी_F1] = SDL_SCANCODE_F1;
    keymap[कुंजी_F2] = SDL_SCANCODE_F2;
    keymap[कुंजी_F3] = SDL_SCANCODE_F3;
    keymap[कुंजी_F4] = SDL_SCANCODE_F4;
    keymap[कुंजी_F5] = SDL_SCANCODE_F5;
    keymap[कुंजी_F6] = SDL_SCANCODE_F6;
    keymap[कुंजी_F7] = SDL_SCANCODE_F7;
    keymap[कुंजी_F8] = SDL_SCANCODE_F8;
    keymap[कुंजी_F9] = SDL_SCANCODE_F9;
    keymap[कुंजी_F10] = SDL_SCANCODE_F10;
    keymap[कुंजी_F11] = SDL_SCANCODE_F11;
    keymap[कुंजी_F12] = SDL_SCANCODE_F12;
    keymap[कुंजी_F13] = SDL_SCANCODE_PRINT;
    keymap[कुंजी_F14] = SDL_SCANCODE_PAUSE;

    keymap[कुंजी_GRAVE] = SDL_SCANCODE_GRAVE;
    keymap[कुंजी_1] = SDL_SCANCODE_1;
    keymap[कुंजी_2_2] = SDL_SCANCODE_2;
    keymap[कुंजी_3] = SDL_SCANCODE_3;
    keymap[कुंजी_4] = SDL_SCANCODE_4;
    keymap[कुंजी_5] = SDL_SCANCODE_5;
    keymap[कुंजी_6] = SDL_SCANCODE_6;
    keymap[कुंजी_7] = SDL_SCANCODE_7;
    keymap[कुंजी_8] = SDL_SCANCODE_8;
    keymap[कुंजी_9] = SDL_SCANCODE_9;
    keymap[कुंजी_0] = SDL_SCANCODE_0;
    keymap[कुंजी_MINUS] = SDL_SCANCODE_MINUS;
    keymap[कुंजी_EQUAL] = SDL_SCANCODE_EQUALS;
    keymap[कुंजी_BACKSPACE] = SDL_SCANCODE_BACKSPACE;

    keymap[कुंजी_TAB] = SDL_SCANCODE_TAB;
    keymap[कुंजी_Q] = SDL_SCANCODE_q;
    keymap[कुंजी_W] = SDL_SCANCODE_w;
    keymap[कुंजी_E] = SDL_SCANCODE_e;
    keymap[कुंजी_R] = SDL_SCANCODE_r;
    keymap[कुंजी_T] = SDL_SCANCODE_t;
    keymap[कुंजी_Y] = SDL_SCANCODE_y;
    keymap[कुंजी_U] = SDL_SCANCODE_u;
    keymap[कुंजी_I] = SDL_SCANCODE_i;
    keymap[कुंजी_O] = SDL_SCANCODE_o;
    keymap[कुंजी_P] = SDL_SCANCODE_p;
    keymap[कुंजी_LEFTBRACE] = SDL_SCANCODE_LEFTBRACKET;
    keymap[कुंजी_RIGHTBRACE] = SDL_SCANCODE_RIGHTBRACKET;
    keymap[कुंजी_ENTER] = SDL_SCANCODE_RETURN;

    keymap[कुंजी_CAPSLOCK] = SDL_SCANCODE_CAPSLOCK;
    keymap[कुंजी_A] = SDL_SCANCODE_a;
    keymap[कुंजी_S] = SDL_SCANCODE_s;
    keymap[कुंजी_D] = SDL_SCANCODE_d;
    keymap[कुंजी_F] = SDL_SCANCODE_f;
    keymap[कुंजी_G] = SDL_SCANCODE_g;
    keymap[कुंजी_H] = SDL_SCANCODE_h;
    keymap[कुंजी_J] = SDL_SCANCODE_j;
    keymap[कुंजी_K] = SDL_SCANCODE_k;
    keymap[कुंजी_L] = SDL_SCANCODE_l;
    keymap[कुंजी_SEMICOLON] = SDL_SCANCODE_SEMICOLON;
    keymap[कुंजी_APOSTROPHE] = SDL_SCANCODE_APOSTROPHE;
    keymap[कुंजी_BACKSLASH] = SDL_SCANCODE_BACKSLASH;

    keymap[कुंजी_Z] = SDL_SCANCODE_z;
    keymap[कुंजी_X] = SDL_SCANCODE_x;
    keymap[कुंजी_C] = SDL_SCANCODE_c;
    keymap[कुंजी_V] = SDL_SCANCODE_v;
    keymap[कुंजी_B] = SDL_SCANCODE_b;
    keymap[कुंजी_N] = SDL_SCANCODE_n;
    keymap[कुंजी_M] = SDL_SCANCODE_m;
    keymap[कुंजी_COMMA] = SDL_SCANCODE_COMMA;
    keymap[कुंजी_DOT] = SDL_SCANCODE_PERIOD;
    keymap[कुंजी_SLASH] = SDL_SCANCODE_SLASH;

    keymap[कुंजी_SPACE] = SDL_SCANCODE_SPACE;

    keymap[कुंजी_UP] = SDL_SCANCODE_UP;
    keymap[कुंजी_DOWN] = SDL_SCANCODE_DOWN;
    keymap[कुंजी_बायाँ] = SDL_SCANCODE_बायाँ;
    keymap[कुंजी_दायाँ] = SDL_SCANCODE_दायाँ;

    keymap[कुंजी_HOME] = SDL_SCANCODE_HOME;
    keymap[कुंजी_END] = SDL_SCANCODE_END;
    keymap[कुंजी_जोड़ो] = SDL_SCANCODE_जोड़ो;
    keymap[कुंजी_DELETE] = SDL_SCANCODE_DELETE;

    keymap[कुंजी_NUMLOCK] = SDL_SCANCODE_NUMLOCK;
    keymap[कुंजी_LEFTMETA] = SDL_SCANCODE_LSUPER;

    keymap[कुंजी_KPSLASH] = SDL_SCANCODE_KP_DIVIDE;
    keymap[कुंजी_KPASTERISK] = SDL_SCANCODE_KP_MULTIPLY;
    keymap[कुंजी_KPMINUS] = SDL_SCANCODE_KP_MINUS;
    keymap[कुंजी_KPPLUS] = SDL_SCANCODE_KP_PLUS;
    keymap[कुंजी_KPDOT] = SDL_SCANCODE_KP_PERIOD;
    keymap[कुंजी_KPEQUAL] = SDL_SCANCODE_KP_EQUALS;

    keymap[कुंजी_LEFTCTRL] = SDL_SCANCODE_LCTRL;
    keymap[कुंजी_RIGHTCTRL] = SDL_SCANCODE_RCTRL;
    keymap[कुंजी_LEFTALT] = SDL_SCANCODE_LALT;
    keymap[कुंजी_RIGHTALT] = SDL_SCANCODE_RALT;
    keymap[कुंजी_LEFTSHIFT] = SDL_SCANCODE_LSHIFT;
    keymap[कुंजी_RIGHTSHIFT] = SDL_SCANCODE_RSHIFT;
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
        प्रत्यागम SDL_SetError("Can't create input semaphore");
    }
    running = 1;
    यदि ((thread = SDL_Create_Thread_With_ढेर_Size(EventUpdate, "PSPInputThread", 4096, रिक्त)) == रिक्त) {
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
    यदि (irkbd_ready) {
        pspIrKeybFinish();
        irkbd_ready = 0;
    }
#endif
}

// end of SDL_pspevents.c ...

#endif // SDL_VIDEO_DRIVER_PSP

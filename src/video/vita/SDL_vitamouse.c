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
#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VITA

#અન્તર્ભાવ <psp2/kernel/processmgr.h>
#અન્તર્ભાવ <psp2/ctrl.h>
#અન્તર્ભાવ <psp2/hid.h>

#અન્તર્ભાવ "SDL_vitavideo.h"
#અન્તર્ભાવ "SDL_vitamouse_c.h"
#અન્તર્ભાવ "../../events/SDL_mouse_c.h"

SceHidMouseReport m_reports[SCE_HID_MAX_REPORT];
પૂર્ણાંક mouse_hid_handle = 0;
Uint8 prev_buttons = 0;

શૂન્ય VITA_InitMouse(શૂન્ય)
{
    sceHidMouseEnumerate(&mouse_hid_handle, 1);

    જો (mouse_hid_handle > 0) {
        SDL_AddMouse((SDL_MouseID)mouse_hid_handle, ખાલી);
    }
}

શૂન્ય VITA_PollMouse(શૂન્ય)
{
    // We skip polling mouse if no window is created
    જો (!Vita_Window) {
        પાછા;
    }

    જો (mouse_hid_handle > 0) {
        SDL_MouseID mouseID = (SDL_MouseID)mouse_hid_handle;
        પૂર્ણાંક અંક_Reports = sceHidMouseRead(mouse_hid_handle, (SceHidMouseReport **)&m_reports, SCE_HID_MAX_REPORT);
        જો (અંક_Reports > 0) {
            માટે (પૂર્ણાંક i = 0; i <= અંક_Reports - 1; i++) {
                Uint8 changed_buttons = m_reports[i].buttons ^ prev_buttons;

                જો (changed_buttons & 0x1) {
                    જો (prev_buttons & 0x1)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_ડાબું, false);
                    નહીંતર
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_ડાબું, true);
                }
                જો (changed_buttons & 0x2) {
                    જો (prev_buttons & 0x2)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_જમણું, false);
                    નહીંતર
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_જમણું, true);
                }
                જો (changed_buttons & 0x4) {
                    જો (prev_buttons & 0x4)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_મધ્ય, false);
                    નહીંતર
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_મધ્ય, true);
                }
                જો (changed_buttons & 0x8) {
                    જો (prev_buttons & 0x8)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_X1, false);
                    નહીંતર
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_X1, true);
                }
                જો (changed_buttons & 0x10) {
                    જો (prev_buttons & 0x10)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_X2, false);
                    નહીંતર
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_X2, true);
                }

                prev_buttons = m_reports[i].buttons;

                જો (m_reports[i].rel_x || m_reports[i].rel_y) {
                    SDL_SendMouseMotion(0, Vita_Window, mouseID, true, (દશાંશ)m_reports[i].rel_x, (દશાંશ)m_reports[i].rel_y);
                }

                જો (m_reports[i].tilt != 0 || m_reports[i].wheel != 0) {
                    SDL_SendMouseWheel(0, Vita_Window, mouseID, m_reports[i].tilt, m_reports[i].wheel, SDL_MOUSEWHEEL_NORMAL);
                }
            }
        }
    }
}

#endif // SDL_VIDEO_DRIVER_VITA

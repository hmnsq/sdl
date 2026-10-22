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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VITA

#ଅନ୍ତର୍ଭାଵ <psp2/kernel/processmgr.h>
#ଅନ୍ତର୍ଭାଵ <psp2/ctrl.h>
#ଅନ୍ତର୍ଭାଵ <psp2/hid.h>

#ଅନ୍ତର୍ଭାଵ "SDL_vitavideo.h"
#ଅନ୍ତର୍ଭାଵ "SDL_vitamouse_c.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_mouse_c.h"

SceHidMouseReport m_reports[SCE_HID_MAX_REPORT];
ପୂର୍ଣ୍ଣସଂଖ୍ୟା mouse_hid_handle = 0;
Uint8 prev_buttons = 0;

ଶୂନ୍ୟ VITA_InitMouse(ଶୂନ୍ୟ)
{
    sceHidMouseEnumerate(&mouse_hid_handle, 1);

    ଯଦି (mouse_hid_handle > 0) {
        SDL_AddMouse((SDL_MouseID)mouse_hid_handle, ଖାଲି);
    }
}

ଶୂନ୍ୟ VITA_PollMouse(ଶୂନ୍ୟ)
{
    // We skip polling mouse if no window is created
    ଯଦି (!Vita_Window) {
        ଫେରନ୍ତୁ;
    }

    ଯଦି (mouse_hid_handle > 0) {
        SDL_MouseID mouseID = (SDL_MouseID)mouse_hid_handle;
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା ଅଙ୍କ_Reports = sceHidMouseRead(mouse_hid_handle, (SceHidMouseReport **)&m_reports, SCE_HID_MAX_REPORT);
        ଯଦି (ଅଙ୍କ_Reports > 0) {
            ପାଇଁ (ପୂର୍ଣ୍ଣସଂଖ୍ୟା i = 0; i <= ଅଙ୍କ_Reports - 1; i++) {
                Uint8 changed_buttons = m_reports[i].buttons ^ prev_buttons;

                ଯଦି (changed_buttons & 0x1) {
                    ଯଦି (prev_buttons & 0x1)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_ବାମ, false);
                    ଅନ୍ୟଥା
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_ବାମ, true);
                }
                ଯଦି (changed_buttons & 0x2) {
                    ଯଦି (prev_buttons & 0x2)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_ଡାହାଣ, false);
                    ଅନ୍ୟଥା
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_ଡାହାଣ, true);
                }
                ଯଦି (changed_buttons & 0x4) {
                    ଯଦି (prev_buttons & 0x4)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_ମଧ୍ୟ, false);
                    ଅନ୍ୟଥା
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_ମଧ୍ୟ, true);
                }
                ଯଦି (changed_buttons & 0x8) {
                    ଯଦି (prev_buttons & 0x8)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_X1, false);
                    ଅନ୍ୟଥା
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_X1, true);
                }
                ଯଦି (changed_buttons & 0x10) {
                    ଯଦି (prev_buttons & 0x10)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_X2, false);
                    ଅନ୍ୟଥା
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_X2, true);
                }

                prev_buttons = m_reports[i].buttons;

                ଯଦି (m_reports[i].rel_x || m_reports[i].rel_y) {
                    SDL_SendMouseMotion(0, Vita_Window, mouseID, true, (ଦଶମିକ)m_reports[i].rel_x, (ଦଶମିକ)m_reports[i].rel_y);
                }

                ଯଦି (m_reports[i].tilt != 0 || m_reports[i].wheel != 0) {
                    SDL_SendMouseWheel(0, Vita_Window, mouseID, m_reports[i].tilt, m_reports[i].wheel, SDL_MOUSEWHEEL_NORMAL);
                }
            }
        }
    }
}

#endif // SDL_VIDEO_DRIVER_VITA

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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VITA

#ಅನ್ತರ್ಭಾವ <psp2/kernel/processmgr.h>
#ಅನ್ತರ್ಭಾವ <psp2/ctrl.h>
#ಅನ್ತರ್ಭಾವ <psp2/hid.h>

#ಅನ್ತರ್ಭಾವ "SDL_vitavideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_vitamouse_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"

SceHidMouseReport m_reports[SCE_HID_MAX_REPORT];
ಪೂರ್ಣಾಙ್ಕ mouse_hid_handle = 0;
Uint8 prev_buttons = 0;

ಶೂನ್ಯ VITA_InitMouse(ಶೂನ್ಯ)
{
    sceHidMouseEnumerate(&mouse_hid_handle, 1);

    ಯದಿ (mouse_hid_handle > 0) {
        SDL_AddMouse((SDL_MouseID)mouse_hid_handle, ರಿಕ್ತ);
    }
}

ಶೂನ್ಯ VITA_PollMouse(ಶೂನ್ಯ)
{
    // We skip polling mouse if no window is created
    ಯದಿ (!Vita_Window) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    ಯದಿ (mouse_hid_handle > 0) {
        SDL_MouseID mouseID = (SDL_MouseID)mouse_hid_handle;
        ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ_Reports = sceHidMouseRead(mouse_hid_handle, (SceHidMouseReport **)&m_reports, SCE_HID_MAX_REPORT);
        ಯದಿ (ಅಂಕೆ_Reports > 0) {
            ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i <= ಅಂಕೆ_Reports - 1; i++) {
                Uint8 changed_buttons = m_reports[i].buttons ^ prev_buttons;

                ಯದಿ (changed_buttons & 0x1) {
                    ಯದಿ (prev_buttons & 0x1)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_ಎಡ, false);
                    ಅನ್ಯಥಾ
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_ಎಡ, true);
                }
                ಯದಿ (changed_buttons & 0x2) {
                    ಯದಿ (prev_buttons & 0x2)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_ಬಲ, false);
                    ಅನ್ಯಥಾ
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_ಬಲ, true);
                }
                ಯದಿ (changed_buttons & 0x4) {
                    ಯದಿ (prev_buttons & 0x4)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_ಮಧ್ಯ, false);
                    ಅನ್ಯಥಾ
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_ಮಧ್ಯ, true);
                }
                ಯದಿ (changed_buttons & 0x8) {
                    ಯದಿ (prev_buttons & 0x8)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_X1, false);
                    ಅನ್ಯಥಾ
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_X1, true);
                }
                ಯದಿ (changed_buttons & 0x10) {
                    ಯದಿ (prev_buttons & 0x10)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_X2, false);
                    ಅನ್ಯಥಾ
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_X2, true);
                }

                prev_buttons = m_reports[i].buttons;

                ಯದಿ (m_reports[i].rel_x || m_reports[i].rel_y) {
                    SDL_SendMouseMotion(0, Vita_Window, mouseID, true, (ಭಿನ್ನ)m_reports[i].rel_x, (ಭಿನ್ನ)m_reports[i].rel_y);
                }

                ಯದಿ (m_reports[i].tilt != 0 || m_reports[i].wheel != 0) {
                    SDL_SendMouseWheel(0, Vita_Window, mouseID, m_reports[i].tilt, m_reports[i].wheel, SDL_MOUSEWHEEL_NORMAL);
                }
            }
        }
    }
}

#endif // SDL_VIDEO_DRIVER_VITA

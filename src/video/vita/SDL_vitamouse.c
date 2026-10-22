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

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_VITA

#ಅನ್ತರ್ಭಾವ <psp2/kernel/processmgr.h>
#ಅನ್ತರ್ಭಾವ <psp2/ctrl.h>
#ಅನ್ತರ್ಭಾವ <psp2/hid.h>

#ಅನ್ತರ್ಭಾವ "SDL_vitavideo.h"
#ಅನ್ತರ್ಭಾವ "SDL_vitamouse_c.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_mouse_c.h"

SceHidMouseReport m_reports[SCE_HID_MAX_REPORT];
ಪೂರ್ಣಾಂಕ mouse_hid_handle = 0;
Uint8 prev_buttons = 0;

ಶೂನ್ಯ VITA_InitMouse(ಶೂನ್ಯ)
{
    sceHidMouseEnumerate(&mouse_hid_handle, 1);

    ಆದರೆ (mouse_hid_handle > 0) {
        SDL_ಕೂಡಿಸು_Mouse((SDL_MouseID)mouse_hid_handle, ಖಾಲಿ);
    }
}

ಶೂನ್ಯ VITA_PollMouse(ಶೂನ್ಯ)
{
    // We skip polling mouse if no window is created
    ಆದರೆ (!Vita_ಕಿಟಕಿ) {
        ಹಿಂತಿರುಗಿ;
    }

    ಆದರೆ (mouse_hid_handle > 0) {
        SDL_MouseID mouseID = (SDL_MouseID)mouse_hid_handle;
        ಪೂರ್ಣಾಂಕ ಅಂಕೆ_Reports = sceHidMouseRead(mouse_hid_handle, (SceHidMouseReport **)&m_reports, SCE_HID_MAX_REPORT);
        ಆದರೆ (ಅಂಕೆ_Reports > 0) {
            ಗಾಗಿ (ಪೂರ್ಣಾಂಕ i = 0; i <= ಅಂಕೆ_Reports - 1; i++) {
                Uint8 ಬದಲಾಯಿತು_buttons = m_reports[i].buttons ^ prev_buttons;

                ಆದರೆ (ಬದಲಾಯಿತು_buttons & 0x1) {
                    ಆದರೆ (prev_buttons & 0x1)
                        SDL_SendMouseButton(0, Vita_ಕಿಟಕಿ, mouseID, SDL_BUTTON_ಎಡ, false);
                    ಇಲ್ಲದಿದ್ದರೆ
                        SDL_SendMouseButton(0, Vita_ಕಿಟಕಿ, mouseID, SDL_BUTTON_ಎಡ, true);
                }
                ಆದರೆ (ಬದಲಾಯಿತು_buttons & 0x2) {
                    ಆದರೆ (prev_buttons & 0x2)
                        SDL_SendMouseButton(0, Vita_ಕಿಟಕಿ, mouseID, SDL_BUTTON_ಬಲ, false);
                    ಇಲ್ಲದಿದ್ದರೆ
                        SDL_SendMouseButton(0, Vita_ಕಿಟಕಿ, mouseID, SDL_BUTTON_ಬಲ, true);
                }
                ಆದರೆ (ಬದಲಾಯಿತು_buttons & 0x4) {
                    ಆದರೆ (prev_buttons & 0x4)
                        SDL_SendMouseButton(0, Vita_ಕಿಟಕಿ, mouseID, SDL_BUTTON_ಮಧ್ಯ, false);
                    ಇಲ್ಲದಿದ್ದರೆ
                        SDL_SendMouseButton(0, Vita_ಕಿಟಕಿ, mouseID, SDL_BUTTON_ಮಧ್ಯ, true);
                }
                ಆದರೆ (ಬದಲಾಯಿತು_buttons & 0x8) {
                    ಆದರೆ (prev_buttons & 0x8)
                        SDL_SendMouseButton(0, Vita_ಕಿಟಕಿ, mouseID, SDL_BUTTON_X1, false);
                    ಇಲ್ಲದಿದ್ದರೆ
                        SDL_SendMouseButton(0, Vita_ಕಿಟಕಿ, mouseID, SDL_BUTTON_X1, true);
                }
                ಆದರೆ (ಬದಲಾಯಿತು_buttons & 0x10) {
                    ಆದರೆ (prev_buttons & 0x10)
                        SDL_SendMouseButton(0, Vita_ಕಿಟಕಿ, mouseID, SDL_BUTTON_X2, false);
                    ಇಲ್ಲದಿದ್ದರೆ
                        SDL_SendMouseButton(0, Vita_ಕಿಟಕಿ, mouseID, SDL_BUTTON_X2, true);
                }

                prev_buttons = m_reports[i].buttons;

                ಆದರೆ (m_reports[i].rel_x || m_reports[i].rel_y) {
                    SDL_SendMouseMotion(0, Vita_ಕಿಟಕಿ, mouseID, true, (ದಶಮಾಂಶ)m_reports[i].rel_x, (ದಶಮಾಂಶ)m_reports[i].rel_y);
                }

                ಆದರೆ (m_reports[i].tilt != 0 || m_reports[i].wheel != 0) {
                    SDL_SendMouseWheel(0, Vita_ಕಿಟಕಿ, mouseID, m_reports[i].tilt, m_reports[i].wheel, SDL_MOUSEWHEEL_ಸಾಮಾನ್ಯ);
                }
            }
        }
    }
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_VITA

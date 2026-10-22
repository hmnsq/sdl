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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_VITA

#అన్తర్భావ <psp2/kernel/processmgr.h>
#అన్తర్భావ <psp2/ctrl.h>
#అన్తర్భావ <psp2/hid.h>

#అన్తర్భావ "SDL_vitavideo.h"
#అన్తర్భావ "SDL_vitamouse_c.h"
#అన్తర్భావ "../../events/SDL_mouse_c.h"

SceHidMouseReport m_reports[SCE_HID_MAX_REPORT];
పూర్ణాంకం mouse_hid_handle = 0;
Uint8 prev_buttons = 0;

శూన్య VITA_InitMouse(శూన్య)
{
    sceHidMouseEnumerate(&mouse_hid_handle, 1);

    ఒకవేళ (mouse_hid_handle > 0) {
        SDL_కూడు_Mouse((SDL_MouseID)mouse_hid_handle, ఖాళీ);
    }
}

శూన్య VITA_PollMouse(శూన్య)
{
    // We skip polling mouse if no window is created
    ఒకవేళ (!Vita_కిటికీ) {
        తిరిగి;
    }

    ఒకవేళ (mouse_hid_handle > 0) {
        SDL_MouseID mouseID = (SDL_MouseID)mouse_hid_handle;
        పూర్ణాంకం అంకె_Reports = sceHidMouseRead(mouse_hid_handle, (SceHidMouseReport **)&m_reports, SCE_HID_MAX_REPORT);
        ఒకవేళ (అంకె_Reports > 0) {
            కొరకు (పూర్ణాంకం i = 0; i <= అంకె_Reports - 1; i++) {
                Uint8 మారింది_buttons = m_reports[i].buttons ^ prev_buttons;

                ఒకవేళ (మారింది_buttons & 0x1) {
                    ఒకవేళ (prev_buttons & 0x1)
                        SDL_SendMouseButton(0, Vita_కిటికీ, mouseID, SDL_BUTTON_ఎడమ, false);
                    లేకపోతే
                        SDL_SendMouseButton(0, Vita_కిటికీ, mouseID, SDL_BUTTON_ఎడమ, true);
                }
                ఒకవేళ (మారింది_buttons & 0x2) {
                    ఒకవేళ (prev_buttons & 0x2)
                        SDL_SendMouseButton(0, Vita_కిటికీ, mouseID, SDL_BUTTON_కుడి, false);
                    లేకపోతే
                        SDL_SendMouseButton(0, Vita_కిటికీ, mouseID, SDL_BUTTON_కుడి, true);
                }
                ఒకవేళ (మారింది_buttons & 0x4) {
                    ఒకవేళ (prev_buttons & 0x4)
                        SDL_SendMouseButton(0, Vita_కిటికీ, mouseID, SDL_BUTTON_మధ్య, false);
                    లేకపోతే
                        SDL_SendMouseButton(0, Vita_కిటికీ, mouseID, SDL_BUTTON_మధ్య, true);
                }
                ఒకవేళ (మారింది_buttons & 0x8) {
                    ఒకవేళ (prev_buttons & 0x8)
                        SDL_SendMouseButton(0, Vita_కిటికీ, mouseID, SDL_BUTTON_X1, false);
                    లేకపోతే
                        SDL_SendMouseButton(0, Vita_కిటికీ, mouseID, SDL_BUTTON_X1, true);
                }
                ఒకవేళ (మారింది_buttons & 0x10) {
                    ఒకవేళ (prev_buttons & 0x10)
                        SDL_SendMouseButton(0, Vita_కిటికీ, mouseID, SDL_BUTTON_X2, false);
                    లేకపోతే
                        SDL_SendMouseButton(0, Vita_కిటికీ, mouseID, SDL_BUTTON_X2, true);
                }

                prev_buttons = m_reports[i].buttons;

                ఒకవేళ (m_reports[i].rel_x || m_reports[i].rel_y) {
                    SDL_SendMouseMotion(0, Vita_కిటికీ, mouseID, true, (దశాంశం)m_reports[i].rel_x, (దశాంశం)m_reports[i].rel_y);
                }

                ఒకవేళ (m_reports[i].tilt != 0 || m_reports[i].wheel != 0) {
                    SDL_SendMouseWheel(0, Vita_కిటికీ, mouseID, m_reports[i].tilt, m_reports[i].wheel, SDL_MOUSEWHEEL_సాధారణ);
                }
            }
        }
    }
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_VITA

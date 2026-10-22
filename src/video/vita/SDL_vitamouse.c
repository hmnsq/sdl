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

#ifdef SDL_VIDEO_DRIVER_VITA

#ضمن <psp2/kernel/processmgr.h>
#ضمن <psp2/ctrl.h>
#ضمن <psp2/hid.h>

#ضمن "SDL_vitavideo.h"
#ضمن "SDL_vitamouse_c.h"
#ضمن "../../events/SDL_mouse_c.h"

SceHidMouseReport m_reports[SCE_HID_MAX_REPORT];
صحيح mouse_hid_handle = 0;
Uint8 prev_buttons = 0;

فراغ VITA_InitMouse(فراغ)
{
    sceHidMouseEnumerate(&mouse_hid_handle, 1);

    إذا (mouse_hid_handle > 0) {
        SDL_AddMouse((SDL_MouseID)mouse_hid_handle, عدم);
    }
}

فراغ VITA_PollMouse(فراغ)
{
    // We skip polling mouse if no window is created
    إذا (!Vita_Window) {
        أرجع;
    }

    إذا (mouse_hid_handle > 0) {
        SDL_MouseID mouseID = (SDL_MouseID)mouse_hid_handle;
        صحيح رقم_Reports = sceHidMouseRead(mouse_hid_handle, (SceHidMouseReport **)&m_reports, SCE_HID_MAX_REPORT);
        إذا (رقم_Reports > 0) {
            لكل (صحيح i = 0; i <= رقم_Reports - 1; i++) {
                Uint8 changed_buttons = m_reports[i].buttons ^ prev_buttons;

                إذا (changed_buttons & 0x1) {
                    إذا (prev_buttons & 0x1)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_يسار, false);
                    وإلا
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_يسار, true);
                }
                إذا (changed_buttons & 0x2) {
                    إذا (prev_buttons & 0x2)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_يمين, false);
                    وإلا
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_يمين, true);
                }
                إذا (changed_buttons & 0x4) {
                    إذا (prev_buttons & 0x4)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_وسط, false);
                    وإلا
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_وسط, true);
                }
                إذا (changed_buttons & 0x8) {
                    إذا (prev_buttons & 0x8)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_X1, false);
                    وإلا
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_X1, true);
                }
                إذا (changed_buttons & 0x10) {
                    إذا (prev_buttons & 0x10)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_X2, false);
                    وإلا
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_X2, true);
                }

                prev_buttons = m_reports[i].buttons;

                إذا (m_reports[i].rel_x || m_reports[i].rel_y) {
                    SDL_SendMouseMotion(0, Vita_Window, mouseID, true, (عائم)m_reports[i].rel_x, (عائم)m_reports[i].rel_y);
                }

                إذا (m_reports[i].tilt != 0 || m_reports[i].wheel != 0) {
                    SDL_SendMouseWheel(0, Vita_Window, mouseID, m_reports[i].tilt, m_reports[i].wheel, SDL_MOUSEWHEEL_NORMAL);
                }
            }
        }
    }
}

#endif // SDL_VIDEO_DRIVER_VITA

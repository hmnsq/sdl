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

#ifdef SDL_VIDEO_DRIVER_VITA

#अन्तर्भाव <psp2/kernel/processmgr.h>
#अन्तर्भाव <psp2/ctrl.h>
#अन्तर्भाव <psp2/hid.h>

#अन्तर्भाव "SDL_vitavideo.h"
#अन्तर्भाव "SDL_vitamouse_c.h"
#अन्तर्भाव "../../events/SDL_mouse_c.h"

SceHidMouseReport m_reports[SCE_HID_MAX_REPORT];
पूर्णाङ्क mouse_hid_handle = 0;
Uint8 prev_buttons = 0;

शून्य VITA_InitMouse(शून्य)
{
    sceHidMouseEnumerate(&mouse_hid_handle, 1);

    सचे (mouse_hid_handle > 0) {
        SDL_AddMouse((SDL_MouseID)mouse_hid_handle, रिक्त);
    }
}

शून्य VITA_PollMouse(शून्य)
{
    // We skip polling mouse if no window is created
    सचे (!Vita_Window) {
        पटिनिवत्त;
    }

    सचे (mouse_hid_handle > 0) {
        SDL_MouseID mouseID = (SDL_MouseID)mouse_hid_handle;
        पूर्णाङ्क अङ्कः_Reports = sceHidMouseRead(mouse_hid_handle, (SceHidMouseReport **)&m_reports, SCE_HID_MAX_REPORT);
        सचे (अङ्कः_Reports > 0) {
            अत्थाय (पूर्णाङ्क i = 0; i <= अङ्कः_Reports - 1; i++) {
                Uint8 changed_buttons = m_reports[i].buttons ^ prev_buttons;

                सचे (changed_buttons & 0x1) {
                    सचे (prev_buttons & 0x1)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_वामः, false);
                    अञ्ञथा
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_वामः, true);
                }
                सचे (changed_buttons & 0x2) {
                    सचे (prev_buttons & 0x2)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_दक्षिणः, false);
                    अञ्ञथा
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_दक्षिणः, true);
                }
                सचे (changed_buttons & 0x4) {
                    सचे (prev_buttons & 0x4)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_मध्यः, false);
                    अञ्ञथा
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_मध्यः, true);
                }
                सचे (changed_buttons & 0x8) {
                    सचे (prev_buttons & 0x8)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_X1, false);
                    अञ्ञथा
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_X1, true);
                }
                सचे (changed_buttons & 0x10) {
                    सचे (prev_buttons & 0x10)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_X2, false);
                    अञ्ञथा
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_X2, true);
                }

                prev_buttons = m_reports[i].buttons;

                सचे (m_reports[i].rel_x || m_reports[i].rel_y) {
                    SDL_SendMouseMotion(0, Vita_Window, mouseID, true, (भिन्न)m_reports[i].rel_x, (भिन्न)m_reports[i].rel_y);
                }

                सचे (m_reports[i].tilt != 0 || m_reports[i].wheel != 0) {
                    SDL_SendMouseWheel(0, Vita_Window, mouseID, m_reports[i].tilt, m_reports[i].wheel, SDL_MOUSEWHEEL_NORMAL);
                }
            }
        }
    }
}

#endif // SDL_VIDEO_DRIVER_VITA

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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_VITA

#समावेश <psp2/kernel/processmgr.h>
#समावेश <psp2/ctrl.h>
#समावेश <psp2/hid.h>

#समावेश "SDL_vitavideo.h"
#समावेश "SDL_vitamouse_c.h"
#समावेश "../../events/SDL_mouse_c.h"

SceHidMouseReport m_reports[SCE_HID_MAX_REPORT];
पूर्णांक mouse_hid_handle = 0;
Uint8 पूर्व_buttons = 0;

व्योम VITA_InitMouse(व्योम)
{
    sceHidMouseEnumerate(&mouse_hid_handle, 1);

    अगर (mouse_hid_handle > 0) {
        SDL_AddMouse((SDL_MouseID)mouse_hid_handle, शून्य);
    }
}

व्योम VITA_PollMouse(व्योम)
{
    // We skip polling mouse if no window is created
    अगर (!Vita_Window) {
        वापस;
    }

    अगर (mouse_hid_handle > 0) {
        SDL_MouseID mouseID = (SDL_MouseID)mouse_hid_handle;
        पूर्णांक अंक_Reports = sceHidMouseRead(mouse_hid_handle, (SceHidMouseReport **)&m_reports, SCE_HID_MAX_REPORT);
        अगर (अंक_Reports > 0) {
            क्रम (पूर्णांक i = 0; i <= अंक_Reports - 1; i++) {
                Uint8 changed_buttons = m_reports[i].buttons ^ पूर्व_buttons;

                अगर (changed_buttons & 0x1) {
                    अगर (पूर्व_buttons & 0x1)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_बायाँ, false);
                    अन्यथा
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_बायाँ, true);
                }
                अगर (changed_buttons & 0x2) {
                    अगर (पूर्व_buttons & 0x2)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_दायाँ, false);
                    अन्यथा
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_दायाँ, true);
                }
                अगर (changed_buttons & 0x4) {
                    अगर (पूर्व_buttons & 0x4)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_मध्य, false);
                    अन्यथा
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_मध्य, true);
                }
                अगर (changed_buttons & 0x8) {
                    अगर (पूर्व_buttons & 0x8)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_X1, false);
                    अन्यथा
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_X1, true);
                }
                अगर (changed_buttons & 0x10) {
                    अगर (पूर्व_buttons & 0x10)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_X2, false);
                    अन्यथा
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_X2, true);
                }

                पूर्व_buttons = m_reports[i].buttons;

                अगर (m_reports[i].rel_x || m_reports[i].rel_y) {
                    SDL_SendMouseMotion(0, Vita_Window, mouseID, true, (भग्न)m_reports[i].rel_x, (भग्न)m_reports[i].rel_y);
                }

                अगर (m_reports[i].tilt != 0 || m_reports[i].wheel != 0) {
                    SDL_SendMouseWheel(0, Vita_Window, mouseID, m_reports[i].tilt, m_reports[i].wheel, SDL_MOUSEWHEEL_NORMAL);
                }
            }
        }
    }
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_VITA

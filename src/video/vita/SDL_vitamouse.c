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
#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VITA

#অন্তর্ভাব <psp2/kernel/processmgr.h>
#অন্তর্ভাব <psp2/ctrl.h>
#অন্তর্ভাব <psp2/hid.h>

#অন্তর্ভাব "SDL_vitavideo.h"
#অন্তর্ভাব "SDL_vitamouse_c.h"
#অন্তর্ভাব "../../events/SDL_mouse_c.h"

SceHidMouseReport m_reports[SCE_HID_MAX_REPORT];
পূর্ণাঙ্ক mouse_hid_handle = 0;
Uint8 prev_buttons = 0;

শূন্য VITA_InitMouse(শূন্য)
{
    sceHidMouseEnumerate(&mouse_hid_handle, 1);

    যদি (mouse_hid_handle > 0) {
        SDL_AddMouse((SDL_MouseID)mouse_hid_handle, রিক্ত);
    }
}

শূন্য VITA_PollMouse(শূন্য)
{
    // We skip polling mouse if no window is created
    যদি (!Vita_Window) {
        প্রত্যাগম;
    }

    যদি (mouse_hid_handle > 0) {
        SDL_MouseID mouseID = (SDL_MouseID)mouse_hid_handle;
        পূর্ণাঙ্ক অঙ্ক_Reports = sceHidMouseRead(mouse_hid_handle, (SceHidMouseReport **)&m_reports, SCE_HID_MAX_REPORT);
        যদি (অঙ্ক_Reports > 0) {
            প্রতি (পূর্ণাঙ্ক i = 0; i <= অঙ্ক_Reports - 1; i++) {
                Uint8 changed_buttons = m_reports[i].buttons ^ prev_buttons;

                যদি (changed_buttons & 0x1) {
                    যদি (prev_buttons & 0x1)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_বাম, false);
                    অন্যথা
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_বাম, true);
                }
                যদি (changed_buttons & 0x2) {
                    যদি (prev_buttons & 0x2)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_ডান, false);
                    অন্যথা
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_ডান, true);
                }
                যদি (changed_buttons & 0x4) {
                    যদি (prev_buttons & 0x4)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_মধ্য, false);
                    অন্যথা
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_মধ্য, true);
                }
                যদি (changed_buttons & 0x8) {
                    যদি (prev_buttons & 0x8)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_X1, false);
                    অন্যথা
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_X1, true);
                }
                যদি (changed_buttons & 0x10) {
                    যদি (prev_buttons & 0x10)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_X2, false);
                    অন্যথা
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_X2, true);
                }

                prev_buttons = m_reports[i].buttons;

                যদি (m_reports[i].rel_x || m_reports[i].rel_y) {
                    SDL_SendMouseMotion(0, Vita_Window, mouseID, true, (ভিন্ন)m_reports[i].rel_x, (ভিন্ন)m_reports[i].rel_y);
                }

                যদি (m_reports[i].tilt != 0 || m_reports[i].wheel != 0) {
                    SDL_SendMouseWheel(0, Vita_Window, mouseID, m_reports[i].tilt, m_reports[i].wheel, SDL_MOUSEWHEEL_NORMAL);
                }
            }
        }
    }
}

#endif // SDL_VIDEO_DRIVER_VITA

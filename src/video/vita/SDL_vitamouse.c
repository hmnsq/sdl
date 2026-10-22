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
#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VITA

#அந்தர்பாவ <psp2/kernel/processmgr.h>
#அந்தர்பாவ <psp2/ctrl.h>
#அந்தர்பாவ <psp2/hid.h>

#அந்தர்பாவ "SDL_vitavideo.h"
#அந்தர்பாவ "SDL_vitamouse_c.h"
#அந்தர்பாவ "../../events/SDL_mouse_c.h"

SceHidMouseReport m_reports[SCE_HID_MAX_REPORT];
முழு mouse_hid_handle = 0;
Uint8 prev_buttons = 0;

வெறுமை VITA_InitMouse(வெறுமை)
{
    sceHidMouseEnumerate(&mouse_hid_handle, 1);

    எனில் (mouse_hid_handle > 0) {
        SDL_AddMouse((SDL_MouseID)mouse_hid_handle, வெற்று);
    }
}

வெறுமை VITA_PollMouse(வெறுமை)
{
    // We skip polling mouse if no window is created
    எனில் (!Vita_Window) {
        திரும்பு;
    }

    எனில் (mouse_hid_handle > 0) {
        SDL_MouseID mouseID = (SDL_MouseID)mouse_hid_handle;
        முழு இலக்கம்_Reports = sceHidMouseRead(mouse_hid_handle, (SceHidMouseReport **)&m_reports, SCE_HID_MAX_REPORT);
        எனில் (இலக்கம்_Reports > 0) {
            க்கு (முழு i = 0; i <= இலக்கம்_Reports - 1; i++) {
                Uint8 changed_buttons = m_reports[i].buttons ^ prev_buttons;

                எனில் (changed_buttons & 0x1) {
                    எனில் (prev_buttons & 0x1)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_இடது, false);
                    இல்லையெனில்
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_இடது, true);
                }
                எனில் (changed_buttons & 0x2) {
                    எனில் (prev_buttons & 0x2)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_வலது, false);
                    இல்லையெனில்
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_வலது, true);
                }
                எனில் (changed_buttons & 0x4) {
                    எனில் (prev_buttons & 0x4)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_நடு, false);
                    இல்லையெனில்
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_நடு, true);
                }
                எனில் (changed_buttons & 0x8) {
                    எனில் (prev_buttons & 0x8)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_X1, false);
                    இல்லையெனில்
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_X1, true);
                }
                எனில் (changed_buttons & 0x10) {
                    எனில் (prev_buttons & 0x10)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_X2, false);
                    இல்லையெனில்
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_X2, true);
                }

                prev_buttons = m_reports[i].buttons;

                எனில் (m_reports[i].rel_x || m_reports[i].rel_y) {
                    SDL_SendMouseMotion(0, Vita_Window, mouseID, true, (தசம)m_reports[i].rel_x, (தசம)m_reports[i].rel_y);
                }

                எனில் (m_reports[i].tilt != 0 || m_reports[i].wheel != 0) {
                    SDL_SendMouseWheel(0, Vita_Window, mouseID, m_reports[i].tilt, m_reports[i].wheel, SDL_MOUSEWHEEL_NORMAL);
                }
            }
        }
    }
}

#endif // SDL_VIDEO_DRIVER_VITA

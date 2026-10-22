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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_VITA

#ਅਨ੍ਤਰ੍ਭਾਵ <psp2/kernel/processmgr.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <psp2/ctrl.h>
#ਅਨ੍ਤਰ੍ਭਾਵ <psp2/hid.h>

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_vitavideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_vitamouse_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_mouse_c.h"

SceHidMouseReport m_reports[SCE_HID_MAX_REPORT];
ਪੂਰਨ mouse_hid_handle = 0;
Uint8 prev_buttons = 0;

ਖਾਲੀ VITA_InitMouse(ਖਾਲੀ)
{
    sceHidMouseEnumerate(&mouse_hid_handle, 1);

    ਜੇ (mouse_hid_handle > 0) {
        SDL_ਜੋੜੋ_Mouse((SDL_MouseID)mouse_hid_handle, ਨਿਰਾ);
    }
}

ਖਾਲੀ VITA_PollMouse(ਖਾਲੀ)
{
    // We skip polling mouse if no window is created
    ਜੇ (!Vita_ਖਿੜਕੀ) {
        ਵਾਪਸ;
    }

    ਜੇ (mouse_hid_handle > 0) {
        SDL_MouseID mouseID = (SDL_MouseID)mouse_hid_handle;
        ਪੂਰਨ ਅੰਕ_Reports = sceHidMouseRead(mouse_hid_handle, (SceHidMouseReport **)&m_reports, SCE_HID_MAX_REPORT);
        ਜੇ (ਅੰਕ_Reports > 0) {
            ਲਈ (ਪੂਰਨ i = 0; i <= ਅੰਕ_Reports - 1; i++) {
                Uint8 ਬਦਲਿਆ_buttons = m_reports[i].buttons ^ prev_buttons;

                ਜੇ (ਬਦਲਿਆ_buttons & 0x1) {
                    ਜੇ (prev_buttons & 0x1)
                        SDL_SendMouseButton(0, Vita_ਖਿੜਕੀ, mouseID, SDL_BUTTON_ਖੱਬਾ, false);
                    ਨਹੀਂਤਾਂ
                        SDL_SendMouseButton(0, Vita_ਖਿੜਕੀ, mouseID, SDL_BUTTON_ਖੱਬਾ, true);
                }
                ਜੇ (ਬਦਲਿਆ_buttons & 0x2) {
                    ਜੇ (prev_buttons & 0x2)
                        SDL_SendMouseButton(0, Vita_ਖਿੜਕੀ, mouseID, SDL_BUTTON_ਸੱਜਾ, false);
                    ਨਹੀਂਤਾਂ
                        SDL_SendMouseButton(0, Vita_ਖਿੜਕੀ, mouseID, SDL_BUTTON_ਸੱਜਾ, true);
                }
                ਜੇ (ਬਦਲਿਆ_buttons & 0x4) {
                    ਜੇ (prev_buttons & 0x4)
                        SDL_SendMouseButton(0, Vita_ਖਿੜਕੀ, mouseID, SDL_BUTTON_ਵਿਚਕਾਰ, false);
                    ਨਹੀਂਤਾਂ
                        SDL_SendMouseButton(0, Vita_ਖਿੜਕੀ, mouseID, SDL_BUTTON_ਵਿਚਕਾਰ, true);
                }
                ਜੇ (ਬਦਲਿਆ_buttons & 0x8) {
                    ਜੇ (prev_buttons & 0x8)
                        SDL_SendMouseButton(0, Vita_ਖਿੜਕੀ, mouseID, SDL_BUTTON_X1, false);
                    ਨਹੀਂਤਾਂ
                        SDL_SendMouseButton(0, Vita_ਖਿੜਕੀ, mouseID, SDL_BUTTON_X1, true);
                }
                ਜੇ (ਬਦਲਿਆ_buttons & 0x10) {
                    ਜੇ (prev_buttons & 0x10)
                        SDL_SendMouseButton(0, Vita_ਖਿੜਕੀ, mouseID, SDL_BUTTON_X2, false);
                    ਨਹੀਂਤਾਂ
                        SDL_SendMouseButton(0, Vita_ਖਿੜਕੀ, mouseID, SDL_BUTTON_X2, true);
                }

                prev_buttons = m_reports[i].buttons;

                ਜੇ (m_reports[i].rel_x || m_reports[i].rel_y) {
                    SDL_SendMouseMotion(0, Vita_ਖਿੜਕੀ, mouseID, true, (ਦਸ਼ਮਲਵ)m_reports[i].rel_x, (ਦਸ਼ਮਲਵ)m_reports[i].rel_y);
                }

                ਜੇ (m_reports[i].tilt != 0 || m_reports[i].wheel != 0) {
                    SDL_SendMouseWheel(0, Vita_ਖਿੜਕੀ, mouseID, m_reports[i].tilt, m_reports[i].wheel, SDL_MOUSEWHEEL_ਸਾਧਾਰਨ);
                }
            }
        }
    }
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_VITA

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
#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_VITA

#شامل <psp2/kernel/processmgr.h>
#شامل <psp2/ctrl.h>
#شامل <psp2/hid.h>

#شامل "SDL_vitavideo.h"
#شامل "SDL_vitamouse_c.h"
#شامل "../../events/SDL_mouse_c.h"

SceHidMouseReport m_reports[SCE_HID_MAX_REPORT];
صحیح mouse_hid_handle = 0;
Uint8 پچھلا_buttons = 0;

خالی VITA_InitMouse(خالی)
{
    sceHidMouseEnumerate(&mouse_hid_handle, 1);

    اگر (mouse_hid_handle > 0) {
        SDL_جوڑو_Mouse((SDL_MouseID)mouse_hid_handle, تہی);
    }
}

خالی VITA_PollMouse(خالی)
{
    // We skip polling mouse if no window is created
    اگر (!Vita_کھڑکی) {
        واپس;
    }

    اگر (mouse_hid_handle > 0) {
        SDL_MouseID mouseID = (SDL_MouseID)mouse_hid_handle;
        صحیح عدد_Reports = sceHidMouseRead(mouse_hid_handle, (SceHidMouseReport **)&m_reports, SCE_HID_MAX_REPORT);
        اگر (عدد_Reports > 0) {
            برائے (صحیح i = 0; i <= عدد_Reports - 1; i++) {
                Uint8 بدلا_buttons = m_reports[i].buttons ^ پچھلا_buttons;

                اگر (بدلا_buttons & 0x1) {
                    اگر (پچھلا_buttons & 0x1)
                        SDL_SendMouseButton(0, Vita_کھڑکی, mouseID, SDL_BUTTON_بایاں, false);
                    ورنہ
                        SDL_SendMouseButton(0, Vita_کھڑکی, mouseID, SDL_BUTTON_بایاں, true);
                }
                اگر (بدلا_buttons & 0x2) {
                    اگر (پچھلا_buttons & 0x2)
                        SDL_SendMouseButton(0, Vita_کھڑکی, mouseID, SDL_BUTTON_دایاں, false);
                    ورنہ
                        SDL_SendMouseButton(0, Vita_کھڑکی, mouseID, SDL_BUTTON_دایاں, true);
                }
                اگر (بدلا_buttons & 0x4) {
                    اگر (پچھلا_buttons & 0x4)
                        SDL_SendMouseButton(0, Vita_کھڑکی, mouseID, SDL_BUTTON_درمیان, false);
                    ورنہ
                        SDL_SendMouseButton(0, Vita_کھڑکی, mouseID, SDL_BUTTON_درمیان, true);
                }
                اگر (بدلا_buttons & 0x8) {
                    اگر (پچھلا_buttons & 0x8)
                        SDL_SendMouseButton(0, Vita_کھڑکی, mouseID, SDL_BUTTON_X1, false);
                    ورنہ
                        SDL_SendMouseButton(0, Vita_کھڑکی, mouseID, SDL_BUTTON_X1, true);
                }
                اگر (بدلا_buttons & 0x10) {
                    اگر (پچھلا_buttons & 0x10)
                        SDL_SendMouseButton(0, Vita_کھڑکی, mouseID, SDL_BUTTON_X2, false);
                    ورنہ
                        SDL_SendMouseButton(0, Vita_کھڑکی, mouseID, SDL_BUTTON_X2, true);
                }

                پچھلا_buttons = m_reports[i].buttons;

                اگر (m_reports[i].rel_x || m_reports[i].rel_y) {
                    SDL_SendMouseMotion(0, Vita_کھڑکی, mouseID, true, (اعشاری)m_reports[i].rel_x, (اعشاری)m_reports[i].rel_y);
                }

                اگر (m_reports[i].tilt != 0 || m_reports[i].wheel != 0) {
                    SDL_SendMouseWheel(0, Vita_کھڑکی, mouseID, m_reports[i].tilt, m_reports[i].wheel, SDL_MOUSEWHEEL_معمول);
                }
            }
        }
    }
}

#اگر_ختم // SDL_VIDEO_DRIVER_VITA

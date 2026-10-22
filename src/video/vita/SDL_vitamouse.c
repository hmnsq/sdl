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
#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_VITA

#അന്തര്ഭാവ <psp2/kernel/processmgr.h>
#അന്തര്ഭാവ <psp2/ctrl.h>
#അന്തര്ഭാവ <psp2/hid.h>

#അന്തര്ഭാവ "SDL_vitavideo.h"
#അന്തര്ഭാവ "SDL_vitamouse_c.h"
#അന്തര്ഭാവ "../../events/SDL_mouse_c.h"

SceHidMouseReport m_reports[SCE_HID_MAX_REPORT];
പൂർണ്ണസംഖ്യ mouse_hid_handle = 0;
Uint8 prev_buttons = 0;

ശൂന്യം VITA_InitMouse(ശൂന്യം)
{
    sceHidMouseEnumerate(&mouse_hid_handle, 1);

    എങ്കിൽ (mouse_hid_handle > 0) {
        SDL_AddMouse((SDL_MouseID)mouse_hid_handle, ശൂന്യ);
    }
}

ശൂന്യം VITA_PollMouse(ശൂന്യം)
{
    // We skip polling mouse if no window is created
    എങ്കിൽ (!Vita_Window) {
        തിരികെ;
    }

    എങ്കിൽ (mouse_hid_handle > 0) {
        SDL_MouseID mouseID = (SDL_MouseID)mouse_hid_handle;
        പൂർണ്ണസംഖ്യ അക്കം_Reports = sceHidMouseRead(mouse_hid_handle, (SceHidMouseReport **)&m_reports, SCE_HID_MAX_REPORT);
        എങ്കിൽ (അക്കം_Reports > 0) {
            വേണ്ടി (പൂർണ്ണസംഖ്യ i = 0; i <= അക്കം_Reports - 1; i++) {
                Uint8 changed_buttons = m_reports[i].buttons ^ prev_buttons;

                എങ്കിൽ (changed_buttons & 0x1) {
                    എങ്കിൽ (prev_buttons & 0x1)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_ഇടത്, false);
                    അല്ലെങ്കിൽ
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_ഇടത്, true);
                }
                എങ്കിൽ (changed_buttons & 0x2) {
                    എങ്കിൽ (prev_buttons & 0x2)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_വലത്, false);
                    അല്ലെങ്കിൽ
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_വലത്, true);
                }
                എങ്കിൽ (changed_buttons & 0x4) {
                    എങ്കിൽ (prev_buttons & 0x4)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_നടുവ്, false);
                    അല്ലെങ്കിൽ
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_നടുവ്, true);
                }
                എങ്കിൽ (changed_buttons & 0x8) {
                    എങ്കിൽ (prev_buttons & 0x8)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_X1, false);
                    അല്ലെങ്കിൽ
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_X1, true);
                }
                എങ്കിൽ (changed_buttons & 0x10) {
                    എങ്കിൽ (prev_buttons & 0x10)
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_X2, false);
                    അല്ലെങ്കിൽ
                        SDL_SendMouseButton(0, Vita_Window, mouseID, SDL_BUTTON_X2, true);
                }

                prev_buttons = m_reports[i].buttons;

                എങ്കിൽ (m_reports[i].rel_x || m_reports[i].rel_y) {
                    SDL_SendMouseMotion(0, Vita_Window, mouseID, true, (ദശാംശം)m_reports[i].rel_x, (ദശാംശം)m_reports[i].rel_y);
                }

                എങ്കിൽ (m_reports[i].tilt != 0 || m_reports[i].wheel != 0) {
                    SDL_SendMouseWheel(0, Vita_Window, mouseID, m_reports[i].tilt, m_reports[i].wheel, SDL_MOUSEWHEEL_NORMAL);
                }
            }
        }
    }
}

#endif // SDL_VIDEO_DRIVER_VITA

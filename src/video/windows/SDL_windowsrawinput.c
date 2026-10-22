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

#ಆದರೆ defined(SDL_VIDEO_DRIVER_WINDOWS)

#ಅನ್ತರ್ಭಾವ "SDL_windowsvideo.h"

#ಆದರೆ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ಅನ್ತರ್ಭಾವ "SDL_windowsevents.h"

#ಅನ್ತರ್ಭಾವ "../../joystick/usb_ids.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_events_c.h"
#ಅನ್ತರ್ಭಾವ "../../thread/SDL_systhread.h"

#ವ್ಯಾಖ್ಯಾನಿಸು ENABLE_RAW_MOUSE_ಒಳಹರಿವು      0x01
#ವ್ಯಾಖ್ಯಾನಿಸು RAW_MOUSE_FLAG_NOLEGACY     0x02
#ವ್ಯಾಖ್ಯಾನಿಸು ENABLE_RAW_KEYBOARD_ಒಳಹರಿವು   0x10
#ವ್ಯಾಖ್ಯಾನಿಸು RAW_KEYBOARD_FLAG_NOHOTKEYS 0x20
#ವ್ಯಾಖ್ಯಾನಿಸು RAW_KEYBOARD_FLAG_INPUTSINK 0x40

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ
{
    bool ಮುಗಿದ;
    SDL_AtomicU32 flags; // Thread sets this to the actually-set flags if updating state failed
    HANDLE ready_event;
    HANDLE signal_event;
    HANDLE thread;
} Raw_ಒಳಹರಿವು_Thread_ದತ್ತಾಂಶ;

ಸ್ಥಿರ Raw_ಒಳಹರಿವು_Thread_ದತ್ತಾಂಶ thread_ದತ್ತಾಂಶ = { 0 };

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ
{
    RINP_QUIT,
    RINP_UPDATE,
    RINP_CONTINUE
} Raw_ಒಳಹರಿವು_Iterate_ಫಲಿತಾಂಶ;

ಸ್ಥಿರ Raw_ಒಳಹರಿವು_Iterate_ಫಲಿತಾಂಶ Iterate_Raw_ಒಳಹರಿವು_Thread(ಶೂನ್ಯ)
{
    // The high-order word of GetQueueStatus() will let us know if there's immediate raw input to be processed.
    // A (necessary!) side effect is that it also marks the message queue bits as stale,
    // so MsgWaitForMultipleObjects will block.

    // Any pending flag update won't be processed until the queue drains, but this is
    // at most one poll cycle since GetQueueStatus clears the wake bits.
    ಆದರೆ (HIWORD(Get_ಸರತಿ_ಸ್ಥಿತಿ(QS_RAWINPUT)) & QS_RAWINPUT) {
        ಹಿಂತಿರುಗಿ thread_ದತ್ತಾಂಶ.ಮುಗಿದ ? RINP_QUIT : RINP_CONTINUE;
    }

    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ DWORD WAIT_SIGNAL = WAIT_OBJECT_0;
    ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ DWORD WAIT_ಒಳಹರಿವು = WAIT_OBJECT_0 + 1;

    // There wasn't anything, so we'll wait until new data (or signal_event) wakes us up.
    DWORD wait_ಸ್ಥಿತಿ = ಸಂದೇಶ_Wait_For_ಅಪವರ್ತ್ಯ_Objects(1, &thread_ದತ್ತಾಂಶ.signal_event, FALSE, INFINITE, QS_RAWINPUT);
    ಆದರೆ (wait_ಸ್ಥಿತಿ == WAIT_SIGNAL) {
        // signal_event can only be set if we need to update or quit.
        ಹಿಂತಿರುಗಿ thread_ದತ್ತಾಂಶ.ಮುಗಿದ ? RINP_QUIT : RINP_UPDATE;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (wait_ಸ್ಥಿತಿ == WAIT_ಒಳಹರಿವು) {
        ಹಿಂತಿರುಗಿ RINP_CONTINUE;
    } ಇಲ್ಲದಿದ್ದರೆ {
        SDL_LogWarn(SDL_LOG_CATEGORY_ಒಳಹರಿವು, "Raw input thread exiting, unexpected wait result: %" SDL_PRIuULONG, wait_ಸ್ಥಿತಿ);
        ಹಿಂತಿರುಗಿ RINP_QUIT;
    }
}

ಸ್ಥಿರ bool Update_Raw_ಒಳಹರಿವು_Device_Flags(HWND ಕಿಟಕಿ, Uint32 ಕೊನೆಯ_flags, Uint32 new_flags)
{
    // We had nothing enabled, and we're trying to stop everything. Nothing to do.
    ಆದರೆ (ಕೊನೆಯ_flags == new_flags) {
        ಹಿಂತಿರುಗಿ true;
    }

    RAWINPUTDEVICE devices[2] = { 0 };
    UINT ಎಣಿಕೆ_2 = 0;

    ಸ್ಥಿರಾಂಕ Uint32 old_mouse_flags = ಕೊನೆಯ_flags & (ENABLE_RAW_MOUSE_ಒಳಹರಿವು | RAW_MOUSE_FLAG_NOLEGACY);
    ಸ್ಥಿರಾಂಕ Uint32 new_mouse_flags = new_flags & (ENABLE_RAW_MOUSE_ಒಳಹರಿವು | RAW_MOUSE_FLAG_NOLEGACY);

    ಆದರೆ (old_mouse_flags != new_mouse_flags) {
        devices[ಎಣಿಕೆ_2].us_Usage_ಪುಟ = USB_USAGEPAGE_GENERIC_DESKTOP;
        devices[ಎಣಿಕೆ_2].usUsage = USB_USAGE_GENERIC_MOUSE;

        ಆದರೆ (new_flags & ENABLE_RAW_MOUSE_ಒಳಹರಿವು) {
            devices[ಎಣಿಕೆ_2].dwFlags = 0;
            devices[ಎಣಿಕೆ_2].hwnd_ಗುರಿ = ಕಿಟಕಿ;
            ಆದರೆ (new_mouse_flags & RAW_MOUSE_FLAG_NOLEGACY) {
                devices[ಎಣಿಕೆ_2].dwFlags |= RIDEV_NOLEGACY;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            devices[ಎಣಿಕೆ_2].dwFlags = RIDEV_REMOVE;
            devices[ಎಣಿಕೆ_2].hwnd_ಗುರಿ = ಖಾಲಿ;
        }

        ++ಎಣಿಕೆ_2;
    }

    ಸ್ಥಿರಾಂಕ Uint32 old_kb_flags = ಕೊನೆಯ_flags & (ENABLE_RAW_KEYBOARD_ಒಳಹರಿವು | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);
    ಸ್ಥಿರಾಂಕ Uint32 new_kb_flags = new_flags & (ENABLE_RAW_KEYBOARD_ಒಳಹರಿವು | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);

    ಆದರೆ (old_kb_flags != new_kb_flags) {
        devices[ಎಣಿಕೆ_2].us_Usage_ಪುಟ = USB_USAGEPAGE_GENERIC_DESKTOP;
        devices[ಎಣಿಕೆ_2].usUsage = USB_USAGE_GENERIC_KEYBOARD;

        ಆದರೆ (new_kb_flags & ENABLE_RAW_KEYBOARD_ಒಳಹರಿವು) {
            devices[ಎಣಿಕೆ_2].dwFlags = 0;
            devices[ಎಣಿಕೆ_2].hwnd_ಗುರಿ = ಕಿಟಕಿ;
            ಆದರೆ (new_kb_flags & RAW_KEYBOARD_FLAG_NOHOTKEYS) {
                devices[ಎಣಿಕೆ_2].dwFlags |= RIDEV_NOHOTKEYS;
            }
            ಆದರೆ (new_kb_flags & RAW_KEYBOARD_FLAG_INPUTSINK) {
                devices[ಎಣಿಕೆ_2].dwFlags |= RIDEV_INPUTSINK;
            }
        } ಇಲ್ಲದಿದ್ದರೆ {
            devices[ಎಣಿಕೆ_2].dwFlags = RIDEV_REMOVE;
            devices[ಎಣಿಕೆ_2].hwnd_ಗುರಿ = ಖಾಲಿ;
        }

        ++ಎಣಿಕೆ_2;
    }

    ಆದರೆ (ರಿಜಿಸ್ಟರ್_Raw_ಒಳಹರಿವು_Devices(devices, ಎಣಿಕೆ_2, ಗಾತ್ರ(devices[0]))) {
        ಹಿಂತಿರುಗಿ true;
    }
    ಹಿಂತಿರುಗಿ false;
}

ಸ್ಥಿರ DWORD WINAPI WIN_Raw_ಒಳಹರಿವು_Thread(LPVOID param)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    Uint32 ಕೊನೆಯ_flags = 0;
    HWND ಕಿಟಕಿ;

    SDL_SYS_ಸಿದ್ಧತೆ_Thread("SDLRawInput");

    ಕಿಟಕಿ = Create_ಕಿಟಕಿ_Ex(0, ಪಠ್ಯ_2("Message"), ಖಾಲಿ, 0, 0, 0, 0, 0, HWND_ಸಂದೇಶ, ಖಾಲಿ, ಖಾಲಿ, ಖಾಲಿ);
    ಆದರೆ (!ಕಿಟಕಿ) {
        ಹಿಂತಿರುಗಿ 0;
    }

    // This doesn't *really* need to be atomic, because the parent is waiting for us
    ಕೊನೆಯ_flags = SDL_GetAtomicU32(&thread_ದತ್ತಾಂಶ.flags);
    ಆದರೆ (!Update_Raw_ಒಳಹರಿವು_Device_Flags(ಕಿಟಕಿ, 0, ಕೊನೆಯ_flags)) {
        Destroy_ಕಿಟಕಿ(ಕಿಟಕಿ);
        ಹಿಂತಿರುಗಿ 0;
    }

    // Make sure we get events as soon as possible
    ಗಣ_Thread_ಆದ್ಯತೆ(GetCurrentThread(), THREAD_ಆದ್ಯತೆ_ಸಮಯ_CRITICAL);

    // Tell the parent we're ready to go!
    ಗಣ_Event(thread_ದತ್ತಾಂಶ.ready_event);

    Raw_ಒಳಹರಿವು_Iterate_ಫಲಿತಾಂಶ iter_ಫಲಿತಾಂಶ;

    Uint64 idle_begin = SDL_GetTicksNS();
    ಆಗ ((iter_ಫಲಿತಾಂಶ = Iterate_Raw_ಒಳಹರಿವು_Thread()) != RINP_QUIT) {
        ಆಯ್ಕೆ (iter_ಫಲಿತಾಂಶ) {
        ಸ್ಥಿತಿ RINP_QUIT: // Unreachable
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ RINP_UPDATE:
        {
            ಸ್ಥಿರಾಂಕ Uint32 new_flags = SDL_GetAtomicU32(&thread_ದತ್ತಾಂಶ.flags);
            ಆದರೆ (!Update_Raw_ಒಳಹರಿವು_Device_Flags(ಕಿಟಕಿ, ಕೊನೆಯ_flags, new_flags)) {
                // Revert the shared flags so the main thread can detect the failure
                SDL_ಗಣ_Atomic_U32(&thread_ದತ್ತಾಂಶ.flags, ಕೊನೆಯ_flags);
            } ಇಲ್ಲದಿದ್ದರೆ {
                ಕೊನೆಯ_flags = new_flags;
            }
        } ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ RINP_CONTINUE:
        {
            Uint64 idle_ಕೊನೆ = SDL_GetTicksNS();
            Uint64 idle_ಸಮಯ = idle_ಕೊನೆ - idle_begin;
            Uint64 usb_8khz_interval = SDL_US_ಗಮ್ಯ_NS(125);
            Uint64 poll_ಆರಂಭ = idle_ಸಮಯ < usb_8khz_interval ? _this->ಆಂತರಿಕ->ಕೊನೆಯ_rawinput_poll : idle_ಕೊನೆ;

            WIN_Poll_Raw_ಒಳಹರಿವು(_this, poll_ಆರಂಭ);

            // Reset idle_begin for the next go-around
            idle_begin = SDL_GetTicksNS();
        } ನಿಲ್ಲಿಸು;
        }
    }

    ಆದರೆ (_this->ಆಂತರಿಕ->raw_ಒಳಹರಿವು_fake_pen_id) {
        SDL_RemovePenDevice(0, SDL_GetKeyboardFocus(), _this->ಆಂತರಿಕ->raw_ಒಳಹರಿವು_fake_pen_id);
        _this->ಆಂತರಿಕ->raw_ಒಳಹರಿವು_fake_pen_id = 0;
    }

    // Reset this here, since if we're exiting due to failure, WIN_UpdateRawInputEnabled would see a stale value.
    SDL_ಗಣ_Atomic_U32(&thread_ದತ್ತಾಂಶ.flags, 0);

    Update_Raw_ಒಳಹರಿವು_Device_Flags(ಖಾಲಿ, ಕೊನೆಯ_flags, 0);

    Destroy_ಕಿಟಕಿ(ಕಿಟಕಿ);

    ಹಿಂತಿರುಗಿ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ Cleanup_Raw_ಒಳಹರಿವು_Thread_ದತ್ತಾಂಶ(ಶೂನ್ಯ)
{
    ಆದರೆ (thread_ದತ್ತಾಂಶ.thread) {
        thread_ದತ್ತಾಂಶ.ಮುಗಿದ = true;
        ಗಣ_Event(thread_ದತ್ತಾಂಶ.signal_event);
        WaitForSingleObject(thread_ದತ್ತಾಂಶ.thread, 3000);
        CloseHandle(thread_ದತ್ತಾಂಶ.thread);
    }

    ಆದರೆ (thread_ದತ್ತಾಂಶ.ready_event) {
        CloseHandle(thread_ದತ್ತಾಂಶ.ready_event);
    }

    ಆದರೆ (thread_ದತ್ತಾಂಶ.signal_event) {
        CloseHandle(thread_ದತ್ತಾಂಶ.signal_event);
    }

    thread_ದತ್ತಾಂಶ = (Raw_ಒಳಹರಿವು_Thread_ದತ್ತಾಂಶ){ 0 };
}

// Computes the desired raw input flags from SDL_VideoData and ensures the
// raw input thread's device registrations match.
// Creates the thread on first use, only WIN_QuitRawInput actually shuts it down.
ಸ್ಥಿರ bool WIN_Update_Raw_ಒಳಹರಿವು_Enabled(SDL_VideoDevice *_this)
{
    bool ಫಲಿತಾಂಶ = false;
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    Uint32 desired_flags = 0;

    ಆದರೆ (!ದತ್ತಾಂಶ->gameinput_context) {
        ಆದರೆ (ದತ್ತಾಂಶ->raw_mouse_enabled) {
            desired_flags |= ENABLE_RAW_MOUSE_ಒಳಹರಿವು;
            ಆದರೆ (ದತ್ತಾಂಶ->raw_mouse_flag_nolegacy) {
                desired_flags |= RAW_MOUSE_FLAG_NOLEGACY;
            }
        }
        ಆದರೆ (ದತ್ತಾಂಶ->raw_keyboard_enabled) {
            desired_flags |= ENABLE_RAW_KEYBOARD_ಒಳಹರಿವು;
            ಆದರೆ (ದತ್ತಾಂಶ->raw_keyboard_flag_nohotkeys) {
                desired_flags |= RAW_KEYBOARD_FLAG_NOHOTKEYS;
            }
            ಆದರೆ (ದತ್ತಾಂಶ->raw_keyboard_flag_inputsink) {
                desired_flags |= RAW_KEYBOARD_FLAG_INPUTSINK;
            }
        }
    }

    ಆದರೆ (desired_flags == SDL_GetAtomicU32(&thread_ದತ್ತಾಂಶ.flags)) {
        ಫಲಿತಾಂಶ = true;
        ಹೋಗು ಮುಗಿದ;
    }

    // If the thread exited unexpectedly (e.g. MsgWaitForMultipleObjects failed),
    // the handle is stale. Clean it up so the creation path below can recover.
    ಆದರೆ (thread_ದತ್ತಾಂಶ.thread && WaitForSingleObject(thread_ದತ್ತಾಂಶ.thread, 0) != WAIT_TIMEOUT) {
        Cleanup_Raw_ಒಳಹರಿವು_Thread_ದತ್ತಾಂಶ();
    }

    // The thread will read from this to update its flags
    SDL_ಗಣ_Atomic_U32(&thread_ದತ್ತಾಂಶ.flags, desired_flags);

    ಆದರೆ (thread_ದತ್ತಾಂಶ.thread) {
        // Thread is already running. Fire (the event) and forget, it'll read the atomic flags on wakeup.

        // If RegisterRawInputDevices fails, the thread reverts the atomic and the next call
        // to this function will see the mismatch and retry.
        SDL_assert(thread_ದತ್ತಾಂಶ.signal_event);
        ಗಣ_Event(thread_ದತ್ತಾಂಶ.signal_event);
        ಫಲಿತಾಂಶ = true;
    } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (desired_flags) {
        HANDLE wait_handles[2];

        // Thread isn't running, spin it up
        thread_ದತ್ತಾಂಶ.ready_event = CreateEvent(ಖಾಲಿ, FALSE, FALSE, ಖಾಲಿ);
        ಆದರೆ (!thread_ದತ್ತಾಂಶ.ready_event) {
            WIN_ಗಣ_Error("CreateEvent");
            ಹೋಗು ಮುಗಿದ;
        }

        thread_ದತ್ತಾಂಶ.ಮುಗಿದ = false;
        thread_ದತ್ತಾಂಶ.signal_event = CreateEvent(ಖಾಲಿ, FALSE, FALSE, ಖಾಲಿ);
        ಆದರೆ (!thread_ದತ್ತಾಂಶ.signal_event) {
            WIN_ಗಣ_Error("CreateEvent");
            ಹೋಗು ಮುಗಿದ;
        }

        thread_ದತ್ತಾಂಶ.thread = CreateThread(ಖಾಲಿ, 0, WIN_Raw_ಒಳಹರಿವು_Thread, ಖಾಲಿ, 0, ಖಾಲಿ);
        ಆದರೆ (!thread_ದತ್ತಾಂಶ.thread) {
            WIN_ಗಣ_Error("CreateThread");
            ಹೋಗು ಮುಗಿದ;
        }

        // Wait for the thread to complete initial setup or exit
        wait_handles[0] = thread_ದತ್ತಾಂಶ.ready_event;
        wait_handles[1] = thread_ದತ್ತಾಂಶ.thread;
        ಆದರೆ (Wait_For_ಅಪವರ್ತ್ಯ_Objects(2, wait_handles, FALSE, INFINITE) != WAIT_OBJECT_0) {
            SDL_ಗಣ_Error("Couldn't set up raw input handling");
            ಹೋಗು ಮುಗಿದ;
        }
        ಫಲಿತಾಂಶ = true;
    } ಇಲ್ಲದಿದ್ದರೆ {
        // Thread isn't running and we tried to disable raw input, nothing to do
        ಫಲಿತಾಂಶ = true;
    }
ಮುಗಿದ:
    ಆದರೆ (!ಫಲಿತಾಂಶ) {
        Cleanup_Raw_ಒಳಹರಿವು_Thread_ದತ್ತಾಂಶ();
    }
    ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

bool WIN_ಗಣ_Raw_Mouse_Enabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    ದತ್ತಾಂಶ->raw_mouse_enabled = enabled;
    ಆದರೆ (ದತ್ತಾಂಶ->gameinput_context) {
        ಆದರೆ (!WIN_Update_Game_ಒಳಹರಿವು_Enabled(_this)) {
            ದತ್ತಾಂಶ->raw_mouse_enabled = !enabled;
            ಹಿಂತಿರುಗಿ false;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (!WIN_Update_Raw_ಒಳಹರಿವು_Enabled(_this)) {
            ದತ್ತಾಂಶ->raw_mouse_enabled = !enabled;
            ಹಿಂತಿರುಗಿ false;
        }
    }
    ಹಿಂತಿರುಗಿ true;
}

bool WIN_ಗಣ_Raw_Mouse_Flag_No_Legacy(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;

    ದತ್ತಾಂಶ->raw_mouse_flag_nolegacy = enabled;

    ಹಿಂತಿರುಗಿ WIN_Update_Raw_ಒಳಹರಿವು_Enabled(_this);
}

bool WIN_ಗಣ_Raw_Keyboard_Enabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;
    ದತ್ತಾಂಶ->raw_keyboard_enabled = enabled;
    ಆದರೆ (ದತ್ತಾಂಶ->gameinput_context) {
        ಆದರೆ (!WIN_Update_Game_ಒಳಹರಿವು_Enabled(_this)) {
            ದತ್ತಾಂಶ->raw_keyboard_enabled = !enabled;
            ಹಿಂತಿರುಗಿ false;
        }
    } ಇಲ್ಲದಿದ್ದರೆ {
        ಆದರೆ (!WIN_Update_Raw_ಒಳಹರಿವು_Enabled(_this)) {
            ದತ್ತಾಂಶ->raw_keyboard_enabled = !enabled;
            ಹಿಂತಿರುಗಿ false;
        }
    }
    ಹಿಂತಿರುಗಿ true;
}

bool WIN_ಗಣ_Raw_Keyboard_Flag_No_Hotkeys(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;

    ದತ್ತಾಂಶ->raw_keyboard_flag_nohotkeys = enabled;

    ಹಿಂತಿರುಗಿ WIN_Update_Raw_ಒಳಹರಿವು_Enabled(_this);
}

bool WIN_ಗಣ_Raw_Keyboard_Flag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = _this->ಆಂತರಿಕ;

    ದತ್ತಾಂಶ->raw_keyboard_flag_inputsink = enabled;

    ಹಿಂತಿರುಗಿ WIN_Update_Raw_ಒಳಹರಿವು_Enabled(_this);
}

ಶೂನ್ಯ WIN_Quit_Raw_ಒಳಹರಿವು(SDL_VideoDevice *_this)
{
    Cleanup_Raw_ಒಳಹರಿವು_Thread_ದತ್ತಾಂಶ();
}

#ಇಲ್ಲದಿದ್ದರೆ

bool WIN_ಗಣ_Raw_Mouse_Enabled(SDL_VideoDevice *_this, bool enabled)
{
    ಹಿಂತಿರುಗಿ SDL_Unsupported();
}

bool WIN_ಗಣ_Raw_Mouse_Flag_No_Legacy(SDL_VideoDevice *_this, bool enabled)
{
    ಹಿಂತಿರುಗಿ SDL_Unsupported();
}

bool WIN_ಗಣ_Raw_Keyboard_Enabled(SDL_VideoDevice *_this, bool enabled)
{
    ಹಿಂತಿರುಗಿ SDL_Unsupported();
}

bool WIN_ಗಣ_Raw_Keyboard_Flag_No_Hotkeys(SDL_VideoDevice *_this, bool enabled)
{
    ಹಿಂತಿರುಗಿ SDL_Unsupported();
}

bool WIN_ಗಣ_Raw_Keyboard_Flag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    ಹಿಂತಿರುಗಿ SDL_Unsupported();
}

ಶೂನ್ಯ WIN_Quit_Raw_ಒಳಹರಿವು(SDL_VideoDevice *_this)
{
}

#ಆದರೆ_ಅಂತ್ಯ // !SDL_PLATFORM_XBOXONE && !SDL_PLATFORM_XBOXSERIES

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_WINDOWS

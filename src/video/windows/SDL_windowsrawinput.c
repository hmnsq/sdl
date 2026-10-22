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

#ಯದಿ defined(SDL_VIDEO_DRIVER_WINDOWS)

#ಅನ್ತರ್ಭಾವ "SDL_windowsvideo.h"

#ಯದಿ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ಅನ್ತರ್ಭಾವ "SDL_windowsevents.h"

#ಅನ್ತರ್ಭಾವ "../../joystick/usb_ids.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_events_c.h"
#ಅನ್ತರ್ಭಾವ "../../thread/SDL_systhread.h"

#define ENABLE_RAW_MOUSE_ಒಳಹರಿವು      0x01
#define RAW_MOUSE_FLAG_NOLEGACY     0x02
#define ENABLE_RAW_KEYBOARD_ಒಳಹರಿವು   0x10
#define RAW_KEYBOARD_FLAG_NOHOTKEYS 0x20
#define RAW_KEYBOARD_FLAG_INPUTSINK 0x40

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ
{
    bool done;
    SDL_AtomicU32 flags; // Thread sets this to the actually-set flags if updating state failed
    HANDLE ready_event;
    HANDLE signal_event;
    HANDLE thread;
} Raw_ಒಳಹರಿವು_Thread_Data;

ಸ್ಥಿರ Raw_ಒಳಹರಿವು_Thread_Data thread_data = { 0 };

ಪ್ರಕಾರನಿರ್ದೇಶ ಗಣನಾ
{
    RINP_QUIT,
    RINP_UPDATE,
    RINP_CONTINUE
} Raw_ಒಳಹರಿವು_Iterate_Result;

ಸ್ಥಿರ Raw_ಒಳಹರಿವು_Iterate_Result Iterate_Raw_ಒಳಹರಿವು_Thread(ಶೂನ್ಯ)
{
    // The high-order word of GetQueueStatus() will let us know if there's immediate raw input to be processed.
    // A (necessary!) side effect is that it also marks the message queue bits as stale,
    // so MsgWaitForMultipleObjects will block.

    // Any pending flag update won't be processed until the queue drains, but this is
    // at most one poll cycle since GetQueueStatus clears the wake bits.
    ಯದಿ (HIWORD(GetQueueStatus(QS_RAWINPUT)) & QS_RAWINPUT) {
        ಪ್ರತ್ಯಾಗಮ thread_data.done ? RINP_QUIT : RINP_CONTINUE;
    }

    ಸ್ಥಿರ ಧ್ರುವ DWORD WAIT_SIGNAL = WAIT_OBJECT_0;
    ಸ್ಥಿರ ಧ್ರುವ DWORD WAIT_ಒಳಹರಿವು = WAIT_OBJECT_0 + 1;

    // There wasn't anything, so we'll wait until new data (or signal_event) wakes us up.
    DWORD wait_status = ಸಂದೇಶ_Wait_For_Multiple_Objects(1, &thread_data.signal_event, FALSE, INFINITE, QS_RAWINPUT);
    ಯದಿ (wait_status == WAIT_SIGNAL) {
        // signal_event can only be set if we need to update or quit.
        ಪ್ರತ್ಯಾಗಮ thread_data.done ? RINP_QUIT : RINP_UPDATE;
    } ಅನ್ಯಥಾ ಯದಿ (wait_status == WAIT_ಒಳಹರಿವು) {
        ಪ್ರತ್ಯಾಗಮ RINP_CONTINUE;
    } ಅನ್ಯಥಾ {
        SDL_LogWarn(SDL_LOG_CATEGORY_ಒಳಹರಿವು, "Raw input thread exiting, unexpected wait result: %" SDL_PRIuULONG, wait_status);
        ಪ್ರತ್ಯಾಗಮ RINP_QUIT;
    }
}

ಸ್ಥಿರ bool Update_Raw_ಒಳಹರಿವು_Device_Flags(HWND window, Uint32 last_flags, Uint32 new_flags)
{
    // We had nothing enabled, and we're trying to stop everything. Nothing to do.
    ಯದಿ (last_flags == new_flags) {
        ಪ್ರತ್ಯಾಗಮ true;
    }

    RAWINPUTDEVICE devices[2] = { 0 };
    UINT ಎಣಿಕೆ = 0;

    ಧ್ರುವ Uint32 old_mouse_flags = last_flags & (ENABLE_RAW_MOUSE_ಒಳಹರಿವು | RAW_MOUSE_FLAG_NOLEGACY);
    ಧ್ರುವ Uint32 new_mouse_flags = new_flags & (ENABLE_RAW_MOUSE_ಒಳಹರಿವು | RAW_MOUSE_FLAG_NOLEGACY);

    ಯದಿ (old_mouse_flags != new_mouse_flags) {
        devices[ಎಣಿಕೆ].usUsagePage = USB_USAGEPAGE_GENERIC_DESKTOP;
        devices[ಎಣಿಕೆ].usUsage = USB_USAGE_GENERIC_MOUSE;

        ಯದಿ (new_flags & ENABLE_RAW_MOUSE_ಒಳಹರಿವು) {
            devices[ಎಣಿಕೆ].dwFlags = 0;
            devices[ಎಣಿಕೆ].hwndTarget = window;
            ಯದಿ (new_mouse_flags & RAW_MOUSE_FLAG_NOLEGACY) {
                devices[ಎಣಿಕೆ].dwFlags |= RIDEV_NOLEGACY;
            }
        } ಅನ್ಯಥಾ {
            devices[ಎಣಿಕೆ].dwFlags = RIDEV_REMOVE;
            devices[ಎಣಿಕೆ].hwndTarget = ರಿಕ್ತ;
        }

        ++ಎಣಿಕೆ;
    }

    ಧ್ರುವ Uint32 old_kb_flags = last_flags & (ENABLE_RAW_KEYBOARD_ಒಳಹರಿವು | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);
    ಧ್ರುವ Uint32 new_kb_flags = new_flags & (ENABLE_RAW_KEYBOARD_ಒಳಹರಿವು | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);

    ಯದಿ (old_kb_flags != new_kb_flags) {
        devices[ಎಣಿಕೆ].usUsagePage = USB_USAGEPAGE_GENERIC_DESKTOP;
        devices[ಎಣಿಕೆ].usUsage = USB_USAGE_GENERIC_KEYBOARD;

        ಯದಿ (new_kb_flags & ENABLE_RAW_KEYBOARD_ಒಳಹರಿವು) {
            devices[ಎಣಿಕೆ].dwFlags = 0;
            devices[ಎಣಿಕೆ].hwndTarget = window;
            ಯದಿ (new_kb_flags & RAW_KEYBOARD_FLAG_NOHOTKEYS) {
                devices[ಎಣಿಕೆ].dwFlags |= RIDEV_NOHOTKEYS;
            }
            ಯದಿ (new_kb_flags & RAW_KEYBOARD_FLAG_INPUTSINK) {
                devices[ಎಣಿಕೆ].dwFlags |= RIDEV_INPUTSINK;
            }
        } ಅನ್ಯಥಾ {
            devices[ಎಣಿಕೆ].dwFlags = RIDEV_REMOVE;
            devices[ಎಣಿಕೆ].hwndTarget = ರಿಕ್ತ;
        }

        ++ಎಣಿಕೆ;
    }

    ಯದಿ (Register_Raw_ಒಳಹರಿವು_Devices(devices, ಎಣಿಕೆ, ಪರಿಮಾಣ(devices[0]))) {
        ಪ್ರತ್ಯಾಗಮ true;
    }
    ಪ್ರತ್ಯಾಗಮ false;
}

ಸ್ಥಿರ DWORD WINAPI WIN_Raw_ಒಳಹರಿವು_Thread(LPVOID param)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    Uint32 last_flags = 0;
    HWND window;

    SDL_SYS_SetupThread("SDLRawInput");

    window = CreateWindowEx(0, TEXT("Message"), ರಿಕ್ತ, 0, 0, 0, 0, 0, HWND_MESSAGE, ರಿಕ್ತ, ರಿಕ್ತ, ರಿಕ್ತ);
    ಯದಿ (!window) {
        ಪ್ರತ್ಯಾಗಮ 0;
    }

    // This doesn't *really* need to be atomic, because the parent is waiting for us
    last_flags = SDL_GetAtomicU32(&thread_data.flags);
    ಯದಿ (!Update_Raw_ಒಳಹರಿವು_Device_Flags(window, 0, last_flags)) {
        DestroyWindow(window);
        ಪ್ರತ್ಯಾಗಮ 0;
    }

    // Make sure we get events as soon as possible
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);

    // Tell the parent we're ready to go!
    SetEvent(thread_data.ready_event);

    Raw_ಒಳಹರಿವು_Iterate_Result iter_result;

    Uint64 idle_begin = SDL_GetTicksNS();
    ಯಾವತ್ ((iter_result = Iterate_Raw_ಒಳಹರಿವು_Thread()) != RINP_QUIT) {
        ವಿಕಲ್ಪ (iter_result) {
        ಪಕ್ಷ RINP_QUIT: // Unreachable
            ಭಙ್ಗ;
        ಪಕ್ಷ RINP_UPDATE:
        {
            ಧ್ರುವ Uint32 new_flags = SDL_GetAtomicU32(&thread_data.flags);
            ಯದಿ (!Update_Raw_ಒಳಹರಿವು_Device_Flags(window, last_flags, new_flags)) {
                // Revert the shared flags so the main thread can detect the failure
                SDL_SetAtomicU32(&thread_data.flags, last_flags);
            } ಅನ್ಯಥಾ {
                last_flags = new_flags;
            }
        } ಭಙ್ಗ;
        ಪಕ್ಷ RINP_CONTINUE:
        {
            Uint64 idle_end = SDL_GetTicksNS();
            Uint64 idle_time = idle_end - idle_begin;
            Uint64 usb_8khz_interval = SDL_US_TO_NS(125);
            Uint64 poll_start = idle_time < usb_8khz_interval ? _this->internal->last_rawinput_poll : idle_end;

            WIN_Poll_Raw_ಒಳಹರಿವು(_this, poll_start);

            // Reset idle_begin for the next go-around
            idle_begin = SDL_GetTicksNS();
        } ಭಙ್ಗ;
        }
    }

    ಯದಿ (_this->internal->raw_ಒಳಹರಿವು_fake_pen_id) {
        SDL_RemovePenDevice(0, SDL_GetKeyboardFocus(), _this->internal->raw_ಒಳಹರಿವು_fake_pen_id);
        _this->internal->raw_ಒಳಹರಿವು_fake_pen_id = 0;
    }

    // Reset this here, since if we're exiting due to failure, WIN_UpdateRawInputEnabled would see a stale value.
    SDL_SetAtomicU32(&thread_data.flags, 0);

    Update_Raw_ಒಳಹರಿವು_Device_Flags(ರಿಕ್ತ, last_flags, 0);

    DestroyWindow(window);

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಸ್ಥಿರ ಶೂನ್ಯ Cleanup_Raw_ಒಳಹರಿವು_Thread_Data(ಶೂನ್ಯ)
{
    ಯದಿ (thread_data.thread) {
        thread_data.done = true;
        SetEvent(thread_data.signal_event);
        WaitForSingleObject(thread_data.thread, 3000);
        CloseHandle(thread_data.thread);
    }

    ಯದಿ (thread_data.ready_event) {
        CloseHandle(thread_data.ready_event);
    }

    ಯದಿ (thread_data.signal_event) {
        CloseHandle(thread_data.signal_event);
    }

    thread_data = (Raw_ಒಳಹರಿವು_Thread_Data){ 0 };
}

// Computes the desired raw input flags from SDL_VideoData and ensures the
// raw input thread's device registrations match.
// Creates the thread on first use, only WIN_QuitRawInput actually shuts it down.
ಸ್ಥಿರ bool WIN_Update_Raw_ಒಳಹರಿವು_Enabled(SDL_VideoDevice *_this)
{
    bool result = false;
    SDL_VideoData *data = _this->internal;
    Uint32 desired_flags = 0;

    ಯದಿ (!data->gameinput_context) {
        ಯದಿ (data->raw_mouse_enabled) {
            desired_flags |= ENABLE_RAW_MOUSE_ಒಳಹರಿವು;
            ಯದಿ (data->raw_mouse_flag_nolegacy) {
                desired_flags |= RAW_MOUSE_FLAG_NOLEGACY;
            }
        }
        ಯದಿ (data->raw_keyboard_enabled) {
            desired_flags |= ENABLE_RAW_KEYBOARD_ಒಳಹರಿವು;
            ಯದಿ (data->raw_keyboard_flag_nohotkeys) {
                desired_flags |= RAW_KEYBOARD_FLAG_NOHOTKEYS;
            }
            ಯದಿ (data->raw_keyboard_flag_inputsink) {
                desired_flags |= RAW_KEYBOARD_FLAG_INPUTSINK;
            }
        }
    }

    ಯದಿ (desired_flags == SDL_GetAtomicU32(&thread_data.flags)) {
        result = true;
        ಗಚ್ಛ done;
    }

    // If the thread exited unexpectedly (e.g. MsgWaitForMultipleObjects failed),
    // the handle is stale. Clean it up so the creation path below can recover.
    ಯದಿ (thread_data.thread && WaitForSingleObject(thread_data.thread, 0) != WAIT_TIMEOUT) {
        Cleanup_Raw_ಒಳಹರಿವು_Thread_Data();
    }

    // The thread will read from this to update its flags
    SDL_SetAtomicU32(&thread_data.flags, desired_flags);

    ಯದಿ (thread_data.thread) {
        // Thread is already running. Fire (the event) and forget, it'll read the atomic flags on wakeup.

        // If RegisterRawInputDevices fails, the thread reverts the atomic and the next call
        // to this function will see the mismatch and retry.
        SDL_assert(thread_data.signal_event);
        SetEvent(thread_data.signal_event);
        result = true;
    } ಅನ್ಯಥಾ ಯದಿ (desired_flags) {
        HANDLE wait_handles[2];

        // Thread isn't running, spin it up
        thread_data.ready_event = CreateEvent(ರಿಕ್ತ, FALSE, FALSE, ರಿಕ್ತ);
        ಯದಿ (!thread_data.ready_event) {
            WIN_SetError("CreateEvent");
            ಗಚ್ಛ done;
        }

        thread_data.done = false;
        thread_data.signal_event = CreateEvent(ರಿಕ್ತ, FALSE, FALSE, ರಿಕ್ತ);
        ಯದಿ (!thread_data.signal_event) {
            WIN_SetError("CreateEvent");
            ಗಚ್ಛ done;
        }

        thread_data.thread = CreateThread(ರಿಕ್ತ, 0, WIN_Raw_ಒಳಹರಿವು_Thread, ರಿಕ್ತ, 0, ರಿಕ್ತ);
        ಯದಿ (!thread_data.thread) {
            WIN_SetError("CreateThread");
            ಗಚ್ಛ done;
        }

        // Wait for the thread to complete initial setup or exit
        wait_handles[0] = thread_data.ready_event;
        wait_handles[1] = thread_data.thread;
        ಯದಿ (WaitForMultipleObjects(2, wait_handles, FALSE, INFINITE) != WAIT_OBJECT_0) {
            SDL_SetError("Couldn't set up raw input handling");
            ಗಚ್ಛ done;
        }
        result = true;
    } ಅನ್ಯಥಾ {
        // Thread isn't running and we tried to disable raw input, nothing to do
        result = true;
    }
done:
    ಯದಿ (!result) {
        Cleanup_Raw_ಒಳಹರಿವು_Thread_Data();
    }
    ಪ್ರತ್ಯಾಗಮ result;
}

bool WIN_SetRawMouseEnabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;
    data->raw_mouse_enabled = enabled;
    ಯದಿ (data->gameinput_context) {
        ಯದಿ (!WIN_Update_Game_ಒಳಹರಿವು_Enabled(_this)) {
            data->raw_mouse_enabled = !enabled;
            ಪ್ರತ್ಯಾಗಮ false;
        }
    } ಅನ್ಯಥಾ {
        ಯದಿ (!WIN_Update_Raw_ಒಳಹರಿವು_Enabled(_this)) {
            data->raw_mouse_enabled = !enabled;
            ಪ್ರತ್ಯಾಗಮ false;
        }
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

bool WIN_SetRawMouseFlag_NoLegacy(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;

    data->raw_mouse_flag_nolegacy = enabled;

    ಪ್ರತ್ಯಾಗಮ WIN_Update_Raw_ಒಳಹರಿವು_Enabled(_this);
}

bool WIN_SetRawKeyboardEnabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;
    data->raw_keyboard_enabled = enabled;
    ಯದಿ (data->gameinput_context) {
        ಯದಿ (!WIN_Update_Game_ಒಳಹರಿವು_Enabled(_this)) {
            data->raw_keyboard_enabled = !enabled;
            ಪ್ರತ್ಯಾಗಮ false;
        }
    } ಅನ್ಯಥಾ {
        ಯದಿ (!WIN_Update_Raw_ಒಳಹರಿವು_Enabled(_this)) {
            data->raw_keyboard_enabled = !enabled;
            ಪ್ರತ್ಯಾಗಮ false;
        }
    }
    ಪ್ರತ್ಯಾಗಮ true;
}

bool WIN_SetRawKeyboardFlag_NoHotkeys(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;

    data->raw_keyboard_flag_nohotkeys = enabled;

    ಪ್ರತ್ಯಾಗಮ WIN_Update_Raw_ಒಳಹರಿವು_Enabled(_this);
}

bool WIN_SetRawKeyboardFlag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;

    data->raw_keyboard_flag_inputsink = enabled;

    ಪ್ರತ್ಯಾಗಮ WIN_Update_Raw_ಒಳಹರಿವು_Enabled(_this);
}

ಶೂನ್ಯ WIN_Quit_Raw_ಒಳಹರಿವು(SDL_VideoDevice *_this)
{
    Cleanup_Raw_ಒಳಹರಿವು_Thread_Data();
}

#ಅನ್ಯಥಾ

bool WIN_SetRawMouseEnabled(SDL_VideoDevice *_this, bool enabled)
{
    ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
}

bool WIN_SetRawMouseFlag_NoLegacy(SDL_VideoDevice *_this, bool enabled)
{
    ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
}

bool WIN_SetRawKeyboardEnabled(SDL_VideoDevice *_this, bool enabled)
{
    ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
}

bool WIN_SetRawKeyboardFlag_NoHotkeys(SDL_VideoDevice *_this, bool enabled)
{
    ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
}

bool WIN_SetRawKeyboardFlag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    ಪ್ರತ್ಯಾಗಮ SDL_Unsupported();
}

ಶೂನ್ಯ WIN_Quit_Raw_ಒಳಹರಿವು(SDL_VideoDevice *_this)
{
}

#endif // !SDL_PLATFORM_XBOXONE && !SDL_PLATFORM_XBOXSERIES

#endif // SDL_VIDEO_DRIVER_WINDOWS

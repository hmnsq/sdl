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

#إذا defined(SDL_VIDEO_DRIVER_WINDOWS)

#ضمن "SDL_windowsvideo.h"

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ضمن "SDL_windowsevents.h"

#ضمن "../../joystick/usb_ids.h"
#ضمن "../../events/SDL_events_c.h"
#ضمن "../../thread/SDL_systhread.h"

#define ENABLE_RAW_MOUSE_كىرگۈزۈش      0x01
#define RAW_MOUSE_FLAG_NOLEGACY     0x02
#define ENABLE_RAW_KEYBOARD_كىرگۈزۈش   0x10
#define RAW_KEYBOARD_FLAG_NOHOTKEYS 0x20
#define RAW_KEYBOARD_FLAG_INPUTSINK 0x40

تعريفنوع بنية
{
    bool done;
    SDL_AtomicU32 flags; // Thread sets this to the actually-set flags if updating state failed
    HANDLE ready_event;
    HANDLE signal_event;
    HANDLE thread;
} Raw_كىرگۈزۈش_Thread_Data;

ساكن Raw_كىرگۈزۈش_Thread_Data thread_data = { 0 };

تعريفنوع تعداد
{
    RINP_QUIT,
    RINP_UPDATE,
    RINP_CONTINUE
} Raw_كىرگۈزۈش_Iterate_Result;

ساكن Raw_كىرگۈزۈش_Iterate_Result Iterate_Raw_كىرگۈزۈش_Thread(فراغ)
{
    // The high-order word of GetQueueStatus() will let us know if there's immediate raw input to be processed.
    // A (necessary!) side effect is that it also marks the message queue bits as stale,
    // so MsgWaitForMultipleObjects will block.

    // Any pending flag update won't be processed until the queue drains, but this is
    // at most one poll cycle since GetQueueStatus clears the wake bits.
    إذا (HIWORD(GetQueueStatus(QS_RAWINPUT)) & QS_RAWINPUT) {
        أرجع thread_data.done ? RINP_QUIT : RINP_CONTINUE;
    }

    ساكن ثابت DWORD WAIT_SIGNAL = WAIT_OBJECT_0;
    ساكن ثابت DWORD WAIT_كىرگۈزۈش = WAIT_OBJECT_0 + 1;

    // There wasn't anything, so we'll wait until new data (or signal_event) wakes us up.
    DWORD wait_status = ئۇچۇر_Wait_For_Multiple_Objects(1, &thread_data.signal_event, FALSE, INFINITE, QS_RAWINPUT);
    إذا (wait_status == WAIT_SIGNAL) {
        // signal_event can only be set if we need to update or quit.
        أرجع thread_data.done ? RINP_QUIT : RINP_UPDATE;
    } وإلا إذا (wait_status == WAIT_كىرگۈزۈش) {
        أرجع RINP_CONTINUE;
    } وإلا {
        SDL_LogWarn(SDL_LOG_CATEGORY_كىرگۈزۈش, "Raw input thread exiting, unexpected wait result: %" SDL_PRIuULONG, wait_status);
        أرجع RINP_QUIT;
    }
}

ساكن bool Update_Raw_كىرگۈزۈش_Device_Flags(HWND window, Uint32 last_flags, Uint32 new_flags)
{
    // We had nothing enabled, and we're trying to stop everything. Nothing to do.
    إذا (last_flags == new_flags) {
        أرجع true;
    }

    RAWINPUTDEVICE devices[2] = { 0 };
    UINT سانى = 0;

    ثابت Uint32 old_mouse_flags = last_flags & (ENABLE_RAW_MOUSE_كىرگۈزۈش | RAW_MOUSE_FLAG_NOLEGACY);
    ثابت Uint32 new_mouse_flags = new_flags & (ENABLE_RAW_MOUSE_كىرگۈزۈش | RAW_MOUSE_FLAG_NOLEGACY);

    إذا (old_mouse_flags != new_mouse_flags) {
        devices[سانى].usUsagePage = USB_USAGEPAGE_GENERIC_DESKTOP;
        devices[سانى].usUsage = USB_USAGE_GENERIC_MOUSE;

        إذا (new_flags & ENABLE_RAW_MOUSE_كىرگۈزۈش) {
            devices[سانى].dwFlags = 0;
            devices[سانى].hwndTarget = window;
            إذا (new_mouse_flags & RAW_MOUSE_FLAG_NOLEGACY) {
                devices[سانى].dwFlags |= RIDEV_NOLEGACY;
            }
        } وإلا {
            devices[سانى].dwFlags = RIDEV_REMOVE;
            devices[سانى].hwndTarget = عدم;
        }

        ++سانى;
    }

    ثابت Uint32 old_kb_flags = last_flags & (ENABLE_RAW_KEYBOARD_كىرگۈزۈش | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);
    ثابت Uint32 new_kb_flags = new_flags & (ENABLE_RAW_KEYBOARD_كىرگۈزۈش | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);

    إذا (old_kb_flags != new_kb_flags) {
        devices[سانى].usUsagePage = USB_USAGEPAGE_GENERIC_DESKTOP;
        devices[سانى].usUsage = USB_USAGE_GENERIC_KEYBOARD;

        إذا (new_kb_flags & ENABLE_RAW_KEYBOARD_كىرگۈزۈش) {
            devices[سانى].dwFlags = 0;
            devices[سانى].hwndTarget = window;
            إذا (new_kb_flags & RAW_KEYBOARD_FLAG_NOHOTKEYS) {
                devices[سانى].dwFlags |= RIDEV_NOHOTKEYS;
            }
            إذا (new_kb_flags & RAW_KEYBOARD_FLAG_INPUTSINK) {
                devices[سانى].dwFlags |= RIDEV_INPUTSINK;
            }
        } وإلا {
            devices[سانى].dwFlags = RIDEV_REMOVE;
            devices[سانى].hwndTarget = عدم;
        }

        ++سانى;
    }

    إذا (Register_Raw_كىرگۈزۈش_Devices(devices, سانى, حجم(devices[0]))) {
        أرجع true;
    }
    أرجع false;
}

ساكن DWORD WINAPI WIN_Raw_كىرگۈزۈش_Thread(LPVOID param)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    Uint32 last_flags = 0;
    HWND window;

    SDL_SYS_SetupThread("SDLRawInput");

    window = CreateWindowEx(0, TEXT("Message"), عدم, 0, 0, 0, 0, 0, HWND_MESSAGE, عدم, عدم, عدم);
    إذا (!window) {
        أرجع 0;
    }

    // This doesn't *really* need to be atomic, because the parent is waiting for us
    last_flags = SDL_GetAtomicU32(&thread_data.flags);
    إذا (!Update_Raw_كىرگۈزۈش_Device_Flags(window, 0, last_flags)) {
        DestroyWindow(window);
        أرجع 0;
    }

    // Make sure we get events as soon as possible
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);

    // Tell the parent we're ready to go!
    SetEvent(thread_data.ready_event);

    Raw_كىرگۈزۈش_Iterate_Result iter_result;

    Uint64 idle_begin = SDL_GetTicksNS();
    طالما ((iter_result = Iterate_Raw_كىرگۈزۈش_Thread()) != RINP_QUIT) {
        بدل (iter_result) {
        حالة RINP_QUIT: // Unreachable
            اكسر;
        حالة RINP_UPDATE:
        {
            ثابت Uint32 new_flags = SDL_GetAtomicU32(&thread_data.flags);
            إذا (!Update_Raw_كىرگۈزۈش_Device_Flags(window, last_flags, new_flags)) {
                // Revert the shared flags so the main thread can detect the failure
                SDL_SetAtomicU32(&thread_data.flags, last_flags);
            } وإلا {
                last_flags = new_flags;
            }
        } اكسر;
        حالة RINP_CONTINUE:
        {
            Uint64 idle_end = SDL_GetTicksNS();
            Uint64 idle_time = idle_end - idle_begin;
            Uint64 usb_8khz_interval = SDL_US_TO_NS(125);
            Uint64 poll_start = idle_time < usb_8khz_interval ? _this->internal->last_rawinput_poll : idle_end;

            WIN_Poll_Raw_كىرگۈزۈش(_this, poll_start);

            // Reset idle_begin for the next go-around
            idle_begin = SDL_GetTicksNS();
        } اكسر;
        }
    }

    إذا (_this->internal->raw_كىرگۈزۈش_fake_pen_id) {
        SDL_RemovePenDevice(0, SDL_GetKeyboardFocus(), _this->internal->raw_كىرگۈزۈش_fake_pen_id);
        _this->internal->raw_كىرگۈزۈش_fake_pen_id = 0;
    }

    // Reset this here, since if we're exiting due to failure, WIN_UpdateRawInputEnabled would see a stale value.
    SDL_SetAtomicU32(&thread_data.flags, 0);

    Update_Raw_كىرگۈزۈش_Device_Flags(عدم, last_flags, 0);

    DestroyWindow(window);

    أرجع 0;
}

ساكن فراغ Cleanup_Raw_كىرگۈزۈش_Thread_Data(فراغ)
{
    إذا (thread_data.thread) {
        thread_data.done = true;
        SetEvent(thread_data.signal_event);
        WaitForSingleObject(thread_data.thread, 3000);
        CloseHandle(thread_data.thread);
    }

    إذا (thread_data.ready_event) {
        CloseHandle(thread_data.ready_event);
    }

    إذا (thread_data.signal_event) {
        CloseHandle(thread_data.signal_event);
    }

    thread_data = (Raw_كىرگۈزۈش_Thread_Data){ 0 };
}

// Computes the desired raw input flags from SDL_VideoData and ensures the
// raw input thread's device registrations match.
// Creates the thread on first use, only WIN_QuitRawInput actually shuts it down.
ساكن bool WIN_Update_Raw_كىرگۈزۈش_Enabled(SDL_VideoDevice *_this)
{
    bool result = false;
    SDL_VideoData *data = _this->internal;
    Uint32 desired_flags = 0;

    إذا (!data->gameinput_context) {
        إذا (data->raw_mouse_enabled) {
            desired_flags |= ENABLE_RAW_MOUSE_كىرگۈزۈش;
            إذا (data->raw_mouse_flag_nolegacy) {
                desired_flags |= RAW_MOUSE_FLAG_NOLEGACY;
            }
        }
        إذا (data->raw_keyboard_enabled) {
            desired_flags |= ENABLE_RAW_KEYBOARD_كىرگۈزۈش;
            إذا (data->raw_keyboard_flag_nohotkeys) {
                desired_flags |= RAW_KEYBOARD_FLAG_NOHOTKEYS;
            }
            إذا (data->raw_keyboard_flag_inputsink) {
                desired_flags |= RAW_KEYBOARD_FLAG_INPUTSINK;
            }
        }
    }

    إذا (desired_flags == SDL_GetAtomicU32(&thread_data.flags)) {
        result = true;
        اذهب done;
    }

    // If the thread exited unexpectedly (e.g. MsgWaitForMultipleObjects failed),
    // the handle is stale. Clean it up so the creation path below can recover.
    إذا (thread_data.thread && WaitForSingleObject(thread_data.thread, 0) != WAIT_TIMEOUT) {
        Cleanup_Raw_كىرگۈزۈش_Thread_Data();
    }

    // The thread will read from this to update its flags
    SDL_SetAtomicU32(&thread_data.flags, desired_flags);

    إذا (thread_data.thread) {
        // Thread is already running. Fire (the event) and forget, it'll read the atomic flags on wakeup.

        // If RegisterRawInputDevices fails, the thread reverts the atomic and the next call
        // to this function will see the mismatch and retry.
        SDL_assert(thread_data.signal_event);
        SetEvent(thread_data.signal_event);
        result = true;
    } وإلا إذا (desired_flags) {
        HANDLE wait_handles[2];

        // Thread isn't running, spin it up
        thread_data.ready_event = CreateEvent(عدم, FALSE, FALSE, عدم);
        إذا (!thread_data.ready_event) {
            WIN_SetError("CreateEvent");
            اذهب done;
        }

        thread_data.done = false;
        thread_data.signal_event = CreateEvent(عدم, FALSE, FALSE, عدم);
        إذا (!thread_data.signal_event) {
            WIN_SetError("CreateEvent");
            اذهب done;
        }

        thread_data.thread = CreateThread(عدم, 0, WIN_Raw_كىرگۈزۈش_Thread, عدم, 0, عدم);
        إذا (!thread_data.thread) {
            WIN_SetError("CreateThread");
            اذهب done;
        }

        // Wait for the thread to complete initial setup or exit
        wait_handles[0] = thread_data.ready_event;
        wait_handles[1] = thread_data.thread;
        إذا (WaitForMultipleObjects(2, wait_handles, FALSE, INFINITE) != WAIT_OBJECT_0) {
            SDL_SetError("Couldn't set up raw input handling");
            اذهب done;
        }
        result = true;
    } وإلا {
        // Thread isn't running and we tried to disable raw input, nothing to do
        result = true;
    }
done:
    إذا (!result) {
        Cleanup_Raw_كىرگۈزۈش_Thread_Data();
    }
    أرجع result;
}

bool WIN_SetRawMouseEnabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;
    data->raw_mouse_enabled = enabled;
    إذا (data->gameinput_context) {
        إذا (!WIN_Update_Game_كىرگۈزۈش_Enabled(_this)) {
            data->raw_mouse_enabled = !enabled;
            أرجع false;
        }
    } وإلا {
        إذا (!WIN_Update_Raw_كىرگۈزۈش_Enabled(_this)) {
            data->raw_mouse_enabled = !enabled;
            أرجع false;
        }
    }
    أرجع true;
}

bool WIN_SetRawMouseFlag_NoLegacy(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;

    data->raw_mouse_flag_nolegacy = enabled;

    أرجع WIN_Update_Raw_كىرگۈزۈش_Enabled(_this);
}

bool WIN_SetRawKeyboardEnabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;
    data->raw_keyboard_enabled = enabled;
    إذا (data->gameinput_context) {
        إذا (!WIN_Update_Game_كىرگۈزۈش_Enabled(_this)) {
            data->raw_keyboard_enabled = !enabled;
            أرجع false;
        }
    } وإلا {
        إذا (!WIN_Update_Raw_كىرگۈزۈش_Enabled(_this)) {
            data->raw_keyboard_enabled = !enabled;
            أرجع false;
        }
    }
    أرجع true;
}

bool WIN_SetRawKeyboardFlag_NoHotkeys(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;

    data->raw_keyboard_flag_nohotkeys = enabled;

    أرجع WIN_Update_Raw_كىرگۈزۈش_Enabled(_this);
}

bool WIN_SetRawKeyboardFlag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;

    data->raw_keyboard_flag_inputsink = enabled;

    أرجع WIN_Update_Raw_كىرگۈزۈش_Enabled(_this);
}

فراغ WIN_Quit_Raw_كىرگۈزۈش(SDL_VideoDevice *_this)
{
    Cleanup_Raw_كىرگۈزۈش_Thread_Data();
}

#وإلا

bool WIN_SetRawMouseEnabled(SDL_VideoDevice *_this, bool enabled)
{
    أرجع SDL_Unsupported();
}

bool WIN_SetRawMouseFlag_NoLegacy(SDL_VideoDevice *_this, bool enabled)
{
    أرجع SDL_Unsupported();
}

bool WIN_SetRawKeyboardEnabled(SDL_VideoDevice *_this, bool enabled)
{
    أرجع SDL_Unsupported();
}

bool WIN_SetRawKeyboardFlag_NoHotkeys(SDL_VideoDevice *_this, bool enabled)
{
    أرجع SDL_Unsupported();
}

bool WIN_SetRawKeyboardFlag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    أرجع SDL_Unsupported();
}

فراغ WIN_Quit_Raw_كىرگۈزۈش(SDL_VideoDevice *_this)
{
}

#endif // !SDL_PLATFORM_XBOXONE && !SDL_PLATFORM_XBOXSERIES

#endif // SDL_VIDEO_DRIVER_WINDOWS

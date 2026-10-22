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

#যদি defined(SDL_VIDEO_DRIVER_WINDOWS)

#অন্তর্ভাব "SDL_windowsvideo.h"

#যদি !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#অন্তর্ভাব "SDL_windowsevents.h"

#অন্তর্ভাব "../../joystick/usb_ids.h"
#অন্তর্ভাব "../../events/SDL_events_c.h"
#অন্তর্ভাব "../../thread/SDL_systhread.h"

#define ENABLE_RAW_MOUSE_প্রবেশ      0x01
#define RAW_MOUSE_FLAG_NOLEGACY     0x02
#define ENABLE_RAW_KEYBOARD_প্রবেশ   0x10
#define RAW_KEYBOARD_FLAG_NOHOTKEYS 0x20
#define RAW_KEYBOARD_FLAG_INPUTSINK 0x40

প্রকারনির্দেশ সংরচনা
{
    bool done;
    SDL_AtomicU32 flags; // Thread sets this to the actually-set flags if updating state failed
    HANDLE ready_event;
    HANDLE signal_event;
    HANDLE thread;
} Raw_প্রবেশ_Thread_Data;

স্থির Raw_প্রবেশ_Thread_Data thread_data = { 0 };

প্রকারনির্দেশ গণনা
{
    RINP_QUIT,
    RINP_UPDATE,
    RINP_CONTINUE
} Raw_প্রবেশ_Iterate_Result;

স্থির Raw_প্রবেশ_Iterate_Result Iterate_Raw_প্রবেশ_Thread(শূন্য)
{
    // The high-order word of GetQueueStatus() will let us know if there's immediate raw input to be processed.
    // A (necessary!) side effect is that it also marks the message queue bits as stale,
    // so MsgWaitForMultipleObjects will block.

    // Any pending flag update won't be processed until the queue drains, but this is
    // at most one poll cycle since GetQueueStatus clears the wake bits.
    যদি (HIWORD(GetQueueStatus(QS_RAWINPUT)) & QS_RAWINPUT) {
        প্রত্যাগম thread_data.done ? RINP_QUIT : RINP_CONTINUE;
    }

    স্থির ধ্রুব DWORD WAIT_SIGNAL = WAIT_OBJECT_0;
    স্থির ধ্রুব DWORD WAIT_প্রবেশ = WAIT_OBJECT_0 + 1;

    // There wasn't anything, so we'll wait until new data (or signal_event) wakes us up.
    DWORD wait_status = বার্তা_Wait_For_Multiple_Objects(1, &thread_data.signal_event, FALSE, INFINITE, QS_RAWINPUT);
    যদি (wait_status == WAIT_SIGNAL) {
        // signal_event can only be set if we need to update or quit.
        প্রত্যাগম thread_data.done ? RINP_QUIT : RINP_UPDATE;
    } অন্যথা যদি (wait_status == WAIT_প্রবেশ) {
        প্রত্যাগম RINP_CONTINUE;
    } অন্যথা {
        SDL_LogWarn(SDL_LOG_CATEGORY_প্রবেশ, "Raw input thread exiting, unexpected wait result: %" SDL_PRIuULONG, wait_status);
        প্রত্যাগম RINP_QUIT;
    }
}

স্থির bool Update_Raw_প্রবেশ_Device_Flags(HWND window, Uint32 last_flags, Uint32 new_flags)
{
    // We had nothing enabled, and we're trying to stop everything. Nothing to do.
    যদি (last_flags == new_flags) {
        প্রত্যাগম true;
    }

    RAWINPUTDEVICE devices[2] = { 0 };
    UINT গুনতি = 0;

    ধ্রুব Uint32 old_mouse_flags = last_flags & (ENABLE_RAW_MOUSE_প্রবেশ | RAW_MOUSE_FLAG_NOLEGACY);
    ধ্রুব Uint32 new_mouse_flags = new_flags & (ENABLE_RAW_MOUSE_প্রবেশ | RAW_MOUSE_FLAG_NOLEGACY);

    যদি (old_mouse_flags != new_mouse_flags) {
        devices[গুনতি].usUsagePage = USB_USAGEPAGE_GENERIC_DESKTOP;
        devices[গুনতি].usUsage = USB_USAGE_GENERIC_MOUSE;

        যদি (new_flags & ENABLE_RAW_MOUSE_প্রবেশ) {
            devices[গুনতি].dwFlags = 0;
            devices[গুনতি].hwndTarget = window;
            যদি (new_mouse_flags & RAW_MOUSE_FLAG_NOLEGACY) {
                devices[গুনতি].dwFlags |= RIDEV_NOLEGACY;
            }
        } অন্যথা {
            devices[গুনতি].dwFlags = RIDEV_REMOVE;
            devices[গুনতি].hwndTarget = রিক্ত;
        }

        ++গুনতি;
    }

    ধ্রুব Uint32 old_kb_flags = last_flags & (ENABLE_RAW_KEYBOARD_প্রবেশ | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);
    ধ্রুব Uint32 new_kb_flags = new_flags & (ENABLE_RAW_KEYBOARD_প্রবেশ | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);

    যদি (old_kb_flags != new_kb_flags) {
        devices[গুনতি].usUsagePage = USB_USAGEPAGE_GENERIC_DESKTOP;
        devices[গুনতি].usUsage = USB_USAGE_GENERIC_KEYBOARD;

        যদি (new_kb_flags & ENABLE_RAW_KEYBOARD_প্রবেশ) {
            devices[গুনতি].dwFlags = 0;
            devices[গুনতি].hwndTarget = window;
            যদি (new_kb_flags & RAW_KEYBOARD_FLAG_NOHOTKEYS) {
                devices[গুনতি].dwFlags |= RIDEV_NOHOTKEYS;
            }
            যদি (new_kb_flags & RAW_KEYBOARD_FLAG_INPUTSINK) {
                devices[গুনতি].dwFlags |= RIDEV_INPUTSINK;
            }
        } অন্যথা {
            devices[গুনতি].dwFlags = RIDEV_REMOVE;
            devices[গুনতি].hwndTarget = রিক্ত;
        }

        ++গুনতি;
    }

    যদি (Register_Raw_প্রবেশ_Devices(devices, গুনতি, পরিমাণ(devices[0]))) {
        প্রত্যাগম true;
    }
    প্রত্যাগম false;
}

স্থির DWORD WINAPI WIN_Raw_প্রবেশ_Thread(LPVOID param)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    Uint32 last_flags = 0;
    HWND window;

    SDL_SYS_SetupThread("SDLRawInput");

    window = CreateWindowEx(0, TEXT("Message"), রিক্ত, 0, 0, 0, 0, 0, HWND_MESSAGE, রিক্ত, রিক্ত, রিক্ত);
    যদি (!window) {
        প্রত্যাগম 0;
    }

    // This doesn't *really* need to be atomic, because the parent is waiting for us
    last_flags = SDL_GetAtomicU32(&thread_data.flags);
    যদি (!Update_Raw_প্রবেশ_Device_Flags(window, 0, last_flags)) {
        DestroyWindow(window);
        প্রত্যাগম 0;
    }

    // Make sure we get events as soon as possible
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);

    // Tell the parent we're ready to go!
    SetEvent(thread_data.ready_event);

    Raw_প্রবেশ_Iterate_Result iter_result;

    Uint64 idle_begin = SDL_GetTicksNS();
    যাবত্ ((iter_result = Iterate_Raw_প্রবেশ_Thread()) != RINP_QUIT) {
        বিকল্প (iter_result) {
        পক্ষ RINP_QUIT: // Unreachable
            ভঙ্গ;
        পক্ষ RINP_UPDATE:
        {
            ধ্রুব Uint32 new_flags = SDL_GetAtomicU32(&thread_data.flags);
            যদি (!Update_Raw_প্রবেশ_Device_Flags(window, last_flags, new_flags)) {
                // Revert the shared flags so the main thread can detect the failure
                SDL_SetAtomicU32(&thread_data.flags, last_flags);
            } অন্যথা {
                last_flags = new_flags;
            }
        } ভঙ্গ;
        পক্ষ RINP_CONTINUE:
        {
            Uint64 idle_end = SDL_GetTicksNS();
            Uint64 idle_time = idle_end - idle_begin;
            Uint64 usb_8khz_interval = SDL_US_TO_NS(125);
            Uint64 poll_start = idle_time < usb_8khz_interval ? _this->internal->last_rawinput_poll : idle_end;

            WIN_Poll_Raw_প্রবেশ(_this, poll_start);

            // Reset idle_begin for the next go-around
            idle_begin = SDL_GetTicksNS();
        } ভঙ্গ;
        }
    }

    যদি (_this->internal->raw_প্রবেশ_fake_pen_id) {
        SDL_RemovePenDevice(0, SDL_GetKeyboardFocus(), _this->internal->raw_প্রবেশ_fake_pen_id);
        _this->internal->raw_প্রবেশ_fake_pen_id = 0;
    }

    // Reset this here, since if we're exiting due to failure, WIN_UpdateRawInputEnabled would see a stale value.
    SDL_SetAtomicU32(&thread_data.flags, 0);

    Update_Raw_প্রবেশ_Device_Flags(রিক্ত, last_flags, 0);

    DestroyWindow(window);

    প্রত্যাগম 0;
}

স্থির শূন্য Cleanup_Raw_প্রবেশ_Thread_Data(শূন্য)
{
    যদি (thread_data.thread) {
        thread_data.done = true;
        SetEvent(thread_data.signal_event);
        WaitForSingleObject(thread_data.thread, 3000);
        CloseHandle(thread_data.thread);
    }

    যদি (thread_data.ready_event) {
        CloseHandle(thread_data.ready_event);
    }

    যদি (thread_data.signal_event) {
        CloseHandle(thread_data.signal_event);
    }

    thread_data = (Raw_প্রবেশ_Thread_Data){ 0 };
}

// Computes the desired raw input flags from SDL_VideoData and ensures the
// raw input thread's device registrations match.
// Creates the thread on first use, only WIN_QuitRawInput actually shuts it down.
স্থির bool WIN_Update_Raw_প্রবেশ_Enabled(SDL_VideoDevice *_this)
{
    bool result = false;
    SDL_VideoData *data = _this->internal;
    Uint32 desired_flags = 0;

    যদি (!data->gameinput_context) {
        যদি (data->raw_mouse_enabled) {
            desired_flags |= ENABLE_RAW_MOUSE_প্রবেশ;
            যদি (data->raw_mouse_flag_nolegacy) {
                desired_flags |= RAW_MOUSE_FLAG_NOLEGACY;
            }
        }
        যদি (data->raw_keyboard_enabled) {
            desired_flags |= ENABLE_RAW_KEYBOARD_প্রবেশ;
            যদি (data->raw_keyboard_flag_nohotkeys) {
                desired_flags |= RAW_KEYBOARD_FLAG_NOHOTKEYS;
            }
            যদি (data->raw_keyboard_flag_inputsink) {
                desired_flags |= RAW_KEYBOARD_FLAG_INPUTSINK;
            }
        }
    }

    যদি (desired_flags == SDL_GetAtomicU32(&thread_data.flags)) {
        result = true;
        গচ্ছ done;
    }

    // If the thread exited unexpectedly (e.g. MsgWaitForMultipleObjects failed),
    // the handle is stale. Clean it up so the creation path below can recover.
    যদি (thread_data.thread && WaitForSingleObject(thread_data.thread, 0) != WAIT_TIMEOUT) {
        Cleanup_Raw_প্রবেশ_Thread_Data();
    }

    // The thread will read from this to update its flags
    SDL_SetAtomicU32(&thread_data.flags, desired_flags);

    যদি (thread_data.thread) {
        // Thread is already running. Fire (the event) and forget, it'll read the atomic flags on wakeup.

        // If RegisterRawInputDevices fails, the thread reverts the atomic and the next call
        // to this function will see the mismatch and retry.
        SDL_assert(thread_data.signal_event);
        SetEvent(thread_data.signal_event);
        result = true;
    } অন্যথা যদি (desired_flags) {
        HANDLE wait_handles[2];

        // Thread isn't running, spin it up
        thread_data.ready_event = CreateEvent(রিক্ত, FALSE, FALSE, রিক্ত);
        যদি (!thread_data.ready_event) {
            WIN_SetError("CreateEvent");
            গচ্ছ done;
        }

        thread_data.done = false;
        thread_data.signal_event = CreateEvent(রিক্ত, FALSE, FALSE, রিক্ত);
        যদি (!thread_data.signal_event) {
            WIN_SetError("CreateEvent");
            গচ্ছ done;
        }

        thread_data.thread = CreateThread(রিক্ত, 0, WIN_Raw_প্রবেশ_Thread, রিক্ত, 0, রিক্ত);
        যদি (!thread_data.thread) {
            WIN_SetError("CreateThread");
            গচ্ছ done;
        }

        // Wait for the thread to complete initial setup or exit
        wait_handles[0] = thread_data.ready_event;
        wait_handles[1] = thread_data.thread;
        যদি (WaitForMultipleObjects(2, wait_handles, FALSE, INFINITE) != WAIT_OBJECT_0) {
            SDL_SetError("Couldn't set up raw input handling");
            গচ্ছ done;
        }
        result = true;
    } অন্যথা {
        // Thread isn't running and we tried to disable raw input, nothing to do
        result = true;
    }
done:
    যদি (!result) {
        Cleanup_Raw_প্রবেশ_Thread_Data();
    }
    প্রত্যাগম result;
}

bool WIN_SetRawMouseEnabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;
    data->raw_mouse_enabled = enabled;
    যদি (data->gameinput_context) {
        যদি (!WIN_Update_Game_প্রবেশ_Enabled(_this)) {
            data->raw_mouse_enabled = !enabled;
            প্রত্যাগম false;
        }
    } অন্যথা {
        যদি (!WIN_Update_Raw_প্রবেশ_Enabled(_this)) {
            data->raw_mouse_enabled = !enabled;
            প্রত্যাগম false;
        }
    }
    প্রত্যাগম true;
}

bool WIN_SetRawMouseFlag_NoLegacy(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;

    data->raw_mouse_flag_nolegacy = enabled;

    প্রত্যাগম WIN_Update_Raw_প্রবেশ_Enabled(_this);
}

bool WIN_SetRawKeyboardEnabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;
    data->raw_keyboard_enabled = enabled;
    যদি (data->gameinput_context) {
        যদি (!WIN_Update_Game_প্রবেশ_Enabled(_this)) {
            data->raw_keyboard_enabled = !enabled;
            প্রত্যাগম false;
        }
    } অন্যথা {
        যদি (!WIN_Update_Raw_প্রবেশ_Enabled(_this)) {
            data->raw_keyboard_enabled = !enabled;
            প্রত্যাগম false;
        }
    }
    প্রত্যাগম true;
}

bool WIN_SetRawKeyboardFlag_NoHotkeys(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;

    data->raw_keyboard_flag_nohotkeys = enabled;

    প্রত্যাগম WIN_Update_Raw_প্রবেশ_Enabled(_this);
}

bool WIN_SetRawKeyboardFlag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;

    data->raw_keyboard_flag_inputsink = enabled;

    প্রত্যাগম WIN_Update_Raw_প্রবেশ_Enabled(_this);
}

শূন্য WIN_Quit_Raw_প্রবেশ(SDL_VideoDevice *_this)
{
    Cleanup_Raw_প্রবেশ_Thread_Data();
}

#অন্যথা

bool WIN_SetRawMouseEnabled(SDL_VideoDevice *_this, bool enabled)
{
    প্রত্যাগম SDL_Unsupported();
}

bool WIN_SetRawMouseFlag_NoLegacy(SDL_VideoDevice *_this, bool enabled)
{
    প্রত্যাগম SDL_Unsupported();
}

bool WIN_SetRawKeyboardEnabled(SDL_VideoDevice *_this, bool enabled)
{
    প্রত্যাগম SDL_Unsupported();
}

bool WIN_SetRawKeyboardFlag_NoHotkeys(SDL_VideoDevice *_this, bool enabled)
{
    প্রত্যাগম SDL_Unsupported();
}

bool WIN_SetRawKeyboardFlag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    প্রত্যাগম SDL_Unsupported();
}

শূন্য WIN_Quit_Raw_প্রবেশ(SDL_VideoDevice *_this)
{
}

#endif // !SDL_PLATFORM_XBOXONE && !SDL_PLATFORM_XBOXSERIES

#endif // SDL_VIDEO_DRIVER_WINDOWS

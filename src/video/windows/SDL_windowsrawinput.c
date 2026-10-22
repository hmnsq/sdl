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

প্রকারলেখ কাঠামো
{
    bool done;
    SDL_AtomicU32 flags; // Thread sets this to the actually-set flags if updating state failed
    HANDLE ready_event;
    HANDLE signal_event;
    HANDLE thread;
} Raw_প্রবেশ_Thread_তথ্য;

স্থির Raw_প্রবেশ_Thread_তথ্য thread_তথ্য = { 0 };

প্রকারলেখ গণনা
{
    RINP_QUIT,
    RINP_UPDATE,
    RINP_CONTINUE
} Raw_প্রবেশ_Iterate_ফলাফল;

স্থির Raw_প্রবেশ_Iterate_ফলাফল Iterate_Raw_প্রবেশ_Thread(শূন্য)
{
    // The high-order word of GetQueueStatus() will let us know if there's immediate raw input to be processed.
    // A (necessary!) side effect is that it also marks the message queue bits as stale,
    // so MsgWaitForMultipleObjects will block.

    // Any pending flag update won't be processed until the queue drains, but this is
    // at most one poll cycle since GetQueueStatus clears the wake bits.
    যদি (HIWORD(GetQueueStatus(QS_RAWINPUT)) & QS_RAWINPUT) {
        ফেরত thread_তথ্য.done ? RINP_QUIT : RINP_CONTINUE;
    }

    স্থির ধ্রুবক DWORD WAIT_SIGNAL = WAIT_OBJECT_0;
    স্থির ধ্রুবক DWORD WAIT_প্রবেশ = WAIT_OBJECT_0 + 1;

    // There wasn't anything, so we'll wait until new data (or signal_event) wakes us up.
    DWORD wait_status = বার্তা_Wait_For_Multiple_Objects(1, &thread_তথ্য.signal_event, FALSE, INFINITE, QS_RAWINPUT);
    যদি (wait_status == WAIT_SIGNAL) {
        // signal_event can only be set if we need to update or quit.
        ফেরত thread_তথ্য.done ? RINP_QUIT : RINP_UPDATE;
    } অন্যথা যদি (wait_status == WAIT_প্রবেশ) {
        ফেরত RINP_CONTINUE;
    } অন্যথা {
        SDL_LogWarn(SDL_LOG_CATEGORY_প্রবেশ, "Raw input thread exiting, unexpected wait result: %" SDL_PRIuULONG, wait_status);
        ফেরত RINP_QUIT;
    }
}

স্থির bool Update_Raw_প্রবেশ_Device_Flags(HWND window, Uint32 last_flags, Uint32 new_flags)
{
    // We had nothing enabled, and we're trying to stop everything. Nothing to do.
    যদি (last_flags == new_flags) {
        ফেরত true;
    }

    RAWINPUTDEVICE devices[2] = { 0 };
    UINT গুনতি = 0;

    ধ্রুবক Uint32 old_mouse_flags = last_flags & (ENABLE_RAW_MOUSE_প্রবেশ | RAW_MOUSE_FLAG_NOLEGACY);
    ধ্রুবক Uint32 new_mouse_flags = new_flags & (ENABLE_RAW_MOUSE_প্রবেশ | RAW_MOUSE_FLAG_NOLEGACY);

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
            devices[গুনতি].hwndTarget = ফাঁকা;
        }

        ++গুনতি;
    }

    ধ্রুবক Uint32 old_kb_flags = last_flags & (ENABLE_RAW_KEYBOARD_প্রবেশ | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);
    ধ্রুবক Uint32 new_kb_flags = new_flags & (ENABLE_RAW_KEYBOARD_প্রবেশ | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);

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
            devices[গুনতি].hwndTarget = ফাঁকা;
        }

        ++গুনতি;
    }

    যদি (Register_Raw_প্রবেশ_Devices(devices, গুনতি, আকার(devices[0]))) {
        ফেরত true;
    }
    ফেরত false;
}

স্থির DWORD WINAPI WIN_Raw_প্রবেশ_Thread(LPVOID param)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    Uint32 last_flags = 0;
    HWND window;

    SDL_SYS_SetupThread("SDLRawInput");

    window = CreateWindowEx(0, TEXT("Message"), ফাঁকা, 0, 0, 0, 0, 0, HWND_MESSAGE, ফাঁকা, ফাঁকা, ফাঁকা);
    যদি (!window) {
        ফেরত 0;
    }

    // This doesn't *really* need to be atomic, because the parent is waiting for us
    last_flags = SDL_GetAtomicU32(&thread_তথ্য.flags);
    যদি (!Update_Raw_প্রবেশ_Device_Flags(window, 0, last_flags)) {
        DestroyWindow(window);
        ফেরত 0;
    }

    // Make sure we get events as soon as possible
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);

    // Tell the parent we're ready to go!
    SetEvent(thread_তথ্য.ready_event);

    Raw_প্রবেশ_Iterate_ফলাফল iter_ফলাফল;

    Uint64 idle_begin = SDL_GetTicksNS();
    যখন ((iter_ফলাফল = Iterate_Raw_প্রবেশ_Thread()) != RINP_QUIT) {
        নির্বাচন (iter_ফলাফল) {
        ক্ষেত্র RINP_QUIT: // Unreachable
            বিরতি;
        ক্ষেত্র RINP_UPDATE:
        {
            ধ্রুবক Uint32 new_flags = SDL_GetAtomicU32(&thread_তথ্য.flags);
            যদি (!Update_Raw_প্রবেশ_Device_Flags(window, last_flags, new_flags)) {
                // Revert the shared flags so the main thread can detect the failure
                SDL_SetAtomicU32(&thread_তথ্য.flags, last_flags);
            } অন্যথা {
                last_flags = new_flags;
            }
        } বিরতি;
        ক্ষেত্র RINP_CONTINUE:
        {
            Uint64 idle_end = SDL_GetTicksNS();
            Uint64 idle_time = idle_end - idle_begin;
            Uint64 usb_8khz_interval = SDL_US_TO_NS(125);
            Uint64 poll_start = idle_time < usb_8khz_interval ? _this->internal->last_rawinput_poll : idle_end;

            WIN_Poll_Raw_প্রবেশ(_this, poll_start);

            // Reset idle_begin for the next go-around
            idle_begin = SDL_GetTicksNS();
        } বিরতি;
        }
    }

    যদি (_this->internal->raw_প্রবেশ_fake_pen_id) {
        SDL_RemovePenDevice(0, SDL_GetKeyboardFocus(), _this->internal->raw_প্রবেশ_fake_pen_id);
        _this->internal->raw_প্রবেশ_fake_pen_id = 0;
    }

    // Reset this here, since if we're exiting due to failure, WIN_UpdateRawInputEnabled would see a stale value.
    SDL_SetAtomicU32(&thread_তথ্য.flags, 0);

    Update_Raw_প্রবেশ_Device_Flags(ফাঁকা, last_flags, 0);

    DestroyWindow(window);

    ফেরত 0;
}

স্থির শূন্য Cleanup_Raw_প্রবেশ_Thread_তথ্য(শূন্য)
{
    যদি (thread_তথ্য.thread) {
        thread_তথ্য.done = true;
        SetEvent(thread_তথ্য.signal_event);
        WaitForSingleObject(thread_তথ্য.thread, 3000);
        CloseHandle(thread_তথ্য.thread);
    }

    যদি (thread_তথ্য.ready_event) {
        CloseHandle(thread_তথ্য.ready_event);
    }

    যদি (thread_তথ্য.signal_event) {
        CloseHandle(thread_তথ্য.signal_event);
    }

    thread_তথ্য = (Raw_প্রবেশ_Thread_তথ্য){ 0 };
}

// Computes the desired raw input flags from SDL_VideoData and ensures the
// raw input thread's device registrations match.
// Creates the thread on first use, only WIN_QuitRawInput actually shuts it down.
স্থির bool WIN_Update_Raw_প্রবেশ_Enabled(SDL_VideoDevice *_this)
{
    bool ফলাফল = false;
    SDL_Video_তথ্য *তথ্য = _this->internal;
    Uint32 desired_flags = 0;

    যদি (!তথ্য->gameinput_context) {
        যদি (তথ্য->raw_mouse_enabled) {
            desired_flags |= ENABLE_RAW_MOUSE_প্রবেশ;
            যদি (তথ্য->raw_mouse_flag_nolegacy) {
                desired_flags |= RAW_MOUSE_FLAG_NOLEGACY;
            }
        }
        যদি (তথ্য->raw_keyboard_enabled) {
            desired_flags |= ENABLE_RAW_KEYBOARD_প্রবেশ;
            যদি (তথ্য->raw_keyboard_flag_nohotkeys) {
                desired_flags |= RAW_KEYBOARD_FLAG_NOHOTKEYS;
            }
            যদি (তথ্য->raw_keyboard_flag_inputsink) {
                desired_flags |= RAW_KEYBOARD_FLAG_INPUTSINK;
            }
        }
    }

    যদি (desired_flags == SDL_GetAtomicU32(&thread_তথ্য.flags)) {
        ফলাফল = true;
        যাও done;
    }

    // If the thread exited unexpectedly (e.g. MsgWaitForMultipleObjects failed),
    // the handle is stale. Clean it up so the creation path below can recover.
    যদি (thread_তথ্য.thread && WaitForSingleObject(thread_তথ্য.thread, 0) != WAIT_TIMEOUT) {
        Cleanup_Raw_প্রবেশ_Thread_তথ্য();
    }

    // The thread will read from this to update its flags
    SDL_SetAtomicU32(&thread_তথ্য.flags, desired_flags);

    যদি (thread_তথ্য.thread) {
        // Thread is already running. Fire (the event) and forget, it'll read the atomic flags on wakeup.

        // If RegisterRawInputDevices fails, the thread reverts the atomic and the next call
        // to this function will see the mismatch and retry.
        SDL_assert(thread_তথ্য.signal_event);
        SetEvent(thread_তথ্য.signal_event);
        ফলাফল = true;
    } অন্যথা যদি (desired_flags) {
        HANDLE wait_handles[2];

        // Thread isn't running, spin it up
        thread_তথ্য.ready_event = CreateEvent(ফাঁকা, FALSE, FALSE, ফাঁকা);
        যদি (!thread_তথ্য.ready_event) {
            WIN_SetError("CreateEvent");
            যাও done;
        }

        thread_তথ্য.done = false;
        thread_তথ্য.signal_event = CreateEvent(ফাঁকা, FALSE, FALSE, ফাঁকা);
        যদি (!thread_তথ্য.signal_event) {
            WIN_SetError("CreateEvent");
            যাও done;
        }

        thread_তথ্য.thread = CreateThread(ফাঁকা, 0, WIN_Raw_প্রবেশ_Thread, ফাঁকা, 0, ফাঁকা);
        যদি (!thread_তথ্য.thread) {
            WIN_SetError("CreateThread");
            যাও done;
        }

        // Wait for the thread to complete initial setup or exit
        wait_handles[0] = thread_তথ্য.ready_event;
        wait_handles[1] = thread_তথ্য.thread;
        যদি (WaitForMultipleObjects(2, wait_handles, FALSE, INFINITE) != WAIT_OBJECT_0) {
            SDL_SetError("Couldn't set up raw input handling");
            যাও done;
        }
        ফলাফল = true;
    } অন্যথা {
        // Thread isn't running and we tried to disable raw input, nothing to do
        ফলাফল = true;
    }
done:
    যদি (!ফলাফল) {
        Cleanup_Raw_প্রবেশ_Thread_তথ্য();
    }
    ফেরত ফলাফল;
}

bool WIN_SetRawMouseEnabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_তথ্য *তথ্য = _this->internal;
    তথ্য->raw_mouse_enabled = enabled;
    যদি (তথ্য->gameinput_context) {
        যদি (!WIN_Update_Game_প্রবেশ_Enabled(_this)) {
            তথ্য->raw_mouse_enabled = !enabled;
            ফেরত false;
        }
    } অন্যথা {
        যদি (!WIN_Update_Raw_প্রবেশ_Enabled(_this)) {
            তথ্য->raw_mouse_enabled = !enabled;
            ফেরত false;
        }
    }
    ফেরত true;
}

bool WIN_SetRawMouseFlag_NoLegacy(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_তথ্য *তথ্য = _this->internal;

    তথ্য->raw_mouse_flag_nolegacy = enabled;

    ফেরত WIN_Update_Raw_প্রবেশ_Enabled(_this);
}

bool WIN_SetRawKeyboardEnabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_তথ্য *তথ্য = _this->internal;
    তথ্য->raw_keyboard_enabled = enabled;
    যদি (তথ্য->gameinput_context) {
        যদি (!WIN_Update_Game_প্রবেশ_Enabled(_this)) {
            তথ্য->raw_keyboard_enabled = !enabled;
            ফেরত false;
        }
    } অন্যথা {
        যদি (!WIN_Update_Raw_প্রবেশ_Enabled(_this)) {
            তথ্য->raw_keyboard_enabled = !enabled;
            ফেরত false;
        }
    }
    ফেরত true;
}

bool WIN_SetRawKeyboardFlag_NoHotkeys(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_তথ্য *তথ্য = _this->internal;

    তথ্য->raw_keyboard_flag_nohotkeys = enabled;

    ফেরত WIN_Update_Raw_প্রবেশ_Enabled(_this);
}

bool WIN_SetRawKeyboardFlag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_তথ্য *তথ্য = _this->internal;

    তথ্য->raw_keyboard_flag_inputsink = enabled;

    ফেরত WIN_Update_Raw_প্রবেশ_Enabled(_this);
}

শূন্য WIN_Quit_Raw_প্রবেশ(SDL_VideoDevice *_this)
{
    Cleanup_Raw_প্রবেশ_Thread_তথ্য();
}

#অন্যথা

bool WIN_SetRawMouseEnabled(SDL_VideoDevice *_this, bool enabled)
{
    ফেরত SDL_Unsupported();
}

bool WIN_SetRawMouseFlag_NoLegacy(SDL_VideoDevice *_this, bool enabled)
{
    ফেরত SDL_Unsupported();
}

bool WIN_SetRawKeyboardEnabled(SDL_VideoDevice *_this, bool enabled)
{
    ফেরত SDL_Unsupported();
}

bool WIN_SetRawKeyboardFlag_NoHotkeys(SDL_VideoDevice *_this, bool enabled)
{
    ফেরত SDL_Unsupported();
}

bool WIN_SetRawKeyboardFlag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    ফেরত SDL_Unsupported();
}

শূন্য WIN_Quit_Raw_প্রবেশ(SDL_VideoDevice *_this)
{
}

#endif // !SDL_PLATFORM_XBOXONE && !SDL_PLATFORM_XBOXSERIES

#endif // SDL_VIDEO_DRIVER_WINDOWS

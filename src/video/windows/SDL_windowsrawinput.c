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

#ܐܢ defined(SDL_VIDEO_DRIVER_WINDOWS)

#ضمن "SDL_windowsvideo.h"

#ܐܢ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ضمن "SDL_windowsevents.h"

#ضمن "../../joystick/usb_ids.h"
#ضمن "../../events/SDL_events_c.h"
#ضمن "../../thread/SDL_systhread.h"

#define ENABLE_RAW_MOUSE_INPUT      0x01
#define RAW_MOUSE_FLAG_NOLEGACY     0x02
#define ENABLE_RAW_KEYBOARD_INPUT   0x10
#define RAW_KEYBOARD_FLAG_NOHOTKEYS 0x20
#define RAW_KEYBOARD_FLAG_INPUTSINK 0x40

تعريفنوع بنية
{
    bool done;
    SDL_AtomicU32 flags; // Thread sets this to the actually-set flags if updating state failed
    HANDLE ready_event;
    HANDLE signal_event;
    HANDLE thread;
} RawInputThreadData;

ساكن RawInputThreadData thread_data = { 0 };

تعريفنوع تعداد
{
    RINP_QUIT,
    RINP_UPDATE,
    RINP_CONTINUE
} RawInputIterateResult;

ساكن RawInputIterateResult IterateRawInputThread(فراغ)
{
    // The high-order word of GetQueueStatus() will let us know if there's immediate raw input to be processed.
    // A (necessary!) side effect is that it also marks the message queue bits as stale,
    // so MsgWaitForMultipleObjects will block.

    // Any pending flag update won't be processed until the queue drains, but this is
    // at most one poll cycle since GetQueueStatus clears the wake bits.
    ܐܢ (HIWORD(GetQueueStatus(QS_RAWINPUT)) & QS_RAWINPUT) {
        ܦܢܐ thread_data.done ? RINP_QUIT : RINP_CONTINUE;
    }

    ساكن ثابت DWORD WAIT_SIGNAL = WAIT_OBJECT_0;
    ساكن ثابت DWORD WAIT_INPUT = WAIT_OBJECT_0 + 1;

    // There wasn't anything, so we'll wait until new data (or signal_event) wakes us up.
    DWORD wait_status = MsgWaitForMultipleObjects(1, &thread_data.signal_event, FALSE, INFINITE, QS_RAWINPUT);
    ܐܢ (wait_status == WAIT_SIGNAL) {
        // signal_event can only be set if we need to update or quit.
        ܦܢܐ thread_data.done ? RINP_QUIT : RINP_UPDATE;
    } ܐܚܪܢܐ ܐܢ (wait_status == WAIT_INPUT) {
        ܦܢܐ RINP_CONTINUE;
    } ܐܚܪܢܐ {
        SDL_LogWarn(SDL_LOG_CATEGORY_INPUT, "Raw input thread exiting, unexpected wait result: %" SDL_PRIuULONG, wait_status);
        ܦܢܐ RINP_QUIT;
    }
}

ساكن bool UpdateRawInputDeviceFlags(HWND window, Uint32 last_flags, Uint32 new_flags)
{
    // We had nothing enabled, and we're trying to stop everything. Nothing to do.
    ܐܢ (last_flags == new_flags) {
        ܦܢܐ true;
    }

    RAWINPUTDEVICE devices[2] = { 0 };
    UINT count = 0;

    ثابت Uint32 old_mouse_flags = last_flags & (ENABLE_RAW_MOUSE_INPUT | RAW_MOUSE_FLAG_NOLEGACY);
    ثابت Uint32 new_mouse_flags = new_flags & (ENABLE_RAW_MOUSE_INPUT | RAW_MOUSE_FLAG_NOLEGACY);

    ܐܢ (old_mouse_flags != new_mouse_flags) {
        devices[count].usUsagePage = USB_USAGEPAGE_GENERIC_DESKTOP;
        devices[count].usUsage = USB_USAGE_GENERIC_MOUSE;

        ܐܢ (new_flags & ENABLE_RAW_MOUSE_INPUT) {
            devices[count].dwFlags = 0;
            devices[count].hwndTarget = window;
            ܐܢ (new_mouse_flags & RAW_MOUSE_FLAG_NOLEGACY) {
                devices[count].dwFlags |= RIDEV_NOLEGACY;
            }
        } ܐܚܪܢܐ {
            devices[count].dwFlags = RIDEV_REMOVE;
            devices[count].hwndTarget = عدم;
        }

        ++count;
    }

    ثابت Uint32 old_kb_flags = last_flags & (ENABLE_RAW_KEYBOARD_INPUT | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);
    ثابت Uint32 new_kb_flags = new_flags & (ENABLE_RAW_KEYBOARD_INPUT | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);

    ܐܢ (old_kb_flags != new_kb_flags) {
        devices[count].usUsagePage = USB_USAGEPAGE_GENERIC_DESKTOP;
        devices[count].usUsage = USB_USAGE_GENERIC_KEYBOARD;

        ܐܢ (new_kb_flags & ENABLE_RAW_KEYBOARD_INPUT) {
            devices[count].dwFlags = 0;
            devices[count].hwndTarget = window;
            ܐܢ (new_kb_flags & RAW_KEYBOARD_FLAG_NOHOTKEYS) {
                devices[count].dwFlags |= RIDEV_NOHOTKEYS;
            }
            ܐܢ (new_kb_flags & RAW_KEYBOARD_FLAG_INPUTSINK) {
                devices[count].dwFlags |= RIDEV_INPUTSINK;
            }
        } ܐܚܪܢܐ {
            devices[count].dwFlags = RIDEV_REMOVE;
            devices[count].hwndTarget = عدم;
        }

        ++count;
    }

    ܐܢ (RegisterRawInputDevices(devices, count, حجم(devices[0]))) {
        ܦܢܐ true;
    }
    ܦܢܐ false;
}

ساكن DWORD WINAPI WIN_RawInputThread(LPVOID param)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    Uint32 last_flags = 0;
    HWND window;

    SDL_SYS_SetupThread("SDLRawInput");

    window = CreateWindowEx(0, TEXT("Message"), عدم, 0, 0, 0, 0, 0, HWND_MESSAGE, عدم, عدم, عدم);
    ܐܢ (!window) {
        ܦܢܐ 0;
    }

    // This doesn't *really* need to be atomic, because the parent is waiting for us
    last_flags = SDL_GetAtomicU32(&thread_data.flags);
    ܐܢ (!UpdateRawInputDeviceFlags(window, 0, last_flags)) {
        DestroyWindow(window);
        ܦܢܐ 0;
    }

    // Make sure we get events as soon as possible
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);

    // Tell the parent we're ready to go!
    SetEvent(thread_data.ready_event);

    RawInputIterateResult iter_result;

    Uint64 idle_begin = SDL_GetTicksNS();
    ܟܡܐ ((iter_result = IterateRawInputThread()) != RINP_QUIT) {
        بدل (iter_result) {
        حالة RINP_QUIT: // Unreachable
            اكسر;
        حالة RINP_UPDATE:
        {
            ثابت Uint32 new_flags = SDL_GetAtomicU32(&thread_data.flags);
            ܐܢ (!UpdateRawInputDeviceFlags(window, last_flags, new_flags)) {
                // Revert the shared flags so the main thread can detect the failure
                SDL_SetAtomicU32(&thread_data.flags, last_flags);
            } ܐܚܪܢܐ {
                last_flags = new_flags;
            }
        } اكسر;
        حالة RINP_CONTINUE:
        {
            Uint64 idle_end = SDL_GetTicksNS();
            Uint64 idle_time = idle_end - idle_begin;
            Uint64 usb_8khz_interval = SDL_US_TO_NS(125);
            Uint64 poll_start = idle_time < usb_8khz_interval ? _this->internal->last_rawinput_poll : idle_end;

            WIN_PollRawInput(_this, poll_start);

            // Reset idle_begin for the next go-around
            idle_begin = SDL_GetTicksNS();
        } اكسر;
        }
    }

    ܐܢ (_this->internal->raw_input_fake_pen_id) {
        SDL_RemovePenDevice(0, SDL_GetKeyboardFocus(), _this->internal->raw_input_fake_pen_id);
        _this->internal->raw_input_fake_pen_id = 0;
    }

    // Reset this here, since if we're exiting due to failure, WIN_UpdateRawInputEnabled would see a stale value.
    SDL_SetAtomicU32(&thread_data.flags, 0);

    UpdateRawInputDeviceFlags(عدم, last_flags, 0);

    DestroyWindow(window);

    ܦܢܐ 0;
}

ساكن فراغ CleanupRawInputThreadData(فراغ)
{
    ܐܢ (thread_data.thread) {
        thread_data.done = true;
        SetEvent(thread_data.signal_event);
        WaitForSingleObject(thread_data.thread, 3000);
        CloseHandle(thread_data.thread);
    }

    ܐܢ (thread_data.ready_event) {
        CloseHandle(thread_data.ready_event);
    }

    ܐܢ (thread_data.signal_event) {
        CloseHandle(thread_data.signal_event);
    }

    thread_data = (RawInputThreadData){ 0 };
}

// Computes the desired raw input flags from SDL_VideoData and ensures the
// raw input thread's device registrations match.
// Creates the thread on first use, only WIN_QuitRawInput actually shuts it down.
ساكن bool WIN_UpdateRawInputEnabled(SDL_VideoDevice *_this)
{
    bool result = false;
    SDL_VideoData *data = _this->internal;
    Uint32 desired_flags = 0;

    ܐܢ (!data->gameinput_context) {
        ܐܢ (data->raw_mouse_enabled) {
            desired_flags |= ENABLE_RAW_MOUSE_INPUT;
            ܐܢ (data->raw_mouse_flag_nolegacy) {
                desired_flags |= RAW_MOUSE_FLAG_NOLEGACY;
            }
        }
        ܐܢ (data->raw_keyboard_enabled) {
            desired_flags |= ENABLE_RAW_KEYBOARD_INPUT;
            ܐܢ (data->raw_keyboard_flag_nohotkeys) {
                desired_flags |= RAW_KEYBOARD_FLAG_NOHOTKEYS;
            }
            ܐܢ (data->raw_keyboard_flag_inputsink) {
                desired_flags |= RAW_KEYBOARD_FLAG_INPUTSINK;
            }
        }
    }

    ܐܢ (desired_flags == SDL_GetAtomicU32(&thread_data.flags)) {
        result = true;
        اذهب done;
    }

    // If the thread exited unexpectedly (e.g. MsgWaitForMultipleObjects failed),
    // the handle is stale. Clean it up so the creation path below can recover.
    ܐܢ (thread_data.thread && WaitForSingleObject(thread_data.thread, 0) != WAIT_TIMEOUT) {
        CleanupRawInputThreadData();
    }

    // The thread will read from this to update its flags
    SDL_SetAtomicU32(&thread_data.flags, desired_flags);

    ܐܢ (thread_data.thread) {
        // Thread is already running. Fire (the event) and forget, it'll read the atomic flags on wakeup.

        // If RegisterRawInputDevices fails, the thread reverts the atomic and the next call
        // to this function will see the mismatch and retry.
        SDL_assert(thread_data.signal_event);
        SetEvent(thread_data.signal_event);
        result = true;
    } ܐܚܪܢܐ ܐܢ (desired_flags) {
        HANDLE wait_handles[2];

        // Thread isn't running, spin it up
        thread_data.ready_event = CreateEvent(عدم, FALSE, FALSE, عدم);
        ܐܢ (!thread_data.ready_event) {
            WIN_SetError("CreateEvent");
            اذهب done;
        }

        thread_data.done = false;
        thread_data.signal_event = CreateEvent(عدم, FALSE, FALSE, عدم);
        ܐܢ (!thread_data.signal_event) {
            WIN_SetError("CreateEvent");
            اذهب done;
        }

        thread_data.thread = CreateThread(عدم, 0, WIN_RawInputThread, عدم, 0, عدم);
        ܐܢ (!thread_data.thread) {
            WIN_SetError("CreateThread");
            اذهب done;
        }

        // Wait for the thread to complete initial setup or exit
        wait_handles[0] = thread_data.ready_event;
        wait_handles[1] = thread_data.thread;
        ܐܢ (WaitForMultipleObjects(2, wait_handles, FALSE, INFINITE) != WAIT_OBJECT_0) {
            SDL_SetError("Couldn't set up raw input handling");
            اذهب done;
        }
        result = true;
    } ܐܚܪܢܐ {
        // Thread isn't running and we tried to disable raw input, nothing to do
        result = true;
    }
done:
    ܐܢ (!result) {
        CleanupRawInputThreadData();
    }
    ܦܢܐ result;
}

bool WIN_SetRawMouseEnabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;
    data->raw_mouse_enabled = enabled;
    ܐܢ (data->gameinput_context) {
        ܐܢ (!WIN_UpdateGameInputEnabled(_this)) {
            data->raw_mouse_enabled = !enabled;
            ܦܢܐ false;
        }
    } ܐܚܪܢܐ {
        ܐܢ (!WIN_UpdateRawInputEnabled(_this)) {
            data->raw_mouse_enabled = !enabled;
            ܦܢܐ false;
        }
    }
    ܦܢܐ true;
}

bool WIN_SetRawMouseFlag_NoLegacy(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;

    data->raw_mouse_flag_nolegacy = enabled;

    ܦܢܐ WIN_UpdateRawInputEnabled(_this);
}

bool WIN_SetRawKeyboardEnabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;
    data->raw_keyboard_enabled = enabled;
    ܐܢ (data->gameinput_context) {
        ܐܢ (!WIN_UpdateGameInputEnabled(_this)) {
            data->raw_keyboard_enabled = !enabled;
            ܦܢܐ false;
        }
    } ܐܚܪܢܐ {
        ܐܢ (!WIN_UpdateRawInputEnabled(_this)) {
            data->raw_keyboard_enabled = !enabled;
            ܦܢܐ false;
        }
    }
    ܦܢܐ true;
}

bool WIN_SetRawKeyboardFlag_NoHotkeys(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;

    data->raw_keyboard_flag_nohotkeys = enabled;

    ܦܢܐ WIN_UpdateRawInputEnabled(_this);
}

bool WIN_SetRawKeyboardFlag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;

    data->raw_keyboard_flag_inputsink = enabled;

    ܦܢܐ WIN_UpdateRawInputEnabled(_this);
}

فراغ WIN_QuitRawInput(SDL_VideoDevice *_this)
{
    CleanupRawInputThreadData();
}

#ܐܚܪܢܐ

bool WIN_SetRawMouseEnabled(SDL_VideoDevice *_this, bool enabled)
{
    ܦܢܐ SDL_Unsupported();
}

bool WIN_SetRawMouseFlag_NoLegacy(SDL_VideoDevice *_this, bool enabled)
{
    ܦܢܐ SDL_Unsupported();
}

bool WIN_SetRawKeyboardEnabled(SDL_VideoDevice *_this, bool enabled)
{
    ܦܢܐ SDL_Unsupported();
}

bool WIN_SetRawKeyboardFlag_NoHotkeys(SDL_VideoDevice *_this, bool enabled)
{
    ܦܢܐ SDL_Unsupported();
}

bool WIN_SetRawKeyboardFlag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    ܦܢܐ SDL_Unsupported();
}

فراغ WIN_QuitRawInput(SDL_VideoDevice *_this)
{
}

#endif // !SDL_PLATFORM_XBOXONE && !SDL_PLATFORM_XBOXSERIES

#endif // SDL_VIDEO_DRIVER_WINDOWS

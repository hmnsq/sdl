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

#എങ്കിൽ defined(SDL_VIDEO_DRIVER_WINDOWS)

#അന്തര്ഭാവ "SDL_windowsvideo.h"

#എങ്കിൽ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#അന്തര്ഭാവ "SDL_windowsevents.h"

#അന്തര്ഭാവ "../../joystick/usb_ids.h"
#അന്തര്ഭാവ "../../events/SDL_events_c.h"
#അന്തര്ഭാവ "../../thread/SDL_systhread.h"

#define ENABLE_RAW_MOUSE_നിവേശം      0x01
#define RAW_MOUSE_FLAG_NOLEGACY     0x02
#define ENABLE_RAW_KEYBOARD_നിവേശം   0x10
#define RAW_KEYBOARD_FLAG_NOHOTKEYS 0x20
#define RAW_KEYBOARD_FLAG_INPUTSINK 0x40

തരനിർവചനം ഘടന
{
    bool done;
    SDL_AtomicU32 flags; // Thread sets this to the actually-set flags if updating state failed
    HANDLE ready_event;
    HANDLE signal_event;
    HANDLE thread;
} Raw_നിവേശം_Thread_Data;

സ്ഥിതം Raw_നിവേശം_Thread_Data thread_data = { 0 };

തരനിർവചനം എണ്ണൽ
{
    RINP_QUIT,
    RINP_UPDATE,
    RINP_CONTINUE
} Raw_നിവേശം_Iterate_Result;

സ്ഥിതം Raw_നിവേശം_Iterate_Result Iterate_Raw_നിവേശം_Thread(ശൂന്യം)
{
    // The high-order word of GetQueueStatus() will let us know if there's immediate raw input to be processed.
    // A (necessary!) side effect is that it also marks the message queue bits as stale,
    // so MsgWaitForMultipleObjects will block.

    // Any pending flag update won't be processed until the queue drains, but this is
    // at most one poll cycle since GetQueueStatus clears the wake bits.
    എങ്കിൽ (HIWORD(GetQueueStatus(QS_RAWINPUT)) & QS_RAWINPUT) {
        തിരികെ thread_data.done ? RINP_QUIT : RINP_CONTINUE;
    }

    സ്ഥിതം സ്ഥിരം DWORD WAIT_SIGNAL = WAIT_OBJECT_0;
    സ്ഥിതം സ്ഥിരം DWORD WAIT_നിവേശം = WAIT_OBJECT_0 + 1;

    // There wasn't anything, so we'll wait until new data (or signal_event) wakes us up.
    DWORD wait_status = സന്ദേശം_Wait_For_Multiple_Objects(1, &thread_data.signal_event, FALSE, INFINITE, QS_RAWINPUT);
    എങ്കിൽ (wait_status == WAIT_SIGNAL) {
        // signal_event can only be set if we need to update or quit.
        തിരികെ thread_data.done ? RINP_QUIT : RINP_UPDATE;
    } അല്ലെങ്കിൽ എങ്കിൽ (wait_status == WAIT_നിവേശം) {
        തിരികെ RINP_CONTINUE;
    } അല്ലെങ്കിൽ {
        SDL_LogWarn(SDL_LOG_CATEGORY_നിവേശം, "Raw input thread exiting, unexpected wait result: %" SDL_PRIuULONG, wait_status);
        തിരികെ RINP_QUIT;
    }
}

സ്ഥിതം bool Update_Raw_നിവേശം_Device_Flags(HWND window, Uint32 last_flags, Uint32 new_flags)
{
    // We had nothing enabled, and we're trying to stop everything. Nothing to do.
    എങ്കിൽ (last_flags == new_flags) {
        തിരികെ true;
    }

    RAWINPUTDEVICE devices[2] = { 0 };
    UINT എണ്ണം = 0;

    സ്ഥിരം Uint32 old_mouse_flags = last_flags & (ENABLE_RAW_MOUSE_നിവേശം | RAW_MOUSE_FLAG_NOLEGACY);
    സ്ഥിരം Uint32 new_mouse_flags = new_flags & (ENABLE_RAW_MOUSE_നിവേശം | RAW_MOUSE_FLAG_NOLEGACY);

    എങ്കിൽ (old_mouse_flags != new_mouse_flags) {
        devices[എണ്ണം].usUsagePage = USB_USAGEPAGE_GENERIC_DESKTOP;
        devices[എണ്ണം].usUsage = USB_USAGE_GENERIC_MOUSE;

        എങ്കിൽ (new_flags & ENABLE_RAW_MOUSE_നിവേശം) {
            devices[എണ്ണം].dwFlags = 0;
            devices[എണ്ണം].hwndTarget = window;
            എങ്കിൽ (new_mouse_flags & RAW_MOUSE_FLAG_NOLEGACY) {
                devices[എണ്ണം].dwFlags |= RIDEV_NOLEGACY;
            }
        } അല്ലെങ്കിൽ {
            devices[എണ്ണം].dwFlags = RIDEV_REMOVE;
            devices[എണ്ണം].hwndTarget = ശൂന്യ;
        }

        ++എണ്ണം;
    }

    സ്ഥിരം Uint32 old_kb_flags = last_flags & (ENABLE_RAW_KEYBOARD_നിവേശം | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);
    സ്ഥിരം Uint32 new_kb_flags = new_flags & (ENABLE_RAW_KEYBOARD_നിവേശം | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);

    എങ്കിൽ (old_kb_flags != new_kb_flags) {
        devices[എണ്ണം].usUsagePage = USB_USAGEPAGE_GENERIC_DESKTOP;
        devices[എണ്ണം].usUsage = USB_USAGE_GENERIC_KEYBOARD;

        എങ്കിൽ (new_kb_flags & ENABLE_RAW_KEYBOARD_നിവേശം) {
            devices[എണ്ണം].dwFlags = 0;
            devices[എണ്ണം].hwndTarget = window;
            എങ്കിൽ (new_kb_flags & RAW_KEYBOARD_FLAG_NOHOTKEYS) {
                devices[എണ്ണം].dwFlags |= RIDEV_NOHOTKEYS;
            }
            എങ്കിൽ (new_kb_flags & RAW_KEYBOARD_FLAG_INPUTSINK) {
                devices[എണ്ണം].dwFlags |= RIDEV_INPUTSINK;
            }
        } അല്ലെങ്കിൽ {
            devices[എണ്ണം].dwFlags = RIDEV_REMOVE;
            devices[എണ്ണം].hwndTarget = ശൂന്യ;
        }

        ++എണ്ണം;
    }

    എങ്കിൽ (Register_Raw_നിവേശം_Devices(devices, എണ്ണം, വലുപ്പം(devices[0]))) {
        തിരികെ true;
    }
    തിരികെ false;
}

സ്ഥിതം DWORD WINAPI WIN_Raw_നിവേശം_Thread(LPVOID param)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    Uint32 last_flags = 0;
    HWND window;

    SDL_SYS_SetupThread("SDLRawInput");

    window = CreateWindowEx(0, TEXT("Message"), ശൂന്യ, 0, 0, 0, 0, 0, HWND_MESSAGE, ശൂന്യ, ശൂന്യ, ശൂന്യ);
    എങ്കിൽ (!window) {
        തിരികെ 0;
    }

    // This doesn't *really* need to be atomic, because the parent is waiting for us
    last_flags = SDL_GetAtomicU32(&thread_data.flags);
    എങ്കിൽ (!Update_Raw_നിവേശം_Device_Flags(window, 0, last_flags)) {
        DestroyWindow(window);
        തിരികെ 0;
    }

    // Make sure we get events as soon as possible
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);

    // Tell the parent we're ready to go!
    SetEvent(thread_data.ready_event);

    Raw_നിവേശം_Iterate_Result iter_result;

    Uint64 idle_begin = SDL_GetTicksNS();
    ആകുമ്പോൾ ((iter_result = Iterate_Raw_നിവേശം_Thread()) != RINP_QUIT) {
        തിരഞ്ഞെടുപ്പ് (iter_result) {
        അവസ്ഥ RINP_QUIT: // Unreachable
            നിർത്തുക;
        അവസ്ഥ RINP_UPDATE:
        {
            സ്ഥിരം Uint32 new_flags = SDL_GetAtomicU32(&thread_data.flags);
            എങ്കിൽ (!Update_Raw_നിവേശം_Device_Flags(window, last_flags, new_flags)) {
                // Revert the shared flags so the main thread can detect the failure
                SDL_SetAtomicU32(&thread_data.flags, last_flags);
            } അല്ലെങ്കിൽ {
                last_flags = new_flags;
            }
        } നിർത്തുക;
        അവസ്ഥ RINP_CONTINUE:
        {
            Uint64 idle_end = SDL_GetTicksNS();
            Uint64 idle_time = idle_end - idle_begin;
            Uint64 usb_8khz_interval = SDL_US_TO_NS(125);
            Uint64 poll_start = idle_time < usb_8khz_interval ? _this->internal->last_rawinput_poll : idle_end;

            WIN_Poll_Raw_നിവേശം(_this, poll_start);

            // Reset idle_begin for the next go-around
            idle_begin = SDL_GetTicksNS();
        } നിർത്തുക;
        }
    }

    എങ്കിൽ (_this->internal->raw_നിവേശം_fake_pen_id) {
        SDL_RemovePenDevice(0, SDL_GetKeyboardFocus(), _this->internal->raw_നിവേശം_fake_pen_id);
        _this->internal->raw_നിവേശം_fake_pen_id = 0;
    }

    // Reset this here, since if we're exiting due to failure, WIN_UpdateRawInputEnabled would see a stale value.
    SDL_SetAtomicU32(&thread_data.flags, 0);

    Update_Raw_നിവേശം_Device_Flags(ശൂന്യ, last_flags, 0);

    DestroyWindow(window);

    തിരികെ 0;
}

സ്ഥിതം ശൂന്യം Cleanup_Raw_നിവേശം_Thread_Data(ശൂന്യം)
{
    എങ്കിൽ (thread_data.thread) {
        thread_data.done = true;
        SetEvent(thread_data.signal_event);
        WaitForSingleObject(thread_data.thread, 3000);
        CloseHandle(thread_data.thread);
    }

    എങ്കിൽ (thread_data.ready_event) {
        CloseHandle(thread_data.ready_event);
    }

    എങ്കിൽ (thread_data.signal_event) {
        CloseHandle(thread_data.signal_event);
    }

    thread_data = (Raw_നിവേശം_Thread_Data){ 0 };
}

// Computes the desired raw input flags from SDL_VideoData and ensures the
// raw input thread's device registrations match.
// Creates the thread on first use, only WIN_QuitRawInput actually shuts it down.
സ്ഥിതം bool WIN_Update_Raw_നിവേശം_Enabled(SDL_VideoDevice *_this)
{
    bool result = false;
    SDL_VideoData *data = _this->internal;
    Uint32 desired_flags = 0;

    എങ്കിൽ (!data->gameinput_context) {
        എങ്കിൽ (data->raw_mouse_enabled) {
            desired_flags |= ENABLE_RAW_MOUSE_നിവേശം;
            എങ്കിൽ (data->raw_mouse_flag_nolegacy) {
                desired_flags |= RAW_MOUSE_FLAG_NOLEGACY;
            }
        }
        എങ്കിൽ (data->raw_keyboard_enabled) {
            desired_flags |= ENABLE_RAW_KEYBOARD_നിവേശം;
            എങ്കിൽ (data->raw_keyboard_flag_nohotkeys) {
                desired_flags |= RAW_KEYBOARD_FLAG_NOHOTKEYS;
            }
            എങ്കിൽ (data->raw_keyboard_flag_inputsink) {
                desired_flags |= RAW_KEYBOARD_FLAG_INPUTSINK;
            }
        }
    }

    എങ്കിൽ (desired_flags == SDL_GetAtomicU32(&thread_data.flags)) {
        result = true;
        പോകുക done;
    }

    // If the thread exited unexpectedly (e.g. MsgWaitForMultipleObjects failed),
    // the handle is stale. Clean it up so the creation path below can recover.
    എങ്കിൽ (thread_data.thread && WaitForSingleObject(thread_data.thread, 0) != WAIT_TIMEOUT) {
        Cleanup_Raw_നിവേശം_Thread_Data();
    }

    // The thread will read from this to update its flags
    SDL_SetAtomicU32(&thread_data.flags, desired_flags);

    എങ്കിൽ (thread_data.thread) {
        // Thread is already running. Fire (the event) and forget, it'll read the atomic flags on wakeup.

        // If RegisterRawInputDevices fails, the thread reverts the atomic and the next call
        // to this function will see the mismatch and retry.
        SDL_assert(thread_data.signal_event);
        SetEvent(thread_data.signal_event);
        result = true;
    } അല്ലെങ്കിൽ എങ്കിൽ (desired_flags) {
        HANDLE wait_handles[2];

        // Thread isn't running, spin it up
        thread_data.ready_event = CreateEvent(ശൂന്യ, FALSE, FALSE, ശൂന്യ);
        എങ്കിൽ (!thread_data.ready_event) {
            WIN_SetError("CreateEvent");
            പോകുക done;
        }

        thread_data.done = false;
        thread_data.signal_event = CreateEvent(ശൂന്യ, FALSE, FALSE, ശൂന്യ);
        എങ്കിൽ (!thread_data.signal_event) {
            WIN_SetError("CreateEvent");
            പോകുക done;
        }

        thread_data.thread = CreateThread(ശൂന്യ, 0, WIN_Raw_നിവേശം_Thread, ശൂന്യ, 0, ശൂന്യ);
        എങ്കിൽ (!thread_data.thread) {
            WIN_SetError("CreateThread");
            പോകുക done;
        }

        // Wait for the thread to complete initial setup or exit
        wait_handles[0] = thread_data.ready_event;
        wait_handles[1] = thread_data.thread;
        എങ്കിൽ (WaitForMultipleObjects(2, wait_handles, FALSE, INFINITE) != WAIT_OBJECT_0) {
            SDL_SetError("Couldn't set up raw input handling");
            പോകുക done;
        }
        result = true;
    } അല്ലെങ്കിൽ {
        // Thread isn't running and we tried to disable raw input, nothing to do
        result = true;
    }
done:
    എങ്കിൽ (!result) {
        Cleanup_Raw_നിവേശം_Thread_Data();
    }
    തിരികെ result;
}

bool WIN_SetRawMouseEnabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;
    data->raw_mouse_enabled = enabled;
    എങ്കിൽ (data->gameinput_context) {
        എങ്കിൽ (!WIN_Update_Game_നിവേശം_Enabled(_this)) {
            data->raw_mouse_enabled = !enabled;
            തിരികെ false;
        }
    } അല്ലെങ്കിൽ {
        എങ്കിൽ (!WIN_Update_Raw_നിവേശം_Enabled(_this)) {
            data->raw_mouse_enabled = !enabled;
            തിരികെ false;
        }
    }
    തിരികെ true;
}

bool WIN_SetRawMouseFlag_NoLegacy(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;

    data->raw_mouse_flag_nolegacy = enabled;

    തിരികെ WIN_Update_Raw_നിവേശം_Enabled(_this);
}

bool WIN_SetRawKeyboardEnabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;
    data->raw_keyboard_enabled = enabled;
    എങ്കിൽ (data->gameinput_context) {
        എങ്കിൽ (!WIN_Update_Game_നിവേശം_Enabled(_this)) {
            data->raw_keyboard_enabled = !enabled;
            തിരികെ false;
        }
    } അല്ലെങ്കിൽ {
        എങ്കിൽ (!WIN_Update_Raw_നിവേശം_Enabled(_this)) {
            data->raw_keyboard_enabled = !enabled;
            തിരികെ false;
        }
    }
    തിരികെ true;
}

bool WIN_SetRawKeyboardFlag_NoHotkeys(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;

    data->raw_keyboard_flag_nohotkeys = enabled;

    തിരികെ WIN_Update_Raw_നിവേശം_Enabled(_this);
}

bool WIN_SetRawKeyboardFlag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;

    data->raw_keyboard_flag_inputsink = enabled;

    തിരികെ WIN_Update_Raw_നിവേശം_Enabled(_this);
}

ശൂന്യം WIN_Quit_Raw_നിവേശം(SDL_VideoDevice *_this)
{
    Cleanup_Raw_നിവേശം_Thread_Data();
}

#അല്ലെങ്കിൽ

bool WIN_SetRawMouseEnabled(SDL_VideoDevice *_this, bool enabled)
{
    തിരികെ SDL_Unsupported();
}

bool WIN_SetRawMouseFlag_NoLegacy(SDL_VideoDevice *_this, bool enabled)
{
    തിരികെ SDL_Unsupported();
}

bool WIN_SetRawKeyboardEnabled(SDL_VideoDevice *_this, bool enabled)
{
    തിരികെ SDL_Unsupported();
}

bool WIN_SetRawKeyboardFlag_NoHotkeys(SDL_VideoDevice *_this, bool enabled)
{
    തിരികെ SDL_Unsupported();
}

bool WIN_SetRawKeyboardFlag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    തിരികെ SDL_Unsupported();
}

ശൂന്യം WIN_Quit_Raw_നിവേശം(SDL_VideoDevice *_this)
{
}

#endif // !SDL_PLATFORM_XBOXONE && !SDL_PLATFORM_XBOXSERIES

#endif // SDL_VIDEO_DRIVER_WINDOWS

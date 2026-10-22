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
#அந்தர்பாவ "SDL_internal.h"

#எனில் defined(SDL_VIDEO_DRIVER_WINDOWS)

#அந்தர்பாவ "SDL_windowsvideo.h"

#எனில் !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#அந்தர்பாவ "SDL_windowsevents.h"

#அந்தர்பாவ "../../joystick/usb_ids.h"
#அந்தர்பாவ "../../events/SDL_events_c.h"
#அந்தர்பாவ "../../thread/SDL_systhread.h"

#define ENABLE_RAW_MOUSE_உள்ளீடு      0x01
#define RAW_MOUSE_FLAG_NOLEGACY     0x02
#define ENABLE_RAW_KEYBOARD_உள்ளீடு   0x10
#define RAW_KEYBOARD_FLAG_NOHOTKEYS 0x20
#define RAW_KEYBOARD_FLAG_INPUTSINK 0x40

வகைவரை கட்டமைப்பு
{
    bool done;
    SDL_AtomicU32 flags; // Thread sets this to the actually-set flags if updating state failed
    HANDLE ready_event;
    HANDLE signal_event;
    HANDLE thread;
} Raw_உள்ளீடு_Thread_Data;

நிலையான Raw_உள்ளீடு_Thread_Data thread_data = { 0 };

வகைவரை எண்ணிக்கை
{
    RINP_QUIT,
    RINP_UPDATE,
    RINP_CONTINUE
} Raw_உள்ளீடு_Iterate_Result;

நிலையான Raw_உள்ளீடு_Iterate_Result Iterate_Raw_உள்ளீடு_Thread(வெறுமை)
{
    // The high-order word of GetQueueStatus() will let us know if there's immediate raw input to be processed.
    // A (necessary!) side effect is that it also marks the message queue bits as stale,
    // so MsgWaitForMultipleObjects will block.

    // Any pending flag update won't be processed until the queue drains, but this is
    // at most one poll cycle since GetQueueStatus clears the wake bits.
    எனில் (HIWORD(GetQueueStatus(QS_RAWINPUT)) & QS_RAWINPUT) {
        திரும்பு thread_data.done ? RINP_QUIT : RINP_CONTINUE;
    }

    நிலையான மாறிலி DWORD WAIT_SIGNAL = WAIT_OBJECT_0;
    நிலையான மாறிலி DWORD WAIT_உள்ளீடு = WAIT_OBJECT_0 + 1;

    // There wasn't anything, so we'll wait until new data (or signal_event) wakes us up.
    DWORD wait_status = செய்தி_Wait_For_Multiple_Objects(1, &thread_data.signal_event, FALSE, INFINITE, QS_RAWINPUT);
    எனில் (wait_status == WAIT_SIGNAL) {
        // signal_event can only be set if we need to update or quit.
        திரும்பு thread_data.done ? RINP_QUIT : RINP_UPDATE;
    } இல்லையெனில் எனில் (wait_status == WAIT_உள்ளீடு) {
        திரும்பு RINP_CONTINUE;
    } இல்லையெனில் {
        SDL_LogWarn(SDL_LOG_CATEGORY_உள்ளீடு, "Raw input thread exiting, unexpected wait result: %" SDL_PRIuULONG, wait_status);
        திரும்பு RINP_QUIT;
    }
}

நிலையான bool Update_Raw_உள்ளீடு_Device_Flags(HWND window, Uint32 last_flags, Uint32 new_flags)
{
    // We had nothing enabled, and we're trying to stop everything. Nothing to do.
    எனில் (last_flags == new_flags) {
        திரும்பு true;
    }

    RAWINPUTDEVICE devices[2] = { 0 };
    UINT மொத்தம் = 0;

    மாறிலி Uint32 old_mouse_flags = last_flags & (ENABLE_RAW_MOUSE_உள்ளீடு | RAW_MOUSE_FLAG_NOLEGACY);
    மாறிலி Uint32 new_mouse_flags = new_flags & (ENABLE_RAW_MOUSE_உள்ளீடு | RAW_MOUSE_FLAG_NOLEGACY);

    எனில் (old_mouse_flags != new_mouse_flags) {
        devices[மொத்தம்].usUsagePage = USB_USAGEPAGE_GENERIC_DESKTOP;
        devices[மொத்தம்].usUsage = USB_USAGE_GENERIC_MOUSE;

        எனில் (new_flags & ENABLE_RAW_MOUSE_உள்ளீடு) {
            devices[மொத்தம்].dwFlags = 0;
            devices[மொத்தம்].hwndTarget = window;
            எனில் (new_mouse_flags & RAW_MOUSE_FLAG_NOLEGACY) {
                devices[மொத்தம்].dwFlags |= RIDEV_NOLEGACY;
            }
        } இல்லையெனில் {
            devices[மொத்தம்].dwFlags = RIDEV_REMOVE;
            devices[மொத்தம்].hwndTarget = வெற்று;
        }

        ++மொத்தம்;
    }

    மாறிலி Uint32 old_kb_flags = last_flags & (ENABLE_RAW_KEYBOARD_உள்ளீடு | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);
    மாறிலி Uint32 new_kb_flags = new_flags & (ENABLE_RAW_KEYBOARD_உள்ளீடு | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);

    எனில் (old_kb_flags != new_kb_flags) {
        devices[மொத்தம்].usUsagePage = USB_USAGEPAGE_GENERIC_DESKTOP;
        devices[மொத்தம்].usUsage = USB_USAGE_GENERIC_KEYBOARD;

        எனில் (new_kb_flags & ENABLE_RAW_KEYBOARD_உள்ளீடு) {
            devices[மொத்தம்].dwFlags = 0;
            devices[மொத்தம்].hwndTarget = window;
            எனில் (new_kb_flags & RAW_KEYBOARD_FLAG_NOHOTKEYS) {
                devices[மொத்தம்].dwFlags |= RIDEV_NOHOTKEYS;
            }
            எனில் (new_kb_flags & RAW_KEYBOARD_FLAG_INPUTSINK) {
                devices[மொத்தம்].dwFlags |= RIDEV_INPUTSINK;
            }
        } இல்லையெனில் {
            devices[மொத்தம்].dwFlags = RIDEV_REMOVE;
            devices[மொத்தம்].hwndTarget = வெற்று;
        }

        ++மொத்தம்;
    }

    எனில் (Register_Raw_உள்ளீடு_Devices(devices, மொத்தம், அளவு(devices[0]))) {
        திரும்பு true;
    }
    திரும்பு false;
}

நிலையான DWORD WINAPI WIN_Raw_உள்ளீடு_Thread(LPVOID param)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    Uint32 last_flags = 0;
    HWND window;

    SDL_SYS_SetupThread("SDLRawInput");

    window = CreateWindowEx(0, TEXT("Message"), வெற்று, 0, 0, 0, 0, 0, HWND_MESSAGE, வெற்று, வெற்று, வெற்று);
    எனில் (!window) {
        திரும்பு 0;
    }

    // This doesn't *really* need to be atomic, because the parent is waiting for us
    last_flags = SDL_GetAtomicU32(&thread_data.flags);
    எனில் (!Update_Raw_உள்ளீடு_Device_Flags(window, 0, last_flags)) {
        DestroyWindow(window);
        திரும்பு 0;
    }

    // Make sure we get events as soon as possible
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);

    // Tell the parent we're ready to go!
    SetEvent(thread_data.ready_event);

    Raw_உள்ளீடு_Iterate_Result iter_result;

    Uint64 idle_begin = SDL_GetTicksNS();
    போது ((iter_result = Iterate_Raw_உள்ளீடு_Thread()) != RINP_QUIT) {
        தேர்வு (iter_result) {
        நிலை RINP_QUIT: // Unreachable
            நிறுத்து;
        நிலை RINP_UPDATE:
        {
            மாறிலி Uint32 new_flags = SDL_GetAtomicU32(&thread_data.flags);
            எனில் (!Update_Raw_உள்ளீடு_Device_Flags(window, last_flags, new_flags)) {
                // Revert the shared flags so the main thread can detect the failure
                SDL_SetAtomicU32(&thread_data.flags, last_flags);
            } இல்லையெனில் {
                last_flags = new_flags;
            }
        } நிறுத்து;
        நிலை RINP_CONTINUE:
        {
            Uint64 idle_end = SDL_GetTicksNS();
            Uint64 idle_time = idle_end - idle_begin;
            Uint64 usb_8khz_interval = SDL_US_TO_NS(125);
            Uint64 poll_start = idle_time < usb_8khz_interval ? _this->internal->last_rawinput_poll : idle_end;

            WIN_Poll_Raw_உள்ளீடு(_this, poll_start);

            // Reset idle_begin for the next go-around
            idle_begin = SDL_GetTicksNS();
        } நிறுத்து;
        }
    }

    எனில் (_this->internal->raw_உள்ளீடு_fake_pen_id) {
        SDL_RemovePenDevice(0, SDL_GetKeyboardFocus(), _this->internal->raw_உள்ளீடு_fake_pen_id);
        _this->internal->raw_உள்ளீடு_fake_pen_id = 0;
    }

    // Reset this here, since if we're exiting due to failure, WIN_UpdateRawInputEnabled would see a stale value.
    SDL_SetAtomicU32(&thread_data.flags, 0);

    Update_Raw_உள்ளீடு_Device_Flags(வெற்று, last_flags, 0);

    DestroyWindow(window);

    திரும்பு 0;
}

நிலையான வெறுமை Cleanup_Raw_உள்ளீடு_Thread_Data(வெறுமை)
{
    எனில் (thread_data.thread) {
        thread_data.done = true;
        SetEvent(thread_data.signal_event);
        WaitForSingleObject(thread_data.thread, 3000);
        CloseHandle(thread_data.thread);
    }

    எனில் (thread_data.ready_event) {
        CloseHandle(thread_data.ready_event);
    }

    எனில் (thread_data.signal_event) {
        CloseHandle(thread_data.signal_event);
    }

    thread_data = (Raw_உள்ளீடு_Thread_Data){ 0 };
}

// Computes the desired raw input flags from SDL_VideoData and ensures the
// raw input thread's device registrations match.
// Creates the thread on first use, only WIN_QuitRawInput actually shuts it down.
நிலையான bool WIN_Update_Raw_உள்ளீடு_Enabled(SDL_VideoDevice *_this)
{
    bool result = false;
    SDL_VideoData *data = _this->internal;
    Uint32 desired_flags = 0;

    எனில் (!data->gameinput_context) {
        எனில் (data->raw_mouse_enabled) {
            desired_flags |= ENABLE_RAW_MOUSE_உள்ளீடு;
            எனில் (data->raw_mouse_flag_nolegacy) {
                desired_flags |= RAW_MOUSE_FLAG_NOLEGACY;
            }
        }
        எனில் (data->raw_keyboard_enabled) {
            desired_flags |= ENABLE_RAW_KEYBOARD_உள்ளீடு;
            எனில் (data->raw_keyboard_flag_nohotkeys) {
                desired_flags |= RAW_KEYBOARD_FLAG_NOHOTKEYS;
            }
            எனில் (data->raw_keyboard_flag_inputsink) {
                desired_flags |= RAW_KEYBOARD_FLAG_INPUTSINK;
            }
        }
    }

    எனில் (desired_flags == SDL_GetAtomicU32(&thread_data.flags)) {
        result = true;
        செல் done;
    }

    // If the thread exited unexpectedly (e.g. MsgWaitForMultipleObjects failed),
    // the handle is stale. Clean it up so the creation path below can recover.
    எனில் (thread_data.thread && WaitForSingleObject(thread_data.thread, 0) != WAIT_TIMEOUT) {
        Cleanup_Raw_உள்ளீடு_Thread_Data();
    }

    // The thread will read from this to update its flags
    SDL_SetAtomicU32(&thread_data.flags, desired_flags);

    எனில் (thread_data.thread) {
        // Thread is already running. Fire (the event) and forget, it'll read the atomic flags on wakeup.

        // If RegisterRawInputDevices fails, the thread reverts the atomic and the next call
        // to this function will see the mismatch and retry.
        SDL_assert(thread_data.signal_event);
        SetEvent(thread_data.signal_event);
        result = true;
    } இல்லையெனில் எனில் (desired_flags) {
        HANDLE wait_handles[2];

        // Thread isn't running, spin it up
        thread_data.ready_event = CreateEvent(வெற்று, FALSE, FALSE, வெற்று);
        எனில் (!thread_data.ready_event) {
            WIN_SetError("CreateEvent");
            செல் done;
        }

        thread_data.done = false;
        thread_data.signal_event = CreateEvent(வெற்று, FALSE, FALSE, வெற்று);
        எனில் (!thread_data.signal_event) {
            WIN_SetError("CreateEvent");
            செல் done;
        }

        thread_data.thread = CreateThread(வெற்று, 0, WIN_Raw_உள்ளீடு_Thread, வெற்று, 0, வெற்று);
        எனில் (!thread_data.thread) {
            WIN_SetError("CreateThread");
            செல் done;
        }

        // Wait for the thread to complete initial setup or exit
        wait_handles[0] = thread_data.ready_event;
        wait_handles[1] = thread_data.thread;
        எனில் (WaitForMultipleObjects(2, wait_handles, FALSE, INFINITE) != WAIT_OBJECT_0) {
            SDL_SetError("Couldn't set up raw input handling");
            செல் done;
        }
        result = true;
    } இல்லையெனில் {
        // Thread isn't running and we tried to disable raw input, nothing to do
        result = true;
    }
done:
    எனில் (!result) {
        Cleanup_Raw_உள்ளீடு_Thread_Data();
    }
    திரும்பு result;
}

bool WIN_SetRawMouseEnabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;
    data->raw_mouse_enabled = enabled;
    எனில் (data->gameinput_context) {
        எனில் (!WIN_Update_Game_உள்ளீடு_Enabled(_this)) {
            data->raw_mouse_enabled = !enabled;
            திரும்பு false;
        }
    } இல்லையெனில் {
        எனில் (!WIN_Update_Raw_உள்ளீடு_Enabled(_this)) {
            data->raw_mouse_enabled = !enabled;
            திரும்பு false;
        }
    }
    திரும்பு true;
}

bool WIN_SetRawMouseFlag_NoLegacy(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;

    data->raw_mouse_flag_nolegacy = enabled;

    திரும்பு WIN_Update_Raw_உள்ளீடு_Enabled(_this);
}

bool WIN_SetRawKeyboardEnabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;
    data->raw_keyboard_enabled = enabled;
    எனில் (data->gameinput_context) {
        எனில் (!WIN_Update_Game_உள்ளீடு_Enabled(_this)) {
            data->raw_keyboard_enabled = !enabled;
            திரும்பு false;
        }
    } இல்லையெனில் {
        எனில் (!WIN_Update_Raw_உள்ளீடு_Enabled(_this)) {
            data->raw_keyboard_enabled = !enabled;
            திரும்பு false;
        }
    }
    திரும்பு true;
}

bool WIN_SetRawKeyboardFlag_NoHotkeys(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;

    data->raw_keyboard_flag_nohotkeys = enabled;

    திரும்பு WIN_Update_Raw_உள்ளீடு_Enabled(_this);
}

bool WIN_SetRawKeyboardFlag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;

    data->raw_keyboard_flag_inputsink = enabled;

    திரும்பு WIN_Update_Raw_உள்ளீடு_Enabled(_this);
}

வெறுமை WIN_Quit_Raw_உள்ளீடு(SDL_VideoDevice *_this)
{
    Cleanup_Raw_உள்ளீடு_Thread_Data();
}

#இல்லையெனில்

bool WIN_SetRawMouseEnabled(SDL_VideoDevice *_this, bool enabled)
{
    திரும்பு SDL_Unsupported();
}

bool WIN_SetRawMouseFlag_NoLegacy(SDL_VideoDevice *_this, bool enabled)
{
    திரும்பு SDL_Unsupported();
}

bool WIN_SetRawKeyboardEnabled(SDL_VideoDevice *_this, bool enabled)
{
    திரும்பு SDL_Unsupported();
}

bool WIN_SetRawKeyboardFlag_NoHotkeys(SDL_VideoDevice *_this, bool enabled)
{
    திரும்பு SDL_Unsupported();
}

bool WIN_SetRawKeyboardFlag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    திரும்பு SDL_Unsupported();
}

வெறுமை WIN_Quit_Raw_உள்ளீடு(SDL_VideoDevice *_this)
{
}

#endif // !SDL_PLATFORM_XBOXONE && !SDL_PLATFORM_XBOXSERIES

#endif // SDL_VIDEO_DRIVER_WINDOWS

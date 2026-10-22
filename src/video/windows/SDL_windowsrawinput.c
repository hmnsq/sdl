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
#अन्तर्भाव "SDL_internal.h"

#जर defined(SDL_VIDEO_DRIVER_WINDOWS)

#अन्तर्भाव "SDL_windowsvideo.h"

#जर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#अन्तर्भाव "SDL_windowsevents.h"

#अन्तर्भाव "../../joystick/usb_ids.h"
#अन्तर्भाव "../../events/SDL_events_c.h"
#अन्तर्भाव "../../thread/SDL_systhread.h"

#define ENABLE_RAW_MOUSE_आदान      0x01
#define RAW_MOUSE_FLAG_NOLEGACY     0x02
#define ENABLE_RAW_KEYBOARD_आदान   0x10
#define RAW_KEYBOARD_FLAG_NOHOTKEYS 0x20
#define RAW_KEYBOARD_FLAG_INPUTSINK 0x40

प्रकारव्याख्या संरचना
{
    bool done;
    SDL_AtomicU32 flags; // Thread sets this to the actually-set flags if updating state failed
    HANDLE ready_event;
    HANDLE signal_event;
    HANDLE thread;
} Raw_आदान_Thread_Data;

स्थिर Raw_आदान_Thread_Data thread_data = { 0 };

प्रकारव्याख्या गणना
{
    RINP_QUIT,
    RINP_UPDATE,
    RINP_CONTINUE
} Raw_आदान_Iterate_Result;

स्थिर Raw_आदान_Iterate_Result Iterate_Raw_आदान_Thread(शून्य)
{
    // The high-order word of GetQueueStatus() will let us know if there's immediate raw input to be processed.
    // A (necessary!) side effect is that it also marks the message queue bits as stale,
    // so MsgWaitForMultipleObjects will block.

    // Any pending flag update won't be processed until the queue drains, but this is
    // at most one poll cycle since GetQueueStatus clears the wake bits.
    जर (HIWORD(GetQueueStatus(QS_RAWINPUT)) & QS_RAWINPUT) {
        परत thread_data.done ? RINP_QUIT : RINP_CONTINUE;
    }

    स्थिर स्थिरांक DWORD WAIT_SIGNAL = WAIT_OBJECT_0;
    स्थिर स्थिरांक DWORD WAIT_आदान = WAIT_OBJECT_0 + 1;

    // There wasn't anything, so we'll wait until new data (or signal_event) wakes us up.
    DWORD wait_status = संदेश_Wait_For_Multiple_Objects(1, &thread_data.signal_event, FALSE, INFINITE, QS_RAWINPUT);
    जर (wait_status == WAIT_SIGNAL) {
        // signal_event can only be set if we need to update or quit.
        परत thread_data.done ? RINP_QUIT : RINP_UPDATE;
    } अन्यथा जर (wait_status == WAIT_आदान) {
        परत RINP_CONTINUE;
    } अन्यथा {
        SDL_LogWarn(SDL_LOG_CATEGORY_आदान, "Raw input thread exiting, unexpected wait result: %" SDL_PRIuULONG, wait_status);
        परत RINP_QUIT;
    }
}

स्थिर bool Update_Raw_आदान_Device_Flags(HWND window, Uint32 last_flags, Uint32 new_flags)
{
    // We had nothing enabled, and we're trying to stop everything. Nothing to do.
    जर (last_flags == new_flags) {
        परत true;
    }

    RAWINPUTDEVICE devices[2] = { 0 };
    UINT मोजणी = 0;

    स्थिरांक Uint32 old_mouse_flags = last_flags & (ENABLE_RAW_MOUSE_आदान | RAW_MOUSE_FLAG_NOLEGACY);
    स्थिरांक Uint32 new_mouse_flags = new_flags & (ENABLE_RAW_MOUSE_आदान | RAW_MOUSE_FLAG_NOLEGACY);

    जर (old_mouse_flags != new_mouse_flags) {
        devices[मोजणी].usUsagePage = USB_USAGEPAGE_GENERIC_DESKTOP;
        devices[मोजणी].usUsage = USB_USAGE_GENERIC_MOUSE;

        जर (new_flags & ENABLE_RAW_MOUSE_आदान) {
            devices[मोजणी].dwFlags = 0;
            devices[मोजणी].hwndTarget = window;
            जर (new_mouse_flags & RAW_MOUSE_FLAG_NOLEGACY) {
                devices[मोजणी].dwFlags |= RIDEV_NOLEGACY;
            }
        } अन्यथा {
            devices[मोजणी].dwFlags = RIDEV_REMOVE;
            devices[मोजणी].hwndTarget = रिक्त;
        }

        ++मोजणी;
    }

    स्थिरांक Uint32 old_kb_flags = last_flags & (ENABLE_RAW_KEYBOARD_आदान | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);
    स्थिरांक Uint32 new_kb_flags = new_flags & (ENABLE_RAW_KEYBOARD_आदान | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);

    जर (old_kb_flags != new_kb_flags) {
        devices[मोजणी].usUsagePage = USB_USAGEPAGE_GENERIC_DESKTOP;
        devices[मोजणी].usUsage = USB_USAGE_GENERIC_KEYBOARD;

        जर (new_kb_flags & ENABLE_RAW_KEYBOARD_आदान) {
            devices[मोजणी].dwFlags = 0;
            devices[मोजणी].hwndTarget = window;
            जर (new_kb_flags & RAW_KEYBOARD_FLAG_NOHOTKEYS) {
                devices[मोजणी].dwFlags |= RIDEV_NOHOTKEYS;
            }
            जर (new_kb_flags & RAW_KEYBOARD_FLAG_INPUTSINK) {
                devices[मोजणी].dwFlags |= RIDEV_INPUTSINK;
            }
        } अन्यथा {
            devices[मोजणी].dwFlags = RIDEV_REMOVE;
            devices[मोजणी].hwndTarget = रिक्त;
        }

        ++मोजणी;
    }

    जर (Register_Raw_आदान_Devices(devices, मोजणी, आकार(devices[0]))) {
        परत true;
    }
    परत false;
}

स्थिर DWORD WINAPI WIN_Raw_आदान_Thread(LPVOID param)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    Uint32 last_flags = 0;
    HWND window;

    SDL_SYS_SetupThread("SDLRawInput");

    window = CreateWindowEx(0, TEXT("Message"), रिक्त, 0, 0, 0, 0, 0, HWND_MESSAGE, रिक्त, रिक्त, रिक्त);
    जर (!window) {
        परत 0;
    }

    // This doesn't *really* need to be atomic, because the parent is waiting for us
    last_flags = SDL_GetAtomicU32(&thread_data.flags);
    जर (!Update_Raw_आदान_Device_Flags(window, 0, last_flags)) {
        DestroyWindow(window);
        परत 0;
    }

    // Make sure we get events as soon as possible
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);

    // Tell the parent we're ready to go!
    SetEvent(thread_data.ready_event);

    Raw_आदान_Iterate_Result iter_result;

    Uint64 idle_begin = SDL_GetTicksNS();
    पर्यंत ((iter_result = Iterate_Raw_आदान_Thread()) != RINP_QUIT) {
        निवड (iter_result) {
        स्थिती RINP_QUIT: // Unreachable
            थांबा;
        स्थिती RINP_UPDATE:
        {
            स्थिरांक Uint32 new_flags = SDL_GetAtomicU32(&thread_data.flags);
            जर (!Update_Raw_आदान_Device_Flags(window, last_flags, new_flags)) {
                // Revert the shared flags so the main thread can detect the failure
                SDL_SetAtomicU32(&thread_data.flags, last_flags);
            } अन्यथा {
                last_flags = new_flags;
            }
        } थांबा;
        स्थिती RINP_CONTINUE:
        {
            Uint64 idle_end = SDL_GetTicksNS();
            Uint64 idle_time = idle_end - idle_begin;
            Uint64 usb_8khz_interval = SDL_US_TO_NS(125);
            Uint64 poll_start = idle_time < usb_8khz_interval ? _this->internal->last_rawinput_poll : idle_end;

            WIN_Poll_Raw_आदान(_this, poll_start);

            // Reset idle_begin for the next go-around
            idle_begin = SDL_GetTicksNS();
        } थांबा;
        }
    }

    जर (_this->internal->raw_आदान_fake_pen_id) {
        SDL_RemovePenDevice(0, SDL_GetKeyboardFocus(), _this->internal->raw_आदान_fake_pen_id);
        _this->internal->raw_आदान_fake_pen_id = 0;
    }

    // Reset this here, since if we're exiting due to failure, WIN_UpdateRawInputEnabled would see a stale value.
    SDL_SetAtomicU32(&thread_data.flags, 0);

    Update_Raw_आदान_Device_Flags(रिक्त, last_flags, 0);

    DestroyWindow(window);

    परत 0;
}

स्थिर शून्य Cleanup_Raw_आदान_Thread_Data(शून्य)
{
    जर (thread_data.thread) {
        thread_data.done = true;
        SetEvent(thread_data.signal_event);
        WaitForSingleObject(thread_data.thread, 3000);
        CloseHandle(thread_data.thread);
    }

    जर (thread_data.ready_event) {
        CloseHandle(thread_data.ready_event);
    }

    जर (thread_data.signal_event) {
        CloseHandle(thread_data.signal_event);
    }

    thread_data = (Raw_आदान_Thread_Data){ 0 };
}

// Computes the desired raw input flags from SDL_VideoData and ensures the
// raw input thread's device registrations match.
// Creates the thread on first use, only WIN_QuitRawInput actually shuts it down.
स्थिर bool WIN_Update_Raw_आदान_Enabled(SDL_VideoDevice *_this)
{
    bool result = false;
    SDL_VideoData *data = _this->internal;
    Uint32 desired_flags = 0;

    जर (!data->gameinput_context) {
        जर (data->raw_mouse_enabled) {
            desired_flags |= ENABLE_RAW_MOUSE_आदान;
            जर (data->raw_mouse_flag_nolegacy) {
                desired_flags |= RAW_MOUSE_FLAG_NOLEGACY;
            }
        }
        जर (data->raw_keyboard_enabled) {
            desired_flags |= ENABLE_RAW_KEYBOARD_आदान;
            जर (data->raw_keyboard_flag_nohotkeys) {
                desired_flags |= RAW_KEYBOARD_FLAG_NOHOTKEYS;
            }
            जर (data->raw_keyboard_flag_inputsink) {
                desired_flags |= RAW_KEYBOARD_FLAG_INPUTSINK;
            }
        }
    }

    जर (desired_flags == SDL_GetAtomicU32(&thread_data.flags)) {
        result = true;
        जा done;
    }

    // If the thread exited unexpectedly (e.g. MsgWaitForMultipleObjects failed),
    // the handle is stale. Clean it up so the creation path below can recover.
    जर (thread_data.thread && WaitForSingleObject(thread_data.thread, 0) != WAIT_TIMEOUT) {
        Cleanup_Raw_आदान_Thread_Data();
    }

    // The thread will read from this to update its flags
    SDL_SetAtomicU32(&thread_data.flags, desired_flags);

    जर (thread_data.thread) {
        // Thread is already running. Fire (the event) and forget, it'll read the atomic flags on wakeup.

        // If RegisterRawInputDevices fails, the thread reverts the atomic and the next call
        // to this function will see the mismatch and retry.
        SDL_assert(thread_data.signal_event);
        SetEvent(thread_data.signal_event);
        result = true;
    } अन्यथा जर (desired_flags) {
        HANDLE wait_handles[2];

        // Thread isn't running, spin it up
        thread_data.ready_event = CreateEvent(रिक्त, FALSE, FALSE, रिक्त);
        जर (!thread_data.ready_event) {
            WIN_SetError("CreateEvent");
            जा done;
        }

        thread_data.done = false;
        thread_data.signal_event = CreateEvent(रिक्त, FALSE, FALSE, रिक्त);
        जर (!thread_data.signal_event) {
            WIN_SetError("CreateEvent");
            जा done;
        }

        thread_data.thread = CreateThread(रिक्त, 0, WIN_Raw_आदान_Thread, रिक्त, 0, रिक्त);
        जर (!thread_data.thread) {
            WIN_SetError("CreateThread");
            जा done;
        }

        // Wait for the thread to complete initial setup or exit
        wait_handles[0] = thread_data.ready_event;
        wait_handles[1] = thread_data.thread;
        जर (WaitForMultipleObjects(2, wait_handles, FALSE, INFINITE) != WAIT_OBJECT_0) {
            SDL_SetError("Couldn't set up raw input handling");
            जा done;
        }
        result = true;
    } अन्यथा {
        // Thread isn't running and we tried to disable raw input, nothing to do
        result = true;
    }
done:
    जर (!result) {
        Cleanup_Raw_आदान_Thread_Data();
    }
    परत result;
}

bool WIN_SetRawMouseEnabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;
    data->raw_mouse_enabled = enabled;
    जर (data->gameinput_context) {
        जर (!WIN_Update_Game_आदान_Enabled(_this)) {
            data->raw_mouse_enabled = !enabled;
            परत false;
        }
    } अन्यथा {
        जर (!WIN_Update_Raw_आदान_Enabled(_this)) {
            data->raw_mouse_enabled = !enabled;
            परत false;
        }
    }
    परत true;
}

bool WIN_SetRawMouseFlag_NoLegacy(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;

    data->raw_mouse_flag_nolegacy = enabled;

    परत WIN_Update_Raw_आदान_Enabled(_this);
}

bool WIN_SetRawKeyboardEnabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;
    data->raw_keyboard_enabled = enabled;
    जर (data->gameinput_context) {
        जर (!WIN_Update_Game_आदान_Enabled(_this)) {
            data->raw_keyboard_enabled = !enabled;
            परत false;
        }
    } अन्यथा {
        जर (!WIN_Update_Raw_आदान_Enabled(_this)) {
            data->raw_keyboard_enabled = !enabled;
            परत false;
        }
    }
    परत true;
}

bool WIN_SetRawKeyboardFlag_NoHotkeys(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;

    data->raw_keyboard_flag_nohotkeys = enabled;

    परत WIN_Update_Raw_आदान_Enabled(_this);
}

bool WIN_SetRawKeyboardFlag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;

    data->raw_keyboard_flag_inputsink = enabled;

    परत WIN_Update_Raw_आदान_Enabled(_this);
}

शून्य WIN_Quit_Raw_आदान(SDL_VideoDevice *_this)
{
    Cleanup_Raw_आदान_Thread_Data();
}

#अन्यथा

bool WIN_SetRawMouseEnabled(SDL_VideoDevice *_this, bool enabled)
{
    परत SDL_Unsupported();
}

bool WIN_SetRawMouseFlag_NoLegacy(SDL_VideoDevice *_this, bool enabled)
{
    परत SDL_Unsupported();
}

bool WIN_SetRawKeyboardEnabled(SDL_VideoDevice *_this, bool enabled)
{
    परत SDL_Unsupported();
}

bool WIN_SetRawKeyboardFlag_NoHotkeys(SDL_VideoDevice *_this, bool enabled)
{
    परत SDL_Unsupported();
}

bool WIN_SetRawKeyboardFlag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    परत SDL_Unsupported();
}

शून्य WIN_Quit_Raw_आदान(SDL_VideoDevice *_this)
{
}

#endif // !SDL_PLATFORM_XBOXONE && !SDL_PLATFORM_XBOXSERIES

#endif // SDL_VIDEO_DRIVER_WINDOWS

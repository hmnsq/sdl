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

#सचे defined(SDL_VIDEO_DRIVER_WINDOWS)

#अन्तर्भाव "SDL_windowsvideo.h"

#सचे !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#अन्तर्भाव "SDL_windowsevents.h"

#अन्तर्भाव "../../joystick/usb_ids.h"
#अन्तर्भाव "../../events/SDL_events_c.h"
#अन्तर्भाव "../../thread/SDL_systhread.h"

#define ENABLE_RAW_MOUSE_निवेशः      0x01
#define RAW_MOUSE_FLAG_NOLEGACY     0x02
#define ENABLE_RAW_KEYBOARD_निवेशः   0x10
#define RAW_KEYBOARD_FLAG_NOHOTKEYS 0x20
#define RAW_KEYBOARD_FLAG_INPUTSINK 0x40

प्रकारनिर्देश संरचना
{
    bool done;
    SDL_AtomicU32 flags; // Thread sets this to the actually-set flags if updating state failed
    HANDLE ready_event;
    HANDLE signal_event;
    HANDLE thread;
} Raw_निवेशः_Thread_Data;

स्थिर Raw_निवेशः_Thread_Data thread_data = { 0 };

प्रकारनिर्देश गणना
{
    RINP_QUIT,
    RINP_UPDATE,
    RINP_CONTINUE
} Raw_निवेशः_Iterate_Result;

स्थिर Raw_निवेशः_Iterate_Result Iterate_Raw_निवेशः_Thread(शून्य)
{
    // The high-order word of GetQueueStatus() will let us know if there's immediate raw input to be processed.
    // A (necessary!) side effect is that it also marks the message queue bits as stale,
    // so MsgWaitForMultipleObjects will block.

    // Any pending flag update won't be processed until the queue drains, but this is
    // at most one poll cycle since GetQueueStatus clears the wake bits.
    सचे (HIWORD(GetQueueStatus(QS_RAWINPUT)) & QS_RAWINPUT) {
        पटिनिवत्त thread_data.done ? RINP_QUIT : RINP_CONTINUE;
    }

    स्थिर ध्रुव DWORD WAIT_SIGNAL = WAIT_OBJECT_0;
    स्थिर ध्रुव DWORD WAIT_निवेशः = WAIT_OBJECT_0 + 1;

    // There wasn't anything, so we'll wait until new data (or signal_event) wakes us up.
    DWORD wait_status = सन्देशः_Wait_For_Multiple_Objects(1, &thread_data.signal_event, FALSE, INFINITE, QS_RAWINPUT);
    सचे (wait_status == WAIT_SIGNAL) {
        // signal_event can only be set if we need to update or quit.
        पटिनिवत्त thread_data.done ? RINP_QUIT : RINP_UPDATE;
    } अञ्ञथा सचे (wait_status == WAIT_निवेशः) {
        पटिनिवत्त RINP_CONTINUE;
    } अञ्ञथा {
        SDL_LogWarn(SDL_LOG_CATEGORY_निवेशः, "Raw input thread exiting, unexpected wait result: %" SDL_PRIuULONG, wait_status);
        पटिनिवत्त RINP_QUIT;
    }
}

स्थिर bool Update_Raw_निवेशः_Device_Flags(HWND window, Uint32 last_flags, Uint32 new_flags)
{
    // We had nothing enabled, and we're trying to stop everything. Nothing to do.
    सचे (last_flags == new_flags) {
        पटिनिवत्त true;
    }

    RAWINPUTDEVICE devices[2] = { 0 };
    UINT गणनम् = 0;

    ध्रुव Uint32 old_mouse_flags = last_flags & (ENABLE_RAW_MOUSE_निवेशः | RAW_MOUSE_FLAG_NOLEGACY);
    ध्रुव Uint32 new_mouse_flags = new_flags & (ENABLE_RAW_MOUSE_निवेशः | RAW_MOUSE_FLAG_NOLEGACY);

    सचे (old_mouse_flags != new_mouse_flags) {
        devices[गणनम्].usUsagePage = USB_USAGEPAGE_GENERIC_DESKTOP;
        devices[गणनम्].usUsage = USB_USAGE_GENERIC_MOUSE;

        सचे (new_flags & ENABLE_RAW_MOUSE_निवेशः) {
            devices[गणनम्].dwFlags = 0;
            devices[गणनम्].hwndTarget = window;
            सचे (new_mouse_flags & RAW_MOUSE_FLAG_NOLEGACY) {
                devices[गणनम्].dwFlags |= RIDEV_NOLEGACY;
            }
        } अञ्ञथा {
            devices[गणनम्].dwFlags = RIDEV_REMOVE;
            devices[गणनम्].hwndTarget = रिक्त;
        }

        ++गणनम्;
    }

    ध्रुव Uint32 old_kb_flags = last_flags & (ENABLE_RAW_KEYBOARD_निवेशः | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);
    ध्रुव Uint32 new_kb_flags = new_flags & (ENABLE_RAW_KEYBOARD_निवेशः | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);

    सचे (old_kb_flags != new_kb_flags) {
        devices[गणनम्].usUsagePage = USB_USAGEPAGE_GENERIC_DESKTOP;
        devices[गणनम्].usUsage = USB_USAGE_GENERIC_KEYBOARD;

        सचे (new_kb_flags & ENABLE_RAW_KEYBOARD_निवेशः) {
            devices[गणनम्].dwFlags = 0;
            devices[गणनम्].hwndTarget = window;
            सचे (new_kb_flags & RAW_KEYBOARD_FLAG_NOHOTKEYS) {
                devices[गणनम्].dwFlags |= RIDEV_NOHOTKEYS;
            }
            सचे (new_kb_flags & RAW_KEYBOARD_FLAG_INPUTSINK) {
                devices[गणनम्].dwFlags |= RIDEV_INPUTSINK;
            }
        } अञ्ञथा {
            devices[गणनम्].dwFlags = RIDEV_REMOVE;
            devices[गणनम्].hwndTarget = रिक्त;
        }

        ++गणनम्;
    }

    सचे (Register_Raw_निवेशः_Devices(devices, गणनम्, परिमाण(devices[0]))) {
        पटिनिवत्त true;
    }
    पटिनिवत्त false;
}

स्थिर DWORD WINAPI WIN_Raw_निवेशः_Thread(LPVOID param)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    Uint32 last_flags = 0;
    HWND window;

    SDL_SYS_SetupThread("SDLRawInput");

    window = CreateWindowEx(0, TEXT("Message"), रिक्त, 0, 0, 0, 0, 0, HWND_MESSAGE, रिक्त, रिक्त, रिक्त);
    सचे (!window) {
        पटिनिवत्त 0;
    }

    // This doesn't *really* need to be atomic, because the parent is waiting for us
    last_flags = SDL_GetAtomicU32(&thread_data.flags);
    सचे (!Update_Raw_निवेशः_Device_Flags(window, 0, last_flags)) {
        DestroyWindow(window);
        पटिनिवत्त 0;
    }

    // Make sure we get events as soon as possible
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);

    // Tell the parent we're ready to go!
    SetEvent(thread_data.ready_event);

    Raw_निवेशः_Iterate_Result iter_result;

    Uint64 idle_begin = SDL_GetTicksNS();
    याव ((iter_result = Iterate_Raw_निवेशः_Thread()) != RINP_QUIT) {
        विकल्प (iter_result) {
        पक्ष RINP_QUIT: // Unreachable
            भङ्ग;
        पक्ष RINP_UPDATE:
        {
            ध्रुव Uint32 new_flags = SDL_GetAtomicU32(&thread_data.flags);
            सचे (!Update_Raw_निवेशः_Device_Flags(window, last_flags, new_flags)) {
                // Revert the shared flags so the main thread can detect the failure
                SDL_SetAtomicU32(&thread_data.flags, last_flags);
            } अञ्ञथा {
                last_flags = new_flags;
            }
        } भङ्ग;
        पक्ष RINP_CONTINUE:
        {
            Uint64 idle_end = SDL_GetTicksNS();
            Uint64 idle_time = idle_end - idle_begin;
            Uint64 usb_8khz_interval = SDL_US_TO_NS(125);
            Uint64 poll_start = idle_time < usb_8khz_interval ? _this->internal->last_rawinput_poll : idle_end;

            WIN_Poll_Raw_निवेशः(_this, poll_start);

            // Reset idle_begin for the next go-around
            idle_begin = SDL_GetTicksNS();
        } भङ्ग;
        }
    }

    सचे (_this->internal->raw_निवेशः_fake_pen_id) {
        SDL_RemovePenDevice(0, SDL_GetKeyboardFocus(), _this->internal->raw_निवेशः_fake_pen_id);
        _this->internal->raw_निवेशः_fake_pen_id = 0;
    }

    // Reset this here, since if we're exiting due to failure, WIN_UpdateRawInputEnabled would see a stale value.
    SDL_SetAtomicU32(&thread_data.flags, 0);

    Update_Raw_निवेशः_Device_Flags(रिक्त, last_flags, 0);

    DestroyWindow(window);

    पटिनिवत्त 0;
}

स्थिर शून्य Cleanup_Raw_निवेशः_Thread_Data(शून्य)
{
    सचे (thread_data.thread) {
        thread_data.done = true;
        SetEvent(thread_data.signal_event);
        WaitForSingleObject(thread_data.thread, 3000);
        CloseHandle(thread_data.thread);
    }

    सचे (thread_data.ready_event) {
        CloseHandle(thread_data.ready_event);
    }

    सचे (thread_data.signal_event) {
        CloseHandle(thread_data.signal_event);
    }

    thread_data = (Raw_निवेशः_Thread_Data){ 0 };
}

// Computes the desired raw input flags from SDL_VideoData and ensures the
// raw input thread's device registrations match.
// Creates the thread on first use, only WIN_QuitRawInput actually shuts it down.
स्थिर bool WIN_Update_Raw_निवेशः_Enabled(SDL_VideoDevice *_this)
{
    bool result = false;
    SDL_VideoData *data = _this->internal;
    Uint32 desired_flags = 0;

    सचे (!data->gameinput_context) {
        सचे (data->raw_mouse_enabled) {
            desired_flags |= ENABLE_RAW_MOUSE_निवेशः;
            सचे (data->raw_mouse_flag_nolegacy) {
                desired_flags |= RAW_MOUSE_FLAG_NOLEGACY;
            }
        }
        सचे (data->raw_keyboard_enabled) {
            desired_flags |= ENABLE_RAW_KEYBOARD_निवेशः;
            सचे (data->raw_keyboard_flag_nohotkeys) {
                desired_flags |= RAW_KEYBOARD_FLAG_NOHOTKEYS;
            }
            सचे (data->raw_keyboard_flag_inputsink) {
                desired_flags |= RAW_KEYBOARD_FLAG_INPUTSINK;
            }
        }
    }

    सचे (desired_flags == SDL_GetAtomicU32(&thread_data.flags)) {
        result = true;
        गच्छ done;
    }

    // If the thread exited unexpectedly (e.g. MsgWaitForMultipleObjects failed),
    // the handle is stale. Clean it up so the creation path below can recover.
    सचे (thread_data.thread && WaitForSingleObject(thread_data.thread, 0) != WAIT_TIMEOUT) {
        Cleanup_Raw_निवेशः_Thread_Data();
    }

    // The thread will read from this to update its flags
    SDL_SetAtomicU32(&thread_data.flags, desired_flags);

    सचे (thread_data.thread) {
        // Thread is already running. Fire (the event) and forget, it'll read the atomic flags on wakeup.

        // If RegisterRawInputDevices fails, the thread reverts the atomic and the next call
        // to this function will see the mismatch and retry.
        SDL_assert(thread_data.signal_event);
        SetEvent(thread_data.signal_event);
        result = true;
    } अञ्ञथा सचे (desired_flags) {
        HANDLE wait_handles[2];

        // Thread isn't running, spin it up
        thread_data.ready_event = CreateEvent(रिक्त, FALSE, FALSE, रिक्त);
        सचे (!thread_data.ready_event) {
            WIN_SetError("CreateEvent");
            गच्छ done;
        }

        thread_data.done = false;
        thread_data.signal_event = CreateEvent(रिक्त, FALSE, FALSE, रिक्त);
        सचे (!thread_data.signal_event) {
            WIN_SetError("CreateEvent");
            गच्छ done;
        }

        thread_data.thread = CreateThread(रिक्त, 0, WIN_Raw_निवेशः_Thread, रिक्त, 0, रिक्त);
        सचे (!thread_data.thread) {
            WIN_SetError("CreateThread");
            गच्छ done;
        }

        // Wait for the thread to complete initial setup or exit
        wait_handles[0] = thread_data.ready_event;
        wait_handles[1] = thread_data.thread;
        सचे (WaitForMultipleObjects(2, wait_handles, FALSE, INFINITE) != WAIT_OBJECT_0) {
            SDL_SetError("Couldn't set up raw input handling");
            गच्छ done;
        }
        result = true;
    } अञ्ञथा {
        // Thread isn't running and we tried to disable raw input, nothing to do
        result = true;
    }
done:
    सचे (!result) {
        Cleanup_Raw_निवेशः_Thread_Data();
    }
    पटिनिवत्त result;
}

bool WIN_SetRawMouseEnabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;
    data->raw_mouse_enabled = enabled;
    सचे (data->gameinput_context) {
        सचे (!WIN_Update_Game_निवेशः_Enabled(_this)) {
            data->raw_mouse_enabled = !enabled;
            पटिनिवत्त false;
        }
    } अञ्ञथा {
        सचे (!WIN_Update_Raw_निवेशः_Enabled(_this)) {
            data->raw_mouse_enabled = !enabled;
            पटिनिवत्त false;
        }
    }
    पटिनिवत्त true;
}

bool WIN_SetRawMouseFlag_NoLegacy(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;

    data->raw_mouse_flag_nolegacy = enabled;

    पटिनिवत्त WIN_Update_Raw_निवेशः_Enabled(_this);
}

bool WIN_SetRawKeyboardEnabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;
    data->raw_keyboard_enabled = enabled;
    सचे (data->gameinput_context) {
        सचे (!WIN_Update_Game_निवेशः_Enabled(_this)) {
            data->raw_keyboard_enabled = !enabled;
            पटिनिवत्त false;
        }
    } अञ्ञथा {
        सचे (!WIN_Update_Raw_निवेशः_Enabled(_this)) {
            data->raw_keyboard_enabled = !enabled;
            पटिनिवत्त false;
        }
    }
    पटिनिवत्त true;
}

bool WIN_SetRawKeyboardFlag_NoHotkeys(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;

    data->raw_keyboard_flag_nohotkeys = enabled;

    पटिनिवत्त WIN_Update_Raw_निवेशः_Enabled(_this);
}

bool WIN_SetRawKeyboardFlag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;

    data->raw_keyboard_flag_inputsink = enabled;

    पटिनिवत्त WIN_Update_Raw_निवेशः_Enabled(_this);
}

शून्य WIN_Quit_Raw_निवेशः(SDL_VideoDevice *_this)
{
    Cleanup_Raw_निवेशः_Thread_Data();
}

#अञ्ञथा

bool WIN_SetRawMouseEnabled(SDL_VideoDevice *_this, bool enabled)
{
    पटिनिवत्त SDL_Unsupported();
}

bool WIN_SetRawMouseFlag_NoLegacy(SDL_VideoDevice *_this, bool enabled)
{
    पटिनिवत्त SDL_Unsupported();
}

bool WIN_SetRawKeyboardEnabled(SDL_VideoDevice *_this, bool enabled)
{
    पटिनिवत्त SDL_Unsupported();
}

bool WIN_SetRawKeyboardFlag_NoHotkeys(SDL_VideoDevice *_this, bool enabled)
{
    पटिनिवत्त SDL_Unsupported();
}

bool WIN_SetRawKeyboardFlag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    पटिनिवत्त SDL_Unsupported();
}

शून्य WIN_Quit_Raw_निवेशः(SDL_VideoDevice *_this)
{
}

#endif // !SDL_PLATFORM_XBOXONE && !SDL_PLATFORM_XBOXSERIES

#endif // SDL_VIDEO_DRIVER_WINDOWS

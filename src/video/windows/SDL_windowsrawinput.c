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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ଯଦି defined(SDL_VIDEO_DRIVER_WINDOWS)

#ଅନ୍ତର୍ଭାଵ "SDL_windowsvideo.h"

#ଯଦି !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ଅନ୍ତର୍ଭାଵ "SDL_windowsevents.h"

#ଅନ୍ତର୍ଭାଵ "../../joystick/usb_ids.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_events_c.h"
#ଅନ୍ତର୍ଭାଵ "../../thread/SDL_systhread.h"

#define ENABLE_RAW_MOUSE_ନିବେଶ      0x01
#define RAW_MOUSE_FLAG_NOLEGACY     0x02
#define ENABLE_RAW_KEYBOARD_ନିବେଶ   0x10
#define RAW_KEYBOARD_FLAG_NOHOTKEYS 0x20
#define RAW_KEYBOARD_FLAG_INPUTSINK 0x40

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା
{
    bool done;
    SDL_AtomicU32 flags; // Thread sets this to the actually-set flags if updating state failed
    HANDLE ready_event;
    HANDLE signal_event;
    HANDLE thread;
} Raw_ନିବେଶ_Thread_Data;

ସ୍ଥିର Raw_ନିବେଶ_Thread_Data thread_data = { 0 };

ପ୍ରକାରବ୍ୟାଖ୍ୟା ଗଣନା
{
    RINP_QUIT,
    RINP_UPDATE,
    RINP_CONTINUE
} Raw_ନିବେଶ_Iterate_Result;

ସ୍ଥିର Raw_ନିବେଶ_Iterate_Result Iterate_Raw_ନିବେଶ_Thread(ଶୂନ୍ୟ)
{
    // The high-order word of GetQueueStatus() will let us know if there's immediate raw input to be processed.
    // A (necessary!) side effect is that it also marks the message queue bits as stale,
    // so MsgWaitForMultipleObjects will block.

    // Any pending flag update won't be processed until the queue drains, but this is
    // at most one poll cycle since GetQueueStatus clears the wake bits.
    ଯଦି (HIWORD(GetQueueStatus(QS_RAWINPUT)) & QS_RAWINPUT) {
        ଫେରନ୍ତୁ thread_data.done ? RINP_QUIT : RINP_CONTINUE;
    }

    ସ୍ଥିର ଅଚଳ DWORD WAIT_SIGNAL = WAIT_OBJECT_0;
    ସ୍ଥିର ଅଚଳ DWORD WAIT_ନିବେଶ = WAIT_OBJECT_0 + 1;

    // There wasn't anything, so we'll wait until new data (or signal_event) wakes us up.
    DWORD wait_status = ସନ୍ଦେଶ_Wait_For_Multiple_Objects(1, &thread_data.signal_event, FALSE, INFINITE, QS_RAWINPUT);
    ଯଦି (wait_status == WAIT_SIGNAL) {
        // signal_event can only be set if we need to update or quit.
        ଫେରନ୍ତୁ thread_data.done ? RINP_QUIT : RINP_UPDATE;
    } ଅନ୍ୟଥା ଯଦି (wait_status == WAIT_ନିବେଶ) {
        ଫେରନ୍ତୁ RINP_CONTINUE;
    } ଅନ୍ୟଥା {
        SDL_LogWarn(SDL_LOG_CATEGORY_ନିବେଶ, "Raw input thread exiting, unexpected wait result: %" SDL_PRIuULONG, wait_status);
        ଫେରନ୍ତୁ RINP_QUIT;
    }
}

ସ୍ଥିର bool Update_Raw_ନିବେଶ_Device_Flags(HWND window, Uint32 last_flags, Uint32 new_flags)
{
    // We had nothing enabled, and we're trying to stop everything. Nothing to do.
    ଯଦି (last_flags == new_flags) {
        ଫେରନ୍ତୁ true;
    }

    RAWINPUTDEVICE devices[2] = { 0 };
    UINT ଗଣନା_2 = 0;

    ଅଚଳ Uint32 old_mouse_flags = last_flags & (ENABLE_RAW_MOUSE_ନିବେଶ | RAW_MOUSE_FLAG_NOLEGACY);
    ଅଚଳ Uint32 new_mouse_flags = new_flags & (ENABLE_RAW_MOUSE_ନିବେଶ | RAW_MOUSE_FLAG_NOLEGACY);

    ଯଦି (old_mouse_flags != new_mouse_flags) {
        devices[ଗଣନା_2].usUsagePage = USB_USAGEPAGE_GENERIC_DESKTOP;
        devices[ଗଣନା_2].usUsage = USB_USAGE_GENERIC_MOUSE;

        ଯଦି (new_flags & ENABLE_RAW_MOUSE_ନିବେଶ) {
            devices[ଗଣନା_2].dwFlags = 0;
            devices[ଗଣନା_2].hwndTarget = window;
            ଯଦି (new_mouse_flags & RAW_MOUSE_FLAG_NOLEGACY) {
                devices[ଗଣନା_2].dwFlags |= RIDEV_NOLEGACY;
            }
        } ଅନ୍ୟଥା {
            devices[ଗଣନା_2].dwFlags = RIDEV_REMOVE;
            devices[ଗଣନା_2].hwndTarget = ଖାଲି;
        }

        ++ଗଣନା_2;
    }

    ଅଚଳ Uint32 old_kb_flags = last_flags & (ENABLE_RAW_KEYBOARD_ନିବେଶ | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);
    ଅଚଳ Uint32 new_kb_flags = new_flags & (ENABLE_RAW_KEYBOARD_ନିବେଶ | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);

    ଯଦି (old_kb_flags != new_kb_flags) {
        devices[ଗଣନା_2].usUsagePage = USB_USAGEPAGE_GENERIC_DESKTOP;
        devices[ଗଣନା_2].usUsage = USB_USAGE_GENERIC_KEYBOARD;

        ଯଦି (new_kb_flags & ENABLE_RAW_KEYBOARD_ନିବେଶ) {
            devices[ଗଣନା_2].dwFlags = 0;
            devices[ଗଣନା_2].hwndTarget = window;
            ଯଦି (new_kb_flags & RAW_KEYBOARD_FLAG_NOHOTKEYS) {
                devices[ଗଣନା_2].dwFlags |= RIDEV_NOHOTKEYS;
            }
            ଯଦି (new_kb_flags & RAW_KEYBOARD_FLAG_INPUTSINK) {
                devices[ଗଣନା_2].dwFlags |= RIDEV_INPUTSINK;
            }
        } ଅନ୍ୟଥା {
            devices[ଗଣନା_2].dwFlags = RIDEV_REMOVE;
            devices[ଗଣନା_2].hwndTarget = ଖାଲି;
        }

        ++ଗଣନା_2;
    }

    ଯଦି (Register_Raw_ନିବେଶ_Devices(devices, ଗଣନା_2, ଆକାର(devices[0]))) {
        ଫେରନ୍ତୁ true;
    }
    ଫେରନ୍ତୁ false;
}

ସ୍ଥିର DWORD WINAPI WIN_Raw_ନିବେଶ_Thread(LPVOID param)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    Uint32 last_flags = 0;
    HWND window;

    SDL_SYS_SetupThread("SDLRawInput");

    window = CreateWindowEx(0, TEXT("Message"), ଖାଲି, 0, 0, 0, 0, 0, HWND_MESSAGE, ଖାଲି, ଖାଲି, ଖାଲି);
    ଯଦି (!window) {
        ଫେରନ୍ତୁ 0;
    }

    // This doesn't *really* need to be atomic, because the parent is waiting for us
    last_flags = SDL_GetAtomicU32(&thread_data.flags);
    ଯଦି (!Update_Raw_ନିବେଶ_Device_Flags(window, 0, last_flags)) {
        DestroyWindow(window);
        ଫେରନ୍ତୁ 0;
    }

    // Make sure we get events as soon as possible
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);

    // Tell the parent we're ready to go!
    SetEvent(thread_data.ready_event);

    Raw_ନିବେଶ_Iterate_Result iter_result;

    Uint64 idle_begin = SDL_GetTicksNS();
    ଯେତେବେଳେ ((iter_result = Iterate_Raw_ନିବେଶ_Thread()) != RINP_QUIT) {
        ବାଛ (iter_result) {
        ସ୍ଥିତି RINP_QUIT: // Unreachable
            ଭାଙ୍ଗ;
        ସ୍ଥିତି RINP_UPDATE:
        {
            ଅଚଳ Uint32 new_flags = SDL_GetAtomicU32(&thread_data.flags);
            ଯଦି (!Update_Raw_ନିବେଶ_Device_Flags(window, last_flags, new_flags)) {
                // Revert the shared flags so the main thread can detect the failure
                SDL_SetAtomicU32(&thread_data.flags, last_flags);
            } ଅନ୍ୟଥା {
                last_flags = new_flags;
            }
        } ଭାଙ୍ଗ;
        ସ୍ଥିତି RINP_CONTINUE:
        {
            Uint64 idle_end = SDL_GetTicksNS();
            Uint64 idle_time = idle_end - idle_begin;
            Uint64 usb_8khz_interval = SDL_US_TO_NS(125);
            Uint64 poll_start = idle_time < usb_8khz_interval ? _this->internal->last_rawinput_poll : idle_end;

            WIN_Poll_Raw_ନିବେଶ(_this, poll_start);

            // Reset idle_begin for the next go-around
            idle_begin = SDL_GetTicksNS();
        } ଭାଙ୍ଗ;
        }
    }

    ଯଦି (_this->internal->raw_ନିବେଶ_fake_pen_id) {
        SDL_RemovePenDevice(0, SDL_GetKeyboardFocus(), _this->internal->raw_ନିବେଶ_fake_pen_id);
        _this->internal->raw_ନିବେଶ_fake_pen_id = 0;
    }

    // Reset this here, since if we're exiting due to failure, WIN_UpdateRawInputEnabled would see a stale value.
    SDL_SetAtomicU32(&thread_data.flags, 0);

    Update_Raw_ନିବେଶ_Device_Flags(ଖାଲି, last_flags, 0);

    DestroyWindow(window);

    ଫେରନ୍ତୁ 0;
}

ସ୍ଥିର ଶୂନ୍ୟ Cleanup_Raw_ନିବେଶ_Thread_Data(ଶୂନ୍ୟ)
{
    ଯଦି (thread_data.thread) {
        thread_data.done = true;
        SetEvent(thread_data.signal_event);
        WaitForSingleObject(thread_data.thread, 3000);
        CloseHandle(thread_data.thread);
    }

    ଯଦି (thread_data.ready_event) {
        CloseHandle(thread_data.ready_event);
    }

    ଯଦି (thread_data.signal_event) {
        CloseHandle(thread_data.signal_event);
    }

    thread_data = (Raw_ନିବେଶ_Thread_Data){ 0 };
}

// Computes the desired raw input flags from SDL_VideoData and ensures the
// raw input thread's device registrations match.
// Creates the thread on first use, only WIN_QuitRawInput actually shuts it down.
ସ୍ଥିର bool WIN_Update_Raw_ନିବେଶ_Enabled(SDL_VideoDevice *_this)
{
    bool result = false;
    SDL_VideoData *data = _this->internal;
    Uint32 desired_flags = 0;

    ଯଦି (!data->gameinput_context) {
        ଯଦି (data->raw_mouse_enabled) {
            desired_flags |= ENABLE_RAW_MOUSE_ନିବେଶ;
            ଯଦି (data->raw_mouse_flag_nolegacy) {
                desired_flags |= RAW_MOUSE_FLAG_NOLEGACY;
            }
        }
        ଯଦି (data->raw_keyboard_enabled) {
            desired_flags |= ENABLE_RAW_KEYBOARD_ନିବେଶ;
            ଯଦି (data->raw_keyboard_flag_nohotkeys) {
                desired_flags |= RAW_KEYBOARD_FLAG_NOHOTKEYS;
            }
            ଯଦି (data->raw_keyboard_flag_inputsink) {
                desired_flags |= RAW_KEYBOARD_FLAG_INPUTSINK;
            }
        }
    }

    ଯଦି (desired_flags == SDL_GetAtomicU32(&thread_data.flags)) {
        result = true;
        ଯାଅ done;
    }

    // If the thread exited unexpectedly (e.g. MsgWaitForMultipleObjects failed),
    // the handle is stale. Clean it up so the creation path below can recover.
    ଯଦି (thread_data.thread && WaitForSingleObject(thread_data.thread, 0) != WAIT_TIMEOUT) {
        Cleanup_Raw_ନିବେଶ_Thread_Data();
    }

    // The thread will read from this to update its flags
    SDL_SetAtomicU32(&thread_data.flags, desired_flags);

    ଯଦି (thread_data.thread) {
        // Thread is already running. Fire (the event) and forget, it'll read the atomic flags on wakeup.

        // If RegisterRawInputDevices fails, the thread reverts the atomic and the next call
        // to this function will see the mismatch and retry.
        SDL_assert(thread_data.signal_event);
        SetEvent(thread_data.signal_event);
        result = true;
    } ଅନ୍ୟଥା ଯଦି (desired_flags) {
        HANDLE wait_handles[2];

        // Thread isn't running, spin it up
        thread_data.ready_event = CreateEvent(ଖାଲି, FALSE, FALSE, ଖାଲି);
        ଯଦି (!thread_data.ready_event) {
            WIN_SetError("CreateEvent");
            ଯାଅ done;
        }

        thread_data.done = false;
        thread_data.signal_event = CreateEvent(ଖାଲି, FALSE, FALSE, ଖାଲି);
        ଯଦି (!thread_data.signal_event) {
            WIN_SetError("CreateEvent");
            ଯାଅ done;
        }

        thread_data.thread = CreateThread(ଖାଲି, 0, WIN_Raw_ନିବେଶ_Thread, ଖାଲି, 0, ଖାଲି);
        ଯଦି (!thread_data.thread) {
            WIN_SetError("CreateThread");
            ଯାଅ done;
        }

        // Wait for the thread to complete initial setup or exit
        wait_handles[0] = thread_data.ready_event;
        wait_handles[1] = thread_data.thread;
        ଯଦି (WaitForMultipleObjects(2, wait_handles, FALSE, INFINITE) != WAIT_OBJECT_0) {
            SDL_SetError("Couldn't set up raw input handling");
            ଯାଅ done;
        }
        result = true;
    } ଅନ୍ୟଥା {
        // Thread isn't running and we tried to disable raw input, nothing to do
        result = true;
    }
done:
    ଯଦି (!result) {
        Cleanup_Raw_ନିବେଶ_Thread_Data();
    }
    ଫେରନ୍ତୁ result;
}

bool WIN_SetRawMouseEnabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;
    data->raw_mouse_enabled = enabled;
    ଯଦି (data->gameinput_context) {
        ଯଦି (!WIN_Update_Game_ନିବେଶ_Enabled(_this)) {
            data->raw_mouse_enabled = !enabled;
            ଫେରନ୍ତୁ false;
        }
    } ଅନ୍ୟଥା {
        ଯଦି (!WIN_Update_Raw_ନିବେଶ_Enabled(_this)) {
            data->raw_mouse_enabled = !enabled;
            ଫେରନ୍ତୁ false;
        }
    }
    ଫେରନ୍ତୁ true;
}

bool WIN_SetRawMouseFlag_NoLegacy(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;

    data->raw_mouse_flag_nolegacy = enabled;

    ଫେରନ୍ତୁ WIN_Update_Raw_ନିବେଶ_Enabled(_this);
}

bool WIN_SetRawKeyboardEnabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;
    data->raw_keyboard_enabled = enabled;
    ଯଦି (data->gameinput_context) {
        ଯଦି (!WIN_Update_Game_ନିବେଶ_Enabled(_this)) {
            data->raw_keyboard_enabled = !enabled;
            ଫେରନ୍ତୁ false;
        }
    } ଅନ୍ୟଥା {
        ଯଦି (!WIN_Update_Raw_ନିବେଶ_Enabled(_this)) {
            data->raw_keyboard_enabled = !enabled;
            ଫେରନ୍ତୁ false;
        }
    }
    ଫେରନ୍ତୁ true;
}

bool WIN_SetRawKeyboardFlag_NoHotkeys(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;

    data->raw_keyboard_flag_nohotkeys = enabled;

    ଫେରନ୍ତୁ WIN_Update_Raw_ନିବେଶ_Enabled(_this);
}

bool WIN_SetRawKeyboardFlag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;

    data->raw_keyboard_flag_inputsink = enabled;

    ଫେରନ୍ତୁ WIN_Update_Raw_ନିବେଶ_Enabled(_this);
}

ଶୂନ୍ୟ WIN_Quit_Raw_ନିବେଶ(SDL_VideoDevice *_this)
{
    Cleanup_Raw_ନିବେଶ_Thread_Data();
}

#ଅନ୍ୟଥା

bool WIN_SetRawMouseEnabled(SDL_VideoDevice *_this, bool enabled)
{
    ଫେରନ୍ତୁ SDL_Unsupported();
}

bool WIN_SetRawMouseFlag_NoLegacy(SDL_VideoDevice *_this, bool enabled)
{
    ଫେରନ୍ତୁ SDL_Unsupported();
}

bool WIN_SetRawKeyboardEnabled(SDL_VideoDevice *_this, bool enabled)
{
    ଫେରନ୍ତୁ SDL_Unsupported();
}

bool WIN_SetRawKeyboardFlag_NoHotkeys(SDL_VideoDevice *_this, bool enabled)
{
    ଫେରନ୍ତୁ SDL_Unsupported();
}

bool WIN_SetRawKeyboardFlag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    ଫେରନ୍ତୁ SDL_Unsupported();
}

ଶୂନ୍ୟ WIN_Quit_Raw_ନିବେଶ(SDL_VideoDevice *_this)
{
}

#endif // !SDL_PLATFORM_XBOXONE && !SDL_PLATFORM_XBOXSERIES

#endif // SDL_VIDEO_DRIVER_WINDOWS

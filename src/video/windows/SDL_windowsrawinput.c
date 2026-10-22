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
#અન્તર્ભાવ "SDL_internal.h"

#જો defined(SDL_VIDEO_DRIVER_WINDOWS)

#અન્તર્ભાવ "SDL_windowsvideo.h"

#જો !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#અન્તર્ભાવ "SDL_windowsevents.h"

#અન્તર્ભાવ "../../joystick/usb_ids.h"
#અન્તર્ભાવ "../../events/SDL_events_c.h"
#અન્તર્ભાવ "../../thread/SDL_systhread.h"

#define ENABLE_RAW_MOUSE_આગત      0x01
#define RAW_MOUSE_FLAG_NOLEGACY     0x02
#define ENABLE_RAW_KEYBOARD_આગત   0x10
#define RAW_KEYBOARD_FLAG_NOHOTKEYS 0x20
#define RAW_KEYBOARD_FLAG_INPUTSINK 0x40

પ્રકારવ્યાખ્યા સંરચના
{
    bool done;
    SDL_AtomicU32 flags; // Thread sets this to the actually-set flags if updating state failed
    HANDLE ready_event;
    HANDLE signal_event;
    HANDLE thread;
} Raw_આગત_Thread_Data;

સ્થિર Raw_આગત_Thread_Data thread_data = { 0 };

પ્રકારવ્યાખ્યા ગણના
{
    RINP_QUIT,
    RINP_UPDATE,
    RINP_CONTINUE
} Raw_આગત_Iterate_Result;

સ્થિર Raw_આગત_Iterate_Result Iterate_Raw_આગત_Thread(શૂન્ય)
{
    // The high-order word of GetQueueStatus() will let us know if there's immediate raw input to be processed.
    // A (necessary!) side effect is that it also marks the message queue bits as stale,
    // so MsgWaitForMultipleObjects will block.

    // Any pending flag update won't be processed until the queue drains, but this is
    // at most one poll cycle since GetQueueStatus clears the wake bits.
    જો (HIWORD(GetQueueStatus(QS_RAWINPUT)) & QS_RAWINPUT) {
        પાછા thread_data.done ? RINP_QUIT : RINP_CONTINUE;
    }

    સ્થિર અચલ DWORD WAIT_SIGNAL = WAIT_OBJECT_0;
    સ્થિર અચલ DWORD WAIT_આગત = WAIT_OBJECT_0 + 1;

    // There wasn't anything, so we'll wait until new data (or signal_event) wakes us up.
    DWORD wait_status = સંદેશ_Wait_For_Multiple_Objects(1, &thread_data.signal_event, FALSE, INFINITE, QS_RAWINPUT);
    જો (wait_status == WAIT_SIGNAL) {
        // signal_event can only be set if we need to update or quit.
        પાછા thread_data.done ? RINP_QUIT : RINP_UPDATE;
    } નહીંતર જો (wait_status == WAIT_આગત) {
        પાછા RINP_CONTINUE;
    } નહીંતર {
        SDL_LogWarn(SDL_LOG_CATEGORY_આગત, "Raw input thread exiting, unexpected wait result: %" SDL_PRIuULONG, wait_status);
        પાછા RINP_QUIT;
    }
}

સ્થિર bool Update_Raw_આગત_Device_Flags(HWND window, Uint32 last_flags, Uint32 new_flags)
{
    // We had nothing enabled, and we're trying to stop everything. Nothing to do.
    જો (last_flags == new_flags) {
        પાછા true;
    }

    RAWINPUTDEVICE devices[2] = { 0 };
    UINT ગણતરી = 0;

    અચલ Uint32 old_mouse_flags = last_flags & (ENABLE_RAW_MOUSE_આગત | RAW_MOUSE_FLAG_NOLEGACY);
    અચલ Uint32 new_mouse_flags = new_flags & (ENABLE_RAW_MOUSE_આગત | RAW_MOUSE_FLAG_NOLEGACY);

    જો (old_mouse_flags != new_mouse_flags) {
        devices[ગણતરી].usUsagePage = USB_USAGEPAGE_GENERIC_DESKTOP;
        devices[ગણતરી].usUsage = USB_USAGE_GENERIC_MOUSE;

        જો (new_flags & ENABLE_RAW_MOUSE_આગત) {
            devices[ગણતરી].dwFlags = 0;
            devices[ગણતરી].hwndTarget = window;
            જો (new_mouse_flags & RAW_MOUSE_FLAG_NOLEGACY) {
                devices[ગણતરી].dwFlags |= RIDEV_NOLEGACY;
            }
        } નહીંતર {
            devices[ગણતરી].dwFlags = RIDEV_REMOVE;
            devices[ગણતરી].hwndTarget = ખાલી;
        }

        ++ગણતરી;
    }

    અચલ Uint32 old_kb_flags = last_flags & (ENABLE_RAW_KEYBOARD_આગત | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);
    અચલ Uint32 new_kb_flags = new_flags & (ENABLE_RAW_KEYBOARD_આગત | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);

    જો (old_kb_flags != new_kb_flags) {
        devices[ગણતરી].usUsagePage = USB_USAGEPAGE_GENERIC_DESKTOP;
        devices[ગણતરી].usUsage = USB_USAGE_GENERIC_KEYBOARD;

        જો (new_kb_flags & ENABLE_RAW_KEYBOARD_આગત) {
            devices[ગણતરી].dwFlags = 0;
            devices[ગણતરી].hwndTarget = window;
            જો (new_kb_flags & RAW_KEYBOARD_FLAG_NOHOTKEYS) {
                devices[ગણતરી].dwFlags |= RIDEV_NOHOTKEYS;
            }
            જો (new_kb_flags & RAW_KEYBOARD_FLAG_INPUTSINK) {
                devices[ગણતરી].dwFlags |= RIDEV_INPUTSINK;
            }
        } નહીંતર {
            devices[ગણતરી].dwFlags = RIDEV_REMOVE;
            devices[ગણતરી].hwndTarget = ખાલી;
        }

        ++ગણતરી;
    }

    જો (Register_Raw_આગત_Devices(devices, ગણતરી, કદ(devices[0]))) {
        પાછા true;
    }
    પાછા false;
}

સ્થિર DWORD WINAPI WIN_Raw_આગત_Thread(LPVOID param)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    Uint32 last_flags = 0;
    HWND window;

    SDL_SYS_SetupThread("SDLRawInput");

    window = CreateWindowEx(0, TEXT("Message"), ખાલી, 0, 0, 0, 0, 0, HWND_MESSAGE, ખાલી, ખાલી, ખાલી);
    જો (!window) {
        પાછા 0;
    }

    // This doesn't *really* need to be atomic, because the parent is waiting for us
    last_flags = SDL_GetAtomicU32(&thread_data.flags);
    જો (!Update_Raw_આગત_Device_Flags(window, 0, last_flags)) {
        DestroyWindow(window);
        પાછા 0;
    }

    // Make sure we get events as soon as possible
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);

    // Tell the parent we're ready to go!
    SetEvent(thread_data.ready_event);

    Raw_આગત_Iterate_Result iter_result;

    Uint64 idle_begin = SDL_GetTicksNS();
    જ્યારે ((iter_result = Iterate_Raw_આગત_Thread()) != RINP_QUIT) {
        પસંદગી (iter_result) {
        સ્થિતિ RINP_QUIT: // Unreachable
            તોડો;
        સ્થિતિ RINP_UPDATE:
        {
            અચલ Uint32 new_flags = SDL_GetAtomicU32(&thread_data.flags);
            જો (!Update_Raw_આગત_Device_Flags(window, last_flags, new_flags)) {
                // Revert the shared flags so the main thread can detect the failure
                SDL_SetAtomicU32(&thread_data.flags, last_flags);
            } નહીંતર {
                last_flags = new_flags;
            }
        } તોડો;
        સ્થિતિ RINP_CONTINUE:
        {
            Uint64 idle_end = SDL_GetTicksNS();
            Uint64 idle_time = idle_end - idle_begin;
            Uint64 usb_8khz_interval = SDL_US_TO_NS(125);
            Uint64 poll_start = idle_time < usb_8khz_interval ? _this->internal->last_rawinput_poll : idle_end;

            WIN_Poll_Raw_આગત(_this, poll_start);

            // Reset idle_begin for the next go-around
            idle_begin = SDL_GetTicksNS();
        } તોડો;
        }
    }

    જો (_this->internal->raw_આગત_fake_pen_id) {
        SDL_RemovePenDevice(0, SDL_GetKeyboardFocus(), _this->internal->raw_આગત_fake_pen_id);
        _this->internal->raw_આગત_fake_pen_id = 0;
    }

    // Reset this here, since if we're exiting due to failure, WIN_UpdateRawInputEnabled would see a stale value.
    SDL_SetAtomicU32(&thread_data.flags, 0);

    Update_Raw_આગત_Device_Flags(ખાલી, last_flags, 0);

    DestroyWindow(window);

    પાછા 0;
}

સ્થિર શૂન્ય Cleanup_Raw_આગત_Thread_Data(શૂન્ય)
{
    જો (thread_data.thread) {
        thread_data.done = true;
        SetEvent(thread_data.signal_event);
        WaitForSingleObject(thread_data.thread, 3000);
        CloseHandle(thread_data.thread);
    }

    જો (thread_data.ready_event) {
        CloseHandle(thread_data.ready_event);
    }

    જો (thread_data.signal_event) {
        CloseHandle(thread_data.signal_event);
    }

    thread_data = (Raw_આગત_Thread_Data){ 0 };
}

// Computes the desired raw input flags from SDL_VideoData and ensures the
// raw input thread's device registrations match.
// Creates the thread on first use, only WIN_QuitRawInput actually shuts it down.
સ્થિર bool WIN_Update_Raw_આગત_Enabled(SDL_VideoDevice *_this)
{
    bool result = false;
    SDL_VideoData *data = _this->internal;
    Uint32 desired_flags = 0;

    જો (!data->gameinput_context) {
        જો (data->raw_mouse_enabled) {
            desired_flags |= ENABLE_RAW_MOUSE_આગત;
            જો (data->raw_mouse_flag_nolegacy) {
                desired_flags |= RAW_MOUSE_FLAG_NOLEGACY;
            }
        }
        જો (data->raw_keyboard_enabled) {
            desired_flags |= ENABLE_RAW_KEYBOARD_આગત;
            જો (data->raw_keyboard_flag_nohotkeys) {
                desired_flags |= RAW_KEYBOARD_FLAG_NOHOTKEYS;
            }
            જો (data->raw_keyboard_flag_inputsink) {
                desired_flags |= RAW_KEYBOARD_FLAG_INPUTSINK;
            }
        }
    }

    જો (desired_flags == SDL_GetAtomicU32(&thread_data.flags)) {
        result = true;
        જાઓ done;
    }

    // If the thread exited unexpectedly (e.g. MsgWaitForMultipleObjects failed),
    // the handle is stale. Clean it up so the creation path below can recover.
    જો (thread_data.thread && WaitForSingleObject(thread_data.thread, 0) != WAIT_TIMEOUT) {
        Cleanup_Raw_આગત_Thread_Data();
    }

    // The thread will read from this to update its flags
    SDL_SetAtomicU32(&thread_data.flags, desired_flags);

    જો (thread_data.thread) {
        // Thread is already running. Fire (the event) and forget, it'll read the atomic flags on wakeup.

        // If RegisterRawInputDevices fails, the thread reverts the atomic and the next call
        // to this function will see the mismatch and retry.
        SDL_assert(thread_data.signal_event);
        SetEvent(thread_data.signal_event);
        result = true;
    } નહીંતર જો (desired_flags) {
        HANDLE wait_handles[2];

        // Thread isn't running, spin it up
        thread_data.ready_event = CreateEvent(ખાલી, FALSE, FALSE, ખાલી);
        જો (!thread_data.ready_event) {
            WIN_SetError("CreateEvent");
            જાઓ done;
        }

        thread_data.done = false;
        thread_data.signal_event = CreateEvent(ખાલી, FALSE, FALSE, ખાલી);
        જો (!thread_data.signal_event) {
            WIN_SetError("CreateEvent");
            જાઓ done;
        }

        thread_data.thread = CreateThread(ખાલી, 0, WIN_Raw_આગત_Thread, ખાલી, 0, ખાલી);
        જો (!thread_data.thread) {
            WIN_SetError("CreateThread");
            જાઓ done;
        }

        // Wait for the thread to complete initial setup or exit
        wait_handles[0] = thread_data.ready_event;
        wait_handles[1] = thread_data.thread;
        જો (WaitForMultipleObjects(2, wait_handles, FALSE, INFINITE) != WAIT_OBJECT_0) {
            SDL_SetError("Couldn't set up raw input handling");
            જાઓ done;
        }
        result = true;
    } નહીંતર {
        // Thread isn't running and we tried to disable raw input, nothing to do
        result = true;
    }
done:
    જો (!result) {
        Cleanup_Raw_આગત_Thread_Data();
    }
    પાછા result;
}

bool WIN_SetRawMouseEnabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;
    data->raw_mouse_enabled = enabled;
    જો (data->gameinput_context) {
        જો (!WIN_Update_Game_આગત_Enabled(_this)) {
            data->raw_mouse_enabled = !enabled;
            પાછા false;
        }
    } નહીંતર {
        જો (!WIN_Update_Raw_આગત_Enabled(_this)) {
            data->raw_mouse_enabled = !enabled;
            પાછા false;
        }
    }
    પાછા true;
}

bool WIN_SetRawMouseFlag_NoLegacy(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;

    data->raw_mouse_flag_nolegacy = enabled;

    પાછા WIN_Update_Raw_આગત_Enabled(_this);
}

bool WIN_SetRawKeyboardEnabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;
    data->raw_keyboard_enabled = enabled;
    જો (data->gameinput_context) {
        જો (!WIN_Update_Game_આગત_Enabled(_this)) {
            data->raw_keyboard_enabled = !enabled;
            પાછા false;
        }
    } નહીંતર {
        જો (!WIN_Update_Raw_આગત_Enabled(_this)) {
            data->raw_keyboard_enabled = !enabled;
            પાછા false;
        }
    }
    પાછા true;
}

bool WIN_SetRawKeyboardFlag_NoHotkeys(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;

    data->raw_keyboard_flag_nohotkeys = enabled;

    પાછા WIN_Update_Raw_આગત_Enabled(_this);
}

bool WIN_SetRawKeyboardFlag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    SDL_VideoData *data = _this->internal;

    data->raw_keyboard_flag_inputsink = enabled;

    પાછા WIN_Update_Raw_આગત_Enabled(_this);
}

શૂન્ય WIN_Quit_Raw_આગત(SDL_VideoDevice *_this)
{
    Cleanup_Raw_આગત_Thread_Data();
}

#નહીંતર

bool WIN_SetRawMouseEnabled(SDL_VideoDevice *_this, bool enabled)
{
    પાછા SDL_Unsupported();
}

bool WIN_SetRawMouseFlag_NoLegacy(SDL_VideoDevice *_this, bool enabled)
{
    પાછા SDL_Unsupported();
}

bool WIN_SetRawKeyboardEnabled(SDL_VideoDevice *_this, bool enabled)
{
    પાછા SDL_Unsupported();
}

bool WIN_SetRawKeyboardFlag_NoHotkeys(SDL_VideoDevice *_this, bool enabled)
{
    પાછા SDL_Unsupported();
}

bool WIN_SetRawKeyboardFlag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    પાછા SDL_Unsupported();
}

શૂન્ય WIN_Quit_Raw_આગત(SDL_VideoDevice *_this)
{
}

#endif // !SDL_PLATFORM_XBOXONE && !SDL_PLATFORM_XBOXSERIES

#endif // SDL_VIDEO_DRIVER_WINDOWS

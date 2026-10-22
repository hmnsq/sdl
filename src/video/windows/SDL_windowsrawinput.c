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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ defined(SDL_VIDEO_DRIVER_WINDOWS)

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_windowsvideo.h"

#ਜੇ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_windowsevents.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "../../joystick/usb_ids.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_events_c.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../thread/SDL_systhread.h"

#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ENABLE_RAW_MOUSE_ਨਿਵੇਸ਼      0x01
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RAW_MOUSE_FLAG_NOLEGACY     0x02
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ ENABLE_RAW_KEYBOARD_ਨਿਵੇਸ਼   0x10
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RAW_KEYBOARD_FLAG_NOHOTKEYS 0x20
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ RAW_KEYBOARD_FLAG_INPUTSINK 0x40

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ
{
    bool ਪੂਰਾ;
    SDL_AtomicU32 flags; // Thread sets this to the actually-set flags if updating state failed
    HANDLE ready_event;
    HANDLE signal_event;
    HANDLE thread;
} Raw_ਨਿਵੇਸ਼_Thread_ਅੰਕੜੇ;

ਸਥਿਰ Raw_ਨਿਵੇਸ਼_Thread_ਅੰਕੜੇ thread_ਅੰਕੜੇ = { 0 };

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ
{
    RINP_QUIT,
    RINP_UPDATE,
    RINP_CONTINUE
} Raw_ਨਿਵੇਸ਼_Iterate_ਨਤੀਜਾ;

ਸਥਿਰ Raw_ਨਿਵੇਸ਼_Iterate_ਨਤੀਜਾ Iterate_Raw_ਨਿਵੇਸ਼_Thread(ਖਾਲੀ)
{
    // The high-order word of GetQueueStatus() will let us know if there's immediate raw input to be processed.
    // A (necessary!) side effect is that it also marks the message queue bits as stale,
    // so MsgWaitForMultipleObjects will block.

    // Any pending flag update won't be processed until the queue drains, but this is
    // at most one poll cycle since GetQueueStatus clears the wake bits.
    ਜੇ (HIWORD(Get_ਕਤਾਰ_ਸਥਿਤੀ(QS_RAWINPUT)) & QS_RAWINPUT) {
        ਵਾਪਸ thread_ਅੰਕੜੇ.ਪੂਰਾ ? RINP_QUIT : RINP_CONTINUE;
    }

    ਸਥਿਰ ਅਚਲ DWORD WAIT_SIGNAL = WAIT_OBJECT_0;
    ਸਥਿਰ ਅਚਲ DWORD WAIT_ਨਿਵੇਸ਼ = WAIT_OBJECT_0 + 1;

    // There wasn't anything, so we'll wait until new data (or signal_event) wakes us up.
    DWORD wait_ਸਥਿਤੀ = ਸੁਨੇਹਾ_Wait_For_ਗੁਣਜ_Objects(1, &thread_ਅੰਕੜੇ.signal_event, FALSE, INFINITE, QS_RAWINPUT);
    ਜੇ (wait_ਸਥਿਤੀ == WAIT_SIGNAL) {
        // signal_event can only be set if we need to update or quit.
        ਵਾਪਸ thread_ਅੰਕੜੇ.ਪੂਰਾ ? RINP_QUIT : RINP_UPDATE;
    } ਨਹੀਂਤਾਂ ਜੇ (wait_ਸਥਿਤੀ == WAIT_ਨਿਵੇਸ਼) {
        ਵਾਪਸ RINP_CONTINUE;
    } ਨਹੀਂਤਾਂ {
        SDL_LogWarn(SDL_LOG_CATEGORY_ਨਿਵੇਸ਼, "Raw input thread exiting, unexpected wait result: %" SDL_PRIuULONG, wait_ਸਥਿਤੀ);
        ਵਾਪਸ RINP_QUIT;
    }
}

ਸਥਿਰ bool Update_Raw_ਨਿਵੇਸ਼_Device_Flags(HWND ਖਿੜਕੀ, Uint32 ਆਖਰੀ_flags, Uint32 new_flags)
{
    // We had nothing enabled, and we're trying to stop everything. Nothing to do.
    ਜੇ (ਆਖਰੀ_flags == new_flags) {
        ਵਾਪਸ true;
    }

    RAWINPUTDEVICE devices[2] = { 0 };
    UINT ਗਿਣਤੀ_2 = 0;

    ਅਚਲ Uint32 old_mouse_flags = ਆਖਰੀ_flags & (ENABLE_RAW_MOUSE_ਨਿਵੇਸ਼ | RAW_MOUSE_FLAG_NOLEGACY);
    ਅਚਲ Uint32 new_mouse_flags = new_flags & (ENABLE_RAW_MOUSE_ਨਿਵੇਸ਼ | RAW_MOUSE_FLAG_NOLEGACY);

    ਜੇ (old_mouse_flags != new_mouse_flags) {
        devices[ਗਿਣਤੀ_2].us_Usage_ਪੰਨਾ = USB_USAGEPAGE_GENERIC_DESKTOP;
        devices[ਗਿਣਤੀ_2].usUsage = USB_USAGE_GENERIC_MOUSE;

        ਜੇ (new_flags & ENABLE_RAW_MOUSE_ਨਿਵੇਸ਼) {
            devices[ਗਿਣਤੀ_2].dwFlags = 0;
            devices[ਗਿਣਤੀ_2].hwnd_ਨਿਸ਼ਾਨਾ = ਖਿੜਕੀ;
            ਜੇ (new_mouse_flags & RAW_MOUSE_FLAG_NOLEGACY) {
                devices[ਗਿਣਤੀ_2].dwFlags |= RIDEV_NOLEGACY;
            }
        } ਨਹੀਂਤਾਂ {
            devices[ਗਿਣਤੀ_2].dwFlags = RIDEV_REMOVE;
            devices[ਗਿਣਤੀ_2].hwnd_ਨਿਸ਼ਾਨਾ = ਨਿਰਾ;
        }

        ++ਗਿਣਤੀ_2;
    }

    ਅਚਲ Uint32 old_kb_flags = ਆਖਰੀ_flags & (ENABLE_RAW_KEYBOARD_ਨਿਵੇਸ਼ | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);
    ਅਚਲ Uint32 new_kb_flags = new_flags & (ENABLE_RAW_KEYBOARD_ਨਿਵੇਸ਼ | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);

    ਜੇ (old_kb_flags != new_kb_flags) {
        devices[ਗਿਣਤੀ_2].us_Usage_ਪੰਨਾ = USB_USAGEPAGE_GENERIC_DESKTOP;
        devices[ਗਿਣਤੀ_2].usUsage = USB_USAGE_GENERIC_KEYBOARD;

        ਜੇ (new_kb_flags & ENABLE_RAW_KEYBOARD_ਨਿਵੇਸ਼) {
            devices[ਗਿਣਤੀ_2].dwFlags = 0;
            devices[ਗਿਣਤੀ_2].hwnd_ਨਿਸ਼ਾਨਾ = ਖਿੜਕੀ;
            ਜੇ (new_kb_flags & RAW_KEYBOARD_FLAG_NOHOTKEYS) {
                devices[ਗਿਣਤੀ_2].dwFlags |= RIDEV_NOHOTKEYS;
            }
            ਜੇ (new_kb_flags & RAW_KEYBOARD_FLAG_INPUTSINK) {
                devices[ਗਿਣਤੀ_2].dwFlags |= RIDEV_INPUTSINK;
            }
        } ਨਹੀਂਤਾਂ {
            devices[ਗਿਣਤੀ_2].dwFlags = RIDEV_REMOVE;
            devices[ਗਿਣਤੀ_2].hwnd_ਨਿਸ਼ਾਨਾ = ਨਿਰਾ;
        }

        ++ਗਿਣਤੀ_2;
    }

    ਜੇ (ਰਜਿਸਟਰ_Raw_ਨਿਵੇਸ਼_Devices(devices, ਗਿਣਤੀ_2, ਆਕਾਰ(devices[0]))) {
        ਵਾਪਸ true;
    }
    ਵਾਪਸ false;
}

ਸਥਿਰ DWORD WINAPI WIN_Raw_ਨਿਵੇਸ਼_Thread(LPVOID param)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    Uint32 ਆਖਰੀ_flags = 0;
    HWND ਖਿੜਕੀ;

    SDL_SYS_ਤਿਆਰੀ_Thread("SDLRawInput");

    ਖਿੜਕੀ = Create_ਖਿੜਕੀ_Ex(0, ਪਾਠ_2("Message"), ਨਿਰਾ, 0, 0, 0, 0, 0, HWND_ਸੁਨੇਹਾ, ਨਿਰਾ, ਨਿਰਾ, ਨਿਰਾ);
    ਜੇ (!ਖਿੜਕੀ) {
        ਵਾਪਸ 0;
    }

    // This doesn't *really* need to be atomic, because the parent is waiting for us
    ਆਖਰੀ_flags = SDL_GetAtomicU32(&thread_ਅੰਕੜੇ.flags);
    ਜੇ (!Update_Raw_ਨਿਵੇਸ਼_Device_Flags(ਖਿੜਕੀ, 0, ਆਖਰੀ_flags)) {
        Destroy_ਖਿੜਕੀ(ਖਿੜਕੀ);
        ਵਾਪਸ 0;
    }

    // Make sure we get events as soon as possible
    ਸੈੱਟ_Thread_ਤਰਜੀਹ(GetCurrentThread(), THREAD_ਤਰਜੀਹ_ਸਮਾਂ_CRITICAL);

    // Tell the parent we're ready to go!
    ਸੈੱਟ_Event(thread_ਅੰਕੜੇ.ready_event);

    Raw_ਨਿਵੇਸ਼_Iterate_ਨਤੀਜਾ iter_ਨਤੀਜਾ;

    Uint64 idle_begin = SDL_GetTicksNS();
    ਜਦੋਂ ((iter_ਨਤੀਜਾ = Iterate_Raw_ਨਿਵੇਸ਼_Thread()) != RINP_QUIT) {
        ਚੋਣ (iter_ਨਤੀਜਾ) {
        ਹਾਲਤ RINP_QUIT: // Unreachable
            ਰੋਕੋ;
        ਹਾਲਤ RINP_UPDATE:
        {
            ਅਚਲ Uint32 new_flags = SDL_GetAtomicU32(&thread_ਅੰਕੜੇ.flags);
            ਜੇ (!Update_Raw_ਨਿਵੇਸ਼_Device_Flags(ਖਿੜਕੀ, ਆਖਰੀ_flags, new_flags)) {
                // Revert the shared flags so the main thread can detect the failure
                SDL_ਸੈੱਟ_Atomic_U32(&thread_ਅੰਕੜੇ.flags, ਆਖਰੀ_flags);
            } ਨਹੀਂਤਾਂ {
                ਆਖਰੀ_flags = new_flags;
            }
        } ਰੋਕੋ;
        ਹਾਲਤ RINP_CONTINUE:
        {
            Uint64 idle_ਸਿਰਾ = SDL_GetTicksNS();
            Uint64 idle_ਸਮਾਂ = idle_ਸਿਰਾ - idle_begin;
            Uint64 usb_8khz_interval = SDL_US_ਮੰਜ਼ਿਲ_NS(125);
            Uint64 poll_ਸ਼ੁਰੂ = idle_ਸਮਾਂ < usb_8khz_interval ? _this->ਅੰਦਰੂਨੀ->ਆਖਰੀ_rawinput_poll : idle_ਸਿਰਾ;

            WIN_Poll_Raw_ਨਿਵੇਸ਼(_this, poll_ਸ਼ੁਰੂ);

            // Reset idle_begin for the next go-around
            idle_begin = SDL_GetTicksNS();
        } ਰੋਕੋ;
        }
    }

    ਜੇ (_this->ਅੰਦਰੂਨੀ->raw_ਨਿਵੇਸ਼_fake_pen_id) {
        SDL_RemovePenDevice(0, SDL_GetKeyboardFocus(), _this->ਅੰਦਰੂਨੀ->raw_ਨਿਵੇਸ਼_fake_pen_id);
        _this->ਅੰਦਰੂਨੀ->raw_ਨਿਵੇਸ਼_fake_pen_id = 0;
    }

    // Reset this here, since if we're exiting due to failure, WIN_UpdateRawInputEnabled would see a stale value.
    SDL_ਸੈੱਟ_Atomic_U32(&thread_ਅੰਕੜੇ.flags, 0);

    Update_Raw_ਨਿਵੇਸ਼_Device_Flags(ਨਿਰਾ, ਆਖਰੀ_flags, 0);

    Destroy_ਖਿੜਕੀ(ਖਿੜਕੀ);

    ਵਾਪਸ 0;
}

ਸਥਿਰ ਖਾਲੀ Cleanup_Raw_ਨਿਵੇਸ਼_Thread_ਅੰਕੜੇ(ਖਾਲੀ)
{
    ਜੇ (thread_ਅੰਕੜੇ.thread) {
        thread_ਅੰਕੜੇ.ਪੂਰਾ = true;
        ਸੈੱਟ_Event(thread_ਅੰਕੜੇ.signal_event);
        WaitForSingleObject(thread_ਅੰਕੜੇ.thread, 3000);
        CloseHandle(thread_ਅੰਕੜੇ.thread);
    }

    ਜੇ (thread_ਅੰਕੜੇ.ready_event) {
        CloseHandle(thread_ਅੰਕੜੇ.ready_event);
    }

    ਜੇ (thread_ਅੰਕੜੇ.signal_event) {
        CloseHandle(thread_ਅੰਕੜੇ.signal_event);
    }

    thread_ਅੰਕੜੇ = (Raw_ਨਿਵੇਸ਼_Thread_ਅੰਕੜੇ){ 0 };
}

// Computes the desired raw input flags from SDL_VideoData and ensures the
// raw input thread's device registrations match.
// Creates the thread on first use, only WIN_QuitRawInput actually shuts it down.
ਸਥਿਰ bool WIN_Update_Raw_ਨਿਵੇਸ਼_Enabled(SDL_VideoDevice *_this)
{
    bool ਨਤੀਜਾ = false;
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    Uint32 desired_flags = 0;

    ਜੇ (!ਅੰਕੜੇ->gameinput_context) {
        ਜੇ (ਅੰਕੜੇ->raw_mouse_enabled) {
            desired_flags |= ENABLE_RAW_MOUSE_ਨਿਵੇਸ਼;
            ਜੇ (ਅੰਕੜੇ->raw_mouse_flag_nolegacy) {
                desired_flags |= RAW_MOUSE_FLAG_NOLEGACY;
            }
        }
        ਜੇ (ਅੰਕੜੇ->raw_keyboard_enabled) {
            desired_flags |= ENABLE_RAW_KEYBOARD_ਨਿਵੇਸ਼;
            ਜੇ (ਅੰਕੜੇ->raw_keyboard_flag_nohotkeys) {
                desired_flags |= RAW_KEYBOARD_FLAG_NOHOTKEYS;
            }
            ਜੇ (ਅੰਕੜੇ->raw_keyboard_flag_inputsink) {
                desired_flags |= RAW_KEYBOARD_FLAG_INPUTSINK;
            }
        }
    }

    ਜੇ (desired_flags == SDL_GetAtomicU32(&thread_ਅੰਕੜੇ.flags)) {
        ਨਤੀਜਾ = true;
        ਜਾਓ ਪੂਰਾ;
    }

    // If the thread exited unexpectedly (e.g. MsgWaitForMultipleObjects failed),
    // the handle is stale. Clean it up so the creation path below can recover.
    ਜੇ (thread_ਅੰਕੜੇ.thread && WaitForSingleObject(thread_ਅੰਕੜੇ.thread, 0) != WAIT_TIMEOUT) {
        Cleanup_Raw_ਨਿਵੇਸ਼_Thread_ਅੰਕੜੇ();
    }

    // The thread will read from this to update its flags
    SDL_ਸੈੱਟ_Atomic_U32(&thread_ਅੰਕੜੇ.flags, desired_flags);

    ਜੇ (thread_ਅੰਕੜੇ.thread) {
        // Thread is already running. Fire (the event) and forget, it'll read the atomic flags on wakeup.

        // If RegisterRawInputDevices fails, the thread reverts the atomic and the next call
        // to this function will see the mismatch and retry.
        SDL_assert(thread_ਅੰਕੜੇ.signal_event);
        ਸੈੱਟ_Event(thread_ਅੰਕੜੇ.signal_event);
        ਨਤੀਜਾ = true;
    } ਨਹੀਂਤਾਂ ਜੇ (desired_flags) {
        HANDLE wait_handles[2];

        // Thread isn't running, spin it up
        thread_ਅੰਕੜੇ.ready_event = CreateEvent(ਨਿਰਾ, FALSE, FALSE, ਨਿਰਾ);
        ਜੇ (!thread_ਅੰਕੜੇ.ready_event) {
            WIN_ਸੈੱਟ_Error("CreateEvent");
            ਜਾਓ ਪੂਰਾ;
        }

        thread_ਅੰਕੜੇ.ਪੂਰਾ = false;
        thread_ਅੰਕੜੇ.signal_event = CreateEvent(ਨਿਰਾ, FALSE, FALSE, ਨਿਰਾ);
        ਜੇ (!thread_ਅੰਕੜੇ.signal_event) {
            WIN_ਸੈੱਟ_Error("CreateEvent");
            ਜਾਓ ਪੂਰਾ;
        }

        thread_ਅੰਕੜੇ.thread = CreateThread(ਨਿਰਾ, 0, WIN_Raw_ਨਿਵੇਸ਼_Thread, ਨਿਰਾ, 0, ਨਿਰਾ);
        ਜੇ (!thread_ਅੰਕੜੇ.thread) {
            WIN_ਸੈੱਟ_Error("CreateThread");
            ਜਾਓ ਪੂਰਾ;
        }

        // Wait for the thread to complete initial setup or exit
        wait_handles[0] = thread_ਅੰਕੜੇ.ready_event;
        wait_handles[1] = thread_ਅੰਕੜੇ.thread;
        ਜੇ (Wait_For_ਗੁਣਜ_Objects(2, wait_handles, FALSE, INFINITE) != WAIT_OBJECT_0) {
            SDL_ਸੈੱਟ_Error("Couldn't set up raw input handling");
            ਜਾਓ ਪੂਰਾ;
        }
        ਨਤੀਜਾ = true;
    } ਨਹੀਂਤਾਂ {
        // Thread isn't running and we tried to disable raw input, nothing to do
        ਨਤੀਜਾ = true;
    }
ਪੂਰਾ:
    ਜੇ (!ਨਤੀਜਾ) {
        Cleanup_Raw_ਨਿਵੇਸ਼_Thread_ਅੰਕੜੇ();
    }
    ਵਾਪਸ ਨਤੀਜਾ;
}

bool WIN_ਸੈੱਟ_Raw_Mouse_Enabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    ਅੰਕੜੇ->raw_mouse_enabled = enabled;
    ਜੇ (ਅੰਕੜੇ->gameinput_context) {
        ਜੇ (!WIN_Update_Game_ਨਿਵੇਸ਼_Enabled(_this)) {
            ਅੰਕੜੇ->raw_mouse_enabled = !enabled;
            ਵਾਪਸ false;
        }
    } ਨਹੀਂਤਾਂ {
        ਜੇ (!WIN_Update_Raw_ਨਿਵੇਸ਼_Enabled(_this)) {
            ਅੰਕੜੇ->raw_mouse_enabled = !enabled;
            ਵਾਪਸ false;
        }
    }
    ਵਾਪਸ true;
}

bool WIN_ਸੈੱਟ_Raw_Mouse_Flag_No_Legacy(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;

    ਅੰਕੜੇ->raw_mouse_flag_nolegacy = enabled;

    ਵਾਪਸ WIN_Update_Raw_ਨਿਵੇਸ਼_Enabled(_this);
}

bool WIN_ਸੈੱਟ_Raw_Keyboard_Enabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;
    ਅੰਕੜੇ->raw_keyboard_enabled = enabled;
    ਜੇ (ਅੰਕੜੇ->gameinput_context) {
        ਜੇ (!WIN_Update_Game_ਨਿਵੇਸ਼_Enabled(_this)) {
            ਅੰਕੜੇ->raw_keyboard_enabled = !enabled;
            ਵਾਪਸ false;
        }
    } ਨਹੀਂਤਾਂ {
        ਜੇ (!WIN_Update_Raw_ਨਿਵੇਸ਼_Enabled(_this)) {
            ਅੰਕੜੇ->raw_keyboard_enabled = !enabled;
            ਵਾਪਸ false;
        }
    }
    ਵਾਪਸ true;
}

bool WIN_ਸੈੱਟ_Raw_Keyboard_Flag_No_Hotkeys(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;

    ਅੰਕੜੇ->raw_keyboard_flag_nohotkeys = enabled;

    ਵਾਪਸ WIN_Update_Raw_ਨਿਵੇਸ਼_Enabled(_this);
}

bool WIN_ਸੈੱਟ_Raw_Keyboard_Flag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ = _this->ਅੰਦਰੂਨੀ;

    ਅੰਕੜੇ->raw_keyboard_flag_inputsink = enabled;

    ਵਾਪਸ WIN_Update_Raw_ਨਿਵੇਸ਼_Enabled(_this);
}

ਖਾਲੀ WIN_Quit_Raw_ਨਿਵੇਸ਼(SDL_VideoDevice *_this)
{
    Cleanup_Raw_ਨਿਵੇਸ਼_Thread_ਅੰਕੜੇ();
}

#ਨਹੀਂਤਾਂ

bool WIN_ਸੈੱਟ_Raw_Mouse_Enabled(SDL_VideoDevice *_this, bool enabled)
{
    ਵਾਪਸ SDL_Unsupported();
}

bool WIN_ਸੈੱਟ_Raw_Mouse_Flag_No_Legacy(SDL_VideoDevice *_this, bool enabled)
{
    ਵਾਪਸ SDL_Unsupported();
}

bool WIN_ਸੈੱਟ_Raw_Keyboard_Enabled(SDL_VideoDevice *_this, bool enabled)
{
    ਵਾਪਸ SDL_Unsupported();
}

bool WIN_ਸੈੱਟ_Raw_Keyboard_Flag_No_Hotkeys(SDL_VideoDevice *_this, bool enabled)
{
    ਵਾਪਸ SDL_Unsupported();
}

bool WIN_ਸੈੱਟ_Raw_Keyboard_Flag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    ਵਾਪਸ SDL_Unsupported();
}

ਖਾਲੀ WIN_Quit_Raw_ਨਿਵੇਸ਼(SDL_VideoDevice *_this)
{
}

#ਜੇ_ਅੰਤ // !SDL_PLATFORM_XBOXONE && !SDL_PLATFORM_XBOXSERIES

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_WINDOWS

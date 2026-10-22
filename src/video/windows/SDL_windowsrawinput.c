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

#إذا defined(SDL_VIDEO_DRIVER_WINDOWS)

#ضمن "SDL_windowsvideo.h"

#إذا !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#ضمن "SDL_windowsevents.h"

#ضمن "../../joystick/usb_ids.h"
#ضمن "../../events/SDL_events_c.h"
#ضمن "../../thread/SDL_systhread.h"

#تعریف_کرو ENABLE_RAW_MOUSE_داخلہ      0x01
#تعریف_کرو RAW_MOUSE_FLAG_NOLEGACY     0x02
#تعریف_کرو ENABLE_RAW_KEYBOARD_داخلہ   0x10
#تعریف_کرو RAW_KEYBOARD_FLAG_NOHOTKEYS 0x20
#تعریف_کرو RAW_KEYBOARD_FLAG_INPUTSINK 0x40

تعريفنوع بنية
{
    bool پورا;
    SDL_AtomicU32 flags; // Thread sets this to the actually-set flags if updating state failed
    HANDLE ready_event;
    HANDLE signal_event;
    HANDLE thread;
} Raw_داخلہ_Thread_انکڑے;

ساكن Raw_داخلہ_Thread_انکڑے thread_انکڑے = { 0 };

تعريفنوع تعداد
{
    RINP_QUIT,
    RINP_UPDATE,
    RINP_CONTINUE
} Raw_داخلہ_Iterate_نتیجہ;

ساكن Raw_داخلہ_Iterate_نتیجہ Iterate_Raw_داخلہ_Thread(فراغ)
{
    // The high-order word of GetQueueStatus() will let us know if there's immediate raw input to be processed.
    // A (necessary!) side effect is that it also marks the message queue bits as stale,
    // so MsgWaitForMultipleObjects will block.

    // Any pending flag update won't be processed until the queue drains, but this is
    // at most one poll cycle since GetQueueStatus clears the wake bits.
    إذا (HIWORD(Get_قطار_حالت(QS_RAWINPUT)) & QS_RAWINPUT) {
        أرجع thread_انکڑے.پورا ? RINP_QUIT : RINP_CONTINUE;
    }

    ساكن ثابت DWORD WAIT_SIGNAL = WAIT_OBJECT_0;
    ساكن ثابت DWORD WAIT_داخلہ = WAIT_OBJECT_0 + 1;

    // There wasn't anything, so we'll wait until new data (or signal_event) wakes us up.
    DWORD wait_حالت = پیغام_Wait_For_مضرب_Objects(1, &thread_انکڑے.signal_event, FALSE, INFINITE, QS_RAWINPUT);
    إذا (wait_حالت == WAIT_SIGNAL) {
        // signal_event can only be set if we need to update or quit.
        أرجع thread_انکڑے.پورا ? RINP_QUIT : RINP_UPDATE;
    } وإلا إذا (wait_حالت == WAIT_داخلہ) {
        أرجع RINP_CONTINUE;
    } وإلا {
        SDL_LogWarn(SDL_LOG_CATEGORY_داخلہ, "Raw input thread exiting, unexpected wait result: %" SDL_PRIuULONG, wait_حالت);
        أرجع RINP_QUIT;
    }
}

ساكن bool Update_Raw_داخلہ_Device_Flags(HWND کھڑکی, Uint32 آخری_flags, Uint32 new_flags)
{
    // We had nothing enabled, and we're trying to stop everything. Nothing to do.
    إذا (آخری_flags == new_flags) {
        أرجع true;
    }

    RAWINPUTDEVICE devices[2] = { 0 };
    UINT گنتی = 0;

    ثابت Uint32 old_mouse_flags = آخری_flags & (ENABLE_RAW_MOUSE_داخلہ | RAW_MOUSE_FLAG_NOLEGACY);
    ثابت Uint32 new_mouse_flags = new_flags & (ENABLE_RAW_MOUSE_داخلہ | RAW_MOUSE_FLAG_NOLEGACY);

    إذا (old_mouse_flags != new_mouse_flags) {
        devices[گنتی].us_Usage_ورقہ = USB_USAGEPAGE_GENERIC_DESKTOP;
        devices[گنتی].usUsage = USB_USAGE_GENERIC_MOUSE;

        إذا (new_flags & ENABLE_RAW_MOUSE_داخلہ) {
            devices[گنتی].dwFlags = 0;
            devices[گنتی].hwnd_نشانہ = کھڑکی;
            إذا (new_mouse_flags & RAW_MOUSE_FLAG_NOLEGACY) {
                devices[گنتی].dwFlags |= RIDEV_NOLEGACY;
            }
        } وإلا {
            devices[گنتی].dwFlags = RIDEV_REMOVE;
            devices[گنتی].hwnd_نشانہ = عدم;
        }

        ++گنتی;
    }

    ثابت Uint32 old_kb_flags = آخری_flags & (ENABLE_RAW_KEYBOARD_داخلہ | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);
    ثابت Uint32 new_kb_flags = new_flags & (ENABLE_RAW_KEYBOARD_داخلہ | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);

    إذا (old_kb_flags != new_kb_flags) {
        devices[گنتی].us_Usage_ورقہ = USB_USAGEPAGE_GENERIC_DESKTOP;
        devices[گنتی].usUsage = USB_USAGE_GENERIC_KEYBOARD;

        إذا (new_kb_flags & ENABLE_RAW_KEYBOARD_داخلہ) {
            devices[گنتی].dwFlags = 0;
            devices[گنتی].hwnd_نشانہ = کھڑکی;
            إذا (new_kb_flags & RAW_KEYBOARD_FLAG_NOHOTKEYS) {
                devices[گنتی].dwFlags |= RIDEV_NOHOTKEYS;
            }
            إذا (new_kb_flags & RAW_KEYBOARD_FLAG_INPUTSINK) {
                devices[گنتی].dwFlags |= RIDEV_INPUTSINK;
            }
        } وإلا {
            devices[گنتی].dwFlags = RIDEV_REMOVE;
            devices[گنتی].hwnd_نشانہ = عدم;
        }

        ++گنتی;
    }

    إذا (رجسٹر_Raw_داخلہ_Devices(devices, گنتی, حجم(devices[0]))) {
        أرجع true;
    }
    أرجع false;
}

ساكن DWORD WINAPI WIN_Raw_داخلہ_Thread(LPVOID param)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    Uint32 آخری_flags = 0;
    HWND کھڑکی;

    SDL_SYS_تیاری_Thread("SDLRawInput");

    کھڑکی = Create_کھڑکی_Ex(0, متن_2("Message"), عدم, 0, 0, 0, 0, 0, HWND_سنیہا, عدم, عدم, عدم);
    إذا (!کھڑکی) {
        أرجع 0;
    }

    // This doesn't *really* need to be atomic, because the parent is waiting for us
    آخری_flags = SDL_GetAtomicU32(&thread_انکڑے.flags);
    إذا (!Update_Raw_داخلہ_Device_Flags(کھڑکی, 0, آخری_flags)) {
        Destroy_کھڑکی(کھڑکی);
        أرجع 0;
    }

    // Make sure we get events as soon as possible
    سیٹ_Thread_ترجیح(GetCurrentThread(), THREAD_ترجیح_ویلا_CRITICAL);

    // Tell the parent we're ready to go!
    سیٹ_Event(thread_انکڑے.ready_event);

    Raw_داخلہ_Iterate_نتیجہ iter_نتیجہ;

    Uint64 idle_begin = SDL_GetTicksNS();
    طالما ((iter_نتیجہ = Iterate_Raw_داخلہ_Thread()) != RINP_QUIT) {
        بدل (iter_نتیجہ) {
        حالة RINP_QUIT: // Unreachable
            اكسر;
        حالة RINP_UPDATE:
        {
            ثابت Uint32 new_flags = SDL_GetAtomicU32(&thread_انکڑے.flags);
            إذا (!Update_Raw_داخلہ_Device_Flags(کھڑکی, آخری_flags, new_flags)) {
                // Revert the shared flags so the main thread can detect the failure
                SDL_سیٹ_Atomic_U32(&thread_انکڑے.flags, آخری_flags);
            } وإلا {
                آخری_flags = new_flags;
            }
        } اكسر;
        حالة RINP_CONTINUE:
        {
            Uint64 idle_سرا = SDL_GetTicksNS();
            Uint64 idle_ویلا = idle_سرا - idle_begin;
            Uint64 usb_8khz_interval = SDL_US_منزل_NS(125);
            Uint64 poll_شروع = idle_ویلا < usb_8khz_interval ? _this->اندرونی->آخری_rawinput_poll : idle_سرا;

            WIN_Poll_Raw_داخلہ(_this, poll_شروع);

            // Reset idle_begin for the next go-around
            idle_begin = SDL_GetTicksNS();
        } اكسر;
        }
    }

    إذا (_this->اندرونی->raw_داخلہ_fake_pen_id) {
        SDL_RemovePenDevice(0, SDL_GetKeyboardFocus(), _this->اندرونی->raw_داخلہ_fake_pen_id);
        _this->اندرونی->raw_داخلہ_fake_pen_id = 0;
    }

    // Reset this here, since if we're exiting due to failure, WIN_UpdateRawInputEnabled would see a stale value.
    SDL_سیٹ_Atomic_U32(&thread_انکڑے.flags, 0);

    Update_Raw_داخلہ_Device_Flags(عدم, آخری_flags, 0);

    Destroy_کھڑکی(کھڑکی);

    أرجع 0;
}

ساكن فراغ Cleanup_Raw_داخلہ_Thread_انکڑے(فراغ)
{
    إذا (thread_انکڑے.thread) {
        thread_انکڑے.پورا = true;
        سیٹ_Event(thread_انکڑے.signal_event);
        WaitForSingleObject(thread_انکڑے.thread, 3000);
        CloseHandle(thread_انکڑے.thread);
    }

    إذا (thread_انکڑے.ready_event) {
        CloseHandle(thread_انکڑے.ready_event);
    }

    إذا (thread_انکڑے.signal_event) {
        CloseHandle(thread_انکڑے.signal_event);
    }

    thread_انکڑے = (Raw_داخلہ_Thread_انکڑے){ 0 };
}

// Computes the desired raw input flags from SDL_VideoData and ensures the
// raw input thread's device registrations match.
// Creates the thread on first use, only WIN_QuitRawInput actually shuts it down.
ساكن bool WIN_Update_Raw_داخلہ_Enabled(SDL_VideoDevice *_this)
{
    bool نتیجہ = false;
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;
    Uint32 desired_flags = 0;

    إذا (!انکڑے->gameinput_context) {
        إذا (انکڑے->raw_mouse_enabled) {
            desired_flags |= ENABLE_RAW_MOUSE_داخلہ;
            إذا (انکڑے->raw_mouse_flag_nolegacy) {
                desired_flags |= RAW_MOUSE_FLAG_NOLEGACY;
            }
        }
        إذا (انکڑے->raw_keyboard_enabled) {
            desired_flags |= ENABLE_RAW_KEYBOARD_داخلہ;
            إذا (انکڑے->raw_keyboard_flag_nohotkeys) {
                desired_flags |= RAW_KEYBOARD_FLAG_NOHOTKEYS;
            }
            إذا (انکڑے->raw_keyboard_flag_inputsink) {
                desired_flags |= RAW_KEYBOARD_FLAG_INPUTSINK;
            }
        }
    }

    إذا (desired_flags == SDL_GetAtomicU32(&thread_انکڑے.flags)) {
        نتیجہ = true;
        اذهب پورا;
    }

    // If the thread exited unexpectedly (e.g. MsgWaitForMultipleObjects failed),
    // the handle is stale. Clean it up so the creation path below can recover.
    إذا (thread_انکڑے.thread && WaitForSingleObject(thread_انکڑے.thread, 0) != WAIT_TIMEOUT) {
        Cleanup_Raw_داخلہ_Thread_انکڑے();
    }

    // The thread will read from this to update its flags
    SDL_سیٹ_Atomic_U32(&thread_انکڑے.flags, desired_flags);

    إذا (thread_انکڑے.thread) {
        // Thread is already running. Fire (the event) and forget, it'll read the atomic flags on wakeup.

        // If RegisterRawInputDevices fails, the thread reverts the atomic and the next call
        // to this function will see the mismatch and retry.
        SDL_assert(thread_انکڑے.signal_event);
        سیٹ_Event(thread_انکڑے.signal_event);
        نتیجہ = true;
    } وإلا إذا (desired_flags) {
        HANDLE wait_handles[2];

        // Thread isn't running, spin it up
        thread_انکڑے.ready_event = CreateEvent(عدم, FALSE, FALSE, عدم);
        إذا (!thread_انکڑے.ready_event) {
            WIN_سیٹ_Error("CreateEvent");
            اذهب پورا;
        }

        thread_انکڑے.پورا = false;
        thread_انکڑے.signal_event = CreateEvent(عدم, FALSE, FALSE, عدم);
        إذا (!thread_انکڑے.signal_event) {
            WIN_سیٹ_Error("CreateEvent");
            اذهب پورا;
        }

        thread_انکڑے.thread = CreateThread(عدم, 0, WIN_Raw_داخلہ_Thread, عدم, 0, عدم);
        إذا (!thread_انکڑے.thread) {
            WIN_سیٹ_Error("CreateThread");
            اذهب پورا;
        }

        // Wait for the thread to complete initial setup or exit
        wait_handles[0] = thread_انکڑے.ready_event;
        wait_handles[1] = thread_انکڑے.thread;
        إذا (Wait_For_مضرب_Objects(2, wait_handles, FALSE, INFINITE) != WAIT_OBJECT_0) {
            SDL_سیٹ_Error("Couldn't set up raw input handling");
            اذهب پورا;
        }
        نتیجہ = true;
    } وإلا {
        // Thread isn't running and we tried to disable raw input, nothing to do
        نتیجہ = true;
    }
پورا:
    إذا (!نتیجہ) {
        Cleanup_Raw_داخلہ_Thread_انکڑے();
    }
    أرجع نتیجہ;
}

bool WIN_سیٹ_Raw_Mouse_Enabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;
    انکڑے->raw_mouse_enabled = enabled;
    إذا (انکڑے->gameinput_context) {
        إذا (!WIN_Update_Game_داخلہ_Enabled(_this)) {
            انکڑے->raw_mouse_enabled = !enabled;
            أرجع false;
        }
    } وإلا {
        إذا (!WIN_Update_Raw_داخلہ_Enabled(_this)) {
            انکڑے->raw_mouse_enabled = !enabled;
            أرجع false;
        }
    }
    أرجع true;
}

bool WIN_سیٹ_Raw_Mouse_Flag_No_Legacy(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;

    انکڑے->raw_mouse_flag_nolegacy = enabled;

    أرجع WIN_Update_Raw_داخلہ_Enabled(_this);
}

bool WIN_سیٹ_Raw_Keyboard_Enabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;
    انکڑے->raw_keyboard_enabled = enabled;
    إذا (انکڑے->gameinput_context) {
        إذا (!WIN_Update_Game_داخلہ_Enabled(_this)) {
            انکڑے->raw_keyboard_enabled = !enabled;
            أرجع false;
        }
    } وإلا {
        إذا (!WIN_Update_Raw_داخلہ_Enabled(_this)) {
            انکڑے->raw_keyboard_enabled = !enabled;
            أرجع false;
        }
    }
    أرجع true;
}

bool WIN_سیٹ_Raw_Keyboard_Flag_No_Hotkeys(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;

    انکڑے->raw_keyboard_flag_nohotkeys = enabled;

    أرجع WIN_Update_Raw_داخلہ_Enabled(_this);
}

bool WIN_سیٹ_Raw_Keyboard_Flag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_انکڑے *انکڑے = _this->اندرونی;

    انکڑے->raw_keyboard_flag_inputsink = enabled;

    أرجع WIN_Update_Raw_داخلہ_Enabled(_this);
}

فراغ WIN_Quit_Raw_داخلہ(SDL_VideoDevice *_this)
{
    Cleanup_Raw_داخلہ_Thread_انکڑے();
}

#وإلا

bool WIN_سیٹ_Raw_Mouse_Enabled(SDL_VideoDevice *_this, bool enabled)
{
    أرجع SDL_Unsupported();
}

bool WIN_سیٹ_Raw_Mouse_Flag_No_Legacy(SDL_VideoDevice *_this, bool enabled)
{
    أرجع SDL_Unsupported();
}

bool WIN_سیٹ_Raw_Keyboard_Enabled(SDL_VideoDevice *_this, bool enabled)
{
    أرجع SDL_Unsupported();
}

bool WIN_سیٹ_Raw_Keyboard_Flag_No_Hotkeys(SDL_VideoDevice *_this, bool enabled)
{
    أرجع SDL_Unsupported();
}

bool WIN_سیٹ_Raw_Keyboard_Flag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    أرجع SDL_Unsupported();
}

فراغ WIN_Quit_Raw_داخلہ(SDL_VideoDevice *_this)
{
}

#جے_انت // !SDL_PLATFORM_XBOXONE && !SDL_PLATFORM_XBOXSERIES

#جے_انت // SDL_VIDEO_DRIVER_WINDOWS

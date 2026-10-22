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

#وصف_ڪريو ENABLE_RAW_MOUSE_داخلا      0x01
#وصف_ڪريو RAW_MOUSE_FLAG_NOLEGACY     0x02
#وصف_ڪريو ENABLE_RAW_KEYBOARD_داخلا   0x10
#وصف_ڪريو RAW_KEYBOARD_FLAG_NOHOTKEYS 0x20
#وصف_ڪريو RAW_KEYBOARD_FLAG_INPUTSINK 0x40

تعريفنوع بنية
{
    bool پورو;
    SDL_AtomicU32 flags; // Thread sets this to the actually-set flags if updating state failed
    HANDLE ready_event;
    HANDLE signal_event;
    HANDLE thread;
} Raw_داخلا_Thread_معلومات;

ساكن Raw_داخلا_Thread_معلومات thread_معلومات = { 0 };

تعريفنوع تعداد
{
    RINP_QUIT,
    RINP_UPDATE,
    RINP_CONTINUE
} Raw_داخلا_Iterate_نتيجو;

ساكن Raw_داخلا_Iterate_نتيجو Iterate_Raw_داخلا_Thread(فراغ)
{
    // The high-order word of GetQueueStatus() will let us know if there's immediate raw input to be processed.
    // A (necessary!) side effect is that it also marks the message queue bits as stale,
    // so MsgWaitForMultipleObjects will block.

    // Any pending flag update won't be processed until the queue drains, but this is
    // at most one poll cycle since GetQueueStatus clears the wake bits.
    إذا (HIWORD(Get_قطار_حالت(QS_RAWINPUT)) & QS_RAWINPUT) {
        أرجع thread_معلومات.پورو ? RINP_QUIT : RINP_CONTINUE;
    }

    ساكن ثابت DWORD WAIT_SIGNAL = WAIT_OBJECT_0;
    ساكن ثابت DWORD WAIT_داخلا = WAIT_OBJECT_0 + 1;

    // There wasn't anything, so we'll wait until new data (or signal_event) wakes us up.
    DWORD wait_حالت = نياپو_Wait_For_گڻو_Objects(1, &thread_معلومات.signal_event, FALSE, INFINITE, QS_RAWINPUT);
    إذا (wait_حالت == WAIT_SIGNAL) {
        // signal_event can only be set if we need to update or quit.
        أرجع thread_معلومات.پورو ? RINP_QUIT : RINP_UPDATE;
    } وإلا إذا (wait_حالت == WAIT_داخلا) {
        أرجع RINP_CONTINUE;
    } وإلا {
        SDL_LogWarn(SDL_LOG_CATEGORY_داخلا, "Raw input thread exiting, unexpected wait result: %" SDL_PRIuULONG, wait_حالت);
        أرجع RINP_QUIT;
    }
}

ساكن bool Update_Raw_داخلا_Device_Flags(HWND دري, Uint32 آخري_flags, Uint32 new_flags)
{
    // We had nothing enabled, and we're trying to stop everything. Nothing to do.
    إذا (آخري_flags == new_flags) {
        أرجع true;
    }

    RAWINPUTDEVICE devices[2] = { 0 };
    UINT ڳڻپ = 0;

    ثابت Uint32 old_mouse_flags = آخري_flags & (ENABLE_RAW_MOUSE_داخلا | RAW_MOUSE_FLAG_NOLEGACY);
    ثابت Uint32 new_mouse_flags = new_flags & (ENABLE_RAW_MOUSE_داخلا | RAW_MOUSE_FLAG_NOLEGACY);

    إذا (old_mouse_flags != new_mouse_flags) {
        devices[ڳڻپ].us_Usage_صفحو = USB_USAGEPAGE_GENERIC_DESKTOP;
        devices[ڳڻپ].usUsage = USB_USAGE_GENERIC_MOUSE;

        إذا (new_flags & ENABLE_RAW_MOUSE_داخلا) {
            devices[ڳڻپ].dwFlags = 0;
            devices[ڳڻپ].hwnd_هدف = دري;
            إذا (new_mouse_flags & RAW_MOUSE_FLAG_NOLEGACY) {
                devices[ڳڻپ].dwFlags |= RIDEV_NOLEGACY;
            }
        } وإلا {
            devices[ڳڻپ].dwFlags = RIDEV_REMOVE;
            devices[ڳڻپ].hwnd_هدف = عدم;
        }

        ++ڳڻپ;
    }

    ثابت Uint32 old_kb_flags = آخري_flags & (ENABLE_RAW_KEYBOARD_داخلا | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);
    ثابت Uint32 new_kb_flags = new_flags & (ENABLE_RAW_KEYBOARD_داخلا | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);

    إذا (old_kb_flags != new_kb_flags) {
        devices[ڳڻپ].us_Usage_صفحو = USB_USAGEPAGE_GENERIC_DESKTOP;
        devices[ڳڻپ].usUsage = USB_USAGE_GENERIC_KEYBOARD;

        إذا (new_kb_flags & ENABLE_RAW_KEYBOARD_داخلا) {
            devices[ڳڻپ].dwFlags = 0;
            devices[ڳڻپ].hwnd_هدف = دري;
            إذا (new_kb_flags & RAW_KEYBOARD_FLAG_NOHOTKEYS) {
                devices[ڳڻپ].dwFlags |= RIDEV_NOHOTKEYS;
            }
            إذا (new_kb_flags & RAW_KEYBOARD_FLAG_INPUTSINK) {
                devices[ڳڻپ].dwFlags |= RIDEV_INPUTSINK;
            }
        } وإلا {
            devices[ڳڻپ].dwFlags = RIDEV_REMOVE;
            devices[ڳڻپ].hwnd_هدف = عدم;
        }

        ++ڳڻپ;
    }

    إذا (رجسٽر_Raw_داخلا_Devices(devices, ڳڻپ, حجم(devices[0]))) {
        أرجع true;
    }
    أرجع false;
}

ساكن DWORD WINAPI WIN_Raw_داخلا_Thread(LPVOID param)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    Uint32 آخري_flags = 0;
    HWND دري;

    SDL_SYS_تياري_Thread("SDLRawInput");

    دري = Create_دري_Ex(0, متن_2("Message"), عدم, 0, 0, 0, 0, 0, HWND_پيغام, عدم, عدم, عدم);
    إذا (!دري) {
        أرجع 0;
    }

    // This doesn't *really* need to be atomic, because the parent is waiting for us
    آخري_flags = SDL_GetAtomicU32(&thread_معلومات.flags);
    إذا (!Update_Raw_داخلا_Device_Flags(دري, 0, آخري_flags)) {
        Destroy_دري(دري);
        أرجع 0;
    }

    // Make sure we get events as soon as possible
    سيٽ_Thread_ترجيح(GetCurrentThread(), THREAD_ترجيح_وقت_CRITICAL);

    // Tell the parent we're ready to go!
    سيٽ_Event(thread_معلومات.ready_event);

    Raw_داخلا_Iterate_نتيجو iter_نتيجو;

    Uint64 idle_begin = SDL_GetTicksNS();
    طالما ((iter_نتيجو = Iterate_Raw_داخلا_Thread()) != RINP_QUIT) {
        بدل (iter_نتيجو) {
        حالة RINP_QUIT: // Unreachable
            اكسر;
        حالة RINP_UPDATE:
        {
            ثابت Uint32 new_flags = SDL_GetAtomicU32(&thread_معلومات.flags);
            إذا (!Update_Raw_داخلا_Device_Flags(دري, آخري_flags, new_flags)) {
                // Revert the shared flags so the main thread can detect the failure
                SDL_سيٽ_Atomic_U32(&thread_معلومات.flags, آخري_flags);
            } وإلا {
                آخري_flags = new_flags;
            }
        } اكسر;
        حالة RINP_CONTINUE:
        {
            Uint64 idle_پڇاڙي = SDL_GetTicksNS();
            Uint64 idle_وقت = idle_پڇاڙي - idle_begin;
            Uint64 usb_8khz_interval = SDL_US_منزل_NS(125);
            Uint64 poll_شروعات = idle_وقت < usb_8khz_interval ? _this->اندروني->آخري_rawinput_poll : idle_پڇاڙي;

            WIN_Poll_Raw_داخلا(_this, poll_شروعات);

            // Reset idle_begin for the next go-around
            idle_begin = SDL_GetTicksNS();
        } اكسر;
        }
    }

    إذا (_this->اندروني->raw_داخلا_fake_pen_id) {
        SDL_RemovePenDevice(0, SDL_GetKeyboardFocus(), _this->اندروني->raw_داخلا_fake_pen_id);
        _this->اندروني->raw_داخلا_fake_pen_id = 0;
    }

    // Reset this here, since if we're exiting due to failure, WIN_UpdateRawInputEnabled would see a stale value.
    SDL_سيٽ_Atomic_U32(&thread_معلومات.flags, 0);

    Update_Raw_داخلا_Device_Flags(عدم, آخري_flags, 0);

    Destroy_دري(دري);

    أرجع 0;
}

ساكن فراغ Cleanup_Raw_داخلا_Thread_معلومات(فراغ)
{
    إذا (thread_معلومات.thread) {
        thread_معلومات.پورو = true;
        سيٽ_Event(thread_معلومات.signal_event);
        WaitForSingleObject(thread_معلومات.thread, 3000);
        CloseHandle(thread_معلومات.thread);
    }

    إذا (thread_معلومات.ready_event) {
        CloseHandle(thread_معلومات.ready_event);
    }

    إذا (thread_معلومات.signal_event) {
        CloseHandle(thread_معلومات.signal_event);
    }

    thread_معلومات = (Raw_داخلا_Thread_معلومات){ 0 };
}

// Computes the desired raw input flags from SDL_VideoData and ensures the
// raw input thread's device registrations match.
// Creates the thread on first use, only WIN_QuitRawInput actually shuts it down.
ساكن bool WIN_Update_Raw_داخلا_Enabled(SDL_VideoDevice *_this)
{
    bool نتيجو = false;
    SDL_Video_معلومات *معلومات = _this->اندروني;
    Uint32 desired_flags = 0;

    إذا (!معلومات->gameinput_context) {
        إذا (معلومات->raw_mouse_enabled) {
            desired_flags |= ENABLE_RAW_MOUSE_داخلا;
            إذا (معلومات->raw_mouse_flag_nolegacy) {
                desired_flags |= RAW_MOUSE_FLAG_NOLEGACY;
            }
        }
        إذا (معلومات->raw_keyboard_enabled) {
            desired_flags |= ENABLE_RAW_KEYBOARD_داخلا;
            إذا (معلومات->raw_keyboard_flag_nohotkeys) {
                desired_flags |= RAW_KEYBOARD_FLAG_NOHOTKEYS;
            }
            إذا (معلومات->raw_keyboard_flag_inputsink) {
                desired_flags |= RAW_KEYBOARD_FLAG_INPUTSINK;
            }
        }
    }

    إذا (desired_flags == SDL_GetAtomicU32(&thread_معلومات.flags)) {
        نتيجو = true;
        اذهب پورو;
    }

    // If the thread exited unexpectedly (e.g. MsgWaitForMultipleObjects failed),
    // the handle is stale. Clean it up so the creation path below can recover.
    إذا (thread_معلومات.thread && WaitForSingleObject(thread_معلومات.thread, 0) != WAIT_TIMEOUT) {
        Cleanup_Raw_داخلا_Thread_معلومات();
    }

    // The thread will read from this to update its flags
    SDL_سيٽ_Atomic_U32(&thread_معلومات.flags, desired_flags);

    إذا (thread_معلومات.thread) {
        // Thread is already running. Fire (the event) and forget, it'll read the atomic flags on wakeup.

        // If RegisterRawInputDevices fails, the thread reverts the atomic and the next call
        // to this function will see the mismatch and retry.
        SDL_assert(thread_معلومات.signal_event);
        سيٽ_Event(thread_معلومات.signal_event);
        نتيجو = true;
    } وإلا إذا (desired_flags) {
        HANDLE wait_handles[2];

        // Thread isn't running, spin it up
        thread_معلومات.ready_event = CreateEvent(عدم, FALSE, FALSE, عدم);
        إذا (!thread_معلومات.ready_event) {
            WIN_سيٽ_Error("CreateEvent");
            اذهب پورو;
        }

        thread_معلومات.پورو = false;
        thread_معلومات.signal_event = CreateEvent(عدم, FALSE, FALSE, عدم);
        إذا (!thread_معلومات.signal_event) {
            WIN_سيٽ_Error("CreateEvent");
            اذهب پورو;
        }

        thread_معلومات.thread = CreateThread(عدم, 0, WIN_Raw_داخلا_Thread, عدم, 0, عدم);
        إذا (!thread_معلومات.thread) {
            WIN_سيٽ_Error("CreateThread");
            اذهب پورو;
        }

        // Wait for the thread to complete initial setup or exit
        wait_handles[0] = thread_معلومات.ready_event;
        wait_handles[1] = thread_معلومات.thread;
        إذا (Wait_For_گڻو_Objects(2, wait_handles, FALSE, INFINITE) != WAIT_OBJECT_0) {
            SDL_سيٽ_Error("Couldn't set up raw input handling");
            اذهب پورو;
        }
        نتيجو = true;
    } وإلا {
        // Thread isn't running and we tried to disable raw input, nothing to do
        نتيجو = true;
    }
پورو:
    إذا (!نتيجو) {
        Cleanup_Raw_داخلا_Thread_معلومات();
    }
    أرجع نتيجو;
}

bool WIN_سيٽ_Raw_Mouse_Enabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_معلومات *معلومات = _this->اندروني;
    معلومات->raw_mouse_enabled = enabled;
    إذا (معلومات->gameinput_context) {
        إذا (!WIN_Update_Game_داخلا_Enabled(_this)) {
            معلومات->raw_mouse_enabled = !enabled;
            أرجع false;
        }
    } وإلا {
        إذا (!WIN_Update_Raw_داخلا_Enabled(_this)) {
            معلومات->raw_mouse_enabled = !enabled;
            أرجع false;
        }
    }
    أرجع true;
}

bool WIN_سيٽ_Raw_Mouse_Flag_No_Legacy(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_معلومات *معلومات = _this->اندروني;

    معلومات->raw_mouse_flag_nolegacy = enabled;

    أرجع WIN_Update_Raw_داخلا_Enabled(_this);
}

bool WIN_سيٽ_Raw_Keyboard_Enabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_معلومات *معلومات = _this->اندروني;
    معلومات->raw_keyboard_enabled = enabled;
    إذا (معلومات->gameinput_context) {
        إذا (!WIN_Update_Game_داخلا_Enabled(_this)) {
            معلومات->raw_keyboard_enabled = !enabled;
            أرجع false;
        }
    } وإلا {
        إذا (!WIN_Update_Raw_داخلا_Enabled(_this)) {
            معلومات->raw_keyboard_enabled = !enabled;
            أرجع false;
        }
    }
    أرجع true;
}

bool WIN_سيٽ_Raw_Keyboard_Flag_No_Hotkeys(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_معلومات *معلومات = _this->اندروني;

    معلومات->raw_keyboard_flag_nohotkeys = enabled;

    أرجع WIN_Update_Raw_داخلا_Enabled(_this);
}

bool WIN_سيٽ_Raw_Keyboard_Flag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_معلومات *معلومات = _this->اندروني;

    معلومات->raw_keyboard_flag_inputsink = enabled;

    أرجع WIN_Update_Raw_داخلا_Enabled(_this);
}

فراغ WIN_Quit_Raw_داخلا(SDL_VideoDevice *_this)
{
    Cleanup_Raw_داخلا_Thread_معلومات();
}

#وإلا

bool WIN_سيٽ_Raw_Mouse_Enabled(SDL_VideoDevice *_this, bool enabled)
{
    أرجع SDL_Unsupported();
}

bool WIN_سيٽ_Raw_Mouse_Flag_No_Legacy(SDL_VideoDevice *_this, bool enabled)
{
    أرجع SDL_Unsupported();
}

bool WIN_سيٽ_Raw_Keyboard_Enabled(SDL_VideoDevice *_this, bool enabled)
{
    أرجع SDL_Unsupported();
}

bool WIN_سيٽ_Raw_Keyboard_Flag_No_Hotkeys(SDL_VideoDevice *_this, bool enabled)
{
    أرجع SDL_Unsupported();
}

bool WIN_سيٽ_Raw_Keyboard_Flag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    أرجع SDL_Unsupported();
}

فراغ WIN_Quit_Raw_داخلا(SDL_VideoDevice *_this)
{
}

#جيڪڏهن_پورو // !SDL_PLATFORM_XBOXONE && !SDL_PLATFORM_XBOXSERIES

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_WINDOWS

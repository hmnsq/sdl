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

#تعریف_کن ENABLE_RAW_MOUSE_درون_داد      0x01
#تعریف_کن RAW_MOUSE_FLAG_NOLEGACY     0x02
#تعریف_کن ENABLE_RAW_KEYBOARD_درون_داد   0x10
#تعریف_کن RAW_KEYBOARD_FLAG_NOHOTKEYS 0x20
#تعریف_کن RAW_KEYBOARD_FLAG_INPUTSINK 0x40

تعريفنوع بنية
{
    bool انجامشده;
    SDL_AtomicU32 flags; // Thread sets this to the actually-set flags if updating state failed
    HANDLE ready_event;
    HANDLE signal_event;
    HANDLE thread;
} Raw_درون_داد_Thread_داده;

ساكن Raw_درون_داد_Thread_داده thread_داده = { 0 };

تعريفنوع تعداد
{
    RINP_QUIT,
    RINP_UPDATE,
    RINP_CONTINUE
} Raw_درون_داد_Iterate_نتیجه;

ساكن Raw_درون_داد_Iterate_نتیجه Iterate_Raw_درون_داد_Thread(فراغ)
{
    // The high-order word of GetQueueStatus() will let us know if there's immediate raw input to be processed.
    // A (necessary!) side effect is that it also marks the message queue bits as stale,
    // so MsgWaitForMultipleObjects will block.

    // Any pending flag update won't be processed until the queue drains, but this is
    // at most one poll cycle since GetQueueStatus clears the wake bits.
    إذا (HIWORD(Get_صف_وضعیت(QS_RAWINPUT)) & QS_RAWINPUT) {
        أرجع thread_داده.انجامشده ? RINP_QUIT : RINP_CONTINUE;
    }

    ساكن ثابت DWORD WAIT_SIGNAL = WAIT_OBJECT_0;
    ساكن ثابت DWORD WAIT_درون_داد = WAIT_OBJECT_0 + 1;

    // There wasn't anything, so we'll wait until new data (or signal_event) wakes us up.
    DWORD wait_وضعیت = پیام_Wait_For_مضرب_Objects(1, &thread_داده.signal_event, FALSE, INFINITE, QS_RAWINPUT);
    إذا (wait_وضعیت == WAIT_SIGNAL) {
        // signal_event can only be set if we need to update or quit.
        أرجع thread_داده.انجامشده ? RINP_QUIT : RINP_UPDATE;
    } وإلا إذا (wait_وضعیت == WAIT_درون_داد) {
        أرجع RINP_CONTINUE;
    } وإلا {
        SDL_LogWarn(SDL_LOG_CATEGORY_درون_داد, "Raw input thread exiting, unexpected wait result: %" SDL_PRIuULONG, wait_وضعیت);
        أرجع RINP_QUIT;
    }
}

ساكن bool Update_Raw_درون_داد_Device_Flags(HWND پنجره, Uint32 آخرین_flags, Uint32 new_flags)
{
    // We had nothing enabled, and we're trying to stop everything. Nothing to do.
    إذا (آخرین_flags == new_flags) {
        أرجع true;
    }

    RAWINPUTDEVICE devices[2] = { 0 };
    UINT شمار = 0;

    ثابت Uint32 old_mouse_flags = آخرین_flags & (ENABLE_RAW_MOUSE_درون_داد | RAW_MOUSE_FLAG_NOLEGACY);
    ثابت Uint32 new_mouse_flags = new_flags & (ENABLE_RAW_MOUSE_درون_داد | RAW_MOUSE_FLAG_NOLEGACY);

    إذا (old_mouse_flags != new_mouse_flags) {
        devices[شمار].us_Usage_صفحه = USB_USAGEPAGE_GENERIC_DESKTOP;
        devices[شمار].usUsage = USB_USAGE_GENERIC_MOUSE;

        إذا (new_flags & ENABLE_RAW_MOUSE_درون_داد) {
            devices[شمار].dwFlags = 0;
            devices[شمار].hwnd_هدف = پنجره;
            إذا (new_mouse_flags & RAW_MOUSE_FLAG_NOLEGACY) {
                devices[شمار].dwFlags |= RIDEV_NOLEGACY;
            }
        } وإلا {
            devices[شمار].dwFlags = RIDEV_REMOVE;
            devices[شمار].hwnd_هدف = عدم;
        }

        ++شمار;
    }

    ثابت Uint32 old_kb_flags = آخرین_flags & (ENABLE_RAW_KEYBOARD_درون_داد | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);
    ثابت Uint32 new_kb_flags = new_flags & (ENABLE_RAW_KEYBOARD_درون_داد | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);

    إذا (old_kb_flags != new_kb_flags) {
        devices[شمار].us_Usage_صفحه = USB_USAGEPAGE_GENERIC_DESKTOP;
        devices[شمار].usUsage = USB_USAGE_GENERIC_KEYBOARD;

        إذا (new_kb_flags & ENABLE_RAW_KEYBOARD_درون_داد) {
            devices[شمار].dwFlags = 0;
            devices[شمار].hwnd_هدف = پنجره;
            إذا (new_kb_flags & RAW_KEYBOARD_FLAG_NOHOTKEYS) {
                devices[شمار].dwFlags |= RIDEV_NOHOTKEYS;
            }
            إذا (new_kb_flags & RAW_KEYBOARD_FLAG_INPUTSINK) {
                devices[شمار].dwFlags |= RIDEV_INPUTSINK;
            }
        } وإلا {
            devices[شمار].dwFlags = RIDEV_REMOVE;
            devices[شمار].hwnd_هدف = عدم;
        }

        ++شمار;
    }

    إذا (ثبات_Raw_درون_داد_Devices(devices, شمار, حجم(devices[0]))) {
        أرجع true;
    }
    أرجع false;
}

ساكن DWORD WINAPI WIN_Raw_درون_داد_Thread(LPVOID param)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    Uint32 آخرین_flags = 0;
    HWND پنجره;

    SDL_SYS_راهاندازی_Thread("SDLRawInput");

    پنجره = Create_پنجره_Ex(0, متن_2("Message"), عدم, 0, 0, 0, 0, 0, HWND_پیام, عدم, عدم, عدم);
    إذا (!پنجره) {
        أرجع 0;
    }

    // This doesn't *really* need to be atomic, because the parent is waiting for us
    آخرین_flags = SDL_GetAtomicU32(&thread_داده.flags);
    إذا (!Update_Raw_درون_داد_Device_Flags(پنجره, 0, آخرین_flags)) {
        Destroy_پنجره(پنجره);
        أرجع 0;
    }

    // Make sure we get events as soon as possible
    مجموعه_Thread_اولویت(GetCurrentThread(), THREAD_اولویت_زمان_CRITICAL);

    // Tell the parent we're ready to go!
    مجموعه_Event(thread_داده.ready_event);

    Raw_درون_داد_Iterate_نتیجه iter_نتیجه;

    Uint64 idle_begin = SDL_GetTicksNS();
    طالما ((iter_نتیجه = Iterate_Raw_درون_داد_Thread()) != RINP_QUIT) {
        بدل (iter_نتیجه) {
        حالة RINP_QUIT: // Unreachable
            اكسر;
        حالة RINP_UPDATE:
        {
            ثابت Uint32 new_flags = SDL_GetAtomicU32(&thread_داده.flags);
            إذا (!Update_Raw_درون_داد_Device_Flags(پنجره, آخرین_flags, new_flags)) {
                // Revert the shared flags so the main thread can detect the failure
                SDL_مجموعه_Atomic_U32(&thread_داده.flags, آخرین_flags);
            } وإلا {
                آخرین_flags = new_flags;
            }
        } اكسر;
        حالة RINP_CONTINUE:
        {
            Uint64 idle_انتها = SDL_GetTicksNS();
            Uint64 idle_زمان = idle_انتها - idle_begin;
            Uint64 usb_8khz_interval = SDL_US_مقصد_NS(125);
            Uint64 poll_شروع = idle_زمان < usb_8khz_interval ? _this->داخلی->آخرین_rawinput_poll : idle_انتها;

            WIN_Poll_Raw_درون_داد(_this, poll_شروع);

            // Reset idle_begin for the next go-around
            idle_begin = SDL_GetTicksNS();
        } اكسر;
        }
    }

    إذا (_this->داخلی->raw_درون_داد_fake_pen_id) {
        SDL_RemovePenDevice(0, SDL_GetKeyboardFocus(), _this->داخلی->raw_درون_داد_fake_pen_id);
        _this->داخلی->raw_درون_داد_fake_pen_id = 0;
    }

    // Reset this here, since if we're exiting due to failure, WIN_UpdateRawInputEnabled would see a stale value.
    SDL_مجموعه_Atomic_U32(&thread_داده.flags, 0);

    Update_Raw_درون_داد_Device_Flags(عدم, آخرین_flags, 0);

    Destroy_پنجره(پنجره);

    أرجع 0;
}

ساكن فراغ Cleanup_Raw_درون_داد_Thread_داده(فراغ)
{
    إذا (thread_داده.thread) {
        thread_داده.انجامشده = true;
        مجموعه_Event(thread_داده.signal_event);
        WaitForSingleObject(thread_داده.thread, 3000);
        CloseHandle(thread_داده.thread);
    }

    إذا (thread_داده.ready_event) {
        CloseHandle(thread_داده.ready_event);
    }

    إذا (thread_داده.signal_event) {
        CloseHandle(thread_داده.signal_event);
    }

    thread_داده = (Raw_درون_داد_Thread_داده){ 0 };
}

// Computes the desired raw input flags from SDL_VideoData and ensures the
// raw input thread's device registrations match.
// Creates the thread on first use, only WIN_QuitRawInput actually shuts it down.
ساكن bool WIN_Update_Raw_درون_داد_Enabled(SDL_VideoDevice *_this)
{
    bool نتیجه = false;
    SDL_Video_داده *داده = _this->داخلی;
    Uint32 desired_flags = 0;

    إذا (!داده->gameinput_context) {
        إذا (داده->raw_mouse_enabled) {
            desired_flags |= ENABLE_RAW_MOUSE_درون_داد;
            إذا (داده->raw_mouse_flag_nolegacy) {
                desired_flags |= RAW_MOUSE_FLAG_NOLEGACY;
            }
        }
        إذا (داده->raw_keyboard_enabled) {
            desired_flags |= ENABLE_RAW_KEYBOARD_درون_داد;
            إذا (داده->raw_keyboard_flag_nohotkeys) {
                desired_flags |= RAW_KEYBOARD_FLAG_NOHOTKEYS;
            }
            إذا (داده->raw_keyboard_flag_inputsink) {
                desired_flags |= RAW_KEYBOARD_FLAG_INPUTSINK;
            }
        }
    }

    إذا (desired_flags == SDL_GetAtomicU32(&thread_داده.flags)) {
        نتیجه = true;
        اذهب انجامشده;
    }

    // If the thread exited unexpectedly (e.g. MsgWaitForMultipleObjects failed),
    // the handle is stale. Clean it up so the creation path below can recover.
    إذا (thread_داده.thread && WaitForSingleObject(thread_داده.thread, 0) != WAIT_TIMEOUT) {
        Cleanup_Raw_درون_داد_Thread_داده();
    }

    // The thread will read from this to update its flags
    SDL_مجموعه_Atomic_U32(&thread_داده.flags, desired_flags);

    إذا (thread_داده.thread) {
        // Thread is already running. Fire (the event) and forget, it'll read the atomic flags on wakeup.

        // If RegisterRawInputDevices fails, the thread reverts the atomic and the next call
        // to this function will see the mismatch and retry.
        SDL_assert(thread_داده.signal_event);
        مجموعه_Event(thread_داده.signal_event);
        نتیجه = true;
    } وإلا إذا (desired_flags) {
        HANDLE wait_handles[2];

        // Thread isn't running, spin it up
        thread_داده.ready_event = CreateEvent(عدم, FALSE, FALSE, عدم);
        إذا (!thread_داده.ready_event) {
            WIN_مجموعه_Error("CreateEvent");
            اذهب انجامشده;
        }

        thread_داده.انجامشده = false;
        thread_داده.signal_event = CreateEvent(عدم, FALSE, FALSE, عدم);
        إذا (!thread_داده.signal_event) {
            WIN_مجموعه_Error("CreateEvent");
            اذهب انجامشده;
        }

        thread_داده.thread = CreateThread(عدم, 0, WIN_Raw_درون_داد_Thread, عدم, 0, عدم);
        إذا (!thread_داده.thread) {
            WIN_مجموعه_Error("CreateThread");
            اذهب انجامشده;
        }

        // Wait for the thread to complete initial setup or exit
        wait_handles[0] = thread_داده.ready_event;
        wait_handles[1] = thread_داده.thread;
        إذا (Wait_For_مضرب_Objects(2, wait_handles, FALSE, INFINITE) != WAIT_OBJECT_0) {
            SDL_مجموعه_Error("Couldn't set up raw input handling");
            اذهب انجامشده;
        }
        نتیجه = true;
    } وإلا {
        // Thread isn't running and we tried to disable raw input, nothing to do
        نتیجه = true;
    }
انجامشده:
    إذا (!نتیجه) {
        Cleanup_Raw_درون_داد_Thread_داده();
    }
    أرجع نتیجه;
}

bool WIN_مجموعه_Raw_Mouse_Enabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_داده *داده = _this->داخلی;
    داده->raw_mouse_enabled = enabled;
    إذا (داده->gameinput_context) {
        إذا (!WIN_Update_Game_درون_داد_Enabled(_this)) {
            داده->raw_mouse_enabled = !enabled;
            أرجع false;
        }
    } وإلا {
        إذا (!WIN_Update_Raw_درون_داد_Enabled(_this)) {
            داده->raw_mouse_enabled = !enabled;
            أرجع false;
        }
    }
    أرجع true;
}

bool WIN_مجموعه_Raw_Mouse_Flag_No_Legacy(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_داده *داده = _this->داخلی;

    داده->raw_mouse_flag_nolegacy = enabled;

    أرجع WIN_Update_Raw_درون_داد_Enabled(_this);
}

bool WIN_مجموعه_Raw_Keyboard_Enabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_داده *داده = _this->داخلی;
    داده->raw_keyboard_enabled = enabled;
    إذا (داده->gameinput_context) {
        إذا (!WIN_Update_Game_درون_داد_Enabled(_this)) {
            داده->raw_keyboard_enabled = !enabled;
            أرجع false;
        }
    } وإلا {
        إذا (!WIN_Update_Raw_درون_داد_Enabled(_this)) {
            داده->raw_keyboard_enabled = !enabled;
            أرجع false;
        }
    }
    أرجع true;
}

bool WIN_مجموعه_Raw_Keyboard_Flag_No_Hotkeys(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_داده *داده = _this->داخلی;

    داده->raw_keyboard_flag_nohotkeys = enabled;

    أرجع WIN_Update_Raw_درون_داد_Enabled(_this);
}

bool WIN_مجموعه_Raw_Keyboard_Flag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_داده *داده = _this->داخلی;

    داده->raw_keyboard_flag_inputsink = enabled;

    أرجع WIN_Update_Raw_درون_داد_Enabled(_this);
}

فراغ WIN_Quit_Raw_درون_داد(SDL_VideoDevice *_this)
{
    Cleanup_Raw_درون_داد_Thread_داده();
}

#وإلا

bool WIN_مجموعه_Raw_Mouse_Enabled(SDL_VideoDevice *_this, bool enabled)
{
    أرجع SDL_Unsupported();
}

bool WIN_مجموعه_Raw_Mouse_Flag_No_Legacy(SDL_VideoDevice *_this, bool enabled)
{
    أرجع SDL_Unsupported();
}

bool WIN_مجموعه_Raw_Keyboard_Enabled(SDL_VideoDevice *_this, bool enabled)
{
    أرجع SDL_Unsupported();
}

bool WIN_مجموعه_Raw_Keyboard_Flag_No_Hotkeys(SDL_VideoDevice *_this, bool enabled)
{
    أرجع SDL_Unsupported();
}

bool WIN_مجموعه_Raw_Keyboard_Flag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    أرجع SDL_Unsupported();
}

فراغ WIN_Quit_Raw_درون_داد(SDL_VideoDevice *_this)
{
}

#پایان_اگر // !SDL_PLATFORM_XBOXONE && !SDL_PLATFORM_XBOXSERIES

#پایان_اگر // SDL_VIDEO_DRIVER_WINDOWS

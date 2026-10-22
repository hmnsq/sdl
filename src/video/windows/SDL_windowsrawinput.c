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
#شامل "SDL_internal.h"

#اگر defined(SDL_VIDEO_DRIVER_WINDOWS)

#شامل "SDL_windowsvideo.h"

#اگر !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#شامل "SDL_windowsevents.h"

#شامل "../../joystick/usb_ids.h"
#شامل "../../events/SDL_events_c.h"
#شامل "../../thread/SDL_systhread.h"

#تعریف_کرو ENABLE_RAW_MOUSE_داخلہ      0x01
#تعریف_کرو RAW_MOUSE_FLAG_NOLEGACY     0x02
#تعریف_کرو ENABLE_RAW_KEYBOARD_داخلہ   0x10
#تعریف_کرو RAW_KEYBOARD_FLAG_NOHOTKEYS 0x20
#تعریف_کرو RAW_KEYBOARD_FLAG_INPUTSINK 0x40

قسمتعریف ساخت
{
    bool مکمل;
    SDL_AtomicU32 flags; // Thread sets this to the actually-set flags if updating state failed
    HANDLE ready_event;
    HANDLE signal_event;
    HANDLE thread;
} Raw_داخلہ_Thread_ڈیٹا;

ساکن Raw_داخلہ_Thread_ڈیٹا thread_ڈیٹا = { 0 };

قسمتعریف شمار
{
    RINP_QUIT,
    RINP_UPDATE,
    RINP_CONTINUE
} Raw_داخلہ_Iterate_نتیجہ;

ساکن Raw_داخلہ_Iterate_نتیجہ Iterate_Raw_داخلہ_Thread(خالی)
{
    // The high-order word of GetQueueStatus() will let us know if there's immediate raw input to be processed.
    // A (necessary!) side effect is that it also marks the message queue bits as stale,
    // so MsgWaitForMultipleObjects will block.

    // Any pending flag update won't be processed until the queue drains, but this is
    // at most one poll cycle since GetQueueStatus clears the wake bits.
    اگر (HIWORD(Get_قطار_حالت(QS_RAWINPUT)) & QS_RAWINPUT) {
        واپس thread_ڈیٹا.مکمل ? RINP_QUIT : RINP_CONTINUE;
    }

    ساکن ثابت DWORD WAIT_SIGNAL = WAIT_OBJECT_0;
    ساکن ثابت DWORD WAIT_داخلہ = WAIT_OBJECT_0 + 1;

    // There wasn't anything, so we'll wait until new data (or signal_event) wakes us up.
    DWORD wait_حالت = پیغام_Wait_For_مضرب_Objects(1, &thread_ڈیٹا.signal_event, FALSE, INFINITE, QS_RAWINPUT);
    اگر (wait_حالت == WAIT_SIGNAL) {
        // signal_event can only be set if we need to update or quit.
        واپس thread_ڈیٹا.مکمل ? RINP_QUIT : RINP_UPDATE;
    } ورنہ اگر (wait_حالت == WAIT_داخلہ) {
        واپس RINP_CONTINUE;
    } ورنہ {
        SDL_LogWarn(SDL_LOG_CATEGORY_داخلہ, "Raw input thread exiting, unexpected wait result: %" SDL_PRIuULONG, wait_حالت);
        واپس RINP_QUIT;
    }
}

ساکن bool Update_Raw_داخلہ_Device_Flags(HWND کھڑکی, Uint32 آخری_flags, Uint32 new_flags)
{
    // We had nothing enabled, and we're trying to stop everything. Nothing to do.
    اگر (آخری_flags == new_flags) {
        واپس true;
    }

    RAWINPUTDEVICE devices[2] = { 0 };
    UINT گنتی = 0;

    ثابت Uint32 old_mouse_flags = آخری_flags & (ENABLE_RAW_MOUSE_داخلہ | RAW_MOUSE_FLAG_NOLEGACY);
    ثابت Uint32 new_mouse_flags = new_flags & (ENABLE_RAW_MOUSE_داخلہ | RAW_MOUSE_FLAG_NOLEGACY);

    اگر (old_mouse_flags != new_mouse_flags) {
        devices[گنتی].us_Usage_صفحہ = USB_USAGEPAGE_GENERIC_DESKTOP;
        devices[گنتی].usUsage = USB_USAGE_GENERIC_MOUSE;

        اگر (new_flags & ENABLE_RAW_MOUSE_داخلہ) {
            devices[گنتی].dwFlags = 0;
            devices[گنتی].hwnd_ہدف = کھڑکی;
            اگر (new_mouse_flags & RAW_MOUSE_FLAG_NOLEGACY) {
                devices[گنتی].dwFlags |= RIDEV_NOLEGACY;
            }
        } ورنہ {
            devices[گنتی].dwFlags = RIDEV_REMOVE;
            devices[گنتی].hwnd_ہدف = تہی;
        }

        ++گنتی;
    }

    ثابت Uint32 old_kb_flags = آخری_flags & (ENABLE_RAW_KEYBOARD_داخلہ | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);
    ثابت Uint32 new_kb_flags = new_flags & (ENABLE_RAW_KEYBOARD_داخلہ | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);

    اگر (old_kb_flags != new_kb_flags) {
        devices[گنتی].us_Usage_صفحہ = USB_USAGEPAGE_GENERIC_DESKTOP;
        devices[گنتی].usUsage = USB_USAGE_GENERIC_KEYBOARD;

        اگر (new_kb_flags & ENABLE_RAW_KEYBOARD_داخلہ) {
            devices[گنتی].dwFlags = 0;
            devices[گنتی].hwnd_ہدف = کھڑکی;
            اگر (new_kb_flags & RAW_KEYBOARD_FLAG_NOHOTKEYS) {
                devices[گنتی].dwFlags |= RIDEV_NOHOTKEYS;
            }
            اگر (new_kb_flags & RAW_KEYBOARD_FLAG_INPUTSINK) {
                devices[گنتی].dwFlags |= RIDEV_INPUTSINK;
            }
        } ورنہ {
            devices[گنتی].dwFlags = RIDEV_REMOVE;
            devices[گنتی].hwnd_ہدف = تہی;
        }

        ++گنتی;
    }

    اگر (رجسٹر_Raw_داخلہ_Devices(devices, گنتی, حجم(devices[0]))) {
        واپس true;
    }
    واپس false;
}

ساکن DWORD WINAPI WIN_Raw_داخلہ_Thread(LPVOID param)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    Uint32 آخری_flags = 0;
    HWND کھڑکی;

    SDL_SYS_تیاری_Thread("SDLRawInput");

    کھڑکی = Create_کھڑکی_Ex(0, متن_2("Message"), تہی, 0, 0, 0, 0, 0, HWND_پیغام, تہی, تہی, تہی);
    اگر (!کھڑکی) {
        واپس 0;
    }

    // This doesn't *really* need to be atomic, because the parent is waiting for us
    آخری_flags = SDL_GetAtomicU32(&thread_ڈیٹا.flags);
    اگر (!Update_Raw_داخلہ_Device_Flags(کھڑکی, 0, آخری_flags)) {
        Destroy_کھڑکی(کھڑکی);
        واپس 0;
    }

    // Make sure we get events as soon as possible
    سیٹ_Thread_ترجیح(GetCurrentThread(), THREAD_ترجیح_وقت_CRITICAL);

    // Tell the parent we're ready to go!
    سیٹ_Event(thread_ڈیٹا.ready_event);

    Raw_داخلہ_Iterate_نتیجہ iter_نتیجہ;

    Uint64 idle_begin = SDL_GetTicksNS();
    جب ((iter_نتیجہ = Iterate_Raw_داخلہ_Thread()) != RINP_QUIT) {
        انتخاب (iter_نتیجہ) {
        حالت RINP_QUIT: // Unreachable
            توڑو;
        حالت RINP_UPDATE:
        {
            ثابت Uint32 new_flags = SDL_GetAtomicU32(&thread_ڈیٹا.flags);
            اگر (!Update_Raw_داخلہ_Device_Flags(کھڑکی, آخری_flags, new_flags)) {
                // Revert the shared flags so the main thread can detect the failure
                SDL_سیٹ_Atomic_U32(&thread_ڈیٹا.flags, آخری_flags);
            } ورنہ {
                آخری_flags = new_flags;
            }
        } توڑو;
        حالت RINP_CONTINUE:
        {
            Uint64 idle_انتہا = SDL_GetTicksNS();
            Uint64 idle_وقت = idle_انتہا - idle_begin;
            Uint64 usb_8khz_interval = SDL_US_مقصد_NS(125);
            Uint64 poll_آغاز = idle_وقت < usb_8khz_interval ? _this->اندرونی_2->آخری_rawinput_poll : idle_انتہا;

            WIN_Poll_Raw_داخلہ(_this, poll_آغاز);

            // Reset idle_begin for the next go-around
            idle_begin = SDL_GetTicksNS();
        } توڑو;
        }
    }

    اگر (_this->اندرونی_2->raw_داخلہ_fake_pen_id) {
        SDL_RemovePenDevice(0, SDL_GetKeyboardFocus(), _this->اندرونی_2->raw_داخلہ_fake_pen_id);
        _this->اندرونی_2->raw_داخلہ_fake_pen_id = 0;
    }

    // Reset this here, since if we're exiting due to failure, WIN_UpdateRawInputEnabled would see a stale value.
    SDL_سیٹ_Atomic_U32(&thread_ڈیٹا.flags, 0);

    Update_Raw_داخلہ_Device_Flags(تہی, آخری_flags, 0);

    Destroy_کھڑکی(کھڑکی);

    واپس 0;
}

ساکن خالی Cleanup_Raw_داخلہ_Thread_ڈیٹا(خالی)
{
    اگر (thread_ڈیٹا.thread) {
        thread_ڈیٹا.مکمل = true;
        سیٹ_Event(thread_ڈیٹا.signal_event);
        WaitForSingleObject(thread_ڈیٹا.thread, 3000);
        CloseHandle(thread_ڈیٹا.thread);
    }

    اگر (thread_ڈیٹا.ready_event) {
        CloseHandle(thread_ڈیٹا.ready_event);
    }

    اگر (thread_ڈیٹا.signal_event) {
        CloseHandle(thread_ڈیٹا.signal_event);
    }

    thread_ڈیٹا = (Raw_داخلہ_Thread_ڈیٹا){ 0 };
}

// Computes the desired raw input flags from SDL_VideoData and ensures the
// raw input thread's device registrations match.
// Creates the thread on first use, only WIN_QuitRawInput actually shuts it down.
ساکن bool WIN_Update_Raw_داخلہ_Enabled(SDL_VideoDevice *_this)
{
    bool نتیجہ = false;
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;
    Uint32 desired_flags = 0;

    اگر (!ڈیٹا->gameinput_context) {
        اگر (ڈیٹا->raw_mouse_enabled) {
            desired_flags |= ENABLE_RAW_MOUSE_داخلہ;
            اگر (ڈیٹا->raw_mouse_flag_nolegacy) {
                desired_flags |= RAW_MOUSE_FLAG_NOLEGACY;
            }
        }
        اگر (ڈیٹا->raw_keyboard_enabled) {
            desired_flags |= ENABLE_RAW_KEYBOARD_داخلہ;
            اگر (ڈیٹا->raw_keyboard_flag_nohotkeys) {
                desired_flags |= RAW_KEYBOARD_FLAG_NOHOTKEYS;
            }
            اگر (ڈیٹا->raw_keyboard_flag_inputsink) {
                desired_flags |= RAW_KEYBOARD_FLAG_INPUTSINK;
            }
        }
    }

    اگر (desired_flags == SDL_GetAtomicU32(&thread_ڈیٹا.flags)) {
        نتیجہ = true;
        جاؤ مکمل;
    }

    // If the thread exited unexpectedly (e.g. MsgWaitForMultipleObjects failed),
    // the handle is stale. Clean it up so the creation path below can recover.
    اگر (thread_ڈیٹا.thread && WaitForSingleObject(thread_ڈیٹا.thread, 0) != WAIT_TIMEOUT) {
        Cleanup_Raw_داخلہ_Thread_ڈیٹا();
    }

    // The thread will read from this to update its flags
    SDL_سیٹ_Atomic_U32(&thread_ڈیٹا.flags, desired_flags);

    اگر (thread_ڈیٹا.thread) {
        // Thread is already running. Fire (the event) and forget, it'll read the atomic flags on wakeup.

        // If RegisterRawInputDevices fails, the thread reverts the atomic and the next call
        // to this function will see the mismatch and retry.
        SDL_assert(thread_ڈیٹا.signal_event);
        سیٹ_Event(thread_ڈیٹا.signal_event);
        نتیجہ = true;
    } ورنہ اگر (desired_flags) {
        HANDLE wait_handles[2];

        // Thread isn't running, spin it up
        thread_ڈیٹا.ready_event = CreateEvent(تہی, FALSE, FALSE, تہی);
        اگر (!thread_ڈیٹا.ready_event) {
            WIN_سیٹ_Error("CreateEvent");
            جاؤ مکمل;
        }

        thread_ڈیٹا.مکمل = false;
        thread_ڈیٹا.signal_event = CreateEvent(تہی, FALSE, FALSE, تہی);
        اگر (!thread_ڈیٹا.signal_event) {
            WIN_سیٹ_Error("CreateEvent");
            جاؤ مکمل;
        }

        thread_ڈیٹا.thread = CreateThread(تہی, 0, WIN_Raw_داخلہ_Thread, تہی, 0, تہی);
        اگر (!thread_ڈیٹا.thread) {
            WIN_سیٹ_Error("CreateThread");
            جاؤ مکمل;
        }

        // Wait for the thread to complete initial setup or exit
        wait_handles[0] = thread_ڈیٹا.ready_event;
        wait_handles[1] = thread_ڈیٹا.thread;
        اگر (Wait_For_مضرب_Objects(2, wait_handles, FALSE, INFINITE) != WAIT_OBJECT_0) {
            SDL_سیٹ_Error("Couldn't set up raw input handling");
            جاؤ مکمل;
        }
        نتیجہ = true;
    } ورنہ {
        // Thread isn't running and we tried to disable raw input, nothing to do
        نتیجہ = true;
    }
مکمل:
    اگر (!نتیجہ) {
        Cleanup_Raw_داخلہ_Thread_ڈیٹا();
    }
    واپس نتیجہ;
}

bool WIN_سیٹ_Raw_Mouse_Enabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;
    ڈیٹا->raw_mouse_enabled = enabled;
    اگر (ڈیٹا->gameinput_context) {
        اگر (!WIN_Update_Game_داخلہ_Enabled(_this)) {
            ڈیٹا->raw_mouse_enabled = !enabled;
            واپس false;
        }
    } ورنہ {
        اگر (!WIN_Update_Raw_داخلہ_Enabled(_this)) {
            ڈیٹا->raw_mouse_enabled = !enabled;
            واپس false;
        }
    }
    واپس true;
}

bool WIN_سیٹ_Raw_Mouse_Flag_No_Legacy(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;

    ڈیٹا->raw_mouse_flag_nolegacy = enabled;

    واپس WIN_Update_Raw_داخلہ_Enabled(_this);
}

bool WIN_سیٹ_Raw_Keyboard_Enabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;
    ڈیٹا->raw_keyboard_enabled = enabled;
    اگر (ڈیٹا->gameinput_context) {
        اگر (!WIN_Update_Game_داخلہ_Enabled(_this)) {
            ڈیٹا->raw_keyboard_enabled = !enabled;
            واپس false;
        }
    } ورنہ {
        اگر (!WIN_Update_Raw_داخلہ_Enabled(_this)) {
            ڈیٹا->raw_keyboard_enabled = !enabled;
            واپس false;
        }
    }
    واپس true;
}

bool WIN_سیٹ_Raw_Keyboard_Flag_No_Hotkeys(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;

    ڈیٹا->raw_keyboard_flag_nohotkeys = enabled;

    واپس WIN_Update_Raw_داخلہ_Enabled(_this);
}

bool WIN_سیٹ_Raw_Keyboard_Flag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_ڈیٹا *ڈیٹا = _this->اندرونی_2;

    ڈیٹا->raw_keyboard_flag_inputsink = enabled;

    واپس WIN_Update_Raw_داخلہ_Enabled(_this);
}

خالی WIN_Quit_Raw_داخلہ(SDL_VideoDevice *_this)
{
    Cleanup_Raw_داخلہ_Thread_ڈیٹا();
}

#ورنہ

bool WIN_سیٹ_Raw_Mouse_Enabled(SDL_VideoDevice *_this, bool enabled)
{
    واپس SDL_Unsupported();
}

bool WIN_سیٹ_Raw_Mouse_Flag_No_Legacy(SDL_VideoDevice *_this, bool enabled)
{
    واپس SDL_Unsupported();
}

bool WIN_سیٹ_Raw_Keyboard_Enabled(SDL_VideoDevice *_this, bool enabled)
{
    واپس SDL_Unsupported();
}

bool WIN_سیٹ_Raw_Keyboard_Flag_No_Hotkeys(SDL_VideoDevice *_this, bool enabled)
{
    واپس SDL_Unsupported();
}

bool WIN_سیٹ_Raw_Keyboard_Flag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    واپس SDL_Unsupported();
}

خالی WIN_Quit_Raw_داخلہ(SDL_VideoDevice *_this)
{
}

#اگر_ختم // !SDL_PLATFORM_XBOXONE && !SDL_PLATFORM_XBOXSERIES

#اگر_ختم // SDL_VIDEO_DRIVER_WINDOWS

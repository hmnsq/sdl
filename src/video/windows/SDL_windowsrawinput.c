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

#यदि defined(SDL_VIDEO_DRIVER_WINDOWS)

#अन्तर्भाव "SDL_windowsvideo.h"

#यदि !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#अन्तर्भाव "SDL_windowsevents.h"

#अन्तर्भाव "../../joystick/usb_ids.h"
#अन्तर्भाव "../../events/SDL_events_c.h"
#अन्तर्भाव "../../thread/SDL_systhread.h"

#परिभाषय ENABLE_RAW_MOUSE_निवेशः      0x01
#परिभाषय RAW_MOUSE_FLAG_NOLEGACY     0x02
#परिभाषय ENABLE_RAW_KEYBOARD_निवेशः   0x10
#परिभाषय RAW_KEYBOARD_FLAG_NOHOTKEYS 0x20
#परिभाषय RAW_KEYBOARD_FLAG_INPUTSINK 0x40

प्रकारनिर्देश संरचना
{
    bool समाप्तम्;
    SDL_AtomicU32 flags; // Thread sets this to the actually-set flags if updating state failed
    HANDLE ready_event;
    HANDLE signal_event;
    HANDLE thread;
} Raw_निवेशः_Thread_दत्त;

स्थिर Raw_निवेशः_Thread_दत्त thread_दत्त = { 0 };

प्रकारनिर्देश गणना
{
    RINP_QUIT,
    RINP_UPDATE,
    RINP_CONTINUE
} Raw_निवेशः_Iterate_परिणाम;

स्थिर Raw_निवेशः_Iterate_परिणाम Iterate_Raw_निवेशः_Thread(शून्य)
{
    // The high-order word of GetQueueStatus() will let us know if there's immediate raw input to be processed.
    // A (necessary!) side effect is that it also marks the message queue bits as stale,
    // so MsgWaitForMultipleObjects will block.

    // Any pending flag update won't be processed until the queue drains, but this is
    // at most one poll cycle since GetQueueStatus clears the wake bits.
    यदि (HIWORD(Get_Queue_स्थितिः(QS_RAWINPUT)) & QS_RAWINPUT) {
        प्रत्यागम thread_दत्त.समाप्तम् ? RINP_QUIT : RINP_CONTINUE;
    }

    स्थिर ध्रुव DWORD WAIT_SIGNAL = WAIT_OBJECT_0;
    स्थिर ध्रुव DWORD WAIT_निवेशः = WAIT_OBJECT_0 + 1;

    // There wasn't anything, so we'll wait until new data (or signal_event) wakes us up.
    DWORD wait_स्थितिः = सन्देशः_Wait_For_गुणजः_Objects(1, &thread_दत्त.signal_event, FALSE, INFINITE, QS_RAWINPUT);
    यदि (wait_स्थितिः == WAIT_SIGNAL) {
        // signal_event can only be set if we need to update or quit.
        प्रत्यागम thread_दत्त.समाप्तम् ? RINP_QUIT : RINP_UPDATE;
    } अन्यथा यदि (wait_स्थितिः == WAIT_निवेशः) {
        प्रत्यागम RINP_CONTINUE;
    } अन्यथा {
        SDL_LogWarn(SDL_LOG_CATEGORY_निवेशः, "Raw input thread exiting, unexpected wait result: %" SDL_PRIuULONG, wait_स्थितिः);
        प्रत्यागम RINP_QUIT;
    }
}

स्थिर bool Update_Raw_निवेशः_Device_Flags(HWND गवाक्षः, Uint32 चरमः_flags, Uint32 new_flags)
{
    // We had nothing enabled, and we're trying to stop everything. Nothing to do.
    यदि (चरमः_flags == new_flags) {
        प्रत्यागम true;
    }

    RAWINPUTDEVICE devices[2] = { 0 };
    UINT गणनम् = 0;

    ध्रुव Uint32 old_mouse_flags = चरमः_flags & (ENABLE_RAW_MOUSE_निवेशः | RAW_MOUSE_FLAG_NOLEGACY);
    ध्रुव Uint32 new_mouse_flags = new_flags & (ENABLE_RAW_MOUSE_निवेशः | RAW_MOUSE_FLAG_NOLEGACY);

    यदि (old_mouse_flags != new_mouse_flags) {
        devices[गणनम्].usUsagePage = USB_USAGEPAGE_GENERIC_DESKTOP;
        devices[गणनम्].usUsage = USB_USAGE_GENERIC_MOUSE;

        यदि (new_flags & ENABLE_RAW_MOUSE_निवेशः) {
            devices[गणनम्].dwFlags = 0;
            devices[गणनम्].hwndTarget = गवाक्षः;
            यदि (new_mouse_flags & RAW_MOUSE_FLAG_NOLEGACY) {
                devices[गणनम्].dwFlags |= RIDEV_NOLEGACY;
            }
        } अन्यथा {
            devices[गणनम्].dwFlags = RIDEV_REMOVE;
            devices[गणनम्].hwndTarget = रिक्त;
        }

        ++गणनम्;
    }

    ध्रुव Uint32 old_kb_flags = चरमः_flags & (ENABLE_RAW_KEYBOARD_निवेशः | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);
    ध्रुव Uint32 new_kb_flags = new_flags & (ENABLE_RAW_KEYBOARD_निवेशः | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);

    यदि (old_kb_flags != new_kb_flags) {
        devices[गणनम्].usUsagePage = USB_USAGEPAGE_GENERIC_DESKTOP;
        devices[गणनम्].usUsage = USB_USAGE_GENERIC_KEYBOARD;

        यदि (new_kb_flags & ENABLE_RAW_KEYBOARD_निवेशः) {
            devices[गणनम्].dwFlags = 0;
            devices[गणनम्].hwndTarget = गवाक्षः;
            यदि (new_kb_flags & RAW_KEYBOARD_FLAG_NOHOTKEYS) {
                devices[गणनम्].dwFlags |= RIDEV_NOHOTKEYS;
            }
            यदि (new_kb_flags & RAW_KEYBOARD_FLAG_INPUTSINK) {
                devices[गणनम्].dwFlags |= RIDEV_INPUTSINK;
            }
        } अन्यथा {
            devices[गणनम्].dwFlags = RIDEV_REMOVE;
            devices[गणनम्].hwndTarget = रिक्त;
        }

        ++गणनम्;
    }

    यदि (पञ्जिकाकोशः_Raw_निवेशः_Devices(devices, गणनम्, परिमाण(devices[0]))) {
        प्रत्यागम true;
    }
    प्रत्यागम false;
}

स्थिर DWORD WINAPI WIN_Raw_निवेशः_Thread(LPVOID param)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    Uint32 चरमः_flags = 0;
    HWND गवाक्षः;

    SDL_SYS_सज्जता_Thread("SDLRawInput");

    गवाक्षः = Create_गवाक्षः_Ex(0, TEXT("Message"), रिक्त, 0, 0, 0, 0, 0, HWND_सन्देशः, रिक्त, रिक्त, रिक्त);
    यदि (!गवाक्षः) {
        प्रत्यागम 0;
    }

    // This doesn't *really* need to be atomic, because the parent is waiting for us
    चरमः_flags = SDL_GetAtomicU32(&thread_दत्त.flags);
    यदि (!Update_Raw_निवेशः_Device_Flags(गवाक्षः, 0, चरमः_flags)) {
        Destroy_गवाक्षः(गवाक्षः);
        प्रत्यागम 0;
    }

    // Make sure we get events as soon as possible
    समुच्चयः_Thread_प्राथमिकता(GetCurrentThread(), THREAD_प्राथमिकता_TIME_CRITICAL);

    // Tell the parent we're ready to go!
    समुच्चयः_Event(thread_दत्त.ready_event);

    Raw_निवेशः_Iterate_परिणाम iter_परिणाम;

    Uint64 idle_begin = SDL_GetTicksNS();
    यावत् ((iter_परिणाम = Iterate_Raw_निवेशः_Thread()) != RINP_QUIT) {
        विकल्प (iter_परिणाम) {
        पक्ष RINP_QUIT: // Unreachable
            भङ्ग;
        पक्ष RINP_UPDATE:
        {
            ध्रुव Uint32 new_flags = SDL_GetAtomicU32(&thread_दत्त.flags);
            यदि (!Update_Raw_निवेशः_Device_Flags(गवाक्षः, चरमः_flags, new_flags)) {
                // Revert the shared flags so the main thread can detect the failure
                SDL_समुच्चयः_Atomic_U32(&thread_दत्त.flags, चरमः_flags);
            } अन्यथा {
                चरमः_flags = new_flags;
            }
        } भङ्ग;
        पक्ष RINP_CONTINUE:
        {
            Uint64 idle_अन्तः = SDL_GetTicksNS();
            Uint64 idle_time = idle_अन्तः - idle_begin;
            Uint64 usb_8khz_interval = SDL_US_गन्तव्यम्_NS(125);
            Uint64 poll_start = idle_time < usb_8khz_interval ? _this->आन्तरिकम्->चरमः_rawinput_poll : idle_अन्तः;

            WIN_Poll_Raw_निवेशः(_this, poll_start);

            // Reset idle_begin for the next go-around
            idle_begin = SDL_GetTicksNS();
        } भङ्ग;
        }
    }

    यदि (_this->आन्तरिकम्->raw_निवेशः_fake_pen_id) {
        SDL_RemovePenDevice(0, SDL_GetKeyboardFocus(), _this->आन्तरिकम्->raw_निवेशः_fake_pen_id);
        _this->आन्तरिकम्->raw_निवेशः_fake_pen_id = 0;
    }

    // Reset this here, since if we're exiting due to failure, WIN_UpdateRawInputEnabled would see a stale value.
    SDL_समुच्चयः_Atomic_U32(&thread_दत्त.flags, 0);

    Update_Raw_निवेशः_Device_Flags(रिक्त, चरमः_flags, 0);

    Destroy_गवाक्षः(गवाक्षः);

    प्रत्यागम 0;
}

स्थिर शून्य Cleanup_Raw_निवेशः_Thread_दत्त(शून्य)
{
    यदि (thread_दत्त.thread) {
        thread_दत्त.समाप्तम् = true;
        समुच्चयः_Event(thread_दत्त.signal_event);
        WaitForSingleObject(thread_दत्त.thread, 3000);
        CloseHandle(thread_दत्त.thread);
    }

    यदि (thread_दत्त.ready_event) {
        CloseHandle(thread_दत्त.ready_event);
    }

    यदि (thread_दत्त.signal_event) {
        CloseHandle(thread_दत्त.signal_event);
    }

    thread_दत्त = (Raw_निवेशः_Thread_दत्त){ 0 };
}

// Computes the desired raw input flags from SDL_VideoData and ensures the
// raw input thread's device registrations match.
// Creates the thread on first use, only WIN_QuitRawInput actually shuts it down.
स्थिर bool WIN_Update_Raw_निवेशः_Enabled(SDL_VideoDevice *_this)
{
    bool परिणाम = false;
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;
    Uint32 desired_flags = 0;

    यदि (!दत्त->gameinput_context) {
        यदि (दत्त->raw_mouse_enabled) {
            desired_flags |= ENABLE_RAW_MOUSE_निवेशः;
            यदि (दत्त->raw_mouse_flag_nolegacy) {
                desired_flags |= RAW_MOUSE_FLAG_NOLEGACY;
            }
        }
        यदि (दत्त->raw_keyboard_enabled) {
            desired_flags |= ENABLE_RAW_KEYBOARD_निवेशः;
            यदि (दत्त->raw_keyboard_flag_nohotkeys) {
                desired_flags |= RAW_KEYBOARD_FLAG_NOHOTKEYS;
            }
            यदि (दत्त->raw_keyboard_flag_inputsink) {
                desired_flags |= RAW_KEYBOARD_FLAG_INPUTSINK;
            }
        }
    }

    यदि (desired_flags == SDL_GetAtomicU32(&thread_दत्त.flags)) {
        परिणाम = true;
        गच्छ समाप्तम्;
    }

    // If the thread exited unexpectedly (e.g. MsgWaitForMultipleObjects failed),
    // the handle is stale. Clean it up so the creation path below can recover.
    यदि (thread_दत्त.thread && WaitForSingleObject(thread_दत्त.thread, 0) != WAIT_TIMEOUT) {
        Cleanup_Raw_निवेशः_Thread_दत्त();
    }

    // The thread will read from this to update its flags
    SDL_समुच्चयः_Atomic_U32(&thread_दत्त.flags, desired_flags);

    यदि (thread_दत्त.thread) {
        // Thread is already running. Fire (the event) and forget, it'll read the atomic flags on wakeup.

        // If RegisterRawInputDevices fails, the thread reverts the atomic and the next call
        // to this function will see the mismatch and retry.
        SDL_assert(thread_दत्त.signal_event);
        समुच्चयः_Event(thread_दत्त.signal_event);
        परिणाम = true;
    } अन्यथा यदि (desired_flags) {
        HANDLE wait_handles[2];

        // Thread isn't running, spin it up
        thread_दत्त.ready_event = CreateEvent(रिक्त, FALSE, FALSE, रिक्त);
        यदि (!thread_दत्त.ready_event) {
            WIN_समुच्चयः_Error("CreateEvent");
            गच्छ समाप्तम्;
        }

        thread_दत्त.समाप्तम् = false;
        thread_दत्त.signal_event = CreateEvent(रिक्त, FALSE, FALSE, रिक्त);
        यदि (!thread_दत्त.signal_event) {
            WIN_समुच्चयः_Error("CreateEvent");
            गच्छ समाप्तम्;
        }

        thread_दत्त.thread = CreateThread(रिक्त, 0, WIN_Raw_निवेशः_Thread, रिक्त, 0, रिक्त);
        यदि (!thread_दत्त.thread) {
            WIN_समुच्चयः_Error("CreateThread");
            गच्छ समाप्तम्;
        }

        // Wait for the thread to complete initial setup or exit
        wait_handles[0] = thread_दत्त.ready_event;
        wait_handles[1] = thread_दत्त.thread;
        यदि (Wait_For_गुणजः_Objects(2, wait_handles, FALSE, INFINITE) != WAIT_OBJECT_0) {
            SDL_समुच्चयः_Error("Couldn't set up raw input handling");
            गच्छ समाप्तम्;
        }
        परिणाम = true;
    } अन्यथा {
        // Thread isn't running and we tried to disable raw input, nothing to do
        परिणाम = true;
    }
समाप्तम्:
    यदि (!परिणाम) {
        Cleanup_Raw_निवेशः_Thread_दत्त();
    }
    प्रत्यागम परिणाम;
}

bool WIN_समुच्चयः_Raw_Mouse_Enabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;
    दत्त->raw_mouse_enabled = enabled;
    यदि (दत्त->gameinput_context) {
        यदि (!WIN_Update_Game_निवेशः_Enabled(_this)) {
            दत्त->raw_mouse_enabled = !enabled;
            प्रत्यागम false;
        }
    } अन्यथा {
        यदि (!WIN_Update_Raw_निवेशः_Enabled(_this)) {
            दत्त->raw_mouse_enabled = !enabled;
            प्रत्यागम false;
        }
    }
    प्रत्यागम true;
}

bool WIN_समुच्चयः_Raw_Mouse_Flag_No_Legacy(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;

    दत्त->raw_mouse_flag_nolegacy = enabled;

    प्रत्यागम WIN_Update_Raw_निवेशः_Enabled(_this);
}

bool WIN_समुच्चयः_Raw_Keyboard_Enabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;
    दत्त->raw_keyboard_enabled = enabled;
    यदि (दत्त->gameinput_context) {
        यदि (!WIN_Update_Game_निवेशः_Enabled(_this)) {
            दत्त->raw_keyboard_enabled = !enabled;
            प्रत्यागम false;
        }
    } अन्यथा {
        यदि (!WIN_Update_Raw_निवेशः_Enabled(_this)) {
            दत्त->raw_keyboard_enabled = !enabled;
            प्रत्यागम false;
        }
    }
    प्रत्यागम true;
}

bool WIN_समुच्चयः_Raw_Keyboard_Flag_No_Hotkeys(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;

    दत्त->raw_keyboard_flag_nohotkeys = enabled;

    प्रत्यागम WIN_Update_Raw_निवेशः_Enabled(_this);
}

bool WIN_समुच्चयः_Raw_Keyboard_Flag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_दत्त *दत्त = _this->आन्तरिकम्;

    दत्त->raw_keyboard_flag_inputsink = enabled;

    प्रत्यागम WIN_Update_Raw_निवेशः_Enabled(_this);
}

शून्य WIN_Quit_Raw_निवेशः(SDL_VideoDevice *_this)
{
    Cleanup_Raw_निवेशः_Thread_दत्त();
}

#अन्यथा

bool WIN_समुच्चयः_Raw_Mouse_Enabled(SDL_VideoDevice *_this, bool enabled)
{
    प्रत्यागम SDL_Unsupported();
}

bool WIN_समुच्चयः_Raw_Mouse_Flag_No_Legacy(SDL_VideoDevice *_this, bool enabled)
{
    प्रत्यागम SDL_Unsupported();
}

bool WIN_समुच्चयः_Raw_Keyboard_Enabled(SDL_VideoDevice *_this, bool enabled)
{
    प्रत्यागम SDL_Unsupported();
}

bool WIN_समुच्चयः_Raw_Keyboard_Flag_No_Hotkeys(SDL_VideoDevice *_this, bool enabled)
{
    प्रत्यागम SDL_Unsupported();
}

bool WIN_समुच्चयः_Raw_Keyboard_Flag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    प्रत्यागम SDL_Unsupported();
}

शून्य WIN_Quit_Raw_निवेशः(SDL_VideoDevice *_this)
{
}

#यदि_अन्तः // !SDL_PLATFORM_XBOXONE && !SDL_PLATFORM_XBOXSERIES

#यदि_अन्तः // SDL_VIDEO_DRIVER_WINDOWS

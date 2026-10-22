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
#समावेश "SDL_internal.h"

#अगर defined(SDL_VIDEO_DRIVER_WINDOWS)

#समावेश "SDL_windowsvideo.h"

#अगर !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#समावेश "SDL_windowsevents.h"

#समावेश "../../joystick/usb_ids.h"
#समावेश "../../events/SDL_events_c.h"
#समावेश "../../thread/SDL_systhread.h"

#घोषणा ENABLE_RAW_MOUSE_निवेश      0x01
#घोषणा RAW_MOUSE_FLAG_NOLEGACY     0x02
#घोषणा ENABLE_RAW_KEYBOARD_निवेश   0x10
#घोषणा RAW_KEYBOARD_FLAG_NOHOTKEYS 0x20
#घोषणा RAW_KEYBOARD_FLAG_INPUTSINK 0x40

प्रकार काष्ठा
{
    bool done;
    SDL_AtomicU32 flags; // Thread sets this to the actually-set flags if updating state failed
    HANDLE ready_event;
    HANDLE signal_event;
    HANDLE thread;
} Raw_निवेश_Thread_तथ्य;

अटल Raw_निवेश_Thread_तथ्य thread_तथ्य = { 0 };

प्रकार क्रमागत
{
    RINP_QUIT,
    RINP_UPDATE,
    RINP_CONTINUE
} Raw_निवेश_Iterate_परिणाम;

अटल Raw_निवेश_Iterate_परिणाम Iterate_Raw_निवेश_Thread(व्योम)
{
    // The high-order word of GetQueueStatus() will let us know if there's immediate raw input to be processed.
    // A (necessary!) side effect is that it also marks the message queue bits as stale,
    // so MsgWaitForMultipleObjects will block.

    // Any pending flag update won't be processed until the queue drains, but this is
    // at most one poll cycle since GetQueueStatus clears the wake bits.
    अगर (HIWORD(GetQueueStatus(QS_RAWINPUT)) & QS_RAWINPUT) {
        वापस thread_तथ्य.done ? RINP_QUIT : RINP_CONTINUE;
    }

    अटल स्थिर DWORD WAIT_SIGNAL = WAIT_OBJECT_0;
    अटल स्थिर DWORD WAIT_निवेश = WAIT_OBJECT_0 + 1;

    // There wasn't anything, so we'll wait until new data (or signal_event) wakes us up.
    DWORD wait_status = संदेश_Wait_For_Multiple_Objects(1, &thread_तथ्य.signal_event, FALSE, INFINITE, QS_RAWINPUT);
    अगर (wait_status == WAIT_SIGNAL) {
        // signal_event can only be set if we need to update or quit.
        वापस thread_तथ्य.done ? RINP_QUIT : RINP_UPDATE;
    } अन्यथा अगर (wait_status == WAIT_निवेश) {
        वापस RINP_CONTINUE;
    } अन्यथा {
        SDL_LogWarn(SDL_LOG_CATEGORY_निवेश, "Raw input thread exiting, unexpected wait result: %" SDL_PRIuULONG, wait_status);
        वापस RINP_QUIT;
    }
}

अटल bool Update_Raw_निवेश_Device_Flags(HWND window, Uint32 last_flags, Uint32 new_flags)
{
    // We had nothing enabled, and we're trying to stop everything. Nothing to do.
    अगर (last_flags == new_flags) {
        वापस true;
    }

    RAWINPUTDEVICE devices[2] = { 0 };
    UINT गिनती = 0;

    स्थिर Uint32 old_mouse_flags = last_flags & (ENABLE_RAW_MOUSE_निवेश | RAW_MOUSE_FLAG_NOLEGACY);
    स्थिर Uint32 new_mouse_flags = new_flags & (ENABLE_RAW_MOUSE_निवेश | RAW_MOUSE_FLAG_NOLEGACY);

    अगर (old_mouse_flags != new_mouse_flags) {
        devices[गिनती].usUsagePage = USB_USAGEPAGE_GENERIC_DESKTOP;
        devices[गिनती].usUsage = USB_USAGE_GENERIC_MOUSE;

        अगर (new_flags & ENABLE_RAW_MOUSE_निवेश) {
            devices[गिनती].dwFlags = 0;
            devices[गिनती].hwndTarget = window;
            अगर (new_mouse_flags & RAW_MOUSE_FLAG_NOLEGACY) {
                devices[गिनती].dwFlags |= RIDEV_NOLEGACY;
            }
        } अन्यथा {
            devices[गिनती].dwFlags = RIDEV_REMOVE;
            devices[गिनती].hwndTarget = शून्य;
        }

        ++गिनती;
    }

    स्थिर Uint32 old_kb_flags = last_flags & (ENABLE_RAW_KEYBOARD_निवेश | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);
    स्थिर Uint32 new_kb_flags = new_flags & (ENABLE_RAW_KEYBOARD_निवेश | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);

    अगर (old_kb_flags != new_kb_flags) {
        devices[गिनती].usUsagePage = USB_USAGEPAGE_GENERIC_DESKTOP;
        devices[गिनती].usUsage = USB_USAGE_GENERIC_KEYBOARD;

        अगर (new_kb_flags & ENABLE_RAW_KEYBOARD_निवेश) {
            devices[गिनती].dwFlags = 0;
            devices[गिनती].hwndTarget = window;
            अगर (new_kb_flags & RAW_KEYBOARD_FLAG_NOHOTKEYS) {
                devices[गिनती].dwFlags |= RIDEV_NOHOTKEYS;
            }
            अगर (new_kb_flags & RAW_KEYBOARD_FLAG_INPUTSINK) {
                devices[गिनती].dwFlags |= RIDEV_INPUTSINK;
            }
        } अन्यथा {
            devices[गिनती].dwFlags = RIDEV_REMOVE;
            devices[गिनती].hwndTarget = शून्य;
        }

        ++गिनती;
    }

    अगर (Register_Raw_निवेश_Devices(devices, गिनती, माप(devices[0]))) {
        वापस true;
    }
    वापस false;
}

अटल DWORD WINAPI WIN_Raw_निवेश_Thread(LPVOID param)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    Uint32 last_flags = 0;
    HWND window;

    SDL_SYS_SetupThread("SDLRawInput");

    window = CreateWindowEx(0, TEXT("Message"), शून्य, 0, 0, 0, 0, 0, HWND_MESSAGE, शून्य, शून्य, शून्य);
    अगर (!window) {
        वापस 0;
    }

    // This doesn't *really* need to be atomic, because the parent is waiting for us
    last_flags = SDL_GetAtomicU32(&thread_तथ्य.flags);
    अगर (!Update_Raw_निवेश_Device_Flags(window, 0, last_flags)) {
        DestroyWindow(window);
        वापस 0;
    }

    // Make sure we get events as soon as possible
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);

    // Tell the parent we're ready to go!
    SetEvent(thread_तथ्य.ready_event);

    Raw_निवेश_Iterate_परिणाम iter_परिणाम;

    Uint64 idle_begin = SDL_GetTicksNS();
    जबतक ((iter_परिणाम = Iterate_Raw_निवेश_Thread()) != RINP_QUIT) {
        चयन (iter_परिणाम) {
        हाल RINP_QUIT: // Unreachable
            अवरोध;
        हाल RINP_UPDATE:
        {
            स्थिर Uint32 new_flags = SDL_GetAtomicU32(&thread_तथ्य.flags);
            अगर (!Update_Raw_निवेश_Device_Flags(window, last_flags, new_flags)) {
                // Revert the shared flags so the main thread can detect the failure
                SDL_SetAtomicU32(&thread_तथ्य.flags, last_flags);
            } अन्यथा {
                last_flags = new_flags;
            }
        } अवरोध;
        हाल RINP_CONTINUE:
        {
            Uint64 idle_end = SDL_GetTicksNS();
            Uint64 idle_time = idle_end - idle_begin;
            Uint64 usb_8khz_interval = SDL_US_TO_NS(125);
            Uint64 poll_start = idle_time < usb_8khz_interval ? _this->internal->last_rawinput_poll : idle_end;

            WIN_Poll_Raw_निवेश(_this, poll_start);

            // Reset idle_begin for the next go-around
            idle_begin = SDL_GetTicksNS();
        } अवरोध;
        }
    }

    अगर (_this->internal->raw_निवेश_fake_pen_id) {
        SDL_RemovePenDevice(0, SDL_GetKeyboardFocus(), _this->internal->raw_निवेश_fake_pen_id);
        _this->internal->raw_निवेश_fake_pen_id = 0;
    }

    // Reset this here, since if we're exiting due to failure, WIN_UpdateRawInputEnabled would see a stale value.
    SDL_SetAtomicU32(&thread_तथ्य.flags, 0);

    Update_Raw_निवेश_Device_Flags(शून्य, last_flags, 0);

    DestroyWindow(window);

    वापस 0;
}

अटल व्योम Cleanup_Raw_निवेश_Thread_तथ्य(व्योम)
{
    अगर (thread_तथ्य.thread) {
        thread_तथ्य.done = true;
        SetEvent(thread_तथ्य.signal_event);
        WaitForSingleObject(thread_तथ्य.thread, 3000);
        CloseHandle(thread_तथ्य.thread);
    }

    अगर (thread_तथ्य.ready_event) {
        CloseHandle(thread_तथ्य.ready_event);
    }

    अगर (thread_तथ्य.signal_event) {
        CloseHandle(thread_तथ्य.signal_event);
    }

    thread_तथ्य = (Raw_निवेश_Thread_तथ्य){ 0 };
}

// Computes the desired raw input flags from SDL_VideoData and ensures the
// raw input thread's device registrations match.
// Creates the thread on first use, only WIN_QuitRawInput actually shuts it down.
अटल bool WIN_Update_Raw_निवेश_Enabled(SDL_VideoDevice *_this)
{
    bool परिणाम = false;
    SDL_Video_तथ्य *तथ्य = _this->internal;
    Uint32 desired_flags = 0;

    अगर (!तथ्य->gameinput_context) {
        अगर (तथ्य->raw_mouse_enabled) {
            desired_flags |= ENABLE_RAW_MOUSE_निवेश;
            अगर (तथ्य->raw_mouse_flag_nolegacy) {
                desired_flags |= RAW_MOUSE_FLAG_NOLEGACY;
            }
        }
        अगर (तथ्य->raw_keyboard_enabled) {
            desired_flags |= ENABLE_RAW_KEYBOARD_निवेश;
            अगर (तथ्य->raw_keyboard_flag_nohotkeys) {
                desired_flags |= RAW_KEYBOARD_FLAG_NOHOTKEYS;
            }
            अगर (तथ्य->raw_keyboard_flag_inputsink) {
                desired_flags |= RAW_KEYBOARD_FLAG_INPUTSINK;
            }
        }
    }

    अगर (desired_flags == SDL_GetAtomicU32(&thread_तथ्य.flags)) {
        परिणाम = true;
        जाओ done;
    }

    // If the thread exited unexpectedly (e.g. MsgWaitForMultipleObjects failed),
    // the handle is stale. Clean it up so the creation path below can recover.
    अगर (thread_तथ्य.thread && WaitForSingleObject(thread_तथ्य.thread, 0) != WAIT_TIMEOUT) {
        Cleanup_Raw_निवेश_Thread_तथ्य();
    }

    // The thread will read from this to update its flags
    SDL_SetAtomicU32(&thread_तथ्य.flags, desired_flags);

    अगर (thread_तथ्य.thread) {
        // Thread is already running. Fire (the event) and forget, it'll read the atomic flags on wakeup.

        // If RegisterRawInputDevices fails, the thread reverts the atomic and the next call
        // to this function will see the mismatch and retry.
        SDL_assert(thread_तथ्य.signal_event);
        SetEvent(thread_तथ्य.signal_event);
        परिणाम = true;
    } अन्यथा अगर (desired_flags) {
        HANDLE wait_handles[2];

        // Thread isn't running, spin it up
        thread_तथ्य.ready_event = CreateEvent(शून्य, FALSE, FALSE, शून्य);
        अगर (!thread_तथ्य.ready_event) {
            WIN_SetError("CreateEvent");
            जाओ done;
        }

        thread_तथ्य.done = false;
        thread_तथ्य.signal_event = CreateEvent(शून्य, FALSE, FALSE, शून्य);
        अगर (!thread_तथ्य.signal_event) {
            WIN_SetError("CreateEvent");
            जाओ done;
        }

        thread_तथ्य.thread = CreateThread(शून्य, 0, WIN_Raw_निवेश_Thread, शून्य, 0, शून्य);
        अगर (!thread_तथ्य.thread) {
            WIN_SetError("CreateThread");
            जाओ done;
        }

        // Wait for the thread to complete initial setup or exit
        wait_handles[0] = thread_तथ्य.ready_event;
        wait_handles[1] = thread_तथ्य.thread;
        अगर (WaitForMultipleObjects(2, wait_handles, FALSE, INFINITE) != WAIT_OBJECT_0) {
            SDL_SetError("Couldn't set up raw input handling");
            जाओ done;
        }
        परिणाम = true;
    } अन्यथा {
        // Thread isn't running and we tried to disable raw input, nothing to do
        परिणाम = true;
    }
done:
    अगर (!परिणाम) {
        Cleanup_Raw_निवेश_Thread_तथ्य();
    }
    वापस परिणाम;
}

bool WIN_SetRawMouseEnabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_तथ्य *तथ्य = _this->internal;
    तथ्य->raw_mouse_enabled = enabled;
    अगर (तथ्य->gameinput_context) {
        अगर (!WIN_Update_Game_निवेश_Enabled(_this)) {
            तथ्य->raw_mouse_enabled = !enabled;
            वापस false;
        }
    } अन्यथा {
        अगर (!WIN_Update_Raw_निवेश_Enabled(_this)) {
            तथ्य->raw_mouse_enabled = !enabled;
            वापस false;
        }
    }
    वापस true;
}

bool WIN_SetRawMouseFlag_NoLegacy(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_तथ्य *तथ्य = _this->internal;

    तथ्य->raw_mouse_flag_nolegacy = enabled;

    वापस WIN_Update_Raw_निवेश_Enabled(_this);
}

bool WIN_SetRawKeyboardEnabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_तथ्य *तथ्य = _this->internal;
    तथ्य->raw_keyboard_enabled = enabled;
    अगर (तथ्य->gameinput_context) {
        अगर (!WIN_Update_Game_निवेश_Enabled(_this)) {
            तथ्य->raw_keyboard_enabled = !enabled;
            वापस false;
        }
    } अन्यथा {
        अगर (!WIN_Update_Raw_निवेश_Enabled(_this)) {
            तथ्य->raw_keyboard_enabled = !enabled;
            वापस false;
        }
    }
    वापस true;
}

bool WIN_SetRawKeyboardFlag_NoHotkeys(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_तथ्य *तथ्य = _this->internal;

    तथ्य->raw_keyboard_flag_nohotkeys = enabled;

    वापस WIN_Update_Raw_निवेश_Enabled(_this);
}

bool WIN_SetRawKeyboardFlag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_तथ्य *तथ्य = _this->internal;

    तथ्य->raw_keyboard_flag_inputsink = enabled;

    वापस WIN_Update_Raw_निवेश_Enabled(_this);
}

व्योम WIN_Quit_Raw_निवेश(SDL_VideoDevice *_this)
{
    Cleanup_Raw_निवेश_Thread_तथ्य();
}

#अन्यथा

bool WIN_SetRawMouseEnabled(SDL_VideoDevice *_this, bool enabled)
{
    वापस SDL_Unsupported();
}

bool WIN_SetRawMouseFlag_NoLegacy(SDL_VideoDevice *_this, bool enabled)
{
    वापस SDL_Unsupported();
}

bool WIN_SetRawKeyboardEnabled(SDL_VideoDevice *_this, bool enabled)
{
    वापस SDL_Unsupported();
}

bool WIN_SetRawKeyboardFlag_NoHotkeys(SDL_VideoDevice *_this, bool enabled)
{
    वापस SDL_Unsupported();
}

bool WIN_SetRawKeyboardFlag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    वापस SDL_Unsupported();
}

व्योम WIN_Quit_Raw_निवेश(SDL_VideoDevice *_this)
{
}

#पूर्ण_अगर // !SDL_PLATFORM_XBOXONE && !SDL_PLATFORM_XBOXSERIES

#पूर्ण_अगर // SDL_VIDEO_DRIVER_WINDOWS

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
#అన్తర్భావ "SDL_internal.h"

#ఒకవేళ defined(SDL_VIDEO_DRIVER_WINDOWS)

#అన్తర్భావ "SDL_windowsvideo.h"

#ఒకవేళ !defined(SDL_PLATFORM_XBOXONE) && !defined(SDL_PLATFORM_XBOXSERIES)

#అన్తర్భావ "SDL_windowsevents.h"

#అన్తర్భావ "../../joystick/usb_ids.h"
#అన్తర్భావ "../../events/SDL_events_c.h"
#అన్తర్భావ "../../thread/SDL_systhread.h"

#నిర్వచించు ENABLE_RAW_MOUSE_ఆదానం      0x01
#నిర్వచించు RAW_MOUSE_FLAG_NOLEGACY     0x02
#నిర్వచించు ENABLE_RAW_KEYBOARD_ఆదానం   0x10
#నిర్వచించు RAW_KEYBOARD_FLAG_NOHOTKEYS 0x20
#నిర్వచించు RAW_KEYBOARD_FLAG_INPUTSINK 0x40

రకనిర్వచనం నిర్మాణం
{
    bool పూర్తి;
    SDL_AtomicU32 flags; // Thread sets this to the actually-set flags if updating state failed
    HANDLE ready_event;
    HANDLE signal_event;
    HANDLE thread;
} Raw_ఆదానం_Thread_దత్తాంశం;

స్థిర Raw_ఆదానం_Thread_దత్తాంశం thread_దత్తాంశం = { 0 };

రకనిర్వచనం గణన
{
    RINP_QUIT,
    RINP_UPDATE,
    RINP_CONTINUE
} Raw_ఆదానం_Iterate_ఫలితం;

స్థిర Raw_ఆదానం_Iterate_ఫలితం Iterate_Raw_ఆదానం_Thread(శూన్య)
{
    // The high-order word of GetQueueStatus() will let us know if there's immediate raw input to be processed.
    // A (necessary!) side effect is that it also marks the message queue bits as stale,
    // so MsgWaitForMultipleObjects will block.

    // Any pending flag update won't be processed until the queue drains, but this is
    // at most one poll cycle since GetQueueStatus clears the wake bits.
    ఒకవేళ (HIWORD(Get_వరుస_స్థితి(QS_RAWINPUT)) & QS_RAWINPUT) {
        తిరిగి thread_దత్తాంశం.పూర్తి ? RINP_QUIT : RINP_CONTINUE;
    }

    స్థిర స్థిరరాశి DWORD WAIT_SIGNAL = WAIT_OBJECT_0;
    స్థిర స్థిరరాశి DWORD WAIT_ఆదానం = WAIT_OBJECT_0 + 1;

    // There wasn't anything, so we'll wait until new data (or signal_event) wakes us up.
    DWORD wait_స్థితి = సందేశం_Wait_For_గుణిజం_Objects(1, &thread_దత్తాంశం.signal_event, FALSE, INFINITE, QS_RAWINPUT);
    ఒకవేళ (wait_స్థితి == WAIT_SIGNAL) {
        // signal_event can only be set if we need to update or quit.
        తిరిగి thread_దత్తాంశం.పూర్తి ? RINP_QUIT : RINP_UPDATE;
    } లేకపోతే ఒకవేళ (wait_స్థితి == WAIT_ఆదానం) {
        తిరిగి RINP_CONTINUE;
    } లేకపోతే {
        SDL_LogWarn(SDL_LOG_CATEGORY_ఆదానం, "Raw input thread exiting, unexpected wait result: %" SDL_PRIuULONG, wait_స్థితి);
        తిరిగి RINP_QUIT;
    }
}

స్థిర bool Update_Raw_ఆదానం_Device_Flags(HWND కిటికీ, Uint32 చివరి_flags, Uint32 new_flags)
{
    // We had nothing enabled, and we're trying to stop everything. Nothing to do.
    ఒకవేళ (చివరి_flags == new_flags) {
        తిరిగి true;
    }

    RAWINPUTDEVICE devices[2] = { 0 };
    UINT లెక్క = 0;

    స్థిరరాశి Uint32 old_mouse_flags = చివరి_flags & (ENABLE_RAW_MOUSE_ఆదానం | RAW_MOUSE_FLAG_NOLEGACY);
    స్థిరరాశి Uint32 new_mouse_flags = new_flags & (ENABLE_RAW_MOUSE_ఆదానం | RAW_MOUSE_FLAG_NOLEGACY);

    ఒకవేళ (old_mouse_flags != new_mouse_flags) {
        devices[లెక్క].us_Usage_పుట = USB_USAGEPAGE_GENERIC_DESKTOP;
        devices[లెక్క].usUsage = USB_USAGE_GENERIC_MOUSE;

        ఒకవేళ (new_flags & ENABLE_RAW_MOUSE_ఆదానం) {
            devices[లెక్క].dwFlags = 0;
            devices[లెక్క].hwnd_లక్ష్యం = కిటికీ;
            ఒకవేళ (new_mouse_flags & RAW_MOUSE_FLAG_NOLEGACY) {
                devices[లెక్క].dwFlags |= RIDEV_NOLEGACY;
            }
        } లేకపోతే {
            devices[లెక్క].dwFlags = RIDEV_REMOVE;
            devices[లెక్క].hwnd_లక్ష్యం = ఖాళీ;
        }

        ++లెక్క;
    }

    స్థిరరాశి Uint32 old_kb_flags = చివరి_flags & (ENABLE_RAW_KEYBOARD_ఆదానం | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);
    స్థిరరాశి Uint32 new_kb_flags = new_flags & (ENABLE_RAW_KEYBOARD_ఆదానం | RAW_KEYBOARD_FLAG_NOHOTKEYS | RAW_KEYBOARD_FLAG_INPUTSINK);

    ఒకవేళ (old_kb_flags != new_kb_flags) {
        devices[లెక్క].us_Usage_పుట = USB_USAGEPAGE_GENERIC_DESKTOP;
        devices[లెక్క].usUsage = USB_USAGE_GENERIC_KEYBOARD;

        ఒకవేళ (new_kb_flags & ENABLE_RAW_KEYBOARD_ఆదానం) {
            devices[లెక్క].dwFlags = 0;
            devices[లెక్క].hwnd_లక్ష్యం = కిటికీ;
            ఒకవేళ (new_kb_flags & RAW_KEYBOARD_FLAG_NOHOTKEYS) {
                devices[లెక్క].dwFlags |= RIDEV_NOHOTKEYS;
            }
            ఒకవేళ (new_kb_flags & RAW_KEYBOARD_FLAG_INPUTSINK) {
                devices[లెక్క].dwFlags |= RIDEV_INPUTSINK;
            }
        } లేకపోతే {
            devices[లెక్క].dwFlags = RIDEV_REMOVE;
            devices[లెక్క].hwnd_లక్ష్యం = ఖాళీ;
        }

        ++లెక్క;
    }

    ఒకవేళ (రిజిస్టరు_Raw_ఆదానం_Devices(devices, లెక్క, పరిమాణం(devices[0]))) {
        తిరిగి true;
    }
    తిరిగి false;
}

స్థిర DWORD WINAPI WIN_Raw_ఆదానం_Thread(LPVOID param)
{
    SDL_VideoDevice *_this = SDL_GetVideoDevice();
    Uint32 చివరి_flags = 0;
    HWND కిటికీ;

    SDL_SYS_అమరిక_Thread("SDLRawInput");

    కిటికీ = Create_కిటికీ_Ex(0, పాఠ్యం_2("Message"), ఖాళీ, 0, 0, 0, 0, 0, HWND_సందేశం, ఖాళీ, ఖాళీ, ఖాళీ);
    ఒకవేళ (!కిటికీ) {
        తిరిగి 0;
    }

    // This doesn't *really* need to be atomic, because the parent is waiting for us
    చివరి_flags = SDL_GetAtomicU32(&thread_దత్తాంశం.flags);
    ఒకవేళ (!Update_Raw_ఆదానం_Device_Flags(కిటికీ, 0, చివరి_flags)) {
        Destroy_కిటికీ(కిటికీ);
        తిరిగి 0;
    }

    // Make sure we get events as soon as possible
    సమితి_Thread_ప్రాధాన్యత(GetCurrentThread(), THREAD_ప్రాధాన్యత_సమయం_CRITICAL);

    // Tell the parent we're ready to go!
    సమితి_Event(thread_దత్తాంశం.ready_event);

    Raw_ఆదానం_Iterate_ఫలితం iter_ఫలితం;

    Uint64 idle_begin = SDL_GetTicksNS();
    అయితే ((iter_ఫలితం = Iterate_Raw_ఆదానం_Thread()) != RINP_QUIT) {
        ఎంపిక (iter_ఫలితం) {
        స్థితి RINP_QUIT: // Unreachable
            ఆపు;
        స్థితి RINP_UPDATE:
        {
            స్థిరరాశి Uint32 new_flags = SDL_GetAtomicU32(&thread_దత్తాంశం.flags);
            ఒకవేళ (!Update_Raw_ఆదానం_Device_Flags(కిటికీ, చివరి_flags, new_flags)) {
                // Revert the shared flags so the main thread can detect the failure
                SDL_సమితి_Atomic_U32(&thread_దత్తాంశం.flags, చివరి_flags);
            } లేకపోతే {
                చివరి_flags = new_flags;
            }
        } ఆపు;
        స్థితి RINP_CONTINUE:
        {
            Uint64 idle_చివర = SDL_GetTicksNS();
            Uint64 idle_సమయం = idle_చివర - idle_begin;
            Uint64 usb_8khz_interval = SDL_US_గమ్యం_NS(125);
            Uint64 poll_ప్రారంభం = idle_సమయం < usb_8khz_interval ? _this->అంతర్గత->చివరి_rawinput_poll : idle_చివర;

            WIN_Poll_Raw_ఆదానం(_this, poll_ప్రారంభం);

            // Reset idle_begin for the next go-around
            idle_begin = SDL_GetTicksNS();
        } ఆపు;
        }
    }

    ఒకవేళ (_this->అంతర్గత->raw_ఆదానం_fake_pen_id) {
        SDL_RemovePenDevice(0, SDL_GetKeyboardFocus(), _this->అంతర్గత->raw_ఆదానం_fake_pen_id);
        _this->అంతర్గత->raw_ఆదానం_fake_pen_id = 0;
    }

    // Reset this here, since if we're exiting due to failure, WIN_UpdateRawInputEnabled would see a stale value.
    SDL_సమితి_Atomic_U32(&thread_దత్తాంశం.flags, 0);

    Update_Raw_ఆదానం_Device_Flags(ఖాళీ, చివరి_flags, 0);

    Destroy_కిటికీ(కిటికీ);

    తిరిగి 0;
}

స్థిర శూన్య Cleanup_Raw_ఆదానం_Thread_దత్తాంశం(శూన్య)
{
    ఒకవేళ (thread_దత్తాంశం.thread) {
        thread_దత్తాంశం.పూర్తి = true;
        సమితి_Event(thread_దత్తాంశం.signal_event);
        WaitForSingleObject(thread_దత్తాంశం.thread, 3000);
        CloseHandle(thread_దత్తాంశం.thread);
    }

    ఒకవేళ (thread_దత్తాంశం.ready_event) {
        CloseHandle(thread_దత్తాంశం.ready_event);
    }

    ఒకవేళ (thread_దత్తాంశం.signal_event) {
        CloseHandle(thread_దత్తాంశం.signal_event);
    }

    thread_దత్తాంశం = (Raw_ఆదానం_Thread_దత్తాంశం){ 0 };
}

// Computes the desired raw input flags from SDL_VideoData and ensures the
// raw input thread's device registrations match.
// Creates the thread on first use, only WIN_QuitRawInput actually shuts it down.
స్థిర bool WIN_Update_Raw_ఆదానం_Enabled(SDL_VideoDevice *_this)
{
    bool ఫలితం = false;
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    Uint32 desired_flags = 0;

    ఒకవేళ (!దత్తాంశం->gameinput_context) {
        ఒకవేళ (దత్తాంశం->raw_mouse_enabled) {
            desired_flags |= ENABLE_RAW_MOUSE_ఆదానం;
            ఒకవేళ (దత్తాంశం->raw_mouse_flag_nolegacy) {
                desired_flags |= RAW_MOUSE_FLAG_NOLEGACY;
            }
        }
        ఒకవేళ (దత్తాంశం->raw_keyboard_enabled) {
            desired_flags |= ENABLE_RAW_KEYBOARD_ఆదానం;
            ఒకవేళ (దత్తాంశం->raw_keyboard_flag_nohotkeys) {
                desired_flags |= RAW_KEYBOARD_FLAG_NOHOTKEYS;
            }
            ఒకవేళ (దత్తాంశం->raw_keyboard_flag_inputsink) {
                desired_flags |= RAW_KEYBOARD_FLAG_INPUTSINK;
            }
        }
    }

    ఒకవేళ (desired_flags == SDL_GetAtomicU32(&thread_దత్తాంశం.flags)) {
        ఫలితం = true;
        వెళ్ళు పూర్తి;
    }

    // If the thread exited unexpectedly (e.g. MsgWaitForMultipleObjects failed),
    // the handle is stale. Clean it up so the creation path below can recover.
    ఒకవేళ (thread_దత్తాంశం.thread && WaitForSingleObject(thread_దత్తాంశం.thread, 0) != WAIT_TIMEOUT) {
        Cleanup_Raw_ఆదానం_Thread_దత్తాంశం();
    }

    // The thread will read from this to update its flags
    SDL_సమితి_Atomic_U32(&thread_దత్తాంశం.flags, desired_flags);

    ఒకవేళ (thread_దత్తాంశం.thread) {
        // Thread is already running. Fire (the event) and forget, it'll read the atomic flags on wakeup.

        // If RegisterRawInputDevices fails, the thread reverts the atomic and the next call
        // to this function will see the mismatch and retry.
        SDL_assert(thread_దత్తాంశం.signal_event);
        సమితి_Event(thread_దత్తాంశం.signal_event);
        ఫలితం = true;
    } లేకపోతే ఒకవేళ (desired_flags) {
        HANDLE wait_handles[2];

        // Thread isn't running, spin it up
        thread_దత్తాంశం.ready_event = CreateEvent(ఖాళీ, FALSE, FALSE, ఖాళీ);
        ఒకవేళ (!thread_దత్తాంశం.ready_event) {
            WIN_సమితి_Error("CreateEvent");
            వెళ్ళు పూర్తి;
        }

        thread_దత్తాంశం.పూర్తి = false;
        thread_దత్తాంశం.signal_event = CreateEvent(ఖాళీ, FALSE, FALSE, ఖాళీ);
        ఒకవేళ (!thread_దత్తాంశం.signal_event) {
            WIN_సమితి_Error("CreateEvent");
            వెళ్ళు పూర్తి;
        }

        thread_దత్తాంశం.thread = CreateThread(ఖాళీ, 0, WIN_Raw_ఆదానం_Thread, ఖాళీ, 0, ఖాళీ);
        ఒకవేళ (!thread_దత్తాంశం.thread) {
            WIN_సమితి_Error("CreateThread");
            వెళ్ళు పూర్తి;
        }

        // Wait for the thread to complete initial setup or exit
        wait_handles[0] = thread_దత్తాంశం.ready_event;
        wait_handles[1] = thread_దత్తాంశం.thread;
        ఒకవేళ (Wait_For_గుణిజం_Objects(2, wait_handles, FALSE, INFINITE) != WAIT_OBJECT_0) {
            SDL_సమితి_Error("Couldn't set up raw input handling");
            వెళ్ళు పూర్తి;
        }
        ఫలితం = true;
    } లేకపోతే {
        // Thread isn't running and we tried to disable raw input, nothing to do
        ఫలితం = true;
    }
పూర్తి:
    ఒకవేళ (!ఫలితం) {
        Cleanup_Raw_ఆదానం_Thread_దత్తాంశం();
    }
    తిరిగి ఫలితం;
}

bool WIN_సమితి_Raw_Mouse_Enabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    దత్తాంశం->raw_mouse_enabled = enabled;
    ఒకవేళ (దత్తాంశం->gameinput_context) {
        ఒకవేళ (!WIN_Update_Game_ఆదానం_Enabled(_this)) {
            దత్తాంశం->raw_mouse_enabled = !enabled;
            తిరిగి false;
        }
    } లేకపోతే {
        ఒకవేళ (!WIN_Update_Raw_ఆదానం_Enabled(_this)) {
            దత్తాంశం->raw_mouse_enabled = !enabled;
            తిరిగి false;
        }
    }
    తిరిగి true;
}

bool WIN_సమితి_Raw_Mouse_Flag_No_Legacy(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;

    దత్తాంశం->raw_mouse_flag_nolegacy = enabled;

    తిరిగి WIN_Update_Raw_ఆదానం_Enabled(_this);
}

bool WIN_సమితి_Raw_Keyboard_Enabled(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;
    దత్తాంశం->raw_keyboard_enabled = enabled;
    ఒకవేళ (దత్తాంశం->gameinput_context) {
        ఒకవేళ (!WIN_Update_Game_ఆదానం_Enabled(_this)) {
            దత్తాంశం->raw_keyboard_enabled = !enabled;
            తిరిగి false;
        }
    } లేకపోతే {
        ఒకవేళ (!WIN_Update_Raw_ఆదానం_Enabled(_this)) {
            దత్తాంశం->raw_keyboard_enabled = !enabled;
            తిరిగి false;
        }
    }
    తిరిగి true;
}

bool WIN_సమితి_Raw_Keyboard_Flag_No_Hotkeys(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;

    దత్తాంశం->raw_keyboard_flag_nohotkeys = enabled;

    తిరిగి WIN_Update_Raw_ఆదానం_Enabled(_this);
}

bool WIN_సమితి_Raw_Keyboard_Flag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    SDL_Video_దత్తాంశం *దత్తాంశం = _this->అంతర్గత;

    దత్తాంశం->raw_keyboard_flag_inputsink = enabled;

    తిరిగి WIN_Update_Raw_ఆదానం_Enabled(_this);
}

శూన్య WIN_Quit_Raw_ఆదానం(SDL_VideoDevice *_this)
{
    Cleanup_Raw_ఆదానం_Thread_దత్తాంశం();
}

#లేకపోతే

bool WIN_సమితి_Raw_Mouse_Enabled(SDL_VideoDevice *_this, bool enabled)
{
    తిరిగి SDL_Unsupported();
}

bool WIN_సమితి_Raw_Mouse_Flag_No_Legacy(SDL_VideoDevice *_this, bool enabled)
{
    తిరిగి SDL_Unsupported();
}

bool WIN_సమితి_Raw_Keyboard_Enabled(SDL_VideoDevice *_this, bool enabled)
{
    తిరిగి SDL_Unsupported();
}

bool WIN_సమితి_Raw_Keyboard_Flag_No_Hotkeys(SDL_VideoDevice *_this, bool enabled)
{
    తిరిగి SDL_Unsupported();
}

bool WIN_సమితి_Raw_Keyboard_Flag_Inputsink(SDL_VideoDevice *_this, bool enabled)
{
    తిరిగి SDL_Unsupported();
}

శూన్య WIN_Quit_Raw_ఆదానం(SDL_VideoDevice *_this)
{
}

#అయితే_ముగింపు // !SDL_PLATFORM_XBOXONE && !SDL_PLATFORM_XBOXSERIES

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_WINDOWS

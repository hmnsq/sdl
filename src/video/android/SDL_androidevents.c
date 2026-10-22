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
#অন্তর্ভাৱ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_ANDROID

#অন্তর্ভাৱ "SDL_androidevents.h"
#অন্তর্ভাৱ "SDL_androidkeyboard.h"
#অন্তর্ভাৱ "SDL_androidwindow.h"
#অন্তর্ভাৱ "../SDL_sysvideo.h"
#অন্তর্ভাৱ "../../events/SDL_events_c.h"

#অন্তর্ভাৱ "../../audio/aaudio/SDL_aaudio.h"
#অন্তর্ভাৱ "../../audio/openslES/SDL_openslES.h"


#ifdef SDL_VIDEO_OPENGL_EGL
স্থির শূন্য android_egl_context_restore(SDL_Window *window)
{
    যদি (window && (window->flags & SDL_WINDOW_OPENGL)) {
        SDL_WindowData *data = window->internal;
        SDL_GL_MakeCurrent(window, রিক্ত);
        যদি (!SDL_GL_MakeCurrent(window, (SDL_GLContext)data->egl_context)) {
            // The context is no longer valid, create a new one
            data->egl_context = (EGLContext)SDL_GL_CreateContext(window);
            SDL_GL_MakeCurrent(window, (SDL_GLContext)data->egl_context);
            SDL_Event event;
            SDL_zero(event);
            event.type = SDL_EVENT_RENDER_DEVICE_RESET;
            event.render.windowID = SDL_GetWindowID(window);
            SDL_ঠেলো_Event(&event);
        }
        data->backup_done = false;

        SDL_GL_SetSwapInterval(data->swap_interval);
    }
}

স্থির শূন্য android_egl_context_backup(SDL_Window *window)
{
    যদি (window && (window->flags & SDL_WINDOW_OPENGL)) {
        পূর্ণাঙ্ক interval = 0;
        // Keep a copy of the EGL Context so we can try to restore it when we resume
        SDL_WindowData *data = window->internal;
        data->egl_context = SDL_GL_GetCurrentContext();

        // Save/Restore the swap interval / vsync
        যদি (SDL_GL_GetSwapInterval(&interval)) {
            data->has_swap_interval = 1;
            data->swap_interval = interval;
        }

        // We need to do this so the EGLSurface can be freed
        SDL_GL_MakeCurrent(window, রিক্ত);
        data->backup_done = true;
    }
}
#endif

/*
 * Android_ResumeSem and Android_PauseSem are signaled from Java_org_libsdl_app_SDLActivity_nativePause and Java_org_libsdl_app_SDLActivity_nativeResume
 */
স্থির bool Android_EventsInitialized;
স্থির bool Android_BlockOnPause = true;
স্থির bool Android_Paused;
স্থির bool Android_PausedAudio;
স্থির bool Android_Destroyed;

শূন্য Android_InitEvents(শূন্য)
{
    যদি (!Android_EventsInitialized) {
        Android_BlockOnPause = SDL_GetHintBoolean(SDL_HINT_ANDROID_BLOCK_ON_PAUSE, true);
        Android_Paused = false;
        Android_Destroyed = false;
        Android_EventsInitialized = true;
    }
}

স্থির শূন্য Android_PauseAudio(শূন্য)
{
    OPENSLES_PauseDevices();
    AAUDIO_PauseDevices();
    Android_PausedAudio = true;
}

স্থির শূন্য Android_ResumeAudio(শূন্য)
{
    যদি (Android_PausedAudio) {
        OPENSLES_ResumeDevices();
        AAUDIO_ResumeDevices();
        Android_PausedAudio = false;
    }
}

স্থির শূন্য Android_OnPause(শূন্য)
{
    SDL_OnApplicationWillEnterBackground();
    SDL_OnApplicationDidEnterBackground();

    /* The semantics are that as soon as the enter background event
     * has been queued, the app will block. The application should
     * do any life cycle handling in an event filter while the event
     * was being queued.
     */
#ifdef SDL_VIDEO_OPENGL_EGL
    যদি (Android_Window && !Android_Window->external_graphics_context) {
        Android_LockActivityMutex();
        android_egl_context_backup(Android_Window);
        Android_UnlockActivityMutex();
    }
#endif

    যদি (Android_BlockOnPause) {
        // We're blocking, also pause audio
        Android_PauseAudio();
    }

    Android_Paused = true;
}

স্থির শূন্য Android_OnResume(শূন্য)
{
    Android_Paused = false;

    SDL_OnApplicationWillEnterForeground();

    Android_ResumeAudio();

#ifdef SDL_VIDEO_OPENGL_EGL
    // Restore the GL Context from here, as this operation is thread dependent
    যদি (Android_Window && !Android_Window->external_graphics_context && !SDL_HasEvent(SDL_EVENT_QUIT)) {
        Android_LockActivityMutex();
        android_egl_context_restore(Android_Window);
        Android_UnlockActivityMutex();
    }
#endif

    SDL_OnApplicationDidEnterForeground();
}

স্থির শূন্য Android_On_নিচেৰ_Memory(শূন্য)
{
    SDL_SendAppEvent(SDL_EVENT_নিচেৰ_MEMORY);
}

স্থির শূন্য Android_OnDestroy(শূন্য)
{
    // Make sure we unblock any audio processing before we quit
    Android_ResumeAudio();

    /* Discard previous events. The user should have handled state storage
     * in SDL_EVENT_WILL_ENTER_BACKGROUND. After nativeSendQuit() is called, no
     * events other than SDL_EVENT_QUIT and SDL_EVENT_TERMINATING should fire */
    SDL_FlushEvents(SDL_EVENT_FIRST, SDL_EVENT_LAST);
    SDL_SendQuit();
    SDL_OnApplicationWillTerminate();

    Android_Destroyed = true;
}

স্থির শূন্য Android_HandleLifecycleEvent(SDL_AndroidLifecycleEvent event)
{
    ৱিকল্প (event) {
    পক্ষ SDL_ANDROID_LIFECYCLE_WAKE:
        // Nothing to do, just return
        ভঙ্গ;
    পক্ষ SDL_ANDROID_LIFECYCLE_PAUSE:
        Android_OnPause();
        ভঙ্গ;
    পক্ষ SDL_ANDROID_LIFECYCLE_RESUME:
        Android_OnResume();
        ভঙ্গ;
    পক্ষ SDL_ANDROID_LIFECYCLE_LOWMEMORY:
        Android_On_নিচেৰ_Memory();
        ভঙ্গ;
    পক্ষ SDL_ANDROID_LIFECYCLE_DESTROY:
        Android_OnDestroy();
        ভঙ্গ;
    স্ৱভাৱ:
        ভঙ্গ;
    }
}

স্থির Sint64 GetLifecycleEventTimeout(bool paused, Sint64 timeoutNS)
{
    যদি (Android_Paused) {
        যদি (Android_BlockOnPause) {
            timeoutNS = -1;
        } অন্যথা যদি (timeoutNS == 0) {
            timeoutNS = SDL_MS_TO_NS(100);
        }
    }
    ঘূৰাই timeoutNS;
}

শূন্য Android_PumpEvents(Sint64 timeoutNS)
{
    SDL_AndroidLifecycleEvent event;
    bool paused = Android_Paused;

    যেতিয়ালৈ (!Android_Destroyed &&
           Android_WaitLifecycleEvent(&event, GetLifecycleEventTimeout(paused, timeoutNS))) {
        Android_HandleLifecycleEvent(event);

        ৱিকল্প (event) {
        পক্ষ SDL_ANDROID_LIFECYCLE_WAKE:
            // Finish handling events quickly if we're not paused
            timeoutNS = 0;
            ভঙ্গ;
        পক্ষ SDL_ANDROID_LIFECYCLE_PAUSE:
            // Finish handling events at the current timeout and return to process events one more time before blocking.
            ভঙ্গ;
        পক্ষ SDL_ANDROID_LIFECYCLE_RESUME:
            // Finish handling events at the resume state timeout
            paused = false;
            ভঙ্গ;
        স্ৱভাৱ:
            ভঙ্গ;
        }
    }
}

bool Android_WaitActiveAndLockActivity(শূন্য)
{
    /* Make sure we have pumped all events so that Android_Paused state is correct */
    SDL_AndroidLifecycleEvent event;
    যেতিয়ালৈ (!Android_Destroyed && Android_WaitLifecycleEvent(&event, 0)) {
        Android_HandleLifecycleEvent(event);
    }

    যেতিয়ালৈ (Android_Paused && !Android_Destroyed) {
        Android_PumpEvents(-1);
    }

    যদি (Android_Destroyed) {
        SDL_SetError("Android activity has been destroyed");
        ঘূৰাই false;
    }

    Android_LockActivityMutex();
    ঘূৰাই true;
}

শূন্য Android_QuitEvents(শূন্য)
{
    Android_EventsInitialized = false;
}

#অন্যথা

#অন্তর্ভাৱ "../../core/android/SDL_android.h"

শূন্য Android_InitEvents(শূন্য)
{
}

শূন্য Android_PumpEvents(Sint64 timeoutNS)
{
    (শূন্য)timeoutNS;
}

bool Android_WaitActiveAndLockActivity(শূন্য)
{
    Android_LockActivityMutex();
    ঘূৰাই true;
}

শূন্য Android_QuitEvents(শূন্য)
{
}

#endif // SDL_VIDEO_DRIVER_ANDROID

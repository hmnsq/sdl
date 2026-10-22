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
#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_ANDROID

#അന്തര്ഭാവ "SDL_androidevents.h"
#അന്തര്ഭാവ "SDL_androidkeyboard.h"
#അന്തര്ഭാവ "SDL_androidwindow.h"
#അന്തര്ഭാവ "../SDL_sysvideo.h"
#അന്തര്ഭാവ "../../events/SDL_events_c.h"

#അന്തര്ഭാവ "../../audio/aaudio/SDL_aaudio.h"
#അന്തര്ഭാവ "../../audio/openslES/SDL_openslES.h"


#ifdef SDL_VIDEO_OPENGL_EGL
സ്ഥിതം ശൂന്യം android_egl_context_restore(SDL_Window *window)
{
    എങ്കിൽ (window && (window->flags & SDL_WINDOW_OPENGL)) {
        SDL_WindowData *data = window->internal;
        SDL_GL_MakeCurrent(window, ശൂന്യ);
        എങ്കിൽ (!SDL_GL_MakeCurrent(window, (SDL_GLContext)data->egl_context)) {
            // The context is no longer valid, create a new one
            data->egl_context = (EGLContext)SDL_GL_CreateContext(window);
            SDL_GL_MakeCurrent(window, (SDL_GLContext)data->egl_context);
            SDL_Event event;
            SDL_zero(event);
            event.type = SDL_EVENT_RENDER_DEVICE_RESET;
            event.render.windowID = SDL_GetWindowID(window);
            SDL_തള്ളുക_Event(&event);
        }
        data->backup_done = false;

        SDL_GL_SetSwapInterval(data->swap_interval);
    }
}

സ്ഥിതം ശൂന്യം android_egl_context_backup(SDL_Window *window)
{
    എങ്കിൽ (window && (window->flags & SDL_WINDOW_OPENGL)) {
        പൂർണ്ണസംഖ്യ interval = 0;
        // Keep a copy of the EGL Context so we can try to restore it when we resume
        SDL_WindowData *data = window->internal;
        data->egl_context = SDL_GL_GetCurrentContext();

        // Save/Restore the swap interval / vsync
        എങ്കിൽ (SDL_GL_GetSwapInterval(&interval)) {
            data->has_swap_interval = 1;
            data->swap_interval = interval;
        }

        // We need to do this so the EGLSurface can be freed
        SDL_GL_MakeCurrent(window, ശൂന്യ);
        data->backup_done = true;
    }
}
#endif

/*
 * Android_ResumeSem and Android_PauseSem are signaled from Java_org_libsdl_app_SDLActivity_nativePause and Java_org_libsdl_app_SDLActivity_nativeResume
 */
സ്ഥിതം bool Android_EventsInitialized;
സ്ഥിതം bool Android_BlockOnPause = true;
സ്ഥിതം bool Android_Paused;
സ്ഥിതം bool Android_PausedAudio;
സ്ഥിതം bool Android_Destroyed;

ശൂന്യം Android_InitEvents(ശൂന്യം)
{
    എങ്കിൽ (!Android_EventsInitialized) {
        Android_BlockOnPause = SDL_GetHintBoolean(SDL_HINT_ANDROID_BLOCK_ON_PAUSE, true);
        Android_Paused = false;
        Android_Destroyed = false;
        Android_EventsInitialized = true;
    }
}

സ്ഥിതം ശൂന്യം Android_PauseAudio(ശൂന്യം)
{
    OPENSLES_PauseDevices();
    AAUDIO_PauseDevices();
    Android_PausedAudio = true;
}

സ്ഥിതം ശൂന്യം Android_ResumeAudio(ശൂന്യം)
{
    എങ്കിൽ (Android_PausedAudio) {
        OPENSLES_ResumeDevices();
        AAUDIO_ResumeDevices();
        Android_PausedAudio = false;
    }
}

സ്ഥിതം ശൂന്യം Android_OnPause(ശൂന്യം)
{
    SDL_OnApplicationWillEnterBackground();
    SDL_OnApplicationDidEnterBackground();

    /* The semantics are that as soon as the enter background event
     * has been queued, the app will block. The application should
     * do any life cycle handling in an event filter while the event
     * was being queued.
     */
#ifdef SDL_VIDEO_OPENGL_EGL
    എങ്കിൽ (Android_Window && !Android_Window->external_graphics_context) {
        Android_LockActivityMutex();
        android_egl_context_backup(Android_Window);
        Android_UnlockActivityMutex();
    }
#endif

    എങ്കിൽ (Android_BlockOnPause) {
        // We're blocking, also pause audio
        Android_PauseAudio();
    }

    Android_Paused = true;
}

സ്ഥിതം ശൂന്യം Android_OnResume(ശൂന്യം)
{
    Android_Paused = false;

    SDL_OnApplicationWillEnterForeground();

    Android_ResumeAudio();

#ifdef SDL_VIDEO_OPENGL_EGL
    // Restore the GL Context from here, as this operation is thread dependent
    എങ്കിൽ (Android_Window && !Android_Window->external_graphics_context && !SDL_HasEvent(SDL_EVENT_QUIT)) {
        Android_LockActivityMutex();
        android_egl_context_restore(Android_Window);
        Android_UnlockActivityMutex();
    }
#endif

    SDL_OnApplicationDidEnterForeground();
}

സ്ഥിതം ശൂന്യം Android_On_താഴെയുള്ള_Memory(ശൂന്യം)
{
    SDL_SendAppEvent(SDL_EVENT_താഴെയുള്ള_MEMORY);
}

സ്ഥിതം ശൂന്യം Android_OnDestroy(ശൂന്യം)
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

സ്ഥിതം ശൂന്യം Android_HandleLifecycleEvent(SDL_AndroidLifecycleEvent event)
{
    തിരഞ്ഞെടുപ്പ് (event) {
    അവസ്ഥ SDL_ANDROID_LIFECYCLE_WAKE:
        // Nothing to do, just return
        നിർത്തുക;
    അവസ്ഥ SDL_ANDROID_LIFECYCLE_PAUSE:
        Android_OnPause();
        നിർത്തുക;
    അവസ്ഥ SDL_ANDROID_LIFECYCLE_RESUME:
        Android_OnResume();
        നിർത്തുക;
    അവസ്ഥ SDL_ANDROID_LIFECYCLE_LOWMEMORY:
        Android_On_താഴെയുള്ള_Memory();
        നിർത്തുക;
    അവസ്ഥ SDL_ANDROID_LIFECYCLE_DESTROY:
        Android_OnDestroy();
        നിർത്തുക;
    സ്ഥിരസ്ഥിതി:
        നിർത്തുക;
    }
}

സ്ഥിതം Sint64 GetLifecycleEventTimeout(bool paused, Sint64 timeoutNS)
{
    എങ്കിൽ (Android_Paused) {
        എങ്കിൽ (Android_BlockOnPause) {
            timeoutNS = -1;
        } അല്ലെങ്കിൽ എങ്കിൽ (timeoutNS == 0) {
            timeoutNS = SDL_MS_TO_NS(100);
        }
    }
    തിരികെ timeoutNS;
}

ശൂന്യം Android_PumpEvents(Sint64 timeoutNS)
{
    SDL_AndroidLifecycleEvent event;
    bool paused = Android_Paused;

    ആകുമ്പോൾ (!Android_Destroyed &&
           Android_WaitLifecycleEvent(&event, GetLifecycleEventTimeout(paused, timeoutNS))) {
        Android_HandleLifecycleEvent(event);

        തിരഞ്ഞെടുപ്പ് (event) {
        അവസ്ഥ SDL_ANDROID_LIFECYCLE_WAKE:
            // Finish handling events quickly if we're not paused
            timeoutNS = 0;
            നിർത്തുക;
        അവസ്ഥ SDL_ANDROID_LIFECYCLE_PAUSE:
            // Finish handling events at the current timeout and return to process events one more time before blocking.
            നിർത്തുക;
        അവസ്ഥ SDL_ANDROID_LIFECYCLE_RESUME:
            // Finish handling events at the resume state timeout
            paused = false;
            നിർത്തുക;
        സ്ഥിരസ്ഥിതി:
            നിർത്തുക;
        }
    }
}

bool Android_WaitActiveAndLockActivity(ശൂന്യം)
{
    /* Make sure we have pumped all events so that Android_Paused state is correct */
    SDL_AndroidLifecycleEvent event;
    ആകുമ്പോൾ (!Android_Destroyed && Android_WaitLifecycleEvent(&event, 0)) {
        Android_HandleLifecycleEvent(event);
    }

    ആകുമ്പോൾ (Android_Paused && !Android_Destroyed) {
        Android_PumpEvents(-1);
    }

    എങ്കിൽ (Android_Destroyed) {
        SDL_SetError("Android activity has been destroyed");
        തിരികെ false;
    }

    Android_LockActivityMutex();
    തിരികെ true;
}

ശൂന്യം Android_QuitEvents(ശൂന്യം)
{
    Android_EventsInitialized = false;
}

#അല്ലെങ്കിൽ

#അന്തര്ഭാവ "../../core/android/SDL_android.h"

ശൂന്യം Android_InitEvents(ശൂന്യം)
{
}

ശൂന്യം Android_PumpEvents(Sint64 timeoutNS)
{
    (ശൂന്യം)timeoutNS;
}

bool Android_WaitActiveAndLockActivity(ശൂന്യം)
{
    Android_LockActivityMutex();
    തിരികെ true;
}

ശൂന്യം Android_QuitEvents(ശൂന്യം)
{
}

#endif // SDL_VIDEO_DRIVER_ANDROID

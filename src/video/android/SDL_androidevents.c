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
#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_ANDROID

#અન્તર્ભાવ "SDL_androidevents.h"
#અન્તર્ભાવ "SDL_androidkeyboard.h"
#અન્તર્ભાવ "SDL_androidwindow.h"
#અન્તર્ભાવ "../SDL_sysvideo.h"
#અન્તર્ભાવ "../../events/SDL_events_c.h"

#અન્તર્ભાવ "../../audio/aaudio/SDL_aaudio.h"
#અન્તર્ભાવ "../../audio/openslES/SDL_openslES.h"


#ifdef SDL_VIDEO_OPENGL_EGL
સ્થિર શૂન્ય android_egl_context_restore(SDL_Window *window)
{
    જો (window && (window->flags & SDL_WINDOW_OPENGL)) {
        SDL_WindowData *data = window->internal;
        SDL_GL_MakeCurrent(window, ખાલી);
        જો (!SDL_GL_MakeCurrent(window, (SDL_GLContext)data->egl_context)) {
            // The context is no longer valid, create a new one
            data->egl_context = (EGLContext)SDL_GL_CreateContext(window);
            SDL_GL_MakeCurrent(window, (SDL_GLContext)data->egl_context);
            SDL_Event event;
            SDL_zero(event);
            event.type = SDL_EVENT_RENDER_DEVICE_RESET;
            event.render.windowID = SDL_GetWindowID(window);
            SDL_ધકેલો_Event(&event);
        }
        data->backup_done = false;

        SDL_GL_SetSwapInterval(data->swap_interval);
    }
}

સ્થિર શૂન્ય android_egl_context_backup(SDL_Window *window)
{
    જો (window && (window->flags & SDL_WINDOW_OPENGL)) {
        પૂર્ણાંક interval = 0;
        // Keep a copy of the EGL Context so we can try to restore it when we resume
        SDL_WindowData *data = window->internal;
        data->egl_context = SDL_GL_GetCurrentContext();

        // Save/Restore the swap interval / vsync
        જો (SDL_GL_GetSwapInterval(&interval)) {
            data->has_swap_interval = 1;
            data->swap_interval = interval;
        }

        // We need to do this so the EGLSurface can be freed
        SDL_GL_MakeCurrent(window, ખાલી);
        data->backup_done = true;
    }
}
#endif

/*
 * Android_ResumeSem and Android_PauseSem are signaled from Java_org_libsdl_app_SDLActivity_nativePause and Java_org_libsdl_app_SDLActivity_nativeResume
 */
સ્થિર bool Android_EventsInitialized;
સ્થિર bool Android_BlockOnPause = true;
સ્થિર bool Android_Paused;
સ્થિર bool Android_PausedAudio;
સ્થિર bool Android_Destroyed;

શૂન્ય Android_InitEvents(શૂન્ય)
{
    જો (!Android_EventsInitialized) {
        Android_BlockOnPause = SDL_GetHintBoolean(SDL_HINT_ANDROID_BLOCK_ON_PAUSE, true);
        Android_Paused = false;
        Android_Destroyed = false;
        Android_EventsInitialized = true;
    }
}

સ્થિર શૂન્ય Android_PauseAudio(શૂન્ય)
{
    OPENSLES_PauseDevices();
    AAUDIO_PauseDevices();
    Android_PausedAudio = true;
}

સ્થિર શૂન્ય Android_ResumeAudio(શૂન્ય)
{
    જો (Android_PausedAudio) {
        OPENSLES_ResumeDevices();
        AAUDIO_ResumeDevices();
        Android_PausedAudio = false;
    }
}

સ્થિર શૂન્ય Android_OnPause(શૂન્ય)
{
    SDL_OnApplicationWillEnterBackground();
    SDL_OnApplicationDidEnterBackground();

    /* The semantics are that as soon as the enter background event
     * has been queued, the app will block. The application should
     * do any life cycle handling in an event filter while the event
     * was being queued.
     */
#ifdef SDL_VIDEO_OPENGL_EGL
    જો (Android_Window && !Android_Window->external_graphics_context) {
        Android_LockActivityMutex();
        android_egl_context_backup(Android_Window);
        Android_UnlockActivityMutex();
    }
#endif

    જો (Android_BlockOnPause) {
        // We're blocking, also pause audio
        Android_PauseAudio();
    }

    Android_Paused = true;
}

સ્થિર શૂન્ય Android_OnResume(શૂન્ય)
{
    Android_Paused = false;

    SDL_OnApplicationWillEnterForeground();

    Android_ResumeAudio();

#ifdef SDL_VIDEO_OPENGL_EGL
    // Restore the GL Context from here, as this operation is thread dependent
    જો (Android_Window && !Android_Window->external_graphics_context && !SDL_HasEvent(SDL_EVENT_QUIT)) {
        Android_LockActivityMutex();
        android_egl_context_restore(Android_Window);
        Android_UnlockActivityMutex();
    }
#endif

    SDL_OnApplicationDidEnterForeground();
}

સ્થિર શૂન્ય Android_On_નીચલું_Memory(શૂન્ય)
{
    SDL_SendAppEvent(SDL_EVENT_નીચલું_MEMORY);
}

સ્થિર શૂન્ય Android_OnDestroy(શૂન્ય)
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

સ્થિર શૂન્ય Android_HandleLifecycleEvent(SDL_AndroidLifecycleEvent event)
{
    પસંદગી (event) {
    સ્થિતિ SDL_ANDROID_LIFECYCLE_WAKE:
        // Nothing to do, just return
        તોડો;
    સ્થિતિ SDL_ANDROID_LIFECYCLE_PAUSE:
        Android_OnPause();
        તોડો;
    સ્થિતિ SDL_ANDROID_LIFECYCLE_RESUME:
        Android_OnResume();
        તોડો;
    સ્થિતિ SDL_ANDROID_LIFECYCLE_LOWMEMORY:
        Android_On_નીચલું_Memory();
        તોડો;
    સ્થિતિ SDL_ANDROID_LIFECYCLE_DESTROY:
        Android_OnDestroy();
        તોડો;
    મૂળભૂત:
        તોડો;
    }
}

સ્થિર Sint64 GetLifecycleEventTimeout(bool paused, Sint64 timeoutNS)
{
    જો (Android_Paused) {
        જો (Android_BlockOnPause) {
            timeoutNS = -1;
        } નહીંતર જો (timeoutNS == 0) {
            timeoutNS = SDL_MS_TO_NS(100);
        }
    }
    પાછા timeoutNS;
}

શૂન્ય Android_PumpEvents(Sint64 timeoutNS)
{
    SDL_AndroidLifecycleEvent event;
    bool paused = Android_Paused;

    જ્યારે (!Android_Destroyed &&
           Android_WaitLifecycleEvent(&event, GetLifecycleEventTimeout(paused, timeoutNS))) {
        Android_HandleLifecycleEvent(event);

        પસંદગી (event) {
        સ્થિતિ SDL_ANDROID_LIFECYCLE_WAKE:
            // Finish handling events quickly if we're not paused
            timeoutNS = 0;
            તોડો;
        સ્થિતિ SDL_ANDROID_LIFECYCLE_PAUSE:
            // Finish handling events at the current timeout and return to process events one more time before blocking.
            તોડો;
        સ્થિતિ SDL_ANDROID_LIFECYCLE_RESUME:
            // Finish handling events at the resume state timeout
            paused = false;
            તોડો;
        મૂળભૂત:
            તોડો;
        }
    }
}

bool Android_WaitActiveAndLockActivity(શૂન્ય)
{
    /* Make sure we have pumped all events so that Android_Paused state is correct */
    SDL_AndroidLifecycleEvent event;
    જ્યારે (!Android_Destroyed && Android_WaitLifecycleEvent(&event, 0)) {
        Android_HandleLifecycleEvent(event);
    }

    જ્યારે (Android_Paused && !Android_Destroyed) {
        Android_PumpEvents(-1);
    }

    જો (Android_Destroyed) {
        SDL_SetError("Android activity has been destroyed");
        પાછા false;
    }

    Android_LockActivityMutex();
    પાછા true;
}

શૂન્ય Android_QuitEvents(શૂન્ય)
{
    Android_EventsInitialized = false;
}

#નહીંતર

#અન્તર્ભાવ "../../core/android/SDL_android.h"

શૂન્ય Android_InitEvents(શૂન્ય)
{
}

શૂન્ય Android_PumpEvents(Sint64 timeoutNS)
{
    (શૂન્ય)timeoutNS;
}

bool Android_WaitActiveAndLockActivity(શૂન્ય)
{
    Android_LockActivityMutex();
    પાછા true;
}

શૂન્ય Android_QuitEvents(શૂન્ય)
{
}

#endif // SDL_VIDEO_DRIVER_ANDROID

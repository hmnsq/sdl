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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_ANDROID

#ଅନ୍ତର୍ଭାଵ "SDL_androidevents.h"
#ଅନ୍ତର୍ଭାଵ "SDL_androidkeyboard.h"
#ଅନ୍ତର୍ଭାଵ "SDL_androidwindow.h"
#ଅନ୍ତର୍ଭାଵ "../SDL_sysvideo.h"
#ଅନ୍ତର୍ଭାଵ "../../events/SDL_events_c.h"

#ଅନ୍ତର୍ଭାଵ "../../audio/aaudio/SDL_aaudio.h"
#ଅନ୍ତର୍ଭାଵ "../../audio/openslES/SDL_openslES.h"


#ifdef SDL_VIDEO_OPENGL_EGL
ସ୍ଥିର ଶୂନ୍ୟ android_egl_context_restore(SDL_Window *window)
{
    ଯଦି (window && (window->flags & SDL_WINDOW_OPENGL)) {
        SDL_WindowData *data = window->internal;
        SDL_GL_MakeCurrent(window, ଖାଲି);
        ଯଦି (!SDL_GL_MakeCurrent(window, (SDL_GLContext)data->egl_context)) {
            // The context is no longer valid, create a new one
            data->egl_context = (EGLContext)SDL_GL_CreateContext(window);
            SDL_GL_MakeCurrent(window, (SDL_GLContext)data->egl_context);
            SDL_Event event;
            SDL_zero(event);
            event.type = SDL_EVENT_RENDER_DEVICE_RESET;
            event.render.windowID = SDL_GetWindowID(window);
            SDL_ଠେଲ_Event(&event);
        }
        data->backup_done = false;

        SDL_GL_SetSwapInterval(data->swap_interval);
    }
}

ସ୍ଥିର ଶୂନ୍ୟ android_egl_context_backup(SDL_Window *window)
{
    ଯଦି (window && (window->flags & SDL_WINDOW_OPENGL)) {
        ପୂର୍ଣ୍ଣସଂଖ୍ୟା interval = 0;
        // Keep a copy of the EGL Context so we can try to restore it when we resume
        SDL_WindowData *data = window->internal;
        data->egl_context = SDL_GL_GetCurrentContext();

        // Save/Restore the swap interval / vsync
        ଯଦି (SDL_GL_GetSwapInterval(&interval)) {
            data->has_swap_interval = 1;
            data->swap_interval = interval;
        }

        // We need to do this so the EGLSurface can be freed
        SDL_GL_MakeCurrent(window, ଖାଲି);
        data->backup_done = true;
    }
}
#endif

/*
 * Android_ResumeSem and Android_PauseSem are signaled from Java_org_libsdl_app_SDLActivity_nativePause and Java_org_libsdl_app_SDLActivity_nativeResume
 */
ସ୍ଥିର bool Android_EventsInitialized;
ସ୍ଥିର bool Android_BlockOnPause = true;
ସ୍ଥିର bool Android_Paused;
ସ୍ଥିର bool Android_PausedAudio;
ସ୍ଥିର bool Android_Destroyed;

ଶୂନ୍ୟ Android_InitEvents(ଶୂନ୍ୟ)
{
    ଯଦି (!Android_EventsInitialized) {
        Android_BlockOnPause = SDL_GetHintBoolean(SDL_HINT_ANDROID_BLOCK_ON_PAUSE, true);
        Android_Paused = false;
        Android_Destroyed = false;
        Android_EventsInitialized = true;
    }
}

ସ୍ଥିର ଶୂନ୍ୟ Android_PauseAudio(ଶୂନ୍ୟ)
{
    OPENSLES_PauseDevices();
    AAUDIO_PauseDevices();
    Android_PausedAudio = true;
}

ସ୍ଥିର ଶୂନ୍ୟ Android_ResumeAudio(ଶୂନ୍ୟ)
{
    ଯଦି (Android_PausedAudio) {
        OPENSLES_ResumeDevices();
        AAUDIO_ResumeDevices();
        Android_PausedAudio = false;
    }
}

ସ୍ଥିର ଶୂନ୍ୟ Android_OnPause(ଶୂନ୍ୟ)
{
    SDL_OnApplicationWillEnterBackground();
    SDL_OnApplicationDidEnterBackground();

    /* The semantics are that as soon as the enter background event
     * has been queued, the app will block. The application should
     * do any life cycle handling in an event filter while the event
     * was being queued.
     */
#ifdef SDL_VIDEO_OPENGL_EGL
    ଯଦି (Android_Window && !Android_Window->external_graphics_context) {
        Android_LockActivityMutex();
        android_egl_context_backup(Android_Window);
        Android_UnlockActivityMutex();
    }
#endif

    ଯଦି (Android_BlockOnPause) {
        // We're blocking, also pause audio
        Android_PauseAudio();
    }

    Android_Paused = true;
}

ସ୍ଥିର ଶୂନ୍ୟ Android_OnResume(ଶୂନ୍ୟ)
{
    Android_Paused = false;

    SDL_OnApplicationWillEnterForeground();

    Android_ResumeAudio();

#ifdef SDL_VIDEO_OPENGL_EGL
    // Restore the GL Context from here, as this operation is thread dependent
    ଯଦି (Android_Window && !Android_Window->external_graphics_context && !SDL_HasEvent(SDL_EVENT_QUIT)) {
        Android_LockActivityMutex();
        android_egl_context_restore(Android_Window);
        Android_UnlockActivityMutex();
    }
#endif

    SDL_OnApplicationDidEnterForeground();
}

ସ୍ଥିର ଶୂନ୍ୟ Android_On_ତଳ_Memory(ଶୂନ୍ୟ)
{
    SDL_SendAppEvent(SDL_EVENT_ତଳ_MEMORY);
}

ସ୍ଥିର ଶୂନ୍ୟ Android_OnDestroy(ଶୂନ୍ୟ)
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

ସ୍ଥିର ଶୂନ୍ୟ Android_HandleLifecycleEvent(SDL_AndroidLifecycleEvent event)
{
    ବାଛ (event) {
    ସ୍ଥିତି SDL_ANDROID_LIFECYCLE_WAKE:
        // Nothing to do, just return
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_ANDROID_LIFECYCLE_PAUSE:
        Android_OnPause();
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_ANDROID_LIFECYCLE_RESUME:
        Android_OnResume();
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_ANDROID_LIFECYCLE_LOWMEMORY:
        Android_On_ତଳ_Memory();
        ଭାଙ୍ଗ;
    ସ୍ଥିତି SDL_ANDROID_LIFECYCLE_DESTROY:
        Android_OnDestroy();
        ଭାଙ୍ଗ;
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
        ଭାଙ୍ଗ;
    }
}

ସ୍ଥିର Sint64 GetLifecycleEventTimeout(bool paused, Sint64 timeoutNS)
{
    ଯଦି (Android_Paused) {
        ଯଦି (Android_BlockOnPause) {
            timeoutNS = -1;
        } ଅନ୍ୟଥା ଯଦି (timeoutNS == 0) {
            timeoutNS = SDL_MS_TO_NS(100);
        }
    }
    ଫେରନ୍ତୁ timeoutNS;
}

ଶୂନ୍ୟ Android_PumpEvents(Sint64 timeoutNS)
{
    SDL_AndroidLifecycleEvent event;
    bool paused = Android_Paused;

    ଯେତେବେଳେ (!Android_Destroyed &&
           Android_WaitLifecycleEvent(&event, GetLifecycleEventTimeout(paused, timeoutNS))) {
        Android_HandleLifecycleEvent(event);

        ବାଛ (event) {
        ସ୍ଥିତି SDL_ANDROID_LIFECYCLE_WAKE:
            // Finish handling events quickly if we're not paused
            timeoutNS = 0;
            ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_ANDROID_LIFECYCLE_PAUSE:
            // Finish handling events at the current timeout and return to process events one more time before blocking.
            ଭାଙ୍ଗ;
        ସ୍ଥିତି SDL_ANDROID_LIFECYCLE_RESUME:
            // Finish handling events at the resume state timeout
            paused = false;
            ଭାଙ୍ଗ;
        ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
            ଭାଙ୍ଗ;
        }
    }
}

bool Android_WaitActiveAndLockActivity(ଶୂନ୍ୟ)
{
    /* Make sure we have pumped all events so that Android_Paused state is correct */
    SDL_AndroidLifecycleEvent event;
    ଯେତେବେଳେ (!Android_Destroyed && Android_WaitLifecycleEvent(&event, 0)) {
        Android_HandleLifecycleEvent(event);
    }

    ଯେତେବେଳେ (Android_Paused && !Android_Destroyed) {
        Android_PumpEvents(-1);
    }

    ଯଦି (Android_Destroyed) {
        SDL_SetError("Android activity has been destroyed");
        ଫେରନ୍ତୁ false;
    }

    Android_LockActivityMutex();
    ଫେରନ୍ତୁ true;
}

ଶୂନ୍ୟ Android_QuitEvents(ଶୂନ୍ୟ)
{
    Android_EventsInitialized = false;
}

#ଅନ୍ୟଥା

#ଅନ୍ତର୍ଭାଵ "../../core/android/SDL_android.h"

ଶୂନ୍ୟ Android_InitEvents(ଶୂନ୍ୟ)
{
}

ଶୂନ୍ୟ Android_PumpEvents(Sint64 timeoutNS)
{
    (ଶୂନ୍ୟ)timeoutNS;
}

bool Android_WaitActiveAndLockActivity(ଶୂନ୍ୟ)
{
    Android_LockActivityMutex();
    ଫେରନ୍ତୁ true;
}

ଶୂନ୍ୟ Android_QuitEvents(ଶୂନ୍ୟ)
{
}

#endif // SDL_VIDEO_DRIVER_ANDROID

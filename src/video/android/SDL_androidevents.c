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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_ANDROID

#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_androidevents.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_androidkeyboard.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_androidwindow.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../events/SDL_events_c.h"

#ਅਨ੍ਤਰ੍ਭਾਵ "../../audio/aaudio/SDL_aaudio.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "../../audio/openslES/SDL_openslES.h"


#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
ਸਥਿਰ ਖਾਲੀ android_egl_context_restore(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਜੇ (ਖਿੜਕੀ && (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_OPENGL)) {
        SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
        SDL_GL_MakeCurrent(ਖਿੜਕੀ, ਨਿਰਾ);
        ਜੇ (!SDL_GL_MakeCurrent(ਖਿੜਕੀ, (SDL_GLContext)ਅੰਕੜੇ->egl_context)) {
            // The context is no longer valid, create a new one
            ਅੰਕੜੇ->egl_context = (EGLContext)SDL_GL_CreateContext(ਖਿੜਕੀ);
            SDL_GL_MakeCurrent(ਖਿੜਕੀ, (SDL_GLContext)ਅੰਕੜੇ->egl_context);
            SDL_Event event;
            SDL_zero(event);
            event.type = SDL_EVENT_RENDER_DEVICE_RESET;
            event.render.ਖਿੜਕੀ_ID = SDL_Get_ਖਿੜਕੀ_ID(ਖਿੜਕੀ);
            SDL_ਧੱਕੋ_Event(&event);
        }
        ਅੰਕੜੇ->backup_ਪੂਰਾ = false;

        SDL_GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval(ਅੰਕੜੇ->ਅਦਲਾ_ਬਦਲੀ_interval);
    }
}

ਸਥਿਰ ਖਾਲੀ android_egl_context_backup(SDL_ਖਿੜਕੀ *ਖਿੜਕੀ)
{
    ਜੇ (ਖਿੜਕੀ && (ਖਿੜਕੀ->flags & SDL_ਖਿੜਕੀ_OPENGL)) {
        ਪੂਰਨ interval = 0;
        // Keep a copy of the EGL Context so we can try to restore it when we resume
        SDL_ਖਿੜਕੀ_ਅੰਕੜੇ *ਅੰਕੜੇ = ਖਿੜਕੀ->ਅੰਦਰੂਨੀ;
        ਅੰਕੜੇ->egl_context = SDL_GL_GetCurrentContext();

        // Save/Restore the swap interval / vsync
        ਜੇ (SDL_GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval(&interval)) {
            ਅੰਕੜੇ->has_ਅਦਲਾ_ਬਦਲੀ_interval = 1;
            ਅੰਕੜੇ->ਅਦਲਾ_ਬਦਲੀ_interval = interval;
        }

        // We need to do this so the EGLSurface can be freed
        SDL_GL_MakeCurrent(ਖਿੜਕੀ, ਨਿਰਾ);
        ਅੰਕੜੇ->backup_ਪੂਰਾ = true;
    }
}
#ਜੇ_ਅੰਤ

/*
 * Android_ResumeSem and Android_PauseSem are signaled from Java_org_libsdl_app_SDLActivity_nativePause and Java_org_libsdl_app_SDLActivity_nativeResume
 */
ਸਥਿਰ bool Android_EventsInitialized;
ਸਥਿਰ bool Android_ਖੰਡ_On_Pause = true;
ਸਥਿਰ bool Android_Paused;
ਸਥਿਰ bool Android_PausedAudio;
ਸਥਿਰ bool Android_Destroyed;

ਖਾਲੀ Android_InitEvents(ਖਾਲੀ)
{
    ਜੇ (!Android_EventsInitialized) {
        Android_ਖੰਡ_On_Pause = SDL_GetHintBoolean(SDL_HINT_ANDROID_ਖੰਡ_ON_PAUSE, true);
        Android_Paused = false;
        Android_Destroyed = false;
        Android_EventsInitialized = true;
    }
}

ਸਥਿਰ ਖਾਲੀ Android_PauseAudio(ਖਾਲੀ)
{
    OPENSLES_PauseDevices();
    AAUDIO_PauseDevices();
    Android_PausedAudio = true;
}

ਸਥਿਰ ਖਾਲੀ Android_ResumeAudio(ਖਾਲੀ)
{
    ਜੇ (Android_PausedAudio) {
        OPENSLES_ResumeDevices();
        AAUDIO_ResumeDevices();
        Android_PausedAudio = false;
    }
}

ਸਥਿਰ ਖਾਲੀ Android_OnPause(ਖਾਲੀ)
{
    SDL_OnApplicationWillEnterBackground();
    SDL_OnApplicationDidEnterBackground();

    /* The semantics are that as soon as the enter background event
     * has been queued, the app will block. The application should
     * do any life cycle handling in an event filter while the event
     * was being queued.
     */
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
    ਜੇ (Android_ਖਿੜਕੀ && !Android_ਖਿੜਕੀ->external_graphics_context) {
        Android_ਤਾਲਾ_Activity_Mutex();
        android_egl_context_backup(Android_ਖਿੜਕੀ);
        Android_UnlockActivityMutex();
    }
#ਜੇ_ਅੰਤ

    ਜੇ (Android_ਖੰਡ_On_Pause) {
        // We're blocking, also pause audio
        Android_PauseAudio();
    }

    Android_Paused = true;
}

ਸਥਿਰ ਖਾਲੀ Android_OnResume(ਖਾਲੀ)
{
    Android_Paused = false;

    SDL_OnApplicationWillEnterForeground();

    Android_ResumeAudio();

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_EGL
    // Restore the GL Context from here, as this operation is thread dependent
    ਜੇ (Android_ਖਿੜਕੀ && !Android_ਖਿੜਕੀ->external_graphics_context && !SDL_HasEvent(SDL_EVENT_QUIT)) {
        Android_ਤਾਲਾ_Activity_Mutex();
        android_egl_context_restore(Android_ਖਿੜਕੀ);
        Android_UnlockActivityMutex();
    }
#ਜੇ_ਅੰਤ

    SDL_OnApplicationDidEnterForeground();
}

ਸਥਿਰ ਖਾਲੀ Android_On_ਨੀਵਾਂ_ਸਮ੍ਰਿਤੀ(ਖਾਲੀ)
{
    SDL_SendAppEvent(SDL_EVENT_ਨੀਵਾਂ_ਸਮ੍ਰਿਤੀ);
}

ਸਥਿਰ ਖਾਲੀ Android_OnDestroy(ਖਾਲੀ)
{
    // Make sure we unblock any audio processing before we quit
    Android_ResumeAudio();

    /* Discard previous events. The user should have handled state storage
     * in SDL_EVENT_WILL_ENTER_BACKGROUND. After nativeSendQuit() is called, no
     * events other than SDL_EVENT_QUIT and SDL_EVENT_TERMINATING should fire */
    SDL_FlushEvents(SDL_EVENT_ਪਹਿਲਾ, SDL_EVENT_ਆਖਰੀ);
    SDL_SendQuit();
    SDL_OnApplicationWillTerminate();

    Android_Destroyed = true;
}

ਸਥਿਰ ਖਾਲੀ Android_HandleLifecycleEvent(SDL_AndroidLifecycleEvent event)
{
    ਚੋਣ (event) {
    ਹਾਲਤ SDL_ANDROID_LIFECYCLE_WAKE:
        // Nothing to do, just return
        ਰੋਕੋ;
    ਹਾਲਤ SDL_ANDROID_LIFECYCLE_PAUSE:
        Android_OnPause();
        ਰੋਕੋ;
    ਹਾਲਤ SDL_ANDROID_LIFECYCLE_RESUME:
        Android_OnResume();
        ਰੋਕੋ;
    ਹਾਲਤ SDL_ANDROID_LIFECYCLE_LOWMEMORY:
        Android_On_ਨੀਵਾਂ_ਸਮ੍ਰਿਤੀ();
        ਰੋਕੋ;
    ਹਾਲਤ SDL_ANDROID_LIFECYCLE_DESTROY:
        Android_OnDestroy();
        ਰੋਕੋ;
    ਮੂਲ:
        ਰੋਕੋ;
    }
}

ਸਥਿਰ Sint64 GetLifecycleEventTimeout(bool paused, Sint64 timeoutNS)
{
    ਜੇ (Android_Paused) {
        ਜੇ (Android_ਖੰਡ_On_Pause) {
            timeoutNS = -1;
        } ਨਹੀਂਤਾਂ ਜੇ (timeoutNS == 0) {
            timeoutNS = SDL_MS_ਮੰਜ਼ਿਲ_NS(100);
        }
    }
    ਵਾਪਸ timeoutNS;
}

ਖਾਲੀ Android_PumpEvents(Sint64 timeoutNS)
{
    SDL_AndroidLifecycleEvent event;
    bool paused = Android_Paused;

    ਜਦੋਂ (!Android_Destroyed &&
           Android_WaitLifecycleEvent(&event, GetLifecycleEventTimeout(paused, timeoutNS))) {
        Android_HandleLifecycleEvent(event);

        ਚੋਣ (event) {
        ਹਾਲਤ SDL_ANDROID_LIFECYCLE_WAKE:
            // Finish handling events quickly if we're not paused
            timeoutNS = 0;
            ਰੋਕੋ;
        ਹਾਲਤ SDL_ANDROID_LIFECYCLE_PAUSE:
            // Finish handling events at the current timeout and return to process events one more time before blocking.
            ਰੋਕੋ;
        ਹਾਲਤ SDL_ANDROID_LIFECYCLE_RESUME:
            // Finish handling events at the resume state timeout
            paused = false;
            ਰੋਕੋ;
        ਮੂਲ:
            ਰੋਕੋ;
        }
    }
}

bool Android_Wait_ਸਰਗਰਮ_And_ਤਾਲਾ_Activity(ਖਾਲੀ)
{
    /* Make sure we have pumped all events so that Android_Paused state is correct */
    SDL_AndroidLifecycleEvent event;
    ਜਦੋਂ (!Android_Destroyed && Android_WaitLifecycleEvent(&event, 0)) {
        Android_HandleLifecycleEvent(event);
    }

    ਜਦੋਂ (Android_Paused && !Android_Destroyed) {
        Android_PumpEvents(-1);
    }

    ਜੇ (Android_Destroyed) {
        SDL_ਸੈੱਟ_Error("Android activity has been destroyed");
        ਵਾਪਸ false;
    }

    Android_ਤਾਲਾ_Activity_Mutex();
    ਵਾਪਸ true;
}

ਖਾਲੀ Android_QuitEvents(ਖਾਲੀ)
{
    Android_EventsInitialized = false;
}

#ਨਹੀਂਤਾਂ

#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/android/SDL_android.h"

ਖਾਲੀ Android_InitEvents(ਖਾਲੀ)
{
}

ਖਾਲੀ Android_PumpEvents(Sint64 timeoutNS)
{
    (ਖਾਲੀ)timeoutNS;
}

bool Android_Wait_ਸਰਗਰਮ_And_ਤਾਲਾ_Activity(ਖਾਲੀ)
{
    Android_ਤਾਲਾ_Activity_Mutex();
    ਵਾਪਸ true;
}

ਖਾਲੀ Android_QuitEvents(ਖਾਲੀ)
{
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_ANDROID

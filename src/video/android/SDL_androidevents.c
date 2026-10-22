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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_ANDROID

#ಅನ್ತರ್ಭಾವ "SDL_androidevents.h"
#ಅನ್ತರ್ಭಾವ "SDL_androidkeyboard.h"
#ಅನ್ತರ್ಭಾವ "SDL_androidwindow.h"
#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"
#ಅನ್ತರ್ಭಾವ "../../events/SDL_events_c.h"

#ಅನ್ತರ್ಭಾವ "../../audio/aaudio/SDL_aaudio.h"
#ಅನ್ತರ್ಭಾವ "../../audio/openslES/SDL_openslES.h"


#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
ಸ್ಥಿರ ಶೂನ್ಯ android_egl_context_restore(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಆದರೆ (ಕಿಟಕಿ && (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_OPENGL)) {
        SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
        SDL_GL_MakeCurrent(ಕಿಟಕಿ, ಖಾಲಿ);
        ಆದರೆ (!SDL_GL_MakeCurrent(ಕಿಟಕಿ, (SDL_GLContext)ದತ್ತಾಂಶ->egl_context)) {
            // The context is no longer valid, create a new one
            ದತ್ತಾಂಶ->egl_context = (EGLContext)SDL_GL_CreateContext(ಕಿಟಕಿ);
            SDL_GL_MakeCurrent(ಕಿಟಕಿ, (SDL_GLContext)ದತ್ತಾಂಶ->egl_context);
            SDL_Event event;
            SDL_zero(event);
            event.type = SDL_EVENT_RENDER_DEVICE_RESET;
            event.render.ಕಿಟಕಿ_ID = SDL_Get_ಕಿಟಕಿ_ID(ಕಿಟಕಿ);
            SDL_ತಳ್ಳು_Event(&event);
        }
        ದತ್ತಾಂಶ->backup_ಮುಗಿದ = false;

        SDL_GL_ಗಣ_ಅದಲುಬದಲು_Interval(ದತ್ತಾಂಶ->ಅದಲುಬದಲು_interval);
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ android_egl_context_backup(SDL_ಕಿಟಕಿ *ಕಿಟಕಿ)
{
    ಆದರೆ (ಕಿಟಕಿ && (ಕಿಟಕಿ->flags & SDL_ಕಿಟಕಿ_OPENGL)) {
        ಪೂರ್ಣಾಂಕ interval = 0;
        // Keep a copy of the EGL Context so we can try to restore it when we resume
        SDL_ಕಿಟಕಿ_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ = ಕಿಟಕಿ->ಆಂತರಿಕ;
        ದತ್ತಾಂಶ->egl_context = SDL_GL_GetCurrentContext();

        // Save/Restore the swap interval / vsync
        ಆದರೆ (SDL_GL_Get_ಅದಲುಬದಲು_Interval(&interval)) {
            ದತ್ತಾಂಶ->has_ಅದಲುಬದಲು_interval = 1;
            ದತ್ತಾಂಶ->ಅದಲುಬದಲು_interval = interval;
        }

        // We need to do this so the EGLSurface can be freed
        SDL_GL_MakeCurrent(ಕಿಟಕಿ, ಖಾಲಿ);
        ದತ್ತಾಂಶ->backup_ಮುಗಿದ = true;
    }
}
#ಆದರೆ_ಅಂತ್ಯ

/*
 * Android_ResumeSem and Android_PauseSem are signaled from Java_org_libsdl_app_SDLActivity_nativePause and Java_org_libsdl_app_SDLActivity_nativeResume
 */
ಸ್ಥಿರ bool Android_EventsInitialized;
ಸ್ಥಿರ bool Android_ಖಂಡ_On_Pause = true;
ಸ್ಥಿರ bool Android_Paused;
ಸ್ಥಿರ bool Android_PausedAudio;
ಸ್ಥಿರ bool Android_Destroyed;

ಶೂನ್ಯ Android_InitEvents(ಶೂನ್ಯ)
{
    ಆದರೆ (!Android_EventsInitialized) {
        Android_ಖಂಡ_On_Pause = SDL_GetHintBoolean(SDL_HINT_ANDROID_ಖಂಡ_ON_PAUSE, true);
        Android_Paused = false;
        Android_Destroyed = false;
        Android_EventsInitialized = true;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Android_PauseAudio(ಶೂನ್ಯ)
{
    OPENSLES_PauseDevices();
    AAUDIO_PauseDevices();
    Android_PausedAudio = true;
}

ಸ್ಥಿರ ಶೂನ್ಯ Android_ResumeAudio(ಶೂನ್ಯ)
{
    ಆದರೆ (Android_PausedAudio) {
        OPENSLES_ResumeDevices();
        AAUDIO_ResumeDevices();
        Android_PausedAudio = false;
    }
}

ಸ್ಥಿರ ಶೂನ್ಯ Android_OnPause(ಶೂನ್ಯ)
{
    SDL_OnApplicationWillEnterBackground();
    SDL_OnApplicationDidEnterBackground();

    /* The semantics are that as soon as the enter background event
     * has been queued, the app will block. The application should
     * do any life cycle handling in an event filter while the event
     * was being queued.
     */
#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
    ಆದರೆ (Android_ಕಿಟಕಿ && !Android_ಕಿಟಕಿ->external_graphics_context) {
        Android_ಬೀಗ_Activity_Mutex();
        android_egl_context_backup(Android_ಕಿಟಕಿ);
        Android_UnlockActivityMutex();
    }
#ಆದರೆ_ಅಂತ್ಯ

    ಆದರೆ (Android_ಖಂಡ_On_Pause) {
        // We're blocking, also pause audio
        Android_PauseAudio();
    }

    Android_Paused = true;
}

ಸ್ಥಿರ ಶೂನ್ಯ Android_OnResume(ಶೂನ್ಯ)
{
    Android_Paused = false;

    SDL_OnApplicationWillEnterForeground();

    Android_ResumeAudio();

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_OPENGL_EGL
    // Restore the GL Context from here, as this operation is thread dependent
    ಆದರೆ (Android_ಕಿಟಕಿ && !Android_ಕಿಟಕಿ->external_graphics_context && !SDL_HasEvent(SDL_EVENT_QUIT)) {
        Android_ಬೀಗ_Activity_Mutex();
        android_egl_context_restore(Android_ಕಿಟಕಿ);
        Android_UnlockActivityMutex();
    }
#ಆದರೆ_ಅಂತ್ಯ

    SDL_OnApplicationDidEnterForeground();
}

ಸ್ಥಿರ ಶೂನ್ಯ Android_On_ಕೆಳಗಿನ_ಸ್ಮರಣೆ(ಶೂನ್ಯ)
{
    SDL_SendAppEvent(SDL_EVENT_ಕೆಳಗಿನ_ಸ್ಮರಣೆ);
}

ಸ್ಥಿರ ಶೂನ್ಯ Android_OnDestroy(ಶೂನ್ಯ)
{
    // Make sure we unblock any audio processing before we quit
    Android_ResumeAudio();

    /* Discard previous events. The user should have handled state storage
     * in SDL_EVENT_WILL_ENTER_BACKGROUND. After nativeSendQuit() is called, no
     * events other than SDL_EVENT_QUIT and SDL_EVENT_TERMINATING should fire */
    SDL_FlushEvents(SDL_EVENT_ಮೊದಲ, SDL_EVENT_ಕೊನೆಯ);
    SDL_SendQuit();
    SDL_OnApplicationWillTerminate();

    Android_Destroyed = true;
}

ಸ್ಥಿರ ಶೂನ್ಯ Android_HandleLifecycleEvent(SDL_AndroidLifecycleEvent event)
{
    ಆಯ್ಕೆ (event) {
    ಸ್ಥಿತಿ SDL_ANDROID_LIFECYCLE_WAKE:
        // Nothing to do, just return
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_ANDROID_LIFECYCLE_PAUSE:
        Android_OnPause();
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_ANDROID_LIFECYCLE_RESUME:
        Android_OnResume();
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_ANDROID_LIFECYCLE_LOWMEMORY:
        Android_On_ಕೆಳಗಿನ_ಸ್ಮರಣೆ();
        ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ SDL_ANDROID_LIFECYCLE_DESTROY:
        Android_OnDestroy();
        ನಿಲ್ಲಿಸು;
    ಪೂರ್ವನಿಯೋಜಿತ:
        ನಿಲ್ಲಿಸು;
    }
}

ಸ್ಥಿರ Sint64 GetLifecycleEventTimeout(bool paused, Sint64 timeoutNS)
{
    ಆದರೆ (Android_Paused) {
        ಆದರೆ (Android_ಖಂಡ_On_Pause) {
            timeoutNS = -1;
        } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (timeoutNS == 0) {
            timeoutNS = SDL_MS_ಗಮ್ಯ_NS(100);
        }
    }
    ಹಿಂತಿರುಗಿ timeoutNS;
}

ಶೂನ್ಯ Android_PumpEvents(Sint64 timeoutNS)
{
    SDL_AndroidLifecycleEvent event;
    bool paused = Android_Paused;

    ಆಗ (!Android_Destroyed &&
           Android_WaitLifecycleEvent(&event, GetLifecycleEventTimeout(paused, timeoutNS))) {
        Android_HandleLifecycleEvent(event);

        ಆಯ್ಕೆ (event) {
        ಸ್ಥಿತಿ SDL_ANDROID_LIFECYCLE_WAKE:
            // Finish handling events quickly if we're not paused
            timeoutNS = 0;
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_ANDROID_LIFECYCLE_PAUSE:
            // Finish handling events at the current timeout and return to process events one more time before blocking.
            ನಿಲ್ಲಿಸು;
        ಸ್ಥಿತಿ SDL_ANDROID_LIFECYCLE_RESUME:
            // Finish handling events at the resume state timeout
            paused = false;
            ನಿಲ್ಲಿಸು;
        ಪೂರ್ವನಿಯೋಜಿತ:
            ನಿಲ್ಲಿಸು;
        }
    }
}

bool Android_Wait_ಸಕ್ರಿಯ_And_ಬೀಗ_Activity(ಶೂನ್ಯ)
{
    /* Make sure we have pumped all events so that Android_Paused state is correct */
    SDL_AndroidLifecycleEvent event;
    ಆಗ (!Android_Destroyed && Android_WaitLifecycleEvent(&event, 0)) {
        Android_HandleLifecycleEvent(event);
    }

    ಆಗ (Android_Paused && !Android_Destroyed) {
        Android_PumpEvents(-1);
    }

    ಆದರೆ (Android_Destroyed) {
        SDL_ಗಣ_Error("Android activity has been destroyed");
        ಹಿಂತಿರುಗಿ false;
    }

    Android_ಬೀಗ_Activity_Mutex();
    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ Android_QuitEvents(ಶೂನ್ಯ)
{
    Android_EventsInitialized = false;
}

#ಇಲ್ಲದಿದ್ದರೆ

#ಅನ್ತರ್ಭಾವ "../../core/android/SDL_android.h"

ಶೂನ್ಯ Android_InitEvents(ಶೂನ್ಯ)
{
}

ಶೂನ್ಯ Android_PumpEvents(Sint64 timeoutNS)
{
    (ಶೂನ್ಯ)timeoutNS;
}

bool Android_Wait_ಸಕ್ರಿಯ_And_ಬೀಗ_Activity(ಶೂನ್ಯ)
{
    Android_ಬೀಗ_Activity_Mutex();
    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ Android_QuitEvents(ಶೂನ್ಯ)
{
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_ANDROID

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

#अगर_घोषित SDL_VIDEO_DRIVER_ANDROID

#समावेश "SDL_androidevents.h"
#समावेश "SDL_androidkeyboard.h"
#समावेश "SDL_androidwindow.h"
#समावेश "../SDL_sysvideo.h"
#समावेश "../../events/SDL_events_c.h"

#समावेश "../../audio/aaudio/SDL_aaudio.h"
#समावेश "../../audio/openslES/SDL_openslES.h"


#अगर_घोषित SDL_VIDEO_OPENGL_EGL
अटल व्योम android_egl_context_restore(SDL_Window *window)
{
    अगर (window && (window->flags & SDL_WINDOW_OPENGL)) {
        SDL_Window_तथ्य *तथ्य = window->internal;
        SDL_GL_MakeCurrent(window, शून्य);
        अगर (!SDL_GL_MakeCurrent(window, (SDL_GLContext)तथ्य->egl_context)) {
            // The context is no longer valid, create a new one
            तथ्य->egl_context = (EGLContext)SDL_GL_CreateContext(window);
            SDL_GL_MakeCurrent(window, (SDL_GLContext)तथ्य->egl_context);
            SDL_Event event;
            SDL_zero(event);
            event.type = SDL_EVENT_RENDER_DEVICE_RESET;
            event.render.windowID = SDL_GetWindowID(window);
            SDL_धकेलो_Event(&event);
        }
        तथ्य->backup_done = false;

        SDL_GL_SetSwapInterval(तथ्य->swap_interval);
    }
}

अटल व्योम android_egl_context_backup(SDL_Window *window)
{
    अगर (window && (window->flags & SDL_WINDOW_OPENGL)) {
        पूर्णांक interval = 0;
        // Keep a copy of the EGL Context so we can try to restore it when we resume
        SDL_Window_तथ्य *तथ्य = window->internal;
        तथ्य->egl_context = SDL_GL_GetCurrentContext();

        // Save/Restore the swap interval / vsync
        अगर (SDL_GL_GetSwapInterval(&interval)) {
            तथ्य->has_swap_interval = 1;
            तथ्य->swap_interval = interval;
        }

        // We need to do this so the EGLSurface can be freed
        SDL_GL_MakeCurrent(window, शून्य);
        तथ्य->backup_done = true;
    }
}
#पूर्ण_अगर

/*
 * Android_ResumeSem and Android_PauseSem are signaled from Java_org_libsdl_app_SDLActivity_nativePause and Java_org_libsdl_app_SDLActivity_nativeResume
 */
अटल bool Android_EventsInitialized;
अटल bool Android_BlockOnPause = true;
अटल bool Android_Paused;
अटल bool Android_PausedAudio;
अटल bool Android_Destroyed;

व्योम Android_InitEvents(व्योम)
{
    अगर (!Android_EventsInitialized) {
        Android_BlockOnPause = SDL_GetHintBoolean(SDL_HINT_ANDROID_BLOCK_ON_PAUSE, true);
        Android_Paused = false;
        Android_Destroyed = false;
        Android_EventsInitialized = true;
    }
}

अटल व्योम Android_PauseAudio(व्योम)
{
    OPENSLES_PauseDevices();
    AAUDIO_PauseDevices();
    Android_PausedAudio = true;
}

अटल व्योम Android_ResumeAudio(व्योम)
{
    अगर (Android_PausedAudio) {
        OPENSLES_ResumeDevices();
        AAUDIO_ResumeDevices();
        Android_PausedAudio = false;
    }
}

अटल व्योम Android_OnPause(व्योम)
{
    SDL_OnApplicationWillEnterBackground();
    SDL_OnApplicationDidEnterBackground();

    /* The semantics are that as soon as the enter background event
     * has been queued, the app will block. The application should
     * do any life cycle handling in an event filter while the event
     * was being queued.
     */
#अगर_घोषित SDL_VIDEO_OPENGL_EGL
    अगर (Android_Window && !Android_Window->external_graphics_context) {
        Android_LockActivityMutex();
        android_egl_context_backup(Android_Window);
        Android_UnlockActivityMutex();
    }
#पूर्ण_अगर

    अगर (Android_BlockOnPause) {
        // We're blocking, also pause audio
        Android_PauseAudio();
    }

    Android_Paused = true;
}

अटल व्योम Android_OnResume(व्योम)
{
    Android_Paused = false;

    SDL_OnApplicationWillEnterForeground();

    Android_ResumeAudio();

#अगर_घोषित SDL_VIDEO_OPENGL_EGL
    // Restore the GL Context from here, as this operation is thread dependent
    अगर (Android_Window && !Android_Window->external_graphics_context && !SDL_HasEvent(SDL_EVENT_QUIT)) {
        Android_LockActivityMutex();
        android_egl_context_restore(Android_Window);
        Android_UnlockActivityMutex();
    }
#पूर्ण_अगर

    SDL_OnApplicationDidEnterForeground();
}

अटल व्योम Android_On_निचला_Memory(व्योम)
{
    SDL_SendAppEvent(SDL_EVENT_निचला_MEMORY);
}

अटल व्योम Android_OnDestroy(व्योम)
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

अटल व्योम Android_HandleLifecycleEvent(SDL_AndroidLifecycleEvent event)
{
    चयन (event) {
    हाल SDL_ANDROID_LIFECYCLE_WAKE:
        // Nothing to do, just return
        अवरोध;
    हाल SDL_ANDROID_LIFECYCLE_PAUSE:
        Android_OnPause();
        अवरोध;
    हाल SDL_ANDROID_LIFECYCLE_RESUME:
        Android_OnResume();
        अवरोध;
    हाल SDL_ANDROID_LIFECYCLE_LOWMEMORY:
        Android_On_निचला_Memory();
        अवरोध;
    हाल SDL_ANDROID_LIFECYCLE_DESTROY:
        Android_OnDestroy();
        अवरोध;
    शेष:
        अवरोध;
    }
}

अटल Sint64 GetLifecycleEventTimeout(bool paused, Sint64 timeoutNS)
{
    अगर (Android_Paused) {
        अगर (Android_BlockOnPause) {
            timeoutNS = -1;
        } अन्यथा अगर (timeoutNS == 0) {
            timeoutNS = SDL_MS_TO_NS(100);
        }
    }
    वापस timeoutNS;
}

व्योम Android_PumpEvents(Sint64 timeoutNS)
{
    SDL_AndroidLifecycleEvent event;
    bool paused = Android_Paused;

    जबतक (!Android_Destroyed &&
           Android_WaitLifecycleEvent(&event, GetLifecycleEventTimeout(paused, timeoutNS))) {
        Android_HandleLifecycleEvent(event);

        चयन (event) {
        हाल SDL_ANDROID_LIFECYCLE_WAKE:
            // Finish handling events quickly if we're not paused
            timeoutNS = 0;
            अवरोध;
        हाल SDL_ANDROID_LIFECYCLE_PAUSE:
            // Finish handling events at the current timeout and return to process events one more time before blocking.
            अवरोध;
        हाल SDL_ANDROID_LIFECYCLE_RESUME:
            // Finish handling events at the resume state timeout
            paused = false;
            अवरोध;
        शेष:
            अवरोध;
        }
    }
}

bool Android_WaitActiveAndLockActivity(व्योम)
{
    /* Make sure we have pumped all events so that Android_Paused state is correct */
    SDL_AndroidLifecycleEvent event;
    जबतक (!Android_Destroyed && Android_WaitLifecycleEvent(&event, 0)) {
        Android_HandleLifecycleEvent(event);
    }

    जबतक (Android_Paused && !Android_Destroyed) {
        Android_PumpEvents(-1);
    }

    अगर (Android_Destroyed) {
        SDL_SetError("Android activity has been destroyed");
        वापस false;
    }

    Android_LockActivityMutex();
    वापस true;
}

व्योम Android_QuitEvents(व्योम)
{
    Android_EventsInitialized = false;
}

#अन्यथा

#समावेश "../../core/android/SDL_android.h"

व्योम Android_InitEvents(व्योम)
{
}

व्योम Android_PumpEvents(Sint64 timeoutNS)
{
    (व्योम)timeoutNS;
}

bool Android_WaitActiveAndLockActivity(व्योम)
{
    Android_LockActivityMutex();
    वापस true;
}

व्योम Android_QuitEvents(व्योम)
{
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_ANDROID

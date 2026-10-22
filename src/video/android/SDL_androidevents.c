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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_ANDROID

#अन्तर्भाव "SDL_androidevents.h"
#अन्तर्भाव "SDL_androidkeyboard.h"
#अन्तर्भाव "SDL_androidwindow.h"
#अन्तर्भाव "../SDL_sysvideo.h"
#अन्तर्भाव "../../events/SDL_events_c.h"

#अन्तर्भाव "../../audio/aaudio/SDL_aaudio.h"
#अन्तर्भाव "../../audio/openslES/SDL_openslES.h"


#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
स्थिर शून्य android_egl_context_restore(SDL_गवाक्षः *गवाक्षः)
{
    यदि (गवाक्षः && (गवाक्षः->flags & SDL_गवाक्षः_OPENGL)) {
        SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
        SDL_GL_MakeCurrent(गवाक्षः, रिक्त);
        यदि (!SDL_GL_MakeCurrent(गवाक्षः, (SDL_GLContext)दत्त->egl_context)) {
            // The context is no longer valid, create a new one
            दत्त->egl_context = (EGLContext)SDL_GL_CreateContext(गवाक्षः);
            SDL_GL_MakeCurrent(गवाक्षः, (SDL_GLContext)दत्त->egl_context);
            SDL_Event event;
            SDL_zero(event);
            event.type = SDL_EVENT_RENDER_DEVICE_RESET;
            event.render.गवाक्षः_ID = SDL_Get_गवाक्षः_ID(गवाक्षः);
            SDL_प्रक्षिप_Event(&event);
        }
        दत्त->backup_समाप्तम् = false;

        SDL_GL_समुच्चयः_Swap_Interval(दत्त->swap_interval);
    }
}

स्थिर शून्य android_egl_context_backup(SDL_गवाक्षः *गवाक्षः)
{
    यदि (गवाक्षः && (गवाक्षः->flags & SDL_गवाक्षः_OPENGL)) {
        पूर्णाङ्क interval = 0;
        // Keep a copy of the EGL Context so we can try to restore it when we resume
        SDL_गवाक्षः_दत्त *दत्त = गवाक्षः->आन्तरिकम्;
        दत्त->egl_context = SDL_GL_GetCurrentContext();

        // Save/Restore the swap interval / vsync
        यदि (SDL_GL_GetSwapInterval(&interval)) {
            दत्त->has_swap_interval = 1;
            दत्त->swap_interval = interval;
        }

        // We need to do this so the EGLSurface can be freed
        SDL_GL_MakeCurrent(गवाक्षः, रिक्त);
        दत्त->backup_समाप्तम् = true;
    }
}
#यदि_अन्तः

/*
 * Android_ResumeSem and Android_PauseSem are signaled from Java_org_libsdl_app_SDLActivity_nativePause and Java_org_libsdl_app_SDLActivity_nativeResume
 */
स्थिर bool Android_EventsInitialized;
स्थिर bool Android_खण्डम्_On_Pause = true;
स्थिर bool Android_Paused;
स्थिर bool Android_PausedAudio;
स्थिर bool Android_Destroyed;

शून्य Android_InitEvents(शून्य)
{
    यदि (!Android_EventsInitialized) {
        Android_खण्डम्_On_Pause = SDL_GetHintBoolean(SDL_HINT_ANDROID_खण्डम्_ON_PAUSE, true);
        Android_Paused = false;
        Android_Destroyed = false;
        Android_EventsInitialized = true;
    }
}

स्थिर शून्य Android_PauseAudio(शून्य)
{
    OPENSLES_PauseDevices();
    AAUDIO_PauseDevices();
    Android_PausedAudio = true;
}

स्थिर शून्य Android_ResumeAudio(शून्य)
{
    यदि (Android_PausedAudio) {
        OPENSLES_ResumeDevices();
        AAUDIO_ResumeDevices();
        Android_PausedAudio = false;
    }
}

स्थिर शून्य Android_OnPause(शून्य)
{
    SDL_OnApplicationWillEnterBackground();
    SDL_OnApplicationDidEnterBackground();

    /* The semantics are that as soon as the enter background event
     * has been queued, the app will block. The application should
     * do any life cycle handling in an event filter while the event
     * was being queued.
     */
#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
    यदि (Android_गवाक्षः && !Android_गवाक्षः->external_graphics_context) {
        Android_तालकम्_Activity_Mutex();
        android_egl_context_backup(Android_गवाक्षः);
        Android_UnlockActivityMutex();
    }
#यदि_अन्तः

    यदि (Android_खण्डम्_On_Pause) {
        // We're blocking, also pause audio
        Android_PauseAudio();
    }

    Android_Paused = true;
}

स्थिर शून्य Android_OnResume(शून्य)
{
    Android_Paused = false;

    SDL_OnApplicationWillEnterForeground();

    Android_ResumeAudio();

#यदि_परिभाषितम् SDL_VIDEO_OPENGL_EGL
    // Restore the GL Context from here, as this operation is thread dependent
    यदि (Android_गवाक्षः && !Android_गवाक्षः->external_graphics_context && !SDL_HasEvent(SDL_EVENT_QUIT)) {
        Android_तालकम्_Activity_Mutex();
        android_egl_context_restore(Android_गवाक्षः);
        Android_UnlockActivityMutex();
    }
#यदि_अन्तः

    SDL_OnApplicationDidEnterForeground();
}

स्थिर शून्य Android_On_नीचः_स्मृतिः(शून्य)
{
    SDL_SendAppEvent(SDL_EVENT_नीचः_स्मृतिः);
}

स्थिर शून्य Android_OnDestroy(शून्य)
{
    // Make sure we unblock any audio processing before we quit
    Android_ResumeAudio();

    /* Discard previous events. The user should have handled state storage
     * in SDL_EVENT_WILL_ENTER_BACKGROUND. After nativeSendQuit() is called, no
     * events other than SDL_EVENT_QUIT and SDL_EVENT_TERMINATING should fire */
    SDL_FlushEvents(SDL_EVENT_FIRST, SDL_EVENT_चरमः);
    SDL_SendQuit();
    SDL_OnApplicationWillTerminate();

    Android_Destroyed = true;
}

स्थिर शून्य Android_HandleLifecycleEvent(SDL_AndroidLifecycleEvent event)
{
    विकल्प (event) {
    पक्ष SDL_ANDROID_LIFECYCLE_WAKE:
        // Nothing to do, just return
        भङ्ग;
    पक्ष SDL_ANDROID_LIFECYCLE_PAUSE:
        Android_OnPause();
        भङ्ग;
    पक्ष SDL_ANDROID_LIFECYCLE_RESUME:
        Android_OnResume();
        भङ्ग;
    पक्ष SDL_ANDROID_LIFECYCLE_LOWMEMORY:
        Android_On_नीचः_स्मृतिः();
        भङ्ग;
    पक्ष SDL_ANDROID_LIFECYCLE_DESTROY:
        Android_OnDestroy();
        भङ्ग;
    स्वभाव:
        भङ्ग;
    }
}

स्थिर Sint64 GetLifecycleEventTimeout(bool paused, Sint64 timeoutNS)
{
    यदि (Android_Paused) {
        यदि (Android_खण्डम्_On_Pause) {
            timeoutNS = -1;
        } अन्यथा यदि (timeoutNS == 0) {
            timeoutNS = SDL_MS_गन्तव्यम्_NS(100);
        }
    }
    प्रत्यागम timeoutNS;
}

शून्य Android_PumpEvents(Sint64 timeoutNS)
{
    SDL_AndroidLifecycleEvent event;
    bool paused = Android_Paused;

    यावत् (!Android_Destroyed &&
           Android_WaitLifecycleEvent(&event, GetLifecycleEventTimeout(paused, timeoutNS))) {
        Android_HandleLifecycleEvent(event);

        विकल्प (event) {
        पक्ष SDL_ANDROID_LIFECYCLE_WAKE:
            // Finish handling events quickly if we're not paused
            timeoutNS = 0;
            भङ्ग;
        पक्ष SDL_ANDROID_LIFECYCLE_PAUSE:
            // Finish handling events at the current timeout and return to process events one more time before blocking.
            भङ्ग;
        पक्ष SDL_ANDROID_LIFECYCLE_RESUME:
            // Finish handling events at the resume state timeout
            paused = false;
            भङ्ग;
        स्वभाव:
            भङ्ग;
        }
    }
}

bool Android_Wait_सक्रिय_And_तालकम्_Activity(शून्य)
{
    /* Make sure we have pumped all events so that Android_Paused state is correct */
    SDL_AndroidLifecycleEvent event;
    यावत् (!Android_Destroyed && Android_WaitLifecycleEvent(&event, 0)) {
        Android_HandleLifecycleEvent(event);
    }

    यावत् (Android_Paused && !Android_Destroyed) {
        Android_PumpEvents(-1);
    }

    यदि (Android_Destroyed) {
        SDL_समुच्चयः_Error("Android activity has been destroyed");
        प्रत्यागम false;
    }

    Android_तालकम्_Activity_Mutex();
    प्रत्यागम true;
}

शून्य Android_QuitEvents(शून्य)
{
    Android_EventsInitialized = false;
}

#अन्यथा

#अन्तर्भाव "../../core/android/SDL_android.h"

शून्य Android_InitEvents(शून्य)
{
}

शून्य Android_PumpEvents(Sint64 timeoutNS)
{
    (शून्य)timeoutNS;
}

bool Android_Wait_सक्रिय_And_तालकम्_Activity(शून्य)
{
    Android_तालकम्_Activity_Mutex();
    प्रत्यागम true;
}

शून्य Android_QuitEvents(शून्य)
{
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_ANDROID

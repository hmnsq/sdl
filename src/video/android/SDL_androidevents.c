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

#నిర్వచితమైతే SDL_VIDEO_DRIVER_ANDROID

#అన్తర్భావ "SDL_androidevents.h"
#అన్తర్భావ "SDL_androidkeyboard.h"
#అన్తర్భావ "SDL_androidwindow.h"
#అన్తర్భావ "../SDL_sysvideo.h"
#అన్తర్భావ "../../events/SDL_events_c.h"

#అన్తర్భావ "../../audio/aaudio/SDL_aaudio.h"
#అన్తర్భావ "../../audio/openslES/SDL_openslES.h"


#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
స్థిర శూన్య android_egl_context_restore(SDL_కిటికీ *కిటికీ)
{
    ఒకవేళ (కిటికీ && (కిటికీ->flags & SDL_కిటికీ_OPENGL)) {
        SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
        SDL_GL_MakeCurrent(కిటికీ, ఖాళీ);
        ఒకవేళ (!SDL_GL_MakeCurrent(కిటికీ, (SDL_GLContext)దత్తాంశం->egl_context)) {
            // The context is no longer valid, create a new one
            దత్తాంశం->egl_context = (EGLContext)SDL_GL_CreateContext(కిటికీ);
            SDL_GL_MakeCurrent(కిటికీ, (SDL_GLContext)దత్తాంశం->egl_context);
            SDL_Event event;
            SDL_zero(event);
            event.type = SDL_EVENT_RENDER_DEVICE_RESET;
            event.render.కిటికీ_ID = SDL_Get_కిటికీ_ID(కిటికీ);
            SDL_నెట్టు_Event(&event);
        }
        దత్తాంశం->backup_పూర్తి = false;

        SDL_GL_సమితి_మార్పిడి_Interval(దత్తాంశం->మార్పిడి_interval);
    }
}

స్థిర శూన్య android_egl_context_backup(SDL_కిటికీ *కిటికీ)
{
    ఒకవేళ (కిటికీ && (కిటికీ->flags & SDL_కిటికీ_OPENGL)) {
        పూర్ణాంకం interval = 0;
        // Keep a copy of the EGL Context so we can try to restore it when we resume
        SDL_కిటికీ_దత్తాంశం *దత్తాంశం = కిటికీ->అంతర్గత;
        దత్తాంశం->egl_context = SDL_GL_GetCurrentContext();

        // Save/Restore the swap interval / vsync
        ఒకవేళ (SDL_GL_Get_మార్పిడి_Interval(&interval)) {
            దత్తాంశం->has_మార్పిడి_interval = 1;
            దత్తాంశం->మార్పిడి_interval = interval;
        }

        // We need to do this so the EGLSurface can be freed
        SDL_GL_MakeCurrent(కిటికీ, ఖాళీ);
        దత్తాంశం->backup_పూర్తి = true;
    }
}
#అయితే_ముగింపు

/*
 * Android_ResumeSem and Android_PauseSem are signaled from Java_org_libsdl_app_SDLActivity_nativePause and Java_org_libsdl_app_SDLActivity_nativeResume
 */
స్థిర bool Android_EventsInitialized;
స్థిర bool Android_ఖండం_On_Pause = true;
స్థిర bool Android_Paused;
స్థిర bool Android_PausedAudio;
స్థిర bool Android_Destroyed;

శూన్య Android_InitEvents(శూన్య)
{
    ఒకవేళ (!Android_EventsInitialized) {
        Android_ఖండం_On_Pause = SDL_GetHintBoolean(SDL_HINT_ANDROID_ఖండం_ON_PAUSE, true);
        Android_Paused = false;
        Android_Destroyed = false;
        Android_EventsInitialized = true;
    }
}

స్థిర శూన్య Android_PauseAudio(శూన్య)
{
    OPENSLES_PauseDevices();
    AAUDIO_PauseDevices();
    Android_PausedAudio = true;
}

స్థిర శూన్య Android_ResumeAudio(శూన్య)
{
    ఒకవేళ (Android_PausedAudio) {
        OPENSLES_ResumeDevices();
        AAUDIO_ResumeDevices();
        Android_PausedAudio = false;
    }
}

స్థిర శూన్య Android_OnPause(శూన్య)
{
    SDL_OnApplicationWillEnterBackground();
    SDL_OnApplicationDidEnterBackground();

    /* The semantics are that as soon as the enter background event
     * has been queued, the app will block. The application should
     * do any life cycle handling in an event filter while the event
     * was being queued.
     */
#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
    ఒకవేళ (Android_కిటికీ && !Android_కిటికీ->external_graphics_context) {
        Android_తాళం_Activity_Mutex();
        android_egl_context_backup(Android_కిటికీ);
        Android_UnlockActivityMutex();
    }
#అయితే_ముగింపు

    ఒకవేళ (Android_ఖండం_On_Pause) {
        // We're blocking, also pause audio
        Android_PauseAudio();
    }

    Android_Paused = true;
}

స్థిర శూన్య Android_OnResume(శూన్య)
{
    Android_Paused = false;

    SDL_OnApplicationWillEnterForeground();

    Android_ResumeAudio();

#నిర్వచితమైతే SDL_VIDEO_OPENGL_EGL
    // Restore the GL Context from here, as this operation is thread dependent
    ఒకవేళ (Android_కిటికీ && !Android_కిటికీ->external_graphics_context && !SDL_HasEvent(SDL_EVENT_QUIT)) {
        Android_తాళం_Activity_Mutex();
        android_egl_context_restore(Android_కిటికీ);
        Android_UnlockActivityMutex();
    }
#అయితే_ముగింపు

    SDL_OnApplicationDidEnterForeground();
}

స్థిర శూన్య Android_On_దిగువ_జ్ఞాపకం(శూన్య)
{
    SDL_SendAppEvent(SDL_EVENT_దిగువ_జ్ఞాపకం);
}

స్థిర శూన్య Android_OnDestroy(శూన్య)
{
    // Make sure we unblock any audio processing before we quit
    Android_ResumeAudio();

    /* Discard previous events. The user should have handled state storage
     * in SDL_EVENT_WILL_ENTER_BACKGROUND. After nativeSendQuit() is called, no
     * events other than SDL_EVENT_QUIT and SDL_EVENT_TERMINATING should fire */
    SDL_FlushEvents(SDL_EVENT_మొదటి, SDL_EVENT_చివరి);
    SDL_SendQuit();
    SDL_OnApplicationWillTerminate();

    Android_Destroyed = true;
}

స్థిర శూన్య Android_HandleLifecycleEvent(SDL_AndroidLifecycleEvent event)
{
    ఎంపిక (event) {
    స్థితి SDL_ANDROID_LIFECYCLE_WAKE:
        // Nothing to do, just return
        ఆపు;
    స్థితి SDL_ANDROID_LIFECYCLE_PAUSE:
        Android_OnPause();
        ఆపు;
    స్థితి SDL_ANDROID_LIFECYCLE_RESUME:
        Android_OnResume();
        ఆపు;
    స్థితి SDL_ANDROID_LIFECYCLE_LOWMEMORY:
        Android_On_దిగువ_జ్ఞాపకం();
        ఆపు;
    స్థితి SDL_ANDROID_LIFECYCLE_DESTROY:
        Android_OnDestroy();
        ఆపు;
    అప్రమేయ:
        ఆపు;
    }
}

స్థిర Sint64 GetLifecycleEventTimeout(bool paused, Sint64 timeoutNS)
{
    ఒకవేళ (Android_Paused) {
        ఒకవేళ (Android_ఖండం_On_Pause) {
            timeoutNS = -1;
        } లేకపోతే ఒకవేళ (timeoutNS == 0) {
            timeoutNS = SDL_MS_గమ్యం_NS(100);
        }
    }
    తిరిగి timeoutNS;
}

శూన్య Android_PumpEvents(Sint64 timeoutNS)
{
    SDL_AndroidLifecycleEvent event;
    bool paused = Android_Paused;

    అయితే (!Android_Destroyed &&
           Android_WaitLifecycleEvent(&event, GetLifecycleEventTimeout(paused, timeoutNS))) {
        Android_HandleLifecycleEvent(event);

        ఎంపిక (event) {
        స్థితి SDL_ANDROID_LIFECYCLE_WAKE:
            // Finish handling events quickly if we're not paused
            timeoutNS = 0;
            ఆపు;
        స్థితి SDL_ANDROID_LIFECYCLE_PAUSE:
            // Finish handling events at the current timeout and return to process events one more time before blocking.
            ఆపు;
        స్థితి SDL_ANDROID_LIFECYCLE_RESUME:
            // Finish handling events at the resume state timeout
            paused = false;
            ఆపు;
        అప్రమేయ:
            ఆపు;
        }
    }
}

bool Android_Wait_చురుకైన_And_తాళం_Activity(శూన్య)
{
    /* Make sure we have pumped all events so that Android_Paused state is correct */
    SDL_AndroidLifecycleEvent event;
    అయితే (!Android_Destroyed && Android_WaitLifecycleEvent(&event, 0)) {
        Android_HandleLifecycleEvent(event);
    }

    అయితే (Android_Paused && !Android_Destroyed) {
        Android_PumpEvents(-1);
    }

    ఒకవేళ (Android_Destroyed) {
        SDL_సమితి_Error("Android activity has been destroyed");
        తిరిగి false;
    }

    Android_తాళం_Activity_Mutex();
    తిరిగి true;
}

శూన్య Android_QuitEvents(శూన్య)
{
    Android_EventsInitialized = false;
}

#లేకపోతే

#అన్తర్భావ "../../core/android/SDL_android.h"

శూన్య Android_InitEvents(శూన్య)
{
}

శూన్య Android_PumpEvents(Sint64 timeoutNS)
{
    (శూన్య)timeoutNS;
}

bool Android_Wait_చురుకైన_And_తాళం_Activity(శూన్య)
{
    Android_తాళం_Activity_Mutex();
    తిరిగి true;
}

శూన్య Android_QuitEvents(శూన్య)
{
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_ANDROID

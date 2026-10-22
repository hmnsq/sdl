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
#شامل "SDL_internal.h"

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_ANDROID

#شامل "SDL_androidevents.h"
#شامل "SDL_androidkeyboard.h"
#شامل "SDL_androidwindow.h"
#شامل "../SDL_sysvideo.h"
#شامل "../../events/SDL_events_c.h"

#شامل "../../audio/aaudio/SDL_aaudio.h"
#شامل "../../audio/openslES/SDL_openslES.h"


#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
ساکن خالی android_egl_context_restore(SDL_کھڑکی *کھڑکی)
{
    اگر (کھڑکی && (کھڑکی->flags & SDL_کھڑکی_OPENGL)) {
        SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
        SDL_GL_MakeCurrent(کھڑکی, تہی);
        اگر (!SDL_GL_MakeCurrent(کھڑکی, (SDL_GLContext)ڈیٹا->egl_context)) {
            // The context is no longer valid, create a new one
            ڈیٹا->egl_context = (EGLContext)SDL_GL_CreateContext(کھڑکی);
            SDL_GL_MakeCurrent(کھڑکی, (SDL_GLContext)ڈیٹا->egl_context);
            SDL_Event event;
            SDL_zero(event);
            event.type = SDL_EVENT_RENDER_DEVICE_RESET;
            event.render.کھڑکی_ID = SDL_Get_کھڑکی_ID(کھڑکی);
            SDL_ڈالو_Event(&event);
        }
        ڈیٹا->backup_مکمل = false;

        SDL_GL_سیٹ_تبادلہ_Interval(ڈیٹا->تبادلہ_interval);
    }
}

ساکن خالی android_egl_context_backup(SDL_کھڑکی *کھڑکی)
{
    اگر (کھڑکی && (کھڑکی->flags & SDL_کھڑکی_OPENGL)) {
        صحیح interval = 0;
        // Keep a copy of the EGL Context so we can try to restore it when we resume
        SDL_کھڑکی_ڈیٹا *ڈیٹا = کھڑکی->اندرونی_2;
        ڈیٹا->egl_context = SDL_GL_GetCurrentContext();

        // Save/Restore the swap interval / vsync
        اگر (SDL_GL_Get_تبادلہ_Interval(&interval)) {
            ڈیٹا->has_تبادلہ_interval = 1;
            ڈیٹا->تبادلہ_interval = interval;
        }

        // We need to do this so the EGLSurface can be freed
        SDL_GL_MakeCurrent(کھڑکی, تہی);
        ڈیٹا->backup_مکمل = true;
    }
}
#اگر_ختم

/*
 * Android_ResumeSem and Android_PauseSem are signaled from Java_org_libsdl_app_SDLActivity_nativePause and Java_org_libsdl_app_SDLActivity_nativeResume
 */
ساکن bool Android_EventsInitialized;
ساکن bool Android_بلاک_On_Pause = true;
ساکن bool Android_Paused;
ساکن bool Android_PausedAudio;
ساکن bool Android_Destroyed;

خالی Android_InitEvents(خالی)
{
    اگر (!Android_EventsInitialized) {
        Android_بلاک_On_Pause = SDL_GetHintBoolean(SDL_HINT_ANDROID_بلاک_ON_PAUSE, true);
        Android_Paused = false;
        Android_Destroyed = false;
        Android_EventsInitialized = true;
    }
}

ساکن خالی Android_PauseAudio(خالی)
{
    OPENSLES_PauseDevices();
    AAUDIO_PauseDevices();
    Android_PausedAudio = true;
}

ساکن خالی Android_ResumeAudio(خالی)
{
    اگر (Android_PausedAudio) {
        OPENSLES_ResumeDevices();
        AAUDIO_ResumeDevices();
        Android_PausedAudio = false;
    }
}

ساکن خالی Android_OnPause(خالی)
{
    SDL_OnApplicationWillEnterBackground();
    SDL_OnApplicationDidEnterBackground();

    /* The semantics are that as soon as the enter background event
     * has been queued, the app will block. The application should
     * do any life cycle handling in an event filter while the event
     * was being queued.
     */
#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    اگر (Android_کھڑکی && !Android_کھڑکی->external_graphics_context) {
        Android_تالا_Activity_Mutex();
        android_egl_context_backup(Android_کھڑکی);
        Android_UnlockActivityMutex();
    }
#اگر_ختم

    اگر (Android_بلاک_On_Pause) {
        // We're blocking, also pause audio
        Android_PauseAudio();
    }

    Android_Paused = true;
}

ساکن خالی Android_OnResume(خالی)
{
    Android_Paused = false;

    SDL_OnApplicationWillEnterForeground();

    Android_ResumeAudio();

#اگر_تعریف_شدہ SDL_VIDEO_OPENGL_EGL
    // Restore the GL Context from here, as this operation is thread dependent
    اگر (Android_کھڑکی && !Android_کھڑکی->external_graphics_context && !SDL_HasEvent(SDL_EVENT_QUIT)) {
        Android_تالا_Activity_Mutex();
        android_egl_context_restore(Android_کھڑکی);
        Android_UnlockActivityMutex();
    }
#اگر_ختم

    SDL_OnApplicationDidEnterForeground();
}

ساکن خالی Android_On_کم_حافظہ(خالی)
{
    SDL_SendAppEvent(SDL_EVENT_کم_حافظہ);
}

ساکن خالی Android_OnDestroy(خالی)
{
    // Make sure we unblock any audio processing before we quit
    Android_ResumeAudio();

    /* Discard previous events. The user should have handled state storage
     * in SDL_EVENT_WILL_ENTER_BACKGROUND. After nativeSendQuit() is called, no
     * events other than SDL_EVENT_QUIT and SDL_EVENT_TERMINATING should fire */
    SDL_FlushEvents(SDL_EVENT_پہلا, SDL_EVENT_آخری);
    SDL_SendQuit();
    SDL_OnApplicationWillTerminate();

    Android_Destroyed = true;
}

ساکن خالی Android_HandleLifecycleEvent(SDL_AndroidLifecycleEvent event)
{
    انتخاب (event) {
    حالت SDL_ANDROID_LIFECYCLE_WAKE:
        // Nothing to do, just return
        توڑو;
    حالت SDL_ANDROID_LIFECYCLE_PAUSE:
        Android_OnPause();
        توڑو;
    حالت SDL_ANDROID_LIFECYCLE_RESUME:
        Android_OnResume();
        توڑو;
    حالت SDL_ANDROID_LIFECYCLE_LOWMEMORY:
        Android_On_کم_حافظہ();
        توڑو;
    حالت SDL_ANDROID_LIFECYCLE_DESTROY:
        Android_OnDestroy();
        توڑو;
    طےشدہ:
        توڑو;
    }
}

ساکن Sint64 GetLifecycleEventTimeout(bool paused, Sint64 timeoutNS)
{
    اگر (Android_Paused) {
        اگر (Android_بلاک_On_Pause) {
            timeoutNS = -1;
        } ورنہ اگر (timeoutNS == 0) {
            timeoutNS = SDL_MS_مقصد_NS(100);
        }
    }
    واپس timeoutNS;
}

خالی Android_PumpEvents(Sint64 timeoutNS)
{
    SDL_AndroidLifecycleEvent event;
    bool paused = Android_Paused;

    جب (!Android_Destroyed &&
           Android_WaitLifecycleEvent(&event, GetLifecycleEventTimeout(paused, timeoutNS))) {
        Android_HandleLifecycleEvent(event);

        انتخاب (event) {
        حالت SDL_ANDROID_LIFECYCLE_WAKE:
            // Finish handling events quickly if we're not paused
            timeoutNS = 0;
            توڑو;
        حالت SDL_ANDROID_LIFECYCLE_PAUSE:
            // Finish handling events at the current timeout and return to process events one more time before blocking.
            توڑو;
        حالت SDL_ANDROID_LIFECYCLE_RESUME:
            // Finish handling events at the resume state timeout
            paused = false;
            توڑو;
        طےشدہ:
            توڑو;
        }
    }
}

bool Android_Wait_فعال_And_تالا_Activity(خالی)
{
    /* Make sure we have pumped all events so that Android_Paused state is correct */
    SDL_AndroidLifecycleEvent event;
    جب (!Android_Destroyed && Android_WaitLifecycleEvent(&event, 0)) {
        Android_HandleLifecycleEvent(event);
    }

    جب (Android_Paused && !Android_Destroyed) {
        Android_PumpEvents(-1);
    }

    اگر (Android_Destroyed) {
        SDL_سیٹ_Error("Android activity has been destroyed");
        واپس false;
    }

    Android_تالا_Activity_Mutex();
    واپس true;
}

خالی Android_QuitEvents(خالی)
{
    Android_EventsInitialized = false;
}

#ورنہ

#شامل "../../core/android/SDL_android.h"

خالی Android_InitEvents(خالی)
{
}

خالی Android_PumpEvents(Sint64 timeoutNS)
{
    (خالی)timeoutNS;
}

bool Android_Wait_فعال_And_تالا_Activity(خالی)
{
    Android_تالا_Activity_Mutex();
    واپس true;
}

خالی Android_QuitEvents(خالی)
{
}

#اگر_ختم // SDL_VIDEO_DRIVER_ANDROID

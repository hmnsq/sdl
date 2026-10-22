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
#ضمن "SDL_internal.h"

#اگر_تعریف_شده SDL_VIDEO_DRIVER_ANDROID

#ضمن "SDL_androidevents.h"
#ضمن "SDL_androidkeyboard.h"
#ضمن "SDL_androidwindow.h"
#ضمن "../SDL_sysvideo.h"
#ضمن "../../events/SDL_events_c.h"

#ضمن "../../audio/aaudio/SDL_aaudio.h"
#ضمن "../../audio/openslES/SDL_openslES.h"


#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
ساكن فراغ android_egl_context_restore(SDL_پنجره *پنجره)
{
    إذا (پنجره && (پنجره->flags & SDL_پنجره_OPENGL)) {
        SDL_پنجره_داده *داده = پنجره->داخلی;
        SDL_GL_MakeCurrent(پنجره, عدم);
        إذا (!SDL_GL_MakeCurrent(پنجره, (SDL_GLContext)داده->egl_context)) {
            // The context is no longer valid, create a new one
            داده->egl_context = (EGLContext)SDL_GL_CreateContext(پنجره);
            SDL_GL_MakeCurrent(پنجره, (SDL_GLContext)داده->egl_context);
            SDL_Event event;
            SDL_zero(event);
            event.type = SDL_EVENT_RENDER_DEVICE_RESET;
            event.render.پنجره_ID = SDL_Get_پنجره_ID(پنجره);
            SDL_افزودن_Event(&event);
        }
        داده->backup_انجامشده = false;

        SDL_GL_مجموعه_جابجا_Interval(داده->جابجا_interval);
    }
}

ساكن فراغ android_egl_context_backup(SDL_پنجره *پنجره)
{
    إذا (پنجره && (پنجره->flags & SDL_پنجره_OPENGL)) {
        صحيح interval = 0;
        // Keep a copy of the EGL Context so we can try to restore it when we resume
        SDL_پنجره_داده *داده = پنجره->داخلی;
        داده->egl_context = SDL_GL_GetCurrentContext();

        // Save/Restore the swap interval / vsync
        إذا (SDL_GL_Get_جابجا_Interval(&interval)) {
            داده->has_جابجا_interval = 1;
            داده->جابجا_interval = interval;
        }

        // We need to do this so the EGLSurface can be freed
        SDL_GL_MakeCurrent(پنجره, عدم);
        داده->backup_انجامشده = true;
    }
}
#پایان_اگر

/*
 * Android_ResumeSem and Android_PauseSem are signaled from Java_org_libsdl_app_SDLActivity_nativePause and Java_org_libsdl_app_SDLActivity_nativeResume
 */
ساكن bool Android_EventsInitialized;
ساكن bool Android_بلوک_On_Pause = true;
ساكن bool Android_Paused;
ساكن bool Android_PausedAudio;
ساكن bool Android_Destroyed;

فراغ Android_InitEvents(فراغ)
{
    إذا (!Android_EventsInitialized) {
        Android_بلوک_On_Pause = SDL_GetHintBoolean(SDL_HINT_ANDROID_بلوک_ON_PAUSE, true);
        Android_Paused = false;
        Android_Destroyed = false;
        Android_EventsInitialized = true;
    }
}

ساكن فراغ Android_PauseAudio(فراغ)
{
    OPENSLES_PauseDevices();
    AAUDIO_PauseDevices();
    Android_PausedAudio = true;
}

ساكن فراغ Android_ResumeAudio(فراغ)
{
    إذا (Android_PausedAudio) {
        OPENSLES_ResumeDevices();
        AAUDIO_ResumeDevices();
        Android_PausedAudio = false;
    }
}

ساكن فراغ Android_OnPause(فراغ)
{
    SDL_OnApplicationWillEnterBackground();
    SDL_OnApplicationDidEnterBackground();

    /* The semantics are that as soon as the enter background event
     * has been queued, the app will block. The application should
     * do any life cycle handling in an event filter while the event
     * was being queued.
     */
#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
    إذا (Android_پنجره && !Android_پنجره->external_graphics_context) {
        Android_قفل_Activity_Mutex();
        android_egl_context_backup(Android_پنجره);
        Android_UnlockActivityMutex();
    }
#پایان_اگر

    إذا (Android_بلوک_On_Pause) {
        // We're blocking, also pause audio
        Android_PauseAudio();
    }

    Android_Paused = true;
}

ساكن فراغ Android_OnResume(فراغ)
{
    Android_Paused = false;

    SDL_OnApplicationWillEnterForeground();

    Android_ResumeAudio();

#اگر_تعریف_شده SDL_VIDEO_OPENGL_EGL
    // Restore the GL Context from here, as this operation is thread dependent
    إذا (Android_پنجره && !Android_پنجره->external_graphics_context && !SDL_HasEvent(SDL_EVENT_QUIT)) {
        Android_قفل_Activity_Mutex();
        android_egl_context_restore(Android_پنجره);
        Android_UnlockActivityMutex();
    }
#پایان_اگر

    SDL_OnApplicationDidEnterForeground();
}

ساكن فراغ Android_On_کم_حافظه(فراغ)
{
    SDL_SendAppEvent(SDL_EVENT_کم_حافظه);
}

ساكن فراغ Android_OnDestroy(فراغ)
{
    // Make sure we unblock any audio processing before we quit
    Android_ResumeAudio();

    /* Discard previous events. The user should have handled state storage
     * in SDL_EVENT_WILL_ENTER_BACKGROUND. After nativeSendQuit() is called, no
     * events other than SDL_EVENT_QUIT and SDL_EVENT_TERMINATING should fire */
    SDL_FlushEvents(SDL_EVENT_اولی, SDL_EVENT_آخرین);
    SDL_SendQuit();
    SDL_OnApplicationWillTerminate();

    Android_Destroyed = true;
}

ساكن فراغ Android_HandleLifecycleEvent(SDL_AndroidLifecycleEvent event)
{
    بدل (event) {
    حالة SDL_ANDROID_LIFECYCLE_WAKE:
        // Nothing to do, just return
        اكسر;
    حالة SDL_ANDROID_LIFECYCLE_PAUSE:
        Android_OnPause();
        اكسر;
    حالة SDL_ANDROID_LIFECYCLE_RESUME:
        Android_OnResume();
        اكسر;
    حالة SDL_ANDROID_LIFECYCLE_LOWMEMORY:
        Android_On_کم_حافظه();
        اكسر;
    حالة SDL_ANDROID_LIFECYCLE_DESTROY:
        Android_OnDestroy();
        اكسر;
    افتراضي:
        اكسر;
    }
}

ساكن Sint64 GetLifecycleEventTimeout(bool paused, Sint64 timeoutNS)
{
    إذا (Android_Paused) {
        إذا (Android_بلوک_On_Pause) {
            timeoutNS = -1;
        } وإلا إذا (timeoutNS == 0) {
            timeoutNS = SDL_MS_مقصد_NS(100);
        }
    }
    أرجع timeoutNS;
}

فراغ Android_PumpEvents(Sint64 timeoutNS)
{
    SDL_AndroidLifecycleEvent event;
    bool paused = Android_Paused;

    طالما (!Android_Destroyed &&
           Android_WaitLifecycleEvent(&event, GetLifecycleEventTimeout(paused, timeoutNS))) {
        Android_HandleLifecycleEvent(event);

        بدل (event) {
        حالة SDL_ANDROID_LIFECYCLE_WAKE:
            // Finish handling events quickly if we're not paused
            timeoutNS = 0;
            اكسر;
        حالة SDL_ANDROID_LIFECYCLE_PAUSE:
            // Finish handling events at the current timeout and return to process events one more time before blocking.
            اكسر;
        حالة SDL_ANDROID_LIFECYCLE_RESUME:
            // Finish handling events at the resume state timeout
            paused = false;
            اكسر;
        افتراضي:
            اكسر;
        }
    }
}

bool Android_Wait_فعال_And_قفل_Activity(فراغ)
{
    /* Make sure we have pumped all events so that Android_Paused state is correct */
    SDL_AndroidLifecycleEvent event;
    طالما (!Android_Destroyed && Android_WaitLifecycleEvent(&event, 0)) {
        Android_HandleLifecycleEvent(event);
    }

    طالما (Android_Paused && !Android_Destroyed) {
        Android_PumpEvents(-1);
    }

    إذا (Android_Destroyed) {
        SDL_مجموعه_Error("Android activity has been destroyed");
        أرجع false;
    }

    Android_قفل_Activity_Mutex();
    أرجع true;
}

فراغ Android_QuitEvents(فراغ)
{
    Android_EventsInitialized = false;
}

#وإلا

#ضمن "../../core/android/SDL_android.h"

فراغ Android_InitEvents(فراغ)
{
}

فراغ Android_PumpEvents(Sint64 timeoutNS)
{
    (فراغ)timeoutNS;
}

bool Android_Wait_فعال_And_قفل_Activity(فراغ)
{
    Android_قفل_Activity_Mutex();
    أرجع true;
}

فراغ Android_QuitEvents(فراغ)
{
}

#پایان_اگر // SDL_VIDEO_DRIVER_ANDROID

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

#اگر_تعریف_شده SDL_VIDEO_DRIVER_WAYLAND

#ضمن "../../core/unix/SDL_poll.h"
#ضمن "SDL_waylandeventthread.h"
#ضمن "SDL_waylandvideo.h"

#ضمن <errno.h>

تعريفنوع تعداد Wayland_کار_وضعیت
{
    کار_وضعیت_انتظار = 0,
    کار_وضعیت_RUNNING,
    کار_وضعیت_SIGNAL_PENDING,
    کار_وضعیت_SIGNALED,
    کار_وضعیت_CANCELED
} Wayland_کار_وضعیت;

تعريفنوع بنية Wayland_کار
{
    Wayland_کار_Thread_Callback callback;
    فراغ *userdata;
    Wayland_کار_ID id;
    Wayland_کار_وضعیت وضعیت;

    بنية wl_list link;
} Wayland_کار;

بنية Wayland_کار_Thread_Context
{
    SDL_Thread *thread;
    SDL_Mutex *صف_قفل;
    SDL_Mutex *completion_قفل;
    SDL_Condition *cond;
    بنية wl_list jobs;
    Wayland_کار_ID id_counter;
    bool should_exit;
};

بنية Wayland_EventThreadContext
{
    SDL_Video_داده *wayland_داده_2;
    SDL_Thread *thread;
    بنية wl_event_صف *صف;
    SDL_Mutex *dispatch_قفل;
    bool should_exit;
};

ساكن فراغ handle_event_thread_exit(فراغ *داده, بنية wl_callback *wl_callback, uint32_t callback_داده)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)داده;
    wl_callback_destroy(wl_callback);
    context->should_exit = true;
}

ساكن ثابت بنية wl_callback_listener event_thread_exit_listener = {
    handle_event_thread_exit
};

ساكن صحيح SDLCALL Wayland_EventThreadFunc(فراغ *داده)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)داده;
    بنية wl_display *display = context->wayland_داده_2->display;
    ثابت صحيح display_fd = WAYLAND_wl_display_get_fd(display);
    صحيح ret;

    /* The lock must be held whenever dispatching to avoid a race condition when adding
     * or destroying objects using the queue.
     *
     * Any error other than EAGAIN is fatal and causes the thread to exit.
     */
    طالما (!context->should_exit) {
        إذا (WAYLAND_wl_display_prepare_read_صف(display, context->صف) == 0) {
            Sint64 timeoutNS = -1;

            ret = WAYLAND_wl_display_flush(display);

            إذا (ret < 0) {
                إذا (errno == EAGAIN) {
                    // If the flush failed with EAGAIN, don't block as not to inhibit other threads from reading events.
                    timeoutNS = SDL_MS_مقصد_NS(1);
                } وإلا {
                    WAYLAND_wl_display_cancel_read(display);
                    أرجع -1;
                }
            }

            // Wait for a read/write operation to become possible.
            ret = SDL_IOReady(display_fd, SDL_IOR_READ, timeoutNS);

            إذا (ret <= 0) {
                WAYLAND_wl_display_cancel_read(display);
                إذا (ret < 0) {
                    أرجع -1;
                }

                // Nothing to read, and woke to flush; try again.
                استمر;
            }

            ret = WAYLAND_wl_display_read_events(display);
            إذا (ret == -1) {
                أرجع -1;
            }
        }

        SDL_قفل_Mutex(context->dispatch_قفل);
        ret = WAYLAND_wl_display_dispatch_صف_pending(display, context->صف);
        SDL_UnlockMutex(context->dispatch_قفل);

        إذا (ret < 0) {
            أرجع -1;
        }
    }

    أرجع 0;
}

Wayland_EventThreadContext *Wayland_CreateEventThread(SDL_Video_داده *داده, ثابت حرف *صف_name)
{
    Wayland_EventThreadContext *context = SDL_calloc(1, حجم(Wayland_EventThreadContext));
    إذا (!context) {
        أرجع عدم;
    }

    context->wayland_داده_2 = داده;
    context->صف = Wayland_Display_Create_صف(داده->display, صف_name);
    إذا (!context->صف) {
        اذهب cleanup;
    }

    context->dispatch_قفل = SDL_CreateMutex();
    إذا (!context->dispatch_قفل) {
        اذهب cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_EventThreadFunc, "wl_event_thread", context);
    إذا (!context->thread) {
        اذهب cleanup;
    }

    أرجع context;

cleanup:
    إذا (context->dispatch_قفل) {
        SDL_DestroyMutex(context->dispatch_قفل);
    }

    إذا (context->صف) {
        WAYLAND_wl_event_صف_destroy(context->صف);
    }

    SDL_free(context);
    أرجع عدم;
}

فراغ Wayland_DestroyEventThread(Wayland_EventThreadContext *context)
{
    إذا (context) {
        // Dispatch the exit event to unblock the thread and signal it to exit.
        بنية wl_display *display = context->wayland_داده_2->display;
        بنية wl_proxy *display_wrapper = Wayland_CreateEventThreadProxyWrapper(context, display);

        SDL_قفل_Mutex(context->dispatch_قفل);
        بنية wl_callback *cb = wl_display_sync((بنية wl_display *)display_wrapper);
        wl_callback_جمع_کن_listener(cb, &event_thread_exit_listener, context);
        SDL_UnlockMutex(context->dispatch_قفل);

        WAYLAND_wl_proxy_wrapper_destroy(display_wrapper);

        صحيح ret = WAYLAND_wl_display_flush(display);
        طالما (ret == -1 && errno == EAGAIN) {
            // Shutting down the thread requires a successful flush.
            ret = SDL_IOReady(WAYLAND_wl_display_get_fd(display), SDL_IOR_WRITE, -1);
            إذا (ret >= 0) {
                ret = WAYLAND_wl_display_flush(display);
            }
        }

        // Avoid a warning if the flush failed due to a broken connection.
        إذا (ret < 0) {
            wl_callback_destroy(cb);
        }

        // Wait for the thread to return; it will exit automatically on a broken connection.
        SDL_WaitThread(context->thread, عدم);

        WAYLAND_wl_event_صف_destroy(context->صف);
        SDL_DestroyMutex(context->dispatch_قفل);
        SDL_free(context);
    }
}

فراغ *Wayland_CreateEventThreadProxyWrapper(Wayland_EventThreadContext *context, فراغ *obj)
{
    بنية wl_proxy *wrapper = WAYLAND_wl_proxy_create_wrapper(obj);
    إذا (wrapper && context) {
        WAYLAND_wl_proxy_مجموعه_صف(wrapper, context->صف);
    }

    أرجع wrapper;
}

فراغ Wayland_قفل_Event_Thread(Wayland_EventThreadContext *context)
{
    إذا (context) {
        SDL_قفل_Mutex(context->dispatch_قفل);
    }
}

فراغ Wayland_UnlockEventThread(Wayland_EventThreadContext *context)
{
    إذا (context) {
        SDL_UnlockMutex(context->dispatch_قفل);
    }
}

ساكن صحيح SDLCALL Wayland_کار_Thread_Func(فراغ *داده)
{
    Wayland_کار_Thread_Context *context = (Wayland_کار_Thread_Context *)داده;

    SDL_قفل_Mutex(context->صف_قفل);
    طالما (!context->should_exit) {
        إذا (WAYLAND_wl_list_خالی(&context->jobs)) {
            SDL_WaitCondition(context->cond, context->صف_قفل);
        }

        Wayland_کار *کار, *کار_موقت;
        wl_list_for_each_امن (کار, کار_موقت, &context->jobs, link) {
            إذا (کار->وضعیت == کار_وضعیت_انتظار) {
                کار->وضعیت = کار_وضعیت_RUNNING;
            }

            // Don't block queue operations while dispatching the job.
            SDL_UnlockMutex(context->صف_قفل);

            // If the job was cancelled, just remove it.
            إذا (کار->وضعیت == کار_وضعیت_RUNNING) {
                کار->callback(کار->userdata);

                // Signal completion to the waiting thread.
                SDL_قفل_Mutex(context->completion_قفل);
                إذا (کار->وضعیت == کار_وضعیت_SIGNAL_PENDING) {
                    SDL_SignalCondition(context->cond);
                }
                کار->وضعیت = کار_وضعیت_SIGNALED;
                SDL_UnlockMutex(context->completion_قفل);
            }

            SDL_قفل_Mutex(context->صف_قفل);

            WAYLAND_wl_list_remove(&کار->link);
            SDL_free(کار);
        }
    }
    SDL_UnlockMutex(context->صف_قفل);

    أرجع 0;
}

خارجي Wayland_کار_Thread_Context *Wayland_Create_کار_Thread()
{
    Wayland_کار_Thread_Context *context = SDL_calloc(1, حجم(Wayland_کار_Thread_Context));
    إذا (!context) {
        أرجع عدم;
    }

    WAYLAND_wl_list_init(&context->jobs);

    context->صف_قفل = SDL_CreateMutex();
    إذا (!context->صف_قفل) {
        اذهب cleanup;
    }

    context->completion_قفل = SDL_CreateMutex();
    إذا (!context->completion_قفل) {
        اذهب cleanup;
    }

    context->cond = SDL_CreateCondition();
    إذا (!context->cond) {
        اذهب cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_کار_Thread_Func, "wl_job_thread", context);
    إذا (!context->thread) {
        اذهب cleanup;
    }

    أرجع context;

cleanup:
    إذا (context->صف_قفل) {
        SDL_DestroyMutex(context->صف_قفل);
    }

    إذا (context->completion_قفل) {
        SDL_DestroyMutex(context->completion_قفل);
    }

    إذا (context->cond) {
        SDL_DestroyCondition(context->cond);
    }

    SDL_free(context);

    أرجع عدم;
}

ساكن فراغ کار_thread_exit(فراغ *داده)
{
    Wayland_کار_Thread_Context *context = (Wayland_کار_Thread_Context *)داده;
    context->should_exit = true;
}

خارجي فراغ Wayland_Destroy_کار_Thread(Wayland_کار_Thread_Context *context)
{
    إذا (!context) {
        أرجع;
    }

    // Dispatch the exit job to unblock the thread and set the exit condition.
    Wayland_کار_Thread_جمع_کن_کار(context, کار_thread_exit, context, عدم);

    // Wait for the thread to return; all jobs will be complete at this point.
    SDL_WaitThread(context->thread, عدم);

    // Cleanup.
    SDL_DestroyCondition(context->cond);
    SDL_DestroyMutex(context->صف_قفل);
    SDL_DestroyMutex(context->completion_قفل);
    SDL_free(context);
}

bool Wayland_کار_Thread_جمع_کن_کار(Wayland_کار_Thread_Context *context, Wayland_کار_Thread_Callback callback, فراغ *userdata, Wayland_کار_ID *id)
{
    إذا (!callback) {
        أرجع false;
    }

    إذا (context) {
        SDL_قفل_Mutex(context->صف_قفل);
        Wayland_کار *کار = SDL_calloc(1, حجم(Wayland_کار));
        إذا (کار) {
            کار->id = context->id_counter++;
            إذا (id) {
                *id = کار->id;
            }

            کار->callback = callback;
            کار->userdata = userdata;

            WAYLAND_wl_list_درج(context->jobs.prev, &کار->link);

            SDL_SignalCondition(context->cond);
            SDL_UnlockMutex(context->صف_قفل);

            أرجع true;
        }

        SDL_UnlockMutex(context->صف_قفل);
        أرجع false;
    } وإلا {
        // No thread? Just run the job.
        callback(userdata);
    }

    أرجع true;
}

فراغ Wayland_کار_Thread_Cancel_کار(Wayland_کار_Thread_Context *context, Wayland_کار_ID id)
{
    إذا (!context) {
        أرجع;
    }

    SDL_قفل_Mutex(context->صف_قفل);

    Wayland_کار *کار;
    wl_list_for_each (کار, &context->jobs, link) {
        إذا (کار->id == id) {
            SDL_قفل_Mutex(context->completion_قفل);
            إذا (کار->وضعیت == کار_وضعیت_انتظار) {
                // In the queue, waiting to run; mark as cancelled.
                کار->وضعیت = کار_وضعیت_CANCELED;
            } وإلا إذا (کار->وضعیت == کار_وضعیت_RUNNING) {
                // The job is running; wait for completion.
                کار->وضعیت = کار_وضعیت_SIGNAL_PENDING;
                SDL_WaitCondition(context->cond, context->completion_قفل);
            }
            SDL_UnlockMutex(context->completion_قفل);
            اكسر;
        }
    }

    SDL_UnlockMutex(context->صف_قفل);
}

#پایان_اگر // SDL_VIDEO_DRIVER_WAYLAND

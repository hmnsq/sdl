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

#که_تعریف_شوی SDL_VIDEO_DRIVER_WAYLAND

#ضمن "../../core/unix/SDL_poll.h"
#ضمن "SDL_waylandeventthread.h"
#ضمن "SDL_waylandvideo.h"

#ضمن <errno.h>

تعريفنوع تعداد Wayland_دنده_حالت
{
    دنده_حالت_انتظار = 0,
    دنده_حالت_RUNNING,
    دنده_حالت_SIGNAL_PENDING,
    دنده_حالت_SIGNALED,
    دنده_حالت_CANCELED
} Wayland_دنده_حالت;

تعريفنوع بنية Wayland_دنده
{
    Wayland_دنده_Thread_Callback callback;
    فراغ *userdata;
    Wayland_دنده_ID id;
    Wayland_دنده_حالت حالت;

    بنية wl_list link;
} Wayland_دنده;

بنية Wayland_دنده_Thread_Context
{
    SDL_Thread *thread;
    SDL_Mutex *کتار_قلف;
    SDL_Mutex *completion_قلف;
    SDL_Condition *cond;
    بنية wl_list jobs;
    Wayland_دنده_ID id_counter;
    bool should_exit;
};

بنية Wayland_EventThreadContext
{
    SDL_Video_معلومات *wayland_معلومات_2;
    SDL_Thread *thread;
    بنية wl_event_کتار *کتار;
    SDL_Mutex *dispatch_قلف;
    bool should_exit;
};

ساكن فراغ handle_event_thread_exit(فراغ *معلومات, بنية wl_callback *wl_callback, uint32_t callback_معلومات)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)معلومات;
    wl_callback_destroy(wl_callback);
    context->should_exit = true;
}

ساكن ثابت بنية wl_callback_listener event_thread_exit_listener = {
    handle_event_thread_exit
};

ساكن صحيح SDLCALL Wayland_EventThreadFunc(فراغ *معلومات)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)معلومات;
    بنية wl_display *display = context->wayland_معلومات_2->display;
    ثابت صحيح display_fd = WAYLAND_wl_display_get_fd(display);
    صحيح ret;

    /* The lock must be held whenever dispatching to avoid a race condition when adding
     * or destroying objects using the queue.
     *
     * Any error other than EAGAIN is fatal and causes the thread to exit.
     */
    طالما (!context->should_exit) {
        إذا (WAYLAND_wl_display_prepare_read_کتار(display, context->کتار) == 0) {
            Sint64 timeoutNS = -1;

            ret = WAYLAND_wl_display_flush(display);

            إذا (ret < 0) {
                إذا (errno == EAGAIN) {
                    // If the flush failed with EAGAIN, don't block as not to inhibit other threads from reading events.
                    timeoutNS = SDL_MS_منزل_NS(1);
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

        SDL_قلف_Mutex(context->dispatch_قلف);
        ret = WAYLAND_wl_display_dispatch_کتار_pending(display, context->کتار);
        SDL_UnlockMutex(context->dispatch_قلف);

        إذا (ret < 0) {
            أرجع -1;
        }
    }

    أرجع 0;
}

Wayland_EventThreadContext *Wayland_CreateEventThread(SDL_Video_معلومات *معلومات, ثابت حرف *کتار_name)
{
    Wayland_EventThreadContext *context = SDL_calloc(1, حجم(Wayland_EventThreadContext));
    إذا (!context) {
        أرجع عدم;
    }

    context->wayland_معلومات_2 = معلومات;
    context->کتار = Wayland_Display_Create_کتار(معلومات->display, کتار_name);
    إذا (!context->کتار) {
        اذهب cleanup;
    }

    context->dispatch_قلف = SDL_CreateMutex();
    إذا (!context->dispatch_قلف) {
        اذهب cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_EventThreadFunc, "wl_event_thread", context);
    إذا (!context->thread) {
        اذهب cleanup;
    }

    أرجع context;

cleanup:
    إذا (context->dispatch_قلف) {
        SDL_DestroyMutex(context->dispatch_قلف);
    }

    إذا (context->کتار) {
        WAYLAND_wl_event_کتار_destroy(context->کتار);
    }

    SDL_free(context);
    أرجع عدم;
}

فراغ Wayland_DestroyEventThread(Wayland_EventThreadContext *context)
{
    إذا (context) {
        // Dispatch the exit event to unblock the thread and signal it to exit.
        بنية wl_display *display = context->wayland_معلومات_2->display;
        بنية wl_proxy *display_wrapper = Wayland_CreateEventThreadProxyWrapper(context, display);

        SDL_قلف_Mutex(context->dispatch_قلف);
        بنية wl_callback *cb = wl_display_sync((بنية wl_display *)display_wrapper);
        wl_callback_جمع_کړه_listener(cb, &event_thread_exit_listener, context);
        SDL_UnlockMutex(context->dispatch_قلف);

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

        WAYLAND_wl_event_کتار_destroy(context->کتار);
        SDL_DestroyMutex(context->dispatch_قلف);
        SDL_free(context);
    }
}

فراغ *Wayland_CreateEventThreadProxyWrapper(Wayland_EventThreadContext *context, فراغ *obj)
{
    بنية wl_proxy *wrapper = WAYLAND_wl_proxy_create_wrapper(obj);
    إذا (wrapper && context) {
        WAYLAND_wl_proxy_سېټ_کتار(wrapper, context->کتار);
    }

    أرجع wrapper;
}

فراغ Wayland_قلف_Event_Thread(Wayland_EventThreadContext *context)
{
    إذا (context) {
        SDL_قلف_Mutex(context->dispatch_قلف);
    }
}

فراغ Wayland_UnlockEventThread(Wayland_EventThreadContext *context)
{
    إذا (context) {
        SDL_UnlockMutex(context->dispatch_قلف);
    }
}

ساكن صحيح SDLCALL Wayland_دنده_Thread_Func(فراغ *معلومات)
{
    Wayland_دنده_Thread_Context *context = (Wayland_دنده_Thread_Context *)معلومات;

    SDL_قلف_Mutex(context->کتار_قلف);
    طالما (!context->should_exit) {
        إذا (WAYLAND_wl_list_تشه(&context->jobs)) {
            SDL_WaitCondition(context->cond, context->کتار_قلف);
        }

        Wayland_دنده *دنده, *دنده_لنډمهاله;
        wl_list_for_each_خوندي (دنده, دنده_لنډمهاله, &context->jobs, link) {
            إذا (دنده->حالت == دنده_حالت_انتظار) {
                دنده->حالت = دنده_حالت_RUNNING;
            }

            // Don't block queue operations while dispatching the job.
            SDL_UnlockMutex(context->کتار_قلف);

            // If the job was cancelled, just remove it.
            إذا (دنده->حالت == دنده_حالت_RUNNING) {
                دنده->callback(دنده->userdata);

                // Signal completion to the waiting thread.
                SDL_قلف_Mutex(context->completion_قلف);
                إذا (دنده->حالت == دنده_حالت_SIGNAL_PENDING) {
                    SDL_SignalCondition(context->cond);
                }
                دنده->حالت = دنده_حالت_SIGNALED;
                SDL_UnlockMutex(context->completion_قلف);
            }

            SDL_قلف_Mutex(context->کتار_قلف);

            WAYLAND_wl_list_remove(&دنده->link);
            SDL_free(دنده);
        }
    }
    SDL_UnlockMutex(context->کتار_قلف);

    أرجع 0;
}

خارجي Wayland_دنده_Thread_Context *Wayland_Create_دنده_Thread()
{
    Wayland_دنده_Thread_Context *context = SDL_calloc(1, حجم(Wayland_دنده_Thread_Context));
    إذا (!context) {
        أرجع عدم;
    }

    WAYLAND_wl_list_init(&context->jobs);

    context->کتار_قلف = SDL_CreateMutex();
    إذا (!context->کتار_قلف) {
        اذهب cleanup;
    }

    context->completion_قلف = SDL_CreateMutex();
    إذا (!context->completion_قلف) {
        اذهب cleanup;
    }

    context->cond = SDL_CreateCondition();
    إذا (!context->cond) {
        اذهب cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_دنده_Thread_Func, "wl_job_thread", context);
    إذا (!context->thread) {
        اذهب cleanup;
    }

    أرجع context;

cleanup:
    إذا (context->کتار_قلف) {
        SDL_DestroyMutex(context->کتار_قلف);
    }

    إذا (context->completion_قلف) {
        SDL_DestroyMutex(context->completion_قلف);
    }

    إذا (context->cond) {
        SDL_DestroyCondition(context->cond);
    }

    SDL_free(context);

    أرجع عدم;
}

ساكن فراغ دنده_thread_exit(فراغ *معلومات)
{
    Wayland_دنده_Thread_Context *context = (Wayland_دنده_Thread_Context *)معلومات;
    context->should_exit = true;
}

خارجي فراغ Wayland_Destroy_دنده_Thread(Wayland_دنده_Thread_Context *context)
{
    إذا (!context) {
        أرجع;
    }

    // Dispatch the exit job to unblock the thread and set the exit condition.
    Wayland_دنده_Thread_جمع_کړه_دنده(context, دنده_thread_exit, context, عدم);

    // Wait for the thread to return; all jobs will be complete at this point.
    SDL_WaitThread(context->thread, عدم);

    // Cleanup.
    SDL_DestroyCondition(context->cond);
    SDL_DestroyMutex(context->کتار_قلف);
    SDL_DestroyMutex(context->completion_قلف);
    SDL_free(context);
}

bool Wayland_دنده_Thread_جمع_کړه_دنده(Wayland_دنده_Thread_Context *context, Wayland_دنده_Thread_Callback callback, فراغ *userdata, Wayland_دنده_ID *id)
{
    إذا (!callback) {
        أرجع false;
    }

    إذا (context) {
        SDL_قلف_Mutex(context->کتار_قلف);
        Wayland_دنده *دنده = SDL_calloc(1, حجم(Wayland_دنده));
        إذا (دنده) {
            دنده->id = context->id_counter++;
            إذا (id) {
                *id = دنده->id;
            }

            دنده->callback = callback;
            دنده->userdata = userdata;

            WAYLAND_wl_list_ورننباسه(context->jobs.prev, &دنده->link);

            SDL_SignalCondition(context->cond);
            SDL_UnlockMutex(context->کتار_قلف);

            أرجع true;
        }

        SDL_UnlockMutex(context->کتار_قلف);
        أرجع false;
    } وإلا {
        // No thread? Just run the job.
        callback(userdata);
    }

    أرجع true;
}

فراغ Wayland_دنده_Thread_Cancel_دنده(Wayland_دنده_Thread_Context *context, Wayland_دنده_ID id)
{
    إذا (!context) {
        أرجع;
    }

    SDL_قلف_Mutex(context->کتار_قلف);

    Wayland_دنده *دنده;
    wl_list_for_each (دنده, &context->jobs, link) {
        إذا (دنده->id == id) {
            SDL_قلف_Mutex(context->completion_قلف);
            إذا (دنده->حالت == دنده_حالت_انتظار) {
                // In the queue, waiting to run; mark as cancelled.
                دنده->حالت = دنده_حالت_CANCELED;
            } وإلا إذا (دنده->حالت == دنده_حالت_RUNNING) {
                // The job is running; wait for completion.
                دنده->حالت = دنده_حالت_SIGNAL_PENDING;
                SDL_WaitCondition(context->cond, context->completion_قلف);
            }
            SDL_UnlockMutex(context->completion_قلف);
            اكسر;
        }
    }

    SDL_UnlockMutex(context->کتار_قلف);
}

#د_که_پای // SDL_VIDEO_DRIVER_WAYLAND

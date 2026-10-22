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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_WAYLAND

#ضمن "../../core/unix/SDL_poll.h"
#ضمن "SDL_waylandeventthread.h"
#ضمن "SDL_waylandvideo.h"

#ضمن <errno.h>

تعريفنوع تعداد Wayland_ڪم_حالت
{
    ڪم_حالت_انتظار = 0,
    ڪم_حالت_RUNNING,
    ڪم_حالت_SIGNAL_PENDING,
    ڪم_حالت_SIGNALED,
    ڪم_حالت_CANCELED
} Wayland_ڪم_حالت;

تعريفنوع بنية Wayland_ڪم
{
    Wayland_ڪم_Thread_Callback callback;
    فراغ *userdata;
    Wayland_ڪم_ID id;
    Wayland_ڪم_حالت حالت;

    بنية wl_list link;
} Wayland_ڪم;

بنية Wayland_ڪم_Thread_Context
{
    SDL_Thread *thread;
    SDL_Mutex *قطار_تالو;
    SDL_Mutex *completion_تالو;
    SDL_Condition *cond;
    بنية wl_list jobs;
    Wayland_ڪم_ID id_counter;
    bool should_exit;
};

بنية Wayland_EventThreadContext
{
    SDL_Video_معلومات *wayland_معلومات_2;
    SDL_Thread *thread;
    بنية wl_event_قطار *قطار;
    SDL_Mutex *dispatch_تالو;
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
        إذا (WAYLAND_wl_display_prepare_read_قطار(display, context->قطار) == 0) {
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

        SDL_تالو_Mutex(context->dispatch_تالو);
        ret = WAYLAND_wl_display_dispatch_قطار_pending(display, context->قطار);
        SDL_UnlockMutex(context->dispatch_تالو);

        إذا (ret < 0) {
            أرجع -1;
        }
    }

    أرجع 0;
}

Wayland_EventThreadContext *Wayland_CreateEventThread(SDL_Video_معلومات *معلومات, ثابت حرف *قطار_name)
{
    Wayland_EventThreadContext *context = SDL_calloc(1, حجم(Wayland_EventThreadContext));
    إذا (!context) {
        أرجع عدم;
    }

    context->wayland_معلومات_2 = معلومات;
    context->قطار = Wayland_Display_Create_قطار(معلومات->display, قطار_name);
    إذا (!context->قطار) {
        اذهب cleanup;
    }

    context->dispatch_تالو = SDL_CreateMutex();
    إذا (!context->dispatch_تالو) {
        اذهب cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_EventThreadFunc, "wl_event_thread", context);
    إذا (!context->thread) {
        اذهب cleanup;
    }

    أرجع context;

cleanup:
    إذا (context->dispatch_تالو) {
        SDL_DestroyMutex(context->dispatch_تالو);
    }

    إذا (context->قطار) {
        WAYLAND_wl_event_قطار_destroy(context->قطار);
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

        SDL_تالو_Mutex(context->dispatch_تالو);
        بنية wl_callback *cb = wl_display_sync((بنية wl_display *)display_wrapper);
        wl_callback_جوڙيو_listener(cb, &event_thread_exit_listener, context);
        SDL_UnlockMutex(context->dispatch_تالو);

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

        WAYLAND_wl_event_قطار_destroy(context->قطار);
        SDL_DestroyMutex(context->dispatch_تالو);
        SDL_free(context);
    }
}

فراغ *Wayland_CreateEventThreadProxyWrapper(Wayland_EventThreadContext *context, فراغ *obj)
{
    بنية wl_proxy *wrapper = WAYLAND_wl_proxy_create_wrapper(obj);
    إذا (wrapper && context) {
        WAYLAND_wl_proxy_سيٽ_قطار(wrapper, context->قطار);
    }

    أرجع wrapper;
}

فراغ Wayland_تالو_Event_Thread(Wayland_EventThreadContext *context)
{
    إذا (context) {
        SDL_تالو_Mutex(context->dispatch_تالو);
    }
}

فراغ Wayland_UnlockEventThread(Wayland_EventThreadContext *context)
{
    إذا (context) {
        SDL_UnlockMutex(context->dispatch_تالو);
    }
}

ساكن صحيح SDLCALL Wayland_ڪم_Thread_Func(فراغ *معلومات)
{
    Wayland_ڪم_Thread_Context *context = (Wayland_ڪم_Thread_Context *)معلومات;

    SDL_تالو_Mutex(context->قطار_تالو);
    طالما (!context->should_exit) {
        إذا (WAYLAND_wl_list_خالي_جايون(&context->jobs)) {
            SDL_WaitCondition(context->cond, context->قطار_تالو);
        }

        Wayland_ڪم *ڪم, *ڪم_عارضي;
        wl_list_for_each_محفوظ (ڪم, ڪم_عارضي, &context->jobs, link) {
            إذا (ڪم->حالت == ڪم_حالت_انتظار) {
                ڪم->حالت = ڪم_حالت_RUNNING;
            }

            // Don't block queue operations while dispatching the job.
            SDL_UnlockMutex(context->قطار_تالو);

            // If the job was cancelled, just remove it.
            إذا (ڪم->حالت == ڪم_حالت_RUNNING) {
                ڪم->callback(ڪم->userdata);

                // Signal completion to the waiting thread.
                SDL_تالو_Mutex(context->completion_تالو);
                إذا (ڪم->حالت == ڪم_حالت_SIGNAL_PENDING) {
                    SDL_SignalCondition(context->cond);
                }
                ڪم->حالت = ڪم_حالت_SIGNALED;
                SDL_UnlockMutex(context->completion_تالو);
            }

            SDL_تالو_Mutex(context->قطار_تالو);

            WAYLAND_wl_list_remove(&ڪم->link);
            SDL_free(ڪم);
        }
    }
    SDL_UnlockMutex(context->قطار_تالو);

    أرجع 0;
}

خارجي Wayland_ڪم_Thread_Context *Wayland_Create_ڪم_Thread()
{
    Wayland_ڪم_Thread_Context *context = SDL_calloc(1, حجم(Wayland_ڪم_Thread_Context));
    إذا (!context) {
        أرجع عدم;
    }

    WAYLAND_wl_list_init(&context->jobs);

    context->قطار_تالو = SDL_CreateMutex();
    إذا (!context->قطار_تالو) {
        اذهب cleanup;
    }

    context->completion_تالو = SDL_CreateMutex();
    إذا (!context->completion_تالو) {
        اذهب cleanup;
    }

    context->cond = SDL_CreateCondition();
    إذا (!context->cond) {
        اذهب cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_ڪم_Thread_Func, "wl_job_thread", context);
    إذا (!context->thread) {
        اذهب cleanup;
    }

    أرجع context;

cleanup:
    إذا (context->قطار_تالو) {
        SDL_DestroyMutex(context->قطار_تالو);
    }

    إذا (context->completion_تالو) {
        SDL_DestroyMutex(context->completion_تالو);
    }

    إذا (context->cond) {
        SDL_DestroyCondition(context->cond);
    }

    SDL_free(context);

    أرجع عدم;
}

ساكن فراغ ڪم_thread_exit(فراغ *معلومات)
{
    Wayland_ڪم_Thread_Context *context = (Wayland_ڪم_Thread_Context *)معلومات;
    context->should_exit = true;
}

خارجي فراغ Wayland_Destroy_ڪم_Thread(Wayland_ڪم_Thread_Context *context)
{
    إذا (!context) {
        أرجع;
    }

    // Dispatch the exit job to unblock the thread and set the exit condition.
    Wayland_ڪم_Thread_جوڙيو_ڪم(context, ڪم_thread_exit, context, عدم);

    // Wait for the thread to return; all jobs will be complete at this point.
    SDL_WaitThread(context->thread, عدم);

    // Cleanup.
    SDL_DestroyCondition(context->cond);
    SDL_DestroyMutex(context->قطار_تالو);
    SDL_DestroyMutex(context->completion_تالو);
    SDL_free(context);
}

bool Wayland_ڪم_Thread_جوڙيو_ڪم(Wayland_ڪم_Thread_Context *context, Wayland_ڪم_Thread_Callback callback, فراغ *userdata, Wayland_ڪم_ID *id)
{
    إذا (!callback) {
        أرجع false;
    }

    إذا (context) {
        SDL_تالو_Mutex(context->قطار_تالو);
        Wayland_ڪم *ڪم = SDL_calloc(1, حجم(Wayland_ڪم));
        إذا (ڪم) {
            ڪم->id = context->id_counter++;
            إذا (id) {
                *id = ڪم->id;
            }

            ڪم->callback = callback;
            ڪم->userdata = userdata;

            WAYLAND_wl_list_وجهو(context->jobs.prev, &ڪم->link);

            SDL_SignalCondition(context->cond);
            SDL_UnlockMutex(context->قطار_تالو);

            أرجع true;
        }

        SDL_UnlockMutex(context->قطار_تالو);
        أرجع false;
    } وإلا {
        // No thread? Just run the job.
        callback(userdata);
    }

    أرجع true;
}

فراغ Wayland_ڪم_Thread_Cancel_ڪم(Wayland_ڪم_Thread_Context *context, Wayland_ڪم_ID id)
{
    إذا (!context) {
        أرجع;
    }

    SDL_تالو_Mutex(context->قطار_تالو);

    Wayland_ڪم *ڪم;
    wl_list_for_each (ڪم, &context->jobs, link) {
        إذا (ڪم->id == id) {
            SDL_تالو_Mutex(context->completion_تالو);
            إذا (ڪم->حالت == ڪم_حالت_انتظار) {
                // In the queue, waiting to run; mark as cancelled.
                ڪم->حالت = ڪم_حالت_CANCELED;
            } وإلا إذا (ڪم->حالت == ڪم_حالت_RUNNING) {
                // The job is running; wait for completion.
                ڪم->حالت = ڪم_حالت_SIGNAL_PENDING;
                SDL_WaitCondition(context->cond, context->completion_تالو);
            }
            SDL_UnlockMutex(context->completion_تالو);
            اكسر;
        }
    }

    SDL_UnlockMutex(context->قطار_تالو);
}

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_WAYLAND

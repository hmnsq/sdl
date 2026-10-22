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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND

#ضمن "../../core/unix/SDL_poll.h"
#ضمن "SDL_waylandeventthread.h"
#ضمن "SDL_waylandvideo.h"

#ضمن <errno.h>

تعريفنوع تعداد Wayland_کم_حالت
{
    کم_حالت_اڈیک = 0,
    کم_حالت_RUNNING,
    کم_حالت_SIGNAL_PENDING,
    کم_حالت_SIGNALED,
    کم_حالت_CANCELED
} Wayland_کم_حالت;

تعريفنوع بنية Wayland_کم
{
    Wayland_کم_Thread_Callback callback;
    فراغ *userdata;
    Wayland_کم_ID id;
    Wayland_کم_حالت حالت;

    بنية wl_list link;
} Wayland_کم;

بنية Wayland_کم_Thread_Context
{
    SDL_Thread *thread;
    SDL_Mutex *قطار_جندرا;
    SDL_Mutex *completion_جندرا;
    SDL_Condition *cond;
    بنية wl_list jobs;
    Wayland_کم_ID id_counter;
    bool should_exit;
};

بنية Wayland_EventThreadContext
{
    SDL_Video_انکڑے *wayland_انکڑے_2;
    SDL_Thread *thread;
    بنية wl_event_قطار *قطار;
    SDL_Mutex *dispatch_جندرا;
    bool should_exit;
};

ساكن فراغ handle_event_thread_exit(فراغ *انکڑے, بنية wl_callback *wl_callback, uint32_t callback_انکڑے)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)انکڑے;
    wl_callback_destroy(wl_callback);
    context->should_exit = true;
}

ساكن ثابت بنية wl_callback_listener event_thread_exit_listener = {
    handle_event_thread_exit
};

ساكن صحيح SDLCALL Wayland_EventThreadFunc(فراغ *انکڑے)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)انکڑے;
    بنية wl_display *display = context->wayland_انکڑے_2->display;
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

        SDL_جندرا_Mutex(context->dispatch_جندرا);
        ret = WAYLAND_wl_display_dispatch_قطار_pending(display, context->قطار);
        SDL_UnlockMutex(context->dispatch_جندرا);

        إذا (ret < 0) {
            أرجع -1;
        }
    }

    أرجع 0;
}

Wayland_EventThreadContext *Wayland_CreateEventThread(SDL_Video_انکڑے *انکڑے, ثابت حرف *قطار_name)
{
    Wayland_EventThreadContext *context = SDL_calloc(1, حجم(Wayland_EventThreadContext));
    إذا (!context) {
        أرجع عدم;
    }

    context->wayland_انکڑے_2 = انکڑے;
    context->قطار = Wayland_Display_Create_قطار(انکڑے->display, قطار_name);
    إذا (!context->قطار) {
        اذهب cleanup;
    }

    context->dispatch_جندرا = SDL_CreateMutex();
    إذا (!context->dispatch_جندرا) {
        اذهب cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_EventThreadFunc, "wl_event_thread", context);
    إذا (!context->thread) {
        اذهب cleanup;
    }

    أرجع context;

cleanup:
    إذا (context->dispatch_جندرا) {
        SDL_DestroyMutex(context->dispatch_جندرا);
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
        بنية wl_display *display = context->wayland_انکڑے_2->display;
        بنية wl_proxy *display_wrapper = Wayland_CreateEventThreadProxyWrapper(context, display);

        SDL_جندرا_Mutex(context->dispatch_جندرا);
        بنية wl_callback *cb = wl_display_sync((بنية wl_display *)display_wrapper);
        wl_callback_جوڑو_listener(cb, &event_thread_exit_listener, context);
        SDL_UnlockMutex(context->dispatch_جندرا);

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
        SDL_DestroyMutex(context->dispatch_جندرا);
        SDL_free(context);
    }
}

فراغ *Wayland_CreateEventThreadProxyWrapper(Wayland_EventThreadContext *context, فراغ *obj)
{
    بنية wl_proxy *wrapper = WAYLAND_wl_proxy_create_wrapper(obj);
    إذا (wrapper && context) {
        WAYLAND_wl_proxy_سیٹ_قطار(wrapper, context->قطار);
    }

    أرجع wrapper;
}

فراغ Wayland_جندرا_Event_Thread(Wayland_EventThreadContext *context)
{
    إذا (context) {
        SDL_جندرا_Mutex(context->dispatch_جندرا);
    }
}

فراغ Wayland_UnlockEventThread(Wayland_EventThreadContext *context)
{
    إذا (context) {
        SDL_UnlockMutex(context->dispatch_جندرا);
    }
}

ساكن صحيح SDLCALL Wayland_کم_Thread_Func(فراغ *انکڑے)
{
    Wayland_کم_Thread_Context *context = (Wayland_کم_Thread_Context *)انکڑے;

    SDL_جندرا_Mutex(context->قطار_جندرا);
    طالما (!context->should_exit) {
        إذا (WAYLAND_wl_list_خالی_تھاواں(&context->jobs)) {
            SDL_WaitCondition(context->cond, context->قطار_جندرا);
        }

        Wayland_کم *کم, *کم_عارضی;
        wl_list_for_each_محفوظ (کم, کم_عارضی, &context->jobs, link) {
            إذا (کم->حالت == کم_حالت_اڈیک) {
                کم->حالت = کم_حالت_RUNNING;
            }

            // Don't block queue operations while dispatching the job.
            SDL_UnlockMutex(context->قطار_جندرا);

            // If the job was cancelled, just remove it.
            إذا (کم->حالت == کم_حالت_RUNNING) {
                کم->callback(کم->userdata);

                // Signal completion to the waiting thread.
                SDL_جندرا_Mutex(context->completion_جندرا);
                إذا (کم->حالت == کم_حالت_SIGNAL_PENDING) {
                    SDL_SignalCondition(context->cond);
                }
                کم->حالت = کم_حالت_SIGNALED;
                SDL_UnlockMutex(context->completion_جندرا);
            }

            SDL_جندرا_Mutex(context->قطار_جندرا);

            WAYLAND_wl_list_remove(&کم->link);
            SDL_free(کم);
        }
    }
    SDL_UnlockMutex(context->قطار_جندرا);

    أرجع 0;
}

خارجي Wayland_کم_Thread_Context *Wayland_Create_کم_Thread()
{
    Wayland_کم_Thread_Context *context = SDL_calloc(1, حجم(Wayland_کم_Thread_Context));
    إذا (!context) {
        أرجع عدم;
    }

    WAYLAND_wl_list_init(&context->jobs);

    context->قطار_جندرا = SDL_CreateMutex();
    إذا (!context->قطار_جندرا) {
        اذهب cleanup;
    }

    context->completion_جندرا = SDL_CreateMutex();
    إذا (!context->completion_جندرا) {
        اذهب cleanup;
    }

    context->cond = SDL_CreateCondition();
    إذا (!context->cond) {
        اذهب cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_کم_Thread_Func, "wl_job_thread", context);
    إذا (!context->thread) {
        اذهب cleanup;
    }

    أرجع context;

cleanup:
    إذا (context->قطار_جندرا) {
        SDL_DestroyMutex(context->قطار_جندرا);
    }

    إذا (context->completion_جندرا) {
        SDL_DestroyMutex(context->completion_جندرا);
    }

    إذا (context->cond) {
        SDL_DestroyCondition(context->cond);
    }

    SDL_free(context);

    أرجع عدم;
}

ساكن فراغ کم_thread_exit(فراغ *انکڑے)
{
    Wayland_کم_Thread_Context *context = (Wayland_کم_Thread_Context *)انکڑے;
    context->should_exit = true;
}

خارجي فراغ Wayland_Destroy_کم_Thread(Wayland_کم_Thread_Context *context)
{
    إذا (!context) {
        أرجع;
    }

    // Dispatch the exit job to unblock the thread and set the exit condition.
    Wayland_کم_Thread_جوڑو_کم(context, کم_thread_exit, context, عدم);

    // Wait for the thread to return; all jobs will be complete at this point.
    SDL_WaitThread(context->thread, عدم);

    // Cleanup.
    SDL_DestroyCondition(context->cond);
    SDL_DestroyMutex(context->قطار_جندرا);
    SDL_DestroyMutex(context->completion_جندرا);
    SDL_free(context);
}

bool Wayland_کم_Thread_جوڑو_کم(Wayland_کم_Thread_Context *context, Wayland_کم_Thread_Callback callback, فراغ *userdata, Wayland_کم_ID *id)
{
    إذا (!callback) {
        أرجع false;
    }

    إذا (context) {
        SDL_جندرا_Mutex(context->قطار_جندرا);
        Wayland_کم *کم = SDL_calloc(1, حجم(Wayland_کم));
        إذا (کم) {
            کم->id = context->id_counter++;
            إذا (id) {
                *id = کم->id;
            }

            کم->callback = callback;
            کم->userdata = userdata;

            WAYLAND_wl_list_داخل_کرو(context->jobs.prev, &کم->link);

            SDL_SignalCondition(context->cond);
            SDL_UnlockMutex(context->قطار_جندرا);

            أرجع true;
        }

        SDL_UnlockMutex(context->قطار_جندرا);
        أرجع false;
    } وإلا {
        // No thread? Just run the job.
        callback(userdata);
    }

    أرجع true;
}

فراغ Wayland_کم_Thread_Cancel_کم(Wayland_کم_Thread_Context *context, Wayland_کم_ID id)
{
    إذا (!context) {
        أرجع;
    }

    SDL_جندرا_Mutex(context->قطار_جندرا);

    Wayland_کم *کم;
    wl_list_for_each (کم, &context->jobs, link) {
        إذا (کم->id == id) {
            SDL_جندرا_Mutex(context->completion_جندرا);
            إذا (کم->حالت == کم_حالت_اڈیک) {
                // In the queue, waiting to run; mark as cancelled.
                کم->حالت = کم_حالت_CANCELED;
            } وإلا إذا (کم->حالت == کم_حالت_RUNNING) {
                // The job is running; wait for completion.
                کم->حالت = کم_حالت_SIGNAL_PENDING;
                SDL_WaitCondition(context->cond, context->completion_جندرا);
            }
            SDL_UnlockMutex(context->completion_جندرا);
            اكسر;
        }
    }

    SDL_UnlockMutex(context->قطار_جندرا);
}

#جے_انت // SDL_VIDEO_DRIVER_WAYLAND

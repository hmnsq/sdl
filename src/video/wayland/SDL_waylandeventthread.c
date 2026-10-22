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

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_WAYLAND

#شامل "../../core/unix/SDL_poll.h"
#شامل "SDL_waylandeventthread.h"
#شامل "SDL_waylandvideo.h"

#شامل <errno.h>

قسمتعریف شمار Wayland_کام_حالت
{
    کام_حالت_انتظار = 0,
    کام_حالت_RUNNING,
    کام_حالت_SIGNAL_PENDING,
    کام_حالت_SIGNALED,
    کام_حالت_CANCELED
} Wayland_کام_حالت;

قسمتعریف ساخت Wayland_کام
{
    Wayland_کام_Thread_Callback callback;
    خالی *userdata;
    Wayland_کام_ID id;
    Wayland_کام_حالت حالت_2;

    ساخت wl_list link;
} Wayland_کام;

ساخت Wayland_کام_Thread_Context
{
    SDL_Thread *thread;
    SDL_Mutex *قطار_تالا;
    SDL_Mutex *completion_تالا;
    SDL_Condition *cond;
    ساخت wl_list jobs;
    Wayland_کام_ID id_شمار;
    bool should_exit;
};

ساخت Wayland_EventThreadContext
{
    SDL_Video_ڈیٹا *wayland_ڈیٹا_2;
    SDL_Thread *thread;
    ساخت wl_event_قطار *قطار;
    SDL_Mutex *dispatch_تالا;
    bool should_exit;
};

ساکن خالی handle_event_thread_exit(خالی *ڈیٹا, ساخت wl_callback *wl_callback, uint32_t callback_ڈیٹا)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)ڈیٹا;
    wl_callback_destroy(wl_callback);
    context->should_exit = true;
}

ساکن ثابت ساخت wl_callback_listener event_thread_exit_listener = {
    handle_event_thread_exit
};

ساکن صحیح SDLCALL Wayland_EventThreadFunc(خالی *ڈیٹا)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)ڈیٹا;
    ساخت wl_display *display = context->wayland_ڈیٹا_2->display;
    ثابت صحیح display_fd = WAYLAND_wl_display_get_fd(display);
    صحیح ret;

    /* The lock must be held whenever dispatching to avoid a race condition when adding
     * or destroying objects using the queue.
     *
     * Any error other than EAGAIN is fatal and causes the thread to exit.
     */
    جب (!context->should_exit) {
        اگر (WAYLAND_wl_display_prepare_read_قطار(display, context->قطار) == 0) {
            Sint64 timeoutNS = -1;

            ret = WAYLAND_wl_display_flush(display);

            اگر (ret < 0) {
                اگر (errno == EAGAIN) {
                    // If the flush failed with EAGAIN, don't block as not to inhibit other threads from reading events.
                    timeoutNS = SDL_MS_مقصد_NS(1);
                } ورنہ {
                    WAYLAND_wl_display_cancel_read(display);
                    واپس -1;
                }
            }

            // Wait for a read/write operation to become possible.
            ret = SDL_IOReady(display_fd, SDL_IOR_READ, timeoutNS);

            اگر (ret <= 0) {
                WAYLAND_wl_display_cancel_read(display);
                اگر (ret < 0) {
                    واپس -1;
                }

                // Nothing to read, and woke to flush; try again.
                جاری;
            }

            ret = WAYLAND_wl_display_read_events(display);
            اگر (ret == -1) {
                واپس -1;
            }
        }

        SDL_تالا_Mutex(context->dispatch_تالا);
        ret = WAYLAND_wl_display_dispatch_قطار_pending(display, context->قطار);
        SDL_UnlockMutex(context->dispatch_تالا);

        اگر (ret < 0) {
            واپس -1;
        }
    }

    واپس 0;
}

Wayland_EventThreadContext *Wayland_CreateEventThread(SDL_Video_ڈیٹا *ڈیٹا, ثابت حرف *قطار_name)
{
    Wayland_EventThreadContext *context = SDL_calloc(1, حجم(Wayland_EventThreadContext));
    اگر (!context) {
        واپس تہی;
    }

    context->wayland_ڈیٹا_2 = ڈیٹا;
    context->قطار = Wayland_Display_Create_قطار(ڈیٹا->display, قطار_name);
    اگر (!context->قطار) {
        جاؤ cleanup;
    }

    context->dispatch_تالا = SDL_CreateMutex();
    اگر (!context->dispatch_تالا) {
        جاؤ cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_EventThreadFunc, "wl_event_thread", context);
    اگر (!context->thread) {
        جاؤ cleanup;
    }

    واپس context;

cleanup:
    اگر (context->dispatch_تالا) {
        SDL_DestroyMutex(context->dispatch_تالا);
    }

    اگر (context->قطار) {
        WAYLAND_wl_event_قطار_destroy(context->قطار);
    }

    SDL_free(context);
    واپس تہی;
}

خالی Wayland_DestroyEventThread(Wayland_EventThreadContext *context)
{
    اگر (context) {
        // Dispatch the exit event to unblock the thread and signal it to exit.
        ساخت wl_display *display = context->wayland_ڈیٹا_2->display;
        ساخت wl_proxy *display_wrapper = Wayland_CreateEventThreadProxyWrapper(context, display);

        SDL_تالا_Mutex(context->dispatch_تالا);
        ساخت wl_callback *cb = wl_display_sync((ساخت wl_display *)display_wrapper);
        wl_callback_جوڑو_listener(cb, &event_thread_exit_listener, context);
        SDL_UnlockMutex(context->dispatch_تالا);

        WAYLAND_wl_proxy_wrapper_destroy(display_wrapper);

        صحیح ret = WAYLAND_wl_display_flush(display);
        جب (ret == -1 && errno == EAGAIN) {
            // Shutting down the thread requires a successful flush.
            ret = SDL_IOReady(WAYLAND_wl_display_get_fd(display), SDL_IOR_WRITE, -1);
            اگر (ret >= 0) {
                ret = WAYLAND_wl_display_flush(display);
            }
        }

        // Avoid a warning if the flush failed due to a broken connection.
        اگر (ret < 0) {
            wl_callback_destroy(cb);
        }

        // Wait for the thread to return; it will exit automatically on a broken connection.
        SDL_WaitThread(context->thread, تہی);

        WAYLAND_wl_event_قطار_destroy(context->قطار);
        SDL_DestroyMutex(context->dispatch_تالا);
        SDL_free(context);
    }
}

خالی *Wayland_CreateEventThreadProxyWrapper(Wayland_EventThreadContext *context, خالی *obj)
{
    ساخت wl_proxy *wrapper = WAYLAND_wl_proxy_create_wrapper(obj);
    اگر (wrapper && context) {
        WAYLAND_wl_proxy_سیٹ_قطار(wrapper, context->قطار);
    }

    واپس wrapper;
}

خالی Wayland_تالا_Event_Thread(Wayland_EventThreadContext *context)
{
    اگر (context) {
        SDL_تالا_Mutex(context->dispatch_تالا);
    }
}

خالی Wayland_UnlockEventThread(Wayland_EventThreadContext *context)
{
    اگر (context) {
        SDL_UnlockMutex(context->dispatch_تالا);
    }
}

ساکن صحیح SDLCALL Wayland_کام_Thread_Func(خالی *ڈیٹا)
{
    Wayland_کام_Thread_Context *context = (Wayland_کام_Thread_Context *)ڈیٹا;

    SDL_تالا_Mutex(context->قطار_تالا);
    جب (!context->should_exit) {
        اگر (WAYLAND_wl_list_خالی_خانے(&context->jobs)) {
            SDL_WaitCondition(context->cond, context->قطار_تالا);
        }

        Wayland_کام *کام, *کام_عارضی;
        wl_list_for_each_محفوظ (کام, کام_عارضی, &context->jobs, link) {
            اگر (کام->حالت_2 == کام_حالت_انتظار) {
                کام->حالت_2 = کام_حالت_RUNNING;
            }

            // Don't block queue operations while dispatching the job.
            SDL_UnlockMutex(context->قطار_تالا);

            // If the job was cancelled, just remove it.
            اگر (کام->حالت_2 == کام_حالت_RUNNING) {
                کام->callback(کام->userdata);

                // Signal completion to the waiting thread.
                SDL_تالا_Mutex(context->completion_تالا);
                اگر (کام->حالت_2 == کام_حالت_SIGNAL_PENDING) {
                    SDL_SignalCondition(context->cond);
                }
                کام->حالت_2 = کام_حالت_SIGNALED;
                SDL_UnlockMutex(context->completion_تالا);
            }

            SDL_تالا_Mutex(context->قطار_تالا);

            WAYLAND_wl_list_remove(&کام->link);
            SDL_free(کام);
        }
    }
    SDL_UnlockMutex(context->قطار_تالا);

    واپس 0;
}

خارجی Wayland_کام_Thread_Context *Wayland_Create_کام_Thread()
{
    Wayland_کام_Thread_Context *context = SDL_calloc(1, حجم(Wayland_کام_Thread_Context));
    اگر (!context) {
        واپس تہی;
    }

    WAYLAND_wl_list_init(&context->jobs);

    context->قطار_تالا = SDL_CreateMutex();
    اگر (!context->قطار_تالا) {
        جاؤ cleanup;
    }

    context->completion_تالا = SDL_CreateMutex();
    اگر (!context->completion_تالا) {
        جاؤ cleanup;
    }

    context->cond = SDL_CreateCondition();
    اگر (!context->cond) {
        جاؤ cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_کام_Thread_Func, "wl_job_thread", context);
    اگر (!context->thread) {
        جاؤ cleanup;
    }

    واپس context;

cleanup:
    اگر (context->قطار_تالا) {
        SDL_DestroyMutex(context->قطار_تالا);
    }

    اگر (context->completion_تالا) {
        SDL_DestroyMutex(context->completion_تالا);
    }

    اگر (context->cond) {
        SDL_DestroyCondition(context->cond);
    }

    SDL_free(context);

    واپس تہی;
}

ساکن خالی کام_thread_exit(خالی *ڈیٹا)
{
    Wayland_کام_Thread_Context *context = (Wayland_کام_Thread_Context *)ڈیٹا;
    context->should_exit = true;
}

خارجی خالی Wayland_Destroy_کام_Thread(Wayland_کام_Thread_Context *context)
{
    اگر (!context) {
        واپس;
    }

    // Dispatch the exit job to unblock the thread and set the exit condition.
    Wayland_کام_Thread_جوڑو_کام(context, کام_thread_exit, context, تہی);

    // Wait for the thread to return; all jobs will be complete at this point.
    SDL_WaitThread(context->thread, تہی);

    // Cleanup.
    SDL_DestroyCondition(context->cond);
    SDL_DestroyMutex(context->قطار_تالا);
    SDL_DestroyMutex(context->completion_تالا);
    SDL_free(context);
}

bool Wayland_کام_Thread_جوڑو_کام(Wayland_کام_Thread_Context *context, Wayland_کام_Thread_Callback callback, خالی *userdata, Wayland_کام_ID *id)
{
    اگر (!callback) {
        واپس false;
    }

    اگر (context) {
        SDL_تالا_Mutex(context->قطار_تالا);
        Wayland_کام *کام = SDL_calloc(1, حجم(Wayland_کام));
        اگر (کام) {
            کام->id = context->id_شمار++;
            اگر (id) {
                *id = کام->id;
            }

            کام->callback = callback;
            کام->userdata = userdata;

            WAYLAND_wl_list_داخل_کرو(context->jobs.پچھلا, &کام->link);

            SDL_SignalCondition(context->cond);
            SDL_UnlockMutex(context->قطار_تالا);

            واپس true;
        }

        SDL_UnlockMutex(context->قطار_تالا);
        واپس false;
    } ورنہ {
        // No thread? Just run the job.
        callback(userdata);
    }

    واپس true;
}

خالی Wayland_کام_Thread_Cancel_کام(Wayland_کام_Thread_Context *context, Wayland_کام_ID id)
{
    اگر (!context) {
        واپس;
    }

    SDL_تالا_Mutex(context->قطار_تالا);

    Wayland_کام *کام;
    wl_list_for_each (کام, &context->jobs, link) {
        اگر (کام->id == id) {
            SDL_تالا_Mutex(context->completion_تالا);
            اگر (کام->حالت_2 == کام_حالت_انتظار) {
                // In the queue, waiting to run; mark as cancelled.
                کام->حالت_2 = کام_حالت_CANCELED;
            } ورنہ اگر (کام->حالت_2 == کام_حالت_RUNNING) {
                // The job is running; wait for completion.
                کام->حالت_2 = کام_حالت_SIGNAL_PENDING;
                SDL_WaitCondition(context->cond, context->completion_تالا);
            }
            SDL_UnlockMutex(context->completion_تالا);
            توڑو;
        }
    }

    SDL_UnlockMutex(context->قطار_تالا);
}

#اگر_ختم // SDL_VIDEO_DRIVER_WAYLAND

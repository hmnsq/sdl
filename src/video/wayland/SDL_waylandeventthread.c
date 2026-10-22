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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_DRIVER_WAYLAND

#ਅਨ੍ਤਰ੍ਭਾਵ "../../core/unix/SDL_poll.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandeventthread.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_waylandvideo.h"

#ਅਨ੍ਤਰ੍ਭਾਵ <errno.h>

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਗਿਣਤੀ Wayland_ਕੰਮ_ਸਥਿਤੀ
{
    ਕੰਮ_ਸਥਿਤੀ_ਉਡੀਕ = 0,
    ਕੰਮ_ਸਥਿਤੀ_RUNNING,
    ਕੰਮ_ਸਥਿਤੀ_SIGNAL_PENDING,
    ਕੰਮ_ਸਥਿਤੀ_SIGNALED,
    ਕੰਮ_ਸਥਿਤੀ_CANCELED
} Wayland_ਕੰਮ_ਸਥਿਤੀ;

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Wayland_ਕੰਮ
{
    Wayland_ਕੰਮ_Thread_Callback callback;
    ਖਾਲੀ *userdata;
    Wayland_ਕੰਮ_ID id;
    Wayland_ਕੰਮ_ਸਥਿਤੀ ਸਥਿਤੀ;

    ਬਣਤਰ wl_list link;
} Wayland_ਕੰਮ;

ਬਣਤਰ Wayland_ਕੰਮ_Thread_Context
{
    SDL_Thread *thread;
    SDL_Mutex *ਕਤਾਰ_ਤਾਲਾ;
    SDL_Mutex *completion_ਤਾਲਾ;
    SDL_Condition *cond;
    ਬਣਤਰ wl_list jobs;
    Wayland_ਕੰਮ_ID id_counter;
    bool should_exit;
};

ਬਣਤਰ Wayland_EventThreadContext
{
    SDL_Video_ਅੰਕੜੇ *wayland_ਅੰਕੜੇ_2;
    SDL_Thread *thread;
    ਬਣਤਰ wl_event_ਕਤਾਰ *ਕਤਾਰ;
    SDL_Mutex *dispatch_ਤਾਲਾ;
    bool should_exit;
};

ਸਥਿਰ ਖਾਲੀ handle_event_thread_exit(ਖਾਲੀ *ਅੰਕੜੇ, ਬਣਤਰ wl_callback *wl_callback, uint32_t callback_ਅੰਕੜੇ)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)ਅੰਕੜੇ;
    wl_callback_destroy(wl_callback);
    context->should_exit = true;
}

ਸਥਿਰ ਅਚਲ ਬਣਤਰ wl_callback_listener event_thread_exit_listener = {
    handle_event_thread_exit
};

ਸਥਿਰ ਪੂਰਨ SDLCALL Wayland_EventThreadFunc(ਖਾਲੀ *ਅੰਕੜੇ)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)ਅੰਕੜੇ;
    ਬਣਤਰ wl_display *display = context->wayland_ਅੰਕੜੇ_2->display;
    ਅਚਲ ਪੂਰਨ display_fd = WAYLAND_wl_display_get_fd(display);
    ਪੂਰਨ ret;

    /* The lock must be held whenever dispatching to avoid a race condition when adding
     * or destroying objects using the queue.
     *
     * Any error other than EAGAIN is fatal and causes the thread to exit.
     */
    ਜਦੋਂ (!context->should_exit) {
        ਜੇ (WAYLAND_wl_display_prepare_read_ਕਤਾਰ(display, context->ਕਤਾਰ) == 0) {
            Sint64 timeoutNS = -1;

            ret = WAYLAND_wl_display_flush(display);

            ਜੇ (ret < 0) {
                ਜੇ (errno == EAGAIN) {
                    // If the flush failed with EAGAIN, don't block as not to inhibit other threads from reading events.
                    timeoutNS = SDL_MS_ਮੰਜ਼ਿਲ_NS(1);
                } ਨਹੀਂਤਾਂ {
                    WAYLAND_wl_display_cancel_read(display);
                    ਵਾਪਸ -1;
                }
            }

            // Wait for a read/write operation to become possible.
            ret = SDL_IOReady(display_fd, SDL_IOR_READ, timeoutNS);

            ਜੇ (ret <= 0) {
                WAYLAND_wl_display_cancel_read(display);
                ਜੇ (ret < 0) {
                    ਵਾਪਸ -1;
                }

                // Nothing to read, and woke to flush; try again.
                ਜਾਰੀ;
            }

            ret = WAYLAND_wl_display_read_events(display);
            ਜੇ (ret == -1) {
                ਵਾਪਸ -1;
            }
        }

        SDL_ਤਾਲਾ_Mutex(context->dispatch_ਤਾਲਾ);
        ret = WAYLAND_wl_display_dispatch_ਕਤਾਰ_pending(display, context->ਕਤਾਰ);
        SDL_UnlockMutex(context->dispatch_ਤਾਲਾ);

        ਜੇ (ret < 0) {
            ਵਾਪਸ -1;
        }
    }

    ਵਾਪਸ 0;
}

Wayland_EventThreadContext *Wayland_CreateEventThread(SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ, ਅਚਲ ਅੱਖਰ *ਕਤਾਰ_name)
{
    Wayland_EventThreadContext *context = SDL_calloc(1, ਆਕਾਰ(Wayland_EventThreadContext));
    ਜੇ (!context) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    context->wayland_ਅੰਕੜੇ_2 = ਅੰਕੜੇ;
    context->ਕਤਾਰ = Wayland_Display_Create_ਕਤਾਰ(ਅੰਕੜੇ->display, ਕਤਾਰ_name);
    ਜੇ (!context->ਕਤਾਰ) {
        ਜਾਓ cleanup;
    }

    context->dispatch_ਤਾਲਾ = SDL_CreateMutex();
    ਜੇ (!context->dispatch_ਤਾਲਾ) {
        ਜਾਓ cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_EventThreadFunc, "wl_event_thread", context);
    ਜੇ (!context->thread) {
        ਜਾਓ cleanup;
    }

    ਵਾਪਸ context;

cleanup:
    ਜੇ (context->dispatch_ਤਾਲਾ) {
        SDL_DestroyMutex(context->dispatch_ਤਾਲਾ);
    }

    ਜੇ (context->ਕਤਾਰ) {
        WAYLAND_wl_event_ਕਤਾਰ_destroy(context->ਕਤਾਰ);
    }

    SDL_free(context);
    ਵਾਪਸ ਨਿਰਾ;
}

ਖਾਲੀ Wayland_DestroyEventThread(Wayland_EventThreadContext *context)
{
    ਜੇ (context) {
        // Dispatch the exit event to unblock the thread and signal it to exit.
        ਬਣਤਰ wl_display *display = context->wayland_ਅੰਕੜੇ_2->display;
        ਬਣਤਰ wl_proxy *display_wrapper = Wayland_CreateEventThreadProxyWrapper(context, display);

        SDL_ਤਾਲਾ_Mutex(context->dispatch_ਤਾਲਾ);
        ਬਣਤਰ wl_callback *cb = wl_display_sync((ਬਣਤਰ wl_display *)display_wrapper);
        wl_callback_ਜੋੜੋ_listener(cb, &event_thread_exit_listener, context);
        SDL_UnlockMutex(context->dispatch_ਤਾਲਾ);

        WAYLAND_wl_proxy_wrapper_destroy(display_wrapper);

        ਪੂਰਨ ret = WAYLAND_wl_display_flush(display);
        ਜਦੋਂ (ret == -1 && errno == EAGAIN) {
            // Shutting down the thread requires a successful flush.
            ret = SDL_IOReady(WAYLAND_wl_display_get_fd(display), SDL_IOR_WRITE, -1);
            ਜੇ (ret >= 0) {
                ret = WAYLAND_wl_display_flush(display);
            }
        }

        // Avoid a warning if the flush failed due to a broken connection.
        ਜੇ (ret < 0) {
            wl_callback_destroy(cb);
        }

        // Wait for the thread to return; it will exit automatically on a broken connection.
        SDL_WaitThread(context->thread, ਨਿਰਾ);

        WAYLAND_wl_event_ਕਤਾਰ_destroy(context->ਕਤਾਰ);
        SDL_DestroyMutex(context->dispatch_ਤਾਲਾ);
        SDL_free(context);
    }
}

ਖਾਲੀ *Wayland_CreateEventThreadProxyWrapper(Wayland_EventThreadContext *context, ਖਾਲੀ *obj)
{
    ਬਣਤਰ wl_proxy *wrapper = WAYLAND_wl_proxy_create_wrapper(obj);
    ਜੇ (wrapper && context) {
        WAYLAND_wl_proxy_ਸੈੱਟ_ਕਤਾਰ(wrapper, context->ਕਤਾਰ);
    }

    ਵਾਪਸ wrapper;
}

ਖਾਲੀ Wayland_ਤਾਲਾ_Event_Thread(Wayland_EventThreadContext *context)
{
    ਜੇ (context) {
        SDL_ਤਾਲਾ_Mutex(context->dispatch_ਤਾਲਾ);
    }
}

ਖਾਲੀ Wayland_UnlockEventThread(Wayland_EventThreadContext *context)
{
    ਜੇ (context) {
        SDL_UnlockMutex(context->dispatch_ਤਾਲਾ);
    }
}

ਸਥਿਰ ਪੂਰਨ SDLCALL Wayland_ਕੰਮ_Thread_Func(ਖਾਲੀ *ਅੰਕੜੇ)
{
    Wayland_ਕੰਮ_Thread_Context *context = (Wayland_ਕੰਮ_Thread_Context *)ਅੰਕੜੇ;

    SDL_ਤਾਲਾ_Mutex(context->ਕਤਾਰ_ਤਾਲਾ);
    ਜਦੋਂ (!context->should_exit) {
        ਜੇ (WAYLAND_wl_list_ਖਾਲੀ_ਥਾਵਾਂ(&context->jobs)) {
            SDL_WaitCondition(context->cond, context->ਕਤਾਰ_ਤਾਲਾ);
        }

        Wayland_ਕੰਮ *ਕੰਮ, *ਕੰਮ_ਆਰਜ਼ੀ;
        wl_list_for_each_ਸੁਰੱਖਿਅਤ (ਕੰਮ, ਕੰਮ_ਆਰਜ਼ੀ, &context->jobs, link) {
            ਜੇ (ਕੰਮ->ਸਥਿਤੀ == ਕੰਮ_ਸਥਿਤੀ_ਉਡੀਕ) {
                ਕੰਮ->ਸਥਿਤੀ = ਕੰਮ_ਸਥਿਤੀ_RUNNING;
            }

            // Don't block queue operations while dispatching the job.
            SDL_UnlockMutex(context->ਕਤਾਰ_ਤਾਲਾ);

            // If the job was cancelled, just remove it.
            ਜੇ (ਕੰਮ->ਸਥਿਤੀ == ਕੰਮ_ਸਥਿਤੀ_RUNNING) {
                ਕੰਮ->callback(ਕੰਮ->userdata);

                // Signal completion to the waiting thread.
                SDL_ਤਾਲਾ_Mutex(context->completion_ਤਾਲਾ);
                ਜੇ (ਕੰਮ->ਸਥਿਤੀ == ਕੰਮ_ਸਥਿਤੀ_SIGNAL_PENDING) {
                    SDL_SignalCondition(context->cond);
                }
                ਕੰਮ->ਸਥਿਤੀ = ਕੰਮ_ਸਥਿਤੀ_SIGNALED;
                SDL_UnlockMutex(context->completion_ਤਾਲਾ);
            }

            SDL_ਤਾਲਾ_Mutex(context->ਕਤਾਰ_ਤਾਲਾ);

            WAYLAND_wl_list_remove(&ਕੰਮ->link);
            SDL_free(ਕੰਮ);
        }
    }
    SDL_UnlockMutex(context->ਕਤਾਰ_ਤਾਲਾ);

    ਵਾਪਸ 0;
}

ਬਾਹਰੀ Wayland_ਕੰਮ_Thread_Context *Wayland_Create_ਕੰਮ_Thread()
{
    Wayland_ਕੰਮ_Thread_Context *context = SDL_calloc(1, ਆਕਾਰ(Wayland_ਕੰਮ_Thread_Context));
    ਜੇ (!context) {
        ਵਾਪਸ ਨਿਰਾ;
    }

    WAYLAND_wl_list_init(&context->jobs);

    context->ਕਤਾਰ_ਤਾਲਾ = SDL_CreateMutex();
    ਜੇ (!context->ਕਤਾਰ_ਤਾਲਾ) {
        ਜਾਓ cleanup;
    }

    context->completion_ਤਾਲਾ = SDL_CreateMutex();
    ਜੇ (!context->completion_ਤਾਲਾ) {
        ਜਾਓ cleanup;
    }

    context->cond = SDL_CreateCondition();
    ਜੇ (!context->cond) {
        ਜਾਓ cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_ਕੰਮ_Thread_Func, "wl_job_thread", context);
    ਜੇ (!context->thread) {
        ਜਾਓ cleanup;
    }

    ਵਾਪਸ context;

cleanup:
    ਜੇ (context->ਕਤਾਰ_ਤਾਲਾ) {
        SDL_DestroyMutex(context->ਕਤਾਰ_ਤਾਲਾ);
    }

    ਜੇ (context->completion_ਤਾਲਾ) {
        SDL_DestroyMutex(context->completion_ਤਾਲਾ);
    }

    ਜੇ (context->cond) {
        SDL_DestroyCondition(context->cond);
    }

    SDL_free(context);

    ਵਾਪਸ ਨਿਰਾ;
}

ਸਥਿਰ ਖਾਲੀ ਕੰਮ_thread_exit(ਖਾਲੀ *ਅੰਕੜੇ)
{
    Wayland_ਕੰਮ_Thread_Context *context = (Wayland_ਕੰਮ_Thread_Context *)ਅੰਕੜੇ;
    context->should_exit = true;
}

ਬਾਹਰੀ ਖਾਲੀ Wayland_Destroy_ਕੰਮ_Thread(Wayland_ਕੰਮ_Thread_Context *context)
{
    ਜੇ (!context) {
        ਵਾਪਸ;
    }

    // Dispatch the exit job to unblock the thread and set the exit condition.
    Wayland_ਕੰਮ_Thread_ਜੋੜੋ_ਕੰਮ(context, ਕੰਮ_thread_exit, context, ਨਿਰਾ);

    // Wait for the thread to return; all jobs will be complete at this point.
    SDL_WaitThread(context->thread, ਨਿਰਾ);

    // Cleanup.
    SDL_DestroyCondition(context->cond);
    SDL_DestroyMutex(context->ਕਤਾਰ_ਤਾਲਾ);
    SDL_DestroyMutex(context->completion_ਤਾਲਾ);
    SDL_free(context);
}

bool Wayland_ਕੰਮ_Thread_ਜੋੜੋ_ਕੰਮ(Wayland_ਕੰਮ_Thread_Context *context, Wayland_ਕੰਮ_Thread_Callback callback, ਖਾਲੀ *userdata, Wayland_ਕੰਮ_ID *id)
{
    ਜੇ (!callback) {
        ਵਾਪਸ false;
    }

    ਜੇ (context) {
        SDL_ਤਾਲਾ_Mutex(context->ਕਤਾਰ_ਤਾਲਾ);
        Wayland_ਕੰਮ *ਕੰਮ = SDL_calloc(1, ਆਕਾਰ(Wayland_ਕੰਮ));
        ਜੇ (ਕੰਮ) {
            ਕੰਮ->id = context->id_counter++;
            ਜੇ (id) {
                *id = ਕੰਮ->id;
            }

            ਕੰਮ->callback = callback;
            ਕੰਮ->userdata = userdata;

            WAYLAND_wl_list_ਪਾਓ(context->jobs.prev, &ਕੰਮ->link);

            SDL_SignalCondition(context->cond);
            SDL_UnlockMutex(context->ਕਤਾਰ_ਤਾਲਾ);

            ਵਾਪਸ true;
        }

        SDL_UnlockMutex(context->ਕਤਾਰ_ਤਾਲਾ);
        ਵਾਪਸ false;
    } ਨਹੀਂਤਾਂ {
        // No thread? Just run the job.
        callback(userdata);
    }

    ਵਾਪਸ true;
}

ਖਾਲੀ Wayland_ਕੰਮ_Thread_Cancel_ਕੰਮ(Wayland_ਕੰਮ_Thread_Context *context, Wayland_ਕੰਮ_ID id)
{
    ਜੇ (!context) {
        ਵਾਪਸ;
    }

    SDL_ਤਾਲਾ_Mutex(context->ਕਤਾਰ_ਤਾਲਾ);

    Wayland_ਕੰਮ *ਕੰਮ;
    wl_list_for_each (ਕੰਮ, &context->jobs, link) {
        ਜੇ (ਕੰਮ->id == id) {
            SDL_ਤਾਲਾ_Mutex(context->completion_ਤਾਲਾ);
            ਜੇ (ਕੰਮ->ਸਥਿਤੀ == ਕੰਮ_ਸਥਿਤੀ_ਉਡੀਕ) {
                // In the queue, waiting to run; mark as cancelled.
                ਕੰਮ->ਸਥਿਤੀ = ਕੰਮ_ਸਥਿਤੀ_CANCELED;
            } ਨਹੀਂਤਾਂ ਜੇ (ਕੰਮ->ਸਥਿਤੀ == ਕੰਮ_ਸਥਿਤੀ_RUNNING) {
                // The job is running; wait for completion.
                ਕੰਮ->ਸਥਿਤੀ = ਕੰਮ_ਸਥਿਤੀ_SIGNAL_PENDING;
                SDL_WaitCondition(context->cond, context->completion_ਤਾਲਾ);
            }
            SDL_UnlockMutex(context->completion_ਤਾਲਾ);
            ਰੋਕੋ;
        }
    }

    SDL_UnlockMutex(context->ਕਤਾਰ_ਤਾਲਾ);
}

#ਜੇ_ਅੰਤ // SDL_VIDEO_DRIVER_WAYLAND

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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ವ್ಯಾಖ್ಯಾನಿತವಾದರೆ SDL_VIDEO_DRIVER_WAYLAND

#ಅನ್ತರ್ಭಾವ "../../core/unix/SDL_poll.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandeventthread.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandvideo.h"

#ಅನ್ತರ್ಭಾವ <errno.h>

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಎಣಿಕೆ Wayland_ಕೆಲಸ_ಸ್ಥಿತಿ
{
    ಕೆಲಸ_ಸ್ಥಿತಿ_ಕಾಯುವಿಕೆ = 0,
    ಕೆಲಸ_ಸ್ಥಿತಿ_RUNNING,
    ಕೆಲಸ_ಸ್ಥಿತಿ_SIGNAL_PENDING,
    ಕೆಲಸ_ಸ್ಥಿತಿ_SIGNALED,
    ಕೆಲಸ_ಸ್ಥಿತಿ_CANCELED
} Wayland_ಕೆಲಸ_ಸ್ಥಿತಿ;

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Wayland_ಕೆಲಸ
{
    Wayland_ಕೆಲಸ_Thread_Callback callback;
    ಶೂನ್ಯ *userdata;
    Wayland_ಕೆಲಸ_ID id;
    Wayland_ಕೆಲಸ_ಸ್ಥಿತಿ ಸ್ಥಿತಿ_2;

    ರಚನೆ wl_list link;
} Wayland_ಕೆಲಸ;

ರಚನೆ Wayland_ಕೆಲಸ_Thread_Context
{
    SDL_Thread *thread;
    SDL_Mutex *ಸರತಿ_ಬೀಗ;
    SDL_Mutex *completion_ಬೀಗ;
    SDL_Condition *cond;
    ರಚನೆ wl_list jobs;
    Wayland_ಕೆಲಸ_ID id_counter;
    bool should_exit;
};

ರಚನೆ Wayland_EventThreadContext
{
    SDL_Video_ದತ್ತಾಂಶ *wayland_ದತ್ತಾಂಶ_2;
    SDL_Thread *thread;
    ರಚನೆ wl_event_ಸರತಿ *ಸರತಿ;
    SDL_Mutex *dispatch_ಬೀಗ;
    bool should_exit;
};

ಸ್ಥಿರ ಶೂನ್ಯ handle_event_thread_exit(ಶೂನ್ಯ *ದತ್ತಾಂಶ, ರಚನೆ wl_callback *wl_callback, uint32_t callback_ದತ್ತಾಂಶ)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)ದತ್ತಾಂಶ;
    wl_callback_destroy(wl_callback);
    context->should_exit = true;
}

ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ ರಚನೆ wl_callback_listener event_thread_exit_listener = {
    handle_event_thread_exit
};

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ SDLCALL Wayland_EventThreadFunc(ಶೂನ್ಯ *ದತ್ತಾಂಶ)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)ದತ್ತಾಂಶ;
    ರಚನೆ wl_display *display = context->wayland_ದತ್ತಾಂಶ_2->display;
    ಸ್ಥಿರಾಂಕ ಪೂರ್ಣಾಂಕ display_fd = WAYLAND_wl_display_get_fd(display);
    ಪೂರ್ಣಾಂಕ ret;

    /* The lock must be held whenever dispatching to avoid a race condition when adding
     * or destroying objects using the queue.
     *
     * Any error other than EAGAIN is fatal and causes the thread to exit.
     */
    ಆಗ (!context->should_exit) {
        ಆದರೆ (WAYLAND_wl_display_prepare_read_ಸರತಿ(display, context->ಸರತಿ) == 0) {
            Sint64 timeoutNS = -1;

            ret = WAYLAND_wl_display_flush(display);

            ಆದರೆ (ret < 0) {
                ಆದರೆ (errno == EAGAIN) {
                    // If the flush failed with EAGAIN, don't block as not to inhibit other threads from reading events.
                    timeoutNS = SDL_MS_ಗಮ್ಯ_NS(1);
                } ಇಲ್ಲದಿದ್ದರೆ {
                    WAYLAND_wl_display_cancel_read(display);
                    ಹಿಂತಿರುಗಿ -1;
                }
            }

            // Wait for a read/write operation to become possible.
            ret = SDL_IOReady(display_fd, SDL_IOR_READ, timeoutNS);

            ಆದರೆ (ret <= 0) {
                WAYLAND_wl_display_cancel_read(display);
                ಆದರೆ (ret < 0) {
                    ಹಿಂತಿರುಗಿ -1;
                }

                // Nothing to read, and woke to flush; try again.
                ಮುಂದುವರಿ;
            }

            ret = WAYLAND_wl_display_read_events(display);
            ಆದರೆ (ret == -1) {
                ಹಿಂತಿರುಗಿ -1;
            }
        }

        SDL_ಬೀಗ_Mutex(context->dispatch_ಬೀಗ);
        ret = WAYLAND_wl_display_dispatch_ಸರತಿ_pending(display, context->ಸರತಿ);
        SDL_UnlockMutex(context->dispatch_ಬೀಗ);

        ಆದರೆ (ret < 0) {
            ಹಿಂತಿರುಗಿ -1;
        }
    }

    ಹಿಂತಿರುಗಿ 0;
}

Wayland_EventThreadContext *Wayland_CreateEventThread(SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸರತಿ_name)
{
    Wayland_EventThreadContext *context = SDL_calloc(1, ಗಾತ್ರ(Wayland_EventThreadContext));
    ಆದರೆ (!context) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    context->wayland_ದತ್ತಾಂಶ_2 = ದತ್ತಾಂಶ;
    context->ಸರತಿ = Wayland_Display_Create_ಸರತಿ(ದತ್ತಾಂಶ->display, ಸರತಿ_name);
    ಆದರೆ (!context->ಸರತಿ) {
        ಹೋಗು cleanup;
    }

    context->dispatch_ಬೀಗ = SDL_CreateMutex();
    ಆದರೆ (!context->dispatch_ಬೀಗ) {
        ಹೋಗು cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_EventThreadFunc, "wl_event_thread", context);
    ಆದರೆ (!context->thread) {
        ಹೋಗು cleanup;
    }

    ಹಿಂತಿರುಗಿ context;

cleanup:
    ಆದರೆ (context->dispatch_ಬೀಗ) {
        SDL_DestroyMutex(context->dispatch_ಬೀಗ);
    }

    ಆದರೆ (context->ಸರತಿ) {
        WAYLAND_wl_event_ಸರತಿ_destroy(context->ಸರತಿ);
    }

    SDL_free(context);
    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಶೂನ್ಯ Wayland_DestroyEventThread(Wayland_EventThreadContext *context)
{
    ಆದರೆ (context) {
        // Dispatch the exit event to unblock the thread and signal it to exit.
        ರಚನೆ wl_display *display = context->wayland_ದತ್ತಾಂಶ_2->display;
        ರಚನೆ wl_proxy *display_wrapper = Wayland_CreateEventThreadProxyWrapper(context, display);

        SDL_ಬೀಗ_Mutex(context->dispatch_ಬೀಗ);
        ರಚನೆ wl_callback *cb = wl_display_sync((ರಚನೆ wl_display *)display_wrapper);
        wl_callback_ಕೂಡಿಸು_listener(cb, &event_thread_exit_listener, context);
        SDL_UnlockMutex(context->dispatch_ಬೀಗ);

        WAYLAND_wl_proxy_wrapper_destroy(display_wrapper);

        ಪೂರ್ಣಾಂಕ ret = WAYLAND_wl_display_flush(display);
        ಆಗ (ret == -1 && errno == EAGAIN) {
            // Shutting down the thread requires a successful flush.
            ret = SDL_IOReady(WAYLAND_wl_display_get_fd(display), SDL_IOR_WRITE, -1);
            ಆದರೆ (ret >= 0) {
                ret = WAYLAND_wl_display_flush(display);
            }
        }

        // Avoid a warning if the flush failed due to a broken connection.
        ಆದರೆ (ret < 0) {
            wl_callback_destroy(cb);
        }

        // Wait for the thread to return; it will exit automatically on a broken connection.
        SDL_WaitThread(context->thread, ಖಾಲಿ);

        WAYLAND_wl_event_ಸರತಿ_destroy(context->ಸರತಿ);
        SDL_DestroyMutex(context->dispatch_ಬೀಗ);
        SDL_free(context);
    }
}

ಶೂನ್ಯ *Wayland_CreateEventThreadProxyWrapper(Wayland_EventThreadContext *context, ಶೂನ್ಯ *obj)
{
    ರಚನೆ wl_proxy *wrapper = WAYLAND_wl_proxy_create_wrapper(obj);
    ಆದರೆ (wrapper && context) {
        WAYLAND_wl_proxy_ಗಣ_ಸರತಿ(wrapper, context->ಸರತಿ);
    }

    ಹಿಂತಿರುಗಿ wrapper;
}

ಶೂನ್ಯ Wayland_ಬೀಗ_Event_Thread(Wayland_EventThreadContext *context)
{
    ಆದರೆ (context) {
        SDL_ಬೀಗ_Mutex(context->dispatch_ಬೀಗ);
    }
}

ಶೂನ್ಯ Wayland_UnlockEventThread(Wayland_EventThreadContext *context)
{
    ಆದರೆ (context) {
        SDL_UnlockMutex(context->dispatch_ಬೀಗ);
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಂಕ SDLCALL Wayland_ಕೆಲಸ_Thread_Func(ಶೂನ್ಯ *ದತ್ತಾಂಶ)
{
    Wayland_ಕೆಲಸ_Thread_Context *context = (Wayland_ಕೆಲಸ_Thread_Context *)ದತ್ತಾಂಶ;

    SDL_ಬೀಗ_Mutex(context->ಸರತಿ_ಬೀಗ);
    ಆಗ (!context->should_exit) {
        ಆದರೆ (WAYLAND_wl_list_ಖಾಲಿಗಳು(&context->jobs)) {
            SDL_WaitCondition(context->cond, context->ಸರತಿ_ಬೀಗ);
        }

        Wayland_ಕೆಲಸ *ಕೆಲಸ, *ಕೆಲಸ_ತಾತ್ಕಾಲಿಕ;
        wl_list_for_each_ಸುರಕ್ಷಿತ (ಕೆಲಸ, ಕೆಲಸ_ತಾತ್ಕಾಲಿಕ, &context->jobs, link) {
            ಆದರೆ (ಕೆಲಸ->ಸ್ಥಿತಿ_2 == ಕೆಲಸ_ಸ್ಥಿತಿ_ಕಾಯುವಿಕೆ) {
                ಕೆಲಸ->ಸ್ಥಿತಿ_2 = ಕೆಲಸ_ಸ್ಥಿತಿ_RUNNING;
            }

            // Don't block queue operations while dispatching the job.
            SDL_UnlockMutex(context->ಸರತಿ_ಬೀಗ);

            // If the job was cancelled, just remove it.
            ಆದರೆ (ಕೆಲಸ->ಸ್ಥಿತಿ_2 == ಕೆಲಸ_ಸ್ಥಿತಿ_RUNNING) {
                ಕೆಲಸ->callback(ಕೆಲಸ->userdata);

                // Signal completion to the waiting thread.
                SDL_ಬೀಗ_Mutex(context->completion_ಬೀಗ);
                ಆದರೆ (ಕೆಲಸ->ಸ್ಥಿತಿ_2 == ಕೆಲಸ_ಸ್ಥಿತಿ_SIGNAL_PENDING) {
                    SDL_SignalCondition(context->cond);
                }
                ಕೆಲಸ->ಸ್ಥಿತಿ_2 = ಕೆಲಸ_ಸ್ಥಿತಿ_SIGNALED;
                SDL_UnlockMutex(context->completion_ಬೀಗ);
            }

            SDL_ಬೀಗ_Mutex(context->ಸರತಿ_ಬೀಗ);

            WAYLAND_wl_list_remove(&ಕೆಲಸ->link);
            SDL_free(ಕೆಲಸ);
        }
    }
    SDL_UnlockMutex(context->ಸರತಿ_ಬೀಗ);

    ಹಿಂತಿರುಗಿ 0;
}

ಬಾಹ್ಯ Wayland_ಕೆಲಸ_Thread_Context *Wayland_Create_ಕೆಲಸ_Thread()
{
    Wayland_ಕೆಲಸ_Thread_Context *context = SDL_calloc(1, ಗಾತ್ರ(Wayland_ಕೆಲಸ_Thread_Context));
    ಆದರೆ (!context) {
        ಹಿಂತಿರುಗಿ ಖಾಲಿ;
    }

    WAYLAND_wl_list_init(&context->jobs);

    context->ಸರತಿ_ಬೀಗ = SDL_CreateMutex();
    ಆದರೆ (!context->ಸರತಿ_ಬೀಗ) {
        ಹೋಗು cleanup;
    }

    context->completion_ಬೀಗ = SDL_CreateMutex();
    ಆದರೆ (!context->completion_ಬೀಗ) {
        ಹೋಗು cleanup;
    }

    context->cond = SDL_CreateCondition();
    ಆದರೆ (!context->cond) {
        ಹೋಗು cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_ಕೆಲಸ_Thread_Func, "wl_job_thread", context);
    ಆದರೆ (!context->thread) {
        ಹೋಗು cleanup;
    }

    ಹಿಂತಿರುಗಿ context;

cleanup:
    ಆದರೆ (context->ಸರತಿ_ಬೀಗ) {
        SDL_DestroyMutex(context->ಸರತಿ_ಬೀಗ);
    }

    ಆದರೆ (context->completion_ಬೀಗ) {
        SDL_DestroyMutex(context->completion_ಬೀಗ);
    }

    ಆದರೆ (context->cond) {
        SDL_DestroyCondition(context->cond);
    }

    SDL_free(context);

    ಹಿಂತಿರುಗಿ ಖಾಲಿ;
}

ಸ್ಥಿರ ಶೂನ್ಯ ಕೆಲಸ_thread_exit(ಶೂನ್ಯ *ದತ್ತಾಂಶ)
{
    Wayland_ಕೆಲಸ_Thread_Context *context = (Wayland_ಕೆಲಸ_Thread_Context *)ದತ್ತಾಂಶ;
    context->should_exit = true;
}

ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_Destroy_ಕೆಲಸ_Thread(Wayland_ಕೆಲಸ_Thread_Context *context)
{
    ಆದರೆ (!context) {
        ಹಿಂತಿರುಗಿ;
    }

    // Dispatch the exit job to unblock the thread and set the exit condition.
    Wayland_ಕೆಲಸ_Thread_ಕೂಡಿಸು_ಕೆಲಸ(context, ಕೆಲಸ_thread_exit, context, ಖಾಲಿ);

    // Wait for the thread to return; all jobs will be complete at this point.
    SDL_WaitThread(context->thread, ಖಾಲಿ);

    // Cleanup.
    SDL_DestroyCondition(context->cond);
    SDL_DestroyMutex(context->ಸರತಿ_ಬೀಗ);
    SDL_DestroyMutex(context->completion_ಬೀಗ);
    SDL_free(context);
}

bool Wayland_ಕೆಲಸ_Thread_ಕೂಡಿಸು_ಕೆಲಸ(Wayland_ಕೆಲಸ_Thread_Context *context, Wayland_ಕೆಲಸ_Thread_Callback callback, ಶೂನ್ಯ *userdata, Wayland_ಕೆಲಸ_ID *id)
{
    ಆದರೆ (!callback) {
        ಹಿಂತಿರುಗಿ false;
    }

    ಆದರೆ (context) {
        SDL_ಬೀಗ_Mutex(context->ಸರತಿ_ಬೀಗ);
        Wayland_ಕೆಲಸ *ಕೆಲಸ = SDL_calloc(1, ಗಾತ್ರ(Wayland_ಕೆಲಸ));
        ಆದರೆ (ಕೆಲಸ) {
            ಕೆಲಸ->id = context->id_counter++;
            ಆದರೆ (id) {
                *id = ಕೆಲಸ->id;
            }

            ಕೆಲಸ->callback = callback;
            ಕೆಲಸ->userdata = userdata;

            WAYLAND_wl_list_ಸೇರಿಸು(context->jobs.prev, &ಕೆಲಸ->link);

            SDL_SignalCondition(context->cond);
            SDL_UnlockMutex(context->ಸರತಿ_ಬೀಗ);

            ಹಿಂತಿರುಗಿ true;
        }

        SDL_UnlockMutex(context->ಸರತಿ_ಬೀಗ);
        ಹಿಂತಿರುಗಿ false;
    } ಇಲ್ಲದಿದ್ದರೆ {
        // No thread? Just run the job.
        callback(userdata);
    }

    ಹಿಂತಿರುಗಿ true;
}

ಶೂನ್ಯ Wayland_ಕೆಲಸ_Thread_Cancel_ಕೆಲಸ(Wayland_ಕೆಲಸ_Thread_Context *context, Wayland_ಕೆಲಸ_ID id)
{
    ಆದರೆ (!context) {
        ಹಿಂತಿರುಗಿ;
    }

    SDL_ಬೀಗ_Mutex(context->ಸರತಿ_ಬೀಗ);

    Wayland_ಕೆಲಸ *ಕೆಲಸ;
    wl_list_for_each (ಕೆಲಸ, &context->jobs, link) {
        ಆದರೆ (ಕೆಲಸ->id == id) {
            SDL_ಬೀಗ_Mutex(context->completion_ಬೀಗ);
            ಆದರೆ (ಕೆಲಸ->ಸ್ಥಿತಿ_2 == ಕೆಲಸ_ಸ್ಥಿತಿ_ಕಾಯುವಿಕೆ) {
                // In the queue, waiting to run; mark as cancelled.
                ಕೆಲಸ->ಸ್ಥಿತಿ_2 = ಕೆಲಸ_ಸ್ಥಿತಿ_CANCELED;
            } ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ಕೆಲಸ->ಸ್ಥಿತಿ_2 == ಕೆಲಸ_ಸ್ಥಿತಿ_RUNNING) {
                // The job is running; wait for completion.
                ಕೆಲಸ->ಸ್ಥಿತಿ_2 = ಕೆಲಸ_ಸ್ಥಿತಿ_SIGNAL_PENDING;
                SDL_WaitCondition(context->cond, context->completion_ಬೀಗ);
            }
            SDL_UnlockMutex(context->completion_ಬೀಗ);
            ನಿಲ್ಲಿಸು;
        }
    }

    SDL_UnlockMutex(context->ಸರತಿ_ಬೀಗ);
}

#ಆದರೆ_ಅಂತ್ಯ // SDL_VIDEO_DRIVER_WAYLAND

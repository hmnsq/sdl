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

#నిర్వచితమైతే SDL_VIDEO_DRIVER_WAYLAND

#అన్తర్భావ "../../core/unix/SDL_poll.h"
#అన్తర్భావ "SDL_waylandeventthread.h"
#అన్తర్భావ "SDL_waylandvideo.h"

#అన్తర్భావ <errno.h>

రకనిర్వచనం గణన Wayland_పని_స్థితి
{
    పని_స్థితి_నిరీక్షణ = 0,
    పని_స్థితి_RUNNING,
    పని_స్థితి_SIGNAL_PENDING,
    పని_స్థితి_SIGNALED,
    పని_స్థితి_CANCELED
} Wayland_పని_స్థితి;

రకనిర్వచనం నిర్మాణం Wayland_పని
{
    Wayland_పని_Thread_Callback callback;
    శూన్య *userdata;
    Wayland_పని_ID id;
    Wayland_పని_స్థితి స్థితి_2;

    నిర్మాణం wl_list link;
} Wayland_పని;

నిర్మాణం Wayland_పని_Thread_Context
{
    SDL_Thread *thread;
    SDL_Mutex *వరుస_తాళం;
    SDL_Mutex *completion_తాళం;
    SDL_Condition *cond;
    నిర్మాణం wl_list jobs;
    Wayland_పని_ID id_counter;
    bool should_exit;
};

నిర్మాణం Wayland_EventThreadContext
{
    SDL_Video_దత్తాంశం *wayland_దత్తాంశం_2;
    SDL_Thread *thread;
    నిర్మాణం wl_event_వరుస *వరుస;
    SDL_Mutex *dispatch_తాళం;
    bool should_exit;
};

స్థిర శూన్య handle_event_thread_exit(శూన్య *దత్తాంశం, నిర్మాణం wl_callback *wl_callback, uint32_t callback_దత్తాంశం)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)దత్తాంశం;
    wl_callback_destroy(wl_callback);
    context->should_exit = true;
}

స్థిర స్థిరరాశి నిర్మాణం wl_callback_listener event_thread_exit_listener = {
    handle_event_thread_exit
};

స్థిర పూర్ణాంకం SDLCALL Wayland_EventThreadFunc(శూన్య *దత్తాంశం)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)దత్తాంశం;
    నిర్మాణం wl_display *display = context->wayland_దత్తాంశం_2->display;
    స్థిరరాశి పూర్ణాంకం display_fd = WAYLAND_wl_display_get_fd(display);
    పూర్ణాంకం ret;

    /* The lock must be held whenever dispatching to avoid a race condition when adding
     * or destroying objects using the queue.
     *
     * Any error other than EAGAIN is fatal and causes the thread to exit.
     */
    అయితే (!context->should_exit) {
        ఒకవేళ (WAYLAND_wl_display_prepare_read_వరుస(display, context->వరుస) == 0) {
            Sint64 timeoutNS = -1;

            ret = WAYLAND_wl_display_flush(display);

            ఒకవేళ (ret < 0) {
                ఒకవేళ (errno == EAGAIN) {
                    // If the flush failed with EAGAIN, don't block as not to inhibit other threads from reading events.
                    timeoutNS = SDL_MS_గమ్యం_NS(1);
                } లేకపోతే {
                    WAYLAND_wl_display_cancel_read(display);
                    తిరిగి -1;
                }
            }

            // Wait for a read/write operation to become possible.
            ret = SDL_IOReady(display_fd, SDL_IOR_READ, timeoutNS);

            ఒకవేళ (ret <= 0) {
                WAYLAND_wl_display_cancel_read(display);
                ఒకవేళ (ret < 0) {
                    తిరిగి -1;
                }

                // Nothing to read, and woke to flush; try again.
                కొనసాగు;
            }

            ret = WAYLAND_wl_display_read_events(display);
            ఒకవేళ (ret == -1) {
                తిరిగి -1;
            }
        }

        SDL_తాళం_Mutex(context->dispatch_తాళం);
        ret = WAYLAND_wl_display_dispatch_వరుస_pending(display, context->వరుస);
        SDL_UnlockMutex(context->dispatch_తాళం);

        ఒకవేళ (ret < 0) {
            తిరిగి -1;
        }
    }

    తిరిగి 0;
}

Wayland_EventThreadContext *Wayland_CreateEventThread(SDL_Video_దత్తాంశం *దత్తాంశం, స్థిరరాశి అక్షరం *వరుస_name)
{
    Wayland_EventThreadContext *context = SDL_calloc(1, పరిమాణం(Wayland_EventThreadContext));
    ఒకవేళ (!context) {
        తిరిగి ఖాళీ;
    }

    context->wayland_దత్తాంశం_2 = దత్తాంశం;
    context->వరుస = Wayland_Display_Create_వరుస(దత్తాంశం->display, వరుస_name);
    ఒకవేళ (!context->వరుస) {
        వెళ్ళు cleanup;
    }

    context->dispatch_తాళం = SDL_CreateMutex();
    ఒకవేళ (!context->dispatch_తాళం) {
        వెళ్ళు cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_EventThreadFunc, "wl_event_thread", context);
    ఒకవేళ (!context->thread) {
        వెళ్ళు cleanup;
    }

    తిరిగి context;

cleanup:
    ఒకవేళ (context->dispatch_తాళం) {
        SDL_DestroyMutex(context->dispatch_తాళం);
    }

    ఒకవేళ (context->వరుస) {
        WAYLAND_wl_event_వరుస_destroy(context->వరుస);
    }

    SDL_free(context);
    తిరిగి ఖాళీ;
}

శూన్య Wayland_DestroyEventThread(Wayland_EventThreadContext *context)
{
    ఒకవేళ (context) {
        // Dispatch the exit event to unblock the thread and signal it to exit.
        నిర్మాణం wl_display *display = context->wayland_దత్తాంశం_2->display;
        నిర్మాణం wl_proxy *display_wrapper = Wayland_CreateEventThreadProxyWrapper(context, display);

        SDL_తాళం_Mutex(context->dispatch_తాళం);
        నిర్మాణం wl_callback *cb = wl_display_sync((నిర్మాణం wl_display *)display_wrapper);
        wl_callback_కూడు_listener(cb, &event_thread_exit_listener, context);
        SDL_UnlockMutex(context->dispatch_తాళం);

        WAYLAND_wl_proxy_wrapper_destroy(display_wrapper);

        పూర్ణాంకం ret = WAYLAND_wl_display_flush(display);
        అయితే (ret == -1 && errno == EAGAIN) {
            // Shutting down the thread requires a successful flush.
            ret = SDL_IOReady(WAYLAND_wl_display_get_fd(display), SDL_IOR_WRITE, -1);
            ఒకవేళ (ret >= 0) {
                ret = WAYLAND_wl_display_flush(display);
            }
        }

        // Avoid a warning if the flush failed due to a broken connection.
        ఒకవేళ (ret < 0) {
            wl_callback_destroy(cb);
        }

        // Wait for the thread to return; it will exit automatically on a broken connection.
        SDL_WaitThread(context->thread, ఖాళీ);

        WAYLAND_wl_event_వరుస_destroy(context->వరుస);
        SDL_DestroyMutex(context->dispatch_తాళం);
        SDL_free(context);
    }
}

శూన్య *Wayland_CreateEventThreadProxyWrapper(Wayland_EventThreadContext *context, శూన్య *obj)
{
    నిర్మాణం wl_proxy *wrapper = WAYLAND_wl_proxy_create_wrapper(obj);
    ఒకవేళ (wrapper && context) {
        WAYLAND_wl_proxy_సమితి_వరుస(wrapper, context->వరుస);
    }

    తిరిగి wrapper;
}

శూన్య Wayland_తాళం_Event_Thread(Wayland_EventThreadContext *context)
{
    ఒకవేళ (context) {
        SDL_తాళం_Mutex(context->dispatch_తాళం);
    }
}

శూన్య Wayland_UnlockEventThread(Wayland_EventThreadContext *context)
{
    ఒకవేళ (context) {
        SDL_UnlockMutex(context->dispatch_తాళం);
    }
}

స్థిర పూర్ణాంకం SDLCALL Wayland_పని_Thread_Func(శూన్య *దత్తాంశం)
{
    Wayland_పని_Thread_Context *context = (Wayland_పని_Thread_Context *)దత్తాంశం;

    SDL_తాళం_Mutex(context->వరుస_తాళం);
    అయితే (!context->should_exit) {
        ఒకవేళ (WAYLAND_wl_list_ఖాళీలు(&context->jobs)) {
            SDL_WaitCondition(context->cond, context->వరుస_తాళం);
        }

        Wayland_పని *పని, *పని_తాత్కాలిక;
        wl_list_for_each_సురక్షిత (పని, పని_తాత్కాలిక, &context->jobs, link) {
            ఒకవేళ (పని->స్థితి_2 == పని_స్థితి_నిరీక్షణ) {
                పని->స్థితి_2 = పని_స్థితి_RUNNING;
            }

            // Don't block queue operations while dispatching the job.
            SDL_UnlockMutex(context->వరుస_తాళం);

            // If the job was cancelled, just remove it.
            ఒకవేళ (పని->స్థితి_2 == పని_స్థితి_RUNNING) {
                పని->callback(పని->userdata);

                // Signal completion to the waiting thread.
                SDL_తాళం_Mutex(context->completion_తాళం);
                ఒకవేళ (పని->స్థితి_2 == పని_స్థితి_SIGNAL_PENDING) {
                    SDL_SignalCondition(context->cond);
                }
                పని->స్థితి_2 = పని_స్థితి_SIGNALED;
                SDL_UnlockMutex(context->completion_తాళం);
            }

            SDL_తాళం_Mutex(context->వరుస_తాళం);

            WAYLAND_wl_list_remove(&పని->link);
            SDL_free(పని);
        }
    }
    SDL_UnlockMutex(context->వరుస_తాళం);

    తిరిగి 0;
}

బాహ్య Wayland_పని_Thread_Context *Wayland_Create_పని_Thread()
{
    Wayland_పని_Thread_Context *context = SDL_calloc(1, పరిమాణం(Wayland_పని_Thread_Context));
    ఒకవేళ (!context) {
        తిరిగి ఖాళీ;
    }

    WAYLAND_wl_list_init(&context->jobs);

    context->వరుస_తాళం = SDL_CreateMutex();
    ఒకవేళ (!context->వరుస_తాళం) {
        వెళ్ళు cleanup;
    }

    context->completion_తాళం = SDL_CreateMutex();
    ఒకవేళ (!context->completion_తాళం) {
        వెళ్ళు cleanup;
    }

    context->cond = SDL_CreateCondition();
    ఒకవేళ (!context->cond) {
        వెళ్ళు cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_పని_Thread_Func, "wl_job_thread", context);
    ఒకవేళ (!context->thread) {
        వెళ్ళు cleanup;
    }

    తిరిగి context;

cleanup:
    ఒకవేళ (context->వరుస_తాళం) {
        SDL_DestroyMutex(context->వరుస_తాళం);
    }

    ఒకవేళ (context->completion_తాళం) {
        SDL_DestroyMutex(context->completion_తాళం);
    }

    ఒకవేళ (context->cond) {
        SDL_DestroyCondition(context->cond);
    }

    SDL_free(context);

    తిరిగి ఖాళీ;
}

స్థిర శూన్య పని_thread_exit(శూన్య *దత్తాంశం)
{
    Wayland_పని_Thread_Context *context = (Wayland_పని_Thread_Context *)దత్తాంశం;
    context->should_exit = true;
}

బాహ్య శూన్య Wayland_Destroy_పని_Thread(Wayland_పని_Thread_Context *context)
{
    ఒకవేళ (!context) {
        తిరిగి;
    }

    // Dispatch the exit job to unblock the thread and set the exit condition.
    Wayland_పని_Thread_కూడు_పని(context, పని_thread_exit, context, ఖాళీ);

    // Wait for the thread to return; all jobs will be complete at this point.
    SDL_WaitThread(context->thread, ఖాళీ);

    // Cleanup.
    SDL_DestroyCondition(context->cond);
    SDL_DestroyMutex(context->వరుస_తాళం);
    SDL_DestroyMutex(context->completion_తాళం);
    SDL_free(context);
}

bool Wayland_పని_Thread_కూడు_పని(Wayland_పని_Thread_Context *context, Wayland_పని_Thread_Callback callback, శూన్య *userdata, Wayland_పని_ID *id)
{
    ఒకవేళ (!callback) {
        తిరిగి false;
    }

    ఒకవేళ (context) {
        SDL_తాళం_Mutex(context->వరుస_తాళం);
        Wayland_పని *పని = SDL_calloc(1, పరిమాణం(Wayland_పని));
        ఒకవేళ (పని) {
            పని->id = context->id_counter++;
            ఒకవేళ (id) {
                *id = పని->id;
            }

            పని->callback = callback;
            పని->userdata = userdata;

            WAYLAND_wl_list_చొప్పించు(context->jobs.prev, &పని->link);

            SDL_SignalCondition(context->cond);
            SDL_UnlockMutex(context->వరుస_తాళం);

            తిరిగి true;
        }

        SDL_UnlockMutex(context->వరుస_తాళం);
        తిరిగి false;
    } లేకపోతే {
        // No thread? Just run the job.
        callback(userdata);
    }

    తిరిగి true;
}

శూన్య Wayland_పని_Thread_Cancel_పని(Wayland_పని_Thread_Context *context, Wayland_పని_ID id)
{
    ఒకవేళ (!context) {
        తిరిగి;
    }

    SDL_తాళం_Mutex(context->వరుస_తాళం);

    Wayland_పని *పని;
    wl_list_for_each (పని, &context->jobs, link) {
        ఒకవేళ (పని->id == id) {
            SDL_తాళం_Mutex(context->completion_తాళం);
            ఒకవేళ (పని->స్థితి_2 == పని_స్థితి_నిరీక్షణ) {
                // In the queue, waiting to run; mark as cancelled.
                పని->స్థితి_2 = పని_స్థితి_CANCELED;
            } లేకపోతే ఒకవేళ (పని->స్థితి_2 == పని_స్థితి_RUNNING) {
                // The job is running; wait for completion.
                పని->స్థితి_2 = పని_స్థితి_SIGNAL_PENDING;
                SDL_WaitCondition(context->cond, context->completion_తాళం);
            }
            SDL_UnlockMutex(context->completion_తాళం);
            ఆపు;
        }
    }

    SDL_UnlockMutex(context->వరుస_తాళం);
}

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_WAYLAND

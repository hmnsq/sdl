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

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#ಅನ್ತರ್ಭಾವ "../../core/unix/SDL_poll.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandeventthread.h"
#ಅನ್ತರ್ಭಾವ "SDL_waylandvideo.h"

#ಅನ್ತರ್ಭಾವ <errno.h>

ಪ್ರಕಾರನಿರ್ದೇಶ ಗಣನಾ Wayland_JobStatus
{
    JOB_STATUS_WAITING = 0,
    JOB_STATUS_RUNNING,
    JOB_STATUS_SIGNAL_PENDING,
    JOB_STATUS_SIGNALED,
    JOB_STATUS_CANCELED
} Wayland_JobStatus;

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ Wayland_Job
{
    Wayland_JobThreadCallback callback;
    ಶೂನ್ಯ *userdata;
    Wayland_JobID id;
    Wayland_JobStatus status;

    ಸಂರಚನಾ wl_list link;
} Wayland_Job;

ಸಂರಚನಾ Wayland_JobThreadContext
{
    SDL_Thread *thread;
    SDL_Mutex *queue_lock;
    SDL_Mutex *completion_lock;
    SDL_Condition *cond;
    ಸಂರಚನಾ wl_list jobs;
    Wayland_JobID id_counter;
    bool should_exit;
};

ಸಂರಚನಾ Wayland_EventThreadContext
{
    SDL_VideoData *wayland_data;
    SDL_Thread *thread;
    ಸಂರಚನಾ wl_event_queue *queue;
    SDL_Mutex *dispatch_lock;
    bool should_exit;
};

ಸ್ಥಿರ ಶೂನ್ಯ handle_event_thread_exit(ಶೂನ್ಯ *data, ಸಂರಚನಾ wl_callback *wl_callback, uint32_t callback_data)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)data;
    wl_callback_destroy(wl_callback);
    context->should_exit = true;
}

ಸ್ಥಿರ ಧ್ರುವ ಸಂರಚನಾ wl_callback_listener event_thread_exit_listener = {
    handle_event_thread_exit
};

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ SDLCALL Wayland_EventThreadFunc(ಶೂನ್ಯ *data)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)data;
    ಸಂರಚನಾ wl_display *display = context->wayland_data->display;
    ಧ್ರುವ ಪೂರ್ಣಾಙ್ಕ display_fd = WAYLAND_wl_display_get_fd(display);
    ಪೂರ್ಣಾಙ್ಕ ret;

    /* The lock must be held whenever dispatching to avoid a race condition when adding
     * or destroying objects using the queue.
     *
     * Any error other than EAGAIN is fatal and causes the thread to exit.
     */
    ಯಾವತ್ (!context->should_exit) {
        ಯದಿ (WAYLAND_wl_display_prepare_read_queue(display, context->queue) == 0) {
            Sint64 timeoutNS = -1;

            ret = WAYLAND_wl_display_flush(display);

            ಯದಿ (ret < 0) {
                ಯದಿ (errno == EAGAIN) {
                    // If the flush failed with EAGAIN, don't block as not to inhibit other threads from reading events.
                    timeoutNS = SDL_MS_TO_NS(1);
                } ಅನ್ಯಥಾ {
                    WAYLAND_wl_display_cancel_read(display);
                    ಪ್ರತ್ಯಾಗಮ -1;
                }
            }

            // Wait for a read/write operation to become possible.
            ret = SDL_IOReady(display_fd, SDL_IOR_READ, timeoutNS);

            ಯದಿ (ret <= 0) {
                WAYLAND_wl_display_cancel_read(display);
                ಯದಿ (ret < 0) {
                    ಪ್ರತ್ಯಾಗಮ -1;
                }

                // Nothing to read, and woke to flush; try again.
                ಅನುವರ್ತ;
            }

            ret = WAYLAND_wl_display_read_events(display);
            ಯದಿ (ret == -1) {
                ಪ್ರತ್ಯಾಗಮ -1;
            }
        }

        SDL_LockMutex(context->dispatch_lock);
        ret = WAYLAND_wl_display_dispatch_queue_pending(display, context->queue);
        SDL_UnlockMutex(context->dispatch_lock);

        ಯದಿ (ret < 0) {
            ಪ್ರತ್ಯಾಗಮ -1;
        }
    }

    ಪ್ರತ್ಯಾಗಮ 0;
}

Wayland_EventThreadContext *Wayland_CreateEventThread(SDL_VideoData *data, ಧ್ರುವ ವರ್ಣ *queue_name)
{
    Wayland_EventThreadContext *context = SDL_calloc(1, ಪರಿಮಾಣ(Wayland_EventThreadContext));
    ಯದಿ (!context) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    context->wayland_data = data;
    context->queue = Wayland_DisplayCreateQueue(data->display, queue_name);
    ಯದಿ (!context->queue) {
        ಗಚ್ಛ cleanup;
    }

    context->dispatch_lock = SDL_CreateMutex();
    ಯದಿ (!context->dispatch_lock) {
        ಗಚ್ಛ cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_EventThreadFunc, "wl_event_thread", context);
    ಯದಿ (!context->thread) {
        ಗಚ್ಛ cleanup;
    }

    ಪ್ರತ್ಯಾಗಮ context;

cleanup:
    ಯದಿ (context->dispatch_lock) {
        SDL_DestroyMutex(context->dispatch_lock);
    }

    ಯದಿ (context->queue) {
        WAYLAND_wl_event_queue_destroy(context->queue);
    }

    SDL_free(context);
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ಶೂನ್ಯ Wayland_DestroyEventThread(Wayland_EventThreadContext *context)
{
    ಯದಿ (context) {
        // Dispatch the exit event to unblock the thread and signal it to exit.
        ಸಂರಚನಾ wl_display *display = context->wayland_data->display;
        ಸಂರಚನಾ wl_proxy *display_wrapper = Wayland_CreateEventThreadProxyWrapper(context, display);

        SDL_LockMutex(context->dispatch_lock);
        ಸಂರಚನಾ wl_callback *cb = wl_display_sync((ಸಂರಚನಾ wl_display *)display_wrapper);
        wl_callback_add_listener(cb, &event_thread_exit_listener, context);
        SDL_UnlockMutex(context->dispatch_lock);

        WAYLAND_wl_proxy_wrapper_destroy(display_wrapper);

        ಪೂರ್ಣಾಙ್ಕ ret = WAYLAND_wl_display_flush(display);
        ಯಾವತ್ (ret == -1 && errno == EAGAIN) {
            // Shutting down the thread requires a successful flush.
            ret = SDL_IOReady(WAYLAND_wl_display_get_fd(display), SDL_IOR_WRITE, -1);
            ಯದಿ (ret >= 0) {
                ret = WAYLAND_wl_display_flush(display);
            }
        }

        // Avoid a warning if the flush failed due to a broken connection.
        ಯದಿ (ret < 0) {
            wl_callback_destroy(cb);
        }

        // Wait for the thread to return; it will exit automatically on a broken connection.
        SDL_WaitThread(context->thread, ರಿಕ್ತ);

        WAYLAND_wl_event_queue_destroy(context->queue);
        SDL_DestroyMutex(context->dispatch_lock);
        SDL_free(context);
    }
}

ಶೂನ್ಯ *Wayland_CreateEventThreadProxyWrapper(Wayland_EventThreadContext *context, ಶೂನ್ಯ *obj)
{
    ಸಂರಚನಾ wl_proxy *wrapper = WAYLAND_wl_proxy_create_wrapper(obj);
    ಯದಿ (wrapper && context) {
        WAYLAND_wl_proxy_set_queue(wrapper, context->queue);
    }

    ಪ್ರತ್ಯಾಗಮ wrapper;
}

ಶೂನ್ಯ Wayland_LockEventThread(Wayland_EventThreadContext *context)
{
    ಯದಿ (context) {
        SDL_LockMutex(context->dispatch_lock);
    }
}

ಶೂನ್ಯ Wayland_UnlockEventThread(Wayland_EventThreadContext *context)
{
    ಯದಿ (context) {
        SDL_UnlockMutex(context->dispatch_lock);
    }
}

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ SDLCALL Wayland_JobThreadFunc(ಶೂನ್ಯ *data)
{
    Wayland_JobThreadContext *context = (Wayland_JobThreadContext *)data;

    SDL_LockMutex(context->queue_lock);
    ಯಾವತ್ (!context->should_exit) {
        ಯದಿ (WAYLAND_wl_list_empty(&context->jobs)) {
            SDL_WaitCondition(context->cond, context->queue_lock);
        }

        Wayland_Job *job, *job_temp;
        wl_list_for_each_safe (job, job_temp, &context->jobs, link) {
            ಯದಿ (job->status == JOB_STATUS_WAITING) {
                job->status = JOB_STATUS_RUNNING;
            }

            // Don't block queue operations while dispatching the job.
            SDL_UnlockMutex(context->queue_lock);

            // If the job was cancelled, just remove it.
            ಯದಿ (job->status == JOB_STATUS_RUNNING) {
                job->callback(job->userdata);

                // Signal completion to the waiting thread.
                SDL_LockMutex(context->completion_lock);
                ಯದಿ (job->status == JOB_STATUS_SIGNAL_PENDING) {
                    SDL_SignalCondition(context->cond);
                }
                job->status = JOB_STATUS_SIGNALED;
                SDL_UnlockMutex(context->completion_lock);
            }

            SDL_LockMutex(context->queue_lock);

            WAYLAND_wl_list_remove(&job->link);
            SDL_free(job);
        }
    }
    SDL_UnlockMutex(context->queue_lock);

    ಪ್ರತ್ಯಾಗಮ 0;
}

ಬಾಹ್ಯ Wayland_JobThreadContext *Wayland_CreateJobThread()
{
    Wayland_JobThreadContext *context = SDL_calloc(1, ಪರಿಮಾಣ(Wayland_JobThreadContext));
    ಯದಿ (!context) {
        ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
    }

    WAYLAND_wl_list_init(&context->jobs);

    context->queue_lock = SDL_CreateMutex();
    ಯದಿ (!context->queue_lock) {
        ಗಚ್ಛ cleanup;
    }

    context->completion_lock = SDL_CreateMutex();
    ಯದಿ (!context->completion_lock) {
        ಗಚ್ಛ cleanup;
    }

    context->cond = SDL_CreateCondition();
    ಯದಿ (!context->cond) {
        ಗಚ್ಛ cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_JobThreadFunc, "wl_job_thread", context);
    ಯದಿ (!context->thread) {
        ಗಚ್ಛ cleanup;
    }

    ಪ್ರತ್ಯಾಗಮ context;

cleanup:
    ಯದಿ (context->queue_lock) {
        SDL_DestroyMutex(context->queue_lock);
    }

    ಯದಿ (context->completion_lock) {
        SDL_DestroyMutex(context->completion_lock);
    }

    ಯದಿ (context->cond) {
        SDL_DestroyCondition(context->cond);
    }

    SDL_free(context);

    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

ಸ್ಥಿರ ಶೂನ್ಯ job_thread_exit(ಶೂನ್ಯ *data)
{
    Wayland_JobThreadContext *context = (Wayland_JobThreadContext *)data;
    context->should_exit = true;
}

ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_DestroyJobThread(Wayland_JobThreadContext *context)
{
    ಯದಿ (!context) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    // Dispatch the exit job to unblock the thread and set the exit condition.
    Wayland_JobThreadAddJob(context, job_thread_exit, context, ರಿಕ್ತ);

    // Wait for the thread to return; all jobs will be complete at this point.
    SDL_WaitThread(context->thread, ರಿಕ್ತ);

    // Cleanup.
    SDL_DestroyCondition(context->cond);
    SDL_DestroyMutex(context->queue_lock);
    SDL_DestroyMutex(context->completion_lock);
    SDL_free(context);
}

bool Wayland_JobThreadAddJob(Wayland_JobThreadContext *context, Wayland_JobThreadCallback callback, ಶೂನ್ಯ *userdata, Wayland_JobID *id)
{
    ಯದಿ (!callback) {
        ಪ್ರತ್ಯಾಗಮ false;
    }

    ಯದಿ (context) {
        SDL_LockMutex(context->queue_lock);
        Wayland_Job *job = SDL_calloc(1, ಪರಿಮಾಣ(Wayland_Job));
        ಯದಿ (job) {
            job->id = context->id_counter++;
            ಯದಿ (id) {
                *id = job->id;
            }

            job->callback = callback;
            job->userdata = userdata;

            WAYLAND_wl_list_ಸೇರಿಸು(context->jobs.prev, &job->link);

            SDL_SignalCondition(context->cond);
            SDL_UnlockMutex(context->queue_lock);

            ಪ್ರತ್ಯಾಗಮ true;
        }

        SDL_UnlockMutex(context->queue_lock);
        ಪ್ರತ್ಯಾಗಮ false;
    } ಅನ್ಯಥಾ {
        // No thread? Just run the job.
        callback(userdata);
    }

    ಪ್ರತ್ಯಾಗಮ true;
}

ಶೂನ್ಯ Wayland_JobThreadCancelJob(Wayland_JobThreadContext *context, Wayland_JobID id)
{
    ಯದಿ (!context) {
        ಪ್ರತ್ಯಾಗಮ;
    }

    SDL_LockMutex(context->queue_lock);

    Wayland_Job *job;
    wl_list_for_each (job, &context->jobs, link) {
        ಯದಿ (job->id == id) {
            SDL_LockMutex(context->completion_lock);
            ಯದಿ (job->status == JOB_STATUS_WAITING) {
                // In the queue, waiting to run; mark as cancelled.
                job->status = JOB_STATUS_CANCELED;
            } ಅನ್ಯಥಾ ಯದಿ (job->status == JOB_STATUS_RUNNING) {
                // The job is running; wait for completion.
                job->status = JOB_STATUS_SIGNAL_PENDING;
                SDL_WaitCondition(context->cond, context->completion_lock);
            }
            SDL_UnlockMutex(context->completion_lock);
            ಭಙ್ಗ;
        }
    }

    SDL_UnlockMutex(context->queue_lock);
}

#endif // SDL_VIDEO_DRIVER_WAYLAND

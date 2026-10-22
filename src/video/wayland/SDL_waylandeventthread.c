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

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#شامل "../../core/unix/SDL_poll.h"
#شامل "SDL_waylandeventthread.h"
#شامل "SDL_waylandvideo.h"

#شامل <errno.h>

تعریفنوع شمارش Wayland_JobStatus
{
    JOB_STATUS_WAITING = 0,
    JOB_STATUS_RUNNING,
    JOB_STATUS_SIGNAL_PENDING,
    JOB_STATUS_SIGNALED,
    JOB_STATUS_CANCELED
} Wayland_JobStatus;

تعریفنوع ساختار Wayland_Job
{
    Wayland_JobThreadCallback callback;
    تهی *userdata;
    Wayland_JobID id;
    Wayland_JobStatus status;

    ساختار wl_list link;
} Wayland_Job;

ساختار Wayland_JobThreadContext
{
    SDL_Thread *thread;
    SDL_Mutex *queue_lock;
    SDL_Mutex *completion_lock;
    SDL_Condition *cond;
    ساختار wl_list jobs;
    Wayland_JobID id_counter;
    bool should_exit;
};

ساختار Wayland_EventThreadContext
{
    SDL_VideoData *wayland_data;
    SDL_Thread *thread;
    ساختار wl_event_queue *queue;
    SDL_Mutex *dispatch_lock;
    bool should_exit;
};

ایستا تهی handle_event_thread_exit(تهی *data, ساختار wl_callback *wl_callback, uint32_t callback_data)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)data;
    wl_callback_destroy(wl_callback);
    context->should_exit = true;
}

ایستا ثابت ساختار wl_callback_listener event_thread_exit_listener = {
    handle_event_thread_exit
};

ایستا صحیح SDLCALL Wayland_EventThreadFunc(تهی *data)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)data;
    ساختار wl_display *display = context->wayland_data->display;
    ثابت صحیح display_fd = WAYLAND_wl_display_get_fd(display);
    صحیح ret;

    /* The lock must be held whenever dispatching to avoid a race condition when adding
     * or destroying objects using the queue.
     *
     * Any error other than EAGAIN is fatal and causes the thread to exit.
     */
    وقتی (!context->should_exit) {
        اگر (WAYLAND_wl_display_prepare_read_queue(display, context->queue) == 0) {
            Sint64 timeoutNS = -1;

            ret = WAYLAND_wl_display_flush(display);

            اگر (ret < 0) {
                اگر (errno == EAGAIN) {
                    // If the flush failed with EAGAIN, don't block as not to inhibit other threads from reading events.
                    timeoutNS = SDL_MS_TO_NS(1);
                } وگرنه {
                    WAYLAND_wl_display_cancel_read(display);
                    بازگشت -1;
                }
            }

            // Wait for a read/write operation to become possible.
            ret = SDL_IOReady(display_fd, SDL_IOR_READ, timeoutNS);

            اگر (ret <= 0) {
                WAYLAND_wl_display_cancel_read(display);
                اگر (ret < 0) {
                    بازگشت -1;
                }

                // Nothing to read, and woke to flush; try again.
                ادامه;
            }

            ret = WAYLAND_wl_display_read_events(display);
            اگر (ret == -1) {
                بازگشت -1;
            }
        }

        SDL_LockMutex(context->dispatch_lock);
        ret = WAYLAND_wl_display_dispatch_queue_pending(display, context->queue);
        SDL_UnlockMutex(context->dispatch_lock);

        اگر (ret < 0) {
            بازگشت -1;
        }
    }

    بازگشت 0;
}

Wayland_EventThreadContext *Wayland_CreateEventThread(SDL_VideoData *data, ثابت نویسه *queue_name)
{
    Wayland_EventThreadContext *context = SDL_calloc(1, اندازه(Wayland_EventThreadContext));
    اگر (!context) {
        بازگشت پوچ;
    }

    context->wayland_data = data;
    context->queue = Wayland_DisplayCreateQueue(data->display, queue_name);
    اگر (!context->queue) {
        برو cleanup;
    }

    context->dispatch_lock = SDL_CreateMutex();
    اگر (!context->dispatch_lock) {
        برو cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_EventThreadFunc, "wl_event_thread", context);
    اگر (!context->thread) {
        برو cleanup;
    }

    بازگشت context;

cleanup:
    اگر (context->dispatch_lock) {
        SDL_DestroyMutex(context->dispatch_lock);
    }

    اگر (context->queue) {
        WAYLAND_wl_event_queue_destroy(context->queue);
    }

    SDL_free(context);
    بازگشت پوچ;
}

تهی Wayland_DestroyEventThread(Wayland_EventThreadContext *context)
{
    اگر (context) {
        // Dispatch the exit event to unblock the thread and signal it to exit.
        ساختار wl_display *display = context->wayland_data->display;
        ساختار wl_proxy *display_wrapper = Wayland_CreateEventThreadProxyWrapper(context, display);

        SDL_LockMutex(context->dispatch_lock);
        ساختار wl_callback *cb = wl_display_sync((ساختار wl_display *)display_wrapper);
        wl_callback_add_listener(cb, &event_thread_exit_listener, context);
        SDL_UnlockMutex(context->dispatch_lock);

        WAYLAND_wl_proxy_wrapper_destroy(display_wrapper);

        صحیح ret = WAYLAND_wl_display_flush(display);
        وقتی (ret == -1 && errno == EAGAIN) {
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
        SDL_WaitThread(context->thread, پوچ);

        WAYLAND_wl_event_queue_destroy(context->queue);
        SDL_DestroyMutex(context->dispatch_lock);
        SDL_free(context);
    }
}

تهی *Wayland_CreateEventThreadProxyWrapper(Wayland_EventThreadContext *context, تهی *obj)
{
    ساختار wl_proxy *wrapper = WAYLAND_wl_proxy_create_wrapper(obj);
    اگر (wrapper && context) {
        WAYLAND_wl_proxy_set_queue(wrapper, context->queue);
    }

    بازگشت wrapper;
}

تهی Wayland_LockEventThread(Wayland_EventThreadContext *context)
{
    اگر (context) {
        SDL_LockMutex(context->dispatch_lock);
    }
}

تهی Wayland_UnlockEventThread(Wayland_EventThreadContext *context)
{
    اگر (context) {
        SDL_UnlockMutex(context->dispatch_lock);
    }
}

ایستا صحیح SDLCALL Wayland_JobThreadFunc(تهی *data)
{
    Wayland_JobThreadContext *context = (Wayland_JobThreadContext *)data;

    SDL_LockMutex(context->queue_lock);
    وقتی (!context->should_exit) {
        اگر (WAYLAND_wl_list_empty(&context->jobs)) {
            SDL_WaitCondition(context->cond, context->queue_lock);
        }

        Wayland_Job *job, *job_temp;
        wl_list_for_each_safe (job, job_temp, &context->jobs, link) {
            اگر (job->status == JOB_STATUS_WAITING) {
                job->status = JOB_STATUS_RUNNING;
            }

            // Don't block queue operations while dispatching the job.
            SDL_UnlockMutex(context->queue_lock);

            // If the job was cancelled, just remove it.
            اگر (job->status == JOB_STATUS_RUNNING) {
                job->callback(job->userdata);

                // Signal completion to the waiting thread.
                SDL_LockMutex(context->completion_lock);
                اگر (job->status == JOB_STATUS_SIGNAL_PENDING) {
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

    بازگشت 0;
}

بیرونی Wayland_JobThreadContext *Wayland_CreateJobThread()
{
    Wayland_JobThreadContext *context = SDL_calloc(1, اندازه(Wayland_JobThreadContext));
    اگر (!context) {
        بازگشت پوچ;
    }

    WAYLAND_wl_list_init(&context->jobs);

    context->queue_lock = SDL_CreateMutex();
    اگر (!context->queue_lock) {
        برو cleanup;
    }

    context->completion_lock = SDL_CreateMutex();
    اگر (!context->completion_lock) {
        برو cleanup;
    }

    context->cond = SDL_CreateCondition();
    اگر (!context->cond) {
        برو cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_JobThreadFunc, "wl_job_thread", context);
    اگر (!context->thread) {
        برو cleanup;
    }

    بازگشت context;

cleanup:
    اگر (context->queue_lock) {
        SDL_DestroyMutex(context->queue_lock);
    }

    اگر (context->completion_lock) {
        SDL_DestroyMutex(context->completion_lock);
    }

    اگر (context->cond) {
        SDL_DestroyCondition(context->cond);
    }

    SDL_free(context);

    بازگشت پوچ;
}

ایستا تهی job_thread_exit(تهی *data)
{
    Wayland_JobThreadContext *context = (Wayland_JobThreadContext *)data;
    context->should_exit = true;
}

بیرونی تهی Wayland_DestroyJobThread(Wayland_JobThreadContext *context)
{
    اگر (!context) {
        بازگشت;
    }

    // Dispatch the exit job to unblock the thread and set the exit condition.
    Wayland_JobThreadAddJob(context, job_thread_exit, context, پوچ);

    // Wait for the thread to return; all jobs will be complete at this point.
    SDL_WaitThread(context->thread, پوچ);

    // Cleanup.
    SDL_DestroyCondition(context->cond);
    SDL_DestroyMutex(context->queue_lock);
    SDL_DestroyMutex(context->completion_lock);
    SDL_free(context);
}

bool Wayland_JobThreadAddJob(Wayland_JobThreadContext *context, Wayland_JobThreadCallback callback, تهی *userdata, Wayland_JobID *id)
{
    اگر (!callback) {
        بازگشت false;
    }

    اگر (context) {
        SDL_LockMutex(context->queue_lock);
        Wayland_Job *job = SDL_calloc(1, اندازه(Wayland_Job));
        اگر (job) {
            job->id = context->id_counter++;
            اگر (id) {
                *id = job->id;
            }

            job->callback = callback;
            job->userdata = userdata;

            WAYLAND_wl_list_درج(context->jobs.prev, &job->link);

            SDL_SignalCondition(context->cond);
            SDL_UnlockMutex(context->queue_lock);

            بازگشت true;
        }

        SDL_UnlockMutex(context->queue_lock);
        بازگشت false;
    } وگرنه {
        // No thread? Just run the job.
        callback(userdata);
    }

    بازگشت true;
}

تهی Wayland_JobThreadCancelJob(Wayland_JobThreadContext *context, Wayland_JobID id)
{
    اگر (!context) {
        بازگشت;
    }

    SDL_LockMutex(context->queue_lock);

    Wayland_Job *job;
    wl_list_for_each (job, &context->jobs, link) {
        اگر (job->id == id) {
            SDL_LockMutex(context->completion_lock);
            اگر (job->status == JOB_STATUS_WAITING) {
                // In the queue, waiting to run; mark as cancelled.
                job->status = JOB_STATUS_CANCELED;
            } وگرنه اگر (job->status == JOB_STATUS_RUNNING) {
                // The job is running; wait for completion.
                job->status = JOB_STATUS_SIGNAL_PENDING;
                SDL_WaitCondition(context->cond, context->completion_lock);
            }
            SDL_UnlockMutex(context->completion_lock);
            بشکن;
        }
    }

    SDL_UnlockMutex(context->queue_lock);
}

#endif // SDL_VIDEO_DRIVER_WAYLAND

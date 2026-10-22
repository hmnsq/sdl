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
#அந்தர்பாவ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#அந்தர்பாவ "../../core/unix/SDL_poll.h"
#அந்தர்பாவ "SDL_waylandeventthread.h"
#அந்தர்பாவ "SDL_waylandvideo.h"

#அந்தர்பாவ <errno.h>

வகைவரை எண்ணிக்கை Wayland_JobStatus
{
    JOB_STATUS_WAITING = 0,
    JOB_STATUS_RUNNING,
    JOB_STATUS_SIGNAL_PENDING,
    JOB_STATUS_SIGNALED,
    JOB_STATUS_CANCELED
} Wayland_JobStatus;

வகைவரை கட்டமைப்பு Wayland_Job
{
    Wayland_JobThreadCallback callback;
    வெறுமை *userdata;
    Wayland_JobID id;
    Wayland_JobStatus status;

    கட்டமைப்பு wl_list link;
} Wayland_Job;

கட்டமைப்பு Wayland_JobThreadContext
{
    SDL_Thread *thread;
    SDL_Mutex *queue_lock;
    SDL_Mutex *completion_lock;
    SDL_Condition *cond;
    கட்டமைப்பு wl_list jobs;
    Wayland_JobID id_counter;
    bool should_exit;
};

கட்டமைப்பு Wayland_EventThreadContext
{
    SDL_VideoData *wayland_data;
    SDL_Thread *thread;
    கட்டமைப்பு wl_event_queue *queue;
    SDL_Mutex *dispatch_lock;
    bool should_exit;
};

நிலையான வெறுமை handle_event_thread_exit(வெறுமை *data, கட்டமைப்பு wl_callback *wl_callback, uint32_t callback_data)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)data;
    wl_callback_destroy(wl_callback);
    context->should_exit = true;
}

நிலையான மாறிலி கட்டமைப்பு wl_callback_listener event_thread_exit_listener = {
    handle_event_thread_exit
};

நிலையான முழு SDLCALL Wayland_EventThreadFunc(வெறுமை *data)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)data;
    கட்டமைப்பு wl_display *display = context->wayland_data->display;
    மாறிலி முழு display_fd = WAYLAND_wl_display_get_fd(display);
    முழு ret;

    /* The lock must be held whenever dispatching to avoid a race condition when adding
     * or destroying objects using the queue.
     *
     * Any error other than EAGAIN is fatal and causes the thread to exit.
     */
    போது (!context->should_exit) {
        எனில் (WAYLAND_wl_display_prepare_read_queue(display, context->queue) == 0) {
            Sint64 timeoutNS = -1;

            ret = WAYLAND_wl_display_flush(display);

            எனில் (ret < 0) {
                எனில் (errno == EAGAIN) {
                    // If the flush failed with EAGAIN, don't block as not to inhibit other threads from reading events.
                    timeoutNS = SDL_MS_TO_NS(1);
                } இல்லையெனில் {
                    WAYLAND_wl_display_cancel_read(display);
                    திரும்பு -1;
                }
            }

            // Wait for a read/write operation to become possible.
            ret = SDL_IOReady(display_fd, SDL_IOR_READ, timeoutNS);

            எனில் (ret <= 0) {
                WAYLAND_wl_display_cancel_read(display);
                எனில் (ret < 0) {
                    திரும்பு -1;
                }

                // Nothing to read, and woke to flush; try again.
                தொடர்;
            }

            ret = WAYLAND_wl_display_read_events(display);
            எனில் (ret == -1) {
                திரும்பு -1;
            }
        }

        SDL_LockMutex(context->dispatch_lock);
        ret = WAYLAND_wl_display_dispatch_queue_pending(display, context->queue);
        SDL_UnlockMutex(context->dispatch_lock);

        எனில் (ret < 0) {
            திரும்பு -1;
        }
    }

    திரும்பு 0;
}

Wayland_EventThreadContext *Wayland_CreateEventThread(SDL_VideoData *data, மாறிலி எழுத்து *queue_name)
{
    Wayland_EventThreadContext *context = SDL_calloc(1, அளவு(Wayland_EventThreadContext));
    எனில் (!context) {
        திரும்பு வெற்று;
    }

    context->wayland_data = data;
    context->queue = Wayland_DisplayCreateQueue(data->display, queue_name);
    எனில் (!context->queue) {
        செல் cleanup;
    }

    context->dispatch_lock = SDL_CreateMutex();
    எனில் (!context->dispatch_lock) {
        செல் cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_EventThreadFunc, "wl_event_thread", context);
    எனில் (!context->thread) {
        செல் cleanup;
    }

    திரும்பு context;

cleanup:
    எனில் (context->dispatch_lock) {
        SDL_DestroyMutex(context->dispatch_lock);
    }

    எனில் (context->queue) {
        WAYLAND_wl_event_queue_destroy(context->queue);
    }

    SDL_free(context);
    திரும்பு வெற்று;
}

வெறுமை Wayland_DestroyEventThread(Wayland_EventThreadContext *context)
{
    எனில் (context) {
        // Dispatch the exit event to unblock the thread and signal it to exit.
        கட்டமைப்பு wl_display *display = context->wayland_data->display;
        கட்டமைப்பு wl_proxy *display_wrapper = Wayland_CreateEventThreadProxyWrapper(context, display);

        SDL_LockMutex(context->dispatch_lock);
        கட்டமைப்பு wl_callback *cb = wl_display_sync((கட்டமைப்பு wl_display *)display_wrapper);
        wl_callback_add_listener(cb, &event_thread_exit_listener, context);
        SDL_UnlockMutex(context->dispatch_lock);

        WAYLAND_wl_proxy_wrapper_destroy(display_wrapper);

        முழு ret = WAYLAND_wl_display_flush(display);
        போது (ret == -1 && errno == EAGAIN) {
            // Shutting down the thread requires a successful flush.
            ret = SDL_IOReady(WAYLAND_wl_display_get_fd(display), SDL_IOR_WRITE, -1);
            எனில் (ret >= 0) {
                ret = WAYLAND_wl_display_flush(display);
            }
        }

        // Avoid a warning if the flush failed due to a broken connection.
        எனில் (ret < 0) {
            wl_callback_destroy(cb);
        }

        // Wait for the thread to return; it will exit automatically on a broken connection.
        SDL_WaitThread(context->thread, வெற்று);

        WAYLAND_wl_event_queue_destroy(context->queue);
        SDL_DestroyMutex(context->dispatch_lock);
        SDL_free(context);
    }
}

வெறுமை *Wayland_CreateEventThreadProxyWrapper(Wayland_EventThreadContext *context, வெறுமை *obj)
{
    கட்டமைப்பு wl_proxy *wrapper = WAYLAND_wl_proxy_create_wrapper(obj);
    எனில் (wrapper && context) {
        WAYLAND_wl_proxy_set_queue(wrapper, context->queue);
    }

    திரும்பு wrapper;
}

வெறுமை Wayland_LockEventThread(Wayland_EventThreadContext *context)
{
    எனில் (context) {
        SDL_LockMutex(context->dispatch_lock);
    }
}

வெறுமை Wayland_UnlockEventThread(Wayland_EventThreadContext *context)
{
    எனில் (context) {
        SDL_UnlockMutex(context->dispatch_lock);
    }
}

நிலையான முழு SDLCALL Wayland_JobThreadFunc(வெறுமை *data)
{
    Wayland_JobThreadContext *context = (Wayland_JobThreadContext *)data;

    SDL_LockMutex(context->queue_lock);
    போது (!context->should_exit) {
        எனில் (WAYLAND_wl_list_empty(&context->jobs)) {
            SDL_WaitCondition(context->cond, context->queue_lock);
        }

        Wayland_Job *job, *job_temp;
        wl_list_for_each_safe (job, job_temp, &context->jobs, link) {
            எனில் (job->status == JOB_STATUS_WAITING) {
                job->status = JOB_STATUS_RUNNING;
            }

            // Don't block queue operations while dispatching the job.
            SDL_UnlockMutex(context->queue_lock);

            // If the job was cancelled, just remove it.
            எனில் (job->status == JOB_STATUS_RUNNING) {
                job->callback(job->userdata);

                // Signal completion to the waiting thread.
                SDL_LockMutex(context->completion_lock);
                எனில் (job->status == JOB_STATUS_SIGNAL_PENDING) {
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

    திரும்பு 0;
}

வெளி Wayland_JobThreadContext *Wayland_CreateJobThread()
{
    Wayland_JobThreadContext *context = SDL_calloc(1, அளவு(Wayland_JobThreadContext));
    எனில் (!context) {
        திரும்பு வெற்று;
    }

    WAYLAND_wl_list_init(&context->jobs);

    context->queue_lock = SDL_CreateMutex();
    எனில் (!context->queue_lock) {
        செல் cleanup;
    }

    context->completion_lock = SDL_CreateMutex();
    எனில் (!context->completion_lock) {
        செல் cleanup;
    }

    context->cond = SDL_CreateCondition();
    எனில் (!context->cond) {
        செல் cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_JobThreadFunc, "wl_job_thread", context);
    எனில் (!context->thread) {
        செல் cleanup;
    }

    திரும்பு context;

cleanup:
    எனில் (context->queue_lock) {
        SDL_DestroyMutex(context->queue_lock);
    }

    எனில் (context->completion_lock) {
        SDL_DestroyMutex(context->completion_lock);
    }

    எனில் (context->cond) {
        SDL_DestroyCondition(context->cond);
    }

    SDL_free(context);

    திரும்பு வெற்று;
}

நிலையான வெறுமை job_thread_exit(வெறுமை *data)
{
    Wayland_JobThreadContext *context = (Wayland_JobThreadContext *)data;
    context->should_exit = true;
}

வெளி வெறுமை Wayland_DestroyJobThread(Wayland_JobThreadContext *context)
{
    எனில் (!context) {
        திரும்பு;
    }

    // Dispatch the exit job to unblock the thread and set the exit condition.
    Wayland_JobThreadAddJob(context, job_thread_exit, context, வெற்று);

    // Wait for the thread to return; all jobs will be complete at this point.
    SDL_WaitThread(context->thread, வெற்று);

    // Cleanup.
    SDL_DestroyCondition(context->cond);
    SDL_DestroyMutex(context->queue_lock);
    SDL_DestroyMutex(context->completion_lock);
    SDL_free(context);
}

bool Wayland_JobThreadAddJob(Wayland_JobThreadContext *context, Wayland_JobThreadCallback callback, வெறுமை *userdata, Wayland_JobID *id)
{
    எனில் (!callback) {
        திரும்பு false;
    }

    எனில் (context) {
        SDL_LockMutex(context->queue_lock);
        Wayland_Job *job = SDL_calloc(1, அளவு(Wayland_Job));
        எனில் (job) {
            job->id = context->id_counter++;
            எனில் (id) {
                *id = job->id;
            }

            job->callback = callback;
            job->userdata = userdata;

            WAYLAND_wl_list_செருகு(context->jobs.prev, &job->link);

            SDL_SignalCondition(context->cond);
            SDL_UnlockMutex(context->queue_lock);

            திரும்பு true;
        }

        SDL_UnlockMutex(context->queue_lock);
        திரும்பு false;
    } இல்லையெனில் {
        // No thread? Just run the job.
        callback(userdata);
    }

    திரும்பு true;
}

வெறுமை Wayland_JobThreadCancelJob(Wayland_JobThreadContext *context, Wayland_JobID id)
{
    எனில் (!context) {
        திரும்பு;
    }

    SDL_LockMutex(context->queue_lock);

    Wayland_Job *job;
    wl_list_for_each (job, &context->jobs, link) {
        எனில் (job->id == id) {
            SDL_LockMutex(context->completion_lock);
            எனில் (job->status == JOB_STATUS_WAITING) {
                // In the queue, waiting to run; mark as cancelled.
                job->status = JOB_STATUS_CANCELED;
            } இல்லையெனில் எனில் (job->status == JOB_STATUS_RUNNING) {
                // The job is running; wait for completion.
                job->status = JOB_STATUS_SIGNAL_PENDING;
                SDL_WaitCondition(context->cond, context->completion_lock);
            }
            SDL_UnlockMutex(context->completion_lock);
            நிறுத்து;
        }
    }

    SDL_UnlockMutex(context->queue_lock);
}

#endif // SDL_VIDEO_DRIVER_WAYLAND

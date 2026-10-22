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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#ଅନ୍ତର୍ଭାଵ "../../core/unix/SDL_poll.h"
#ଅନ୍ତର୍ଭାଵ "SDL_waylandeventthread.h"
#ଅନ୍ତର୍ଭାଵ "SDL_waylandvideo.h"

#ଅନ୍ତର୍ଭାଵ <errno.h>

ପ୍ରକାରବ୍ୟାଖ୍ୟା ଗଣନା Wayland_JobStatus
{
    JOB_STATUS_WAITING = 0,
    JOB_STATUS_RUNNING,
    JOB_STATUS_SIGNAL_PENDING,
    JOB_STATUS_SIGNALED,
    JOB_STATUS_CANCELED
} Wayland_JobStatus;

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା Wayland_Job
{
    Wayland_JobThreadCallback callback;
    ଶୂନ୍ୟ *userdata;
    Wayland_JobID id;
    Wayland_JobStatus status;

    ସଂରଚନା wl_list link;
} Wayland_Job;

ସଂରଚନା Wayland_JobThreadContext
{
    SDL_Thread *thread;
    SDL_Mutex *queue_lock;
    SDL_Mutex *completion_lock;
    SDL_Condition *cond;
    ସଂରଚନା wl_list jobs;
    Wayland_JobID id_counter;
    bool should_exit;
};

ସଂରଚନା Wayland_EventThreadContext
{
    SDL_VideoData *wayland_data;
    SDL_Thread *thread;
    ସଂରଚନା wl_event_queue *queue;
    SDL_Mutex *dispatch_lock;
    bool should_exit;
};

ସ୍ଥିର ଶୂନ୍ୟ handle_event_thread_exit(ଶୂନ୍ୟ *data, ସଂରଚନା wl_callback *wl_callback, uint32_t callback_data)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)data;
    wl_callback_destroy(wl_callback);
    context->should_exit = true;
}

ସ୍ଥିର ଅଚଳ ସଂରଚନା wl_callback_listener event_thread_exit_listener = {
    handle_event_thread_exit
};

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା SDLCALL Wayland_EventThreadFunc(ଶୂନ୍ୟ *data)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)data;
    ସଂରଚନା wl_display *display = context->wayland_data->display;
    ଅଚଳ ପୂର୍ଣ୍ଣସଂଖ୍ୟା display_fd = WAYLAND_wl_display_get_fd(display);
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret;

    /* The lock must be held whenever dispatching to avoid a race condition when adding
     * or destroying objects using the queue.
     *
     * Any error other than EAGAIN is fatal and causes the thread to exit.
     */
    ଯେତେବେଳେ (!context->should_exit) {
        ଯଦି (WAYLAND_wl_display_prepare_read_queue(display, context->queue) == 0) {
            Sint64 timeoutNS = -1;

            ret = WAYLAND_wl_display_flush(display);

            ଯଦି (ret < 0) {
                ଯଦି (errno == EAGAIN) {
                    // If the flush failed with EAGAIN, don't block as not to inhibit other threads from reading events.
                    timeoutNS = SDL_MS_TO_NS(1);
                } ଅନ୍ୟଥା {
                    WAYLAND_wl_display_cancel_read(display);
                    ଫେରନ୍ତୁ -1;
                }
            }

            // Wait for a read/write operation to become possible.
            ret = SDL_IOReady(display_fd, SDL_IOR_READ, timeoutNS);

            ଯଦି (ret <= 0) {
                WAYLAND_wl_display_cancel_read(display);
                ଯଦି (ret < 0) {
                    ଫେରନ୍ତୁ -1;
                }

                // Nothing to read, and woke to flush; try again.
                ଜାରି;
            }

            ret = WAYLAND_wl_display_read_events(display);
            ଯଦି (ret == -1) {
                ଫେରନ୍ତୁ -1;
            }
        }

        SDL_LockMutex(context->dispatch_lock);
        ret = WAYLAND_wl_display_dispatch_queue_pending(display, context->queue);
        SDL_UnlockMutex(context->dispatch_lock);

        ଯଦି (ret < 0) {
            ଫେରନ୍ତୁ -1;
        }
    }

    ଫେରନ୍ତୁ 0;
}

Wayland_EventThreadContext *Wayland_CreateEventThread(SDL_VideoData *data, ଅଚଳ ଅକ୍ଷର *queue_name)
{
    Wayland_EventThreadContext *context = SDL_calloc(1, ଆକାର(Wayland_EventThreadContext));
    ଯଦି (!context) {
        ଫେରନ୍ତୁ ଖାଲି;
    }

    context->wayland_data = data;
    context->queue = Wayland_DisplayCreateQueue(data->display, queue_name);
    ଯଦି (!context->queue) {
        ଯାଅ cleanup;
    }

    context->dispatch_lock = SDL_CreateMutex();
    ଯଦି (!context->dispatch_lock) {
        ଯାଅ cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_EventThreadFunc, "wl_event_thread", context);
    ଯଦି (!context->thread) {
        ଯାଅ cleanup;
    }

    ଫେରନ୍ତୁ context;

cleanup:
    ଯଦି (context->dispatch_lock) {
        SDL_DestroyMutex(context->dispatch_lock);
    }

    ଯଦି (context->queue) {
        WAYLAND_wl_event_queue_destroy(context->queue);
    }

    SDL_free(context);
    ଫେରନ୍ତୁ ଖାଲି;
}

ଶୂନ୍ୟ Wayland_DestroyEventThread(Wayland_EventThreadContext *context)
{
    ଯଦି (context) {
        // Dispatch the exit event to unblock the thread and signal it to exit.
        ସଂରଚନା wl_display *display = context->wayland_data->display;
        ସଂରଚନା wl_proxy *display_wrapper = Wayland_CreateEventThreadProxyWrapper(context, display);

        SDL_LockMutex(context->dispatch_lock);
        ସଂରଚନା wl_callback *cb = wl_display_sync((ସଂରଚନା wl_display *)display_wrapper);
        wl_callback_add_listener(cb, &event_thread_exit_listener, context);
        SDL_UnlockMutex(context->dispatch_lock);

        WAYLAND_wl_proxy_wrapper_destroy(display_wrapper);

        ପୂର୍ଣ୍ଣସଂଖ୍ୟା ret = WAYLAND_wl_display_flush(display);
        ଯେତେବେଳେ (ret == -1 && errno == EAGAIN) {
            // Shutting down the thread requires a successful flush.
            ret = SDL_IOReady(WAYLAND_wl_display_get_fd(display), SDL_IOR_WRITE, -1);
            ଯଦି (ret >= 0) {
                ret = WAYLAND_wl_display_flush(display);
            }
        }

        // Avoid a warning if the flush failed due to a broken connection.
        ଯଦି (ret < 0) {
            wl_callback_destroy(cb);
        }

        // Wait for the thread to return; it will exit automatically on a broken connection.
        SDL_WaitThread(context->thread, ଖାଲି);

        WAYLAND_wl_event_queue_destroy(context->queue);
        SDL_DestroyMutex(context->dispatch_lock);
        SDL_free(context);
    }
}

ଶୂନ୍ୟ *Wayland_CreateEventThreadProxyWrapper(Wayland_EventThreadContext *context, ଶୂନ୍ୟ *obj)
{
    ସଂରଚନା wl_proxy *wrapper = WAYLAND_wl_proxy_create_wrapper(obj);
    ଯଦି (wrapper && context) {
        WAYLAND_wl_proxy_set_queue(wrapper, context->queue);
    }

    ଫେରନ୍ତୁ wrapper;
}

ଶୂନ୍ୟ Wayland_LockEventThread(Wayland_EventThreadContext *context)
{
    ଯଦି (context) {
        SDL_LockMutex(context->dispatch_lock);
    }
}

ଶୂନ୍ୟ Wayland_UnlockEventThread(Wayland_EventThreadContext *context)
{
    ଯଦି (context) {
        SDL_UnlockMutex(context->dispatch_lock);
    }
}

ସ୍ଥିର ପୂର୍ଣ୍ଣସଂଖ୍ୟା SDLCALL Wayland_JobThreadFunc(ଶୂନ୍ୟ *data)
{
    Wayland_JobThreadContext *context = (Wayland_JobThreadContext *)data;

    SDL_LockMutex(context->queue_lock);
    ଯେତେବେଳେ (!context->should_exit) {
        ଯଦି (WAYLAND_wl_list_empty(&context->jobs)) {
            SDL_WaitCondition(context->cond, context->queue_lock);
        }

        Wayland_Job *job, *job_temp;
        wl_list_for_each_safe (job, job_temp, &context->jobs, link) {
            ଯଦି (job->status == JOB_STATUS_WAITING) {
                job->status = JOB_STATUS_RUNNING;
            }

            // Don't block queue operations while dispatching the job.
            SDL_UnlockMutex(context->queue_lock);

            // If the job was cancelled, just remove it.
            ଯଦି (job->status == JOB_STATUS_RUNNING) {
                job->callback(job->userdata);

                // Signal completion to the waiting thread.
                SDL_LockMutex(context->completion_lock);
                ଯଦି (job->status == JOB_STATUS_SIGNAL_PENDING) {
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

    ଫେରନ୍ତୁ 0;
}

ବାହ୍ୟ Wayland_JobThreadContext *Wayland_CreateJobThread()
{
    Wayland_JobThreadContext *context = SDL_calloc(1, ଆକାର(Wayland_JobThreadContext));
    ଯଦି (!context) {
        ଫେରନ୍ତୁ ଖାଲି;
    }

    WAYLAND_wl_list_init(&context->jobs);

    context->queue_lock = SDL_CreateMutex();
    ଯଦି (!context->queue_lock) {
        ଯାଅ cleanup;
    }

    context->completion_lock = SDL_CreateMutex();
    ଯଦି (!context->completion_lock) {
        ଯାଅ cleanup;
    }

    context->cond = SDL_CreateCondition();
    ଯଦି (!context->cond) {
        ଯାଅ cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_JobThreadFunc, "wl_job_thread", context);
    ଯଦି (!context->thread) {
        ଯାଅ cleanup;
    }

    ଫେରନ୍ତୁ context;

cleanup:
    ଯଦି (context->queue_lock) {
        SDL_DestroyMutex(context->queue_lock);
    }

    ଯଦି (context->completion_lock) {
        SDL_DestroyMutex(context->completion_lock);
    }

    ଯଦି (context->cond) {
        SDL_DestroyCondition(context->cond);
    }

    SDL_free(context);

    ଫେରନ୍ତୁ ଖାଲି;
}

ସ୍ଥିର ଶୂନ୍ୟ job_thread_exit(ଶୂନ୍ୟ *data)
{
    Wayland_JobThreadContext *context = (Wayland_JobThreadContext *)data;
    context->should_exit = true;
}

ବାହ୍ୟ ଶୂନ୍ୟ Wayland_DestroyJobThread(Wayland_JobThreadContext *context)
{
    ଯଦି (!context) {
        ଫେରନ୍ତୁ;
    }

    // Dispatch the exit job to unblock the thread and set the exit condition.
    Wayland_JobThreadAddJob(context, job_thread_exit, context, ଖାଲି);

    // Wait for the thread to return; all jobs will be complete at this point.
    SDL_WaitThread(context->thread, ଖାଲି);

    // Cleanup.
    SDL_DestroyCondition(context->cond);
    SDL_DestroyMutex(context->queue_lock);
    SDL_DestroyMutex(context->completion_lock);
    SDL_free(context);
}

bool Wayland_JobThreadAddJob(Wayland_JobThreadContext *context, Wayland_JobThreadCallback callback, ଶୂନ୍ୟ *userdata, Wayland_JobID *id)
{
    ଯଦି (!callback) {
        ଫେରନ୍ତୁ false;
    }

    ଯଦି (context) {
        SDL_LockMutex(context->queue_lock);
        Wayland_Job *job = SDL_calloc(1, ଆକାର(Wayland_Job));
        ଯଦି (job) {
            job->id = context->id_counter++;
            ଯଦି (id) {
                *id = job->id;
            }

            job->callback = callback;
            job->userdata = userdata;

            WAYLAND_wl_list_ଭର୍ତ୍ତି(context->jobs.prev, &job->link);

            SDL_SignalCondition(context->cond);
            SDL_UnlockMutex(context->queue_lock);

            ଫେରନ୍ତୁ true;
        }

        SDL_UnlockMutex(context->queue_lock);
        ଫେରନ୍ତୁ false;
    } ଅନ୍ୟଥା {
        // No thread? Just run the job.
        callback(userdata);
    }

    ଫେରନ୍ତୁ true;
}

ଶୂନ୍ୟ Wayland_JobThreadCancelJob(Wayland_JobThreadContext *context, Wayland_JobID id)
{
    ଯଦି (!context) {
        ଫେରନ୍ତୁ;
    }

    SDL_LockMutex(context->queue_lock);

    Wayland_Job *job;
    wl_list_for_each (job, &context->jobs, link) {
        ଯଦି (job->id == id) {
            SDL_LockMutex(context->completion_lock);
            ଯଦି (job->status == JOB_STATUS_WAITING) {
                // In the queue, waiting to run; mark as cancelled.
                job->status = JOB_STATUS_CANCELED;
            } ଅନ୍ୟଥା ଯଦି (job->status == JOB_STATUS_RUNNING) {
                // The job is running; wait for completion.
                job->status = JOB_STATUS_SIGNAL_PENDING;
                SDL_WaitCondition(context->cond, context->completion_lock);
            }
            SDL_UnlockMutex(context->completion_lock);
            ଭାଙ୍ଗ;
        }
    }

    SDL_UnlockMutex(context->queue_lock);
}

#endif // SDL_VIDEO_DRIVER_WAYLAND

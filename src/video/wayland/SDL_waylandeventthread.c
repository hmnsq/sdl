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
#অন্তর্ভাব "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#অন্তর্ভাব "../../core/unix/SDL_poll.h"
#অন্তর্ভাব "SDL_waylandeventthread.h"
#অন্তর্ভাব "SDL_waylandvideo.h"

#অন্তর্ভাব <errno.h>

প্রকারনির্দেশ গণনা Wayland_JobStatus
{
    JOB_STATUS_WAITING = 0,
    JOB_STATUS_RUNNING,
    JOB_STATUS_SIGNAL_PENDING,
    JOB_STATUS_SIGNALED,
    JOB_STATUS_CANCELED
} Wayland_JobStatus;

প্রকারনির্দেশ সংরচনা Wayland_Job
{
    Wayland_JobThreadCallback callback;
    শূন্য *userdata;
    Wayland_JobID id;
    Wayland_JobStatus status;

    সংরচনা wl_list link;
} Wayland_Job;

সংরচনা Wayland_JobThreadContext
{
    SDL_Thread *thread;
    SDL_Mutex *queue_lock;
    SDL_Mutex *completion_lock;
    SDL_Condition *cond;
    সংরচনা wl_list jobs;
    Wayland_JobID id_counter;
    bool should_exit;
};

সংরচনা Wayland_EventThreadContext
{
    SDL_VideoData *wayland_data;
    SDL_Thread *thread;
    সংরচনা wl_event_queue *queue;
    SDL_Mutex *dispatch_lock;
    bool should_exit;
};

স্থির শূন্য handle_event_thread_exit(শূন্য *data, সংরচনা wl_callback *wl_callback, uint32_t callback_data)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)data;
    wl_callback_destroy(wl_callback);
    context->should_exit = true;
}

স্থির ধ্রুব সংরচনা wl_callback_listener event_thread_exit_listener = {
    handle_event_thread_exit
};

স্থির পূর্ণাঙ্ক SDLCALL Wayland_EventThreadFunc(শূন্য *data)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)data;
    সংরচনা wl_display *display = context->wayland_data->display;
    ধ্রুব পূর্ণাঙ্ক display_fd = WAYLAND_wl_display_get_fd(display);
    পূর্ণাঙ্ক ret;

    /* The lock must be held whenever dispatching to avoid a race condition when adding
     * or destroying objects using the queue.
     *
     * Any error other than EAGAIN is fatal and causes the thread to exit.
     */
    যাবত্ (!context->should_exit) {
        যদি (WAYLAND_wl_display_prepare_read_queue(display, context->queue) == 0) {
            Sint64 timeoutNS = -1;

            ret = WAYLAND_wl_display_flush(display);

            যদি (ret < 0) {
                যদি (errno == EAGAIN) {
                    // If the flush failed with EAGAIN, don't block as not to inhibit other threads from reading events.
                    timeoutNS = SDL_MS_TO_NS(1);
                } অন্যথা {
                    WAYLAND_wl_display_cancel_read(display);
                    প্রত্যাগম -1;
                }
            }

            // Wait for a read/write operation to become possible.
            ret = SDL_IOReady(display_fd, SDL_IOR_READ, timeoutNS);

            যদি (ret <= 0) {
                WAYLAND_wl_display_cancel_read(display);
                যদি (ret < 0) {
                    প্রত্যাগম -1;
                }

                // Nothing to read, and woke to flush; try again.
                অনুবর্ত;
            }

            ret = WAYLAND_wl_display_read_events(display);
            যদি (ret == -1) {
                প্রত্যাগম -1;
            }
        }

        SDL_LockMutex(context->dispatch_lock);
        ret = WAYLAND_wl_display_dispatch_queue_pending(display, context->queue);
        SDL_UnlockMutex(context->dispatch_lock);

        যদি (ret < 0) {
            প্রত্যাগম -1;
        }
    }

    প্রত্যাগম 0;
}

Wayland_EventThreadContext *Wayland_CreateEventThread(SDL_VideoData *data, ধ্রুব বর্ণ *queue_name)
{
    Wayland_EventThreadContext *context = SDL_calloc(1, পরিমাণ(Wayland_EventThreadContext));
    যদি (!context) {
        প্রত্যাগম রিক্ত;
    }

    context->wayland_data = data;
    context->queue = Wayland_DisplayCreateQueue(data->display, queue_name);
    যদি (!context->queue) {
        গচ্ছ cleanup;
    }

    context->dispatch_lock = SDL_CreateMutex();
    যদি (!context->dispatch_lock) {
        গচ্ছ cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_EventThreadFunc, "wl_event_thread", context);
    যদি (!context->thread) {
        গচ্ছ cleanup;
    }

    প্রত্যাগম context;

cleanup:
    যদি (context->dispatch_lock) {
        SDL_DestroyMutex(context->dispatch_lock);
    }

    যদি (context->queue) {
        WAYLAND_wl_event_queue_destroy(context->queue);
    }

    SDL_free(context);
    প্রত্যাগম রিক্ত;
}

শূন্য Wayland_DestroyEventThread(Wayland_EventThreadContext *context)
{
    যদি (context) {
        // Dispatch the exit event to unblock the thread and signal it to exit.
        সংরচনা wl_display *display = context->wayland_data->display;
        সংরচনা wl_proxy *display_wrapper = Wayland_CreateEventThreadProxyWrapper(context, display);

        SDL_LockMutex(context->dispatch_lock);
        সংরচনা wl_callback *cb = wl_display_sync((সংরচনা wl_display *)display_wrapper);
        wl_callback_add_listener(cb, &event_thread_exit_listener, context);
        SDL_UnlockMutex(context->dispatch_lock);

        WAYLAND_wl_proxy_wrapper_destroy(display_wrapper);

        পূর্ণাঙ্ক ret = WAYLAND_wl_display_flush(display);
        যাবত্ (ret == -1 && errno == EAGAIN) {
            // Shutting down the thread requires a successful flush.
            ret = SDL_IOReady(WAYLAND_wl_display_get_fd(display), SDL_IOR_WRITE, -1);
            যদি (ret >= 0) {
                ret = WAYLAND_wl_display_flush(display);
            }
        }

        // Avoid a warning if the flush failed due to a broken connection.
        যদি (ret < 0) {
            wl_callback_destroy(cb);
        }

        // Wait for the thread to return; it will exit automatically on a broken connection.
        SDL_WaitThread(context->thread, রিক্ত);

        WAYLAND_wl_event_queue_destroy(context->queue);
        SDL_DestroyMutex(context->dispatch_lock);
        SDL_free(context);
    }
}

শূন্য *Wayland_CreateEventThreadProxyWrapper(Wayland_EventThreadContext *context, শূন্য *obj)
{
    সংরচনা wl_proxy *wrapper = WAYLAND_wl_proxy_create_wrapper(obj);
    যদি (wrapper && context) {
        WAYLAND_wl_proxy_set_queue(wrapper, context->queue);
    }

    প্রত্যাগম wrapper;
}

শূন্য Wayland_LockEventThread(Wayland_EventThreadContext *context)
{
    যদি (context) {
        SDL_LockMutex(context->dispatch_lock);
    }
}

শূন্য Wayland_UnlockEventThread(Wayland_EventThreadContext *context)
{
    যদি (context) {
        SDL_UnlockMutex(context->dispatch_lock);
    }
}

স্থির পূর্ণাঙ্ক SDLCALL Wayland_JobThreadFunc(শূন্য *data)
{
    Wayland_JobThreadContext *context = (Wayland_JobThreadContext *)data;

    SDL_LockMutex(context->queue_lock);
    যাবত্ (!context->should_exit) {
        যদি (WAYLAND_wl_list_empty(&context->jobs)) {
            SDL_WaitCondition(context->cond, context->queue_lock);
        }

        Wayland_Job *job, *job_temp;
        wl_list_for_each_safe (job, job_temp, &context->jobs, link) {
            যদি (job->status == JOB_STATUS_WAITING) {
                job->status = JOB_STATUS_RUNNING;
            }

            // Don't block queue operations while dispatching the job.
            SDL_UnlockMutex(context->queue_lock);

            // If the job was cancelled, just remove it.
            যদি (job->status == JOB_STATUS_RUNNING) {
                job->callback(job->userdata);

                // Signal completion to the waiting thread.
                SDL_LockMutex(context->completion_lock);
                যদি (job->status == JOB_STATUS_SIGNAL_PENDING) {
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

    প্রত্যাগম 0;
}

বাহ্য Wayland_JobThreadContext *Wayland_CreateJobThread()
{
    Wayland_JobThreadContext *context = SDL_calloc(1, পরিমাণ(Wayland_JobThreadContext));
    যদি (!context) {
        প্রত্যাগম রিক্ত;
    }

    WAYLAND_wl_list_init(&context->jobs);

    context->queue_lock = SDL_CreateMutex();
    যদি (!context->queue_lock) {
        গচ্ছ cleanup;
    }

    context->completion_lock = SDL_CreateMutex();
    যদি (!context->completion_lock) {
        গচ্ছ cleanup;
    }

    context->cond = SDL_CreateCondition();
    যদি (!context->cond) {
        গচ্ছ cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_JobThreadFunc, "wl_job_thread", context);
    যদি (!context->thread) {
        গচ্ছ cleanup;
    }

    প্রত্যাগম context;

cleanup:
    যদি (context->queue_lock) {
        SDL_DestroyMutex(context->queue_lock);
    }

    যদি (context->completion_lock) {
        SDL_DestroyMutex(context->completion_lock);
    }

    যদি (context->cond) {
        SDL_DestroyCondition(context->cond);
    }

    SDL_free(context);

    প্রত্যাগম রিক্ত;
}

স্থির শূন্য job_thread_exit(শূন্য *data)
{
    Wayland_JobThreadContext *context = (Wayland_JobThreadContext *)data;
    context->should_exit = true;
}

বাহ্য শূন্য Wayland_DestroyJobThread(Wayland_JobThreadContext *context)
{
    যদি (!context) {
        প্রত্যাগম;
    }

    // Dispatch the exit job to unblock the thread and set the exit condition.
    Wayland_JobThreadAddJob(context, job_thread_exit, context, রিক্ত);

    // Wait for the thread to return; all jobs will be complete at this point.
    SDL_WaitThread(context->thread, রিক্ত);

    // Cleanup.
    SDL_DestroyCondition(context->cond);
    SDL_DestroyMutex(context->queue_lock);
    SDL_DestroyMutex(context->completion_lock);
    SDL_free(context);
}

bool Wayland_JobThreadAddJob(Wayland_JobThreadContext *context, Wayland_JobThreadCallback callback, শূন্য *userdata, Wayland_JobID *id)
{
    যদি (!callback) {
        প্রত্যাগম false;
    }

    যদি (context) {
        SDL_LockMutex(context->queue_lock);
        Wayland_Job *job = SDL_calloc(1, পরিমাণ(Wayland_Job));
        যদি (job) {
            job->id = context->id_counter++;
            যদি (id) {
                *id = job->id;
            }

            job->callback = callback;
            job->userdata = userdata;

            WAYLAND_wl_list_ঢোকাও(context->jobs.prev, &job->link);

            SDL_SignalCondition(context->cond);
            SDL_UnlockMutex(context->queue_lock);

            প্রত্যাগম true;
        }

        SDL_UnlockMutex(context->queue_lock);
        প্রত্যাগম false;
    } অন্যথা {
        // No thread? Just run the job.
        callback(userdata);
    }

    প্রত্যাগম true;
}

শূন্য Wayland_JobThreadCancelJob(Wayland_JobThreadContext *context, Wayland_JobID id)
{
    যদি (!context) {
        প্রত্যাগম;
    }

    SDL_LockMutex(context->queue_lock);

    Wayland_Job *job;
    wl_list_for_each (job, &context->jobs, link) {
        যদি (job->id == id) {
            SDL_LockMutex(context->completion_lock);
            যদি (job->status == JOB_STATUS_WAITING) {
                // In the queue, waiting to run; mark as cancelled.
                job->status = JOB_STATUS_CANCELED;
            } অন্যথা যদি (job->status == JOB_STATUS_RUNNING) {
                // The job is running; wait for completion.
                job->status = JOB_STATUS_SIGNAL_PENDING;
                SDL_WaitCondition(context->cond, context->completion_lock);
            }
            SDL_UnlockMutex(context->completion_lock);
            ভঙ্গ;
        }
    }

    SDL_UnlockMutex(context->queue_lock);
}

#endif // SDL_VIDEO_DRIVER_WAYLAND

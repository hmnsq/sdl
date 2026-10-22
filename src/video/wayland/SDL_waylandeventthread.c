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

প্রকারলেখ গণনা Wayland_JobStatus
{
    JOB_STATUS_WAITING = 0,
    JOB_STATUS_RUNNING,
    JOB_STATUS_SIGNAL_PENDING,
    JOB_STATUS_SIGNALED,
    JOB_STATUS_CANCELED
} Wayland_JobStatus;

প্রকারলেখ কাঠামো Wayland_Job
{
    Wayland_JobThreadCallback callback;
    শূন্য *userdata;
    Wayland_JobID id;
    Wayland_JobStatus status;

    কাঠামো wl_list link;
} Wayland_Job;

কাঠামো Wayland_JobThreadContext
{
    SDL_Thread *thread;
    SDL_Mutex *queue_lock;
    SDL_Mutex *completion_lock;
    SDL_Condition *cond;
    কাঠামো wl_list jobs;
    Wayland_JobID id_গণক;
    bool should_exit;
};

কাঠামো Wayland_EventThreadContext
{
    SDL_Video_তথ্য *wayland_তথ্য_2;
    SDL_Thread *thread;
    কাঠামো wl_event_queue *queue;
    SDL_Mutex *dispatch_lock;
    bool should_exit;
};

স্থির শূন্য handle_event_thread_exit(শূন্য *তথ্য, কাঠামো wl_callback *wl_callback, uint32_t callback_তথ্য)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)তথ্য;
    wl_callback_destroy(wl_callback);
    context->should_exit = true;
}

স্থির ধ্রুবক কাঠামো wl_callback_listener event_thread_exit_listener = {
    handle_event_thread_exit
};

স্থির পূর্ণসংখ্যা SDLCALL Wayland_EventThreadFunc(শূন্য *তথ্য)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)তথ্য;
    কাঠামো wl_display *display = context->wayland_তথ্য_2->display;
    ধ্রুবক পূর্ণসংখ্যা display_fd = WAYLAND_wl_display_get_fd(display);
    পূর্ণসংখ্যা ret;

    /* The lock must be held whenever dispatching to avoid a race condition when adding
     * or destroying objects using the queue.
     *
     * Any error other than EAGAIN is fatal and causes the thread to exit.
     */
    যখন (!context->should_exit) {
        যদি (WAYLAND_wl_display_prepare_read_queue(display, context->queue) == 0) {
            Sint64 timeoutNS = -1;

            ret = WAYLAND_wl_display_flush(display);

            যদি (ret < 0) {
                যদি (errno == EAGAIN) {
                    // If the flush failed with EAGAIN, don't block as not to inhibit other threads from reading events.
                    timeoutNS = SDL_MS_TO_NS(1);
                } অন্যথা {
                    WAYLAND_wl_display_cancel_read(display);
                    ফেরত -1;
                }
            }

            // Wait for a read/write operation to become possible.
            ret = SDL_IOReady(display_fd, SDL_IOR_READ, timeoutNS);

            যদি (ret <= 0) {
                WAYLAND_wl_display_cancel_read(display);
                যদি (ret < 0) {
                    ফেরত -1;
                }

                // Nothing to read, and woke to flush; try again.
                চালু;
            }

            ret = WAYLAND_wl_display_read_events(display);
            যদি (ret == -1) {
                ফেরত -1;
            }
        }

        SDL_LockMutex(context->dispatch_lock);
        ret = WAYLAND_wl_display_dispatch_queue_pending(display, context->queue);
        SDL_UnlockMutex(context->dispatch_lock);

        যদি (ret < 0) {
            ফেরত -1;
        }
    }

    ফেরত 0;
}

Wayland_EventThreadContext *Wayland_CreateEventThread(SDL_Video_তথ্য *তথ্য, ধ্রুবক অক্ষর *queue_name)
{
    Wayland_EventThreadContext *context = SDL_calloc(1, আকার(Wayland_EventThreadContext));
    যদি (!context) {
        ফেরত ফাঁকা;
    }

    context->wayland_তথ্য_2 = তথ্য;
    context->queue = Wayland_DisplayCreateQueue(তথ্য->display, queue_name);
    যদি (!context->queue) {
        যাও cleanup;
    }

    context->dispatch_lock = SDL_CreateMutex();
    যদি (!context->dispatch_lock) {
        যাও cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_EventThreadFunc, "wl_event_thread", context);
    যদি (!context->thread) {
        যাও cleanup;
    }

    ফেরত context;

cleanup:
    যদি (context->dispatch_lock) {
        SDL_DestroyMutex(context->dispatch_lock);
    }

    যদি (context->queue) {
        WAYLAND_wl_event_queue_destroy(context->queue);
    }

    SDL_free(context);
    ফেরত ফাঁকা;
}

শূন্য Wayland_DestroyEventThread(Wayland_EventThreadContext *context)
{
    যদি (context) {
        // Dispatch the exit event to unblock the thread and signal it to exit.
        কাঠামো wl_display *display = context->wayland_তথ্য_2->display;
        কাঠামো wl_proxy *display_wrapper = Wayland_CreateEventThreadProxyWrapper(context, display);

        SDL_LockMutex(context->dispatch_lock);
        কাঠামো wl_callback *cb = wl_display_sync((কাঠামো wl_display *)display_wrapper);
        wl_callback_add_listener(cb, &event_thread_exit_listener, context);
        SDL_UnlockMutex(context->dispatch_lock);

        WAYLAND_wl_proxy_wrapper_destroy(display_wrapper);

        পূর্ণসংখ্যা ret = WAYLAND_wl_display_flush(display);
        যখন (ret == -1 && errno == EAGAIN) {
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
        SDL_WaitThread(context->thread, ফাঁকা);

        WAYLAND_wl_event_queue_destroy(context->queue);
        SDL_DestroyMutex(context->dispatch_lock);
        SDL_free(context);
    }
}

শূন্য *Wayland_CreateEventThreadProxyWrapper(Wayland_EventThreadContext *context, শূন্য *obj)
{
    কাঠামো wl_proxy *wrapper = WAYLAND_wl_proxy_create_wrapper(obj);
    যদি (wrapper && context) {
        WAYLAND_wl_proxy_set_queue(wrapper, context->queue);
    }

    ফেরত wrapper;
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

স্থির পূর্ণসংখ্যা SDLCALL Wayland_JobThreadFunc(শূন্য *তথ্য)
{
    Wayland_JobThreadContext *context = (Wayland_JobThreadContext *)তথ্য;

    SDL_LockMutex(context->queue_lock);
    যখন (!context->should_exit) {
        যদি (WAYLAND_wl_list_empty(&context->jobs)) {
            SDL_WaitCondition(context->cond, context->queue_lock);
        }

        Wayland_Job *job, *job_অস্থায়ী;
        wl_list_for_each_safe (job, job_অস্থায়ী, &context->jobs, link) {
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

    ফেরত 0;
}

বাহ্যিক Wayland_JobThreadContext *Wayland_CreateJobThread()
{
    Wayland_JobThreadContext *context = SDL_calloc(1, আকার(Wayland_JobThreadContext));
    যদি (!context) {
        ফেরত ফাঁকা;
    }

    WAYLAND_wl_list_init(&context->jobs);

    context->queue_lock = SDL_CreateMutex();
    যদি (!context->queue_lock) {
        যাও cleanup;
    }

    context->completion_lock = SDL_CreateMutex();
    যদি (!context->completion_lock) {
        যাও cleanup;
    }

    context->cond = SDL_CreateCondition();
    যদি (!context->cond) {
        যাও cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_JobThreadFunc, "wl_job_thread", context);
    যদি (!context->thread) {
        যাও cleanup;
    }

    ফেরত context;

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

    ফেরত ফাঁকা;
}

স্থির শূন্য job_thread_exit(শূন্য *তথ্য)
{
    Wayland_JobThreadContext *context = (Wayland_JobThreadContext *)তথ্য;
    context->should_exit = true;
}

বাহ্যিক শূন্য Wayland_DestroyJobThread(Wayland_JobThreadContext *context)
{
    যদি (!context) {
        ফেরত;
    }

    // Dispatch the exit job to unblock the thread and set the exit condition.
    Wayland_JobThreadAddJob(context, job_thread_exit, context, ফাঁকা);

    // Wait for the thread to return; all jobs will be complete at this point.
    SDL_WaitThread(context->thread, ফাঁকা);

    // Cleanup.
    SDL_DestroyCondition(context->cond);
    SDL_DestroyMutex(context->queue_lock);
    SDL_DestroyMutex(context->completion_lock);
    SDL_free(context);
}

bool Wayland_JobThreadAddJob(Wayland_JobThreadContext *context, Wayland_JobThreadCallback callback, শূন্য *userdata, Wayland_JobID *id)
{
    যদি (!callback) {
        ফেরত false;
    }

    যদি (context) {
        SDL_LockMutex(context->queue_lock);
        Wayland_Job *job = SDL_calloc(1, আকার(Wayland_Job));
        যদি (job) {
            job->id = context->id_গণক++;
            যদি (id) {
                *id = job->id;
            }

            job->callback = callback;
            job->userdata = userdata;

            WAYLAND_wl_list_ঢোকাও(context->jobs.পূর্ব, &job->link);

            SDL_SignalCondition(context->cond);
            SDL_UnlockMutex(context->queue_lock);

            ফেরত true;
        }

        SDL_UnlockMutex(context->queue_lock);
        ফেরত false;
    } অন্যথা {
        // No thread? Just run the job.
        callback(userdata);
    }

    ফেরত true;
}

শূন্য Wayland_JobThreadCancelJob(Wayland_JobThreadContext *context, Wayland_JobID id)
{
    যদি (!context) {
        ফেরত;
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
            বিরতি;
        }
    }

    SDL_UnlockMutex(context->queue_lock);
}

#endif // SDL_VIDEO_DRIVER_WAYLAND

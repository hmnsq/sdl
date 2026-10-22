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
#अन्तर्भाव "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#अन्तर्भाव "../../core/unix/SDL_poll.h"
#अन्तर्भाव "SDL_waylandeventthread.h"
#अन्तर्भाव "SDL_waylandvideo.h"

#अन्तर्भाव <errno.h>

प्रकारनिर्देश गणना Wayland_JobStatus
{
    JOB_STATUS_WAITING = 0,
    JOB_STATUS_RUNNING,
    JOB_STATUS_SIGNAL_PENDING,
    JOB_STATUS_SIGNALED,
    JOB_STATUS_CANCELED
} Wayland_JobStatus;

प्रकारनिर्देश संरचना Wayland_Job
{
    Wayland_JobThreadCallback callback;
    शून्य *userdata;
    Wayland_JobID id;
    Wayland_JobStatus status;

    संरचना wl_list link;
} Wayland_Job;

संरचना Wayland_JobThreadContext
{
    SDL_Thread *thread;
    SDL_Mutex *queue_lock;
    SDL_Mutex *completion_lock;
    SDL_Condition *cond;
    संरचना wl_list jobs;
    Wayland_JobID id_counter;
    bool should_exit;
};

संरचना Wayland_EventThreadContext
{
    SDL_VideoData *wayland_data;
    SDL_Thread *thread;
    संरचना wl_event_queue *queue;
    SDL_Mutex *dispatch_lock;
    bool should_exit;
};

स्थिर शून्य handle_event_thread_exit(शून्य *data, संरचना wl_callback *wl_callback, uint32_t callback_data)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)data;
    wl_callback_destroy(wl_callback);
    context->should_exit = true;
}

स्थिर ध्रुव संरचना wl_callback_listener event_thread_exit_listener = {
    handle_event_thread_exit
};

स्थिर पूर्णाङ्क SDLCALL Wayland_EventThreadFunc(शून्य *data)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)data;
    संरचना wl_display *display = context->wayland_data->display;
    ध्रुव पूर्णाङ्क display_fd = WAYLAND_wl_display_get_fd(display);
    पूर्णाङ्क ret;

    /* The lock must be held whenever dispatching to avoid a race condition when adding
     * or destroying objects using the queue.
     *
     * Any error other than EAGAIN is fatal and causes the thread to exit.
     */
    यावत् (!context->should_exit) {
        यदि (WAYLAND_wl_display_prepare_read_queue(display, context->queue) == 0) {
            Sint64 timeoutNS = -1;

            ret = WAYLAND_wl_display_flush(display);

            यदि (ret < 0) {
                यदि (errno == EAGAIN) {
                    // If the flush failed with EAGAIN, don't block as not to inhibit other threads from reading events.
                    timeoutNS = SDL_MS_TO_NS(1);
                } अन्यथा {
                    WAYLAND_wl_display_cancel_read(display);
                    प्रत्यागम -1;
                }
            }

            // Wait for a read/write operation to become possible.
            ret = SDL_IOReady(display_fd, SDL_IOR_READ, timeoutNS);

            यदि (ret <= 0) {
                WAYLAND_wl_display_cancel_read(display);
                यदि (ret < 0) {
                    प्रत्यागम -1;
                }

                // Nothing to read, and woke to flush; try again.
                अनुवर्त;
            }

            ret = WAYLAND_wl_display_read_events(display);
            यदि (ret == -1) {
                प्रत्यागम -1;
            }
        }

        SDL_LockMutex(context->dispatch_lock);
        ret = WAYLAND_wl_display_dispatch_queue_pending(display, context->queue);
        SDL_UnlockMutex(context->dispatch_lock);

        यदि (ret < 0) {
            प्रत्यागम -1;
        }
    }

    प्रत्यागम 0;
}

Wayland_EventThreadContext *Wayland_CreateEventThread(SDL_VideoData *data, ध्रुव वर्ण *queue_name)
{
    Wayland_EventThreadContext *context = SDL_calloc(1, परिमाण(Wayland_EventThreadContext));
    यदि (!context) {
        प्रत्यागम रिक्त;
    }

    context->wayland_data = data;
    context->queue = Wayland_DisplayCreateQueue(data->display, queue_name);
    यदि (!context->queue) {
        गच्छ cleanup;
    }

    context->dispatch_lock = SDL_CreateMutex();
    यदि (!context->dispatch_lock) {
        गच्छ cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_EventThreadFunc, "wl_event_thread", context);
    यदि (!context->thread) {
        गच्छ cleanup;
    }

    प्रत्यागम context;

cleanup:
    यदि (context->dispatch_lock) {
        SDL_DestroyMutex(context->dispatch_lock);
    }

    यदि (context->queue) {
        WAYLAND_wl_event_queue_destroy(context->queue);
    }

    SDL_free(context);
    प्रत्यागम रिक्त;
}

शून्य Wayland_DestroyEventThread(Wayland_EventThreadContext *context)
{
    यदि (context) {
        // Dispatch the exit event to unblock the thread and signal it to exit.
        संरचना wl_display *display = context->wayland_data->display;
        संरचना wl_proxy *display_wrapper = Wayland_CreateEventThreadProxyWrapper(context, display);

        SDL_LockMutex(context->dispatch_lock);
        संरचना wl_callback *cb = wl_display_sync((संरचना wl_display *)display_wrapper);
        wl_callback_add_listener(cb, &event_thread_exit_listener, context);
        SDL_UnlockMutex(context->dispatch_lock);

        WAYLAND_wl_proxy_wrapper_destroy(display_wrapper);

        पूर्णाङ्क ret = WAYLAND_wl_display_flush(display);
        यावत् (ret == -1 && errno == EAGAIN) {
            // Shutting down the thread requires a successful flush.
            ret = SDL_IOReady(WAYLAND_wl_display_get_fd(display), SDL_IOR_WRITE, -1);
            यदि (ret >= 0) {
                ret = WAYLAND_wl_display_flush(display);
            }
        }

        // Avoid a warning if the flush failed due to a broken connection.
        यदि (ret < 0) {
            wl_callback_destroy(cb);
        }

        // Wait for the thread to return; it will exit automatically on a broken connection.
        SDL_WaitThread(context->thread, रिक्त);

        WAYLAND_wl_event_queue_destroy(context->queue);
        SDL_DestroyMutex(context->dispatch_lock);
        SDL_free(context);
    }
}

शून्य *Wayland_CreateEventThreadProxyWrapper(Wayland_EventThreadContext *context, शून्य *obj)
{
    संरचना wl_proxy *wrapper = WAYLAND_wl_proxy_create_wrapper(obj);
    यदि (wrapper && context) {
        WAYLAND_wl_proxy_set_queue(wrapper, context->queue);
    }

    प्रत्यागम wrapper;
}

शून्य Wayland_LockEventThread(Wayland_EventThreadContext *context)
{
    यदि (context) {
        SDL_LockMutex(context->dispatch_lock);
    }
}

शून्य Wayland_UnlockEventThread(Wayland_EventThreadContext *context)
{
    यदि (context) {
        SDL_UnlockMutex(context->dispatch_lock);
    }
}

स्थिर पूर्णाङ्क SDLCALL Wayland_JobThreadFunc(शून्य *data)
{
    Wayland_JobThreadContext *context = (Wayland_JobThreadContext *)data;

    SDL_LockMutex(context->queue_lock);
    यावत् (!context->should_exit) {
        यदि (WAYLAND_wl_list_empty(&context->jobs)) {
            SDL_WaitCondition(context->cond, context->queue_lock);
        }

        Wayland_Job *job, *job_temp;
        wl_list_for_each_safe (job, job_temp, &context->jobs, link) {
            यदि (job->status == JOB_STATUS_WAITING) {
                job->status = JOB_STATUS_RUNNING;
            }

            // Don't block queue operations while dispatching the job.
            SDL_UnlockMutex(context->queue_lock);

            // If the job was cancelled, just remove it.
            यदि (job->status == JOB_STATUS_RUNNING) {
                job->callback(job->userdata);

                // Signal completion to the waiting thread.
                SDL_LockMutex(context->completion_lock);
                यदि (job->status == JOB_STATUS_SIGNAL_PENDING) {
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

    प्रत्यागम 0;
}

बाह्य Wayland_JobThreadContext *Wayland_CreateJobThread()
{
    Wayland_JobThreadContext *context = SDL_calloc(1, परिमाण(Wayland_JobThreadContext));
    यदि (!context) {
        प्रत्यागम रिक्त;
    }

    WAYLAND_wl_list_init(&context->jobs);

    context->queue_lock = SDL_CreateMutex();
    यदि (!context->queue_lock) {
        गच्छ cleanup;
    }

    context->completion_lock = SDL_CreateMutex();
    यदि (!context->completion_lock) {
        गच्छ cleanup;
    }

    context->cond = SDL_CreateCondition();
    यदि (!context->cond) {
        गच्छ cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_JobThreadFunc, "wl_job_thread", context);
    यदि (!context->thread) {
        गच्छ cleanup;
    }

    प्रत्यागम context;

cleanup:
    यदि (context->queue_lock) {
        SDL_DestroyMutex(context->queue_lock);
    }

    यदि (context->completion_lock) {
        SDL_DestroyMutex(context->completion_lock);
    }

    यदि (context->cond) {
        SDL_DestroyCondition(context->cond);
    }

    SDL_free(context);

    प्रत्यागम रिक्त;
}

स्थिर शून्य job_thread_exit(शून्य *data)
{
    Wayland_JobThreadContext *context = (Wayland_JobThreadContext *)data;
    context->should_exit = true;
}

बाह्य शून्य Wayland_DestroyJobThread(Wayland_JobThreadContext *context)
{
    यदि (!context) {
        प्रत्यागम;
    }

    // Dispatch the exit job to unblock the thread and set the exit condition.
    Wayland_JobThreadAddJob(context, job_thread_exit, context, रिक्त);

    // Wait for the thread to return; all jobs will be complete at this point.
    SDL_WaitThread(context->thread, रिक्त);

    // Cleanup.
    SDL_DestroyCondition(context->cond);
    SDL_DestroyMutex(context->queue_lock);
    SDL_DestroyMutex(context->completion_lock);
    SDL_free(context);
}

bool Wayland_JobThreadAddJob(Wayland_JobThreadContext *context, Wayland_JobThreadCallback callback, शून्य *userdata, Wayland_JobID *id)
{
    यदि (!callback) {
        प्रत्यागम false;
    }

    यदि (context) {
        SDL_LockMutex(context->queue_lock);
        Wayland_Job *job = SDL_calloc(1, परिमाण(Wayland_Job));
        यदि (job) {
            job->id = context->id_counter++;
            यदि (id) {
                *id = job->id;
            }

            job->callback = callback;
            job->userdata = userdata;

            WAYLAND_wl_list_घाला(context->jobs.prev, &job->link);

            SDL_SignalCondition(context->cond);
            SDL_UnlockMutex(context->queue_lock);

            प्रत्यागम true;
        }

        SDL_UnlockMutex(context->queue_lock);
        प्रत्यागम false;
    } अन्यथा {
        // No thread? Just run the job.
        callback(userdata);
    }

    प्रत्यागम true;
}

शून्य Wayland_JobThreadCancelJob(Wayland_JobThreadContext *context, Wayland_JobID id)
{
    यदि (!context) {
        प्रत्यागम;
    }

    SDL_LockMutex(context->queue_lock);

    Wayland_Job *job;
    wl_list_for_each (job, &context->jobs, link) {
        यदि (job->id == id) {
            SDL_LockMutex(context->completion_lock);
            यदि (job->status == JOB_STATUS_WAITING) {
                // In the queue, waiting to run; mark as cancelled.
                job->status = JOB_STATUS_CANCELED;
            } अन्यथा यदि (job->status == JOB_STATUS_RUNNING) {
                // The job is running; wait for completion.
                job->status = JOB_STATUS_SIGNAL_PENDING;
                SDL_WaitCondition(context->cond, context->completion_lock);
            }
            SDL_UnlockMutex(context->completion_lock);
            भङ्ग;
        }
    }

    SDL_UnlockMutex(context->queue_lock);
}

#endif // SDL_VIDEO_DRIVER_WAYLAND

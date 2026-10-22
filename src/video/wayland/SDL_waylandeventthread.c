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
#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_WAYLAND

#समावेश "../../core/unix/SDL_poll.h"
#समावेश "SDL_waylandeventthread.h"
#समावेश "SDL_waylandvideo.h"

#समावेश <errno.h>

प्रकार क्रमागत Wayland_JobStatus
{
    JOB_STATUS_WAITING = 0,
    JOB_STATUS_RUNNING,
    JOB_STATUS_SIGNAL_PENDING,
    JOB_STATUS_SIGNALED,
    JOB_STATUS_CANCELED
} Wayland_JobStatus;

प्रकार काष्ठा Wayland_Job
{
    Wayland_JobThreadCallback callback;
    व्योम *userdata;
    Wayland_JobID id;
    Wayland_JobStatus status;

    काष्ठा wl_list link;
} Wayland_Job;

काष्ठा Wayland_JobThreadContext
{
    SDL_Thread *thread;
    SDL_Mutex *queue_lock;
    SDL_Mutex *completion_lock;
    SDL_Condition *cond;
    काष्ठा wl_list jobs;
    Wayland_JobID id_गणक;
    bool should_exit;
};

काष्ठा Wayland_EventThreadContext
{
    SDL_Video_तथ्य *wayland_तथ्य_2;
    SDL_Thread *thread;
    काष्ठा wl_event_queue *queue;
    SDL_Mutex *dispatch_lock;
    bool should_exit;
};

अटल व्योम handle_event_thread_exit(व्योम *तथ्य, काष्ठा wl_callback *wl_callback, uint32_t callback_तथ्य)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)तथ्य;
    wl_callback_destroy(wl_callback);
    context->should_exit = true;
}

अटल स्थिर काष्ठा wl_callback_listener event_thread_exit_listener = {
    handle_event_thread_exit
};

अटल पूर्णांक SDLCALL Wayland_EventThreadFunc(व्योम *तथ्य)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)तथ्य;
    काष्ठा wl_display *display = context->wayland_तथ्य_2->display;
    स्थिर पूर्णांक display_fd = WAYLAND_wl_display_get_fd(display);
    पूर्णांक ret;

    /* The lock must be held whenever dispatching to avoid a race condition when adding
     * or destroying objects using the queue.
     *
     * Any error other than EAGAIN is fatal and causes the thread to exit.
     */
    जबतक (!context->should_exit) {
        अगर (WAYLAND_wl_display_prepare_read_queue(display, context->queue) == 0) {
            Sint64 timeoutNS = -1;

            ret = WAYLAND_wl_display_flush(display);

            अगर (ret < 0) {
                अगर (त्रुटि_सं == EAGAIN) {
                    // If the flush failed with EAGAIN, don't block as not to inhibit other threads from reading events.
                    timeoutNS = SDL_MS_TO_NS(1);
                } अन्यथा {
                    WAYLAND_wl_display_cancel_read(display);
                    वापस -1;
                }
            }

            // Wait for a read/write operation to become possible.
            ret = SDL_IOReady(display_fd, SDL_IOR_READ, timeoutNS);

            अगर (ret <= 0) {
                WAYLAND_wl_display_cancel_read(display);
                अगर (ret < 0) {
                    वापस -1;
                }

                // Nothing to read, and woke to flush; try again.
                जारी;
            }

            ret = WAYLAND_wl_display_read_events(display);
            अगर (ret == -1) {
                वापस -1;
            }
        }

        SDL_LockMutex(context->dispatch_lock);
        ret = WAYLAND_wl_display_dispatch_queue_pending(display, context->queue);
        SDL_UnlockMutex(context->dispatch_lock);

        अगर (ret < 0) {
            वापस -1;
        }
    }

    वापस 0;
}

Wayland_EventThreadContext *Wayland_CreateEventThread(SDL_Video_तथ्य *तथ्य, स्थिर अक्षर *queue_name)
{
    Wayland_EventThreadContext *context = SDL_calloc(1, माप(Wayland_EventThreadContext));
    अगर (!context) {
        वापस शून्य;
    }

    context->wayland_तथ्य_2 = तथ्य;
    context->queue = Wayland_DisplayCreateQueue(तथ्य->display, queue_name);
    अगर (!context->queue) {
        जाओ cleanup;
    }

    context->dispatch_lock = SDL_CreateMutex();
    अगर (!context->dispatch_lock) {
        जाओ cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_EventThreadFunc, "wl_event_thread", context);
    अगर (!context->thread) {
        जाओ cleanup;
    }

    वापस context;

cleanup:
    अगर (context->dispatch_lock) {
        SDL_DestroyMutex(context->dispatch_lock);
    }

    अगर (context->queue) {
        WAYLAND_wl_event_queue_destroy(context->queue);
    }

    SDL_free(context);
    वापस शून्य;
}

व्योम Wayland_DestroyEventThread(Wayland_EventThreadContext *context)
{
    अगर (context) {
        // Dispatch the exit event to unblock the thread and signal it to exit.
        काष्ठा wl_display *display = context->wayland_तथ्य_2->display;
        काष्ठा wl_proxy *display_wrapper = Wayland_CreateEventThreadProxyWrapper(context, display);

        SDL_LockMutex(context->dispatch_lock);
        काष्ठा wl_callback *cb = wl_display_sync((काष्ठा wl_display *)display_wrapper);
        wl_callback_add_listener(cb, &event_thread_exit_listener, context);
        SDL_UnlockMutex(context->dispatch_lock);

        WAYLAND_wl_proxy_wrapper_destroy(display_wrapper);

        पूर्णांक ret = WAYLAND_wl_display_flush(display);
        जबतक (ret == -1 && त्रुटि_सं == EAGAIN) {
            // Shutting down the thread requires a successful flush.
            ret = SDL_IOReady(WAYLAND_wl_display_get_fd(display), SDL_IOR_WRITE, -1);
            अगर (ret >= 0) {
                ret = WAYLAND_wl_display_flush(display);
            }
        }

        // Avoid a warning if the flush failed due to a broken connection.
        अगर (ret < 0) {
            wl_callback_destroy(cb);
        }

        // Wait for the thread to return; it will exit automatically on a broken connection.
        SDL_WaitThread(context->thread, शून्य);

        WAYLAND_wl_event_queue_destroy(context->queue);
        SDL_DestroyMutex(context->dispatch_lock);
        SDL_free(context);
    }
}

व्योम *Wayland_CreateEventThreadProxyWrapper(Wayland_EventThreadContext *context, व्योम *obj)
{
    काष्ठा wl_proxy *wrapper = WAYLAND_wl_proxy_create_wrapper(obj);
    अगर (wrapper && context) {
        WAYLAND_wl_proxy_set_queue(wrapper, context->queue);
    }

    वापस wrapper;
}

व्योम Wayland_LockEventThread(Wayland_EventThreadContext *context)
{
    अगर (context) {
        SDL_LockMutex(context->dispatch_lock);
    }
}

व्योम Wayland_UnlockEventThread(Wayland_EventThreadContext *context)
{
    अगर (context) {
        SDL_UnlockMutex(context->dispatch_lock);
    }
}

अटल पूर्णांक SDLCALL Wayland_JobThreadFunc(व्योम *तथ्य)
{
    Wayland_JobThreadContext *context = (Wayland_JobThreadContext *)तथ्य;

    SDL_LockMutex(context->queue_lock);
    जबतक (!context->should_exit) {
        अगर (WAYLAND_wl_list_empty(&context->jobs)) {
            SDL_WaitCondition(context->cond, context->queue_lock);
        }

        Wayland_Job *job, *job_अस्थायी;
        wl_list_for_each_safe (job, job_अस्थायी, &context->jobs, link) {
            अगर (job->status == JOB_STATUS_WAITING) {
                job->status = JOB_STATUS_RUNNING;
            }

            // Don't block queue operations while dispatching the job.
            SDL_UnlockMutex(context->queue_lock);

            // If the job was cancelled, just remove it.
            अगर (job->status == JOB_STATUS_RUNNING) {
                job->callback(job->userdata);

                // Signal completion to the waiting thread.
                SDL_LockMutex(context->completion_lock);
                अगर (job->status == JOB_STATUS_SIGNAL_PENDING) {
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

    वापस 0;
}

बाह्य Wayland_JobThreadContext *Wayland_CreateJobThread()
{
    Wayland_JobThreadContext *context = SDL_calloc(1, माप(Wayland_JobThreadContext));
    अगर (!context) {
        वापस शून्य;
    }

    WAYLAND_wl_list_init(&context->jobs);

    context->queue_lock = SDL_CreateMutex();
    अगर (!context->queue_lock) {
        जाओ cleanup;
    }

    context->completion_lock = SDL_CreateMutex();
    अगर (!context->completion_lock) {
        जाओ cleanup;
    }

    context->cond = SDL_CreateCondition();
    अगर (!context->cond) {
        जाओ cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_JobThreadFunc, "wl_job_thread", context);
    अगर (!context->thread) {
        जाओ cleanup;
    }

    वापस context;

cleanup:
    अगर (context->queue_lock) {
        SDL_DestroyMutex(context->queue_lock);
    }

    अगर (context->completion_lock) {
        SDL_DestroyMutex(context->completion_lock);
    }

    अगर (context->cond) {
        SDL_DestroyCondition(context->cond);
    }

    SDL_free(context);

    वापस शून्य;
}

अटल व्योम job_thread_exit(व्योम *तथ्य)
{
    Wayland_JobThreadContext *context = (Wayland_JobThreadContext *)तथ्य;
    context->should_exit = true;
}

बाह्य व्योम Wayland_DestroyJobThread(Wayland_JobThreadContext *context)
{
    अगर (!context) {
        वापस;
    }

    // Dispatch the exit job to unblock the thread and set the exit condition.
    Wayland_JobThreadAddJob(context, job_thread_exit, context, शून्य);

    // Wait for the thread to return; all jobs will be complete at this point.
    SDL_WaitThread(context->thread, शून्य);

    // Cleanup.
    SDL_DestroyCondition(context->cond);
    SDL_DestroyMutex(context->queue_lock);
    SDL_DestroyMutex(context->completion_lock);
    SDL_free(context);
}

bool Wayland_JobThreadAddJob(Wayland_JobThreadContext *context, Wayland_JobThreadCallback callback, व्योम *userdata, Wayland_JobID *id)
{
    अगर (!callback) {
        वापस false;
    }

    अगर (context) {
        SDL_LockMutex(context->queue_lock);
        Wayland_Job *job = SDL_calloc(1, माप(Wayland_Job));
        अगर (job) {
            job->id = context->id_गणक++;
            अगर (id) {
                *id = job->id;
            }

            job->callback = callback;
            job->userdata = userdata;

            WAYLAND_wl_list_जोड़ो(context->jobs.पूर्व, &job->link);

            SDL_SignalCondition(context->cond);
            SDL_UnlockMutex(context->queue_lock);

            वापस true;
        }

        SDL_UnlockMutex(context->queue_lock);
        वापस false;
    } अन्यथा {
        // No thread? Just run the job.
        callback(userdata);
    }

    वापस true;
}

व्योम Wayland_JobThreadCancelJob(Wayland_JobThreadContext *context, Wayland_JobID id)
{
    अगर (!context) {
        वापस;
    }

    SDL_LockMutex(context->queue_lock);

    Wayland_Job *job;
    wl_list_for_each (job, &context->jobs, link) {
        अगर (job->id == id) {
            SDL_LockMutex(context->completion_lock);
            अगर (job->status == JOB_STATUS_WAITING) {
                // In the queue, waiting to run; mark as cancelled.
                job->status = JOB_STATUS_CANCELED;
            } अन्यथा अगर (job->status == JOB_STATUS_RUNNING) {
                // The job is running; wait for completion.
                job->status = JOB_STATUS_SIGNAL_PENDING;
                SDL_WaitCondition(context->cond, context->completion_lock);
            }
            SDL_UnlockMutex(context->completion_lock);
            अवरोध;
        }
    }

    SDL_UnlockMutex(context->queue_lock);
}

#पूर्ण_अगर // SDL_VIDEO_DRIVER_WAYLAND

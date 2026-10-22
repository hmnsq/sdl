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
#અન્તર્ભાવ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#અન્તર્ભાવ "../../core/unix/SDL_poll.h"
#અન્તર્ભાવ "SDL_waylandeventthread.h"
#અન્તર્ભાવ "SDL_waylandvideo.h"

#અન્તર્ભાવ <errno.h>

પ્રકારવ્યાખ્યા ગણના Wayland_JobStatus
{
    JOB_STATUS_WAITING = 0,
    JOB_STATUS_RUNNING,
    JOB_STATUS_SIGNAL_PENDING,
    JOB_STATUS_SIGNALED,
    JOB_STATUS_CANCELED
} Wayland_JobStatus;

પ્રકારવ્યાખ્યા સંરચના Wayland_Job
{
    Wayland_JobThreadCallback callback;
    શૂન્ય *userdata;
    Wayland_JobID id;
    Wayland_JobStatus status;

    સંરચના wl_list link;
} Wayland_Job;

સંરચના Wayland_JobThreadContext
{
    SDL_Thread *thread;
    SDL_Mutex *queue_lock;
    SDL_Mutex *completion_lock;
    SDL_Condition *cond;
    સંરચના wl_list jobs;
    Wayland_JobID id_counter;
    bool should_exit;
};

સંરચના Wayland_EventThreadContext
{
    SDL_VideoData *wayland_data;
    SDL_Thread *thread;
    સંરચના wl_event_queue *queue;
    SDL_Mutex *dispatch_lock;
    bool should_exit;
};

સ્થિર શૂન્ય handle_event_thread_exit(શૂન્ય *data, સંરચના wl_callback *wl_callback, uint32_t callback_data)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)data;
    wl_callback_destroy(wl_callback);
    context->should_exit = true;
}

સ્થિર અચલ સંરચના wl_callback_listener event_thread_exit_listener = {
    handle_event_thread_exit
};

સ્થિર પૂર્ણાંક SDLCALL Wayland_EventThreadFunc(શૂન્ય *data)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)data;
    સંરચના wl_display *display = context->wayland_data->display;
    અચલ પૂર્ણાંક display_fd = WAYLAND_wl_display_get_fd(display);
    પૂર્ણાંક ret;

    /* The lock must be held whenever dispatching to avoid a race condition when adding
     * or destroying objects using the queue.
     *
     * Any error other than EAGAIN is fatal and causes the thread to exit.
     */
    જ્યારે (!context->should_exit) {
        જો (WAYLAND_wl_display_prepare_read_queue(display, context->queue) == 0) {
            Sint64 timeoutNS = -1;

            ret = WAYLAND_wl_display_flush(display);

            જો (ret < 0) {
                જો (errno == EAGAIN) {
                    // If the flush failed with EAGAIN, don't block as not to inhibit other threads from reading events.
                    timeoutNS = SDL_MS_TO_NS(1);
                } નહીંતર {
                    WAYLAND_wl_display_cancel_read(display);
                    પાછા -1;
                }
            }

            // Wait for a read/write operation to become possible.
            ret = SDL_IOReady(display_fd, SDL_IOR_READ, timeoutNS);

            જો (ret <= 0) {
                WAYLAND_wl_display_cancel_read(display);
                જો (ret < 0) {
                    પાછા -1;
                }

                // Nothing to read, and woke to flush; try again.
                ચાલુ;
            }

            ret = WAYLAND_wl_display_read_events(display);
            જો (ret == -1) {
                પાછા -1;
            }
        }

        SDL_LockMutex(context->dispatch_lock);
        ret = WAYLAND_wl_display_dispatch_queue_pending(display, context->queue);
        SDL_UnlockMutex(context->dispatch_lock);

        જો (ret < 0) {
            પાછા -1;
        }
    }

    પાછા 0;
}

Wayland_EventThreadContext *Wayland_CreateEventThread(SDL_VideoData *data, અચલ અક્ષર *queue_name)
{
    Wayland_EventThreadContext *context = SDL_calloc(1, કદ(Wayland_EventThreadContext));
    જો (!context) {
        પાછા ખાલી;
    }

    context->wayland_data = data;
    context->queue = Wayland_DisplayCreateQueue(data->display, queue_name);
    જો (!context->queue) {
        જાઓ cleanup;
    }

    context->dispatch_lock = SDL_CreateMutex();
    જો (!context->dispatch_lock) {
        જાઓ cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_EventThreadFunc, "wl_event_thread", context);
    જો (!context->thread) {
        જાઓ cleanup;
    }

    પાછા context;

cleanup:
    જો (context->dispatch_lock) {
        SDL_DestroyMutex(context->dispatch_lock);
    }

    જો (context->queue) {
        WAYLAND_wl_event_queue_destroy(context->queue);
    }

    SDL_free(context);
    પાછા ખાલી;
}

શૂન્ય Wayland_DestroyEventThread(Wayland_EventThreadContext *context)
{
    જો (context) {
        // Dispatch the exit event to unblock the thread and signal it to exit.
        સંરચના wl_display *display = context->wayland_data->display;
        સંરચના wl_proxy *display_wrapper = Wayland_CreateEventThreadProxyWrapper(context, display);

        SDL_LockMutex(context->dispatch_lock);
        સંરચના wl_callback *cb = wl_display_sync((સંરચના wl_display *)display_wrapper);
        wl_callback_add_listener(cb, &event_thread_exit_listener, context);
        SDL_UnlockMutex(context->dispatch_lock);

        WAYLAND_wl_proxy_wrapper_destroy(display_wrapper);

        પૂર્ણાંક ret = WAYLAND_wl_display_flush(display);
        જ્યારે (ret == -1 && errno == EAGAIN) {
            // Shutting down the thread requires a successful flush.
            ret = SDL_IOReady(WAYLAND_wl_display_get_fd(display), SDL_IOR_WRITE, -1);
            જો (ret >= 0) {
                ret = WAYLAND_wl_display_flush(display);
            }
        }

        // Avoid a warning if the flush failed due to a broken connection.
        જો (ret < 0) {
            wl_callback_destroy(cb);
        }

        // Wait for the thread to return; it will exit automatically on a broken connection.
        SDL_WaitThread(context->thread, ખાલી);

        WAYLAND_wl_event_queue_destroy(context->queue);
        SDL_DestroyMutex(context->dispatch_lock);
        SDL_free(context);
    }
}

શૂન્ય *Wayland_CreateEventThreadProxyWrapper(Wayland_EventThreadContext *context, શૂન્ય *obj)
{
    સંરચના wl_proxy *wrapper = WAYLAND_wl_proxy_create_wrapper(obj);
    જો (wrapper && context) {
        WAYLAND_wl_proxy_set_queue(wrapper, context->queue);
    }

    પાછા wrapper;
}

શૂન્ય Wayland_LockEventThread(Wayland_EventThreadContext *context)
{
    જો (context) {
        SDL_LockMutex(context->dispatch_lock);
    }
}

શૂન્ય Wayland_UnlockEventThread(Wayland_EventThreadContext *context)
{
    જો (context) {
        SDL_UnlockMutex(context->dispatch_lock);
    }
}

સ્થિર પૂર્ણાંક SDLCALL Wayland_JobThreadFunc(શૂન્ય *data)
{
    Wayland_JobThreadContext *context = (Wayland_JobThreadContext *)data;

    SDL_LockMutex(context->queue_lock);
    જ્યારે (!context->should_exit) {
        જો (WAYLAND_wl_list_empty(&context->jobs)) {
            SDL_WaitCondition(context->cond, context->queue_lock);
        }

        Wayland_Job *job, *job_temp;
        wl_list_for_each_safe (job, job_temp, &context->jobs, link) {
            જો (job->status == JOB_STATUS_WAITING) {
                job->status = JOB_STATUS_RUNNING;
            }

            // Don't block queue operations while dispatching the job.
            SDL_UnlockMutex(context->queue_lock);

            // If the job was cancelled, just remove it.
            જો (job->status == JOB_STATUS_RUNNING) {
                job->callback(job->userdata);

                // Signal completion to the waiting thread.
                SDL_LockMutex(context->completion_lock);
                જો (job->status == JOB_STATUS_SIGNAL_PENDING) {
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

    પાછા 0;
}

બાહ્ય Wayland_JobThreadContext *Wayland_CreateJobThread()
{
    Wayland_JobThreadContext *context = SDL_calloc(1, કદ(Wayland_JobThreadContext));
    જો (!context) {
        પાછા ખાલી;
    }

    WAYLAND_wl_list_init(&context->jobs);

    context->queue_lock = SDL_CreateMutex();
    જો (!context->queue_lock) {
        જાઓ cleanup;
    }

    context->completion_lock = SDL_CreateMutex();
    જો (!context->completion_lock) {
        જાઓ cleanup;
    }

    context->cond = SDL_CreateCondition();
    જો (!context->cond) {
        જાઓ cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_JobThreadFunc, "wl_job_thread", context);
    જો (!context->thread) {
        જાઓ cleanup;
    }

    પાછા context;

cleanup:
    જો (context->queue_lock) {
        SDL_DestroyMutex(context->queue_lock);
    }

    જો (context->completion_lock) {
        SDL_DestroyMutex(context->completion_lock);
    }

    જો (context->cond) {
        SDL_DestroyCondition(context->cond);
    }

    SDL_free(context);

    પાછા ખાલી;
}

સ્થિર શૂન્ય job_thread_exit(શૂન્ય *data)
{
    Wayland_JobThreadContext *context = (Wayland_JobThreadContext *)data;
    context->should_exit = true;
}

બાહ્ય શૂન્ય Wayland_DestroyJobThread(Wayland_JobThreadContext *context)
{
    જો (!context) {
        પાછા;
    }

    // Dispatch the exit job to unblock the thread and set the exit condition.
    Wayland_JobThreadAddJob(context, job_thread_exit, context, ખાલી);

    // Wait for the thread to return; all jobs will be complete at this point.
    SDL_WaitThread(context->thread, ખાલી);

    // Cleanup.
    SDL_DestroyCondition(context->cond);
    SDL_DestroyMutex(context->queue_lock);
    SDL_DestroyMutex(context->completion_lock);
    SDL_free(context);
}

bool Wayland_JobThreadAddJob(Wayland_JobThreadContext *context, Wayland_JobThreadCallback callback, શૂન્ય *userdata, Wayland_JobID *id)
{
    જો (!callback) {
        પાછા false;
    }

    જો (context) {
        SDL_LockMutex(context->queue_lock);
        Wayland_Job *job = SDL_calloc(1, કદ(Wayland_Job));
        જો (job) {
            job->id = context->id_counter++;
            જો (id) {
                *id = job->id;
            }

            job->callback = callback;
            job->userdata = userdata;

            WAYLAND_wl_list_ઉમેરો(context->jobs.prev, &job->link);

            SDL_SignalCondition(context->cond);
            SDL_UnlockMutex(context->queue_lock);

            પાછા true;
        }

        SDL_UnlockMutex(context->queue_lock);
        પાછા false;
    } નહીંતર {
        // No thread? Just run the job.
        callback(userdata);
    }

    પાછા true;
}

શૂન્ય Wayland_JobThreadCancelJob(Wayland_JobThreadContext *context, Wayland_JobID id)
{
    જો (!context) {
        પાછા;
    }

    SDL_LockMutex(context->queue_lock);

    Wayland_Job *job;
    wl_list_for_each (job, &context->jobs, link) {
        જો (job->id == id) {
            SDL_LockMutex(context->completion_lock);
            જો (job->status == JOB_STATUS_WAITING) {
                // In the queue, waiting to run; mark as cancelled.
                job->status = JOB_STATUS_CANCELED;
            } નહીંતર જો (job->status == JOB_STATUS_RUNNING) {
                // The job is running; wait for completion.
                job->status = JOB_STATUS_SIGNAL_PENDING;
                SDL_WaitCondition(context->cond, context->completion_lock);
            }
            SDL_UnlockMutex(context->completion_lock);
            તોડો;
        }
    }

    SDL_UnlockMutex(context->queue_lock);
}

#endif // SDL_VIDEO_DRIVER_WAYLAND

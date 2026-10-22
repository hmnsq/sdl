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
#അന്തര്ഭാവ "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#അന്തര്ഭാവ "../../core/unix/SDL_poll.h"
#അന്തര്ഭാവ "SDL_waylandeventthread.h"
#അന്തര്ഭാവ "SDL_waylandvideo.h"

#അന്തര്ഭാവ <errno.h>

തരനിർവചനം എണ്ണൽ Wayland_JobStatus
{
    JOB_STATUS_WAITING = 0,
    JOB_STATUS_RUNNING,
    JOB_STATUS_SIGNAL_PENDING,
    JOB_STATUS_SIGNALED,
    JOB_STATUS_CANCELED
} Wayland_JobStatus;

തരനിർവചനം ഘടന Wayland_Job
{
    Wayland_JobThreadCallback callback;
    ശൂന്യം *userdata;
    Wayland_JobID id;
    Wayland_JobStatus status;

    ഘടന wl_list link;
} Wayland_Job;

ഘടന Wayland_JobThreadContext
{
    SDL_Thread *thread;
    SDL_Mutex *queue_lock;
    SDL_Mutex *completion_lock;
    SDL_Condition *cond;
    ഘടന wl_list jobs;
    Wayland_JobID id_counter;
    bool should_exit;
};

ഘടന Wayland_EventThreadContext
{
    SDL_VideoData *wayland_data;
    SDL_Thread *thread;
    ഘടന wl_event_queue *queue;
    SDL_Mutex *dispatch_lock;
    bool should_exit;
};

സ്ഥിതം ശൂന്യം handle_event_thread_exit(ശൂന്യം *data, ഘടന wl_callback *wl_callback, uint32_t callback_data)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)data;
    wl_callback_destroy(wl_callback);
    context->should_exit = true;
}

സ്ഥിതം സ്ഥിരം ഘടന wl_callback_listener event_thread_exit_listener = {
    handle_event_thread_exit
};

സ്ഥിതം പൂർണ്ണസംഖ്യ SDLCALL Wayland_EventThreadFunc(ശൂന്യം *data)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)data;
    ഘടന wl_display *display = context->wayland_data->display;
    സ്ഥിരം പൂർണ്ണസംഖ്യ display_fd = WAYLAND_wl_display_get_fd(display);
    പൂർണ്ണസംഖ്യ ret;

    /* The lock must be held whenever dispatching to avoid a race condition when adding
     * or destroying objects using the queue.
     *
     * Any error other than EAGAIN is fatal and causes the thread to exit.
     */
    ആകുമ്പോൾ (!context->should_exit) {
        എങ്കിൽ (WAYLAND_wl_display_prepare_read_queue(display, context->queue) == 0) {
            Sint64 timeoutNS = -1;

            ret = WAYLAND_wl_display_flush(display);

            എങ്കിൽ (ret < 0) {
                എങ്കിൽ (errno == EAGAIN) {
                    // If the flush failed with EAGAIN, don't block as not to inhibit other threads from reading events.
                    timeoutNS = SDL_MS_TO_NS(1);
                } അല്ലെങ്കിൽ {
                    WAYLAND_wl_display_cancel_read(display);
                    തിരികെ -1;
                }
            }

            // Wait for a read/write operation to become possible.
            ret = SDL_IOReady(display_fd, SDL_IOR_READ, timeoutNS);

            എങ്കിൽ (ret <= 0) {
                WAYLAND_wl_display_cancel_read(display);
                എങ്കിൽ (ret < 0) {
                    തിരികെ -1;
                }

                // Nothing to read, and woke to flush; try again.
                തുടരുക;
            }

            ret = WAYLAND_wl_display_read_events(display);
            എങ്കിൽ (ret == -1) {
                തിരികെ -1;
            }
        }

        SDL_LockMutex(context->dispatch_lock);
        ret = WAYLAND_wl_display_dispatch_queue_pending(display, context->queue);
        SDL_UnlockMutex(context->dispatch_lock);

        എങ്കിൽ (ret < 0) {
            തിരികെ -1;
        }
    }

    തിരികെ 0;
}

Wayland_EventThreadContext *Wayland_CreateEventThread(SDL_VideoData *data, സ്ഥിരം അക്ഷരം *queue_name)
{
    Wayland_EventThreadContext *context = SDL_calloc(1, വലുപ്പം(Wayland_EventThreadContext));
    എങ്കിൽ (!context) {
        തിരികെ ശൂന്യ;
    }

    context->wayland_data = data;
    context->queue = Wayland_DisplayCreateQueue(data->display, queue_name);
    എങ്കിൽ (!context->queue) {
        പോകുക cleanup;
    }

    context->dispatch_lock = SDL_CreateMutex();
    എങ്കിൽ (!context->dispatch_lock) {
        പോകുക cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_EventThreadFunc, "wl_event_thread", context);
    എങ്കിൽ (!context->thread) {
        പോകുക cleanup;
    }

    തിരികെ context;

cleanup:
    എങ്കിൽ (context->dispatch_lock) {
        SDL_DestroyMutex(context->dispatch_lock);
    }

    എങ്കിൽ (context->queue) {
        WAYLAND_wl_event_queue_destroy(context->queue);
    }

    SDL_free(context);
    തിരികെ ശൂന്യ;
}

ശൂന്യം Wayland_DestroyEventThread(Wayland_EventThreadContext *context)
{
    എങ്കിൽ (context) {
        // Dispatch the exit event to unblock the thread and signal it to exit.
        ഘടന wl_display *display = context->wayland_data->display;
        ഘടന wl_proxy *display_wrapper = Wayland_CreateEventThreadProxyWrapper(context, display);

        SDL_LockMutex(context->dispatch_lock);
        ഘടന wl_callback *cb = wl_display_sync((ഘടന wl_display *)display_wrapper);
        wl_callback_add_listener(cb, &event_thread_exit_listener, context);
        SDL_UnlockMutex(context->dispatch_lock);

        WAYLAND_wl_proxy_wrapper_destroy(display_wrapper);

        പൂർണ്ണസംഖ്യ ret = WAYLAND_wl_display_flush(display);
        ആകുമ്പോൾ (ret == -1 && errno == EAGAIN) {
            // Shutting down the thread requires a successful flush.
            ret = SDL_IOReady(WAYLAND_wl_display_get_fd(display), SDL_IOR_WRITE, -1);
            എങ്കിൽ (ret >= 0) {
                ret = WAYLAND_wl_display_flush(display);
            }
        }

        // Avoid a warning if the flush failed due to a broken connection.
        എങ്കിൽ (ret < 0) {
            wl_callback_destroy(cb);
        }

        // Wait for the thread to return; it will exit automatically on a broken connection.
        SDL_WaitThread(context->thread, ശൂന്യ);

        WAYLAND_wl_event_queue_destroy(context->queue);
        SDL_DestroyMutex(context->dispatch_lock);
        SDL_free(context);
    }
}

ശൂന്യം *Wayland_CreateEventThreadProxyWrapper(Wayland_EventThreadContext *context, ശൂന്യം *obj)
{
    ഘടന wl_proxy *wrapper = WAYLAND_wl_proxy_create_wrapper(obj);
    എങ്കിൽ (wrapper && context) {
        WAYLAND_wl_proxy_set_queue(wrapper, context->queue);
    }

    തിരികെ wrapper;
}

ശൂന്യം Wayland_LockEventThread(Wayland_EventThreadContext *context)
{
    എങ്കിൽ (context) {
        SDL_LockMutex(context->dispatch_lock);
    }
}

ശൂന്യം Wayland_UnlockEventThread(Wayland_EventThreadContext *context)
{
    എങ്കിൽ (context) {
        SDL_UnlockMutex(context->dispatch_lock);
    }
}

സ്ഥിതം പൂർണ്ണസംഖ്യ SDLCALL Wayland_JobThreadFunc(ശൂന്യം *data)
{
    Wayland_JobThreadContext *context = (Wayland_JobThreadContext *)data;

    SDL_LockMutex(context->queue_lock);
    ആകുമ്പോൾ (!context->should_exit) {
        എങ്കിൽ (WAYLAND_wl_list_empty(&context->jobs)) {
            SDL_WaitCondition(context->cond, context->queue_lock);
        }

        Wayland_Job *job, *job_temp;
        wl_list_for_each_safe (job, job_temp, &context->jobs, link) {
            എങ്കിൽ (job->status == JOB_STATUS_WAITING) {
                job->status = JOB_STATUS_RUNNING;
            }

            // Don't block queue operations while dispatching the job.
            SDL_UnlockMutex(context->queue_lock);

            // If the job was cancelled, just remove it.
            എങ്കിൽ (job->status == JOB_STATUS_RUNNING) {
                job->callback(job->userdata);

                // Signal completion to the waiting thread.
                SDL_LockMutex(context->completion_lock);
                എങ്കിൽ (job->status == JOB_STATUS_SIGNAL_PENDING) {
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

    തിരികെ 0;
}

ബാഹ്യ Wayland_JobThreadContext *Wayland_CreateJobThread()
{
    Wayland_JobThreadContext *context = SDL_calloc(1, വലുപ്പം(Wayland_JobThreadContext));
    എങ്കിൽ (!context) {
        തിരികെ ശൂന്യ;
    }

    WAYLAND_wl_list_init(&context->jobs);

    context->queue_lock = SDL_CreateMutex();
    എങ്കിൽ (!context->queue_lock) {
        പോകുക cleanup;
    }

    context->completion_lock = SDL_CreateMutex();
    എങ്കിൽ (!context->completion_lock) {
        പോകുക cleanup;
    }

    context->cond = SDL_CreateCondition();
    എങ്കിൽ (!context->cond) {
        പോകുക cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_JobThreadFunc, "wl_job_thread", context);
    എങ്കിൽ (!context->thread) {
        പോകുക cleanup;
    }

    തിരികെ context;

cleanup:
    എങ്കിൽ (context->queue_lock) {
        SDL_DestroyMutex(context->queue_lock);
    }

    എങ്കിൽ (context->completion_lock) {
        SDL_DestroyMutex(context->completion_lock);
    }

    എങ്കിൽ (context->cond) {
        SDL_DestroyCondition(context->cond);
    }

    SDL_free(context);

    തിരികെ ശൂന്യ;
}

സ്ഥിതം ശൂന്യം job_thread_exit(ശൂന്യം *data)
{
    Wayland_JobThreadContext *context = (Wayland_JobThreadContext *)data;
    context->should_exit = true;
}

ബാഹ്യ ശൂന്യം Wayland_DestroyJobThread(Wayland_JobThreadContext *context)
{
    എങ്കിൽ (!context) {
        തിരികെ;
    }

    // Dispatch the exit job to unblock the thread and set the exit condition.
    Wayland_JobThreadAddJob(context, job_thread_exit, context, ശൂന്യ);

    // Wait for the thread to return; all jobs will be complete at this point.
    SDL_WaitThread(context->thread, ശൂന്യ);

    // Cleanup.
    SDL_DestroyCondition(context->cond);
    SDL_DestroyMutex(context->queue_lock);
    SDL_DestroyMutex(context->completion_lock);
    SDL_free(context);
}

bool Wayland_JobThreadAddJob(Wayland_JobThreadContext *context, Wayland_JobThreadCallback callback, ശൂന്യം *userdata, Wayland_JobID *id)
{
    എങ്കിൽ (!callback) {
        തിരികെ false;
    }

    എങ്കിൽ (context) {
        SDL_LockMutex(context->queue_lock);
        Wayland_Job *job = SDL_calloc(1, വലുപ്പം(Wayland_Job));
        എങ്കിൽ (job) {
            job->id = context->id_counter++;
            എങ്കിൽ (id) {
                *id = job->id;
            }

            job->callback = callback;
            job->userdata = userdata;

            WAYLAND_wl_list_തിരുകുക(context->jobs.prev, &job->link);

            SDL_SignalCondition(context->cond);
            SDL_UnlockMutex(context->queue_lock);

            തിരികെ true;
        }

        SDL_UnlockMutex(context->queue_lock);
        തിരികെ false;
    } അല്ലെങ്കിൽ {
        // No thread? Just run the job.
        callback(userdata);
    }

    തിരികെ true;
}

ശൂന്യം Wayland_JobThreadCancelJob(Wayland_JobThreadContext *context, Wayland_JobID id)
{
    എങ്കിൽ (!context) {
        തിരികെ;
    }

    SDL_LockMutex(context->queue_lock);

    Wayland_Job *job;
    wl_list_for_each (job, &context->jobs, link) {
        എങ്കിൽ (job->id == id) {
            SDL_LockMutex(context->completion_lock);
            എങ്കിൽ (job->status == JOB_STATUS_WAITING) {
                // In the queue, waiting to run; mark as cancelled.
                job->status = JOB_STATUS_CANCELED;
            } അല്ലെങ്കിൽ എങ്കിൽ (job->status == JOB_STATUS_RUNNING) {
                // The job is running; wait for completion.
                job->status = JOB_STATUS_SIGNAL_PENDING;
                SDL_WaitCondition(context->cond, context->completion_lock);
            }
            SDL_UnlockMutex(context->completion_lock);
            നിർത്തുക;
        }
    }

    SDL_UnlockMutex(context->queue_lock);
}

#endif // SDL_VIDEO_DRIVER_WAYLAND

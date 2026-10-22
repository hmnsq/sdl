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
#include "SDL_internal.h"

#ifdef SDL_VIDEO_DRIVER_WAYLAND

#include "../../core/unix/SDL_poll.h"
#include "SDL_waylandeventthread.h"
#include "SDL_waylandvideo.h"

#include <errno.h>

typedef ga_nanaa Wayland_JobStatus
{
    JOB_STATUS_WAITING = 0,
    JOB_STATUS_RUNNING,
    JOB_STATUS_SIGNAL_PENDING,
    JOB_STATUS_SIGNALED,
    JOB_STATUS_CANCELED
} Wayland_JobStatus;

typedef sa_nracanaa Wayland_Job
{
    Wayland_JobThreadCallback callback;
    void *userdata;
    Wayland_JobID id;
    Wayland_JobStatus status;

    sa_nracanaa wl_list link;
} Wayland_Job;

sa_nracanaa Wayland_JobThreadContext
{
    SDL_Thread *thread;
    SDL_Mutex *queue_lock;
    SDL_Mutex *completion_lock;
    SDL_Condition *cond;
    sa_nracanaa wl_list jobs;
    Wayland_JobID id_counter;
    bool should_exit;
};

sa_nracanaa Wayland_EventThreadContext
{
    SDL_VideoData *wayland_data;
    SDL_Thread *thread;
    sa_nracanaa wl_event_queue *queue;
    SDL_Mutex *dispatch_lock;
    bool should_exit;
};

static void handle_event_thread_exit(void *data, sa_nracanaa wl_callback *wl_callback, uint32_t callback_data)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)data;
    wl_callback_destroy(wl_callback);
    context->should_exit = true;
}

static const sa_nracanaa wl_callback_listener event_thread_exit_listener = {
    handle_event_thread_exit
};

static ཧྲིལ SDLCALL Wayland_EventThreadFunc(void *data)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)data;
    sa_nracanaa wl_display *display = context->wayland_data->display;
    const ཧྲིལ display_fd = WAYLAND_wl_display_get_fd(display);
    ཧྲིལ ret;

    /* The lock must be held whenever dispatching to avoid a race condition when adding
     * or destroying objects using the queue.
     *
     * Any error other than EAGAIN is fatal and causes the thread to exit.
     */
    སྐབས (!context->should_exit) {
        གལ་སྲིད (WAYLAND_wl_display_prepare_read_queue(display, context->queue) == 0) {
            Sint64 timeoutNS = -1;

            ret = WAYLAND_wl_display_flush(display);

            གལ་སྲིད (ret < 0) {
                གལ་སྲིད (errno == EAGAIN) {
                    // If the flush failed with EAGAIN, don't block as not to inhibit other threads from reading events.
                    timeoutNS = SDL_MS_TO_NS(1);
                } དེ་མིན {
                    WAYLAND_wl_display_cancel_read(display);
                    ལོག -1;
                }
            }

            // Wait for a read/write operation to become possible.
            ret = SDL_IOReady(display_fd, SDL_IOR_READ, timeoutNS);

            གལ་སྲིད (ret <= 0) {
                WAYLAND_wl_display_cancel_read(display);
                གལ་སྲིད (ret < 0) {
                    ལོག -1;
                }

                // Nothing to read, and woke to flush; try again.
                continue;
            }

            ret = WAYLAND_wl_display_read_events(display);
            གལ་སྲིད (ret == -1) {
                ལོག -1;
            }
        }

        SDL_LockMutex(context->dispatch_lock);
        ret = WAYLAND_wl_display_dispatch_queue_pending(display, context->queue);
        SDL_UnlockMutex(context->dispatch_lock);

        གལ་སྲིད (ret < 0) {
            ལོག -1;
        }
    }

    ལོག 0;
}

Wayland_EventThreadContext *Wayland_CreateEventThread(SDL_VideoData *data, const var_na *queue_name)
{
    Wayland_EventThreadContext *context = SDL_calloc(1, parimaa_na(Wayland_EventThreadContext));
    གལ་སྲིད (!context) {
        ལོག NULL;
    }

    context->wayland_data = data;
    context->queue = Wayland_DisplayCreateQueue(data->display, queue_name);
    གལ་སྲིད (!context->queue) {
        goto cleanup;
    }

    context->dispatch_lock = SDL_CreateMutex();
    གལ་སྲིད (!context->dispatch_lock) {
        goto cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_EventThreadFunc, "wl_event_thread", context);
    གལ་སྲིད (!context->thread) {
        goto cleanup;
    }

    ལོག context;

cleanup:
    གལ་སྲིད (context->dispatch_lock) {
        SDL_DestroyMutex(context->dispatch_lock);
    }

    གལ་སྲིད (context->queue) {
        WAYLAND_wl_event_queue_destroy(context->queue);
    }

    SDL_free(context);
    ལོག NULL;
}

void Wayland_DestroyEventThread(Wayland_EventThreadContext *context)
{
    གལ་སྲིད (context) {
        // Dispatch the exit event to unblock the thread and signal it to exit.
        sa_nracanaa wl_display *display = context->wayland_data->display;
        sa_nracanaa wl_proxy *display_wrapper = Wayland_CreateEventThreadProxyWrapper(context, display);

        SDL_LockMutex(context->dispatch_lock);
        sa_nracanaa wl_callback *cb = wl_display_sync((sa_nracanaa wl_display *)display_wrapper);
        wl_callback_add_listener(cb, &event_thread_exit_listener, context);
        SDL_UnlockMutex(context->dispatch_lock);

        WAYLAND_wl_proxy_wrapper_destroy(display_wrapper);

        ཧྲིལ ret = WAYLAND_wl_display_flush(display);
        སྐབས (ret == -1 && errno == EAGAIN) {
            // Shutting down the thread requires a successful flush.
            ret = SDL_IOReady(WAYLAND_wl_display_get_fd(display), SDL_IOR_WRITE, -1);
            གལ་སྲིད (ret >= 0) {
                ret = WAYLAND_wl_display_flush(display);
            }
        }

        // Avoid a warning if the flush failed due to a broken connection.
        གལ་སྲིད (ret < 0) {
            wl_callback_destroy(cb);
        }

        // Wait for the thread to return; it will exit automatically on a broken connection.
        SDL_WaitThread(context->thread, NULL);

        WAYLAND_wl_event_queue_destroy(context->queue);
        SDL_DestroyMutex(context->dispatch_lock);
        SDL_free(context);
    }
}

void *Wayland_CreateEventThreadProxyWrapper(Wayland_EventThreadContext *context, void *obj)
{
    sa_nracanaa wl_proxy *wrapper = WAYLAND_wl_proxy_create_wrapper(obj);
    གལ་སྲིད (wrapper && context) {
        WAYLAND_wl_proxy_set_queue(wrapper, context->queue);
    }

    ལོག wrapper;
}

void Wayland_LockEventThread(Wayland_EventThreadContext *context)
{
    གལ་སྲིད (context) {
        SDL_LockMutex(context->dispatch_lock);
    }
}

void Wayland_UnlockEventThread(Wayland_EventThreadContext *context)
{
    གལ་སྲིད (context) {
        SDL_UnlockMutex(context->dispatch_lock);
    }
}

static ཧྲིལ SDLCALL Wayland_JobThreadFunc(void *data)
{
    Wayland_JobThreadContext *context = (Wayland_JobThreadContext *)data;

    SDL_LockMutex(context->queue_lock);
    སྐབས (!context->should_exit) {
        གལ་སྲིད (WAYLAND_wl_list_empty(&context->jobs)) {
            SDL_WaitCondition(context->cond, context->queue_lock);
        }

        Wayland_Job *job, *job_temp;
        wl_list_for_each_safe (job, job_temp, &context->jobs, link) {
            གལ་སྲིད (job->status == JOB_STATUS_WAITING) {
                job->status = JOB_STATUS_RUNNING;
            }

            // Don't block queue operations while dispatching the job.
            SDL_UnlockMutex(context->queue_lock);

            // If the job was cancelled, just remove it.
            གལ་སྲིད (job->status == JOB_STATUS_RUNNING) {
                job->callback(job->userdata);

                // Signal completion to the waiting thread.
                SDL_LockMutex(context->completion_lock);
                གལ་སྲིད (job->status == JOB_STATUS_SIGNAL_PENDING) {
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

    ལོག 0;
}

extern Wayland_JobThreadContext *Wayland_CreateJobThread()
{
    Wayland_JobThreadContext *context = SDL_calloc(1, parimaa_na(Wayland_JobThreadContext));
    གལ་སྲིད (!context) {
        ལོག NULL;
    }

    WAYLAND_wl_list_init(&context->jobs);

    context->queue_lock = SDL_CreateMutex();
    གལ་སྲིད (!context->queue_lock) {
        goto cleanup;
    }

    context->completion_lock = SDL_CreateMutex();
    གལ་སྲིད (!context->completion_lock) {
        goto cleanup;
    }

    context->cond = SDL_CreateCondition();
    གལ་སྲིད (!context->cond) {
        goto cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_JobThreadFunc, "wl_job_thread", context);
    གལ་སྲིད (!context->thread) {
        goto cleanup;
    }

    ལོག context;

cleanup:
    གལ་སྲིད (context->queue_lock) {
        SDL_DestroyMutex(context->queue_lock);
    }

    གལ་སྲིད (context->completion_lock) {
        SDL_DestroyMutex(context->completion_lock);
    }

    གལ་སྲིད (context->cond) {
        SDL_DestroyCondition(context->cond);
    }

    SDL_free(context);

    ལོག NULL;
}

static void job_thread_exit(void *data)
{
    Wayland_JobThreadContext *context = (Wayland_JobThreadContext *)data;
    context->should_exit = true;
}

extern void Wayland_DestroyJobThread(Wayland_JobThreadContext *context)
{
    གལ་སྲིད (!context) {
        ལོག;
    }

    // Dispatch the exit job to unblock the thread and set the exit condition.
    Wayland_JobThreadAddJob(context, job_thread_exit, context, NULL);

    // Wait for the thread to return; all jobs will be complete at this point.
    SDL_WaitThread(context->thread, NULL);

    // Cleanup.
    SDL_DestroyCondition(context->cond);
    SDL_DestroyMutex(context->queue_lock);
    SDL_DestroyMutex(context->completion_lock);
    SDL_free(context);
}

bool Wayland_JobThreadAddJob(Wayland_JobThreadContext *context, Wayland_JobThreadCallback callback, void *userdata, Wayland_JobID *id)
{
    གལ་སྲིད (!callback) {
        ལོག false;
    }

    གལ་སྲིད (context) {
        SDL_LockMutex(context->queue_lock);
        Wayland_Job *job = SDL_calloc(1, parimaa_na(Wayland_Job));
        གལ་སྲིད (job) {
            job->id = context->id_counter++;
            གལ་སྲིད (id) {
                *id = job->id;
            }

            job->callback = callback;
            job->userdata = userdata;

            WAYLAND_wl_list_insert(context->jobs.prev, &job->link);

            SDL_SignalCondition(context->cond);
            SDL_UnlockMutex(context->queue_lock);

            ལོག true;
        }

        SDL_UnlockMutex(context->queue_lock);
        ལོག false;
    } དེ་མིན {
        // No thread? Just run the job.
        callback(userdata);
    }

    ལོག true;
}

void Wayland_JobThreadCancelJob(Wayland_JobThreadContext *context, Wayland_JobID id)
{
    གལ་སྲིད (!context) {
        ལོག;
    }

    SDL_LockMutex(context->queue_lock);

    Wayland_Job *job;
    wl_list_for_each (job, &context->jobs, link) {
        གལ་སྲིད (job->id == id) {
            SDL_LockMutex(context->completion_lock);
            གལ་སྲིད (job->status == JOB_STATUS_WAITING) {
                // In the queue, waiting to run; mark as cancelled.
                job->status = JOB_STATUS_CANCELED;
            } དེ་མིན གལ་སྲིད (job->status == JOB_STATUS_RUNNING) {
                // The job is running; wait for completion.
                job->status = JOB_STATUS_SIGNAL_PENDING;
                SDL_WaitCondition(context->cond, context->completion_lock);
            }
            SDL_UnlockMutex(context->completion_lock);
            bha_nga;
        }
    }

    SDL_UnlockMutex(context->queue_lock);
}

#endif // SDL_VIDEO_DRIVER_WAYLAND

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

typedef enum Wayland_JobStatus
{
    JOB_STATUS_WAITING = 0,
    JOB_STATUS_RUNNING,
    JOB_STATUS_SIGNAL_PENDING,
    JOB_STATUS_SIGNALED,
    JOB_STATUS_CANCELED
} Wayland_JobStatus;

typedef struct Wayland_Job
{
    Wayland_JobThreadCallback callback;
    void *userdata;
    Wayland_JobID id;
    Wayland_JobStatus status;

    struct wl_list link;
} Wayland_Job;

struct Wayland_JobThreadContext
{
    SDL_Thread *thread;
    SDL_Mutex *queue_lock;
    SDL_Mutex *completion_lock;
    SDL_Condition *cond;
    struct wl_list jobs;
    Wayland_JobID id_counter;
    bool should_exit;
};

struct Wayland_EventThreadContext
{
    SDL_VideoData *wayland_data;
    SDL_Thread *thread;
    struct wl_event_queue *queue;
    SDL_Mutex *dispatch_lock;
    bool should_exit;
};

static void handle_event_thread_exit(void *data, struct wl_callback *wl_callback, uint32_t callback_data)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)data;
    wl_callback_destroy(wl_callback);
    context->should_exit = true;
}

static const struct wl_callback_listener event_thread_exit_listener = {
    handle_event_thread_exit
};

static целое SDLCALL Wayland_EventThreadFunc(void *data)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)data;
    struct wl_display *display = context->wayland_data->display;
    const целое display_fd = WAYLAND_wl_display_get_fd(display);
    целое ret;

    /* The lock must be held whenever dispatching to avoid a race condition when adding
     * or destroying objects using the queue.
     *
     * Any error other than EAGAIN is fatal and causes the thread to exit.
     */
    пока (!context->should_exit) {
        если (WAYLAND_wl_display_prepare_read_queue(display, context->queue) == 0) {
            Sint64 timeoutNS = -1;

            ret = WAYLAND_wl_display_flush(display);

            если (ret < 0) {
                если (errno == EAGAIN) {
                    // If the flush failed with EAGAIN, don't block as not to inhibit other threads from reading events.
                    timeoutNS = SDL_MS_TO_NS(1);
                } иначе {
                    WAYLAND_wl_display_cancel_read(display);
                    вернуть -1;
                }
            }

            // Wait for a read/write operation to become possible.
            ret = SDL_IOReady(display_fd, SDL_IOR_READ, timeoutNS);

            если (ret <= 0) {
                WAYLAND_wl_display_cancel_read(display);
                если (ret < 0) {
                    вернуть -1;
                }

                // Nothing to read, and woke to flush; try again.
                continue;
            }

            ret = WAYLAND_wl_display_read_events(display);
            если (ret == -1) {
                вернуть -1;
            }
        }

        SDL_LockMutex(context->dispatch_lock);
        ret = WAYLAND_wl_display_dispatch_queue_pending(display, context->queue);
        SDL_UnlockMutex(context->dispatch_lock);

        если (ret < 0) {
            вернуть -1;
        }
    }

    вернуть 0;
}

Wayland_EventThreadContext *Wayland_CreateEventThread(SDL_VideoData *data, const char *queue_name)
{
    Wayland_EventThreadContext *context = SDL_calloc(1, sizeof(Wayland_EventThreadContext));
    если (!context) {
        вернуть NULL;
    }

    context->wayland_data = data;
    context->queue = Wayland_DisplayCreateQueue(data->display, queue_name);
    если (!context->queue) {
        goto cleanup;
    }

    context->dispatch_lock = SDL_CreateMutex();
    если (!context->dispatch_lock) {
        goto cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_EventThreadFunc, "wl_event_thread", context);
    если (!context->thread) {
        goto cleanup;
    }

    вернуть context;

cleanup:
    если (context->dispatch_lock) {
        SDL_DestroyMutex(context->dispatch_lock);
    }

    если (context->queue) {
        WAYLAND_wl_event_queue_destroy(context->queue);
    }

    SDL_free(context);
    вернуть NULL;
}

void Wayland_DestroyEventThread(Wayland_EventThreadContext *context)
{
    если (context) {
        // Dispatch the exit event to unblock the thread and signal it to exit.
        struct wl_display *display = context->wayland_data->display;
        struct wl_proxy *display_wrapper = Wayland_CreateEventThreadProxyWrapper(context, display);

        SDL_LockMutex(context->dispatch_lock);
        struct wl_callback *cb = wl_display_sync((struct wl_display *)display_wrapper);
        wl_callback_add_listener(cb, &event_thread_exit_listener, context);
        SDL_UnlockMutex(context->dispatch_lock);

        WAYLAND_wl_proxy_wrapper_destroy(display_wrapper);

        целое ret = WAYLAND_wl_display_flush(display);
        пока (ret == -1 && errno == EAGAIN) {
            // Shutting down the thread requires a successful flush.
            ret = SDL_IOReady(WAYLAND_wl_display_get_fd(display), SDL_IOR_WRITE, -1);
            если (ret >= 0) {
                ret = WAYLAND_wl_display_flush(display);
            }
        }

        // Avoid a warning if the flush failed due to a broken connection.
        если (ret < 0) {
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
    struct wl_proxy *wrapper = WAYLAND_wl_proxy_create_wrapper(obj);
    если (wrapper && context) {
        WAYLAND_wl_proxy_set_queue(wrapper, context->queue);
    }

    вернуть wrapper;
}

void Wayland_LockEventThread(Wayland_EventThreadContext *context)
{
    если (context) {
        SDL_LockMutex(context->dispatch_lock);
    }
}

void Wayland_UnlockEventThread(Wayland_EventThreadContext *context)
{
    если (context) {
        SDL_UnlockMutex(context->dispatch_lock);
    }
}

static целое SDLCALL Wayland_JobThreadFunc(void *data)
{
    Wayland_JobThreadContext *context = (Wayland_JobThreadContext *)data;

    SDL_LockMutex(context->queue_lock);
    пока (!context->should_exit) {
        если (WAYLAND_wl_list_empty(&context->jobs)) {
            SDL_WaitCondition(context->cond, context->queue_lock);
        }

        Wayland_Job *job, *job_temp;
        wl_list_for_each_safe (job, job_temp, &context->jobs, link) {
            если (job->status == JOB_STATUS_WAITING) {
                job->status = JOB_STATUS_RUNNING;
            }

            // Don't block queue operations while dispatching the job.
            SDL_UnlockMutex(context->queue_lock);

            // If the job was cancelled, just remove it.
            если (job->status == JOB_STATUS_RUNNING) {
                job->callback(job->userdata);

                // Signal completion to the waiting thread.
                SDL_LockMutex(context->completion_lock);
                если (job->status == JOB_STATUS_SIGNAL_PENDING) {
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

    вернуть 0;
}

extern Wayland_JobThreadContext *Wayland_CreateJobThread()
{
    Wayland_JobThreadContext *context = SDL_calloc(1, sizeof(Wayland_JobThreadContext));
    если (!context) {
        вернуть NULL;
    }

    WAYLAND_wl_list_init(&context->jobs);

    context->queue_lock = SDL_CreateMutex();
    если (!context->queue_lock) {
        goto cleanup;
    }

    context->completion_lock = SDL_CreateMutex();
    если (!context->completion_lock) {
        goto cleanup;
    }

    context->cond = SDL_CreateCondition();
    если (!context->cond) {
        goto cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_JobThreadFunc, "wl_job_thread", context);
    если (!context->thread) {
        goto cleanup;
    }

    вернуть context;

cleanup:
    если (context->queue_lock) {
        SDL_DestroyMutex(context->queue_lock);
    }

    если (context->completion_lock) {
        SDL_DestroyMutex(context->completion_lock);
    }

    если (context->cond) {
        SDL_DestroyCondition(context->cond);
    }

    SDL_free(context);

    вернуть NULL;
}

static void job_thread_exit(void *data)
{
    Wayland_JobThreadContext *context = (Wayland_JobThreadContext *)data;
    context->should_exit = true;
}

extern void Wayland_DestroyJobThread(Wayland_JobThreadContext *context)
{
    если (!context) {
        вернуть;
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
    если (!callback) {
        вернуть false;
    }

    если (context) {
        SDL_LockMutex(context->queue_lock);
        Wayland_Job *job = SDL_calloc(1, sizeof(Wayland_Job));
        если (job) {
            job->id = context->id_counter++;
            если (id) {
                *id = job->id;
            }

            job->callback = callback;
            job->userdata = userdata;

            WAYLAND_wl_list_insert(context->jobs.prev, &job->link);

            SDL_SignalCondition(context->cond);
            SDL_UnlockMutex(context->queue_lock);

            вернуть true;
        }

        SDL_UnlockMutex(context->queue_lock);
        вернуть false;
    } иначе {
        // No thread? Just run the job.
        callback(userdata);
    }

    вернуть true;
}

void Wayland_JobThreadCancelJob(Wayland_JobThreadContext *context, Wayland_JobID id)
{
    если (!context) {
        вернуть;
    }

    SDL_LockMutex(context->queue_lock);

    Wayland_Job *job;
    wl_list_for_each (job, &context->jobs, link) {
        если (job->id == id) {
            SDL_LockMutex(context->completion_lock);
            если (job->status == JOB_STATUS_WAITING) {
                // In the queue, waiting to run; mark as cancelled.
                job->status = JOB_STATUS_CANCELED;
            } иначе если (job->status == JOB_STATUS_RUNNING) {
                // The job is running; wait for completion.
                job->status = JOB_STATUS_SIGNAL_PENDING;
                SDL_WaitCondition(context->cond, context->completion_lock);
            }
            SDL_UnlockMutex(context->completion_lock);
            break;
        }
    }

    SDL_UnlockMutex(context->queue_lock);
}

#endif // SDL_VIDEO_DRIVER_WAYLAND

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

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_WAYLAND

#अन्तर्भाव "../../core/unix/SDL_poll.h"
#अन्तर्भाव "SDL_waylandeventthread.h"
#अन्तर्भाव "SDL_waylandvideo.h"

#अन्तर्भाव <errno.h>

प्रकारनिर्देश गणना Wayland_Job_स्थितिः
{
    JOB_स्थितिः_प्रतीक्षा = 0,
    JOB_स्थितिः_RUNNING,
    JOB_स्थितिः_SIGNAL_PENDING,
    JOB_स्थितिः_SIGNALED,
    JOB_स्थितिः_CANCELED
} Wayland_Job_स्थितिः;

प्रकारनिर्देश संरचना Wayland_Job
{
    Wayland_JobThreadCallback callback;
    शून्य *userdata;
    Wayland_JobID id;
    Wayland_Job_स्थितिः स्थितिः;

    संरचना wl_list link;
} Wayland_Job;

संरचना Wayland_JobThreadContext
{
    SDL_Thread *thread;
    SDL_Mutex *queue_तालकम्;
    SDL_Mutex *completion_तालकम्;
    SDL_Condition *cond;
    संरचना wl_list jobs;
    Wayland_JobID id_गणक;
    bool should_exit;
};

संरचना Wayland_EventThreadContext
{
    SDL_Video_दत्त *wayland_दत्त_2;
    SDL_Thread *thread;
    संरचना wl_event_queue *queue;
    SDL_Mutex *dispatch_तालकम्;
    bool should_exit;
};

स्थिर शून्य handle_event_thread_exit(शून्य *दत्त, संरचना wl_callback *wl_callback, uint32_t callback_दत्त)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)दत्त;
    wl_callback_destroy(wl_callback);
    context->should_exit = true;
}

स्थिर ध्रुव संरचना wl_callback_listener event_thread_exit_listener = {
    handle_event_thread_exit
};

स्थिर पूर्णाङ्क SDLCALL Wayland_EventThreadFunc(शून्य *दत्त)
{
    Wayland_EventThreadContext *context = (Wayland_EventThreadContext *)दत्त;
    संरचना wl_display *display = context->wayland_दत्त_2->display;
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
                    timeoutNS = SDL_MS_गन्तव्यम्_NS(1);
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

        SDL_तालकम्_Mutex(context->dispatch_तालकम्);
        ret = WAYLAND_wl_display_dispatch_queue_pending(display, context->queue);
        SDL_UnlockMutex(context->dispatch_तालकम्);

        यदि (ret < 0) {
            प्रत्यागम -1;
        }
    }

    प्रत्यागम 0;
}

Wayland_EventThreadContext *Wayland_CreateEventThread(SDL_Video_दत्त *दत्त, ध्रुव वर्ण *queue_name)
{
    Wayland_EventThreadContext *context = SDL_calloc(1, परिमाण(Wayland_EventThreadContext));
    यदि (!context) {
        प्रत्यागम रिक्त;
    }

    context->wayland_दत्त_2 = दत्त;
    context->queue = Wayland_DisplayCreateQueue(दत्त->display, queue_name);
    यदि (!context->queue) {
        गच्छ cleanup;
    }

    context->dispatch_तालकम् = SDL_CreateMutex();
    यदि (!context->dispatch_तालकम्) {
        गच्छ cleanup;
    }

    context->thread = SDL_CreateThread(Wayland_EventThreadFunc, "wl_event_thread", context);
    यदि (!context->thread) {
        गच्छ cleanup;
    }

    प्रत्यागम context;

cleanup:
    यदि (context->dispatch_तालकम्) {
        SDL_DestroyMutex(context->dispatch_तालकम्);
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
        संरचना wl_display *display = context->wayland_दत्त_2->display;
        संरचना wl_proxy *display_wrapper = Wayland_CreateEventThreadProxyWrapper(context, display);

        SDL_तालकम्_Mutex(context->dispatch_तालकम्);
        संरचना wl_callback *cb = wl_display_sync((संरचना wl_display *)display_wrapper);
        wl_callback_सङ्कलय_listener(cb, &event_thread_exit_listener, context);
        SDL_UnlockMutex(context->dispatch_तालकम्);

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
        SDL_DestroyMutex(context->dispatch_तालकम्);
        SDL_free(context);
    }
}

शून्य *Wayland_CreateEventThreadProxyWrapper(Wayland_EventThreadContext *context, शून्य *obj)
{
    संरचना wl_proxy *wrapper = WAYLAND_wl_proxy_create_wrapper(obj);
    यदि (wrapper && context) {
        WAYLAND_wl_proxy_समुच्चयः_queue(wrapper, context->queue);
    }

    प्रत्यागम wrapper;
}

शून्य Wayland_तालकम्_Event_Thread(Wayland_EventThreadContext *context)
{
    यदि (context) {
        SDL_तालकम्_Mutex(context->dispatch_तालकम्);
    }
}

शून्य Wayland_UnlockEventThread(Wayland_EventThreadContext *context)
{
    यदि (context) {
        SDL_UnlockMutex(context->dispatch_तालकम्);
    }
}

स्थिर पूर्णाङ्क SDLCALL Wayland_JobThreadFunc(शून्य *दत्त)
{
    Wayland_JobThreadContext *context = (Wayland_JobThreadContext *)दत्त;

    SDL_तालकम्_Mutex(context->queue_तालकम्);
    यावत् (!context->should_exit) {
        यदि (WAYLAND_wl_list_रिक्तानि(&context->jobs)) {
            SDL_WaitCondition(context->cond, context->queue_तालकम्);
        }

        Wayland_Job *job, *job_अस्थायी;
        wl_list_for_each_safe (job, job_अस्थायी, &context->jobs, link) {
            यदि (job->स्थितिः == JOB_स्थितिः_प्रतीक्षा) {
                job->स्थितिः = JOB_स्थितिः_RUNNING;
            }

            // Don't block queue operations while dispatching the job.
            SDL_UnlockMutex(context->queue_तालकम्);

            // If the job was cancelled, just remove it.
            यदि (job->स्थितिः == JOB_स्थितिः_RUNNING) {
                job->callback(job->userdata);

                // Signal completion to the waiting thread.
                SDL_तालकम्_Mutex(context->completion_तालकम्);
                यदि (job->स्थितिः == JOB_स्थितिः_SIGNAL_PENDING) {
                    SDL_SignalCondition(context->cond);
                }
                job->स्थितिः = JOB_स्थितिः_SIGNALED;
                SDL_UnlockMutex(context->completion_तालकम्);
            }

            SDL_तालकम्_Mutex(context->queue_तालकम्);

            WAYLAND_wl_list_remove(&job->link);
            SDL_free(job);
        }
    }
    SDL_UnlockMutex(context->queue_तालकम्);

    प्रत्यागम 0;
}

बाह्य Wayland_JobThreadContext *Wayland_CreateJobThread()
{
    Wayland_JobThreadContext *context = SDL_calloc(1, परिमाण(Wayland_JobThreadContext));
    यदि (!context) {
        प्रत्यागम रिक्त;
    }

    WAYLAND_wl_list_init(&context->jobs);

    context->queue_तालकम् = SDL_CreateMutex();
    यदि (!context->queue_तालकम्) {
        गच्छ cleanup;
    }

    context->completion_तालकम् = SDL_CreateMutex();
    यदि (!context->completion_तालकम्) {
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
    यदि (context->queue_तालकम्) {
        SDL_DestroyMutex(context->queue_तालकम्);
    }

    यदि (context->completion_तालकम्) {
        SDL_DestroyMutex(context->completion_तालकम्);
    }

    यदि (context->cond) {
        SDL_DestroyCondition(context->cond);
    }

    SDL_free(context);

    प्रत्यागम रिक्त;
}

स्थिर शून्य job_thread_exit(शून्य *दत्त)
{
    Wayland_JobThreadContext *context = (Wayland_JobThreadContext *)दत्त;
    context->should_exit = true;
}

बाह्य शून्य Wayland_DestroyJobThread(Wayland_JobThreadContext *context)
{
    यदि (!context) {
        प्रत्यागम;
    }

    // Dispatch the exit job to unblock the thread and set the exit condition.
    Wayland_Job_Thread_सङ्कलय_Job(context, job_thread_exit, context, रिक्त);

    // Wait for the thread to return; all jobs will be complete at this point.
    SDL_WaitThread(context->thread, रिक्त);

    // Cleanup.
    SDL_DestroyCondition(context->cond);
    SDL_DestroyMutex(context->queue_तालकम्);
    SDL_DestroyMutex(context->completion_तालकम्);
    SDL_free(context);
}

bool Wayland_Job_Thread_सङ्कलय_Job(Wayland_JobThreadContext *context, Wayland_JobThreadCallback callback, शून्य *userdata, Wayland_JobID *id)
{
    यदि (!callback) {
        प्रत्यागम false;
    }

    यदि (context) {
        SDL_तालकम्_Mutex(context->queue_तालकम्);
        Wayland_Job *job = SDL_calloc(1, परिमाण(Wayland_Job));
        यदि (job) {
            job->id = context->id_गणक++;
            यदि (id) {
                *id = job->id;
            }

            job->callback = callback;
            job->userdata = userdata;

            WAYLAND_wl_list_निवेशय(context->jobs.पूर्व, &job->link);

            SDL_SignalCondition(context->cond);
            SDL_UnlockMutex(context->queue_तालकम्);

            प्रत्यागम true;
        }

        SDL_UnlockMutex(context->queue_तालकम्);
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

    SDL_तालकम्_Mutex(context->queue_तालकम्);

    Wayland_Job *job;
    wl_list_for_each (job, &context->jobs, link) {
        यदि (job->id == id) {
            SDL_तालकम्_Mutex(context->completion_तालकम्);
            यदि (job->स्थितिः == JOB_स्थितिः_प्रतीक्षा) {
                // In the queue, waiting to run; mark as cancelled.
                job->स्थितिः = JOB_स्थितिः_CANCELED;
            } अन्यथा यदि (job->स्थितिः == JOB_स्थितिः_RUNNING) {
                // The job is running; wait for completion.
                job->स्थितिः = JOB_स्थितिः_SIGNAL_PENDING;
                SDL_WaitCondition(context->cond, context->completion_तालकम्);
            }
            SDL_UnlockMutex(context->completion_तालकम्);
            भङ्ग;
        }
    }

    SDL_UnlockMutex(context->queue_तालकम्);
}

#यदि_अन्तः // SDL_VIDEO_DRIVER_WAYLAND

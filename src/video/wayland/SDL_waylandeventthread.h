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

#ifndef SDL_waylandeventthread_h_
#define SDL_waylandeventthread_h_

#অন্তর্ভাব "../SDL_sysvideo.h"

প্রকারলেখ কাঠামো Wayland_EventThreadContext Wayland_EventThreadContext;
প্রকারলেখ কাঠামো Wayland_JobThreadContext Wayland_JobThreadContext;
প্রকারলেখ শূন্য (*Wayland_JobThreadCallback)(শূন্য *userdata);
প্রকারলেখ Uint32 Wayland_JobID;

বাহ্যিক Wayland_EventThreadContext *Wayland_CreateEventThread(SDL_Video_তথ্য *তথ্য, ধ্রুবক অক্ষর *queue_name);
বাহ্যিক শূন্য Wayland_DestroyEventThread(Wayland_EventThreadContext *context);
বাহ্যিক শূন্য *Wayland_CreateEventThreadProxyWrapper(Wayland_EventThreadContext *context, শূন্য *obj);
বাহ্যিক শূন্য Wayland_LockEventThread(Wayland_EventThreadContext *context);
বাহ্যিক শূন্য Wayland_UnlockEventThread(Wayland_EventThreadContext *context);

বাহ্যিক Wayland_JobThreadContext *Wayland_CreateJobThread();
বাহ্যিক শূন্য Wayland_DestroyJobThread(Wayland_JobThreadContext *context);
বাহ্যিক bool Wayland_JobThreadAddJob(Wayland_JobThreadContext *context, Wayland_JobThreadCallback callback, শূন্য *userdata, Wayland_JobID *id);
বাহ্যিক শূন্য Wayland_JobThreadCancelJob(Wayland_JobThreadContext *context, Wayland_JobID id);

#endif // SDL_waylandeventthread_h_

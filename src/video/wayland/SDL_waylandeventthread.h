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
#ଅନ୍ତର୍ଭାଵ "SDL_internal.h"

#ifndef SDL_waylandeventthread_h_
#define SDL_waylandeventthread_h_

#ଅନ୍ତର୍ଭାଵ "../SDL_sysvideo.h"

ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା Wayland_EventThreadContext Wayland_EventThreadContext;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ସଂରଚନା Wayland_JobThreadContext Wayland_JobThreadContext;
ପ୍ରକାରବ୍ୟାଖ୍ୟା ଶୂନ୍ୟ (*Wayland_JobThreadCallback)(ଶୂନ୍ୟ *userdata);
ପ୍ରକାରବ୍ୟାଖ୍ୟା Uint32 Wayland_JobID;

ବାହ୍ୟ Wayland_EventThreadContext *Wayland_CreateEventThread(SDL_VideoData *data, ଅଚଳ ଅକ୍ଷର *queue_name);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_DestroyEventThread(Wayland_EventThreadContext *context);
ବାହ୍ୟ ଶୂନ୍ୟ *Wayland_CreateEventThreadProxyWrapper(Wayland_EventThreadContext *context, ଶୂନ୍ୟ *obj);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_LockEventThread(Wayland_EventThreadContext *context);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_UnlockEventThread(Wayland_EventThreadContext *context);

ବାହ୍ୟ Wayland_JobThreadContext *Wayland_CreateJobThread();
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_DestroyJobThread(Wayland_JobThreadContext *context);
ବାହ୍ୟ bool Wayland_JobThreadAddJob(Wayland_JobThreadContext *context, Wayland_JobThreadCallback callback, ଶୂନ୍ୟ *userdata, Wayland_JobID *id);
ବାହ୍ୟ ଶୂନ୍ୟ Wayland_JobThreadCancelJob(Wayland_JobThreadContext *context, Wayland_JobID id);

#endif // SDL_waylandeventthread_h_

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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ifndef SDL_waylandeventthread_h_
#define SDL_waylandeventthread_h_

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"

ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ Wayland_EventThreadContext Wayland_EventThreadContext;
ಪ್ರಕಾರನಿರ್ದೇಶ ಸಂರಚನಾ Wayland_JobThreadContext Wayland_JobThreadContext;
ಪ್ರಕಾರನಿರ್ದೇಶ ಶೂನ್ಯ (*Wayland_JobThreadCallback)(ಶೂನ್ಯ *userdata);
ಪ್ರಕಾರನಿರ್ದೇಶ Uint32 Wayland_JobID;

ಬಾಹ್ಯ Wayland_EventThreadContext *Wayland_CreateEventThread(SDL_VideoData *data, ಧ್ರುವ ವರ್ಣ *queue_name);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_DestroyEventThread(Wayland_EventThreadContext *context);
ಬಾಹ್ಯ ಶೂನ್ಯ *Wayland_CreateEventThreadProxyWrapper(Wayland_EventThreadContext *context, ಶೂನ್ಯ *obj);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_LockEventThread(Wayland_EventThreadContext *context);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_UnlockEventThread(Wayland_EventThreadContext *context);

ಬಾಹ್ಯ Wayland_JobThreadContext *Wayland_CreateJobThread();
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_DestroyJobThread(Wayland_JobThreadContext *context);
ಬಾಹ್ಯ bool Wayland_JobThreadAddJob(Wayland_JobThreadContext *context, Wayland_JobThreadCallback callback, ಶೂನ್ಯ *userdata, Wayland_JobID *id);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_JobThreadCancelJob(Wayland_JobThreadContext *context, Wayland_JobID id);

#endif // SDL_waylandeventthread_h_

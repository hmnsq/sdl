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

#यदि_अपरिभाषितम् SDL_waylandeventthread_h_
#परिभाषय SDL_waylandeventthread_h_

#अन्तर्भाव "../SDL_sysvideo.h"

प्रकारनिर्देश संरचना Wayland_EventThreadContext Wayland_EventThreadContext;
प्रकारनिर्देश संरचना Wayland_JobThreadContext Wayland_JobThreadContext;
प्रकारनिर्देश शून्य (*Wayland_JobThreadCallback)(शून्य *userdata);
प्रकारनिर्देश Uint32 Wayland_JobID;

बाह्य Wayland_EventThreadContext *Wayland_CreateEventThread(SDL_Video_दत्त *दत्त, ध्रुव वर्ण *queue_name);
बाह्य शून्य Wayland_DestroyEventThread(Wayland_EventThreadContext *context);
बाह्य शून्य *Wayland_CreateEventThreadProxyWrapper(Wayland_EventThreadContext *context, शून्य *obj);
बाह्य शून्य Wayland_तालकम्_Event_Thread(Wayland_EventThreadContext *context);
बाह्य शून्य Wayland_UnlockEventThread(Wayland_EventThreadContext *context);

बाह्य Wayland_JobThreadContext *Wayland_CreateJobThread();
बाह्य शून्य Wayland_DestroyJobThread(Wayland_JobThreadContext *context);
बाह्य bool Wayland_Job_Thread_सङ्कलय_Job(Wayland_JobThreadContext *context, Wayland_JobThreadCallback callback, शून्य *userdata, Wayland_JobID *id);
बाह्य शून्य Wayland_JobThreadCancelJob(Wayland_JobThreadContext *context, Wayland_JobID id);

#यदि_अन्तः // SDL_waylandeventthread_h_

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

#अगर_अघोषित SDL_waylandeventthread_h_
#घोषणा SDL_waylandeventthread_h_

#समावेश "../SDL_sysvideo.h"

प्रकार काष्ठा Wayland_EventThreadContext Wayland_EventThreadContext;
प्रकार काष्ठा Wayland_JobThreadContext Wayland_JobThreadContext;
प्रकार व्योम (*Wayland_JobThreadCallback)(व्योम *userdata);
प्रकार Uint32 Wayland_JobID;

बाह्य Wayland_EventThreadContext *Wayland_CreateEventThread(SDL_Video_तथ्य *तथ्य, स्थिर अक्षर *queue_name);
बाह्य व्योम Wayland_DestroyEventThread(Wayland_EventThreadContext *context);
बाह्य व्योम *Wayland_CreateEventThreadProxyWrapper(Wayland_EventThreadContext *context, व्योम *obj);
बाह्य व्योम Wayland_LockEventThread(Wayland_EventThreadContext *context);
बाह्य व्योम Wayland_UnlockEventThread(Wayland_EventThreadContext *context);

बाह्य Wayland_JobThreadContext *Wayland_CreateJobThread();
बाह्य व्योम Wayland_DestroyJobThread(Wayland_JobThreadContext *context);
बाह्य bool Wayland_JobThreadAddJob(Wayland_JobThreadContext *context, Wayland_JobThreadCallback callback, व्योम *userdata, Wayland_JobID *id);
बाह्य व्योम Wayland_JobThreadCancelJob(Wayland_JobThreadContext *context, Wayland_JobID id);

#पूर्ण_अगर // SDL_waylandeventthread_h_

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

#ifndef SDL_waylandeventthread_h_
#define SDL_waylandeventthread_h_

#അന്തര്ഭാവ "../SDL_sysvideo.h"

തരനിർവചനം ഘടന Wayland_EventThreadContext Wayland_EventThreadContext;
തരനിർവചനം ഘടന Wayland_JobThreadContext Wayland_JobThreadContext;
തരനിർവചനം ശൂന്യം (*Wayland_JobThreadCallback)(ശൂന്യം *userdata);
തരനിർവചനം Uint32 Wayland_JobID;

ബാഹ്യ Wayland_EventThreadContext *Wayland_CreateEventThread(SDL_VideoData *data, സ്ഥിരം അക്ഷരം *queue_name);
ബാഹ്യ ശൂന്യം Wayland_DestroyEventThread(Wayland_EventThreadContext *context);
ബാഹ്യ ശൂന്യം *Wayland_CreateEventThreadProxyWrapper(Wayland_EventThreadContext *context, ശൂന്യം *obj);
ബാഹ്യ ശൂന്യം Wayland_LockEventThread(Wayland_EventThreadContext *context);
ബാഹ്യ ശൂന്യം Wayland_UnlockEventThread(Wayland_EventThreadContext *context);

ബാഹ്യ Wayland_JobThreadContext *Wayland_CreateJobThread();
ബാഹ്യ ശൂന്യം Wayland_DestroyJobThread(Wayland_JobThreadContext *context);
ബാഹ്യ bool Wayland_JobThreadAddJob(Wayland_JobThreadContext *context, Wayland_JobThreadCallback callback, ശൂന്യം *userdata, Wayland_JobID *id);
ബാഹ്യ ശൂന്യം Wayland_JobThreadCancelJob(Wayland_JobThreadContext *context, Wayland_JobID id);

#endif // SDL_waylandeventthread_h_

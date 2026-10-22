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
#అన్తర్భావ "SDL_internal.h"

#నిర్వచితం_కాకపోతే SDL_waylandeventthread_h_
#నిర్వచించు SDL_waylandeventthread_h_

#అన్తర్భావ "../SDL_sysvideo.h"

రకనిర్వచనం నిర్మాణం Wayland_EventThreadContext Wayland_EventThreadContext;
రకనిర్వచనం నిర్మాణం Wayland_పని_Thread_Context Wayland_పని_Thread_Context;
రకనిర్వచనం శూన్య (*Wayland_పని_Thread_Callback)(శూన్య *userdata);
రకనిర్వచనం Uint32 Wayland_పని_ID;

బాహ్య Wayland_EventThreadContext *Wayland_CreateEventThread(SDL_Video_దత్తాంశం *దత్తాంశం, స్థిరరాశి అక్షరం *వరుస_name);
బాహ్య శూన్య Wayland_DestroyEventThread(Wayland_EventThreadContext *context);
బాహ్య శూన్య *Wayland_CreateEventThreadProxyWrapper(Wayland_EventThreadContext *context, శూన్య *obj);
బాహ్య శూన్య Wayland_తాళం_Event_Thread(Wayland_EventThreadContext *context);
బాహ్య శూన్య Wayland_UnlockEventThread(Wayland_EventThreadContext *context);

బాహ్య Wayland_పని_Thread_Context *Wayland_Create_పని_Thread();
బాహ్య శూన్య Wayland_Destroy_పని_Thread(Wayland_పని_Thread_Context *context);
బాహ్య bool Wayland_పని_Thread_కూడు_పని(Wayland_పని_Thread_Context *context, Wayland_పని_Thread_Callback callback, శూన్య *userdata, Wayland_పని_ID *id);
బాహ్య శూన్య Wayland_పని_Thread_Cancel_పని(Wayland_పని_Thread_Context *context, Wayland_పని_ID id);

#అయితే_ముగింపు // SDL_waylandeventthread_h_

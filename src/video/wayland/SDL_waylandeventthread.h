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
#ضمن "SDL_internal.h"

#اگر_تعریف_نشده SDL_waylandeventthread_h_
#تعریف_کن SDL_waylandeventthread_h_

#ضمن "../SDL_sysvideo.h"

تعريفنوع بنية Wayland_EventThreadContext Wayland_EventThreadContext;
تعريفنوع بنية Wayland_کار_Thread_Context Wayland_کار_Thread_Context;
تعريفنوع فراغ (*Wayland_کار_Thread_Callback)(فراغ *userdata);
تعريفنوع Uint32 Wayland_کار_ID;

خارجي Wayland_EventThreadContext *Wayland_CreateEventThread(SDL_Video_داده *داده, ثابت حرف *صف_name);
خارجي فراغ Wayland_DestroyEventThread(Wayland_EventThreadContext *context);
خارجي فراغ *Wayland_CreateEventThreadProxyWrapper(Wayland_EventThreadContext *context, فراغ *obj);
خارجي فراغ Wayland_قفل_Event_Thread(Wayland_EventThreadContext *context);
خارجي فراغ Wayland_UnlockEventThread(Wayland_EventThreadContext *context);

خارجي Wayland_کار_Thread_Context *Wayland_Create_کار_Thread();
خارجي فراغ Wayland_Destroy_کار_Thread(Wayland_کار_Thread_Context *context);
خارجي bool Wayland_کار_Thread_جمع_کن_کار(Wayland_کار_Thread_Context *context, Wayland_کار_Thread_Callback callback, فراغ *userdata, Wayland_کار_ID *id);
خارجي فراغ Wayland_کار_Thread_Cancel_کار(Wayland_کار_Thread_Context *context, Wayland_کار_ID id);

#پایان_اگر // SDL_waylandeventthread_h_

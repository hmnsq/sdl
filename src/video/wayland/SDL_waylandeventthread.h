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

#که_نه_تعریف_شوی SDL_waylandeventthread_h_
#تعریف_کړه SDL_waylandeventthread_h_

#ضمن "../SDL_sysvideo.h"

تعريفنوع بنية Wayland_EventThreadContext Wayland_EventThreadContext;
تعريفنوع بنية Wayland_دنده_Thread_Context Wayland_دنده_Thread_Context;
تعريفنوع فراغ (*Wayland_دنده_Thread_Callback)(فراغ *userdata);
تعريفنوع Uint32 Wayland_دنده_ID;

خارجي Wayland_EventThreadContext *Wayland_CreateEventThread(SDL_Video_معلومات *معلومات, ثابت حرف *کتار_name);
خارجي فراغ Wayland_DestroyEventThread(Wayland_EventThreadContext *context);
خارجي فراغ *Wayland_CreateEventThreadProxyWrapper(Wayland_EventThreadContext *context, فراغ *obj);
خارجي فراغ Wayland_قلف_Event_Thread(Wayland_EventThreadContext *context);
خارجي فراغ Wayland_UnlockEventThread(Wayland_EventThreadContext *context);

خارجي Wayland_دنده_Thread_Context *Wayland_Create_دنده_Thread();
خارجي فراغ Wayland_Destroy_دنده_Thread(Wayland_دنده_Thread_Context *context);
خارجي bool Wayland_دنده_Thread_جمع_کړه_دنده(Wayland_دنده_Thread_Context *context, Wayland_دنده_Thread_Callback callback, فراغ *userdata, Wayland_دنده_ID *id);
خارجي فراغ Wayland_دنده_Thread_Cancel_دنده(Wayland_دنده_Thread_Context *context, Wayland_دنده_ID id);

#د_که_پای // SDL_waylandeventthread_h_

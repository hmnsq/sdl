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
#شامل "SDL_internal.h"

#اگر_غیر_تعریف_شدہ SDL_waylandeventthread_h_
#تعریف_کرو SDL_waylandeventthread_h_

#شامل "../SDL_sysvideo.h"

قسمتعریف ساخت Wayland_EventThreadContext Wayland_EventThreadContext;
قسمتعریف ساخت Wayland_کام_Thread_Context Wayland_کام_Thread_Context;
قسمتعریف خالی (*Wayland_کام_Thread_Callback)(خالی *userdata);
قسمتعریف Uint32 Wayland_کام_ID;

خارجی Wayland_EventThreadContext *Wayland_CreateEventThread(SDL_Video_ڈیٹا *ڈیٹا, ثابت حرف *قطار_name);
خارجی خالی Wayland_DestroyEventThread(Wayland_EventThreadContext *context);
خارجی خالی *Wayland_CreateEventThreadProxyWrapper(Wayland_EventThreadContext *context, خالی *obj);
خارجی خالی Wayland_تالا_Event_Thread(Wayland_EventThreadContext *context);
خارجی خالی Wayland_UnlockEventThread(Wayland_EventThreadContext *context);

خارجی Wayland_کام_Thread_Context *Wayland_Create_کام_Thread();
خارجی خالی Wayland_Destroy_کام_Thread(Wayland_کام_Thread_Context *context);
خارجی bool Wayland_کام_Thread_جوڑو_کام(Wayland_کام_Thread_Context *context, Wayland_کام_Thread_Callback callback, خالی *userdata, Wayland_کام_ID *id);
خارجی خالی Wayland_کام_Thread_Cancel_کام(Wayland_کام_Thread_Context *context, Wayland_کام_ID id);

#اگر_ختم // SDL_waylandeventthread_h_

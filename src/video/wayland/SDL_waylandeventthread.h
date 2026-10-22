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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_waylandeventthread_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_waylandeventthread_h_

#ਅਨ੍ਤਰ੍ਭਾਵ "../SDL_sysvideo.h"

ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Wayland_EventThreadContext Wayland_EventThreadContext;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਬਣਤਰ Wayland_ਕੰਮ_Thread_Context Wayland_ਕੰਮ_Thread_Context;
ਕਿਸਮਪਰਿਭਾਸ਼ਾ ਖਾਲੀ (*Wayland_ਕੰਮ_Thread_Callback)(ਖਾਲੀ *userdata);
ਕਿਸਮਪਰਿਭਾਸ਼ਾ Uint32 Wayland_ਕੰਮ_ID;

ਬਾਹਰੀ Wayland_EventThreadContext *Wayland_CreateEventThread(SDL_Video_ਅੰਕੜੇ *ਅੰਕੜੇ, ਅਚਲ ਅੱਖਰ *ਕਤਾਰ_name);
ਬਾਹਰੀ ਖਾਲੀ Wayland_DestroyEventThread(Wayland_EventThreadContext *context);
ਬਾਹਰੀ ਖਾਲੀ *Wayland_CreateEventThreadProxyWrapper(Wayland_EventThreadContext *context, ਖਾਲੀ *obj);
ਬਾਹਰੀ ਖਾਲੀ Wayland_ਤਾਲਾ_Event_Thread(Wayland_EventThreadContext *context);
ਬਾਹਰੀ ਖਾਲੀ Wayland_UnlockEventThread(Wayland_EventThreadContext *context);

ਬਾਹਰੀ Wayland_ਕੰਮ_Thread_Context *Wayland_Create_ਕੰਮ_Thread();
ਬਾਹਰੀ ਖਾਲੀ Wayland_Destroy_ਕੰਮ_Thread(Wayland_ਕੰਮ_Thread_Context *context);
ਬਾਹਰੀ bool Wayland_ਕੰਮ_Thread_ਜੋੜੋ_ਕੰਮ(Wayland_ਕੰਮ_Thread_Context *context, Wayland_ਕੰਮ_Thread_Callback callback, ਖਾਲੀ *userdata, Wayland_ਕੰਮ_ID *id);
ਬਾਹਰੀ ਖਾਲੀ Wayland_ਕੰਮ_Thread_Cancel_ਕੰਮ(Wayland_ਕੰਮ_Thread_Context *context, Wayland_ਕੰਮ_ID id);

#ਜੇ_ਅੰਤ // SDL_waylandeventthread_h_

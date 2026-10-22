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

#ವ್ಯಾಖ್ಯಾನಿತವಾಗದಿದ್ದರೆ SDL_waylandeventthread_h_
#ವ್ಯಾಖ್ಯಾನಿಸು SDL_waylandeventthread_h_

#ಅನ್ತರ್ಭಾವ "../SDL_sysvideo.h"

ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Wayland_EventThreadContext Wayland_EventThreadContext;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ರಚನೆ Wayland_ಕೆಲಸ_Thread_Context Wayland_ಕೆಲಸ_Thread_Context;
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ ಶೂನ್ಯ (*Wayland_ಕೆಲಸ_Thread_Callback)(ಶೂನ್ಯ *userdata);
ಪ್ರಕಾರವ್ಯಾಖ್ಯೆ Uint32 Wayland_ಕೆಲಸ_ID;

ಬಾಹ್ಯ Wayland_EventThreadContext *Wayland_CreateEventThread(SDL_Video_ದತ್ತಾಂಶ *ದತ್ತಾಂಶ, ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಸರತಿ_name);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_DestroyEventThread(Wayland_EventThreadContext *context);
ಬಾಹ್ಯ ಶೂನ್ಯ *Wayland_CreateEventThreadProxyWrapper(Wayland_EventThreadContext *context, ಶೂನ್ಯ *obj);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_ಬೀಗ_Event_Thread(Wayland_EventThreadContext *context);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_UnlockEventThread(Wayland_EventThreadContext *context);

ಬಾಹ್ಯ Wayland_ಕೆಲಸ_Thread_Context *Wayland_Create_ಕೆಲಸ_Thread();
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_Destroy_ಕೆಲಸ_Thread(Wayland_ಕೆಲಸ_Thread_Context *context);
ಬಾಹ್ಯ bool Wayland_ಕೆಲಸ_Thread_ಕೂಡಿಸು_ಕೆಲಸ(Wayland_ಕೆಲಸ_Thread_Context *context, Wayland_ಕೆಲಸ_Thread_Callback callback, ಶೂನ್ಯ *userdata, Wayland_ಕೆಲಸ_ID *id);
ಬಾಹ್ಯ ಶೂನ್ಯ Wayland_ಕೆಲಸ_Thread_Cancel_ಕೆಲಸ(Wayland_ಕೆಲಸ_Thread_Context *context, Wayland_ಕೆಲಸ_ID id);

#ಆದರೆ_ಅಂತ್ಯ // SDL_waylandeventthread_h_

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

#నిర్వచితం_కాకపోతే SDL_BWINDOW_H
#నిర్వచించు SDL_BWINDOW_H

#అన్తర్భావ "../SDL_sysvideo.h"

బాహ్య bool HAIKU_Create_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID create_props);
బాహ్య శూన్య HAIKU_సమితి_కిటికీ_Title(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool HAIKU_సమితి_కిటికీ_Position(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య HAIKU_సమితి_కిటికీ_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య HAIKU_సమితి_కిటికీ_Minimum_కొలత(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య HAIKU_Show_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య HAIKU_Hide_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య HAIKU_Raise_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య HAIKU_Maximize_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య HAIKU_Minimize_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య HAIKU_Restore_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య HAIKU_సమితి_కిటికీ_Bordered(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool bordered);
బాహ్య శూన్య HAIKU_సమితి_కిటికీ_Resizable(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool resizable);
బాహ్య SDL_Fullscreen_ఫలితం HAIKU_సమితి_కిటికీ_Fullscreen(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
బాహ్య bool HAIKU_సమితి_కిటికీ_Mouse_Grab(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool grabbed);
బాహ్య bool HAIKU_సమితి_కిటికీ_మాతృ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_కిటికీ *మాతృ);
బాహ్య bool HAIKU_సమితి_కిటికీ_Modal(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, bool modal);
బాహ్య శూన్య HAIKU_Destroy_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);

#అయితే_ముగింపు

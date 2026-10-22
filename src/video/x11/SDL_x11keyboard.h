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

#నిర్వచితం_కాకపోతే SDL_x11keyboard_h_
#నిర్వచించు SDL_x11keyboard_h_

బాహ్య bool X11_InitKeyboard(SDL_VideoDevice *_this);
బాహ్య శూన్య X11_UpdateKeymap(SDL_VideoDevice *_this, bool send_event);
బాహ్య శూన్య X11_QuitKeyboard(SDL_VideoDevice *_this);
బాహ్య శూన్య X11_Create_ఆదానం_Context(SDL_కిటికీ_దత్తాంశం *దత్తాంశం);
బాహ్య శూన్య X11_Destroy_ఆదానం_Context(SDL_కిటికీ_దత్తాంశం *దత్తాంశం);
బాహ్య శూన్య X11_ClearComposition(SDL_కిటికీ_దత్తాంశం *దత్తాంశం);
బాహ్య bool X11_ప్రారంభం_పాఠ్యం_ఆదానం(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID props);
బాహ్య bool X11_Stop_పాఠ్యం_ఆదానం(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool X11_Update_పాఠ్యం_ఆదానం_Area(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool X11_HasScreenKeyboardSupport(SDL_VideoDevice *_this);
బాహ్య శూన్య X11_ShowScreenKeyboard(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_PropertiesID props);
బాహ్య శూన్య X11_HideScreenKeyboard(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);

#అయితే_ముగింపు // SDL_x11keyboard_h_

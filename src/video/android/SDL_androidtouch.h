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
#अन्तर्भाव "SDL_internal.h"

#अन्तर्भाव "SDL_androidvideo.h"

बाह्य शून्य Android_InitTouch(शून्य);
बाह्य शून्य Android_QuitTouch(शून्य);
बाह्य शून्य Android_OnTouch(SDL_Window *window, पूर्णांक touch_device_id_in, पूर्णांक pointer_finger_id_in, पूर्णांक action, दशांश x, दशांश y, दशांश p);
बाह्य SDL_TouchID Android_ConvertJavaTouchID(पूर्णांक touchID);

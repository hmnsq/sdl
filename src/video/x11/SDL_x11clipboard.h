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

#اگر_غیر_تعریف_شدہ SDL_x11clipboard_h_
#تعریف_کرو SDL_x11clipboard_h_

#شامل <X11/Xlib.h>

قسمتعریف ساخت X11_Clipboard_ڈیٹا {
    SDL_Clipboard_ڈیٹا_Callback callback;
    خالی *userdata;
    ثابت حرف *ثابت *mime_types;
    size_t mime_گنتی;
    Uint32 sequence;
} SDLX11_Clipboard_ڈیٹا;

خارجی ثابت حرف *ثابت *X11_Get_متن_Mime_Types(SDL_VideoDevice *_this, size_t *عدد_mime_types);
خارجی bool X11_سیٹ_Clipboard_ڈیٹا(SDL_VideoDevice *_this);
خارجی خالی *X11_Get_Clipboard_ڈیٹا(SDL_VideoDevice *_this, ثابت حرف *mime_type, size_t *لمبائی);
خارجی bool X11_Has_Clipboard_ڈیٹا(SDL_VideoDevice *_this, ثابت حرف *mime_type);
خارجی bool X11_سیٹ_Primary_Selection_متن(SDL_VideoDevice *_this, ثابت حرف *متن);
خارجی حرف *X11_Get_Primary_Selection_متن(SDL_VideoDevice *_this);
خارجی bool X11_Has_Primary_Selection_متن(SDL_VideoDevice *_this);
خارجی خالی X11_QuitClipboard(SDL_VideoDevice *_this);
کھڑکی_2 Get_کھڑکی(SDL_VideoDevice *_this);

#اگر_ختم // SDL_x11clipboard_h_

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
#समावेश "SDL_internal.h"

#अगर_अघोषित SDL_x11clipboard_h_
#घोषणा SDL_x11clipboard_h_

#समावेश <X11/Xlib.h>

प्रकार काष्ठा X11_Clipboard_तथ्य {
    SDL_Clipboard_तथ्य_Callback callback;
    व्योम *userdata;
    स्थिर अक्षर *स्थिर *mime_types;
    माप_प्रकार mime_गिनती;
    Uint32 sequence;
} SDLX11_Clipboard_तथ्य;

बाह्य स्थिर अक्षर *स्थिर *X11_GetTextMimeTypes(SDL_VideoDevice *_this, माप_प्रकार *अंक_mime_types);
बाह्य bool X11_Set_Clipboard_तथ्य(SDL_VideoDevice *_this);
बाह्य व्योम *X11_Get_Clipboard_तथ्य(SDL_VideoDevice *_this, स्थिर अक्षर *mime_type, माप_प्रकार *लंबाई);
बाह्य bool X11_Has_Clipboard_तथ्य(SDL_VideoDevice *_this, स्थिर अक्षर *mime_type);
बाह्य bool X11_SetPrimarySelectionText(SDL_VideoDevice *_this, स्थिर अक्षर *text);
बाह्य अक्षर *X11_GetPrimarySelectionText(SDL_VideoDevice *_this);
बाह्य bool X11_HasPrimarySelectionText(SDL_VideoDevice *_this);
बाह्य व्योम X11_QuitClipboard(SDL_VideoDevice *_this);
Window GetWindow(SDL_VideoDevice *_this);

#पूर्ण_अगर // SDL_x11clipboard_h_

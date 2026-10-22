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

#यदि_अपरिभाषितम् SDL_BWINDOW_H
#परिभाषय SDL_BWINDOW_H

#अन्तर्भाव "../SDL_sysvideo.h"

बाह्य bool HAIKU_Create_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_PropertiesID create_props);
बाह्य शून्य HAIKU_समुच्चयः_गवाक्षः_Title(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool HAIKU_समुच्चयः_गवाक्षः_Position(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य HAIKU_समुच्चयः_गवाक्षः_आकार(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य HAIKU_समुच्चयः_गवाक्षः_Minimum_आकार(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य HAIKU_Show_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य HAIKU_Hide_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य HAIKU_Raise_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य HAIKU_Maximize_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य HAIKU_Minimize_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य HAIKU_Restore_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य शून्य HAIKU_समुच्चयः_गवाक्षः_Bordered(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool bordered);
बाह्य शून्य HAIKU_समुच्चयः_गवाक्षः_Resizable(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool resizable);
बाह्य SDL_Fullscreen_परिणाम HAIKU_समुच्चयः_गवाक्षः_Fullscreen(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_VideoDisplay *display, SDL_FullscreenOp fullscreen);
बाह्य bool HAIKU_समुच्चयः_गवाक्षः_Mouse_Grab(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool grabbed);
बाह्य bool HAIKU_समुच्चयः_गवाक्षः_Parent(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_गवाक्षः *parent);
बाह्य bool HAIKU_समुच्चयः_गवाक्षः_Modal(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, bool modal);
बाह्य शून्य HAIKU_Destroy_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);

#यदि_अन्तः

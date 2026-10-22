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

#اگر_غیر_تعریف_شدہ SDL_windowsclipboard_h_
#تعریف_کرو SDL_windowsclipboard_h_

// Forward declaration
ساخت SDL_Video_ڈیٹا;

خارجی bool WIN_سیٹ_Clipboard_ڈیٹا(SDL_VideoDevice *_this);
خارجی خالی *WIN_Get_Clipboard_ڈیٹا(SDL_VideoDevice *_this, ثابت حرف *mime_type, size_t *سائز);
خارجی bool WIN_Has_Clipboard_ڈیٹا(SDL_VideoDevice *_this, ثابت حرف *mime_type);
خارجی خالی WIN_CheckClipboardUpdate(ساخت SDL_Video_ڈیٹا *ڈیٹا);

#اگر_ختم // SDL_windowsclipboard_h_

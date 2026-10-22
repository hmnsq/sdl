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

#अगर_अघोषित SDL_ps2video_h_
#घोषणा SDL_ps2video_h_

#समावेश "../SDL_sysvideo.h"

#समावेश <kernel.h>

#समावेश <gsKit.h>
#समावेश <dmaKit.h>

#समावेश <gsToolkit.h>

#अगर_घोषित HAVE_GCC_DIAGNOSTIC_PRAGMA
#आशय GCC diagnostic धकेलो
#आशय GCC diagnostic ignored "-Wdeclaration-after-statement"
#पूर्ण_अगर

#समावेश <gsInline.h>

#अगर_घोषित HAVE_GCC_DIAGNOSTIC_PRAGMA
#आशय GCC diagnostic निकालो
#पूर्ण_अगर

#पूर्ण_अगर // SDL_ps2video_h_

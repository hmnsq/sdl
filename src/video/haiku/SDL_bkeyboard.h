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

#నిర్వచితం_కాకపోతే SDL_BKEYBOARD_H
#నిర్వచించు SDL_BKEYBOARD_H

#అన్తర్భావ <SupportDefs.h>

#నిర్వచితమైతే __cplusplus
బాహ్య "C" {
#అయితే_ముగింపు

బాహ్య శూన్య HAIKU_InitOSKeymap(శూన్య);
బాహ్య SDL_Scancode HAIKU_Get_Scancode_From_Be_కీలకం(int32 bkey);

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు

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

#నిర్వచితం_కాకపోతే SDL_riscosdefs_h_
#నిర్వచించు SDL_riscosdefs_h_

రకనిర్వచనం నిర్మాణం sprite_area
{
    పూర్ణాంకం కొలత;  // +0
    పూర్ణాంకం లెక్క; // +4
    పూర్ణాంకం ప్రారంభం; // +8
    పూర్ణాంకం చివర;   // +12
} sprite_area;

SDL_COMPILE_సమయం_ASSERT(sprite_area, పరిమాణం(sprite_area) == 16);

రకనిర్వచనం నిర్మాణం sprite_శీర్షిక
{
    పూర్ణాంకం తదుపరి;         // +0
    అక్షరం name[12];    // +4
    పూర్ణాంకం వెడల్పు;        // +16
    పూర్ణాంకం ఎత్తు;       // +20
    పూర్ణాంకం మొదటి_బిట్టు;    // +24
    పూర్ణాంకం చివరి_బిట్టు;     // +28
    పూర్ణాంకం image_స్థానభ్రంశం_2; // +32
    పూర్ణాంకం ముసుగు_స్థానభ్రంశం;  // +36
    పూర్ణాంకం బహుళకం;         // +40
} sprite_శీర్షిక;

SDL_COMPILE_సమయం_ASSERT(sprite_శీర్షిక, పరిమాణం(sprite_శీర్షిక) == 44);

#అయితే_ముగింపు // SDL_riscosdefs_h_

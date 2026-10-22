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

#నిర్వచితం_కాకపోతే SDL_androidvideo_h_
#నిర్వచించు SDL_androidvideo_h_

#అన్తర్భావ "../SDL_sysvideo.h"

// Called by the JNI layer when the screen changes size or format
బాహ్య శూన్య Android_సమితి_Screen_Resolution(పూర్ణాంకం surface_వెడల్పు, పూర్ణాంకం surface_ఎత్తు, పూర్ణాంకం device_వెడల్పు, పూర్ణాంకం device_ఎత్తు, దశాంశం density, దశాంశం రేటు);
బాహ్య శూన్య Android_సమితి_Screen_HDRHeadroom(దశాంశం headroom);
బాహ్య శూన్య Android_సమితి_Format(పూర్ణాంకం format_wanted, పూర్ణాంకం format_got);
బాహ్య శూన్య Android_సమితి_Orientation(SDL_DisplayOrientation orientation);
బాహ్య శూన్య Android_SendResize(SDL_కిటికీ *కిటికీ);
బాహ్య శూన్య Android_సమితి_కిటికీ_సురక్షిత_Area_Insets(పూర్ణాంకం ఎడమ, పూర్ణాంకం కుడి, పూర్ణాంకం శిఖరం, పూర్ణాంకం bottom);
బాహ్య శూన్య Android_సమితి_Dark_బహుళకం(bool enabled);

// Private display data

నిర్మాణం SDL_Video_దత్తాంశం
{
    పూర్ణాంకం isPaused;
    పూర్ణాంకం isPausing;
};

బాహ్య పూర్ణాంకం Android_Surface_వెడల్పు;
బాహ్య పూర్ణాంకం Android_Surface_ఎత్తు;
బాహ్య దశాంశం Android_ScreenDensity;
బాహ్య పూర్ణాంకం Android_సురక్షిత_Inset_ఎడమ;
బాహ్య పూర్ణాంకం Android_సురక్షిత_Inset_కుడి;
బాహ్య పూర్ణాంకం Android_సురక్షిత_Inset_శిఖరం;
బాహ్య పూర్ణాంకం Android_సురక్షిత_Inset_Bottom;

#అయితే_ముగింపు // SDL_androidvideo_h_

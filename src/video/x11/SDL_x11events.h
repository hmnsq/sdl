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

#నిర్వచితం_కాకపోతే SDL_x11events_h_
#నిర్వచించు SDL_x11events_h_

బాహ్య శూన్య X11_PumpEvents(SDL_VideoDevice *_this);
బాహ్య పూర్ణాంకం X11_WaitEventTimeout(SDL_VideoDevice *_this, Sint64 timeoutNS);
బాహ్య శూన్య X11_SendWakeupEvent(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool X11_SuspendScreenSaver(SDL_VideoDevice *_this);
బాహ్య శూన్య X11_ReconcileKeyboardState(SDL_VideoDevice *_this);
బాహ్య శూన్య X11_Get_Border_విలువలు(SDL_కిటికీ_దత్తాంశం *దత్తాంశం);
బాహ్య Uint64 X11_GetEventTimestamp(గుర్తులేని దీర్ఘ సమయం);
బాహ్య శూన్య X11_Handle_కీలకం_Event(SDL_VideoDevice *_this, SDL_కిటికీ_దత్తాంశం *windowdata, SDL_KeyboardID keyboardID, XEvent *xevent);
బాహ్య శూన్య X11_HandleButtonPress(SDL_VideoDevice *_this, SDL_కిటికీ_దత్తాంశం *windowdata, SDL_MouseID mouseID, పూర్ణాంకం button, దశాంశం x, దశాంశం y, గుర్తులేని దీర్ఘ సమయం, గుర్తులేని దీర్ఘ serial);
బాహ్య శూన్య X11_HandleButtonRelease(SDL_VideoDevice *_this, SDL_కిటికీ_దత్తాంశం *windowdata, SDL_MouseID mouseID, పూర్ణాంకం button, గుర్తులేని దీర్ఘ సమయం);
బాహ్య SDL_కిటికీ_దత్తాంశం *X11_కనుగొను_కిటికీ(SDL_Video_దత్తాంశం *videodata, కిటికీ_2 కిటికీ);
బాహ్య bool X11_Process_తగిలింది_Test(SDL_VideoDevice *_this, SDL_కిటికీ_దత్తాంశం *దత్తాంశం, స్థిరరాశి దశాంశం x, స్థిరరాశి దశాంశం y, bool force_new_ఫలితం);
బాహ్య bool X11_Trigger_తగిలింది_Test_Action(SDL_VideoDevice *_this, SDL_కిటికీ_దత్తాంశం *దత్తాంశం, స్థిరరాశి దశాంశం x, స్థిరరాశి దశాంశం y);
బాహ్య bool X11_IsWheelEvent(పూర్ణాంకం button, పూర్ణాంకం *xticks, పూర్ణాంకం *yticks);

#అయితే_ముగింపు // SDL_x11events_h_

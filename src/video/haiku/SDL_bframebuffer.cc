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

#నిర్వచితమైతే SDL_VIDEO_DRIVER_HAIKU

#అన్తర్భావ "SDL_bframebuffer.h"

#అన్తర్భావ <AppKit.h>
#అన్తర్భావ <InterfaceKit.h>
#అన్తర్భావ "SDL_bmodes.h"
#అన్తర్భావ "SDL_BWin.h"

#అన్తర్భావ "../../core/haiku/SDL_BApp.h"

#నిర్వచితమైతే __cplusplus
బాహ్య "C" {
#అయితే_ముగింపు

స్థిర SDL_INLINE SDL_BWin *గమ్యం_Be_Win(SDL_కిటికీ *కిటికీ)
{
    తిరిగి (SDL_BWin *)(కిటికీ->అంతర్గత);
}

స్థిర SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    తిరిగి SDL_Looper;
}

తార్కిక HAIKU_Create_కిటికీ_Framebuffer(SDL_VideoDevice *_this, SDL_కిటికీ * కిటికీ, SDL_PixelFormat * format, శూన్య ** pixels, పూర్ణాంకం *pitch)
{
    SDL_BWin *bwin = గమ్యం_Be_Win(కిటికీ);
    BScreen bscreen;
    ఒకవేళ (!bscreen.IsValid()) {
        తిరిగి అబద్ధం;
    }

    // Make sure we have exclusive access to frame buffer data
    bwin->తాళం_బఫరు();

    bwin->CreateView();

    // format
    display_బహుళకం_2 bmode;
    bscreen.Get_బహుళకం(&bmode);
    *format = HAIKU_Color_Space_గమ్యం_SDLPx_Format(bmode.space);

    // Create the new bitmap object
    BBitmap *bitmap = bwin->GetBitmap();

    ఒకవేళ (bitmap) {
        తొలగించు bitmap;
    }
    bitmap = కొత్త BBitmap(bwin->Bounds(), (color_space)bmode.space,
            అబద్ధం,    // Views not accepted
            నిజం);    // Contiguous memory required

    ఒకవేళ (bitmap->InitCheck() != B_OK) {
        తొలగించు bitmap;
        తిరిగి SDL_సమితి_Error("Could not initialize back buffer!");
    }


    bwin->సమితి_Bitmap(bitmap);

    // Set the pixel pointer
    *pixels = bitmap->బిట్లు_2();

    // pitch = width of window, in bytes
    *pitch = bitmap->బైట్లు_చొప్పున_అడ్డువరుస();

    bwin->Unlock_బఫరు();
    తిరిగి నిజం;
}



తార్కిక HAIKU_Update_కిటికీ_Framebuffer(SDL_VideoDevice *_this, SDL_కిటికీ * కిటికీ,
                                      స్థిరరాశి SDL_Rect * rects, పూర్ణాంకం numrects) {
    ఒకవేళ (!కిటికీ) {
        తిరిగి నిజం;
    }

    SDL_BWin *bwin = గమ్యం_Be_Win(కిటికీ);

    bwin->Post_సందేశం(BWIN_UPDATE_FRAMEBUFFER);

    తిరిగి నిజం;
}

శూన్య HAIKU_Destroy_కిటికీ_Framebuffer(SDL_VideoDevice *_this, SDL_కిటికీ * కిటికీ) {
    SDL_BWin *bwin = గమ్యం_Be_Win(కిటికీ);

    bwin->తాళం_బఫరు();

    // Free and clear the window buffer
    BBitmap *bitmap = bwin->GetBitmap();
    తొలగించు bitmap;
    bwin->సమితి_Bitmap(ఖాళీ);

    bwin->RemoveView();

    bwin->Unlock_బఫరు();
}

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_HAIKU

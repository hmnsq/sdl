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
#अन्तर्भाव "SDL_internal.h"

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_HAIKU

#अन्तर्भाव "SDL_bframebuffer.h"

#अन्तर्भाव <AppKit.h>
#अन्तर्भाव <InterfaceKit.h>
#अन्तर्भाव "SDL_bmodes.h"
#अन्तर्भाव "SDL_BWin.h"

#अन्तर्भाव "../../core/haiku/SDL_BApp.h"

#यदि_परिभाषितम् __cplusplus
बाह्य "C" {
#यदि_अन्तः

स्थिर SDL_INLINE SDL_BWin *गन्तव्यम्_Be_Win(SDL_गवाक्षः *गवाक्षः)
{
    प्रत्यागम (SDL_BWin *)(गवाक्षः->आन्तरिकम्);
}

स्थिर SDL_INLINE SDL_BLooper *_GetBeLooper()
{
    प्रत्यागम SDL_Looper;
}

तार्किक HAIKU_Create_गवाक्षः_Framebuffer(SDL_VideoDevice *_this, SDL_गवाक्षः * गवाक्षः, SDL_PixelFormat * format, शून्य ** pixels, पूर्णाङ्क *pitch)
{
    SDL_BWin *bwin = गन्तव्यम्_Be_Win(गवाक्षः);
    BScreen bscreen;
    यदि (!bscreen.IsValid()) {
        प्रत्यागम असत्य;
    }

    // Make sure we have exclusive access to frame buffer data
    bwin->तालकम्_बफर();

    bwin->CreateView();

    // format
    display_बहुलकम्_2 bmode;
    bscreen.Get_बहुलकम्(&bmode);
    *format = HAIKU_Color_Space_गन्तव्यम्_SDLPx_Format(bmode.space);

    // Create the new bitmap object
    BBitmap *bitmap = bwin->GetBitmap();

    यदि (bitmap) {
        विलोपय bitmap;
    }
    bitmap = नूतन BBitmap(bwin->Bounds(), (color_space)bmode.space,
            असत्य,    // Views not accepted
            सत्य);    // Contiguous memory required

    यदि (bitmap->InitCheck() != B_OK) {
        विलोपय bitmap;
        प्रत्यागम SDL_समुच्चयः_Error("Could not initialize back buffer!");
    }


    bwin->समुच्चयः_Bitmap(bitmap);

    // Set the pixel pointer
    *pixels = bitmap->द्वयङ्काः_2();

    // pitch = width of window, in bytes
    *pitch = bitmap->अष्टकानि_प्रत्येकम्_Row();

    bwin->Unlock_बफर();
    प्रत्यागम सत्य;
}



तार्किक HAIKU_Update_गवाक्षः_Framebuffer(SDL_VideoDevice *_this, SDL_गवाक्षः * गवाक्षः,
                                      ध्रुव SDL_Rect * rects, पूर्णाङ्क numrects) {
    यदि (!गवाक्षः) {
        प्रत्यागम सत्य;
    }

    SDL_BWin *bwin = गन्तव्यम्_Be_Win(गवाक्षः);

    bwin->Post_सन्देशः(BWIN_UPDATE_FRAMEBUFFER);

    प्रत्यागम सत्य;
}

शून्य HAIKU_Destroy_गवाक्षः_Framebuffer(SDL_VideoDevice *_this, SDL_गवाक्षः * गवाक्षः) {
    SDL_BWin *bwin = गन्तव्यम्_Be_Win(गवाक्षः);

    bwin->तालकम्_बफर();

    // Free and clear the window buffer
    BBitmap *bitmap = bwin->GetBitmap();
    विलोपय bitmap;
    bwin->समुच्चयः_Bitmap(रिक्त);

    bwin->RemoveView();

    bwin->Unlock_बफर();
}

#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः // SDL_VIDEO_DRIVER_HAIKU

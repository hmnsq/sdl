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

#यदि_अपरिभाषितम् SDL_cocoaopengl_h_
#परिभाषय SDL_cocoaopengl_h_

#यदि_परिभाषितम् SDL_VIDEO_OPENGL_CGL

#import <Cocoa/Cocoa.h>
#import <QuartzCore/CVDisplayLink.h>

// We still support OpenGL as long as Apple offers it, deprecated or not, so disable deprecation warnings about it.
#यदि_परिभाषितम् __clang__
#निर्देशः clang diagnostic प्रक्षिप
#निर्देशः clang diagnostic ignored "-Wdeprecated-declarations"
#यदि_अन्तः

संरचना SDL_GLDriver_दत्त
{
    पूर्णाङ्क initialized;
};

@interface SDL3OpenGLContext : NSOpenGLContext
{
    SDL_AtomicInt dirty;
    SDL_गवाक्षः *गवाक्षः;
    CVDisplayLinkRef displayLink;
  @सार्वजनिक
    SDL_Mutex *swapIntervalMutex;
  @सार्वजनिक
    SDL_Condition *swapIntervalCond;
  @सार्वजनिक
    SDL_AtomicInt swapIntervalSetting;
  @सार्वजनिक
    SDL_AtomicInt swapIntervalsPassed;
}

- (id)initWithFormat:(NSOpenGLPixelFormat *)format
        shareContext:(NSOpenGLContext *)share;
- (शून्य)कालसारणी_Update;
- (शून्य)updateIfNeeded;
- (शून्य)moved_गन्तव्यम्_New_Screen;
- (शून्य)समुच्चयः_गवाक्षः:(SDL_गवाक्षः *)गवाक्षः;
- (SDL_गवाक्षः *)गवाक्षः;
- (शून्य)explicitUpdate;
- (शून्य)cleanup;

@property(retain, nonatomic) NSOpenGLPixelFormat *openglPixelFormat; // macOS 10.10 has -[NSOpenGLContext pixelFormat] but this handles older OS releases.

@अन्तः

// OpenGL functions
बाह्य bool Cocoa_GL_आरोपय_Library(SDL_VideoDevice *_this, ध्रुव वर्ण *मार्गः);
बाह्य SDL_FunctionPointer Cocoa_GL_Get_Proc_स्थानाङ्कः(SDL_VideoDevice *_this, ध्रुव वर्ण *proc);
बाह्य शून्य Cocoa_GL_UnloadLibrary(SDL_VideoDevice *_this);
बाह्य SDL_GLContext Cocoa_GL_CreateContext(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool Cocoa_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः, SDL_GLContext context);
बाह्य bool Cocoa_GL_समुच्चयः_Swap_Interval(SDL_VideoDevice *_this, पूर्णाङ्क interval);
बाह्य bool Cocoa_GL_GetSwapInterval(SDL_VideoDevice *_this, पूर्णाङ्क *interval);
बाह्य bool Cocoa_GL_Swap_गवाक्षः(SDL_VideoDevice *_this, SDL_गवाक्षः *गवाक्षः);
बाह्य bool Cocoa_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

#यदि_परिभाषितम् __clang__
#निर्देशः clang diagnostic निष्कासय
#यदि_अन्तः

#यदि_अन्तः // SDL_VIDEO_OPENGL_CGL

#यदि_अन्तः // SDL_cocoaopengl_h_

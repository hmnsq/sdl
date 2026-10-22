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
#ಅನ್ತರ್ಭಾವ "SDL_internal.h"

#ifndef SDL_cocoaopengl_h_
#define SDL_cocoaopengl_h_

#ifdef SDL_VIDEO_OPENGL_CGL

#import <Cocoa/Cocoa.h>
#import <QuartzCore/CVDisplayLink.h>

// We still support OpenGL as long as Apple offers it, deprecated or not, so disable deprecation warnings about it.
#ifdef __clang__
#pragma clang diagnostic ತಳ್ಳು
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif

ಸಂರಚನಾ SDL_GLDriverData
{
    ಪೂರ್ಣಾಙ್ಕ initialized;
};

@interface SDL3OpenGLContext : NSOpenGLContext
{
    SDL_AtomicInt dirty;
    SDL_Window *window;
    CVDisplayLinkRef displayLink;
  @ಸಾರ್ವಜನಿಕ
    SDL_Mutex *swapIntervalMutex;
  @ಸಾರ್ವಜನಿಕ
    SDL_Condition *swapIntervalCond;
  @ಸಾರ್ವಜನಿಕ
    SDL_AtomicInt swapIntervalSetting;
  @ಸಾರ್ವಜನಿಕ
    SDL_AtomicInt swapIntervalsPassed;
}

- (id)initWithFormat:(NSOpenGLPixelFormat *)format
        shareContext:(NSOpenGLContext *)share;
- (ಶೂನ್ಯ)scheduleUpdate;
- (ಶೂನ್ಯ)updateIfNeeded;
- (ಶೂನ್ಯ)movedToNewScreen;
- (ಶೂನ್ಯ)setWindow:(SDL_Window *)window;
- (SDL_Window *)window;
- (ಶೂನ್ಯ)explicitUpdate;
- (ಶೂನ್ಯ)cleanup;

@property(retain, nonatomic) NSOpenGLPixelFormat *openglPixelFormat; // macOS 10.10 has -[NSOpenGLContext pixelFormat] but this handles older OS releases.

@end

// OpenGL functions
ಬಾಹ್ಯ bool Cocoa_GL_LoadLibrary(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *path);
ಬಾಹ್ಯ SDL_FunctionPointer Cocoa_GL_GetProcAddress(SDL_VideoDevice *_this, ಧ್ರುವ ವರ್ಣ *proc);
ಬಾಹ್ಯ ಶೂನ್ಯ Cocoa_GL_UnloadLibrary(SDL_VideoDevice *_this);
ಬಾಹ್ಯ SDL_GLContext Cocoa_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ bool Cocoa_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context);
ಬಾಹ್ಯ bool Cocoa_GL_SetSwapInterval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಙ್ಕ interval);
ಬಾಹ್ಯ bool Cocoa_GL_GetSwapInterval(SDL_VideoDevice *_this, ಪೂರ್ಣಾಙ್ಕ *interval);
ಬಾಹ್ಯ bool Cocoa_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
ಬಾಹ್ಯ bool Cocoa_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

#ifdef __clang__
#pragma clang diagnostic ತೆಗೆ
#endif

#endif // SDL_VIDEO_OPENGL_CGL

#endif // SDL_cocoaopengl_h_

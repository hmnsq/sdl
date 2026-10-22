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
#ضمن "SDL_internal.h"

#ifndef SDL_cocoaopengl_h_
#define SDL_cocoaopengl_h_

#ifdef SDL_VIDEO_OPENGL_CGL

#import <Cocoa/Cocoa.h>
#import <QuartzCore/CVDisplayLink.h>

// We still support OpenGL as long as Apple offers it, deprecated or not, so disable deprecation warnings about it.
#ifdef __clang__
#pragma clang diagnostic تولق
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif

بنية SDL_GLDriverData
{
    صحيح initialized;
};

@interface SDL3OpenGLContext : NSOpenGLContext
{
    SDL_AtomicInt dirty;
    SDL_Window *window;
    CVDisplayLinkRef displayLink;
  @عام
    SDL_Mutex *swapIntervalMutex;
  @عام
    SDL_Condition *swapIntervalCond;
  @عام
    SDL_AtomicInt swapIntervalSetting;
  @عام
    SDL_AtomicInt swapIntervalsPassed;
}

- (id)initWithFormat:(NSOpenGLPixelFormat *)format
        shareContext:(NSOpenGLContext *)share;
- (فراغ)scheduleUpdate;
- (فراغ)updateIfNeeded;
- (فراغ)movedToNewScreen;
- (فراغ)setWindow:(SDL_Window *)window;
- (SDL_Window *)window;
- (فراغ)explicitUpdate;
- (فراغ)cleanup;

@property(retain, nonatomic) NSOpenGLPixelFormat *openglPixelFormat; // macOS 10.10 has -[NSOpenGLContext pixelFormat] but this handles older OS releases.

@end

// OpenGL functions
خارجي bool Cocoa_GL_LoadLibrary(SDL_VideoDevice *_this, ثابت حرف *path);
خارجي SDL_FunctionPointer Cocoa_GL_GetProcAddress(SDL_VideoDevice *_this, ثابت حرف *proc);
خارجي فراغ Cocoa_GL_UnloadLibrary(SDL_VideoDevice *_this);
خارجي SDL_GLContext Cocoa_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
خارجي bool Cocoa_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context);
خارجي bool Cocoa_GL_SetSwapInterval(SDL_VideoDevice *_this, صحيح interval);
خارجي bool Cocoa_GL_GetSwapInterval(SDL_VideoDevice *_this, صحيح *interval);
خارجي bool Cocoa_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
خارجي bool Cocoa_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

#ifdef __clang__
#pragma clang diagnostic کلوار
#endif

#endif // SDL_VIDEO_OPENGL_CGL

#endif // SDL_cocoaopengl_h_

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

#अगर_अघोषित SDL_cocoaopengl_h_
#घोषणा SDL_cocoaopengl_h_

#अगर_घोषित SDL_VIDEO_OPENGL_CGL

#import <Cocoa/Cocoa.h>
#import <QuartzCore/CVDisplayLink.h>

// We still support OpenGL as long as Apple offers it, deprecated or not, so disable deprecation warnings about it.
#अगर_घोषित __clang__
#आशय clang diagnostic धकेलो
#आशय clang diagnostic ignored "-Wdeprecated-declarations"
#पूर्ण_अगर

काष्ठा SDL_GLDriver_तथ्य
{
    पूर्णांक initialized;
};

@interface SDL3OpenGLContext : NSOpenGLContext
{
    SDL_AtomicInt dirty;
    SDL_Window *window;
    CVDisplayLinkRef displayLink;
  @खुला
    SDL_Mutex *swapIntervalMutex;
  @खुला
    SDL_Condition *swapIntervalCond;
  @खुला
    SDL_AtomicInt swapIntervalSetting;
  @खुला
    SDL_AtomicInt swapIntervalsPassed;
}

- (id)initWithFormat:(NSOpenGLPixelFormat *)format
        shareContext:(NSOpenGLContext *)share;
- (व्योम)scheduleUpdate;
- (व्योम)updateIfNeeded;
- (व्योम)movedToNewScreen;
- (व्योम)setWindow:(SDL_Window *)window;
- (SDL_Window *)window;
- (व्योम)explicitUpdate;
- (व्योम)cleanup;

@property(retain, nonatomic) NSOpenGLPixelFormat *openglPixelFormat; // macOS 10.10 has -[NSOpenGLContext pixelFormat] but this handles older OS releases.

@end

// OpenGL functions
बाह्य bool Cocoa_GL_LoadLibrary(SDL_VideoDevice *_this, स्थिर अक्षर *path);
बाह्य SDL_FunctionPointer Cocoa_GL_GetProcAddress(SDL_VideoDevice *_this, स्थिर अक्षर *proc);
बाह्य व्योम Cocoa_GL_UnloadLibrary(SDL_VideoDevice *_this);
बाह्य SDL_GLContext Cocoa_GL_CreateContext(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool Cocoa_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_Window *window, SDL_GLContext context);
बाह्य bool Cocoa_GL_SetSwapInterval(SDL_VideoDevice *_this, पूर्णांक interval);
बाह्य bool Cocoa_GL_GetSwapInterval(SDL_VideoDevice *_this, पूर्णांक *interval);
बाह्य bool Cocoa_GL_SwapWindow(SDL_VideoDevice *_this, SDL_Window *window);
बाह्य bool Cocoa_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

#अगर_घोषित __clang__
#आशय clang diagnostic निकालो
#पूर्ण_अगर

#पूर्ण_अगर // SDL_VIDEO_OPENGL_CGL

#पूर्ण_अगर // SDL_cocoaopengl_h_

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
#ਅਨ੍ਤਰ੍ਭਾਵ "SDL_internal.h"

#ਜੇ_ਅਪਰਿਭਾਸ਼ਿਤ SDL_cocoaopengl_h_
#ਪਰਿਭਾਸ਼ਿਤ_ਕਰੋ SDL_cocoaopengl_h_

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ SDL_VIDEO_OPENGL_CGL

#import <Cocoa/Cocoa.h>
#import <QuartzCore/CVDisplayLink.h>

// We still support OpenGL as long as Apple offers it, deprecated or not, so disable deprecation warnings about it.
#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __clang__
#ਹਦਾਇਤ clang diagnostic ਧੱਕੋ
#ਹਦਾਇਤ clang diagnostic ignored "-Wdeprecated-declarations"
#ਜੇ_ਅੰਤ

ਬਣਤਰ SDL_GLDriver_ਅੰਕੜੇ
{
    ਪੂਰਨ initialized;
};

@interface SDL3OpenGLContext : NSOpenGLContext
{
    SDL_AtomicInt dirty;
    SDL_ਖਿੜਕੀ *ਖਿੜਕੀ;
    CVDisplayLinkRef displayLink;
  @ਜਨਤਕ
    SDL_Mutex *ਅਦਲਾ_ਬਦਲੀ_Interval_Mutex;
  @ਜਨਤਕ
    SDL_Condition *ਅਦਲਾ_ਬਦਲੀ_Interval_Cond;
  @ਜਨਤਕ
    SDL_AtomicInt ਅਦਲਾ_ਬਦਲੀ_Interval_Setting;
  @ਜਨਤਕ
    SDL_AtomicInt ਅਦਲਾ_ਬਦਲੀ_Intervals_Passed;
}

- (id)initWithFormat:(NSOpenGLPixelFormat *)format
        shareContext:(NSOpenGLContext *)share;
- (ਖਾਲੀ)ਸਮਾਂ_ਸਾਰਣੀ_Update;
- (ਖਾਲੀ)updateIfNeeded;
- (ਖਾਲੀ)moved_ਮੰਜ਼ਿਲ_New_Screen;
- (ਖਾਲੀ)ਸੈੱਟ_ਖਿੜਕੀ:(SDL_ਖਿੜਕੀ *)ਖਿੜਕੀ;
- (SDL_ਖਿੜਕੀ *)ਖਿੜਕੀ;
- (ਖਾਲੀ)explicitUpdate;
- (ਖਾਲੀ)cleanup;

@property(retain, nonatomic) NSOpenGLPixelFormat *openglPixelFormat; // macOS 10.10 has -[NSOpenGLContext pixelFormat] but this handles older OS releases.

@ਸਿਰਾ

// OpenGL functions
ਬਾਹਰੀ bool Cocoa_GL_ਲੱਦੋ_Library(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *ਰਸਤਾ);
ਬਾਹਰੀ SDL_Function_ਸੂਚਕ Cocoa_GL_Get_Proc_ਪਤਾ(SDL_VideoDevice *_this, ਅਚਲ ਅੱਖਰ *proc);
ਬਾਹਰੀ ਖਾਲੀ Cocoa_GL_UnloadLibrary(SDL_VideoDevice *_this);
ਬਾਹਰੀ SDL_GLContext Cocoa_GL_CreateContext(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool Cocoa_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ, SDL_GLContext context);
ਬਾਹਰੀ bool Cocoa_GL_ਸੈੱਟ_ਅਦਲਾ_ਬਦਲੀ_Interval(SDL_VideoDevice *_this, ਪੂਰਨ interval);
ਬਾਹਰੀ bool Cocoa_GL_Get_ਅਦਲਾ_ਬਦਲੀ_Interval(SDL_VideoDevice *_this, ਪੂਰਨ *interval);
ਬਾਹਰੀ bool Cocoa_GL_ਅਦਲਾ_ਬਦਲੀ_ਖਿੜਕੀ(SDL_VideoDevice *_this, SDL_ਖਿੜਕੀ *ਖਿੜਕੀ);
ਬਾਹਰੀ bool Cocoa_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

#ਜੇ_ਪਰਿਭਾਸ਼ਿਤ __clang__
#ਹਦਾਇਤ clang diagnostic ਕੱਢੋ
#ਜੇ_ਅੰਤ

#ਜੇ_ਅੰਤ // SDL_VIDEO_OPENGL_CGL

#ਜੇ_ਅੰਤ // SDL_cocoaopengl_h_

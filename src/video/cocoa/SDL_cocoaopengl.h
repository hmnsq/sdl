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

#నిర్వచితం_కాకపోతే SDL_cocoaopengl_h_
#నిర్వచించు SDL_cocoaopengl_h_

#నిర్వచితమైతే SDL_VIDEO_OPENGL_CGL

#import <Cocoa/Cocoa.h>
#import <QuartzCore/CVDisplayLink.h>

// We still support OpenGL as long as Apple offers it, deprecated or not, so disable deprecation warnings about it.
#నిర్వచితమైతే __clang__
#సూచన clang diagnostic నెట్టు
#సూచన clang diagnostic ignored "-Wdeprecated-declarations"
#అయితే_ముగింపు

నిర్మాణం SDL_GLDriver_దత్తాంశం
{
    పూర్ణాంకం initialized;
};

@interface SDL3OpenGLContext : NSOpenGLContext
{
    SDL_AtomicInt dirty;
    SDL_కిటికీ *కిటికీ;
    CVDisplayLinkRef displayLink;
  @బహిరంగ
    SDL_Mutex *మార్పిడి_Interval_Mutex;
  @బహిరంగ
    SDL_Condition *మార్పిడి_Interval_Cond;
  @బహిరంగ
    SDL_AtomicInt మార్పిడి_Interval_Setting;
  @బహిరంగ
    SDL_AtomicInt మార్పిడి_Intervals_Passed;
}

- (id)initWithFormat:(NSOpenGLPixelFormat *)format
        shareContext:(NSOpenGLContext *)share;
- (శూన్య)కాలపట్టిక_Update;
- (శూన్య)updateIfNeeded;
- (శూన్య)moved_గమ్యం_New_Screen;
- (శూన్య)సమితి_కిటికీ:(SDL_కిటికీ *)కిటికీ;
- (SDL_కిటికీ *)కిటికీ;
- (శూన్య)explicitUpdate;
- (శూన్య)cleanup;

@property(retain, nonatomic) NSOpenGLPixelFormat *openglPixelFormat; // macOS 10.10 has -[NSOpenGLContext pixelFormat] but this handles older OS releases.

@చివర

// OpenGL functions
బాహ్య bool Cocoa_GL_ఎక్కించు_Library(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *మార్గం);
బాహ్య SDL_Function_సూచిక Cocoa_GL_Get_Proc_చిరునామా(SDL_VideoDevice *_this, స్థిరరాశి అక్షరం *proc);
బాహ్య శూన్య Cocoa_GL_UnloadLibrary(SDL_VideoDevice *_this);
బాహ్య SDL_GLContext Cocoa_GL_CreateContext(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool Cocoa_GL_MakeCurrent(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ, SDL_GLContext context);
బాహ్య bool Cocoa_GL_సమితి_మార్పిడి_Interval(SDL_VideoDevice *_this, పూర్ణాంకం interval);
బాహ్య bool Cocoa_GL_Get_మార్పిడి_Interval(SDL_VideoDevice *_this, పూర్ణాంకం *interval);
బాహ్య bool Cocoa_GL_మార్పిడి_కిటికీ(SDL_VideoDevice *_this, SDL_కిటికీ *కిటికీ);
బాహ్య bool Cocoa_GL_DestroyContext(SDL_VideoDevice *_this, SDL_GLContext context);

#నిర్వచితమైతే __clang__
#సూచన clang diagnostic తీయి
#అయితే_ముగింపు

#అయితే_ముగింపు // SDL_VIDEO_OPENGL_CGL

#అయితే_ముగింపు // SDL_cocoaopengl_h_

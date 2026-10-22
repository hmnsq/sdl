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

/* *INDENT-OFF* */ // clang-format off

#ifndef SDL_X11_MODULE
#define SDL_X11_MODULE(modname)
#endif

#ifndef SDL_X11_SYM
#define SDL_X11_SYM(rc, fn, params)
#endif

SDL_X11_MODULE(BASEXLIB)
SDL_X11_SYM(XSizeHints*,XAllocSizeHints,(void))
SDL_X11_SYM(XWMHints*,XAllocWMHints,(void))
SDL_X11_SYM(XClassHint*,XAllocClassHint,(void))
SDL_X11_SYM(ціле,XChangePointerControl,(Display* a,Bool b,Bool c,ціле d,ціле e,ціле f))
SDL_X11_SYM(ціле,XChangeProperty,(Display* a,Window b,Atom c,Atom d,ціле e,ціле f,_Xconst unsigned char* g,ціле h))
SDL_X11_SYM(Bool,XCheckIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(ціле,XClearWindow,(Display* a,Window b))
SDL_X11_SYM(ціле,XCloseDisplay,(Display* a))
SDL_X11_SYM(ціле,XConvertSelection,(Display* a,Atom b,Atom c,Atom d,Window e,Time f))
SDL_X11_SYM(Pixmap,XCreateBitmapFromData,(Display *dpy,Drawable d,_Xconst char *data,unsigned ціле width,unsigned ціле height))
SDL_X11_SYM(Colormap,XCreateColormap,(Display* a,Window b,Visual* c,ціле d))
SDL_X11_SYM(Cursor,XCreatePixmapCursor,(Display* a,Pixmap b,Pixmap c,XColor* d,XColor* e,unsigned ціле f,unsigned ціле g))
SDL_X11_SYM(Cursor,XCreatePixmap,(Display* a,Drawable b,unsigned ціле d,unsigned ціле e,unsigned ціле f))
SDL_X11_SYM(Cursor,XCreateFontCursor,(Display* a,unsigned ціле b))
SDL_X11_SYM(XFontSet,XCreateFontSet,(Display* a, _Xconst char* b, char*** c, ціле* d, char** e))
SDL_X11_SYM(GC,XCreateGC,(Display* a,Drawable b,unsigned long c,XGCValues* d))
SDL_X11_SYM(void,XSetFont,(Display* a,GC b,Font c))
SDL_X11_SYM(Status,XAllocColor,(Display *a, Colormap b, XColor *c))
SDL_X11_SYM(XImage*,XCreateImage,(Display* a,Visual* b,unsigned ціле c,ціле d,ціле e,char* f,unsigned ціле g,unsigned ціле h,ціле i,ціле j))
SDL_X11_SYM(Window,XCreateWindow,(Display* a,Window b,ціле c,ціле d,unsigned ціле e,unsigned ціле f,unsigned ціле g,ціле h,unsigned ціле i,Visual* j,unsigned long k,XSetWindowAttributes* l))
SDL_X11_SYM(void,XCopyArea,(Display *a, Drawable b, Drawable c, GC d, ціле e, ціле f, unsigned ціле g, unsigned ціле h, ціле i, ціле j))
SDL_X11_SYM(ціле,XDefineCursor,(Display* a,Window b,Cursor c))
SDL_X11_SYM(ціле,XDeleteProperty,(Display* a,Window b,Atom c))
SDL_X11_SYM(ціле,XDestroyWindow,(Display* a,Window b))
SDL_X11_SYM(ціле,XDisplayKeycodes,(Display* a,ціле* b,ціле* c))
SDL_X11_SYM(ціле,XDrawRectangle,(Display* a,Drawable b,GC c,ціле d,ціле e,unsigned ціле f,unsigned ціле g))
SDL_X11_SYM(ціле,XFontsOfFontSet,(XFontSet a,XFontStruct ***b,char ***c))
SDL_X11_SYM(ціле,XFillArc,(Display* a,Drawable b,GC c,ціле d,ціле e,unsigned ціле f,unsigned ціле g, ціле h, ціле i))
SDL_X11_SYM(char*,XDisplayName,(_Xconst char* a))
SDL_X11_SYM(ціле,XDrawString,(Display* a,Drawable b,GC c,ціле d,ціле e,_Xconst char* f,ціле g))
SDL_X11_SYM(ціле,XEventsQueued,(Display* a,ціле b))
SDL_X11_SYM(ціле,XFillRectangle,(Display* a,Drawable b,GC c,ціле d,ціле e,unsigned ціле f,unsigned ціле g))
SDL_X11_SYM(Bool,XFilterEvent,(XEvent *event,Window w))
SDL_X11_SYM(ціле,XFlush,(Display* a))
SDL_X11_SYM(ціле,XFree,(void*a))
SDL_X11_SYM(ціле,XFreeCursor,(Display* a,Cursor b))
SDL_X11_SYM(void,XFreeFontSet,(Display* a, XFontSet b))
SDL_X11_SYM(ціле,XFreeGC,(Display* a,GC b))
SDL_X11_SYM(ціле,XFreeFont,(Display* a, XFontStruct* b))
SDL_X11_SYM(ціле,XFreeModifiermap,(XModifierKeymap* a))
SDL_X11_SYM(ціле,XFreePixmap,(Display* a,Pixmap b))
SDL_X11_SYM(ціле,XFreeColormap,(Display* a,Colormap b))
SDL_X11_SYM(void,XFreeStringList,(char** a))
SDL_X11_SYM(char*,XGetAtomName,(Display *a,Atom b))
SDL_X11_SYM(ціле,XGetInputFocus,(Display *a,Window *b,ціле *c))
SDL_X11_SYM(KeySym*,XGetKeyboardMapping,(Display *a, KeyCode b, ціле c, ціле *d))
SDL_X11_SYM(ціле,XGetErrorDatabaseText,(Display* a,_Xconst char* b,_Xconst char* c,_Xconst char* d,char* e,ціле f))
SDL_X11_SYM(XModifierKeymap*,XGetModifierMapping,(Display* a))
SDL_X11_SYM(ціле,XGetPointerControl,(Display* a,ціле* b,ціле* c,ціле* d))
SDL_X11_SYM(Window,XGetSelectionOwner,(Display* a,Atom b))
SDL_X11_SYM(XVisualInfo*,XGetVisualInfo,(Display* a,long b,XVisualInfo* c,ціле* d))
SDL_X11_SYM(Status,XGetWindowAttributes,(Display* a,Window b,XWindowAttributes* c))
SDL_X11_SYM(ціле,XGetWindowProperty,(Display* a,Window b,Atom c,long d,long e,Bool f,Atom g,Atom* h,ціле* i,unsigned long* j,unsigned long *k,unsigned char **l))
SDL_X11_SYM(XWMHints*,XGetWMHints,(Display* a,Window b))
SDL_X11_SYM(Status,XGetWMNormalHints,(Display *a,Window b, XSizeHints *c, long *d))
SDL_X11_SYM(ціле,XIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(ціле,XGrabKeyboard,(Display* a,Window b,Bool c,ціле d,ціле e,Time f))
SDL_X11_SYM(ціле,XGrabPointer,(Display* a,Window b,Bool c,unsigned ціле d,ціле e,ціле f,Window g,Cursor h,Time i))
SDL_X11_SYM(ціле,XGrabServer,(Display* a))
SDL_X11_SYM(Status,XIconifyWindow,(Display* a,Window b,ціле c))
SDL_X11_SYM(KeyCode,XKeysymToKeycode,(Display* a,KeySym b))
SDL_X11_SYM(char*,XKeysymToString,(KeySym a))
SDL_X11_SYM(ціле,XInstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(Atom,XInternAtom,(Display* a,_Xconst char* b,Bool c))
SDL_X11_SYM(XPixmapFormatValues*,XListPixmapFormats,(Display* a,ціле* b))
SDL_X11_SYM(XFontStruct*,XLoadQueryFont,(Display* a,_Xconst char* b))
SDL_X11_SYM(KeySym,XLookupKeysym,(XKeyEvent* a,ціле b))
SDL_X11_SYM(ціле,XLookupString,(XKeyEvent* a,char* b,ціле c,KeySym* d,XComposeStatus* e))
SDL_X11_SYM(ціле,XMapRaised,(Display* a,Window b))
SDL_X11_SYM(Status,XMatchVisualInfo,(Display* a,ціле b,ціле c,ціле d,XVisualInfo* e))
SDL_X11_SYM(ціле,XMissingExtension,(Display* a,_Xconst char* b))
SDL_X11_SYM(ціле,XMoveWindow,(Display* a,Window b,ціле c,ціле d))
SDL_X11_SYM(Display*,XOpenDisplay,(_Xconst char* a))
SDL_X11_SYM(Status,XInitThreads,(void))
SDL_X11_SYM(ціле,XPeekEvent,(Display* a,XEvent* b))
SDL_X11_SYM(ціле,XPending,(Display* a))
SDL_X11_SYM(XImage*,XGetImage,(Display* a,Drawable b,ціле c, ціле d,unsigned ціле e,unsigned ціле f,unsigned long g,ціле h))
SDL_X11_SYM(ціле,XPutImage,(Display* a,Drawable b,GC c,XImage* d,ціле e,ціле f,ціле g,ціле h,unsigned ціле i,unsigned ціле j))
SDL_X11_SYM(ціле,XQueryKeymap,(Display* a,char b[32]))
SDL_X11_SYM(Bool,XQueryPointer,(Display* a,Window b,Window* c,Window* d,ціле* e,ціле* f,ціле* g,ціле* h,unsigned ціле* i))
SDL_X11_SYM(ціле,XRaiseWindow,(Display* a,Window b))
SDL_X11_SYM(ціле,XReparentWindow,(Display* a,Window b,Window c,ціле d,ціле e))
SDL_X11_SYM(ціле,XResetScreenSaver,(Display* a))
SDL_X11_SYM(ціле,XResizeWindow,(Display* a,Window b,unsigned ціле c,unsigned ціле d))
SDL_X11_SYM(ціле,XScreenNumberOfScreen,(Screen* a))
SDL_X11_SYM(ціле,XSelectInput,(Display* a,Window b,long c))
SDL_X11_SYM(Status,XSendEvent,(Display* a,Window b,Bool c,long d,XEvent* e))
SDL_X11_SYM(XErrorHandler,XSetErrorHandler,(XErrorHandler a))
SDL_X11_SYM(ціле,XSetForeground,(Display* a,GC b,unsigned long c))
SDL_X11_SYM(XIOErrorHandler,XSetIOErrorHandler,(XIOErrorHandler a))
SDL_X11_SYM(ціле,XSetInputFocus,(Display *a,Window b,ціле c,Time d))
SDL_X11_SYM(ціле,XSetSelectionOwner,(Display* a,Atom b,Window c,Time d))
SDL_X11_SYM(ціле,XSetTransientForHint,(Display* a,Window b,Window c))
SDL_X11_SYM(void,XSetTextProperty,(Display* a,Window b,XTextProperty* c,Atom d))
SDL_X11_SYM(ціле,XSetWindowBackground,(Display* a,Window b,unsigned long c))
SDL_X11_SYM(void,XSetWMHints,(Display* a,Window b,XWMHints* c))
SDL_X11_SYM(void,XSetWMNormalHints,(Display* a,Window b,XSizeHints* c))
SDL_X11_SYM(void,XSetWMProperties,(Display* a,Window b,XTextProperty* c,XTextProperty* d,char** e,ціле f,XSizeHints* g,XWMHints* h,XClassHint* i))
SDL_X11_SYM(Status,XSetWMProtocols,(Display* a,Window b,Atom* c,ціле d))
SDL_X11_SYM(ціле,XStoreColors,(Display* a,Colormap b,XColor* c,ціле d))
SDL_X11_SYM(ціле,XStoreName,(Display* a,Window b,_Xconst char* c))
SDL_X11_SYM(Status,XStringListToTextProperty,(char** a,ціле b,XTextProperty* c))
SDL_X11_SYM(ціле,XSync,(Display* a,Bool b))
SDL_X11_SYM(ціле,XTextExtents,(XFontStruct* a,_Xconst char* b,ціле c,ціле* d,ціле* e,ціле* f,XCharStruct* g))
SDL_X11_SYM(Bool,XTranslateCoordinates,(Display *a,Window b,Window c,ціле d,ціле e,ціле* f,ціле* g,Window* h))
SDL_X11_SYM(ціле,XUndefineCursor,(Display* a,Window b))
SDL_X11_SYM(ціле,XUngrabKeyboard,(Display* a,Time b))
SDL_X11_SYM(ціле,XUngrabPointer,(Display* a,Time b))
SDL_X11_SYM(ціле,XUngrabServer,(Display* a))
SDL_X11_SYM(ціле,XUninstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(ціле,XUnloadFont,(Display* a,Font b))
SDL_X11_SYM(ціле,XWarpPointer,(Display* a,Window b,Window c,ціле d,ціле e,unsigned ціле f,unsigned ціле g,ціле h,ціле i))
SDL_X11_SYM(ціле,XWindowEvent,(Display* a,Window b,long c,XEvent* d))
SDL_X11_SYM(Status,XWithdrawWindow,(Display* a,Window b,ціле c))
SDL_X11_SYM(VisualID,XVisualIDFromVisual,(Visual* a))
SDL_X11_SYM(char*,XGetDefault,(Display* a,_Xconst char* b, _Xconst char* c))
SDL_X11_SYM(Bool,XQueryExtension,(Display* a,_Xconst char* b,ціле* c,ціле* d,ціле* e))
SDL_X11_SYM(char *,XDisplayString,(Display* a))
SDL_X11_SYM(ціле,XGetErrorText,(Display* a,ціле b,char* c,ціле d))
SDL_X11_SYM(void,_XEatData,(Display* a,unsigned long b))
SDL_X11_SYM(void,_XFlush,(Display* a))
SDL_X11_SYM(void,_XFlushGCCache,(Display* a,GC b))
SDL_X11_SYM(ціле,_XRead,(Display* a,char* b,long c))
SDL_X11_SYM(void,_XReadPad,(Display* a,char* b,long c))
SDL_X11_SYM(void,_XSend,(Display* a,_Xconst char* b,long c))
SDL_X11_SYM(Status,_XReply,(Display* a,xReply* b,ціле c,Bool d))
SDL_X11_SYM(unsigned long,_XSetLastRequestRead,(Display* a,xGenericReply* b))
SDL_X11_SYM(SDL_X11_XSynchronizeRetType,XSynchronize,(Display* a,Bool b))
SDL_X11_SYM(SDL_X11_XESetWireToEventRetType,XESetWireToEvent,(Display* a,ціле b,SDL_X11_XESetWireToEventRetType c))
SDL_X11_SYM(SDL_X11_XESetEventToWireRetType,XESetEventToWire,(Display* a,ціле b,SDL_X11_XESetEventToWireRetType c))
SDL_X11_SYM(void,XRefreshKeyboardMapping,(XMappingEvent *a))
SDL_X11_SYM(ціле,XQueryTree,(Display* a,Window b,Window* c,Window* d,Window** e,unsigned ціле* f))
SDL_X11_SYM(Bool,XSupportsLocale,(void))
SDL_X11_SYM(Status,XmbTextListToTextProperty,(Display* a,char** b,ціле c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(Region,XCreateRegion,(void))
SDL_X11_SYM(ціле,XUnionRectWithRegion,(XRectangle *a, Region b, Region c))
SDL_X11_SYM(void,XDestroyRegion,(Region))
SDL_X11_SYM(void,XrmInitialize,(void))
SDL_X11_SYM(char*,XResourceManagerString,(Display *display))
SDL_X11_SYM(XrmDatabase,XrmGetStringDatabase,(char *data))
SDL_X11_SYM(void,XrmDestroyDatabase,(XrmDatabase db))
SDL_X11_SYM(Bool,XrmGetResource,(XrmDatabase db, char* str_name, char* str_class, char **str_type_return, XrmValue *))
SDL_X11_SYM(ціле,XGetPointerMapping,(Display *a, unsigned char *b, unsigned ціле c))

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
SDL_X11_MODULE(XFIXES)
SDL_X11_SYM(PointerBarrier, XFixesCreatePointerBarrier, (Display* a, Window b, ціле c, ціле d, ціле e, ціле f, ціле g, ціле h, ціле *i))
SDL_X11_SYM(void, XFixesDestroyPointerBarrier, (Display* a, PointerBarrier b))
SDL_X11_SYM(ціле, XIBarrierReleasePointer,(Display* a,  ціле b, PointerBarrier c, BarrierEventID d)) // this is actually Xinput2
SDL_X11_SYM(Status, XFixesQueryVersion,(Display* a, ціле* b, ціле* c))
SDL_X11_SYM(Status, XFixesSelectSelectionInput, (Display* a, Window b, Atom c, unsigned long d))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
SDL_X11_MODULE(XSYNC)
SDL_X11_SYM(Status, XSyncQueryExtension, (Display* a, ціле* b, ціле* c))
SDL_X11_SYM(Status, XSyncInitialize, (Display* a, ціле* b, ціле* c))
SDL_X11_SYM(XSyncCounter, XSyncCreateCounter, (Display* a, XSyncValue b))
SDL_X11_SYM(Status, XSyncDestroyCounter, (Display* a, XSyncCounter b))
SDL_X11_SYM(Status, XSyncSetCounter, (Display* a, XSyncCounter b, XSyncValue c))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XTEST
SDL_X11_MODULE(XTEST)
SDL_X11_SYM(Status, XTestQueryExtension, (Display* a, ціле* b, ціле* c))
SDL_X11_SYM(ціле, XTestFakeMotionEvent, (Display* a, ціле b, ціле c, ціле d, unsigned long e))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
SDL_X11_SYM(Bool,XGetEventData,(Display* a,XGenericEventCookie* b))
SDL_X11_SYM(void,XFreeEventData,(Display* a,XGenericEventCookie* b))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
SDL_X11_SYM(Bool,XkbQueryExtension,(Display* a,ціле * b,ціле * c,ціле * d,ціле * e, ціле *f))
SDL_X11_SYM(KeySym,XkbKeycodeToKeysym,(Display* a, KeyCode b, unsigned ціле c, unsigned ціле d))
SDL_X11_SYM(Bool,XkbSelectEvents,(Display* a, unsigned ціле b, unsigned ціле c, unsigned long d))
SDL_X11_SYM(Bool,XkbSelectEventDetails,(Display* a, unsigned ціле b, unsigned ціле c, unsigned long d, unsigned long e))
SDL_X11_SYM(Status,XkbGetNames,(Display *a, unsigned ціле b, XkbDescPtr c))
SDL_X11_SYM(Status,XkbGetState,(Display* a,unsigned ціле b,XkbStatePtr c))
SDL_X11_SYM(Status,XkbGetUpdatedMap,(Display* a,unsigned ціле b,XkbDescPtr c))
SDL_X11_SYM(XkbDescPtr,XkbGetMap,(Display* a,unsigned ціле b,unsigned ціле c))
SDL_X11_SYM(void,XkbFreeClientMap,(XkbDescPtr a,unsigned ціле b, Bool c))
SDL_X11_SYM(void,XkbFreeKeyboard,(XkbDescPtr a,unsigned ціле b, Bool c))
SDL_X11_SYM(Status,XkbRefreshKeyboardMapping,(XkbMapNotifyEvent *a))
SDL_X11_SYM(Bool,XkbSetDetectableAutoRepeat,(Display* a, Bool b, Bool* c))
#endif

#ifdef X_HAVE_UTF8_STRING
SDL_X11_MODULE(UTF8)
SDL_X11_SYM(ціле,Xutf8TextListToTextProperty,(Display* a,char** b,ціле c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(ціле,Xutf8LookupString,(XIC a,XKeyPressedEvent* b,char* c,ціле d,KeySym* e,Status* f))
SDL_X11_SYM(XIC,XCreateIC,(XIM,...))
SDL_X11_SYM(void,XDestroyIC,(XIC a))
SDL_X11_SYM(char*,XGetICValues,(XIC,...))
SDL_X11_SYM(char*,XSetICValues,(XIC,...))
SDL_X11_SYM(XVaNestedList,XVaCreateNestedList,(ціле, ...))
SDL_X11_SYM(void,XSetICFocus,(XIC a))
SDL_X11_SYM(void,XUnsetICFocus,(XIC a))
SDL_X11_SYM(XIM,XOpenIM,(Display* a,struct _XrmHashBucketRec* b,char* c,char* d))
SDL_X11_SYM(Status,XCloseIM,(XIM a))
SDL_X11_SYM(char*, XSetIMValues,(XIM,...))
SDL_X11_SYM(Bool,XRegisterIMInstantiateCallback,(Display*,struct _XrmHashBucketRec*,char*,char*,XIDProc,XPointer))
SDL_X11_SYM(Bool,XUnregisterIMInstantiateCallback,(Display*,struct _XrmHashBucketRec*,char*,char*,XIDProc,XPointer))
SDL_X11_SYM(void,Xutf8DrawString,(Display *a, Drawable b, XFontSet c, GC d, ціле e, ціле f, _Xconst char *g, ціле h))
SDL_X11_SYM(ціле,Xutf8TextExtents,(XFontSet a, _Xconst char* b, ціле c, XRectangle* d, XRectangle* e))
SDL_X11_SYM(char*,XSetLocaleModifiers,(const char *a))
SDL_X11_SYM(char*,Xutf8ResetIC,(XIC a))
SDL_X11_SYM(XFontSetExtents*,XExtentsOfFontSet,(XFontSet a))
SDL_X11_SYM(Bool,XContextDependentDrawing,(XFontSet a))
#endif


#ifndef NO_SHARED_MEMORY
SDL_X11_MODULE(SHM)
SDL_X11_SYM(Status,XShmAttach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(Status,XShmDetach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(Status,XShmPutImage,(Display* a,Drawable b,GC c,XImage* d,ціле e,ціле f,ціле g,ціле h,unsigned ціле i,unsigned ціле j,Bool k))
SDL_X11_SYM(Status,XShmGetImage,(Display* a,Drawable b,XImage *c,ціле d, ціле e, unsigned long f))
SDL_X11_SYM(XImage*,XShmCreateImage,(Display* a,Visual* b,unsigned ціле c,ціле d,char* e,XShmSegmentInfo* f,unsigned ціле g,unsigned ціле h))
SDL_X11_SYM(Pixmap,XShmCreatePixmap,(Display *a,Drawable b,char* c,XShmSegmentInfo* d, unsigned ціле e, unsigned ціле f, unsigned ціле g))
SDL_X11_SYM(Bool,XShmQueryExtension,(Display* a))
SDL_X11_SYM(Status,XShmQueryVersion,(Display* a, ціле *b, ціле *c, Bool *d))
SDL_X11_SYM(ціле,XShmPixmapFormat,(Display* a))
#endif

/*
 * Not required...these only exist in code in headers on some 64-bit platforms,
 *  and are removed via macros elsewhere, so it's safe for them to be missing.
 */
#ifdef LONG64
SDL_X11_MODULE(IO_32BIT)
SDL_X11_SYM(ціле,_XData32,(Display *dpy,register _Xconst long *data,unsigned len))
SDL_X11_SYM(void,_XRead32,(Display *dpy,register long *data,long len))
#endif

/*
 * These only show up on some variants of Unix.
 */
#ifdef SDL_PLATFORM_OSF
SDL_X11_MODULE(OSF_ENTRY_POINTS)
SDL_X11_SYM(void,_SmtBufferOverflow,(Display *dpy,register smtDisplayPtr p))
SDL_X11_SYM(void,_SmtIpError,(Display *dpy,register smtDisplayPtr p,ціле i))
SDL_X11_SYM(ціле,ipAllocateData,(ChannelPtr a,IPCard b,IPDataPtr * c))
SDL_X11_SYM(ціле,ipUnallocateAndSendData,(ChannelPtr a,IPCard b))
#endif

// XCursor support
#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
SDL_X11_MODULE(XCURSOR)
SDL_X11_SYM(XcursorImage*,XcursorImageCreate,(ціле a,ціле b))
SDL_X11_SYM(XcursorImages*,XcursorImagesCreate,(ціле a))
SDL_X11_SYM(void,XcursorImageDestroy,(XcursorImage *a))
SDL_X11_SYM(void,XcursorImagesDestroy,(XcursorImages *a))
SDL_X11_SYM(Cursor,XcursorImageLoadCursor,(Display *a,const XcursorImage *b))
SDL_X11_SYM(Cursor,XcursorImagesLoadCursor,(Display *a,const XcursorImages *b))
SDL_X11_SYM(Cursor,XcursorLibraryLoadCursor,(Display *a, const char *b))
#endif

// Xdbe support
#ifdef SDL_VIDEO_DRIVER_X11_XDBE
SDL_X11_MODULE(XDBE)
SDL_X11_SYM(Status,XdbeQueryExtension,(Display *dpy,ціле *major_version_return,ціле *minor_version_return))
SDL_X11_SYM(XdbeBackBuffer,XdbeAllocateBackBufferName,(Display *dpy,Window window,XdbeSwapAction swap_action))
SDL_X11_SYM(Status,XdbeDeallocateBackBufferName,(Display *dpy,XdbeBackBuffer buffer))
SDL_X11_SYM(Status,XdbeSwapBuffers,(Display *dpy,XdbeSwapInfo *swap_info,ціле num_windows))
SDL_X11_SYM(Status,XdbeBeginIdiom,(Display *dpy))
SDL_X11_SYM(Status,XdbeEndIdiom,(Display *dpy))
SDL_X11_SYM(XdbeScreenVisualInfo*,XdbeGetVisualInfo,(Display *dpy,Drawable *screen_specifiers,ціле *num_screens))
SDL_X11_SYM(void,XdbeFreeVisualInfo,(XdbeScreenVisualInfo *visual_info))
SDL_X11_SYM(XdbeBackBufferAttributes*,XdbeGetBackBufferAttributes,(Display *dpy,XdbeBackBuffer buffer))
#endif

// XInput2 support for multiple mice, tablets, etc.
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
SDL_X11_MODULE(XINPUT2)
SDL_X11_SYM(XIDeviceInfo*,XIQueryDevice,(Display *a,ціле b,ціле *c))
SDL_X11_SYM(void,XIFreeDeviceInfo,(XIDeviceInfo *a))
SDL_X11_SYM(ціле,XISelectEvents,(Display *a,Window b,XIEventMask *c,ціле d))
SDL_X11_SYM(ціле,XIGrabTouchBegin,(Display *a,ціле b,Window c,ціле d,XIEventMask *e,ціле f,XIGrabModifiers *g))
SDL_X11_SYM(ціле,XIUngrabTouchBegin, (Display *a,ціле b,Window c, ціле d,XIGrabModifiers *e))
SDL_X11_SYM(Status,XIQueryVersion,(Display *a,ціле *b,ціле *c))
SDL_X11_SYM(XIEventMask*,XIGetSelectedEvents,(Display *a,Window b,ціле *c))
SDL_X11_SYM(Bool,XIGetClientPointer,(Display *a,Window b,ціле *c))
SDL_X11_SYM(Bool,XIWarpPointer,(Display *a,ціле b,Window c,Window d,double e,double f,ціле g,ціле h,double i,double j))
SDL_X11_SYM(Status,XIGetProperty,(Display *a,ціле b,Atom c,long d,long e,Bool f, Atom g, Atom *h, ціле *i, unsigned long *j, unsigned long *k, unsigned char **l))
#endif

// XRandR support
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
SDL_X11_MODULE(XRANDR)
SDL_X11_SYM(Status,XRRQueryVersion,(Display *dpy,ціле *major_versionp,ціле *minor_versionp))
SDL_X11_SYM(Bool,XRRQueryExtension,(Display *dpy,ціле *event_base_return,ціле *error_base_return))
SDL_X11_SYM(XRRScreenConfiguration *,XRRGetScreenInfo,(Display *dpy,Drawable draw))
SDL_X11_SYM(SizeID,XRRConfigCurrentConfiguration,(XRRScreenConfiguration *config,Rotation *rotation))
SDL_X11_SYM(short,XRRConfigCurrentRate,(XRRScreenConfiguration *config))
SDL_X11_SYM(short *,XRRConfigRates,(XRRScreenConfiguration *config,ціле sizeID,ціле *nrates))
SDL_X11_SYM(XRRScreenSize *,XRRConfigSizes,(XRRScreenConfiguration *config,ціле *nsizes))
SDL_X11_SYM(Status,XRRSetScreenConfigAndRate,(Display *dpy,XRRScreenConfiguration *config,Drawable draw,ціле size_index,Rotation rotation,short rate,Time timestamp))
SDL_X11_SYM(void,XRRFreeScreenConfigInfo,(XRRScreenConfiguration *config))
SDL_X11_SYM(void,XRRSetScreenSize,(Display *dpy, Window window,ціле width, ціле height,ціле mmWidth, ціле mmHeight))
SDL_X11_SYM(Status,XRRGetScreenSizeRange,(Display *dpy, Window window,ціле *minWidth, ціле *minHeight, ціле *maxWidth, ціле *maxHeight))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResources,(Display *dpy, Window window))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResourcesCurrent,(Display *dpy, Window window))
SDL_X11_SYM(void,XRRFreeScreenResources,(XRRScreenResources *resources))
SDL_X11_SYM(XRROutputInfo *,XRRGetOutputInfo,(Display *dpy, XRRScreenResources *resources, RROutput output))
SDL_X11_SYM(void,XRRFreeOutputInfo,(XRROutputInfo *outputInfo))
SDL_X11_SYM(XRRCrtcInfo *,XRRGetCrtcInfo,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc))
SDL_X11_SYM(void,XRRFreeCrtcInfo,(XRRCrtcInfo *crtcInfo))
SDL_X11_SYM(Status,XRRSetCrtcConfig,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc, Time timestamp, ціле x, ціле y, RRMode mode, Rotation rotation, RROutput *outputs, ціле noutputs))
SDL_X11_SYM(Atom*,XRRListOutputProperties,(Display *dpy, RROutput output, ціле *nprop))
SDL_X11_SYM(XRRPropertyInfo*,XRRQueryOutputProperty,(Display *dpy,RROutput output, Atom property))
SDL_X11_SYM(ціле,XRRGetOutputProperty,(Display *dpy,RROutput output, Atom property, long offset, long length, Bool _delete, Bool pending, Atom req_type, Atom *actual_type, ціле *actual_format, unsigned long *nitems, unsigned long *bytes_after, unsigned char **prop))
SDL_X11_SYM(RROutput,XRRGetOutputPrimary,(Display *dpy,Window window))
SDL_X11_SYM(void,XRRSelectInput,(Display *dpy, Window window, ціле mask))
SDL_X11_SYM(Status,XRRGetCrtcTransform,(Display *dpy,RRCrtc crtc,XRRCrtcTransformAttributes **attributes))
#endif

// MIT-SCREEN-SAVER support
#ifdef SDL_VIDEO_DRIVER_X11_XSCRNSAVER
SDL_X11_MODULE(XSS)
SDL_X11_SYM(Bool,XScreenSaverQueryExtension,(Display *dpy,ціле *event_base,ціле *error_base))
SDL_X11_SYM(Status,XScreenSaverQueryVersion,(Display *dpy,ціле *major_versionp,ціле *minor_versionp))
SDL_X11_SYM(void,XScreenSaverSuspend,(Display *dpy,Bool suspend))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XSHAPE
SDL_X11_MODULE(XSHAPE)
SDL_X11_SYM(void,XShapeCombineMask,(Display *dpy,Window dest,ціле dest_kind,ціле x_off,ціле y_off,Pixmap src,ціле op))
SDL_X11_SYM(void,XShapeCombineRegion,(Display *a,Window b,ціле c,ціле d,ціле e,Region f,ціле g))
#endif

#undef SDL_X11_MODULE
#undef SDL_X11_SYM

/* *INDENT-ON* */ // clang-format on

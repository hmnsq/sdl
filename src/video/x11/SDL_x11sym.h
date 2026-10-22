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
SDL_X11_SYM(целое,XChangePointerControl,(Display* a,Bool b,Bool c,целое d,целое e,целое f))
SDL_X11_SYM(целое,XChangeProperty,(Display* a,Window b,Atom c,Atom d,целое e,целое f,_Xconst unsigned char* g,целое h))
SDL_X11_SYM(Bool,XCheckIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(целое,XClearWindow,(Display* a,Window b))
SDL_X11_SYM(целое,XCloseDisplay,(Display* a))
SDL_X11_SYM(целое,XConvertSelection,(Display* a,Atom b,Atom c,Atom d,Window e,Time f))
SDL_X11_SYM(Pixmap,XCreateBitmapFromData,(Display *dpy,Drawable d,_Xconst char *data,unsigned целое width,unsigned целое height))
SDL_X11_SYM(Colormap,XCreateColormap,(Display* a,Window b,Visual* c,целое d))
SDL_X11_SYM(Cursor,XCreatePixmapCursor,(Display* a,Pixmap b,Pixmap c,XColor* d,XColor* e,unsigned целое f,unsigned целое g))
SDL_X11_SYM(Cursor,XCreatePixmap,(Display* a,Drawable b,unsigned целое d,unsigned целое e,unsigned целое f))
SDL_X11_SYM(Cursor,XCreateFontCursor,(Display* a,unsigned целое b))
SDL_X11_SYM(XFontSet,XCreateFontSet,(Display* a, _Xconst char* b, char*** c, целое* d, char** e))
SDL_X11_SYM(GC,XCreateGC,(Display* a,Drawable b,unsigned long c,XGCValues* d))
SDL_X11_SYM(void,XSetFont,(Display* a,GC b,Font c))
SDL_X11_SYM(Status,XAllocColor,(Display *a, Colormap b, XColor *c))
SDL_X11_SYM(XImage*,XCreateImage,(Display* a,Visual* b,unsigned целое c,целое d,целое e,char* f,unsigned целое g,unsigned целое h,целое i,целое j))
SDL_X11_SYM(Window,XCreateWindow,(Display* a,Window b,целое c,целое d,unsigned целое e,unsigned целое f,unsigned целое g,целое h,unsigned целое i,Visual* j,unsigned long k,XSetWindowAttributes* l))
SDL_X11_SYM(void,XCopyArea,(Display *a, Drawable b, Drawable c, GC d, целое e, целое f, unsigned целое g, unsigned целое h, целое i, целое j))
SDL_X11_SYM(целое,XDefineCursor,(Display* a,Window b,Cursor c))
SDL_X11_SYM(целое,XDeleteProperty,(Display* a,Window b,Atom c))
SDL_X11_SYM(целое,XDestroyWindow,(Display* a,Window b))
SDL_X11_SYM(целое,XDisplayKeycodes,(Display* a,целое* b,целое* c))
SDL_X11_SYM(целое,XDrawRectangle,(Display* a,Drawable b,GC c,целое d,целое e,unsigned целое f,unsigned целое g))
SDL_X11_SYM(целое,XFontsOfFontSet,(XFontSet a,XFontStruct ***b,char ***c))
SDL_X11_SYM(целое,XFillArc,(Display* a,Drawable b,GC c,целое d,целое e,unsigned целое f,unsigned целое g, целое h, целое i))
SDL_X11_SYM(char*,XDisplayName,(_Xconst char* a))
SDL_X11_SYM(целое,XDrawString,(Display* a,Drawable b,GC c,целое d,целое e,_Xconst char* f,целое g))
SDL_X11_SYM(целое,XEventsQueued,(Display* a,целое b))
SDL_X11_SYM(целое,XFillRectangle,(Display* a,Drawable b,GC c,целое d,целое e,unsigned целое f,unsigned целое g))
SDL_X11_SYM(Bool,XFilterEvent,(XEvent *event,Window w))
SDL_X11_SYM(целое,XFlush,(Display* a))
SDL_X11_SYM(целое,XFree,(void*a))
SDL_X11_SYM(целое,XFreeCursor,(Display* a,Cursor b))
SDL_X11_SYM(void,XFreeFontSet,(Display* a, XFontSet b))
SDL_X11_SYM(целое,XFreeGC,(Display* a,GC b))
SDL_X11_SYM(целое,XFreeFont,(Display* a, XFontStruct* b))
SDL_X11_SYM(целое,XFreeModifiermap,(XModifierKeymap* a))
SDL_X11_SYM(целое,XFreePixmap,(Display* a,Pixmap b))
SDL_X11_SYM(целое,XFreeColormap,(Display* a,Colormap b))
SDL_X11_SYM(void,XFreeStringList,(char** a))
SDL_X11_SYM(char*,XGetAtomName,(Display *a,Atom b))
SDL_X11_SYM(целое,XGetInputFocus,(Display *a,Window *b,целое *c))
SDL_X11_SYM(KeySym*,XGetKeyboardMapping,(Display *a, KeyCode b, целое c, целое *d))
SDL_X11_SYM(целое,XGetErrorDatabaseText,(Display* a,_Xconst char* b,_Xconst char* c,_Xconst char* d,char* e,целое f))
SDL_X11_SYM(XModifierKeymap*,XGetModifierMapping,(Display* a))
SDL_X11_SYM(целое,XGetPointerControl,(Display* a,целое* b,целое* c,целое* d))
SDL_X11_SYM(Window,XGetSelectionOwner,(Display* a,Atom b))
SDL_X11_SYM(XVisualInfo*,XGetVisualInfo,(Display* a,long b,XVisualInfo* c,целое* d))
SDL_X11_SYM(Status,XGetWindowAttributes,(Display* a,Window b,XWindowAttributes* c))
SDL_X11_SYM(целое,XGetWindowProperty,(Display* a,Window b,Atom c,long d,long e,Bool f,Atom g,Atom* h,целое* i,unsigned long* j,unsigned long *k,unsigned char **l))
SDL_X11_SYM(XWMHints*,XGetWMHints,(Display* a,Window b))
SDL_X11_SYM(Status,XGetWMNormalHints,(Display *a,Window b, XSizeHints *c, long *d))
SDL_X11_SYM(целое,XIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(целое,XGrabKeyboard,(Display* a,Window b,Bool c,целое d,целое e,Time f))
SDL_X11_SYM(целое,XGrabPointer,(Display* a,Window b,Bool c,unsigned целое d,целое e,целое f,Window g,Cursor h,Time i))
SDL_X11_SYM(целое,XGrabServer,(Display* a))
SDL_X11_SYM(Status,XIconifyWindow,(Display* a,Window b,целое c))
SDL_X11_SYM(KeyCode,XKeysymToKeycode,(Display* a,KeySym b))
SDL_X11_SYM(char*,XKeysymToString,(KeySym a))
SDL_X11_SYM(целое,XInstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(Atom,XInternAtom,(Display* a,_Xconst char* b,Bool c))
SDL_X11_SYM(XPixmapFormatValues*,XListPixmapFormats,(Display* a,целое* b))
SDL_X11_SYM(XFontStruct*,XLoadQueryFont,(Display* a,_Xconst char* b))
SDL_X11_SYM(KeySym,XLookupKeysym,(XKeyEvent* a,целое b))
SDL_X11_SYM(целое,XLookupString,(XKeyEvent* a,char* b,целое c,KeySym* d,XComposeStatus* e))
SDL_X11_SYM(целое,XMapRaised,(Display* a,Window b))
SDL_X11_SYM(Status,XMatchVisualInfo,(Display* a,целое b,целое c,целое d,XVisualInfo* e))
SDL_X11_SYM(целое,XMissingExtension,(Display* a,_Xconst char* b))
SDL_X11_SYM(целое,XMoveWindow,(Display* a,Window b,целое c,целое d))
SDL_X11_SYM(Display*,XOpenDisplay,(_Xconst char* a))
SDL_X11_SYM(Status,XInitThreads,(void))
SDL_X11_SYM(целое,XPeekEvent,(Display* a,XEvent* b))
SDL_X11_SYM(целое,XPending,(Display* a))
SDL_X11_SYM(XImage*,XGetImage,(Display* a,Drawable b,целое c, целое d,unsigned целое e,unsigned целое f,unsigned long g,целое h))
SDL_X11_SYM(целое,XPutImage,(Display* a,Drawable b,GC c,XImage* d,целое e,целое f,целое g,целое h,unsigned целое i,unsigned целое j))
SDL_X11_SYM(целое,XQueryKeymap,(Display* a,char b[32]))
SDL_X11_SYM(Bool,XQueryPointer,(Display* a,Window b,Window* c,Window* d,целое* e,целое* f,целое* g,целое* h,unsigned целое* i))
SDL_X11_SYM(целое,XRaiseWindow,(Display* a,Window b))
SDL_X11_SYM(целое,XReparentWindow,(Display* a,Window b,Window c,целое d,целое e))
SDL_X11_SYM(целое,XResetScreenSaver,(Display* a))
SDL_X11_SYM(целое,XResizeWindow,(Display* a,Window b,unsigned целое c,unsigned целое d))
SDL_X11_SYM(целое,XScreenNumberOfScreen,(Screen* a))
SDL_X11_SYM(целое,XSelectInput,(Display* a,Window b,long c))
SDL_X11_SYM(Status,XSendEvent,(Display* a,Window b,Bool c,long d,XEvent* e))
SDL_X11_SYM(XErrorHandler,XSetErrorHandler,(XErrorHandler a))
SDL_X11_SYM(целое,XSetForeground,(Display* a,GC b,unsigned long c))
SDL_X11_SYM(XIOErrorHandler,XSetIOErrorHandler,(XIOErrorHandler a))
SDL_X11_SYM(целое,XSetInputFocus,(Display *a,Window b,целое c,Time d))
SDL_X11_SYM(целое,XSetSelectionOwner,(Display* a,Atom b,Window c,Time d))
SDL_X11_SYM(целое,XSetTransientForHint,(Display* a,Window b,Window c))
SDL_X11_SYM(void,XSetTextProperty,(Display* a,Window b,XTextProperty* c,Atom d))
SDL_X11_SYM(целое,XSetWindowBackground,(Display* a,Window b,unsigned long c))
SDL_X11_SYM(void,XSetWMHints,(Display* a,Window b,XWMHints* c))
SDL_X11_SYM(void,XSetWMNormalHints,(Display* a,Window b,XSizeHints* c))
SDL_X11_SYM(void,XSetWMProperties,(Display* a,Window b,XTextProperty* c,XTextProperty* d,char** e,целое f,XSizeHints* g,XWMHints* h,XClassHint* i))
SDL_X11_SYM(Status,XSetWMProtocols,(Display* a,Window b,Atom* c,целое d))
SDL_X11_SYM(целое,XStoreColors,(Display* a,Colormap b,XColor* c,целое d))
SDL_X11_SYM(целое,XStoreName,(Display* a,Window b,_Xconst char* c))
SDL_X11_SYM(Status,XStringListToTextProperty,(char** a,целое b,XTextProperty* c))
SDL_X11_SYM(целое,XSync,(Display* a,Bool b))
SDL_X11_SYM(целое,XTextExtents,(XFontStruct* a,_Xconst char* b,целое c,целое* d,целое* e,целое* f,XCharStruct* g))
SDL_X11_SYM(Bool,XTranslateCoordinates,(Display *a,Window b,Window c,целое d,целое e,целое* f,целое* g,Window* h))
SDL_X11_SYM(целое,XUndefineCursor,(Display* a,Window b))
SDL_X11_SYM(целое,XUngrabKeyboard,(Display* a,Time b))
SDL_X11_SYM(целое,XUngrabPointer,(Display* a,Time b))
SDL_X11_SYM(целое,XUngrabServer,(Display* a))
SDL_X11_SYM(целое,XUninstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(целое,XUnloadFont,(Display* a,Font b))
SDL_X11_SYM(целое,XWarpPointer,(Display* a,Window b,Window c,целое d,целое e,unsigned целое f,unsigned целое g,целое h,целое i))
SDL_X11_SYM(целое,XWindowEvent,(Display* a,Window b,long c,XEvent* d))
SDL_X11_SYM(Status,XWithdrawWindow,(Display* a,Window b,целое c))
SDL_X11_SYM(VisualID,XVisualIDFromVisual,(Visual* a))
SDL_X11_SYM(char*,XGetDefault,(Display* a,_Xconst char* b, _Xconst char* c))
SDL_X11_SYM(Bool,XQueryExtension,(Display* a,_Xconst char* b,целое* c,целое* d,целое* e))
SDL_X11_SYM(char *,XDisplayString,(Display* a))
SDL_X11_SYM(целое,XGetErrorText,(Display* a,целое b,char* c,целое d))
SDL_X11_SYM(void,_XEatData,(Display* a,unsigned long b))
SDL_X11_SYM(void,_XFlush,(Display* a))
SDL_X11_SYM(void,_XFlushGCCache,(Display* a,GC b))
SDL_X11_SYM(целое,_XRead,(Display* a,char* b,long c))
SDL_X11_SYM(void,_XReadPad,(Display* a,char* b,long c))
SDL_X11_SYM(void,_XSend,(Display* a,_Xconst char* b,long c))
SDL_X11_SYM(Status,_XReply,(Display* a,xReply* b,целое c,Bool d))
SDL_X11_SYM(unsigned long,_XSetLastRequestRead,(Display* a,xGenericReply* b))
SDL_X11_SYM(SDL_X11_XSynchronizeRetType,XSynchronize,(Display* a,Bool b))
SDL_X11_SYM(SDL_X11_XESetWireToEventRetType,XESetWireToEvent,(Display* a,целое b,SDL_X11_XESetWireToEventRetType c))
SDL_X11_SYM(SDL_X11_XESetEventToWireRetType,XESetEventToWire,(Display* a,целое b,SDL_X11_XESetEventToWireRetType c))
SDL_X11_SYM(void,XRefreshKeyboardMapping,(XMappingEvent *a))
SDL_X11_SYM(целое,XQueryTree,(Display* a,Window b,Window* c,Window* d,Window** e,unsigned целое* f))
SDL_X11_SYM(Bool,XSupportsLocale,(void))
SDL_X11_SYM(Status,XmbTextListToTextProperty,(Display* a,char** b,целое c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(Region,XCreateRegion,(void))
SDL_X11_SYM(целое,XUnionRectWithRegion,(XRectangle *a, Region b, Region c))
SDL_X11_SYM(void,XDestroyRegion,(Region))
SDL_X11_SYM(void,XrmInitialize,(void))
SDL_X11_SYM(char*,XResourceManagerString,(Display *display))
SDL_X11_SYM(XrmDatabase,XrmGetStringDatabase,(char *data))
SDL_X11_SYM(void,XrmDestroyDatabase,(XrmDatabase db))
SDL_X11_SYM(Bool,XrmGetResource,(XrmDatabase db, char* str_name, char* str_class, char **str_type_return, XrmValue *))
SDL_X11_SYM(целое,XGetPointerMapping,(Display *a, unsigned char *b, unsigned целое c))

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
SDL_X11_MODULE(XFIXES)
SDL_X11_SYM(PointerBarrier, XFixesCreatePointerBarrier, (Display* a, Window b, целое c, целое d, целое e, целое f, целое g, целое h, целое *i))
SDL_X11_SYM(void, XFixesDestroyPointerBarrier, (Display* a, PointerBarrier b))
SDL_X11_SYM(целое, XIBarrierReleasePointer,(Display* a,  целое b, PointerBarrier c, BarrierEventID d)) // this is actually Xinput2
SDL_X11_SYM(Status, XFixesQueryVersion,(Display* a, целое* b, целое* c))
SDL_X11_SYM(Status, XFixesSelectSelectionInput, (Display* a, Window b, Atom c, unsigned long d))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
SDL_X11_MODULE(XSYNC)
SDL_X11_SYM(Status, XSyncQueryExtension, (Display* a, целое* b, целое* c))
SDL_X11_SYM(Status, XSyncInitialize, (Display* a, целое* b, целое* c))
SDL_X11_SYM(XSyncCounter, XSyncCreateCounter, (Display* a, XSyncValue b))
SDL_X11_SYM(Status, XSyncDestroyCounter, (Display* a, XSyncCounter b))
SDL_X11_SYM(Status, XSyncSetCounter, (Display* a, XSyncCounter b, XSyncValue c))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XTEST
SDL_X11_MODULE(XTEST)
SDL_X11_SYM(Status, XTestQueryExtension, (Display* a, целое* b, целое* c))
SDL_X11_SYM(целое, XTestFakeMotionEvent, (Display* a, целое b, целое c, целое d, unsigned long e))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
SDL_X11_SYM(Bool,XGetEventData,(Display* a,XGenericEventCookie* b))
SDL_X11_SYM(void,XFreeEventData,(Display* a,XGenericEventCookie* b))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
SDL_X11_SYM(Bool,XkbQueryExtension,(Display* a,целое * b,целое * c,целое * d,целое * e, целое *f))
SDL_X11_SYM(KeySym,XkbKeycodeToKeysym,(Display* a, KeyCode b, unsigned целое c, unsigned целое d))
SDL_X11_SYM(Bool,XkbSelectEvents,(Display* a, unsigned целое b, unsigned целое c, unsigned long d))
SDL_X11_SYM(Bool,XkbSelectEventDetails,(Display* a, unsigned целое b, unsigned целое c, unsigned long d, unsigned long e))
SDL_X11_SYM(Status,XkbGetNames,(Display *a, unsigned целое b, XkbDescPtr c))
SDL_X11_SYM(Status,XkbGetState,(Display* a,unsigned целое b,XkbStatePtr c))
SDL_X11_SYM(Status,XkbGetUpdatedMap,(Display* a,unsigned целое b,XkbDescPtr c))
SDL_X11_SYM(XkbDescPtr,XkbGetMap,(Display* a,unsigned целое b,unsigned целое c))
SDL_X11_SYM(void,XkbFreeClientMap,(XkbDescPtr a,unsigned целое b, Bool c))
SDL_X11_SYM(void,XkbFreeKeyboard,(XkbDescPtr a,unsigned целое b, Bool c))
SDL_X11_SYM(Status,XkbRefreshKeyboardMapping,(XkbMapNotifyEvent *a))
SDL_X11_SYM(Bool,XkbSetDetectableAutoRepeat,(Display* a, Bool b, Bool* c))
#endif

#ifdef X_HAVE_UTF8_STRING
SDL_X11_MODULE(UTF8)
SDL_X11_SYM(целое,Xutf8TextListToTextProperty,(Display* a,char** b,целое c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(целое,Xutf8LookupString,(XIC a,XKeyPressedEvent* b,char* c,целое d,KeySym* e,Status* f))
SDL_X11_SYM(XIC,XCreateIC,(XIM,...))
SDL_X11_SYM(void,XDestroyIC,(XIC a))
SDL_X11_SYM(char*,XGetICValues,(XIC,...))
SDL_X11_SYM(char*,XSetICValues,(XIC,...))
SDL_X11_SYM(XVaNestedList,XVaCreateNestedList,(целое, ...))
SDL_X11_SYM(void,XSetICFocus,(XIC a))
SDL_X11_SYM(void,XUnsetICFocus,(XIC a))
SDL_X11_SYM(XIM,XOpenIM,(Display* a,struct _XrmHashBucketRec* b,char* c,char* d))
SDL_X11_SYM(Status,XCloseIM,(XIM a))
SDL_X11_SYM(char*, XSetIMValues,(XIM,...))
SDL_X11_SYM(Bool,XRegisterIMInstantiateCallback,(Display*,struct _XrmHashBucketRec*,char*,char*,XIDProc,XPointer))
SDL_X11_SYM(Bool,XUnregisterIMInstantiateCallback,(Display*,struct _XrmHashBucketRec*,char*,char*,XIDProc,XPointer))
SDL_X11_SYM(void,Xutf8DrawString,(Display *a, Drawable b, XFontSet c, GC d, целое e, целое f, _Xconst char *g, целое h))
SDL_X11_SYM(целое,Xutf8TextExtents,(XFontSet a, _Xconst char* b, целое c, XRectangle* d, XRectangle* e))
SDL_X11_SYM(char*,XSetLocaleModifiers,(const char *a))
SDL_X11_SYM(char*,Xutf8ResetIC,(XIC a))
SDL_X11_SYM(XFontSetExtents*,XExtentsOfFontSet,(XFontSet a))
SDL_X11_SYM(Bool,XContextDependentDrawing,(XFontSet a))
#endif


#ifndef NO_SHARED_MEMORY
SDL_X11_MODULE(SHM)
SDL_X11_SYM(Status,XShmAttach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(Status,XShmDetach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(Status,XShmPutImage,(Display* a,Drawable b,GC c,XImage* d,целое e,целое f,целое g,целое h,unsigned целое i,unsigned целое j,Bool k))
SDL_X11_SYM(Status,XShmGetImage,(Display* a,Drawable b,XImage *c,целое d, целое e, unsigned long f))
SDL_X11_SYM(XImage*,XShmCreateImage,(Display* a,Visual* b,unsigned целое c,целое d,char* e,XShmSegmentInfo* f,unsigned целое g,unsigned целое h))
SDL_X11_SYM(Pixmap,XShmCreatePixmap,(Display *a,Drawable b,char* c,XShmSegmentInfo* d, unsigned целое e, unsigned целое f, unsigned целое g))
SDL_X11_SYM(Bool,XShmQueryExtension,(Display* a))
SDL_X11_SYM(Status,XShmQueryVersion,(Display* a, целое *b, целое *c, Bool *d))
SDL_X11_SYM(целое,XShmPixmapFormat,(Display* a))
#endif

/*
 * Not required...these only exist in code in headers on some 64-bit platforms,
 *  and are removed via macros elsewhere, so it's safe for them to be missing.
 */
#ifdef LONG64
SDL_X11_MODULE(IO_32BIT)
SDL_X11_SYM(целое,_XData32,(Display *dpy,register _Xconst long *data,unsigned len))
SDL_X11_SYM(void,_XRead32,(Display *dpy,register long *data,long len))
#endif

/*
 * These only show up on some variants of Unix.
 */
#ifdef SDL_PLATFORM_OSF
SDL_X11_MODULE(OSF_ENTRY_POINTS)
SDL_X11_SYM(void,_SmtBufferOverflow,(Display *dpy,register smtDisplayPtr p))
SDL_X11_SYM(void,_SmtIpError,(Display *dpy,register smtDisplayPtr p,целое i))
SDL_X11_SYM(целое,ipAllocateData,(ChannelPtr a,IPCard b,IPDataPtr * c))
SDL_X11_SYM(целое,ipUnallocateAndSendData,(ChannelPtr a,IPCard b))
#endif

// XCursor support
#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
SDL_X11_MODULE(XCURSOR)
SDL_X11_SYM(XcursorImage*,XcursorImageCreate,(целое a,целое b))
SDL_X11_SYM(XcursorImages*,XcursorImagesCreate,(целое a))
SDL_X11_SYM(void,XcursorImageDestroy,(XcursorImage *a))
SDL_X11_SYM(void,XcursorImagesDestroy,(XcursorImages *a))
SDL_X11_SYM(Cursor,XcursorImageLoadCursor,(Display *a,const XcursorImage *b))
SDL_X11_SYM(Cursor,XcursorImagesLoadCursor,(Display *a,const XcursorImages *b))
SDL_X11_SYM(Cursor,XcursorLibraryLoadCursor,(Display *a, const char *b))
#endif

// Xdbe support
#ifdef SDL_VIDEO_DRIVER_X11_XDBE
SDL_X11_MODULE(XDBE)
SDL_X11_SYM(Status,XdbeQueryExtension,(Display *dpy,целое *major_version_return,целое *minor_version_return))
SDL_X11_SYM(XdbeBackBuffer,XdbeAllocateBackBufferName,(Display *dpy,Window window,XdbeSwapAction swap_action))
SDL_X11_SYM(Status,XdbeDeallocateBackBufferName,(Display *dpy,XdbeBackBuffer buffer))
SDL_X11_SYM(Status,XdbeSwapBuffers,(Display *dpy,XdbeSwapInfo *swap_info,целое num_windows))
SDL_X11_SYM(Status,XdbeBeginIdiom,(Display *dpy))
SDL_X11_SYM(Status,XdbeEndIdiom,(Display *dpy))
SDL_X11_SYM(XdbeScreenVisualInfo*,XdbeGetVisualInfo,(Display *dpy,Drawable *screen_specifiers,целое *num_screens))
SDL_X11_SYM(void,XdbeFreeVisualInfo,(XdbeScreenVisualInfo *visual_info))
SDL_X11_SYM(XdbeBackBufferAttributes*,XdbeGetBackBufferAttributes,(Display *dpy,XdbeBackBuffer buffer))
#endif

// XInput2 support for multiple mice, tablets, etc.
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
SDL_X11_MODULE(XINPUT2)
SDL_X11_SYM(XIDeviceInfo*,XIQueryDevice,(Display *a,целое b,целое *c))
SDL_X11_SYM(void,XIFreeDeviceInfo,(XIDeviceInfo *a))
SDL_X11_SYM(целое,XISelectEvents,(Display *a,Window b,XIEventMask *c,целое d))
SDL_X11_SYM(целое,XIGrabTouchBegin,(Display *a,целое b,Window c,целое d,XIEventMask *e,целое f,XIGrabModifiers *g))
SDL_X11_SYM(целое,XIUngrabTouchBegin, (Display *a,целое b,Window c, целое d,XIGrabModifiers *e))
SDL_X11_SYM(Status,XIQueryVersion,(Display *a,целое *b,целое *c))
SDL_X11_SYM(XIEventMask*,XIGetSelectedEvents,(Display *a,Window b,целое *c))
SDL_X11_SYM(Bool,XIGetClientPointer,(Display *a,Window b,целое *c))
SDL_X11_SYM(Bool,XIWarpPointer,(Display *a,целое b,Window c,Window d,double e,double f,целое g,целое h,double i,double j))
SDL_X11_SYM(Status,XIGetProperty,(Display *a,целое b,Atom c,long d,long e,Bool f, Atom g, Atom *h, целое *i, unsigned long *j, unsigned long *k, unsigned char **l))
#endif

// XRandR support
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
SDL_X11_MODULE(XRANDR)
SDL_X11_SYM(Status,XRRQueryVersion,(Display *dpy,целое *major_versionp,целое *minor_versionp))
SDL_X11_SYM(Bool,XRRQueryExtension,(Display *dpy,целое *event_base_return,целое *error_base_return))
SDL_X11_SYM(XRRScreenConfiguration *,XRRGetScreenInfo,(Display *dpy,Drawable draw))
SDL_X11_SYM(SizeID,XRRConfigCurrentConfiguration,(XRRScreenConfiguration *config,Rotation *rotation))
SDL_X11_SYM(short,XRRConfigCurrentRate,(XRRScreenConfiguration *config))
SDL_X11_SYM(short *,XRRConfigRates,(XRRScreenConfiguration *config,целое sizeID,целое *nrates))
SDL_X11_SYM(XRRScreenSize *,XRRConfigSizes,(XRRScreenConfiguration *config,целое *nsizes))
SDL_X11_SYM(Status,XRRSetScreenConfigAndRate,(Display *dpy,XRRScreenConfiguration *config,Drawable draw,целое size_index,Rotation rotation,short rate,Time timestamp))
SDL_X11_SYM(void,XRRFreeScreenConfigInfo,(XRRScreenConfiguration *config))
SDL_X11_SYM(void,XRRSetScreenSize,(Display *dpy, Window window,целое width, целое height,целое mmWidth, целое mmHeight))
SDL_X11_SYM(Status,XRRGetScreenSizeRange,(Display *dpy, Window window,целое *minWidth, целое *minHeight, целое *maxWidth, целое *maxHeight))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResources,(Display *dpy, Window window))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResourcesCurrent,(Display *dpy, Window window))
SDL_X11_SYM(void,XRRFreeScreenResources,(XRRScreenResources *resources))
SDL_X11_SYM(XRROutputInfo *,XRRGetOutputInfo,(Display *dpy, XRRScreenResources *resources, RROutput output))
SDL_X11_SYM(void,XRRFreeOutputInfo,(XRROutputInfo *outputInfo))
SDL_X11_SYM(XRRCrtcInfo *,XRRGetCrtcInfo,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc))
SDL_X11_SYM(void,XRRFreeCrtcInfo,(XRRCrtcInfo *crtcInfo))
SDL_X11_SYM(Status,XRRSetCrtcConfig,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc, Time timestamp, целое x, целое y, RRMode mode, Rotation rotation, RROutput *outputs, целое noutputs))
SDL_X11_SYM(Atom*,XRRListOutputProperties,(Display *dpy, RROutput output, целое *nprop))
SDL_X11_SYM(XRRPropertyInfo*,XRRQueryOutputProperty,(Display *dpy,RROutput output, Atom property))
SDL_X11_SYM(целое,XRRGetOutputProperty,(Display *dpy,RROutput output, Atom property, long offset, long length, Bool _delete, Bool pending, Atom req_type, Atom *actual_type, целое *actual_format, unsigned long *nitems, unsigned long *bytes_after, unsigned char **prop))
SDL_X11_SYM(RROutput,XRRGetOutputPrimary,(Display *dpy,Window window))
SDL_X11_SYM(void,XRRSelectInput,(Display *dpy, Window window, целое mask))
SDL_X11_SYM(Status,XRRGetCrtcTransform,(Display *dpy,RRCrtc crtc,XRRCrtcTransformAttributes **attributes))
#endif

// MIT-SCREEN-SAVER support
#ifdef SDL_VIDEO_DRIVER_X11_XSCRNSAVER
SDL_X11_MODULE(XSS)
SDL_X11_SYM(Bool,XScreenSaverQueryExtension,(Display *dpy,целое *event_base,целое *error_base))
SDL_X11_SYM(Status,XScreenSaverQueryVersion,(Display *dpy,целое *major_versionp,целое *minor_versionp))
SDL_X11_SYM(void,XScreenSaverSuspend,(Display *dpy,Bool suspend))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XSHAPE
SDL_X11_MODULE(XSHAPE)
SDL_X11_SYM(void,XShapeCombineMask,(Display *dpy,Window dest,целое dest_kind,целое x_off,целое y_off,Pixmap src,целое op))
SDL_X11_SYM(void,XShapeCombineRegion,(Display *a,Window b,целое c,целое d,целое e,Region f,целое g))
#endif

#undef SDL_X11_MODULE
#undef SDL_X11_SYM

/* *INDENT-ON* */ // clang-format on

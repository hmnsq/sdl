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
SDL_X11_SYM(XSizeHints*,XAllocSizeHints,(வெறுமை))
SDL_X11_SYM(XWMHints*,XAllocWMHints,(வெறுமை))
SDL_X11_SYM(XClassHint*,XAllocClassHint,(வெறுமை))
SDL_X11_SYM(முழு,XChangePointerControl,(Display* a,Bool b,Bool c,முழு d,முழு e,முழு f))
SDL_X11_SYM(முழு,XChangeProperty,(Display* a,Window b,Atom c,Atom d,முழு e,முழு f,_Xconst unsigned எழுத்து* g,முழு h))
SDL_X11_SYM(Bool,XCheckIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(முழு,XClearWindow,(Display* a,Window b))
SDL_X11_SYM(முழு,XCloseDisplay,(Display* a))
SDL_X11_SYM(முழு,XConvertSelection,(Display* a,Atom b,Atom c,Atom d,Window e,Time f))
SDL_X11_SYM(Pixmap,XCreateBitmapFromData,(Display *dpy,Drawable d,_Xconst எழுத்து *data,unsigned முழு width,unsigned முழு height))
SDL_X11_SYM(Colormap,XCreateColormap,(Display* a,Window b,Visual* c,முழு d))
SDL_X11_SYM(Cursor,XCreatePixmapCursor,(Display* a,Pixmap b,Pixmap c,XColor* d,XColor* e,unsigned முழு f,unsigned முழு g))
SDL_X11_SYM(Cursor,XCreatePixmap,(Display* a,Drawable b,unsigned முழு d,unsigned முழு e,unsigned முழு f))
SDL_X11_SYM(Cursor,XCreateFontCursor,(Display* a,unsigned முழு b))
SDL_X11_SYM(XFontSet,XCreateFontSet,(Display* a, _Xconst எழுத்து* b, எழுத்து*** c, முழு* d, எழுத்து** e))
SDL_X11_SYM(GC,XCreateGC,(Display* a,Drawable b,unsigned long c,XGCValues* d))
SDL_X11_SYM(வெறுமை,XSetFont,(Display* a,GC b,Font c))
SDL_X11_SYM(Status,XAllocColor,(Display *a, Colormap b, XColor *c))
SDL_X11_SYM(XImage*,XCreateImage,(Display* a,Visual* b,unsigned முழு c,முழு d,முழு e,எழுத்து* f,unsigned முழு g,unsigned முழு h,முழு i,முழு j))
SDL_X11_SYM(Window,XCreateWindow,(Display* a,Window b,முழு c,முழு d,unsigned முழு e,unsigned முழு f,unsigned முழு g,முழு h,unsigned முழு i,Visual* j,unsigned long k,XSetWindowAttributes* l))
SDL_X11_SYM(வெறுமை,XCopyArea,(Display *a, Drawable b, Drawable c, GC d, முழு e, முழு f, unsigned முழு g, unsigned முழு h, முழு i, முழு j))
SDL_X11_SYM(முழு,XDefineCursor,(Display* a,Window b,Cursor c))
SDL_X11_SYM(முழு,XDeleteProperty,(Display* a,Window b,Atom c))
SDL_X11_SYM(முழு,XDestroyWindow,(Display* a,Window b))
SDL_X11_SYM(முழு,XDisplayKeycodes,(Display* a,முழு* b,முழு* c))
SDL_X11_SYM(முழு,XDrawRectangle,(Display* a,Drawable b,GC c,முழு d,முழு e,unsigned முழு f,unsigned முழு g))
SDL_X11_SYM(முழு,XFontsOfFontSet,(XFontSet a,XFontStruct ***b,எழுத்து ***c))
SDL_X11_SYM(முழு,XFillArc,(Display* a,Drawable b,GC c,முழு d,முழு e,unsigned முழு f,unsigned முழு g, முழு h, முழு i))
SDL_X11_SYM(எழுத்து*,XDisplayName,(_Xconst எழுத்து* a))
SDL_X11_SYM(முழு,XDrawString,(Display* a,Drawable b,GC c,முழு d,முழு e,_Xconst எழுத்து* f,முழு g))
SDL_X11_SYM(முழு,XEventsQueued,(Display* a,முழு b))
SDL_X11_SYM(முழு,XFillRectangle,(Display* a,Drawable b,GC c,முழு d,முழு e,unsigned முழு f,unsigned முழு g))
SDL_X11_SYM(Bool,XFilterEvent,(XEvent *event,Window w))
SDL_X11_SYM(முழு,XFlush,(Display* a))
SDL_X11_SYM(முழு,XFree,(வெறுமை*a))
SDL_X11_SYM(முழு,XFreeCursor,(Display* a,Cursor b))
SDL_X11_SYM(வெறுமை,XFreeFontSet,(Display* a, XFontSet b))
SDL_X11_SYM(முழு,XFreeGC,(Display* a,GC b))
SDL_X11_SYM(முழு,XFreeFont,(Display* a, XFontStruct* b))
SDL_X11_SYM(முழு,XFreeModifiermap,(XModifierKeymap* a))
SDL_X11_SYM(முழு,XFreePixmap,(Display* a,Pixmap b))
SDL_X11_SYM(முழு,XFreeColormap,(Display* a,Colormap b))
SDL_X11_SYM(வெறுமை,XFreeStringList,(எழுத்து** a))
SDL_X11_SYM(எழுத்து*,XGetAtomName,(Display *a,Atom b))
SDL_X11_SYM(முழு,XGet_உள்ளீடு_Focus,(Display *a,Window *b,முழு *c))
SDL_X11_SYM(சாவி_Sym*,XGetKeyboardMapping,(Display *a, சாவி_Code_2 b, முழு c, முழு *d))
SDL_X11_SYM(முழு,XGetErrorDatabaseText,(Display* a,_Xconst எழுத்து* b,_Xconst எழுத்து* c,_Xconst எழுத்து* d,எழுத்து* e,முழு f))
SDL_X11_SYM(XModifierKeymap*,XGetModifierMapping,(Display* a))
SDL_X11_SYM(முழு,XGetPointerControl,(Display* a,முழு* b,முழு* c,முழு* d))
SDL_X11_SYM(Window,XGetSelectionOwner,(Display* a,Atom b))
SDL_X11_SYM(XVisualInfo*,XGetVisualInfo,(Display* a,long b,XVisualInfo* c,முழு* d))
SDL_X11_SYM(Status,XGetWindowAttributes,(Display* a,Window b,XWindowAttributes* c))
SDL_X11_SYM(முழு,XGetWindowProperty,(Display* a,Window b,Atom c,long d,long e,Bool f,Atom g,Atom* h,முழு* i,unsigned long* j,unsigned long *k,unsigned எழுத்து **l))
SDL_X11_SYM(XWMHints*,XGetWMHints,(Display* a,Window b))
SDL_X11_SYM(Status,XGetWMNormalHints,(Display *a,Window b, XSizeHints *c, long *d))
SDL_X11_SYM(முழு,XIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(முழு,XGrabKeyboard,(Display* a,Window b,Bool c,முழு d,முழு e,Time f))
SDL_X11_SYM(முழு,XGrabPointer,(Display* a,Window b,Bool c,unsigned முழு d,முழு e,முழு f,Window g,Cursor h,Time i))
SDL_X11_SYM(முழு,XGrabServer,(Display* a))
SDL_X11_SYM(Status,XIconifyWindow,(Display* a,Window b,முழு c))
SDL_X11_SYM(சாவி_Code_2,XKeysymToKeycode,(Display* a,சாவி_Sym b))
SDL_X11_SYM(எழுத்து*,XKeysymToString,(சாவி_Sym a))
SDL_X11_SYM(முழு,XInstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(Atom,XInternAtom,(Display* a,_Xconst எழுத்து* b,Bool c))
SDL_X11_SYM(XPixmap_Format_மதிப்புகள்*,XListPixmapFormats,(Display* a,முழு* b))
SDL_X11_SYM(XFontStruct*,XLoadQueryFont,(Display* a,_Xconst எழுத்து* b))
SDL_X11_SYM(சாவி_Sym,XLookupKeysym,(XKeyEvent* a,முழு b))
SDL_X11_SYM(முழு,XLookupString,(XKeyEvent* a,எழுத்து* b,முழு c,சாவி_Sym* d,XComposeStatus* e))
SDL_X11_SYM(முழு,XMapRaised,(Display* a,Window b))
SDL_X11_SYM(Status,XMatchVisualInfo,(Display* a,முழு b,முழு c,முழு d,XVisualInfo* e))
SDL_X11_SYM(முழு,XMissingExtension,(Display* a,_Xconst எழுத்து* b))
SDL_X11_SYM(முழு,XMoveWindow,(Display* a,Window b,முழு c,முழு d))
SDL_X11_SYM(Display*,XOpenDisplay,(_Xconst எழுத்து* a))
SDL_X11_SYM(Status,XInitThreads,(வெறுமை))
SDL_X11_SYM(முழு,XPeekEvent,(Display* a,XEvent* b))
SDL_X11_SYM(முழு,XPending,(Display* a))
SDL_X11_SYM(XImage*,XGetImage,(Display* a,Drawable b,முழு c, முழு d,unsigned முழு e,unsigned முழு f,unsigned long g,முழு h))
SDL_X11_SYM(முழு,XPutImage,(Display* a,Drawable b,GC c,XImage* d,முழு e,முழு f,முழு g,முழு h,unsigned முழு i,unsigned முழு j))
SDL_X11_SYM(முழு,XQueryKeymap,(Display* a,எழுத்து b[32]))
SDL_X11_SYM(Bool,XQueryPointer,(Display* a,Window b,Window* c,Window* d,முழு* e,முழு* f,முழு* g,முழு* h,unsigned முழு* i))
SDL_X11_SYM(முழு,XRaiseWindow,(Display* a,Window b))
SDL_X11_SYM(முழு,XReparentWindow,(Display* a,Window b,Window c,முழு d,முழு e))
SDL_X11_SYM(முழு,XResetScreenSaver,(Display* a))
SDL_X11_SYM(முழு,XResizeWindow,(Display* a,Window b,unsigned முழு c,unsigned முழு d))
SDL_X11_SYM(முழு,XScreen_எண்_Of_Screen,(Screen* a))
SDL_X11_SYM(முழு,XSelect_உள்ளீடு,(Display* a,Window b,long c))
SDL_X11_SYM(Status,XSendEvent,(Display* a,Window b,Bool c,long d,XEvent* e))
SDL_X11_SYM(XErrorHandler,XSetErrorHandler,(XErrorHandler a))
SDL_X11_SYM(முழு,XSetForeground,(Display* a,GC b,unsigned long c))
SDL_X11_SYM(XIOErrorHandler,XSetIOErrorHandler,(XIOErrorHandler a))
SDL_X11_SYM(முழு,XSet_உள்ளீடு_Focus,(Display *a,Window b,முழு c,Time d))
SDL_X11_SYM(முழு,XSetSelectionOwner,(Display* a,Atom b,Window c,Time d))
SDL_X11_SYM(முழு,XSetTransientForHint,(Display* a,Window b,Window c))
SDL_X11_SYM(வெறுமை,XSetTextProperty,(Display* a,Window b,XTextProperty* c,Atom d))
SDL_X11_SYM(முழு,XSetWindowBackground,(Display* a,Window b,unsigned long c))
SDL_X11_SYM(வெறுமை,XSetWMHints,(Display* a,Window b,XWMHints* c))
SDL_X11_SYM(வெறுமை,XSetWMNormalHints,(Display* a,Window b,XSizeHints* c))
SDL_X11_SYM(வெறுமை,XSetWMProperties,(Display* a,Window b,XTextProperty* c,XTextProperty* d,எழுத்து** e,முழு f,XSizeHints* g,XWMHints* h,XClassHint* i))
SDL_X11_SYM(Status,XSetWMProtocols,(Display* a,Window b,Atom* c,முழு d))
SDL_X11_SYM(முழு,XStoreColors,(Display* a,Colormap b,XColor* c,முழு d))
SDL_X11_SYM(முழு,XStoreName,(Display* a,Window b,_Xconst எழுத்து* c))
SDL_X11_SYM(Status,XStringListToTextProperty,(எழுத்து** a,முழு b,XTextProperty* c))
SDL_X11_SYM(முழு,XSync,(Display* a,Bool b))
SDL_X11_SYM(முழு,XTextExtents,(XFontStruct* a,_Xconst எழுத்து* b,முழு c,முழு* d,முழு* e,முழு* f,XCharStruct* g))
SDL_X11_SYM(Bool,XTranslateCoordinates,(Display *a,Window b,Window c,முழு d,முழு e,முழு* f,முழு* g,Window* h))
SDL_X11_SYM(முழு,XUndefineCursor,(Display* a,Window b))
SDL_X11_SYM(முழு,XUngrabKeyboard,(Display* a,Time b))
SDL_X11_SYM(முழு,XUngrabPointer,(Display* a,Time b))
SDL_X11_SYM(முழு,XUngrabServer,(Display* a))
SDL_X11_SYM(முழு,XUninstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(முழு,XUnloadFont,(Display* a,Font b))
SDL_X11_SYM(முழு,XWarpPointer,(Display* a,Window b,Window c,முழு d,முழு e,unsigned முழு f,unsigned முழு g,முழு h,முழு i))
SDL_X11_SYM(முழு,XWindowEvent,(Display* a,Window b,long c,XEvent* d))
SDL_X11_SYM(Status,XWithdrawWindow,(Display* a,Window b,முழு c))
SDL_X11_SYM(VisualID,XVisualIDFromVisual,(Visual* a))
SDL_X11_SYM(எழுத்து*,XGetDefault,(Display* a,_Xconst எழுத்து* b, _Xconst எழுத்து* c))
SDL_X11_SYM(Bool,XQueryExtension,(Display* a,_Xconst எழுத்து* b,முழு* c,முழு* d,முழு* e))
SDL_X11_SYM(எழுத்து *,XDisplayString,(Display* a))
SDL_X11_SYM(முழு,XGetErrorText,(Display* a,முழு b,எழுத்து* c,முழு d))
SDL_X11_SYM(வெறுமை,_XEatData,(Display* a,unsigned long b))
SDL_X11_SYM(வெறுமை,_XFlush,(Display* a))
SDL_X11_SYM(வெறுமை,_XFlushGCCache,(Display* a,GC b))
SDL_X11_SYM(முழு,_XRead,(Display* a,எழுத்து* b,long c))
SDL_X11_SYM(வெறுமை,_XReadPad,(Display* a,எழுத்து* b,long c))
SDL_X11_SYM(வெறுமை,_XSend,(Display* a,_Xconst எழுத்து* b,long c))
SDL_X11_SYM(Status,_XReply,(Display* a,xReply* b,முழு c,Bool d))
SDL_X11_SYM(unsigned long,_XSetLastRequestRead,(Display* a,xGenericReply* b))
SDL_X11_SYM(SDL_X11_XSynchronizeRetType,XSynchronize,(Display* a,Bool b))
SDL_X11_SYM(SDL_X11_XESetWireToEventRetType,XESetWireToEvent,(Display* a,முழு b,SDL_X11_XESetWireToEventRetType c))
SDL_X11_SYM(SDL_X11_XESetEventToWireRetType,XESetEventToWire,(Display* a,முழு b,SDL_X11_XESetEventToWireRetType c))
SDL_X11_SYM(வெறுமை,XRefreshKeyboardMapping,(XMappingEvent *a))
SDL_X11_SYM(முழு,XQuery_மரம்,(Display* a,Window b,Window* c,Window* d,Window** e,unsigned முழு* f))
SDL_X11_SYM(Bool,XSupportsLocale,(வெறுமை))
SDL_X11_SYM(Status,XmbTextListToTextProperty,(Display* a,எழுத்து** b,முழு c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(Region,XCreateRegion,(வெறுமை))
SDL_X11_SYM(முழு,XUnionRectWithRegion,(XRectangle *a, Region b, Region c))
SDL_X11_SYM(வெறுமை,XDestroyRegion,(Region))
SDL_X11_SYM(வெறுமை,XrmInitialize,(வெறுமை))
SDL_X11_SYM(எழுத்து*,XResourceManagerString,(Display *display))
SDL_X11_SYM(XrmDatabase,XrmGetStringDatabase,(எழுத்து *data))
SDL_X11_SYM(வெறுமை,XrmDestroyDatabase,(XrmDatabase db))
SDL_X11_SYM(Bool,XrmGetResource,(XrmDatabase db, எழுத்து* str_name, எழுத்து* str_class, எழுத்து **str_type_return, Xrm_மதிப்பு *))
SDL_X11_SYM(முழு,XGetPointerMapping,(Display *a, unsigned எழுத்து *b, unsigned முழு c))

#ifdef SDL_VIDEO_DRIVER_X11_XFIXES
SDL_X11_MODULE(XFIXES)
SDL_X11_SYM(PointerBarrier, XFixesCreatePointerBarrier, (Display* a, Window b, முழு c, முழு d, முழு e, முழு f, முழு g, முழு h, முழு *i))
SDL_X11_SYM(வெறுமை, XFixesDestroyPointerBarrier, (Display* a, PointerBarrier b))
SDL_X11_SYM(முழு, XIBarrierReleasePointer,(Display* a,  முழு b, PointerBarrier c, BarrierEventID d)) // this is actually Xinput2
SDL_X11_SYM(Status, XFixesQueryVersion,(Display* a, முழு* b, முழு* c))
SDL_X11_SYM(Status, XFixes_Select_Selection_உள்ளீடு, (Display* a, Window b, Atom c, unsigned long d))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XSYNC
SDL_X11_MODULE(XSYNC)
SDL_X11_SYM(Status, XSyncQueryExtension, (Display* a, முழு* b, முழு* c))
SDL_X11_SYM(Status, XSyncInitialize, (Display* a, முழு* b, முழு* c))
SDL_X11_SYM(XSyncCounter, XSyncCreateCounter, (Display* a, XSync_மதிப்பு b))
SDL_X11_SYM(Status, XSyncDestroyCounter, (Display* a, XSyncCounter b))
SDL_X11_SYM(Status, XSyncSetCounter, (Display* a, XSyncCounter b, XSync_மதிப்பு c))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XTEST
SDL_X11_MODULE(XTEST)
SDL_X11_SYM(Status, XTestQueryExtension, (Display* a, முழு* b, முழு* c))
SDL_X11_SYM(முழு, XTestFakeMotionEvent, (Display* a, முழு b, முழு c, முழு d, unsigned long e))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
SDL_X11_SYM(Bool,XGetEventData,(Display* a,XGenericEventCookie* b))
SDL_X11_SYM(வெறுமை,XFreeEventData,(Display* a,XGenericEventCookie* b))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
SDL_X11_SYM(Bool,XkbQueryExtension,(Display* a,முழு * b,முழு * c,முழு * d,முழு * e, முழு *f))
SDL_X11_SYM(சாவி_Sym,XkbKeycodeToKeysym,(Display* a, சாவி_Code_2 b, unsigned முழு c, unsigned முழு d))
SDL_X11_SYM(Bool,XkbSelectEvents,(Display* a, unsigned முழு b, unsigned முழு c, unsigned long d))
SDL_X11_SYM(Bool,XkbSelectEventDetails,(Display* a, unsigned முழு b, unsigned முழு c, unsigned long d, unsigned long e))
SDL_X11_SYM(Status,XkbGetNames,(Display *a, unsigned முழு b, XkbDescPtr c))
SDL_X11_SYM(Status,XkbGetState,(Display* a,unsigned முழு b,XkbStatePtr c))
SDL_X11_SYM(Status,XkbGetUpdatedMap,(Display* a,unsigned முழு b,XkbDescPtr c))
SDL_X11_SYM(XkbDescPtr,XkbGetMap,(Display* a,unsigned முழு b,unsigned முழு c))
SDL_X11_SYM(வெறுமை,XkbFreeClientMap,(XkbDescPtr a,unsigned முழு b, Bool c))
SDL_X11_SYM(வெறுமை,XkbFreeKeyboard,(XkbDescPtr a,unsigned முழு b, Bool c))
SDL_X11_SYM(Status,XkbRefreshKeyboardMapping,(XkbMapNotifyEvent *a))
SDL_X11_SYM(Bool,XkbSetDetectableAutoRepeat,(Display* a, Bool b, Bool* c))
#endif

#ifdef X_HAVE_UTF8_STRING
SDL_X11_MODULE(UTF8)
SDL_X11_SYM(முழு,Xutf8TextListToTextProperty,(Display* a,எழுத்து** b,முழு c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(முழு,Xutf8LookupString,(XIC a,XKeyPressedEvent* b,எழுத்து* c,முழு d,சாவி_Sym* e,Status* f))
SDL_X11_SYM(XIC,XCreateIC,(XIM,...))
SDL_X11_SYM(வெறுமை,XDestroyIC,(XIC a))
SDL_X11_SYM(எழுத்து*,XGetICValues,(XIC,...))
SDL_X11_SYM(எழுத்து*,XSetICValues,(XIC,...))
SDL_X11_SYM(XVaNestedList,XVaCreateNestedList,(முழு, ...))
SDL_X11_SYM(வெறுமை,XSetICFocus,(XIC a))
SDL_X11_SYM(வெறுமை,XUnsetICFocus,(XIC a))
SDL_X11_SYM(XIM,XOpenIM,(Display* a,கட்டமைப்பு _XrmHashBucketRec* b,எழுத்து* c,எழுத்து* d))
SDL_X11_SYM(Status,XCloseIM,(XIM a))
SDL_X11_SYM(எழுத்து*, XSetIMValues,(XIM,...))
SDL_X11_SYM(Bool,XRegisterIMInstantiateCallback,(Display*,கட்டமைப்பு _XrmHashBucketRec*,எழுத்து*,எழுத்து*,XIDProc,XPointer))
SDL_X11_SYM(Bool,XUnregisterIMInstantiateCallback,(Display*,கட்டமைப்பு _XrmHashBucketRec*,எழுத்து*,எழுத்து*,XIDProc,XPointer))
SDL_X11_SYM(வெறுமை,Xutf8DrawString,(Display *a, Drawable b, XFontSet c, GC d, முழு e, முழு f, _Xconst எழுத்து *g, முழு h))
SDL_X11_SYM(முழு,Xutf8TextExtents,(XFontSet a, _Xconst எழுத்து* b, முழு c, XRectangle* d, XRectangle* e))
SDL_X11_SYM(எழுத்து*,XSetLocaleModifiers,(மாறிலி எழுத்து *a))
SDL_X11_SYM(எழுத்து*,Xutf8ResetIC,(XIC a))
SDL_X11_SYM(XFontSetExtents*,XExtentsOfFontSet,(XFontSet a))
SDL_X11_SYM(Bool,XContextDependentDrawing,(XFontSet a))
#endif


#ifndef NO_SHARED_MEMORY
SDL_X11_MODULE(SHM)
SDL_X11_SYM(Status,XShmAttach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(Status,XShmDetach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(Status,XShmPutImage,(Display* a,Drawable b,GC c,XImage* d,முழு e,முழு f,முழு g,முழு h,unsigned முழு i,unsigned முழு j,Bool k))
SDL_X11_SYM(Status,XShmGetImage,(Display* a,Drawable b,XImage *c,முழு d, முழு e, unsigned long f))
SDL_X11_SYM(XImage*,XShmCreateImage,(Display* a,Visual* b,unsigned முழு c,முழு d,எழுத்து* e,XShmSegmentInfo* f,unsigned முழு g,unsigned முழு h))
SDL_X11_SYM(Pixmap,XShmCreatePixmap,(Display *a,Drawable b,எழுத்து* c,XShmSegmentInfo* d, unsigned முழு e, unsigned முழு f, unsigned முழு g))
SDL_X11_SYM(Bool,XShmQueryExtension,(Display* a))
SDL_X11_SYM(Status,XShmQueryVersion,(Display* a, முழு *b, முழு *c, Bool *d))
SDL_X11_SYM(முழு,XShmPixmapFormat,(Display* a))
#endif

/*
 * Not required...these only exist in code in headers on some 64-bit platforms,
 *  and are removed via macros elsewhere, so it's safe for them to be missing.
 */
#ifdef LONG64
SDL_X11_MODULE(IO_32BIT)
SDL_X11_SYM(முழு,_XData32,(Display *dpy,பதிவு _Xconst long *data,unsigned len))
SDL_X11_SYM(வெறுமை,_XRead32,(Display *dpy,பதிவு long *data,long len))
#endif

/*
 * These only show up on some variants of Unix.
 */
#ifdef SDL_PLATFORM_OSF
SDL_X11_MODULE(OSF_ENTRY_POINTS)
SDL_X11_SYM(வெறுமை,_SmtBufferOverflow,(Display *dpy,பதிவு smtDisplayPtr p))
SDL_X11_SYM(வெறுமை,_SmtIpError,(Display *dpy,பதிவு smtDisplayPtr p,முழு i))
SDL_X11_SYM(முழு,ipAllocateData,(ChannelPtr a,IPCard b,IPDataPtr * c))
SDL_X11_SYM(முழு,ipUnallocateAndSendData,(ChannelPtr a,IPCard b))
#endif

// XCursor support
#ifdef SDL_VIDEO_DRIVER_X11_XCURSOR
SDL_X11_MODULE(XCURSOR)
SDL_X11_SYM(XcursorImage*,XcursorImageCreate,(முழு a,முழு b))
SDL_X11_SYM(XcursorImages*,XcursorImagesCreate,(முழு a))
SDL_X11_SYM(வெறுமை,XcursorImageDestroy,(XcursorImage *a))
SDL_X11_SYM(வெறுமை,XcursorImagesDestroy,(XcursorImages *a))
SDL_X11_SYM(Cursor,XcursorImageLoadCursor,(Display *a,மாறிலி XcursorImage *b))
SDL_X11_SYM(Cursor,XcursorImagesLoadCursor,(Display *a,மாறிலி XcursorImages *b))
SDL_X11_SYM(Cursor,XcursorLibraryLoadCursor,(Display *a, மாறிலி எழுத்து *b))
#endif

// Xdbe support
#ifdef SDL_VIDEO_DRIVER_X11_XDBE
SDL_X11_MODULE(XDBE)
SDL_X11_SYM(Status,XdbeQueryExtension,(Display *dpy,முழு *major_version_return,முழு *minor_version_return))
SDL_X11_SYM(XdbeBackBuffer,XdbeAllocateBackBufferName,(Display *dpy,Window window,XdbeSwapAction swap_action))
SDL_X11_SYM(Status,XdbeDeallocateBackBufferName,(Display *dpy,XdbeBackBuffer buffer))
SDL_X11_SYM(Status,XdbeSwapBuffers,(Display *dpy,XdbeSwapInfo *swap_info,முழு இலக்கம்_windows))
SDL_X11_SYM(Status,XdbeBeginIdiom,(Display *dpy))
SDL_X11_SYM(Status,XdbeEndIdiom,(Display *dpy))
SDL_X11_SYM(XdbeScreenVisualInfo*,XdbeGetVisualInfo,(Display *dpy,Drawable *screen_specifiers,முழு *இலக்கம்_screens))
SDL_X11_SYM(வெறுமை,XdbeFreeVisualInfo,(XdbeScreenVisualInfo *visual_info))
SDL_X11_SYM(XdbeBackBufferAttributes*,XdbeGetBackBufferAttributes,(Display *dpy,XdbeBackBuffer buffer))
#endif

// XInput2 support for multiple mice, tablets, etc.
#ifdef SDL_VIDEO_DRIVER_X11_XINPUT2
SDL_X11_MODULE(XINPUT2)
SDL_X11_SYM(XIDeviceInfo*,XIQueryDevice,(Display *a,முழு b,முழு *c))
SDL_X11_SYM(வெறுமை,XIFreeDeviceInfo,(XIDeviceInfo *a))
SDL_X11_SYM(முழு,XISelectEvents,(Display *a,Window b,XIEventMask *c,முழு d))
SDL_X11_SYM(முழு,XIGrabTouchBegin,(Display *a,முழு b,Window c,முழு d,XIEventMask *e,முழு f,XIGrabModifiers *g))
SDL_X11_SYM(முழு,XIUngrabTouchBegin, (Display *a,முழு b,Window c, முழு d,XIGrabModifiers *e))
SDL_X11_SYM(Status,XIQueryVersion,(Display *a,முழு *b,முழு *c))
SDL_X11_SYM(XIEventMask*,XIGetSelectedEvents,(Display *a,Window b,முழு *c))
SDL_X11_SYM(Bool,XIGetClientPointer,(Display *a,Window b,முழு *c))
SDL_X11_SYM(Bool,XIWarpPointer,(Display *a,முழு b,Window c,Window d,இரட்டை e,இரட்டை f,முழு g,முழு h,இரட்டை i,இரட்டை j))
SDL_X11_SYM(Status,XIGetProperty,(Display *a,முழு b,Atom c,long d,long e,Bool f, Atom g, Atom *h, முழு *i, unsigned long *j, unsigned long *k, unsigned எழுத்து **l))
#endif

// XRandR support
#ifdef SDL_VIDEO_DRIVER_X11_XRANDR
SDL_X11_MODULE(XRANDR)
SDL_X11_SYM(Status,XRRQueryVersion,(Display *dpy,முழு *major_versionp,முழு *minor_versionp))
SDL_X11_SYM(Bool,XRRQueryExtension,(Display *dpy,முழு *event_base_return,முழு *error_base_return))
SDL_X11_SYM(XRRScreenConfiguration *,XRRGetScreenInfo,(Display *dpy,Drawable draw))
SDL_X11_SYM(SizeID,XRRConfigCurrentConfiguration,(XRRScreenConfiguration *config,Rotation *rotation))
SDL_X11_SYM(short,XRRConfigCurrentRate,(XRRScreenConfiguration *config))
SDL_X11_SYM(short *,XRRConfigRates,(XRRScreenConfiguration *config,முழு sizeID,முழு *nrates))
SDL_X11_SYM(XRRScreenSize *,XRRConfigSizes,(XRRScreenConfiguration *config,முழு *nsizes))
SDL_X11_SYM(Status,XRRSetScreenConfigAndRate,(Display *dpy,XRRScreenConfiguration *config,Drawable draw,முழு size_index,Rotation rotation,short rate,Time timestamp))
SDL_X11_SYM(வெறுமை,XRRFreeScreenConfigInfo,(XRRScreenConfiguration *config))
SDL_X11_SYM(வெறுமை,XRRSetScreenSize,(Display *dpy, Window window,முழு width, முழு height,முழு mmWidth, முழு mmHeight))
SDL_X11_SYM(Status,XRRGetScreenSizeRange,(Display *dpy, Window window,முழு *minWidth, முழு *minHeight, முழு *maxWidth, முழு *maxHeight))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResources,(Display *dpy, Window window))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResourcesCurrent,(Display *dpy, Window window))
SDL_X11_SYM(வெறுமை,XRRFreeScreenResources,(XRRScreenResources *resources))
SDL_X11_SYM(XRROutputInfo *,XRRGetOutputInfo,(Display *dpy, XRRScreenResources *resources, RROutput output))
SDL_X11_SYM(வெறுமை,XRRFreeOutputInfo,(XRROutputInfo *outputInfo))
SDL_X11_SYM(XRRCrtcInfo *,XRRGetCrtcInfo,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc))
SDL_X11_SYM(வெறுமை,XRRFreeCrtcInfo,(XRRCrtcInfo *crtcInfo))
SDL_X11_SYM(Status,XRRSetCrtcConfig,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc, Time timestamp, முழு x, முழு y, RRMode mode, Rotation rotation, RROutput *outputs, முழு noutputs))
SDL_X11_SYM(Atom*,XRRListOutputProperties,(Display *dpy, RROutput output, முழு *nprop))
SDL_X11_SYM(XRRPropertyInfo*,XRRQueryOutputProperty,(Display *dpy,RROutput output, Atom property))
SDL_X11_SYM(முழு,XRRGetOutputProperty,(Display *dpy,RROutput output, Atom property, long offset, long length, Bool _delete, Bool pending, Atom req_type, Atom *actual_type, முழு *actual_format, unsigned long *nitems, unsigned long *bytes_after, unsigned எழுத்து **prop))
SDL_X11_SYM(RROutput,XRRGetOutputPrimary,(Display *dpy,Window window))
SDL_X11_SYM(வெறுமை,XRRSelect_உள்ளீடு,(Display *dpy, Window window, முழு mask))
SDL_X11_SYM(Status,XRRGetCrtcTransform,(Display *dpy,RRCrtc crtc,XRRCrtcTransformAttributes **attributes))
#endif

// MIT-SCREEN-SAVER support
#ifdef SDL_VIDEO_DRIVER_X11_XSCRNSAVER
SDL_X11_MODULE(XSS)
SDL_X11_SYM(Bool,XScreenSaverQueryExtension,(Display *dpy,முழு *event_base,முழு *error_base))
SDL_X11_SYM(Status,XScreenSaverQueryVersion,(Display *dpy,முழு *major_versionp,முழு *minor_versionp))
SDL_X11_SYM(வெறுமை,XScreenSaverSuspend,(Display *dpy,Bool suspend))
#endif

#ifdef SDL_VIDEO_DRIVER_X11_XSHAPE
SDL_X11_MODULE(XSHAPE)
SDL_X11_SYM(வெறுமை,XShapeCombineMask,(Display *dpy,Window dest,முழு dest_kind,முழு x_off,முழு y_off,Pixmap src,முழு op))
SDL_X11_SYM(வெறுமை,XShapeCombineRegion,(Display *a,Window b,முழு c,முழு d,முழு e,Region f,முழு g))
#endif

#undef SDL_X11_MODULE
#undef SDL_X11_SYM

/* *INDENT-ON* */ // clang-format on

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

#جيڪڏهن_وصف_نه_ٿيل SDL_X11_MODULE
#وصف_ڪريو SDL_X11_MODULE(modname)
#جيڪڏهن_پورو

#جيڪڏهن_وصف_نه_ٿيل SDL_X11_SYM
#وصف_ڪريو SDL_X11_SYM(rc, fn, params)
#جيڪڏهن_پورو

SDL_X11_MODULE(BASEXLIB)
SDL_X11_SYM(XSizeHints*,XAlloc_سائيز_Hints,(فراغ))
SDL_X11_SYM(XWMHints*,XAllocWMHints,(فراغ))
SDL_X11_SYM(XClassHint*,XAllocClassHint,(فراغ))
SDL_X11_SYM(صحيح,XChange_اشارو_Control,(Display* a,Bool b,Bool c,صحيح d,صحيح e,صحيح f))
SDL_X11_SYM(صحيح,XChangeProperty,(Display* a,دري_2 b,Atom c,Atom d,صحيح e,صحيح f,_Xconst بنانشان حرف* g,صحيح h))
SDL_X11_SYM(Bool,XCheckIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(صحيح,XClear_دري,(Display* a,دري_2 b))
SDL_X11_SYM(صحيح,XCloseDisplay,(Display* a))
SDL_X11_SYM(صحيح,XConvertSelection,(Display* a,Atom b,Atom c,Atom d,دري_2 e,وقت_2 f))
SDL_X11_SYM(Pixmap,XCreate_Bitmap_From_معلومات,(Display *dpy,Drawable d,_Xconst حرف *معلومات,بنانشان صحيح ويڪر,بنانشان صحيح اوچائي))
SDL_X11_SYM(Colormap,XCreateColormap,(Display* a,دري_2 b,Visual* c,صحيح d))
SDL_X11_SYM(Cursor,XCreatePixmapCursor,(Display* a,Pixmap b,Pixmap c,XColor* d,XColor* e,بنانشان صحيح f,بنانشان صحيح g))
SDL_X11_SYM(Cursor,XCreatePixmap,(Display* a,Drawable b,بنانشان صحيح d,بنانشان صحيح e,بنانشان صحيح f))
SDL_X11_SYM(Cursor,XCreateFontCursor,(Display* a,بنانشان صحيح b))
SDL_X11_SYM(XFont_سيٽ,XCreate_Font_سيٽ,(Display* a, _Xconst حرف* b, حرف*** c, صحيح* d, حرف** e))
SDL_X11_SYM(GC,XCreateGC,(Display* a,Drawable b,بنانشان ڊگهو c,XGCValues* d))
SDL_X11_SYM(فراغ,XSetFont,(Display* a,GC b,Font c))
SDL_X11_SYM(حالت_2,XAllocColor,(Display *a, Colormap b, XColor *c))
SDL_X11_SYM(XImage*,XCreateImage,(Display* a,Visual* b,بنانشان صحيح c,صحيح d,صحيح e,حرف* f,بنانشان صحيح g,بنانشان صحيح h,صحيح i,صحيح j))
SDL_X11_SYM(دري_2,XCreate_دري,(Display* a,دري_2 b,صحيح c,صحيح d,بنانشان صحيح e,بنانشان صحيح f,بنانشان صحيح g,صحيح h,بنانشان صحيح i,Visual* j,بنانشان ڊگهو k,XSet_دري_خاصيتون* l))
SDL_X11_SYM(فراغ,XCopyArea,(Display *a, Drawable b, Drawable c, GC d, صحيح e, صحيح f, بنانشان صحيح g, بنانشان صحيح h, صحيح i, صحيح j))
SDL_X11_SYM(صحيح,XDefineCursor,(Display* a,دري_2 b,Cursor c))
SDL_X11_SYM(صحيح,XDeleteProperty,(Display* a,دري_2 b,Atom c))
SDL_X11_SYM(صحيح,XDestroy_دري,(Display* a,دري_2 b))
SDL_X11_SYM(صحيح,XDisplayKeycodes,(Display* a,صحيح* b,صحيح* c))
SDL_X11_SYM(صحيح,XDrawRectangle,(Display* a,Drawable b,GC c,صحيح d,صحيح e,بنانشان صحيح f,بنانشان صحيح g))
SDL_X11_SYM(صحيح,XFonts_جو_Font_سيٽ,(XFont_سيٽ a,XFontStruct ***b,حرف ***c))
SDL_X11_SYM(صحيح,XFillArc,(Display* a,Drawable b,GC c,صحيح d,صحيح e,بنانشان صحيح f,بنانشان صحيح g, صحيح h, صحيح i))
SDL_X11_SYM(حرف*,XDisplayName,(_Xconst حرف* a))
SDL_X11_SYM(صحيح,XDrawString,(Display* a,Drawable b,GC c,صحيح d,صحيح e,_Xconst حرف* f,صحيح g))
SDL_X11_SYM(صحيح,XEventsQueued,(Display* a,صحيح b))
SDL_X11_SYM(صحيح,XFillRectangle,(Display* a,Drawable b,GC c,صحيح d,صحيح e,بنانشان صحيح f,بنانشان صحيح g))
SDL_X11_SYM(Bool,XFilterEvent,(XEvent *event,دري_2 w))
SDL_X11_SYM(صحيح,XFlush,(Display* a))
SDL_X11_SYM(صحيح,XFree,(فراغ*a))
SDL_X11_SYM(صحيح,XFreeCursor,(Display* a,Cursor b))
SDL_X11_SYM(فراغ,XFree_Font_سيٽ,(Display* a, XFont_سيٽ b))
SDL_X11_SYM(صحيح,XFreeGC,(Display* a,GC b))
SDL_X11_SYM(صحيح,XFreeFont,(Display* a, XFontStruct* b))
SDL_X11_SYM(صحيح,XFreeModifiermap,(XModifierKeymap* a))
SDL_X11_SYM(صحيح,XFreePixmap,(Display* a,Pixmap b))
SDL_X11_SYM(صحيح,XFreeColormap,(Display* a,Colormap b))
SDL_X11_SYM(فراغ,XFreeStringList,(حرف** a))
SDL_X11_SYM(حرف*,XGetAtomName,(Display *a,Atom b))
SDL_X11_SYM(صحيح,XGet_داخلا_Focus,(Display *a,دري_2 *b,صحيح *c))
SDL_X11_SYM(ڪنجي_Sym*,XGetKeyboardMapping,(Display *a, ڪنجي_ڪوڊ_2 b, صحيح c, صحيح *d))
SDL_X11_SYM(صحيح,XGet_Error_Database_متن,(Display* a,_Xconst حرف* b,_Xconst حرف* c,_Xconst حرف* d,حرف* e,صحيح f))
SDL_X11_SYM(XModifierKeymap*,XGetModifierMapping,(Display* a))
SDL_X11_SYM(صحيح,XGet_اشارو_Control,(Display* a,صحيح* b,صحيح* c,صحيح* d))
SDL_X11_SYM(دري_2,XGetSelectionOwner,(Display* a,Atom b))
SDL_X11_SYM(XVisualInfo*,XGetVisualInfo,(Display* a,ڊگهو b,XVisualInfo* c,صحيح* d))
SDL_X11_SYM(حالت_2,XGet_دري_خاصيتون,(Display* a,دري_2 b,XWindow_خاصيتون* c))
SDL_X11_SYM(صحيح,XGet_دري_Property,(Display* a,دري_2 b,Atom c,ڊگهو d,ڊگهو e,Bool f,Atom g,Atom* h,صحيح* i,بنانشان ڊگهو* j,بنانشان ڊگهو *k,بنانشان حرف **l))
SDL_X11_SYM(XWMHints*,XGetWMHints,(Display* a,دري_2 b))
SDL_X11_SYM(حالت_2,XGetWMNormalHints,(Display *a,دري_2 b, XSizeHints *c, ڊگهو *d))
SDL_X11_SYM(صحيح,XIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(صحيح,XGrabKeyboard,(Display* a,دري_2 b,Bool c,صحيح d,صحيح e,وقت_2 f))
SDL_X11_SYM(صحيح,XGrab_اشارو,(Display* a,دري_2 b,Bool c,بنانشان صحيح d,صحيح e,صحيح f,دري_2 g,Cursor h,وقت_2 i))
SDL_X11_SYM(صحيح,XGrabServer,(Display* a))
SDL_X11_SYM(حالت_2,XIconify_دري,(Display* a,دري_2 b,صحيح c))
SDL_X11_SYM(ڪنجي_ڪوڊ_2,XKeysym_منزل_Keycode,(Display* a,ڪنجي_Sym b))
SDL_X11_SYM(حرف*,XKeysym_منزل_String,(ڪنجي_Sym a))
SDL_X11_SYM(صحيح,XInstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(Atom,XInternAtom,(Display* a,_Xconst حرف* b,Bool c))
SDL_X11_SYM(XPixmap_Format_قدرون*,XListPixmapFormats,(Display* a,صحيح* b))
SDL_X11_SYM(XFontStruct*,XLoadQueryFont,(Display* a,_Xconst حرف* b))
SDL_X11_SYM(ڪنجي_Sym,XLookupKeysym,(XKeyEvent* a,صحيح b))
SDL_X11_SYM(صحيح,XLookupString,(XKeyEvent* a,حرف* b,صحيح c,ڪنجي_Sym* d,XCompose_حالت* e))
SDL_X11_SYM(صحيح,XMapRaised,(Display* a,دري_2 b))
SDL_X11_SYM(حالت_2,XMatchVisualInfo,(Display* a,صحيح b,صحيح c,صحيح d,XVisualInfo* e))
SDL_X11_SYM(صحيح,XMissingExtension,(Display* a,_Xconst حرف* b))
SDL_X11_SYM(صحيح,XMove_دري,(Display* a,دري_2 b,صحيح c,صحيح d))
SDL_X11_SYM(Display*,XOpenDisplay,(_Xconst حرف* a))
SDL_X11_SYM(حالت_2,XInit_ڌاڳا,(فراغ))
SDL_X11_SYM(صحيح,XPeekEvent,(Display* a,XEvent* b))
SDL_X11_SYM(صحيح,XPending,(Display* a))
SDL_X11_SYM(XImage*,XGetImage,(Display* a,Drawable b,صحيح c, صحيح d,بنانشان صحيح e,بنانشان صحيح f,بنانشان ڊگهو g,صحيح h))
SDL_X11_SYM(صحيح,XPutImage,(Display* a,Drawable b,GC c,XImage* d,صحيح e,صحيح f,صحيح g,صحيح h,بنانشان صحيح i,بنانشان صحيح j))
SDL_X11_SYM(صحيح,XQueryKeymap,(Display* a,حرف b[32]))
SDL_X11_SYM(Bool,XQuery_اشارو,(Display* a,دري_2 b,دري_2* c,دري_2* d,صحيح* e,صحيح* f,صحيح* g,صحيح* h,بنانشان صحيح* i))
SDL_X11_SYM(صحيح,XRaise_دري,(Display* a,دري_2 b))
SDL_X11_SYM(صحيح,XReparent_دري,(Display* a,دري_2 b,دري_2 c,صحيح d,صحيح e))
SDL_X11_SYM(صحيح,XResetScreenSaver,(Display* a))
SDL_X11_SYM(صحيح,XResize_دري,(Display* a,دري_2 b,بنانشان صحيح c,بنانشان صحيح d))
SDL_X11_SYM(صحيح,XScreen_عدد_جو_Screen,(Screen* a))
SDL_X11_SYM(صحيح,XSelect_داخلا,(Display* a,دري_2 b,ڊگهو c))
SDL_X11_SYM(حالت_2,XSendEvent,(Display* a,دري_2 b,Bool c,ڊگهو d,XEvent* e))
SDL_X11_SYM(XErrorHandler,XSetErrorHandler,(XErrorHandler a))
SDL_X11_SYM(صحيح,XSetForeground,(Display* a,GC b,بنانشان ڊگهو c))
SDL_X11_SYM(XIOErrorHandler,XSetIOErrorHandler,(XIOErrorHandler a))
SDL_X11_SYM(صحيح,XSet_داخلا_Focus,(Display *a,دري_2 b,صحيح c,وقت_2 d))
SDL_X11_SYM(صحيح,XSetSelectionOwner,(Display* a,Atom b,دري_2 c,وقت_2 d))
SDL_X11_SYM(صحيح,XSetTransientForHint,(Display* a,دري_2 b,دري_2 c))
SDL_X11_SYM(فراغ,XSet_متن_Property,(Display* a,دري_2 b,XTextProperty* c,Atom d))
SDL_X11_SYM(صحيح,XSet_دري_Background,(Display* a,دري_2 b,بنانشان ڊگهو c))
SDL_X11_SYM(فراغ,XSetWMHints,(Display* a,دري_2 b,XWMHints* c))
SDL_X11_SYM(فراغ,XSetWMNormalHints,(Display* a,دري_2 b,XSizeHints* c))
SDL_X11_SYM(فراغ,XSetWMProperties,(Display* a,دري_2 b,XTextProperty* c,XTextProperty* d,حرف** e,صحيح f,XSizeHints* g,XWMHints* h,XClassHint* i))
SDL_X11_SYM(حالت_2,XSetWMProtocols,(Display* a,دري_2 b,Atom* c,صحيح d))
SDL_X11_SYM(صحيح,XStoreColors,(Display* a,Colormap b,XColor* c,صحيح d))
SDL_X11_SYM(صحيح,XStoreName,(Display* a,دري_2 b,_Xconst حرف* c))
SDL_X11_SYM(حالت_2,XString_List_منزل_متن_Property,(حرف** a,صحيح b,XTextProperty* c))
SDL_X11_SYM(صحيح,XSync,(Display* a,Bool b))
SDL_X11_SYM(صحيح,XTextExtents,(XFontStruct* a,_Xconst حرف* b,صحيح c,صحيح* d,صحيح* e,صحيح* f,XCharStruct* g))
SDL_X11_SYM(Bool,XTranslateCoordinates,(Display *a,دري_2 b,دري_2 c,صحيح d,صحيح e,صحيح* f,صحيح* g,دري_2* h))
SDL_X11_SYM(صحيح,XUndefineCursor,(Display* a,دري_2 b))
SDL_X11_SYM(صحيح,XUngrabKeyboard,(Display* a,وقت_2 b))
SDL_X11_SYM(صحيح,XUngrab_اشارو,(Display* a,وقت_2 b))
SDL_X11_SYM(صحيح,XUngrabServer,(Display* a))
SDL_X11_SYM(صحيح,XUninstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(صحيح,XUnloadFont,(Display* a,Font b))
SDL_X11_SYM(صحيح,XWarp_اشارو,(Display* a,دري_2 b,دري_2 c,صحيح d,صحيح e,بنانشان صحيح f,بنانشان صحيح g,صحيح h,صحيح i))
SDL_X11_SYM(صحيح,XWindowEvent,(Display* a,دري_2 b,ڊگهو c,XEvent* d))
SDL_X11_SYM(حالت_2,XWithdraw_دري,(Display* a,دري_2 b,صحيح c))
SDL_X11_SYM(VisualID,XVisualIDFromVisual,(Visual* a))
SDL_X11_SYM(حرف*,XGetDefault,(Display* a,_Xconst حرف* b, _Xconst حرف* c))
SDL_X11_SYM(Bool,XQueryExtension,(Display* a,_Xconst حرف* b,صحيح* c,صحيح* d,صحيح* e))
SDL_X11_SYM(حرف *,XDisplayString,(Display* a))
SDL_X11_SYM(صحيح,XGet_Error_متن,(Display* a,صحيح b,حرف* c,صحيح d))
SDL_X11_SYM(فراغ,XEat_معلومات,(Display* a,بنانشان ڊگهو b))
SDL_X11_SYM(فراغ,_XFlush,(Display* a))
SDL_X11_SYM(فراغ,_XFlushGCCache,(Display* a,GC b))
SDL_X11_SYM(صحيح,_XRead,(Display* a,حرف* b,ڊگهو c))
SDL_X11_SYM(فراغ,_XReadPad,(Display* a,حرف* b,ڊگهو c))
SDL_X11_SYM(فراغ,_XSend,(Display* a,_Xconst حرف* b,ڊگهو c))
SDL_X11_SYM(حالت_2,_XReply,(Display* a,x_جواب* b,صحيح c,Bool d))
SDL_X11_SYM(بنانشان ڊگهو,XSet_آخري_Request_Read,(Display* a,x_Generic_جواب* b))
SDL_X11_SYM(SDL_X11_XSynchronizeRetType,XSynchronize,(Display* a,Bool b))
SDL_X11_SYM(SDL_X11_XESet_Wire_منزل_Event_Ret_Type,XESet_Wire_منزل_Event,(Display* a,صحيح b,SDL_X11_XESet_Wire_منزل_Event_Ret_Type c))
SDL_X11_SYM(SDL_X11_XESet_Event_منزل_Wire_Ret_Type,XESet_Event_منزل_Wire,(Display* a,صحيح b,SDL_X11_XESet_Event_منزل_Wire_Ret_Type c))
SDL_X11_SYM(فراغ,XRefreshKeyboardMapping,(XMappingEvent *a))
SDL_X11_SYM(صحيح,XQuery_وڻ,(Display* a,دري_2 b,دري_2* c,دري_2* d,دري_2** e,بنانشان صحيح* f))
SDL_X11_SYM(Bool,XSupportsLocale,(فراغ))
SDL_X11_SYM(حالت_2,Xmb_متن_List_منزل_متن_Property,(Display* a,حرف** b,صحيح c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(Region,XCreateRegion,(فراغ))
SDL_X11_SYM(صحيح,XUnionRectWithRegion,(XRectangle *a, Region b, Region c))
SDL_X11_SYM(فراغ,XDestroyRegion,(Region))
SDL_X11_SYM(فراغ,XrmInitialize,(فراغ))
SDL_X11_SYM(حرف*,XResourceManagerString,(Display *display))
SDL_X11_SYM(XrmDatabase,XrmGetStringDatabase,(حرف *معلومات))
SDL_X11_SYM(فراغ,XrmDestroyDatabase,(XrmDatabase db))
SDL_X11_SYM(Bool,XrmGetResource,(XrmDatabase db, حرف* str_name, حرف* str_class, حرف **str_type_return, Xrm_قدر *))
SDL_X11_SYM(صحيح,XGet_اشارو_Mapping,(Display *a, بنانشان حرف *b, بنانشان صحيح c))

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XFIXES
SDL_X11_MODULE(XFIXES)
SDL_X11_SYM(اشارو_Barrier, XFixes_Create_اشارو_Barrier, (Display* a, دري_2 b, صحيح c, صحيح d, صحيح e, صحيح f, صحيح g, صحيح h, صحيح *i))
SDL_X11_SYM(فراغ, XFixes_Destroy_اشارو_Barrier, (Display* a, اشارو_Barrier b))
SDL_X11_SYM(صحيح, XIBarrier_Release_اشارو,(Display* a,  صحيح b, اشارو_Barrier c, BarrierEventID d)) // this is actually Xinput2
SDL_X11_SYM(حالت_2, XFixes_Query_نسخو,(Display* a, صحيح* b, صحيح* c))
SDL_X11_SYM(حالت_2, XFixes_Select_Selection_داخلا, (Display* a, دري_2 b, Atom c, بنانشان ڊگهو d))
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XSYNC
SDL_X11_MODULE(XSYNC)
SDL_X11_SYM(حالت_2, XSyncQueryExtension, (Display* a, صحيح* b, صحيح* c))
SDL_X11_SYM(حالت_2, XSyncInitialize, (Display* a, صحيح* b, صحيح* c))
SDL_X11_SYM(XSyncCounter, XSyncCreateCounter, (Display* a, XSync_قدر b))
SDL_X11_SYM(حالت_2, XSyncDestroyCounter, (Display* a, XSyncCounter b))
SDL_X11_SYM(حالت_2, XSync_سيٽ_Counter, (Display* a, XSyncCounter b, XSync_قدر c))
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XTEST
SDL_X11_MODULE(XTEST)
SDL_X11_SYM(حالت_2, XTestQueryExtension, (Display* a, صحيح* b, صحيح* c))
SDL_X11_SYM(صحيح, XTestFakeMotionEvent, (Display* a, صحيح b, صحيح c, صحيح d, بنانشان ڊگهو e))
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
SDL_X11_SYM(Bool,XGet_Event_معلومات,(Display* a,XGenericEventCookie* b))
SDL_X11_SYM(فراغ,XFree_Event_معلومات,(Display* a,XGenericEventCookie* b))
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
SDL_X11_SYM(Bool,XkbQueryExtension,(Display* a,صحيح * b,صحيح * c,صحيح * d,صحيح * e, صحيح *f))
SDL_X11_SYM(ڪنجي_Sym,Xkb_Keycode_منزل_Keysym,(Display* a, ڪنجي_ڪوڊ_2 b, بنانشان صحيح c, بنانشان صحيح d))
SDL_X11_SYM(Bool,XkbSelectEvents,(Display* a, بنانشان صحيح b, بنانشان صحيح c, بنانشان ڊگهو d))
SDL_X11_SYM(Bool,XkbSelectEventDetails,(Display* a, بنانشان صحيح b, بنانشان صحيح c, بنانشان ڊگهو d, بنانشان ڊگهو e))
SDL_X11_SYM(حالت_2,Xkb_Get_نالا,(Display *a, بنانشان صحيح b, XkbDescPtr c))
SDL_X11_SYM(حالت_2,XkbGetState,(Display* a,بنانشان صحيح b,XkbStatePtr c))
SDL_X11_SYM(حالت_2,XkbGetUpdatedMap,(Display* a,بنانشان صحيح b,XkbDescPtr c))
SDL_X11_SYM(XkbDescPtr,XkbGetMap,(Display* a,بنانشان صحيح b,بنانشان صحيح c))
SDL_X11_SYM(فراغ,XkbFreeClientMap,(XkbDescPtr a,بنانشان صحيح b, Bool c))
SDL_X11_SYM(فراغ,XkbFreeKeyboard,(XkbDescPtr a,بنانشان صحيح b, Bool c))
SDL_X11_SYM(حالت_2,XkbRefreshKeyboardMapping,(XkbMapNotifyEvent *a))
SDL_X11_SYM(Bool,Xkb_سيٽ_Detectable_Auto_Repeat,(Display* a, Bool b, Bool* c))
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل X_HAVE_UTF8_STRING
SDL_X11_MODULE(UTF8)
SDL_X11_SYM(صحيح,Xutf8_متن_List_منزل_متن_Property,(Display* a,حرف** b,صحيح c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(صحيح,Xutf8LookupString,(XIC a,XKeyPressedEvent* b,حرف* c,صحيح d,ڪنجي_Sym* e,حالت_2* f))
SDL_X11_SYM(XIC,XCreateIC,(XIM,...))
SDL_X11_SYM(فراغ,XDestroyIC,(XIC a))
SDL_X11_SYM(حرف*,XGetICValues,(XIC,...))
SDL_X11_SYM(حرف*,XSetICValues,(XIC,...))
SDL_X11_SYM(XVaNestedList,XVaCreateNestedList,(صحيح, ...))
SDL_X11_SYM(فراغ,XSetICFocus,(XIC a))
SDL_X11_SYM(فراغ,XUnsetICFocus,(XIC a))
SDL_X11_SYM(XIM,XOpenIM,(Display* a,بنية Xrm_Hash_ٻالٽي_Rec* b,حرف* c,حرف* d))
SDL_X11_SYM(حالت_2,XCloseIM,(XIM a))
SDL_X11_SYM(حرف*, XSetIMValues,(XIM,...))
SDL_X11_SYM(Bool,XRegisterIMInstantiateCallback,(Display*,بنية Xrm_Hash_ٻالٽي_Rec*,حرف*,حرف*,XIDProc,XPointer))
SDL_X11_SYM(Bool,XUnregisterIMInstantiateCallback,(Display*,بنية Xrm_Hash_ٻالٽي_Rec*,حرف*,حرف*,XIDProc,XPointer))
SDL_X11_SYM(فراغ,Xutf8DrawString,(Display *a, Drawable b, XFont_سيٽ c, GC d, صحيح e, صحيح f, _Xconst حرف *g, صحيح h))
SDL_X11_SYM(صحيح,Xutf8_متن_Extents,(XFont_سيٽ a, _Xconst حرف* b, صحيح c, XRectangle* d, XRectangle* e))
SDL_X11_SYM(حرف*,XSetLocaleModifiers,(ثابت حرف *a))
SDL_X11_SYM(حرف*,Xutf8ResetIC,(XIC a))
SDL_X11_SYM(XFont_سيٽ_Extents*,XExtents_جو_Font_سيٽ,(XFont_سيٽ a))
SDL_X11_SYM(Bool,XContextDependentDrawing,(XFont_سيٽ a))
#جيڪڏهن_پورو


#جيڪڏهن_وصف_نه_ٿيل NO_SHARED_يادگيري
SDL_X11_MODULE(SHM)
SDL_X11_SYM(حالت_2,XShmAttach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(حالت_2,XShmDetach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(حالت_2,XShmPutImage,(Display* a,Drawable b,GC c,XImage* d,صحيح e,صحيح f,صحيح g,صحيح h,بنانشان صحيح i,بنانشان صحيح j,Bool k))
SDL_X11_SYM(حالت_2,XShmGetImage,(Display* a,Drawable b,XImage *c,صحيح d, صحيح e, بنانشان ڊگهو f))
SDL_X11_SYM(XImage*,XShmCreateImage,(Display* a,Visual* b,بنانشان صحيح c,صحيح d,حرف* e,XShmSegmentInfo* f,بنانشان صحيح g,بنانشان صحيح h))
SDL_X11_SYM(Pixmap,XShmCreatePixmap,(Display *a,Drawable b,حرف* c,XShmSegmentInfo* d, بنانشان صحيح e, بنانشان صحيح f, بنانشان صحيح g))
SDL_X11_SYM(Bool,XShmQueryExtension,(Display* a))
SDL_X11_SYM(حالت_2,XShm_Query_نسخو,(Display* a, صحيح *b, صحيح *c, Bool *d))
SDL_X11_SYM(صحيح,XShmPixmapFormat,(Display* a))
#جيڪڏهن_پورو

/*
 * Not required...these only exist in code in headers on some 64-bit platforms,
 *  and are removed via macros elsewhere, so it's safe for them to be missing.
 */
#جيڪڏهن_وصف_ٿيل LONG64
SDL_X11_MODULE(IO_32_ٻٽو_انگ)
SDL_X11_SYM(صحيح,_XData32,(Display *dpy,سجل _Xconst ڊگهو *معلومات,بنانشان len))
SDL_X11_SYM(فراغ,_XRead32,(Display *dpy,سجل ڊگهو *معلومات,ڊگهو len))
#جيڪڏهن_پورو

/*
 * These only show up on some variants of Unix.
 */
#جيڪڏهن_وصف_ٿيل SDL_PLATFORM_OSF
SDL_X11_MODULE(OSF_داخلا_POINTS)
SDL_X11_SYM(فراغ,Smt_بفر_حد_کان_مٿي,(Display *dpy,سجل smtDisplayPtr p))
SDL_X11_SYM(فراغ,_SmtIpError,(Display *dpy,سجل smtDisplayPtr p,صحيح i))
SDL_X11_SYM(صحيح,ip_Allocate_معلومات,(ChannelPtr a,IPCard b,IPDataPtr * c))
SDL_X11_SYM(صحيح,ip_Unallocate_And_Send_معلومات,(ChannelPtr a,IPCard b))
#جيڪڏهن_پورو

// XCursor support
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XCURSOR
SDL_X11_MODULE(XCURSOR)
SDL_X11_SYM(XcursorImage*,XcursorImageCreate,(صحيح a,صحيح b))
SDL_X11_SYM(XcursorImages*,XcursorImagesCreate,(صحيح a))
SDL_X11_SYM(فراغ,XcursorImageDestroy,(XcursorImage *a))
SDL_X11_SYM(فراغ,XcursorImagesDestroy,(XcursorImages *a))
SDL_X11_SYM(Cursor,Xcursor_Image_ڀريو_Cursor,(Display *a,ثابت XcursorImage *b))
SDL_X11_SYM(Cursor,Xcursor_Images_ڀريو_Cursor,(Display *a,ثابت XcursorImages *b))
SDL_X11_SYM(Cursor,Xcursor_Library_ڀريو_Cursor,(Display *a, ثابت حرف *b))
#جيڪڏهن_پورو

// Xdbe support
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XDBE
SDL_X11_MODULE(XDBE)
SDL_X11_SYM(حالت_2,XdbeQueryExtension,(Display *dpy,صحيح *major_نسخو_return,صحيح *minor_نسخو_return))
SDL_X11_SYM(Xdbe_پٺ_بفر,Xdbe_Allocate_پٺ_بفر_Name,(Display *dpy,دري_2 دري,Xdbe_مٽا_سٽا_Action مٽا_سٽا_action))
SDL_X11_SYM(حالت_2,Xdbe_Deallocate_پٺ_بفر_Name,(Display *dpy,Xdbe_پٺ_بفر بفر_2))
SDL_X11_SYM(حالت_2,Xdbe_مٽا_سٽا_Buffers,(Display *dpy,Xdbe_مٽا_سٽا_Info *مٽا_سٽا_info,صحيح انگ_windows))
SDL_X11_SYM(حالت_2,XdbeBeginIdiom,(Display *dpy))
SDL_X11_SYM(حالت_2,Xdbe_پڇاڙي_Idiom,(Display *dpy))
SDL_X11_SYM(XdbeScreenVisualInfo*,XdbeGetVisualInfo,(Display *dpy,Drawable *screen_specifiers,صحيح *انگ_screens))
SDL_X11_SYM(فراغ,XdbeFreeVisualInfo,(XdbeScreenVisualInfo *visual_info))
SDL_X11_SYM(Xdbe_پٺ_بفر_خاصيتون*,Xdbe_Get_پٺ_بفر_خاصيتون,(Display *dpy,Xdbe_پٺ_بفر بفر_2))
#جيڪڏهن_پورو

// XInput2 support for multiple mice, tablets, etc.
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XINPUT2
SDL_X11_MODULE(XINPUT2)
SDL_X11_SYM(XIDeviceInfo*,XIQueryDevice,(Display *a,صحيح b,صحيح *c))
SDL_X11_SYM(فراغ,XIFreeDeviceInfo,(XIDeviceInfo *a))
SDL_X11_SYM(صحيح,XISelectEvents,(Display *a,دري_2 b,XIEvent_نقاب *c,صحيح d))
SDL_X11_SYM(صحيح,XIGrabTouchBegin,(Display *a,صحيح b,دري_2 c,صحيح d,XIEvent_نقاب *e,صحيح f,XIGrabModifiers *g))
SDL_X11_SYM(صحيح,XIUngrabTouchBegin, (Display *a,صحيح b,دري_2 c, صحيح d,XIGrabModifiers *e))
SDL_X11_SYM(حالت_2,XIQuery_نسخو,(Display *a,صحيح *b,صحيح *c))
SDL_X11_SYM(XIEvent_نقاب*,XIGetSelectedEvents,(Display *a,دري_2 b,صحيح *c))
SDL_X11_SYM(Bool,XIGet_Client_اشارو,(Display *a,دري_2 b,صحيح *c))
SDL_X11_SYM(Bool,XIWarp_اشارو,(Display *a,صحيح b,دري_2 c,دري_2 d,مزدوج e,مزدوج f,صحيح g,صحيح h,مزدوج i,مزدوج j))
SDL_X11_SYM(حالت_2,XIGetProperty,(Display *a,صحيح b,Atom c,ڊگهو d,ڊگهو e,Bool f, Atom g, Atom *h, صحيح *i, بنانشان ڊگهو *j, بنانشان ڊگهو *k, بنانشان حرف **l))
#جيڪڏهن_پورو

// XRandR support
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XRANDR
SDL_X11_MODULE(XRANDR)
SDL_X11_SYM(حالت_2,XRRQuery_نسخو,(Display *dpy,صحيح *major_versionp,صحيح *minor_versionp))
SDL_X11_SYM(Bool,XRRQueryExtension,(Display *dpy,صحيح *event_بنياد_return,صحيح *error_بنياد_return))
SDL_X11_SYM(XRRScreenConfiguration *,XRRGetScreenInfo,(Display *dpy,Drawable draw))
SDL_X11_SYM(سائيز_ID,XRRConfigCurrentConfiguration,(XRRScreenConfiguration *config,Rotation *rotation))
SDL_X11_SYM(ننڍو,XRRConfig_Current_شرح,(XRRScreenConfiguration *config))
SDL_X11_SYM(ننڍو *,XRRConfigRates,(XRRScreenConfiguration *config,صحيح سائيز_ID_2,صحيح *nrates))
SDL_X11_SYM(XRRScreen_سائيز *,XRRConfigSizes,(XRRScreenConfiguration *config,صحيح *nsizes))
SDL_X11_SYM(حالت_2,XRRSet_Screen_Config_And_شرح,(Display *dpy,XRRScreenConfiguration *config,Drawable draw,صحيح سائيز_اشاريو,Rotation rotation,ننڍو شرح,وقت_2 timestamp))
SDL_X11_SYM(فراغ,XRRFreeScreenConfigInfo,(XRRScreenConfiguration *config))
SDL_X11_SYM(فراغ,XRRSet_Screen_سائيز,(Display *dpy, دري_2 دري,صحيح ويڪر, صحيح اوچائي,صحيح mm_ويڪر_2, صحيح mm_اوچائي_2))
SDL_X11_SYM(حالت_2,XRRGet_Screen_سائيز_Range,(Display *dpy, دري_2 دري,صحيح *min_ويڪر, صحيح *min_اوچائي, صحيح *max_ويڪر, صحيح *max_اوچائي))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResources,(Display *dpy, دري_2 دري))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResourcesCurrent,(Display *dpy, دري_2 دري))
SDL_X11_SYM(فراغ,XRRFreeScreenResources,(XRRScreenResources *resources))
SDL_X11_SYM(XRROutputInfo *,XRRGetOutputInfo,(Display *dpy, XRRScreenResources *resources, RROutput output))
SDL_X11_SYM(فراغ,XRRFreeOutputInfo,(XRROutputInfo *outputInfo))
SDL_X11_SYM(XRRCrtcInfo *,XRRGetCrtcInfo,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc))
SDL_X11_SYM(فراغ,XRRFreeCrtcInfo,(XRRCrtcInfo *crtcInfo))
SDL_X11_SYM(حالت_2,XRRSetCrtcConfig,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc, وقت_2 timestamp, صحيح x, صحيح y, RRMode گهڻائي, Rotation rotation, RROutput *outputs, صحيح noutputs))
SDL_X11_SYM(Atom*,XRRListOutputProperties,(Display *dpy, RROutput output, صحيح *nprop))
SDL_X11_SYM(XRRPropertyInfo*,XRRQueryOutputProperty,(Display *dpy,RROutput output, Atom property))
SDL_X11_SYM(صحيح,XRRGetOutputProperty,(Display *dpy,RROutput output, Atom property, ڊگهو وٿي_2, ڊگهو ڊيگهائي, Bool _delete, Bool pending, Atom req_type, Atom *actual_type, صحيح *actual_format, بنانشان ڊگهو *nitems, بنانشان ڊگهو *بائيٽون_after, بنانشان حرف **prop))
SDL_X11_SYM(RROutput,XRRGetOutputPrimary,(Display *dpy,دري_2 دري))
SDL_X11_SYM(فراغ,XRRSelect_داخلا,(Display *dpy, دري_2 دري, صحيح نقاب))
SDL_X11_SYM(حالت_2,XRRGetCrtcTransform,(Display *dpy,RRCrtc crtc,XRRCrtc_Transform_خاصيتون **خاصيتون))
#جيڪڏهن_پورو

// MIT-SCREEN-SAVER support
#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XSCRNSAVER
SDL_X11_MODULE(XSS)
SDL_X11_SYM(Bool,XScreenSaverQueryExtension,(Display *dpy,صحيح *event_بنياد_2,صحيح *error_بنياد_2))
SDL_X11_SYM(حالت_2,XScreen_Saver_Query_نسخو,(Display *dpy,صحيح *major_versionp,صحيح *minor_versionp))
SDL_X11_SYM(فراغ,XScreenSaverSuspend,(Display *dpy,Bool suspend))
#جيڪڏهن_پورو

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_X11_XSHAPE
SDL_X11_MODULE(XSHAPE)
SDL_X11_SYM(فراغ,XShape_Combine_نقاب,(Display *dpy,دري_2 dest,صحيح dest_قسم,صحيح x_off,صحيح y_off,Pixmap src,صحيح op))
SDL_X11_SYM(فراغ,XShapeCombineRegion,(Display *a,دري_2 b,صحيح c,صحيح d,صحيح e,Region f,صحيح g))
#جيڪڏهن_پورو

#وصف_رد SDL_X11_MODULE
#وصف_رد SDL_X11_SYM

/* *INDENT-ON* */ // clang-format on

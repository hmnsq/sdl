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

#اگر_غیر_تعریف_شدہ SDL_X11_MODULE
#تعریف_کرو SDL_X11_MODULE(modname)
#اگر_ختم

#اگر_غیر_تعریف_شدہ SDL_X11_SYM
#تعریف_کرو SDL_X11_SYM(rc, fn, params)
#اگر_ختم

SDL_X11_MODULE(BASEXLIB)
SDL_X11_SYM(XSizeHints*,XAlloc_سائز_Hints,(خالی))
SDL_X11_SYM(XWMHints*,XAllocWMHints,(خالی))
SDL_X11_SYM(XClassHint*,XAllocClassHint,(خالی))
SDL_X11_SYM(صحیح,XChange_اشارہ_گر_Control,(Display* a,Bool b,Bool c,صحیح d,صحیح e,صحیح f))
SDL_X11_SYM(صحیح,XChangeProperty,(Display* a,کھڑکی_2 b,Atom c,Atom d,صحیح e,صحیح f,_Xconst غیرعلامتی حرف* g,صحیح h))
SDL_X11_SYM(Bool,XCheckIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(صحیح,XClear_کھڑکی,(Display* a,کھڑکی_2 b))
SDL_X11_SYM(صحیح,XCloseDisplay,(Display* a))
SDL_X11_SYM(صحیح,XConvertSelection,(Display* a,Atom b,Atom c,Atom d,کھڑکی_2 e,وقت_2 f))
SDL_X11_SYM(Pixmap,XCreate_Bitmap_From_ڈیٹا,(Display *dpy,Drawable d,_Xconst حرف *ڈیٹا,غیرعلامتی صحیح چوڑائی,غیرعلامتی صحیح اونچائی))
SDL_X11_SYM(Colormap,XCreateColormap,(Display* a,کھڑکی_2 b,Visual* c,صحیح d))
SDL_X11_SYM(Cursor,XCreatePixmapCursor,(Display* a,Pixmap b,Pixmap c,XColor* d,XColor* e,غیرعلامتی صحیح f,غیرعلامتی صحیح g))
SDL_X11_SYM(Cursor,XCreatePixmap,(Display* a,Drawable b,غیرعلامتی صحیح d,غیرعلامتی صحیح e,غیرعلامتی صحیح f))
SDL_X11_SYM(Cursor,XCreateFontCursor,(Display* a,غیرعلامتی صحیح b))
SDL_X11_SYM(XFont_سیٹ,XCreate_Font_سیٹ,(Display* a, _Xconst حرف* b, حرف*** c, صحیح* d, حرف** e))
SDL_X11_SYM(GC,XCreateGC,(Display* a,Drawable b,غیرعلامتی طویل c,XGCValues* d))
SDL_X11_SYM(خالی,XSetFont,(Display* a,GC b,Font c))
SDL_X11_SYM(حالت_3,XAllocColor,(Display *a, Colormap b, XColor *c))
SDL_X11_SYM(XImage*,XCreateImage,(Display* a,Visual* b,غیرعلامتی صحیح c,صحیح d,صحیح e,حرف* f,غیرعلامتی صحیح g,غیرعلامتی صحیح h,صحیح i,صحیح j))
SDL_X11_SYM(کھڑکی_2,XCreate_کھڑکی,(Display* a,کھڑکی_2 b,صحیح c,صحیح d,غیرعلامتی صحیح e,غیرعلامتی صحیح f,غیرعلامتی صحیح g,صحیح h,غیرعلامتی صحیح i,Visual* j,غیرعلامتی طویل k,XSet_کھڑکی_اوصاف* l))
SDL_X11_SYM(خالی,XCopyArea,(Display *a, Drawable b, Drawable c, GC d, صحیح e, صحیح f, غیرعلامتی صحیح g, غیرعلامتی صحیح h, صحیح i, صحیح j))
SDL_X11_SYM(صحیح,XDefineCursor,(Display* a,کھڑکی_2 b,Cursor c))
SDL_X11_SYM(صحیح,XDeleteProperty,(Display* a,کھڑکی_2 b,Atom c))
SDL_X11_SYM(صحیح,XDestroy_کھڑکی,(Display* a,کھڑکی_2 b))
SDL_X11_SYM(صحیح,XDisplayKeycodes,(Display* a,صحیح* b,صحیح* c))
SDL_X11_SYM(صحیح,XDrawRectangle,(Display* a,Drawable b,GC c,صحیح d,صحیح e,غیرعلامتی صحیح f,غیرعلامتی صحیح g))
SDL_X11_SYM(صحیح,XFonts_کا_Font_سیٹ,(XFont_سیٹ a,XFontStruct ***b,حرف ***c))
SDL_X11_SYM(صحیح,XFillArc,(Display* a,Drawable b,GC c,صحیح d,صحیح e,غیرعلامتی صحیح f,غیرعلامتی صحیح g, صحیح h, صحیح i))
SDL_X11_SYM(حرف*,XDisplayName,(_Xconst حرف* a))
SDL_X11_SYM(صحیح,XDrawString,(Display* a,Drawable b,GC c,صحیح d,صحیح e,_Xconst حرف* f,صحیح g))
SDL_X11_SYM(صحیح,XEventsQueued,(Display* a,صحیح b))
SDL_X11_SYM(صحیح,XFillRectangle,(Display* a,Drawable b,GC c,صحیح d,صحیح e,غیرعلامتی صحیح f,غیرعلامتی صحیح g))
SDL_X11_SYM(Bool,XFilterEvent,(XEvent *event,کھڑکی_2 w))
SDL_X11_SYM(صحیح,XFlush,(Display* a))
SDL_X11_SYM(صحیح,XFree,(خالی*a))
SDL_X11_SYM(صحیح,XFreeCursor,(Display* a,Cursor b))
SDL_X11_SYM(خالی,XFree_Font_سیٹ,(Display* a, XFont_سیٹ b))
SDL_X11_SYM(صحیح,XFreeGC,(Display* a,GC b))
SDL_X11_SYM(صحیح,XFreeFont,(Display* a, XFontStruct* b))
SDL_X11_SYM(صحیح,XFreeModifiermap,(XModifierKeymap* a))
SDL_X11_SYM(صحیح,XFreePixmap,(Display* a,Pixmap b))
SDL_X11_SYM(صحیح,XFreeColormap,(Display* a,Colormap b))
SDL_X11_SYM(خالی,XFreeStringList,(حرف** a))
SDL_X11_SYM(حرف*,XGetAtomName,(Display *a,Atom b))
SDL_X11_SYM(صحیح,XGet_داخلہ_Focus,(Display *a,کھڑکی_2 *b,صحیح *c))
SDL_X11_SYM(کلید_Sym*,XGetKeyboardMapping,(Display *a, کلید_رمز_2 b, صحیح c, صحیح *d))
SDL_X11_SYM(صحیح,XGet_Error_Database_متن,(Display* a,_Xconst حرف* b,_Xconst حرف* c,_Xconst حرف* d,حرف* e,صحیح f))
SDL_X11_SYM(XModifierKeymap*,XGetModifierMapping,(Display* a))
SDL_X11_SYM(صحیح,XGet_اشارہ_گر_Control,(Display* a,صحیح* b,صحیح* c,صحیح* d))
SDL_X11_SYM(کھڑکی_2,XGetSelectionOwner,(Display* a,Atom b))
SDL_X11_SYM(XVisualInfo*,XGetVisualInfo,(Display* a,طویل b,XVisualInfo* c,صحیح* d))
SDL_X11_SYM(حالت_3,XGet_کھڑکی_اوصاف,(Display* a,کھڑکی_2 b,XWindow_اوصاف* c))
SDL_X11_SYM(صحیح,XGet_کھڑکی_Property,(Display* a,کھڑکی_2 b,Atom c,طویل d,طویل e,Bool f,Atom g,Atom* h,صحیح* i,غیرعلامتی طویل* j,غیرعلامتی طویل *k,غیرعلامتی حرف **l))
SDL_X11_SYM(XWMHints*,XGetWMHints,(Display* a,کھڑکی_2 b))
SDL_X11_SYM(حالت_3,XGetWMNormalHints,(Display *a,کھڑکی_2 b, XSizeHints *c, طویل *d))
SDL_X11_SYM(صحیح,XIfEvent,(Display* a,XEvent *b,Bool (*c)(Display*,XEvent*,XPointer),XPointer d))
SDL_X11_SYM(صحیح,XGrabKeyboard,(Display* a,کھڑکی_2 b,Bool c,صحیح d,صحیح e,وقت_2 f))
SDL_X11_SYM(صحیح,XGrab_اشارہ_گر,(Display* a,کھڑکی_2 b,Bool c,غیرعلامتی صحیح d,صحیح e,صحیح f,کھڑکی_2 g,Cursor h,وقت_2 i))
SDL_X11_SYM(صحیح,XGrabServer,(Display* a))
SDL_X11_SYM(حالت_3,XIconify_کھڑکی,(Display* a,کھڑکی_2 b,صحیح c))
SDL_X11_SYM(کلید_رمز_2,XKeysym_مقصد_Keycode,(Display* a,کلید_Sym b))
SDL_X11_SYM(حرف*,XKeysym_مقصد_String,(کلید_Sym a))
SDL_X11_SYM(صحیح,XInstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(Atom,XInternAtom,(Display* a,_Xconst حرف* b,Bool c))
SDL_X11_SYM(XPixmap_Format_اقدار*,XListPixmapFormats,(Display* a,صحیح* b))
SDL_X11_SYM(XFontStruct*,XLoadQueryFont,(Display* a,_Xconst حرف* b))
SDL_X11_SYM(کلید_Sym,XLookupKeysym,(XKeyEvent* a,صحیح b))
SDL_X11_SYM(صحیح,XLookupString,(XKeyEvent* a,حرف* b,صحیح c,کلید_Sym* d,XCompose_حالت* e))
SDL_X11_SYM(صحیح,XMapRaised,(Display* a,کھڑکی_2 b))
SDL_X11_SYM(حالت_3,XMatchVisualInfo,(Display* a,صحیح b,صحیح c,صحیح d,XVisualInfo* e))
SDL_X11_SYM(صحیح,XMissingExtension,(Display* a,_Xconst حرف* b))
SDL_X11_SYM(صحیح,XMove_کھڑکی,(Display* a,کھڑکی_2 b,صحیح c,صحیح d))
SDL_X11_SYM(Display*,XOpenDisplay,(_Xconst حرف* a))
SDL_X11_SYM(حالت_3,XInit_دھاگے,(خالی))
SDL_X11_SYM(صحیح,XPeekEvent,(Display* a,XEvent* b))
SDL_X11_SYM(صحیح,XPending,(Display* a))
SDL_X11_SYM(XImage*,XGetImage,(Display* a,Drawable b,صحیح c, صحیح d,غیرعلامتی صحیح e,غیرعلامتی صحیح f,غیرعلامتی طویل g,صحیح h))
SDL_X11_SYM(صحیح,XPutImage,(Display* a,Drawable b,GC c,XImage* d,صحیح e,صحیح f,صحیح g,صحیح h,غیرعلامتی صحیح i,غیرعلامتی صحیح j))
SDL_X11_SYM(صحیح,XQueryKeymap,(Display* a,حرف b[32]))
SDL_X11_SYM(Bool,XQuery_اشارہ_گر,(Display* a,کھڑکی_2 b,کھڑکی_2* c,کھڑکی_2* d,صحیح* e,صحیح* f,صحیح* g,صحیح* h,غیرعلامتی صحیح* i))
SDL_X11_SYM(صحیح,XRaise_کھڑکی,(Display* a,کھڑکی_2 b))
SDL_X11_SYM(صحیح,XReparent_کھڑکی,(Display* a,کھڑکی_2 b,کھڑکی_2 c,صحیح d,صحیح e))
SDL_X11_SYM(صحیح,XResetScreenSaver,(Display* a))
SDL_X11_SYM(صحیح,XResize_کھڑکی,(Display* a,کھڑکی_2 b,غیرعلامتی صحیح c,غیرعلامتی صحیح d))
SDL_X11_SYM(صحیح,XScreen_نمبر_کا_Screen,(Screen* a))
SDL_X11_SYM(صحیح,XSelect_داخلہ,(Display* a,کھڑکی_2 b,طویل c))
SDL_X11_SYM(حالت_3,XSendEvent,(Display* a,کھڑکی_2 b,Bool c,طویل d,XEvent* e))
SDL_X11_SYM(XErrorHandler,XSetErrorHandler,(XErrorHandler a))
SDL_X11_SYM(صحیح,XSetForeground,(Display* a,GC b,غیرعلامتی طویل c))
SDL_X11_SYM(XIOErrorHandler,XSetIOErrorHandler,(XIOErrorHandler a))
SDL_X11_SYM(صحیح,XSet_داخلہ_Focus,(Display *a,کھڑکی_2 b,صحیح c,وقت_2 d))
SDL_X11_SYM(صحیح,XSetSelectionOwner,(Display* a,Atom b,کھڑکی_2 c,وقت_2 d))
SDL_X11_SYM(صحیح,XSetTransientForHint,(Display* a,کھڑکی_2 b,کھڑکی_2 c))
SDL_X11_SYM(خالی,XSet_متن_Property,(Display* a,کھڑکی_2 b,XTextProperty* c,Atom d))
SDL_X11_SYM(صحیح,XSet_کھڑکی_Background,(Display* a,کھڑکی_2 b,غیرعلامتی طویل c))
SDL_X11_SYM(خالی,XSetWMHints,(Display* a,کھڑکی_2 b,XWMHints* c))
SDL_X11_SYM(خالی,XSetWMNormalHints,(Display* a,کھڑکی_2 b,XSizeHints* c))
SDL_X11_SYM(خالی,XSetWMProperties,(Display* a,کھڑکی_2 b,XTextProperty* c,XTextProperty* d,حرف** e,صحیح f,XSizeHints* g,XWMHints* h,XClassHint* i))
SDL_X11_SYM(حالت_3,XSetWMProtocols,(Display* a,کھڑکی_2 b,Atom* c,صحیح d))
SDL_X11_SYM(صحیح,XStoreColors,(Display* a,Colormap b,XColor* c,صحیح d))
SDL_X11_SYM(صحیح,XStoreName,(Display* a,کھڑکی_2 b,_Xconst حرف* c))
SDL_X11_SYM(حالت_3,XString_List_مقصد_متن_Property,(حرف** a,صحیح b,XTextProperty* c))
SDL_X11_SYM(صحیح,XSync,(Display* a,Bool b))
SDL_X11_SYM(صحیح,XTextExtents,(XFontStruct* a,_Xconst حرف* b,صحیح c,صحیح* d,صحیح* e,صحیح* f,XCharStruct* g))
SDL_X11_SYM(Bool,XTranslateCoordinates,(Display *a,کھڑکی_2 b,کھڑکی_2 c,صحیح d,صحیح e,صحیح* f,صحیح* g,کھڑکی_2* h))
SDL_X11_SYM(صحیح,XUndefineCursor,(Display* a,کھڑکی_2 b))
SDL_X11_SYM(صحیح,XUngrabKeyboard,(Display* a,وقت_2 b))
SDL_X11_SYM(صحیح,XUngrab_اشارہ_گر,(Display* a,وقت_2 b))
SDL_X11_SYM(صحیح,XUngrabServer,(Display* a))
SDL_X11_SYM(صحیح,XUninstallColormap,(Display* a,Colormap b))
SDL_X11_SYM(صحیح,XUnloadFont,(Display* a,Font b))
SDL_X11_SYM(صحیح,XWarp_اشارہ_گر,(Display* a,کھڑکی_2 b,کھڑکی_2 c,صحیح d,صحیح e,غیرعلامتی صحیح f,غیرعلامتی صحیح g,صحیح h,صحیح i))
SDL_X11_SYM(صحیح,XWindowEvent,(Display* a,کھڑکی_2 b,طویل c,XEvent* d))
SDL_X11_SYM(حالت_3,XWithdraw_کھڑکی,(Display* a,کھڑکی_2 b,صحیح c))
SDL_X11_SYM(VisualID,XVisualIDFromVisual,(Visual* a))
SDL_X11_SYM(حرف*,XGetDefault,(Display* a,_Xconst حرف* b, _Xconst حرف* c))
SDL_X11_SYM(Bool,XQueryExtension,(Display* a,_Xconst حرف* b,صحیح* c,صحیح* d,صحیح* e))
SDL_X11_SYM(حرف *,XDisplayString,(Display* a))
SDL_X11_SYM(صحیح,XGet_Error_متن,(Display* a,صحیح b,حرف* c,صحیح d))
SDL_X11_SYM(خالی,XEat_ڈیٹا,(Display* a,غیرعلامتی طویل b))
SDL_X11_SYM(خالی,_XFlush,(Display* a))
SDL_X11_SYM(خالی,_XFlushGCCache,(Display* a,GC b))
SDL_X11_SYM(صحیح,_XRead,(Display* a,حرف* b,طویل c))
SDL_X11_SYM(خالی,_XReadPad,(Display* a,حرف* b,طویل c))
SDL_X11_SYM(خالی,_XSend,(Display* a,_Xconst حرف* b,طویل c))
SDL_X11_SYM(حالت_3,_XReply,(Display* a,x_جواب* b,صحیح c,Bool d))
SDL_X11_SYM(غیرعلامتی طویل,XSet_آخری_Request_Read,(Display* a,x_Generic_جواب* b))
SDL_X11_SYM(SDL_X11_XSynchronizeRetType,XSynchronize,(Display* a,Bool b))
SDL_X11_SYM(SDL_X11_XESet_Wire_مقصد_Event_Ret_Type,XESet_Wire_مقصد_Event,(Display* a,صحیح b,SDL_X11_XESet_Wire_مقصد_Event_Ret_Type c))
SDL_X11_SYM(SDL_X11_XESet_Event_مقصد_Wire_Ret_Type,XESet_Event_مقصد_Wire,(Display* a,صحیح b,SDL_X11_XESet_Event_مقصد_Wire_Ret_Type c))
SDL_X11_SYM(خالی,XRefreshKeyboardMapping,(XMappingEvent *a))
SDL_X11_SYM(صحیح,XQuery_درخت,(Display* a,کھڑکی_2 b,کھڑکی_2* c,کھڑکی_2* d,کھڑکی_2** e,غیرعلامتی صحیح* f))
SDL_X11_SYM(Bool,XSupportsLocale,(خالی))
SDL_X11_SYM(حالت_3,Xmb_متن_List_مقصد_متن_Property,(Display* a,حرف** b,صحیح c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(Region,XCreateRegion,(خالی))
SDL_X11_SYM(صحیح,XUnionRectWithRegion,(XRectangle *a, Region b, Region c))
SDL_X11_SYM(خالی,XDestroyRegion,(Region))
SDL_X11_SYM(خالی,XrmInitialize,(خالی))
SDL_X11_SYM(حرف*,XResourceManagerString,(Display *display))
SDL_X11_SYM(XrmDatabase,XrmGetStringDatabase,(حرف *ڈیٹا))
SDL_X11_SYM(خالی,XrmDestroyDatabase,(XrmDatabase db))
SDL_X11_SYM(Bool,XrmGetResource,(XrmDatabase db, حرف* str_name, حرف* str_class, حرف **str_type_return, Xrm_قدر *))
SDL_X11_SYM(صحیح,XGet_اشارہ_گر_Mapping,(Display *a, غیرعلامتی حرف *b, غیرعلامتی صحیح c))

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XFIXES
SDL_X11_MODULE(XFIXES)
SDL_X11_SYM(اشارہ_گر_Barrier, XFixes_Create_اشارہ_گر_Barrier, (Display* a, کھڑکی_2 b, صحیح c, صحیح d, صحیح e, صحیح f, صحیح g, صحیح h, صحیح *i))
SDL_X11_SYM(خالی, XFixes_Destroy_اشارہ_گر_Barrier, (Display* a, اشارہ_گر_Barrier b))
SDL_X11_SYM(صحیح, XIBarrier_Release_اشارہ_گر,(Display* a,  صحیح b, اشارہ_گر_Barrier c, BarrierEventID d)) // this is actually Xinput2
SDL_X11_SYM(حالت_3, XFixes_Query_نسخہ,(Display* a, صحیح* b, صحیح* c))
SDL_X11_SYM(حالت_3, XFixes_Select_Selection_داخلہ, (Display* a, کھڑکی_2 b, Atom c, غیرعلامتی طویل d))
#اگر_ختم

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XSYNC
SDL_X11_MODULE(XSYNC)
SDL_X11_SYM(حالت_3, XSyncQueryExtension, (Display* a, صحیح* b, صحیح* c))
SDL_X11_SYM(حالت_3, XSyncInitialize, (Display* a, صحیح* b, صحیح* c))
SDL_X11_SYM(XSync_شمار, XSync_Create_شمار, (Display* a, XSync_قدر b))
SDL_X11_SYM(حالت_3, XSync_Destroy_شمار, (Display* a, XSync_شمار b))
SDL_X11_SYM(حالت_3, XSync_سیٹ_شمار, (Display* a, XSync_شمار b, XSync_قدر c))
#اگر_ختم

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XTEST
SDL_X11_MODULE(XTEST)
SDL_X11_SYM(حالت_3, XTestQueryExtension, (Display* a, صحیح* b, صحیح* c))
SDL_X11_SYM(صحیح, XTestFakeMotionEvent, (Display* a, صحیح b, صحیح c, صحیح d, غیرعلامتی طویل e))
#اگر_ختم

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_SUPPORTS_GENERIC_EVENTS
SDL_X11_SYM(Bool,XGet_Event_ڈیٹا,(Display* a,XGenericEventCookie* b))
SDL_X11_SYM(خالی,XFree_Event_ڈیٹا,(Display* a,XGenericEventCookie* b))
#اگر_ختم

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_HAS_XKBLIB
SDL_X11_SYM(Bool,XkbQueryExtension,(Display* a,صحیح * b,صحیح * c,صحیح * d,صحیح * e, صحیح *f))
SDL_X11_SYM(کلید_Sym,Xkb_Keycode_مقصد_Keysym,(Display* a, کلید_رمز_2 b, غیرعلامتی صحیح c, غیرعلامتی صحیح d))
SDL_X11_SYM(Bool,XkbSelectEvents,(Display* a, غیرعلامتی صحیح b, غیرعلامتی صحیح c, غیرعلامتی طویل d))
SDL_X11_SYM(Bool,XkbSelectEventDetails,(Display* a, غیرعلامتی صحیح b, غیرعلامتی صحیح c, غیرعلامتی طویل d, غیرعلامتی طویل e))
SDL_X11_SYM(حالت_3,Xkb_Get_نام,(Display *a, غیرعلامتی صحیح b, XkbDescPtr c))
SDL_X11_SYM(حالت_3,XkbGetState,(Display* a,غیرعلامتی صحیح b,XkbStatePtr c))
SDL_X11_SYM(حالت_3,XkbGetUpdatedMap,(Display* a,غیرعلامتی صحیح b,XkbDescPtr c))
SDL_X11_SYM(XkbDescPtr,XkbGetMap,(Display* a,غیرعلامتی صحیح b,غیرعلامتی صحیح c))
SDL_X11_SYM(خالی,XkbFreeClientMap,(XkbDescPtr a,غیرعلامتی صحیح b, Bool c))
SDL_X11_SYM(خالی,XkbFreeKeyboard,(XkbDescPtr a,غیرعلامتی صحیح b, Bool c))
SDL_X11_SYM(حالت_3,XkbRefreshKeyboardMapping,(XkbMapNotifyEvent *a))
SDL_X11_SYM(Bool,Xkb_سیٹ_Detectable_Auto_Repeat,(Display* a, Bool b, Bool* c))
#اگر_ختم

#اگر_تعریف_شدہ X_HAVE_UTF8_STRING
SDL_X11_MODULE(UTF8)
SDL_X11_SYM(صحیح,Xutf8_متن_List_مقصد_متن_Property,(Display* a,حرف** b,صحیح c,XICCEncodingStyle d,XTextProperty* e))
SDL_X11_SYM(صحیح,Xutf8LookupString,(XIC a,XKeyPressedEvent* b,حرف* c,صحیح d,کلید_Sym* e,حالت_3* f))
SDL_X11_SYM(XIC,XCreateIC,(XIM,...))
SDL_X11_SYM(خالی,XDestroyIC,(XIC a))
SDL_X11_SYM(حرف*,XGetICValues,(XIC,...))
SDL_X11_SYM(حرف*,XSetICValues,(XIC,...))
SDL_X11_SYM(XVaNestedList,XVaCreateNestedList,(صحیح, ...))
SDL_X11_SYM(خالی,XSetICFocus,(XIC a))
SDL_X11_SYM(خالی,XUnsetICFocus,(XIC a))
SDL_X11_SYM(XIM,XOpenIM,(Display* a,ساخت Xrm_Hash_بالٹی_Rec* b,حرف* c,حرف* d))
SDL_X11_SYM(حالت_3,XCloseIM,(XIM a))
SDL_X11_SYM(حرف*, XSetIMValues,(XIM,...))
SDL_X11_SYM(Bool,XRegisterIMInstantiateCallback,(Display*,ساخت Xrm_Hash_بالٹی_Rec*,حرف*,حرف*,XIDProc,XPointer))
SDL_X11_SYM(Bool,XUnregisterIMInstantiateCallback,(Display*,ساخت Xrm_Hash_بالٹی_Rec*,حرف*,حرف*,XIDProc,XPointer))
SDL_X11_SYM(خالی,Xutf8DrawString,(Display *a, Drawable b, XFont_سیٹ c, GC d, صحیح e, صحیح f, _Xconst حرف *g, صحیح h))
SDL_X11_SYM(صحیح,Xutf8_متن_Extents,(XFont_سیٹ a, _Xconst حرف* b, صحیح c, XRectangle* d, XRectangle* e))
SDL_X11_SYM(حرف*,XSetLocaleModifiers,(ثابت حرف *a))
SDL_X11_SYM(حرف*,Xutf8ResetIC,(XIC a))
SDL_X11_SYM(XFont_سیٹ_Extents*,XExtents_کا_Font_سیٹ,(XFont_سیٹ a))
SDL_X11_SYM(Bool,XContextDependentDrawing,(XFont_سیٹ a))
#اگر_ختم


#اگر_غیر_تعریف_شدہ NO_SHARED_حافظہ
SDL_X11_MODULE(SHM)
SDL_X11_SYM(حالت_3,XShmAttach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(حالت_3,XShmDetach,(Display* a,XShmSegmentInfo* b))
SDL_X11_SYM(حالت_3,XShmPutImage,(Display* a,Drawable b,GC c,XImage* d,صحیح e,صحیح f,صحیح g,صحیح h,غیرعلامتی صحیح i,غیرعلامتی صحیح j,Bool k))
SDL_X11_SYM(حالت_3,XShmGetImage,(Display* a,Drawable b,XImage *c,صحیح d, صحیح e, غیرعلامتی طویل f))
SDL_X11_SYM(XImage*,XShmCreateImage,(Display* a,Visual* b,غیرعلامتی صحیح c,صحیح d,حرف* e,XShmSegmentInfo* f,غیرعلامتی صحیح g,غیرعلامتی صحیح h))
SDL_X11_SYM(Pixmap,XShmCreatePixmap,(Display *a,Drawable b,حرف* c,XShmSegmentInfo* d, غیرعلامتی صحیح e, غیرعلامتی صحیح f, غیرعلامتی صحیح g))
SDL_X11_SYM(Bool,XShmQueryExtension,(Display* a))
SDL_X11_SYM(حالت_3,XShm_Query_نسخہ,(Display* a, صحیح *b, صحیح *c, Bool *d))
SDL_X11_SYM(صحیح,XShmPixmapFormat,(Display* a))
#اگر_ختم

/*
 * Not required...these only exist in code in headers on some 64-bit platforms,
 *  and are removed via macros elsewhere, so it's safe for them to be missing.
 */
#اگر_تعریف_شدہ LONG64
SDL_X11_MODULE(IO_32_ثنائی_ہندسہ)
SDL_X11_SYM(صحیح,_XData32,(Display *dpy,اندراج _Xconst طویل *ڈیٹا,غیرعلامتی len))
SDL_X11_SYM(خالی,_XRead32,(Display *dpy,اندراج طویل *ڈیٹا,طویل len))
#اگر_ختم

/*
 * These only show up on some variants of Unix.
 */
#اگر_تعریف_شدہ SDL_PLATFORM_OSF
SDL_X11_MODULE(OSF_اندراج_POINTS)
SDL_X11_SYM(خالی,Smt_بفر_حد_سے_تجاوز,(Display *dpy,اندراج smtDisplayPtr p))
SDL_X11_SYM(خالی,_SmtIpError,(Display *dpy,اندراج smtDisplayPtr p,صحیح i))
SDL_X11_SYM(صحیح,ip_Allocate_ڈیٹا,(ChannelPtr a,IPCard b,IPDataPtr * c))
SDL_X11_SYM(صحیح,ip_Unallocate_And_Send_ڈیٹا,(ChannelPtr a,IPCard b))
#اگر_ختم

// XCursor support
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XCURSOR
SDL_X11_MODULE(XCURSOR)
SDL_X11_SYM(XcursorImage*,XcursorImageCreate,(صحیح a,صحیح b))
SDL_X11_SYM(XcursorImages*,XcursorImagesCreate,(صحیح a))
SDL_X11_SYM(خالی,XcursorImageDestroy,(XcursorImage *a))
SDL_X11_SYM(خالی,XcursorImagesDestroy,(XcursorImages *a))
SDL_X11_SYM(Cursor,Xcursor_Image_بھرو_Cursor,(Display *a,ثابت XcursorImage *b))
SDL_X11_SYM(Cursor,Xcursor_Images_بھرو_Cursor,(Display *a,ثابت XcursorImages *b))
SDL_X11_SYM(Cursor,Xcursor_Library_بھرو_Cursor,(Display *a, ثابت حرف *b))
#اگر_ختم

// Xdbe support
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XDBE
SDL_X11_MODULE(XDBE)
SDL_X11_SYM(حالت_3,XdbeQueryExtension,(Display *dpy,صحیح *major_نسخہ_return,صحیح *minor_نسخہ_return))
SDL_X11_SYM(Xdbe_عقب_بفر,Xdbe_Allocate_عقب_بفر_Name,(Display *dpy,کھڑکی_2 کھڑکی,Xdbe_تبادلہ_Action تبادلہ_action))
SDL_X11_SYM(حالت_3,Xdbe_Deallocate_عقب_بفر_Name,(Display *dpy,Xdbe_عقب_بفر بفر_2))
SDL_X11_SYM(حالت_3,Xdbe_تبادلہ_Buffers,(Display *dpy,Xdbe_تبادلہ_Info *تبادلہ_info,صحیح عدد_windows))
SDL_X11_SYM(حالت_3,XdbeBeginIdiom,(Display *dpy))
SDL_X11_SYM(حالت_3,Xdbe_انتہا_Idiom,(Display *dpy))
SDL_X11_SYM(XdbeScreenVisualInfo*,XdbeGetVisualInfo,(Display *dpy,Drawable *screen_specifiers,صحیح *عدد_screens))
SDL_X11_SYM(خالی,XdbeFreeVisualInfo,(XdbeScreenVisualInfo *visual_info))
SDL_X11_SYM(Xdbe_عقب_بفر_اوصاف*,Xdbe_Get_عقب_بفر_اوصاف,(Display *dpy,Xdbe_عقب_بفر بفر_2))
#اگر_ختم

// XInput2 support for multiple mice, tablets, etc.
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XINPUT2
SDL_X11_MODULE(XINPUT2)
SDL_X11_SYM(XIDeviceInfo*,XIQueryDevice,(Display *a,صحیح b,صحیح *c))
SDL_X11_SYM(خالی,XIFreeDeviceInfo,(XIDeviceInfo *a))
SDL_X11_SYM(صحیح,XISelectEvents,(Display *a,کھڑکی_2 b,XIEvent_نقاب *c,صحیح d))
SDL_X11_SYM(صحیح,XIGrabTouchBegin,(Display *a,صحیح b,کھڑکی_2 c,صحیح d,XIEvent_نقاب *e,صحیح f,XIGrabModifiers *g))
SDL_X11_SYM(صحیح,XIUngrabTouchBegin, (Display *a,صحیح b,کھڑکی_2 c, صحیح d,XIGrabModifiers *e))
SDL_X11_SYM(حالت_3,XIQuery_نسخہ,(Display *a,صحیح *b,صحیح *c))
SDL_X11_SYM(XIEvent_نقاب*,XIGetSelectedEvents,(Display *a,کھڑکی_2 b,صحیح *c))
SDL_X11_SYM(Bool,XIGet_Client_اشارہ_گر,(Display *a,کھڑکی_2 b,صحیح *c))
SDL_X11_SYM(Bool,XIWarp_اشارہ_گر,(Display *a,صحیح b,کھڑکی_2 c,کھڑکی_2 d,دوہرا e,دوہرا f,صحیح g,صحیح h,دوہرا i,دوہرا j))
SDL_X11_SYM(حالت_3,XIGetProperty,(Display *a,صحیح b,Atom c,طویل d,طویل e,Bool f, Atom g, Atom *h, صحیح *i, غیرعلامتی طویل *j, غیرعلامتی طویل *k, غیرعلامتی حرف **l))
#اگر_ختم

// XRandR support
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XRANDR
SDL_X11_MODULE(XRANDR)
SDL_X11_SYM(حالت_3,XRRQuery_نسخہ,(Display *dpy,صحیح *major_versionp,صحیح *minor_versionp))
SDL_X11_SYM(Bool,XRRQueryExtension,(Display *dpy,صحیح *event_بنیاد_return,صحیح *error_بنیاد_return))
SDL_X11_SYM(XRRScreenConfiguration *,XRRGetScreenInfo,(Display *dpy,Drawable draw))
SDL_X11_SYM(سائز_ID,XRRConfigCurrentConfiguration,(XRRScreenConfiguration *config,Rotation *rotation))
SDL_X11_SYM(مختصر,XRRConfig_Current_شرح,(XRRScreenConfiguration *config))
SDL_X11_SYM(مختصر *,XRRConfigRates,(XRRScreenConfiguration *config,صحیح سائز_ID_2,صحیح *nrates))
SDL_X11_SYM(XRRScreen_سائز *,XRRConfigSizes,(XRRScreenConfiguration *config,صحیح *nsizes))
SDL_X11_SYM(حالت_3,XRRSet_Screen_Config_And_شرح,(Display *dpy,XRRScreenConfiguration *config,Drawable draw,صحیح سائز_اشاریہ,Rotation rotation,مختصر شرح,وقت_2 timestamp))
SDL_X11_SYM(خالی,XRRFreeScreenConfigInfo,(XRRScreenConfiguration *config))
SDL_X11_SYM(خالی,XRRSet_Screen_سائز,(Display *dpy, کھڑکی_2 کھڑکی,صحیح چوڑائی, صحیح اونچائی,صحیح mm_چوڑائی_2, صحیح mm_اونچائی_2))
SDL_X11_SYM(حالت_3,XRRGet_Screen_سائز_Range,(Display *dpy, کھڑکی_2 کھڑکی,صحیح *min_چوڑائی, صحیح *min_اونچائی, صحیح *max_چوڑائی, صحیح *max_اونچائی))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResources,(Display *dpy, کھڑکی_2 کھڑکی))
SDL_X11_SYM(XRRScreenResources *,XRRGetScreenResourcesCurrent,(Display *dpy, کھڑکی_2 کھڑکی))
SDL_X11_SYM(خالی,XRRFreeScreenResources,(XRRScreenResources *resources))
SDL_X11_SYM(XRROutputInfo *,XRRGetOutputInfo,(Display *dpy, XRRScreenResources *resources, RROutput output))
SDL_X11_SYM(خالی,XRRFreeOutputInfo,(XRROutputInfo *outputInfo))
SDL_X11_SYM(XRRCrtcInfo *,XRRGetCrtcInfo,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc))
SDL_X11_SYM(خالی,XRRFreeCrtcInfo,(XRRCrtcInfo *crtcInfo))
SDL_X11_SYM(حالت_3,XRRSetCrtcConfig,(Display *dpy, XRRScreenResources *resources, RRCrtc crtc, وقت_2 timestamp, صحیح x, صحیح y, RRMode منوال, Rotation rotation, RROutput *outputs, صحیح noutputs))
SDL_X11_SYM(Atom*,XRRListOutputProperties,(Display *dpy, RROutput output, صحیح *nprop))
SDL_X11_SYM(XRRPropertyInfo*,XRRQueryOutputProperty,(Display *dpy,RROutput output, Atom property))
SDL_X11_SYM(صحیح,XRRGetOutputProperty,(Display *dpy,RROutput output, Atom property, طویل انحراف_2, طویل لمبائی, Bool _delete, Bool pending, Atom req_type, Atom *actual_type, صحیح *actual_format, غیرعلامتی طویل *nitems, غیرعلامتی طویل *بائٹیں_after, غیرعلامتی حرف **prop))
SDL_X11_SYM(RROutput,XRRGetOutputPrimary,(Display *dpy,کھڑکی_2 کھڑکی))
SDL_X11_SYM(خالی,XRRSelect_داخلہ,(Display *dpy, کھڑکی_2 کھڑکی, صحیح نقاب))
SDL_X11_SYM(حالت_3,XRRGetCrtcTransform,(Display *dpy,RRCrtc crtc,XRRCrtc_Transform_اوصاف **اوصاف))
#اگر_ختم

// MIT-SCREEN-SAVER support
#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XSCRNSAVER
SDL_X11_MODULE(XSS)
SDL_X11_SYM(Bool,XScreenSaverQueryExtension,(Display *dpy,صحیح *event_بنیاد_2,صحیح *error_بنیاد_2))
SDL_X11_SYM(حالت_3,XScreen_Saver_Query_نسخہ,(Display *dpy,صحیح *major_versionp,صحیح *minor_versionp))
SDL_X11_SYM(خالی,XScreenSaverSuspend,(Display *dpy,Bool suspend))
#اگر_ختم

#اگر_تعریف_شدہ SDL_VIDEO_DRIVER_X11_XSHAPE
SDL_X11_MODULE(XSHAPE)
SDL_X11_SYM(خالی,XShape_Combine_نقاب,(Display *dpy,کھڑکی_2 dest,صحیح dest_قسم,صحیح x_off,صحیح y_off,Pixmap src,صحیح op))
SDL_X11_SYM(خالی,XShapeCombineRegion,(Display *a,کھڑکی_2 b,صحیح c,صحیح d,صحیح e,Region f,صحیح g))
#اگر_ختم

#تعریف_منسوخ SDL_X11_MODULE
#تعریف_منسوخ SDL_X11_SYM

/* *INDENT-ON* */ // clang-format on

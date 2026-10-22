/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org>
  Copyright (C) 2018-2019 EXL <exlmotodev@gmail.com>

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

#جيڪڏهن_وصف_ٿيل SDL_VIDEO_DRIVER_HAIKU


// For application signature.
#ضمن "../../core/haiku/SDL_BeApp.h"

#ضمن <Alert.h>
#ضمن <Application.h>
#ضمن <Button.h>
#ضمن <Font.h>
#ضمن <Layout.h>
#ضمن <String.h>
#ضمن <TextView.h>
#ضمن <View.h>
#ضمن <Window.h>

#ضمن <InterfaceDefs.h>
#ضمن <SupportDefs.h>
#ضمن <GraphicsDefs.h>

#ضمن <new>
#ضمن <vector>
#ضمن <algorithm>
#ضمن <memory>

تعداد
{
	G_CLOSE_BUTTON_ID   = -1,
	G_DEFAULT_BUTTON_ID = 0,
	G_MAX_STRING_ڊيگهائي_بائيٽون = 120
};

صنف HAIKU_SDL_پيغام_Box : عام BAlert
{
	عائم f_Computed_پيغام_Box_ويڪر;

	BTextView *f_پيغام_Box_متن_View;

	صحيح fCloseButton;
	صحيح fDefaultButton;

	منطقي fCustomColorScheme;
	منطقي f_There_Is_Long_سٽ;
	rgb_color f_متن_Color;

	ثابت حرف *fTitle;
	ثابت حرف *HAIKU_SDL_DefTitle;
	ثابت حرف *HAIKU_SDL_Def_پيغام;
	ثابت حرف *HAIKU_SDL_DefButton;

	std::ويڪٽر<ثابت SDL_پيغام_Box_Button_معلومات *> fButtons;

	ساكن منطقي
	ترتيب_ڏيو_Buttons_Predicate(ثابت SDL_پيغام_Box_Button_معلومات *a_Button_کاٻو,
	                                 ثابت SDL_پيغام_Box_Button_معلومات *a_Button_ساڄو)
	{
		أرجع a_Button_کاٻو->buttonID < a_Button_ساڄو->buttonID;
	}

	alert_type
	Convert_پيغام_Box_Type(ثابت SDL_پيغام_Box_Flags a_دري_Type) ثابت
	{
		بدل (a_دري_Type)
		{
			افتراضي:
			حالة SDL_MESSAGEBOX_WARNING:
			{
				أرجع B_WARNING_ALERT;
			}
			حالة SDL_MESSAGEBOX_ERROR:
			{
				أرجع B_STOP_ALERT;
			}
			حالة SDL_MESSAGEBOX_INFORMATION:
			{
				أرجع B_INFO_ALERT;
			}
		}
	}

	rgb_color
	ConvertColorType(ثابت SDL_پيغام_Box_Color *aColor) ثابت
	{
		rgb_color color = { aColor->r, aColor->g, aColor->b, color.alpha = 255 };
		أرجع color;
	}

	int32
	Get_کاٻو_Panel_ويڪر(فراغ) ثابت
	{
		// See file "haiku/src/kits/interface/Alert.cpp" for this magic numbers.
		//    IconStripeWidth = 30 * Scale
		//    IconSize = 32 * Scale
		//    Scale = max_c(1, ((int32)be_plain_font->Size() + 15) / 16)
		//    RealWidth = (IconStripeWidth * Scale) + (IconSize * Scale)

		int32 scale = max_c(1, ((int32)be_plain_font->سائيز_2() + 15) / 16);
		أرجع (30 * scale) + (32 * scale);
	}

	فراغ
	Update_متن_View_ويڪر(فراغ)
	{
		f_Computed_پيغام_Box_ويڪر = f_پيغام_Box_متن_View->Preferred_سائيز().ويڪر_2() + Get_کاٻو_Panel_ويڪر();
	}

	فراغ
	Parse_Sdl_پيغام_Box_معلومات(ثابت SDL_پيغام_Box_معلومات *a_پيغام_Box_معلومات)
	{
		إذا (a_پيغام_Box_معلومات == عدم) {
			سيٽ_Title_2(HAIKU_SDL_DefTitle);
			سيٽ_پيغام_متن(HAIKU_SDL_Def_پيغام);
			جوڙيو_Button(HAIKU_SDL_DefButton);
			أرجع;
		}

		إذا (a_پيغام_Box_معلومات->numbuttons <= 0) {
			جوڙيو_Button(HAIKU_SDL_DefButton);
		} وإلا {
			جوڙيو_Sdl_Buttons(a_پيغام_Box_معلومات->buttons, a_پيغام_Box_معلومات->numbuttons);
		}

		إذا (a_پيغام_Box_معلومات->colorScheme != عدم) {
			fCustomColorScheme = سچ;
			ApplyAndParseColorScheme(a_پيغام_Box_معلومات->colorScheme);
		}

		(a_پيغام_Box_معلومات->title[0]) ?
			سيٽ_Title_2(a_پيغام_Box_معلومات->title) : سيٽ_Title_2(HAIKU_SDL_DefTitle);
		(a_پيغام_Box_معلومات->پيغام[0]) ?
			سيٽ_پيغام_متن(a_پيغام_Box_معلومات->پيغام) : سيٽ_پيغام_متن(HAIKU_SDL_Def_پيغام);

		سيٽ_Type(Convert_پيغام_Box_Type(a_پيغام_Box_معلومات->flags));
	}

	فراغ
	ApplyAndParseColorScheme(ثابت SDL_پيغام_Box_Color_Scheme *aColorScheme)
	{
		سيٽ_Background_Color(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BACKGROUND]);
		f_متن_Color = ConvertColorType(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_متن]);
		سيٽ_Button_Colors(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_متن],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED]);
	}

	فراغ
	سيٽ_Button_Colors(ثابت SDL_پيغام_Box_Color *aBorderColor,
	                ثابت SDL_پيغام_Box_Color *aBackgroundColor,
	                ثابت SDL_پيغام_Box_Color *a_متن_Color,
	                ثابت SDL_پيغام_Box_Color *aSelectedColor)
	{
		إذا (fCustomColorScheme) {
			int32 ڳڻپ_Buttons = ڳڻپ_Buttons_2();
			لكل (صحيح i = 0; i < ڳڻپ_Buttons; ++i) {
				ButtonAt(i)->سيٽ_View_Color(ConvertColorType(aBorderColor));
				ButtonAt(i)->سيٽ_هيٺيون_Color(ConvertColorType(aBackgroundColor));

				// This doesn't work. See this why:
				// https://github.com/haiku/haiku/commit/de9c53f8f5008c7b3b0af75d944a628e17f6dffe
				// Let it remain.
				ButtonAt(i)->سيٽ_مٿاهون_Color(ConvertColorType(a_متن_Color));
			}
		}
		// TODO: Not Implemented.
		// Is it even necessary?!
		(فراغ)aSelectedColor;
	}

	فراغ
	سيٽ_Background_Color(ثابت SDL_پيغام_Box_Color *aColor)
	{
		rgb_color background = ConvertColorType(aColor);

		GetLayout()->View()->سيٽ_View_Color(background);
		// See file "haiku/src/kits/interface/Alert.cpp", the "TAlertView" is the internal name of the left panel.
		ڳوليو_View("TAlertView")->سيٽ_View_Color(background);
		f_پيغام_Box_متن_View->سيٽ_View_Color(background);
	}

	منطقي
	Check_Long_سٽون(ثابت حرف *a_پيغام)
	{
		صحيح final = 0;

		// This UTF-8 friendly.
		BString پيغام = a_پيغام;
		int32 ڊيگهائي = پيغام.ڳڻپ_Chars();

		لكل (صحيح i = 0, c = 0; i < ڊيگهائي; ++i) {
			c++;
			إذا (*(پيغام.CharAt(i)) == '\n') {
				c = 0;
			}
			إذا (c > final) {
				final = c;
			}
		}

		أرجع (final > G_MAX_STRING_ڊيگهائي_بائيٽون);
	}

	فراغ
	سيٽ_پيغام_متن(ثابت حرف *a_پيغام)
	{
		f_There_Is_Long_سٽ = Check_Long_سٽون(a_پيغام);
		إذا (f_There_Is_Long_سٽ) {
			f_پيغام_Box_متن_View->سيٽ_لفظ_Wrap(سچ);
		}

		rgb_color متن_Color = ui_color(B_PANEL_متن_COLOR);
		إذا (fCustomColorScheme) {
			متن_Color = f_متن_Color;
		}

		/*
		if (fNoTitledWindow) {
			fMessageBoxTextView->SetFontAndColor(be_bold_font);
			fMessageBoxTextView->Insert(fTitle);
			fMessageBoxTextView->Insert("\n\n");
			fMessageBoxTextView->SetFontAndColor(be_plain_font);
		}
		*/

		f_پيغام_Box_متن_View->سيٽ_Font_And_Color(be_plain_font, B_FONT_ALL, &متن_Color);
		f_پيغام_Box_متن_View->وجهو(a_پيغام);

		// Be sure to call update width method.
		Update_متن_View_ويڪر();
	}

	فراغ
	جوڙيو_Sdl_Buttons(ثابت SDL_پيغام_Box_Button_معلومات *aButtons, صحيح a_انگ_Buttons)
	{
		لكل (صحيح i = 0; i < a_انگ_Buttons; ++i) {
			fButtons.ڌڪو_پٺ(&aButtons[i]);
		}

		std::ترتيب_ڏيو(fButtons.begin(), fButtons.پڇاڙي(), &HAIKU_SDL_پيغام_Box::ترتيب_ڏيو_Buttons_Predicate);

		size_t ڳڻپ_Buttons = fButtons.سائيز();
		لكل (size_t i = 0; i < ڳڻپ_Buttons; ++i) {
			إذا (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
                fCloseButton = static_cast<صحيح>(i);
            }
			إذا (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
                fDefaultButton = static_cast<صحيح>(i);
            }
			جوڙيو_Button(fButtons[i]->متن);
		}

		سيٽ_Default_Button(ButtonAt(fDefaultButton));
	}

عام:
	واضح
	HAIKU_SDL_پيغام_Box(ثابت SDL_پيغام_Box_معلومات *a_پيغام_Box_معلومات)
		: BAlert(عدم, عدم, عدم, عدم, عدم, B_ويڪر_FROM_LABEL, B_WARNING_ALERT),
		  f_Computed_پيغام_Box_ويڪر(0.0f),
		  fCloseButton(G_CLOSE_BUTTON_ID), fDefaultButton(G_DEFAULT_BUTTON_ID),
		  fCustomColorScheme(خطأ), f_There_Is_Long_سٽ(خطأ),
		  HAIKU_SDL_DefTitle("SDL MessageBox"),
		  HAIKU_SDL_Def_پيغام("Some information has been lost."),
		  HAIKU_SDL_DefButton("OK")
	{
		// MessageBox settings.
		// We need a title to display it.
		سيٽ_Look(B_TITLED_دري_LOOK);
		سيٽ_Flags(Flags() | B_CLOSE_ON_ESCAPE);

		// MessageBox TextView settings.
		f_پيغام_Box_متن_View = متن_View();
		f_پيغام_Box_متن_View->سيٽ_لفظ_Wrap(خطأ);
		f_پيغام_Box_متن_View->سيٽ_Stylable(سچ);

		Parse_Sdl_پيغام_Box_معلومات(a_پيغام_Box_معلومات);
	}

	صحيح
	GetCloseButtonId(فراغ) ثابت
	{
		أرجع fCloseButton;
	}

	مجازي
	~HAIKU_SDL_پيغام_Box(فراغ)
	{
		fButtons.clear();
	}

محمي:
	مجازي فراغ
	چوکٺو_Resized(عائم a_New_ويڪر, عائم a_New_اوچائي)
	{
		إذا (f_Computed_پيغام_Box_ويڪر > a_New_ويڪر) {
			Resize_منزل(f_Computed_پيغام_Box_ويڪر, a_New_اوچائي);
		} وإلا {
			BAlert::چوکٺو_Resized(a_New_ويڪر, a_New_اوچائي);
		}
	}

	مجازي فراغ
	سيٽ_Title_2(ثابت حرف *aTitle)
	{
		fTitle = aTitle;
		BAlert::سيٽ_Title_2(aTitle);
	}
};

#جيڪڏهن_وصف_ٿيل __cplusplus
خارجي "C" {
#جيڪڏهن_پورو

منطقي HAIKU_Show_پيغام_Box(ثابت SDL_پيغام_Box_معلومات *messageboxdata, صحيح *buttonID)
{
	// Initialize button by closed or error value first.
	*buttonID = G_CLOSE_BUTTON_ID;

	// We need to check "be_app" pointer to "NULL". The "messageboxdata->window" pointer isn't appropriate here
	// because it is possible to create a MessageBox from another thread. This fixes the following errors:
	// "You need a valid BApplication object before interacting with the app_server."
	// "2 BApplication objects were created. Only one is allowed."
	std::unique_ptr<BApplication> application;
	إذا (!be_app) {
		application = std::unique_ptr<BApplication>(جديد(std::nothrow) BApplication(SDL_signature));
		إذا (!application) {
			أرجع SDL_سيٽ_Error("Cannot create the BApplication object. Lack of memory?");
		}
	}

	HAIKU_SDL_پيغام_Box *SDL_پيغام_Box = جديد(std::nothrow) HAIKU_SDL_پيغام_Box(messageboxdata);
	إذا (!SDL_پيغام_Box) {
		أرجع SDL_سيٽ_Error("Cannot create the HAIKU_SDL_MessageBox (BAlert inheritor) object. Lack of memory?");
	}
	ثابت صحيح closeButton = SDL_پيغام_Box->GetCloseButtonId();
	صحيح pushedButton = SDL_پيغام_Box->Go();

	// The close button is equivalent to pressing Escape.
	إذا (closeButton != G_CLOSE_BUTTON_ID && pushedButton == G_CLOSE_BUTTON_ID) {
		pushedButton = closeButton;
	}

	// It's deleted by itself after the "Go()" method was executed.
	/*
	if (messageBox != NULL) {
		delete messageBox;
	}
	*/
	// Initialize button by real pushed value then.
	*buttonID = pushedButton;

	أرجع سچ;
}

#جيڪڏهن_وصف_ٿيل __cplusplus
}
#جيڪڏهن_پورو

#جيڪڏهن_پورو // SDL_VIDEO_DRIVER_HAIKU

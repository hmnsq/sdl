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

#جے_تعریف_شدہ SDL_VIDEO_DRIVER_HAIKU


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
	G_MAX_STRING_لمائی_بائٹاں = 120
};

صنف HAIKU_SDL_سنیہا_Box : عام BAlert
{
	عائم f_Computed_سنیہا_Box_چوڑائی;

	BTextView *f_سنیہا_Box_متن_View;

	صحيح fCloseButton;
	صحيح fDefaultButton;

	منطقي fCustomColorScheme;
	منطقي f_There_Is_Long_سطر;
	rgb_color f_متن_Color;

	ثابت حرف *fTitle;
	ثابت حرف *HAIKU_SDL_DefTitle;
	ثابت حرف *HAIKU_SDL_Def_سنیہا;
	ثابت حرف *HAIKU_SDL_DefButton;

	std::سمتیہ<ثابت SDL_سنیہا_Box_Button_انکڑے *> fButtons;

	ساكن منطقي
	ترتیب_دیو_Buttons_Predicate(ثابت SDL_سنیہا_Box_Button_انکڑے *a_Button_بایاں,
	                                 ثابت SDL_سنیہا_Box_Button_انکڑے *a_Button_دایاں)
	{
		أرجع a_Button_بایاں->buttonID < a_Button_دایاں->buttonID;
	}

	alert_type
	Convert_سنیہا_Box_Type(ثابت SDL_سنیہا_Box_Flags a_کھڑکی_Type) ثابت
	{
		بدل (a_کھڑکی_Type)
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
	ConvertColorType(ثابت SDL_سنیہا_Box_Color *aColor) ثابت
	{
		rgb_color color = { aColor->r, aColor->g, aColor->b, color.alpha = 255 };
		أرجع color;
	}

	int32
	Get_بایاں_Panel_چوڑائی(فراغ) ثابت
	{
		// See file "haiku/src/kits/interface/Alert.cpp" for this magic numbers.
		//    IconStripeWidth = 30 * Scale
		//    IconSize = 32 * Scale
		//    Scale = max_c(1, ((int32)be_plain_font->Size() + 15) / 16)
		//    RealWidth = (IconStripeWidth * Scale) + (IconSize * Scale)

		int32 scale = max_c(1, ((int32)be_plain_font->ناپ_2() + 15) / 16);
		أرجع (30 * scale) + (32 * scale);
	}

	فراغ
	Update_متن_View_چوڑائی(فراغ)
	{
		f_Computed_سنیہا_Box_چوڑائی = f_سنیہا_Box_متن_View->Preferred_ناپ().چوڑائی_2() + Get_بایاں_Panel_چوڑائی();
	}

	فراغ
	Parse_Sdl_سنیہا_Box_انکڑے(ثابت SDL_سنیہا_Box_انکڑے *a_سنیہا_Box_انکڑے)
	{
		إذا (a_سنیہا_Box_انکڑے == عدم) {
			سیٹ_Title_2(HAIKU_SDL_DefTitle);
			سیٹ_سنیہا_متن(HAIKU_SDL_Def_سنیہا);
			جوڑو_Button(HAIKU_SDL_DefButton);
			أرجع;
		}

		إذا (a_سنیہا_Box_انکڑے->numbuttons <= 0) {
			جوڑو_Button(HAIKU_SDL_DefButton);
		} وإلا {
			جوڑو_Sdl_Buttons(a_سنیہا_Box_انکڑے->buttons, a_سنیہا_Box_انکڑے->numbuttons);
		}

		إذا (a_سنیہا_Box_انکڑے->colorScheme != عدم) {
			fCustomColorScheme = سچ;
			ApplyAndParseColorScheme(a_سنیہا_Box_انکڑے->colorScheme);
		}

		(a_سنیہا_Box_انکڑے->title[0]) ?
			سیٹ_Title_2(a_سنیہا_Box_انکڑے->title) : سیٹ_Title_2(HAIKU_SDL_DefTitle);
		(a_سنیہا_Box_انکڑے->سنیہا[0]) ?
			سیٹ_سنیہا_متن(a_سنیہا_Box_انکڑے->سنیہا) : سیٹ_سنیہا_متن(HAIKU_SDL_Def_سنیہا);

		سیٹ_Type(Convert_سنیہا_Box_Type(a_سنیہا_Box_انکڑے->flags));
	}

	فراغ
	ApplyAndParseColorScheme(ثابت SDL_سنیہا_Box_Color_Scheme *aColorScheme)
	{
		سیٹ_Background_Color(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BACKGROUND]);
		f_متن_Color = ConvertColorType(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_متن]);
		سیٹ_Button_Colors(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_متن],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED]);
	}

	فراغ
	سیٹ_Button_Colors(ثابت SDL_سنیہا_Box_Color *aBorderColor,
	                ثابت SDL_سنیہا_Box_Color *aBackgroundColor,
	                ثابت SDL_سنیہا_Box_Color *a_متن_Color,
	                ثابت SDL_سنیہا_Box_Color *aSelectedColor)
	{
		إذا (fCustomColorScheme) {
			int32 گنتی_Buttons = گنتی_Buttons_2();
			لكل (صحيح i = 0; i < گنتی_Buttons; ++i) {
				ButtonAt(i)->سیٹ_View_Color(ConvertColorType(aBorderColor));
				ButtonAt(i)->سیٹ_کم_Color(ConvertColorType(aBackgroundColor));

				// This doesn't work. See this why:
				// https://github.com/haiku/haiku/commit/de9c53f8f5008c7b3b0af75d944a628e17f6dffe
				// Let it remain.
				ButtonAt(i)->سیٹ_بلند_Color(ConvertColorType(a_متن_Color));
			}
		}
		// TODO: Not Implemented.
		// Is it even necessary?!
		(فراغ)aSelectedColor;
	}

	فراغ
	سیٹ_Background_Color(ثابت SDL_سنیہا_Box_Color *aColor)
	{
		rgb_color background = ConvertColorType(aColor);

		GetLayout()->View()->سیٹ_View_Color(background);
		// See file "haiku/src/kits/interface/Alert.cpp", the "TAlertView" is the internal name of the left panel.
		لبھو_View("TAlertView")->سیٹ_View_Color(background);
		f_سنیہا_Box_متن_View->سیٹ_View_Color(background);
	}

	منطقي
	Check_Long_سطریں(ثابت حرف *a_سنیہا)
	{
		صحيح final = 0;

		// This UTF-8 friendly.
		BString سنیہا = a_سنیہا;
		int32 لمائی = سنیہا.گنتی_Chars();

		لكل (صحيح i = 0, c = 0; i < لمائی; ++i) {
			c++;
			إذا (*(سنیہا.CharAt(i)) == '\n') {
				c = 0;
			}
			إذا (c > final) {
				final = c;
			}
		}

		أرجع (final > G_MAX_STRING_لمائی_بائٹاں);
	}

	فراغ
	سیٹ_سنیہا_متن(ثابت حرف *a_سنیہا)
	{
		f_There_Is_Long_سطر = Check_Long_سطریں(a_سنیہا);
		إذا (f_There_Is_Long_سطر) {
			f_سنیہا_Box_متن_View->سیٹ_لفظ_Wrap(سچ);
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

		f_سنیہا_Box_متن_View->سیٹ_Font_And_Color(be_plain_font, B_FONT_ALL, &متن_Color);
		f_سنیہا_Box_متن_View->داخل_کرو(a_سنیہا);

		// Be sure to call update width method.
		Update_متن_View_چوڑائی();
	}

	فراغ
	جوڑو_Sdl_Buttons(ثابت SDL_سنیہا_Box_Button_انکڑے *aButtons, صحيح a_عدد_Buttons)
	{
		لكل (صحيح i = 0; i < a_عدد_Buttons; ++i) {
			fButtons.ڈالو_پٹھ(&aButtons[i]);
		}

		std::ترتیب_دیو(fButtons.begin(), fButtons.سرا(), &HAIKU_SDL_سنیہا_Box::ترتیب_دیو_Buttons_Predicate);

		size_t گنتی_Buttons = fButtons.ناپ();
		لكل (size_t i = 0; i < گنتی_Buttons; ++i) {
			إذا (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
                fCloseButton = static_cast<صحيح>(i);
            }
			إذا (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
                fDefaultButton = static_cast<صحيح>(i);
            }
			جوڑو_Button(fButtons[i]->متن);
		}

		سیٹ_Default_Button(ButtonAt(fDefaultButton));
	}

عام:
	واضح
	HAIKU_SDL_سنیہا_Box(ثابت SDL_سنیہا_Box_انکڑے *a_سنیہا_Box_انکڑے)
		: BAlert(عدم, عدم, عدم, عدم, عدم, B_چوڑائی_FROM_LABEL, B_WARNING_ALERT),
		  f_Computed_سنیہا_Box_چوڑائی(0.0f),
		  fCloseButton(G_CLOSE_BUTTON_ID), fDefaultButton(G_DEFAULT_BUTTON_ID),
		  fCustomColorScheme(خطأ), f_There_Is_Long_سطر(خطأ),
		  HAIKU_SDL_DefTitle("SDL MessageBox"),
		  HAIKU_SDL_Def_سنیہا("Some information has been lost."),
		  HAIKU_SDL_DefButton("OK")
	{
		// MessageBox settings.
		// We need a title to display it.
		سیٹ_Look(B_TITLED_کھڑکی_LOOK);
		سیٹ_Flags(Flags() | B_CLOSE_ON_ESCAPE);

		// MessageBox TextView settings.
		f_سنیہا_Box_متن_View = متن_View();
		f_سنیہا_Box_متن_View->سیٹ_لفظ_Wrap(خطأ);
		f_سنیہا_Box_متن_View->سیٹ_Stylable(سچ);

		Parse_Sdl_سنیہا_Box_انکڑے(a_سنیہا_Box_انکڑے);
	}

	صحيح
	GetCloseButtonId(فراغ) ثابت
	{
		أرجع fCloseButton;
	}

	مجازی
	~HAIKU_SDL_سنیہا_Box(فراغ)
	{
		fButtons.clear();
	}

محمي:
	مجازی فراغ
	چوکھٹا_Resized(عائم a_New_چوڑائی, عائم a_New_اچائی)
	{
		إذا (f_Computed_سنیہا_Box_چوڑائی > a_New_چوڑائی) {
			Resize_منزل(f_Computed_سنیہا_Box_چوڑائی, a_New_اچائی);
		} وإلا {
			BAlert::چوکھٹا_Resized(a_New_چوڑائی, a_New_اچائی);
		}
	}

	مجازی فراغ
	سیٹ_Title_2(ثابت حرف *aTitle)
	{
		fTitle = aTitle;
		BAlert::سیٹ_Title_2(aTitle);
	}
};

#جے_تعریف_شدہ __cplusplus
خارجي "C" {
#جے_انت

منطقي HAIKU_Show_سنیہا_Box(ثابت SDL_سنیہا_Box_انکڑے *messageboxdata, صحيح *buttonID)
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
			أرجع SDL_سیٹ_Error("Cannot create the BApplication object. Lack of memory?");
		}
	}

	HAIKU_SDL_سنیہا_Box *SDL_سنیہا_Box = جديد(std::nothrow) HAIKU_SDL_سنیہا_Box(messageboxdata);
	إذا (!SDL_سنیہا_Box) {
		أرجع SDL_سیٹ_Error("Cannot create the HAIKU_SDL_MessageBox (BAlert inheritor) object. Lack of memory?");
	}
	ثابت صحيح closeButton = SDL_سنیہا_Box->GetCloseButtonId();
	صحيح pushedButton = SDL_سنیہا_Box->Go();

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

#جے_تعریف_شدہ __cplusplus
}
#جے_انت

#جے_انت // SDL_VIDEO_DRIVER_HAIKU

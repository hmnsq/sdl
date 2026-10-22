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

#که_تعریف_شوی SDL_VIDEO_DRIVER_HAIKU


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
	G_MAX_STRING_اوږدتیا_بایټونه = 120
};

صنف HAIKU_SDL_پیغام_Box : عام BAlert
{
	عائم f_Computed_پیغام_Box_پلنوالی;

	BTextView *f_پیغام_Box_متن_View;

	صحيح fCloseButton;
	صحيح fDefaultButton;

	منطقي fCustomColorScheme;
	منطقي f_There_Is_Long_کرښه;
	rgb_color f_متن_Color;

	ثابت حرف *fTitle;
	ثابت حرف *HAIKU_SDL_DefTitle;
	ثابت حرف *HAIKU_SDL_Def_پیغام;
	ثابت حرف *HAIKU_SDL_DefButton;

	std::ویکټور<ثابت SDL_پیغام_Box_Button_معلومات *> fButtons;

	ساكن منطقي
	ترتیبول_Buttons_Predicate(ثابت SDL_پیغام_Box_Button_معلومات *a_Button_کیڼ,
	                                 ثابت SDL_پیغام_Box_Button_معلومات *a_Button_ښی)
	{
		أرجع a_Button_کیڼ->buttonID < a_Button_ښی->buttonID;
	}

	alert_type
	Convert_پیغام_Box_Type(ثابت SDL_پیغام_Box_Flags a_کړکۍ_Type) ثابت
	{
		بدل (a_کړکۍ_Type)
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
	ConvertColorType(ثابت SDL_پیغام_Box_Color *aColor) ثابت
	{
		rgb_color color = { aColor->r, aColor->g, aColor->b, color.alpha = 255 };
		أرجع color;
	}

	int32
	Get_کیڼ_Panel_پلنوالی(فراغ) ثابت
	{
		// See file "haiku/src/kits/interface/Alert.cpp" for this magic numbers.
		//    IconStripeWidth = 30 * Scale
		//    IconSize = 32 * Scale
		//    Scale = max_c(1, ((int32)be_plain_font->Size() + 15) / 16)
		//    RealWidth = (IconStripeWidth * Scale) + (IconSize * Scale)

		int32 scale = max_c(1, ((int32)be_plain_font->اندازه_2() + 15) / 16);
		أرجع (30 * scale) + (32 * scale);
	}

	فراغ
	Update_متن_View_پلنوالی(فراغ)
	{
		f_Computed_پیغام_Box_پلنوالی = f_پیغام_Box_متن_View->Preferred_اندازه().پلنوالی_2() + Get_کیڼ_Panel_پلنوالی();
	}

	فراغ
	Parse_Sdl_پیغام_Box_معلومات(ثابت SDL_پیغام_Box_معلومات *a_پیغام_Box_معلومات)
	{
		إذا (a_پیغام_Box_معلومات == عدم) {
			سېټ_Title_2(HAIKU_SDL_DefTitle);
			سېټ_پیغام_متن(HAIKU_SDL_Def_پیغام);
			جمع_کړه_Button(HAIKU_SDL_DefButton);
			أرجع;
		}

		إذا (a_پیغام_Box_معلومات->numbuttons <= 0) {
			جمع_کړه_Button(HAIKU_SDL_DefButton);
		} وإلا {
			جمع_کړه_Sdl_Buttons(a_پیغام_Box_معلومات->buttons, a_پیغام_Box_معلومات->numbuttons);
		}

		إذا (a_پیغام_Box_معلومات->colorScheme != عدم) {
			fCustomColorScheme = ریښتیا;
			ApplyAndParseColorScheme(a_پیغام_Box_معلومات->colorScheme);
		}

		(a_پیغام_Box_معلومات->title[0]) ?
			سېټ_Title_2(a_پیغام_Box_معلومات->title) : سېټ_Title_2(HAIKU_SDL_DefTitle);
		(a_پیغام_Box_معلومات->پیغام[0]) ?
			سېټ_پیغام_متن(a_پیغام_Box_معلومات->پیغام) : سېټ_پیغام_متن(HAIKU_SDL_Def_پیغام);

		سېټ_Type(Convert_پیغام_Box_Type(a_پیغام_Box_معلومات->flags));
	}

	فراغ
	ApplyAndParseColorScheme(ثابت SDL_پیغام_Box_Color_Scheme *aColorScheme)
	{
		سېټ_Background_Color(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BACKGROUND]);
		f_متن_Color = ConvertColorType(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_متن]);
		سېټ_Button_Colors(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_متن],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED]);
	}

	فراغ
	سېټ_Button_Colors(ثابت SDL_پیغام_Box_Color *aBorderColor,
	                ثابت SDL_پیغام_Box_Color *aBackgroundColor,
	                ثابت SDL_پیغام_Box_Color *a_متن_Color,
	                ثابت SDL_پیغام_Box_Color *aSelectedColor)
	{
		إذا (fCustomColorScheme) {
			int32 شمېر_Buttons = شمېر_Buttons_2();
			لكل (صحيح i = 0; i < شمېر_Buttons; ++i) {
				ButtonAt(i)->سېټ_View_Color(ConvertColorType(aBorderColor));
				ButtonAt(i)->سېټ_ټیټ_Color(ConvertColorType(aBackgroundColor));

				// This doesn't work. See this why:
				// https://github.com/haiku/haiku/commit/de9c53f8f5008c7b3b0af75d944a628e17f6dffe
				// Let it remain.
				ButtonAt(i)->سېټ_لوړ_Color(ConvertColorType(a_متن_Color));
			}
		}
		// TODO: Not Implemented.
		// Is it even necessary?!
		(فراغ)aSelectedColor;
	}

	فراغ
	سېټ_Background_Color(ثابت SDL_پیغام_Box_Color *aColor)
	{
		rgb_color background = ConvertColorType(aColor);

		GetLayout()->View()->سېټ_View_Color(background);
		// See file "haiku/src/kits/interface/Alert.cpp", the "TAlertView" is the internal name of the left panel.
		پیدا_کړه_View("TAlertView")->سېټ_View_Color(background);
		f_پیغام_Box_متن_View->سېټ_View_Color(background);
	}

	منطقي
	Check_Long_کرښې(ثابت حرف *a_پیغام)
	{
		صحيح final = 0;

		// This UTF-8 friendly.
		BString پیغام = a_پیغام;
		int32 اوږدتیا = پیغام.شمېر_Chars();

		لكل (صحيح i = 0, c = 0; i < اوږدتیا; ++i) {
			c++;
			إذا (*(پیغام.CharAt(i)) == '\n') {
				c = 0;
			}
			إذا (c > final) {
				final = c;
			}
		}

		أرجع (final > G_MAX_STRING_اوږدتیا_بایټونه);
	}

	فراغ
	سېټ_پیغام_متن(ثابت حرف *a_پیغام)
	{
		f_There_Is_Long_کرښه = Check_Long_کرښې(a_پیغام);
		إذا (f_There_Is_Long_کرښه) {
			f_پیغام_Box_متن_View->سېټ_کلمه_Wrap(ریښتیا);
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

		f_پیغام_Box_متن_View->سېټ_Font_And_Color(be_plain_font, B_FONT_ALL, &متن_Color);
		f_پیغام_Box_متن_View->ورننباسه(a_پیغام);

		// Be sure to call update width method.
		Update_متن_View_پلنوالی();
	}

	فراغ
	جمع_کړه_Sdl_Buttons(ثابت SDL_پیغام_Box_Button_معلومات *aButtons, صحيح a_عدد_Buttons)
	{
		لكل (صحيح i = 0; i < a_عدد_Buttons; ++i) {
			fButtons.ټېل_شا(&aButtons[i]);
		}

		std::ترتیبول(fButtons.begin(), fButtons.پای_ټکی(), &HAIKU_SDL_پیغام_Box::ترتیبول_Buttons_Predicate);

		size_t شمېر_Buttons = fButtons.اندازه();
		لكل (size_t i = 0; i < شمېر_Buttons; ++i) {
			إذا (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
                fCloseButton = static_cast<صحيح>(i);
            }
			إذا (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
                fDefaultButton = static_cast<صحيح>(i);
            }
			جمع_کړه_Button(fButtons[i]->متن);
		}

		سېټ_Default_Button(ButtonAt(fDefaultButton));
	}

عام:
	څرګند
	HAIKU_SDL_پیغام_Box(ثابت SDL_پیغام_Box_معلومات *a_پیغام_Box_معلومات)
		: BAlert(عدم, عدم, عدم, عدم, عدم, B_پلنوالی_FROM_LABEL, B_WARNING_ALERT),
		  f_Computed_پیغام_Box_پلنوالی(0.0f),
		  fCloseButton(G_CLOSE_BUTTON_ID), fDefaultButton(G_DEFAULT_BUTTON_ID),
		  fCustomColorScheme(خطأ), f_There_Is_Long_کرښه(خطأ),
		  HAIKU_SDL_DefTitle("SDL MessageBox"),
		  HAIKU_SDL_Def_پیغام("Some information has been lost."),
		  HAIKU_SDL_DefButton("OK")
	{
		// MessageBox settings.
		// We need a title to display it.
		سېټ_Look(B_TITLED_کړکۍ_LOOK);
		سېټ_Flags(Flags() | B_CLOSE_ON_ESCAPE);

		// MessageBox TextView settings.
		f_پیغام_Box_متن_View = متن_View();
		f_پیغام_Box_متن_View->سېټ_کلمه_Wrap(خطأ);
		f_پیغام_Box_متن_View->سېټ_Stylable(ریښتیا);

		Parse_Sdl_پیغام_Box_معلومات(a_پیغام_Box_معلومات);
	}

	صحيح
	GetCloseButtonId(فراغ) ثابت
	{
		أرجع fCloseButton;
	}

	مجازي
	~HAIKU_SDL_پیغام_Box(فراغ)
	{
		fButtons.clear();
	}

محمي:
	مجازي فراغ
	چوکاټ_Resized(عائم a_New_پلنوالی, عائم a_New_لوړوالی)
	{
		إذا (f_Computed_پیغام_Box_پلنوالی > a_New_پلنوالی) {
			Resize_منزل(f_Computed_پیغام_Box_پلنوالی, a_New_لوړوالی);
		} وإلا {
			BAlert::چوکاټ_Resized(a_New_پلنوالی, a_New_لوړوالی);
		}
	}

	مجازي فراغ
	سېټ_Title_2(ثابت حرف *aTitle)
	{
		fTitle = aTitle;
		BAlert::سېټ_Title_2(aTitle);
	}
};

#که_تعریف_شوی __cplusplus
خارجي "C" {
#د_که_پای

منطقي HAIKU_Show_پیغام_Box(ثابت SDL_پیغام_Box_معلومات *messageboxdata, صحيح *buttonID)
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
			أرجع SDL_سېټ_Error("Cannot create the BApplication object. Lack of memory?");
		}
	}

	HAIKU_SDL_پیغام_Box *SDL_پیغام_Box = جديد(std::nothrow) HAIKU_SDL_پیغام_Box(messageboxdata);
	إذا (!SDL_پیغام_Box) {
		أرجع SDL_سېټ_Error("Cannot create the HAIKU_SDL_MessageBox (BAlert inheritor) object. Lack of memory?");
	}
	ثابت صحيح closeButton = SDL_پیغام_Box->GetCloseButtonId();
	صحيح pushedButton = SDL_پیغام_Box->Go();

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

	أرجع ریښتیا;
}

#که_تعریف_شوی __cplusplus
}
#د_که_پای

#د_که_پای // SDL_VIDEO_DRIVER_HAIKU

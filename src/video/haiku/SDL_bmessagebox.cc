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

#అన్తర్భావ "SDL_internal.h"

#నిర్వచితమైతే SDL_VIDEO_DRIVER_HAIKU


// For application signature.
#అన్తర్భావ "../../core/haiku/SDL_BeApp.h"

#అన్తర్భావ <Alert.h>
#అన్తర్భావ <Application.h>
#అన్తర్భావ <Button.h>
#అన్తర్భావ <Font.h>
#అన్తర్భావ <Layout.h>
#అన్తర్భావ <String.h>
#అన్తర్భావ <TextView.h>
#అన్తర్భావ <View.h>
#అన్తర్భావ <Window.h>

#అన్తర్భావ <InterfaceDefs.h>
#అన్తర్భావ <SupportDefs.h>
#అన్తర్భావ <GraphicsDefs.h>

#అన్తర్భావ <new>
#అన్తర్భావ <vector>
#అన్తర్భావ <algorithm>
#అన్తర్భావ <memory>

గణన
{
	G_CLOSE_BUTTON_ID   = -1,
	G_DEFAULT_BUTTON_ID = 0,
	G_MAX_STRING_నిడివి_బైట్లు = 120
};

తరగతి HAIKU_SDL_సందేశం_Box : బహిరంగ BAlert
{
	దశాంశం f_Computed_సందేశం_Box_వెడల్పు;

	BTextView *f_సందేశం_Box_పాఠ్యం_View;

	పూర్ణాంకం fCloseButton;
	పూర్ణాంకం fDefaultButton;

	తార్కిక fCustomColorScheme;
	తార్కిక f_There_Is_Long_పంక్తి;
	rgb_color f_పాఠ్యం_Color;

	స్థిరరాశి అక్షరం *fTitle;
	స్థిరరాశి అక్షరం *HAIKU_SDL_DefTitle;
	స్థిరరాశి అక్షరం *HAIKU_SDL_Def_సందేశం;
	స్థిరరాశి అక్షరం *HAIKU_SDL_DefButton;

	std::సదిశ<స్థిరరాశి SDL_సందేశం_Box_Button_దత్తాంశం *> fButtons;

	స్థిర తార్కిక
	క్రమీకరించు_Buttons_Predicate(స్థిరరాశి SDL_సందేశం_Box_Button_దత్తాంశం *a_Button_ఎడమ,
	                                 స్థిరరాశి SDL_సందేశం_Box_Button_దత్తాంశం *a_Button_కుడి)
	{
		తిరిగి a_Button_ఎడమ->buttonID < a_Button_కుడి->buttonID;
	}

	alert_type
	Convert_సందేశం_Box_Type(స్థిరరాశి SDL_సందేశం_Box_Flags a_కిటికీ_Type) స్థిరరాశి
	{
		ఎంపిక (a_కిటికీ_Type)
		{
			అప్రమేయ:
			స్థితి SDL_MESSAGEBOX_WARNING:
			{
				తిరిగి B_WARNING_ALERT;
			}
			స్థితి SDL_MESSAGEBOX_ERROR:
			{
				తిరిగి B_STOP_ALERT;
			}
			స్థితి SDL_MESSAGEBOX_INFORMATION:
			{
				తిరిగి B_INFO_ALERT;
			}
		}
	}

	rgb_color
	ConvertColorType(స్థిరరాశి SDL_సందేశం_Box_Color *aColor) స్థిరరాశి
	{
		rgb_color color = { aColor->r, aColor->g, aColor->b, color.alpha = 255 };
		తిరిగి color;
	}

	int32
	Get_ఎడమ_Panel_వెడల్పు(శూన్య) స్థిరరాశి
	{
		// See file "haiku/src/kits/interface/Alert.cpp" for this magic numbers.
		//    IconStripeWidth = 30 * Scale
		//    IconSize = 32 * Scale
		//    Scale = max_c(1, ((int32)be_plain_font->Size() + 15) / 16)
		//    RealWidth = (IconStripeWidth * Scale) + (IconSize * Scale)

		int32 scale = max_c(1, ((int32)be_plain_font->కొలత_2() + 15) / 16);
		తిరిగి (30 * scale) + (32 * scale);
	}

	శూన్య
	Update_పాఠ్యం_View_వెడల్పు(శూన్య)
	{
		f_Computed_సందేశం_Box_వెడల్పు = f_సందేశం_Box_పాఠ్యం_View->Preferred_కొలత().వెడల్పు_2() + Get_ఎడమ_Panel_వెడల్పు();
	}

	శూన్య
	Parse_Sdl_సందేశం_Box_దత్తాంశం(స్థిరరాశి SDL_సందేశం_Box_దత్తాంశం *a_సందేశం_Box_దత్తాంశం)
	{
		ఒకవేళ (a_సందేశం_Box_దత్తాంశం == ఖాళీ) {
			సమితి_Title_2(HAIKU_SDL_DefTitle);
			సమితి_సందేశం_పాఠ్యం(HAIKU_SDL_Def_సందేశం);
			కూడు_Button(HAIKU_SDL_DefButton);
			తిరిగి;
		}

		ఒకవేళ (a_సందేశం_Box_దత్తాంశం->numbuttons <= 0) {
			కూడు_Button(HAIKU_SDL_DefButton);
		} లేకపోతే {
			కూడు_Sdl_Buttons(a_సందేశం_Box_దత్తాంశం->buttons, a_సందేశం_Box_దత్తాంశం->numbuttons);
		}

		ఒకవేళ (a_సందేశం_Box_దత్తాంశం->colorScheme != ఖాళీ) {
			fCustomColorScheme = నిజం;
			ApplyAndParseColorScheme(a_సందేశం_Box_దత్తాంశం->colorScheme);
		}

		(a_సందేశం_Box_దత్తాంశం->title[0]) ?
			సమితి_Title_2(a_సందేశం_Box_దత్తాంశం->title) : సమితి_Title_2(HAIKU_SDL_DefTitle);
		(a_సందేశం_Box_దత్తాంశం->సందేశం[0]) ?
			సమితి_సందేశం_పాఠ్యం(a_సందేశం_Box_దత్తాంశం->సందేశం) : సమితి_సందేశం_పాఠ్యం(HAIKU_SDL_Def_సందేశం);

		సమితి_Type(Convert_సందేశం_Box_Type(a_సందేశం_Box_దత్తాంశం->flags));
	}

	శూన్య
	ApplyAndParseColorScheme(స్థిరరాశి SDL_సందేశం_Box_Color_Scheme *aColorScheme)
	{
		సమితి_Background_Color(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BACKGROUND]);
		f_పాఠ్యం_Color = ConvertColorType(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_పాఠ్యం]);
		సమితి_Button_Colors(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_పాఠ్యం],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED]);
	}

	శూన్య
	సమితి_Button_Colors(స్థిరరాశి SDL_సందేశం_Box_Color *aBorderColor,
	                స్థిరరాశి SDL_సందేశం_Box_Color *aBackgroundColor,
	                స్థిరరాశి SDL_సందేశం_Box_Color *a_పాఠ్యం_Color,
	                స్థిరరాశి SDL_సందేశం_Box_Color *aSelectedColor)
	{
		ఒకవేళ (fCustomColorScheme) {
			int32 లెక్క_Buttons = లెక్క_Buttons_2();
			కొరకు (పూర్ణాంకం i = 0; i < లెక్క_Buttons; ++i) {
				ButtonAt(i)->సమితి_View_Color(ConvertColorType(aBorderColor));
				ButtonAt(i)->సమితి_దిగువ_Color(ConvertColorType(aBackgroundColor));

				// This doesn't work. See this why:
				// https://github.com/haiku/haiku/commit/de9c53f8f5008c7b3b0af75d944a628e17f6dffe
				// Let it remain.
				ButtonAt(i)->సమితి_ఎగువ_Color(ConvertColorType(a_పాఠ్యం_Color));
			}
		}
		// TODO: Not Implemented.
		// Is it even necessary?!
		(శూన్య)aSelectedColor;
	}

	శూన్య
	సమితి_Background_Color(స్థిరరాశి SDL_సందేశం_Box_Color *aColor)
	{
		rgb_color background = ConvertColorType(aColor);

		GetLayout()->View()->సమితి_View_Color(background);
		// See file "haiku/src/kits/interface/Alert.cpp", the "TAlertView" is the internal name of the left panel.
		కనుగొను_View("TAlertView")->సమితి_View_Color(background);
		f_సందేశం_Box_పాఠ్యం_View->సమితి_View_Color(background);
	}

	తార్కిక
	Check_Long_పంక్తులు(స్థిరరాశి అక్షరం *a_సందేశం)
	{
		పూర్ణాంకం final = 0;

		// This UTF-8 friendly.
		BString సందేశం = a_సందేశం;
		int32 నిడివి = సందేశం.లెక్క_Chars();

		కొరకు (పూర్ణాంకం i = 0, c = 0; i < నిడివి; ++i) {
			c++;
			ఒకవేళ (*(సందేశం.CharAt(i)) == '\n') {
				c = 0;
			}
			ఒకవేళ (c > final) {
				final = c;
			}
		}

		తిరిగి (final > G_MAX_STRING_నిడివి_బైట్లు);
	}

	శూన్య
	సమితి_సందేశం_పాఠ్యం(స్థిరరాశి అక్షరం *a_సందేశం)
	{
		f_There_Is_Long_పంక్తి = Check_Long_పంక్తులు(a_సందేశం);
		ఒకవేళ (f_There_Is_Long_పంక్తి) {
			f_సందేశం_Box_పాఠ్యం_View->సమితి_మాట_Wrap(నిజం);
		}

		rgb_color పాఠ్యం_Color = ui_color(B_PANEL_పాఠ్యం_COLOR);
		ఒకవేళ (fCustomColorScheme) {
			పాఠ్యం_Color = f_పాఠ్యం_Color;
		}

		/*
		if (fNoTitledWindow) {
			fMessageBoxTextView->SetFontAndColor(be_bold_font);
			fMessageBoxTextView->Insert(fTitle);
			fMessageBoxTextView->Insert("\n\n");
			fMessageBoxTextView->SetFontAndColor(be_plain_font);
		}
		*/

		f_సందేశం_Box_పాఠ్యం_View->సమితి_Font_And_Color(be_plain_font, B_FONT_ALL, &పాఠ్యం_Color);
		f_సందేశం_Box_పాఠ్యం_View->చొప్పించు(a_సందేశం);

		// Be sure to call update width method.
		Update_పాఠ్యం_View_వెడల్పు();
	}

	శూన్య
	కూడు_Sdl_Buttons(స్థిరరాశి SDL_సందేశం_Box_Button_దత్తాంశం *aButtons, పూర్ణాంకం a_అంకె_Buttons)
	{
		కొరకు (పూర్ణాంకం i = 0; i < a_అంకె_Buttons; ++i) {
			fButtons.నెట్టు_వెనుక(&aButtons[i]);
		}

		std::క్రమీకరించు(fButtons.begin(), fButtons.చివర(), &HAIKU_SDL_సందేశం_Box::క్రమీకరించు_Buttons_Predicate);

		size_t లెక్క_Buttons = fButtons.కొలత();
		కొరకు (size_t i = 0; i < లెక్క_Buttons; ++i) {
			ఒకవేళ (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
                fCloseButton = static_cast<పూర్ణాంకం>(i);
            }
			ఒకవేళ (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
                fDefaultButton = static_cast<పూర్ణాంకం>(i);
            }
			కూడు_Button(fButtons[i]->పాఠ్యం);
		}

		సమితి_Default_Button(ButtonAt(fDefaultButton));
	}

బహిరంగ:
	స్పష్టమైన
	HAIKU_SDL_సందేశం_Box(స్థిరరాశి SDL_సందేశం_Box_దత్తాంశం *a_సందేశం_Box_దత్తాంశం)
		: BAlert(ఖాళీ, ఖాళీ, ఖాళీ, ఖాళీ, ఖాళీ, B_వెడల్పు_FROM_LABEL, B_WARNING_ALERT),
		  f_Computed_సందేశం_Box_వెడల్పు(0.0f),
		  fCloseButton(G_CLOSE_BUTTON_ID), fDefaultButton(G_DEFAULT_BUTTON_ID),
		  fCustomColorScheme(అబద్ధం), f_There_Is_Long_పంక్తి(అబద్ధం),
		  HAIKU_SDL_DefTitle("SDL MessageBox"),
		  HAIKU_SDL_Def_సందేశం("Some information has been lost."),
		  HAIKU_SDL_DefButton("OK")
	{
		// MessageBox settings.
		// We need a title to display it.
		సమితి_Look(B_TITLED_కిటికీ_LOOK);
		సమితి_Flags(Flags() | B_CLOSE_ON_ESCAPE);

		// MessageBox TextView settings.
		f_సందేశం_Box_పాఠ్యం_View = పాఠ్యం_View();
		f_సందేశం_Box_పాఠ్యం_View->సమితి_మాట_Wrap(అబద్ధం);
		f_సందేశం_Box_పాఠ్యం_View->సమితి_Stylable(నిజం);

		Parse_Sdl_సందేశం_Box_దత్తాంశం(a_సందేశం_Box_దత్తాంశం);
	}

	పూర్ణాంకం
	GetCloseButtonId(శూన్య) స్థిరరాశి
	{
		తిరిగి fCloseButton;
	}

	మాయా
	~HAIKU_SDL_సందేశం_Box(శూన్య)
	{
		fButtons.clear();
	}

రక్షిత:
	మాయా శూన్య
	చట్రం_Resized(దశాంశం a_New_వెడల్పు, దశాంశం a_New_ఎత్తు)
	{
		ఒకవేళ (f_Computed_సందేశం_Box_వెడల్పు > a_New_వెడల్పు) {
			Resize_గమ్యం(f_Computed_సందేశం_Box_వెడల్పు, a_New_ఎత్తు);
		} లేకపోతే {
			BAlert::చట్రం_Resized(a_New_వెడల్పు, a_New_ఎత్తు);
		}
	}

	మాయా శూన్య
	సమితి_Title_2(స్థిరరాశి అక్షరం *aTitle)
	{
		fTitle = aTitle;
		BAlert::సమితి_Title_2(aTitle);
	}
};

#నిర్వచితమైతే __cplusplus
బాహ్య "C" {
#అయితే_ముగింపు

తార్కిక HAIKU_Show_సందేశం_Box(స్థిరరాశి SDL_సందేశం_Box_దత్తాంశం *messageboxdata, పూర్ణాంకం *buttonID)
{
	// Initialize button by closed or error value first.
	*buttonID = G_CLOSE_BUTTON_ID;

	// We need to check "be_app" pointer to "NULL". The "messageboxdata->window" pointer isn't appropriate here
	// because it is possible to create a MessageBox from another thread. This fixes the following errors:
	// "You need a valid BApplication object before interacting with the app_server."
	// "2 BApplication objects were created. Only one is allowed."
	std::unique_ptr<BApplication> application;
	ఒకవేళ (!be_app) {
		application = std::unique_ptr<BApplication>(కొత్త(std::nothrow) BApplication(SDL_signature));
		ఒకవేళ (!application) {
			తిరిగి SDL_సమితి_Error("Cannot create the BApplication object. Lack of memory?");
		}
	}

	HAIKU_SDL_సందేశం_Box *SDL_సందేశం_Box = కొత్త(std::nothrow) HAIKU_SDL_సందేశం_Box(messageboxdata);
	ఒకవేళ (!SDL_సందేశం_Box) {
		తిరిగి SDL_సమితి_Error("Cannot create the HAIKU_SDL_MessageBox (BAlert inheritor) object. Lack of memory?");
	}
	స్థిరరాశి పూర్ణాంకం closeButton = SDL_సందేశం_Box->GetCloseButtonId();
	పూర్ణాంకం pushedButton = SDL_సందేశం_Box->Go();

	// The close button is equivalent to pressing Escape.
	ఒకవేళ (closeButton != G_CLOSE_BUTTON_ID && pushedButton == G_CLOSE_BUTTON_ID) {
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

	తిరిగి నిజం;
}

#నిర్వచితమైతే __cplusplus
}
#అయితే_ముగింపు

#అయితే_ముగింపు // SDL_VIDEO_DRIVER_HAIKU

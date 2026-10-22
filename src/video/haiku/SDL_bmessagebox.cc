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

#अन्तर्भाव "SDL_internal.h"

#यदि_परिभाषितम् SDL_VIDEO_DRIVER_HAIKU


// For application signature.
#अन्तर्भाव "../../core/haiku/SDL_BeApp.h"

#अन्तर्भाव <Alert.h>
#अन्तर्भाव <Application.h>
#अन्तर्भाव <Button.h>
#अन्तर्भाव <Font.h>
#अन्तर्भाव <Layout.h>
#अन्तर्भाव <String.h>
#अन्तर्भाव <TextView.h>
#अन्तर्भाव <View.h>
#अन्तर्भाव <Window.h>

#अन्तर्भाव <InterfaceDefs.h>
#अन्तर्भाव <SupportDefs.h>
#अन्तर्भाव <GraphicsDefs.h>

#अन्तर्भाव <new>
#अन्तर्भाव <vector>
#अन्तर्भाव <algorithm>
#अन्तर्भाव <memory>

गणना
{
	G_CLOSE_BUTTON_ID   = -1,
	G_DEFAULT_BUTTON_ID = 0,
	G_MAX_STRING_दीर्घता_अष्टकानि = 120
};

वर्ग HAIKU_SDL_सन्देशः_Box : सार्वजनिक BAlert
{
	भिन्न f_Computed_सन्देशः_Box_विस्तारः;

	BTextView *f_सन्देशः_Box_Text_View;

	पूर्णाङ्क fCloseButton;
	पूर्णाङ्क fDefaultButton;

	तार्किक fCustomColorScheme;
	तार्किक f_There_Is_Long_पङ्क्तिः;
	rgb_color fTextColor;

	ध्रुव वर्ण *fTitle;
	ध्रुव वर्ण *HAIKU_SDL_DefTitle;
	ध्रुव वर्ण *HAIKU_SDL_Def_सन्देशः;
	ध्रुव वर्ण *HAIKU_SDL_DefButton;

	std::सदिशम्<ध्रुव SDL_सन्देशः_Box_Button_दत्त *> fButtons;

	स्थिर तार्किक
	क्रमय_Buttons_Predicate(ध्रुव SDL_सन्देशः_Box_Button_दत्त *a_Button_वामः,
	                                 ध्रुव SDL_सन्देशः_Box_Button_दत्त *a_Button_दक्षिणः)
	{
		प्रत्यागम a_Button_वामः->buttonID < a_Button_दक्षिणः->buttonID;
	}

	alert_type
	Convert_सन्देशः_Box_Type(ध्रुव SDL_सन्देशः_Box_Flags a_गवाक्षः_Type) ध्रुव
	{
		विकल्प (a_गवाक्षः_Type)
		{
			स्वभाव:
			पक्ष SDL_MESSAGEBOX_WARNING:
			{
				प्रत्यागम B_WARNING_ALERT;
			}
			पक्ष SDL_MESSAGEBOX_ERROR:
			{
				प्रत्यागम B_STOP_ALERT;
			}
			पक्ष SDL_MESSAGEBOX_INFORMATION:
			{
				प्रत्यागम B_INFO_ALERT;
			}
		}
	}

	rgb_color
	ConvertColorType(ध्रुव SDL_सन्देशः_Box_Color *aColor) ध्रुव
	{
		rgb_color color = { aColor->r, aColor->g, aColor->b, color.alpha = 255 };
		प्रत्यागम color;
	}

	int32
	Get_वामः_Panel_विस्तारः(शून्य) ध्रुव
	{
		// See file "haiku/src/kits/interface/Alert.cpp" for this magic numbers.
		//    IconStripeWidth = 30 * Scale
		//    IconSize = 32 * Scale
		//    Scale = max_c(1, ((int32)be_plain_font->Size() + 15) / 16)
		//    RealWidth = (IconStripeWidth * Scale) + (IconSize * Scale)

		int32 scale = max_c(1, ((int32)be_plain_font->आकार_2() + 15) / 16);
		प्रत्यागम (30 * scale) + (32 * scale);
	}

	शून्य
	Update_Text_View_विस्तारः(शून्य)
	{
		f_Computed_सन्देशः_Box_विस्तारः = f_सन्देशः_Box_Text_View->Preferred_आकार().विस्तारः_2() + Get_वामः_Panel_विस्तारः();
	}

	शून्य
	Parse_Sdl_सन्देशः_Box_दत्त(ध्रुव SDL_सन्देशः_Box_दत्त *a_सन्देशः_Box_दत्त)
	{
		यदि (a_सन्देशः_Box_दत्त == रिक्त) {
			समुच्चयः_Title_2(HAIKU_SDL_DefTitle);
			समुच्चयः_सन्देशः_Text(HAIKU_SDL_Def_सन्देशः);
			सङ्कलय_Button(HAIKU_SDL_DefButton);
			प्रत्यागम;
		}

		यदि (a_सन्देशः_Box_दत्त->numbuttons <= 0) {
			सङ्कलय_Button(HAIKU_SDL_DefButton);
		} अन्यथा {
			सङ्कलय_Sdl_Buttons(a_सन्देशः_Box_दत्त->buttons, a_सन्देशः_Box_दत्त->numbuttons);
		}

		यदि (a_सन्देशः_Box_दत्त->colorScheme != रिक्त) {
			fCustomColorScheme = सत्य;
			ApplyAndParseColorScheme(a_सन्देशः_Box_दत्त->colorScheme);
		}

		(a_सन्देशः_Box_दत्त->title[0]) ?
			समुच्चयः_Title_2(a_सन्देशः_Box_दत्त->title) : समुच्चयः_Title_2(HAIKU_SDL_DefTitle);
		(a_सन्देशः_Box_दत्त->सन्देशः[0]) ?
			समुच्चयः_सन्देशः_Text(a_सन्देशः_Box_दत्त->सन्देशः) : समुच्चयः_सन्देशः_Text(HAIKU_SDL_Def_सन्देशः);

		समुच्चयः_Type(Convert_सन्देशः_Box_Type(a_सन्देशः_Box_दत्त->flags));
	}

	शून्य
	ApplyAndParseColorScheme(ध्रुव SDL_सन्देशः_Box_Color_Scheme *aColorScheme)
	{
		समुच्चयः_Background_Color(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BACKGROUND]);
		fTextColor = ConvertColorType(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_TEXT]);
		समुच्चयः_Button_Colors(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_TEXT],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED]);
	}

	शून्य
	समुच्चयः_Button_Colors(ध्रुव SDL_सन्देशः_Box_Color *aBorderColor,
	                ध्रुव SDL_सन्देशः_Box_Color *aBackgroundColor,
	                ध्रुव SDL_सन्देशः_Box_Color *aTextColor,
	                ध्रुव SDL_सन्देशः_Box_Color *aSelectedColor)
	{
		यदि (fCustomColorScheme) {
			int32 गणनम्_Buttons = गणनम्_Buttons_2();
			प्रति (पूर्णाङ्क i = 0; i < गणनम्_Buttons; ++i) {
				ButtonAt(i)->समुच्चयः_View_Color(ConvertColorType(aBorderColor));
				ButtonAt(i)->समुच्चयः_नीचः_Color(ConvertColorType(aBackgroundColor));

				// This doesn't work. See this why:
				// https://github.com/haiku/haiku/commit/de9c53f8f5008c7b3b0af75d944a628e17f6dffe
				// Let it remain.
				ButtonAt(i)->समुच्चयः_उच्चः_Color(ConvertColorType(aTextColor));
			}
		}
		// TODO: Not Implemented.
		// Is it even necessary?!
		(शून्य)aSelectedColor;
	}

	शून्य
	समुच्चयः_Background_Color(ध्रुव SDL_सन्देशः_Box_Color *aColor)
	{
		rgb_color background = ConvertColorType(aColor);

		GetLayout()->View()->समुच्चयः_View_Color(background);
		// See file "haiku/src/kits/interface/Alert.cpp", the "TAlertView" is the internal name of the left panel.
		FindView("TAlertView")->समुच्चयः_View_Color(background);
		f_सन्देशः_Box_Text_View->समुच्चयः_View_Color(background);
	}

	तार्किक
	Check_Long_पङ्क्तयः(ध्रुव वर्ण *a_सन्देशः)
	{
		पूर्णाङ्क final = 0;

		// This UTF-8 friendly.
		BString सन्देशः = a_सन्देशः;
		int32 दीर्घता = सन्देशः.गणनम्_Chars();

		प्रति (पूर्णाङ्क i = 0, c = 0; i < दीर्घता; ++i) {
			c++;
			यदि (*(सन्देशः.CharAt(i)) == '\n') {
				c = 0;
			}
			यदि (c > final) {
				final = c;
			}
		}

		प्रत्यागम (final > G_MAX_STRING_दीर्घता_अष्टकानि);
	}

	शून्य
	समुच्चयः_सन्देशः_Text(ध्रुव वर्ण *a_सन्देशः)
	{
		f_There_Is_Long_पङ्क्तिः = Check_Long_पङ्क्तयः(a_सन्देशः);
		यदि (f_There_Is_Long_पङ्क्तिः) {
			f_सन्देशः_Box_Text_View->समुच्चयः_Word_Wrap(सत्य);
		}

		rgb_color textColor = ui_color(B_PANEL_TEXT_COLOR);
		यदि (fCustomColorScheme) {
			textColor = fTextColor;
		}

		/*
		if (fNoTitledWindow) {
			fMessageBoxTextView->SetFontAndColor(be_bold_font);
			fMessageBoxTextView->Insert(fTitle);
			fMessageBoxTextView->Insert("\n\n");
			fMessageBoxTextView->SetFontAndColor(be_plain_font);
		}
		*/

		f_सन्देशः_Box_Text_View->समुच्चयः_Font_And_Color(be_plain_font, B_FONT_ALL, &textColor);
		f_सन्देशः_Box_Text_View->निवेशय(a_सन्देशः);

		// Be sure to call update width method.
		Update_Text_View_विस्तारः();
	}

	शून्य
	सङ्कलय_Sdl_Buttons(ध्रुव SDL_सन्देशः_Box_Button_दत्त *aButtons, पूर्णाङ्क a_अङ्कः_Buttons)
	{
		प्रति (पूर्णाङ्क i = 0; i < a_अङ्कः_Buttons; ++i) {
			fButtons.प्रक्षिप_पृष्ठभागः(&aButtons[i]);
		}

		std::क्रमय(fButtons.begin(), fButtons.अन्तः(), &HAIKU_SDL_सन्देशः_Box::क्रमय_Buttons_Predicate);

		size_t गणनम्_Buttons = fButtons.आकार();
		प्रति (size_t i = 0; i < गणनम्_Buttons; ++i) {
			यदि (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
                fCloseButton = static_cast<पूर्णाङ्क>(i);
            }
			यदि (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
                fDefaultButton = static_cast<पूर्णाङ्क>(i);
            }
			सङ्कलय_Button(fButtons[i]->text);
		}

		समुच्चयः_Default_Button(ButtonAt(fDefaultButton));
	}

सार्वजनिक:
	स्पष्ट
	HAIKU_SDL_सन्देशः_Box(ध्रुव SDL_सन्देशः_Box_दत्त *a_सन्देशः_Box_दत्त)
		: BAlert(रिक्त, रिक्त, रिक्त, रिक्त, रिक्त, B_विस्तारः_FROM_LABEL, B_WARNING_ALERT),
		  f_Computed_सन्देशः_Box_विस्तारः(0.0f),
		  fCloseButton(G_CLOSE_BUTTON_ID), fDefaultButton(G_DEFAULT_BUTTON_ID),
		  fCustomColorScheme(असत्य), f_There_Is_Long_पङ्क्तिः(असत्य),
		  HAIKU_SDL_DefTitle("SDL MessageBox"),
		  HAIKU_SDL_Def_सन्देशः("Some information has been lost."),
		  HAIKU_SDL_DefButton("OK")
	{
		// MessageBox settings.
		// We need a title to display it.
		समुच्चयः_Look(B_TITLED_गवाक्षः_LOOK);
		समुच्चयः_Flags(Flags() | B_CLOSE_ON_ESCAPE);

		// MessageBox TextView settings.
		f_सन्देशः_Box_Text_View = TextView();
		f_सन्देशः_Box_Text_View->समुच्चयः_Word_Wrap(असत्य);
		f_सन्देशः_Box_Text_View->समुच्चयः_Stylable(सत्य);

		Parse_Sdl_सन्देशः_Box_दत्त(a_सन्देशः_Box_दत्त);
	}

	पूर्णाङ्क
	GetCloseButtonId(शून्य) ध्रुव
	{
		प्रत्यागम fCloseButton;
	}

	आभास
	~HAIKU_SDL_सन्देशः_Box(शून्य)
	{
		fButtons.clear();
	}

रक्षित:
	आभास शून्य
	FrameResized(भिन्न a_New_विस्तारः, भिन्न aNewHeight)
	{
		यदि (f_Computed_सन्देशः_Box_विस्तारः > a_New_विस्तारः) {
			Resize_गन्तव्यम्(f_Computed_सन्देशः_Box_विस्तारः, aNewHeight);
		} अन्यथा {
			BAlert::FrameResized(a_New_विस्तारः, aNewHeight);
		}
	}

	आभास शून्य
	समुच्चयः_Title_2(ध्रुव वर्ण *aTitle)
	{
		fTitle = aTitle;
		BAlert::समुच्चयः_Title_2(aTitle);
	}
};

#यदि_परिभाषितम् __cplusplus
बाह्य "C" {
#यदि_अन्तः

तार्किक HAIKU_Show_सन्देशः_Box(ध्रुव SDL_सन्देशः_Box_दत्त *messageboxdata, पूर्णाङ्क *buttonID)
{
	// Initialize button by closed or error value first.
	*buttonID = G_CLOSE_BUTTON_ID;

	// We need to check "be_app" pointer to "NULL". The "messageboxdata->window" pointer isn't appropriate here
	// because it is possible to create a MessageBox from another thread. This fixes the following errors:
	// "You need a valid BApplication object before interacting with the app_server."
	// "2 BApplication objects were created. Only one is allowed."
	std::unique_ptr<BApplication> application;
	यदि (!be_app) {
		application = std::unique_ptr<BApplication>(नूतन(std::nothrow) BApplication(SDL_signature));
		यदि (!application) {
			प्रत्यागम SDL_समुच्चयः_Error("Cannot create the BApplication object. Lack of memory?");
		}
	}

	HAIKU_SDL_सन्देशः_Box *SDL_सन्देशः_Box = नूतन(std::nothrow) HAIKU_SDL_सन्देशः_Box(messageboxdata);
	यदि (!SDL_सन्देशः_Box) {
		प्रत्यागम SDL_समुच्चयः_Error("Cannot create the HAIKU_SDL_MessageBox (BAlert inheritor) object. Lack of memory?");
	}
	ध्रुव पूर्णाङ्क closeButton = SDL_सन्देशः_Box->GetCloseButtonId();
	पूर्णाङ्क pushedButton = SDL_सन्देशः_Box->Go();

	// The close button is equivalent to pressing Escape.
	यदि (closeButton != G_CLOSE_BUTTON_ID && pushedButton == G_CLOSE_BUTTON_ID) {
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

	प्रत्यागम सत्य;
}

#यदि_परिभाषितम् __cplusplus
}
#यदि_अन्तः

#यदि_अन्तः // SDL_VIDEO_DRIVER_HAIKU

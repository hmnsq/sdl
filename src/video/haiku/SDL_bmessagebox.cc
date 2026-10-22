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

#ifdef SDL_VIDEO_DRIVER_HAIKU


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
	G_MAX_STRING_LENGTH_BYTES = 120
};

वर्ग HAIKU_SDL_MessageBox : सार्वजनिक BAlert
{
	भिन्न fComputedMessageBoxWidth;

	BTextView *fMessageBoxTextView;

	पूर्णाङ्क fCloseButton;
	पूर्णाङ्क fDefaultButton;

	तार्किक fCustomColorScheme;
	तार्किक f_There_Is_Long_पङ्क्तिः;
	rgb_color fTextColor;

	ध्रुव वर्ण *fTitle;
	ध्रुव वर्ण *HAIKU_SDL_DefTitle;
	ध्रुव वर्ण *HAIKU_SDL_DefMessage;
	ध्रुव वर्ण *HAIKU_SDL_DefButton;

	std::vector<ध्रुव SDL_MessageBoxButtonData *> fButtons;

	स्थिर तार्किक
	SortButtonsPredicate(ध्रुव SDL_MessageBoxButtonData *a_Button_वामः,
	                                 ध्रुव SDL_MessageBoxButtonData *a_Button_दक्षिणः)
	{
		प्रत्यागम a_Button_वामः->buttonID < a_Button_दक्षिणः->buttonID;
	}

	alert_type
	ConvertMessageBoxType(ध्रुव SDL_MessageBoxFlags aWindowType) ध्रुव
	{
		विकल्प (aWindowType)
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
	ConvertColorType(ध्रुव SDL_MessageBoxColor *aColor) ध्रुव
	{
		rgb_color color = { aColor->r, aColor->g, aColor->b, color.alpha = 255 };
		प्रत्यागम color;
	}

	int32
	Get_वामः_Panel_Width(शून्य) ध्रुव
	{
		// See file "haiku/src/kits/interface/Alert.cpp" for this magic numbers.
		//    IconStripeWidth = 30 * Scale
		//    IconSize = 32 * Scale
		//    Scale = max_c(1, ((int32)be_plain_font->Size() + 15) / 16)
		//    RealWidth = (IconStripeWidth * Scale) + (IconSize * Scale)

		int32 scale = max_c(1, ((int32)be_plain_font->Size() + 15) / 16);
		प्रत्यागम (30 * scale) + (32 * scale);
	}

	शून्य
	UpdateTextViewWidth(शून्य)
	{
		fComputedMessageBoxWidth = fMessageBoxTextView->PreferredSize().Width() + Get_वामः_Panel_Width();
	}

	शून्य
	ParseSdlMessageBoxData(ध्रुव SDL_MessageBoxData *aMessageBoxData)
	{
		जइ (aMessageBoxData == रिक्त) {
			SetTitle(HAIKU_SDL_DefTitle);
			SetMessageText(HAIKU_SDL_DefMessage);
			AddButton(HAIKU_SDL_DefButton);
			प्रत्यागम;
		}

		जइ (aMessageBoxData->numbuttons <= 0) {
			AddButton(HAIKU_SDL_DefButton);
		} अण्णहा {
			AddSdlButtons(aMessageBoxData->buttons, aMessageBoxData->numbuttons);
		}

		जइ (aMessageBoxData->colorScheme != रिक्त) {
			fCustomColorScheme = सच्च;
			ApplyAndParseColorScheme(aMessageBoxData->colorScheme);
		}

		(aMessageBoxData->title[0]) ?
			SetTitle(aMessageBoxData->title) : SetTitle(HAIKU_SDL_DefTitle);
		(aMessageBoxData->message[0]) ?
			SetMessageText(aMessageBoxData->message) : SetMessageText(HAIKU_SDL_DefMessage);

		SetType(ConvertMessageBoxType(aMessageBoxData->flags));
	}

	शून्य
	ApplyAndParseColorScheme(ध्रुव SDL_MessageBoxColorScheme *aColorScheme)
	{
		SetBackgroundColor(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BACKGROUND]);
		fTextColor = ConvertColorType(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_TEXT]);
		SetButtonColors(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_TEXT],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED]);
	}

	शून्य
	SetButtonColors(ध्रुव SDL_MessageBoxColor *aBorderColor,
	                ध्रुव SDL_MessageBoxColor *aBackgroundColor,
	                ध्रुव SDL_MessageBoxColor *aTextColor,
	                ध्रुव SDL_MessageBoxColor *aSelectedColor)
	{
		जइ (fCustomColorScheme) {
			int32 गणनम्_Buttons = गणनम्_Buttons_2();
			प्रति (पूर्णाङ्क i = 0; i < गणनम्_Buttons; ++i) {
				ButtonAt(i)->SetViewColor(ConvertColorType(aBorderColor));
				ButtonAt(i)->Set_नीचः_Color(ConvertColorType(aBackgroundColor));

				// This doesn't work. See this why:
				// https://github.com/haiku/haiku/commit/de9c53f8f5008c7b3b0af75d944a628e17f6dffe
				// Let it remain.
				ButtonAt(i)->Set_उच्चः_Color(ConvertColorType(aTextColor));
			}
		}
		// TODO: Not Implemented.
		// Is it even necessary?!
		(शून्य)aSelectedColor;
	}

	शून्य
	SetBackgroundColor(ध्रुव SDL_MessageBoxColor *aColor)
	{
		rgb_color background = ConvertColorType(aColor);

		GetLayout()->View()->SetViewColor(background);
		// See file "haiku/src/kits/interface/Alert.cpp", the "TAlertView" is the internal name of the left panel.
		FindView("TAlertView")->SetViewColor(background);
		fMessageBoxTextView->SetViewColor(background);
	}

	तार्किक
	Check_Long_पङ्क्तयः(ध्रुव वर्ण *aMessage)
	{
		पूर्णाङ्क final = 0;

		// This UTF-8 friendly.
		BString message = aMessage;
		int32 length = message.गणनम्_Chars();

		प्रति (पूर्णाङ्क i = 0, c = 0; i < length; ++i) {
			c++;
			जइ (*(message.CharAt(i)) == '\n') {
				c = 0;
			}
			जइ (c > final) {
				final = c;
			}
		}

		प्रत्यागम (final > G_MAX_STRING_LENGTH_BYTES);
	}

	शून्य
	SetMessageText(ध्रुव वर्ण *aMessage)
	{
		f_There_Is_Long_पङ्क्तिः = Check_Long_पङ्क्तयः(aMessage);
		जइ (f_There_Is_Long_पङ्क्तिः) {
			fMessageBoxTextView->SetWordWrap(सच्च);
		}

		rgb_color textColor = ui_color(B_PANEL_TEXT_COLOR);
		जइ (fCustomColorScheme) {
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

		fMessageBoxTextView->SetFontAndColor(be_plain_font, B_FONT_ALL, &textColor);
		fMessageBoxTextView->निवेशय(aMessage);

		// Be sure to call update width method.
		UpdateTextViewWidth();
	}

	शून्य
	AddSdlButtons(ध्रुव SDL_MessageBoxButtonData *aButtons, पूर्णाङ्क a_अङ्कः_Buttons)
	{
		प्रति (पूर्णाङ्क i = 0; i < a_अङ्कः_Buttons; ++i) {
			fButtons.प्रक्षिप_back(&aButtons[i]);
		}

		std::sort(fButtons.begin(), fButtons.end(), &HAIKU_SDL_MessageBox::SortButtonsPredicate);

		size_t गणनम्_Buttons = fButtons.size();
		प्रति (size_t i = 0; i < गणनम्_Buttons; ++i) {
			जइ (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
                fCloseButton = static_cast<पूर्णाङ्क>(i);
            }
			जइ (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
                fDefaultButton = static_cast<पूर्णाङ्क>(i);
            }
			AddButton(fButtons[i]->text);
		}

		SetDefaultButton(ButtonAt(fDefaultButton));
	}

सार्वजनिक:
	explicit
	HAIKU_SDL_MessageBox(ध्रुव SDL_MessageBoxData *aMessageBoxData)
		: BAlert(रिक्त, रिक्त, रिक्त, रिक्त, रिक्त, B_WIDTH_FROM_LABEL, B_WARNING_ALERT),
		  fComputedMessageBoxWidth(0.0f),
		  fCloseButton(G_CLOSE_BUTTON_ID), fDefaultButton(G_DEFAULT_BUTTON_ID),
		  fCustomColorScheme(मिच्छ), f_There_Is_Long_पङ्क्तिः(मिच्छ),
		  HAIKU_SDL_DefTitle("SDL MessageBox"),
		  HAIKU_SDL_DefMessage("Some information has been lost."),
		  HAIKU_SDL_DefButton("OK")
	{
		// MessageBox settings.
		// We need a title to display it.
		SetLook(B_TITLED_WINDOW_LOOK);
		SetFlags(Flags() | B_CLOSE_ON_ESCAPE);

		// MessageBox TextView settings.
		fMessageBoxTextView = TextView();
		fMessageBoxTextView->SetWordWrap(मिच्छ);
		fMessageBoxTextView->SetStylable(सच्च);

		ParseSdlMessageBoxData(aMessageBoxData);
	}

	पूर्णाङ्क
	GetCloseButtonId(शून्य) ध्रुव
	{
		प्रत्यागम fCloseButton;
	}

	आभास
	~HAIKU_SDL_MessageBox(शून्य)
	{
		fButtons.clear();
	}

रक्षित:
	आभास शून्य
	FrameResized(भिन्न aNewWidth, भिन्न aNewHeight)
	{
		जइ (fComputedMessageBoxWidth > aNewWidth) {
			ResizeTo(fComputedMessageBoxWidth, aNewHeight);
		} अण्णहा {
			BAlert::FrameResized(aNewWidth, aNewHeight);
		}
	}

	आभास शून्य
	SetTitle(ध्रुव वर्ण *aTitle)
	{
		fTitle = aTitle;
		BAlert::SetTitle(aTitle);
	}
};

#ifdef __cplusplus
बाह्य "C" {
#endif

तार्किक HAIKU_ShowMessageBox(ध्रुव SDL_MessageBoxData *messageboxdata, पूर्णाङ्क *buttonID)
{
	// Initialize button by closed or error value first.
	*buttonID = G_CLOSE_BUTTON_ID;

	// We need to check "be_app" pointer to "NULL". The "messageboxdata->window" pointer isn't appropriate here
	// because it is possible to create a MessageBox from another thread. This fixes the following errors:
	// "You need a valid BApplication object before interacting with the app_server."
	// "2 BApplication objects were created. Only one is allowed."
	std::unique_ptr<BApplication> application;
	जइ (!be_app) {
		application = std::unique_ptr<BApplication>(नूतन(std::nothrow) BApplication(SDL_signature));
		जइ (!application) {
			प्रत्यागम SDL_SetError("Cannot create the BApplication object. Lack of memory?");
		}
	}

	HAIKU_SDL_MessageBox *SDL_MessageBox = नूतन(std::nothrow) HAIKU_SDL_MessageBox(messageboxdata);
	जइ (!SDL_MessageBox) {
		प्रत्यागम SDL_SetError("Cannot create the HAIKU_SDL_MessageBox (BAlert inheritor) object. Lack of memory?");
	}
	ध्रुव पूर्णाङ्क closeButton = SDL_MessageBox->GetCloseButtonId();
	पूर्णाङ्क pushedButton = SDL_MessageBox->Go();

	// The close button is equivalent to pressing Escape.
	जइ (closeButton != G_CLOSE_BUTTON_ID && pushedButton == G_CLOSE_BUTTON_ID) {
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

	प्रत्यागम सच्च;
}

#ifdef __cplusplus
}
#endif

#endif // SDL_VIDEO_DRIVER_HAIKU

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

#समावेश "SDL_internal.h"

#अगर_घोषित SDL_VIDEO_DRIVER_HAIKU


// For application signature.
#समावेश "../../core/haiku/SDL_BeApp.h"

#समावेश <Alert.h>
#समावेश <Application.h>
#समावेश <Button.h>
#समावेश <Font.h>
#समावेश <Layout.h>
#समावेश <String.h>
#समावेश <TextView.h>
#समावेश <View.h>
#समावेश <Window.h>

#समावेश <InterfaceDefs.h>
#समावेश <SupportDefs.h>
#समावेश <GraphicsDefs.h>

#समावेश <new>
#समावेश <vector>
#समावेश <algorithm>
#समावेश <memory>

क्रमागत
{
	G_CLOSE_BUTTON_ID   = -1,
	G_DEFAULT_BUTTON_ID = 0,
	G_MAX_STRING_लंबाई_BYTES = 120
};

श्रेणी HAIKU_SDL_MessageBox : खुला BAlert
{
	भग्न fComputedMessageBoxWidth;

	BTextView *fMessageBoxTextView;

	पूर्णांक fCloseButton;
	पूर्णांक fDefaultButton;

	bool fCustomColorScheme;
	bool f_There_Is_Long_पंक्ति;
	rgb_color fTextColor;

	स्थिर अक्षर *fTitle;
	स्थिर अक्षर *HAIKU_SDL_DefTitle;
	स्थिर अक्षर *HAIKU_SDL_DefMessage;
	स्थिर अक्षर *HAIKU_SDL_DefButton;

	std::vector<स्थिर SDL_Message_Box_Button_तथ्य *> fButtons;

	अटल bool
	SortButtonsPredicate(स्थिर SDL_Message_Box_Button_तथ्य *a_Button_बायाँ,
	                                 स्थिर SDL_Message_Box_Button_तथ्य *a_Button_दायाँ)
	{
		वापस a_Button_बायाँ->buttonID < a_Button_दायाँ->buttonID;
	}

	alert_type
	ConvertMessageBoxType(स्थिर SDL_MessageBoxFlags aWindowType) स्थिर
	{
		चयन (aWindowType)
		{
			शेष:
			हाल SDL_MESSAGEBOX_WARNING:
			{
				वापस B_WARNING_ALERT;
			}
			हाल SDL_MESSAGEBOX_ERROR:
			{
				वापस B_STOP_ALERT;
			}
			हाल SDL_MESSAGEBOX_INFORMATION:
			{
				वापस B_INFO_ALERT;
			}
		}
	}

	rgb_color
	ConvertColorType(स्थिर SDL_MessageBoxColor *aColor) स्थिर
	{
		rgb_color color = { aColor->r, aColor->g, aColor->b, color.alpha = 255 };
		वापस color;
	}

	int32
	Get_बायाँ_Panel_Width(व्योम) स्थिर
	{
		// See file "haiku/src/kits/interface/Alert.cpp" for this magic numbers.
		//    IconStripeWidth = 30 * Scale
		//    IconSize = 32 * Scale
		//    Scale = max_c(1, ((int32)be_plain_font->Size() + 15) / 16)
		//    RealWidth = (IconStripeWidth * Scale) + (IconSize * Scale)

		int32 scale = max_c(1, ((int32)be_plain_font->आकार_2() + 15) / 16);
		वापस (30 * scale) + (32 * scale);
	}

	व्योम
	UpdateTextViewWidth(व्योम)
	{
		fComputedMessageBoxWidth = fMessageBoxTextView->Preferred_आकार().Width() + Get_बायाँ_Panel_Width();
	}

	व्योम
	Parse_Sdl_Message_Box_तथ्य(स्थिर SDL_Message_Box_तथ्य *a_Message_Box_तथ्य)
	{
		अगर (a_Message_Box_तथ्य == शून्य) {
			SetTitle(HAIKU_SDL_DefTitle);
			SetMessageText(HAIKU_SDL_DefMessage);
			AddButton(HAIKU_SDL_DefButton);
			वापस;
		}

		अगर (a_Message_Box_तथ्य->numbuttons <= 0) {
			AddButton(HAIKU_SDL_DefButton);
		} अन्यथा {
			AddSdlButtons(a_Message_Box_तथ्य->buttons, a_Message_Box_तथ्य->numbuttons);
		}

		अगर (a_Message_Box_तथ्य->colorScheme != शून्य) {
			fCustomColorScheme = true;
			ApplyAndParseColorScheme(a_Message_Box_तथ्य->colorScheme);
		}

		(a_Message_Box_तथ्य->title[0]) ?
			SetTitle(a_Message_Box_तथ्य->title) : SetTitle(HAIKU_SDL_DefTitle);
		(a_Message_Box_तथ्य->message[0]) ?
			SetMessageText(a_Message_Box_तथ्य->message) : SetMessageText(HAIKU_SDL_DefMessage);

		SetType(ConvertMessageBoxType(a_Message_Box_तथ्य->flags));
	}

	व्योम
	ApplyAndParseColorScheme(स्थिर SDL_MessageBoxColorScheme *aColorScheme)
	{
		SetBackgroundColor(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BACKGROUND]);
		fTextColor = ConvertColorType(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_TEXT]);
		SetButtonColors(&aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BORDER],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_TEXT],
		                &aColorScheme->colors[SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED]);
	}

	व्योम
	SetButtonColors(स्थिर SDL_MessageBoxColor *aBorderColor,
	                स्थिर SDL_MessageBoxColor *aBackgroundColor,
	                स्थिर SDL_MessageBoxColor *aTextColor,
	                स्थिर SDL_MessageBoxColor *aSelectedColor)
	{
		अगर (fCustomColorScheme) {
			int32 गिनती_Buttons = गिनती_Buttons_2();
			क्रम (पूर्णांक i = 0; i < गिनती_Buttons; ++i) {
				ButtonAt(i)->SetViewColor(ConvertColorType(aBorderColor));
				ButtonAt(i)->Set_निचला_Color(ConvertColorType(aBackgroundColor));

				// This doesn't work. See this why:
				// https://github.com/haiku/haiku/commit/de9c53f8f5008c7b3b0af75d944a628e17f6dffe
				// Let it remain.
				ButtonAt(i)->Set_ऊपरी_Color(ConvertColorType(aTextColor));
			}
		}
		// TODO: Not Implemented.
		// Is it even necessary?!
		(व्योम)aSelectedColor;
	}

	व्योम
	SetBackgroundColor(स्थिर SDL_MessageBoxColor *aColor)
	{
		rgb_color background = ConvertColorType(aColor);

		GetLayout()->View()->SetViewColor(background);
		// See file "haiku/src/kits/interface/Alert.cpp", the "TAlertView" is the internal name of the left panel.
		FindView("TAlertView")->SetViewColor(background);
		fMessageBoxTextView->SetViewColor(background);
	}

	bool
	Check_Long_पंक्तियाँ(स्थिर अक्षर *aMessage)
	{
		पूर्णांक final = 0;

		// This UTF-8 friendly.
		BString message = aMessage;
		int32 लंबाई = message.गिनती_Chars();

		क्रम (पूर्णांक i = 0, c = 0; i < लंबाई; ++i) {
			c++;
			अगर (*(message.CharAt(i)) == '\n') {
				c = 0;
			}
			अगर (c > final) {
				final = c;
			}
		}

		वापस (final > G_MAX_STRING_लंबाई_BYTES);
	}

	व्योम
	SetMessageText(स्थिर अक्षर *aMessage)
	{
		f_There_Is_Long_पंक्ति = Check_Long_पंक्तियाँ(aMessage);
		अगर (f_There_Is_Long_पंक्ति) {
			fMessageBoxTextView->SetWordWrap(true);
		}

		rgb_color textColor = ui_color(B_PANEL_TEXT_COLOR);
		अगर (fCustomColorScheme) {
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
		fMessageBoxTextView->जोड़ो(aMessage);

		// Be sure to call update width method.
		UpdateTextViewWidth();
	}

	व्योम
	AddSdlButtons(स्थिर SDL_Message_Box_Button_तथ्य *aButtons, पूर्णांक a_अंक_Buttons)
	{
		क्रम (पूर्णांक i = 0; i < a_अंक_Buttons; ++i) {
			fButtons.धकेलो_back(&aButtons[i]);
		}

		std::sort(fButtons.begin(), fButtons.end(), &HAIKU_SDL_MessageBox::SortButtonsPredicate);

		माप_प्रकार गिनती_Buttons = fButtons.आकार();
		क्रम (माप_प्रकार i = 0; i < गिनती_Buttons; ++i) {
			अगर (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT) {
                fCloseButton = static_cast<पूर्णांक>(i);
            }
			अगर (fButtons[i]->flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT) {
                fDefaultButton = static_cast<पूर्णांक>(i);
            }
			AddButton(fButtons[i]->text);
		}

		SetDefaultButton(ButtonAt(fDefaultButton));
	}

खुला:
	explicit
	HAIKU_SDL_MessageBox(स्थिर SDL_Message_Box_तथ्य *a_Message_Box_तथ्य)
		: BAlert(शून्य, शून्य, शून्य, शून्य, शून्य, B_WIDTH_FROM_LABEL, B_WARNING_ALERT),
		  fComputedMessageBoxWidth(0.0f),
		  fCloseButton(G_CLOSE_BUTTON_ID), fDefaultButton(G_DEFAULT_BUTTON_ID),
		  fCustomColorScheme(false), f_There_Is_Long_पंक्ति(false),
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
		fMessageBoxTextView->SetWordWrap(false);
		fMessageBoxTextView->SetStylable(true);

		Parse_Sdl_Message_Box_तथ्य(a_Message_Box_तथ्य);
	}

	पूर्णांक
	GetCloseButtonId(व्योम) स्थिर
	{
		वापस fCloseButton;
	}

	भव
	~HAIKU_SDL_MessageBox(व्योम)
	{
		fButtons.सफा();
	}

रक्षित:
	भव व्योम
	FrameResized(भग्न aNewWidth, भग्न aNewHeight)
	{
		अगर (fComputedMessageBoxWidth > aNewWidth) {
			ResizeTo(fComputedMessageBoxWidth, aNewHeight);
		} अन्यथा {
			BAlert::FrameResized(aNewWidth, aNewHeight);
		}
	}

	भव व्योम
	SetTitle(स्थिर अक्षर *aTitle)
	{
		fTitle = aTitle;
		BAlert::SetTitle(aTitle);
	}
};

#अगर_घोषित __cplusplus
बाह्य "C" {
#पूर्ण_अगर

bool HAIKU_ShowMessageBox(स्थिर SDL_Message_Box_तथ्य *messageboxdata, पूर्णांक *buttonID)
{
	// Initialize button by closed or error value first.
	*buttonID = G_CLOSE_BUTTON_ID;

	// We need to check "be_app" pointer to "NULL". The "messageboxdata->window" pointer isn't appropriate here
	// because it is possible to create a MessageBox from another thread. This fixes the following errors:
	// "You need a valid BApplication object before interacting with the app_server."
	// "2 BApplication objects were created. Only one is allowed."
	std::unique_ptr<BApplication> application;
	अगर (!be_app) {
		application = std::unique_ptr<BApplication>(नया(std::nothrow) BApplication(SDL_signature));
		अगर (!application) {
			वापस SDL_SetError("Cannot create the BApplication object. Lack of memory?");
		}
	}

	HAIKU_SDL_MessageBox *SDL_MessageBox = नया(std::nothrow) HAIKU_SDL_MessageBox(messageboxdata);
	अगर (!SDL_MessageBox) {
		वापस SDL_SetError("Cannot create the HAIKU_SDL_MessageBox (BAlert inheritor) object. Lack of memory?");
	}
	स्थिर पूर्णांक closeButton = SDL_MessageBox->GetCloseButtonId();
	पूर्णांक pushedButton = SDL_MessageBox->Go();

	// The close button is equivalent to pressing Escape.
	अगर (closeButton != G_CLOSE_BUTTON_ID && pushedButton == G_CLOSE_BUTTON_ID) {
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

	वापस true;
}

#अगर_घोषित __cplusplus
}
#पूर्ण_अगर

#पूर्ण_अगर // SDL_VIDEO_DRIVER_HAIKU

#include "text.h"

text::text()
{
    verified = false;
    inputText.str( "" );
    noRobo.str("");
}

text::~text()
{

}

bool text::verifyNoRobo()
{

    if (inputText.str() != noRobo.str())
    {
        std::cout << "\n verified: " << std::to_string( verified );
    }
    else{
        verified = true;
        std::cout << "\n verified: " << std::to_string( verified );
    }

    return verified;
}

void text::loadText(TTF_Font* font,SDL_Renderer* renderer)
{
    //Set text color as black
			SDL_Color textColor = { 255, 255, 255, 0xFF };

			//The current input text.
			inputText.str("");
			inputTextTexture.loadFromRenderedText( inputText.str().c_str(),textColor,font,renderer );
            //the text to be verified
            noRobo.str("fuck capitalism");
			noRoboTextTexture.loadFromRenderedText( noRobo.str().c_str(),textColor,font,renderer );
			//Enable text input
            SDL_StartTextInput();
}

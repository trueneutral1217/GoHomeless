#include "text.h"

text::text()
{
    verified = false;
    inputText.str( "" );
    noRobo.str("fuck capitalism");
}

text::~text()
{

}

bool text::verifyNoRobo()
{
    //Enable text input
    //SDL_StartTextInput();



    //Set text color as black
    //SDL_Color textColor = { 0, 0, 0, 0xFF };

    //noRoboTextTexture.loadFromRenderedText( noRobo, textColor )


    if (inputText.str() != noRobo.str())
    {
        std::cout << "\n verified: " << std::to_string( verified );
    }
    else{
        verified = true;
        std::cout << "\n verified: " << std::to_string( verified );
    }
    /*
    if (inputText.compare(noRobo) == 0)
    {
        verified = true;
    }*/
    /*
    if (0 == stricmp(inputText,noRobo))
    {
        verified = true;
    }*/

    return verified;
}

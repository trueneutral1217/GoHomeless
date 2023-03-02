#ifndef TEXT_H
#define TEXT_H

#include "texture.h"

class text
{
    public:
        //constructor
        text();
        //destructor
        ~text();

        bool verified;

        Texture noRoboTextTexture;
        Texture inputTextTexture;

        std::string foo;

        std::stringstream inputText;

        std::stringstream noRobo;

        void loadText(TTF_Font* font,SDL_Renderer* renderer);

        bool verifyNoRobo();


    private:

};

#endif // TEXT_H

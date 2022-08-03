#ifndef PREGAMEUI_H
#define PREGAMEUI_H

#include "texture.h"

class pregameui
{
public:
    //constructor
    pregameui();
    //destructor
    ~pregameui();

    //declaring textures (title, backgrounds, etc
    Texture title;
    Texture titleTexture;
    Texture creditsTexture;
    Texture optionsTexture;
    Texture loadGameTexture;
    Texture chapterSelectTexture;
    Texture thanksTexture;

    bool setPGUITextures(SDL_Renderer* renderer);
    void freePGUITextures();

private:

};

#endif // PREGAMEUI_H

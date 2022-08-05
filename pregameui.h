#ifndef PREGAMEUI_H
#define PREGAMEUI_H

#include "texture.h"
#include "button.h"



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

    button buttons[TOTAL_PREGAME_BUTTONS];

    bool setPGUITextures(SDL_Renderer* renderer);
    void freePGUITextures();

    //sets up the textures by button name and sets positions of the pregame buttons.
    bool setPreGameButtonTextures(SDL_Renderer* renderer, bool success);

private:

};

#endif // PREGAMEUI_H

#include "pregameui.h"

pregameui::pregameui()
{

}

pregameui::~pregameui()
{

}

bool pregameui::setPGUITextures(SDL_Renderer* renderer)
{
    bool success = true;
    //game title image
	success = title.loadFromFile( "images/title.png",renderer );
	//load background image files for non-chapter1 backgrounds
	success = titleTexture.loadFromFile( "images/skidrow.png",renderer );
	success = loadGameTexture.loadFromFile( "images/loadgamescreen.png",renderer );
	success = chapterSelectTexture.loadFromFile( "images/busstop.png",renderer );
	success = creditsTexture.loadFromFile( "images/brickwall.png",renderer );
	success = optionsTexture.loadFromFile("images/maritime.png",renderer );
	success = thanksTexture.loadFromFile("images/thanks.png",renderer);

	if(!success)
    {
        printf("\n \n there was a problem loading pregame UI textures. \n \n");
    }

	return success;
}

void pregameui::freePGUITextures()
{
     //free the title image
    title.free();
    //free the background textures
	titleTexture.free();
	chapterSelectTexture.free();
	loadGameTexture.free();
	optionsTexture.free();
	creditsTexture.free();
    thanksTexture.free();
}

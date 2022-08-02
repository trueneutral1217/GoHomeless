#ifndef BUTTON_H
#define BUTTON_H

#include "Texture.h"

//buttons on the title screen + back button for screens like options
const int TOTAL_BUTTONS = 10;

const int BUTTON_WIDTH = 160;
const int BUTTON_HEIGHT = 120;

class button
{
    public:
		//Initializes internal variables
		button();
        ~button();
		//Sets top left position
		void setPosition( int x, int y );

		int getPositionX();
		int getPositionY();
		bool fullScreen;

		//Handles mouse event
		int handleEvent( int gameState, std::string buttonName, SDL_Event* e, SDL_Window* window,SDL_Renderer* renderer );

        Texture buttonTexture;

        bool setFullScreenOn(SDL_Window* window,SDL_Renderer* renderer);
        bool setFullScreenOff(SDL_Window* window,SDL_Renderer* renderer);


		std::string buttonName;

	private:
		//Top left point of button image location
		SDL_Point position;

};

#endif // BUTTON_H

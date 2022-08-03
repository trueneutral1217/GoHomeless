#include "button.h"

button::button()
{
	position.x = 0;
	position.y = 0;
    buttonName = "";
    fullScreen=false;

}

button::~button()
{
    buttonTexture.free();
}

void button::setPosition( int x, int y )
{
	position.x = x;
	position.y = y;
}

int button::getPositionX()
{
    return position.x;
}
int button::getPositionY()
{
    return position.y;
}

bool button::setFullScreenOn(SDL_Window* window,SDL_Renderer* renderer)
{
    fullScreen = true;
    SDL_SetWindowFullscreen( window, SDL_TRUE );
    return fullScreen;
}

bool button::setFullScreenOff(SDL_Window* window,SDL_Renderer* renderer)
{
    fullScreen = false;
    SDL_SetWindowFullscreen( window, SDL_FALSE );
    return fullScreen;
}

int button::handleEvent(int gameState, std::string buttonName, SDL_Event* e, SDL_Window* window, SDL_Renderer* renderer )
{
	//If mouse event happened
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if( x < position.x )
		{
			inside = false;
		}
		//Mouse is right of the button
		else if( x > position.x + buttonTexture.getWidth() )
		{
			inside = false;
		}
		//Mouse above the button
		else if( y < position.y )
		{
			inside = false;
		}
		//Mouse below the button
		else if( y > position.y + buttonTexture.getHeight() )
		{
			inside = false;
		}

		//Mouse is outside button
		if( !inside )
		{

		}
		//Mouse is inside button
		else
		{
                switch( e->type )
                {
                    case SDL_MOUSEBUTTONDOWN:

                        if(buttonName=="new" && gameState==0){
                            printf("\n \n new game button pressed \n \n");
                            gameState = 1;
                        }
                        else if(buttonName=="load" && gameState==0){
                            printf("\n \n load game button pressed \n \n");
                            gameState = 2;
                        }
                        else if(buttonName=="credits" && gameState==0){
                            printf("\n \n credits button pressed \n \n");
                            gameState = 4;
                        }
                        else if(buttonName=="options" && gameState==0){
                            printf("\n \n options button pressed \n \n");
                            gameState = 3;
                        }
                        else if(buttonName=="back" && gameState != 0){
                            printf("\n \n back button pressed \n \n");
                            gameState = 0;
                        }
                        else if(buttonName=="chapter1" && gameState==1){
                            printf("\n \n chapter 1 button pressed \n \n");
                            gameState = 5;
                        }
                        else if(buttonName=="chapter1" && gameState==2){
                            printf("\n \n chapter 1 button pressed \n \n");
                            gameState = 5;
                        }
                        else if(buttonName=="fullScreenOn" && gameState==3)
                        {
                            printf("\n \n fullScreenOn button pressed \n \n");
                            setFullScreenOff(window,renderer);
                            gameState = 3;
                        }
                        else if(buttonName=="stage1" && gameState==2)
                        {
                            printf("\n \n Stage 1 button pressed \n \n");
                            gameState = 6;
                        }
                        else if(buttonName=="backPage" && gameState==5)
                        {
                            printf("\n \n backPage button pressed \n \n");
                            gameState=-1;
                        }
                        else if(buttonName=="backLine" && gameState==5)
                        {
                            printf("\n \n backLine button pressed \n \n");
                            gameState=-1;
                        }
                        else if(buttonName=="autoOn" && gameState==5)
                        {
                            printf("\n \n autotexton button pressed \n \n");
                            gameState=-1;
                        }
                        else if(buttonName=="autoOff" && gameState==5)
                        {
                            printf("\n \n autotextoff button pressed \n \n");
                            gameState=-1;
                        }
                        else if(buttonName=="autoSpeed1" && gameState==5)
                        {
                            printf("\n \n autospeed1 button pressed \n \n");
                            gameState=-1;
                        }
                        else if(buttonName=="autoSpeed2" && gameState==5)
                        {
                            printf("\n \n autospeed2 button pressed \n \n");
                            gameState=-1;
                        }
                        else if(buttonName=="autoSpeed3" && gameState==5)
                        {
                            printf("\n \n autospeed3 button pressed \n \n");
                            gameState=-1;
                        }
                    break;
                }

		}
	}
	return gameState;
}

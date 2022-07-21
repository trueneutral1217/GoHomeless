#include "button.h"

button::button()
{
	position.x = 0;
	position.y = 0;
    buttonName = "";

    //buttonTexture = NULL;

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

int button::handleEvent(int gameState, std::string buttonName, SDL_Event* e )
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
		else if( x > position.x + BUTTON_WIDTH )
		{
			inside = false;
		}
		//Mouse above the button
		else if( y < position.y )
		{
			inside = false;
		}
		//Mouse below the button
		else if( y > position.y + BUTTON_HEIGHT )
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
            //std::cout << "button name: " << buttonName;

                switch( e->type )
                {
                    case SDL_MOUSEBUTTONDOWN:

                        if(buttonName=="new" && gameState==0){
                            printf("\n \n new game button pressed \n \n");
                            gameState = 1;
                        }
                        else if(buttonName=="load" && gameState==0){
                            printf("\n \n load game button pressed \n \n");
                            gameState = 2; //Note, this will need to be changed once saving game implemented
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
                    break;
                    //case SDL_MOUSEBUTTONUP:
                     //   clicked = false;
                     //   break;
                }

		}
	}
	return gameState;
}
/*
void button::render(texture gButtonTexture,SDL_Renderer* gRenderer)
{
	//Show current button sprite
	buttonTexture = gButtonTexture;
	buttonTexture.render( mPosition.x, mPosition.y,NULL,0.0,NULL,SDL_FLIP_NONE,gRenderer );
}
*/

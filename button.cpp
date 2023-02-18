#include "button.h"

button::button()
{
	position.x = 0;
	position.y = 0;
    buttonName = "";
    fullScreen=false;
    //move buttons 0-7 to pregameui
    pregameButtonNames[0]="back";
	pregameButtonNames[1]="new";
	pregameButtonNames[2]="load";
	pregameButtonNames[3]="options";
	pregameButtonNames[4]="credits";
	pregameButtonNames[5]="chapter1";
	pregameButtonNames[6]="fullScreenOff";
	pregameButtonNames[7]="stage1";
	pregameButtonNames[8]="chapter2";
	//move buttons 8-15 to chapter
	chapterButtonNames[0]="backPage";
	chapterButtonNames[1]="backLine";
	chapterButtonNames[2]="autoOn";
	chapterButtonNames[3]="autoOff";
	chapterButtonNames[4]="autoSpeed1";
	chapterButtonNames[5]="autoSpeed2";
	chapterButtonNames[6]="autoSpeed3";
    chapterButtonNames[7]="saveAndExit";

    stageButtonNames[0]="saveAndExit";

    //buttonTexture=NULL;
}

button::~button()
{
    buttonTexture.free();
}

void button::fullScreenButtonTextureToggle(SDL_Renderer* renderer)
{
    buttonTexture.free();
    if(fullScreen)
    {
        buttonTexture.loadFromFile("images/buttons/fullScreenOn.png", renderer);
    }
    else
    {
        buttonTexture.loadFromFile("images/buttons/fullScreenOff.png", renderer);
    }
    buttonTexture.render(getPositionX(),getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
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

void button::setChapterButtonName(int i)
{
    buttonName=chapterButtonNames[i];
}

void button::setPregameButtonName(int i)
{
    buttonName=pregameButtonNames[i];
}

void button::setStageButtonName(int i)
{
    buttonName=stageButtonNames[i];
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
                        //gamestate0 - 4 is pregameui area
                        else if(buttonName=="back" && (gameState < 5 || gameState==6) ){
                            printf("\n \n back button pressed \n \n");
                            gameState = 0;
                        }
                        else if(buttonName=="chapter1" && gameState==1){
                            printf("\n \n chapter 1 button pressed from new game screen \n \n");
                            gameState = 5;
                        }
                        else if(buttonName=="chapter1" && gameState==2){
                            printf("\n \n chapter 1 button pressed from load screen \n \n");
                            gameState = 5;
                        }
                        else if(buttonName=="chapter2")
                        {
                            printf("\n \n chapter 2 button pressed \n \n");
                            gameState = 7;
                        }
                        else if(buttonName=="fullScreenOff" && gameState==3)
                        {
                            printf("\n \n fullScreenOff button pressed \n \n");
                            if(!fullScreen)
                                setFullScreenOn(window,renderer);
                            else
                                setFullScreenOff(window,renderer);
                            gameState = 3;
                        }
                        else if(buttonName=="stage1" && gameState==2)
                        {
                            printf("\n \n Stage 1 button pressed \n \n");
                            gameState = 6;
                        }
                        else if(buttonName=="backPage" && (gameState==5 || gameState ==7))
                        {
                            printf("\n \n backPage button pressed \n \n");
                            gameState=-1;
                        }
                        else if(buttonName=="backLine" && (gameState==5 || gameState ==7))
                        {
                            printf("\n \n backLine button pressed \n \n");
                            gameState=-1;
                        }
                        else if(buttonName=="autoOn" && (gameState==5 || gameState ==7))
                        {
                            printf("\n \n autotexton button pressed \n \n");
                            gameState=1;
                        }
                        else if(buttonName=="autoOff" && (gameState==5 || gameState ==7))
                        {
                            printf("\n \n autotextoff button pressed \n \n");
                            gameState=0;
                        }
                        else if(buttonName=="autoSpeed1" && (gameState==5 || gameState ==7))
                        {
                            printf("\n \n autospeed1 button pressed \n \n");
                            gameState=0;
                        }
                        else if(buttonName=="autoSpeed2" && (gameState==5 || gameState ==7))
                        {
                            printf("\n \n autospeed2 button pressed \n \n");
                            gameState=1;
                        }
                        else if(buttonName=="autoSpeed3" && (gameState==5 || gameState ==7))
                        {
                            printf("\n \n autospeed3 button pressed \n \n");
                            gameState=2;
                        }
                        else if(buttonName=="saveAndExit" && (gameState==5 || gameState ==7))
                        {
                            printf("\n \n saveAndExit button pressed \n \n");
                            gameState=0;
                        }
                    break;
                }

		}
	}
	return gameState;
}

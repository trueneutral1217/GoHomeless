//SDL and system libraries
#include <iostream>
#include <assert.h>
#include <stddef.h>
#include <vector>
//local classes
#include "audio.h"
#include "button.h"
#include "Texture.h"
#include "timer.h"
#include "particle.h"
#include "chapter.h"
#include "saveGame.h"
#include "player.h"
const int TOTAL_STATES = 5;
//Starts up SDL and creates window
bool init();
//Loads media
bool loadMedia();
//Frees media and shuts down SDL
void close();
//The window renderer
SDL_Renderer* renderer = NULL;
//The window we'll be rendering to
SDL_Window* window = NULL;
//declaring textures (title, backgrounds, and dialog box
Texture title;
Texture titleTexture;
Texture creditsTexture;
Texture optionsTexture;
Texture loadGameTexture;
Texture chapterSelectTexture;
Texture thanksTexture;
//chapter1bg textures needs to be cleaned up, maybe made into an array.
Texture chapter1BG;
Texture chapter1BG2;
Texture chapter1BG3;
Texture chapter1BG4;
Texture chapter1BG5;
Texture chapter1BG6;
Texture dialogBox;
//user presses 'h' to hide the dialogbox, or dialog box & text, or neither.
bool hideDialogBox = false;
bool hideDialogAndBox = false;
bool fullScreen = false;
//Buttons object array
button buttons[ TOTAL_BUTTONS ];
//animation textures
Texture tao[TAO_ANIMATION_FRAMES];
//savegame handler
saveGame savegame;
audio music;
std::vector<audio> sounds;
audio sound;
//particle objects
Particle particles[ TOTAL_PARTICLES ];
//declare chapter1
chapter chapter;
//declare player
player player1;
//tests savegame variables, usually when altered, saved, or loaded.
void testSaveVariables();
//declare sound vector & load sounds into it.
void loadSounds();
//render particles to screen
void renderParticles();
//sets buttonTexture by buttonName
bool setButtonTextures(bool success);
//determines which texture to show in options screen, red or green.
void fullScreenButtonTextureToggle();
//tracks the state of the game for rendering etc.
int gameState;

void renderParticles(){
    //Go through particles
    for( int i = 0; i < TOTAL_PARTICLES; ++i )
    {
        //Delete and replace dead particles
        if( particles[i].isDead() )
        {
            particles[i].createParticle(renderer);
        }
    }
    //Show particles
    for( int i = 0; i < TOTAL_PARTICLES; ++i )
    {
        particles[i].render(renderer,particles[i].renderColor);
    }
}

bool setButtonTextures(bool success)
{
    for( int i = 0; i < TOTAL_BUTTONS; ++i )
    {
        std::stringstream ss;
        ss << "images/buttons/" << buttons[i].buttonName << ".png";
        std::string str = ss.str();
        success = buttons[i].buttonTexture.loadFromFile( str,renderer );
        buttons[ i ].setPosition( ((i*160)-80), SCREEN_HEIGHT - 140 );
    }
    buttons[0].setPosition(600,20);
    buttons[5].setPosition(20,20);
    buttons[6].setPosition(20,100);
    buttons[7].setPosition(20,150);
    return success;
}

void fullScreenButtonTextureToggle()
{
    buttons[6].buttonTexture.free();
    if(buttons[6].fullScreen)
    {

        buttons[6].buttonTexture.loadFromFile("images/buttons/fullScreenOn.png", renderer);
    }
    else
    {
        buttons[6].buttonTexture.loadFromFile("images/buttons/fullScreenOff.png", renderer);
    }
    buttons[6].buttonTexture.render(buttons[6].getPositionX(),buttons[6].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
}

//initializes audio,video, etc.
bool init()
{
	//Initialization flag
	bool success = true;
	gameState = 0;
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0  )
	{
		printf( "\n SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "\n Warning: Linear texture filtering not enabled!" );
		}
		window = SDL_CreateWindow( "Go Homeless!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN  | SDL_WINDOW_RESIZABLE  );
		if( window == NULL )
		{

		    //SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_RESIZABLE | SDL_FULLSCREEN )
			printf( "\n Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
            renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
			if( renderer == NULL )
			{
				printf( "\n Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
				//create particles
				for(int i=0;i<TOTAL_PARTICLES;i++){
                    particles[i].createParticle(renderer);
                }
				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "\n SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
            {
                printf( "\n SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                success = false;
            }
        if( TTF_Init() == -1 )
        {
            printf( "\n SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
            success = false;
        }
	}
	return success;
}

void testSaveVariables()
{
    std::cout << "\n currentChapter: " << std::to_string( chapter.currentChapter );
    std::cout << "\n currentPage: " << std::to_string( chapter.currentPage );
    std::cout << "\n currentScript: " << std::to_string( chapter.currentScript );
    std::cout << "\n chapter1Complete: " << std::to_string(chapter.chapter1Complete);
}

void loadSounds()
{
    //prep the vector
    for(int i = 0; i < TOTAL_SOUNDS; i++)
    {
        sounds.push_back(sound);
    }
    //load the sounds for each point in the vector
    for(int i = 0; i < TOTAL_SOUNDS; i++)
    {
        sounds[i].loadSound(i);
    }
}

bool loadMedia()
{
	bool success = true;
	//set button names
	buttons[0].buttonName="back";
	buttons[1].buttonName="new";
	buttons[2].buttonName="load";
	buttons[3].buttonName="options";
	buttons[4].buttonName="credits";
	buttons[5].buttonName="chapter1";
	buttons[6].buttonName="fullScreenOff";
	buttons[7].buttonName="stage1";
//load saved game
	savegame.readFile();
    chapter.currentChapter= savegame.data[0];
    chapter.currentPage= savegame.data[1];
    chapter.currentScript = savegame.data[2];
    chapter.chapter1Complete = savegame.data[3];
    if(chapter.currentChapter>0)
    {
        chapter.chapter1Complete = true;
    }
    testSaveVariables();
    //load tao animation images
    for(int i = 0; i<TAO_ANIMATION_FRAMES;i++)
    {
        int a = i+1;
        std::stringstream ss;
        ss << "images/animations/tao/tao" << a << ".png";
        std::string str = ss.str();
        success = tao[i].loadFromFile(str,renderer);
    }
    //set button positions & image textures
    success = setButtonTextures(success);
	//game title image
	success = title.loadFromFile( "images/title.png",renderer );
	//load background image files for non-chapter1 backgrounds
	success = titleTexture.loadFromFile( "images/skidrow.png",renderer );
	success = loadGameTexture.loadFromFile( "images/loadgamescreen.png",renderer );
	success = chapterSelectTexture.loadFromFile( "images/busstop.png",renderer );
	success = creditsTexture.loadFromFile( "images/brickwall.png",renderer );
	success = optionsTexture.loadFromFile("images/maritime.png",renderer );
	success = thanksTexture.loadFromFile("images/thanks.png",renderer);
    //load chapter 1 background textures
    success = chapter.setBGTextures(renderer);
   //load dialog box image
	success = dialogBox.loadFromFile( "images/dialogbox1.png",renderer );
    //set dialog box alpha (about 75% opaque @ 192)
    dialogBox.setAlpha(255);
    //load font
	chapter.loadFont();
	//load sound effects
	loadSounds();
    //load player texture
    player1.loadPlayer(renderer);
    //for debugging
    if(success == false)
    {
        printf("something didn't load right in loadmedia.");
    }
	return success;
}

void close()
{
    //save progress
    savegame.writeFile(chapter.currentChapter,chapter.currentPage,chapter.currentScript,chapter.chapter1Complete);
    testSaveVariables();
    //free the button textures
    for(int i = 0; i<TOTAL_BUTTONS;i++)
    {
        buttons[i].buttonTexture.free();
    }
    //free the script textures
    for(int j = 0; j < TOTAL_PAGES; j++)
    {
        for(int i=0;i<TOTAL_SCRIPTS;i++)
        {
            chapter.scriptTexture[j][i].free();
        }
    }
    //free the tao animation textures
    for(int i=0;i<TAO_ANIMATION_FRAMES;i++){
        tao[i].free();
    }
    //free the title image
    title.free();
    //free the background textures
	titleTexture.free();
	chapterSelectTexture.free();
	loadGameTexture.free();
	optionsTexture.free();
	creditsTexture.free();
    chapter.freeBGTextures();
    thanksTexture.free();
	//free the dialog box for chapters
	dialogBox.free();
	//audio destructor frees audio
	//free the font
	TTF_CloseFont( chapter.font );
    chapter.font = NULL;
	//Destroy window
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	window = NULL;
	renderer = NULL;
	//Quit SDL subsystems
	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;
            //set text color as white
			SDL_Color textColor = { 255, 255, 255, 255 };
            //Set text color as black
			textColor = { 0, 0, 0, 255 };
			//load the bg music file
			chapter.loadChapterStrings(renderer);
            music.loadMusic();
			//The frames per second cap timer
			timer capTimer;
			//timer for dialog for chapter1
			timer chapter1Timer;
            //timer for tao animation
            timer animationTimer;
            animationTimer.start();
			//Frame of animation
			int aniFrame = 0;
			//Start counting frames per second
			int countedFrames = 0;
			//Event handler
			SDL_Event e;
			//While application is running
			while( !quit )
			{
			    //Start cap timer
				capTimer.start();
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
                    if(e.type == SDL_MOUSEBUTTONDOWN){
                        if(gameState == 5) //Chapter 1
                        {
                            if(chapter.currentPage==TOTAL_PAGES-1 && chapter.currentScript==TOTAL_SCRIPTS-1){
                                chapter.completeChapter(renderer);
                                gameState=2;
                                chapter1Timer.stop();
                            }
                            else if (chapter.currentScript<TOTAL_SCRIPTS-1)
                            {
                                chapter.scriptIncrement();
                                chapter1Timer.restart();
                            }
                            else if(chapter.currentPage<TOTAL_PAGES-1){
                                chapter.pageIncrement();
                                chapter1Timer.restart();
                            }
                        }
                        if(gameState == 1)//new game chapter select
                        {
                            chapter.resetChapters(renderer);
                        }
                        if(gameState == 2){//load game chapter select
                            if(chapter.currentPage<TOTAL_PAGES-1)
                            {
                                if(chapter.currentPage!=0)
                                {
                                    if(chapter.currentScript ==0)
                                    {//compensate for clicking back button at end of page.
                                        chapter.backPage();
                                    }
                                }
                                if(chapter.currentScript != 0 && chapter.currentScript!=7)
                                {
                                    chapter.backScript();
                                }
                            }
                        }
                    }
					//Handle key press
					if( e.type == SDL_KEYDOWN )
					{
						switch( e.key.keysym.sym )
						{
                            case SDLK_SPACE:
                                if(gameState == 5)
                                {
                                    if(chapter.currentScript<TOTAL_SCRIPTS-1)
                                    {
                                        chapter.scriptIncrement();
                                        chapter1Timer.restart();
                                    }
                                    else
                                    {
                                        if(chapter.currentPage<TOTAL_PAGES-1)
                                        {
                                            chapter.pageIncrement();
                                            chapter1Timer.restart();
                                        }
                                        else
                                        {
                                            gameState = 2;
                                            chapter.completeChapter(renderer);
                                        }
                                    }
                                }
                                break;
                            case SDLK_ESCAPE:
                            if(gameState==0)
                            {
                                quit=true;
                            }
                            break;
							//sound tests
							case SDLK_1:
							    sounds[0].playSound();
							break;
							case SDLK_2:
                                sounds[1].playSound();
							break;
							case SDLK_3:
                                sounds[2].playSound();
							break;
							case SDLK_4:
                                sounds[3].playSound();
							break;
							case SDLK_h:
							if(hideDialogBox == false && hideDialogAndBox == false)
                            {
                                hideDialogBox = true;
                                hideDialogAndBox = false;
							}
							else if(hideDialogBox == true && hideDialogAndBox == false)
                            {
                                hideDialogAndBox = true;
                                hideDialogBox = true;
							}else if(hideDialogBox == true && hideDialogAndBox == true)
							{
							    hideDialogAndBox=false;
							    hideDialogBox=false;
							}
							printf("\n h pressed \n");
                            std::cout << "hideDialogBox: " << hideDialogBox;
							break;
							case SDLK_9:
							//press 9 to play / pause music
                            music.playMusic();
							break;
						}
					}
					//Handle button events
					for( int i = 0; i < TOTAL_BUTTONS; ++i )
					{
                        gameState = buttons[ i ].handleEvent(gameState,buttons[i].buttonName, &e, window,renderer );
					}
					player1.handleEvent(e);
				}
				player1.move();
				//Clear screen
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( renderer );
                //Title Screen rendering
                if(gameState == 0)
                {
                    chapter1Timer.stop();
                    titleTexture.render( 0, 0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer );
                    renderParticles();
                    title.render(200, 100,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                    //render title screen buttons
                    for(int i=1;i<TOTAL_BUTTONS;i++)
                    {
                        if(i<5)//5 is back button 6 is fullscreen button
                            buttons[i].buttonTexture.render(buttons[i].getPositionX(),buttons[i].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                    }
                }
                else if(gameState == 1)
                {//new game chapter select screen
                    chapter1Timer.stop();
                    chapterSelectTexture.render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer );
                    //chapter 1 button
                    buttons[5].buttonTexture.render(buttons[5].getPositionX(),buttons[5].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                    //back button
                    buttons[0].buttonTexture.render(buttons[0].getPositionX(),buttons[0].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                }
                else if(gameState == 2)
                {//load game chapter/stage select screen
                    chapter1Timer.stop();
                    //chapter select screen
                    chapterSelectTexture.render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                    //stage 1 button
                    if(chapter.chapter1Complete)
                    {
                        buttons[7].buttonTexture.render(buttons[7].getPositionX(),buttons[7].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                    }

                    //chapter 1 button
                    buttons[5].buttonTexture.render(buttons[5].getPositionX(),buttons[5].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                    //back button
                    buttons[0].buttonTexture.render(buttons[0].getPositionX(),buttons[0].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                }
                else if(gameState == 3)
                {
                    //options screen
                    optionsTexture.render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                    buttons[0].buttonTexture.render(buttons[0].getPositionX(),buttons[0].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                    fullScreenButtonTextureToggle();
                }
                else if(gameState == 5)
                {
                    if(chapter1Timer.isStarted()==false)
                    {
                        chapter1Timer.start();
                    }
                    //Chapter 1
                    for(int j = 0; j<TOTAL_PAGES;j++){
                        //render background & dialog box before script lines
                        switch(chapter.currentPage %TOTAL_PAGES){
                            case 0:chapter.chapter1BG[0].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                                    break;
                            case 1:chapter.chapter1BG[1].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                                    break;
                            case 2:chapter.chapter1BG[2].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                                    break;
                            case 3:chapter.chapter1BG[3].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                                    break;
                            case 4:chapter.chapter1BG[4].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                                    break;
                            case 5:chapter.chapter1BG[5].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                                    break;
                            case 6:chapter.chapter1BG[6].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                                    break;
                            case 7:chapter.chapter1BG[7].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                                    break;
                        }
                        //if player presses 'h' to hide dialog box or not.
                        if(hideDialogBox == false){
                            dialogBox.render(0,400,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                        }
                        if(hideDialogAndBox==false){
                            for(int i = 0; i<TOTAL_SCRIPTS;i++){
                                //render script lines
                                if(i <= chapter.currentScript)
                                {
                                    chapter.scriptTexture[chapter.currentPage][i].render(20,420 + (i*20),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                                }
                            }
                        }
                    }
                    switch(aniFrame){
                    case 0:tao[0].render(750,350,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                        break;
                    case 1:tao[1].render(750,350,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                        break;
                    case 2:tao[2].render(750,350,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                        break;
                    case 3:tao[3].render(750,350,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                        break;
                    case 4:tao[4].render(750,350,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                        break;
                    case 5:tao[5].render(750,350,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                        break;
                    case 6:tao[6].render(750,350,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                        break;
                    case 7:tao[7].render(750,350,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                        break;
                    }
                    buttons[0].buttonTexture.render(buttons[0].getPositionX(),buttons[0].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                }
                else if(gameState == 4)
                {
                    creditsTexture.render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                    buttons[0].buttonTexture.render(buttons[0].getPositionX(),buttons[0].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                }
                else if(gameState == 6)
                {
                    thanksTexture.render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                    player1.render(renderer);
                    buttons[0].buttonTexture.render(buttons[0].getPositionX(),buttons[0].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                }
				//Update screen
				SDL_RenderPresent( renderer );
				++countedFrames;
				//If frame finished early
				int frameTicks = capTimer.getTicks();
				if( frameTicks < SCREEN_TICK_PER_FRAME )
				{
					//Wait remaining time
					SDL_Delay( SCREEN_TICK_PER_FRAME - frameTicks );
				}
                if(animationTimer.getTicks() / 500 > 1)
                {
                    ++aniFrame;
                    animationTimer.restart();
                }
                //set script line
                if(chapter1Timer.getTicks()/1000 > 1)
                {//implement timer auto script option.
                    if(chapter.currentScript<TOTAL_SCRIPTS-1)
                    {
                        chapter.scriptIncrement();
                        chapter1Timer.restart();
                        //printf("\n \n timer tick");
                        //testSaveVariables();
                    }
                    if(chapter.currentScript == TOTAL_SCRIPTS-1)
                    {
                        chapter1Timer.stop();
                    }
                }
				//Cycle animation
				if( aniFrame >= TAO_ANIMATION_FRAMES )
				{
					aniFrame = 0;
				}
			}
		}
	}
	//Free resources and close SDL
	close();
	return 0;
}


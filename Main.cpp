//SDL and system libraries
#include <SDL_mixer.h>
#include <iostream>
#include <assert.h>
#include <stddef.h>
//local classes
#include "button.h"
#include "Texture.h"
#include "timer.h"
#include "particle.h"
#include "chapter.h"
#include "saveGame.h"
//declare and set constant variables
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int TOTAL_STATES = 5;
const int SCREEN_FPS=60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;
const int TAO_ANIMATION_FRAMES = 8;
const int TOTAL_SOUNDS = 4;
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
//chapter1bg textures needs to be cleaned up, maybe made into an array.
Texture chapter1BG;
Texture chapter1BG2;
Texture chapter1BG3;
Texture chapter1BG4;
Texture chapter1BG5;
Texture chapter1BG6;
Texture dialogBox;
bool hideDialogBox = false;
bool hideDialog = false;
bool hideDialogAndBox = false;
bool hideNone = true;
bool fullScreen = false;
//declare music
Mix_Music *music = NULL;
//declare sound effects
//Mix_Chunk sound[TOTAL_SOUNDS];

Mix_Chunk *sound0 = NULL;
Mix_Chunk *sound1 = NULL;
Mix_Chunk *sound2 = NULL;
Mix_Chunk *sound3 = NULL;

//Buttons objects
button buttons[ TOTAL_BUTTONS ];
//animation textures
Texture tao[TAO_ANIMATION_FRAMES];
//savegame handler
saveGame savegame;
//particle objects
Particle particles[ TOTAL_PARTICLES ];
//declare chapter1
chapter chapter1;
//tests savegame variables, usually when altered, saved, or loaded.
void testSaveVariables();
//render particles to screen
void renderParticles();

bool setButtonTextures(bool success);

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
    return success;
}

void fullScreenButtonTextureToggle()
{
    if(buttons[6].fullScreen)
    {
        buttons[6].buttonTexture.loadFromFile("images/buttons/fullScreenOn.png", renderer);
        //window = SDL_CreateWindow( "Go Homeless!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_FULLSCREEN);
    //
    }
    else
    {
        buttons[6].buttonTexture.loadFromFile("images/buttons/fullScreenOff.png", renderer);
        //window = SDL_CreateWindow( "Go Homeless!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN );

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
		window = SDL_CreateWindow( "Go Homeless!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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
    std::cout << "\n currentChapter: " << std::to_string( chapter1.currentChapter );
    std::cout << "\n currentPage: " << std::to_string( chapter1.currentPage );
    std::cout << "\n currentScript: " << std::to_string( chapter1.currentScript );
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
	//buttons[7].buttonName="fullScreenOff";

	savegame.readFile();

    chapter1.currentChapter= savegame.gData[0];
    chapter1.currentPage= savegame.gData[1];
    chapter1.currentScript = savegame.gData[2];

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
    /*for( int i = 0; i < TOTAL_BUTTONS; ++i )
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
    */
	//game title image
	success = title.loadFromFile( "images/title.png",renderer );
	//load background image files for non-chapter1 backgrounds
	success = titleTexture.loadFromFile( "images/skidrow.png",renderer );
	//success = creditsTexture.loadFromFile( "images/creditsscreen.png",renderer );
	//success = optionsTexture.loadFromFile( "images/optionsscreen.png",renderer);
	success = loadGameTexture.loadFromFile( "images/loadgamescreen.png",renderer );
	success = chapterSelectTexture.loadFromFile( "images/busstop.png",renderer );
	success = creditsTexture.loadFromFile( "images/brickwall.png",renderer );
	success = optionsTexture.loadFromFile("images/maritime.png",renderer );
	//success = .loadFromFile( "images/busstop.png",renderer );
    //load chapter 1 background textures
    success = chapter1.setBGTextures(renderer);
   //load dialog box image
	success = dialogBox.loadFromFile( "images/dialogbox1.png",renderer );
    //set dialog box alpha (about 75% opaque @ 192)
    dialogBox.setAlpha(192);
	//Load music
	music = Mix_LoadMUS( "music/Radioactive Rain.mp3" );
	//Load sound effects
	/*
	for(int i = 0; i<TOTAL_SOUNDS;i++)
    {
        std::stringstream ss;
        ss << "sounds/titleitemselect" << (i+1) << ".wav";
        std::string str = ss.str();

        sound[i] = Mix_LoadWAV(str);
	}*/
	//load sounds (still working on new way).
	sound0 = Mix_LoadWAV( "sounds/titleitemselect1.wav" );
	sound1 = Mix_LoadWAV( "sounds/titleitemselect2.wav" );
	sound2 = Mix_LoadWAV( "sounds/titleitemselect3.wav" );
	sound3 = Mix_LoadWAV( "sounds/titleitemselect4.wav" );
    //load font
	chapter1.loadFont();

	//chapter1.loadChapterStrings(renderer);

    if(success == false)
    {
        printf("something didn't load right in loadmedia.");
    }
	return success;
}

void close()
{
    savegame.writeFile(chapter1.currentChapter,chapter1.currentPage,chapter1.currentScript);
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
            chapter1.scriptTexture[j][i].free();
        }
    }
    //free the tao animation textures
    for(int i=0;i<TAO_ANIMATION_FRAMES;i++){
        tao[i].free();
    }
    /*
    for(int i=0;i<TOTAL_SOUNDS;i++)
    {
        Mix_FreeChunk( sound[i] );
        sound[i]=NULL;
    }*/
    //free the title image
    title.free();
    //free the background textures
	titleTexture.free();
	chapterSelectTexture.free();
	loadGameTexture.free();
	optionsTexture.free();
	creditsTexture.free();
    chapter1.freeBGTextures();

	//free the dialog box for chapters
	dialogBox.free();
	//Free the sound effects

	Mix_FreeChunk( sound0 );
	Mix_FreeChunk( sound1 );
	Mix_FreeChunk( sound2 );
	Mix_FreeChunk( sound3 );
	sound0 = NULL;
	sound1 = NULL;
	sound2 = NULL;
	sound3 = NULL;
	//free the font
	TTF_CloseFont( chapter1.font );
    chapter1.font = NULL;
	//Free the music
	Mix_FreeMusic( music );
	music = NULL;
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
			//starting music
            //Mix_PlayMusic( music, -1 );

            //Set text color as black
			SDL_Color textColor = { 0, 0, 0, 255 };
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
                        if(gameState == 5)
                        {
                            if(chapter1.currentPage==TOTAL_PAGES-1 && chapter1.currentScript==TOTAL_SCRIPTS-1){
                                chapter1.completeChapter(renderer);
                                gameState=2;
                                chapter1Timer.stop();
                                //printf("\n \n currentPage & currentScript = 7");
                                //testSaveVariables();
                            }
                            else if (chapter1.currentScript<TOTAL_SCRIPTS-1)
                            {
                                chapter1.scriptIncrement();
                                chapter1Timer.restart();
                                //printf("\n \n left mouse down total scripts loop");
                                //testSaveVariables();
                            }
                            else if(chapter1.currentPage<TOTAL_PAGES-1){
                                chapter1.pageIncrement();
                                //printf("\n \n left mouse down total pages loop");
                                //testSaveVariables();
                                chapter1Timer.restart();
                            }
                        }
                        if(gameState == 1)//new game chapter select
                        {
                            chapter1.resetChapters(renderer);
                        }
                        if(gameState == 2){//load game chapter select
                            if(chapter1.currentPage<TOTAL_PAGES-1)
                            {
                                if(chapter1.currentPage!=0)
                                {
                                    if(chapter1.currentScript ==0)
                                    {//compensate for clicking back button at end of page.
                                        chapter1.backPage();
                                    }
                                }
                                if(chapter1.currentScript != 0 && chapter1.currentScript!=7)
                                {
                                    chapter1.backScript();
                                    //printf("\n %d \n",chapter1.currentScript);
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
                                    if(chapter1.currentScript<TOTAL_SCRIPTS-1)
                                    {
                                        chapter1.scriptIncrement();
                                        chapter1Timer.restart();
                                    }
                                    else
                                    {
                                        if(chapter1.currentPage<TOTAL_PAGES-1)
                                        {
                                            chapter1.pageIncrement();
                                            chapter1Timer.restart();
                                        }
                                        else
                                        {
                                            //currentPage=0;
                                            //printf("end of chapter 1 dialog return to game state = 0 \n");
                                            gameState = 2;
                                            chapter1.completeChapter(renderer);
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
							Mix_PlayChannel( -1, sound0, 0 );
							break;
							//Play sound effect
							case SDLK_2:
							Mix_PlayChannel( -1, sound1, 0 );
							break;
							case SDLK_3:
							Mix_PlayChannel( -1, sound2, 0 );
							break;
							case SDLK_4:
							Mix_PlayChannel( -1, sound3, 0 );
							break;
							case SDLK_h:
							if(hideDialogBox == false)
                            {
                                hideDialogBox = true;
							}
							else
                            {
                                hideDialogBox = false;
							}
							printf("\n h pressed \n");
                            std::cout << "hideDialogBox: " << hideDialogBox;
							break;
							case SDLK_9:
							//If there is no music playing
							if( Mix_PlayingMusic() == 0 )
							{
								//Play the music
								Mix_PlayMusic( music, -1 );
							}
							//If music is being played
							else
							{
								//If the music is paused
								if( Mix_PausedMusic() == 1 )
								{
									//Resume the music
									Mix_ResumeMusic();
								}
								//If the music is playing
								else
								{
									//Pause the music
									Mix_PauseMusic();
								}
							}
							break;
							case SDLK_0:
							//Stop the music
							Mix_HaltMusic();
							break;
						}
					}
					//Handle button events
					for( int i = 0; i < TOTAL_BUTTONS; ++i )
					{
						//if(gameState == 3){
                           // if(i==0){
                            //    gameState = buttons[i].handleEvent(gameState,buttons[i].buttonName, &e );
                           // }
/*
                            else if(i==6){
                                if(fullScreen == false)
                                {
                                    fullScreen = buttons[i].setFullScreenOff();
                                }
                            }
                            else if(i==7)
                            {
                                if(fullScreen)
                                {
                                    fullScreen = buttons[i].setFullScreenOn();
                                }
                            }*/
						//}
                        //else{

                            gameState = buttons[ i ].handleEvent(gameState,buttons[i].buttonName, &e, window );


                            /*if(i==6 or i==7)
                            {
                                fullScreen = buttons[i].fullScreen
                            }*/
                        //}

					}
				}
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
                        if(i<5)//5 is back button
                            buttons[i].buttonTexture.render(buttons[i].getPositionX(),buttons[i].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                    }
                }
                else if(gameState == 1)
                {//new gamme chapter select screen
                    chapter1Timer.stop();
                    chapterSelectTexture.render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer );
                    //chapter 1 button
                    buttons[5].buttonTexture.render(buttons[5].getPositionX(),buttons[5].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                    //back button
                    buttons[0].buttonTexture.render(buttons[0].getPositionX(),buttons[0].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                }
                else if(gameState == 2)
                {
                    chapter1Timer.stop();
                    //chapter select screen
                    chapterSelectTexture.render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
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

                    //THIS AREA NEEDS WORK, attempting to get the button to change when pressed before changing window
                    //Debugging was killing me, so yeah.
                    fullScreenButtonTextureToggle();
                    /*
                    if(!buttons[7].fullScreen)
                    {
                        buttons[6].buttonTexture.render(buttons[6].getPositionX(),buttons[6].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                    }
                    else if(buttons[6].fullScreen)
                    {
                        buttons[7].buttonTexture.render(buttons[7].getPositionX(),buttons[7].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                    }*/
                }
                else if(gameState == 5)
                {
                    if(chapter1Timer.isStarted()==false)
                        chapter1Timer.start();
                    //Chapter 1
                    for(int j = 0; j<TOTAL_PAGES;j++){
                        //render background & dialog box before script lines
                        switch(chapter1.currentPage %TOTAL_PAGES){
                            case 0:chapter1.chapter1BG[0].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                                    break;
                            case 1:chapter1.chapter1BG[1].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                                    break;
                            case 2:chapter1.chapter1BG[2].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                                    break;
                            case 3:chapter1.chapter1BG[3].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                                    break;
                            case 4:chapter1.chapter1BG[4].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                                    break;
                            case 5:chapter1.chapter1BG[5].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                                    break;
                            case 6:chapter1.chapter1BG[6].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                                    break;
                            case 7:chapter1.chapter1BG[7].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                                    break;


                        }
                        //if player presses 'h' to hide dialog box or not.
                        if(hideDialogBox == false || hideDialogAndBox==false){
                            dialogBox.render(0,400,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                        }
                        if(hideDialog==false || hideDialogAndBox==false){
                            for(int i = 0; i<TOTAL_SCRIPTS;i++){
                                //render script lines
                                if(i <= chapter1.currentScript)
                                {
                                    chapter1.scriptTexture[chapter1.currentPage][i].render(20,420 + (i*20),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
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
                else
                {
                    creditsTexture.render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
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
                    if(chapter1.currentScript<TOTAL_SCRIPTS-1)
                    {
                        chapter1.scriptIncrement();
                        chapter1Timer.restart();
                        //printf("\n \n timer tick");
                        //testSaveVariables();
                    }
                    if(chapter1.currentScript == TOTAL_SCRIPTS-1)
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


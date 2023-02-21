//local classes
#include "audio.h"
#include "button.h"
#include "Texture.h"
#include "timer.h"
#include "particle.h"
#include "chapter.h"
#include "saveGame.h"
#include "pregameui.h"
#include "animations.h"
#include "stage.h"
const int TOTAL_STATES = 7;

//gameStates
//gameState = 0 pregameui
//gameState = 1 new game chapter select
//gameState = 2 load game chapter select
//gameState = 3 options
//gameState = 4 credits
//gameState = 5 chapter 1
//gameState = 6 stage 1
//gameState = 7 chapter 2

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
//savegame handler
saveGame savegame;
audio music;
std::vector<audio> sounds;
audio sound;
//declare chapter1
chapter chapter;
//declare stage
stage stage;
//declare instance of pregame user interface.
pregameui pregameui;
//declare instance of animations
animations animations;
//declare sound vector & load sounds into it.
void loadSounds();
//render particles to screen
//tracks the state of the game for rendering etc.
int gameState;
//initializes audio,video, etc.
Texture blackGround;
bool fadeOut(int countedFrames, bool fade);

bool fadeIn(int countedFrames,bool fade);

bool fadeIn(int countedFrames, bool fade)
{
//this stuff is still experimental.  gonna have to figure something out for this system.

    //std::cout << "fade in function is triggered\n";


        Uint32 alpha = 255-(countedFrames%256);
        blackGround.setAlpha(alpha);
        //std::cout << "\n alpha: " << alpha;

    if(countedFrames%256>254)
    {
        fade=false;
        std::cout <<"fade In counted Frames:" << countedFrames << " \n";
    }

    return fade;
}

bool fadeOut(int countedFrames, bool fade)
{

       if(countedFrames%256 < 255)
            {  //fades in the go homeless title
                blackGround.setAlpha(countedFrames);

            }


    if(countedFrames%256>=255)
    {
        fade=false;
        std::cout <<"fade out counted Frames:" << countedFrames << " \n";
    }

return fade;
}

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
				pregameui.createParticles(renderer);
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
    pregameui.setButtonNames();
    chapter.setButtonNames();
    stage.setButtonNames();
    //load saved game
	savegame.readFile();
	//set chapter variables based on savegame data.
	chapter.loadSavedVariables(savegame.data[0],savegame.data[1],savegame.data[2],savegame.data[3]);
	//test the variables after loading
    chapter.testSaveVariables();
    //load animations textures
    success = animations.setAnimationTextures(renderer);
    //set button positions & image textures
    success = pregameui.setPreGameButtonTextures(renderer, success);
    //load titlescreen textures, credit screen textures, etc.
    success = pregameui.setPGUITextures(renderer);
    //sets up button textures and positions for chapter buttons
    success = chapter.setChapterButtonTextures(renderer,success);
    //load chapter 1 background textures
    success = chapter.setChapterTextures(renderer);
    //load stage button textures and positions
    success = stage.setStageButtonTextures(renderer,success);
    //set stage bg texture
    success = stage.setStageTextures(renderer);
    //load font
	chapter.loadFont();
	//load sound effects
	loadSounds();
    //load player texture
    stage.player1.loadPlayer(renderer);
    //fade to black background
    blackGround.loadFromFile("images/Blackground.png",renderer);
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
    chapter.testSaveVariables();
    //free the button textures
    chapter.freeButtons();
    pregameui.freeButtons();
    stage.freeButtons();
    stage.freeBGTextures();
    stage.player1.freePlayer();
    //free animation textures
    animations.freeAnimationTextures();
    //free pregame ui textures
    pregameui.freePGUITextures();
	//free the backgrounds, dialog box, menubar for chapters and script textures
	chapter.freeBGTextures();
	blackGround.free();
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

			bool fade=false;
			//load the bg music file
			//chapter.loadChapterStrings(renderer);
            music.loadMusic();
            music.playMusic();
			//The frames per second cap timer
			timer capTimer;
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
                    if(e.type == SDL_MOUSEBUTTONDOWN)
                    {
                        if(gameState == 0)
                        {
                            //fade = true;
                        }

                        if(gameState == 1)//new game chapter select
                        {
                            //chapters get reset here, but I may have the actual chapter 1 button on this screen determine the reset.
                            chapter.resetChapters(renderer);
                        }
                        if(gameState == 2){//load game chapter select
                                //fade = true;
                                //fade = fadeIn(countedFrames,fade);
                        //std::cout << "mouse down in gameState = 2";
                                //correction for the mousedown event that increments even when button press on back button happening.
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
                        if(gameState == 7)//chapter 2
                        {
                            gameState = chapter.progress(renderer,gameState);
                        }
                        if(gameState == 5) //Chapter 1
                        {
                            //need if(!insideButtons())
                            //updates counters for script lines,turns pages, changes gameState if at end of chapter.
                            gameState = chapter.progress(renderer,gameState);
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
                                    //update script line, page, end chapter
                                    gameState = chapter.progress2(renderer,gameState);
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
							    //press h to cycle dialog visability
							    chapter.handleDialogVisability();
							break;
							case SDLK_9:
                                //press 9 to play / pause music
                                music.playMusic();
							break;
						}
					}
					//Handle button events when in pregame ui or stage 1.
					if(gameState <5 || gameState==6)
                    {
                        int oldGameState = gameState;
                        for( int i = 0; i < TOTAL_PREGAME_BUTTONS; ++i )
                        {
                            gameState = pregameui.buttons[ i ].handleEvent(gameState,pregameui.buttons[i].buttonName, &e, window,renderer );
                        }
                        //printf("gameState = ", gameState);
                        if(gameState == 5)
                        {
                            if(chapter.currentChapter != 0)
                            {
                                chapter.currentChapter = 0;
                                chapter.resetPages();
                            }
                            music.stopMusic();
                            music.loadChapter1Music();
                            music.playMusic();
                            chapter.setChapterTextures(renderer);
                            chapter.loadChapterStrings(renderer);
                            chapter.testSaveVariables();
                        }
                        if(gameState == 7)
                        {
                            if(chapter.currentChapter!=1)
                            {
                                chapter.currentChapter =1;
                                chapter.resetPages();
                            }
                            music.stopMusic();
                            music.loadChapter2Music();
                            music.playMusic();
                            chapter.setChapterTextures(renderer);
                            chapter.loadChapterStrings(renderer);
                            chapter.testSaveVariables();
                        }
                        if(gameState != oldGameState)
                        {
                            int newGameState = gameState;
                            gameState = oldGameState;
                            fade=true;
                            //if(countedFrames%256 < 255)
                            //{

                            fade=fadeOut(countedFrames,fade);
                            //}
                            //if(!fade)
                            gameState=newGameState;

                        }
                    }

                    if(gameState == 5)
                    {
                        //handles button presses in chapter 1 (autospeed changes, backpage, etc).
                        gameState = chapter.handleChapterButtonPresses(gameState,&e,window,renderer );
                        if(gameState==0){
                            music.stopMusic();
                            music.loadMusic();
                            music.playMusic();
                        }
                    }
                    if(gameState == 7)
                    {
                        //handles button presses for chapter 2.
                        gameState = chapter.handleChapterButtonPresses(gameState,&e,window,renderer);
                        if(gameState==0){
                            music.stopMusic();
                            music.loadMusic();
                            music.playMusic();
                        }
                    }
					//if wasd are pressed player will be moved.
					stage.player1.handleEvent(e);
				}
				//process player movement
				stage.player1.move();
				//Clear screen
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( renderer );
                //Title Screen rendering

                if(gameState == 0)
                {
                    chapter.chapterTimer.stop();
                    //renders buttons, bg, title image, and handles particle effect.
                    pregameui.handleTitleScreenRendering(renderer);

                }
                else if(gameState == 1)
                {//new game chapter select screen
                    chapter.chapterTimer.stop();
                    pregameui.handleNewGameScreenRendering(renderer);
                }
                else if(gameState == 2)
                {//load game chapter/stage select screen

                    chapter.chapterTimer.stop();

                    //handles the buttons and background rendering
                    pregameui.handleLoadGameScreenRendering(renderer,chapter.chapter1Complete);


                }
                else if(gameState == 3)
                {
                    //options screen buttons/bg rendering
                    pregameui.handleOptionsScreenRendering(renderer);
                }
                //chapter 1 is in effect
                else if(gameState == 5)
                {
                    if(!chapter.chapterTimer.isStarted())
                    {
                        chapter.chapterTimer.start();
                    }
                    //Chapter 1 rendering (buttons and backgrounds and text.
                    chapter.handleRendering(renderer);
                    //render tao animation
                    animations.renderTao(renderer);
                }
                //if chapter 2 is in effect
                else if(gameState == 7)
                {
                    if(!chapter.chapterTimer.isStarted())
                    {
                        chapter.chapterTimer.start();
                    }
                    chapter.handleRendering(renderer);
                }
                else if(gameState == 4)
                {
                    //render background image and back button
                    pregameui.handleCreditsScreenRendering(renderer);
                    //robot animation
                    animations.renderToaster(renderer);
                    //animations.renderToaster2(renderer);
                }
                else if(gameState == 6)
                {
                    //temporary texture until I get the tiles working on this gamestate
                    //this stuff should all be part of stage class eventually.
                    stage.stage1BG[0].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                    stage.player1.render(renderer);
                    stage.buttons[0].buttonTexture.render(stage.buttons[0].getPositionX(),stage.buttons[0].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                }
                if(fade)
                {
                    fade = fadeIn(countedFrames,fade);
                    blackGround.render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                }

				//Update screen
				SDL_RenderPresent( renderer );
				++countedFrames;
				if(countedFrames>0 && countedFrames < 255 && gameState==0)
                {  //fades in the go homeless title
                    pregameui.title.setAlpha(countedFrames);
                }

				//If frame finished early
				int frameTicks = capTimer.getTicks();
				if( frameTicks < SCREEN_TICK_PER_FRAME )
				{
					//Wait remaining time
					SDL_Delay( SCREEN_TICK_PER_FRAME - frameTicks );
				}
				//the tao animation timer
				animations.taoAnimationProgress();
                //the timer for toaster the robot's animation
                animations.toasterAnimationProgress();

                animations.toaster2AnimationProgress();
                //set script line
                chapter.setAutoScript();
				//Cycle animation
				animations.cycleAnimations();
			}
		}
	}
	//Free resources and close SDL
	close();
	return 0;
}


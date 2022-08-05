//local classes
#include "audio.h"
#include "button.h"
#include "Texture.h"
#include "timer.h"
#include "particle.h"
#include "chapter.h"
#include "saveGame.h"
#include "player.h"
#include "pregameui.h"
#include "animations.h"
#include "stage.h"
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
//declare instance of pregame user interface.
pregameui pregameui;
//declare instance of animations
animations animations;
//declare sound vector & load sounds into it.
void loadSounds();
//render particles to screen
void renderParticles();
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
	for(int i = 0; i<TOTAL_PREGAME_BUTTONS; i++)
    {
        pregameui.buttons[i].setPregameButtonName(i);
    }
    for(int i = 0; i < TOTAL_CHAPTER_BUTTONS; i++)
    {
        chapter.buttons[i].setChapterButtonName(i);
    }
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
    chapter.testSaveVariables();
    //free the button textures
    for(int i = 0; i<TOTAL_CHAPTER_BUTTONS;i++)
    {
        chapter.buttons[i].buttonTexture.free();
    }
    for(int i = 0; i<TOTAL_PREGAME_BUTTONS;i++)
    {
        pregameui.buttons[i].buttonTexture.free();
    }
    //free animation textures
    animations.freeAnimationTextures();
    //free pregame ui textures
    pregameui.freePGUITextures();
	//free the backgrounds, dialog box, menubar for chapters and script textures
	chapter.freeBGTextures();
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
			//load the bg music file
			chapter.loadChapterStrings(renderer);
            music.loadMusic();
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
                    if(e.type == SDL_MOUSEBUTTONDOWN){
                        if(gameState == 5) //Chapter 1
                        {
                            //need if(!insideButtons())
                            //updates counters for script lines,turns pages, changes gameState if at end of chapter.
                            gameState = chapter.progress(renderer,gameState);
                        }
                        if(gameState == 1)//new game chapter select
                        {
                            //chapters get reset here, but I may have the actual chapter 1 button on this screen determine the reset.
                            chapter.resetChapters(renderer);
                        }
                        if(gameState == 2){//load game chapter select
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
					//Handle button events
					if(gameState <5 || gameState==6)
                    {
                        for( int i = 0; i < TOTAL_PREGAME_BUTTONS; ++i )
                        {
                            gameState = pregameui.buttons[ i ].handleEvent(gameState,pregameui.buttons[i].buttonName, &e, window,renderer );
                        }
                    }
                    if(gameState == 5)
                    {
                        for(int i = 0; i<TOTAL_CHAPTER_BUTTONS; ++i)
                        {
                            //if player presses backpage button, ugly af, but it works somewhat
                            if(i==0)
                            {
                                if(chapter.buttons[ i ].handleEvent(gameState,chapter.buttons[i].buttonName, &e, window,renderer ) == -1)
                                {
                                    chapter.handleBackPagePress();
                                }
                            }
                            //if player presses backline button, ugly af, but it works somewhat
                            if(i==1)
                            {
                                if(chapter.buttons[ i ].handleEvent(gameState,chapter.buttons[i].buttonName, &e, window,renderer ) == -1)
                                {
                                    chapter.handleBackLinePress();
                                }
                            }
                            //player presses auto Text on (resumes progress of chapters if stopped).
                            if(i==2)
                            {
                                if(chapter.buttons[ i ].handleEvent(gameState,chapter.buttons[i].buttonName, &e, window,renderer )==1)
                                {
                                    chapter.autoText=true;
                                }
                            }
                            //player presses auto text off (stops progress of chapters)
                            if(i==3)
                            {
                                if(chapter.buttons[ i ].handleEvent(gameState,chapter.buttons[i].buttonName, &e, window,renderer )==0)
                                {
                                    chapter.autoText=false;
                                }
                            }
                            //auto text speed slow button is pressed.
                            if(i==4 && chapter.buttons[ i ].handleEvent(gameState,chapter.buttons[i].buttonName, &e, window,renderer ) == 0)
                            {
                                chapter.autoTextSpeed = 0;
                            }
                            //auto text speed medium button is pressed.
                            if(i==5 && chapter.buttons[ i ].handleEvent(gameState,chapter.buttons[i].buttonName, &e, window,renderer ) == 1)
                            {
                                chapter.autoTextSpeed = 1;
                            }
                            //auto text speed fast button is pressed.
                            if(i==6 && chapter.buttons[ i ].handleEvent(gameState,chapter.buttons[i].buttonName, &e, window,renderer ) == 2)
                            {
                                chapter.autoTextSpeed = 2;
                                //chapter.autoTextSpeed=2;
                            }
                            if(i==7)
                            {//save and exit button
                                gameState=chapter.buttons[i].handleEvent(gameState,chapter.buttons[i].buttonName,&e,window,renderer);
                            }
                        }
                    }

					//if wasd are pressed player will be moved.
					player1.handleEvent(e);
				}
				//process player movement
				player1.move();
				//Clear screen
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( renderer );
                //Title Screen rendering
                if(gameState == 0)
                {
                    chapter.chapter1Timer.stop();
                    pregameui.titleTexture.render( 0, 0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer );
                    renderParticles();
                    pregameui.title.render(200, 100,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                    //render title screen buttons
                    //5 is back button 6 is fullscreen button
                    for(int i=1;i<5;i++)
                    {
                        pregameui.buttons[i].buttonTexture.render(pregameui.buttons[i].getPositionX(),pregameui.buttons[i].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                    }
                }
                else if(gameState == 1)
                {//new game chapter select screen
                    chapter.chapter1Timer.stop();
                    pregameui.chapterSelectTexture.render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer );
                    //chapter 1 button
                    pregameui.buttons[5].buttonTexture.render(pregameui.buttons[5].getPositionX(),pregameui.buttons[5].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                    //back button
                    pregameui.buttons[0].buttonTexture.render(pregameui.buttons[0].getPositionX(),pregameui.buttons[0].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                }
                else if(gameState == 2)
                {//load game chapter/stage select screen
                    chapter.chapter1Timer.stop();
                    //chapter select screen
                    pregameui.chapterSelectTexture.render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                    //if chapter 1 is complete, render stage 1 button
                    if(chapter.chapter1Complete)
                    {  //render stage 1 button
                        pregameui.buttons[7].buttonTexture.render(pregameui.buttons[7].getPositionX(),pregameui.buttons[7].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                    }
                    //chapter 1 button
                    pregameui.buttons[5].buttonTexture.render(pregameui.buttons[5].getPositionX(),pregameui.buttons[5].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                    //back button
                    pregameui.buttons[0].buttonTexture.render(pregameui.buttons[0].getPositionX(),pregameui.buttons[0].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                }
                else if(gameState == 3)
                {
                    //options screen
                    pregameui.optionsTexture.render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                    pregameui.buttons[0].buttonTexture.render(pregameui.buttons[0].getPositionX(),pregameui.buttons[0].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                    pregameui.buttons[6].fullScreenButtonTextureToggle(renderer);
                }
                else if(gameState == 5)
                {
                    if(chapter.chapter1Timer.isStarted()==false)
                    {
                        chapter.chapter1Timer.start();
                    }
                    //Chapter 1
                    for(int j = 0; j<TOTAL_PAGES;j++){
                        //render background & dialog box before script lines
                        chapter.renderBackgrounds(renderer,j);

                        //chapter.buttons[0].buttonTexture.render(chapter.buttons[0].getPositionX(),chapter.buttons[0].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                        //chapter.buttons[1].buttonTexture.render(chapter.buttons[1].getPositionX(),chapter.buttons[1].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);

                        if(chapter.autoText)
                        {
                            //render auto texture on button (hightlights auto text on in menubar)
                            chapter.buttons[2].buttonTexture.render(chapter.buttons[2].getPositionX(),chapter.buttons[2].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                        }
                        else
                        {
                            //render auto texture off button (hightlights auto text off in menubar)
                            chapter.buttons[3].buttonTexture.render(chapter.buttons[3].getPositionX(),chapter.buttons[3].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                        }
                        if(chapter.autoTextSpeed==0)
                        {
                            //highlights text speed 1
                            chapter.buttons[4].buttonTexture.render(chapter.buttons[4].getPositionX(),chapter.buttons[4].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                        }
                        else if(chapter.autoTextSpeed==1)
                        {
                            //highlights text speed 2
                            chapter.buttons[5].buttonTexture.render(chapter.buttons[5].getPositionX(),chapter.buttons[5].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                        }
                        else if(chapter.autoTextSpeed==2)
                        {
                            //highlights text speed 3
                            chapter.buttons[6].buttonTexture.render(chapter.buttons[6].getPositionX(),chapter.buttons[6].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                        }
                        chapter.menuBar.render(0,350,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                        //load page number into menubar
                        chapter.loadPageText(renderer);
                        chapter.curPageTextTexture.render(140,352,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                        //load line number into menubar
                        chapter.loadLineText(renderer);
                        chapter.curLineTextTexture.render(130,374,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                        //if the state of the dialog box visibility gets changed, this handles the rendering or not rendering.
                        chapter.handleDialogRendering(renderer);
                    }
                    animations.renderTao(renderer);
                    //render save & exit button
                    chapter.buttons[7].buttonTexture.render(chapter.buttons[7].getPositionX(),chapter.buttons[7].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                }
                else if(gameState == 4)
                {
                    pregameui.creditsTexture.render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                    animations.renderToaster(renderer);
                    pregameui.buttons[0].buttonTexture.render(pregameui.buttons[0].getPositionX(),pregameui.buttons[0].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                }
                else if(gameState == 6)
                {
                    //temporary texture until I get the tiles working on this gamestate
                    pregameui.thanksTexture.render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
                    player1.render(renderer);
                    pregameui.buttons[0].buttonTexture.render(pregameui.buttons[0].getPositionX(),pregameui.buttons[0].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
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
				//the tao animation timer
				animations.taoAnimationProgress();
                //the timer for toaster the robot's animation
                animations.toasterAnimationProgress();
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


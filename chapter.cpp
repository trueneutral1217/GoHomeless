#include "chapter.h"

chapter::chapter()
{
    currentChapter = 0;
    chapter1Complete = false;
    currentPage = 0;
    currentScript = 0;
    autoText = true;
    autoTextSpeed = 0;
    for(int j =0; j <TOTAL_PAGES; j++)
    {
        for(int i = 0; i<TOTAL_SCRIPTS; i++)
        {
            scriptString[j][i].str("");
        }
    }

    for(int j =0; j <TOTAL_PAGES; j++)
    {
        for(int i = 0; i<TOTAL_SCRIPTS; i++)
        {
            //scriptTexture[j][i] = NULL;
        }
    }
    font = NULL;
    pageText.str( "" );
    lineText.str( "" );
}

chapter::~chapter()
{
    for(int i = 0; i < TOTAL_PAGES;i++)
    {
        for(int j = 0; j < TOTAL_SCRIPTS;j++)
        {
            //scriptString[i][j].free();
        }
    }
}

void chapter::scriptIncrement()
{
    currentScript++;

}
void chapter::pageIncrement()
{
    currentPage++;
    currentScript=0;
}
void chapter::backScript()
{
    if(0 < currentScript)
    {
        currentScript--;
    }
}
void chapter::backPage()
{
    if(0 < currentPage)
    {
        currentPage--;
        currentScript=7;
    }
}
void chapter::completeChapter(SDL_Renderer* renderer)
{
    if(!chapter1Complete)
    {
        //currentChapter++;
    }
    resetPages();
    chapter1Complete=true;
}
void chapter::resetPages()
{
    currentPage=0;
    resetScripts();
}
void chapter::resetScripts()
{
    currentScript=0;
}
void chapter::resetChapters(SDL_Renderer* renderer)
{
    currentChapter=0;
    resetPages();
    chapter1Complete = false;
}
void chapter::loadChapterStrings(SDL_Renderer* renderer)
{
	if(currentChapter==0)
    {
        //chapter 1, page 1
        scriptString[0][0].str( "5 years ago, I stopped working regular jobs." );
        scriptString[0][1].str("Since then I've mostly begged for money on the street corner");
        scriptString[0][2].str("with cardboard signs that say things like 'Anything Helps'.");
        scriptString[0][3].str("I stopped working because I noticed a few major problems with");
        scriptString[0][4].str("our socio-economic system.  self-driving cars were commercially viable,");
        scriptString[0][5].str("but the state of California red-taped self driving cars. It made sense");
        scriptString[0][6].str("why... it would greatly affect the need for labor in the workforce.");
        scriptString[0][7].str("                                Press LMB or Enter to continue...");
        //chapter 1, page 2
        scriptString[1][0].str("If the car is driving, the person behind the wheel [but why tf");
        scriptString[1][1].str("would there be a wheel?] can't be held liable, which makes the car driving");
        scriptString[1][2].str("system responsible, but their cars drive better than humans, so that");
        scriptString[1][3].str("won't be much of a problem.  They would probably insure their own");
        scriptString[1][4].str("cars, which would reduce auto insurance agents.  Besides that, ");
        scriptString[1][5].str("it's hard to find probable cause when the car is driving, which");
        scriptString[1][6].str("reduces the need for police on the streets.");
        scriptString[1][7].str("                                Press LMB or Enter to continue...");
        //chapter 1, page 3
        scriptString[2][0].str("when self-driving cars are freely allowed, the need for cars drops.");
        scriptString[2][1].str("One car can be used by an entire family by summoning it as needed");
        scriptString[2][2].str("when not in active use.  But mainly, drivers would lose jobs, taxi");
        scriptString[2][3].str("drivers, gig-economy transportation drivers, and big-rig truckers.");
        scriptString[2][4].str("Self-driving cars would require a black box like airplanes for liability");
        scriptString[2][5].str("as well as bug fixes.  The goal is 100% safety on the road. 30,000");
        scriptString[2][6].str("automobile deaths yearly would be greatly reduced by self driving cars.");
        scriptString[2][7].str("                                Press LMB or Enter to continue...");
        //chapter 1, page 4
        scriptString[3][0].str("The only problem with changing over to large scale automation in areas");
        scriptString[3][1].str("like driving is the job problem.  The only way to deal with a job market");
        scriptString[3][2].str("that is smaller than the labor force is to implement Universal Basic Income.");
        scriptString[3][3].str("Universal Basic Income is the idea that everyone, no matter their employment");
        scriptString[3][4].str("status receives a certain amount of money.  debtors can not garnish it, and");
        scriptString[3][5].str("you still receive it if you are working...  ");
        scriptString[3][6].str("My mission is Universal basic income.");
        scriptString[3][7].str("                                Press LMB or Enter to continue...");
        //chapter 1, page 5
        scriptString[4][0].str("You may be asking yourself: Won't people lose the incentive ");
        scriptString[4][1].str("to work if they receive UBI?  and yes, they will.  Millions of");
        scriptString[4][2].str("Americans are working minimum wage jobs that don't provide a ");
        scriptString[4][3].str("living wage.  The companies that provide these jobs fight against");
        scriptString[4][4].str("worker's rights, because nothing is more important to them than");
        scriptString[4][5].str("the bottom line.  In my last job I was working in a call center for");
        scriptString[4][6].str("a big telecom company.  bedbugs and mandatory overtime for all.");
        scriptString[4][7].str("                                Press LMB or Enter to continue...");
        //chapter 1, page 6
        scriptString[5][0].str("Since that job I've worked for myself mostly. Besides begging on");
        scriptString[5][1].str("street corners, I have knitted several scarves although I never made");
        scriptString[5][2].str("any money on them, only gave them away, except one that a friend");
        scriptString[5][3].str("tried on and walked off with... sigh.  I've painted a lot of paintings");
        scriptString[5][4].str("and sold a few of them.  acrylic + canvas.  I'm an avid gamer and");
        scriptString[5][5].str("since I'm basically retired, I play a lot of pc/android games.");
        scriptString[5][6].str("I have a bachelor's degree in computer science, so I'm programming this.");
        scriptString[5][7].str("                                Press LMB or Enter to continue...");
        //chapter1 page 7
        scriptString[6][0].str("If universal basic income is instated, the ultra rich know that");
        scriptString[6][1].str("eventually we will move toward income equality across the planet.");
        scriptString[6][2].str("That means people will be doing what they want to instead of what");
        scriptString[6][3].str("they must.  Since my last job I've been doing my part in keeping");
        scriptString[6][4].str("the demand for labor up by not working.  I want a future where");
        scriptString[6][5].str("employers don't low-ball new employees on wages, and perhaps we");
        scriptString[6][6].str("can return to a time where employers search for employees.");
        scriptString[6][7].str("                                Press LMB or Enter to continue...");
        //chapter1 page8
        scriptString[7][0].str("I grew up playing PC and console videogames.  I knew I wanted");
        scriptString[7][1].str("to make videogames.  It's why I got into computer science.");
        scriptString[7][2].str("unfortunately the market for game developers is too competitive,");
        scriptString[7][3].str("so I'm making this game independently in my spare time, with zero");
        scriptString[7][4].str("budget. The jobs in the computer science field are cut-throat and");
        scriptString[7][5].str("don't actually pay as much as I thought they would. I'm done making");
        scriptString[7][6].str("online surveys for market research.");
        scriptString[7][7].str(" *End of Chapter 1* Press LMB or Enter to return to select screen.");
    }

    if(currentChapter==1)
    {
        //chapter 2 page 1
        scriptString[0][0].str("1");
        scriptString[0][1].str("2");
        scriptString[0][2].str("3");
        scriptString[0][3].str("4");
        scriptString[0][4].str("5");
        scriptString[0][5].str("6");
        scriptString[0][6].str("7");
        scriptString[0][7].str("                                Press LMB or Enter to continue...");
        //chapter 2, page 2
        scriptString[1][0].str("1");
        scriptString[1][1].str("2");
        scriptString[1][2].str("3");
        scriptString[1][3].str("4");
        scriptString[1][4].str("5");
        scriptString[1][5].str("6");
        scriptString[1][6].str("7");
        scriptString[1][7].str("                                Press LMB or Enter to continue...");
        //chapter 2, page 3
        scriptString[2][0].str("1");
        scriptString[2][1].str("2");
        scriptString[2][2].str("3");
        scriptString[2][3].str("4");
        scriptString[2][4].str("5");
        scriptString[2][5].str("6");
        scriptString[2][6].str("7");
        scriptString[2][7].str("                                Press LMB or Enter to continue...");
        //chapter 2, page 4
        scriptString[3][0].str("1");
        scriptString[3][1].str("2");
        scriptString[3][2].str("3");
        scriptString[3][3].str("4");
        scriptString[3][4].str("5");
        scriptString[3][5].str("6");
        scriptString[3][6].str("7");
        scriptString[3][7].str("                                Press LMB or Enter to continue...");
        //chapter 2, page 5
        scriptString[4][0].str("1");
        scriptString[4][1].str("2");
        scriptString[4][2].str("3");
        scriptString[4][3].str("4");
        scriptString[4][4].str("5");
        scriptString[4][5].str("6");
        scriptString[4][6].str("7");
        scriptString[4][7].str("                                Press LMB or Enter to continue...");
        //chapter 2, page 6
        scriptString[5][0].str("1");
        scriptString[5][1].str("2");
        scriptString[5][2].str("3");
        scriptString[5][3].str("4");
        scriptString[5][4].str("5");
        scriptString[5][5].str("6");
        scriptString[5][6].str("7");
        scriptString[5][7].str("                                Press LMB or Enter to continue...");
        //chapter 2, page 7
        scriptString[6][0].str("1");
        scriptString[6][1].str("2");
        scriptString[6][2].str("3");
        scriptString[6][3].str("4");
        scriptString[6][4].str("5");
        scriptString[6][5].str("6");
        scriptString[6][6].str("7");
        scriptString[6][7].str("                                Press LMB or Enter to continue...");
        //chapter 2, page 8
        scriptString[7][0].str("1");
        scriptString[7][1].str("2");
        scriptString[7][2].str("3");
        scriptString[7][3].str("4");
        scriptString[7][4].str("5");
        scriptString[7][5].str("6");
        scriptString[7][6].str("7");
        scriptString[7][7].str(" *End of Chapter 1* Press LMB or Enter to return to select screen.");
    }

    setScriptTextures(renderer);
}

void chapter::freeBGTextures()
{
    for(int i = 0; i < TOTAL_PAGES; i++)
    {
        chapter1BG[i].free();
    }
    dialogBox.free();
	menuBar.free();

	//free the script textures
    for(int j = 0; j < TOTAL_PAGES; j++)
    {
        for(int i=0;i<TOTAL_SCRIPTS;i++)
        {
            scriptTexture[j][i].free();
        }
    }

}

void chapter::setFileNames()
{
    bgFileName[0] = "images/signflying800x600.png";
    bgFileName[1] = "images/parkbench.png";
    bgFileName[2] = "images/bluewave.png";
    bgFileName[3] = "images/please.png";
    bgFileName[4] = "images/biblioteca.png";
    bgFileName[5] = "images/America2.png";
    bgFileName[6] = "images/darknight.png";
    bgFileName[7] = "images/forest.png";
}

bool chapter::setChapterTextures(SDL_Renderer* renderer){
    bool success = true;
    setFileNames();
    for(int i = 0; i<TOTAL_PAGES;i++)
    {
        success = chapter1BG[i].loadFromFile( bgFileName[i],renderer );
    }
       //load dialog box image
	success = dialogBox.loadFromFile( "images/dialogbox1.png",renderer );
	success = menuBar.loadFromFile("images/menuBar.png",renderer);
    //set dialog box alpha (about 75% opaque @ 192)
    dialogBox.setAlpha(255);
    return success;
}

void chapter::loadLineText(SDL_Renderer* renderer)
{
    lineText.str( "" );
    lineText << "" << currentScript + 1;
    //set text color to black
    SDL_Color textColor = {0,0,0};

    if( !curLineTextTexture.loadFromRenderedText( lineText.str().c_str(), textColor,font,renderer ) )
    {
        printf( "\n Unable to render current line text to texture!\n" );
    }
}

void chapter::loadPageText(SDL_Renderer* renderer)
{
    pageText.str( "" );
    pageText << "" << currentPage + 1;
    //set text color to black
    SDL_Color textColor = {0,0,0};

    if( !curPageTextTexture.loadFromRenderedText( pageText.str().c_str(), textColor,font,renderer ) )
    {
        printf( "\n Unable to render current page text to texture!\n" );
    }
}

bool chapter::setScriptTextures(SDL_Renderer* renderer){
    bool success = true;
    //Render text
    SDL_Color textColor;
    //make sure loading current strings
    for(int j=0;j<TOTAL_PAGES;j++)
    {
        textColor = {55,55,55};
        if(j==0)//was testing page 1 dialog color here
        {
            //green
            //textColor = {0,255,0};

            //pink
            //textColor = {255,0,255};
        }
        if(j==3 || j==4 || j==6)//pages 4,5, and 7 have dialog color white.
        {
            //white
            textColor = {255,255,255};
        }
        if(j==5)//page 6 has red dialog
        {
            //red
            textColor = {255,0,0};
        }
        for(int i=0;i<TOTAL_SCRIPTS;i++){

            if( !scriptTexture[j][i].loadFromRenderedText( scriptString[j][i].str().c_str(), textColor,font, renderer ) )
            {
                printf( "Failed to render text texture!\n" );
                success = false;
            }
        }
    }
    return success;
}

void chapter::testSaveVariables()
{
    std::cout << "\n currentChapter: " << std::to_string( currentChapter );
    std::cout << "\n currentPage: " << std::to_string( currentPage );
    std::cout << "\n currentScript: " << std::to_string( currentScript );
    std::cout << "\n chapter1Complete: " << std::to_string(chapter1Complete);
}

void chapter::loadFont()
{
    //load the font
	font = TTF_OpenFont( "fonts/Tapeworm.ttf", 16 );
}

int chapter::progress(SDL_Renderer* renderer,int gameState)
{
    if(currentPage==TOTAL_PAGES-1 && currentScript==TOTAL_SCRIPTS-1){
        completeChapter(renderer);
        gameState=2;
        chapter1Timer.stop();
    }
    else if (currentScript<TOTAL_SCRIPTS-1)
    {
        scriptIncrement();
        chapter1Timer.restart();
    }
    else if(currentPage<TOTAL_PAGES-1){
        pageIncrement();
        chapter1Timer.restart();
    }
    return gameState;
}

int chapter::progress2(SDL_Renderer* renderer,int gameState)
{
    if(currentScript<TOTAL_SCRIPTS-1)
    {
        scriptIncrement();
        chapter1Timer.restart();
    }
    else
    {
        if(currentPage<TOTAL_PAGES-1)
        {
            pageIncrement();
            chapter1Timer.restart();
        }
        else
        {
            gameState = 2;
            completeChapter(renderer);
        }
    }
    return gameState;
}

void chapter::handleDialogVisability()
{
    if(!hideDialogBox && !hideDialogAndBox)
    {
        hideDialogBox = true;
        hideDialogAndBox = false;
    }
    else if(hideDialogBox && !hideDialogAndBox)
    {
        hideDialogAndBox = true;
        hideDialogBox = true;
    }else if(hideDialogBox && hideDialogAndBox)
    {
        hideDialogAndBox=false;
        hideDialogBox=false;
    }
    printf("\n h pressed \n");
    std::cout << "hideDialogBox: " << hideDialogBox;
}

void chapter::handleDialogRendering(SDL_Renderer* renderer)
{
    if(hideDialogBox == false)
    {
        dialogBox.render(0,400,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    }
    if(hideDialogAndBox==false){
        for(int i = 0; i<TOTAL_SCRIPTS;i++)
        {
            //render script lines
            if(i <= currentScript)
            {
                scriptTexture[currentPage][i].render(20,420 + (i*20),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
            }
        }
    }
}

void chapter::handleBackPagePress()
{
    if(currentPage>0)
    {
        currentPage--;
        currentScript=7;
    }
}

void chapter::setButtonNames()
{
    for(int i = 0; i < TOTAL_CHAPTER_BUTTONS; i++)
    {
        buttons[i].setChapterButtonName(i);
    }
}

void chapter::freeButtons()
{
    for(int i = 0; i<TOTAL_CHAPTER_BUTTONS;i++)
    {
        buttons[i].buttonTexture.free();
    }
}

void chapter::loadSavedVariables(Sint32 data0, Sint32 data1,Sint32 data2,Sint32 data3)
{
    currentChapter=data0;
    currentPage=data1;
    currentScript=data2;
    chapter1Complete=data3;
}

void chapter::handleRendering(SDL_Renderer* renderer)
{
    for(int j = 0; j<TOTAL_PAGES;j++)
    {
        //render background & dialog box before script lines
        renderBackgrounds(renderer,j);
        //these two lines may not actually be necessary.
        buttons[0].buttonTexture.render(buttons[0].getPositionX(),buttons[0].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        buttons[1].buttonTexture.render(buttons[1].getPositionX(),buttons[1].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);

        if(autoText)
        {
            //render auto texture on button (hightlights auto text on in menubar)
            buttons[2].buttonTexture.render(buttons[2].getPositionX(),buttons[2].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        }
        else
        {
            //render auto texture off button (hightlights auto text off in menubar)
            buttons[3].buttonTexture.render(buttons[3].getPositionX(),buttons[3].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        }
        if(autoTextSpeed==0)
        {
            //highlights text speed 1
            buttons[4].buttonTexture.render(buttons[4].getPositionX(),buttons[4].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        }
        else if(autoTextSpeed==1)
        {
            //highlights text speed 2
            buttons[5].buttonTexture.render(buttons[5].getPositionX(),buttons[5].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        }
        else if(autoTextSpeed==2)
        {
            //highlights text speed 3
            buttons[6].buttonTexture.render(buttons[6].getPositionX(),buttons[6].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        }
        menuBar.render(0,350,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        //load page number into menubar
        loadPageText(renderer);
        curPageTextTexture.render(140,352,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        //load line number into menubar
        loadLineText(renderer);
        curLineTextTexture.render(130,374,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        //if the state of the dialog box visibility gets changed, this handles the rendering or not rendering.
        handleDialogRendering(renderer);
    }
    //render save & exit button
    buttons[7].buttonTexture.render(buttons[7].getPositionX(),buttons[7].getPositionY(),NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
}

bool chapter::setChapterButtonTextures(SDL_Renderer* renderer, bool success)
{

    for( int i = 0; i < TOTAL_CHAPTER_BUTTONS; ++i )
    {
        std::stringstream ss;
        ss << "images/buttons/" << buttons[i].buttonName << ".png";
        std::string str = ss.str();
        success = buttons[i].buttonTexture.loadFromFile( str,renderer );
        //buttons[ i ].setPosition( ((i*160)-80), SCREEN_HEIGHT - 140 );
    }
    //backpage and backline button positions
    buttons[0].setPosition(161,350);
    buttons[1].setPosition(195,350);
    //autoTextOn
    buttons[2].setPosition(270,385);
    buttons[3].setPosition(290,385);
    //autospeed
    buttons[4].setPosition(240,365);
    buttons[5].setPosition(266,365);
    buttons[6].setPosition(292,365);
    //save and exit
    buttons[7].setPosition(600,20);
    return success;
}

void chapter::handleBackLinePress()
{
    if(currentScript>0)
    {
       currentScript-=2;
    }
    if(currentScript>=6)
    {
        currentPage--;
        currentScript=6;
    }
}

void chapter::renderBackgrounds(SDL_Renderer* renderer,int j)
{
    switch(currentPage %TOTAL_PAGES)
    {
    case 0:
        chapter1BG[0].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
    case 1:
        chapter1BG[1].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
    case 2:
        chapter1BG[2].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
    case 3:
        chapter1BG[3].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
    case 4:
        chapter1BG[4].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
    case 5:
        chapter1BG[5].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
    case 6:
        chapter1BG[6].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
    case 7:
        chapter1BG[7].render(0,0,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
    }
}

void chapter::setAutoScript()
{
    if(chapter1Timer.getTicks()/1000 > 1 && autoTextSpeed==0 && autoText)
    {//implement timer auto script option.
        if(currentScript<TOTAL_SCRIPTS-1)
        {
            scriptIncrement();
            chapter1Timer.restart();
            //printf("\n \n timer tick");
            //testSaveVariables();
        }
        if(currentScript == TOTAL_SCRIPTS-1)
        {
            chapter1Timer.stop();
        }
    }
    else if(chapter1Timer.getTicks()/750 > 1 && autoTextSpeed==1 && autoText)
    {//implement timer auto script option.
        if(currentScript<TOTAL_SCRIPTS-1)
        {
            scriptIncrement();
            chapter1Timer.restart();
            //printf("\n \n timer tick");
            //testSaveVariables();
        }
        if(currentScript == TOTAL_SCRIPTS-1)
        {
            chapter1Timer.stop();
        }
    }
    else if(chapter1Timer.getTicks()/500 > 1 && autoTextSpeed==2 && autoText)
    {//implement timer auto script option.
        if(currentScript<TOTAL_SCRIPTS-1)
        {
            scriptIncrement();
            chapter1Timer.restart();
            //printf("\n \n timer tick");
            //testSaveVariables();
        }
        if(currentScript == TOTAL_SCRIPTS-1)
        {
            chapter1Timer.stop();
        }
    }
}

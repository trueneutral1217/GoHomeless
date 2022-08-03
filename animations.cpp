#include "animations.h"

animations::animations()
{
    aniFrame=0;
    aniFrame2=0;
    aniCountUp=true;
}

animations::~animations()
{

}

bool animations::setAnimationTextures(SDL_Renderer* renderer)
{
    bool success = true;

    //load tao animation images
    for(int i = 0; i<TAO_ANIMATION_FRAMES;i++)
    {
        int a = i+1;
        std::stringstream ss;
        ss << "images/animations/tao/tao" << a << ".png";
        std::string str = ss.str();
        success = tao[i].loadFromFile(str,renderer);
    }
    for(int i = 0; i<TOASTER_ANIMATION_FRAMES;i++)
    {
        int a = i;
        std::stringstream ss;
        ss << "images/animations/toaster/toaster" << a << ".png";
        std::string str = ss.str();
        success = toaster[i].loadFromFile(str,renderer);
    }

    return success;
}

void animations::freeAnimationTextures()
{
        //free the tao animation textures
    for(int i=0;i<TAO_ANIMATION_FRAMES;i++)
    {
        tao[i].free();
    }
    for(int i=0;i<TOASTER_ANIMATION_FRAMES;i++)
    {
        toaster[i].free();
    }
}

void animations::renderTao(SDL_Renderer* renderer)
{
    switch(aniFrame){
        case 0:tao[0].render(750,300,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 1:tao[1].render(750,300,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 2:tao[2].render(750,300,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 3:tao[3].render(750,300,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 4:tao[4].render(750,300,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 5:tao[5].render(750,300,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 6:tao[6].render(750,300,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
        case 7:tao[7].render(750,300,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
    break;
    }
}

void animations::renderToaster(SDL_Renderer* renderer)
{
    switch(aniFrame2)
    {
    case 0:toaster[0].render(50,400,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
    case 1:toaster[1].render(50,400,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
    case 2:toaster[2].render(50,400,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
    case 3:toaster[3].render(50,400,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
    case 4:toaster[4].render(50,400,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
    case 5:toaster[5].render(50,400,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
    case 6:toaster[6].render(50,400,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
    case 7:toaster[7].render(50,400,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
        break;
    }
}


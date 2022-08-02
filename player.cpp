#include "player.h"

player::player()
{
    playerX = playerY = pVelX = pVelY = 0;
}
player::~player()
{
    playerTexture.free();
}

void player::handleEvent(SDL_Event& e)
{
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
        case SDLK_w:
            pVelY -= PLAYER_VEL;
            break;
        case SDLK_s:
            pVelY += PLAYER_VEL;
            break;
        case SDLK_a:
            pVelX -= PLAYER_VEL;
            break;
        case SDLK_d:
            pVelX += PLAYER_VEL;
            break;
        }
    }
    else if(e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
        case SDLK_w:
            pVelY += PLAYER_VEL;
            break;
        case SDLK_s:
            pVelY -= PLAYER_VEL;
            break;
        case SDLK_a:
            pVelX += PLAYER_VEL;
            break;
        case SDLK_d:
            pVelX -= PLAYER_VEL;
            break;
        }
    }
}


void player::move()
{
    playerX += pVelX;
    playerY += pVelY;
    if((playerX < 0) || (playerX + PLAYER_WIDTH > SCREEN_WIDTH))
    {
        playerX -= pVelX;
    }
    if((playerY < 0) || (playerY + PLAYER_HEIGHT > SCREEN_HEIGHT))
    {
        playerY -= pVelY;
    }
}

void player::loadPlayer(SDL_Renderer* renderer)
{
    playerTexture.loadFromFile( "images/sprites/tree1.png",renderer );
}

void player::render(SDL_Renderer* renderer)
{
    playerTexture.render(playerX,playerY,NULL,0.0,NULL,SDL_FLIP_NONE,renderer);
}

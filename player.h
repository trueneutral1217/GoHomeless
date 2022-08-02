#ifndef PLAYER_H
#define PLAYER_H

#include "texture.h"

class player
{
    public:

        player();
        ~player();
        static const int PLAYER_WIDTH = 40;
        static const int PLAYER_HEIGHT = 80;
        static const int PLAYER_VEL = 10;

        Texture playerTexture;

        void loadPlayer(SDL_Renderer* renderer);
        void handleEvent(SDL_Event& e);
        void move();
        void render(SDL_Renderer* renderer);

    private:

        int playerX,playerY;
        int pVelX,pVelY;

};
#endif // PLAYER_H


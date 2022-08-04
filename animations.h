#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "Texture.h"
#include "timer.h"
const int TAO_ANIMATION_FRAMES = 8;
const int TOASTER_ANIMATION_FRAMES = 8;


class animations
{
    public:
        //constructor
        animations();
        //destructor
        ~animations();

        //timer for tao animation
        timer animationTimer;

        //timer for toaster the robot's animation
        timer animationTimer2;

        bool aniCountUp;
        int aniFrame,aniFrame2;

        //animation textures
        Texture tao[TAO_ANIMATION_FRAMES];
        Texture toaster[TOASTER_ANIMATION_FRAMES];

        bool setAnimationTextures(SDL_Renderer* renderer);
        void freeAnimationTextures();

        void renderTao(SDL_Renderer* renderer);
        void renderToaster(SDL_Renderer* renderer);
        void cycleAnimations();
        void oscillateCount();

        void taoAnimationProgress();
        void toasterAnimationProgress();

    private:

};

#endif // ANIMATIONS_H

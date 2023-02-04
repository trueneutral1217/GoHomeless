#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "Texture.h"
#include "timer.h"
const int TAO_ANIMATION_FRAMES = 8;
const int TOASTER_ANIMATION_FRAMES = 8;
//I've made a second toaster, I'm testing out walking animation.
const int TOASTER2_ANIMATION_FRAMES = 3;


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

        timer animationTimer3;

        bool aniCountUp;
        int aniFrame,aniFrame2,aniFrame3;

        //animation textures
        Texture tao[TAO_ANIMATION_FRAMES];
        Texture toaster[TOASTER_ANIMATION_FRAMES];
        Texture toaster2[TOASTER2_ANIMATION_FRAMES];

        bool setAnimationTextures(SDL_Renderer* renderer);
        void freeAnimationTextures();

        void renderTao(SDL_Renderer* renderer);
        void renderToaster(SDL_Renderer* renderer);
        void renderToaster2(SDL_Renderer* renderer);
        void cycleAnimations();
        void oscillateCount();

        void taoAnimationProgress();
        void toasterAnimationProgress();
        void toaster2AnimationProgress();

    private:

};

#endif // ANIMATIONS_H

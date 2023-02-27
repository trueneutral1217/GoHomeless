#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "Texture.h"
#include "timer.h"


const int TAO_ANIMATION_FRAMES = 8;
const int TOASTER_ANIMATION_FRAMES = 8;
//I've made a second toaster, I'm testing out walking animation.
const int TOASTER2_ANIMATION_FRAMES = 3;

const int BLACKSTAR_ANIMATION_FRAMES=9;


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

        timer animationTimer4;
        timer animationTimer5;
        timer animationTimer6;
        timer animationTimer7;

        bool aniCountUp;

        //tracker for the frame of the animation being used
        int aniFrame,aniFrame2,aniFrame3;

        //aniFrame4, 5,6,and 7 are for the blackstar animations
        int aniFrame4,aniFrame5,aniFrame6,aniFrame7;

        //creating 4 blackstar animations with random x/y coords to be displayed
        int bsX1,bsX2,bsX3,bsX4,bsY1,bsY2,bsY3,bsY4;

        //animation textures
        Texture tao[TAO_ANIMATION_FRAMES];
        Texture toaster[TOASTER_ANIMATION_FRAMES];
        Texture toaster2[TOASTER2_ANIMATION_FRAMES];
        Texture blackstar[BLACKSTAR_ANIMATION_FRAMES];

        bool setAnimationTextures(SDL_Renderer* renderer);
        void freeAnimationTextures();

        void renderTao(SDL_Renderer* renderer);
        void renderToaster(SDL_Renderer* renderer);
        void renderToaster2(SDL_Renderer* renderer);
        void renderBlackstar(SDL_Renderer* renderer);

        void cycleAnimations();
        void oscillateCount();

        void taoAnimationProgress();
        void toasterAnimationProgress();
        void toaster2AnimationProgress();
        void blackstarAnimationProgress();

    private:

};

#endif // ANIMATIONS_H

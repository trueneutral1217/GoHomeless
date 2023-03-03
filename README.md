# GoHomeless

This is the current version of Go Homeless!  The local repo file directory was different from the github repo, 
so if you want older info about this project, check go homelessbaddirectories.  I'll delete that repo eventually.

7/21/22 - removed FPS from main screen, stopped running if statements for media loading, removed some artifacts,
and generally tried to reduce the size (in lines) of main.cpp.

7/25/22 - I've been making and adding new art to the game, as well as implementing some of the important parts for 
the visual novel portion of this game.  chapter 1 is about done, I'd still like to make a new song for chapter 1
instead of using something I've used in one of my previous projects.  A lot of my artwork has been used in other
projects.  If I didn't make it, it would have been from some cc0 location.  I may remove some assets just to keep
the size of the game down.  Right now the game saves and loads, chapters are going to be fairly easy to add with
the framework that I've implemented.  I plan to have stage 1 open up after chapter one is complete.  chapter 1 
could still use user interface improvements.  I've been planning it out, but I only have so much time that I
can commit to this project in any given day.  I'll be making a release version fairly soon just meant to be a 
playable demo.  I was going to send it to my mommy.  besides the song I'd still like to make artwork for the credits 
and options screens, as well as possibly implement those UI improvements that I've been thinking about.  

8/1/22 - finally figured out how to make the release build work locally, so I uploaded a rar with the go homeless folder and an executable and cleaned out some files that aren't yet being used by the release (may never be used).  from there I added a player class, currently using a tree pic as a stand in for my player that only shows up in gamestate == 6, aka stage 1.  also added an animated robot waving at the user to the credit screen. :-)

8/5/22 - a lot of cosmetic updates for the code, moved a lot of stuff out to chapter class, animations class, created player class,
created stage class.  stage 1 is gameState 6.  thinking about doing a tilesheet for stage 1.  chapter two dialog is no longer just place
holders.  chapter one's title is Origins, chapter 2 title is Thoughts.  oh, a lot of changes to button class.  main.cpp doesn't look like it did a week ago.
I don't plan to stop.  I'll keep updating this game until it freaking sparkles.  I love you.

2/3/23 - added a couple bg images for gamestate 7 / chapter 2.  added a button for chapter 2 to the load game screen when chapter1Complete is true.
did some testing, but probably could use more in depth testing, it was mainly just a quick & dirty update to make chapter2 accessible & show the
new backgrounds.  despite the fact that it's been about 8 months, the code wasn't so convoluted that I couldn't get it done in about an hour (the programming,
not the art).  cheers.

2/16/23 - Parallax added to chapter 2 page 7, haven't done much debugging, but it seemed to work fine on my side. added the art files 
associated with that page's parallax effect.  I'm probably going to do parallax for ch 2 page 8 as well.  I love you.

2/17/23 - added parallax images to chapter 2 page 8, added another layer to the parallax effect, anterior mid.  future naming of 
layers will include anterior & posterior if I add more than 3 layers.

2/18/23 - debug day, chapter backgrounds and scripts were having some issues, they look to be resolved now.
noticed that autoscript is only working on chapter 1, so I'll begin working on that at a later date.

2/19/23 - autoscript wasn't working for chapter 2, so I updated the fuction that controls chapter 1's autoscript.
Now, chapter1Timer has been changed to chapterTimer, the setAutoScript function now works for chapter 1 and chapter two, 
also it should work for subsequent chapters.  I guess I'll find out when I implement chapter 3.  also added a couple functions for
the car image at the end of chapter two, it's not actually a background, and doesn't need to really be parallax.  I feel like
it looks a lot better.

2/21/23 - audio is now set up to play different songs for the pregame user interface, chapter1, and chapter 2.  still having a weird error when I close
program, so I'll be trying to figure that one out, I'm guessing I'm not freeing up a texture or something.  other than that, I can't think of
much else to do before release of demo 2 besides maybe adding an animation or two to some of the middle pages of chapter 2 since the art on those
pages is a little meh.

2/27/23 - created images and added animation to page 5 of chapter 2.  Did the same for page 6.

2/28/23 - bug fixes, chapter 3 framework up: placeholder background images, music, placeholder script, chapter 3 button.

3/1/23 - no robo verification added to start of chapter 3.

3/2/23 - chapter 3 dialog is written.  title?  probably going to go with 'Logic over Common Sense'.

3/3/23 - voice acting recorded and added to chapters 1 through 3.  haven't created a voice toggle yet, but
I probably will soon.
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
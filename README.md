# Gem-Jive
This project is a Candy Crush Clone game developed in C++ using OpenGL as part of a Programming Fundamentals(PF) course. It brings a colorful and interactive gem-matching experience with several engaging features.
## Features
### Login System
- Players enter their name at the start, creating a personalized experience.
### Classic Match-3 Gameplay
- Players can swap adjacent gems using the mouse. Matching a minimum of three identical gems forms a valid chain. Longer chains yield higher rewards, promoting strategic play.
### Dual Gameplay Modes
- Normal Mode: Allows unrestricted play without time constraints.
- Time Trial Mode: Challenges the player to achieve the highest possible score within a limited time frame.
### Progressive Levels
- The game includes a level-based system where new levels are unlocked based on the player’s cumulative score, increasing in complexity as the game progresses.
### Hint System
- An integrated hint feature assists players by suggesting a valid move when no immediate chain is visible, helping maintain gameplay flow.
### State Control (Play/Pause/Resume)
- The game  supports play, pause, and resume functionality, allowing users to manage their gameplay sessions effectively.
### Menus
- Several menus including a comprehensive instructions menu outlining core mechanics and controls.
![Game UI](https://github.com/ImamaSarwar/Gem-Jive_Candy-Crush-Clone-Game/raw/f29c5428e1ea60fd3f08874c81d9bce9bbb90875/Game%20UI.png)
## Getting Started
Follow these steps to build and run the game on a Linux system
### Install Required Libraries 
- sudo apt-get install make freeglut3-dev glew-utils libglew-dev libfreeimage-dev
### Compile the Game
- g++ -o game util.o game.o \-L/usr/X11R6/lib -L/sw/lib -L/usr/sww/lib -L/usr/sww/bin -L/usr/sww/pkg/Mesa/lib \-lglut -lGLU -lGL -lX11 -lfreeimage -pthread
- make
- ./game
## Acknowledgements
- Project Partner:[Hiyam Rehan](https://github.com/hiyamrehan)
### Enjoy!

# Gem-Jive
## Getting Started
Follow these steps to build and run the game on a Linux system
### Install Required Libraries 
- sudo apt-get install make freeglut3-dev glew-utils libglew-dev libfreeimage-dev
### Compile the Game
- g++ -o game util.o game.o \-L/usr/X11R6/lib -L/sw/lib -L/usr/sww/lib -L/usr/sww/bin -L/usr/sww/pkg/Mesa/lib \-lglut -lGLU -lGL -lX11 -lfreeimage -pthread
- make
- ./game
## Acknowledgements
- Project Partner: ![Hiyam Rehan](https://github.com/hiyamrehan)
### Enjoy!

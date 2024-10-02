# Woolly Breakout (ongoing...)

An original 2D game made with C++ and the SDL2 library used as a way to learn about CMake, and C++ shipping as a whole, and to work collaboratively with a few classmates. 


## How to run

### Linux (Examples with debian distributions)

First, open the terminal and install any C++ compiler, CMake and the SDL2 library if needed. Example as follows:

```bash
  sudo apt install cmake libsdl2-dev g++ 
```
Then, you can clone the repository with git on any given folder.

```
git clone https://github.com/DanielRamirez404/Wolly-Breakout.git
```

After that, you'll have downloaded the whole game's code, so you can go to the src folder and build the project on a new build file, like this:

```
...Woolly-Breakout/src$ mkdir build
...Woolly-Breakout/src$ cd build
...Woolly-Breakout/src/build$ cmake ...
...Woolly-Breakout/src/build$ make
```

Finally, a brand-new executable file should have been added to your build folder, so you can run it to start the game.

```
...Woolly-Breakout/src/build$ ./WoollyBreakout
```

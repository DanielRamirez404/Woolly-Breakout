# Woolly Breakout (ongoing...)

An original 2D game made with ```C++``` and the ```SDL2``` library used as a way to learn about ```CMake```, and ```C++``` shipping as a whole, and to work collaboratively with a few classmates.

## Requirements

To successfully run the app, you should have both ```Make``` and ```CMake``` installed on your device (as well as any ```C++``` compiler) so that you can build the executable file. You should also have the ```SDL2``` library somewhere on your computer, but don't worry, it's way simpler than it sounds, here's a breakdown on what you should do, depending on your operating system:

### Linux

On linux it's pretty easy to install all of the necessary tools, you can open the command line and then use your distribution's package manager to do so. For instance, using debian-based distributions as an example:

```
sudo apt install cmake libsdl2-dev g++
```

Notice how this will install ```CMake```, the ```SDL2``` library and the ```g++``` compiler, respectively.

> [!NOTE] 
> You should have ```Make``` installed by default, but if that is not your case, you can always add make as an argument. 

> _Source: [Using SDL2 with CMake][1]_ 

### Windows

On Windows, it's a bit harder and more time-consuming, but if you follow the steps throroughly, you'll be able to run the software in no time!

First, you can easily install ```CMake``` from [its official website][2]. And similarly ```Make``` from [SourceForge's website][3]

> [!NOTE]
> You can watch the walkthrough of these two installations on the following links: [CMake installation's video][4] and [Make installation's video][5]

> [!IMPORTANT]
> Don't forget to add both installations' directories to the PATH environment variable, so that you can access the  ```make``` and ```cmake``` commands from the command prompt.

Now, you can download the ```SDL2``` library by going into its [official website][6] and clicking on the releases link.

> [!NOTE]
> You can also just use the direct link of current version at redaction time: [SDL2 2.30.8][7]

You must download the ```SDL2-devel-(version)-VC.zip``` file. If you wish no aditional settings, you can extract it at the ```C:\``` directory and rename the extracted folder as ```SDL2```.

> [!WARNING]
> Otherwise (or if you've installed Windows on another disk) you should pay attention to the **How to Run**'s **Configuring CMake** section.

## How to run

If you don't have ```git``` installed, you can download this project's code as a ```zip``` file, as an option that pops up after clicking the big green button. Unzip it on any given folder.

If you do have ```git```, however, just clone the repository as follows:

```
git clone https://github.com/DanielRamirez404/Wolly-Breakout.git
```

After that, you'll have downloaded all of the game's files. It's time to run it!

### Linux

Go to the ```src``` folder and build the project on a new ```build``` folder, like this:

```
...Woolly-Breakout/src$ mkdir build
...Woolly-Breakout/src$ cd build
...Woolly-Breakout/src/build$ cmake ..
...Woolly-Breakout/src/build$ make
```

Finally, a brand-new executable file should have been added to your ```build``` folder, so you can run it to start the game.

```
...Woolly-Breakout/src/build$ ./WoollyBreakout
```

> [!TIP]
> If you have to rebuild the project, you can just clean the ```build``` folder with the ```rm * -r``` command and use the ```cmake ..``` and ```make``` commands.

### Windows

Similarly to Linux, go to the ```src``` folder and create a new ```build``` folder.

Before going inside, however, if you didn't rename your ```SDL2-version``` folder, didn't use the same location as specified, or if you've installed Windows on another disk, go to the CMakeListsFile and change all instances of the ```C:\\SDL2``` directory as that of the real address of your ```SDL2``` folder.

> [!IMPORTANT]
> Notice that you should escape the backslash ```\``` character, so just write it twice.

Open the command promt on the ```build``` folder and run the following commands:

```
cmake ..
cmake --build . --config Release
```

It should've created some ```Visual Studio``` solution files and then an executable inside a ```Realase``` folder, but you cannot run it just yet!

Before running, make sure to copy the ```SDL2.dll``` file to the same location of your executable file. You'll find it inside your ```SDL2``` folder, on the ```lib``` one and then, depending on the architecture of your system, on the ```x64``` or ```x86``` folder.

Finally, run and enjoy!

<!-- Links -->

<!-- Using SDL2 with CMake Tutorial -->
[1]: https://trenki2.github.io/blog/2017/06/02/using-sdl2-with-cmake/

<!-- CMake's Official Website -->
[2]: https://cmake.org/

<!-- Make Installation on Sourceforge -->
[3]: http://gnuwin32.sourceforge.net/downlinks/make.php

<!-- CMake Installation Video--> 
[4]: https://www.youtube.com/watch?v=8_X5Iq9niDE

<!-- Make Installation Video -->
[5]: https://www.youtube.com/watch?v=8bqH8AOPT3U 

<!-- SDL's official Website -->
[6]: https://www.libsdl.org/

<!-- Latest SDL2 Version Link -->
[7]: https://github.com/libsdl-org/SDL/releases/tag/release-2.30.8

# This is a game project name "MeowXMonster" a 3D pixel art game

## Author List sorted by student ID (ascending)
- [1] [Chawalya Mattayanpol]
- [2] [Ko-Kwan Mongkholtham]
- [3] [Pochara Wiangkham]
- [4] [Ravinan Roraratyanon]
- [5] [Thanyanit Poothong]
- [6] [Wit Yimrattanabaworn]

#### Project Structure (updated 26/10/2023): 
```
╰─ tree                                                                                                                                                                                      ─╯
.
├── App.c
├── CMakeLists.txt
├── README.md
├── assets
│   ├── images
│   │   ├── avatar
│   │   │   ├── Bomb
│   │   │   ├── Laika
│   │   │   └── MegaChonker
│   │   ├── background
│   │   └── monster
│   │       ├── Jelly
│   │       ├── Muscle
│   │       └── Ufo
│   └── text
├── include
│   ├── raylib.h
│   ├── raymath.h
│   └── rlgl.h
├── lib
│   └── libraylib.a
└── src
    ├── asm
    │   ├── cal.o
    │   └── cal.s
    └── c
        ├── character
        │   ├── character.c
        │   └── character.h
        ├── constant
        │   ├── game_constant.h
        │   ├── game_data.h
        │   └── game_function.h
        ├── game.c
        ├── gameover.c
        └── startgame.c

```
<b>NOTE: this project cannot be compiled from macOS and Window</b>

# How to compile the game on macOS
##### 1. Install the dependencies:
   + [raylib](https://github.com/raysan5/raylib)

##### 2. Navigate to Project:
`cd` to the root directory of the project
  
##### 3. Compile the Game:
Run the following command:
`clang App.c src/c/game.c src/c/startgame.c src/c/character/character.c -L lib/ -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL lib/libraylib.a -o compiled-raylib-game`
- The compiled game will be in the root directory of the project named `compiled-raylib-game`
 #### 4. Run the compiled game by running the following command:
`./compiled-raylib-game`

# How to compile the game on Windows
##### 1. Install the dependencies:
   + [MinGW](https://sourceforge.net/projects/mingw-w64/)
   + [raylib](https://github.com/raysan5/raylib)
  
##### 2. Navigate to Project:
   `cd` to the root directory of the project

##### 3. Compile the Game:
Run the following command:
`gcc -o compiled-raylib-game App.c src/c/game.c src/c/startgame.c src/c/character/character.c -Ipath/to/raylib/include -Lpath/to/raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm`
- <b>NOTE:</b> Replace `path/to/raylib/include` with the actual path to the raylib include folder and `path/to/raylib/lib` with the path to the raylib library folder. Ensure the paths are correct to avoid compilation errors.
- After successful compilation, you'll find the game executable named `compiled-raylib-game.exe` in the root directory of the project.

##### 3. Compile the Game:
Run the following command:
`gcc -o compiled-raylib-game App.c src/c/game.c -Ipath/to/raylib/include -Lpath/to/raylib/lib -lraylib -lopengl32 -lgdi32 -lwinmm`
- <b>NOTE:</b> Replace `path/to/raylib/include` with the path to the raylib include folder and `path/to/raylib/lib` with the path to the raylib library folder.  
- The compiled game will be in the root directory of the project named `compiled-raylib-game.exe`
#### 4. Run the compiled game by running the following command:
`compiled-raylib-game`
   

# How to compile the game on Raspberry Pi:
##### 1. Navigate to Project:
`cd` to the directory of the project.

##### 2. Create build directory:
First, compile `mkdir build`:

`cd build`
`cmake ..`

##### 3. Export additional command for Rapsberry pi:
`export MESA_GLSL_VERSION_OVERRIDE=330`
`export MESA_GL_VERSION_OVERRIDE=3.3`
`make all`

##### 4. Run the compiled game by running the following command:
`./MeowXMonster`


# How to play

- Select your cat character and place it on one of the yard blocks to defend your house from monsters that are coming from the right of the screen.
- Once monster can walk through the yard, it is game over.
- There are maximum 50 monsters, if you can kill all of them and survive, you win.
- Reminder that each time you select a character, it costs money.
- Laika, the tuxido cat that costs 100.- shoots spits in sequence to attack monsters.
- MegaChonker, the round orange cat that costs 200.-, have high HP which can block monsters for a period of time.
- Bomb cat, the black cat that costs 400.-, will explode and kill monster nearby immediately.


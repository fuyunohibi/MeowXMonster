# This is a game project name "MeowXMonster" a 3D pixel art game

## Author List sorted by student ID (ascending)
- [1] [Chawalya Mattayanpol]
- [2] [Ko-Kwan Mongkholtham]
- [3] [Pochara Wiangkham]
- [4] [Ravinan Roraratyanon]
- [5] [Thanyanit Poothong]
- [6] [Wit Yimrattanabaworn]

#### Project Structure (updated 05/10/2023): 
-  By Captain
```
╰─ tree                                                                                                                                                                                      ─╯
.
├── App.c
├── Makefile
├── README.md
├── assets
│   ├── sounds
│   └── textures
├── include
│   ├── raylib.h
│   ├── raymath.h
│   └── rlgl.h
├── lib
│   └── libraylib.a
└── src
    ├── asm
    │   └── game.asm
    └── c
        └── game.c

9 directories, 9 files
```

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
##### 1. Install Dependencies:
First, compile and install `raylib`:

`sudo apt-get update`
`sudo apt-get install build-essential git`
`git clone https://github.com/raysan5/raylib.git raylib-repo`
`cd raylib-repo/src`
`make PLATFORM=PLATFORM_RPI`
`sudo make install RAYLIB_LIBTYPE=SHARED RAYLIB_PATH=../..`
- <b>NOTE:</b> In the command, `RAYLIB_PATH=../..` sets the installation path relative to the src directory. Only adjust this if you're sure about the installation path. For example, if you want to install in a directory called my_directory one level above src, you'd change it to `RAYLIB_PATH=../my_directory`. For most users, the original `../..` should work just fine.

##### 2. Navigate to Project:
`cd` to the root directory of the project.

##### 3. Compile the Game:
`gcc -o compiled-raylib-game App.c src/c/game.c src/c/character/character.c -I/path/to/raylib/include -L/path/to/raylib/lib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11`

- <b>NOTE:</b> Replace `/path/to/raylib/include` with the path to the raylib include folder and `/path/to/raylib/lib` with the path to the raylib library folder.
- The compiled game will be in the root directory of the project named `compiled-raylib-game`

##### 4. Run the compiled game by running the following command:
`./compiled-raylib-game`


# How to play


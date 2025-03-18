# Tic-Tac-Toe Game

This is a simple Tic-Tac-Toe game implemented in C. The game supports two modes: playing against the computer or playing with a friend over a local network.

## Features

- Play against the computer.
- Play with a friend over a local network.
- Randomized starting player.
- Simple command-line interface.

## Prerequisites

- A C compiler (e.g., GCC for Linux, MinGW for Windows)
- Make (for building the project on Linux)
- MinGW and Make for Windows (optional, for building the project using Make)

## Building the Project

### On Linux

To build the project, run the following command in the terminal:

```sh
make
```

This will compile the source code and generate an executable named `tic_tac_toe`.

### On Windows

#### Using MinGW and Make

1. Install [MinGW](http://www.mingw.org/) and [Make for Windows](http://gnuwin32.sourceforge.net/packages/make.htm).
2. Open the MinGW shell and navigate to the project directory.
3. Run the following command:

```sh
mingw32-make
```

This will compile the source code and generate an executable named `tic_tac_toe.exe`.

#### Using Visual Studio

1. Open the Developer Command Prompt for Visual Studio.
2. Navigate to the project directory.
3. Run the following command:

```sh
cl /EHsc tic_tac_toe.c /Fe:tic_tac_toe.exe
```

This will compile the source code and generate an executable named `tic_tac_toe.exe`.

## Running the Game

### Playing against the Computer

To play against the computer, run the following command:

#### On Linux

```sh
./tic_tac_toe
```

#### On Windows

```sh
tic_tac_toe.exe
```

Then, select option `1` to play against the computer.

### Playing with a Friend

To play with a friend over a local network, follow these steps:

1. One player should host the game by running:

#### On Linux

```sh
./tic_tac_toe
```

#### On Windows

```sh
tic_tac_toe.exe
```

Then, select option `2` and enter `1` to host the game.

2. The other player should join the game by running:

#### On Linux

```sh
./tic_tac_toe
```

#### On Windows

```sh
tic_tac_toe.exe
```

Then, select option `2` and enter `0` to join the game.

## Cleaning Up

To clean up the build files, run the following command:

### On Linux

```sh
make clean
```

### On Windows (using MinGW and Make)

```sh
mingw32-make clean
```

This will remove the compiled object files and the executable.


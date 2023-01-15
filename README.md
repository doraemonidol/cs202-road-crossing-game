# CS202 - Final Project - Road Crossing Game - OOP / SFML

This is our Road Crossing Game clone for the CS202 Final Assignment using **OOP concept** and **SFML library**.

![menu-bg-sample](https://user-images.githubusercontent.com/87884396/212503163-e0406cb4-5454-45da-b903-c6c3f58b32bb.png)

---

## Authors :wave:

- 21125041 - Đặng Hoàng Nhật Hưng ([@doraemonidol](https://github.com/doraemonidol))
- 21125165 - Trần Hải Nam ([@doraemonidol](https://github.com/doraemonidol))
- 21125045 - Hứa Trường Khả ([@doraemonidol](https://github.com/doraemonidol))

---

## How To Use

To clone and run this application, you'll need [Git](https://git-scm.com) and [Chocolatey](https://chocolatey.org).

```bash
# Install make command
$ choco install make

# Clone this repository
$ git clone https://github.com/doraemonidol/cs202-road-crossing-game.git

# Go into the repository
$ cd cs202-road-crossing-game/cs202-road-crossing-game/

# Build the executable
$ make

# Run the game
$ bin/Release/crossing-the-universe.exe
```

---

## Technology Used

- ["SFML" library](https://www.sfml-dev.org/)

---

## Features

### Graphics and Sound

Pixel art style with 8-bit retro music.
Game textures are based on some design on
- [Freepik](https://www.freepik.com/)
- [Dribble](https://dribbble.com/) and
- Craftpix](https://craftpix.net/).

Music are from 
- [xDeviruchi](https://www.youtube.com/watch?v=5bn3Jmvep1k)
- [Jeremy Blake](https://www.youtube.com/watch?v=l7SwiFWOQqM)
- 
- [Final Fantasy IV](https://www.youtube.com/watch?v=ID3qmuAiadA) and
- [8 Bit Universe](https://www.youtube.com/watch?v=9NcPvmk4vfo)

#### Backstory

We intended to renovate it using some graphics libraries. However, since this version is working flawlessly and we are also in love with its minimalistic look, we've come to the decision that this will be our final version :smile:.

### Basic Features

- Drawing the board (including cells, mines and flags).
- Changing a cell's state when it is selected.
- A timer.
- Game levels.
- Generating random mines positions.
- Receiving the new position of the pointer (to select a cell) from the console.
- Saving the current state of the playing board.
- Loading the previously saved board.
- A leaderboard.
- Message boxes to prompt the user.

#### There are 3 game levels:

- **Beginner:** 9x9 cells, 10 mines.
- **Intermediate:** 16x16 cells, 40 mines.
- **Expert:** 30x16 cells, 99 mines.

### Remarkable Features

- Changing the game's resolution corresponding to the current level to improve user experience.
- Guaranteeing that the first clicked cell is not a mine.
- Making our own library for manipulating the console based on the "windows.h" library.

---

## How to Play

- `W`, `A`, `S`, `D`: Move cursor.
- `J`, `Enter`: Select options | Reveal current cell.
- `K`: Reveal all adjacent cells of the current cell.
- `L`: Flag current cell.
- `O`: Save current board.
- `R`: Restart current game.
- `Esc`: Exit current game | Go back to menu.

---

## Screenshots

![image](https://user-images.githubusercontent.com/47299149/147375758-7fe57c0b-d3b6-4f88-b93d-2b21aa20122b.png)
![image](https://user-images.githubusercontent.com/47299149/147375766-3c3ac961-ff60-49f6-b62b-f81c267dc730.png)
![image](https://user-images.githubusercontent.com/47299149/147375809-d24436fe-e176-4f62-b4b3-7fbc90dd6372.png)
![image](https://user-images.githubusercontent.com/47299149/147375815-c62fef09-3902-43ae-83e4-00e1d629707e.png)

---

## Additional Information

### Project Requirements

#### Basic Features

- Game rules: [Minesweeper Online](https://minesweeper.online/)
- Drawing the board (including cells, mines and flags).
- Changing a cell's state when it is selected.
- A timer.
- Functions: New game, change board dimensions, select a function from console screen.
- Randomizing the positions of the mines.
- Receiving the new position of the pointer (to select a cell) from the console.
- Saving the current state of the playing board.
- Loading the previously saved board.
- A leaderboard.

#### Other Features

- Using the keyboard (arrow keys) to select a cell.
- Rendering images.
- Using structs.

---

## License

> You can check out the full license [here](https://github.com/sangpham2710/CS161-Project/blob/main/LICENSE)

This project is licensed under the terms of the **MIT** license.

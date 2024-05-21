# Description
In this game, you are a human and you need to survive as long as you can by avoiding stronger animals or plants. The same is implemented using 3 languages: C++, Java and Python with some minor differences between languages (mostly visual). More description of the game is in the [instruction](OOP_project_ENG.pdf) file.
## Controls
### C++
* "q": quit the game
* "up", "left", "down", "right" arrow keys to move
* "a": use the ability
* "s": save file
* "l": load file
### Java
* "w", "a", "s", "d": keys for moving in the square grid (up, left, down, right respectively)
* "q", "w", "e", "a", "s", "d": keys for moving in the square grid (up-left, up, up-right, down-left, down, down-right respectively)
* "r": ability
### Python
* "w", "a", "s", "d": keys for moving (up, left, down, right respectively)
* "r": ability
## Customization
You can change many parameters of the game (like initial positions of organisms) and how the window looks like.\
Additionally, in java you can change between hexagonal and square grid.

# Example screens from the game
## C++
![image](https://github.com/polemaster/game_of_life/assets/88908662/53f55c89-61d2-4041-9a4d-92375a497218)

## Java
![image](https://github.com/polemaster/game_of_life/assets/88908662/949e1009-b88b-46b4-8471-2f9d412a4aad)

## Python
![image](https://github.com/polemaster/game_of_life/assets/88908662/5b9dc990-47f6-4808-9876-f70a9dcb5240)

# Installation and execution (on Linux)
## C++
*cmake*, *make*, *g++* and *ncurses* required\
After cloning the repo, go to the *cpp* directory and type in terminal:
```
mkdir build
cd build
cmake ..
make
./game_of_life
```
## Java
Only Java environment required - no additional packages need to be installed. Run the *Main.java* file.
## Python
*Python 3* required\
After cloning the repo, go to the *python* directory, and then create virtual environment and install pygame by typing:
```
python3 -m venv venv
source venv/bin/activate
pip install pygame
```
And run the game: 
```
python3 main.py
```

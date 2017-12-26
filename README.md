# Pong
An implementation of Pong using SDL2. It includes the ability to pause in the middle of a match, the ability to play against an AI, and watch two AI play each other.



## Installation

This program was originally developed with Visual Studio 2017 and SDL2-2.0.7. In addition, the SDL2_TTF library was used for 

The process of building the program should be as follows
1. Download the SDL2-2.0.7 development source (or the most recent version available) and extract to a folder. Do the same for SDL2_TTF and make sure to extract it to the same folder.
2. Download Visual Studio 2017 (Or newest version).
3. Create an environment variable called $(SDL2) pointing to the folder containing the SDL2 source.
4. Clone the this repository.
5. Open the solution file.
6. Build the project in either release or debug mode.
7. Copy over the appropriate DLL's (SDL2, SDL2_ttf, zlib1, libfreetype-6) to the same directory as the executable.
8. Copy over the fonts from fonts folder to a "res" folder in the location of the executable.
9. You should be able to run the program now and play Pong.

## Usage
- Play to three points to win.
- The W and S keys move the left paddle. The Up and Down Arrow keys move the right paddle.
- Vs AI mode turns the right paddle into an opponent.
- Bot Game turns over control to both paddles. Just sit back and watch.
- The P key pauses the game. Pressing the P key again unpauses it.
- The Escape key brings you back to the main menu and the game is reset on the next option you choose.

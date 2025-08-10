# BINGO Game

This project is a console-based implementation of the classic game of Bingo, developed in C++. It features a two-player mode, a high-score system, and the ability to save and resume games. The application is designed to be run in a command-line environment on a system that supports C++ compilation.

## Author
  * M Basim Irfan (23L-0846)

## Features

  * **Two-Player Gameplay:** Players take turns selecting numbers from their respective Bingo tables.

  * **Dynamic Tables:** The game generates unique, random Bingo tables for each player.

  * **Scoring System:** The first player to complete a line (row, column, or diagonal) wins the round.

  * **Game History:** The application records the winners and losers of each game in a `game_history.txt` file.

  * **High Scores:** A "Hall of Fame" feature tracks players with the most wins, storing the data in a `high_scores.txt` file.

  * **Save & Resume:** Players can save an ongoing game and resume it later from the main menu.

  * **Instructions:** A dedicated "How to Play" screen provides instructions for new players.

  * **User-Friendly Interface:** The game uses `system("CLS")` and `system("color")` to provide a clean and colorful console interface.

## How to Compile and Run

To compile and run this program, you will need a C++ compiler (like g++).

1.  **Save the file:**
    Save the provided code as `Bingo.cpp`.

2.  **Compile the code:**
    Open a terminal or command prompt and navigate to the directory containing the file. Use the following command to compile:

    ```
    g++ Bingo.cpp -o Bingo.exe

    ```

3.  **Run the executable:**
    Execute the compiled file:

    ```
    ./Bingo.exe

    ```

## Files

The game uses the following external files to store persistent data. These files will be created automatically if they do not exist.

  * `game_history.txt`: Stores a log of all completed games, including the winner and loser.

  * `high_scores.txt`: Contains the top players' names and their win counts.

  * `resume_game.txt`: Stores the state of a game when a player chooses to save and exit.

  * `game_instructions.txt`: This file is required to display the "How to Play" instructions. It should contain the instructions you wish to display. A sample content for this file would be:

    ```
    HOW TO PLAY BINGO

    1. The game is for two players.
    2. Each player gets a randomly generated grid of numbers.
    3. Players take turns calling out a number.
    4. If the number exists on a player's grid, it is marked off (replaced with 0).
    5. The first player to get 5 lines (rows, columns, or diagonals) wins.

    ```

## Project Structure

The project is structured with multiple functions for a clear and organized approach:

  * `main_menu()`: Displays the main menu with options for New Game, Continue, History, High Scores, Instructions, and Exit.

  * `new_game()`: Starts a new game, including player name input and table generation.

  * `continue_game()` and `resume_game()`: Handles saving and loading game states to a file.

  * `display_history()` and `display_high_scores()`: Reads from files and displays game history and high scores.

  * `replace_number()`: Marks a number on the Bingo grid.

  * `row_check()`, `column_check()`, `main_diagonal_check()`, `secondary_diagonal_check()`: Functions to check for winning conditions.

  * `table_display()`: Prints the Bingo table to the console.

  * `random_table()`: Generates a new, unique Bingo table.

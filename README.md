# CS3503 Project 1 - BitBoard Checkers
## Author:##
Louis Cushnie

## Course Info
- Course: CS 3503 – Computer Organization & Architecture  
- Project: P1 – BitBoard Checkers
- Language: C Programming  

## Description
This program is a simple checkers game implemented using **bitboard logic**.  
Each 64-bit integer represents the game board and stores piece locations using bits.  
The player can move pieces or capture opponents by typing moves such as `C6 D5` or `C6 E4`.

## Build Instructions
Compile and run from the terminal (Linux/macOS/WSL/Cygwin):
```bash
make
./checkers
```

## Gameplay Instructions
 - Red moves first.
 - To move, enter coordinates (e.g., C6 D5).
 - Captures are two-square diagonal jumps (e.g., C6 E4).
 - Pieces reaching the opposite side are promoted to kings 👑 automatically.
 - The game ends when one player has no pieces left.

## Sample output of text
```=== BitBoard Checkers ===
Current turn: Red
Enter move like C6 D5 or C6 E4
Red moves: C6 D5
Black moves: B3 A4
Red captures: E6 C4
👑 Red piece promoted to KING!
🏁 Red wins! Black has no pieces left.
Game Over. Thanks for playing!
```

## Repository/Submission Contents
- `bitops.c` – implementation of bit functions
- `bitops.h` – header file for `bitops.c` functions
- `checkers.c` – implementation of gameplay functions
- `checkers.h` – header file for `checkers.c` functions
- `main.c` – Executable file for the game 
- `output.txt` – Sample program output  
- `README.md` – this file  

## Notes
 - This project demonstrates bit manipulation, masking, and logical operations in C.
 - All bit operations ran error free during testing.

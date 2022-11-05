<p align="center">
	<img src="docs/logo.png">
</p>

# CHESS ++

A simple chess game made in C++ for a univesity exam. 

## Functionality
- 2 play mode 
	- **Computer vs Computer**
	- **Player vs Computer**
- all special moves have been added 
	- en-passant
	- castling
- possibility to **ask for surrender**
- **replay mode**, every match have been saved in .txt file. Two replay mode:
	- **Put replay in file .txt** with all chessboard changes.
	- **Step by Step view** with replay program

---

## Installation
**Note:** CMake is required!



---

## How to Play

First of all, you need to execute the chessboard with the desired mode: 
<p align="center">
	<img src="docs/start_chessboard.png">
</p>

if you choose **CC**:
- you need to select the maximum round

if you choose **PC**:
- you need to chose your player name

### it's time to make a move! ♟️

**How to read a move:**

<p align="center">
	<img src="docs/how_to_read_a_move.png">
</p>

>what is F2 or F4?

this is the layout of our virtual chessboard:

<p align="center">
	<img src="docs/chessboard.png">
</p>

>**Note:** white pieces are lower case, black pieces are upper case

- the numbers *[1,8]* are the rows
- the letters *[A,H]* are the  colums

A square coordinates composition is **{letter}{number}**

when it's your turn, monitor display this message (Rick is my nick 😉):

<p align="center">
	<img src="docs/monitor_message.png">
</p>

**what you can do?**
- **DRAW:** you can request a draw and bot decide if accept o decline
- **XXXX:** print the current status of virtual chessboard
- **Write Move:** make your next move


---

## How to Replay


### Replay

- rimossi tutti gli spazi in tutte le istruzioni ad input => A2 A4 == A2A4 (not case sensitive)
- le partite in cui il pg chiede patta in prima mossa (player = bianco) e viene accettata la partita non viene salvata.


github : https://github.com/RickSrick/ChessPlusPlus
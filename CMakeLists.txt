cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(ChessPlusPlus VERSION 1.0)

add_library(chessboard 
	include/chessboard.h
	src/chessboard.cpp
)

add_library(path 
	include/path.h
	src/path.cpp
)

add_library(piece 
	include/piece.h
	src/piece.cpp
)

add_library(pieces 
	include/pieces.h
	src/pieces.cpp
)

add_library(player 
	include/player.h
	src/player.cpp
)

add_executable(scacchiera
	scacchiera.cpp
)

add_executable(replay
	replay.cpp
)

target_link_libraries(
	scacchiera
	chessboard
	pieces
	player
	piece
	path
)
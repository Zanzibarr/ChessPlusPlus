cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(ChessPlusPlus VERSION 1.0)

set(CMAKE_CXX_FLAGS, "-02")
set(CMAKE_CXX_FLAGS_DEBUG, "-02")
set(CMAKE_CXX_FLAGS_RELEASE, "-02")

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

target_link_libraries( scacchiera
	chessboard
	pieces
	player
	piece
	path
)

target_link_libraries( replay
	chessboard
	pieces
	player
	piece
	path
)
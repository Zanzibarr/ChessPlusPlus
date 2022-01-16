cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(ChessPlusPlus VERSION 1.0)


add_library(path 
	lib/path/path.h
	lib/path/path.cpp
)
	
add_library( piece
	lib/piece/piece.h
	lib/piece/piece.cpp
)

add_library(chessboard
	lib/chessboard/chessboard.h
	lib/chessboard/chessboard.cpp
)

add_executable(scacchiera
	prova.cpp
)

target_include_directories(scacchiera PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)

target_link_libraries(scacchiera
	chessboard
	piece
	path
	)
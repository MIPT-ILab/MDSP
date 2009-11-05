project (mdsp-asm)
cmake_minimum_required (VERSION 2.6.0)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

set (SRC_FILES
	main.cpp
	tokenan.cpp
	semantican.cpp
	assembler.cpp
	../funcsim/operation.cpp
	../../pzaichenkov/memory.cpp
	)

add_executable (mdsp-asm ${SRC_FILES})

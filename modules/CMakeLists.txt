cmake_minimum_required(VERSION 2.8.11)

if(WITH_GANIMEDE)
	add_subdirectory(Ganymede)
endif()

add_subdirectory(Jupiter)
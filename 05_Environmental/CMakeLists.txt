cmake_minimum_required(VERSION 3.3)

project(Show)

OPTION(NO_UTF "Turn UTF off" OFF)

IF(NO_UTF)
    ADD_DEFINITIONS(-DNO_UTF)
ENDIF(NO_UTF)
find_path (PCRE2_INCLUDE_DIR pcre2.h
	include/pcre2
	include/PCRE2
	include
)

find_library (PCRE2_LIBRARY NAMES pcre2-8 PCRE2)

find_package(Curses REQUIRED)
include_directories(${PCRE2_INCLUDE_DIRECTORIES})
include_directories(${CURSES_INCLUDE_DIRECTORIES})


add_executable(main main.c)
message(STATUS ${PCRE2_LIBRARY})
message(STATUS ${CURSES_LIBRARY})
target_link_libraries(main ${PCRE2_LIBRARY} ${CURSES_LIBRARY})

add_custom_target(allclean 
                  COMMAND rm -rf ${CMAKE_BINARY_DIR}/CMake* 
                                 ${CMAKE_BINARY_DIR}/cmake* 
                                 ${CMAKE_BINARY_DIR}/Makefile 
                                 ${CMAKE_BINARY_DIR}/05_Environmental)
